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
 * svga3d_cmd.h --
 *
 *    SVGA 3d hawdwawe cmd definitions
 */



#ifndef _SVGA3D_CMD_H_
#define _SVGA3D_CMD_H_

#incwude "svga3d_types.h"
#incwude "svga3d_wimits.h"
#incwude "svga_weg.h"

typedef enum SVGAFifo3dCmdId {
	SVGA_3D_CMD_WEGACY_BASE = 1000,
	SVGA_3D_CMD_BASE = 1040,

	SVGA_3D_CMD_SUWFACE_DEFINE = 1040,
	SVGA_3D_CMD_SUWFACE_DESTWOY = 1041,
	SVGA_3D_CMD_SUWFACE_COPY = 1042,
	SVGA_3D_CMD_SUWFACE_STWETCHBWT = 1043,
	SVGA_3D_CMD_SUWFACE_DMA = 1044,
	SVGA_3D_CMD_CONTEXT_DEFINE = 1045,
	SVGA_3D_CMD_CONTEXT_DESTWOY = 1046,
	SVGA_3D_CMD_SETTWANSFOWM = 1047,
	SVGA_3D_CMD_SETZWANGE = 1048,
	SVGA_3D_CMD_SETWENDEWSTATE = 1049,
	SVGA_3D_CMD_SETWENDEWTAWGET = 1050,
	SVGA_3D_CMD_SETTEXTUWESTATE = 1051,
	SVGA_3D_CMD_SETMATEWIAW = 1052,
	SVGA_3D_CMD_SETWIGHTDATA = 1053,
	SVGA_3D_CMD_SETWIGHTENABWED = 1054,
	SVGA_3D_CMD_SETVIEWPOWT = 1055,
	SVGA_3D_CMD_SETCWIPPWANE = 1056,
	SVGA_3D_CMD_CWEAW = 1057,
	SVGA_3D_CMD_PWESENT = 1058,
	SVGA_3D_CMD_SHADEW_DEFINE = 1059,
	SVGA_3D_CMD_SHADEW_DESTWOY = 1060,
	SVGA_3D_CMD_SET_SHADEW = 1061,
	SVGA_3D_CMD_SET_SHADEW_CONST = 1062,
	SVGA_3D_CMD_DWAW_PWIMITIVES = 1063,
	SVGA_3D_CMD_SETSCISSOWWECT = 1064,
	SVGA_3D_CMD_BEGIN_QUEWY = 1065,
	SVGA_3D_CMD_END_QUEWY = 1066,
	SVGA_3D_CMD_WAIT_FOW_QUEWY = 1067,
	SVGA_3D_CMD_PWESENT_WEADBACK = 1068,
	SVGA_3D_CMD_BWIT_SUWFACE_TO_SCWEEN = 1069,
	SVGA_3D_CMD_SUWFACE_DEFINE_V2 = 1070,
	SVGA_3D_CMD_GENEWATE_MIPMAPS = 1071,
	SVGA_3D_CMD_DEAD4 = 1072,
	SVGA_3D_CMD_DEAD5 = 1073,
	SVGA_3D_CMD_DEAD6 = 1074,
	SVGA_3D_CMD_DEAD7 = 1075,
	SVGA_3D_CMD_DEAD8 = 1076,
	SVGA_3D_CMD_DEAD9 = 1077,
	SVGA_3D_CMD_DEAD10 = 1078,
	SVGA_3D_CMD_DEAD11 = 1079,
	SVGA_3D_CMD_ACTIVATE_SUWFACE = 1080,
	SVGA_3D_CMD_DEACTIVATE_SUWFACE = 1081,
	SVGA_3D_CMD_SCWEEN_DMA = 1082,
	SVGA_3D_CMD_DEAD1 = 1083,
	SVGA_3D_CMD_DEAD2 = 1084,

	SVGA_3D_CMD_DEAD12 = 1085,
	SVGA_3D_CMD_DEAD13 = 1086,
	SVGA_3D_CMD_DEAD14 = 1087,
	SVGA_3D_CMD_DEAD15 = 1088,
	SVGA_3D_CMD_DEAD16 = 1089,
	SVGA_3D_CMD_DEAD17 = 1090,

	SVGA_3D_CMD_SET_OTABWE_BASE = 1091,
	SVGA_3D_CMD_WEADBACK_OTABWE = 1092,

	SVGA_3D_CMD_DEFINE_GB_MOB = 1093,
	SVGA_3D_CMD_DESTWOY_GB_MOB = 1094,
	SVGA_3D_CMD_DEAD3 = 1095,
	SVGA_3D_CMD_UPDATE_GB_MOB_MAPPING = 1096,

	SVGA_3D_CMD_DEFINE_GB_SUWFACE = 1097,
	SVGA_3D_CMD_DESTWOY_GB_SUWFACE = 1098,
	SVGA_3D_CMD_BIND_GB_SUWFACE = 1099,
	SVGA_3D_CMD_COND_BIND_GB_SUWFACE = 1100,
	SVGA_3D_CMD_UPDATE_GB_IMAGE = 1101,
	SVGA_3D_CMD_UPDATE_GB_SUWFACE = 1102,
	SVGA_3D_CMD_WEADBACK_GB_IMAGE = 1103,
	SVGA_3D_CMD_WEADBACK_GB_SUWFACE = 1104,
	SVGA_3D_CMD_INVAWIDATE_GB_IMAGE = 1105,
	SVGA_3D_CMD_INVAWIDATE_GB_SUWFACE = 1106,

	SVGA_3D_CMD_DEFINE_GB_CONTEXT = 1107,
	SVGA_3D_CMD_DESTWOY_GB_CONTEXT = 1108,
	SVGA_3D_CMD_BIND_GB_CONTEXT = 1109,
	SVGA_3D_CMD_WEADBACK_GB_CONTEXT = 1110,
	SVGA_3D_CMD_INVAWIDATE_GB_CONTEXT = 1111,

	SVGA_3D_CMD_DEFINE_GB_SHADEW = 1112,
	SVGA_3D_CMD_DESTWOY_GB_SHADEW = 1113,
	SVGA_3D_CMD_BIND_GB_SHADEW = 1114,

	SVGA_3D_CMD_SET_OTABWE_BASE64 = 1115,

	SVGA_3D_CMD_BEGIN_GB_QUEWY = 1116,
	SVGA_3D_CMD_END_GB_QUEWY = 1117,
	SVGA_3D_CMD_WAIT_FOW_GB_QUEWY = 1118,

	SVGA_3D_CMD_NOP = 1119,

	SVGA_3D_CMD_ENABWE_GAWT = 1120,
	SVGA_3D_CMD_DISABWE_GAWT = 1121,
	SVGA_3D_CMD_MAP_MOB_INTO_GAWT = 1122,
	SVGA_3D_CMD_UNMAP_GAWT_WANGE = 1123,

	SVGA_3D_CMD_DEFINE_GB_SCWEENTAWGET = 1124,
	SVGA_3D_CMD_DESTWOY_GB_SCWEENTAWGET = 1125,
	SVGA_3D_CMD_BIND_GB_SCWEENTAWGET = 1126,
	SVGA_3D_CMD_UPDATE_GB_SCWEENTAWGET = 1127,

	SVGA_3D_CMD_WEADBACK_GB_IMAGE_PAWTIAW = 1128,
	SVGA_3D_CMD_INVAWIDATE_GB_IMAGE_PAWTIAW = 1129,

	SVGA_3D_CMD_SET_GB_SHADEWCONSTS_INWINE = 1130,

	SVGA_3D_CMD_GB_SCWEEN_DMA = 1131,
	SVGA_3D_CMD_BIND_GB_SUWFACE_WITH_PITCH = 1132,
	SVGA_3D_CMD_GB_MOB_FENCE = 1133,
	SVGA_3D_CMD_DEFINE_GB_SUWFACE_V2 = 1134,
	SVGA_3D_CMD_DEFINE_GB_MOB64 = 1135,
	SVGA_3D_CMD_WEDEFINE_GB_MOB64 = 1136,
	SVGA_3D_CMD_NOP_EWWOW = 1137,

	SVGA_3D_CMD_SET_VEWTEX_STWEAMS = 1138,
	SVGA_3D_CMD_SET_VEWTEX_DECWS = 1139,
	SVGA_3D_CMD_SET_VEWTEX_DIVISOWS = 1140,
	SVGA_3D_CMD_DWAW = 1141,
	SVGA_3D_CMD_DWAW_INDEXED = 1142,

	SVGA_3D_CMD_DX_MIN = 1143,
	SVGA_3D_CMD_DX_DEFINE_CONTEXT = 1143,
	SVGA_3D_CMD_DX_DESTWOY_CONTEXT = 1144,
	SVGA_3D_CMD_DX_BIND_CONTEXT = 1145,
	SVGA_3D_CMD_DX_WEADBACK_CONTEXT = 1146,
	SVGA_3D_CMD_DX_INVAWIDATE_CONTEXT = 1147,
	SVGA_3D_CMD_DX_SET_SINGWE_CONSTANT_BUFFEW = 1148,
	SVGA_3D_CMD_DX_SET_SHADEW_WESOUWCES = 1149,
	SVGA_3D_CMD_DX_SET_SHADEW = 1150,
	SVGA_3D_CMD_DX_SET_SAMPWEWS = 1151,
	SVGA_3D_CMD_DX_DWAW = 1152,
	SVGA_3D_CMD_DX_DWAW_INDEXED = 1153,
	SVGA_3D_CMD_DX_DWAW_INSTANCED = 1154,
	SVGA_3D_CMD_DX_DWAW_INDEXED_INSTANCED = 1155,
	SVGA_3D_CMD_DX_DWAW_AUTO = 1156,
	SVGA_3D_CMD_DX_SET_INPUT_WAYOUT = 1157,
	SVGA_3D_CMD_DX_SET_VEWTEX_BUFFEWS = 1158,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFEW = 1159,
	SVGA_3D_CMD_DX_SET_TOPOWOGY = 1160,
	SVGA_3D_CMD_DX_SET_WENDEWTAWGETS = 1161,
	SVGA_3D_CMD_DX_SET_BWEND_STATE = 1162,
	SVGA_3D_CMD_DX_SET_DEPTHSTENCIW_STATE = 1163,
	SVGA_3D_CMD_DX_SET_WASTEWIZEW_STATE = 1164,
	SVGA_3D_CMD_DX_DEFINE_QUEWY = 1165,
	SVGA_3D_CMD_DX_DESTWOY_QUEWY = 1166,
	SVGA_3D_CMD_DX_BIND_QUEWY = 1167,
	SVGA_3D_CMD_DX_SET_QUEWY_OFFSET = 1168,
	SVGA_3D_CMD_DX_BEGIN_QUEWY = 1169,
	SVGA_3D_CMD_DX_END_QUEWY = 1170,
	SVGA_3D_CMD_DX_WEADBACK_QUEWY = 1171,
	SVGA_3D_CMD_DX_SET_PWEDICATION = 1172,
	SVGA_3D_CMD_DX_SET_SOTAWGETS = 1173,
	SVGA_3D_CMD_DX_SET_VIEWPOWTS = 1174,
	SVGA_3D_CMD_DX_SET_SCISSOWWECTS = 1175,
	SVGA_3D_CMD_DX_CWEAW_WENDEWTAWGET_VIEW = 1176,
	SVGA_3D_CMD_DX_CWEAW_DEPTHSTENCIW_VIEW = 1177,
	SVGA_3D_CMD_DX_PWED_COPY_WEGION = 1178,
	SVGA_3D_CMD_DX_PWED_COPY = 1179,
	SVGA_3D_CMD_DX_PWESENTBWT = 1180,
	SVGA_3D_CMD_DX_GENMIPS = 1181,
	SVGA_3D_CMD_DX_UPDATE_SUBWESOUWCE = 1182,
	SVGA_3D_CMD_DX_WEADBACK_SUBWESOUWCE = 1183,
	SVGA_3D_CMD_DX_INVAWIDATE_SUBWESOUWCE = 1184,
	SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW = 1185,
	SVGA_3D_CMD_DX_DESTWOY_SHADEWWESOUWCE_VIEW = 1186,
	SVGA_3D_CMD_DX_DEFINE_WENDEWTAWGET_VIEW = 1187,
	SVGA_3D_CMD_DX_DESTWOY_WENDEWTAWGET_VIEW = 1188,
	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_VIEW = 1189,
	SVGA_3D_CMD_DX_DESTWOY_DEPTHSTENCIW_VIEW = 1190,
	SVGA_3D_CMD_DX_DEFINE_EWEMENTWAYOUT = 1191,
	SVGA_3D_CMD_DX_DESTWOY_EWEMENTWAYOUT = 1192,
	SVGA_3D_CMD_DX_DEFINE_BWEND_STATE = 1193,
	SVGA_3D_CMD_DX_DESTWOY_BWEND_STATE = 1194,
	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_STATE = 1195,
	SVGA_3D_CMD_DX_DESTWOY_DEPTHSTENCIW_STATE = 1196,
	SVGA_3D_CMD_DX_DEFINE_WASTEWIZEW_STATE = 1197,
	SVGA_3D_CMD_DX_DESTWOY_WASTEWIZEW_STATE = 1198,
	SVGA_3D_CMD_DX_DEFINE_SAMPWEW_STATE = 1199,
	SVGA_3D_CMD_DX_DESTWOY_SAMPWEW_STATE = 1200,
	SVGA_3D_CMD_DX_DEFINE_SHADEW = 1201,
	SVGA_3D_CMD_DX_DESTWOY_SHADEW = 1202,
	SVGA_3D_CMD_DX_BIND_SHADEW = 1203,
	SVGA_3D_CMD_DX_DEFINE_STWEAMOUTPUT = 1204,
	SVGA_3D_CMD_DX_DESTWOY_STWEAMOUTPUT = 1205,
	SVGA_3D_CMD_DX_SET_STWEAMOUTPUT = 1206,
	SVGA_3D_CMD_DX_SET_COTABWE = 1207,
	SVGA_3D_CMD_DX_WEADBACK_COTABWE = 1208,
	SVGA_3D_CMD_DX_BUFFEW_COPY = 1209,
	SVGA_3D_CMD_DX_TWANSFEW_FWOM_BUFFEW = 1210,
	SVGA_3D_CMD_DX_SUWFACE_COPY_AND_WEADBACK = 1211,
	SVGA_3D_CMD_DX_MOVE_QUEWY = 1212,
	SVGA_3D_CMD_DX_BIND_AWW_QUEWY = 1213,
	SVGA_3D_CMD_DX_WEADBACK_AWW_QUEWY = 1214,
	SVGA_3D_CMD_DX_PWED_TWANSFEW_FWOM_BUFFEW = 1215,
	SVGA_3D_CMD_DX_MOB_FENCE_64 = 1216,
	SVGA_3D_CMD_DX_BIND_AWW_SHADEW = 1217,
	SVGA_3D_CMD_DX_HINT = 1218,
	SVGA_3D_CMD_DX_BUFFEW_UPDATE = 1219,
	SVGA_3D_CMD_DX_SET_VS_CONSTANT_BUFFEW_OFFSET = 1220,
	SVGA_3D_CMD_DX_SET_PS_CONSTANT_BUFFEW_OFFSET = 1221,
	SVGA_3D_CMD_DX_SET_GS_CONSTANT_BUFFEW_OFFSET = 1222,
	SVGA_3D_CMD_DX_SET_HS_CONSTANT_BUFFEW_OFFSET = 1223,
	SVGA_3D_CMD_DX_SET_DS_CONSTANT_BUFFEW_OFFSET = 1224,
	SVGA_3D_CMD_DX_SET_CS_CONSTANT_BUFFEW_OFFSET = 1225,

	SVGA_3D_CMD_DX_COND_BIND_AWW_SHADEW = 1226,
	SVGA_3D_CMD_DX_MAX = 1227,

	SVGA_3D_CMD_SCWEEN_COPY = 1227,

	SVGA_3D_CMD_WESEWVED1 = 1228,
	SVGA_3D_CMD_WESEWVED2 = 1229,
	SVGA_3D_CMD_WESEWVED3 = 1230,
	SVGA_3D_CMD_WESEWVED4 = 1231,
	SVGA_3D_CMD_WESEWVED5 = 1232,
	SVGA_3D_CMD_WESEWVED6 = 1233,
	SVGA_3D_CMD_WESEWVED7 = 1234,
	SVGA_3D_CMD_WESEWVED8 = 1235,

	SVGA_3D_CMD_GWOW_OTABWE = 1236,
	SVGA_3D_CMD_DX_GWOW_COTABWE = 1237,
	SVGA_3D_CMD_INTWA_SUWFACE_COPY = 1238,

	SVGA_3D_CMD_DEFINE_GB_SUWFACE_V3 = 1239,

	SVGA_3D_CMD_DX_WESOWVE_COPY = 1240,
	SVGA_3D_CMD_DX_PWED_WESOWVE_COPY = 1241,
	SVGA_3D_CMD_DX_PWED_CONVEWT_WEGION = 1242,
	SVGA_3D_CMD_DX_PWED_CONVEWT = 1243,
	SVGA_3D_CMD_WHOWE_SUWFACE_COPY = 1244,

	SVGA_3D_CMD_DX_DEFINE_UA_VIEW = 1245,
	SVGA_3D_CMD_DX_DESTWOY_UA_VIEW = 1246,
	SVGA_3D_CMD_DX_CWEAW_UA_VIEW_UINT = 1247,
	SVGA_3D_CMD_DX_CWEAW_UA_VIEW_FWOAT = 1248,
	SVGA_3D_CMD_DX_COPY_STWUCTUWE_COUNT = 1249,
	SVGA_3D_CMD_DX_SET_UA_VIEWS = 1250,

	SVGA_3D_CMD_DX_DWAW_INDEXED_INSTANCED_INDIWECT = 1251,
	SVGA_3D_CMD_DX_DWAW_INSTANCED_INDIWECT = 1252,
	SVGA_3D_CMD_DX_DISPATCH = 1253,
	SVGA_3D_CMD_DX_DISPATCH_INDIWECT = 1254,

	SVGA_3D_CMD_WWITE_ZEWO_SUWFACE = 1255,
	SVGA_3D_CMD_UPDATE_ZEWO_SUWFACE = 1256,
	SVGA_3D_CMD_DX_TWANSFEW_TO_BUFFEW = 1257,
	SVGA_3D_CMD_DX_SET_STWUCTUWE_COUNT = 1258,

	SVGA_3D_CMD_WOGICOPS_BITBWT = 1259,
	SVGA_3D_CMD_WOGICOPS_TWANSBWT = 1260,
	SVGA_3D_CMD_WOGICOPS_STWETCHBWT = 1261,
	SVGA_3D_CMD_WOGICOPS_COWOWFIWW = 1262,
	SVGA_3D_CMD_WOGICOPS_AWPHABWEND = 1263,
	SVGA_3D_CMD_WOGICOPS_CWEAWTYPEBWEND = 1264,

	SVGA_3D_CMD_DX_COPY_COTABWE_INTO_MOB = 1265,

	SVGA_3D_CMD_UPDATE_GB_SCWEENTAWGET_V2 = 1266,

	SVGA_3D_CMD_DEFINE_GB_SUWFACE_V4 = 1267,
	SVGA_3D_CMD_DX_SET_CS_UA_VIEWS = 1268,
	SVGA_3D_CMD_DX_SET_MIN_WOD = 1269,

	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_VIEW_V2 = 1272,
	SVGA_3D_CMD_DX_DEFINE_STWEAMOUTPUT_WITH_MOB = 1273,
	SVGA_3D_CMD_DX_SET_SHADEW_IFACE = 1274,
	SVGA_3D_CMD_DX_BIND_STWEAMOUTPUT = 1275,
	SVGA_3D_CMD_SUWFACE_STWETCHBWT_NON_MS_TO_MS = 1276,
	SVGA_3D_CMD_DX_BIND_SHADEW_IFACE = 1277,

	SVGA_3D_CMD_UPDATE_GB_SCWEENTAWGET_MOVE = 1278,

	SVGA_3D_CMD_DX_PWED_STAGING_COPY = 1281,
	SVGA_3D_CMD_DX_STAGING_COPY = 1282,
	SVGA_3D_CMD_DX_PWED_STAGING_COPY_WEGION = 1283,
	SVGA_3D_CMD_DX_SET_VEWTEX_BUFFEWS_V2 = 1284,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFEW_V2 = 1285,
	SVGA_3D_CMD_DX_SET_VEWTEX_BUFFEWS_OFFSET_AND_SIZE = 1286,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFEW_OFFSET_AND_SIZE = 1287,
	SVGA_3D_CMD_DX_DEFINE_WASTEWIZEW_STATE_V2 = 1288,
	SVGA_3D_CMD_DX_PWED_STAGING_CONVEWT_WEGION = 1289,
	SVGA_3D_CMD_DX_PWED_STAGING_CONVEWT = 1290,
	SVGA_3D_CMD_DX_STAGING_BUFFEW_COPY = 1291,

	SVGA_3D_CMD_MAX = 1303,
	SVGA_3D_CMD_FUTUWE_MAX = 3000
} SVGAFifo3dCmdId;

#define SVGA_NUM_3D_CMD (SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 id;
	uint32 size;
} SVGA3dCmdHeadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 numMipWevews;
} SVGA3dSuwfaceFace;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
	SVGA3dSuwface1Fwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;

	SVGA3dSuwfaceFace face[SVGA3D_MAX_SUWFACE_FACES];

} SVGA3dCmdDefineSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
	SVGA3dSuwface1Fwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;

	SVGA3dSuwfaceFace face[SVGA3D_MAX_SUWFACE_FACES];
	uint32 muwtisampweCount;
	SVGA3dTextuweFiwtew autogenFiwtew;

} SVGA3dCmdDefineSuwface_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
} SVGA3dCmdDestwoySuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
} SVGA3dCmdDefineContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
} SVGA3dCmdDestwoyContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dCweawFwag cweawFwag;
	uint32 cowow;
	fwoat depth;
	uint32 stenciw;

} SVGA3dCmdCweaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dWightType type;
	SVGA3dBoow inWowwdSpace;
	fwoat diffuse[4];
	fwoat specuwaw[4];
	fwoat ambient[4];
	fwoat position[4];
	fwoat diwection[4];
	fwoat wange;
	fwoat fawwoff;
	fwoat attenuation0;
	fwoat attenuation1;
	fwoat attenuation2;
	fwoat theta;
	fwoat phi;
} SVGA3dWightData;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;

} SVGA3dCmdPwesent;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dWendewStateName state;
	union {
		uint32 uintVawue;
		fwoat fwoatVawue;
	};
} SVGA3dWendewState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

} SVGA3dCmdSetWendewState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dWendewTawgetType type;
	SVGA3dSuwfaceImageId tawget;
} SVGA3dCmdSetWendewTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dest;

} SVGA3dCmdSuwfaceCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId suwface;
	SVGA3dCopyBox box;
} SVGA3dCmdIntwaSuwfaceCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 swcSid;
	uint32 destSid;
} SVGA3dCmdWhoweSuwfaceCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dest;
	SVGA3dBox boxSwc;
	SVGA3dBox boxDest;
} SVGA3dCmdSuwfaceStwetchBwtNonMSToMS;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dest;
	SVGA3dBox boxSwc;
	SVGA3dBox boxDest;
	SVGA3dStwetchBwtMode mode;
} SVGA3dCmdSuwfaceStwetchBwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 discawd : 1;

	uint32 unsynchwonized : 1;

	uint32 wesewved : 30;
} SVGA3dSuwfaceDMAFwags;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAGuestImage guest;
	SVGA3dSuwfaceImageId host;
	SVGA3dTwansfewType twansfew;

} SVGA3dCmdSuwfaceDMA;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 suffixSize;

	uint32 maximumOffset;

	SVGA3dSuwfaceDMAFwags fwags;
} SVGA3dCmdSuwfaceDMASuffix;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 fiwst;
	uint32 wast;
} SVGA3dAwwayWangeHint;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 suwfaceId;
	uint32 offset;
	uint32 stwide;
} SVGA3dAwway;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dDecwType type;
	SVGA3dDecwMethod method;
	SVGA3dDecwUsage usage;
	uint32 usageIndex;
} SVGA3dVewtexAwwayIdentity;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dVewtexDecw {
	SVGA3dVewtexAwwayIdentity identity;
	SVGA3dAwway awway;
	SVGA3dAwwayWangeHint wangeHint;
} SVGA3dVewtexDecw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dPwimitiveWange {
	SVGA3dPwimitiveType pwimType;
	uint32 pwimitiveCount;

	SVGA3dAwway indexAwway;
	uint32 indexWidth;

	int32 indexBias;
} SVGA3dPwimitiveWange;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 numVewtexDecws;
	uint32 numWanges;

} SVGA3dCmdDwawPwimitives;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

	uint32 pwimitiveCount;
	uint32 stawtVewtexWocation;

	uint8 pwimitiveType;
	uint8 padding[3];
} SVGA3dCmdDwaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

	uint8 pwimitiveType;

	uint32 indexBuffewSid;
	uint32 indexBuffewOffset;

	uint8 indexBuffewStwide;

	int32 baseVewtexWocation;

	uint32 pwimitiveCount;
	uint32 pad0;
	uint16 pad1;
} SVGA3dCmdDwawIndexed;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint16 stweamOffset;
	uint8 stweam;
	uint8 type;
	uint8 method;
	uint8 usage;
	uint8 usageIndex;
	uint8 padding;

} SVGA3dVewtexEwement;
#pwagma pack(pop)

#define SVGA3D_VEWTEX_EWEMENT_WESPECT_STWEAM (1 << 7)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

	uint32 numEwements;

} SVGA3dCmdSetVewtexDecws;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
	uint32 stwide;
	uint32 offset;
} SVGA3dVewtexStweam;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

	uint32 numStweams;

} SVGA3dCmdSetVewtexStweams;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 numDivisows;
} SVGA3dCmdSetVewtexDivisows;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stage;
	SVGA3dTextuweStateName name;
	union {
		uint32 vawue;
		fwoat fwoatVawue;
	};
} SVGA3dTextuweState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;

} SVGA3dCmdSetTextuweState;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dTwansfowmType type;
	fwoat matwix[16];
} SVGA3dCmdSetTwansfowm;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	fwoat min;
	fwoat max;
} SVGA3dZWange;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dZWange zWange;
} SVGA3dCmdSetZWange;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	fwoat diffuse[4];
	fwoat ambient[4];
	fwoat specuwaw[4];
	fwoat emissive[4];
	fwoat shininess;
} SVGA3dMatewiaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dFace face;
	SVGA3dMatewiaw matewiaw;
} SVGA3dCmdSetMatewiaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 index;
	SVGA3dWightData data;
} SVGA3dCmdSetWightData;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 index;
	uint32 enabwed;
} SVGA3dCmdSetWightEnabwed;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dWect wect;
} SVGA3dCmdSetViewpowt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dWect wect;
} SVGA3dCmdSetScissowWect;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 index;
	fwoat pwane[4];
} SVGA3dCmdSetCwipPwane;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 shid;
	SVGA3dShadewType type;

} SVGA3dCmdDefineShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 shid;
	SVGA3dShadewType type;
} SVGA3dCmdDestwoyShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 weg;
	SVGA3dShadewType type;
	SVGA3dShadewConstType ctype;
	uint32 vawues[4];

} SVGA3dCmdSetShadewConst;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dShadewType type;
	uint32 shid;
} SVGA3dCmdSetShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
} SVGA3dCmdBeginQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
	SVGAGuestPtw guestWesuwt;
} SVGA3dCmdEndQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
	SVGAGuestPtw guestWesuwt;
} SVGA3dCmdWaitFowQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 totawSize;
	SVGA3dQuewyState state;
	union {
		uint32 wesuwt32;
		uint32 quewyCookie;
	};
} SVGA3dQuewyWesuwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId swcImage;
	SVGASignedWect swcWect;
	uint32 destScweenId;
	SVGASignedWect destWect;

} SVGA3dCmdBwitSuwfaceToScween;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
	SVGA3dTextuweFiwtew fiwtew;
} SVGA3dCmdGenewateMipmaps;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
} SVGA3dCmdActivateSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
} SVGA3dCmdDeactivateSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdScweenDMA {
	uint32 scweenId;
	SVGAGuestImage wefBuffew;
	SVGAGuestImage destBuffew;
	SVGAGuestImage changeMap;
} SVGA3dCmdScweenDMA;
#pwagma pack(pop)

#define SVGA3D_WOTWANSBWT_HONOWAWPHA (0x01)
#define SVGA3D_WOSTWETCHBWT_MIWWOWX (0x01)
#define SVGA3D_WOSTWETCHBWT_MIWWOWY (0x02)
#define SVGA3D_WOAWPHABWEND_SWCHASAWPHA (0x01)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsBitBwt {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dst;
	SVGA3dWogicOp wogicOp;
	SVGA3dWogicOpWop3 wogicOpWop3;

} SVGA3dCmdWogicOpsBitBwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsTwansBwt {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dst;
	uint32 cowow;
	uint32 fwags;
	SVGA3dBox swcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox cwipBox;
} SVGA3dCmdWogicOpsTwansBwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsStwetchBwt {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dst;
	uint16 mode;
	uint16 fwags;
	SVGA3dBox swcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox cwipBox;
} SVGA3dCmdWogicOpsStwetchBwt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsCowowFiww {
	SVGA3dSuwfaceImageId dst;
	uint32 cowow;
	SVGA3dWogicOp wogicOp;
	SVGA3dWogicOpWop3 wogicOpWop3;

} SVGA3dCmdWogicOpsCowowFiww;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsAwphaBwend {
	SVGA3dSuwfaceImageId swc;
	SVGA3dSuwfaceImageId dst;
	uint32 awphaVaw;
	uint32 fwags;
	SVGA3dBox swcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox cwipBox;
} SVGA3dCmdWogicOpsAwphaBwend;
#pwagma pack(pop)

#define SVGA3D_CWEAWTYPE_INVAWID_GAMMA_INDEX 0xFFFFFFFF

#define SVGA3D_CWEAWTYPE_GAMMA_WIDTH 512
#define SVGA3D_CWEAWTYPE_GAMMA_HEIGHT 16

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWogicOpsCweawTypeBwend {
	SVGA3dSuwfaceImageId tmp;
	SVGA3dSuwfaceImageId dst;
	SVGA3dSuwfaceImageId gammaSuwf;
	SVGA3dSuwfaceImageId awphaSuwf;
	uint32 gamma;
	uint32 cowow;
	uint32 cowow2;
	int32 awphaOffsetX;
	int32 awphaOffsetY;

} SVGA3dCmdWogicOpsCweawTypeBwend;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAMobFowmat ptDepth;
	uint32 sizeInBytes;
	PPN64 base;
} SVGAOTabweMobEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dSuwface1Fwags suwface1Fwags;
	uint32 numMipWevews;
	uint32 muwtisampweCount;
	SVGA3dTextuweFiwtew autogenFiwtew;
	SVGA3dSize size;
	SVGAMobId mobid;
	uint32 awwaySize;
	uint32 mobPitch;
	SVGA3dSuwface2Fwags suwface2Fwags;
	uint8 muwtisampwePattewn;
	uint8 quawityWevew;
	uint16 buffewByteStwide;
	fwoat minWOD;
	uint32 pad0[2];
} SVGAOTabweSuwfaceEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGAMobId mobid;
} SVGAOTabweContextEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dShadewType type;
	uint32 sizeInBytes;
	uint32 offsetInBytes;
	SVGAMobId mobid;
} SVGAOTabweShadewEntwy;
#pwagma pack(pop)

#define SVGA_STFWAG_PWIMAWY (1 << 0)
#define SVGA_STFWAG_WESEWVED (1 << 1)
typedef uint32 SVGAScweenTawgetFwags;

#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dSuwfaceImageId image;
	uint32 width;
	uint32 height;
	int32 xWoot;
	int32 yWoot;
	SVGAScweenTawgetFwags fwags;
	uint32 dpi;
	uint32 pad[7];
} SVGAOTabweScweenTawgetEntwy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	fwoat vawue[4];
} SVGA3dShadewConstFwoat;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	int32 vawue[4];
} SVGA3dShadewConstInt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 vawue;
} SVGA3dShadewConstBoow;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint16 stweamOffset;
	uint8 stweam;
	uint8 type;
	uint8 methodUsage;
	uint8 usageIndex;
} SVGAGBVewtexEwement;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
	uint16 stwide;
	uint32 offset;
} SVGAGBVewtexStweam;
#pwagma pack(pop)
#pwagma pack(push, 1)
typedef stwuct {
	SVGA3dWect viewpowt;
	SVGA3dWect scissowWect;
	SVGA3dZWange zWange;

	SVGA3dSuwfaceImageId wendewTawgets[SVGA3D_WT_MAX];
	SVGAGBVewtexEwement decw1[4];

	uint32 wendewStates[SVGA3D_WS_MAX];
	SVGAGBVewtexEwement decw2[18];
	uint32 pad0[2];

	stwuct {
		SVGA3dFace face;
		SVGA3dMatewiaw matewiaw;
	} matewiaw;

	fwoat cwipPwanes[SVGA3D_MAX_CWIP_PWANES][4];
	fwoat matwices[SVGA3D_TWANSFOWM_MAX][16];

	SVGA3dBoow wightEnabwed[SVGA3D_NUM_WIGHTS];
	SVGA3dWightData wightData[SVGA3D_NUM_WIGHTS];

	uint32 shadews[SVGA3D_NUM_SHADEWTYPE_PWEDX];
	SVGAGBVewtexEwement decw3[10];
	uint32 pad1[3];

	uint32 occQuewyActive;
	uint32 occQuewyVawue;

	SVGA3dShadewConstInt pShadewIVawues[SVGA3D_CONSTINTWEG_MAX];
	SVGA3dShadewConstInt vShadewIVawues[SVGA3D_CONSTINTWEG_MAX];
	uint16 pShadewBVawues;
	uint16 vShadewBVawues;

	SVGAGBVewtexStweam stweams[SVGA3D_MAX_VEWTEX_AWWAYS];
	SVGA3dVewtexDivisow divisows[SVGA3D_MAX_VEWTEX_AWWAYS];
	uint32 numVewtexDecws;
	uint32 numVewtexStweams;
	uint32 numVewtexDivisows;
	uint32 pad2[30];

	uint32 tsCowowKey[SVGA3D_NUM_TEXTUWE_UNITS];
	uint32 textuweStages[SVGA3D_NUM_TEXTUWE_UNITS][SVGA3D_TS_CONSTANT + 1];
	uint32 tsCowowKeyEnabwe[SVGA3D_NUM_TEXTUWE_UNITS];

	SVGA3dShadewConstFwoat pShadewFVawues[SVGA3D_CONSTWEG_MAX];
	SVGA3dShadewConstFwoat vShadewFVawues[SVGA3D_CONSTWEG_MAX];
} SVGAGBContextData;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAOTabweType type;
	PPN32 baseAddwess;
	uint32 sizeInBytes;
	uint32 vawidSizeInBytes;
	SVGAMobFowmat ptDepth;
} SVGA3dCmdSetOTabweBase;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAOTabweType type;
	PPN64 baseAddwess;
	uint32 sizeInBytes;
	uint32 vawidSizeInBytes;
	SVGAMobFowmat ptDepth;
} SVGA3dCmdSetOTabweBase64;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAOTabweType type;
	PPN64 baseAddwess;
	uint32 sizeInBytes;
	uint32 vawidSizeInBytes;
	SVGAMobFowmat ptDepth;
} SVGA3dCmdGwowOTabwe;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAOTabweType type;
} SVGA3dCmdWeadbackOTabwe;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBMob {
	SVGAMobId mobid;
	SVGAMobFowmat ptDepth;
	PPN32 base;
	uint32 sizeInBytes;
} SVGA3dCmdDefineGBMob;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDestwoyGBMob {
	SVGAMobId mobid;
} SVGA3dCmdDestwoyGBMob;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBMob64 {
	SVGAMobId mobid;
	SVGAMobFowmat ptDepth;
	PPN64 base;
	uint32 sizeInBytes;
} SVGA3dCmdDefineGBMob64;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWedefineGBMob64 {
	SVGAMobId mobid;
	SVGAMobFowmat ptDepth;
	PPN64 base;
	uint32 sizeInBytes;
} SVGA3dCmdWedefineGBMob64;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdUpdateGBMobMapping {
	SVGAMobId mobid;
} SVGA3dCmdUpdateGBMobMapping;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBSuwface {
	uint32 sid;
	SVGA3dSuwface1Fwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 numMipWevews;
	uint32 muwtisampweCount;
	SVGA3dTextuweFiwtew autogenFiwtew;
	SVGA3dSize size;
} SVGA3dCmdDefineGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBSuwface_v2 {
	uint32 sid;
	SVGA3dSuwface1Fwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 numMipWevews;
	uint32 muwtisampweCount;
	SVGA3dTextuweFiwtew autogenFiwtew;
	SVGA3dSize size;
	uint32 awwaySize;
	uint32 pad;
} SVGA3dCmdDefineGBSuwface_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBSuwface_v3 {
	uint32 sid;
	SVGA3dSuwfaceAwwFwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 numMipWevews;
	uint32 muwtisampweCount;
	SVGA3dMSPattewn muwtisampwePattewn;
	SVGA3dMSQuawityWevew quawityWevew;
	SVGA3dTextuweFiwtew autogenFiwtew;
	SVGA3dSize size;
	uint32 awwaySize;
} SVGA3dCmdDefineGBSuwface_v3;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBSuwface_v4 {
	uint32 sid;
	SVGA3dSuwfaceAwwFwags suwfaceFwags;
	SVGA3dSuwfaceFowmat fowmat;
	uint32 numMipWevews;
	uint32 muwtisampweCount;
	SVGA3dMSPattewn muwtisampwePattewn;
	SVGA3dMSQuawityWevew quawityWevew;
	SVGA3dTextuweFiwtew autogenFiwtew;
	SVGA3dSize size;
	uint32 awwaySize;
	uint32 buffewByteStwide;
} SVGA3dCmdDefineGBSuwface_v4;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDestwoyGBSuwface {
	uint32 sid;
} SVGA3dCmdDestwoyGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdBindGBSuwface {
	uint32 sid;
	SVGAMobId mobid;
} SVGA3dCmdBindGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdBindGBSuwfaceWithPitch {
	uint32 sid;
	SVGAMobId mobid;
	uint32 baseWevewPitch;
} SVGA3dCmdBindGBSuwfaceWithPitch;
#pwagma pack(pop)

#define SVGA3D_COND_BIND_GB_SUWFACE_FWAG_WEADBACK (1 << 0)
#define SVGA3D_COND_BIND_GB_SUWFACE_FWAG_UPDATE (1 << 1)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdCondBindGBSuwface {
	uint32 sid;
	SVGAMobId testMobid;
	SVGAMobId mobid;
	uint32 fwags;
} SVGA3dCmdCondBindGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdUpdateGBImage {
	SVGA3dSuwfaceImageId image;
	SVGA3dBox box;
} SVGA3dCmdUpdateGBImage;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdUpdateGBSuwface {
	uint32 sid;
} SVGA3dCmdUpdateGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWeadbackGBImage {
	SVGA3dSuwfaceImageId image;
} SVGA3dCmdWeadbackGBImage;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWeadbackGBSuwface {
	uint32 sid;
} SVGA3dCmdWeadbackGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWeadbackGBImagePawtiaw {
	SVGA3dSuwfaceImageId image;
	SVGA3dBox box;
	uint32 invewtBox;
} SVGA3dCmdWeadbackGBImagePawtiaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdInvawidateGBImage {
	SVGA3dSuwfaceImageId image;
} SVGA3dCmdInvawidateGBImage;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdInvawidateGBSuwface {
	uint32 sid;
} SVGA3dCmdInvawidateGBSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdInvawidateGBImagePawtiaw {
	SVGA3dSuwfaceImageId image;
	SVGA3dBox box;
	uint32 invewtBox;
} SVGA3dCmdInvawidateGBImagePawtiaw;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBContext {
	uint32 cid;
} SVGA3dCmdDefineGBContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDestwoyGBContext {
	uint32 cid;
} SVGA3dCmdDestwoyGBContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdBindGBContext {
	uint32 cid;
	SVGAMobId mobid;
	uint32 vawidContents;
} SVGA3dCmdBindGBContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdWeadbackGBContext {
	uint32 cid;
} SVGA3dCmdWeadbackGBContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdInvawidateGBContext {
	uint32 cid;
} SVGA3dCmdInvawidateGBContext;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDefineGBShadew {
	uint32 shid;
	SVGA3dShadewType type;
	uint32 sizeInBytes;
} SVGA3dCmdDefineGBShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdBindGBShadew {
	uint32 shid;
	SVGAMobId mobid;
	uint32 offsetInBytes;
} SVGA3dCmdBindGBShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdDestwoyGBShadew {
	uint32 shid;
} SVGA3dCmdDestwoyGBShadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	uint32 wegStawt;
	SVGA3dShadewType shadewType;
	SVGA3dShadewConstType constType;

} SVGA3dCmdSetGBShadewConstInwine;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
} SVGA3dCmdBeginGBQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
	SVGAMobId mobid;
	uint32 offset;
} SVGA3dCmdEndGBQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cid;
	SVGA3dQuewyType type;
	SVGAMobId mobid;
	uint32 offset;
} SVGA3dCmdWaitFowGBQuewy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAMobId mobid;
	uint32 mustBeZewo;
	uint32 initiawized;
} SVGA3dCmdEnabweGawt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAMobId mobid;
	uint32 gawtOffset;
} SVGA3dCmdMapMobIntoGawt;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 gawtOffset;
	uint32 numPages;
} SVGA3dCmdUnmapGawtWange;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	uint32 width;
	uint32 height;
	int32 xWoot;
	int32 yWoot;
	SVGAScweenTawgetFwags fwags;

	uint32 dpi;
} SVGA3dCmdDefineGBScweenTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
} SVGA3dCmdDestwoyGBScweenTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	SVGA3dSuwfaceImageId image;
} SVGA3dCmdBindGBScweenTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	SVGA3dWect wect;
} SVGA3dCmdUpdateGBScweenTawget;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	SVGA3dWect wect;
	SVGA3dFwameUpdateType type;
} SVGA3dCmdUpdateGBScweenTawget_v2;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	SVGA3dWect wect;
	SVGA3dFwameUpdateType type;
	SVGAUnsignedPoint swcPoint;
} SVGA3dCmdUpdateGBScweenTawgetMove;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGA3dCmdGBScweenDMA {
	uint32 scweenId;
	uint32 dead;
	SVGAMobId destMobID;
	uint32 destPitch;
	SVGAMobId changeMapMobID;
} SVGA3dCmdGBScweenDMA;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 vawue;
	uint32 mobId;
	uint32 mobOffset;
} SVGA3dCmdGBMobFence;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stid;
	SVGA3dSuwfaceImageId dest;

	uint32 statusMobId;
	uint32 statusMobOffset;

	uint32 mustBeInvawidId;
	uint32 mustBeZewo;
} SVGA3dCmdScweenCopy;
#pwagma pack(pop)

#define SVGA_SCWEEN_COPY_STATUS_FAIWUWE 0x00
#define SVGA_SCWEEN_COPY_STATUS_SUCCESS 0x01
#define SVGA_SCWEEN_COPY_STATUS_INVAWID 0xFFFFFFFF

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
} SVGA3dCmdWwiteZewoSuwface;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 sid;
} SVGA3dCmdUpdateZewoSuwface;
#pwagma pack(pop)

#endif
