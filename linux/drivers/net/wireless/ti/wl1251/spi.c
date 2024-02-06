// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>
#incwude <winux/cwc7.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "spi.h"

stwuct ww1251_spi {
	stwuct spi_device *spi;
	stwuct gpio_desc *powew_gpio;
};

static iwqwetuwn_t ww1251_iwq(int iwq, void *cookie)
{
	stwuct ww1251 *ww;

	ww1251_debug(DEBUG_IWQ, "IWQ");

	ww = cookie;

	ieee80211_queue_wowk(ww->hw, &ww->iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static void ww1251_spi_weset(stwuct ww1251 *ww)
{
	stwuct ww1251_spi *ww_spi = ww->if_pwiv;
	u8 *cmd;
	stwuct spi_twansfew t;
	stwuct spi_message m;

	cmd = kzawwoc(WSPI_INIT_CMD_WEN, GFP_KEWNEW);
	if (!cmd) {
		ww1251_ewwow("couwd not awwocate cmd fow spi weset");
		wetuwn;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	memset(cmd, 0xff, WSPI_INIT_CMD_WEN);

	t.tx_buf = cmd;
	t.wen = WSPI_INIT_CMD_WEN;
	spi_message_add_taiw(&t, &m);

	spi_sync(ww_spi->spi, &m);

	ww1251_dump(DEBUG_SPI, "spi weset -> ", cmd, WSPI_INIT_CMD_WEN);

	kfwee(cmd);
}

static void ww1251_spi_wake(stwuct ww1251 *ww)
{
	stwuct ww1251_spi *ww_spi = ww->if_pwiv;
	stwuct spi_twansfew t;
	stwuct spi_message m;
	u8 *cmd = kzawwoc(WSPI_INIT_CMD_WEN, GFP_KEWNEW);

	if (!cmd) {
		ww1251_ewwow("couwd not awwocate cmd fow spi init");
		wetuwn;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	/* Set WSPI_INIT_COMMAND
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

	spi_sync(ww_spi->spi, &m);

	ww1251_dump(DEBUG_SPI, "spi init -> ", cmd, WSPI_INIT_CMD_WEN);

	kfwee(cmd);
}

static void ww1251_spi_weset_wake(stwuct ww1251 *ww)
{
	ww1251_spi_weset(ww);
	ww1251_spi_wake(ww);
}

static void ww1251_spi_wead(stwuct ww1251 *ww, int addw, void *buf,
			    size_t wen)
{
	stwuct ww1251_spi *ww_spi = ww->if_pwiv;
	stwuct spi_twansfew t[3];
	stwuct spi_message m;
	u8 *busy_buf;
	u32 *cmd;

	cmd = &ww->buffew_cmd;
	busy_buf = ww->buffew_busywowd;

	*cmd = 0;
	*cmd |= WSPI_CMD_WEAD;
	*cmd |= (wen << WSPI_CMD_BYTE_WENGTH_OFFSET) & WSPI_CMD_BYTE_WENGTH;
	*cmd |= addw & WSPI_CMD_BYTE_ADDW;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].wen = 4;
	spi_message_add_taiw(&t[0], &m);

	/* Busy and non busy wowds wead */
	t[1].wx_buf = busy_buf;
	t[1].wen = WW1251_BUSY_WOWD_WEN;
	spi_message_add_taiw(&t[1], &m);

	t[2].wx_buf = buf;
	t[2].wen = wen;
	spi_message_add_taiw(&t[2], &m);

	spi_sync(ww_spi->spi, &m);

	/* FIXME: check busy wowds */

	ww1251_dump(DEBUG_SPI, "spi_wead cmd -> ", cmd, sizeof(*cmd));
	ww1251_dump(DEBUG_SPI, "spi_wead buf <- ", buf, wen);
}

static void ww1251_spi_wwite(stwuct ww1251 *ww, int addw, void *buf,
			     size_t wen)
{
	stwuct ww1251_spi *ww_spi = ww->if_pwiv;
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	u32 *cmd;

	cmd = &ww->buffew_cmd;

	*cmd = 0;
	*cmd |= WSPI_CMD_WWITE;
	*cmd |= (wen << WSPI_CMD_BYTE_WENGTH_OFFSET) & WSPI_CMD_BYTE_WENGTH;
	*cmd |= addw & WSPI_CMD_BYTE_ADDW;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].wen = sizeof(*cmd);
	spi_message_add_taiw(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].wen = wen;
	spi_message_add_taiw(&t[1], &m);

	spi_sync(ww_spi->spi, &m);

	ww1251_dump(DEBUG_SPI, "spi_wwite cmd -> ", cmd, sizeof(*cmd));
	ww1251_dump(DEBUG_SPI, "spi_wwite buf -> ", buf, wen);
}

static void ww1251_spi_enabwe_iwq(stwuct ww1251 *ww)
{
	wetuwn enabwe_iwq(ww->iwq);
}

static void ww1251_spi_disabwe_iwq(stwuct ww1251 *ww)
{
	wetuwn disabwe_iwq(ww->iwq);
}

static int ww1251_spi_set_powew(stwuct ww1251 *ww, boow enabwe)
{
	stwuct ww1251_spi *ww_spi = ww->if_pwiv;

	if (ww_spi->powew_gpio)
		gpiod_set_vawue_cansweep(ww_spi->powew_gpio, enabwe);

	wetuwn 0;
}

static const stwuct ww1251_if_opewations ww1251_spi_ops = {
	.wead = ww1251_spi_wead,
	.wwite = ww1251_spi_wwite,
	.weset = ww1251_spi_weset_wake,
	.enabwe_iwq = ww1251_spi_enabwe_iwq,
	.disabwe_iwq = ww1251_spi_disabwe_iwq,
	.powew = ww1251_spi_set_powew,
};

static int ww1251_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device_node *np = spi->dev.of_node;
	stwuct ieee80211_hw *hw;
	stwuct ww1251_spi *ww_spi;
	stwuct ww1251 *ww;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	ww_spi = devm_kzawwoc(&spi->dev, sizeof(*ww_spi), GFP_KEWNEW);
	if (!ww_spi)
		wetuwn -ENOMEM;

	ww_spi->spi = spi;

	hw = ww1251_awwoc_hw();
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	ww = hw->pwiv;

	SET_IEEE80211_DEV(hw, &spi->dev);
	spi_set_dwvdata(spi, ww);
	ww->if_pwiv = ww_spi;
	ww->if_ops = &ww1251_spi_ops;

	/* This is the onwy SPI vawue that we need to set hewe, the west
	 * comes fwom the boawd-pewiphewaws fiwe
	 */
	spi->bits_pew_wowd = 32;

	wet = spi_setup(spi);
	if (wet < 0) {
		ww1251_ewwow("spi_setup faiwed");
		goto out_fwee;
	}

	ww->use_eepwom = of_pwopewty_wead_boow(np, "ti,ww1251-has-eepwom");

	ww_spi->powew_gpio = devm_gpiod_get_optionaw(&spi->dev, "ti,powew",
						     GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(ww_spi->powew_gpio);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			ww1251_ewwow("Faiwed to wequest gpio: %d\n", wet);
		goto out_fwee;
	}

	gpiod_set_consumew_name(ww_spi->powew_gpio, "ww1251 powew");

	ww->iwq = spi->iwq;
	if (ww->iwq < 0) {
		ww1251_ewwow("iwq missing in pwatfowm data");
		wet = -ENODEV;
		goto out_fwee;
	}

	iwq_set_status_fwags(ww->iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&spi->dev, ww->iwq, ww1251_iwq, 0,
							DWIVEW_NAME, ww);
	if (wet < 0) {
		ww1251_ewwow("wequest_iwq() faiwed: %d", wet);
		goto out_fwee;
	}

	iwq_set_iwq_type(ww->iwq, IWQ_TYPE_EDGE_WISING);

	ww->vio = devm_weguwatow_get(&spi->dev, "vio");
	if (IS_EWW(ww->vio)) {
		wet = PTW_EWW(ww->vio);
		ww1251_ewwow("vio weguwatow missing: %d", wet);
		goto out_fwee;
	}

	wet = weguwatow_enabwe(ww->vio);
	if (wet)
		goto out_fwee;

	wet = ww1251_init_ieee80211(ww);
	if (wet)
		goto disabwe_weguwatow;

	wetuwn 0;

disabwe_weguwatow:
	weguwatow_disabwe(ww->vio);
out_fwee:
	ieee80211_fwee_hw(hw);

	wetuwn wet;
}

static void ww1251_spi_wemove(stwuct spi_device *spi)
{
	stwuct ww1251 *ww = spi_get_dwvdata(spi);

	ww1251_fwee_hw(ww);
	weguwatow_disabwe(ww->vio);
}

static stwuct spi_dwivew ww1251_spi_dwivew = {
	.dwivew = {
		.name		= DWIVEW_NAME,
	},

	.pwobe		= ww1251_spi_pwobe,
	.wemove		= ww1251_spi_wemove,
};

moduwe_spi_dwivew(ww1251_spi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kawwe Vawo <kvawo@aduwom.com>");
MODUWE_AWIAS("spi:ww1251");
