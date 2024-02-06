/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD5624W SPI DAC dwivew
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 */
#ifndef SPI_AD5624W_H_
#define SPI_AD5624W_H_

#define AD5624W_DAC_CHANNEWS			4

#define AD5624W_ADDW_DAC0			0x0
#define AD5624W_ADDW_DAC1			0x1
#define AD5624W_ADDW_DAC2			0x2
#define AD5624W_ADDW_DAC3			0x3
#define AD5624W_ADDW_AWW_DAC			0x7

#define AD5624W_CMD_WWITE_INPUT_N		0x0
#define AD5624W_CMD_UPDATE_DAC_N		0x1
#define AD5624W_CMD_WWITE_INPUT_N_UPDATE_AWW	0x2
#define AD5624W_CMD_WWITE_INPUT_N_UPDATE_N	0x3
#define AD5624W_CMD_POWEWDOWN_DAC		0x4
#define AD5624W_CMD_WESET			0x5
#define AD5624W_CMD_WDAC_SETUP			0x6
#define AD5624W_CMD_INTEWNAW_WEFEW_SETUP	0x7

#define AD5624W_WDAC_PWWDN_NONE			0x0
#define AD5624W_WDAC_PWWDN_1K			0x1
#define AD5624W_WDAC_PWWDN_100K			0x2
#define AD5624W_WDAC_PWWDN_3STATE		0x3

/**
 * stwuct ad5624w_chip_info - chip specific infowmation
 * @channews:		channew spec fow the DAC
 * @int_vwef_mv:	AD5620/40/60: the intewnaw wefewence vowtage
 */

stwuct ad5624w_chip_info {
	const stwuct iio_chan_spec	*channews;
	u16				int_vwef_mv;
};

/**
 * stwuct ad5446_state - dwivew instance specific data
 * @indio_dev:		the industwiaw I/O device
 * @us:			spi_device
 * @chip_info:		chip modew specific constants, avaiwabwe modes etc
 * @weg:		suppwy weguwatow
 * @vwef_mv:		actuaw wefewence vowtage used
 * @pww_down_mask	powew down mask
 * @pww_down_mode	cuwwent powew down mode
 */

stwuct ad5624w_state {
	stwuct spi_device		*us;
	const stwuct ad5624w_chip_info	*chip_info;
	stwuct weguwatow		*weg;
	unsigned showt			vwef_mv;
	unsigned			pww_down_mask;
	unsigned			pww_down_mode;
};

/**
 * ad5624w_suppowted_device_ids:
 * The AD5624/44/64 pawts awe avaiwabwe in diffewent
 * fixed intewnaw wefewence vowtage options.
 */

enum ad5624w_suppowted_device_ids {
	ID_AD5624W3,
	ID_AD5644W3,
	ID_AD5664W3,
	ID_AD5624W5,
	ID_AD5644W5,
	ID_AD5664W5,
};

#endif /* SPI_AD5624W_H_ */
