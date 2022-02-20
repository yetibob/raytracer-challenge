use std::{
    ops,
    cmp::Eq,
    cmp::PartialEq,
};

use crate::tuple::Tuple;

// TODO Is there a way to make data an array of size dim x dim?
#[derive(Debug)]
pub struct Matrix {
    pub size: usize,
    pub data: Vec<Vec<f64>>
}

impl Matrix {
    pub fn IDENTITY() -> Matrix {
        Matrix {
            size: 4,
            data: vec![vec![1.0, 0.0, 0.0, 0.0], vec![0.0, 1.0, 0.0, 0.0], vec![0.0, 0.0, 1.0, 0.0], vec![0.0, 0.0, 0.0, 1.0]],
        }
    }

    pub fn transpose(&self) -> Matrix {
        let mut m = Matrix {
            size: 4,
            data: vec![vec![0.0, 0.0, 0.0, 0.0]; 4],
        };

        for row in 0..self.size {
            for col in 0..self.size {
                m.data[col][row] = self.data[row][col];
            }
        }

        m
    }
}

impl PartialEq for Matrix {
    fn eq(&self, oth: &Self) -> bool {
        if self.size != oth.size {
            return false;
        }

        for i in 0..self.size {
            for j in 0..self.size {
                if (self.data[i][j] - oth.data[i][j]).abs() >= f64::EPSILON {
                    return false;
                }
            }
        }

        true
    }
}

impl Eq for Matrix {}

// TODO
// Figure out best way to overload multiplication operator
// Want to be able to do m*m now &m * &m
// However that requires implementing Copy for Vecs 
impl ops::Mul for &Matrix {
    type Output = Matrix;

    fn mul(self, rhs: Self) -> Self::Output {
        // We won't be multiplying matrices with a size other than 4
        // Just return a dud matrix in any other case
        if self.size != 4 && self.size != rhs.size {
            return Matrix {
               size: 0,
               data: vec![],
            };
        }

        let mut v = vec![vec![0.0, 0.0, 0.0, 0.0]; 4];

        for row in 0..4 {
            for col in 0..4 {
               v[row][col] =   self.data[row][0] * rhs.data[0][col]
                             + self.data[row][1] * rhs.data[1][col]
                             + self.data[row][2] * rhs.data[2][col]
                             + self.data[row][3] * rhs.data[3][col];
            }
        }
        
        Matrix {
            size: self.size, 
            data: v,
        }
    }
}

impl ops::Mul<&Tuple> for &Matrix {
    type Output = Tuple;

    fn mul(self, rhs: &Tuple) -> Self::Output {
        let mut t = Tuple::ZERO();

        for row in 0..4 {
            let mut result = 0.0;
            for col in 0..4 {
               result +=   self.data[row][col] * rhs[col]
            }
            t[row] = result;
        }
        t
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn create() {
        let m = Matrix {
            size: 4,
            data: vec![vec![1.0, 2.0, 3.0, 4.0], vec![5.5, 6.5, 7.5, 8.5], vec![9.0, 10.0, 11.0, 12.0], vec![13.5, 14.5, 15.5, 16.5]]
        };
    
        assert_eq!(m.data[0][0], 1.0);
        assert_eq!(m.data[0][3], 4.0);
        assert_eq!(m.data[1][0], 5.5);
        assert_eq!(m.data[1][2], 7.5);
        assert_eq!(m.data[2][2], 11.0);
        assert_eq!(m.data[3][0], 13.5);
        assert_eq!(m.data[3][2], 15.5);
    }

    #[test]
    fn compare() {
        let m1 = Matrix {
            size: 2,
            data: vec![vec![1.0, 2.0], vec![3.0, 4.0]],
        };

        let m2 = Matrix {
            size: 2,
            data: vec![vec![1.0, 2.0], vec![3.0, 4.0]],
        };

        assert_eq!(m1, m2);
    }

    #[test]
    fn multiply_by_matrix() {
        let m1 = Matrix {
            size: 4,
            data: vec![vec![1.0, 2.0, 3.0, 4.0], vec![5.0, 6.0, 7.0, 8.0], vec![9.0, 8.0, 7.0, 6.0], vec![5.0, 4.0, 3.0, 2.0]],
        };

        let m2 = Matrix {
            size: 4,
            data: vec![vec![-2.0, 1.0, 2.0, 3.0], vec![3.0, 2.0, 1.0, -1.0], vec![4.0, 3.0, 6.0, 5.0], vec![1.0, 2.0, 7.0, 8.0]],
        };

        let exp = Matrix {
            size: 4,
            data: vec![vec![20.0, 22.0, 50.0, 48.0], vec![44.0, 54.0, 114.0, 108.0], vec![40.0, 58.0, 110.0, 102.0], vec![16.0, 26.0, 46.0, 42.0]],
        };

        assert_eq!(&m1*&m2, exp);
    }

    #[test]
    fn multiply_by_tuple() {
        let m = Matrix {
            size: 4,
            data: vec![vec![1.0, 2.0, 3.0, 4.0], vec![2.0, 4.0, 4.0, 2.0], vec![8.0, 6.0, 4.0, 1.0], vec![0.0, 0.0, 0.0, 1.0]],
        };

        let t = Tuple::new(1.0, 2.0, 3.0, 1.0);

        let exp = Tuple::new(18.0, 24.0, 33.0, 1.0);

        assert_eq!(&m*&t, exp);
    }

    #[test]
    fn multiple_by_identity() {
        let m = Matrix {
            size: 4,
            data: vec![vec![0.0, 1.0, 2.0, 4.0], vec![1.0, 2.0, 4.0, 8.0], vec![2.0, 4.0, 8.0, 16.0], vec![4.0, 8.0, 16.0, 32.0]]
        };

        assert_eq!(&m * &Matrix::IDENTITY(), m);
    }

    #[test]
    fn multiple_tuple_by_identity() {
        let t = Tuple::new(1.0, 2.0, 3.0, 4.0);

        assert_eq!(&Matrix::IDENTITY() * &t, t);
    }

    #[test]
    fn transpose() {
        let m = Matrix {
            size: 4,
            data: vec![vec![0.0, 9.0, 3.0, 0.0], vec![9.0, 8.0, 0.0, 8.0], vec![1.0, 8.0, 5.0, 3.0], vec![0.0, 0.0, 5.0, 8.0]],
        };

        let exp = Matrix {
            size: 4,
            data: vec![vec![0.0, 9.0, 1.0, 0.0], vec![9.0, 8.0, 8.0, 0.0], vec![3.0, 0.0, 5.0, 5.0], vec![0.0, 8.0, 3.0, 8.0]],
        };

        assert_eq!(m.transpose(), exp);
        assert_eq!(Matrix::IDENTITY().transpose(), Matrix::IDENTITY());
    }
}
