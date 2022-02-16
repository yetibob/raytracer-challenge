use crate::color::Color;

// Figure out how to do heap allocated arrays...don't need dynamic properties of vec
pub struct Canvas {
    pub width: u32,
    pub height: u32,
    pixels: Vec<Color>,
    ppm: String,
}

// Convert x, y coordinates to row major order for use in 1d array
fn convert(x: u32, y: u32, width: u32) -> usize {
    (width * y + x) as usize
}

fn clip(col: &f64) -> i64 {
    let mut clipped = (col * 255.0).round() as i64;
    if clipped < 0 {
        clipped = 0;
    } else if clipped > 255 {
        clipped = 255; 
    }
    clipped
}


impl Canvas {
    pub fn new(width: u32, height: u32) -> Self {
        Self {
            width,
            height,
            pixels: vec![Color::new(0.0, 0.0, 0.0); (width*height) as usize],
            ppm: String::from(""),
        }
    }

    pub fn write_pixel(&mut self, x: u32, y: u32, col: Color) {
        if x >= self.width || y >= self.height {
            return;
        }
        self.pixels[convert(x, y, self.width)] = col; 
    }

    pub fn write_all(&mut self, col: Color) {
        for pix in &mut self.pixels {
            *pix = col; 
        }
    }

    pub fn pixel_at(&self, x: u32, y: u32) -> &Color {
        &self.pixels[convert(x, y, self.width)]
    }

    pub fn to_ppm(&mut self) -> &String {
        self.ppm = format!("P3\n{} {}\n255\n", self.width, self.height);

        let mut pix_count = 0;
        let mut line = String::from("");

        for pix in &self.pixels {
            let rgb = vec![clip(&pix.red), clip(&pix.green), clip(&pix.blue)];

            for (idx, col) in rgb.iter().enumerate() {
                if line.len() + col.to_string().len() >= 70 {
                    if line.chars().last().unwrap() == ' ' {
                        line.pop();
                    }
                    line += "\n";
                    self.ppm += &line;
                    line = String::from("");
                }

                line += &col.to_string();
                if idx < 2 {
                    line += " ";
                }
            }

            pix_count += 1;
            if pix_count == self.width {
                if line.chars().last().unwrap() != '\n' {
                    line += "\n";
                }
                self.ppm += &line;
                line = String::from("");
                pix_count = 0;
            } else {
                line += " ";
            }
        }

        &self.ppm
    }
}

#[cfg(test)]
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
    fn test_to_ppm_header() {
        let mut c = Canvas::new(5, 3);
        let exp = format!("P3\n{} {}\n255\n", c.width, c.height);

        let ppm: Vec<&str> = c.to_ppm().split("\n").collect();
        let mut header = String::from("");

        for line in &ppm[0..3] {
            header += line;
            header += "\n";
        }

        assert_eq!(header, exp);
    }

    #[test]
    fn test_to_ppm_pixels () {
        let mut c = Canvas::new(5, 3);
        let c1 = Color::new(1.5, 0.0, 0.0);
        let c2 = Color::new(0.0, 0.5, 0.0);
        let c3 = Color::new(-0.5, 0.0, 1.0);
        c.write_pixel(0, 0, c1);
        c.write_pixel(2, 1, c2);
        c.write_pixel(4, 2, c3);
        let exp = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

        let ppm: Vec<&str> = c.to_ppm().split("\n").collect();
        let mut body = String::from("");

        for line in &ppm[3..6] {
            body += line;
            body += "\n";
        }

        assert_eq!(body, exp);
    }

    #[test]
    fn test_to_ppm_max_len() {
        let mut c = Canvas::new(10, 2);
        c.write_all(Color::new(1.0, 0.8, 0.6));

        let exp = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n\
                   153 255 204 153 255 204 153 255 204 153 255 204 153\n\
                   255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n\
                   153 255 204 153 255 204 153 255 204 153 255 204 153\n";

        let ppm: Vec<&str> = c.to_ppm().split("\n").collect();
        let mut body = String::from("");

        for line in &ppm[3..ppm.len()-1] {
            body += line;
            body += "\n";
        }

        assert_eq!(body, exp);
    }

    #[test]
    fn test_ppm_ends_in_newline() {
        let mut c = Canvas::new(10, 2);
        c.write_all(Color::new(1.0, 0.8, 0.6));
        let ppm = c.to_ppm();
        println!("{}", ppm);
        assert_eq!(ppm.chars().last().unwrap(), '\n');
    }
}
