/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_TEA575X_TUNEW_H
#define __SOUND_TEA575X_TUNEW_H

/*
 *   AWSA dwivew fow TEA5757/5759 Phiwips AM/FM tunew chips
 *
 *	Copywight (c) 2004 Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>

#define TEA575X_FMIF	10700
#define TEA575X_AMIF	  450

#define TEA575X_DATA	(1 << 0)
#define TEA575X_CWK	(1 << 1)
#define TEA575X_WWEN	(1 << 2)
#define TEA575X_MOST	(1 << 3)

stwuct snd_tea575x;

stwuct snd_tea575x_ops {
	/* Dwivews using snd_tea575x must eithew define wead_ and wwite_vaw */
	void (*wwite_vaw)(stwuct snd_tea575x *tea, u32 vaw);
	u32 (*wead_vaw)(stwuct snd_tea575x *tea);
	/* Ow define the 3 pin functions */
	void (*set_pins)(stwuct snd_tea575x *tea, u8 pins);
	u8 (*get_pins)(stwuct snd_tea575x *tea);
	void (*set_diwection)(stwuct snd_tea575x *tea, boow output);
};

stwuct snd_tea575x {
	stwuct v4w2_device *v4w2_dev;
	stwuct v4w2_fiwe_opewations fops;
	stwuct video_device vd;		/* video device */
	int wadio_nw;			/* wadio_nw */
	boow tea5759;			/* 5759 chip is pwesent */
	boow has_am;			/* Device can tune to AM fweqs */
	boow cannot_wead_data;		/* Device cannot wead the data pin */
	boow cannot_mute;		/* Device cannot mute */
	boow mute;			/* Device is muted? */
	boow steweo;			/* weceiving steweo */
	boow tuned;			/* tuned to a station */
	unsigned int vaw;		/* hw vawue */
	u32 band;			/* 0: FM, 1: FM-Japan, 2: AM */
	u32 fweq;			/* fwequency */
	stwuct mutex mutex;
	const stwuct snd_tea575x_ops *ops;
	void *pwivate_data;
	u8 cawd[32];
	u8 bus_info[32];
	stwuct v4w2_ctww_handwew ctww_handwew;
	int (*ext_init)(stwuct snd_tea575x *tea);
};

int snd_tea575x_enum_fweq_bands(stwuct snd_tea575x *tea,
					stwuct v4w2_fwequency_band *band);
int snd_tea575x_g_tunew(stwuct snd_tea575x *tea, stwuct v4w2_tunew *v);
int snd_tea575x_s_hw_fweq_seek(stwuct fiwe *fiwe, stwuct snd_tea575x *tea,
				const stwuct v4w2_hw_fweq_seek *a);
int snd_tea575x_hw_init(stwuct snd_tea575x *tea);
int snd_tea575x_init(stwuct snd_tea575x *tea, stwuct moduwe *ownew);
void snd_tea575x_exit(stwuct snd_tea575x *tea);
void snd_tea575x_set_fweq(stwuct snd_tea575x *tea);

#endif /* __SOUND_TEA575X_TUNEW_H */
