use std::fs;

use rust::{
    tuple::Tuple,
    color::Color,
    canvas::Canvas,
};

struct Projectile {
    position: Tuple,
    velocity: Tuple,
}

struct Environment {
    gravity: Tuple,
    wind: Tuple,
}

fn main() {
    let mut p = Projectile {
        position: Tuple::point(0.0, 1.0, 0.0),
        velocity: Tuple::vector(1.0, 1.8, 0.0).normalize() * 11.25,
    };

    let e = Environment {
        gravity: Tuple::vector(0.0, -0.1, 0.0),
        wind: Tuple::vector(-0.01, 0.0, 0.0),
    };

    let mut c = Canvas::new(900, 550);
    let col = Color::new(1.0, 0.0, 0.0);


    while p.position.y > 0.0 {
        p = tick(&e, &p); 
        c.write_pixel(p.position.x as u32, c.height - p.position.y as u32, col);
    }

    fs::write("tmp.ppm", c.to_ppm()).expect("Uh Oh!");
}

fn tick(env: &Environment, proj: &Projectile) -> Projectile {
    Projectile {
        position: proj.position + proj.velocity,
        velocity: proj.velocity + env.gravity + env.wind,
    }
}
