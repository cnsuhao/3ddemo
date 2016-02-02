#ifdef GL_ES
precision mediump float;
#endif      

varying vec4 v_fragmentColor;                             
varying vec2 v_texCoord;                                  
                            
void main() 
{           
    vec4 texColor = texture2D(CC_Texture0, v_texCoord); 
	
	if (texColor[0] + texColor[1] + texColor[2] < 0.2)
	{
		texColor[3] = 0.0;
	}   

	if (texColor[3] < 0.2)
	{
		texColor[3] = 1.0;
		texColor[0] = 1.0;
	}    	
	gl_FragColor = v_fragmentColor*texColor; 
}