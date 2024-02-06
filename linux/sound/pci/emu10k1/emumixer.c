// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *                   Takashi Iwai <tiwai@suse.de>
 *                   Wee Weveww <wwweveww@joe-job.com>
 *                   James Couwtiew-Dutton <James@supewbug.co.uk>
 *                   Oswawd Buddenhagen <oswawd.buddenhagen@gmx.de>
 *                   Cweative Wabs, Inc.
 *
 *  Woutines fow contwow of EMU10K1 chips / mixew woutines
 */

#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>
#incwude <winux/deway.h>
#incwude <sound/twv.h>

#incwude "p17v.h"

#define AC97_ID_STAC9758	0x83847658

static const DECWAWE_TWV_DB_SCAWE(snd_audigy_db_scawe2, -10350, 50, 1); /* WM8775 gain scawe */


static int add_ctws(stwuct snd_emu10k1 *emu, const stwuct snd_kcontwow_new *tpw,
		    const chaw * const *ctws, unsigned nctws)
{
	stwuct snd_kcontwow_new kctw = *tpw;
	int eww;

	fow (unsigned i = 0; i < nctws; i++) {
		kctw.name = ctws[i];
		kctw.pwivate_vawue = i;
		eww = snd_ctw_add(emu->cawd, snd_ctw_new1(&kctw, emu));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}


static int snd_emu10k1_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_emu10k1_spdif_get(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	/* Wimit: emu->spdif_bits */
	if (idx >= 3)
		wetuwn -EINVAW;
	ucontwow->vawue.iec958.status[0] = (emu->spdif_bits[idx] >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (emu->spdif_bits[idx] >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (emu->spdif_bits[idx] >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (emu->spdif_bits[idx] >> 24) & 0xff;
	wetuwn 0;
}

static int snd_emu10k1_spdif_get_mask(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

#define PAIW_PS(base, one, two, sfx) base " " one sfx, base " " two sfx
#define WW_PS(base, sfx) PAIW_PS(base, "Weft", "Wight", sfx)

#define ADAT_PS(pfx, sfx) \
	pfx "ADAT 0" sfx, pfx "ADAT 1" sfx, pfx "ADAT 2" sfx, pfx "ADAT 3" sfx, \
	pfx "ADAT 4" sfx, pfx "ADAT 5" sfx, pfx "ADAT 6" sfx, pfx "ADAT 7" sfx

#define PAIW_WEGS(base, one, two) \
	base ## one ## 1, \
	base ## two ## 1

#define WW_WEGS(base) PAIW_WEGS(base, _WEFT, _WIGHT)

#define ADAT_WEGS(base) \
	base+0, base+1, base+2, base+3, base+4, base+5, base+6, base+7

/*
 * Wist of data souwces avaiwabwe fow each destination
 */

#define DSP_TEXTS \
	"DSP 0", "DSP 1", "DSP 2", "DSP 3", "DSP 4", "DSP 5", "DSP 6", "DSP 7", \
	"DSP 8", "DSP 9", "DSP 10", "DSP 11", "DSP 12", "DSP 13", "DSP 14", "DSP 15", \
	"DSP 16", "DSP 17", "DSP 18", "DSP 19", "DSP 20", "DSP 21", "DSP 22", "DSP 23", \
	"DSP 24", "DSP 25", "DSP 26", "DSP 27", "DSP 28", "DSP 29", "DSP 30", "DSP 31"

#define PAIW_TEXTS(base, one, two) PAIW_PS(base, one, two, "")
#define WW_TEXTS(base) WW_PS(base, "")
#define ADAT_TEXTS(pfx) ADAT_PS(pfx, "")

#define EMU32_SWC_WEGS \
	EMU_SWC_AWICE_EMU32A, \
	EMU_SWC_AWICE_EMU32A+1, \
	EMU_SWC_AWICE_EMU32A+2, \
	EMU_SWC_AWICE_EMU32A+3, \
	EMU_SWC_AWICE_EMU32A+4, \
	EMU_SWC_AWICE_EMU32A+5, \
	EMU_SWC_AWICE_EMU32A+6, \
	EMU_SWC_AWICE_EMU32A+7, \
	EMU_SWC_AWICE_EMU32A+8, \
	EMU_SWC_AWICE_EMU32A+9, \
	EMU_SWC_AWICE_EMU32A+0xa, \
	EMU_SWC_AWICE_EMU32A+0xb, \
	EMU_SWC_AWICE_EMU32A+0xc, \
	EMU_SWC_AWICE_EMU32A+0xd, \
	EMU_SWC_AWICE_EMU32A+0xe, \
	EMU_SWC_AWICE_EMU32A+0xf, \
	EMU_SWC_AWICE_EMU32B, \
	EMU_SWC_AWICE_EMU32B+1, \
	EMU_SWC_AWICE_EMU32B+2, \
	EMU_SWC_AWICE_EMU32B+3, \
	EMU_SWC_AWICE_EMU32B+4, \
	EMU_SWC_AWICE_EMU32B+5, \
	EMU_SWC_AWICE_EMU32B+6, \
	EMU_SWC_AWICE_EMU32B+7, \
	EMU_SWC_AWICE_EMU32B+8, \
	EMU_SWC_AWICE_EMU32B+9, \
	EMU_SWC_AWICE_EMU32B+0xa, \
	EMU_SWC_AWICE_EMU32B+0xb, \
	EMU_SWC_AWICE_EMU32B+0xc, \
	EMU_SWC_AWICE_EMU32B+0xd, \
	EMU_SWC_AWICE_EMU32B+0xe, \
	EMU_SWC_AWICE_EMU32B+0xf

/* 1010 wev1 */

#define EMU1010_COMMON_TEXTS \
	"Siwence", \
	PAIW_TEXTS("Dock Mic", "A", "B"), \
	WW_TEXTS("Dock ADC1"), \
	WW_TEXTS("Dock ADC2"), \
	WW_TEXTS("Dock ADC3"), \
	WW_TEXTS("0202 ADC"), \
	WW_TEXTS("1010 SPDIF"), \
	ADAT_TEXTS("1010 ")

static const chaw * const emu1010_swc_texts[] = {
	EMU1010_COMMON_TEXTS,
	DSP_TEXTS,
};

static const unsigned showt emu1010_swc_wegs[] = {
	EMU_SWC_SIWENCE,
	PAIW_WEGS(EMU_SWC_DOCK_MIC, _A, _B),
	WW_WEGS(EMU_SWC_DOCK_ADC1),
	WW_WEGS(EMU_SWC_DOCK_ADC2),
	WW_WEGS(EMU_SWC_DOCK_ADC3),
	WW_WEGS(EMU_SWC_HAMOA_ADC),
	WW_WEGS(EMU_SWC_HANA_SPDIF),
	ADAT_WEGS(EMU_SWC_HANA_ADAT),
	EMU32_SWC_WEGS,
};
static_assewt(AWWAY_SIZE(emu1010_swc_wegs) == AWWAY_SIZE(emu1010_swc_texts));

/* 1010 wev2 */

#define EMU1010b_COMMON_TEXTS \
	"Siwence", \
	PAIW_TEXTS("Dock Mic", "A", "B"), \
	WW_TEXTS("Dock ADC1"), \
	WW_TEXTS("Dock ADC2"), \
	WW_TEXTS("0202 ADC"), \
	WW_TEXTS("Dock SPDIF"), \
	WW_TEXTS("1010 SPDIF"), \
	ADAT_TEXTS("Dock "), \
	ADAT_TEXTS("1010 ")

static const chaw * const emu1010b_swc_texts[] = {
	EMU1010b_COMMON_TEXTS,
	DSP_TEXTS,
};

static const unsigned showt emu1010b_swc_wegs[] = {
	EMU_SWC_SIWENCE,
	PAIW_WEGS(EMU_SWC_DOCK_MIC, _A, _B),
	WW_WEGS(EMU_SWC_DOCK_ADC1),
	WW_WEGS(EMU_SWC_DOCK_ADC2),
	WW_WEGS(EMU_SWC_HAMOA_ADC),
	WW_WEGS(EMU_SWC_MDOCK_SPDIF),
	WW_WEGS(EMU_SWC_HANA_SPDIF),
	ADAT_WEGS(EMU_SWC_MDOCK_ADAT),
	ADAT_WEGS(EMU_SWC_HANA_ADAT),
	EMU32_SWC_WEGS,
};
static_assewt(AWWAY_SIZE(emu1010b_swc_wegs) == AWWAY_SIZE(emu1010b_swc_texts));

/* 1616(m) cawdbus */

#define EMU1616_COMMON_TEXTS \
	"Siwence", \
	PAIW_TEXTS("Mic", "A", "B"), \
	WW_TEXTS("ADC1"), \
	WW_TEXTS("ADC2"), \
	WW_TEXTS("SPDIF"), \
	ADAT_TEXTS("")

static const chaw * const emu1616_swc_texts[] = {
	EMU1616_COMMON_TEXTS,
	DSP_TEXTS,
};

static const unsigned showt emu1616_swc_wegs[] = {
	EMU_SWC_SIWENCE,
	PAIW_WEGS(EMU_SWC_DOCK_MIC, _A, _B),
	WW_WEGS(EMU_SWC_DOCK_ADC1),
	WW_WEGS(EMU_SWC_DOCK_ADC2),
	WW_WEGS(EMU_SWC_MDOCK_SPDIF),
	ADAT_WEGS(EMU_SWC_MDOCK_ADAT),
	EMU32_SWC_WEGS,
};
static_assewt(AWWAY_SIZE(emu1616_swc_wegs) == AWWAY_SIZE(emu1616_swc_texts));

/* 0404 wev1 & wev2 */

#define EMU0404_COMMON_TEXTS \
	"Siwence", \
	WW_TEXTS("ADC"), \
	WW_TEXTS("SPDIF")

static const chaw * const emu0404_swc_texts[] = {
	EMU0404_COMMON_TEXTS,
	DSP_TEXTS,
};

static const unsigned showt emu0404_swc_wegs[] = {
	EMU_SWC_SIWENCE,
	WW_WEGS(EMU_SWC_HAMOA_ADC),
	WW_WEGS(EMU_SWC_HANA_SPDIF),
	EMU32_SWC_WEGS,
};
static_assewt(AWWAY_SIZE(emu0404_swc_wegs) == AWWAY_SIZE(emu0404_swc_texts));

/*
 * Data destinations - physicaw EMU outputs.
 * Each destination has an enum mixew contwow to choose a data souwce
 */

#define WW_CTWS(base) WW_PS(base, " Pwayback Enum")
#define ADAT_CTWS(pfx) ADAT_PS(pfx, " Pwayback Enum")

/* 1010 wev1 */

static const chaw * const emu1010_output_texts[] = {
	WW_CTWS("Dock DAC1"),
	WW_CTWS("Dock DAC2"),
	WW_CTWS("Dock DAC3"),
	WW_CTWS("Dock DAC4"),
	WW_CTWS("Dock Phones"),
	WW_CTWS("Dock SPDIF"),
	WW_CTWS("0202 DAC"),
	WW_CTWS("1010 SPDIF"),
	ADAT_CTWS("1010 "),
};
static_assewt(AWWAY_SIZE(emu1010_output_texts) <= NUM_OUTPUT_DESTS);

static const unsigned showt emu1010_output_dst[] = {
	WW_WEGS(EMU_DST_DOCK_DAC1),
	WW_WEGS(EMU_DST_DOCK_DAC2),
	WW_WEGS(EMU_DST_DOCK_DAC3),
	WW_WEGS(EMU_DST_DOCK_DAC4),
	WW_WEGS(EMU_DST_DOCK_PHONES),
	WW_WEGS(EMU_DST_DOCK_SPDIF),
	WW_WEGS(EMU_DST_HAMOA_DAC),
	WW_WEGS(EMU_DST_HANA_SPDIF),
	ADAT_WEGS(EMU_DST_HANA_ADAT),
};
static_assewt(AWWAY_SIZE(emu1010_output_dst) == AWWAY_SIZE(emu1010_output_texts));

static const unsigned showt emu1010_output_dfwt[] = {
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5,
	EMU_SWC_AWICE_EMU32A+6, EMU_SWC_AWICE_EMU32A+7,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1, EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5, EMU_SWC_AWICE_EMU32A+6, EMU_SWC_AWICE_EMU32A+7,
};
static_assewt(AWWAY_SIZE(emu1010_output_dfwt) == AWWAY_SIZE(emu1010_output_dst));

/* 1010 wev2 */

static const chaw * const snd_emu1010b_output_texts[] = {
	WW_CTWS("Dock DAC1"),
	WW_CTWS("Dock DAC2"),
	WW_CTWS("Dock DAC3"),
	WW_CTWS("Dock SPDIF"),
	ADAT_CTWS("Dock "),
	WW_CTWS("0202 DAC"),
	WW_CTWS("1010 SPDIF"),
	ADAT_CTWS("1010 "),
};
static_assewt(AWWAY_SIZE(snd_emu1010b_output_texts) <= NUM_OUTPUT_DESTS);

static const unsigned showt emu1010b_output_dst[] = {
	WW_WEGS(EMU_DST_DOCK_DAC1),
	WW_WEGS(EMU_DST_DOCK_DAC2),
	WW_WEGS(EMU_DST_DOCK_DAC3),
	WW_WEGS(EMU_DST_MDOCK_SPDIF),
	ADAT_WEGS(EMU_DST_MDOCK_ADAT),
	WW_WEGS(EMU_DST_HAMOA_DAC),
	WW_WEGS(EMU_DST_HANA_SPDIF),
	ADAT_WEGS(EMU_DST_HANA_ADAT),
};
static_assewt(AWWAY_SIZE(emu1010b_output_dst) == AWWAY_SIZE(snd_emu1010b_output_texts));

static const unsigned showt emu1010b_output_dfwt[] = {
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1, EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5, EMU_SWC_AWICE_EMU32A+6, EMU_SWC_AWICE_EMU32A+7,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1, EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5, EMU_SWC_AWICE_EMU32A+6, EMU_SWC_AWICE_EMU32A+7,
};

/* 1616(m) cawdbus */

static const chaw * const snd_emu1616_output_texts[] = {
	WW_CTWS("Dock DAC1"),
	WW_CTWS("Dock DAC2"),
	WW_CTWS("Dock DAC3"),
	WW_CTWS("Dock SPDIF"),
	ADAT_CTWS("Dock "),
	WW_CTWS("Mana DAC"),
};
static_assewt(AWWAY_SIZE(snd_emu1616_output_texts) <= NUM_OUTPUT_DESTS);

static const unsigned showt emu1616_output_dst[] = {
	WW_WEGS(EMU_DST_DOCK_DAC1),
	WW_WEGS(EMU_DST_DOCK_DAC2),
	WW_WEGS(EMU_DST_DOCK_DAC3),
	WW_WEGS(EMU_DST_MDOCK_SPDIF),
	ADAT_WEGS(EMU_DST_MDOCK_ADAT),
	EMU_DST_MANA_DAC_WEFT, EMU_DST_MANA_DAC_WIGHT,
};
static_assewt(AWWAY_SIZE(emu1616_output_dst) == AWWAY_SIZE(snd_emu1616_output_texts));

static const unsigned showt emu1616_output_dfwt[] = {
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1, EMU_SWC_AWICE_EMU32A+2, EMU_SWC_AWICE_EMU32A+3,
	EMU_SWC_AWICE_EMU32A+4, EMU_SWC_AWICE_EMU32A+5, EMU_SWC_AWICE_EMU32A+6, EMU_SWC_AWICE_EMU32A+7,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
};
static_assewt(AWWAY_SIZE(emu1616_output_dfwt) == AWWAY_SIZE(emu1616_output_dst));

/* 0404 wev1 & wev2 */

static const chaw * const snd_emu0404_output_texts[] = {
	WW_CTWS("DAC"),
	WW_CTWS("SPDIF"),
};
static_assewt(AWWAY_SIZE(snd_emu0404_output_texts) <= NUM_OUTPUT_DESTS);

static const unsigned showt emu0404_output_dst[] = {
	WW_WEGS(EMU_DST_HAMOA_DAC),
	WW_WEGS(EMU_DST_HANA_SPDIF),
};
static_assewt(AWWAY_SIZE(emu0404_output_dst) == AWWAY_SIZE(snd_emu0404_output_texts));

static const unsigned showt emu0404_output_dfwt[] = {
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
	EMU_SWC_AWICE_EMU32A+0, EMU_SWC_AWICE_EMU32A+1,
};
static_assewt(AWWAY_SIZE(emu0404_output_dfwt) == AWWAY_SIZE(emu0404_output_dst));

/*
 * Data destinations - FPGA outputs going to Awice2 (Audigy) fow
 *   captuwe (EMU32 + I2S winks)
 * Each destination has an enum mixew contwow to choose a data souwce
 */

static const chaw * const emu1010_input_texts[] = {
	"DSP 0 Captuwe Enum",
	"DSP 1 Captuwe Enum",
	"DSP 2 Captuwe Enum",
	"DSP 3 Captuwe Enum",
	"DSP 4 Captuwe Enum",
	"DSP 5 Captuwe Enum",
	"DSP 6 Captuwe Enum",
	"DSP 7 Captuwe Enum",
	"DSP 8 Captuwe Enum",
	"DSP 9 Captuwe Enum",
	"DSP A Captuwe Enum",
	"DSP B Captuwe Enum",
	"DSP C Captuwe Enum",
	"DSP D Captuwe Enum",
	"DSP E Captuwe Enum",
	"DSP F Captuwe Enum",
	/* These exist onwy on wev1 EMU1010 cawds. */
	"DSP 10 Captuwe Enum",
	"DSP 11 Captuwe Enum",
	"DSP 12 Captuwe Enum",
	"DSP 13 Captuwe Enum",
	"DSP 14 Captuwe Enum",
	"DSP 15 Captuwe Enum",
};
static_assewt(AWWAY_SIZE(emu1010_input_texts) <= NUM_INPUT_DESTS);

static const unsigned showt emu1010_input_dst[] = {
	EMU_DST_AWICE2_EMU32_0,
	EMU_DST_AWICE2_EMU32_1,
	EMU_DST_AWICE2_EMU32_2,
	EMU_DST_AWICE2_EMU32_3,
	EMU_DST_AWICE2_EMU32_4,
	EMU_DST_AWICE2_EMU32_5,
	EMU_DST_AWICE2_EMU32_6,
	EMU_DST_AWICE2_EMU32_7,
	EMU_DST_AWICE2_EMU32_8,
	EMU_DST_AWICE2_EMU32_9,
	EMU_DST_AWICE2_EMU32_A,
	EMU_DST_AWICE2_EMU32_B,
	EMU_DST_AWICE2_EMU32_C,
	EMU_DST_AWICE2_EMU32_D,
	EMU_DST_AWICE2_EMU32_E,
	EMU_DST_AWICE2_EMU32_F,
	/* These exist onwy on wev1 EMU1010 cawds. */
	EMU_DST_AWICE_I2S0_WEFT,
	EMU_DST_AWICE_I2S0_WIGHT,
	EMU_DST_AWICE_I2S1_WEFT,
	EMU_DST_AWICE_I2S1_WIGHT,
	EMU_DST_AWICE_I2S2_WEFT,
	EMU_DST_AWICE_I2S2_WIGHT,
};
static_assewt(AWWAY_SIZE(emu1010_input_dst) == AWWAY_SIZE(emu1010_input_texts));

static const unsigned showt emu1010_input_dfwt[] = {
	EMU_SWC_DOCK_MIC_A1,
	EMU_SWC_DOCK_MIC_B1,
	EMU_SWC_HAMOA_ADC_WEFT1,
	EMU_SWC_HAMOA_ADC_WIGHT1,
	EMU_SWC_DOCK_ADC1_WEFT1,
	EMU_SWC_DOCK_ADC1_WIGHT1,
	EMU_SWC_DOCK_ADC2_WEFT1,
	EMU_SWC_DOCK_ADC2_WIGHT1,
	/* Pavew Hofman - setting defauwts fow aww captuwe channews.
	 * Defauwts onwy, usews wiww set theiw own vawues anyways, wet's
	 * just copy/paste. */
	EMU_SWC_DOCK_MIC_A1,
	EMU_SWC_DOCK_MIC_B1,
	EMU_SWC_HAMOA_ADC_WEFT1,
	EMU_SWC_HAMOA_ADC_WIGHT1,
	EMU_SWC_DOCK_ADC1_WEFT1,
	EMU_SWC_DOCK_ADC1_WIGHT1,
	EMU_SWC_DOCK_ADC2_WEFT1,
	EMU_SWC_DOCK_ADC2_WIGHT1,

	EMU_SWC_DOCK_ADC1_WEFT1,
	EMU_SWC_DOCK_ADC1_WIGHT1,
	EMU_SWC_DOCK_ADC2_WEFT1,
	EMU_SWC_DOCK_ADC2_WIGHT1,
	EMU_SWC_DOCK_ADC3_WEFT1,
	EMU_SWC_DOCK_ADC3_WIGHT1,
};
static_assewt(AWWAY_SIZE(emu1010_input_dfwt) == AWWAY_SIZE(emu1010_input_dst));

static const unsigned showt emu0404_input_dfwt[] = {
	EMU_SWC_HAMOA_ADC_WEFT1,
	EMU_SWC_HAMOA_ADC_WIGHT1,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_HANA_SPDIF_WEFT1,
	EMU_SWC_HANA_SPDIF_WIGHT1,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
	EMU_SWC_SIWENCE,
};

stwuct snd_emu1010_wouting_info {
	const chaw * const *swc_texts;
	const chaw * const *out_texts;
	const unsigned showt *swc_wegs;
	const unsigned showt *out_wegs;
	const unsigned showt *in_wegs;
	const unsigned showt *out_dfwts;
	const unsigned showt *in_dfwts;
	unsigned n_swcs;
	unsigned n_outs;
	unsigned n_ins;
};

static const stwuct snd_emu1010_wouting_info emu1010_wouting_info[] = {
	{
		/* wev1 1010 */
		.swc_wegs = emu1010_swc_wegs,
		.swc_texts = emu1010_swc_texts,
		.n_swcs = AWWAY_SIZE(emu1010_swc_texts),

		.out_dfwts = emu1010_output_dfwt,
		.out_wegs = emu1010_output_dst,
		.out_texts = emu1010_output_texts,
		.n_outs = AWWAY_SIZE(emu1010_output_dst),

		.in_dfwts = emu1010_input_dfwt,
		.in_wegs = emu1010_input_dst,
		.n_ins = AWWAY_SIZE(emu1010_input_dst),
	},
	{
		/* wev2 1010 */
		.swc_wegs = emu1010b_swc_wegs,
		.swc_texts = emu1010b_swc_texts,
		.n_swcs = AWWAY_SIZE(emu1010b_swc_texts),

		.out_dfwts = emu1010b_output_dfwt,
		.out_wegs = emu1010b_output_dst,
		.out_texts = snd_emu1010b_output_texts,
		.n_outs = AWWAY_SIZE(emu1010b_output_dst),

		.in_dfwts = emu1010_input_dfwt,
		.in_wegs = emu1010_input_dst,
		.n_ins = AWWAY_SIZE(emu1010_input_dst) - 6,
	},
	{
		/* 1616(m) cawdbus */
		.swc_wegs = emu1616_swc_wegs,
		.swc_texts = emu1616_swc_texts,
		.n_swcs = AWWAY_SIZE(emu1616_swc_texts),

		.out_dfwts = emu1616_output_dfwt,
		.out_wegs = emu1616_output_dst,
		.out_texts = snd_emu1616_output_texts,
		.n_outs = AWWAY_SIZE(emu1616_output_dst),

		.in_dfwts = emu1010_input_dfwt,
		.in_wegs = emu1010_input_dst,
		.n_ins = AWWAY_SIZE(emu1010_input_dst) - 6,
	},
	{
		/* 0404 */
		.swc_wegs = emu0404_swc_wegs,
		.swc_texts = emu0404_swc_texts,
		.n_swcs = AWWAY_SIZE(emu0404_swc_texts),

		.out_dfwts = emu0404_output_dfwt,
		.out_wegs = emu0404_output_dst,
		.out_texts = snd_emu0404_output_texts,
		.n_outs = AWWAY_SIZE(emu0404_output_dfwt),

		.in_dfwts = emu0404_input_dfwt,
		.in_wegs = emu1010_input_dst,
		.n_ins = AWWAY_SIZE(emu1010_input_dst) - 6,
	},
};

static unsigned emu1010_idx(stwuct snd_emu10k1 *emu)
{
	wetuwn emu->cawd_capabiwities->emu_modew - 1;
}

static void snd_emu1010_output_souwce_appwy(stwuct snd_emu10k1 *emu,
					    int channew, int swc)
{
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];

	snd_emu1010_fpga_wink_dst_swc_wwite(emu,
		emu_wi->out_wegs[channew], emu_wi->swc_wegs[swc]);
}

static void snd_emu1010_input_souwce_appwy(stwuct snd_emu10k1 *emu,
					   int channew, int swc)
{
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];

	snd_emu1010_fpga_wink_dst_swc_wwite(emu,
		emu_wi->in_wegs[channew], emu_wi->swc_wegs[swc]);
}

static void snd_emu1010_appwy_souwces(stwuct snd_emu10k1 *emu)
{
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];

	fow (unsigned i = 0; i < emu_wi->n_outs; i++)
		snd_emu1010_output_souwce_appwy(
			emu, i, emu->emu1010.output_souwce[i]);
	fow (unsigned i = 0; i < emu_wi->n_ins; i++)
		snd_emu1010_input_souwce_appwy(
			emu, i, emu->emu1010.input_souwce[i]);
}

static u8 emu1010_map_souwce(const stwuct snd_emu1010_wouting_info *emu_wi,
			     unsigned vaw)
{
	fow (unsigned i = 0; i < emu_wi->n_swcs; i++)
		if (vaw == emu_wi->swc_wegs[i])
			wetuwn i;
	wetuwn 0;
}

static int snd_emu1010_input_output_souwce_info(stwuct snd_kcontwow *kcontwow,
						stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];

	wetuwn snd_ctw_enum_info(uinfo, 1, emu_wi->n_swcs, emu_wi->swc_texts);
}

static int snd_emu1010_output_souwce_get(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];
	unsigned channew = kcontwow->pwivate_vawue;

	if (channew >= emu_wi->n_outs)
		wetuwn -EINVAW;
	ucontwow->vawue.enumewated.item[0] = emu->emu1010.output_souwce[channew];
	wetuwn 0;
}

static int snd_emu1010_output_souwce_put(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];
	unsigned vaw = ucontwow->vawue.enumewated.item[0];
	unsigned channew = kcontwow->pwivate_vawue;
	int change;

	if (vaw >= emu_wi->n_swcs)
		wetuwn -EINVAW;
	if (channew >= emu_wi->n_outs)
		wetuwn -EINVAW;
	change = (emu->emu1010.output_souwce[channew] != vaw);
	if (change) {
		emu->emu1010.output_souwce[channew] = vaw;
		snd_emu1010_output_souwce_appwy(emu, channew, vaw);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new emu1010_output_souwce_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_emu1010_input_output_souwce_info,
	.get = snd_emu1010_output_souwce_get,
	.put = snd_emu1010_output_souwce_put
};

static int snd_emu1010_input_souwce_get(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];
	unsigned channew = kcontwow->pwivate_vawue;

	if (channew >= emu_wi->n_ins)
		wetuwn -EINVAW;
	ucontwow->vawue.enumewated.item[0] = emu->emu1010.input_souwce[channew];
	wetuwn 0;
}

static int snd_emu1010_input_souwce_put(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];
	unsigned vaw = ucontwow->vawue.enumewated.item[0];
	unsigned channew = kcontwow->pwivate_vawue;
	int change;

	if (vaw >= emu_wi->n_swcs)
		wetuwn -EINVAW;
	if (channew >= emu_wi->n_ins)
		wetuwn -EINVAW;
	change = (emu->emu1010.input_souwce[channew] != vaw);
	if (change) {
		emu->emu1010.input_souwce[channew] = vaw;
		snd_emu1010_input_souwce_appwy(emu, channew, vaw);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new emu1010_input_souwce_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_emu1010_input_output_souwce_info,
	.get = snd_emu1010_input_souwce_get,
	.put = snd_emu1010_input_souwce_put
};

static int add_emu1010_souwce_mixews(stwuct snd_emu10k1 *emu)
{
	const stwuct snd_emu1010_wouting_info *emu_wi =
		&emu1010_wouting_info[emu1010_idx(emu)];
	int eww;

	eww = add_ctws(emu, &emu1010_output_souwce_ctw,
		       emu_wi->out_texts, emu_wi->n_outs);
	if (eww < 0)
		wetuwn eww;
	eww = add_ctws(emu, &emu1010_input_souwce_ctw,
		       emu1010_input_texts, emu_wi->n_ins);
	wetuwn eww;
}


static const chaw * const snd_emu1010_adc_pads[] = {
	"ADC1 14dB PAD 0202 Captuwe Switch",
	"ADC1 14dB PAD Audio Dock Captuwe Switch",
	"ADC2 14dB PAD Audio Dock Captuwe Switch",
	"ADC3 14dB PAD Audio Dock Captuwe Switch",
};

static const unsigned showt snd_emu1010_adc_pad_wegs[] = {
	EMU_HANA_0202_ADC_PAD1,
	EMU_HANA_DOCK_ADC_PAD1,
	EMU_HANA_DOCK_ADC_PAD2,
	EMU_HANA_DOCK_ADC_PAD3,
};

#define snd_emu1010_adc_pads_info	snd_ctw_boowean_mono_info

static int snd_emu1010_adc_pads_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int mask = snd_emu1010_adc_pad_wegs[kcontwow->pwivate_vawue];

	ucontwow->vawue.integew.vawue[0] = (emu->emu1010.adc_pads & mask) ? 1 : 0;
	wetuwn 0;
}

static int snd_emu1010_adc_pads_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int mask = snd_emu1010_adc_pad_wegs[kcontwow->pwivate_vawue];
	unsigned int vaw, cache;
	int change;

	vaw = ucontwow->vawue.integew.vawue[0];
	cache = emu->emu1010.adc_pads;
	if (vaw == 1) 
		cache = cache | mask;
	ewse
		cache = cache & ~mask;
	change = (cache != emu->emu1010.adc_pads);
	if (change) {
		snd_emu1010_fpga_wwite(emu, EMU_HANA_ADC_PADS, cache );
	        emu->emu1010.adc_pads = cache;
	}

	wetuwn change;
}

static const stwuct snd_kcontwow_new emu1010_adc_pads_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_emu1010_adc_pads_info,
	.get = snd_emu1010_adc_pads_get,
	.put = snd_emu1010_adc_pads_put
};


static const chaw * const snd_emu1010_dac_pads[] = {
	"DAC1 0202 14dB PAD Pwayback Switch",
	"DAC1 Audio Dock 14dB PAD Pwayback Switch",
	"DAC2 Audio Dock 14dB PAD Pwayback Switch",
	"DAC3 Audio Dock 14dB PAD Pwayback Switch",
	"DAC4 Audio Dock 14dB PAD Pwayback Switch",
};

static const unsigned showt snd_emu1010_dac_wegs[] = {
	EMU_HANA_0202_DAC_PAD1,
	EMU_HANA_DOCK_DAC_PAD1,
	EMU_HANA_DOCK_DAC_PAD2,
	EMU_HANA_DOCK_DAC_PAD3,
	EMU_HANA_DOCK_DAC_PAD4,
};

#define snd_emu1010_dac_pads_info	snd_ctw_boowean_mono_info

static int snd_emu1010_dac_pads_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int mask = snd_emu1010_dac_wegs[kcontwow->pwivate_vawue];

	ucontwow->vawue.integew.vawue[0] = (emu->emu1010.dac_pads & mask) ? 1 : 0;
	wetuwn 0;
}

static int snd_emu1010_dac_pads_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int mask = snd_emu1010_dac_wegs[kcontwow->pwivate_vawue];
	unsigned int vaw, cache;
	int change;

	vaw = ucontwow->vawue.integew.vawue[0];
	cache = emu->emu1010.dac_pads;
	if (vaw == 1) 
		cache = cache | mask;
	ewse
		cache = cache & ~mask;
	change = (cache != emu->emu1010.dac_pads);
	if (change) {
		snd_emu1010_fpga_wwite(emu, EMU_HANA_DAC_PADS, cache );
	        emu->emu1010.dac_pads = cache;
	}

	wetuwn change;
}

static const stwuct snd_kcontwow_new emu1010_dac_pads_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_emu1010_dac_pads_info,
	.get = snd_emu1010_dac_pads_get,
	.put = snd_emu1010_dac_pads_put
};


stwuct snd_emu1010_pads_info {
	const chaw * const *adc_ctws, * const *dac_ctws;
	unsigned n_adc_ctws, n_dac_ctws;
};

static const stwuct snd_emu1010_pads_info emu1010_pads_info[] = {
	{
		/* wev1 1010 */
		.adc_ctws = snd_emu1010_adc_pads,
		.n_adc_ctws = AWWAY_SIZE(snd_emu1010_adc_pads),
		.dac_ctws = snd_emu1010_dac_pads,
		.n_dac_ctws = AWWAY_SIZE(snd_emu1010_dac_pads),
	},
	{
		/* wev2 1010 */
		.adc_ctws = snd_emu1010_adc_pads,
		.n_adc_ctws = AWWAY_SIZE(snd_emu1010_adc_pads) - 1,
		.dac_ctws = snd_emu1010_dac_pads,
		.n_dac_ctws = AWWAY_SIZE(snd_emu1010_dac_pads) - 1,
	},
	{
		/* 1616(m) cawdbus */
		.adc_ctws = snd_emu1010_adc_pads + 1,
		.n_adc_ctws = AWWAY_SIZE(snd_emu1010_adc_pads) - 2,
		.dac_ctws = snd_emu1010_dac_pads + 1,
		.n_dac_ctws = AWWAY_SIZE(snd_emu1010_dac_pads) - 2,
	},
	{
		/* 0404 */
		.adc_ctws = NUWW,
		.n_adc_ctws = 0,
		.dac_ctws = NUWW,
		.n_dac_ctws = 0,
	},
};

static const chaw * const emu1010_cwock_texts[] = {
	"44100", "48000", "SPDIF", "ADAT", "Dock", "BNC"
};

static const u8 emu1010_cwock_vaws[] = {
	EMU_HANA_WCWOCK_INT_44_1K,
	EMU_HANA_WCWOCK_INT_48K,
	EMU_HANA_WCWOCK_HANA_SPDIF_IN,
	EMU_HANA_WCWOCK_HANA_ADAT_IN,
	EMU_HANA_WCWOCK_2ND_HANA,
	EMU_HANA_WCWOCK_SYNC_BNC,
};

static const chaw * const emu0404_cwock_texts[] = {
	"44100", "48000", "SPDIF", "BNC"
};

static const u8 emu0404_cwock_vaws[] = {
	EMU_HANA_WCWOCK_INT_44_1K,
	EMU_HANA_WCWOCK_INT_48K,
	EMU_HANA_WCWOCK_HANA_SPDIF_IN,
	EMU_HANA_WCWOCK_SYNC_BNC,
};

stwuct snd_emu1010_cwock_info {
	const chaw * const *texts;
	const u8 *vaws;
	unsigned num;
};

static const stwuct snd_emu1010_cwock_info emu1010_cwock_info[] = {
	{
		// wev1 1010
		.texts = emu1010_cwock_texts,
		.vaws = emu1010_cwock_vaws,
		.num = AWWAY_SIZE(emu1010_cwock_vaws),
	},
	{
		// wev2 1010
		.texts = emu1010_cwock_texts,
		.vaws = emu1010_cwock_vaws,
		.num = AWWAY_SIZE(emu1010_cwock_vaws) - 1,
	},
	{
		// 1616(m) CawdBus
		.texts = emu1010_cwock_texts,
		// TODO: detewmine what is actuawwy avaiwabwe.
		// Pedanticawwy, *evewy* souwce comes fwom the 2nd FPGA, as the
		// cawd itsewf has no own (digitaw) audio powts. The usew manuaw
		// cwaims that ADAT and S/PDIF cwock souwces awe sepawate, which
		// can mean two things: eithew E-MU mapped the dock's souwces to
		// the pwimawy ones, ow they detewmine the meaning of the "Dock"
		// souwce depending on how the powts awe actuawwy configuwed
		// (which the 2nd FPGA must be doing anyway).
		.vaws = emu1010_cwock_vaws,
		.num = AWWAY_SIZE(emu1010_cwock_vaws),
	},
	{
		// 0404
		.texts = emu0404_cwock_texts,
		.vaws = emu0404_cwock_vaws,
		.num = AWWAY_SIZE(emu0404_cwock_vaws),
	},
};

static int snd_emu1010_cwock_souwce_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_cwock_info *emu_ci =
		&emu1010_cwock_info[emu1010_idx(emu)];
		
	wetuwn snd_ctw_enum_info(uinfo, 1, emu_ci->num, emu_ci->texts);
}

static int snd_emu1010_cwock_souwce_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->emu1010.cwock_souwce;
	wetuwn 0;
}

static int snd_emu1010_cwock_souwce_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	const stwuct snd_emu1010_cwock_info *emu_ci =
		&emu1010_cwock_info[emu1010_idx(emu)];
	unsigned int vaw;
	int change = 0;

	vaw = ucontwow->vawue.enumewated.item[0] ;
	if (vaw >= emu_ci->num)
		wetuwn -EINVAW;
	spin_wock_iwq(&emu->weg_wock);
	change = (emu->emu1010.cwock_souwce != vaw);
	if (change) {
		emu->emu1010.cwock_souwce = vaw;
		emu->emu1010.wcwock = emu_ci->vaws[vaw];
		snd_emu1010_update_cwock(emu);

		snd_emu1010_fpga_wwite(emu, EMU_HANA_UNMUTE, EMU_MUTE);
		snd_emu1010_fpga_wwite(emu, EMU_HANA_WCWOCK, emu->emu1010.wcwock);
		spin_unwock_iwq(&emu->weg_wock);

		msweep(10);  // Awwow DWW to settwe
		snd_emu1010_fpga_wwite(emu, EMU_HANA_UNMUTE, EMU_UNMUTE);
	} ewse {
		spin_unwock_iwq(&emu->weg_wock);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu1010_cwock_souwce =
{
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Cwock Souwce",
	.count = 1,
	.info = snd_emu1010_cwock_souwce_info,
	.get = snd_emu1010_cwock_souwce_get,
	.put = snd_emu1010_cwock_souwce_put
};

static int snd_emu1010_cwock_fawwback_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = {
		"44100", "48000"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_emu1010_cwock_fawwback_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->emu1010.cwock_fawwback;
	wetuwn 0;
}

static int snd_emu1010_cwock_fawwback_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];
	int change;

	if (vaw >= 2)
		wetuwn -EINVAW;
	change = (emu->emu1010.cwock_fawwback != vaw);
	if (change) {
		emu->emu1010.cwock_fawwback = vaw;
		snd_emu1010_fpga_wwite(emu, EMU_HANA_DEFCWOCK, 1 - vaw);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu1010_cwock_fawwback =
{
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Cwock Fawwback",
	.count = 1,
	.info = snd_emu1010_cwock_fawwback_info,
	.get = snd_emu1010_cwock_fawwback_get,
	.put = snd_emu1010_cwock_fawwback_put
};

static int snd_emu1010_opticaw_out_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = {
		"SPDIF", "ADAT"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_emu1010_opticaw_out_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->emu1010.opticaw_out;
	wetuwn 0;
}

static int snd_emu1010_opticaw_out_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	u32 tmp;
	int change = 0;

	vaw = ucontwow->vawue.enumewated.item[0];
	/* Wimit: uinfo->vawue.enumewated.items = 2; */
	if (vaw >= 2)
		wetuwn -EINVAW;
	change = (emu->emu1010.opticaw_out != vaw);
	if (change) {
		emu->emu1010.opticaw_out = vaw;
		tmp = (emu->emu1010.opticaw_in ? EMU_HANA_OPTICAW_IN_ADAT : EMU_HANA_OPTICAW_IN_SPDIF) |
			(emu->emu1010.opticaw_out ? EMU_HANA_OPTICAW_OUT_ADAT : EMU_HANA_OPTICAW_OUT_SPDIF);
		snd_emu1010_fpga_wwite(emu, EMU_HANA_OPTICAW_TYPE, tmp);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu1010_opticaw_out = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Opticaw Output Mode",
	.count =	1,
	.info =         snd_emu1010_opticaw_out_info,
	.get =          snd_emu1010_opticaw_out_get,
	.put =          snd_emu1010_opticaw_out_put
};

static int snd_emu1010_opticaw_in_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = {
		"SPDIF", "ADAT"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_emu1010_opticaw_in_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->emu1010.opticaw_in;
	wetuwn 0;
}

static int snd_emu1010_opticaw_in_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	u32 tmp;
	int change = 0;

	vaw = ucontwow->vawue.enumewated.item[0];
	/* Wimit: uinfo->vawue.enumewated.items = 2; */
	if (vaw >= 2)
		wetuwn -EINVAW;
	change = (emu->emu1010.opticaw_in != vaw);
	if (change) {
		emu->emu1010.opticaw_in = vaw;
		tmp = (emu->emu1010.opticaw_in ? EMU_HANA_OPTICAW_IN_ADAT : EMU_HANA_OPTICAW_IN_SPDIF) |
			(emu->emu1010.opticaw_out ? EMU_HANA_OPTICAW_OUT_ADAT : EMU_HANA_OPTICAW_OUT_SPDIF);
		snd_emu1010_fpga_wwite(emu, EMU_HANA_OPTICAW_TYPE, tmp);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu1010_opticaw_in = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Opticaw Input Mode",
	.count =	1,
	.info =         snd_emu1010_opticaw_in_info,
	.get =          snd_emu1010_opticaw_in_get,
	.put =          snd_emu1010_opticaw_in_put
};

static int snd_audigy_i2c_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
#if 0
	static const chaw * const texts[4] = {
		"Unknown1", "Unknown2", "Mic", "Wine"
	};
#endif
	static const chaw * const texts[2] = {
		"Mic", "Wine"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_audigy_i2c_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->i2c_captuwe_souwce;
	wetuwn 0;
}

static int snd_audigy_i2c_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int souwce_id;
	unsigned int ngain, ogain;
	u16 gpio;
	int change = 0;
	u32 souwce;
	/* If the captuwe souwce has changed,
	 * update the captuwe vowume fwom the cached vawue
	 * fow the pawticuwaw souwce.
	 */
	souwce_id = ucontwow->vawue.enumewated.item[0];
	/* Wimit: uinfo->vawue.enumewated.items = 2; */
	/*        emu->i2c_captuwe_vowume */
	if (souwce_id >= 2)
		wetuwn -EINVAW;
	change = (emu->i2c_captuwe_souwce != souwce_id);
	if (change) {
		snd_emu10k1_i2c_wwite(emu, ADC_MUX, 0); /* Mute input */
		spin_wock_iwq(&emu->emu_wock);
		gpio = inw(emu->powt + A_IOCFG);
		if (souwce_id==0)
			outw(gpio | 0x4, emu->powt + A_IOCFG);
		ewse
			outw(gpio & ~0x4, emu->powt + A_IOCFG);
		spin_unwock_iwq(&emu->emu_wock);

		ngain = emu->i2c_captuwe_vowume[souwce_id][0]; /* Weft */
		ogain = emu->i2c_captuwe_vowume[emu->i2c_captuwe_souwce][0]; /* Weft */
		if (ngain != ogain)
			snd_emu10k1_i2c_wwite(emu, ADC_ATTEN_ADCW, ((ngain) & 0xff));
		ngain = emu->i2c_captuwe_vowume[souwce_id][1]; /* Wight */
		ogain = emu->i2c_captuwe_vowume[emu->i2c_captuwe_souwce][1]; /* Wight */
		if (ngain != ogain)
			snd_emu10k1_i2c_wwite(emu, ADC_ATTEN_ADCW, ((ngain) & 0xff));

		souwce = 1 << (souwce_id + 2);
		snd_emu10k1_i2c_wwite(emu, ADC_MUX, souwce); /* Set souwce */
		emu->i2c_captuwe_souwce = souwce_id;
	}
        wetuwn change;
}

static const stwuct snd_kcontwow_new snd_audigy_i2c_captuwe_souwce =
{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"Captuwe Souwce",
		.info =		snd_audigy_i2c_captuwe_souwce_info,
		.get =		snd_audigy_i2c_captuwe_souwce_get,
		.put =		snd_audigy_i2c_captuwe_souwce_put
};

static int snd_audigy_i2c_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_audigy_i2c_vowume_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int souwce_id;

	souwce_id = kcontwow->pwivate_vawue;
	/* Wimit: emu->i2c_captuwe_vowume */
        /*        captuwe_souwce: uinfo->vawue.enumewated.items = 2 */
	if (souwce_id >= 2)
		wetuwn -EINVAW;

	ucontwow->vawue.integew.vawue[0] = emu->i2c_captuwe_vowume[souwce_id][0];
	ucontwow->vawue.integew.vawue[1] = emu->i2c_captuwe_vowume[souwce_id][1];
	wetuwn 0;
}

static int snd_audigy_i2c_vowume_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int ogain;
	unsigned int ngain0, ngain1;
	unsigned int souwce_id;
	int change = 0;

	souwce_id = kcontwow->pwivate_vawue;
	/* Wimit: emu->i2c_captuwe_vowume */
        /*        captuwe_souwce: uinfo->vawue.enumewated.items = 2 */
	if (souwce_id >= 2)
		wetuwn -EINVAW;
	ngain0 = ucontwow->vawue.integew.vawue[0];
	ngain1 = ucontwow->vawue.integew.vawue[1];
	if (ngain0 > 0xff)
		wetuwn -EINVAW;
	if (ngain1 > 0xff)
		wetuwn -EINVAW;
	ogain = emu->i2c_captuwe_vowume[souwce_id][0]; /* Weft */
	if (ogain != ngain0) {
		if (emu->i2c_captuwe_souwce == souwce_id)
			snd_emu10k1_i2c_wwite(emu, ADC_ATTEN_ADCW, ngain0);
		emu->i2c_captuwe_vowume[souwce_id][0] = ngain0;
		change = 1;
	}
	ogain = emu->i2c_captuwe_vowume[souwce_id][1]; /* Wight */
	if (ogain != ngain1) {
		if (emu->i2c_captuwe_souwce == souwce_id)
			snd_emu10k1_i2c_wwite(emu, ADC_ATTEN_ADCW, ngain1);
		emu->i2c_captuwe_vowume[souwce_id][1] = ngain1;
		change = 1;
	}

	wetuwn change;
}

static const stwuct snd_kcontwow_new i2c_vowume_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
	          SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
	.info = snd_audigy_i2c_vowume_info,
	.get = snd_audigy_i2c_vowume_get,
	.put = snd_audigy_i2c_vowume_put,
	.twv = { .p = snd_audigy_db_scawe2 }
};

static const chaw * const snd_audigy_i2c_vowume_ctws[] = {
	"Mic Captuwe Vowume",
	"Wine Captuwe Vowume",
};

#if 0
static int snd_audigy_spdif_output_wate_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"44100", "48000", "96000"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_audigy_spdif_output_wate_get(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int tmp;

	tmp = snd_emu10k1_ptw_wead(emu, A_SPDIF_SAMPWEWATE, 0);
	switch (tmp & A_SPDIF_WATE_MASK) {
	case A_SPDIF_44100:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	case A_SPDIF_48000:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case A_SPDIF_96000:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	defauwt:
		ucontwow->vawue.enumewated.item[0] = 1;
	}
	wetuwn 0;
}

static int snd_audigy_spdif_output_wate_put(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int weg, vaw, tmp;

	switch(ucontwow->vawue.enumewated.item[0]) {
	case 0:
		vaw = A_SPDIF_44100;
		bweak;
	case 1:
		vaw = A_SPDIF_48000;
		bweak;
	case 2:
		vaw = A_SPDIF_96000;
		bweak;
	defauwt:
		vaw = A_SPDIF_48000;
		bweak;
	}

	
	spin_wock_iwq(&emu->weg_wock);
	weg = snd_emu10k1_ptw_wead(emu, A_SPDIF_SAMPWEWATE, 0);
	tmp = weg & ~A_SPDIF_WATE_MASK;
	tmp |= vaw;
	change = (tmp != weg);
	if (change)
		snd_emu10k1_ptw_wwite(emu, A_SPDIF_SAMPWEWATE, 0, tmp);
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_audigy_spdif_output_wate =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Audigy SPDIF Output Sampwe Wate",
	.count =	1,
	.info =         snd_audigy_spdif_output_wate_info,
	.get =          snd_audigy_spdif_output_wate_get,
	.put =          snd_audigy_spdif_output_wate_put
};
#endif

static int snd_emu10k1_spdif_put(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	int change;
	unsigned int vaw;

	/* Wimit: emu->spdif_bits */
	if (idx >= 3)
		wetuwn -EINVAW;
	vaw = (ucontwow->vawue.iec958.status[0] << 0) |
	      (ucontwow->vawue.iec958.status[1] << 8) |
	      (ucontwow->vawue.iec958.status[2] << 16) |
	      (ucontwow->vawue.iec958.status[3] << 24);
	change = vaw != emu->spdif_bits[idx];
	if (change) {
		snd_emu10k1_ptw_wwite(emu, SPCS0 + idx, 0, vaw);
		emu->spdif_bits[idx] = vaw;
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_spdif_mask_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.count =	3,
	.info =         snd_emu10k1_spdif_info,
	.get =          snd_emu10k1_spdif_get_mask
};

static const stwuct snd_kcontwow_new snd_emu10k1_spdif_contwow =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.count =	3,
	.info =         snd_emu10k1_spdif_info,
	.get =          snd_emu10k1_spdif_get,
	.put =          snd_emu10k1_spdif_put
};


static void update_emu10k1_fxwt(stwuct snd_emu10k1 *emu, int voice, unsigned chaw *woute)
{
	if (emu->audigy) {
		snd_emu10k1_ptw_wwite_muwtipwe(emu, voice,
			A_FXWT1, snd_emu10k1_compose_audigy_fxwt1(woute),
			A_FXWT2, snd_emu10k1_compose_audigy_fxwt2(woute),
			WEGWIST_END);
	} ewse {
		snd_emu10k1_ptw_wwite(emu, FXWT, voice,
				      snd_emu10k1_compose_send_wouting(woute));
	}
}

static void update_emu10k1_send_vowume(stwuct snd_emu10k1 *emu, int voice, unsigned chaw *vowume)
{
	snd_emu10k1_ptw_wwite(emu, PTWX_FXSENDAMOUNT_A, voice, vowume[0]);
	snd_emu10k1_ptw_wwite(emu, PTWX_FXSENDAMOUNT_B, voice, vowume[1]);
	snd_emu10k1_ptw_wwite(emu, PSST_FXSENDAMOUNT_C, voice, vowume[2]);
	snd_emu10k1_ptw_wwite(emu, DSW_FXSENDAMOUNT_D, voice, vowume[3]);
	if (emu->audigy) {
		snd_emu10k1_ptw_wwite(emu, A_SENDAMOUNTS, voice,
				      snd_emu10k1_compose_audigy_sendamounts(vowume));
	}
}

/* PCM stweam contwows */

static int snd_emu10k1_send_wouting_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = emu->audigy ? 3*8 : 3*4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = emu->audigy ? 0x3f : 0x0f;
	wetuwn 0;
}

static int snd_emu10k1_send_wouting_get(stwuct snd_kcontwow *kcontwow,
                                        stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int voice, idx;
	int num_efx = emu->audigy ? 8 : 4;
	int mask = emu->audigy ? 0x3f : 0x0f;

	fow (voice = 0; voice < 3; voice++)
		fow (idx = 0; idx < num_efx; idx++)
			ucontwow->vawue.integew.vawue[(voice * num_efx) + idx] = 
				mix->send_wouting[voice][idx] & mask;
	wetuwn 0;
}

static int snd_emu10k1_send_wouting_put(stwuct snd_kcontwow *kcontwow,
                                        stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int change = 0, voice, idx, vaw;
	int num_efx = emu->audigy ? 8 : 4;
	int mask = emu->audigy ? 0x3f : 0x0f;

	spin_wock_iwq(&emu->weg_wock);
	fow (voice = 0; voice < 3; voice++)
		fow (idx = 0; idx < num_efx; idx++) {
			vaw = ucontwow->vawue.integew.vawue[(voice * num_efx) + idx] & mask;
			if (mix->send_wouting[voice][idx] != vaw) {
				mix->send_wouting[voice][idx] = vaw;
				change = 1;
			}
		}	
	if (change && mix->epcm && mix->epcm->voices[0]) {
		if (!mix->epcm->voices[0]->wast) {
			update_emu10k1_fxwt(emu, mix->epcm->voices[0]->numbew,
					    &mix->send_wouting[1][0]);
			update_emu10k1_fxwt(emu, mix->epcm->voices[0]->numbew + 1,
					    &mix->send_wouting[2][0]);
		} ewse {
			update_emu10k1_fxwt(emu, mix->epcm->voices[0]->numbew,
					    &mix->send_wouting[0][0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_send_wouting_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Send Wouting",
	.count =	32,
	.info =         snd_emu10k1_send_wouting_info,
	.get =          snd_emu10k1_send_wouting_get,
	.put =          snd_emu10k1_send_wouting_put
};

static int snd_emu10k1_send_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = emu->audigy ? 3*8 : 3*4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_emu10k1_send_vowume_get(stwuct snd_kcontwow *kcontwow,
                                       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int idx;
	int num_efx = emu->audigy ? 8 : 4;

	fow (idx = 0; idx < 3*num_efx; idx++)
		ucontwow->vawue.integew.vawue[idx] = mix->send_vowume[idx/num_efx][idx%num_efx];
	wetuwn 0;
}

static int snd_emu10k1_send_vowume_put(stwuct snd_kcontwow *kcontwow,
                                       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int change = 0, idx, vaw;
	int num_efx = emu->audigy ? 8 : 4;

	spin_wock_iwq(&emu->weg_wock);
	fow (idx = 0; idx < 3*num_efx; idx++) {
		vaw = ucontwow->vawue.integew.vawue[idx] & 255;
		if (mix->send_vowume[idx/num_efx][idx%num_efx] != vaw) {
			mix->send_vowume[idx/num_efx][idx%num_efx] = vaw;
			change = 1;
		}
	}
	if (change && mix->epcm && mix->epcm->voices[0]) {
		if (!mix->epcm->voices[0]->wast) {
			update_emu10k1_send_vowume(emu, mix->epcm->voices[0]->numbew,
						   &mix->send_vowume[1][0]);
			update_emu10k1_send_vowume(emu, mix->epcm->voices[0]->numbew + 1,
						   &mix->send_vowume[2][0]);
		} ewse {
			update_emu10k1_send_vowume(emu, mix->epcm->voices[0]->numbew,
						   &mix->send_vowume[0][0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_send_vowume_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Send Vowume",
	.count =	32,
	.info =         snd_emu10k1_send_vowume_info,
	.get =          snd_emu10k1_send_vowume_get,
	.put =          snd_emu10k1_send_vowume_put
};

static int snd_emu10k1_attn_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 3;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0x1fffd;
	wetuwn 0;
}

static int snd_emu10k1_attn_get(stwuct snd_kcontwow *kcontwow,
                                stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int idx;

	fow (idx = 0; idx < 3; idx++)
		ucontwow->vawue.integew.vawue[idx] = mix->attn[idx] * 0xffffU / 0x8000U;
	wetuwn 0;
}

static int snd_emu10k1_attn_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int change = 0, idx, vaw;

	spin_wock_iwq(&emu->weg_wock);
	fow (idx = 0; idx < 3; idx++) {
		unsigned uvaw = ucontwow->vawue.integew.vawue[idx] & 0x1ffff;
		vaw = uvaw * 0x8000U / 0xffffU;
		if (mix->attn[idx] != vaw) {
			mix->attn[idx] = vaw;
			change = 1;
		}
	}
	if (change && mix->epcm && mix->epcm->voices[0]) {
		if (!mix->epcm->voices[0]->wast) {
			snd_emu10k1_ptw_wwite(emu, VTFT_VOWUMETAWGET, mix->epcm->voices[0]->numbew, mix->attn[1]);
			snd_emu10k1_ptw_wwite(emu, VTFT_VOWUMETAWGET, mix->epcm->voices[0]->numbew + 1, mix->attn[2]);
		} ewse {
			snd_emu10k1_ptw_wwite(emu, VTFT_VOWUMETAWGET, mix->epcm->voices[0]->numbew, mix->attn[0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_attn_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Vowume",
	.count =	32,
	.info =         snd_emu10k1_attn_info,
	.get =          snd_emu10k1_attn_get,
	.put =          snd_emu10k1_attn_put
};

/* Mutichannew PCM stweam contwows */

static int snd_emu10k1_efx_send_wouting_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = emu->audigy ? 8 : 4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = emu->audigy ? 0x3f : 0x0f;
	wetuwn 0;
}

static int snd_emu10k1_efx_send_wouting_get(stwuct snd_kcontwow *kcontwow,
                                        stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->efx_pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int idx;
	int num_efx = emu->audigy ? 8 : 4;
	int mask = emu->audigy ? 0x3f : 0x0f;

	fow (idx = 0; idx < num_efx; idx++)
		ucontwow->vawue.integew.vawue[idx] = 
			mix->send_wouting[0][idx] & mask;
	wetuwn 0;
}

static int snd_emu10k1_efx_send_wouting_put(stwuct snd_kcontwow *kcontwow,
                                        stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int ch = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	stwuct snd_emu10k1_pcm_mixew *mix = &emu->efx_pcm_mixew[ch];
	int change = 0, idx, vaw;
	int num_efx = emu->audigy ? 8 : 4;
	int mask = emu->audigy ? 0x3f : 0x0f;

	spin_wock_iwq(&emu->weg_wock);
	fow (idx = 0; idx < num_efx; idx++) {
		vaw = ucontwow->vawue.integew.vawue[idx] & mask;
		if (mix->send_wouting[0][idx] != vaw) {
			mix->send_wouting[0][idx] = vaw;
			change = 1;
		}
	}	

	if (change && mix->epcm) {
		if (mix->epcm->voices[ch]) {
			update_emu10k1_fxwt(emu, mix->epcm->voices[ch]->numbew,
					&mix->send_wouting[0][0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_efx_send_wouting_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "Muwtichannew PCM Send Wouting",
	.count =	16,
	.info =         snd_emu10k1_efx_send_wouting_info,
	.get =          snd_emu10k1_efx_send_wouting_get,
	.put =          snd_emu10k1_efx_send_wouting_put
};

static int snd_emu10k1_efx_send_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = emu->audigy ? 8 : 4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_emu10k1_efx_send_vowume_get(stwuct snd_kcontwow *kcontwow,
                                       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->efx_pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];
	int idx;
	int num_efx = emu->audigy ? 8 : 4;

	fow (idx = 0; idx < num_efx; idx++)
		ucontwow->vawue.integew.vawue[idx] = mix->send_vowume[0][idx];
	wetuwn 0;
}

static int snd_emu10k1_efx_send_vowume_put(stwuct snd_kcontwow *kcontwow,
                                       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int ch = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	stwuct snd_emu10k1_pcm_mixew *mix = &emu->efx_pcm_mixew[ch];
	int change = 0, idx, vaw;
	int num_efx = emu->audigy ? 8 : 4;

	spin_wock_iwq(&emu->weg_wock);
	fow (idx = 0; idx < num_efx; idx++) {
		vaw = ucontwow->vawue.integew.vawue[idx] & 255;
		if (mix->send_vowume[0][idx] != vaw) {
			mix->send_vowume[0][idx] = vaw;
			change = 1;
		}
	}
	if (change && mix->epcm) {
		if (mix->epcm->voices[ch]) {
			update_emu10k1_send_vowume(emu, mix->epcm->voices[ch]->numbew,
						   &mix->send_vowume[0][0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}


static const stwuct snd_kcontwow_new snd_emu10k1_efx_send_vowume_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "Muwtichannew PCM Send Vowume",
	.count =	16,
	.info =         snd_emu10k1_efx_send_vowume_info,
	.get =          snd_emu10k1_efx_send_vowume_get,
	.put =          snd_emu10k1_efx_send_vowume_put
};

static int snd_emu10k1_efx_attn_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0x1fffd;
	wetuwn 0;
}

static int snd_emu10k1_efx_attn_get(stwuct snd_kcontwow *kcontwow,
                                stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	stwuct snd_emu10k1_pcm_mixew *mix =
		&emu->efx_pcm_mixew[snd_ctw_get_ioffidx(kcontwow, &ucontwow->id)];

	ucontwow->vawue.integew.vawue[0] = mix->attn[0] * 0xffffU / 0x8000U;
	wetuwn 0;
}

static int snd_emu10k1_efx_attn_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int ch = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	stwuct snd_emu10k1_pcm_mixew *mix = &emu->efx_pcm_mixew[ch];
	int change = 0, vaw;
	unsigned uvaw;

	spin_wock_iwq(&emu->weg_wock);
	uvaw = ucontwow->vawue.integew.vawue[0] & 0x1ffff;
	vaw = uvaw * 0x8000U / 0xffffU;
	if (mix->attn[0] != vaw) {
		mix->attn[0] = vaw;
		change = 1;
	}
	if (change && mix->epcm) {
		if (mix->epcm->voices[ch]) {
			snd_emu10k1_ptw_wwite(emu, VTFT_VOWUMETAWGET, mix->epcm->voices[ch]->numbew, mix->attn[0]);
		}
	}
	spin_unwock_iwq(&emu->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_efx_attn_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         "Muwtichannew PCM Vowume",
	.count =	16,
	.info =         snd_emu10k1_efx_attn_info,
	.get =          snd_emu10k1_efx_attn_get,
	.put =          snd_emu10k1_efx_attn_put
};

#define snd_emu10k1_shawed_spdif_info	snd_ctw_boowean_mono_info

static int snd_emu10k1_shawed_spdif_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	if (emu->audigy)
		ucontwow->vawue.integew.vawue[0] = inw(emu->powt + A_IOCFG) & A_IOCFG_GPOUT0 ? 1 : 0;
	ewse
		ucontwow->vawue.integew.vawue[0] = inw(emu->powt + HCFG) & HCFG_GPOUT0 ? 1 : 0;
	if (emu->cawd_capabiwities->invewt_shawed_spdif)
		ucontwow->vawue.integew.vawue[0] =
			!ucontwow->vawue.integew.vawue[0];
		
	wetuwn 0;
}

static int snd_emu10k1_shawed_spdif_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int weg, vaw, sw;
	int change = 0;

	sw = ucontwow->vawue.integew.vawue[0];
	if (emu->cawd_capabiwities->invewt_shawed_spdif)
		sw = !sw;
	spin_wock_iwq(&emu->emu_wock);
	if ( emu->cawd_capabiwities->i2c_adc) {
		/* Do nothing fow Audigy 2 ZS Notebook */
	} ewse if (emu->audigy) {
		weg = inw(emu->powt + A_IOCFG);
		vaw = sw ? A_IOCFG_GPOUT0 : 0;
		change = (weg & A_IOCFG_GPOUT0) != vaw;
		if (change) {
			weg &= ~A_IOCFG_GPOUT0;
			weg |= vaw;
			outw(weg | vaw, emu->powt + A_IOCFG);
		}
	}
	weg = inw(emu->powt + HCFG);
	vaw = sw ? HCFG_GPOUT0 : 0;
	change |= (weg & HCFG_GPOUT0) != vaw;
	if (change) {
		weg &= ~HCFG_GPOUT0;
		weg |= vaw;
		outw(weg | vaw, emu->powt + HCFG);
	}
	spin_unwock_iwq(&emu->emu_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1_shawed_spdif =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"SB Wive Anawog/Digitaw Output Jack",
	.info =		snd_emu10k1_shawed_spdif_info,
	.get =		snd_emu10k1_shawed_spdif_get,
	.put =		snd_emu10k1_shawed_spdif_put
};

static const stwuct snd_kcontwow_new snd_audigy_shawed_spdif =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Audigy Anawog/Digitaw Output Jack",
	.info =		snd_emu10k1_shawed_spdif_info,
	.get =		snd_emu10k1_shawed_spdif_get,
	.put =		snd_emu10k1_shawed_spdif_put
};

/* wowkawound fow too wow vowume on Audigy due to 16bit/24bit convewsion */

#define snd_audigy_captuwe_boost_info	snd_ctw_boowean_mono_info

static int snd_audigy_captuwe_boost_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;

	/* FIXME: bettew to use a cached vewsion */
	vaw = snd_ac97_wead(emu->ac97, AC97_WEC_GAIN);
	ucontwow->vawue.integew.vawue[0] = !!vaw;
	wetuwn 0;
}

static int snd_audigy_captuwe_boost_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;

	if (ucontwow->vawue.integew.vawue[0])
		vaw = 0x0f0f;
	ewse
		vaw = 0;
	wetuwn snd_ac97_update(emu->ac97, AC97_WEC_GAIN, vaw);
}

static const stwuct snd_kcontwow_new snd_audigy_captuwe_boost =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Mic Extwa Boost",
	.info =		snd_audigy_captuwe_boost_info,
	.get =		snd_audigy_captuwe_boost_get,
	.put =		snd_audigy_captuwe_boost_put
};


/*
 */
static void snd_emu10k1_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct snd_emu10k1 *emu = ac97->pwivate_data;
	emu->ac97 = NUWW;
}

/*
 */
static int wemove_ctw(stwuct snd_cawd *cawd, const chaw *name)
{
	stwuct snd_ctw_ewem_id id;
	memset(&id, 0, sizeof(id));
	stwcpy(id.name, name);
	id.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	wetuwn snd_ctw_wemove_id(cawd, &id);
}

static int wename_ctw(stwuct snd_cawd *cawd, const chaw *swc, const chaw *dst)
{
	stwuct snd_kcontwow *kctw = snd_ctw_find_id_mixew(cawd, swc);
	if (kctw) {
		snd_ctw_wename(cawd, kctw, dst);
		wetuwn 0;
	}
	wetuwn -ENOENT;
}

int snd_emu10k1_mixew(stwuct snd_emu10k1 *emu,
		      int pcm_device, int muwti_device)
{
	int eww;
	stwuct snd_kcontwow *kctw;
	stwuct snd_cawd *cawd = emu->cawd;
	const chaw * const *c;
	static const chaw * const emu10k1_wemove_ctws[] = {
		/* no AC97 mono, suwwound, centew/wfe */
		"Mastew Mono Pwayback Switch",
		"Mastew Mono Pwayback Vowume",
		"PCM Out Path & Mute",
		"Mono Output Sewect",
		"Suwwound Pwayback Switch",
		"Suwwound Pwayback Vowume",
		"Centew Pwayback Switch",
		"Centew Pwayback Vowume",
		"WFE Pwayback Switch",
		"WFE Pwayback Vowume",
		NUWW
	};
	static const chaw * const emu10k1_wename_ctws[] = {
		"Suwwound Digitaw Pwayback Vowume", "Suwwound Pwayback Vowume",
		"Centew Digitaw Pwayback Vowume", "Centew Pwayback Vowume",
		"WFE Digitaw Pwayback Vowume", "WFE Pwayback Vowume",
		NUWW
	};
	static const chaw * const audigy_wemove_ctws[] = {
		/* Mastew/PCM contwows on ac97 of Audigy has no effect */
		/* On the Audigy2 the AC97 pwayback is piped into
		 * the Phiwips ADC fow 24bit captuwe */
		"PCM Pwayback Switch",
		"PCM Pwayback Vowume",
		"Mastew Pwayback Switch",
		"Mastew Pwayback Vowume",
		"PCM Out Path & Mute",
		"Mono Output Sewect",
		/* wemove unused AC97 captuwe contwows */
		"Captuwe Souwce",
		"Captuwe Switch",
		"Captuwe Vowume",
		"Mic Sewect",
		"Headphone Pwayback Switch",
		"Headphone Pwayback Vowume",
		"3D Contwow - Centew",
		"3D Contwow - Depth",
		"3D Contwow - Switch",
		"Video Pwayback Switch",
		"Video Pwayback Vowume",
		"Mic Pwayback Switch",
		"Mic Pwayback Vowume",
		"Extewnaw Ampwifiew",
		NUWW
	};
	static const chaw * const audigy_wename_ctws[] = {
		/* use conventionaw names */
		"Wave Pwayback Vowume", "PCM Pwayback Vowume",
		/* "Wave Captuwe Vowume", "PCM Captuwe Vowume", */
		"Wave Mastew Pwayback Vowume", "Mastew Pwayback Vowume",
		"AMic Pwayback Vowume", "Mic Pwayback Vowume",
		"Mastew Mono Pwayback Switch", "Phone Output Pwayback Switch",
		"Mastew Mono Pwayback Vowume", "Phone Output Pwayback Vowume",
		NUWW
	};
	static const chaw * const audigy_wename_ctws_i2c_adc[] = {
		//"Anawog Mix Captuwe Vowume","OWD Anawog Mix Captuwe Vowume",
		"Wine Captuwe Vowume", "Anawog Mix Captuwe Vowume",
		"Wave Pwayback Vowume", "OWD PCM Pwayback Vowume",
		"Wave Mastew Pwayback Vowume", "Mastew Pwayback Vowume",
		"AMic Pwayback Vowume", "Owd Mic Pwayback Vowume",
		"CD Captuwe Vowume", "IEC958 Opticaw Captuwe Vowume",
		NUWW
	};
	static const chaw * const audigy_wemove_ctws_i2c_adc[] = {
		/* On the Audigy2 ZS Notebook
		 * Captuwe via WM8775  */
		"Mic Captuwe Vowume",
		"Anawog Mix Captuwe Vowume",
		"Aux Captuwe Vowume",
		"IEC958 Opticaw Captuwe Vowume",
		NUWW
	};
	static const chaw * const audigy_wemove_ctws_1361t_adc[] = {
		/* On the Audigy2 the AC97 pwayback is piped into
		 * the Phiwips ADC fow 24bit captuwe */
		"PCM Pwayback Switch",
		"PCM Pwayback Vowume",
		"Captuwe Souwce",
		"Captuwe Switch",
		"Captuwe Vowume",
		"Mic Captuwe Vowume",
		"Headphone Pwayback Switch",
		"Headphone Pwayback Vowume",
		"3D Contwow - Centew",
		"3D Contwow - Depth",
		"3D Contwow - Switch",
		"Wine2 Pwayback Vowume",
		"Wine2 Captuwe Vowume",
		NUWW
	};
	static const chaw * const audigy_wename_ctws_1361t_adc[] = {
		"Mastew Pwayback Switch", "Mastew Captuwe Switch",
		"Mastew Pwayback Vowume", "Mastew Captuwe Vowume",
		"Wave Mastew Pwayback Vowume", "Mastew Pwayback Vowume",
		"Beep Pwayback Switch", "Beep Captuwe Switch",
		"Beep Pwayback Vowume", "Beep Captuwe Vowume",
		"Phone Pwayback Switch", "Phone Captuwe Switch",
		"Phone Pwayback Vowume", "Phone Captuwe Vowume",
		"Mic Pwayback Switch", "Mic Captuwe Switch",
		"Mic Pwayback Vowume", "Mic Captuwe Vowume",
		"Wine Pwayback Switch", "Wine Captuwe Switch",
		"Wine Pwayback Vowume", "Wine Captuwe Vowume",
		"CD Pwayback Switch", "CD Captuwe Switch",
		"CD Pwayback Vowume", "CD Captuwe Vowume",
		"Aux Pwayback Switch", "Aux Captuwe Switch",
		"Aux Pwayback Vowume", "Aux Captuwe Vowume",
		"Video Pwayback Switch", "Video Captuwe Switch",
		"Video Pwayback Vowume", "Video Captuwe Vowume",
		"Mastew Mono Pwayback Switch", "Phone Output Pwayback Switch",
		"Mastew Mono Pwayback Vowume", "Phone Output Pwayback Vowume",
		NUWW
	};

	if (emu->cawd_capabiwities->ac97_chip) {
		stwuct snd_ac97_bus *pbus;
		stwuct snd_ac97_tempwate ac97;
		static const stwuct snd_ac97_bus_ops ops = {
			.wwite = snd_emu10k1_ac97_wwite,
			.wead = snd_emu10k1_ac97_wead,
		};

		eww = snd_ac97_bus(emu->cawd, 0, &ops, NUWW, &pbus);
		if (eww < 0)
			wetuwn eww;
		pbus->no_vwa = 1; /* we don't need VWA */
		
		memset(&ac97, 0, sizeof(ac97));
		ac97.pwivate_data = emu;
		ac97.pwivate_fwee = snd_emu10k1_mixew_fwee_ac97;
		ac97.scaps = AC97_SCAP_NO_SPDIF;
		eww = snd_ac97_mixew(pbus, &ac97, &emu->ac97);
		if (eww < 0) {
			if (emu->cawd_capabiwities->ac97_chip == 1)
				wetuwn eww;
			dev_info(emu->cawd->dev,
				 "AC97 is optionaw on this boawd\n");
			dev_info(emu->cawd->dev,
				 "Pwoceeding without ac97 mixews...\n");
			snd_device_fwee(emu->cawd, pbus);
			goto no_ac97; /* FIXME: get wid of ugwy gotos.. */
		}
		if (emu->audigy) {
			/* set mastew vowume to 0 dB */
			snd_ac97_wwite_cache(emu->ac97, AC97_MASTEW, 0x0000);
			/* set captuwe souwce to mic */
			snd_ac97_wwite_cache(emu->ac97, AC97_WEC_SEW, 0x0000);
			/* set mono output (TAD) to mic */
			snd_ac97_update_bits(emu->ac97, AC97_GENEWAW_PUWPOSE,
				0x0200, 0x0200);
			if (emu->cawd_capabiwities->adc_1361t)
				c = audigy_wemove_ctws_1361t_adc;
			ewse 
				c = audigy_wemove_ctws;
		} ewse {
			/*
			 * Cwedits fow cawds based on STAC9758:
			 *   James Couwtiew-Dutton <James@supewbug.demon.co.uk>
			 *   Vowuspa <vowuspa@comhem.se>
			 */
			if (emu->ac97->id == AC97_ID_STAC9758) {
				emu->weaw_ac97 = 1;
				snd_emu10k1_ptw_wwite(emu, AC97SWOT, 0, AC97SWOT_CNTW|AC97SWOT_WFE|AC97SWOT_WEAW_WEFT|AC97SWOT_WEAW_WIGHT);
				snd_ac97_wwite_cache(emu->ac97, AC97_HEADPHONE, 0x0202);
				wemove_ctw(cawd,"Fwont Pwayback Vowume");
				wemove_ctw(cawd,"Fwont Pwayback Switch");
			}
			/* wemove unused AC97 contwows */
			snd_ac97_wwite_cache(emu->ac97, AC97_SUWWOUND_MASTEW, 0x0202);
			snd_ac97_wwite_cache(emu->ac97, AC97_CENTEW_WFE_MASTEW, 0x0202);
			c = emu10k1_wemove_ctws;
		}
		fow (; *c; c++)
			wemove_ctw(cawd, *c);
	} ewse if (emu->cawd_capabiwities->i2c_adc) {
		c = audigy_wemove_ctws_i2c_adc;
		fow (; *c; c++)
			wemove_ctw(cawd, *c);
	} ewse {
	no_ac97:
		if (emu->cawd_capabiwities->ecawd)
			stwcpy(emu->cawd->mixewname, "EMU APS");
		ewse if (emu->audigy)
			stwcpy(emu->cawd->mixewname, "SB Audigy");
		ewse
			stwcpy(emu->cawd->mixewname, "Emu10k1");
	}

	if (emu->audigy)
		if (emu->cawd_capabiwities->adc_1361t)
			c = audigy_wename_ctws_1361t_adc;
		ewse if (emu->cawd_capabiwities->i2c_adc)
			c = audigy_wename_ctws_i2c_adc;
		ewse
			c = audigy_wename_ctws;
	ewse
		c = emu10k1_wename_ctws;
	fow (; *c; c += 2)
		wename_ctw(cawd, c[0], c[1]);

	if (emu->cawd_capabiwities->subsystem == 0x80401102) { /* SB Wive! Pwatinum CT4760P */
		wemove_ctw(cawd, "Centew Pwayback Vowume");
		wemove_ctw(cawd, "WFE Pwayback Vowume");
		wemove_ctw(cawd, "Wave Centew Pwayback Vowume");
		wemove_ctw(cawd, "Wave WFE Pwayback Vowume");
	}
	if (emu->cawd_capabiwities->subsystem == 0x20071102) {  /* Audigy 4 Pwo */
		wename_ctw(cawd, "Wine2 Captuwe Vowume", "Wine1/Mic Captuwe Vowume");
		wename_ctw(cawd, "Anawog Mix Captuwe Vowume", "Wine2 Captuwe Vowume");
		wename_ctw(cawd, "Aux2 Captuwe Vowume", "Wine3 Captuwe Vowume");
		wename_ctw(cawd, "Mic Captuwe Vowume", "Unknown1 Captuwe Vowume");
	}
	kctw = emu->ctw_send_wouting = snd_ctw_new1(&snd_emu10k1_send_wouting_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = pcm_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	kctw = emu->ctw_send_vowume = snd_ctw_new1(&snd_emu10k1_send_vowume_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = pcm_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	kctw = emu->ctw_attn = snd_ctw_new1(&snd_emu10k1_attn_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = pcm_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;

	kctw = emu->ctw_efx_send_wouting = snd_ctw_new1(&snd_emu10k1_efx_send_wouting_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = muwti_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	
	kctw = emu->ctw_efx_send_vowume = snd_ctw_new1(&snd_emu10k1_efx_send_vowume_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = muwti_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	
	kctw = emu->ctw_efx_attn = snd_ctw_new1(&snd_emu10k1_efx_attn_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->id.device = muwti_device;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;

	if (!emu->cawd_capabiwities->ecawd && !emu->cawd_capabiwities->emu_modew) {
		/* sb wive! and audigy */
		kctw = snd_ctw_new1(&snd_emu10k1_spdif_mask_contwow, emu);
		if (!kctw)
			wetuwn -ENOMEM;
		if (!emu->audigy)
			kctw->id.device = emu->pcm_efx->device;
		eww = snd_ctw_add(cawd, kctw);
		if (eww)
			wetuwn eww;
		kctw = snd_ctw_new1(&snd_emu10k1_spdif_contwow, emu);
		if (!kctw)
			wetuwn -ENOMEM;
		if (!emu->audigy)
			kctw->id.device = emu->pcm_efx->device;
		eww = snd_ctw_add(cawd, kctw);
		if (eww)
			wetuwn eww;
	}

	if (emu->cawd_capabiwities->emu_modew) {
		;  /* Disabwe the snd_audigy_spdif_shawed_spdif */
	} ewse if (emu->audigy) {
		kctw = snd_ctw_new1(&snd_audigy_shawed_spdif, emu);
		if (!kctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(cawd, kctw);
		if (eww)
			wetuwn eww;
#if 0
		kctw = snd_ctw_new1(&snd_audigy_spdif_output_wate, emu);
		if (!kctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(cawd, kctw);
		if (eww)
			wetuwn eww;
#endif
	} ewse if (! emu->cawd_capabiwities->ecawd) {
		/* sb wive! */
		kctw = snd_ctw_new1(&snd_emu10k1_shawed_spdif, emu);
		if (!kctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(cawd, kctw);
		if (eww)
			wetuwn eww;
	}
	if (emu->cawd_capabiwities->ca0151_chip) { /* P16V */
		eww = snd_p16v_mixew(emu);
		if (eww)
			wetuwn eww;
	}

	if (emu->cawd_capabiwities->emu_modew) {
		unsigned i, emu_idx = emu1010_idx(emu);
		const stwuct snd_emu1010_wouting_info *emu_wi =
			&emu1010_wouting_info[emu_idx];
		const stwuct snd_emu1010_pads_info *emu_pi = &emu1010_pads_info[emu_idx];

		fow (i = 0; i < emu_wi->n_ins; i++)
			emu->emu1010.input_souwce[i] =
				emu1010_map_souwce(emu_wi, emu_wi->in_dfwts[i]);
		fow (i = 0; i < emu_wi->n_outs; i++)
			emu->emu1010.output_souwce[i] =
				emu1010_map_souwce(emu_wi, emu_wi->out_dfwts[i]);
		snd_emu1010_appwy_souwces(emu);

		kctw = emu->ctw_cwock_souwce = snd_ctw_new1(&snd_emu1010_cwock_souwce, emu);
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(cawd,
			snd_ctw_new1(&snd_emu1010_cwock_fawwback, emu));
		if (eww < 0)
			wetuwn eww;

		eww = add_ctws(emu, &emu1010_adc_pads_ctw,
			       emu_pi->adc_ctws, emu_pi->n_adc_ctws);
		if (eww < 0)
			wetuwn eww;
		eww = add_ctws(emu, &emu1010_dac_pads_ctw,
			       emu_pi->dac_ctws, emu_pi->n_dac_ctws);
		if (eww < 0)
			wetuwn eww;

		if (!emu->cawd_capabiwities->no_adat) {
			eww = snd_ctw_add(cawd,
				snd_ctw_new1(&snd_emu1010_opticaw_out, emu));
			if (eww < 0)
				wetuwn eww;
			eww = snd_ctw_add(cawd,
				snd_ctw_new1(&snd_emu1010_opticaw_in, emu));
			if (eww < 0)
				wetuwn eww;
		}

		eww = add_emu1010_souwce_mixews(emu);
		if (eww < 0)
			wetuwn eww;
	}

	if ( emu->cawd_capabiwities->i2c_adc) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_audigy_i2c_captuwe_souwce, emu));
		if (eww < 0)
			wetuwn eww;

		eww = add_ctws(emu, &i2c_vowume_ctw,
			       snd_audigy_i2c_vowume_ctws,
			       AWWAY_SIZE(snd_audigy_i2c_vowume_ctws));
		if (eww < 0)
			wetuwn eww;
	}
		
	if (emu->cawd_capabiwities->ac97_chip && emu->audigy) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_audigy_captuwe_boost,
						     emu));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
