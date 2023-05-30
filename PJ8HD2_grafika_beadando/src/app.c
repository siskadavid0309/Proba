#include "app.h"
//#include <unistd.h>

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "F1",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene), &(app->objects));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 27
    );
}

void show_help_image()
{
    SDL_Window* window = SDL_CreateWindow(
        "Súgó",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* image = IMG_Load("assets/textures/sugo.png");
    if (image == NULL) {
        printf("[ERROR] Failed to load help image: %s\n", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL) {
        printf("[ERROR] Failed to create texture from image: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        return;
    }

    SDL_FreeSurface(image);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                is_running = false;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void handle_app_events(App* app)
{
	
	SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

while (SDL_PollEvent(&event)) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    app->is_running = false;
                    break;
                case SDL_SCANCODE_W:
                    set_camera_speed(&(app->camera), 2);
                    break;
                case SDL_SCANCODE_S:
                    set_camera_speed(&(app->camera), -2);
                    break;
                case SDL_SCANCODE_E:
                    set_car_speed_x(&(app->scene.car), 2);
                    set_car_angle(&(app->scene.car), app->scene.car.angle += 16);
                    break;
                case SDL_SCANCODE_F1:
                    show_help_image();
                    break;
					case SDL_SCANCODE_C:
					app->camera.position.x=app->scene.car.position.x-2.5;
					app->camera.position.y=app->scene.car.position.y+0.05;
					app->camera.rotation.x=0.0;
					app->camera.rotation.y=0.0;
					app->camera.rotation.z=0.0;
                    break;
                case SDL_SCANCODE_Q:
                    set_car_speed_x(&(app->scene.car), -2);
                    set_car_angle(&(app->scene.car), app->scene.car.angle -= 16);
                    break;
                case SDL_SCANCODE_A:
                    set_camera_side_speed(&(app->camera), 2);
                    break;
                case SDL_SCANCODE_D:
                    set_camera_side_speed(&(app->camera), -2);
                    break;
				case SDL_SCANCODE_KP_MINUS:
					app->scene.lighting_level -= 0.2f;
					set_lighting(app->scene.lighting_level);
                    break;
                case SDL_SCANCODE_KP_PLUS:
					app->scene.lighting_level += 0.2f;
					set_lighting(app->scene.lighting_level);

                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_S:
                    set_camera_speed(&(app->camera), 0);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_D:
                    set_camera_side_speed(&(app->camera), 0);
                    break;
                case SDL_SCANCODE_E:
                case SDL_SCANCODE_Q:
                    set_car_speed_x(&(app->scene.car), 0);
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
    }
}

}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene), elapsed_time);
	
	     if(app->scene.car.position.x >= 11)
    {
        set_car_speed_x(&(app->scene.car), 0); 
		//sleep(0.1);
						time_t t1;
		 t1 = time(0) + 3;
		 while(  time(0) < t1)
			 ;
		app->scene.car.position.x-=0.3;
    }
	

		 if(app->scene.car.position.x >=10.89)
    {
		app->scene.fog_level=0.2f;
		
		glFogf(GL_FOG_DENSITY, app->scene.fog_level);
		glFogfv(GL_FOG_COLOR, app->scene.fogColor);
		
    }
	else{
				app->scene.fog_level=0.0f;

		glFogf(GL_FOG_DENSITY, app->scene.fog_level);
		glFogfv(GL_FOG_COLOR, app->scene.fogColor);
	}
	
		 if(app->camera.position.x >= 11)
    {
        set_camera_speed(&(app->camera), 0);
		app->camera.position.x-=0.1;
    }
	
		if(app->camera.position.x <= -11)
    {
        set_camera_speed(&(app->camera), 0);
		app->camera.position.x+=0.1;
    }

	if(app->camera.position.y <= -5)
    {
        set_camera_speed(&(app->camera), 0);
		app->camera.position.y+=0.1;
    }
	
	if(app->camera.position.y >= 5)
    {
        set_camera_speed(&(app->camera), 0);
		app->camera.position.y-=0.1;
    }
	

    if(app->scene.car.position.x < -11.0)
    {
        
        set_car_speed_x(&(app->scene.car), 0);
		app->scene.car.position.x+=0.1;
    }
   
    move_car(&(app->scene.car), elapsed_time);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene),&(app->objects));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
