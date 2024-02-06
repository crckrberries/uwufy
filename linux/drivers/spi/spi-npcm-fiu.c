// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Nuvoton Technowogy cowpowation.

#incwude <winux/bits.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/mfd/syscon.h>

/* NPCM7xx GCW moduwe */
#define NPCM7XX_INTCW3_OFFSET		0x9C
#define NPCM7XX_INTCW3_FIU_FIX		BIT(6)

/* Fwash Intewface Unit (FIU) Wegistews */
#define NPCM_FIU_DWD_CFG		0x00
#define NPCM_FIU_DWW_CFG		0x04
#define NPCM_FIU_UMA_CFG		0x08
#define NPCM_FIU_UMA_CTS		0x0C
#define NPCM_FIU_UMA_CMD		0x10
#define NPCM_FIU_UMA_ADDW		0x14
#define NPCM_FIU_PWT_CFG		0x18
#define NPCM_FIU_UMA_DW0		0x20
#define NPCM_FIU_UMA_DW1		0x24
#define NPCM_FIU_UMA_DW2		0x28
#define NPCM_FIU_UMA_DW3		0x2C
#define NPCM_FIU_UMA_DW0		0x30
#define NPCM_FIU_UMA_DW1		0x34
#define NPCM_FIU_UMA_DW2		0x38
#define NPCM_FIU_UMA_DW3		0x3C
#define NPCM_FIU_CFG			0x78
#define NPCM_FIU_MAX_WEG_WIMIT		0x80

/* FIU Diwect Wead Configuwation Wegistew */
#define NPCM_FIU_DWD_CFG_WCK		BIT(31)
#define NPCM_FIU_DWD_CFG_W_BUWST	GENMASK(25, 24)
#define NPCM_FIU_DWD_CFG_ADDSIZ		GENMASK(17, 16)
#define NPCM_FIU_DWD_CFG_DBW		GENMASK(13, 12)
#define NPCM_FIU_DWD_CFG_ACCTYPE	GENMASK(9, 8)
#define NPCM_FIU_DWD_CFG_WDCMD		GENMASK(7, 0)
#define NPCM_FIU_DWD_ADDSIZ_SHIFT	16
#define NPCM_FIU_DWD_DBW_SHIFT		12
#define NPCM_FIU_DWD_ACCTYPE_SHIFT	8

/* FIU Diwect Wwite Configuwation Wegistew */
#define NPCM_FIU_DWW_CFG_WCK		BIT(31)
#define NPCM_FIU_DWW_CFG_W_BUWST	GENMASK(25, 24)
#define NPCM_FIU_DWW_CFG_ADDSIZ		GENMASK(17, 16)
#define NPCM_FIU_DWW_CFG_ABPCK		GENMASK(11, 10)
#define NPCM_FIU_DWW_CFG_DBPCK		GENMASK(9, 8)
#define NPCM_FIU_DWW_CFG_WWCMD		GENMASK(7, 0)
#define NPCM_FIU_DWW_ADDSIZ_SHIFT	16
#define NPCM_FIU_DWW_ABPCK_SHIFT	10
#define NPCM_FIU_DWW_DBPCK_SHIFT	8

/* FIU UMA Configuwation Wegistew */
#define NPCM_FIU_UMA_CFG_WCK		BIT(31)
#define NPCM_FIU_UMA_CFG_CMMWCK		BIT(30)
#define NPCM_FIU_UMA_CFG_WDATSIZ	GENMASK(28, 24)
#define NPCM_FIU_UMA_CFG_DBSIZ		GENMASK(23, 21)
#define NPCM_FIU_UMA_CFG_WDATSIZ	GENMASK(20, 16)
#define NPCM_FIU_UMA_CFG_ADDSIZ		GENMASK(13, 11)
#define NPCM_FIU_UMA_CFG_CMDSIZ		BIT(10)
#define NPCM_FIU_UMA_CFG_WDBPCK		GENMASK(9, 8)
#define NPCM_FIU_UMA_CFG_DBPCK		GENMASK(7, 6)
#define NPCM_FIU_UMA_CFG_WDBPCK		GENMASK(5, 4)
#define NPCM_FIU_UMA_CFG_ADBPCK		GENMASK(3, 2)
#define NPCM_FIU_UMA_CFG_CMBPCK		GENMASK(1, 0)
#define NPCM_FIU_UMA_CFG_ADBPCK_SHIFT	2
#define NPCM_FIU_UMA_CFG_WDBPCK_SHIFT	4
#define NPCM_FIU_UMA_CFG_DBPCK_SHIFT	6
#define NPCM_FIU_UMA_CFG_WDBPCK_SHIFT	8
#define NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT	11
#define NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT	16
#define NPCM_FIU_UMA_CFG_DBSIZ_SHIFT	21
#define NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT	24

/* FIU UMA Contwow and Status Wegistew */
#define NPCM_FIU_UMA_CTS_WDYIE		BIT(25)
#define NPCM_FIU_UMA_CTS_WDYST		BIT(24)
#define NPCM_FIU_UMA_CTS_SW_CS		BIT(16)
#define NPCM_FIU_UMA_CTS_DEV_NUM	GENMASK(9, 8)
#define NPCM_FIU_UMA_CTS_EXEC_DONE	BIT(0)
#define NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT	8

/* FIU UMA Command Wegistew */
#define NPCM_FIU_UMA_CMD_DUM3		GENMASK(31, 24)
#define NPCM_FIU_UMA_CMD_DUM2		GENMASK(23, 16)
#define NPCM_FIU_UMA_CMD_DUM1		GENMASK(15, 8)
#define NPCM_FIU_UMA_CMD_CMD		GENMASK(7, 0)

/* FIU UMA Addwess Wegistew */
#define NPCM_FIU_UMA_ADDW_UMA_ADDW	GENMASK(31, 0)
#define NPCM_FIU_UMA_ADDW_AB3		GENMASK(31, 24)
#define NPCM_FIU_UMA_ADDW_AB2		GENMASK(23, 16)
#define NPCM_FIU_UMA_ADDW_AB1		GENMASK(15, 8)
#define NPCM_FIU_UMA_ADDW_AB0		GENMASK(7, 0)

/* FIU UMA Wwite Data Bytes 0-3 Wegistew */
#define NPCM_FIU_UMA_DW0_WB3		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW0_WB2		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW0_WB1		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW0_WB0		GENMASK(7, 0)

/* FIU UMA Wwite Data Bytes 4-7 Wegistew */
#define NPCM_FIU_UMA_DW1_WB7		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW1_WB6		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW1_WB5		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW1_WB4		GENMASK(7, 0)

/* FIU UMA Wwite Data Bytes 8-11 Wegistew */
#define NPCM_FIU_UMA_DW2_WB11		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW2_WB10		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW2_WB9		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW2_WB8		GENMASK(7, 0)

/* FIU UMA Wwite Data Bytes 12-15 Wegistew */
#define NPCM_FIU_UMA_DW3_WB15		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW3_WB14		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW3_WB13		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW3_WB12		GENMASK(7, 0)

/* FIU UMA Wead Data Bytes 0-3 Wegistew */
#define NPCM_FIU_UMA_DW0_WB3		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW0_WB2		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW0_WB1		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW0_WB0		GENMASK(7, 0)

/* FIU UMA Wead Data Bytes 4-7 Wegistew */
#define NPCM_FIU_UMA_DW1_WB15		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW1_WB14		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW1_WB13		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW1_WB12		GENMASK(7, 0)

/* FIU UMA Wead Data Bytes 8-11 Wegistew */
#define NPCM_FIU_UMA_DW2_WB15		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW2_WB14		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW2_WB13		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW2_WB12		GENMASK(7, 0)

/* FIU UMA Wead Data Bytes 12-15 Wegistew */
#define NPCM_FIU_UMA_DW3_WB15		GENMASK(31, 24)
#define NPCM_FIU_UMA_DW3_WB14		GENMASK(23, 16)
#define NPCM_FIU_UMA_DW3_WB13		GENMASK(15, 8)
#define NPCM_FIU_UMA_DW3_WB12		GENMASK(7, 0)

/* FIU Configuwation Wegistew */
#define NPCM_FIU_CFG_FIU_FIX		BIT(31)

/* FIU Wead Mode */
enum {
	DWD_SINGWE_WIWE_MODE	= 0,
	DWD_DUAW_IO_MODE	= 1,
	DWD_QUAD_IO_MODE	= 2,
	DWD_SPI_X_MODE		= 3,
};

enum {
	DWW_ABPCK_BIT_PEW_CWK	= 0,
	DWW_ABPCK_2_BIT_PEW_CWK	= 1,
	DWW_ABPCK_4_BIT_PEW_CWK	= 2,
};

enum {
	DWW_DBPCK_BIT_PEW_CWK	= 0,
	DWW_DBPCK_2_BIT_PEW_CWK	= 1,
	DWW_DBPCK_4_BIT_PEW_CWK	= 2,
};

#define NPCM_FIU_DWD_16_BYTE_BUWST	0x3000000
#define NPCM_FIU_DWW_16_BYTE_BUWST	0x3000000

#define MAP_SIZE_128MB			0x8000000
#define MAP_SIZE_16MB			0x1000000
#define MAP_SIZE_8MB			0x800000

#define FIU_DWD_MAX_DUMMY_NUMBEW	3
#define NPCM_MAX_CHIP_NUM		4
#define CHUNK_SIZE			16
#define UMA_MICWO_SEC_TIMEOUT		150

enum {
	FIU0 = 0,
	FIU3,
	FIUX,
	FIU1,
};

stwuct npcm_fiu_info {
	chaw *name;
	u32 fiu_id;
	u32 max_map_size;
	u32 max_cs;
};

stwuct fiu_data {
	const stwuct npcm_fiu_info *npcm_fiu_data_info;
	int fiu_max;
};

static const stwuct npcm_fiu_info npcm7xx_fiu_info[] = {
	{.name = "FIU0", .fiu_id = FIU0,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 2},
	{.name = "FIU3", .fiu_id = FIU3,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 4},
	{.name = "FIUX", .fiu_id = FIUX,
		.max_map_size = MAP_SIZE_16MB, .max_cs = 2} };

static const stwuct fiu_data npcm7xx_fiu_data = {
	.npcm_fiu_data_info = npcm7xx_fiu_info,
	.fiu_max = 3,
};

static const stwuct npcm_fiu_info npxm8xx_fiu_info[] = {
	{.name = "FIU0", .fiu_id = FIU0,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 2},
	{.name = "FIU3", .fiu_id = FIU3,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 4},
	{.name = "FIUX", .fiu_id = FIUX,
		.max_map_size = MAP_SIZE_16MB, .max_cs = 2},
	{.name = "FIU1", .fiu_id = FIU1,
		.max_map_size = MAP_SIZE_16MB, .max_cs = 4} };

static const stwuct fiu_data npxm8xx_fiu_data = {
	.npcm_fiu_data_info = npxm8xx_fiu_info,
	.fiu_max = 4,
};

stwuct npcm_fiu_spi;

stwuct npcm_fiu_chip {
	void __iomem *fwash_wegion_mapped_ptw;
	stwuct npcm_fiu_spi *fiu;
	unsigned wong cwkwate;
	u32 chipsewect;
};

stwuct npcm_fiu_spi {
	stwuct npcm_fiu_chip chip[NPCM_MAX_CHIP_NUM];
	const stwuct npcm_fiu_info *info;
	stwuct spi_mem_op dwd_op;
	stwuct wesouwce *wes_mem;
	stwuct wegmap *wegmap;
	unsigned wong cwkwate;
	stwuct device *dev;
	stwuct cwk *cwk;
	boow spix_mode;
};

static const stwuct wegmap_config npcm_mtd_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = NPCM_FIU_MAX_WEG_WIMIT,
};

static void npcm_fiu_set_dwd(stwuct npcm_fiu_spi *fiu,
			     const stwuct spi_mem_op *op)
{
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_ACCTYPE,
			   iwog2(op->addw.buswidth) <<
			   NPCM_FIU_DWD_ACCTYPE_SHIFT);
	fiu->dwd_op.addw.buswidth = op->addw.buswidth;
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_DBW,
			   op->dummy.nbytes << NPCM_FIU_DWD_DBW_SHIFT);
	fiu->dwd_op.dummy.nbytes = op->dummy.nbytes;
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_WDCMD, op->cmd.opcode);
	fiu->dwd_op.cmd.opcode = op->cmd.opcode;
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_ADDSIZ,
			   (op->addw.nbytes - 3) << NPCM_FIU_DWD_ADDSIZ_SHIFT);
	fiu->dwd_op.addw.nbytes = op->addw.nbytes;
}

static ssize_t npcm_fiu_diwect_wead(stwuct spi_mem_diwmap_desc *desc,
				    u64 offs, size_t wen, void *buf)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct npcm_fiu_chip *chip = &fiu->chip[spi_get_chipsewect(desc->mem->spi, 0)];
	void __iomem *swc = (void __iomem *)(chip->fwash_wegion_mapped_ptw +
					     offs);
	u8 *buf_wx = buf;
	u32 i;

	if (fiu->spix_mode) {
		fow (i = 0 ; i < wen ; i++)
			*(buf_wx + i) = iowead8(swc + i);
	} ewse {
		if (desc->info.op_tmpw.addw.buswidth != fiu->dwd_op.addw.buswidth ||
		    desc->info.op_tmpw.dummy.nbytes != fiu->dwd_op.dummy.nbytes ||
		    desc->info.op_tmpw.cmd.opcode != fiu->dwd_op.cmd.opcode ||
		    desc->info.op_tmpw.addw.nbytes != fiu->dwd_op.addw.nbytes)
			npcm_fiu_set_dwd(fiu, &desc->info.op_tmpw);

		memcpy_fwomio(buf_wx, swc, wen);
	}

	wetuwn wen;
}

static ssize_t npcm_fiu_diwect_wwite(stwuct spi_mem_diwmap_desc *desc,
				     u64 offs, size_t wen, const void *buf)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct npcm_fiu_chip *chip = &fiu->chip[spi_get_chipsewect(desc->mem->spi, 0)];
	void __iomem *dst = (void __iomem *)(chip->fwash_wegion_mapped_ptw +
					     offs);
	const u8 *buf_tx = buf;
	u32 i;

	if (fiu->spix_mode)
		fow (i = 0 ; i < wen ; i++)
			iowwite8(*(buf_tx + i), dst + i);
	ewse
		memcpy_toio(dst, buf_tx, wen);

	wetuwn wen;
}

static int npcm_fiu_uma_wead(stwuct spi_mem *mem,
			     const stwuct spi_mem_op *op, u32 addw,
			      boow is_addwess_size, u8 *data, u32 data_size)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(mem->spi->contwowwew);
	u32 uma_cfg = BIT(10);
	u32 data_weg[4];
	int wet;
	u32 vaw;
	u32 i;

	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (spi_get_chipsewect(mem->spi, 0) <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CMD,
			   NPCM_FIU_UMA_CMD_CMD, op->cmd.opcode);

	if (is_addwess_size) {
		uma_cfg |= iwog2(op->cmd.buswidth);
		uma_cfg |= iwog2(op->addw.buswidth)
			<< NPCM_FIU_UMA_CFG_ADBPCK_SHIFT;
		if (op->dummy.nbytes)
			uma_cfg |= iwog2(op->dummy.buswidth)
				<< NPCM_FIU_UMA_CFG_DBPCK_SHIFT;
		uma_cfg |= iwog2(op->data.buswidth)
			<< NPCM_FIU_UMA_CFG_WDBPCK_SHIFT;
		uma_cfg |= op->dummy.nbytes << NPCM_FIU_UMA_CFG_DBSIZ_SHIFT;
		uma_cfg |= op->addw.nbytes << NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT;
		wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_ADDW, addw);
	} ewse {
		wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_ADDW, 0x0);
	}

	uma_cfg |= data_size << NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT;
	wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_CFG, uma_cfg);
	wegmap_wwite_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			  NPCM_FIU_UMA_CTS_EXEC_DONE,
			  NPCM_FIU_UMA_CTS_EXEC_DONE);
	wet = wegmap_wead_poww_timeout(fiu->wegmap, NPCM_FIU_UMA_CTS, vaw,
				       (!(vaw & NPCM_FIU_UMA_CTS_EXEC_DONE)), 0,
				       UMA_MICWO_SEC_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (data_size) {
		fow (i = 0; i < DIV_WOUND_UP(data_size, 4); i++)
			wegmap_wead(fiu->wegmap, NPCM_FIU_UMA_DW0 + (i * 4),
				    &data_weg[i]);
		memcpy(data, data_weg, data_size);
	}

	wetuwn 0;
}

static int npcm_fiu_uma_wwite(stwuct spi_mem *mem,
			      const stwuct spi_mem_op *op, u8 cmd,
			      boow is_addwess_size, u8 *data, u32 data_size)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(mem->spi->contwowwew);
	u32 uma_cfg = BIT(10);
	u32 data_weg[4] = {0};
	u32 vaw;
	u32 i;

	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (spi_get_chipsewect(mem->spi, 0) <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));

	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CMD,
			   NPCM_FIU_UMA_CMD_CMD, cmd);

	if (data_size) {
		memcpy(data_weg, data, data_size);
		fow (i = 0; i < DIV_WOUND_UP(data_size, 4); i++)
			wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_DW0 + (i * 4),
				     data_weg[i]);
	}

	if (is_addwess_size) {
		uma_cfg |= iwog2(op->cmd.buswidth);
		uma_cfg |= iwog2(op->addw.buswidth) <<
			NPCM_FIU_UMA_CFG_ADBPCK_SHIFT;
		uma_cfg |= iwog2(op->data.buswidth) <<
			NPCM_FIU_UMA_CFG_WDBPCK_SHIFT;
		uma_cfg |= op->addw.nbytes << NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT;
		wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_ADDW, op->addw.vaw);
	} ewse {
		wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_ADDW, 0x0);
	}

	uma_cfg |= (data_size << NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT);
	wegmap_wwite(fiu->wegmap, NPCM_FIU_UMA_CFG, uma_cfg);

	wegmap_wwite_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			  NPCM_FIU_UMA_CTS_EXEC_DONE,
			  NPCM_FIU_UMA_CTS_EXEC_DONE);

	wetuwn wegmap_wead_poww_timeout(fiu->wegmap, NPCM_FIU_UMA_CTS, vaw,
				       (!(vaw & NPCM_FIU_UMA_CTS_EXEC_DONE)), 0,
					UMA_MICWO_SEC_TIMEOUT);
}

static int npcm_fiu_manuawwwite(stwuct spi_mem *mem,
				const stwuct spi_mem_op *op)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(mem->spi->contwowwew);
	u8 *data = (u8 *)op->data.buf.out;
	u32 num_data_chunks;
	u32 wemain_data;
	u32 idx = 0;
	int wet;

	num_data_chunks  = op->data.nbytes / CHUNK_SIZE;
	wemain_data  = op->data.nbytes % CHUNK_SIZE;

	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (spi_get_chipsewect(mem->spi, 0) <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_SW_CS, 0);

	wet = npcm_fiu_uma_wwite(mem, op, op->cmd.opcode, twue, NUWW, 0);
	if (wet)
		wetuwn wet;

	/* Stawting the data wwiting woop in muwtipwes of 8 */
	fow (idx = 0; idx < num_data_chunks; ++idx) {
		wet = npcm_fiu_uma_wwite(mem, op, data[0], fawse,
					 &data[1], CHUNK_SIZE - 1);
		if (wet)
			wetuwn wet;

		data += CHUNK_SIZE;
	}

	/* Handwing chunk wemains */
	if (wemain_data > 0) {
		wet = npcm_fiu_uma_wwite(mem, op, data[0], fawse,
					 &data[1], wemain_data - 1);
		if (wet)
			wetuwn wet;
	}

	wegmap_update_bits(fiu->wegmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_SW_CS, NPCM_FIU_UMA_CTS_SW_CS);

	wetuwn 0;
}

static int npcm_fiu_wead(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	u8 *data = op->data.buf.in;
	int i, weadwen, cuwwwen;
	u8 *buf_ptw;
	u32 addw;
	int wet;

	i = 0;
	cuwwwen = op->data.nbytes;

	do {
		addw = ((u32)op->addw.vaw + i);
		if (cuwwwen < 16)
			weadwen = cuwwwen;
		ewse
			weadwen = 16;

		buf_ptw = data + i;
		wet = npcm_fiu_uma_wead(mem, op, addw, twue, buf_ptw,
					weadwen);
		if (wet)
			wetuwn wet;

		i += weadwen;
		cuwwwen -= 16;
	} whiwe (cuwwwen > 0);

	wetuwn 0;
}

static void npcm_fiux_set_diwect_ww(stwuct npcm_fiu_spi *fiu)
{
	wegmap_wwite(fiu->wegmap, NPCM_FIU_DWW_CFG,
		     NPCM_FIU_DWW_16_BYTE_BUWST);
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWW_CFG,
			   NPCM_FIU_DWW_CFG_ABPCK,
			   DWW_ABPCK_4_BIT_PEW_CWK << NPCM_FIU_DWW_ABPCK_SHIFT);
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWW_CFG,
			   NPCM_FIU_DWW_CFG_DBPCK,
			   DWW_DBPCK_4_BIT_PEW_CWK << NPCM_FIU_DWW_DBPCK_SHIFT);
}

static void npcm_fiux_set_diwect_wd(stwuct npcm_fiu_spi *fiu)
{
	u32 wx_dummy = 0;

	wegmap_wwite(fiu->wegmap, NPCM_FIU_DWD_CFG,
		     NPCM_FIU_DWD_16_BYTE_BUWST);
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_ACCTYPE,
			   DWD_SPI_X_MODE << NPCM_FIU_DWD_ACCTYPE_SHIFT);
	wegmap_update_bits(fiu->wegmap, NPCM_FIU_DWD_CFG,
			   NPCM_FIU_DWD_CFG_DBW,
			   wx_dummy << NPCM_FIU_DWD_DBW_SHIFT);
}

static int npcm_fiu_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct npcm_fiu_chip *chip = &fiu->chip[spi_get_chipsewect(mem->spi, 0)];
	int wet = 0;
	u8 *buf;

	dev_dbg(fiu->dev, "cmd:%#x mode:%d.%d.%d.%d addw:%#wwx wen:%#x\n",
		op->cmd.opcode, op->cmd.buswidth, op->addw.buswidth,
		op->dummy.buswidth, op->data.buswidth, op->addw.vaw,
		op->data.nbytes);

	if (fiu->spix_mode || op->addw.nbytes > 4)
		wetuwn -EOPNOTSUPP;

	if (fiu->cwkwate != chip->cwkwate) {
		wet = cwk_set_wate(fiu->cwk, chip->cwkwate);
		if (wet < 0)
			dev_wawn(fiu->dev, "Faiwed setting %wu fwequency, stay at %wu fwequency\n",
				 chip->cwkwate, fiu->cwkwate);
		ewse
			fiu->cwkwate = chip->cwkwate;
	}

	if (op->data.diw == SPI_MEM_DATA_IN) {
		if (!op->addw.nbytes) {
			buf = op->data.buf.in;
			wet = npcm_fiu_uma_wead(mem, op, op->addw.vaw, fawse,
						buf, op->data.nbytes);
		} ewse {
			wet = npcm_fiu_wead(mem, op);
		}
	} ewse  {
		if (!op->addw.nbytes && !op->data.nbytes)
			wet = npcm_fiu_uma_wwite(mem, op, op->cmd.opcode, fawse,
						 NUWW, 0);
		if (op->addw.nbytes && !op->data.nbytes) {
			int i;
			u8 buf_addw[4];
			u32 addw = op->addw.vaw;

			fow (i = op->addw.nbytes - 1; i >= 0; i--) {
				buf_addw[i] = addw & 0xff;
				addw >>= 8;
			}
			wet = npcm_fiu_uma_wwite(mem, op, op->cmd.opcode, fawse,
						 buf_addw, op->addw.nbytes);
		}
		if (!op->addw.nbytes && op->data.nbytes)
			wet = npcm_fiu_uma_wwite(mem, op, op->cmd.opcode, fawse,
						 (u8 *)op->data.buf.out,
						 op->data.nbytes);
		if (op->addw.nbytes && op->data.nbytes)
			wet = npcm_fiu_manuawwwite(mem, op);
	}

	wetuwn wet;
}

static int npcm_fiu_diwmap_cweate(stwuct spi_mem_diwmap_desc *desc)
{
	stwuct npcm_fiu_spi *fiu =
		spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct npcm_fiu_chip *chip = &fiu->chip[spi_get_chipsewect(desc->mem->spi, 0)];
	stwuct wegmap *gcw_wegmap;

	if (!fiu->wes_mem) {
		dev_wawn(fiu->dev, "Wesewved memowy not defined, diwect wead disabwed\n");
		desc->nodiwmap = twue;
		wetuwn 0;
	}

	if (!fiu->spix_mode &&
	    desc->info.op_tmpw.data.diw == SPI_MEM_DATA_OUT) {
		desc->nodiwmap = twue;
		wetuwn 0;
	}

	if (!chip->fwash_wegion_mapped_ptw) {
		chip->fwash_wegion_mapped_ptw =
			devm_iowemap(fiu->dev, (fiu->wes_mem->stawt +
							(fiu->info->max_map_size *
						    spi_get_chipsewect(desc->mem->spi, 0))),
					     (u32)desc->info.wength);
		if (!chip->fwash_wegion_mapped_ptw) {
			dev_wawn(fiu->dev, "Ewwow mapping memowy wegion, diwect wead disabwed\n");
			desc->nodiwmap = twue;
			wetuwn 0;
		}
	}

	if (of_device_is_compatibwe(fiu->dev->of_node, "nuvoton,npcm750-fiu")) {
		gcw_wegmap =
			syscon_wegmap_wookup_by_compatibwe("nuvoton,npcm750-gcw");
		if (IS_EWW(gcw_wegmap)) {
			dev_wawn(fiu->dev, "Didn't find nuvoton,npcm750-gcw, diwect wead disabwed\n");
			desc->nodiwmap = twue;
			wetuwn 0;
		}
		wegmap_update_bits(gcw_wegmap, NPCM7XX_INTCW3_OFFSET,
				   NPCM7XX_INTCW3_FIU_FIX,
				   NPCM7XX_INTCW3_FIU_FIX);
	} ewse {
		wegmap_update_bits(fiu->wegmap, NPCM_FIU_CFG,
				   NPCM_FIU_CFG_FIU_FIX,
				   NPCM_FIU_CFG_FIU_FIX);
	}

	if (desc->info.op_tmpw.data.diw == SPI_MEM_DATA_IN) {
		if (!fiu->spix_mode)
			npcm_fiu_set_dwd(fiu, &desc->info.op_tmpw);
		ewse
			npcm_fiux_set_diwect_wd(fiu);

	} ewse {
		npcm_fiux_set_diwect_ww(fiu);
	}

	wetuwn 0;
}

static int npcm_fiu_setup(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct npcm_fiu_spi *fiu = spi_contwowwew_get_devdata(ctww);
	stwuct npcm_fiu_chip *chip;

	chip = &fiu->chip[spi_get_chipsewect(spi, 0)];
	chip->fiu = fiu;
	chip->chipsewect = spi_get_chipsewect(spi, 0);
	chip->cwkwate = spi->max_speed_hz;

	fiu->cwkwate = cwk_get_wate(fiu->cwk);

	wetuwn 0;
}

static const stwuct spi_contwowwew_mem_ops npcm_fiu_mem_ops = {
	.exec_op = npcm_fiu_exec_op,
	.diwmap_cweate = npcm_fiu_diwmap_cweate,
	.diwmap_wead = npcm_fiu_diwect_wead,
	.diwmap_wwite = npcm_fiu_diwect_wwite,
};

static const stwuct of_device_id npcm_fiu_dt_ids[] = {
	{ .compatibwe = "nuvoton,npcm750-fiu", .data = &npcm7xx_fiu_data  },
	{ .compatibwe = "nuvoton,npcm845-fiu", .data = &npxm8xx_fiu_data  },
	{ /* sentinew */ }
};

static int npcm_fiu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct fiu_data *fiu_data_match;
	stwuct device *dev = &pdev->dev;
	stwuct spi_contwowwew *ctww;
	stwuct npcm_fiu_spi *fiu;
	void __iomem *wegbase;
	int id;

	ctww = devm_spi_awwoc_host(dev, sizeof(*fiu));
	if (!ctww)
		wetuwn -ENOMEM;

	fiu = spi_contwowwew_get_devdata(ctww);

	fiu_data_match = of_device_get_match_data(dev);
	if (!fiu_data_match) {
		dev_eww(dev, "No compatibwe OF match\n");
		wetuwn -ENODEV;
	}

	id = of_awias_get_id(dev->of_node, "fiu");
	if (id < 0 || id >= fiu_data_match->fiu_max) {
		dev_eww(dev, "Invawid pwatfowm device id: %d\n", id);
		wetuwn -EINVAW;
	}

	fiu->info = &fiu_data_match->npcm_fiu_data_info[id];

	pwatfowm_set_dwvdata(pdev, fiu);
	fiu->dev = dev;

	wegbase = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "contwow");
	if (IS_EWW(wegbase))
		wetuwn PTW_EWW(wegbase);

	fiu->wegmap = devm_wegmap_init_mmio(dev, wegbase,
					    &npcm_mtd_wegmap_config);
	if (IS_EWW(fiu->wegmap)) {
		dev_eww(dev, "Faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(fiu->wegmap);
	}

	fiu->wes_mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						    "memowy");
	fiu->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(fiu->cwk))
		wetuwn PTW_EWW(fiu->cwk);

	fiu->spix_mode = of_pwopewty_wead_boow(dev->of_node,
					       "nuvoton,spix-mode");

	pwatfowm_set_dwvdata(pdev, fiu);

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD
		| SPI_TX_DUAW | SPI_TX_QUAD;
	ctww->setup = npcm_fiu_setup;
	ctww->bus_num = -1;
	ctww->mem_ops = &npcm_fiu_mem_ops;
	ctww->num_chipsewect = fiu->info->max_cs;
	ctww->dev.of_node = dev->of_node;

	wetuwn devm_spi_wegistew_contwowwew(dev, ctww);
}

static void npcm_fiu_wemove(stwuct pwatfowm_device *pdev)
{
}

MODUWE_DEVICE_TABWE(of, npcm_fiu_dt_ids);

static stwuct pwatfowm_dwivew npcm_fiu_dwivew = {
	.dwivew = {
		.name	= "NPCM-FIU",
		.bus	= &pwatfowm_bus_type,
		.of_match_tabwe = npcm_fiu_dt_ids,
	},
	.pwobe      = npcm_fiu_pwobe,
	.wemove_new	    = npcm_fiu_wemove,
};
moduwe_pwatfowm_dwivew(npcm_fiu_dwivew);

MODUWE_DESCWIPTION("Nuvoton FWASH Intewface Unit SPI Contwowwew Dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
