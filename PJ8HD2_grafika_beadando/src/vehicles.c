#include "vehicles.h"

void init_vehicles(Vehicles *vehicles)
{
    load_model(&(vehicles->model), "assets/models/f1.obj");
    vehicles->vehicles_texture_id = load_texture("assets/textures/f1.png");
	
	load_model(&(vehicles->tyre), "assets/models/tyre.obj");
    vehicles->tyre_texture_id = load_texture("assets/textures/tyre.png");
	
	load_model(&(vehicles->tyre2), "assets/models/tyre2.obj");
    vehicles->tyre_texture_id = load_texture("assets/textures/tyre.png");
	
	load_model(&(vehicles->helmet), "assets/models/helmet.obj");
    vehicles->helmet_texture_id = load_texture("assets/textures/helmet.png");
	
	load_model(&(vehicles->plane), "assets/models/plane.obj");
    vehicles->plane_texture_id = load_texture("assets/textures/plane.png");


    vehicles->position.x = 3.0;
    vehicles->position.y = 0.3;
    vehicles->position.z = 0.1;

    vehicles->speed.x = 0.0;
    vehicles->speed.y = 0.0;
    vehicles->speed.z = 0.0;
   
    vehicles->rotation.x = 0.0;
    vehicles->rotation.y = 0.0;
    vehicles->rotation.z = 0.0;
    vehicles->angle = 0.0;
	
	vehicles->p_position.x = 3.0;
    vehicles->p_position.y = 0.3;
    vehicles->p_position.z = 0.1;

    vehicles->p_speed.x = 0.0;
    vehicles->p_speed.y = 0.0;
    vehicles->p_speed.z = 0.0;
   
    vehicles->p_rotation.x = 0.0;
    vehicles->p_rotation.y = 0.0;
    vehicles->p_rotation.z = 0.0;
    vehicles->p_angle = 180.0;

  
}



void set_vehicles_position(Vehicles *vehicles, vec3 newPosition)
{
    vehicles->position.x += newPosition.x;
    vehicles->position.y += newPosition.y;
    vehicles->position.z += newPosition.z;
}

void set_vehicles_rotation_y (Vehicles *vehicles, double rotation)
{
vehicles->rotation.y = rotation;
}

void set_vehicles_rotation_x (Vehicles *vehicles, double rotation)
{
vehicles->rotation.x = rotation;
}
void set_vehicles_rotation_z (Vehicles *vehicles, double rotation)
{
vehicles->rotation.z = rotation;
}

void set_vehicles_angle (Vehicles *vehicles, double angle)
{
vehicles->angle = angle;
}


void set_vehicles_speed_y(Vehicles *vehicles, double speed)
{
    vehicles->speed.y = -speed;
}

void set_vehicles_speed_x(Vehicles *vehicles, double speed)
{
    vehicles->speed.x = speed;
}

void set_vehicles_speed_z(Vehicles *vehicles, double speed)
{
    vehicles->speed.z = speed;
}

void move_vehicles(Vehicles *vehicles, double time)
{
    vehicles->position.x += vehicles->speed.x * time;
    vehicles->position.y += vehicles->speed.y * time;
    vehicles->position.z += vehicles->speed.z * time;

}

void set_plane_position(Vehicles *vehicles, vec3 newPosition)
{
    vehicles->p_position.x += newPosition.x;
    vehicles->p_position.y += newPosition.y;
    vehicles->p_position.z += newPosition.z;
}

void set_plane_rotation_y (Vehicles *vehicles, double rotation)
{
vehicles->p_rotation.y = rotation;
}

void set_plane_rotation_x (Vehicles *vehicles, double rotation)
{
vehicles->p_rotation.x = rotation;
}
void set_plane_rotation_z (Vehicles *vehicles, double rotation)
{
vehicles->p_rotation.z = rotation;
}

void set_plane_angle (Vehicles *vehicles, double angle)
{
vehicles->p_angle = angle;
}


void set_plane_speed_y(Vehicles *vehicles, double speed)
{
    vehicles->p_speed.y = -speed;
}

void set_plane_speed_x(Vehicles *vehicles, double speed)
{
    vehicles->p_speed.x = speed;
}

void set_plane_speed_z(Vehicles *vehicles, double speed)
{
    vehicles->p_speed.z = speed;
}

void move_plane(Vehicles *vehicles, double time)
{
    vehicles->p_position.x += vehicles->p_speed.x * time;
    vehicles->p_position.y += vehicles->p_speed.y * time;
    vehicles->p_position.z += vehicles->p_speed.z * time;

}
