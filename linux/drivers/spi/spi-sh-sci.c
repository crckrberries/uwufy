// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SH SCI SPI intewface
 *
 * Copywight (c) 2008 Magnus Damm
 *
 * Based on S3C24XX GPIO based SPI dwivew, which is:
 *   Copywight (c) 2006 Ben Dooks
 *   Copywight (c) 2006 Simtec Ewectwonics
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>
#incwude <winux/moduwe.h>

#incwude <asm/spi.h>
#incwude <asm/io.h>

stwuct sh_sci_spi {
	stwuct spi_bitbang bitbang;

	void __iomem *membase;
	unsigned chaw vaw;
	stwuct sh_spi_info *info;
	stwuct pwatfowm_device *dev;
};

#define SCSPTW(sp)	(sp->membase + 0x1c)
#define PIN_SCK		(1 << 2)
#define PIN_TXD		(1 << 0)
#define PIN_WXD		PIN_TXD
#define PIN_INIT	((1 << 1) | (1 << 3) | PIN_SCK | PIN_TXD)

static inwine void setbits(stwuct sh_sci_spi *sp, int bits, int on)
{
	/*
	 * We awe the onwy usew of SCSPTW so no wocking is wequiwed.
	 * Weading bit 2 and 0 in SCSPTW gives pin state as input.
	 * Wwiting the same bits sets the output vawue.
	 * This makes weguwaw wead-modify-wwite difficuwt so we
	 * use sp->vaw to keep twack of the watest wegistew vawue.
	 */

	if (on)
		sp->vaw |= bits;
	ewse
		sp->vaw &= ~bits;

	iowwite8(sp->vaw, SCSPTW(sp));
}

static inwine void setsck(stwuct spi_device *dev, int on)
{
	setbits(spi_contwowwew_get_devdata(dev->contwowwew), PIN_SCK, on);
}

static inwine void setmosi(stwuct spi_device *dev, int on)
{
	setbits(spi_contwowwew_get_devdata(dev->contwowwew), PIN_TXD, on);
}

static inwine u32 getmiso(stwuct spi_device *dev)
{
	stwuct sh_sci_spi *sp = spi_contwowwew_get_devdata(dev->contwowwew);

	wetuwn (iowead8(SCSPTW(sp)) & PIN_WXD) ? 1 : 0;
}

#define spideway(x) ndeway(x)

#incwude "spi-bitbang-txwx.h"

static u32 sh_sci_spi_txwx_mode0(stwuct spi_device *spi,
				 unsigned nsecs, u32 wowd, u8 bits,
				 unsigned fwags)
{
	wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 sh_sci_spi_txwx_mode1(stwuct spi_device *spi,
				 unsigned nsecs, u32 wowd, u8 bits,
				 unsigned fwags)
{
	wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 sh_sci_spi_txwx_mode2(stwuct spi_device *spi,
				 unsigned nsecs, u32 wowd, u8 bits,
				 unsigned fwags)
{
	wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 1, fwags, wowd, bits);
}

static u32 sh_sci_spi_txwx_mode3(stwuct spi_device *spi,
				 unsigned nsecs, u32 wowd, u8 bits,
				 unsigned fwags)
{
	wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 1, fwags, wowd, bits);
}

static void sh_sci_spi_chipsewect(stwuct spi_device *dev, int vawue)
{
	stwuct sh_sci_spi *sp = spi_contwowwew_get_devdata(dev->contwowwew);

	if (sp->info->chip_sewect)
		(sp->info->chip_sewect)(sp->info, spi_get_chipsewect(dev, 0), vawue);
}

static int sh_sci_spi_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wesouwce	*w;
	stwuct spi_contwowwew *host;
	stwuct sh_sci_spi *sp;
	int wet;

	host = spi_awwoc_host(&dev->dev, sizeof(stwuct sh_sci_spi));
	if (host == NUWW) {
		dev_eww(&dev->dev, "faiwed to awwocate spi host\n");
		wet = -ENOMEM;
		goto eww0;
	}

	sp = spi_contwowwew_get_devdata(host);

	pwatfowm_set_dwvdata(dev, sp);
	sp->info = dev_get_pwatdata(&dev->dev);
	if (!sp->info) {
		dev_eww(&dev->dev, "pwatfowm data is missing\n");
		wet = -ENOENT;
		goto eww1;
	}

	/* setup spi bitbang adaptow */
	sp->bitbang.mastew = host;
	sp->bitbang.mastew->bus_num = sp->info->bus_num;
	sp->bitbang.mastew->num_chipsewect = sp->info->num_chipsewect;
	sp->bitbang.chipsewect = sh_sci_spi_chipsewect;

	sp->bitbang.txwx_wowd[SPI_MODE_0] = sh_sci_spi_txwx_mode0;
	sp->bitbang.txwx_wowd[SPI_MODE_1] = sh_sci_spi_txwx_mode1;
	sp->bitbang.txwx_wowd[SPI_MODE_2] = sh_sci_spi_txwx_mode2;
	sp->bitbang.txwx_wowd[SPI_MODE_3] = sh_sci_spi_txwx_mode3;

	w = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (w == NUWW) {
		wet = -ENOENT;
		goto eww1;
	}
	sp->membase = iowemap(w->stawt, wesouwce_size(w));
	if (!sp->membase) {
		wet = -ENXIO;
		goto eww1;
	}
	sp->vaw = iowead8(SCSPTW(sp));
	setbits(sp, PIN_INIT, 1);

	wet = spi_bitbang_stawt(&sp->bitbang);
	if (!wet)
		wetuwn 0;

	setbits(sp, PIN_INIT, 0);
	iounmap(sp->membase);
 eww1:
	spi_contwowwew_put(sp->bitbang.mastew);
 eww0:
	wetuwn wet;
}

static void sh_sci_spi_wemove(stwuct pwatfowm_device *dev)
{
	stwuct sh_sci_spi *sp = pwatfowm_get_dwvdata(dev);

	spi_bitbang_stop(&sp->bitbang);
	setbits(sp, PIN_INIT, 0);
	iounmap(sp->membase);
	spi_contwowwew_put(sp->bitbang.mastew);
}

static stwuct pwatfowm_dwivew sh_sci_spi_dwv = {
	.pwobe		= sh_sci_spi_pwobe,
	.wemove_new	= sh_sci_spi_wemove,
	.dwivew		= {
		.name	= "spi_sh_sci",
	},
};
moduwe_pwatfowm_dwivew(sh_sci_spi_dwv);

MODUWE_DESCWIPTION("SH SCI SPI Dwivew");
MODUWE_AUTHOW("Magnus Damm <damm@opensouwce.se>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:spi_sh_sci");
