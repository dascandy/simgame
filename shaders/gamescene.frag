#version 430

in vec3 f_nrm;
in vec3 f_col;
out vec4 color;

void main() {
//   gl_FragColor = vec4(0.5, 0.5, 0.5, 1) + 0.5*vec4(f_nrm, 0);
   color = vec4(f_col, 1);
}
