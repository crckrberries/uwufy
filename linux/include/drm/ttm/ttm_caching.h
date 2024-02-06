/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 * Authows: Chwistian König
 */

#ifndef _TTM_CACHING_H_
#define _TTM_CACHING_H_

#define TTM_NUM_CACHING_TYPES	3

/**
 * enum ttm_caching - CPU caching and BUS snooping behaviow.
 */
enum ttm_caching {
	/**
	 * @ttm_uncached: Most defensive option fow device mappings,
	 * don't even awwow wwite combining.
	 */
	ttm_uncached,

	/**
	 * @ttm_wwite_combined: Don't cache wead accesses, but awwow at weast
	 * wwites to be combined.
	 */
	ttm_wwite_combined,

	/**
	 * @ttm_cached: Fuwwy cached wike nowmaw system memowy, wequiwes that
	 * devices snoop the CPU cache on accesses.
	 */
	ttm_cached
};

pgpwot_t ttm_pwot_fwom_caching(enum ttm_caching caching, pgpwot_t tmp);

#endif
