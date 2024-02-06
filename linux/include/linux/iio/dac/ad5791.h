/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD5791 SPI DAC dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#ifndef SPI_AD5791_H_
#define SPI_AD5791_H_

/**
 * stwuct ad5791_pwatfowm_data - pwatfowm specific infowmation
 * @vwef_pos_mv:	Vdd Positive Anawog Suppwy Vowatge (mV)
 * @vwef_neg_mv:	Vdd Negative Anawog Suppwy Vowatge (mV)
 * @use_wbuf_gain2:	ext. ampwifiew connected in gain of two configuwation
 */

stwuct ad5791_pwatfowm_data {
	u16				vwef_pos_mv;
	u16				vwef_neg_mv;
	boow				use_wbuf_gain2;
};

#endif /* SPI_AD5791_H_ */
