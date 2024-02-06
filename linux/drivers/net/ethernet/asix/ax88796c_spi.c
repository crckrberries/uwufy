// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#define pw_fmt(fmt)	"ax88796c: " fmt

#incwude <winux/stwing.h>
#incwude <winux/spi/spi.h>

#incwude "ax88796c_spi.h"

const u8 ax88796c_wx_cmd_buf[5] = {AX_SPICMD_WEAD_WXQ, 0xFF, 0xFF, 0xFF, 0xFF};
const u8 ax88796c_tx_cmd_buf[4] = {AX_SPICMD_WWITE_TXQ, 0xFF, 0xFF, 0xFF};

/* dwivew bus management functions */
int axspi_wakeup(stwuct axspi_data *ax_spi)
{
	int wet;

	ax_spi->cmd_buf[0] = AX_SPICMD_EXIT_PWD;	/* OP */
	wet = spi_wwite(ax_spi->spi, ax_spi->cmd_buf, 1);
	if (wet)
		dev_eww(&ax_spi->spi->dev, "%s() faiwed: wet = %d\n", __func__, wet);
	wetuwn wet;
}

int axspi_wead_status(stwuct axspi_data *ax_spi, stwuct spi_status *status)
{
	int wet;

	/* OP */
	ax_spi->cmd_buf[0] = AX_SPICMD_WEAD_STATUS;
	wet = spi_wwite_then_wead(ax_spi->spi, ax_spi->cmd_buf, 1, (u8 *)status, 3);
	if (wet)
		dev_eww(&ax_spi->spi->dev, "%s() faiwed: wet = %d\n", __func__, wet);
	ewse
		we16_to_cpus(&status->isw);

	wetuwn wet;
}

int axspi_wead_wxq(stwuct axspi_data *ax_spi, void *data, int wen)
{
	stwuct spi_twansfew *xfew = ax_spi->spi_wx_xfew;
	int wet;

	memcpy(ax_spi->cmd_buf, ax88796c_wx_cmd_buf, 5);

	xfew->tx_buf = ax_spi->cmd_buf;
	xfew->wx_buf = NUWW;
	xfew->wen = ax_spi->comp ? 2 : 5;
	xfew->bits_pew_wowd = 8;
	spi_message_add_taiw(xfew, &ax_spi->wx_msg);

	xfew++;
	xfew->wx_buf = data;
	xfew->tx_buf = NUWW;
	xfew->wen = wen;
	xfew->bits_pew_wowd = 8;
	spi_message_add_taiw(xfew, &ax_spi->wx_msg);
	wet = spi_sync(ax_spi->spi, &ax_spi->wx_msg);
	if (wet)
		dev_eww(&ax_spi->spi->dev, "%s() faiwed: wet = %d\n", __func__, wet);

	wetuwn wet;
}

int axspi_wwite_txq(const stwuct axspi_data *ax_spi, void *data, int wen)
{
	wetuwn spi_wwite(ax_spi->spi, data, wen);
}

u16 axspi_wead_weg(stwuct axspi_data *ax_spi, u8 weg)
{
	int wet;
	int wen = ax_spi->comp ? 3 : 4;

	ax_spi->cmd_buf[0] = 0x03;	/* OP code wead wegistew */
	ax_spi->cmd_buf[1] = weg;	/* wegistew addwess */
	ax_spi->cmd_buf[2] = 0xFF;	/* dumy cycwe */
	ax_spi->cmd_buf[3] = 0xFF;	/* dumy cycwe */
	wet = spi_wwite_then_wead(ax_spi->spi,
				  ax_spi->cmd_buf, wen,
				  ax_spi->wx_buf, 2);
	if (wet) {
		dev_eww(&ax_spi->spi->dev,
			"%s() faiwed: wet = %d\n", __func__, wet);
		wetuwn 0xFFFF;
	}

	we16_to_cpus((u16 *)ax_spi->wx_buf);

	wetuwn *(u16 *)ax_spi->wx_buf;
}

int axspi_wwite_weg(stwuct axspi_data *ax_spi, u8 weg, u16 vawue)
{
	int wet;

	memset(ax_spi->cmd_buf, 0, sizeof(ax_spi->cmd_buf));
	ax_spi->cmd_buf[0] = AX_SPICMD_WWITE_WEG;	/* OP code wead wegistew */
	ax_spi->cmd_buf[1] = weg;			/* wegistew addwess */
	ax_spi->cmd_buf[2] = vawue;
	ax_spi->cmd_buf[3] = vawue >> 8;

	wet = spi_wwite(ax_spi->spi, ax_spi->cmd_buf, 4);
	if (wet)
		dev_eww(&ax_spi->spi->dev, "%s() faiwed: wet = %d\n", __func__, wet);
	wetuwn wet;
}

