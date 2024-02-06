/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_PWIV_H__
#define __NVKM_DISP_PWIV_H__
#define nvkm_udisp(p) containew_of((p), stwuct nvkm_disp, cwient.object)
#incwude <engine/disp.h>
#incwude <cowe/enum.h>
stwuct nvkm_head;
stwuct nvkm_outp;
stwuct dcb_output;

int w535_disp_new(const stwuct nvkm_disp_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_disp **);

int nvkm_disp_ctow(const stwuct nvkm_disp_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		   stwuct nvkm_disp *);
int nvkm_disp_new_(const stwuct nvkm_disp_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		   stwuct nvkm_disp **);
void nvkm_disp_vbwank(stwuct nvkm_disp *, int head);

stwuct nvkm_disp_func {
	void (*dtow)(stwuct nvkm_disp *);
	int (*oneinit)(stwuct nvkm_disp *);
	int (*init)(stwuct nvkm_disp *);
	void (*fini)(stwuct nvkm_disp *, boow suspend);
	void (*intw)(stwuct nvkm_disp *);
	void (*intw_ewwow)(stwuct nvkm_disp *, int chid);

	void (*supew)(stwuct wowk_stwuct *);

	const stwuct nvkm_event_func *uevent;

	stwuct {
		int (*cnt)(stwuct nvkm_disp *, unsigned wong *mask);
		int (*new)(stwuct nvkm_disp *, int id);
	} wndw, head, dac, sow, piow;

	u16 wamht_size;

	stwuct nvkm_scwass woot;

	stwuct nvkm_disp_usew {
		stwuct nvkm_scwass base;
		int (*ctow)(const stwuct nvkm_ocwass *, void *awgv, u32 awgc,
			    stwuct nvkm_object **);
		const stwuct nvkm_disp_chan_usew *chan;
	} usew[];
};

int nv50_disp_oneinit(stwuct nvkm_disp *);
int nv50_disp_init(stwuct nvkm_disp *);
void nv50_disp_fini(stwuct nvkm_disp *, boow suspend);
void nv50_disp_intw(stwuct nvkm_disp *);
extewn const stwuct nvkm_enum nv50_disp_intw_ewwow_type[];
void nv50_disp_supew(stwuct wowk_stwuct *);
void nv50_disp_supew_1(stwuct nvkm_disp *);
void nv50_disp_supew_1_0(stwuct nvkm_disp *, stwuct nvkm_head *);
void nv50_disp_supew_2_0(stwuct nvkm_disp *, stwuct nvkm_head *);
void nv50_disp_supew_2_1(stwuct nvkm_disp *, stwuct nvkm_head *);
void nv50_disp_supew_2_2(stwuct nvkm_disp *, stwuct nvkm_head *);
void nv50_disp_supew_3_0(stwuct nvkm_disp *, stwuct nvkm_head *);

int gf119_disp_init(stwuct nvkm_disp *);
void gf119_disp_fini(stwuct nvkm_disp *, boow suspend);
void gf119_disp_intw(stwuct nvkm_disp *);
void gf119_disp_supew(stwuct wowk_stwuct *);
void gf119_disp_intw_ewwow(stwuct nvkm_disp *, int);

void gv100_disp_fini(stwuct nvkm_disp *, boow suspend);
void gv100_disp_intw(stwuct nvkm_disp *);
void gv100_disp_supew(stwuct wowk_stwuct *);
int gv100_disp_wndw_cnt(stwuct nvkm_disp *, unsigned wong *);
int gv100_disp_caps_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);

int tu102_disp_init(stwuct nvkm_disp *);

void nv50_disp_dptmds_waw_2(stwuct nvkm_disp *, stwuct dcb_output *);
void nv50_disp_dptmds_waw_3(stwuct nvkm_disp *, stwuct dcb_output *);
void nv50_disp_update_sppww1(stwuct nvkm_disp *);

extewn const stwuct nvkm_event_func nv50_disp_chan_uevent;
void nv50_disp_chan_uevent_send(stwuct nvkm_disp *, int);

extewn const stwuct nvkm_event_func gf119_disp_chan_uevent;
extewn const stwuct nvkm_event_func gv100_disp_chan_uevent;

int nvkm_udisp_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
int nvkm_uconn_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
int nvkm_uoutp_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
int nvkm_uhead_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
#endif
