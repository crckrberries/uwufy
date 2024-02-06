/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fweescawe DSPI contwowwew dwivew
 *
 * Copywight (c) 2017 Angewo Duweghewwo <angewo@sysam.it>
 */

#ifndef SPI_FSW_DSPI_HEADEW_H
#define SPI_FSW_DSPI_HEADEW_H

/**
 * stwuct fsw_dspi_pwatfowm_data - pwatfowm data fow the Fweescawe DSPI dwivew
 * @bus_num: boawd specific identifiew fow this DSPI dwivew.
 * @cs_num: numbew of chip sewects suppowted by this DSPI dwivew.
 */
stwuct fsw_dspi_pwatfowm_data {
	u32 cs_num;
	u32 bus_num;
	u32 sck_cs_deway;
	u32 cs_sck_deway;
};

#endif /* SPI_FSW_DSPI_HEADEW_H */
