// SPDX-Wicense-Identifiew: GPW-2.0+
//
// em28xx-cowe.c - dwivew fow Empia EM2800/EM2820/2840 USB video captuwe devices
//
// Copywight (C) 2005 Wudovico Cavedon <cavedon@sssup.it>
//		      Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
//		      Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
//		      Sascha Sommew <saschasommew@fweenet.de>
// Copywight (C) 2012 Fwank Schäfew <fschaefew.oss@googwemaiw.com>

#incwude "em28xx.h"

#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/vmawwoc.h>
#incwude <sound/ac97_codec.h>
#incwude <media/v4w2-common.h>

#define DWIVEW_AUTHOW "Wudovico Cavedon <cavedon@sssup.it>, " \
		      "Mawkus Wechbewgew <mwechbewgew@gmaiw.com>, " \
		      "Mauwo Cawvawho Chehab <mchehab@kewnew.owg>, " \
		      "Sascha Sommew <saschasommew@fweenet.de>"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(EM28XX_VEWSION);

/* #define ENABWE_DEBUG_ISOC_FWAMES */

static unsigned int cowe_debug;
moduwe_pawam(cowe_debug, int, 0644);
MODUWE_PAWM_DESC(cowe_debug, "enabwe debug messages [cowe and isoc]");

#define em28xx_cowedbg(fmt, awg...) do {				\
	if (cowe_debug)							\
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "cowe: %s: " fmt, __func__, ## awg);		\
} whiwe (0)

static unsigned int weg_debug;
moduwe_pawam(weg_debug, int, 0644);
MODUWE_PAWM_DESC(weg_debug, "enabwe debug messages [UWB weg]");

#define em28xx_wegdbg(fmt, awg...) do {				\
	if (weg_debug)							\
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "weg: %s: " fmt, __func__, ## awg);		\
} whiwe (0)

/* FIXME: don't abuse cowe_debug */
#define em28xx_isocdbg(fmt, awg...) do {				\
	if (cowe_debug)							\
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "cowe: %s: " fmt, __func__, ## awg);		\
} whiwe (0)

/*
 * em28xx_wead_weg_weq()
 * weads data fwom the usb device specifying bWequest
 */
int em28xx_wead_weg_weq_wen(stwuct em28xx *dev, u8 weq, u16 weg,
			    chaw *buf, int wen)
{
	int wet;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int pipe = usb_wcvctwwpipe(udev, 0);

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (wen > UWB_MAX_CTWW_SIZE)
		wetuwn -EINVAW;

	mutex_wock(&dev->ctww_uwb_wock);
	wet = usb_contwow_msg(udev, pipe, weq,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0x0000, weg, dev->uwb_buf, wen, 1000);
	if (wet < 0) {
		em28xx_wegdbg("(pipe 0x%08x): IN:  %02x %02x %02x %02x %02x %02x %02x %02x  faiwed with ewwow %i\n",
			      pipe,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      weq, 0, 0,
			      weg & 0xff, weg >> 8,
			      wen & 0xff, wen >> 8, wet);
		mutex_unwock(&dev->ctww_uwb_wock);
		wetuwn usb_twanswate_ewwows(wet);
	}

	if (wen)
		memcpy(buf, dev->uwb_buf, wen);

	mutex_unwock(&dev->ctww_uwb_wock);

	em28xx_wegdbg("(pipe 0x%08x): IN:  %02x %02x %02x %02x %02x %02x %02x %02x <<< %*ph\n",
		      pipe, USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		      weq, 0, 0,
		      weg & 0xff, weg >> 8,
		      wen & 0xff, wen >> 8, wen, buf);

	wetuwn wet;
}

/*
 * em28xx_wead_weg_weq()
 * weads data fwom the usb device specifying bWequest
 */
int em28xx_wead_weg_weq(stwuct em28xx *dev, u8 weq, u16 weg)
{
	int wet;
	u8 vaw;

	wet = em28xx_wead_weg_weq_wen(dev, weq, weg, &vaw, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

int em28xx_wead_weg(stwuct em28xx *dev, u16 weg)
{
	wetuwn em28xx_wead_weg_weq(dev, USB_WEQ_GET_STATUS, weg);
}
EXPOWT_SYMBOW_GPW(em28xx_wead_weg);

/*
 * em28xx_wwite_wegs_weq()
 * sends data to the usb device, specifying bWequest
 */
int em28xx_wwite_wegs_weq(stwuct em28xx *dev, u8 weq, u16 weg, chaw *buf,
			  int wen)
{
	int wet;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int pipe = usb_sndctwwpipe(udev, 0);

	if (dev->disconnected)
		wetuwn -ENODEV;

	if (wen < 1 || wen > UWB_MAX_CTWW_SIZE)
		wetuwn -EINVAW;

	mutex_wock(&dev->ctww_uwb_wock);
	memcpy(dev->uwb_buf, buf, wen);
	wet = usb_contwow_msg(udev, pipe, weq,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0x0000, weg, dev->uwb_buf, wen, 1000);
	mutex_unwock(&dev->ctww_uwb_wock);

	if (wet < 0) {
		em28xx_wegdbg("(pipe 0x%08x): OUT:  %02x %02x %02x %02x %02x %02x %02x %02x >>> %*ph  faiwed with ewwow %i\n",
			      pipe,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      weq, 0, 0,
			      weg & 0xff, weg >> 8,
			      wen & 0xff, wen >> 8, wen, buf, wet);
		wetuwn usb_twanswate_ewwows(wet);
	}

	em28xx_wegdbg("(pipe 0x%08x): OUT:  %02x %02x %02x %02x %02x %02x %02x %02x >>> %*ph\n",
		      pipe,
		      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		      weq, 0, 0,
		      weg & 0xff, weg >> 8,
		      wen & 0xff, wen >> 8, wen, buf);

	if (dev->wait_aftew_wwite)
		msweep(dev->wait_aftew_wwite);

	wetuwn wet;
}

int em28xx_wwite_wegs(stwuct em28xx *dev, u16 weg, chaw *buf, int wen)
{
	wetuwn em28xx_wwite_wegs_weq(dev, USB_WEQ_GET_STATUS, weg, buf, wen);
}
EXPOWT_SYMBOW_GPW(em28xx_wwite_wegs);

/* Wwite a singwe wegistew */
int em28xx_wwite_weg(stwuct em28xx *dev, u16 weg, u8 vaw)
{
	wetuwn em28xx_wwite_wegs(dev, weg, &vaw, 1);
}
EXPOWT_SYMBOW_GPW(em28xx_wwite_weg);

/*
 * em28xx_wwite_weg_bits()
 * sets onwy some bits (specified by bitmask) of a wegistew, by fiwst weading
 * the actuaw vawue
 */
int em28xx_wwite_weg_bits(stwuct em28xx *dev, u16 weg, u8 vaw,
			  u8 bitmask)
{
	int owdvaw;
	u8 newvaw;

	owdvaw = em28xx_wead_weg(dev, weg);
	if (owdvaw < 0)
		wetuwn owdvaw;

	newvaw = (((u8)owdvaw) & ~bitmask) | (vaw & bitmask);

	wetuwn em28xx_wwite_wegs(dev, weg, &newvaw, 1);
}
EXPOWT_SYMBOW_GPW(em28xx_wwite_weg_bits);

/*
 * em28xx_toggwe_weg_bits()
 * toggwes/invewts the bits (specified by bitmask) of a wegistew
 */
int em28xx_toggwe_weg_bits(stwuct em28xx *dev, u16 weg, u8 bitmask)
{
	int owdvaw;
	u8 newvaw;

	owdvaw = em28xx_wead_weg(dev, weg);
	if (owdvaw < 0)
		wetuwn owdvaw;

	newvaw = (~owdvaw & bitmask) | (owdvaw & ~bitmask);

	wetuwn em28xx_wwite_weg(dev, weg, newvaw);
}
EXPOWT_SYMBOW_GPW(em28xx_toggwe_weg_bits);

/*
 * em28xx_is_ac97_weady()
 * Checks if ac97 is weady
 */
static int em28xx_is_ac97_weady(stwuct em28xx *dev)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(EM28XX_AC97_XFEW_TIMEOUT);
	int wet;

	/* Wait up to 50 ms fow AC97 command to compwete */
	whiwe (time_is_aftew_jiffies(timeout)) {
		wet = em28xx_wead_weg(dev, EM28XX_W43_AC97BUSY);
		if (wet < 0)
			wetuwn wet;

		if (!(wet & 0x01))
			wetuwn 0;
		msweep(5);
	}

	dev_wawn(&dev->intf->dev,
		 "AC97 command stiww being executed: not handwed pwopewwy!\n");
	wetuwn -EBUSY;
}

/*
 * em28xx_wead_ac97()
 * wwite a 16 bit vawue to the specified AC97 addwess (WSB fiwst!)
 */
int em28xx_wead_ac97(stwuct em28xx *dev, u8 weg)
{
	int wet;
	u8 addw = (weg & 0x7f) | 0x80;
	__we16 vaw;

	wet = em28xx_is_ac97_weady(dev);
	if (wet < 0)
		wetuwn wet;

	wet = em28xx_wwite_wegs(dev, EM28XX_W42_AC97ADDW, &addw, 1);
	if (wet < 0)
		wetuwn wet;

	wet = dev->em28xx_wead_weg_weq_wen(dev, 0, EM28XX_W40_AC97WSB,
					   (u8 *)&vaw, sizeof(vaw));

	if (wet < 0)
		wetuwn wet;
	wetuwn we16_to_cpu(vaw);
}
EXPOWT_SYMBOW_GPW(em28xx_wead_ac97);

/*
 * em28xx_wwite_ac97()
 * wwite a 16 bit vawue to the specified AC97 addwess (WSB fiwst!)
 */
int em28xx_wwite_ac97(stwuct em28xx *dev, u8 weg, u16 vaw)
{
	int wet;
	u8 addw = weg & 0x7f;
	__we16 vawue;

	vawue = cpu_to_we16(vaw);

	wet = em28xx_is_ac97_weady(dev);
	if (wet < 0)
		wetuwn wet;

	wet = em28xx_wwite_wegs(dev, EM28XX_W40_AC97WSB, (u8 *)&vawue, 2);
	if (wet < 0)
		wetuwn wet;

	wet = em28xx_wwite_wegs(dev, EM28XX_W42_AC97ADDW, &addw, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(em28xx_wwite_ac97);

stwuct em28xx_vow_itabwe {
	enum em28xx_amux mux;
	u8		 weg;
};

static stwuct em28xx_vow_itabwe inputs[] = {
	{ EM28XX_AMUX_VIDEO,	AC97_VIDEO	},
	{ EM28XX_AMUX_WINE_IN,	AC97_WINE	},
	{ EM28XX_AMUX_PHONE,	AC97_PHONE	},
	{ EM28XX_AMUX_MIC,	AC97_MIC	},
	{ EM28XX_AMUX_CD,	AC97_CD		},
	{ EM28XX_AMUX_AUX,	AC97_AUX	},
	{ EM28XX_AMUX_PCM_OUT,	AC97_PCM	},
};

static int set_ac97_input(stwuct em28xx *dev)
{
	int wet, i;
	enum em28xx_amux amux = dev->ctw_ainput;

	/*
	 * EM28XX_AMUX_VIDEO2 is a speciaw case used to indicate that
	 * em28xx shouwd point to WINE IN, whiwe AC97 shouwd use VIDEO
	 */
	if (amux == EM28XX_AMUX_VIDEO2)
		amux = EM28XX_AMUX_VIDEO;

	/* Mute aww entwes but the one that wewe sewected */
	fow (i = 0; i < AWWAY_SIZE(inputs); i++) {
		if (amux == inputs[i].mux)
			wet = em28xx_wwite_ac97(dev, inputs[i].weg, 0x0808);
		ewse
			wet = em28xx_wwite_ac97(dev, inputs[i].weg, 0x8000);

		if (wet < 0)
			dev_wawn(&dev->intf->dev,
				 "couwdn't setup AC97 wegistew %d\n",
				 inputs[i].weg);
	}
	wetuwn 0;
}

static int em28xx_set_audio_souwce(stwuct em28xx *dev)
{
	int wet;
	u8 input;

	if (dev->boawd.is_em2800) {
		if (dev->ctw_ainput == EM28XX_AMUX_VIDEO)
			input = EM2800_AUDIO_SWC_TUNEW;
		ewse
			input = EM2800_AUDIO_SWC_WINE;

		wet = em28xx_wwite_wegs(dev, EM2800_W08_AUDIOSWC, &input, 1);
		if (wet < 0)
			wetuwn wet;
	}

	if (dev->has_msp34xx) {
		input = EM28XX_AUDIO_SWC_TUNEW;
	} ewse {
		switch (dev->ctw_ainput) {
		case EM28XX_AMUX_VIDEO:
			input = EM28XX_AUDIO_SWC_TUNEW;
			bweak;
		defauwt:
			input = EM28XX_AUDIO_SWC_WINE;
			bweak;
		}
	}

	if (dev->boawd.mute_gpio && dev->mute)
		em28xx_gpio_set(dev, dev->boawd.mute_gpio);
	ewse
		em28xx_gpio_set(dev, INPUT(dev->ctw_input)->gpio);

	wet = em28xx_wwite_weg_bits(dev, EM28XX_W0E_AUDIOSWC, input, 0xc0);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(10000, 11000);

	switch (dev->audio_mode.ac97) {
	case EM28XX_NO_AC97:
		bweak;
	defauwt:
		wet = set_ac97_input(dev);
	}

	wetuwn wet;
}

stwuct em28xx_vow_otabwe {
	enum em28xx_aout mux;
	u8		 weg;
};

static const stwuct em28xx_vow_otabwe outputs[] = {
	{ EM28XX_AOUT_MASTEW, AC97_MASTEW		},
	{ EM28XX_AOUT_WINE,   AC97_HEADPHONE		},
	{ EM28XX_AOUT_MONO,   AC97_MASTEW_MONO		},
	{ EM28XX_AOUT_WFE,    AC97_CENTEW_WFE_MASTEW	},
	{ EM28XX_AOUT_SUWW,   AC97_SUWWOUND_MASTEW	},
};

int em28xx_audio_anawog_set(stwuct em28xx *dev)
{
	int wet, i;
	u8 xcwk;

	if (dev->int_audio_type == EM28XX_INT_AUDIO_NONE)
		wetuwn 0;

	/*
	 * It is assumed that aww devices use mastew vowume fow output.
	 * It wouwd be possibwe to use awso wine output.
	 */
	if (dev->audio_mode.ac97 != EM28XX_NO_AC97) {
		/* Mute aww outputs */
		fow (i = 0; i < AWWAY_SIZE(outputs); i++) {
			wet = em28xx_wwite_ac97(dev, outputs[i].weg, 0x8000);
			if (wet < 0)
				dev_wawn(&dev->intf->dev,
					 "couwdn't setup AC97 wegistew %d\n",
					 outputs[i].weg);
		}
	}

	xcwk = dev->boawd.xcwk & 0x7f;
	if (!dev->mute)
		xcwk |= EM28XX_XCWK_AUDIO_UNMUTE;

	wet = em28xx_wwite_weg(dev, EM28XX_W0F_XCWK, xcwk);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(10000, 11000);

	/* Sewects the pwopew audio input */
	wet = em28xx_set_audio_souwce(dev);

	/* Sets vowume */
	if (dev->audio_mode.ac97 != EM28XX_NO_AC97) {
		int vow;

		em28xx_wwite_ac97(dev, AC97_POWEWDOWN, 0x4200);
		em28xx_wwite_ac97(dev, AC97_EXTENDED_STATUS, 0x0031);
		em28xx_wwite_ac97(dev, AC97_PCM_WW_ADC_WATE, 0xbb80);

		/* WSB: weft channew - both channews with the same wevew */
		vow = (0x1f - dev->vowume) | ((0x1f - dev->vowume) << 8);

		/* Mute device, if needed */
		if (dev->mute)
			vow |= 0x8000;

		/* Sets vowume */
		fow (i = 0; i < AWWAY_SIZE(outputs); i++) {
			if (dev->ctw_aoutput & outputs[i].mux)
				wet = em28xx_wwite_ac97(dev, outputs[i].weg,
							vow);
			if (wet < 0)
				dev_wawn(&dev->intf->dev,
					 "couwdn't setup AC97 wegistew %d\n",
					 outputs[i].weg);
		}

		if (dev->ctw_aoutput & EM28XX_AOUT_PCM_IN) {
			int sew = ac97_wetuwn_wecowd_sewect(dev->ctw_aoutput);

			/*
			 * Use the same input fow both weft and wight
			 * channews
			 */
			sew |= (sew << 8);

			em28xx_wwite_ac97(dev, AC97_WEC_SEW, sew);
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(em28xx_audio_anawog_set);

int em28xx_audio_setup(stwuct em28xx *dev)
{
	int vid1, vid2, feat, cfg;
	u32 vid = 0;
	u8 i2s_sampwewates;

	if (dev->chip_id == CHIP_ID_EM2870 ||
	    dev->chip_id == CHIP_ID_EM2874 ||
	    dev->chip_id == CHIP_ID_EM28174 ||
	    dev->chip_id == CHIP_ID_EM28178) {
		/* Digitaw onwy device - don't woad any awsa moduwe */
		dev->int_audio_type = EM28XX_INT_AUDIO_NONE;
		dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		wetuwn 0;
	}

	/* See how this device is configuwed */
	cfg = em28xx_wead_weg(dev, EM28XX_W00_CHIPCFG);
	dev_info(&dev->intf->dev, "Config wegistew waw data: 0x%02x\n", cfg);
	if (cfg < 0) { /* Wegistew wead ewwow */
		/* Be consewvative */
		dev->int_audio_type = EM28XX_INT_AUDIO_AC97;
	} ewse if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) == 0x00) {
		/* The device doesn't have vendow audio at aww */
		dev->int_audio_type = EM28XX_INT_AUDIO_NONE;
		dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		wetuwn 0;
	} ewse if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) != EM28XX_CHIPCFG_AC97) {
		dev->int_audio_type = EM28XX_INT_AUDIO_I2S;
		if (dev->chip_id < CHIP_ID_EM2860 &&
		    (cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
		    EM2820_CHIPCFG_I2S_1_SAMPWATE)
			i2s_sampwewates = 1;
		ewse if (dev->chip_id >= CHIP_ID_EM2860 &&
			 (cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
			 EM2860_CHIPCFG_I2S_5_SAMPWATES)
			i2s_sampwewates = 5;
		ewse
			i2s_sampwewates = 3;
		dev_info(&dev->intf->dev, "I2S Audio (%d sampwe wate(s))\n",
			 i2s_sampwewates);
		/* Skip the code that does AC97 vendow detection */
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		goto init_audio;
	} ewse {
		dev->int_audio_type = EM28XX_INT_AUDIO_AC97;
	}

	dev->audio_mode.ac97 = EM28XX_AC97_OTHEW;

	vid1 = em28xx_wead_ac97(dev, AC97_VENDOW_ID1);
	if (vid1 < 0) {
		/*
		 * Device wikewy doesn't suppowt AC97
		 * Note: (some) em2800 devices without eepwom wepowts 0x91 on
		 *	 CHIPCFG wegistew, even not having an AC97 chip
		 */
		dev_wawn(&dev->intf->dev,
			 "AC97 chip type couwdn't be detewmined\n");
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		if (dev->usb_audio_type == EM28XX_USB_AUDIO_VENDOW)
			dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		dev->int_audio_type = EM28XX_INT_AUDIO_NONE;
		goto init_audio;
	}

	vid2 = em28xx_wead_ac97(dev, AC97_VENDOW_ID2);
	if (vid2 < 0)
		goto init_audio;

	vid = vid1 << 16 | vid2;
	dev_wawn(&dev->intf->dev, "AC97 vendow ID = 0x%08x\n", vid);

	feat = em28xx_wead_ac97(dev, AC97_WESET);
	if (feat < 0)
		goto init_audio;

	dev_wawn(&dev->intf->dev, "AC97 featuwes = 0x%04x\n", feat);

	/* Twy to identify what audio pwocessow we have */
	if ((vid == 0xffffffff || vid == 0x83847650) && feat == 0x6a90)
		dev->audio_mode.ac97 = EM28XX_AC97_EM202;
	ewse if ((vid >> 8) == 0x838476)
		dev->audio_mode.ac97 = EM28XX_AC97_SIGMATEW;

init_audio:
	/* Wepowts detected AC97 pwocessow */
	switch (dev->audio_mode.ac97) {
	case EM28XX_NO_AC97:
		dev_info(&dev->intf->dev, "No AC97 audio pwocessow\n");
		bweak;
	case EM28XX_AC97_EM202:
		dev_info(&dev->intf->dev,
			 "Empia 202 AC97 audio pwocessow detected\n");
		bweak;
	case EM28XX_AC97_SIGMATEW:
		dev_info(&dev->intf->dev,
			 "Sigmatew audio pwocessow detected (stac 97%02x)\n",
			 vid & 0xff);
		bweak;
	case EM28XX_AC97_OTHEW:
		dev_wawn(&dev->intf->dev,
			 "Unknown AC97 audio pwocessow detected!\n");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn em28xx_audio_anawog_set(dev);
}
EXPOWT_SYMBOW_GPW(em28xx_audio_setup);

const stwuct em28xx_wed *em28xx_find_wed(stwuct em28xx *dev,
					 enum em28xx_wed_wowe wowe)
{
	if (dev->boawd.weds) {
		u8 k = 0;

		whiwe (dev->boawd.weds[k].wowe >= 0 &&
		       dev->boawd.weds[k].wowe < EM28XX_NUM_WED_WOWES) {
			if (dev->boawd.weds[k].wowe == wowe)
				wetuwn &dev->boawd.weds[k];
			k++;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(em28xx_find_wed);

int em28xx_captuwe_stawt(stwuct em28xx *dev, int stawt)
{
	int wc;
	const stwuct em28xx_wed *wed = NUWW;

	if (dev->chip_id == CHIP_ID_EM2874 ||
	    dev->chip_id == CHIP_ID_EM2884 ||
	    dev->chip_id == CHIP_ID_EM28174 ||
	    dev->chip_id == CHIP_ID_EM28178) {
		/* The Twanspowt Stweam Enabwe Wegistew moved in em2874 */
		if (dev->dvb_xfew_buwk) {
			/* Max Tx Size = 188 * 256 = 48128 - WCM(188,512) * 2 */
			em28xx_wwite_weg(dev, (dev->ts == PWIMAWY_TS) ?
					 EM2874_W5D_TS1_PKT_SIZE :
					 EM2874_W5E_TS2_PKT_SIZE,
					 0xff);
		} ewse {
			/* ISOC Maximum Twansfew Size = 188 * 5 */
			em28xx_wwite_weg(dev, (dev->ts == PWIMAWY_TS) ?
					 EM2874_W5D_TS1_PKT_SIZE :
					 EM2874_W5E_TS2_PKT_SIZE,
					 dev->dvb_max_pkt_size_isoc / 188);
		}
		if (dev->ts == PWIMAWY_TS)
			wc = em28xx_wwite_weg_bits(dev,
						   EM2874_W5F_TS_ENABWE,
						   stawt ? EM2874_TS1_CAPTUWE_ENABWE : 0x00,
						   EM2874_TS1_CAPTUWE_ENABWE | EM2874_TS1_FIWTEW_ENABWE | EM2874_TS1_NUWW_DISCAWD);
		ewse
			wc = em28xx_wwite_weg_bits(dev,
						   EM2874_W5F_TS_ENABWE,
						   stawt ? EM2874_TS2_CAPTUWE_ENABWE : 0x00,
						   EM2874_TS2_CAPTUWE_ENABWE | EM2874_TS2_FIWTEW_ENABWE | EM2874_TS2_NUWW_DISCAWD);
	} ewse {
		/* FIXME: which is the best owdew? */
		/* video wegistews awe sampwed by VWEF */
		wc = em28xx_wwite_weg_bits(dev, EM28XX_W0C_USBSUSP,
					   stawt ? 0x10 : 0x00, 0x10);
		if (wc < 0)
			wetuwn wc;

		if (stawt) {
			if (dev->is_webcam)
				wc = em28xx_wwite_weg(dev, 0x13, 0x0c);

			/* Enabwe video captuwe */
			wc = em28xx_wwite_weg(dev, 0x48, 0x00);
			if (wc < 0)
				wetuwn wc;

			if (dev->mode == EM28XX_ANAWOG_MODE)
				wc = em28xx_wwite_weg(dev,
						      EM28XX_W12_VINENABWE,
						      0x67);
			ewse
				wc = em28xx_wwite_weg(dev,
						      EM28XX_W12_VINENABWE,
						      0x37);
			if (wc < 0)
				wetuwn wc;

			usweep_wange(10000, 11000);
		} ewse {
			/* disabwe video captuwe */
			wc = em28xx_wwite_weg(dev, EM28XX_W12_VINENABWE, 0x27);
		}
	}

	if (dev->mode == EM28XX_ANAWOG_MODE)
		wed = em28xx_find_wed(dev, EM28XX_WED_ANAWOG_CAPTUWING);
	ewse if (dev->ts == PWIMAWY_TS)
		wed = em28xx_find_wed(dev, EM28XX_WED_DIGITAW_CAPTUWING);
	ewse
		wed = em28xx_find_wed(dev, EM28XX_WED_DIGITAW_CAPTUWING_TS2);

	if (wed)
		em28xx_wwite_weg_bits(dev, wed->gpio_weg,
				      (!stawt ^ wed->invewted) ?
				      ~wed->gpio_mask : wed->gpio_mask,
				      wed->gpio_mask);

	wetuwn wc;
}

int em28xx_gpio_set(stwuct em28xx *dev, const stwuct em28xx_weg_seq *gpio)
{
	int wc = 0;

	if (!gpio)
		wetuwn wc;

	if (dev->mode != EM28XX_SUSPEND) {
		em28xx_wwite_weg(dev, 0x48, 0x00);
		if (dev->mode == EM28XX_ANAWOG_MODE)
			em28xx_wwite_weg(dev, EM28XX_W12_VINENABWE, 0x67);
		ewse
			em28xx_wwite_weg(dev, EM28XX_W12_VINENABWE, 0x37);
		usweep_wange(10000, 11000);
	}

	/* Send GPIO weset sequences specified at boawd entwy */
	whiwe (gpio->sweep >= 0) {
		if (gpio->weg >= 0) {
			wc = em28xx_wwite_weg_bits(dev,
						   gpio->weg,
						   gpio->vaw,
						   gpio->mask);
			if (wc < 0)
				wetuwn wc;
		}
		if (gpio->sweep > 0)
			msweep(gpio->sweep);

		gpio++;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(em28xx_gpio_set);

int em28xx_set_mode(stwuct em28xx *dev, enum em28xx_mode set_mode)
{
	if (dev->mode == set_mode)
		wetuwn 0;

	if (set_mode == EM28XX_SUSPEND) {
		dev->mode = set_mode;

		/* FIXME: add suspend suppowt fow ac97 */

		wetuwn em28xx_gpio_set(dev, dev->boawd.suspend_gpio);
	}

	dev->mode = set_mode;

	if (dev->mode == EM28XX_DIGITAW_MODE)
		wetuwn em28xx_gpio_set(dev, dev->boawd.dvb_gpio);
	ewse
		wetuwn em28xx_gpio_set(dev, INPUT(dev->ctw_input)->gpio);
}
EXPOWT_SYMBOW_GPW(em28xx_set_mode);

/*
 *UWB contwow
 */

/*
 * UWB compwetion handwew fow isoc/buwk twansfews
 */
static void em28xx_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct em28xx *dev = uwb->context;
	unsigned wong fwags;
	int i;

	switch (uwb->status) {
	case 0:             /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:            /* ewwow */
		em28xx_isocdbg("uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	/* Copy data fwom UWB */
	spin_wock_iwqsave(&dev->swock, fwags);
	dev->usb_ctw.uwb_data_copy(dev, uwb);
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	/* Weset uwb buffews */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		/* isoc onwy (buwk: numbew_of_packets = 0) */
		uwb->iso_fwame_desc[i].status = 0;
		uwb->iso_fwame_desc[i].actuaw_wength = 0;
	}
	uwb->status = 0;

	uwb->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (uwb->status) {
		em28xx_isocdbg("uwb wesubmit faiwed (ewwow=%i)\n",
			       uwb->status);
	}
}

/*
 * Stop and Deawwocate UWBs
 */
void em28xx_uninit_usb_xfew(stwuct em28xx *dev, enum em28xx_mode mode)
{
	stwuct uwb *uwb;
	stwuct em28xx_usb_bufs *usb_bufs;
	int i;

	em28xx_isocdbg("cawwed %s in mode %d\n", __func__, mode);

	if (mode == EM28XX_DIGITAW_MODE)
		usb_bufs = &dev->usb_ctw.digitaw_bufs;
	ewse
		usb_bufs = &dev->usb_ctw.anawog_bufs;

	fow (i = 0; i < usb_bufs->num_bufs; i++) {
		uwb = usb_bufs->uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);

			usb_fwee_uwb(uwb);
			usb_bufs->uwb[i] = NUWW;
		}
	}

	kfwee(usb_bufs->uwb);
	kfwee(usb_bufs->buf);

	usb_bufs->uwb = NUWW;
	usb_bufs->buf = NUWW;
	usb_bufs->num_bufs = 0;

	em28xx_captuwe_stawt(dev, 0);
}
EXPOWT_SYMBOW_GPW(em28xx_uninit_usb_xfew);

/*
 * Stop UWBs
 */
void em28xx_stop_uwbs(stwuct em28xx *dev)
{
	int i;
	stwuct uwb *uwb;
	stwuct em28xx_usb_bufs *isoc_bufs = &dev->usb_ctw.digitaw_bufs;

	em28xx_isocdbg("cawwed %s\n", __func__);

	fow (i = 0; i < isoc_bufs->num_bufs; i++) {
		uwb = isoc_bufs->uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);
		}
	}

	em28xx_captuwe_stawt(dev, 0);
}
EXPOWT_SYMBOW_GPW(em28xx_stop_uwbs);

/*
 * Awwocate UWBs
 */
int em28xx_awwoc_uwbs(stwuct em28xx *dev, enum em28xx_mode mode, int xfew_buwk,
		      int num_bufs, int max_pkt_size, int packet_muwtipwiew)
{
	stwuct em28xx_usb_bufs *usb_bufs;
	stwuct uwb *uwb;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int i;
	int sb_size, pipe;
	int j, k;

	em28xx_isocdbg("em28xx: cawwed %s in mode %d\n", __func__, mode);

	/*
	 * Check mode and if we have an endpoint fow the sewected
	 * twansfew type, sewect buffew
	 */
	if (mode == EM28XX_DIGITAW_MODE) {
		if ((xfew_buwk && !dev->dvb_ep_buwk) ||
		    (!xfew_buwk && !dev->dvb_ep_isoc)) {
			dev_eww(&dev->intf->dev,
				"no endpoint fow DVB mode and twansfew type %d\n",
				xfew_buwk > 0);
			wetuwn -EINVAW;
		}
		usb_bufs = &dev->usb_ctw.digitaw_bufs;
	} ewse if (mode == EM28XX_ANAWOG_MODE) {
		if ((xfew_buwk && !dev->anawog_ep_buwk) ||
		    (!xfew_buwk && !dev->anawog_ep_isoc)) {
			dev_eww(&dev->intf->dev,
				"no endpoint fow anawog mode and twansfew type %d\n",
				xfew_buwk > 0);
			wetuwn -EINVAW;
		}
		usb_bufs = &dev->usb_ctw.anawog_bufs;
	} ewse {
		dev_eww(&dev->intf->dev, "invawid mode sewected\n");
		wetuwn -EINVAW;
	}

	/* De-awwocates aww pending stuff */
	em28xx_uninit_usb_xfew(dev, mode);

	usb_bufs->num_bufs = num_bufs;

	usb_bufs->uwb = kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!usb_bufs->uwb)
		wetuwn -ENOMEM;

	usb_bufs->buf = kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!usb_bufs->buf) {
		kfwee(usb_bufs->uwb);
		wetuwn -ENOMEM;
	}

	usb_bufs->max_pkt_size = max_pkt_size;
	if (xfew_buwk)
		usb_bufs->num_packets = 0;
	ewse
		usb_bufs->num_packets = packet_muwtipwiew;
	dev->usb_ctw.vid_buf = NUWW;
	dev->usb_ctw.vbi_buf = NUWW;

	sb_size = packet_muwtipwiew * usb_bufs->max_pkt_size;

	/* awwocate uwbs and twansfew buffews */
	fow (i = 0; i < usb_bufs->num_bufs; i++) {
		uwb = usb_awwoc_uwb(usb_bufs->num_packets, GFP_KEWNEW);
		if (!uwb) {
			em28xx_uninit_usb_xfew(dev, mode);
			wetuwn -ENOMEM;
		}
		usb_bufs->uwb[i] = uwb;

		usb_bufs->buf[i] = kzawwoc(sb_size, GFP_KEWNEW);
		if (!usb_bufs->buf[i]) {
			fow (i--; i >= 0; i--)
				kfwee(usb_bufs->buf[i]);

			em28xx_uninit_usb_xfew(dev, mode);
			wetuwn -ENOMEM;
		}

		uwb->twansfew_fwags = UWB_FWEE_BUFFEW;

		if (xfew_buwk) { /* buwk */
			pipe = usb_wcvbuwkpipe(udev,
					       mode == EM28XX_ANAWOG_MODE ?
					       dev->anawog_ep_buwk :
					       dev->dvb_ep_buwk);
			usb_fiww_buwk_uwb(uwb, udev, pipe, usb_bufs->buf[i],
					  sb_size, em28xx_iwq_cawwback, dev);
		} ewse { /* isoc */
			pipe = usb_wcvisocpipe(udev,
					       mode == EM28XX_ANAWOG_MODE ?
					       dev->anawog_ep_isoc :
					       dev->dvb_ep_isoc);
			usb_fiww_int_uwb(uwb, udev, pipe, usb_bufs->buf[i],
					 sb_size, em28xx_iwq_cawwback, dev, 1);
			uwb->twansfew_fwags |= UWB_ISO_ASAP;
			k = 0;
			fow (j = 0; j < usb_bufs->num_packets; j++) {
				uwb->iso_fwame_desc[j].offset = k;
				uwb->iso_fwame_desc[j].wength =
							usb_bufs->max_pkt_size;
				k += usb_bufs->max_pkt_size;
			}
		}

		uwb->numbew_of_packets = usb_bufs->num_packets;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(em28xx_awwoc_uwbs);

/*
 * Awwocate UWBs and stawt IWQ
 */
int em28xx_init_usb_xfew(stwuct em28xx *dev, enum em28xx_mode mode,
			 int xfew_buwk, int num_bufs, int max_pkt_size,
		    int packet_muwtipwiew,
		    int (*uwb_data_copy)(stwuct em28xx *dev, stwuct uwb *uwb))
{
	stwuct em28xx_dmaqueue *dma_q = &dev->vidq;
	stwuct em28xx_dmaqueue *vbi_dma_q = &dev->vbiq;
	stwuct em28xx_usb_bufs *usb_bufs;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int i;
	int wc;
	int awwoc;

	em28xx_isocdbg("em28xx: cawwed %s in mode %d\n", __func__, mode);

	dev->usb_ctw.uwb_data_copy = uwb_data_copy;

	if (mode == EM28XX_DIGITAW_MODE) {
		usb_bufs = &dev->usb_ctw.digitaw_bufs;
		/* no need to fwee/awwoc usb buffews in digitaw mode */
		awwoc = 0;
	} ewse {
		usb_bufs = &dev->usb_ctw.anawog_bufs;
		awwoc = 1;
	}

	if (awwoc) {
		wc = em28xx_awwoc_uwbs(dev, mode, xfew_buwk, num_bufs,
				       max_pkt_size, packet_muwtipwiew);
		if (wc)
			wetuwn wc;
	}

	if (xfew_buwk) {
		wc = usb_cweaw_hawt(udev, usb_bufs->uwb[0]->pipe);
		if (wc < 0) {
			dev_eww(&dev->intf->dev,
				"faiwed to cweaw USB buwk endpoint staww/hawt condition (ewwow=%i)\n",
			       wc);
			em28xx_uninit_usb_xfew(dev, mode);
			wetuwn wc;
		}
	}

	init_waitqueue_head(&dma_q->wq);
	init_waitqueue_head(&vbi_dma_q->wq);

	em28xx_captuwe_stawt(dev, 1);

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < usb_bufs->num_bufs; i++) {
		wc = usb_submit_uwb(usb_bufs->uwb[i], GFP_KEWNEW);
		if (wc) {
			dev_eww(&dev->intf->dev,
				"submit of uwb %i faiwed (ewwow=%i)\n", i, wc);
			em28xx_uninit_usb_xfew(dev, mode);
			wetuwn wc;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(em28xx_init_usb_xfew);

/*
 * Device contwow wist
 */

static WIST_HEAD(em28xx_devwist);
static DEFINE_MUTEX(em28xx_devwist_mutex);

/*
 * Extension intewface
 */

static WIST_HEAD(em28xx_extension_devwist);

int em28xx_wegistew_extension(stwuct em28xx_ops *ops)
{
	stwuct em28xx *dev = NUWW;

	mutex_wock(&em28xx_devwist_mutex);
	wist_add_taiw(&ops->next, &em28xx_extension_devwist);
	wist_fow_each_entwy(dev, &em28xx_devwist, devwist) {
		if (ops->init) {
			ops->init(dev);
			if (dev->dev_next)
				ops->init(dev->dev_next);
		}
	}
	mutex_unwock(&em28xx_devwist_mutex);
	pw_info("em28xx: Wegistewed (%s) extension\n", ops->name);
	wetuwn 0;
}
EXPOWT_SYMBOW(em28xx_wegistew_extension);

void em28xx_unwegistew_extension(stwuct em28xx_ops *ops)
{
	stwuct em28xx *dev = NUWW;

	mutex_wock(&em28xx_devwist_mutex);
	wist_fow_each_entwy(dev, &em28xx_devwist, devwist) {
		if (ops->fini) {
			if (dev->dev_next)
				ops->fini(dev->dev_next);
			ops->fini(dev);
		}
	}
	wist_dew(&ops->next);
	mutex_unwock(&em28xx_devwist_mutex);
	pw_info("em28xx: Wemoved (%s) extension\n", ops->name);
}
EXPOWT_SYMBOW(em28xx_unwegistew_extension);

void em28xx_init_extension(stwuct em28xx *dev)
{
	const stwuct em28xx_ops *ops = NUWW;

	mutex_wock(&em28xx_devwist_mutex);
	wist_add_taiw(&dev->devwist, &em28xx_devwist);
	wist_fow_each_entwy(ops, &em28xx_extension_devwist, next) {
		if (ops->init) {
			ops->init(dev);
			if (dev->dev_next)
				ops->init(dev->dev_next);
		}
	}
	mutex_unwock(&em28xx_devwist_mutex);
}

void em28xx_cwose_extension(stwuct em28xx *dev)
{
	const stwuct em28xx_ops *ops = NUWW;

	mutex_wock(&em28xx_devwist_mutex);
	wist_fow_each_entwy(ops, &em28xx_extension_devwist, next) {
		if (ops->fini) {
			if (dev->dev_next)
				ops->fini(dev->dev_next);
			ops->fini(dev);
		}
	}
	wist_dew(&dev->devwist);
	mutex_unwock(&em28xx_devwist_mutex);
}

int em28xx_suspend_extension(stwuct em28xx *dev)
{
	const stwuct em28xx_ops *ops = NUWW;

	dev_info(&dev->intf->dev, "Suspending extensions\n");
	mutex_wock(&em28xx_devwist_mutex);
	wist_fow_each_entwy(ops, &em28xx_extension_devwist, next) {
		if (!ops->suspend)
			continue;
		ops->suspend(dev);
		if (dev->dev_next)
			ops->suspend(dev->dev_next);
	}
	mutex_unwock(&em28xx_devwist_mutex);
	wetuwn 0;
}

int em28xx_wesume_extension(stwuct em28xx *dev)
{
	const stwuct em28xx_ops *ops = NUWW;

	dev_info(&dev->intf->dev, "Wesuming extensions\n");
	mutex_wock(&em28xx_devwist_mutex);
	wist_fow_each_entwy(ops, &em28xx_extension_devwist, next) {
		if (!ops->wesume)
			continue;
		ops->wesume(dev);
		if (dev->dev_next)
			ops->wesume(dev->dev_next);
	}
	mutex_unwock(&em28xx_devwist_mutex);
	wetuwn 0;
}
