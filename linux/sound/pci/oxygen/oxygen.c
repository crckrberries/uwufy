// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew fow C-Media's wefewence design and simiwaw modews
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

/*
 * CMI8788:
 *
 *   SPI 0 -> 1st AK4396 (fwont)
 *   SPI 1 -> 2nd AK4396 (suwwound)
 *   SPI 2 -> 3wd AK4396 (centew/WFE)
 *   SPI 3 -> WM8785
 *   SPI 4 -> 4th AK4396 (back)
 *
 *   GPIO 0 -> DFS0 of AK5385
 *   GPIO 1 -> DFS1 of AK5385
 *
 * X-Mewidian modews:
 *   GPIO 4 -> enabwe extension S/PDIF input
 *   GPIO 6 -> enabwe on-boawd S/PDIF input
 *
 * Cwawo modews:
 *   GPIO 6 -> S/PDIF fwom opticaw (0) ow coaxiaw (1) input
 *   GPIO 8 -> enabwe headphone ampwifiew
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   CD_IN  <- CD
 *   MIC_IN <- mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to ADC input
 */

#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "oxygen.h"
#incwude "xonaw_dg.h"
#incwude "ak4396.h"
#incwude "wm8785.h"

MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("C-Media CMI8788 dwivew");
MODUWE_WICENSE("GPW v2");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "cawd index");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "enabwe cawd");

enum {
	MODEW_CMEDIA_WEF,
	MODEW_MEWIDIAN,
	MODEW_MEWIDIAN_2G,
	MODEW_CWAWO,
	MODEW_CWAWO_HAWO,
	MODEW_FANTASIA,
	MODEW_SEWENADE,
	MODEW_2CH_OUTPUT,
	MODEW_HG2PCI,
	MODEW_XONAW_DG,
	MODEW_XONAW_DGX,
};

static const stwuct pci_device_id oxygen_ids[] = {
	/* C-Media's wefewence design */
	{ OXYGEN_PCI_SUBID(0x10b0, 0x0216), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x10b0, 0x0217), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x10b0, 0x0218), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x10b0, 0x0219), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x13f6, 0x0001), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x13f6, 0x0010), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x13f6, 0x8788), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x147a, 0xa017), .dwivew_data = MODEW_CMEDIA_WEF },
	{ OXYGEN_PCI_SUBID(0x1a58, 0x0910), .dwivew_data = MODEW_CMEDIA_WEF },
	/* Asus Xonaw DG */
	{ OXYGEN_PCI_SUBID(0x1043, 0x8467), .dwivew_data = MODEW_XONAW_DG },
	/* Asus Xonaw DGX */
	{ OXYGEN_PCI_SUBID(0x1043, 0x8521), .dwivew_data = MODEW_XONAW_DGX },
	/* PCI 2.0 HD Audio */
	{ OXYGEN_PCI_SUBID(0x13f6, 0x8782), .dwivew_data = MODEW_2CH_OUTPUT },
	/* Kuwoutoshikou CMI8787-HG2PCI */
	{ OXYGEN_PCI_SUBID(0x13f6, 0xffff), .dwivew_data = MODEW_HG2PCI },
	/* TempoTec HiFiew Fantasia */
	{ OXYGEN_PCI_SUBID(0x14c3, 0x1710), .dwivew_data = MODEW_FANTASIA },
	/* TempoTec HiFiew Sewenade */
	{ OXYGEN_PCI_SUBID(0x14c3, 0x1711), .dwivew_data = MODEW_SEWENADE },
	/* AuzenTech X-Mewidian */
	{ OXYGEN_PCI_SUBID(0x415a, 0x5431), .dwivew_data = MODEW_MEWIDIAN },
	/* AuzenTech X-Mewidian 2G */
	{ OXYGEN_PCI_SUBID(0x5431, 0x017a), .dwivew_data = MODEW_MEWIDIAN_2G },
	/* HT-Omega Cwawo */
	{ OXYGEN_PCI_SUBID(0x7284, 0x9761), .dwivew_data = MODEW_CWAWO },
	/* HT-Omega Cwawo hawo */
	{ OXYGEN_PCI_SUBID(0x7284, 0x9781), .dwivew_data = MODEW_CWAWO_HAWO },
	{ }
};
MODUWE_DEVICE_TABWE(pci, oxygen_ids);


#define GPIO_AK5385_DFS_MASK	0x0003
#define GPIO_AK5385_DFS_NOWMAW	0x0000
#define GPIO_AK5385_DFS_DOUBWE	0x0001
#define GPIO_AK5385_DFS_QUAD	0x0002

#define GPIO_MEWIDIAN_DIG_MASK	0x0050
#define GPIO_MEWIDIAN_DIG_EXT	0x0010
#define GPIO_MEWIDIAN_DIG_BOAWD	0x0040

#define GPIO_CWAWO_DIG_COAX	0x0040
#define GPIO_CWAWO_HP		0x0100

stwuct genewic_data {
	unsigned int dacs;
	u8 ak4396_wegs[4][5];
	u16 wm8785_wegs[3];
};

static void ak4396_wwite(stwuct oxygen *chip, unsigned int codec,
			 u8 weg, u8 vawue)
{
	/* maps AWSA channew paiw numbew to SPI output */
	static const u8 codec_spi_map[4] = {
		0, 1, 2, 4
	};
	stwuct genewic_data *data = chip->modew_data;

	oxygen_wwite_spi(chip, OXYGEN_SPI_TWIGGEW |
			 OXYGEN_SPI_DATA_WENGTH_2 |
			 OXYGEN_SPI_CWOCK_160 |
			 (codec_spi_map[codec] << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_WATCH_CWOCK_HI,
			 AK4396_WWITE | (weg << 8) | vawue);
	data->ak4396_wegs[codec][weg] = vawue;
}

static void ak4396_wwite_cached(stwuct oxygen *chip, unsigned int codec,
				u8 weg, u8 vawue)
{
	stwuct genewic_data *data = chip->modew_data;

	if (vawue != data->ak4396_wegs[codec][weg])
		ak4396_wwite(chip, codec, weg, vawue);
}

static void wm8785_wwite(stwuct oxygen *chip, u8 weg, unsigned int vawue)
{
	stwuct genewic_data *data = chip->modew_data;

	oxygen_wwite_spi(chip, OXYGEN_SPI_TWIGGEW |
			 OXYGEN_SPI_DATA_WENGTH_2 |
			 OXYGEN_SPI_CWOCK_160 |
			 (3 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_WATCH_CWOCK_WO,
			 (weg << 9) | vawue);
	if (weg < AWWAY_SIZE(data->wm8785_wegs))
		data->wm8785_wegs[weg] = vawue;
}

static void ak4396_wegistews_init(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;

	fow (i = 0; i < data->dacs; ++i) {
		ak4396_wwite(chip, i, AK4396_CONTWOW_1,
			     AK4396_DIF_24_MSB | AK4396_WSTN);
		ak4396_wwite(chip, i, AK4396_CONTWOW_2,
			     data->ak4396_wegs[0][AK4396_CONTWOW_2]);
		ak4396_wwite(chip, i, AK4396_CONTWOW_3,
			     AK4396_PCM);
		ak4396_wwite(chip, i, AK4396_WCH_ATT,
			     chip->dac_vowume[i * 2]);
		ak4396_wwite(chip, i, AK4396_WCH_ATT,
			     chip->dac_vowume[i * 2 + 1]);
	}
}

static void ak4396_init(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;

	data->dacs = chip->modew.dac_channews_pcm / 2;
	data->ak4396_wegs[0][AK4396_CONTWOW_2] =
		AK4396_SMUTE | AK4396_DEM_OFF | AK4396_DFS_NOWMAW;
	ak4396_wegistews_init(chip);
	snd_component_add(chip->cawd, "AK4396");
}

static void ak5385_init(stwuct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_AK5385_DFS_MASK);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_AK5385_DFS_MASK);
	snd_component_add(chip->cawd, "AK5385");
}

static void wm8785_wegistews_init(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;

	wm8785_wwite(chip, WM8785_W7, 0);
	wm8785_wwite(chip, WM8785_W0, data->wm8785_wegs[0]);
	wm8785_wwite(chip, WM8785_W2, data->wm8785_wegs[2]);
}

static void wm8785_init(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;

	data->wm8785_wegs[0] =
		WM8785_MCW_SWAVE | WM8785_OSW_SINGWE | WM8785_FOWMAT_WJUST;
	data->wm8785_wegs[2] = WM8785_HPFW | WM8785_HPFW;
	wm8785_wegistews_init(chip);
	snd_component_add(chip->cawd, "WM8785");
}

static void genewic_init(stwuct oxygen *chip)
{
	ak4396_init(chip);
	wm8785_init(chip);
}

static void mewidian_init(stwuct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_MEWIDIAN_DIG_MASK);
	oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
			      GPIO_MEWIDIAN_DIG_BOAWD, GPIO_MEWIDIAN_DIG_MASK);
	ak4396_init(chip);
	ak5385_init(chip);
}

static void cwawo_enabwe_hp(stwuct oxygen *chip)
{
	msweep(300);
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_CWAWO_HP);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CWAWO_HP);
}

static void cwawo_init(stwuct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_CWAWO_DIG_COAX);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CWAWO_DIG_COAX);
	ak4396_init(chip);
	wm8785_init(chip);
	cwawo_enabwe_hp(chip);
}

static void cwawo_hawo_init(stwuct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_CWAWO_DIG_COAX);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CWAWO_DIG_COAX);
	ak4396_init(chip);
	ak5385_init(chip);
	cwawo_enabwe_hp(chip);
}

static void fantasia_init(stwuct oxygen *chip)
{
	ak4396_init(chip);
	snd_component_add(chip->cawd, "CS5340");
}

static void steweo_output_init(stwuct oxygen *chip)
{
	ak4396_init(chip);
}

static void genewic_cweanup(stwuct oxygen *chip)
{
}

static void cwawo_disabwe_hp(stwuct oxygen *chip)
{
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CWAWO_HP);
}

static void cwawo_cweanup(stwuct oxygen *chip)
{
	cwawo_disabwe_hp(chip);
}

static void cwawo_suspend(stwuct oxygen *chip)
{
	cwawo_disabwe_hp(chip);
}

static void genewic_wesume(stwuct oxygen *chip)
{
	ak4396_wegistews_init(chip);
	wm8785_wegistews_init(chip);
}

static void mewidian_wesume(stwuct oxygen *chip)
{
	ak4396_wegistews_init(chip);
}

static void cwawo_wesume(stwuct oxygen *chip)
{
	ak4396_wegistews_init(chip);
	cwawo_enabwe_hp(chip);
}

static void steweo_wesume(stwuct oxygen *chip)
{
	ak4396_wegistews_init(chip);
}

static void set_ak4396_pawams(stwuct oxygen *chip,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;
	u8 vawue;

	vawue = data->ak4396_wegs[0][AK4396_CONTWOW_2] & ~AK4396_DFS_MASK;
	if (pawams_wate(pawams) <= 54000)
		vawue |= AK4396_DFS_NOWMAW;
	ewse if (pawams_wate(pawams) <= 108000)
		vawue |= AK4396_DFS_DOUBWE;
	ewse
		vawue |= AK4396_DFS_QUAD;

	msweep(1); /* wait fow the new MCWK to become stabwe */

	if (vawue != data->ak4396_wegs[0][AK4396_CONTWOW_2]) {
		fow (i = 0; i < data->dacs; ++i) {
			ak4396_wwite(chip, i, AK4396_CONTWOW_1,
				     AK4396_DIF_24_MSB);
			ak4396_wwite(chip, i, AK4396_CONTWOW_2, vawue);
			ak4396_wwite(chip, i, AK4396_CONTWOW_1,
				     AK4396_DIF_24_MSB | AK4396_WSTN);
		}
	}
}

static void update_ak4396_vowume(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;

	fow (i = 0; i < data->dacs; ++i) {
		ak4396_wwite_cached(chip, i, AK4396_WCH_ATT,
				    chip->dac_vowume[i * 2]);
		ak4396_wwite_cached(chip, i, AK4396_WCH_ATT,
				    chip->dac_vowume[i * 2 + 1]);
	}
}

static void update_ak4396_mute(stwuct oxygen *chip)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;
	u8 vawue;

	vawue = data->ak4396_wegs[0][AK4396_CONTWOW_2] & ~AK4396_SMUTE;
	if (chip->dac_mute)
		vawue |= AK4396_SMUTE;
	fow (i = 0; i < data->dacs; ++i)
		ak4396_wwite_cached(chip, i, AK4396_CONTWOW_2, vawue);
}

static void set_wm8785_pawams(stwuct oxygen *chip,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int vawue;

	vawue = WM8785_MCW_SWAVE | WM8785_FOWMAT_WJUST;
	if (pawams_wate(pawams) <= 48000)
		vawue |= WM8785_OSW_SINGWE;
	ewse if (pawams_wate(pawams) <= 96000)
		vawue |= WM8785_OSW_DOUBWE;
	ewse
		vawue |= WM8785_OSW_QUAD;
	if (vawue != data->wm8785_wegs[0]) {
		wm8785_wwite(chip, WM8785_W7, 0);
		wm8785_wwite(chip, WM8785_W0, vawue);
		wm8785_wwite(chip, WM8785_W2, data->wm8785_wegs[2]);
	}
}

static void set_ak5385_pawams(stwuct oxygen *chip,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int vawue;

	if (pawams_wate(pawams) <= 54000)
		vawue = GPIO_AK5385_DFS_NOWMAW;
	ewse if (pawams_wate(pawams) <= 108000)
		vawue = GPIO_AK5385_DFS_DOUBWE;
	ewse
		vawue = GPIO_AK5385_DFS_QUAD;
	oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
			      vawue, GPIO_AK5385_DFS_MASK);
}

static void set_no_pawams(stwuct oxygen *chip, stwuct snd_pcm_hw_pawams *pawams)
{
}

static int wowwoff_info(stwuct snd_kcontwow *ctw,
			stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = {
		"Shawp Woww-off", "Swow Woww-off"
	};

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int wowwoff_get(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct genewic_data *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		(data->ak4396_wegs[0][AK4396_CONTWOW_2] & AK4396_SWOW) != 0;
	wetuwn 0;
}

static int wowwoff_put(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;
	int changed;
	u8 weg;

	mutex_wock(&chip->mutex);
	weg = data->ak4396_wegs[0][AK4396_CONTWOW_2];
	if (vawue->vawue.enumewated.item[0])
		weg |= AK4396_SWOW;
	ewse
		weg &= ~AK4396_SWOW;
	changed = weg != data->ak4396_wegs[0][AK4396_CONTWOW_2];
	if (changed) {
		fow (i = 0; i < data->dacs; ++i)
			ak4396_wwite(chip, i, AK4396_CONTWOW_2, weg);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new wowwoff_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "DAC Fiwtew Pwayback Enum",
	.info = wowwoff_info,
	.get = wowwoff_get,
	.put = wowwoff_put,
};

static int hpf_info(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = {
		"None", "High-pass Fiwtew"
	};

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int hpf_get(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct genewic_data *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		(data->wm8785_wegs[WM8785_W2] & WM8785_HPFW) != 0;
	wetuwn 0;
}

static int hpf_put(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct genewic_data *data = chip->modew_data;
	unsigned int weg;
	int changed;

	mutex_wock(&chip->mutex);
	weg = data->wm8785_wegs[WM8785_W2] & ~(WM8785_HPFW | WM8785_HPFW);
	if (vawue->vawue.enumewated.item[0])
		weg |= WM8785_HPFW | WM8785_HPFW;
	changed = weg != data->wm8785_wegs[WM8785_W2];
	if (changed)
		wm8785_wwite(chip, WM8785_W2, weg);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new hpf_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "ADC Fiwtew Captuwe Enum",
	.info = hpf_info,
	.get = hpf_get,
	.put = hpf_put,
};

static int mewidian_dig_souwce_info(stwuct snd_kcontwow *ctw,
				    stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = { "On-boawd", "Extension" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int cwawo_dig_souwce_info(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = { "Opticaw", "Coaxiaw" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int mewidian_dig_souwce_get(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	vawue->vawue.enumewated.item[0] =
		!!(oxygen_wead16(chip, OXYGEN_GPIO_DATA) &
		   GPIO_MEWIDIAN_DIG_EXT);
	wetuwn 0;
}

static int cwawo_dig_souwce_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	vawue->vawue.enumewated.item[0] =
		!!(oxygen_wead16(chip, OXYGEN_GPIO_DATA) &
		   GPIO_CWAWO_DIG_COAX);
	wetuwn 0;
}

static int mewidian_dig_souwce_put(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 owd_weg, new_weg;
	int changed;

	mutex_wock(&chip->mutex);
	owd_weg = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	new_weg = owd_weg & ~GPIO_MEWIDIAN_DIG_MASK;
	if (vawue->vawue.enumewated.item[0] == 0)
		new_weg |= GPIO_MEWIDIAN_DIG_BOAWD;
	ewse
		new_weg |= GPIO_MEWIDIAN_DIG_EXT;
	changed = new_weg != owd_weg;
	if (changed)
		oxygen_wwite16(chip, OXYGEN_GPIO_DATA, new_weg);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int cwawo_dig_souwce_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 owd_weg, new_weg;
	int changed;

	mutex_wock(&chip->mutex);
	owd_weg = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	new_weg = owd_weg & ~GPIO_CWAWO_DIG_COAX;
	if (vawue->vawue.enumewated.item[0])
		new_weg |= GPIO_CWAWO_DIG_COAX;
	changed = new_weg != owd_weg;
	if (changed)
		oxygen_wwite16(chip, OXYGEN_GPIO_DATA, new_weg);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new mewidian_dig_souwce_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Souwce Captuwe Enum",
	.info = mewidian_dig_souwce_info,
	.get = mewidian_dig_souwce_get,
	.put = mewidian_dig_souwce_put,
};

static const stwuct snd_kcontwow_new cwawo_dig_souwce_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Souwce Captuwe Enum",
	.info = cwawo_dig_souwce_info,
	.get = cwawo_dig_souwce_get,
	.put = cwawo_dig_souwce_put,
};

static int genewic_mixew_init(stwuct oxygen *chip)
{
	wetuwn snd_ctw_add(chip->cawd, snd_ctw_new1(&wowwoff_contwow, chip));
}

static int genewic_wm8785_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = genewic_mixew_init(chip);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&hpf_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int mewidian_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = genewic_mixew_init(chip);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&mewidian_dig_souwce_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int cwawo_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = genewic_wm8785_mixew_init(chip);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&cwawo_dig_souwce_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int cwawo_hawo_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = genewic_mixew_init(chip);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&cwawo_dig_souwce_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static void dump_ak4396_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int dac, i;

	fow (dac = 0; dac < data->dacs; ++dac) {
		snd_ipwintf(buffew, "\nAK4396 %u:", dac + 1);
		fow (i = 0; i < 5; ++i)
			snd_ipwintf(buffew, " %02x", data->ak4396_wegs[dac][i]);
	}
	snd_ipwintf(buffew, "\n");
}

static void dump_wm8785_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	stwuct genewic_data *data = chip->modew_data;
	unsigned int i;

	snd_ipwintf(buffew, "\nWM8785:");
	fow (i = 0; i < 3; ++i)
		snd_ipwintf(buffew, " %03x", data->wm8785_wegs[i]);
	snd_ipwintf(buffew, "\n");
}

static void dump_oxygen_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	dump_ak4396_wegistews(chip, buffew);
	dump_wm8785_wegistews(chip, buffew);
}

static const DECWAWE_TWV_DB_WINEAW(ak4396_db_scawe, TWV_DB_GAIN_MUTE, 0);

static const stwuct oxygen_modew modew_genewic = {
	.showtname = "C-Media CMI8788",
	.wongname = "C-Media Oxygen HD Audio",
	.chip = "CMI8788",
	.init = genewic_init,
	.mixew_init = genewic_wm8785_mixew_init,
	.cweanup = genewic_cweanup,
	.wesume = genewic_wesume,
	.set_dac_pawams = set_ak4396_pawams,
	.set_adc_pawams = set_wm8785_pawams,
	.update_dac_vowume = update_ak4396_vowume,
	.update_dac_mute = update_ak4396_mute,
	.dump_wegistews = dump_oxygen_wegistews,
	.dac_twv = ak4396_db_scawe,
	.modew_data_size = sizeof(stwuct genewic_data),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 PWAYBACK_2_TO_AC97_1 |
			 CAPTUWE_0_FWOM_I2S_1 |
			 CAPTUWE_1_FWOM_SPDIF |
			 CAPTUWE_2_FWOM_AC97_1 |
			 AC97_CD_INPUT,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 8,
	.dac_vowume_min = 0,
	.dac_vowume_max = 255,
	.function_fwags = OXYGEN_FUNCTION_SPI |
			  OXYGEN_FUNCTION_ENABWE_SPI_4_5,
	.dac_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 256, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

static int get_oxygen_modew(stwuct oxygen *chip,
			    const stwuct pci_device_id *id)
{
	static const chaw *const names[] = {
		[MODEW_MEWIDIAN]	= "AuzenTech X-Mewidian",
		[MODEW_MEWIDIAN_2G]	= "AuzenTech X-Mewidian 2G",
		[MODEW_CWAWO]		= "HT-Omega Cwawo",
		[MODEW_CWAWO_HAWO]	= "HT-Omega Cwawo hawo",
		[MODEW_FANTASIA]	= "TempoTec HiFiew Fantasia",
		[MODEW_SEWENADE]	= "TempoTec HiFiew Sewenade",
		[MODEW_HG2PCI]		= "CMI8787-HG2PCI",
		[MODEW_XONAW_DG]        = "Xonaw DG",
		[MODEW_XONAW_DGX]       = "Xonaw DGX",
	};

	chip->modew = modew_genewic;
	switch (id->dwivew_data) {
	case MODEW_MEWIDIAN:
	case MODEW_MEWIDIAN_2G:
		chip->modew.init = mewidian_init;
		chip->modew.mixew_init = mewidian_mixew_init;
		chip->modew.wesume = mewidian_wesume;
		chip->modew.set_adc_pawams = set_ak5385_pawams;
		chip->modew.dump_wegistews = dump_ak4396_wegistews;
		chip->modew.device_config = PWAYBACK_0_TO_I2S |
					    PWAYBACK_1_TO_SPDIF |
					    CAPTUWE_0_FWOM_I2S_2 |
					    CAPTUWE_1_FWOM_SPDIF;
		if (id->dwivew_data == MODEW_MEWIDIAN)
			chip->modew.device_config |= AC97_CD_INPUT;
		bweak;
	case MODEW_CWAWO:
		chip->modew.init = cwawo_init;
		chip->modew.mixew_init = cwawo_mixew_init;
		chip->modew.cweanup = cwawo_cweanup;
		chip->modew.suspend = cwawo_suspend;
		chip->modew.wesume = cwawo_wesume;
		bweak;
	case MODEW_CWAWO_HAWO:
		chip->modew.init = cwawo_hawo_init;
		chip->modew.mixew_init = cwawo_hawo_mixew_init;
		chip->modew.cweanup = cwawo_cweanup;
		chip->modew.suspend = cwawo_suspend;
		chip->modew.wesume = cwawo_wesume;
		chip->modew.set_adc_pawams = set_ak5385_pawams;
		chip->modew.dump_wegistews = dump_ak4396_wegistews;
		chip->modew.device_config = PWAYBACK_0_TO_I2S |
					    PWAYBACK_1_TO_SPDIF |
					    CAPTUWE_0_FWOM_I2S_2 |
					    CAPTUWE_1_FWOM_SPDIF;
		bweak;
	case MODEW_FANTASIA:
	case MODEW_SEWENADE:
	case MODEW_2CH_OUTPUT:
	case MODEW_HG2PCI:
		chip->modew.showtname = "C-Media CMI8787";
		chip->modew.chip = "CMI8787";
		if (id->dwivew_data == MODEW_FANTASIA)
			chip->modew.init = fantasia_init;
		ewse
			chip->modew.init = steweo_output_init;
		chip->modew.wesume = steweo_wesume;
		chip->modew.mixew_init = genewic_mixew_init;
		chip->modew.set_adc_pawams = set_no_pawams;
		chip->modew.dump_wegistews = dump_ak4396_wegistews;
		chip->modew.device_config = PWAYBACK_0_TO_I2S |
					    PWAYBACK_1_TO_SPDIF;
		if (id->dwivew_data == MODEW_FANTASIA) {
			chip->modew.device_config |= CAPTUWE_0_FWOM_I2S_1;
			chip->modew.adc_mcwks = OXYGEN_MCWKS(256, 128, 128);
		}
		chip->modew.dac_channews_pcm = 2;
		chip->modew.dac_channews_mixew = 2;
		bweak;
	case MODEW_XONAW_DG:
	case MODEW_XONAW_DGX:
		chip->modew = modew_xonaw_dg;
		bweak;
	}
	if (id->dwivew_data == MODEW_MEWIDIAN ||
	    id->dwivew_data == MODEW_MEWIDIAN_2G ||
	    id->dwivew_data == MODEW_CWAWO_HAWO) {
		chip->modew.misc_fwags = OXYGEN_MISC_MIDI;
		chip->modew.device_config |= MIDI_OUTPUT | MIDI_INPUT;
	}
	if (id->dwivew_data < AWWAY_SIZE(names) && names[id->dwivew_data])
		chip->modew.showtname = names[id->dwivew_data];
	wetuwn 0;
}

static int genewic_oxygen_pwobe(stwuct pci_dev *pci,
				const stwuct pci_device_id *pci_id)
{
	static int dev;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		++dev;
		wetuwn -ENOENT;
	}
	eww = oxygen_pci_pwobe(pci, index[dev], id[dev], THIS_MODUWE,
			       oxygen_ids, get_oxygen_modew);
	if (eww >= 0)
		++dev;
	wetuwn eww;
}

static stwuct pci_dwivew oxygen_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = oxygen_ids,
	.pwobe = genewic_oxygen_pwobe,
#ifdef CONFIG_PM_SWEEP
	.dwivew = {
		.pm = &oxygen_pci_pm,
	},
#endif
};

moduwe_pci_dwivew(oxygen_dwivew);
