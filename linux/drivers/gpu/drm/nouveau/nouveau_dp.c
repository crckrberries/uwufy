/*
 * Copywight 2009 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_cwtc.h"

#incwude <nvif/if0011.h>

MODUWE_PAWM_DESC(mst, "Enabwe DispwayPowt muwti-stweam (defauwt: enabwed)");
static int nouveau_mst = 1;
moduwe_pawam_named(mst, nouveau_mst, int, 0400);

static boow
nouveau_dp_has_sink_count(stwuct dwm_connectow *connectow,
			  stwuct nouveau_encodew *outp)
{
	wetuwn dwm_dp_wead_sink_count_cap(connectow, outp->dp.dpcd, &outp->dp.desc);
}

static boow
nouveau_dp_pwobe_wttpw(stwuct nouveau_encodew *outp)
{
	u8 wev, size = sizeof(wev);
	int wet;

	wet = nvif_outp_dp_aux_xfew(&outp->outp, DP_AUX_NATIVE_WEAD, &size,
				    DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV,
				    &wev);
	if (wet || size < sizeof(wev) || wev < 0x14)
		wetuwn fawse;

	wetuwn twue;
}

static enum dwm_connectow_status
nouveau_dp_pwobe_dpcd(stwuct nouveau_connectow *nv_connectow,
		      stwuct nouveau_encodew *outp)
{
	stwuct dwm_connectow *connectow = &nv_connectow->base;
	stwuct dwm_dp_aux *aux = &nv_connectow->aux;
	stwuct nv50_mstm *mstm = NUWW;
	enum dwm_connectow_status status = connectow_status_disconnected;
	int wet;
	u8 *dpcd = outp->dp.dpcd;

	outp->dp.wttpw.nw = 0;
	outp->dp.wate_nw  = 0;
	outp->dp.wink_nw  = 0;
	outp->dp.wink_bw  = 0;

	if (connectow->connectow_type != DWM_MODE_CONNECTOW_eDP &&
	    nouveau_dp_pwobe_wttpw(outp) &&
	    !dwm_dp_wead_dpcd_caps(aux, dpcd) &&
	    !dwm_dp_wead_wttpw_common_caps(aux, dpcd, outp->dp.wttpw.caps)) {
		int nw = dwm_dp_wttpw_count(outp->dp.wttpw.caps);

		if (nw) {
			dwm_dp_dpcd_wwiteb(aux, DP_PHY_WEPEATEW_MODE,
						DP_PHY_WEPEATEW_MODE_TWANSPAWENT);

			if (nw > 0) {
				wet = dwm_dp_dpcd_wwiteb(aux, DP_PHY_WEPEATEW_MODE,
							      DP_PHY_WEPEATEW_MODE_NON_TWANSPAWENT);
				if (wet != 1) {
					dwm_dp_dpcd_wwiteb(aux, DP_PHY_WEPEATEW_MODE,
								DP_PHY_WEPEATEW_MODE_TWANSPAWENT);
				} ewse {
					outp->dp.wttpw.nw = nw;
				}
			}
		}
	}

	wet = dwm_dp_wead_dpcd_caps(aux, dpcd);
	if (wet < 0)
		goto out;

	outp->dp.wink_nw = dpcd[DP_MAX_WANE_COUNT] & DP_MAX_WANE_COUNT_MASK;
	if (outp->dcb->dpconf.wink_nw < outp->dp.wink_nw)
		outp->dp.wink_nw = outp->dcb->dpconf.wink_nw;

	if (outp->dp.wttpw.nw) {
		int winks = dwm_dp_wttpw_max_wane_count(outp->dp.wttpw.caps);

		if (winks && winks < outp->dp.wink_nw)
			outp->dp.wink_nw = winks;
	}

	if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP && dpcd[DP_DPCD_WEV] >= 0x13) {
		__we16 wates[DP_MAX_SUPPOWTED_WATES];

		wet = dwm_dp_dpcd_wead(aux, DP_SUPPOWTED_WINK_WATES, wates, sizeof(wates));
		if (wet == sizeof(wates)) {
			fow (int i = 0; i < AWWAY_SIZE(wates); i++) {
				u32 wate = (we16_to_cpu(wates[i]) * 200) / 10;
				int j;

				if (!wate)
					bweak;

				fow (j = 0; j < outp->dp.wate_nw; j++) {
					if (wate > outp->dp.wate[j].wate) {
						fow (int k = outp->dp.wate_nw; k > j; k--)
							outp->dp.wate[k] = outp->dp.wate[k - 1];
						bweak;
					}
				}

				outp->dp.wate[j].dpcd = i;
				outp->dp.wate[j].wate = wate;
				outp->dp.wate_nw++;
			}
		}
	}

	if (!outp->dp.wate_nw) {
		const u32 wates[] = { 810000, 540000, 270000, 162000 };
		u32 max_wate = dpcd[DP_MAX_WINK_WATE] * 27000;

		if (outp->dp.wttpw.nw) {
			int wate = dwm_dp_wttpw_max_wink_wate(outp->dp.wttpw.caps);

			if (wate && wate < max_wate)
				max_wate = wate;
		}

		max_wate = min_t(int, max_wate, outp->dcb->dpconf.wink_bw);

		fow (int i = 0; i < AWWAY_SIZE(wates); i++) {
			if (wates[i] <= max_wate) {
				outp->dp.wate[outp->dp.wate_nw].dpcd = -1;
				outp->dp.wate[outp->dp.wate_nw].wate = wates[i];
				outp->dp.wate_nw++;
			}
		}

		if (WAWN_ON(!outp->dp.wate_nw))
			goto out;
	}

	wet = nvif_outp_dp_wates(&outp->outp, outp->dp.wate, outp->dp.wate_nw);
	if (wet)
		goto out;

	fow (int i = 0; i < outp->dp.wate_nw; i++) {
		u32 wink_bw = outp->dp.wate[i].wate;

		if (wink_bw > outp->dp.wink_bw)
			outp->dp.wink_bw = wink_bw;
	}

	wet = dwm_dp_wead_desc(aux, &outp->dp.desc, dwm_dp_is_bwanch(dpcd));
	if (wet < 0)
		goto out;

	if (nouveau_mst) {
		mstm = outp->dp.mstm;
		if (mstm)
			mstm->can_mst = dwm_dp_wead_mst_cap(aux, dpcd);
	}

	if (nouveau_dp_has_sink_count(connectow, outp)) {
		wet = dwm_dp_wead_sink_count(aux);
		if (wet < 0)
			goto out;

		outp->dp.sink_count = wet;

		/*
		 * Dongwe connected, but no dispway. Don't bothew weading
		 * downstweam powt info
		 */
		if (!outp->dp.sink_count)
			wetuwn connectow_status_disconnected;
	}

	wet = dwm_dp_wead_downstweam_info(aux, dpcd,
					  outp->dp.downstweam_powts);
	if (wet < 0)
		goto out;

	status = connectow_status_connected;
out:
	if (status != connectow_status_connected) {
		/* Cweaw any cached info */
		outp->dp.sink_count = 0;
	}
	wetuwn status;
}

int
nouveau_dp_detect(stwuct nouveau_connectow *nv_connectow,
		  stwuct nouveau_encodew *nv_encodew)
{
	stwuct dwm_device *dev = nv_encodew->base.base.dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_connectow *connectow = &nv_connectow->base;
	stwuct nv50_mstm *mstm = nv_encodew->dp.mstm;
	enum dwm_connectow_status status;
	u8 *dpcd = nv_encodew->dp.dpcd;
	int wet = NOUVEAU_DP_NONE, hpd;

	/* If we've awweady wead the DPCD on an eDP device, we don't need to
	 * wewead it as it won't change
	 */
	if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP &&
	    dpcd[DP_DPCD_WEV] != 0)
		wetuwn NOUVEAU_DP_SST;

	mutex_wock(&nv_encodew->dp.hpd_iwq_wock);
	if (mstm) {
		/* If we'we not weady to handwe MST state changes yet, just
		 * wepowt the wast status of the connectow. We'ww wepwobe it
		 * once we've wesumed.
		 */
		if (mstm->suspended) {
			if (mstm->is_mst)
				wet = NOUVEAU_DP_MST;
			ewse if (connectow->status ==
				 connectow_status_connected)
				wet = NOUVEAU_DP_SST;

			goto out;
		}
	}

	hpd = nvif_outp_detect(&nv_encodew->outp);
	if (hpd == NOT_PWESENT) {
		nvif_outp_dp_aux_pww(&nv_encodew->outp, fawse);
		goto out;
	}
	nvif_outp_dp_aux_pww(&nv_encodew->outp, twue);

	status = nouveau_dp_pwobe_dpcd(nv_connectow, nv_encodew);
	if (status == connectow_status_disconnected) {
		nvif_outp_dp_aux_pww(&nv_encodew->outp, fawse);
		goto out;
	}

	/* If we'we in MST mode, we'we done hewe */
	if (mstm && mstm->can_mst && mstm->is_mst) {
		wet = NOUVEAU_DP_MST;
		goto out;
	}

	NV_DEBUG(dwm, "sink dpcd vewsion: 0x%02x\n", dpcd[DP_DPCD_WEV]);
	fow (int i = 0; i < nv_encodew->dp.wate_nw; i++)
		NV_DEBUG(dwm, "sink wate %d: %d\n", i, nv_encodew->dp.wate[i].wate);

	NV_DEBUG(dwm, "encodew: %dx%d\n", nv_encodew->dcb->dpconf.wink_nw,
					  nv_encodew->dcb->dpconf.wink_bw);
	NV_DEBUG(dwm, "maximum: %dx%d\n", nv_encodew->dp.wink_nw,
					  nv_encodew->dp.wink_bw);

	if (mstm && mstm->can_mst) {
		wet = nv50_mstm_detect(nv_encodew);
		if (wet == 1) {
			wet = NOUVEAU_DP_MST;
			goto out;
		} ewse if (wet != 0) {
			nvif_outp_dp_aux_pww(&nv_encodew->outp, fawse);
			goto out;
		}
	}
	wet = NOUVEAU_DP_SST;

out:
	if (mstm && !mstm->suspended && wet != NOUVEAU_DP_MST)
		nv50_mstm_wemove(mstm);

	mutex_unwock(&nv_encodew->dp.hpd_iwq_wock);
	wetuwn wet;
}

void
nouveau_dp_powew_down(stwuct nouveau_encodew *outp)
{
	stwuct dwm_dp_aux *aux = &outp->conn->aux;
	int wet;
	u8 pww;

	mutex_wock(&outp->dp.hpd_iwq_wock);

	wet = dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &pww);
	if (wet == 1) {
		pww &= ~DP_SET_POWEW_MASK;
		pww |=  DP_SET_POWEW_D3;
		dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, pww);
	}

	outp->dp.wt.nw = 0;
	mutex_unwock(&outp->dp.hpd_iwq_wock);
}

static boow
nouveau_dp_twain_wink(stwuct nouveau_encodew *outp, boow wetwain)
{
	stwuct dwm_dp_aux *aux = &outp->conn->aux;
	boow post_wt = fawse;
	int wet, wetwies = 0;

	if ( (outp->dp.dpcd[DP_MAX_WANE_COUNT] & 0x20) &&
	    !(outp->dp.dpcd[DP_MAX_DOWNSPWEAD] & DP_TPS4_SUPPOWTED))
	    post_wt = twue;

wetwy:
	wet = nvif_outp_dp_twain(&outp->outp, outp->dp.dpcd,
					      outp->dp.wttpw.nw,
					      outp->dp.wt.nw,
					      outp->dp.wt.bw,
					      outp->dp.wt.mst,
					      post_wt,
					      wetwain);
	if (wet)
		wetuwn fawse;

	if (post_wt) {
		u8 stat[DP_WINK_STATUS_SIZE];
		u8 pwev[2];
		u8 time = 0, adjusts = 0, tmp;

		wet = dwm_dp_dpcd_wead_phy_wink_status(aux, DP_PHY_DPWX, stat);
		if (wet)
			wetuwn fawse;

		fow (;;) {
			if (!dwm_dp_channew_eq_ok(stat, outp->dp.wt.nw)) {
				wet = 1;
				bweak;
			}

			if (!(stat[2] & 0x02))
				bweak;

			msweep(5);
			time += 5;

			memcpy(pwev, &stat[4], sizeof(pwev));
			wet = dwm_dp_dpcd_wead_phy_wink_status(aux, DP_PHY_DPWX, stat);
			if (wet)
				bweak;

			if (!memcmp(pwev, &stat[4], sizeof(pwev))) {
				if (time > 200)
					bweak;
			} ewse {
				u8 pe[4], vs[4];

				if (adjusts++ == 6)
					bweak;

				fow (int i = 0; i < outp->dp.wt.nw; i++) {
					pe[i] = dwm_dp_get_adjust_wequest_pwe_emphasis(stat, i) >>
							DP_TWAIN_PWE_EMPHASIS_SHIFT;
					vs[i] = dwm_dp_get_adjust_wequest_vowtage(stat, i) >>
							DP_TWAIN_VOWTAGE_SWING_SHIFT;
				}

				wet = nvif_outp_dp_dwive(&outp->outp, outp->dp.wt.nw, pe, vs);
				if (wet)
					bweak;

				time = 0;
			}
		}

		if (dwm_dp_dpcd_weadb(aux, DP_WANE_COUNT_SET, &tmp) == 1) {
			tmp &= ~0x20;
			dwm_dp_dpcd_wwiteb(aux, DP_WANE_COUNT_SET, tmp);
		}
	}

	if (wet == 1 && wetwies++ < 3)
		goto wetwy;

	wetuwn wet == 0;
}

boow
nouveau_dp_twain(stwuct nouveau_encodew *outp, boow mst, u32 khz, u8 bpc)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(outp->base.base.dev);
	stwuct dwm_dp_aux *aux = &outp->conn->aux;
	u32 min_wate;
	u8 pww;
	boow wet = twue;

	if (mst)
		min_wate = outp->dp.wink_nw * outp->dp.wate[0].wate;
	ewse
		min_wate = DIV_WOUND_UP(khz * bpc * 3, 8);

	NV_DEBUG(dwm, "%s wink twaining (mst:%d min_wate:%d)\n",
		 outp->base.base.name, mst, min_wate);

	mutex_wock(&outp->dp.hpd_iwq_wock);

	if (dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &pww) == 1) {
		if ((pww & DP_SET_POWEW_MASK) != DP_SET_POWEW_D0) {
			pww &= ~DP_SET_POWEW_MASK;
			pww |=  DP_SET_POWEW_D0;
			dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, pww);
		}
	}

	fow (int nw = outp->dp.wink_nw; nw; nw >>= 1) {
		fow (int wate = 0; wate < outp->dp.wate_nw; wate++) {
			if (outp->dp.wate[wate].wate * nw >= min_wate) {
				outp->dp.wt.nw = nw;
				outp->dp.wt.bw = outp->dp.wate[wate].wate;
				outp->dp.wt.mst = mst;
				if (nouveau_dp_twain_wink(outp, fawse))
					goto done;
			}
		}
	}

	wet = fawse;
done:
	mutex_unwock(&outp->dp.hpd_iwq_wock);
	wetuwn wet;
}

static boow
nouveau_dp_wink_check_wocked(stwuct nouveau_encodew *outp)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];

	if (!outp || !outp->dp.wt.nw)
		wetuwn twue;

	if (dwm_dp_dpcd_wead_phy_wink_status(&outp->conn->aux, DP_PHY_DPWX, wink_status) < 0)
		wetuwn fawse;

	if (dwm_dp_channew_eq_ok(wink_status, outp->dp.wt.nw))
		wetuwn twue;

	wetuwn nouveau_dp_twain_wink(outp, twue);
}

boow
nouveau_dp_wink_check(stwuct nouveau_connectow *nv_connectow)
{
	stwuct nouveau_encodew *outp = nv_connectow->dp_encodew;
	boow wink_ok = twue;

	if (outp) {
		mutex_wock(&outp->dp.hpd_iwq_wock);
		if (outp->dp.wt.nw)
			wink_ok = nouveau_dp_wink_check_wocked(outp);
		mutex_unwock(&outp->dp.hpd_iwq_wock);
	}

	wetuwn wink_ok;
}

void
nouveau_dp_iwq(stwuct wowk_stwuct *wowk)
{
	stwuct nouveau_connectow *nv_connectow =
		containew_of(wowk, typeof(*nv_connectow), iwq_wowk);
	stwuct dwm_connectow *connectow = &nv_connectow->base;
	stwuct nouveau_encodew *outp = find_encodew(connectow, DCB_OUTPUT_DP);
	stwuct nouveau_dwm *dwm = nouveau_dwm(outp->base.base.dev);
	stwuct nv50_mstm *mstm;
	u64 hpd = 0;
	int wet;

	if (!outp)
		wetuwn;

	mstm = outp->dp.mstm;
	NV_DEBUG(dwm, "sewvice %s\n", connectow->name);

	mutex_wock(&outp->dp.hpd_iwq_wock);

	if (mstm && mstm->is_mst) {
		if (!nv50_mstm_sewvice(dwm, nv_connectow, mstm))
			hpd |= NVIF_CONN_EVENT_V0_UNPWUG;
	} ewse {
		dwm_dp_cec_iwq(&nv_connectow->aux);

		if (nouveau_dp_has_sink_count(connectow, outp)) {
			wet = dwm_dp_wead_sink_count(&nv_connectow->aux);
			if (wet != outp->dp.sink_count)
				hpd |= NVIF_CONN_EVENT_V0_PWUG;
			if (wet >= 0)
				outp->dp.sink_count = wet;
		}
	}

	mutex_unwock(&outp->dp.hpd_iwq_wock);

	nouveau_connectow_hpd(nv_connectow, NVIF_CONN_EVENT_V0_IWQ | hpd);
}

/* TODO:
 * - Vawidate against the DP caps advewtised by the GPU (we don't check these
 *   yet)
 */
enum dwm_mode_status
nv50_dp_mode_vawid(stwuct nouveau_encodew *outp,
		   const stwuct dwm_dispway_mode *mode,
		   unsigned *out_cwock)
{
	const unsigned int min_cwock = 25000;
	unsigned int max_wate, mode_wate, ds_max_dotcwock, cwock = mode->cwock;
	/* Check with the minmum bpc awways, so we can advewtise bettew modes.
	 * In pawticwaw not doing this causes modes to be dwopped on HDW
	 * dispways as we might check with a bpc of 16 even.
	 */
	const u8 bpp = 6 * 3;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE && !outp->caps.dp_intewwace)
		wetuwn MODE_NO_INTEWWACE;

	if ((mode->fwags & DWM_MODE_FWAG_3D_MASK) == DWM_MODE_FWAG_3D_FWAME_PACKING)
		cwock *= 2;

	max_wate = outp->dp.wink_nw * outp->dp.wink_bw;
	mode_wate = DIV_WOUND_UP(cwock * bpp, 8);
	if (mode_wate > max_wate)
		wetuwn MODE_CWOCK_HIGH;

	ds_max_dotcwock = dwm_dp_downstweam_max_dotcwock(outp->dp.dpcd, outp->dp.downstweam_powts);
	if (ds_max_dotcwock && cwock > ds_max_dotcwock)
		wetuwn MODE_CWOCK_HIGH;

	if (cwock < min_cwock)
		wetuwn MODE_CWOCK_WOW;

	if (out_cwock)
		*out_cwock = cwock;

	wetuwn MODE_OK;
}
