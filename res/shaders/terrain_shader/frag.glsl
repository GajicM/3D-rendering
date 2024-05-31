#version 330

in vec3 pass_normal;
in vec3 pass_world_position;
in vec2 pass_uv;
in float pass_distance;

out vec4 final_colour;



uniform sampler2D albedo;
uniform sampler2D snow;
uniform sampler2D rocks;
uniform vec3 uni_light_colour;
uniform vec3 uni_light_direction;
uniform vec3 uni_camera_position;

const float LOD_DISTANCE = 10.0;
float brightness(vec3 pix)
{
	return (pix.r + pix.g + pix.b) / 3.0;
}

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec3 ambient = vec3(0.2);
	vec3 object_colour;
	vec2 tiled_uv;
	
	 if (pass_distance < LOD_DISTANCE)
    {
       tiled_uv = pass_uv * 20.0;
    }
    else if(pass_distance< 4.0*LOD_DISTANCE/5.0)
    {
      tiled_uv=4*pass_uv;
    }else
	tiled_uv=pass_uv;
	
	
	
	
	if (pass_world_position.y<-2.5 &&pass_world_position.y>-3.5){
	
	object_colour =(mix(texture(albedo, tiled_uv).rgb,texture(rocks,tiled_uv).rgb,smoothstep(-3.5, -2.5, pass_world_position.y)));
	}else if(pass_world_position.y>-3){
	object_colour = texture(rocks, tiled_uv).rgb;
	}
	else if (pass_world_position.y<-5.5 &&pass_world_position.y>-6.5){
	object_colour =(mix(texture(snow, tiled_uv).rgb,texture(albedo,tiled_uv).rgb,smoothstep(-6.5, -5.5, pass_world_position.y)));
	}
	else if(pass_world_position.y>-6){
	object_colour=texture(albedo,tiled_uv).rgb;
	}
	else{
	object_colour=texture(snow,tiled_uv).rgb;
	}
	vec3 view_vector = normalize(pass_world_position - uni_camera_position);
	vec3 neg_view_vector = view_vector * (-1);
	vec3 normalized_normal = normalize(pass_normal);
	vec3 reflected_light = reflect(normalize(uni_light_direction), normalized_normal);
	
	float specular_factor = clamp(dot(reflected_light, neg_view_vector), 0, 1);
	specular_factor = pow(specular_factor, 5.0);
	vec3 specular_colour = object_colour * uni_light_colour * specular_factor;
	
	float light_factor = clamp(dot(normalize(pass_normal), normalize(-uni_light_direction)), 0, 1);
    vec3 diffuse_colour = (ambient * object_colour) + (object_colour * (uni_light_colour * light_factor));
	
	final_colour = vec4(diffuse_colour + specular_colour, 1.0);
	
}