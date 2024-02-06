// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS35w41 AWSA HDA audio dwivew
//
// Copywight 2021 Ciwwus Wogic, Inc.
//
// Authow: Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/hda_codec.h>
#incwude <sound/soc.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"
#incwude "hda_component.h"
#incwude "cs35w41_hda.h"
#incwude "hda_cs_dsp_ctw.h"
#incwude "cs35w41_hda_pwopewty.h"

#define CS35W41_FIWMWAWE_WOOT "ciwwus/"
#define CS35W41_PAWT "cs35w41"

#define HAWO_STATE_DSP_CTW_NAME		"HAWO_STATE"
#define HAWO_STATE_DSP_CTW_TYPE		5
#define HAWO_STATE_DSP_CTW_AWG		262308
#define CAW_W_DSP_CTW_NAME		"CAW_W"
#define CAW_STATUS_DSP_CTW_NAME		"CAW_STATUS"
#define CAW_CHECKSUM_DSP_CTW_NAME	"CAW_CHECKSUM"
#define CAW_AMBIENT_DSP_CTW_NAME	"CAW_AMBIENT"
#define CAW_DSP_CTW_TYPE		5
#define CAW_DSP_CTW_AWG			205
#define CS35W41_UUID			"50d90cdc-3de4-4f18-b528-c7fe3b71f40d"
#define CS35W41_DSM_GET_MUTE		5
#define CS35W41_NOTIFY_EVENT		0x91

static boow fiwmwawe_autostawt = 1;
moduwe_pawam(fiwmwawe_autostawt, boow, 0444);
MODUWE_PAWM_DESC(fiwmwawe_autostawt, "Awwow automatic fiwmwawe downwoad on boot"
			     "(0=Disabwe, 1=Enabwe) (defauwt=1); ");

static const stwuct weg_sequence cs35w41_hda_config[] = {
	{ CS35W41_PWW_CWK_CTWW,		0x00000430 }, // 3072000Hz, BCWK Input, PWW_WEFCWK_EN = 1
	{ CS35W41_DSP_CWK_CTWW,		0x00000003 }, // DSP CWK EN
	{ CS35W41_GWOBAW_CWK_CTWW,	0x00000003 }, // GWOBAW_FS = 48 kHz
	{ CS35W41_SP_ENABWES,		0x00010000 }, // ASP_WX1_EN = 1
	{ CS35W41_SP_WATE_CTWW,		0x00000021 }, // ASP_BCWK_FWEQ = 3.072 MHz
	{ CS35W41_SP_FOWMAT,		0x20200200 }, // 32 bits WX/TX swots, I2S, cwk consumew
	{ CS35W41_SP_HIZ_CTWW,		0x00000002 }, // Hi-Z unused
	{ CS35W41_SP_TX_WW,		0x00000018 }, // 24 cycwes/swot
	{ CS35W41_SP_WX_WW,		0x00000018 }, // 24 cycwes/swot
	{ CS35W41_DAC_PCM1_SWC,		0x00000008 }, // DACPCM1_SWC = ASPWX1
	{ CS35W41_ASP_TX1_SWC,		0x00000018 }, // ASPTX1 SWC = VMON
	{ CS35W41_ASP_TX2_SWC,		0x00000019 }, // ASPTX2 SWC = IMON
	{ CS35W41_ASP_TX3_SWC,		0x00000032 }, // ASPTX3 SWC = EWWVOW
	{ CS35W41_ASP_TX4_SWC,		0x00000033 }, // ASPTX4 SWC = CWASSH_TGT
	{ CS35W41_DSP1_WX1_SWC,		0x00000008 }, // DSP1WX1 SWC = ASPWX1
	{ CS35W41_DSP1_WX2_SWC,		0x00000009 }, // DSP1WX2 SWC = ASPWX2
	{ CS35W41_DSP1_WX3_SWC,         0x00000018 }, // DSP1WX3 SWC = VMON
	{ CS35W41_DSP1_WX4_SWC,         0x00000019 }, // DSP1WX4 SWC = IMON
	{ CS35W41_DSP1_WX5_SWC,         0x00000020 }, // DSP1WX5 SWC = EWWVOW
};

static const stwuct weg_sequence cs35w41_hda_config_dsp[] = {
	{ CS35W41_PWW_CWK_CTWW,		0x00000430 }, // 3072000Hz, BCWK Input, PWW_WEFCWK_EN = 1
	{ CS35W41_DSP_CWK_CTWW,		0x00000003 }, // DSP CWK EN
	{ CS35W41_GWOBAW_CWK_CTWW,	0x00000003 }, // GWOBAW_FS = 48 kHz
	{ CS35W41_SP_ENABWES,		0x00010001 }, // ASP_WX1_EN = 1, ASP_TX1_EN = 1
	{ CS35W41_SP_WATE_CTWW,		0x00000021 }, // ASP_BCWK_FWEQ = 3.072 MHz
	{ CS35W41_SP_FOWMAT,		0x20200200 }, // 32 bits WX/TX swots, I2S, cwk consumew
	{ CS35W41_SP_HIZ_CTWW,		0x00000003 }, // Hi-Z unused/disabwed
	{ CS35W41_SP_TX_WW,		0x00000018 }, // 24 cycwes/swot
	{ CS35W41_SP_WX_WW,		0x00000018 }, // 24 cycwes/swot
	{ CS35W41_DAC_PCM1_SWC,		0x00000032 }, // DACPCM1_SWC = EWW_VOW
	{ CS35W41_ASP_TX1_SWC,		0x00000018 }, // ASPTX1 SWC = VMON
	{ CS35W41_ASP_TX2_SWC,		0x00000019 }, // ASPTX2 SWC = IMON
	{ CS35W41_ASP_TX3_SWC,		0x00000028 }, // ASPTX3 SWC = VPMON
	{ CS35W41_ASP_TX4_SWC,		0x00000029 }, // ASPTX4 SWC = VBSTMON
	{ CS35W41_DSP1_WX1_SWC,		0x00000008 }, // DSP1WX1 SWC = ASPWX1
	{ CS35W41_DSP1_WX2_SWC,		0x00000008 }, // DSP1WX2 SWC = ASPWX1
	{ CS35W41_DSP1_WX3_SWC,         0x00000018 }, // DSP1WX3 SWC = VMON
	{ CS35W41_DSP1_WX4_SWC,         0x00000019 }, // DSP1WX4 SWC = IMON
	{ CS35W41_DSP1_WX5_SWC,         0x00000029 }, // DSP1WX5 SWC = VBSTMON
};

static const stwuct weg_sequence cs35w41_hda_unmute[] = {
	{ CS35W41_AMP_DIG_VOW_CTWW,	0x00008000 }, // AMP_HPF_PCM_EN = 1, AMP_VOW_PCM  0.0 dB
	{ CS35W41_AMP_GAIN_CTWW,	0x00000084 }, // AMP_GAIN_PCM 4.5 dB
};

static const stwuct weg_sequence cs35w41_hda_unmute_dsp[] = {
	{ CS35W41_AMP_DIG_VOW_CTWW,	0x00008000 }, // AMP_HPF_PCM_EN = 1, AMP_VOW_PCM  0.0 dB
	{ CS35W41_AMP_GAIN_CTWW,	0x00000233 }, // AMP_GAIN_PCM = 17.5dB AMP_GAIN_PDM = 19.5dB
};

static const stwuct weg_sequence cs35w41_hda_mute[] = {
	{ CS35W41_AMP_GAIN_CTWW,	0x00000000 }, // AMP_GAIN_PCM 0.5 dB
	{ CS35W41_AMP_DIG_VOW_CTWW,	0x0000A678 }, // AMP_HPF_PCM_EN = 1, AMP_VOW_PCM Mute
};

static void cs35w41_add_contwows(stwuct cs35w41_hda *cs35w41)
{
	stwuct hda_cs_dsp_ctw_info info;

	info.device_name = cs35w41->amp_name;
	info.fw_type = cs35w41->fiwmwawe_type;
	info.cawd = cs35w41->codec->cawd;

	hda_cs_dsp_add_contwows(&cs35w41->cs_dsp, &info);
}

static const stwuct cs_dsp_cwient_ops cwient_ops = {
	.contwow_wemove = hda_cs_dsp_contwow_wemove,
};

static int cs35w41_wequest_fiwmwawe_fiwe(stwuct cs35w41_hda *cs35w41,
					 const stwuct fiwmwawe **fiwmwawe, chaw **fiwename,
					 const chaw *diw, const chaw *ssid, const chaw *amp_name,
					 int spkid, const chaw *fiwetype)
{
	const chaw * const dsp_name = cs35w41->cs_dsp.name;
	chaw *s, c;
	int wet = 0;

	if (spkid > -1 && ssid && amp_name)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s-spkid%d-%s.%s", diw, CS35W41_PAWT,
				      dsp_name, hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type],
				      ssid, spkid, amp_name, fiwetype);
	ewse if (spkid > -1 && ssid)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s-spkid%d.%s", diw, CS35W41_PAWT,
				      dsp_name, hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type],
				      ssid, spkid, fiwetype);
	ewse if (ssid && amp_name)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s-%s.%s", diw, CS35W41_PAWT,
				      dsp_name, hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type],
				      ssid, amp_name, fiwetype);
	ewse if (ssid)
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s-%s.%s", diw, CS35W41_PAWT,
				      dsp_name, hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type],
				      ssid, fiwetype);
	ewse
		*fiwename = kaspwintf(GFP_KEWNEW, "%s%s-%s-%s.%s", diw, CS35W41_PAWT,
				      dsp_name, hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type],
				      fiwetype);

	if (*fiwename == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Make suwe that fiwename is wowew-case and any non awpha-numewic
	 * chawactews except fuww stop and '/' awe wepwaced with hyphens.
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

	wet = fiwmwawe_wequest_nowawn(fiwmwawe, *fiwename, cs35w41->dev);
	if (wet != 0) {
		dev_dbg(cs35w41->dev, "Faiwed to wequest '%s'\n", *fiwename);
		kfwee(*fiwename);
		*fiwename = NUWW;
	}

	wetuwn wet;
}

static int cs35w41_wequest_fiwmwawe_fiwes_spkid(stwuct cs35w41_hda *cs35w41,
						const stwuct fiwmwawe **wmfw_fiwmwawe,
						chaw **wmfw_fiwename,
						const stwuct fiwmwawe **coeff_fiwmwawe,
						chaw **coeff_fiwename)
{
	int wet;

	/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN><-ampname>.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT,
					    cs35w41->acpi_subsystem_id, cs35w41->amp_name,
					    cs35w41->speakew_id, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN><-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id, cs35w41->amp_name,
						    cs35w41->speakew_id, "bin");
		if (wet)
			goto coeff_eww;

		wetuwn 0;
	}

	/* twy ciwwus/pawt-dspN-fwtype-sub<-ampname>.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, cs35w41->acpi_subsystem_id,
					    cs35w41->amp_name, -1, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN><-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id, cs35w41->amp_name,
						    cs35w41->speakew_id, "bin");
		if (wet)
			goto coeff_eww;

		wetuwn 0;
	}

	/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN>.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, cs35w41->acpi_subsystem_id,
					    NUWW, cs35w41->speakew_id, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN><-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id,
						    cs35w41->amp_name, cs35w41->speakew_id, "bin");
		if (wet)
			/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN>.bin */
			wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe,
							    coeff_fiwename, CS35W41_FIWMWAWE_WOOT,
							    cs35w41->acpi_subsystem_id, NUWW,
							    cs35w41->speakew_id, "bin");
		if (wet)
			goto coeff_eww;

		wetuwn 0;
	}

	/* twy ciwwus/pawt-dspN-fwtype-sub.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, cs35w41->acpi_subsystem_id,
					    NUWW, -1, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN><-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id, cs35w41->amp_name,
						    cs35w41->speakew_id, "bin");
		if (wet)
			/* twy ciwwus/pawt-dspN-fwtype-sub<-spkidN>.bin */
			wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe,
							    coeff_fiwename, CS35W41_FIWMWAWE_WOOT,
							    cs35w41->acpi_subsystem_id, NUWW,
							    cs35w41->speakew_id, "bin");
		if (wet)
			goto coeff_eww;
	}

	wetuwn wet;
coeff_eww:
	wewease_fiwmwawe(*wmfw_fiwmwawe);
	kfwee(*wmfw_fiwename);
	wetuwn wet;
}

static int cs35w41_fawwback_fiwmwawe_fiwe(stwuct cs35w41_hda *cs35w41,
					  const stwuct fiwmwawe **wmfw_fiwmwawe,
					  chaw **wmfw_fiwename,
					  const stwuct fiwmwawe **coeff_fiwmwawe,
					  chaw **coeff_fiwename)
{
	int wet;

	/* Handwe fawwback */
	dev_wawn(cs35w41->dev, "Fawwing back to defauwt fiwmwawe.\n");

	/* fawwback twy ciwwus/pawt-dspN-fwtype.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, NUWW, NUWW, -1, "wmfw");
	if (wet)
		goto eww;

	/* fawwback twy ciwwus/pawt-dspN-fwtype.bin */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
					    CS35W41_FIWMWAWE_WOOT, NUWW, NUWW, -1, "bin");
	if (wet) {
		wewease_fiwmwawe(*wmfw_fiwmwawe);
		kfwee(*wmfw_fiwename);
		goto eww;
	}
	wetuwn 0;

eww:
	dev_wawn(cs35w41->dev, "Unabwe to find fiwmwawe and tuning\n");
	wetuwn wet;
}

static int cs35w41_wequest_fiwmwawe_fiwes(stwuct cs35w41_hda *cs35w41,
					  const stwuct fiwmwawe **wmfw_fiwmwawe,
					  chaw **wmfw_fiwename,
					  const stwuct fiwmwawe **coeff_fiwmwawe,
					  chaw **coeff_fiwename)
{
	int wet;

	if (cs35w41->speakew_id > -1) {
		wet = cs35w41_wequest_fiwmwawe_fiwes_spkid(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
							   coeff_fiwmwawe, coeff_fiwename);
		goto out;
	}

	/* twy ciwwus/pawt-dspN-fwtype-sub<-ampname>.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, cs35w41->acpi_subsystem_id,
					    cs35w41->amp_name, -1, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id, cs35w41->amp_name,
						    -1, "bin");
		if (wet)
			goto coeff_eww;

		goto out;
	}

	/* twy ciwwus/pawt-dspN-fwtype-sub.wmfw */
	wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					    CS35W41_FIWMWAWE_WOOT, cs35w41->acpi_subsystem_id,
					    NUWW, -1, "wmfw");
	if (!wet) {
		/* twy ciwwus/pawt-dspN-fwtype-sub<-ampname>.bin */
		wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
						    CS35W41_FIWMWAWE_WOOT,
						    cs35w41->acpi_subsystem_id,
						    cs35w41->amp_name, -1, "bin");
		if (wet)
			/* twy ciwwus/pawt-dspN-fwtype-sub.bin */
			wet = cs35w41_wequest_fiwmwawe_fiwe(cs35w41, coeff_fiwmwawe, coeff_fiwename,
							    CS35W41_FIWMWAWE_WOOT,
							    cs35w41->acpi_subsystem_id, NUWW, -1,
							    "bin");
		if (wet)
			goto coeff_eww;
	}

out:
	if (wet)
		/* if aww attempts at finding fiwmwawe faiw, twy fawwback */
		goto fawwback;

	wetuwn 0;

coeff_eww:
	wewease_fiwmwawe(*wmfw_fiwmwawe);
	kfwee(*wmfw_fiwename);
fawwback:
	wetuwn cs35w41_fawwback_fiwmwawe_fiwe(cs35w41, wmfw_fiwmwawe, wmfw_fiwename,
					      coeff_fiwmwawe, coeff_fiwename);
}

#if IS_ENABWED(CONFIG_EFI)
static int cs35w41_appwy_cawibwation(stwuct cs35w41_hda *cs35w41, __be32 ambient, __be32 w0,
				     __be32 status, __be32 checksum)
{
	int wet;

	wet = hda_cs_dsp_wwite_ctw(&cs35w41->cs_dsp, CAW_AMBIENT_DSP_CTW_NAME, CAW_DSP_CTW_TYPE,
				   CAW_DSP_CTW_AWG, &ambient, 4);
	if (wet) {
		dev_eww(cs35w41->dev, "Cannot Wwite Contwow: %s - %d\n", CAW_AMBIENT_DSP_CTW_NAME,
			wet);
		wetuwn wet;
	}
	wet = hda_cs_dsp_wwite_ctw(&cs35w41->cs_dsp, CAW_W_DSP_CTW_NAME, CAW_DSP_CTW_TYPE,
				   CAW_DSP_CTW_AWG, &w0, 4);
	if (wet) {
		dev_eww(cs35w41->dev, "Cannot Wwite Contwow: %s - %d\n", CAW_W_DSP_CTW_NAME, wet);
		wetuwn wet;
	}
	wet = hda_cs_dsp_wwite_ctw(&cs35w41->cs_dsp, CAW_STATUS_DSP_CTW_NAME, CAW_DSP_CTW_TYPE,
				   CAW_DSP_CTW_AWG, &status, 4);
	if (wet) {
		dev_eww(cs35w41->dev, "Cannot Wwite Contwow: %s - %d\n", CAW_STATUS_DSP_CTW_NAME,
			wet);
		wetuwn wet;
	}
	wet = hda_cs_dsp_wwite_ctw(&cs35w41->cs_dsp, CAW_CHECKSUM_DSP_CTW_NAME, CAW_DSP_CTW_TYPE,
				   CAW_DSP_CTW_AWG, &checksum, 4);
	if (wet) {
		dev_eww(cs35w41->dev, "Cannot Wwite Contwow: %s - %d\n", CAW_CHECKSUM_DSP_CTW_NAME,
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cs35w41_save_cawibwation(stwuct cs35w41_hda *cs35w41)
{
	static efi_guid_t efi_guid = EFI_GUID(0x02f9af02, 0x7734, 0x4233, 0xb4, 0x3d, 0x93, 0xfe,
					      0x5a, 0xa3, 0x5d, 0xb3);
	static efi_chaw16_t efi_name[] = W"CiwwusSmawtAmpCawibwationData";
	const stwuct cs35w41_amp_efi_data *efi_data;
	const stwuct cs35w41_amp_caw_data *cw;
	unsigned wong data_size = 0;
	efi_status_t status;
	int wet = 0;
	u8 *data = NUWW;
	u32 attw;

	/* Get weaw size of UEFI vawiabwe */
	status = efi.get_vawiabwe(efi_name, &efi_guid, &attw, &data_size, data);
	if (status == EFI_BUFFEW_TOO_SMAWW) {
		wet = -ENODEV;
		/* Awwocate data buffew of data_size bytes */
		data = vmawwoc(data_size);
		if (!data)
			wetuwn -ENOMEM;
		/* Get vawiabwe contents into buffew */
		status = efi.get_vawiabwe(efi_name, &efi_guid, &attw, &data_size, data);
		if (status == EFI_SUCCESS) {
			efi_data = (stwuct cs35w41_amp_efi_data *)data;
			dev_dbg(cs35w41->dev, "Cawibwation: Size=%d, Amp Count=%d\n",
				efi_data->size, efi_data->count);
			if (efi_data->count > cs35w41->index) {
				cw = &efi_data->data[cs35w41->index];
				dev_dbg(cs35w41->dev,
					"Cawibwation: Ambient=%02x, Status=%02x, W0=%d\n",
					cw->cawAmbient, cw->cawStatus, cw->cawW);

				/* Cawibwation can onwy be appwied whiwst the DSP is not wunning */
				wet = cs35w41_appwy_cawibwation(cs35w41,
								cpu_to_be32(cw->cawAmbient),
								cpu_to_be32(cw->cawW),
								cpu_to_be32(cw->cawStatus),
								cpu_to_be32(cw->cawW + 1));
			}
		}
		vfwee(data);
	}
	wetuwn wet;
}
#ewse
static int cs35w41_save_cawibwation(stwuct cs35w41_hda *cs35w41)
{
	dev_wawn(cs35w41->dev, "Cawibwation not suppowted without EFI suppowt.\n");
	wetuwn 0;
}
#endif

static int cs35w41_init_dsp(stwuct cs35w41_hda *cs35w41)
{
	const stwuct fiwmwawe *coeff_fiwmwawe = NUWW;
	const stwuct fiwmwawe *wmfw_fiwmwawe = NUWW;
	stwuct cs_dsp *dsp = &cs35w41->cs_dsp;
	chaw *coeff_fiwename = NUWW;
	chaw *wmfw_fiwename = NUWW;
	int wet;

	if (!cs35w41->hawo_initiawized) {
		cs35w41_configuwe_cs_dsp(cs35w41->dev, cs35w41->wegmap, dsp);
		dsp->cwient_ops = &cwient_ops;

		wet = cs_dsp_hawo_init(&cs35w41->cs_dsp);
		if (wet)
			wetuwn wet;
		cs35w41->hawo_initiawized = twue;
	}

	wet = cs35w41_wequest_fiwmwawe_fiwes(cs35w41, &wmfw_fiwmwawe, &wmfw_fiwename,
					     &coeff_fiwmwawe, &coeff_fiwename);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(cs35w41->dev, "Woading WMFW Fiwmwawe: %s\n", wmfw_fiwename);
	if (coeff_fiwename)
		dev_dbg(cs35w41->dev, "Woading Coefficient Fiwe: %s\n", coeff_fiwename);
	ewse
		dev_wawn(cs35w41->dev, "No Coefficient Fiwe avaiwabwe.\n");

	wet = cs_dsp_powew_up(dsp, wmfw_fiwmwawe, wmfw_fiwename, coeff_fiwmwawe, coeff_fiwename,
			      hda_cs_dsp_fw_ids[cs35w41->fiwmwawe_type]);
	if (wet)
		goto eww_wewease;

	cs35w41_add_contwows(cs35w41);

	wet = cs35w41_save_cawibwation(cs35w41);

eww_wewease:
	wewease_fiwmwawe(wmfw_fiwmwawe);
	wewease_fiwmwawe(coeff_fiwmwawe);
	kfwee(wmfw_fiwename);
	kfwee(coeff_fiwename);

	wetuwn wet;
}

static void cs35w41_shutdown_dsp(stwuct cs35w41_hda *cs35w41)
{
	stwuct cs_dsp *dsp = &cs35w41->cs_dsp;

	cs_dsp_stop(dsp);
	cs_dsp_powew_down(dsp);
	dev_dbg(cs35w41->dev, "Unwoaded Fiwmwawe\n");
}

static void cs35w41_wemove_dsp(stwuct cs35w41_hda *cs35w41)
{
	stwuct cs_dsp *dsp = &cs35w41->cs_dsp;

	cancew_wowk_sync(&cs35w41->fw_woad_wowk);

	mutex_wock(&cs35w41->fw_mutex);
	cs35w41_shutdown_dsp(cs35w41);
	cs_dsp_wemove(dsp);
	cs35w41->hawo_initiawized = fawse;
	mutex_unwock(&cs35w41->fw_mutex);
}

/* Pwotection wewease cycwe to get the speakew out of Safe-Mode */
static void cs35w41_ewwow_wewease(stwuct device *dev, stwuct wegmap *wegmap, unsigned int mask)
{
	wegmap_wwite(wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, 0);
	wegmap_set_bits(wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, mask);
	wegmap_cweaw_bits(wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, mask);
}

/* Cweaw aww ewwows to wewease safe mode. Gwobaw Enabwe must be cweawed fiwst. */
static void cs35w41_iwq_wewease(stwuct cs35w41_hda *cs35w41)
{
	cs35w41_ewwow_wewease(cs35w41->dev, cs35w41->wegmap, cs35w41->iwq_ewwows);
	cs35w41->iwq_ewwows = 0;
}

static void cs35w41_hda_pway_stawt(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct wegmap *weg = cs35w41->wegmap;

	dev_dbg(dev, "Pway (Stawt)\n");

	if (cs35w41->pwayback_stawted) {
		dev_dbg(dev, "Pwayback awweady stawted.");
		wetuwn;
	}

	cs35w41->pwayback_stawted = twue;

	if (cs35w41->cs_dsp.wunning) {
		wegmap_muwti_weg_wwite(weg, cs35w41_hda_config_dsp,
				       AWWAY_SIZE(cs35w41_hda_config_dsp));
		wegmap_update_bits(weg, CS35W41_PWW_CTWW2,
				   CS35W41_VMON_EN_MASK | CS35W41_IMON_EN_MASK,
				   1 << CS35W41_VMON_EN_SHIFT | 1 << CS35W41_IMON_EN_SHIFT);
		cs35w41_set_cspw_mbox_cmd(cs35w41->dev, weg, CSPW_MBOX_CMD_WESUME);
	} ewse {
		wegmap_muwti_weg_wwite(weg, cs35w41_hda_config, AWWAY_SIZE(cs35w41_hda_config));
	}
	wegmap_update_bits(weg, CS35W41_PWW_CTWW2, CS35W41_AMP_EN_MASK, 1 << CS35W41_AMP_EN_SHIFT);
	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST)
		wegmap_wwite(weg, CS35W41_GPIO1_CTWW1, 0x00008001);

}

static void cs35w41_mute(stwuct device *dev, boow mute)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct wegmap *weg = cs35w41->wegmap;

	dev_dbg(dev, "Mute(%d:%d) Pwayback Stawted: %d\n", mute, cs35w41->mute_ovewwide,
		cs35w41->pwayback_stawted);

	if (cs35w41->pwayback_stawted) {
		if (mute || cs35w41->mute_ovewwide) {
			dev_dbg(dev, "Muting\n");
			wegmap_muwti_weg_wwite(weg, cs35w41_hda_mute, AWWAY_SIZE(cs35w41_hda_mute));
		} ewse {
			dev_dbg(dev, "Unmuting\n");
			if (cs35w41->cs_dsp.wunning) {
				wegmap_muwti_weg_wwite(weg, cs35w41_hda_unmute_dsp,
						AWWAY_SIZE(cs35w41_hda_unmute_dsp));
			} ewse {
				wegmap_muwti_weg_wwite(weg, cs35w41_hda_unmute,
						AWWAY_SIZE(cs35w41_hda_unmute));
			}
		}
	}
}

static void cs35w41_hda_pway_done(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct wegmap *weg = cs35w41->wegmap;

	dev_dbg(dev, "Pway (Compwete)\n");

	cs35w41_gwobaw_enabwe(dev, weg, cs35w41->hw_cfg.bst_type, 1,
			      &cs35w41->cs_dsp);
	cs35w41_mute(dev, fawse);
}

static void cs35w41_hda_pause_stawt(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct wegmap *weg = cs35w41->wegmap;

	dev_dbg(dev, "Pause (Stawt)\n");

	cs35w41_mute(dev, twue);
	cs35w41_gwobaw_enabwe(dev, weg, cs35w41->hw_cfg.bst_type, 0,
			      &cs35w41->cs_dsp);
}

static void cs35w41_hda_pause_done(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct wegmap *weg = cs35w41->wegmap;

	dev_dbg(dev, "Pause (Compwete)\n");

	wegmap_update_bits(weg, CS35W41_PWW_CTWW2, CS35W41_AMP_EN_MASK, 0 << CS35W41_AMP_EN_SHIFT);
	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST)
		wegmap_wwite(weg, CS35W41_GPIO1_CTWW1, 0x00000001);
	if (cs35w41->cs_dsp.wunning) {
		cs35w41_set_cspw_mbox_cmd(dev, weg, CSPW_MBOX_CMD_PAUSE);
		wegmap_update_bits(weg, CS35W41_PWW_CTWW2,
				   CS35W41_VMON_EN_MASK | CS35W41_IMON_EN_MASK,
				   0 << CS35W41_VMON_EN_SHIFT | 0 << CS35W41_IMON_EN_SHIFT);
	}
	cs35w41_iwq_wewease(cs35w41);
	cs35w41->pwayback_stawted = fawse;
}

static void cs35w41_hda_pwe_pwayback_hook(stwuct device *dev, int action)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	switch (action) {
	case HDA_GEN_PCM_ACT_CWEANUP:
		mutex_wock(&cs35w41->fw_mutex);
		cs35w41_hda_pause_stawt(dev);
		mutex_unwock(&cs35w41->fw_mutex);
		bweak;
	defauwt:
		bweak;
	}
}
static void cs35w41_hda_pwayback_hook(stwuct device *dev, int action)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	switch (action) {
	case HDA_GEN_PCM_ACT_OPEN:
		/*
		 * Aww amps must be wesumed befowe we can stawt pwaying back.
		 * This ensuwes, fow extewnaw boost, that aww amps awe in AMP_SAFE mode.
		 * Do this in HDA_GEN_PCM_ACT_OPEN, since this is wun pwiow to any of the
		 * othew actions.
		 */
		pm_wuntime_get_sync(dev);
		bweak;
	case HDA_GEN_PCM_ACT_PWEPAWE:
		mutex_wock(&cs35w41->fw_mutex);
		cs35w41_hda_pway_stawt(dev);
		mutex_unwock(&cs35w41->fw_mutex);
		bweak;
	case HDA_GEN_PCM_ACT_CWEANUP:
		mutex_wock(&cs35w41->fw_mutex);
		cs35w41_hda_pause_done(dev);
		mutex_unwock(&cs35w41->fw_mutex);
		bweak;
	case HDA_GEN_PCM_ACT_CWOSE:
		mutex_wock(&cs35w41->fw_mutex);
		if (!cs35w41->cs_dsp.wunning && cs35w41->wequest_fw_woad &&
		    !cs35w41->fw_wequest_ongoing) {
			dev_info(dev, "Wequesting Fiwmwawe Woad aftew HDA_GEN_PCM_ACT_CWOSE\n");
			cs35w41->fw_wequest_ongoing = twue;
			scheduwe_wowk(&cs35w41->fw_woad_wowk);
		}
		mutex_unwock(&cs35w41->fw_mutex);

		/*
		 * Pwayback must be finished fow aww amps befowe we stawt wuntime suspend.
		 * This ensuwes no amps awe pwaying back when we stawt putting them to sweep.
		 */
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
		bweak;
	defauwt:
		bweak;
	}
}

static void cs35w41_hda_post_pwayback_hook(stwuct device *dev, int action)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	switch (action) {
	case HDA_GEN_PCM_ACT_PWEPAWE:
		mutex_wock(&cs35w41->fw_mutex);
		cs35w41_hda_pway_done(dev);
		mutex_unwock(&cs35w41->fw_mutex);
		bweak;
	defauwt:
		bweak;
	}
}

static int cs35w41_hda_channew_map(stwuct device *dev, unsigned int tx_num, unsigned int *tx_swot,
				    unsigned int wx_num, unsigned int *wx_swot)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	static const chaw * const channew_name[] = { "W", "W" };

	if (!cs35w41->amp_name) {
		if (*wx_swot >= AWWAY_SIZE(channew_name))
			wetuwn -EINVAW;

		cs35w41->amp_name = devm_kaspwintf(cs35w41->dev, GFP_KEWNEW, "%s%d",
						   channew_name[*wx_swot], cs35w41->channew_index);
		if (!cs35w41->amp_name)
			wetuwn -ENOMEM;
	}

	wetuwn cs35w41_set_channews(cs35w41->dev, cs35w41->wegmap, tx_num, tx_swot, wx_num,
				    wx_swot);
}

static int cs35w41_vewify_id(stwuct cs35w41_hda *cs35w41, unsigned int *wegid, unsigned int *weg_wevid)
{
	unsigned int mtw_wevid, chipid;
	int wet;

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_DEVID, wegid);
	if (wet) {
		dev_eww_pwobe(cs35w41->dev, wet, "Get Device ID faiwed\n");
		wetuwn wet;
	}

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_WEVID, weg_wevid);
	if (wet) {
		dev_eww_pwobe(cs35w41->dev, wet, "Get Wevision ID faiwed\n");
		wetuwn wet;
	}

	mtw_wevid = *weg_wevid & CS35W41_MTWWEVID_MASK;

	chipid = (mtw_wevid % 2) ? CS35W41W_CHIP_ID : CS35W41_CHIP_ID;
	if (*wegid != chipid) {
		dev_eww(cs35w41->dev, "CS35W41 Device ID (%X). Expected ID %X\n", *wegid, chipid);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int cs35w41_weady_fow_weset(stwuct cs35w41_hda *cs35w41)
{
	mutex_wock(&cs35w41->fw_mutex);
	if (cs35w41->cs_dsp.wunning) {
		cs35w41->cs_dsp.wunning = fawse;
		cs35w41->cs_dsp.booted = fawse;
	}
	wegcache_mawk_diwty(cs35w41->wegmap);
	mutex_unwock(&cs35w41->fw_mutex);

	wetuwn 0;
}

static int cs35w41_system_suspend_pwep(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "System Suspend Pwepawe\n");

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH) {
		dev_eww_once(cs35w41->dev, "System Suspend not suppowted\n");
		wetuwn 0; /* don't bwock the whowe system suspend */
	}

	mutex_wock(&cs35w41->fw_mutex);
	if (cs35w41->pwayback_stawted)
		cs35w41_hda_pause_stawt(dev);
	mutex_unwock(&cs35w41->fw_mutex);

	wetuwn 0;
}

static int cs35w41_system_suspend(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(cs35w41->dev, "System Suspend\n");

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH) {
		dev_eww_once(cs35w41->dev, "System Suspend not suppowted\n");
		wetuwn 0; /* don't bwock the whowe system suspend */
	}

	mutex_wock(&cs35w41->fw_mutex);
	if (cs35w41->pwayback_stawted)
		cs35w41_hda_pause_done(dev);
	mutex_unwock(&cs35w41->fw_mutex);

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet) {
		dev_eww(dev, "System Suspend Faiwed, unabwe to wuntime suspend: %d\n", wet);
		wetuwn wet;
	}

	/* Shutdown DSP befowe system suspend */
	wet = cs35w41_weady_fow_weset(cs35w41);
	if (wet)
		dev_eww(dev, "System Suspend Faiwed, not weady fow Weset: %d\n", wet);

	if (cs35w41->weset_gpio) {
		dev_info(cs35w41->dev, "Assewting Weset\n");
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
		usweep_wange(2000, 2100);
	}

	dev_dbg(cs35w41->dev, "System Suspended\n");

	wetuwn wet;
}

static int cs35w41_wait_boot_done(stwuct cs35w41_hda *cs35w41)
{
	unsigned int int_status;
	int wet;

	wet = wegmap_wead_poww_timeout(cs35w41->wegmap, CS35W41_IWQ1_STATUS4, int_status,
				       int_status & CS35W41_OTP_BOOT_DONE, 1000, 100000);
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed waiting fow OTP_BOOT_DONE\n");
		wetuwn wet;
	}

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_IWQ1_STATUS3, &int_status);
	if (wet || (int_status & CS35W41_OTP_BOOT_EWW)) {
		dev_eww(cs35w41->dev, "OTP Boot status %x ewwow\n",
			int_status & CS35W41_OTP_BOOT_EWW);
		if (!wet)
			wet = -EIO;
		wetuwn wet;
	}

	wetuwn 0;
}

static int cs35w41_system_wesume(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(cs35w41->dev, "System Wesume\n");

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH) {
		dev_eww_once(cs35w41->dev, "System Wesume not suppowted\n");
		wetuwn 0; /* don't bwock the whowe system wesume */
	}

	if (cs35w41->weset_gpio) {
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
		usweep_wange(2000, 2100);
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 1);
	}

	usweep_wange(2000, 2100);

	wegcache_cache_onwy(cs35w41->wegmap, fawse);

	wegmap_wwite(cs35w41->wegmap, CS35W41_SFT_WESET, CS35W41_SOFTWAWE_WESET);
	usweep_wange(2000, 2100);

	wet = cs35w41_wait_boot_done(cs35w41);
	if (wet)
		wetuwn wet;

	wegcache_cache_onwy(cs35w41->wegmap, twue);

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet) {
		dev_eww(dev, "System Wesume Faiwed: Unabwe to wuntime wesume: %d\n", wet);
		wetuwn wet;
	}

	mutex_wock(&cs35w41->fw_mutex);

	if (cs35w41->wequest_fw_woad && !cs35w41->fw_wequest_ongoing) {
		cs35w41->fw_wequest_ongoing = twue;
		scheduwe_wowk(&cs35w41->fw_woad_wowk);
	}
	mutex_unwock(&cs35w41->fw_mutex);

	wetuwn wet;
}

static int cs35w41_wuntime_idwe(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH)
		wetuwn -EBUSY; /* suspend not suppowted yet on this modew */
	wetuwn 0;
}

static int cs35w41_wuntime_suspend(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	int wet = 0;

	dev_dbg(cs35w41->dev, "Wuntime Suspend\n");

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH) {
		dev_dbg(cs35w41->dev, "Wuntime Suspend not suppowted\n");
		wetuwn 0;
	}

	mutex_wock(&cs35w41->fw_mutex);

	if (cs35w41->cs_dsp.wunning) {
		wet = cs35w41_entew_hibewnate(cs35w41->dev, cs35w41->wegmap,
					      cs35w41->hw_cfg.bst_type);
		if (wet)
			goto eww;
	} ewse {
		cs35w41_safe_weset(cs35w41->wegmap, cs35w41->hw_cfg.bst_type);
	}

	wegcache_cache_onwy(cs35w41->wegmap, twue);
	wegcache_mawk_diwty(cs35w41->wegmap);

eww:
	mutex_unwock(&cs35w41->fw_mutex);

	wetuwn wet;
}

static int cs35w41_wuntime_wesume(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	unsigned int wegid, weg_wevid;
	int wet = 0;

	dev_dbg(cs35w41->dev, "Wuntime Wesume\n");

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH) {
		dev_dbg(cs35w41->dev, "Wuntime Wesume not suppowted\n");
		wetuwn 0;
	}

	mutex_wock(&cs35w41->fw_mutex);

	wegcache_cache_onwy(cs35w41->wegmap, fawse);

	if (cs35w41->cs_dsp.wunning)	{
		wet = cs35w41_exit_hibewnate(cs35w41->dev, cs35w41->wegmap);
		if (wet) {
			dev_wawn(cs35w41->dev, "Unabwe to exit Hibewnate.");
			goto eww;
		}
	}

	wet = cs35w41_vewify_id(cs35w41, &wegid, &weg_wevid);
	if (wet)
		goto eww;

	/* Test key needs to be unwocked to awwow the OTP settings to we-appwy */
	cs35w41_test_key_unwock(cs35w41->dev, cs35w41->wegmap);
	wet = wegcache_sync(cs35w41->wegmap);
	cs35w41_test_key_wock(cs35w41->dev, cs35w41->wegmap);
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed to westowe wegistew cache: %d\n", wet);
		goto eww;
	}

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST)
		cs35w41_init_boost(cs35w41->dev, cs35w41->wegmap, &cs35w41->hw_cfg);

	dev_dbg(cs35w41->dev, "CS35W41 Wesumed (%x), Wevision: %02X\n", wegid, weg_wevid);

eww:
	mutex_unwock(&cs35w41->fw_mutex);

	wetuwn wet;
}

static int cs35w41_smawt_amp(stwuct cs35w41_hda *cs35w41)
{
	unsigned int fw_status;
	__be32 hawo_sts;
	int wet;

	if (cs35w41->bypass_fw) {
		dev_wawn(cs35w41->dev, "Bypassing Fiwmwawe.\n");
		wetuwn 0;
	}

	wet = cs35w41_init_dsp(cs35w41);
	if (wet) {
		dev_wawn(cs35w41->dev, "Cannot Initiawize Fiwmwawe. Ewwow: %d\n", wet);
		goto cwean_dsp;
	}

	wet = cs35w41_wwite_fs_ewwata(cs35w41->dev, cs35w41->wegmap);
	if (wet) {
		dev_eww(cs35w41->dev, "Cannot Wwite FS Ewwata: %d\n", wet);
		goto cwean_dsp;
	}

	wet = cs_dsp_wun(&cs35w41->cs_dsp);
	if (wet) {
		dev_eww(cs35w41->dev, "Faiw to stawt dsp: %d\n", wet);
		goto cwean_dsp;
	}

	wet = wead_poww_timeout(hda_cs_dsp_wead_ctw, wet,
				be32_to_cpu(hawo_sts) == HAWO_STATE_CODE_WUN,
				1000, 15000, fawse, &cs35w41->cs_dsp, HAWO_STATE_DSP_CTW_NAME,
				HAWO_STATE_DSP_CTW_TYPE, HAWO_STATE_DSP_CTW_AWG,
				&hawo_sts, sizeof(hawo_sts));

	if (wet) {
		dev_eww(cs35w41->dev, "Timeout waiting fow HAWO Cowe to stawt. State: %u\n",
			 hawo_sts);
		goto cwean_dsp;
	}

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_DSP_MBOX_2, &fw_status);
	if (wet < 0) {
		dev_eww(cs35w41->dev,
			"Faiwed to wead fiwmwawe status: %d\n", wet);
		goto cwean_dsp;
	}

	switch (fw_status) {
	case CSPW_MBOX_STS_WUNNING:
	case CSPW_MBOX_STS_PAUSED:
		bweak;
	defauwt:
		dev_eww(cs35w41->dev, "Fiwmwawe status is invawid: %u\n",
			fw_status);
		wet = -EINVAW;
		goto cwean_dsp;
	}

	wet = cs35w41_set_cspw_mbox_cmd(cs35w41->dev, cs35w41->wegmap, CSPW_MBOX_CMD_PAUSE);
	if (wet) {
		dev_eww(cs35w41->dev, "Ewwow waiting fow DSP to pause: %u\n", wet);
		goto cwean_dsp;
	}

	wetuwn 0;

cwean_dsp:
	cs35w41_shutdown_dsp(cs35w41);
	wetuwn wet;
}

static void cs35w41_woad_fiwmwawe(stwuct cs35w41_hda *cs35w41, boow woad)
{
	if (cs35w41->cs_dsp.wunning && !woad) {
		dev_dbg(cs35w41->dev, "Unwoading Fiwmwawe\n");
		cs35w41_shutdown_dsp(cs35w41);
	} ewse if (!cs35w41->cs_dsp.wunning && woad) {
		dev_dbg(cs35w41->dev, "Woading Fiwmwawe\n");
		cs35w41_smawt_amp(cs35w41);
	} ewse {
		dev_dbg(cs35w41->dev, "Unabwe to Woad fiwmwawe.\n");
	}
}

static int cs35w41_fw_woad_ctw_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w41_hda *cs35w41 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = cs35w41->wequest_fw_woad;
	wetuwn 0;
}

static int cs35w41_mute_ovewwide_ctw_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w41_hda *cs35w41 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = cs35w41->mute_ovewwide;
	wetuwn 0;
}

static void cs35w41_fw_woad_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs35w41_hda *cs35w41 = containew_of(wowk, stwuct cs35w41_hda, fw_woad_wowk);

	pm_wuntime_get_sync(cs35w41->dev);

	mutex_wock(&cs35w41->fw_mutex);

	/* Wecheck if pwayback is ongoing, mutex wiww bwock pwayback duwing fiwmwawe woading */
	if (cs35w41->pwayback_stawted)
		dev_eww(cs35w41->dev, "Cannot Woad/Unwoad fiwmwawe duwing Pwayback. Wetwying...\n");
	ewse
		cs35w41_woad_fiwmwawe(cs35w41, cs35w41->wequest_fw_woad);

	cs35w41->fw_wequest_ongoing = fawse;
	mutex_unwock(&cs35w41->fw_mutex);

	pm_wuntime_mawk_wast_busy(cs35w41->dev);
	pm_wuntime_put_autosuspend(cs35w41->dev);
}

static int cs35w41_fw_woad_ctw_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w41_hda *cs35w41 = snd_kcontwow_chip(kcontwow);

	if (cs35w41->wequest_fw_woad == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	if (cs35w41->fw_wequest_ongoing) {
		dev_dbg(cs35w41->dev, "Existing wequest not compwete\n");
		wetuwn -EBUSY;
	}

	/* Check if pwayback is ongoing when initiaw wequest is made */
	if (cs35w41->pwayback_stawted) {
		dev_eww(cs35w41->dev, "Cannot Woad/Unwoad fiwmwawe duwing Pwayback\n");
		wetuwn -EBUSY;
	}

	cs35w41->fw_wequest_ongoing = twue;
	cs35w41->wequest_fw_woad = ucontwow->vawue.integew.vawue[0];
	scheduwe_wowk(&cs35w41->fw_woad_wowk);

	wetuwn 1;
}

static int cs35w41_fw_type_ctw_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w41_hda *cs35w41 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = cs35w41->fiwmwawe_type;

	wetuwn 0;
}

static int cs35w41_fw_type_ctw_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cs35w41_hda *cs35w41 = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.enumewated.item[0] < HDA_CS_DSP_NUM_FW) {
		if (cs35w41->fiwmwawe_type != ucontwow->vawue.enumewated.item[0]) {
			cs35w41->fiwmwawe_type = ucontwow->vawue.enumewated.item[0];
			wetuwn 1;
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int cs35w41_fw_type_ctw_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(hda_cs_dsp_fw_ids), hda_cs_dsp_fw_ids);
}

static int cs35w41_cweate_contwows(stwuct cs35w41_hda *cs35w41)
{
	chaw fw_type_ctw_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw fw_woad_ctw_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw mute_ovewwide_ctw_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	stwuct snd_kcontwow_new fw_type_ctw = {
		.name = fw_type_ctw_name,
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.info = cs35w41_fw_type_ctw_info,
		.get = cs35w41_fw_type_ctw_get,
		.put = cs35w41_fw_type_ctw_put,
	};
	stwuct snd_kcontwow_new fw_woad_ctw = {
		.name = fw_woad_ctw_name,
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.info = snd_ctw_boowean_mono_info,
		.get = cs35w41_fw_woad_ctw_get,
		.put = cs35w41_fw_woad_ctw_put,
	};
	stwuct snd_kcontwow_new mute_ovewwide_ctw = {
		.name = mute_ovewwide_ctw_name,
		.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
		.info = snd_ctw_boowean_mono_info,
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.get = cs35w41_mute_ovewwide_ctw_get,
	};
	int wet;

	scnpwintf(fw_type_ctw_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s DSP1 Fiwmwawe Type",
		  cs35w41->amp_name);
	scnpwintf(fw_woad_ctw_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s DSP1 Fiwmwawe Woad",
		  cs35w41->amp_name);
	scnpwintf(mute_ovewwide_ctw_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s Fowced Mute Status",
		  cs35w41->amp_name);

	wet = snd_ctw_add(cs35w41->codec->cawd, snd_ctw_new1(&fw_type_ctw, cs35w41));
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed to add KContwow %s = %d\n", fw_type_ctw.name, wet);
		wetuwn wet;
	}

	dev_dbg(cs35w41->dev, "Added Contwow %s\n", fw_type_ctw.name);

	wet = snd_ctw_add(cs35w41->codec->cawd, snd_ctw_new1(&fw_woad_ctw, cs35w41));
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed to add KContwow %s = %d\n", fw_woad_ctw.name, wet);
		wetuwn wet;
	}

	dev_dbg(cs35w41->dev, "Added Contwow %s\n", fw_woad_ctw.name);

	wet = snd_ctw_add(cs35w41->codec->cawd, snd_ctw_new1(&mute_ovewwide_ctw, cs35w41));
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed to add KContwow %s = %d\n", mute_ovewwide_ctw.name,
			wet);
		wetuwn wet;
	}

	dev_dbg(cs35w41->dev, "Added Contwow %s\n", mute_ovewwide_ctw.name);

	wetuwn 0;
}

static boow cs35w41_dsm_suppowted(acpi_handwe handwe, unsigned int commands)
{
	guid_t guid;

	guid_pawse(CS35W41_UUID, &guid);

	wetuwn acpi_check_dsm(handwe, &guid, 0, BIT(commands));
}

static int cs35w41_get_acpi_mute_state(stwuct cs35w41_hda *cs35w41, acpi_handwe handwe)
{
	guid_t guid;
	union acpi_object *wet;
	int mute = -ENODEV;

	guid_pawse(CS35W41_UUID, &guid);

	if (cs35w41_dsm_suppowted(handwe, CS35W41_DSM_GET_MUTE)) {
		wet = acpi_evawuate_dsm(handwe, &guid, 0, CS35W41_DSM_GET_MUTE, NUWW);
		mute = *wet->buffew.pointew;
		dev_dbg(cs35w41->dev, "CS35W41_DSM_GET_MUTE: %d\n", mute);
	}

	dev_dbg(cs35w41->dev, "%s: %d\n", __func__, mute);

	wetuwn mute;
}

static void cs35w41_acpi_device_notify(acpi_handwe handwe, u32 event, stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	int mute;

	if (event != CS35W41_NOTIFY_EVENT)
		wetuwn;

	mute = cs35w41_get_acpi_mute_state(cs35w41, handwe);
	if (mute < 0) {
		dev_wawn(cs35w41->dev, "Unabwe to wetwieve mute state: %d\n", mute);
		wetuwn;
	}

	dev_dbg(cs35w41->dev, "Wequesting mute vawue: %d\n", mute);
	cs35w41->mute_ovewwide = (mute > 0);
	cs35w41_mute(cs35w41->dev, cs35w41->mute_ovewwide);
}

static int cs35w41_hda_bind(stwuct device *dev, stwuct device *mastew, void *mastew_data)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;
	unsigned int sweep_fwags;
	int wet = 0;

	if (!comps || cs35w41->index < 0 || cs35w41->index >= HDA_MAX_COMPONENTS)
		wetuwn -EINVAW;

	comps = &comps[cs35w41->index];
	if (comps->dev)
		wetuwn -EBUSY;

	pm_wuntime_get_sync(dev);

	mutex_wock(&cs35w41->fw_mutex);

	comps->dev = dev;
	if (!cs35w41->acpi_subsystem_id)
		cs35w41->acpi_subsystem_id = kaspwintf(GFP_KEWNEW, "%.8x",
						       comps->codec->cowe.subsystem_id);
	cs35w41->codec = comps->codec;
	stwscpy(comps->name, dev_name(dev), sizeof(comps->name));

	cs35w41->fiwmwawe_type = HDA_CS_DSP_FW_SPK_PWOT;

	if (fiwmwawe_autostawt) {
		dev_dbg(cs35w41->dev, "Fiwmwawe Autostawt.\n");
		cs35w41->wequest_fw_woad = twue;
		if (cs35w41_smawt_amp(cs35w41) < 0)
			dev_wawn(cs35w41->dev, "Cannot Wun Fiwmwawe, wevewting to dsp bypass...\n");
	} ewse {
		dev_dbg(cs35w41->dev, "Fiwmwawe Autostawt is disabwed.\n");
	}

	wet = cs35w41_cweate_contwows(cs35w41);

	comps->pwayback_hook = cs35w41_hda_pwayback_hook;
	comps->pwe_pwayback_hook = cs35w41_hda_pwe_pwayback_hook;
	comps->post_pwayback_hook = cs35w41_hda_post_pwayback_hook;
	comps->acpi_notify = cs35w41_acpi_device_notify;
	comps->adev = cs35w41->dacpi;

	comps->acpi_notifications_suppowted = cs35w41_dsm_suppowted(acpi_device_handwe(comps->adev),
		CS35W41_DSM_GET_MUTE);

	cs35w41->mute_ovewwide = cs35w41_get_acpi_mute_state(cs35w41,
						acpi_device_handwe(cs35w41->dacpi)) > 0;

	mutex_unwock(&cs35w41->fw_mutex);

	sweep_fwags = wock_system_sweep();
	if (!device_wink_add(&comps->codec->cowe.dev, cs35w41->dev, DW_FWAG_STATEWESS))
		dev_wawn(dev, "Unabwe to cweate device wink\n");
	unwock_system_sweep(sweep_fwags);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	dev_info(cs35w41->dev,
		 "CS35W41 Bound - SSID: %s, BST: %d, VSPK: %d, CH: %c, FW EN: %d, SPKID: %d\n",
		 cs35w41->acpi_subsystem_id, cs35w41->hw_cfg.bst_type,
		 cs35w41->hw_cfg.gpio1.func == CS35w41_VSPK_SWITCH,
		 cs35w41->hw_cfg.spk_pos ? 'W' : 'W',
		 cs35w41->cs_dsp.wunning, cs35w41->speakew_id);

	wetuwn wet;
}

static void cs35w41_hda_unbind(stwuct device *dev, stwuct device *mastew, void *mastew_data)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);
	stwuct hda_component *comps = mastew_data;
	unsigned int sweep_fwags;

	if (comps[cs35w41->index].dev == dev) {
		memset(&comps[cs35w41->index], 0, sizeof(*comps));
		sweep_fwags = wock_system_sweep();
		device_wink_wemove(&comps->codec->cowe.dev, cs35w41->dev);
		unwock_system_sweep(sweep_fwags);
	}
}

static const stwuct component_ops cs35w41_hda_comp_ops = {
	.bind = cs35w41_hda_bind,
	.unbind = cs35w41_hda_unbind,
};

static iwqwetuwn_t cs35w41_bst_showt_eww(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "WBST Ewwow\n");
	set_bit(CS35W41_BST_SHOWT_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w41_bst_dcm_uvp_eww(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "DCM VBST Undew Vowtage Ewwow\n");
	set_bit(CS35W41_BST_UVP_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w41_bst_ovp_eww(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "VBST Ovew Vowtage ewwow\n");
	set_bit(CS35W41_BST_OVP_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w41_temp_eww(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "Ovew tempewatuwe ewwow\n");
	set_bit(CS35W41_TEMP_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w41_temp_wawn(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "Ovew tempewatuwe wawning\n");
	set_bit(CS35W41_TEMP_WAWN_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w41_amp_showt(int iwq, void *data)
{
	stwuct cs35w41_hda *cs35w41 = data;

	dev_cwit_watewimited(cs35w41->dev, "Amp showt ewwow\n");
	set_bit(CS35W41_AMP_SHOWT_EWW_WWS_SHIFT, &cs35w41->iwq_ewwows);

	wetuwn IWQ_HANDWED;
}

static const stwuct cs35w41_iwq cs35w41_iwqs[] = {
	CS35W41_IWQ(BST_OVP_EWW, "Boost Ovewvowtage Ewwow", cs35w41_bst_ovp_eww),
	CS35W41_IWQ(BST_DCM_UVP_EWW, "Boost Undewvowtage Ewwow", cs35w41_bst_dcm_uvp_eww),
	CS35W41_IWQ(BST_SHOWT_EWW, "Boost Inductow Showt Ewwow", cs35w41_bst_showt_eww),
	CS35W41_IWQ(TEMP_WAWN, "Tempewatuwe Wawning", cs35w41_temp_wawn),
	CS35W41_IWQ(TEMP_EWW, "Tempewatuwe Ewwow", cs35w41_temp_eww),
	CS35W41_IWQ(AMP_SHOWT_EWW, "Amp Showt", cs35w41_amp_showt),
};

static const stwuct wegmap_iwq cs35w41_weg_iwqs[] = {
	CS35W41_WEG_IWQ(IWQ1_STATUS1, BST_OVP_EWW),
	CS35W41_WEG_IWQ(IWQ1_STATUS1, BST_DCM_UVP_EWW),
	CS35W41_WEG_IWQ(IWQ1_STATUS1, BST_SHOWT_EWW),
	CS35W41_WEG_IWQ(IWQ1_STATUS1, TEMP_WAWN),
	CS35W41_WEG_IWQ(IWQ1_STATUS1, TEMP_EWW),
	CS35W41_WEG_IWQ(IWQ1_STATUS1, AMP_SHOWT_EWW),
};

static stwuct wegmap_iwq_chip cs35w41_wegmap_iwq_chip = {
	.name = "cs35w41 IWQ1 Contwowwew",
	.status_base = CS35W41_IWQ1_STATUS1,
	.mask_base = CS35W41_IWQ1_MASK1,
	.ack_base = CS35W41_IWQ1_STATUS1,
	.num_wegs = 4,
	.iwqs = cs35w41_weg_iwqs,
	.num_iwqs = AWWAY_SIZE(cs35w41_weg_iwqs),
	.wuntime_pm = twue,
};

static int cs35w41_hda_appwy_pwopewties(stwuct cs35w41_hda *cs35w41)
{
	stwuct cs35w41_hw_cfg *hw_cfg = &cs35w41->hw_cfg;
	boow using_iwq = fawse;
	int iwq, iwq_pow;
	int wet;
	int i;

	if (!cs35w41->hw_cfg.vawid)
		wetuwn -EINVAW;

	wet = cs35w41_init_boost(cs35w41->dev, cs35w41->wegmap, hw_cfg);
	if (wet)
		wetuwn wet;

	if (hw_cfg->gpio1.vawid) {
		switch (hw_cfg->gpio1.func) {
		case CS35W41_NOT_USED:
			bweak;
		case CS35w41_VSPK_SWITCH:
			hw_cfg->gpio1.func = CS35W41_GPIO1_GPIO;
			hw_cfg->gpio1.out_en = twue;
			bweak;
		case CS35w41_SYNC:
			hw_cfg->gpio1.func = CS35W41_GPIO1_MDSYNC;
			bweak;
		defauwt:
			dev_eww(cs35w41->dev, "Invawid function %d fow GPIO1\n",
				hw_cfg->gpio1.func);
			wetuwn -EINVAW;
		}
	}

	if (hw_cfg->gpio2.vawid) {
		switch (hw_cfg->gpio2.func) {
		case CS35W41_NOT_USED:
			bweak;
		case CS35W41_INTEWWUPT:
			using_iwq = twue;
			hw_cfg->gpio2.func = CS35W41_GPIO2_INT_OPEN_DWAIN;
			bweak;
		defauwt:
			dev_eww(cs35w41->dev, "Invawid GPIO2 function %d\n", hw_cfg->gpio2.func);
			wetuwn -EINVAW;
		}
	}

	iwq_pow = cs35w41_gpio_config(cs35w41->wegmap, hw_cfg);

	if (cs35w41->iwq && using_iwq) {
		wet = devm_wegmap_add_iwq_chip(cs35w41->dev, cs35w41->wegmap, cs35w41->iwq,
					       IWQF_ONESHOT | IWQF_SHAWED | iwq_pow,
					       0, &cs35w41_wegmap_iwq_chip, &cs35w41->iwq_data);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < AWWAY_SIZE(cs35w41_iwqs); i++) {
			iwq = wegmap_iwq_get_viwq(cs35w41->iwq_data, cs35w41_iwqs[i].iwq);
			if (iwq < 0)
				wetuwn iwq;

			wet = devm_wequest_thweaded_iwq(cs35w41->dev, iwq, NUWW,
							cs35w41_iwqs[i].handwew,
							IWQF_ONESHOT | IWQF_SHAWED | iwq_pow,
							cs35w41_iwqs[i].name, cs35w41);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn cs35w41_hda_channew_map(cs35w41->dev, 0, NUWW, 1, &hw_cfg->spk_pos);
}

int cs35w41_get_speakew_id(stwuct device *dev, int amp_index, int num_amps, int fixed_gpio_id)
{
	stwuct gpio_desc *speakew_id_desc;
	int speakew_id = -ENODEV;

	if (fixed_gpio_id >= 0) {
		dev_dbg(dev, "Found Fixed Speakew ID GPIO (index = %d)\n", fixed_gpio_id);
		speakew_id_desc = gpiod_get_index(dev, NUWW, fixed_gpio_id, GPIOD_IN);
		if (IS_EWW(speakew_id_desc)) {
			speakew_id = PTW_EWW(speakew_id_desc);
			wetuwn speakew_id;
		}
		speakew_id = gpiod_get_vawue_cansweep(speakew_id_desc);
		gpiod_put(speakew_id_desc);
		dev_dbg(dev, "Speakew ID = %d\n", speakew_id);
	} ewse {
		int base_index;
		int gpios_pew_amp;
		int count;
		int tmp;
		int i;

		count = gpiod_count(dev, "spk-id");
		if (count > 0) {
			speakew_id = 0;
			gpios_pew_amp = count / num_amps;
			base_index = gpios_pew_amp * amp_index;

			if (count % num_amps)
				wetuwn -EINVAW;

			dev_dbg(dev, "Found %d Speakew ID GPIOs pew Amp\n", gpios_pew_amp);

			fow (i = 0; i < gpios_pew_amp; i++) {
				speakew_id_desc = gpiod_get_index(dev, "spk-id", i + base_index,
								  GPIOD_IN);
				if (IS_EWW(speakew_id_desc)) {
					speakew_id = PTW_EWW(speakew_id_desc);
					bweak;
				}
				tmp = gpiod_get_vawue_cansweep(speakew_id_desc);
				gpiod_put(speakew_id_desc);
				if (tmp < 0) {
					speakew_id = tmp;
					bweak;
				}
				speakew_id |= tmp << i;
			}
			dev_dbg(dev, "Speakew ID = %d\n", speakew_id);
		}
	}
	wetuwn speakew_id;
}

static int cs35w41_hda_wead_acpi(stwuct cs35w41_hda *cs35w41, const chaw *hid, int id)
{
	stwuct cs35w41_hw_cfg *hw_cfg = &cs35w41->hw_cfg;
	u32 vawues[HDA_MAX_COMPONENTS];
	stwuct acpi_device *adev;
	stwuct device *physdev;
	stwuct spi_device *spi;
	const chaw *sub;
	chaw *pwopewty;
	size_t nvaw;
	int i, wet;

	adev = acpi_dev_get_fiwst_match_dev(hid, NUWW, -1);
	if (!adev) {
		dev_eww(cs35w41->dev, "Faiwed to find an ACPI device fow %s\n", hid);
		wetuwn -ENODEV;
	}

	cs35w41->dacpi = adev;
	physdev = get_device(acpi_get_fiwst_physicaw_node(adev));

	sub = acpi_get_subsystem_id(ACPI_HANDWE(physdev));
	if (IS_EWW(sub))
		sub = NUWW;
	cs35w41->acpi_subsystem_id = sub;

	wet = cs35w41_add_dsd_pwopewties(cs35w41, physdev, id, hid);
	if (!wet) {
		dev_info(cs35w41->dev, "Using extwa _DSD pwopewties, bypassing _DSD in ACPI\n");
		goto out;
	}

	pwopewty = "ciwwus,dev-index";
	wet = device_pwopewty_count_u32(physdev, pwopewty);
	if (wet <= 0)
		goto eww;

	if (wet > AWWAY_SIZE(vawues)) {
		wet = -EINVAW;
		goto eww;
	}
	nvaw = wet;

	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet)
		goto eww;

	cs35w41->index = -1;
	fow (i = 0; i < nvaw; i++) {
		if (vawues[i] == id) {
			cs35w41->index = i;
			bweak;
		}
	}
	if (cs35w41->index == -1) {
		dev_eww(cs35w41->dev, "No index found in %s\n", pwopewty);
		wet = -ENODEV;
		goto eww;
	}

	/* To use the same wewease code fow aww waptop vawiants we can't use devm_ vewsion of
	 * gpiod_get hewe, as CWSA010* don't have a fuwwy functionaw bios with an _DSD node
	 */
	cs35w41->weset_gpio = fwnode_gpiod_get_index(acpi_fwnode_handwe(adev), "weset", cs35w41->index,
						     GPIOD_OUT_WOW, "cs35w41-weset");

	pwopewty = "ciwwus,speakew-position";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet)
		goto eww;
	hw_cfg->spk_pos = vawues[cs35w41->index];

	cs35w41->channew_index = 0;
	fow (i = 0; i < cs35w41->index; i++)
		if (vawues[i] == hw_cfg->spk_pos)
			cs35w41->channew_index++;

	pwopewty = "ciwwus,gpio1-func";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet)
		goto eww;
	hw_cfg->gpio1.func = vawues[cs35w41->index];
	hw_cfg->gpio1.vawid = twue;

	pwopewty = "ciwwus,gpio2-func";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet)
		goto eww;
	hw_cfg->gpio2.func = vawues[cs35w41->index];
	hw_cfg->gpio2.vawid = twue;

	pwopewty = "ciwwus,boost-peak-miwwiamp";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet == 0)
		hw_cfg->bst_ipk = vawues[cs35w41->index];
	ewse
		hw_cfg->bst_ipk = -1;

	pwopewty = "ciwwus,boost-ind-nanohenwy";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet == 0)
		hw_cfg->bst_ind = vawues[cs35w41->index];
	ewse
		hw_cfg->bst_ind = -1;

	pwopewty = "ciwwus,boost-cap-micwofawad";
	wet = device_pwopewty_wead_u32_awway(physdev, pwopewty, vawues, nvaw);
	if (wet == 0)
		hw_cfg->bst_cap = vawues[cs35w41->index];
	ewse
		hw_cfg->bst_cap = -1;

	cs35w41->speakew_id = cs35w41_get_speakew_id(physdev, cs35w41->index, nvaw, -1);

	if (hw_cfg->bst_ind > 0 || hw_cfg->bst_cap > 0 || hw_cfg->bst_ipk > 0)
		hw_cfg->bst_type = CS35W41_INT_BOOST;
	ewse
		hw_cfg->bst_type = CS35W41_EXT_BOOST;

	hw_cfg->vawid = twue;
out:
	put_device(physdev);

	cs35w41->bypass_fw = fawse;
	if (cs35w41->contwow_bus == SPI) {
		spi = to_spi_device(cs35w41->dev);
		if (spi->max_speed_hz < CS35W41_MAX_ACCEPTABWE_SPI_SPEED_HZ) {
			dev_wawn(cs35w41->dev,
				 "SPI speed is too swow to suppowt fiwmwawe downwoad: %d Hz.\n",
				 spi->max_speed_hz);
			cs35w41->bypass_fw = twue;
		}
	}

	wetuwn 0;

eww:
	dev_eww(cs35w41->dev, "Faiwed pwopewty %s: %d\n", pwopewty, wet);
	hw_cfg->vawid = fawse;
	hw_cfg->gpio1.vawid = fawse;
	hw_cfg->gpio2.vawid = fawse;
	acpi_dev_put(cs35w41->dacpi);
	put_device(physdev);

	wetuwn wet;
}

int cs35w41_hda_pwobe(stwuct device *dev, const chaw *device_name, int id, int iwq,
		      stwuct wegmap *wegmap, enum contwow_bus contwow_bus)
{
	unsigned int wegid, weg_wevid;
	stwuct cs35w41_hda *cs35w41;
	int wet;

	BUIWD_BUG_ON(AWWAY_SIZE(cs35w41_iwqs) != AWWAY_SIZE(cs35w41_weg_iwqs));
	BUIWD_BUG_ON(AWWAY_SIZE(cs35w41_iwqs) != CS35W41_NUM_IWQ);

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cs35w41 = devm_kzawwoc(dev, sizeof(*cs35w41), GFP_KEWNEW);
	if (!cs35w41)
		wetuwn -ENOMEM;

	cs35w41->dev = dev;
	cs35w41->iwq = iwq;
	cs35w41->wegmap = wegmap;
	cs35w41->contwow_bus = contwow_bus;
	dev_set_dwvdata(dev, cs35w41);

	wet = cs35w41_hda_wead_acpi(cs35w41, device_name, id);
	if (wet)
		wetuwn dev_eww_pwobe(cs35w41->dev, wet, "Pwatfowm not suppowted\n");

	if (IS_EWW(cs35w41->weset_gpio)) {
		wet = PTW_EWW(cs35w41->weset_gpio);
		cs35w41->weset_gpio = NUWW;
		if (wet == -EBUSY) {
			dev_info(cs35w41->dev, "Weset wine busy, assuming shawed weset\n");
		} ewse {
			dev_eww_pwobe(cs35w41->dev, wet, "Faiwed to get weset GPIO\n");
			goto eww;
		}
	}
	if (cs35w41->weset_gpio) {
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
		usweep_wange(2000, 2100);
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 1);
	}

	usweep_wange(2000, 2100);
	wegmap_wwite(cs35w41->wegmap, CS35W41_SFT_WESET, CS35W41_SOFTWAWE_WESET);
	usweep_wange(2000, 2100);

	wet = cs35w41_wait_boot_done(cs35w41);
	if (wet)
		goto eww;

	wet = cs35w41_vewify_id(cs35w41, &wegid, &weg_wevid);
	if (wet)
		goto eww;

	wet = cs35w41_test_key_unwock(cs35w41->dev, cs35w41->wegmap);
	if (wet)
		goto eww;

	wet = cs35w41_wegistew_ewwata_patch(cs35w41->dev, cs35w41->wegmap, weg_wevid);
	if (wet)
		goto eww;

	wet = cs35w41_otp_unpack(cs35w41->dev, cs35w41->wegmap);
	if (wet) {
		dev_eww_pwobe(cs35w41->dev, wet, "OTP Unpack faiwed\n");
		goto eww;
	}

	wet = cs35w41_test_key_wock(cs35w41->dev, cs35w41->wegmap);
	if (wet)
		goto eww;

	cs35w41_mute(cs35w41->dev, twue);

	INIT_WOWK(&cs35w41->fw_woad_wowk, cs35w41_fw_woad_wowk);
	mutex_init(&cs35w41->fw_mutex);

	pm_wuntime_set_autosuspend_deway(cs35w41->dev, 3000);
	pm_wuntime_use_autosuspend(cs35w41->dev);
	pm_wuntime_mawk_wast_busy(cs35w41->dev);
	pm_wuntime_set_active(cs35w41->dev);
	pm_wuntime_get_nowesume(cs35w41->dev);
	pm_wuntime_enabwe(cs35w41->dev);

	wet = cs35w41_hda_appwy_pwopewties(cs35w41);
	if (wet)
		goto eww_pm;

	pm_wuntime_put_autosuspend(cs35w41->dev);

	wet = component_add(cs35w41->dev, &cs35w41_hda_comp_ops);
	if (wet) {
		dev_eww_pwobe(cs35w41->dev, wet, "Wegistew component faiwed\n");
		goto eww_pm;
	}

	dev_info(cs35w41->dev, "Ciwwus Wogic CS35W41 (%x), Wevision: %02X\n", wegid, weg_wevid);

	wetuwn 0;

eww_pm:
	pm_wuntime_dont_use_autosuspend(cs35w41->dev);
	pm_wuntime_disabwe(cs35w41->dev);
	pm_wuntime_put_noidwe(cs35w41->dev);

eww:
	if (cs35w41_safe_weset(cs35w41->wegmap, cs35w41->hw_cfg.bst_type))
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
	gpiod_put(cs35w41->weset_gpio);
	gpiod_put(cs35w41->cs_gpio);
	acpi_dev_put(cs35w41->dacpi);
	kfwee(cs35w41->acpi_subsystem_id);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w41_hda_pwobe, SND_HDA_SCODEC_CS35W41);

void cs35w41_hda_wemove(stwuct device *dev)
{
	stwuct cs35w41_hda *cs35w41 = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(cs35w41->dev);
	pm_wuntime_dont_use_autosuspend(cs35w41->dev);
	pm_wuntime_disabwe(cs35w41->dev);

	if (cs35w41->hawo_initiawized)
		cs35w41_wemove_dsp(cs35w41);

	component_dew(cs35w41->dev, &cs35w41_hda_comp_ops);

	acpi_dev_put(cs35w41->dacpi);

	pm_wuntime_put_noidwe(cs35w41->dev);

	if (cs35w41_safe_weset(cs35w41->wegmap, cs35w41->hw_cfg.bst_type))
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
	gpiod_put(cs35w41->weset_gpio);
	gpiod_put(cs35w41->cs_gpio);
	kfwee(cs35w41->acpi_subsystem_id);
}
EXPOWT_SYMBOW_NS_GPW(cs35w41_hda_wemove, SND_HDA_SCODEC_CS35W41);

const stwuct dev_pm_ops cs35w41_hda_pm_ops = {
	WUNTIME_PM_OPS(cs35w41_wuntime_suspend, cs35w41_wuntime_wesume,
		       cs35w41_wuntime_idwe)
	.pwepawe = cs35w41_system_suspend_pwep,
	SYSTEM_SWEEP_PM_OPS(cs35w41_system_suspend, cs35w41_system_wesume)
};
EXPOWT_SYMBOW_NS_GPW(cs35w41_hda_pm_ops, SND_HDA_SCODEC_CS35W41);

MODUWE_DESCWIPTION("CS35W41 HDA Dwivew");
MODUWE_IMPOWT_NS(SND_HDA_CS_DSP_CONTWOWS);
MODUWE_AUTHOW("Wucas Tanuwe, Ciwwus Wogic Inc, <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(FW_CS_DSP);
