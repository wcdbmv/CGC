#include "dimensional_transformations.hpp"

DimensionalTransformations::RotationOX::RotationOX(double angle) : ITransformation() {
  ResetMatrix();

  const auto c = std::cos(angle);
  const auto s = std::sin(angle);

  (*this)[1][1] = c;
  (*this)[1][2] = s;
  (*this)[2][1] = -s;
  (*this)[2][2] = c;
}

DimensionalTransformations::RotationOY::RotationOY(double angle) : ITransformation() {
  ResetMatrix();

  const auto c = std::cos(angle);
  const auto s = std::sin(angle);

  (*this)[0][0] = c;
  (*this)[0][2] = s;
  (*this)[2][0] = -s;
  (*this)[2][2] = c;
}

DimensionalTransformations::RotationOZ::RotationOZ(double angle) : ITransformation() {
  ResetMatrix();

  const auto c = std::cos(angle);
  const auto s = std::sin(angle);

  (*this)[0][0] = c;
  (*this)[0][1] = s;
  (*this)[1][0] = -s;
  (*this)[1][1] = c;
}

DimensionalTransformations::Rotation::Rotation(const Vector3D<double>& offset, double angle) : ITransformation() {
  ResetMatrix();

  const auto c = std::cos(angle);
  const auto s = std::sin(angle);
  const auto _1c = 1 - c;

  (*this)[0][0] = c + _1c * offset.x() * offset.x();
  (*this)[1][0] = _1c * offset.x() * offset.y() - s * offset.z();
  (*this)[2][0] = _1c * offset.x() * offset.z() + s * offset.y();
  (*this)[0][1] = _1c * offset.y() * offset.x() + s * offset.z();
  (*this)[1][1] = c + _1c * offset.y() * offset.y();
  (*this)[2][1] = _1c * offset.y() * offset.z() - s * offset.x();
  (*this)[0][2] = _1c * offset.z() * offset.x() - s * offset.y();
  (*this)[1][2] = _1c * offset.z() * offset.y() + s * offset.x();
  (*this)[2][2] = c + _1c * offset.z() * offset.z();
}

DimensionalTransformations::Translation::Translation(const Vector3D<double>& offset) : ITransformation() {
  ResetMatrix();

  (*this)[0][3] = offset.x();
  (*this)[1][3] = offset.y();
  (*this)[2][3] = offset.z();
}

DimensionalTransformations::Scaling::Scaling(double factor) {
  ResetMatrix();

  (*this)[0][0] = factor;
  (*this)[1][1] = factor;
  (*this)[2][2] = factor;
}
