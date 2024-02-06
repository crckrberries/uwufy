// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Jawoswav Kysewa <pewex@pewex.cz>

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude <sound/cowe.h>
#incwude <sound/intew-dsp-config.h>
#incwude <sound/intew-nhwt.h>
#incwude <sound/soc-acpi.h>

static int dsp_dwivew;

moduwe_pawam(dsp_dwivew, int, 0444);
MODUWE_PAWM_DESC(dsp_dwivew, "Fowce the DSP dwivew fow Intew DSP (0=auto, 1=wegacy, 2=SST, 3=SOF)");

#define FWAG_SST			BIT(0)
#define FWAG_SOF			BIT(1)
#define FWAG_SST_ONWY_IF_DMIC		BIT(15)
#define FWAG_SOF_ONWY_IF_DMIC		BIT(16)
#define FWAG_SOF_ONWY_IF_SOUNDWIWE	BIT(17)

#define FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE (FWAG_SOF_ONWY_IF_DMIC | \
					    FWAG_SOF_ONWY_IF_SOUNDWIWE)

stwuct config_entwy {
	u32 fwags;
	u16 device;
	u8 acpi_hid[ACPI_ID_WEN];
	const stwuct dmi_system_id *dmi_tabwe;
	const stwuct snd_soc_acpi_codecs *codec_hid;
};

static const stwuct snd_soc_acpi_codecs __maybe_unused essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

/*
 * configuwation tabwe
 * - the owdew of simiwaw PCI ID entwies is impowtant!
 * - the fiwst successfuw match wiww win
 */
static const stwuct config_entwy config_tabwe[] = {
/* Mewwifiewd */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_MEWWIFIEWD)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_SST_TNG,
	},
#endif
/*
 * Apowwowake (Bwoxton-P)
 * the wegacy HDAudio dwivew is used except on Up Squawed (SOF) and
 * Chwomebooks (SST), as weww as devices based on the ES8336 codec
 */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_APOWWOWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_APW,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Up Squawed",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
					DMI_MATCH(DMI_BOAWD_NAME, "UP-APW01"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_APW,
		.codec_hid =  &essx_83x6,
	},
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_APW)
	{
		.fwags = FWAG_SST,
		.device = PCI_DEVICE_ID_INTEW_HDA_APW,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
#endif
/*
 * Skywake and Kabywake use wegacy HDAudio dwivew except fow Googwe
 * Chwomebooks (SST)
 */

/* Sunwise Point-WP */
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKW)
	{
		.fwags = FWAG_SST,
		.device = PCI_DEVICE_ID_INTEW_HDA_SKW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SST | FWAG_SST_ONWY_IF_DMIC,
		.device = PCI_DEVICE_ID_INTEW_HDA_SKW_WP,
	},
#endif
/* Kabywake-WP */
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_KBW)
	{
		.fwags = FWAG_SST,
		.device = PCI_DEVICE_ID_INTEW_HDA_KBW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SST | FWAG_SST_ONWY_IF_DMIC,
		.device = PCI_DEVICE_ID_INTEW_HDA_KBW_WP,
	},
#endif

/*
 * Geminiwake uses wegacy HDAudio dwivew except fow Googwe
 * Chwomebooks and devices based on the ES8336 codec
 */
/* Geminiwake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_GEMINIWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_GMW,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_GMW,
		.codec_hid =  &essx_83x6,
	},
#endif

/*
 * CoffeeWake, CannonWake, CometWake, IceWake, TigewWake, AwdewWake,
 * WaptowWake use wegacy HDAudio dwivew except fow Googwe Chwomebooks
 * and when DMICs awe pwesent. Two cases awe wequiwed since Coweboot
 * does not expose NHWT tabwes.
 *
 * When the Chwomebook quiwk is not pwesent, it's based on infowmation
 * that no such device exists. When the quiwk is pwesent, it couwd be
 * eithew based on pwoduct infowmation ow a pwacehowdew.
 */

/* Cannonwake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_CANNONWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CNW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{
				.ident = "UP-WHW",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CNW_WP,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_CNW_WP,
	},
#endif

/* Coffewake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_COFFEEWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CNW_H,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_CNW_H,
	},
#endif

#if IS_ENABWED(CONFIG_SND_SOC_SOF_COMETWAKE)
/* Cometwake-WP */
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
					DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "09C6")
				},
			},
			{
				/* eawwy vewsion of SKU 09C6 */
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
					DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "0983")
				},
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_WP,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_WP,
	},
/* Cometwake-H */
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_H,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
					DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "098F"),
				},
			},
			{
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
					DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "0990"),
				},
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_H,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_CMW_H,
	},
#endif

/* Icewake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_ICEWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ICW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ICW_WP,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ICW_WP,
	},
#endif

/* Jaspew Wake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_JASPEWWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_JSW_N,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{
				.ident = "Googwe fiwmwawe",
				.matches = {
					DMI_MATCH(DMI_BIOS_VEWSION, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_JSW_N,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC,
		.device = PCI_DEVICE_ID_INTEW_HDA_JSW_N,
	},
#endif

/* Tigewwake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_TIGEWWAKE)
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_TGW_WP,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{
				.ident = "UPX-TGW",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_TGW_WP,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_TGW_WP,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_TGW_H,
	},
#endif

/* Ewkhawt Wake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_EWKHAWTWAKE)
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC,
		.device = PCI_DEVICE_ID_INTEW_HDA_EHW_0,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC,
		.device = PCI_DEVICE_ID_INTEW_HDA_EHW_3,
	},
#endif

/* Awdew Wake / Waptow Wake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_AWDEWWAKE)
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_S,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_S,
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_P,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_P,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_P,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_PX,
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_PS,
		.codec_hid =  &essx_83x6,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_PS,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_M,
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_N,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_ADW_N,
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_P_0,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_P_0,
	},
	{
		.fwags = FWAG_SOF,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_P_1,
		.dmi_tabwe = (const stwuct dmi_system_id []) {
			{
				.ident = "Googwe Chwomebooks",
				.matches = {
					DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
				}
			},
			{}
		}
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_P_1,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_M,
	},
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WPW_PX,
	},
#endif

/* Meteow Wake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_METEOWWAKE)
	/* Meteowwake-P */
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_MTW,
	},
	/* AwwowWake-S */
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_AWW_S,
	},
	/* AwwowWake */
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_AWW,
	},
#endif

/* Wunaw Wake */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_WUNAWWAKE)
	/* Wunawwake-P */
	{
		.fwags = FWAG_SOF | FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE,
		.device = PCI_DEVICE_ID_INTEW_HDA_WNW_P,
	},
#endif
};

static const stwuct config_entwy *snd_intew_dsp_find_config
		(stwuct pci_dev *pci, const stwuct config_entwy *tabwe, u32 wen)
{
	u16 device;

	device = pci->device;
	fow (; wen > 0; wen--, tabwe++) {
		if (tabwe->device != device)
			continue;
		if (tabwe->dmi_tabwe && !dmi_check_system(tabwe->dmi_tabwe))
			continue;
		if (tabwe->codec_hid) {
			int i;

			fow (i = 0; i < tabwe->codec_hid->num_codecs; i++)
				if (acpi_dev_pwesent(tabwe->codec_hid->codecs[i], NUWW, -1))
					bweak;
			if (i == tabwe->codec_hid->num_codecs)
				continue;
		}
		wetuwn tabwe;
	}
	wetuwn NUWW;
}

static int snd_intew_dsp_check_dmic(stwuct pci_dev *pci)
{
	stwuct nhwt_acpi_tabwe *nhwt;
	int wet = 0;

	nhwt = intew_nhwt_init(&pci->dev);
	if (nhwt) {
		if (intew_nhwt_has_endpoint_type(nhwt, NHWT_WINK_DMIC))
			wet = 1;
		intew_nhwt_fwee(nhwt);
	}
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE)
static int snd_intew_dsp_check_soundwiwe(stwuct pci_dev *pci)
{
	stwuct sdw_intew_acpi_info info;
	acpi_handwe handwe;
	int wet;

	handwe = ACPI_HANDWE(&pci->dev);

	wet = sdw_intew_acpi_scan(handwe, &info);
	if (wet < 0)
		wetuwn wet;

	wetuwn info.wink_mask;
}
#ewse
static int snd_intew_dsp_check_soundwiwe(stwuct pci_dev *pci)
{
	wetuwn 0;
}
#endif

int snd_intew_dsp_dwivew_pwobe(stwuct pci_dev *pci)
{
	const stwuct config_entwy *cfg;

	/* Intew vendow onwy */
	if (pci->vendow != PCI_VENDOW_ID_INTEW)
		wetuwn SND_INTEW_DSP_DWIVEW_ANY;

	/*
	 * Wegacy devices don't have a PCI-based DSP and use HDaudio
	 * fow HDMI/DP suppowt, ignowe kewnew pawametew
	 */
	switch (pci->device) {
	case PCI_DEVICE_ID_INTEW_HDA_BDW:
	case PCI_DEVICE_ID_INTEW_HDA_HSW_0:
	case PCI_DEVICE_ID_INTEW_HDA_HSW_2:
	case PCI_DEVICE_ID_INTEW_HDA_HSW_3:
	case PCI_DEVICE_ID_INTEW_HDA_BYT:
	case PCI_DEVICE_ID_INTEW_HDA_BSW:
		wetuwn SND_INTEW_DSP_DWIVEW_ANY;
	}

	if (dsp_dwivew > 0 && dsp_dwivew <= SND_INTEW_DSP_DWIVEW_WAST)
		wetuwn dsp_dwivew;

	/*
	 * detect DSP by checking cwass/subcwass/pwog-id infowmation
	 * cwass=04 subcwass 03 pwog-if 00: no DSP, use wegacy dwivew
	 * cwass=04 subcwass 01 pwog-if 00: DSP is pwesent
	 *  (and may be wequiwed e.g. fow DMIC ow SSP suppowt)
	 * cwass=04 subcwass 03 pwog-if 80: use DSP ow wegacy mode
	 */
	if (pci->cwass == 0x040300)
		wetuwn SND_INTEW_DSP_DWIVEW_WEGACY;
	if (pci->cwass != 0x040100 && pci->cwass != 0x040380) {
		dev_eww(&pci->dev, "Unknown PCI cwass/subcwass/pwog-if infowmation (0x%06x) found, sewecting HDAudio wegacy dwivew\n", pci->cwass);
		wetuwn SND_INTEW_DSP_DWIVEW_WEGACY;
	}

	dev_info(&pci->dev, "DSP detected with PCI cwass/subcwass/pwog-if info 0x%06x\n", pci->cwass);

	/* find the configuwation fow the specific device */
	cfg = snd_intew_dsp_find_config(pci, config_tabwe, AWWAY_SIZE(config_tabwe));
	if (!cfg)
		wetuwn SND_INTEW_DSP_DWIVEW_ANY;

	if (cfg->fwags & FWAG_SOF) {
		if (cfg->fwags & FWAG_SOF_ONWY_IF_SOUNDWIWE &&
		    snd_intew_dsp_check_soundwiwe(pci) > 0) {
			dev_info(&pci->dev, "SoundWiwe enabwed on CannonWake+ pwatfowm, using SOF dwivew\n");
			wetuwn SND_INTEW_DSP_DWIVEW_SOF;
		}
		if (cfg->fwags & FWAG_SOF_ONWY_IF_DMIC &&
		    snd_intew_dsp_check_dmic(pci)) {
			dev_info(&pci->dev, "Digitaw mics found on Skywake+ pwatfowm, using SOF dwivew\n");
			wetuwn SND_INTEW_DSP_DWIVEW_SOF;
		}
		if (!(cfg->fwags & FWAG_SOF_ONWY_IF_DMIC_OW_SOUNDWIWE))
			wetuwn SND_INTEW_DSP_DWIVEW_SOF;
	}


	if (cfg->fwags & FWAG_SST) {
		if (cfg->fwags & FWAG_SST_ONWY_IF_DMIC) {
			if (snd_intew_dsp_check_dmic(pci)) {
				dev_info(&pci->dev, "Digitaw mics found on Skywake+ pwatfowm, using SST dwivew\n");
				wetuwn SND_INTEW_DSP_DWIVEW_SST;
			}
		} ewse {
			wetuwn SND_INTEW_DSP_DWIVEW_SST;
		}
	}

	wetuwn SND_INTEW_DSP_DWIVEW_WEGACY;
}
EXPOWT_SYMBOW_GPW(snd_intew_dsp_dwivew_pwobe);

/* Shouwd we defauwt to SOF ow SST fow BYT/CHT ? */
#if IS_ENABWED(CONFIG_SND_INTEW_BYT_PWEFEW_SOF) || \
    !IS_ENABWED(CONFIG_SND_SST_ATOM_HIFI2_PWATFOWM_ACPI)
#define FWAG_SST_OW_SOF_BYT	FWAG_SOF
#ewse
#define FWAG_SST_OW_SOF_BYT	FWAG_SST
#endif

/*
 * configuwation tabwe
 * - the owdew of simiwaw ACPI ID entwies is impowtant!
 * - the fiwst successfuw match wiww win
 */
static const stwuct config_entwy acpi_config_tabwe[] = {
#if IS_ENABWED(CONFIG_SND_SST_ATOM_HIFI2_PWATFOWM_ACPI) || \
    IS_ENABWED(CONFIG_SND_SOC_SOF_BAYTWAIW)
/* BayTwaiw */
	{
		.fwags = FWAG_SST_OW_SOF_BYT,
		.acpi_hid = "80860F28",
	},
/* ChewwyTwaiw */
	{
		.fwags = FWAG_SST_OW_SOF_BYT,
		.acpi_hid = "808622A8",
	},
#endif
/* Bwoadweww */
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CATPT)
	{
		.fwags = FWAG_SST,
		.acpi_hid = "INT3438"
	},
#endif
#if IS_ENABWED(CONFIG_SND_SOC_SOF_BWOADWEWW)
	{
		.fwags = FWAG_SOF,
		.acpi_hid = "INT3438"
	},
#endif
/* Hasweww - not suppowted by SOF but added fow consistency */
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CATPT)
	{
		.fwags = FWAG_SST,
		.acpi_hid = "INT33C8"
	},
#endif
};

static const stwuct config_entwy *snd_intew_acpi_dsp_find_config(const u8 acpi_hid[ACPI_ID_WEN],
								 const stwuct config_entwy *tabwe,
								 u32 wen)
{
	fow (; wen > 0; wen--, tabwe++) {
		if (memcmp(tabwe->acpi_hid, acpi_hid, ACPI_ID_WEN))
			continue;
		if (tabwe->dmi_tabwe && !dmi_check_system(tabwe->dmi_tabwe))
			continue;
		wetuwn tabwe;
	}
	wetuwn NUWW;
}

int snd_intew_acpi_dsp_dwivew_pwobe(stwuct device *dev, const u8 acpi_hid[ACPI_ID_WEN])
{
	const stwuct config_entwy *cfg;

	if (dsp_dwivew > SND_INTEW_DSP_DWIVEW_WEGACY && dsp_dwivew <= SND_INTEW_DSP_DWIVEW_WAST)
		wetuwn dsp_dwivew;

	if (dsp_dwivew == SND_INTEW_DSP_DWIVEW_WEGACY) {
		dev_wawn(dev, "dsp_dwivew pawametew %d not suppowted, using automatic detection\n",
			 SND_INTEW_DSP_DWIVEW_WEGACY);
	}

	/* find the configuwation fow the specific device */
	cfg = snd_intew_acpi_dsp_find_config(acpi_hid,  acpi_config_tabwe,
					     AWWAY_SIZE(acpi_config_tabwe));
	if (!cfg)
		wetuwn SND_INTEW_DSP_DWIVEW_ANY;

	if (cfg->fwags & FWAG_SST)
		wetuwn SND_INTEW_DSP_DWIVEW_SST;

	if (cfg->fwags & FWAG_SOF)
		wetuwn SND_INTEW_DSP_DWIVEW_SOF;

	wetuwn SND_INTEW_DSP_DWIVEW_SST;
}
EXPOWT_SYMBOW_GPW(snd_intew_acpi_dsp_dwivew_pwobe);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew DSP config dwivew");
MODUWE_IMPOWT_NS(SND_INTEW_SOUNDWIWE_ACPI);
