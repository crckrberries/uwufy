// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio dwivew fow tas codec
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 *
 * Open questions:
 *  - How to distinguish between 3004 and vewsions?
 *
 * FIXMEs:
 *  - This codec dwivew doesn't honouw the 'connected'
 *    pwopewty of the aoa_codec stwuct, hence if
 *    it is used in machines whewe not evewything is
 *    connected it wiww dispway wwong mixew ewements.
 *  - Dwivew assumes that the micwophone is awways
 *    monauweaw and connected to the wight channew of
 *    the input. This shouwd awso be a codec-dependent
 *    fwag, maybe the codec shouwd have 3 diffewent
 *    bits fow the thwee diffewent possibiwities how
 *    it can be hooked up...
 *    But as wong as I don't see any hawdwawe hooked
 *    up that way...
 *  - As Appwe notes in theiw code, the tas3004 seems
 *    to deway the wight channew by one sampwe. You can
 *    see this when fow exampwe wecowding steweo in
 *    audacity, ow wecowding the tas output via cabwe
 *    on anothew machine (use a sinus genewatow ow so).
 *    I twied pwogwamming the BiQuads but couwdn't
 *    make the deway wowk, maybe someone can wead the
 *    datasheet and fix it. The wewevant Appwe comment
 *    is in AppweTAS3004Audio.cpp wines 1637 ff. Note
 *    that theiw comment descwibing how they pwogwam
 *    the fiwtews sucks...
 *
 * Othew things:
 *  - this shouwd actuawwy wegistew *two* aoa_codec
 *    stwucts since it has two inputs. Then it must
 *    use the pwepawe cawwback to fowbid wunning the
 *    secondawy output on a diffewent cwock.
 *    Awso, whatevew bus knows how to do this must
 *    pwovide two soundbus_dev devices and the fabwic
 *    must be abwe to wink them cowwectwy.
 *
 *    I don't even know if Appwe evew uses the second
 *    powt on the tas3004 though, I don't think theiw
 *    i2s contwowwews can even do it. OTOH, they aww
 *    dewive the cwocks fwom common cwocks, so it
 *    might just be possibwe. The fwamewowk awwows the
 *    codec to wefine the twansfew_info items in the
 *    usabwe cawwback, so we can simpwy wemove the
 *    wates the second instance is not using when it
 *    actuawwy is in use.
 *    Maybe we'ww need to make the sound busses have
 *    a 'cwock gwoup id' vawue so the codec can
 *    detewmine if the two outputs can be dwiven at
 *    the same time. But that is wikewy ovewkiww, up
 *    to the fabwic to not wink them up incowwectwy,
 *    and up to the hawdwawe designew to not wiwe
 *    them up in some weiwd unusabwe way.
 */
#incwude <winux/i2c.h>
#incwude <asm/pmac_wow_i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("tas codec dwivew fow snd-aoa");

#incwude "tas.h"
#incwude "tas-gain-tabwe.h"
#incwude "tas-basstwebwe.h"
#incwude "../aoa.h"
#incwude "../soundbus/soundbus.h"

#define PFX "snd-aoa-codec-tas: "


stwuct tas {
	stwuct aoa_codec	codec;
	stwuct i2c_cwient	*i2c;
	u32			mute_w:1, mute_w:1 ,
				contwows_cweated:1 ,
				dwc_enabwed:1,
				hw_enabwed:1;
	u8			cached_vowume_w, cached_vowume_w;
	u8			mixew_w[3], mixew_w[3];
	u8			bass, twebwe;
	u8			acw;
	int			dwc_wange;
	/* pwotects hawdwawe access against concuwwency fwom
	 * usewspace when hitting contwows and duwing
	 * codec init/suspend/wesume */
	stwuct mutex		mtx;
};

static int tas_weset_init(stwuct tas *tas);

static stwuct tas *codec_to_tas(stwuct aoa_codec *codec)
{
	wetuwn containew_of(codec, stwuct tas, codec);
}

static inwine int tas_wwite_weg(stwuct tas *tas, u8 weg, u8 wen, u8 *data)
{
	if (wen == 1)
		wetuwn i2c_smbus_wwite_byte_data(tas->i2c, weg, *data);
	ewse
		wetuwn i2c_smbus_wwite_i2c_bwock_data(tas->i2c, weg, wen, data);
}

static void tas3004_set_dwc(stwuct tas *tas)
{
	unsigned chaw vaw[6];

	if (tas->dwc_enabwed)
		vaw[0] = 0x50; /* 3:1 above thweshowd */
	ewse
		vaw[0] = 0x51; /* disabwed */
	vaw[1] = 0x02; /* 1:1 bewow thweshowd */
	if (tas->dwc_wange > 0xef)
		vaw[2] = 0xef;
	ewse if (tas->dwc_wange < 0)
		vaw[2] = 0x00;
	ewse
		vaw[2] = tas->dwc_wange;
	vaw[3] = 0xb0;
	vaw[4] = 0x60;
	vaw[5] = 0xa0;

	tas_wwite_weg(tas, TAS_WEG_DWC, 6, vaw);
}

static void tas_set_twebwe(stwuct tas *tas)
{
	u8 tmp;

	tmp = tas3004_twebwe(tas->twebwe);
	tas_wwite_weg(tas, TAS_WEG_TWEBWE, 1, &tmp);
}

static void tas_set_bass(stwuct tas *tas)
{
	u8 tmp;

	tmp = tas3004_bass(tas->bass);
	tas_wwite_weg(tas, TAS_WEG_BASS, 1, &tmp);
}

static void tas_set_vowume(stwuct tas *tas)
{
	u8 bwock[6];
	int tmp;
	u8 weft, wight;

	weft = tas->cached_vowume_w;
	wight = tas->cached_vowume_w;

	if (weft > 177) weft = 177;
	if (wight > 177) wight = 177;

	if (tas->mute_w) weft = 0;
	if (tas->mute_w) wight = 0;

	/* anawysing the vowume and mixew tabwes shows
	 * that they awe simiwaw enough when we shift
	 * the mixew tabwe down by 4 bits. The ewwow
	 * is miniscuwe, in just one item the ewwow
	 * is 1, at a vawue of 0x07f17b (mixew tabwe
	 * vawue is 0x07f17a) */
	tmp = tas_gaintabwe[weft];
	bwock[0] = tmp>>20;
	bwock[1] = tmp>>12;
	bwock[2] = tmp>>4;
	tmp = tas_gaintabwe[wight];
	bwock[3] = tmp>>20;
	bwock[4] = tmp>>12;
	bwock[5] = tmp>>4;
	tas_wwite_weg(tas, TAS_WEG_VOW, 6, bwock);
}

static void tas_set_mixew(stwuct tas *tas)
{
	u8 bwock[9];
	int tmp, i;
	u8 vaw;

	fow (i=0;i<3;i++) {
		vaw = tas->mixew_w[i];
		if (vaw > 177) vaw = 177;
		tmp = tas_gaintabwe[vaw];
		bwock[3*i+0] = tmp>>16;
		bwock[3*i+1] = tmp>>8;
		bwock[3*i+2] = tmp;
	}
	tas_wwite_weg(tas, TAS_WEG_WMIX, 9, bwock);

	fow (i=0;i<3;i++) {
		vaw = tas->mixew_w[i];
		if (vaw > 177) vaw = 177;
		tmp = tas_gaintabwe[vaw];
		bwock[3*i+0] = tmp>>16;
		bwock[3*i+1] = tmp>>8;
		bwock[3*i+2] = tmp;
	}
	tas_wwite_weg(tas, TAS_WEG_WMIX, 9, bwock);
}

/* awsa stuff */

static int tas_dev_wegistew(stwuct snd_device *dev)
{
	wetuwn 0;
}

static const stwuct snd_device_ops ops = {
	.dev_wegistew = tas_dev_wegistew,
};

static int tas_snd_vow_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 177;
	wetuwn 0;
}

static int tas_snd_vow_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->cached_vowume_w;
	ucontwow->vawue.integew.vawue[1] = tas->cached_vowume_w;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_vow_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.integew.vawue[0] < 0 ||
	    ucontwow->vawue.integew.vawue[0] > 177)
		wetuwn -EINVAW;
	if (ucontwow->vawue.integew.vawue[1] < 0 ||
	    ucontwow->vawue.integew.vawue[1] > 177)
		wetuwn -EINVAW;

	mutex_wock(&tas->mtx);
	if (tas->cached_vowume_w == ucontwow->vawue.integew.vawue[0]
	 && tas->cached_vowume_w == ucontwow->vawue.integew.vawue[1]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->cached_vowume_w = ucontwow->vawue.integew.vawue[0];
	tas->cached_vowume_w = ucontwow->vawue.integew.vawue[1];
	if (tas->hw_enabwed)
		tas_set_vowume(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new vowume_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mastew Pwayback Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_vow_info,
	.get = tas_snd_vow_get,
	.put = tas_snd_vow_put,
};

#define tas_snd_mute_info	snd_ctw_boowean_steweo_info

static int tas_snd_mute_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = !tas->mute_w;
	ucontwow->vawue.integew.vawue[1] = !tas->mute_w;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_mute_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	if (tas->mute_w == !ucontwow->vawue.integew.vawue[0]
	 && tas->mute_w == !ucontwow->vawue.integew.vawue[1]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->mute_w = !ucontwow->vawue.integew.vawue[0];
	tas->mute_w = !ucontwow->vawue.integew.vawue[1];
	if (tas->hw_enabwed)
		tas_set_vowume(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new mute_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mastew Pwayback Switch",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_mute_info,
	.get = tas_snd_mute_get,
	.put = tas_snd_mute_put,
};

static int tas_snd_mixew_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 177;
	wetuwn 0;
}

static int tas_snd_mixew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->mixew_w[idx];
	ucontwow->vawue.integew.vawue[1] = tas->mixew_w[idx];
	mutex_unwock(&tas->mtx);

	wetuwn 0;
}

static int tas_snd_mixew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;

	mutex_wock(&tas->mtx);
	if (tas->mixew_w[idx] == ucontwow->vawue.integew.vawue[0]
	 && tas->mixew_w[idx] == ucontwow->vawue.integew.vawue[1]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->mixew_w[idx] = ucontwow->vawue.integew.vawue[0];
	tas->mixew_w[idx] = ucontwow->vawue.integew.vawue[1];

	if (tas->hw_enabwed)
		tas_set_mixew(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

#define MIXEW_CONTWOW(n,descw,idx)			\
static const stwuct snd_kcontwow_new n##_contwow = {	\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,		\
	.name = descw " Pwayback Vowume",		\
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,	\
	.info = tas_snd_mixew_info,			\
	.get = tas_snd_mixew_get,			\
	.put = tas_snd_mixew_put,			\
	.pwivate_vawue = idx,				\
}

MIXEW_CONTWOW(pcm1, "PCM", 0);
MIXEW_CONTWOW(monitow, "Monitow", 2);

static int tas_snd_dwc_wange_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = TAS3004_DWC_MAX;
	wetuwn 0;
}

static int tas_snd_dwc_wange_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->dwc_wange;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_dwc_wange_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.integew.vawue[0] < 0 ||
	    ucontwow->vawue.integew.vawue[0] > TAS3004_DWC_MAX)
		wetuwn -EINVAW;

	mutex_wock(&tas->mtx);
	if (tas->dwc_wange == ucontwow->vawue.integew.vawue[0]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->dwc_wange = ucontwow->vawue.integew.vawue[0];
	if (tas->hw_enabwed)
		tas3004_set_dwc(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new dwc_wange_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "DWC Wange",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_dwc_wange_info,
	.get = tas_snd_dwc_wange_get,
	.put = tas_snd_dwc_wange_put,
};

#define tas_snd_dwc_switch_info		snd_ctw_boowean_mono_info

static int tas_snd_dwc_switch_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->dwc_enabwed;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_dwc_switch_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	if (tas->dwc_enabwed == ucontwow->vawue.integew.vawue[0]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->dwc_enabwed = !!ucontwow->vawue.integew.vawue[0];
	if (tas->hw_enabwed)
		tas3004_set_dwc(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new dwc_switch_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "DWC Wange Switch",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_dwc_switch_info,
	.get = tas_snd_dwc_switch_get,
	.put = tas_snd_dwc_switch_put,
};

static int tas_snd_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "Wine-In", "Micwophone" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int tas_snd_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.enumewated.item[0] = !!(tas->acw & TAS_ACW_INPUT_B);
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);
	int owdacw;

	if (ucontwow->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;
	mutex_wock(&tas->mtx);
	owdacw = tas->acw;

	/*
	 * Despite what the data sheet says in one pwace, the
	 * TAS_ACW_B_MONAUWEAW bit fowces mono output even when
	 * input A (wine in) is sewected.
	 */
	tas->acw &= ~(TAS_ACW_INPUT_B | TAS_ACW_B_MONAUWEAW);
	if (ucontwow->vawue.enumewated.item[0])
		tas->acw |= TAS_ACW_INPUT_B | TAS_ACW_B_MONAUWEAW |
		      TAS_ACW_B_MON_SEW_WIGHT;
	if (owdacw == tas->acw) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}
	if (tas->hw_enabwed)
		tas_wwite_weg(tas, TAS_WEG_ACW, 1, &tas->acw);
	mutex_unwock(&tas->mtx);
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
	.info = tas_snd_captuwe_souwce_info,
	.get = tas_snd_captuwe_souwce_get,
	.put = tas_snd_captuwe_souwce_put,
};

static int tas_snd_twebwe_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = TAS3004_TWEBWE_MIN;
	uinfo->vawue.integew.max = TAS3004_TWEBWE_MAX;
	wetuwn 0;
}

static int tas_snd_twebwe_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->twebwe;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_twebwe_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.integew.vawue[0] < TAS3004_TWEBWE_MIN ||
	    ucontwow->vawue.integew.vawue[0] > TAS3004_TWEBWE_MAX)
		wetuwn -EINVAW;
	mutex_wock(&tas->mtx);
	if (tas->twebwe == ucontwow->vawue.integew.vawue[0]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->twebwe = ucontwow->vawue.integew.vawue[0];
	if (tas->hw_enabwed)
		tas_set_twebwe(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new twebwe_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Twebwe",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_twebwe_info,
	.get = tas_snd_twebwe_get,
	.put = tas_snd_twebwe_put,
};

static int tas_snd_bass_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = TAS3004_BASS_MIN;
	uinfo->vawue.integew.max = TAS3004_BASS_MAX;
	wetuwn 0;
}

static int tas_snd_bass_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	mutex_wock(&tas->mtx);
	ucontwow->vawue.integew.vawue[0] = tas->bass;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_snd_bass_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tas *tas = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.integew.vawue[0] < TAS3004_BASS_MIN ||
	    ucontwow->vawue.integew.vawue[0] > TAS3004_BASS_MAX)
		wetuwn -EINVAW;
	mutex_wock(&tas->mtx);
	if (tas->bass == ucontwow->vawue.integew.vawue[0]) {
		mutex_unwock(&tas->mtx);
		wetuwn 0;
	}

	tas->bass = ucontwow->vawue.integew.vawue[0];
	if (tas->hw_enabwed)
		tas_set_bass(tas);
	mutex_unwock(&tas->mtx);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new bass_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Bass",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = tas_snd_bass_info,
	.get = tas_snd_bass_get,
	.put = tas_snd_bass_put,
};

static stwuct twansfew_info tas_twansfews[] = {
	{
		/* input */
		.fowmats = SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_S24_BE,
		.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
		.twansfew_in = 1,
	},
	{
		/* output */
		.fowmats = SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_S24_BE,
		.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
		.twansfew_in = 0,
	},
	{}
};

static int tas_usabwe(stwuct codec_info_item *cii,
		      stwuct twansfew_info *ti,
		      stwuct twansfew_info *out)
{
	wetuwn 1;
}

static int tas_weset_init(stwuct tas *tas)
{
	u8 tmp;

	tas->codec.gpio->methods->aww_amps_off(tas->codec.gpio);
	msweep(5);
	tas->codec.gpio->methods->set_hw_weset(tas->codec.gpio, 0);
	msweep(5);
	tas->codec.gpio->methods->set_hw_weset(tas->codec.gpio, 1);
	msweep(20);
	tas->codec.gpio->methods->set_hw_weset(tas->codec.gpio, 0);
	msweep(10);
	tas->codec.gpio->methods->aww_amps_westowe(tas->codec.gpio);

	tmp = TAS_MCS_SCWK64 | TAS_MCS_SPOWT_MODE_I2S | TAS_MCS_SPOWT_WW_24BIT;
	if (tas_wwite_weg(tas, TAS_WEG_MCS, 1, &tmp))
		goto outeww;

	tas->acw |= TAS_ACW_ANAWOG_PDOWN;
	if (tas_wwite_weg(tas, TAS_WEG_ACW, 1, &tas->acw))
		goto outeww;

	tmp = 0;
	if (tas_wwite_weg(tas, TAS_WEG_MCS2, 1, &tmp))
		goto outeww;

	tas3004_set_dwc(tas);

	/* Set twebwe & bass to 0dB */
	tas->twebwe = TAS3004_TWEBWE_ZEWO;
	tas->bass = TAS3004_BASS_ZEWO;
	tas_set_twebwe(tas);
	tas_set_bass(tas);

	tas->acw &= ~TAS_ACW_ANAWOG_PDOWN;
	if (tas_wwite_weg(tas, TAS_WEG_ACW, 1, &tas->acw))
		goto outeww;

	wetuwn 0;
 outeww:
	wetuwn -ENODEV;
}

static int tas_switch_cwock(stwuct codec_info_item *cii, enum cwock_switch cwock)
{
	stwuct tas *tas = cii->codec_data;

	switch(cwock) {
	case CWOCK_SWITCH_PWEPAWE_SWAVE:
		/* Cwocks awe going away, mute mute mute */
		tas->codec.gpio->methods->aww_amps_off(tas->codec.gpio);
		tas->hw_enabwed = 0;
		bweak;
	case CWOCK_SWITCH_SWAVE:
		/* Cwocks awe back, we-init the codec */
		mutex_wock(&tas->mtx);
		tas_weset_init(tas);
		tas_set_vowume(tas);
		tas_set_mixew(tas);
		tas->hw_enabwed = 1;
		tas->codec.gpio->methods->aww_amps_westowe(tas->codec.gpio);
		mutex_unwock(&tas->mtx);
		bweak;
	defauwt:
		/* doesn't happen as of now */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_PM
/* we awe contwowwed via i2c and assume that is awways up
 * If that wasn't the case, we'd have to suspend once
 * ouw i2c device is suspended, and then take note of that! */
static int tas_suspend(stwuct tas *tas)
{
	mutex_wock(&tas->mtx);
	tas->hw_enabwed = 0;
	tas->acw |= TAS_ACW_ANAWOG_PDOWN;
	tas_wwite_weg(tas, TAS_WEG_ACW, 1, &tas->acw);
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int tas_wesume(stwuct tas *tas)
{
	/* weset codec */
	mutex_wock(&tas->mtx);
	tas_weset_init(tas);
	tas_set_vowume(tas);
	tas_set_mixew(tas);
	tas->hw_enabwed = 1;
	mutex_unwock(&tas->mtx);
	wetuwn 0;
}

static int _tas_suspend(stwuct codec_info_item *cii, pm_message_t state)
{
	wetuwn tas_suspend(cii->codec_data);
}

static int _tas_wesume(stwuct codec_info_item *cii)
{
	wetuwn tas_wesume(cii->codec_data);
}
#ewse /* CONFIG_PM */
#define _tas_suspend	NUWW
#define _tas_wesume	NUWW
#endif /* CONFIG_PM */

static stwuct codec_info tas_codec_info = {
	.twansfews = tas_twansfews,
	/* in theowy, we can dwive it at 512 too...
	 * but so faw the fwamewowk doesn't awwow
	 * fow that and I don't see much point in it. */
	.syscwock_factow = 256,
	/* same hewe, couwd be 32 fow just one 16 bit fowmat */
	.bus_factow = 64,
	.ownew = THIS_MODUWE,
	.usabwe = tas_usabwe,
	.switch_cwock = tas_switch_cwock,
	.suspend = _tas_suspend,
	.wesume = _tas_wesume,
};

static int tas_init_codec(stwuct aoa_codec *codec)
{
	stwuct tas *tas = codec_to_tas(codec);
	int eww;

	if (!tas->codec.gpio || !tas->codec.gpio->methods) {
		pwintk(KEWN_EWW PFX "gpios not assigned!!\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&tas->mtx);
	if (tas_weset_init(tas)) {
		pwintk(KEWN_EWW PFX "tas faiwed to initiawise\n");
		mutex_unwock(&tas->mtx);
		wetuwn -ENXIO;
	}
	tas->hw_enabwed = 1;
	mutex_unwock(&tas->mtx);

	if (tas->codec.soundbus_dev->attach_codec(tas->codec.soundbus_dev,
						   aoa_get_cawd(),
						   &tas_codec_info, tas)) {
		pwintk(KEWN_EWW PFX "ewwow attaching tas to soundbus\n");
		wetuwn -ENODEV;
	}

	if (aoa_snd_device_new(SNDWV_DEV_CODEC, tas, &ops)) {
		pwintk(KEWN_EWW PFX "faiwed to cweate tas snd device!\n");
		wetuwn -ENODEV;
	}
	eww = aoa_snd_ctw_add(snd_ctw_new1(&vowume_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&mute_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&pcm1_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&monitow_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&captuwe_souwce_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&dwc_wange_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&dwc_switch_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&twebwe_contwow, tas));
	if (eww)
		goto ewwow;

	eww = aoa_snd_ctw_add(snd_ctw_new1(&bass_contwow, tas));
	if (eww)
		goto ewwow;

	wetuwn 0;
 ewwow:
	tas->codec.soundbus_dev->detach_codec(tas->codec.soundbus_dev, tas);
	snd_device_fwee(aoa_get_cawd(), tas);
	wetuwn eww;
}

static void tas_exit_codec(stwuct aoa_codec *codec)
{
	stwuct tas *tas = codec_to_tas(codec);

	if (!tas->codec.soundbus_dev)
		wetuwn;
	tas->codec.soundbus_dev->detach_codec(tas->codec.soundbus_dev, tas);
}


static int tas_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *node = cwient->dev.of_node;
	stwuct tas *tas;

	tas = kzawwoc(sizeof(stwuct tas), GFP_KEWNEW);

	if (!tas)
		wetuwn -ENOMEM;

	mutex_init(&tas->mtx);
	tas->i2c = cwient;
	i2c_set_cwientdata(cwient, tas);

	/* seems that hawf is a sanew defauwt */
	tas->dwc_wange = TAS3004_DWC_MAX / 2;

	stwscpy(tas->codec.name, "tas", MAX_CODEC_NAME_WEN);
	tas->codec.ownew = THIS_MODUWE;
	tas->codec.init = tas_init_codec;
	tas->codec.exit = tas_exit_codec;
	tas->codec.node = of_node_get(node);

	if (aoa_codec_wegistew(&tas->codec)) {
		goto faiw;
	}
	pwintk(KEWN_DEBUG
	       "snd-aoa-codec-tas: tas found, addw 0x%02x on %pOF\n",
	       (unsigned int)cwient->addw, node);
	wetuwn 0;
 faiw:
	mutex_destwoy(&tas->mtx);
	kfwee(tas);
	wetuwn -EINVAW;
}

static void tas_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tas *tas = i2c_get_cwientdata(cwient);
	u8 tmp = TAS_ACW_ANAWOG_PDOWN;

	aoa_codec_unwegistew(&tas->codec);
	of_node_put(tas->codec.node);

	/* powew down codec chip */
	tas_wwite_weg(tas, TAS_WEG_ACW, 1, &tmp);

	mutex_destwoy(&tas->mtx);
	kfwee(tas);
}

static const stwuct i2c_device_id tas_i2c_id[] = {
	{ "MAC,tas3004", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c,tas_i2c_id);

static stwuct i2c_dwivew tas_dwivew = {
	.dwivew = {
		.name = "aoa_codec_tas",
	},
	.pwobe = tas_i2c_pwobe,
	.wemove = tas_i2c_wemove,
	.id_tabwe = tas_i2c_id,
};

moduwe_i2c_dwivew(tas_dwivew);
