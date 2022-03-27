use std::cmp::PartialEq;

use crate::{
    tuple::Tuple,
    sphere::Object,
    matrix::Matrix,
};

#[derive(Debug)]
pub struct Ray {
    origin: Tuple,
    direction: Tuple,
}

// TODO:
// Limit intersection to only contains objects that implement Object instead of enforcing it in
// function args
#[derive(Debug)]
pub struct Intersection<T> {
    pub t: f64,
    pub object: T,
}

impl<T> PartialEq for Intersection<T> 
where T: Object
{
    fn eq(&self, oth: &Self) -> bool {
        self.t == oth.t && self.object.id() == oth.object.id()
    }
}

impl<T> Intersection<T> {
    pub fn new(t: f64, object: T) -> Self {
        Self {
            t,
            object
        }
    }

    // TODO
    // Holy References Batman. Figure out if this stuff can be restructured
    pub fn intersections(mut xs: Vec<&Self>) -> Vec<&Self> {
        xs.sort_unstable_by(|a, b| a.t.partial_cmp(&b.t).unwrap());
        xs
    }

    pub fn hit<'a>(xs: &'a Vec<&Self>) -> Option<&'a Self> {
        for i in xs {
            if i.t > 0.0 {
                return Some(i);
            }
        }

        None
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

        let transformed_self = self.transform(&t.transform().inverse());

        let sphere_to_ray = transformed_self.origin - t.origin(); 
        let a = transformed_self.direction.dot(&transformed_self.direction);
        let b = 2_f64 * transformed_self.direction.dot(&sphere_to_ray);
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

    pub fn transform(&self, m: &Matrix) -> Ray {
        let origin = self.origin * m;
        let direction = self.direction * m;
        Ray::new(origin, direction)
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::sphere::Sphere;

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
    fn hit_when_all_positive() {
        let s = Sphere::new();
        let i1 = Intersection::new(1.0, &s);
        let i2 = Intersection::new(2.0, &s);

        let xs = Intersection::intersections(vec![&i2, &i1]);
        let i = Intersection::hit(&xs).unwrap();

        assert_eq!(*i, i1);
    }

    #[test]
    fn hit_when_some_negative() {
        let s = Sphere::new();
        let i1 = Intersection::new(-1.0, &s);
        let i2 = Intersection::new(1.0, &s);

        let xs = Intersection::intersections(vec![&i2, &i1]);
        let i = Intersection::hit(&xs).unwrap();

        assert_eq!(*i, i2);
    }

    #[test]
    fn hit_when_all_negative() {
        let s = Sphere::new();
        let i1 = Intersection::new(-2.0, &s);
        let i2 = Intersection::new(-1.0, &s);

        let xs = Intersection::intersections(vec![&i1, &i2]);
        let i = Intersection::hit(&xs);

        assert!(i.is_none());
    }

    #[test]
    fn hit_is_always_lowest_non_negative_intersection() {
        let s = Sphere::new();
        let i1 = Intersection::new(5.0, &s);
        let i2 = Intersection::new(7.0, &s);
        let i3 = Intersection::new(-3.0, &s);
        let i4 = Intersection::new(2.0, &s);

        let xs = Intersection::intersections(vec![&i1, &i2, &i3, &i4]);
        let i = Intersection::hit(&xs).unwrap();

        assert_eq!(*i, i4);
    }

    #[test]
    fn translate_ray() {
        let r = Ray::new(Tuple::point(1.0, 2.0, 3.0), Tuple::vector(0.0, 1.0, 0.0));
        let m = Matrix::translation(3.0, 4.0, 5.0);
        let r2 = r.transform(&m);
        assert_eq!(r2.origin, Tuple::point(4.0, 6.0, 8.0));
        assert_eq!(r2.direction, Tuple::vector(0.0, 1.0, 0.0));
    }

    #[test]
    fn scale_ray() {
        let r = Ray::new(Tuple::point(1.0, 2.0, 3.0), Tuple::vector(0.0, 1.0, 0.0));
        let m = Matrix::scaling(2.0, 3.0, 4.0);
        let r2 = r.transform(&m);
        assert_eq!(r2.origin, Tuple::point(2.0, 6.0, 12.0));
        assert_eq!(r2.direction, Tuple::vector(0.0, 3.0, 0.0));
    }

    #[test]
    fn intersecting_scaled_sphere() {
        let r = Ray::new(Tuple::point(0.0, 0.0, -5.0), Tuple::vector(0.0, 0.0, 1.0));
        let mut s = Sphere::new();
        s.set_transform(&Matrix::scaling(2.0, 2.0, 2.0));

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 2);
        assert_eq!(xs[0].t, 3.0);
        assert_eq!(xs[1].t, 7.0);
    }

    #[test]
    fn intersecting_translated_sphere() {
        let r = Ray::new(Tuple::point(0.0, 0.0, -5.0), Tuple::vector(0.0, 0.0, 1.0));
        let mut s = Sphere::new();
        s.set_transform(&Matrix::translation(5.0, 0.0, 0.0));

        let xs = r.intersect(&s);
        assert_eq!(xs.len(), 0);
    }
}
