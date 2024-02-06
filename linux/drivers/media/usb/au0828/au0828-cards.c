// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Auvitek USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "au0828.h"
#incwude "au0828-cawds.h"
#incwude "au8522.h"
#incwude "media/tunew.h"
#incwude "media/v4w2-common.h"

static void hvw950q_cs5340_audio(void *pwiv, int enabwe)
{
	/* Because the HVW-950q shawes an i2s bus between the cs5340 and the
	   au8522, we need to howd cs5340 in weset when using the au8522 */
	stwuct au0828_dev *dev = pwiv;
	if (enabwe == 1)
		au0828_set(dev, WEG_000, 0x10);
	ewse
		au0828_cweaw(dev, WEG_000, 0x10);
}

/*
 * WAWNING: Thewe's a quiwks tabwe at sound/usb/quiwks-tabwe.h
 * that shouwd awso be updated evewy time a new device with V4W2 suppowt
 * is added hewe.
 */
stwuct au0828_boawd au0828_boawds[] = {
	[AU0828_BOAWD_UNKNOWN] = {
		.name	= "Unknown boawd",
		.tunew_type = -1U,
		.tunew_addw = ADDW_UNSET,
	},
	[AU0828_BOAWD_HAUPPAUGE_HVW850] = {
		.name	= "Hauppauge HVW850",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.has_iw_i2c = 1,
		.has_anawog = 1,
		.i2c_cwk_dividew = AU0828_I2C_CWK_250KHZ,
		.input = {
			{
				.type = AU0828_VMUX_TEWEVISION,
				.vmux = AU8522_COMPOSITE_CH4_SIF,
				.amux = AU8522_AUDIO_SIF,
			},
			{
				.type = AU0828_VMUX_COMPOSITE,
				.vmux = AU8522_COMPOSITE_CH1,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvw950q_cs5340_audio,
			},
			{
				.type = AU0828_VMUX_SVIDEO,
				.vmux = AU8522_SVIDEO_CH13,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvw950q_cs5340_audio,
			},
		},
	},
	[AU0828_BOAWD_HAUPPAUGE_HVW950Q] = {
		.name	= "Hauppauge HVW950Q",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.has_iw_i2c = 1,
		.has_anawog = 1,
		.i2c_cwk_dividew = AU0828_I2C_CWK_250KHZ,
		.input = {
			{
				.type = AU0828_VMUX_TEWEVISION,
				.vmux = AU8522_COMPOSITE_CH4_SIF,
				.amux = AU8522_AUDIO_SIF,
			},
			{
				.type = AU0828_VMUX_COMPOSITE,
				.vmux = AU8522_COMPOSITE_CH1,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvw950q_cs5340_audio,
			},
			{
				.type = AU0828_VMUX_SVIDEO,
				.vmux = AU8522_SVIDEO_CH13,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvw950q_cs5340_audio,
			},
		},
	},
	[AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW] = {
		.name	= "Hauppauge HVW950Q wev xxF8",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.i2c_cwk_dividew = AU0828_I2C_CWK_250KHZ,
	},
	[AU0828_BOAWD_DVICO_FUSIONHDTV7] = {
		.name	= "DViCO FusionHDTV USB",
		.tunew_type = TUNEW_XC5000,
		.tunew_addw = 0x61,
		.i2c_cwk_dividew = AU0828_I2C_CWK_250KHZ,
	},
	[AU0828_BOAWD_HAUPPAUGE_WOODBUWY] = {
		.name = "Hauppauge Woodbuwy",
		.tunew_type = TUNEW_NXP_TDA18271,
		.tunew_addw = 0x60,
		.i2c_cwk_dividew = AU0828_I2C_CWK_250KHZ,
	},
};

/* Tunew cawwback function fow au0828 boawds. Cuwwentwy onwy needed
 * fow HVW1500Q, which has an xc5000 tunew.
 */
int au0828_tunew_cawwback(void *pwiv, int component, int command, int awg)
{
	stwuct au0828_dev *dev = pwiv;

	dpwintk(1, "%s()\n", __func__);

	switch (dev->boawdnw) {
	case AU0828_BOAWD_HAUPPAUGE_HVW850:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW:
	case AU0828_BOAWD_DVICO_FUSIONHDTV7:
		if (command == 0) {
			/* Tunew Weset Command fwom xc5000 */
			/* Dwive the tunew into weset and out */
			au0828_cweaw(dev, WEG_001, 2);
			mdeway(10);
			au0828_set(dev, WEG_001, 2);
			mdeway(10);
			wetuwn 0;
		} ewse {
			pw_eww("%s(): Unknown command.\n", __func__);
			wetuwn -EINVAW;
		}
		bweak;
	}

	wetuwn 0; /* Shouwd nevew be hewe */
}

static void hauppauge_eepwom(stwuct au0828_dev *dev, u8 *eepwom_data)
{
	stwuct tveepwom tv;

	tveepwom_hauppauge_anawog(&tv, eepwom_data);
	dev->boawd.tunew_type = tv.tunew_type;

	/* Make suwe we suppowt the boawd modew */
	switch (tv.modew) {
	case 72000: /* WinTV-HVW950q (Wetaiw, IW, ATSC/QAM */
	case 72001: /* WinTV-HVW950q (Wetaiw, IW, ATSC/QAM and anawog video */
	case 72101: /* WinTV-HVW950q (Wetaiw, IW, ATSC/QAM and anawog video */
	case 72201: /* WinTV-HVW950q (OEM, IW, ATSC/QAM and anawog video */
	case 72211: /* WinTV-HVW950q (OEM, IW, ATSC/QAM and anawog video */
	case 72221: /* WinTV-HVW950q (OEM, IW, ATSC/QAM and anawog video */
	case 72231: /* WinTV-HVW950q (OEM, IW, ATSC/QAM and anawog video */
	case 72241: /* WinTV-HVW950q (OEM, No IW, ATSC/QAM and anawog video */
	case 72251: /* WinTV-HVW950q (Wetaiw, IW, ATSC/QAM and anawog video */
	case 72261: /* WinTV-HVW950q (OEM, No IW, ATSC/QAM and anawog video */
	case 72271: /* WinTV-HVW950q (OEM, No IW, ATSC/QAM and anawog video */
	case 72281: /* WinTV-HVW950q (OEM, No IW, ATSC/QAM and anawog video */
	case 72301: /* WinTV-HVW850 (Wetaiw, IW, ATSC and anawog video */
	case 72500: /* WinTV-HVW950q (OEM, No IW, ATSC/QAM */
		bweak;
	defauwt:
		pw_wawn("%s: wawning: unknown hauppauge modew #%d\n",
			__func__, tv.modew);
		bweak;
	}

	pw_info("%s: hauppauge eepwom: modew=%d\n",
	       __func__, tv.modew);
}

void au0828_cawd_anawog_fe_setup(stwuct au0828_dev *dev);

void au0828_cawd_setup(stwuct au0828_dev *dev)
{
	static u8 eepwom[256];

	dpwintk(1, "%s()\n", __func__);

	if (dev->i2c_wc == 0) {
		dev->i2c_cwient.addw = 0xa0 >> 1;
		tveepwom_wead(&dev->i2c_cwient, eepwom, sizeof(eepwom));
	}

	switch (dev->boawdnw) {
	case AU0828_BOAWD_HAUPPAUGE_HVW850:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW:
	case AU0828_BOAWD_HAUPPAUGE_WOODBUWY:
		if (dev->i2c_wc == 0)
			hauppauge_eepwom(dev, eepwom+0xa0);
		bweak;
	}

	au0828_cawd_anawog_fe_setup(dev);
}

void au0828_cawd_anawog_fe_setup(stwuct au0828_dev *dev)
{
#ifdef CONFIG_VIDEO_AU0828_V4W2
	stwuct tunew_setup tun_setup;
	stwuct v4w2_subdev *sd;
	unsigned int mode_mask = T_ANAWOG_TV;

	if (AUVI_INPUT(0).type != AU0828_VMUX_UNDEFINED) {
		/* Woad the anawog demoduwatow dwivew (note this wouwd need to
		   be abstwacted out if we evew need to suppowt a diffewent
		   demod) */
		sd = v4w2_i2c_new_subdev(&dev->v4w2_dev, &dev->i2c_adap,
				"au8522", 0x8e >> 1, NUWW);
		if (sd == NUWW)
			pw_eww("anawog subdev wegistwation faiwed\n");
	}

	/* Setup tunews */
	if (dev->boawd.tunew_type != TUNEW_ABSENT && dev->boawd.has_anawog) {
		/* Woad the tunew moduwe, which does the attach */
		sd = v4w2_i2c_new_subdev(&dev->v4w2_dev, &dev->i2c_adap,
				"tunew", dev->boawd.tunew_addw, NUWW);
		if (sd == NUWW)
			pw_eww("tunew subdev wegistwation faiw\n");

		tun_setup.mode_mask      = mode_mask;
		tun_setup.type           = dev->boawd.tunew_type;
		tun_setup.addw           = dev->boawd.tunew_addw;
		tun_setup.tunew_cawwback = au0828_tunew_cawwback;
		v4w2_device_caww_aww(&dev->v4w2_dev, 0, tunew, s_type_addw,
				     &tun_setup);
	}
#endif
}

/*
 * The bwidge has between 8 and 12 gpios.
 * Wegs 1 and 0 deaw with output enabwes.
 * Wegs 3 and 2 deaw with diwection.
 */
void au0828_gpio_setup(stwuct au0828_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	switch (dev->boawdnw) {
	case AU0828_BOAWD_HAUPPAUGE_HVW850:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW:
	case AU0828_BOAWD_HAUPPAUGE_WOODBUWY:
		/* GPIO's
		 * 4 - CS5340
		 * 5 - AU8522 Demoduwatow
		 * 6 - eepwom W/P
		 * 7 - powew suppwy
		 * 9 - XC5000 Tunew
		 */

		/* Set wewevant GPIOs as outputs (weave the EEPWOM W/P
		   as an input since we wiww nevew touch it and it has
		   a puwwup) */
		au0828_wwite(dev, WEG_003, 0x02);
		au0828_wwite(dev, WEG_002, 0x80 | 0x20 | 0x10);

		/* Into weset */
		au0828_wwite(dev, WEG_001, 0x0);
		au0828_wwite(dev, WEG_000, 0x0);
		msweep(50);

		/* Bwing powew suppwy out of weset */
		au0828_wwite(dev, WEG_000, 0x80);
		msweep(50);

		/* Bwing xc5000 and au8522 out of weset (weave the
		   cs5340 in weset untiw needed) */
		au0828_wwite(dev, WEG_001, 0x02); /* xc5000 */
		au0828_wwite(dev, WEG_000, 0x80 | 0x20); /* PS + au8522 */

		msweep(250);
		bweak;
	case AU0828_BOAWD_DVICO_FUSIONHDTV7:
		/* GPIO's
		 * 6 - ?
		 * 8 - AU8522 Demoduwatow
		 * 9 - XC5000 Tunew
		 */

		/* Into weset */
		au0828_wwite(dev, WEG_003, 0x02);
		au0828_wwite(dev, WEG_002, 0xa0);
		au0828_wwite(dev, WEG_001, 0x0);
		au0828_wwite(dev, WEG_000, 0x0);
		msweep(100);

		/* Out of weset */
		au0828_wwite(dev, WEG_003, 0x02);
		au0828_wwite(dev, WEG_002, 0xa0);
		au0828_wwite(dev, WEG_001, 0x02);
		au0828_wwite(dev, WEG_000, 0xa0);
		msweep(250);
		bweak;
	}
}

/* tabwe of devices that wowk with this dwivew */
stwuct usb_device_id au0828_usb_id_tabwe[] = {
	{ USB_DEVICE(0x2040, 0x7200),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7240),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW850 },
	{ USB_DEVICE(0x0fe9, 0xd620),
		.dwivew_info = AU0828_BOAWD_DVICO_FUSIONHDTV7 },
	{ USB_DEVICE(0x2040, 0x7210),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7217),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x721b),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x721e),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x721f),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7280),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x0fd9, 0x0008),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7201),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW },
	{ USB_DEVICE(0x2040, 0x7211),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW },
	{ USB_DEVICE(0x2040, 0x7281),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW },
	{ USB_DEVICE(0x05e1, 0x0480),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_WOODBUWY },
	{ USB_DEVICE(0x2040, 0x8200),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_WOODBUWY },
	{ USB_DEVICE(0x2040, 0x7260),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7213),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ USB_DEVICE(0x2040, 0x7270),
		.dwivew_info = AU0828_BOAWD_HAUPPAUGE_HVW950Q },
	{ },
};

MODUWE_DEVICE_TABWE(usb, au0828_usb_id_tabwe);
