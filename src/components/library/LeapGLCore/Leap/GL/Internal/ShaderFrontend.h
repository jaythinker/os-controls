#pragma once

#include "Leap/GL/Common.h"
#include "Leap/GL/GLHeaders.h"

namespace Leap {
namespace GL {
// The contents of the Internal namespace are not intended to be used publicly, and provide
// no guarantee as to the stability of their API.  The classes and functions are used
// internally in the implementation of the publicly-presented classes.
namespace Internal {

// This structure is for encoding a value (e.g. int32_t(10034)) in the type system for metaprogramming.
template <typename T_, T_ V_> struct Value_t { static T_ const V = V_; };

template <typename Uniform_> struct UniformNameOf_f;
template <typename Name_, Name_ NAME_, GLenum GL_TYPE_, typename CppType_> struct UniformNameOf_f<Uniform<Name_,NAME_,GL_TYPE_,CppType_>> {
  typedef Value_t<Name_,NAME_> T;
};

template <typename Uniform_> struct GlTypeMappingOf_f;
template <typename Name_, Name_ NAME_, GLenum GL_TYPE_, typename CppType_> struct GlTypeMappingOf_f<Uniform<Name_,NAME_,GL_TYPE_,CppType_>> {
  typedef Typle_t<Value_t<Name_,NAME_>,Value_t<GLenum,GL_TYPE_>> T;
};

template <typename Uniform_> struct CppTypeMappingOf_f;
template <typename Name_, Name_ NAME_, GLenum GL_TYPE_, typename CppType_> struct CppTypeMappingOf_f<Uniform<Name_,NAME_,GL_TYPE_,CppType_>> {
  typedef Typle_t<Value_t<Name_,NAME_>,CppType_> T;
};

template <typename Uniform_> struct CppTypeOf_f;
template <typename Name_, Name_ NAME_, GLenum GL_TYPE_, typename CppType_> struct CppTypeOf_f<Uniform<Name_,NAME_,GL_TYPE_,CppType_>> {
  typedef CppType_ T;
};

} // end of namespace Internal
} // end of namespace GL
} // end of namespace Leap

using namespace Leap::GL; // TEMPORARY until the Leap::GL:: scoping has been integrated into all code.