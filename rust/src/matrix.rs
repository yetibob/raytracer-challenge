use std::cmp::Eq;
use std::cmp::PartialEq;

// TODO Is there a way to make data an array of size dim x dim?
#[derive(Debug)]
pub struct Matrix {
    size: usize,
    data: Vec<Vec<f64>>
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_matrix() {
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
    fn test_matrix_compare() {
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
}
