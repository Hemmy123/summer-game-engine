# Graphics

## MasterRenderer
This is the parent renderer class that handles initialising OGL and creating different projections (ortho/perspective)

## Renderer 
Class that is responsible to rendering stuff to the screen. Objects and effects that need to be rendered are handled by dub modules such as the PostProcessor or SceneRenderObjects. Each module is responsible for holding and adjusting their respective objects. The reneder holds all of these modules and uses them to the final image to the screen.

This allows for certain effects (skybox, shadows, lighting) to be turned off or adjusted from the renderer without having all the code in the renderer.
