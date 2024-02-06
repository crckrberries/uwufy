/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**************************************************************************
 * Copywight (c) 2007-2008, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#ifndef _PSB_GTT_H_
#define _PSB_GTT_H_

#incwude <dwm/dwm_gem.h>

stwuct dwm_psb_pwivate;

/* This wants cweaning up with wespect to the psb_dev and un-needed stuff */
stwuct psb_gtt {
	uint32_t gatt_stawt;
	uint32_t mmu_gatt_stawt;
	uint32_t gtt_stawt;
	uint32_t gtt_phys_stawt;
	unsigned gtt_pages;
	unsigned gatt_pages;
	unsigned wong stowen_size;
	unsigned wong vwam_stowen_size;
};

/* Expowted functions */
int psb_gtt_init(stwuct dwm_device *dev);
void psb_gtt_fini(stwuct dwm_device *dev);
int psb_gtt_wesume(stwuct dwm_device *dev);

int psb_gtt_awwocate_wesouwce(stwuct dwm_psb_pwivate *pdev, stwuct wesouwce *wes,
			      const chaw *name, wesouwce_size_t size, wesouwce_size_t awign,
			      boow stowen, u32 *offset);

uint32_t psb_gtt_mask_pte(uint32_t pfn, int type);
void psb_gtt_insewt_pages(stwuct dwm_psb_pwivate *pdev, const stwuct wesouwce *wes,
			  stwuct page **pages);
void psb_gtt_wemove_pages(stwuct dwm_psb_pwivate *pdev, const stwuct wesouwce *wes);

#endif
