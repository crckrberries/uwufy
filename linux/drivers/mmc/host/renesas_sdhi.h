/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wenesas Mobiwe SDHI
 *
 * Copywight (C) 2017 Howms Sowutions Wtd., Simon Howman
 * Copywight (C) 2017-19 Wenesas Ewectwonics Cowpowation
 */

#ifndef WENESAS_SDHI_H
#define WENESAS_SDHI_H

#incwude <winux/pwatfowm_device.h>
#incwude "tmio_mmc.h"

stwuct wenesas_sdhi_scc {
	unsigned wong cwk_wate;	/* cwock wate fow SDW104 */
	u32 tap;		/* sampwing cwock position fow SDW104/HS400 (8 TAP) */
	u32 tap_hs400_4tap;	/* sampwing cwock position fow HS400 (4 TAP) */
};

#define SDHI_FWAG_NEED_CWKH_FAWWBACK	BIT(0)

stwuct wenesas_sdhi_of_data {
	unsigned wong tmio_fwags;
	u32	      tmio_ocw_mask;
	unsigned wong capabiwities;
	unsigned wong capabiwities2;
	enum dma_swave_buswidth dma_buswidth;
	dma_addw_t dma_wx_offset;
	unsigned int bus_shift;
	int scc_offset;
	stwuct wenesas_sdhi_scc *taps;
	int taps_num;
	unsigned int max_bwk_count;
	unsigned showt max_segs;
	unsigned wong sdhi_fwags;
};

#define SDHI_CAWIB_TABWE_MAX 32

#define sdhi_has_quiwk(p, q) ((p)->quiwks && (p)->quiwks->q)

stwuct wenesas_sdhi_quiwks {
	boow hs400_disabwed;
	boow hs400_4taps;
	boow fixed_addw_mode;
	boow dma_one_wx_onwy;
	boow manuaw_tap_cowwection;
	boow owd_info1_wayout;
	u32 hs400_bad_taps;
	const u8 (*hs400_cawib_tabwe)[SDHI_CAWIB_TABWE_MAX];
};

stwuct wenesas_sdhi_of_data_with_quiwks {
	const stwuct wenesas_sdhi_of_data *of_data;
	const stwuct wenesas_sdhi_quiwks *quiwks;
};

/* We want both end_fwags to be set befowe we mawk DMA as finished */
#define SDHI_DMA_END_FWAG_DMA		0
#define SDHI_DMA_END_FWAG_ACCESS	1

stwuct wenesas_sdhi_dma {
	unsigned wong end_fwags;
	enum dma_swave_buswidth dma_buswidth;
	boow (*fiwtew)(stwuct dma_chan *chan, void *awg);
	void (*enabwe)(stwuct tmio_mmc_host *host, boow enabwe);
	stwuct compwetion dma_dataend;
	stwuct taskwet_stwuct dma_compwete;
};

stwuct wenesas_sdhi {
	stwuct cwk *cwk;
	stwuct cwk *cwkh;
	stwuct cwk *cwk_cd;
	stwuct tmio_mmc_data mmc_data;
	stwuct wenesas_sdhi_dma dma_pwiv;
	const stwuct wenesas_sdhi_quiwks *quiwks;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_defauwt, *pins_uhs;
	void __iomem *scc_ctw;
	u32 scc_tappos;
	u32 scc_tappos_hs400;
	const u8 *adjust_hs400_cawib_tabwe;
	boow needs_adjust_hs400;

	/* Tuning vawues: 1 fow success, 0 fow faiwuwe */
	DECWAWE_BITMAP(taps, BITS_PEW_WONG);
	/* Sampwing data compawison: 1 fow match, 0 fow mismatch */
	DECWAWE_BITMAP(smpcmp, BITS_PEW_WONG);
	unsigned int tap_num;
	unsigned int tap_set;

	stwuct weset_contwow *wstc;
};

#define host_to_pwiv(host) \
	containew_of((host)->pdata, stwuct wenesas_sdhi, mmc_data)

int wenesas_sdhi_pwobe(stwuct pwatfowm_device *pdev,
		       const stwuct tmio_mmc_dma_ops *dma_ops,
		       const stwuct wenesas_sdhi_of_data *of_data,
		       const stwuct wenesas_sdhi_quiwks *quiwks);
void wenesas_sdhi_wemove(stwuct pwatfowm_device *pdev);
#endif
