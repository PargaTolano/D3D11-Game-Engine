cbuffer MVP : register(b0)
{
	matrix m_World;
	matrix m_View;
	matrix m_ProjectedView;
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
	float3 wpos  : COLOR0;
	float4 clip  : COLOR1;
	float4 viewposition :COLOR2;
	float3 nrm   : NORMAL;
	float2 tex   : TEXCOORD;
};

PSIN vert(VSIN IN)
{
	PSIN OUT;

	OUT.clip = OUT.pos = mul(IN.pos, m_World);
	OUT.wpos = mul(IN.pos, m_World);
	OUT.pos = mul(OUT.pos, m_View);
	OUT.pos = mul(OUT.pos, m_Proj);

	OUT.clip = mul(OUT.clip, m_ProjectedView);
	OUT.clip = mul(OUT.clip, m_Proj);

	OUT.nrm = mul(IN.nrm, m_World);

	OUT.viewposition = mul(float4(0,0,-2,1), m_World);
	OUT.viewposition = mul(OUT.viewposition, m_View);
	OUT.viewposition = mul(OUT.viewposition, m_Proj);

	OUT.tex = IN.tex;

	return OUT;
}

struct point_light
{
	float3 wpos;
	float  radius;
	float  falloff_start;
};

float4 pix(PSIN IN) : SV_TARGET
{
	float4 OUT;

	point_light p;
	p.wpos = float3(0, 0, -1);
	p.radius = 3;
	p.falloff_start = 0;

	float4 ndc = IN.clip / IN.clip.w;

	float4 texture_sample = t_color.Sample(s_sampler, ndc.xy/ 2.0f + 0.5f);

	OUT = texture_sample;

	return OUT;
}