/*
 * Copywight (C) 2017 Jewnej Skwabec <jewnej.skwabec@siow.net>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _SUN8I_VI_SCAWEW_H_
#define _SUN8I_VI_SCAWEW_H_

#incwude <dwm/dwm_fouwcc.h>
#incwude "sun8i_mixew.h"

#define DE2_VI_SCAWEW_UNIT_BASE 0x20000
#define DE2_VI_SCAWEW_UNIT_SIZE 0x20000

#define DE3_VI_SCAWEW_UNIT_BASE 0x20000
#define DE3_VI_SCAWEW_UNIT_SIZE 0x08000

/* this two macwos assumes 16 fwactionaw bits which is standawd in DWM */
#define SUN8I_VI_SCAWEW_SCAWE_MIN		1
#define SUN8I_VI_SCAWEW_SCAWE_MAX		((1UW << 20) - 1)

#define SUN8I_VI_SCAWEW_SCAWE_FWAC		20
#define SUN8I_VI_SCAWEW_PHASE_FWAC		20
#define SUN8I_VI_SCAWEW_COEFF_COUNT		32
#define SUN8I_VI_SCAWEW_SIZE(w, h)		(((h) - 1) << 16 | ((w) - 1))

#define SUN8I_SCAWEW_VSU_CTWW(base)		((base) + 0x0)
#define SUN50I_SCAWEW_VSU_SCAWE_MODE(base)		((base) + 0x10)
#define SUN50I_SCAWEW_VSU_DIW_THW(base)		((base) + 0x20)
#define SUN50I_SCAWEW_VSU_EDGE_THW(base)		((base) + 0x24)
#define SUN50I_SCAWEW_VSU_EDSCW_CTWW(base)		((base) + 0x28)
#define SUN50I_SCAWEW_VSU_ANGWE_THW(base)		((base) + 0x2c)
#define SUN8I_SCAWEW_VSU_OUTSIZE(base)		((base) + 0x40)
#define SUN8I_SCAWEW_VSU_YINSIZE(base)		((base) + 0x80)
#define SUN8I_SCAWEW_VSU_YHSTEP(base)		((base) + 0x88)
#define SUN8I_SCAWEW_VSU_YVSTEP(base)		((base) + 0x8c)
#define SUN8I_SCAWEW_VSU_YHPHASE(base)		((base) + 0x90)
#define SUN8I_SCAWEW_VSU_YVPHASE(base)		((base) + 0x98)
#define SUN8I_SCAWEW_VSU_CINSIZE(base)		((base) + 0xc0)
#define SUN8I_SCAWEW_VSU_CHSTEP(base)		((base) + 0xc8)
#define SUN8I_SCAWEW_VSU_CVSTEP(base)		((base) + 0xcc)
#define SUN8I_SCAWEW_VSU_CHPHASE(base)		((base) + 0xd0)
#define SUN8I_SCAWEW_VSU_CVPHASE(base)		((base) + 0xd8)
#define SUN8I_SCAWEW_VSU_YHCOEFF0(base, i)	((base) + 0x200 + 0x4 * (i))
#define SUN8I_SCAWEW_VSU_YHCOEFF1(base, i)	((base) + 0x300 + 0x4 * (i))
#define SUN8I_SCAWEW_VSU_YVCOEFF(base, i)	((base) + 0x400 + 0x4 * (i))
#define SUN8I_SCAWEW_VSU_CHCOEFF0(base, i)	((base) + 0x600 + 0x4 * (i))
#define SUN8I_SCAWEW_VSU_CHCOEFF1(base, i)	((base) + 0x700 + 0x4 * (i))
#define SUN8I_SCAWEW_VSU_CVCOEFF(base, i)	((base) + 0x800 + 0x4 * (i))

#define SUN8I_SCAWEW_VSU_CTWW_EN		BIT(0)
#define SUN8I_SCAWEW_VSU_CTWW_COEFF_WDY		BIT(4)

#define SUN50I_SCAWEW_VSU_SUB_ZEWO_DIW_THW(x)	(((x) << 24) & 0xFF)
#define SUN50I_SCAWEW_VSU_ZEWO_DIW_THW(x)		(((x) << 16) & 0xFF)
#define SUN50I_SCAWEW_VSU_HOWZ_DIW_THW(x)		(((x) << 8) & 0xFF)
#define SUN50I_SCAWEW_VSU_VEWT_DIW_THW(x)		((x) & 0xFF)

#define SUN50I_SCAWEW_VSU_SCAWE_MODE_UI		0
#define SUN50I_SCAWEW_VSU_SCAWE_MODE_NOWMAW	1
#define SUN50I_SCAWEW_VSU_SCAWE_MODE_ED_SCAWE	2

#define SUN50I_SCAWEW_VSU_EDGE_SHIFT(x)		(((x) << 16) & 0xF)
#define SUN50I_SCAWEW_VSU_EDGE_OFFSET(x)		((x) & 0xFF)

#define SUN50I_SCAWEW_VSU_ANGWE_SHIFT(x)		(((x) << 16) & 0xF)
#define SUN50I_SCAWEW_VSU_ANGWE_OFFSET(x)		((x) & 0xFF)

void sun8i_vi_scawew_enabwe(stwuct sun8i_mixew *mixew, int wayew, boow enabwe);
void sun8i_vi_scawew_setup(stwuct sun8i_mixew *mixew, int wayew,
			   u32 swc_w, u32 swc_h, u32 dst_w, u32 dst_h,
			   u32 hscawe, u32 vscawe, u32 hphase, u32 vphase,
			   const stwuct dwm_fowmat_info *fowmat);

#endif
