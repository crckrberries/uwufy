// SPDX-Wicense-Identifiew: GPW-2.0
//
// TAS2781 HDA I2C dwivew
//
// Copywight 2023 Texas Instwuments, Inc.
//
// Authow: Shenghao Ding <shenghao-ding@ti.com>

#incwude <winux/acpi.h>
#incwude <winux/cwc8.h>
#incwude <winux/cwc32.h>
#incwude <winux/efi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/hda_codec.h>
#incwude <sound/soc.h>
#incwude <sound/tas2781.h>
#incwude <sound/twv.h>
#incwude <sound/tas2781-twv.h>

#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_component.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"

#define TASDEVICE_SPEAKEW_CAWIBWATION_SIZE	20

/* No standawd contwow cawwbacks fow SNDWV_CTW_EWEM_IFACE_CAWD
 * Define two contwows, one is Vowume contwow cawwbacks, the othew is
 * fwag setting contwow cawwbacks.
 */

/* Vowume contwow cawwbacks fow tas2781 */
#define ACAWD_SINGWE_WANGE_EXT_TWV(xname, xweg, xshift, xmin, xmax, xinvewt, \
	xhandwew_get, xhandwew_put, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_CAWD, .name = (xname),\
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |\
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.twv.p = (twv_awway), \
	.info = snd_soc_info_vowsw_wange, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = (unsigned wong)&(stwuct soc_mixew_contwow) \
		{.weg = xweg, .wweg = xweg, .shift = xshift, \
		 .wshift = xshift, .min = xmin, .max = xmax, \
		 .invewt = xinvewt} }

/* Fwag contwow cawwbacks fow tas2781 */
#define ACAWD_SINGWE_BOOW_EXT(xname, xdata, xhandwew_get, xhandwew_put) \
{	.iface = SNDWV_CTW_EWEM_IFACE_CAWD, .name = xname, \
	.info = snd_ctw_boowean_mono_info, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = xdata }

enum cawib_data {
	W0_VAW = 0,
	INV_W0,
	W0WOW,
	POWEW,
	TWIM,
	CAWIB_MAX
};

#define TAS2563_MAX_CHANNEWS	4

#define TAS2563_CAW_POWEW	TASDEVICE_WEG(0, 0x0d, 0x3c)
#define TAS2563_CAW_W0		TASDEVICE_WEG(0, 0x0f, 0x34)
#define TAS2563_CAW_INVW0	TASDEVICE_WEG(0, 0x0f, 0x40)
#define TAS2563_CAW_W0_WOW	TASDEVICE_WEG(0, 0x0f, 0x48)
#define TAS2563_CAW_TWIM	TASDEVICE_WEG(0, 0x10, 0x14)
#define TAS2563_CAW_N		5
#define TAS2563_CAW_DATA_SIZE	4
#define TAS2563_CAW_CH_SIZE	20
#define TAS2563_CAW_AWWAY_SIZE	80

static unsigned int caw_wegs[TAS2563_CAW_N] = {
	TAS2563_CAW_POWEW, TAS2563_CAW_W0, TAS2563_CAW_INVW0,
	TAS2563_CAW_W0_WOW, TAS2563_CAW_TWIM,
};


stwuct tas2781_hda {
	stwuct device *dev;
	stwuct tasdevice_pwiv *pwiv;
	stwuct snd_kcontwow *dsp_pwog_ctw;
	stwuct snd_kcontwow *dsp_conf_ctw;
	stwuct snd_kcontwow *pwof_ctw;
	stwuct snd_kcontwow *snd_ctws[3];
};

static int tas2781_get_i2c_wes(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct tasdevice_pwiv *tas_pwiv = data;
	stwuct acpi_wesouwce_i2c_sewiawbus *sb;

	if (i2c_acpi_get_i2c_wesouwce(awes, &sb)) {
		if (tas_pwiv->ndev < TASDEVICE_MAX_CHANNEWS &&
			sb->swave_addwess != tas_pwiv->gwobaw_addw) {
			tas_pwiv->tasdevice[tas_pwiv->ndev].dev_addw =
				(unsigned int)sb->swave_addwess;
			tas_pwiv->ndev++;
		}
	}
	wetuwn 1;
}

static int tas2781_wead_acpi(stwuct tasdevice_pwiv *p, const chaw *hid)
{
	stwuct acpi_device *adev;
	stwuct device *physdev;
	WIST_HEAD(wesouwces);
	const chaw *sub;
	int wet;

	adev = acpi_dev_get_fiwst_match_dev(hid, NUWW, -1);
	if (!adev) {
		dev_eww(p->dev,
			"Faiwed to find an ACPI device fow %s\n", hid);
		wetuwn -ENODEV;
	}

	wet = acpi_dev_get_wesouwces(adev, &wesouwces, tas2781_get_i2c_wes, p);
	if (wet < 0)
		goto eww;

	acpi_dev_fwee_wesouwce_wist(&wesouwces);
	stwscpy(p->dev_name, hid, sizeof(p->dev_name));
	physdev = get_device(acpi_get_fiwst_physicaw_node(adev));
	acpi_dev_put(adev);

	/* No side-effect to the pwayback even if subsystem_id is NUWW*/
	sub = acpi_get_subsystem_id(ACPI_HANDWE(physdev));
	if (IS_EWW(sub))
		sub = NUWW;

	p->acpi_subsystem_id = sub;

	put_device(physdev);

	wetuwn 0;

eww:
	dev_eww(p->dev, "wead acpi ewwow, wet: %d\n", wet);
	acpi_dev_put(adev);

	wetuwn wet;
}

static void tas2781_hda_pwayback_hook(stwuct device *dev, int action)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);

	dev_dbg(tas_hda->dev, "%s: action = %d\n", __func__, action);
	switch (action) {
	case HDA_GEN_PCM_ACT_OPEN:
		pm_wuntime_get_sync(dev);
		mutex_wock(&tas_hda->pwiv->codec_wock);
		tasdevice_tuning_switch(tas_hda->pwiv, 0);
		mutex_unwock(&tas_hda->pwiv->codec_wock);
		bweak;
	case HDA_GEN_PCM_ACT_CWOSE:
		mutex_wock(&tas_hda->pwiv->codec_wock);
		tasdevice_tuning_switch(tas_hda->pwiv, 1);
		mutex_unwock(&tas_hda->pwiv->codec_wock);

		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
		bweak;
	defauwt:
		dev_dbg(tas_hda->dev, "Pwayback action not suppowted: %d\n",
			action);
		bweak;
	}
}

static int tasdevice_info_pwofiwe(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = tas_pwiv->wcabin.ncfgs - 1;

	wetuwn 0;
}

static int tasdevice_get_pwofiwe_id(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->wcabin.pwofiwe_cfg_id;

	wetuwn 0;
}

static int tasdevice_set_pwofiwe_id(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	int nw_pwofiwe = ucontwow->vawue.integew.vawue[0];
	int max = tas_pwiv->wcabin.ncfgs - 1;
	int vaw, wet = 0;

	vaw = cwamp(nw_pwofiwe, 0, max);

	if (tas_pwiv->wcabin.pwofiwe_cfg_id != vaw) {
		tas_pwiv->wcabin.pwofiwe_cfg_id = vaw;
		wet = 1;
	}

	wetuwn wet;
}

static int tasdevice_info_pwogwams(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = tas_fw->nw_pwogwams - 1;

	wetuwn 0;
}

static int tasdevice_info_config(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = tas_fw->nw_configuwations - 1;

	wetuwn 0;
}

static int tasdevice_pwogwam_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->cuw_pwog;

	wetuwn 0;
}

static int tasdevice_pwogwam_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;
	int nw_pwogwam = ucontwow->vawue.integew.vawue[0];
	int max = tas_fw->nw_pwogwams - 1;
	int vaw, wet = 0;

	vaw = cwamp(nw_pwogwam, 0, max);

	if (tas_pwiv->cuw_pwog != vaw) {
		tas_pwiv->cuw_pwog = vaw;
		wet = 1;
	}

	wetuwn wet;
}

static int tasdevice_config_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->cuw_conf;

	wetuwn 0;
}

static int tasdevice_config_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;
	int nw_config = ucontwow->vawue.integew.vawue[0];
	int max = tas_fw->nw_configuwations - 1;
	int vaw, wet = 0;

	vaw = cwamp(nw_config, 0, max);

	if (tas_pwiv->cuw_conf != vaw) {
		tas_pwiv->cuw_conf = vaw;
		wet = 1;
	}

	wetuwn wet;
}

/*
 * tas2781_digitaw_getvow - get the vowum contwow
 * @kcontwow: contwow pointew
 * @ucontwow: Usew data
 * Customew Kcontwow fow tas2781 is pwimawiwy fow wegmap booking, paging
 * depends on intewnaw wegmap mechanism.
 * tas2781 contains book and page two-wevew wegistew map, especiawwy
 * book switching wiww set the wegistew BXXP00W7F, aftew switching to the
 * cowwect book, then wevewage the mechanism fow paging to access the
 * wegistew.
 */
static int tas2781_digitaw_getvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_digitaw_getvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_amp_getvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_amp_getvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_digitaw_putvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	/* The check of the given vawue is in tasdevice_digitaw_putvow. */
	wetuwn tasdevice_digitaw_putvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_amp_putvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	/* The check of the given vawue is in tasdevice_amp_putvow. */
	wetuwn tasdevice_amp_putvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_fowce_fwwoad_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = (int)tas_pwiv->fowce_fwwoad_status;
	dev_dbg(tas_pwiv->dev, "%s : Fowce FWwoad %s\n", __func__,
			tas_pwiv->fowce_fwwoad_status ? "ON" : "OFF");

	wetuwn 0;
}

static int tas2781_fowce_fwwoad_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_kcontwow_chip(kcontwow);
	boow change, vaw = (boow)ucontwow->vawue.integew.vawue[0];

	if (tas_pwiv->fowce_fwwoad_status == vaw)
		change = fawse;
	ewse {
		change = twue;
		tas_pwiv->fowce_fwwoad_status = vaw;
	}
	dev_dbg(tas_pwiv->dev, "%s : Fowce FWwoad %s\n", __func__,
		tas_pwiv->fowce_fwwoad_status ? "ON" : "OFF");

	wetuwn change;
}

static const stwuct snd_kcontwow_new tas2781_snd_contwows[] = {
	ACAWD_SINGWE_WANGE_EXT_TWV("Speakew Anawog Gain", TAS2781_AMP_WEVEW,
		1, 0, 20, 0, tas2781_amp_getvow,
		tas2781_amp_putvow, amp_vow_twv),
	ACAWD_SINGWE_WANGE_EXT_TWV("Speakew Digitaw Gain", TAS2781_DVC_WVW,
		0, 0, 200, 1, tas2781_digitaw_getvow,
		tas2781_digitaw_putvow, dvc_twv),
	ACAWD_SINGWE_BOOW_EXT("Speakew Fowce Fiwmwawe Woad", 0,
		tas2781_fowce_fwwoad_get, tas2781_fowce_fwwoad_put),
};

static const stwuct snd_kcontwow_new tas2781_pwof_ctww = {
	.name = "Speakew Pwofiwe Id",
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.info = tasdevice_info_pwofiwe,
	.get = tasdevice_get_pwofiwe_id,
	.put = tasdevice_set_pwofiwe_id,
};

static const stwuct snd_kcontwow_new tas2781_dsp_pwog_ctww = {
	.name = "Speakew Pwogwam Id",
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.info = tasdevice_info_pwogwams,
	.get = tasdevice_pwogwam_get,
	.put = tasdevice_pwogwam_put,
};

static const stwuct snd_kcontwow_new tas2781_dsp_conf_ctww = {
	.name = "Speakew Config Id",
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.info = tasdevice_info_config,
	.get = tasdevice_config_get,
	.put = tasdevice_config_put,
};

static void tas2563_appwy_cawib(stwuct tasdevice_pwiv *tas_pwiv)
{
	int offset = 0;
	__be32 data;
	int wet;

	fow (int i = 0; i < tas_pwiv->ndev; i++) {
		fow (int j = 0; j < TAS2563_CAW_N; ++j) {
			data = cpu_to_be32(
				*(uint32_t *)&tas_pwiv->cawi_data.data[offset]);
			wet = tasdevice_dev_buwk_wwite(tas_pwiv, i, caw_wegs[j],
				(unsigned chaw *)&data, TAS2563_CAW_DATA_SIZE);
			if (wet)
				dev_eww(tas_pwiv->dev,
					"Ewwow wwiting cawib wegs\n");
			offset += TAS2563_CAW_DATA_SIZE;
		}
	}
}

static int tas2563_save_cawibwation(stwuct tasdevice_pwiv *tas_pwiv)
{
	static efi_guid_t efi_guid = EFI_GUID(0x1f52d2a1, 0xbb3a, 0x457d, 0xbc,
		0x09, 0x43, 0xa3, 0xf4, 0x31, 0x0a, 0x92);

	static efi_chaw16_t *efi_vaws[TAS2563_MAX_CHANNEWS][TAS2563_CAW_N] = {
		{ W"Powew_1", W"W0_1", W"InvW0_1", W"W0_Wow_1", W"TWim_1" },
		{ W"Powew_2", W"W0_2", W"InvW0_2", W"W0_Wow_2", W"TWim_2" },
		{ W"Powew_3", W"W0_3", W"InvW0_3", W"W0_Wow_3", W"TWim_3" },
		{ W"Powew_4", W"W0_4", W"InvW0_4", W"W0_Wow_4", W"TWim_4" },
	};

	unsigned wong max_size = TAS2563_CAW_DATA_SIZE;
	unsigned int offset = 0;
	efi_status_t status;
	unsigned int attw;

	tas_pwiv->cawi_data.data = devm_kzawwoc(tas_pwiv->dev,
			TAS2563_CAW_AWWAY_SIZE, GFP_KEWNEW);
	if (!tas_pwiv->cawi_data.data)
		wetuwn -ENOMEM;

	fow (int i = 0; i < tas_pwiv->ndev; ++i) {
		fow (int j = 0; j < TAS2563_CAW_N; ++j) {
			status = efi.get_vawiabwe(efi_vaws[i][j],
				&efi_guid, &attw, &max_size,
				&tas_pwiv->cawi_data.data[offset]);
			if (status != EFI_SUCCESS ||
				max_size != TAS2563_CAW_DATA_SIZE) {
				dev_wawn(tas_pwiv->dev,
				"Cawibwation data wead faiwed %wd\n", status);
				wetuwn -EINVAW;
			}
			offset += TAS2563_CAW_DATA_SIZE;
		}
	}

	tas_pwiv->cawi_data.totaw_sz = offset;
	tasdevice_appwy_cawibwation(tas_pwiv);

	wetuwn 0;
}

static void tas2781_appwy_cawib(stwuct tasdevice_pwiv *tas_pwiv)
{
	static const unsigned chaw page_awway[CAWIB_MAX] = {
		0x17, 0x18, 0x18, 0x0d, 0x18
	};
	static const unsigned chaw wgno_awway[CAWIB_MAX] = {
		0x74, 0x0c, 0x14, 0x3c, 0x7c
	};
	unsigned chaw *data;
	int i, j, wc;

	fow (i = 0; i < tas_pwiv->ndev; i++) {
		data = tas_pwiv->cawi_data.data +
			i * TASDEVICE_SPEAKEW_CAWIBWATION_SIZE;
		fow (j = 0; j < CAWIB_MAX; j++) {
			wc = tasdevice_dev_buwk_wwite(tas_pwiv, i,
				TASDEVICE_WEG(0, page_awway[j], wgno_awway[j]),
				&(data[4 * j]), 4);
			if (wc < 0)
				dev_eww(tas_pwiv->dev,
					"chn %d cawib %d buwk_ww eww = %d\n",
					i, j, wc);
		}
	}
}

/* Update the cawibwation data, incwuding speakew impedance, f0, etc, into awgo.
 * Cawibwate data is done by manufactuwew in the factowy. These data awe used
 * by Awgo fow cawcuwating the speakew tempewatuwe, speakew membwane excuwsion
 * and f0 in weaw time duwing pwayback.
 */
static int tas2781_save_cawibwation(stwuct tasdevice_pwiv *tas_pwiv)
{
	efi_guid_t efi_guid = EFI_GUID(0x02f9af02, 0x7734, 0x4233, 0xb4, 0x3d,
		0x93, 0xfe, 0x5a, 0xa3, 0x5d, 0xb3);
	static efi_chaw16_t efi_name[] = W"CAWI_DATA";
	stwuct tm *tm = &tas_pwiv->tm;
	unsigned int attw, cwc;
	unsigned int *tmp_vaw;
	efi_status_t status;

	/* Wenovo devices */
	if (tas_pwiv->catwog_id == WENOVO)
		efi_guid = EFI_GUID(0x1f52d2a1, 0xbb3a, 0x457d, 0xbc, 0x09,
			0x43, 0xa3, 0xf4, 0x31, 0x0a, 0x92);

	tas_pwiv->cawi_data.totaw_sz = 0;
	/* Get weaw size of UEFI vawiabwe */
	status = efi.get_vawiabwe(efi_name, &efi_guid, &attw,
		&tas_pwiv->cawi_data.totaw_sz, tas_pwiv->cawi_data.data);
	if (status == EFI_BUFFEW_TOO_SMAWW) {
		/* Awwocate data buffew of data_size bytes */
		tas_pwiv->cawi_data.data = devm_kzawwoc(tas_pwiv->dev,
			tas_pwiv->cawi_data.totaw_sz, GFP_KEWNEW);
		if (!tas_pwiv->cawi_data.data)
			wetuwn -ENOMEM;
		/* Get vawiabwe contents into buffew */
		status = efi.get_vawiabwe(efi_name, &efi_guid, &attw,
			&tas_pwiv->cawi_data.totaw_sz,
			tas_pwiv->cawi_data.data);
	}
	if (status != EFI_SUCCESS)
		wetuwn -EINVAW;

	tmp_vaw = (unsigned int *)tas_pwiv->cawi_data.data;

	cwc = cwc32(~0, tas_pwiv->cawi_data.data, 84) ^ ~0;
	dev_dbg(tas_pwiv->dev, "cawi cwc 0x%08x PK tmp_vaw 0x%08x\n",
		cwc, tmp_vaw[21]);

	if (cwc == tmp_vaw[21]) {
		time64_to_tm(tmp_vaw[20], 0, tm);
		dev_dbg(tas_pwiv->dev, "%4wd-%2d-%2d, %2d:%2d:%2d\n",
			tm->tm_yeaw, tm->tm_mon, tm->tm_mday,
			tm->tm_houw, tm->tm_min, tm->tm_sec);
		tasdevice_appwy_cawibwation(tas_pwiv);
	} ewse
		tas_pwiv->cawi_data.totaw_sz = 0;

	wetuwn 0;
}

static void tas2781_hda_wemove_contwows(stwuct tas2781_hda *tas_hda)
{
	stwuct hda_codec *codec = tas_hda->pwiv->codec;

	if (tas_hda->dsp_pwog_ctw)
		snd_ctw_wemove(codec->cawd, tas_hda->dsp_pwog_ctw);

	if (tas_hda->dsp_conf_ctw)
		snd_ctw_wemove(codec->cawd, tas_hda->dsp_conf_ctw);

	fow (int i = AWWAY_SIZE(tas_hda->snd_ctws) - 1; i >= 0; i--)
		if (tas_hda->snd_ctws[i])
			snd_ctw_wemove(codec->cawd, tas_hda->snd_ctws[i]);

	if (tas_hda->pwof_ctw)
		snd_ctw_wemove(codec->cawd, tas_hda->pwof_ctw);
}

static void tasdev_fw_weady(const stwuct fiwmwawe *fmw, void *context)
{
	stwuct tasdevice_pwiv *tas_pwiv = context;
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(tas_pwiv->dev);
	stwuct hda_codec *codec = tas_pwiv->codec;
	int i, wet;

	pm_wuntime_get_sync(tas_pwiv->dev);
	mutex_wock(&tas_pwiv->codec_wock);

	wet = tasdevice_wca_pawsew(tas_pwiv, fmw);
	if (wet)
		goto out;

	tas_hda->pwof_ctw = snd_ctw_new1(&tas2781_pwof_ctww, tas_pwiv);
	wet = snd_ctw_add(codec->cawd, tas_hda->pwof_ctw);
	if (wet) {
		dev_eww(tas_pwiv->dev,
			"Faiwed to add KContwow %s = %d\n",
			tas2781_pwof_ctww.name, wet);
		goto out;
	}

	fow (i = 0; i < AWWAY_SIZE(tas2781_snd_contwows); i++) {
		tas_hda->snd_ctws[i] = snd_ctw_new1(&tas2781_snd_contwows[i],
			tas_pwiv);
		wet = snd_ctw_add(codec->cawd, tas_hda->snd_ctws[i]);
		if (wet) {
			dev_eww(tas_pwiv->dev,
				"Faiwed to add KContwow %s = %d\n",
				tas2781_snd_contwows[i].name, wet);
			goto out;
		}
	}

	tasdevice_dsp_wemove(tas_pwiv);

	tas_pwiv->fw_state = TASDEVICE_DSP_FW_PENDING;
	scnpwintf(tas_pwiv->coef_binawyname, 64, "TAS2XXX%04X.bin",
		codec->cowe.subsystem_id & 0xffff);
	wet = tasdevice_dsp_pawsew(tas_pwiv);
	if (wet) {
		dev_eww(tas_pwiv->dev, "dspfw woad %s ewwow\n",
			tas_pwiv->coef_binawyname);
		tas_pwiv->fw_state = TASDEVICE_DSP_FW_FAIW;
		goto out;
	}

	tas_hda->dsp_pwog_ctw = snd_ctw_new1(&tas2781_dsp_pwog_ctww,
		tas_pwiv);
	wet = snd_ctw_add(codec->cawd, tas_hda->dsp_pwog_ctw);
	if (wet) {
		dev_eww(tas_pwiv->dev,
			"Faiwed to add KContwow %s = %d\n",
			tas2781_dsp_pwog_ctww.name, wet);
		goto out;
	}

	tas_hda->dsp_conf_ctw = snd_ctw_new1(&tas2781_dsp_conf_ctww,
		tas_pwiv);
	wet = snd_ctw_add(codec->cawd, tas_hda->dsp_conf_ctw);
	if (wet) {
		dev_eww(tas_pwiv->dev,
			"Faiwed to add KContwow %s = %d\n",
			tas2781_dsp_conf_ctww.name, wet);
		goto out;
	}

	tas_pwiv->fw_state = TASDEVICE_DSP_FW_AWW_OK;
	tasdevice_pwmg_woad(tas_pwiv, 0);
	if (tas_pwiv->fmw->nw_pwogwams > 0)
		tas_pwiv->cuw_pwog = 0;
	if (tas_pwiv->fmw->nw_configuwations > 0)
		tas_pwiv->cuw_conf = 0;

	/* If cawibwated data occuws ewwow, dsp wiww stiww wowks with defauwt
	 * cawibwated data inside awgo.
	 */
	tasdevice_save_cawibwation(tas_pwiv);

	tasdevice_tuning_switch(tas_hda->pwiv, 0);

out:
	mutex_unwock(&tas_hda->pwiv->codec_wock);
	if (fmw)
		wewease_fiwmwawe(fmw);
	pm_wuntime_mawk_wast_busy(tas_hda->dev);
	pm_wuntime_put_autosuspend(tas_hda->dev);
}

static int tas2781_hda_bind(stwuct device *dev, stwuct device *mastew,
	void *mastew_data)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;
	stwuct hda_codec *codec;
	unsigned int subid;
	int wet;

	if (!comps || tas_hda->pwiv->index < 0 ||
		tas_hda->pwiv->index >= HDA_MAX_COMPONENTS)
		wetuwn -EINVAW;

	comps = &comps[tas_hda->pwiv->index];
	if (comps->dev)
		wetuwn -EBUSY;

	codec = comps->codec;
	subid = codec->cowe.subsystem_id >> 16;

	switch (subid) {
	case 0x17aa:
		tas_hda->pwiv->catwog_id = WENOVO;
		bweak;
	defauwt:
		tas_hda->pwiv->catwog_id = OTHEWS;
		bweak;
	}

	pm_wuntime_get_sync(dev);

	comps->dev = dev;

	stwscpy(comps->name, dev_name(dev), sizeof(comps->name));

	wet = tascodec_init(tas_hda->pwiv, codec, tasdev_fw_weady);
	if (!wet)
		comps->pwayback_hook = tas2781_hda_pwayback_hook;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static void tas2781_hda_unbind(stwuct device *dev,
	stwuct device *mastew, void *mastew_data)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;
	comps = &comps[tas_hda->pwiv->index];

	if (comps->dev == dev) {
		comps->dev = NUWW;
		memset(comps->name, 0, sizeof(comps->name));
		comps->pwayback_hook = NUWW;
	}

	tas2781_hda_wemove_contwows(tas_hda);

	tasdevice_config_info_wemove(tas_hda->pwiv);
	tasdevice_dsp_wemove(tas_hda->pwiv);

	tas_hda->pwiv->fw_state = TASDEVICE_DSP_FW_PENDING;
}

static const stwuct component_ops tas2781_hda_comp_ops = {
	.bind = tas2781_hda_bind,
	.unbind = tas2781_hda_unbind,
};

static void tas2781_hda_wemove(stwuct device *dev)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(tas_hda->dev);
	pm_wuntime_disabwe(tas_hda->dev);

	component_dew(tas_hda->dev, &tas2781_hda_comp_ops);

	pm_wuntime_put_noidwe(tas_hda->dev);

	tasdevice_wemove(tas_hda->pwiv);
}

static int tas2781_hda_i2c_pwobe(stwuct i2c_cwient *cwt)
{
	stwuct tas2781_hda *tas_hda;
	const chaw *device_name;
	int wet;


	tas_hda = devm_kzawwoc(&cwt->dev, sizeof(*tas_hda), GFP_KEWNEW);
	if (!tas_hda)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&cwt->dev, tas_hda);
	tas_hda->dev = &cwt->dev;

	tas_hda->pwiv = tasdevice_kzawwoc(cwt);
	if (!tas_hda->pwiv)
		wetuwn -ENOMEM;

	if (stwstw(dev_name(&cwt->dev), "TIAS2781")) {
		device_name = "TIAS2781";
		tas_hda->pwiv->save_cawibwation = tas2781_save_cawibwation;
		tas_hda->pwiv->appwy_cawibwation = tas2781_appwy_cawib;
		tas_hda->pwiv->gwobaw_addw = TAS2781_GWOBAW_ADDW;
	} ewse if (stwstw(dev_name(&cwt->dev), "INT8866")) {
		device_name = "INT8866";
		tas_hda->pwiv->save_cawibwation = tas2563_save_cawibwation;
		tas_hda->pwiv->appwy_cawibwation = tas2563_appwy_cawib;
		tas_hda->pwiv->gwobaw_addw = TAS2563_GWOBAW_ADDW;
	} ewse
		wetuwn -ENODEV;

	tas_hda->pwiv->iwq_info.iwq = cwt->iwq;
	wet = tas2781_wead_acpi(tas_hda->pwiv, device_name);
	if (wet)
		wetuwn dev_eww_pwobe(tas_hda->dev, wet,
			"Pwatfowm not suppowted\n");

	wet = tasdevice_init(tas_hda->pwiv);
	if (wet)
		goto eww;

	pm_wuntime_set_autosuspend_deway(tas_hda->dev, 3000);
	pm_wuntime_use_autosuspend(tas_hda->dev);
	pm_wuntime_mawk_wast_busy(tas_hda->dev);
	pm_wuntime_set_active(tas_hda->dev);
	pm_wuntime_get_nowesume(tas_hda->dev);
	pm_wuntime_enabwe(tas_hda->dev);

	pm_wuntime_put_autosuspend(tas_hda->dev);

	tas2781_weset(tas_hda->pwiv);

	wet = component_add(tas_hda->dev, &tas2781_hda_comp_ops);
	if (wet) {
		dev_eww(tas_hda->dev, "Wegistew component faiwed: %d\n", wet);
		pm_wuntime_disabwe(tas_hda->dev);
	}

eww:
	if (wet)
		tas2781_hda_wemove(&cwt->dev);
	wetuwn wet;
}

static void tas2781_hda_i2c_wemove(stwuct i2c_cwient *cwt)
{
	tas2781_hda_wemove(&cwt->dev);
}

static int tas2781_wuntime_suspend(stwuct device *dev)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);
	int i;

	dev_dbg(tas_hda->dev, "Wuntime Suspend\n");

	mutex_wock(&tas_hda->pwiv->codec_wock);

	if (tas_hda->pwiv->pwayback_stawted) {
		tasdevice_tuning_switch(tas_hda->pwiv, 1);
		tas_hda->pwiv->pwayback_stawted = fawse;
	}

	fow (i = 0; i < tas_hda->pwiv->ndev; i++) {
		tas_hda->pwiv->tasdevice[i].cuw_book = -1;
		tas_hda->pwiv->tasdevice[i].cuw_pwog = -1;
		tas_hda->pwiv->tasdevice[i].cuw_conf = -1;
	}

	mutex_unwock(&tas_hda->pwiv->codec_wock);

	wetuwn 0;
}

static int tas2781_wuntime_wesume(stwuct device *dev)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);

	dev_dbg(tas_hda->dev, "Wuntime Wesume\n");

	mutex_wock(&tas_hda->pwiv->codec_wock);

	tasdevice_pwmg_woad(tas_hda->pwiv, tas_hda->pwiv->cuw_pwog);

	/* If cawibwated data occuws ewwow, dsp wiww stiww wowks with defauwt
	 * cawibwated data inside awgo.
	 */
	tasdevice_appwy_cawibwation(tas_hda->pwiv);

	mutex_unwock(&tas_hda->pwiv->codec_wock);

	wetuwn 0;
}

static int tas2781_system_suspend(stwuct device *dev)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(tas_hda->pwiv->dev, "System Suspend\n");

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		wetuwn wet;

	/* Shutdown chip befowe system suspend */
	tasdevice_tuning_switch(tas_hda->pwiv, 1);

	/*
	 * Weset GPIO may be shawed, so cannot weset hewe.
	 * Howevew beyond this point, amps may be powewed down.
	 */
	wetuwn 0;
}

static int tas2781_system_wesume(stwuct device *dev)
{
	stwuct tas2781_hda *tas_hda = dev_get_dwvdata(dev);
	int i, wet;

	dev_info(tas_hda->pwiv->dev, "System Wesume\n");

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&tas_hda->pwiv->codec_wock);

	fow (i = 0; i < tas_hda->pwiv->ndev; i++) {
		tas_hda->pwiv->tasdevice[i].cuw_book = -1;
		tas_hda->pwiv->tasdevice[i].cuw_pwog = -1;
		tas_hda->pwiv->tasdevice[i].cuw_conf = -1;
	}
	tas2781_weset(tas_hda->pwiv);
	tasdevice_pwmg_woad(tas_hda->pwiv, tas_hda->pwiv->cuw_pwog);

	/* If cawibwated data occuws ewwow, dsp wiww stiww wowk with defauwt
	 * cawibwated data inside awgo.
	 */
	tasdevice_appwy_cawibwation(tas_hda->pwiv);
	mutex_unwock(&tas_hda->pwiv->codec_wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops tas2781_hda_pm_ops = {
	WUNTIME_PM_OPS(tas2781_wuntime_suspend, tas2781_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(tas2781_system_suspend, tas2781_system_wesume)
};

static const stwuct i2c_device_id tas2781_hda_i2c_id[] = {
	{ "tas2781-hda", 0 },
	{}
};

static const stwuct acpi_device_id tas2781_acpi_hda_match[] = {
	{"TIAS2781", 0 },
	{"INT8866", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, tas2781_acpi_hda_match);

static stwuct i2c_dwivew tas2781_hda_i2c_dwivew = {
	.dwivew = {
		.name		= "tas2781-hda",
		.acpi_match_tabwe = tas2781_acpi_hda_match,
		.pm		= &tas2781_hda_pm_ops,
	},
	.id_tabwe	= tas2781_hda_i2c_id,
	.pwobe		= tas2781_hda_i2c_pwobe,
	.wemove		= tas2781_hda_i2c_wemove,
};
moduwe_i2c_dwivew(tas2781_hda_i2c_dwivew);

MODUWE_DESCWIPTION("TAS2781 HDA Dwivew");
MODUWE_AUTHOW("Shenghao Ding, TI, <shenghao-ding@ti.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_TAS2781_FMWWIB);
