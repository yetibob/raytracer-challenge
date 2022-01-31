use std::{ ops, cmp::PartialEq };

#[derive(PartialEq)]
pub struct Tuple {
    pub x: f64,
    pub y: f64,
    pub z: f64,
    pub w: f64,
}

impl Tuple {
    pub fn new(x: f64, y: f64, z: f64, w: f64) -> Tuple {
        Tuple { x: x, y: y, z: z, w: w }
    }

    pub fn point(x: f64, y: f64, z: f64) -> Tuple {
        Tuple::new(x, y, z, 1.0)
    }

    pub fn vector(x: f64, y: f64, z: f64) -> Tuple {
        Tuple::new(x, y, z, 0.0)
    }

    pub fn is_point(&self) -> bool {
        self.w == 1.0
    }

    pub fn is_vector(&self) -> bool {
        self.w == 0.0
    }
}

impl ops::Add for Tuple {
    type Output = Tuple;

    fn add(self, rhs: Self) -> Tuple {
        Tuple::new(self.x + rhs.x, self.y + rhs.y, self.z + rhs.z, self.w + rhs.w)
    }
}

impl ops::AddAssign for Tuple {
    fn add_assign(&mut self, rhs: Self) {
        *self = Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
            w: self.w + rhs.w
        }
    }
}

impl ops::Sub for Tuple {
    type Output = Tuple;

    fn sub(self, rhs: Self) -> Tuple {
        Tuple::new(self.x - rhs.x, self.y - rhs.y, self.z - rhs.z, self.w - rhs.w)
    }
}

impl ops::SubAssign for Tuple {
    fn sub_assign(&mut self, rhs: Self) {
        *self = Self {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
            z: self.z - rhs.z,
            w: self.w - rhs.w
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_is_point() {
        let p = Tuple::point(0.0, 0.0, 0.0);
        assert!(p.is_point());
        assert!(!p.is_vector());
    }

    #[test]
    fn test_is_vector() {
        let v = Tuple::vector(0.0, 0.0, 0.0);
        assert!(v.is_vector());
        assert!(!v.is_point());
    }
}
