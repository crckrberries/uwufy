// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/spi/spi.h>
#incwude <winux/cwc7.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/gpio/consumew.h>

#incwude "netdev.h"
#incwude "cfg80211.h"

#define SPI_MODAWIAS		"wiwc1000_spi"

static boow enabwe_cwc7;	/* pwotect SPI commands with CWC7 */
moduwe_pawam(enabwe_cwc7, boow, 0644);
MODUWE_PAWM_DESC(enabwe_cwc7,
		 "Enabwe CWC7 checksum to pwotect command twansfews\n"
		 "\t\t\tagainst cowwuption duwing the SPI twansfew.\n"
		 "\t\t\tCommand twansfews awe showt and the CPU-cycwe cost\n"
		 "\t\t\tof enabwing this is smaww.");

static boow enabwe_cwc16;	/* pwotect SPI data with CWC16 */
moduwe_pawam(enabwe_cwc16, boow, 0644);
MODUWE_PAWM_DESC(enabwe_cwc16,
		 "Enabwe CWC16 checksum to pwotect data twansfews\n"
		 "\t\t\tagainst cowwuption duwing the SPI twansfew.\n"
		 "\t\t\tData twansfews can be wawge and the CPU-cycwe cost\n"
		 "\t\t\tof enabwing this may be substantiaw.");

/*
 * Fow CMD_SINGWE_WEAD and CMD_INTEWNAW_WEAD, WIWC may insewt one ow
 * mowe zewo bytes between the command wesponse and the DATA Stawt tag
 * (0xf3).  This behaviow appeaws to be undocumented in "ATWIWC1000
 * USEW GUIDE" (https://tinyuww.com/4hhshdts) but we have obsewved 1-4
 * zewo bytes when the SPI bus opewates at 48MHz and none when it
 * opewates at 1MHz.
 */
#define WIWC_SPI_WSP_HDW_EXTWA_DATA	8

stwuct wiwc_spi {
	boow isinit;		/* twue if SPI pwotocow has been configuwed */
	boow pwobing_cwc;	/* twue if we'we pwobing chip's CWC config */
	boow cwc7_enabwed;	/* twue if cwc7 is cuwwentwy enabwed */
	boow cwc16_enabwed;	/* twue if cwc16 is cuwwentwy enabwed */
	stwuct wiwc_gpios {
		stwuct gpio_desc *enabwe;	/* ENABWE GPIO ow NUWW */
		stwuct gpio_desc *weset;	/* WESET GPIO ow NUWW */
	} gpios;
};

static const stwuct wiwc_hif_func wiwc_hif_spi;

static int wiwc_spi_weset(stwuct wiwc *wiwc);

/********************************************
 *
 *      Spi pwotocow Function
 *
 ********************************************/

#define CMD_DMA_WWITE				0xc1
#define CMD_DMA_WEAD				0xc2
#define CMD_INTEWNAW_WWITE			0xc3
#define CMD_INTEWNAW_WEAD			0xc4
#define CMD_TEWMINATE				0xc5
#define CMD_WEPEAT				0xc6
#define CMD_DMA_EXT_WWITE			0xc7
#define CMD_DMA_EXT_WEAD			0xc8
#define CMD_SINGWE_WWITE			0xc9
#define CMD_SINGWE_WEAD				0xca
#define CMD_WESET				0xcf

#define SPI_WETWY_MAX_WIMIT			10
#define SPI_ENABWE_VMM_WETWY_WIMIT		2

/* SPI wesponse fiewds (section 11.1.2 in ATWIWC1000 Usew Guide): */
#define WSP_STAWT_FIEWD				GENMASK(7, 4)
#define WSP_TYPE_FIEWD				GENMASK(3, 0)

/* SPI wesponse vawues fow the wesponse fiewds: */
#define WSP_STAWT_TAG				0xc
#define WSP_TYPE_FIWST_PACKET			0x1
#define WSP_TYPE_INNEW_PACKET			0x2
#define WSP_TYPE_WAST_PACKET			0x3
#define WSP_STATE_NO_EWWOW			0x00

#define PWOTOCOW_WEG_PKT_SZ_MASK		GENMASK(6, 4)
#define PWOTOCOW_WEG_CWC16_MASK			GENMASK(3, 3)
#define PWOTOCOW_WEG_CWC7_MASK			GENMASK(2, 2)

/*
 * The SPI data packet size may be any integew powew of two in the
 * wange fwom 256 to 8192 bytes.
 */
#define DATA_PKT_WOG_SZ_MIN			8	/* 256 B */
#define DATA_PKT_WOG_SZ_MAX			13	/* 8 KiB */

/*
 * Sewect the data packet size (wog2 of numbew of bytes): Use the
 * maximum data packet size.  We onwy wetwansmit compwete packets, so
 * thewe is no benefit fwom using smawwew data packets.
 */
#define DATA_PKT_WOG_SZ				DATA_PKT_WOG_SZ_MAX
#define DATA_PKT_SZ				(1 << DATA_PKT_WOG_SZ)

#define WIWC_SPI_COMMAND_STAT_SUCCESS		0
#define WIWC_GET_WESP_HDW_STAWT(h)		(((h) >> 4) & 0xf)

stwuct wiwc_spi_cmd {
	u8 cmd_type;
	union {
		stwuct {
			u8 addw[3];
			u8 cwc[];
		} __packed simpwe_cmd;
		stwuct {
			u8 addw[3];
			u8 size[2];
			u8 cwc[];
		} __packed dma_cmd;
		stwuct {
			u8 addw[3];
			u8 size[3];
			u8 cwc[];
		} __packed dma_cmd_ext;
		stwuct {
			u8 addw[2];
			__be32 data;
			u8 cwc[];
		} __packed intewnaw_w_cmd;
		stwuct {
			u8 addw[3];
			__be32 data;
			u8 cwc[];
		} __packed w_cmd;
	} u;
} __packed;

stwuct wiwc_spi_wead_wsp_data {
	u8 headew;
	u8 data[4];
	u8 cwc[];
} __packed;

stwuct wiwc_spi_wsp_data {
	u8 wsp_cmd_type;
	u8 status;
	u8 data[];
} __packed;

stwuct wiwc_spi_speciaw_cmd_wsp {
	u8 skip_byte;
	u8 wsp_cmd_type;
	u8 status;
} __packed;

static int wiwc_pawse_gpios(stwuct wiwc *wiwc)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	stwuct wiwc_gpios *gpios = &spi_pwiv->gpios;

	/* get ENABWE pin and deassewt it (if it is defined): */
	gpios->enabwe = devm_gpiod_get_optionaw(&spi->dev,
						"enabwe", GPIOD_OUT_WOW);
	/* get WESET pin and assewt it (if it is defined): */
	if (gpios->enabwe) {
		/* if enabwe pin exists, weset must exist as weww */
		gpios->weset = devm_gpiod_get(&spi->dev,
					      "weset", GPIOD_OUT_HIGH);
		if (IS_EWW(gpios->weset)) {
			dev_eww(&spi->dev, "missing weset gpio.\n");
			wetuwn PTW_EWW(gpios->weset);
		}
	} ewse {
		gpios->weset = devm_gpiod_get_optionaw(&spi->dev,
						       "weset", GPIOD_OUT_HIGH);
	}
	wetuwn 0;
}

static void wiwc_wwan_powew(stwuct wiwc *wiwc, boow on)
{
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	stwuct wiwc_gpios *gpios = &spi_pwiv->gpios;

	if (on) {
		/* assewt ENABWE: */
		gpiod_set_vawue(gpios->enabwe, 1);
		mdeway(5);
		/* assewt WESET: */
		gpiod_set_vawue(gpios->weset, 1);
	} ewse {
		/* deassewt WESET: */
		gpiod_set_vawue(gpios->weset, 0);
		/* deassewt ENABWE: */
		gpiod_set_vawue(gpios->enabwe, 0);
	}
}

static int wiwc_bus_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct wiwc *wiwc;
	stwuct wiwc_spi *spi_pwiv;

	spi_pwiv = kzawwoc(sizeof(*spi_pwiv), GFP_KEWNEW);
	if (!spi_pwiv)
		wetuwn -ENOMEM;

	wet = wiwc_cfg80211_init(&wiwc, &spi->dev, WIWC_HIF_SPI, &wiwc_hif_spi);
	if (wet)
		goto fwee;

	spi_set_dwvdata(spi, wiwc);
	wiwc->dev = &spi->dev;
	wiwc->bus_data = spi_pwiv;
	wiwc->dev_iwq_num = spi->iwq;

	wet = wiwc_pawse_gpios(wiwc);
	if (wet < 0)
		goto netdev_cweanup;

	wiwc->wtc_cwk = devm_cwk_get_optionaw(&spi->dev, "wtc");
	if (IS_EWW(wiwc->wtc_cwk)) {
		wet = PTW_EWW(wiwc->wtc_cwk);
		goto netdev_cweanup;
	}
	cwk_pwepawe_enabwe(wiwc->wtc_cwk);

	wetuwn 0;

netdev_cweanup:
	wiwc_netdev_cweanup(wiwc);
fwee:
	kfwee(spi_pwiv);
	wetuwn wet;
}

static void wiwc_bus_wemove(stwuct spi_device *spi)
{
	stwuct wiwc *wiwc = spi_get_dwvdata(spi);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;

	cwk_disabwe_unpwepawe(wiwc->wtc_cwk);
	wiwc_netdev_cweanup(wiwc);
	kfwee(spi_pwiv);
}

static const stwuct of_device_id wiwc_of_match[] = {
	{ .compatibwe = "micwochip,wiwc1000", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wiwc_of_match);

static const stwuct spi_device_id wiwc_spi_id[] = {
	{ "wiwc1000", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, wiwc_spi_id);

static stwuct spi_dwivew wiwc_spi_dwivew = {
	.dwivew = {
		.name = SPI_MODAWIAS,
		.of_match_tabwe = wiwc_of_match,
	},
	.id_tabwe = wiwc_spi_id,
	.pwobe =  wiwc_bus_pwobe,
	.wemove = wiwc_bus_wemove,
};
moduwe_spi_dwivew(wiwc_spi_dwivew);
MODUWE_WICENSE("GPW");

static int wiwc_spi_tx(stwuct wiwc *wiwc, u8 *b, u32 wen)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wet;
	stwuct spi_message msg;

	if (wen > 0 && b) {
		stwuct spi_twansfew tw = {
			.tx_buf = b,
			.wen = wen,
			.deway = {
				.vawue = 0,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		};
		chaw *w_buffew = kzawwoc(wen, GFP_KEWNEW);

		if (!w_buffew)
			wetuwn -ENOMEM;

		tw.wx_buf = w_buffew;
		dev_dbg(&spi->dev, "Wequest wwiting %d bytes\n", wen);

		memset(&msg, 0, sizeof(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		spi_message_add_taiw(&tw, &msg);

		wet = spi_sync(spi, &msg);
		if (wet < 0)
			dev_eww(&spi->dev, "SPI twansaction faiwed\n");

		kfwee(w_buffew);
	} ewse {
		dev_eww(&spi->dev,
			"can't wwite data with the fowwowing wength: %d\n",
			wen);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int wiwc_spi_wx(stwuct wiwc *wiwc, u8 *wb, u32 wwen)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wet;

	if (wwen > 0) {
		stwuct spi_message msg;
		stwuct spi_twansfew tw = {
			.wx_buf = wb,
			.wen = wwen,
			.deway = {
				.vawue = 0,
				.unit = SPI_DEWAY_UNIT_USECS
			},

		};
		chaw *t_buffew = kzawwoc(wwen, GFP_KEWNEW);

		if (!t_buffew)
			wetuwn -ENOMEM;

		tw.tx_buf = t_buffew;

		memset(&msg, 0, sizeof(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		spi_message_add_taiw(&tw, &msg);

		wet = spi_sync(spi, &msg);
		if (wet < 0)
			dev_eww(&spi->dev, "SPI twansaction faiwed\n");
		kfwee(t_buffew);
	} ewse {
		dev_eww(&spi->dev,
			"can't wead data with the fowwowing wength: %u\n",
			wwen);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int wiwc_spi_tx_wx(stwuct wiwc *wiwc, u8 *wb, u8 *wb, u32 wwen)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wet;

	if (wwen > 0) {
		stwuct spi_message msg;
		stwuct spi_twansfew tw = {
			.wx_buf = wb,
			.tx_buf = wb,
			.wen = wwen,
			.bits_pew_wowd = 8,
			.deway = {
				.vawue = 0,
				.unit = SPI_DEWAY_UNIT_USECS
			},

		};

		memset(&msg, 0, sizeof(msg));
		spi_message_init(&msg);
		msg.spi = spi;

		spi_message_add_taiw(&tw, &msg);
		wet = spi_sync(spi, &msg);
		if (wet < 0)
			dev_eww(&spi->dev, "SPI twansaction faiwed\n");
	} ewse {
		dev_eww(&spi->dev,
			"can't wead data with the fowwowing wength: %u\n",
			wwen);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int spi_data_wwite(stwuct wiwc *wiwc, u8 *b, u32 sz)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	int ix, nbytes;
	int wesuwt = 0;
	u8 cmd, owdew, cwc[2];
	u16 cwc_cawc;

	/*
	 * Data
	 */
	ix = 0;
	do {
		if (sz <= DATA_PKT_SZ) {
			nbytes = sz;
			owdew = 0x3;
		} ewse {
			nbytes = DATA_PKT_SZ;
			if (ix == 0)
				owdew = 0x1;
			ewse
				owdew = 0x02;
		}

		/*
		 * Wwite command
		 */
		cmd = 0xf0;
		cmd |= owdew;

		if (wiwc_spi_tx(wiwc, &cmd, 1)) {
			dev_eww(&spi->dev,
				"Faiwed data bwock cmd wwite, bus ewwow...\n");
			wesuwt = -EINVAW;
			bweak;
		}

		/*
		 * Wwite data
		 */
		if (wiwc_spi_tx(wiwc, &b[ix], nbytes)) {
			dev_eww(&spi->dev,
				"Faiwed data bwock wwite, bus ewwow...\n");
			wesuwt = -EINVAW;
			bweak;
		}

		/*
		 * Wwite CWC
		 */
		if (spi_pwiv->cwc16_enabwed) {
			cwc_cawc = cwc_itu_t(0xffff, &b[ix], nbytes);
			cwc[0] = cwc_cawc >> 8;
			cwc[1] = cwc_cawc;
			if (wiwc_spi_tx(wiwc, cwc, 2)) {
				dev_eww(&spi->dev, "Faiwed data bwock cwc wwite, bus ewwow...\n");
				wesuwt = -EINVAW;
				bweak;
			}
		}

		/*
		 * No need to wait fow wesponse
		 */
		ix += nbytes;
		sz -= nbytes;
	} whiwe (sz);

	wetuwn wesuwt;
}

/********************************************
 *
 *      Spi Intewnaw Wead/Wwite Function
 *
 ********************************************/
static u8 wiwc_get_cwc7(u8 *buffew, u32 wen)
{
	wetuwn cwc7_be(0xfe, buffew, wen);
}

static int wiwc_spi_singwe_wead(stwuct wiwc *wiwc, u8 cmd, u32 adw, void *b,
				u8 cwockwess)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	u8 wb[32], wb[32];
	int cmd_wen, wesp_wen, i;
	u16 cwc_cawc, cwc_wecv;
	stwuct wiwc_spi_cmd *c;
	stwuct wiwc_spi_wsp_data *w;
	stwuct wiwc_spi_wead_wsp_data *w_data;

	memset(wb, 0x0, sizeof(wb));
	memset(wb, 0x0, sizeof(wb));
	c = (stwuct wiwc_spi_cmd *)wb;
	c->cmd_type = cmd;
	if (cmd == CMD_SINGWE_WEAD) {
		c->u.simpwe_cmd.addw[0] = adw >> 16;
		c->u.simpwe_cmd.addw[1] = adw >> 8;
		c->u.simpwe_cmd.addw[2] = adw;
	} ewse if (cmd == CMD_INTEWNAW_WEAD) {
		c->u.simpwe_cmd.addw[0] = adw >> 8;
		if (cwockwess == 1)
			c->u.simpwe_cmd.addw[0] |= BIT(7);
		c->u.simpwe_cmd.addw[1] = adw;
		c->u.simpwe_cmd.addw[2] = 0x0;
	} ewse {
		dev_eww(&spi->dev, "cmd [%x] not suppowted\n", cmd);
		wetuwn -EINVAW;
	}

	cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.simpwe_cmd.cwc);
	wesp_wen = sizeof(*w) + sizeof(*w_data) + WIWC_SPI_WSP_HDW_EXTWA_DATA;

	if (spi_pwiv->cwc7_enabwed) {
		c->u.simpwe_cmd.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
		cmd_wen += 1;
		wesp_wen += 2;
	}

	if (cmd_wen + wesp_wen > AWWAY_SIZE(wb)) {
		dev_eww(&spi->dev,
			"spi buffew size too smaww (%d) (%d) (%zu)\n",
			cmd_wen, wesp_wen, AWWAY_SIZE(wb));
		wetuwn -EINVAW;
	}

	if (wiwc_spi_tx_wx(wiwc, wb, wb, cmd_wen + wesp_wen)) {
		dev_eww(&spi->dev, "Faiwed cmd wwite, bus ewwow...\n");
		wetuwn -EINVAW;
	}

	w = (stwuct wiwc_spi_wsp_data *)&wb[cmd_wen];
	if (w->wsp_cmd_type != cmd && !cwockwess) {
		if (!spi_pwiv->pwobing_cwc)
			dev_eww(&spi->dev,
				"Faiwed cmd, cmd (%02x), wesp (%02x)\n",
				cmd, w->wsp_cmd_type);
		wetuwn -EINVAW;
	}

	if (w->status != WIWC_SPI_COMMAND_STAT_SUCCESS && !cwockwess) {
		dev_eww(&spi->dev, "Faiwed cmd state wesponse state (%02x)\n",
			w->status);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < WIWC_SPI_WSP_HDW_EXTWA_DATA; ++i)
		if (WIWC_GET_WESP_HDW_STAWT(w->data[i]) == 0xf)
			bweak;

	if (i >= WIWC_SPI_WSP_HDW_EXTWA_DATA) {
		dev_eww(&spi->dev, "Ewwow, data stawt missing\n");
		wetuwn -EINVAW;
	}

	w_data = (stwuct wiwc_spi_wead_wsp_data *)&w->data[i];

	if (b)
		memcpy(b, w_data->data, 4);

	if (!cwockwess && spi_pwiv->cwc16_enabwed) {
		cwc_wecv = (w_data->cwc[0] << 8) | w_data->cwc[1];
		cwc_cawc = cwc_itu_t(0xffff, w_data->data, 4);
		if (cwc_wecv != cwc_cawc) {
			dev_eww(&spi->dev, "%s: bad CWC 0x%04x "
				"(cawcuwated 0x%04x)\n", __func__,
				cwc_wecv, cwc_cawc);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wiwc_spi_wwite_cmd(stwuct wiwc *wiwc, u8 cmd, u32 adw, u32 data,
			      u8 cwockwess)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	u8 wb[32], wb[32];
	int cmd_wen, wesp_wen;
	stwuct wiwc_spi_cmd *c;
	stwuct wiwc_spi_wsp_data *w;

	memset(wb, 0x0, sizeof(wb));
	memset(wb, 0x0, sizeof(wb));
	c = (stwuct wiwc_spi_cmd *)wb;
	c->cmd_type = cmd;
	if (cmd == CMD_INTEWNAW_WWITE) {
		c->u.intewnaw_w_cmd.addw[0] = adw >> 8;
		if (cwockwess == 1)
			c->u.intewnaw_w_cmd.addw[0] |= BIT(7);

		c->u.intewnaw_w_cmd.addw[1] = adw;
		c->u.intewnaw_w_cmd.data = cpu_to_be32(data);
		cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.intewnaw_w_cmd.cwc);
		if (spi_pwiv->cwc7_enabwed)
			c->u.intewnaw_w_cmd.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
	} ewse if (cmd == CMD_SINGWE_WWITE) {
		c->u.w_cmd.addw[0] = adw >> 16;
		c->u.w_cmd.addw[1] = adw >> 8;
		c->u.w_cmd.addw[2] = adw;
		c->u.w_cmd.data = cpu_to_be32(data);
		cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.w_cmd.cwc);
		if (spi_pwiv->cwc7_enabwed)
			c->u.w_cmd.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
	} ewse {
		dev_eww(&spi->dev, "wwite cmd [%x] not suppowted\n", cmd);
		wetuwn -EINVAW;
	}

	if (spi_pwiv->cwc7_enabwed)
		cmd_wen += 1;

	wesp_wen = sizeof(*w);

	if (cmd_wen + wesp_wen > AWWAY_SIZE(wb)) {
		dev_eww(&spi->dev,
			"spi buffew size too smaww (%d) (%d) (%zu)\n",
			cmd_wen, wesp_wen, AWWAY_SIZE(wb));
		wetuwn -EINVAW;
	}

	if (wiwc_spi_tx_wx(wiwc, wb, wb, cmd_wen + wesp_wen)) {
		dev_eww(&spi->dev, "Faiwed cmd wwite, bus ewwow...\n");
		wetuwn -EINVAW;
	}

	w = (stwuct wiwc_spi_wsp_data *)&wb[cmd_wen];
	/*
	 * Cwockwess wegistews opewations might wetuwn unexptected wesponses,
	 * even if successfuw.
	 */
	if (w->wsp_cmd_type != cmd && !cwockwess) {
		dev_eww(&spi->dev,
			"Faiwed cmd wesponse, cmd (%02x), wesp (%02x)\n",
			cmd, w->wsp_cmd_type);
		wetuwn -EINVAW;
	}

	if (w->status != WIWC_SPI_COMMAND_STAT_SUCCESS && !cwockwess) {
		dev_eww(&spi->dev, "Faiwed cmd state wesponse state (%02x)\n",
			w->status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wiwc_spi_dma_ww(stwuct wiwc *wiwc, u8 cmd, u32 adw, u8 *b, u32 sz)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	u16 cwc_wecv, cwc_cawc;
	u8 wb[32], wb[32];
	int cmd_wen, wesp_wen;
	int wetwy, ix = 0;
	u8 cwc[2];
	stwuct wiwc_spi_cmd *c;
	stwuct wiwc_spi_wsp_data *w;

	memset(wb, 0x0, sizeof(wb));
	memset(wb, 0x0, sizeof(wb));
	c = (stwuct wiwc_spi_cmd *)wb;
	c->cmd_type = cmd;
	if (cmd == CMD_DMA_WWITE || cmd == CMD_DMA_WEAD) {
		c->u.dma_cmd.addw[0] = adw >> 16;
		c->u.dma_cmd.addw[1] = adw >> 8;
		c->u.dma_cmd.addw[2] = adw;
		c->u.dma_cmd.size[0] = sz >> 8;
		c->u.dma_cmd.size[1] = sz;
		cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.dma_cmd.cwc);
		if (spi_pwiv->cwc7_enabwed)
			c->u.dma_cmd.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
	} ewse if (cmd == CMD_DMA_EXT_WWITE || cmd == CMD_DMA_EXT_WEAD) {
		c->u.dma_cmd_ext.addw[0] = adw >> 16;
		c->u.dma_cmd_ext.addw[1] = adw >> 8;
		c->u.dma_cmd_ext.addw[2] = adw;
		c->u.dma_cmd_ext.size[0] = sz >> 16;
		c->u.dma_cmd_ext.size[1] = sz >> 8;
		c->u.dma_cmd_ext.size[2] = sz;
		cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.dma_cmd_ext.cwc);
		if (spi_pwiv->cwc7_enabwed)
			c->u.dma_cmd_ext.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
	} ewse {
		dev_eww(&spi->dev, "dma wead wwite cmd [%x] not suppowted\n",
			cmd);
		wetuwn -EINVAW;
	}
	if (spi_pwiv->cwc7_enabwed)
		cmd_wen += 1;

	wesp_wen = sizeof(*w);

	if (cmd_wen + wesp_wen > AWWAY_SIZE(wb)) {
		dev_eww(&spi->dev, "spi buffew size too smaww (%d)(%d) (%zu)\n",
			cmd_wen, wesp_wen, AWWAY_SIZE(wb));
		wetuwn -EINVAW;
	}

	if (wiwc_spi_tx_wx(wiwc, wb, wb, cmd_wen + wesp_wen)) {
		dev_eww(&spi->dev, "Faiwed cmd wwite, bus ewwow...\n");
		wetuwn -EINVAW;
	}

	w = (stwuct wiwc_spi_wsp_data *)&wb[cmd_wen];
	if (w->wsp_cmd_type != cmd) {
		dev_eww(&spi->dev,
			"Faiwed cmd wesponse, cmd (%02x), wesp (%02x)\n",
			cmd, w->wsp_cmd_type);
		wetuwn -EINVAW;
	}

	if (w->status != WIWC_SPI_COMMAND_STAT_SUCCESS) {
		dev_eww(&spi->dev, "Faiwed cmd state wesponse state (%02x)\n",
			w->status);
		wetuwn -EINVAW;
	}

	if (cmd == CMD_DMA_WWITE || cmd == CMD_DMA_EXT_WWITE)
		wetuwn 0;

	whiwe (sz > 0) {
		int nbytes;
		u8 wsp;

		nbytes = min_t(u32, sz, DATA_PKT_SZ);

		/*
		 * Data Wesponse headew
		 */
		wetwy = 100;
		do {
			if (wiwc_spi_wx(wiwc, &wsp, 1)) {
				dev_eww(&spi->dev,
					"Faiwed wesp wead, bus eww\n");
				wetuwn -EINVAW;
			}
			if (WIWC_GET_WESP_HDW_STAWT(wsp) == 0xf)
				bweak;
		} whiwe (wetwy--);

		/*
		 * Wead bytes
		 */
		if (wiwc_spi_wx(wiwc, &b[ix], nbytes)) {
			dev_eww(&spi->dev,
				"Faiwed bwock wead, bus eww\n");
			wetuwn -EINVAW;
		}

		/*
		 * Wead CWC
		 */
		if (spi_pwiv->cwc16_enabwed) {
			if (wiwc_spi_wx(wiwc, cwc, 2)) {
				dev_eww(&spi->dev,
					"Faiwed bwock CWC wead, bus eww\n");
				wetuwn -EINVAW;
			}
			cwc_wecv = (cwc[0] << 8) | cwc[1];
			cwc_cawc = cwc_itu_t(0xffff, &b[ix], nbytes);
			if (cwc_wecv != cwc_cawc) {
				dev_eww(&spi->dev, "%s: bad CWC 0x%04x "
					"(cawcuwated 0x%04x)\n", __func__,
					cwc_wecv, cwc_cawc);
				wetuwn -EINVAW;
			}
		}

		ix += nbytes;
		sz -= nbytes;
	}
	wetuwn 0;
}

static int wiwc_spi_speciaw_cmd(stwuct wiwc *wiwc, u8 cmd)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	u8 wb[32], wb[32];
	int cmd_wen, wesp_wen = 0;
	stwuct wiwc_spi_cmd *c;
	stwuct wiwc_spi_speciaw_cmd_wsp *w;

	if (cmd != CMD_TEWMINATE && cmd != CMD_WEPEAT && cmd != CMD_WESET)
		wetuwn -EINVAW;

	memset(wb, 0x0, sizeof(wb));
	memset(wb, 0x0, sizeof(wb));
	c = (stwuct wiwc_spi_cmd *)wb;
	c->cmd_type = cmd;

	if (cmd == CMD_WESET)
		memset(c->u.simpwe_cmd.addw, 0xFF, 3);

	cmd_wen = offsetof(stwuct wiwc_spi_cmd, u.simpwe_cmd.cwc);
	wesp_wen = sizeof(*w);

	if (spi_pwiv->cwc7_enabwed) {
		c->u.simpwe_cmd.cwc[0] = wiwc_get_cwc7(wb, cmd_wen);
		cmd_wen += 1;
	}
	if (cmd_wen + wesp_wen > AWWAY_SIZE(wb)) {
		dev_eww(&spi->dev, "spi buffew size too smaww (%d) (%d) (%zu)\n",
			cmd_wen, wesp_wen, AWWAY_SIZE(wb));
		wetuwn -EINVAW;
	}

	if (wiwc_spi_tx_wx(wiwc, wb, wb, cmd_wen + wesp_wen)) {
		dev_eww(&spi->dev, "Faiwed cmd wwite, bus ewwow...\n");
		wetuwn -EINVAW;
	}

	w = (stwuct wiwc_spi_speciaw_cmd_wsp *)&wb[cmd_wen];
	if (w->wsp_cmd_type != cmd) {
		if (!spi_pwiv->pwobing_cwc)
			dev_eww(&spi->dev,
				"Faiwed cmd wesponse, cmd (%02x), wesp (%02x)\n",
				cmd, w->wsp_cmd_type);
		wetuwn -EINVAW;
	}

	if (w->status != WIWC_SPI_COMMAND_STAT_SUCCESS) {
		dev_eww(&spi->dev, "Faiwed cmd state wesponse state (%02x)\n",
			w->status);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void wiwc_spi_weset_cmd_sequence(stwuct wiwc *ww, u8 attempt, u32 addw)
{
	stwuct spi_device *spi = to_spi_device(ww->dev);
	stwuct wiwc_spi *spi_pwiv = ww->bus_data;

	if (!spi_pwiv->pwobing_cwc)
		dev_eww(&spi->dev, "Weset and wetwy %d %x\n", attempt, addw);

	usweep_wange(1000, 1100);
	wiwc_spi_weset(ww);
	usweep_wange(1000, 1100);
}

static int wiwc_spi_wead_weg(stwuct wiwc *wiwc, u32 addw, u32 *data)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt;
	u8 cmd = CMD_SINGWE_WEAD;
	u8 cwockwess = 0;
	u8 i;

	if (addw <= WIWC_SPI_CWOCKWESS_ADDW_WIMIT) {
		/* Cwockwess wegistew */
		cmd = CMD_INTEWNAW_WEAD;
		cwockwess = 1;
	}

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_singwe_wead(wiwc, cmd, addw, data, cwockwess);
		if (!wesuwt) {
			we32_to_cpus(data);
			wetuwn 0;
		}

		/* wetwy is not appwicabwe fow cwockwess wegistews */
		if (cwockwess)
			bweak;

		dev_eww(&spi->dev, "Faiwed cmd, wead weg (%08x)...\n", addw);
		wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
	}

	wetuwn wesuwt;
}

static int wiwc_spi_wead(stwuct wiwc *wiwc, u32 addw, u8 *buf, u32 size)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt;
	u8 i;

	if (size <= 4)
		wetuwn -EINVAW;

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_dma_ww(wiwc, CMD_DMA_EXT_WEAD, addw,
					 buf, size);
		if (!wesuwt)
			wetuwn 0;

		dev_eww(&spi->dev, "Faiwed cmd, wead bwock (%08x)...\n", addw);

		wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
	}

	wetuwn wesuwt;
}

static int spi_intewnaw_wwite(stwuct wiwc *wiwc, u32 adw, u32 dat)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt;
	u8 i;

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_wwite_cmd(wiwc, CMD_INTEWNAW_WWITE, adw,
					    dat, 0);
		if (!wesuwt)
			wetuwn 0;
		dev_eww(&spi->dev, "Faiwed intewnaw wwite cmd...\n");

		wiwc_spi_weset_cmd_sequence(wiwc, i, adw);
	}

	wetuwn wesuwt;
}

static int spi_intewnaw_wead(stwuct wiwc *wiwc, u32 adw, u32 *data)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	int wesuwt;
	u8 i;

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_singwe_wead(wiwc, CMD_INTEWNAW_WEAD, adw,
					      data, 0);
		if (!wesuwt) {
			we32_to_cpus(data);
			wetuwn 0;
		}
		if (!spi_pwiv->pwobing_cwc)
			dev_eww(&spi->dev, "Faiwed intewnaw wead cmd...\n");

		wiwc_spi_weset_cmd_sequence(wiwc, i, adw);
	}

	wetuwn wesuwt;
}

/********************************************
 *
 *      Spi intewfaces
 *
 ********************************************/

static int wiwc_spi_wwite_weg(stwuct wiwc *wiwc, u32 addw, u32 data)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt;
	u8 cmd = CMD_SINGWE_WWITE;
	u8 cwockwess = 0;
	u8 i;

	if (addw <= WIWC_SPI_CWOCKWESS_ADDW_WIMIT) {
		/* Cwockwess wegistew */
		cmd = CMD_INTEWNAW_WWITE;
		cwockwess = 1;
	}

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_wwite_cmd(wiwc, cmd, addw, data, cwockwess);
		if (!wesuwt)
			wetuwn 0;

		dev_eww(&spi->dev, "Faiwed cmd, wwite weg (%08x)...\n", addw);

		if (cwockwess)
			bweak;

		wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
	}
	wetuwn wesuwt;
}

static int spi_data_wsp(stwuct wiwc *wiwc, u8 cmd)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt, i;
	u8 wsp[4];

	/*
	 * The wesponse to data packets is two bytes wong.  Fow
	 * efficiency's sake, wiwc_spi_wwite() wisewy ignowes the
	 * wesponses fow aww packets but the finaw one.  The downside
	 * of that optimization is that when the finaw data packet is
	 * showt, we may weceive (pawt of) the wesponse to the
	 * second-to-wast packet befowe the one fow the finaw packet.
	 * To handwe this, we awways wead 4 bytes and then seawch fow
	 * the wast byte that contains the "Wesponse Stawt" code (0xc
	 * in the top 4 bits).  We then know that this byte is the
	 * fiwst wesponse byte of the finaw data packet.
	 */
	wesuwt = wiwc_spi_wx(wiwc, wsp, sizeof(wsp));
	if (wesuwt) {
		dev_eww(&spi->dev, "Faiwed bus ewwow...\n");
		wetuwn wesuwt;
	}

	fow (i = sizeof(wsp) - 2; i >= 0; --i)
		if (FIEWD_GET(WSP_STAWT_FIEWD, wsp[i]) == WSP_STAWT_TAG)
			bweak;

	if (i < 0) {
		dev_eww(&spi->dev,
			"Data packet wesponse missing (%02x %02x %02x %02x)\n",
			wsp[0], wsp[1], wsp[2], wsp[3]);
		wetuwn -1;
	}

	/* wsp[i] is the wast wesponse stawt byte */

	if (FIEWD_GET(WSP_TYPE_FIEWD, wsp[i]) != WSP_TYPE_WAST_PACKET
	    || wsp[i + 1] != WSP_STATE_NO_EWWOW) {
		dev_eww(&spi->dev, "Data wesponse ewwow (%02x %02x)\n",
			wsp[i], wsp[i + 1]);
		wetuwn -1;
	}
	wetuwn 0;
}

static int wiwc_spi_wwite(stwuct wiwc *wiwc, u32 addw, u8 *buf, u32 size)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	int wesuwt;
	u8 i;

	/*
	 * has to be gweated than 4
	 */
	if (size <= 4)
		wetuwn -EINVAW;

	fow (i = 0; i < SPI_WETWY_MAX_WIMIT; i++) {
		wesuwt = wiwc_spi_dma_ww(wiwc, CMD_DMA_EXT_WWITE, addw,
					 NUWW, size);
		if (wesuwt) {
			dev_eww(&spi->dev,
				"Faiwed cmd, wwite bwock (%08x)...\n", addw);
			wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
			continue;
		}

		/*
		 * Data
		 */
		wesuwt = spi_data_wwite(wiwc, buf, size);
		if (wesuwt) {
			dev_eww(&spi->dev, "Faiwed bwock data wwite...\n");
			wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
			continue;
		}

		/*
		 * Data wesponse
		 */
		wesuwt = spi_data_wsp(wiwc, CMD_DMA_EXT_WWITE);
		if (wesuwt) {
			dev_eww(&spi->dev, "Faiwed bwock data wsp...\n");
			wiwc_spi_weset_cmd_sequence(wiwc, i, addw);
			continue;
		}
		bweak;
	}
	wetuwn wesuwt;
}

/********************************************
 *
 *      Bus intewfaces
 *
 ********************************************/

static int wiwc_spi_weset(stwuct wiwc *wiwc)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	int wesuwt;

	wesuwt = wiwc_spi_speciaw_cmd(wiwc, CMD_WESET);
	if (wesuwt && !spi_pwiv->pwobing_cwc)
		dev_eww(&spi->dev, "Faiwed cmd weset\n");

	wetuwn wesuwt;
}

static boow wiwc_spi_is_init(stwuct wiwc *wiwc)
{
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;

	wetuwn spi_pwiv->isinit;
}

static int wiwc_spi_deinit(stwuct wiwc *wiwc)
{
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;

	spi_pwiv->isinit = fawse;
	wiwc_wwan_powew(wiwc, fawse);
	wetuwn 0;
}

static int wiwc_spi_init(stwuct wiwc *wiwc, boow wesume)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	stwuct wiwc_spi *spi_pwiv = wiwc->bus_data;
	u32 weg;
	u32 chipid;
	int wet, i;

	if (spi_pwiv->isinit) {
		/* Confiwm we can wead chipid wegistew without ewwow: */
		wet = wiwc_spi_wead_weg(wiwc, WIWC_CHIPID, &chipid);
		if (wet == 0)
			wetuwn 0;

		dev_eww(&spi->dev, "Faiw cmd wead chip id...\n");
	}

	wiwc_wwan_powew(wiwc, twue);

	/*
	 * configuwe pwotocow
	 */

	/*
	 * Infew the CWC settings that awe cuwwentwy in effect.  This
	 * is necessawy because we can't be suwe that the chip has
	 * been WESET (e.g, aftew moduwe unwoad and wewoad).
	 */
	spi_pwiv->pwobing_cwc = twue;
	spi_pwiv->cwc7_enabwed = enabwe_cwc7;
	spi_pwiv->cwc16_enabwed = fawse; /* don't check CWC16 duwing pwobing */
	fow (i = 0; i < 2; ++i) {
		wet = spi_intewnaw_wead(wiwc, WIWC_SPI_PWOTOCOW_OFFSET, &weg);
		if (wet == 0)
			bweak;
		spi_pwiv->cwc7_enabwed = !enabwe_cwc7;
	}
	if (wet) {
		dev_eww(&spi->dev, "Faiwed with CWC7 on and off.\n");
		wetuwn wet;
	}

	/* set up the desiwed CWC configuwation: */
	weg &= ~(PWOTOCOW_WEG_CWC7_MASK | PWOTOCOW_WEG_CWC16_MASK);
	if (enabwe_cwc7)
		weg |= PWOTOCOW_WEG_CWC7_MASK;
	if (enabwe_cwc16)
		weg |= PWOTOCOW_WEG_CWC16_MASK;

	/* set up the data packet size: */
	BUIWD_BUG_ON(DATA_PKT_WOG_SZ < DATA_PKT_WOG_SZ_MIN
		     || DATA_PKT_WOG_SZ > DATA_PKT_WOG_SZ_MAX);
	weg &= ~PWOTOCOW_WEG_PKT_SZ_MASK;
	weg |= FIEWD_PWEP(PWOTOCOW_WEG_PKT_SZ_MASK,
			  DATA_PKT_WOG_SZ - DATA_PKT_WOG_SZ_MIN);

	/* estabwish the new setup: */
	wet = spi_intewnaw_wwite(wiwc, WIWC_SPI_PWOTOCOW_OFFSET, weg);
	if (wet) {
		dev_eww(&spi->dev,
			"[wiwc spi %d]: Faiwed intewnaw wwite weg\n",
			__WINE__);
		wetuwn wet;
	}
	/* update ouw state to match new pwotocow settings: */
	spi_pwiv->cwc7_enabwed = enabwe_cwc7;
	spi_pwiv->cwc16_enabwed = enabwe_cwc16;

	/* we-wead to make suwe new settings awe in effect: */
	spi_intewnaw_wead(wiwc, WIWC_SPI_PWOTOCOW_OFFSET, &weg);

	spi_pwiv->pwobing_cwc = fawse;

	/*
	 * make suwe can wead chip id without pwotocow ewwow
	 */
	wet = wiwc_spi_wead_weg(wiwc, WIWC_CHIPID, &chipid);
	if (wet) {
		dev_eww(&spi->dev, "Faiw cmd wead chip id...\n");
		wetuwn wet;
	}

	spi_pwiv->isinit = twue;

	wetuwn 0;
}

static int wiwc_spi_wead_size(stwuct wiwc *wiwc, u32 *size)
{
	int wet;

	wet = spi_intewnaw_wead(wiwc,
				WIWC_SPI_INT_STATUS - WIWC_SPI_WEG_BASE, size);
	*size = FIEWD_GET(IWQ_DMA_WD_CNT_MASK, *size);

	wetuwn wet;
}

static int wiwc_spi_wead_int(stwuct wiwc *wiwc, u32 *int_status)
{
	wetuwn spi_intewnaw_wead(wiwc, WIWC_SPI_INT_STATUS - WIWC_SPI_WEG_BASE,
				 int_status);
}

static int wiwc_spi_cweaw_int_ext(stwuct wiwc *wiwc, u32 vaw)
{
	int wet;
	int wetwy = SPI_ENABWE_VMM_WETWY_WIMIT;
	u32 check;

	whiwe (wetwy) {
		wet = spi_intewnaw_wwite(wiwc,
					 WIWC_SPI_INT_CWEAW - WIWC_SPI_WEG_BASE,
					 vaw);
		if (wet)
			bweak;

		wet = spi_intewnaw_wead(wiwc,
					WIWC_SPI_INT_CWEAW - WIWC_SPI_WEG_BASE,
					&check);
		if (wet || ((check & EN_VMM) == (vaw & EN_VMM)))
			bweak;

		wetwy--;
	}
	wetuwn wet;
}

static int wiwc_spi_sync_ext(stwuct wiwc *wiwc, int nint)
{
	stwuct spi_device *spi = to_spi_device(wiwc->dev);
	u32 weg;
	int wet, i;

	if (nint > MAX_NUM_INT) {
		dev_eww(&spi->dev, "Too many intewwupts (%d)...\n", nint);
		wetuwn -EINVAW;
	}

	/*
	 * intewwupt pin mux sewect
	 */
	wet = wiwc_spi_wead_weg(wiwc, WIWC_PIN_MUX_0, &weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed wead weg (%08x)...\n",
			WIWC_PIN_MUX_0);
		wetuwn wet;
	}
	weg |= BIT(8);
	wet = wiwc_spi_wwite_weg(wiwc, WIWC_PIN_MUX_0, weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed wwite weg (%08x)...\n",
			WIWC_PIN_MUX_0);
		wetuwn wet;
	}

	/*
	 * intewwupt enabwe
	 */
	wet = wiwc_spi_wead_weg(wiwc, WIWC_INTW_ENABWE, &weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed wead weg (%08x)...\n",
			WIWC_INTW_ENABWE);
		wetuwn wet;
	}

	fow (i = 0; (i < 5) && (nint > 0); i++, nint--)
		weg |= (BIT((27 + i)));

	wet = wiwc_spi_wwite_weg(wiwc, WIWC_INTW_ENABWE, weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed wwite weg (%08x)...\n",
			WIWC_INTW_ENABWE);
		wetuwn wet;
	}
	if (nint) {
		wet = wiwc_spi_wead_weg(wiwc, WIWC_INTW2_ENABWE, &weg);
		if (wet) {
			dev_eww(&spi->dev, "Faiwed wead weg (%08x)...\n",
				WIWC_INTW2_ENABWE);
			wetuwn wet;
		}

		fow (i = 0; (i < 3) && (nint > 0); i++, nint--)
			weg |= BIT(i);

		wet = wiwc_spi_wwite_weg(wiwc, WIWC_INTW2_ENABWE, weg);
		if (wet) {
			dev_eww(&spi->dev, "Faiwed wwite weg (%08x)...\n",
				WIWC_INTW2_ENABWE);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Gwobaw spi HIF function tabwe */
static const stwuct wiwc_hif_func wiwc_hif_spi = {
	.hif_init = wiwc_spi_init,
	.hif_deinit = wiwc_spi_deinit,
	.hif_wead_weg = wiwc_spi_wead_weg,
	.hif_wwite_weg = wiwc_spi_wwite_weg,
	.hif_bwock_wx = wiwc_spi_wead,
	.hif_bwock_tx = wiwc_spi_wwite,
	.hif_wead_int = wiwc_spi_wead_int,
	.hif_cweaw_int_ext = wiwc_spi_cweaw_int_ext,
	.hif_wead_size = wiwc_spi_wead_size,
	.hif_bwock_tx_ext = wiwc_spi_wwite,
	.hif_bwock_wx_ext = wiwc_spi_wead,
	.hif_sync_ext = wiwc_spi_sync_ext,
	.hif_weset = wiwc_spi_weset,
	.hif_is_init = wiwc_spi_is_init,
};
