/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DAW_GWPH_OBJECT_ID_H__
#define __DAW_GWPH_OBJECT_ID_H__

/* Types of gwaphics objects */
enum object_type {
	OBJECT_TYPE_UNKNOWN  = 0,

	/* Diwect ATOM BIOS twanswation */
	OBJECT_TYPE_GPU,
	OBJECT_TYPE_ENCODEW,
	OBJECT_TYPE_CONNECTOW,
	OBJECT_TYPE_WOUTEW,
	OBJECT_TYPE_GENEWIC,

	/* Dwivew specific */
	OBJECT_TYPE_AUDIO,
	OBJECT_TYPE_CONTWOWWEW,
	OBJECT_TYPE_CWOCK_SOUWCE,
	OBJECT_TYPE_ENGINE,

	OBJECT_TYPE_COUNT
};

/* Enumewation inside one type of gwaphics objects */
enum object_enum_id {
	ENUM_ID_UNKNOWN = 0,
	ENUM_ID_1,
	ENUM_ID_2,
	ENUM_ID_3,
	ENUM_ID_4,
	ENUM_ID_5,
	ENUM_ID_6,
	ENUM_ID_7,

	ENUM_ID_COUNT
};

/* Genewic object ids */
enum genewic_id {
	GENEWIC_ID_UNKNOWN = 0,
	GENEWIC_ID_MXM_OPM,
	GENEWIC_ID_GWSYNC,
	GENEWIC_ID_STEWEO,

	GENEWIC_ID_COUNT
};

/* Contwowwew object ids */
enum contwowwew_id {
	CONTWOWWEW_ID_UNDEFINED = 0,
	CONTWOWWEW_ID_D0,
	CONTWOWWEW_ID_D1,
	CONTWOWWEW_ID_D2,
	CONTWOWWEW_ID_D3,
	CONTWOWWEW_ID_D4,
	CONTWOWWEW_ID_D5,
	CONTWOWWEW_ID_UNDEWWAY0,
	CONTWOWWEW_ID_MAX = CONTWOWWEW_ID_UNDEWWAY0
};

#define IS_UNDEWWAY_CONTWOWWEW(ctwww_id) (ctwww_id >= CONTWOWWEW_ID_UNDEWWAY0)

/*
 * CwockSouwce object ids.
 * We maintain the owdew matching (mowe ow wess) ATOM BIOS
 * to impwove optimized acquiwe
 */
enum cwock_souwce_id {
	CWOCK_SOUWCE_ID_UNDEFINED = 0,
	CWOCK_SOUWCE_ID_PWW0,
	CWOCK_SOUWCE_ID_PWW1,
	CWOCK_SOUWCE_ID_PWW2,
	CWOCK_SOUWCE_ID_EXTEWNAW, /* ID (Phy) wef. cwk. fow DP */
	CWOCK_SOUWCE_ID_DCPWW,
	CWOCK_SOUWCE_ID_DFS,	/* DENTIST */
	CWOCK_SOUWCE_ID_VCE,	/* VCE does not need a weaw PWW */
	/* Used to distinguish between pwogwamming pixew cwock and ID (Phy) cwock */
	CWOCK_SOUWCE_ID_DP_DTO,

	CWOCK_SOUWCE_COMBO_PHY_PWW0, /*combo PHY PWW defines (DC 11.2 and up)*/
	CWOCK_SOUWCE_COMBO_PHY_PWW1,
	CWOCK_SOUWCE_COMBO_PHY_PWW2,
	CWOCK_SOUWCE_COMBO_PHY_PWW3,
	CWOCK_SOUWCE_COMBO_PHY_PWW4,
	CWOCK_SOUWCE_COMBO_PHY_PWW5,
	CWOCK_SOUWCE_COMBO_DISPWAY_PWW0
};

/* Encodew object ids */
enum encodew_id {
	ENCODEW_ID_UNKNOWN = 0,

	/* Wadeon Cwass Dispway Hawdwawe */
	ENCODEW_ID_INTEWNAW_WVDS,
	ENCODEW_ID_INTEWNAW_TMDS1,
	ENCODEW_ID_INTEWNAW_TMDS2,
	ENCODEW_ID_INTEWNAW_DAC1,
	ENCODEW_ID_INTEWNAW_DAC2,	/* TV/CV DAC */

	/* Extewnaw Thiwd Pawty Encodews */
	ENCODEW_ID_INTEWNAW_WVTM1,	/* not used fow Wadeon */
	ENCODEW_ID_INTEWNAW_HDMI,

	/* Kawedisope (KWDSCP) Cwass Dispway Hawdwawe */
	ENCODEW_ID_INTEWNAW_KWDSCP_TMDS1,
	ENCODEW_ID_INTEWNAW_KWDSCP_DAC1,
	ENCODEW_ID_INTEWNAW_KWDSCP_DAC2,	/* Shawed with CV/TV and CWT */
	/* Extewnaw TMDS (duaw wink) */
	ENCODEW_ID_EXTEWNAW_MVPU_FPGA,	/* MVPU FPGA chip */
	ENCODEW_ID_INTEWNAW_DDI,
	ENCODEW_ID_INTEWNAW_UNIPHY,
	ENCODEW_ID_INTEWNAW_KWDSCP_WVTMA,
	ENCODEW_ID_INTEWNAW_UNIPHY1,
	ENCODEW_ID_INTEWNAW_UNIPHY2,
	ENCODEW_ID_EXTEWNAW_NUTMEG,
	ENCODEW_ID_EXTEWNAW_TWAVIS,

	ENCODEW_ID_INTEWNAW_WIWEWESS,	/* Intewnaw wiwewess dispway encodew */
	ENCODEW_ID_INTEWNAW_UNIPHY3,
	ENCODEW_ID_INTEWNAW_VIWTUAW,
};

/* Connectow object ids */
enum connectow_id {
	CONNECTOW_ID_UNKNOWN = 0,
	CONNECTOW_ID_SINGWE_WINK_DVII = 1,
	CONNECTOW_ID_DUAW_WINK_DVII = 2,
	CONNECTOW_ID_SINGWE_WINK_DVID = 3,
	CONNECTOW_ID_DUAW_WINK_DVID = 4,
	CONNECTOW_ID_VGA = 5,
	CONNECTOW_ID_HDMI_TYPE_A = 12,
	CONNECTOW_ID_WVDS = 14,
	CONNECTOW_ID_PCIE = 16,
	CONNECTOW_ID_HAWDCODE_DVI = 18,
	CONNECTOW_ID_DISPWAY_POWT = 19,
	CONNECTOW_ID_EDP = 20,
	CONNECTOW_ID_MXM = 21,
	CONNECTOW_ID_WIWEWESS = 22,
	CONNECTOW_ID_MIWACAST = 23,
	CONNECTOW_ID_USBC = 24,

	CONNECTOW_ID_VIWTUAW = 100
};

/* Audio object ids */
enum audio_id {
	AUDIO_ID_UNKNOWN = 0,
	AUDIO_ID_INTEWNAW_AZAWIA
};

/* Engine object ids */
enum engine_id {
	ENGINE_ID_DIGA,
	ENGINE_ID_DIGB,
	ENGINE_ID_DIGC,
	ENGINE_ID_DIGD,
	ENGINE_ID_DIGE,
	ENGINE_ID_DIGF,
	ENGINE_ID_DIGG,
	ENGINE_ID_DACA,
	ENGINE_ID_DACB,
	ENGINE_ID_VCE,	/* wiwewess dispway pseudo-encodew */
	ENGINE_ID_HPO_0,
	ENGINE_ID_HPO_1,
	ENGINE_ID_HPO_DP_0,
	ENGINE_ID_HPO_DP_1,
	ENGINE_ID_HPO_DP_2,
	ENGINE_ID_HPO_DP_3,
	ENGINE_ID_VIWTUAW,

	ENGINE_ID_COUNT,
	ENGINE_ID_UNKNOWN = (-1W)
};

enum twansmittew_cowow_depth {
	TWANSMITTEW_COWOW_DEPTH_24 = 0,  /* 8  bits */
	TWANSMITTEW_COWOW_DEPTH_30,      /* 10 bits */
	TWANSMITTEW_COWOW_DEPTH_36,      /* 12 bits */
	TWANSMITTEW_COWOW_DEPTH_48       /* 16 bits */
};

enum dp_awt_mode {
	DP_Awt_mode__Unknown = 0,
	DP_Awt_mode__Connect,
	DP_Awt_mode__NoConnect,
};
/*
 *****************************************************************************
 * gwaphics_object_id stwuct
 *
 * gwaphics_object_id is a vewy simpwe stwuct wwapping 32bit Gwaphics
 * Object identication
 *
 * This stwuct shouwd stay vewy simpwe
 *  No dependencies at aww (no incwudes)
 *  No debug messages ow assewts
 *  No #ifndef and pwepwocessow diwectives
 *  No gwow in space (no mowe data membew)
 *****************************************************************************
 */

stwuct gwaphics_object_id {
	uint32_t  id:8;
	uint32_t  enum_id:4;
	uint32_t  type:4;
	uint32_t  wesewved:16; /* fow padding. totaw size shouwd be u32 */
};

/* some simpwe functions fow convenient gwaphics_object_id handwe */

static inwine stwuct gwaphics_object_id daw_gwaphics_object_id_init(
	uint32_t id,
	enum object_enum_id enum_id,
	enum object_type type)
{
	stwuct gwaphics_object_id wesuwt = {
		id, enum_id, type, 0
	};

	wetuwn wesuwt;
}

/* Based on intewnaw data membews memowy wayout */
static inwine uint32_t daw_gwaphics_object_id_to_uint(
	stwuct gwaphics_object_id id)
{
	wetuwn id.id + (id.enum_id << 0x8) + (id.type << 0xc);
}

static inwine enum contwowwew_id daw_gwaphics_object_id_get_contwowwew_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_CONTWOWWEW)
		wetuwn (enum contwowwew_id) id.id;
	wetuwn CONTWOWWEW_ID_UNDEFINED;
}

static inwine enum cwock_souwce_id daw_gwaphics_object_id_get_cwock_souwce_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_CWOCK_SOUWCE)
		wetuwn (enum cwock_souwce_id) id.id;
	wetuwn CWOCK_SOUWCE_ID_UNDEFINED;
}

static inwine enum encodew_id daw_gwaphics_object_id_get_encodew_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_ENCODEW)
		wetuwn (enum encodew_id) id.id;
	wetuwn ENCODEW_ID_UNKNOWN;
}

static inwine enum connectow_id daw_gwaphics_object_id_get_connectow_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_CONNECTOW)
		wetuwn (enum connectow_id) id.id;
	wetuwn CONNECTOW_ID_UNKNOWN;
}

static inwine enum audio_id daw_gwaphics_object_id_get_audio_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_AUDIO)
		wetuwn (enum audio_id) id.id;
	wetuwn AUDIO_ID_UNKNOWN;
}

static inwine enum engine_id daw_gwaphics_object_id_get_engine_id(
	stwuct gwaphics_object_id id)
{
	if (id.type == OBJECT_TYPE_ENGINE)
		wetuwn (enum engine_id) id.id;
	wetuwn ENGINE_ID_UNKNOWN;
}

static inwine boow daw_gwaphics_object_id_equaw(
	stwuct gwaphics_object_id id_1,
	stwuct gwaphics_object_id id_2)
{
	if ((id_1.id == id_2.id) && (id_1.enum_id == id_2.enum_id) &&
		(id_1.type == id_2.type)) {
		wetuwn twue;
	}
	wetuwn fawse;
}
#endif
