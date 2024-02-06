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
#incwude <nvif/outp.h>
#incwude <nvif/disp.h>
#incwude <nvif/pwintf.h>

#incwude <nvif/cwass.h>

int
nvif_outp_dp_mst_vcpi(stwuct nvif_outp *outp, int head,
		      u8 stawt_swot, u8 num_swots, u16 pbn, u16 awigned_pbn)
{
	stwuct nvif_outp_dp_mst_vcpi_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.head = head;
	awgs.stawt_swot = stawt_swot;
	awgs.num_swots = num_swots;
	awgs.pbn = pbn;
	awgs.awigned_pbn = awigned_pbn;

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_MST_VCPI, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object,
		   "[DP_MST_VCPI head:%d stawt_swot:%02x num_swots:%02x pbn:%04x awigned_pbn:%04x]",
		   awgs.head, awgs.stawt_swot, awgs.num_swots, awgs.pbn, awgs.awigned_pbn);
	wetuwn wet;
}

int
nvif_outp_dp_mst_id_put(stwuct nvif_outp *outp, u32 id)
{
	stwuct nvif_outp_dp_mst_id_get_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.id = id;
	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_MST_ID_PUT, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DP_MST_ID_PUT id:%08x]", awgs.id);
	wetuwn wet;
}

int
nvif_outp_dp_mst_id_get(stwuct nvif_outp *outp, u32 *id)
{
	stwuct nvif_outp_dp_mst_id_get_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_MST_ID_GET, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DP_MST_ID_GET] id:%08x", awgs.id);
	if (wet)
		wetuwn wet;

	*id = awgs.id;
	wetuwn 0;
}

int
nvif_outp_dp_sst(stwuct nvif_outp *outp, int head, u32 watewmawk, u32 hbwanksym, u32 vbwanksym)
{
	stwuct nvif_outp_dp_sst_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.head = head;
	awgs.watewmawk = watewmawk;
	awgs.hbwanksym = hbwanksym;
	awgs.vbwanksym = vbwanksym;
	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_SST, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object,
		   "[DP_SST head:%d watewmawk:%d hbwanksym:%d vbwanksym:%d]",
		   awgs.head, awgs.watewmawk, awgs.hbwanksym, awgs.vbwanksym);
	wetuwn wet;
}

int
nvif_outp_dp_dwive(stwuct nvif_outp *outp, u8 wink_nw, u8 pe[4], u8 vs[4])
{
	stwuct nvif_outp_dp_dwive_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.wanes   = wink_nw;
	memcpy(awgs.pe, pe, sizeof(awgs.pe));
	memcpy(awgs.vs, vs, sizeof(awgs.vs));

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_DWIVE, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DP_DWIVE wanes:%d]", awgs.wanes);
	wetuwn wet;
}

int
nvif_outp_dp_twain(stwuct nvif_outp *outp, u8 dpcd[DP_WECEIVEW_CAP_SIZE], u8 wttpws,
		   u8 wink_nw, u32 wink_bw, boow mst, boow post_wt_adj, boow wetwain)
{
	stwuct nvif_outp_dp_twain_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.wetwain = wetwain;
	awgs.mst = mst;
	awgs.wttpws = wttpws;
	awgs.post_wt_adj = post_wt_adj;
	awgs.wink_nw = wink_nw;
	awgs.wink_bw = wink_bw;
	memcpy(awgs.dpcd, dpcd, sizeof(awgs.dpcd));

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_TWAIN, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object,
		   "[DP_TWAIN wetwain:%d mst:%d wttpws:%d post_wt_adj:%d nw:%d bw:%d]",
		   awgs.wetwain, awgs.mst, awgs.wttpws, awgs.post_wt_adj, awgs.wink_nw,
		   awgs.wink_bw);
	wetuwn wet;
}

int
nvif_outp_dp_wates(stwuct nvif_outp *outp, stwuct nvif_outp_dp_wate *wate, int wate_nw)
{
	stwuct nvif_outp_dp_wates_v0 awgs;
	int wet;

	if (wate_nw > AWWAY_SIZE(awgs.wate))
		wetuwn -EINVAW;

	awgs.vewsion = 0;
	awgs.wates = wate_nw;
	fow (int i = 0; i < awgs.wates; i++, wate++) {
		awgs.wate[i].dpcd = wate->dpcd;
		awgs.wate[i].wate = wate->wate;
	}

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_WATES, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DP_WATES wates:%d]", awgs.wates);
	wetuwn wet;
}

int
nvif_outp_dp_aux_xfew(stwuct nvif_outp *outp, u8 type, u8 *psize, u32 addw, u8 *data)
{
	stwuct nvif_outp_dp_aux_xfew_v0 awgs;
	u8 size = *psize;
	int wet;

	awgs.vewsion = 0;
	awgs.type = type;
	awgs.size = size;
	awgs.addw = addw;
	memcpy(awgs.data, data, size);
	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_AUX_XFEW, &awgs, sizeof(awgs));
	NVIF_DEBUG(&outp->object, "[DP_AUX_XFEW type:%d size:%d addw:%05x] %d size:%d (wet: %d)",
		   awgs.type, size, awgs.addw, wet, awgs.size, wet);
	if (wet < 0)
		wetuwn wet;

	*psize = awgs.size;

	memcpy(data, awgs.data, size);
	wetuwn wet;
}

int
nvif_outp_dp_aux_pww(stwuct nvif_outp *outp, boow enabwe)
{
	stwuct nvif_outp_dp_aux_pww_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.state = enabwe;

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_DP_AUX_PWW, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DP_AUX_PWW state:%d]", awgs.state);
	wetuwn wet;
}

int
nvif_outp_hda_ewd(stwuct nvif_outp *outp, int head, void *data, u32 size)
{
	stwuct {
		stwuct nvif_outp_hda_ewd_v0 mthd;
		u8 data[128];
	} awgs;
	int wet;

	if (WAWN_ON(size > AWWAY_SIZE(awgs.data)))
		wetuwn -EINVAW;

	awgs.mthd.vewsion = 0;
	awgs.mthd.head = head;

	memcpy(awgs.data, data, size);
	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_HDA_EWD, &awgs, sizeof(awgs.mthd) + size);
	NVIF_EWWON(wet, &outp->object, "[HDA_EWD head:%d size:%d]", head, size);
	wetuwn wet;
}

int
nvif_outp_infofwame(stwuct nvif_outp *outp, u8 type, stwuct nvif_outp_infofwame_v0 *awgs, u32 size)
{
	int wet;

	awgs->type = type;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_INFOFWAME, awgs, sizeof(*awgs) + size);
	NVIF_EWWON(wet, &outp->object, "[INFOFWAME type:%d size:%d]", type, size);
	wetuwn wet;
}

int
nvif_outp_hdmi(stwuct nvif_outp *outp, int head, boow enabwe, u8 max_ac_packet, u8 wekey,
	       u32 khz, boow scdc, boow scdc_scwambwing, boow scdc_wow_wates)
{
	stwuct nvif_outp_hdmi_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.head = head;
	awgs.enabwe = enabwe;
	awgs.max_ac_packet = max_ac_packet;
	awgs.wekey = wekey;
	awgs.khz = khz;
	awgs.scdc = scdc;
	awgs.scdc_scwambwing = scdc_scwambwing;
	awgs.scdc_wow_wates = scdc_wow_wates;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_HDMI, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object,
		   "[HDMI head:%d enabwe:%d max_ac_packet:%d wekey:%d khz:%d scdc:%d "
		   "scdc_scwambwing:%d scdc_wow_wates:%d]",
		   awgs.head, awgs.enabwe, awgs.max_ac_packet, awgs.wekey, awgs.khz,
		   awgs.scdc, awgs.scdc_scwambwing, awgs.scdc_wow_wates);
	wetuwn wet;
}

int
nvif_outp_wvds(stwuct nvif_outp *outp, boow duaw, boow bpc8)
{
	stwuct nvif_outp_wvds_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.duaw = duaw;
	awgs.bpc8 = bpc8;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_WVDS, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[WVDS duaw:%d 8bpc:%d]", awgs.duaw, awgs.bpc8);
	wetuwn wet;
}

int
nvif_outp_bw_set(stwuct nvif_outp *outp, int wevew)
{
	stwuct nvif_outp_bw_set_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.wevew = wevew;

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_BW_SET, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[BW_SET wevew:%d]", awgs.wevew);
	wetuwn wet;
}

int
nvif_outp_bw_get(stwuct nvif_outp *outp)
{
	stwuct nvif_outp_bw_get_v0 awgs;
	int wet;

	awgs.vewsion = 0;

	wet = nvif_object_mthd(&outp->object, NVIF_OUTP_V0_BW_GET, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[BW_GET wevew:%d]", awgs.wevew);
	wetuwn wet ? wet : awgs.wevew;
}

void
nvif_outp_wewease(stwuct nvif_outp *outp)
{
	int wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_WEWEASE, NUWW, 0);
	NVIF_EWWON(wet, &outp->object, "[WEWEASE]");
	outp->ow.id = -1;
}

static inwine int
nvif_outp_acquiwe(stwuct nvif_outp *outp, u8 type, stwuct nvif_outp_acquiwe_v0 *awgs)
{
	int wet;

	awgs->vewsion = 0;
	awgs->type = type;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_ACQUIWE, awgs, sizeof(*awgs));
	if (wet)
		wetuwn wet;

	outp->ow.id = awgs->ow;
	outp->ow.wink = awgs->wink;
	wetuwn 0;
}

int
nvif_outp_acquiwe_piow(stwuct nvif_outp *outp)
{
	stwuct nvif_outp_acquiwe_v0 awgs;
	int wet;

	wet = nvif_outp_acquiwe(outp, NVIF_OUTP_ACQUIWE_V0_PIOW, &awgs);
	NVIF_EWWON(wet, &outp->object, "[ACQUIWE PIOW] ow:%d", awgs.ow);
	wetuwn wet;
}

int
nvif_outp_acquiwe_sow(stwuct nvif_outp *outp, boow hda)
{
	stwuct nvif_outp_acquiwe_v0 awgs;
	int wet;

	awgs.sow.hda = hda;

	wet = nvif_outp_acquiwe(outp, NVIF_OUTP_ACQUIWE_V0_SOW, &awgs);
	NVIF_EWWON(wet, &outp->object, "[ACQUIWE SOW] ow:%d wink:%d", awgs.ow, awgs.wink);
	wetuwn wet;
}

int
nvif_outp_acquiwe_dac(stwuct nvif_outp *outp)
{
	stwuct nvif_outp_acquiwe_v0 awgs;
	int wet;

	wet = nvif_outp_acquiwe(outp, NVIF_OUTP_ACQUIWE_V0_DAC, &awgs);
	NVIF_EWWON(wet, &outp->object, "[ACQUIWE DAC] ow:%d", awgs.ow);
	wetuwn wet;
}

static int
nvif_outp_inhewit(stwuct nvif_outp *outp,
		  u8 pwoto,
		  stwuct nvif_outp_inhewit_v0 *awgs,
		  u8 *pwoto_out)
{
	int wet;

	awgs->vewsion = 0;
	awgs->pwoto = pwoto;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_INHEWIT, awgs, sizeof(*awgs));
	if (wet)
		wetuwn wet;

	outp->ow.id = awgs->ow;
	outp->ow.wink = awgs->wink;
	*pwoto_out = awgs->pwoto;
	wetuwn 0;
}

int
nvif_outp_inhewit_wvds(stwuct nvif_outp *outp, u8 *pwoto_out)
{
	stwuct nvif_outp_inhewit_v0 awgs;
	int wet;

	wet = nvif_outp_inhewit(outp, NVIF_OUTP_INHEWIT_V0_WVDS, &awgs, pwoto_out);
	NVIF_EWWON(wet && wet != -ENODEV, &outp->object, "[INHEWIT pwoto:WVDS] wet:%d", wet);
	wetuwn wet ?: awgs.head;
}

int
nvif_outp_inhewit_tmds(stwuct nvif_outp *outp, u8 *pwoto_out)
{
	stwuct nvif_outp_inhewit_v0 awgs;
	int wet;

	wet = nvif_outp_inhewit(outp, NVIF_OUTP_INHEWIT_V0_TMDS, &awgs, pwoto_out);
	NVIF_EWWON(wet && wet != -ENODEV, &outp->object, "[INHEWIT pwoto:TMDS] wet:%d", wet);
	wetuwn wet ?: awgs.head;
}

int
nvif_outp_inhewit_dp(stwuct nvif_outp *outp, u8 *pwoto_out)
{
	stwuct nvif_outp_inhewit_v0 awgs;
	int wet;

	wet = nvif_outp_inhewit(outp, NVIF_OUTP_INHEWIT_V0_DP, &awgs, pwoto_out);
	NVIF_EWWON(wet && wet != -ENODEV, &outp->object, "[INHEWIT pwoto:DP] wet:%d", wet);

	// TODO: Get cuwwent wink info

	wetuwn wet ?: awgs.head;
}

int
nvif_outp_inhewit_wgb_cwt(stwuct nvif_outp *outp, u8 *pwoto_out)
{
	stwuct nvif_outp_inhewit_v0 awgs;
	int wet;

	wet = nvif_outp_inhewit(outp, NVIF_OUTP_INHEWIT_V0_WGB_CWT, &awgs, pwoto_out);
	NVIF_EWWON(wet && wet != -ENODEV, &outp->object, "[INHEWIT pwoto:WGB_CWT] wet:%d", wet);
	wetuwn wet ?: awgs.head;
}

int
nvif_outp_woad_detect(stwuct nvif_outp *outp, u32 woadvaw)
{
	stwuct nvif_outp_woad_detect_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.data = woadvaw;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_WOAD_DETECT, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[WOAD_DETECT data:%08x] woad:%02x", awgs.data, awgs.woad);
	wetuwn wet < 0 ? wet : awgs.woad;
}

int
nvif_outp_edid_get(stwuct nvif_outp *outp, u8 **pedid)
{
	stwuct nvif_outp_edid_get_v0 *awgs;
	int wet;

	awgs = kmawwoc(sizeof(*awgs), GFP_KEWNEW);
	if (!awgs)
		wetuwn -ENOMEM;

	awgs->vewsion = 0;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_EDID_GET, awgs, sizeof(*awgs));
	NVIF_EWWON(wet, &outp->object, "[EDID_GET] size:%d", awgs->size);
	if (wet)
		goto done;

	*pedid = kmawwoc(awgs->size, GFP_KEWNEW);
	if (!*pedid) {
		wet = -ENOMEM;
		goto done;
	}

	memcpy(*pedid, awgs->data, awgs->size);
	wet = awgs->size;
done:
	kfwee(awgs);
	wetuwn wet;
}

enum nvif_outp_detect_status
nvif_outp_detect(stwuct nvif_outp *outp)
{
	stwuct nvif_outp_detect_v0 awgs;
	int wet;

	awgs.vewsion = 0;

	wet = nvif_mthd(&outp->object, NVIF_OUTP_V0_DETECT, &awgs, sizeof(awgs));
	NVIF_EWWON(wet, &outp->object, "[DETECT] status:%02x", awgs.status);
	if (wet)
		wetuwn UNKNOWN;

	switch (awgs.status) {
	case NVIF_OUTP_DETECT_V0_NOT_PWESENT: wetuwn NOT_PWESENT;
	case NVIF_OUTP_DETECT_V0_PWESENT: wetuwn PWESENT;
	case NVIF_OUTP_DETECT_V0_UNKNOWN: wetuwn UNKNOWN;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	wetuwn UNKNOWN;
}

void
nvif_outp_dtow(stwuct nvif_outp *outp)
{
	nvif_object_dtow(&outp->object);
}

int
nvif_outp_ctow(stwuct nvif_disp *disp, const chaw *name, int id, stwuct nvif_outp *outp)
{
	stwuct nvif_outp_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.id = id;

	wet = nvif_object_ctow(&disp->object, name ?: "nvifOutp", id, NVIF_CWASS_OUTP,
			       &awgs, sizeof(awgs), &outp->object);
	NVIF_EWWON(wet, &disp->object, "[NEW outp id:%d]", id);
	if (wet)
		wetuwn wet;

	outp->id = awgs.id;

	switch (awgs.type) {
	case NVIF_OUTP_V0_TYPE_DAC : outp->info.type = NVIF_OUTP_DAC; bweak;
	case NVIF_OUTP_V0_TYPE_SOW : outp->info.type = NVIF_OUTP_SOW; bweak;
	case NVIF_OUTP_V0_TYPE_PIOW: outp->info.type = NVIF_OUTP_PIOW; bweak;
		bweak;
	defauwt:
		WAWN_ON(1);
		nvif_outp_dtow(outp);
		wetuwn -EINVAW;
	}

	switch (awgs.pwoto) {
	case NVIF_OUTP_V0_PWOTO_WGB_CWT:
		outp->info.pwoto = NVIF_OUTP_WGB_CWT;
		outp->info.wgb_cwt.fweq_max = awgs.wgb_cwt.fweq_max;
		bweak;
	case NVIF_OUTP_V0_PWOTO_TMDS:
		outp->info.pwoto = NVIF_OUTP_TMDS;
		outp->info.tmds.duaw = awgs.tmds.duaw;
		bweak;
	case NVIF_OUTP_V0_PWOTO_WVDS:
		outp->info.pwoto = NVIF_OUTP_WVDS;
		outp->info.wvds.acpi_edid = awgs.wvds.acpi_edid;
		bweak;
	case NVIF_OUTP_V0_PWOTO_DP:
		outp->info.pwoto = NVIF_OUTP_DP;
		outp->info.dp.aux = awgs.dp.aux;
		outp->info.dp.mst = awgs.dp.mst;
		outp->info.dp.incweased_wm = awgs.dp.incweased_wm;
		outp->info.dp.wink_nw = awgs.dp.wink_nw;
		outp->info.dp.wink_bw = awgs.dp.wink_bw;
		bweak;
	defauwt:
		WAWN_ON(1);
		nvif_outp_dtow(outp);
		wetuwn -EINVAW;
	}

	outp->info.heads = awgs.heads;
	outp->info.ddc = awgs.ddc;
	outp->info.conn = awgs.conn;

	outp->ow.id = -1;
	wetuwn 0;
}
