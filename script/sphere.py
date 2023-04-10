import typing
from pathlib import Path

import pyvista as pv
import typer

app: typer.Typer = typer.Typer()


@app.command()
def main(
    radius: float = typer.Option(0.5, "-r", "--radius"),
    center: tuple[float, float, float] = typer.Option(
        (0.0, 0.0, 0.0), "-c", "--center"
    ),
    direction: tuple[float, float, float] = typer.Option(
        (0.0, 1.0, 0.0), "-d", "--direction"
    ),
    theta_resolution: int = typer.Option(30, "-t", "--theta-resolution"),
    phi_resolution: int = typer.Option(30, "-p", "--phi-resolution"),
    start_theta: int = typer.Option(0, "-st", "--start-theta"),
    end_theta: int = typer.Option(360, "-et", "--end-theta"),
    start_phi: int = typer.Option(0, "-sp", "--start-phi"),
    end_phi: int = typer.Option(180, "-ep", "--end-phi"),
    output: Path = typer.Option(Path.cwd() / "data" / "sphere.obj", "-o", "--output"),
) -> None:
    sphere: pv.PolyData = typing.cast(
        pv.PolyData,
        pv.Sphere(
            radius=radius,
            center=center,
            direction=direction,
            theta_resolution=theta_resolution,
            phi_resolution=phi_resolution,
            start_theta=start_theta,
            end_theta=end_theta,
            start_phi=start_phi,
            end_phi=end_phi,
        ),
    )
    sphere: pv.PolyData = typing.cast(pv.PolyData, sphere.triangulate())
    plotter = pv.Plotter()
    plotter.add_mesh(sphere)
    plotter.export_obj(output)


if __name__ == "__main__":
    app()
