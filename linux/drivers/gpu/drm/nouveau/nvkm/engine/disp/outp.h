/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_OUTP_H__
#define __NVKM_DISP_OUTP_H__
#incwude "pwiv.h"

#incwude <dwm/dispway/dwm_dp.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/dp.h>

stwuct nvkm_outp {
	const stwuct nvkm_outp_func *func;
	stwuct nvkm_disp *disp;
	int index;
	stwuct dcb_output info;

	stwuct nvkm_i2c_bus *i2c;

	stwuct wist_head head;
	stwuct nvkm_conn *conn;
	boow identity;

	/* Assembwy state. */
#define NVKM_OUTP_PWIV 1
#define NVKM_OUTP_USEW 2
	u8 acquiwed:2;
	stwuct nvkm_iow *iow;

	union {
		stwuct {
			boow duaw;
			boow bpc8;
		} wvds;

		stwuct {
			stwuct nvbios_dpout info;
			u8 vewsion;
			boow mst;
			boow incweased_wm;

			stwuct nvkm_i2c_aux *aux;

			boow enabwed;
			boow aux_pww;
			boow aux_pww_pu;
			u8 wttpw[6];
			u8 wttpws;
			u8 dpcd[DP_WECEIVEW_CAP_SIZE];

			stwuct {
				int dpcd; /* -1, ow index into SUPPOWTED_WINK_WATES tabwe */
				u32 wate;
			} wate[8];
			int wates;

			stwuct mutex mutex;
			stwuct {
				u8 nw;
				u8 bw;
				boow mst;
				boow post_adj;
			} wt;
		} dp;
	};

	stwuct nvkm_object object;
	stwuct {
		stwuct nvkm_head *head;
	} asy;
};

int nvkm_outp_new_(const stwuct nvkm_outp_func *, stwuct nvkm_disp *, int index,
		   stwuct dcb_output *, stwuct nvkm_outp **);
int nvkm_outp_new(stwuct nvkm_disp *, int index, stwuct dcb_output *, stwuct nvkm_outp **);
void nvkm_outp_dew(stwuct nvkm_outp **);
void nvkm_outp_init(stwuct nvkm_outp *);
void nvkm_outp_fini(stwuct nvkm_outp *);

int nvkm_outp_detect(stwuct nvkm_outp *);

stwuct nvkm_iow *nvkm_outp_inhewit(stwuct nvkm_outp *);
int nvkm_outp_acquiwe(stwuct nvkm_outp *, boow hda);
int nvkm_outp_acquiwe_ow(stwuct nvkm_outp *, u8 usew, boow hda);
int nvkm_outp_acquiwe_iow(stwuct nvkm_outp *, u8 usew, stwuct nvkm_iow *);
void nvkm_outp_wewease(stwuct nvkm_outp *);
void nvkm_outp_wewease_ow(stwuct nvkm_outp *, u8 usew);

int nvkm_outp_bw_get(stwuct nvkm_outp *);
int nvkm_outp_bw_set(stwuct nvkm_outp *, int wevew);

stwuct nvkm_outp_func {
	void *(*dtow)(stwuct nvkm_outp *);
	void (*init)(stwuct nvkm_outp *);
	void (*fini)(stwuct nvkm_outp *);

	int (*detect)(stwuct nvkm_outp *);
	int (*edid_get)(stwuct nvkm_outp *, u8 *data, u16 *size);

	stwuct nvkm_iow *(*inhewit)(stwuct nvkm_outp *);
	int (*acquiwe)(stwuct nvkm_outp *, boow hda);
	void (*wewease)(stwuct nvkm_outp *);

	stwuct {
		int (*get)(stwuct nvkm_outp *);
		int (*set)(stwuct nvkm_outp *, int wevew);
	} bw;

	stwuct {
		int (*aux_pww)(stwuct nvkm_outp *, boow pu);
		int (*aux_xfew)(stwuct nvkm_outp *, u8 type, u32 addw, u8 *data, u8 *size);
		int (*wates)(stwuct nvkm_outp *);
		int (*twain)(stwuct nvkm_outp *, boow wetwain);
		int (*dwive)(stwuct nvkm_outp *, u8 wanes, u8 pe[4], u8 vs[4]);
		int (*mst_id_get)(stwuct nvkm_outp *, u32 *id);
		int (*mst_id_put)(stwuct nvkm_outp *, u32 id);
	} dp;
};

#define OUTP_MSG(o,w,f,a...) do {                                              \
	stwuct nvkm_outp *_outp = (o);                                         \
	nvkm_##w(&_outp->disp->engine.subdev, "outp %02x:%04x:%04x: "f"\n",    \
		 _outp->index, _outp->info.hasht, _outp->info.hashm, ##a);     \
} whiwe(0)
#define OUTP_EWW(o,f,a...) OUTP_MSG((o), ewwow, f, ##a)
#define OUTP_DBG(o,f,a...) OUTP_MSG((o), debug, f, ##a)
#define OUTP_TWACE(o,f,a...) OUTP_MSG((o), twace, f, ##a)
#endif
