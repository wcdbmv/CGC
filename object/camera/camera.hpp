#ifndef OBJECT_CAMERA_CAMERA_HPP_
#define OBJECT_CAMERA_CAMERA_HPP_

#include "math/matrix/matrix4x4.hpp"

class Camera {
public:
	Camera();
	Camera(const Vector3D<double>&, const Vector3D<double>&, double, double, double);

	void set_position(const Vector3D<double>&);
	void set_target(const Vector3D<double>&);

	Matrix4x4<double> get_view_matrix();
	Matrix4x4<double> get_view_matrix(double);

	void RotateUpDownSphere(double);
	void RotateLeftRightSphere(double);

	void Yaw(double);
	void Pitch(double);
	void Roll(double);

private:
	HomogeneousVector3D<double> look_;
	HomogeneousVector3D<double> up_;
	HomogeneousVector3D<double> right_;

	HomogeneousVector3D<double> position_;
	HomogeneousVector3D<double> target_;
};

#endif  // OBJECT_CAMERA_CAMERA_HPP_
