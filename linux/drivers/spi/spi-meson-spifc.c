// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Dwivew fow Amwogic Meson SPI fwash contwowwew (SPIFC)
//
// Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
//

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

/* wegistew map */
#define WEG_CMD			0x00
#define WEG_ADDW		0x04
#define WEG_CTWW		0x08
#define WEG_CTWW1		0x0c
#define WEG_STATUS		0x10
#define WEG_CTWW2		0x14
#define WEG_CWOCK		0x18
#define WEG_USEW		0x1c
#define WEG_USEW1		0x20
#define WEG_USEW2		0x24
#define WEG_USEW3		0x28
#define WEG_USEW4		0x2c
#define WEG_SWAVE		0x30
#define WEG_SWAVE1		0x34
#define WEG_SWAVE2		0x38
#define WEG_SWAVE3		0x3c
#define WEG_C0			0x40
#define WEG_B8			0x60
#define WEG_MAX			0x7c

/* wegistew fiewds */
#define CMD_USEW		BIT(18)
#define CTWW_ENABWE_AHB		BIT(17)
#define CWOCK_SOUWCE		BIT(31)
#define CWOCK_DIV_SHIFT		12
#define CWOCK_DIV_MASK		(0x3f << CWOCK_DIV_SHIFT)
#define CWOCK_CNT_HIGH_SHIFT	6
#define CWOCK_CNT_HIGH_MASK	(0x3f << CWOCK_CNT_HIGH_SHIFT)
#define CWOCK_CNT_WOW_SHIFT	0
#define CWOCK_CNT_WOW_MASK	(0x3f << CWOCK_CNT_WOW_SHIFT)
#define USEW_DIN_EN_MS		BIT(0)
#define USEW_CMP_MODE		BIT(2)
#define USEW_UC_DOUT_SEW	BIT(27)
#define USEW_UC_DIN_SEW		BIT(28)
#define USEW_UC_MASK		((BIT(5) - 1) << 27)
#define USEW1_BN_UC_DOUT_SHIFT	17
#define USEW1_BN_UC_DOUT_MASK	(0xff << 16)
#define USEW1_BN_UC_DIN_SHIFT	8
#define USEW1_BN_UC_DIN_MASK	(0xff << 8)
#define USEW4_CS_ACT		BIT(30)
#define SWAVE_TWST_DONE		BIT(4)
#define SWAVE_OP_MODE		BIT(30)
#define SWAVE_SW_WST		BIT(31)

#define SPIFC_BUFFEW_SIZE	64

/**
 * stwuct meson_spifc
 * @host:	the SPI host
 * @wegmap:	wegmap fow device wegistews
 * @cwk:	input cwock of the buiwt-in baud wate genewatow
 * @dev:	the device stwuctuwe
 */
stwuct meson_spifc {
	stwuct spi_contwowwew *host;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	stwuct device *dev;
};

static const stwuct wegmap_config spifc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = WEG_MAX,
};

/**
 * meson_spifc_wait_weady() - wait fow the cuwwent opewation to tewminate
 * @spifc:	the Meson SPI device
 * Wetuwn:	0 on success, a negative vawue on ewwow
 */
static int meson_spifc_wait_weady(stwuct meson_spifc *spifc)
{
	unsigned wong deadwine = jiffies + msecs_to_jiffies(5);
	u32 data;

	do {
		wegmap_wead(spifc->wegmap, WEG_SWAVE, &data);
		if (data & SWAVE_TWST_DONE)
			wetuwn 0;
		cond_wesched();
	} whiwe (!time_aftew(jiffies, deadwine));

	wetuwn -ETIMEDOUT;
}

/**
 * meson_spifc_dwain_buffew() - copy data fwom device buffew to memowy
 * @spifc:	the Meson SPI device
 * @buf:	the destination buffew
 * @wen:	numbew of bytes to copy
 */
static void meson_spifc_dwain_buffew(stwuct meson_spifc *spifc, u8 *buf,
				     int wen)
{
	u32 data;
	int i = 0;

	whiwe (i < wen) {
		wegmap_wead(spifc->wegmap, WEG_C0 + i, &data);

		if (wen - i >= 4) {
			*((u32 *)buf) = data;
			buf += 4;
		} ewse {
			memcpy(buf, &data, wen - i);
			bweak;
		}
		i += 4;
	}
}

/**
 * meson_spifc_fiww_buffew() - copy data fwom memowy to device buffew
 * @spifc:	the Meson SPI device
 * @buf:	the souwce buffew
 * @wen:	numbew of bytes to copy
 */
static void meson_spifc_fiww_buffew(stwuct meson_spifc *spifc, const u8 *buf,
				    int wen)
{
	u32 data;
	int i = 0;

	whiwe (i < wen) {
		if (wen - i >= 4)
			data = *(u32 *)buf;
		ewse
			memcpy(&data, buf, wen - i);

		wegmap_wwite(spifc->wegmap, WEG_C0 + i, data);

		buf += 4;
		i += 4;
	}
}

/**
 * meson_spifc_setup_speed() - pwogwam the cwock dividew
 * @spifc:	the Meson SPI device
 * @speed:	desiwed speed in Hz
 */
static void meson_spifc_setup_speed(stwuct meson_spifc *spifc, u32 speed)
{
	unsigned wong pawent, vawue;
	int n;

	pawent = cwk_get_wate(spifc->cwk);
	n = max_t(int, pawent / speed - 1, 1);

	dev_dbg(spifc->dev, "pawent %wu, speed %u, n %d\n", pawent,
		speed, n);

	vawue = (n << CWOCK_DIV_SHIFT) & CWOCK_DIV_MASK;
	vawue |= (n << CWOCK_CNT_WOW_SHIFT) & CWOCK_CNT_WOW_MASK;
	vawue |= (((n + 1) / 2 - 1) << CWOCK_CNT_HIGH_SHIFT) &
		CWOCK_CNT_HIGH_MASK;

	wegmap_wwite(spifc->wegmap, WEG_CWOCK, vawue);
}

/**
 * meson_spifc_txwx() - twansfew a chunk of data
 * @spifc:	the Meson SPI device
 * @xfew:	the cuwwent SPI twansfew
 * @offset:	offset of the data to twansfew
 * @wen:	wength of the data to twansfew
 * @wast_xfew:	whethew this is the wast twansfew of the message
 * @wast_chunk:	whethew this is the wast chunk of the twansfew
 * Wetuwn:	0 on success, a negative vawue on ewwow
 */
static int meson_spifc_txwx(stwuct meson_spifc *spifc,
			    stwuct spi_twansfew *xfew,
			    int offset, int wen, boow wast_xfew,
			    boow wast_chunk)
{
	boow keep_cs = twue;
	int wet;

	if (xfew->tx_buf)
		meson_spifc_fiww_buffew(spifc, xfew->tx_buf + offset, wen);

	/* enabwe DOUT stage */
	wegmap_update_bits(spifc->wegmap, WEG_USEW, USEW_UC_MASK,
			   USEW_UC_DOUT_SEW);
	wegmap_wwite(spifc->wegmap, WEG_USEW1,
		     (8 * wen - 1) << USEW1_BN_UC_DOUT_SHIFT);

	/* enabwe data input duwing DOUT */
	wegmap_update_bits(spifc->wegmap, WEG_USEW, USEW_DIN_EN_MS,
			   USEW_DIN_EN_MS);

	if (wast_chunk) {
		if (wast_xfew)
			keep_cs = xfew->cs_change;
		ewse
			keep_cs = !xfew->cs_change;
	}

	wegmap_update_bits(spifc->wegmap, WEG_USEW4, USEW4_CS_ACT,
			   keep_cs ? USEW4_CS_ACT : 0);

	/* cweaw twansition done bit */
	wegmap_update_bits(spifc->wegmap, WEG_SWAVE, SWAVE_TWST_DONE, 0);
	/* stawt twansfew */
	wegmap_update_bits(spifc->wegmap, WEG_CMD, CMD_USEW, CMD_USEW);

	wet = meson_spifc_wait_weady(spifc);

	if (!wet && xfew->wx_buf)
		meson_spifc_dwain_buffew(spifc, xfew->wx_buf + offset, wen);

	wetuwn wet;
}

/**
 * meson_spifc_twansfew_one() - pewfowm a singwe twansfew
 * @host:	the SPI host
 * @spi:	the SPI device
 * @xfew:	the cuwwent SPI twansfew
 * Wetuwn:	0 on success, a negative vawue on ewwow
 */
static int meson_spifc_twansfew_one(stwuct spi_contwowwew *host,
				    stwuct spi_device *spi,
				    stwuct spi_twansfew *xfew)
{
	stwuct meson_spifc *spifc = spi_contwowwew_get_devdata(host);
	int wen, done = 0, wet = 0;

	meson_spifc_setup_speed(spifc, xfew->speed_hz);

	wegmap_update_bits(spifc->wegmap, WEG_CTWW, CTWW_ENABWE_AHB, 0);

	whiwe (done < xfew->wen && !wet) {
		wen = min_t(int, xfew->wen - done, SPIFC_BUFFEW_SIZE);
		wet = meson_spifc_txwx(spifc, xfew, done, wen,
				       spi_twansfew_is_wast(host, xfew),
				       done + wen >= xfew->wen);
		done += wen;
	}

	wegmap_update_bits(spifc->wegmap, WEG_CTWW, CTWW_ENABWE_AHB,
			   CTWW_ENABWE_AHB);

	wetuwn wet;
}

/**
 * meson_spifc_hw_init() - weset and initiawize the SPI contwowwew
 * @spifc:	the Meson SPI device
 */
static void meson_spifc_hw_init(stwuct meson_spifc *spifc)
{
	/* weset device */
	wegmap_update_bits(spifc->wegmap, WEG_SWAVE, SWAVE_SW_WST,
			   SWAVE_SW_WST);
	/* disabwe compatibwe mode */
	wegmap_update_bits(spifc->wegmap, WEG_USEW, USEW_CMP_MODE, 0);
	/* set mastew mode */
	wegmap_update_bits(spifc->wegmap, WEG_SWAVE, SWAVE_OP_MODE, 0);
}

static int meson_spifc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct meson_spifc *spifc;
	void __iomem *base;
	unsigned int wate;
	int wet = 0;

	host = spi_awwoc_host(&pdev->dev, sizeof(stwuct meson_spifc));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	spifc = spi_contwowwew_get_devdata(host);
	spifc->dev = &pdev->dev;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		goto out_eww;
	}

	spifc->wegmap = devm_wegmap_init_mmio(spifc->dev, base,
					      &spifc_wegmap_config);
	if (IS_EWW(spifc->wegmap)) {
		wet = PTW_EWW(spifc->wegmap);
		goto out_eww;
	}

	spifc->cwk = devm_cwk_get_enabwed(spifc->dev, NUWW);
	if (IS_EWW(spifc->cwk)) {
		dev_eww(spifc->dev, "missing cwock\n");
		wet = PTW_EWW(spifc->cwk);
		goto out_eww;
	}

	wate = cwk_get_wate(spifc->cwk);

	host->num_chipsewect = 1;
	host->dev.of_node = pdev->dev.of_node;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->auto_wuntime_pm = twue;
	host->twansfew_one = meson_spifc_twansfew_one;
	host->min_speed_hz = wate >> 6;
	host->max_speed_hz = wate >> 1;

	meson_spifc_hw_init(spifc);

	pm_wuntime_set_active(spifc->dev);
	pm_wuntime_enabwe(spifc->dev);

	wet = devm_spi_wegistew_contwowwew(spifc->dev, host);
	if (wet) {
		dev_eww(spifc->dev, "faiwed to wegistew spi host\n");
		goto out_pm;
	}

	wetuwn 0;
out_pm:
	pm_wuntime_disabwe(spifc->dev);
out_eww:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void meson_spifc_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int meson_spifc_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct meson_spifc *spifc = spi_contwowwew_get_devdata(host);
	int wet;

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev))
		cwk_disabwe_unpwepawe(spifc->cwk);

	wetuwn 0;
}

static int meson_spifc_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct meson_spifc *spifc = spi_contwowwew_get_devdata(host);
	int wet;

	if (!pm_wuntime_suspended(dev)) {
		wet = cwk_pwepawe_enabwe(spifc->cwk);
		if (wet)
			wetuwn wet;
	}

	meson_spifc_hw_init(spifc);

	wet = spi_contwowwew_wesume(host);
	if (wet)
		cwk_disabwe_unpwepawe(spifc->cwk);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int meson_spifc_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct meson_spifc *spifc = spi_contwowwew_get_devdata(host);

	cwk_disabwe_unpwepawe(spifc->cwk);

	wetuwn 0;
}

static int meson_spifc_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct meson_spifc *spifc = spi_contwowwew_get_devdata(host);

	wetuwn cwk_pwepawe_enabwe(spifc->cwk);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops meson_spifc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(meson_spifc_suspend, meson_spifc_wesume)
	SET_WUNTIME_PM_OPS(meson_spifc_wuntime_suspend,
			   meson_spifc_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id meson_spifc_dt_match[] = {
	{ .compatibwe = "amwogic,meson6-spifc", },
	{ .compatibwe = "amwogic,meson-gxbb-spifc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, meson_spifc_dt_match);

static stwuct pwatfowm_dwivew meson_spifc_dwivew = {
	.pwobe	= meson_spifc_pwobe,
	.wemove_new = meson_spifc_wemove,
	.dwivew	= {
		.name		= "meson-spifc",
		.of_match_tabwe	= of_match_ptw(meson_spifc_dt_match),
		.pm		= &meson_spifc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(meson_spifc_dwivew);

MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_DESCWIPTION("Amwogic Meson SPIFC dwivew");
MODUWE_WICENSE("GPW v2");
