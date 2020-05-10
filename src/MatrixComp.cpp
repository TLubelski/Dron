#include "size.hh"
#include "Matrix.cpp"

/*******************************************
 Template compilation for double and _SIZE_
********************************************/
template class Matrix<double, _SIZE_>;
template std::ostream &operator<<(std::ostream &strm, const Matrix<double, _SIZE_> &M);
template std::istream &operator>>(std::istream &strm, Matrix<double, _SIZE_> &M);

