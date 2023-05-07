# Design

If I merely wanted to complete this assignment, my approach would be too complicated. But I always aim for my code to have some extensibility and maintainability, so I adopted the OOP paradigm at the beginning. However, OpenGL is not designed for OOP, so when I imposed OOP, it resulted in a bit odd program architecture, at least not satisfying. Anyway, as long as it can work in the end, that's fine.

## Directory Structure

- `common`: commonly used utils & helpers
- `opengl`: naive OOP wrapper for OpenGL
- `scene`: 3D scene & lights & objects
- `shader`: shaders extending naive OpenGL wrapper
- `ui`: user interface

> **Note:** The difference between `opengl::Window` and `ui::Window` is that the classes under `opengl::` are only a simple object-oriented wrapper of the OpenGL API, while `ui::` provides a higher level of encapsulation. Classes such as `opengl::Program` and `shader::Shader` have a similar relationship.

## Signal & Slots

![Signal & Slots](https://mermaid.ink/img/pako:eNqVlF1vgjAUhv9K06t96Q8ghsTo5ZaZObMbEnKEg3ST1rRFsjn_-6CWj4K6rTdAeXrO-55z4EAjESP1aLQFpeYMNhKygBNinsk0WzPk-pFtUk0O1T4h90SxDYctiVLgG4xvbqv9Y-fQbteyLzkfADPIUMKf482A70G1-FxCMYCe1-8YNRonk-laaQmR9v3hMZNzKzRZ7WLQuBCKaSaGOheC_df7MkKOv0hdphCj7IRspaw4S4TMBkdeJXtClbYbb4zHojhT5q7GXCohw0zsa6Gdl0nZZ1znSYIyVOwLQ8dRB-RYhAZuRFUXZzDGY5_Urk7Ls6cNWo5Ds-5GI2KL1KCi4Bc4N-RFzhajx9kpOy0jsdNPV-IQvejGDuNpiTNuJJYlRR5hRduprAN_-3Una5rxFCXTcI4XZ2rgRHf8XJftiDRFczrYFG3IObW5wjnSr3C9JljOaaGx0svbWhmivdQXUOum0z6bnT7QMlUGLC7_g-aLCqhOMcOAeuVtDPIjoAE_lhzkWiw_eUQ9LXN8oLn5au1vk3oJbBUefwCU-4zE?type=png)

Each object has a shader reference. The object uses this shader to draw itself when `Object::Draw()` is invoked.

## Call Flow

```cpp
App::Run() -> Window::Run() -> Canvas::Draw() -> Scene::Draw() -> Object::Draw()
```

Refer to [Call Graph](https://liblaf.github.io/tiny-mesh-viewer/dd/df1/classtiny__mesh__viewer_1_1ui_1_1Window.html#ad2143e13c67f3084a1636f831d549fb7) or source code for more intuitive description.
