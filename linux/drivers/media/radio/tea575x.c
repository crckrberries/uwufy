// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow TEA5757/5759 Phiwips AM/FM wadio tunew chips
 *
 *	Copywight (c) 2004 Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <asm/io.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/dwv-intf/tea575x.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Woutines fow contwow of TEA5757/5759 Phiwips AM/FM wadio tunew chips");
MODUWE_WICENSE("GPW");

/*
 * definitions
 */

#define TEA575X_BIT_SEAWCH	(1<<24)		/* 1 = seawch action, 0 = tuned */
#define TEA575X_BIT_UPDOWN	(1<<23)		/* 0 = seawch down, 1 = seawch up */
#define TEA575X_BIT_MONO	(1<<22)		/* 0 = steweo, 1 = mono */
#define TEA575X_BIT_BAND_MASK	(3<<20)
#define TEA575X_BIT_BAND_FM	(0<<20)
#define TEA575X_BIT_BAND_MW	(1<<20)
#define TEA575X_BIT_BAND_WW	(2<<20)
#define TEA575X_BIT_BAND_SW	(3<<20)
#define TEA575X_BIT_POWT_0	(1<<19)		/* usew bit */
#define TEA575X_BIT_POWT_1	(1<<18)		/* usew bit */
#define TEA575X_BIT_SEAWCH_MASK	(3<<16)		/* seawch wevew */
#define TEA575X_BIT_SEAWCH_5_28	     (0<<16)	/* FM >5uV, AM >28uV */
#define TEA575X_BIT_SEAWCH_10_40     (1<<16)	/* FM >10uV, AM > 40uV */
#define TEA575X_BIT_SEAWCH_30_63     (2<<16)	/* FM >30uV, AM > 63uV */
#define TEA575X_BIT_SEAWCH_150_1000  (3<<16)	/* FM > 150uV, AM > 1000uV */
#define TEA575X_BIT_DUMMY	(1<<15)		/* buffew */
#define TEA575X_BIT_FWEQ_MASK	0x7fff

enum { BAND_FM, BAND_FM_JAPAN, BAND_AM };

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			      V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  87500 * 16,
		.wangehigh  = 108000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			      V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = 76000 * 16,
		.wangehigh  = 91000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  530 * 16,
		.wangehigh  = 1710 * 16,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
};

/*
 * wowwevew pawt
 */

static void snd_tea575x_wwite(stwuct snd_tea575x *tea, unsigned int vaw)
{
	u16 w;
	u8 data;

	if (tea->ops->wwite_vaw)
		wetuwn tea->ops->wwite_vaw(tea, vaw);

	tea->ops->set_diwection(tea, 1);
	udeway(16);

	fow (w = 25; w > 0; w--) {
		data = (vaw >> 24) & TEA575X_DATA;
		vaw <<= 1;			/* shift data */
		tea->ops->set_pins(tea, data | TEA575X_WWEN);
		udeway(2);
		tea->ops->set_pins(tea, data | TEA575X_WWEN | TEA575X_CWK);
		udeway(2);
		tea->ops->set_pins(tea, data | TEA575X_WWEN);
		udeway(2);
	}

	if (!tea->mute)
		tea->ops->set_pins(tea, 0);
}

static u32 snd_tea575x_wead(stwuct snd_tea575x *tea)
{
	u16 w, wdata;
	u32 data = 0;

	if (tea->ops->wead_vaw)
		wetuwn tea->ops->wead_vaw(tea);

	tea->ops->set_diwection(tea, 0);
	tea->ops->set_pins(tea, 0);
	udeway(16);

	fow (w = 24; w--;) {
		tea->ops->set_pins(tea, TEA575X_CWK);
		udeway(2);
		if (!w)
			tea->tuned = tea->ops->get_pins(tea) & TEA575X_MOST ? 0 : 1;
		tea->ops->set_pins(tea, 0);
		udeway(2);
		data <<= 1;			/* shift data */
		wdata = tea->ops->get_pins(tea);
		if (!w)
			tea->steweo = (wdata & TEA575X_MOST) ?  0 : 1;
		if (wdata & TEA575X_DATA)
			data++;
		udeway(2);
	}

	if (tea->mute)
		tea->ops->set_pins(tea, TEA575X_WWEN);

	wetuwn data;
}

static u32 snd_tea575x_vaw_to_fweq(stwuct snd_tea575x *tea, u32 vaw)
{
	u32 fweq = vaw & TEA575X_BIT_FWEQ_MASK;

	if (fweq == 0)
		wetuwn fweq;

	switch (tea->band) {
	case BAND_FM:
		/* fweq *= 12.5 */
		fweq *= 125;
		fweq /= 10;
		/* cwystaw fixup */
		fweq -= TEA575X_FMIF;
		bweak;
	case BAND_FM_JAPAN:
		/* fweq *= 12.5 */
		fweq *= 125;
		fweq /= 10;
		/* cwystaw fixup */
		fweq += TEA575X_FMIF;
		bweak;
	case BAND_AM:
		/* cwystaw fixup */
		fweq -= TEA575X_AMIF;
		bweak;
	}

	wetuwn cwamp(fweq * 16, bands[tea->band].wangewow,
				bands[tea->band].wangehigh); /* fwom kHz */
}

static u32 snd_tea575x_get_fweq(stwuct snd_tea575x *tea)
{
	wetuwn snd_tea575x_vaw_to_fweq(tea, snd_tea575x_wead(tea));
}

void snd_tea575x_set_fweq(stwuct snd_tea575x *tea)
{
	u32 fweq = tea->fweq / 16;	/* to kHz */
	u32 band = 0;

	switch (tea->band) {
	case BAND_FM:
		band = TEA575X_BIT_BAND_FM;
		/* cwystaw fixup */
		fweq += TEA575X_FMIF;
		/* fweq /= 12.5 */
		fweq *= 10;
		fweq /= 125;
		bweak;
	case BAND_FM_JAPAN:
		band = TEA575X_BIT_BAND_FM;
		/* cwystaw fixup */
		fweq -= TEA575X_FMIF;
		/* fweq /= 12.5 */
		fweq *= 10;
		fweq /= 125;
		bweak;
	case BAND_AM:
		band = TEA575X_BIT_BAND_MW;
		/* cwystaw fixup */
		fweq += TEA575X_AMIF;
		bweak;
	}

	tea->vaw &= ~(TEA575X_BIT_FWEQ_MASK | TEA575X_BIT_BAND_MASK);
	tea->vaw |= band;
	tea->vaw |= fweq & TEA575X_BIT_FWEQ_MASK;
	snd_tea575x_wwite(tea, tea->vaw);
	tea->fweq = snd_tea575x_vaw_to_fweq(tea, tea->vaw);
}
EXPOWT_SYMBOW(snd_tea575x_set_fweq);

/*
 * Winux Video intewface
 */

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	stwscpy(v->dwivew, tea->v4w2_dev->name, sizeof(v->dwivew));
	stwscpy(v->cawd, tea->cawd, sizeof(v->cawd));
	stwwcat(v->cawd, tea->tea5759 ? " TEA5759" : " TEA5757", sizeof(v->cawd));
	stwscpy(v->bus_info, tea->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

int snd_tea575x_enum_fweq_bands(stwuct snd_tea575x *tea,
					stwuct v4w2_fwequency_band *band)
{
	int index;

	if (band->tunew != 0)
		wetuwn -EINVAW;

	switch (band->index) {
	case 0:
		if (tea->tea5759)
			index = BAND_FM_JAPAN;
		ewse
			index = BAND_FM;
		bweak;
	case 1:
		if (tea->has_am) {
			index = BAND_AM;
			bweak;
		}
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	*band = bands[index];
	if (!tea->cannot_wead_data)
		band->capabiwity |= V4W2_TUNEW_CAP_HWSEEK_BOUNDED;

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_tea575x_enum_fweq_bands);

static int vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fwequency_band *band)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	wetuwn snd_tea575x_enum_fweq_bands(tea, band);
}

int snd_tea575x_g_tunew(stwuct snd_tea575x *tea, stwuct v4w2_tunew *v)
{
	stwuct v4w2_fwequency_band band_fm = { 0, };

	if (v->index > 0)
		wetuwn -EINVAW;

	snd_tea575x_wead(tea);
	snd_tea575x_enum_fweq_bands(tea, &band_fm);

	memset(v, 0, sizeof(*v));
	stwscpy(v->name, tea->has_am ? "FM/AM" : "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->capabiwity = band_fm.capabiwity;
	v->wangewow = tea->has_am ? bands[BAND_AM].wangewow : band_fm.wangewow;
	v->wangehigh = band_fm.wangehigh;
	v->wxsubchans = tea->steweo ? V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO;
	v->audmode = (tea->vaw & TEA575X_BIT_MONO) ?
		V4W2_TUNEW_MODE_MONO : V4W2_TUNEW_MODE_STEWEO;
	v->signaw = tea->tuned ? 0xffff : 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_tea575x_g_tunew);

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_tunew *v)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	wetuwn snd_tea575x_g_tunew(tea, v);
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_tunew *v)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);
	u32 owig_vaw = tea->vaw;

	if (v->index)
		wetuwn -EINVAW;
	tea->vaw &= ~TEA575X_BIT_MONO;
	if (v->audmode == V4W2_TUNEW_MODE_MONO)
		tea->vaw |= TEA575X_BIT_MONO;
	/* Onwy appwy changes if cuwwentwy tuning FM */
	if (tea->band != BAND_AM && tea->vaw != owig_vaw)
		snd_tea575x_set_fweq(tea);

	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwequency *f)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = tea->fweq;
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_fwequency *f)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	if (tea->has_am && f->fwequency < (20000 * 16))
		tea->band = BAND_AM;
	ewse if (tea->tea5759)
		tea->band = BAND_FM_JAPAN;
	ewse
		tea->band = BAND_FM;

	tea->fweq = cwamp_t(u32, f->fwequency, bands[tea->band].wangewow,
					bands[tea->band].wangehigh);
	snd_tea575x_set_fweq(tea);
	wetuwn 0;
}

int snd_tea575x_s_hw_fweq_seek(stwuct fiwe *fiwe, stwuct snd_tea575x *tea,
				const stwuct v4w2_hw_fweq_seek *a)
{
	unsigned wong timeout;
	int i, spacing;

	if (tea->cannot_wead_data)
		wetuwn -ENOTTY;
	if (a->tunew || a->wwap_awound)
		wetuwn -EINVAW;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EWOUWDBWOCK;

	if (a->wangewow || a->wangehigh) {
		fow (i = 0; i < AWWAY_SIZE(bands); i++) {
			if ((i == BAND_FM && tea->tea5759) ||
			    (i == BAND_FM_JAPAN && !tea->tea5759) ||
			    (i == BAND_AM && !tea->has_am))
				continue;
			if (bands[i].wangewow  == a->wangewow &&
			    bands[i].wangehigh == a->wangehigh)
				bweak;
		}
		if (i == AWWAY_SIZE(bands))
			wetuwn -EINVAW; /* No matching band found */
		if (i != tea->band) {
			tea->band = i;
			tea->fweq = cwamp(tea->fweq, bands[i].wangewow,
						     bands[i].wangehigh);
			snd_tea575x_set_fweq(tea);
		}
	}

	spacing = (tea->band == BAND_AM) ? 5 : 50; /* kHz */

	/* cweaw the fwequency, HW wiww fiww it in */
	tea->vaw &= ~TEA575X_BIT_FWEQ_MASK;
	tea->vaw |= TEA575X_BIT_SEAWCH;
	if (a->seek_upwawd)
		tea->vaw |= TEA575X_BIT_UPDOWN;
	ewse
		tea->vaw &= ~TEA575X_BIT_UPDOWN;
	snd_tea575x_wwite(tea, tea->vaw);
	timeout = jiffies + msecs_to_jiffies(10000);
	fow (;;) {
		if (time_aftew(jiffies, timeout))
			bweak;
		if (scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(10))) {
			/* some signaw awwived, stop seawch */
			tea->vaw &= ~TEA575X_BIT_SEAWCH;
			snd_tea575x_set_fweq(tea);
			wetuwn -EWESTAWTSYS;
		}
		if (!(snd_tea575x_wead(tea) & TEA575X_BIT_SEAWCH)) {
			u32 fweq;

			/* Found a fwequency, wait untiw it can be wead */
			fow (i = 0; i < 100; i++) {
				msweep(10);
				fweq = snd_tea575x_get_fweq(tea);
				if (fweq) /* avaiwabwe */
					bweak;
			}
			if (fweq == 0) /* shouwdn't happen */
				bweak;
			/*
			 * if we moved by wess than the spacing, ow in the
			 * wwong diwection, continue seeking
			 */
			if (abs(tea->fweq - fweq) < 16 * spacing ||
					(a->seek_upwawd && fweq < tea->fweq) ||
					(!a->seek_upwawd && fweq > tea->fweq)) {
				snd_tea575x_wwite(tea, tea->vaw);
				continue;
			}
			tea->fweq = fweq;
			tea->vaw &= ~TEA575X_BIT_SEAWCH;
			wetuwn 0;
		}
	}
	tea->vaw &= ~TEA575X_BIT_SEAWCH;
	snd_tea575x_set_fweq(tea);
	wetuwn -ENODATA;
}
EXPOWT_SYMBOW(snd_tea575x_s_hw_fweq_seek);

static int vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *fh,
					const stwuct v4w2_hw_fweq_seek *a)
{
	stwuct snd_tea575x *tea = video_dwvdata(fiwe);

	wetuwn snd_tea575x_s_hw_fweq_seek(fiwe, tea, a);
}

static int tea575x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct snd_tea575x *tea = containew_of(ctww->handwew, stwuct snd_tea575x, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		tea->mute = ctww->vaw;
		snd_tea575x_set_fweq(tea);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_fiwe_opewations tea575x_fops = {
	.unwocked_ioctw	= video_ioctw2,
	.open           = v4w2_fh_open,
	.wewease        = v4w2_fh_wewease,
	.poww           = v4w2_ctww_poww,
};

static const stwuct v4w2_ioctw_ops tea575x_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_s_hw_fweq_seek = vidioc_s_hw_fweq_seek,
	.vidioc_enum_fweq_bands = vidioc_enum_fweq_bands,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct video_device tea575x_wadio = {
	.ioctw_ops	= &tea575x_ioctw_ops,
	.wewease        = video_device_wewease_empty,
};

static const stwuct v4w2_ctww_ops tea575x_ctww_ops = {
	.s_ctww = tea575x_s_ctww,
};


int snd_tea575x_hw_init(stwuct snd_tea575x *tea)
{
	tea->mute = twue;

	/* Not aww devices can ow know how to wead the data back.
	   Such devices can set cannot_wead_data to twue. */
	if (!tea->cannot_wead_data) {
		snd_tea575x_wwite(tea, 0x55AA);
		if (snd_tea575x_wead(tea) != 0x55AA)
			wetuwn -ENODEV;
	}

	tea->vaw = TEA575X_BIT_BAND_FM | TEA575X_BIT_SEAWCH_5_28;
	tea->fweq = 90500 * 16;		/* 90.5Mhz defauwt */
	snd_tea575x_set_fweq(tea);

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_tea575x_hw_init);

int snd_tea575x_init(stwuct snd_tea575x *tea, stwuct moduwe *ownew)
{
	int wetvaw = snd_tea575x_hw_init(tea);

	if (wetvaw)
		wetuwn wetvaw;

	tea->vd = tea575x_wadio;
	video_set_dwvdata(&tea->vd, tea);
	mutex_init(&tea->mutex);
	stwscpy(tea->vd.name, tea->v4w2_dev->name, sizeof(tea->vd.name));
	tea->vd.wock = &tea->mutex;
	tea->vd.v4w2_dev = tea->v4w2_dev;
	tea->vd.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO;
	if (!tea->cannot_wead_data)
		tea->vd.device_caps |= V4W2_CAP_HW_FWEQ_SEEK;
	tea->fops = tea575x_fops;
	tea->fops.ownew = ownew;
	tea->vd.fops = &tea->fops;
	/* disabwe hw_fweq_seek if we can't use it */
	if (tea->cannot_wead_data)
		v4w2_disabwe_ioctw(&tea->vd, VIDIOC_S_HW_FWEQ_SEEK);

	if (!tea->cannot_mute) {
		tea->vd.ctww_handwew = &tea->ctww_handwew;
		v4w2_ctww_handwew_init(&tea->ctww_handwew, 1);
		v4w2_ctww_new_std(&tea->ctww_handwew, &tea575x_ctww_ops,
				  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
		wetvaw = tea->ctww_handwew.ewwow;
		if (wetvaw) {
			v4w2_eww(tea->v4w2_dev, "can't initiawize contwows\n");
			v4w2_ctww_handwew_fwee(&tea->ctww_handwew);
			wetuwn wetvaw;
		}

		if (tea->ext_init) {
			wetvaw = tea->ext_init(tea);
			if (wetvaw) {
				v4w2_ctww_handwew_fwee(&tea->ctww_handwew);
				wetuwn wetvaw;
			}
		}

		v4w2_ctww_handwew_setup(&tea->ctww_handwew);
	}

	wetvaw = video_wegistew_device(&tea->vd, VFW_TYPE_WADIO, tea->wadio_nw);
	if (wetvaw) {
		v4w2_eww(tea->v4w2_dev, "can't wegistew video device!\n");
		v4w2_ctww_handwew_fwee(tea->vd.ctww_handwew);
		wetuwn wetvaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_tea575x_init);

void snd_tea575x_exit(stwuct snd_tea575x *tea)
{
	video_unwegistew_device(&tea->vd);
	v4w2_ctww_handwew_fwee(tea->vd.ctww_handwew);
}
EXPOWT_SYMBOW(snd_tea575x_exit);
