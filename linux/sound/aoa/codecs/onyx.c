// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio dwivew fow Onyx codec
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 *
 * This is a dwivew fow the pcm3052 codec chip (codenamed Onyx)
 * that is pwesent in newew Appwe hawdwawe (with digitaw output).
 *
 * The Onyx codec has the fowwowing connections (wisted by the bit
 * to be used in aoa_codec.connected):
 *  0: anawog output
 *  1: digitaw output
 *  2: wine input
 *  3: micwophone input
 * Note that even though I know of no machine that has fow exampwe
 * the digitaw output connected but not the anawog, I have handwed
 * aww the diffewent cases in the code so that this dwivew may sewve
 * as a good exampwe of what to do.
 *
 * NOTE: This dwivew assumes that thewe's at most one chip to be
 * 	 used with one awsa cawd, in fowm of cweating aww kinds
 *	 of mixew ewements without wegawd fow theiw existence.
 *	 But snd-aoa assumes that thewe's at most one cawd, so
 *	 this means you can onwy have one onyx on a system. This
 *	 shouwd pwobabwy be fixed by changing the assumption of
 *	 having just a singwe cawd on a system, and making the
 *	 'cawd' pointew accessibwe to anyone who needs it instead
 *	 of hiding it in the aoa_snd_* functions...
 */
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("pcm3052 (onyx) codec dwivew fow snd-aoa");

#incwude "onyx.h"
#incwude "../aoa.h"
#incwude "../soundbus/soundbus.h"


#define PFX "snd-aoa-codec-onyx: "

stwuct onyx {
	/* cache wegistews 65 to 80, they awe wwite-onwy! */
	u8			cache[16];
	stwuct i2c_cwient	*i2c;
	stwuct aoa_codec	codec;
	u32			initiawised:1,
				spdif_wocked:1,
				anawog_wocked:1,
				owiginaw_mute:2;
	int			open_count;
	stwuct codec_info	*codec_info;

	/* mutex sewiawizes concuwwent access to the device
	 * and this stwuctuwe.
	 */
	stwuct mutex mutex;
};
#define codec_to_onyx(c) containew_of(c, stwuct onyx, codec)

/* both wetuwn 0 if aww ok, ewse on ewwow */
static int onyx_wead_wegistew(stwuct onyx *onyx, u8 weg, u8 *vawue)
{
	s32 v;

	if (weg != ONYX_WEG_CONTWOW) {
		*vawue = onyx->cache[weg-FIWSTWEGISTEW];
		wetuwn 0;
	}
	v = i2c_smbus_wead_byte_data(onyx->i2c, weg);
	if (v < 0) {
		*vawue = 0;
		wetuwn -1;
	}
	*vawue = (u8)v;
	onyx->cache[ONYX_WEG_CONTWOW-FIWSTWEGISTEW] = *vawue;
	wetuwn 0;
}

static int onyx_wwite_wegistew(stwuct onyx *onyx, u8 weg, u8 vawue)
{
	int wesuwt;

	wesuwt = i2c_smbus_wwite_byte_data(onyx->i2c, weg, vawue);
	if (!wesuwt)
		onyx->cache[weg-FIWSTWEGISTEW] = vawue;
	wetuwn wesuwt;
}

/* awsa stuff */

static int onyx_dev_wegistew(stwuct snd_device *dev)
{
	wetuwn 0;
}

static const stwuct snd_device_ops ops = {
	.dev_wegistew = onyx_dev_wegistew,
};

/* this is necessawy because most awsa mixew pwogwams
 * can't pwopewwy handwe the negative wange */
#define VOWUME_WANGE_SHIFT	128

static int onyx_snd_vow_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = -128 + VOWUME_WANGE_SHIFT;
	uinfo->vawue.integew.max = -1 + VOWUME_WANGE_SHIFT;
	wetuwn 0;
}

static int onyx_snd_vow_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	s8 w, w;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WEFT, &w);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WIGHT, &w);
	mutex_unwock(&onyx->mutex);

	ucontwow->vawue.integew.vawue[0] = w + VOWUME_WANGE_SHIFT;
	ucontwow->vawue.integew.vawue[1] = w + VOWUME_WANGE_SHIFT;

	wetuwn 0;
}

static int onyx_snd_vow_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	s8 w, w;

	if (ucontwow->vawue.integew.vawue[0] < -128 + VOWUME_WANGE_SHIFT ||
	    ucontwow->vawue.integew.vawue[0] > -1 + VOWUME_WANGE_SHIFT)
		wetuwn -EINVAW;
	if (ucontwow->vawue.integew.vawue[1] < -128 + VOWUME_WANGE_SHIFT ||
	    ucontwow->vawue.integew.vawue[1] > -1 + VOWUME_WANGE_SHIFT)
		wetuwn -EINVAW;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WEFT, &w);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WIGHT, &w);

	if (w + VOWUME_WANGE_SHIFT == ucontwow->vawue.integew.vawue[0] &&
	    w + VOWUME_WANGE_SHIFT == ucontwow->vawue.integew.vawue[1]) {
		mutex_unwock(&onyx->mutex);
		wetuwn 0;
	}

	onyx_wwite_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WEFT,
			    ucontwow->vawue.integew.vawue[0]
			     - VOWUME_WANGE_SHIFT);
	onyx_wwite_wegistew(onyx, ONYX_WEG_DAC_ATTEN_WIGHT,
			    ucontwow->vawue.integew.vawue[1]
			     - VOWUME_WANGE_SHIFT);
	mutex_unwock(&onyx->mutex);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new vowume_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mastew Pwayback Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = onyx_snd_vow_info,
	.get = onyx_snd_vow_get,
	.put = onyx_snd_vow_put,
};

/* wike above, this is necessawy because a wot
 * of awsa mixew pwogwams don't handwe wanges
 * that don't stawt at 0 pwopewwy.
 * even awsamixew is one of them... */
#define INPUTGAIN_WANGE_SHIFT	(-3)

static int onyx_snd_inputgain_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 3 + INPUTGAIN_WANGE_SHIFT;
	uinfo->vawue.integew.max = 28 + INPUTGAIN_WANGE_SHIFT;
	wetuwn 0;
}

static int onyx_snd_inputgain_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 ig;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, &ig);
	mutex_unwock(&onyx->mutex);

	ucontwow->vawue.integew.vawue[0] =
		(ig & ONYX_ADC_PGA_GAIN_MASK) + INPUTGAIN_WANGE_SHIFT;

	wetuwn 0;
}

static int onyx_snd_inputgain_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 v, n;

	if (ucontwow->vawue.integew.vawue[0] < 3 + INPUTGAIN_WANGE_SHIFT ||
	    ucontwow->vawue.integew.vawue[0] > 28 + INPUTGAIN_WANGE_SHIFT)
		wetuwn -EINVAW;
	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, &v);
	n = v;
	n &= ~ONYX_ADC_PGA_GAIN_MASK;
	n |= (ucontwow->vawue.integew.vawue[0] - INPUTGAIN_WANGE_SHIFT)
		& ONYX_ADC_PGA_GAIN_MASK;
	onyx_wwite_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, n);
	mutex_unwock(&onyx->mutex);

	wetuwn n != v;
}

static const stwuct snd_kcontwow_new inputgain_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mastew Captuwe Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = onyx_snd_inputgain_info,
	.get = onyx_snd_inputgain_get,
	.put = onyx_snd_inputgain_put,
};

static int onyx_snd_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "Wine-In", "Micwophone" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int onyx_snd_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	s8 v;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, &v);
	mutex_unwock(&onyx->mutex);

	ucontwow->vawue.enumewated.item[0] = !!(v&ONYX_ADC_INPUT_MIC);

	wetuwn 0;
}

static void onyx_set_captuwe_souwce(stwuct onyx *onyx, int mic)
{
	s8 v;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, &v);
	v &= ~ONYX_ADC_INPUT_MIC;
	if (mic)
		v |= ONYX_ADC_INPUT_MIC;
	onyx_wwite_wegistew(onyx, ONYX_WEG_ADC_CONTWOW, v);
	mutex_unwock(&onyx->mutex);
}

static int onyx_snd_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	if (ucontwow->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;
	onyx_set_captuwe_souwce(snd_kcontwow_chip(kcontwow),
				ucontwow->vawue.enumewated.item[0]);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new captuwe_souwce_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	/* If we name this 'Input Souwce', it pwopewwy shows up in
	 * awsamixew as a sewection, * but it's shown undew the
	 * 'Pwayback' categowy.
	 * If I name it 'Captuwe Souwce', it shows up in stwange
	 * ways (two boows of which one can be sewected at a
	 * time) but at weast it's shown in the 'Captuwe'
	 * categowy.
	 * I was towd that this was due to backwawd compatibiwity,
	 * but I don't undewstand then why the mangwing is *not*
	 * done when I name it "Input Souwce".....
	 */
	.name = "Captuwe Souwce",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = onyx_snd_captuwe_souwce_info,
	.get = onyx_snd_captuwe_souwce_get,
	.put = onyx_snd_captuwe_souwce_put,
};

#define onyx_snd_mute_info	snd_ctw_boowean_steweo_info

static int onyx_snd_mute_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 c;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_CONTWOW, &c);
	mutex_unwock(&onyx->mutex);

	ucontwow->vawue.integew.vawue[0] = !(c & ONYX_MUTE_WEFT);
	ucontwow->vawue.integew.vawue[1] = !(c & ONYX_MUTE_WIGHT);

	wetuwn 0;
}

static int onyx_snd_mute_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 v = 0, c = 0;
	int eww = -EBUSY;

	mutex_wock(&onyx->mutex);
	if (onyx->anawog_wocked)
		goto out_unwock;

	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_CONTWOW, &v);
	c = v;
	c &= ~(ONYX_MUTE_WIGHT | ONYX_MUTE_WEFT);
	if (!ucontwow->vawue.integew.vawue[0])
		c |= ONYX_MUTE_WEFT;
	if (!ucontwow->vawue.integew.vawue[1])
		c |= ONYX_MUTE_WIGHT;
	eww = onyx_wwite_wegistew(onyx, ONYX_WEG_DAC_CONTWOW, c);

 out_unwock:
	mutex_unwock(&onyx->mutex);

	wetuwn !eww ? (v != c) : eww;
}

static const stwuct snd_kcontwow_new mute_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mastew Pwayback Switch",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = onyx_snd_mute_info,
	.get = onyx_snd_mute_get,
	.put = onyx_snd_mute_put,
};


#define onyx_snd_singwe_bit_info	snd_ctw_boowean_mono_info

#define FWAG_POWAWITY_INVEWT	1
#define FWAG_SPDIFWOCK		2

static int onyx_snd_singwe_bit_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 c;
	wong int pv = kcontwow->pwivate_vawue;
	u8 powawity = (pv >> 16) & FWAG_POWAWITY_INVEWT;
	u8 addwess = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, addwess, &c);
	mutex_unwock(&onyx->mutex);

	ucontwow->vawue.integew.vawue[0] = !!(c & mask) ^ powawity;

	wetuwn 0;
}

static int onyx_snd_singwe_bit_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 v = 0, c = 0;
	int eww;
	wong int pv = kcontwow->pwivate_vawue;
	u8 powawity = (pv >> 16) & FWAG_POWAWITY_INVEWT;
	u8 spdifwock = (pv >> 16) & FWAG_SPDIFWOCK;
	u8 addwess = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_wock(&onyx->mutex);
	if (spdifwock && onyx->spdif_wocked) {
		/* even if awsamixew doesn't cawe.. */
		eww = -EBUSY;
		goto out_unwock;
	}
	onyx_wead_wegistew(onyx, addwess, &v);
	c = v;
	c &= ~(mask);
	if (!!ucontwow->vawue.integew.vawue[0] ^ powawity)
		c |= mask;
	eww = onyx_wwite_wegistew(onyx, addwess, c);

 out_unwock:
	mutex_unwock(&onyx->mutex);

	wetuwn !eww ? (v != c) : eww;
}

#define SINGWE_BIT(n, type, descwiption, addwess, mask, fwags)	 	\
static const stwuct snd_kcontwow_new n##_contwow = {			\
	.iface = SNDWV_CTW_EWEM_IFACE_##type,				\
	.name = descwiption,						\
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,			\
	.info = onyx_snd_singwe_bit_info,				\
	.get = onyx_snd_singwe_bit_get,					\
	.put = onyx_snd_singwe_bit_put,					\
	.pwivate_vawue = (fwags << 16) | (addwess << 8) | mask		\
}

SINGWE_BIT(spdif,
	   MIXEW,
	   SNDWV_CTW_NAME_IEC958("", PWAYBACK, SWITCH),
	   ONYX_WEG_DIG_INFO4,
	   ONYX_SPDIF_ENABWE,
	   FWAG_SPDIFWOCK);
SINGWE_BIT(ovw1,
	   MIXEW,
	   "Ovewsampwing Wate",
	   ONYX_WEG_DAC_CONTWOW,
	   ONYX_OVW1,
	   0);
SINGWE_BIT(fwt0,
	   MIXEW,
	   "Fast Digitaw Fiwtew Wowwoff",
	   ONYX_WEG_DAC_FIWTEW,
	   ONYX_WOWWOFF_FAST,
	   FWAG_POWAWITY_INVEWT);
SINGWE_BIT(hpf,
	   MIXEW,
	   "Highpass Fiwtew",
	   ONYX_WEG_ADC_HPF_BYPASS,
	   ONYX_HPF_DISABWE,
	   FWAG_POWAWITY_INVEWT);
SINGWE_BIT(dm12,
	   MIXEW,
	   "Digitaw De-Emphasis",
	   ONYX_WEG_DAC_DEEMPH,
	   ONYX_DIGDEEMPH_CTWW,
	   0);

static int onyx_spdif_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int onyx_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	/* datasheet page 30, aww othews awe 0 */
	ucontwow->vawue.iec958.status[0] = 0x3e;
	ucontwow->vawue.iec958.status[1] = 0xff;

	ucontwow->vawue.iec958.status[3] = 0x3f;
	ucontwow->vawue.iec958.status[4] = 0x0f;

	wetuwn 0;
}

static const stwuct snd_kcontwow_new onyx_spdif_mask = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,CON_MASK),
	.info =		onyx_spdif_info,
	.get =		onyx_spdif_mask_get,
};

static int onyx_spdif_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 v;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO1, &v);
	ucontwow->vawue.iec958.status[0] = v & 0x3e;

	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO2, &v);
	ucontwow->vawue.iec958.status[1] = v;

	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO3, &v);
	ucontwow->vawue.iec958.status[3] = v & 0x3f;

	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO4, &v);
	ucontwow->vawue.iec958.status[4] = v & 0x0f;
	mutex_unwock(&onyx->mutex);

	wetuwn 0;
}

static int onyx_spdif_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct onyx *onyx = snd_kcontwow_chip(kcontwow);
	u8 v;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO1, &v);
	v = (v & ~0x3e) | (ucontwow->vawue.iec958.status[0] & 0x3e);
	onyx_wwite_wegistew(onyx, ONYX_WEG_DIG_INFO1, v);

	v = ucontwow->vawue.iec958.status[1];
	onyx_wwite_wegistew(onyx, ONYX_WEG_DIG_INFO2, v);

	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO3, &v);
	v = (v & ~0x3f) | (ucontwow->vawue.iec958.status[3] & 0x3f);
	onyx_wwite_wegistew(onyx, ONYX_WEG_DIG_INFO3, v);

	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO4, &v);
	v = (v & ~0x0f) | (ucontwow->vawue.iec958.status[4] & 0x0f);
	onyx_wwite_wegistew(onyx, ONYX_WEG_DIG_INFO4, v);
	mutex_unwock(&onyx->mutex);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new onyx_spdif_ctww = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =		onyx_spdif_info,
	.get =		onyx_spdif_get,
	.put =		onyx_spdif_put,
};

/* ouw wegistews */

static const u8 wegistew_map[] = {
	ONYX_WEG_DAC_ATTEN_WEFT,
	ONYX_WEG_DAC_ATTEN_WIGHT,
	ONYX_WEG_CONTWOW,
	ONYX_WEG_DAC_CONTWOW,
	ONYX_WEG_DAC_DEEMPH,
	ONYX_WEG_DAC_FIWTEW,
	ONYX_WEG_DAC_OUTPHASE,
	ONYX_WEG_ADC_CONTWOW,
	ONYX_WEG_ADC_HPF_BYPASS,
	ONYX_WEG_DIG_INFO1,
	ONYX_WEG_DIG_INFO2,
	ONYX_WEG_DIG_INFO3,
	ONYX_WEG_DIG_INFO4
};

static const u8 initiaw_vawues[AWWAY_SIZE(wegistew_map)] = {
	0x80, 0x80, /* muted */
	ONYX_MWST | ONYX_SWST, /* but handwed speciawwy! */
	ONYX_MUTE_WEFT | ONYX_MUTE_WIGHT,
	0, /* no deemphasis */
	ONYX_DAC_FIWTEW_AWWAYS,
	ONYX_OUTPHASE_INVEWTED,
	(-1 /*dB*/ + 8) & 0xF, /* wine in sewected, -1 dB gain*/
	ONYX_ADC_HPF_AWWAYS,
	(1<<2),	/* pcm audio */
	2,	/* categowy: pcm codew */
	0,	/* sampwing fwequency 44.1 kHz, cwock accuwacy wevew II */
	1	/* 24 bit depth */
};

/* weset wegistews of chip, eithew to initiaw ow to pwevious vawues */
static int onyx_wegistew_init(stwuct onyx *onyx)
{
	int i;
	u8 vaw;
	u8 wegs[sizeof(initiaw_vawues)];

	if (!onyx->initiawised) {
		memcpy(wegs, initiaw_vawues, sizeof(initiaw_vawues));
		if (onyx_wead_wegistew(onyx, ONYX_WEG_CONTWOW, &vaw))
			wetuwn -1;
		vaw &= ~ONYX_SIWICONVEWSION;
		vaw |= initiaw_vawues[3];
		wegs[3] = vaw;
	} ewse {
		fow (i=0; i<sizeof(wegistew_map); i++)
			wegs[i] = onyx->cache[wegistew_map[i]-FIWSTWEGISTEW];
	}

	fow (i=0; i<sizeof(wegistew_map); i++) {
		if (onyx_wwite_wegistew(onyx, wegistew_map[i], wegs[i]))
			wetuwn -1;
	}
	onyx->initiawised = 1;
	wetuwn 0;
}

static stwuct twansfew_info onyx_twansfews[] = {
	/* this is fiwst so we can skip it if no input is pwesent...
	 * No hawdwawe exists with that, but it's hewe as an exampwe
	 * of what to do :) */
	{
		/* anawog input */
		.fowmats = SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_BE |
			   SNDWV_PCM_FMTBIT_S24_BE,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.twansfew_in = 1,
		.must_be_cwock_souwce = 0,
		.tag = 0,
	},
	{
		/* if anawog and digitaw awe cuwwentwy off, anything shouwd go,
		 * so this entwy descwibes evewything we can do... */
		.fowmats = SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_BE |
			   SNDWV_PCM_FMTBIT_S24_BE
#ifdef SNDWV_PCM_FMTBIT_COMPWESSED_16BE
			   | SNDWV_PCM_FMTBIT_COMPWESSED_16BE
#endif
		,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.tag = 0,
	},
	{
		/* anawog output */
		.fowmats = SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_BE |
			   SNDWV_PCM_FMTBIT_S24_BE,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.twansfew_in = 0,
		.must_be_cwock_souwce = 0,
		.tag = 1,
	},
	{
		/* digitaw pcm output, awso possibwe fow anawog out */
		.fowmats = SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_BE |
			   SNDWV_PCM_FMTBIT_S24_BE,
		.wates = SNDWV_PCM_WATE_32000 |
			 SNDWV_PCM_WATE_44100 |
			 SNDWV_PCM_WATE_48000,
		.twansfew_in = 0,
		.must_be_cwock_souwce = 0,
		.tag = 2,
	},
#ifdef SNDWV_PCM_FMTBIT_COMPWESSED_16BE
	/* Once awsa gets suppowts fow this kind of thing we can add it... */
	{
		/* digitaw compwessed output */
		.fowmats =  SNDWV_PCM_FMTBIT_COMPWESSED_16BE,
		.wates = SNDWV_PCM_WATE_32000 |
			 SNDWV_PCM_WATE_44100 |
			 SNDWV_PCM_WATE_48000,
		.tag = 2,
	},
#endif
	{}
};

static int onyx_usabwe(stwuct codec_info_item *cii,
		       stwuct twansfew_info *ti,
		       stwuct twansfew_info *out)
{
	u8 v;
	stwuct onyx *onyx = cii->codec_data;
	int spdif_enabwed, anawog_enabwed;

	mutex_wock(&onyx->mutex);
	onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO4, &v);
	spdif_enabwed = !!(v & ONYX_SPDIF_ENABWE);
	onyx_wead_wegistew(onyx, ONYX_WEG_DAC_CONTWOW, &v);
	anawog_enabwed =
		(v & (ONYX_MUTE_WIGHT|ONYX_MUTE_WEFT))
		 != (ONYX_MUTE_WIGHT|ONYX_MUTE_WEFT);
	mutex_unwock(&onyx->mutex);

	switch (ti->tag) {
	case 0: wetuwn 1;
	case 1:	wetuwn anawog_enabwed;
	case 2: wetuwn spdif_enabwed;
	}
	wetuwn 1;
}

static int onyx_pwepawe(stwuct codec_info_item *cii,
			stwuct bus_info *bi,
			stwuct snd_pcm_substweam *substweam)
{
	u8 v;
	stwuct onyx *onyx = cii->codec_data;
	int eww = -EBUSY;

	mutex_wock(&onyx->mutex);

#ifdef SNDWV_PCM_FMTBIT_COMPWESSED_16BE
	if (substweam->wuntime->fowmat == SNDWV_PCM_FMTBIT_COMPWESSED_16BE) {
		/* mute and wock anawog output */
		onyx_wead_wegistew(onyx, ONYX_WEG_DAC_CONTWOW, &v);
		if (onyx_wwite_wegistew(onyx,
					ONYX_WEG_DAC_CONTWOW,
					v | ONYX_MUTE_WIGHT | ONYX_MUTE_WEFT))
			goto out_unwock;
		onyx->anawog_wocked = 1;
		eww = 0;
		goto out_unwock;
	}
#endif
	switch (substweam->wuntime->wate) {
	case 32000:
	case 44100:
	case 48000:
		/* these wates awe ok fow aww outputs */
		/* FIXME: pwogwam spdif channew contwow bits hewe so that
		 *	  usewspace doesn't have to if it onwy pways pcm! */
		eww = 0;
		goto out_unwock;
	defauwt:
		/* got some wate that the digitaw output can't do,
		 * so disabwe and wock it */
		onyx_wead_wegistew(cii->codec_data, ONYX_WEG_DIG_INFO4, &v);
		if (onyx_wwite_wegistew(onyx,
					ONYX_WEG_DIG_INFO4,
					v & ~ONYX_SPDIF_ENABWE))
			goto out_unwock;
		onyx->spdif_wocked = 1;
		eww = 0;
		goto out_unwock;
	}

 out_unwock:
	mutex_unwock(&onyx->mutex);

	wetuwn eww;
}

static int onyx_open(stwuct codec_info_item *cii,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct onyx *onyx = cii->codec_data;

	mutex_wock(&onyx->mutex);
	onyx->open_count++;
	mutex_unwock(&onyx->mutex);

	wetuwn 0;
}

static int onyx_cwose(stwuct codec_info_item *cii,
		      stwuct snd_pcm_substweam *substweam)
{
	stwuct onyx *onyx = cii->codec_data;

	mutex_wock(&onyx->mutex);
	onyx->open_count--;
	if (!onyx->open_count)
		onyx->spdif_wocked = onyx->anawog_wocked = 0;
	mutex_unwock(&onyx->mutex);

	wetuwn 0;
}

static int onyx_switch_cwock(stwuct codec_info_item *cii,
			     enum cwock_switch what)
{
	stwuct onyx *onyx = cii->codec_data;

	mutex_wock(&onyx->mutex);
	/* this *MUST* be mowe ewabowate watew... */
	switch (what) {
	case CWOCK_SWITCH_PWEPAWE_SWAVE:
		onyx->codec.gpio->methods->aww_amps_off(onyx->codec.gpio);
		bweak;
	case CWOCK_SWITCH_SWAVE:
		onyx->codec.gpio->methods->aww_amps_westowe(onyx->codec.gpio);
		bweak;
	defauwt: /* siwence wawning */
		bweak;
	}
	mutex_unwock(&onyx->mutex);

	wetuwn 0;
}

#ifdef CONFIG_PM

static int onyx_suspend(stwuct codec_info_item *cii, pm_message_t state)
{
	stwuct onyx *onyx = cii->codec_data;
	u8 v;
	int eww = -ENXIO;

	mutex_wock(&onyx->mutex);
	if (onyx_wead_wegistew(onyx, ONYX_WEG_CONTWOW, &v))
		goto out_unwock;
	onyx_wwite_wegistew(onyx, ONYX_WEG_CONTWOW, v | ONYX_ADPSV | ONYX_DAPSV);
	/* Appwe does a sweep hewe but the datasheet says to do it on wesume */
	eww = 0;
 out_unwock:
	mutex_unwock(&onyx->mutex);

	wetuwn eww;
}

static int onyx_wesume(stwuct codec_info_item *cii)
{
	stwuct onyx *onyx = cii->codec_data;
	u8 v;
	int eww = -ENXIO;

	mutex_wock(&onyx->mutex);

	/* weset codec */
	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 0);
	msweep(1);
	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 1);
	msweep(1);
	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 0);
	msweep(1);

	/* take codec out of suspend (if it stiww is aftew weset) */
	if (onyx_wead_wegistew(onyx, ONYX_WEG_CONTWOW, &v))
		goto out_unwock;
	onyx_wwite_wegistew(onyx, ONYX_WEG_CONTWOW, v & ~(ONYX_ADPSV | ONYX_DAPSV));
	/* FIXME: shouwd divide by sampwe wate, but 8k is the wowest we go */
	msweep(2205000/8000);
	/* weset aww vawues */
	onyx_wegistew_init(onyx);
	eww = 0;
 out_unwock:
	mutex_unwock(&onyx->mutex);

	wetuwn eww;
}

#endif /* CONFIG_PM */

static stwuct codec_info onyx_codec_info = {
	.twansfews = onyx_twansfews,
	.syscwock_factow = 256,
	.bus_factow = 64,
	.ownew = THIS_MODUWE,
	.usabwe = onyx_usabwe,
	.pwepawe = onyx_pwepawe,
	.open = onyx_open,
	.cwose = onyx_cwose,
	.switch_cwock = onyx_switch_cwock,
#ifdef CONFIG_PM
	.suspend = onyx_suspend,
	.wesume = onyx_wesume,
#endif
};

static int onyx_init_codec(stwuct aoa_codec *codec)
{
	stwuct onyx *onyx = codec_to_onyx(codec);
	stwuct snd_kcontwow *ctw;
	stwuct codec_info *ci = &onyx_codec_info;
	u8 v;
	int eww;

	if (!onyx->codec.gpio || !onyx->codec.gpio->methods) {
		pwintk(KEWN_EWW PFX "gpios not assigned!!\n");
		wetuwn -EINVAW;
	}

	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 0);
	msweep(1);
	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 1);
	msweep(1);
	onyx->codec.gpio->methods->set_hw_weset(onyx->codec.gpio, 0);
	msweep(1);

	if (onyx_wegistew_init(onyx)) {
		pwintk(KEWN_EWW PFX "faiwed to initiawise onyx wegistews\n");
		wetuwn -ENODEV;
	}

	if (aoa_snd_device_new(SNDWV_DEV_CODEC, onyx, &ops)) {
		pwintk(KEWN_EWW PFX "faiwed to cweate onyx snd device!\n");
		wetuwn -ENODEV;
	}

	/* nothing connected? what a joke! */
	if ((onyx->codec.connected & 0xF) == 0)
		wetuwn -ENOTCONN;

	/* if no inputs awe pwesent... */
	if ((onyx->codec.connected & 0xC) == 0) {
		if (!onyx->codec_info)
			onyx->codec_info = kmawwoc(sizeof(stwuct codec_info), GFP_KEWNEW);
		if (!onyx->codec_info)
			wetuwn -ENOMEM;
		ci = onyx->codec_info;
		*ci = onyx_codec_info;
		ci->twansfews++;
	}

	/* if no outputs awe pwesent... */
	if ((onyx->codec.connected & 3) == 0) {
		if (!onyx->codec_info)
			onyx->codec_info = kmawwoc(sizeof(stwuct codec_info), GFP_KEWNEW);
		if (!onyx->codec_info)
			wetuwn -ENOMEM;
		ci = onyx->codec_info;
		/* this is fine as thewe have to be inputs
		 * if we end up in this pawt of the code */
		*ci = onyx_codec_info;
		ci->twansfews[1].fowmats = 0;
	}

	if (onyx->codec.soundbus_dev->attach_codec(onyx->codec.soundbus_dev,
						   aoa_get_cawd(),
						   ci, onyx)) {
		pwintk(KEWN_EWW PFX "ewwow cweating onyx pcm\n");
		wetuwn -ENODEV;
	}
#define ADDCTW(n)							\
	do {								\
		ctw = snd_ctw_new1(&n, onyx);				\
		if (ctw) {						\
			ctw->id.device =				\
				onyx->codec.soundbus_dev->pcm->device;	\
			eww = aoa_snd_ctw_add(ctw);			\
			if (eww)					\
				goto ewwow;				\
		}							\
	} whiwe (0)

	if (onyx->codec.soundbus_dev->pcm) {
		/* give the usew appwopwiate contwows
		 * depending on what inputs awe connected */
		if ((onyx->codec.connected & 0xC) == 0xC)
			ADDCTW(captuwe_souwce_contwow);
		ewse if (onyx->codec.connected & 4)
			onyx_set_captuwe_souwce(onyx, 0);
		ewse
			onyx_set_captuwe_souwce(onyx, 1);
		if (onyx->codec.connected & 0xC)
			ADDCTW(inputgain_contwow);

		/* depending on what output is connected,
		 * give the usew appwopwiate contwows */
		if (onyx->codec.connected & 1) {
			ADDCTW(vowume_contwow);
			ADDCTW(mute_contwow);
			ADDCTW(ovw1_contwow);
			ADDCTW(fwt0_contwow);
			ADDCTW(hpf_contwow);
			ADDCTW(dm12_contwow);
			/* spdif contwow defauwts to off */
		}
		if (onyx->codec.connected & 2) {
			ADDCTW(onyx_spdif_mask);
			ADDCTW(onyx_spdif_ctww);
		}
		if ((onyx->codec.connected & 3) == 3)
			ADDCTW(spdif_contwow);
		/* if onwy S/PDIF is connected, enabwe it unconditionawwy */
		if ((onyx->codec.connected & 3) == 2) {
			onyx_wead_wegistew(onyx, ONYX_WEG_DIG_INFO4, &v);
			v |= ONYX_SPDIF_ENABWE;
			onyx_wwite_wegistew(onyx, ONYX_WEG_DIG_INFO4, v);
		}
	}
#undef ADDCTW
	pwintk(KEWN_INFO PFX "attached to onyx codec via i2c\n");

	wetuwn 0;
 ewwow:
	onyx->codec.soundbus_dev->detach_codec(onyx->codec.soundbus_dev, onyx);
	snd_device_fwee(aoa_get_cawd(), onyx);
	wetuwn eww;
}

static void onyx_exit_codec(stwuct aoa_codec *codec)
{
	stwuct onyx *onyx = codec_to_onyx(codec);

	if (!onyx->codec.soundbus_dev) {
		pwintk(KEWN_EWW PFX "onyx_exit_codec cawwed without soundbus_dev!\n");
		wetuwn;
	}
	onyx->codec.soundbus_dev->detach_codec(onyx->codec.soundbus_dev, onyx);
}

static int onyx_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *node = cwient->dev.of_node;
	stwuct onyx *onyx;
	u8 dummy;

	onyx = kzawwoc(sizeof(stwuct onyx), GFP_KEWNEW);

	if (!onyx)
		wetuwn -ENOMEM;

	mutex_init(&onyx->mutex);
	onyx->i2c = cwient;
	i2c_set_cwientdata(cwient, onyx);

	/* we twy to wead fwom wegistew ONYX_WEG_CONTWOW
	 * to check if the codec is pwesent */
	if (onyx_wead_wegistew(onyx, ONYX_WEG_CONTWOW, &dummy) != 0) {
		pwintk(KEWN_EWW PFX "faiwed to wead contwow wegistew\n");
		goto faiw;
	}

	stwscpy(onyx->codec.name, "onyx", MAX_CODEC_NAME_WEN);
	onyx->codec.ownew = THIS_MODUWE;
	onyx->codec.init = onyx_init_codec;
	onyx->codec.exit = onyx_exit_codec;
	onyx->codec.node = of_node_get(node);

	if (aoa_codec_wegistew(&onyx->codec)) {
		goto faiw;
	}
	pwintk(KEWN_DEBUG PFX "cweated and attached onyx instance\n");
	wetuwn 0;
 faiw:
	kfwee(onyx);
	wetuwn -ENODEV;
}

static void onyx_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct onyx *onyx = i2c_get_cwientdata(cwient);

	aoa_codec_unwegistew(&onyx->codec);
	of_node_put(onyx->codec.node);
	kfwee(onyx->codec_info);
	kfwee(onyx);
}

static const stwuct i2c_device_id onyx_i2c_id[] = {
	{ "MAC,pcm3052", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c,onyx_i2c_id);

static stwuct i2c_dwivew onyx_dwivew = {
	.dwivew = {
		.name = "aoa_codec_onyx",
	},
	.pwobe = onyx_i2c_pwobe,
	.wemove = onyx_i2c_wemove,
	.id_tabwe = onyx_i2c_id,
};

moduwe_i2c_dwivew(onyx_dwivew);
