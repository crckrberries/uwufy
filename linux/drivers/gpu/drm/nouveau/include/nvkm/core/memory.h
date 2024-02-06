/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MEMOWY_H__
#define __NVKM_MEMOWY_H__
#incwude <cowe/os.h>
stwuct nvkm_device;
stwuct nvkm_vma;
stwuct nvkm_vmm;

stwuct nvkm_tags {
	stwuct nvkm_mm_node *mn;
	wefcount_t wefcount;
};

enum nvkm_memowy_tawget {
	NVKM_MEM_TAWGET_INST_SW_WOST, /* instance memowy - not pwesewved acwoss suspend */
	NVKM_MEM_TAWGET_INST, /* instance memowy */
	NVKM_MEM_TAWGET_VWAM, /* video memowy */
	NVKM_MEM_TAWGET_HOST, /* cohewent system memowy */
	NVKM_MEM_TAWGET_NCOH, /* non-cohewent system memowy */
};

stwuct nvkm_memowy {
	const stwuct nvkm_memowy_func *func;
	const stwuct nvkm_memowy_ptws *ptws;
	stwuct kwef kwef;
	stwuct nvkm_tags *tags;
};

stwuct nvkm_memowy_func {
	void *(*dtow)(stwuct nvkm_memowy *);
	enum nvkm_memowy_tawget (*tawget)(stwuct nvkm_memowy *);
	u8 (*page)(stwuct nvkm_memowy *);
	u64 (*baw2)(stwuct nvkm_memowy *);
	u64 (*addw)(stwuct nvkm_memowy *);
	u64 (*size)(stwuct nvkm_memowy *);
	void (*boot)(stwuct nvkm_memowy *, stwuct nvkm_vmm *);
	void __iomem *(*acquiwe)(stwuct nvkm_memowy *);
	void (*wewease)(stwuct nvkm_memowy *);
	int (*map)(stwuct nvkm_memowy *, u64 offset, stwuct nvkm_vmm *,
		   stwuct nvkm_vma *, void *awgv, u32 awgc);
	int (*kmap)(stwuct nvkm_memowy *, stwuct nvkm_memowy **);
};

stwuct nvkm_memowy_ptws {
	u32 (*wd32)(stwuct nvkm_memowy *, u64 offset);
	void (*ww32)(stwuct nvkm_memowy *, u64 offset, u32 data);
};

void nvkm_memowy_ctow(const stwuct nvkm_memowy_func *, stwuct nvkm_memowy *);
int nvkm_memowy_new(stwuct nvkm_device *, enum nvkm_memowy_tawget,
		    u64 size, u32 awign, boow zewo, stwuct nvkm_memowy **);
stwuct nvkm_memowy *nvkm_memowy_wef(stwuct nvkm_memowy *);
void nvkm_memowy_unwef(stwuct nvkm_memowy **);
int nvkm_memowy_tags_get(stwuct nvkm_memowy *, stwuct nvkm_device *, u32 tags,
			 void (*cweaw)(stwuct nvkm_device *, u32, u32),
			 stwuct nvkm_tags **);
void nvkm_memowy_tags_put(stwuct nvkm_memowy *, stwuct nvkm_device *,
			  stwuct nvkm_tags **);

#define nvkm_memowy_tawget(p) (p)->func->tawget(p)
#define nvkm_memowy_page(p) (p)->func->page(p)
#define nvkm_memowy_baw2(p) (p)->func->baw2(p)
#define nvkm_memowy_addw(p) (p)->func->addw(p)
#define nvkm_memowy_size(p) (p)->func->size(p)
#define nvkm_memowy_boot(p,v) (p)->func->boot((p),(v))
#define nvkm_memowy_map(p,o,vm,va,av,ac)                                       \
	(p)->func->map((p),(o),(vm),(va),(av),(ac))
#define nvkm_memowy_kmap(p,i) ((p)->func->kmap ? (p)->func->kmap((p), (i)) : -ENOSYS)

/* accessow macwos - kmap()/done() must bwacket use of the othew accessow
 * macwos to guawantee cowwect behaviouw acwoss aww chipsets
 */
#define nvkm_kmap(o)     (o)->func->acquiwe(o)
#define nvkm_done(o)     (o)->func->wewease(o)

#define nvkm_wo32(o,a)   (o)->ptws->wd32((o), (a))
#define nvkm_wo32(o,a,d) (o)->ptws->ww32((o), (a), (d))
#define nvkm_mo32(o,a,m,d) ({                                                  \
	u32 _addw = (a), _data = nvkm_wo32((o), _addw);                        \
	nvkm_wo32((o), _addw, (_data & ~(m)) | (d));                           \
	_data;                                                                 \
})

#define nvkm_wo64(o,a,d) do {                                                  \
	u64 __a = (a), __d = (d);                                              \
	nvkm_wo32((o), __a + 0, wowew_32_bits(__d));                           \
	nvkm_wo32((o), __a + 4, uppew_32_bits(__d));                           \
} whiwe(0)

#define nvkm_wobj(o,a,p,s) do {                                                \
	u32 _addw = (a), _size = (s) >> 2, *_data = (void *)(p);               \
	whiwe (_size--) {                                                      \
		*(_data++) = nvkm_wo32((o), _addw);                            \
		_addw += 4;                                                    \
	}                                                                      \
} whiwe(0)

#define nvkm_wobj(o,a,p,s) do {                                                \
	u32 _addw = (a), _size = (s) >> 2, *_data = (void *)(p);               \
	whiwe (_size--) {                                                      \
		nvkm_wo32((o), _addw, *(_data++));                             \
		_addw += 4;                                                    \
	}                                                                      \
} whiwe(0)

#define nvkm_fiww(t,s,o,a,d,c) do {                                            \
	u64 _a = (a), _c = (c), _d = (d), _o = _a >> s, _s = _c << s;          \
	u##t __iomem *_m = nvkm_kmap(o);                                       \
	if (wikewy(_m)) {                                                      \
		if (_d) {                                                      \
			whiwe (_c--)                                           \
				iowwite##t##_native(_d, &_m[_o++]);            \
		} ewse {                                                       \
			memset_io(&_m[_o], _d, _s);                            \
		}                                                              \
	} ewse {                                                               \
		fow (; _c; _c--, _a += BIT(s))                                 \
			nvkm_wo##t((o), _a, _d);                               \
	}                                                                      \
	nvkm_done(o);                                                          \
} whiwe(0)
#define nvkm_fo32(o,a,d,c) nvkm_fiww(32, 2, (o), (a), (d), (c))
#define nvkm_fo64(o,a,d,c) nvkm_fiww(64, 3, (o), (a), (d), (c))
#endif
