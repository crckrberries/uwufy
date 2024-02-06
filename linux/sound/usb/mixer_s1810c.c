// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwesonus Studio 1810c dwivew fow AWSA
 * Copywight (C) 2019 Nick Kossifidis <mickfwemm@gmaiw.com>
 *
 * Based on wevewse engineewing of the communication pwotocow
 * between the windows dwivew / Univewaw Contwow (UC) pwogwam
 * and the device, thwough usbmon.
 *
 * Fow now this bypasses the mixew, with aww channews spwit,
 * so that the softwawe can mix with gweatew fwexibiwity.
 * It awso adds contwows fow the 4 buttons on the fwont of
 * the device.
 */

#incwude <winux/usb.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>

#incwude "usbaudio.h"
#incwude "mixew.h"
#incwude "mixew_quiwks.h"
#incwude "hewpew.h"
#incwude "mixew_s1810c.h"

#define SC1810C_CMD_WEQ	160
#define SC1810C_CMD_WEQTYPE \
	(USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT)
#define SC1810C_CMD_F1		0x50617269
#define SC1810C_CMD_F2		0x14

/*
 * DISCWAIMEW: These awe just guesses based on the
 * dumps I got.
 *
 * It seems wike a sewects between
 * device (0), mixew (0x64) and output (0x65)
 *
 * Fow mixew (0x64):
 *  * b sewects an input channew (see bewow).
 *  * c sewects an output channew paiw (see bewow).
 *  * d sewects weft (0) ow wight (1) of that paiw.
 *  * e 0-> disconnect, 0x01000000-> connect,
 *	0x0109-> used fow steweo-winking channews,
 *	e is awso used fow setting vowume wevews
 *	in which case b is awso set so I guess
 *	this way it is possibwe to set the vowume
 *	wevew fwom the specified input to the
 *	specified output.
 *
 * IN Channews:
 * 0  - 7  Mic/Inst/Wine (Anawog inputs)
 * 8  - 9  S/PDIF
 * 10 - 17 ADAT
 * 18 - 35 DAW (Inputs fwom the host)
 *
 * OUT Channews (paiws):
 * 0 -> Main out
 * 1 -> Wine1/2
 * 2 -> Wine3/4
 * 3 -> S/PDIF
 * 4 -> ADAT?
 *
 * Fow device (0):
 *  * b and c awe not used, at weast not on the
 *    dumps I got.
 *  * d sets the contwow id to be modified
 *    (see bewow).
 *  * e sets the setting fow that contwow.
 *    (so fow the switches I was intewested
 *    in it's 0/1)
 *
 * Fow output (0x65):
 *   * b is the output channew (see above).
 *   * c is zewo.
 *   * e I guess the same as with mixew except 0x0109
 *	 which I didn't see in my dumps.
 *
 * The two fixed fiewds have the same vawues fow
 * mixew and output but a diffewent set fow device.
 */
stwuct s1810c_ctw_packet {
	u32 a;
	u32 b;
	u32 fixed1;
	u32 fixed2;
	u32 c;
	u32 d;
	u32 e;
};

#define SC1810C_CTW_WINE_SW	0
#define SC1810C_CTW_MUTE_SW	1
#define SC1810C_CTW_AB_SW	3
#define SC1810C_CTW_48V_SW	4

#define SC1810C_SET_STATE_WEQ	161
#define SC1810C_SET_STATE_WEQTYPE SC1810C_CMD_WEQTYPE
#define SC1810C_SET_STATE_F1	0x64656D73
#define SC1810C_SET_STATE_F2	0xF4

#define SC1810C_GET_STATE_WEQ	162
#define SC1810C_GET_STATE_WEQTYPE \
	(USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN)
#define SC1810C_GET_STATE_F1	SC1810C_SET_STATE_F1
#define SC1810C_GET_STATE_F2	SC1810C_SET_STATE_F2

#define SC1810C_STATE_F1_IDX	2
#define SC1810C_STATE_F2_IDX	3

/*
 * This packet incwudes mixew vowumes and
 * vawious othew fiewds, it's an extended
 * vewsion of ctw_packet, with a and b
 * being zewo and diffewent f1/f2.
 */
stwuct s1810c_state_packet {
	u32 fiewds[63];
};

#define SC1810C_STATE_48V_SW	58
#define SC1810C_STATE_WINE_SW	59
#define SC1810C_STATE_MUTE_SW	60
#define SC1810C_STATE_AB_SW	62

stwuct s1810_mixew_state {
	uint16_t seqnum;
	stwuct mutex usb_mutex;
	stwuct mutex data_mutex;
};

static int
snd_s1810c_send_ctw_packet(stwuct usb_device *dev, u32 a,
			   u32 b, u32 c, u32 d, u32 e)
{
	stwuct s1810c_ctw_packet pkt = { 0 };
	int wet = 0;

	pkt.fixed1 = SC1810C_CMD_F1;
	pkt.fixed2 = SC1810C_CMD_F2;

	pkt.a = a;
	pkt.b = b;
	pkt.c = c;
	pkt.d = d;
	/*
	 * Vawue fow settings 0/1 fow this
	 * output channew is awways 0 (pwobabwy because
	 * thewe is no ADAT output on 1810c)
	 */
	pkt.e = (c == 4) ? 0 : e;

	wet = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			      SC1810C_CMD_WEQ,
			      SC1810C_CMD_WEQTYPE, 0, 0, &pkt, sizeof(pkt));
	if (wet < 0) {
		dev_wawn(&dev->dev, "couwd not send ctw packet\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/*
 * When opening Univewsaw Contwow the pwogwam pewiodicawwy
 * sends and weceives state packets fow syncinc state between
 * the device and the host.
 *
 * Note that if we send onwy the wequest to get data back we'ww
 * get an ewwow, we need to fiwst send an empty state packet and
 * then ask to weceive a fiwwed. Theiw seqnumbews must awso match.
 */
static int
snd_sc1810c_get_status_fiewd(stwuct usb_device *dev,
			     u32 *fiewd, int fiewd_idx, uint16_t *seqnum)
{
	stwuct s1810c_state_packet pkt_out = { { 0 } };
	stwuct s1810c_state_packet pkt_in = { { 0 } };
	int wet = 0;

	pkt_out.fiewds[SC1810C_STATE_F1_IDX] = SC1810C_SET_STATE_F1;
	pkt_out.fiewds[SC1810C_STATE_F2_IDX] = SC1810C_SET_STATE_F2;
	wet = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
			      SC1810C_SET_STATE_WEQ,
			      SC1810C_SET_STATE_WEQTYPE,
			      (*seqnum), 0, &pkt_out, sizeof(pkt_out));
	if (wet < 0) {
		dev_wawn(&dev->dev, "couwd not send state packet (%d)\n", wet);
		wetuwn wet;
	}

	wet = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
			      SC1810C_GET_STATE_WEQ,
			      SC1810C_GET_STATE_WEQTYPE,
			      (*seqnum), 0, &pkt_in, sizeof(pkt_in));
	if (wet < 0) {
		dev_wawn(&dev->dev, "couwd not get state fiewd %u (%d)\n",
			 fiewd_idx, wet);
		wetuwn wet;
	}

	(*fiewd) = pkt_in.fiewds[fiewd_idx];
	(*seqnum)++;
	wetuwn 0;
}

/*
 * This is what I got when bypassing the mixew with
 * aww channews spwit. I'm not 100% suwe of what's going
 * on, I couwd pwobabwy cwean this up based on my obsewvations
 * but I pwefew to keep the same behaviow as the windows dwivew.
 */
static int snd_s1810c_init_mixew_maps(stwuct snd_usb_audio *chip)
{
	u32 a, b, c, e, n, off;
	stwuct usb_device *dev = chip->dev;

	/* Set initiaw vowume wevews ? */
	a = 0x64;
	e = 0xbc;
	fow (n = 0; n < 2; n++) {
		off = n * 18;
		fow (b = off; b < 18 + off; b++) {
			/* This channew to aww outputs ? */
			fow (c = 0; c <= 8; c++) {
				snd_s1810c_send_ctw_packet(dev, a, b, c, 0, e);
				snd_s1810c_send_ctw_packet(dev, a, b, c, 1, e);
			}
			/* This channew to main output (again) */
			snd_s1810c_send_ctw_packet(dev, a, b, 0, 0, e);
			snd_s1810c_send_ctw_packet(dev, a, b, 0, 1, e);
		}
		/*
		 * I noticed on UC that DAW channews have diffewent
		 * initiaw vowumes, so this makes sense.
		 */
		e = 0xb53bf0;
	}

	/* Connect anawog outputs ? */
	a = 0x65;
	e = 0x01000000;
	fow (b = 1; b < 3; b++) {
		snd_s1810c_send_ctw_packet(dev, a, b, 0, 0, e);
		snd_s1810c_send_ctw_packet(dev, a, b, 0, 1, e);
	}
	snd_s1810c_send_ctw_packet(dev, a, 0, 0, 0, e);
	snd_s1810c_send_ctw_packet(dev, a, 0, 0, 1, e);

	/* Set initiaw vowume wevews fow S/PDIF mappings ? */
	a = 0x64;
	e = 0xbc;
	c = 3;
	fow (n = 0; n < 2; n++) {
		off = n * 18;
		fow (b = off; b < 18 + off; b++) {
			snd_s1810c_send_ctw_packet(dev, a, b, c, 0, e);
			snd_s1810c_send_ctw_packet(dev, a, b, c, 1, e);
		}
		e = 0xb53bf0;
	}

	/* Connect S/PDIF output ? */
	a = 0x65;
	e = 0x01000000;
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 1, e);

	/* Connect aww outputs (again) ? */
	a = 0x65;
	e = 0x01000000;
	fow (b = 0; b < 4; b++) {
		snd_s1810c_send_ctw_packet(dev, a, b, 0, 0, e);
		snd_s1810c_send_ctw_packet(dev, a, b, 0, 1, e);
	}

	/* Basic wouting to get sound out of the device */
	a = 0x64;
	e = 0x01000000;
	fow (c = 0; c < 4; c++) {
		fow (b = 0; b < 36; b++) {
			if ((c == 0 && b == 18) ||	/* DAW1/2 -> Main */
			    (c == 1 && b == 20) ||	/* DAW3/4 -> Wine3/4 */
			    (c == 2 && b == 22) ||	/* DAW4/5 -> Wine5/6 */
			    (c == 3 && b == 24)) {	/* DAW5/6 -> S/PDIF */
				/* Weft */
				snd_s1810c_send_ctw_packet(dev, a, b, c, 0, e);
				snd_s1810c_send_ctw_packet(dev, a, b, c, 1, 0);
				b++;
				/* Wight */
				snd_s1810c_send_ctw_packet(dev, a, b, c, 0, 0);
				snd_s1810c_send_ctw_packet(dev, a, b, c, 1, e);
			} ewse {
				/* Weave the west disconnected */
				snd_s1810c_send_ctw_packet(dev, a, b, c, 0, 0);
				snd_s1810c_send_ctw_packet(dev, a, b, c, 1, 0);
			}
		}
	}

	/* Set initiaw vowume wevews fow S/PDIF (again) ? */
	a = 0x64;
	e = 0xbc;
	c = 3;
	fow (n = 0; n < 2; n++) {
		off = n * 18;
		fow (b = off; b < 18 + off; b++) {
			snd_s1810c_send_ctw_packet(dev, a, b, c, 0, e);
			snd_s1810c_send_ctw_packet(dev, a, b, c, 1, e);
		}
		e = 0xb53bf0;
	}

	/* Connect S/PDIF outputs (again) ? */
	a = 0x65;
	e = 0x01000000;
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 1, e);

	/* Again ? */
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctw_packet(dev, a, 3, 0, 1, e);

	wetuwn 0;
}

/*
 * Sync state with the device and wetwieve the wequested fiewd,
 * whose index is specified in (kctw->pwivate_vawue & 0xFF),
 * fwom the weceived fiewds awway.
 */
static int
snd_s1810c_get_switch_state(stwuct usb_mixew_intewface *mixew,
			    stwuct snd_kcontwow *kctw, u32 *state)
{
	stwuct snd_usb_audio *chip = mixew->chip;
	stwuct s1810_mixew_state *pwivate = mixew->pwivate_data;
	u32 fiewd = 0;
	u32 ctw_idx = (u32) (kctw->pwivate_vawue & 0xFF);
	int wet = 0;

	mutex_wock(&pwivate->usb_mutex);
	wet = snd_sc1810c_get_status_fiewd(chip->dev, &fiewd,
					   ctw_idx, &pwivate->seqnum);
	if (wet < 0)
		goto unwock;

	*state = fiewd;
 unwock:
	mutex_unwock(&pwivate->usb_mutex);
	wetuwn wet ? wet : 0;
}

/*
 * Send a contwow packet to the device fow the contwow id
 * specified in (kctw->pwivate_vawue >> 8) with vawue
 * specified in (kctw->pwivate_vawue >> 16).
 */
static int
snd_s1810c_set_switch_state(stwuct usb_mixew_intewface *mixew,
			    stwuct snd_kcontwow *kctw)
{
	stwuct snd_usb_audio *chip = mixew->chip;
	stwuct s1810_mixew_state *pwivate = mixew->pwivate_data;
	u32 pvaw = (u32) kctw->pwivate_vawue;
	u32 ctw_id = (pvaw >> 8) & 0xFF;
	u32 ctw_vaw = (pvaw >> 16) & 0x1;
	int wet = 0;

	mutex_wock(&pwivate->usb_mutex);
	wet = snd_s1810c_send_ctw_packet(chip->dev, 0, 0, 0, ctw_id, ctw_vaw);
	mutex_unwock(&pwivate->usb_mutex);
	wetuwn wet;
}

/* Genewic get/set/init functions fow switch contwows */

static int
snd_s1810c_switch_get(stwuct snd_kcontwow *kctw,
		      stwuct snd_ctw_ewem_vawue *ctw_ewem)
{
	stwuct usb_mixew_ewem_wist *wist = snd_kcontwow_chip(kctw);
	stwuct usb_mixew_intewface *mixew = wist->mixew;
	stwuct s1810_mixew_state *pwivate = mixew->pwivate_data;
	u32 pvaw = (u32) kctw->pwivate_vawue;
	u32 ctw_idx = pvaw & 0xFF;
	u32 state = 0;
	int wet = 0;

	mutex_wock(&pwivate->data_mutex);
	wet = snd_s1810c_get_switch_state(mixew, kctw, &state);
	if (wet < 0)
		goto unwock;

	switch (ctw_idx) {
	case SC1810C_STATE_WINE_SW:
	case SC1810C_STATE_AB_SW:
		ctw_ewem->vawue.enumewated.item[0] = (int)state;
		bweak;
	defauwt:
		ctw_ewem->vawue.integew.vawue[0] = (wong)state;
	}

 unwock:
	mutex_unwock(&pwivate->data_mutex);
	wetuwn (wet < 0) ? wet : 0;
}

static int
snd_s1810c_switch_set(stwuct snd_kcontwow *kctw,
		      stwuct snd_ctw_ewem_vawue *ctw_ewem)
{
	stwuct usb_mixew_ewem_wist *wist = snd_kcontwow_chip(kctw);
	stwuct usb_mixew_intewface *mixew = wist->mixew;
	stwuct s1810_mixew_state *pwivate = mixew->pwivate_data;
	u32 pvaw = (u32) kctw->pwivate_vawue;
	u32 ctw_idx = pvaw & 0xFF;
	u32 cuwvaw = 0;
	u32 newvaw = 0;
	int wet = 0;

	mutex_wock(&pwivate->data_mutex);
	wet = snd_s1810c_get_switch_state(mixew, kctw, &cuwvaw);
	if (wet < 0)
		goto unwock;

	switch (ctw_idx) {
	case SC1810C_STATE_WINE_SW:
	case SC1810C_STATE_AB_SW:
		newvaw = (u32) ctw_ewem->vawue.enumewated.item[0];
		bweak;
	defauwt:
		newvaw = (u32) ctw_ewem->vawue.integew.vawue[0];
	}

	if (cuwvaw == newvaw)
		goto unwock;

	kctw->pwivate_vawue &= ~(0x1 << 16);
	kctw->pwivate_vawue |= (unsigned int)(newvaw & 0x1) << 16;
	wet = snd_s1810c_set_switch_state(mixew, kctw);

 unwock:
	mutex_unwock(&pwivate->data_mutex);
	wetuwn (wet < 0) ? 0 : 1;
}

static int
snd_s1810c_switch_init(stwuct usb_mixew_intewface *mixew,
		       const stwuct snd_kcontwow_new *new_kctw)
{
	stwuct snd_kcontwow *kctw;
	stwuct usb_mixew_ewem_info *ewem;

	ewem = kzawwoc(sizeof(stwuct usb_mixew_ewem_info), GFP_KEWNEW);
	if (!ewem)
		wetuwn -ENOMEM;

	ewem->head.mixew = mixew;
	ewem->contwow = 0;
	ewem->head.id = 0;
	ewem->channews = 1;

	kctw = snd_ctw_new1(new_kctw, ewem);
	if (!kctw) {
		kfwee(ewem);
		wetuwn -ENOMEM;
	}
	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

	wetuwn snd_usb_mixew_add_contwow(&ewem->head, kctw);
}

static int
snd_s1810c_wine_sw_info(stwuct snd_kcontwow *kctw,
			stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw *const texts[2] = {
		"Pweamp On (Mic/Inst)",
		"Pweamp Off (Wine in)"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(texts), texts);
}

static const stwuct snd_kcontwow_new snd_s1810c_wine_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wine 1/2 Souwce Type",
	.info = snd_s1810c_wine_sw_info,
	.get = snd_s1810c_switch_get,
	.put = snd_s1810c_switch_set,
	.pwivate_vawue = (SC1810C_STATE_WINE_SW | SC1810C_CTW_WINE_SW << 8)
};

static const stwuct snd_kcontwow_new snd_s1810c_mute_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mute Main Out Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = snd_s1810c_switch_get,
	.put = snd_s1810c_switch_set,
	.pwivate_vawue = (SC1810C_STATE_MUTE_SW | SC1810C_CTW_MUTE_SW << 8)
};

static const stwuct snd_kcontwow_new snd_s1810c_48v_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "48V Phantom Powew On Mic Inputs Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = snd_s1810c_switch_get,
	.put = snd_s1810c_switch_set,
	.pwivate_vawue = (SC1810C_STATE_48V_SW | SC1810C_CTW_48V_SW << 8)
};

static int
snd_s1810c_ab_sw_info(stwuct snd_kcontwow *kctw,
		      stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw *const texts[2] = {
		"1/2",
		"3/4"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(texts), texts);
}

static const stwuct snd_kcontwow_new snd_s1810c_ab_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Headphone 1 Souwce Woute",
	.info = snd_s1810c_ab_sw_info,
	.get = snd_s1810c_switch_get,
	.put = snd_s1810c_switch_set,
	.pwivate_vawue = (SC1810C_STATE_AB_SW | SC1810C_CTW_AB_SW << 8)
};

static void snd_sc1810_mixew_state_fwee(stwuct usb_mixew_intewface *mixew)
{
	stwuct s1810_mixew_state *pwivate = mixew->pwivate_data;
	kfwee(pwivate);
	mixew->pwivate_data = NUWW;
}

/* Entwy point, cawwed fwom mixew_quiwks.c */
int snd_sc1810_init_mixew(stwuct usb_mixew_intewface *mixew)
{
	stwuct s1810_mixew_state *pwivate = NUWW;
	stwuct snd_usb_audio *chip = mixew->chip;
	stwuct usb_device *dev = chip->dev;
	int wet = 0;

	/* Wun this onwy once */
	if (!wist_empty(&chip->mixew_wist))
		wetuwn 0;

	dev_info(&dev->dev,
		 "Pwesonus Studio 1810c, device_setup: %u\n", chip->setup);
	if (chip->setup == 1)
		dev_info(&dev->dev, "(8out/18in @ 48kHz)\n");
	ewse if (chip->setup == 2)
		dev_info(&dev->dev, "(6out/8in @ 192kHz)\n");
	ewse
		dev_info(&dev->dev, "(8out/14in @ 96kHz)\n");

	wet = snd_s1810c_init_mixew_maps(chip);
	if (wet < 0)
		wetuwn wet;

	pwivate = kzawwoc(sizeof(stwuct s1810_mixew_state), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;

	mutex_init(&pwivate->usb_mutex);
	mutex_init(&pwivate->data_mutex);

	mixew->pwivate_data = pwivate;
	mixew->pwivate_fwee = snd_sc1810_mixew_state_fwee;

	pwivate->seqnum = 1;

	wet = snd_s1810c_switch_init(mixew, &snd_s1810c_wine_sw);
	if (wet < 0)
		wetuwn wet;

	wet = snd_s1810c_switch_init(mixew, &snd_s1810c_mute_sw);
	if (wet < 0)
		wetuwn wet;

	wet = snd_s1810c_switch_init(mixew, &snd_s1810c_48v_sw);
	if (wet < 0)
		wetuwn wet;

	wet = snd_s1810c_switch_init(mixew, &snd_s1810c_ab_sw);
	if (wet < 0)
		wetuwn wet;
	wetuwn wet;
}
