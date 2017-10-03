#version 430
uniform mat4 mat_mvp;

in vec3 in_loc;
in vec4 in_col;

out vec3 f_col;

void main() {
   gl_Position = mat_mvp * vec4(in_loc, 1);
   f_col = in_col.rgb;
}
