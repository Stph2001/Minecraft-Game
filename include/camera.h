#pragma once

#ifndef _CAMERA_
#define _CAMERA_

enum class CameraDirection {
	FORWARD,
	LEFT,
	BACKWARD,
	RIGHT,
	UP,
	DOWN
};
enum class CameraSpeed { SLOW, NORMAL, FAST };

enum class Axes { X, Y, Z };

class Camera {
	void UpdateVectors() {
		glm::vec3 temp = glm::vec3(
			cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
			sin(glm::radians(rotation.x)),
			sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
		);

		lookAt = glm::normalize(temp);
		camRight = glm::normalize(glm::cross(lookAt, worldUp));
		camUp = glm::normalize(glm::cross(camRight, lookAt));
	}
public:
	Camera(
		glm::vec3 init_pos = glm::vec3(0.0f, 3.0f, 4.0f),
		glm::vec3 init_rot = glm::vec3(0.0f, -90.0f, 0.0f),
		glm::vec3 look_at = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f),
		f32 fov_angle = 45.0f,
		f32 aspect_ratio = REL_16_9
	) :
		position(init_pos),
		rotation(init_rot),
		lookAt(look_at),
		worldUp(world_up),
		fov(fov_angle),
		aspect_ratio(aspect_ratio) {
		UpdateVectors();
	}

	glm::mat4 getView() { return glm::lookAt(position, position + lookAt, camUp); }
	f32 getFovAngle() { return glm::radians(fov); }

	void InvertMovement(Axes axis) {
		switch (axis) {
		case Axes::X: facMov[0] *= -1; break;
		case Axes::Y: facMov[1] *= -1; break;
		case Axes::Z: facMov[2] *= -1; break;
		}
	}
	void InvertRotation(Axes axis) {
		switch (axis) {
		case Axes::X: facRot[0] *= -1; break;
		case Axes::Y: facRot[1] *= -1; break;
		case Axes::Z: facRot[2] *= -1; break;
		}
	}

	void ControlsKeyboard(CameraDirection cEvent, f32 deltaTime, CameraSpeed cSpeed = CameraSpeed::NORMAL) {
		f32 velocity = speed * deltaTime;

		switch (cSpeed) {
		case CameraSpeed::FAST: velocity *= speed_multiplier; break;
		case CameraSpeed::SLOW: velocity /= speed_multiplier; break;
		default: velocity *= 1; break;
		}

		if (cEvent == CameraDirection::FORWARD)
			position += velocity * facMov[2] * lookAt;
		if (cEvent == CameraDirection::LEFT)
			position -= velocity * facMov[0] * camRight;
		if (cEvent == CameraDirection::BACKWARD)
			position -= velocity * facMov[2] * lookAt;
		if (cEvent == CameraDirection::RIGHT)
			position += velocity * facMov[0] * camRight;
		if (cEvent == CameraDirection::UP)
			position += velocity * facMov[1] * camUp;
		if (cEvent == CameraDirection::DOWN)
			position -= velocity * facMov[1] * camUp;
	}
	void ControlsMouse(f32 xOffset, f32 yOffset, bool constrainPitch = true) {
		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		rotation.y += xOffset;
		rotation.x += yOffset;

		if (constrainPitch)
			if (rotation.x > 89.0f)
				rotation.x = 89.0f;
			else if (rotation.x < -89.0f)
				rotation.x = -89.0f;
		UpdateVectors();
	}
	void ControlsWheel(f32 offset) {
		fov -= (f32)offset;
		if (fov < 1.0f)
			fov = 1.0f;
		else if (fov > 45.0f)
			fov = 45.0f;
	}

	/*f32 getDynamicAspect() {
		return;
	}*/

private:
	f32 aspect_ratio;

	i32 facMov[3] = { 1, 1, 1 };
	i32 facRot[3] = { 1, 1, 1 };

	glm::vec3 worldUp;

	glm::vec3 lookAt;
	glm::vec3 camRight;
	glm::vec3 camUp;

	f32 mouseSensitivity = 0.1f;
	f32 speed = 2.5f;
	f32 speed_multiplier = 3.0f;
public:
	glm::vec3 position;
	glm::vec3 rotation;

	f32 fov;

	f32 zNear = 0.1f;
	f32 zFar = 100.0f;
};

#endif