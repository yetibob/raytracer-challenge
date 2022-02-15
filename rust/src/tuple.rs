use std::{ ops, cmp::PartialEq };

const EPSILON: f64 = 0.00001;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Tuple {
    pub x: f64,
    pub y: f64,
    pub z: f64,
    pub w: f64,
}

impl Tuple {
    pub fn new(x: f64, y: f64, z: f64, w: f64) -> Self {
        Tuple { x: x, y: y, z: z, w: w }
    }

    pub fn point(x: f64, y: f64, z: f64) -> Self {
        Tuple::new(x, y, z, 1.0)
    }

    pub fn vector(x: f64, y: f64, z: f64) -> Self {
        Tuple::new(x, y, z, 0.0)
    }

    pub fn is_point(&self) -> bool {
        self.w == 1.0
    }

    pub fn is_vector(&self) -> bool {
        self.w == 0.0
    }

    pub fn cmp(&self, oth: &Self) -> bool {
        ((self.x - oth.x).abs() <= EPSILON) &&
        ((self.y - oth.y).abs() <= EPSILON) &&
        ((self.z - oth.z).abs() <= EPSILON) &&
        ((self.w - oth.w).abs() <= EPSILON)
    }

    pub fn magnitude(&self) -> f64 {
        (self.x.powi(2) + self.y.powi(2) + self.z.powi(2) + self.w.powi(2)).sqrt()
    }

    pub fn magnitude_sq(&self) -> f64 {
        self.x.powi(2) + self.y.powi(2) + self.z.powi(2) + self.w.powi(2)
    }

    pub fn normalize(&self) -> Self {
        let m = self.magnitude();
        Tuple::new(self.x / m, self.y / m, self.z / m, self.w / m)
    }

    pub fn dot(&self, oth: &Self) -> f64 {
        (self.x * oth.x) + (self.y * oth.y) + (self.z * oth.z) + (self.w * oth.w)
    }

    pub fn cross(&self, oth: &Self) -> Self {
        Tuple::vector((self.y * oth.z) - (self.z * oth.y), (self.z * oth.x) - (self.x * oth.z), (self.x * oth.y) - (self.y * oth.x)) 
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
    fn test_cmp() {
        let t1 = Tuple::new(0.0, 0.0, 0.0, 0.0);
        let mut t2 = Tuple::new(1.0, 0.0, 0.0, 0.0);
        assert!(!t1.cmp(&t2));

        t2 = Tuple::new(0.000001, 0.0, 0.0, 0.0);
        assert!(t1.cmp(&t2));
    }
    
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
    fn test_add() {
        let p = Tuple::new(1.0, 2.0, 3.0, 1.0);
        let v = Tuple::new(1.0, 2.0, 3.0, 0.0);
        let exp = Tuple::new(2.0, 4.0, 6.0, 1.0);

        assert!((p+v).cmp(&exp));
    }

    #[test]
    fn test_sub() {
        let p1 = Tuple::point(3.0, 1.0, 2.0);
        let p2 = Tuple::point(5.0, -1.0, 1.0);

        let mut exp = Tuple::vector(-2.0, 2.0, 1.0);
        assert!((p1-p2).cmp(&exp));


        let v = Tuple::vector(1.0, 2.0, 3.0);
        exp = Tuple::point(2.0, -1.0, -1.0);
        assert!((p1-v).cmp(&exp));
    }

    #[test]
    fn test_negate() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(-1.0, 2.0, -3.0, 4.0);
        
        assert!((-t).cmp(&exp));
    }

    #[test]
    fn test_mul_by_scalar() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(3.5, -7.0, 10.5, -14.0);
        assert!((t*3.5).cmp(&exp));
    }

    #[test]
    fn test_div_by_scalar() {
        let t = Tuple::new(1.0, -2.0, 3.0, -4.0);
        let exp = Tuple::new(0.5, -1.0, 1.5, -2.0);
        assert!((t/2.0).cmp(&exp));
    }

    #[test]
    fn test_magnitude() {
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
    fn test_magnitude_sq() {
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

    #[test]
    fn test_normalize() {
        let mut v = Tuple::vector(4.0, 0.0, 0.0);

        let mut exp = Tuple::vector(1.0, 0.0, 0.0);
        assert!(v.normalize().cmp(&exp));

        let s = 14.0_f64.sqrt();
        v = Tuple::vector(1.0, 2.0, 3.0);
        exp = Tuple::vector(1.0/s, 2.0/s, 3.0/s);
        assert!(v.normalize().cmp(&exp));
        assert_eq!(v.normalize().magnitude(), 1.0);
    }

    #[test]
    fn test_dot() {
        let v1 = Tuple::vector(1.0, 2.0, 3.0);
        let v2 = Tuple::vector(2.0, 3.0, 4.0);
        assert_eq!(v1.dot(&v2), 20.0);
    }

    #[test]
    fn test_cross_product() {
        let v1 = Tuple::vector(1.0, 2.0, 3.0);
        let v2 = Tuple::vector(2.0, 3.0, 4.0);
        let exp = Tuple ::vector(-1.0, 2.0, -1.0);
        assert_eq!(v1.cross(&v2), exp);
        assert_eq!(v2.cross(&v1), -exp);
    }
}