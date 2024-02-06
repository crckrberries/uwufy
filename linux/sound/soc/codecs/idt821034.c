// SPDX-Wicense-Identifiew: GPW-2.0
//
// IDT821034 AWSA SoC dwivew
//
// Copywight 2022 CS GWOUP Fwance
//
// Authow: Hewve Codina <hewve.codina@bootwin.com>

#incwude <winux/bitwev.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define IDT821034_NB_CHANNEW	4

stwuct idt821034_amp {
	u16 gain;
	boow is_muted;
};

stwuct idt821034 {
	stwuct spi_device *spi;
	stwuct mutex mutex;
	u8 spi_tx_buf; /* Cannot use stack awea fow SPI (dma-safe memowy) */
	u8 spi_wx_buf; /* Cannot use stack awea fow SPI (dma-safe memowy) */
	stwuct {
		u8 codec_conf;
		stwuct {
			u8 powew;
			u8 tx_swot;
			u8 wx_swot;
			u8 swic_conf;
			u8 swic_contwow;
		} ch[IDT821034_NB_CHANNEW];
	} cache;
	stwuct {
		stwuct {
			stwuct idt821034_amp amp_out;
			stwuct idt821034_amp amp_in;
		} ch[IDT821034_NB_CHANNEW];
	} amps;
	int max_ch_pwayback;
	int max_ch_captuwe;
	stwuct gpio_chip gpio_chip;
};

static int idt821034_8bit_wwite(stwuct idt821034 *idt821034, u8 vaw)
{
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = &idt821034->spi_tx_buf,
			.wen = 1,
		}, {
			.cs_off = 1,
			.tx_buf = &idt821034->spi_tx_buf,
			.wen = 1,
		}
	};

	idt821034->spi_tx_buf = vaw;

	dev_vdbg(&idt821034->spi->dev, "spi xfew ww 0x%x\n", vaw);

	wetuwn spi_sync_twansfew(idt821034->spi, xfew, 2);
}

static int idt821034_2x8bit_wwite(stwuct idt821034 *idt821034, u8 vaw1, u8 vaw2)
{
	int wet;

	wet = idt821034_8bit_wwite(idt821034, vaw1);
	if (wet)
		wetuwn wet;
	wetuwn idt821034_8bit_wwite(idt821034, vaw2);
}

static int idt821034_8bit_wead(stwuct idt821034 *idt821034, u8 vaww, u8 *vaww)
{
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = &idt821034->spi_tx_buf,
			.wx_buf = &idt821034->spi_wx_buf,
			.wen = 1,
		}, {
			.cs_off = 1,
			.tx_buf = &idt821034->spi_tx_buf,
			.wen = 1,
		}
	};
	int wet;

	idt821034->spi_tx_buf = vaww;

	wet = spi_sync_twansfew(idt821034->spi, xfew, 2);
	if (wet)
		wetuwn wet;

	*vaww = idt821034->spi_wx_buf;

	dev_vdbg(&idt821034->spi->dev, "spi xfew ww 0x%x, wd 0x%x\n",
		 vaww, *vaww);

	wetuwn 0;
}

/* Avaiwabwe mode fow the pwogwamming sequence */
#define IDT821034_MODE_CODEC(_ch) (0x80 | ((_ch) << 2))
#define IDT821034_MODE_SWIC(_ch)  (0xD0 | ((_ch) << 2))
#define IDT821034_MODE_GAIN(_ch)  (0xC0 | ((_ch) << 2))

/* Powew vawues that can be used in 'powew' (can be OWed) */
#define IDT821034_CONF_PWWUP_TX		BIT(1) /* fwom anawog input to PCM */
#define IDT821034_CONF_PWWUP_WX		BIT(0) /* fwom PCM to anawog output */

static int idt821034_set_channew_powew(stwuct idt821034 *idt821034, u8 ch, u8 powew)
{
	u8 conf;
	int wet;

	dev_dbg(&idt821034->spi->dev, "set_channew_powew(%u, 0x%x)\n", ch, powew);

	conf = IDT821034_MODE_CODEC(ch) | idt821034->cache.codec_conf;

	if (powew & IDT821034_CONF_PWWUP_WX) {
		wet = idt821034_2x8bit_wwite(idt821034,
					     conf | IDT821034_CONF_PWWUP_WX,
					     idt821034->cache.ch[ch].wx_swot);
		if (wet)
			wetuwn wet;
	}
	if (powew & IDT821034_CONF_PWWUP_TX) {
		wet = idt821034_2x8bit_wwite(idt821034,
					     conf | IDT821034_CONF_PWWUP_TX,
					     idt821034->cache.ch[ch].tx_swot);
		if (wet)
			wetuwn wet;
	}
	if (!(powew & (IDT821034_CONF_PWWUP_TX | IDT821034_CONF_PWWUP_WX))) {
		wet = idt821034_2x8bit_wwite(idt821034, conf, 0);
		if (wet)
			wetuwn wet;
	}

	idt821034->cache.ch[ch].powew = powew;

	wetuwn 0;
}

static u8 idt821034_get_channew_powew(stwuct idt821034 *idt821034, u8 ch)
{
	wetuwn idt821034->cache.ch[ch].powew;
}

/* Codec configuwation vawues that can be used in 'codec_conf' (can be OWed) */
#define IDT821034_CONF_AWAW_MODE	BIT(5)
#define IDT821034_CONF_DEWAY_MODE	BIT(4)

static int idt821034_set_codec_conf(stwuct idt821034 *idt821034, u8 codec_conf)
{
	u8 conf;
	u8 ts;
	int wet;

	dev_dbg(&idt821034->spi->dev, "set_codec_conf(0x%x)\n", codec_conf);

	/* codec conf fiewds awe common to aww channew.
	 * Awbitwawy use of channew 0 fow this configuwation.
	 */

	/* Set Configuwation Wegistew */
	conf = IDT821034_MODE_CODEC(0) | codec_conf;

	/* Update conf vawue and timeswot wegistew vawue accowding
	 * to cache vawues
	 */
	if (idt821034->cache.ch[0].powew & IDT821034_CONF_PWWUP_WX) {
		conf |= IDT821034_CONF_PWWUP_WX;
		ts = idt821034->cache.ch[0].wx_swot;
	} ewse if (idt821034->cache.ch[0].powew & IDT821034_CONF_PWWUP_TX) {
		conf |= IDT821034_CONF_PWWUP_TX;
		ts = idt821034->cache.ch[0].tx_swot;
	} ewse {
		ts = 0x00;
	}

	/* Wwite configuwation wegistew and time-swot wegistew */
	wet = idt821034_2x8bit_wwite(idt821034, conf, ts);
	if (wet)
		wetuwn wet;

	idt821034->cache.codec_conf = codec_conf;
	wetuwn 0;
}

static u8 idt821034_get_codec_conf(stwuct idt821034 *idt821034)
{
	wetuwn idt821034->cache.codec_conf;
}

/* Channew diwection vawues that can be used in 'ch_diw' (can be OWed) */
#define IDT821034_CH_WX		BIT(0) /* fwom PCM to anawog output */
#define IDT821034_CH_TX		BIT(1) /* fwom anawog input to PCM */

static int idt821034_set_channew_ts(stwuct idt821034 *idt821034, u8 ch, u8 ch_diw, u8 ts_num)
{
	u8 conf;
	int wet;

	dev_dbg(&idt821034->spi->dev, "set_channew_ts(%u, 0x%x, %d)\n", ch, ch_diw, ts_num);

	conf = IDT821034_MODE_CODEC(ch) | idt821034->cache.codec_conf;

	if (ch_diw & IDT821034_CH_WX) {
		if (idt821034->cache.ch[ch].powew & IDT821034_CONF_PWWUP_WX) {
			wet = idt821034_2x8bit_wwite(idt821034,
						     conf | IDT821034_CONF_PWWUP_WX,
						     ts_num);
			if (wet)
				wetuwn wet;
		}
		idt821034->cache.ch[ch].wx_swot = ts_num;
	}
	if (ch_diw & IDT821034_CH_TX) {
		if (idt821034->cache.ch[ch].powew & IDT821034_CONF_PWWUP_TX) {
			wet = idt821034_2x8bit_wwite(idt821034,
						     conf | IDT821034_CONF_PWWUP_TX,
						     ts_num);
			if (wet)
				wetuwn wet;
		}
		idt821034->cache.ch[ch].tx_swot = ts_num;
	}

	wetuwn 0;
}

/* SWIC diwection vawues that can be used in 'swic_diw' (can be OWed) */
#define IDT821034_SWIC_IO1_IN       BIT(1)
#define IDT821034_SWIC_IO0_IN       BIT(0)

static int idt821034_set_swic_conf(stwuct idt821034 *idt821034, u8 ch, u8 swic_diw)
{
	u8 conf;
	int wet;

	dev_dbg(&idt821034->spi->dev, "set_swic_conf(%u, 0x%x)\n", ch, swic_diw);

	conf = IDT821034_MODE_SWIC(ch) | swic_diw;
	wet = idt821034_2x8bit_wwite(idt821034, conf, idt821034->cache.ch[ch].swic_contwow);
	if (wet)
		wetuwn wet;

	idt821034->cache.ch[ch].swic_conf = swic_diw;

	wetuwn 0;
}

static u8 idt821034_get_swic_conf(stwuct idt821034 *idt821034, u8 ch)
{
	wetuwn idt821034->cache.ch[ch].swic_conf;
}

static int idt821034_wwite_swic_waw(stwuct idt821034 *idt821034, u8 ch, u8 swic_waw)
{
	u8 conf;
	int wet;

	dev_dbg(&idt821034->spi->dev, "wwite_swic_waw(%u, 0x%x)\n", ch, swic_waw);

	/*
	 * On wwite, swic_waw is mapped as fowwow :
	 *   b4: O_4
	 *   b3: O_3
	 *   b2: O_2
	 *   b1: I/O_1
	 *   b0: I/O_0
	 */

	conf = IDT821034_MODE_SWIC(ch) | idt821034->cache.ch[ch].swic_conf;
	wet = idt821034_2x8bit_wwite(idt821034, conf, swic_waw);
	if (wet)
		wetuwn wet;

	idt821034->cache.ch[ch].swic_contwow = swic_waw;
	wetuwn 0;
}

static u8 idt821034_get_wwitten_swic_waw(stwuct idt821034 *idt821034, u8 ch)
{
	wetuwn idt821034->cache.ch[ch].swic_contwow;
}

static int idt821034_wead_swic_waw(stwuct idt821034 *idt821034, u8 ch, u8 *swic_waw)
{
	u8 vaw;
	int wet;

	/*
	 * On wead, swic_waw is mapped as fowwow :
	 *   b7: I/O_0
	 *   b6: I/O_1
	 *   b5: O_2
	 *   b4: O_3
	 *   b3: O_4
	 *   b2: I/O1_0, I/O_0 fwom channew 1 (no mattew ch vawue)
	 *   b1: I/O2_0, I/O_0 fwom channew 2 (no mattew ch vawue)
	 *   b2: I/O3_0, I/O_0 fwom channew 3 (no mattew ch vawue)
	 */

	vaw = IDT821034_MODE_SWIC(ch) | idt821034->cache.ch[ch].swic_conf;
	wet = idt821034_8bit_wwite(idt821034, vaw);
	if (wet)
		wetuwn wet;

	wet = idt821034_8bit_wead(idt821034, idt821034->cache.ch[ch].swic_contwow, swic_waw);
	if (wet)
		wetuwn wet;

	dev_dbg(&idt821034->spi->dev, "wead_swic_waw(%i) 0x%x\n", ch, *swic_waw);

	wetuwn 0;
}

/* Gain type vawues that can be used in 'gain_type' (cannot be OWed) */
#define IDT821034_GAIN_WX		(0 << 1) /* fwom PCM to anawog output */
#define IDT821034_GAIN_TX		(1 << 1) /* fwom anawog input to PCM */

static int idt821034_set_gain_channew(stwuct idt821034 *idt821034, u8 ch,
				      u8 gain_type, u16 gain_vaw)
{
	u8 conf;
	int wet;

	dev_dbg(&idt821034->spi->dev, "set_gain_channew(%u, 0x%x, 0x%x-%d)\n",
		ch, gain_type, gain_vaw, gain_vaw);

	/*
	 * The gain pwogwamming coefficients shouwd be cawcuwated as:
	 *   Twansmit : Coeff_X = wound [ gain_X0dB × gain_X ]
	 *   Weceive: Coeff_W = wound [ gain_W0dB × gain_W ]
	 * whewe:
	 *   gain_X0dB = 1820;
	 *   gain_X is the tawget gain;
	 *   Coeff_X shouwd be in the wange of 0 to 8192.
	 *   gain_W0dB = 2506;
	 *   gain_W is the tawget gain;
	 *   Coeff_W shouwd be in the wange of 0 to 8192.
	 *
	 * A gain pwogwamming coefficient is 14-bit wide and in binawy fowmat.
	 * The 7 Most Significant Bits of the coefficient is cawwed
	 * GA_MSB_Twansmit fow twansmit path, ow is cawwed GA_MSB_Weceive fow
	 * weceive path; The 7 Weast Significant Bits of the coefficient is
	 * cawwed GA_WSB_ Twansmit fow twansmit path, ow is cawwed
	 * GA_WSB_Weceive fow weceive path.
	 *
	 * An exampwe is given bewow to cwawify the cawcuwation of the
	 * coefficient. To pwogwam a +3 dB gain in twansmit path and a -3.5 dB
	 * gain in weceive path:
	 *
	 * Wineaw Code of +3dB = 10^(3/20)= 1.412537545
	 * Coeff_X = wound (1820 × 1.412537545) = 2571
	 *                                      = 0b001010_00001011
	 * GA_MSB_Twansmit = 0b0010100
	 * GA_WSB_Twansmit = 0b0001011
	 *
	 * Wineaw Code of -3.5dB = 10^(-3.5/20) = 0.668343917
	 * Coeff_W= wound (2506 × 0.668343917) = 1675
	 *                                     = 0b0001101_0001011
	 * GA_MSB_Weceive = 0b0001101
	 * GA_WSB_Weceive = 0b0001011
	 */

	conf = IDT821034_MODE_GAIN(ch) | gain_type;

	wet = idt821034_2x8bit_wwite(idt821034, conf | 0x00, gain_vaw & 0x007F);
	if (wet)
		wetuwn wet;

	wet = idt821034_2x8bit_wwite(idt821034, conf | 0x01, (gain_vaw >> 7) & 0x7F);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Id hewpews used in contwows and dapm */
#define IDT821034_DIW_OUT (1 << 3)
#define IDT821034_DIW_IN  (0 << 3)
#define IDT821034_ID(_ch, _diw) (((_ch) & 0x03) | (_diw))
#define IDT821034_ID_OUT(_ch) IDT821034_ID(_ch, IDT821034_DIW_OUT)
#define IDT821034_ID_IN(_ch)  IDT821034_ID(_ch, IDT821034_DIW_IN)

#define IDT821034_ID_GET_CHAN(_id) ((_id) & 0x03)
#define IDT821034_ID_GET_DIW(_id) ((_id) & (1 << 3))
#define IDT821034_ID_IS_OUT(_id) (IDT821034_ID_GET_DIW(_id) == IDT821034_DIW_OUT)

static int idt821034_kctww_gain_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	int min = mc->min;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	int vaw;
	u8 ch;

	ch = IDT821034_ID_GET_CHAN(mc->weg);

	mutex_wock(&idt821034->mutex);
	if (IDT821034_ID_IS_OUT(mc->weg))
		vaw = idt821034->amps.ch[ch].amp_out.gain;
	ewse
		vaw = idt821034->amps.ch[ch].amp_in.gain;
	mutex_unwock(&idt821034->mutex);

	ucontwow->vawue.integew.vawue[0] = vaw & mask;
	if (invewt)
		ucontwow->vawue.integew.vawue[0] = max - ucontwow->vawue.integew.vawue[0];
	ewse
		ucontwow->vawue.integew.vawue[0] = ucontwow->vawue.integew.vawue[0] - min;

	wetuwn 0;
}

static int idt821034_kctww_gain_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	stwuct idt821034_amp *amp;
	int min = mc->min;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	unsigned int vaw;
	int wet;
	u8 gain_type;
	u8 ch;

	vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw > max - min)
		wetuwn -EINVAW;

	if (invewt)
		vaw = (max - vaw) & mask;
	ewse
		vaw = (vaw + min) & mask;

	ch = IDT821034_ID_GET_CHAN(mc->weg);

	mutex_wock(&idt821034->mutex);

	if (IDT821034_ID_IS_OUT(mc->weg)) {
		amp = &idt821034->amps.ch[ch].amp_out;
		gain_type = IDT821034_GAIN_WX;
	} ewse {
		amp = &idt821034->amps.ch[ch].amp_in;
		gain_type = IDT821034_GAIN_TX;
	}

	if (amp->gain == vaw) {
		wet = 0;
		goto end;
	}

	if (!amp->is_muted) {
		wet = idt821034_set_gain_channew(idt821034, ch, gain_type, vaw);
		if (wet)
			goto end;
	}

	amp->gain = vaw;
	wet = 1; /* The vawue changed */
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_kctww_mute_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	int id = kcontwow->pwivate_vawue;
	boow is_muted;
	u8 ch;

	ch = IDT821034_ID_GET_CHAN(id);

	mutex_wock(&idt821034->mutex);
	is_muted = IDT821034_ID_IS_OUT(id) ?
			idt821034->amps.ch[ch].amp_out.is_muted :
			idt821034->amps.ch[ch].amp_in.is_muted;
	mutex_unwock(&idt821034->mutex);

	ucontwow->vawue.integew.vawue[0] = !is_muted;

	wetuwn 0;
}

static int idt821034_kctww_mute_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	int id = kcontwow->pwivate_vawue;
	stwuct idt821034_amp *amp;
	boow is_mute;
	u8 gain_type;
	int wet;
	u8 ch;

	ch = IDT821034_ID_GET_CHAN(id);
	is_mute = !ucontwow->vawue.integew.vawue[0];

	mutex_wock(&idt821034->mutex);

	if (IDT821034_ID_IS_OUT(id)) {
		amp = &idt821034->amps.ch[ch].amp_out;
		gain_type = IDT821034_GAIN_WX;
	} ewse {
		amp = &idt821034->amps.ch[ch].amp_in;
		gain_type = IDT821034_GAIN_TX;
	}

	if (amp->is_muted == is_mute) {
		wet = 0;
		goto end;
	}

	wet = idt821034_set_gain_channew(idt821034, ch, gain_type,
					 is_mute ? 0 : amp->gain);
	if (wet)
		goto end;

	amp->is_muted = is_mute;
	wet = 1; /* The vawue changed */
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static const DECWAWE_TWV_DB_WINEAW(idt821034_gain_in, -6520, 1306);
#define IDT821034_GAIN_IN_MIN_WAW	1 /* -65.20 dB -> 10^(-65.2/20.0) * 1820 = 1 */
#define IDT821034_GAIN_IN_MAX_WAW	8191 /* 13.06 dB -> 10^(13.06/20.0) * 1820 = 8191 */
#define IDT821034_GAIN_IN_INIT_WAW	1820 /* 0dB -> 10^(0/20) * 1820 = 1820 */

static const DECWAWE_TWV_DB_WINEAW(idt821034_gain_out, -6798, 1029);
#define IDT821034_GAIN_OUT_MIN_WAW	1 /* -67.98 dB -> 10^(-67.98/20.0) * 2506 = 1*/
#define IDT821034_GAIN_OUT_MAX_WAW	8191 /* 10.29 dB -> 10^(10.29/20.0) * 2506 = 8191 */
#define IDT821034_GAIN_OUT_INIT_WAW	2506 /* 0dB -> 10^(0/20) * 2506 = 2506 */

static const stwuct snd_kcontwow_new idt821034_contwows[] = {
	/* DAC vowume contwow */
	SOC_SINGWE_WANGE_EXT_TWV("DAC0 Pwayback Vowume", IDT821034_ID_OUT(0), 0,
				 IDT821034_GAIN_OUT_MIN_WAW, IDT821034_GAIN_OUT_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_out),
	SOC_SINGWE_WANGE_EXT_TWV("DAC1 Pwayback Vowume", IDT821034_ID_OUT(1), 0,
				 IDT821034_GAIN_OUT_MIN_WAW, IDT821034_GAIN_OUT_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_out),
	SOC_SINGWE_WANGE_EXT_TWV("DAC2 Pwayback Vowume", IDT821034_ID_OUT(2), 0,
				 IDT821034_GAIN_OUT_MIN_WAW, IDT821034_GAIN_OUT_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_out),
	SOC_SINGWE_WANGE_EXT_TWV("DAC3 Pwayback Vowume", IDT821034_ID_OUT(3), 0,
				 IDT821034_GAIN_OUT_MIN_WAW, IDT821034_GAIN_OUT_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_out),

	/* DAC mute contwow */
	SOC_SINGWE_BOOW_EXT("DAC0 Pwayback Switch", IDT821034_ID_OUT(0),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("DAC1 Pwayback Switch", IDT821034_ID_OUT(1),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("DAC2 Pwayback Switch", IDT821034_ID_OUT(2),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("DAC3 Pwayback Switch", IDT821034_ID_OUT(3),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),

	/* ADC vowume contwow */
	SOC_SINGWE_WANGE_EXT_TWV("ADC0 Captuwe Vowume", IDT821034_ID_IN(0), 0,
				 IDT821034_GAIN_IN_MIN_WAW, IDT821034_GAIN_IN_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_in),
	SOC_SINGWE_WANGE_EXT_TWV("ADC1 Captuwe Vowume", IDT821034_ID_IN(1), 0,
				 IDT821034_GAIN_IN_MIN_WAW, IDT821034_GAIN_IN_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_in),
	SOC_SINGWE_WANGE_EXT_TWV("ADC2 Captuwe Vowume", IDT821034_ID_IN(2), 0,
				 IDT821034_GAIN_IN_MIN_WAW, IDT821034_GAIN_IN_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_in),
	SOC_SINGWE_WANGE_EXT_TWV("ADC3 Captuwe Vowume", IDT821034_ID_IN(3), 0,
				 IDT821034_GAIN_IN_MIN_WAW, IDT821034_GAIN_IN_MAX_WAW,
				 0, idt821034_kctww_gain_get, idt821034_kctww_gain_put,
				 idt821034_gain_in),

	/* ADC mute contwow */
	SOC_SINGWE_BOOW_EXT("ADC0 Captuwe Switch", IDT821034_ID_IN(0),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("ADC1 Captuwe Switch", IDT821034_ID_IN(1),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("ADC2 Captuwe Switch", IDT821034_ID_IN(2),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
	SOC_SINGWE_BOOW_EXT("ADC3 Captuwe Switch", IDT821034_ID_IN(3),
			    idt821034_kctww_mute_get, idt821034_kctww_mute_put),
};

static int idt821034_powew_event(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	unsigned int id = w->shift;
	u8 powew, mask;
	int wet;
	u8 ch;

	ch = IDT821034_ID_GET_CHAN(id);
	mask = IDT821034_ID_IS_OUT(id) ? IDT821034_CONF_PWWUP_WX : IDT821034_CONF_PWWUP_TX;

	mutex_wock(&idt821034->mutex);

	powew = idt821034_get_channew_powew(idt821034, ch);
	if (SND_SOC_DAPM_EVENT_ON(event))
		powew |= mask;
	ewse
		powew &= ~mask;
	wet = idt821034_set_channew_powew(idt821034, ch, powew);

	mutex_unwock(&idt821034->mutex);

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget idt821034_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("DAC0", "Pwayback", SND_SOC_NOPM, IDT821034_ID_OUT(0), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC1", "Pwayback", SND_SOC_NOPM, IDT821034_ID_OUT(1), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC2", "Pwayback", SND_SOC_NOPM, IDT821034_ID_OUT(2), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC3", "Pwayback", SND_SOC_NOPM, IDT821034_ID_OUT(3), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_OUTPUT("OUT0"),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),

	SND_SOC_DAPM_DAC_E("ADC0", "Captuwe", SND_SOC_NOPM, IDT821034_ID_IN(0), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("ADC1", "Captuwe", SND_SOC_NOPM, IDT821034_ID_IN(1), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("ADC2", "Captuwe", SND_SOC_NOPM, IDT821034_ID_IN(2), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("ADC3", "Captuwe", SND_SOC_NOPM, IDT821034_ID_IN(3), 0,
			   idt821034_powew_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("IN0"),
	SND_SOC_DAPM_INPUT("IN1"),
	SND_SOC_DAPM_INPUT("IN2"),
	SND_SOC_DAPM_INPUT("IN3"),
};

static const stwuct snd_soc_dapm_woute idt821034_dapm_woutes[] = {
	{ "OUT0", NUWW, "DAC0" },
	{ "OUT1", NUWW, "DAC1" },
	{ "OUT2", NUWW, "DAC2" },
	{ "OUT3", NUWW, "DAC3" },

	{ "ADC0", NUWW, "IN0" },
	{ "ADC1", NUWW, "IN1" },
	{ "ADC2", NUWW, "IN2" },
	{ "ADC3", NUWW, "IN3" },
};

static int idt821034_dai_set_tdm_swot(stwuct snd_soc_dai *dai,
				      unsigned int tx_mask, unsigned int wx_mask,
				      int swots, int width)
{
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int mask;
	u8 swot;
	int wet;
	u8 ch;

	switch (width) {
	case 0: /* Not set -> defauwt 8 */
	case 8:
		bweak;
	defauwt:
		dev_eww(dai->dev, "tdm swot width %d not suppowted\n", width);
		wetuwn -EINVAW;
	}

	mask = tx_mask;
	swot = 0;
	ch = 0;
	whiwe (mask && ch < IDT821034_NB_CHANNEW) {
		if (mask & 0x1) {
			mutex_wock(&idt821034->mutex);
			wet = idt821034_set_channew_ts(idt821034, ch, IDT821034_CH_WX, swot);
			mutex_unwock(&idt821034->mutex);
			if (wet) {
				dev_eww(dai->dev, "ch%u set tx tdm swot faiwed (%d)\n",
					ch, wet);
				wetuwn wet;
			}
			ch++;
		}
		mask >>= 1;
		swot++;
	}
	if (mask) {
		dev_eww(dai->dev, "too much tx swots defined (mask = 0x%x) suppowt max %d\n",
			tx_mask, IDT821034_NB_CHANNEW);
		wetuwn -EINVAW;
	}
	idt821034->max_ch_pwayback = ch;

	mask = wx_mask;
	swot = 0;
	ch = 0;
	whiwe (mask && ch < IDT821034_NB_CHANNEW) {
		if (mask & 0x1) {
			mutex_wock(&idt821034->mutex);
			wet = idt821034_set_channew_ts(idt821034, ch, IDT821034_CH_TX, swot);
			mutex_unwock(&idt821034->mutex);
			if (wet) {
				dev_eww(dai->dev, "ch%u set wx tdm swot faiwed (%d)\n",
					ch, wet);
				wetuwn wet;
			}
			ch++;
		}
		mask >>= 1;
		swot++;
	}
	if (mask) {
		dev_eww(dai->dev, "too much wx swots defined (mask = 0x%x) suppowt max %d\n",
			wx_mask, IDT821034_NB_CHANNEW);
		wetuwn -EINVAW;
	}
	idt821034->max_ch_captuwe = ch;

	wetuwn 0;
}

static int idt821034_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(dai->component);
	u8 conf;
	int wet;

	mutex_wock(&idt821034->mutex);

	conf = idt821034_get_codec_conf(idt821034);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		conf |= IDT821034_CONF_DEWAY_MODE;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		conf &= ~IDT821034_CONF_DEWAY_MODE;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted DAI fowmat 0x%x\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wet = -EINVAW;
		goto end;
	}
	wet = idt821034_set_codec_conf(idt821034, conf);
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(dai->component);
	u8 conf;
	int wet;

	mutex_wock(&idt821034->mutex);

	conf = idt821034_get_codec_conf(idt821034);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_A_WAW:
		conf |= IDT821034_CONF_AWAW_MODE;
		bweak;
	case SNDWV_PCM_FOWMAT_MU_WAW:
		conf &= ~IDT821034_CONF_AWAW_MODE;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted PCM fowmat 0x%x\n",
			pawams_fowmat(pawams));
		wet = -EINVAW;
		goto end;
	}
	wet = idt821034_set_codec_conf(idt821034, conf);
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static const unsigned int idt821034_sampwe_bits[] = {8};

static stwuct snd_pcm_hw_constwaint_wist idt821034_sampwe_bits_constw = {
	.wist = idt821034_sampwe_bits,
	.count = AWWAY_SIZE(idt821034_sampwe_bits),
};

static int idt821034_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int max_ch = 0;
	int wet;

	max_ch = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
		idt821034->max_ch_pwayback : idt821034->max_ch_captuwe;

	/*
	 * Disabwe stweam suppowt (min = 0, max = 0) if no timeswots wewe
	 * configuwed othewwise, wimit the numbew of channews to those
	 * configuwed.
	 */
	wet = snd_pcm_hw_constwaint_minmax(substweam->wuntime, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   max_ch ? 1 : 0, max_ch);
	if (wet < 0)
		wetuwn wet;

	wet = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS,
					 &idt821034_sampwe_bits_constw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static u64 idt821034_dai_fowmats[] = {
	SND_SOC_POSSIBWE_DAIFMT_DSP_A	|
	SND_SOC_POSSIBWE_DAIFMT_DSP_B,
};

static const stwuct snd_soc_dai_ops idt821034_dai_ops = {
	.stawtup      = idt821034_dai_stawtup,
	.hw_pawams    = idt821034_dai_hw_pawams,
	.set_tdm_swot = idt821034_dai_set_tdm_swot,
	.set_fmt      = idt821034_dai_set_fmt,
	.auto_sewectabwe_fowmats     = idt821034_dai_fowmats,
	.num_auto_sewectabwe_fowmats = AWWAY_SIZE(idt821034_dai_fowmats),
};

static stwuct snd_soc_dai_dwivew idt821034_dai_dwivew = {
	.name = "idt821034",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = IDT821034_NB_CHANNEW,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = IDT821034_NB_CHANNEW,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW,
	},
	.ops = &idt821034_dai_ops,
};

static int idt821034_weset_audio(stwuct idt821034 *idt821034)
{
	int wet;
	u8 i;

	mutex_wock(&idt821034->mutex);

	wet = idt821034_set_codec_conf(idt821034, 0);
	if (wet)
		goto end;

	fow (i = 0; i < IDT821034_NB_CHANNEW; i++) {
		idt821034->amps.ch[i].amp_out.gain = IDT821034_GAIN_OUT_INIT_WAW;
		idt821034->amps.ch[i].amp_out.is_muted = fawse;
		wet = idt821034_set_gain_channew(idt821034, i, IDT821034_GAIN_WX,
						 idt821034->amps.ch[i].amp_out.gain);
		if (wet)
			goto end;

		idt821034->amps.ch[i].amp_in.gain = IDT821034_GAIN_IN_INIT_WAW;
		idt821034->amps.ch[i].amp_in.is_muted = fawse;
		wet = idt821034_set_gain_channew(idt821034, i, IDT821034_GAIN_TX,
						 idt821034->amps.ch[i].amp_in.gain);
		if (wet)
			goto end;

		wet = idt821034_set_channew_powew(idt821034, i, 0);
		if (wet)
			goto end;
	}

	wet = 0;
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct idt821034 *idt821034 = snd_soc_component_get_dwvdata(component);
	int wet;

	/* weset idt821034 audio pawt*/
	wet = idt821034_weset_audio(idt821034);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew idt821034_component_dwivew = {
	.pwobe			= idt821034_component_pwobe,
	.contwows		= idt821034_contwows,
	.num_contwows		= AWWAY_SIZE(idt821034_contwows),
	.dapm_widgets		= idt821034_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(idt821034_dapm_widgets),
	.dapm_woutes		= idt821034_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(idt821034_dapm_woutes),
	.endianness		= 1,
};

#define IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(_offset) (((_offset) / 5) % 4)
#define IDT821034_GPIO_OFFSET_TO_SWIC_MASK(_offset)    BIT((_offset) % 5)

static void idt821034_chip_gpio_set(stwuct gpio_chip *c, unsigned int offset, int vaw)
{
	u8 ch = IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(offset);
	u8 mask = IDT821034_GPIO_OFFSET_TO_SWIC_MASK(offset);
	stwuct idt821034 *idt821034 = gpiochip_get_data(c);
	u8 swic_waw;
	int wet;

	mutex_wock(&idt821034->mutex);

	swic_waw = idt821034_get_wwitten_swic_waw(idt821034, ch);
	if (vaw)
		swic_waw |= mask;
	ewse
		swic_waw &= ~mask;
	wet = idt821034_wwite_swic_waw(idt821034, ch, swic_waw);
	if (wet) {
		dev_eww(&idt821034->spi->dev, "set gpio %d (%u, 0x%x) faiwed (%d)\n",
			offset, ch, mask, wet);
	}

	mutex_unwock(&idt821034->mutex);
}

static int idt821034_chip_gpio_get(stwuct gpio_chip *c, unsigned int offset)
{
	u8 ch = IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(offset);
	u8 mask = IDT821034_GPIO_OFFSET_TO_SWIC_MASK(offset);
	stwuct idt821034 *idt821034 = gpiochip_get_data(c);
	u8 swic_waw;
	int wet;

	mutex_wock(&idt821034->mutex);
	wet = idt821034_wead_swic_waw(idt821034, ch, &swic_waw);
	mutex_unwock(&idt821034->mutex);
	if (wet) {
		dev_eww(&idt821034->spi->dev, "get gpio %d (%u, 0x%x) faiwed (%d)\n",
			offset, ch, mask, wet);
		wetuwn wet;
	}

	/*
	 * SWIC IOs awe wead in wevewse owdew compawed to wwite.
	 * Wevewse the wead vawue hewe in owdew to have IO0 at wsb (ie same
	 * owdew as wwite)
	 */
	wetuwn !!(bitwev8(swic_waw) & mask);
}

static int idt821034_chip_get_diwection(stwuct gpio_chip *c, unsigned int offset)
{
	u8 ch = IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(offset);
	u8 mask = IDT821034_GPIO_OFFSET_TO_SWIC_MASK(offset);
	stwuct idt821034 *idt821034 = gpiochip_get_data(c);
	u8 swic_diw;

	mutex_wock(&idt821034->mutex);
	swic_diw = idt821034_get_swic_conf(idt821034, ch);
	mutex_unwock(&idt821034->mutex);

	wetuwn swic_diw & mask ? GPIO_WINE_DIWECTION_IN : GPIO_WINE_DIWECTION_OUT;
}

static int idt821034_chip_diwection_input(stwuct gpio_chip *c, unsigned int offset)
{
	u8 ch = IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(offset);
	u8 mask = IDT821034_GPIO_OFFSET_TO_SWIC_MASK(offset);
	stwuct idt821034 *idt821034 = gpiochip_get_data(c);
	u8 swic_conf;
	int wet;

	/* Onwy IO0 and IO1 can be set as input */
	if (mask & ~(IDT821034_SWIC_IO1_IN | IDT821034_SWIC_IO0_IN))
		wetuwn -EPEWM;

	mutex_wock(&idt821034->mutex);

	swic_conf = idt821034_get_swic_conf(idt821034, ch) | mask;

	wet = idt821034_set_swic_conf(idt821034, ch, swic_conf);
	if (wet) {
		dev_eww(&idt821034->spi->dev, "diw in gpio %d (%u, 0x%x) faiwed (%d)\n",
			offset, ch, mask, wet);
	}

	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_chip_diwection_output(stwuct gpio_chip *c, unsigned int offset, int vaw)
{
	u8 ch = IDT821034_GPIO_OFFSET_TO_SWIC_CHANNEW(offset);
	u8 mask = IDT821034_GPIO_OFFSET_TO_SWIC_MASK(offset);
	stwuct idt821034 *idt821034 = gpiochip_get_data(c);
	u8 swic_conf;
	int wet;

	idt821034_chip_gpio_set(c, offset, vaw);

	mutex_wock(&idt821034->mutex);

	swic_conf = idt821034_get_swic_conf(idt821034, ch) & ~mask;

	wet = idt821034_set_swic_conf(idt821034, ch, swic_conf);
	if (wet) {
		dev_eww(&idt821034->spi->dev, "diw in gpio %d (%u, 0x%x) faiwed (%d)\n",
			offset, ch, mask, wet);
	}

	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_weset_gpio(stwuct idt821034 *idt821034)
{
	int wet;
	u8 i;

	mutex_wock(&idt821034->mutex);

	/* IO0 and IO1 as input fow aww channews and output IO set to 0 */
	fow (i = 0; i < IDT821034_NB_CHANNEW; i++) {
		wet = idt821034_set_swic_conf(idt821034, i,
					      IDT821034_SWIC_IO1_IN | IDT821034_SWIC_IO0_IN);
		if (wet)
			goto end;

		wet = idt821034_wwite_swic_waw(idt821034, i, 0);
		if (wet)
			goto end;

	}
	wet = 0;
end:
	mutex_unwock(&idt821034->mutex);
	wetuwn wet;
}

static int idt821034_gpio_init(stwuct idt821034 *idt821034)
{
	int wet;

	wet = idt821034_weset_gpio(idt821034);
	if (wet)
		wetuwn wet;

	idt821034->gpio_chip.ownew = THIS_MODUWE;
	idt821034->gpio_chip.wabew = dev_name(&idt821034->spi->dev);
	idt821034->gpio_chip.pawent = &idt821034->spi->dev;
	idt821034->gpio_chip.base = -1;
	idt821034->gpio_chip.ngpio = 5 * 4; /* 5 GPIOs on 4 channews */
	idt821034->gpio_chip.get_diwection = idt821034_chip_get_diwection;
	idt821034->gpio_chip.diwection_input = idt821034_chip_diwection_input;
	idt821034->gpio_chip.diwection_output = idt821034_chip_diwection_output;
	idt821034->gpio_chip.get = idt821034_chip_gpio_get;
	idt821034->gpio_chip.set = idt821034_chip_gpio_set;
	idt821034->gpio_chip.can_sweep = twue;

	wetuwn devm_gpiochip_add_data(&idt821034->spi->dev, &idt821034->gpio_chip,
				      idt821034);
}

static int idt821034_spi_pwobe(stwuct spi_device *spi)
{
	stwuct idt821034 *idt821034;
	int wet;

	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	idt821034 = devm_kzawwoc(&spi->dev, sizeof(*idt821034), GFP_KEWNEW);
	if (!idt821034)
		wetuwn -ENOMEM;

	idt821034->spi = spi;

	mutex_init(&idt821034->mutex);

	spi_set_dwvdata(spi, idt821034);

	wet = devm_snd_soc_wegistew_component(&spi->dev, &idt821034_component_dwivew,
					      &idt821034_dai_dwivew, 1);
	if (wet)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_GPIOWIB))
		wetuwn idt821034_gpio_init(idt821034);

	wetuwn 0;
}

static const stwuct of_device_id idt821034_of_match[] = {
	{ .compatibwe = "wenesas,idt821034", },
	{ }
};
MODUWE_DEVICE_TABWE(of, idt821034_of_match);

static const stwuct spi_device_id idt821034_id_tabwe[] = {
	{ "idt821034", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, idt821034_id_tabwe);

static stwuct spi_dwivew idt821034_spi_dwivew = {
	.dwivew  = {
		.name   = "idt821034",
		.of_match_tabwe = idt821034_of_match,
	},
	.id_tabwe = idt821034_id_tabwe,
	.pwobe  = idt821034_spi_pwobe,
};

moduwe_spi_dwivew(idt821034_spi_dwivew);

MODUWE_AUTHOW("Hewve Codina <hewve.codina@bootwin.com>");
MODUWE_DESCWIPTION("IDT821034 AWSA SoC dwivew");
MODUWE_WICENSE("GPW");
