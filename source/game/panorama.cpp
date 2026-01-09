#include "game/panorama.hpp"

#include "3ds/gpu/enums.h"
#include "engine/debug.hpp"
#include "engine/time.hpp"

#include <citro2d.h>
#include <3ds.h>
#include <citro3d.h>
#include <string>
#include <tex3ds.h>
#include <string.h>
#include <array>
#include "vshader_shbin.h"

typedef struct { float position[3]; float texcoord[2]; float normal[3]; } vertex;
static std::array<vertex, 36> vertex_list = {{
  { {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} }, // BL
  { {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f} }, // BR
  { {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f} }, // TL
  { {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f} }, // BR
  { {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} }, // TR
  { {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f} }, // TL

  { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} }, // BL
  { {+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, +1.0f} }, // BR
  { {-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, +1.0f} }, // TL
  { {+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, +1.0f} }, // BR
  { {+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} }, // TR
  { {-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, +1.0f} }, // TL

  { {+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} }, // BL
  { {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} }, // BR
  { {+0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} }, // TL
  { {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} }, // BR
  { {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} }, // TR
  { {+0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} }, // TL

  { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} }, // BL
  { {-0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} }, // BR
  { {-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} }, // TL
  { {-0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} }, // BR
  { {-0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} }, // TR
  { {-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {+1.0f, 0.0f, 0.0f} }, // TL

  { {-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} }, // BL
  { {+0.5f, +0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f} }, // BR
  { {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f} }, // TL
  { {+0.5f, +0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f} }, // BR
  { {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} }, // TR
  { {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f} }, // TL

  { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, +1.0f, 0.0f} }, // BL
  { {+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, +1.0f, 0.0f} }, // BR
  { {-0.5f, -0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, +1.0f, 0.0f} }, // TL
  { {+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, +1.0f, 0.0f} }, // BR
  { {+0.5f, -0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, +1.0f, 0.0f} }, // TR
  { {-0.5f, -0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, +1.0f, 0.0f} }, // TL
}};

static DVLB_s* vshader_dvlb;
static shaderProgram_s program;
static int uLoc_projection, uLoc_modelView;
static C3D_Mtx projection;

static void* vbo_data;
C3D_BufInfo* bufInfo;
C3D_AttrInfo* attrInfo;
C3D_TexEnv* env;
static C3D_Tex pano_tex;
static float angleY = 00.0;

static bool loadTextureFromFile(const char* filename, Tex3DS_Texture* t3x, C3D_Tex* tex, C3D_TexCube* cube)
{
  FILE* f = fopen(filename, "rb");
	if (!f) return false;

	setvbuf(f, NULL, _IOFBF, 64*1024);
  *t3x = Tex3DS_TextureImportStdio(f, tex, cube, false);
	fclose(f);

	if (!t3x)	return false;
	return true;
}

void init_pano() { 

	vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
	C3D_BindProgram(&program);

	uLoc_projection   = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
	uLoc_modelView    = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");
	
	attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v1=texcoord
	AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // v2=normal

	Mtx_PerspTilt(&projection, C3D_AngleFromDegrees(80.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, false);

	vbo_data = linearAlloc(sizeof(vertex_list));
	memcpy(vbo_data, vertex_list.data(), sizeof(vertex_list));

	bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 3, 0x210);

  Tex3DS_Texture t3x{0};
	if (!loadTextureFromFile("romfs:/gfx/pano.t3x", &t3x, &pano_tex, NULL)) {
		svcBreak(USERBREAK_PANIC);
  }

  auto subTextureC = Tex3DS_GetNumSubTextures(t3x);
  for(size_t i = 0; i < subTextureC && i < vertex_list.size()/subTextureC;  i++) {
    auto* sub = Tex3DS_GetSubTexture(t3x, i);

    float u0 = sub->left;
    float v0 = sub->top;
    float u1 = sub->right;
    float v1 = sub->bottom;

    if (u0 > u1) std::swap(u0, u1);
    if (v0 > v1) std::swap(v0, v1);

    vertex_list[i*6 + 0].texcoord[0] = u0; vertex_list[i*6 + 0].texcoord[1] = v0;
    vertex_list[i*6 + 1].texcoord[0] = u1; vertex_list[i*6 + 1].texcoord[1] = v0;
    vertex_list[i*6 + 2].texcoord[0] = u0; vertex_list[i*6 + 2].texcoord[1] = v1;

    vertex_list[i*6 + 3].texcoord[0] = u1; vertex_list[i*6 + 3].texcoord[1] = v0;
    vertex_list[i*6 + 4].texcoord[0] = u1; vertex_list[i*6 + 4].texcoord[1] = v1;
    vertex_list[i*6 + 5].texcoord[0] = u0; vertex_list[i*6 + 5].texcoord[1] = v1;
  }
  Tex3DS_TextureFree(t3x);

	C3D_TexBind(0, &pano_tex);

	env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);
}

void render_pano() {
	C2D_Flush();

	C3D_BindProgram(&program);
  C3D_SetAttrInfo(attrInfo);
	C3D_SetBufInfo(bufInfo);
	BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 3, 0x210);
	C3D_TexBind(0, &pano_tex);

  env = C3D_GetTexEnv(4);
  C3D_TexEnvInit(env);
  C3D_TexEnvSrc(env, C3D_Both, GPU_PREVIOUS, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
  C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);

  env = C3D_GetTexEnv(5);
  C3D_TexEnvInit(env);
  C3D_TexEnvSrc(env, C3D_Both, GPU_PREVIOUS, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
  C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);

  C3D_DepthTest(true, GPU_GREATER, GPU_WRITE_ALL);
  C3D_TexSetWrap(&pano_tex, GPU_CLAMP_TO_EDGE, GPU_CLAMP_TO_EDGE);
  C3D_TexSetFilter(&pano_tex, GPU_NEAREST, GPU_NEAREST);

  env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

	C3D_Mtx modelView;
	Mtx_Identity(&modelView);
	Mtx_Translate(&modelView, 0.0, 0.0,0.0, true);
	Mtx_RotateY(&modelView, angleY, true);

  angleY += 0.01745329252 * Time::deltaTime;

	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelView,  &modelView);

	C3D_DrawArrays(GPU_TRIANGLES, 0, vertex_list.size());

  C2D_Prepare();
}

void deinit_pano() {
	C3D_TexDelete(&pano_tex);
	linearFree(vbo_data);
	shaderProgramFree(&program);
	DVLB_Free(vshader_dvlb);
}
