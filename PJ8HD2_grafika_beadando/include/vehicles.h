#ifndef vehicles_H
#define vehicles_H

#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

#include <obj/model.h>

typedef struct Vehicles
{
    Model model;
	Model tyre;
	Model tyre2;
	Model helmet;
	GLuint vehicles_texture_id;
	GLuint tyre_texture_id;
	GLuint helmet_texture_id;
	Model plane;
	GLuint plane_texture_id;


    vec3 position;
    vec3 speed;
    vec3 rotation;
    float angle;
	vec3 p_position;
    vec3 p_speed;
    vec3 p_rotation;
    float p_angle;

} Vehicles;

void init_vehicles(Vehicles* vehicles);

void set_vehicles_position(Vehicles* vehicles, vec3 newPosition);

void set_vehicles_rotation_x(Vehicles* vehicles, double rotation);

void set_vehicles_rotation_y(Vehicles* vehicles, double rotation);

void set_vehicles_rotation_z(Vehicles* vehicles, double rotation);

void set_vehicles_angle(Vehicles* vehicles, double angle);

void set_vehicles_speed_x(Vehicles* vehicles, double speed);

void set_vehicles_speed_y(Vehicles* vehicles, double speed);


void set_vehicles_speed_z(Vehicles* vehicles, double speed);


void move_vehicles(Vehicles* vehicles, double time);

void set_plane_position(Vehicles* vehicles, vec3 newPosition);

void set_plane_rotation_x(Vehicles* vehicles, double rotation);

void set_plane_rotation_y(Vehicles* vehicles, double rotation);

void set_plane_rotation_z(Vehicles* vehicles, double rotation);

void set_plane_angle(Vehicles* vehicles, double angle);

void set_plane_speed_x(Vehicles* vehicles, double speed);

void set_plane_speed_y(Vehicles* vehicles, double speed);


void set_plane_speed_z(Vehicles* vehicles, double speed);


void move_plane(Vehicles* vehicles, double time);

#endif /*vehicles_H*/