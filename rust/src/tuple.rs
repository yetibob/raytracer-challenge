use std::{ ops, cmp::PartialEq };

#[derive(Clone, Copy, Debug, PartialEq)]
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

    pub fn magnitude(&self) -> f64 {
        (self.x.powi(2) + self.y.powi(2) + self.z.powi(2) + self.w.powi(2)).sqrt()
    }

    pub fn magnitude_sq(&self) -> f64 {
        self.x.powi(2) + self.y.powi(2) + self.z.powi(2) + self.w.powi(2)
    }
}

impl ops::Add for Tuple {
    type Output = Tuple;

    fn add(self, rhs: Self) -> Self::Output {
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

    fn sub(self, rhs: Self) -> Self::Output {
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

impl ops::Mul<f64> for Tuple {
    type Output = Tuple;

    fn mul(self, rhs: f64) -> Self::Output {
        Tuple::new(self.x * rhs , self.y * rhs, self.z * rhs, self.w * rhs)
    }
}

impl ops::Div<f64> for Tuple {
    type Output = Tuple;

    fn div(self, rhs: f64) -> Self::Output {
        Tuple::new(self.x / rhs , self.y / rhs, self.z / rhs, self.w / rhs)
    }
}

impl ops::Neg for Tuple {
    type Output = Tuple;

    fn neg(self) -> Self::Output {
        Tuple::new(-self.x, -self.y, -self.z, -self.w)
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

    #[test]
    fn test_add_tuple() {
        let p = Tuple::new(1.0, 2.0, 3.0, 1.0);
        let v = Tuple::new(1.0, 2.0, 3.0, 0.0);
        let expected = Tuple::new(2.0, 4.0, 6.0, 1.0);

        assert_eq!(p+v, expected);  
    }

    #[test]
    fn test_sub_tuple() {
        let p1 = Tuple::point(3.0, 1.0, 2.0);
        let p2 = Tuple::point(5.0, -1.0, 1.0);

        let mut expected = Tuple::vector(-2.0, 2.0, 1.0);
        assert_eq!(p1-p2, expected);  


        let v = Tuple::vector(1.0, 2.0, 3.0);
        expected = Tuple::point(2.0, -1.0, -1.0);
        assert_eq!(p1-v, expected);  
    }

    #[test]
    fn test_negate_tuple() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(-1.0, 2.0, -3.0, 4.0);
        
        assert_eq!(-t, exp);
    }

    #[test]
    fn test_tuple_mul_scalar() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(3.5, -7.0, 10.5, -14.0);
        assert_eq!(t*3.5, exp);
    }

    #[test]
    fn test_tuple_div_scalar() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(0.5, -1.0, 1.5, -2.0);
        assert_eq!(t/2.0, exp);
    }

    #[test]
    fn test_tuple_magnitude() {
        let mut v = Tuple::vector(1.0, 0.0, 0.0);
        assert_eq!(v.magnitude(), 1.0);

        v = Tuple::vector(0.0, 1.0, 0.0);
        assert_eq!(v.magnitude(), 1.0);

        v = Tuple::vector(0.0, 0.0, 1.0);
        assert_eq!(v.magnitude(), 1.0);

        let exp: f64 = 14.0_f64.sqrt(); 
        v = Tuple::vector(1.0, 2.0, 3.0);
        assert_eq!(v.magnitude(), exp);

        v = Tuple::vector(-1.0, -2.0, -3.0);
        assert_eq!(v.magnitude(), exp);
    }

    #[test]
    fn test_tuple_magnitude_sq() {
        let mut v = Tuple::vector(1.0, 0.0, 0.0);
        assert_eq!(v.magnitude_sq(), 1.0);

        v = Tuple::vector(0.0, 1.0, 0.0);
        assert_eq!(v.magnitude_sq(), 1.0);

        v = Tuple::vector(0.0, 0.0, 1.0);
        assert_eq!(v.magnitude_sq(), 1.0);

        v = Tuple::vector(1.0, 2.0, 3.0);
        assert_eq!(v.magnitude_sq(), 14.0);

        v = Tuple::vector(-1.0, -2.0, -3.0);
        assert_eq!(v.magnitude_sq(), 14.0);
    }
}
