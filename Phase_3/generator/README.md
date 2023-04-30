# Generator

How to use:
`./generator drawing [parameters] [path/to/file.3d] [extras]`

## Drawings

### Implemented

- Plane
  - `./generator plane 1 3 plane.3d` > plane on the x/z axis
  - `./generator plane 1 3 plane.3d z` > plane on the x/y axis
  - `./generator plane 1 3 plane.3d x` > plane on the y/z axis
- Box
  - `./generator box [side] [divisions] [filename]` > box with side length 'side' and 'divisions' divisions on each axis
- Cone
  - `./generator cone [radius] [height] [slices] [stacks] [filename]` > cone with radius, height, slices and stacks
- Cylinder
  - `./generator cylinder [radius] [height] [slices] [stacks] [filename]` > cylinder with radius, height, slices and stacks
- Pyramid
  - `./generator pyramid [base] [height] [stacks] [filename]` > pyramid with base, height and stacks
- Sphere
  - `./generator sphere [radius] [slices] [stacks] [filename]` > sphere with radius, slices and stacks
- Torus
  - `./generator torus [inner_radius] [outer_radius] [slices] [stacks] [filename]` > torus with inner_radius, outer_radius, slices and stacks

### TODO

  - bezier curve
