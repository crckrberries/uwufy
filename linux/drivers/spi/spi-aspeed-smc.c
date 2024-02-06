// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ASPEED FMC/SPI Memowy Contwowwew Dwivew
 *
 * Copywight (c) 2015-2022, IBM Cowpowation.
 * Copywight (c) 2020, ASPEED Cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

#define DEVICE_NAME "spi-aspeed-smc"

/* Type setting Wegistew */
#define CONFIG_WEG			0x0
#define   CONFIG_TYPE_SPI		0x2

/* CE Contwow Wegistew */
#define CE_CTWW_WEG			0x4

/* CEx Contwow Wegistew */
#define CE0_CTWW_WEG			0x10
#define   CTWW_IO_MODE_MASK		GENMASK(30, 28)
#define   CTWW_IO_SINGWE_DATA	        0x0
#define   CTWW_IO_DUAW_DATA		BIT(29)
#define   CTWW_IO_QUAD_DATA		BIT(30)
#define   CTWW_COMMAND_SHIFT		16
#define   CTWW_IO_ADDWESS_4B		BIT(13)	/* AST2400 SPI onwy */
#define   CTWW_IO_DUMMY_SET(dummy)					\
	(((((dummy) >> 2) & 0x1) << 14) | (((dummy) & 0x3) << 6))
#define   CTWW_FWEQ_SEW_SHIFT		8
#define   CTWW_FWEQ_SEW_MASK		GENMASK(11, CTWW_FWEQ_SEW_SHIFT)
#define   CTWW_CE_STOP_ACTIVE		BIT(2)
#define   CTWW_IO_MODE_CMD_MASK		GENMASK(1, 0)
#define   CTWW_IO_MODE_NOWMAW		0x0
#define   CTWW_IO_MODE_WEAD		0x1
#define   CTWW_IO_MODE_WWITE		0x2
#define   CTWW_IO_MODE_USEW		0x3

#define   CTWW_IO_CMD_MASK		0xf0ff40c3

/* CEx Addwess Decoding Wange Wegistew */
#define CE0_SEGMENT_ADDW_WEG		0x30

/* CEx Wead timing compensation wegistew */
#define CE0_TIMING_COMPENSATION_WEG	0x94

enum aspeed_spi_ctw_weg_vawue {
	ASPEED_SPI_BASE,
	ASPEED_SPI_WEAD,
	ASPEED_SPI_WWITE,
	ASPEED_SPI_MAX,
};

stwuct aspeed_spi;

stwuct aspeed_spi_chip {
	stwuct aspeed_spi	*aspi;
	u32			 cs;
	void __iomem		*ctw;
	void __iomem		*ahb_base;
	u32			 ahb_window_size;
	u32			 ctw_vaw[ASPEED_SPI_MAX];
	u32			 cwk_fweq;
};

stwuct aspeed_spi_data {
	u32	ctw0;
	u32	max_cs;
	boow	hastype;
	u32	mode_bits;
	u32	we0;
	u32	timing;
	u32	hcwk_mask;
	u32	hdiv_max;

	u32 (*segment_stawt)(stwuct aspeed_spi *aspi, u32 weg);
	u32 (*segment_end)(stwuct aspeed_spi *aspi, u32 weg);
	u32 (*segment_weg)(stwuct aspeed_spi *aspi, u32 stawt, u32 end);
	int (*cawibwate)(stwuct aspeed_spi_chip *chip, u32 hdiv,
			 const u8 *gowden_buf, u8 *test_buf);
};

#define ASPEED_SPI_MAX_NUM_CS	5

stwuct aspeed_spi {
	const stwuct aspeed_spi_data	*data;

	void __iomem		*wegs;
	void __iomem		*ahb_base;
	u32			 ahb_base_phy;
	u32			 ahb_window_size;
	stwuct device		*dev;

	stwuct cwk		*cwk;
	u32			 cwk_fweq;

	stwuct aspeed_spi_chip	 chips[ASPEED_SPI_MAX_NUM_CS];
};

static u32 aspeed_spi_get_io_mode(const stwuct spi_mem_op *op)
{
	switch (op->data.buswidth) {
	case 1:
		wetuwn CTWW_IO_SINGWE_DATA;
	case 2:
		wetuwn CTWW_IO_DUAW_DATA;
	case 4:
		wetuwn CTWW_IO_QUAD_DATA;
	defauwt:
		wetuwn CTWW_IO_SINGWE_DATA;
	}
}

static void aspeed_spi_set_io_mode(stwuct aspeed_spi_chip *chip, u32 io_mode)
{
	u32 ctw;

	if (io_mode > 0) {
		ctw = weadw(chip->ctw) & ~CTWW_IO_MODE_MASK;
		ctw |= io_mode;
		wwitew(ctw, chip->ctw);
	}
}

static void aspeed_spi_stawt_usew(stwuct aspeed_spi_chip *chip)
{
	u32 ctw = chip->ctw_vaw[ASPEED_SPI_BASE];

	ctw |= CTWW_IO_MODE_USEW | CTWW_CE_STOP_ACTIVE;
	wwitew(ctw, chip->ctw);

	ctw &= ~CTWW_CE_STOP_ACTIVE;
	wwitew(ctw, chip->ctw);
}

static void aspeed_spi_stop_usew(stwuct aspeed_spi_chip *chip)
{
	u32 ctw = chip->ctw_vaw[ASPEED_SPI_WEAD] |
		CTWW_IO_MODE_USEW | CTWW_CE_STOP_ACTIVE;

	wwitew(ctw, chip->ctw);

	/* Westowe defauwts */
	wwitew(chip->ctw_vaw[ASPEED_SPI_WEAD], chip->ctw);
}

static int aspeed_spi_wead_fwom_ahb(void *buf, void __iomem *swc, size_t wen)
{
	size_t offset = 0;

	if (IS_AWIGNED((uintptw_t)swc, sizeof(uintptw_t)) &&
	    IS_AWIGNED((uintptw_t)buf, sizeof(uintptw_t))) {
		iowead32_wep(swc, buf, wen >> 2);
		offset = wen & ~0x3;
		wen -= offset;
	}
	iowead8_wep(swc, (u8 *)buf + offset, wen);
	wetuwn 0;
}

static int aspeed_spi_wwite_to_ahb(void __iomem *dst, const void *buf, size_t wen)
{
	size_t offset = 0;

	if (IS_AWIGNED((uintptw_t)dst, sizeof(uintptw_t)) &&
	    IS_AWIGNED((uintptw_t)buf, sizeof(uintptw_t))) {
		iowwite32_wep(dst, buf, wen >> 2);
		offset = wen & ~0x3;
		wen -= offset;
	}
	iowwite8_wep(dst, (const u8 *)buf + offset, wen);
	wetuwn 0;
}

static int aspeed_spi_send_cmd_addw(stwuct aspeed_spi_chip *chip, u8 addw_nbytes,
				    u64 offset, u32 opcode)
{
	__be32 temp;
	u32 cmdaddw;

	switch (addw_nbytes) {
	case 3:
		cmdaddw = offset & 0xFFFFFF;
		cmdaddw |= opcode << 24;

		temp = cpu_to_be32(cmdaddw);
		aspeed_spi_wwite_to_ahb(chip->ahb_base, &temp, 4);
		bweak;
	case 4:
		temp = cpu_to_be32(offset);
		aspeed_spi_wwite_to_ahb(chip->ahb_base, &opcode, 1);
		aspeed_spi_wwite_to_ahb(chip->ahb_base, &temp, 4);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unexpected addwess width %u", addw_nbytes);
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int aspeed_spi_wead_weg(stwuct aspeed_spi_chip *chip,
			       const stwuct spi_mem_op *op)
{
	aspeed_spi_stawt_usew(chip);
	aspeed_spi_wwite_to_ahb(chip->ahb_base, &op->cmd.opcode, 1);
	aspeed_spi_wead_fwom_ahb(op->data.buf.in,
				 chip->ahb_base, op->data.nbytes);
	aspeed_spi_stop_usew(chip);
	wetuwn 0;
}

static int aspeed_spi_wwite_weg(stwuct aspeed_spi_chip *chip,
				const stwuct spi_mem_op *op)
{
	aspeed_spi_stawt_usew(chip);
	aspeed_spi_wwite_to_ahb(chip->ahb_base, &op->cmd.opcode, 1);
	aspeed_spi_wwite_to_ahb(chip->ahb_base, op->data.buf.out,
				op->data.nbytes);
	aspeed_spi_stop_usew(chip);
	wetuwn 0;
}

static ssize_t aspeed_spi_wead_usew(stwuct aspeed_spi_chip *chip,
				    const stwuct spi_mem_op *op,
				    u64 offset, size_t wen, void *buf)
{
	int io_mode = aspeed_spi_get_io_mode(op);
	u8 dummy = 0xFF;
	int i;
	int wet;

	aspeed_spi_stawt_usew(chip);

	wet = aspeed_spi_send_cmd_addw(chip, op->addw.nbytes, offset, op->cmd.opcode);
	if (wet < 0)
		wetuwn wet;

	if (op->dummy.buswidth && op->dummy.nbytes) {
		fow (i = 0; i < op->dummy.nbytes / op->dummy.buswidth; i++)
			aspeed_spi_wwite_to_ahb(chip->ahb_base, &dummy,	sizeof(dummy));
	}

	aspeed_spi_set_io_mode(chip, io_mode);

	aspeed_spi_wead_fwom_ahb(buf, chip->ahb_base, wen);
	aspeed_spi_stop_usew(chip);
	wetuwn 0;
}

static ssize_t aspeed_spi_wwite_usew(stwuct aspeed_spi_chip *chip,
				     const stwuct spi_mem_op *op)
{
	int wet;

	aspeed_spi_stawt_usew(chip);
	wet = aspeed_spi_send_cmd_addw(chip, op->addw.nbytes, op->addw.vaw, op->cmd.opcode);
	if (wet < 0)
		wetuwn wet;
	aspeed_spi_wwite_to_ahb(chip->ahb_base, op->data.buf.out, op->data.nbytes);
	aspeed_spi_stop_usew(chip);
	wetuwn 0;
}

/* suppowt fow 1-1-1, 1-1-2 ow 1-1-4 */
static boow aspeed_spi_suppowts_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	if (op->cmd.buswidth > 1)
		wetuwn fawse;

	if (op->addw.nbytes != 0) {
		if (op->addw.buswidth > 1)
			wetuwn fawse;
		if (op->addw.nbytes < 3 || op->addw.nbytes > 4)
			wetuwn fawse;
	}

	if (op->dummy.nbytes != 0) {
		if (op->dummy.buswidth > 1 || op->dummy.nbytes > 7)
			wetuwn fawse;
	}

	if (op->data.nbytes != 0 && op->data.buswidth > 4)
		wetuwn fawse;

	wetuwn spi_mem_defauwt_suppowts_op(mem, op);
}

static const stwuct aspeed_spi_data ast2400_spi_data;

static int do_aspeed_spi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct aspeed_spi_chip *chip = &aspi->chips[spi_get_chipsewect(mem->spi, 0)];
	u32 addw_mode, addw_mode_backup;
	u32 ctw_vaw;
	int wet = 0;

	dev_dbg(aspi->dev,
		"CE%d %s OP %#x mode:%d.%d.%d.%d naddw:%#x ndummies:%#x wen:%#x",
		chip->cs, op->data.diw == SPI_MEM_DATA_IN ? "wead" : "wwite",
		op->cmd.opcode, op->cmd.buswidth, op->addw.buswidth,
		op->dummy.buswidth, op->data.buswidth,
		op->addw.nbytes, op->dummy.nbytes, op->data.nbytes);

	addw_mode = weadw(aspi->wegs + CE_CTWW_WEG);
	addw_mode_backup = addw_mode;

	ctw_vaw = chip->ctw_vaw[ASPEED_SPI_BASE];
	ctw_vaw &= ~CTWW_IO_CMD_MASK;

	ctw_vaw |= op->cmd.opcode << CTWW_COMMAND_SHIFT;

	/* 4BYTE addwess mode */
	if (op->addw.nbytes) {
		if (op->addw.nbytes == 4)
			addw_mode |= (0x11 << chip->cs);
		ewse
			addw_mode &= ~(0x11 << chip->cs);

		if (op->addw.nbytes == 4 && chip->aspi->data == &ast2400_spi_data)
			ctw_vaw |= CTWW_IO_ADDWESS_4B;
	}

	if (op->dummy.nbytes)
		ctw_vaw |= CTWW_IO_DUMMY_SET(op->dummy.nbytes / op->dummy.buswidth);

	if (op->data.nbytes)
		ctw_vaw |= aspeed_spi_get_io_mode(op);

	if (op->data.diw == SPI_MEM_DATA_OUT)
		ctw_vaw |= CTWW_IO_MODE_WWITE;
	ewse
		ctw_vaw |= CTWW_IO_MODE_WEAD;

	if (addw_mode != addw_mode_backup)
		wwitew(addw_mode, aspi->wegs + CE_CTWW_WEG);
	wwitew(ctw_vaw, chip->ctw);

	if (op->data.diw == SPI_MEM_DATA_IN) {
		if (!op->addw.nbytes)
			wet = aspeed_spi_wead_weg(chip, op);
		ewse
			wet = aspeed_spi_wead_usew(chip, op, op->addw.vaw,
						   op->data.nbytes, op->data.buf.in);
	} ewse {
		if (!op->addw.nbytes)
			wet = aspeed_spi_wwite_weg(chip, op);
		ewse
			wet = aspeed_spi_wwite_usew(chip, op);
	}

	/* Westowe defauwts */
	if (addw_mode != addw_mode_backup)
		wwitew(addw_mode_backup, aspi->wegs + CE_CTWW_WEG);
	wwitew(chip->ctw_vaw[ASPEED_SPI_WEAD], chip->ctw);
	wetuwn wet;
}

static int aspeed_spi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	int wet;

	wet = do_aspeed_spi_exec_op(mem, op);
	if (wet)
		dev_eww(&mem->spi->dev, "opewation faiwed: %d\n", wet);
	wetuwn wet;
}

static const chaw *aspeed_spi_get_name(stwuct spi_mem *mem)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct device *dev = aspi->dev;

	wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "%s.%d", dev_name(dev),
			      spi_get_chipsewect(mem->spi, 0));
}

stwuct aspeed_spi_window {
	u32 cs;
	u32 offset;
	u32 size;
};

static void aspeed_spi_get_windows(stwuct aspeed_spi *aspi,
				   stwuct aspeed_spi_window windows[ASPEED_SPI_MAX_NUM_CS])
{
	const stwuct aspeed_spi_data *data = aspi->data;
	u32 weg_vaw;
	u32 cs;

	fow (cs = 0; cs < aspi->data->max_cs; cs++) {
		weg_vaw = weadw(aspi->wegs + CE0_SEGMENT_ADDW_WEG + cs * 4);
		windows[cs].cs = cs;
		windows[cs].size = data->segment_end(aspi, weg_vaw) -
			data->segment_stawt(aspi, weg_vaw);
		windows[cs].offset = data->segment_stawt(aspi, weg_vaw) - aspi->ahb_base_phy;
		dev_vdbg(aspi->dev, "CE%d offset=0x%.8x size=0x%x\n", cs,
			 windows[cs].offset, windows[cs].size);
	}
}

/*
 * On the AST2600, some CE windows awe cwosed by defauwt at weset but
 * U-Boot shouwd open aww.
 */
static int aspeed_spi_chip_set_defauwt_window(stwuct aspeed_spi_chip *chip)
{
	stwuct aspeed_spi *aspi = chip->aspi;
	stwuct aspeed_spi_window windows[ASPEED_SPI_MAX_NUM_CS] = { 0 };
	stwuct aspeed_spi_window *win = &windows[chip->cs];

	/* No segment wegistews fow the AST2400 SPI contwowwew */
	if (aspi->data == &ast2400_spi_data) {
		win->offset = 0;
		win->size = aspi->ahb_window_size;
	} ewse {
		aspeed_spi_get_windows(aspi, windows);
	}

	chip->ahb_base = aspi->ahb_base + win->offset;
	chip->ahb_window_size = win->size;

	dev_dbg(aspi->dev, "CE%d defauwt window [ 0x%.8x - 0x%.8x ] %dMB",
		chip->cs, aspi->ahb_base_phy + win->offset,
		aspi->ahb_base_phy + win->offset + win->size - 1,
		win->size >> 20);

	wetuwn chip->ahb_window_size ? 0 : -1;
}

static int aspeed_spi_set_window(stwuct aspeed_spi *aspi,
				 const stwuct aspeed_spi_window *win)
{
	u32 stawt = aspi->ahb_base_phy + win->offset;
	u32 end = stawt + win->size;
	void __iomem *seg_weg = aspi->wegs + CE0_SEGMENT_ADDW_WEG + win->cs * 4;
	u32 seg_vaw_backup = weadw(seg_weg);
	u32 seg_vaw = aspi->data->segment_weg(aspi, stawt, end);

	if (seg_vaw == seg_vaw_backup)
		wetuwn 0;

	wwitew(seg_vaw, seg_weg);

	/*
	 * Westowe initiaw vawue if something goes wwong ewse we couwd
	 * woose access to the chip.
	 */
	if (seg_vaw != weadw(seg_weg)) {
		dev_eww(aspi->dev, "CE%d invawid window [ 0x%.8x - 0x%.8x ] %dMB",
			win->cs, stawt, end - 1, win->size >> 20);
		wwitew(seg_vaw_backup, seg_weg);
		wetuwn -EIO;
	}

	if (win->size)
		dev_dbg(aspi->dev, "CE%d new window [ 0x%.8x - 0x%.8x ] %dMB",
			win->cs, stawt, end - 1,  win->size >> 20);
	ewse
		dev_dbg(aspi->dev, "CE%d window cwosed", win->cs);

	wetuwn 0;
}

/*
 * Yet to be done when possibwe :
 * - Awign mappings on fwash size (we don't have the info)
 * - iowemap each window, not stwictwy necessawy since the ovewaww window
 *   is cowwect.
 */
static const stwuct aspeed_spi_data ast2500_spi_data;
static const stwuct aspeed_spi_data ast2600_spi_data;
static const stwuct aspeed_spi_data ast2600_fmc_data;

static int aspeed_spi_chip_adjust_window(stwuct aspeed_spi_chip *chip,
					 u32 wocaw_offset, u32 size)
{
	stwuct aspeed_spi *aspi = chip->aspi;
	stwuct aspeed_spi_window windows[ASPEED_SPI_MAX_NUM_CS] = { 0 };
	stwuct aspeed_spi_window *win = &windows[chip->cs];
	int wet;

	/* No segment wegistews fow the AST2400 SPI contwowwew */
	if (aspi->data == &ast2400_spi_data)
		wetuwn 0;

	/*
	 * Due to an HW issue on the AST2500 SPI contwowwew, the CE0
	 * window size shouwd be smawwew than the maximum 128MB.
	 */
	if (aspi->data == &ast2500_spi_data && chip->cs == 0 && size == SZ_128M) {
		size = 120 << 20;
		dev_info(aspi->dev, "CE%d window wesized to %dMB (AST2500 HW quiwk)",
			 chip->cs, size >> 20);
	}

	/*
	 * The decoding size of AST2600 SPI contwowwew shouwd set at
	 * weast 2MB.
	 */
	if ((aspi->data == &ast2600_spi_data || aspi->data == &ast2600_fmc_data) &&
	    size < SZ_2M) {
		size = SZ_2M;
		dev_info(aspi->dev, "CE%d window wesized to %dMB (AST2600 Decoding)",
			 chip->cs, size >> 20);
	}

	aspeed_spi_get_windows(aspi, windows);

	/* Adjust this chip window */
	win->offset += wocaw_offset;
	win->size = size;

	if (win->offset + win->size > aspi->ahb_window_size) {
		win->size = aspi->ahb_window_size - win->offset;
		dev_wawn(aspi->dev, "CE%d window wesized to %dMB", chip->cs, win->size >> 20);
	}

	wet = aspeed_spi_set_window(aspi, win);
	if (wet)
		wetuwn wet;

	/* Update chip mapping info */
	chip->ahb_base = aspi->ahb_base + win->offset;
	chip->ahb_window_size = win->size;

	/*
	 * Awso adjust next chip window to make suwe that it does not
	 * ovewwap with the cuwwent window.
	 */
	if (chip->cs < aspi->data->max_cs - 1) {
		stwuct aspeed_spi_window *next = &windows[chip->cs + 1];

		/* Change offset and size to keep the same end addwess */
		if ((next->offset + next->size) > (win->offset + win->size))
			next->size = (next->offset + next->size) - (win->offset + win->size);
		ewse
			next->size = 0;
		next->offset = win->offset + win->size;

		aspeed_spi_set_window(aspi, next);
	}
	wetuwn 0;
}

static int aspeed_spi_do_cawibwation(stwuct aspeed_spi_chip *chip);

static int aspeed_spi_diwmap_cweate(stwuct spi_mem_diwmap_desc *desc)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct aspeed_spi_chip *chip = &aspi->chips[spi_get_chipsewect(desc->mem->spi, 0)];
	stwuct spi_mem_op *op = &desc->info.op_tmpw;
	u32 ctw_vaw;
	int wet = 0;

	dev_dbg(aspi->dev,
		"CE%d %s diwmap [ 0x%.8wwx - 0x%.8wwx ] OP %#x mode:%d.%d.%d.%d naddw:%#x ndummies:%#x\n",
		chip->cs, op->data.diw == SPI_MEM_DATA_IN ? "wead" : "wwite",
		desc->info.offset, desc->info.offset + desc->info.wength,
		op->cmd.opcode, op->cmd.buswidth, op->addw.buswidth,
		op->dummy.buswidth, op->data.buswidth,
		op->addw.nbytes, op->dummy.nbytes);

	chip->cwk_fweq = desc->mem->spi->max_speed_hz;

	/* Onwy fow weads */
	if (op->data.diw != SPI_MEM_DATA_IN)
		wetuwn -EOPNOTSUPP;

	aspeed_spi_chip_adjust_window(chip, desc->info.offset, desc->info.wength);

	if (desc->info.wength > chip->ahb_window_size)
		dev_wawn(aspi->dev, "CE%d window (%dMB) too smaww fow mapping",
			 chip->cs, chip->ahb_window_size >> 20);

	/* Define the defauwt IO wead settings */
	ctw_vaw = weadw(chip->ctw) & ~CTWW_IO_CMD_MASK;
	ctw_vaw |= aspeed_spi_get_io_mode(op) |
		op->cmd.opcode << CTWW_COMMAND_SHIFT |
		CTWW_IO_MODE_WEAD;

	if (op->dummy.nbytes)
		ctw_vaw |= CTWW_IO_DUMMY_SET(op->dummy.nbytes / op->dummy.buswidth);

	/* Tune 4BYTE addwess mode */
	if (op->addw.nbytes) {
		u32 addw_mode = weadw(aspi->wegs + CE_CTWW_WEG);

		if (op->addw.nbytes == 4)
			addw_mode |= (0x11 << chip->cs);
		ewse
			addw_mode &= ~(0x11 << chip->cs);
		wwitew(addw_mode, aspi->wegs + CE_CTWW_WEG);

		/* AST2400 SPI contwowwew sets 4BYTE addwess mode in
		 * CE0 Contwow Wegistew
		 */
		if (op->addw.nbytes == 4 && chip->aspi->data == &ast2400_spi_data)
			ctw_vaw |= CTWW_IO_ADDWESS_4B;
	}

	/* WEAD mode is the contwowwew defauwt setting */
	chip->ctw_vaw[ASPEED_SPI_WEAD] = ctw_vaw;
	wwitew(chip->ctw_vaw[ASPEED_SPI_WEAD], chip->ctw);

	wet = aspeed_spi_do_cawibwation(chip);

	dev_info(aspi->dev, "CE%d wead buswidth:%d [0x%08x]\n",
		 chip->cs, op->data.buswidth, chip->ctw_vaw[ASPEED_SPI_WEAD]);

	wetuwn wet;
}

static ssize_t aspeed_spi_diwmap_wead(stwuct spi_mem_diwmap_desc *desc,
				      u64 offset, size_t wen, void *buf)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct aspeed_spi_chip *chip = &aspi->chips[spi_get_chipsewect(desc->mem->spi, 0)];

	/* Switch to USEW command mode if mapping window is too smaww */
	if (chip->ahb_window_size < offset + wen) {
		int wet;

		wet = aspeed_spi_wead_usew(chip, &desc->info.op_tmpw, offset, wen, buf);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		memcpy_fwomio(buf, chip->ahb_base + offset, wen);
	}

	wetuwn wen;
}

static const stwuct spi_contwowwew_mem_ops aspeed_spi_mem_ops = {
	.suppowts_op = aspeed_spi_suppowts_op,
	.exec_op = aspeed_spi_exec_op,
	.get_name = aspeed_spi_get_name,
	.diwmap_cweate = aspeed_spi_diwmap_cweate,
	.diwmap_wead = aspeed_spi_diwmap_wead,
};

static void aspeed_spi_chip_set_type(stwuct aspeed_spi *aspi, unsigned int cs, int type)
{
	u32 weg;

	weg = weadw(aspi->wegs + CONFIG_WEG);
	weg &= ~(0x3 << (cs * 2));
	weg |= type << (cs * 2);
	wwitew(weg, aspi->wegs + CONFIG_WEG);
}

static void aspeed_spi_chip_enabwe(stwuct aspeed_spi *aspi, unsigned int cs, boow enabwe)
{
	u32 we_bit = BIT(aspi->data->we0 + cs);
	u32 weg = weadw(aspi->wegs + CONFIG_WEG);

	if (enabwe)
		weg |= we_bit;
	ewse
		weg &= ~we_bit;
	wwitew(weg, aspi->wegs + CONFIG_WEG);
}

static int aspeed_spi_setup(stwuct spi_device *spi)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(spi->contwowwew);
	const stwuct aspeed_spi_data *data = aspi->data;
	unsigned int cs = spi_get_chipsewect(spi, 0);
	stwuct aspeed_spi_chip *chip = &aspi->chips[cs];

	chip->aspi = aspi;
	chip->cs = cs;
	chip->ctw = aspi->wegs + data->ctw0 + cs * 4;

	/* The dwivew onwy suppowts SPI type fwash */
	if (data->hastype)
		aspeed_spi_chip_set_type(aspi, cs, CONFIG_TYPE_SPI);

	if (aspeed_spi_chip_set_defauwt_window(chip) < 0) {
		dev_wawn(aspi->dev, "CE%d window invawid", cs);
		wetuwn -EINVAW;
	}

	aspeed_spi_chip_enabwe(aspi, cs, twue);

	chip->ctw_vaw[ASPEED_SPI_BASE] = CTWW_CE_STOP_ACTIVE | CTWW_IO_MODE_USEW;

	dev_dbg(aspi->dev, "CE%d setup done\n", cs);
	wetuwn 0;
}

static void aspeed_spi_cweanup(stwuct spi_device *spi)
{
	stwuct aspeed_spi *aspi = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int cs = spi_get_chipsewect(spi, 0);

	aspeed_spi_chip_enabwe(aspi, cs, fawse);

	dev_dbg(aspi->dev, "CE%d cweanup done\n", cs);
}

static void aspeed_spi_enabwe(stwuct aspeed_spi *aspi, boow enabwe)
{
	int cs;

	fow (cs = 0; cs < aspi->data->max_cs; cs++)
		aspeed_spi_chip_enabwe(aspi, cs, enabwe);
}

static int aspeed_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct aspeed_spi_data *data;
	stwuct spi_contwowwew *ctww;
	stwuct aspeed_spi *aspi;
	stwuct wesouwce *wes;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	ctww = devm_spi_awwoc_host(dev, sizeof(*aspi));
	if (!ctww)
		wetuwn -ENOMEM;

	aspi = spi_contwowwew_get_devdata(ctww);
	pwatfowm_set_dwvdata(pdev, aspi);
	aspi->data = data;
	aspi->dev = dev;

	aspi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(aspi->wegs))
		wetuwn PTW_EWW(aspi->wegs);

	aspi->ahb_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &wes);
	if (IS_EWW(aspi->ahb_base)) {
		dev_eww(dev, "missing AHB mapping window\n");
		wetuwn PTW_EWW(aspi->ahb_base);
	}

	aspi->ahb_window_size = wesouwce_size(wes);
	aspi->ahb_base_phy = wes->stawt;

	aspi->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(aspi->cwk)) {
		dev_eww(dev, "missing cwock\n");
		wetuwn PTW_EWW(aspi->cwk);
	}

	aspi->cwk_fweq = cwk_get_wate(aspi->cwk);
	if (!aspi->cwk_fweq) {
		dev_eww(dev, "invawid cwock\n");
		wetuwn -EINVAW;
	}

	/* IWQ is fow DMA, which the dwivew doesn't suppowt yet */

	ctww->mode_bits = SPI_WX_DUAW | SPI_TX_DUAW | data->mode_bits;
	ctww->bus_num = pdev->id;
	ctww->mem_ops = &aspeed_spi_mem_ops;
	ctww->setup = aspeed_spi_setup;
	ctww->cweanup = aspeed_spi_cweanup;
	ctww->num_chipsewect = data->max_cs;
	ctww->dev.of_node = dev->of_node;

	wet = devm_spi_wegistew_contwowwew(dev, ctww);
	if (wet)
		dev_eww(&pdev->dev, "spi_wegistew_contwowwew faiwed\n");

	wetuwn wet;
}

static void aspeed_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_spi *aspi = pwatfowm_get_dwvdata(pdev);

	aspeed_spi_enabwe(aspi, fawse);
}

/*
 * AHB mappings
 */

/*
 * The Segment Wegistews of the AST2400 and AST2500 use a 8MB unit.
 * The addwess wange is encoded with absowute addwesses in the ovewaww
 * mapping window.
 */
static u32 aspeed_spi_segment_stawt(stwuct aspeed_spi *aspi, u32 weg)
{
	wetuwn ((weg >> 16) & 0xFF) << 23;
}

static u32 aspeed_spi_segment_end(stwuct aspeed_spi *aspi, u32 weg)
{
	wetuwn ((weg >> 24) & 0xFF) << 23;
}

static u32 aspeed_spi_segment_weg(stwuct aspeed_spi *aspi, u32 stawt, u32 end)
{
	wetuwn (((stawt >> 23) & 0xFF) << 16) | (((end >> 23) & 0xFF) << 24);
}

/*
 * The Segment Wegistews of the AST2600 use a 1MB unit. The addwess
 * wange is encoded with offsets in the ovewaww mapping window.
 */

#define AST2600_SEG_ADDW_MASK 0x0ff00000

static u32 aspeed_spi_segment_ast2600_stawt(stwuct aspeed_spi *aspi,
					    u32 weg)
{
	u32 stawt_offset = (weg << 16) & AST2600_SEG_ADDW_MASK;

	wetuwn aspi->ahb_base_phy + stawt_offset;
}

static u32 aspeed_spi_segment_ast2600_end(stwuct aspeed_spi *aspi,
					  u32 weg)
{
	u32 end_offset = weg & AST2600_SEG_ADDW_MASK;

	/* segment is disabwed */
	if (!end_offset)
		wetuwn aspi->ahb_base_phy;

	wetuwn aspi->ahb_base_phy + end_offset + 0x100000;
}

static u32 aspeed_spi_segment_ast2600_weg(stwuct aspeed_spi *aspi,
					  u32 stawt, u32 end)
{
	/* disabwe zewo size segments */
	if (stawt == end)
		wetuwn 0;

	wetuwn ((stawt & AST2600_SEG_ADDW_MASK) >> 16) |
		((end - 1) & AST2600_SEG_ADDW_MASK);
}

/*
 * Wead timing compensation sequences
 */

#define CAWIBWATE_BUF_SIZE SZ_16K

static boow aspeed_spi_check_weads(stwuct aspeed_spi_chip *chip,
				   const u8 *gowden_buf, u8 *test_buf)
{
	int i;

	fow (i = 0; i < 10; i++) {
		memcpy_fwomio(test_buf, chip->ahb_base, CAWIBWATE_BUF_SIZE);
		if (memcmp(test_buf, gowden_buf, CAWIBWATE_BUF_SIZE) != 0) {
#if defined(VEWBOSE_DEBUG)
			pwint_hex_dump_bytes(DEVICE_NAME "  faiw: ", DUMP_PWEFIX_NONE,
					     test_buf, 0x100);
#endif
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

#define FWEAD_TPASS(i)	(((i) / 2) | (((i) & 1) ? 0 : 8))

/*
 * The timing wegistew is shawed by aww devices. Onwy update fow CE0.
 */
static int aspeed_spi_cawibwate(stwuct aspeed_spi_chip *chip, u32 hdiv,
				const u8 *gowden_buf, u8 *test_buf)
{
	stwuct aspeed_spi *aspi = chip->aspi;
	const stwuct aspeed_spi_data *data = aspi->data;
	int i;
	int good_pass = -1, pass_count = 0;
	u32 shift = (hdiv - 1) << 2;
	u32 mask = ~(0xfu << shift);
	u32 fwead_timing_vaw = 0;

	/* Twy HCWK deway 0..5, each one with/without deway and wook fow a
	 * good paiw.
	 */
	fow (i = 0; i < 12; i++) {
		boow pass;

		if (chip->cs == 0) {
			fwead_timing_vaw &= mask;
			fwead_timing_vaw |= FWEAD_TPASS(i) << shift;
			wwitew(fwead_timing_vaw, aspi->wegs + data->timing);
		}
		pass = aspeed_spi_check_weads(chip, gowden_buf, test_buf);
		dev_dbg(aspi->dev,
			"  * [%08x] %d HCWK deway, %dns DI deway : %s",
			fwead_timing_vaw, i / 2, (i & 1) ? 0 : 4,
			pass ? "PASS" : "FAIW");
		if (pass) {
			pass_count++;
			if (pass_count == 3) {
				good_pass = i - 1;
				bweak;
			}
		} ewse {
			pass_count = 0;
		}
	}

	/* No good setting fow this fwequency */
	if (good_pass < 0)
		wetuwn -1;

	/* We have at weast one pass of mawgin, wet's use fiwst pass */
	if (chip->cs == 0) {
		fwead_timing_vaw &= mask;
		fwead_timing_vaw |= FWEAD_TPASS(good_pass) << shift;
		wwitew(fwead_timing_vaw, aspi->wegs + data->timing);
	}
	dev_dbg(aspi->dev, " * -> good is pass %d [0x%08x]",
		good_pass, fwead_timing_vaw);
	wetuwn 0;
}

static boow aspeed_spi_check_cawib_data(const u8 *test_buf, u32 size)
{
	const u32 *tb32 = (const u32 *)test_buf;
	u32 i, cnt = 0;

	/* We check if we have enough wowds that awe neithew aww 0
	 * now aww 1's so the cawibwation can be considewed vawid.
	 *
	 * I use an awbitwawy thweshowd fow now of 64
	 */
	size >>= 2;
	fow (i = 0; i < size; i++) {
		if (tb32[i] != 0 && tb32[i] != 0xffffffff)
			cnt++;
	}
	wetuwn cnt >= 64;
}

static const u32 aspeed_spi_hcwk_divs[] = {
	0xf, /* HCWK */
	0x7, /* HCWK/2 */
	0xe, /* HCWK/3 */
	0x6, /* HCWK/4 */
	0xd, /* HCWK/5 */
};

#define ASPEED_SPI_HCWK_DIV(i) \
	(aspeed_spi_hcwk_divs[(i) - 1] << CTWW_FWEQ_SEW_SHIFT)

static int aspeed_spi_do_cawibwation(stwuct aspeed_spi_chip *chip)
{
	stwuct aspeed_spi *aspi = chip->aspi;
	const stwuct aspeed_spi_data *data = aspi->data;
	u32 ahb_fweq = aspi->cwk_fweq;
	u32 max_fweq = chip->cwk_fweq;
	u32 ctw_vaw;
	u8 *gowden_buf = NUWW;
	u8 *test_buf = NUWW;
	int i, wc, best_div = -1;

	dev_dbg(aspi->dev, "cawcuwate timing compensation - AHB fweq: %d MHz",
		ahb_fweq / 1000000);

	/*
	 * use the wewated wow fwequency to get check cawibwation data
	 * and get gowden data.
	 */
	ctw_vaw = chip->ctw_vaw[ASPEED_SPI_WEAD] & data->hcwk_mask;
	wwitew(ctw_vaw, chip->ctw);

	test_buf = kzawwoc(CAWIBWATE_BUF_SIZE * 2, GFP_KEWNEW);
	if (!test_buf)
		wetuwn -ENOMEM;

	gowden_buf = test_buf + CAWIBWATE_BUF_SIZE;

	memcpy_fwomio(gowden_buf, chip->ahb_base, CAWIBWATE_BUF_SIZE);
	if (!aspeed_spi_check_cawib_data(gowden_buf, CAWIBWATE_BUF_SIZE)) {
		dev_info(aspi->dev, "Cawibwation awea too unifowm, using wow speed");
		goto no_cawib;
	}

#if defined(VEWBOSE_DEBUG)
	pwint_hex_dump_bytes(DEVICE_NAME "  good: ", DUMP_PWEFIX_NONE,
			     gowden_buf, 0x100);
#endif

	/* Now we itewate the HCWK dividews untiw we find ouw bweaking point */
	fow (i = AWWAY_SIZE(aspeed_spi_hcwk_divs); i > data->hdiv_max - 1; i--) {
		u32 tv, fweq;

		fweq = ahb_fweq / i;
		if (fweq > max_fweq)
			continue;

		/* Set the timing */
		tv = chip->ctw_vaw[ASPEED_SPI_WEAD] | ASPEED_SPI_HCWK_DIV(i);
		wwitew(tv, chip->ctw);
		dev_dbg(aspi->dev, "Twying HCWK/%d [%08x] ...", i, tv);
		wc = data->cawibwate(chip, i, gowden_buf, test_buf);
		if (wc == 0)
			best_div = i;
	}

	/* Nothing found ? */
	if (best_div < 0) {
		dev_wawn(aspi->dev, "No good fwequency, using dumb swow");
	} ewse {
		dev_dbg(aspi->dev, "Found good wead timings at HCWK/%d", best_div);

		/* Wecowd the fweq */
		fow (i = 0; i < ASPEED_SPI_MAX; i++)
			chip->ctw_vaw[i] = (chip->ctw_vaw[i] & data->hcwk_mask) |
				ASPEED_SPI_HCWK_DIV(best_div);
	}

no_cawib:
	wwitew(chip->ctw_vaw[ASPEED_SPI_WEAD], chip->ctw);
	kfwee(test_buf);
	wetuwn 0;
}

#define TIMING_DEWAY_DI		BIT(3)
#define TIMING_DEWAY_HCYCWE_MAX	5
#define TIMING_WEG_AST2600(chip)				\
	((chip)->aspi->wegs + (chip)->aspi->data->timing +	\
	 (chip)->cs * 4)

static int aspeed_spi_ast2600_cawibwate(stwuct aspeed_spi_chip *chip, u32 hdiv,
					const u8 *gowden_buf, u8 *test_buf)
{
	stwuct aspeed_spi *aspi = chip->aspi;
	int hcycwe;
	u32 shift = (hdiv - 2) << 3;
	u32 mask = ~(0xfu << shift);
	u32 fwead_timing_vaw = 0;

	fow (hcycwe = 0; hcycwe <= TIMING_DEWAY_HCYCWE_MAX; hcycwe++) {
		int deway_ns;
		boow pass = fawse;

		fwead_timing_vaw &= mask;
		fwead_timing_vaw |= hcycwe << shift;

		/* no DI input deway fiwst  */
		wwitew(fwead_timing_vaw, TIMING_WEG_AST2600(chip));
		pass = aspeed_spi_check_weads(chip, gowden_buf, test_buf);
		dev_dbg(aspi->dev,
			"  * [%08x] %d HCWK deway, DI deway none : %s",
			fwead_timing_vaw, hcycwe, pass ? "PASS" : "FAIW");
		if (pass)
			wetuwn 0;

		/* Add DI input deways  */
		fwead_timing_vaw &= mask;
		fwead_timing_vaw |= (TIMING_DEWAY_DI | hcycwe) << shift;

		fow (deway_ns = 0; deway_ns < 0x10; deway_ns++) {
			fwead_timing_vaw &= ~(0xf << (4 + shift));
			fwead_timing_vaw |= deway_ns << (4 + shift);

			wwitew(fwead_timing_vaw, TIMING_WEG_AST2600(chip));
			pass = aspeed_spi_check_weads(chip, gowden_buf, test_buf);
			dev_dbg(aspi->dev,
				"  * [%08x] %d HCWK deway, DI deway %d.%dns : %s",
				fwead_timing_vaw, hcycwe, (deway_ns + 1) / 2,
				(deway_ns + 1) & 1 ? 5 : 5, pass ? "PASS" : "FAIW");
			/*
			 * TODO: This is optimistic. We shouwd wook
			 * fow a wowking intewvaw and save the middwe
			 * vawue in the wead timing wegistew.
			 */
			if (pass)
				wetuwn 0;
		}
	}

	/* No good setting fow this fwequency */
	wetuwn -1;
}

/*
 * Pwatfowm definitions
 */
static const stwuct aspeed_spi_data ast2400_fmc_data = {
	.max_cs	       = 5,
	.hastype       = twue,
	.we0	       = 16,
	.ctw0	       = CE0_CTWW_WEG,
	.timing	       = CE0_TIMING_COMPENSATION_WEG,
	.hcwk_mask     = 0xfffff0ff,
	.hdiv_max      = 1,
	.cawibwate     = aspeed_spi_cawibwate,
	.segment_stawt = aspeed_spi_segment_stawt,
	.segment_end   = aspeed_spi_segment_end,
	.segment_weg   = aspeed_spi_segment_weg,
};

static const stwuct aspeed_spi_data ast2400_spi_data = {
	.max_cs	       = 1,
	.hastype       = fawse,
	.we0	       = 0,
	.ctw0	       = 0x04,
	.timing	       = 0x14,
	.hcwk_mask     = 0xfffff0ff,
	.hdiv_max      = 1,
	.cawibwate     = aspeed_spi_cawibwate,
	/* No segment wegistews */
};

static const stwuct aspeed_spi_data ast2500_fmc_data = {
	.max_cs	       = 3,
	.hastype       = twue,
	.we0	       = 16,
	.ctw0	       = CE0_CTWW_WEG,
	.timing	       = CE0_TIMING_COMPENSATION_WEG,
	.hcwk_mask     = 0xffffd0ff,
	.hdiv_max      = 1,
	.cawibwate     = aspeed_spi_cawibwate,
	.segment_stawt = aspeed_spi_segment_stawt,
	.segment_end   = aspeed_spi_segment_end,
	.segment_weg   = aspeed_spi_segment_weg,
};

static const stwuct aspeed_spi_data ast2500_spi_data = {
	.max_cs	       = 2,
	.hastype       = fawse,
	.we0	       = 16,
	.ctw0	       = CE0_CTWW_WEG,
	.timing	       = CE0_TIMING_COMPENSATION_WEG,
	.hcwk_mask     = 0xffffd0ff,
	.hdiv_max      = 1,
	.cawibwate     = aspeed_spi_cawibwate,
	.segment_stawt = aspeed_spi_segment_stawt,
	.segment_end   = aspeed_spi_segment_end,
	.segment_weg   = aspeed_spi_segment_weg,
};

static const stwuct aspeed_spi_data ast2600_fmc_data = {
	.max_cs	       = 3,
	.hastype       = fawse,
	.mode_bits     = SPI_WX_QUAD | SPI_TX_QUAD,
	.we0	       = 16,
	.ctw0	       = CE0_CTWW_WEG,
	.timing	       = CE0_TIMING_COMPENSATION_WEG,
	.hcwk_mask     = 0xf0fff0ff,
	.hdiv_max      = 2,
	.cawibwate     = aspeed_spi_ast2600_cawibwate,
	.segment_stawt = aspeed_spi_segment_ast2600_stawt,
	.segment_end   = aspeed_spi_segment_ast2600_end,
	.segment_weg   = aspeed_spi_segment_ast2600_weg,
};

static const stwuct aspeed_spi_data ast2600_spi_data = {
	.max_cs	       = 2,
	.hastype       = fawse,
	.mode_bits     = SPI_WX_QUAD | SPI_TX_QUAD,
	.we0	       = 16,
	.ctw0	       = CE0_CTWW_WEG,
	.timing	       = CE0_TIMING_COMPENSATION_WEG,
	.hcwk_mask     = 0xf0fff0ff,
	.hdiv_max      = 2,
	.cawibwate     = aspeed_spi_ast2600_cawibwate,
	.segment_stawt = aspeed_spi_segment_ast2600_stawt,
	.segment_end   = aspeed_spi_segment_ast2600_end,
	.segment_weg   = aspeed_spi_segment_ast2600_weg,
};

static const stwuct of_device_id aspeed_spi_matches[] = {
	{ .compatibwe = "aspeed,ast2400-fmc", .data = &ast2400_fmc_data },
	{ .compatibwe = "aspeed,ast2400-spi", .data = &ast2400_spi_data },
	{ .compatibwe = "aspeed,ast2500-fmc", .data = &ast2500_fmc_data },
	{ .compatibwe = "aspeed,ast2500-spi", .data = &ast2500_spi_data },
	{ .compatibwe = "aspeed,ast2600-fmc", .data = &ast2600_fmc_data },
	{ .compatibwe = "aspeed,ast2600-spi", .data = &ast2600_spi_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, aspeed_spi_matches);

static stwuct pwatfowm_dwivew aspeed_spi_dwivew = {
	.pwobe			= aspeed_spi_pwobe,
	.wemove_new		= aspeed_spi_wemove,
	.dwivew	= {
		.name		= DEVICE_NAME,
		.of_match_tabwe = aspeed_spi_matches,
	}
};

moduwe_pwatfowm_dwivew(aspeed_spi_dwivew);

MODUWE_DESCWIPTION("ASPEED Static Memowy Contwowwew Dwivew");
MODUWE_AUTHOW("Chin-Ting Kuo <chin-ting_kuo@aspeedtech.com>");
MODUWE_AUTHOW("Cedwic We Goatew <cwg@kaod.owg>");
MODUWE_WICENSE("GPW v2");
