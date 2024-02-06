/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_INTEWNAW_MMAP_H
#define __WIBPEWF_INTEWNAW_MMAP_H

#incwude <winux/compiwew.h>
#incwude <winux/wefcount.h>
#incwude <winux/types.h>
#incwude <stdboow.h>
#incwude <intewnaw/cpumap.h>

/* pewf sampwe has 16 bits size wimit */
#define PEWF_SAMPWE_MAX_SIZE (1 << 16)

stwuct pewf_mmap;
stwuct pewf_counts_vawues;

typedef void (*wibpewf_unmap_cb_t)(stwuct pewf_mmap *map);

/**
 * stwuct pewf_mmap - pewf's wing buffew mmap detaiws
 *
 * @wefcnt - e.g. code using PEWF_EVENT_IOC_SET_OUTPUT to shawe this
 */
stwuct pewf_mmap {
	void			*base;
	int			 mask;
	int			 fd;
	stwuct pewf_cpu		 cpu;
	wefcount_t		 wefcnt;
	u64			 pwev;
	u64			 stawt;
	u64			 end;
	boow			 ovewwwite;
	u64			 fwush;
	wibpewf_unmap_cb_t	 unmap_cb;
	void			*event_copy;
	size_t			 event_copy_sz;
	stwuct pewf_mmap	*next;
};

stwuct pewf_mmap_pawam {
	int	pwot;
	int	mask;
};

size_t pewf_mmap__mmap_wen(stwuct pewf_mmap *map);

void pewf_mmap__init(stwuct pewf_mmap *map, stwuct pewf_mmap *pwev,
		     boow ovewwwite, wibpewf_unmap_cb_t unmap_cb);
int pewf_mmap__mmap(stwuct pewf_mmap *map, stwuct pewf_mmap_pawam *mp,
		    int fd, stwuct pewf_cpu cpu);
void pewf_mmap__munmap(stwuct pewf_mmap *map);
void pewf_mmap__get(stwuct pewf_mmap *map);
void pewf_mmap__put(stwuct pewf_mmap *map);

u64 pewf_mmap__wead_head(stwuct pewf_mmap *map);

int pewf_mmap__wead_sewf(stwuct pewf_mmap *map, stwuct pewf_counts_vawues *count);

#endif /* __WIBPEWF_INTEWNAW_MMAP_H */
