#pragma once
#ifndef CUBECLASS
#define CUBECLASS

#include "Model.h"
class Cube :
    public Model
{
public:

    bool initialize(ID3D11Device*);
};

#endif
