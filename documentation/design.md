# Design

## Signal & Slots

![Signal & Slots](https://mermaid.ink/img/pako:eNqVlF1vgjAUhv9K06t96Q8ghsTo5ZaZObMbEnKEg3ST1rRFsjn_-6CWj4K6rTdAeXrO-55z4EAjESP1aLQFpeYMNhKygBNinsk0WzPk-pFtUk0O1T4h90SxDYctiVLgG4xvbqv9Y-fQbteyLzkfADPIUMKf482A70G1-FxCMYCe1-8YNRonk-laaQmR9v3hMZNzKzRZ7WLQuBCKaSaGOheC_df7MkKOv0hdphCj7IRspaw4S4TMBkdeJXtClbYbb4zHojhT5q7GXCohw0zsa6Gdl0nZZ1znSYIyVOwLQ8dRB-RYhAZuRFUXZzDGY5_Urk7Ls6cNWo5Ds-5GI2KL1KCi4Bc4N-RFzhajx9kpOy0jsdNPV-IQvejGDuNpiTNuJJYlRR5hRduprAN_-3Una5rxFCXTcI4XZ2rgRHf8XJftiDRFczrYFG3IObW5wjnSr3C9JljOaaGx0svbWhmivdQXUOum0z6bnT7QMlUGLC7_g-aLCqhOMcOAeuVtDPIjoAE_lhzkWiw_eUQ9LXN8oLn5au1vk3oJbBUefwCU-4zE?type=png)

## Workflow

```cpp
App::Run() {
  Window::Run() {
    Canvas::Draw() {
      Canvas::ClearColor();
      Scene::Draw() {
        Object::Draw() {
          // update uniform variables
          // draw triangles
          // ...
        }
      }
    }
  }
}
```
