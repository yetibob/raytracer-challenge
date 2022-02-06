use crate::color::Color;

// Figure out how to do heap allocated arrays...don't need dynamic properties of vec
struct Canvas {
    width: i32,
    height: i32,
    pixels: Vec<Color>,
    ppm: String,
}

impl Canvas {
    pub fn new(width: i32, height: i32) -> Self {
        let size: usize = (width * height) as usize;
        let mut c = Self {
            width,
            height,
            pixels: Vec::with_capacity(size),
            ppm: String::from(""),
        };

        for _ in 0..size {
            c.pixels.push(Color::new(0.0, 0.0, 0.0));
        }

        c
    }

    pub fn convert(x: i32, y: i32, width: i32) -> usize {
        (x + width * y) as usize
    }

    pub fn write_pixel(&mut self, x: i32, y: i32, col:Color) {
        self.pixels[Self::convert(x, y, self.width)] = col; 
    }

    pub fn pixel_at(&self, x: i32, y: i32) -> &Color {
        &self.pixels[Self::convert(x, y, self.width)]
    }

    pub fn to_ppm(&mut self) {
        self.ppm = format!("P3\n{} {}\n255", self.width, self.height);
    }

    pub fn save(&self) {}
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

    #[test]
    fn test_write_pixel() {
        let mut c = Canvas::new(10, 20);
        let red = Color::new(1.0, 0.0, 0.0);
        let exp = Color::new(1.0, 0.0, 0.0); 
        
        c.write_pixel(2, 3, red);
        assert!(c.pixel_at(2, 3).cmp(&exp));
    }

    #[test]
    fn test_to_ppm() {
        let mut c = Canvas::new(5, 3);
        let exp = format!("P3\n5 3\n255");

        c.to_ppm();
        let ppm = c.ppm.split("\n");
        let mut header = String::from("");

        let mut count = 0;
        for line in ppm {
            header += line;

            if count == 2 {
                break;
            }
            header += "\n";
            count += 1;
        }

        assert_eq!(header, exp);

    }
}
