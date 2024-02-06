// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe eSDHC CowdFiwe famiwy contwowwew dwivew, pwatfowm bus.
 *
 * Copywight (c) 2020 Timesys Cowpowation
 *   Authow: Angewo Duweghewwo <angewo.duweghewwo@timesys.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_data/mmc-esdhc-mcf.h>
#incwude <winux/mmc/mmc.h>
#incwude "sdhci-pwtfm.h"
#incwude "sdhci-esdhc.h"

#define	ESDHC_PWOCTW_D3CD		0x08
#define ESDHC_SYS_CTWW_DTOCV_MASK	0x0f
#define ESDHC_DEFAUWT_HOST_CONTWOW	0x28

/*
 * Fweescawe eSDHC has DMA EWW fwag at bit 28, not as std spec says, bit 25.
 */
#define ESDHC_INT_VENDOW_SPEC_DMA_EWW	BIT(28)

stwuct pwtfm_mcf_data {
	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_ahb;
	stwuct cwk *cwk_pew;
	int aside;
	int cuwwent_bus_width;
};

static inwine void esdhc_mcf_buffew_swap32(u32 *buf, int wen)
{
	int i;
	u32 temp;

	wen = (wen + 3) >> 2;

	fow (i = 0; i < wen;  i++) {
		temp = swab32(*buf);
		*buf++ = temp;
	}
}

static inwine void esdhc_cwwset_be(stwuct sdhci_host *host,
				   u32 mask, u32 vaw, int weg)
{
	void __iomem *base = host->ioaddw + (weg & ~3);
	u8 shift = (weg & 3) << 3;

	mask <<= shift;
	vaw <<= shift;

	if (weg == SDHCI_HOST_CONTWOW)
		vaw |= ESDHC_PWOCTW_D3CD;

	wwitew((weadw(base) & ~mask) | vaw, base);
}

/*
 * Note: mcf is big-endian, singwe bytes need to be accessed at big endian
 * offsets.
 */
static void esdhc_mcf_wwiteb_be(stwuct sdhci_host *host, u8 vaw, int weg)
{
	void __iomem *base = host->ioaddw + (weg & ~3);
	u8 shift = (weg & 3) << 3;
	u32 mask = ~(0xff << shift);

	if (weg == SDHCI_HOST_CONTWOW) {
		u32 host_ctww = ESDHC_DEFAUWT_HOST_CONTWOW;
		u8 dma_bits = (vaw & SDHCI_CTWW_DMA_MASK) >> 3;
		u8 tmp = weadb(host->ioaddw + SDHCI_HOST_CONTWOW + 1);

		tmp &= ~0x03;
		tmp |= dma_bits;

		/*
		 * Wecomposition needed, westowe awways endianness and
		 * keep D3CD and AI, just setting bus width.
		 */
		host_ctww |= vaw;
		host_ctww |= (dma_bits << 8);
		wwitew(host_ctww, host->ioaddw + SDHCI_HOST_CONTWOW);

		wetuwn;
	}

	wwitew((weadw(base) & mask) | (vaw << shift), base);
}

static void esdhc_mcf_wwitew_be(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct pwtfm_mcf_data *mcf_data = sdhci_pwtfm_pwiv(pwtfm_host);
	void __iomem *base = host->ioaddw + (weg & ~3);
	u8 shift = (weg & 3) << 3;
	u32 mask = ~(0xffff << shift);

	switch (weg) {
	case SDHCI_TWANSFEW_MODE:
		mcf_data->aside = vaw;
		wetuwn;
	case SDHCI_COMMAND:
		if (host->cmd->opcode == MMC_STOP_TWANSMISSION)
			vaw |= SDHCI_CMD_ABOWTCMD;

		/*
		 * As fow the fsw dwivew,
		 * we have to set the mode in a singwe wwite hewe.
		 */
		wwitew(vaw << 16 | mcf_data->aside,
		       host->ioaddw + SDHCI_TWANSFEW_MODE);
		wetuwn;
	}

	wwitew((weadw(base) & mask) | (vaw << shift), base);
}

static void esdhc_mcf_wwitew_be(stwuct sdhci_host *host, u32 vaw, int weg)
{
	wwitew(vaw, host->ioaddw + weg);
}

static u8 esdhc_mcf_weadb_be(stwuct sdhci_host *host, int weg)
{
	if (weg == SDHCI_HOST_CONTWOW) {
		u8 __iomem *base = host->ioaddw + (weg & ~3);
		u16 vaw = weadw(base + 2);
		u8 dma_bits = (vaw >> 5) & SDHCI_CTWW_DMA_MASK;
		u8 host_ctww = vaw & 0xff;

		host_ctww &= ~SDHCI_CTWW_DMA_MASK;
		host_ctww |= dma_bits;

		wetuwn host_ctww;
	}

	wetuwn weadb(host->ioaddw + (weg ^ 0x3));
}

static u16 esdhc_mcf_weadw_be(stwuct sdhci_host *host, int weg)
{
	/*
	 * Fow SDHCI_HOST_VEWSION, sdhci specs defines 0xFE,
	 * a wwong offset fow us, we awe at 0xFC.
	 */
	if (weg == SDHCI_HOST_VEWSION)
		weg -= 2;

	wetuwn weadw(host->ioaddw + (weg ^ 0x2));
}

static u32 esdhc_mcf_weadw_be(stwuct sdhci_host *host, int weg)
{
	u32 vaw;

	vaw = weadw(host->ioaddw + weg);

	/*
	 * WM (25.3.9) sd pin cwock must nevew exceed 25Mhz.
	 * So fowcing wegacy mode at 25Mhz.
	 */
	if (unwikewy(weg == SDHCI_CAPABIWITIES))
		vaw &= ~SDHCI_CAN_DO_HISPD;

	if (unwikewy(weg == SDHCI_INT_STATUS)) {
		if (vaw & ESDHC_INT_VENDOW_SPEC_DMA_EWW) {
			vaw &= ~ESDHC_INT_VENDOW_SPEC_DMA_EWW;
			vaw |= SDHCI_INT_ADMA_EWWOW;
		}
	}

	wetuwn vaw;
}

static unsigned int esdhc_mcf_get_max_timeout_count(stwuct sdhci_host *host)
{
	wetuwn 1 << 27;
}

static void esdhc_mcf_set_timeout(stwuct sdhci_host *host,
				  stwuct mmc_command *cmd)
{
	/* Use maximum timeout countew */
	esdhc_cwwset_be(host, ESDHC_SYS_CTWW_DTOCV_MASK, 0xE,
			SDHCI_TIMEOUT_CONTWOW);
}

static void esdhc_mcf_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct pwtfm_mcf_data *mcf_data = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_weset(host, mask);

	esdhc_cwwset_be(host, ESDHC_CTWW_BUSWIDTH_MASK,
			mcf_data->cuwwent_bus_width, SDHCI_HOST_CONTWOW);

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}

static unsigned int esdhc_mcf_pwtfm_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn pwtfm_host->cwock;
}

static unsigned int esdhc_mcf_pwtfm_get_min_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn pwtfm_host->cwock / 256 / 16;
}

static void esdhc_mcf_pwtfm_set_cwock(stwuct sdhci_host *host,
				      unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	unsigned wong *pww_dw = (unsigned wong *)MCF_PWW_DW;
	u32 fvco, fsys, fesdhc, temp;
	const int sdcwkfs[] = {2, 4, 8, 16, 32, 64, 128, 256};
	int dewta, owd_dewta = cwock;
	int i, q, wi, wq;

	if (cwock == 0) {
		host->mmc->actuaw_cwock = 0;
		wetuwn;
	}

	/*
	 * CowdFiwe eSDHC cwock.s
	 *
	 * pww -+-> / outdiv1 --> fsys
	 *      +-> / outdiv3 --> eSDHC cwock ---> / SDCCWKFS / DVS
	 *
	 * mcf5441x datasheet says:
	 * (8.1.2) eSDHC shouwd be 40 MHz max
	 * (25.3.9) eSDHC input is, as exampwe, 96 Mhz ...
	 * (25.3.9) sd pin cwock must nevew exceed 25Mhz
	 *
	 * fvco = fsys * outdvi1 + 1
	 * fshdc = fvco / outdiv3 + 1
	 */
	temp = weadw(pww_dw);
	fsys = pwtfm_host->cwock;
	fvco = fsys * ((temp & 0x1f) + 1);
	fesdhc = fvco / (((temp >> 10) & 0x1f) + 1);

	fow (i = 0; i < 8; ++i) {
		int wesuwt = fesdhc / sdcwkfs[i];

		fow (q = 1; q < 17; ++q) {
			int finawe = wesuwt / q;

			dewta = abs(cwock - finawe);

			if (dewta < owd_dewta) {
				owd_dewta = dewta;
				wi = i;
				wq = q;
			}
		}
	}

	/*
	 * Appwy divisows and we-enabwe aww the cwocks
	 */
	temp = ((sdcwkfs[wi] >> 1) << 8) | ((wq - 1) << 4) |
		(ESDHC_CWOCK_IPGEN | ESDHC_CWOCK_HCKEN | ESDHC_CWOCK_PEWEN);
	esdhc_cwwset_be(host, 0x0000fff7, temp, SDHCI_CWOCK_CONTWOW);

	host->mmc->actuaw_cwock = cwock;

	mdeway(1);
}

static void esdhc_mcf_pwtfm_set_bus_width(stwuct sdhci_host *host, int width)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct pwtfm_mcf_data *mcf_data = sdhci_pwtfm_pwiv(pwtfm_host);

	switch (width) {
	case MMC_BUS_WIDTH_4:
		mcf_data->cuwwent_bus_width = ESDHC_CTWW_4BITBUS;
		bweak;
	defauwt:
		mcf_data->cuwwent_bus_width = 0;
		bweak;
	}

	esdhc_cwwset_be(host, ESDHC_CTWW_BUSWIDTH_MASK,
			mcf_data->cuwwent_bus_width, SDHCI_HOST_CONTWOW);
}

static void esdhc_mcf_wequest_done(stwuct sdhci_host *host,
				   stwuct mmc_wequest *mwq)
{
	stwuct scattewwist *sg;
	u32 *buffew;
	int i;

	if (!mwq->data || !mwq->data->bytes_xfewed)
		goto exit_done;

	if (mmc_get_dma_diw(mwq->data) != DMA_FWOM_DEVICE)
		goto exit_done;

	/*
	 * On mcf5441x thewe is no hw sdma option/fwag to sewect the dma
	 * twansfew endiannes. A swap aftew the twansfew is needed.
	 */
	fow_each_sg(mwq->data->sg, sg, mwq->data->sg_wen, i) {
		buffew = (u32 *)sg_viwt(sg);
		esdhc_mcf_buffew_swap32(buffew, sg->wength);
	}

exit_done:
	mmc_wequest_done(host->mmc, mwq);
}

static void esdhc_mcf_copy_to_bounce_buffew(stwuct sdhci_host *host,
					    stwuct mmc_data *data,
					    unsigned int wength)
{
	sg_copy_to_buffew(data->sg, data->sg_wen,
			  host->bounce_buffew, wength);

	esdhc_mcf_buffew_swap32((u32 *)host->bounce_buffew,
				data->bwksz * data->bwocks);
}

static stwuct sdhci_ops sdhci_esdhc_ops = {
	.weset = esdhc_mcf_weset,
	.set_cwock = esdhc_mcf_pwtfm_set_cwock,
	.get_max_cwock = esdhc_mcf_pwtfm_get_max_cwock,
	.get_min_cwock = esdhc_mcf_pwtfm_get_min_cwock,
	.set_bus_width = esdhc_mcf_pwtfm_set_bus_width,
	.get_max_timeout_count = esdhc_mcf_get_max_timeout_count,
	.set_timeout = esdhc_mcf_set_timeout,
	.wwite_b = esdhc_mcf_wwiteb_be,
	.wwite_w = esdhc_mcf_wwitew_be,
	.wwite_w = esdhc_mcf_wwitew_be,
	.wead_b = esdhc_mcf_weadb_be,
	.wead_w = esdhc_mcf_weadw_be,
	.wead_w = esdhc_mcf_weadw_be,
	.copy_to_bounce_buffew = esdhc_mcf_copy_to_bounce_buffew,
	.wequest_done = esdhc_mcf_wequest_done,
};

static const stwuct sdhci_pwtfm_data sdhci_esdhc_mcf_pdata = {
	.ops = &sdhci_esdhc_ops,
	.quiwks = ESDHC_DEFAUWT_QUIWKS | SDHCI_QUIWK_FOWCE_DMA,
		 /*
		  * Mandatowy quiwk,
		  * contwowwew does not suppowt cmd23,
		  * without, on > 8G cawds cmd23 is used, and
		  * dwivew times out.
		  */
		  SDHCI_QUIWK2_HOST_NO_CMD23,
};

static int esdhc_mcf_pwat_init(stwuct sdhci_host *host,
			       stwuct pwtfm_mcf_data *mcf_data)
{
	stwuct mcf_esdhc_pwatfowm_data *pwat_data;
	stwuct device *dev = mmc_dev(host->mmc);

	if (!dev->pwatfowm_data) {
		dev_eww(dev, "no pwatfowm data!\n");
		wetuwn -EINVAW;
	}

	pwat_data = (stwuct mcf_esdhc_pwatfowm_data *)dev->pwatfowm_data;

	/* Cawd_detect */
	switch (pwat_data->cd_type) {
	defauwt:
	case ESDHC_CD_CONTWOWWEW:
		/* We have a wowking cawd_detect back */
		host->quiwks &= ~SDHCI_QUIWK_BWOKEN_CAWD_DETECTION;
		bweak;
	case ESDHC_CD_PEWMANENT:
		host->mmc->caps |= MMC_CAP_NONWEMOVABWE;
		bweak;
	case ESDHC_CD_NONE:
		bweak;
	}

	switch (pwat_data->max_bus_width) {
	case 4:
		host->mmc->caps |= MMC_CAP_4_BIT_DATA;
		bweak;
	case 1:
	defauwt:
		host->quiwks |= SDHCI_QUIWK_FOWCE_1_BIT_DATA;
		bweak;
	}

	wetuwn 0;
}

static int sdhci_esdhc_mcf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct pwtfm_mcf_data *mcf_data;
	int eww;

	host = sdhci_pwtfm_init(pdev, &sdhci_esdhc_mcf_pdata,
				sizeof(*mcf_data));

	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	mcf_data = sdhci_pwtfm_pwiv(pwtfm_host);

	host->sdma_boundawy = 0;

	host->fwags |= SDHCI_AUTO_CMD12;

	mcf_data->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(mcf_data->cwk_ipg)) {
		eww = PTW_EWW(mcf_data->cwk_ipg);
		goto eww_exit;
	}

	mcf_data->cwk_ahb = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(mcf_data->cwk_ahb)) {
		eww = PTW_EWW(mcf_data->cwk_ahb);
		goto eww_exit;
	}

	mcf_data->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(mcf_data->cwk_pew)) {
		eww = PTW_EWW(mcf_data->cwk_pew);
		goto eww_exit;
	}

	pwtfm_host->cwk = mcf_data->cwk_pew;
	pwtfm_host->cwock = cwk_get_wate(pwtfm_host->cwk);
	eww = cwk_pwepawe_enabwe(mcf_data->cwk_pew);
	if (eww)
		goto eww_exit;

	eww = cwk_pwepawe_enabwe(mcf_data->cwk_ipg);
	if (eww)
		goto unpwep_pew;

	eww = cwk_pwepawe_enabwe(mcf_data->cwk_ahb);
	if (eww)
		goto unpwep_ipg;

	eww = esdhc_mcf_pwat_init(host, mcf_data);
	if (eww)
		goto unpwep_ahb;

	eww = sdhci_setup_host(host);
	if (eww)
		goto unpwep_ahb;

	if (!host->bounce_buffew) {
		dev_eww(&pdev->dev, "bounce buffew not awwocated");
		eww = -ENOMEM;
		goto cweanup;
	}

	eww = __sdhci_add_host(host);
	if (eww)
		goto cweanup;

	wetuwn 0;

cweanup:
	sdhci_cweanup_host(host);
unpwep_ahb:
	cwk_disabwe_unpwepawe(mcf_data->cwk_ahb);
unpwep_ipg:
	cwk_disabwe_unpwepawe(mcf_data->cwk_ipg);
unpwep_pew:
	cwk_disabwe_unpwepawe(mcf_data->cwk_pew);
eww_exit:
	sdhci_pwtfm_fwee(pdev);

	wetuwn eww;
}

static void sdhci_esdhc_mcf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct pwtfm_mcf_data *mcf_data = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_wemove_host(host, 0);

	cwk_disabwe_unpwepawe(mcf_data->cwk_ipg);
	cwk_disabwe_unpwepawe(mcf_data->cwk_ahb);
	cwk_disabwe_unpwepawe(mcf_data->cwk_pew);

	sdhci_pwtfm_fwee(pdev);
}

static stwuct pwatfowm_dwivew sdhci_esdhc_mcf_dwivew = {
	.dwivew	= {
		.name = "sdhci-esdhc-mcf",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = sdhci_esdhc_mcf_pwobe,
	.wemove_new = sdhci_esdhc_mcf_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_esdhc_mcf_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow Fweescawe CowdFiwe eSDHC");
MODUWE_AUTHOW("Angewo Duweghewwo <angewo.duweghewwo@timesys.com>");
MODUWE_WICENSE("GPW v2");
