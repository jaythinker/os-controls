#pragma once

#include "EigenTypes.h"
#include "Leap/GL/BufferObject.h"
#include "Leap/GL/Mesh.h"
#include "RenderState.h"

#include <map>
#include <vector>

using namespace Leap::GL;

namespace Leap {
namespace GL {

class Shader;

} // end of namespace GL
} // end of namespace Leap

typedef Mesh<VertexAttribute<GL_FLOAT_VEC3>, // Position
             VertexAttribute<GL_FLOAT_VEC3>, // Normal vector
             VertexAttribute<GL_FLOAT_VEC2>, // 2D texture coordinate
             VertexAttribute<GL_FLOAT_VEC4>  // RGBA color
            > PrimitiveGeometryMesh;

namespace PrimitiveGeometry {

// TODO: make the PrimitiveGeometryMesh argument first.

// Functions for populating a PrimitiveGeometryMesh object with some simple shapes.  These functions assume that
// the draw mode of the mesh is GL_TRIANGLES.
void PushUnitSphere(int widthResolution, int heightResolution, PrimitiveGeometryMesh& geom, double heightAngleStart = -M_PI/2.0, double heightAngleEnd = M_PI/2.0, double widthAngleStart = 0, double widthAngleEnd = 2.0*M_PI);
void PushUnitCylinder(int radialResolution, int verticalResolution, PrimitiveGeometryMesh& geom, float radiusBottom = 1.0f, float radiusTop = 1.0f, double angleStart = 0, double angleEnd = 2.0*M_PI);
void PushUnitSquare(PrimitiveGeometryMesh &mesh);
void PushUnitDisk(size_t resolution, PrimitiveGeometryMesh &mesh);
void PushUnitBox(PrimitiveGeometryMesh &mesh);

} // end of namespace PrimitiveGeometry
