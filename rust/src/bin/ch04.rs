use std::{
    fs,
    f64::consts::PI,
};

use rust::{
    tuple::Tuple,
    color::Color,
    canvas::Canvas,
    matrix::Matrix,
};

fn main() {
    let mut c = Canvas::new(500, 500);
    let col = Color::new(1.0, 1.0, 1.0);

    let origin = Tuple::point(c.width as f64 / 2.0, c.height as f64 / 2.0, 0.0);
    let twelve = Tuple::point(0.0, 1.0, 0.0);

    let clock_radius = c.width as f64 * (3.0 / 8.0);

    for i in 1..13 {
        let rot_y = Matrix::rotation_z(i as f64 * (PI / 6.0));
        let mut point = &rot_y * &twelve; 
        point = (point * clock_radius) + origin; 
        c.write_pixel(point.x as u32, c.height - point.y as u32, col);
    }
    


    fs::write("ch04.ppm", c.to_ppm()).expect("Uh Oh!");
}
