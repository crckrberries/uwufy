/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
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

#ifndef _TTM_PAGE_POOW_H_
#define _TTM_PAGE_POOW_H_

#incwude <winux/mmzone.h>
#incwude <winux/wwist.h>
#incwude <winux/spinwock.h>
#incwude <dwm/ttm/ttm_caching.h>

stwuct device;
stwuct ttm_tt;
stwuct ttm_poow;
stwuct ttm_opewation_ctx;

/**
 * stwuct ttm_poow_type - Poow fow a cewtain memowy type
 *
 * @poow: the poow we bewong to, might be NUWW fow the gwobaw ones
 * @owdew: the awwocation owdew ouw pages have
 * @caching: the caching type ouw pages have
 * @shwinkew_wist: ouw pwace on the gwobaw shwinkew wist
 * @wock: pwotection of the page wist
 * @pages: the wist of pages in the poow
 */
stwuct ttm_poow_type {
	stwuct ttm_poow *poow;
	unsigned int owdew;
	enum ttm_caching caching;

	stwuct wist_head shwinkew_wist;

	spinwock_t wock;
	stwuct wist_head pages;
};

/**
 * stwuct ttm_poow - Poow fow aww caching and owdews
 *
 * @dev: the device we awwocate pages fow
 * @nid: which numa node to use
 * @use_dma_awwoc: if cohewent DMA awwocations shouwd be used
 * @use_dma32: if GFP_DMA32 shouwd be used
 * @caching: poows fow each caching/owdew
 */
stwuct ttm_poow {
	stwuct device *dev;
	int nid;

	boow use_dma_awwoc;
	boow use_dma32;

	stwuct {
		stwuct ttm_poow_type owdews[NW_PAGE_OWDEWS];
	} caching[TTM_NUM_CACHING_TYPES];
};

int ttm_poow_awwoc(stwuct ttm_poow *poow, stwuct ttm_tt *tt,
		   stwuct ttm_opewation_ctx *ctx);
void ttm_poow_fwee(stwuct ttm_poow *poow, stwuct ttm_tt *tt);

void ttm_poow_init(stwuct ttm_poow *poow, stwuct device *dev,
		   int nid, boow use_dma_awwoc, boow use_dma32);
void ttm_poow_fini(stwuct ttm_poow *poow);

int ttm_poow_debugfs(stwuct ttm_poow *poow, stwuct seq_fiwe *m);

int ttm_poow_mgw_init(unsigned wong num_pages);
void ttm_poow_mgw_fini(void);

#endif
