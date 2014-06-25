# version 120 

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Mine is an old machine.  For version 130 or higher, do 
// in vec4 color;  
// in vec3 mynormal; 
// in vec4 myvertex;
// That is certainly more modern

varying vec4 color;
varying vec3 mynormal; 
varying vec4 myvertex; 

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.  These could be varying and/or bound to 
// a buffer.  But for now, I'll just make them uniform.  
// I use ambient, diffuse, specular, shininess as in OpenGL.  
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

	float nDotL = dot(normal, direction)  ;
	vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;

	float nDotH = dot(normal, halfvec) ;
	vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;

	vec4 retval = lambert + phong ;
	return retval ;
}

void main (void) 
{       
    if (enablelighting) {       
        vec4 finalcolor; 
		int i;
        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

        // Color all pixels black for now, remove this in your implementation!
        finalcolor = vec4(0,0,0,1); 
		finalcolor = ambient;

		vec3 eyepos = vec3(0, 0, 0);
		vec4 _mypos = gl_ModelViewMatrix * myvertex;
		vec3 mypos = _mypos.xyz / _mypos.w;
		vec3 eyedirn = normalize(eyepos - mypos);
		vec3 _normal = (gl_ModelViewMatrixInverseTranspose * vec4(mynormal, 0.0)).xyz;
		vec3 normal = normalize(_normal);
		for (i= 0; i < numused; ++i) {
			vec4 _position = lightposn[i * 4];
			vec3 direction;
			if(_position.w == 0){  // equal ok float value ??
				direction = _position.xyz;
			}
			else {
				vec3 position = _position.xyz/ _position.w;
				direction = normalize (position - mypos);
			}
			vec3 halfvec = normalize(direction + eyedirn);
			vec4 col = ComputeLight(direction, lightcolor[i * 4],
					normal, halfvec, diffuse, specular, shininess);
			finalcolor = finalcolor + clamp (col, 0.0, 1.0);
		}
		finalcolor = clamp (finalcolor, 0.0, 1.0);	
        gl_FragColor = finalcolor; 
    } else {
        gl_FragColor = color; 
    }
}

