# IMPROVEMENTS
## Tuples
Tuples should probably have a data member similar to Matrix for storing its info. This would simplify the indexing code

## Matrix
Make matrixes indexable by simply making the index return m.data[idx]


## General
Matrix and tuple multiplication is currently awful to work with because Mul wants to take ownership so we are forced to implement it for references
This makes things like chaining (and just general usage) unwieldy. Figure out how to support the multiplication operator `*` without references but without taking ownership
OR implement a basic method such as Matrix::mul or some equivalent

Learning about lifetimes might be helpful here
