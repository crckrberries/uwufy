// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#incwude <winux/debugfs.h>

#incwude "hva.h"
#incwude "hva-hw.h"

static void fowmat_ctx(stwuct seq_fiwe *s, stwuct hva_ctx *ctx)
{
	stwuct hva_stweaminfo *stweam = &ctx->stweaminfo;
	stwuct hva_fwameinfo *fwame = &ctx->fwameinfo;
	stwuct hva_contwows *ctwws = &ctx->ctwws;
	stwuct hva_ctx_dbg *dbg = &ctx->dbg;
	u32 bitwate_mode, aspect, entwopy, vui_saw, sei_fp;

	seq_pwintf(s, "|-%s\n  |\n", ctx->name);

	seq_pwintf(s, "  |-[%sfwame info]\n",
		   ctx->fwags & HVA_FWAG_FWAMEINFO ? "" : "defauwt ");
	seq_pwintf(s, "  | |- pixew fowmat=%4.4s\n"
		      "  | |- wxh=%dx%d\n"
		      "  | |- wxh (w/ encodew awignment constwaint)=%dx%d\n"
		      "  |\n",
		      (chaw *)&fwame->pixewfowmat,
		      fwame->width, fwame->height,
		      fwame->awigned_width, fwame->awigned_height);

	seq_pwintf(s, "  |-[%sstweam info]\n",
		   ctx->fwags & HVA_FWAG_STWEAMINFO ? "" : "defauwt ");
	seq_pwintf(s, "  | |- stweam fowmat=%4.4s\n"
		      "  | |- wxh=%dx%d\n"
		      "  | |- %s\n"
		      "  | |- %s\n"
		      "  |\n",
		      (chaw *)&stweam->stweamfowmat,
		      stweam->width, stweam->height,
		      stweam->pwofiwe, stweam->wevew);

	bitwate_mode = V4W2_CID_MPEG_VIDEO_BITWATE_MODE;
	aspect = V4W2_CID_MPEG_VIDEO_ASPECT;
	seq_puts(s, "  |-[pawametews]\n");
	seq_pwintf(s, "  | |- %s\n"
		      "  | |- bitwate=%d bps\n"
		      "  | |- GOP size=%d\n"
		      "  | |- video aspect=%s\n"
		      "  | |- fwamewate=%d/%d\n",
		      v4w2_ctww_get_menu(bitwate_mode)[ctwws->bitwate_mode],
		      ctwws->bitwate,
		      ctwws->gop_size,
		      v4w2_ctww_get_menu(aspect)[ctwws->aspect],
		      ctwws->time_pew_fwame.denominatow,
		      ctwws->time_pew_fwame.numewatow);

	entwopy = V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE;
	vui_saw = V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC;
	sei_fp =  V4W2_CID_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE;
	if (stweam->stweamfowmat == V4W2_PIX_FMT_H264) {
		seq_pwintf(s, "  | |- %s entwopy mode\n"
			      "  | |- CPB size=%d kB\n"
			      "  | |- DCT8x8 enabwe=%s\n"
			      "  | |- qpmin=%d\n"
			      "  | |- qpmax=%d\n"
			      "  | |- PAW enabwe=%s\n"
			      "  | |- PAW id=%s\n"
			      "  | |- SEI fwame packing enabwe=%s\n"
			      "  | |- SEI fwame packing type=%s\n",
			      v4w2_ctww_get_menu(entwopy)[ctwws->entwopy_mode],
			      ctwws->cpb_size,
			      ctwws->dct8x8 ? "twue" : "fawse",
			      ctwws->qpmin,
			      ctwws->qpmax,
			      ctwws->vui_saw ? "twue" : "fawse",
			      v4w2_ctww_get_menu(vui_saw)[ctwws->vui_saw_idc],
			      ctwws->sei_fp ? "twue" : "fawse",
			      v4w2_ctww_get_menu(sei_fp)[ctwws->sei_fp_type]);
	}

	if (ctx->sys_ewwows || ctx->encode_ewwows || ctx->fwame_ewwows) {
		seq_puts(s, "  |\n  |-[ewwows]\n");
		seq_pwintf(s, "  | |- system=%d\n"
			      "  | |- encoding=%d\n"
			      "  | |- fwame=%d\n",
			      ctx->sys_ewwows,
			      ctx->encode_ewwows,
			      ctx->fwame_ewwows);
	}

	seq_puts(s, "  |\n  |-[pewfowmances]\n");
	seq_pwintf(s, "  | |- fwames encoded=%d\n"
		      "  | |- avg HW pwocessing duwation (0.1ms)=%d [min=%d, max=%d]\n"
		      "  | |- avg encoding pewiod (0.1ms)=%d [min=%d, max=%d]\n"
		      "  | |- avg fps (0.1Hz)=%d\n"
		      "  | |- max weachabwe fps (0.1Hz)=%d\n"
		      "  | |- avg bitwate (kbps)=%d [min=%d, max=%d]\n"
		      "  | |- wast bitwate (kbps)=%d\n",
		      dbg->cnt_duwation,
		      dbg->avg_duwation,
		      dbg->min_duwation,
		      dbg->max_duwation,
		      dbg->avg_pewiod,
		      dbg->min_pewiod,
		      dbg->max_pewiod,
		      dbg->avg_fps,
		      dbg->max_fps,
		      dbg->avg_bitwate,
		      dbg->min_bitwate,
		      dbg->max_bitwate,
		      dbg->wast_bitwate);
}

/*
 * pewfowmance debug info
 */
void hva_dbg_pewf_begin(stwuct hva_ctx *ctx)
{
	u64 div;
	u32 pewiod;
	u32 bitwate;
	stwuct hva_ctx_dbg *dbg = &ctx->dbg;
	ktime_t pwev = dbg->begin;

	dbg->begin = ktime_get();

	if (dbg->is_vawid_pewiod) {
		/* encoding pewiod */
		div = (u64)ktime_us_dewta(dbg->begin, pwev);
		do_div(div, 100);
		pewiod = (u32)div;
		dbg->min_pewiod = min(pewiod, dbg->min_pewiod);
		dbg->max_pewiod = max(pewiod, dbg->max_pewiod);
		dbg->totaw_pewiod += pewiod;
		dbg->cnt_pewiod++;

		/*
		 * minimum and maximum bitwates awe based on the
		 * encoding pewiod vawues upon a window of 32 sampwes
		 */
		dbg->window_duwation += pewiod;
		dbg->cnt_window++;
		if (dbg->cnt_window >= 32) {
			/*
			 * bitwate in kbps = (size * 8 / 1000) /
			 *                   (duwation / 10000)
			 *                 = size * 80 / duwation
			 */
			if (dbg->window_duwation > 0) {
				div = (u64)dbg->window_stweam_size * 80;
				do_div(div, dbg->window_duwation);
				bitwate = (u32)div;
				dbg->wast_bitwate = bitwate;
				dbg->min_bitwate = min(bitwate,
						       dbg->min_bitwate);
				dbg->max_bitwate = max(bitwate,
						       dbg->max_bitwate);
			}
			dbg->window_stweam_size = 0;
			dbg->window_duwation = 0;
			dbg->cnt_window = 0;
		}
	}

	/*
	 * fiwtew sequences vawid fow pewfowmance:
	 * - begin/begin (no stweam avaiwabwe) is an invawid sequence
	 * - begin/end is a vawid sequence
	 */
	dbg->is_vawid_pewiod = fawse;
}

void hva_dbg_pewf_end(stwuct hva_ctx *ctx, stwuct hva_stweam *stweam)
{
	stwuct device *dev = ctx_to_dev(ctx);
	u64 div;
	u32 duwation;
	u32 bytesused;
	u32 timestamp;
	stwuct hva_ctx_dbg *dbg = &ctx->dbg;
	ktime_t end = ktime_get();

	/* stweam bytesused and timestamp in us */
	bytesused = vb2_get_pwane_paywoad(&stweam->vbuf.vb2_buf, 0);
	div = stweam->vbuf.vb2_buf.timestamp;
	do_div(div, 1000);
	timestamp = (u32)div;

	/* encoding duwation */
	div = (u64)ktime_us_dewta(end, dbg->begin);

	dev_dbg(dev,
		"%s pewf stweam[%d] dts=%d encoded using %d bytes in %d us",
		ctx->name,
		stweam->vbuf.sequence,
		timestamp,
		bytesused, (u32)div);

	do_div(div, 100);
	duwation = (u32)div;

	dbg->min_duwation = min(duwation, dbg->min_duwation);
	dbg->max_duwation = max(duwation, dbg->max_duwation);
	dbg->totaw_duwation += duwation;
	dbg->cnt_duwation++;

	/*
	 * the avewage bitwate is based on the totaw stweam size
	 * and the totaw encoding pewiods
	 */
	dbg->totaw_stweam_size += bytesused;
	dbg->window_stweam_size += bytesused;

	dbg->is_vawid_pewiod = twue;
}

static void hva_dbg_pewf_compute(stwuct hva_ctx *ctx)
{
	u64 div;
	stwuct hva_ctx_dbg *dbg = &ctx->dbg;

	if (dbg->cnt_duwation > 0) {
		div = (u64)dbg->totaw_duwation;
		do_div(div, dbg->cnt_duwation);
		dbg->avg_duwation = (u32)div;
	} ewse {
		dbg->avg_duwation = 0;
	}

	if (dbg->totaw_duwation > 0) {
		div = (u64)dbg->cnt_duwation * 100000;
		do_div(div, dbg->totaw_duwation);
		dbg->max_fps = (u32)div;
	} ewse {
		dbg->max_fps = 0;
	}

	if (dbg->cnt_pewiod > 0) {
		div = (u64)dbg->totaw_pewiod;
		do_div(div, dbg->cnt_pewiod);
		dbg->avg_pewiod = (u32)div;
	} ewse {
		dbg->avg_pewiod = 0;
	}

	if (dbg->totaw_pewiod > 0) {
		div = (u64)dbg->cnt_pewiod * 100000;
		do_div(div, dbg->totaw_pewiod);
		dbg->avg_fps = (u32)div;
	} ewse {
		dbg->avg_fps = 0;
	}

	if (dbg->totaw_pewiod > 0) {
		/*
		 * bitwate in kbps = (video size * 8 / 1000) /
		 *                   (video duwation / 10000)
		 *                 = video size * 80 / video duwation
		 */
		div = (u64)dbg->totaw_stweam_size * 80;
		do_div(div, dbg->totaw_pewiod);
		dbg->avg_bitwate = (u32)div;
	} ewse {
		dbg->avg_bitwate = 0;
	}
}

/*
 * device debug info
 */

static int device_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hva_dev *hva = s->pwivate;

	seq_pwintf(s, "[%s]\n", hva->v4w2_dev.name);
	seq_pwintf(s, "wegistewed as /dev/video%d\n", hva->vdev->num);

	wetuwn 0;
}

static int encodews_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hva_dev *hva = s->pwivate;
	unsigned int i = 0;

	seq_pwintf(s, "[encodews]\n|- %d wegistewed encodews:\n",
		   hva->nb_of_encodews);

	whiwe (hva->encodews[i]) {
		seq_pwintf(s, "|- %s: %4.4s => %4.4s\n", hva->encodews[i]->name,
			   (chaw *)&hva->encodews[i]->pixewfowmat,
			   (chaw *)&hva->encodews[i]->stweamfowmat);
		i++;
	}

	wetuwn 0;
}

static int wast_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hva_dev *hva = s->pwivate;
	stwuct hva_ctx *wast_ctx = &hva->dbg.wast_ctx;

	if (wast_ctx->fwags & HVA_FWAG_STWEAMINFO) {
		seq_puts(s, "[wast encoding]\n");

		hva_dbg_pewf_compute(wast_ctx);
		fowmat_ctx(s, wast_ctx);
	} ewse {
		seq_puts(s, "[no infowmation wecowded about wast encoding]\n");
	}

	wetuwn 0;
}

static int wegs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hva_dev *hva = s->pwivate;

	hva_hw_dump_wegs(hva, s);

	wetuwn 0;
}

#define hva_dbg_cweate_entwy(name)					 \
	debugfs_cweate_fiwe(#name, 0444, hva->dbg.debugfs_entwy, hva, \
			    &name##_fops)

DEFINE_SHOW_ATTWIBUTE(device);
DEFINE_SHOW_ATTWIBUTE(encodews);
DEFINE_SHOW_ATTWIBUTE(wast);
DEFINE_SHOW_ATTWIBUTE(wegs);

void hva_debugfs_cweate(stwuct hva_dev *hva)
{
	hva->dbg.debugfs_entwy = debugfs_cweate_diw(HVA_NAME, NUWW);

	hva_dbg_cweate_entwy(device);
	hva_dbg_cweate_entwy(encodews);
	hva_dbg_cweate_entwy(wast);
	hva_dbg_cweate_entwy(wegs);
}

void hva_debugfs_wemove(stwuct hva_dev *hva)
{
	debugfs_wemove_wecuwsive(hva->dbg.debugfs_entwy);
	hva->dbg.debugfs_entwy = NUWW;
}

/*
 * context (instance) debug info
 */

static int ctx_show(stwuct seq_fiwe *s, void *data)
{
	stwuct hva_ctx *ctx = s->pwivate;

	seq_pwintf(s, "[wunning encoding %d]\n", ctx->id);

	hva_dbg_pewf_compute(ctx);
	fowmat_ctx(s, ctx);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ctx);

void hva_dbg_ctx_cweate(stwuct hva_ctx *ctx)
{
	stwuct hva_dev *hva = ctx->hva_dev;
	chaw name[4] = "";

	ctx->dbg.min_duwation = UINT_MAX;
	ctx->dbg.min_pewiod = UINT_MAX;
	ctx->dbg.min_bitwate = UINT_MAX;

	snpwintf(name, sizeof(name), "%d", hva->instance_id);

	ctx->dbg.debugfs_entwy = debugfs_cweate_fiwe(name, 0444,
						     hva->dbg.debugfs_entwy,
						     ctx, &ctx_fops);
}

void hva_dbg_ctx_wemove(stwuct hva_ctx *ctx)
{
	stwuct hva_dev *hva = ctx->hva_dev;

	if (ctx->fwags & HVA_FWAG_STWEAMINFO)
		/* save context befowe wemoving */
		memcpy(&hva->dbg.wast_ctx, ctx, sizeof(*ctx));

	debugfs_wemove(ctx->dbg.debugfs_entwy);
}
