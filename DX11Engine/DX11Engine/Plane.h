#pragma once

#ifndef PLANECLASS
#define PLANECLASS
#include "Model.h"
class Plane :
    public Model
{

public:

    bool initialize(ID3D11Device*);
};

#endif