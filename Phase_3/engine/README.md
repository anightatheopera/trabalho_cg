# Engine

How to use:
`./engine [path/to/config.xml]`

- Example:
  - `./engine ../scenes/output_scene_1/Cool_Models.xml`
  - View Mode `GL_LINE`
  - Models `[plane_1_1_x.3d,plane_1_1_y.3d,plane_1_1_z.3d]`

![example_image](../scenes/cool_model_scene/Cool_Models.png)

## Drawings

### Implemented

- View Mode `key: m`
- Quit `key: q`
- Angle Camera `key: Up, Down, Left, Right`
- Move Camera `key: mouse`
- Zoom Camera `key: - , +`
- Parse Camera starting point from scene XML
- Named Groups and Models
- Color by Model `rgb or HEX`
- VBOS
- Timed Animation Rotation and Scale

### Not Implemented

#### Mandatory

- Fix Timed Animation Translation
- Lights
- Textures

#### Extras (Not Implemented)

- Shadows
- Menus
- Dynamic Model Loading
- Multiple Scene Files
- Interactive Mode (Mouse and Keyboard) to Move Objects
- FPS Camera
- Pick Object
  