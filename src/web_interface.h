#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H
#include "model.h"
void reset_webpage();
void update_webpage(int x_quasi, int y_quasi, int pointsInside_quasi, int pointsOutside_quasi, double pi_quasi, int x_pseudo, int y_pseudo, int pointsInside_pseudo, int pointsOutside_pseudo, double pi_pseudo);
#endif