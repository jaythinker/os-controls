#include "stdafx.h"
#include "FrameFragmenter.h"
#include "StateMachine.h"
#include "StateMachineContext.h"
#include <Leap.h>

FrameFragmenter::FrameFragmenter(void)
{
}

FrameFragmenter::~FrameFragmenter(void)
{
}

std::shared_ptr<CoreContext> FrameFragmenter::CreateMenuContext(const Leap::Hand& hand) const {
  AutoCreateContextT<StateMachineContext> ctxt;
  ctxt->Inject<StateMachine>();
  return ctxt;
}


void FrameFragmenter::AutoFilter(const Leap::Frame& frame) {
  // Hold on to our contexts, and then feed them back into m_contexts as we encounter them
  std::unordered_map<int, std::shared_ptr<CoreContext>> contexts;
  std::swap(contexts, m_contexts);

  // Process each context that we have found a hand for:
  for(auto& hand : frame.hands()) {
    std::shared_ptr<CoreContext>& ctxt = contexts[hand.id()];

    if(!ctxt)
      // Need to initialize a new context, spin it up and send it off
      ctxt = CreateMenuContext(hand);

    // Decorate with a pointer to the hand
    AutoRequired<AutoPacketFactory> factory(ctxt);
    auto packet = factory->NewPacket();
    packet->Decorate(&hand);

    // We found this context this time, do an implicit set difference by moving it
    // into our known set of subcontexts:
    contexts.erase(hand.id());
    m_contexts[hand.id()] = ctxt;
  }

  // Tell each orphan context that we've got no further information for them.  Then, when this
  // loop exits, it will be the responsibility of these subcontexts to decide when they go away.
  for(auto& value : contexts) {
    AutoRequired<AutoPacketFactory> factory(value.second);
    factory->NewPacket()->Decorate((Leap::Hand*)nullptr);
  }
}