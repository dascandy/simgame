#version 430

in vec3 f_col;
out vec4 color;

void main() {
   color = vec4(f_col, 1);
}
