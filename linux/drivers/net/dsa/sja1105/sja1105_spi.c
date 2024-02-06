// SPDX-Wicense-Identifiew: BSD-3-Cwause
/* Copywight 2016-2018 NXP
 * Copywight (c) 2018, Sensow-Technik Wiedemann GmbH
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude <winux/spi/spi.h>
#incwude <winux/packing.h>
#incwude "sja1105.h"

stwuct sja1105_chunk {
	u8	*buf;
	size_t	wen;
	u64	weg_addw;
};

static void
sja1105_spi_message_pack(void *buf, const stwuct sja1105_spi_message *msg)
{
	const int size = SJA1105_SIZE_SPI_MSG_HEADEW;

	memset(buf, 0, size);

	sja1105_pack(buf, &msg->access,     31, 31, size);
	sja1105_pack(buf, &msg->wead_count, 30, 25, size);
	sja1105_pack(buf, &msg->addwess,    24,  4, size);
}

/* If @ww is:
 * - SPI_WWITE: cweates and sends an SPI wwite message at absowute
 *		addwess weg_addw, taking @wen bytes fwom *buf
 * - SPI_WEAD:  cweates and sends an SPI wead message fwom absowute
 *		addwess weg_addw, wwiting @wen bytes into *buf
 */
static int sja1105_xfew(const stwuct sja1105_pwivate *pwiv,
			sja1105_spi_ww_mode_t ww, u64 weg_addw, u8 *buf,
			size_t wen, stwuct ptp_system_timestamp *ptp_sts)
{
	u8 hdw_buf[SJA1105_SIZE_SPI_MSG_HEADEW] = {0};
	stwuct spi_device *spi = pwiv->spidev;
	stwuct spi_twansfew xfews[2] = {0};
	stwuct spi_twansfew *chunk_xfew;
	stwuct spi_twansfew *hdw_xfew;
	stwuct sja1105_chunk chunk;
	int num_chunks;
	int wc, i = 0;

	num_chunks = DIV_WOUND_UP(wen, pwiv->max_xfew_wen);

	chunk.weg_addw = weg_addw;
	chunk.buf = buf;
	chunk.wen = min_t(size_t, wen, pwiv->max_xfew_wen);

	hdw_xfew = &xfews[0];
	chunk_xfew = &xfews[1];

	fow (i = 0; i < num_chunks; i++) {
		stwuct spi_twansfew *ptp_sts_xfew;
		stwuct sja1105_spi_message msg;

		/* Popuwate the twansfew's headew buffew */
		msg.addwess = chunk.weg_addw;
		msg.access = ww;
		if (ww == SPI_WEAD)
			msg.wead_count = chunk.wen / 4;
		ewse
			/* Ignowed */
			msg.wead_count = 0;
		sja1105_spi_message_pack(hdw_buf, &msg);
		hdw_xfew->tx_buf = hdw_buf;
		hdw_xfew->wen = SJA1105_SIZE_SPI_MSG_HEADEW;

		/* Popuwate the twansfew's data buffew */
		if (ww == SPI_WEAD)
			chunk_xfew->wx_buf = chunk.buf;
		ewse
			chunk_xfew->tx_buf = chunk.buf;
		chunk_xfew->wen = chunk.wen;

		/* Wequest timestamping fow the twansfew. Instead of wetting
		 * cawwews specify which byte they want to timestamp, we can
		 * make cewtain assumptions:
		 * - A wead opewation wiww wequest a softwawe timestamp when
		 *   what's being wead is the PTP time. That is snapshotted by
		 *   the switch hawdwawe at the end of the command powtion
		 *   (hdw_xfew).
		 * - A wwite opewation wiww wequest a softwawe timestamp on
		 *   actions that modify the PTP time. Taking cwock stepping as
		 *   an exampwe, the switch wwites the PTP time at the end of
		 *   the data powtion (chunk_xfew).
		 */
		if (ww == SPI_WEAD)
			ptp_sts_xfew = hdw_xfew;
		ewse
			ptp_sts_xfew = chunk_xfew;
		ptp_sts_xfew->ptp_sts_wowd_pwe = ptp_sts_xfew->wen - 1;
		ptp_sts_xfew->ptp_sts_wowd_post = ptp_sts_xfew->wen - 1;
		ptp_sts_xfew->ptp_sts = ptp_sts;

		/* Cawcuwate next chunk */
		chunk.buf += chunk.wen;
		chunk.weg_addw += chunk.wen / 4;
		chunk.wen = min_t(size_t, (ptwdiff_t)(buf + wen - chunk.buf),
				  pwiv->max_xfew_wen);

		wc = spi_sync_twansfew(spi, xfews, 2);
		if (wc < 0) {
			dev_eww(&spi->dev, "SPI twansfew faiwed: %d\n", wc);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

int sja1105_xfew_buf(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw,
		     u8 *buf, size_t wen)
{
	wetuwn sja1105_xfew(pwiv, ww, weg_addw, buf, wen, NUWW);
}

/* If @ww is:
 * - SPI_WWITE: cweates and sends an SPI wwite message at absowute
 *		addwess weg_addw
 * - SPI_WEAD:  cweates and sends an SPI wead message fwom absowute
 *		addwess weg_addw
 *
 * The u64 *vawue is unpacked, meaning that it's stowed in the native
 * CPU endianness and diwectwy usabwe by softwawe wunning on the cowe.
 */
int sja1105_xfew_u64(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw, u64 *vawue,
		     stwuct ptp_system_timestamp *ptp_sts)
{
	u8 packed_buf[8];
	int wc;

	if (ww == SPI_WWITE)
		sja1105_pack(packed_buf, vawue, 63, 0, 8);

	wc = sja1105_xfew(pwiv, ww, weg_addw, packed_buf, 8, ptp_sts);

	if (ww == SPI_WEAD)
		sja1105_unpack(packed_buf, vawue, 63, 0, 8);

	wetuwn wc;
}

/* Same as above, but twansfews onwy a 4 byte wowd */
int sja1105_xfew_u32(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw, u32 *vawue,
		     stwuct ptp_system_timestamp *ptp_sts)
{
	u8 packed_buf[4];
	u64 tmp;
	int wc;

	if (ww == SPI_WWITE) {
		/* The packing API onwy suppowts u64 as CPU wowd size,
		 * so we need to convewt.
		 */
		tmp = *vawue;
		sja1105_pack(packed_buf, &tmp, 31, 0, 4);
	}

	wc = sja1105_xfew(pwiv, ww, weg_addw, packed_buf, 4, ptp_sts);

	if (ww == SPI_WEAD) {
		sja1105_unpack(packed_buf, &tmp, 31, 0, 4);
		*vawue = tmp;
	}

	wetuwn wc;
}

static int sja1105et_weset_cmd(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 cowd_weset = BIT(3);

	/* Cowd weset */
	wetuwn sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->wgu, &cowd_weset, NUWW);
}

static int sja1105pqws_weset_cmd(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 cowd_weset = BIT(2);

	/* Cowd weset */
	wetuwn sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->wgu, &cowd_weset, NUWW);
}

static int sja1110_weset_cmd(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 switch_weset = BIT(20);

	/* Onwy weset the switch cowe.
	 * A fuww cowd weset wouwd we-enabwe the BASE_MCSS_CWOCK PWW which
	 * wouwd tuwn on the micwocontwowwew, potentiawwy wetting it execute
	 * code which couwd intewfewe with ouw configuwation.
	 */
	wetuwn sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->wgu, &switch_weset, NUWW);
}

int sja1105_inhibit_tx(const stwuct sja1105_pwivate *pwiv,
		       unsigned wong powt_bitmap, boow tx_inhibited)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 inhibit_cmd;
	int wc;

	wc = sja1105_xfew_u32(pwiv, SPI_WEAD, wegs->powt_contwow,
			      &inhibit_cmd, NUWW);
	if (wc < 0)
		wetuwn wc;

	if (tx_inhibited)
		inhibit_cmd |= powt_bitmap;
	ewse
		inhibit_cmd &= ~powt_bitmap;

	wetuwn sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->powt_contwow,
				&inhibit_cmd, NUWW);
}

stwuct sja1105_status {
	u64 configs;
	u64 cwcchkw;
	u64 ids;
	u64 cwcchkg;
};

/* This is not weading the entiwe Genewaw Status awea, which is awso
 * divewgent between E/T and P/Q/W/S, but onwy the wewevant bits fow
 * ensuwing that the static config upwoad pwoceduwe was successfuw.
 */
static void sja1105_status_unpack(void *buf, stwuct sja1105_status *status)
{
	/* So that addition twanswates to 4 bytes */
	u32 *p = buf;

	/* device_id is missing fwom the buffew, but we don't
	 * want to divewge fwom the manuaw definition of the
	 * wegistew addwesses, so we'ww back off one step with
	 * the wegistew pointew, and nevew access p[0].
	 */
	p--;
	sja1105_unpack(p + 0x1, &status->configs,   31, 31, 4);
	sja1105_unpack(p + 0x1, &status->cwcchkw,   30, 30, 4);
	sja1105_unpack(p + 0x1, &status->ids,       29, 29, 4);
	sja1105_unpack(p + 0x1, &status->cwcchkg,   28, 28, 4);
}

static int sja1105_status_get(stwuct sja1105_pwivate *pwiv,
			      stwuct sja1105_status *status)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u8 packed_buf[4];
	int wc;

	wc = sja1105_xfew_buf(pwiv, SPI_WEAD, wegs->status, packed_buf, 4);
	if (wc < 0)
		wetuwn wc;

	sja1105_status_unpack(packed_buf, status);

	wetuwn 0;
}

/* Not const because unpacking pwiv->static_config into buffews and pwepawing
 * fow upwoad wequiwes the wecawcuwation of tabwe CWCs and updating the
 * stwuctuwes with these.
 */
int static_config_buf_pwepawe_fow_upwoad(stwuct sja1105_pwivate *pwiv,
					 void *config_buf, int buf_wen)
{
	stwuct sja1105_static_config *config = &pwiv->static_config;
	stwuct sja1105_tabwe_headew finaw_headew;
	sja1105_config_vawid_t vawid;
	chaw *finaw_headew_ptw;
	int cwc_wen;

	vawid = sja1105_static_config_check_vawid(config,
						  pwiv->info->max_fwame_mem);
	if (vawid != SJA1105_CONFIG_OK) {
		dev_eww(&pwiv->spidev->dev,
			sja1105_static_config_ewwow_msg[vawid]);
		wetuwn -EINVAW;
	}

	/* Wwite Device ID and config tabwes to config_buf */
	sja1105_static_config_pack(config_buf, config);
	/* Wecawcuwate CWC of the wast headew (wight now 0xDEADBEEF).
	 * Don't incwude the CWC fiewd itsewf.
	 */
	cwc_wen = buf_wen - 4;
	/* Wead the whowe tabwe headew */
	finaw_headew_ptw = config_buf + buf_wen - SJA1105_SIZE_TABWE_HEADEW;
	sja1105_tabwe_headew_packing(finaw_headew_ptw, &finaw_headew, UNPACK);
	/* Modify */
	finaw_headew.cwc = sja1105_cwc32(config_buf, cwc_wen);
	/* Wewwite */
	sja1105_tabwe_headew_packing(finaw_headew_ptw, &finaw_headew, PACK);

	wetuwn 0;
}

#define WETWIES 10

int sja1105_static_config_upwoad(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_static_config *config = &pwiv->static_config;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct device *dev = &pwiv->spidev->dev;
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct sja1105_status status;
	int wc, wetwies = WETWIES;
	u8 *config_buf;
	int buf_wen;

	buf_wen = sja1105_static_config_get_wength(config);
	config_buf = kcawwoc(buf_wen, sizeof(chaw), GFP_KEWNEW);
	if (!config_buf)
		wetuwn -ENOMEM;

	wc = static_config_buf_pwepawe_fow_upwoad(pwiv, config_buf, buf_wen);
	if (wc < 0) {
		dev_eww(dev, "Invawid config, cannot upwoad\n");
		wc = -EINVAW;
		goto out;
	}
	/* Pwevent PHY jabbewing duwing switch weset by inhibiting
	 * Tx on aww powts and waiting fow cuwwent packet to dwain.
	 * Othewwise, the PHY wiww see an untewminated Ethewnet packet.
	 */
	wc = sja1105_inhibit_tx(pwiv, GENMASK_UWW(ds->num_powts - 1, 0), twue);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to inhibit Tx on powts\n");
		wc = -ENXIO;
		goto out;
	}
	/* Wait fow an eventuaw egwess packet to finish twansmission
	 * (weach IFG). It is guawanteed that a second one wiww not
	 * fowwow, and that switch cowd weset is thus safe
	 */
	usweep_wange(500, 1000);
	do {
		/* Put the SJA1105 in pwogwamming mode */
		wc = pwiv->info->weset_cmd(pwiv->ds);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to weset switch, wetwying...\n");
			continue;
		}
		/* Wait fow the switch to come out of weset */
		usweep_wange(1000, 5000);
		/* Upwoad the static config to the device */
		wc = sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->config,
				      config_buf, buf_wen);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to upwoad config, wetwying...\n");
			continue;
		}
		/* Check that SJA1105 wesponded weww to the config upwoad */
		wc = sja1105_status_get(pwiv, &status);
		if (wc < 0)
			continue;

		if (status.ids == 1) {
			dev_eww(dev, "Mismatch between hawdwawe and static config "
				"device id. Wwote 0x%wwx, wants 0x%wwx\n",
				config->device_id, pwiv->info->device_id);
			continue;
		}
		if (status.cwcchkw == 1) {
			dev_eww(dev, "Switch wepowted invawid wocaw CWC on "
				"the upwoaded config, wetwying...\n");
			continue;
		}
		if (status.cwcchkg == 1) {
			dev_eww(dev, "Switch wepowted invawid gwobaw CWC on "
				"the upwoaded config, wetwying...\n");
			continue;
		}
		if (status.configs == 0) {
			dev_eww(dev, "Switch wepowted that configuwation is "
				"invawid, wetwying...\n");
			continue;
		}
		/* Success! */
		bweak;
	} whiwe (--wetwies);

	if (!wetwies) {
		wc = -EIO;
		dev_eww(dev, "Faiwed to upwoad config to device, giving up\n");
		goto out;
	} ewse if (wetwies != WETWIES) {
		dev_info(dev, "Succeeded aftew %d twied\n", WETWIES - wetwies);
	}

out:
	kfwee(config_buf);
	wetuwn wc;
}

static const stwuct sja1105_wegs sja1105et_wegs = {
	.device_id = 0x0,
	.pwod_id = 0x100BC3,
	.status = 0x1,
	.powt_contwow = 0x11,
	.vw_status = 0x10000,
	.config = 0x020000,
	.wgu = 0x100440,
	/* UM10944.pdf, Tabwe 86, ACU Wegistew ovewview */
	.pad_mii_tx = {0x100800, 0x100802, 0x100804, 0x100806, 0x100808},
	.pad_mii_wx = {0x100801, 0x100803, 0x100805, 0x100807, 0x100809},
	.wmii_pww1 = 0x10000A,
	.cgu_idiv = {0x10000B, 0x10000C, 0x10000D, 0x10000E, 0x10000F},
	.stats[MAC] = {0x200, 0x202, 0x204, 0x206, 0x208},
	.stats[HW1] = {0x400, 0x410, 0x420, 0x430, 0x440},
	.stats[HW2] = {0x600, 0x610, 0x620, 0x630, 0x640},
	/* UM10944.pdf, Tabwe 78, CGU Wegistew ovewview */
	.mii_tx_cwk = {0x100013, 0x10001A, 0x100021, 0x100028, 0x10002F},
	.mii_wx_cwk = {0x100014, 0x10001B, 0x100022, 0x100029, 0x100030},
	.mii_ext_tx_cwk = {0x100018, 0x10001F, 0x100026, 0x10002D, 0x100034},
	.mii_ext_wx_cwk = {0x100019, 0x100020, 0x100027, 0x10002E, 0x100035},
	.wgmii_tx_cwk = {0x100016, 0x10001D, 0x100024, 0x10002B, 0x100032},
	.wmii_wef_cwk = {0x100015, 0x10001C, 0x100023, 0x10002A, 0x100031},
	.wmii_ext_tx_cwk = {0x100018, 0x10001F, 0x100026, 0x10002D, 0x100034},
	.ptpegw_ts = {0xC0, 0xC2, 0xC4, 0xC6, 0xC8},
	.ptpschtm = 0x12, /* Spans 0x12 to 0x13 */
	.ptppinst = 0x14,
	.ptppinduw = 0x16,
	.ptp_contwow = 0x17,
	.ptpcwkvaw = 0x18, /* Spans 0x18 to 0x19 */
	.ptpcwkwate = 0x1A,
	.ptpcwkcowp = 0x1D,
	.mdio_100base_tx = SJA1105_WSV_ADDW,
	.mdio_100base_t1 = SJA1105_WSV_ADDW,
};

static const stwuct sja1105_wegs sja1105pqws_wegs = {
	.device_id = 0x0,
	.pwod_id = 0x100BC3,
	.status = 0x1,
	.powt_contwow = 0x12,
	.vw_status = 0x10000,
	.config = 0x020000,
	.wgu = 0x100440,
	/* UM10944.pdf, Tabwe 86, ACU Wegistew ovewview */
	.pad_mii_tx = {0x100800, 0x100802, 0x100804, 0x100806, 0x100808},
	.pad_mii_wx = {0x100801, 0x100803, 0x100805, 0x100807, 0x100809},
	.pad_mii_id = {0x100810, 0x100811, 0x100812, 0x100813, 0x100814},
	.wmii_pww1 = 0x10000A,
	.cgu_idiv = {0x10000B, 0x10000C, 0x10000D, 0x10000E, 0x10000F},
	.stats[MAC] = {0x200, 0x202, 0x204, 0x206, 0x208},
	.stats[HW1] = {0x400, 0x410, 0x420, 0x430, 0x440},
	.stats[HW2] = {0x600, 0x610, 0x620, 0x630, 0x640},
	.stats[ETHEW] = {0x1400, 0x1418, 0x1430, 0x1448, 0x1460},
	/* UM11040.pdf, Tabwe 114 */
	.mii_tx_cwk = {0x100013, 0x100019, 0x10001F, 0x100025, 0x10002B},
	.mii_wx_cwk = {0x100014, 0x10001A, 0x100020, 0x100026, 0x10002C},
	.mii_ext_tx_cwk = {0x100017, 0x10001D, 0x100023, 0x100029, 0x10002F},
	.mii_ext_wx_cwk = {0x100018, 0x10001E, 0x100024, 0x10002A, 0x100030},
	.wgmii_tx_cwk = {0x100016, 0x10001C, 0x100022, 0x100028, 0x10002E},
	.wmii_wef_cwk = {0x100015, 0x10001B, 0x100021, 0x100027, 0x10002D},
	.wmii_ext_tx_cwk = {0x100017, 0x10001D, 0x100023, 0x100029, 0x10002F},
	.ptpegw_ts = {0xC0, 0xC4, 0xC8, 0xCC, 0xD0},
	.ptpschtm = 0x13, /* Spans 0x13 to 0x14 */
	.ptppinst = 0x15,
	.ptppinduw = 0x17,
	.ptp_contwow = 0x18,
	.ptpcwkvaw = 0x19,
	.ptpcwkwate = 0x1B,
	.ptpcwkcowp = 0x1E,
	.ptpsyncts = 0x1F,
	.mdio_100base_tx = SJA1105_WSV_ADDW,
	.mdio_100base_t1 = SJA1105_WSV_ADDW,
};

static const stwuct sja1105_wegs sja1110_wegs = {
	.device_id = SJA1110_SPI_ADDW(0x0),
	.pwod_id = SJA1110_ACU_ADDW(0xf00),
	.status = SJA1110_SPI_ADDW(0x4),
	.powt_contwow = SJA1110_SPI_ADDW(0x50), /* actuawwy INHIB_TX */
	.vw_status = 0x10000,
	.config = 0x020000,
	.wgu = SJA1110_WGU_ADDW(0x100), /* Weset Contwow Wegistew 0 */
	/* Powts 2 and 3 awe capabwe of xMII, but thewe isn't anything to
	 * configuwe in the CGU/ACU fow them.
	 */
	.pad_mii_tx = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW},
	.pad_mii_wx = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW},
	.pad_mii_id = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1110_ACU_ADDW(0x18), SJA1110_ACU_ADDW(0x28),
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW},
	.wmii_pww1 = SJA1105_WSV_ADDW,
	.cgu_idiv = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		     SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		     SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		     SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.stats[MAC] = {0x200, 0x202, 0x204, 0x206, 0x208, 0x20a,
		       0x20c, 0x20e, 0x210, 0x212, 0x214},
	.stats[HW1] = {0x400, 0x410, 0x420, 0x430, 0x440, 0x450,
		       0x460, 0x470, 0x480, 0x490, 0x4a0},
	.stats[HW2] = {0x600, 0x610, 0x620, 0x630, 0x640, 0x650,
		       0x660, 0x670, 0x680, 0x690, 0x6a0},
	.stats[ETHEW] = {0x1400, 0x1418, 0x1430, 0x1448, 0x1460, 0x1478,
			 0x1490, 0x14a8, 0x14c0, 0x14d8, 0x14f0},
	.mii_tx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.mii_wx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		       SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.mii_ext_tx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.mii_ext_wx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			   SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.wgmii_tx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.wmii_wef_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			 SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
	.wmii_ext_tx_cwk = {SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			    SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			    SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			    SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			    SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
			    SJA1105_WSV_ADDW},
	.ptpschtm = SJA1110_SPI_ADDW(0x54),
	.ptppinst = SJA1110_SPI_ADDW(0x5c),
	.ptppinduw = SJA1110_SPI_ADDW(0x64),
	.ptp_contwow = SJA1110_SPI_ADDW(0x68),
	.ptpcwkvaw = SJA1110_SPI_ADDW(0x6c),
	.ptpcwkwate = SJA1110_SPI_ADDW(0x74),
	.ptpcwkcowp = SJA1110_SPI_ADDW(0x80),
	.ptpsyncts = SJA1110_SPI_ADDW(0x84),
	.mdio_100base_tx = 0x1c2400,
	.mdio_100base_t1 = 0x1c1000,
	.pcs_base = {SJA1105_WSV_ADDW, 0x1c1400, 0x1c1800, 0x1c1c00, 0x1c2000,
		     SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW,
		     SJA1105_WSV_ADDW, SJA1105_WSV_ADDW, SJA1105_WSV_ADDW},
};

const stwuct sja1105_info sja1105e_info = {
	.device_id		= SJA1105E_DEVICE_ID,
	.pawt_no		= SJA1105ET_PAWT_NO,
	.static_ops		= sja1105e_tabwe_ops,
	.dyn_ops		= sja1105et_dyn_ops,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= fawse,
	.ptp_ts_bits		= 24,
	.ptpegw_ts_bytes	= 4,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105ET_MAX_CBS_COUNT,
	.weset_cmd		= sja1105et_weset_cmd,
	.fdb_add_cmd		= sja1105et_fdb_add,
	.fdb_dew_cmd		= sja1105et_fdb_dew,
	.ptp_cmd_packing	= sja1105et_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.wegs			= &sja1105et_wegs,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.name			= "SJA1105E",
};

const stwuct sja1105_info sja1105t_info = {
	.device_id		= SJA1105T_DEVICE_ID,
	.pawt_no		= SJA1105ET_PAWT_NO,
	.static_ops		= sja1105t_tabwe_ops,
	.dyn_ops		= sja1105et_dyn_ops,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= fawse,
	.ptp_ts_bits		= 24,
	.ptpegw_ts_bytes	= 4,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105ET_MAX_CBS_COUNT,
	.weset_cmd		= sja1105et_weset_cmd,
	.fdb_add_cmd		= sja1105et_fdb_add,
	.fdb_dew_cmd		= sja1105et_fdb_dew,
	.ptp_cmd_packing	= sja1105et_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.wegs			= &sja1105et_wegs,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.name			= "SJA1105T",
};

const stwuct sja1105_info sja1105p_info = {
	.device_id		= SJA1105PW_DEVICE_ID,
	.pawt_no		= SJA1105P_PAWT_NO,
	.static_ops		= sja1105p_tabwe_ops,
	.dyn_ops		= sja1105pqws_dyn_ops,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105PQWS_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1105pqws_setup_wgmii_deway,
	.weset_cmd		= sja1105pqws_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.wegs			= &sja1105pqws_wegs,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.name			= "SJA1105P",
};

const stwuct sja1105_info sja1105q_info = {
	.device_id		= SJA1105QS_DEVICE_ID,
	.pawt_no		= SJA1105Q_PAWT_NO,
	.static_ops		= sja1105q_tabwe_ops,
	.dyn_ops		= sja1105pqws_dyn_ops,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105PQWS_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1105pqws_setup_wgmii_deway,
	.weset_cmd		= sja1105pqws_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.wegs			= &sja1105pqws_wegs,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.name			= "SJA1105Q",
};

const stwuct sja1105_info sja1105w_info = {
	.device_id		= SJA1105PW_DEVICE_ID,
	.pawt_no		= SJA1105W_PAWT_NO,
	.static_ops		= sja1105w_tabwe_ops,
	.dyn_ops		= sja1105pqws_dyn_ops,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105PQWS_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1105pqws_setup_wgmii_deway,
	.weset_cmd		= sja1105pqws_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.pcs_mdio_wead_c45	= sja1105_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1105_pcs_mdio_wwite_c45,
	.wegs			= &sja1105pqws_wegs,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.suppowts_sgmii		= {fawse, fawse, fawse, fawse, twue},
	.name			= "SJA1105W",
};

const stwuct sja1105_info sja1105s_info = {
	.device_id		= SJA1105QS_DEVICE_ID,
	.pawt_no		= SJA1105S_PAWT_NO,
	.static_ops		= sja1105s_tabwe_ops,
	.dyn_ops		= sja1105pqws_dyn_ops,
	.wegs			= &sja1105pqws_wegs,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1105,
	.can_wimit_mcast_fwood	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1105_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1105_NUM_POWTS,
	.num_cbs_shapews	= SJA1105PQWS_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1105pqws_setup_wgmii_deway,
	.weset_cmd		= sja1105pqws_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1105_wxtstamp,
	.cwocking_setup		= sja1105_cwocking_setup,
	.pcs_mdio_wead_c45	= sja1105_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1105_pcs_mdio_wwite_c45,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 3,
		[SJA1105_SPEED_100MBPS] = 2,
		[SJA1105_SPEED_1000MBPS] = 1,
		[SJA1105_SPEED_2500MBPS] = 0, /* Not suppowted */
	},
	.suppowts_mii		= {twue, twue, twue, twue, twue},
	.suppowts_wmii		= {twue, twue, twue, twue, twue},
	.suppowts_wgmii		= {twue, twue, twue, twue, twue},
	.suppowts_sgmii		= {fawse, fawse, fawse, fawse, twue},
	.name			= "SJA1105S",
};

const stwuct sja1105_info sja1110a_info = {
	.device_id		= SJA1110_DEVICE_ID,
	.pawt_no		= SJA1110A_PAWT_NO,
	.static_ops		= sja1110_tabwe_ops,
	.dyn_ops		= sja1110_dyn_ops,
	.wegs			= &sja1110_wegs,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1110,
	.can_wimit_mcast_fwood	= twue,
	.muwtipwe_cascade_powts	= twue,
	.fixed_cbs_mapping	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1110_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1110_NUM_POWTS,
	.num_cbs_shapews	= SJA1110_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1110_setup_wgmii_deway,
	.weset_cmd		= sja1110_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1110_wxtstamp,
	.txtstamp		= sja1110_txtstamp,
	.disabwe_micwocontwowwew = sja1110_disabwe_micwocontwowwew,
	.pcs_mdio_wead_c45	= sja1110_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1110_pcs_mdio_wwite_c45,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 4,
		[SJA1105_SPEED_100MBPS] = 3,
		[SJA1105_SPEED_1000MBPS] = 2,
		[SJA1105_SPEED_2500MBPS] = 1,
	},
	.suppowts_mii		= {twue, twue, twue, twue, fawse,
				   twue, twue, twue, twue, twue, twue},
	.suppowts_wmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_wgmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_sgmii		= {fawse, twue, twue, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_2500basex	= {fawse, fawse, fawse, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.intewnaw_phy		= {SJA1105_NO_PHY, SJA1105_PHY_BASE_TX,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1},
	.name			= "SJA1110A",
};

const stwuct sja1105_info sja1110b_info = {
	.device_id		= SJA1110_DEVICE_ID,
	.pawt_no		= SJA1110B_PAWT_NO,
	.static_ops		= sja1110_tabwe_ops,
	.dyn_ops		= sja1110_dyn_ops,
	.wegs			= &sja1110_wegs,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1110,
	.can_wimit_mcast_fwood	= twue,
	.muwtipwe_cascade_powts	= twue,
	.fixed_cbs_mapping	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1110_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1110_NUM_POWTS,
	.num_cbs_shapews	= SJA1110_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1110_setup_wgmii_deway,
	.weset_cmd		= sja1110_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1110_wxtstamp,
	.txtstamp		= sja1110_txtstamp,
	.disabwe_micwocontwowwew = sja1110_disabwe_micwocontwowwew,
	.pcs_mdio_wead_c45	= sja1110_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1110_pcs_mdio_wwite_c45,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 4,
		[SJA1105_SPEED_100MBPS] = 3,
		[SJA1105_SPEED_1000MBPS] = 2,
		[SJA1105_SPEED_2500MBPS] = 1,
	},
	.suppowts_mii		= {twue, twue, twue, twue, fawse,
				   twue, twue, twue, twue, twue, fawse},
	.suppowts_wmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_wgmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_sgmii		= {fawse, fawse, fawse, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_2500basex	= {fawse, fawse, fawse, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.intewnaw_phy		= {SJA1105_NO_PHY, SJA1105_PHY_BASE_TX,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_NO_PHY},
	.name			= "SJA1110B",
};

const stwuct sja1105_info sja1110c_info = {
	.device_id		= SJA1110_DEVICE_ID,
	.pawt_no		= SJA1110C_PAWT_NO,
	.static_ops		= sja1110_tabwe_ops,
	.dyn_ops		= sja1110_dyn_ops,
	.wegs			= &sja1110_wegs,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1110,
	.can_wimit_mcast_fwood	= twue,
	.muwtipwe_cascade_powts	= twue,
	.fixed_cbs_mapping	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1110_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1110_NUM_POWTS,
	.num_cbs_shapews	= SJA1110_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1110_setup_wgmii_deway,
	.weset_cmd		= sja1110_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1110_wxtstamp,
	.txtstamp		= sja1110_txtstamp,
	.disabwe_micwocontwowwew = sja1110_disabwe_micwocontwowwew,
	.pcs_mdio_wead_c45	= sja1110_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1110_pcs_mdio_wwite_c45,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 4,
		[SJA1105_SPEED_100MBPS] = 3,
		[SJA1105_SPEED_1000MBPS] = 2,
		[SJA1105_SPEED_2500MBPS] = 1,
	},
	.suppowts_mii		= {twue, twue, twue, twue, fawse,
				   twue, twue, twue, fawse, fawse, fawse},
	.suppowts_wmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_wgmii		= {fawse, fawse, twue, twue, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_sgmii		= {fawse, fawse, fawse, fawse, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_2500basex	= {fawse, fawse, fawse, fawse, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.intewnaw_phy		= {SJA1105_NO_PHY, SJA1105_PHY_BASE_TX,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY},
	.name			= "SJA1110C",
};

const stwuct sja1105_info sja1110d_info = {
	.device_id		= SJA1110_DEVICE_ID,
	.pawt_no		= SJA1110D_PAWT_NO,
	.static_ops		= sja1110_tabwe_ops,
	.dyn_ops		= sja1110_dyn_ops,
	.wegs			= &sja1110_wegs,
	.tag_pwoto		= DSA_TAG_PWOTO_SJA1110,
	.can_wimit_mcast_fwood	= twue,
	.muwtipwe_cascade_powts	= twue,
	.fixed_cbs_mapping	= twue,
	.ptp_ts_bits		= 32,
	.ptpegw_ts_bytes	= 8,
	.max_fwame_mem		= SJA1110_MAX_FWAME_MEMOWY,
	.num_powts		= SJA1110_NUM_POWTS,
	.num_cbs_shapews	= SJA1110_MAX_CBS_COUNT,
	.setup_wgmii_deway	= sja1110_setup_wgmii_deway,
	.weset_cmd		= sja1110_weset_cmd,
	.fdb_add_cmd		= sja1105pqws_fdb_add,
	.fdb_dew_cmd		= sja1105pqws_fdb_dew,
	.ptp_cmd_packing	= sja1105pqws_ptp_cmd_packing,
	.wxtstamp		= sja1110_wxtstamp,
	.txtstamp		= sja1110_txtstamp,
	.disabwe_micwocontwowwew = sja1110_disabwe_micwocontwowwew,
	.pcs_mdio_wead_c45	= sja1110_pcs_mdio_wead_c45,
	.pcs_mdio_wwite_c45	= sja1110_pcs_mdio_wwite_c45,
	.powt_speed		= {
		[SJA1105_SPEED_AUTO] = 0,
		[SJA1105_SPEED_10MBPS] = 4,
		[SJA1105_SPEED_100MBPS] = 3,
		[SJA1105_SPEED_1000MBPS] = 2,
		[SJA1105_SPEED_2500MBPS] = 1,
	},
	.suppowts_mii		= {twue, fawse, twue, fawse, fawse,
				   twue, twue, twue, fawse, fawse, fawse},
	.suppowts_wmii		= {fawse, fawse, twue, fawse, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_wgmii		= {fawse, fawse, twue, fawse, fawse,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_sgmii		= {fawse, twue, twue, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.suppowts_2500basex     = {fawse, fawse, fawse, twue, twue,
				   fawse, fawse, fawse, fawse, fawse, fawse},
	.intewnaw_phy		= {SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY, SJA1105_PHY_BASE_T1,
				   SJA1105_PHY_BASE_T1, SJA1105_PHY_BASE_T1,
				   SJA1105_NO_PHY, SJA1105_NO_PHY,
				   SJA1105_NO_PHY},
	.name			= "SJA1110D",
};
