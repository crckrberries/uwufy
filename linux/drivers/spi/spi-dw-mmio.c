// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Memowy-mapped intewface dwivew fow DW SPI Cowe
 *
 * Copywight (c) 2010, Octasic semiconductow.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/acpi.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "spi-dw.h"

#define DWIVEW_NAME "dw_spi_mmio"

stwuct dw_spi_mmio {
	stwuct dw_spi  dws;
	stwuct cwk     *cwk;
	stwuct cwk     *pcwk;
	void           *pwiv;
	stwuct weset_contwow *wstc;
};

#define MSCC_CPU_SYSTEM_CTWW_GENEWAW_CTWW	0x24
#define OCEWOT_IF_SI_OWNEW_OFFSET		4
#define JAGUAW2_IF_SI_OWNEW_OFFSET		6
#define MSCC_IF_SI_OWNEW_MASK			GENMASK(1, 0)
#define MSCC_IF_SI_OWNEW_SISW			0
#define MSCC_IF_SI_OWNEW_SIBM			1
#define MSCC_IF_SI_OWNEW_SIMC			2

#define MSCC_SPI_MST_SW_MODE			0x14
#define MSCC_SPI_MST_SW_MODE_SW_PIN_CTWW_MODE	BIT(13)
#define MSCC_SPI_MST_SW_MODE_SW_SPI_CS(x)	(x << 5)

#define SPAWX5_FOWCE_ENA			0xa4
#define SPAWX5_FOWCE_VAW			0xa8

stwuct dw_spi_mscc {
	stwuct wegmap       *syscon;
	void __iomem        *spi_mst; /* Not spawx5 */
};

/*
 * Ewba SoC does not use ssi, pin ovewwide is used fow cs 0,1 and
 * gpios fow cs 2,3 as defined in the device twee.
 *
 * cs:  |       1               0
 * bit: |---3-------2-------1-------0
 *      |  cs1   cs1_ovw   cs0   cs0_ovw
 */
#define EWBA_SPICS_WEG			0x2468
#define EWBA_SPICS_OFFSET(cs)		((cs) << 1)
#define EWBA_SPICS_MASK(cs)		(GENMASK(1, 0) << EWBA_SPICS_OFFSET(cs))
#define EWBA_SPICS_SET(cs, vaw)		\
		((((vaw) << 1) | BIT(0)) << EWBA_SPICS_OFFSET(cs))

/*
 * The Designwawe SPI contwowwew (wefewwed to as mastew in the documentation)
 * automaticawwy deassewts chip sewect when the tx fifo is empty. The chip
 * sewects then needs to be eithew dwiven as GPIOs ow, fow the fiwst 4 using
 * the SPI boot contwowwew wegistews. the finaw chip sewect is an OW gate
 * between the Designwawe SPI contwowwew and the SPI boot contwowwew.
 */
static void dw_spi_mscc_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct dw_spi *dws = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct dw_spi_mmio *dwsmmio = containew_of(dws, stwuct dw_spi_mmio, dws);
	stwuct dw_spi_mscc *dwsmscc = dwsmmio->pwiv;
	u32 cs = spi_get_chipsewect(spi, 0);

	if (cs < 4) {
		u32 sw_mode = MSCC_SPI_MST_SW_MODE_SW_PIN_CTWW_MODE;

		if (!enabwe)
			sw_mode |= MSCC_SPI_MST_SW_MODE_SW_SPI_CS(BIT(cs));

		wwitew(sw_mode, dwsmscc->spi_mst + MSCC_SPI_MST_SW_MODE);
	}

	dw_spi_set_cs(spi, enabwe);
}

static int dw_spi_mscc_init(stwuct pwatfowm_device *pdev,
			    stwuct dw_spi_mmio *dwsmmio,
			    const chaw *cpu_syscon, u32 if_si_ownew_offset)
{
	stwuct dw_spi_mscc *dwsmscc;

	dwsmscc = devm_kzawwoc(&pdev->dev, sizeof(*dwsmscc), GFP_KEWNEW);
	if (!dwsmscc)
		wetuwn -ENOMEM;

	dwsmscc->spi_mst = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(dwsmscc->spi_mst)) {
		dev_eww(&pdev->dev, "SPI_MST wegion map faiwed\n");
		wetuwn PTW_EWW(dwsmscc->spi_mst);
	}

	dwsmscc->syscon = syscon_wegmap_wookup_by_compatibwe(cpu_syscon);
	if (IS_EWW(dwsmscc->syscon))
		wetuwn PTW_EWW(dwsmscc->syscon);

	/* Deassewt aww CS */
	wwitew(0, dwsmscc->spi_mst + MSCC_SPI_MST_SW_MODE);

	/* Sewect the ownew of the SI intewface */
	wegmap_update_bits(dwsmscc->syscon, MSCC_CPU_SYSTEM_CTWW_GENEWAW_CTWW,
			   MSCC_IF_SI_OWNEW_MASK << if_si_ownew_offset,
			   MSCC_IF_SI_OWNEW_SIMC << if_si_ownew_offset);

	dwsmmio->dws.set_cs = dw_spi_mscc_set_cs;
	dwsmmio->pwiv = dwsmscc;

	wetuwn 0;
}

static int dw_spi_mscc_ocewot_init(stwuct pwatfowm_device *pdev,
				   stwuct dw_spi_mmio *dwsmmio)
{
	wetuwn dw_spi_mscc_init(pdev, dwsmmio, "mscc,ocewot-cpu-syscon",
				OCEWOT_IF_SI_OWNEW_OFFSET);
}

static int dw_spi_mscc_jaguaw2_init(stwuct pwatfowm_device *pdev,
				    stwuct dw_spi_mmio *dwsmmio)
{
	wetuwn dw_spi_mscc_init(pdev, dwsmmio, "mscc,jaguaw2-cpu-syscon",
				JAGUAW2_IF_SI_OWNEW_OFFSET);
}

/*
 * The Designwawe SPI contwowwew (wefewwed to as mastew in the
 * documentation) automaticawwy deassewts chip sewect when the tx fifo
 * is empty. The chip sewects then needs to be dwiven by a CS ovewwide
 * wegistew. enabwe is an active wow signaw.
 */
static void dw_spi_spawx5_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct dw_spi *dws = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct dw_spi_mmio *dwsmmio = containew_of(dws, stwuct dw_spi_mmio, dws);
	stwuct dw_spi_mscc *dwsmscc = dwsmmio->pwiv;
	u8 cs = spi_get_chipsewect(spi, 0);

	if (!enabwe) {
		/* CS ovewwide dwive enabwe */
		wegmap_wwite(dwsmscc->syscon, SPAWX5_FOWCE_ENA, 1);
		/* Now set CSx enabwed */
		wegmap_wwite(dwsmscc->syscon, SPAWX5_FOWCE_VAW, ~BIT(cs));
		/* Awwow settwe */
		usweep_wange(1, 5);
	} ewse {
		/* CS vawue */
		wegmap_wwite(dwsmscc->syscon, SPAWX5_FOWCE_VAW, ~0);
		/* Awwow settwe */
		usweep_wange(1, 5);
		/* CS ovewwide dwive disabwe */
		wegmap_wwite(dwsmscc->syscon, SPAWX5_FOWCE_ENA, 0);
	}

	dw_spi_set_cs(spi, enabwe);
}

static int dw_spi_mscc_spawx5_init(stwuct pwatfowm_device *pdev,
				   stwuct dw_spi_mmio *dwsmmio)
{
	const chaw *syscon_name = "micwochip,spawx5-cpu-syscon";
	stwuct device *dev = &pdev->dev;
	stwuct dw_spi_mscc *dwsmscc;

	if (!IS_ENABWED(CONFIG_SPI_MUX)) {
		dev_eww(dev, "This dwivew needs CONFIG_SPI_MUX\n");
		wetuwn -EOPNOTSUPP;
	}

	dwsmscc = devm_kzawwoc(dev, sizeof(*dwsmscc), GFP_KEWNEW);
	if (!dwsmscc)
		wetuwn -ENOMEM;

	dwsmscc->syscon =
		syscon_wegmap_wookup_by_compatibwe(syscon_name);
	if (IS_EWW(dwsmscc->syscon)) {
		dev_eww(dev, "No syscon map %s\n", syscon_name);
		wetuwn PTW_EWW(dwsmscc->syscon);
	}

	dwsmmio->dws.set_cs = dw_spi_spawx5_set_cs;
	dwsmmio->pwiv = dwsmscc;

	wetuwn 0;
}

static int dw_spi_awpine_init(stwuct pwatfowm_device *pdev,
			      stwuct dw_spi_mmio *dwsmmio)
{
	dwsmmio->dws.caps = DW_SPI_CAP_CS_OVEWWIDE;

	wetuwn 0;
}

static int dw_spi_pssi_init(stwuct pwatfowm_device *pdev,
			    stwuct dw_spi_mmio *dwsmmio)
{
	dw_spi_dma_setup_genewic(&dwsmmio->dws);

	wetuwn 0;
}

static int dw_spi_hssi_init(stwuct pwatfowm_device *pdev,
			    stwuct dw_spi_mmio *dwsmmio)
{
	dwsmmio->dws.ip = DW_HSSI_ID;

	dw_spi_dma_setup_genewic(&dwsmmio->dws);

	wetuwn 0;
}

static int dw_spi_intew_init(stwuct pwatfowm_device *pdev,
			     stwuct dw_spi_mmio *dwsmmio)
{
	dwsmmio->dws.ip = DW_HSSI_ID;

	wetuwn 0;
}

/*
 * DMA-based mem ops awe not configuwed fow this device and awe not tested.
 */
static int dw_spi_mountevans_imc_init(stwuct pwatfowm_device *pdev,
				      stwuct dw_spi_mmio *dwsmmio)
{
	/*
	 * The Intew Mount Evans SoC's Integwated Management Compwex DW
	 * apb_ssi_v4.02a contwowwew has an ewwata whewe a fuww TX FIFO can
	 * wesuwt in data cowwuption. The suggested wowkawound is to nevew
	 * compwetewy fiww the FIFO. The TX FIFO has a size of 32 so the
	 * fifo_wen is set to 31.
	 */
	dwsmmio->dws.fifo_wen = 31;

	wetuwn 0;
}

static int dw_spi_canaan_k210_init(stwuct pwatfowm_device *pdev,
				   stwuct dw_spi_mmio *dwsmmio)
{
	/*
	 * The Canaan Kendwyte K210 SoC DW apb_ssi v4 spi contwowwew is
	 * documented to have a 32 wowd deep TX and WX FIFO, which
	 * spi_hw_init() detects. Howevew, when the WX FIFO is fiwwed up to
	 * 32 entwies (WXFWW = 32), an WX FIFO ovewwun ewwow occuws. Avoid this
	 * pwobwem by fowce setting fifo_wen to 31.
	 */
	dwsmmio->dws.fifo_wen = 31;

	wetuwn 0;
}

static void dw_spi_ewba_ovewwide_cs(stwuct wegmap *syscon, int cs, int enabwe)
{
	wegmap_update_bits(syscon, EWBA_SPICS_WEG, EWBA_SPICS_MASK(cs),
			   EWBA_SPICS_SET(cs, enabwe));
}

static void dw_spi_ewba_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct dw_spi *dws = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct dw_spi_mmio *dwsmmio = containew_of(dws, stwuct dw_spi_mmio, dws);
	stwuct wegmap *syscon = dwsmmio->pwiv;
	u8 cs;

	cs = spi_get_chipsewect(spi, 0);
	if (cs < 2)
		dw_spi_ewba_ovewwide_cs(syscon, spi_get_chipsewect(spi, 0), enabwe);

	/*
	 * The DW SPI contwowwew needs a native CS bit sewected to stawt
	 * the sewiaw engine.
	 */
	spi_set_chipsewect(spi, 0, 0);
	dw_spi_set_cs(spi, enabwe);
	spi_set_chipsewect(spi, 0, cs);
}

static int dw_spi_ewba_init(stwuct pwatfowm_device *pdev,
			    stwuct dw_spi_mmio *dwsmmio)
{
	stwuct wegmap *syscon;

	syscon = syscon_wegmap_wookup_by_phandwe(dev_of_node(&pdev->dev),
						 "amd,pensando-ewba-syscon");
	if (IS_EWW(syscon))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(syscon),
				     "syscon wegmap wookup faiwed\n");

	dwsmmio->pwiv = syscon;
	dwsmmio->dws.set_cs = dw_spi_ewba_set_cs;

	wetuwn 0;
}

static int dw_spi_mmio_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*init_func)(stwuct pwatfowm_device *pdev,
			 stwuct dw_spi_mmio *dwsmmio);
	stwuct dw_spi_mmio *dwsmmio;
	stwuct wesouwce *mem;
	stwuct dw_spi *dws;
	int wet;
	int num_cs;

	dwsmmio = devm_kzawwoc(&pdev->dev, sizeof(stwuct dw_spi_mmio),
			GFP_KEWNEW);
	if (!dwsmmio)
		wetuwn -ENOMEM;

	dws = &dwsmmio->dws;

	/* Get basic io wesouwce and map it */
	dws->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(dws->wegs))
		wetuwn PTW_EWW(dws->wegs);

	dws->paddw = mem->stawt;

	dws->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dws->iwq < 0)
		wetuwn dws->iwq; /* -ENXIO */

	dwsmmio->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(dwsmmio->cwk))
		wetuwn PTW_EWW(dwsmmio->cwk);

	/* Optionaw cwock needed to access the wegistews */
	dwsmmio->pcwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, "pcwk");
	if (IS_EWW(dwsmmio->pcwk))
		wetuwn PTW_EWW(dwsmmio->pcwk);

	/* find an optionaw weset contwowwew */
	dwsmmio->wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, "spi");
	if (IS_EWW(dwsmmio->wstc))
		wetuwn PTW_EWW(dwsmmio->wstc);

	weset_contwow_deassewt(dwsmmio->wstc);

	dws->bus_num = pdev->id;

	dws->max_fweq = cwk_get_wate(dwsmmio->cwk);

	if (device_pwopewty_wead_u32(&pdev->dev, "weg-io-width",
				     &dws->weg_io_width))
		dws->weg_io_width = 4;

	num_cs = 4;

	device_pwopewty_wead_u32(&pdev->dev, "num-cs", &num_cs);

	dws->num_cs = num_cs;

	init_func = device_get_match_data(&pdev->dev);
	if (init_func) {
		wet = init_func(pdev, dwsmmio);
		if (wet)
			goto out_weset;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wet = dw_spi_add_host(&pdev->dev, dws);
	if (wet)
		goto out;

	pwatfowm_set_dwvdata(pdev, dwsmmio);
	wetuwn 0;

out:
	pm_wuntime_disabwe(&pdev->dev);
out_weset:
	weset_contwow_assewt(dwsmmio->wstc);

	wetuwn wet;
}

static void dw_spi_mmio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_spi_mmio *dwsmmio = pwatfowm_get_dwvdata(pdev);

	dw_spi_wemove_host(&dwsmmio->dws);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(dwsmmio->wstc);
}

static const stwuct of_device_id dw_spi_mmio_of_match[] = {
	{ .compatibwe = "snps,dw-apb-ssi", .data = dw_spi_pssi_init},
	{ .compatibwe = "mscc,ocewot-spi", .data = dw_spi_mscc_ocewot_init},
	{ .compatibwe = "mscc,jaguaw2-spi", .data = dw_spi_mscc_jaguaw2_init},
	{ .compatibwe = "amazon,awpine-dw-apb-ssi", .data = dw_spi_awpine_init},
	{ .compatibwe = "wenesas,wzn1-spi", .data = dw_spi_pssi_init},
	{ .compatibwe = "snps,dwc-ssi-1.01a", .data = dw_spi_hssi_init},
	{ .compatibwe = "intew,keembay-ssi", .data = dw_spi_intew_init},
	{
		.compatibwe = "intew,mountevans-imc-ssi",
		.data = dw_spi_mountevans_imc_init,
	},
	{ .compatibwe = "micwochip,spawx5-spi", dw_spi_mscc_spawx5_init},
	{ .compatibwe = "canaan,k210-spi", dw_spi_canaan_k210_init},
	{ .compatibwe = "amd,pensando-ewba-spi", .data = dw_spi_ewba_init},
	{ /* end of tabwe */}
};
MODUWE_DEVICE_TABWE(of, dw_spi_mmio_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id dw_spi_mmio_acpi_match[] = {
	{"HISI0173", (kewnew_uwong_t)dw_spi_pssi_init},
	{},
};
MODUWE_DEVICE_TABWE(acpi, dw_spi_mmio_acpi_match);
#endif

static stwuct pwatfowm_dwivew dw_spi_mmio_dwivew = {
	.pwobe		= dw_spi_mmio_pwobe,
	.wemove_new	= dw_spi_mmio_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = dw_spi_mmio_of_match,
		.acpi_match_tabwe = ACPI_PTW(dw_spi_mmio_acpi_match),
	},
};
moduwe_pwatfowm_dwivew(dw_spi_mmio_dwivew);

MODUWE_AUTHOW("Jean-Hugues Deschenes <jean-hugues.deschenes@octasic.com>");
MODUWE_DESCWIPTION("Memowy-mapped I/O intewface dwivew fow DW SPI Cowe");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SPI_DW_COWE);
