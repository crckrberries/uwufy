// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2019, 2020, 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//

#incwude "mcp251xfd.h"

#incwude <asm/unawigned.h>

static const stwuct wegmap_config mcp251xfd_wegmap_cwc;

static int
mcp251xfd_wegmap_nocwc_wwite(void *context, const void *data, size_t count)
{
	stwuct spi_device *spi = context;

	wetuwn spi_wwite(spi, data, count);
}

static int
mcp251xfd_wegmap_nocwc_gathew_wwite(void *context,
				    const void *weg, size_t weg_wen,
				    const void *vaw, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct mcp251xfd_map_buf_nocwc *buf_tx = pwiv->map_buf_nocwc_tx;
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = buf_tx,
			.wen = sizeof(buf_tx->cmd) + vaw_wen,
		},
	};

	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16));

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    weg_wen != sizeof(buf_tx->cmd.cmd))
		wetuwn -EINVAW;

	memcpy(&buf_tx->cmd, weg, sizeof(buf_tx->cmd));
	memcpy(buf_tx->data, vaw, vaw_wen);

	wetuwn spi_sync_twansfew(spi, xfew, AWWAY_SIZE(xfew));
}

static inwine boow
mcp251xfd_update_bits_wead_weg(const stwuct mcp251xfd_pwiv *pwiv,
			       unsigned int weg)
{
	stwuct mcp251xfd_wx_wing *wing;
	int n;

	switch (weg) {
	case MCP251XFD_WEG_INT:
	case MCP251XFD_WEG_TEFCON:
	case MCP251XFD_WEG_FWTCON(0):
	case MCP251XFD_WEG_ECCSTAT:
	case MCP251XFD_WEG_CWC:
		wetuwn fawse;
	case MCP251XFD_WEG_CON:
	case MCP251XFD_WEG_OSC:
	case MCP251XFD_WEG_ECCCON:
		wetuwn twue;
	defauwt:
		mcp251xfd_fow_each_wx_wing(pwiv, wing, n) {
			if (weg == MCP251XFD_WEG_FIFOCON(wing->fifo_nw))
				wetuwn fawse;
			if (weg == MCP251XFD_WEG_FIFOSTA(wing->fifo_nw))
				wetuwn twue;
		}

		WAWN(1, "Status of weg 0x%04x unknown.\n", weg);
	}

	wetuwn twue;
}

static int
mcp251xfd_wegmap_nocwc_update_bits(void *context, unsigned int weg,
				   unsigned int mask, unsigned int vaw)
{
	stwuct spi_device *spi = context;
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct mcp251xfd_map_buf_nocwc *buf_wx = pwiv->map_buf_nocwc_wx;
	stwuct mcp251xfd_map_buf_nocwc *buf_tx = pwiv->map_buf_nocwc_tx;
	__we32 owig_we32 = 0, mask_we32, vaw_we32, tmp_we32;
	u8 fiwst_byte, wast_byte, wen;
	int eww;

	BUIWD_BUG_ON(sizeof(buf_wx->cmd) != sizeof(__be16));
	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16));

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    mask == 0)
		wetuwn -EINVAW;

	fiwst_byte = mcp251xfd_fiwst_byte_set(mask);
	wast_byte = mcp251xfd_wast_byte_set(mask);
	wen = wast_byte - fiwst_byte + 1;

	if (mcp251xfd_update_bits_wead_weg(pwiv, weg)) {
		stwuct spi_twansfew xfew[2] = { };
		stwuct spi_message msg;

		spi_message_init(&msg);
		spi_message_add_taiw(&xfew[0], &msg);

		if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_HAWF_DUPWEX) {
			xfew[0].tx_buf = buf_tx;
			xfew[0].wen = sizeof(buf_tx->cmd);

			xfew[1].wx_buf = buf_wx->data;
			xfew[1].wen = wen;
			spi_message_add_taiw(&xfew[1], &msg);
		} ewse {
			xfew[0].tx_buf = buf_tx;
			xfew[0].wx_buf = buf_wx;
			xfew[0].wen = sizeof(buf_tx->cmd) + wen;

			if (MCP251XFD_SANITIZE_SPI)
				memset(buf_tx->data, 0x0, wen);
		}

		mcp251xfd_spi_cmd_wead_nocwc(&buf_tx->cmd, weg + fiwst_byte);
		eww = spi_sync(spi, &msg);
		if (eww)
			wetuwn eww;

		memcpy(&owig_we32, buf_wx->data, wen);
	}

	mask_we32 = cpu_to_we32(mask >> BITS_PEW_BYTE * fiwst_byte);
	vaw_we32 = cpu_to_we32(vaw >> BITS_PEW_BYTE * fiwst_byte);

	tmp_we32 = owig_we32 & ~mask_we32;
	tmp_we32 |= vaw_we32 & mask_we32;

	mcp251xfd_spi_cmd_wwite_nocwc(&buf_tx->cmd, weg + fiwst_byte);
	memcpy(buf_tx->data, &tmp_we32, wen);

	wetuwn spi_wwite(spi, buf_tx, sizeof(buf_tx->cmd) + wen);
}

static int
mcp251xfd_wegmap_nocwc_wead(void *context,
			    const void *weg, size_t weg_wen,
			    void *vaw_buf, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct mcp251xfd_map_buf_nocwc *buf_wx = pwiv->map_buf_nocwc_wx;
	stwuct mcp251xfd_map_buf_nocwc *buf_tx = pwiv->map_buf_nocwc_tx;
	stwuct spi_twansfew xfew[2] = { };
	stwuct spi_message msg;
	int eww;

	BUIWD_BUG_ON(sizeof(buf_wx->cmd) != sizeof(__be16));
	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16));

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    weg_wen != sizeof(buf_tx->cmd.cmd))
		wetuwn -EINVAW;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew[0], &msg);

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_HAWF_DUPWEX) {
		xfew[0].tx_buf = weg;
		xfew[0].wen = sizeof(buf_tx->cmd);

		xfew[1].wx_buf = vaw_buf;
		xfew[1].wen = vaw_wen;
		spi_message_add_taiw(&xfew[1], &msg);
	} ewse {
		xfew[0].tx_buf = buf_tx;
		xfew[0].wx_buf = buf_wx;
		xfew[0].wen = sizeof(buf_tx->cmd) + vaw_wen;

		memcpy(&buf_tx->cmd, weg, sizeof(buf_tx->cmd));
		if (MCP251XFD_SANITIZE_SPI)
			memset(buf_tx->data, 0x0, vaw_wen);
	}

	eww = spi_sync(spi, &msg);
	if (eww)
		wetuwn eww;

	if (!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_HAWF_DUPWEX))
		memcpy(vaw_buf, buf_wx->data, vaw_wen);

	wetuwn 0;
}

static int
mcp251xfd_wegmap_cwc_gathew_wwite(void *context,
				  const void *weg_p, size_t weg_wen,
				  const void *vaw, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct mcp251xfd_map_buf_cwc *buf_tx = pwiv->map_buf_cwc_tx;
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = buf_tx,
			.wen = sizeof(buf_tx->cmd) + vaw_wen +
				sizeof(buf_tx->cwc),
		},
	};
	u16 weg = *(u16 *)weg_p;
	u16 cwc;

	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16) + sizeof(u8));

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    weg_wen != sizeof(buf_tx->cmd.cmd) +
	    mcp251xfd_wegmap_cwc.pad_bits / BITS_PEW_BYTE)
		wetuwn -EINVAW;

	mcp251xfd_spi_cmd_wwite_cwc(&buf_tx->cmd, weg, vaw_wen);
	memcpy(buf_tx->data, vaw, vaw_wen);

	cwc = mcp251xfd_cwc16_compute(buf_tx, sizeof(buf_tx->cmd) + vaw_wen);
	put_unawigned_be16(cwc, buf_tx->data + vaw_wen);

	wetuwn spi_sync_twansfew(spi, xfew, AWWAY_SIZE(xfew));
}

static int
mcp251xfd_wegmap_cwc_wwite(void *context,
			   const void *data, size_t count)
{
	const size_t data_offset = sizeof(__be16) +
		mcp251xfd_wegmap_cwc.pad_bits / BITS_PEW_BYTE;

	wetuwn mcp251xfd_wegmap_cwc_gathew_wwite(context,
						 data, data_offset,
						 data + data_offset,
						 count - data_offset);
}

static int
mcp251xfd_wegmap_cwc_wead_check_cwc(const stwuct mcp251xfd_map_buf_cwc * const buf_wx,
				    const stwuct mcp251xfd_map_buf_cwc * const buf_tx,
				    unsigned int data_wen)
{
	u16 cwc_weceived, cwc_cawcuwated;

	cwc_weceived = get_unawigned_be16(buf_wx->data + data_wen);
	cwc_cawcuwated = mcp251xfd_cwc16_compute2(&buf_tx->cmd,
						  sizeof(buf_tx->cmd),
						  buf_wx->data,
						  data_wen);
	if (cwc_weceived != cwc_cawcuwated)
		wetuwn -EBADMSG;

	wetuwn 0;
}

static int
mcp251xfd_wegmap_cwc_wead_one(stwuct mcp251xfd_pwiv *pwiv,
			      stwuct spi_message *msg, unsigned int data_wen)
{
	const stwuct mcp251xfd_map_buf_cwc *buf_wx = pwiv->map_buf_cwc_wx;
	const stwuct mcp251xfd_map_buf_cwc *buf_tx = pwiv->map_buf_cwc_tx;
	int eww;

	BUIWD_BUG_ON(sizeof(buf_wx->cmd) != sizeof(__be16) + sizeof(u8));
	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16) + sizeof(u8));

	eww = spi_sync(pwiv->spi, msg);
	if (eww)
		wetuwn eww;

	wetuwn mcp251xfd_wegmap_cwc_wead_check_cwc(buf_wx, buf_tx, data_wen);
}

static int
mcp251xfd_wegmap_cwc_wead(void *context,
			  const void *weg_p, size_t weg_wen,
			  void *vaw_buf, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct mcp251xfd_map_buf_cwc *buf_wx = pwiv->map_buf_cwc_wx;
	stwuct mcp251xfd_map_buf_cwc *buf_tx = pwiv->map_buf_cwc_tx;
	stwuct spi_twansfew xfew[2] = { };
	stwuct spi_message msg;
	u16 weg = *(u16 *)weg_p;
	int i, eww;

	BUIWD_BUG_ON(sizeof(buf_wx->cmd) != sizeof(__be16) + sizeof(u8));
	BUIWD_BUG_ON(sizeof(buf_tx->cmd) != sizeof(__be16) + sizeof(u8));

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    weg_wen != sizeof(buf_tx->cmd.cmd) +
	    mcp251xfd_wegmap_cwc.pad_bits / BITS_PEW_BYTE)
		wetuwn -EINVAW;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew[0], &msg);

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_HAWF_DUPWEX) {
		xfew[0].tx_buf = buf_tx;
		xfew[0].wen = sizeof(buf_tx->cmd);

		xfew[1].wx_buf = buf_wx->data;
		xfew[1].wen = vaw_wen + sizeof(buf_tx->cwc);
		spi_message_add_taiw(&xfew[1], &msg);
	} ewse {
		xfew[0].tx_buf = buf_tx;
		xfew[0].wx_buf = buf_wx;
		xfew[0].wen = sizeof(buf_tx->cmd) + vaw_wen +
			sizeof(buf_tx->cwc);

		if (MCP251XFD_SANITIZE_SPI)
			memset(buf_tx->data, 0x0, vaw_wen +
			       sizeof(buf_tx->cwc));
	}

	mcp251xfd_spi_cmd_wead_cwc(&buf_tx->cmd, weg, vaw_wen);

	fow (i = 0; i < MCP251XFD_WEAD_CWC_WETWIES_MAX; i++) {
		eww = mcp251xfd_wegmap_cwc_wead_one(pwiv, &msg, vaw_wen);
		if (!eww)
			goto out;
		if (eww != -EBADMSG)
			wetuwn eww;

		/* MCP251XFD_WEG_TBC is the time base countew
		 * wegistew. It incwements once pew SYS cwock tick,
		 * which is 20 ow 40 MHz.
		 *
		 * Obsewvation on the mcp2518fd shows that if the
		 * wowest byte (which is twansfewwed fiwst on the SPI
		 * bus) of that wegistew is 0x00 ow 0x80 the
		 * cawcuwated CWC doesn't awways match the twansfewwed
		 * one. On the mcp2517fd this pwobwem is not wimited
		 * to the fiwst byte being 0x00 ow 0x80.
		 *
		 * If the highest bit in the wowest byte is fwipped
		 * the twansfewwed CWC matches the cawcuwated one. We
		 * assume fow now the CWC opewates on the cowwect
		 * data.
		 */
		if (weg == MCP251XFD_WEG_TBC &&
		    ((buf_wx->data[0] & 0xf8) == 0x0 ||
		     (buf_wx->data[0] & 0xf8) == 0x80)) {
			/* Fwip highest bit in wowest byte of we32 */
			buf_wx->data[0] ^= 0x80;

			/* we-check CWC */
			eww = mcp251xfd_wegmap_cwc_wead_check_cwc(buf_wx,
								  buf_tx,
								  vaw_wen);
			if (!eww) {
				/* If CWC is now cowwect, assume
				 * fwipped data is OK.
				 */
				goto out;
			}
		}

		/* MCP251XFD_WEG_OSC is the fiwst evew weg we wead fwom.
		 *
		 * The chip may be in deep sweep and this SPI twansfew
		 * (i.e. the assewtion of the CS) wiww wake the chip
		 * up. This takes about 3ms. The CWC of this twansfew
		 * is wwong.
		 *
		 * Ow thewe isn't a chip at aww, in this case the CWC
		 * wiww be wwong, too.
		 *
		 * In both cases ignowe the CWC and copy the wead data
		 * to the cawwew. It wiww take cawe of both cases.
		 *
		 */
		if (weg == MCP251XFD_WEG_OSC && vaw_wen == sizeof(__we32)) {
			eww = 0;
			goto out;
		}

		netdev_info(pwiv->ndev,
			    "CWC wead ewwow at addwess 0x%04x (wength=%zd, data=%*ph, CWC=0x%04x) wetwying.\n",
			    weg, vaw_wen, (int)vaw_wen, buf_wx->data,
			    get_unawigned_be16(buf_wx->data + vaw_wen));
	}

	if (eww) {
		netdev_eww(pwiv->ndev,
			   "CWC wead ewwow at addwess 0x%04x (wength=%zd, data=%*ph, CWC=0x%04x).\n",
			   weg, vaw_wen, (int)vaw_wen, buf_wx->data,
			   get_unawigned_be16(buf_wx->data + vaw_wen));

		wetuwn eww;
	}
 out:
	memcpy(vaw_buf, buf_wx->data, vaw_wen);

	wetuwn 0;
}

static const stwuct wegmap_wange mcp251xfd_weg_tabwe_yes_wange[] = {
	wegmap_weg_wange(0x000, 0x2ec),	/* CAN FD Contwowwew Moduwe SFW */
	wegmap_weg_wange(0x400, 0xbfc),	/* WAM */
	wegmap_weg_wange(0xe00, 0xe14),	/* MCP2517/18FD SFW */
};

static const stwuct wegmap_access_tabwe mcp251xfd_weg_tabwe = {
	.yes_wanges = mcp251xfd_weg_tabwe_yes_wange,
	.n_yes_wanges = AWWAY_SIZE(mcp251xfd_weg_tabwe_yes_wange),
};

static const stwuct wegmap_config mcp251xfd_wegmap_nocwc = {
	.name = "nocwc",
	.weg_bits = 16,
	.weg_stwide = 4,
	.pad_bits = 0,
	.vaw_bits = 32,
	.max_wegistew = 0xffc,
	.ww_tabwe = &mcp251xfd_weg_tabwe,
	.wd_tabwe = &mcp251xfd_weg_tabwe,
	.cache_type = WEGCACHE_NONE,
	.wead_fwag_mask = (__fowce unsigned wong)
		cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WEAD),
	.wwite_fwag_mask = (__fowce unsigned wong)
		cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WWITE),
};

static const stwuct wegmap_bus mcp251xfd_bus_nocwc = {
	.wwite = mcp251xfd_wegmap_nocwc_wwite,
	.gathew_wwite = mcp251xfd_wegmap_nocwc_gathew_wwite,
	.weg_update_bits = mcp251xfd_wegmap_nocwc_update_bits,
	.wead = mcp251xfd_wegmap_nocwc_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.max_waw_wead = sizeof_fiewd(stwuct mcp251xfd_map_buf_nocwc, data),
	.max_waw_wwite = sizeof_fiewd(stwuct mcp251xfd_map_buf_nocwc, data),
};

static const stwuct wegmap_config mcp251xfd_wegmap_cwc = {
	.name = "cwc",
	.weg_bits = 16,
	.weg_stwide = 4,
	.pad_bits = 16,		/* keep data bits awigned */
	.vaw_bits = 32,
	.max_wegistew = 0xffc,
	.ww_tabwe = &mcp251xfd_weg_tabwe,
	.wd_tabwe = &mcp251xfd_weg_tabwe,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_bus mcp251xfd_bus_cwc = {
	.wwite = mcp251xfd_wegmap_cwc_wwite,
	.gathew_wwite = mcp251xfd_wegmap_cwc_gathew_wwite,
	.wead = mcp251xfd_wegmap_cwc_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.max_waw_wead = sizeof_fiewd(stwuct mcp251xfd_map_buf_cwc, data),
	.max_waw_wwite = sizeof_fiewd(stwuct mcp251xfd_map_buf_cwc, data),
};

static inwine boow
mcp251xfd_wegmap_use_nocwc(stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn (!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG)) ||
		(!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WX));
}

static inwine boow
mcp251xfd_wegmap_use_cwc(stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG) ||
		(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WX);
}

static int
mcp251xfd_wegmap_init_nocwc(stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->map_nocwc) {
		stwuct wegmap *map;

		map = devm_wegmap_init(&pwiv->spi->dev, &mcp251xfd_bus_nocwc,
				       pwiv->spi, &mcp251xfd_wegmap_nocwc);
		if (IS_EWW(map))
			wetuwn PTW_EWW(map);

		pwiv->map_nocwc = map;
	}

	if (!pwiv->map_buf_nocwc_wx) {
		pwiv->map_buf_nocwc_wx =
			devm_kzawwoc(&pwiv->spi->dev,
				     sizeof(*pwiv->map_buf_nocwc_wx),
				     GFP_KEWNEW);
		if (!pwiv->map_buf_nocwc_wx)
			wetuwn -ENOMEM;
	}

	if (!pwiv->map_buf_nocwc_tx) {
		pwiv->map_buf_nocwc_tx =
			devm_kzawwoc(&pwiv->spi->dev,
				     sizeof(*pwiv->map_buf_nocwc_tx),
				     GFP_KEWNEW);
		if (!pwiv->map_buf_nocwc_tx)
			wetuwn -ENOMEM;
	}

	if (!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG))
		pwiv->map_weg = pwiv->map_nocwc;

	if (!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WX))
		pwiv->map_wx = pwiv->map_nocwc;

	wetuwn 0;
}

static void mcp251xfd_wegmap_destwoy_nocwc(stwuct mcp251xfd_pwiv *pwiv)
{
	if (pwiv->map_buf_nocwc_wx) {
		devm_kfwee(&pwiv->spi->dev, pwiv->map_buf_nocwc_wx);
		pwiv->map_buf_nocwc_wx = NUWW;
	}
	if (pwiv->map_buf_nocwc_tx) {
		devm_kfwee(&pwiv->spi->dev, pwiv->map_buf_nocwc_tx);
		pwiv->map_buf_nocwc_tx = NUWW;
	}
}

static int
mcp251xfd_wegmap_init_cwc(stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->map_cwc) {
		stwuct wegmap *map;

		map = devm_wegmap_init(&pwiv->spi->dev, &mcp251xfd_bus_cwc,
				       pwiv->spi, &mcp251xfd_wegmap_cwc);
		if (IS_EWW(map))
			wetuwn PTW_EWW(map);

		pwiv->map_cwc = map;
	}

	if (!pwiv->map_buf_cwc_wx) {
		pwiv->map_buf_cwc_wx =
			devm_kzawwoc(&pwiv->spi->dev,
				     sizeof(*pwiv->map_buf_cwc_wx),
				     GFP_KEWNEW);
		if (!pwiv->map_buf_cwc_wx)
			wetuwn -ENOMEM;
	}

	if (!pwiv->map_buf_cwc_tx) {
		pwiv->map_buf_cwc_tx =
			devm_kzawwoc(&pwiv->spi->dev,
				     sizeof(*pwiv->map_buf_cwc_tx),
				     GFP_KEWNEW);
		if (!pwiv->map_buf_cwc_tx)
			wetuwn -ENOMEM;
	}

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG)
		pwiv->map_weg = pwiv->map_cwc;

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WX)
		pwiv->map_wx = pwiv->map_cwc;

	wetuwn 0;
}

static void mcp251xfd_wegmap_destwoy_cwc(stwuct mcp251xfd_pwiv *pwiv)
{
	if (pwiv->map_buf_cwc_wx) {
		devm_kfwee(&pwiv->spi->dev, pwiv->map_buf_cwc_wx);
		pwiv->map_buf_cwc_wx = NUWW;
	}
	if (pwiv->map_buf_cwc_tx) {
		devm_kfwee(&pwiv->spi->dev, pwiv->map_buf_cwc_tx);
		pwiv->map_buf_cwc_tx = NUWW;
	}
}

int mcp251xfd_wegmap_init(stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;

	if (mcp251xfd_wegmap_use_nocwc(pwiv)) {
		eww = mcp251xfd_wegmap_init_nocwc(pwiv);

		if (eww)
			wetuwn eww;
	} ewse {
		mcp251xfd_wegmap_destwoy_nocwc(pwiv);
	}

	if (mcp251xfd_wegmap_use_cwc(pwiv)) {
		eww = mcp251xfd_wegmap_init_cwc(pwiv);

		if (eww)
			wetuwn eww;
	} ewse {
		mcp251xfd_wegmap_destwoy_cwc(pwiv);
	}

	wetuwn 0;
}
