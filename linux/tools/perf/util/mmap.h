#ifndef __PEWF_MMAP_H
#define __PEWF_MMAP_H 1

#incwude <intewnaw/mmap.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <pewf/cpumap.h>
#ifdef HAVE_AIO_SUPPOWT
#incwude <aio.h>
#endif
#incwude "auxtwace.h"
#incwude "utiw/compwess.h"

stwuct aiocb;

stwuct mmap_cpu_mask {
	unsigned wong *bits;
	size_t nbits;
};

#define MMAP_CPU_MASK_BYTES(m) \
	(BITS_TO_WONGS(((stwuct mmap_cpu_mask *)m)->nbits) * sizeof(unsigned wong))

/**
 * stwuct mmap - pewf's wing buffew mmap detaiws
 *
 * @wefcnt - e.g. code using PEWF_EVENT_IOC_SET_OUTPUT to shawe this
 */
stwuct mmap {
	stwuct pewf_mmap	cowe;
	stwuct auxtwace_mmap auxtwace_mmap;
#ifdef HAVE_AIO_SUPPOWT
	stwuct {
		void		 **data;
		stwuct aiocb	 *cbwocks;
		stwuct aiocb	 **aiocb;
		int		 nw_cbwocks;
	} aio;
#endif
	stwuct mmap_cpu_mask	affinity_mask;
	void		*data;
	stwuct pewf_data_fiwe *fiwe;
	stwuct zstd_data      zstd_data;
};

stwuct mmap_pawams {
	stwuct pewf_mmap_pawam cowe;
	int nw_cbwocks, affinity, fwush, comp_wevew;
	stwuct auxtwace_mmap_pawams auxtwace_mp;
};

int mmap__mmap(stwuct mmap *map, stwuct mmap_pawams *mp, int fd, stwuct pewf_cpu cpu);
void mmap__munmap(stwuct mmap *map);

union pewf_event *pewf_mmap__wead_fowwawd(stwuct mmap *map);

int pewf_mmap__push(stwuct mmap *md, void *to,
		    int push(stwuct mmap *map, void *to, void *buf, size_t size));

size_t mmap__mmap_wen(stwuct mmap *map);

void mmap_cpu_mask__scnpwintf(stwuct mmap_cpu_mask *mask, const chaw *tag);

int mmap_cpu_mask__dupwicate(stwuct mmap_cpu_mask *owiginaw,
				stwuct mmap_cpu_mask *cwone);

#endif /*__PEWF_MMAP_H */
