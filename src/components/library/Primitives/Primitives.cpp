#include "Primitives.h"

#include <cassert>
#include "GLTexture2.h"

void GenericShape::DrawContents(RenderState& renderState) const {
  m_geometry.Draw(Shader(), m_drawMode);
}

Sphere::Sphere() : m_Radius(1) { }

void Sphere::MakeAdditionalModelViewTransformations (ModelView &model_view) const {
  model_view.Scale(EigenTypes::Vector3::Constant(m_Radius));
}

void Sphere::DrawContents(RenderState& renderState) const {
  static PrimitiveGeometry geom;
  static bool loaded = false;
  if (!loaded) {
    PrimitiveGeometry::CreateUnitSphere(30, geom);
    loaded = true;
  }
  geom.Draw(Shader(), GL_TRIANGLES);
}

Cylinder::Cylinder() : m_Radius(1), m_Height(1) { }

void Cylinder::MakeAdditionalModelViewTransformations (ModelView &model_view) const {
  model_view.Scale(EigenTypes::Vector3(m_Radius, m_Height, m_Radius));
}

void Cylinder::DrawContents(RenderState& renderState) const {
  static PrimitiveGeometry geom;
  static bool loaded = false;
  if (!loaded) {
    PrimitiveGeometry::CreateUnitCylinder(50, 1, geom);
    loaded = true;
  }
  geom.Draw(Shader(), GL_TRIANGLES);
}

Box::Box() : m_Size(EigenTypes::Vector3::Constant(1.0)) { }

void Box::MakeAdditionalModelViewTransformations (ModelView &model_view) const {
  model_view.Scale(m_Size);
}

void Box::DrawContents(RenderState& renderState) const {
  static PrimitiveGeometry geom;
  static bool loaded = false;
  if (!loaded) {
    PrimitiveGeometry::CreateUnitBox(geom);
    loaded = true;
  }
  geom.Draw(Shader(), GL_TRIANGLES);
}

Disk::Disk() : m_Radius(1) { }

void Disk::MakeAdditionalModelViewTransformations (ModelView &model_view) const {
  model_view.Scale(EigenTypes::Vector3::Constant(m_Radius));
}

void Disk::DrawContents(RenderState& renderState) const {
  static PrimitiveGeometry geom;
  static bool loaded = false;
  if (!loaded) {
    PrimitiveGeometry::CreateUnitDisk(75, geom);
    loaded = true;
  }
  geom.Draw(Shader(), GL_TRIANGLES);
}

RectanglePrim::RectanglePrim() : m_Size(1, 1) { }

void RectanglePrim::MakeAdditionalModelViewTransformations (ModelView &model_view) const {
  model_view.Scale(EigenTypes::Vector3(m_Size.x(), m_Size.y(), 1.0));
}

void RectanglePrim::DrawContents(RenderState& renderState) const {
  bool useTexture = bool(m_texture); // If there is a valid texture, enable texturing.
  if (useTexture) {
    glEnable(GL_TEXTURE_2D);
    m_texture->Bind();
  }
  static PrimitiveGeometry geom;
  static bool loaded = false;
  if (!loaded) {
    PrimitiveGeometry::CreateUnitSquare(geom);
    loaded = true;
  }
  geom.Draw(Shader(), GL_TRIANGLES);
  if (useTexture) {
    glDisable(GL_TEXTURE_2D);
    m_texture->Unbind();
  }
}

ImagePrimitive::ImagePrimitive(void) :
  ImagePrimitive(nullptr)
{}

ImagePrimitive::ImagePrimitive(const std::shared_ptr<GLTexture2> &texture) {
  SetTexture(texture);
  SetScaleBasedOnTextureSize();
  Material().SetAmbientLightingProportion(1.0f);
  Material().SetUseTexture(true);
}

void ImagePrimitive::SetScaleBasedOnTextureSize () {
  if(Texture())
    SetSize(EigenTypes::Vector2(Texture()->Params().Width(), Texture()->Params().Height()));
}

PartialDisk::PartialDisk() : m_RecomputeGeometry(true), m_InnerRadius(0.5), m_OuterRadius(1), m_StartAngle(0), m_EndAngle(2*M_PI) { }

void PartialDisk::DrawContents(RenderState& renderState) const {
  if (m_InnerRadius >= m_OuterRadius || m_StartAngle >= m_EndAngle) {
    // don't proceed if the shape is empty
    return;
  }

  if (m_RecomputeGeometry) {
    RecomputeGeometry();
  }

  m_Geometry.Draw(Shader(), GL_TRIANGLES);
}

void PartialDisk::RecomputeGeometry() const {
  double sweepAngle = m_EndAngle - m_StartAngle;
  if (sweepAngle > 2*M_PI) {
    sweepAngle = 2*M_PI;
  }

  static const double DESIRED_ANGLE_PER_SEGMENT = 0.1; // radians
  const int numSegments = static_cast<int>(sweepAngle / DESIRED_ANGLE_PER_SEGMENT) + 1;
  const double anglePerSegment = sweepAngle / numSegments;

  m_Geometry.CleanUpBuffers();

  double curAngle = m_StartAngle;
  const double cosStart = std::cos(m_StartAngle);
  const double sinStart = std::sin(m_StartAngle);
  EigenTypes::Vector3f prevInner(static_cast<float>(m_InnerRadius*cosStart), static_cast<float>(m_InnerRadius*sinStart), 0.0f);
  EigenTypes::Vector3f prevOuter(static_cast<float>(m_OuterRadius*cosStart), static_cast<float>(m_OuterRadius*sinStart), 0.0f);
  for (int i=0; i<numSegments; i++) {
    curAngle += anglePerSegment;

    const double cosCur = std::cos(curAngle);
    const double sinCur = std::sin(curAngle);

    const EigenTypes::Vector3f curInner(static_cast<float>(m_InnerRadius*cosCur), static_cast<float>(m_InnerRadius*sinCur), 0.0f);
    const EigenTypes::Vector3f curOuter(static_cast<float>(m_OuterRadius*cosCur), static_cast<float>(m_OuterRadius*sinCur), 0.0f);

    m_Geometry.PushTri(prevInner, prevOuter, curOuter);
    m_Geometry.PushTri(curOuter, curInner, prevInner);

    prevInner = curInner;
    prevOuter = curOuter;
  }

  m_Geometry.UploadDataToBuffers();

  m_RecomputeGeometry = false;
}

PartialDiskWithTriangle::PartialDiskWithTriangle()
  :
  m_TriangleSide(OUTSIDE),
  m_TrianglePosition(0.5),
  m_TriangleWidth(0.1),
  m_TriangleOffset(0.35)
{ }

void PartialDiskWithTriangle::RecomputeGeometry() const {
  double sweepAngle = m_EndAngle - m_StartAngle;
  if (sweepAngle > 2*M_PI) {
    sweepAngle = 2*M_PI;
  }

  static const double DESIRED_ANGLE_PER_SEGMENT = 0.1; // radians
  int numSegments = static_cast<int>(sweepAngle / DESIRED_ANGLE_PER_SEGMENT) + 1;
  const double anglePerSegment = sweepAngle / numSegments;

  m_Geometry.CleanUpBuffers();

  double curAngle = m_StartAngle;
  const double cosStart = std::cos(m_StartAngle);
  const double sinStart = std::sin(m_StartAngle);
  EigenTypes::Vector3f prevInner(static_cast<float>(m_InnerRadius*cosStart), static_cast<float>(m_InnerRadius*sinStart), 0.0f);
  EigenTypes::Vector3f prevOuter(static_cast<float>(m_OuterRadius*cosStart), static_cast<float>(m_OuterRadius*sinStart), 0.0f);

  bool haveStarted = false;
  bool havePassedMidpoint = false;
  bool havePassedEnd = false;
  bool haveTakenCareOfExtraAngle = false;

  const double triangleAngle = sweepAngle * m_TriangleWidth;
  const double triangleStart = m_TrianglePosition * sweepAngle + m_StartAngle - triangleAngle / 2.0;
  const double triangleEnd = triangleStart + triangleAngle;
  const double triangleMidpoint = 0.5*(triangleStart + triangleEnd);

  while (curAngle < (m_EndAngle - 0.001)) {
    curAngle += anglePerSegment;

    if (!haveStarted && curAngle > triangleStart) {
      curAngle = triangleStart;
      haveStarted = true;
    } else if (!havePassedMidpoint && curAngle > triangleMidpoint) {
      curAngle = triangleMidpoint;
      havePassedMidpoint = true;
    } else if (!havePassedEnd && curAngle > triangleEnd) {
      curAngle = triangleEnd;
      havePassedEnd = true;
    } else if (havePassedEnd && !haveTakenCareOfExtraAngle) {
      haveTakenCareOfExtraAngle = true;
      curAngle = m_StartAngle + anglePerSegment * (static_cast<int>((curAngle-m_StartAngle) / anglePerSegment));
    }

    double innerRadius = m_InnerRadius;
    double outerRadius = m_OuterRadius;
    if (curAngle >= triangleStart && curAngle <= triangleEnd) {
      double ratio = (curAngle - triangleStart) / (triangleAngle);
      double mult = -2 * std::abs(ratio-0.5) + 1;
      const double triangleHeight = m_TriangleOffset * (m_OuterRadius - m_InnerRadius);
      if (m_TriangleSide == INSIDE) {
        innerRadius -= mult * triangleHeight;
      } else if (m_TriangleSide == OUTSIDE) {
        outerRadius += mult * triangleHeight;
      }
    }

    const double cosCur = std::cos(curAngle);
    const double sinCur = std::sin(curAngle);

    const EigenTypes::Vector3f curInner(static_cast<float>(innerRadius*cosCur), static_cast<float>(innerRadius*sinCur), 0.0f);
    const EigenTypes::Vector3f curOuter(static_cast<float>(outerRadius*cosCur), static_cast<float>(outerRadius*sinCur), 0.0f);

    m_Geometry.PushTri(prevInner, prevOuter, curOuter);
    m_Geometry.PushTri(curOuter, curInner, prevInner);

    prevInner = curInner;
    prevOuter = curOuter;
  }

  m_Geometry.UploadDataToBuffers();

  m_RecomputeGeometry = false;
}