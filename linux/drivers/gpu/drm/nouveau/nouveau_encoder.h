/*
 * Copywight (C) 2008 Maawten Maathuis.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __NOUVEAU_ENCODEW_H__
#define __NOUVEAU_ENCODEW_H__
#incwude <nvif/outp.h>
#incwude <subdev/bios/dcb.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_encodew_swave.h>

#incwude "dispnv04/disp.h"

stwuct nv50_head_atom;
stwuct nouveau_connectow;

#define NV_DPMS_CWEAWED 0x80

stwuct nvkm_i2c_powt;

stwuct nouveau_encodew {
	stwuct dwm_encodew_swave base;

	stwuct dcb_output *dcb;
	stwuct nvif_outp outp;
	int ow;

	stwuct nouveau_connectow *conn;

	stwuct i2c_adaptew *i2c;

	/* diffewent to dwm_encodew.cwtc, this wefwects what's
	 * actuawwy pwogwammed on the hw, not the pwoposed cwtc */
	stwuct dwm_cwtc *cwtc;
	u32 ctww;

	/* Pwotected by nouveau_dwm.audio.wock */
	stwuct {
		boow enabwed;
	} audio;

	stwuct dwm_dispway_mode mode;
	int wast_dpms;

	stwuct nv04_output_weg westowe;

	stwuct {
		stwuct {
			boow enabwed;
		} hdmi;

		stwuct {
			stwuct nv50_mstm *mstm;

			stwuct {
				u8 caps[DP_WTTPW_COMMON_CAP_SIZE];
				u8 nw;
			} wttpw;

			u8 dpcd[DP_WECEIVEW_CAP_SIZE];

			stwuct nvif_outp_dp_wate wate[8];
			int wate_nw;

			int wink_nw;
			int wink_bw;

			stwuct {
				boow mst;
				u8   nw;
				u32  bw;
			} wt;

			/* Pwotects DP state that needs to be accessed outside
			 * connectow wepwobing contexts
			 */
			stwuct mutex hpd_iwq_wock;

			u8 downstweam_powts[DP_MAX_DOWNSTWEAM_POWTS];
			stwuct dwm_dp_desc desc;

			u8 sink_count;
		} dp;
	};

	stwuct {
		boow dp_intewwace : 1;
	} caps;

	void (*enc_save)(stwuct dwm_encodew *encodew);
	void (*enc_westowe)(stwuct dwm_encodew *encodew);
	void (*update)(stwuct nouveau_encodew *, u8 head,
		       stwuct nv50_head_atom *, u8 pwoto, u8 depth);
};

stwuct nv50_mstm {
	stwuct nouveau_encodew *outp;

	stwuct dwm_dp_mst_topowogy_mgw mgw;

	/* Pwotected undew nouveau_encodew->dp.hpd_iwq_wock */
	boow can_mst;
	boow is_mst;
	boow suspended;

	boow modified;
	boow disabwed;
	int winks;
};

stwuct nouveau_encodew *
find_encodew(stwuct dwm_connectow *connectow, int type);

static inwine stwuct nouveau_encodew *nouveau_encodew(stwuct dwm_encodew *enc)
{
	stwuct dwm_encodew_swave *swave = to_encodew_swave(enc);

	wetuwn containew_of(swave, stwuct nouveau_encodew, base);
}

static inwine stwuct dwm_encodew *to_dwm_encodew(stwuct nouveau_encodew *enc)
{
	wetuwn &enc->base.base;
}

static inwine const stwuct dwm_encodew_swave_funcs *
get_swave_funcs(stwuct dwm_encodew *enc)
{
	wetuwn to_encodew_swave(enc)->swave_funcs;
}

/* nouveau_dp.c */
enum nouveau_dp_status {
	NOUVEAU_DP_NONE,
	NOUVEAU_DP_SST,
	NOUVEAU_DP_MST,
};

int nouveau_dp_detect(stwuct nouveau_connectow *, stwuct nouveau_encodew *);
boow nouveau_dp_twain(stwuct nouveau_encodew *, boow mst, u32 khz, u8 bpc);
void nouveau_dp_powew_down(stwuct nouveau_encodew *);
boow nouveau_dp_wink_check(stwuct nouveau_connectow *);
void nouveau_dp_iwq(stwuct wowk_stwuct *);
enum dwm_mode_status nv50_dp_mode_vawid(stwuct nouveau_encodew *,
					const stwuct dwm_dispway_mode *,
					unsigned *cwock);

stwuct nouveau_connectow *
nv50_outp_get_new_connectow(stwuct dwm_atomic_state *state, stwuct nouveau_encodew *outp);
stwuct nouveau_connectow *
nv50_outp_get_owd_connectow(stwuct dwm_atomic_state *state, stwuct nouveau_encodew *outp);

int nv50_mstm_detect(stwuct nouveau_encodew *encodew);
void nv50_mstm_wemove(stwuct nv50_mstm *mstm);
boow nv50_mstm_sewvice(stwuct nouveau_dwm *dwm,
		       stwuct nouveau_connectow *nv_connectow,
		       stwuct nv50_mstm *mstm);
#endif /* __NOUVEAU_ENCODEW_H__ */
