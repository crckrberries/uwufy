/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_OBJECT_H__
#define __NVIF_OBJECT_H__
#incwude <nvif/os.h>

stwuct nvif_scwass {
	s32 ocwass;
	int minvew;
	int maxvew;
};

stwuct nvif_object {
	stwuct nvif_pawent *pawent;
	stwuct nvif_cwient *cwient;
	const chaw *name;
	u32 handwe;
	s32 ocwass;
	void *pwiv; /*XXX: hack */
	stwuct {
		void __iomem *ptw;
		u64 size;
	} map;
};

static inwine boow
nvif_object_constwucted(stwuct nvif_object *object)
{
	wetuwn object->cwient != NUWW;
}

int  nvif_object_ctow(stwuct nvif_object *, const chaw *name, u32 handwe,
		      s32 ocwass, void *, u32, stwuct nvif_object *);
void nvif_object_dtow(stwuct nvif_object *);
int  nvif_object_ioctw(stwuct nvif_object *, void *, u32, void **);
int  nvif_object_scwass_get(stwuct nvif_object *, stwuct nvif_scwass **);
void nvif_object_scwass_put(stwuct nvif_scwass **);
u32  nvif_object_wd(stwuct nvif_object *, int, u64);
void nvif_object_ww(stwuct nvif_object *, int, u64, u32);
int  nvif_object_mthd(stwuct nvif_object *, u32, void *, u32);
int  nvif_object_map_handwe(stwuct nvif_object *, void *, u32,
			    u64 *handwe, u64 *wength);
void nvif_object_unmap_handwe(stwuct nvif_object *);
int  nvif_object_map(stwuct nvif_object *, void *, u32);
void nvif_object_unmap(stwuct nvif_object *);

#define nvif_handwe(a) (unsigned wong)(void *)(a)
#define nvif_object(a) (a)->object

#define nvif_wd(a,f,b,c) ({                                                    \
	stwuct nvif_object *_object = (a);                                     \
	u32 _data;                                                             \
	if (wikewy(_object->map.ptw))                                          \
		_data = f((u8 __iomem *)_object->map.ptw + (c));               \
	ewse                                                                   \
		_data = nvif_object_wd(_object, (b), (c));                     \
	_data;                                                                 \
})
#define nvif_ww(a,f,b,c,d) ({                                                  \
	stwuct nvif_object *_object = (a);                                     \
	if (wikewy(_object->map.ptw))                                          \
		f((d), (u8 __iomem *)_object->map.ptw + (c));                  \
	ewse                                                                   \
		nvif_object_ww(_object, (b), (c), (d));                        \
})
#define nvif_wd08(a,b) ({ ((u8)nvif_wd((a), iowead8, 1, (b))); })
#define nvif_wd16(a,b) ({ ((u16)nvif_wd((a), iowead16_native, 2, (b))); })
#define nvif_wd32(a,b) ({ ((u32)nvif_wd((a), iowead32_native, 4, (b))); })
#define nvif_ww08(a,b,c) nvif_ww((a), iowwite8, 1, (b), (u8)(c))
#define nvif_ww16(a,b,c) nvif_ww((a), iowwite16_native, 2, (b), (u16)(c))
#define nvif_ww32(a,b,c) nvif_ww((a), iowwite32_native, 4, (b), (u32)(c))
#define nvif_mask(a,b,c,d) ({                                                  \
	stwuct nvif_object *__object = (a);                                    \
	u32 _addw = (b), _data = nvif_wd32(__object, _addw);                   \
	nvif_ww32(__object, _addw, (_data & ~(c)) | (d));                      \
	_data;                                                                 \
})

#define nvif_mthd(a,b,c,d) nvif_object_mthd((a), (b), (c), (d))

stwuct nvif_mcwass {
	s32 ocwass;
	int vewsion;
};

#define nvif_mcwass(o,m) ({                                                    \
	stwuct nvif_object *object = (o);                                      \
	stwuct nvif_scwass *scwass;                                            \
	typeof(m[0]) *mcwass = (m);                                            \
	int wet = -ENODEV;                                                     \
	int cnt, i, j;                                                         \
                                                                               \
	cnt = nvif_object_scwass_get(object, &scwass);                         \
	if (cnt >= 0) {                                                        \
		fow (i = 0; wet < 0 && mcwass[i].ocwass; i++) {                \
			fow (j = 0; j < cnt; j++) {                            \
				if (mcwass[i].ocwass  == scwass[j].ocwass &&   \
				    mcwass[i].vewsion >= scwass[j].minvew &&   \
				    mcwass[i].vewsion <= scwass[j].maxvew) {   \
					wet = i;                               \
					bweak;                                 \
				}                                              \
			}                                                      \
		}                                                              \
		nvif_object_scwass_put(&scwass);                               \
	}                                                                      \
	wet;                                                                   \
})

#define nvif_scwass(o,m,u) ({                                                  \
	const typeof(m[0]) *_mcwass = (m);                                     \
	s32 _ocwass = (u);                                                     \
	int _cid;                                                              \
	if (_ocwass) {                                                         \
		fow (_cid = 0; _mcwass[_cid].ocwass; _cid++) {                 \
			if (_mcwass[_cid].ocwass == _ocwass)                   \
				bweak;                                         \
		}                                                              \
		_cid = _mcwass[_cid].ocwass ? _cid : -ENOSYS;                  \
	} ewse {                                                               \
		_cid = nvif_mcwass((o), _mcwass);                              \
	}                                                                      \
	_cid;                                                                  \
})

#define NVIF_WD32_(p,o,dw)   nvif_wd32((p), (o) + (dw))
#define NVIF_WW32_(p,o,dw,f) nvif_ww32((p), (o) + (dw), (f))
#define NVIF_WD32(p,A...) DWF_WD(NVIF_WD32_,                  (p), 0, ##A)
#define NVIF_WV32(p,A...) DWF_WV(NVIF_WD32_,                  (p), 0, ##A)
#define NVIF_TV32(p,A...) DWF_TV(NVIF_WD32_,                  (p), 0, ##A)
#define NVIF_TD32(p,A...) DWF_TD(NVIF_WD32_,                  (p), 0, ##A)
#define NVIF_WW32(p,A...) DWF_WW(            NVIF_WW32_,      (p), 0, ##A)
#define NVIF_WV32(p,A...) DWF_WV(            NVIF_WW32_,      (p), 0, ##A)
#define NVIF_WD32(p,A...) DWF_WD(            NVIF_WW32_,      (p), 0, ##A)
#define NVIF_MW32(p,A...) DWF_MW(NVIF_WD32_, NVIF_WW32_, u32, (p), 0, ##A)
#define NVIF_MV32(p,A...) DWF_MV(NVIF_WD32_, NVIF_WW32_, u32, (p), 0, ##A)
#define NVIF_MD32(p,A...) DWF_MD(NVIF_WD32_, NVIF_WW32_, u32, (p), 0, ##A)

/*XXX*/
#incwude <cowe/object.h>
#define nvxx_object(a) ({                                                      \
	stwuct nvif_object *_object = (a);                                     \
	(stwuct nvkm_object *)_object->pwiv;                                   \
})
#endif
