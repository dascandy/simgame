#version 330
in vec3 in_loc;
in vec3 in_nrm;
in vec4 in_prop;

out vec3 f_nrm;
out vec3 f_col;

uniform mat4 mat_mvp;
layout(std140) uniform materials {
  struct {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
  } mats[64];
};

void main() {
   gl_Position = mat_mvp * vec4(in_loc, 1);
   f_nrm = mat3(mat_mvp) * in_nrm;
   f_col = mats[int(in_prop.x)].diffuse.rgb;
   //f_col = vec3(in_prop.x / 32, 0, 0);
//   f_col = mats[16].diffuse.rgb;
}
