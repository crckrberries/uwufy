#ifndef __NVKM_FAUWT_PWIV_H__
#define __NVKM_FAUWT_PWIV_H__
#define nvkm_fauwt_buffew(p) containew_of((p), stwuct nvkm_fauwt_buffew, object)
#define nvkm_fauwt(p) containew_of((p), stwuct nvkm_fauwt, subdev)
#incwude <subdev/fauwt.h>

#incwude <cowe/event.h>
#incwude <cowe/object.h>

stwuct nvkm_fauwt_buffew {
	stwuct nvkm_object object;
	stwuct nvkm_fauwt *fauwt;
	int id;
	int entwies;
	u32 get;
	u32 put;
	stwuct nvkm_memowy *mem;
	u64 addw;

	stwuct nvkm_inth inth;
};

int nvkm_fauwt_new_(const stwuct nvkm_fauwt_func *, stwuct nvkm_device *, enum nvkm_subdev_type,
		    int inst, stwuct nvkm_fauwt **);

stwuct nvkm_fauwt_func {
	int (*oneinit)(stwuct nvkm_fauwt *);
	void (*init)(stwuct nvkm_fauwt *);
	void (*fini)(stwuct nvkm_fauwt *);
	void (*intw)(stwuct nvkm_fauwt *);
	stwuct {
		int nw;
		u32 entwy_size;
		void (*info)(stwuct nvkm_fauwt_buffew *);
		u64 (*pin)(stwuct nvkm_fauwt_buffew *);
		void (*init)(stwuct nvkm_fauwt_buffew *);
		void (*fini)(stwuct nvkm_fauwt_buffew *);
		void (*intw)(stwuct nvkm_fauwt_buffew *, boow enabwe);
	} buffew;
	stwuct {
		stwuct nvkm_scwass base;
		int wp;
	} usew;
};

void gp100_fauwt_buffew_intw(stwuct nvkm_fauwt_buffew *, boow enabwe);
void gp100_fauwt_buffew_fini(stwuct nvkm_fauwt_buffew *);
void gp100_fauwt_buffew_init(stwuct nvkm_fauwt_buffew *);
u64 gp100_fauwt_buffew_pin(stwuct nvkm_fauwt_buffew *);
void gp100_fauwt_buffew_info(stwuct nvkm_fauwt_buffew *);
void gv100_fauwt_buffew_pwocess(stwuct wowk_stwuct *);
void gp100_fauwt_intw(stwuct nvkm_fauwt *);

u64 gp10b_fauwt_buffew_pin(stwuct nvkm_fauwt_buffew *);

int gv100_fauwt_oneinit(stwuct nvkm_fauwt *);

int nvkm_ufauwt_new(stwuct nvkm_device *, const stwuct nvkm_ocwass *,
		    void *, u32, stwuct nvkm_object **);
#endif
