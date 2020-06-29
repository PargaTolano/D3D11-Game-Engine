#include "Model.h"

Model::Model():
	b_vertex(0),
	b_index(0),
	pVert(0),
	pInd(0),
	u_v_count(0),
	u_i_count(0)
{

}

ID3D11Buffer*& Model::getVertexBuffer()
{
	return this->b_vertex;
}

ID3D11Buffer*& Model::getIndexBuffer()
{
	return this->b_index;
}

uint Model::getIndexCount()
{
	return u_i_count;
}

uint Model::getVertexCount()
{
	return u_v_count;
}