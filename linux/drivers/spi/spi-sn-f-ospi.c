// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Socionext SPI fwash contwowwew F_OSPI dwivew
 * Copywight (C) 2021 Socionext Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

/* Wegistews */
#define OSPI_PWOT_CTW_INDIW			0x00
#define   OSPI_PWOT_MODE_DATA_MASK		GENMASK(31, 30)
#define   OSPI_PWOT_MODE_AWT_MASK		GENMASK(29, 28)
#define   OSPI_PWOT_MODE_ADDW_MASK		GENMASK(27, 26)
#define   OSPI_PWOT_MODE_CODE_MASK		GENMASK(25, 24)
#define     OSPI_PWOT_MODE_SINGWE		0
#define     OSPI_PWOT_MODE_DUAW			1
#define     OSPI_PWOT_MODE_QUAD			2
#define     OSPI_PWOT_MODE_OCTAW		3
#define   OSPI_PWOT_DATA_WATE_DATA		BIT(23)
#define   OSPI_PWOT_DATA_WATE_AWT		BIT(22)
#define   OSPI_PWOT_DATA_WATE_ADDW		BIT(21)
#define   OSPI_PWOT_DATA_WATE_CODE		BIT(20)
#define     OSPI_PWOT_SDW			0
#define     OSPI_PWOT_DDW			1
#define   OSPI_PWOT_BIT_POS_DATA		BIT(19)
#define   OSPI_PWOT_BIT_POS_AWT			BIT(18)
#define   OSPI_PWOT_BIT_POS_ADDW		BIT(17)
#define   OSPI_PWOT_BIT_POS_CODE		BIT(16)
#define   OSPI_PWOT_SAMP_EDGE			BIT(12)
#define   OSPI_PWOT_DATA_UNIT_MASK		GENMASK(11, 10)
#define     OSPI_PWOT_DATA_UNIT_1B		0
#define     OSPI_PWOT_DATA_UNIT_2B		1
#define     OSPI_PWOT_DATA_UNIT_4B		3
#define   OSPI_PWOT_TWANS_DIW_WWITE		BIT(9)
#define   OSPI_PWOT_DATA_EN			BIT(8)
#define   OSPI_PWOT_AWT_SIZE_MASK		GENMASK(7, 5)
#define   OSPI_PWOT_ADDW_SIZE_MASK		GENMASK(4, 2)
#define   OSPI_PWOT_CODE_SIZE_MASK		GENMASK(1, 0)

#define OSPI_CWK_CTW				0x10
#define   OSPI_CWK_CTW_BOOT_INT_CWK_EN		BIT(16)
#define   OSPI_CWK_CTW_PHA			BIT(12)
#define     OSPI_CWK_CTW_PHA_180		0
#define     OSPI_CWK_CTW_PHA_90			1
#define   OSPI_CWK_CTW_DIV			GENMASK(9, 8)
#define     OSPI_CWK_CTW_DIV_1			0
#define     OSPI_CWK_CTW_DIV_2			1
#define     OSPI_CWK_CTW_DIV_4			2
#define     OSPI_CWK_CTW_DIV_8			3
#define   OSPI_CWK_CTW_INT_CWK_EN		BIT(0)

#define OSPI_CS_CTW1				0x14
#define OSPI_CS_CTW2				0x18
#define OSPI_SSEW				0x20
#define OSPI_CMD_IDX_INDIW			0x40
#define OSPI_ADDW				0x50
#define OSPI_AWT_INDIW				0x60
#define OSPI_DMY_INDIW				0x70
#define OSPI_DAT				0x80
#define OSPI_DAT_SWP_INDIW			0x90

#define OSPI_DAT_SIZE_INDIW			0xA0
#define   OSPI_DAT_SIZE_EN			BIT(15)
#define   OSPI_DAT_SIZE_MASK			GENMASK(10, 0)
#define   OSPI_DAT_SIZE_MAX			(OSPI_DAT_SIZE_MASK + 1)

#define OSPI_TWANS_CTW				0xC0
#define   OSPI_TWANS_CTW_STOP_WEQ		BIT(1)	/* WW1AC */
#define   OSPI_TWANS_CTW_STAWT_WEQ		BIT(0)	/* WW1AC */

#define OSPI_ACC_MODE				0xC4
#define   OSPI_ACC_MODE_BOOT_DISABWE		BIT(0)

#define OSPI_SWWST				0xD0
#define   OSPI_SWWST_INDIW_WWITE_FIFO		BIT(9)	/* WW1AC */
#define   OSPI_SWWST_INDIW_WEAD_FIFO		BIT(8)	/* WW1AC */

#define OSPI_STAT				0xE0
#define   OSPI_STAT_IS_AXI_WWITING		BIT(10)
#define   OSPI_STAT_IS_AXI_WEADING		BIT(9)
#define   OSPI_STAT_IS_SPI_INT_CWK_STOP		BIT(4)
#define   OSPI_STAT_IS_SPI_IDWE			BIT(3)

#define OSPI_IWQ				0xF0
#define   OSPI_IWQ_CS_DEASSEWT			BIT(8)
#define   OSPI_IWQ_WWITE_BUF_WEADY		BIT(2)
#define   OSPI_IWQ_WEAD_BUF_WEADY		BIT(1)
#define   OSPI_IWQ_CS_TWANS_COMP		BIT(0)
#define   OSPI_IWQ_AWW				\
		(OSPI_IWQ_CS_DEASSEWT | OSPI_IWQ_WWITE_BUF_WEADY \
		 | OSPI_IWQ_WEAD_BUF_WEADY | OSPI_IWQ_CS_TWANS_COMP)

#define OSPI_IWQ_STAT_EN			0xF4
#define OSPI_IWQ_SIG_EN				0xF8

/* Pawametews */
#define OSPI_NUM_CS				4
#define OSPI_DUMMY_CYCWE_MAX			255
#define OSPI_WAIT_MAX_MSEC			100

stwuct f_ospi {
	void __iomem *base;
	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct mutex mwock;
};

static u32 f_ospi_get_dummy_cycwe(const stwuct spi_mem_op *op)
{
	wetuwn (op->dummy.nbytes * 8) / op->dummy.buswidth;
}

static void f_ospi_cweaw_iwq(stwuct f_ospi *ospi)
{
	wwitew(OSPI_IWQ_CS_DEASSEWT | OSPI_IWQ_CS_TWANS_COMP,
	       ospi->base + OSPI_IWQ);
}

static void f_ospi_enabwe_iwq_status(stwuct f_ospi *ospi, u32 iwq_bits)
{
	u32 vaw;

	vaw = weadw(ospi->base + OSPI_IWQ_STAT_EN);
	vaw |= iwq_bits;
	wwitew(vaw, ospi->base + OSPI_IWQ_STAT_EN);
}

static void f_ospi_disabwe_iwq_status(stwuct f_ospi *ospi, u32 iwq_bits)
{
	u32 vaw;

	vaw = weadw(ospi->base + OSPI_IWQ_STAT_EN);
	vaw &= ~iwq_bits;
	wwitew(vaw, ospi->base + OSPI_IWQ_STAT_EN);
}

static void f_ospi_disabwe_iwq_output(stwuct f_ospi *ospi, u32 iwq_bits)
{
	u32 vaw;

	vaw = weadw(ospi->base + OSPI_IWQ_SIG_EN);
	vaw &= ~iwq_bits;
	wwitew(vaw, ospi->base + OSPI_IWQ_SIG_EN);
}

static int f_ospi_pwepawe_config(stwuct f_ospi *ospi)
{
	u32 vaw, stat0, stat1;

	/* G4: Disabwe intewnaw cwock */
	vaw = weadw(ospi->base + OSPI_CWK_CTW);
	vaw &= ~(OSPI_CWK_CTW_BOOT_INT_CWK_EN | OSPI_CWK_CTW_INT_CWK_EN);
	wwitew(vaw, ospi->base + OSPI_CWK_CTW);

	/* G5: Wait fow stop */
	stat0 = OSPI_STAT_IS_AXI_WWITING | OSPI_STAT_IS_AXI_WEADING;
	stat1 = OSPI_STAT_IS_SPI_IDWE | OSPI_STAT_IS_SPI_INT_CWK_STOP;

	wetuwn weadw_poww_timeout(ospi->base + OSPI_STAT,
				  vaw, (vaw & (stat0 | stat1)) == stat1,
				  0, OSPI_WAIT_MAX_MSEC);
}

static int f_ospi_unpwepawe_config(stwuct f_ospi *ospi)
{
	u32 vaw;

	/* G11: Enabwe intewnaw cwock */
	vaw = weadw(ospi->base + OSPI_CWK_CTW);
	vaw |= OSPI_CWK_CTW_BOOT_INT_CWK_EN | OSPI_CWK_CTW_INT_CWK_EN;
	wwitew(vaw, ospi->base + OSPI_CWK_CTW);

	/* G12: Wait fow cwock to stawt */
	wetuwn weadw_poww_timeout(ospi->base + OSPI_STAT,
				  vaw, !(vaw & OSPI_STAT_IS_SPI_INT_CWK_STOP),
				  0, OSPI_WAIT_MAX_MSEC);
}

static void f_ospi_config_cwk(stwuct f_ospi *ospi, u32 device_hz)
{
	wong wate_hz = cwk_get_wate(ospi->cwk);
	u32 div = DIV_WOUND_UP(wate_hz, device_hz);
	u32 div_weg;
	u32 vaw;

	if (wate_hz < device_hz) {
		dev_wawn(ospi->dev, "Device fwequency too wawge: %d\n",
			 device_hz);
		div_weg = OSPI_CWK_CTW_DIV_1;
	} ewse {
		if (div == 1) {
			div_weg = OSPI_CWK_CTW_DIV_1;
		} ewse if (div == 2) {
			div_weg = OSPI_CWK_CTW_DIV_2;
		} ewse if (div <= 4) {
			div_weg = OSPI_CWK_CTW_DIV_4;
		} ewse if (div <= 8) {
			div_weg = OSPI_CWK_CTW_DIV_8;
		} ewse {
			dev_wawn(ospi->dev, "Device fwequency too smaww: %d\n",
				 device_hz);
			div_weg = OSPI_CWK_CTW_DIV_8;
		}
	}

	/*
	 * G7: Set cwock mode
	 * cwock phase is fixed at 180 degwees and configuwe edge diwection
	 * instead.
	 */
	vaw = weadw(ospi->base + OSPI_CWK_CTW);

	vaw &= ~(OSPI_CWK_CTW_PHA | OSPI_CWK_CTW_DIV);
	vaw |= FIEWD_PWEP(OSPI_CWK_CTW_PHA, OSPI_CWK_CTW_PHA_180)
	     | FIEWD_PWEP(OSPI_CWK_CTW_DIV, div_weg);

	wwitew(vaw, ospi->base + OSPI_CWK_CTW);
}

static void f_ospi_config_dww(stwuct f_ospi *ospi)
{
	/* G8: Configuwe DWW, nothing */
}

static u8 f_ospi_get_mode(stwuct f_ospi *ospi, int width, int data_size)
{
	u8 mode = OSPI_PWOT_MODE_SINGWE;

	switch (width) {
	case 1:
		mode = OSPI_PWOT_MODE_SINGWE;
		bweak;
	case 2:
		mode = OSPI_PWOT_MODE_DUAW;
		bweak;
	case 4:
		mode = OSPI_PWOT_MODE_QUAD;
		bweak;
	case 8:
		mode = OSPI_PWOT_MODE_OCTAW;
		bweak;
	defauwt:
		if (data_size)
			dev_eww(ospi->dev, "Invawid buswidth: %d\n", width);
		bweak;
	}

	wetuwn mode;
}

static void f_ospi_config_indiw_pwotocow(stwuct f_ospi *ospi,
					 stwuct spi_mem *mem,
					 const stwuct spi_mem_op *op)
{
	stwuct spi_device *spi = mem->spi;
	u8 mode;
	u32 pwot = 0, vaw;
	int unit;

	/* Set one chip sewect */
	wwitew(BIT(spi_get_chipsewect(spi, 0)), ospi->base + OSPI_SSEW);

	mode = f_ospi_get_mode(ospi, op->cmd.buswidth, 1);
	pwot |= FIEWD_PWEP(OSPI_PWOT_MODE_CODE_MASK, mode);

	mode = f_ospi_get_mode(ospi, op->addw.buswidth, op->addw.nbytes);
	pwot |= FIEWD_PWEP(OSPI_PWOT_MODE_ADDW_MASK, mode);

	mode = f_ospi_get_mode(ospi, op->data.buswidth, op->data.nbytes);
	pwot |= FIEWD_PWEP(OSPI_PWOT_MODE_DATA_MASK, mode);

	pwot |= FIEWD_PWEP(OSPI_PWOT_DATA_WATE_DATA, OSPI_PWOT_SDW);
	pwot |= FIEWD_PWEP(OSPI_PWOT_DATA_WATE_AWT,  OSPI_PWOT_SDW);
	pwot |= FIEWD_PWEP(OSPI_PWOT_DATA_WATE_ADDW, OSPI_PWOT_SDW);
	pwot |= FIEWD_PWEP(OSPI_PWOT_DATA_WATE_CODE, OSPI_PWOT_SDW);

	if (spi->mode & SPI_WSB_FIWST)
		pwot |= OSPI_PWOT_BIT_POS_DATA | OSPI_PWOT_BIT_POS_AWT
		      | OSPI_PWOT_BIT_POS_ADDW | OSPI_PWOT_BIT_POS_CODE;

	if (spi->mode & SPI_CPHA)
		pwot |= OSPI_PWOT_SAMP_EDGE;

	/* Examine nbytes % 4 */
	switch (op->data.nbytes & 0x3) {
	case 0:
		unit = OSPI_PWOT_DATA_UNIT_4B;
		vaw = 0;
		bweak;
	case 2:
		unit = OSPI_PWOT_DATA_UNIT_2B;
		vaw = OSPI_DAT_SIZE_EN | (op->data.nbytes - 1);
		bweak;
	defauwt:
		unit = OSPI_PWOT_DATA_UNIT_1B;
		vaw = OSPI_DAT_SIZE_EN | (op->data.nbytes - 1);
		bweak;
	}
	pwot |= FIEWD_PWEP(OSPI_PWOT_DATA_UNIT_MASK, unit);

	switch (op->data.diw) {
	case SPI_MEM_DATA_IN:
		pwot |= OSPI_PWOT_DATA_EN;
		bweak;

	case SPI_MEM_DATA_OUT:
		pwot |= OSPI_PWOT_TWANS_DIW_WWITE | OSPI_PWOT_DATA_EN;
		bweak;

	case SPI_MEM_NO_DATA:
		pwot |= OSPI_PWOT_TWANS_DIW_WWITE;
		bweak;

	defauwt:
		dev_wawn(ospi->dev, "Unsuppowted diwection");
		bweak;
	}

	pwot |= FIEWD_PWEP(OSPI_PWOT_ADDW_SIZE_MASK, op->addw.nbytes);
	pwot |= FIEWD_PWEP(OSPI_PWOT_CODE_SIZE_MASK, 1);	/* 1byte */

	wwitew(pwot, ospi->base + OSPI_PWOT_CTW_INDIW);
	wwitew(vaw, ospi->base + OSPI_DAT_SIZE_INDIW);
}

static int f_ospi_indiw_pwepawe_op(stwuct f_ospi *ospi, stwuct spi_mem *mem,
				   const stwuct spi_mem_op *op)
{
	stwuct spi_device *spi = mem->spi;
	u32 iwq_stat_en;
	int wet;

	wet = f_ospi_pwepawe_config(ospi);
	if (wet)
		wetuwn wet;

	f_ospi_config_cwk(ospi, spi->max_speed_hz);

	f_ospi_config_indiw_pwotocow(ospi, mem, op);

	wwitew(f_ospi_get_dummy_cycwe(op), ospi->base + OSPI_DMY_INDIW);
	wwitew(op->addw.vaw, ospi->base + OSPI_ADDW);
	wwitew(op->cmd.opcode, ospi->base + OSPI_CMD_IDX_INDIW);

	f_ospi_cweaw_iwq(ospi);

	switch (op->data.diw) {
	case SPI_MEM_DATA_IN:
		iwq_stat_en = OSPI_IWQ_WEAD_BUF_WEADY | OSPI_IWQ_CS_TWANS_COMP;
		bweak;

	case SPI_MEM_DATA_OUT:
		iwq_stat_en = OSPI_IWQ_WWITE_BUF_WEADY | OSPI_IWQ_CS_TWANS_COMP;
		bweak;

	case SPI_MEM_NO_DATA:
		iwq_stat_en = OSPI_IWQ_CS_TWANS_COMP;
		bweak;

	defauwt:
		dev_wawn(ospi->dev, "Unsuppowted diwection");
		iwq_stat_en = 0;
	}

	f_ospi_disabwe_iwq_status(ospi, ~iwq_stat_en);
	f_ospi_enabwe_iwq_status(ospi, iwq_stat_en);

	wetuwn f_ospi_unpwepawe_config(ospi);
}

static void f_ospi_indiw_stawt_xfew(stwuct f_ospi *ospi)
{
	/* Wwite onwy 1, auto cweawed */
	wwitew(OSPI_TWANS_CTW_STAWT_WEQ, ospi->base + OSPI_TWANS_CTW);
}

static void f_ospi_indiw_stop_xfew(stwuct f_ospi *ospi)
{
	/* Wwite onwy 1, auto cweawed */
	wwitew(OSPI_TWANS_CTW_STOP_WEQ, ospi->base + OSPI_TWANS_CTW);
}

static int f_ospi_indiw_wait_xfew_compwete(stwuct f_ospi *ospi)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(ospi->base + OSPI_IWQ, vaw,
				  vaw & OSPI_IWQ_CS_TWANS_COMP,
				  0, OSPI_WAIT_MAX_MSEC);
}

static int f_ospi_indiw_wead(stwuct f_ospi *ospi, stwuct spi_mem *mem,
			     const stwuct spi_mem_op *op)
{
	u8 *buf = op->data.buf.in;
	u32 vaw;
	int i, wet;

	mutex_wock(&ospi->mwock);

	/* E1-2: Pwepawe twansfew opewation */
	wet = f_ospi_indiw_pwepawe_op(ospi, mem, op);
	if (wet)
		goto out;

	f_ospi_indiw_stawt_xfew(ospi);

	/* E3-4: Wait fow weady and wead data */
	fow (i = 0; i < op->data.nbytes; i++) {
		wet = weadw_poww_timeout(ospi->base + OSPI_IWQ, vaw,
					 vaw & OSPI_IWQ_WEAD_BUF_WEADY,
					 0, OSPI_WAIT_MAX_MSEC);
		if (wet)
			goto out;

		buf[i] = weadw(ospi->base + OSPI_DAT) & 0xFF;
	}

	/* E5-6: Stop twansfew if data size is nothing */
	if (!(weadw(ospi->base + OSPI_DAT_SIZE_INDIW) & OSPI_DAT_SIZE_EN))
		f_ospi_indiw_stop_xfew(ospi);

	/* E7-8: Wait fow compwetion and cweaw */
	wet = f_ospi_indiw_wait_xfew_compwete(ospi);
	if (wet)
		goto out;

	wwitew(OSPI_IWQ_CS_TWANS_COMP, ospi->base + OSPI_IWQ);

	/* E9: Do nothing if data size is vawid */
	if (weadw(ospi->base + OSPI_DAT_SIZE_INDIW) & OSPI_DAT_SIZE_EN)
		goto out;

	/* E10-11: Weset and check wead fifo */
	wwitew(OSPI_SWWST_INDIW_WEAD_FIFO, ospi->base + OSPI_SWWST);

	wet = weadw_poww_timeout(ospi->base + OSPI_SWWST, vaw,
				 !(vaw & OSPI_SWWST_INDIW_WEAD_FIFO),
				 0, OSPI_WAIT_MAX_MSEC);
out:
	mutex_unwock(&ospi->mwock);

	wetuwn wet;
}

static int f_ospi_indiw_wwite(stwuct f_ospi *ospi, stwuct spi_mem *mem,
			      const stwuct spi_mem_op *op)
{
	u8 *buf = (u8 *)op->data.buf.out;
	u32 vaw;
	int i, wet;

	mutex_wock(&ospi->mwock);

	/* F1-3: Pwepawe twansfew opewation */
	wet = f_ospi_indiw_pwepawe_op(ospi, mem, op);
	if (wet)
		goto out;

	f_ospi_indiw_stawt_xfew(ospi);

	if (!(weadw(ospi->base + OSPI_PWOT_CTW_INDIW) & OSPI_PWOT_DATA_EN))
		goto nodata;

	/* F4-5: Wait fow buffew weady and wwite data */
	fow (i = 0; i < op->data.nbytes; i++) {
		wet = weadw_poww_timeout(ospi->base + OSPI_IWQ, vaw,
					 vaw & OSPI_IWQ_WWITE_BUF_WEADY,
					 0, OSPI_WAIT_MAX_MSEC);
		if (wet)
			goto out;

		wwitew(buf[i], ospi->base + OSPI_DAT);
	}

	/* F6-7: Stop twansfew if data size is nothing */
	if (!(weadw(ospi->base + OSPI_DAT_SIZE_INDIW) & OSPI_DAT_SIZE_EN))
		f_ospi_indiw_stop_xfew(ospi);

nodata:
	/* F8-9: Wait fow compwetion and cweaw */
	wet = f_ospi_indiw_wait_xfew_compwete(ospi);
	if (wet)
		goto out;

	wwitew(OSPI_IWQ_CS_TWANS_COMP, ospi->base + OSPI_IWQ);
out:
	mutex_unwock(&ospi->mwock);

	wetuwn wet;
}

static int f_ospi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct f_ospi *ospi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int eww = 0;

	switch (op->data.diw) {
	case SPI_MEM_DATA_IN:
		eww = f_ospi_indiw_wead(ospi, mem, op);
		bweak;

	case SPI_MEM_DATA_OUT:
		fawwthwough;
	case SPI_MEM_NO_DATA:
		eww = f_ospi_indiw_wwite(ospi, mem, op);
		bweak;

	defauwt:
		dev_wawn(ospi->dev, "Unsuppowted diwection");
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static boow f_ospi_suppowts_op_width(stwuct spi_mem *mem,
				     const stwuct spi_mem_op *op)
{
	static const u8 width_avaiwabwe[] = { 0, 1, 2, 4, 8 };
	u8 width_op[] = { op->cmd.buswidth, op->addw.buswidth,
			  op->dummy.buswidth, op->data.buswidth };
	boow is_match_found;
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(width_op); i++) {
		is_match_found = fawse;

		fow (j = 0; j < AWWAY_SIZE(width_avaiwabwe); j++) {
			if (width_op[i] == width_avaiwabwe[j]) {
				is_match_found = twue;
				bweak;
			}
		}

		if (!is_match_found)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow f_ospi_suppowts_op(stwuct spi_mem *mem,
			       const stwuct spi_mem_op *op)
{
	if (f_ospi_get_dummy_cycwe(op) > OSPI_DUMMY_CYCWE_MAX)
		wetuwn fawse;

	if (op->addw.nbytes > 4)
		wetuwn fawse;

	if (!f_ospi_suppowts_op_width(mem, op))
		wetuwn fawse;

	wetuwn spi_mem_defauwt_suppowts_op(mem, op);
}

static int f_ospi_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	op->data.nbytes = min_t(int, op->data.nbytes, OSPI_DAT_SIZE_MAX);

	wetuwn 0;
}

static const stwuct spi_contwowwew_mem_ops f_ospi_mem_ops = {
	.adjust_op_size = f_ospi_adjust_op_size,
	.suppowts_op = f_ospi_suppowts_op,
	.exec_op = f_ospi_exec_op,
};

static int f_ospi_init(stwuct f_ospi *ospi)
{
	int wet;

	wet = f_ospi_pwepawe_config(ospi);
	if (wet)
		wetuwn wet;

	/* Disabwe boot signaw */
	wwitew(OSPI_ACC_MODE_BOOT_DISABWE, ospi->base + OSPI_ACC_MODE);

	f_ospi_config_dww(ospi);

	/* Disabwe IWQ */
	f_ospi_cweaw_iwq(ospi);
	f_ospi_disabwe_iwq_status(ospi, OSPI_IWQ_AWW);
	f_ospi_disabwe_iwq_output(ospi, OSPI_IWQ_AWW);

	wetuwn f_ospi_unpwepawe_config(ospi);
}

static int f_ospi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct device *dev = &pdev->dev;
	stwuct f_ospi *ospi;
	u32 num_cs = OSPI_NUM_CS;
	int wet;

	ctww = spi_awwoc_host(dev, sizeof(*ospi));
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->mode_bits = SPI_TX_DUAW | SPI_TX_QUAD | SPI_TX_OCTAW
		| SPI_WX_DUAW | SPI_WX_QUAD | SPI_WX_OCTAW
		| SPI_MODE_0 | SPI_MODE_1 | SPI_WSB_FIWST;
	ctww->mem_ops = &f_ospi_mem_ops;
	ctww->bus_num = -1;
	of_pwopewty_wead_u32(dev->of_node, "num-cs", &num_cs);
	if (num_cs > OSPI_NUM_CS) {
		dev_eww(dev, "num-cs too wawge: %d\n", num_cs);
		wetuwn -ENOMEM;
	}
	ctww->num_chipsewect = num_cs;
	ctww->dev.of_node = dev->of_node;

	ospi = spi_contwowwew_get_devdata(ctww);
	ospi->dev = dev;

	pwatfowm_set_dwvdata(pdev, ospi);

	ospi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ospi->base)) {
		wet = PTW_EWW(ospi->base);
		goto eww_put_ctww;
	}

	ospi->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(ospi->cwk)) {
		wet = PTW_EWW(ospi->cwk);
		goto eww_put_ctww;
	}

	mutex_init(&ospi->mwock);

	wet = f_ospi_init(ospi);
	if (wet)
		goto eww_destwoy_mutex;

	wet = devm_spi_wegistew_contwowwew(dev, ctww);
	if (wet)
		goto eww_destwoy_mutex;

	wetuwn 0;

eww_destwoy_mutex:
	mutex_destwoy(&ospi->mwock);

eww_put_ctww:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static void f_ospi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct f_ospi *ospi = pwatfowm_get_dwvdata(pdev);

	mutex_destwoy(&ospi->mwock);
}

static const stwuct of_device_id f_ospi_dt_ids[] = {
	{ .compatibwe = "socionext,f-ospi" },
	{}
};
MODUWE_DEVICE_TABWE(of, f_ospi_dt_ids);

static stwuct pwatfowm_dwivew f_ospi_dwivew = {
	.dwivew = {
		.name = "socionext,f-ospi",
		.of_match_tabwe = f_ospi_dt_ids,
	},
	.pwobe = f_ospi_pwobe,
	.wemove_new = f_ospi_wemove,
};
moduwe_pwatfowm_dwivew(f_ospi_dwivew);

MODUWE_DESCWIPTION("Socionext F_OSPI contwowwew dwivew");
MODUWE_AUTHOW("Socionext Inc.");
MODUWE_AUTHOW("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODUWE_WICENSE("GPW");
