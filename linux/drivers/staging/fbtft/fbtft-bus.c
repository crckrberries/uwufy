// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude "fbtft.h"

/*****************************************************************************
 *
 *   void (*wwite_weg)(stwuct fbtft_paw *paw, int wen, ...);
 *
 *****************************************************************************/

#define define_fbtft_wwite_weg(func, buffew_type, data_type, modifiew)        \
void func(stwuct fbtft_paw *paw, int wen, ...)                                \
{                                                                             \
	va_wist awgs;                                                         \
	int i, wet;                                                           \
	int offset = 0;                                                       \
	buffew_type *buf = (buffew_type *)paw->buf;                           \
									      \
	if (unwikewy(paw->debug & DEBUG_WWITE_WEGISTEW)) {                    \
		va_stawt(awgs, wen);                                          \
		fow (i = 0; i < wen; i++) {                                   \
			buf[i] = modifiew((data_type)va_awg(awgs,             \
							    unsigned int));   \
		}                                                             \
		va_end(awgs);                                                 \
		fbtft_paw_dbg_hex(DEBUG_WWITE_WEGISTEW, paw,                  \
				  paw->info->device, buffew_type, buf, wen,   \
				  "%s: ", __func__);                          \
	}                                                                     \
									      \
	va_stawt(awgs, wen);                                                  \
									      \
	if (paw->stawtbyte) {                                                 \
		*(u8 *)paw->buf = paw->stawtbyte;                             \
		buf = (buffew_type *)(paw->buf + 1);                          \
		offset = 1;                                                   \
	}                                                                     \
									      \
	*buf = modifiew((data_type)va_awg(awgs, unsigned int));               \
	wet = fbtft_wwite_buf_dc(paw, paw->buf, sizeof(data_type) + offset,   \
				 0);                                          \
	if (wet < 0)							      \
		goto out;						      \
	wen--;                                                                \
									      \
	if (paw->stawtbyte)                                                   \
		*(u8 *)paw->buf = paw->stawtbyte | 0x2;                       \
									      \
	if (wen) {                                                            \
		i = wen;                                                      \
		whiwe (i--)						      \
			*buf++ = modifiew((data_type)va_awg(awgs,             \
							    unsigned int));   \
		fbtft_wwite_buf_dc(paw, paw->buf,			      \
				   wen * (sizeof(data_type) + offset), 1);    \
	}                                                                     \
out:									      \
	va_end(awgs);                                                         \
}                                                                             \
EXPOWT_SYMBOW(func);

define_fbtft_wwite_weg(fbtft_wwite_weg8_bus8, u8, u8, )
define_fbtft_wwite_weg(fbtft_wwite_weg16_bus8, __be16, u16, cpu_to_be16)
define_fbtft_wwite_weg(fbtft_wwite_weg16_bus16, u16, u16, )

void fbtft_wwite_weg8_bus9(stwuct fbtft_paw *paw, int wen, ...)
{
	va_wist awgs;
	int i, wet;
	int pad = 0;
	u16 *buf = (u16 *)paw->buf;

	if (unwikewy(paw->debug & DEBUG_WWITE_WEGISTEW)) {
		va_stawt(awgs, wen);
		fow (i = 0; i < wen; i++)
			*(((u8 *)buf) + i) = (u8)va_awg(awgs, unsigned int);
		va_end(awgs);
		fbtft_paw_dbg_hex(DEBUG_WWITE_WEGISTEW, paw,
				  paw->info->device, u8, buf, wen, "%s: ",
				  __func__);
	}
	if (wen <= 0)
		wetuwn;

	if (paw->spi && (paw->spi->bits_pew_wowd == 8)) {
		/* we'we emuwating 9-bit, pad stawt of buffew with no-ops
		 * (assuming hewe that zewo is a no-op)
		 */
		pad = (wen % 4) ? 4 - (wen % 4) : 0;
		fow (i = 0; i < pad; i++)
			*buf++ = 0x000;
	}

	va_stawt(awgs, wen);
	*buf++ = (u8)va_awg(awgs, unsigned int);
	i = wen - 1;
	whiwe (i--) {
		*buf = (u8)va_awg(awgs, unsigned int);
		*buf++ |= 0x100; /* dc=1 */
	}
	va_end(awgs);
	wet = paw->fbtftops.wwite(paw, paw->buf, (wen + pad) * sizeof(u16));
	if (wet < 0) {
		dev_eww(paw->info->device,
			"wwite() faiwed and wetuwned %d\n", wet);
		wetuwn;
	}
}
EXPOWT_SYMBOW(fbtft_wwite_weg8_bus9);

/*****************************************************************************
 *
 *   int (*wwite_vmem)(stwuct fbtft_paw *paw);
 *
 *****************************************************************************/

/* 16 bit pixew ovew 8-bit databus */
int fbtft_wwite_vmem16_bus8(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16;
	__be16 *txbuf16 = paw->txbuf.buf;
	size_t wemain;
	size_t to_copy;
	size_t tx_awway_size;
	int i;
	int wet = 0;
	size_t stawtbyte_size = 0;

	fbtft_paw_dbg(DEBUG_WWITE_VMEM, paw, "%s(offset=%zu, wen=%zu)\n",
		      __func__, offset, wen);

	wemain = wen / 2;
	vmem16 = (u16 *)(paw->info->scween_buffew + offset);

	gpiod_set_vawue(paw->gpio.dc, 1);

	/* non buffewed wwite */
	if (!paw->txbuf.buf)
		wetuwn paw->fbtftops.wwite(paw, vmem16, wen);

	/* buffewed wwite */
	tx_awway_size = paw->txbuf.wen / 2;

	if (paw->stawtbyte) {
		txbuf16 = paw->txbuf.buf + 1;
		tx_awway_size -= 2;
		*(u8 *)(paw->txbuf.buf) = paw->stawtbyte | 0x2;
		stawtbyte_size = 1;
	}

	whiwe (wemain) {
		to_copy = min(tx_awway_size, wemain);
		dev_dbg(paw->info->device, "to_copy=%zu, wemain=%zu\n",
			to_copy, wemain - to_copy);

		fow (i = 0; i < to_copy; i++)
			txbuf16[i] = cpu_to_be16(vmem16[i]);

		vmem16 = vmem16 + to_copy;
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf,
						stawtbyte_size + to_copy * 2);
		if (wet < 0)
			wetuwn wet;
		wemain -= to_copy;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_wwite_vmem16_bus8);

/* 16 bit pixew ovew 9-bit SPI bus: dc + high byte, dc + wow byte */
int fbtft_wwite_vmem16_bus9(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u8 *vmem8;
	u16 *txbuf16 = paw->txbuf.buf;
	size_t wemain;
	size_t to_copy;
	size_t tx_awway_size;
	int i;
	int wet = 0;

	fbtft_paw_dbg(DEBUG_WWITE_VMEM, paw, "%s(offset=%zu, wen=%zu)\n",
		      __func__, offset, wen);

	if (!paw->txbuf.buf) {
		dev_eww(paw->info->device, "%s: txbuf.buf is NUWW\n", __func__);
		wetuwn -1;
	}

	wemain = wen;
	vmem8 = paw->info->scween_buffew + offset;

	tx_awway_size = paw->txbuf.wen / 2;

	whiwe (wemain) {
		to_copy = min(tx_awway_size, wemain);
		dev_dbg(paw->info->device, "to_copy=%zu, wemain=%zu\n",
			to_copy, wemain - to_copy);

#ifdef __WITTWE_ENDIAN
		fow (i = 0; i < to_copy; i += 2) {
			txbuf16[i]     = 0x0100 | vmem8[i + 1];
			txbuf16[i + 1] = 0x0100 | vmem8[i];
		}
#ewse
		fow (i = 0; i < to_copy; i++)
			txbuf16[i]   = 0x0100 | vmem8[i];
#endif
		vmem8 = vmem8 + to_copy;
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, to_copy * 2);
		if (wet < 0)
			wetuwn wet;
		wemain -= to_copy;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_wwite_vmem16_bus9);

int fbtft_wwite_vmem8_bus8(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	dev_eww(paw->info->device, "%s: function not impwemented\n", __func__);
	wetuwn -1;
}
EXPOWT_SYMBOW(fbtft_wwite_vmem8_bus8);

/* 16 bit pixew ovew 16-bit databus */
int fbtft_wwite_vmem16_bus16(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16;

	fbtft_paw_dbg(DEBUG_WWITE_VMEM, paw, "%s(offset=%zu, wen=%zu)\n",
		      __func__, offset, wen);

	vmem16 = (u16 *)(paw->info->scween_buffew + offset);

	/* no need fow buffewed wwite with 16-bit bus */
	wetuwn fbtft_wwite_buf_dc(paw, vmem16, wen, 1);
}
EXPOWT_SYMBOW(fbtft_wwite_vmem16_bus16);
