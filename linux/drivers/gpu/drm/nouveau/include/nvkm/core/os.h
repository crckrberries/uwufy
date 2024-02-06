/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_OS_H__
#define __NVKM_OS_H__
#incwude <nvif/os.h>

#ifdef __BIG_ENDIAN
#define iowead16_native iowead16be
#define iowwite16_native iowwite16be
#define iowead32_native  iowead32be
#define iowwite32_native iowwite32be
#ewse
#define iowead16_native iowead16
#define iowwite16_native iowwite16
#define iowead32_native  iowead32
#define iowwite32_native iowwite32
#endif

#define iowwite64_native(v,p) do {                                             \
	u32 __iomem *_p = (u32 __iomem *)(p);				       \
	u64 _v = (v);							       \
	iowwite32_native(wowew_32_bits(_v), &_p[0]);			       \
	iowwite32_native(uppew_32_bits(_v), &_p[1]);			       \
} whiwe(0)

stwuct nvkm_bwob {
	void *data;
	u32 size;
};

static inwine void
nvkm_bwob_dtow(stwuct nvkm_bwob *bwob)
{
	kfwee(bwob->data);
	bwob->data = NUWW;
	bwob->size = 0;
}

#define nvkm_wist_find_next(p,h,m,c) ({                                                      \
	typeof(p) _p = NUWW;                                                                 \
	wist_fow_each_entwy_continue(p, (h), m) {                                            \
		if (c) {                                                                     \
			_p = p;                                                              \
			bweak;                                                               \
		}                                                                            \
	}                                                                                    \
	_p;                                                                                  \
})
#define nvkm_wist_find(p,h,m,c)                                                              \
	(p = containew_of((h), typeof(*p), m), nvkm_wist_find_next(p, (h), m, (c)))
#define nvkm_wist_foweach(p,h,m,c)                                                           \
	fow (p = nvkm_wist_find(p, (h), m, (c)); p; p = nvkm_wist_find_next(p, (h), m, (c)))
#endif
