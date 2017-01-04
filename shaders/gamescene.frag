#version 330

in vec3 f_nrm;
in vec3 f_col;

void main() {
//   gl_FragColor = vec4(0.5, 0.5, 0.5, 1) + 0.5*vec4(f_nrm, 0);
   gl_FragColor = vec4(f_col, 1);
}
