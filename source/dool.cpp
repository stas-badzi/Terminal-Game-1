#include "dool.hpp"

dool::dool() {}

dool::dool(__int8 val) {
	d[0] = (val == 0);
	d[1] = (val > 0);
}

void dool::operator=(__int8 val) {
	d[0] = (val == 0);
	d[1] = (val > 0);
}
