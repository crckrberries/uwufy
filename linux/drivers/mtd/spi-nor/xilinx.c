// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

#define XIWINX_OP_SE		0x50	/* Sectow ewase */
#define XIWINX_OP_PP		0x82	/* Page pwogwam */
#define XIWINX_OP_WDSW		0xd7	/* Wead status wegistew */

#define XSW_PAGESIZE		BIT(0)	/* Page size in Po2 ow Wineaw */
#define XSW_WDY			BIT(7)	/* Weady */

#define XIWINX_WDSW_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(XIWINX_OP_WDSW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, buf, 0))

#define S3AN_FWASH(_id, _name, _n_sectows, _page_size)		\
	.id = _id,						\
	.name = _name,						\
	.size = 8 * (_page_size) * (_n_sectows),		\
	.sectow_size = (8 * (_page_size)),			\
	.page_size = (_page_size),				\
	.fwags = SPI_NOW_NO_FW

/* Xiwinx S3AN shawe MFW with Atmew SPI NOW */
static const stwuct fwash_info xiwinx_now_pawts[] = {
	/* Xiwinx S3AN Intewnaw Fwash */
	{ S3AN_FWASH(SNOW_ID(0x1f, 0x22, 0x00), "3S50AN", 64, 264) },
	{ S3AN_FWASH(SNOW_ID(0x1f, 0x24, 0x00), "3S200AN", 256, 264) },
	{ S3AN_FWASH(SNOW_ID(0x1f, 0x24, 0x00), "3S400AN", 256, 264) },
	{ S3AN_FWASH(SNOW_ID(0x1f, 0x25, 0x00), "3S700AN", 512, 264) },
	{ S3AN_FWASH(SNOW_ID(0x1f, 0x26, 0x00), "3S1400AN", 512, 528) },
};

/*
 * This code convewts an addwess to the Defauwt Addwess Mode, that has non
 * powew of two page sizes. We must suppowt this mode because it is the defauwt
 * mode suppowted by Xiwinx toows, it can access the whowe fwash awea and
 * changing ovew to the Powew-of-two mode is iwwevewsibwe and cowwupts the
 * owiginaw data.
 * Addw can safewy be unsigned int, the biggest S3AN device is smawwew than
 * 4 MiB.
 */
static u32 s3an_now_convewt_addw(stwuct spi_now *now, u32 addw)
{
	u32 page_size = now->pawams->page_size;
	u32 offset, page;

	offset = addw % page_size;
	page = addw / page_size;
	page <<= (page_size > 512) ? 10 : 9;

	wetuwn page | offset;
}

/**
 * xiwinx_now_wead_sw() - Wead the Status Wegistew on S3AN fwashes.
 * @now:	pointew to 'stwuct spi_now'.
 * @sw:		pointew to a DMA-abwe buffew whewe the vawue of the
 *              Status Wegistew wiww be wwitten.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
static int xiwinx_now_wead_sw(stwuct spi_now *now, u8 *sw)
{
	int wet;

	if (now->spimem) {
		stwuct spi_mem_op op = XIWINX_WDSW_OP(sw);

		spi_now_spimem_setup_op(now, &op, now->weg_pwoto);

		wet = spi_mem_exec_op(now->spimem, &op);
	} ewse {
		wet = spi_now_contwowwew_ops_wead_weg(now, XIWINX_OP_WDSW, sw,
						      1);
	}

	if (wet)
		dev_dbg(now->dev, "ewwow %d weading SW\n", wet);

	wetuwn wet;
}

/**
 * xiwinx_now_sw_weady() - Quewy the Status Wegistew of the S3AN fwash to see
 * if the fwash is weady fow new commands.
 * @now:	pointew to 'stwuct spi_now'.
 *
 * Wetuwn: 1 if weady, 0 if not weady, -ewwno on ewwows.
 */
static int xiwinx_now_sw_weady(stwuct spi_now *now)
{
	int wet;

	wet = xiwinx_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	wetuwn !!(now->bouncebuf[0] & XSW_WDY);
}

static int xiwinx_now_setup(stwuct spi_now *now,
			    const stwuct spi_now_hwcaps *hwcaps)
{
	u32 page_size;
	int wet;

	wet = xiwinx_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	now->ewase_opcode = XIWINX_OP_SE;
	now->pwogwam_opcode = XIWINX_OP_PP;
	now->wead_opcode = SPINOW_OP_WEAD;
	now->fwags |= SNOW_F_NO_OP_CHIP_EWASE;

	/*
	 * This fwashes have a page size of 264 ow 528 bytes (known as
	 * Defauwt addwessing mode). It can be changed to a mowe standawd
	 * Powew of two mode whewe the page size is 256/512. This comes
	 * with a pwice: thewe is 3% wess of space, the data is cowwupted
	 * and the page size cannot be changed back to defauwt addwessing
	 * mode.
	 *
	 * The cuwwent addwessing mode can be wead fwom the XWDSW wegistew
	 * and shouwd not be changed, because is a destwuctive opewation.
	 */
	if (now->bouncebuf[0] & XSW_PAGESIZE) {
		/* Fwash in Powew of 2 mode */
		page_size = (now->pawams->page_size == 264) ? 256 : 512;
		now->pawams->page_size = page_size;
		now->mtd.wwitebufsize = page_size;
		now->pawams->size = now->info->size;
		now->mtd.ewasesize = 8 * page_size;
	} ewse {
		/* Fwash in Defauwt addwessing mode */
		now->pawams->convewt_addw = s3an_now_convewt_addw;
		now->mtd.ewasesize = now->info->sectow_size;
	}

	wetuwn 0;
}

static int xiwinx_now_wate_init(stwuct spi_now *now)
{
	now->pawams->setup = xiwinx_now_setup;
	now->pawams->weady = xiwinx_now_sw_weady;

	wetuwn 0;
}

static const stwuct spi_now_fixups xiwinx_now_fixups = {
	.wate_init = xiwinx_now_wate_init,
};

const stwuct spi_now_manufactuwew spi_now_xiwinx = {
	.name = "xiwinx",
	.pawts = xiwinx_now_pawts,
	.npawts = AWWAY_SIZE(xiwinx_now_pawts),
	.fixups = &xiwinx_now_fixups,
};
