#ifndef CAR_H
#define CAR_H

#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

#include <obj/model.h>

typedef struct Car
{
    Model model;
	Model tyre;
	Model tyre2;
	Model helmet;
	Model barrier;
	GLuint car_texture_id;
	GLuint tyre_texture_id;
	GLuint helmet_texture_id;
	Model stop;
	GLuint stop_texture_id;
	Model pedestriantable;
	GLuint barrier_texture_id;
	GLuint pedestriantable_texture_id;
	Model plane;
	GLuint plane_texture_id;

    vec3 position;
    vec3 speed;
    vec3 rotation;
    float angle;

} Car;

void init_car(Car* car);

void set_car_position(Car* car, vec3 newPosition);

void set_car_rotation_x(Car* car, double rotation);

void set_car_rotation_y(Car* car, double rotation);

void set_car_rotation_z(Car* car, double rotation);

void set_car_angle(Car* car, double angle);

void set_car_speed_x(Car* car, double speed);

void set_car_speed_y(Car* car, double speed);


void set_car_speed_z(Car* car, double speed);


void move_car(Car* car, double time);

#endif /*CAR_H*/