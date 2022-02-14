use std::ops;

const EPSILON: f64 = 0.00001;

#[derive(Copy, Clone, Debug)]
pub struct Color {
   pub red: f64,
   pub green: f64,
   pub blue: f64,
}

impl Color {
    pub fn new(red: f64, green: f64, blue: f64) -> Self {
        Self {
            red,
            green,
            blue
        } 
    }

    pub fn cmp(&self, oth: &Self) -> bool {
        ((self.red - oth.red).abs() <= EPSILON) &&
        ((self.green - oth.green).abs() <= EPSILON) &&
        ((self.blue - oth.blue).abs() <= EPSILON)
    }
}

impl ops::Add for Color {
    type Output = Color;

    fn add(self, rhs: Self) -> Self::Output {
        Color::new(self.red + rhs.red, self.green + rhs.green, self.blue + rhs.blue)
    }
}

impl ops::AddAssign for Color {
    fn add_assign(&mut self, rhs: Self) {
        *self = Self {
            red: self.red + rhs.blue,
            green: self.green + rhs.green,
            blue: self.blue + rhs.blue,
        }
    }
}

impl ops::Sub for Color {
    type Output = Color;

    fn sub(self, rhs: Self) -> Self::Output {
        Color::new(self.red - rhs.red, self.green - rhs.green, self.blue - rhs.blue)
    }
}

impl ops::SubAssign for Color {
    fn sub_assign(&mut self, rhs: Self) {
        *self = Self {
            red: self.red - rhs.red,
            green: self.green - rhs.green,
            blue: self.blue - rhs.blue,
        }
    }
}

impl ops::Mul for Color {
    type Output = Color;

    fn mul(self, rhs: Self) -> Self::Output {
        Color::new(self.red * rhs.red , self.green * rhs.green, self.blue * rhs.blue)
    }
}

impl ops::Mul<f64> for Color {
    type Output = Color;

    fn mul(self, rhs: f64) -> Self::Output {
        Color::new(self.red * rhs , self.green * rhs, self.blue * rhs)
    }
}

mod tests {
    use super::*;

    #[test]
    fn test_new() {
        let c = Color::new(0.0, 1.0, 2.0);
        assert_eq!(c.red, 0.0);
        assert_eq!(c.green, 1.0);
        assert_eq!(c.blue, 2.0);
    }

    #[test]
    fn test_add() {
        let c1 = Color::new(1.0, 2.0, 3.0);
        let c2 = Color::new(2.0, 3.0, 4.0);
        let exp = Color::new(3.0, 5.0, 7.0);
        assert!((c1+c2).cmp(&exp));
    }

    #[test]
    fn test_sub() {
        let c1 = Color::new(2.0, 3.0, 4.0);
        let c2 = Color::new(1.0, 2.0, 3.0);
        let exp = Color::new(1.0, 1.0, 1.0);
        assert!((c1-c2).cmp(&exp));
    }

    #[test]
    fn test_mul_by_scalar() {
        let c1 = Color::new(2.0, 3.0, 4.0);
        let exp = Color::new(4.0, 6.0, 8.0);
        assert!((c1*2.0).cmp(&exp));
    }

    #[test]
    fn test_mul_by_color() {
        let c1 = Color::new(2.0, 3.0, 4.0);
        let c2 = Color::new(1.0, 2.0, 3.0);
        let exp = Color::new(2.0, 6.0, 12.0);
        assert!((c1*c2).cmp(&exp));
    }
}
