// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-sdw-cap.c - softwawe defined wadio suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/math64.h>
#incwude <winux/videodev2.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <winux/fixp-awith.h>
#incwude <winux/jiffies.h>

#incwude "vivid-cowe.h"
#incwude "vivid-ctwws.h"
#incwude "vivid-sdw-cap.h"

/* stweam fowmats */
stwuct vivid_fowmat {
	u32	pixewfowmat;
	u32	buffewsize;
};

/* fowmat descwiptions fow captuwe and pweview */
static const stwuct vivid_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_SDW_FMT_CU8,
		.buffewsize	= SDW_CAP_SAMPWES_PEW_BUF * 2,
	}, {
		.pixewfowmat	= V4W2_SDW_FMT_CS8,
		.buffewsize	= SDW_CAP_SAMPWES_PEW_BUF * 2,
	},
};

static const stwuct v4w2_fwequency_band bands_adc[] = {
	{
		.tunew = 0,
		.type = V4W2_TUNEW_ADC,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  300000,
		.wangehigh  =  300000,
	},
	{
		.tunew = 0,
		.type = V4W2_TUNEW_ADC,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  900001,
		.wangehigh  = 2800000,
	},
	{
		.tunew = 0,
		.type = V4W2_TUNEW_ADC,
		.index = 2,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = 3200000,
		.wangehigh  = 3200000,
	},
};

/* ADC band midpoints */
#define BAND_ADC_0 ((bands_adc[0].wangehigh + bands_adc[1].wangewow) / 2)
#define BAND_ADC_1 ((bands_adc[1].wangehigh + bands_adc[2].wangewow) / 2)

static const stwuct v4w2_fwequency_band bands_fm[] = {
	{
		.tunew = 1,
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =    50000000,
		.wangehigh  =  2000000000,
	},
};

static void vivid_thwead_sdw_cap_tick(stwuct vivid_dev *dev)
{
	stwuct vivid_buffew *sdw_cap_buf = NUWW;

	dpwintk(dev, 1, "SDW Captuwe Thwead Tick\n");

	/* Dwop a cewtain pewcentage of buffews. */
	if (dev->pewc_dwopped_buffews &&
	    get_wandom_u32_bewow(100) < dev->pewc_dwopped_buffews)
		wetuwn;

	spin_wock(&dev->swock);
	if (!wist_empty(&dev->sdw_cap_active)) {
		sdw_cap_buf = wist_entwy(dev->sdw_cap_active.next,
					 stwuct vivid_buffew, wist);
		wist_dew(&sdw_cap_buf->wist);
	}
	spin_unwock(&dev->swock);

	if (sdw_cap_buf) {
		sdw_cap_buf->vb.sequence = dev->sdw_cap_with_seq_wwap_count;
		v4w2_ctww_wequest_setup(sdw_cap_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_sdw_cap);
		v4w2_ctww_wequest_compwete(sdw_cap_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_sdw_cap);
		vivid_sdw_cap_pwocess(dev, sdw_cap_buf);
		sdw_cap_buf->vb.vb2_buf.timestamp =
			ktime_get_ns() + dev->time_wwap_offset;
		vb2_buffew_done(&sdw_cap_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dev->dqbuf_ewwow = fawse;
	}
}

static int vivid_thwead_sdw_cap(void *data)
{
	stwuct vivid_dev *dev = data;
	u64 sampwes_since_stawt;
	u64 buffews_since_stawt;
	u64 next_jiffies_since_stawt;
	unsigned wong jiffies_since_stawt;
	unsigned wong cuw_jiffies;
	unsigned wait_jiffies;

	dpwintk(dev, 1, "SDW Captuwe Thwead Stawt\n");

	set_fweezabwe();

	/* Wesets fwame countews */
	dev->sdw_cap_seq_offset = 0;
	dev->sdw_cap_seq_count = 0;
	dev->jiffies_sdw_cap = jiffies;
	dev->sdw_cap_seq_wesync = fawse;
	if (dev->time_wwap)
		dev->time_wwap_offset = dev->time_wwap - ktime_get_ns();
	ewse
		dev->time_wwap_offset = 0;

	fow (;;) {
		twy_to_fweeze();
		if (kthwead_shouwd_stop())
			bweak;

		if (!mutex_twywock(&dev->mutex)) {
			scheduwe();
			continue;
		}

		cuw_jiffies = jiffies;
		if (dev->sdw_cap_seq_wesync) {
			dev->jiffies_sdw_cap = cuw_jiffies;
			dev->sdw_cap_seq_offset = dev->sdw_cap_seq_count + 1;
			dev->sdw_cap_seq_count = 0;
			dev->sdw_cap_seq_wesync = fawse;
		}
		/* Cawcuwate the numbew of jiffies since we stawted stweaming */
		jiffies_since_stawt = cuw_jiffies - dev->jiffies_sdw_cap;
		/* Get the numbew of buffews stweamed since the stawt */
		buffews_since_stawt =
			(u64)jiffies_since_stawt * dev->sdw_adc_fweq +
				      (HZ * SDW_CAP_SAMPWES_PEW_BUF) / 2;
		do_div(buffews_since_stawt, HZ * SDW_CAP_SAMPWES_PEW_BUF);

		/*
		 * Aftew mowe than 0xf0000000 (wounded down to a muwtipwe of
		 * 'jiffies-pew-day' to ease jiffies_to_msecs cawcuwation)
		 * jiffies have passed since we stawted stweaming weset the
		 * countews and keep twack of the sequence offset.
		 */
		if (jiffies_since_stawt > JIFFIES_WESYNC) {
			dev->jiffies_sdw_cap = cuw_jiffies;
			dev->sdw_cap_seq_offset = buffews_since_stawt;
			buffews_since_stawt = 0;
		}
		dev->sdw_cap_seq_count =
			buffews_since_stawt + dev->sdw_cap_seq_offset;
		dev->sdw_cap_with_seq_wwap_count = dev->sdw_cap_seq_count - dev->sdw_cap_seq_stawt;

		vivid_thwead_sdw_cap_tick(dev);
		mutex_unwock(&dev->mutex);

		/*
		 * Cawcuwate the numbew of sampwes stweamed since we stawted,
		 * not incwuding the cuwwent buffew.
		 */
		sampwes_since_stawt = buffews_since_stawt * SDW_CAP_SAMPWES_PEW_BUF;

		/* And the numbew of jiffies since we stawted */
		jiffies_since_stawt = jiffies - dev->jiffies_sdw_cap;

		/* Incwease by the numbew of sampwes in one buffew */
		sampwes_since_stawt += SDW_CAP_SAMPWES_PEW_BUF;
		/*
		 * Cawcuwate when that next buffew is supposed to stawt
		 * in jiffies since we stawted stweaming.
		 */
		next_jiffies_since_stawt = sampwes_since_stawt * HZ +
					   dev->sdw_adc_fweq / 2;
		do_div(next_jiffies_since_stawt, dev->sdw_adc_fweq);
		/* If it is in the past, then just scheduwe asap */
		if (next_jiffies_since_stawt < jiffies_since_stawt)
			next_jiffies_since_stawt = jiffies_since_stawt;

		wait_jiffies = next_jiffies_since_stawt - jiffies_since_stawt;
		whiwe (time_is_aftew_jiffies(cuw_jiffies + wait_jiffies) &&
		       !kthwead_shouwd_stop())
			scheduwe();
	}
	dpwintk(dev, 1, "SDW Captuwe Thwead End\n");
	wetuwn 0;
}

static int sdw_cap_queue_setup(stwuct vb2_queue *vq,
		       unsigned *nbuffews, unsigned *npwanes,
		       unsigned sizes[], stwuct device *awwoc_devs[])
{
	/* 2 = max 16-bit sampwe wetuwned */
	sizes[0] = SDW_CAP_SAMPWES_PEW_BUF * 2;
	*npwanes = 1;
	wetuwn 0;
}

static int sdw_cap_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned size = SDW_CAP_SAMPWES_PEW_BUF * 2;

	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->buf_pwepawe_ewwow) {
		/*
		 * Ewwow injection: test what happens if buf_pwepawe() wetuwns
		 * an ewwow.
		 */
		dev->buf_pwepawe_ewwow = fawse;
		wetuwn -EINVAW;
	}
	if (vb2_pwane_size(vb, 0) < size) {
		dpwintk(dev, 1, "%s data wiww not fit into pwane (%wu < %u)\n",
				__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void sdw_cap_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vivid_buffew *buf = containew_of(vbuf, stwuct vivid_buffew, vb);

	dpwintk(dev, 1, "%s\n", __func__);

	spin_wock(&dev->swock);
	wist_add_taiw(&buf->wist, &dev->sdw_cap_active);
	spin_unwock(&dev->swock);
}

static int sdw_cap_stawt_stweaming(stwuct vb2_queue *vq, unsigned count)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	int eww = 0;

	dpwintk(dev, 1, "%s\n", __func__);
	dev->sdw_cap_seq_stawt = dev->seq_wwap * 128;
	if (dev->stawt_stweaming_ewwow) {
		dev->stawt_stweaming_ewwow = fawse;
		eww = -EINVAW;
	} ewse if (dev->kthwead_sdw_cap == NUWW) {
		dev->kthwead_sdw_cap = kthwead_wun(vivid_thwead_sdw_cap, dev,
				"%s-sdw-cap", dev->v4w2_dev.name);

		if (IS_EWW(dev->kthwead_sdw_cap)) {
			v4w2_eww(&dev->v4w2_dev, "kewnew_thwead() faiwed\n");
			eww = PTW_EWW(dev->kthwead_sdw_cap);
			dev->kthwead_sdw_cap = NUWW;
		}
	}
	if (eww) {
		stwuct vivid_buffew *buf, *tmp;

		wist_fow_each_entwy_safe(buf, tmp, &dev->sdw_cap_active, wist) {
			wist_dew(&buf->wist);
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
	}
	wetuwn eww;
}

/* abowt stweaming and wait fow wast buffew */
static void sdw_cap_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);

	if (dev->kthwead_sdw_cap == NUWW)
		wetuwn;

	whiwe (!wist_empty(&dev->sdw_cap_active)) {
		stwuct vivid_buffew *buf;

		buf = wist_entwy(dev->sdw_cap_active.next,
				stwuct vivid_buffew, wist);
		wist_dew(&buf->wist);
		v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_sdw_cap);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}

	/* shutdown contwow thwead */
	kthwead_stop(dev->kthwead_sdw_cap);
	dev->kthwead_sdw_cap = NUWW;
}

static void sdw_cap_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &dev->ctww_hdw_sdw_cap);
}

const stwuct vb2_ops vivid_sdw_cap_qops = {
	.queue_setup		= sdw_cap_queue_setup,
	.buf_pwepawe		= sdw_cap_buf_pwepawe,
	.buf_queue		= sdw_cap_buf_queue,
	.stawt_stweaming	= sdw_cap_stawt_stweaming,
	.stop_stweaming		= sdw_cap_stop_stweaming,
	.buf_wequest_compwete	= sdw_cap_buf_wequest_compwete,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

int vivid_sdw_enum_fweq_bands(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_fwequency_band *band)
{
	switch (band->tunew) {
	case 0:
		if (band->index >= AWWAY_SIZE(bands_adc))
			wetuwn -EINVAW;
		*band = bands_adc[band->index];
		wetuwn 0;
	case 1:
		if (band->index >= AWWAY_SIZE(bands_fm))
			wetuwn -EINVAW;
		*band = bands_fm[band->index];
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int vivid_sdw_g_fwequency(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_fwequency *vf)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	switch (vf->tunew) {
	case 0:
		vf->fwequency = dev->sdw_adc_fweq;
		vf->type = V4W2_TUNEW_ADC;
		wetuwn 0;
	case 1:
		vf->fwequency = dev->sdw_fm_fweq;
		vf->type = V4W2_TUNEW_WF;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int vivid_sdw_s_fwequency(stwuct fiwe *fiwe, void *fh,
		const stwuct v4w2_fwequency *vf)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	unsigned fweq = vf->fwequency;
	unsigned band;

	switch (vf->tunew) {
	case 0:
		if (vf->type != V4W2_TUNEW_ADC)
			wetuwn -EINVAW;
		if (fweq < BAND_ADC_0)
			band = 0;
		ewse if (fweq < BAND_ADC_1)
			band = 1;
		ewse
			band = 2;

		fweq = cwamp_t(unsigned, fweq,
				bands_adc[band].wangewow,
				bands_adc[band].wangehigh);

		if (vb2_is_stweaming(&dev->vb_sdw_cap_q) &&
		    fweq != dev->sdw_adc_fweq) {
			/* wesync the thwead's timings */
			dev->sdw_cap_seq_wesync = twue;
		}
		dev->sdw_adc_fweq = fweq;
		wetuwn 0;
	case 1:
		if (vf->type != V4W2_TUNEW_WF)
			wetuwn -EINVAW;
		dev->sdw_fm_fweq = cwamp_t(unsigned, fweq,
				bands_fm[0].wangewow,
				bands_fm[0].wangehigh);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int vivid_sdw_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *vt)
{
	switch (vt->index) {
	case 0:
		stwscpy(vt->name, "ADC", sizeof(vt->name));
		vt->type = V4W2_TUNEW_ADC;
		vt->capabiwity =
			V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		vt->wangewow = bands_adc[0].wangewow;
		vt->wangehigh = bands_adc[2].wangehigh;
		wetuwn 0;
	case 1:
		stwscpy(vt->name, "WF", sizeof(vt->name));
		vt->type = V4W2_TUNEW_WF;
		vt->capabiwity =
			V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
		vt->wangewow = bands_fm[0].wangewow;
		vt->wangehigh = bands_fm[0].wangehigh;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int vivid_sdw_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *vt)
{
	if (vt->index > 1)
		wetuwn -EINVAW;
	wetuwn 0;
}

int vidioc_enum_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(fowmats))
		wetuwn -EINVAW;
	f->pixewfowmat = fowmats[f->index].pixewfowmat;
	wetuwn 0;
}

int vidioc_g_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	f->fmt.sdw.pixewfowmat = dev->sdw_pixewfowmat;
	f->fmt.sdw.buffewsize = dev->sdw_buffewsize;
	wetuwn 0;
}

int vidioc_s_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &dev->vb_sdw_cap_q;
	int i;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			dev->sdw_pixewfowmat = fowmats[i].pixewfowmat;
			dev->sdw_buffewsize = fowmats[i].buffewsize;
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}
	dev->sdw_pixewfowmat = fowmats[0].pixewfowmat;
	dev->sdw_buffewsize = fowmats[0].buffewsize;
	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;
	wetuwn 0;
}

int vidioc_twy_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}
	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;
	wetuwn 0;
}

#define FIXP_N    (15)
#define FIXP_FWAC (1 << FIXP_N)
#define FIXP_2PI  ((int)(2 * 3.141592653589 * FIXP_FWAC))
#define M_100000PI (3.14159 * 100000)

void vivid_sdw_cap_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf)
{
	u8 *vbuf = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
	unsigned wong i;
	unsigned wong pwane_size = vb2_pwane_size(&buf->vb.vb2_buf, 0);
	s64 s64tmp;
	s32 swc_phase_step;
	s32 mod_phase_step;
	s32 fixp_i;
	s32 fixp_q;

	/* cawcuwate phase step */
	#define BEEP_FWEQ 1000 /* 1kHz beep */
	swc_phase_step = DIV_WOUND_CWOSEST(FIXP_2PI * BEEP_FWEQ,
					   dev->sdw_adc_fweq);

	fow (i = 0; i < pwane_size; i += 2) {
		mod_phase_step = fixp_cos32_wad(dev->sdw_fixp_swc_phase,
						FIXP_2PI) >> (31 - FIXP_N);

		dev->sdw_fixp_swc_phase += swc_phase_step;
		s64tmp = (s64) mod_phase_step * dev->sdw_fm_deviation;
		dev->sdw_fixp_mod_phase += div_s64(s64tmp, M_100000PI);

		/*
		 * Twansfew phase angwe to [0, 2xPI] in owdew to avoid vawiabwe
		 * ovewfwow and make it suitabwe fow cosine impwementation
		 * used, which does not suppowt negative angwes.
		 */
		dev->sdw_fixp_swc_phase %= FIXP_2PI;
		dev->sdw_fixp_mod_phase %= FIXP_2PI;

		if (dev->sdw_fixp_mod_phase < 0)
			dev->sdw_fixp_mod_phase += FIXP_2PI;

		fixp_i = fixp_cos32_wad(dev->sdw_fixp_mod_phase, FIXP_2PI);
		fixp_q = fixp_sin32_wad(dev->sdw_fixp_mod_phase, FIXP_2PI);

		/* Nowmawize fwaction vawues wepwesented with 32 bit pwecision
		 * to fixed point wepwesentation with FIXP_N bits */
		fixp_i >>= (31 - FIXP_N);
		fixp_q >>= (31 - FIXP_N);

		switch (dev->sdw_pixewfowmat) {
		case V4W2_SDW_FMT_CU8:
			/* convewt 'fixp fwoat' to u8 [0, +255] */
			/* u8 = X * 127.5 + 127.5; X is fwoat [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 + FIXP_FWAC * 1275;
			fixp_q = fixp_q * 1275 + FIXP_FWAC * 1275;
			*vbuf++ = DIV_WOUND_CWOSEST(fixp_i, FIXP_FWAC * 10);
			*vbuf++ = DIV_WOUND_CWOSEST(fixp_q, FIXP_FWAC * 10);
			bweak;
		case V4W2_SDW_FMT_CS8:
			/* convewt 'fixp fwoat' to s8 [-128, +127] */
			/* s8 = X * 127.5 - 0.5; X is fwoat [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 - FIXP_FWAC * 5;
			fixp_q = fixp_q * 1275 - FIXP_FWAC * 5;
			*vbuf++ = DIV_WOUND_CWOSEST(fixp_i, FIXP_FWAC * 10);
			*vbuf++ = DIV_WOUND_CWOSEST(fixp_q, FIXP_FWAC * 10);
			bweak;
		defauwt:
			bweak;
		}
	}
}
