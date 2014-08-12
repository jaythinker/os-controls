#pragma once
#include "utility/VirtualScreen.h"
#include <autowiring/autowiring.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <atomic>

struct OsControlContext {};
struct OsControlRender {
  std::shared_ptr<sf::RenderWindow> renderWindow;
  std::chrono::duration<double> timeDelta;
};

class AudioVolumeController;
class LeapInput;
class MediaController;

namespace sf {
  class Event;
  class RenderWindow;
}

int oscontrols_main(int argc, char **argv);

class OsControl :
  public CoreRunnable,
  public leap::VirtualScreenListener,
  public ExceptionFilter
{
public:
  OsControl(void);

private:
  std::mutex m_lock;
  std::condition_variable m_stateCondition;

  Autowired<leap::VirtualScreen> m_virtualScreen;
  AutoDesired<AudioVolumeController> m_avcontrol;
  AutoRequired<MediaController> m_media;
  AutoRequired<LeapInput> m_leapInput;

  AutoConstruct<sf::RenderWindow> m_mw;

  // Requirements for this to be a CoreRunnable:
  bool m_bShouldStop;
  bool m_bRunning;
  std::shared_ptr<Object> m_outstanding;

  // Indicates the number of desktop changes needed to be performed
  std::atomic<int> m_desktopChanged;

  void AdjustDesktopWindow(void);

  /// <summary>
  /// Handles window & keyboard events from the primary event dispatch loop
  /// </summary>
  void HandleEvent(const sf::Event& ev) const;

  // VirtualScreenListener overrides:
  void OnChange(void) override { ++m_desktopChanged; }

public:
  void Main(void);
  void Filter(void);

  // CoreRunnable overrides
  bool Start(std::shared_ptr<Object> outstanding) override;
  void Stop(bool graceful) override { m_bShouldStop = true; }
  bool IsRunning(void) const override { return m_bRunning; }
  bool ShouldStop(void) const override { return m_bShouldStop; }
  void Wait(void) override;
};
