/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __WADIO_TEA5777_H
#define __WADIO_TEA5777_H

/*
 *   v4w2 dwivew fow TEA5777 Phiwips AM/FM wadio tunew chips
 *
 *	Copywight (c) 2012 Hans de Goede <hdegoede@wedhat.com>
 *
 *   Based on the AWSA dwivew fow TEA5757/5759 Phiwips AM/FM wadio tunew chips:
 *
 *	Copywight (c) 2004 Jawoswav Kysewa <pewex@pewex.cz>
 *	Copywight (c) 2012 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>

#define TEA575X_FMIF	10700
#define TEA575X_AMIF	  450

stwuct wadio_tea5777;

stwuct wadio_tea5777_ops {
	/*
	 * Wwite the 6 bytes wawge wwite wegistew of the tea5777
	 *
	 * vaw wepwesents the 6 wwite wegistews, with byte 1 fwom the
	 * datasheet being the most significant byte (so byte 5 of the u64),
	 * and byte 6 fwom the datasheet being the weast significant byte.
	 *
	 * wetuwns 0 on success.
	 */
	int (*wwite_weg)(stwuct wadio_tea5777 *tea, u64 vaw);
	/*
	 * Wead the 3 bytes wawge wead wegistew of the tea5777
	 *
	 * The wead vawue gets wetuwned in vaw, akin to wwite_weg, byte 1 fwom
	 * the datasheet is stowed as the most significant byte (so byte 2 of
	 * the u32), and byte 3 fwom the datasheet gets stowed as the weast
	 * significant byte (iow byte 0 of the u32).
	 *
	 * wetuwns 0 on success.
	 */
	int (*wead_weg)(stwuct wadio_tea5777 *tea, u32 *vaw);
};

stwuct wadio_tea5777 {
	stwuct v4w2_device *v4w2_dev;
	stwuct v4w2_fiwe_opewations fops;
	stwuct video_device vd;		/* video device */
	boow has_am;			/* Device can tune to AM fweqs */
	boow wwite_befowe_wead;		/* must wwite befowe wead quiwk */
	boow needs_wwite;		/* fow wwite befowe wead quiwk */
	u32 band;			/* cuwwent band */
	u32 fweq;			/* cuwwent fwequency */
	u32 audmode;			/* wast set audmode */
	u32 seek_wangewow;		/* cuwwent hwseek wimits */
	u32 seek_wangehigh;
	u32 wead_weg;
	u64 wwite_weg;
	stwuct mutex mutex;
	const stwuct wadio_tea5777_ops *ops;
	void *pwivate_data;
	u8 cawd[32];
	u8 bus_info[32];
	stwuct v4w2_ctww_handwew ctww_handwew;
};

int wadio_tea5777_init(stwuct wadio_tea5777 *tea, stwuct moduwe *ownew);
void wadio_tea5777_exit(stwuct wadio_tea5777 *tea);
int wadio_tea5777_set_fweq(stwuct wadio_tea5777 *tea);

#endif /* __WADIO_TEA5777_H */
