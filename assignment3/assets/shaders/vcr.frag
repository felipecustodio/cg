uniform float time;
uniform sampler2D texture;
varying vec2 vTexCoord;

//Credit: http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 seed){
    return fract(sin(dot(seed.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
    vec2 displacement = vec2(0.004, 0.0);

    float r = texture2D(texture, vTexCoord - displacement).r - 0.1;
	float g = texture2D(texture, vTexCoord).g - 0.1;
    float b = texture2D(texture, vTexCoord).b - 0.1;

    //Flicker frequency
	float flicker = 10.0;

	//Play with power to change noise frequency
	float freq = sin(pow(mod(time, flicker) + flicker, 1.9));

    //Generate noise seed
    float seed = rand(gl_FragCoord.xy + mod(time, freq)) / 10.0;

    //float x = rand(textureColor.gb);
    gl_FragColor = vec4(r + seed, g + seed, b + seed, 1.0);
    //gl_FragColor = vec4(r, g, b, 1.0);
}
