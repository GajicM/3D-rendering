#include <main_state.h>
#include <glad/glad.h>
#include <math.h>


#include <rafgl.h>

#include <game_constants.h>


rafgl_meshPUN_t plane;

rafgl_texture_t heightmap,  grass, rocks, snow;


rafgl_raster_t raster_hm;

/*tree*/
rafgl_meshPUN_t obj_mesh;
GLuint object_shader;
GLuint object_shader, object_uni_M, object_uni_VP, object_uni_object_colour, object_uni_light_colour, object_uni_light_direction, object_uni_ambient, object_uni_camera_position;
vec3_t object_colour = vec3m(0.8f, 0.80f, 0.8f);
vec3_t ambient = RAFGL_GRAYX(0.2f);
rafgl_framebuffer_multitarget_t fbo1;

vec3_t obj_pos[10];

mat4_t obj_bases[10];
void set_objs(){
    int k=0;
obj_pos[k++]=vec3m(6, 0, 12);
obj_pos[k++]=vec3m(8.90 ,0, 15.41);
obj_pos[k++]=vec3m(6, 0, 12);
obj_pos[k++]=vec3m(5.43 ,-3.95, 14.39);

/*stavi umesto bunnya da bude ili drvo ili ako ne nadjes fajl, onda piramida obrnuta*/

}


void init_objs(){


        for(int i=0;i<10;i++){
                 vec3_t map_uv = v3_adds(obj_pos[i], 30);
                map_uv = v3_muls(map_uv, 1.0f / 60.0f);

        float height = rafgl_bilinear_sample(&raster_hm,map_uv.x, map_uv.z).r * 2.0f / 256.0f;


        if(height==0.00f)
            continue;

        obj_pos[i].y =-height*4 +0.05;
        obj_bases[i] =m4_translation(obj_pos[i]);

}
}


vec3_t pyramid_pos[3];
mat4_t pyr_base[3];
void init_pyramid_pos(){
pyramid_pos[0]=vec3(10.7,0.0,9.6);
pyramid_pos[1]=vec3(12.3,0,10.1);
pyramid_pos[2]=vec3(13.3,0,11.1);

for(int i=0;i<3;i++){
vec3_t map_uv = v3_adds(pyramid_pos[i], 30);
        map_uv = v3_muls(map_uv, 1.0f / 60.0f);

        float height = rafgl_bilinear_sample(&raster_hm,map_uv.x, map_uv.z).r * 2.0f / 256.0f;

        printf("%f\n",height);
        pyramid_pos[i].y=-height*4 +0.2f;
        pyr_base[i]=m4_translation(pyramid_pos[i]);

}
}
static GLfloat pyramid_vertices[] =
{
    -1, -1, -1,     0, 0.4, 0,    /* z- */
     1, -1, -1,     0, 0.6, 0,
     0,  1,  0,     0, 0.8, 0,

    -1, -1,  1,     0, 0.8, 0,    /* z+ */
     1, -1,  1,     0, 0.6, 0,
     0,  1,  0,     0, 0.4, 0,

    -1, -1, -1,     0, 0.4, 0,    /* x- */
    -1, -1,  1,     0, 0.6, 0,
     0,  1,  0,     0, 0.8, 0,

     1, -1, -1,     0, 0.8, 0,    /* x+ */
     1, -1,  1,     0, 0.6, 0,
     0,  1,  0,     0, 0.4, 0,

    -1, -1, -1,     0, 0.8, 0,    /* dno 1. polovina */
    -1, -1,  1,     0, 0.7, 0,
     1, -1,  1,     0, 0.7, 0,

     1, -1,  1,     0, 0.8, 0,    /* dno 2. polovina */
     1, -1, -1,     0, 0.7, 0,
    -1, -1, -1,     0, 0.7, 0,
 /**LICA STABLA*/
    -0.25, -2, -0.25,     0, 0.5, 0,    /* dno 1. polovina STABLO m1*/
    -0.25, -2,  0.25,     1, 0.6, 0,
     0.25, -2,  0.25,     0, 0.7,1,

     0.25, -2,  0.25,     0.3, 0.5, 0.6,    /* dno 2. polovina STABLO  m2*/
     0.25, -2, -0.25,     1, 0.6,1,
    -0.25, -2, -0.25,     0, 0.7, 0,

    -0.25, -1, -0.25,     0, 0.5, 0,    /* dno 1. polovina drugi deo STABLO m3*/
    -0.25, -1,  0.25,     1, 0.6, 0,
     0.25, -1,  0.25,     0, 0.7,1,

     0.25, -1,  0.25,     0.3, 0.5, 0.6,    /* dno 2. polovina  drugi STABLO deo m4*/
     0.25, -1, -0.25,     1, 0.6,1,
    -0.25, -1, -0.25,     0, 0.7, 0,


    -0.25, -2,  0.25,     1, 0.6, 0,   //m1 2
    -0.25, -1,  0.25,     1, 0.6, 0,   // m3 2
     0.25, -2,  0.25,     0, 0.7,1,    //m1 3

    -0.25, -1,  0.25,     1, 0.6, 0,   // m3 2
     0.25, -1,  0.25,     0, 0.7,1,    // m3 3
     0.25, -2,  0.25,     0, 0.7,1,     //m1 3

    -0.25, -2,  0.25,     1, 0.6, 0,   //m1 2
    -0.25, -1,  0.25,     1, 0.6, 0,   // m3 2
    -0.25, -2, -0.25,     0, 0.5, 0,   //m1 1

    -0.25, -1,  0.25,     1, 0.6, 0,   // m3 2
    -0.25, -1, -0.25,     0, 0.5, 0,  // m3 1
    -0.25, -2, -0.25,     0, 0.5, 0, //m1 1


    0.25, -2, -0.25,     1,0,1, //M22
    -0.25, -2, -0.25,    1,0, 1,   //M23
    0.25, -1, -0.25,     1, 0,1, //M42

    0.25, -1,  0.25,     0.3, 0.5, 0.6,    /* dno 2. polovina  drugi deo m4*/
    0.25, -1, -0.25,     1, 0.6,1, //M41 42 22
    0.25, -2, -0.25,     1, 0.6,1,

    0.25, -2,  0.25,     0.3, 0.5, 0.6,    /* dno 2. polovina  m2*/
    0.25, -2, -0.25,     1, 0.6,1,
    0.25, -1,  0.25,     0.3, 0.5, 0.6,

    0.25, -1, -0.25,     0.6, 0.6,0.6,
    -0.25, -1, -0.25,     0.6, 0.7, 0.6,
    -0.25, -2, -0.25,     0.6, 0.7, 0.6,

};
static GLuint pyramid_vao, pyramid_vbo;
static GLuint shader_program_id, tree_uni_M, tree_uni_VP;
void init_tree_shader()
{

    shader_program_id = rafgl_program_create_from_name("pyramid_shader");
    tree_uni_M = glGetUniformLocation(shader_program_id, "uni_M");
    tree_uni_VP = glGetUniformLocation(shader_program_id, "uni_VP");
    glUniform1i(glGetUniformLocation(shader_program_id, "heightmap"), 0);

    glGenVertexArrays(1, &pyramid_vao);
    glGenBuffers(1, &pyramid_vbo);

    glBindVertexArray(pyramid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, pyramid_vbo);
                        /* 6 trouglova po 3 vertexa po 6 floatova */
    glBufferData(GL_ARRAY_BUFFER, 18 * 3 * 6 * sizeof(GLfloat), pyramid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

}













void load_tex(rafgl_texture_t *tex, const char *path)
{
    rafgl_raster_t raster;
    rafgl_raster_load_from_image(&raster, path);
    rafgl_texture_init(tex);
    rafgl_texture_load_from_raster(tex, &raster);

    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

}


typedef struct
{
    GLuint program_id;
    GLuint uni_M, uni_V, uni_P;

    GLuint uni_light_colour;
    GLuint uni_light_direction;
    GLuint uni_camera_position;


    GLuint special_unis[16];

    void (*tex_fun)(GLuint);

} shader_program_t;

shader_program_t terrain_shader;



void terrain_tex_fun(GLuint prog_id)
{
    glUniform1i(glGetUniformLocation(prog_id, "heightmap"), 0);
    glUniform1i(glGetUniformLocation(prog_id, "albedo"), 1);
    glUniform1i(glGetUniformLocation(prog_id,"snow"),2);
    glUniform1i(glGetUniformLocation(prog_id,"rocks"),3);
}



void load_terrain_shader()
{
    GLuint id = terrain_shader.program_id = rafgl_program_create_from_name("terrain_shader");
    terrain_shader.tex_fun = terrain_tex_fun;
    terrain_shader.uni_M = glGetUniformLocation(id, "uni_M");
    terrain_shader.uni_V = glGetUniformLocation(id, "uni_V");
    terrain_shader.uni_P = glGetUniformLocation(id, "uni_P");

    terrain_shader.uni_light_colour = glGetUniformLocation(id, "uni_light_colour");
    terrain_shader.uni_light_direction = glGetUniformLocation(id, "uni_light_direction");
    terrain_shader.uni_camera_position = glGetUniformLocation(id, "uni_camera_position");

}

void bind_shader(shader_program_t *sp)
{
    if(sp != NULL)
    {
        glUseProgram(sp->program_id);
        sp->tex_fun(sp->program_id);
    }
    else
    {
        glUseProgram(0);
    }
}


vec3_t light_direction;
vec3_t light_colour;
static rafgl_texture_t skybox_tex;

static GLuint skybox_shader, skybox_shader_cell;
static GLuint skybox_uni_P, skybox_uni_V;
static GLuint skybox_cell_uni_P, skybox_cell_uni_V;



static rafgl_meshPUN_t skybox_mesh;

static rafgl_framebuffer_simple_t fbo;






void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    light_direction = v3_norm(vec3(-60, -60,-60));
    light_colour = vec3(1.0f, 0.9f, 0.7f);


    /*skybox*/
     fbo = rafgl_framebuffer_simple_create(width, height);



    rafgl_texture_load_cubemap_named(&skybox_tex, "skybro", "png");
    skybox_shader = rafgl_program_create_from_name("v9_skybox_shader");
    skybox_shader_cell = rafgl_program_create_from_name("v9_skybox_shader_cell");

    skybox_uni_P = glGetUniformLocation(skybox_shader, "uni_P");
    skybox_uni_V = glGetUniformLocation(skybox_shader, "uni_V");

    skybox_cell_uni_P = glGetUniformLocation(skybox_shader_cell, "uni_P");
    skybox_cell_uni_V = glGetUniformLocation(skybox_shader_cell, "uni_V");

    rafgl_meshPUN_init(&skybox_mesh);
    rafgl_meshPUN_load_cube(&skybox_mesh, 1.0f);
       glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    /*skybox*/


    /*tree*/

    rafgl_meshPUN_init(&obj_mesh);
    rafgl_meshPUN_load_from_OBJ(&obj_mesh, "res/models/bunny.obj");

    glUniform1i(glGetUniformLocation(object_shader,"heightmap"),0);

    object_shader = rafgl_program_create_from_name("v8PerPixel");
     object_uni_M = glGetUniformLocation(object_shader, "uni_M");
    object_uni_VP = glGetUniformLocation(object_shader, "uni_VP");

    object_uni_object_colour = glGetUniformLocation(object_shader, "uni_object_colour");
    object_uni_light_colour = glGetUniformLocation(object_shader, "uni_light_colour");
    object_uni_light_direction = glGetUniformLocation(object_shader, "uni_light_direction");
    object_uni_ambient = glGetUniformLocation(object_shader, "uni_ambient");
    object_uni_camera_position = glGetUniformLocation(object_shader, "uni_camera_position");

    fbo1 = rafgl_framebuffer_multitarget_create(width, height, 3);

    glBindTexture(GL_TEXTURE_2D, fbo1.tex_ids[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    /*tree*/
    /*terrain*/
    rafgl_meshPUN_init(&plane);
   // rafgl_meshPUN_load_plane(&plane, 40, 40, 64, 64);
    rafgl_meshPUN_load_terrain_from_heightmap(&plane,60, 60, "res/images/iceland_heightmap.png", -10);
    load_terrain_shader();
   rafgl_raster_load_from_image(&raster_hm, "res/images/iceland_heightmap.png");

    load_tex(&heightmap,"res/images/iceland_heightmap.png");
    load_tex(&grass, "res/images/grass.jpg");
    load_tex(&rocks,"res/images/rocks.jpg");
    load_tex(&snow,"res/images/snow.png");
    /*terrain*/

   set_objs();
   init_objs();
   init_tree_shader();
   init_pyramid_pos();
}
mat4_t model, view, projection, view_projection;
/*tree*/

float radius =0.2f; // radius of the circle
float speed = 0.01; // speed of rotation
float angle = 0.0;  // current angle of rotation
/*tree**/

/* field of view */
float fov = 75.0f;

vec3_t camera_position = vec3m(0.0f, 2.0f, 1.0f);
vec3_t camera_target = vec3m(0.0f, 0.0f, 0.0f);
vec3_t camera_up = vec3m(0.0f, 1.0f, 0.0f);
vec3_t aim_dir = vec3m(0.0f, 0.0f, -1.0f);

float camera_angle = -M_PIf * 0.5f;
float angle_speed = 0.2f * M_PIf;
float move_speed = 0.8f;

float hoffset = -0.35f * M_PIf;

void v3show(vec3_t v)
{
    printf("(%.2f %.2f %.2f)\n", v.x, v.y, v.z);
}

float time = 0.0f;
int reshow_cursor_flag = 0;
int last_lmb = 0;

void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{

    time += delta_time;

    if(game_data->keys_down['A']) camera_angle -= angle_speed * delta_time;
    if(game_data->keys_down['D']) camera_angle += angle_speed * delta_time;


    if(game_data->is_lmb_down)
    {

        if(reshow_cursor_flag == 0)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        float ydelta = game_data->mouse_pos_y - game_data->raster_height / 2;
        float xdelta = game_data->mouse_pos_x - game_data->raster_width / 2;

        if(!last_lmb)
        {
            ydelta = 0;
            xdelta = 0;
        }

        hoffset -= ydelta / game_data->raster_height;
        camera_angle += xdelta / game_data->raster_width;

        glfwSetCursorPos(window, game_data->raster_width / 2, game_data->raster_height / 2);
        reshow_cursor_flag = 1;
    }
    else if(reshow_cursor_flag)
    {
        reshow_cursor_flag = 0;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    last_lmb = game_data->is_lmb_down;

    aim_dir = vec3(cosf(camera_angle), 0.0f, sinf(camera_angle));

    if(game_data->keys_down['W']) camera_position = v3_add(camera_position, v3_muls(aim_dir, move_speed * delta_time));
    if(game_data->keys_down['S']) camera_position = v3_add(camera_position, v3_muls(aim_dir, -move_speed * delta_time));

    if(game_data->keys_down[RAFGL_KEY_SPACE]) camera_position.y += 3.0f * delta_time;
    if(game_data->keys_down[RAFGL_KEY_LEFT_SHIFT]) camera_position.y -= 3.0f * delta_time;


    float aspect = ((float)(game_data->raster_width)) / game_data->raster_height;
    projection = m4_perspective(fov, aspect, 0.1f, 100.0f);

    if(!game_data->keys_down['T'])
    {
        view = m4_look_at(camera_position, v3_add(camera_position, v3_add(aim_dir, vec3(0.0f, hoffset, 0.0f))), camera_up);
    }
    else
    {
        view = m4_look_at(camera_position, vec3(0.0f, 0.0f, 0.0f), camera_up);
    }

    model = m4_identity();

    view_projection = m4_mul(projection, view);



if(!game_data->keys_down[RAFGL_KEY_G])
    {
        angle_speed = 0.2f * M_PIf;
        move_speed = 2.4f;

    }
    else
    {
        angle_speed = 5 * 0.2f * M_PIf;
        move_speed = 5 * 2.4f;

    }
 //   v3show(camera_position);
if(game_data->keys_down[RAFGL_KEY_K]){
    pyr_base[0] = m4_mul( pyr_base[0], m4_rotation(delta_time, vec3(0.0f,0.1f, 0.0f)));
    pyr_base[1] = m4_mul( pyr_base[1], m4_rotation(delta_time, vec3(0.0f,0.1f, 0.0f)));
    pyr_base[2] = m4_mul( pyr_base[2], m4_rotation(delta_time, vec3(0.0f,0.1f, 0.0f)));

     //   printf("%f \n",pyr_base[0].m13);


}
if(game_data->keys_down[RAFGL_KEY_M]){
    angle += speed;
    if (angle > 2 * M_PIf) angle -= 2 *M_PIf;
    for(int i=0;i<5;i++){
            if(i==1)continue;
            angle=-angle;
            float xx=obj_pos[i].x;
            float yy=obj_pos[i].z;
        obj_pos[i].x+=radius+sinf(angle);
        obj_pos[i].z+=radius + cosf(angle);
        vec3_t map_uv = v3_adds(obj_pos[i], 30);
            map_uv = v3_muls(map_uv, 1.0f / 60.0f);

        float height = rafgl_bilinear_sample(&raster_hm,map_uv.x, map_uv.z).r * 2.0f / 256.0f;


        if(height==0.00f)
            continue;

        obj_pos[i].y =-height*4 +0.05;
        obj_bases[i] =m4_translation(obj_pos[i]);
        obj_bases[i]=m4_mul( obj_bases[i], m4_rotation(angle, vec3(0.0f,1.0f, 0.0f)));

        obj_pos[i].x=xx;
        obj_pos[i].z=yy;

    }

}





}

void load_vec3(GLuint location, vec3_t v)
{
    glUniform3f(location, v.x, v.y, v.z);
}

void load_mat4(GLuint location, mat4_t *m)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &(m->m00));
}

void main_state_render(GLFWwindow *window, void *args)
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   render_skybox();
  //  load_terrain();
//render_trees();
    //render_tree_triangles();
}

void render_terrain(){
    glEnable(GL_DEPTH_TEST);
    bind_shader(&terrain_shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightmap.tex_id);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, grass.tex_id);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, rocks.tex_id);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, snow.tex_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(plane.vao_id);

    load_vec3(terrain_shader.uni_light_colour, light_colour);
    load_vec3(terrain_shader.uni_light_direction, light_direction);
    load_vec3(terrain_shader.uni_camera_position, camera_position);

    mat4_t identity = m4_identity();
    load_mat4(terrain_shader.uni_M, &identity);
    load_mat4(terrain_shader.uni_V, &view);
    load_mat4(terrain_shader.uni_P, &projection);


    glDrawArrays(GL_TRIANGLES, 0, plane.vertex_count);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
     glBindTexture(GL_TEXTURE_2D, 0);
}
void render_skybox(){

    glBindFramebuffer(GL_FRAMEBUFFER, fbo.fbo_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glDepthMask(GL_FALSE);


    glUseProgram(skybox_shader);
    glUniformMatrix4fv(skybox_uni_V, 1, GL_FALSE, (void*) view.m);
    glUniformMatrix4fv(skybox_uni_P, 1, GL_FALSE, (void*) projection.m);


    glBindVertexArray(skybox_mesh.vao_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_tex.tex_id);

    glDrawArrays(GL_TRIANGLES, 0, skybox_mesh.vertex_count);
    glDepthMask(GL_TRUE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    render_objs();
    render_tree_triangles();
    render_terrain();

    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_tex.tex_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDisable(GL_DEPTH_TEST);

        rafgl_texture_t tmptex;
        tmptex.tex_id = fbo.tex_id;
        rafgl_texture_show(&tmptex, 1);

    glEnable(GL_DEPTH_TEST);
}


void render_objs(){
 //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glUseProgram(object_shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightmap.tex_id);

     glBindVertexArray(obj_mesh.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for(int i=0;i<10;i++){
        if(obj_pos[i].x==0.0f && obj_pos[i].z==0.0f) continue;
    glUniformMatrix4fv(object_uni_M, 1, GL_FALSE, (void*) obj_bases[i].m);
    glUniformMatrix4fv(object_uni_VP, 1, GL_FALSE, (void*) view_projection.m);

    glUniform3f(object_uni_object_colour, object_colour.x, object_colour.y, object_colour.z);
    glUniform3f(object_uni_light_colour, light_colour.x, light_colour.y, light_colour.z);
    glUniform3f(object_uni_light_direction, light_direction.x, light_direction.y,light_direction.z);
    glUniform3f(object_uni_ambient, ambient.x, ambient.y, ambient.z);
    glUniform3f(object_uni_camera_position, camera_position.x, camera_position.y, camera_position.z);



    glDrawArrays(GL_TRIANGLES, 0, obj_mesh.vertex_count);
    }
    glBindVertexArray(0);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);



}

void render_tree_triangles()
{
 // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(pyramid_vao);
    for(int i=0;i<3;i++){
    glUniformMatrix4fv(tree_uni_M, 1, GL_FALSE, pyr_base[i].m);
    glUniformMatrix4fv(tree_uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 18 * 3);
    }

    glBindVertexArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}


void main_state_cleanup(GLFWwindow *window, void *args)
{

}

