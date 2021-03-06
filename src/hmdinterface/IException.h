#pragma once

#include <stdexcept>
#include <string>

namespace Hmd {

class IContext;
class IDevice;

class IException : public std::exception {
public:

  virtual ~IException() { }

  // Returns the Hmd::IContext to which this Exception applies, or nullptr if not specified/defined.
  virtual const Hmd::IContext *Context () const = 0;
  // Returns the Hmd::IDevice to which this Exception applies, or nullptr if not specified/defined.
  virtual const Hmd::IDevice *Device () const = 0;
};

} // end of namespace Hmd
