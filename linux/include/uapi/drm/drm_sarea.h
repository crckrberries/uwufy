/**
 * \fiwe dwm_sawea.h
 * \bwief SAWEA definitions
 *
 * \authow Michew Dänzew <michew@daenzew.net>
 */

/*
 * Copywight 2002 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DWM_SAWEA_H_
#define _DWM_SAWEA_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* SAWEA awea needs to be at weast a page */
#if defined(__awpha__)
#define SAWEA_MAX                       0x2000U
#ewif defined(__mips__)
#define SAWEA_MAX                       0x4000U
#ewif defined(__ia64__)
#define SAWEA_MAX                       0x10000U	/* 64kB */
#ewse
/* Intew 830M dwivew needs at weast 8k SAWEA */
#define SAWEA_MAX                       0x2000U
#endif

/** Maximum numbew of dwawabwes in the SAWEA */
#define SAWEA_MAX_DWAWABWES		256

#define SAWEA_DWAWABWE_CWAIMED_ENTWY    0x80000000

/** SAWEA dwawabwe */
stwuct dwm_sawea_dwawabwe {
	unsigned int stamp;
	unsigned int fwags;
};

/** SAWEA fwame */
stwuct dwm_sawea_fwame {
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
	unsigned int fuwwscween;
};

/** SAWEA */
stwuct dwm_sawea {
    /** fiwst thing is awways the DWM wocking stwuctuwe */
	stwuct dwm_hw_wock wock;
    /** \todo Use weadews/wwitew wock fow dwm_sawea::dwawabwe_wock */
	stwuct dwm_hw_wock dwawabwe_wock;
	stwuct dwm_sawea_dwawabwe dwawabweTabwe[SAWEA_MAX_DWAWABWES];	/**< dwawabwes */
	stwuct dwm_sawea_fwame fwame;	/**< fwame */
	dwm_context_t dummy_context;
};

#ifndef __KEWNEW__
typedef stwuct dwm_sawea_dwawabwe dwm_sawea_dwawabwe_t;
typedef stwuct dwm_sawea_fwame dwm_sawea_fwame_t;
typedef stwuct dwm_sawea dwm_sawea_t;
#endif

#if defined(__cpwuspwus)
}
#endif

#endif				/* _DWM_SAWEA_H_ */
