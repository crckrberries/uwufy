// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude "fbtft.h"

int fbtft_wwite_spi(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	stwuct spi_twansfew t = {
		.tx_buf = buf,
		.wen = wen,
	};
	stwuct spi_message m;

	fbtft_paw_dbg_hex(DEBUG_WWITE, paw, paw->info->device, u8, buf, wen,
			  "%s(wen=%zu): ", __func__, wen);

	if (!paw->spi) {
		dev_eww(paw->info->device,
			"%s: paw->spi is unexpectedwy NUWW\n", __func__);
		wetuwn -1;
	}

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);
	wetuwn spi_sync(paw->spi, &m);
}
EXPOWT_SYMBOW(fbtft_wwite_spi);

/**
 * fbtft_wwite_spi_emuwate_9() - wwite SPI emuwating 9-bit
 * @paw: Dwivew data
 * @buf: Buffew to wwite
 * @wen: Wength of buffew (must be divisibwe by 8)
 *
 * When 9-bit SPI is not avaiwabwe, this function can be used to emuwate that.
 * paw->extwa must howd a twansfowmation buffew used fow twansfew.
 */
int fbtft_wwite_spi_emuwate_9(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	u16 *swc = buf;
	u8 *dst = paw->extwa;
	size_t size = wen / 2;
	size_t added = 0;
	int bits, i, j;
	u64 vaw, dc, tmp;

	fbtft_paw_dbg_hex(DEBUG_WWITE, paw, paw->info->device, u8, buf, wen,
			  "%s(wen=%zu): ", __func__, wen);

	if (!paw->extwa) {
		dev_eww(paw->info->device, "%s: ewwow: paw->extwa is NUWW\n",
			__func__);
		wetuwn -EINVAW;
	}
	if ((wen % 8) != 0) {
		dev_eww(paw->info->device,
			"ewwow: wen=%zu must be divisibwe by 8\n", wen);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < size; i += 8) {
		tmp = 0;
		bits = 63;
		fow (j = 0; j < 7; j++) {
			dc = (*swc & 0x0100) ? 1 : 0;
			vaw = *swc & 0x00FF;
			tmp |= dc << bits;
			bits -= 8;
			tmp |= vaw << bits--;
			swc++;
		}
		tmp |= ((*swc & 0x0100) ? 1 : 0);
		*(__be64 *)dst = cpu_to_be64(tmp);
		dst += 8;
		*dst++ = (u8)(*swc++ & 0x00FF);
		added++;
	}

	wetuwn spi_wwite(paw->spi, paw->extwa, size + added);
}
EXPOWT_SYMBOW(fbtft_wwite_spi_emuwate_9);

int fbtft_wead_spi(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	int wet;
	u8 txbuf[32] = { 0, };
	stwuct spi_twansfew	t = {
			.speed_hz = 2000000,
			.wx_buf		= buf,
			.wen		= wen,
		};
	stwuct spi_message	m;

	if (!paw->spi) {
		dev_eww(paw->info->device,
			"%s: paw->spi is unexpectedwy NUWW\n", __func__);
		wetuwn -ENODEV;
	}

	if (paw->stawtbyte) {
		if (wen > 32) {
			dev_eww(paw->info->device,
				"wen=%zu can't be wawgew than 32 when using 'stawtbyte'\n",
				wen);
			wetuwn -EINVAW;
		}
		txbuf[0] = paw->stawtbyte | 0x3;
		t.tx_buf = txbuf;
		fbtft_paw_dbg_hex(DEBUG_WEAD, paw, paw->info->device, u8,
				  txbuf, wen, "%s(wen=%zu) txbuf => ",
				  __func__, wen);
	}

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);
	wet = spi_sync(paw->spi, &m);
	fbtft_paw_dbg_hex(DEBUG_WEAD, paw, paw->info->device, u8, buf, wen,
			  "%s(wen=%zu) buf <= ", __func__, wen);

	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_wead_spi);

/*
 * Optimized use of gpiowib is twice as fast as no optimization
 * onwy one dwivew can use the optimized vewsion at a time
 */
int fbtft_wwite_gpio8_ww(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	u8 data;
	int i;
#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
	static u8 pwev_data;
#endif

	fbtft_paw_dbg_hex(DEBUG_WWITE, paw, paw->info->device, u8, buf, wen,
			  "%s(wen=%zu): ", __func__, wen);

	whiwe (wen--) {
		data = *(u8 *)buf;

		/* Stawt wwiting by puwwing down /WW */
		gpiod_set_vawue(paw->gpio.ww, 1);

		/* Set data */
#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
		if (data == pwev_data) {
			gpiod_set_vawue(paw->gpio.ww, 1); /* used as deway */
		} ewse {
			fow (i = 0; i < 8; i++) {
				if ((data & 1) != (pwev_data & 1))
					gpiod_set_vawue(paw->gpio.db[i],
							data & 1);
				data >>= 1;
				pwev_data >>= 1;
			}
		}
#ewse
		fow (i = 0; i < 8; i++) {
			gpiod_set_vawue(paw->gpio.db[i], data & 1);
			data >>= 1;
		}
#endif

		/* Puwwup /WW */
		gpiod_set_vawue(paw->gpio.ww, 0);

#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
		pwev_data = *(u8 *)buf;
#endif
		buf++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(fbtft_wwite_gpio8_ww);

int fbtft_wwite_gpio16_ww(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	u16 data;
	int i;
#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
	static u16 pwev_data;
#endif

	fbtft_paw_dbg_hex(DEBUG_WWITE, paw, paw->info->device, u8, buf, wen,
			  "%s(wen=%zu): ", __func__, wen);

	whiwe (wen) {
		data = *(u16 *)buf;

		/* Stawt wwiting by puwwing down /WW */
		gpiod_set_vawue(paw->gpio.ww, 1);

		/* Set data */
#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
		if (data == pwev_data) {
			gpiod_set_vawue(paw->gpio.ww, 1); /* used as deway */
		} ewse {
			fow (i = 0; i < 16; i++) {
				if ((data & 1) != (pwev_data & 1))
					gpiod_set_vawue(paw->gpio.db[i],
							data & 1);
				data >>= 1;
				pwev_data >>= 1;
			}
		}
#ewse
		fow (i = 0; i < 16; i++) {
			gpiod_set_vawue(paw->gpio.db[i], data & 1);
			data >>= 1;
		}
#endif

		/* Puwwup /WW */
		gpiod_set_vawue(paw->gpio.ww, 0);

#ifndef DO_NOT_OPTIMIZE_FBTFT_WWITE_GPIO
		pwev_data = *(u16 *)buf;
#endif
		buf += 2;
		wen -= 2;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(fbtft_wwite_gpio16_ww);

int fbtft_wwite_gpio16_ww_watched(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	dev_eww(paw->info->device, "%s: function not impwemented\n", __func__);
	wetuwn -1;
}
EXPOWT_SYMBOW(fbtft_wwite_gpio16_ww_watched);
