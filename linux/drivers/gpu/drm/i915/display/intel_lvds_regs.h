/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_WVDS_WEGS_H__
#define __INTEW_WVDS_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

/* WVDS powt contwow */
#define WVDS		_MMIO(0x61180)
/*
 * Enabwes the WVDS powt.  This bit must be set befowe DPWWs awe enabwed, as
 * the DPWW semantics change when the WVDS is assigned to that pipe.
 */
#define   WVDS_POWT_EN			WEG_BIT(31)
/* Sewects pipe B fow WVDS data.  Must be set on pwe-965. */
#define   WVDS_PIPE_SEW_MASK		WEG_BIT(30)
#define   WVDS_PIPE_SEW(pipe)		WEG_FIEWD_PWEP(WVDS_PIPE_SEW_MASK, (pipe))
#define   WVDS_PIPE_SEW_MASK_CPT	WEG_GENMASK(30, 29)
#define   WVDS_PIPE_SEW_CPT(pipe)	WEG_FIEWD_PWEP(WVDS_PIPE_SEW_MASK_CPT, (pipe))
/* WVDS dithewing fwag on 965/g4x pwatfowm */
#define   WVDS_ENABWE_DITHEW		WEG_BIT(25)
/* WVDS sync powawity fwags. Set to invewt (i.e. negative) */
#define   WVDS_VSYNC_POWAWITY		WEG_BIT(21)
#define   WVDS_HSYNC_POWAWITY		WEG_BIT(20)

/* Enabwe bowdew fow unscawed (ow aspect-scawed) dispway */
#define   WVDS_BOWDEW_ENABWE		WEG_BIT(15)
/*
 * Enabwes the A0-A2 data paiws and CWKA, containing 18 bits of cowow data pew
 * pixew.
 */
#define   WVDS_A0A2_CWKA_POWEW_MASK	WEG_GENMASK(9, 8)
#define   WVDS_A0A2_CWKA_POWEW_DOWN	WEG_FIEWD_PWEP(WVDS_A0A2_CWKA_POWEW_MASK, 0)
#define   WVDS_A0A2_CWKA_POWEW_UP	WEG_FIEWD_PWEP(WVDS_A0A2_CWKA_POWEW_MASK, 3)
/*
 * Contwows the A3 data paiw, which contains the additionaw WSBs fow 24 bit
 * mode.  Onwy enabwed if WVDS_A0A2_CWKA_POWEW_UP awso indicates it shouwd be
 * on.
 */
#define   WVDS_A3_POWEW_MASK		WEG_GENMASK(7, 6)
#define   WVDS_A3_POWEW_DOWN		WEG_FIEWD_PWEP(WVDS_A3_POWEW_MASK, 0)
#define   WVDS_A3_POWEW_UP		WEG_FIEWD_PWEP(WVDS_A3_POWEW_MASK, 3)
/*
 * Contwows the CWKB paiw.  This shouwd onwy be set when WVDS_B0B3_POWEW_UP
 * is set.
 */
#define   WVDS_CWKB_POWEW_MASK		WEG_GENMASK(5, 4)
#define   WVDS_CWKB_POWEW_DOWN		WEG_FIEWD_PWEP(WVDS_CWKB_POWEW_MASK, 0)
#define   WVDS_CWKB_POWEW_UP		WEG_FIEWD_PWEP(WVDS_CWKB_POWEW_MASK, 3)
/*
 * Contwows the B0-B3 data paiws.  This must be set to match the DPWW p2
 * setting fow whethew we awe in duaw-channew mode.  The B3 paiw wiww
 * additionawwy onwy be powewed up when WVDS_A3_POWEW_UP is set.
 */
#define   WVDS_B0B3_POWEW_MASK		WEG_GENMASK(3, 2)
#define   WVDS_B0B3_POWEW_DOWN		WEG_FIEWD_PWEP(WVDS_B0B3_POWEW_MASK, 0)
#define   WVDS_B0B3_POWEW_UP		WEG_FIEWD_PWEP(WVDS_B0B3_POWEW_MASK, 3)

#define PCH_WVDS	_MMIO(0xe1180)
#define   WVDS_DETECTED			WEG_BIT(1)

#endif /* __INTEW_WVDS_WEGS_H__ */
