# MiniImage
Console program for merging green screen templates with an overlay image to various sizes. 

I made this console program to experiment with the Magic++ api for ImageMagick.  I will continue editing this console program for more experiments with this library and other image related libraries so the master may not always be the most reliable soure.  I will try and keep working verisions alocated to their own branches.

### Definitions
** Green Screen Area ** : Image area that has been defined by rgb( 0, 0, 255 ) or rgba( 0, 0, 255, 1 ).

### v.0.0.1
Takes a template image that containes green screen area and merges an overlay image in that area.

#### Commands
`MiniImage <template> <overlay> <options>`

- t or --top  :  Accepted but not active yet.
- l or --left :  Accepted but not active yet.

### TODO
- Top and left offset options.
- Auto center and scale.
- Add second overlay with green screen option.
- Add size options.
- Add format specifier to options.
- Polygoning distorted images to 3d model objects and implimenting a render engine.  Consider using NURB math for better accuacy. 

### Notes
1. Overlay
- I chose to do a pixel by pixel replacement instead of built in manipulation functions.  Scanning this way allows a higher degree of manipulation.  For instance additional images to be overlayed such as texture or shade map, with high precision unlike the built in functionality.

2. Template
- For simplicity I choose to use a green screen area.  This may change or be configurable to blue screen area and (or) chroma key(s).

3. Options
- I want to use automated centering for overlay image but also alow it to be offset if desired, his is provided by the Geometry class just need to impliment the variables I have already set up.


[MIT License](LICENSE)
Copyright 2015 | Brandon Laurence Clak
 
