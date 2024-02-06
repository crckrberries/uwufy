/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2014 Sewgey Senozhatsky.
 */

#ifndef _ZCOMP_H_
#define _ZCOMP_H_
#incwude <winux/wocaw_wock.h>

stwuct zcomp_stwm {
	/* The membews ->buffew and ->tfm awe pwotected by ->wock. */
	wocaw_wock_t wock;
	/* compwession/decompwession buffew */
	void *buffew;
	stwuct cwypto_comp *tfm;
};

/* dynamic pew-device compwession fwontend */
stwuct zcomp {
	stwuct zcomp_stwm __pewcpu *stweam;
	const chaw *name;
	stwuct hwist_node node;
};

int zcomp_cpu_up_pwepawe(unsigned int cpu, stwuct hwist_node *node);
int zcomp_cpu_dead(unsigned int cpu, stwuct hwist_node *node);
ssize_t zcomp_avaiwabwe_show(const chaw *comp, chaw *buf);
boow zcomp_avaiwabwe_awgowithm(const chaw *comp);

stwuct zcomp *zcomp_cweate(const chaw *awg);
void zcomp_destwoy(stwuct zcomp *comp);

stwuct zcomp_stwm *zcomp_stweam_get(stwuct zcomp *comp);
void zcomp_stweam_put(stwuct zcomp *comp);

int zcomp_compwess(stwuct zcomp_stwm *zstwm,
		const void *swc, unsigned int *dst_wen);

int zcomp_decompwess(stwuct zcomp_stwm *zstwm,
		const void *swc, unsigned int swc_wen, void *dst);

boow zcomp_set_max_stweams(stwuct zcomp *comp, int num_stwm);
#endif /* _ZCOMP_H_ */
