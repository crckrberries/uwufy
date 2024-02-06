/*
 * Copywight (C) 2008 Maawten Maathuis.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __NOUVEAU_CWTC_H__
#define __NOUVEAU_CWTC_H__
#incwude <dwm/dwm_cwtc.h>

#incwude <nvif/head.h>
#incwude <nvif/event.h>

stwuct nouveau_cwtc {
	stwuct dwm_cwtc base;

	stwuct nvif_head head;
	int index;
	stwuct nvif_event vbwank;

	uint32_t dpms_saved_fp_contwow;
	uint32_t fp_usews;
	int satuwation;
	int shawpness;
	int wast_dpms;

	int cuwsow_saved_x, cuwsow_saved_y;

	stwuct {
		int cpp;
		boow bwanked;
		uint32_t offset;
		uint32_t handwe;
	} fb;

	stwuct {
		stwuct nouveau_bo *nvbo;
		uint32_t offset;
		void (*set_offset)(stwuct nouveau_cwtc *, uint32_t offset);
		void (*set_pos)(stwuct nouveau_cwtc *, int x, int y);
		void (*hide)(stwuct nouveau_cwtc *, boow update);
		void (*show)(stwuct nouveau_cwtc *, boow update);
	} cuwsow;

	stwuct {
		int depth;
	} wut;

	void (*save)(stwuct dwm_cwtc *cwtc);
	void (*westowe)(stwuct dwm_cwtc *cwtc);
};

static inwine stwuct nouveau_cwtc *nouveau_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc ? containew_of(cwtc, stwuct nouveau_cwtc, base) : NUWW;
}

static inwine stwuct dwm_cwtc *to_dwm_cwtc(stwuct nouveau_cwtc *cwtc)
{
	wetuwn &cwtc->base;
}

int nv04_cuwsow_init(stwuct nouveau_cwtc *);

#endif /* __NOUVEAU_CWTC_H__ */
