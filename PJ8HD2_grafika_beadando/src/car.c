#include "car.h"

void init_car(Car *car)
{
    load_model(&(car->model), "assets/models/f1.obj");
    car->car_texture_id = load_texture("assets/textures/f1.png");
	
	load_model(&(car->tyre), "assets/models/tyre.obj");
    car->tyre_texture_id = load_texture("assets/textures/tyre.png");
	
	load_model(&(car->tyre2), "assets/models/tyre2.obj");
    car->tyre_texture_id = load_texture("assets/textures/tyre.png");
	
	load_model(&(car->helmet), "assets/models/helmet.obj");
    car->helmet_texture_id = load_texture("assets/textures/helmet.png");
	
	load_model(&(car->stop), "assets/models/stop.obj");
    car->stop_texture_id = load_texture("assets/textures/stop.png");
	
	load_model(&(car->pedestriantable), "assets/models/pedestriantable.obj");
    car->pedestriantable_texture_id = load_texture("assets/textures/pedestriantable.png");
	
	load_model(&(car->barrier), "assets/models/barrier.obj");
    car->barrier_texture_id = load_texture("assets/textures/barrier.png");
	
	load_model(&(car->model), "assets/models/plane.obj");
    car->plane_texture_id = load_texture("assets/textures/plane.png");


    car->position.x = 3.0;
    car->position.y = 0.3;
    car->position.z = 0.1;

    car->speed.x = 0.0;
    car->speed.y = 0.0;
    car->speed.z = 0.0;
   
    car->rotation.x = 0.0;
    car->rotation.y = 0.0;
    car->rotation.z = 0.0;
    car->angle = 0.0;

  
}



void set_car_position(Car *car, vec3 newPosition)
{
    car->position.x += newPosition.x;
    car->position.y += newPosition.y;
    car->position.z += newPosition.z;
}

void set_car_rotation_y (Car *car, double rotation)
{
car->rotation.y = rotation;
}

void set_car_rotation_x (Car *car, double rotation)
{
car->rotation.x = rotation;
}
void set_car_rotation_z (Car *car, double rotation)
{
car->rotation.z = rotation;
}

void set_car_angle (Car *car, double angle)
{
car->angle = angle;
}


void set_car_speed_y(Car *car, double speed)
{
    car->speed.y = -speed;
}

void set_car_speed_x(Car *car, double speed)
{
    car->speed.x = speed;
}

void set_car_speed_z(Car *car, double speed)
{
    car->speed.z = speed;
}

void move_car(Car *car, double time)
{
    car->position.x += car->speed.x * time;
    car->position.y += car->speed.y * time;
    car->position.z += car->speed.z * time;

}