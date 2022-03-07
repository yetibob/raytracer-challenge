use std::fs;

use rust::matrix::Matrix;

fn main() {
    let m = Matrix::IDENTITY();
    let m2 = m.inverse().unwrap();
    println!("M: {:?}", m);
    println!("M: {:?}", m2);

    let m3 = Matrix {
        size: 4,
        data: vec![vec![1.0, 3.0, 3.0, 7.0], vec![2.0, 7.0, 4.0, 5.0], vec![1.0, 4.0, 5.0, 6.0], vec![9.0, 7.0, 122.0, 9.0]],
    };
    
    let m4 = m3.inverse().unwrap();

    println!("M3: {:?}", m3);
    println!("M4: {:?}", m4);
    println!("M3*M4: {:?}", &m3 * &m4);
}
