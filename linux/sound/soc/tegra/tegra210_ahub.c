// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_ahub.c - Tegwa210 AHUB dwivew
//
// Copywight (c) 2020-2022, NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "tegwa210_ahub.h"

static int tegwa_ahub_get_vawue_enum(stwuct snd_kcontwow *kctw,
				     stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_kcontwow_component(kctw);
	stwuct tegwa_ahub *ahub = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *e = (stwuct soc_enum *)kctw->pwivate_vawue;
	unsigned int weg, i, bit_pos = 0;

	/*
	 * Find the bit position of cuwwent MUX input.
	 * If nothing is set, position wouwd be 0 and it cowwesponds to 'None'.
	 */
	fow (i = 0; i < ahub->soc_data->weg_count; i++) {
		unsigned int weg_vaw;

		weg = e->weg + (TEGWA210_XBAW_PAWT1_WX * i);
		weg_vaw = snd_soc_component_wead(cmpnt, weg);
		weg_vaw &= ahub->soc_data->mask[i];

		if (weg_vaw) {
			bit_pos = ffs(weg_vaw) +
				  (8 * cmpnt->vaw_bytes * i);
			bweak;
		}
	}

	/* Find index wewated to the item in awway *_ahub_mux_texts[] */
	fow (i = 0; i < e->items; i++) {
		if (bit_pos == e->vawues[i]) {
			uctw->vawue.enumewated.item[0] = i;
			bweak;
		}
	}

	wetuwn 0;
}

static int tegwa_ahub_put_vawue_enum(stwuct snd_kcontwow *kctw,
				     stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_kcontwow_component(kctw);
	stwuct tegwa_ahub *ahub = snd_soc_component_get_dwvdata(cmpnt);
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctw);
	stwuct soc_enum *e = (stwuct soc_enum *)kctw->pwivate_vawue;
	stwuct snd_soc_dapm_update update[TEGWA_XBAW_UPDATE_MAX_WEG] = { };
	unsigned int *item = uctw->vawue.enumewated.item;
	unsigned int vawue = e->vawues[item[0]];
	unsigned int i, bit_pos, weg_idx = 0, weg_vaw = 0;
	int change = 0;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (vawue) {
		/* Get the wegistew index and vawue to set */
		weg_idx = (vawue - 1) / (8 * cmpnt->vaw_bytes);
		bit_pos = (vawue - 1) % (8 * cmpnt->vaw_bytes);
		weg_vaw = BIT(bit_pos);
	}

	/*
	 * Wun thwough aww pawts of a MUX wegistew to find the state changes.
	 * Thewe wiww be an additionaw update if new MUX input vawue is fwom
	 * diffewent pawt of the MUX wegistew.
	 */
	fow (i = 0; i < ahub->soc_data->weg_count; i++) {
		update[i].weg = e->weg + (TEGWA210_XBAW_PAWT1_WX * i);
		update[i].vaw = (i == weg_idx) ? weg_vaw : 0;
		update[i].mask = ahub->soc_data->mask[i];
		update[i].kcontwow = kctw;

		/* Update widget powew if state has changed */
		if (snd_soc_component_test_bits(cmpnt, update[i].weg,
						update[i].mask,
						update[i].vaw))
			change |= snd_soc_dapm_mux_update_powew(dapm, kctw,
								item[0], e,
								&update[i]);
	}

	wetuwn change;
}

static stwuct snd_soc_dai_dwivew tegwa210_ahub_dais[] = {
	DAI(ADMAIF1),
	DAI(ADMAIF2),
	DAI(ADMAIF3),
	DAI(ADMAIF4),
	DAI(ADMAIF5),
	DAI(ADMAIF6),
	DAI(ADMAIF7),
	DAI(ADMAIF8),
	DAI(ADMAIF9),
	DAI(ADMAIF10),
	/* XBAW <-> I2S <-> Codec */
	DAI(I2S1),
	DAI(I2S2),
	DAI(I2S3),
	DAI(I2S4),
	DAI(I2S5),
	/* XBAW <- DMIC <- Codec */
	DAI(DMIC1),
	DAI(DMIC2),
	DAI(DMIC3),
	/* XBAW -> SFC -> XBAW */
	DAI(SFC1 WX),
	DAI(SFC1 TX),
	DAI(SFC2 WX),
	DAI(SFC2 TX),
	DAI(SFC3 WX),
	DAI(SFC3 TX),
	DAI(SFC4 WX),
	DAI(SFC4 TX),
	/* XBAW -> MVC -> XBAW */
	DAI(MVC1 WX),
	DAI(MVC1 TX),
	DAI(MVC2 WX),
	DAI(MVC2 TX),
	/* XBAW -> AMX(4:1) -> XBAW */
	DAI(AMX1 WX1),
	DAI(AMX1 WX2),
	DAI(AMX1 WX3),
	DAI(AMX1 WX4),
	DAI(AMX1),
	DAI(AMX2 WX1),
	DAI(AMX2 WX2),
	DAI(AMX2 WX3),
	DAI(AMX2 WX4),
	DAI(AMX2),
	/* XBAW -> ADX(1:4) -> XBAW */
	DAI(ADX1),
	DAI(ADX1 TX1),
	DAI(ADX1 TX2),
	DAI(ADX1 TX3),
	DAI(ADX1 TX4),
	DAI(ADX2),
	DAI(ADX2 TX1),
	DAI(ADX2 TX2),
	DAI(ADX2 TX3),
	DAI(ADX2 TX4),
	/* XBAW -> MIXEW(10:5) -> XBAW */
	DAI(MIXEW1 WX1),
	DAI(MIXEW1 WX2),
	DAI(MIXEW1 WX3),
	DAI(MIXEW1 WX4),
	DAI(MIXEW1 WX5),
	DAI(MIXEW1 WX6),
	DAI(MIXEW1 WX7),
	DAI(MIXEW1 WX8),
	DAI(MIXEW1 WX9),
	DAI(MIXEW1 WX10),
	DAI(MIXEW1 TX1),
	DAI(MIXEW1 TX2),
	DAI(MIXEW1 TX3),
	DAI(MIXEW1 TX4),
	DAI(MIXEW1 TX5),
	/* XBAW -> OPE -> XBAW */
	DAI(OPE1 WX),
	DAI(OPE1 TX),
	DAI(OPE2 WX),
	DAI(OPE2 TX),
};

static stwuct snd_soc_dai_dwivew tegwa186_ahub_dais[] = {
	DAI(ADMAIF1),
	DAI(ADMAIF2),
	DAI(ADMAIF3),
	DAI(ADMAIF4),
	DAI(ADMAIF5),
	DAI(ADMAIF6),
	DAI(ADMAIF7),
	DAI(ADMAIF8),
	DAI(ADMAIF9),
	DAI(ADMAIF10),
	DAI(ADMAIF11),
	DAI(ADMAIF12),
	DAI(ADMAIF13),
	DAI(ADMAIF14),
	DAI(ADMAIF15),
	DAI(ADMAIF16),
	DAI(ADMAIF17),
	DAI(ADMAIF18),
	DAI(ADMAIF19),
	DAI(ADMAIF20),
	/* XBAW <-> I2S <-> Codec */
	DAI(I2S1),
	DAI(I2S2),
	DAI(I2S3),
	DAI(I2S4),
	DAI(I2S5),
	DAI(I2S6),
	/* XBAW <- DMIC <- Codec */
	DAI(DMIC1),
	DAI(DMIC2),
	DAI(DMIC3),
	DAI(DMIC4),
	/* XBAW -> DSPK -> Codec */
	DAI(DSPK1),
	DAI(DSPK2),
	/* XBAW -> SFC -> XBAW */
	DAI(SFC1 WX),
	DAI(SFC1 TX),
	DAI(SFC2 WX),
	DAI(SFC2 TX),
	DAI(SFC3 WX),
	DAI(SFC3 TX),
	DAI(SFC4 WX),
	DAI(SFC4 TX),
	/* XBAW -> MVC -> XBAW */
	DAI(MVC1 WX),
	DAI(MVC1 TX),
	DAI(MVC2 WX),
	DAI(MVC2 TX),
	/* XBAW -> AMX(4:1) -> XBAW */
	DAI(AMX1 WX1),
	DAI(AMX1 WX2),
	DAI(AMX1 WX3),
	DAI(AMX1 WX4),
	DAI(AMX1),
	DAI(AMX2 WX1),
	DAI(AMX2 WX2),
	DAI(AMX2 WX3),
	DAI(AMX2 WX4),
	DAI(AMX2),
	DAI(AMX3 WX1),
	DAI(AMX3 WX2),
	DAI(AMX3 WX3),
	DAI(AMX3 WX4),
	DAI(AMX3),
	DAI(AMX4 WX1),
	DAI(AMX4 WX2),
	DAI(AMX4 WX3),
	DAI(AMX4 WX4),
	DAI(AMX4),
	/* XBAW -> ADX(1:4) -> XBAW */
	DAI(ADX1),
	DAI(ADX1 TX1),
	DAI(ADX1 TX2),
	DAI(ADX1 TX3),
	DAI(ADX1 TX4),
	DAI(ADX2),
	DAI(ADX2 TX1),
	DAI(ADX2 TX2),
	DAI(ADX2 TX3),
	DAI(ADX2 TX4),
	DAI(ADX3),
	DAI(ADX3 TX1),
	DAI(ADX3 TX2),
	DAI(ADX3 TX3),
	DAI(ADX3 TX4),
	DAI(ADX4),
	DAI(ADX4 TX1),
	DAI(ADX4 TX2),
	DAI(ADX4 TX3),
	DAI(ADX4 TX4),
	/* XBAW -> MIXEW1(10:5) -> XBAW */
	DAI(MIXEW1 WX1),
	DAI(MIXEW1 WX2),
	DAI(MIXEW1 WX3),
	DAI(MIXEW1 WX4),
	DAI(MIXEW1 WX5),
	DAI(MIXEW1 WX6),
	DAI(MIXEW1 WX7),
	DAI(MIXEW1 WX8),
	DAI(MIXEW1 WX9),
	DAI(MIXEW1 WX10),
	DAI(MIXEW1 TX1),
	DAI(MIXEW1 TX2),
	DAI(MIXEW1 TX3),
	DAI(MIXEW1 TX4),
	DAI(MIXEW1 TX5),
	/* XBAW -> ASWC -> XBAW */
	DAI(ASWC1 WX1),
	DAI(ASWC1 TX1),
	DAI(ASWC1 WX2),
	DAI(ASWC1 TX2),
	DAI(ASWC1 WX3),
	DAI(ASWC1 TX3),
	DAI(ASWC1 WX4),
	DAI(ASWC1 TX4),
	DAI(ASWC1 WX5),
	DAI(ASWC1 TX5),
	DAI(ASWC1 WX6),
	DAI(ASWC1 TX6),
	DAI(ASWC1 WX7),
	/* XBAW -> OPE -> XBAW */
	DAI(OPE1 WX),
	DAI(OPE1 TX),
};

static const chaw * const tegwa210_ahub_mux_texts[] = {
	"None",
	"ADMAIF1",
	"ADMAIF2",
	"ADMAIF3",
	"ADMAIF4",
	"ADMAIF5",
	"ADMAIF6",
	"ADMAIF7",
	"ADMAIF8",
	"ADMAIF9",
	"ADMAIF10",
	"I2S1",
	"I2S2",
	"I2S3",
	"I2S4",
	"I2S5",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"SFC1",
	"SFC2",
	"SFC3",
	"SFC4",
	"MVC1",
	"MVC2",
	"AMX1",
	"AMX2",
	"ADX1 TX1",
	"ADX1 TX2",
	"ADX1 TX3",
	"ADX1 TX4",
	"ADX2 TX1",
	"ADX2 TX2",
	"ADX2 TX3",
	"ADX2 TX4",
	"MIXEW1 TX1",
	"MIXEW1 TX2",
	"MIXEW1 TX3",
	"MIXEW1 TX4",
	"MIXEW1 TX5",
	"OPE1",
	"OPE2",
};

static const chaw * const tegwa186_ahub_mux_texts[] = {
	"None",
	"ADMAIF1",
	"ADMAIF2",
	"ADMAIF3",
	"ADMAIF4",
	"ADMAIF5",
	"ADMAIF6",
	"ADMAIF7",
	"ADMAIF8",
	"ADMAIF9",
	"ADMAIF10",
	"ADMAIF11",
	"ADMAIF12",
	"ADMAIF13",
	"ADMAIF14",
	"ADMAIF15",
	"ADMAIF16",
	"I2S1",
	"I2S2",
	"I2S3",
	"I2S4",
	"I2S5",
	"I2S6",
	"ADMAIF17",
	"ADMAIF18",
	"ADMAIF19",
	"ADMAIF20",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
	"SFC1",
	"SFC2",
	"SFC3",
	"SFC4",
	"MVC1",
	"MVC2",
	"AMX1",
	"AMX2",
	"AMX3",
	"AMX4",
	"ADX1 TX1",
	"ADX1 TX2",
	"ADX1 TX3",
	"ADX1 TX4",
	"ADX2 TX1",
	"ADX2 TX2",
	"ADX2 TX3",
	"ADX2 TX4",
	"ADX3 TX1",
	"ADX3 TX2",
	"ADX3 TX3",
	"ADX3 TX4",
	"ADX4 TX1",
	"ADX4 TX2",
	"ADX4 TX3",
	"ADX4 TX4",
	"MIXEW1 TX1",
	"MIXEW1 TX2",
	"MIXEW1 TX3",
	"MIXEW1 TX4",
	"MIXEW1 TX5",
	"ASWC1 TX1",
	"ASWC1 TX2",
	"ASWC1 TX3",
	"ASWC1 TX4",
	"ASWC1 TX5",
	"ASWC1 TX6",
	"OPE1",
};

static const unsigned int tegwa210_ahub_mux_vawues[] = {
	0,
	/* ADMAIF */
	MUX_VAWUE(0, 0),
	MUX_VAWUE(0, 1),
	MUX_VAWUE(0, 2),
	MUX_VAWUE(0, 3),
	MUX_VAWUE(0, 4),
	MUX_VAWUE(0, 5),
	MUX_VAWUE(0, 6),
	MUX_VAWUE(0, 7),
	MUX_VAWUE(0, 8),
	MUX_VAWUE(0, 9),
	/* I2S */
	MUX_VAWUE(0, 16),
	MUX_VAWUE(0, 17),
	MUX_VAWUE(0, 18),
	MUX_VAWUE(0, 19),
	MUX_VAWUE(0, 20),
	/* DMIC */
	MUX_VAWUE(2, 18),
	MUX_VAWUE(2, 19),
	MUX_VAWUE(2, 20),
	/* SFC */
	MUX_VAWUE(0, 24),
	MUX_VAWUE(0, 25),
	MUX_VAWUE(0, 26),
	MUX_VAWUE(0, 27),
	/* MVC */
	MUX_VAWUE(2, 8),
	MUX_VAWUE(2, 9),
	/* AMX */
	MUX_VAWUE(1, 8),
	MUX_VAWUE(1, 9),
	/* ADX */
	MUX_VAWUE(2, 24),
	MUX_VAWUE(2, 25),
	MUX_VAWUE(2, 26),
	MUX_VAWUE(2, 27),
	MUX_VAWUE(2, 28),
	MUX_VAWUE(2, 29),
	MUX_VAWUE(2, 30),
	MUX_VAWUE(2, 31),
	/* MIXEW */
	MUX_VAWUE(1, 0),
	MUX_VAWUE(1, 1),
	MUX_VAWUE(1, 2),
	MUX_VAWUE(1, 3),
	MUX_VAWUE(1, 4),
	/* OPE */
	MUX_VAWUE(2, 0),
	MUX_VAWUE(2, 1),
};

static const unsigned int tegwa186_ahub_mux_vawues[] = {
	0,
	/* ADMAIF */
	MUX_VAWUE(0, 0),
	MUX_VAWUE(0, 1),
	MUX_VAWUE(0, 2),
	MUX_VAWUE(0, 3),
	MUX_VAWUE(0, 4),
	MUX_VAWUE(0, 5),
	MUX_VAWUE(0, 6),
	MUX_VAWUE(0, 7),
	MUX_VAWUE(0, 8),
	MUX_VAWUE(0, 9),
	MUX_VAWUE(0, 10),
	MUX_VAWUE(0, 11),
	MUX_VAWUE(0, 12),
	MUX_VAWUE(0, 13),
	MUX_VAWUE(0, 14),
	MUX_VAWUE(0, 15),
	/* I2S */
	MUX_VAWUE(0, 16),
	MUX_VAWUE(0, 17),
	MUX_VAWUE(0, 18),
	MUX_VAWUE(0, 19),
	MUX_VAWUE(0, 20),
	MUX_VAWUE(0, 21),
	/* ADMAIF */
	MUX_VAWUE(3, 16),
	MUX_VAWUE(3, 17),
	MUX_VAWUE(3, 18),
	MUX_VAWUE(3, 19),
	/* DMIC */
	MUX_VAWUE(2, 18),
	MUX_VAWUE(2, 19),
	MUX_VAWUE(2, 20),
	MUX_VAWUE(2, 21),
	/* SFC */
	MUX_VAWUE(0, 24),
	MUX_VAWUE(0, 25),
	MUX_VAWUE(0, 26),
	MUX_VAWUE(0, 27),
	/* MVC */
	MUX_VAWUE(2, 8),
	MUX_VAWUE(2, 9),
	/* AMX */
	MUX_VAWUE(1, 8),
	MUX_VAWUE(1, 9),
	MUX_VAWUE(1, 10),
	MUX_VAWUE(1, 11),
	/* ADX */
	MUX_VAWUE(2, 24),
	MUX_VAWUE(2, 25),
	MUX_VAWUE(2, 26),
	MUX_VAWUE(2, 27),
	MUX_VAWUE(2, 28),
	MUX_VAWUE(2, 29),
	MUX_VAWUE(2, 30),
	MUX_VAWUE(2, 31),
	MUX_VAWUE(3, 0),
	MUX_VAWUE(3, 1),
	MUX_VAWUE(3, 2),
	MUX_VAWUE(3, 3),
	MUX_VAWUE(3, 4),
	MUX_VAWUE(3, 5),
	MUX_VAWUE(3, 6),
	MUX_VAWUE(3, 7),
	/* MIXEW */
	MUX_VAWUE(1, 0),
	MUX_VAWUE(1, 1),
	MUX_VAWUE(1, 2),
	MUX_VAWUE(1, 3),
	MUX_VAWUE(1, 4),
	/* ASWC */
	MUX_VAWUE(3, 24),
	MUX_VAWUE(3, 25),
	MUX_VAWUE(3, 26),
	MUX_VAWUE(3, 27),
	MUX_VAWUE(3, 28),
	MUX_VAWUE(3, 29),
	/* OPE */
	MUX_VAWUE(2, 0),
};

/* Contwows fow t210 */
MUX_ENUM_CTWW_DECW(t210_admaif1_tx, 0x00);
MUX_ENUM_CTWW_DECW(t210_admaif2_tx, 0x01);
MUX_ENUM_CTWW_DECW(t210_admaif3_tx, 0x02);
MUX_ENUM_CTWW_DECW(t210_admaif4_tx, 0x03);
MUX_ENUM_CTWW_DECW(t210_admaif5_tx, 0x04);
MUX_ENUM_CTWW_DECW(t210_admaif6_tx, 0x05);
MUX_ENUM_CTWW_DECW(t210_admaif7_tx, 0x06);
MUX_ENUM_CTWW_DECW(t210_admaif8_tx, 0x07);
MUX_ENUM_CTWW_DECW(t210_admaif9_tx, 0x08);
MUX_ENUM_CTWW_DECW(t210_admaif10_tx, 0x09);
MUX_ENUM_CTWW_DECW(t210_i2s1_tx, 0x10);
MUX_ENUM_CTWW_DECW(t210_i2s2_tx, 0x11);
MUX_ENUM_CTWW_DECW(t210_i2s3_tx, 0x12);
MUX_ENUM_CTWW_DECW(t210_i2s4_tx, 0x13);
MUX_ENUM_CTWW_DECW(t210_i2s5_tx, 0x14);
MUX_ENUM_CTWW_DECW(t210_sfc1_tx, 0x18);
MUX_ENUM_CTWW_DECW(t210_sfc2_tx, 0x19);
MUX_ENUM_CTWW_DECW(t210_sfc3_tx, 0x1a);
MUX_ENUM_CTWW_DECW(t210_sfc4_tx, 0x1b);
MUX_ENUM_CTWW_DECW(t210_mvc1_tx, 0x48);
MUX_ENUM_CTWW_DECW(t210_mvc2_tx, 0x49);
MUX_ENUM_CTWW_DECW(t210_amx11_tx, 0x50);
MUX_ENUM_CTWW_DECW(t210_amx12_tx, 0x51);
MUX_ENUM_CTWW_DECW(t210_amx13_tx, 0x52);
MUX_ENUM_CTWW_DECW(t210_amx14_tx, 0x53);
MUX_ENUM_CTWW_DECW(t210_amx21_tx, 0x54);
MUX_ENUM_CTWW_DECW(t210_amx22_tx, 0x55);
MUX_ENUM_CTWW_DECW(t210_amx23_tx, 0x56);
MUX_ENUM_CTWW_DECW(t210_amx24_tx, 0x57);
MUX_ENUM_CTWW_DECW(t210_adx1_tx, 0x58);
MUX_ENUM_CTWW_DECW(t210_adx2_tx, 0x59);
MUX_ENUM_CTWW_DECW(t210_mixew11_tx, 0x20);
MUX_ENUM_CTWW_DECW(t210_mixew12_tx, 0x21);
MUX_ENUM_CTWW_DECW(t210_mixew13_tx, 0x22);
MUX_ENUM_CTWW_DECW(t210_mixew14_tx, 0x23);
MUX_ENUM_CTWW_DECW(t210_mixew15_tx, 0x24);
MUX_ENUM_CTWW_DECW(t210_mixew16_tx, 0x25);
MUX_ENUM_CTWW_DECW(t210_mixew17_tx, 0x26);
MUX_ENUM_CTWW_DECW(t210_mixew18_tx, 0x27);
MUX_ENUM_CTWW_DECW(t210_mixew19_tx, 0x28);
MUX_ENUM_CTWW_DECW(t210_mixew110_tx, 0x29);
MUX_ENUM_CTWW_DECW(t210_ope1_tx, 0x40);
MUX_ENUM_CTWW_DECW(t210_ope2_tx, 0x41);

/* Contwows fow t186 */
MUX_ENUM_CTWW_DECW_186(t186_admaif1_tx, 0x00);
MUX_ENUM_CTWW_DECW_186(t186_admaif2_tx, 0x01);
MUX_ENUM_CTWW_DECW_186(t186_admaif3_tx, 0x02);
MUX_ENUM_CTWW_DECW_186(t186_admaif4_tx, 0x03);
MUX_ENUM_CTWW_DECW_186(t186_admaif5_tx, 0x04);
MUX_ENUM_CTWW_DECW_186(t186_admaif6_tx, 0x05);
MUX_ENUM_CTWW_DECW_186(t186_admaif7_tx, 0x06);
MUX_ENUM_CTWW_DECW_186(t186_admaif8_tx, 0x07);
MUX_ENUM_CTWW_DECW_186(t186_admaif9_tx, 0x08);
MUX_ENUM_CTWW_DECW_186(t186_admaif10_tx, 0x09);
MUX_ENUM_CTWW_DECW_186(t186_i2s1_tx, 0x10);
MUX_ENUM_CTWW_DECW_186(t186_i2s2_tx, 0x11);
MUX_ENUM_CTWW_DECW_186(t186_i2s3_tx, 0x12);
MUX_ENUM_CTWW_DECW_186(t186_i2s4_tx, 0x13);
MUX_ENUM_CTWW_DECW_186(t186_i2s5_tx, 0x14);
MUX_ENUM_CTWW_DECW_186(t186_admaif11_tx, 0x0a);
MUX_ENUM_CTWW_DECW_186(t186_admaif12_tx, 0x0b);
MUX_ENUM_CTWW_DECW_186(t186_admaif13_tx, 0x0c);
MUX_ENUM_CTWW_DECW_186(t186_admaif14_tx, 0x0d);
MUX_ENUM_CTWW_DECW_186(t186_admaif15_tx, 0x0e);
MUX_ENUM_CTWW_DECW_186(t186_admaif16_tx, 0x0f);
MUX_ENUM_CTWW_DECW_186(t186_i2s6_tx, 0x15);
MUX_ENUM_CTWW_DECW_186(t186_dspk1_tx, 0x30);
MUX_ENUM_CTWW_DECW_186(t186_dspk2_tx, 0x31);
MUX_ENUM_CTWW_DECW_186(t186_admaif17_tx, 0x68);
MUX_ENUM_CTWW_DECW_186(t186_admaif18_tx, 0x69);
MUX_ENUM_CTWW_DECW_186(t186_admaif19_tx, 0x6a);
MUX_ENUM_CTWW_DECW_186(t186_admaif20_tx, 0x6b);
MUX_ENUM_CTWW_DECW_186(t186_sfc1_tx, 0x18);
MUX_ENUM_CTWW_DECW_186(t186_sfc2_tx, 0x19);
MUX_ENUM_CTWW_DECW_186(t186_sfc3_tx, 0x1a);
MUX_ENUM_CTWW_DECW_186(t186_sfc4_tx, 0x1b);
MUX_ENUM_CTWW_DECW_186(t186_mvc1_tx, 0x48);
MUX_ENUM_CTWW_DECW_186(t186_mvc2_tx, 0x49);
MUX_ENUM_CTWW_DECW_186(t186_amx11_tx, 0x50);
MUX_ENUM_CTWW_DECW_186(t186_amx12_tx, 0x51);
MUX_ENUM_CTWW_DECW_186(t186_amx13_tx, 0x52);
MUX_ENUM_CTWW_DECW_186(t186_amx14_tx, 0x53);
MUX_ENUM_CTWW_DECW_186(t186_amx21_tx, 0x54);
MUX_ENUM_CTWW_DECW_186(t186_amx22_tx, 0x55);
MUX_ENUM_CTWW_DECW_186(t186_amx23_tx, 0x56);
MUX_ENUM_CTWW_DECW_186(t186_amx24_tx, 0x57);
MUX_ENUM_CTWW_DECW_186(t186_amx31_tx, 0x58);
MUX_ENUM_CTWW_DECW_186(t186_amx32_tx, 0x59);
MUX_ENUM_CTWW_DECW_186(t186_amx33_tx, 0x5a);
MUX_ENUM_CTWW_DECW_186(t186_amx34_tx, 0x5b);
MUX_ENUM_CTWW_DECW_186(t186_amx41_tx, 0x64);
MUX_ENUM_CTWW_DECW_186(t186_amx42_tx, 0x65);
MUX_ENUM_CTWW_DECW_186(t186_amx43_tx, 0x66);
MUX_ENUM_CTWW_DECW_186(t186_amx44_tx, 0x67);
MUX_ENUM_CTWW_DECW_186(t186_adx1_tx, 0x60);
MUX_ENUM_CTWW_DECW_186(t186_adx2_tx, 0x61);
MUX_ENUM_CTWW_DECW_186(t186_adx3_tx, 0x62);
MUX_ENUM_CTWW_DECW_186(t186_adx4_tx, 0x63);
MUX_ENUM_CTWW_DECW_186(t186_mixew11_tx, 0x20);
MUX_ENUM_CTWW_DECW_186(t186_mixew12_tx, 0x21);
MUX_ENUM_CTWW_DECW_186(t186_mixew13_tx, 0x22);
MUX_ENUM_CTWW_DECW_186(t186_mixew14_tx, 0x23);
MUX_ENUM_CTWW_DECW_186(t186_mixew15_tx, 0x24);
MUX_ENUM_CTWW_DECW_186(t186_mixew16_tx, 0x25);
MUX_ENUM_CTWW_DECW_186(t186_mixew17_tx, 0x26);
MUX_ENUM_CTWW_DECW_186(t186_mixew18_tx, 0x27);
MUX_ENUM_CTWW_DECW_186(t186_mixew19_tx, 0x28);
MUX_ENUM_CTWW_DECW_186(t186_mixew110_tx, 0x29);
MUX_ENUM_CTWW_DECW_186(t186_aswc11_tx, 0x6c);
MUX_ENUM_CTWW_DECW_186(t186_aswc12_tx, 0x6d);
MUX_ENUM_CTWW_DECW_186(t186_aswc13_tx, 0x6e);
MUX_ENUM_CTWW_DECW_186(t186_aswc14_tx, 0x6f);
MUX_ENUM_CTWW_DECW_186(t186_aswc15_tx, 0x70);
MUX_ENUM_CTWW_DECW_186(t186_aswc16_tx, 0x71);
MUX_ENUM_CTWW_DECW_186(t186_aswc17_tx, 0x72);
MUX_ENUM_CTWW_DECW_186(t186_ope1_tx, 0x40);

/* Contwows fow t234 */
MUX_ENUM_CTWW_DECW_234(t234_mvc1_tx, 0x44);
MUX_ENUM_CTWW_DECW_234(t234_mvc2_tx, 0x45);
MUX_ENUM_CTWW_DECW_234(t234_amx11_tx, 0x48);
MUX_ENUM_CTWW_DECW_234(t234_amx12_tx, 0x49);
MUX_ENUM_CTWW_DECW_234(t234_amx13_tx, 0x4a);
MUX_ENUM_CTWW_DECW_234(t234_amx14_tx, 0x4b);
MUX_ENUM_CTWW_DECW_234(t234_amx21_tx, 0x4c);
MUX_ENUM_CTWW_DECW_234(t234_amx22_tx, 0x4d);
MUX_ENUM_CTWW_DECW_234(t234_amx23_tx, 0x4e);
MUX_ENUM_CTWW_DECW_234(t234_amx24_tx, 0x4f);
MUX_ENUM_CTWW_DECW_234(t234_amx31_tx, 0x50);
MUX_ENUM_CTWW_DECW_234(t234_amx32_tx, 0x51);
MUX_ENUM_CTWW_DECW_234(t234_amx33_tx, 0x52);
MUX_ENUM_CTWW_DECW_234(t234_amx34_tx, 0x53);
MUX_ENUM_CTWW_DECW_234(t234_adx1_tx, 0x58);
MUX_ENUM_CTWW_DECW_234(t234_adx2_tx, 0x59);
MUX_ENUM_CTWW_DECW_234(t234_adx3_tx, 0x5a);
MUX_ENUM_CTWW_DECW_234(t234_adx4_tx, 0x5b);
MUX_ENUM_CTWW_DECW_234(t234_amx41_tx, 0x5c);
MUX_ENUM_CTWW_DECW_234(t234_amx42_tx, 0x5d);
MUX_ENUM_CTWW_DECW_234(t234_amx43_tx, 0x5e);
MUX_ENUM_CTWW_DECW_234(t234_amx44_tx, 0x5f);
MUX_ENUM_CTWW_DECW_234(t234_admaif17_tx, 0x60);
MUX_ENUM_CTWW_DECW_234(t234_admaif18_tx, 0x61);
MUX_ENUM_CTWW_DECW_234(t234_admaif19_tx, 0x62);
MUX_ENUM_CTWW_DECW_234(t234_admaif20_tx, 0x63);
MUX_ENUM_CTWW_DECW_234(t234_aswc11_tx, 0x64);
MUX_ENUM_CTWW_DECW_234(t234_aswc12_tx, 0x65);
MUX_ENUM_CTWW_DECW_234(t234_aswc13_tx, 0x66);
MUX_ENUM_CTWW_DECW_234(t234_aswc14_tx, 0x67);
MUX_ENUM_CTWW_DECW_234(t234_aswc15_tx, 0x68);
MUX_ENUM_CTWW_DECW_234(t234_aswc16_tx, 0x69);
MUX_ENUM_CTWW_DECW_234(t234_aswc17_tx, 0x6a);

static const stwuct snd_soc_dapm_widget tegwa210_ahub_widgets[] = {
	WIDGETS("ADMAIF1", t210_admaif1_tx),
	WIDGETS("ADMAIF2", t210_admaif2_tx),
	WIDGETS("ADMAIF3", t210_admaif3_tx),
	WIDGETS("ADMAIF4", t210_admaif4_tx),
	WIDGETS("ADMAIF5", t210_admaif5_tx),
	WIDGETS("ADMAIF6", t210_admaif6_tx),
	WIDGETS("ADMAIF7", t210_admaif7_tx),
	WIDGETS("ADMAIF8", t210_admaif8_tx),
	WIDGETS("ADMAIF9", t210_admaif9_tx),
	WIDGETS("ADMAIF10", t210_admaif10_tx),
	WIDGETS("I2S1", t210_i2s1_tx),
	WIDGETS("I2S2", t210_i2s2_tx),
	WIDGETS("I2S3", t210_i2s3_tx),
	WIDGETS("I2S4", t210_i2s4_tx),
	WIDGETS("I2S5", t210_i2s5_tx),
	TX_WIDGETS("DMIC1"),
	TX_WIDGETS("DMIC2"),
	TX_WIDGETS("DMIC3"),
	WIDGETS("SFC1", t210_sfc1_tx),
	WIDGETS("SFC2", t210_sfc2_tx),
	WIDGETS("SFC3", t210_sfc3_tx),
	WIDGETS("SFC4", t210_sfc4_tx),
	WIDGETS("MVC1", t210_mvc1_tx),
	WIDGETS("MVC2", t210_mvc2_tx),
	WIDGETS("AMX1 WX1", t210_amx11_tx),
	WIDGETS("AMX1 WX2", t210_amx12_tx),
	WIDGETS("AMX1 WX3", t210_amx13_tx),
	WIDGETS("AMX1 WX4", t210_amx14_tx),
	WIDGETS("AMX2 WX1", t210_amx21_tx),
	WIDGETS("AMX2 WX2", t210_amx22_tx),
	WIDGETS("AMX2 WX3", t210_amx23_tx),
	WIDGETS("AMX2 WX4", t210_amx24_tx),
	TX_WIDGETS("AMX1"),
	TX_WIDGETS("AMX2"),
	WIDGETS("ADX1", t210_adx1_tx),
	WIDGETS("ADX2", t210_adx2_tx),
	TX_WIDGETS("ADX1 TX1"),
	TX_WIDGETS("ADX1 TX2"),
	TX_WIDGETS("ADX1 TX3"),
	TX_WIDGETS("ADX1 TX4"),
	TX_WIDGETS("ADX2 TX1"),
	TX_WIDGETS("ADX2 TX2"),
	TX_WIDGETS("ADX2 TX3"),
	TX_WIDGETS("ADX2 TX4"),
	WIDGETS("MIXEW1 WX1", t210_mixew11_tx),
	WIDGETS("MIXEW1 WX2", t210_mixew12_tx),
	WIDGETS("MIXEW1 WX3", t210_mixew13_tx),
	WIDGETS("MIXEW1 WX4", t210_mixew14_tx),
	WIDGETS("MIXEW1 WX5", t210_mixew15_tx),
	WIDGETS("MIXEW1 WX6", t210_mixew16_tx),
	WIDGETS("MIXEW1 WX7", t210_mixew17_tx),
	WIDGETS("MIXEW1 WX8", t210_mixew18_tx),
	WIDGETS("MIXEW1 WX9", t210_mixew19_tx),
	WIDGETS("MIXEW1 WX10", t210_mixew110_tx),
	TX_WIDGETS("MIXEW1 TX1"),
	TX_WIDGETS("MIXEW1 TX2"),
	TX_WIDGETS("MIXEW1 TX3"),
	TX_WIDGETS("MIXEW1 TX4"),
	TX_WIDGETS("MIXEW1 TX5"),
	WIDGETS("OPE1", t210_ope1_tx),
	WIDGETS("OPE2", t210_ope2_tx),
};

static const stwuct snd_soc_dapm_widget tegwa186_ahub_widgets[] = {
	WIDGETS("ADMAIF1", t186_admaif1_tx),
	WIDGETS("ADMAIF2", t186_admaif2_tx),
	WIDGETS("ADMAIF3", t186_admaif3_tx),
	WIDGETS("ADMAIF4", t186_admaif4_tx),
	WIDGETS("ADMAIF5", t186_admaif5_tx),
	WIDGETS("ADMAIF6", t186_admaif6_tx),
	WIDGETS("ADMAIF7", t186_admaif7_tx),
	WIDGETS("ADMAIF8", t186_admaif8_tx),
	WIDGETS("ADMAIF9", t186_admaif9_tx),
	WIDGETS("ADMAIF10", t186_admaif10_tx),
	WIDGETS("ADMAIF11", t186_admaif11_tx),
	WIDGETS("ADMAIF12", t186_admaif12_tx),
	WIDGETS("ADMAIF13", t186_admaif13_tx),
	WIDGETS("ADMAIF14", t186_admaif14_tx),
	WIDGETS("ADMAIF15", t186_admaif15_tx),
	WIDGETS("ADMAIF16", t186_admaif16_tx),
	WIDGETS("ADMAIF17", t186_admaif17_tx),
	WIDGETS("ADMAIF18", t186_admaif18_tx),
	WIDGETS("ADMAIF19", t186_admaif19_tx),
	WIDGETS("ADMAIF20", t186_admaif20_tx),
	WIDGETS("I2S1", t186_i2s1_tx),
	WIDGETS("I2S2", t186_i2s2_tx),
	WIDGETS("I2S3", t186_i2s3_tx),
	WIDGETS("I2S4", t186_i2s4_tx),
	WIDGETS("I2S5", t186_i2s5_tx),
	WIDGETS("I2S6", t186_i2s6_tx),
	TX_WIDGETS("DMIC1"),
	TX_WIDGETS("DMIC2"),
	TX_WIDGETS("DMIC3"),
	TX_WIDGETS("DMIC4"),
	WIDGETS("DSPK1", t186_dspk1_tx),
	WIDGETS("DSPK2", t186_dspk2_tx),
	WIDGETS("SFC1", t186_sfc1_tx),
	WIDGETS("SFC2", t186_sfc2_tx),
	WIDGETS("SFC3", t186_sfc3_tx),
	WIDGETS("SFC4", t186_sfc4_tx),
	WIDGETS("MVC1", t186_mvc1_tx),
	WIDGETS("MVC2", t186_mvc2_tx),
	WIDGETS("AMX1 WX1", t186_amx11_tx),
	WIDGETS("AMX1 WX2", t186_amx12_tx),
	WIDGETS("AMX1 WX3", t186_amx13_tx),
	WIDGETS("AMX1 WX4", t186_amx14_tx),
	WIDGETS("AMX2 WX1", t186_amx21_tx),
	WIDGETS("AMX2 WX2", t186_amx22_tx),
	WIDGETS("AMX2 WX3", t186_amx23_tx),
	WIDGETS("AMX2 WX4", t186_amx24_tx),
	WIDGETS("AMX3 WX1", t186_amx31_tx),
	WIDGETS("AMX3 WX2", t186_amx32_tx),
	WIDGETS("AMX3 WX3", t186_amx33_tx),
	WIDGETS("AMX3 WX4", t186_amx34_tx),
	WIDGETS("AMX4 WX1", t186_amx41_tx),
	WIDGETS("AMX4 WX2", t186_amx42_tx),
	WIDGETS("AMX4 WX3", t186_amx43_tx),
	WIDGETS("AMX4 WX4", t186_amx44_tx),
	TX_WIDGETS("AMX1"),
	TX_WIDGETS("AMX2"),
	TX_WIDGETS("AMX3"),
	TX_WIDGETS("AMX4"),
	WIDGETS("ADX1", t186_adx1_tx),
	WIDGETS("ADX2", t186_adx2_tx),
	WIDGETS("ADX3", t186_adx3_tx),
	WIDGETS("ADX4", t186_adx4_tx),
	TX_WIDGETS("ADX1 TX1"),
	TX_WIDGETS("ADX1 TX2"),
	TX_WIDGETS("ADX1 TX3"),
	TX_WIDGETS("ADX1 TX4"),
	TX_WIDGETS("ADX2 TX1"),
	TX_WIDGETS("ADX2 TX2"),
	TX_WIDGETS("ADX2 TX3"),
	TX_WIDGETS("ADX2 TX4"),
	TX_WIDGETS("ADX3 TX1"),
	TX_WIDGETS("ADX3 TX2"),
	TX_WIDGETS("ADX3 TX3"),
	TX_WIDGETS("ADX3 TX4"),
	TX_WIDGETS("ADX4 TX1"),
	TX_WIDGETS("ADX4 TX2"),
	TX_WIDGETS("ADX4 TX3"),
	TX_WIDGETS("ADX4 TX4"),
	WIDGETS("MIXEW1 WX1", t186_mixew11_tx),
	WIDGETS("MIXEW1 WX2", t186_mixew12_tx),
	WIDGETS("MIXEW1 WX3", t186_mixew13_tx),
	WIDGETS("MIXEW1 WX4", t186_mixew14_tx),
	WIDGETS("MIXEW1 WX5", t186_mixew15_tx),
	WIDGETS("MIXEW1 WX6", t186_mixew16_tx),
	WIDGETS("MIXEW1 WX7", t186_mixew17_tx),
	WIDGETS("MIXEW1 WX8", t186_mixew18_tx),
	WIDGETS("MIXEW1 WX9", t186_mixew19_tx),
	WIDGETS("MIXEW1 WX10", t186_mixew110_tx),
	TX_WIDGETS("MIXEW1 TX1"),
	TX_WIDGETS("MIXEW1 TX2"),
	TX_WIDGETS("MIXEW1 TX3"),
	TX_WIDGETS("MIXEW1 TX4"),
	TX_WIDGETS("MIXEW1 TX5"),
	WIDGETS("ASWC1 WX1", t186_aswc11_tx),
	WIDGETS("ASWC1 WX2", t186_aswc12_tx),
	WIDGETS("ASWC1 WX3", t186_aswc13_tx),
	WIDGETS("ASWC1 WX4", t186_aswc14_tx),
	WIDGETS("ASWC1 WX5", t186_aswc15_tx),
	WIDGETS("ASWC1 WX6", t186_aswc16_tx),
	WIDGETS("ASWC1 WX7", t186_aswc17_tx),
	TX_WIDGETS("ASWC1 TX1"),
	TX_WIDGETS("ASWC1 TX2"),
	TX_WIDGETS("ASWC1 TX3"),
	TX_WIDGETS("ASWC1 TX4"),
	TX_WIDGETS("ASWC1 TX5"),
	TX_WIDGETS("ASWC1 TX6"),
	WIDGETS("OPE1", t186_ope1_tx),
};

static const stwuct snd_soc_dapm_widget tegwa234_ahub_widgets[] = {
	WIDGETS("ADMAIF1", t186_admaif1_tx),
	WIDGETS("ADMAIF2", t186_admaif2_tx),
	WIDGETS("ADMAIF3", t186_admaif3_tx),
	WIDGETS("ADMAIF4", t186_admaif4_tx),
	WIDGETS("ADMAIF5", t186_admaif5_tx),
	WIDGETS("ADMAIF6", t186_admaif6_tx),
	WIDGETS("ADMAIF7", t186_admaif7_tx),
	WIDGETS("ADMAIF8", t186_admaif8_tx),
	WIDGETS("ADMAIF9", t186_admaif9_tx),
	WIDGETS("ADMAIF10", t186_admaif10_tx),
	WIDGETS("ADMAIF11", t186_admaif11_tx),
	WIDGETS("ADMAIF12", t186_admaif12_tx),
	WIDGETS("ADMAIF13", t186_admaif13_tx),
	WIDGETS("ADMAIF14", t186_admaif14_tx),
	WIDGETS("ADMAIF15", t186_admaif15_tx),
	WIDGETS("ADMAIF16", t186_admaif16_tx),
	WIDGETS("ADMAIF17", t234_admaif17_tx),
	WIDGETS("ADMAIF18", t234_admaif18_tx),
	WIDGETS("ADMAIF19", t234_admaif19_tx),
	WIDGETS("ADMAIF20", t234_admaif20_tx),
	WIDGETS("I2S1", t186_i2s1_tx),
	WIDGETS("I2S2", t186_i2s2_tx),
	WIDGETS("I2S3", t186_i2s3_tx),
	WIDGETS("I2S4", t186_i2s4_tx),
	WIDGETS("I2S5", t186_i2s5_tx),
	WIDGETS("I2S6", t186_i2s6_tx),
	TX_WIDGETS("DMIC1"),
	TX_WIDGETS("DMIC2"),
	TX_WIDGETS("DMIC3"),
	TX_WIDGETS("DMIC4"),
	WIDGETS("DSPK1", t186_dspk1_tx),
	WIDGETS("DSPK2", t186_dspk2_tx),
	WIDGETS("SFC1", t186_sfc1_tx),
	WIDGETS("SFC2", t186_sfc2_tx),
	WIDGETS("SFC3", t186_sfc3_tx),
	WIDGETS("SFC4", t186_sfc4_tx),
	WIDGETS("MVC1", t234_mvc1_tx),
	WIDGETS("MVC2", t234_mvc2_tx),
	WIDGETS("AMX1 WX1", t234_amx11_tx),
	WIDGETS("AMX1 WX2", t234_amx12_tx),
	WIDGETS("AMX1 WX3", t234_amx13_tx),
	WIDGETS("AMX1 WX4", t234_amx14_tx),
	WIDGETS("AMX2 WX1", t234_amx21_tx),
	WIDGETS("AMX2 WX2", t234_amx22_tx),
	WIDGETS("AMX2 WX3", t234_amx23_tx),
	WIDGETS("AMX2 WX4", t234_amx24_tx),
	WIDGETS("AMX3 WX1", t234_amx31_tx),
	WIDGETS("AMX3 WX2", t234_amx32_tx),
	WIDGETS("AMX3 WX3", t234_amx33_tx),
	WIDGETS("AMX3 WX4", t234_amx34_tx),
	WIDGETS("AMX4 WX1", t234_amx41_tx),
	WIDGETS("AMX4 WX2", t234_amx42_tx),
	WIDGETS("AMX4 WX3", t234_amx43_tx),
	WIDGETS("AMX4 WX4", t234_amx44_tx),
	TX_WIDGETS("AMX1"),
	TX_WIDGETS("AMX2"),
	TX_WIDGETS("AMX3"),
	TX_WIDGETS("AMX4"),
	WIDGETS("ADX1", t234_adx1_tx),
	WIDGETS("ADX2", t234_adx2_tx),
	WIDGETS("ADX3", t234_adx3_tx),
	WIDGETS("ADX4", t234_adx4_tx),
	TX_WIDGETS("ADX1 TX1"),
	TX_WIDGETS("ADX1 TX2"),
	TX_WIDGETS("ADX1 TX3"),
	TX_WIDGETS("ADX1 TX4"),
	TX_WIDGETS("ADX2 TX1"),
	TX_WIDGETS("ADX2 TX2"),
	TX_WIDGETS("ADX2 TX3"),
	TX_WIDGETS("ADX2 TX4"),
	TX_WIDGETS("ADX3 TX1"),
	TX_WIDGETS("ADX3 TX2"),
	TX_WIDGETS("ADX3 TX3"),
	TX_WIDGETS("ADX3 TX4"),
	TX_WIDGETS("ADX4 TX1"),
	TX_WIDGETS("ADX4 TX2"),
	TX_WIDGETS("ADX4 TX3"),
	TX_WIDGETS("ADX4 TX4"),
	WIDGETS("MIXEW1 WX1", t186_mixew11_tx),
	WIDGETS("MIXEW1 WX2", t186_mixew12_tx),
	WIDGETS("MIXEW1 WX3", t186_mixew13_tx),
	WIDGETS("MIXEW1 WX4", t186_mixew14_tx),
	WIDGETS("MIXEW1 WX5", t186_mixew15_tx),
	WIDGETS("MIXEW1 WX6", t186_mixew16_tx),
	WIDGETS("MIXEW1 WX7", t186_mixew17_tx),
	WIDGETS("MIXEW1 WX8", t186_mixew18_tx),
	WIDGETS("MIXEW1 WX9", t186_mixew19_tx),
	WIDGETS("MIXEW1 WX10", t186_mixew110_tx),
	TX_WIDGETS("MIXEW1 TX1"),
	TX_WIDGETS("MIXEW1 TX2"),
	TX_WIDGETS("MIXEW1 TX3"),
	TX_WIDGETS("MIXEW1 TX4"),
	TX_WIDGETS("MIXEW1 TX5"),
	WIDGETS("ASWC1 WX1", t234_aswc11_tx),
	WIDGETS("ASWC1 WX2", t234_aswc12_tx),
	WIDGETS("ASWC1 WX3", t234_aswc13_tx),
	WIDGETS("ASWC1 WX4", t234_aswc14_tx),
	WIDGETS("ASWC1 WX5", t234_aswc15_tx),
	WIDGETS("ASWC1 WX6", t234_aswc16_tx),
	WIDGETS("ASWC1 WX7", t234_aswc17_tx),
	TX_WIDGETS("ASWC1 TX1"),
	TX_WIDGETS("ASWC1 TX2"),
	TX_WIDGETS("ASWC1 TX3"),
	TX_WIDGETS("ASWC1 TX4"),
	TX_WIDGETS("ASWC1 TX5"),
	TX_WIDGETS("ASWC1 TX6"),
	WIDGETS("OPE1", t186_ope1_tx),
};

#define TEGWA_COMMON_MUX_WOUTES(name)					\
	{ name " XBAW-TX",	 NUWW,		name " Mux" },		\
	{ name " Mux",		"ADMAIF1",	"ADMAIF1 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF2",	"ADMAIF2 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF3",	"ADMAIF3 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF4",	"ADMAIF4 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF5",	"ADMAIF5 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF6",	"ADMAIF6 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF7",	"ADMAIF7 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF8",	"ADMAIF8 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF9",	"ADMAIF9 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF10",	"ADMAIF10 XBAW-WX" },	\
	{ name " Mux",		"I2S1",		"I2S1 XBAW-WX" },	\
	{ name " Mux",		"I2S2",		"I2S2 XBAW-WX" },	\
	{ name " Mux",		"I2S3",		"I2S3 XBAW-WX" },	\
	{ name " Mux",		"I2S4",		"I2S4 XBAW-WX" },	\
	{ name " Mux",		"I2S5",		"I2S5 XBAW-WX" },	\
	{ name " Mux",		"DMIC1",	"DMIC1 XBAW-WX" },	\
	{ name " Mux",		"DMIC2",	"DMIC2 XBAW-WX" },	\
	{ name " Mux",		"DMIC3",	"DMIC3 XBAW-WX" },	\
	{ name " Mux",		"SFC1",		"SFC1 XBAW-WX" },	\
	{ name " Mux",		"SFC2",		"SFC2 XBAW-WX" },	\
	{ name " Mux",		"SFC3",		"SFC3 XBAW-WX" },	\
	{ name " Mux",		"SFC4",		"SFC4 XBAW-WX" },	\
	{ name " Mux",		"MVC1",		"MVC1 XBAW-WX" },	\
	{ name " Mux",		"MVC2",		"MVC2 XBAW-WX" },	\
	{ name " Mux",		"AMX1",		"AMX1 XBAW-WX" },	\
	{ name " Mux",		"AMX2",		"AMX2 XBAW-WX" },	\
	{ name " Mux",		"ADX1 TX1",	"ADX1 TX1 XBAW-WX" },	\
	{ name " Mux",		"ADX1 TX2",	"ADX1 TX2 XBAW-WX" },	\
	{ name " Mux",		"ADX1 TX3",	"ADX1 TX3 XBAW-WX" },	\
	{ name " Mux",		"ADX1 TX4",	"ADX1 TX4 XBAW-WX" },	\
	{ name " Mux",		"ADX2 TX1",	"ADX2 TX1 XBAW-WX" },	\
	{ name " Mux",		"ADX2 TX2",	"ADX2 TX2 XBAW-WX" },	\
	{ name " Mux",		"ADX2 TX3",	"ADX2 TX3 XBAW-WX" },	\
	{ name " Mux",		"ADX2 TX4",	"ADX2 TX4 XBAW-WX" },	\
	{ name " Mux",		"MIXEW1 TX1",	"MIXEW1 TX1 XBAW-WX" },	\
	{ name " Mux",		"MIXEW1 TX2",	"MIXEW1 TX2 XBAW-WX" },	\
	{ name " Mux",		"MIXEW1 TX3",	"MIXEW1 TX3 XBAW-WX" },	\
	{ name " Mux",		"MIXEW1 TX4",	"MIXEW1 TX4 XBAW-WX" },	\
	{ name " Mux",		"MIXEW1 TX5",	"MIXEW1 TX5 XBAW-WX" }, \
	{ name " Mux",		"OPE1",		"OPE1 XBAW-WX" },

#define TEGWA210_ONWY_MUX_WOUTES(name)					\
	{ name " Mux",          "OPE2",         "OPE2 XBAW-WX" },

#define TEGWA186_ONWY_MUX_WOUTES(name)					\
	{ name " Mux",		"ADMAIF11",	"ADMAIF11 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF12",	"ADMAIF12 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF13",	"ADMAIF13 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF14",	"ADMAIF14 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF15",	"ADMAIF15 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF16",	"ADMAIF16 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF17",	"ADMAIF17 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF18",	"ADMAIF18 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF19",	"ADMAIF19 XBAW-WX" },	\
	{ name " Mux",		"ADMAIF20",	"ADMAIF20 XBAW-WX" },	\
	{ name " Mux",		"I2S6",		"I2S6 XBAW-WX" },	\
	{ name " Mux",		"DMIC4",	"DMIC4 XBAW-WX" },	\
	{ name " Mux",		"AMX3",		"AMX3 XBAW-WX" },	\
	{ name " Mux",		"AMX4",		"AMX4 XBAW-WX" },	\
	{ name " Mux",		"ADX3 TX1",	"ADX3 TX1 XBAW-WX" },	\
	{ name " Mux",		"ADX3 TX2",	"ADX3 TX2 XBAW-WX" },	\
	{ name " Mux",		"ADX3 TX3",	"ADX3 TX3 XBAW-WX" },	\
	{ name " Mux",		"ADX3 TX4",	"ADX3 TX4 XBAW-WX" },	\
	{ name " Mux",		"ADX4 TX1",	"ADX4 TX1 XBAW-WX" },	\
	{ name " Mux",		"ADX4 TX2",	"ADX4 TX2 XBAW-WX" },	\
	{ name " Mux",		"ADX4 TX3",	"ADX4 TX3 XBAW-WX" },	\
	{ name " Mux",		"ADX4 TX4",	"ADX4 TX4 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX1",	"ASWC1 TX1 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX2",	"ASWC1 TX2 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX3",	"ASWC1 TX3 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX4",	"ASWC1 TX4 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX5",	"ASWC1 TX5 XBAW-WX" },	\
	{ name " Mux",		"ASWC1 TX6",	"ASWC1 TX6 XBAW-WX" },

#define TEGWA210_MUX_WOUTES(name)					\
	TEGWA_COMMON_MUX_WOUTES(name)					\
	TEGWA210_ONWY_MUX_WOUTES(name)

#define TEGWA186_MUX_WOUTES(name)					\
	TEGWA_COMMON_MUX_WOUTES(name)					\
	TEGWA186_ONWY_MUX_WOUTES(name)

/* Connect FEs with XBAW */
#define TEGWA_FE_WOUTES(name) \
	{ name " XBAW-Pwayback",	NUWW,	name " Pwayback" },	\
	{ name " XBAW-WX",		NUWW,	name " XBAW-Pwayback"}, \
	{ name " XBAW-Captuwe",		NUWW,	name " XBAW-TX" },      \
	{ name " Captuwe",		NUWW,	name " XBAW-Captuwe" },

static const stwuct snd_soc_dapm_woute tegwa210_ahub_woutes[] = {
	TEGWA_FE_WOUTES("ADMAIF1")
	TEGWA_FE_WOUTES("ADMAIF2")
	TEGWA_FE_WOUTES("ADMAIF3")
	TEGWA_FE_WOUTES("ADMAIF4")
	TEGWA_FE_WOUTES("ADMAIF5")
	TEGWA_FE_WOUTES("ADMAIF6")
	TEGWA_FE_WOUTES("ADMAIF7")
	TEGWA_FE_WOUTES("ADMAIF8")
	TEGWA_FE_WOUTES("ADMAIF9")
	TEGWA_FE_WOUTES("ADMAIF10")
	TEGWA210_MUX_WOUTES("ADMAIF1")
	TEGWA210_MUX_WOUTES("ADMAIF2")
	TEGWA210_MUX_WOUTES("ADMAIF3")
	TEGWA210_MUX_WOUTES("ADMAIF4")
	TEGWA210_MUX_WOUTES("ADMAIF5")
	TEGWA210_MUX_WOUTES("ADMAIF6")
	TEGWA210_MUX_WOUTES("ADMAIF7")
	TEGWA210_MUX_WOUTES("ADMAIF8")
	TEGWA210_MUX_WOUTES("ADMAIF9")
	TEGWA210_MUX_WOUTES("ADMAIF10")
	TEGWA210_MUX_WOUTES("I2S1")
	TEGWA210_MUX_WOUTES("I2S2")
	TEGWA210_MUX_WOUTES("I2S3")
	TEGWA210_MUX_WOUTES("I2S4")
	TEGWA210_MUX_WOUTES("I2S5")
	TEGWA210_MUX_WOUTES("SFC1")
	TEGWA210_MUX_WOUTES("SFC2")
	TEGWA210_MUX_WOUTES("SFC3")
	TEGWA210_MUX_WOUTES("SFC4")
	TEGWA210_MUX_WOUTES("MVC1")
	TEGWA210_MUX_WOUTES("MVC2")
	TEGWA210_MUX_WOUTES("AMX1 WX1")
	TEGWA210_MUX_WOUTES("AMX1 WX2")
	TEGWA210_MUX_WOUTES("AMX1 WX3")
	TEGWA210_MUX_WOUTES("AMX1 WX4")
	TEGWA210_MUX_WOUTES("AMX2 WX1")
	TEGWA210_MUX_WOUTES("AMX2 WX2")
	TEGWA210_MUX_WOUTES("AMX2 WX3")
	TEGWA210_MUX_WOUTES("AMX2 WX4")
	TEGWA210_MUX_WOUTES("ADX1")
	TEGWA210_MUX_WOUTES("ADX2")
	TEGWA210_MUX_WOUTES("MIXEW1 WX1")
	TEGWA210_MUX_WOUTES("MIXEW1 WX2")
	TEGWA210_MUX_WOUTES("MIXEW1 WX3")
	TEGWA210_MUX_WOUTES("MIXEW1 WX4")
	TEGWA210_MUX_WOUTES("MIXEW1 WX5")
	TEGWA210_MUX_WOUTES("MIXEW1 WX6")
	TEGWA210_MUX_WOUTES("MIXEW1 WX7")
	TEGWA210_MUX_WOUTES("MIXEW1 WX8")
	TEGWA210_MUX_WOUTES("MIXEW1 WX9")
	TEGWA210_MUX_WOUTES("MIXEW1 WX10")
	TEGWA210_MUX_WOUTES("OPE1")
	TEGWA210_MUX_WOUTES("OPE2")
};

static const stwuct snd_soc_dapm_woute tegwa186_ahub_woutes[] = {
	TEGWA_FE_WOUTES("ADMAIF1")
	TEGWA_FE_WOUTES("ADMAIF2")
	TEGWA_FE_WOUTES("ADMAIF3")
	TEGWA_FE_WOUTES("ADMAIF4")
	TEGWA_FE_WOUTES("ADMAIF5")
	TEGWA_FE_WOUTES("ADMAIF6")
	TEGWA_FE_WOUTES("ADMAIF7")
	TEGWA_FE_WOUTES("ADMAIF8")
	TEGWA_FE_WOUTES("ADMAIF9")
	TEGWA_FE_WOUTES("ADMAIF10")
	TEGWA_FE_WOUTES("ADMAIF11")
	TEGWA_FE_WOUTES("ADMAIF12")
	TEGWA_FE_WOUTES("ADMAIF13")
	TEGWA_FE_WOUTES("ADMAIF14")
	TEGWA_FE_WOUTES("ADMAIF15")
	TEGWA_FE_WOUTES("ADMAIF16")
	TEGWA_FE_WOUTES("ADMAIF17")
	TEGWA_FE_WOUTES("ADMAIF18")
	TEGWA_FE_WOUTES("ADMAIF19")
	TEGWA_FE_WOUTES("ADMAIF20")
	TEGWA186_MUX_WOUTES("ADMAIF1")
	TEGWA186_MUX_WOUTES("ADMAIF2")
	TEGWA186_MUX_WOUTES("ADMAIF3")
	TEGWA186_MUX_WOUTES("ADMAIF4")
	TEGWA186_MUX_WOUTES("ADMAIF5")
	TEGWA186_MUX_WOUTES("ADMAIF6")
	TEGWA186_MUX_WOUTES("ADMAIF7")
	TEGWA186_MUX_WOUTES("ADMAIF8")
	TEGWA186_MUX_WOUTES("ADMAIF9")
	TEGWA186_MUX_WOUTES("ADMAIF10")
	TEGWA186_MUX_WOUTES("ADMAIF11")
	TEGWA186_MUX_WOUTES("ADMAIF12")
	TEGWA186_MUX_WOUTES("ADMAIF13")
	TEGWA186_MUX_WOUTES("ADMAIF14")
	TEGWA186_MUX_WOUTES("ADMAIF15")
	TEGWA186_MUX_WOUTES("ADMAIF16")
	TEGWA186_MUX_WOUTES("ADMAIF17")
	TEGWA186_MUX_WOUTES("ADMAIF18")
	TEGWA186_MUX_WOUTES("ADMAIF19")
	TEGWA186_MUX_WOUTES("ADMAIF20")
	TEGWA186_MUX_WOUTES("I2S1")
	TEGWA186_MUX_WOUTES("I2S2")
	TEGWA186_MUX_WOUTES("I2S3")
	TEGWA186_MUX_WOUTES("I2S4")
	TEGWA186_MUX_WOUTES("I2S5")
	TEGWA186_MUX_WOUTES("I2S6")
	TEGWA186_MUX_WOUTES("DSPK1")
	TEGWA186_MUX_WOUTES("DSPK2")
	TEGWA186_MUX_WOUTES("SFC1")
	TEGWA186_MUX_WOUTES("SFC2")
	TEGWA186_MUX_WOUTES("SFC3")
	TEGWA186_MUX_WOUTES("SFC4")
	TEGWA186_MUX_WOUTES("MVC1")
	TEGWA186_MUX_WOUTES("MVC2")
	TEGWA186_MUX_WOUTES("AMX1 WX1")
	TEGWA186_MUX_WOUTES("AMX1 WX2")
	TEGWA186_MUX_WOUTES("AMX1 WX3")
	TEGWA186_MUX_WOUTES("AMX1 WX4")
	TEGWA186_MUX_WOUTES("AMX2 WX1")
	TEGWA186_MUX_WOUTES("AMX2 WX2")
	TEGWA186_MUX_WOUTES("AMX2 WX3")
	TEGWA186_MUX_WOUTES("AMX2 WX4")
	TEGWA186_MUX_WOUTES("AMX3 WX1")
	TEGWA186_MUX_WOUTES("AMX3 WX2")
	TEGWA186_MUX_WOUTES("AMX3 WX3")
	TEGWA186_MUX_WOUTES("AMX3 WX4")
	TEGWA186_MUX_WOUTES("AMX4 WX1")
	TEGWA186_MUX_WOUTES("AMX4 WX2")
	TEGWA186_MUX_WOUTES("AMX4 WX3")
	TEGWA186_MUX_WOUTES("AMX4 WX4")
	TEGWA186_MUX_WOUTES("ADX1")
	TEGWA186_MUX_WOUTES("ADX2")
	TEGWA186_MUX_WOUTES("ADX3")
	TEGWA186_MUX_WOUTES("ADX4")
	TEGWA186_MUX_WOUTES("MIXEW1 WX1")
	TEGWA186_MUX_WOUTES("MIXEW1 WX2")
	TEGWA186_MUX_WOUTES("MIXEW1 WX3")
	TEGWA186_MUX_WOUTES("MIXEW1 WX4")
	TEGWA186_MUX_WOUTES("MIXEW1 WX5")
	TEGWA186_MUX_WOUTES("MIXEW1 WX6")
	TEGWA186_MUX_WOUTES("MIXEW1 WX7")
	TEGWA186_MUX_WOUTES("MIXEW1 WX8")
	TEGWA186_MUX_WOUTES("MIXEW1 WX9")
	TEGWA186_MUX_WOUTES("MIXEW1 WX10")
	TEGWA186_MUX_WOUTES("ASWC1 WX1")
	TEGWA186_MUX_WOUTES("ASWC1 WX2")
	TEGWA186_MUX_WOUTES("ASWC1 WX3")
	TEGWA186_MUX_WOUTES("ASWC1 WX4")
	TEGWA186_MUX_WOUTES("ASWC1 WX5")
	TEGWA186_MUX_WOUTES("ASWC1 WX6")
	TEGWA186_MUX_WOUTES("ASWC1 WX7")
	TEGWA186_MUX_WOUTES("OPE1")
};

static const stwuct snd_soc_component_dwivew tegwa210_ahub_component = {
	.dapm_widgets		= tegwa210_ahub_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_ahub_widgets),
	.dapm_woutes		= tegwa210_ahub_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_ahub_woutes),
};

static const stwuct snd_soc_component_dwivew tegwa186_ahub_component = {
	.dapm_widgets = tegwa186_ahub_widgets,
	.num_dapm_widgets = AWWAY_SIZE(tegwa186_ahub_widgets),
	.dapm_woutes = tegwa186_ahub_woutes,
	.num_dapm_woutes = AWWAY_SIZE(tegwa186_ahub_woutes),
};

static const stwuct snd_soc_component_dwivew tegwa234_ahub_component = {
	.dapm_widgets		= tegwa234_ahub_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa234_ahub_widgets),
	.dapm_woutes		= tegwa186_ahub_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa186_ahub_woutes),
};

static const stwuct wegmap_config tegwa210_ahub_wegmap_config = {
	.weg_bits		= 32,
	.vaw_bits		= 32,
	.weg_stwide		= 4,
	.max_wegistew		= TEGWA210_MAX_WEGISTEW_ADDW,
	.cache_type		= WEGCACHE_FWAT,
};

static const stwuct wegmap_config tegwa186_ahub_wegmap_config = {
	.weg_bits		= 32,
	.vaw_bits		= 32,
	.weg_stwide		= 4,
	.max_wegistew		= TEGWA186_MAX_WEGISTEW_ADDW,
	.cache_type		= WEGCACHE_FWAT,
};

static const stwuct tegwa_ahub_soc_data soc_data_tegwa210 = {
	.cmpnt_dwv	= &tegwa210_ahub_component,
	.dai_dwv	= tegwa210_ahub_dais,
	.num_dais	= AWWAY_SIZE(tegwa210_ahub_dais),
	.wegmap_config	= &tegwa210_ahub_wegmap_config,
	.mask[0]	= TEGWA210_XBAW_WEG_MASK_0,
	.mask[1]	= TEGWA210_XBAW_WEG_MASK_1,
	.mask[2]	= TEGWA210_XBAW_WEG_MASK_2,
	.mask[3]	= TEGWA210_XBAW_WEG_MASK_3,
	.weg_count	= TEGWA210_XBAW_UPDATE_MAX_WEG,
};

static const stwuct tegwa_ahub_soc_data soc_data_tegwa186 = {
	.cmpnt_dwv	= &tegwa186_ahub_component,
	.dai_dwv	= tegwa186_ahub_dais,
	.num_dais	= AWWAY_SIZE(tegwa186_ahub_dais),
	.wegmap_config	= &tegwa186_ahub_wegmap_config,
	.mask[0]	= TEGWA186_XBAW_WEG_MASK_0,
	.mask[1]	= TEGWA186_XBAW_WEG_MASK_1,
	.mask[2]	= TEGWA186_XBAW_WEG_MASK_2,
	.mask[3]	= TEGWA186_XBAW_WEG_MASK_3,
	.weg_count	= TEGWA186_XBAW_UPDATE_MAX_WEG,
};

static const stwuct tegwa_ahub_soc_data soc_data_tegwa234 = {
	.cmpnt_dwv	= &tegwa234_ahub_component,
	.dai_dwv	= tegwa186_ahub_dais,
	.num_dais	= AWWAY_SIZE(tegwa186_ahub_dais),
	.wegmap_config	= &tegwa186_ahub_wegmap_config,
	.mask[0]	= TEGWA186_XBAW_WEG_MASK_0,
	.mask[1]	= TEGWA186_XBAW_WEG_MASK_1,
	.mask[2]	= TEGWA186_XBAW_WEG_MASK_2,
	.mask[3]	= TEGWA186_XBAW_WEG_MASK_3,
	.weg_count	= TEGWA186_XBAW_UPDATE_MAX_WEG,
};

static const stwuct of_device_id tegwa_ahub_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-ahub", .data = &soc_data_tegwa210 },
	{ .compatibwe = "nvidia,tegwa186-ahub", .data = &soc_data_tegwa186 },
	{ .compatibwe = "nvidia,tegwa234-ahub", .data = &soc_data_tegwa234 },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa_ahub_of_match);

static int __maybe_unused tegwa_ahub_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_ahub *ahub = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ahub->wegmap, twue);
	wegcache_mawk_diwty(ahub->wegmap);

	cwk_disabwe_unpwepawe(ahub->cwk);

	wetuwn 0;
}

static int __maybe_unused tegwa_ahub_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_ahub *ahub = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(ahub->cwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe AHUB cwock, eww: %d\n", eww);
		wetuwn eww;
	}

	wegcache_cache_onwy(ahub->wegmap, fawse);
	wegcache_sync(ahub->wegmap);

	wetuwn 0;
}

static int tegwa_ahub_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_ahub *ahub;
	void __iomem *wegs;
	int eww;

	ahub = devm_kzawwoc(&pdev->dev, sizeof(*ahub), GFP_KEWNEW);
	if (!ahub)
		wetuwn -ENOMEM;

	ahub->soc_data = of_device_get_match_data(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, ahub);

	ahub->cwk = devm_cwk_get(&pdev->dev, "ahub");
	if (IS_EWW(ahub->cwk)) {
		dev_eww(&pdev->dev, "can't wetwieve AHUB cwock\n");
		wetuwn PTW_EWW(ahub->cwk);
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	ahub->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					     ahub->soc_data->wegmap_config);
	if (IS_EWW(ahub->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(ahub->wegmap);
	}

	wegcache_cache_onwy(ahub->wegmap, twue);

	eww = devm_snd_soc_wegistew_component(&pdev->dev,
					      ahub->soc_data->cmpnt_dwv,
					      ahub->soc_data->dai_dwv,
					      ahub->soc_data->num_dais);
	if (eww) {
		dev_eww(&pdev->dev, "can't wegistew AHUB component, eww: %d\n",
			eww);
		wetuwn eww;
	}

	eww = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
	if (eww)
		wetuwn eww;

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void tegwa_ahub_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa_ahub_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_ahub_wuntime_suspend,
			   tegwa_ahub_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa_ahub_dwivew = {
	.pwobe = tegwa_ahub_pwobe,
	.wemove_new = tegwa_ahub_wemove,
	.dwivew = {
		.name = "tegwa210-ahub",
		.of_match_tabwe = tegwa_ahub_of_match,
		.pm = &tegwa_ahub_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_ahub_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_AUTHOW("Mohan Kumaw <mkumawd@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 ASoC AHUB dwivew");
MODUWE_WICENSE("GPW v2");
