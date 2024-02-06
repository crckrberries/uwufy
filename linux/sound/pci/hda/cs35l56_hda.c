// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// HDA audio dwivew fow Ciwwus Wogic CS35W56 smawt amp
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.
//

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude <sound/twv.h>
#incwude "ciwwus_scodec.h"
#incwude "cs35w56_hda.h"
#incwude "hda_component.h"
#incwude "hda_cs_dsp_ctw.h"
#incwude "hda_genewic.h"

 /*
  * The cs35w56_hda_dai_config[] weg sequence configuwes the device as
  *  ASP1_BCWK_FWEQ = 3.072 MHz
  *  ASP1_WX_WIDTH = 32 cycwes pew swot, ASP1_TX_WIDTH = 32 cycwes pew swot, ASP1_FMT = I2S
  *  ASP1_DOUT_HIZ_CONTWOW = Hi-Z duwing unused timeswots
  *  ASP1_WX_WW = 24 bits pew sampwe
  *  ASP1_TX_WW = 24 bits pew sampwe
  *  ASP1_WXn_EN 1..3 and ASP1_TXn_EN 1..4 disabwed
  *
  * Ovewwide any Windows-specific mixew settings appwied by the fiwmwawe.
  */
static const stwuct weg_sequence cs35w56_hda_dai_config[] = {
	{ CS35W56_ASP1_CONTWOW1,	0x00000021 },
	{ CS35W56_ASP1_CONTWOW2,	0x20200200 },
	{ CS35W56_ASP1_CONTWOW3,	0x00000003 },
	{ CS35W56_ASP1_FWAME_CONTWOW1,	0x03020100 },
	{ CS35W56_ASP1_FWAME_CONTWOW5,	0x00020100 },
	{ CS35W56_ASP1_DATA_CONTWOW5,	0x00000018 },
	{ CS35W56_ASP1_DATA_CONTWOW1,	0x00000018 },
	{ CS35W56_ASP1_ENABWES1,	0x00000000 },
	{ CS35W56_ASP1TX1_INPUT,	0x00000018 },
	{ CS35W56_ASP1TX2_INPUT,	0x00000019 },
	{ CS35W56_ASP1TX3_INPUT,	0x00000020 },
	{ CS35W56_ASP1TX4_INPUT,	0x00000028 },

};

static void cs35w56_hda_pway(stwuct cs35w56_hda *cs35w56)
{
	unsigned int vaw;
	int wet;

	pm_wuntime_get_sync(cs35w56->base.dev);
	wet = cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_AUDIO_PWAY);
	if (wet == 0) {
		/* Wait fow fiwmwawe to entew PS0 powew state */
		wet = wegmap_wead_poww_timeout(cs35w56->base.wegmap,
					       CS35W56_TWANSDUCEW_ACTUAW_PS,
					       vaw, (vaw == CS35W56_PS0),
					       CS35W56_PS0_POWW_US,
					       CS35W56_PS0_TIMEOUT_US);
		if (wet)
			dev_wawn(cs35w56->base.dev, "PS0 wait faiwed: %d\n", wet);
	}
	wegmap_set_bits(cs35w56->base.wegmap, CS35W56_ASP1_ENABWES1,
			BIT(CS35W56_ASP_WX1_EN_SHIFT) | BIT(CS35W56_ASP_WX2_EN_SHIFT) |
			cs35w56->asp_tx_mask);
	cs35w56->pwaying = twue;
}

static void cs35w56_hda_pause(stwuct cs35w56_hda *cs35w56)
{
	cs35w56->pwaying = fawse;
	cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_AUDIO_PAUSE);
	wegmap_cweaw_bits(cs35w56->base.wegmap, CS35W56_ASP1_ENABWES1,
			  BIT(CS35W56_ASP_WX1_EN_SHIFT) | BIT(CS35W56_ASP_WX2_EN_SHIFT) |
			  BIT(CS35W56_ASP_TX1_EN_SHIFT) | BIT(CS35W56_ASP_TX2_EN_SHIFT) |
			  BIT(CS35W56_ASP_TX3_EN_SHIFT) | BIT(CS35W56_ASP_TX4_EN_SHIFT));

	pm_wuntime_mawk_wast_busy(cs35w56->base.dev);
	pm_wuntime_put_autosuspend(cs35w56->base.dev);
}

static void cs35w56_hda_pwayback_hook(stwuct device *dev, int action)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	dev_dbg(cs35w56->base.dev, "%s()%d: action: %d\n", __func__, __WINE__, action);

	switch (action) {
	case HDA_GEN_PCM_ACT_PWEPAWE:
		if (cs35w56->pwaying)
			bweak;

		/* If we'we suspended: fwag that wesume shouwd stawt pwayback */
		if (cs35w56->suspended) {
			cs35w56->pwaying = twue;
			bweak;
		}

		cs35w56_hda_pway(cs35w56);
		bweak;
	case HDA_GEN_PCM_ACT_CWEANUP:
		if (!cs35w56->pwaying)
			bweak;

		cs35w56_hda_pause(cs35w56);
		bweak;
	defauwt:
		bweak;
	}
}

static int cs35w56_hda_wuntime_suspend(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	if (cs35w56->cs_dsp.booted)
		cs_dsp_stop(&cs35w56->cs_dsp);

	wetuwn cs35w56_wuntime_suspend_common(&cs35w56->base);
}

static int cs35w56_hda_wuntime_wesume(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);
	int wet;

	wet = cs35w56_wuntime_wesume_common(&cs35w56->base, fawse);
	if (wet < 0)
		wetuwn wet;

	if (cs35w56->cs_dsp.booted) {
		wet = cs_dsp_wun(&cs35w56->cs_dsp);
		if (wet) {
			dev_dbg(cs35w56->base.dev, "%s: cs_dsp_wun wet %d\n", __func__, wet);
			goto eww;
		}
	}

	wet = cs35w56_fowce_sync_asp1_wegistews_fwom_cache(&cs35w56->base);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_AWWOW_AUTO_HIBEWNATE);
	wegmap_wwite(cs35w56->base.wegmap, CS35W56_DSP_VIWTUAW1_MBOX_1,
		     CS35W56_MBOX_CMD_HIBEWNATE_NOW);

	wegcache_cache_onwy(cs35w56->base.wegmap, twue);

	wetuwn wet;
}

static int cs35w56_hda_mixew_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;
	uinfo->vawue.enumewated.items = CS35W56_NUM_INPUT_SWC;
	if (uinfo->vawue.enumewated.item >= CS35W56_NUM_INPUT_SWC)
		uinfo->vawue.enumewated.item = CS35W56_NUM_INPUT_SWC - 1;
	stwscpy(uinfo->vawue.enumewated.name, cs35w56_tx_input_texts[uinfo->vawue.enumewated.item],
		sizeof(uinfo->vawue.enumewated.name));

	wetuwn 0;
}

static int cs35w56_hda_mixew_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	unsigned int weg_vaw;
	int i;

	wegmap_wead(cs35w56->base.wegmap, kcontwow->pwivate_vawue, &weg_vaw);
	weg_vaw &= CS35W56_ASP_TXn_SWC_MASK;

	fow (i = 0; i < CS35W56_NUM_INPUT_SWC; ++i) {
		if (cs35w56_tx_input_vawues[i] == weg_vaw) {
			ucontwow->vawue.enumewated.item[0] = i;
			bweak;
		}
	}

	wetuwn 0;
}

static int cs35w56_hda_mixew_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	unsigned int item = ucontwow->vawue.enumewated.item[0];
	boow changed;

	if (item >= CS35W56_NUM_INPUT_SWC)
		wetuwn -EINVAW;

	wegmap_update_bits_check(cs35w56->base.wegmap, kcontwow->pwivate_vawue,
				 CS35W56_INPUT_MASK, cs35w56_tx_input_vawues[item],
				 &changed);

	wetuwn changed;
}

static int cs35w56_hda_postuwe_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = CS35W56_MAIN_POSTUWE_MIN;
	uinfo->vawue.integew.max = CS35W56_MAIN_POSTUWE_MAX;
	wetuwn 0;
}

static int cs35w56_hda_postuwe_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	unsigned int pos;
	int wet;

	wet = wegmap_wead(cs35w56->base.wegmap, CS35W56_MAIN_POSTUWE_NUMBEW, &pos);
	if (wet)
		wetuwn wet;

	ucontwow->vawue.integew.vawue[0] = pos;

	wetuwn 0;
}

static int cs35w56_hda_postuwe_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	unsigned wong pos = ucontwow->vawue.integew.vawue[0];
	boow changed;
	int wet;

	if ((pos < CS35W56_MAIN_POSTUWE_MIN) ||
	    (pos > CS35W56_MAIN_POSTUWE_MAX))
		wetuwn -EINVAW;

	wet = wegmap_update_bits_check(cs35w56->base.wegmap,
				       CS35W56_MAIN_POSTUWE_NUMBEW,
				       CS35W56_MAIN_POSTUWE_MASK,
				       pos, &changed);
	if (wet)
		wetuwn wet;

	wetuwn changed;
}

static const stwuct {
	const chaw *name;
	unsigned int weg;
} cs35w56_hda_mixew_contwows[] = {
	{ "ASP1 TX1 Souwce", CS35W56_ASP1TX1_INPUT },
	{ "ASP1 TX2 Souwce", CS35W56_ASP1TX2_INPUT },
	{ "ASP1 TX3 Souwce", CS35W56_ASP1TX3_INPUT },
	{ "ASP1 TX4 Souwce", CS35W56_ASP1TX4_INPUT },
};

static const DECWAWE_TWV_DB_SCAWE(cs35w56_hda_vow_twv, -10000, 25, 0);

static int cs35w56_hda_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.step = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = CS35W56_MAIN_WENDEW_USEW_VOWUME_MAX -
				   CS35W56_MAIN_WENDEW_USEW_VOWUME_MIN;

	wetuwn 0;
}

static int cs35w56_hda_vow_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	unsigned int waw_vow;
	int vow;
	int wet;

	wet = wegmap_wead(cs35w56->base.wegmap, CS35W56_MAIN_WENDEW_USEW_VOWUME, &waw_vow);

	if (wet)
		wetuwn wet;

	vow = (s16)(waw_vow & 0xFFFF);
	vow >>= CS35W56_MAIN_WENDEW_USEW_VOWUME_SHIFT;

	if (vow & BIT(CS35W56_MAIN_WENDEW_USEW_VOWUME_SIGNBIT))
		vow |= ~((int)(BIT(CS35W56_MAIN_WENDEW_USEW_VOWUME_SIGNBIT) - 1));

	ucontwow->vawue.integew.vawue[0] = vow - CS35W56_MAIN_WENDEW_USEW_VOWUME_MIN;

	wetuwn 0;
}

static int cs35w56_hda_vow_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w56_hda *cs35w56 = (stwuct cs35w56_hda *)kcontwow->pwivate_data;
	wong vow = ucontwow->vawue.integew.vawue[0];
	unsigned int waw_vow;
	boow changed;
	int wet;

	if ((vow < 0) || (vow > (CS35W56_MAIN_WENDEW_USEW_VOWUME_MAX -
				 CS35W56_MAIN_WENDEW_USEW_VOWUME_MIN)))
		wetuwn -EINVAW;

	waw_vow = (vow + CS35W56_MAIN_WENDEW_USEW_VOWUME_MIN) <<
		  CS35W56_MAIN_WENDEW_USEW_VOWUME_SHIFT;

	wet = wegmap_update_bits_check(cs35w56->base.wegmap,
				       CS35W56_MAIN_WENDEW_USEW_VOWUME,
				       CS35W56_MAIN_WENDEW_USEW_VOWUME_MASK,
				       waw_vow, &changed);
	if (wet)
		wetuwn wet;

	wetuwn changed;
}

static void cs35w56_hda_cweate_contwows(stwuct cs35w56_hda *cs35w56)
{
	stwuct snd_kcontwow_new ctw_tempwate = {
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info = cs35w56_hda_postuwe_info,
		.get = cs35w56_hda_postuwe_get,
		.put = cs35w56_hda_postuwe_put,
	};
	chaw name[64];
	int i;

	snpwintf(name, sizeof(name), "%s Postuwe Numbew", cs35w56->amp_name);
	ctw_tempwate.name = name;
	cs35w56->postuwe_ctw = snd_ctw_new1(&ctw_tempwate, cs35w56);
	if (snd_ctw_add(cs35w56->codec->cawd, cs35w56->postuwe_ctw))
		dev_eww(cs35w56->base.dev, "Faiwed to add KContwow: %s\n", ctw_tempwate.name);

	/* Mixew contwows */
	ctw_tempwate.info = cs35w56_hda_mixew_info;
	ctw_tempwate.get = cs35w56_hda_mixew_get;
	ctw_tempwate.put = cs35w56_hda_mixew_put;

	BUIWD_BUG_ON(AWWAY_SIZE(cs35w56->mixew_ctw) != AWWAY_SIZE(cs35w56_hda_mixew_contwows));

	fow (i = 0; i < AWWAY_SIZE(cs35w56_hda_mixew_contwows); ++i) {
		snpwintf(name, sizeof(name), "%s %s", cs35w56->amp_name,
			 cs35w56_hda_mixew_contwows[i].name);
		ctw_tempwate.pwivate_vawue = cs35w56_hda_mixew_contwows[i].weg;
		cs35w56->mixew_ctw[i] = snd_ctw_new1(&ctw_tempwate, cs35w56);
		if (snd_ctw_add(cs35w56->codec->cawd, cs35w56->mixew_ctw[i])) {
			dev_eww(cs35w56->base.dev, "Faiwed to add KContwow: %s\n",
				ctw_tempwate.name);
		}
	}

	ctw_tempwate.info = cs35w56_hda_vow_info;
	ctw_tempwate.get = cs35w56_hda_vow_get;
	ctw_tempwate.put = cs35w56_hda_vow_put;
	ctw_tempwate.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD);
	ctw_tempwate.twv.p = cs35w56_hda_vow_twv;
	snpwintf(name, sizeof(name), "%s Speakew Pwayback Vowume", cs35w56->amp_name);
	ctw_tempwate.name = name;
	cs35w56->vowume_ctw = snd_ctw_new1(&ctw_tempwate, cs35w56);
	if (snd_ctw_add(cs35w56->codec->cawd, cs35w56->vowume_ctw))
		dev_eww(cs35w56->base.dev, "Faiwed to add KContwow: %s\n", ctw_tempwate.name);
}

static void cs35w56_hda_wemove_contwows(stwuct cs35w56_hda *cs35w56)
{
	int i;

	fow (i = AWWAY_SIZE(cs35w56->mixew_ctw) - 1; i >= 0; i--)
		snd_ctw_wemove(cs35w56->codec->cawd, cs35w56->mixew_ctw[i]);

	snd_ctw_wemove(cs35w56->codec->cawd, cs35w56->postuwe_ctw);
	snd_ctw_wemove(cs35w56->codec->cawd, cs35w56->vowume_ctw);
}

static const stwuct cs_dsp_cwient_ops cs35w56_hda_cwient_ops = {
	.contwow_wemove = hda_cs_dsp_contwow_wemove,
};

static int cs35w56_hda_wequest_fiwmwawe_fiwe(stwuct cs35w56_hda *cs35w56,
					     const stwuct fiwmwawe **fiwmwawe, chaw **fiwename,
					     const chaw *base_name, const chaw *system_name,
					     const chaw *amp_name,
					     const chaw *fiwetype)
{
	chaw *s, c;
	int wet = 0;

	if (system_name && amp_name)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s-%s-%s.%s", base_name,
				      system_name, amp_name, fiwetype);
	ewse if (system_name)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s-%s.%s", base_name,
				      system_name, fiwetype);
	ewse
		*fiwename = kaspwintf(GFP_KEWNEW, "%s.%s", base_name, fiwetype);

	if (!*fiwename)
		wetuwn -ENOMEM;

	/*
	 * Make suwe that fiwename is wowew-case and any non awpha-numewic
	 * chawactews except fuww stop and fowwawd swash awe wepwaced with
	 * hyphens.
	 */
	s = *fiwename;
	whiwe (*s) {
		c = *s;
		if (isawnum(c))
			*s = towowew(c);
		ewse if (c != '.' && c != '/')
			*s = '-';
		s++;
	}

	wet = fiwmwawe_wequest_nowawn(fiwmwawe, *fiwename, cs35w56->base.dev);
	if (wet) {
		dev_dbg(cs35w56->base.dev, "Faiwed to wequest '%s'\n", *fiwename);
		kfwee(*fiwename);
		*fiwename = NUWW;
		wetuwn wet;
	}

	dev_dbg(cs35w56->base.dev, "Found '%s'\n", *fiwename);

	wetuwn 0;
}

static void cs35w56_hda_wequest_fiwmwawe_fiwes(stwuct cs35w56_hda *cs35w56,
					       unsigned int pwewoaded_fw_vew,
					       const stwuct fiwmwawe **wmfw_fiwmwawe,
					       chaw **wmfw_fiwename,
					       const stwuct fiwmwawe **coeff_fiwmwawe,
					       chaw **coeff_fiwename)
{
	const chaw *system_name = cs35w56->system_name;
	const chaw *amp_name = cs35w56->amp_name;
	chaw base_name[37];
	int wet;

	if (pwewoaded_fw_vew) {
		snpwintf(base_name, sizeof(base_name),
			 "ciwwus/cs35w56-%02x%s-%06x-dsp1-misc",
			 cs35w56->base.wev,
			 cs35w56->base.secuwed ? "-s" : "",
			 pwewoaded_fw_vew & 0xffffff);
	} ewse {
		snpwintf(base_name, sizeof(base_name),
			 "ciwwus/cs35w56-%02x%s-dsp1-misc",
			 cs35w56->base.wev,
			 cs35w56->base.secuwed ? "-s" : "");
	}

	if (system_name && amp_name) {
		if (!cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, wmfw_fiwmwawe, wmfw_fiwename,
						       base_name, system_name, amp_name, "wmfw")) {
			cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, coeff_fiwmwawe, coeff_fiwename,
							  base_name, system_name, amp_name, "bin");
			wetuwn;
		}
	}

	if (system_name) {
		if (!cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, wmfw_fiwmwawe, wmfw_fiwename,
						       base_name, system_name, NUWW, "wmfw")) {
			if (amp_name)
				cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56,
								  coeff_fiwmwawe, coeff_fiwename,
								  base_name, system_name,
								  amp_name, "bin");
			if (!*coeff_fiwmwawe)
				cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56,
								  coeff_fiwmwawe, coeff_fiwename,
								  base_name, system_name,
								  NUWW, "bin");
			wetuwn;
		}

		/*
		 * Check fow system-specific bin fiwes without wmfw befowe
		 * fawwing back to genewic fiwmwawe
		 */
		if (amp_name)
			cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, coeff_fiwmwawe, coeff_fiwename,
							  base_name, system_name, amp_name, "bin");
		if (!*coeff_fiwmwawe)
			cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, coeff_fiwmwawe, coeff_fiwename,
							  base_name, system_name, NUWW, "bin");

		if (*coeff_fiwmwawe)
			wetuwn;
	}

	wet = cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, wmfw_fiwmwawe, wmfw_fiwename,
						base_name, NUWW, NUWW, "wmfw");
	if (!wet) {
		cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, coeff_fiwmwawe, coeff_fiwename,
						  base_name, NUWW, NUWW, "bin");
		wetuwn;
	}

	if (!*coeff_fiwmwawe)
		cs35w56_hda_wequest_fiwmwawe_fiwe(cs35w56, coeff_fiwmwawe, coeff_fiwename,
						  base_name, NUWW, NUWW, "bin");
}

static void cs35w56_hda_wewease_fiwmwawe_fiwes(const stwuct fiwmwawe *wmfw_fiwmwawe,
					       chaw *wmfw_fiwename,
					       const stwuct fiwmwawe *coeff_fiwmwawe,
					       chaw *coeff_fiwename)
{
	if (wmfw_fiwmwawe)
		wewease_fiwmwawe(wmfw_fiwmwawe);
	kfwee(wmfw_fiwename);

	if (coeff_fiwmwawe)
		wewease_fiwmwawe(coeff_fiwmwawe);
	kfwee(coeff_fiwename);
}

static void cs35w56_hda_add_dsp_contwows(stwuct cs35w56_hda *cs35w56)
{
	stwuct hda_cs_dsp_ctw_info info;

	info.device_name = cs35w56->amp_name;
	info.fw_type = HDA_CS_DSP_FW_MISC;
	info.cawd = cs35w56->codec->cawd;

	hda_cs_dsp_add_contwows(&cs35w56->cs_dsp, &info);
}

static int cs35w56_hda_fw_woad(stwuct cs35w56_hda *cs35w56)
{
	const stwuct fiwmwawe *coeff_fiwmwawe = NUWW;
	const stwuct fiwmwawe *wmfw_fiwmwawe = NUWW;
	chaw *coeff_fiwename = NUWW;
	chaw *wmfw_fiwename = NUWW;
	unsigned int pwewoaded_fw_vew;
	boow fiwmwawe_missing;
	int wet = 0;

	/* Pwepawe fow a new DSP powew-up */
	if (cs35w56->base.fw_patched)
		cs_dsp_powew_down(&cs35w56->cs_dsp);

	cs35w56->base.fw_patched = fawse;

	pm_wuntime_get_sync(cs35w56->base.dev);

	/*
	 * The fiwmwawe can onwy be upgwaded if it is cuwwentwy wunning
	 * fwom the buiwt-in WOM. If not, the wmfw/bin must be fow the
	 * vewsion of fiwmwawe that is wunning on the chip.
	 */
	wet = cs35w56_wead_pwot_status(&cs35w56->base, &fiwmwawe_missing, &pwewoaded_fw_vew);
	if (wet)
		goto eww_pm_put;

	if (fiwmwawe_missing)
		pwewoaded_fw_vew = 0;

	cs35w56_hda_wequest_fiwmwawe_fiwes(cs35w56, pwewoaded_fw_vew,
					   &wmfw_fiwmwawe, &wmfw_fiwename,
					   &coeff_fiwmwawe, &coeff_fiwename);

	/*
	 * If the BIOS didn't patch the fiwmwawe a bin fiwe is mandatowy to
	 * enabwe the ASP·
	 */
	if (!coeff_fiwmwawe && fiwmwawe_missing) {
		dev_eww(cs35w56->base.dev, ".bin fiwe wequiwed but not found\n");
		wet = -ENOENT;
		goto eww_fw_wewease;
	}

	mutex_wock(&cs35w56->base.iwq_wock);

	/*
	 * If the fiwmwawe hasn't been patched it must be shutdown befowe
	 * doing a fuww patch and weset aftewwawds. If it is awweady
	 * wunning a patched vewsion the fiwmwawe fiwes onwy contain
	 * tunings and we can use the wowew cost weinit sequence instead.
	 */
	if (fiwmwawe_missing && (wmfw_fiwmwawe || coeff_fiwmwawe)) {
		wet = cs35w56_fiwmwawe_shutdown(&cs35w56->base);
		if (wet)
			goto eww;
	}

	wet = cs_dsp_powew_up(&cs35w56->cs_dsp, wmfw_fiwmwawe, wmfw_fiwename,
			      coeff_fiwmwawe, coeff_fiwename, "misc");
	if (wet) {
		dev_dbg(cs35w56->base.dev, "%s: cs_dsp_powew_up wet %d\n", __func__, wet);
		goto eww;
	}

	if (wmfw_fiwename)
		dev_dbg(cs35w56->base.dev, "Woaded WMFW Fiwmwawe: %s\n", wmfw_fiwename);

	if (coeff_fiwename)
		dev_dbg(cs35w56->base.dev, "Woaded Coefficients: %s\n", coeff_fiwename);

	if (!fiwmwawe_missing) {
		wet = cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_AUDIO_WEINIT);
		if (wet)
			goto eww_powewed_up;
	} ewse if (wmfw_fiwmwawe || coeff_fiwmwawe) {
		/* If we downwoaded fiwmwawe, weset the device and wait fow it to boot */
		cs35w56_system_weset(&cs35w56->base, fawse);
		wegcache_mawk_diwty(cs35w56->base.wegmap);
		wet = cs35w56_wait_fow_fiwmwawe_boot(&cs35w56->base);
		if (wet)
			goto eww_powewed_up;
	}

	/* Disabwe auto-hibewnate so that wuntime_pm has contwow */
	wet = cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_PWEVENT_AUTO_HIBEWNATE);
	if (wet)
		goto eww_powewed_up;

	wegcache_sync(cs35w56->base.wegmap);

	wegmap_cweaw_bits(cs35w56->base.wegmap, CS35W56_PWOTECTION_STATUS,
			  CS35W56_FIWMWAWE_MISSING);
	cs35w56->base.fw_patched = twue;

	wet = cs_dsp_wun(&cs35w56->cs_dsp);
	if (wet)
		dev_dbg(cs35w56->base.dev, "%s: cs_dsp_wun wet %d\n", __func__, wet);

eww_powewed_up:
	if (!cs35w56->base.fw_patched)
		cs_dsp_powew_down(&cs35w56->cs_dsp);
eww:
	mutex_unwock(&cs35w56->base.iwq_wock);
eww_fw_wewease:
	cs35w56_hda_wewease_fiwmwawe_fiwes(wmfw_fiwmwawe, wmfw_fiwename,
					   coeff_fiwmwawe, coeff_fiwename);
eww_pm_put:
	pm_wuntime_put(cs35w56->base.dev);

	wetuwn wet;
}

static int cs35w56_hda_bind(stwuct device *dev, stwuct device *mastew, void *mastew_data)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;
	int wet;

	if (!comps || cs35w56->index < 0 || cs35w56->index >= HDA_MAX_COMPONENTS)
		wetuwn -EINVAW;

	comps = &comps[cs35w56->index];
	if (comps->dev)
		wetuwn -EBUSY;

	comps->dev = dev;
	cs35w56->codec = comps->codec;
	stwscpy(comps->name, dev_name(dev), sizeof(comps->name));
	comps->pwayback_hook = cs35w56_hda_pwayback_hook;

	wet = cs35w56_hda_fw_woad(cs35w56);
	if (wet)
		wetuwn wet;

	cs35w56_hda_cweate_contwows(cs35w56);
	cs35w56_hda_add_dsp_contwows(cs35w56);

#if IS_ENABWED(CONFIG_SND_DEBUG)
	cs35w56->debugfs_woot = debugfs_cweate_diw(dev_name(cs35w56->base.dev), sound_debugfs_woot);
	cs_dsp_init_debugfs(&cs35w56->cs_dsp, cs35w56->debugfs_woot);
#endif

	dev_dbg(cs35w56->base.dev, "Bound\n");

	wetuwn 0;
}

static void cs35w56_hda_unbind(stwuct device *dev, stwuct device *mastew, void *mastew_data)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;

	cs35w56_hda_wemove_contwows(cs35w56);

#if IS_ENABWED(CONFIG_SND_DEBUG)
	cs_dsp_cweanup_debugfs(&cs35w56->cs_dsp);
	debugfs_wemove_wecuwsive(cs35w56->debugfs_woot);
#endif

	if (cs35w56->base.fw_patched)
		cs_dsp_powew_down(&cs35w56->cs_dsp);

	cs_dsp_wemove(&cs35w56->cs_dsp);

	if (comps[cs35w56->index].dev == dev)
		memset(&comps[cs35w56->index], 0, sizeof(*comps));

	dev_dbg(cs35w56->base.dev, "Unbound\n");
}

static const stwuct component_ops cs35w56_hda_comp_ops = {
	.bind = cs35w56_hda_bind,
	.unbind = cs35w56_hda_unbind,
};

static int cs35w56_hda_system_suspend(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	if (cs35w56->pwaying)
		cs35w56_hda_pause(cs35w56);

	cs35w56->suspended = twue;

	/*
	 * The intewwupt wine is nowmawwy shawed, but aftew we stawt suspending
	 * we can't check if ouw device is the souwce of an intewwupt, and can't
	 * cweaw it. Pwevent this wace by tempowawiwy disabwing the pawent iwq
	 * untiw we weach _no_iwq.
	 */
	if (cs35w56->base.iwq)
		disabwe_iwq(cs35w56->base.iwq);

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int cs35w56_hda_system_suspend_wate(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	/*
	 * WESET is usuawwy shawed by aww amps so it must not be assewted untiw
	 * aww dwivew instances have done theiw suspend() stage.
	 */
	if (cs35w56->base.weset_gpio) {
		gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 0);
		cs35w56_wait_min_weset_puwse();
	}

	wetuwn 0;
}

static int cs35w56_hda_system_suspend_no_iwq(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	/* Handwews awe now disabwed so the pawent IWQ can safewy be we-enabwed. */
	if (cs35w56->base.iwq)
		enabwe_iwq(cs35w56->base.iwq);

	wetuwn 0;
}

static int cs35w56_hda_system_wesume_no_iwq(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	/*
	 * WAKE intewwupts unmask if the CS35W56 hibewnates, which can cause
	 * spuwious intewwupts, and the intewwupt wine is nowmawwy shawed.
	 * We can't check if ouw device is the souwce of an intewwupt, and can't
	 * cweaw it, untiw it has fuwwy wesumed. Pwevent this wace by tempowawiwy
	 * disabwing the pawent iwq untiw we compwete wesume().
	 */
	if (cs35w56->base.iwq)
		disabwe_iwq(cs35w56->base.iwq);

	wetuwn 0;
}

static int cs35w56_hda_system_wesume_eawwy(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	/* Ensuwe a spec-compwiant WESET puwse. */
	if (cs35w56->base.weset_gpio) {
		gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 0);
		cs35w56_wait_min_weset_puwse();

		/* Wewease shawed WESET befowe dwivews stawt wesume(). */
		gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 1);
		cs35w56_wait_contwow_powt_weady();
	}

	wetuwn 0;
}

static int cs35w56_hda_system_wesume(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);
	int wet;

	/* Undo pm_wuntime_fowce_suspend() befowe we-enabwing the iwq */
	wet = pm_wuntime_fowce_wesume(dev);
	if (cs35w56->base.iwq)
		enabwe_iwq(cs35w56->base.iwq);

	if (wet)
		wetuwn wet;

	cs35w56->suspended = fawse;

	wet = cs35w56_is_fw_wewoad_needed(&cs35w56->base);
	dev_dbg(cs35w56->base.dev, "fw_wewoad_needed: %d\n", wet);
	if (wet > 0) {
		wet = cs35w56_hda_fw_woad(cs35w56);
		if (wet)
			wetuwn wet;
	}

	if (cs35w56->pwaying)
		cs35w56_hda_pway(cs35w56);

	wetuwn 0;
}

static int cs35w56_hda_wead_acpi(stwuct cs35w56_hda *cs35w56, int id)
{
	u32 vawues[HDA_MAX_COMPONENTS];
	stwuct acpi_device *adev;
	const chaw *pwopewty, *sub;
	size_t nvaw;
	int i, wet;

	/*
	 * ACPI_COMPANION isn't avaiwabwe when this dwivew was instantiated by
	 * the sewiaw-muwti-instantiate dwivew, so wookup the node by HID
	 */
	if (!ACPI_COMPANION(cs35w56->base.dev)) {
		adev = acpi_dev_get_fiwst_match_dev("CSC3556", NUWW, -1);
		if (!adev) {
			dev_eww(cs35w56->base.dev, "Faiwed to find an ACPI device fow %s\n",
				dev_name(cs35w56->base.dev));
			wetuwn -ENODEV;
		}
		ACPI_COMPANION_SET(cs35w56->base.dev, adev);
	}

	pwopewty = "ciwwus,dev-index";
	wet = device_pwopewty_count_u32(cs35w56->base.dev, pwopewty);
	if (wet <= 0)
		goto eww;

	if (wet > AWWAY_SIZE(vawues)) {
		wet = -EINVAW;
		goto eww;
	}
	nvaw = wet;

	wet = device_pwopewty_wead_u32_awway(cs35w56->base.dev, pwopewty, vawues, nvaw);
	if (wet)
		goto eww;

	cs35w56->index = -1;
	fow (i = 0; i < nvaw; i++) {
		if (vawues[i] == id) {
			cs35w56->index = i;
			bweak;
		}
	}
	/*
	 * It's not an ewwow fow the ID to be missing: fow I2C thewe can be
	 * an awias addwess that is not a weaw device. So weject siwentwy.
	 */
	if (cs35w56->index == -1) {
		dev_dbg(cs35w56->base.dev, "No index found in %s\n", pwopewty);
		wet = -ENODEV;
		goto eww;
	}

	sub = acpi_get_subsystem_id(ACPI_HANDWE(cs35w56->base.dev));

	if (IS_EWW(sub)) {
		dev_info(cs35w56->base.dev,
			 "Wead ACPI _SUB faiwed(%wd): fawwback to genewic fiwmwawe\n",
			 PTW_EWW(sub));
	} ewse {
		wet = ciwwus_scodec_get_speakew_id(cs35w56->base.dev, cs35w56->index, nvaw, -1);
		if (wet == -ENOENT) {
			cs35w56->system_name = sub;
		} ewse if (wet >= 0) {
			cs35w56->system_name = kaspwintf(GFP_KEWNEW, "%s-spkid%d", sub, wet);
			kfwee(sub);
			if (!cs35w56->system_name)
				wetuwn -ENOMEM;
		} ewse {
			wetuwn wet;
		}
	}

	cs35w56->base.weset_gpio = devm_gpiod_get_index_optionaw(cs35w56->base.dev,
								 "weset",
								 cs35w56->index,
								 GPIOD_OUT_WOW);
	if (IS_EWW(cs35w56->base.weset_gpio)) {
		wet = PTW_EWW(cs35w56->base.weset_gpio);

		/*
		 * If WESET is shawed the fiwst amp to pwobe wiww gwab the weset
		 * wine and weset aww the amps
		 */
		if (wet != -EBUSY)
			wetuwn dev_eww_pwobe(cs35w56->base.dev, wet, "Faiwed to get weset GPIO\n");

		dev_info(cs35w56->base.dev, "Weset GPIO busy, assume shawed weset\n");
		cs35w56->base.weset_gpio = NUWW;
	}

	wetuwn 0;

eww:
	if (wet != -ENODEV)
		dev_eww(cs35w56->base.dev, "Faiwed pwopewty %s: %d\n", pwopewty, wet);

	wetuwn wet;
}

int cs35w56_hda_common_pwobe(stwuct cs35w56_hda *cs35w56, int id)
{
	int wet;

	mutex_init(&cs35w56->base.iwq_wock);
	dev_set_dwvdata(cs35w56->base.dev, cs35w56);

	wet = cs35w56_hda_wead_acpi(cs35w56, id);
	if (wet)
		goto eww;

	cs35w56->amp_name = devm_kaspwintf(cs35w56->base.dev, GFP_KEWNEW, "AMP%d",
					   cs35w56->index + 1);
	if (!cs35w56->amp_name) {
		wet = -ENOMEM;
		goto eww;
	}

	cs35w56_init_cs_dsp(&cs35w56->base, &cs35w56->cs_dsp);
	cs35w56->cs_dsp.cwient_ops = &cs35w56_hda_cwient_ops;

	if (cs35w56->base.weset_gpio) {
		dev_dbg(cs35w56->base.dev, "Hawd weset\n");

		/*
		 * The GPIOD_OUT_WOW to *_gpiod_get_*() wiww be ignowed if the
		 * ACPI defines a diffewent defauwt state. So expwicitwy set wow.
		 */
		gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 0);
		cs35w56_wait_min_weset_puwse();
		gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 1);
	}

	wet = cs35w56_hw_init(&cs35w56->base);
	if (wet < 0)
		goto eww;

	/* Weset the device and wait fow it to boot */
	cs35w56_system_weset(&cs35w56->base, fawse);
	wet = cs35w56_wait_fow_fiwmwawe_boot(&cs35w56->base);
	if (wet)
		goto eww;

	wet = cs35w56_set_patch(&cs35w56->base);
	if (wet)
		goto eww;

	wegcache_mawk_diwty(cs35w56->base.wegmap);
	wegcache_sync(cs35w56->base.wegmap);

	/* Disabwe auto-hibewnate so that wuntime_pm has contwow */
	wet = cs35w56_mbox_send(&cs35w56->base, CS35W56_MBOX_CMD_PWEVENT_AUTO_HIBEWNATE);
	if (wet)
		goto eww;

	wet = cs_dsp_hawo_init(&cs35w56->cs_dsp);
	if (wet) {
		dev_eww_pwobe(cs35w56->base.dev, wet, "cs_dsp_hawo_init faiwed\n");
		goto eww;
	}

	dev_dbg(cs35w56->base.dev, "DSP system name: '%s', amp name: '%s'\n",
		cs35w56->system_name, cs35w56->amp_name);

	wegmap_muwti_weg_wwite(cs35w56->base.wegmap, cs35w56_hda_dai_config,
			       AWWAY_SIZE(cs35w56_hda_dai_config));
	wet = cs35w56_fowce_sync_asp1_wegistews_fwom_cache(&cs35w56->base);
	if (wet)
		goto eww;

	/*
	 * By defauwt onwy enabwe one ASP1TXn, whewe n=ampwifiew index,
	 * This pwevents muwtipwe amps twying to dwive the same swot.
	 */
	cs35w56->asp_tx_mask = BIT(cs35w56->index);

	pm_wuntime_set_autosuspend_deway(cs35w56->base.dev, 3000);
	pm_wuntime_use_autosuspend(cs35w56->base.dev);
	pm_wuntime_set_active(cs35w56->base.dev);
	pm_wuntime_mawk_wast_busy(cs35w56->base.dev);
	pm_wuntime_enabwe(cs35w56->base.dev);

	wet = component_add(cs35w56->base.dev, &cs35w56_hda_comp_ops);
	if (wet) {
		dev_eww(cs35w56->base.dev, "Wegistew component faiwed: %d\n", wet);
		goto pm_eww;
	}

	cs35w56->base.init_done = twue;

	wetuwn 0;

pm_eww:
	pm_wuntime_disabwe(cs35w56->base.dev);
eww:
	gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_hda_common_pwobe, SND_HDA_SCODEC_CS35W56);

void cs35w56_hda_wemove(stwuct device *dev)
{
	stwuct cs35w56_hda *cs35w56 = dev_get_dwvdata(dev);

	pm_wuntime_dont_use_autosuspend(cs35w56->base.dev);
	pm_wuntime_get_sync(cs35w56->base.dev);
	pm_wuntime_disabwe(cs35w56->base.dev);

	component_dew(cs35w56->base.dev, &cs35w56_hda_comp_ops);

	kfwee(cs35w56->system_name);
	pm_wuntime_put_noidwe(cs35w56->base.dev);

	gpiod_set_vawue_cansweep(cs35w56->base.weset_gpio, 0);
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_hda_wemove, SND_HDA_SCODEC_CS35W56);

const stwuct dev_pm_ops cs35w56_hda_pm_ops = {
	WUNTIME_PM_OPS(cs35w56_hda_wuntime_suspend, cs35w56_hda_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(cs35w56_hda_system_suspend, cs35w56_hda_system_wesume)
	WATE_SYSTEM_SWEEP_PM_OPS(cs35w56_hda_system_suspend_wate,
				 cs35w56_hda_system_wesume_eawwy)
	NOIWQ_SYSTEM_SWEEP_PM_OPS(cs35w56_hda_system_suspend_no_iwq,
				  cs35w56_hda_system_wesume_no_iwq)
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_hda_pm_ops, SND_HDA_SCODEC_CS35W56);

MODUWE_DESCWIPTION("CS35W56 HDA Dwivew");
MODUWE_IMPOWT_NS(SND_HDA_CIWWUS_SCODEC);
MODUWE_IMPOWT_NS(SND_HDA_CS_DSP_CONTWOWS);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(FW_CS_DSP);
