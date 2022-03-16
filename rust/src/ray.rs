use crate::{
    tuple::Tuple,
    sphere::Sphere,
    sphere::Object,
};

pub struct Ray {
    origin: Tuple,
    direction: Tuple,
}

pub struct Intersection<T> {
    pub t: f64,
    pub object: T,
}

impl<T> Intersection<T> {
    pub fn new(t: f64, object: T) -> Self {
        Self {
            t,
            object
        }
    }

    pub fn intersections(i1: Self, i2: Self) -> Vec<Self> {
        vec![i1, i2]
    }
}

impl Ray {
    pub fn new(origin: Tuple, direction: Tuple) -> Ray {
        // TODO
        // Perform some kind of validation to ensure origin is a point and direction is a vector
        // OR rework tuples to have an explicit Point and Vector types
        Ray {
            origin,
            direction,
        }
    }

    pub fn position(&self, t: f64) -> Tuple {
        self.origin + (self.direction * t) 
    }


    pub fn intersect<'a, T>(&self, t: &'a T) -> Vec<Intersection<&'a T>> 
    where
        T: Object,
    {
        let sphere_to_ray = self.origin - t.origin(); 
        let a = self.direction.dot(&self.direction);
        let b = 2_f64 * self.direction.dot(&sphere_to_ray);
        let c = sphere_to_ray.dot(&sphere_to_ray) - 1.0;

        let disc = (b * b) - (4_f64 * a * c);

        let mut xs: Vec<Intersection<&T>> = vec![];

        if disc < 0.0 {
            return xs;
        }

        xs.push(Intersection::new((-b - disc.sqrt()) / (2_f64 * a), &t));
        xs.push(Intersection::new((-b + disc.sqrt()) / (2_f64 * a), &t));

        xs
    }

}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn new() {
        let p = Tuple::point(1.0, 2.0, 3.0);
        let v = Tuple::vector(4.0, 5.0, 6.0);

        let r = Ray::new(p, v);
        assert_eq!(r.origin, p);
        assert_eq!(r.direction, v);
    }

    #[test]
    fn position() {
        let r = Ray::new(Tuple::point(2.0, 3.0, 4.0), Tuple::vector(1.0, 0.0, 0.0));
        assert_eq!(r.position(0.0) , Tuple::point(2.0, 3.0, 4.0));
        assert_eq!(r.position(1.0) , Tuple::point(3.0, 3.0, 4.0));
        assert_eq!(r.position(-1.0), Tuple::point(1.0, 3.0, 4.0));
        assert_eq!(r.position(2.5) , Tuple::point(4.5, 3.0, 4.0));
    }
    
    #[test]
    fn ray_intersect_sphere() {
        let r = Ray::new(Tuple::point(0.0, 0.0, -5.0), Tuple::vector(0.0, 0.0, 1.0));        
        let s = Sphere::new();

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, 4.0);
        assert_eq!(xs[1].t, 6.0);
    }

    #[test]
    fn ray_tangent_sphere() {
        let r = Ray::new(Tuple::point(0.0, 1.0, -5.0), Tuple::vector(0.0, 0.0, 1.0));        
        let s = Sphere::new();

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, 5.0);
        assert_eq!(xs[1].t, 5.0);
    }

    #[test]
    fn ray_miss_sphere() {
        let r = Ray::new(Tuple::point(0.0, 2.0, -5.0), Tuple::vector(0.0, 0.0, 1.0));        
        let s = Sphere::new();

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 0);
    }

    #[test]
    fn ray_originates_in_sphere() {
        let r = Ray::new(Tuple::point(0.0, 0.0, 0.0), Tuple::vector(0.0, 0.0, 1.0));        
        let s = Sphere::new();

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, -1.0);
        assert_eq!(xs[1].t, 1.0);
    }

    #[test]
    fn ray_behind_sphere() {
        let r = Ray::new(Tuple::point(0.0, 0.0, 5.0), Tuple::vector(0.0, 0.0, 1.0));        
        let s = Sphere::new();

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, -6.0);
        assert_eq!(xs[1].t, -4.0);
    }

    #[test]
    fn intersection() {
        let s = Sphere::new();
        let i = Intersection::new(3.5, &s);

        assert_eq!(i.t, 3.5);
        assert_eq!(i.object.id, s.id);
    }

    #[test]
    fn aggregating_intersections() {
        let s = Sphere::new();
        let i1 = Intersection::new(1.0, &s);
        let i2 = Intersection::new(2.0, &s);

        let xs = Intersection::intersections(i1, i2);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, 1.0);
        assert_eq!(xs[1].t, 2.0);
    }
}
