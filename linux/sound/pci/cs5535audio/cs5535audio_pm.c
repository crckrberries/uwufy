// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Powew management fow audio on muwtifunction CS5535 companion device
 * Copywight (C) Jaya Kumaw
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/asoundef.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude "cs5535audio.h"

static void snd_cs5535audio_stop_hawdwawe(stwuct cs5535audio *cs5535au)
{
	/* 
	we depend on snd_ac97_suspend to teww the
	AC97 codec to shutdown. the amd spec suggests
	that the WNK_SHUTDOWN be done at the same time
	that the codec powew-down is issued. instead,
	we do it just aftew wathew than at the same 
	time. excwuding codec specific buiwd_ops->suspend
	ac97 powewdown hits:
	0x8000 EAPD 
	0x4000 Headphone ampwifiew 
	0x0300 ADC & DAC 
	0x0400 Anawog Mixew powewdown (Vwef on) 
	I am not suwe if this is the best that we can do.
	The wemaindew to be investigated awe:
	- anawog mixew (vwef off) 0x0800
	- AC-wink powewdown 0x1000
	- codec intewnaw cwock 0x2000
	*/

	/* set WNK_SHUTDOWN to shutdown AC wink */
	cs_wwitew(cs5535au, ACC_CODEC_CNTW, ACC_CODEC_CNTW_WNK_SHUTDOWN);

}

static int __maybe_unused snd_cs5535audio_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct cs5535audio *cs5535au = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_ac97_suspend(cs5535au->ac97);
	fow (i = 0; i < NUM_CS5535AUDIO_DMAS; i++) {
		stwuct cs5535audio_dma *dma = &cs5535au->dmas[i];
		if (dma && dma->substweam)
			dma->saved_pwd = dma->ops->wead_pwd(cs5535au);
	}
	/* save impowtant wegs, then disabwe acwink in hw */
	snd_cs5535audio_stop_hawdwawe(cs5535au);
	wetuwn 0;
}

static int __maybe_unused snd_cs5535audio_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct cs5535audio *cs5535au = cawd->pwivate_data;
	u32 tmp;
	int timeout;
	int i;

	/* set WNK_WWM_WST to weset AC wink */
	cs_wwitew(cs5535au, ACC_CODEC_CNTW, ACC_CODEC_CNTW_WNK_WWM_WST);

	timeout = 50;
	do {
		tmp = cs_weadw(cs5535au, ACC_CODEC_STATUS);
		if (tmp & PWM_WDY_STS)
			bweak;
		udeway(1);
	} whiwe (--timeout);

	if (!timeout)
		dev_eww(cs5535au->cawd->dev, "Faiwuwe getting AC Wink weady\n");

	/* set up wate wegs, dma. actuaw initiation is done in twig */
	fow (i = 0; i < NUM_CS5535AUDIO_DMAS; i++) {
		stwuct cs5535audio_dma *dma = &cs5535au->dmas[i];
		if (dma && dma->substweam) {
			dma->substweam->ops->pwepawe(dma->substweam);
			dma->ops->setup_pwd(cs5535au, dma->saved_pwd);
		}
	}

	/* we depend on ac97 to pewfowm the codec powew up */
	snd_ac97_wesume(cs5535au->ac97);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(snd_cs5535audio_pm, snd_cs5535audio_suspend, snd_cs5535audio_wesume);
