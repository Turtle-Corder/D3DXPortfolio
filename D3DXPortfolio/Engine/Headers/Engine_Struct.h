#pragma once
#ifndef __ENGINE_STRUCT_H__
#define __ENGINE_STRUCT_H__





//----------------------------------------------------------------------------------------------------
// 버텍스 버퍼
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 단순 색상
//--------------------------------------------------
typedef struct tagVertexColor
{
	_vec3	vPosition;
	_uint	iColor;
} VTX_COLOR;

const _uint VTX_CLOLOR_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;


//--------------------------------------------------
// 평면 텍스처
//--------------------------------------------------
typedef struct tagVertexTexture
{
	_vec3	vPosition;
	_vec3	vNormal;
	_vec2	vUV;
} VTX_TEXTURE;

const _uint VTX_TEXTURE_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;


//--------------------------------------------------
// 큐브 텍스처
//--------------------------------------------------
typedef struct tagVertexCubeTexture
{
	_vec3	vPosition;
	_vec3	vUV;
} VTX_CUBETEXTURE;

const _uint VTX_CUBETEXTURE_FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);





//----------------------------------------------------------------------------------------------------
// 인덱스 버퍼
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 16비트용 (최대 65535)
//--------------------------------------------------
typedef struct tagIndex16
{
	_ushort	_1;
	_ushort _2;
	_ushort _3;
} INDEX16;


//--------------------------------------------------
// 32비트용
//--------------------------------------------------
typedef struct tagIndex32
{
	_ulong	_1;
	_ulong	_2;
	_ulong	_3;
} INDEX32;





#endif // !__ENGINE_STRUCT_H__
