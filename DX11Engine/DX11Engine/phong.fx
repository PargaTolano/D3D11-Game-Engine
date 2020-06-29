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
	float3 wpos  : COLOR0;
	float3 nrm   : NORMAL;
	float2 tex   : TEXCOORD;
};

PSIN vert(VSIN IN)
{
	PSIN OUT;

	OUT.pos = mul(IN.pos, m_World);
	OUT.wpos = mul(IN.pos, m_World);
	OUT.pos = mul(OUT.pos, m_View);
	OUT.pos = mul(OUT.pos, m_Proj);

	OUT.nrm = mul(IN.nrm, m_World);

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

	float4 texture_sample = t_color.Sample(s_sampler, IN.tex);

	//ambient
	float4 ambient = float4 (0.1, 0.1, 0.1,1);
	
	//diffuse
	float lambert = saturate(dot(p.wpos, IN.nrm));

	//specular
	float3 camposition = float3(0, 0, -2);
	float4 specularColor = float4(1, 1, 1, 1);

	float3 cameravector = camposition - IN.wpos;
	float3 lightvector  = p.wpos      - IN.wpos;

	float3 reflectDir = reflect(-lightvector, IN.nrm);
	
	float  similarity = pow(saturate(dot(cameravector, reflectDir)), 2);

	OUT = texture_sample * saturate(ambient + lambert + specularColor * similarity);

	return OUT;
}