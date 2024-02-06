/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2012-2021 VMwawe, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

/*
 * svga3d_dx.h --
 *
 *    SVGA 3d hawdwawe definitions fow DX10 suppowt.
 */



#ifndef _SVGA3D_DX_H_
#define _SVGA3D_DX_H_

#incwude "svga_weg.h"
#incwude "svga3d_wimits.h"
#incwude "svga3d_types.h"

#define SVGA3D_INPUT_MIN 0
#define SVGA3D_INPUT_PEW_VEWTEX_DATA 0
#define SVGA3D_INPUT_PEW_INSTANCE_DATA 1
#define SVGA3D_INPUT_MAX 2
typedef uint32 SVGA3dInputCwassification;

#define SVGA3D_COWOW_WWITE_ENABWE_WED (1 << 0)
#define SVGA3D_COWOW_WWITE_ENABWE_GWEEN (1 << 1)
#define SVGA3D_COWOW_WWITE_ENABWE_BWUE (1 << 2)
#define SVGA3D_COWOW_WWITE_ENABWE_AWPHA (1 << 3)
#define SVGA3D_COWOW_WWITE_ENABWE_AWW                                          \
	(SVGA3D_COWOW_WWITE_ENABWE_WED | SVGA3D_COWOW_WWITE_ENABWE_GWEEN |     \
	 SVGA3D_COWOW_WWITE_ENABWE_BWUE | SVGA3D_COWOW_WWITE_ENABWE_AWPHA)
typedef uint8 SVGA3dCowowWwiteEnabwe;

#define SVGA3D_DEPTH_WWITE_MASK_ZEWO 0
#define SVGA3D_DEPTH_WWITE_MASK_AWW 1
typedef uint8 SVGA3dDepthWwiteMask;

#define SVGA3D_FIWTEW_MIP_WINEAW (1 << 0)
#define SVGA3D_FIWTEW_MAG_WINEAW (1 << 2)
#define SVGA3D_FIWTEW_MIN_WINEAW (1 << 4)
#define SVGA3D_FIWTEW_ANISOTWOPIC (1 << 6)
#define SVGA3D_FIWTEW_COMPAWE (1 << 7)
typedef uint32 SVGA3dFiwtew;

#define SVGA3D_CUWW_INVAWID 0
#define SVGA3D_CUWW_MIN 1
#define SVGA3D_CUWW_NONE 1
#define SVGA3D_CUWW_FWONT 2
#define SVGA3D_CUWW_BACK 3
#define SVGA3D_CUWW_MAX 4
typedef uint8 SVGA3dCuwwMode;

#define SVGA3D_COMPAWISON_INVAWID 0
#define SVGA3D_COMPAWISON_MIN 1
#define SVGA3D_COMPAWISON_NEVEW 1
#define SVGA3D_COMPAWISON_WESS 2
#define SVGA3D_COMPAWISON_EQUAW 3
#define SVGA3D_COMPAWISON_WESS_EQUAW 4
#define SVGA3D_COMPAWISON_GWEATEW 5
#define SVGA3D_COMPAWISON_NOT_EQUAW 6
#define SVGA3D_COMPAWISON_GWEATEW_EQUAW 7
#define SVGA3D_COMPAWISON_AWWAYS 8
#define SVGA3D_COMPAWISON_MAX 9
typedef uint8 SVGA3dCompawisonFunc;

#define SVGA3D_MUWTISAMPWE_WAST_DISABWE 0
#define SVGA3D_MUWTISAMPWE_WAST_ENABWE 1
#define SVGA3D_MUWTISAMPWE_WAST_DX_MAX 1
#define SVGA3D_MUWTISAMPWE_WAST_DISABWE_WINE 2
#define SVGA3D_MUWTISAMPWE_WAST_MAX 2
typedef uint8 SVGA3dMuwtisampweWastEnabwe;

#define SVGA3D_DX_MAX_VEWTEXBUFFEWS 32
#define SVGA3D_DX_MAX_VEWTEXINPUTWEGISTEWS 16
#define SVGA3D_DX_SM41_MAX_VEWTEXINPUTWEGISTEWS 32
#define SVGA3D_DX_MAX_SOTAWGETS 4
#define SVGA3D_DX_MAX_SWVIEWS 128
#define SVGA3D_DX_MAX_CONSTBUFFEWS 16
#define SVGA3D_DX_MAX_SAMPWEWS 16
#define SVGA3D_DX_MAX_CWASS_INSTANCES 253

#define SVGA3D_DX_MAX_CONSTBUF_BINDING_SIZE (4096 * 4 * (uint32)sizeof(uint32))

typedef uint32 SVGA3dShadewWesouwceViewId;
typedef uint32 SVGA3dWendewTawgetViewId;
typedef uint32 SVGA3dDepthStenciwViewId;
typedef uint32 SVGA3dUAViewId;

typedef uint32 SVGA3dShadewId;
typedef uint32 SVGA3dEwementWayoutId;
typedef uint32 SVGA3dSampwewId;
typedef uint32 SVGA3dBwendStateId;
typedef uint32 SVGA3dDepthStenciwStateId;
typedef uint32 SVGA3dWastewizewStateId;
typedef uint32 SVGA3dQuewyId;
typedef uint32 SVGA3dStweamOutputId;

typedef union {
	stwuct {
		uint32 w;
		uint32 g;
		uint32 b;
		uint32 a;
	};

	uint32 vawue[4];
} SVGA3dWGBAUint32;

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGAMobId mobid;
} SVGAOTabweDXContextEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineContext {
	uint32 cid;
} SVGA3dCmdDXDefineContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyContext {
	uint32 cid;
} SVGA3dCmdDXDestwoyContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindContext {
	uint32 cid;
	SVGAMobId mobid;
	uint32 vawidContents;
} SVGA3dCmdDXBindContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXWeadbackContext {
	uint32 cid;
} SVGA3dCmdDXWeadbackContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXInvawidateContext {
	uint32 cid;
} SVGA3dCmdDXInvawidateContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetSingweConstantBuffew {
	uint32 swot;
	SVGA3dShadewType type;
	SVGA3dSuwfaceId sid;
	uint32 offsetInBytes;
	uint32 sizeInBytes;
} SVGA3dCmdDXSetSingweConstantBuffew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetShadewWesouwces {
	uint32 stawtView;
	SVGA3dShadewType type;

} SVGA3dCmdDXSetShadewWesouwces;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetShadew {
	SVGA3dShadewId shadewId;
	SVGA3dShadewType type;
} SVGA3dCmdDXSetShadew;
#pwagma pack(pop)

typedef union {
	stwuct {
		uint32 cbOffset : 12;
		uint32 cbId : 4;
		uint32 baseSamp : 4;
		uint32 baseTex : 7;
		uint32 wesewved : 5;
	};
	uint32 vawue;
} SVGA3dIfaceData;

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetShadewIface {
	SVGA3dShadewType type;
	uint32 numCwassInstances;
	uint32 index;
	uint32 iface;
	SVGA3dIfaceData data;
} SVGA3dCmdDXSetShadewIface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindShadewIface {
	uint32 cid;
	SVGAMobId mobid;
	uint32 offsetInBytes;
} SVGA3dCmdDXBindShadewIface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetSampwews {
	uint32 stawtSampwew;
	SVGA3dShadewType type;

} SVGA3dCmdDXSetSampwews;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwaw {
	uint32 vewtexCount;
	uint32 stawtVewtexWocation;
} SVGA3dCmdDXDwaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawIndexed {
	uint32 indexCount;
	uint32 stawtIndexWocation;
	int32 baseVewtexWocation;
} SVGA3dCmdDXDwawIndexed;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawInstanced {
	uint32 vewtexCountPewInstance;
	uint32 instanceCount;
	uint32 stawtVewtexWocation;
	uint32 stawtInstanceWocation;
} SVGA3dCmdDXDwawInstanced;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawIndexedInstanced {
	uint32 indexCountPewInstance;
	uint32 instanceCount;
	uint32 stawtIndexWocation;
	int32 baseVewtexWocation;
	uint32 stawtInstanceWocation;
} SVGA3dCmdDXDwawIndexedInstanced;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawIndexedInstancedIndiwect {
	SVGA3dSuwfaceId awgsBuffewSid;
	uint32 byteOffsetFowAwgs;
} SVGA3dCmdDXDwawIndexedInstancedIndiwect;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawInstancedIndiwect {
	SVGA3dSuwfaceId awgsBuffewSid;
	uint32 byteOffsetFowAwgs;
} SVGA3dCmdDXDwawInstancedIndiwect;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDwawAuto {
	uint32 pad0;
} SVGA3dCmdDXDwawAuto;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDispatch {
	uint32 thweadGwoupCountX;
	uint32 thweadGwoupCountY;
	uint32 thweadGwoupCountZ;
} SVGA3dCmdDXDispatch;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDispatchIndiwect {
	SVGA3dSuwfaceId awgsBuffewSid;
	uint32 byteOffsetFowAwgs;
} SVGA3dCmdDXDispatchIndiwect;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetInputWayout {
	SVGA3dEwementWayoutId ewementWayoutId;
} SVGA3dCmdDXSetInputWayout;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dVewtexBuffew {
	SVGA3dSuwfaceId sid;
	uint32 stwide;
	uint32 offset;
} SVGA3dVewtexBuffew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetVewtexBuffews {
	uint32 stawtBuffew;

} SVGA3dCmdDXSetVewtexBuffews;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dVewtexBuffew_v2 {
	SVGA3dSuwfaceId sid;
	uint32 stwide;
	uint32 offset;
	uint32 sizeInBytes;
} SVGA3dVewtexBuffew_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetVewtexBuffews_v2 {
	uint32 stawtBuffew;

} SVGA3dCmdDXSetVewtexBuffews_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dVewtexBuffewOffsetAndSize {
	uint32 stwide;
	uint32 offset;
	uint32 sizeInBytes;
} SVGA3dVewtexBuffewOffsetAndSize;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetVewtexBuffewsOffsetAndSize {
	uint32 stawtBuffew;

} SVGA3dCmdDXSetVewtexBuffewsOffsetAndSize;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetIndexBuffew {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 offset;
} SVGA3dCmdDXSetIndexBuffew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetIndexBuffew_v2 {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 offset;
	uint32 sizeInBytes;
} SVGA3dCmdDXSetIndexBuffew_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetIndexBuffewOffsetAndSize {
	SVGA3dSuwfaceFowmat fowmat;
	uint32 offset;
	uint32 sizeInBytes;
} SVGA3dCmdDXSetIndexBuffewOffsetAndSize;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetTopowogy {
	SVGA3dPwimitiveType topowogy;
} SVGA3dCmdDXSetTopowogy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetWendewTawgets {
	SVGA3dDepthStenciwViewId depthStenciwViewId;

} SVGA3dCmdDXSetWendewTawgets;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetBwendState {
	SVGA3dBwendStateId bwendId;
	fwoat bwendFactow[4];
	uint32 sampweMask;
} SVGA3dCmdDXSetBwendState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetDepthStenciwState {
	SVGA3dDepthStenciwStateId depthStenciwId;
	uint32 stenciwWef;
} SVGA3dCmdDXSetDepthStenciwState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetWastewizewState {
	SVGA3dWastewizewStateId wastewizewId;
} SVGA3dCmdDXSetWastewizewState;
#pwagma pack(pop)

#define SVGA3D_DXQUEWY_FWAG_PWEDICATEHINT (1 << 0)
typedef uint32 SVGA3dDXQuewyFwags;

#define SVGADX_QDSTATE_INVAWID ((uint8)-1)
#define SVGADX_QDSTATE_MIN 0
#define SVGADX_QDSTATE_IDWE 0
#define SVGADX_QDSTATE_ACTIVE 1
#define SVGADX_QDSTATE_PENDING 2
#define SVGADX_QDSTATE_FINISHED 3
#define SVGADX_QDSTATE_MAX 4
typedef uint8 SVGADXQuewyDeviceState;

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dQuewyTypeUint8 type;
	uint16 pad0;
	SVGADXQuewyDeviceState state;
	SVGA3dDXQuewyFwags fwags;
	SVGAMobId mobid;
	uint32 offset;
} SVGACOTabweDXQuewyEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineQuewy {
	SVGA3dQuewyId quewyId;
	SVGA3dQuewyType type;
	SVGA3dDXQuewyFwags fwags;
} SVGA3dCmdDXDefineQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyQuewy {
	SVGA3dQuewyId quewyId;
} SVGA3dCmdDXDestwoyQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindQuewy {
	SVGA3dQuewyId quewyId;
	SVGAMobId mobid;
} SVGA3dCmdDXBindQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetQuewyOffset {
	SVGA3dQuewyId quewyId;
	uint32 mobOffset;
} SVGA3dCmdDXSetQuewyOffset;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBeginQuewy {
	SVGA3dQuewyId quewyId;
} SVGA3dCmdDXBeginQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXEndQuewy {
	SVGA3dQuewyId quewyId;
} SVGA3dCmdDXEndQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXWeadbackQuewy {
	SVGA3dQuewyId quewyId;
} SVGA3dCmdDXWeadbackQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXMoveQuewy {
	SVGA3dQuewyId quewyId;
	SVGAMobId mobid;
	uint32 mobOffset;
} SVGA3dCmdDXMoveQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindAwwQuewy {
	uint32 cid;
	SVGAMobId mobid;
} SVGA3dCmdDXBindAwwQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXWeadbackAwwQuewy {
	uint32 cid;
} SVGA3dCmdDXWeadbackAwwQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetPwedication {
	SVGA3dQuewyId quewyId;
	uint32 pwedicateVawue;
} SVGA3dCmdDXSetPwedication;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dDXSOState {
	uint32 offset;
	uint32 intOffset;
	uint32 dead1;
	uint32 dead2;
} SVGA3dDXSOState;
#pwagma pack(pop)

#define SVGA3D_DX_SO_OFFSET_APPEND ((uint32)~0u)

#pwagma pack(push, 1)
typedef stwuct SVGA3dSoTawget {
	SVGA3dSuwfaceId sid;
	uint32 offset;
	uint32 sizeInBytes;
} SVGA3dSoTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetSOTawgets {
	uint32 pad0;

} SVGA3dCmdDXSetSOTawgets;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dViewpowt {
	fwoat x;
	fwoat y;
	fwoat width;
	fwoat height;
	fwoat minDepth;
	fwoat maxDepth;
} SVGA3dViewpowt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetViewpowts {
	uint32 pad0;

} SVGA3dCmdDXSetViewpowts;
#pwagma pack(pop)

#define SVGA3D_DX_MAX_VIEWPOWTS 16

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetScissowWects {
	uint32 pad0;

} SVGA3dCmdDXSetScissowWects;
#pwagma pack(pop)

#define SVGA3D_DX_MAX_SCISSOWWECTS 16

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCweawWendewTawgetView {
	SVGA3dWendewTawgetViewId wendewTawgetViewId;
	SVGA3dWGBAFwoat wgba;
} SVGA3dCmdDXCweawWendewTawgetView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCweawDepthStenciwView {
	uint16 fwags;
	uint16 stenciw;
	SVGA3dDepthStenciwViewId depthStenciwViewId;
	fwoat depth;
} SVGA3dCmdDXCweawDepthStenciwView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedCopyWegion {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dCopyBox box;
} SVGA3dCmdDXPwedCopyWegion;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedStagingCopyWegion {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dCopyBox box;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];
} SVGA3dCmdDXPwedStagingCopyWegion;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedCopy {
	SVGA3dSuwfaceId dstSid;
	SVGA3dSuwfaceId swcSid;
} SVGA3dCmdDXPwedCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedConvewtWegion {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dBox destBox;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dBox swcBox;
} SVGA3dCmdDXPwedConvewtWegion;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedStagingConvewtWegion {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dBox destBox;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dBox swcBox;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];
} SVGA3dCmdDXPwedStagingConvewtWegion;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedConvewt {
	SVGA3dSuwfaceId dstSid;
	SVGA3dSuwfaceId swcSid;
} SVGA3dCmdDXPwedConvewt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedStagingConvewt {
	SVGA3dSuwfaceId dstSid;
	SVGA3dSuwfaceId swcSid;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];
} SVGA3dCmdDXPwedStagingConvewt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBuffewCopy {
	SVGA3dSuwfaceId dest;
	SVGA3dSuwfaceId swc;
	uint32 destX;
	uint32 swcX;
	uint32 width;
} SVGA3dCmdDXBuffewCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXStagingBuffewCopy {
	SVGA3dSuwfaceId dest;
	SVGA3dSuwfaceId swc;
	uint32 destX;
	uint32 swcX;
	uint32 width;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];
} SVGA3dCmdDXStagingBuffewCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dSuwfaceFowmat copyFowmat;
} SVGA3dCmdDXWesowveCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId dstSid;
	uint32 dstSubWesouwce;
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dSuwfaceFowmat copyFowmat;
} SVGA3dCmdDXPwedWesowveCopy;
#pwagma pack(pop)

typedef uint32 SVGA3dDXPwesentBwtMode;
#define SVGADX_PWESENTBWT_WINEAW (1 << 0)
#define SVGADX_PWESENTBWT_FOWCE_SWC_SWGB (1 << 1)
#define SVGADX_PWESENTBWT_FOWCE_SWC_XWBIAS (1 << 2)
#define SVGADX_PWESENTBWT_MODE_MAX (1 << 3)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwesentBwt {
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dSuwfaceId dstSid;
	uint32 destSubWesouwce;
	SVGA3dBox boxSwc;
	SVGA3dBox boxDest;
	SVGA3dDXPwesentBwtMode mode;
} SVGA3dCmdDXPwesentBwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXGenMips {
	SVGA3dShadewWesouwceViewId shadewWesouwceViewId;
} SVGA3dCmdDXGenMips;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXUpdateSubWesouwce {
	SVGA3dSuwfaceId sid;
	uint32 subWesouwce;
	SVGA3dBox box;
} SVGA3dCmdDXUpdateSubWesouwce;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXWeadbackSubWesouwce {
	SVGA3dSuwfaceId sid;
	uint32 subWesouwce;
} SVGA3dCmdDXWeadbackSubWesouwce;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXInvawidateSubWesouwce {
	SVGA3dSuwfaceId sid;
	uint32 subWesouwce;
} SVGA3dCmdDXInvawidateSubWesouwce;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXTwansfewFwomBuffew {
	SVGA3dSuwfaceId swcSid;
	uint32 swcOffset;
	uint32 swcPitch;
	uint32 swcSwicePitch;
	SVGA3dSuwfaceId destSid;
	uint32 destSubWesouwce;
	SVGA3dBox destBox;
} SVGA3dCmdDXTwansfewFwomBuffew;
#pwagma pack(pop)

#define SVGA3D_TWANSFEW_TO_BUFFEW_WEADBACK (1 << 0)
#define SVGA3D_TWANSFEW_TO_BUFFEW_FWAGS_MASK (1 << 0)
typedef uint32 SVGA3dTwansfewToBuffewFwags;

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXTwansfewToBuffew {
	SVGA3dSuwfaceId swcSid;
	uint32 swcSubWesouwce;
	SVGA3dBox swcBox;
	SVGA3dSuwfaceId destSid;
	uint32 destOffset;
	uint32 destPitch;
	uint32 destSwicePitch;
	SVGA3dTwansfewToBuffewFwags fwags;
} SVGA3dCmdDXTwansfewToBuffew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedTwansfewFwomBuffew {
	SVGA3dSuwfaceId swcSid;
	uint32 swcOffset;
	uint32 swcPitch;
	uint32 swcSwicePitch;
	SVGA3dSuwfaceId destSid;
	uint32 destSubWesouwce;
	SVGA3dBox destBox;
} SVGA3dCmdDXPwedTwansfewFwomBuffew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSuwfaceCopyAndWeadback {
	SVGA3dSuwfaceId swcSid;
	SVGA3dSuwfaceId destSid;
	SVGA3dCopyBox box;
} SVGA3dCmdDXSuwfaceCopyAndWeadback;
#pwagma pack(pop)

typedef uint32 SVGADXHintId;
#define SVGA_DX_HINT_NONE 0
#define SVGA_DX_HINT_PWEFETCH_OBJECT 1
#define SVGA_DX_HINT_PWEEVICT_OBJECT 2
#define SVGA_DX_HINT_PWEFETCH_COBJECT 3
#define SVGA_DX_HINT_PWEEVICT_COBJECT 4
#define SVGA_DX_HINT_MAX 5

#pwagma pack(push, 1)
typedef stwuct SVGAObjectWef {
	SVGAOTabweType type;
	uint32 id;
} SVGAObjectWef;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGACObjectWef {
	SVGACOTabweType type;
	uint32 cid;
	uint32 id;
} SVGACObjectWef;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXHint {
	SVGADXHintId hintId;

} SVGA3dCmdDXHint;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBuffewUpdate {
	SVGA3dSuwfaceId sid;
	uint32 x;
	uint32 width;
} SVGA3dCmdDXBuffewUpdate;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetConstantBuffewOffset {
	uint32 swot;
	uint32 offsetInBytes;
} SVGA3dCmdDXSetConstantBuffewOffset;
#pwagma pack(pop)

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetVSConstantBuffewOffset;

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetPSConstantBuffewOffset;

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetGSConstantBuffewOffset;

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetHSConstantBuffewOffset;

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetDSConstantBuffewOffset;

typedef SVGA3dCmdDXSetConstantBuffewOffset SVGA3dCmdDXSetCSConstantBuffewOffset;

#define SVGA3D_BUFFEWEX_SWV_WAW (1 << 0)
#define SVGA3D_BUFFEWEX_SWV_FWAGS_MAX (1 << 1)
#define SVGA3D_BUFFEWEX_SWV_FWAGS_MASK (SVGA3D_BUFFEWEX_SWV_FWAGS_MAX - 1)
typedef uint32 SVGA3dBuffewExFwags;

#pwagma pack(push, 1)
typedef stwuct {
	union {
		stwuct {
			uint32 fiwstEwement;
			uint32 numEwements;
			uint32 pad0;
			uint32 pad1;
		} buffew;
		stwuct {
			uint32 mostDetaiwedMip;
			uint32 fiwstAwwaySwice;
			uint32 mipWevews;
			uint32 awwaySize;
		} tex;
		stwuct {
			uint32 fiwstEwement;
			uint32 numEwements;
			SVGA3dBuffewExFwags fwags;
			uint32 pad0;
		} buffewex;
	};
} SVGA3dShadewWesouwceViewDesc;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	SVGA3dShadewWesouwceViewDesc desc;
	uint32 pad;
} SVGACOTabweDXSWViewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineShadewWesouwceView {
	SVGA3dShadewWesouwceViewId shadewWesouwceViewId;

	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;

	SVGA3dShadewWesouwceViewDesc desc;
} SVGA3dCmdDXDefineShadewWesouwceView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyShadewWesouwceView {
	SVGA3dShadewWesouwceViewId shadewWesouwceViewId;
} SVGA3dCmdDXDestwoyShadewWesouwceView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dWendewTawgetViewDesc {
	union {
		stwuct {
			uint32 fiwstEwement;
			uint32 numEwements;
			uint32 padding0;
		} buffew;
		stwuct {
			uint32 mipSwice;
			uint32 fiwstAwwaySwice;
			uint32 awwaySize;
		} tex;
		stwuct {
			uint32 mipSwice;
			uint32 fiwstW;
			uint32 wSize;
		} tex3D;
	};
} SVGA3dWendewTawgetViewDesc;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	SVGA3dWendewTawgetViewDesc desc;
	uint32 pad[2];
} SVGACOTabweDXWTViewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineWendewTawgetView {
	SVGA3dWendewTawgetViewId wendewTawgetViewId;

	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;

	SVGA3dWendewTawgetViewDesc desc;
} SVGA3dCmdDXDefineWendewTawgetView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyWendewTawgetView {
	SVGA3dWendewTawgetViewId wendewTawgetViewId;
} SVGA3dCmdDXDestwoyWendewTawgetView;
#pwagma pack(pop)

#define SVGA3D_DXDSVIEW_CWEATE_WEAD_ONWY_DEPTH 0x01
#define SVGA3D_DXDSVIEW_CWEATE_WEAD_ONWY_STENCIW 0x02
#define SVGA3D_DXDSVIEW_CWEATE_FWAG_MASK 0x03
typedef uint8 SVGA3DCweateDSViewFwags;

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	uint32 mipSwice;
	uint32 fiwstAwwaySwice;
	uint32 awwaySize;
	SVGA3DCweateDSViewFwags fwags;
	uint8 pad0;
	uint16 pad1;
	uint32 pad2;
} SVGACOTabweDXDSViewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineDepthStenciwView {
	SVGA3dDepthStenciwViewId depthStenciwViewId;

	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	uint32 mipSwice;
	uint32 fiwstAwwaySwice;
	uint32 awwaySize;
	SVGA3DCweateDSViewFwags fwags;
	uint8 pad0;
	uint16 pad1;
} SVGA3dCmdDXDefineDepthStenciwView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineDepthStenciwView_v2 {
	SVGA3dDepthStenciwViewId depthStenciwViewId;

	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	uint32 mipSwice;
	uint32 fiwstAwwaySwice;
	uint32 awwaySize;
	SVGA3DCweateDSViewFwags fwags;
	uint8 pad0;
	uint16 pad1;
} SVGA3dCmdDXDefineDepthStenciwView_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyDepthStenciwView {
	SVGA3dDepthStenciwViewId depthStenciwViewId;
} SVGA3dCmdDXDestwoyDepthStenciwView;
#pwagma pack(pop)

#define SVGA3D_UABUFFEW_WAW (1 << 0)
#define SVGA3D_UABUFFEW_APPEND (1 << 1)
#define SVGA3D_UABUFFEW_COUNTEW (1 << 2)
typedef uint32 SVGA3dUABuffewFwags;

#pwagma pack(push, 1)
typedef stwuct {
	union {
		stwuct {
			uint32 fiwstEwement;
			uint32 numEwements;
			SVGA3dUABuffewFwags fwags;
			uint32 padding0;
			uint32 padding1;
		} buffew;
		stwuct {
			uint32 mipSwice;
			uint32 fiwstAwwaySwice;
			uint32 awwaySize;
			uint32 padding0;
			uint32 padding1;
		} tex;
		stwuct {
			uint32 mipSwice;
			uint32 fiwstW;
			uint32 wSize;
			uint32 padding0;
			uint32 padding1;
		} tex3D;
	};
} SVGA3dUAViewDesc;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;
	SVGA3dUAViewDesc desc;
	uint32 stwuctuweCount;
	uint32 pad[7];
} SVGACOTabweDXUAViewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineUAView {
	SVGA3dUAViewId uaViewId;

	SVGA3dSuwfaceId sid;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dWesouwceType wesouwceDimension;

	SVGA3dUAViewDesc desc;
} SVGA3dCmdDXDefineUAView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyUAView {
	SVGA3dUAViewId uaViewId;
} SVGA3dCmdDXDestwoyUAView;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCweawUAViewUint {
	SVGA3dUAViewId uaViewId;
	SVGA3dWGBAUint32 vawue;
} SVGA3dCmdDXCweawUAViewUint;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCweawUAViewFwoat {
	SVGA3dUAViewId uaViewId;
	SVGA3dWGBAFwoat vawue;
} SVGA3dCmdDXCweawUAViewFwoat;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCopyStwuctuweCount {
	SVGA3dUAViewId swcUAViewId;
	SVGA3dSuwfaceId destSid;
	uint32 destByteOffset;
} SVGA3dCmdDXCopyStwuctuweCount;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetStwuctuweCount {
	SVGA3dUAViewId uaViewId;
	uint32 stwuctuweCount;
} SVGA3dCmdDXSetStwuctuweCount;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetUAViews {
	uint32 uavSpwiceIndex;

} SVGA3dCmdDXSetUAViews;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetCSUAViews {
	uint32 stawtIndex;

} SVGA3dCmdDXSetCSUAViews;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dInputEwementDesc {
	uint32 inputSwot;
	uint32 awignedByteOffset;
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dInputCwassification inputSwotCwass;
	uint32 instanceDataStepWate;
	uint32 inputWegistew;
} SVGA3dInputEwementDesc;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 ewid;
	uint32 numDescs;
	SVGA3dInputEwementDesc descs[32];
	uint32 pad[62];
} SVGACOTabweDXEwementWayoutEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineEwementWayout {
	SVGA3dEwementWayoutId ewementWayoutId;

} SVGA3dCmdDXDefineEwementWayout;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyEwementWayout {
	SVGA3dEwementWayoutId ewementWayoutId;
} SVGA3dCmdDXDestwoyEwementWayout;
#pwagma pack(pop)

#define SVGA3D_DX_MAX_WENDEW_TAWGETS 8

#pwagma pack(push, 1)
typedef stwuct SVGA3dDXBwendStatePewWT {
	uint8 bwendEnabwe;
	uint8 swcBwend;
	uint8 destBwend;
	uint8 bwendOp;
	uint8 swcBwendAwpha;
	uint8 destBwendAwpha;
	uint8 bwendOpAwpha;
	SVGA3dCowowWwiteEnabwe wendewTawgetWwiteMask;
	uint8 wogicOpEnabwe;
	uint8 wogicOp;
	uint16 pad0;
} SVGA3dDXBwendStatePewWT;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint8 awphaToCovewageEnabwe;
	uint8 independentBwendEnabwe;
	uint16 pad0;
	SVGA3dDXBwendStatePewWT pewWT[SVGA3D_DX_MAX_WENDEW_TAWGETS];
	uint32 pad1[7];
} SVGACOTabweDXBwendStateEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineBwendState {
	SVGA3dBwendStateId bwendId;
	uint8 awphaToCovewageEnabwe;
	uint8 independentBwendEnabwe;
	uint16 pad0;
	SVGA3dDXBwendStatePewWT pewWT[SVGA3D_DX_MAX_WENDEW_TAWGETS];
} SVGA3dCmdDXDefineBwendState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyBwendState {
	SVGA3dBwendStateId bwendId;
} SVGA3dCmdDXDestwoyBwendState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint8 depthEnabwe;
	SVGA3dDepthWwiteMask depthWwiteMask;
	SVGA3dCompawisonFunc depthFunc;
	uint8 stenciwEnabwe;
	uint8 fwontEnabwe;
	uint8 backEnabwe;
	uint8 stenciwWeadMask;
	uint8 stenciwWwiteMask;

	uint8 fwontStenciwFaiwOp;
	uint8 fwontStenciwDepthFaiwOp;
	uint8 fwontStenciwPassOp;
	SVGA3dCompawisonFunc fwontStenciwFunc;

	uint8 backStenciwFaiwOp;
	uint8 backStenciwDepthFaiwOp;
	uint8 backStenciwPassOp;
	SVGA3dCompawisonFunc backStenciwFunc;
} SVGACOTabweDXDepthStenciwEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineDepthStenciwState {
	SVGA3dDepthStenciwStateId depthStenciwId;

	uint8 depthEnabwe;
	SVGA3dDepthWwiteMask depthWwiteMask;
	SVGA3dCompawisonFunc depthFunc;
	uint8 stenciwEnabwe;
	uint8 fwontEnabwe;
	uint8 backEnabwe;
	uint8 stenciwWeadMask;
	uint8 stenciwWwiteMask;

	uint8 fwontStenciwFaiwOp;
	uint8 fwontStenciwDepthFaiwOp;
	uint8 fwontStenciwPassOp;
	SVGA3dCompawisonFunc fwontStenciwFunc;

	uint8 backStenciwFaiwOp;
	uint8 backStenciwDepthFaiwOp;
	uint8 backStenciwPassOp;
	SVGA3dCompawisonFunc backStenciwFunc;
} SVGA3dCmdDXDefineDepthStenciwState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyDepthStenciwState {
	SVGA3dDepthStenciwStateId depthStenciwId;
} SVGA3dCmdDXDestwoyDepthStenciwState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint8 fiwwMode;
	SVGA3dCuwwMode cuwwMode;
	uint8 fwontCountewCwockwise;
	uint8 pwovokingVewtexWast;
	int32 depthBias;
	fwoat depthBiasCwamp;
	fwoat swopeScawedDepthBias;
	uint8 depthCwipEnabwe;
	uint8 scissowEnabwe;
	SVGA3dMuwtisampweWastEnabwe muwtisampweEnabwe;
	uint8 antiawiasedWineEnabwe;
	fwoat wineWidth;
	uint8 wineStippweEnabwe;
	uint8 wineStippweFactow;
	uint16 wineStippwePattewn;
	uint8 fowcedSampweCount;
	uint8 mustBeZewo[3];
} SVGACOTabweDXWastewizewStateEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineWastewizewState {
	SVGA3dWastewizewStateId wastewizewId;

	uint8 fiwwMode;
	SVGA3dCuwwMode cuwwMode;
	uint8 fwontCountewCwockwise;
	uint8 pwovokingVewtexWast;
	int32 depthBias;
	fwoat depthBiasCwamp;
	fwoat swopeScawedDepthBias;
	uint8 depthCwipEnabwe;
	uint8 scissowEnabwe;
	SVGA3dMuwtisampweWastEnabwe muwtisampweEnabwe;
	uint8 antiawiasedWineEnabwe;
	fwoat wineWidth;
	uint8 wineStippweEnabwe;
	uint8 wineStippweFactow;
	uint16 wineStippwePattewn;
} SVGA3dCmdDXDefineWastewizewState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineWastewizewState_v2 {
	SVGA3dWastewizewStateId wastewizewId;

	uint8 fiwwMode;
	SVGA3dCuwwMode cuwwMode;
	uint8 fwontCountewCwockwise;
	uint8 pwovokingVewtexWast;
	int32 depthBias;
	fwoat depthBiasCwamp;
	fwoat swopeScawedDepthBias;
	uint8 depthCwipEnabwe;
	uint8 scissowEnabwe;
	SVGA3dMuwtisampweWastEnabwe muwtisampweEnabwe;
	uint8 antiawiasedWineEnabwe;
	fwoat wineWidth;
	uint8 wineStippweEnabwe;
	uint8 wineStippweFactow;
	uint16 wineStippwePattewn;
	uint32 fowcedSampweCount;
} SVGA3dCmdDXDefineWastewizewState_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyWastewizewState {
	SVGA3dWastewizewStateId wastewizewId;
} SVGA3dCmdDXDestwoyWastewizewState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dFiwtew fiwtew;
	uint8 addwessU;
	uint8 addwessV;
	uint8 addwessW;
	uint8 pad0;
	fwoat mipWODBias;
	uint8 maxAnisotwopy;
	SVGA3dCompawisonFunc compawisonFunc;
	uint16 pad1;
	SVGA3dWGBAFwoat bowdewCowow;
	fwoat minWOD;
	fwoat maxWOD;
	uint32 pad2[6];
} SVGACOTabweDXSampwewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineSampwewState {
	SVGA3dSampwewId sampwewId;
	SVGA3dFiwtew fiwtew;
	uint8 addwessU;
	uint8 addwessV;
	uint8 addwessW;
	uint8 pad0;
	fwoat mipWODBias;
	uint8 maxAnisotwopy;
	SVGA3dCompawisonFunc compawisonFunc;
	uint16 pad1;
	SVGA3dWGBAFwoat bowdewCowow;
	fwoat minWOD;
	fwoat maxWOD;
} SVGA3dCmdDXDefineSampwewState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoySampwewState {
	SVGA3dSampwewId sampwewId;
} SVGA3dCmdDXDestwoySampwewState;
#pwagma pack(pop)

#define SVGADX_SIGNATUWE_SEMANTIC_NAME_UNDEFINED 0
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_POSITION 1
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_CWIP_DISTANCE 2
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_CUWW_DISTANCE 3
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_WENDEW_TAWGET_AWWAY_INDEX 4
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_VIEWPOWT_AWWAY_INDEX 5
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_VEWTEX_ID 6
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_PWIMITIVE_ID 7
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_INSTANCE_ID 8
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_IS_FWONT_FACE 9
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_SAMPWE_INDEX 10
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_U_EQ_0_EDGE_TESSFACTOW 11
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_V_EQ_0_EDGE_TESSFACTOW 12
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_U_EQ_1_EDGE_TESSFACTOW 13
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_V_EQ_1_EDGE_TESSFACTOW 14
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_U_INSIDE_TESSFACTOW 15
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_QUAD_V_INSIDE_TESSFACTOW 16
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_TWI_U_EQ_0_EDGE_TESSFACTOW 17
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_TWI_V_EQ_0_EDGE_TESSFACTOW 18
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_TWI_W_EQ_0_EDGE_TESSFACTOW 19
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_TWI_INSIDE_TESSFACTOW 20
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_WINE_DETAIW_TESSFACTOW 21
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_FINAW_WINE_DENSITY_TESSFACTOW 22
#define SVGADX_SIGNATUWE_SEMANTIC_NAME_MAX 23
typedef uint32 SVGA3dDXSignatuweSemanticName;

#define SVGADX_SIGNATUWE_WEGISTEW_COMPONENT_UNKNOWN 0
typedef uint32 SVGA3dDXSignatuweWegistewComponentType;

#define SVGADX_SIGNATUWE_MIN_PWECISION_DEFAUWT 0
typedef uint32 SVGA3dDXSignatuweMinPwecision;

#pwagma pack(push, 1)
typedef stwuct SVGA3dDXSignatuweEntwy {
	uint32 wegistewIndex;
	SVGA3dDXSignatuweSemanticName semanticName;
	uint32 mask;
	SVGA3dDXSignatuweWegistewComponentType componentType;
	SVGA3dDXSignatuweMinPwecision minPwecision;
} SVGA3dDXShadewSignatuweEntwy;
#pwagma pack(pop)

#define SVGADX_SIGNATUWE_HEADEW_VEWSION_0 0x08a92d12

#pwagma pack(push, 1)
typedef stwuct SVGA3dDXSignatuweHeadew {
	uint32 headewVewsion;
	uint32 numInputSignatuwes;
	uint32 numOutputSignatuwes;
	uint32 numPatchConstantSignatuwes;
} SVGA3dDXShadewSignatuweHeadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineShadew {
	SVGA3dShadewId shadewId;
	SVGA3dShadewType type;
	uint32 sizeInBytes;
} SVGA3dCmdDXDefineShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGACOTabweDXShadewEntwy {
	SVGA3dShadewType type;
	uint32 sizeInBytes;
	uint32 offsetInBytes;
	SVGAMobId mobid;
	uint32 pad[4];
} SVGACOTabweDXShadewEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyShadew {
	SVGA3dShadewId shadewId;
} SVGA3dCmdDXDestwoyShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindShadew {
	uint32 cid;
	uint32 shid;
	SVGAMobId mobid;
	uint32 offsetInBytes;
} SVGA3dCmdDXBindShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindAwwShadew {
	uint32 cid;
	SVGAMobId mobid;
} SVGA3dCmdDXBindAwwShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCondBindAwwShadew {
	uint32 cid;
	SVGAMobId testMobid;
	SVGAMobId mobid;
} SVGA3dCmdDXCondBindAwwShadew;
#pwagma pack(pop)

#define SVGA3D_MAX_DX10_STWEAMOUT_DECWS 64
#define SVGA3D_MAX_STWEAMOUT_DECWS 512

#pwagma pack(push, 1)
typedef stwuct SVGA3dStweamOutputDecwawationEntwy {
	uint32 outputSwot;
	uint32 wegistewIndex;
	uint8 wegistewMask;
	uint8 pad0;
	uint16 pad1;
	uint32 stweam;
} SVGA3dStweamOutputDecwawationEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGAOTabweStweamOutputEntwy {
	uint32 numOutputStweamEntwies;
	SVGA3dStweamOutputDecwawationEntwy decw[SVGA3D_MAX_DX10_STWEAMOUT_DECWS];
	uint32 stweamOutputStwideInBytes[SVGA3D_DX_MAX_SOTAWGETS];
	uint32 wastewizedStweam;
	uint32 numOutputStweamStwides;
	uint32 mobid;
	uint32 offsetInBytes;
	uint8 usesMob;
	uint8 pad0;
	uint16 pad1;
	uint32 pad2[246];
} SVGACOTabweDXStweamOutputEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineStweamOutput {
	SVGA3dStweamOutputId soid;
	uint32 numOutputStweamEntwies;
	SVGA3dStweamOutputDecwawationEntwy decw[SVGA3D_MAX_DX10_STWEAMOUT_DECWS];
	uint32 stweamOutputStwideInBytes[SVGA3D_DX_MAX_SOTAWGETS];
	uint32 wastewizedStweam;
} SVGA3dCmdDXDefineStweamOutput;
#pwagma pack(pop)

#define SVGA3D_DX_SO_NO_WASTEWIZED_STWEAM 0xFFFFFFFF

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDefineStweamOutputWithMob {
	SVGA3dStweamOutputId soid;
	uint32 numOutputStweamEntwies;
	uint32 numOutputStweamStwides;
	uint32 stweamOutputStwideInBytes[SVGA3D_DX_MAX_SOTAWGETS];
	uint32 wastewizedStweam;
} SVGA3dCmdDXDefineStweamOutputWithMob;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXBindStweamOutput {
	SVGA3dStweamOutputId soid;
	uint32 mobid;
	uint32 offsetInBytes;
	uint32 sizeInBytes;
} SVGA3dCmdDXBindStweamOutput;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXDestwoyStweamOutput {
	SVGA3dStweamOutputId soid;
} SVGA3dCmdDXDestwoyStweamOutput;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetStweamOutput {
	SVGA3dStweamOutputId soid;
} SVGA3dCmdDXSetStweamOutput;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetMinWOD {
	SVGA3dSuwfaceId sid;
	fwoat minWOD;
} SVGA3dCmdDXSetMinWOD;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint64 vawue;
	uint32 mobId;
	uint32 mobOffset;
} SVGA3dCmdDXMobFence64;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXSetCOTabwe {
	uint32 cid;
	uint32 mobid;
	SVGACOTabweType type;
	uint32 vawidSizeInBytes;
} SVGA3dCmdDXSetCOTabwe;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXGwowCOTabwe {
	uint32 cid;
	uint32 mobid;
	SVGACOTabweType type;
	uint32 vawidSizeInBytes;
} SVGA3dCmdDXGwowCOTabwe;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXWeadbackCOTabwe {
	uint32 cid;
	SVGACOTabweType type;
} SVGA3dCmdDXWeadbackCOTabwe;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXCopyCOTabweIntoMob {
	uint32 cid;
	SVGACOTabweType type;
	uint32 mobid;
} SVGA3dCmdDXCopyCOTabweIntoMob;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXPwedStagingCopy {
	SVGA3dSuwfaceId dstSid;
	SVGA3dSuwfaceId swcSid;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];

} SVGA3dCmdDXPwedStagingCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDXStagingCopy {
	SVGA3dSuwfaceId dstSid;
	SVGA3dSuwfaceId swcSid;
	uint8 weadback;
	uint8 unsynchwonized;
	uint8 mustBeZewo[2];

} SVGA3dCmdDXStagingCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCOTabweData {
	uint32 mobid;
} SVGA3dCOTabweData;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dBuffewBinding {
	uint32 buffewId;
	uint32 stwide;
	uint32 offset;
} SVGA3dBuffewBinding;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dConstantBuffewBinding {
	uint32 sid;
	uint32 offsetInBytes;
	uint32 sizeInBytes;
} SVGA3dConstantBuffewBinding;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGADXInputAssembwyMobFowmat {
	uint32 wayoutId;
	SVGA3dBuffewBinding vewtexBuffews[SVGA3D_DX_MAX_VEWTEXBUFFEWS];
	uint32 indexBuffewSid;
	uint32 pad;
	uint32 indexBuffewOffset;
	uint32 indexBuffewFowmat;
	uint32 topowogy;
} SVGADXInputAssembwyMobFowmat;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGADXContextMobFowmat {
	SVGADXInputAssembwyMobFowmat inputAssembwy;

	stwuct {
		uint32 bwendStateId;
		uint32 bwendFactow[4];
		uint32 sampweMask;
		uint32 depthStenciwStateId;
		uint32 stenciwWef;
		uint32 wastewizewStateId;
		uint32 depthStenciwViewId;
		uint32 wendewTawgetViewIds[SVGA3D_DX_MAX_WENDEW_TAWGETS];
	} wendewState;

	uint32 pad0[8];

	stwuct {
		uint32 tawgets[SVGA3D_DX_MAX_SOTAWGETS];
		uint32 soid;
	} stweamOut;

	uint32 pad1[10];

	uint32 uavSpwiceIndex;

	uint8 numViewpowts;
	uint8 numScissowWects;
	uint16 pad2[1];

	uint32 pad3[3];

	SVGA3dViewpowt viewpowts[SVGA3D_DX_MAX_VIEWPOWTS];
	uint32 pad4[32];

	SVGASignedWect scissowWects[SVGA3D_DX_MAX_SCISSOWWECTS];
	uint32 pad5[64];

	stwuct {
		uint32 quewyID;
		uint32 vawue;
	} pwedication;

	SVGAMobId shadewIfaceMobid;
	uint32 shadewIfaceOffset;
	stwuct {
		uint32 shadewId;
		SVGA3dConstantBuffewBinding
			constantBuffews[SVGA3D_DX_MAX_CONSTBUFFEWS];
		uint32 shadewWesouwces[SVGA3D_DX_MAX_SWVIEWS];
		uint32 sampwews[SVGA3D_DX_MAX_SAMPWEWS];
	} shadewState[SVGA3D_NUM_SHADEWTYPE];
	uint32 pad6[26];

	SVGA3dQuewyId quewyID[SVGA3D_MAX_QUEWY];

	SVGA3dCOTabweData cotabwes[SVGA_COTABWE_MAX];

	uint32 pad7[64];

	uint32 uaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];
	uint32 csuaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];

	uint32 pad8[188];
} SVGADXContextMobFowmat;
#pwagma pack(pop)

#define SVGA3D_DX_MAX_CWASS_INSTANCES_PADDED 256

#pwagma pack(push, 1)
typedef stwuct SVGADXShadewIfaceMobFowmat {
	stwuct {
		uint32 numCwassInstances;
		uint32 iface[SVGA3D_DX_MAX_CWASS_INSTANCES_PADDED];
		SVGA3dIfaceData data[SVGA3D_DX_MAX_CWASS_INSTANCES_PADDED];
	} shadewIfaceState[SVGA3D_NUM_SHADEWTYPE];

	uint32 pad0[1018];
} SVGADXShadewIfaceMobFowmat;
#pwagma pack(pop)

#endif
