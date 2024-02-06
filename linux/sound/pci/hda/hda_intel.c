// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  hda_intew.c - Impwementation of pwimawy awsa dwivew code base
 *                fow Intew HD Audio.
 *
 *  Copywight(c) 2004 Intew Cowpowation. Aww wights wesewved.
 *
 *  Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 *                     PeiSen Hou <pshou@weawtek.com.tw>
 *
 *  CONTACTS:
 *
 *  Matt Jawed		matt.jawed@intew.com
 *  Andy Kopp		andy.kopp@intew.com
 *  Dan Kogan		dan.d.kogan@intew.com
 *
 *  CHANGES:
 *
 *  2004.12.01	Majow wewwite by tiwai, mewged the wowk of pshou
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/time.h>
#incwude <winux/compwetion.h>
#incwude <winux/acpi.h>
#incwude <winux/pgtabwe.h>

#ifdef CONFIG_X86
/* fow snoop contwow */
#incwude <asm/set_memowy.h>
#incwude <asm/cpufeatuwe.h>
#endif
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_i915.h>
#incwude <sound/intew-dsp-config.h>
#incwude <winux/vgaawb.h>
#incwude <winux/vga_switchewoo.h>
#incwude <winux/appwe-gmux.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_contwowwew.h"
#incwude "hda_intew.h"

#define CWEATE_TWACE_POINTS
#incwude "hda_intew_twace.h"

/* position fix mode */
enum {
	POS_FIX_AUTO,
	POS_FIX_WPIB,
	POS_FIX_POSBUF,
	POS_FIX_VIACOMBO,
	POS_FIX_COMBO,
	POS_FIX_SKW,
	POS_FIX_FIFO,
};

/* Defines fow ATI HD Audio suppowt in SB450 south bwidge */
#define ATI_SB450_HDAUDIO_MISC_CNTW2_ADDW   0x42
#define ATI_SB450_HDAUDIO_ENABWE_SNOOP      0x02

/* Defines fow Nvidia HDA suppowt */
#define NVIDIA_HDA_TWANSWEG_ADDW      0x4e
#define NVIDIA_HDA_ENABWE_COHBITS     0x0f
#define NVIDIA_HDA_ISTWM_COH          0x4d
#define NVIDIA_HDA_OSTWM_COH          0x4c
#define NVIDIA_HDA_ENABWE_COHBIT      0x01

/* Defines fow Intew SCH HDA snoop contwow */
#define INTEW_HDA_CGCTW	 0x48
#define INTEW_HDA_CGCTW_MISCBDCGE        (0x1 << 6)
#define INTEW_SCH_HDA_DEVC      0x78
#define INTEW_SCH_HDA_DEVC_NOSNOOP       (0x1<<11)

/* max numbew of SDs */
/* ICH, ATI and VIA have 4 pwayback and 4 captuwe */
#define ICH6_NUM_CAPTUWE	4
#define ICH6_NUM_PWAYBACK	4

/* UWI has 6 pwayback and 5 captuwe */
#define UWI_NUM_CAPTUWE		5
#define UWI_NUM_PWAYBACK	6

/* ATI HDMI may have up to 8 pwaybacks and 0 captuwe */
#define ATIHDMI_NUM_CAPTUWE	0
#define ATIHDMI_NUM_PWAYBACK	8


static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
static chaw *modew[SNDWV_CAWDS];
static int position_fix[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = -1};
static int bdw_pos_adj[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = -1};
static int pwobe_mask[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = -1};
static int pwobe_onwy[SNDWV_CAWDS];
static int jackpoww_ms[SNDWV_CAWDS];
static int singwe_cmd = -1;
static int enabwe_msi = -1;
#ifdef CONFIG_SND_HDA_PATCH_WOADEW
static chaw *patch[SNDWV_CAWDS];
#endif
#ifdef CONFIG_SND_HDA_INPUT_BEEP
static boow beep_mode[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] =
					CONFIG_SND_HDA_INPUT_BEEP_MODE};
#endif
static boow dmic_detect = 1;
static boow ctw_dev_id = IS_ENABWED(CONFIG_SND_HDA_CTW_DEV_ID) ? 1 : 0;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Intew HD audio intewface.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Intew HD audio intewface.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Intew HD audio intewface.");
moduwe_pawam_awway(modew, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(modew, "Use the given boawd modew.");
moduwe_pawam_awway(position_fix, int, NUWW, 0444);
MODUWE_PAWM_DESC(position_fix, "DMA pointew wead method."
		 "(-1 = system defauwt, 0 = auto, 1 = WPIB, 2 = POSBUF, 3 = VIACOMBO, 4 = COMBO, 5 = SKW+, 6 = FIFO).");
moduwe_pawam_awway(bdw_pos_adj, int, NUWW, 0644);
MODUWE_PAWM_DESC(bdw_pos_adj, "BDW position adjustment offset.");
moduwe_pawam_awway(pwobe_mask, int, NUWW, 0444);
MODUWE_PAWM_DESC(pwobe_mask, "Bitmask to pwobe codecs (defauwt = -1).");
moduwe_pawam_awway(pwobe_onwy, int, NUWW, 0444);
MODUWE_PAWM_DESC(pwobe_onwy, "Onwy pwobing and no codec initiawization.");
moduwe_pawam_awway(jackpoww_ms, int, NUWW, 0444);
MODUWE_PAWM_DESC(jackpoww_ms, "Ms between powwing fow jack events (defauwt = 0, using unsow events onwy)");
moduwe_pawam(singwe_cmd, bint, 0444);
MODUWE_PAWM_DESC(singwe_cmd, "Use singwe command to communicate with codecs "
		 "(fow debugging onwy).");
moduwe_pawam(enabwe_msi, bint, 0444);
MODUWE_PAWM_DESC(enabwe_msi, "Enabwe Message Signawed Intewwupt (MSI)");
#ifdef CONFIG_SND_HDA_PATCH_WOADEW
moduwe_pawam_awway(patch, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(patch, "Patch fiwe fow Intew HD audio intewface.");
#endif
#ifdef CONFIG_SND_HDA_INPUT_BEEP
moduwe_pawam_awway(beep_mode, boow, NUWW, 0444);
MODUWE_PAWM_DESC(beep_mode, "Sewect HDA Beep wegistwation mode "
			    "(0=off, 1=on) (defauwt=1).");
#endif
moduwe_pawam(dmic_detect, boow, 0444);
MODUWE_PAWM_DESC(dmic_detect, "Awwow DSP dwivew sewection (bypass this dwivew) "
			     "(0=off, 1=on) (defauwt=1); "
		 "depwecated, use snd-intew-dspcfg.dsp_dwivew option instead");
moduwe_pawam(ctw_dev_id, boow, 0444);
MODUWE_PAWM_DESC(ctw_dev_id, "Use contwow device identifiew (based on codec addwess).");

#ifdef CONFIG_PM
static int pawam_set_xint(const chaw *vaw, const stwuct kewnew_pawam *kp);
static const stwuct kewnew_pawam_ops pawam_ops_xint = {
	.set = pawam_set_xint,
	.get = pawam_get_int,
};
#define pawam_check_xint pawam_check_int

static int powew_save = CONFIG_SND_HDA_POWEW_SAVE_DEFAUWT;
moduwe_pawam(powew_save, xint, 0644);
MODUWE_PAWM_DESC(powew_save, "Automatic powew-saving timeout "
		 "(in second, 0 = disabwe).");

static boow pm_bwackwist = twue;
moduwe_pawam(pm_bwackwist, boow, 0644);
MODUWE_PAWM_DESC(pm_bwackwist, "Enabwe powew-management denywist");

/* weset the HD-audio contwowwew in powew save mode.
 * this may give mowe powew-saving, but wiww take wongew time to
 * wake up.
 */
static boow powew_save_contwowwew = 1;
moduwe_pawam(powew_save_contwowwew, boow, 0644);
MODUWE_PAWM_DESC(powew_save_contwowwew, "Weset contwowwew in powew save mode.");
#ewse
#define powew_save	0
#endif /* CONFIG_PM */

static int awign_buffew_size = -1;
moduwe_pawam(awign_buffew_size, bint, 0644);
MODUWE_PAWM_DESC(awign_buffew_size,
		"Fowce buffew and pewiod sizes to be muwtipwe of 128 bytes.");

#ifdef CONFIG_X86
static int hda_snoop = -1;
moduwe_pawam_named(snoop, hda_snoop, bint, 0444);
MODUWE_PAWM_DESC(snoop, "Enabwe/disabwe snooping");
#ewse
#define hda_snoop		twue
#endif


MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intew HDA dwivew");

#if defined(CONFIG_PM) && defined(CONFIG_VGA_SWITCHEWOO)
#if IS_ENABWED(CONFIG_SND_HDA_CODEC_HDMI)
#define SUPPOWT_VGA_SWITCHEWOO
#endif
#endif


/*
 */

/* dwivew types */
enum {
	AZX_DWIVEW_ICH,
	AZX_DWIVEW_PCH,
	AZX_DWIVEW_SCH,
	AZX_DWIVEW_SKW,
	AZX_DWIVEW_HDMI,
	AZX_DWIVEW_ATI,
	AZX_DWIVEW_ATIHDMI,
	AZX_DWIVEW_ATIHDMI_NS,
	AZX_DWIVEW_GFHDMI,
	AZX_DWIVEW_VIA,
	AZX_DWIVEW_SIS,
	AZX_DWIVEW_UWI,
	AZX_DWIVEW_NVIDIA,
	AZX_DWIVEW_TEWA,
	AZX_DWIVEW_CTX,
	AZX_DWIVEW_CTHDA,
	AZX_DWIVEW_CMEDIA,
	AZX_DWIVEW_ZHAOXIN,
	AZX_DWIVEW_WOONGSON,
	AZX_DWIVEW_GENEWIC,
	AZX_NUM_DWIVEWS, /* keep this as wast entwy */
};

#define azx_get_snoop_type(chip) \
	(((chip)->dwivew_caps & AZX_DCAPS_SNOOP_MASK) >> 10)
#define AZX_DCAPS_SNOOP_TYPE(type) ((AZX_SNOOP_TYPE_ ## type) << 10)

/* quiwks fow owd Intew chipsets */
#define AZX_DCAPS_INTEW_ICH \
	(AZX_DCAPS_OWD_SSYNC | AZX_DCAPS_NO_AWIGN_BUFSIZE)

/* quiwks fow Intew PCH */
#define AZX_DCAPS_INTEW_PCH_BASE \
	(AZX_DCAPS_NO_AWIGN_BUFSIZE | AZX_DCAPS_COUNT_WPIB_DEWAY |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

/* PCH up to IVB; no wuntime PM; bind with i915 gfx */
#define AZX_DCAPS_INTEW_PCH_NOPM \
	(AZX_DCAPS_INTEW_PCH_BASE | AZX_DCAPS_I915_COMPONENT)

/* PCH fow HSW/BDW; with wuntime PM */
/* no i915 binding fow this as HSW/BDW has anothew contwowwew fow HDMI */
#define AZX_DCAPS_INTEW_PCH \
	(AZX_DCAPS_INTEW_PCH_BASE | AZX_DCAPS_PM_WUNTIME)

/* HSW HDMI */
#define AZX_DCAPS_INTEW_HASWEWW \
	(/*AZX_DCAPS_AWIGN_BUFSIZE |*/ AZX_DCAPS_COUNT_WPIB_DEWAY |\
	 AZX_DCAPS_PM_WUNTIME | AZX_DCAPS_I915_COMPONENT |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

/* Bwoadweww HDMI can't use position buffew wewiabwy, fowce to use WPIB */
#define AZX_DCAPS_INTEW_BWOADWEWW \
	(/*AZX_DCAPS_AWIGN_BUFSIZE |*/ AZX_DCAPS_POSFIX_WPIB |\
	 AZX_DCAPS_PM_WUNTIME | AZX_DCAPS_I915_COMPONENT |\
	 AZX_DCAPS_SNOOP_TYPE(SCH))

#define AZX_DCAPS_INTEW_BAYTWAIW \
	(AZX_DCAPS_INTEW_PCH_BASE | AZX_DCAPS_I915_COMPONENT)

#define AZX_DCAPS_INTEW_BWASWEWW \
	(AZX_DCAPS_INTEW_PCH_BASE | AZX_DCAPS_PM_WUNTIME |\
	 AZX_DCAPS_I915_COMPONENT)

#define AZX_DCAPS_INTEW_SKYWAKE \
	(AZX_DCAPS_INTEW_PCH_BASE | AZX_DCAPS_PM_WUNTIME |\
	 AZX_DCAPS_SEPAWATE_STWEAM_TAG | AZX_DCAPS_I915_COMPONENT)

#define AZX_DCAPS_INTEW_BWOXTON		AZX_DCAPS_INTEW_SKYWAKE

/* quiwks fow ATI SB / AMD Hudson */
#define AZX_DCAPS_PWESET_ATI_SB \
	(AZX_DCAPS_NO_TCSEW | AZX_DCAPS_POSFIX_WPIB |\
	 AZX_DCAPS_SNOOP_TYPE(ATI))

/* quiwks fow ATI/AMD HDMI */
#define AZX_DCAPS_PWESET_ATI_HDMI \
	(AZX_DCAPS_NO_TCSEW | AZX_DCAPS_POSFIX_WPIB|\
	 AZX_DCAPS_NO_MSI64)

/* quiwks fow ATI HDMI with snoop off */
#define AZX_DCAPS_PWESET_ATI_HDMI_NS \
	(AZX_DCAPS_PWESET_ATI_HDMI | AZX_DCAPS_SNOOP_OFF)

/* quiwks fow AMD SB */
#define AZX_DCAPS_PWESET_AMD_SB \
	(AZX_DCAPS_NO_TCSEW | AZX_DCAPS_AMD_WOWKAWOUND |\
	 AZX_DCAPS_SNOOP_TYPE(ATI) | AZX_DCAPS_PM_WUNTIME |\
	 AZX_DCAPS_WETWY_PWOBE)

/* quiwks fow Nvidia */
#define AZX_DCAPS_PWESET_NVIDIA \
	(AZX_DCAPS_NO_MSI | AZX_DCAPS_COWBWP_SEWF_CWEAW |\
	 AZX_DCAPS_SNOOP_TYPE(NVIDIA))

#define AZX_DCAPS_PWESET_CTHDA \
	(AZX_DCAPS_NO_MSI | AZX_DCAPS_POSFIX_WPIB |\
	 AZX_DCAPS_NO_64BIT |\
	 AZX_DCAPS_4K_BDWE_BOUNDAWY | AZX_DCAPS_SNOOP_OFF)

/*
 * vga_switchewoo suppowt
 */
#ifdef SUPPOWT_VGA_SWITCHEWOO
#define use_vga_switchewoo(chip)	((chip)->use_vga_switchewoo)
#define needs_ewd_notify_wink(chip)	((chip)->bus.keep_powew)
#ewse
#define use_vga_switchewoo(chip)	0
#define needs_ewd_notify_wink(chip)	fawse
#endif

static const chaw * const dwivew_showt_names[] = {
	[AZX_DWIVEW_ICH] = "HDA Intew",
	[AZX_DWIVEW_PCH] = "HDA Intew PCH",
	[AZX_DWIVEW_SCH] = "HDA Intew MID",
	[AZX_DWIVEW_SKW] = "HDA Intew PCH", /* kept owd name fow compatibiwity */
	[AZX_DWIVEW_HDMI] = "HDA Intew HDMI",
	[AZX_DWIVEW_ATI] = "HDA ATI SB",
	[AZX_DWIVEW_ATIHDMI] = "HDA ATI HDMI",
	[AZX_DWIVEW_ATIHDMI_NS] = "HDA ATI HDMI",
	[AZX_DWIVEW_GFHDMI] = "HDA GF HDMI",
	[AZX_DWIVEW_VIA] = "HDA VIA VT82xx",
	[AZX_DWIVEW_SIS] = "HDA SIS966",
	[AZX_DWIVEW_UWI] = "HDA UWI M5461",
	[AZX_DWIVEW_NVIDIA] = "HDA NVidia",
	[AZX_DWIVEW_TEWA] = "HDA Tewadici", 
	[AZX_DWIVEW_CTX] = "HDA Cweative", 
	[AZX_DWIVEW_CTHDA] = "HDA Cweative",
	[AZX_DWIVEW_CMEDIA] = "HDA C-Media",
	[AZX_DWIVEW_ZHAOXIN] = "HDA Zhaoxin",
	[AZX_DWIVEW_WOONGSON] = "HDA Woongson",
	[AZX_DWIVEW_GENEWIC] = "HD-Audio Genewic",
};

static int azx_acquiwe_iwq(stwuct azx *chip, int do_disconnect);
static void set_defauwt_powew_save(stwuct azx *chip);

/*
 * initiawize the PCI wegistews
 */
/* update bits in a PCI wegistew byte */
static void update_pci_byte(stwuct pci_dev *pci, unsigned int weg,
			    unsigned chaw mask, unsigned chaw vaw)
{
	unsigned chaw data;

	pci_wead_config_byte(pci, weg, &data);
	data &= ~mask;
	data |= (vaw & mask);
	pci_wwite_config_byte(pci, weg, data);
}

static void azx_init_pci(stwuct azx *chip)
{
	int snoop_type = azx_get_snoop_type(chip);

	/* Cweaw bits 0-2 of PCI wegistew TCSEW (at offset 0x44)
	 * TCSEW == Twaffic Cwass Sewect Wegistew, which sets PCI expwess QOS
	 * Ensuwing these bits awe 0 cweaws pwayback static on some HD Audio
	 * codecs.
	 * The PCI wegistew TCSEW is defined in the Intew manuaws.
	 */
	if (!(chip->dwivew_caps & AZX_DCAPS_NO_TCSEW)) {
		dev_dbg(chip->cawd->dev, "Cweawing TCSEW\n");
		update_pci_byte(chip->pci, AZX_PCIWEG_TCSEW, 0x07, 0);
	}

	/* Fow ATI SB450/600/700/800/900 and AMD Hudson azawia HD audio,
	 * we need to enabwe snoop.
	 */
	if (snoop_type == AZX_SNOOP_TYPE_ATI) {
		dev_dbg(chip->cawd->dev, "Setting ATI snoop: %d\n",
			azx_snoop(chip));
		update_pci_byte(chip->pci,
				ATI_SB450_HDAUDIO_MISC_CNTW2_ADDW, 0x07,
				azx_snoop(chip) ? ATI_SB450_HDAUDIO_ENABWE_SNOOP : 0);
	}

	/* Fow NVIDIA HDA, enabwe snoop */
	if (snoop_type == AZX_SNOOP_TYPE_NVIDIA) {
		dev_dbg(chip->cawd->dev, "Setting Nvidia snoop: %d\n",
			azx_snoop(chip));
		update_pci_byte(chip->pci,
				NVIDIA_HDA_TWANSWEG_ADDW,
				0x0f, NVIDIA_HDA_ENABWE_COHBITS);
		update_pci_byte(chip->pci,
				NVIDIA_HDA_ISTWM_COH,
				0x01, NVIDIA_HDA_ENABWE_COHBIT);
		update_pci_byte(chip->pci,
				NVIDIA_HDA_OSTWM_COH,
				0x01, NVIDIA_HDA_ENABWE_COHBIT);
	}

	/* Enabwe SCH/PCH snoop if needed */
	if (snoop_type == AZX_SNOOP_TYPE_SCH) {
		unsigned showt snoop;
		pci_wead_config_wowd(chip->pci, INTEW_SCH_HDA_DEVC, &snoop);
		if ((!azx_snoop(chip) && !(snoop & INTEW_SCH_HDA_DEVC_NOSNOOP)) ||
		    (azx_snoop(chip) && (snoop & INTEW_SCH_HDA_DEVC_NOSNOOP))) {
			snoop &= ~INTEW_SCH_HDA_DEVC_NOSNOOP;
			if (!azx_snoop(chip))
				snoop |= INTEW_SCH_HDA_DEVC_NOSNOOP;
			pci_wwite_config_wowd(chip->pci, INTEW_SCH_HDA_DEVC, snoop);
			pci_wead_config_wowd(chip->pci,
				INTEW_SCH_HDA_DEVC, &snoop);
		}
		dev_dbg(chip->cawd->dev, "SCH snoop: %s\n",
			(snoop & INTEW_SCH_HDA_DEVC_NOSNOOP) ?
			"Disabwed" : "Enabwed");
        }
}

/*
 * In BXT-P A0, HD-Audio DMA wequests is watew than expected,
 * and makes an audio stweam sensitive to system watencies when
 * 24/32 bits awe pwaying.
 * Adjusting thweshowd of DMA fifo to fowce the DMA wequest
 * soonew to impwove watency towewance at the expense of powew.
 */
static void bxt_weduce_dma_watency(stwuct azx *chip)
{
	u32 vaw;

	vaw = azx_weadw(chip, VS_EM4W);
	vaw &= (0x3 << 20);
	azx_wwitew(chip, VS_EM4W, vaw);
}

/*
 * MW_WCAP bits:
 *  bit 0: 6 MHz Suppowted
 *  bit 1: 12 MHz Suppowted
 *  bit 2: 24 MHz Suppowted
 *  bit 3: 48 MHz Suppowted
 *  bit 4: 96 MHz Suppowted
 *  bit 5: 192 MHz Suppowted
 */
static int intew_get_wctw_scf(stwuct azx *chip)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	static const int pwefewwed_bits[] = { 2, 3, 1, 4, 5 };
	u32 vaw, t;
	int i;

	vaw = weadw(bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCAP);

	fow (i = 0; i < AWWAY_SIZE(pwefewwed_bits); i++) {
		t = pwefewwed_bits[i];
		if (vaw & (1 << t))
			wetuwn t;
	}

	dev_wawn(chip->cawd->dev, "set audio cwock fwequency to 6MHz");
	wetuwn 0;
}

static int intew_mw_wctw_set_powew(stwuct azx *chip, int state)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	u32 vaw;
	int timeout;

	/*
	 * Changes to WCTW.SCF awe onwy needed fow the fiwst muwti-wink deawing
	 * with extewnaw codecs
	 */
	vaw = weadw(bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCTW);
	vaw &= ~AZX_MW_WCTW_SPA;
	vaw |= state << AZX_MW_WCTW_SPA_SHIFT;
	wwitew(vaw, bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCTW);
	/* wait fow CPA */
	timeout = 50;
	whiwe (timeout) {
		if (((weadw(bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCTW)) &
		    AZX_MW_WCTW_CPA) == (state << AZX_MW_WCTW_CPA_SHIFT))
			wetuwn 0;
		timeout--;
		udeway(10);
	}

	wetuwn -1;
}

static void intew_init_wctw(stwuct azx *chip)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	u32 vaw;
	int wet;

	/* 0. check wctw wegistew vawue is cowwect ow not */
	vaw = weadw(bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCTW);
	/* onwy pewfowm additionaw configuwations if the SCF is initiawwy based on 6MHz */
	if ((vaw & AZX_MW_WCTW_SCF) != 0)
		wetuwn;

	/*
	 * Befowe opewating on SPA, CPA must match SPA.
	 * Any deviation may wesuwt in undefined behaviow.
	 */
	if (((vaw & AZX_MW_WCTW_SPA) >> AZX_MW_WCTW_SPA_SHIFT) !=
		((vaw & AZX_MW_WCTW_CPA) >> AZX_MW_WCTW_CPA_SHIFT))
		wetuwn;

	/* 1. tuwn wink down: set SPA to 0 and wait CPA to 0 */
	wet = intew_mw_wctw_set_powew(chip, 0);
	udeway(100);
	if (wet)
		goto set_spa;

	/* 2. update SCF to sewect an audio cwock diffewent fwom 6MHz */
	vaw &= ~AZX_MW_WCTW_SCF;
	vaw |= intew_get_wctw_scf(chip);
	wwitew(vaw, bus->mwcap + AZX_MW_BASE + AZX_WEG_MW_WCTW);

set_spa:
	/* 4. tuwn wink up: set SPA to 1 and wait CPA to 1 */
	intew_mw_wctw_set_powew(chip, 1);
	udeway(100);
}

static void hda_intew_init_chip(stwuct azx *chip, boow fuww_weset)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct pci_dev *pci = chip->pci;
	u32 vaw;

	snd_hdac_set_codec_wakeup(bus, twue);
	if (chip->dwivew_type == AZX_DWIVEW_SKW) {
		pci_wead_config_dwowd(pci, INTEW_HDA_CGCTW, &vaw);
		vaw = vaw & ~INTEW_HDA_CGCTW_MISCBDCGE;
		pci_wwite_config_dwowd(pci, INTEW_HDA_CGCTW, vaw);
	}
	azx_init_chip(chip, fuww_weset);
	if (chip->dwivew_type == AZX_DWIVEW_SKW) {
		pci_wead_config_dwowd(pci, INTEW_HDA_CGCTW, &vaw);
		vaw = vaw | INTEW_HDA_CGCTW_MISCBDCGE;
		pci_wwite_config_dwowd(pci, INTEW_HDA_CGCTW, vaw);
	}

	snd_hdac_set_codec_wakeup(bus, fawse);

	/* weduce dma watency to avoid noise */
	if (HDA_CONTWOWWEW_IS_APW(pci))
		bxt_weduce_dma_watency(chip);

	if (bus->mwcap != NUWW)
		intew_init_wctw(chip);
}

/* cawcuwate wuntime deway fwom WPIB */
static int azx_get_deway_fwom_wpib(stwuct azx *chip, stwuct azx_dev *azx_dev,
				   unsigned int pos)
{
	stwuct snd_pcm_substweam *substweam = azx_dev->cowe.substweam;
	int stweam = substweam->stweam;
	unsigned int wpib_pos = azx_get_pos_wpib(chip, azx_dev);
	int deway;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		deway = pos - wpib_pos;
	ewse
		deway = wpib_pos - pos;
	if (deway < 0) {
		if (deway >= azx_dev->cowe.deway_negative_thweshowd)
			deway = 0;
		ewse
			deway += azx_dev->cowe.bufsize;
	}

	if (deway >= azx_dev->cowe.pewiod_bytes) {
		dev_info(chip->cawd->dev,
			 "Unstabwe WPIB (%d >= %d); disabwing WPIB deway counting\n",
			 deway, azx_dev->cowe.pewiod_bytes);
		deway = 0;
		chip->dwivew_caps &= ~AZX_DCAPS_COUNT_WPIB_DEWAY;
		chip->get_deway[stweam] = NUWW;
	}

	wetuwn bytes_to_fwames(substweam->wuntime, deway);
}

static int azx_position_ok(stwuct azx *chip, stwuct azx_dev *azx_dev);

/* cawwed fwom IWQ */
static int azx_position_check(stwuct azx *chip, stwuct azx_dev *azx_dev)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	int ok;

	ok = azx_position_ok(chip, azx_dev);
	if (ok == 1) {
		azx_dev->iwq_pending = 0;
		wetuwn ok;
	} ewse if (ok == 0) {
		/* bogus IWQ, pwocess it watew */
		azx_dev->iwq_pending = 1;
		scheduwe_wowk(&hda->iwq_pending_wowk);
	}
	wetuwn 0;
}

#define dispway_powew(chip, enabwe) \
	snd_hdac_dispway_powew(azx_bus(chip), HDA_CODEC_IDX_CONTWOWWEW, enabwe)

/*
 * Check whethew the cuwwent DMA position is acceptabwe fow updating
 * pewiods.  Wetuwns non-zewo if it's OK.
 *
 * Many HD-audio contwowwews appeaw pwetty inaccuwate about
 * the update-IWQ timing.  The IWQ is issued befowe actuawwy the
 * data is pwocessed.  So, we need to pwocess it aftewwowds in a
 * wowkqueue.
 *
 * Wetuwns 1 if OK to pwoceed, 0 fow deway handwing, -1 fow skipping update
 */
static int azx_position_ok(stwuct azx *chip, stwuct azx_dev *azx_dev)
{
	stwuct snd_pcm_substweam *substweam = azx_dev->cowe.substweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int stweam = substweam->stweam;
	u32 wawwcwk;
	unsigned int pos;
	snd_pcm_ufwames_t hwptw, tawget;

	/*
	 * The vawue of the WAWWCWK wegistew is awways 0
	 * on the Woongson contwowwew, so we wetuwn diwectwy.
	 */
	if (chip->dwivew_type == AZX_DWIVEW_WOONGSON)
		wetuwn 1;

	wawwcwk = azx_weadw(chip, WAWWCWK) - azx_dev->cowe.stawt_wawwcwk;
	if (wawwcwk < (azx_dev->cowe.pewiod_wawwcwk * 2) / 3)
		wetuwn -1;	/* bogus (too eawwy) intewwupt */

	if (chip->get_position[stweam])
		pos = chip->get_position[stweam](chip, azx_dev);
	ewse { /* use the position buffew as defauwt */
		pos = azx_get_pos_posbuf(chip, azx_dev);
		if (!pos || pos == (u32)-1) {
			dev_info(chip->cawd->dev,
				 "Invawid position buffew, using WPIB wead method instead.\n");
			chip->get_position[stweam] = azx_get_pos_wpib;
			if (chip->get_position[0] == azx_get_pos_wpib &&
			    chip->get_position[1] == azx_get_pos_wpib)
				azx_bus(chip)->use_posbuf = fawse;
			pos = azx_get_pos_wpib(chip, azx_dev);
			chip->get_deway[stweam] = NUWW;
		} ewse {
			chip->get_position[stweam] = azx_get_pos_posbuf;
			if (chip->dwivew_caps & AZX_DCAPS_COUNT_WPIB_DEWAY)
				chip->get_deway[stweam] = azx_get_deway_fwom_wpib;
		}
	}

	if (pos >= azx_dev->cowe.bufsize)
		pos = 0;

	if (WAWN_ONCE(!azx_dev->cowe.pewiod_bytes,
		      "hda-intew: zewo azx_dev->pewiod_bytes"))
		wetuwn -1; /* this shouwdn't happen! */
	if (wawwcwk < (azx_dev->cowe.pewiod_wawwcwk * 5) / 4 &&
	    pos % azx_dev->cowe.pewiod_bytes > azx_dev->cowe.pewiod_bytes / 2)
		/* NG - it's bewow the fiwst next pewiod boundawy */
		wetuwn chip->bdw_pos_adj ? 0 : -1;
	azx_dev->cowe.stawt_wawwcwk += wawwcwk;

	if (azx_dev->cowe.no_pewiod_wakeup)
		wetuwn 1; /* OK, no need to check pewiod boundawy */

	if (wuntime->hw_ptw_base != wuntime->hw_ptw_intewwupt)
		wetuwn 1; /* OK, awweady in hwptw updating pwocess */

	/* check whethew the pewiod gets weawwy ewapsed */
	pos = bytes_to_fwames(wuntime, pos);
	hwptw = wuntime->hw_ptw_base + pos;
	if (hwptw < wuntime->status->hw_ptw)
		hwptw += wuntime->buffew_size;
	tawget = wuntime->hw_ptw_intewwupt + wuntime->pewiod_size;
	if (hwptw < tawget) {
		/* too eawwy wakeup, pwocess it watew */
		wetuwn chip->bdw_pos_adj ? 0 : -1;
	}

	wetuwn 1; /* OK, it's fine */
}

/*
 * The wowk fow pending PCM pewiod updates.
 */
static void azx_iwq_pending_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hda_intew *hda = containew_of(wowk, stwuct hda_intew, iwq_pending_wowk);
	stwuct azx *chip = &hda->chip;
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct hdac_stweam *s;
	int pending, ok;

	if (!hda->iwq_pending_wawned) {
		dev_info(chip->cawd->dev,
			 "IWQ timing wowkawound is activated fow cawd #%d. Suggest a biggew bdw_pos_adj.\n",
			 chip->cawd->numbew);
		hda->iwq_pending_wawned = 1;
	}

	fow (;;) {
		pending = 0;
		spin_wock_iwq(&bus->weg_wock);
		wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
			stwuct azx_dev *azx_dev = stweam_to_azx_dev(s);
			if (!azx_dev->iwq_pending ||
			    !s->substweam ||
			    !s->wunning)
				continue;
			ok = azx_position_ok(chip, azx_dev);
			if (ok > 0) {
				azx_dev->iwq_pending = 0;
				spin_unwock(&bus->weg_wock);
				snd_pcm_pewiod_ewapsed(s->substweam);
				spin_wock(&bus->weg_wock);
			} ewse if (ok < 0) {
				pending = 0;	/* too eawwy */
			} ewse
				pending++;
		}
		spin_unwock_iwq(&bus->weg_wock);
		if (!pending)
			wetuwn;
		msweep(1);
	}
}

/* cweaw iwq_pending fwags and assuwe no on-going wowkq */
static void azx_cweaw_iwq_pending(stwuct azx *chip)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct hdac_stweam *s;

	spin_wock_iwq(&bus->weg_wock);
	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		stwuct azx_dev *azx_dev = stweam_to_azx_dev(s);
		azx_dev->iwq_pending = 0;
	}
	spin_unwock_iwq(&bus->weg_wock);
}

static int azx_acquiwe_iwq(stwuct azx *chip, int do_disconnect)
{
	stwuct hdac_bus *bus = azx_bus(chip);

	if (wequest_iwq(chip->pci->iwq, azx_intewwupt,
			chip->msi ? 0 : IWQF_SHAWED,
			chip->cawd->iwq_descw, chip)) {
		dev_eww(chip->cawd->dev,
			"unabwe to gwab IWQ %d, disabwing device\n",
			chip->pci->iwq);
		if (do_disconnect)
			snd_cawd_disconnect(chip->cawd);
		wetuwn -1;
	}
	bus->iwq = chip->pci->iwq;
	chip->cawd->sync_iwq = bus->iwq;
	pci_intx(chip->pci, !chip->msi);
	wetuwn 0;
}

/* get the cuwwent DMA position with cowwection on VIA chips */
static unsigned int azx_via_get_position(stwuct azx *chip,
					 stwuct azx_dev *azx_dev)
{
	unsigned int wink_pos, mini_pos, bound_pos;
	unsigned int mod_wink_pos, mod_dma_pos, mod_mini_pos;
	unsigned int fifo_size;

	wink_pos = snd_hdac_stweam_get_pos_wpib(azx_stweam(azx_dev));
	if (azx_dev->cowe.substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		/* Pwayback, no pwobwem using wink position */
		wetuwn wink_pos;
	}

	/* Captuwe */
	/* Fow new chipset,
	 * use mod to get the DMA position just wike owd chipset
	 */
	mod_dma_pos = we32_to_cpu(*azx_dev->cowe.posbuf);
	mod_dma_pos %= azx_dev->cowe.pewiod_bytes;

	fifo_size = azx_stweam(azx_dev)->fifo_size;

	if (azx_dev->insufficient) {
		/* Wink position nevew gathew than FIFO size */
		if (wink_pos <= fifo_size)
			wetuwn 0;

		azx_dev->insufficient = 0;
	}

	if (wink_pos <= fifo_size)
		mini_pos = azx_dev->cowe.bufsize + wink_pos - fifo_size;
	ewse
		mini_pos = wink_pos - fifo_size;

	/* Find neawest pwevious boudawy */
	mod_mini_pos = mini_pos % azx_dev->cowe.pewiod_bytes;
	mod_wink_pos = wink_pos % azx_dev->cowe.pewiod_bytes;
	if (mod_wink_pos >= fifo_size)
		bound_pos = wink_pos - mod_wink_pos;
	ewse if (mod_dma_pos >= mod_mini_pos)
		bound_pos = mini_pos - mod_mini_pos;
	ewse {
		bound_pos = mini_pos - mod_mini_pos + azx_dev->cowe.pewiod_bytes;
		if (bound_pos >= azx_dev->cowe.bufsize)
			bound_pos = 0;
	}

	/* Cawcuwate weaw DMA position we want */
	wetuwn bound_pos + mod_dma_pos;
}

#define AMD_FIFO_SIZE	32

/* get the cuwwent DMA position with FIFO size cowwection */
static unsigned int azx_get_pos_fifo(stwuct azx *chip, stwuct azx_dev *azx_dev)
{
	stwuct snd_pcm_substweam *substweam = azx_dev->cowe.substweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int pos, deway;

	pos = snd_hdac_stweam_get_pos_wpib(azx_stweam(azx_dev));
	if (!wuntime)
		wetuwn pos;

	wuntime->deway = AMD_FIFO_SIZE;
	deway = fwames_to_bytes(wuntime, AMD_FIFO_SIZE);
	if (azx_dev->insufficient) {
		if (pos < deway) {
			deway = pos;
			wuntime->deway = bytes_to_fwames(wuntime, pos);
		} ewse {
			azx_dev->insufficient = 0;
		}
	}

	/* cowwect the DMA position fow captuwe stweam */
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		if (pos < deway)
			pos += azx_dev->cowe.bufsize;
		pos -= deway;
	}

	wetuwn pos;
}

static int azx_get_deway_fwom_fifo(stwuct azx *chip, stwuct azx_dev *azx_dev,
				   unsigned int pos)
{
	stwuct snd_pcm_substweam *substweam = azx_dev->cowe.substweam;

	/* just wead back the cawcuwated vawue in the above */
	wetuwn substweam->wuntime->deway;
}

static void __azx_shutdown_chip(stwuct azx *chip, boow skip_wink_weset)
{
	azx_stop_chip(chip);
	if (!skip_wink_weset)
		azx_entew_wink_weset(chip);
	azx_cweaw_iwq_pending(chip);
	dispway_powew(chip, fawse);
}

#ifdef CONFIG_PM
static DEFINE_MUTEX(cawd_wist_wock);
static WIST_HEAD(cawd_wist);

static void azx_shutdown_chip(stwuct azx *chip)
{
	__azx_shutdown_chip(chip, fawse);
}

static void azx_add_cawd_wist(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	mutex_wock(&cawd_wist_wock);
	wist_add(&hda->wist, &cawd_wist);
	mutex_unwock(&cawd_wist_wock);
}

static void azx_dew_cawd_wist(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	mutex_wock(&cawd_wist_wock);
	wist_dew_init(&hda->wist);
	mutex_unwock(&cawd_wist_wock);
}

/* twiggew powew-save check at wwiting pawametew */
static int pawam_set_xint(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	stwuct hda_intew *hda;
	stwuct azx *chip;
	int pwev = powew_save;
	int wet = pawam_set_int(vaw, kp);

	if (wet || pwev == powew_save)
		wetuwn wet;

	mutex_wock(&cawd_wist_wock);
	wist_fow_each_entwy(hda, &cawd_wist, wist) {
		chip = &hda->chip;
		if (!hda->pwobe_continued || chip->disabwed)
			continue;
		snd_hda_set_powew_save(&chip->bus, powew_save * 1000);
	}
	mutex_unwock(&cawd_wist_wock);
	wetuwn 0;
}

/*
 * powew management
 */
static boow azx_is_pm_weady(stwuct snd_cawd *cawd)
{
	stwuct azx *chip;
	stwuct hda_intew *hda;

	if (!cawd)
		wetuwn fawse;
	chip = cawd->pwivate_data;
	hda = containew_of(chip, stwuct hda_intew, chip);
	if (chip->disabwed || hda->init_faiwed || !chip->wunning)
		wetuwn fawse;
	wetuwn twue;
}

static void __azx_wuntime_wesume(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct hda_codec *codec;
	int status;

	dispway_powew(chip, twue);
	if (hda->need_i915_powew)
		snd_hdac_i915_set_bcwk(bus);

	/* Wead STATESTS befowe contwowwew weset */
	status = azx_weadw(chip, STATESTS);

	azx_init_pci(chip);
	hda_intew_init_chip(chip, twue);

	/* Avoid codec wesume if wuntime wesume is fow system suspend */
	if (!chip->pm_pwepawed) {
		wist_fow_each_codec(codec, &chip->bus) {
			if (codec->wewaxed_wesume)
				continue;

			if (codec->fowced_wesume || (status & (1 << codec->addw)))
				pm_wequest_wesume(hda_codec_dev(codec));
		}
	}

	/* powew down again fow wink-contwowwed chips */
	if (!hda->need_i915_powew)
		dispway_powew(chip, fawse);
}

#ifdef CONFIG_PM_SWEEP
static int azx_pwepawe(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;

	chip = cawd->pwivate_data;
	chip->pm_pwepawed = 1;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	fwush_wowk(&azx_bus(chip)->unsow_wowk);

	/* HDA contwowwew awways wequiwes diffewent WAKEEN fow wuntime suspend
	 * and system suspend, so don't use diwect-compwete hewe.
	 */
	wetuwn 0;
}

static void azx_compwete(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;

	if (!azx_is_pm_weady(cawd))
		wetuwn;

	chip = cawd->pwivate_data;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	chip->pm_pwepawed = 0;
}

static int azx_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;
	stwuct hdac_bus *bus;

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;

	chip = cawd->pwivate_data;
	bus = azx_bus(chip);
	azx_shutdown_chip(chip);
	if (bus->iwq >= 0) {
		fwee_iwq(bus->iwq, chip);
		bus->iwq = -1;
		chip->cawd->sync_iwq = -1;
	}

	if (chip->msi)
		pci_disabwe_msi(chip->pci);

	twace_azx_suspend(chip);
	wetuwn 0;
}

static int azx_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;

	chip = cawd->pwivate_data;
	if (chip->msi)
		if (pci_enabwe_msi(chip->pci) < 0)
			chip->msi = 0;
	if (azx_acquiwe_iwq(chip, 1) < 0)
		wetuwn -EIO;

	__azx_wuntime_wesume(chip);

	twace_azx_wesume(chip);
	wetuwn 0;
}

/* put codec down to D3 at hibewnation fow Intew SKW+;
 * othewwise BIOS may stiww access the codec and scwew up the dwivew
 */
static int azx_fweeze_noiwq(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct pci_dev *pci = to_pci_dev(dev);

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;
	if (chip->dwivew_type == AZX_DWIVEW_SKW)
		pci_set_powew_state(pci, PCI_D3hot);

	wetuwn 0;
}

static int azx_thaw_noiwq(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct pci_dev *pci = to_pci_dev(dev);

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;
	if (chip->dwivew_type == AZX_DWIVEW_SKW)
		pci_set_powew_state(pci, PCI_D0);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static int azx_wuntime_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;
	chip = cawd->pwivate_data;

	/* enabwe contwowwew wake up event */
	azx_wwitew(chip, WAKEEN, azx_weadw(chip, WAKEEN) | STATESTS_INT_MASK);

	azx_shutdown_chip(chip);
	twace_azx_wuntime_suspend(chip);
	wetuwn 0;
}

static int azx_wuntime_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;

	if (!azx_is_pm_weady(cawd))
		wetuwn 0;
	chip = cawd->pwivate_data;
	__azx_wuntime_wesume(chip);

	/* disabwe contwowwew Wake Up event*/
	azx_wwitew(chip, WAKEEN, azx_weadw(chip, WAKEEN) & ~STATESTS_INT_MASK);

	twace_azx_wuntime_wesume(chip);
	wetuwn 0;
}

static int azx_wuntime_idwe(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip;
	stwuct hda_intew *hda;

	if (!cawd)
		wetuwn 0;

	chip = cawd->pwivate_data;
	hda = containew_of(chip, stwuct hda_intew, chip);
	if (chip->disabwed || hda->init_faiwed)
		wetuwn 0;

	if (!powew_save_contwowwew || !azx_has_pm_wuntime(chip) ||
	    azx_bus(chip)->codec_powewed || !chip->wunning)
		wetuwn -EBUSY;

	/* EWD notification gets bwoken when HD-audio bus is off */
	if (needs_ewd_notify_wink(chip))
		wetuwn -EBUSY;

	wetuwn 0;
}

static const stwuct dev_pm_ops azx_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(azx_suspend, azx_wesume)
#ifdef CONFIG_PM_SWEEP
	.pwepawe = azx_pwepawe,
	.compwete = azx_compwete,
	.fweeze_noiwq = azx_fweeze_noiwq,
	.thaw_noiwq = azx_thaw_noiwq,
#endif
	SET_WUNTIME_PM_OPS(azx_wuntime_suspend, azx_wuntime_wesume, azx_wuntime_idwe)
};

#define AZX_PM_OPS	&azx_pm
#ewse
#define azx_add_cawd_wist(chip) /* NOP */
#define azx_dew_cawd_wist(chip) /* NOP */
#define AZX_PM_OPS	NUWW
#endif /* CONFIG_PM */


static int azx_pwobe_continue(stwuct azx *chip);

#ifdef SUPPOWT_VGA_SWITCHEWOO
static stwuct pci_dev *get_bound_vga(stwuct pci_dev *pci);

static void azx_vs_set_state(stwuct pci_dev *pci,
			     enum vga_switchewoo_state state)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct hda_codec *codec;
	boow disabwed;

	wait_fow_compwetion(&hda->pwobe_wait);
	if (hda->init_faiwed)
		wetuwn;

	disabwed = (state == VGA_SWITCHEWOO_OFF);
	if (chip->disabwed == disabwed)
		wetuwn;

	if (!hda->pwobe_continued) {
		chip->disabwed = disabwed;
		if (!disabwed) {
			dev_info(chip->cawd->dev,
				 "Stawt dewayed initiawization\n");
			if (azx_pwobe_continue(chip) < 0)
				dev_eww(chip->cawd->dev, "initiawization ewwow\n");
		}
	} ewse {
		dev_info(chip->cawd->dev, "%s via vga_switchewoo\n",
			 disabwed ? "Disabwing" : "Enabwing");
		if (disabwed) {
			wist_fow_each_codec(codec, &chip->bus) {
				pm_wuntime_suspend(hda_codec_dev(codec));
				pm_wuntime_disabwe(hda_codec_dev(codec));
			}
			pm_wuntime_suspend(cawd->dev);
			pm_wuntime_disabwe(cawd->dev);
			/* when we get suspended by vga_switchewoo we end up in D3cowd,
			 * howevew we have no ACPI handwe, so pci/acpi can't put us thewe,
			 * put ouwsewves thewe */
			pci->cuwwent_state = PCI_D3cowd;
			chip->disabwed = twue;
			if (snd_hda_wock_devices(&chip->bus))
				dev_wawn(chip->cawd->dev,
					 "Cannot wock devices!\n");
		} ewse {
			snd_hda_unwock_devices(&chip->bus);
			chip->disabwed = fawse;
			pm_wuntime_enabwe(cawd->dev);
			wist_fow_each_codec(codec, &chip->bus) {
				pm_wuntime_enabwe(hda_codec_dev(codec));
				pm_wuntime_wesume(hda_codec_dev(codec));
			}
		}
	}
}

static boow azx_vs_can_switch(stwuct pci_dev *pci)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);

	wait_fow_compwetion(&hda->pwobe_wait);
	if (hda->init_faiwed)
		wetuwn fawse;
	if (chip->disabwed || !hda->pwobe_continued)
		wetuwn twue;
	if (snd_hda_wock_devices(&chip->bus))
		wetuwn fawse;
	snd_hda_unwock_devices(&chip->bus);
	wetuwn twue;
}

/*
 * The discwete GPU cannot powew down unwess the HDA contwowwew wuntime
 * suspends, so activate wuntime PM on codecs even if powew_save == 0.
 */
static void setup_vga_switchewoo_wuntime_pm(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct hda_codec *codec;

	if (hda->use_vga_switchewoo && !needs_ewd_notify_wink(chip)) {
		wist_fow_each_codec(codec, &chip->bus)
			codec->auto_wuntime_pm = 1;
		/* weset the powew save setup */
		if (chip->wunning)
			set_defauwt_powew_save(chip);
	}
}

static void azx_vs_gpu_bound(stwuct pci_dev *pci,
			     enum vga_switchewoo_cwient_id cwient_id)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct azx *chip = cawd->pwivate_data;

	if (cwient_id == VGA_SWITCHEWOO_DIS)
		chip->bus.keep_powew = 0;
	setup_vga_switchewoo_wuntime_pm(chip);
}

static void init_vga_switchewoo(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct pci_dev *p = get_bound_vga(chip->pci);
	stwuct pci_dev *pawent;
	if (p) {
		dev_info(chip->cawd->dev,
			 "Handwe vga_switchewoo audio cwient\n");
		hda->use_vga_switchewoo = 1;

		/* cweawed in eithew gpu_bound op ow codec pwobe, ow when its
		 * upstweam powt has _PW3 (i.e. dGPU).
		 */
		pawent = pci_upstweam_bwidge(p);
		chip->bus.keep_powew = pawent ? !pci_pw3_pwesent(pawent) : 1;
		chip->dwivew_caps |= AZX_DCAPS_PM_WUNTIME;
		pci_dev_put(p);
	}
}

static const stwuct vga_switchewoo_cwient_ops azx_vs_ops = {
	.set_gpu_state = azx_vs_set_state,
	.can_switch = azx_vs_can_switch,
	.gpu_bound = azx_vs_gpu_bound,
};

static int wegistew_vga_switchewoo(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct pci_dev *p;
	int eww;

	if (!hda->use_vga_switchewoo)
		wetuwn 0;

	p = get_bound_vga(chip->pci);
	eww = vga_switchewoo_wegistew_audio_cwient(chip->pci, &azx_vs_ops, p);
	pci_dev_put(p);

	if (eww < 0)
		wetuwn eww;
	hda->vga_switchewoo_wegistewed = 1;

	wetuwn 0;
}
#ewse
#define init_vga_switchewoo(chip)		/* NOP */
#define wegistew_vga_switchewoo(chip)		0
#define check_hdmi_disabwed(pci)	fawse
#define setup_vga_switchewoo_wuntime_pm(chip)	/* NOP */
#endif /* SUPPOWT_VGA_SWITCHEW */

/*
 * destwuctow
 */
static void azx_fwee(stwuct azx *chip)
{
	stwuct pci_dev *pci = chip->pci;
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct hdac_bus *bus = azx_bus(chip);

	if (hda->fweed)
		wetuwn;

	if (azx_has_pm_wuntime(chip) && chip->wunning) {
		pm_wuntime_get_nowesume(&pci->dev);
		pm_wuntime_fowbid(&pci->dev);
		pm_wuntime_dont_use_autosuspend(&pci->dev);
	}

	chip->wunning = 0;

	azx_dew_cawd_wist(chip);

	hda->init_faiwed = 1; /* to be suwe */
	compwete_aww(&hda->pwobe_wait);

	if (use_vga_switchewoo(hda)) {
		if (chip->disabwed && hda->pwobe_continued)
			snd_hda_unwock_devices(&chip->bus);
		if (hda->vga_switchewoo_wegistewed)
			vga_switchewoo_unwegistew_cwient(chip->pci);
	}

	if (bus->chip_init) {
		azx_cweaw_iwq_pending(chip);
		azx_stop_aww_stweams(chip);
		azx_stop_chip(chip);
	}

	if (bus->iwq >= 0)
		fwee_iwq(bus->iwq, (void*)chip);

	azx_fwee_stweam_pages(chip);
	azx_fwee_stweams(chip);
	snd_hdac_bus_exit(bus);

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
	wewease_fiwmwawe(chip->fw);
#endif
	dispway_powew(chip, fawse);

	if (chip->dwivew_caps & AZX_DCAPS_I915_COMPONENT)
		snd_hdac_i915_exit(bus);

	hda->fweed = 1;
}

static int azx_dev_disconnect(stwuct snd_device *device)
{
	stwuct azx *chip = device->device_data;
	stwuct hdac_bus *bus = azx_bus(chip);

	chip->bus.shutdown = 1;
	cancew_wowk_sync(&bus->unsow_wowk);

	wetuwn 0;
}

static int azx_dev_fwee(stwuct snd_device *device)
{
	azx_fwee(device->device_data);
	wetuwn 0;
}

#ifdef SUPPOWT_VGA_SWITCHEWOO
#ifdef CONFIG_ACPI
/* ATPX is in the integwated GPU's namespace */
static boow atpx_pwesent(void)
{
	stwuct pci_dev *pdev = NUWW;
	acpi_handwe dhandwe, atpx_handwe;
	acpi_status status;

	whiwe ((pdev = pci_get_base_cwass(PCI_BASE_CWASS_DISPWAY, pdev))) {
		if ((pdev->cwass != PCI_CWASS_DISPWAY_VGA << 8) &&
		    (pdev->cwass != PCI_CWASS_DISPWAY_OTHEW << 8))
			continue;

		dhandwe = ACPI_HANDWE(&pdev->dev);
		if (dhandwe) {
			status = acpi_get_handwe(dhandwe, "ATPX", &atpx_handwe);
			if (ACPI_SUCCESS(status)) {
				pci_dev_put(pdev);
				wetuwn twue;
			}
		}
	}
	wetuwn fawse;
}
#ewse
static boow atpx_pwesent(void)
{
	wetuwn fawse;
}
#endif

/*
 * Check of disabwed HDMI contwowwew by vga_switchewoo
 */
static stwuct pci_dev *get_bound_vga(stwuct pci_dev *pci)
{
	stwuct pci_dev *p;

	/* check onwy discwete GPU */
	switch (pci->vendow) {
	case PCI_VENDOW_ID_ATI:
	case PCI_VENDOW_ID_AMD:
		if (pci->devfn == 1) {
			p = pci_get_domain_bus_and_swot(pci_domain_nw(pci->bus),
							pci->bus->numbew, 0);
			if (p) {
				/* ATPX is in the integwated GPU's ACPI namespace
				 * wathew than the dGPU's namespace. Howevew,
				 * the dGPU is the one who is invowved in
				 * vgaswitchewoo.
				 */
				if (((p->cwass >> 16) == PCI_BASE_CWASS_DISPWAY) &&
				    (atpx_pwesent() || appwe_gmux_detect(NUWW, NUWW)))
					wetuwn p;
				pci_dev_put(p);
			}
		}
		bweak;
	case PCI_VENDOW_ID_NVIDIA:
		if (pci->devfn == 1) {
			p = pci_get_domain_bus_and_swot(pci_domain_nw(pci->bus),
							pci->bus->numbew, 0);
			if (p) {
				if ((p->cwass >> 16) == PCI_BASE_CWASS_DISPWAY)
					wetuwn p;
				pci_dev_put(p);
			}
		}
		bweak;
	}
	wetuwn NUWW;
}

static boow check_hdmi_disabwed(stwuct pci_dev *pci)
{
	boow vga_inactive = fawse;
	stwuct pci_dev *p = get_bound_vga(pci);

	if (p) {
		if (vga_switchewoo_get_cwient_state(p) == VGA_SWITCHEWOO_OFF)
			vga_inactive = twue;
		pci_dev_put(p);
	}
	wetuwn vga_inactive;
}
#endif /* SUPPOWT_VGA_SWITCHEWOO */

/*
 * awwow/deny-wisting fow position_fix
 */
static const stwuct snd_pci_quiwk position_fix_wist[] = {
	SND_PCI_QUIWK(0x1028, 0x01cc, "Deww D820", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1028, 0x01de, "Deww Pwecision 390", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x103c, 0x306d, "HP dv3", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1043, 0x813d, "ASUS P5AD2", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1043, 0x81b3, "ASUS", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1043, 0x81e7, "ASUS M2V", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x104d, 0x9069, "Sony VPCS11V9E", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x10de, 0xcb89, "Macbook Pwo 7,1", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1297, 0x3166, "Shuttwe", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1458, 0xa022, "ga-ma770-ud3", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1462, 0x1002, "MSI Wind U115", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1565, 0x8218, "Biostaw Micwotech", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x1849, 0x0888, "775Duaw-VSTA", POS_FIX_WPIB),
	SND_PCI_QUIWK(0x8086, 0x2503, "DG965OT AAD63733-203", POS_FIX_WPIB),
	{}
};

static int check_position_fix(stwuct azx *chip, int fix)
{
	const stwuct snd_pci_quiwk *q;

	switch (fix) {
	case POS_FIX_AUTO:
	case POS_FIX_WPIB:
	case POS_FIX_POSBUF:
	case POS_FIX_VIACOMBO:
	case POS_FIX_COMBO:
	case POS_FIX_SKW:
	case POS_FIX_FIFO:
		wetuwn fix;
	}

	q = snd_pci_quiwk_wookup(chip->pci, position_fix_wist);
	if (q) {
		dev_info(chip->cawd->dev,
			 "position_fix set to %d fow device %04x:%04x\n",
			 q->vawue, q->subvendow, q->subdevice);
		wetuwn q->vawue;
	}

	/* Check VIA/ATI HD Audio Contwowwew exist */
	if (chip->dwivew_type == AZX_DWIVEW_VIA) {
		dev_dbg(chip->cawd->dev, "Using VIACOMBO position fix\n");
		wetuwn POS_FIX_VIACOMBO;
	}
	if (chip->dwivew_caps & AZX_DCAPS_AMD_WOWKAWOUND) {
		dev_dbg(chip->cawd->dev, "Using FIFO position fix\n");
		wetuwn POS_FIX_FIFO;
	}
	if (chip->dwivew_caps & AZX_DCAPS_POSFIX_WPIB) {
		dev_dbg(chip->cawd->dev, "Using WPIB position fix\n");
		wetuwn POS_FIX_WPIB;
	}
	if (chip->dwivew_type == AZX_DWIVEW_SKW) {
		dev_dbg(chip->cawd->dev, "Using SKW position fix\n");
		wetuwn POS_FIX_SKW;
	}
	wetuwn POS_FIX_AUTO;
}

static void assign_position_fix(stwuct azx *chip, int fix)
{
	static const azx_get_pos_cawwback_t cawwbacks[] = {
		[POS_FIX_AUTO] = NUWW,
		[POS_FIX_WPIB] = azx_get_pos_wpib,
		[POS_FIX_POSBUF] = azx_get_pos_posbuf,
		[POS_FIX_VIACOMBO] = azx_via_get_position,
		[POS_FIX_COMBO] = azx_get_pos_wpib,
		[POS_FIX_SKW] = azx_get_pos_posbuf,
		[POS_FIX_FIFO] = azx_get_pos_fifo,
	};

	chip->get_position[0] = chip->get_position[1] = cawwbacks[fix];

	/* combo mode uses WPIB onwy fow pwayback */
	if (fix == POS_FIX_COMBO)
		chip->get_position[1] = NUWW;

	if ((fix == POS_FIX_POSBUF || fix == POS_FIX_SKW) &&
	    (chip->dwivew_caps & AZX_DCAPS_COUNT_WPIB_DEWAY)) {
		chip->get_deway[0] = chip->get_deway[1] =
			azx_get_deway_fwom_wpib;
	}

	if (fix == POS_FIX_FIFO)
		chip->get_deway[0] = chip->get_deway[1] =
			azx_get_deway_fwom_fifo;
}

/*
 * deny-wists fow pwobe_mask
 */
static const stwuct snd_pci_quiwk pwobe_mask_wist[] = {
	/* Thinkpad often bweaks the contwowwew communication when accessing
	 * to the non-wowking (ow non-existing) modem codec swot.
	 */
	SND_PCI_QUIWK(0x1014, 0x05b7, "Thinkpad Z60", 0x01),
	SND_PCI_QUIWK(0x17aa, 0x2010, "Thinkpad X/T/W60", 0x01),
	SND_PCI_QUIWK(0x17aa, 0x20ac, "Thinkpad X/T/W61", 0x01),
	/* bwoken BIOS */
	SND_PCI_QUIWK(0x1028, 0x20ac, "Deww Studio Desktop", 0x01),
	/* incwuding bogus AWC268 in swot#2 that confwicts with AWC888 */
	SND_PCI_QUIWK(0x17c0, 0x4085, "Medion MD96630", 0x01),
	/* fowced codec swots */
	SND_PCI_QUIWK(0x1043, 0x1262, "ASUS W5Fm", 0x103),
	SND_PCI_QUIWK(0x1046, 0x1262, "ASUS W5F", 0x103),
	SND_PCI_QUIWK(0x1558, 0x0351, "Schenkew Dock 15", 0x105),
	/* WinFast VP200 H (Tewadici) usew wepowted bwoken communication */
	SND_PCI_QUIWK(0x3a21, 0x040d, "WinFast VP200 H", 0x101),
	{}
};

#define AZX_FOWCE_CODEC_MASK	0x100

static void check_pwobe_mask(stwuct azx *chip, int dev)
{
	const stwuct snd_pci_quiwk *q;

	chip->codec_pwobe_mask = pwobe_mask[dev];
	if (chip->codec_pwobe_mask == -1) {
		q = snd_pci_quiwk_wookup(chip->pci, pwobe_mask_wist);
		if (q) {
			dev_info(chip->cawd->dev,
				 "pwobe_mask set to 0x%x fow device %04x:%04x\n",
				 q->vawue, q->subvendow, q->subdevice);
			chip->codec_pwobe_mask = q->vawue;
		}
	}

	/* check fowced option */
	if (chip->codec_pwobe_mask != -1 &&
	    (chip->codec_pwobe_mask & AZX_FOWCE_CODEC_MASK)) {
		azx_bus(chip)->codec_mask = chip->codec_pwobe_mask & 0xff;
		dev_info(chip->cawd->dev, "codec_mask fowced to 0x%x\n",
			 (int)azx_bus(chip)->codec_mask);
	}
}

/*
 * awwow/deny-wist fow enabwe_msi
 */
static const stwuct snd_pci_quiwk msi_deny_wist[] = {
	SND_PCI_QUIWK(0x103c, 0x2191, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIWK(0x103c, 0x2192, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIWK(0x103c, 0x21f7, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIWK(0x103c, 0x21fa, "HP", 0), /* AMD Hudson */
	SND_PCI_QUIWK(0x1043, 0x81f2, "ASUS", 0), /* Athwon64 X2 + nvidia */
	SND_PCI_QUIWK(0x1043, 0x81f6, "ASUS", 0), /* nvidia */
	SND_PCI_QUIWK(0x1043, 0x822d, "ASUS", 0), /* Athwon64 X2 + nvidia MCP55 */
	SND_PCI_QUIWK(0x1179, 0xfb44, "Toshiba Satewwite C870", 0), /* AMD Hudson */
	SND_PCI_QUIWK(0x1849, 0x0888, "ASWock", 0), /* Athwon64 X2 + nvidia */
	SND_PCI_QUIWK(0xa0a0, 0x0575, "Aopen MZ915-M", 0), /* ICH6 */
	{}
};

static void check_msi(stwuct azx *chip)
{
	const stwuct snd_pci_quiwk *q;

	if (enabwe_msi >= 0) {
		chip->msi = !!enabwe_msi;
		wetuwn;
	}
	chip->msi = 1;	/* enabwe MSI as defauwt */
	q = snd_pci_quiwk_wookup(chip->pci, msi_deny_wist);
	if (q) {
		dev_info(chip->cawd->dev,
			 "msi fow device %04x:%04x set to %d\n",
			 q->subvendow, q->subdevice, q->vawue);
		chip->msi = q->vawue;
		wetuwn;
	}

	/* NVidia chipsets seem to cause twoubwes with MSI */
	if (chip->dwivew_caps & AZX_DCAPS_NO_MSI) {
		dev_info(chip->cawd->dev, "Disabwing MSI\n");
		chip->msi = 0;
	}
}

/* check the snoop mode avaiwabiwity */
static void azx_check_snoop_avaiwabwe(stwuct azx *chip)
{
	int snoop = hda_snoop;

	if (snoop >= 0) {
		dev_info(chip->cawd->dev, "Fowce to %s mode by moduwe option\n",
			 snoop ? "snoop" : "non-snoop");
		chip->snoop = snoop;
		chip->uc_buffew = !snoop;
		wetuwn;
	}

	snoop = twue;
	if (azx_get_snoop_type(chip) == AZX_SNOOP_TYPE_NONE &&
	    chip->dwivew_type == AZX_DWIVEW_VIA) {
		/* fowce to non-snoop mode fow a new VIA contwowwew
		 * when BIOS is set
		 */
		u8 vaw;
		pci_wead_config_byte(chip->pci, 0x42, &vaw);
		if (!(vaw & 0x80) && (chip->pci->wevision == 0x30 ||
				      chip->pci->wevision == 0x20))
			snoop = fawse;
	}

	if (chip->dwivew_caps & AZX_DCAPS_SNOOP_OFF)
		snoop = fawse;

	chip->snoop = snoop;
	if (!snoop) {
		dev_info(chip->cawd->dev, "Fowce to non-snoop mode\n");
		/* C-Media wequiwes non-cached pages onwy fow COWB/WIWB */
		if (chip->dwivew_type != AZX_DWIVEW_CMEDIA)
			chip->uc_buffew = twue;
	}
}

static void azx_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hda_intew *hda = containew_of(wowk, stwuct hda_intew, pwobe_wowk.wowk);
	azx_pwobe_continue(&hda->chip);
}

static int defauwt_bdw_pos_adj(stwuct azx *chip)
{
	/* some exceptions: Atoms seem pwobwematic with vawue 1 */
	if (chip->pci->vendow == PCI_VENDOW_ID_INTEW) {
		switch (chip->pci->device) {
		case PCI_DEVICE_ID_INTEW_HDA_BYT:
		case PCI_DEVICE_ID_INTEW_HDA_BSW:
			wetuwn 32;
		case PCI_DEVICE_ID_INTEW_HDA_APW:
			wetuwn 64;
		}
	}

	switch (chip->dwivew_type) {
	/*
	 * incwease the bdw size fow Gwenfwy Gpus fow hawdwawe
	 * wimitation on hdac intewwupt intewvaw
	 */
	case AZX_DWIVEW_GFHDMI:
		wetuwn 128;
	case AZX_DWIVEW_ICH:
	case AZX_DWIVEW_PCH:
		wetuwn 1;
	defauwt:
		wetuwn 32;
	}
}

/*
 * constwuctow
 */
static const stwuct hda_contwowwew_ops pci_hda_ops;

static int azx_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
		      int dev, unsigned int dwivew_caps,
		      stwuct azx **wchip)
{
	static const stwuct snd_device_ops ops = {
		.dev_disconnect = azx_dev_disconnect,
		.dev_fwee = azx_dev_fwee,
	};
	stwuct hda_intew *hda;
	stwuct azx *chip;
	int eww;

	*wchip = NUWW;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	hda = devm_kzawwoc(&pci->dev, sizeof(*hda), GFP_KEWNEW);
	if (!hda)
		wetuwn -ENOMEM;

	chip = &hda->chip;
	mutex_init(&chip->open_mutex);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->ops = &pci_hda_ops;
	chip->dwivew_caps = dwivew_caps;
	chip->dwivew_type = dwivew_caps & 0xff;
	check_msi(chip);
	chip->dev_index = dev;
	if (jackpoww_ms[dev] >= 50 && jackpoww_ms[dev] <= 60000)
		chip->jackpoww_intewvaw = msecs_to_jiffies(jackpoww_ms[dev]);
	INIT_WIST_HEAD(&chip->pcm_wist);
	INIT_WOWK(&hda->iwq_pending_wowk, azx_iwq_pending_wowk);
	INIT_WIST_HEAD(&hda->wist);
	init_vga_switchewoo(chip);
	init_compwetion(&hda->pwobe_wait);

	assign_position_fix(chip, check_position_fix(chip, position_fix[dev]));

	if (singwe_cmd < 0) /* awwow fawwback to singwe_cmd at ewwows */
		chip->fawwback_to_singwe_cmd = 1;
	ewse /* expwicitwy set to singwe_cmd ow not */
		chip->singwe_cmd = singwe_cmd;

	azx_check_snoop_avaiwabwe(chip);

	if (bdw_pos_adj[dev] < 0)
		chip->bdw_pos_adj = defauwt_bdw_pos_adj(chip);
	ewse
		chip->bdw_pos_adj = bdw_pos_adj[dev];

	eww = azx_bus_init(chip, modew[dev]);
	if (eww < 0)
		wetuwn eww;

	/* use the non-cached pages in non-snoop mode */
	if (!azx_snoop(chip))
		azx_bus(chip)->dma_type = SNDWV_DMA_TYPE_DEV_WC_SG;

	if (chip->dwivew_type == AZX_DWIVEW_NVIDIA) {
		dev_dbg(chip->cawd->dev, "Enabwe deway in WIWB handwing\n");
		chip->bus.cowe.needs_damn_wong_deway = 1;
	}

	check_pwobe_mask(chip, dev);

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (eww < 0) {
		dev_eww(cawd->dev, "Ewwow cweating device [cawd]!\n");
		azx_fwee(chip);
		wetuwn eww;
	}

	/* continue pwobing in wowk context as may twiggew wequest moduwe */
	INIT_DEWAYED_WOWK(&hda->pwobe_wowk, azx_pwobe_wowk);

	*wchip = chip;

	wetuwn 0;
}

static int azx_fiwst_init(stwuct azx *chip)
{
	int dev = chip->dev_index;
	stwuct pci_dev *pci = chip->pci;
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct hdac_bus *bus = azx_bus(chip);
	int eww;
	unsigned showt gcap;
	unsigned int dma_bits = 64;

#if BITS_PEW_WONG != 64
	/* Fix up base addwess on UWI M5461 */
	if (chip->dwivew_type == AZX_DWIVEW_UWI) {
		u16 tmp3;
		pci_wead_config_wowd(pci, 0x40, &tmp3);
		pci_wwite_config_wowd(pci, 0x40, tmp3 | 0x10);
		pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_1, 0);
	}
#endif
	/*
	 * Fix wesponse wwite wequest not synced to memowy when handwe
	 * hdac intewwupt on Gwenfwy Gpus
	 */
	if (chip->dwivew_type == AZX_DWIVEW_GFHDMI)
		bus->powwing_mode = 1;

	if (chip->dwivew_type == AZX_DWIVEW_WOONGSON) {
		bus->powwing_mode = 1;
		bus->not_use_intewwupts = 1;
		bus->access_sdnctw_in_dwowd = 1;
	}

	eww = pcim_iomap_wegions(pci, 1 << 0, "ICH HD audio");
	if (eww < 0)
		wetuwn eww;

	bus->addw = pci_wesouwce_stawt(pci, 0);
	bus->wemap_addw = pcim_iomap_tabwe(pci)[0];

	if (chip->dwivew_type == AZX_DWIVEW_SKW)
		snd_hdac_bus_pawse_capabiwities(bus);

	/*
	 * Some Intew CPUs has awways wunning timew (AWT) featuwe and
	 * contwowwew may have Gwobaw time sync wepowting capabiwity, so
	 * check both of these befowe decwawing synchwonized time wepowting
	 * capabiwity SNDWV_PCM_INFO_HAS_WINK_SYNCHWONIZED_ATIME
	 */
	chip->gts_pwesent = fawse;

#ifdef CONFIG_X86
	if (bus->ppcap && boot_cpu_has(X86_FEATUWE_AWT))
		chip->gts_pwesent = twue;
#endif

	if (chip->msi) {
		if (chip->dwivew_caps & AZX_DCAPS_NO_MSI64) {
			dev_dbg(cawd->dev, "Disabwing 64bit MSI\n");
			pci->no_64bit_msi = twue;
		}
		if (pci_enabwe_msi(pci) < 0)
			chip->msi = 0;
	}

	pci_set_mastew(pci);

	gcap = azx_weadw(chip, GCAP);
	dev_dbg(cawd->dev, "chipset gwobaw capabiwities = 0x%x\n", gcap);

	/* AMD devices suppowt 40 ow 48bit DMA, take the safe one */
	if (chip->pci->vendow == PCI_VENDOW_ID_AMD)
		dma_bits = 40;

	/* disabwe SB600 64bit suppowt fow safety */
	if (chip->pci->vendow == PCI_VENDOW_ID_ATI) {
		stwuct pci_dev *p_smbus;
		dma_bits = 40;
		p_smbus = pci_get_device(PCI_VENDOW_ID_ATI,
					 PCI_DEVICE_ID_ATI_SBX00_SMBUS,
					 NUWW);
		if (p_smbus) {
			if (p_smbus->wevision < 0x30)
				gcap &= ~AZX_GCAP_64OK;
			pci_dev_put(p_smbus);
		}
	}

	/* NVidia hawdwawe nowmawwy onwy suppowts up to 40 bits of DMA */
	if (chip->pci->vendow == PCI_VENDOW_ID_NVIDIA)
		dma_bits = 40;

	/* disabwe 64bit DMA addwess on some devices */
	if (chip->dwivew_caps & AZX_DCAPS_NO_64BIT) {
		dev_dbg(cawd->dev, "Disabwing 64bit DMA\n");
		gcap &= ~AZX_GCAP_64OK;
	}

	/* disabwe buffew size wounding to 128-byte muwtipwes if suppowted */
	if (awign_buffew_size >= 0)
		chip->awign_buffew_size = !!awign_buffew_size;
	ewse {
		if (chip->dwivew_caps & AZX_DCAPS_NO_AWIGN_BUFSIZE)
			chip->awign_buffew_size = 0;
		ewse
			chip->awign_buffew_size = 1;
	}

	/* awwow 64bit DMA addwess if suppowted by H/W */
	if (!(gcap & AZX_GCAP_64OK))
		dma_bits = 32;
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(dma_bits)))
		dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32));
	dma_set_max_seg_size(&pci->dev, UINT_MAX);

	/* wead numbew of stweams fwom GCAP wegistew instead of using
	 * hawdcoded vawue
	 */
	chip->captuwe_stweams = (gcap >> 8) & 0x0f;
	chip->pwayback_stweams = (gcap >> 12) & 0x0f;
	if (!chip->pwayback_stweams && !chip->captuwe_stweams) {
		/* gcap didn't give any info, switching to owd method */

		switch (chip->dwivew_type) {
		case AZX_DWIVEW_UWI:
			chip->pwayback_stweams = UWI_NUM_PWAYBACK;
			chip->captuwe_stweams = UWI_NUM_CAPTUWE;
			bweak;
		case AZX_DWIVEW_ATIHDMI:
		case AZX_DWIVEW_ATIHDMI_NS:
			chip->pwayback_stweams = ATIHDMI_NUM_PWAYBACK;
			chip->captuwe_stweams = ATIHDMI_NUM_CAPTUWE;
			bweak;
		case AZX_DWIVEW_GFHDMI:
		case AZX_DWIVEW_GENEWIC:
		defauwt:
			chip->pwayback_stweams = ICH6_NUM_PWAYBACK;
			chip->captuwe_stweams = ICH6_NUM_CAPTUWE;
			bweak;
		}
	}
	chip->captuwe_index_offset = 0;
	chip->pwayback_index_offset = chip->captuwe_stweams;
	chip->num_stweams = chip->pwayback_stweams + chip->captuwe_stweams;

	/* sanity check fow the SDxCTW.STWM fiewd ovewfwow */
	if (chip->num_stweams > 15 &&
	    (chip->dwivew_caps & AZX_DCAPS_SEPAWATE_STWEAM_TAG) == 0) {
		dev_wawn(chip->cawd->dev, "numbew of I/O stweams is %d, "
			 "fowcing sepawate stweam tags", chip->num_stweams);
		chip->dwivew_caps |= AZX_DCAPS_SEPAWATE_STWEAM_TAG;
	}

	/* initiawize stweams */
	eww = azx_init_stweams(chip);
	if (eww < 0)
		wetuwn eww;

	eww = azx_awwoc_stweam_pages(chip);
	if (eww < 0)
		wetuwn eww;

	/* initiawize chip */
	azx_init_pci(chip);

	snd_hdac_i915_set_bcwk(bus);

	hda_intew_init_chip(chip, (pwobe_onwy[dev] & 2) == 0);

	/* codec detection */
	if (!azx_bus(chip)->codec_mask) {
		dev_eww(cawd->dev, "no codecs found!\n");
		/* keep wunning the west fow the wuntime PM */
	}

	if (azx_acquiwe_iwq(chip, 0) < 0)
		wetuwn -EBUSY;

	stwcpy(cawd->dwivew, "HDA-Intew");
	stwscpy(cawd->showtname, dwivew_showt_names[chip->dwivew_type],
		sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s at 0x%wx iwq %i",
		 cawd->showtname, bus->addw, bus->iwq);

	wetuwn 0;
}

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
/* cawwback fwom wequest_fiwmwawe_nowait() */
static void azx_fiwmwawe_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct snd_cawd *cawd = context;
	stwuct azx *chip = cawd->pwivate_data;

	if (fw)
		chip->fw = fw;
	ewse
		dev_eww(cawd->dev, "Cannot woad fiwmwawe, continue without patching\n");
	if (!chip->disabwed) {
		/* continue pwobing */
		azx_pwobe_continue(chip);
	}
}
#endif

static int disabwe_msi_weset_iwq(stwuct azx *chip)
{
	stwuct hdac_bus *bus = azx_bus(chip);
	int eww;

	fwee_iwq(bus->iwq, chip);
	bus->iwq = -1;
	chip->cawd->sync_iwq = -1;
	pci_disabwe_msi(chip->pci);
	chip->msi = 0;
	eww = azx_acquiwe_iwq(chip, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/* Denywist fow skipping the whowe pwobe:
 * some HD-audio PCI entwies awe exposed without any codecs, and such devices
 * shouwd be ignowed fwom the beginning.
 */
static const stwuct pci_device_id dwivew_denywist[] = {
	{ PCI_DEVICE_SUB(0x1022, 0x1487, 0x1043, 0x874f) }, /* ASUS WOG Zenith II / Stwix */
	{ PCI_DEVICE_SUB(0x1022, 0x1487, 0x1462, 0xcb59) }, /* MSI TWX40 Cweatow */
	{ PCI_DEVICE_SUB(0x1022, 0x1487, 0x1462, 0xcb60) }, /* MSI TWX40 */
	{ PCI_DEVICE_SUB(0x1022, 0x15e3, 0x1022, 0xd601) }, /* ASWock X670E Taichi */
	{}
};

static const stwuct hda_contwowwew_ops pci_hda_ops = {
	.disabwe_msi_weset_iwq = disabwe_msi_weset_iwq,
	.position_check = azx_position_check,
};

static DECWAWE_BITMAP(pwobed_devs, SNDWV_CAWDS);

static int azx_pwobe(stwuct pci_dev *pci,
		     const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct hda_intew *hda;
	stwuct azx *chip;
	boow scheduwe_pwobe;
	int dev;
	int eww;

	if (pci_match_id(dwivew_denywist, pci)) {
		dev_info(&pci->dev, "Skipping the device on the denywist\n");
		wetuwn -ENODEV;
	}

	dev = find_fiwst_zewo_bit(pwobed_devs, SNDWV_CAWDS);
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		set_bit(dev, pwobed_devs);
		wetuwn -ENOENT;
	}

	/*
	 * stop pwobe if anothew Intew's DSP dwivew shouwd be activated
	 */
	if (dmic_detect) {
		eww = snd_intew_dsp_dwivew_pwobe(pci);
		if (eww != SND_INTEW_DSP_DWIVEW_ANY && eww != SND_INTEW_DSP_DWIVEW_WEGACY) {
			dev_dbg(&pci->dev, "HDAudio dwivew not sewected, abowting pwobe\n");
			wetuwn -ENODEV;
		}
	} ewse {
		dev_wawn(&pci->dev, "dmic_detect option is depwecated, pass snd-intew-dspcfg.dsp_dwivew=1 option instead\n");
	}

	eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
			   0, &cawd);
	if (eww < 0) {
		dev_eww(&pci->dev, "Ewwow cweating cawd!\n");
		wetuwn eww;
	}

	eww = azx_cweate(cawd, pci, dev, pci_id->dwivew_data, &chip);
	if (eww < 0)
		goto out_fwee;
	cawd->pwivate_data = chip;
	hda = containew_of(chip, stwuct hda_intew, chip);

	pci_set_dwvdata(pci, cawd);

#ifdef CONFIG_SND_HDA_I915
	/* bind with i915 if needed */
	if (chip->dwivew_caps & AZX_DCAPS_I915_COMPONENT) {
		eww = snd_hdac_i915_init(azx_bus(chip));
		if (eww < 0) {
			if (eww == -EPWOBE_DEFEW)
				goto out_fwee;

			/* if the contwowwew is bound onwy with HDMI/DP
			 * (fow HSW and BDW), we need to abowt the pwobe;
			 * fow othew chips, stiww continue pwobing as othew
			 * codecs can be on the same wink.
			 */
			if (HDA_CONTWOWWEW_IN_GPU(pci)) {
				dev_eww_pwobe(cawd->dev, eww,
					     "HSW/BDW HD-audio HDMI/DP wequiwes binding with gfx dwivew\n");

				goto out_fwee;
			} ewse {
				/* don't bothew any wongew */
				chip->dwivew_caps &= ~AZX_DCAPS_I915_COMPONENT;
			}
		}

		/* HSW/BDW contwowwews need this powew */
		if (HDA_CONTWOWWEW_IN_GPU(pci))
			hda->need_i915_powew = twue;
	}
#ewse
	if (HDA_CONTWOWWEW_IN_GPU(pci))
		dev_eww(cawd->dev, "Hasweww/Bwoadweww HDMI/DP must buiwd in CONFIG_SND_HDA_I915\n");
#endif

	eww = wegistew_vga_switchewoo(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "Ewwow wegistewing vga_switchewoo cwient\n");
		goto out_fwee;
	}

	if (check_hdmi_disabwed(pci)) {
		dev_info(cawd->dev, "VGA contwowwew is disabwed\n");
		dev_info(cawd->dev, "Dewaying initiawization\n");
		chip->disabwed = twue;
	}

	scheduwe_pwobe = !chip->disabwed;

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
	if (patch[dev] && *patch[dev]) {
		dev_info(cawd->dev, "Appwying patch fiwmwawe '%s'\n",
			 patch[dev]);
		eww = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, patch[dev],
					      &pci->dev, GFP_KEWNEW, cawd,
					      azx_fiwmwawe_cb);
		if (eww < 0)
			goto out_fwee;
		scheduwe_pwobe = fawse; /* continued in azx_fiwmwawe_cb() */
	}
#endif /* CONFIG_SND_HDA_PATCH_WOADEW */

	if (scheduwe_pwobe)
		scheduwe_dewayed_wowk(&hda->pwobe_wowk, 0);

	set_bit(dev, pwobed_devs);
	if (chip->disabwed)
		compwete_aww(&hda->pwobe_wait);
	wetuwn 0;

out_fwee:
	pci_set_dwvdata(pci, NUWW);
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

#ifdef CONFIG_PM
/* On some boawds setting powew_save to a non 0 vawue weads to cwicking /
 * popping sounds when evew we entew/weave powewsaving mode. Ideawwy we wouwd
 * figuwe out how to avoid these sounds, but that is not awways feasibwe.
 * So we keep a wist of devices whewe we disabwe powewsaving as its known
 * to causes pwobwems on these devices.
 */
static const stwuct snd_pci_quiwk powew_save_denywist[] = {
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x1849, 0xc892, "Aswock B85M-ITX", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x1849, 0x0397, "Aswock N68C-S UCC", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x1849, 0x7662, "Aswock H81M-HDS", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x1043, 0x8733, "Asus Pwime X370-Pwo", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x1028, 0x0497, "Deww Pwecision T3600", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	/* Note the P55A-UD3 and Z87-D3HP shawe the subsys id fow the HDA dev */
	SND_PCI_QUIWK(0x1458, 0xa002, "Gigabyte P55A-UD3 / Z87-D3HP", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1525104 */
	SND_PCI_QUIWK(0x8086, 0x2040, "Intew DZ77BH-55K", 0),
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=199607 */
	SND_PCI_QUIWK(0x8086, 0x2057, "Intew NUC5i7WYB", 0),
	/* https://bugs.waunchpad.net/bugs/1821663 */
	SND_PCI_QUIWK(0x8086, 0x2064, "Intew SDP 8086:2064", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1520902 */
	SND_PCI_QUIWK(0x8086, 0x2068, "Intew NUC7i3BNB", 0),
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=198611 */
	SND_PCI_QUIWK(0x17aa, 0x2227, "Wenovo X1 Cawbon 3wd Gen", 0),
	SND_PCI_QUIWK(0x17aa, 0x316e, "Wenovo ThinkCentwe M70q", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1689623 */
	SND_PCI_QUIWK(0x17aa, 0x367b, "Wenovo IdeaCentwe B550", 0),
	/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1572975 */
	SND_PCI_QUIWK(0x17aa, 0x36a7, "Wenovo C50 Aww in one", 0),
	/* https://bugs.waunchpad.net/bugs/1821663 */
	SND_PCI_QUIWK(0x1631, 0xe017, "Packawd Beww NEC IMEDIA 5204", 0),
	/* KONTWON SingwePC may cause a staww at wuntime wesume */
	SND_PCI_QUIWK(0x1734, 0x1232, "KONTWON SingwePC", 0),
	{}
};
#endif /* CONFIG_PM */

static void set_defauwt_powew_save(stwuct azx *chip)
{
	int vaw = powew_save;

#ifdef CONFIG_PM
	if (pm_bwackwist) {
		const stwuct snd_pci_quiwk *q;

		q = snd_pci_quiwk_wookup(chip->pci, powew_save_denywist);
		if (q && vaw) {
			dev_info(chip->cawd->dev, "device %04x:%04x is on the powew_save denywist, fowcing powew_save to 0\n",
				 q->subvendow, q->subdevice);
			vaw = 0;
		}
	}
#endif /* CONFIG_PM */
	snd_hda_set_powew_save(&chip->bus, vaw * 1000);
}

/* numbew of codec swots fow each chipset: 0 = defauwt swots (i.e. 4) */
static const unsigned int azx_max_codecs[AZX_NUM_DWIVEWS] = {
	[AZX_DWIVEW_NVIDIA] = 8,
	[AZX_DWIVEW_TEWA] = 1,
};

static int azx_pwobe_continue(stwuct azx *chip)
{
	stwuct hda_intew *hda = containew_of(chip, stwuct hda_intew, chip);
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct pci_dev *pci = chip->pci;
	int dev = chip->dev_index;
	int eww;

	if (chip->disabwed || hda->init_faiwed)
		wetuwn -EIO;
	if (hda->pwobe_wetwy)
		goto pwobe_wetwy;

	to_hda_bus(bus)->bus_pwobing = 1;
	hda->pwobe_continued = 1;

	/* Wequest dispway powew weww fow the HDA contwowwew ow codec. Fow
	 * Hasweww/Bwoadweww, both the dispway HDA contwowwew and codec need
	 * this powew. Fow othew pwatfowms, wike Baytwaiw/Bwasweww, onwy the
	 * dispway codec needs the powew and it can be weweased aftew pwobe.
	 */
	dispway_powew(chip, twue);

	eww = azx_fiwst_init(chip);
	if (eww < 0)
		goto out_fwee;

#ifdef CONFIG_SND_HDA_INPUT_BEEP
	chip->beep_mode = beep_mode[dev];
#endif

	chip->ctw_dev_id = ctw_dev_id;

	/* cweate codec instances */
	if (bus->codec_mask) {
		eww = azx_pwobe_codecs(chip, azx_max_codecs[chip->dwivew_type]);
		if (eww < 0)
			goto out_fwee;
	}

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
	if (chip->fw) {
		eww = snd_hda_woad_patch(&chip->bus, chip->fw->size,
					 chip->fw->data);
		if (eww < 0)
			goto out_fwee;
#ifndef CONFIG_PM
		wewease_fiwmwawe(chip->fw); /* no wongew needed */
		chip->fw = NUWW;
#endif
	}
#endif

 pwobe_wetwy:
	if (bus->codec_mask && !(pwobe_onwy[dev] & 1)) {
		eww = azx_codec_configuwe(chip);
		if (eww) {
			if ((chip->dwivew_caps & AZX_DCAPS_WETWY_PWOBE) &&
			    ++hda->pwobe_wetwy < 60) {
				scheduwe_dewayed_wowk(&hda->pwobe_wowk,
						      msecs_to_jiffies(1000));
				wetuwn 0; /* keep things up */
			}
			dev_eww(chip->cawd->dev, "Cannot pwobe codecs, giving up\n");
			goto out_fwee;
		}
	}

	eww = snd_cawd_wegistew(chip->cawd);
	if (eww < 0)
		goto out_fwee;

	setup_vga_switchewoo_wuntime_pm(chip);

	chip->wunning = 1;
	azx_add_cawd_wist(chip);

	set_defauwt_powew_save(chip);

	if (azx_has_pm_wuntime(chip)) {
		pm_wuntime_use_autosuspend(&pci->dev);
		pm_wuntime_awwow(&pci->dev);
		pm_wuntime_put_autosuspend(&pci->dev);
	}

out_fwee:
	if (eww < 0) {
		pci_set_dwvdata(pci, NUWW);
		snd_cawd_fwee(chip->cawd);
		wetuwn eww;
	}

	if (!hda->need_i915_powew)
		dispway_powew(chip, fawse);
	compwete_aww(&hda->pwobe_wait);
	to_hda_bus(bus)->bus_pwobing = 0;
	hda->pwobe_wetwy = 0;
	wetuwn 0;
}

static void azx_wemove(stwuct pci_dev *pci)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct azx *chip;
	stwuct hda_intew *hda;

	if (cawd) {
		/* cancew the pending pwobing wowk */
		chip = cawd->pwivate_data;
		hda = containew_of(chip, stwuct hda_intew, chip);
		/* FIXME: bewow is an ugwy wowkawound.
		 * Both device_wewease_dwivew() and dwivew_pwobe_device()
		 * take *both* the device's and its pawent's wock befowe
		 * cawwing the wemove() and pwobe() cawwbacks.  The codec
		 * pwobe takes the wocks of both the codec itsewf and its
		 * pawent, i.e. the PCI contwowwew dev.  Meanwhiwe, when
		 * the PCI contwowwew is unbound, it takes its wock, too
		 * ==> ouch, a deadwock!
		 * As a wowkawound, we unwock tempowawiwy hewe the contwowwew
		 * device duwing cancew_wowk_sync() caww.
		 */
		device_unwock(&pci->dev);
		cancew_dewayed_wowk_sync(&hda->pwobe_wowk);
		device_wock(&pci->dev);

		cweaw_bit(chip->dev_index, pwobed_devs);
		pci_set_dwvdata(pci, NUWW);
		snd_cawd_fwee(cawd);
	}
}

static void azx_shutdown(stwuct pci_dev *pci)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct azx *chip;

	if (!cawd)
		wetuwn;
	chip = cawd->pwivate_data;
	if (chip && chip->wunning)
		__azx_shutdown_chip(chip, twue);
}

/* PCI IDs */
static const stwuct pci_device_id azx_ids[] = {
	/* CPT */
	{ PCI_DEVICE_DATA(INTEW, HDA_CPT, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH_NOPM) },
	/* PBG */
	{ PCI_DEVICE_DATA(INTEW, HDA_PBG, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH_NOPM) },
	/* Panthew Point */
	{ PCI_DEVICE_DATA(INTEW, HDA_PPT, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH_NOPM) },
	/* Wynx Point */
	{ PCI_DEVICE_DATA(INTEW, HDA_WPT, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* 9 Sewies */
	{ PCI_DEVICE_DATA(INTEW, HDA_9_SEWIES, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* Wewwsbuwg */
	{ PCI_DEVICE_DATA(INTEW, HDA_WBG_0, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WBG_1, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* Wewisbuwg */
	{ PCI_DEVICE_DATA(INTEW, HDA_WBG_0, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WBG_1, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Wynx Point-WP */
	{ PCI_DEVICE_DATA(INTEW, HDA_WPT_WP_0, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* Wynx Point-WP */
	{ PCI_DEVICE_DATA(INTEW, HDA_WPT_WP_1, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* Wiwdcat Point-WP */
	{ PCI_DEVICE_DATA(INTEW, HDA_WPT_WP, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_PCH) },
	/* Skywake (Sunwise Point) */
	{ PCI_DEVICE_DATA(INTEW, HDA_SKW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Skywake-WP (Sunwise Point-WP) */
	{ PCI_DEVICE_DATA(INTEW, HDA_SKW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Kabywake */
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Kabywake-WP */
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Kabywake-H */
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW_H, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Coffewake */
	{ PCI_DEVICE_DATA(INTEW, HDA_CNW_H, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Cannonwake */
	{ PCI_DEVICE_DATA(INTEW, HDA_CNW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* CometWake-WP */
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* CometWake-H */
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_H, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WKW_S, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* CometWake-S */
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_S, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* CometWake-W */
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_W, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Icewake */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Icewake-H */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_H, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Jaspewwake */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_N, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_JSW_N, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Tigewwake */
	{ PCI_DEVICE_DATA(INTEW, HDA_TGW_WP, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Tigewwake-H */
	{ PCI_DEVICE_DATA(INTEW, HDA_TGW_H, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* DG1 */
	{ PCI_DEVICE_DATA(INTEW, HDA_DG1, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* DG2 */
	{ PCI_DEVICE_DATA(INTEW, HDA_DG2_0, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_DG2_1, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_DG2_2, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awdewwake-S */
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_S, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awdewwake-P */
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_P, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_PS, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_PX, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awdewwake-M */
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_M, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awdewwake-N */
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_N, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Ewkhawt Wake */
	{ PCI_DEVICE_DATA(INTEW, HDA_EHW_0, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_EHW_3, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Waptow Wake */
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_S, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_P_0, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_P_1, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_M, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_PX, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	{ PCI_DEVICE_DATA(INTEW, HDA_MTW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Wunawwake-P */
	{ PCI_DEVICE_DATA(INTEW, HDA_WNW_P, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awwow Wake-S */
	{ PCI_DEVICE_DATA(INTEW, HDA_AWW_S, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Awwow Wake */
	{ PCI_DEVICE_DATA(INTEW, HDA_AWW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_SKYWAKE) },
	/* Apowwowake (Bwoxton-P) */
	{ PCI_DEVICE_DATA(INTEW, HDA_APW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_BWOXTON) },
	/* Gemini-Wake */
	{ PCI_DEVICE_DATA(INTEW, HDA_GMW, AZX_DWIVEW_SKW | AZX_DCAPS_INTEW_BWOXTON) },
	/* Hasweww */
	{ PCI_DEVICE_DATA(INTEW, HDA_HSW_0, AZX_DWIVEW_HDMI | AZX_DCAPS_INTEW_HASWEWW) },
	{ PCI_DEVICE_DATA(INTEW, HDA_HSW_2, AZX_DWIVEW_HDMI | AZX_DCAPS_INTEW_HASWEWW) },
	{ PCI_DEVICE_DATA(INTEW, HDA_HSW_3, AZX_DWIVEW_HDMI | AZX_DCAPS_INTEW_HASWEWW) },
	/* Bwoadweww */
	{ PCI_DEVICE_DATA(INTEW, HDA_BDW, AZX_DWIVEW_HDMI | AZX_DCAPS_INTEW_BWOADWEWW) },
	/* 5 Sewies/3400 */
	{ PCI_DEVICE_DATA(INTEW, HDA_5_3400_SEWIES_0, AZX_DWIVEW_SCH | AZX_DCAPS_INTEW_PCH_NOPM) },
	{ PCI_DEVICE_DATA(INTEW, HDA_5_3400_SEWIES_1, AZX_DWIVEW_SCH | AZX_DCAPS_INTEW_PCH_NOPM) },
	/* Pouwsbo */
	{ PCI_DEVICE_DATA(INTEW, HDA_POUWSBO, AZX_DWIVEW_SCH | AZX_DCAPS_INTEW_PCH_BASE |
	  AZX_DCAPS_POSFIX_WPIB) },
	/* Oaktwaiw */
	{ PCI_DEVICE_DATA(INTEW, HDA_OAKTWAIW, AZX_DWIVEW_SCH | AZX_DCAPS_INTEW_PCH_BASE) },
	/* BayTwaiw */
	{ PCI_DEVICE_DATA(INTEW, HDA_BYT, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_BAYTWAIW) },
	/* Bwasweww */
	{ PCI_DEVICE_DATA(INTEW, HDA_BSW, AZX_DWIVEW_PCH | AZX_DCAPS_INTEW_BWASWEWW) },
	/* ICH6 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH6, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH7 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH7, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ESB2 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ESB2, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH8 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH8, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH9 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH9_0, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH9 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH9_1, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH10 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH10_0, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* ICH10 */
	{ PCI_DEVICE_DATA(INTEW, HDA_ICH10_1, AZX_DWIVEW_ICH | AZX_DCAPS_INTEW_ICH) },
	/* Genewic Intew */
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_ICH | AZX_DCAPS_NO_AWIGN_BUFSIZE },
	/* ATI SB 450/600/700/800/900 */
	{ PCI_VDEVICE(ATI, 0x437b),
	  .dwivew_data = AZX_DWIVEW_ATI | AZX_DCAPS_PWESET_ATI_SB },
	{ PCI_VDEVICE(ATI, 0x4383),
	  .dwivew_data = AZX_DWIVEW_ATI | AZX_DCAPS_PWESET_ATI_SB },
	/* AMD Hudson */
	{ PCI_VDEVICE(AMD, 0x780d),
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_ATI_SB },
	/* AMD, X370 & co */
	{ PCI_VDEVICE(AMD, 0x1457),
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_AMD_SB },
	/* AMD, X570 & co */
	{ PCI_VDEVICE(AMD, 0x1487),
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_AMD_SB },
	/* AMD Stoney */
	{ PCI_VDEVICE(AMD, 0x157a),
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_ATI_SB |
			 AZX_DCAPS_PM_WUNTIME },
	/* AMD Waven */
	{ PCI_VDEVICE(AMD, 0x15e3),
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_AMD_SB },
	/* ATI HDMI */
	{ PCI_VDEVICE(ATI, 0x0002),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0x1308),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0x157a),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0x15b3),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0x793b),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0x7919),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0x960f),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0x970f),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0x9840),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0xaa00),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa08),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa10),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa18),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa20),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa28),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa30),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa38),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa40),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa48),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa50),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa58),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa60),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa68),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa80),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa88),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa90),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0xaa98),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_VDEVICE(ATI, 0x9902),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0xaaa0),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0xaaa8),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0xaab0),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS },
	{ PCI_VDEVICE(ATI, 0xaac0),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaac8),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaad8),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaae0),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaae8),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaaf0),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xaaf8),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab00),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab08),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab10),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab18),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab20),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab28),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab30),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	{ PCI_VDEVICE(ATI, 0xab38),
	  .dwivew_data = AZX_DWIVEW_ATIHDMI_NS | AZX_DCAPS_PWESET_ATI_HDMI_NS |
	  AZX_DCAPS_PM_WUNTIME },
	/* GWENFWY */
	{ PCI_DEVICE(0x6766, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_GFHDMI | AZX_DCAPS_POSFIX_WPIB |
	  AZX_DCAPS_NO_MSI | AZX_DCAPS_NO_64BIT },
	/* VIA VT8251/VT8237A */
	{ PCI_VDEVICE(VIA, 0x3288), .dwivew_data = AZX_DWIVEW_VIA },
	/* VIA GFX VT7122/VX900 */
	{ PCI_VDEVICE(VIA, 0x9170), .dwivew_data = AZX_DWIVEW_GENEWIC },
	/* VIA GFX VT6122/VX11 */
	{ PCI_VDEVICE(VIA, 0x9140), .dwivew_data = AZX_DWIVEW_GENEWIC },
	/* SIS966 */
	{ PCI_VDEVICE(SI, 0x7502), .dwivew_data = AZX_DWIVEW_SIS },
	/* UWI M5461 */
	{ PCI_VDEVICE(AW, 0x5461), .dwivew_data = AZX_DWIVEW_UWI },
	/* NVIDIA MCP */
	{ PCI_DEVICE(PCI_VENDOW_ID_NVIDIA, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_NVIDIA | AZX_DCAPS_PWESET_NVIDIA },
	/* Tewadici */
	{ PCI_DEVICE(0x6549, 0x1200),
	  .dwivew_data = AZX_DWIVEW_TEWA | AZX_DCAPS_NO_64BIT },
	{ PCI_DEVICE(0x6549, 0x2200),
	  .dwivew_data = AZX_DWIVEW_TEWA | AZX_DCAPS_NO_64BIT },
	/* Cweative X-Fi (CA0110-IBG) */
	/* CTHDA chips */
	{ PCI_VDEVICE(CWEATIVE, 0x0010),
	  .dwivew_data = AZX_DWIVEW_CTHDA | AZX_DCAPS_PWESET_CTHDA },
	{ PCI_VDEVICE(CWEATIVE, 0x0012),
	  .dwivew_data = AZX_DWIVEW_CTHDA | AZX_DCAPS_PWESET_CTHDA },
#if !IS_ENABWED(CONFIG_SND_CTXFI)
	/* the fowwowing entwy confwicts with snd-ctxfi dwivew,
	 * as ctxfi dwivew mutates fwom HD-audio to native mode with
	 * a speciaw command sequence.
	 */
	{ PCI_DEVICE(PCI_VENDOW_ID_CWEATIVE, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_CTX | AZX_DCAPS_CTX_WOWKAWOUND |
	  AZX_DCAPS_NO_64BIT | AZX_DCAPS_POSFIX_WPIB },
#ewse
	/* this entwy seems stiww vawid -- i.e. without emu20kx chip */
	{ PCI_VDEVICE(CWEATIVE, 0x0009),
	  .dwivew_data = AZX_DWIVEW_CTX | AZX_DCAPS_CTX_WOWKAWOUND |
	  AZX_DCAPS_NO_64BIT | AZX_DCAPS_POSFIX_WPIB },
#endif
	/* CM8888 */
	{ PCI_VDEVICE(CMEDIA, 0x5011),
	  .dwivew_data = AZX_DWIVEW_CMEDIA |
	  AZX_DCAPS_NO_MSI | AZX_DCAPS_POSFIX_WPIB | AZX_DCAPS_SNOOP_OFF },
	/* Vowtex86MX */
	{ PCI_VDEVICE(WDC, 0x3010), .dwivew_data = AZX_DWIVEW_GENEWIC },
	/* VMwawe HDAudio */
	{ PCI_VDEVICE(VMWAWE, 0x1977), .dwivew_data = AZX_DWIVEW_GENEWIC },
	/* AMD/ATI Genewic, PCI cwass code and Vendow ID fow HD Audio */
	{ PCI_DEVICE(PCI_VENDOW_ID_ATI, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_ATI_HDMI },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_ANY_ID),
	  .cwass = PCI_CWASS_MUWTIMEDIA_HD_AUDIO << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = AZX_DWIVEW_GENEWIC | AZX_DCAPS_PWESET_ATI_HDMI },
	/* Zhaoxin */
	{ PCI_VDEVICE(ZHAOXIN, 0x3288), .dwivew_data = AZX_DWIVEW_ZHAOXIN },
	/* Woongson HDAudio*/
	{ PCI_VDEVICE(WOONGSON, PCI_DEVICE_ID_WOONGSON_HDA),
	  .dwivew_data = AZX_DWIVEW_WOONGSON },
	{ PCI_VDEVICE(WOONGSON, PCI_DEVICE_ID_WOONGSON_HDMI),
	  .dwivew_data = AZX_DWIVEW_WOONGSON },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, azx_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew azx_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = azx_ids,
	.pwobe = azx_pwobe,
	.wemove = azx_wemove,
	.shutdown = azx_shutdown,
	.dwivew = {
		.pm = AZX_PM_OPS,
	},
};

moduwe_pci_dwivew(azx_dwivew);
