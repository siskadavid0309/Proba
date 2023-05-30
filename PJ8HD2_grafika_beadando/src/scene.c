#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene, Objects* objects)
{
    glClearColor(0.5, 0.8, 1.9, 1.5);
	
	scene->fan_rotation = 0;

	scene->lighting_level = 0.5;
	
	init_car(&(scene->car));
	 
	load_model(&(scene->windturbine), "assets/models/windturbine.obj");
	scene->fan_texture_id = load_texture("assets/textures/head.jpg");
	
	
	load_model(&(scene->grass), "assets/models/grass.obj");
    scene->grass_texture_id = load_texture("assets/textures/grass.jpg");
	
	load_model(&(objects->road), "assets/models/road.obj");
    objects->road_texture_id = load_texture("assets/textures/originall.png");
	
	
    load_model(&(scene->tree), "assets/models/tree.obj");
    scene->tree_texture_id = load_texture("assets/textures/tree.jpg");
	
	load_model(&(scene->head), "assets/models/head.obj");
	scene->fan_texture_id = load_texture("assets/textures/head.jpg");
	
	load_model(&(scene->bush), "assets/models/bush.obj");
    scene->bush_texture_id = load_texture("assets/textures/bush.jpg");
	

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 11.0;
	
	scene->fogColor[0]=0.5f;
	scene->fogColor[1]=0.1f;
	scene->fogColor[2]=0.1f;
	scene->fogColor[3]=1.5f;
	
	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, scene->fog_level);
	glFogfv(GL_FOG_COLOR, scene->fogColor);
	
	set_lighting(scene->lighting_level);
}

void set_lighting(float lighting_level)
{
    float ambient_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float diffuse_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float specular_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
	scene->fan_rotation += 2000*time;

}

void render_scene(const Scene* scene, const Objects* objects)
{
	glPushMatrix();
    //glTranslatef(scene->plane.position.x, scene->plane.position.y, scene->plane.position.z+10);
    //glScalef(0.1,0.1,0.1);
    glRotatef(180,0,0,1);
    glBindTexture(GL_TEXTURE_2D, scene->car.plane_texture_id);
	draw_model(&(scene->car.plane));
    glPopMatrix();
	
float turbine_spacing = 4.5; // Távolság a szélerőművek között
float head_offset = 0.05; // Fej eltolásának mértéke
glPushMatrix();
glTranslatef(-10.5, 2, 1);
for (int i = 0; i < 5; i++) {
    glPushMatrix();
    glTranslatef(i * turbine_spacing + head_offset, 6.85, 2);
    glRotatef(scene->fan_rotation, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(0.8, 0.8, 0.8);
    glBindTexture(GL_TEXTURE_2D, scene->head_texture_id);
    draw_model(&(scene->head));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(i * turbine_spacing, 7, 2);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->head_texture_id);
    draw_model(&(scene->windturbine));
    glPopMatrix();
}
 glPopMatrix();


	set_material(&(scene->material));
    set_lighting(scene->lighting_level);

	glPushMatrix();
    glTranslatef((scene->car.position.x)+0.09, scene->car.position.y-0.01, scene->car.position.z+0.27);
    glScalef(0.7,0.7,0.7);
    glRotatef(90,0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->car.helmet_texture_id);
	draw_model(&(scene->car.helmet));
    glPopMatrix();
	
	glPushMatrix();
	glTranslatef(13,-0.5,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(180,0,0,1);
	glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->car.stop_texture_id);
	draw_model(&(scene->car.stop));
    glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-13,2.7,0);
    glScalef(0.3,0.3,0.3);
	glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->car.stop_texture_id);
	draw_model(&(scene->car.stop));
    glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6,-0.5,0);
    glScalef(0.01,0.01,0.012);
	glRotatef(90,1,0,0);
	glRotatef(-90,0,1,0);

    glBindTexture(GL_TEXTURE_2D, scene->car.pedestriantable_texture_id);
	draw_model(&(scene->car.pedestriantable));
    glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6,2.5,0);
    glScalef(0.01,0.01,0.012);
    glRotatef(180,0,0,1);
	glRotatef(90,1,0,0);
	glRotatef(-90,0,1,0);
    glBindTexture(GL_TEXTURE_2D, scene->car.pedestriantable_texture_id);
	draw_model(&(scene->car.pedestriantable));
    glPopMatrix();
	
glPushMatrix();
for (int i = -4; i < 3; i++) {
    glPushMatrix();
	glScalef(0.07,0.07,0.07);
    glTranslatef(i * -40, -14.0, -5);
	glRotatef(180,0,0,1);
	glRotatef(90,1,0,0);
	glRotatef(-90,0,1,0);
    glBindTexture(GL_TEXTURE_2D, scene->bush_texture_id);
    draw_model(&(scene->bush));
    glPopMatrix();
}


glPopMatrix();	
	
	

		
		glPushMatrix();
    glTranslatef(scene->car.position.x, scene->car.position.y, scene->car.position.z);
    glScalef(1,1,1);
    glRotatef(180,0,0,1);
    glBindTexture(GL_TEXTURE_2D, scene->car.car_texture_id);
	draw_model(&(scene->car.model));
    glPopMatrix();

	glPushMatrix();
    glTranslatef((scene->car.position.x)-0.75, scene->car.position.y+0.32, scene->car.position.z+0.1);
    glScalef(0.01,0.01,0.01);
    glRotatef(scene->car.angle,0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, scene->car.tyre_texture_id);
	draw_model(&(scene->car.tyre));
    glPopMatrix();
	
		glPushMatrix();
    glTranslatef((scene->car.position.x)+0.59, scene->car.position.y+0.32, scene->car.position.z+0.1);
    glScalef(0.01,0.01,0.01);
    glRotatef(scene->car.angle,0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, scene->car.tyre_texture_id);
	draw_model(&(scene->car.tyre));
    glPopMatrix();
	
	glPushMatrix();
    glTranslatef((scene->car.position.x)+0.59, scene->car.position.y-0.32, scene->car.position.z+0.1);
    glScalef(0.01,0.01,0.01);
	glRotatef(scene->car.angle,0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, scene->car.tyre_texture_id);
	draw_model(&(scene->car.tyre2));
    glPopMatrix();
	
	glPushMatrix();
    glTranslatef((scene->car.position.x)-0.75, scene->car.position.y-0.32, scene->car.position.z+0.1);
    glScalef(0.01,0.01,0.01);
	glRotatef(scene->car.angle,0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, scene->car.tyre_texture_id);
	draw_model(&(scene->car.tyre2));
    glPopMatrix();

	glPushMatrix();
float treeSpacing = 15.0;  // A fák közötti vízszintes távolság

for (int i = -3; i < 3; i++) {
    glPushMatrix();
	glScalef(0.35,0.35,0.35);
    glTranslatef(i * treeSpacing, 15.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, scene->tree_texture_id);
    draw_model(&(scene->tree));
    glPopMatrix();
}
glTranslatef(-0.3, 0, 0);

for (int i = -3; i < 3; i++) {
    glPushMatrix();
	glScalef(0.35,0.35,0.35);
    glTranslatef(i * -treeSpacing+1, -11.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, scene->tree_texture_id);
    draw_model(&(scene->tree));
    glPopMatrix();
}

glPopMatrix();	
	
	glPushMatrix();
glTranslatef(0, 1, -0.03);
glScalef(0.3, 0.3, 0.3);

for (int i = 0; i < 20; i++) {
    glPushMatrix();
    glTranslatef(i * 5, 0.0, 0.0); 
    glBindTexture(GL_TEXTURE_2D, objects->road_texture_id);
    draw_model(&(objects->road));
    glPopMatrix();
}
for (int i = 0; i < 20; i++) {
    glPushMatrix();
    glTranslatef(-i * 5, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, objects->road_texture_id);
    draw_model(&(objects->road));
    glPopMatrix();
}

glPopMatrix();


	glPushMatrix();
glTranslatef(-26,-10,0);
glScalef(0.01, 0.01, 0.001);

float offset = 200.0;
float startX = -offset;
float startY = -offset;

for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 28; j++) {
        glPushMatrix();
        glTranslatef(startX + j * offset, startY + i * offset, -10);
		glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
        draw_model(&(scene->grass));
        glPopMatrix();
    }
}
glPopMatrix();

	
	glPushMatrix();
int i=0;
for(i=0;i<2;i++){
    glPushMatrix();
    glTranslatef(13, 1.5*i+0.25, 0); // hozzáadott tér
    glScalef(0.6, 0.6, 0.6);
    glBindTexture(GL_TEXTURE_2D, scene->car.barrier_texture_id);
    draw_model(&(scene->car.barrier));
    glPopMatrix();
}
glPopMatrix();


	glPushMatrix();
 i=0;
for(i=0;i<2;i++){
    glPushMatrix();
    glTranslatef(-13, 1.5*i+0.25, 0); // hozzáadott tér
    glScalef(0.6, 0.6, 0.6);
    glBindTexture(GL_TEXTURE_2D, scene->car.barrier_texture_id);
    draw_model(&(scene->car.barrier));
    glPopMatrix();
}
glPopMatrix();

}

