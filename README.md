<h1>Cube Rendering using OpenGL 4.0</h1>
<p>This is a template code for use OpenGL 4.0 using FreeGLUT and C++. The code is shader-based using <a href="http://freeglut.sourceforge.net/">freeglut</a> as window manager, <a href="http://glm.g-truc.net">GLM</a> to the data structures (e.g. vec4, vec3, ma4x4, and so on) and <a href="http://glew.sourceforge.net">GLEW</a> to manage the libraries necessaries in shaders.</p>

<p>The display is just a cube where each face is split into 2 triangles. For convenience and simplicity, 36 vertexes are used to cube definition, <code>2 triangles * 3 vertexes each * 6 faces = 36</code>. Also, a vertex is composed by <code>v=(x,y,z,w)</code> for simplicity too.</p>

<p>The class <code>GLSLProgram</code> was written by me to loading/creating/managing of shaders. For example, to load and assign attributes and uniforms is just: <br>
<code>
// this is on the variable defintion <br>
CGLSLProgram program; <br>
... <br>
// this is on the init function <br>
program.loadShader(\<SHADER_PATH\>, CGLSLProgram::<VERTEX or TESSELLATION or GEOMETRY or FRAGMENT>);<br>
program.create_link(); <br>
program.enable();<br>
program.addAttribute(<ATTRIB_NAME>);
program.addUniform(<UNIFORM_NAME>);
program.addSubroutine(<SUBROUTINE_NAME>); <br>
program.addUniformSubroutine(<UNIFORM_SUBR>); <br>
program.disable();<br>
</code></p>

<p>Next, in the display function, only using enable and disable function, the program can be activated. It was developed using Visual Studio 2012 compiler because its using #pragma comment to link the .lib of freeglut and GLEW.</p>

<bold>This code is only to be used as a template. There is no efficiency inside the code.</bold>
