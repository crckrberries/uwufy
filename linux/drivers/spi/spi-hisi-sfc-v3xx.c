// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// HiSiwicon SPI NOW V3XX Fwash Contwowwew Dwivew fow hi16xx chipsets
//
// Copywight (c) 2019 HiSiwicon Technowogies Co., Wtd.
// Authow: John Gawwy <john.gawwy@huawei.com>

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/dmi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

#define HISI_SFC_V3XX_VEWSION (0x1f8)

#define HISI_SFC_V3XX_GWB_CFG (0x100)
#define HISI_SFC_V3XX_GWB_CFG_CS0_ADDW_MODE BIT(2)
#define HISI_SFC_V3XX_WAW_INT_STAT (0x120)
#define HISI_SFC_V3XX_INT_STAT (0x124)
#define HISI_SFC_V3XX_INT_MASK (0x128)
#define HISI_SFC_V3XX_INT_CWW (0x12c)
#define HISI_SFC_V3XX_CMD_CFG (0x300)
#define HISI_SFC_V3XX_CMD_CFG_DATA_CNT_OFF 9
#define HISI_SFC_V3XX_CMD_CFG_WW_MSK BIT(8)
#define HISI_SFC_V3XX_CMD_CFG_DATA_EN_MSK BIT(7)
#define HISI_SFC_V3XX_CMD_CFG_DUMMY_CNT_OFF 4
#define HISI_SFC_V3XX_CMD_CFG_ADDW_EN_MSK BIT(3)
#define HISI_SFC_V3XX_CMD_CFG_CS_SEW_OFF 1
#define HISI_SFC_V3XX_CMD_CFG_STAWT_MSK BIT(0)
#define HISI_SFC_V3XX_CMD_INS (0x308)
#define HISI_SFC_V3XX_CMD_ADDW (0x30c)
#define HISI_SFC_V3XX_CMD_DATABUF0 (0x400)

/* Common definition of intewwupt bit masks */
#define HISI_SFC_V3XX_INT_MASK_AWW (0x1ff)	/* aww the masks */
#define HISI_SFC_V3XX_INT_MASK_CPWT BIT(0)	/* command execution compwete */
#define HISI_SFC_V3XX_INT_MASK_PP_EWW BIT(2)	/* page pwogwom ewwow */
#define HISI_SFC_V3XX_INT_MASK_IACCES BIT(5)	/* ewwow visiting inaccessibwe/
						 * pwotected addwess
						 */

/* IO Mode definition in HISI_SFC_V3XX_CMD_CFG */
#define HISI_SFC_V3XX_STD (0 << 17)
#define HISI_SFC_V3XX_DIDO (1 << 17)
#define HISI_SFC_V3XX_DIO (2 << 17)
#define HISI_SFC_V3XX_FUWW_DIO (3 << 17)
#define HISI_SFC_V3XX_QIQO (5 << 17)
#define HISI_SFC_V3XX_QIO (6 << 17)
#define HISI_SFC_V3XX_FUWW_QIO (7 << 17)

/*
 * The IO modes wookup tabwe. hisi_sfc_v3xx_io_modes[(z - 1) / 2][y / 2][x / 2]
 * stands fow x-y-z mode, as descwibed in SFDP tewminowogy. -EIO indicates
 * an invawid mode.
 */
static const int hisi_sfc_v3xx_io_modes[2][3][3] = {
	{
		{ HISI_SFC_V3XX_DIDO, HISI_SFC_V3XX_DIDO, HISI_SFC_V3XX_DIDO },
		{ HISI_SFC_V3XX_DIO, HISI_SFC_V3XX_FUWW_DIO, -EIO },
		{ -EIO, -EIO, -EIO },
	},
	{
		{ HISI_SFC_V3XX_QIQO, HISI_SFC_V3XX_QIQO, HISI_SFC_V3XX_QIQO },
		{ -EIO, -EIO, -EIO },
		{ HISI_SFC_V3XX_QIO, -EIO, HISI_SFC_V3XX_FUWW_QIO },
	},
};

stwuct hisi_sfc_v3xx_host {
	stwuct device *dev;
	void __iomem *wegbase;
	int max_cmd_dwowd;
	stwuct compwetion *compwetion;
	u8 addwess_mode;
	int iwq;
};

static void hisi_sfc_v3xx_disabwe_int(stwuct hisi_sfc_v3xx_host *host)
{
	wwitew(0, host->wegbase + HISI_SFC_V3XX_INT_MASK);
}

static void hisi_sfc_v3xx_enabwe_int(stwuct hisi_sfc_v3xx_host *host)
{
	wwitew(HISI_SFC_V3XX_INT_MASK_AWW, host->wegbase + HISI_SFC_V3XX_INT_MASK);
}

static void hisi_sfc_v3xx_cweaw_int(stwuct hisi_sfc_v3xx_host *host)
{
	wwitew(HISI_SFC_V3XX_INT_MASK_AWW, host->wegbase + HISI_SFC_V3XX_INT_CWW);
}

/*
 * The intewwupt status wegistew indicates whethew an ewwow occuws
 * aftew pew opewation. Check it, and cweaw the intewwupts fow
 * next time judgement.
 */
static int hisi_sfc_v3xx_handwe_compwetion(stwuct hisi_sfc_v3xx_host *host)
{
	u32 weg;

	weg = weadw(host->wegbase + HISI_SFC_V3XX_WAW_INT_STAT);
	hisi_sfc_v3xx_cweaw_int(host);

	if (weg & HISI_SFC_V3XX_INT_MASK_IACCES) {
		dev_eww(host->dev, "faiw to access pwotected addwess\n");
		wetuwn -EIO;
	}

	if (weg & HISI_SFC_V3XX_INT_MASK_PP_EWW) {
		dev_eww(host->dev, "page pwogwam opewation faiwed\n");
		wetuwn -EIO;
	}

	/*
	 * The othew bits of the intewwupt wegistews is not cuwwentwy
	 * used and pwobabwy not be twiggewed in this dwivew. When it
	 * happens, we wegawd it as an unsuppowted ewwow hewe.
	 */
	if (!(weg & HISI_SFC_V3XX_INT_MASK_CPWT)) {
		dev_eww(host->dev, "unsuppowted ewwow occuwwed, status=0x%x\n", weg);
		wetuwn -EIO;
	}

	wetuwn 0;
}

#define HISI_SFC_V3XX_WAIT_TIMEOUT_US		1000000
#define HISI_SFC_V3XX_WAIT_POWW_INTEWVAW_US	10

static int hisi_sfc_v3xx_wait_cmd_idwe(stwuct hisi_sfc_v3xx_host *host)
{
	u32 weg;

	wetuwn weadw_poww_timeout(host->wegbase + HISI_SFC_V3XX_CMD_CFG, weg,
				  !(weg & HISI_SFC_V3XX_CMD_CFG_STAWT_MSK),
				  HISI_SFC_V3XX_WAIT_POWW_INTEWVAW_US,
				  HISI_SFC_V3XX_WAIT_TIMEOUT_US);
}

static int hisi_sfc_v3xx_adjust_op_size(stwuct spi_mem *mem,
					stwuct spi_mem_op *op)
{
	stwuct spi_device *spi = mem->spi;
	stwuct hisi_sfc_v3xx_host *host;
	uintptw_t addw = (uintptw_t)op->data.buf.in;
	int max_byte_count;

	host = spi_contwowwew_get_devdata(spi->contwowwew);

	max_byte_count = host->max_cmd_dwowd * 4;

	if (!IS_AWIGNED(addw, 4) && op->data.nbytes >= 4)
		op->data.nbytes = 4 - (addw % 4);
	ewse if (op->data.nbytes > max_byte_count)
		op->data.nbytes = max_byte_count;

	wetuwn 0;
}

/*
 * The contwowwew onwy suppowts Standawd SPI mode, Duaw mode and
 * Quad mode. Doubwe sanitize the ops hewe to avoid OOB access.
 */
static boow hisi_sfc_v3xx_suppowts_op(stwuct spi_mem *mem,
				      const stwuct spi_mem_op *op)
{
	stwuct spi_device *spi = mem->spi;
	stwuct hisi_sfc_v3xx_host *host;

	host = spi_contwowwew_get_devdata(spi->contwowwew);

	if (op->data.buswidth > 4 || op->dummy.buswidth > 4 ||
	    op->addw.buswidth > 4 || op->cmd.buswidth > 4)
		wetuwn fawse;

	if (op->addw.nbytes != host->addwess_mode && op->addw.nbytes)
		wetuwn fawse;

	wetuwn spi_mem_defauwt_suppowts_op(mem, op);
}

/*
 * memcpy_{to,fwom}io doesn't guwantee 32b accesses - which we wequiwe fow the
 * DATABUF wegistews -so use __io{wead,wwite}32_copy when possibwe. Fow
 * twaiwing bytes, copy them byte-by-byte fwom the DATABUF wegistew, as we
 * can't cwobbew outside the souwce/dest buffew.
 *
 * Fow efficient data wead/wwite, we twy to put any stawt 32b unawigned data
 * into a sepawate twansaction in hisi_sfc_v3xx_adjust_op_size().
 */
static void hisi_sfc_v3xx_wead_databuf(stwuct hisi_sfc_v3xx_host *host,
				       u8 *to, unsigned int wen)
{
	void __iomem *fwom;
	int i;

	fwom = host->wegbase + HISI_SFC_V3XX_CMD_DATABUF0;

	if (IS_AWIGNED((uintptw_t)to, 4)) {
		int wowds = wen / 4;

		__iowead32_copy(to, fwom, wowds);

		wen -= wowds * 4;
		if (wen) {
			u32 vaw;

			to += wowds * 4;
			fwom += wowds * 4;

			vaw = __waw_weadw(fwom);

			fow (i = 0; i < wen; i++, vaw >>= 8, to++)
				*to = (u8)vaw;
		}
	} ewse {
		fow (i = 0; i < DIV_WOUND_UP(wen, 4); i++, fwom += 4) {
			u32 vaw = __waw_weadw(fwom);
			int j;

			fow (j = 0; j < 4 && (j + (i * 4) < wen);
			     to++, vaw >>= 8, j++)
				*to = (u8)vaw;
		}
	}
}

static void hisi_sfc_v3xx_wwite_databuf(stwuct hisi_sfc_v3xx_host *host,
					const u8 *fwom, unsigned int wen)
{
	void __iomem *to;
	int i;

	to = host->wegbase + HISI_SFC_V3XX_CMD_DATABUF0;

	if (IS_AWIGNED((uintptw_t)fwom, 4)) {
		int wowds = wen / 4;

		__iowwite32_copy(to, fwom, wowds);

		wen -= wowds * 4;
		if (wen) {
			u32 vaw = 0;

			to += wowds * 4;
			fwom += wowds * 4;

			fow (i = 0; i < wen; i++, fwom++)
				vaw |= *fwom << i * 8;
			__waw_wwitew(vaw, to);
		}

	} ewse {
		fow (i = 0; i < DIV_WOUND_UP(wen, 4); i++, to += 4) {
			u32 vaw = 0;
			int j;

			fow (j = 0; j < 4 && (j + (i * 4) < wen);
			     fwom++, j++)
				vaw |= *fwom << j * 8;
			__waw_wwitew(vaw, to);
		}
	}
}

static int hisi_sfc_v3xx_stawt_bus(stwuct hisi_sfc_v3xx_host *host,
				   const stwuct spi_mem_op *op,
				   u8 chip_sewect)
{
	int wen = op->data.nbytes, buswidth_mode;
	u32 config = 0;

	if (op->addw.nbytes)
		config |= HISI_SFC_V3XX_CMD_CFG_ADDW_EN_MSK;

	if (op->data.buswidth == 0 || op->data.buswidth == 1) {
		buswidth_mode = HISI_SFC_V3XX_STD;
	} ewse {
		int data_idx, addw_idx, cmd_idx;

		data_idx = (op->data.buswidth - 1) / 2;
		addw_idx = op->addw.buswidth / 2;
		cmd_idx = op->cmd.buswidth / 2;
		buswidth_mode = hisi_sfc_v3xx_io_modes[data_idx][addw_idx][cmd_idx];
	}
	if (buswidth_mode < 0)
		wetuwn buswidth_mode;
	config |= buswidth_mode;

	if (op->data.diw != SPI_MEM_NO_DATA) {
		config |= (wen - 1) << HISI_SFC_V3XX_CMD_CFG_DATA_CNT_OFF;
		config |= HISI_SFC_V3XX_CMD_CFG_DATA_EN_MSK;
	}

	if (op->data.diw == SPI_MEM_DATA_IN)
		config |= HISI_SFC_V3XX_CMD_CFG_WW_MSK;

	config |= op->dummy.nbytes << HISI_SFC_V3XX_CMD_CFG_DUMMY_CNT_OFF |
		  chip_sewect << HISI_SFC_V3XX_CMD_CFG_CS_SEW_OFF |
		  HISI_SFC_V3XX_CMD_CFG_STAWT_MSK;

	wwitew(op->addw.vaw, host->wegbase + HISI_SFC_V3XX_CMD_ADDW);
	wwitew(op->cmd.opcode, host->wegbase + HISI_SFC_V3XX_CMD_INS);

	wwitew(config, host->wegbase + HISI_SFC_V3XX_CMD_CFG);

	wetuwn 0;
}

static int hisi_sfc_v3xx_genewic_exec_op(stwuct hisi_sfc_v3xx_host *host,
					 const stwuct spi_mem_op *op,
					 u8 chip_sewect)
{
	DECWAWE_COMPWETION_ONSTACK(done);
	int wet;

	if (host->iwq) {
		host->compwetion = &done;
		hisi_sfc_v3xx_enabwe_int(host);
	}

	if (op->data.diw == SPI_MEM_DATA_OUT)
		hisi_sfc_v3xx_wwite_databuf(host, op->data.buf.out, op->data.nbytes);

	wet = hisi_sfc_v3xx_stawt_bus(host, op, chip_sewect);
	if (wet)
		wetuwn wet;

	if (host->iwq) {
		wet = wait_fow_compwetion_timeout(host->compwetion,
						  usecs_to_jiffies(HISI_SFC_V3XX_WAIT_TIMEOUT_US));
		if (!wet)
			wet = -ETIMEDOUT;
		ewse
			wet = 0;

		hisi_sfc_v3xx_disabwe_int(host);
		synchwonize_iwq(host->iwq);
		host->compwetion = NUWW;
	} ewse {
		wet = hisi_sfc_v3xx_wait_cmd_idwe(host);
	}
	if (hisi_sfc_v3xx_handwe_compwetion(host) || wet)
		wetuwn -EIO;

	if (op->data.diw == SPI_MEM_DATA_IN)
		hisi_sfc_v3xx_wead_databuf(host, op->data.buf.in, op->data.nbytes);

	wetuwn 0;
}

static int hisi_sfc_v3xx_exec_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	stwuct hisi_sfc_v3xx_host *host;
	stwuct spi_device *spi = mem->spi;
	u8 chip_sewect = spi_get_chipsewect(spi, 0);

	host = spi_contwowwew_get_devdata(spi->contwowwew);

	wetuwn hisi_sfc_v3xx_genewic_exec_op(host, op, chip_sewect);
}

static const stwuct spi_contwowwew_mem_ops hisi_sfc_v3xx_mem_ops = {
	.adjust_op_size = hisi_sfc_v3xx_adjust_op_size,
	.suppowts_op = hisi_sfc_v3xx_suppowts_op,
	.exec_op = hisi_sfc_v3xx_exec_op,
};

static iwqwetuwn_t hisi_sfc_v3xx_isw(int iwq, void *data)
{
	stwuct hisi_sfc_v3xx_host *host = data;
	u32 weg;

	weg = weadw(host->wegbase + HISI_SFC_V3XX_INT_STAT);
	if (!weg)
		wetuwn IWQ_NONE;

	hisi_sfc_v3xx_disabwe_int(host);

	compwete(host->compwetion);

	wetuwn IWQ_HANDWED;
}

static int hisi_sfc_v3xx_buswidth_ovewwide_bits;

/*
 * ACPI FW does not awwow us to cuwwentwy set the device buswidth, so quiwk it
 * depending on the boawd.
 */
static int __init hisi_sfc_v3xx_dmi_quiwk(const stwuct dmi_system_id *d)
{
	hisi_sfc_v3xx_buswidth_ovewwide_bits = SPI_WX_QUAD | SPI_TX_QUAD;

	wetuwn 0;
}

static const stwuct dmi_system_id hisi_sfc_v3xx_dmi_quiwk_tabwe[]  = {
	{
	.cawwback = hisi_sfc_v3xx_dmi_quiwk,
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Huawei"),
		DMI_MATCH(DMI_PWODUCT_NAME, "D06"),
	},
	},
	{
	.cawwback = hisi_sfc_v3xx_dmi_quiwk,
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Huawei"),
		DMI_MATCH(DMI_PWODUCT_NAME, "TaiShan 2280 V2"),
	},
	},
	{
	.cawwback = hisi_sfc_v3xx_dmi_quiwk,
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Huawei"),
		DMI_MATCH(DMI_PWODUCT_NAME, "TaiShan 200 (Modew 2280)"),
	},
	},
	{}
};

static int hisi_sfc_v3xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hisi_sfc_v3xx_host *host;
	stwuct spi_contwowwew *ctww;
	u32 vewsion, gwb_config;
	int wet;

	ctww = spi_awwoc_host(&pdev->dev, sizeof(*host));
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD |
			  SPI_TX_DUAW | SPI_TX_QUAD;

	ctww->buswidth_ovewwide_bits = hisi_sfc_v3xx_buswidth_ovewwide_bits;

	host = spi_contwowwew_get_devdata(ctww);
	host->dev = dev;

	pwatfowm_set_dwvdata(pdev, host);

	host->wegbase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->wegbase)) {
		wet = PTW_EWW(host->wegbase);
		goto eww_put_host;
	}

	host->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (host->iwq == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto eww_put_host;
	}

	hisi_sfc_v3xx_disabwe_int(host);

	if (host->iwq > 0) {
		wet = devm_wequest_iwq(dev, host->iwq, hisi_sfc_v3xx_isw, 0,
				       "hisi-sfc-v3xx", host);

		if (wet) {
			dev_eww(dev, "faiwed to wequest iwq%d, wet = %d\n", host->iwq, wet);
			host->iwq = 0;
		}
	} ewse {
		host->iwq = 0;
	}

	ctww->bus_num = -1;
	ctww->num_chipsewect = 1;
	ctww->mem_ops = &hisi_sfc_v3xx_mem_ops;

	/*
	 * The addwess mode of the contwowwew is eithew 3 ow 4,
	 * which is indicated by the addwess mode bit in
	 * the gwobaw config wegistew. The wegistew is wead onwy
	 * fow the OS dwivew.
	 */
	gwb_config = weadw(host->wegbase + HISI_SFC_V3XX_GWB_CFG);
	if (gwb_config & HISI_SFC_V3XX_GWB_CFG_CS0_ADDW_MODE)
		host->addwess_mode = 4;
	ewse
		host->addwess_mode = 3;

	vewsion = weadw(host->wegbase + HISI_SFC_V3XX_VEWSION);

	if (vewsion >= 0x351)
		host->max_cmd_dwowd = 64;
	ewse
		host->max_cmd_dwowd = 16;

	wet = devm_spi_wegistew_contwowwew(dev, ctww);
	if (wet)
		goto eww_put_host;

	dev_info(&pdev->dev, "hw vewsion 0x%x, %s mode.\n",
		 vewsion, host->iwq ? "iwq" : "powwing");

	wetuwn 0;

eww_put_host:
	spi_contwowwew_put(ctww);
	wetuwn wet;
}

static const stwuct acpi_device_id hisi_sfc_v3xx_acpi_ids[] = {
	{"HISI0341", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_sfc_v3xx_acpi_ids);

static stwuct pwatfowm_dwivew hisi_sfc_v3xx_spi_dwivew = {
	.dwivew = {
		.name	= "hisi-sfc-v3xx",
		.acpi_match_tabwe = hisi_sfc_v3xx_acpi_ids,
	},
	.pwobe	= hisi_sfc_v3xx_pwobe,
};

static int __init hisi_sfc_v3xx_spi_init(void)
{
	dmi_check_system(hisi_sfc_v3xx_dmi_quiwk_tabwe);

	wetuwn pwatfowm_dwivew_wegistew(&hisi_sfc_v3xx_spi_dwivew);
}

static void __exit hisi_sfc_v3xx_spi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_sfc_v3xx_spi_dwivew);
}

moduwe_init(hisi_sfc_v3xx_spi_init);
moduwe_exit(hisi_sfc_v3xx_spi_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Gawwy <john.gawwy@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon SPI NOW V3XX Fwash Contwowwew Dwivew fow hi16xx chipsets");
