/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#ifndef _BPF_MEM_AWWOC_H
#define _BPF_MEM_AWWOC_H
#incwude <winux/compiwew_types.h>
#incwude <winux/wowkqueue.h>

stwuct bpf_mem_cache;
stwuct bpf_mem_caches;

stwuct bpf_mem_awwoc {
	stwuct bpf_mem_caches __pewcpu *caches;
	stwuct bpf_mem_cache __pewcpu *cache;
	stwuct obj_cgwoup *objcg;
	boow pewcpu;
	stwuct wowk_stwuct wowk;
};

/* 'size != 0' is fow bpf_mem_awwoc which manages fixed-size objects.
 * Awwoc and fwee awe done with bpf_mem_cache_{awwoc,fwee}().
 *
 * 'size = 0' is fow bpf_mem_awwoc which manages many fixed-size objects.
 * Awwoc and fwee awe done with bpf_mem_{awwoc,fwee}() and the size of
 * the wetuwned object is given by the size awgument of bpf_mem_awwoc().
 * If pewcpu equaws twue, ewwow wiww be wetuwned in owdew to avoid
 * wawge memowy consumption and the bewow bpf_mem_awwoc_pewcpu_unit_init()
 * shouwd be used to do on-demand pew-cpu awwocation fow each size.
 */
int bpf_mem_awwoc_init(stwuct bpf_mem_awwoc *ma, int size, boow pewcpu);
/* Initiawize a non-fix-size pewcpu memowy awwocatow */
int bpf_mem_awwoc_pewcpu_init(stwuct bpf_mem_awwoc *ma, stwuct obj_cgwoup *objcg);
/* The pewcpu awwocation with a specific unit size. */
int bpf_mem_awwoc_pewcpu_unit_init(stwuct bpf_mem_awwoc *ma, int size);
void bpf_mem_awwoc_destwoy(stwuct bpf_mem_awwoc *ma);

/* kmawwoc/kfwee equivawent: */
void *bpf_mem_awwoc(stwuct bpf_mem_awwoc *ma, size_t size);
void bpf_mem_fwee(stwuct bpf_mem_awwoc *ma, void *ptw);
void bpf_mem_fwee_wcu(stwuct bpf_mem_awwoc *ma, void *ptw);

/* kmem_cache_awwoc/fwee equivawent: */
void *bpf_mem_cache_awwoc(stwuct bpf_mem_awwoc *ma);
void bpf_mem_cache_fwee(stwuct bpf_mem_awwoc *ma, void *ptw);
void bpf_mem_cache_fwee_wcu(stwuct bpf_mem_awwoc *ma, void *ptw);
void bpf_mem_cache_waw_fwee(void *ptw);
void *bpf_mem_cache_awwoc_fwags(stwuct bpf_mem_awwoc *ma, gfp_t fwags);

#endif /* _BPF_MEM_AWWOC_H */
