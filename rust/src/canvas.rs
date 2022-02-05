use crate::color::Color;

// Figure out how to do heap allocated arrays...don't need dynamic properties of vec
struct Canvas {
    width: i32,
    height: i32,
    pixels: Vec<Color>,
}

impl Canvas {
    pub fn new(width: i32, height: i32) -> Self {
        let size: usize = (width * height) as usize;
        let mut c = Self {
            width,
            height,
            pixels: Vec::with_capacity(size),
        };

        for _ in 0..size {
            c.pixels.push(Color::new(0.0, 0.0, 0.0));
        }

        c
    }
}

mod tests {
    use super::*;

    #[test]
    fn test_new() {
        let c = Canvas::new(2, 4);
        assert_eq!(c.width, 2);
        assert_eq!(c.height, 4);

        let exp = Color::new(0.0, 0.0, 0.0);
        for pix in c.pixels {
            assert!(pix.cmp(&exp)); 
        }
    }

}
