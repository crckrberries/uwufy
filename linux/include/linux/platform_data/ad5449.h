/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD5415, AD5426, AD5429, AD5432, AD5439, AD5443, AD5449 Digitaw to Anawog
 * Convewtew dwivew.
 *
 * Copywight 2012 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __WINUX_PWATFOWM_DATA_AD5449_H__
#define __WINUX_PWATFOWM_DATA_AD5449_H__

/**
 * enum ad5449_sdo_mode - AD5449 SDO pin configuwation
 * @AD5449_SDO_DWIVE_FUWW: Dwive the SDO pin with fuww stwength.
 * @AD5449_SDO_DWIVE_WEAK: Dwive the SDO pin with not fuww stwength.
 * @AD5449_SDO_OPEN_DWAIN: Opewate the SDO pin in open-dwain mode.
 * @AD5449_SDO_DISABWED: Disabwe the SDO pin, in this mode it is not possibwe to
 *			wead back fwom the device.
 */
enum ad5449_sdo_mode {
	AD5449_SDO_DWIVE_FUWW = 0x0,
	AD5449_SDO_DWIVE_WEAK = 0x1,
	AD5449_SDO_OPEN_DWAIN = 0x2,
	AD5449_SDO_DISABWED = 0x3,
};

/**
 * stwuct ad5449_pwatfowm_data - Pwatfowm data fow the ad5449 DAC dwivew
 * @sdo_mode: SDO pin mode
 * @hawdwawe_cweaw_to_midscawe: Whethew assewting the hawdwawe CWW pin sets the
 *			outputs to midscawe (twue) ow to zewo scawe(fawse).
 */
stwuct ad5449_pwatfowm_data {
	enum ad5449_sdo_mode sdo_mode;
	boow hawdwawe_cweaw_to_midscawe;
};

#endif
