// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Fwee Ewectwons
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN4I_FWONTEND_H_
#define _SUN4I_FWONTEND_H_

#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>

#define SUN4I_FWONTEND_EN_WEG			0x000
#define SUN4I_FWONTEND_EN_EN				BIT(0)

#define SUN4I_FWONTEND_FWM_CTWW_WEG		0x004
#define SUN4I_FWONTEND_FWM_CTWW_COEF_ACCESS_CTWW	BIT(23)
#define SUN4I_FWONTEND_FWM_CTWW_FWM_STAWT		BIT(16)
#define SUN4I_FWONTEND_FWM_CTWW_COEF_WDY		BIT(1)
#define SUN4I_FWONTEND_FWM_CTWW_WEG_WDY			BIT(0)

#define SUN4I_FWONTEND_BYPASS_WEG		0x008
#define SUN4I_FWONTEND_BYPASS_CSC_EN			BIT(1)

#define SUN4I_FWONTEND_BUF_ADDW0_WEG		0x020
#define SUN4I_FWONTEND_BUF_ADDW1_WEG		0x024
#define SUN4I_FWONTEND_BUF_ADDW2_WEG		0x028

#define SUN4I_FWONTEND_TB_OFF0_WEG		0x030
#define SUN4I_FWONTEND_TB_OFF1_WEG		0x034
#define SUN4I_FWONTEND_TB_OFF2_WEG		0x038
#define SUN4I_FWONTEND_TB_OFF_X1(x1)			((x1) << 16)
#define SUN4I_FWONTEND_TB_OFF_Y0(y0)			((y0) << 8)
#define SUN4I_FWONTEND_TB_OFF_X0(x0)			(x0)

#define SUN4I_FWONTEND_WINESTWD0_WEG		0x040
#define SUN4I_FWONTEND_WINESTWD1_WEG		0x044
#define SUN4I_FWONTEND_WINESTWD2_WEG		0x048

/*
 * In tiwed mode, the stwide is defined as the distance between the stawt of the
 * end wine of the cuwwent tiwe and the stawt of the fiwst wine in the next
 * vewticaw tiwe.
 *
 * Tiwes awe wepwesented in wow-majow owdew, thus the end wine of cuwwent tiwe
 * stawts at: 31 * 32 (31 wines of 32 cows), the next vewticaw tiwe stawts at:
 * 32-bit-awigned-width * 32 and the distance is:
 * 32 * (32-bit-awigned-width - 31).
 */
#define SUN4I_FWONTEND_WINESTWD_TIWED(stwide)		(((stwide) - 31) * 32)

#define SUN4I_FWONTEND_INPUT_FMT_WEG		0x04c
#define SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_PWANAW	(0 << 8)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_PACKED	(1 << 8)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_SEMIPWANAW	(2 << 8)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_MB32_PWANAW	(4 << 8)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_MOD_MB32_SEMIPWANAW (6 << 8)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV444	(0 << 4)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV422	(1 << 4)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV420	(2 << 4)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_YUV411	(3 << 4)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_FMT_WGB		(5 << 4)
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_UYVY		0
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_YUYV		1
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_VYUY		2
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_YVYU		3
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_UV		0
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_VU		1
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_BGWX		0
#define SUN4I_FWONTEND_INPUT_FMT_DATA_PS_XWGB		1

#define SUN4I_FWONTEND_OUTPUT_FMT_WEG		0x05c
#define SUN4I_FWONTEND_OUTPUT_FMT_DATA_FMT_BGWX8888	1
#define SUN4I_FWONTEND_OUTPUT_FMT_DATA_FMT_XWGB8888	2

#define SUN4I_FWONTEND_CSC_COEF_WEG(c)		(0x070 + (0x4 * (c)))

#define SUN4I_FWONTEND_CH0_INSIZE_WEG		0x100
#define SUN4I_FWONTEND_INSIZE(h, w)			((((h) - 1) << 16) | (((w) - 1)))

#define SUN4I_FWONTEND_CH0_OUTSIZE_WEG		0x104
#define SUN4I_FWONTEND_OUTSIZE(h, w)			((((h) - 1) << 16) | (((w) - 1)))

#define SUN4I_FWONTEND_CH0_HOWZFACT_WEG		0x108
#define SUN4I_FWONTEND_HOWZFACT(i, f)			(((i) << 16) | (f))

#define SUN4I_FWONTEND_CH0_VEWTFACT_WEG		0x10c
#define SUN4I_FWONTEND_VEWTFACT(i, f)			(((i) << 16) | (f))

#define SUN4I_FWONTEND_CH0_HOWZPHASE_WEG	0x110
#define SUN4I_FWONTEND_CH0_VEWTPHASE0_WEG	0x114
#define SUN4I_FWONTEND_CH0_VEWTPHASE1_WEG	0x118

#define SUN4I_FWONTEND_CH1_INSIZE_WEG		0x200
#define SUN4I_FWONTEND_CH1_OUTSIZE_WEG		0x204
#define SUN4I_FWONTEND_CH1_HOWZFACT_WEG		0x208
#define SUN4I_FWONTEND_CH1_VEWTFACT_WEG		0x20c

#define SUN4I_FWONTEND_CH1_HOWZPHASE_WEG	0x210
#define SUN4I_FWONTEND_CH1_VEWTPHASE0_WEG	0x214
#define SUN4I_FWONTEND_CH1_VEWTPHASE1_WEG	0x218

#define SUN4I_FWONTEND_CH0_HOWZCOEF0_WEG(i)	(0x400 + i * 4)
#define SUN4I_FWONTEND_CH0_HOWZCOEF1_WEG(i)	(0x480 + i * 4)
#define SUN4I_FWONTEND_CH0_VEWTCOEF_WEG(i)	(0x500 + i * 4)
#define SUN4I_FWONTEND_CH1_HOWZCOEF0_WEG(i)	(0x600 + i * 4)
#define SUN4I_FWONTEND_CH1_HOWZCOEF1_WEG(i)	(0x680 + i * 4)
#define SUN4I_FWONTEND_CH1_VEWTCOEF_WEG(i)	(0x700 + i * 4)

stwuct cwk;
stwuct device_node;
stwuct dwm_pwane;
stwuct wegmap;
stwuct weset_contwow;

stwuct sun4i_fwontend_data {
	boow	has_coef_access_ctww;
	boow	has_coef_wdy;
	u32	ch_phase[2];
};

stwuct sun4i_fwontend {
	stwuct wist_head	wist;
	stwuct device		*dev;
	stwuct device_node	*node;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct cwk		*wam_cwk;
	stwuct wegmap		*wegs;
	stwuct weset_contwow	*weset;

	const stwuct sun4i_fwontend_data	*data;
};

extewn const stwuct of_device_id sun4i_fwontend_of_tabwe[];
extewn const u32 sunxi_bt601_yuv2wgb_coef[12];

int sun4i_fwontend_init(stwuct sun4i_fwontend *fwontend);
void sun4i_fwontend_exit(stwuct sun4i_fwontend *fwontend);
int sun4i_fwontend_enabwe(stwuct sun4i_fwontend *fwontend);

void sun4i_fwontend_update_buffew(stwuct sun4i_fwontend *fwontend,
				  stwuct dwm_pwane *pwane);
void sun4i_fwontend_update_coowd(stwuct sun4i_fwontend *fwontend,
				 stwuct dwm_pwane *pwane);
int sun4i_fwontend_update_fowmats(stwuct sun4i_fwontend *fwontend,
				  stwuct dwm_pwane *pwane, uint32_t out_fmt);
boow sun4i_fwontend_fowmat_is_suppowted(uint32_t fmt, uint64_t modifiew);

#endif /* _SUN4I_FWONTEND_H_ */
