use crate::{
    tuple::Tuple,
    matrix::Matrix,
};

pub trait Object {
    fn id(&self) -> u64;
    fn origin(&self) -> Tuple;
    fn transform(&self) -> &Matrix;
}

#[derive(Debug)]
pub struct Sphere {
    pub id: u64,
    pub origin: Tuple,
    pub transform: Matrix,
}

// TODO
// This requires the use of unsafe and apparently can potentially break multithreaded/multiprocess code
// What is the proper way to do something like this in rust without globals. Should there be some kind of ID
// generation module? Maybe uuids (a crate likely exists for this)?
static mut ID: u64 = 0;

impl Sphere {
    pub fn new() -> Sphere {
        Sphere {
            id: unsafe { let orig = ID; ID = ID + 1; orig },
            origin: Tuple::point(0.0, 0.0, 0.0),
            transform: Matrix::identity(),
        } 
    }

    pub fn set_transform(&mut self, m: &Matrix) {
        self.transform = m.clone();
    }
}

impl Object for Sphere {
    fn id(&self) -> u64 {
        self.id
    }

    fn origin(&self) -> Tuple {
        self.origin
    } 

    fn transform(&self) -> &Matrix {
        &self.transform
    }
}

impl Object for &Sphere {
    fn id(&self) -> u64 {
        self.id
    }

    fn origin(&self) -> Tuple {
        self.origin
    } 

    fn transform(&self) -> &Matrix {
        &self.transform
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn new() {
        let s1 = Sphere::new();
        let s2 = Sphere::new();

        assert_ne!(s1.id, s2.id);
        assert_eq!(s1.transform, Matrix::identity());
    }

    #[test]
    fn set_transform() {
        let mut s = Sphere::new();
        let t = Matrix::translation(2.0, 3.0, 4.0);
        s.set_transform(&t);

        assert_eq!(s.transform, t);
    }
}
