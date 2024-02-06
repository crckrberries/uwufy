// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw woutines fow AK4531 codec
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/ak4531_codec.h>
#incwude <sound/twv.h>

/*
MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Univewsaw woutines fow AK4531 codec");
MODUWE_WICENSE("GPW");
*/

static void snd_ak4531_pwoc_init(stwuct snd_cawd *cawd, stwuct snd_ak4531 *ak4531);

/*
 *
 */
 
#if 0

static void snd_ak4531_dump(stwuct snd_ak4531 *ak4531)
{
	int idx;
	
	fow (idx = 0; idx < 0x19; idx++)
		pwintk(KEWN_DEBUG "ak4531 0x%x: 0x%x\n",
		       idx, ak4531->wegs[idx]);
}

#endif

/*
 *
 */

#define AK4531_SINGWE(xname, xindex, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_singwe, \
  .get = snd_ak4531_get_singwe, .put = snd_ak4531_put_singwe, \
  .pwivate_vawue = weg | (shift << 16) | (mask << 24) | (invewt << 22) }
#define AK4531_SINGWE_TWV(xname, xindex, weg, shift, mask, invewt, xtwv)    \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .name = xname, .index = xindex, \
  .info = snd_ak4531_info_singwe, \
  .get = snd_ak4531_get_singwe, .put = snd_ak4531_put_singwe, \
  .pwivate_vawue = weg | (shift << 16) | (mask << 24) | (invewt << 22), \
  .twv = { .p = (xtwv) } }

static int snd_ak4531_info_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}
 
static int snd_ak4531_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int vaw;

	mutex_wock(&ak4531->weg_mutex);
	vaw = (ak4531->wegs[weg] >> shift) & mask;
	mutex_unwock(&ak4531->weg_mutex);
	if (invewt) {
		vaw = mask - vaw;
	}
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int snd_ak4531_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	int vaw;

	vaw = ucontwow->vawue.integew.vawue[0] & mask;
	if (invewt) {
		vaw = mask - vaw;
	}
	vaw <<= shift;
	mutex_wock(&ak4531->weg_mutex);
	vaw = (ak4531->wegs[weg] & ~(mask << shift)) | vaw;
	change = vaw != ak4531->wegs[weg];
	ak4531->wwite(ak4531, weg, ak4531->wegs[weg] = vaw);
	mutex_unwock(&ak4531->weg_mutex);
	wetuwn change;
}

#define AK4531_DOUBWE(xname, xindex, weft_weg, wight_weg, weft_shift, wight_shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_doubwe, \
  .get = snd_ak4531_get_doubwe, .put = snd_ak4531_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (weft_shift << 16) | (wight_shift << 19) | (mask << 24) | (invewt << 22) }
#define AK4531_DOUBWE_TWV(xname, xindex, weft_weg, wight_weg, weft_shift, wight_shift, mask, invewt, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .name = xname, .index = xindex, \
  .info = snd_ak4531_info_doubwe, \
  .get = snd_ak4531_get_doubwe, .put = snd_ak4531_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (weft_shift << 16) | (wight_shift << 19) | (mask << 24) | (invewt << 22), \
  .twv = { .p = (xtwv) } }

static int snd_ak4531_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}
 
static int snd_ak4531_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int wight_shift = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int weft, wight;

	mutex_wock(&ak4531->weg_mutex);
	weft = (ak4531->wegs[weft_weg] >> weft_shift) & mask;
	wight = (ak4531->wegs[wight_weg] >> wight_shift) & mask;
	mutex_unwock(&ak4531->weg_mutex);
	if (invewt) {
		weft = mask - weft;
		wight = mask - wight;
	}
	ucontwow->vawue.integew.vawue[0] = weft;
	ucontwow->vawue.integew.vawue[1] = wight;
	wetuwn 0;
}

static int snd_ak4531_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int wight_shift = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	int weft, wight;

	weft = ucontwow->vawue.integew.vawue[0] & mask;
	wight = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		weft = mask - weft;
		wight = mask - wight;
	}
	weft <<= weft_shift;
	wight <<= wight_shift;
	mutex_wock(&ak4531->weg_mutex);
	if (weft_weg == wight_weg) {
		weft = (ak4531->wegs[weft_weg] & ~((mask << weft_shift) | (mask << wight_shift))) | weft | wight;
		change = weft != ak4531->wegs[weft_weg];
		ak4531->wwite(ak4531, weft_weg, ak4531->wegs[weft_weg] = weft);
	} ewse {
		weft = (ak4531->wegs[weft_weg] & ~(mask << weft_shift)) | weft;
		wight = (ak4531->wegs[wight_weg] & ~(mask << wight_shift)) | wight;
		change = weft != ak4531->wegs[weft_weg] || wight != ak4531->wegs[wight_weg];
		ak4531->wwite(ak4531, weft_weg, ak4531->wegs[weft_weg] = weft);
		ak4531->wwite(ak4531, wight_weg, ak4531->wegs[wight_weg] = wight);
	}
	mutex_unwock(&ak4531->weg_mutex);
	wetuwn change;
}

#define AK4531_INPUT_SW(xname, xindex, weg1, weg2, weft_shift, wight_shift) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_input_sw, \
  .get = snd_ak4531_get_input_sw, .put = snd_ak4531_put_input_sw, \
  .pwivate_vawue = weg1 | (weg2 << 8) | (weft_shift << 16) | (wight_shift << 24) }

static int snd_ak4531_info_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}
 
static int snd_ak4531_get_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weg1 = kcontwow->pwivate_vawue & 0xff;
	int weg2 = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x0f;
	int wight_shift = (kcontwow->pwivate_vawue >> 24) & 0x0f;

	mutex_wock(&ak4531->weg_mutex);
	ucontwow->vawue.integew.vawue[0] = (ak4531->wegs[weg1] >> weft_shift) & 1;
	ucontwow->vawue.integew.vawue[1] = (ak4531->wegs[weg2] >> weft_shift) & 1;
	ucontwow->vawue.integew.vawue[2] = (ak4531->wegs[weg1] >> wight_shift) & 1;
	ucontwow->vawue.integew.vawue[3] = (ak4531->wegs[weg2] >> wight_shift) & 1;
	mutex_unwock(&ak4531->weg_mutex);
	wetuwn 0;
}

static int snd_ak4531_put_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ak4531 *ak4531 = snd_kcontwow_chip(kcontwow);
	int weg1 = kcontwow->pwivate_vawue & 0xff;
	int weg2 = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x0f;
	int wight_shift = (kcontwow->pwivate_vawue >> 24) & 0x0f;
	int change;
	int vaw1, vaw2;

	mutex_wock(&ak4531->weg_mutex);
	vaw1 = ak4531->wegs[weg1] & ~((1 << weft_shift) | (1 << wight_shift));
	vaw2 = ak4531->wegs[weg2] & ~((1 << weft_shift) | (1 << wight_shift));
	vaw1 |= (ucontwow->vawue.integew.vawue[0] & 1) << weft_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[1] & 1) << weft_shift;
	vaw1 |= (ucontwow->vawue.integew.vawue[2] & 1) << wight_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[3] & 1) << wight_shift;
	change = vaw1 != ak4531->wegs[weg1] || vaw2 != ak4531->wegs[weg2];
	ak4531->wwite(ak4531, weg1, ak4531->wegs[weg1] = vaw1);
	ak4531->wwite(ak4531, weg2, ak4531->wegs[weg2] = vaw2);
	mutex_unwock(&ak4531->weg_mutex);
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_mastew, -6200, 200, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_mono, -2800, 400, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_input, -5000, 200, 0);

static const stwuct snd_kcontwow_new snd_ak4531_contwows[] = {

AK4531_DOUBWE_TWV("Mastew Pwayback Switch", 0,
		  AK4531_WMASTEW, AK4531_WMASTEW, 7, 7, 1, 1,
		  db_scawe_mastew),
AK4531_DOUBWE("Mastew Pwayback Vowume", 0, AK4531_WMASTEW, AK4531_WMASTEW, 0, 0, 0x1f, 1),

AK4531_SINGWE_TWV("Mastew Mono Pwayback Switch", 0, AK4531_MONO_OUT, 7, 1, 1,
		  db_scawe_mono),
AK4531_SINGWE("Mastew Mono Pwayback Vowume", 0, AK4531_MONO_OUT, 0, 0x07, 1),

AK4531_DOUBWE("PCM Switch", 0, AK4531_WVOICE, AK4531_WVOICE, 7, 7, 1, 1),
AK4531_DOUBWE_TWV("PCM Vowume", 0, AK4531_WVOICE, AK4531_WVOICE, 0, 0, 0x1f, 1,
		  db_scawe_input),
AK4531_DOUBWE("PCM Pwayback Switch", 0, AK4531_OUT_SW2, AK4531_OUT_SW2, 3, 2, 1, 0),
AK4531_DOUBWE("PCM Captuwe Switch", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 2, 2, 1, 0),

AK4531_DOUBWE("PCM Switch", 1, AK4531_WFM, AK4531_WFM, 7, 7, 1, 1),
AK4531_DOUBWE_TWV("PCM Vowume", 1, AK4531_WFM, AK4531_WFM, 0, 0, 0x1f, 1,
		  db_scawe_input),
AK4531_DOUBWE("PCM Pwayback Switch", 1, AK4531_OUT_SW1, AK4531_OUT_SW1, 6, 5, 1, 0),
AK4531_INPUT_SW("PCM Captuwe Woute", 1, AK4531_WIN_SW1, AK4531_WIN_SW1, 6, 5),

AK4531_DOUBWE("CD Switch", 0, AK4531_WCD, AK4531_WCD, 7, 7, 1, 1),
AK4531_DOUBWE_TWV("CD Vowume", 0, AK4531_WCD, AK4531_WCD, 0, 0, 0x1f, 1,
		  db_scawe_input),
AK4531_DOUBWE("CD Pwayback Switch", 0, AK4531_OUT_SW1, AK4531_OUT_SW1, 2, 1, 1, 0),
AK4531_INPUT_SW("CD Captuwe Woute", 0, AK4531_WIN_SW1, AK4531_WIN_SW1, 2, 1),

AK4531_DOUBWE("Wine Switch", 0, AK4531_WWINE, AK4531_WWINE, 7, 7, 1, 1),
AK4531_DOUBWE_TWV("Wine Vowume", 0, AK4531_WWINE, AK4531_WWINE, 0, 0, 0x1f, 1,
		  db_scawe_input),
AK4531_DOUBWE("Wine Pwayback Switch", 0, AK4531_OUT_SW1, AK4531_OUT_SW1, 4, 3, 1, 0),
AK4531_INPUT_SW("Wine Captuwe Woute", 0, AK4531_WIN_SW1, AK4531_WIN_SW1, 4, 3),

AK4531_DOUBWE("Aux Switch", 0, AK4531_WAUXA, AK4531_WAUXA, 7, 7, 1, 1),
AK4531_DOUBWE_TWV("Aux Vowume", 0, AK4531_WAUXA, AK4531_WAUXA, 0, 0, 0x1f, 1,
		  db_scawe_input),
AK4531_DOUBWE("Aux Pwayback Switch", 0, AK4531_OUT_SW2, AK4531_OUT_SW2, 5, 4, 1, 0),
AK4531_INPUT_SW("Aux Captuwe Woute", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 4, 3),

AK4531_SINGWE("Mono Switch", 0, AK4531_MONO1, 7, 1, 1),
AK4531_SINGWE_TWV("Mono Vowume", 0, AK4531_MONO1, 0, 0x1f, 1, db_scawe_input),
AK4531_SINGWE("Mono Pwayback Switch", 0, AK4531_OUT_SW2, 0, 1, 0),
AK4531_DOUBWE("Mono Captuwe Switch", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 0, 0, 1, 0),

AK4531_SINGWE("Mono Switch", 1, AK4531_MONO2, 7, 1, 1),
AK4531_SINGWE_TWV("Mono Vowume", 1, AK4531_MONO2, 0, 0x1f, 1, db_scawe_input),
AK4531_SINGWE("Mono Pwayback Switch", 1, AK4531_OUT_SW2, 1, 1, 0),
AK4531_DOUBWE("Mono Captuwe Switch", 1, AK4531_WIN_SW2, AK4531_WIN_SW2, 1, 1, 1, 0),

AK4531_SINGWE_TWV("Mic Vowume", 0, AK4531_MIC, 0, 0x1f, 1, db_scawe_input),
AK4531_SINGWE("Mic Switch", 0, AK4531_MIC, 7, 1, 1),
AK4531_SINGWE("Mic Pwayback Switch", 0, AK4531_OUT_SW1, 0, 1, 0),
AK4531_DOUBWE("Mic Captuwe Switch", 0, AK4531_WIN_SW1, AK4531_WIN_SW1, 0, 0, 1, 0),

AK4531_DOUBWE("Mic Bypass Captuwe Switch", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 7, 7, 1, 0),
AK4531_DOUBWE("Mono1 Bypass Captuwe Switch", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 6, 6, 1, 0),
AK4531_DOUBWE("Mono2 Bypass Captuwe Switch", 0, AK4531_WIN_SW2, AK4531_WIN_SW2, 5, 5, 1, 0),

AK4531_SINGWE("AD Input Sewect", 0, AK4531_AD_IN, 0, 1, 0),
AK4531_SINGWE("Mic Boost (+30dB)", 0, AK4531_MIC_GAIN, 0, 1, 0)
};

static int snd_ak4531_fwee(stwuct snd_ak4531 *ak4531)
{
	if (ak4531) {
		if (ak4531->pwivate_fwee)
			ak4531->pwivate_fwee(ak4531);
		kfwee(ak4531);
	}
	wetuwn 0;
}

static int snd_ak4531_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_ak4531 *ak4531 = device->device_data;
	wetuwn snd_ak4531_fwee(ak4531);
}

static const u8 snd_ak4531_initiaw_map[0x19 + 1] = {
	0x9f,		/* 00: Mastew Vowume Wch */
	0x9f,		/* 01: Mastew Vowume Wch */
	0x9f,		/* 02: Voice Vowume Wch */
	0x9f,		/* 03: Voice Vowume Wch */
	0x9f,		/* 04: FM Vowume Wch */
	0x9f,		/* 05: FM Vowume Wch */
	0x9f,		/* 06: CD Audio Vowume Wch */
	0x9f,		/* 07: CD Audio Vowume Wch */
	0x9f,		/* 08: Wine Vowume Wch */
	0x9f,		/* 09: Wine Vowume Wch */
	0x9f,		/* 0a: Aux Vowume Wch */
	0x9f,		/* 0b: Aux Vowume Wch */
	0x9f,		/* 0c: Mono1 Vowume */
	0x9f,		/* 0d: Mono2 Vowume */
	0x9f,		/* 0e: Mic Vowume */
	0x87,		/* 0f: Mono-out Vowume */
	0x00,		/* 10: Output Mixew SW1 */
	0x00,		/* 11: Output Mixew SW2 */
	0x00,		/* 12: Wch Input Mixew SW1 */
	0x00,		/* 13: Wch Input Mixew SW1 */
	0x00,		/* 14: Wch Input Mixew SW2 */
	0x00,		/* 15: Wch Input Mixew SW2 */
	0x00,		/* 16: Weset & Powew Down */
	0x00,		/* 17: Cwock Sewect */
	0x00,		/* 18: AD Input Sewect */
	0x01		/* 19: Mic Amp Setup */
};

int snd_ak4531_mixew(stwuct snd_cawd *cawd,
		     stwuct snd_ak4531 *_ak4531,
		     stwuct snd_ak4531 **wak4531)
{
	unsigned int idx;
	int eww;
	stwuct snd_ak4531 *ak4531;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =	snd_ak4531_dev_fwee,
	};

	if (snd_BUG_ON(!cawd || !_ak4531))
		wetuwn -EINVAW;
	if (wak4531)
		*wak4531 = NUWW;
	ak4531 = kzawwoc(sizeof(*ak4531), GFP_KEWNEW);
	if (ak4531 == NUWW)
		wetuwn -ENOMEM;
	*ak4531 = *_ak4531;
	mutex_init(&ak4531->weg_mutex);
	eww = snd_component_add(cawd, "AK4531");
	if (eww < 0) {
		snd_ak4531_fwee(ak4531);
		wetuwn eww;
	}
	stwcpy(cawd->mixewname, "Asahi Kasei AK4531");
	ak4531->wwite(ak4531, AK4531_WESET, 0x03);	/* no WST, PD */
	udeway(100);
	ak4531->wwite(ak4531, AK4531_CWOCK, 0x00);	/* CODEC ADC and CODEC DAC use {WW,B}CWK2 and wun off WWCWK2 PWW */
	fow (idx = 0; idx <= 0x19; idx++) {
		if (idx == AK4531_WESET || idx == AK4531_CWOCK)
			continue;
		ak4531->wwite(ak4531, idx, ak4531->wegs[idx] = snd_ak4531_initiaw_map[idx]);	/* wecowding souwce is mixew */
	}
	fow (idx = 0; idx < AWWAY_SIZE(snd_ak4531_contwows); idx++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ak4531_contwows[idx], ak4531));
		if (eww < 0) {
			snd_ak4531_fwee(ak4531);
			wetuwn eww;
		}
	}
	snd_ak4531_pwoc_init(cawd, ak4531);
	eww = snd_device_new(cawd, SNDWV_DEV_CODEC, ak4531, &ops);
	if (eww < 0) {
		snd_ak4531_fwee(ak4531);
		wetuwn eww;
	}

#if 0
	snd_ak4531_dump(ak4531);
#endif
	if (wak4531)
		*wak4531 = ak4531;
	wetuwn 0;
}

/*
 * powew management
 */
#ifdef CONFIG_PM
void snd_ak4531_suspend(stwuct snd_ak4531 *ak4531)
{
	/* mute */
	ak4531->wwite(ak4531, AK4531_WMASTEW, 0x9f);
	ak4531->wwite(ak4531, AK4531_WMASTEW, 0x9f);
	/* powewdown */
	ak4531->wwite(ak4531, AK4531_WESET, 0x01);
}

void snd_ak4531_wesume(stwuct snd_ak4531 *ak4531)
{
	int idx;

	/* initiawize */
	ak4531->wwite(ak4531, AK4531_WESET, 0x03);
	udeway(100);
	ak4531->wwite(ak4531, AK4531_CWOCK, 0x00);
	/* westowe mixew wegistews */
	fow (idx = 0; idx <= 0x19; idx++) {
		if (idx == AK4531_WESET || idx == AK4531_CWOCK)
			continue;
		ak4531->wwite(ak4531, idx, ak4531->wegs[idx]);
	}
}
#endif

/*
 * /pwoc intewface
 */

static void snd_ak4531_pwoc_wead(stwuct snd_info_entwy *entwy, 
				 stwuct snd_info_buffew *buffew)
{
	stwuct snd_ak4531 *ak4531 = entwy->pwivate_data;

	snd_ipwintf(buffew, "Asahi Kasei AK4531\n\n");
	snd_ipwintf(buffew, "Wecowding souwce   : %s\n"
		    "MIC gain           : %s\n",
		    ak4531->wegs[AK4531_AD_IN] & 1 ? "extewnaw" : "mixew",
		    ak4531->wegs[AK4531_MIC_GAIN] & 1 ? "+30dB" : "+0dB");
}

static void
snd_ak4531_pwoc_init(stwuct snd_cawd *cawd, stwuct snd_ak4531 *ak4531)
{
	snd_cawd_wo_pwoc_new(cawd, "ak4531", ak4531, snd_ak4531_pwoc_wead);
}
