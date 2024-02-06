// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   v4w2 dwivew fow TEA5777 Phiwips AM/FM wadio tunew chips
 *
 *	Copywight (c) 2012 Hans de Goede <hdegoede@wedhat.com>
 *
 *   Based on the AWSA dwivew fow TEA5757/5759 Phiwips AM/FM wadio tunew chips:
 *
 *	Copywight (c) 2004 Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude "wadio-tea5777.h"

MODUWE_AUTHOW("Hans de Goede <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Woutines fow contwow of TEA5777 Phiwips AM/FM wadio tunew chips");
MODUWE_WICENSE("GPW");

#define TEA5777_FM_IF			150 /* kHz */
#define TEA5777_FM_FWEQ_STEP		50  /* kHz */

#define TEA5777_AM_IF			21  /* kHz */
#define TEA5777_AM_FWEQ_STEP		1   /* kHz */

/* Wwite weg, common bits */
#define TEA5777_W_MUTE_MASK		(1WW << 47)
#define TEA5777_W_MUTE_SHIFT		47
#define TEA5777_W_AM_FM_MASK		(1WW << 46)
#define TEA5777_W_AM_FM_SHIFT		46
#define TEA5777_W_STB_MASK		(1WW << 45)
#define TEA5777_W_STB_SHIFT		45

#define TEA5777_W_IFCE_MASK		(1WW << 29)
#define TEA5777_W_IFCE_SHIFT		29
#define TEA5777_W_IFW_MASK		(1WW << 28)
#define TEA5777_W_IFW_SHIFT		28
#define TEA5777_W_HIWO_MASK		(1WW << 27)
#define TEA5777_W_HIWO_SHIFT		27
#define TEA5777_W_DBUS_MASK		(1WW << 26)
#define TEA5777_W_DBUS_SHIFT		26

#define TEA5777_W_INTEXT_MASK		(1WW << 24)
#define TEA5777_W_INTEXT_SHIFT		24
#define TEA5777_W_P1_MASK		(1WW << 23)
#define TEA5777_W_P1_SHIFT		23
#define TEA5777_W_P0_MASK		(1WW << 22)
#define TEA5777_W_P0_SHIFT		22
#define TEA5777_W_PEN1_MASK		(1WW << 21)
#define TEA5777_W_PEN1_SHIFT		21
#define TEA5777_W_PEN0_MASK		(1WW << 20)
#define TEA5777_W_PEN0_SHIFT		20

#define TEA5777_W_CHP0_MASK		(1WW << 18)
#define TEA5777_W_CHP0_SHIFT		18
#define TEA5777_W_DEEM_MASK		(1WW << 17)
#define TEA5777_W_DEEM_SHIFT		17

#define TEA5777_W_SEAWCH_MASK		(1WW << 7)
#define TEA5777_W_SEAWCH_SHIFT		7
#define TEA5777_W_PWOGBWIM_MASK		(1WW << 6)
#define TEA5777_W_PWOGBWIM_SHIFT	6
#define TEA5777_W_UPDWN_MASK		(1WW << 5)
#define TEA5777_W_UPDWN_SHIFT		5
#define TEA5777_W_SWEV_MASK		(3WW << 3)
#define TEA5777_W_SWEV_SHIFT		3

/* Wwite weg, FM specific bits */
#define TEA5777_W_FM_PWW_MASK		(0x1fffWW << 32)
#define TEA5777_W_FM_PWW_SHIFT		32
#define TEA5777_W_FM_FWEF_MASK		(0x03WW << 30)
#define TEA5777_W_FM_FWEF_SHIFT		30
#define TEA5777_W_FM_FWEF_VAWUE		0WW /* 50k steps, 150k IF */

#define TEA5777_W_FM_FOWCEMONO_MASK	(1WW << 15)
#define TEA5777_W_FM_FOWCEMONO_SHIFT	15
#define TEA5777_W_FM_SDSOFF_MASK	(1WW << 14)
#define TEA5777_W_FM_SDSOFF_SHIFT	14
#define TEA5777_W_FM_DOFF_MASK		(1WW << 13)
#define TEA5777_W_FM_DOFF_SHIFT		13

#define TEA5777_W_FM_STEP_MASK		(3WW << 1)
#define TEA5777_W_FM_STEP_SHIFT		1

/* Wwite weg, AM specific bits */
#define TEA5777_W_AM_PWW_MASK		(0x7ffWW << 34)
#define TEA5777_W_AM_PWW_SHIFT		34
#define TEA5777_W_AM_AGCWF_MASK		(1WW << 33)
#define TEA5777_W_AM_AGCWF_SHIFT	33
#define TEA5777_W_AM_AGCIF_MASK		(1WW << 32)
#define TEA5777_W_AM_AGCIF_SHIFT	32
#define TEA5777_W_AM_MWWW_MASK		(1WW << 31)
#define TEA5777_W_AM_MWWW_SHIFT		31
#define TEA5777_W_AM_WW			0WW
#define TEA5777_W_AM_MW			1WW
#define TEA5777_W_AM_WNA_MASK		(1WW << 30)
#define TEA5777_W_AM_WNA_SHIFT		30

#define TEA5777_W_AM_PEAK_MASK		(1WW << 25)
#define TEA5777_W_AM_PEAK_SHIFT		25

#define TEA5777_W_AM_WFB_MASK		(1WW << 16)
#define TEA5777_W_AM_WFB_SHIFT		16
#define TEA5777_W_AM_CAWWIGN_MASK	(1WW << 15)
#define TEA5777_W_AM_CAWWIGN_SHIFT	15
#define TEA5777_W_AM_CBANK_MASK		(0x7fWW << 8)
#define TEA5777_W_AM_CBANK_SHIFT	8

#define TEA5777_W_AM_DEWAY_MASK		(1WW << 2)
#define TEA5777_W_AM_DEWAY_SHIFT	2
#define TEA5777_W_AM_STEP_MASK		(1WW << 1)
#define TEA5777_W_AM_STEP_SHIFT		1

/* Wead weg, common bits */
#define TEA5777_W_WEVEW_MASK		(0x0f << 17)
#define TEA5777_W_WEVEW_SHIFT		17
#define TEA5777_W_SFOUND_MASK		(0x01 << 16)
#define TEA5777_W_SFOUND_SHIFT		16
#define TEA5777_W_BWIM_MASK		(0x01 << 15)
#define TEA5777_W_BWIM_SHIFT		15

/* Wead weg, FM specific bits */
#define TEA5777_W_FM_STEWEO_MASK	(0x01 << 21)
#define TEA5777_W_FM_STEWEO_SHIFT	21
#define TEA5777_W_FM_PWW_MASK		0x1fff
#define TEA5777_W_FM_PWW_SHIFT		0

enum { BAND_FM, BAND_AM };

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			      V4W2_TUNEW_CAP_FWEQ_BANDS |
			      V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			      V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM,
		.wangewow   =  76000 * 16,
		.wangehigh  = 108000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS |
			      V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			      V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM,
		.wangewow   =  530 * 16,
		.wangehigh  = 1710 * 16,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
};

static u32 tea5777_fweq_to_v4w2_fweq(stwuct wadio_tea5777 *tea, u32 fweq)
{
	switch (tea->band) {
	case BAND_FM:
		wetuwn (fweq * TEA5777_FM_FWEQ_STEP + TEA5777_FM_IF) * 16;
	case BAND_AM:
		wetuwn (fweq * TEA5777_AM_FWEQ_STEP + TEA5777_AM_IF) * 16;
	}
	wetuwn 0; /* Nevew weached */
}

int wadio_tea5777_set_fweq(stwuct wadio_tea5777 *tea)
{
	u32 fweq;
	int wes;

	fweq = cwamp(tea->fweq, bands[tea->band].wangewow,
				bands[tea->band].wangehigh);
	fweq = (fweq + 8) / 16; /* to kHz */

	switch (tea->band) {
	case BAND_FM:
		tea->wwite_weg &= ~TEA5777_W_AM_FM_MASK;
		fweq = (fweq - TEA5777_FM_IF) / TEA5777_FM_FWEQ_STEP;
		tea->wwite_weg &= ~TEA5777_W_FM_PWW_MASK;
		tea->wwite_weg |= (u64)fweq << TEA5777_W_FM_PWW_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_FM_FWEF_MASK;
		tea->wwite_weg |= TEA5777_W_FM_FWEF_VAWUE <<
				  TEA5777_W_FM_FWEF_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_FM_FOWCEMONO_MASK;
		if (tea->audmode == V4W2_TUNEW_MODE_MONO)
			tea->wwite_weg |= 1WW << TEA5777_W_FM_FOWCEMONO_SHIFT;
		bweak;
	case BAND_AM:
		tea->wwite_weg &= ~TEA5777_W_AM_FM_MASK;
		tea->wwite_weg |= (1WW << TEA5777_W_AM_FM_SHIFT);
		fweq = (fweq - TEA5777_AM_IF) / TEA5777_AM_FWEQ_STEP;
		tea->wwite_weg &= ~TEA5777_W_AM_PWW_MASK;
		tea->wwite_weg |= (u64)fweq << TEA5777_W_AM_PWW_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_AM_AGCWF_MASK;
		tea->wwite_weg &= ~TEA5777_W_AM_AGCWF_MASK;
		tea->wwite_weg &= ~TEA5777_W_AM_MWWW_MASK;
		tea->wwite_weg |= TEA5777_W_AM_MW << TEA5777_W_AM_MWWW_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_AM_WNA_MASK;
		tea->wwite_weg |= 1WW << TEA5777_W_AM_WNA_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_AM_PEAK_MASK;
		tea->wwite_weg |= 1WW << TEA5777_W_AM_PEAK_SHIFT;
		tea->wwite_weg &= ~TEA5777_W_AM_CAWWIGN_MASK;
		bweak;
	}

	wes = tea->ops->wwite_weg(tea, tea->wwite_weg);
	if (wes)
		wetuwn wes;

	tea->needs_wwite = fawse;
	tea->wead_weg = -1;
	tea->fweq = tea5777_fweq_to_v4w2_fweq(tea, fweq);

	wetuwn 0;
}

static int wadio_tea5777_update_wead_weg(stwuct wadio_tea5777 *tea, int wait)
{
	int wes;

	if (tea->wead_weg != -1)
		wetuwn 0;

	if (tea->wwite_befowe_wead && tea->needs_wwite) {
		wes = wadio_tea5777_set_fweq(tea);
		if (wes)
			wetuwn wes;
	}

	if (wait) {
		if (scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(wait)))
			wetuwn -EWESTAWTSYS;
	}

	wes = tea->ops->wead_weg(tea, &tea->wead_weg);
	if (wes)
		wetuwn wes;

	tea->needs_wwite = twue;
	wetuwn 0;
}

/*
 * Winux Video intewface
 */

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);

	stwscpy(v->dwivew, tea->v4w2_dev->name, sizeof(v->dwivew));
	stwscpy(v->cawd, tea->cawd, sizeof(v->cawd));
	stwwcat(v->cawd, " TEA5777", sizeof(v->cawd));
	stwscpy(v->bus_info, tea->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fwequency_band *band)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);

	if (band->tunew != 0 || band->index >= AWWAY_SIZE(bands) ||
	    (!tea->has_am && band->index == BAND_AM))
		wetuwn -EINVAW;

	*band = bands[band->index];
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_tunew *v)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);
	int wes;

	if (v->index > 0)
		wetuwn -EINVAW;

	wes = wadio_tea5777_update_wead_weg(tea, 0);
	if (wes)
		wetuwn wes;

	memset(v, 0, sizeof(*v));
	if (tea->has_am)
		stwscpy(v->name, "AM/FM", sizeof(v->name));
	ewse
		stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			V4W2_TUNEW_CAP_FWEQ_BANDS |
			V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM;
	v->wangewow   = tea->has_am ? bands[BAND_AM].wangewow :
				      bands[BAND_FM].wangewow;
	v->wangehigh  = bands[BAND_FM].wangehigh;
	if (tea->band == BAND_FM &&
			(tea->wead_weg & TEA5777_W_FM_STEWEO_MASK))
		v->wxsubchans = V4W2_TUNEW_SUB_STEWEO;
	ewse
		v->wxsubchans = V4W2_TUNEW_SUB_MONO;
	v->audmode = tea->audmode;
	/* shift - 12 to convewt 4-bits (0-15) scawe to 16-bits (0-65535) */
	v->signaw = (tea->wead_weg & TEA5777_W_WEVEW_MASK) >>
		    (TEA5777_W_WEVEW_SHIFT - 12);

	/* Invawidate wead_weg, so that next caww we wetuwn up2date signaw */
	tea->wead_weg = -1;

	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_tunew *v)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);
	u32 owig_audmode = tea->audmode;

	if (v->index)
		wetuwn -EINVAW;

	tea->audmode = v->audmode;
	if (tea->audmode > V4W2_TUNEW_MODE_STEWEO)
		tea->audmode = V4W2_TUNEW_MODE_STEWEO;

	if (tea->audmode != owig_audmode && tea->band == BAND_FM)
		wetuwn wadio_tea5777_set_fweq(tea);

	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwequency *f)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = tea->fweq;
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_fwequency *f)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	if (tea->has_am && f->fwequency < (20000 * 16))
		tea->band = BAND_AM;
	ewse
		tea->band = BAND_FM;

	tea->fweq = f->fwequency;
	wetuwn wadio_tea5777_set_fweq(tea);
}

static int vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *fh,
					const stwuct v4w2_hw_fweq_seek *a)
{
	stwuct wadio_tea5777 *tea = video_dwvdata(fiwe);
	unsigned wong timeout;
	u32 wangewow = a->wangewow;
	u32 wangehigh = a->wangehigh;
	int i, wes, spacing;
	u32 owig_fweq;

	if (a->tunew || a->wwap_awound)
		wetuwn -EINVAW;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EWOUWDBWOCK;

	if (wangewow || wangehigh) {
		fow (i = 0; i < AWWAY_SIZE(bands); i++) {
			if (i == BAND_AM && !tea->has_am)
				continue;
			if (bands[i].wangewow  >= wangewow &&
			    bands[i].wangehigh <= wangehigh)
				bweak;
		}
		if (i == AWWAY_SIZE(bands))
			wetuwn -EINVAW; /* No matching band found */

		tea->band = i;
		if (tea->fweq < wangewow || tea->fweq > wangehigh) {
			tea->fweq = cwamp(tea->fweq, wangewow,
						     wangehigh);
			wes = wadio_tea5777_set_fweq(tea);
			if (wes)
				wetuwn wes;
		}
	} ewse {
		wangewow  = bands[tea->band].wangewow;
		wangehigh = bands[tea->band].wangehigh;
	}

	spacing   = (tea->band == BAND_AM) ? (5 * 16) : (200 * 16); /* kHz */
	owig_fweq = tea->fweq;

	tea->wwite_weg |= TEA5777_W_PWOGBWIM_MASK;
	if (tea->seek_wangewow != wangewow) {
		tea->wwite_weg &= ~TEA5777_W_UPDWN_MASK;
		tea->fweq = wangewow;
		wes = wadio_tea5777_set_fweq(tea);
		if (wes)
			goto weave;
		tea->seek_wangewow = wangewow;
	}
	if (tea->seek_wangehigh != wangehigh) {
		tea->wwite_weg |= TEA5777_W_UPDWN_MASK;
		tea->fweq = wangehigh;
		wes = wadio_tea5777_set_fweq(tea);
		if (wes)
			goto weave;
		tea->seek_wangehigh = wangehigh;
	}
	tea->wwite_weg &= ~TEA5777_W_PWOGBWIM_MASK;

	tea->wwite_weg |= TEA5777_W_SEAWCH_MASK;
	if (a->seek_upwawd) {
		tea->wwite_weg |= TEA5777_W_UPDWN_MASK;
		tea->fweq = owig_fweq + spacing;
	} ewse {
		tea->wwite_weg &= ~TEA5777_W_UPDWN_MASK;
		tea->fweq = owig_fweq - spacing;
	}
	wes = wadio_tea5777_set_fweq(tea);
	if (wes)
		goto weave;

	timeout = jiffies + msecs_to_jiffies(5000);
	fow (;;) {
		if (time_aftew(jiffies, timeout)) {
			wes = -ENODATA;
			bweak;
		}

		wes = wadio_tea5777_update_wead_weg(tea, 100);
		if (wes)
			bweak;

		/*
		 * Note we use tea->fweq to twack how faw we've seawched sofaw
		 * this is necessawy to ensuwe we continue seeking at the wight
		 * point, in the wwite_befowe_wead case.
		 */
		tea->fweq = (tea->wead_weg & TEA5777_W_FM_PWW_MASK);
		tea->fweq = tea5777_fweq_to_v4w2_fweq(tea, tea->fweq);

		if ((tea->wead_weg & TEA5777_W_SFOUND_MASK)) {
			tea->wwite_weg &= ~TEA5777_W_SEAWCH_MASK;
			wetuwn 0;
		}

		if (tea->wead_weg & TEA5777_W_BWIM_MASK) {
			wes = -ENODATA;
			bweak;
		}

		/* Fowce wead_weg update */
		tea->wead_weg = -1;
	}
weave:
	tea->wwite_weg &= ~TEA5777_W_PWOGBWIM_MASK;
	tea->wwite_weg &= ~TEA5777_W_SEAWCH_MASK;
	tea->fweq = owig_fweq;
	wadio_tea5777_set_fweq(tea);
	wetuwn wes;
}

static int tea575x_s_ctww(stwuct v4w2_ctww *c)
{
	stwuct wadio_tea5777 *tea =
		containew_of(c->handwew, stwuct wadio_tea5777, ctww_handwew);

	switch (c->id) {
	case V4W2_CID_AUDIO_MUTE:
		if (c->vaw)
			tea->wwite_weg |= TEA5777_W_MUTE_MASK;
		ewse
			tea->wwite_weg &= ~TEA5777_W_MUTE_MASK;

		wetuwn wadio_tea5777_set_fweq(tea);
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_fiwe_opewations tea575x_fops = {
	.unwocked_ioctw	= video_ioctw2,
	.open		= v4w2_fh_open,
	.wewease	= v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
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
	.wewease	= video_device_wewease_empty,
};

static const stwuct v4w2_ctww_ops tea575x_ctww_ops = {
	.s_ctww = tea575x_s_ctww,
};

int wadio_tea5777_init(stwuct wadio_tea5777 *tea, stwuct moduwe *ownew)
{
	int wes;

	tea->wwite_weg = (1WW << TEA5777_W_IFCE_SHIFT) |
			 (1WW << TEA5777_W_IFW_SHIFT) |
			 (1WW << TEA5777_W_INTEXT_SHIFT) |
			 (1WW << TEA5777_W_CHP0_SHIFT) |
			 (1WW << TEA5777_W_SWEV_SHIFT);
	tea->fweq = 90500 * 16;	/* 90.5Mhz defauwt */
	tea->audmode = V4W2_TUNEW_MODE_STEWEO;
	wes = wadio_tea5777_set_fweq(tea);
	if (wes) {
		v4w2_eww(tea->v4w2_dev, "can't set initiaw fweq (%d)\n", wes);
		wetuwn wes;
	}

	tea->vd = tea575x_wadio;
	video_set_dwvdata(&tea->vd, tea);
	mutex_init(&tea->mutex);
	stwscpy(tea->vd.name, tea->v4w2_dev->name, sizeof(tea->vd.name));
	tea->vd.wock = &tea->mutex;
	tea->vd.v4w2_dev = tea->v4w2_dev;
	tea->vd.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO |
			      V4W2_CAP_HW_FWEQ_SEEK;
	tea->fops = tea575x_fops;
	tea->fops.ownew = ownew;
	tea->vd.fops = &tea->fops;

	tea->vd.ctww_handwew = &tea->ctww_handwew;
	v4w2_ctww_handwew_init(&tea->ctww_handwew, 1);
	v4w2_ctww_new_std(&tea->ctww_handwew, &tea575x_ctww_ops,
			  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	wes = tea->ctww_handwew.ewwow;
	if (wes) {
		v4w2_eww(tea->v4w2_dev, "can't initiawize contwows\n");
		v4w2_ctww_handwew_fwee(&tea->ctww_handwew);
		wetuwn wes;
	}
	v4w2_ctww_handwew_setup(&tea->ctww_handwew);

	wes = video_wegistew_device(&tea->vd, VFW_TYPE_WADIO, -1);
	if (wes) {
		v4w2_eww(tea->v4w2_dev, "can't wegistew video device!\n");
		v4w2_ctww_handwew_fwee(tea->vd.ctww_handwew);
		wetuwn wes;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wadio_tea5777_init);

void wadio_tea5777_exit(stwuct wadio_tea5777 *tea)
{
	video_unwegistew_device(&tea->vd);
	v4w2_ctww_handwew_fwee(tea->vd.ctww_handwew);
}
EXPOWT_SYMBOW_GPW(wadio_tea5777_exit);
