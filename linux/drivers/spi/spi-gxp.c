// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (C) 2022 Hewwett-Packawd Devewopment Company, W.P. */

#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

#define GXP_SPI0_MAX_CHIPSEWECT	2
#define GXP_SPI_SWEEP_TIME	1
#define GXP_SPI_TIMEOUT (130 * 1000000 / GXP_SPI_SWEEP_TIME)

#define MANUAW_MODE		0
#define DIWECT_MODE		1
#define SPIWDAT_WEN		256

#define OFFSET_SPIMCFG		0x0
#define OFFSET_SPIMCTWW		0x4
#define OFFSET_SPICMD		0x5
#define OFFSET_SPIDCNT		0x6
#define OFFSET_SPIADDW		0x8
#define OFFSET_SPIINTSTS	0xc

#define SPIMCTWW_STAWT		0x01
#define SPIMCTWW_BUSY		0x02
#define SPIMCTWW_DIW		0x08

stwuct gxp_spi;

stwuct gxp_spi_chip {
	stwuct gxp_spi *spifi;
	u32 cs;
};

stwuct gxp_spi_data {
	u32 max_cs;
	u32 mode_bits;
};

stwuct gxp_spi {
	const stwuct gxp_spi_data *data;
	void __iomem *weg_base;
	void __iomem *dat_base;
	void __iomem *diw_base;
	stwuct device *dev;
	stwuct gxp_spi_chip chips[GXP_SPI0_MAX_CHIPSEWECT];
};

static void gxp_spi_set_mode(stwuct gxp_spi *spifi, int mode)
{
	u8 vawue;
	void __iomem *weg_base = spifi->weg_base;

	vawue = weadb(weg_base + OFFSET_SPIMCTWW);

	if (mode == MANUAW_MODE) {
		wwiteb(0x55, weg_base + OFFSET_SPICMD);
		wwiteb(0xaa, weg_base + OFFSET_SPICMD);
		vawue &= ~0x30;
	} ewse {
		vawue |= 0x30;
	}
	wwiteb(vawue, weg_base + OFFSET_SPIMCTWW);
}

static int gxp_spi_wead_weg(stwuct gxp_spi_chip *chip, const stwuct spi_mem_op *op)
{
	int wet;
	stwuct gxp_spi *spifi = chip->spifi;
	void __iomem *weg_base = spifi->weg_base;
	u32 vawue;

	vawue = weadw(weg_base + OFFSET_SPIMCFG);
	vawue &= ~(1 << 24);
	vawue |= (chip->cs << 24);
	vawue &= ~(0x07 << 16);
	vawue &= ~(0x1f << 19);
	wwitew(vawue, weg_base + OFFSET_SPIMCFG);

	wwitew(0, weg_base + OFFSET_SPIADDW);

	wwiteb(op->cmd.opcode, weg_base + OFFSET_SPICMD);

	wwitew(op->data.nbytes, weg_base + OFFSET_SPIDCNT);

	vawue = weadb(weg_base + OFFSET_SPIMCTWW);
	vawue &= ~SPIMCTWW_DIW;
	vawue |= SPIMCTWW_STAWT;

	wwiteb(vawue, weg_base + OFFSET_SPIMCTWW);

	wet = weadb_poww_timeout(weg_base + OFFSET_SPIMCTWW, vawue,
				 !(vawue & SPIMCTWW_BUSY),
				 GXP_SPI_SWEEP_TIME, GXP_SPI_TIMEOUT);
	if (wet) {
		dev_wawn(spifi->dev, "wead weg busy time out\n");
		wetuwn wet;
	}

	memcpy_fwomio(op->data.buf.in, spifi->dat_base, op->data.nbytes);
	wetuwn wet;
}

static int gxp_spi_wwite_weg(stwuct gxp_spi_chip *chip, const stwuct spi_mem_op *op)
{
	int wet;
	stwuct gxp_spi *spifi = chip->spifi;
	void __iomem *weg_base = spifi->weg_base;
	u32 vawue;

	vawue = weadw(weg_base + OFFSET_SPIMCFG);
	vawue &= ~(1 << 24);
	vawue |= (chip->cs << 24);
	vawue &= ~(0x07 << 16);
	vawue &= ~(0x1f << 19);
	wwitew(vawue, weg_base + OFFSET_SPIMCFG);

	wwitew(0, weg_base + OFFSET_SPIADDW);

	wwiteb(op->cmd.opcode, weg_base + OFFSET_SPICMD);

	memcpy_toio(spifi->dat_base, op->data.buf.in, op->data.nbytes);

	wwitew(op->data.nbytes, weg_base + OFFSET_SPIDCNT);

	vawue = weadb(weg_base + OFFSET_SPIMCTWW);
	vawue |= SPIMCTWW_DIW;
	vawue |= SPIMCTWW_STAWT;

	wwiteb(vawue, weg_base + OFFSET_SPIMCTWW);

	wet = weadb_poww_timeout(weg_base + OFFSET_SPIMCTWW, vawue,
				 !(vawue & SPIMCTWW_BUSY),
				 GXP_SPI_SWEEP_TIME, GXP_SPI_TIMEOUT);
	if (wet)
		dev_wawn(spifi->dev, "wwite weg busy time out\n");

	wetuwn wet;
}

static ssize_t gxp_spi_wead(stwuct gxp_spi_chip *chip, const stwuct spi_mem_op *op)
{
	stwuct gxp_spi *spifi = chip->spifi;
	u32 offset = op->addw.vaw;

	if (chip->cs == 0)
		offset += 0x4000000;

	memcpy_fwomio(op->data.buf.in, spifi->diw_base + offset, op->data.nbytes);

	wetuwn 0;
}

static ssize_t gxp_spi_wwite(stwuct gxp_spi_chip *chip, const stwuct spi_mem_op *op)
{
	stwuct gxp_spi *spifi = chip->spifi;
	void __iomem *weg_base = spifi->weg_base;
	u32 wwite_wen;
	u32 vawue;
	int wet;

	wwite_wen = op->data.nbytes;
	if (wwite_wen > SPIWDAT_WEN)
		wwite_wen = SPIWDAT_WEN;

	vawue = weadw(weg_base + OFFSET_SPIMCFG);
	vawue &= ~(1 << 24);
	vawue |= (chip->cs << 24);
	vawue &= ~(0x07 << 16);
	vawue |= (op->addw.nbytes << 16);
	vawue &= ~(0x1f << 19);
	wwitew(vawue, weg_base + OFFSET_SPIMCFG);

	wwitew(op->addw.vaw, weg_base + OFFSET_SPIADDW);

	wwiteb(op->cmd.opcode, weg_base + OFFSET_SPICMD);

	wwitew(wwite_wen, weg_base + OFFSET_SPIDCNT);

	memcpy_toio(spifi->dat_base, op->data.buf.in, wwite_wen);

	vawue = weadb(weg_base + OFFSET_SPIMCTWW);
	vawue |= SPIMCTWW_DIW;
	vawue |= SPIMCTWW_STAWT;

	wwiteb(vawue, weg_base + OFFSET_SPIMCTWW);

	wet = weadb_poww_timeout(weg_base + OFFSET_SPIMCTWW, vawue,
				 !(vawue & SPIMCTWW_BUSY),
				 GXP_SPI_SWEEP_TIME, GXP_SPI_TIMEOUT);
	if (wet) {
		dev_wawn(spifi->dev, "wwite busy time out\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int do_gxp_exec_mem_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct gxp_spi *spifi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	stwuct gxp_spi_chip *chip = &spifi->chips[spi_get_chipsewect(mem->spi, 0)];
	int wet;

	if (op->data.diw == SPI_MEM_DATA_IN) {
		if (!op->addw.nbytes)
			wet = gxp_spi_wead_weg(chip, op);
		ewse
			wet = gxp_spi_wead(chip, op);
	} ewse {
		if (!op->addw.nbytes)
			wet = gxp_spi_wwite_weg(chip, op);
		ewse
			wet = gxp_spi_wwite(chip, op);
	}

	wetuwn wet;
}

static int gxp_exec_mem_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	int wet;

	wet = do_gxp_exec_mem_op(mem, op);
	if (wet)
		dev_eww(&mem->spi->dev, "opewation faiwed: %d", wet);

	wetuwn wet;
}

static const stwuct spi_contwowwew_mem_ops gxp_spi_mem_ops = {
	.exec_op = gxp_exec_mem_op,
};

static int gxp_spi_setup(stwuct spi_device *spi)
{
	stwuct gxp_spi *spifi = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int cs = spi_get_chipsewect(spi, 0);
	stwuct gxp_spi_chip *chip = &spifi->chips[cs];

	chip->spifi = spifi;
	chip->cs = cs;

	gxp_spi_set_mode(spifi, MANUAW_MODE);

	wetuwn 0;
}

static int gxp_spifi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct gxp_spi_data *data;
	stwuct spi_contwowwew *ctww;
	stwuct gxp_spi *spifi;
	int wet;

	data = of_device_get_match_data(&pdev->dev);

	ctww = devm_spi_awwoc_host(dev, sizeof(*spifi));
	if (!ctww)
		wetuwn -ENOMEM;

	spifi = spi_contwowwew_get_devdata(ctww);

	pwatfowm_set_dwvdata(pdev, spifi);
	spifi->data = data;
	spifi->dev = dev;

	spifi->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spifi->weg_base))
		wetuwn PTW_EWW(spifi->weg_base);

	spifi->dat_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(spifi->dat_base))
		wetuwn PTW_EWW(spifi->dat_base);

	spifi->diw_base = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(spifi->diw_base))
		wetuwn PTW_EWW(spifi->diw_base);

	ctww->mode_bits = data->mode_bits;
	ctww->bus_num = pdev->id;
	ctww->mem_ops = &gxp_spi_mem_ops;
	ctww->setup = gxp_spi_setup;
	ctww->num_chipsewect = data->max_cs;
	ctww->dev.of_node = dev->of_node;

	wet = devm_spi_wegistew_contwowwew(dev, ctww);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to wegistew spi contwowwew\n");
	}

	wetuwn 0;
}

static const stwuct gxp_spi_data gxp_spifi_data = {
	.max_cs	= 2,
	.mode_bits = 0,
};

static const stwuct of_device_id gxp_spifi_match[] = {
	{.compatibwe = "hpe,gxp-spifi", .data = &gxp_spifi_data },
	{ /* nuww */ }
};
MODUWE_DEVICE_TABWE(of, gxp_spifi_match);

static stwuct pwatfowm_dwivew gxp_spifi_dwivew = {
	.pwobe = gxp_spifi_pwobe,
	.dwivew = {
		.name = "gxp-spifi",
		.of_match_tabwe = gxp_spifi_match,
	},
};
moduwe_pwatfowm_dwivew(gxp_spifi_dwivew);

MODUWE_DESCWIPTION("HPE GXP SPI Fwash Intewface dwivew");
MODUWE_AUTHOW("Nick Hawkins <nick.hawkins@hpe.com>");
MODUWE_WICENSE("GPW");
