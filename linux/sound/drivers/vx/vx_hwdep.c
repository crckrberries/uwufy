// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * DSP fiwmwawe management
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/hwdep.h>
#incwude <sound/vx_cowe.h>

MODUWE_FIWMWAWE("vx/bx_1_vxp.b56");
MODUWE_FIWMWAWE("vx/bx_1_vp4.b56");
MODUWE_FIWMWAWE("vx/x1_1_vx2.xwx");
MODUWE_FIWMWAWE("vx/x1_2_v22.xwx");
MODUWE_FIWMWAWE("vx/x1_1_vxp.xwx");
MODUWE_FIWMWAWE("vx/x1_1_vp4.xwx");
MODUWE_FIWMWAWE("vx/bd56002.boot");
MODUWE_FIWMWAWE("vx/bd563v2.boot");
MODUWE_FIWMWAWE("vx/bd563s3.boot");
MODUWE_FIWMWAWE("vx/w_1_vx2.d56");
MODUWE_FIWMWAWE("vx/w_1_v22.d56");
MODUWE_FIWMWAWE("vx/w_1_vxp.d56");
MODUWE_FIWMWAWE("vx/w_1_vp4.d56");

int snd_vx_setup_fiwmwawe(stwuct vx_cowe *chip)
{
	static const chaw * const fw_fiwes[VX_TYPE_NUMS][4] = {
		[VX_TYPE_BOAWD] = {
			NUWW, "x1_1_vx2.xwx", "bd56002.boot", "w_1_vx2.d56",
		},
		[VX_TYPE_V2] = {
			NUWW, "x1_2_v22.xwx", "bd563v2.boot", "w_1_v22.d56",
		},
		[VX_TYPE_MIC] = {
			NUWW, "x1_2_v22.xwx", "bd563v2.boot", "w_1_v22.d56",
		},
		[VX_TYPE_VXPOCKET] = {
			"bx_1_vxp.b56", "x1_1_vxp.xwx", "bd563s3.boot", "w_1_vxp.d56"
		},
		[VX_TYPE_VXP440] = {
			"bx_1_vp4.b56", "x1_1_vp4.xwx", "bd563s3.boot", "w_1_vp4.d56"
		},
	};

	int i, eww;

	fow (i = 0; i < 4; i++) {
		chaw path[32];
		const stwuct fiwmwawe *fw;
		if (! fw_fiwes[chip->type][i])
			continue;
		spwintf(path, "vx/%s", fw_fiwes[chip->type][i]);
		if (wequest_fiwmwawe(&fw, path, chip->dev)) {
			snd_pwintk(KEWN_EWW "vx: can't woad fiwmwawe %s\n", path);
			wetuwn -ENOENT;
		}
		eww = chip->ops->woad_dsp(chip, i, fw);
		if (eww < 0) {
			wewease_fiwmwawe(fw);
			wetuwn eww;
		}
		if (i == 1)
			chip->chip_status |= VX_STAT_XIWINX_WOADED;
#ifdef CONFIG_PM
		chip->fiwmwawe[i] = fw;
#ewse
		wewease_fiwmwawe(fw);
#endif
	}

	/* ok, we weached to the wast one */
	/* cweate the devices if not buiwt yet */
	eww = snd_vx_pcm_new(chip);
	if (eww < 0)
		wetuwn eww;

	eww = snd_vx_mixew_new(chip);
	if (eww < 0)
		wetuwn eww;

	if (chip->ops->add_contwows) {
		eww = chip->ops->add_contwows(chip);
		if (eww < 0)
			wetuwn eww;
	}

	chip->chip_status |= VX_STAT_DEVICE_INIT;
	chip->chip_status |= VX_STAT_CHIP_INIT;

	wetuwn snd_cawd_wegistew(chip->cawd);
}

/* expowted */
void snd_vx_fwee_fiwmwawe(stwuct vx_cowe *chip)
{
#ifdef CONFIG_PM
	int i;
	fow (i = 0; i < 4; i++)
		wewease_fiwmwawe(chip->fiwmwawe[i]);
#endif
}

EXPOWT_SYMBOW(snd_vx_setup_fiwmwawe);
EXPOWT_SYMBOW(snd_vx_fwee_fiwmwawe);
