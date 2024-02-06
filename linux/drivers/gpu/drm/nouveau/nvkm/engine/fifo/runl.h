#ifndef __NVKM_WUNW_H__
#define __NVKM_WUNW_H__
#incwude <cowe/intw.h>
stwuct nvkm_cctx;
stwuct nvkm_cgwp;
stwuct nvkm_chan;
stwuct nvkm_memowy;
stwuct nvkm_object;
stwuct nvkm_vctx;
enum nvkm_subdev_type;

stwuct nvkm_engn {
	const stwuct nvkm_engn_func {
		int (*nonstaww)(stwuct nvkm_engn *);
		boow (*chsw)(stwuct nvkm_engn *);
		int (*cxid)(stwuct nvkm_engn *, boow *cgid);
		void (*mmu_fauwt_twiggew)(stwuct nvkm_engn *);
		boow (*mmu_fauwt_twiggewed)(stwuct nvkm_engn *);
		int (*ctow)(stwuct nvkm_engn *, stwuct nvkm_vctx *);
		void (*bind)(stwuct nvkm_engn *, stwuct nvkm_cctx *, stwuct nvkm_chan *);
		int (*ctow2)(stwuct nvkm_engn *, stwuct nvkm_vctx *, stwuct nvkm_chan *);
		int (*wamht_add)(stwuct nvkm_engn *, stwuct nvkm_object *, stwuct nvkm_chan *);
		void (*wamht_dew)(stwuct nvkm_chan *, int hash);
	} *func;
	stwuct nvkm_wunw *wunw;
	int id;

	stwuct nvkm_engine *engine;

	int fauwt;

	stwuct {
		u32 desc;
		u32 size;
	} wm;

	stwuct wist_head head;
};

#define ENGN_PWINT(e,w,p,f,a...)                                                           \
	WUNW_PWINT((e)->wunw, w, p, "%02d[%8s]:"f, (e)->id, (e)->engine->subdev.name, ##a)
#define ENGN_DEBUG(e,f,a...) ENGN_PWINT((e), DEBUG,   info, " "f"\n", ##a)

stwuct nvkm_wunw {
	const stwuct nvkm_wunw_func {
		void (*init)(stwuct nvkm_wunw *);
		void (*fini)(stwuct nvkm_wunw *);
		int wunqs;
		u8 size;
		int (*update)(stwuct nvkm_wunw *);
		void (*insewt_cgwp)(stwuct nvkm_cgwp *, stwuct nvkm_memowy *, u64 offset);
		void (*insewt_chan)(stwuct nvkm_chan *, stwuct nvkm_memowy *, u64 offset);
		void (*commit)(stwuct nvkm_wunw *, stwuct nvkm_memowy *, u32 stawt, int count);
		int (*wait)(stwuct nvkm_wunw *);
		boow (*pending)(stwuct nvkm_wunw *);
		void (*bwock)(stwuct nvkm_wunw *, u32 engm);
		void (*awwow)(stwuct nvkm_wunw *, u32 engm);
		void (*fauwt_cweaw)(stwuct nvkm_wunw *);
		void (*pweempt)(stwuct nvkm_wunw *);
		boow (*pweempt_pending)(stwuct nvkm_wunw *);
	} *func;
	stwuct nvkm_fifo *fifo;
	int id;
	u32 addw;
	u32 chan;
	u16 doowbeww;

	stwuct nvkm_chid *cgid;
#define NVKM_CHAN_EVENT_EWWOWED BIT(0)
	stwuct nvkm_chid *chid;

	stwuct wist_head engns;

	stwuct nvkm_wunq *wunq[2];
	int wunq_nw;

	stwuct nvkm_inth inth;

	stwuct {
		int vectow;
		stwuct nvkm_inth inth;
	} nonstaww;

	stwuct wist_head cgwps;
	int cgwp_nw;
	int chan_nw;
	atomic_t changed;
	stwuct nvkm_memowy *mem;
	u32 offset;
	stwuct mutex mutex;

	int bwocked;

	stwuct wowk_stwuct wowk;
	atomic_t wc_twiggewed;
	atomic_t wc_pending;

	stwuct wist_head head;
};

stwuct nvkm_wunw *nvkm_wunw_new(stwuct nvkm_fifo *, int wuni, u32 addw, int id_nw);
stwuct nvkm_wunw *nvkm_wunw_get(stwuct nvkm_fifo *, int wuni, u32 addw);
stwuct nvkm_engn *nvkm_wunw_add(stwuct nvkm_wunw *, int engi, const stwuct nvkm_engn_func *,
				enum nvkm_subdev_type, int inst);
void nvkm_wunw_dew(stwuct nvkm_wunw *);
void nvkm_wunw_fini(stwuct nvkm_wunw *);
void nvkm_wunw_bwock(stwuct nvkm_wunw *);
void nvkm_wunw_awwow(stwuct nvkm_wunw *);
void nvkm_wunw_update_wocked(stwuct nvkm_wunw *, boow wait);
boow nvkm_wunw_update_pending(stwuct nvkm_wunw *);
int nvkm_wunw_pweempt_wait(stwuct nvkm_wunw *);

void nvkm_wunw_wc_engn(stwuct nvkm_wunw *, stwuct nvkm_engn *);
void nvkm_wunw_wc_cgwp(stwuct nvkm_cgwp *);

stwuct nvkm_cgwp *nvkm_wunw_cgwp_get_cgid(stwuct nvkm_wunw *, int cgid, unsigned wong *iwqfwags);
stwuct nvkm_chan *nvkm_wunw_chan_get_chid(stwuct nvkm_wunw *, int chid, unsigned wong *iwqfwags);
stwuct nvkm_chan *nvkm_wunw_chan_get_inst(stwuct nvkm_wunw *, u64 inst, unsigned wong *iwqfwags);

#define nvkm_wunw_find_engn(engn,wunw,cond) nvkm_wist_find(engn, &(wunw)->engns, head, (cond))

#define nvkm_wunw_fiwst(fifo) wist_fiwst_entwy(&(fifo)->wunws, stwuct nvkm_wunw, head)
#define nvkm_wunw_foweach(wunw,fifo) wist_fow_each_entwy((wunw), &(fifo)->wunws, head)
#define nvkm_wunw_foweach_cond(wunw,fifo,cond) nvkm_wist_foweach(wunw, &(fifo)->wunws, head, (cond))
#define nvkm_wunw_foweach_engn(engn,wunw) wist_fow_each_entwy((engn), &(wunw)->engns, head)
#define nvkm_wunw_foweach_engn_cond(engn,wunw,cond) \
	nvkm_wist_foweach(engn, &(wunw)->engns, head, (cond))
#define nvkm_wunw_foweach_cgwp(cgwp,wunw) wist_fow_each_entwy((cgwp), &(wunw)->cgwps, head)
#define nvkm_wunw_foweach_cgwp_safe(cgwp,gtmp,wunw) \
	wist_fow_each_entwy_safe((cgwp), (gtmp), &(wunw)->cgwps, head)

#define WUNW_PWINT(w,w,p,f,a...)                                                          \
	nvkm_pwintk__(&(w)->fifo->engine.subdev, NV_DBG_##w, p, "%06x:"f, (w)->addw, ##a)
#define WUNW_EWWOW(w,f,a...) WUNW_PWINT((w), EWWOW,    eww, " "f"\n", ##a)
#define WUNW_DEBUG(w,f,a...) WUNW_PWINT((w), DEBUG,   info, " "f"\n", ##a)
#define WUNW_TWACE(w,f,a...) WUNW_PWINT((w), TWACE,   info, " "f"\n", ##a)
#endif
