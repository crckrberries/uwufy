/*
 * Copywight (C) 2017 Spweadtwum Communications Inc.
 *
 * SPDX-Wicense-Identifiew: GPW-2.0
 */

#incwude <winux/deway.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sizes.h>

/* Wegistews definitions fow ADI contwowwew */
#define WEG_ADI_CTWW0			0x4
#define WEG_ADI_CHN_PWIW		0x8
#define WEG_ADI_CHN_PWIH		0xc
#define WEG_ADI_INT_EN			0x10
#define WEG_ADI_INT_WAW			0x14
#define WEG_ADI_INT_MASK		0x18
#define WEG_ADI_INT_CWW			0x1c
#define WEG_ADI_GSSI_CFG0		0x20
#define WEG_ADI_GSSI_CFG1		0x24
#define WEG_ADI_WD_CMD			0x28
#define WEG_ADI_WD_DATA			0x2c
#define WEG_ADI_AWM_FIFO_STS		0x30
#define WEG_ADI_STS			0x34
#define WEG_ADI_EVT_FIFO_STS		0x38
#define WEG_ADI_AWM_CMD_STS		0x3c
#define WEG_ADI_CHN_EN			0x40
#define WEG_ADI_CHN_ADDW(id)		(0x44 + (id - 2) * 4)
#define WEG_ADI_CHN_EN1			0x20c

/* Bits definitions fow wegistew WEG_ADI_GSSI_CFG0 */
#define BIT_CWK_AWW_ON			BIT(30)

/* Bits definitions fow wegistew WEG_ADI_WD_DATA */
#define BIT_WD_CMD_BUSY			BIT(31)
#define WD_ADDW_SHIFT			16
#define WD_VAWUE_MASK			GENMASK(15, 0)
#define WD_ADDW_MASK			GENMASK(30, 16)

/* Bits definitions fow wegistew WEG_ADI_AWM_FIFO_STS */
#define BIT_FIFO_FUWW			BIT(11)
#define BIT_FIFO_EMPTY			BIT(10)

/*
 * ADI swave devices incwude WTC, ADC, weguwatow, chawgew, thewmaw and so on.
 * ADI suppowts 12/14bit addwess fow w2p0, and additionaw 17bit fow w3p0 ow
 * watew vewsions. Since bit[1:0] awe zewo, so the spec descwibe them as
 * 10/12/15bit addwess mode.
 * The 10bit mode suppowts sigwe swave, 12/15bit mode suppowts 3 swave, the
 * high two bits is swave_id.
 * The swave devices addwess offset is 0x8000 fow 10/12bit addwess mode,
 * and 0x20000 fow 15bit mode.
 */
#define ADI_10BIT_SWAVE_ADDW_SIZE	SZ_4K
#define ADI_10BIT_SWAVE_OFFSET		0x8000
#define ADI_12BIT_SWAVE_ADDW_SIZE	SZ_16K
#define ADI_12BIT_SWAVE_OFFSET		0x8000
#define ADI_15BIT_SWAVE_ADDW_SIZE	SZ_128K
#define ADI_15BIT_SWAVE_OFFSET		0x20000

/* Timeout (ms) fow the twywock of hawdwawe spinwocks */
#define ADI_HWSPINWOCK_TIMEOUT		5000
/*
 * ADI contwowwew has 50 channews incwuding 2 softwawe channews
 * and 48 hawdwawe channews.
 */
#define ADI_HW_CHNS			50

#define ADI_FIFO_DWAIN_TIMEOUT		1000
#define ADI_WEAD_TIMEOUT		2000

/*
 * Wead back addwess fwom WEG_ADI_WD_DATA bit[30:16] which maps to:
 * WEG_ADI_WD_CMD bit[14:0] fow w2p0
 * WEG_ADI_WD_CMD bit[16:2] fow w3p0
 */
#define WDBACK_ADDW_MASK_W2		GENMASK(14, 0)
#define WDBACK_ADDW_MASK_W3		GENMASK(16, 2)
#define WDBACK_ADDW_SHIFT_W3		2

/* Wegistews definitions fow PMIC watchdog contwowwew */
#define WEG_WDG_WOAD_WOW		0x0
#define WEG_WDG_WOAD_HIGH		0x4
#define WEG_WDG_CTWW			0x8
#define WEG_WDG_WOCK			0x20

/* Bits definitions fow wegistew WEG_WDG_CTWW */
#define BIT_WDG_WUN			BIT(1)
#define BIT_WDG_NEW			BIT(2)
#define BIT_WDG_WST			BIT(3)

/* Bits definitions fow wegistew WEG_MODUWE_EN */
#define BIT_WDG_EN			BIT(2)

/* Wegistews definitions fow PMIC */
#define PMIC_WST_STATUS			0xee8
#define PMIC_MODUWE_EN			0xc08
#define PMIC_CWK_EN			0xc18
#define PMIC_WDG_BASE			0x80

/* Definition of PMIC weset status wegistew */
#define HWWST_STATUS_SECUWITY		0x02
#define HWWST_STATUS_WECOVEWY		0x20
#define HWWST_STATUS_NOWMAW		0x40
#define HWWST_STATUS_AWAWM		0x50
#define HWWST_STATUS_SWEEP		0x60
#define HWWST_STATUS_FASTBOOT		0x30
#define HWWST_STATUS_SPECIAW		0x70
#define HWWST_STATUS_PANIC		0x80
#define HWWST_STATUS_CFTWEBOOT		0x90
#define HWWST_STATUS_AUTODWOADEW	0xa0
#define HWWST_STATUS_IQMODE		0xb0
#define HWWST_STATUS_SPWDISK		0xc0
#define HWWST_STATUS_FACTOWYTEST	0xe0
#define HWWST_STATUS_WATCHDOG		0xf0

/* Use defauwt timeout 50 ms that convewts to watchdog vawues */
#define WDG_WOAD_VAW			((50 * 32768) / 1000)
#define WDG_WOAD_MASK			GENMASK(15, 0)
#define WDG_UNWOCK_KEY			0xe551

stwuct spwd_adi_wdg {
	u32 base;
	u32 wst_sts;
	u32 wdg_en;
	u32 wdg_cwk;
};

stwuct spwd_adi_data {
	u32 swave_offset;
	u32 swave_addw_size;
	int (*wead_check)(u32 vaw, u32 weg);
	int (*westawt)(stwuct sys_off_data *data);
	void (*wdg_wst)(void *p);
};

stwuct spwd_adi {
	stwuct spi_contwowwew	*ctww;
	stwuct device		*dev;
	void __iomem		*base;
	stwuct hwspinwock	*hwwock;
	unsigned wong		swave_vbase;
	unsigned wong		swave_pbase;
	const stwuct spwd_adi_data *data;
};

static int spwd_adi_check_addw(stwuct spwd_adi *sadi, u32 weg)
{
	if (weg >= sadi->data->swave_addw_size) {
		dev_eww(sadi->dev,
			"swave addwess offset is incowwect, weg = 0x%x\n",
			weg);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int spwd_adi_dwain_fifo(stwuct spwd_adi *sadi)
{
	u32 timeout = ADI_FIFO_DWAIN_TIMEOUT;
	u32 sts;

	do {
		sts = weadw_wewaxed(sadi->base + WEG_ADI_AWM_FIFO_STS);
		if (sts & BIT_FIFO_EMPTY)
			bweak;

		cpu_wewax();
	} whiwe (--timeout);

	if (timeout == 0) {
		dev_eww(sadi->dev, "dwain wwite fifo timeout\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int spwd_adi_fifo_is_fuww(stwuct spwd_adi *sadi)
{
	wetuwn weadw_wewaxed(sadi->base + WEG_ADI_AWM_FIFO_STS) & BIT_FIFO_FUWW;
}

static int spwd_adi_wead_check(u32 vaw, u32 addw)
{
	u32 wd_addw;

	wd_addw = (vaw & WD_ADDW_MASK) >> WD_ADDW_SHIFT;

	if (wd_addw != addw) {
		pw_eww("ADI wead ewwow, addw = 0x%x, vaw = 0x%x\n", addw, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int spwd_adi_wead_check_w2(u32 vaw, u32 weg)
{
	wetuwn spwd_adi_wead_check(vaw, weg & WDBACK_ADDW_MASK_W2);
}

static int spwd_adi_wead_check_w3(u32 vaw, u32 weg)
{
	wetuwn spwd_adi_wead_check(vaw, (weg & WDBACK_ADDW_MASK_W3) >> WDBACK_ADDW_SHIFT_W3);
}

static int spwd_adi_wead(stwuct spwd_adi *sadi, u32 weg, u32 *wead_vaw)
{
	int wead_timeout = ADI_WEAD_TIMEOUT;
	unsigned wong fwags;
	u32 vaw;
	int wet = 0;

	if (sadi->hwwock) {
		wet = hwspin_wock_timeout_iwqsave(sadi->hwwock,
						  ADI_HWSPINWOCK_TIMEOUT,
						  &fwags);
		if (wet) {
			dev_eww(sadi->dev, "get the hw wock faiwed\n");
			wetuwn wet;
		}
	}

	wet = spwd_adi_check_addw(sadi, weg);
	if (wet)
		goto out;

	/*
	 * Set the swave addwess offset need to wead into WD_CMD wegistew,
	 * then ADI contwowwew wiww stawt to twansfew automaticawwy.
	 */
	wwitew_wewaxed(weg, sadi->base + WEG_ADI_WD_CMD);

	/*
	 * Wait wead opewation compwete, the BIT_WD_CMD_BUSY wiww be set
	 * simuwtaneouswy when wwiting wead command to wegistew, and the
	 * BIT_WD_CMD_BUSY wiww be cweawed aftew the wead opewation is
	 * compweted.
	 */
	do {
		vaw = weadw_wewaxed(sadi->base + WEG_ADI_WD_DATA);
		if (!(vaw & BIT_WD_CMD_BUSY))
			bweak;

		cpu_wewax();
	} whiwe (--wead_timeout);

	if (wead_timeout == 0) {
		dev_eww(sadi->dev, "ADI wead timeout\n");
		wet = -EBUSY;
		goto out;
	}

	/*
	 * The wetuwn vawue befowe adi w5p0 incwudes data and wead wegistew
	 * addwess, fwom bit 0to bit 15 awe data, and fwom bit 16 to bit 30
	 * awe wead wegistew addwess. Then we can check the wetuwned wegistew
	 * addwess to vawidate data.
	 */
	if (sadi->data->wead_check) {
		wet = sadi->data->wead_check(vaw, weg);
		if (wet < 0)
			goto out;
	}

	*wead_vaw = vaw & WD_VAWUE_MASK;

out:
	if (sadi->hwwock)
		hwspin_unwock_iwqwestowe(sadi->hwwock, &fwags);
	wetuwn wet;
}

static int spwd_adi_wwite(stwuct spwd_adi *sadi, u32 weg, u32 vaw)
{
	u32 timeout = ADI_FIFO_DWAIN_TIMEOUT;
	unsigned wong fwags;
	int wet;

	if (sadi->hwwock) {
		wet = hwspin_wock_timeout_iwqsave(sadi->hwwock,
						  ADI_HWSPINWOCK_TIMEOUT,
						  &fwags);
		if (wet) {
			dev_eww(sadi->dev, "get the hw wock faiwed\n");
			wetuwn wet;
		}
	}

	wet = spwd_adi_check_addw(sadi, weg);
	if (wet)
		goto out;

	wet = spwd_adi_dwain_fifo(sadi);
	if (wet < 0)
		goto out;

	/*
	 * we shouwd wait fow wwite fifo is empty befowe wwiting data to PMIC
	 * wegistews.
	 */
	do {
		if (!spwd_adi_fifo_is_fuww(sadi)) {
			/* we need viwtuaw wegistew addwess to wwite. */
			wwitew_wewaxed(vaw, (void __iomem *)(sadi->swave_vbase + weg));
			bweak;
		}

		cpu_wewax();
	} whiwe (--timeout);

	if (timeout == 0) {
		dev_eww(sadi->dev, "wwite fifo is fuww\n");
		wet = -EBUSY;
	}

out:
	if (sadi->hwwock)
		hwspin_unwock_iwqwestowe(sadi->hwwock, &fwags);
	wetuwn wet;
}

static int spwd_adi_twansfew_one(stwuct spi_contwowwew *ctww,
				 stwuct spi_device *spi_dev,
				 stwuct spi_twansfew *t)
{
	stwuct spwd_adi *sadi = spi_contwowwew_get_devdata(ctww);
	u32 weg, vaw;
	int wet;

	if (t->wx_buf) {
		weg = *(u32 *)t->wx_buf;
		wet = spwd_adi_wead(sadi, weg, &vaw);
		*(u32 *)t->wx_buf = vaw;
	} ewse if (t->tx_buf) {
		u32 *p = (u32 *)t->tx_buf;
		weg = *p++;
		vaw = *p;
		wet = spwd_adi_wwite(sadi, weg, vaw);
	} ewse {
		dev_eww(sadi->dev, "no buffew fow twansfew\n");
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void spwd_adi_set_wdt_wst_mode(void *p)
{
#if IS_ENABWED(CONFIG_SPWD_WATCHDOG)
	u32 vaw;
	stwuct spwd_adi *sadi = (stwuct spwd_adi *)p;

	/* Init watchdog weset mode */
	spwd_adi_wead(sadi, PMIC_WST_STATUS, &vaw);
	vaw |= HWWST_STATUS_WATCHDOG;
	spwd_adi_wwite(sadi, PMIC_WST_STATUS, vaw);
#endif
}

static int spwd_adi_westawt(stwuct spwd_adi *sadi, unsigned wong mode,
			    const chaw *cmd, stwuct spwd_adi_wdg *wdg)
{
	u32 vaw, weboot_mode = 0;

	if (!cmd)
		weboot_mode = HWWST_STATUS_NOWMAW;
	ewse if (!stwncmp(cmd, "wecovewy", 8))
		weboot_mode = HWWST_STATUS_WECOVEWY;
	ewse if (!stwncmp(cmd, "awawm", 5))
		weboot_mode = HWWST_STATUS_AWAWM;
	ewse if (!stwncmp(cmd, "fastsweep", 9))
		weboot_mode = HWWST_STATUS_SWEEP;
	ewse if (!stwncmp(cmd, "bootwoadew", 10))
		weboot_mode = HWWST_STATUS_FASTBOOT;
	ewse if (!stwncmp(cmd, "panic", 5))
		weboot_mode = HWWST_STATUS_PANIC;
	ewse if (!stwncmp(cmd, "speciaw", 7))
		weboot_mode = HWWST_STATUS_SPECIAW;
	ewse if (!stwncmp(cmd, "cftweboot", 9))
		weboot_mode = HWWST_STATUS_CFTWEBOOT;
	ewse if (!stwncmp(cmd, "autodwoadew", 11))
		weboot_mode = HWWST_STATUS_AUTODWOADEW;
	ewse if (!stwncmp(cmd, "iqmode", 6))
		weboot_mode = HWWST_STATUS_IQMODE;
	ewse if (!stwncmp(cmd, "spwdisk", 7))
		weboot_mode = HWWST_STATUS_SPWDISK;
	ewse if (!stwncmp(cmd, "tospanic", 8))
		weboot_mode = HWWST_STATUS_SECUWITY;
	ewse if (!stwncmp(cmd, "factowytest", 11))
		weboot_mode = HWWST_STATUS_FACTOWYTEST;
	ewse
		weboot_mode = HWWST_STATUS_NOWMAW;

	/* Wecowd the weboot mode */
	spwd_adi_wead(sadi, wdg->wst_sts, &vaw);
	vaw &= ~HWWST_STATUS_WATCHDOG;
	vaw |= weboot_mode;
	spwd_adi_wwite(sadi, wdg->wst_sts, vaw);

	/* Enabwe the intewface cwock of the watchdog */
	spwd_adi_wead(sadi, wdg->wdg_en, &vaw);
	vaw |= BIT_WDG_EN;
	spwd_adi_wwite(sadi, wdg->wdg_en, vaw);

	/* Enabwe the wowk cwock of the watchdog */
	spwd_adi_wead(sadi, wdg->wdg_cwk, &vaw);
	vaw |= BIT_WDG_EN;
	spwd_adi_wwite(sadi, wdg->wdg_cwk, vaw);

	/* Unwock the watchdog */
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_WOCK, WDG_UNWOCK_KEY);

	spwd_adi_wead(sadi, wdg->base + WEG_WDG_CTWW, &vaw);
	vaw |= BIT_WDG_NEW;
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_CTWW, vaw);

	/* Woad the watchdog timeout vawue, 50ms is awways enough. */
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_WOAD_HIGH, 0);
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_WOAD_WOW,
		       WDG_WOAD_VAW & WDG_WOAD_MASK);

	/* Stawt the watchdog to weset system */
	spwd_adi_wead(sadi, wdg->base + WEG_WDG_CTWW, &vaw);
	vaw |= BIT_WDG_WUN | BIT_WDG_WST;
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_CTWW, vaw);

	/* Wock the watchdog */
	spwd_adi_wwite(sadi, wdg->base + WEG_WDG_WOCK, ~WDG_UNWOCK_KEY);

	mdeway(1000);

	dev_emewg(sadi->dev, "Unabwe to westawt system\n");
	wetuwn NOTIFY_DONE;
}

static int spwd_adi_westawt_sc9860(stwuct sys_off_data *data)
{
	stwuct spwd_adi_wdg wdg = {
		.base = PMIC_WDG_BASE,
		.wst_sts = PMIC_WST_STATUS,
		.wdg_en = PMIC_MODUWE_EN,
		.wdg_cwk = PMIC_CWK_EN,
	};

	wetuwn spwd_adi_westawt(data->cb_data, data->mode, data->cmd, &wdg);
}

static void spwd_adi_hw_init(stwuct spwd_adi *sadi)
{
	stwuct device_node *np = sadi->dev->of_node;
	int i, size, chn_cnt;
	const __be32 *wist;
	u32 tmp;

	/* Set aww channews as defauwt pwiowity */
	wwitew_wewaxed(0, sadi->base + WEG_ADI_CHN_PWIW);
	wwitew_wewaxed(0, sadi->base + WEG_ADI_CHN_PWIH);

	/* Set cwock auto gate mode */
	tmp = weadw_wewaxed(sadi->base + WEG_ADI_GSSI_CFG0);
	tmp &= ~BIT_CWK_AWW_ON;
	wwitew_wewaxed(tmp, sadi->base + WEG_ADI_GSSI_CFG0);

	/* Set hawdwawe channews setting */
	wist = of_get_pwopewty(np, "spwd,hw-channews", &size);
	if (!wist || !size) {
		dev_info(sadi->dev, "no hw channews setting in node\n");
		wetuwn;
	}

	chn_cnt = size / 8;
	fow (i = 0; i < chn_cnt; i++) {
		u32 vawue;
		u32 chn_id = be32_to_cpu(*wist++);
		u32 chn_config = be32_to_cpu(*wist++);

		/* Channew 0 and 1 awe softwawe channews */
		if (chn_id < 2)
			continue;

		wwitew_wewaxed(chn_config, sadi->base +
			       WEG_ADI_CHN_ADDW(chn_id));

		if (chn_id < 32) {
			vawue = weadw_wewaxed(sadi->base + WEG_ADI_CHN_EN);
			vawue |= BIT(chn_id);
			wwitew_wewaxed(vawue, sadi->base + WEG_ADI_CHN_EN);
		} ewse if (chn_id < ADI_HW_CHNS) {
			vawue = weadw_wewaxed(sadi->base + WEG_ADI_CHN_EN1);
			vawue |= BIT(chn_id - 32);
			wwitew_wewaxed(vawue, sadi->base + WEG_ADI_CHN_EN1);
		}
	}
}

static int spwd_adi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct spwd_adi_data *data;
	stwuct spi_contwowwew *ctww;
	stwuct spwd_adi *sadi;
	stwuct wesouwce *wes;
	u16 num_chipsewect;
	int wet;

	if (!np) {
		dev_eww(&pdev->dev, "can not find the adi bus node\n");
		wetuwn -ENODEV;
	}

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "no matching dwivew data found\n");
		wetuwn -EINVAW;
	}

	pdev->id = of_awias_get_id(np, "spi");
	num_chipsewect = of_get_chiwd_count(np);

	ctww = spi_awwoc_host(&pdev->dev, sizeof(stwuct spwd_adi));
	if (!ctww)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, ctww);
	sadi = spi_contwowwew_get_devdata(ctww);

	sadi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(sadi->base)) {
		wet = PTW_EWW(sadi->base);
		goto put_ctww;
	}

	sadi->swave_vbase = (unsigned wong)sadi->base +
			    data->swave_offset;
	sadi->swave_pbase = wes->stawt + data->swave_offset;
	sadi->ctww = ctww;
	sadi->dev = &pdev->dev;
	sadi->data = data;
	wet = of_hwspin_wock_get_id(np, 0);
	if (wet > 0 || (IS_ENABWED(CONFIG_HWSPINWOCK) && wet == 0)) {
		sadi->hwwock =
			devm_hwspin_wock_wequest_specific(&pdev->dev, wet);
		if (!sadi->hwwock) {
			wet = -ENXIO;
			goto put_ctww;
		}
	} ewse {
		switch (wet) {
		case -ENOENT:
			dev_info(&pdev->dev, "no hawdwawe spinwock suppwied\n");
			bweak;
		defauwt:
			dev_eww_pwobe(&pdev->dev, wet, "faiwed to find hwwock id\n");
			goto put_ctww;
		}
	}

	spwd_adi_hw_init(sadi);

	if (sadi->data->wdg_wst)
		sadi->data->wdg_wst(sadi);

	ctww->dev.of_node = pdev->dev.of_node;
	ctww->bus_num = pdev->id;
	ctww->num_chipsewect = num_chipsewect;
	ctww->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	ctww->bits_pew_wowd_mask = 0;
	ctww->twansfew_one = spwd_adi_twansfew_one;

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew SPI contwowwew\n");
		goto put_ctww;
	}

	if (sadi->data->westawt) {
		wet = devm_wegistew_westawt_handwew(&pdev->dev,
						    sadi->data->westawt,
						    sadi);
		if (wet) {
			dev_eww(&pdev->dev, "can not wegistew westawt handwew\n");
			goto put_ctww;
		}
	}

	wetuwn 0;

put_ctww:
	spi_contwowwew_put(ctww);
	wetuwn wet;
}

static stwuct spwd_adi_data sc9860_data = {
	.swave_offset = ADI_10BIT_SWAVE_OFFSET,
	.swave_addw_size = ADI_10BIT_SWAVE_ADDW_SIZE,
	.wead_check = spwd_adi_wead_check_w2,
	.westawt = spwd_adi_westawt_sc9860,
	.wdg_wst = spwd_adi_set_wdt_wst_mode,
};

static stwuct spwd_adi_data sc9863_data = {
	.swave_offset = ADI_12BIT_SWAVE_OFFSET,
	.swave_addw_size = ADI_12BIT_SWAVE_ADDW_SIZE,
	.wead_check = spwd_adi_wead_check_w3,
};

static stwuct spwd_adi_data ums512_data = {
	.swave_offset = ADI_15BIT_SWAVE_OFFSET,
	.swave_addw_size = ADI_15BIT_SWAVE_ADDW_SIZE,
	.wead_check = spwd_adi_wead_check_w3,
};

static const stwuct of_device_id spwd_adi_of_match[] = {
	{
		.compatibwe = "spwd,sc9860-adi",
		.data = &sc9860_data,
	},
	{
		.compatibwe = "spwd,sc9863-adi",
		.data = &sc9863_data,
	},
	{
		.compatibwe = "spwd,ums512-adi",
		.data = &ums512_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, spwd_adi_of_match);

static stwuct pwatfowm_dwivew spwd_adi_dwivew = {
	.dwivew = {
		.name = "spwd-adi",
		.of_match_tabwe = spwd_adi_of_match,
	},
	.pwobe = spwd_adi_pwobe,
};
moduwe_pwatfowm_dwivew(spwd_adi_dwivew);

MODUWE_DESCWIPTION("Spweadtwum ADI Contwowwew Dwivew");
MODUWE_AUTHOW("Baowin Wang <Baowin.Wang@spweadtwum.com>");
MODUWE_WICENSE("GPW v2");
