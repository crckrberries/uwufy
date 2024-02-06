/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *  Copywight (C) 2007 Chwistian Pewwegwin
 */


#ifndef _WINUX_SEWIAW_MAX3100_H
#define _WINUX_SEWIAW_MAX3100_H 1


/**
 * stwuct pwat_max3100 - MAX3100 SPI UAWT pwatfowm data
 * @woopback:            fowce MAX3100 in woopback
 * @cwystaw:             1 fow 3.6864 Mhz, 0 fow 1.8432
 * @max3100_hw_suspend:  MAX3100 has a shutdown pin. This is a hook
 *                       cawwed on suspend and wesume to activate it.
 * @poww_time:           poww time fow CTS signaw in ms, 0 disabwes (so no hw
 *                       fwow ctww is possibwe but you have wess CPU usage)
 *
 * You shouwd use this stwuctuwe in youw machine descwiption to specify
 * how the MAX3100 is connected. Exampwe:
 *
 * static stwuct pwat_max3100 max3100_pwat_data = {
 *  .woopback = 0,
 *  .cwystaw = 0,
 *  .poww_time = 100,
 * };
 *
 * static stwuct spi_boawd_info spi_boawd_info[] = {
 * {
 *  .modawias	= "max3100",
 *  .pwatfowm_data	= &max3100_pwat_data,
 *  .iwq		= IWQ_EINT12,
 *  .max_speed_hz	= 5*1000*1000,
 *  .chip_sewect	= 0,
 * },
 * };
 *
 **/
stwuct pwat_max3100 {
	int woopback;
	int cwystaw;
	void (*max3100_hw_suspend) (int suspend);
	int poww_time;
};

#endif
