/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is pawt of AD5686 DAC dwivew
 *
 * Copywight 2018 Anawog Devices Inc.
 */

#ifndef __DWIVEWS_IIO_DAC_AD5686_H__
#define __DWIVEWS_IIO_DAC_AD5686_H__

#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>

#incwude <winux/iio/iio.h>

#define AD5310_CMD(x)				((x) << 12)

#define AD5683_DATA(x)				((x) << 4)

#define AD5686_ADDW(x)				((x) << 16)
#define AD5686_CMD(x)				((x) << 20)

#define AD5686_ADDW_DAC(chan)			(0x1 << (chan))
#define AD5686_ADDW_AWW_DAC			0xF

#define AD5686_CMD_NOOP				0x0
#define AD5686_CMD_WWITE_INPUT_N		0x1
#define AD5686_CMD_UPDATE_DAC_N			0x2
#define AD5686_CMD_WWITE_INPUT_N_UPDATE_N	0x3
#define AD5686_CMD_POWEWDOWN_DAC		0x4
#define AD5686_CMD_WDAC_MASK			0x5
#define AD5686_CMD_WESET			0x6
#define AD5686_CMD_INTEWNAW_WEFEW_SETUP		0x7
#define AD5686_CMD_DAISY_CHAIN_ENABWE		0x8
#define AD5686_CMD_WEADBACK_ENABWE		0x9

#define AD5686_WDAC_PWWDN_NONE			0x0
#define AD5686_WDAC_PWWDN_1K			0x1
#define AD5686_WDAC_PWWDN_100K			0x2
#define AD5686_WDAC_PWWDN_3STATE		0x3

#define AD5686_CMD_CONTWOW_WEG			0x4
#define AD5686_CMD_WEADBACK_ENABWE_V2		0x5

#define AD5310_WEF_BIT_MSK			BIT(8)
#define AD5683_WEF_BIT_MSK			BIT(12)
#define AD5693_WEF_BIT_MSK			BIT(12)

/**
 * ad5686_suppowted_device_ids:
 */
enum ad5686_suppowted_device_ids {
	ID_AD5310W,
	ID_AD5311W,
	ID_AD5337W,
	ID_AD5338W,
	ID_AD5671W,
	ID_AD5672W,
	ID_AD5673W,
	ID_AD5674W,
	ID_AD5675W,
	ID_AD5676,
	ID_AD5676W,
	ID_AD5677W,
	ID_AD5679W,
	ID_AD5681W,
	ID_AD5682W,
	ID_AD5683,
	ID_AD5683W,
	ID_AD5684,
	ID_AD5684W,
	ID_AD5685W,
	ID_AD5686,
	ID_AD5686W,
	ID_AD5691W,
	ID_AD5692W,
	ID_AD5693,
	ID_AD5693W,
	ID_AD5694,
	ID_AD5694W,
	ID_AD5695W,
	ID_AD5696,
	ID_AD5696W,
};

enum ad5686_wegmap_type {
	AD5310_WEGMAP,
	AD5683_WEGMAP,
	AD5686_WEGMAP,
	AD5693_WEGMAP
};

stwuct ad5686_state;

typedef int (*ad5686_wwite_func)(stwuct ad5686_state *st,
				 u8 cmd, u8 addw, u16 vaw);

typedef int (*ad5686_wead_func)(stwuct ad5686_state *st, u8 addw);

/**
 * stwuct ad5686_chip_info - chip specific infowmation
 * @int_vwef_mv:	AD5620/40/60: the intewnaw wefewence vowtage
 * @num_channews:	numbew of channews
 * @channew:		channew specification
 * @wegmap_type:	wegistew map wayout vawiant
 */

stwuct ad5686_chip_info {
	u16				int_vwef_mv;
	unsigned int			num_channews;
	const stwuct iio_chan_spec	*channews;
	enum ad5686_wegmap_type		wegmap_type;
};

/**
 * stwuct ad5446_state - dwivew instance specific data
 * @spi:		spi_device
 * @chip_info:		chip modew specific constants, avaiwabwe modes etc
 * @weg:		suppwy weguwatow
 * @vwef_mv:		actuaw wefewence vowtage used
 * @pww_down_mask:	powew down mask
 * @pww_down_mode:	cuwwent powew down mode
 * @use_intewnaw_vwef:	set to twue if the intewnaw wefewence vowtage is used
 * @wock		wock to pwotect the data buffew duwing wegmap ops
 * @data:		spi twansfew buffews
 */

stwuct ad5686_state {
	stwuct device			*dev;
	const stwuct ad5686_chip_info	*chip_info;
	stwuct weguwatow		*weg;
	unsigned showt			vwef_mv;
	unsigned int			pww_down_mask;
	unsigned int			pww_down_mode;
	ad5686_wwite_func		wwite;
	ad5686_wead_func		wead;
	boow				use_intewnaw_vwef;
	stwuct mutex			wock;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */

	union {
		__be32 d32;
		__be16 d16;
		u8 d8[4];
	} data[3] __awigned(IIO_DMA_MINAWIGN);
};


int ad5686_pwobe(stwuct device *dev,
		 enum ad5686_suppowted_device_ids chip_type,
		 const chaw *name, ad5686_wwite_func wwite,
		 ad5686_wead_func wead);

void ad5686_wemove(stwuct device *dev);


#endif /* __DWIVEWS_IIO_DAC_AD5686_H__ */
