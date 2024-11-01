#pragma once

#include "Serpentine.h"
#include "imgs.h"
#include "net/ColorSpaces.h"
#include "net/ISender.h"

using namespace NetDriver;

void squareRainbow(const ISender& net);
void flyingParrot(const ISender& net, bool rainbow = false);
