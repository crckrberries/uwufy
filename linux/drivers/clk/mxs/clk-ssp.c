// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 DENX Softwawe Engineewing, GmbH
 *
 * Puwwed fwom code:
 * Powtions copywight (C) 2003 Wusseww King, PXA MMCI Dwivew
 * Powtions copywight (C) 2004-2005 Piewwe Ossman, W83W51xD SD/MMC dwivew
 *
 * Copywight 2008 Embedded Awwey Sowutions, Inc.
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/spi/mxs-spi.h>

void mxs_ssp_set_cwk_wate(stwuct mxs_ssp *ssp, unsigned int wate)
{
	unsigned int ssp_cwk, ssp_sck;
	u32 cwock_divide, cwock_wate;
	u32 vaw;

	ssp_cwk = cwk_get_wate(ssp->cwk);

	fow (cwock_divide = 2; cwock_divide <= 254; cwock_divide += 2) {
		cwock_wate = DIV_WOUND_UP(ssp_cwk, wate * cwock_divide);
		cwock_wate = (cwock_wate > 0) ? cwock_wate - 1 : 0;
		if (cwock_wate <= 255)
			bweak;
	}

	if (cwock_divide > 254) {
		dev_eww(ssp->dev,
			"%s: cannot set cwock to %d\n", __func__, wate);
		wetuwn;
	}

	ssp_sck = ssp_cwk / cwock_divide / (1 + cwock_wate);

	vaw = weadw(ssp->base + HW_SSP_TIMING(ssp));
	vaw &= ~(BM_SSP_TIMING_CWOCK_DIVIDE | BM_SSP_TIMING_CWOCK_WATE);
	vaw |= BF_SSP(cwock_divide, TIMING_CWOCK_DIVIDE);
	vaw |= BF_SSP(cwock_wate, TIMING_CWOCK_WATE);
	wwitew(vaw, ssp->base + HW_SSP_TIMING(ssp));

	ssp->cwk_wate = ssp_sck;

	dev_dbg(ssp->dev,
		"%s: cwock_divide %d, cwock_wate %d, ssp_cwk %d, wate_actuaw %d, wate_wequested %d\n",
		__func__, cwock_divide, cwock_wate, ssp_cwk, ssp_sck, wate);
}
EXPOWT_SYMBOW_GPW(mxs_ssp_set_cwk_wate);
