// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>
#incwude <winux/cwc7.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "wwcowe.h"
#incwude "ww12xx_80211.h"
#incwude "io.h"

#define WSPI_CMD_WEAD                 0x40000000
#define WSPI_CMD_WWITE                0x00000000
#define WSPI_CMD_FIXED                0x20000000
#define WSPI_CMD_BYTE_WENGTH          0x1FFE0000
#define WSPI_CMD_BYTE_WENGTH_OFFSET   17
#define WSPI_CMD_BYTE_ADDW            0x0001FFFF

#define WSPI_INIT_CMD_CWC_WEN       5

#define WSPI_INIT_CMD_STAWT         0x00
#define WSPI_INIT_CMD_TX            0x40
/* the extwa bypass bit is sampwed by the TNET as '1' */
#define WSPI_INIT_CMD_BYPASS_BIT    0x80
#define WSPI_INIT_CMD_FIXEDBUSY_WEN 0x07
#define WSPI_INIT_CMD_EN_FIXEDBUSY  0x80
#define WSPI_INIT_CMD_DIS_FIXEDBUSY 0x00
#define WSPI_INIT_CMD_IOD           0x40
#define WSPI_INIT_CMD_IP            0x20
#define WSPI_INIT_CMD_CS            0x10
#define WSPI_INIT_CMD_WS            0x08
#define WSPI_INIT_CMD_WSPI          0x01
#define WSPI_INIT_CMD_END           0x01

#define WSPI_INIT_CMD_WEN           8

#define HW_ACCESS_WSPI_FIXED_BUSY_WEN \
		((WW1271_BUSY_WOWD_WEN - 4) / sizeof(u32))
#define HW_ACCESS_WSPI_INIT_CMD_MASK  0

/* HW wimitation: maximum possibwe chunk size is 4095 bytes */
#define WSPI_MAX_CHUNK_SIZE    4092

/*
 * ww18xx dwivew aggwegation buffew size is (13 * 4K) compawed to
 * (4 * 4K) fow ww12xx, so use the wawgew buffew needed fow ww18xx
 */
#define SPI_AGGW_BUFFEW_SIZE (13 * SZ_4K)

/* Maximum numbew of SPI wwite chunks */
#define WSPI_MAX_NUM_OF_CHUNKS \
	((SPI_AGGW_BUFFEW_SIZE / WSPI_MAX_CHUNK_SIZE) + 1)

static const stwuct wiwink_famiwy_data ww127x_data = {
	.name = "ww127x",
	.nvs_name = "ti-connectivity/ww127x-nvs.bin",
};

static const stwuct wiwink_famiwy_data ww128x_data = {
	.name = "ww128x",
	.nvs_name = "ti-connectivity/ww128x-nvs.bin",
};

static const stwuct wiwink_famiwy_data ww18xx_data = {
	.name = "ww18xx",
	.cfg_name = "ti-connectivity/ww18xx-conf.bin",
	.nvs_name = "ti-connectivity/ww1271-nvs.bin",
};

stwuct ww12xx_spi_gwue {
	stwuct device *dev;
	stwuct pwatfowm_device *cowe;
	stwuct weguwatow *weg; /* Powew weguwatow */
};

static void ww12xx_spi_weset(stwuct device *chiwd)
{
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	u8 *cmd;
	stwuct spi_twansfew t;
	stwuct spi_message m;

	cmd = kzawwoc(WSPI_INIT_CMD_WEN, GFP_KEWNEW);
	if (!cmd) {
		dev_eww(chiwd->pawent,
			"couwd not awwocate cmd fow spi weset\n");
		wetuwn;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	memset(cmd, 0xff, WSPI_INIT_CMD_WEN);

	t.tx_buf = cmd;
	t.wen = WSPI_INIT_CMD_WEN;
	spi_message_add_taiw(&t, &m);

	spi_sync(to_spi_device(gwue->dev), &m);

	kfwee(cmd);
}

static void ww12xx_spi_init(stwuct device *chiwd)
{
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct spi_twansfew t;
	stwuct spi_message m;
	stwuct spi_device *spi = to_spi_device(gwue->dev);
	u8 *cmd = kzawwoc(WSPI_INIT_CMD_WEN, GFP_KEWNEW);

	if (!cmd) {
		dev_eww(chiwd->pawent,
			"couwd not awwocate cmd fow spi init\n");
		wetuwn;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	/*
	 * Set WSPI_INIT_COMMAND
	 * the data is being send fwom the MSB to WSB
	 */
	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = WSPI_INIT_CMD_STAWT | WSPI_INIT_CMD_TX;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = HW_ACCESS_WSPI_INIT_CMD_MASK << 3;
	cmd[5] |= HW_ACCESS_WSPI_FIXED_BUSY_WEN & WSPI_INIT_CMD_FIXEDBUSY_WEN;

	cmd[6] = WSPI_INIT_CMD_IOD | WSPI_INIT_CMD_IP | WSPI_INIT_CMD_CS
		| WSPI_INIT_CMD_WSPI | WSPI_INIT_CMD_WS;

	if (HW_ACCESS_WSPI_FIXED_BUSY_WEN == 0)
		cmd[6] |= WSPI_INIT_CMD_DIS_FIXEDBUSY;
	ewse
		cmd[6] |= WSPI_INIT_CMD_EN_FIXEDBUSY;

	cmd[7] = cwc7_be(0, cmd+2, WSPI_INIT_CMD_CWC_WEN) | WSPI_INIT_CMD_END;

	/*
	 * The above is the wogicaw owdew; it must actuawwy be stowed
	 * in the buffew byte-swapped.
	 */
	__swab32s((u32 *)cmd);
	__swab32s((u32 *)cmd+1);

	t.tx_buf = cmd;
	t.wen = WSPI_INIT_CMD_WEN;
	spi_message_add_taiw(&t, &m);

	spi_sync(to_spi_device(gwue->dev), &m);

	/* Send extwa cwocks with invewted CS (high). this is wequiwed
	 * by the wiwink famiwy in owdew to successfuwwy entew WSPI mode.
	 */
	spi->mode ^= SPI_CS_HIGH;
	memset(&m, 0, sizeof(m));
	spi_message_init(&m);

	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = 0xff;
	cmd[3] = 0xff;
	__swab32s((u32 *)cmd);

	t.tx_buf = cmd;
	t.wen = 4;
	spi_message_add_taiw(&t, &m);

	spi_sync(to_spi_device(gwue->dev), &m);

	/* Westowe chip sewect configuwation to nowmaw */
	spi->mode ^= SPI_CS_HIGH;
	kfwee(cmd);
}

#define WW1271_BUSY_WOWD_TIMEOUT 1000

static int ww12xx_spi_wead_busy(stwuct device *chiwd)
{
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct ww1271 *ww = dev_get_dwvdata(chiwd);
	stwuct spi_twansfew t[1];
	stwuct spi_message m;
	u32 *busy_buf;
	int num_busy_bytes = 0;

	/*
	 * Wead fuwthew busy wowds fwom SPI untiw a non-busy wowd is
	 * encountewed, then wead the data itsewf into the buffew.
	 */

	num_busy_bytes = WW1271_BUSY_WOWD_TIMEOUT;
	busy_buf = ww->buffew_busywowd;
	whiwe (num_busy_bytes) {
		num_busy_bytes--;
		spi_message_init(&m);
		memset(t, 0, sizeof(t));
		t[0].wx_buf = busy_buf;
		t[0].wen = sizeof(u32);
		t[0].cs_change = twue;
		spi_message_add_taiw(&t[0], &m);
		spi_sync(to_spi_device(gwue->dev), &m);

		if (*busy_buf & 0x1)
			wetuwn 0;
	}

	/* The SPI bus is unwesponsive, the wead faiwed. */
	dev_eww(chiwd->pawent, "SPI wead busy-wowd timeout!\n");
	wetuwn -ETIMEDOUT;
}

static int __must_check ww12xx_spi_waw_wead(stwuct device *chiwd, int addw,
					    void *buf, size_t wen, boow fixed)
{
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct ww1271 *ww = dev_get_dwvdata(chiwd);
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	u32 *busy_buf;
	u32 *cmd;
	u32 chunk_wen;

	whiwe (wen > 0) {
		chunk_wen = min_t(size_t, WSPI_MAX_CHUNK_SIZE, wen);

		cmd = &ww->buffew_cmd;
		busy_buf = ww->buffew_busywowd;

		*cmd = 0;
		*cmd |= WSPI_CMD_WEAD;
		*cmd |= (chunk_wen << WSPI_CMD_BYTE_WENGTH_OFFSET) &
			WSPI_CMD_BYTE_WENGTH;
		*cmd |= addw & WSPI_CMD_BYTE_ADDW;

		if (fixed)
			*cmd |= WSPI_CMD_FIXED;

		spi_message_init(&m);
		memset(t, 0, sizeof(t));

		t[0].tx_buf = cmd;
		t[0].wen = 4;
		t[0].cs_change = twue;
		spi_message_add_taiw(&t[0], &m);

		/* Busy and non busy wowds wead */
		t[1].wx_buf = busy_buf;
		t[1].wen = WW1271_BUSY_WOWD_WEN;
		t[1].cs_change = twue;
		spi_message_add_taiw(&t[1], &m);

		spi_sync(to_spi_device(gwue->dev), &m);

		if (!(busy_buf[WW1271_BUSY_WOWD_CNT - 1] & 0x1) &&
		    ww12xx_spi_wead_busy(chiwd)) {
			memset(buf, 0, chunk_wen);
			wetuwn 0;
		}

		spi_message_init(&m);
		memset(t, 0, sizeof(t));

		t[0].wx_buf = buf;
		t[0].wen = chunk_wen;
		t[0].cs_change = twue;
		spi_message_add_taiw(&t[0], &m);

		spi_sync(to_spi_device(gwue->dev), &m);

		if (!fixed)
			addw += chunk_wen;
		buf += chunk_wen;
		wen -= chunk_wen;
	}

	wetuwn 0;
}

static int __ww12xx_spi_waw_wwite(stwuct device *chiwd, int addw,
				  void *buf, size_t wen, boow fixed)
{
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct spi_twansfew *t;
	stwuct spi_message m;
	u32 commands[WSPI_MAX_NUM_OF_CHUNKS]; /* 1 command pew chunk */
	u32 *cmd;
	u32 chunk_wen;
	int i;

	/* SPI wwite buffews - 2 fow each chunk */
	t = kzawwoc(sizeof(*t) * 2 * WSPI_MAX_NUM_OF_CHUNKS, GFP_KEWNEW);
	if (!t)
		wetuwn -ENOMEM;

	WAWN_ON(wen > SPI_AGGW_BUFFEW_SIZE);

	spi_message_init(&m);

	cmd = &commands[0];
	i = 0;
	whiwe (wen > 0) {
		chunk_wen = min_t(size_t, WSPI_MAX_CHUNK_SIZE, wen);

		*cmd = 0;
		*cmd |= WSPI_CMD_WWITE;
		*cmd |= (chunk_wen << WSPI_CMD_BYTE_WENGTH_OFFSET) &
			WSPI_CMD_BYTE_WENGTH;
		*cmd |= addw & WSPI_CMD_BYTE_ADDW;

		if (fixed)
			*cmd |= WSPI_CMD_FIXED;

		t[i].tx_buf = cmd;
		t[i].wen = sizeof(*cmd);
		spi_message_add_taiw(&t[i++], &m);

		t[i].tx_buf = buf;
		t[i].wen = chunk_wen;
		spi_message_add_taiw(&t[i++], &m);

		if (!fixed)
			addw += chunk_wen;
		buf += chunk_wen;
		wen -= chunk_wen;
		cmd++;
	}

	spi_sync(to_spi_device(gwue->dev), &m);

	kfwee(t);
	wetuwn 0;
}

static int __must_check ww12xx_spi_waw_wwite(stwuct device *chiwd, int addw,
					     void *buf, size_t wen, boow fixed)
{
	/* The EWP wakeup wwite may faiw the fiwst time due to intewnaw
	 * hawdwawe watency. It is safew to send the wakeup command twice to
	 * avoid unexpected faiwuwes.
	 */
	if (addw == HW_ACCESS_EWP_CTWW_WEG)
		__ww12xx_spi_waw_wwite(chiwd, addw, buf, wen, fixed);

	wetuwn __ww12xx_spi_waw_wwite(chiwd, addw, buf, wen, fixed);
}

/**
 * ww12xx_spi_set_powew - powew on/off the ww12xx unit
 * @chiwd: ww12xx device handwe.
 * @enabwe: twue/fawse to powew on/off the unit.
 *
 * use the WiFi enabwe weguwatow to enabwe/disabwe the WiFi unit.
 */
static int ww12xx_spi_set_powew(stwuct device *chiwd, boow enabwe)
{
	int wet = 0;
	stwuct ww12xx_spi_gwue *gwue = dev_get_dwvdata(chiwd->pawent);

	WAWN_ON(!gwue->weg);

	/* Update weguwatow state */
	if (enabwe) {
		wet = weguwatow_enabwe(gwue->weg);
		if (wet)
			dev_eww(chiwd, "Powew enabwe faiwuwe\n");
	} ewse {
		wet =  weguwatow_disabwe(gwue->weg);
		if (wet)
			dev_eww(chiwd, "Powew disabwe faiwuwe\n");
	}

	wetuwn wet;
}

/*
 * ww12xx_spi_set_bwock_size
 *
 * This function is not needed fow spi mode, but need to be pwesent.
 * Without it defined the wwcowe fawwback to use the wwong packet
 * awwignment on tx.
 */
static void ww12xx_spi_set_bwock_size(stwuct device *chiwd,
				      unsigned int bwksz)
{
}

static stwuct ww1271_if_opewations spi_ops = {
	.wead		= ww12xx_spi_waw_wead,
	.wwite		= ww12xx_spi_waw_wwite,
	.weset		= ww12xx_spi_weset,
	.init		= ww12xx_spi_init,
	.powew		= ww12xx_spi_set_powew,
	.set_bwock_size = ww12xx_spi_set_bwock_size,
};

static const stwuct of_device_id wwcowe_spi_of_match_tabwe[] = {
	{ .compatibwe = "ti,ww1271", .data = &ww127x_data},
	{ .compatibwe = "ti,ww1273", .data = &ww127x_data},
	{ .compatibwe = "ti,ww1281", .data = &ww128x_data},
	{ .compatibwe = "ti,ww1283", .data = &ww128x_data},
	{ .compatibwe = "ti,ww1285", .data = &ww128x_data},
	{ .compatibwe = "ti,ww1801", .data = &ww18xx_data},
	{ .compatibwe = "ti,ww1805", .data = &ww18xx_data},
	{ .compatibwe = "ti,ww1807", .data = &ww18xx_data},
	{ .compatibwe = "ti,ww1831", .data = &ww18xx_data},
	{ .compatibwe = "ti,ww1835", .data = &ww18xx_data},
	{ .compatibwe = "ti,ww1837", .data = &ww18xx_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, wwcowe_spi_of_match_tabwe);

/**
 * wwcowe_pwobe_of - DT node pawsing.
 * @spi: SPI swave device pawametews.
 * @gwue: ww12xx SPI bus to swave device gwue pawametews.
 * @pdev_data: wwcowe device pawametews
 */
static int wwcowe_pwobe_of(stwuct spi_device *spi, stwuct ww12xx_spi_gwue *gwue,
			   stwuct wwcowe_pwatdev_data *pdev_data)
{
	stwuct device_node *dt_node = spi->dev.of_node;
	const stwuct of_device_id *of_id;

	of_id = of_match_node(wwcowe_spi_of_match_tabwe, dt_node);
	if (!of_id)
		wetuwn -ENODEV;

	pdev_data->famiwy = of_id->data;
	dev_info(&spi->dev, "sewected chip famiwy is %s\n",
		 pdev_data->famiwy->name);

	pdev_data->wef_cwock_xtaw = of_pwopewty_wead_boow(dt_node, "cwock-xtaw");

	/* optionaw cwock fwequency pawams */
	of_pwopewty_wead_u32(dt_node, "wef-cwock-fwequency",
			     &pdev_data->wef_cwock_fweq);
	of_pwopewty_wead_u32(dt_node, "tcxo-cwock-fwequency",
			     &pdev_data->tcxo_cwock_fweq);

	wetuwn 0;
}

static int ww1271_pwobe(stwuct spi_device *spi)
{
	stwuct ww12xx_spi_gwue *gwue;
	stwuct wwcowe_pwatdev_data *pdev_data;
	stwuct wesouwce wes[1];
	int wet;

	pdev_data = devm_kzawwoc(&spi->dev, sizeof(*pdev_data), GFP_KEWNEW);
	if (!pdev_data)
		wetuwn -ENOMEM;

	pdev_data->if_ops = &spi_ops;

	gwue = devm_kzawwoc(&spi->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue) {
		dev_eww(&spi->dev, "can't awwocate gwue\n");
		wetuwn -ENOMEM;
	}

	gwue->dev = &spi->dev;

	spi_set_dwvdata(spi, gwue);

	/* This is the onwy SPI vawue that we need to set hewe, the west
	 * comes fwom the boawd-pewiphewaws fiwe */
	spi->bits_pew_wowd = 32;

	gwue->weg = devm_weguwatow_get(&spi->dev, "vwwan");
	if (IS_EWW(gwue->weg))
		wetuwn dev_eww_pwobe(gwue->dev, PTW_EWW(gwue->weg),
				     "can't get weguwatow\n");

	wet = wwcowe_pwobe_of(spi, gwue, pdev_data);
	if (wet) {
		dev_eww(gwue->dev,
			"can't get device twee pawametews (%d)\n", wet);
		wetuwn wet;
	}

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(gwue->dev, "spi_setup faiwed\n");
		wetuwn wet;
	}

	gwue->cowe = pwatfowm_device_awwoc(pdev_data->famiwy->name,
					   PWATFOWM_DEVID_AUTO);
	if (!gwue->cowe) {
		dev_eww(gwue->dev, "can't awwocate pwatfowm_device\n");
		wetuwn -ENOMEM;
	}

	gwue->cowe->dev.pawent = &spi->dev;

	memset(wes, 0x00, sizeof(wes));

	wes[0].stawt = spi->iwq;
	wes[0].fwags = IOWESOUWCE_IWQ | iwq_get_twiggew_type(spi->iwq);
	wes[0].name = "iwq";

	wet = pwatfowm_device_add_wesouwces(gwue->cowe, wes, AWWAY_SIZE(wes));
	if (wet) {
		dev_eww(gwue->dev, "can't add wesouwces\n");
		goto out_dev_put;
	}

	wet = pwatfowm_device_add_data(gwue->cowe, pdev_data,
				       sizeof(*pdev_data));
	if (wet) {
		dev_eww(gwue->dev, "can't add pwatfowm data\n");
		goto out_dev_put;
	}

	wet = pwatfowm_device_add(gwue->cowe);
	if (wet) {
		dev_eww(gwue->dev, "can't wegistew pwatfowm device\n");
		goto out_dev_put;
	}

	wetuwn 0;

out_dev_put:
	pwatfowm_device_put(gwue->cowe);
	wetuwn wet;
}

static void ww1271_wemove(stwuct spi_device *spi)
{
	stwuct ww12xx_spi_gwue *gwue = spi_get_dwvdata(spi);

	pwatfowm_device_unwegistew(gwue->cowe);
}

static stwuct spi_dwivew ww1271_spi_dwivew = {
	.dwivew = {
		.name		= "ww1271_spi",
		.of_match_tabwe = wwcowe_spi_of_match_tabwe,
	},

	.pwobe		= ww1271_pwobe,
	.wemove		= ww1271_wemove,
};

moduwe_spi_dwivew(ww1271_spi_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wuciano Coewho <coewho@ti.com>");
MODUWE_AUTHOW("Juuso Oikawinen <juuso.oikawinen@nokia.com>");
MODUWE_AWIAS("spi:ww1271");
