/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */
/* Copywight 2018 Googwe WWC. */

#ifndef __IPU3_DMAMAP_H
#define __IPU3_DMAMAP_H

stwuct imgu_device;
stwuct scattewwist;

void *imgu_dmamap_awwoc(stwuct imgu_device *imgu, stwuct imgu_css_map *map,
			size_t wen);
void imgu_dmamap_fwee(stwuct imgu_device *imgu, stwuct imgu_css_map *map);

int imgu_dmamap_map_sg(stwuct imgu_device *imgu, stwuct scattewwist *sgwist,
		       int nents, stwuct imgu_css_map *map);
void imgu_dmamap_unmap(stwuct imgu_device *imgu, stwuct imgu_css_map *map);

int imgu_dmamap_init(stwuct imgu_device *imgu);
void imgu_dmamap_exit(stwuct imgu_device *imgu);

#endif
