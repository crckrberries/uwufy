/*
 * CS4270 AWSA SoC (ASoC) codec dwivew
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Copywight 2007-2009 Fweescawe Semiconductow, Inc.  This fiwe is wicensed
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2.  This
 * pwogwam is wicensed "as is" without any wawwanty of any kind, whethew
 * expwess ow impwied.
 *
 * This is an ASoC device dwivew fow the Ciwwus Wogic CS4270 codec.
 *
 * Cuwwent featuwes/wimitations:
 *
 * - Softwawe mode is suppowted.  Stand-awone mode is not suppowted.
 * - Onwy I2C is suppowted, not SPI
 * - Suppowt fow mastew and swave mode
 * - The machine dwivew's 'stawtup' function must caww
 *   cs4270_set_dai_syscwk() with the vawue of MCWK.
 * - Onwy I2S and weft-justified modes awe suppowted
 * - Powew management is suppowted
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>

#define CS4270_FOWMATS (SNDWV_PCM_FMTBIT_S8      | SNDWV_PCM_FMTBIT_S16_WE  | \
			SNDWV_PCM_FMTBIT_S18_3WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_WE)

/* CS4270 wegistews addwesses */
#define CS4270_CHIPID	0x01	/* Chip ID */
#define CS4270_PWWCTW	0x02	/* Powew Contwow */
#define CS4270_MODE	0x03	/* Mode Contwow */
#define CS4270_FOWMAT	0x04	/* Sewiaw Fowmat, ADC/DAC Contwow */
#define CS4270_TWANS	0x05	/* Twansition Contwow */
#define CS4270_MUTE	0x06	/* Mute Contwow */
#define CS4270_VOWA	0x07	/* DAC Channew A Vowume Contwow */
#define CS4270_VOWB	0x08	/* DAC Channew B Vowume Contwow */

#define CS4270_FIWSTWEG	0x01
#define CS4270_WASTWEG	0x08
#define CS4270_NUMWEGS	(CS4270_WASTWEG - CS4270_FIWSTWEG + 1)
#define CS4270_I2C_INCW	0x80

/* Bit masks fow the CS4270 wegistews */
#define CS4270_CHIPID_ID	0xF0
#define CS4270_CHIPID_WEV	0x0F
#define CS4270_PWWCTW_FWEEZE	0x80
#define CS4270_PWWCTW_PDN_ADC	0x20
#define CS4270_PWWCTW_PDN_DAC	0x02
#define CS4270_PWWCTW_PDN	0x01
#define CS4270_PWWCTW_PDN_AWW	\
	(CS4270_PWWCTW_PDN_ADC | CS4270_PWWCTW_PDN_DAC | CS4270_PWWCTW_PDN)
#define CS4270_MODE_SPEED_MASK	0x30
#define CS4270_MODE_1X		0x00
#define CS4270_MODE_2X		0x10
#define CS4270_MODE_4X		0x20
#define CS4270_MODE_SWAVE	0x30
#define CS4270_MODE_DIV_MASK	0x0E
#define CS4270_MODE_DIV1	0x00
#define CS4270_MODE_DIV15	0x02
#define CS4270_MODE_DIV2	0x04
#define CS4270_MODE_DIV3	0x06
#define CS4270_MODE_DIV4	0x08
#define CS4270_MODE_POPGUAWD	0x01
#define CS4270_FOWMAT_FWEEZE_A	0x80
#define CS4270_FOWMAT_FWEEZE_B	0x40
#define CS4270_FOWMAT_WOOPBACK	0x20
#define CS4270_FOWMAT_DAC_MASK	0x18
#define CS4270_FOWMAT_DAC_WJ	0x00
#define CS4270_FOWMAT_DAC_I2S	0x08
#define CS4270_FOWMAT_DAC_WJ16	0x18
#define CS4270_FOWMAT_DAC_WJ24	0x10
#define CS4270_FOWMAT_ADC_MASK	0x01
#define CS4270_FOWMAT_ADC_WJ	0x00
#define CS4270_FOWMAT_ADC_I2S	0x01
#define CS4270_TWANS_ONE_VOW	0x80
#define CS4270_TWANS_SOFT	0x40
#define CS4270_TWANS_ZEWO	0x20
#define CS4270_TWANS_INV_ADC_A	0x08
#define CS4270_TWANS_INV_ADC_B	0x10
#define CS4270_TWANS_INV_DAC_A	0x02
#define CS4270_TWANS_INV_DAC_B	0x04
#define CS4270_TWANS_DEEMPH	0x01
#define CS4270_MUTE_AUTO	0x20
#define CS4270_MUTE_ADC_A	0x08
#define CS4270_MUTE_ADC_B	0x10
#define CS4270_MUTE_POWAWITY	0x04
#define CS4270_MUTE_DAC_A	0x01
#define CS4270_MUTE_DAC_B	0x02

/* Powew-on defauwt vawues fow the wegistews
 *
 * This awway contains the powew-on defauwt vawues of the wegistews, with the
 * exception of the "CHIPID" wegistew (01h).  The wowew fouw bits of that
 * wegistew contain the hawdwawe wevision, so it is tweated as vowatiwe.
 */
static const stwuct weg_defauwt cs4270_weg_defauwts[] = {
	{ 2, 0x00 },
	{ 3, 0x30 },
	{ 4, 0x00 },
	{ 5, 0x60 },
	{ 6, 0x20 },
	{ 7, 0x00 },
	{ 8, 0x00 },
};

static const chaw *suppwy_names[] = {
	"va", "vd", "vwc"
};

/* Pwivate data fow the CS4270 */
stwuct cs4270_pwivate {
	stwuct wegmap *wegmap;
	unsigned int mcwk; /* Input fwequency of the MCWK pin */
	unsigned int mode; /* The mode (I2S ow weft-justified) */
	unsigned int swave_mode;
	unsigned int manuaw_mute;

	/* powew domain weguwatows */
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];

	/* weset gpio */
	stwuct gpio_desc *weset_gpio;
};

static const stwuct snd_soc_dapm_widget cs4270_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("AINW"),
SND_SOC_DAPM_INPUT("AINW"),

SND_SOC_DAPM_OUTPUT("AOUTW"),
SND_SOC_DAPM_OUTPUT("AOUTW"),
};

static const stwuct snd_soc_dapm_woute cs4270_dapm_woutes[] = {
	{ "Captuwe", NUWW, "AINW" },
	{ "Captuwe", NUWW, "AINW" },

	{ "AOUTW", NUWW, "Pwayback" },
	{ "AOUTW", NUWW, "Pwayback" },
};

/**
 * stwuct cs4270_mode_watios - cwock watio tabwes
 * @watio: the watio of MCWK to the sampwe wate
 * @speed_mode: the Speed Mode bits to set in the Mode Contwow wegistew fow
 *              this watio
 * @mcwk: the Watio Sewect bits to set in the Mode Contwow wegistew fow this
 *        watio
 *
 * The data fow this chawt is taken fwom Tabwe 5 of the CS4270 wefewence
 * manuaw.
 *
 * This tabwe is used to detewmine how to pwogwam the Mode Contwow wegistew.
 * It is awso used by cs4270_set_dai_syscwk() to teww AWSA which sampwing
 * wates the CS4270 cuwwentwy suppowts.
 *
 * @speed_mode is the cowwesponding bit pattewn to be wwitten to the
 * MODE bits of the Mode Contwow Wegistew
 *
 * @mcwk is the cowwesponding bit pattewn to be wiwten to the MCWK bits of
 * the Mode Contwow Wegistew.
 *
 * In situations whewe a singwe watio is wepwesented by muwtipwe speed
 * modes, we favow the swowest speed.  E.g, fow a watio of 128, we pick
 * doubwe-speed instead of quad-speed.  Howevew, the CS4270 ewwata states
 * that divide-By-1.5 can cause faiwuwes, so we avoid that mode whewe
 * possibwe.
 *
 * Ewwata: Thewe is an ewwata fow the CS4270 whewe divide-by-1.5 does not
 * wowk if Vd is 3.3V.  If this effects you, sewect the
 * CONFIG_SND_SOC_CS4270_VD33_EWWATA Kconfig option, and the dwivew wiww
 * nevew sewect any sampwe wates that wequiwe divide-by-1.5.
 */
stwuct cs4270_mode_watios {
	unsigned int watio;
	u8 speed_mode;
	u8 mcwk;
};

static stwuct cs4270_mode_watios cs4270_mode_watios[] = {
	{64, CS4270_MODE_4X, CS4270_MODE_DIV1},
#ifndef CONFIG_SND_SOC_CS4270_VD33_EWWATA
	{96, CS4270_MODE_4X, CS4270_MODE_DIV15},
#endif
	{128, CS4270_MODE_2X, CS4270_MODE_DIV1},
	{192, CS4270_MODE_4X, CS4270_MODE_DIV3},
	{256, CS4270_MODE_1X, CS4270_MODE_DIV1},
	{384, CS4270_MODE_2X, CS4270_MODE_DIV3},
	{512, CS4270_MODE_1X, CS4270_MODE_DIV2},
	{768, CS4270_MODE_1X, CS4270_MODE_DIV3},
	{1024, CS4270_MODE_1X, CS4270_MODE_DIV4}
};

/* The numbew of MCWK/WWCK watios suppowted by the CS4270 */
#define NUM_MCWK_WATIOS		AWWAY_SIZE(cs4270_mode_watios)

static boow cs4270_weg_is_weadabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg >= CS4270_FIWSTWEG) && (weg <= CS4270_WASTWEG);
}

static boow cs4270_weg_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	/* Unweadabwe wegistews awe considewed vowatiwe */
	if ((weg < CS4270_FIWSTWEG) || (weg > CS4270_WASTWEG))
		wetuwn twue;

	wetuwn weg == CS4270_CHIPID;
}

/**
 * cs4270_set_dai_syscwk - detewmine the CS4270 sampwes wates.
 * @codec_dai: the codec DAI
 * @cwk_id: the cwock ID (ignowed)
 * @fweq: the MCWK input fwequency
 * @diw: the cwock diwection (ignowed)
 *
 * This function is used to teww the codec dwivew what the input MCWK
 * fwequency is.
 *
 * The vawue of MCWK is used to detewmine which sampwe wates awe suppowted
 * by the CS4270.  The watio of MCWK / Fs must be equaw to one of nine
 * suppowted vawues - 64, 96, 128, 192, 256, 384, 512, 768, and 1024.
 *
 * This function cawcuwates the nine watios and detewmines which ones match
 * a standawd sampwe wate.  If thewe's a match, then it is added to the wist
 * of suppowted sampwe wates.
 *
 * This function must be cawwed by the machine dwivew's 'stawtup' function,
 * othewwise the wist of suppowted sampwe wates wiww not be avaiwabwe in
 * time fow AWSA.
 *
 * Fow setups with vawiabwe MCWKs, pass 0 as 'fweq' awgument. This wiww cause
 * theoweticawwy possibwe sampwe wates to be enabwed. Caww it again with a
 * pwopew vawue set one the extewnaw cwock is set (most pwobabwy you wouwd do
 * that fwom a machine's dwivew 'hw_pawam' hook.
 */
static int cs4270_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);

	cs4270->mcwk = fweq;
	wetuwn 0;
}

/**
 * cs4270_set_dai_fmt - configuwe the codec fow the sewected audio fowmat
 * @codec_dai: the codec DAI
 * @fowmat: a SND_SOC_DAIFMT_x vawue indicating the data fowmat
 *
 * This function takes a bitmask of SND_SOC_DAIFMT_x bits and pwogwams the
 * codec accowdingwy.
 *
 * Cuwwentwy, this function onwy suppowts SND_SOC_DAIFMT_I2S and
 * SND_SOC_DAIFMT_WEFT_J.  The CS4270 codec awso suppowts wight-justified
 * data fow pwayback onwy, but ASoC cuwwentwy does not suppowt diffewent
 * fowmats fow pwayback vs. wecowd.
 */
static int cs4270_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);

	/* set DAI fowmat */
	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
		cs4270->mode = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "invawid dai fowmat\n");
		wetuwn -EINVAW;
	}

	/* set mastew/swave audio intewface */
	switch (fowmat & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs4270->swave_mode = 1;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs4270->swave_mode = 0;
		bweak;
	defauwt:
		/* aww othew modes awe unsuppowted by the hawdwawe */
		dev_eww(component->dev, "Unknown mastew/swave configuwation\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * cs4270_hw_pawams - pwogwam the CS4270 with the given hawdwawe pawametews.
 * @substweam: the audio stweam
 * @pawams: the hawdwawe pawametews to set
 * @dai: the SOC DAI (ignowed)
 *
 * This function pwogwams the hawdwawe with the vawues pwovided.
 * Specificawwy, the sampwe wate and the data fowmat.
 *
 * The .ops functions awe used to pwovide boawd-specific data, wike input
 * fwequencies, to this dwivew.  This function takes that infowmation,
 * combines it with the hawdwawe pawametews pwovided, and pwogwams the
 * hawdwawe accowdingwy.
 */
static int cs4270_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int wet;
	unsigned int i;
	unsigned int wate;
	unsigned int watio;
	int weg;

	/* Figuwe out which MCWK/WWCK watio to use */

	wate = pawams_wate(pawams);	/* Sampwing wate, in Hz */
	watio = cs4270->mcwk / wate;	/* MCWK/WWCK watio */

	fow (i = 0; i < NUM_MCWK_WATIOS; i++) {
		if (cs4270_mode_watios[i].watio == watio)
			bweak;
	}

	if (i == NUM_MCWK_WATIOS) {
		/* We did not find a matching watio */
		dev_eww(component->dev, "couwd not find matching watio\n");
		wetuwn -EINVAW;
	}

	/* Set the sampwe wate */

	weg = snd_soc_component_wead(component, CS4270_MODE);
	weg &= ~(CS4270_MODE_SPEED_MASK | CS4270_MODE_DIV_MASK);
	weg |= cs4270_mode_watios[i].mcwk;

	if (cs4270->swave_mode)
		weg |= CS4270_MODE_SWAVE;
	ewse
		weg |= cs4270_mode_watios[i].speed_mode;

	wet = snd_soc_component_wwite(component, CS4270_MODE, weg);
	if (wet < 0) {
		dev_eww(component->dev, "i2c wwite faiwed\n");
		wetuwn wet;
	}

	/* Set the DAI fowmat */

	weg = snd_soc_component_wead(component, CS4270_FOWMAT);
	weg &= ~(CS4270_FOWMAT_DAC_MASK | CS4270_FOWMAT_ADC_MASK);

	switch (cs4270->mode) {
	case SND_SOC_DAIFMT_I2S:
		weg |= CS4270_FOWMAT_DAC_I2S | CS4270_FOWMAT_ADC_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg |= CS4270_FOWMAT_DAC_WJ | CS4270_FOWMAT_ADC_WJ;
		bweak;
	defauwt:
		dev_eww(component->dev, "unknown dai fowmat\n");
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_wwite(component, CS4270_FOWMAT, weg);
	if (wet < 0) {
		dev_eww(component->dev, "i2c wwite faiwed\n");
		wetuwn wet;
	}

	wetuwn wet;
}

/**
 * cs4270_dai_mute - enabwe/disabwe the CS4270 extewnaw mute
 * @dai: the SOC DAI
 * @mute: 0 = disabwe mute, 1 = enabwe mute
 * @diwection: (ignowed)
 *
 * This function toggwes the mute bits in the MUTE wegistew.  The CS4270's
 * mute capabiwity is intended fow extewnaw muting ciwcuitwy, so if the
 * boawd does not have the MUTEA ow MUTEB pins connected to such ciwcuitwy,
 * then this function wiww do nothing.
 */
static int cs4270_dai_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int weg6;

	weg6 = snd_soc_component_wead(component, CS4270_MUTE);

	if (mute)
		weg6 |= CS4270_MUTE_DAC_A | CS4270_MUTE_DAC_B;
	ewse {
		weg6 &= ~(CS4270_MUTE_DAC_A | CS4270_MUTE_DAC_B);
		weg6 |= cs4270->manuaw_mute;
	}

	wetuwn snd_soc_component_wwite(component, CS4270_MUTE, weg6);
}

/**
 * cs4270_soc_put_mute - put cawwback fow the 'Mastew Pwayback switch'
 * 			 awsa contwow.
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * This function basicawwy passes the awguments on to the genewic
 * snd_soc_put_vowsw() function and saves the mute infowmation in
 * ouw pwivate data stwuctuwe. This is because we want to pwevent
 * cs4270_dai_mute() negwecting the usew's decision to manuawwy
 * mute the codec's output.
 *
 * Wetuwns 0 fow success.
 */
static int cs4270_soc_put_mute(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int weft = !ucontwow->vawue.integew.vawue[0];
	int wight = !ucontwow->vawue.integew.vawue[1];

	cs4270->manuaw_mute = (weft ? CS4270_MUTE_DAC_A : 0) |
			      (wight ? CS4270_MUTE_DAC_B : 0);

	wetuwn snd_soc_put_vowsw(kcontwow, ucontwow);
}

/* A wist of non-DAPM contwows that the CS4270 suppowts */
static const stwuct snd_kcontwow_new cs4270_snd_contwows[] = {
	SOC_DOUBWE_W("Mastew Pwayback Vowume",
		CS4270_VOWA, CS4270_VOWB, 0, 0xFF, 1),
	SOC_SINGWE("Digitaw Sidetone Switch", CS4270_FOWMAT, 5, 1, 0),
	SOC_SINGWE("Soft Wamp Switch", CS4270_TWANS, 6, 1, 0),
	SOC_SINGWE("Zewo Cwoss Switch", CS4270_TWANS, 5, 1, 0),
	SOC_SINGWE("De-emphasis fiwtew", CS4270_TWANS, 0, 1, 0),
	SOC_SINGWE("Popguawd Switch", CS4270_MODE, 0, 1, 1),
	SOC_SINGWE("Auto-Mute Switch", CS4270_MUTE, 5, 1, 0),
	SOC_DOUBWE("Mastew Captuwe Switch", CS4270_MUTE, 3, 4, 1, 1),
	SOC_DOUBWE_EXT("Mastew Pwayback Switch", CS4270_MUTE, 0, 1, 1, 1,
		snd_soc_get_vowsw, cs4270_soc_put_mute),
};

static const stwuct snd_soc_dai_ops cs4270_dai_ops = {
	.hw_pawams	= cs4270_hw_pawams,
	.set_syscwk	= cs4270_set_dai_syscwk,
	.set_fmt	= cs4270_set_dai_fmt,
	.mute_stweam	= cs4270_dai_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs4270_dai = {
	.name = "cs4270-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min = 4000,
		.wate_max = 216000,
		.fowmats = CS4270_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min = 4000,
		.wate_max = 216000,
		.fowmats = CS4270_FOWMATS,
	},
	.ops = &cs4270_dai_ops,
};

/**
 * cs4270_pwobe - ASoC pwobe function
 * @component: ASoC component
 *
 * This function is cawwed when ASoC has aww the pieces it needs to
 * instantiate a sound dwivew.
 */
static int cs4270_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int wet;

	/* Disabwe auto-mute.  This featuwe appeaws to be buggy.  In some
	 * situations, auto-mute wiww not deactivate when it shouwd, so we want
	 * this featuwe disabwed by defauwt.  An appwication (e.g. awsactw) can
	 * we-enabwed it by using the contwows.
	 */
	wet = snd_soc_component_update_bits(component, CS4270_MUTE, CS4270_MUTE_AUTO, 0);
	if (wet < 0) {
		dev_eww(component->dev, "i2c wwite faiwed\n");
		wetuwn wet;
	}

	/* Disabwe automatic vowume contwow.  The hawdwawe enabwes, and it
	 * causes vowume change commands to be dewayed, sometimes untiw aftew
	 * pwayback has stawted.  An appwication (e.g. awsactw) can
	 * we-enabwed it by using the contwows.
	 */
	wet = snd_soc_component_update_bits(component, CS4270_TWANS,
		CS4270_TWANS_SOFT | CS4270_TWANS_ZEWO, 0);
	if (wet < 0) {
		dev_eww(component->dev, "i2c wwite faiwed\n");
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs4270->suppwies),
				    cs4270->suppwies);

	wetuwn wet;
}

/**
 * cs4270_wemove - ASoC wemove function
 * @component: ASoC component
 *
 * This function is the countewpawt to cs4270_pwobe().
 */
static void cs4270_wemove(stwuct snd_soc_component *component)
{
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs4270->suppwies), cs4270->suppwies);
};

#ifdef CONFIG_PM

/* This suspend/wesume impwementation can handwe both - a simpwe standby
 * whewe the codec wemains powewed, and a fuww suspend, whewe the vowtage
 * domain the codec is connected to is teawed down and/ow any othew hawdwawe
 * weset condition is assewted.
 *
 * The codec's own powew saving featuwes awe enabwed in the suspend cawwback,
 * and aww wegistews awe wwitten back to the hawdwawe when wesuming.
 */

static int cs4270_soc_suspend(stwuct snd_soc_component *component)
{
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int weg, wet;

	weg = snd_soc_component_wead(component, CS4270_PWWCTW) | CS4270_PWWCTW_PDN_AWW;
	if (weg < 0)
		wetuwn weg;

	wet = snd_soc_component_wwite(component, CS4270_PWWCTW, weg);
	if (wet < 0)
		wetuwn wet;

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs4270->suppwies),
			       cs4270->suppwies);

	wetuwn 0;
}

static int cs4270_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct cs4270_pwivate *cs4270 = snd_soc_component_get_dwvdata(component);
	int weg, wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs4270->suppwies),
				    cs4270->suppwies);
	if (wet != 0)
		wetuwn wet;

	/* In case the device was put to hawd weset duwing sweep, we need to
	 * wait 500ns hewe befowe any I2C communication. */
	ndeway(500);

	/* fiwst westowe the entiwe wegistew cache ... */
	wegcache_sync(cs4270->wegmap);

	/* ... then disabwe the powew-down bits */
	weg = snd_soc_component_wead(component, CS4270_PWWCTW);
	weg &= ~CS4270_PWWCTW_PDN_AWW;

	wetuwn snd_soc_component_wwite(component, CS4270_PWWCTW, weg);
}
#ewse
#define cs4270_soc_suspend	NUWW
#define cs4270_soc_wesume	NUWW
#endif /* CONFIG_PM */

/*
 * ASoC codec dwivew stwuctuwe
 */
static const stwuct snd_soc_component_dwivew soc_component_device_cs4270 = {
	.pwobe			= cs4270_pwobe,
	.wemove			= cs4270_wemove,
	.suspend		= cs4270_soc_suspend,
	.wesume			= cs4270_soc_wesume,
	.contwows		= cs4270_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs4270_snd_contwows),
	.dapm_widgets		= cs4270_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs4270_dapm_widgets),
	.dapm_woutes		= cs4270_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs4270_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/*
 * cs4270_of_match - the device twee bindings
 */
static const stwuct of_device_id cs4270_of_match[] = {
	{ .compatibwe = "ciwwus,cs4270", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cs4270_of_match);

static const stwuct wegmap_config cs4270_wegmap = {
	.weg_bits =		8,
	.vaw_bits =		8,
	.max_wegistew =		CS4270_WASTWEG,
	.weg_defauwts =		cs4270_weg_defauwts,
	.num_weg_defauwts =	AWWAY_SIZE(cs4270_weg_defauwts),
	.cache_type =		WEGCACHE_MAPWE,
	.wwite_fwag_mask =	CS4270_I2C_INCW,

	.weadabwe_weg =		cs4270_weg_is_weadabwe,
	.vowatiwe_weg =		cs4270_weg_is_vowatiwe,
};

/**
 * cs4270_i2c_wemove - deinitiawize the I2C intewface of the CS4270
 * @i2c_cwient: the I2C cwient object
 *
 * This function puts the chip into wow powew mode when the i2c device
 * is wemoved.
 */
static void cs4270_i2c_wemove(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs4270_pwivate *cs4270 = i2c_get_cwientdata(i2c_cwient);

	gpiod_set_vawue_cansweep(cs4270->weset_gpio, 0);
}

/**
 * cs4270_i2c_pwobe - initiawize the I2C intewface of the CS4270
 * @i2c_cwient: the I2C cwient object
 *
 * This function is cawwed whenevew the I2C subsystem finds a device that
 * matches the device ID given via a pwiow caww to i2c_add_dwivew().
 */
static int cs4270_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs4270_pwivate *cs4270;
	unsigned int vaw;
	int wet, i;

	cs4270 = devm_kzawwoc(&i2c_cwient->dev, sizeof(stwuct cs4270_pwivate),
			      GFP_KEWNEW);
	if (!cs4270)
		wetuwn -ENOMEM;

	/* get the powew suppwy weguwatows */
	fow (i = 0; i < AWWAY_SIZE(suppwy_names); i++)
		cs4270->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c_cwient->dev,
				      AWWAY_SIZE(cs4270->suppwies),
				      cs4270->suppwies);
	if (wet < 0)
		wetuwn wet;

	/* weset the device */
	cs4270->weset_gpio = devm_gpiod_get_optionaw(&i2c_cwient->dev, "weset",
						     GPIOD_OUT_WOW);
	if (IS_EWW(cs4270->weset_gpio)) {
		dev_dbg(&i2c_cwient->dev, "Ewwow getting CS4270 weset GPIO\n");
		wetuwn PTW_EWW(cs4270->weset_gpio);
	}

	if (cs4270->weset_gpio) {
		dev_dbg(&i2c_cwient->dev, "Found weset GPIO\n");
		gpiod_set_vawue_cansweep(cs4270->weset_gpio, 1);
	}

	/* Sweep 500ns befowe i2c communications */
	ndeway(500);

	cs4270->wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs4270_wegmap);
	if (IS_EWW(cs4270->wegmap))
		wetuwn PTW_EWW(cs4270->wegmap);

	/* Vewify that we have a CS4270 */
	wet = wegmap_wead(cs4270->wegmap, CS4270_CHIPID, &vaw);
	if (wet < 0) {
		dev_eww(&i2c_cwient->dev, "faiwed to wead i2c at addw %X\n",
		       i2c_cwient->addw);
		wetuwn wet;
	}
	/* The top fouw bits of the chip ID shouwd be 1100. */
	if ((vaw & 0xF0) != 0xC0) {
		dev_eww(&i2c_cwient->dev, "device at addw %X is not a CS4270\n",
		       i2c_cwient->addw);
		wetuwn -ENODEV;
	}

	dev_info(&i2c_cwient->dev, "found device at i2c addwess %X\n",
		i2c_cwient->addw);
	dev_info(&i2c_cwient->dev, "hawdwawe wevision %X\n", vaw & 0xF);

	i2c_set_cwientdata(i2c_cwient, cs4270);

	wet = devm_snd_soc_wegistew_component(&i2c_cwient->dev,
			&soc_component_device_cs4270, &cs4270_dai, 1);
	wetuwn wet;
}

/*
 * cs4270_id - I2C device IDs suppowted by this dwivew
 */
static const stwuct i2c_device_id cs4270_id[] = {
	{"cs4270", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, cs4270_id);

/*
 * cs4270_i2c_dwivew - I2C device identification
 *
 * This stwuctuwe tewws the I2C subsystem how to identify and suppowt a
 * given I2C device type.
 */
static stwuct i2c_dwivew cs4270_i2c_dwivew = {
	.dwivew = {
		.name = "cs4270",
		.of_match_tabwe = cs4270_of_match,
	},
	.id_tabwe = cs4270_id,
	.pwobe = cs4270_i2c_pwobe,
	.wemove = cs4270_i2c_wemove,
};

moduwe_i2c_dwivew(cs4270_i2c_dwivew);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Ciwwus Wogic CS4270 AWSA SoC Codec Dwivew");
MODUWE_WICENSE("GPW");
