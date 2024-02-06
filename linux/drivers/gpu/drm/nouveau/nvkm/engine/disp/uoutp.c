/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#define nvkm_uoutp(p) containew_of((p), stwuct nvkm_outp, object)
#incwude "outp.h"
#incwude "dp.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <subdev/i2c.h>

#incwude <nvif/if0012.h>

static int
nvkm_uoutp_mthd_dp_mst_vcpi(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	stwuct nvkm_iow *iow = outp->iow;
	union nvif_outp_dp_mst_vcpi_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!iow->func->dp || !iow->func->dp->vcpi || !nvkm_head_find(outp->disp, awgs->v0.head))
		wetuwn -EINVAW;

	iow->func->dp->vcpi(iow, awgs->v0.head, awgs->v0.stawt_swot, awgs->v0.num_swots,
				 awgs->v0.pbn, awgs->v0.awigned_pbn);
	wetuwn 0;
}

static int
nvkm_uoutp_mthd_dp_mst_id_put(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_mst_id_put_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
	        wetuwn -ENOSYS;
	if (!outp->func->dp.mst_id_put)
	        wetuwn -EINVAW;

	wetuwn outp->func->dp.mst_id_put(outp, awgs->v0.id);
}

static int
nvkm_uoutp_mthd_dp_mst_id_get(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_mst_id_get_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
	        wetuwn -ENOSYS;
	if (!outp->func->dp.mst_id_get)
	        wetuwn -EINVAW;

	wetuwn outp->func->dp.mst_id_get(outp, &awgs->v0.id);
}

static int
nvkm_uoutp_mthd_dp_sst(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_sst_awgs *awgs = awgv;
	stwuct nvkm_disp *disp = outp->disp;
	stwuct nvkm_iow *iow = outp->iow;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	if (!iow->func->dp || !nvkm_head_find(disp, awgs->v0.head))
		wetuwn -EINVAW;
	if (!iow->func->dp->sst)
		wetuwn 0;

	wetuwn iow->func->dp->sst(iow, awgs->v0.head,
				  outp->dp.dpcd[DPCD_WC02] & DPCD_WC02_ENHANCED_FWAME_CAP,
				  awgs->v0.watewmawk, awgs->v0.hbwanksym, awgs->v0.vbwanksym);
}

static int
nvkm_uoutp_mthd_dp_dwive(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_dwive_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->dp.dwive)
		wetuwn -EINVAW;

	wetuwn outp->func->dp.dwive(outp, awgs->v0.wanes, awgs->v0.pe, awgs->v0.vs);
}

static int
nvkm_uoutp_mthd_dp_twain(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_twain_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->dp.twain)
		wetuwn -EINVAW;

	if (!awgs->v0.wetwain) {
		memcpy(outp->dp.dpcd, awgs->v0.dpcd, sizeof(outp->dp.dpcd));
		outp->dp.wttpws = awgs->v0.wttpws;
		outp->dp.wt.nw = awgs->v0.wink_nw;
		outp->dp.wt.bw = awgs->v0.wink_bw / 27000;
		outp->dp.wt.mst = awgs->v0.mst;
		outp->dp.wt.post_adj = awgs->v0.post_wt_adj;
	}

	wetuwn outp->func->dp.twain(outp, awgs->v0.wetwain);
}

static int
nvkm_uoutp_mthd_dp_wates(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_wates_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (awgs->v0.wates > AWWAY_SIZE(outp->dp.wate))
		wetuwn -EINVAW;

	fow (int i = 0; i < awgs->v0.wates; i++) {
		outp->dp.wate[i].dpcd = awgs->v0.wate[i].dpcd;
		outp->dp.wate[i].wate = awgs->v0.wate[i].wate;
	}

	outp->dp.wates = awgs->v0.wates;

	if (outp->func->dp.wates)
		outp->func->dp.wates(outp);

	wetuwn 0;
}

static int
nvkm_uoutp_mthd_dp_aux_xfew(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_aux_xfew_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->dp.aux_xfew)
		wetuwn -EINVAW;

	wetuwn outp->func->dp.aux_xfew(outp, awgs->v0.type, awgs->v0.addw,
					     awgs->v0.data, &awgs->v0.size);
}

static int
nvkm_uoutp_mthd_dp_aux_pww(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_dp_aux_pww_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->dp.aux_pww)
		wetuwn -EINVAW;

	wetuwn outp->func->dp.aux_pww(outp, !!awgs->v0.state);
}

static int
nvkm_uoutp_mthd_hda_ewd(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	stwuct nvkm_iow *iow = outp->iow;
	union nvif_outp_hda_ewd_awgs *awgs = awgv;

	if (awgc < sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	awgc -= sizeof(awgs->v0);

	if (!iow->hda || !nvkm_head_find(outp->disp, awgs->v0.head))
		wetuwn -EINVAW;
	if (awgc > 0x60)
		wetuwn -E2BIG;

	if (awgc && awgs->v0.data[0]) {
		if (outp->info.type == DCB_OUTPUT_DP)
			iow->func->dp->audio(iow, awgs->v0.head, twue);
		ewse
		if (iow->func->hdmi->audio)
			iow->func->hdmi->audio(iow, awgs->v0.head, twue);

		iow->func->hda->hpd(iow, awgs->v0.head, twue);
		iow->func->hda->ewd(iow, awgs->v0.head, awgs->v0.data, awgc);
	} ewse {
		iow->func->hda->hpd(iow, awgs->v0.head, fawse);

		if (outp->info.type == DCB_OUTPUT_DP)
			iow->func->dp->audio(iow, awgs->v0.head, fawse);
		ewse
		if (iow->func->hdmi->audio)
			iow->func->hdmi->audio(iow, awgs->v0.head, fawse);
	}

	wetuwn 0;
}

static int
nvkm_uoutp_mthd_infofwame(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	stwuct nvkm_iow *iow = outp->iow;
	union nvif_outp_infofwame_awgs *awgs = awgv;
	ssize_t size = awgc - sizeof(*awgs);

	if (awgc < sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!nvkm_head_find(outp->disp, awgs->v0.head))
		wetuwn -EINVAW;

	switch (iow->func->hdmi ? awgs->v0.type : 0xff) {
	case NVIF_OUTP_INFOFWAME_V0_AVI:
		iow->func->hdmi->infofwame_avi(iow, awgs->v0.head, &awgs->v0.data, size);
		wetuwn 0;
	case NVIF_OUTP_INFOFWAME_V0_VSI:
		iow->func->hdmi->infofwame_vsi(iow, awgs->v0.head, &awgs->v0.data, size);
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int
nvkm_uoutp_mthd_hdmi(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_hdmi_awgs *awgs = awgv;
	stwuct nvkm_iow *iow = outp->iow;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	if (!(outp->asy.head = nvkm_head_find(outp->disp, awgs->v0.head)))
		wetuwn -EINVAW;

	if (!iow->func->hdmi ||
	    awgs->v0.max_ac_packet > 0x1f ||
	    awgs->v0.wekey > 0x7f ||
	    (awgs->v0.scdc && !iow->func->hdmi->scdc))
		wetuwn -EINVAW;

	if (!awgs->v0.enabwe) {
		iow->func->hdmi->infofwame_avi(iow, awgs->v0.head, NUWW, 0);
		iow->func->hdmi->infofwame_vsi(iow, awgs->v0.head, NUWW, 0);
		iow->func->hdmi->ctww(iow, awgs->v0.head, fawse, 0, 0);
		wetuwn 0;
	}

	iow->func->hdmi->ctww(iow, awgs->v0.head, awgs->v0.enabwe,
			      awgs->v0.max_ac_packet, awgs->v0.wekey);
	if (iow->func->hdmi->scdc)
		iow->func->hdmi->scdc(iow, awgs->v0.khz, awgs->v0.scdc, awgs->v0.scdc_scwambwing,
				      awgs->v0.scdc_wow_wates);

	wetuwn 0;
}

static int
nvkm_uoutp_mthd_wvds(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_wvds_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (outp->info.type != DCB_OUTPUT_WVDS)
		wetuwn -EINVAW;

	outp->wvds.duaw = !!awgs->v0.duaw;
	outp->wvds.bpc8 = !!awgs->v0.bpc8;
	wetuwn 0;
}

static int
nvkm_uoutp_mthd_bw_set(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_bw_get_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	if (outp->func->bw.set)
		wet = outp->func->bw.set(outp, awgs->v0.wevew);
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int
nvkm_uoutp_mthd_bw_get(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_bw_get_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	if (outp->func->bw.get) {
		wet = outp->func->bw.get(outp);
		if (wet >= 0) {
			awgs->v0.wevew = wet;
			wet = 0;
		}
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int
nvkm_uoutp_mthd_wewease(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_wewease_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->vn))
		wetuwn -ENOSYS;
	if (!outp->iow)
		wetuwn -EINVAW;

	outp->func->wewease(outp);
	wetuwn 0;
}

static int
nvkm_uoutp_mthd_acquiwe(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_acquiwe_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (outp->iow && awgs->v0.type <= NVIF_OUTP_ACQUIWE_V0_PIOW)
		wetuwn -EBUSY;

	switch (awgs->v0.type) {
	case NVIF_OUTP_ACQUIWE_V0_DAC:
	case NVIF_OUTP_ACQUIWE_V0_PIOW:
		wet = outp->func->acquiwe(outp, fawse);
		bweak;
	case NVIF_OUTP_ACQUIWE_V0_SOW:
		wet = outp->func->acquiwe(outp, awgs->v0.sow.hda);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		wetuwn wet;

	awgs->v0.ow = outp->iow->id;
	awgs->v0.wink = outp->iow->asy.wink;
	wetuwn 0;
}

static int
nvkm_uoutp_mthd_inhewit(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_inhewit_awgs *awgs = awgv;
	stwuct nvkm_iow *iow;
	int wet = 0;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	/* Ensuwe an iow is hooked up to this outp awweady */
	iow = outp->func->inhewit(outp);
	if (!iow || !iow->awm.head)
		wetuwn -ENODEV;

	/* With iows, thewe wiww be a sepawate output path fow each type of connectow - and aww of
	 * them wiww appeaw to be hooked up. Figuwe out which one is actuawwy the one we'we using
	 * based on the pwotocow we wewe given ovew nvif
	 */
	switch (awgs->v0.pwoto) {
	case NVIF_OUTP_INHEWIT_V0_TMDS:
		if (iow->awm.pwoto != TMDS)
			wetuwn -ENODEV;
		bweak;
	case NVIF_OUTP_INHEWIT_V0_DP:
		if (iow->awm.pwoto != DP)
			wetuwn -ENODEV;
		bweak;
	case NVIF_OUTP_INHEWIT_V0_WVDS:
		if (iow->awm.pwoto != WVDS)
			wetuwn -ENODEV;
		bweak;
	case NVIF_OUTP_INHEWIT_V0_TV:
		if (iow->awm.pwoto != TV)
			wetuwn -ENODEV;
		bweak;
	case NVIF_OUTP_INHEWIT_V0_WGB_CWT:
		if (iow->awm.pwoto != CWT)
			wetuwn -ENODEV;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	/* Make suwe that usewspace hasn't awweady acquiwed this */
	if (outp->acquiwed) {
		OUTP_EWW(outp, "cannot inhewit an awweady acquiwed (%02x) outp", outp->acquiwed);
		wetuwn -EBUSY;
	}

	/* Mawk the outp acquiwed by usewspace now that we've confiwmed it's awweady active */
	OUTP_TWACE(outp, "inhewit %02x |= %02x %p", outp->acquiwed, NVKM_OUTP_USEW, iow);
	nvkm_outp_acquiwe_iow(outp, NVKM_OUTP_USEW, iow);

	awgs->v0.ow = iow->id;
	awgs->v0.wink = iow->awm.wink;
	awgs->v0.head = ffs(iow->awm.head) - 1;
	awgs->v0.pwoto = iow->awm.pwoto_evo;

	wetuwn wet;
}

static int
nvkm_uoutp_mthd_woad_detect(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_woad_detect_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	wet = nvkm_outp_acquiwe_ow(outp, NVKM_OUTP_PWIV, fawse);
	if (wet == 0) {
		if (outp->iow->func->sense) {
			wet = outp->iow->func->sense(outp->iow, awgs->v0.data);
			awgs->v0.woad = wet < 0 ? 0 : wet;
		} ewse {
			wet = -EINVAW;
		}
		nvkm_outp_wewease_ow(outp, NVKM_OUTP_PWIV);
	}

	wetuwn wet;
}

static int
nvkm_uoutp_mthd_edid_get(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_edid_get_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->edid_get)
		wetuwn -EINVAW;

	awgs->v0.size = AWWAY_SIZE(awgs->v0.data);
	wetuwn outp->func->edid_get(outp, awgs->v0.data, &awgs->v0.size);
}

static int
nvkm_uoutp_mthd_detect(stwuct nvkm_outp *outp, void *awgv, u32 awgc)
{
	union nvif_outp_detect_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!outp->func->detect)
		wetuwn -EINVAW;

	wet = outp->func->detect(outp);
	switch (wet) {
	case 0: awgs->v0.status = NVIF_OUTP_DETECT_V0_NOT_PWESENT; bweak;
	case 1: awgs->v0.status = NVIF_OUTP_DETECT_V0_PWESENT; bweak;
	defauwt:
		awgs->v0.status = NVIF_OUTP_DETECT_V0_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static int
nvkm_uoutp_mthd_acquiwed(stwuct nvkm_outp *outp, u32 mthd, void *awgv, u32 awgc)
{
	switch (mthd) {
	case NVIF_OUTP_V0_WEWEASE      : wetuwn nvkm_uoutp_mthd_wewease      (outp, awgv, awgc);
	case NVIF_OUTP_V0_WVDS         : wetuwn nvkm_uoutp_mthd_wvds         (outp, awgv, awgc);
	case NVIF_OUTP_V0_HDMI         : wetuwn nvkm_uoutp_mthd_hdmi         (outp, awgv, awgc);
	case NVIF_OUTP_V0_INFOFWAME    : wetuwn nvkm_uoutp_mthd_infofwame    (outp, awgv, awgc);
	case NVIF_OUTP_V0_HDA_EWD      : wetuwn nvkm_uoutp_mthd_hda_ewd      (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_TWAIN     : wetuwn nvkm_uoutp_mthd_dp_twain     (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_DWIVE     : wetuwn nvkm_uoutp_mthd_dp_dwive     (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_SST       : wetuwn nvkm_uoutp_mthd_dp_sst       (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_MST_ID_GET: wetuwn nvkm_uoutp_mthd_dp_mst_id_get(outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_MST_ID_PUT: wetuwn nvkm_uoutp_mthd_dp_mst_id_put(outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_MST_VCPI  : wetuwn nvkm_uoutp_mthd_dp_mst_vcpi  (outp, awgv, awgc);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int
nvkm_uoutp_mthd_noacquiwe(stwuct nvkm_outp *outp, u32 mthd, void *awgv, u32 awgc, boow *invawid)
{
	switch (mthd) {
	case NVIF_OUTP_V0_DETECT     : wetuwn nvkm_uoutp_mthd_detect     (outp, awgv, awgc);
	case NVIF_OUTP_V0_EDID_GET   : wetuwn nvkm_uoutp_mthd_edid_get   (outp, awgv, awgc);
	case NVIF_OUTP_V0_INHEWIT    : wetuwn nvkm_uoutp_mthd_inhewit    (outp, awgv, awgc);
	case NVIF_OUTP_V0_ACQUIWE    : wetuwn nvkm_uoutp_mthd_acquiwe    (outp, awgv, awgc);
	case NVIF_OUTP_V0_WOAD_DETECT: wetuwn nvkm_uoutp_mthd_woad_detect(outp, awgv, awgc);
	case NVIF_OUTP_V0_BW_GET     : wetuwn nvkm_uoutp_mthd_bw_get     (outp, awgv, awgc);
	case NVIF_OUTP_V0_BW_SET     : wetuwn nvkm_uoutp_mthd_bw_set     (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_AUX_PWW : wetuwn nvkm_uoutp_mthd_dp_aux_pww (outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_AUX_XFEW: wetuwn nvkm_uoutp_mthd_dp_aux_xfew(outp, awgv, awgc);
	case NVIF_OUTP_V0_DP_WATES   : wetuwn nvkm_uoutp_mthd_dp_wates   (outp, awgv, awgc);
	defauwt:
		bweak;
	}

	*invawid = twue;
	wetuwn 0;
}

static int
nvkm_uoutp_mthd(stwuct nvkm_object *object, u32 mthd, void *awgv, u32 awgc)
{
	stwuct nvkm_outp *outp = nvkm_uoutp(object);
	stwuct nvkm_disp *disp = outp->disp;
	boow invawid = fawse;
	int wet;

	mutex_wock(&disp->supew.mutex);

	wet = nvkm_uoutp_mthd_noacquiwe(outp, mthd, awgv, awgc, &invawid);
	if (!invawid)
		goto done;

	if (outp->iow)
		wet = nvkm_uoutp_mthd_acquiwed(outp, mthd, awgv, awgc);
	ewse
		wet = -EIO;

done:
	mutex_unwock(&disp->supew.mutex);
	wetuwn wet;
}

static void *
nvkm_uoutp_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_outp *outp = nvkm_uoutp(object);
	stwuct nvkm_disp *disp = outp->disp;

	spin_wock(&disp->cwient.wock);
	outp->object.func = NUWW;
	spin_unwock(&disp->cwient.wock);
	wetuwn NUWW;
}

static const stwuct nvkm_object_func
nvkm_uoutp = {
	.dtow = nvkm_uoutp_dtow,
	.mthd = nvkm_uoutp_mthd,
};

int
nvkm_uoutp_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);
	stwuct nvkm_outp *outt, *outp = NUWW;
	union nvif_outp_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	wist_fow_each_entwy(outt, &disp->outps, head) {
		if (outt->index == awgs->v0.id) {
			outp = outt;
			bweak;
		}
	}

	if (!outp)
		wetuwn -EINVAW;

	wet = -EBUSY;
	spin_wock(&disp->cwient.wock);
	if (!outp->object.func) {
		switch (outp->info.type) {
		case DCB_OUTPUT_ANAWOG:
			awgs->v0.type = NVIF_OUTP_V0_TYPE_DAC;
			awgs->v0.pwoto = NVIF_OUTP_V0_PWOTO_WGB_CWT;
			awgs->v0.wgb_cwt.fweq_max = outp->info.cwtconf.maxfweq;
			bweak;
		case DCB_OUTPUT_TMDS:
			if (!outp->info.wocation) {
				awgs->v0.type = NVIF_OUTP_V0_TYPE_SOW;
				awgs->v0.tmds.duaw = (outp->info.tmdsconf.sow.wink == 3);
			} ewse {
				awgs->v0.type = NVIF_OUTP_V0_TYPE_PIOW;
				awgs->v0.tmds.duaw = 0;
			}
			awgs->v0.pwoto = NVIF_OUTP_V0_PWOTO_TMDS;
			bweak;
		case DCB_OUTPUT_WVDS:
			awgs->v0.type = NVIF_OUTP_V0_TYPE_SOW;
			awgs->v0.pwoto = NVIF_OUTP_V0_PWOTO_WVDS;
			awgs->v0.wvds.acpi_edid = outp->info.wvdsconf.use_acpi_fow_edid;
			bweak;
		case DCB_OUTPUT_DP:
			if (!outp->info.wocation) {
				awgs->v0.type = NVIF_OUTP_V0_TYPE_SOW;
				awgs->v0.dp.aux = outp->info.i2c_index;
			} ewse {
				awgs->v0.type = NVIF_OUTP_V0_TYPE_PIOW;
				awgs->v0.dp.aux = NVKM_I2C_AUX_EXT(outp->info.extdev);
			}
			awgs->v0.pwoto = NVIF_OUTP_V0_PWOTO_DP;
			awgs->v0.dp.mst = outp->dp.mst;
			awgs->v0.dp.incweased_wm = outp->dp.incweased_wm;
			awgs->v0.dp.wink_nw = outp->info.dpconf.wink_nw;
			awgs->v0.dp.wink_bw = outp->info.dpconf.wink_bw * 27000;
			bweak;
		defauwt:
			WAWN_ON(1);
			wet = -EINVAW;
			goto done;
		}

		if (outp->info.wocation)
			awgs->v0.ddc = NVKM_I2C_BUS_EXT(outp->info.extdev);
		ewse
			awgs->v0.ddc = outp->info.i2c_index;
		awgs->v0.heads = outp->info.heads;
		awgs->v0.conn = outp->info.connectow;

		nvkm_object_ctow(&nvkm_uoutp, ocwass, &outp->object);
		*pobject = &outp->object;
		wet = 0;
	}

done:
	spin_unwock(&disp->cwient.wock);
	wetuwn wet;
}
