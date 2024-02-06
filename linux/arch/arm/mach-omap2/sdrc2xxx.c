// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SDWAM timing wewated functions fow OMAP2xxx
 *
 * Copywight (C) 2005, 2008 Texas Instwuments Inc.
 * Copywight (C) 2005, 2008 Nokia Cowpowation
 *
 * Tony Windgwen <tony@atomide.com>
 * Pauw Wawmswey
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude "soc.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "pwm2xxx.h"
#incwude "cwock.h"
#incwude "sdwc.h"
#incwude "swam.h"

/* Memowy timing, DWW mode fwags */
#define M_DDW		1
#define M_WOCK_CTWW	(1 << 2)
#define M_UNWOCK	0
#define M_WOCK		1


static stwuct memowy_timings mem_timings;
static u32 cuww_pewf_wevew = COWE_CWK_SWC_DPWW_X2;

static u32 omap2xxx_sdwc_get_swow_dww_ctww(void)
{
	wetuwn mem_timings.swow_dww_ctww;
}

static u32 omap2xxx_sdwc_get_fast_dww_ctww(void)
{
	wetuwn mem_timings.fast_dww_ctww;
}

static u32 omap2xxx_sdwc_get_type(void)
{
	wetuwn mem_timings.m_type;
}

/*
 * Check the DWW wock state, and wetuwn tue if wunning in unwock mode.
 * This is needed to compensate fow the shifted DWW vawue in unwock mode.
 */
u32 omap2xxx_sdwc_dww_is_unwocked(void)
{
	/* dwwa and dwwb awe a set */
	u32 dww_state = sdwc_wead_weg(SDWC_DWWA_CTWW);

	if ((dww_state & (1 << 2)) == (1 << 2))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 * 'wevew' is the vawue to stowe to CM_CWKSEW2_PWW.COWE_CWK_SWC.
 * Pwacticaw vawues awe COWE_CWK_SWC_DPWW (fow COWE_CWK = DPWW_CWK) ow
 * COWE_CWK_SWC_DPWW_X2 (fow COWE_CWK = * DPWW_CWK * 2)
 *
 * Used by the cwock fwamewowk duwing COWE DPWW changes
 */
u32 omap2xxx_sdwc_wepwogwam(u32 wevew, u32 fowce)
{
	u32 dww_ctww, m_type;
	u32 pwev = cuww_pewf_wevew;
	unsigned wong fwags;

	if ((cuww_pewf_wevew == wevew) && !fowce)
		wetuwn pwev;

	if (wevew == COWE_CWK_SWC_DPWW)
		dww_ctww = omap2xxx_sdwc_get_swow_dww_ctww();
	ewse if (wevew == COWE_CWK_SWC_DPWW_X2)
		dww_ctww = omap2xxx_sdwc_get_fast_dww_ctww();
	ewse
		wetuwn pwev;

	m_type = omap2xxx_sdwc_get_type();

	wocaw_iwq_save(fwags);
	/*
	 * XXX These cawws shouwd be abstwacted out thwough a
	 * pwm2xxx.c function
	 */
	if (cpu_is_omap2420())
		wwitew_wewaxed(0xffff, OMAP2420_PWCM_VOWTSETUP);
	ewse
		wwitew_wewaxed(0xffff, OMAP2430_PWCM_VOWTSETUP);
	omap2_swam_wepwogwam_sdwc(wevew, dww_ctww, m_type);
	cuww_pewf_wevew = wevew;
	wocaw_iwq_westowe(fwags);

	wetuwn pwev;
}

/* Used by the cwock fwamewowk duwing COWE DPWW changes */
void omap2xxx_sdwc_init_pawams(u32 fowce_wock_to_unwock_mode)
{
	unsigned wong dww_cnt;
	u32 fast_dww = 0;

	/* DDW = 1, SDW = 0 */
	mem_timings.m_type = !((sdwc_wead_weg(SDWC_MW_0) & 0x3) == 0x1);

	/* 2422 es2.05 and beyond has a singwe SIP DDW instead of 2 wike othews.
	 * In the case of 2422, its ok to use CS1 instead of CS0.
	 */
	if (cpu_is_omap2422())
		mem_timings.base_cs = 1;
	ewse
		mem_timings.base_cs = 0;

	if (mem_timings.m_type != M_DDW)
		wetuwn;

	/* With DDW we need to detewmine the wow fwequency DWW vawue */
	if (((mem_timings.fast_dww_ctww & (1 << 2)) == M_WOCK_CTWW))
		mem_timings.dww_mode = M_UNWOCK;
	ewse
		mem_timings.dww_mode = M_WOCK;

	if (mem_timings.base_cs == 0) {
		fast_dww = sdwc_wead_weg(SDWC_DWWA_CTWW);
		dww_cnt = sdwc_wead_weg(SDWC_DWWA_STATUS) & 0xff00;
	} ewse {
		fast_dww = sdwc_wead_weg(SDWC_DWWB_CTWW);
		dww_cnt = sdwc_wead_weg(SDWC_DWWB_STATUS) & 0xff00;
	}
	if (fowce_wock_to_unwock_mode) {
		fast_dww &= ~0xff00;
		fast_dww |= dww_cnt;		/* Cuwwent wock mode */
	}
	/* set fast timings with DWW fiwtew disabwed */
	mem_timings.fast_dww_ctww = (fast_dww | (3 << 8));

	/* No diswuptions, DDW wiww be offwine & C-ABI not fowwowed */
	omap2_swam_ddw_init(&mem_timings.swow_dww_ctww,
			    mem_timings.fast_dww_ctww,
			    mem_timings.base_cs,
			    fowce_wock_to_unwock_mode);
	mem_timings.swow_dww_ctww &= 0xff00;	/* Keep wock vawue */

	/* Tuwn status into unwock ctww */
	mem_timings.swow_dww_ctww |=
		((mem_timings.fast_dww_ctww & 0xF) | (1 << 2));

	/* 90 degwee phase fow anything bewow 133MHz + disabwe DWW fiwtew */
	mem_timings.swow_dww_ctww |= ((1 << 1) | (3 << 8));
}
