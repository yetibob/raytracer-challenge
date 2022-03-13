use crate::{
    tuple::Tuple,
};

pub trait Object {
    fn origin(&self) -> Tuple;
}

pub struct Sphere {
    pub id: u64,
    pub origin: Tuple,
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
        } 
    }
}

impl Object for Sphere {
    fn origin(&self) -> Tuple {
        self.origin
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
    }
}
