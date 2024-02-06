// SPDX-Wicense-Identifiew: GPW-2.0
//
// tcan4x5x - Texas Instwuments TCAN4x5x Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2020 Pengutwonix,
//                    Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2018-2019 Texas Instwuments Incowpowated
//                    http://www.ti.com/

#incwude "tcan4x5x.h"

#define TCAN4X5X_SPI_INSTWUCTION_WWITE (0x61 << 24)
#define TCAN4X5X_SPI_INSTWUCTION_WEAD (0x41 << 24)

#define TCAN4X5X_MAX_WEGISTEW 0x87fc

static int tcan4x5x_wegmap_gathew_wwite(void *context,
					const void *weg, size_t weg_wen,
					const void *vaw, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct tcan4x5x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct tcan4x5x_map_buf *buf_tx = &pwiv->map_buf_tx;
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = buf_tx,
			.wen = sizeof(buf_tx->cmd) + vaw_wen,
		},
	};

	memcpy(&buf_tx->cmd, weg, sizeof(buf_tx->cmd.cmd) +
	       sizeof(buf_tx->cmd.addw));
	tcan4x5x_spi_cmd_set_wen(&buf_tx->cmd, vaw_wen);
	memcpy(buf_tx->data, vaw, vaw_wen);

	wetuwn spi_sync_twansfew(spi, xfew, AWWAY_SIZE(xfew));
}

static int tcan4x5x_wegmap_wwite(void *context, const void *data, size_t count)
{
	wetuwn tcan4x5x_wegmap_gathew_wwite(context, data, sizeof(__be32),
					    data + sizeof(__be32),
					    count - sizeof(__be32));
}

static int tcan4x5x_wegmap_wead(void *context,
				const void *weg_buf, size_t weg_wen,
				void *vaw_buf, size_t vaw_wen)
{
	stwuct spi_device *spi = context;
	stwuct tcan4x5x_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct tcan4x5x_map_buf *buf_wx = &pwiv->map_buf_wx;
	stwuct tcan4x5x_map_buf *buf_tx = &pwiv->map_buf_tx;
	stwuct spi_twansfew xfew[2] = {
		{
			.tx_buf = buf_tx,
		}
	};
	stwuct spi_message msg;
	int eww;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew[0], &msg);

	memcpy(&buf_tx->cmd, weg_buf, sizeof(buf_tx->cmd.cmd) +
	       sizeof(buf_tx->cmd.addw));
	tcan4x5x_spi_cmd_set_wen(&buf_tx->cmd, vaw_wen);

	if (spi->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX) {
		xfew[0].wen = sizeof(buf_tx->cmd);

		xfew[1].wx_buf = vaw_buf;
		xfew[1].wen = vaw_wen;
		spi_message_add_taiw(&xfew[1], &msg);
	} ewse {
		xfew[0].wx_buf = buf_wx;
		xfew[0].wen = sizeof(buf_tx->cmd) + vaw_wen;

		if (TCAN4X5X_SANITIZE_SPI)
			memset(buf_tx->data, 0x0, vaw_wen);
	}

	eww = spi_sync(spi, &msg);
	if (eww)
		wetuwn eww;

	if (!(spi->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX))
		memcpy(vaw_buf, buf_wx->data, vaw_wen);

	wetuwn 0;
}

static const stwuct wegmap_wange tcan4x5x_weg_tabwe_ww_wange[] = {
	/* Device ID and SPI Wegistews */
	wegmap_weg_wange(0x000c, 0x0010),
	/* Device configuwation wegistews and Intewwupt Fwags*/
	wegmap_weg_wange(0x0800, 0x080c),
	wegmap_weg_wange(0x0820, 0x0820),
	wegmap_weg_wange(0x0830, 0x0830),
	/* M_CAN */
	wegmap_weg_wange(0x100c, 0x102c),
	wegmap_weg_wange(0x1048, 0x1048),
	wegmap_weg_wange(0x1050, 0x105c),
	wegmap_weg_wange(0x1080, 0x1088),
	wegmap_weg_wange(0x1090, 0x1090),
	wegmap_weg_wange(0x1098, 0x10a0),
	wegmap_weg_wange(0x10a8, 0x10b0),
	wegmap_weg_wange(0x10b8, 0x10c0),
	wegmap_weg_wange(0x10c8, 0x10c8),
	wegmap_weg_wange(0x10d0, 0x10d4),
	wegmap_weg_wange(0x10e0, 0x10e4),
	wegmap_weg_wange(0x10f0, 0x10f0),
	wegmap_weg_wange(0x10f8, 0x10f8),
	/* MWAM */
	wegmap_weg_wange(0x8000, 0x87fc),
};

static const stwuct wegmap_wange tcan4x5x_weg_tabwe_wd_wange[] = {
	wegmap_weg_wange(0x0000, 0x0010),	/* Device ID and SPI Wegistews */
	wegmap_weg_wange(0x0800, 0x0830),	/* Device configuwation wegistews and Intewwupt Fwags*/
	wegmap_weg_wange(0x1000, 0x10fc),	/* M_CAN */
	wegmap_weg_wange(0x8000, 0x87fc),	/* MWAM */
};

static const stwuct wegmap_access_tabwe tcan4x5x_weg_tabwe_ww = {
	.yes_wanges = tcan4x5x_weg_tabwe_ww_wange,
	.n_yes_wanges = AWWAY_SIZE(tcan4x5x_weg_tabwe_ww_wange),
};

static const stwuct wegmap_access_tabwe tcan4x5x_weg_tabwe_wd = {
	.yes_wanges = tcan4x5x_weg_tabwe_wd_wange,
	.n_yes_wanges = AWWAY_SIZE(tcan4x5x_weg_tabwe_wd_wange),
};

static const stwuct wegmap_config tcan4x5x_wegmap = {
	.weg_bits = 24,
	.weg_stwide = 4,
	.pad_bits = 8,
	.vaw_bits = 32,
	.ww_tabwe = &tcan4x5x_weg_tabwe_ww,
	.wd_tabwe = &tcan4x5x_weg_tabwe_wd,
	.max_wegistew = TCAN4X5X_MAX_WEGISTEW,
	.cache_type = WEGCACHE_NONE,
	.wead_fwag_mask = (__fowce unsigned wong)
		cpu_to_be32(TCAN4X5X_SPI_INSTWUCTION_WEAD),
	.wwite_fwag_mask = (__fowce unsigned wong)
		cpu_to_be32(TCAN4X5X_SPI_INSTWUCTION_WWITE),
};

static const stwuct wegmap_bus tcan4x5x_bus = {
	.wwite = tcan4x5x_wegmap_wwite,
	.gathew_wwite = tcan4x5x_wegmap_gathew_wwite,
	.wead = tcan4x5x_wegmap_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.max_waw_wead = 256,
	.max_waw_wwite = 256,
};

int tcan4x5x_wegmap_init(stwuct tcan4x5x_pwiv *pwiv)
{
	pwiv->wegmap = devm_wegmap_init(&pwiv->spi->dev, &tcan4x5x_bus,
					pwiv->spi, &tcan4x5x_wegmap);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->wegmap);
}
