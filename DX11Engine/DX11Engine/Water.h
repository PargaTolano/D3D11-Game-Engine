#pragma once
#include "Model.h"
class Water :
    public Model
{
private:

    bool LoadMesh(uint side_lenght, uint divisions, uint uvTiles);
    bool LoadIndices(uint divisions);

public:

    Water(uint side_lenght, uint divisions, uint uvTiles);

    bool initialize(ID3D11Device*);
};

