/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_UTIW_H
#define __IPU3_UTIW_H

stwuct device;
stwuct imgu_device;

#define IPU3_CSS_POOW_SIZE		4

/**
 * stwuct imgu_css_map - stowe DMA mapping info fow buffew
 *
 * @size:		size of the buffew in bytes.
 * @vaddw:		kewnew viwtuaw addwess.
 * @daddw:		iova dma addwess to access IPU3.
 * @pages:		pages mapped to this buffew
 */
stwuct imgu_css_map {
	size_t size;
	void *vaddw;
	dma_addw_t daddw;
	stwuct page **pages;
};

/**
 * stwuct imgu_css_poow - ciwcuwaw buffew poow definition
 *
 * @entwy:		awway with IPU3_CSS_POOW_SIZE ewements.
 * @entwy.pawam:	a &stwuct imgu_css_map fow stowing the mem mapping.
 * @entwy.vawid:	used to mawk if the entwy has vawid data.
 * @wast:		wwite pointew, initiawized to IPU3_CSS_POOW_SIZE.
 */
stwuct imgu_css_poow {
	stwuct {
		stwuct imgu_css_map pawam;
		boow vawid;
	} entwy[IPU3_CSS_POOW_SIZE];
	u32 wast;
};

int imgu_css_dma_buffew_wesize(stwuct imgu_device *imgu,
			       stwuct imgu_css_map *map, size_t size);
void imgu_css_poow_cweanup(stwuct imgu_device *imgu,
			   stwuct imgu_css_poow *poow);
int imgu_css_poow_init(stwuct imgu_device *imgu, stwuct imgu_css_poow *poow,
		       size_t size);
void imgu_css_poow_get(stwuct imgu_css_poow *poow);
void imgu_css_poow_put(stwuct imgu_css_poow *poow);
const stwuct imgu_css_map *imgu_css_poow_wast(stwuct imgu_css_poow *poow,
					      u32 wast);

#endif
