# MiniImage
Console program for merging green screen templates with an overlay image for iconing images to various sizes. 

I made this console program to experiment with the Magic++ api for ImageMagick.  I will continue editing this console program for more experiments with this library and other image related libraries so the master may not always be the most reliable soure.  I will try and keep working verisions alocated to their own branches.

### Definitions
**Green Screen Area ** : Image area that has been defined by rgb( 0, 0, 255 ) or rgba( 0, 0, 255, 1 ).

### v.0.0.1
Takes a template image that containes green screen area and merges an overlay image in that area.

#### Commands
`MiniImage <template> <overlay> <options>`

- t or --top  :  Not active yet.
- l or --left :  Not active yet.

### TODO
- Top and left offset options.
- Auto center and scale.
- Add second overlay with green screen option.
- Add size options.
- Look into polygoning image to 3d models and implimenting a render engine.

##### MIT License
Brandon Laurence Clak
 
