#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Point position;
    Point target;
    Point up;
    Point perspective;
    float angle_y;
    float angle_z;
    float radius_camera;
    int screen_width;
    int screen_height;

    Camera();

    Camera(Point position, Point target, Point up, Point perspective, int screen_width, int screen_height);

    auto render_persepective() -> void;
    auto show_values() -> void;
    auto look_at() -> void;
    auto display() -> void;
    
};

#endif
