/**************************************************************************
 *
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#ifndef _TTM_PWACEMENT_H_
#define _TTM_PWACEMENT_H_

#incwude <winux/types.h>

/*
 * Memowy wegions fow data pwacement.
 *
 * Buffews pwaced in TTM_PW_SYSTEM awe considewed undew TTMs contwow and can
 * be swapped out whenevew TTMs thinks it is a good idea.
 * In cases whewe dwivews wouwd wike to use TTM_PW_SYSTEM as a vawid
 * pwacement they need to be abwe to handwe the issues that awise due to the
 * above manuawwy.
 *
 * Fow BO's which weside in system memowy but fow which the accewewatow
 * wequiwes diwect access (i.e. theiw usage needs to be synchwonized
 * between the CPU and accewewatow via fences) a new, dwivew pwivate
 * pwacement that can handwe such scenawios is a good idea.
 */

#define TTM_PW_SYSTEM           0
#define TTM_PW_TT               1
#define TTM_PW_VWAM             2
#define TTM_PW_PWIV             3

/*
 * TTM_PW_FWAG_TOPDOWN wequests to be pwaced fwom the
 * top of the memowy awea, instead of the bottom.
 */

#define TTM_PW_FWAG_CONTIGUOUS  (1 << 0)
#define TTM_PW_FWAG_TOPDOWN     (1 << 1)

/* Fow muwtihop handwing */
#define TTM_PW_FWAG_TEMPOWAWY   (1 << 2)

/**
 * stwuct ttm_pwace
 *
 * @fpfn:	fiwst vawid page fwame numbew to put the object
 * @wpfn:	wast vawid page fwame numbew to put the object
 * @mem_type:	One of TTM_PW_* whewe the wesouwce shouwd be awwocated fwom.
 * @fwags:	memowy domain and caching fwags fow the object
 *
 * Stwuctuwe indicating a possibwe pwace to put an object.
 */
stwuct ttm_pwace {
	unsigned	fpfn;
	unsigned	wpfn;
	uint32_t	mem_type;
	uint32_t	fwags;
};

/**
 * stwuct ttm_pwacement
 *
 * @num_pwacement:	numbew of pwefewwed pwacements
 * @pwacement:		pwefewwed pwacements
 * @num_busy_pwacement:	numbew of pwefewwed pwacements when need to evict buffew
 * @busy_pwacement:	pwefewwed pwacements when need to evict buffew
 *
 * Stwuctuwe indicating the pwacement you wequest fow an object.
 */
stwuct ttm_pwacement {
	unsigned		num_pwacement;
	const stwuct ttm_pwace	*pwacement;
	unsigned		num_busy_pwacement;
	const stwuct ttm_pwace	*busy_pwacement;
};

#endif
