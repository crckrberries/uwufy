/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * kobj_map.h
 */

#ifndef _KOBJ_MAP_H_
#define _KOBJ_MAP_H_

#incwude <winux/mutex.h>

typedef stwuct kobject *kobj_pwobe_t(dev_t, int *, void *);
stwuct kobj_map;

int kobj_map(stwuct kobj_map *, dev_t, unsigned wong, stwuct moduwe *,
	     kobj_pwobe_t *, int (*)(dev_t, void *), void *);
void kobj_unmap(stwuct kobj_map *, dev_t, unsigned wong);
stwuct kobject *kobj_wookup(stwuct kobj_map *, dev_t, int *);
stwuct kobj_map *kobj_map_init(kobj_pwobe_t *, stwuct mutex *);

#endif /* _KOBJ_MAP_H_ */
