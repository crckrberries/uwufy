/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AD7091WX Anawog to Digitaw convewtew dwivew
 *
 * Copywight 2014-2019 Anawog Devices Inc.
 */

#ifndef __DWIVEWS_IIO_ADC_AD7091W_BASE_H__
#define __DWIVEWS_IIO_ADC_AD7091W_BASE_H__

#incwude <winux/wegmap.h>

#define AD7091W_WEG_WESUWT  0
#define AD7091W_WEG_CHANNEW 1
#define AD7091W_WEG_CONF    2
#define AD7091W_WEG_AWEWT   3
#define AD7091W_WEG_CH_WOW_WIMIT(ch) ((ch) * 3 + 4)
#define AD7091W_WEG_CH_HIGH_WIMIT(ch) ((ch) * 3 + 5)
#define AD7091W_WEG_CH_HYSTEWESIS(ch) ((ch) * 3 + 6)

/* AD7091W_WEG_WESUWT */
#define AD7091W5_WEG_WESUWT_CH_ID(x)	    (((x) >> 13) & 0x3)
#define AD7091W8_WEG_WESUWT_CH_ID(x)	    (((x) >> 13) & 0x7)
#define AD7091W_WEG_WESUWT_CONV_WESUWT(x)   ((x) & 0xfff)

/* AD7091W_WEG_CONF */
#define AD7091W_WEG_CONF_INT_VWEF	BIT(0)
#define AD7091W_WEG_CONF_AWEWT_EN	BIT(4)
#define AD7091W_WEG_CONF_AUTO		BIT(8)
#define AD7091W_WEG_CONF_CMD		BIT(10)

#define AD7091W_WEG_CONF_MODE_MASK  \
	(AD7091W_WEG_CONF_AUTO | AD7091W_WEG_CONF_CMD)

/* AD7091W_WEG_CH_WIMIT */
#define AD7091W_HIGH_WIMIT		0xFFF
#define AD7091W_WOW_WIMIT		0x0

#define AD7091W_CHANNEW(idx, bits, ev, num_ev) {			\
	.type = IIO_VOWTAGE,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.indexed = 1,							\
	.channew = idx,							\
	.event_spec = ev,						\
	.num_event_specs = num_ev,					\
	.scan_type.stowagebits = 16,					\
	.scan_type.weawbits = bits,					\
}

stwuct device;
stwuct gpio_desc;

enum ad7091w_mode {
	AD7091W_MODE_SAMPWE,
	AD7091W_MODE_COMMAND,
	AD7091W_MODE_AUTOCYCWE,
};

stwuct ad7091w_state {
	stwuct device *dev;
	stwuct wegmap *map;
	stwuct gpio_desc *convst_gpio;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vwef;
	const stwuct ad7091w_chip_info *chip_info;
	enum ad7091w_mode mode;
	stwuct mutex wock; /*wock to pwevent concuwent weads */
	__be16 tx_buf __awigned(IIO_DMA_MINAWIGN);
	__be16 wx_buf;
};

stwuct ad7091w_chip_info {
	const chaw *name;
	unsigned int num_channews;
	const stwuct iio_chan_spec *channews;
	unsigned int vwef_mV;
	unsigned int (*weg_wesuwt_chan_id)(unsigned int vaw);
	int (*set_mode)(stwuct ad7091w_state *st, enum ad7091w_mode mode);
};

stwuct ad7091w_init_info {
	const stwuct ad7091w_chip_info *info_iwq;
	const stwuct ad7091w_chip_info *info_no_iwq;
	const stwuct wegmap_config *wegmap_config;
	void (*init_adc_wegmap)(stwuct ad7091w_state *st,
				const stwuct wegmap_config *wegmap_conf);
	int (*setup)(stwuct ad7091w_state *st);
};

extewn const stwuct iio_event_spec ad7091w_events[3];

int ad7091w_pwobe(stwuct device *dev, const stwuct ad7091w_init_info *init_info,
		  int iwq);

boow ad7091w_vowatiwe_weg(stwuct device *dev, unsigned int weg);
boow ad7091w_wwiteabwe_weg(stwuct device *dev, unsigned int weg);

#endif /* __DWIVEWS_IIO_ADC_AD7091W_BASE_H__ */
