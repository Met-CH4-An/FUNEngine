#include "maths.h"

int main() {

	vec3 _v3 = vec4(1.0f, 0.0f, 3.0f, 0.0f) + vec3(0.0f, 2.0f, 0.0f);
	_v3.normalize();

	vec3 _v31 = _v3 - vec3(10.0f, 2.0f, 3.0f);

	return 0;
}