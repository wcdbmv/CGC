#include "camera.hpp"
#include "math/transformation/dimensional_transformations.hpp"

Camera::Camera() {
	right_[0] = right_[3] = 1;
	up_[1] = up_[3] = 1;
	look_[2] = look_[3] = 1;
}

Camera::Camera(const Vector3D<double>& pos, const Vector3D<double>& target, double yaw, double pitch, double roll)
		: position_(pos.x(), pos.y(), pos.z())
		, target_(target.x(), target.y(), target.z()) {
	Pitch(pitch);
	Yaw(yaw);
	Roll(roll);
}

void Camera::set_position(const Vector3D<double>& pos) {
	position_ = HomogeneousVector3D<double>(pos.x(), pos.y(), pos.z());
}

void Camera::set_target(const Vector3D<double>& target) {
	target_ = HomogeneousVector3D<double>(target.x(), target.y(), target.z());
}

void Camera::RotateUpDownSphere(double angle) {
	Vector3D<double> point(up_[0], up_[1], up_[2]);
	const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
	right_ = transform * right_;
	look_ = transform * look_;
	point = Vector3D<double>(target_[0], target_[1], target_[2]);
	const Matrix4x4<double> translation = DimensionalTransformations::Translation(point);
	position_ = position_ * (translation * -1.0) * transform * translation;
}

void Camera::RotateLeftRightSphere(double angle) {
	Vector3D<double> point(right_[0], right_[1], right_[2]);
	const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
	up_ = transform * up_;
	look_ = transform * look_;
	point = Vector3D<double>(target_[0], target_[1], target_[2]);
	const Matrix4x4<double> translation = DimensionalTransformations::Translation(point);
	position_ = position_ * (translation * -1.0) * transform * translation;
}

void Camera::Yaw(double angle) {
	Vector3D<double> point(up_[0], up_[1], up_[2]);
	const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
	right_ = transform * right_;
	look_ = transform * look_;
}

void Camera::Pitch(double angle) {
	Vector3D<double> point(right_[0], right_[1], right_[2]);
	const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
	up_ = transform * up_;
	look_ = transform * look_;
}

void Camera::Roll(double angle) {
	Vector3D<double> point(look_[0], look_[1], look_[2]);
	const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
	right_ = transform * right_;
	up_ = transform * up_;
}

Matrix4x4<double> Camera::get_view_matrix() {
	look_.Normalize();

	up_ = HomogeneousVector3D<double>::Cross(look_, right_);
	up_.Normalize();

	right_ = HomogeneousVector3D<double>::Cross(up_, look_);
	right_.Normalize();

	const double x = -HomogeneousVector3D<double>::Dot(right_, position_);
	const double y = -HomogeneousVector3D<double>::Dot(up_, position_);
	const double z = -HomogeneousVector3D<double>::Dot(look_, position_);

	Matrix4x4<double> tmp = {
		{right_[0], up_[0], look_[0], 0},
		{right_[1], up_[1], look_[1], 0},
		{right_[2], up_[2], look_[2], 0},
		{x, y, z, 1}
	};

	return tmp;
}
