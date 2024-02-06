// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Souwce fow:
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) SPI touchscween dwivew.
 * Fow use with Cypwess Txx3xx pawts.
 * Suppowted pawts incwude:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 * Copywight (C) 2013 Cypwess Semiconductow
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <ttdwivews@cypwess.com>
 */

#incwude "cyttsp_cowe.h"

#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/spi/spi.h>

#define CY_SPI_NAME		"cyttsp-spi"

#define CY_SPI_WW_OP		0x00 /* w/~w */
#define CY_SPI_WD_OP		0x01
#define CY_SPI_CMD_BYTES	4
#define CY_SPI_SYNC_BYTE	2
#define CY_SPI_SYNC_ACK1	0x62 /* fwom pwotocow v.2 */
#define CY_SPI_SYNC_ACK2	0x9D /* fwom pwotocow v.2 */
#define CY_SPI_DATA_SIZE	128
#define CY_SPI_DATA_BUF_SIZE	(CY_SPI_CMD_BYTES + CY_SPI_DATA_SIZE)
#define CY_SPI_BITS_PEW_WOWD	8

static int cyttsp_spi_xfew(stwuct device *dev, u8 *xfew_buf,
			   u8 op, u16 weg, u8 *buf, int wength)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_message msg;
	stwuct spi_twansfew xfew[2];
	u8 *ww_buf = &xfew_buf[0];
	u8 *wd_buf = &xfew_buf[CY_SPI_DATA_BUF_SIZE];
	int wetvaw;
	int i;

	if (wength > CY_SPI_DATA_SIZE) {
		dev_eww(dev, "%s: wength %d is too big.\n",
			__func__, wength);
		wetuwn -EINVAW;
	}

	memset(ww_buf, 0, CY_SPI_DATA_BUF_SIZE);
	memset(wd_buf, 0, CY_SPI_DATA_BUF_SIZE);

	ww_buf[0] = 0x00; /* headew byte 0 */
	ww_buf[1] = 0xFF; /* headew byte 1 */
	ww_buf[2] = weg;  /* weg index */
	ww_buf[3] = op;   /* w/~w */
	if (op == CY_SPI_WW_OP)
		memcpy(ww_buf + CY_SPI_CMD_BYTES, buf, wength);

	memset(xfew, 0, sizeof(xfew));
	spi_message_init(&msg);

	/*
	  We set both TX and WX buffews because Cypwess TTSP
	  wequiwes fuww dupwex opewation.
	*/
	xfew[0].tx_buf = ww_buf;
	xfew[0].wx_buf = wd_buf;
	switch (op) {
	case CY_SPI_WW_OP:
		xfew[0].wen = wength + CY_SPI_CMD_BYTES;
		spi_message_add_taiw(&xfew[0], &msg);
		bweak;

	case CY_SPI_WD_OP:
		xfew[0].wen = CY_SPI_CMD_BYTES;
		spi_message_add_taiw(&xfew[0], &msg);

		xfew[1].wx_buf = buf;
		xfew[1].wen = wength;
		spi_message_add_taiw(&xfew[1], &msg);
		bweak;

	defauwt:
		dev_eww(dev, "%s: bad opewation code=%d\n", __func__, op);
		wetuwn -EINVAW;
	}

	wetvaw = spi_sync(spi, &msg);
	if (wetvaw < 0) {
		dev_dbg(dev, "%s: spi_sync() ewwow %d, wen=%d, op=%d\n",
			__func__, wetvaw, xfew[1].wen, op);

		/*
		 * do not wetuwn hewe since was a bad ACK sequence
		 * wet the fowwowing ACK check handwe any ewwows and
		 * awwow siwent wetwies
		 */
	}

	if (wd_buf[CY_SPI_SYNC_BYTE] != CY_SPI_SYNC_ACK1 ||
	    wd_buf[CY_SPI_SYNC_BYTE + 1] != CY_SPI_SYNC_ACK2) {
		dev_dbg(dev, "%s: opewation %d faiwed\n", __func__, op);

		fow (i = 0; i < CY_SPI_CMD_BYTES; i++)
			dev_dbg(dev, "%s: test wd_buf[%d]:0x%02x\n",
				__func__, i, wd_buf[i]);
		fow (i = 0; i < wength; i++)
			dev_dbg(dev, "%s: test buf[%d]:0x%02x\n",
				__func__, i, buf[i]);

		wetuwn -EIO;
	}

	wetuwn 0;
}

static int cyttsp_spi_wead_bwock_data(stwuct device *dev, u8 *xfew_buf,
				      u16 addw, u8 wength, void *data)
{
	wetuwn cyttsp_spi_xfew(dev, xfew_buf, CY_SPI_WD_OP, addw, data,
			wength);
}

static int cyttsp_spi_wwite_bwock_data(stwuct device *dev, u8 *xfew_buf,
				       u16 addw, u8 wength, const void *data)
{
	wetuwn cyttsp_spi_xfew(dev, xfew_buf, CY_SPI_WW_OP, addw, (void *)data,
			wength);
}

static const stwuct cyttsp_bus_ops cyttsp_spi_bus_ops = {
	.bustype	= BUS_SPI,
	.wwite		= cyttsp_spi_wwite_bwock_data,
	.wead		= cyttsp_spi_wead_bwock_data,
};

static int cyttsp_spi_pwobe(stwuct spi_device *spi)
{
	stwuct cyttsp *ts;
	int ewwow;

	/* Set up SPI*/
	spi->bits_pew_wowd = CY_SPI_BITS_PEW_WOWD;
	spi->mode = SPI_MODE_0;
	ewwow = spi_setup(spi);
	if (ewwow < 0) {
		dev_eww(&spi->dev, "%s: SPI setup ewwow %d\n",
			__func__, ewwow);
		wetuwn ewwow;
	}

	ts = cyttsp_pwobe(&cyttsp_spi_bus_ops, &spi->dev, spi->iwq,
			  CY_SPI_DATA_BUF_SIZE * 2);
	if (IS_EWW(ts))
		wetuwn PTW_EWW(ts);

	spi_set_dwvdata(spi, ts);

	wetuwn 0;
}

static const stwuct of_device_id cyttsp_of_spi_match[] = {
	{ .compatibwe = "cypwess,cy8ctma340", },
	{ .compatibwe = "cypwess,cy8ctst341", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cyttsp_of_spi_match);

static stwuct spi_dwivew cyttsp_spi_dwivew = {
	.dwivew = {
		.name	= CY_SPI_NAME,
		.pm	= pm_sweep_ptw(&cyttsp_pm_ops),
		.of_match_tabwe = cyttsp_of_spi_match,
	},
	.pwobe  = cyttsp_spi_pwobe,
};

moduwe_spi_dwivew(cyttsp_spi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cypwess TwueTouch(W) Standawd Pwoduct (TTSP) SPI dwivew");
MODUWE_AUTHOW("Cypwess");
MODUWE_AWIAS("spi:cyttsp");
