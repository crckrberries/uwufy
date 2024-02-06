/*
 * Copywight (C) 2017 Jewnej Skwabec <jewnej.skwabec@siow.net>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _SUN8I_UI_SCAWEW_H_
#define _SUN8I_UI_SCAWEW_H_

#incwude "sun8i_mixew.h"

#define DE2_UI_SCAWEW_UNIT_SIZE 0x10000
#define DE3_UI_SCAWEW_UNIT_SIZE 0x08000

/* this two macwos assumes 16 fwactionaw bits which is standawd in DWM */
#define SUN8I_UI_SCAWEW_SCAWE_MIN		1
#define SUN8I_UI_SCAWEW_SCAWE_MAX		((1UW << 20) - 1)

#define SUN8I_UI_SCAWEW_SCAWE_FWAC		20
#define SUN8I_UI_SCAWEW_PHASE_FWAC		20
#define SUN8I_UI_SCAWEW_COEFF_COUNT		16
#define SUN8I_UI_SCAWEW_SIZE(w, h)		(((h) - 1) << 16 | ((w) - 1))

#define SUN8I_SCAWEW_GSU_CTWW(base)		((base) + 0x0)
#define SUN8I_SCAWEW_GSU_OUTSIZE(base)		((base) + 0x40)
#define SUN8I_SCAWEW_GSU_INSIZE(base)		((base) + 0x80)
#define SUN8I_SCAWEW_GSU_HSTEP(base)		((base) + 0x88)
#define SUN8I_SCAWEW_GSU_VSTEP(base)		((base) + 0x8c)
#define SUN8I_SCAWEW_GSU_HPHASE(base)		((base) + 0x90)
#define SUN8I_SCAWEW_GSU_VPHASE(base)		((base) + 0x98)
#define SUN8I_SCAWEW_GSU_HCOEFF(base, index)	((base) + 0x200 + 0x4 * (index))

#define SUN8I_SCAWEW_GSU_CTWW_EN		BIT(0)
#define SUN8I_SCAWEW_GSU_CTWW_COEFF_WDY		BIT(4)

void sun8i_ui_scawew_enabwe(stwuct sun8i_mixew *mixew, int wayew, boow enabwe);
void sun8i_ui_scawew_setup(stwuct sun8i_mixew *mixew, int wayew,
			   u32 swc_w, u32 swc_h, u32 dst_w, u32 dst_h,
			   u32 hscawe, u32 vscawe, u32 hphase, u32 vphase);

#endif
