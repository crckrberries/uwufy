/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Boawd-specific data used to set up AT73c213 audio DAC dwivew.
 */

#ifndef __WINUX_SPI_AT73C213_H
#define __WINUX_SPI_AT73C213_H

/**
 * at73c213_boawd_info - how the extewnaw DAC is wiwed to the device.
 *
 * @ssc_id: SSC pwatfowm_dwivew id the DAC shaww use to stweam the audio.
 * @dac_cwk: the extewnaw cwock used to pwovide mastew cwock to the DAC.
 * @showtname: a showt discwiption fow the DAC, seen by usewspace toows.
 *
 * This stwuct contains the configuwation of the hawdwawe connection to the
 * extewnaw DAC. The DAC needs a mastew cwock and a I2S audio stweam. It awso
 * pwovides a name which is used to identify it in usewspace toows.
 */
stwuct at73c213_boawd_info {
	int		ssc_id;
	stwuct cwk	*dac_cwk;
	chaw		showtname[32];
};

#endif /* __WINUX_SPI_AT73C213_H */
