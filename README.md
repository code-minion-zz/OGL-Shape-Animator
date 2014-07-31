#OGL-Shape-Animator
==================
##Instructions

In order to run successfully, the following files need to be in the same folder:
* playground.exe
* SimpleVertexShader.vertexshader
* SimpleFragmentShader.fragmentshader
Additionally, the Shape Config file : 'shape.ini' should be present if you wish to change the shape.

The Shape Configuration file has a rigid format that must be followed. Here is a sample config :

>shape square
>size 0.8
>color red
>movement vertical
>speed 0.4

* shape - accepts the strings 'square', 'triangle', 'circle' and 'hexagon'.
* size - accepts a scalar value. 1.0 sets the scale to the height of the window, larger than that will make the shape larger than the window.
* color - accepts the strings 'red', 'blue', 'green', 'yellow'
* movement - accepts the strings 'vertical', 'horizontal', 'circular', 'box' and 'none'
* speed - accepts a scalar value. Defines the cycles per second. For example, 0.5 means half a cycle per second, or one cycle per 2 seconds.
All characters must be lower case.

In order to change the shape at runtime, press 'Enter'. The shape config file will be read and the new shape will be deployed.

Development Notes

I decided to learn OpenGL for this test... DirectX and GDI did not seem appropriate. I found a tutorial with some samples to quickly get a running window, as well as see how standard graphics tasks like shader-binding and putting data into buffers works. 

I did try to create my own clean project after that, but being out of practice with C++ and Visual Studio, I ran into a lot of linker errors that I just couldn't figure out. I decided to just write my code on top of a working openGL sample project instead, so I could better spend time finishing all the required features.

I made a base CShape class, which contains the shape's position, color, size, and variables for animation. The CShape class also handles updating the shape's position every frame. I was going to make animation it's own class if I had leftover time. CSquare, CTriangle, CCircle and CHexagon derive from CShape, and the only additional thing they do is Draw themselves.

In hindsight, I should have wrapped OpenGL in a class to keep the main loop tidy, and encapsulate all the initialization in a single function. Asides from being short of time, the reason I didn't was that I wasn't confident that I knew OpenGL well enough to do so at the time.

For parsing my INI file, I wrote a very simple line-by-line text reader. I felt that a single function was sufficient for this task, and writing a class around it seemed like overkill.

I included vld.h during production, and by the of the project, I am happy to report there are no memory leaks.

Known Issues
* I am aware that some shapes and movement patterns may display a long trailing tail that goes off into the distance. I am unsure about the cause, my guess is that OpenGL is adding a vector to my buffer that points to some arbitrary coordinate.
* I am also aware that random objects can appear in the window, I have seen green and blue triangles before. My best guess is that garbage data is being used somewhere, although I haven't found it.
* The application may arbitrarily 'pause' for about a second sometimes. I haven't tested this on other computers, and I have exhaustively tried to find out why to no avail.
* Finally, I know that everything appears 'squashed', I have tried to fix it, but for fear of breaking everything when it's already working - and also running out of time, I left it alone.