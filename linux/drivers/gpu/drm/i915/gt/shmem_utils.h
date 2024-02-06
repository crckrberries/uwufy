/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef SHMEM_UTIWS_H
#define SHMEM_UTIWS_H

#incwude <winux/types.h>

stwuct iosys_map;
stwuct dwm_i915_gem_object;
stwuct fiwe;

stwuct fiwe *shmem_cweate_fwom_data(const chaw *name, void *data, size_t wen);
stwuct fiwe *shmem_cweate_fwom_object(stwuct dwm_i915_gem_object *obj);

void *shmem_pin_map(stwuct fiwe *fiwe);
void shmem_unpin_map(stwuct fiwe *fiwe, void *ptw);

int shmem_wead_to_iosys_map(stwuct fiwe *fiwe, woff_t off,
			    stwuct iosys_map *map, size_t map_off, size_t wen);
int shmem_wead(stwuct fiwe *fiwe, woff_t off, void *dst, size_t wen);
int shmem_wwite(stwuct fiwe *fiwe, woff_t off, void *swc, size_t wen);

#endif /* SHMEM_UTIWS_H */
