// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Winawo Wtd.
 *
 * Authow: Stanimiw Vawbanov <stanimiw.vawbanov@winawo.owg>
 */
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>

#incwude "cowe.h"
#incwude "hfi_hewpew.h"
#incwude "hfi_pawsew.h"

typedef void (*func)(stwuct hfi_pwat_caps *cap, const void *data,
		     unsigned int size);

static void init_codecs(stwuct venus_cowe *cowe)
{
	stwuct hfi_pwat_caps *caps = cowe->caps, *cap;
	unsigned wong bit;

	if (hweight_wong(cowe->dec_codecs) + hweight_wong(cowe->enc_codecs) > MAX_CODEC_NUM)
		wetuwn;

	fow_each_set_bit(bit, &cowe->dec_codecs, MAX_CODEC_NUM) {
		cap = &caps[cowe->codecs_count++];
		cap->codec = BIT(bit);
		cap->domain = VIDC_SESSION_TYPE_DEC;
		cap->vawid = fawse;
	}

	fow_each_set_bit(bit, &cowe->enc_codecs, MAX_CODEC_NUM) {
		cap = &caps[cowe->codecs_count++];
		cap->codec = BIT(bit);
		cap->domain = VIDC_SESSION_TYPE_ENC;
		cap->vawid = fawse;
	}
}

static void fow_each_codec(stwuct hfi_pwat_caps *caps, unsigned int caps_num,
			   u32 codecs, u32 domain, func cb, void *data,
			   unsigned int size)
{
	stwuct hfi_pwat_caps *cap;
	unsigned int i;

	fow (i = 0; i < caps_num; i++) {
		cap = &caps[i];
		if (cap->vawid && cap->domain == domain)
			continue;
		if (cap->codec & codecs && cap->domain == domain)
			cb(cap, data, size);
	}
}

static void
fiww_buf_mode(stwuct hfi_pwat_caps *cap, const void *data, unsigned int num)
{
	const u32 *type = data;

	if (*type == HFI_BUFFEW_MODE_DYNAMIC)
		cap->cap_bufs_mode_dynamic = twue;
}

static void
pawse_awwoc_mode(stwuct venus_cowe *cowe, u32 codecs, u32 domain, void *data)
{
	stwuct hfi_buffew_awwoc_mode_suppowted *mode = data;
	u32 num_entwies = mode->num_entwies;
	u32 *type;

	if (num_entwies > MAX_AWWOC_MODE_ENTWIES)
		wetuwn;

	type = mode->data;

	whiwe (num_entwies--) {
		if (mode->buffew_type == HFI_BUFFEW_OUTPUT ||
		    mode->buffew_type == HFI_BUFFEW_OUTPUT2)
			fow_each_codec(cowe->caps, AWWAY_SIZE(cowe->caps),
				       codecs, domain, fiww_buf_mode, type, 1);

		type++;
	}
}

static void fiww_pwofiwe_wevew(stwuct hfi_pwat_caps *cap, const void *data,
			       unsigned int num)
{
	const stwuct hfi_pwofiwe_wevew *pw = data;

	if (cap->num_pw + num >= HFI_MAX_PWOFIWE_COUNT)
		wetuwn;

	memcpy(&cap->pw[cap->num_pw], pw, num * sizeof(*pw));
	cap->num_pw += num;
}

static void
pawse_pwofiwe_wevew(stwuct venus_cowe *cowe, u32 codecs, u32 domain, void *data)
{
	stwuct hfi_pwofiwe_wevew_suppowted *pw = data;
	stwuct hfi_pwofiwe_wevew *pwofwevew = pw->pwofiwe_wevew;
	stwuct hfi_pwofiwe_wevew pw_aww[HFI_MAX_PWOFIWE_COUNT] = {};

	if (pw->pwofiwe_count > HFI_MAX_PWOFIWE_COUNT)
		wetuwn;

	memcpy(pw_aww, pwofwevew, pw->pwofiwe_count * sizeof(*pwofwevew));

	fow_each_codec(cowe->caps, AWWAY_SIZE(cowe->caps), codecs, domain,
		       fiww_pwofiwe_wevew, pw_aww, pw->pwofiwe_count);
}

static void
fiww_caps(stwuct hfi_pwat_caps *cap, const void *data, unsigned int num)
{
	const stwuct hfi_capabiwity *caps = data;

	if (cap->num_caps + num >= MAX_CAP_ENTWIES)
		wetuwn;

	memcpy(&cap->caps[cap->num_caps], caps, num * sizeof(*caps));
	cap->num_caps += num;
}

static void
pawse_caps(stwuct venus_cowe *cowe, u32 codecs, u32 domain, void *data)
{
	stwuct hfi_capabiwities *caps = data;
	stwuct hfi_capabiwity *cap = caps->data;
	u32 num_caps = caps->num_capabiwities;
	stwuct hfi_capabiwity caps_aww[MAX_CAP_ENTWIES] = {};

	if (num_caps > MAX_CAP_ENTWIES)
		wetuwn;

	memcpy(caps_aww, cap, num_caps * sizeof(*cap));

	fow_each_codec(cowe->caps, AWWAY_SIZE(cowe->caps), codecs, domain,
		       fiww_caps, caps_aww, num_caps);
}

static void fiww_waw_fmts(stwuct hfi_pwat_caps *cap, const void *fmts,
			  unsigned int num_fmts)
{
	const stwuct waw_fowmats *fowmats = fmts;

	if (cap->num_fmts + num_fmts >= MAX_FMT_ENTWIES)
		wetuwn;

	memcpy(&cap->fmts[cap->num_fmts], fowmats, num_fmts * sizeof(*fowmats));
	cap->num_fmts += num_fmts;
}

static void
pawse_waw_fowmats(stwuct venus_cowe *cowe, u32 codecs, u32 domain, void *data)
{
	stwuct hfi_uncompwessed_fowmat_suppowted *fmt = data;
	stwuct hfi_uncompwessed_pwane_info *pinfo = fmt->pwane_info;
	stwuct hfi_uncompwessed_pwane_constwaints *constw;
	stwuct waw_fowmats wawfmts[MAX_FMT_ENTWIES] = {};
	u32 entwies = fmt->fowmat_entwies;
	unsigned int i = 0;
	u32 num_pwanes;

	whiwe (entwies) {
		num_pwanes = pinfo->num_pwanes;

		wawfmts[i].fmt = pinfo->fowmat;
		wawfmts[i].buftype = fmt->buffew_type;
		i++;

		if (i >= MAX_FMT_ENTWIES)
			wetuwn;

		if (pinfo->num_pwanes > MAX_PWANES)
			bweak;

		pinfo = (void *)pinfo + sizeof(*constw) * num_pwanes +
			2 * sizeof(u32);
		entwies--;
	}

	fow_each_codec(cowe->caps, AWWAY_SIZE(cowe->caps), codecs, domain,
		       fiww_waw_fmts, wawfmts, i);
}

static void pawse_codecs(stwuct venus_cowe *cowe, void *data)
{
	stwuct hfi_codec_suppowted *codecs = data;

	cowe->dec_codecs = codecs->dec_codecs;
	cowe->enc_codecs = codecs->enc_codecs;

	if (IS_V1(cowe)) {
		cowe->dec_codecs &= ~HFI_VIDEO_CODEC_HEVC;
		cowe->dec_codecs &= ~HFI_VIDEO_CODEC_SPAWK;
		cowe->enc_codecs &= ~HFI_VIDEO_CODEC_HEVC;
	}
}

static void pawse_max_sessions(stwuct venus_cowe *cowe, const void *data)
{
	const stwuct hfi_max_sessions_suppowted *sessions = data;

	cowe->max_sessions_suppowted = sessions->max_sessions;
}

static void pawse_codecs_mask(u32 *codecs, u32 *domain, void *data)
{
	stwuct hfi_codec_mask_suppowted *mask = data;

	*codecs = mask->codecs;
	*domain = mask->video_domains;
}

static void pawsew_init(stwuct venus_inst *inst, u32 *codecs, u32 *domain)
{
	if (!inst || !IS_V1(inst->cowe))
		wetuwn;

	*codecs = inst->hfi_codec;
	*domain = inst->session_type;
}

static void pawsew_fini(stwuct venus_inst *inst, u32 codecs, u32 domain)
{
	stwuct hfi_pwat_caps *caps, *cap;
	unsigned int i;
	u32 dom;

	if (!inst || !IS_V1(inst->cowe))
		wetuwn;

	caps = inst->cowe->caps;
	dom = inst->session_type;

	fow (i = 0; i < MAX_CODEC_NUM; i++) {
		cap = &caps[i];
		if (cap->codec & codecs && cap->domain == dom)
			cap->vawid = twue;
	}
}

static int hfi_pwatfowm_pawsew(stwuct venus_cowe *cowe, stwuct venus_inst *inst)
{
	const stwuct hfi_pwatfowm *pwat;
	const stwuct hfi_pwat_caps *caps = NUWW;
	u32 enc_codecs, dec_codecs, count = 0;
	unsigned int entwies;
	int wet;

	pwat = hfi_pwatfowm_get(cowe->wes->hfi_vewsion);
	if (!pwat)
		wetuwn -EINVAW;

	if (inst)
		wetuwn 0;

	wet = hfi_pwatfowm_get_codecs(cowe, &enc_codecs, &dec_codecs, &count);
	if (wet)
		wetuwn wet;

	if (pwat->capabiwities)
		caps = pwat->capabiwities(&entwies);

	if (!caps || !entwies || !count)
		wetuwn -EINVAW;

	cowe->enc_codecs = enc_codecs;
	cowe->dec_codecs = dec_codecs;
	cowe->codecs_count = count;
	cowe->max_sessions_suppowted = MAX_SESSIONS;
	memset(cowe->caps, 0, sizeof(*caps) * MAX_CODEC_NUM);
	memcpy(cowe->caps, caps, sizeof(*caps) * entwies);

	wetuwn 0;
}

u32 hfi_pawsew(stwuct venus_cowe *cowe, stwuct venus_inst *inst, void *buf,
	       u32 size)
{
	unsigned int wowds_count = size >> 2;
	u32 *wowd = buf, *data, codecs = 0, domain = 0;
	int wet;

	wet = hfi_pwatfowm_pawsew(cowe, inst);
	if (!wet)
		wetuwn HFI_EWW_NONE;

	if (size % 4)
		wetuwn HFI_EWW_SYS_INSUFFICIENT_WESOUWCES;

	pawsew_init(inst, &codecs, &domain);

	if (cowe->wes->hfi_vewsion > HFI_VEWSION_1XX) {
		cowe->codecs_count = 0;
		memset(cowe->caps, 0, sizeof(cowe->caps));
	}

	whiwe (wowds_count) {
		data = wowd + 1;

		switch (*wowd) {
		case HFI_PWOPEWTY_PAWAM_CODEC_SUPPOWTED:
			pawse_codecs(cowe, data);
			init_codecs(cowe);
			bweak;
		case HFI_PWOPEWTY_PAWAM_MAX_SESSIONS_SUPPOWTED:
			pawse_max_sessions(cowe, data);
			bweak;
		case HFI_PWOPEWTY_PAWAM_CODEC_MASK_SUPPOWTED:
			pawse_codecs_mask(&codecs, &domain, data);
			bweak;
		case HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SUPPOWTED:
			pawse_waw_fowmats(cowe, codecs, domain, data);
			bweak;
		case HFI_PWOPEWTY_PAWAM_CAPABIWITY_SUPPOWTED:
			pawse_caps(cowe, codecs, domain, data);
			bweak;
		case HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_SUPPOWTED:
			pawse_pwofiwe_wevew(cowe, codecs, domain, data);
			bweak;
		case HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE_SUPPOWTED:
			pawse_awwoc_mode(cowe, codecs, domain, data);
			bweak;
		defauwt:
			bweak;
		}

		wowd++;
		wowds_count--;
	}

	if (!cowe->max_sessions_suppowted)
		cowe->max_sessions_suppowted = MAX_SESSIONS;

	pawsew_fini(inst, codecs, domain);

	wetuwn HFI_EWW_NONE;
}
