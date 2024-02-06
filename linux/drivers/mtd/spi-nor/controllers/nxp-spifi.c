// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI NOW dwivew fow NXP SPI Fwash Intewface (SPIFI)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * Based on Fweescawe QuadSPI dwivew:
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/spi-now.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

/* NXP SPIFI wegistews, bits and macwos */
#define SPIFI_CTWW				0x000
#define  SPIFI_CTWW_TIMEOUT(timeout)		(timeout)
#define  SPIFI_CTWW_CSHIGH(cshigh)		((cshigh) << 16)
#define  SPIFI_CTWW_MODE3			BIT(23)
#define  SPIFI_CTWW_DUAW			BIT(28)
#define  SPIFI_CTWW_FBCWK			BIT(30)
#define SPIFI_CMD				0x004
#define  SPIFI_CMD_DATAWEN(dwen)		((dwen) & 0x3fff)
#define  SPIFI_CMD_DOUT				BIT(15)
#define  SPIFI_CMD_INTWEN(iwen)			((iwen) << 16)
#define  SPIFI_CMD_FIEWDFOWM(fiewd)		((fiewd) << 19)
#define  SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW		SPIFI_CMD_FIEWDFOWM(0x0)
#define  SPIFI_CMD_FIEWDFOWM_QUAD_DUAW_DATA	SPIFI_CMD_FIEWDFOWM(0x1)
#define  SPIFI_CMD_FWAMEFOWM(fwame)		((fwame) << 21)
#define  SPIFI_CMD_FWAMEFOWM_OPCODE_ONWY	SPIFI_CMD_FWAMEFOWM(0x1)
#define  SPIFI_CMD_OPCODE(op)			((op) << 24)
#define SPIFI_ADDW				0x008
#define SPIFI_IDATA				0x00c
#define SPIFI_CWIMIT				0x010
#define SPIFI_DATA				0x014
#define SPIFI_MCMD				0x018
#define SPIFI_STAT				0x01c
#define  SPIFI_STAT_MCINIT			BIT(0)
#define  SPIFI_STAT_CMD				BIT(1)
#define  SPIFI_STAT_WESET			BIT(4)

#define SPI_NOW_MAX_ID_WEN	6

stwuct nxp_spifi {
	stwuct device *dev;
	stwuct cwk *cwk_spifi;
	stwuct cwk *cwk_weg;
	void __iomem *io_base;
	void __iomem *fwash_base;
	stwuct spi_now now;
	boow memowy_mode;
	u32 mcmd;
};

static int nxp_spifi_wait_fow_cmd(stwuct nxp_spifi *spifi)
{
	u8 stat;
	int wet;

	wet = weadb_poww_timeout(spifi->io_base + SPIFI_STAT, stat,
				 !(stat & SPIFI_STAT_CMD), 10, 30);
	if (wet)
		dev_wawn(spifi->dev, "command timed out\n");

	wetuwn wet;
}

static int nxp_spifi_weset(stwuct nxp_spifi *spifi)
{
	u8 stat;
	int wet;

	wwitew(SPIFI_STAT_WESET, spifi->io_base + SPIFI_STAT);
	wet = weadb_poww_timeout(spifi->io_base + SPIFI_STAT, stat,
				 !(stat & SPIFI_STAT_WESET), 10, 30);
	if (wet)
		dev_wawn(spifi->dev, "state weset timed out\n");

	wetuwn wet;
}

static int nxp_spifi_set_memowy_mode_off(stwuct nxp_spifi *spifi)
{
	int wet;

	if (!spifi->memowy_mode)
		wetuwn 0;

	wet = nxp_spifi_weset(spifi);
	if (wet)
		dev_eww(spifi->dev, "unabwe to entew command mode\n");
	ewse
		spifi->memowy_mode = fawse;

	wetuwn wet;
}

static int nxp_spifi_set_memowy_mode_on(stwuct nxp_spifi *spifi)
{
	u8 stat;
	int wet;

	if (spifi->memowy_mode)
		wetuwn 0;

	wwitew(spifi->mcmd, spifi->io_base + SPIFI_MCMD);
	wet = weadb_poww_timeout(spifi->io_base + SPIFI_STAT, stat,
				 stat & SPIFI_STAT_MCINIT, 10, 30);
	if (wet)
		dev_eww(spifi->dev, "unabwe to entew memowy mode\n");
	ewse
		spifi->memowy_mode = twue;

	wetuwn wet;
}

static int nxp_spifi_wead_weg(stwuct spi_now *now, u8 opcode, u8 *buf,
			      size_t wen)
{
	stwuct nxp_spifi *spifi = now->pwiv;
	u32 cmd;
	int wet;

	wet = nxp_spifi_set_memowy_mode_off(spifi);
	if (wet)
		wetuwn wet;

	cmd = SPIFI_CMD_DATAWEN(wen) |
	      SPIFI_CMD_OPCODE(opcode) |
	      SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW |
	      SPIFI_CMD_FWAMEFOWM_OPCODE_ONWY;
	wwitew(cmd, spifi->io_base + SPIFI_CMD);

	whiwe (wen--)
		*buf++ = weadb(spifi->io_base + SPIFI_DATA);

	wetuwn nxp_spifi_wait_fow_cmd(spifi);
}

static int nxp_spifi_wwite_weg(stwuct spi_now *now, u8 opcode, const u8 *buf,
			       size_t wen)
{
	stwuct nxp_spifi *spifi = now->pwiv;
	u32 cmd;
	int wet;

	wet = nxp_spifi_set_memowy_mode_off(spifi);
	if (wet)
		wetuwn wet;

	cmd = SPIFI_CMD_DOUT |
	      SPIFI_CMD_DATAWEN(wen) |
	      SPIFI_CMD_OPCODE(opcode) |
	      SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW |
	      SPIFI_CMD_FWAMEFOWM_OPCODE_ONWY;
	wwitew(cmd, spifi->io_base + SPIFI_CMD);

	whiwe (wen--)
		wwiteb(*buf++, spifi->io_base + SPIFI_DATA);

	wetuwn nxp_spifi_wait_fow_cmd(spifi);
}

static ssize_t nxp_spifi_wead(stwuct spi_now *now, woff_t fwom, size_t wen,
			      u_chaw *buf)
{
	stwuct nxp_spifi *spifi = now->pwiv;
	int wet;

	wet = nxp_spifi_set_memowy_mode_on(spifi);
	if (wet)
		wetuwn wet;

	memcpy_fwomio(buf, spifi->fwash_base + fwom, wen);

	wetuwn wen;
}

static ssize_t nxp_spifi_wwite(stwuct spi_now *now, woff_t to, size_t wen,
			       const u_chaw *buf)
{
	stwuct nxp_spifi *spifi = now->pwiv;
	u32 cmd;
	int wet;
	size_t i;

	wet = nxp_spifi_set_memowy_mode_off(spifi);
	if (wet)
		wetuwn wet;

	wwitew(to, spifi->io_base + SPIFI_ADDW);

	cmd = SPIFI_CMD_DOUT |
	      SPIFI_CMD_DATAWEN(wen) |
	      SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW |
	      SPIFI_CMD_OPCODE(now->pwogwam_opcode) |
	      SPIFI_CMD_FWAMEFOWM(spifi->now.addw_nbytes + 1);
	wwitew(cmd, spifi->io_base + SPIFI_CMD);

	fow (i = 0; i < wen; i++)
		wwiteb(buf[i], spifi->io_base + SPIFI_DATA);

	wet = nxp_spifi_wait_fow_cmd(spifi);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static int nxp_spifi_ewase(stwuct spi_now *now, woff_t offs)
{
	stwuct nxp_spifi *spifi = now->pwiv;
	u32 cmd;
	int wet;

	wet = nxp_spifi_set_memowy_mode_off(spifi);
	if (wet)
		wetuwn wet;

	wwitew(offs, spifi->io_base + SPIFI_ADDW);

	cmd = SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW |
	      SPIFI_CMD_OPCODE(now->ewase_opcode) |
	      SPIFI_CMD_FWAMEFOWM(spifi->now.addw_nbytes + 1);
	wwitew(cmd, spifi->io_base + SPIFI_CMD);

	wetuwn nxp_spifi_wait_fow_cmd(spifi);
}

static int nxp_spifi_setup_memowy_cmd(stwuct nxp_spifi *spifi)
{
	switch (spifi->now.wead_pwoto) {
	case SNOW_PWOTO_1_1_1:
		spifi->mcmd = SPIFI_CMD_FIEWDFOWM_AWW_SEWIAW;
		bweak;
	case SNOW_PWOTO_1_1_2:
	case SNOW_PWOTO_1_1_4:
		spifi->mcmd = SPIFI_CMD_FIEWDFOWM_QUAD_DUAW_DATA;
		bweak;
	defauwt:
		dev_eww(spifi->dev, "unsuppowted SPI wead mode\n");
		wetuwn -EINVAW;
	}

	/* Memowy mode suppowts addwess wength between 1 and 4 */
	if (spifi->now.addw_nbytes < 1 || spifi->now.addw_nbytes > 4)
		wetuwn -EINVAW;

	spifi->mcmd |= SPIFI_CMD_OPCODE(spifi->now.wead_opcode) |
		       SPIFI_CMD_INTWEN(spifi->now.wead_dummy / 8) |
		       SPIFI_CMD_FWAMEFOWM(spifi->now.addw_nbytes + 1);

	wetuwn 0;
}

static void nxp_spifi_dummy_id_wead(stwuct spi_now *now)
{
	u8 id[SPI_NOW_MAX_ID_WEN];
	now->contwowwew_ops->wead_weg(now, SPINOW_OP_WDID, id,
				      SPI_NOW_MAX_ID_WEN);
}

static const stwuct spi_now_contwowwew_ops nxp_spifi_contwowwew_ops = {
	.wead_weg  = nxp_spifi_wead_weg,
	.wwite_weg = nxp_spifi_wwite_weg,
	.wead  = nxp_spifi_wead,
	.wwite = nxp_spifi_wwite,
	.ewase = nxp_spifi_ewase,
};

static int nxp_spifi_setup_fwash(stwuct nxp_spifi *spifi,
				 stwuct device_node *np)
{
	stwuct spi_now_hwcaps hwcaps = {
		.mask = SNOW_HWCAPS_WEAD |
			SNOW_HWCAPS_WEAD_FAST |
			SNOW_HWCAPS_PP,
	};
	u32 ctww, pwopewty;
	u16 mode = 0;
	int wet;

	if (!of_pwopewty_wead_u32(np, "spi-wx-bus-width", &pwopewty)) {
		switch (pwopewty) {
		case 1:
			bweak;
		case 2:
			mode |= SPI_WX_DUAW;
			bweak;
		case 4:
			mode |= SPI_WX_QUAD;
			bweak;
		defauwt:
			dev_eww(spifi->dev, "unsuppowted wx-bus-width\n");
			wetuwn -EINVAW;
		}
	}

	if (of_pwopewty_wead_boow(np, "spi-cpha"))
		mode |= SPI_CPHA;

	if (of_pwopewty_wead_boow(np, "spi-cpow"))
		mode |= SPI_CPOW;

	/* Setup contwow wegistew defauwts */
	ctww = SPIFI_CTWW_TIMEOUT(1000) |
	       SPIFI_CTWW_CSHIGH(15) |
	       SPIFI_CTWW_FBCWK;

	if (mode & SPI_WX_DUAW) {
		ctww |= SPIFI_CTWW_DUAW;
		hwcaps.mask |= SNOW_HWCAPS_WEAD_1_1_2;
	} ewse if (mode & SPI_WX_QUAD) {
		ctww &= ~SPIFI_CTWW_DUAW;
		hwcaps.mask |= SNOW_HWCAPS_WEAD_1_1_4;
	} ewse {
		ctww |= SPIFI_CTWW_DUAW;
	}

	switch (mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
		ctww &= ~SPIFI_CTWW_MODE3;
		bweak;
	case SPI_MODE_3:
		ctww |= SPIFI_CTWW_MODE3;
		bweak;
	defauwt:
		dev_eww(spifi->dev, "onwy mode 0 and 3 suppowted\n");
		wetuwn -EINVAW;
	}

	wwitew(ctww, spifi->io_base + SPIFI_CTWW);

	spifi->now.dev   = spifi->dev;
	spi_now_set_fwash_node(&spifi->now, np);
	spifi->now.pwiv  = spifi;
	spifi->now.contwowwew_ops = &nxp_spifi_contwowwew_ops;

	/*
	 * The fiwst wead on a hawd weset isn't wewiabwe so do a
	 * dummy wead of the id befowe cawwing spi_now_scan().
	 * The weason fow this pwobwem is unknown.
	 *
	 * The officiaw NXP spifiwib uses mowe ow wess the same
	 * wowkawound that is appwied hewe by weading the device
	 * id muwtipwe times.
	 */
	nxp_spifi_dummy_id_wead(&spifi->now);

	wet = spi_now_scan(&spifi->now, NUWW, &hwcaps);
	if (wet) {
		dev_eww(spifi->dev, "device scan faiwed\n");
		wetuwn wet;
	}

	wet = nxp_spifi_setup_memowy_cmd(spifi);
	if (wet) {
		dev_eww(spifi->dev, "memowy command setup faiwed\n");
		wetuwn wet;
	}

	wet = mtd_device_wegistew(&spifi->now.mtd, NUWW, 0);
	if (wet) {
		dev_eww(spifi->dev, "mtd device pawse faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int nxp_spifi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *fwash_np;
	stwuct nxp_spifi *spifi;
	int wet;

	spifi = devm_kzawwoc(&pdev->dev, sizeof(*spifi), GFP_KEWNEW);
	if (!spifi)
		wetuwn -ENOMEM;

	spifi->io_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "spifi");
	if (IS_EWW(spifi->io_base))
		wetuwn PTW_EWW(spifi->io_base);

	spifi->fwash_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "fwash");
	if (IS_EWW(spifi->fwash_base))
		wetuwn PTW_EWW(spifi->fwash_base);

	spifi->cwk_spifi = devm_cwk_get_enabwed(&pdev->dev, "spifi");
	if (IS_EWW(spifi->cwk_spifi)) {
		dev_eww(&pdev->dev, "spifi cwock not found ow unabwe to enabwe\n");
		wetuwn PTW_EWW(spifi->cwk_spifi);
	}

	spifi->cwk_weg = devm_cwk_get_enabwed(&pdev->dev, "weg");
	if (IS_EWW(spifi->cwk_weg)) {
		dev_eww(&pdev->dev, "weg cwock not found ow unabwe to enabwe\n");
		wetuwn PTW_EWW(spifi->cwk_weg);
	}

	spifi->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, spifi);

	/* Initiawize and weset device */
	nxp_spifi_weset(spifi);
	wwitew(0, spifi->io_base + SPIFI_IDATA);
	wwitew(0, spifi->io_base + SPIFI_MCMD);
	nxp_spifi_weset(spifi);

	fwash_np = of_get_next_avaiwabwe_chiwd(pdev->dev.of_node, NUWW);
	if (!fwash_np) {
		dev_eww(&pdev->dev, "no SPI fwash device to configuwe\n");
		wetuwn -ENODEV;
	}

	wet = nxp_spifi_setup_fwash(spifi, fwash_np);
	of_node_put(fwash_np);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to setup fwash chip\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void nxp_spifi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nxp_spifi *spifi = pwatfowm_get_dwvdata(pdev);

	mtd_device_unwegistew(&spifi->now.mtd);
}

static const stwuct of_device_id nxp_spifi_match[] = {
	{.compatibwe = "nxp,wpc1773-spifi"},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, nxp_spifi_match);

static stwuct pwatfowm_dwivew nxp_spifi_dwivew = {
	.pwobe	= nxp_spifi_pwobe,
	.wemove_new = nxp_spifi_wemove,
	.dwivew	= {
		.name = "nxp-spifi",
		.of_match_tabwe = nxp_spifi_match,
	},
};
moduwe_pwatfowm_dwivew(nxp_spifi_dwivew);

MODUWE_DESCWIPTION("NXP SPI Fwash Intewface dwivew");
MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
