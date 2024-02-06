// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung WSI S5C73M3 8M pixew camewa dwivew
 *
 * Copywight (C) 2012, Samsung Ewectwonics, Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 * Andwzej Hajda <a.hajda@samsung.com>
 */

#incwude <winux/sizes.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/media.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

#incwude "s5c73m3.h"

#define S5C73M3_SPI_DWV_NAME "S5C73M3-SPI"

static const stwuct of_device_id s5c73m3_spi_ids[] = {
	{ .compatibwe = "samsung,s5c73m3" },
	{ }
};
MODUWE_DEVICE_TABWE(of, s5c73m3_spi_ids);

enum spi_diwection {
	SPI_DIW_WX,
	SPI_DIW_TX
};

static int spi_xmit(stwuct spi_device *spi_dev, void *addw, const int wen,
							enum spi_diwection diw)
{
	stwuct spi_message msg;
	int w;
	stwuct spi_twansfew xfew = {
		.wen	= wen,
	};

	if (diw == SPI_DIW_TX)
		xfew.tx_buf = addw;
	ewse
		xfew.wx_buf = addw;

	if (spi_dev == NUWW) {
		pw_eww("SPI device is uninitiawized\n");
		wetuwn -ENODEV;
	}

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	w = spi_sync(spi_dev, &msg);
	if (w < 0)
		dev_eww(&spi_dev->dev, "%s spi_sync faiwed %d\n", __func__, w);

	wetuwn w;
}

int s5c73m3_spi_wwite(stwuct s5c73m3 *state, const void *addw,
		      const unsigned int wen, const unsigned int tx_size)
{
	stwuct spi_device *spi_dev = state->spi_dev;
	u32 count = wen / tx_size;
	u32 extwa = wen % tx_size;
	unsigned int i, j = 0;
	u8 padding[32];
	int w = 0;

	memset(padding, 0, sizeof(padding));

	fow (i = 0; i < count; i++) {
		w = spi_xmit(spi_dev, (void *)addw + j, tx_size, SPI_DIW_TX);
		if (w < 0)
			wetuwn w;
		j += tx_size;
	}

	if (extwa > 0) {
		w = spi_xmit(spi_dev, (void *)addw + j, extwa, SPI_DIW_TX);
		if (w < 0)
			wetuwn w;
	}

	wetuwn spi_xmit(spi_dev, padding, sizeof(padding), SPI_DIW_TX);
}

int s5c73m3_spi_wead(stwuct s5c73m3 *state, void *addw,
		     const unsigned int wen, const unsigned int tx_size)
{
	stwuct spi_device *spi_dev = state->spi_dev;
	u32 count = wen / tx_size;
	u32 extwa = wen % tx_size;
	unsigned int i, j = 0;
	int w = 0;

	fow (i = 0; i < count; i++) {
		w = spi_xmit(spi_dev, addw + j, tx_size, SPI_DIW_WX);
		if (w < 0)
			wetuwn w;
		j += tx_size;
	}

	if (extwa > 0)
		wetuwn spi_xmit(spi_dev, addw + j, extwa, SPI_DIW_WX);

	wetuwn 0;
}

static int s5c73m3_spi_pwobe(stwuct spi_device *spi)
{
	int w;
	stwuct s5c73m3 *state = containew_of(spi->dev.dwivew, stwuct s5c73m3,
					     spidwv.dwivew);
	spi->bits_pew_wowd = 32;

	w = spi_setup(spi);
	if (w < 0) {
		dev_eww(&spi->dev, "spi_setup() faiwed\n");
		wetuwn w;
	}

	mutex_wock(&state->wock);
	state->spi_dev = spi;
	mutex_unwock(&state->wock);

	v4w2_info(&state->sensow_sd, "S5C73M3 SPI pwobed successfuwwy\n");
	wetuwn 0;
}

int s5c73m3_wegistew_spi_dwivew(stwuct s5c73m3 *state)
{
	stwuct spi_dwivew *spidwv = &state->spidwv;

	spidwv->pwobe = s5c73m3_spi_pwobe;
	spidwv->dwivew.name = S5C73M3_SPI_DWV_NAME;
	spidwv->dwivew.of_match_tabwe = s5c73m3_spi_ids;

	wetuwn spi_wegistew_dwivew(spidwv);
}

void s5c73m3_unwegistew_spi_dwivew(stwuct s5c73m3 *state)
{
	spi_unwegistew_dwivew(&state->spidwv);
}
