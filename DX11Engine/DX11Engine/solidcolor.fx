cbuffer MVP : register(b0)
{
	matrix m_World;
	matrix m_View;
	matrix m_Proj;
};

cbuffer color : register(b1)
{
	float4 color;
}

struct VSIN {
	float4 pos : POSITION;
	float3 nrm : NORMAL;
	float3 tg  : TANGENT;
	float3 bn  : BINORMAL;
	float2 tex : TEXCOORD0;
};

struct PSIN {
	float4 pos	 : SV_POSITION;
	float4 color : COLOR0;
};

PSIN vert(VSIN IN)
{
	PSIN OUT;

	OUT.pos = mul( IN.pos, m_World);
	OUT.pos = mul(OUT.pos, m_View);
	OUT.pos = mul(OUT.pos, m_Proj);

	OUT.color = color;

	return OUT;
}

float4 pix(PSIN IN) : SV_TARGET
{
	float4 OUT;

	OUT = IN.color;

	return OUT;
}