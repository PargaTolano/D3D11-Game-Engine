cbuffer MVP : register(b0)
{
	matrix m_World;
	matrix m_View;
	matrix m_Proj;
};

Texture2D		t_color		:	register(t0);
SamplerState	s_sampler	:	register(s0);

struct VSIN {
	float4 pos : POSITION;
	float3 nrm : NORMAL;
	float3 tg  : TANGENT;
	float3 bn  : BINORMAL;
	float2 tex : TEXCOORD0;
};

struct PSIN {
	float4 pos	 : SV_POSITION;
	float2 tex   : TEXCOORD;
};

PSIN vert(VSIN IN)
{
	PSIN OUT;

	OUT.pos = mul(IN.pos, m_World);
	OUT.pos = mul(OUT.pos, m_View);
	OUT.pos = mul(OUT.pos, m_Proj);

	OUT.tex = IN.tex;

	return OUT;
}

float4 pix(PSIN IN) : SV_TARGET
{
	float4 OUT;

	OUT = t_color.Sample(s_sampler,IN.tex);

	return OUT;
}