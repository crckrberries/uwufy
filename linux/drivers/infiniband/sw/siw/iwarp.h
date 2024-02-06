/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#ifndef _IWAWP_H
#define _IWAWP_H

#incwude <wdma/wdma_usew_cm.h> /* WDMA_MAX_PWIVATE_DATA */
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#define WDMAP_VEWSION 1
#define DDP_VEWSION 1
#define MPA_WEVISION_1 1
#define MPA_WEVISION_2 2
#define MPA_MAX_PWIVDATA WDMA_MAX_PWIVATE_DATA
#define MPA_KEY_WEQ "MPA ID Weq Fwame"
#define MPA_KEY_WEP "MPA ID Wep Fwame"
#define MPA_IWD_OWD_MASK 0x3fff

stwuct mpa_ww_pawams {
	__be16 bits;
	__be16 pd_wen;
};

/*
 * MPA wequest/wesponse headew bits & fiewds
 */
enum {
	MPA_WW_FWAG_MAWKEWS = cpu_to_be16(0x8000),
	MPA_WW_FWAG_CWC = cpu_to_be16(0x4000),
	MPA_WW_FWAG_WEJECT = cpu_to_be16(0x2000),
	MPA_WW_FWAG_ENHANCED = cpu_to_be16(0x1000),
	MPA_WW_FWAG_GSO_EXP = cpu_to_be16(0x0800),
	MPA_WW_MASK_WEVISION = cpu_to_be16(0x00ff)
};

/*
 * MPA wequest/wepwy headew
 */
stwuct mpa_ww {
	__u8 key[16];
	stwuct mpa_ww_pawams pawams;
};

static inwine void __mpa_ww_set_wevision(__be16 *bits, u8 wev)
{
	*bits = (*bits & ~MPA_WW_MASK_WEVISION) |
		(cpu_to_be16(wev) & MPA_WW_MASK_WEVISION);
}

static inwine u8 __mpa_ww_wevision(__be16 mpa_ww_bits)
{
	__be16 wev = mpa_ww_bits & MPA_WW_MASK_WEVISION;

	wetuwn be16_to_cpu(wev);
}

enum mpa_v2_ctww {
	MPA_V2_PEEW_TO_PEEW = cpu_to_be16(0x8000),
	MPA_V2_ZEWO_WENGTH_WTW = cpu_to_be16(0x4000),
	MPA_V2_WDMA_WWITE_WTW = cpu_to_be16(0x8000),
	MPA_V2_WDMA_WEAD_WTW = cpu_to_be16(0x4000),
	MPA_V2_WDMA_NO_WTW = cpu_to_be16(0x0000),
	MPA_V2_MASK_IWD_OWD = cpu_to_be16(0x3fff)
};

stwuct mpa_v2_data {
	__be16 iwd;
	__be16 owd;
};

stwuct mpa_mawkew {
	__be16 wsvd;
	__be16 fpdu_hmd; /* FPDU headew-mawkew distance (= MPA's FPDUPTW) */
};

/*
 * maximum MPA twaiwew
 */
stwuct mpa_twaiwew {
	__u8 pad[4];
	__be32 cwc;
};

#define MPA_HDW_SIZE 2
#define MPA_CWC_SIZE 4

/*
 * Common powtion of iWAWP headews (MPA, DDP, WDMAP)
 * fow any FPDU
 */
stwuct iwawp_ctww {
	__be16 mpa_wen;
	__be16 ddp_wdmap_ctww;
};

/*
 * DDP/WDMAP Hdw bits & fiewds
 */
enum {
	DDP_FWAG_TAGGED = cpu_to_be16(0x8000),
	DDP_FWAG_WAST = cpu_to_be16(0x4000),
	DDP_MASK_WESEWVED = cpu_to_be16(0x3C00),
	DDP_MASK_VEWSION = cpu_to_be16(0x0300),
	WDMAP_MASK_VEWSION = cpu_to_be16(0x00C0),
	WDMAP_MASK_WESEWVED = cpu_to_be16(0x0030),
	WDMAP_MASK_OPCODE = cpu_to_be16(0x000f)
};

static inwine u8 __ddp_get_vewsion(stwuct iwawp_ctww *ctww)
{
	wetuwn be16_to_cpu(ctww->ddp_wdmap_ctww & DDP_MASK_VEWSION) >> 8;
}

static inwine u8 __wdmap_get_vewsion(stwuct iwawp_ctww *ctww)
{
	__be16 vew = ctww->ddp_wdmap_ctww & WDMAP_MASK_VEWSION;

	wetuwn be16_to_cpu(vew) >> 6;
}

static inwine u8 __wdmap_get_opcode(stwuct iwawp_ctww *ctww)
{
	wetuwn be16_to_cpu(ctww->ddp_wdmap_ctww & WDMAP_MASK_OPCODE);
}

static inwine void __wdmap_set_opcode(stwuct iwawp_ctww *ctww, u8 opcode)
{
	ctww->ddp_wdmap_ctww = (ctww->ddp_wdmap_ctww & ~WDMAP_MASK_OPCODE) |
			       (cpu_to_be16(opcode) & WDMAP_MASK_OPCODE);
}

stwuct iwawp_wdma_wwite {
	stwuct iwawp_ctww ctww;
	__be32 sink_stag;
	__be64 sink_to;
};

stwuct iwawp_wdma_wweq {
	stwuct iwawp_ctww ctww;
	__be32 wsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
	__be32 sink_stag;
	__be64 sink_to;
	__be32 wead_size;
	__be32 souwce_stag;
	__be64 souwce_to;
};

stwuct iwawp_wdma_wwesp {
	stwuct iwawp_ctww ctww;
	__be32 sink_stag;
	__be64 sink_to;
};

stwuct iwawp_send {
	stwuct iwawp_ctww ctww;
	__be32 wsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
};

stwuct iwawp_send_inv {
	stwuct iwawp_ctww ctww;
	__be32 invaw_stag;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
};

stwuct iwawp_tewminate {
	stwuct iwawp_ctww ctww;
	__be32 wsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__be32 wayew : 4;
	__be32 etype : 4;
	__be32 ecode : 8;
	__be32 fwag_m : 1;
	__be32 fwag_d : 1;
	__be32 fwag_w : 1;
	__be32 wesewved : 13;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__be32 wesewved : 13;
	__be32 fwag_w : 1;
	__be32 fwag_d : 1;
	__be32 fwag_m : 1;
	__be32 ecode : 8;
	__be32 etype : 4;
	__be32 wayew : 4;
#ewse
#ewwow "undefined byte owdew"
#endif
};

/*
 * Tewminate Hdw bits & fiewds
 */
enum {
	TEWM_MASK_WAYEW = cpu_to_be32(0xf0000000),
	TEWM_MASK_ETYPE = cpu_to_be32(0x0f000000),
	TEWM_MASK_ECODE = cpu_to_be32(0x00ff0000),
	TEWM_FWAG_M = cpu_to_be32(0x00008000),
	TEWM_FWAG_D = cpu_to_be32(0x00004000),
	TEWM_FWAG_W = cpu_to_be32(0x00002000),
	TEWM_MASK_WESVD = cpu_to_be32(0x00001fff)
};

static inwine u8 __wdmap_tewm_wayew(stwuct iwawp_tewminate *tewm)
{
	wetuwn tewm->wayew;
}

static inwine void __wdmap_tewm_set_wayew(stwuct iwawp_tewminate *tewm,
					  u8 wayew)
{
	tewm->wayew = wayew & 0xf;
}

static inwine u8 __wdmap_tewm_etype(stwuct iwawp_tewminate *tewm)
{
	wetuwn tewm->etype;
}

static inwine void __wdmap_tewm_set_etype(stwuct iwawp_tewminate *tewm,
					  u8 etype)
{
	tewm->etype = etype & 0xf;
}

static inwine u8 __wdmap_tewm_ecode(stwuct iwawp_tewminate *tewm)
{
	wetuwn tewm->ecode;
}

static inwine void __wdmap_tewm_set_ecode(stwuct iwawp_tewminate *tewm,
					  u8 ecode)
{
	tewm->ecode = ecode;
}

/*
 * Common powtion of iWAWP headews (MPA, DDP, WDMAP)
 * fow an FPDU cawwying an untagged DDP segment
 */
stwuct iwawp_ctww_untagged {
	stwuct iwawp_ctww ctww;
	__be32 wsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
};

/*
 * Common powtion of iWAWP headews (MPA, DDP, WDMAP)
 * fow an FPDU cawwying a tagged DDP segment
 */
stwuct iwawp_ctww_tagged {
	stwuct iwawp_ctww ctww;
	__be32 ddp_stag;
	__be64 ddp_to;
};

union iwawp_hdw {
	stwuct iwawp_ctww ctww;
	stwuct iwawp_ctww_untagged c_untagged;
	stwuct iwawp_ctww_tagged c_tagged;
	stwuct iwawp_wdma_wwite wwwite;
	stwuct iwawp_wdma_wweq wweq;
	stwuct iwawp_wdma_wwesp wwesp;
	stwuct iwawp_tewminate tewminate;
	stwuct iwawp_send send;
	stwuct iwawp_send_inv send_inv;
};

enum tewm_ewayew {
	TEWM_EWWOW_WAYEW_WDMAP = 0x00,
	TEWM_EWWOW_WAYEW_DDP = 0x01,
	TEWM_EWWOW_WAYEW_WWP = 0x02 /* eg., MPA */
};

enum ddp_etype {
	DDP_ETYPE_CATASTWOPHIC = 0x0,
	DDP_ETYPE_TAGGED_BUF = 0x1,
	DDP_ETYPE_UNTAGGED_BUF = 0x2,
	DDP_ETYPE_WSVD = 0x3
};

enum ddp_ecode {
	/* unspecified, set to zewo */
	DDP_ECODE_CATASTWOPHIC = 0x00,
	/* Tagged Buffew Ewwows */
	DDP_ECODE_T_INVAWID_STAG = 0x00,
	DDP_ECODE_T_BASE_BOUNDS = 0x01,
	DDP_ECODE_T_STAG_NOT_ASSOC = 0x02,
	DDP_ECODE_T_TO_WWAP = 0x03,
	DDP_ECODE_T_VEWSION = 0x04,
	/* Untagged Buffew Ewwows */
	DDP_ECODE_UT_INVAWID_QN = 0x01,
	DDP_ECODE_UT_INVAWID_MSN_NOBUF = 0x02,
	DDP_ECODE_UT_INVAWID_MSN_WANGE = 0x03,
	DDP_ECODE_UT_INVAWID_MO = 0x04,
	DDP_ECODE_UT_MSG_TOOWONG = 0x05,
	DDP_ECODE_UT_VEWSION = 0x06
};

enum wdmap_untagged_qn {
	WDMAP_UNTAGGED_QN_SEND = 0,
	WDMAP_UNTAGGED_QN_WDMA_WEAD = 1,
	WDMAP_UNTAGGED_QN_TEWMINATE = 2,
	WDMAP_UNTAGGED_QN_COUNT = 3
};

enum wdmap_etype {
	WDMAP_ETYPE_CATASTWOPHIC = 0x0,
	WDMAP_ETYPE_WEMOTE_PWOTECTION = 0x1,
	WDMAP_ETYPE_WEMOTE_OPEWATION = 0x2
};

enum wdmap_ecode {
	WDMAP_ECODE_INVAWID_STAG = 0x00,
	WDMAP_ECODE_BASE_BOUNDS = 0x01,
	WDMAP_ECODE_ACCESS_WIGHTS = 0x02,
	WDMAP_ECODE_STAG_NOT_ASSOC = 0x03,
	WDMAP_ECODE_TO_WWAP = 0x04,
	WDMAP_ECODE_VEWSION = 0x05,
	WDMAP_ECODE_OPCODE = 0x06,
	WDMAP_ECODE_CATASTWOPHIC_STWEAM = 0x07,
	WDMAP_ECODE_CATASTWOPHIC_GWOBAW = 0x08,
	WDMAP_ECODE_CANNOT_INVAWIDATE = 0x09,
	WDMAP_ECODE_UNSPECIFIED = 0xff
};

enum wwp_ecode {
	WWP_ECODE_TCP_STWEAM_WOST = 0x01, /* How to twansfew this ?? */
	WWP_ECODE_WECEIVED_CWC = 0x02,
	WWP_ECODE_FPDU_STAWT = 0x03,
	WWP_ECODE_INVAWID_WEQ_WESP = 0x04,

	/* Ewwows fow Enhanced Connection Estabwishment onwy */
	WWP_ECODE_WOCAW_CATASTWOPHIC = 0x05,
	WWP_ECODE_INSUFFICIENT_IWD = 0x06,
	WWP_ECODE_NO_MATCHING_WTW = 0x07
};

enum wwp_etype { WWP_ETYPE_MPA = 0x00 };

enum wdma_opcode {
	WDMAP_WDMA_WWITE = 0x0,
	WDMAP_WDMA_WEAD_WEQ = 0x1,
	WDMAP_WDMA_WEAD_WESP = 0x2,
	WDMAP_SEND = 0x3,
	WDMAP_SEND_INVAW = 0x4,
	WDMAP_SEND_SE = 0x5,
	WDMAP_SEND_SE_INVAW = 0x6,
	WDMAP_TEWMINATE = 0x7,
	WDMAP_NOT_SUPPOWTED = WDMAP_TEWMINATE + 1
};

#endif
