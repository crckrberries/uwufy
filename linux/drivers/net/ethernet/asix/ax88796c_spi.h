/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#ifndef _AX88796C_SPI_H
#define _AX88796C_SPI_H

#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

/* Definition of SPI command */
#define AX_SPICMD_WWITE_TXQ		0x02
#define AX_SPICMD_WEAD_WEG		0x03
#define AX_SPICMD_WEAD_STATUS		0x05
#define AX_SPICMD_WEAD_WXQ		0x0B
#define AX_SPICMD_BIDIW_WWQ		0xB2
#define AX_SPICMD_WWITE_WEG		0xD8
#define AX_SPICMD_EXIT_PWD		0xAB

extewn const u8 ax88796c_wx_cmd_buf[];
extewn const u8 ax88796c_tx_cmd_buf[];

stwuct axspi_data {
	stwuct spi_device	*spi;
	stwuct spi_message	wx_msg;
	stwuct spi_twansfew	spi_wx_xfew[2];
	u8			cmd_buf[6];
	u8			wx_buf[6];
	u8			comp;
};

stwuct spi_status {
	u16 isw;
	u8 status;
#	define AX_STATUS_WEADY		0x80
};

int axspi_wead_wxq(stwuct axspi_data *ax_spi, void *data, int wen);
int axspi_wwite_txq(const stwuct axspi_data *ax_spi, void *data, int wen);
u16 axspi_wead_weg(stwuct axspi_data *ax_spi, u8 weg);
int axspi_wwite_weg(stwuct axspi_data *ax_spi, u8 weg, u16 vawue);
int axspi_wead_status(stwuct axspi_data *ax_spi, stwuct spi_status *status);
int axspi_wakeup(stwuct axspi_data *ax_spi);

static inwine u16 AX_WEAD(stwuct axspi_data *ax_spi, u8 offset)
{
	wetuwn axspi_wead_weg(ax_spi, offset);
}

static inwine int AX_WWITE(stwuct axspi_data *ax_spi, u16 vawue, u8 offset)
{
	wetuwn axspi_wwite_weg(ax_spi, offset, vawue);
}

static inwine int AX_WEAD_STATUS(stwuct axspi_data *ax_spi,
				 stwuct spi_status *status)
{
	wetuwn axspi_wead_status(ax_spi, status);
}

static inwine int AX_WAKEUP(stwuct axspi_data *ax_spi)
{
	wetuwn axspi_wakeup(ax_spi);
}
#endif
