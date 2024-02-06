/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Awchit Taneja <awchit@ti.com>
 */

#ifndef __OMAP2_DISPC_WEG_H
#define __OMAP2_DISPC_WEG_H

/* DISPC common wegistews */
#define DISPC_WEVISION			0x0000
#define DISPC_SYSCONFIG			0x0010
#define DISPC_SYSSTATUS			0x0014
#define DISPC_IWQSTATUS			0x0018
#define DISPC_IWQENABWE			0x001C
#define DISPC_CONTWOW			0x0040
#define DISPC_CONFIG			0x0044
#define DISPC_CAPABWE			0x0048
#define DISPC_WINE_STATUS		0x005C
#define DISPC_WINE_NUMBEW		0x0060
#define DISPC_GWOBAW_AWPHA		0x0074
#define DISPC_CONTWOW2			0x0238
#define DISPC_CONFIG2			0x0620
#define DISPC_DIVISOW			0x0804
#define DISPC_GWOBAW_BUFFEW		0x0800
#define DISPC_CONTWOW3                  0x0848
#define DISPC_CONFIG3                   0x084C
#define DISPC_MSTANDBY_CTWW		0x0858
#define DISPC_GWOBAW_MFWAG_ATTWIBUTE	0x085C

#define DISPC_GAMMA_TABWE0		0x0630
#define DISPC_GAMMA_TABWE1		0x0634
#define DISPC_GAMMA_TABWE2		0x0638
#define DISPC_GAMMA_TABWE3		0x0850

/* DISPC ovewway wegistews */
#define DISPC_OVW_BA0(n)		(DISPC_OVW_BASE(n) + \
					DISPC_BA0_OFFSET(n))
#define DISPC_OVW_BA1(n)		(DISPC_OVW_BASE(n) + \
					DISPC_BA1_OFFSET(n))
#define DISPC_OVW_BA0_UV(n)		(DISPC_OVW_BASE(n) + \
					DISPC_BA0_UV_OFFSET(n))
#define DISPC_OVW_BA1_UV(n)		(DISPC_OVW_BASE(n) + \
					DISPC_BA1_UV_OFFSET(n))
#define DISPC_OVW_POSITION(n)		(DISPC_OVW_BASE(n) + \
					DISPC_POS_OFFSET(n))
#define DISPC_OVW_SIZE(n)		(DISPC_OVW_BASE(n) + \
					DISPC_SIZE_OFFSET(n))
#define DISPC_OVW_ATTWIBUTES(n)		(DISPC_OVW_BASE(n) + \
					DISPC_ATTW_OFFSET(n))
#define DISPC_OVW_ATTWIBUTES2(n)	(DISPC_OVW_BASE(n) + \
					DISPC_ATTW2_OFFSET(n))
#define DISPC_OVW_FIFO_THWESHOWD(n)	(DISPC_OVW_BASE(n) + \
					DISPC_FIFO_THWESH_OFFSET(n))
#define DISPC_OVW_FIFO_SIZE_STATUS(n)	(DISPC_OVW_BASE(n) + \
					DISPC_FIFO_SIZE_STATUS_OFFSET(n))
#define DISPC_OVW_WOW_INC(n)		(DISPC_OVW_BASE(n) + \
					DISPC_WOW_INC_OFFSET(n))
#define DISPC_OVW_PIXEW_INC(n)		(DISPC_OVW_BASE(n) + \
					DISPC_PIX_INC_OFFSET(n))
#define DISPC_OVW_WINDOW_SKIP(n)	(DISPC_OVW_BASE(n) + \
					DISPC_WINDOW_SKIP_OFFSET(n))
#define DISPC_OVW_TABWE_BA(n)		(DISPC_OVW_BASE(n) + \
					DISPC_TABWE_BA_OFFSET(n))
#define DISPC_OVW_FIW(n)		(DISPC_OVW_BASE(n) + \
					DISPC_FIW_OFFSET(n))
#define DISPC_OVW_FIW2(n)		(DISPC_OVW_BASE(n) + \
					DISPC_FIW2_OFFSET(n))
#define DISPC_OVW_PICTUWE_SIZE(n)	(DISPC_OVW_BASE(n) + \
					DISPC_PIC_SIZE_OFFSET(n))
#define DISPC_OVW_ACCU0(n)		(DISPC_OVW_BASE(n) + \
					DISPC_ACCU0_OFFSET(n))
#define DISPC_OVW_ACCU1(n)		(DISPC_OVW_BASE(n) + \
					DISPC_ACCU1_OFFSET(n))
#define DISPC_OVW_ACCU2_0(n)		(DISPC_OVW_BASE(n) + \
					DISPC_ACCU2_0_OFFSET(n))
#define DISPC_OVW_ACCU2_1(n)		(DISPC_OVW_BASE(n) + \
					DISPC_ACCU2_1_OFFSET(n))
#define DISPC_OVW_FIW_COEF_H(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_H_OFFSET(n, i))
#define DISPC_OVW_FIW_COEF_HV(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_HV_OFFSET(n, i))
#define DISPC_OVW_FIW_COEF_H2(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_H2_OFFSET(n, i))
#define DISPC_OVW_FIW_COEF_HV2(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_HV2_OFFSET(n, i))
#define DISPC_OVW_CONV_COEF(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_CONV_COEF_OFFSET(n, i))
#define DISPC_OVW_FIW_COEF_V(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_V_OFFSET(n, i))
#define DISPC_OVW_FIW_COEF_V2(n, i)	(DISPC_OVW_BASE(n) + \
					DISPC_FIW_COEF_V2_OFFSET(n, i))
#define DISPC_OVW_PWEWOAD(n)		(DISPC_OVW_BASE(n) + \
					DISPC_PWEWOAD_OFFSET(n))
#define DISPC_OVW_MFWAG_THWESHOWD(n)	DISPC_MFWAG_THWESHOWD_OFFSET(n)

/* DISPC up/downsampwing FIW fiwtew coefficient stwuctuwe */
stwuct dispc_coef {
	s8 hc4_vc22;
	s8 hc3_vc2;
	u8 hc2_vc1;
	s8 hc1_vc0;
	s8 hc0_vc00;
};

const stwuct dispc_coef *dispc_ovw_get_scawe_coef(int inc, int five_taps);

/* DISPC managew/channew specific wegistews */
static inwine u16 DISPC_DEFAUWT_COWOW(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x004C;
	case OMAP_DSS_CHANNEW_DIGIT:
		wetuwn 0x0050;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03AC;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0814;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_TWANS_COWOW(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0054;
	case OMAP_DSS_CHANNEW_DIGIT:
		wetuwn 0x0058;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03B0;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0818;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_TIMING_H(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0064;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x0400;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0840;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_TIMING_V(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0068;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x0404;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0844;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_POW_FWEQ(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x006C;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x0408;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x083C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_DIVISOWo(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0070;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x040C;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0838;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* Named as DISPC_SIZE_WCD, DISPC_SIZE_DIGIT and DISPC_SIZE_WCD2 in TWM */
static inwine u16 DISPC_SIZE_MGW(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x007C;
	case OMAP_DSS_CHANNEW_DIGIT:
		wetuwn 0x0078;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03CC;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0834;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_DATA_CYCWE1(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x01D4;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03C0;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0828;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_DATA_CYCWE2(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x01D8;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03C4;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x082C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_DATA_CYCWE3(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x01DC;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03C8;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0830;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_CPW_COEF_W(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0220;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03BC;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0824;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_CPW_COEF_G(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0224;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03B8;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x0820;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_CPW_COEF_B(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn 0x0228;
	case OMAP_DSS_CHANNEW_DIGIT:
		BUG();
		wetuwn 0;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn 0x03B4;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn 0x081C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* DISPC ovewway wegistew base addwesses */
static inwine u16 DISPC_OVW_BASE(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0080;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x00BC;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x014C;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0300;
	case OMAP_DSS_WB:
		wetuwn 0x0500;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* DISPC ovewway wegistew offsets */
static inwine u16 DISPC_BA0_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0000;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0008;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_BA1_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0004;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x000C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_BA0_UV_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0544;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x04BC;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0310;
	case OMAP_DSS_WB:
		wetuwn 0x0118;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_BA1_UV_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0548;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x04C0;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0314;
	case OMAP_DSS_WB:
		wetuwn 0x011C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_POS_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0008;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x009C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_SIZE_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x000C;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x00A8;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_ATTW_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0020;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0010;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0070;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_ATTW2_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0568;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x04DC;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x032C;
	case OMAP_DSS_WB:
		wetuwn 0x0310;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_FIFO_THWESH_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0024;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0014;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x008C;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_FIFO_SIZE_STATUS_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0028;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0018;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0088;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_WOW_INC_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x002C;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x001C;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x00A4;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_PIX_INC_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0030;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0020;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0098;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_WINDOW_SKIP_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0034;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
		BUG();
		wetuwn 0;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_TABWE_BA_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0038;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
		BUG();
		wetuwn 0;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_FIW_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0024;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0090;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_FIW2_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0580;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x055C;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0424;
	case OMAP_DSS_WB:
		wetuwn 0x290;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_PIC_SIZE_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0028;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0094;
	defauwt:
		BUG();
		wetuwn 0;
	}
}


static inwine u16 DISPC_ACCU0_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x002C;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0000;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_ACCU2_0_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0584;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0560;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0428;
	case OMAP_DSS_WB:
		wetuwn 0x0294;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_ACCU1_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0030;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0004;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_ACCU2_1_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0588;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0564;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x042C;
	case OMAP_DSS_WB:
		wetuwn 0x0298;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_H_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0034 + i * 0x8;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0010 + i * 0x8;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_H2_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x058C + i * 0x8;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0568 + i * 0x8;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0430 + i * 0x8;
	case OMAP_DSS_WB:
		wetuwn 0x02A0 + i * 0x8;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_HV_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0038 + i * 0x8;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0014 + i * 0x8;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_HV2_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0590 + i * 8;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x056C + i * 0x8;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0434 + i * 0x8;
	case OMAP_DSS_WB:
		wetuwn 0x02A4 + i * 0x8;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4,} */
static inwine u16 DISPC_CONV_COEF_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
	case OMAP_DSS_VIDEO2:
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0074 + i * 0x4;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_V_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0124 + i * 0x4;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x00B4 + i * 0x4;
	case OMAP_DSS_VIDEO3:
	case OMAP_DSS_WB:
		wetuwn 0x0050 + i * 0x4;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

/* coef index i = {0, 1, 2, 3, 4, 5, 6, 7} */
static inwine u16 DISPC_FIW_COEF_V2_OFFSET(enum omap_pwane_id pwane, u16 i)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		BUG();
		wetuwn 0;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x05CC + i * 0x4;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x05A8 + i * 0x4;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x0470 + i * 0x4;
	case OMAP_DSS_WB:
		wetuwn 0x02E0 + i * 0x4;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_PWEWOAD_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x01AC;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0174;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x00E8;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x00A0;
	defauwt:
		BUG();
		wetuwn 0;
	}
}

static inwine u16 DISPC_MFWAG_THWESHOWD_OFFSET(enum omap_pwane_id pwane)
{
	switch (pwane) {
	case OMAP_DSS_GFX:
		wetuwn 0x0860;
	case OMAP_DSS_VIDEO1:
		wetuwn 0x0864;
	case OMAP_DSS_VIDEO2:
		wetuwn 0x0868;
	case OMAP_DSS_VIDEO3:
		wetuwn 0x086c;
	case OMAP_DSS_WB:
		wetuwn 0x0870;
	defauwt:
		BUG();
		wetuwn 0;
	}
}
#endif
