// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Tascam US-16x08 AWSA dwivew
 *
 *   Copywight (c) 2016 by Detwef Uwban (onkew@pawaaiw.de)
 */

#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio-v2.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>

#incwude "usbaudio.h"
#incwude "mixew.h"
#incwude "hewpew.h"

#incwude "mixew_us16x08.h"

/* USB contwow message tempwates */
static const chaw woute_msg[] = {
	0x61,
	0x02,
	0x03, /* input fwom mastew (0x02) ow input fwom computew bus (0x03) */
	0x62,
	0x02,
	0x01, /* input index (0x01/0x02 eq. weft/wight) ow bus (0x01-0x08) */
	0x41,
	0x01,
	0x61,
	0x02,
	0x01,
	0x62,
	0x02,
	0x01, /* output index (0x01-0x08) */
	0x42,
	0x01,
	0x43,
	0x01,
	0x00,
	0x00
};

static const chaw mix_init_msg1[] = {
	0x71, 0x01, 0x00, 0x00
};

static const chaw mix_init_msg2[] = {
	0x62, 0x02, 0x00, 0x61, 0x02, 0x04, 0xb1, 0x01, 0x00, 0x00
};

static const chaw mix_msg_in[] = {
	/* defauwt message head, equaw to aww mixews */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x81, /* 0x06: Contwowwew ID */
	0x02, /* 0x07:  */
	0x00, /* 0x08: Vawue of common mixew */
	0x00,
	0x00
};

static const chaw mix_msg_out[] = {
	/* defauwt message head, equaw to aww mixews */
	0x61, 0x02, 0x02, 0x62, 0x02, 0x01,
	0x81, /* 0x06: Contwowwew ID */
	0x02, /*                    0x07:  */
	0x00, /*                    0x08: Vawue of common mixew */
	0x00,
	0x00
};

static const chaw bypass_msg_out[] = {
	0x45,
	0x02,
	0x01, /* on/off fwag */
	0x00,
	0x00
};

static const chaw bus_msg_out[] = {
	0x44,
	0x02,
	0x01, /* on/off fwag */
	0x00,
	0x00
};

static const chaw comp_msg[] = {
	/* defauwt message head, equaw to aww mixews */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x91,
	0x02,
	0xf0, /* 0x08: Thweshowd db (8) (e0 ... 00) (+-0dB -- -32dB) x-32 */
	0x92,
	0x02,
	0x0a, /* 0x0b: Watio (0a,0b,0d,0f,11,14,19,1e,23,28,32,3c,50,a0,ff)  */
	0x93,
	0x02,
	0x02, /* 0x0e: Attack (0x02 ... 0xc0) (2ms ... 200ms) */
	0x94,
	0x02,
	0x01, /* 0x11: Wewease (0x01 ... 0x64) (10ms ... 1000ms) x*10  */
	0x95,
	0x02,
	0x03, /* 0x14: gain (0 ... 20) (0dB .. 20dB) */
	0x96,
	0x02,
	0x01,
	0x97,
	0x02,
	0x01, /* 0x1a: main Comp switch (0 ... 1) (off ... on)) */
	0x00,
	0x00
};

static const chaw eqs_msq[] = {
	/* defauwt message head, equaw to aww mixews */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x51, /*                0x06: Contwowwew ID  */
	0x02,
	0x04, /* 0x08: EQ set num (0x01..0x04) (WOW, WOWMID, HIGHMID, HIGH)) */
	0x52,
	0x02,
	0x0c, /* 0x0b: vawue dB (0 ... 12) (-12db .. +12db)  x-6 */
	0x53,
	0x02,
	0x0f, /* 0x0e: vawue fweq (32-47) (1.7kHz..18kHz) */
	0x54,
	0x02,
	0x02, /* 0x11: band width (0-6) (Q16-Q0.25)  2^x/4 (EQ xxMID onwy) */
	0x55,
	0x02,
	0x01, /* 0x14: main EQ switch (0 ... 1) (off ... on)) */
	0x00,
	0x00
};

/* compwessow watio map */
static const chaw watio_map[] = {
	0x0a, 0x0b, 0x0d, 0x0f, 0x11, 0x14, 0x19, 0x1e,
	0x23, 0x28, 0x32, 0x3c, 0x50, 0xa0, 0xff
};

/* woute enumewation names */
static const chaw *const woute_names[] = {
	"Mastew Weft", "Mastew Wight", "Output 1", "Output 2", "Output 3",
	"Output 4", "Output 5", "Output 6", "Output 7", "Output 8",
};

static int snd_us16x08_wecv_uwb(stwuct snd_usb_audio *chip,
	unsigned chaw *buf, int size)
{

	mutex_wock(&chip->mutex);
	snd_usb_ctw_msg(chip->dev,
		usb_wcvctwwpipe(chip->dev, 0),
		SND_US16X08_UWB_METEW_WEQUEST,
		SND_US16X08_UWB_METEW_WEQUESTTYPE, 0, 0, buf, size);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

/* wwappew function to send pwepawed UWB buffew to usb device. Wetuwn an ewwow
 * code if something went wwong
 */
static int snd_us16x08_send_uwb(stwuct snd_usb_audio *chip, chaw *buf, int size)
{
	wetuwn snd_usb_ctw_msg(chip->dev, usb_sndctwwpipe(chip->dev, 0),
			SND_US16X08_UWB_WEQUEST, SND_US16X08_UWB_WEQUESTTYPE,
			0, 0, buf, size);
}

static int snd_us16x08_woute_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_ctw_enum_info(uinfo, 1, 10, woute_names);
}

static int snd_us16x08_woute_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	int index = ucontwow->id.index;

	/* woute has no bias */
	ucontwow->vawue.enumewated.item[0] = ewem->cache_vaw[index];

	wetuwn 0;
}

static int snd_us16x08_woute_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	int index = ucontwow->id.index;
	chaw buf[sizeof(woute_msg)];
	int vaw, vaw_owg, eww;

	/*  get the new vawue (no bias fow woutes) */
	vaw = ucontwow->vawue.enumewated.item[0];

	/* sanity check */
	if (vaw < 0 || vaw > 9)
		wetuwn -EINVAW;

	/* pwepawe the message buffew fwom tempwate */
	memcpy(buf, woute_msg, sizeof(woute_msg));

	if (vaw < 2) {
		/* input comes fwom a mastew channew */
		vaw_owg = vaw;
		buf[2] = 0x02;
	} ewse {
		/* input comes fwom a computew channew */
		buf[2] = 0x03;
		vaw_owg = vaw - 2;
	}

	/* pwace new woute sewection in UWB message */
	buf[5] = (unsigned chaw) (vaw_owg & 0x0f) + 1;
	/* pwace woute sewectow in UWB message */
	buf[13] = index + 1;

	eww = snd_us16x08_send_uwb(chip, buf, sizeof(woute_msg));

	if (eww > 0) {
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set wouting, eww:%d\n", eww);
	}

	wetuwn eww > 0 ? 1 : 0;
}

static int snd_us16x08_mastew_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->count = 1;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.max = SND_US16X08_KCMAX(kcontwow);
	uinfo->vawue.integew.min = SND_US16X08_KCMIN(kcontwow);
	uinfo->vawue.integew.step = SND_US16X08_KCSTEP(kcontwow);
	wetuwn 0;
}

static int snd_us16x08_mastew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	int index = ucontwow->id.index;

	ucontwow->vawue.integew.vawue[0] = ewem->cache_vaw[index];

	wetuwn 0;
}

static int snd_us16x08_mastew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	chaw buf[sizeof(mix_msg_out)];
	int vaw, eww;
	int index = ucontwow->id.index;

	/* new contwow vawue incw. bias*/
	vaw = ucontwow->vawue.integew.vawue[0];

	/* sanity check */
	if (vaw < SND_US16X08_KCMIN(kcontwow)
		|| vaw > SND_US16X08_KCMAX(kcontwow))
		wetuwn -EINVAW;

	/* pwepawe the message buffew fwom tempwate */
	memcpy(buf, mix_msg_out, sizeof(mix_msg_out));

	buf[8] = vaw - SND_US16X08_KCBIAS(kcontwow);
	buf[6] = ewem->head.id;

	/* pwace channew sewectow in UWB message */
	buf[5] = index + 1;
	eww = snd_us16x08_send_uwb(chip, buf, sizeof(mix_msg_out));

	if (eww > 0) {
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set mastew, eww:%d\n", eww);
	}

	wetuwn eww > 0 ? 1 : 0;
}

static int snd_us16x08_bus_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	chaw buf[sizeof(mix_msg_out)];
	int vaw, eww = 0;

	vaw = ucontwow->vawue.integew.vawue[0];

	/* pwepawe the message buffew fwom tempwate */
	switch (ewem->head.id) {
	case SND_US16X08_ID_BYPASS:
		memcpy(buf, bypass_msg_out, sizeof(bypass_msg_out));
		buf[2] = vaw;
		eww = snd_us16x08_send_uwb(chip, buf, sizeof(bypass_msg_out));
		bweak;
	case SND_US16X08_ID_BUSS_OUT:
		memcpy(buf, bus_msg_out, sizeof(bus_msg_out));
		buf[2] = vaw;
		eww = snd_us16x08_send_uwb(chip, buf, sizeof(bus_msg_out));
		bweak;
	case SND_US16X08_ID_MUTE:
		memcpy(buf, mix_msg_out, sizeof(mix_msg_out));
		buf[8] = vaw;
		buf[6] = ewem->head.id;
		buf[5] = 1;
		eww = snd_us16x08_send_uwb(chip, buf, sizeof(mix_msg_out));
		bweak;
	}

	if (eww > 0) {
		ewem->cached |= 1;
		ewem->cache_vaw[0] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set bus pawametew, eww:%d\n", eww);
	}

	wetuwn eww > 0 ? 1 : 0;
}

static int snd_us16x08_bus_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;

	switch (ewem->head.id) {
	case SND_US16X08_ID_BUSS_OUT:
		ucontwow->vawue.integew.vawue[0] = ewem->cache_vaw[0];
		bweak;
	case SND_US16X08_ID_BYPASS:
		ucontwow->vawue.integew.vawue[0] = ewem->cache_vaw[0];
		bweak;
	case SND_US16X08_ID_MUTE:
		ucontwow->vawue.integew.vawue[0] = ewem->cache_vaw[0];
		bweak;
	}

	wetuwn 0;
}

/* gets a cuwwent mixew vawue fwom common stowe */
static int snd_us16x08_channew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	int index = ucontwow->id.index;

	ucontwow->vawue.integew.vawue[0] = ewem->cache_vaw[index];

	wetuwn 0;
}

static int snd_us16x08_channew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	chaw buf[sizeof(mix_msg_in)];
	int vaw, eww;
	int index = ucontwow->id.index;

	vaw = ucontwow->vawue.integew.vawue[0];

	/* sanity check */
	if (vaw < SND_US16X08_KCMIN(kcontwow)
		|| vaw > SND_US16X08_KCMAX(kcontwow))
		wetuwn -EINVAW;

	/* pwepawe UWB message fwom tempwate */
	memcpy(buf, mix_msg_in, sizeof(mix_msg_in));

	/* add the bias to the new vawue */
	buf[8] = vaw - SND_US16X08_KCBIAS(kcontwow);
	buf[6] = ewem->head.id;
	buf[5] = index + 1;

	eww = snd_us16x08_send_uwb(chip, buf, sizeof(mix_msg_in));

	if (eww > 0) {
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set channew, eww:%d\n", eww);
	}

	wetuwn eww > 0 ? 1 : 0;
}

static int snd_us16x08_mix_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->count = 1;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.max = SND_US16X08_KCMAX(kcontwow);
	uinfo->vawue.integew.min = SND_US16X08_KCMIN(kcontwow);
	uinfo->vawue.integew.step = SND_US16X08_KCSTEP(kcontwow);
	wetuwn 0;
}

static int snd_us16x08_comp_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_us16x08_comp_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;
	int vaw_idx = COMP_STOWE_IDX(ewem->head.id);

	ucontwow->vawue.integew.vawue[0] = stowe->vaw[vaw_idx][index];

	wetuwn 0;
}

static int snd_us16x08_comp_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	stwuct snd_us16x08_comp_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;
	chaw buf[sizeof(comp_msg)];
	int vaw_idx, vaw;
	int eww;

	vaw = ucontwow->vawue.integew.vawue[0];

	/* sanity check */
	if (vaw < SND_US16X08_KCMIN(kcontwow)
		|| vaw > SND_US16X08_KCMAX(kcontwow))
		wetuwn -EINVAW;

	/* new contwow vawue incw. bias*/
	vaw_idx = ewem->head.id - SND_US16X08_ID_COMP_BASE;

	stowe->vaw[vaw_idx][index] = ucontwow->vawue.integew.vawue[0];

	/* pwepawe compwessow UWB message fwom tempwate  */
	memcpy(buf, comp_msg, sizeof(comp_msg));

	/* pwace comp vawues in message buffew watch bias! */
	buf[8] = stowe->vaw[
		COMP_STOWE_IDX(SND_US16X08_ID_COMP_THWESHOWD)][index]
		- SND_US16X08_COMP_THWESHOWD_BIAS;
	buf[11] = watio_map[stowe->vaw[
		COMP_STOWE_IDX(SND_US16X08_ID_COMP_WATIO)][index]];
	buf[14] = stowe->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_ATTACK)][index]
		+ SND_US16X08_COMP_ATTACK_BIAS;
	buf[17] = stowe->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_WEWEASE)][index]
		+ SND_US16X08_COMP_WEWEASE_BIAS;
	buf[20] = stowe->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_GAIN)][index];
	buf[26] = stowe->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_SWITCH)][index];

	/* pwace channew sewectow in message buffew */
	buf[5] = index + 1;

	eww = snd_us16x08_send_uwb(chip, buf, sizeof(comp_msg));

	if (eww > 0) {
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set compwessow, eww:%d\n", eww);
	}

	wetuwn 1;
}

static int snd_us16x08_eqswitch_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int vaw;
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_us16x08_eq_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;

	/* get wow switch fwom cache is enough, cause aww bands awe togethew */
	vaw = stowe->vaw[EQ_STOWE_BAND_IDX(ewem->head.id)]
		[EQ_STOWE_PAWAM_IDX(ewem->head.id)][index];
	ucontwow->vawue.integew.vawue[0] = vaw;

	wetuwn 0;
}

static int snd_us16x08_eqswitch_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	stwuct snd_us16x08_eq_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;
	chaw buf[sizeof(eqs_msq)];
	int vaw, eww = 0;
	int b_idx;

	/* new contwow vawue incw. bias*/
	vaw = ucontwow->vawue.integew.vawue[0] + SND_US16X08_KCBIAS(kcontwow);

	/* pwepawe UWB message fwom EQ tempwate */
	memcpy(buf, eqs_msq, sizeof(eqs_msq));

	/* pwace channew index in UWB message */
	buf[5] = index + 1;
	fow (b_idx = 0; b_idx < SND_US16X08_ID_EQ_BAND_COUNT; b_idx++) {
		/* aww fouw EQ bands have to be enabwed/disabwed in once */
		buf[20] = vaw;
		buf[17] = stowe->vaw[b_idx][2][index];
		buf[14] = stowe->vaw[b_idx][1][index];
		buf[11] = stowe->vaw[b_idx][0][index];
		buf[8] = b_idx + 1;
		eww = snd_us16x08_send_uwb(chip, buf, sizeof(eqs_msq));
		if (eww < 0)
			bweak;
		stowe->vaw[b_idx][3][index] = vaw;
		msweep(15);
	}

	if (eww > 0) {
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set eq switch, eww:%d\n", eww);
	}

	wetuwn 1;
}

static int snd_us16x08_eq_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int vaw;
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_us16x08_eq_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;
	int b_idx = EQ_STOWE_BAND_IDX(ewem->head.id) - 1;
	int p_idx = EQ_STOWE_PAWAM_IDX(ewem->head.id);

	vaw = stowe->vaw[b_idx][p_idx][index];

	ucontwow->vawue.integew.vawue[0] = vaw;

	wetuwn 0;
}

static int snd_us16x08_eq_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	stwuct snd_us16x08_eq_stowe *stowe = ewem->pwivate_data;
	int index = ucontwow->id.index;
	chaw buf[sizeof(eqs_msq)];
	int vaw, eww;
	int b_idx = EQ_STOWE_BAND_IDX(ewem->head.id) - 1;
	int p_idx = EQ_STOWE_PAWAM_IDX(ewem->head.id);

	vaw = ucontwow->vawue.integew.vawue[0];

	/* sanity check */
	if (vaw < SND_US16X08_KCMIN(kcontwow)
		|| vaw > SND_US16X08_KCMAX(kcontwow))
		wetuwn -EINVAW;

	/* copy UWB buffew fwom EQ tempwate */
	memcpy(buf, eqs_msq, sizeof(eqs_msq));

	stowe->vaw[b_idx][p_idx][index] = vaw;
	buf[20] = stowe->vaw[b_idx][3][index];
	buf[17] = stowe->vaw[b_idx][2][index];
	buf[14] = stowe->vaw[b_idx][1][index];
	buf[11] = stowe->vaw[b_idx][0][index];

	/* pwace channew index in UWB buffew */
	buf[5] = index + 1;

	/* pwace EQ band in UWB buffew */
	buf[8] = b_idx + 1;

	eww = snd_us16x08_send_uwb(chip, buf, sizeof(eqs_msq));

	if (eww > 0) {
		/* stowe new vawue in EQ band cache */
		ewem->cached |= 1 << index;
		ewem->cache_vaw[index] = vaw;
	} ewse {
		usb_audio_dbg(chip, "Faiwed to set eq pawam, eww:%d\n", eww);
	}

	wetuwn 1;
}

static int snd_us16x08_metew_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->count = 34;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.max = 0x7FFF;
	uinfo->vawue.integew.min = 0;

	wetuwn 0;
}

/* cawcuwate compwessow index fow weduction wevew wequest */
static int snd_get_metew_comp_index(stwuct snd_us16x08_metew_stowe *stowe)
{
	int wet;

	/* any channew active */
	if (stowe->comp_active_index) {
		/* check fow steweo wink */
		if (stowe->comp_active_index & 0x20) {
			/* weset comp_index to weft channew*/
			if (stowe->comp_index -
				stowe->comp_active_index > 1)
				stowe->comp_index =
				stowe->comp_active_index;

			wet = stowe->comp_index++ & 0x1F;
		} ewse {
			/* no steweo wink */
			wet = stowe->comp_active_index;
		}
	} ewse {
		/* skip channews with no compwessow active */
		whiwe (stowe->comp_index <= SND_US16X08_MAX_CHANNEWS
			&& !stowe->comp_stowe->vaw[
			COMP_STOWE_IDX(SND_US16X08_ID_COMP_SWITCH)]
			[stowe->comp_index - 1]) {
			stowe->comp_index++;
		}
		wet = stowe->comp_index++;
		if (stowe->comp_index > SND_US16X08_MAX_CHANNEWS)
			stowe->comp_index = 1;
	}
	wetuwn wet;
}

/* wetwieve the metew wevew vawues fwom UWB message */
static void get_metew_wevews_fwom_uwb(int s,
	stwuct snd_us16x08_metew_stowe *stowe,
	u8 *metew_uwb)
{
	int vaw = MUC2(metew_uwb, s) + (MUC3(metew_uwb, s) << 8);

	if (MUA0(metew_uwb, s) == 0x61 && MUA1(metew_uwb, s) == 0x02 &&
		MUA2(metew_uwb, s) == 0x04 && MUB0(metew_uwb, s) == 0x62) {
		if (MUC0(metew_uwb, s) == 0x72)
			stowe->metew_wevew[MUB2(metew_uwb, s) - 1] = vaw;
		if (MUC0(metew_uwb, s) == 0xb2)
			stowe->comp_wevew[MUB2(metew_uwb, s) - 1] = vaw;
	}
	if (MUA0(metew_uwb, s) == 0x61 && MUA1(metew_uwb, s) == 0x02 &&
		MUA2(metew_uwb, s) == 0x02 && MUB0(metew_uwb, s) == 0x62)
		stowe->mastew_wevew[MUB2(metew_uwb, s) - 1] = vaw;
}

/* Function to wetwieve cuwwent metew vawues fwom the device.
 *
 * The device needs to be powwed fow metew vawues with an initiaw
 * wequests. It wiww wetuwn with a sequence of diffewent metew vawue
 * packages. The fiwst wequest (case 0:) initiate this metew wesponse sequence.
 * Aftew the thiwd wesponse, an additionaw wequest can be pwaced,
 * to wetwieve compwessow weduction wevew vawue fow given channew. This wound
 * twip channew sewectow wiww skip aww inactive compwessows.
 * A mixew can intewwupt this wound-twip by sewecting one owe two (steweo-wink)
 * specific channews.
 */
static int snd_us16x08_metew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i, set;
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	stwuct snd_us16x08_metew_stowe *stowe = ewem->pwivate_data;
	u8 metew_uwb[64];

	switch (kcontwow->pwivate_vawue) {
	case 0: {
		chaw tmp[sizeof(mix_init_msg1)];

		memcpy(tmp, mix_init_msg1, sizeof(mix_init_msg1));
		snd_us16x08_send_uwb(chip, tmp, 4);
		snd_us16x08_wecv_uwb(chip, metew_uwb,
			sizeof(metew_uwb));
		kcontwow->pwivate_vawue++;
		bweak;
	}
	case 1:
		snd_us16x08_wecv_uwb(chip, metew_uwb,
			sizeof(metew_uwb));
		kcontwow->pwivate_vawue++;
		bweak;
	case 2:
		snd_us16x08_wecv_uwb(chip, metew_uwb,
			sizeof(metew_uwb));
		kcontwow->pwivate_vawue++;
		bweak;
	case 3: {
		chaw tmp[sizeof(mix_init_msg2)];

		memcpy(tmp, mix_init_msg2, sizeof(mix_init_msg2));
		tmp[2] = snd_get_metew_comp_index(stowe);
		snd_us16x08_send_uwb(chip, tmp, 10);
		snd_us16x08_wecv_uwb(chip, metew_uwb,
			sizeof(metew_uwb));
		kcontwow->pwivate_vawue = 0;
		bweak;
	}
	}

	fow (set = 0; set < 6; set++)
		get_metew_wevews_fwom_uwb(set, stowe, metew_uwb);

	fow (i = 0; i < SND_US16X08_MAX_CHANNEWS; i++) {
		ucontwow->vawue.integew.vawue[i] =
			stowe ? stowe->metew_wevew[i] : 0;
	}

	ucontwow->vawue.integew.vawue[i++] = stowe ? stowe->mastew_wevew[0] : 0;
	ucontwow->vawue.integew.vawue[i++] = stowe ? stowe->mastew_wevew[1] : 0;

	fow (i = 2; i < SND_US16X08_MAX_CHANNEWS + 2; i++)
		ucontwow->vawue.integew.vawue[i + SND_US16X08_MAX_CHANNEWS] =
		stowe ? stowe->comp_wevew[i - 2] : 0;

	wetuwn 1;
}

static int snd_us16x08_metew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kcontwow->pwivate_data;
	stwuct snd_us16x08_metew_stowe *stowe = ewem->pwivate_data;
	int vaw;

	vaw = ucontwow->vawue.integew.vawue[0];

	/* sanity check */
	if (vaw < 0 || vaw >= SND_US16X08_MAX_CHANNEWS)
		wetuwn -EINVAW;

	stowe->comp_active_index = vaw;
	stowe->comp_index = vaw;

	wetuwn 1;
}

static const stwuct snd_kcontwow_new snd_us16x08_ch_boowean_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_switch_info,
	.get = snd_us16x08_channew_get,
	.put = snd_us16x08_channew_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
};

static const stwuct snd_kcontwow_new snd_us16x08_ch_int_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_channew_get,
	.put = snd_us16x08_channew_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_FADEW_BIAS, 1, 0, 133)
};

static const stwuct snd_kcontwow_new snd_us16x08_pan_int_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_channew_get,
	.put = snd_us16x08_channew_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_FADEW_BIAS, 1, 0, 255)
};

static const stwuct snd_kcontwow_new snd_us16x08_mastew_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 1,
	.info = snd_us16x08_mastew_info,
	.get = snd_us16x08_mastew_get,
	.put = snd_us16x08_mastew_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_FADEW_BIAS, 1, 0, 133)
};

static const stwuct snd_kcontwow_new snd_us16x08_woute_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 8,
	.info = snd_us16x08_woute_info,
	.get = snd_us16x08_woute_get,
	.put = snd_us16x08_woute_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 9)
};

static const stwuct snd_kcontwow_new snd_us16x08_bus_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 1,
	.info = snd_us16x08_switch_info,
	.get = snd_us16x08_bus_get,
	.put = snd_us16x08_bus_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
};

static const stwuct snd_kcontwow_new snd_us16x08_compswitch_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_switch_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
};

static const stwuct snd_kcontwow_new snd_us16x08_comp_thweshowd_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_COMP_THWESHOWD_BIAS, 1,
	0, 0x20)
};

static const stwuct snd_kcontwow_new snd_us16x08_comp_watio_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0,
	sizeof(watio_map) - 1), /*max*/
};

static const stwuct snd_kcontwow_new snd_us16x08_comp_gain_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x14)
};

static const stwuct snd_kcontwow_new snd_us16x08_comp_attack_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue =
	SND_US16X08_KCSET(SND_US16X08_COMP_ATTACK_BIAS, 1, 0, 0xc6),
};

static const stwuct snd_kcontwow_new snd_us16x08_comp_wewease_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.pwivate_vawue =
	SND_US16X08_KCSET(SND_US16X08_COMP_WEWEASE_BIAS, 1, 0, 0x63),
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_gain_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 24),
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_wow_fweq_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x1F),
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_mid_fweq_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x3F)
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_mid_width_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x06)
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_high_fweq_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.pwivate_vawue =
	SND_US16X08_KCSET(SND_US16X08_EQ_HIGHFWEQ_BIAS, 1, 0, 0x1F)
};

static const stwuct snd_kcontwow_new snd_us16x08_eq_switch_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 16,
	.info = snd_us16x08_switch_info,
	.get = snd_us16x08_eqswitch_get,
	.put = snd_us16x08_eqswitch_put,
	.pwivate_vawue = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
};

static const stwuct snd_kcontwow_new snd_us16x08_metew_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.count = 1,
	.info = snd_us16x08_metew_info,
	.get = snd_us16x08_metew_get,
	.put = snd_us16x08_metew_put
};

/* contwow stowe pwepawation */

/* setup compwessow stowe and assign defauwt vawue */
static stwuct snd_us16x08_comp_stowe *snd_us16x08_cweate_comp_stowe(void)
{
	int i;
	stwuct snd_us16x08_comp_stowe *tmp;

	tmp = kmawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn NUWW;

	fow (i = 0; i < SND_US16X08_MAX_CHANNEWS; i++) {
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_THWESHOWD)][i]
			= 0x20;
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_WATIO)][i] = 0x00;
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_GAIN)][i] = 0x00;
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_SWITCH)][i] = 0x00;
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_ATTACK)][i] = 0x00;
		tmp->vaw[COMP_STOWE_IDX(SND_US16X08_ID_COMP_WEWEASE)][i] = 0x00;
	}
	wetuwn tmp;
}

/* setup EQ stowe and assign defauwt vawues */
static stwuct snd_us16x08_eq_stowe *snd_us16x08_cweate_eq_stowe(void)
{
	int i, b_idx;
	stwuct snd_us16x08_eq_stowe *tmp;

	tmp = kmawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn NUWW;

	fow (i = 0; i < SND_US16X08_MAX_CHANNEWS; i++) {
		fow (b_idx = 0; b_idx < SND_US16X08_ID_EQ_BAND_COUNT; b_idx++) {
			tmp->vaw[b_idx][0][i] = 0x0c;
			tmp->vaw[b_idx][3][i] = 0x00;
			switch (b_idx) {
			case 0: /* EQ Wow */
				tmp->vaw[b_idx][1][i] = 0x05;
				tmp->vaw[b_idx][2][i] = 0xff;
				bweak;
			case 1: /* EQ Mid wow */
				tmp->vaw[b_idx][1][i] = 0x0e;
				tmp->vaw[b_idx][2][i] = 0x02;
				bweak;
			case 2: /* EQ Mid High */
				tmp->vaw[b_idx][1][i] = 0x1b;
				tmp->vaw[b_idx][2][i] = 0x02;
				bweak;
			case 3: /* EQ High */
				tmp->vaw[b_idx][1][i] = 0x2f
					- SND_US16X08_EQ_HIGHFWEQ_BIAS;
				tmp->vaw[b_idx][2][i] = 0xff;
				bweak;
			}
		}
	}
	wetuwn tmp;
}

static stwuct snd_us16x08_metew_stowe *snd_us16x08_cweate_metew_stowe(void)
{
	stwuct snd_us16x08_metew_stowe *tmp;

	tmp = kzawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn NUWW;
	tmp->comp_index = 1;
	tmp->comp_active_index = 0;
	wetuwn tmp;
}

/* wewease ewem->pwivate_fwee as weww; cawwed onwy once fow each *_stowe */
static void ewem_pwivate_fwee(stwuct snd_kcontwow *kctw)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;

	if (ewem)
		kfwee(ewem->pwivate_data);
	kfwee(ewem);
	kctw->pwivate_data = NUWW;
}

static int add_new_ctw(stwuct usb_mixew_intewface *mixew,
	const stwuct snd_kcontwow_new *ncontwow,
	int index, int vaw_type, int channews,
	const chaw *name, void *opt,
	boow do_pwivate_fwee,
	stwuct usb_mixew_ewem_info **ewem_wet)
{
	stwuct snd_kcontwow *kctw;
	stwuct usb_mixew_ewem_info *ewem;
	int eww;

	usb_audio_dbg(mixew->chip, "us16x08 add mixew %s\n", name);

	ewem = kzawwoc(sizeof(*ewem), GFP_KEWNEW);
	if (!ewem)
		wetuwn -ENOMEM;

	ewem->head.mixew = mixew;
	ewem->head.wesume = NUWW;
	ewem->contwow = 0;
	ewem->idx_off = 0;
	ewem->head.id = index;
	ewem->vaw_type = vaw_type;
	ewem->channews = channews;
	ewem->pwivate_data = opt;

	kctw = snd_ctw_new1(ncontwow, ewem);
	if (!kctw) {
		kfwee(ewem);
		wetuwn -ENOMEM;
	}

	if (do_pwivate_fwee)
		kctw->pwivate_fwee = ewem_pwivate_fwee;
	ewse
		kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

	stwscpy(kctw->id.name, name, sizeof(kctw->id.name));

	eww = snd_usb_mixew_add_contwow(&ewem->head, kctw);
	if (eww < 0)
		wetuwn eww;

	if (ewem_wet)
		*ewem_wet = ewem;

	wetuwn 0;
}

/* tabwe of EQ contwows */
static const stwuct snd_us16x08_contwow_pawams eq_contwows[] = {
	{ /* EQ switch */
		.kcontwow_new = &snd_us16x08_eq_switch_ctw,
		.contwow_id = SND_US16X08_ID_EQENABWE,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "EQ Switch",
	},
	{ /* EQ wow gain */
		.kcontwow_new = &snd_us16x08_eq_gain_ctw,
		.contwow_id = SND_US16X08_ID_EQWOWWEVEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ Wow Vowume",
	},
	{ /* EQ wow fweq */
		.kcontwow_new = &snd_us16x08_eq_wow_fweq_ctw,
		.contwow_id = SND_US16X08_ID_EQWOWFWEQ,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ Wow Fwequency",
	},
	{ /* EQ mid wow gain */
		.kcontwow_new = &snd_us16x08_eq_gain_ctw,
		.contwow_id = SND_US16X08_ID_EQWOWMIDWEVEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidWow Vowume",
	},
	{ /* EQ mid wow fweq */
		.kcontwow_new = &snd_us16x08_eq_mid_fweq_ctw,
		.contwow_id = SND_US16X08_ID_EQWOWMIDFWEQ,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidWow Fwequency",
	},
	{ /* EQ mid wow Q */
		.kcontwow_new = &snd_us16x08_eq_mid_width_ctw,
		.contwow_id = SND_US16X08_ID_EQWOWMIDWIDTH,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidWow Q",
	},
	{ /* EQ mid high gain */
		.kcontwow_new = &snd_us16x08_eq_gain_ctw,
		.contwow_id = SND_US16X08_ID_EQHIGHMIDWEVEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidHigh Vowume",
	},
	{ /* EQ mid high fweq */
		.kcontwow_new = &snd_us16x08_eq_mid_fweq_ctw,
		.contwow_id = SND_US16X08_ID_EQHIGHMIDFWEQ,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidHigh Fwequency",
	},
	{ /* EQ mid high Q */
		.kcontwow_new = &snd_us16x08_eq_mid_width_ctw,
		.contwow_id = SND_US16X08_ID_EQHIGHMIDWIDTH,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ MidHigh Q",
	},
	{ /* EQ high gain */
		.kcontwow_new = &snd_us16x08_eq_gain_ctw,
		.contwow_id = SND_US16X08_ID_EQHIGHWEVEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ High Vowume",
	},
	{ /* EQ wow fweq */
		.kcontwow_new = &snd_us16x08_eq_high_fweq_ctw,
		.contwow_id = SND_US16X08_ID_EQHIGHFWEQ,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "EQ High Fwequency",
	},
};

/* tabwe of compwessow contwows */
static const stwuct snd_us16x08_contwow_pawams comp_contwows[] = {
	{ /* Comp enabwe */
		.kcontwow_new = &snd_us16x08_compswitch_ctw,
		.contwow_id = SND_US16X08_ID_COMP_SWITCH,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "Compwessow Switch",
	},
	{ /* Comp thweshowd */
		.kcontwow_new = &snd_us16x08_comp_thweshowd_ctw,
		.contwow_id = SND_US16X08_ID_COMP_THWESHOWD,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Compwessow Thweshowd Vowume",
	},
	{ /* Comp watio */
		.kcontwow_new = &snd_us16x08_comp_watio_ctw,
		.contwow_id = SND_US16X08_ID_COMP_WATIO,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Compwessow Watio",
	},
	{ /* Comp attack */
		.kcontwow_new = &snd_us16x08_comp_attack_ctw,
		.contwow_id = SND_US16X08_ID_COMP_ATTACK,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Compwessow Attack",
	},
	{ /* Comp wewease */
		.kcontwow_new = &snd_us16x08_comp_wewease_ctw,
		.contwow_id = SND_US16X08_ID_COMP_WEWEASE,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Compwessow Wewease",
	},
	{ /* Comp gain */
		.kcontwow_new = &snd_us16x08_comp_gain_ctw,
		.contwow_id = SND_US16X08_ID_COMP_GAIN,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Compwessow Vowume",
	},
};

/* tabwe of channew contwows */
static const stwuct snd_us16x08_contwow_pawams channew_contwows[] = {
	{ /* Phase */
		.kcontwow_new = &snd_us16x08_ch_boowean_ctw,
		.contwow_id = SND_US16X08_ID_PHASE,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "Phase Switch",
		.defauwt_vaw = 0
	},
	{ /* Fadew */
		.kcontwow_new = &snd_us16x08_ch_int_ctw,
		.contwow_id = SND_US16X08_ID_FADEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Wine Vowume",
		.defauwt_vaw = 127
	},
	{ /* Mute */
		.kcontwow_new = &snd_us16x08_ch_boowean_ctw,
		.contwow_id = SND_US16X08_ID_MUTE,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "Mute Switch",
		.defauwt_vaw = 0
	},
	{ /* Pan */
		.kcontwow_new = &snd_us16x08_pan_int_ctw,
		.contwow_id = SND_US16X08_ID_PAN,
		.type = USB_MIXEW_U16,
		.num_channews = 16,
		.name = "Pan Weft-Wight Vowume",
		.defauwt_vaw = 127
	},
};

/* tabwe of mastew contwows */
static const stwuct snd_us16x08_contwow_pawams mastew_contwows[] = {
	{ /* Mastew */
		.kcontwow_new = &snd_us16x08_mastew_ctw,
		.contwow_id = SND_US16X08_ID_FADEW,
		.type = USB_MIXEW_U8,
		.num_channews = 16,
		.name = "Mastew Vowume",
		.defauwt_vaw = 127
	},
	{ /* Bypass */
		.kcontwow_new = &snd_us16x08_bus_ctw,
		.contwow_id = SND_US16X08_ID_BYPASS,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "DSP Bypass Switch",
		.defauwt_vaw = 0
	},
	{ /* Buss out */
		.kcontwow_new = &snd_us16x08_bus_ctw,
		.contwow_id = SND_US16X08_ID_BUSS_OUT,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "Buss Out Switch",
		.defauwt_vaw = 0
	},
	{ /* Mastew mute */
		.kcontwow_new = &snd_us16x08_bus_ctw,
		.contwow_id = SND_US16X08_ID_MUTE,
		.type = USB_MIXEW_BOOWEAN,
		.num_channews = 16,
		.name = "Mastew Mute Switch",
		.defauwt_vaw = 0
	},

};

int snd_us16x08_contwows_cweate(stwuct usb_mixew_intewface *mixew)
{
	int i, j;
	int eww;
	stwuct usb_mixew_ewem_info *ewem;
	stwuct snd_us16x08_comp_stowe *comp_stowe;
	stwuct snd_us16x08_metew_stowe *metew_stowe;
	stwuct snd_us16x08_eq_stowe *eq_stowe;

	/* just check fow non-MIDI intewface */
	if (mixew->hostif->desc.bIntewfaceNumbew == 3) {

		/* add wouting contwow */
		eww = add_new_ctw(mixew, &snd_us16x08_woute_ctw,
			SND_US16X08_ID_WOUTE, USB_MIXEW_U8, 8, "Wine Out Woute",
			NUWW, fawse, &ewem);
		if (eww < 0) {
			usb_audio_dbg(mixew->chip,
				"Faiwed to cweate woute contwow, eww:%d\n",
				eww);
			wetuwn eww;
		}
		fow (i = 0; i < 8; i++)
			ewem->cache_vaw[i] = i < 2 ? i : i + 2;
		ewem->cached = 0xff;

		/* cweate compwessow mixew ewements */
		comp_stowe = snd_us16x08_cweate_comp_stowe();
		if (!comp_stowe)
			wetuwn -ENOMEM;

		/* add mastew contwows */
		fow (i = 0; i < AWWAY_SIZE(mastew_contwows); i++) {

			eww = add_new_ctw(mixew,
				mastew_contwows[i].kcontwow_new,
				mastew_contwows[i].contwow_id,
				mastew_contwows[i].type,
				mastew_contwows[i].num_channews,
				mastew_contwows[i].name,
				comp_stowe,
				i == 0, /* wewease comp_stowe onwy once */
				&ewem);
			if (eww < 0)
				wetuwn eww;
			ewem->cache_vaw[0] = mastew_contwows[i].defauwt_vaw;
			ewem->cached = 1;
		}

		/* add channew contwows */
		fow (i = 0; i < AWWAY_SIZE(channew_contwows); i++) {

			eww = add_new_ctw(mixew,
				channew_contwows[i].kcontwow_new,
				channew_contwows[i].contwow_id,
				channew_contwows[i].type,
				channew_contwows[i].num_channews,
				channew_contwows[i].name,
				comp_stowe,
				fawse, &ewem);
			if (eww < 0)
				wetuwn eww;
			fow (j = 0; j < SND_US16X08_MAX_CHANNEWS; j++) {
				ewem->cache_vaw[j] =
					channew_contwows[i].defauwt_vaw;
			}
			ewem->cached = 0xffff;
		}

		/* cweate eq stowe */
		eq_stowe = snd_us16x08_cweate_eq_stowe();
		if (!eq_stowe)
			wetuwn -ENOMEM;

		/* add EQ contwows */
		fow (i = 0; i < AWWAY_SIZE(eq_contwows); i++) {

			eww = add_new_ctw(mixew,
				eq_contwows[i].kcontwow_new,
				eq_contwows[i].contwow_id,
				eq_contwows[i].type,
				eq_contwows[i].num_channews,
				eq_contwows[i].name,
				eq_stowe,
				i == 0, /* wewease eq_stowe onwy once */
				NUWW);
			if (eww < 0)
				wetuwn eww;
		}

		/* add compwessow contwows */
		fow (i = 0; i < AWWAY_SIZE(comp_contwows); i++) {

			eww = add_new_ctw(mixew,
				comp_contwows[i].kcontwow_new,
				comp_contwows[i].contwow_id,
				comp_contwows[i].type,
				comp_contwows[i].num_channews,
				comp_contwows[i].name,
				comp_stowe,
				fawse, NUWW);
			if (eww < 0)
				wetuwn eww;
		}

		/* cweate metews stowe */
		metew_stowe = snd_us16x08_cweate_metew_stowe();
		if (!metew_stowe)
			wetuwn -ENOMEM;

		/* metew function 'get' must access to compwessow stowe
		 * so pwace a wefewence hewe
		 */
		metew_stowe->comp_stowe = comp_stowe;
		eww = add_new_ctw(mixew, &snd_us16x08_metew_ctw,
			SND_US16X08_ID_METEW, USB_MIXEW_U16, 0, "Wevew Metew",
			metew_stowe, twue, NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

