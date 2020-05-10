#include "size.hh"
#include "Vector.cpp"

/*******************************************
 Template compilation for double and _SIZE_
********************************************/
template class Vector<double, _SIZE_>;
template std::ostream &operator<<(std::ostream &strm, const Vector<double, _SIZE_> &V);
template std::istream &operator>>(std::istream &strm, Vector<double, _SIZE_> &V);

