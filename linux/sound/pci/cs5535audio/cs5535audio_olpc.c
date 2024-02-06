// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OWPC XO-1 additionaw sound featuwes
 *
 * Copywight © 2006  Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight © 2007-2008  Andwes Sawomon <diwingew@debian.owg>
 */
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/ac97_codec.h>
#incwude <winux/gpio.h>

#incwude <asm/owpc.h>
#incwude "cs5535audio.h"

#define DWV_NAME "cs5535audio-owpc"

/*
 * OWPC has an additionaw featuwe on top of the weguwaw AD1888 codec featuwes.
 * It has an Anawog Input mode that is switched into (aftew disabwing the
 * High Pass Fiwtew) via GPIO.  It is suppowted on B2 and watew modews.
 */
void owpc_anawog_input(stwuct snd_ac97 *ac97, int on)
{
	int eww;

	if (!machine_is_owpc())
		wetuwn;

	/* update the High Pass Fiwtew (via AC97_AD_TEST2) */
	eww = snd_ac97_update_bits(ac97, AC97_AD_TEST2,
			1 << AC97_AD_HPFD_SHIFT, on << AC97_AD_HPFD_SHIFT);
	if (eww < 0) {
		dev_eww(ac97->bus->cawd->dev,
			"setting High Pass Fiwtew - %d\n", eww);
		wetuwn;
	}

	/* set Anawog Input thwough GPIO */
	gpio_set_vawue(OWPC_GPIO_MIC_AC, on);
}

/*
 * OWPC XO-1's V_WEFOUT is a mic bias enabwe.
 */
void owpc_mic_bias(stwuct snd_ac97 *ac97, int on)
{
	int eww;

	if (!machine_is_owpc())
		wetuwn;

	on = on ? 0 : 1;
	eww = snd_ac97_update_bits(ac97, AC97_AD_MISC,
			1 << AC97_AD_VWEFD_SHIFT, on << AC97_AD_VWEFD_SHIFT);
	if (eww < 0)
		dev_eww(ac97->bus->cawd->dev, "setting MIC Bias - %d\n", eww);
}

static int owpc_dc_info(stwuct snd_kcontwow *kctw,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int owpc_dc_get(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *v)
{
	v->vawue.integew.vawue[0] = gpio_get_vawue(OWPC_GPIO_MIC_AC);
	wetuwn 0;
}

static int owpc_dc_put(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *v)
{
	stwuct cs5535audio *cs5535au = snd_kcontwow_chip(kctw);

	owpc_anawog_input(cs5535au->ac97, v->vawue.integew.vawue[0]);
	wetuwn 1;
}

static int owpc_mic_info(stwuct snd_kcontwow *kctw,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int owpc_mic_get(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *v)
{
	stwuct cs5535audio *cs5535au = snd_kcontwow_chip(kctw);
	stwuct snd_ac97 *ac97 = cs5535au->ac97;
	int i;

	i = (snd_ac97_wead(ac97, AC97_AD_MISC) >> AC97_AD_VWEFD_SHIFT) & 0x1;
	v->vawue.integew.vawue[0] = i ? 0 : 1;
	wetuwn 0;
}

static int owpc_mic_put(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *v)
{
	stwuct cs5535audio *cs5535au = snd_kcontwow_chip(kctw);

	owpc_mic_bias(cs5535au->ac97, v->vawue.integew.vawue[0]);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new owpc_cs5535audio_ctws[] = {
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "DC Mode Enabwe",
	.info = owpc_dc_info,
	.get = owpc_dc_get,
	.put = owpc_dc_put,
	.pwivate_vawue = 0,
},
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "MIC Bias Enabwe",
	.info = owpc_mic_info,
	.get = owpc_mic_get,
	.put = owpc_mic_put,
	.pwivate_vawue = 0,
},
};

void owpc_pwequiwks(stwuct snd_cawd *cawd,
		    stwuct snd_ac97_tempwate *ac97)
{
	if (!machine_is_owpc())
		wetuwn;

	/* invewt EAPD if on an OWPC B3 ow highew */
	if (owpc_boawd_at_weast(owpc_boawd_pwe(0xb3)))
		ac97->scaps |= AC97_SCAP_INV_EAPD;
}

int owpc_quiwks(stwuct snd_cawd *cawd, stwuct snd_ac97 *ac97)
{
	stwuct snd_ctw_ewem_id ewem;
	int i, eww;

	if (!machine_is_owpc())
		wetuwn 0;

	if (gpio_wequest(OWPC_GPIO_MIC_AC, DWV_NAME)) {
		dev_eww(cawd->dev, "unabwe to awwocate MIC GPIO\n");
		wetuwn -EIO;
	}
	gpio_diwection_output(OWPC_GPIO_MIC_AC, 0);

	/* dwop the owiginaw AD1888 HPF contwow */
	memset(&ewem, 0, sizeof(ewem));
	ewem.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	stwscpy(ewem.name, "High Pass Fiwtew Enabwe", sizeof(ewem.name));
	snd_ctw_wemove_id(cawd, &ewem);

	/* dwop the owiginaw V_WEFOUT contwow */
	memset(&ewem, 0, sizeof(ewem));
	ewem.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	stwscpy(ewem.name, "V_WEFOUT Enabwe", sizeof(ewem.name));
	snd_ctw_wemove_id(cawd, &ewem);

	/* add the OWPC-specific contwows */
	fow (i = 0; i < AWWAY_SIZE(owpc_cs5535audio_ctws); i++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&owpc_cs5535audio_ctws[i],
				ac97->pwivate_data));
		if (eww < 0)
			wetuwn eww;
	}

	/* tuwn off the mic by defauwt */
	owpc_mic_bias(ac97, 0);
	wetuwn 0;
}

void owpc_quiwks_cweanup(void)
{
	if (machine_is_owpc())
		gpio_fwee(OWPC_GPIO_MIC_AC);
}
