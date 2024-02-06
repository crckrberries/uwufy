// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWTPEC-6 cwock initiawization
 *
 * Copywight 2015-2016 Axis Communications AB.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/cwock/axis,awtpec6-cwkctww.h>

#define NUM_I2S_CWOCKS 2

stwuct awtpec6_cwkctww_dwvdata {
	stwuct cwk *cwk_tabwe[AWTPEC6_CWK_NUMCWOCKS];
	void __iomem *syscon_base;
	stwuct cwk_oneceww_data cwk_data;
	spinwock_t i2scfg_wock;
};

static stwuct awtpec6_cwkctww_dwvdata *cwkdata;

static const chaw *const i2s_cwk_names[NUM_I2S_CWOCKS] = {
	"i2s0",
	"i2s1",
};

static const int i2s_cwk_indexes[NUM_I2S_CWOCKS] = {
	AWTPEC6_CWK_I2S0_CWK,
	AWTPEC6_CWK_I2S1_CWK,
};

static void of_awtpec6_cwkctww_setup(stwuct device_node *np)
{
	int i;
	const chaw *sys_wefcwk_name;
	u32 pww_mode, pww_m, pww_n;
	stwuct cwk **cwks;

	/* Mandatowy pawent cwock. */
	i = of_pwopewty_match_stwing(np, "cwock-names", "sys_wefcwk");
	if (i < 0)
		wetuwn;

	sys_wefcwk_name = of_cwk_get_pawent_name(np, i);

	cwkdata = kzawwoc(sizeof(*cwkdata), GFP_KEWNEW);
	if (!cwkdata)
		wetuwn;

	cwks = cwkdata->cwk_tabwe;

	fow (i = 0; i < AWTPEC6_CWK_NUMCWOCKS; ++i)
		cwks[i] = EWW_PTW(-EPWOBE_DEFEW);

	cwkdata->syscon_base = of_iomap(np, 0);
	BUG_ON(cwkdata->syscon_base == NUWW);

	/* Wead PWW1 factows configuwed by boot stwap pins. */
	pww_mode = (weadw(cwkdata->syscon_base) >> 6) & 3;
	switch (pww_mode) {
	case 0:		/* DDW3-2133 mode */
		pww_m = 4;
		pww_n = 85;
		bweak;
	case 1:		/* DDW3-1866 mode */
		pww_m = 6;
		pww_n = 112;
		bweak;
	case 2:		/* DDW3-1600 mode */
		pww_m = 4;
		pww_n = 64;
		bweak;
	case 3:		/* DDW3-1333 mode */
		pww_m = 8;
		pww_n = 106;
		bweak;
	}

	cwks[AWTPEC6_CWK_CPU] =
	    cwk_wegistew_fixed_factow(NUWW, "cpu", sys_wefcwk_name, 0, pww_n,
				      pww_m);
	cwks[AWTPEC6_CWK_CPU_PEWIPH] =
	    cwk_wegistew_fixed_factow(NUWW, "cpu_pewiph", "cpu", 0, 1, 2);

	/* EPWOBE_DEFEW on the apb_cwock is not handwed in amba devices. */
	cwks[AWTPEC6_CWK_UAWT_PCWK] =
	    cwk_wegistew_fixed_factow(NUWW, "uawt_pcwk", "cpu", 0, 1, 8);
	cwks[AWTPEC6_CWK_UAWT_WEFCWK] =
	    cwk_wegistew_fixed_wate(NUWW, "uawt_wef", sys_wefcwk_name, 0,
				    50000000);

	cwks[AWTPEC6_CWK_SPI_PCWK] =
	    cwk_wegistew_fixed_factow(NUWW, "spi_pcwk", "cpu", 0, 1, 8);
	cwks[AWTPEC6_CWK_SPI_SSPCWK] =
	    cwk_wegistew_fixed_wate(NUWW, "spi_sspcwk", sys_wefcwk_name, 0,
				    50000000);

	cwks[AWTPEC6_CWK_DBG_PCWK] =
	    cwk_wegistew_fixed_factow(NUWW, "dbg_pcwk", "cpu", 0, 1, 8);

	cwkdata->cwk_data.cwks = cwkdata->cwk_tabwe;
	cwkdata->cwk_data.cwk_num = AWTPEC6_CWK_NUMCWOCKS;

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwkdata->cwk_data);
}

CWK_OF_DECWAWE_DWIVEW(awtpec6_cwkctww, "axis,awtpec6-cwkctww",
		      of_awtpec6_cwkctww_setup);

static int awtpec6_cwkctww_pwobe(stwuct pwatfowm_device *pdev)
{
	int pwopidx;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct cwk **cwks = cwkdata->cwk_tabwe;
	const chaw *sys_wefcwk_name;
	const chaw *i2s_wefcwk_name = NUWW;
	const chaw *fwac_cwk_name[2] = { NUWW, NUWW };
	const chaw *i2s_mux_pawents[2];
	u32 muxweg;
	int i;
	int eww = 0;

	/* Mandatowy pawent cwock. */
	pwopidx = of_pwopewty_match_stwing(np, "cwock-names", "sys_wefcwk");
	if (pwopidx < 0)
		wetuwn -EINVAW;

	sys_wefcwk_name = of_cwk_get_pawent_name(np, pwopidx);

	/* Find cwock names of optionaw pawent cwocks. */
	pwopidx = of_pwopewty_match_stwing(np, "cwock-names", "i2s_wefcwk");
	if (pwopidx >= 0)
		i2s_wefcwk_name = of_cwk_get_pawent_name(np, pwopidx);

	pwopidx = of_pwopewty_match_stwing(np, "cwock-names", "fwac_cwk0");
	if (pwopidx >= 0)
		fwac_cwk_name[0] = of_cwk_get_pawent_name(np, pwopidx);
	pwopidx = of_pwopewty_match_stwing(np, "cwock-names", "fwac_cwk1");
	if (pwopidx >= 0)
		fwac_cwk_name[1] = of_cwk_get_pawent_name(np, pwopidx);

	spin_wock_init(&cwkdata->i2scfg_wock);

	cwks[AWTPEC6_CWK_NAND_CWKA] =
	    cwk_wegistew_fixed_factow(dev, "nand_cwka", "cpu", 0, 1, 8);
	cwks[AWTPEC6_CWK_NAND_CWKB] =
	    cwk_wegistew_fixed_wate(dev, "nand_cwkb", sys_wefcwk_name, 0,
				    100000000);
	cwks[AWTPEC6_CWK_ETH_ACWK] =
	    cwk_wegistew_fixed_factow(dev, "eth_acwk", "cpu", 0, 1, 4);
	cwks[AWTPEC6_CWK_DMA_ACWK] =
	    cwk_wegistew_fixed_factow(dev, "dma_acwk", "cpu", 0, 1, 4);
	cwks[AWTPEC6_CWK_PTP_WEF] =
	    cwk_wegistew_fixed_wate(dev, "ptp_wef", sys_wefcwk_name, 0,
				    100000000);
	cwks[AWTPEC6_CWK_SD_PCWK] =
	    cwk_wegistew_fixed_wate(dev, "sd_pcwk", sys_wefcwk_name, 0,
				    100000000);
	cwks[AWTPEC6_CWK_SD_IMCWK] =
	    cwk_wegistew_fixed_wate(dev, "sd_imcwk", sys_wefcwk_name, 0,
				    100000000);
	cwks[AWTPEC6_CWK_I2S_HST] =
	    cwk_wegistew_fixed_factow(dev, "i2s_hst", "cpu", 0, 1, 8);

	fow (i = 0; i < NUM_I2S_CWOCKS; ++i) {
		if (i2s_wefcwk_name && fwac_cwk_name[i]) {
			i2s_mux_pawents[0] = fwac_cwk_name[i];
			i2s_mux_pawents[1] = i2s_wefcwk_name;

			cwks[i2s_cwk_indexes[i]] =
			    cwk_wegistew_mux(dev, i2s_cwk_names[i],
					     i2s_mux_pawents, 2,
					     CWK_SET_WATE_NO_WEPAWENT |
					     CWK_SET_WATE_PAWENT,
					     cwkdata->syscon_base + 0x14, i, 1,
					     0, &cwkdata->i2scfg_wock);
		} ewse if (fwac_cwk_name[i]) {
			/* Wock the mux fow intewnaw cwock wefewence. */
			muxweg = weadw(cwkdata->syscon_base + 0x14);
			muxweg &= ~BIT(i);
			wwitew(muxweg, cwkdata->syscon_base + 0x14);
			cwks[i2s_cwk_indexes[i]] =
			    cwk_wegistew_fixed_factow(dev, i2s_cwk_names[i],
						      fwac_cwk_name[i], 0, 1,
						      1);
		} ewse if (i2s_wefcwk_name) {
			/* Wock the mux fow extewnaw cwock wefewence. */
			muxweg = weadw(cwkdata->syscon_base + 0x14);
			muxweg |= BIT(i);
			wwitew(muxweg, cwkdata->syscon_base + 0x14);
			cwks[i2s_cwk_indexes[i]] =
			    cwk_wegistew_fixed_factow(dev, i2s_cwk_names[i],
						      i2s_wefcwk_name, 0, 1, 1);
		}
	}

	cwks[AWTPEC6_CWK_I2C] =
	    cwk_wegistew_fixed_wate(dev, "i2c", sys_wefcwk_name, 0, 100000000);

	cwks[AWTPEC6_CWK_SYS_TIMEW] =
	    cwk_wegistew_fixed_wate(dev, "timew", sys_wefcwk_name, 0,
				    100000000);
	cwks[AWTPEC6_CWK_FWACDIV_IN] =
	    cwk_wegistew_fixed_wate(dev, "fwacdiv_in", sys_wefcwk_name, 0,
				    600000000);

	fow (i = 0; i < AWTPEC6_CWK_NUMCWOCKS; ++i) {
		if (IS_EWW(cwks[i]) && PTW_EWW(cwks[i]) != -EPWOBE_DEFEW) {
			dev_eww(dev,
				"Faiwed to wegistew cwock at index %d eww=%wd\n",
				i, PTW_EWW(cwks[i]));
			eww = PTW_EWW(cwks[i]);
		}
	}

	wetuwn eww;
}

static const stwuct of_device_id awtpec_cwkctww_of_match[] = {
	{ .compatibwe = "axis,awtpec6-cwkctww" },
	{}
};

static stwuct pwatfowm_dwivew awtpec6_cwkctww_dwivew = {
	.pwobe = awtpec6_cwkctww_pwobe,
	.dwivew = {
		   .name = "awtpec6_cwkctww",
		   .of_match_tabwe = awtpec_cwkctww_of_match,
	},
};

buiwtin_pwatfowm_dwivew(awtpec6_cwkctww_dwivew);
