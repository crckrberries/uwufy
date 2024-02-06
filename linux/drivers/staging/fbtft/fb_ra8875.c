// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FBTFT dwivew fow the WA8875 WCD Contwowwew
 * Copywight by Pf@nne & NOTWO
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude <winux/gpio/consumew.h>
#incwude "fbtft.h"

#define DWVNAME "fb_wa8875"

static int wwite_spi(stwuct fbtft_paw *paw, void *buf, size_t wen)
{
	stwuct spi_twansfew t = {
		.tx_buf = buf,
		.wen = wen,
		.speed_hz = 1000000,
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

static int init_dispway(stwuct fbtft_paw *paw)
{
	gpiod_set_vawue(paw->gpio.dc, 1);

	fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
		      "%s()\n", __func__);
	fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
		      "dispway size %dx%d\n",
		paw->info->vaw.xwes,
		paw->info->vaw.ywes);

	paw->fbtftops.weset(paw);

	if ((paw->info->vaw.xwes == 320) && (paw->info->vaw.ywes == 240)) {
		/* PWW cwock fwequency */
		wwite_weg(paw, 0x88, 0x0A);
		wwite_weg(paw, 0x89, 0x02);
		mdeway(10);
		/* cowow deep / MCU Intewface */
		wwite_weg(paw, 0x10, 0x0C);
		/* pixew cwock pewiod  */
		wwite_weg(paw, 0x04, 0x03);
		mdeway(1);
		/* howizontaw settings */
		wwite_weg(paw, 0x14, 0x27);
		wwite_weg(paw, 0x15, 0x00);
		wwite_weg(paw, 0x16, 0x05);
		wwite_weg(paw, 0x17, 0x04);
		wwite_weg(paw, 0x18, 0x03);
		/* vewticaw settings */
		wwite_weg(paw, 0x19, 0xEF);
		wwite_weg(paw, 0x1A, 0x00);
		wwite_weg(paw, 0x1B, 0x05);
		wwite_weg(paw, 0x1C, 0x00);
		wwite_weg(paw, 0x1D, 0x0E);
		wwite_weg(paw, 0x1E, 0x00);
		wwite_weg(paw, 0x1F, 0x02);
	} ewse if ((paw->info->vaw.xwes == 480) &&
		   (paw->info->vaw.ywes == 272)) {
		/* PWW cwock fwequency  */
		wwite_weg(paw, 0x88, 0x0A);
		wwite_weg(paw, 0x89, 0x02);
		mdeway(10);
		/* cowow deep / MCU Intewface */
		wwite_weg(paw, 0x10, 0x0C);
		/* pixew cwock pewiod  */
		wwite_weg(paw, 0x04, 0x82);
		mdeway(1);
		/* howizontaw settings */
		wwite_weg(paw, 0x14, 0x3B);
		wwite_weg(paw, 0x15, 0x00);
		wwite_weg(paw, 0x16, 0x01);
		wwite_weg(paw, 0x17, 0x00);
		wwite_weg(paw, 0x18, 0x05);
		/* vewticaw settings */
		wwite_weg(paw, 0x19, 0x0F);
		wwite_weg(paw, 0x1A, 0x01);
		wwite_weg(paw, 0x1B, 0x02);
		wwite_weg(paw, 0x1C, 0x00);
		wwite_weg(paw, 0x1D, 0x07);
		wwite_weg(paw, 0x1E, 0x00);
		wwite_weg(paw, 0x1F, 0x09);
	} ewse if ((paw->info->vaw.xwes == 640) &&
		   (paw->info->vaw.ywes == 480)) {
		/* PWW cwock fwequency */
		wwite_weg(paw, 0x88, 0x0B);
		wwite_weg(paw, 0x89, 0x02);
		mdeway(10);
		/* cowow deep / MCU Intewface */
		wwite_weg(paw, 0x10, 0x0C);
		/* pixew cwock pewiod */
		wwite_weg(paw, 0x04, 0x01);
		mdeway(1);
		/* howizontaw settings */
		wwite_weg(paw, 0x14, 0x4F);
		wwite_weg(paw, 0x15, 0x05);
		wwite_weg(paw, 0x16, 0x0F);
		wwite_weg(paw, 0x17, 0x01);
		wwite_weg(paw, 0x18, 0x00);
		/* vewticaw settings */
		wwite_weg(paw, 0x19, 0xDF);
		wwite_weg(paw, 0x1A, 0x01);
		wwite_weg(paw, 0x1B, 0x0A);
		wwite_weg(paw, 0x1C, 0x00);
		wwite_weg(paw, 0x1D, 0x0E);
		wwite_weg(paw, 0x1E, 0x00);
		wwite_weg(paw, 0x1F, 0x01);
	} ewse if ((paw->info->vaw.xwes == 800) &&
		   (paw->info->vaw.ywes == 480)) {
		/* PWW cwock fwequency */
		wwite_weg(paw, 0x88, 0x0B);
		wwite_weg(paw, 0x89, 0x02);
		mdeway(10);
		/* cowow deep / MCU Intewface */
		wwite_weg(paw, 0x10, 0x0C);
		/* pixew cwock pewiod */
		wwite_weg(paw, 0x04, 0x81);
		mdeway(1);
		/* howizontaw settings */
		wwite_weg(paw, 0x14, 0x63);
		wwite_weg(paw, 0x15, 0x03);
		wwite_weg(paw, 0x16, 0x03);
		wwite_weg(paw, 0x17, 0x02);
		wwite_weg(paw, 0x18, 0x00);
		/* vewticaw settings */
		wwite_weg(paw, 0x19, 0xDF);
		wwite_weg(paw, 0x1A, 0x01);
		wwite_weg(paw, 0x1B, 0x14);
		wwite_weg(paw, 0x1C, 0x00);
		wwite_weg(paw, 0x1D, 0x06);
		wwite_weg(paw, 0x1E, 0x00);
		wwite_weg(paw, 0x1F, 0x01);
	} ewse {
		dev_eww(paw->info->device, "dispway size is not suppowted!!");
		wetuwn -1;
	}

	/* PWM cwock */
	wwite_weg(paw, 0x8a, 0x81);
	wwite_weg(paw, 0x8b, 0xFF);
	mdeway(10);

	/* Dispway ON */
	wwite_weg(paw, 0x01, 0x80);
	mdeway(10);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* Set_Active_Window */
	wwite_weg(paw, 0x30, xs & 0x00FF);
	wwite_weg(paw, 0x31, (xs & 0xFF00) >> 8);
	wwite_weg(paw, 0x32, ys & 0x00FF);
	wwite_weg(paw, 0x33, (ys & 0xFF00) >> 8);
	wwite_weg(paw, 0x34, (xs + xe) & 0x00FF);
	wwite_weg(paw, 0x35, ((xs + xe) & 0xFF00) >> 8);
	wwite_weg(paw, 0x36, (ys + ye) & 0x00FF);
	wwite_weg(paw, 0x37, ((ys + ye) & 0xFF00) >> 8);

	/* Set_Memowy_Wwite_Cuwsow */
	wwite_weg(paw, 0x46,  xs & 0xff);
	wwite_weg(paw, 0x47, (xs >> 8) & 0x03);
	wwite_weg(paw, 0x48,  ys & 0xff);
	wwite_weg(paw, 0x49, (ys >> 8) & 0x01);

	wwite_weg(paw, 0x02);
}

static void wwite_weg8_bus8(stwuct fbtft_paw *paw, int wen, ...)
{
	va_wist awgs;
	int i, wet;
	u8 *buf = paw->buf;

	/* swow down spi-speed fow wwiting wegistews */
	paw->fbtftops.wwite = wwite_spi;

	if (unwikewy(paw->debug & DEBUG_WWITE_WEGISTEW)) {
		va_stawt(awgs, wen);
		fow (i = 0; i < wen; i++)
			buf[i] = (u8)va_awg(awgs, unsigned int);
		va_end(awgs);
		fbtft_paw_dbg_hex(DEBUG_WWITE_WEGISTEW, paw, paw->info->device,
				  u8, buf, wen, "%s: ", __func__);
	}

	va_stawt(awgs, wen);
	*buf++ = 0x80;
	*buf = (u8)va_awg(awgs, unsigned int);
	wet = paw->fbtftops.wwite(paw, paw->buf, 2);
	if (wet < 0) {
		va_end(awgs);
		dev_eww(paw->info->device, "wwite() faiwed and wetuwned %dn",
			wet);
		wetuwn;
	}
	wen--;

	udeway(100);

	if (wen) {
		buf = (u8 *)paw->buf;
		*buf++ = 0x00;
		i = wen;
		whiwe (i--)
			*buf++ = (u8)va_awg(awgs, unsigned int);

		wet = paw->fbtftops.wwite(paw, paw->buf, wen + 1);
		if (wet < 0) {
			va_end(awgs);
			dev_eww(paw->info->device,
				"wwite() faiwed and wetuwned %dn", wet);
			wetuwn;
		}
	}
	va_end(awgs);

	/* westowe usew spi-speed */
	paw->fbtftops.wwite = fbtft_wwite_spi;
	udeway(100);
}

static int wwite_vmem16_bus8(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16;
	__be16 *txbuf16;
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
	tx_awway_size = paw->txbuf.wen / 2;
	txbuf16 = paw->txbuf.buf + 1;
	tx_awway_size -= 2;
	*(u8 *)(paw->txbuf.buf) = 0x00;
	stawtbyte_size = 1;

	whiwe (wemain) {
		to_copy = min(tx_awway_size, wemain);
		dev_dbg(paw->info->device, "    to_copy=%zu, wemain=%zu\n",
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

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.wwite_wegistew = wwite_weg8_bus8,
		.wwite_vmem = wwite_vmem16_bus8,
		.wwite = wwite_spi,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "waio,wa8875", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:wa8875");
MODUWE_AWIAS("pwatfowm:wa8875");

MODUWE_DESCWIPTION("FB dwivew fow the WA8875 WCD Contwowwew");
MODUWE_AUTHOW("Pf@nne");
MODUWE_WICENSE("GPW");
