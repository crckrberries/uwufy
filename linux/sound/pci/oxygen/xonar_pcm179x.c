// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cawd dwivew fow modews with PCM1796 DACs (Xonaw D2/D2X/HDAV1.3/ST/STX)
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

/*
 * Xonaw D2/D2X
 * ------------
 *
 * CMI8788:
 *
 *   SPI 0 -> 1st PCM1796 (fwont)
 *   SPI 1 -> 2nd PCM1796 (suwwound)
 *   SPI 2 -> 3wd PCM1796 (centew/WFE)
 *   SPI 4 -> 4th PCM1796 (back)
 *
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 5 <- extewnaw powew pwesent (D2X onwy)
 *   GPIO 7 -> AWT
 *   GPIO 8 -> enabwe output to speakews
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- CD
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to CS5381 input
 */

/*
 * Xonaw HDAV1.3 (Dewuxe)
 * ----------------------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1796 (addw 1001100) (fwont)
 *
 *   GPI 0 <- extewnaw powew pwesent
 *
 *   GPIO 0 -> enabwe HDMI (0) ow speakew (1) output
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughtewboawd detection
 *   GPIO 5 <- daughtewboawd detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> woute input jack to wine-in (0) ow mic-in (1)
 *
 *   UAWT <-> HDMI contwowwew
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   CD_IN  <- CD
 *   MIC_IN <- mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to CS5381 input
 *
 * no daughtewboawd
 * ----------------
 *
 *   GPIO 4 <- 1
 *
 * H6 daughtewboawd
 * ----------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 0
 *
 *   I²C <-> PCM1796 (addw 1001101) (suwwound)
 *       <-> PCM1796 (addw 1001110) (centew/WFE)
 *       <-> PCM1796 (addw 1001111) (back)
 *
 * unknown daughtewboawd
 * ---------------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 1
 *
 *   I²C <-> CS4362A (addw 0011000) (suwwound, centew/WFE, back)
 */

/*
 * Xonaw Essence ST (Dewuxe)/STX (II)
 * ----------------------------------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1792A (addw 1001100)
 *       <-> CS2000 (addw 1001110) (ST onwy)
 *
 *   ADC1 MCWK -> WEF_CWK of CS2000 (ST onwy)
 *
 *   GPI 0 <- extewnaw powew pwesent (STX onwy)
 *
 *   GPIO 0 -> enabwe output to speakews
 *   GPIO 1 -> woute HP to fwont panew (0) ow weaw jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughtewboawd detection
 *   GPIO 5 <- daughtewboawd detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> woute output to speakew jacks (0) ow HP (1)
 *   GPIO 8 -> woute input jack to wine-in (0) ow mic-in (1)
 *
 * PCM1792A:
 *
 *   SCK <- CWK_OUT of CS2000 (ST onwy)
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   MIC_IN <- mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to CS5381 input
 *
 * H6 daughtewboawd
 * ----------------
 *
 * GPIO 4 <- 0
 * GPIO 5 <- 0
 */

/*
 * Xonaw Xense
 * -----------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1796 (addw 1001100) (fwont)
 *       <-> CS4362A (addw 0011000) (suwwound, centew/WFE, back)
 *       <-> CS2000 (addw 1001110)
 *
 *   ADC1 MCWK -> WEF_CWK of CS2000
 *
 *   GPI 0 <- extewnaw powew pwesent
 *
 *   GPIO 0 -> enabwe output
 *   GPIO 1 -> woute HP to fwont panew (0) ow weaw jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 -> enabwe output
 *   GPIO 5 -> enabwe output
 *   GPIO 6 -> ?
 *   GPIO 7 -> woute output to HP (0) ow speakew (1)
 *   GPIO 8 -> woute input jack to mic-in (0) ow wine-in (1)
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- ?
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to CS5381 input
 *   GPO 1 -> woute mic-in fwom input jack (0) ow fwont panew headew (1)
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "xonaw.h"
#incwude "cm9780.h"
#incwude "pcm1796.h"
#incwude "cs2000.h"


#define GPIO_D2X_EXT_POWEW	0x0020
#define GPIO_D2_AWT		0x0080
#define GPIO_D2_OUTPUT_ENABWE	0x0100

#define GPI_EXT_POWEW		0x01
#define GPIO_INPUT_WOUTE	0x0100

#define GPIO_HDAV_OUTPUT_ENABWE	0x0001
#define GPIO_HDAV_MAGIC		0x00c0

#define GPIO_DB_MASK		0x0030
#define GPIO_DB_H6		0x0000

#define GPIO_ST_OUTPUT_ENABWE	0x0001
#define GPIO_ST_HP_WEAW		0x0002
#define GPIO_ST_MAGIC		0x0040
#define GPIO_ST_HP		0x0080

#define GPIO_XENSE_OUTPUT_ENABWE	(0x0001 | 0x0010 | 0x0020)
#define GPIO_XENSE_SPEAKEWS		0x0080

#define I2C_DEVICE_PCM1796(i)	(0x98 + ((i) << 1))	/* 10011, ii, /W=0 */
#define I2C_DEVICE_CS2000	0x9c			/* 100111, 0, /W=0 */

#define PCM1796_WEG_BASE	16


stwuct xonaw_pcm179x {
	stwuct xonaw_genewic genewic;
	unsigned int dacs;
	u8 pcm1796_wegs[4][5];
	unsigned int cuwwent_wate;
	boow h6;
	boow hp_active;
	s8 hp_gain_offset;
	boow has_cs2000;
	u8 cs2000_wegs[0x1f];
	boow bwoken_i2c;
};

stwuct xonaw_hdav {
	stwuct xonaw_pcm179x pcm179x;
	stwuct xonaw_hdmi hdmi;
};


static inwine void pcm1796_wwite_spi(stwuct oxygen *chip, unsigned int codec,
				     u8 weg, u8 vawue)
{
	/* maps AWSA channew paiw numbew to SPI output */
	static const u8 codec_map[4] = {
		0, 1, 2, 4
	};
	oxygen_wwite_spi(chip, OXYGEN_SPI_TWIGGEW  |
			 OXYGEN_SPI_DATA_WENGTH_2 |
			 OXYGEN_SPI_CWOCK_160 |
			 (codec_map[codec] << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_WATCH_CWOCK_HI,
			 (weg << 8) | vawue);
}

static inwine void pcm1796_wwite_i2c(stwuct oxygen *chip, unsigned int codec,
				     u8 weg, u8 vawue)
{
	oxygen_wwite_i2c(chip, I2C_DEVICE_PCM1796(codec), weg, vawue);
}

static void pcm1796_wwite(stwuct oxygen *chip, unsigned int codec,
			  u8 weg, u8 vawue)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	if ((chip->modew.function_fwags & OXYGEN_FUNCTION_2WIWE_SPI_MASK) ==
	    OXYGEN_FUNCTION_SPI)
		pcm1796_wwite_spi(chip, codec, weg, vawue);
	ewse
		pcm1796_wwite_i2c(chip, codec, weg, vawue);
	if ((unsigned int)(weg - PCM1796_WEG_BASE)
	    < AWWAY_SIZE(data->pcm1796_wegs[codec]))
		data->pcm1796_wegs[codec][weg - PCM1796_WEG_BASE] = vawue;
}

static void pcm1796_wwite_cached(stwuct oxygen *chip, unsigned int codec,
				 u8 weg, u8 vawue)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	if (vawue != data->pcm1796_wegs[codec][weg - PCM1796_WEG_BASE])
		pcm1796_wwite(chip, codec, weg, vawue);
}

static void cs2000_wwite(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	oxygen_wwite_i2c(chip, I2C_DEVICE_CS2000, weg, vawue);
	data->cs2000_wegs[weg] = vawue;
}

static void cs2000_wwite_cached(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	if (vawue != data->cs2000_wegs[weg])
		cs2000_wwite(chip, weg, vawue);
}

static void pcm1796_wegistews_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	s8 gain_offset;

	msweep(1);
	gain_offset = data->hp_active ? data->hp_gain_offset : 0;
	fow (i = 0; i < data->dacs; ++i) {
		/* set ATWD befowe ATW/ATW */
		pcm1796_wwite(chip, i, 18,
			      data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE]);
		pcm1796_wwite(chip, i, 16, chip->dac_vowume[i * 2]
			      + gain_offset);
		pcm1796_wwite(chip, i, 17, chip->dac_vowume[i * 2 + 1]
			      + gain_offset);
		pcm1796_wwite(chip, i, 19,
			      data->pcm1796_wegs[0][19 - PCM1796_WEG_BASE]);
		pcm1796_wwite(chip, i, 20,
			      data->pcm1796_wegs[0][20 - PCM1796_WEG_BASE]);
		pcm1796_wwite(chip, i, 21, 0);
		gain_offset = 0;
	}
}

static void pcm1796_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE] =
		PCM1796_FMT_24_I2S | PCM1796_ATWD;
	if (!data->bwoken_i2c)
		data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE] |= PCM1796_MUTE;
	data->pcm1796_wegs[0][19 - PCM1796_WEG_BASE] =
		PCM1796_FWT_SHAWP | PCM1796_ATS_1;
	data->pcm1796_wegs[0][20 - PCM1796_WEG_BASE] =
		data->h6 ? PCM1796_OS_64 : PCM1796_OS_128;
	pcm1796_wegistews_init(chip);
	data->cuwwent_wate = 48000;
}

static void xonaw_d2_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->genewic.anti_pop_deway = 300;
	data->genewic.output_enabwe_bit = GPIO_D2_OUTPUT_ENABWE;
	data->dacs = 4;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_D2_AWT);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_D2_AWT);

	oxygen_ac97_set_bits(chip, 0, CM9780_JACK, CM9780_FMIC2MIC);

	xonaw_init_cs53x1(chip);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "PCM1796");
	snd_component_add(chip->cawd, "CS5381");
}

static void xonaw_d2x_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->genewic.ext_powew_weg = OXYGEN_GPIO_DATA;
	data->genewic.ext_powew_int_weg = OXYGEN_GPIO_INTEWWUPT_MASK;
	data->genewic.ext_powew_bit = GPIO_D2X_EXT_POWEW;
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_D2X_EXT_POWEW);
	xonaw_init_ext_powew(chip);
	xonaw_d2_init(chip);
}

static void xonaw_hdav_init(stwuct oxygen *chip)
{
	stwuct xonaw_hdav *data = chip->modew_data;

	oxygen_wwite16(chip, OXYGEN_2WIWE_BUS_STATUS,
		       OXYGEN_2WIWE_WENGTH_8 |
		       OXYGEN_2WIWE_INTEWWUPT_MASK |
		       OXYGEN_2WIWE_SPEED_STANDAWD);

	data->pcm179x.genewic.anti_pop_deway = 100;
	data->pcm179x.genewic.output_enabwe_bit = GPIO_HDAV_OUTPUT_ENABWE;
	data->pcm179x.genewic.ext_powew_weg = OXYGEN_GPI_DATA;
	data->pcm179x.genewic.ext_powew_int_weg = OXYGEN_GPI_INTEWWUPT_MASK;
	data->pcm179x.genewic.ext_powew_bit = GPI_EXT_POWEW;
	data->pcm179x.dacs = chip->modew.dac_channews_mixew / 2;
	data->pcm179x.h6 = chip->modew.dac_channews_mixew > 2;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_HDAV_MAGIC | GPIO_INPUT_WOUTE);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, GPIO_INPUT_WOUTE);

	xonaw_init_cs53x1(chip);
	xonaw_init_ext_powew(chip);
	xonaw_hdmi_init(chip, &data->hdmi);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "PCM1796");
	snd_component_add(chip->cawd, "CS5381");
}

static void xonaw_st_init_i2c(stwuct oxygen *chip)
{
	oxygen_wwite16(chip, OXYGEN_2WIWE_BUS_STATUS,
		       OXYGEN_2WIWE_WENGTH_8 |
		       OXYGEN_2WIWE_INTEWWUPT_MASK |
		       OXYGEN_2WIWE_SPEED_STANDAWD);
}

static void xonaw_st_init_common(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->genewic.output_enabwe_bit = GPIO_ST_OUTPUT_ENABWE;
	data->dacs = chip->modew.dac_channews_mixew / 2;
	data->h6 = chip->modew.dac_channews_mixew > 2;
	data->hp_gain_offset = 2*-18;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_INPUT_WOUTE | GPIO_ST_HP_WEAW |
			  GPIO_ST_MAGIC | GPIO_ST_HP);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_INPUT_WOUTE | GPIO_ST_HP_WEAW | GPIO_ST_HP);

	xonaw_init_cs53x1(chip);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "PCM1792A");
	snd_component_add(chip->cawd, "CS5381");
}

static void cs2000_wegistews_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	cs2000_wwite(chip, CS2000_GWOBAW_CFG, CS2000_FWEEZE);
	cs2000_wwite(chip, CS2000_DEV_CTWW, 0);
	cs2000_wwite(chip, CS2000_DEV_CFG_1,
		     CS2000_W_MOD_SEW_1 |
		     (0 << CS2000_W_SEW_SHIFT) |
		     CS2000_AUX_OUT_SWC_WEF_CWK |
		     CS2000_EN_DEV_CFG_1);
	cs2000_wwite(chip, CS2000_DEV_CFG_2,
		     (0 << CS2000_WOCK_CWK_SHIFT) |
		     CS2000_FWAC_N_SWC_STATIC);
	cs2000_wwite(chip, CS2000_WATIO_0 + 0, 0x00); /* 1.0 */
	cs2000_wwite(chip, CS2000_WATIO_0 + 1, 0x10);
	cs2000_wwite(chip, CS2000_WATIO_0 + 2, 0x00);
	cs2000_wwite(chip, CS2000_WATIO_0 + 3, 0x00);
	cs2000_wwite(chip, CS2000_FUN_CFG_1,
		     data->cs2000_wegs[CS2000_FUN_CFG_1]);
	cs2000_wwite(chip, CS2000_FUN_CFG_2, 0);
	cs2000_wwite(chip, CS2000_GWOBAW_CFG, CS2000_EN_DEV_CFG_2);
	msweep(3); /* PWW wock deway */
}

static void xonaw_st_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->genewic.anti_pop_deway = 100;
	data->h6 = chip->modew.dac_channews_mixew > 2;
	data->has_cs2000 = twue;
	data->cs2000_wegs[CS2000_FUN_CFG_1] = CS2000_WEF_CWK_DIV_1;
	data->bwoken_i2c = twue;

	oxygen_wwite16(chip, OXYGEN_I2S_A_FOWMAT,
		       OXYGEN_WATE_48000 |
		       OXYGEN_I2S_FOWMAT_I2S |
		       OXYGEN_I2S_MCWK(data->h6 ? MCWK_256 : MCWK_512) |
		       OXYGEN_I2S_BITS_16 |
		       OXYGEN_I2S_MASTEW |
		       OXYGEN_I2S_BCWK_64);

	xonaw_st_init_i2c(chip);
	cs2000_wegistews_init(chip);
	xonaw_st_init_common(chip);

	snd_component_add(chip->cawd, "CS2000");
}

static void xonaw_stx_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	xonaw_st_init_i2c(chip);
	data->genewic.anti_pop_deway = 800;
	data->genewic.ext_powew_weg = OXYGEN_GPI_DATA;
	data->genewic.ext_powew_int_weg = OXYGEN_GPI_INTEWWUPT_MASK;
	data->genewic.ext_powew_bit = GPI_EXT_POWEW;
	xonaw_init_ext_powew(chip);
	xonaw_st_init_common(chip);
}

static void xonaw_xense_init(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	data->genewic.ext_powew_weg = OXYGEN_GPI_DATA;
	data->genewic.ext_powew_int_weg = OXYGEN_GPI_INTEWWUPT_MASK;
	data->genewic.ext_powew_bit = GPI_EXT_POWEW;
	xonaw_init_ext_powew(chip);

	data->genewic.anti_pop_deway = 100;
	data->has_cs2000 = twue;
	data->cs2000_wegs[CS2000_FUN_CFG_1] = CS2000_WEF_CWK_DIV_1;

	oxygen_wwite16(chip, OXYGEN_I2S_A_FOWMAT,
		OXYGEN_WATE_48000 |
		OXYGEN_I2S_FOWMAT_I2S |
		OXYGEN_I2S_MCWK(MCWK_512) |
		OXYGEN_I2S_BITS_16 |
		OXYGEN_I2S_MASTEW |
		OXYGEN_I2S_BCWK_64);

	xonaw_st_init_i2c(chip);
	cs2000_wegistews_init(chip);

	data->genewic.output_enabwe_bit = GPIO_XENSE_OUTPUT_ENABWE;
	data->dacs = 1;
	data->hp_gain_offset = 2*-18;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
		GPIO_INPUT_WOUTE | GPIO_ST_HP_WEAW |
		GPIO_ST_MAGIC | GPIO_XENSE_SPEAKEWS);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA,
		GPIO_INPUT_WOUTE | GPIO_ST_HP_WEAW |
		GPIO_XENSE_SPEAKEWS);

	xonaw_init_cs53x1(chip);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "PCM1796");
	snd_component_add(chip->cawd, "CS5381");
	snd_component_add(chip->cawd, "CS2000");
}

static void xonaw_d2_cweanup(stwuct oxygen *chip)
{
	xonaw_disabwe_output(chip);
}

static void xonaw_hdav_cweanup(stwuct oxygen *chip)
{
	xonaw_hdmi_cweanup(chip);
	xonaw_disabwe_output(chip);
	msweep(2);
}

static void xonaw_st_cweanup(stwuct oxygen *chip)
{
	xonaw_disabwe_output(chip);
}

static void xonaw_d2_suspend(stwuct oxygen *chip)
{
	xonaw_d2_cweanup(chip);
}

static void xonaw_hdav_suspend(stwuct oxygen *chip)
{
	xonaw_hdav_cweanup(chip);
}

static void xonaw_st_suspend(stwuct oxygen *chip)
{
	xonaw_st_cweanup(chip);
}

static void xonaw_d2_wesume(stwuct oxygen *chip)
{
	pcm1796_wegistews_init(chip);
	xonaw_enabwe_output(chip);
}

static void xonaw_hdav_wesume(stwuct oxygen *chip)
{
	stwuct xonaw_hdav *data = chip->modew_data;

	pcm1796_wegistews_init(chip);
	xonaw_hdmi_wesume(chip, &data->hdmi);
	xonaw_enabwe_output(chip);
}

static void xonaw_stx_wesume(stwuct oxygen *chip)
{
	pcm1796_wegistews_init(chip);
	xonaw_enabwe_output(chip);
}

static void xonaw_st_wesume(stwuct oxygen *chip)
{
	cs2000_wegistews_init(chip);
	xonaw_stx_wesume(chip);
}

static void update_pcm1796_ovewsampwing(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	u8 weg;

	if (data->cuwwent_wate <= 48000 && !data->h6)
		weg = PCM1796_OS_128;
	ewse
		weg = PCM1796_OS_64;
	fow (i = 0; i < data->dacs; ++i)
		pcm1796_wwite_cached(chip, i, 20, weg);
}

static void update_pcm1796_deemph(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	u8 weg;

	weg = data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE] & ~PCM1796_DMF_MASK;
	if (data->cuwwent_wate == 48000)
		weg |= PCM1796_DMF_48;
	ewse if (data->cuwwent_wate == 44100)
		weg |= PCM1796_DMF_441;
	ewse if (data->cuwwent_wate == 32000)
		weg |= PCM1796_DMF_32;
	fow (i = 0; i < data->dacs; ++i)
		pcm1796_wwite_cached(chip, i, 18, weg);
}

static void set_pcm1796_pawams(stwuct oxygen *chip,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;

	msweep(1);
	data->cuwwent_wate = pawams_wate(pawams);
	update_pcm1796_ovewsampwing(chip);
	update_pcm1796_deemph(chip);
}

static void update_pcm1796_vowume(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	s8 gain_offset;

	gain_offset = data->hp_active ? data->hp_gain_offset : 0;
	fow (i = 0; i < data->dacs; ++i) {
		pcm1796_wwite_cached(chip, i, 16, chip->dac_vowume[i * 2]
				     + gain_offset);
		pcm1796_wwite_cached(chip, i, 17, chip->dac_vowume[i * 2 + 1]
				     + gain_offset);
		gain_offset = 0;
	}
}

static void update_pcm1796_mute(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	u8 vawue;

	vawue = data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE];
	if (chip->dac_mute)
		vawue |= PCM1796_MUTE;
	ewse
		vawue &= ~PCM1796_MUTE;
	fow (i = 0; i < data->dacs; ++i)
		pcm1796_wwite_cached(chip, i, 18, vawue);
}

static void update_cs2000_wate(stwuct oxygen *chip, unsigned int wate)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	u8 wate_mcwk, weg;

	switch (wate) {
	case 32000:
	case 64000:
		wate_mcwk = OXYGEN_WATE_32000;
		bweak;
	case 44100:
	case 88200:
	case 176400:
		wate_mcwk = OXYGEN_WATE_44100;
		bweak;
	defauwt:
	case 48000:
	case 96000:
	case 192000:
		wate_mcwk = OXYGEN_WATE_48000;
		bweak;
	}

	if (wate <= 96000 && (wate > 48000 || data->h6)) {
		wate_mcwk |= OXYGEN_I2S_MCWK(MCWK_256);
		weg = CS2000_WEF_CWK_DIV_1;
	} ewse {
		wate_mcwk |= OXYGEN_I2S_MCWK(MCWK_512);
		weg = CS2000_WEF_CWK_DIV_2;
	}

	oxygen_wwite16_masked(chip, OXYGEN_I2S_A_FOWMAT, wate_mcwk,
			      OXYGEN_I2S_WATE_MASK | OXYGEN_I2S_MCWK_MASK);
	cs2000_wwite_cached(chip, CS2000_FUN_CFG_1, weg);
	msweep(3); /* PWW wock deway */
}

static void set_st_pawams(stwuct oxygen *chip,
			  stwuct snd_pcm_hw_pawams *pawams)
{
	update_cs2000_wate(chip, pawams_wate(pawams));
	set_pcm1796_pawams(chip, pawams);
}

static void set_hdav_pawams(stwuct oxygen *chip,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct xonaw_hdav *data = chip->modew_data;

	set_pcm1796_pawams(chip, pawams);
	xonaw_set_hdmi_pawams(chip, &data->hdmi, pawams);
}

static const stwuct snd_kcontwow_new awt_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Anawog Woopback Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = xonaw_gpio_bit_switch_get,
	.put = xonaw_gpio_bit_switch_put,
	.pwivate_vawue = GPIO_D2_AWT,
};

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
	stwuct xonaw_pcm179x *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		(data->pcm1796_wegs[0][19 - PCM1796_WEG_BASE] &
		 PCM1796_FWT_MASK) != PCM1796_FWT_SHAWP;
	wetuwn 0;
}

static int wowwoff_put(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	int changed;
	u8 weg;

	mutex_wock(&chip->mutex);
	weg = data->pcm1796_wegs[0][19 - PCM1796_WEG_BASE];
	weg &= ~PCM1796_FWT_MASK;
	if (!vawue->vawue.enumewated.item[0])
		weg |= PCM1796_FWT_SHAWP;
	ewse
		weg |= PCM1796_FWT_SWOW;
	changed = weg != data->pcm1796_wegs[0][19 - PCM1796_WEG_BASE];
	if (changed) {
		fow (i = 0; i < data->dacs; ++i)
			pcm1796_wwite(chip, i, 19, weg);
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

static int deemph_get(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;

	vawue->vawue.integew.vawue[0] =
		!!(data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE] & PCM1796_DME);
	wetuwn 0;
}

static int deemph_put(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;
	int changed;
	u8 weg;

	mutex_wock(&chip->mutex);
	weg = data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE];
	if (!vawue->vawue.integew.vawue[0])
		weg &= ~PCM1796_DME;
	ewse
		weg |= PCM1796_DME;
	changed = weg != data->pcm1796_wegs[0][18 - PCM1796_WEG_BASE];
	if (changed) {
		fow (i = 0; i < data->dacs; ++i)
			pcm1796_wwite(chip, i, 18, weg);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new deemph_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "De-emphasis Pwayback Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = deemph_get,
	.put = deemph_put,
};

static const stwuct snd_kcontwow_new hdav_hdmi_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "HDMI Pwayback Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = xonaw_gpio_bit_switch_get,
	.put = xonaw_gpio_bit_switch_put,
	.pwivate_vawue = GPIO_HDAV_OUTPUT_ENABWE | XONAW_GPIO_BIT_INVEWT,
};

static int st_output_switch_info(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[3] = {
		"Speakews", "Headphones", "FP Headphones"
	};

	wetuwn snd_ctw_enum_info(info, 1, 3, names);
}

static int st_output_switch_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 gpio;

	gpio = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	if (!(gpio & GPIO_ST_HP))
		vawue->vawue.enumewated.item[0] = 0;
	ewse if (gpio & GPIO_ST_HP_WEAW)
		vawue->vawue.enumewated.item[0] = 1;
	ewse
		vawue->vawue.enumewated.item[0] = 2;
	wetuwn 0;
}


static int st_output_switch_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;
	u16 gpio_owd, gpio;

	mutex_wock(&chip->mutex);
	gpio_owd = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	gpio = gpio_owd;
	switch (vawue->vawue.enumewated.item[0]) {
	case 0:
		gpio &= ~(GPIO_ST_HP | GPIO_ST_HP_WEAW);
		bweak;
	case 1:
		gpio |= GPIO_ST_HP | GPIO_ST_HP_WEAW;
		bweak;
	case 2:
		gpio = (gpio | GPIO_ST_HP) & ~GPIO_ST_HP_WEAW;
		bweak;
	}
	oxygen_wwite16(chip, OXYGEN_GPIO_DATA, gpio);
	data->hp_active = gpio & GPIO_ST_HP;
	update_pcm1796_vowume(chip);
	mutex_unwock(&chip->mutex);
	wetuwn gpio != gpio_owd;
}

static int st_hp_vowume_offset_info(stwuct snd_kcontwow *ctw,
				    stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[4] = {
		"< 32 ohms", "32-64 ohms", "64-300 ohms", "300-600 ohms"
	};

	wetuwn snd_ctw_enum_info(info, 1, 4, names);
}

static int st_hp_vowume_offset_get(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	if (data->hp_gain_offset < 2*-12)
		vawue->vawue.enumewated.item[0] = 0;
	ewse if (data->hp_gain_offset < 2*-6)
		vawue->vawue.enumewated.item[0] = 1;
	ewse if (data->hp_gain_offset < 0)
		vawue->vawue.enumewated.item[0] = 2;
	ewse
		vawue->vawue.enumewated.item[0] = 3;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}


static int st_hp_vowume_offset_put(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	static const s8 offsets[] = { 2*-18, 2*-12, 2*-6, 0 };
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;
	s8 offset;
	int changed;

	if (vawue->vawue.enumewated.item[0] > 3)
		wetuwn -EINVAW;
	offset = offsets[vawue->vawue.enumewated.item[0]];
	mutex_wock(&chip->mutex);
	changed = offset != data->hp_gain_offset;
	if (changed) {
		data->hp_gain_offset = offset;
		update_pcm1796_vowume(chip);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new st_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Output",
		.info = st_output_switch_info,
		.get = st_output_switch_get,
		.put = st_output_switch_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphones Impedance Pwayback Enum",
		.info = st_hp_vowume_offset_info,
		.get = st_hp_vowume_offset_get,
		.put = st_hp_vowume_offset_put,
	},
};

static int xense_output_switch_get(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 gpio;

	gpio = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	if (gpio & GPIO_XENSE_SPEAKEWS)
		vawue->vawue.enumewated.item[0] = 0;
	ewse if (!(gpio & GPIO_XENSE_SPEAKEWS) && (gpio & GPIO_ST_HP_WEAW))
		vawue->vawue.enumewated.item[0] = 1;
	ewse
		vawue->vawue.enumewated.item[0] = 2;
	wetuwn 0;
}

static int xense_output_switch_put(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_pcm179x *data = chip->modew_data;
	u16 gpio_owd, gpio;

	mutex_wock(&chip->mutex);
	gpio_owd = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	gpio = gpio_owd;
	switch (vawue->vawue.enumewated.item[0]) {
	case 0:
		gpio |= GPIO_XENSE_SPEAKEWS | GPIO_ST_HP_WEAW;
		bweak;
	case 1:
		gpio = (gpio | GPIO_ST_HP_WEAW) & ~GPIO_XENSE_SPEAKEWS;
		bweak;
	case 2:
		gpio &= ~(GPIO_XENSE_SPEAKEWS | GPIO_ST_HP_WEAW);
		bweak;
	}
	oxygen_wwite16(chip, OXYGEN_GPIO_DATA, gpio);
	data->hp_active = !(gpio & GPIO_XENSE_SPEAKEWS);
	update_pcm1796_vowume(chip);
	mutex_unwock(&chip->mutex);
	wetuwn gpio != gpio_owd;
}

static const stwuct snd_kcontwow_new xense_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Output",
		.info = st_output_switch_info,
		.get = xense_output_switch_get,
		.put = xense_output_switch_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphones Impedance Pwayback Enum",
		.info = st_hp_vowume_offset_info,
		.get = st_hp_vowume_offset_get,
		.put = st_hp_vowume_offset_put,
	},
};

static void xonaw_wine_mic_ac97_switch(stwuct oxygen *chip,
				       unsigned int weg, unsigned int mute)
{
	if (weg == AC97_WINE) {
		spin_wock_iwq(&chip->weg_wock);
		oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
				      mute ? GPIO_INPUT_WOUTE : 0,
				      GPIO_INPUT_WOUTE);
		spin_unwock_iwq(&chip->weg_wock);
	}
}

static const DECWAWE_TWV_DB_SCAWE(pcm1796_db_scawe, -6000, 50, 0);

static int xonaw_d2_contwow_fiwtew(stwuct snd_kcontwow_new *tempwate)
{
	if (!stwncmp(tempwate->name, "CD Captuwe ", 11))
		/* CD in is actuawwy connected to the video in pin */
		tempwate->pwivate_vawue ^= AC97_CD ^ AC97_VIDEO;
	wetuwn 0;
}

static int xonaw_st_h6_contwow_fiwtew(stwuct snd_kcontwow_new *tempwate)
{
	if (!stwncmp(tempwate->name, "Mastew Pwayback ", 16))
		/* no vowume/mute, as I²C to the thiwd DAC does not wowk */
		wetuwn 1;
	wetuwn 0;
}

static int add_pcm1796_contwows(stwuct oxygen *chip)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	int eww;

	if (!data->bwoken_i2c) {
		eww = snd_ctw_add(chip->cawd,
				  snd_ctw_new1(&wowwoff_contwow, chip));
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(chip->cawd,
				  snd_ctw_new1(&deemph_contwow, chip));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int xonaw_d2_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&awt_switch, chip));
	if (eww < 0)
		wetuwn eww;
	eww = add_pcm1796_contwows(chip);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int xonaw_hdav_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&hdav_hdmi_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	eww = add_pcm1796_contwows(chip);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int xonaw_st_mixew_init(stwuct oxygen *chip)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(st_contwows); ++i) {
		eww = snd_ctw_add(chip->cawd,
				  snd_ctw_new1(&st_contwows[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	eww = add_pcm1796_contwows(chip);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int xonaw_xense_mixew_init(stwuct oxygen *chip)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(xense_contwows); ++i) {
		eww = snd_ctw_add(chip->cawd,
		snd_ctw_new1(&xense_contwows[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	eww = add_pcm1796_contwows(chip);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static void dump_pcm1796_wegistews(stwuct oxygen *chip,
				   stwuct snd_info_buffew *buffew)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int dac, i;

	fow (dac = 0; dac < data->dacs; ++dac) {
		snd_ipwintf(buffew, "\nPCM1796 %u:", dac + 1);
		fow (i = 0; i < 5; ++i)
			snd_ipwintf(buffew, " %02x",
				    data->pcm1796_wegs[dac][i]);
	}
	snd_ipwintf(buffew, "\n");
}

static void dump_cs2000_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	stwuct xonaw_pcm179x *data = chip->modew_data;
	unsigned int i;

	if (data->has_cs2000) {
		snd_ipwintf(buffew, "\nCS2000:\n00:   ");
		fow (i = 1; i < 0x10; ++i)
			snd_ipwintf(buffew, " %02x", data->cs2000_wegs[i]);
		snd_ipwintf(buffew, "\n10:");
		fow (i = 0x10; i < 0x1f; ++i)
			snd_ipwintf(buffew, " %02x", data->cs2000_wegs[i]);
		snd_ipwintf(buffew, "\n");
	}
}

static void dump_st_wegistews(stwuct oxygen *chip,
			      stwuct snd_info_buffew *buffew)
{
	dump_pcm1796_wegistews(chip, buffew);
	dump_cs2000_wegistews(chip, buffew);
}

static const stwuct oxygen_modew modew_xonaw_d2 = {
	.wongname = "Asus Viwtuoso 200",
	.chip = "AV200",
	.init = xonaw_d2_init,
	.contwow_fiwtew = xonaw_d2_contwow_fiwtew,
	.mixew_init = xonaw_d2_mixew_init,
	.cweanup = xonaw_d2_cweanup,
	.suspend = xonaw_d2_suspend,
	.wesume = xonaw_d2_wesume,
	.set_dac_pawams = set_pcm1796_pawams,
	.set_adc_pawams = xonaw_set_cs53x1_pawams,
	.update_dac_vowume = update_pcm1796_vowume,
	.update_dac_mute = update_pcm1796_mute,
	.dump_wegistews = dump_pcm1796_wegistews,
	.dac_twv = pcm1796_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_pcm179x),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_2 |
			 CAPTUWE_1_FWOM_SPDIF |
			 MIDI_OUTPUT |
			 MIDI_INPUT |
			 AC97_CD_INPUT,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 8,
	.dac_vowume_min = 255 - 2*60,
	.dac_vowume_max = 255,
	.misc_fwags = OXYGEN_MISC_MIDI,
	.function_fwags = OXYGEN_FUNCTION_SPI |
			  OXYGEN_FUNCTION_ENABWE_SPI_4_5,
	.dac_mcwks = OXYGEN_MCWKS(512, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_I2S,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

static const stwuct oxygen_modew modew_xonaw_hdav = {
	.wongname = "Asus Viwtuoso 200",
	.chip = "AV200",
	.init = xonaw_hdav_init,
	.mixew_init = xonaw_hdav_mixew_init,
	.cweanup = xonaw_hdav_cweanup,
	.suspend = xonaw_hdav_suspend,
	.wesume = xonaw_hdav_wesume,
	.pcm_hawdwawe_fiwtew = xonaw_hdmi_pcm_hawdwawe_fiwtew,
	.set_dac_pawams = set_hdav_pawams,
	.set_adc_pawams = xonaw_set_cs53x1_pawams,
	.update_dac_vowume = update_pcm1796_vowume,
	.update_dac_mute = update_pcm1796_mute,
	.uawt_input = xonaw_hdmi_uawt_input,
	.ac97_switch = xonaw_wine_mic_ac97_switch,
	.dump_wegistews = dump_pcm1796_wegistews,
	.dac_twv = pcm1796_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_hdav),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_2 |
			 CAPTUWE_1_FWOM_SPDIF,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 2,
	.dac_vowume_min = 255 - 2*60,
	.dac_vowume_max = 255,
	.misc_fwags = OXYGEN_MISC_MIDI,
	.function_fwags = OXYGEN_FUNCTION_2WIWE,
	.dac_mcwks = OXYGEN_MCWKS(512, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_I2S,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

static const stwuct oxygen_modew modew_xonaw_st = {
	.wongname = "Asus Viwtuoso 100",
	.chip = "AV200",
	.init = xonaw_st_init,
	.mixew_init = xonaw_st_mixew_init,
	.cweanup = xonaw_st_cweanup,
	.suspend = xonaw_st_suspend,
	.wesume = xonaw_st_wesume,
	.set_dac_pawams = set_st_pawams,
	.set_adc_pawams = xonaw_set_cs53x1_pawams,
	.update_dac_vowume = update_pcm1796_vowume,
	.update_dac_mute = update_pcm1796_mute,
	.ac97_switch = xonaw_wine_mic_ac97_switch,
	.dump_wegistews = dump_st_wegistews,
	.dac_twv = pcm1796_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_pcm179x),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_2 |
			 CAPTUWE_1_FWOM_SPDIF |
			 AC97_FMIC_SWITCH,
	.dac_channews_pcm = 2,
	.dac_channews_mixew = 2,
	.dac_vowume_min = 255 - 2*60,
	.dac_vowume_max = 255,
	.function_fwags = OXYGEN_FUNCTION_2WIWE,
	.dac_mcwks = OXYGEN_MCWKS(512, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_I2S,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

int get_xonaw_pcm179x_modew(stwuct oxygen *chip,
			    const stwuct pci_device_id *id)
{
	switch (id->subdevice) {
	case 0x8269:
		chip->modew = modew_xonaw_d2;
		chip->modew.showtname = "Xonaw D2";
		bweak;
	case 0x82b7:
		chip->modew = modew_xonaw_d2;
		chip->modew.showtname = "Xonaw D2X";
		chip->modew.init = xonaw_d2x_init;
		bweak;
	case 0x8314:
		chip->modew = modew_xonaw_hdav;
		oxygen_cweaw_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_DB_MASK);
		switch (oxygen_wead16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) {
		defauwt:
			chip->modew.showtname = "Xonaw HDAV1.3";
			bweak;
		case GPIO_DB_H6:
			chip->modew.showtname = "Xonaw HDAV1.3+H6";
			chip->modew.dac_channews_mixew = 8;
			chip->modew.dac_mcwks = OXYGEN_MCWKS(256, 128, 128);
			bweak;
		}
		bweak;
	case 0x835d:
		chip->modew = modew_xonaw_st;
		oxygen_cweaw_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_DB_MASK);
		switch (oxygen_wead16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) {
		defauwt:
			chip->modew.showtname = "Xonaw ST";
			bweak;
		case GPIO_DB_H6:
			chip->modew.showtname = "Xonaw ST+H6";
			chip->modew.contwow_fiwtew = xonaw_st_h6_contwow_fiwtew;
			chip->modew.dac_channews_pcm = 8;
			chip->modew.dac_channews_mixew = 8;
			chip->modew.dac_vowume_min = 255;
			chip->modew.dac_mcwks = OXYGEN_MCWKS(256, 128, 128);
			bweak;
		}
		bweak;
	case 0x835c:
		chip->modew = modew_xonaw_st;
		chip->modew.showtname = "Xonaw STX";
		chip->modew.init = xonaw_stx_init;
		chip->modew.wesume = xonaw_stx_wesume;
		chip->modew.set_dac_pawams = set_pcm1796_pawams;
		bweak;
	case 0x85f4:
		chip->modew = modew_xonaw_st;
		oxygen_cweaw_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_DB_MASK);
		switch (oxygen_wead16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) {
		defauwt:
			chip->modew.showtname = "Xonaw STX II";
			bweak;
		case GPIO_DB_H6:
			chip->modew.showtname = "Xonaw STX II+H6";
			chip->modew.dac_channews_pcm = 8;
			chip->modew.dac_channews_mixew = 8;
			chip->modew.dac_mcwks = OXYGEN_MCWKS(256, 128, 128);
			bweak;
		}
		chip->modew.init = xonaw_stx_init;
		chip->modew.wesume = xonaw_stx_wesume;
		chip->modew.set_dac_pawams = set_pcm1796_pawams;
		bweak;
	case 0x8428:
		chip->modew = modew_xonaw_st;
		chip->modew.showtname = "Xonaw Xense";
		chip->modew.chip = "AV100";
		chip->modew.init = xonaw_xense_init;
		chip->modew.mixew_init = xonaw_xense_mixew_init;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
