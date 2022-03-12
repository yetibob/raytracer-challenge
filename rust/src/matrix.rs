use std::{
    ops,
    cmp::Eq,
    cmp::PartialEq,
};

use crate::tuple::Tuple;

const EPSILON: f64 = 0.00001;

// TODO Is there a way to make data an array of size dim x dim?
#[derive(Debug)]
pub struct Matrix {
    pub size: usize,
    pub data: Vec<Vec<f64>>
}

impl Matrix {
    pub fn zero(size: usize) -> Matrix {
        Matrix {
            size,
            data: vec![vec![0.0; size]; size],
        }
    }

    pub fn identity() -> Matrix {
        Matrix {
            size: 4,
            data: vec![vec![1.0, 0.0, 0.0, 0.0], vec![0.0, 1.0, 0.0, 0.0], vec![0.0, 0.0, 1.0, 0.0], vec![0.0, 0.0, 0.0, 1.0]],
        }
    }

    pub fn translation() -> Matrix {
        Matrix {
            size: 4,
            data: vec![],
        }
    }

    pub fn transpose(&self) -> Matrix {
        let mut m = Matrix {
            size: self.size,
            data: vec![vec![0.0; self.size]; self.size],
        };

        for row in 0..self.size {
            for col in 0..self.size {
                m.data[col][row] = self.data[row][col];
            }
        }

        m
    }

    pub fn determinant(&self) -> f64 {
        match self.size {
            2 => self.data[0][0] * self.data[1][1] - self.data[0][1] * self.data[1][0],
            _ => {
                let mut det = 0.0;
                for col in 0..self.size {
                    det += self.data[0][col] * self.cofactor(0, col);
                }
                det
            },
        }
    }

    pub fn submatrix(&self, row: usize, col: usize) -> Matrix {
        let mut m = Matrix::zero(self.size - 1);

        let mut r = 0;
        let mut c = 0;
        for i in 0..m.size {
            if i == row {
                r += 1;
            }
            for j in 0..m.size {
                if j == col {
                    c += 1;
                }
                m.data[i][j] = self.data[r][c];
                c += 1;
            }
            c = 0;
            r += 1;
        }

        m
    }

    pub fn minor(&self, row: usize, col: usize) -> f64 {
        self.submatrix(row, col).determinant()
    }

    pub fn cofactor(&self, row: usize, col: usize) -> f64 {
        let mut res = self.minor(row, col);
        if (row + col) % 2 == 1 {
            res = -res;
        }

        res
    }
    
    pub fn inverse(&self) -> Option<Matrix> {
        if self.determinant() == 0.0 {
            return None;
        }

        let mut m = Matrix::zero(self.size);

        for row in 0..m.size {
            for col in 0..m.size {
                let c = self.cofactor(row, col);
                m.data[col][row] = c / self.determinant();
            }
        }

        Some(m)
    }
}

impl PartialEq for Matrix {
    fn eq(&self, oth: &Self) -> bool {
        if self.size != oth.size {
            return false;
        }

        for i in 0..self.size {
            for j in 0..self.size {
                if (self.data[i][j] - oth.data[i][j]).abs() >= EPSILON {
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
// Want to be able to do m*m not &m * &m
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
        let mut t = Tuple::zero();

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

        assert_eq!(&m * &Matrix::identity(), m);
    }

    #[test]
    fn multiple_tuple_by_identity() {
        let t = Tuple::new(1.0, 2.0, 3.0, 4.0);

        assert_eq!(&Matrix::identity() * &t, t);
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
        assert_eq!(Matrix::identity().transpose(), Matrix::identity());
    }

    #[test]
    fn determinant() {
        let m = Matrix {
            size: 2,
            data: vec![vec![1.0, 5.0], vec![-3.0, 2.0]],
        };

        assert_eq!(m.determinant(), 17.0);
    }

    #[test]
    fn submatrix_of_3_is_2() {
        let m = Matrix {
            size: 3,
            data: vec![vec![1.0, 5.0, 0.0], vec![-3.0, 2.0, 7.0], vec![0.0, 6.0, -3.0]],
        };

        let exp = Matrix {
            size: 2,
            data: vec![vec![-3.0, 2.0], vec![0.0, 6.0]],
        };

        assert_eq!(m.submatrix(0, 2), exp);
    }

    #[test]
    fn submatrix_of_4_is_3() {
        let m = Matrix {
            size: 4,
            data: vec![vec![-6.0, 1.0, 1.0, 6.0], vec![-8.0, 5.0, 8.0, 6.0], vec![-1.0, 0.0, 8.0, 2.0], vec![-7.0, 1.0, -1.0, 1.0]],
        };

        let exp = Matrix {
            size: 3,
            data: vec![vec![-6.0, 1.0, 6.0], vec![-8.0, 8.0, 6.0], vec![-7.0, -1.0, 1.0]],
        };

        assert_eq!(m.submatrix(2, 1), exp);
    }

    #[test]
    fn minor() {
        let m = Matrix {
            size: 3,
            data: vec![vec![3.0, 5.0, 0.0], vec![2.0, -1.0, -7.0], vec![6.0, -1.0, 5.0]],
        };
        assert_eq!(m.submatrix(1, 0).determinant(), 25.0);
        assert_eq!(m.minor(1, 0), 25.0);
    }

    #[test]
    fn cofactor() {
        let m = Matrix {
            size: 3,
            data: vec![vec![3.0, 5.0, 0.0], vec![2.0, -1.0, -7.0], vec![6.0, -1.0, 5.0]],
        };

        assert_eq!(m.minor(0, 0), -12.0);
        assert_eq!(m.cofactor(0, 0), -12.0);

        assert_eq!(m.minor(1, 0), 25.0);
        assert_eq!(m.cofactor(1, 0), -25.0);
    }

    #[test]
    fn determinant_3x3() {
        let m = Matrix {
            size: 3,
            data: vec![vec![1.0, 2.0, 6.0], vec![-5.0, 8.0, -4.0], vec![2.0, 6.0, 4.0]],
        };

        assert_eq!(m.cofactor(0, 0), 56.0);
        assert_eq!(m.cofactor(0, 1), 12.0);
        assert_eq!(m.cofactor(0, 2), -46.0);
        assert_eq!(m.determinant(), -196.0);
    }

    #[test]
    fn determinant_4x4() {
        let m = Matrix {
            size: 4,
            data: vec![vec![-2.0, -8.0, 3.0, 5.0], vec![-3.0, 1.0, 7.0, 3.0], vec![1.0, 2.0, -9.0, 6.0], vec![-6.0, 7.0, 7.0, -9.0]],
        };

        assert_eq!(m.cofactor(0, 0), 690.0);
        assert_eq!(m.cofactor(0, 1), 447.0);
        assert_eq!(m.cofactor(0, 2), 210.0);
        assert_eq!(m.cofactor(0, 3), 51.0);
        assert_eq!(m.determinant(), -4071.0);
    }

    #[test]
    fn is_invertible() {
        let m = Matrix {
            size: 4,
            data: vec![vec![6.0, 4.0, 4.0, 4.0], vec![5.0, 5.0, 7.0, 6.0], vec![4.0, -9.0, 3.0, -7.0], vec![9.0, 1.0, 7.0, -6.0]]
        };

        assert!(!m.inverse().is_none());
    }

    #[test]
    fn is_not_invertible() {
        let m = Matrix {
            size: 4,
            data: vec![vec![-4.0, 2.0, -2.0, -3.0], vec![9.0, 6.0, 2.0, 6.0], vec![0.0, -5.0, 1.0, -5.0], vec![0.0, 0.0, 0.0, 0.0]]
        };

        assert!(m.inverse().is_none());
    }

    #[test]
    fn inverse() {
        let m = Matrix {
            size: 4,
            data: vec![vec![-5.0, 2.0, 6.0, -8.0], vec![1.0, -5.0, 1.0, 8.0], vec![7.0, 7.0, -6.0, -7.0], vec![1.0, -3.0, 7.0, 4.0]],
        };

        let inv = m.inverse().unwrap();

        let exp = Matrix {
            size: 4,
            data: vec![vec![0.21805, 0.45113, 0.24060, -0.04511], vec![-0.80827, -1.45677, -0.44361, 0.52068], vec![-0.07895, -0.22368, -0.05263, 0.19737], vec![-0.52256, -0.81391, -0.30075, 0.30639]],
        };

        assert_eq!(m.determinant(), 532.0);
        assert_eq!(m.cofactor(2, 3), -160.0);
        assert_eq!(inv.data[3][2], -160.0 / 532.0);
        assert_eq!(m.cofactor(3, 2), 105.0);
        assert_eq!(inv.data[2][3], 105.0 / 532.0);
        assert_eq!(inv, exp);
    }

    #[test]
    fn inverse_more() {
        let m = Matrix {
            size: 4,
            data: vec![vec![8.0, -5.0, 9.0, 2.0], vec![7.0, 5.0, 6.0, 1.0], vec![-6.0, 0.0, 9.0, 6.0], vec![-3.0, 0.0, -9.0, -4.0]],
        };

        let inv = m.inverse().unwrap();

        let exp = Matrix {
            size: 4,
            data: vec![vec![-0.15385, -0.15385, -0.28205, -0.53846], vec![-0.07692, 0.12308, 0.02564, 0.03077], vec![0.35897, 0.35897, 0.43590, 0.92308], vec![-0.69231, -0.69231, -0.76923, -1.92308]],
        };

        assert_eq!(inv, exp);

        let m2 = Matrix {
            size: 4,
            data: vec![vec![9.0, 3.0, 0.0, 9.0], vec![-5.0, -2.0, -6.0, -3.0], vec![-4.0, 9.0, 6.0, 4.0], vec![-7.0, 6.0, 6.0, 2.0]],
        };

        let inv2 = m2.inverse().unwrap();

        let exp2 = Matrix {
            size: 4,
            data: vec![vec![-0.04074, -0.07778, 0.14444, -0.22222], vec![-0.07778, 0.03333, 0.36667, -0.33333], vec![-0.02901, -0.14630, -0.10926, 0.12963], vec![0.17778, 0.06667, -0.26667, 0.33333]],
        };

        assert_eq!(inv2, exp2);
    }

    #[test]
    fn product_by_inverse() {
        let m = Matrix {
            size: 4,
            data: vec![vec![3.0, -9.0, 7.0, 3.0], vec![3.0, -8.0, 2.0, -9.0], vec![-4.0, 4.0, 4.0, 1.0], vec![-6.0, 5.0, -1.0, 1.0]],
        };

        let m2 = Matrix {
            size: 4,
            data: vec![vec![8.0, 2.0, 2.0, 2.0], vec![3.0, -1.0, 7.0, 0.0], vec![7.0, 0.0, 5.0, 4.0], vec![6.0, -2.0, 0.0, 5.0]],
        };

        let m3 = &m * &m2;
        assert_eq!(&m3 * &m2.inverse().unwrap(), m);
    }
}
