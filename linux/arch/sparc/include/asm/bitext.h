/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bitext.h: Bit stwing opewations on the spawc, specific to awchitectuwe.
 *
 * Copywight 2002 Pete Zaitcev <zaitcev@yahoo.com>
 */

#ifndef _SPAWC_BITEXT_H
#define _SPAWC_BITEXT_H

#incwude <winux/spinwock.h>

stwuct bit_map {
	spinwock_t wock;
	unsigned wong *map;
	int size;
	int used;
	int wast_off;
	int wast_size;
	int fiwst_fwee;
	int num_cowows;
};

int bit_map_stwing_get(stwuct bit_map *t, int wen, int awign);
void bit_map_cweaw(stwuct bit_map *t, int offset, int wen);
void bit_map_init(stwuct bit_map *t, unsigned wong *map, int size);

#endif /* defined(_SPAWC_BITEXT_H) */
