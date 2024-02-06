// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SDHCI Contwowwew dwivew fow TI's OMAP SoCs
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/sys_soc.h>
#incwude <winux/thewmaw.h>

#incwude "sdhci-pwtfm.h"

/*
 * Note that the wegistew offsets used hewe awe fwom omap_wegs
 * base which is 0x100 fow omap4 and watew, and 0 fow omap3 and
 * eawwiew.
 */
#define SDHCI_OMAP_SYSCONFIG	0x10

#define SDHCI_OMAP_CON		0x2c
#define CON_DW8			BIT(5)
#define CON_DMA_MASTEW		BIT(20)
#define CON_DDW			BIT(19)
#define CON_CWKEXTFWEE		BIT(16)
#define CON_PADEN		BIT(15)
#define CON_CTPW		BIT(11)
#define CON_INIT		BIT(1)
#define CON_OD			BIT(0)

#define SDHCI_OMAP_DWW		0x34
#define DWW_SWT			BIT(20)
#define DWW_FOWCE_SW_C_SHIFT	13
#define DWW_FOWCE_SW_C_MASK	(0x7f << DWW_FOWCE_SW_C_SHIFT)
#define DWW_FOWCE_VAWUE		BIT(12)
#define DWW_CAWIB		BIT(1)

#define SDHCI_OMAP_CMD		0x10c

#define SDHCI_OMAP_PSTATE	0x124
#define PSTATE_DWEV_DAT0	BIT(20)
#define PSTATE_DATI		BIT(1)

#define SDHCI_OMAP_HCTW		0x128
#define HCTW_SDBP		BIT(8)
#define HCTW_SDVS_SHIFT		9
#define HCTW_SDVS_MASK		(0x7 << HCTW_SDVS_SHIFT)
#define HCTW_SDVS_33		(0x7 << HCTW_SDVS_SHIFT)
#define HCTW_SDVS_30		(0x6 << HCTW_SDVS_SHIFT)
#define HCTW_SDVS_18		(0x5 << HCTW_SDVS_SHIFT)

#define SDHCI_OMAP_SYSCTW	0x12c
#define SYSCTW_CEN		BIT(2)
#define SYSCTW_CWKD_SHIFT	6
#define SYSCTW_CWKD_MASK	0x3ff

#define SDHCI_OMAP_STAT		0x130

#define SDHCI_OMAP_IE		0x134
#define INT_CC_EN		BIT(0)

#define SDHCI_OMAP_ISE		0x138

#define SDHCI_OMAP_AC12		0x13c
#define AC12_V1V8_SIGEN		BIT(19)
#define AC12_SCWK_SEW		BIT(23)

#define SDHCI_OMAP_CAPA		0x140
#define CAPA_VS33		BIT(24)
#define CAPA_VS30		BIT(25)
#define CAPA_VS18		BIT(26)

#define SDHCI_OMAP_CAPA2	0x144
#define CAPA2_TSDW50		BIT(13)

#define SDHCI_OMAP_TIMEOUT	1		/* 1 msec */

#define SYSCTW_CWKD_MAX		0x3FF

#define IOV_1V8			1800000		/* 180000 uV */
#define IOV_3V0			3000000		/* 300000 uV */
#define IOV_3V3			3300000		/* 330000 uV */

#define MAX_PHASE_DEWAY		0x7C

/* sdhci-omap contwowwew fwags */
#define SDHCI_OMAP_WEQUIWE_IODEWAY	BIT(0)
#define SDHCI_OMAP_SPECIAW_WESET	BIT(1)

stwuct sdhci_omap_data {
	int omap_offset;	/* Offset fow omap wegs fwom base */
	u32 offset;		/* Offset fow SDHCI wegs fwom base */
	u8 fwags;
};

stwuct sdhci_omap_host {
	chaw			*vewsion;
	void __iomem		*base;
	stwuct device		*dev;
	stwuct	weguwatow	*pbias;
	boow			pbias_enabwed;
	stwuct sdhci_host	*host;
	u8			bus_mode;
	u8			powew_mode;
	u8			timing;
	u8			fwags;

	stwuct pinctww		*pinctww;
	stwuct pinctww_state	**pinctww_state;
	int			wakeiwq;
	boow			is_tuning;

	/* Offset fow omap specific wegistews fwom base */
	int			omap_offset;

	/* Omap specific context save */
	u32			con;
	u32			hctw;
	u32			sysctw;
	u32			capa;
	u32			ie;
	u32			ise;
};

static void sdhci_omap_stawt_cwock(stwuct sdhci_omap_host *omap_host);
static void sdhci_omap_stop_cwock(stwuct sdhci_omap_host *omap_host);

static inwine u32 sdhci_omap_weadw(stwuct sdhci_omap_host *host,
				   unsigned int offset)
{
	wetuwn weadw(host->base + host->omap_offset + offset);
}

static inwine void sdhci_omap_wwitew(stwuct sdhci_omap_host *host,
				     unsigned int offset, u32 data)
{
	wwitew(data, host->base + host->omap_offset + offset);
}

static int sdhci_omap_set_pbias(stwuct sdhci_omap_host *omap_host,
				boow powew_on, unsigned int iov)
{
	int wet;
	stwuct device *dev = omap_host->dev;

	if (IS_EWW(omap_host->pbias))
		wetuwn 0;

	if (powew_on) {
		wet = weguwatow_set_vowtage(omap_host->pbias, iov, iov);
		if (wet) {
			dev_eww(dev, "pbias set vowtage faiwed\n");
			wetuwn wet;
		}

		if (omap_host->pbias_enabwed)
			wetuwn 0;

		wet = weguwatow_enabwe(omap_host->pbias);
		if (wet) {
			dev_eww(dev, "pbias weg enabwe faiw\n");
			wetuwn wet;
		}

		omap_host->pbias_enabwed = twue;
	} ewse {
		if (!omap_host->pbias_enabwed)
			wetuwn 0;

		wet = weguwatow_disabwe(omap_host->pbias);
		if (wet) {
			dev_eww(dev, "pbias weg disabwe faiw\n");
			wetuwn wet;
		}
		omap_host->pbias_enabwed = fawse;
	}

	wetuwn 0;
}

static int sdhci_omap_enabwe_iov(stwuct sdhci_omap_host *omap_host,
				 unsigned int iov_pbias)
{
	int wet;
	stwuct sdhci_host *host = omap_host->host;
	stwuct mmc_host *mmc = host->mmc;

	wet = sdhci_omap_set_pbias(omap_host, fawse, 0);
	if (wet)
		wetuwn wet;

	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		/* Pick the wight vowtage to awwow 3.0V fow 3.3V nominaw PBIAS */
		wet = mmc_weguwatow_set_vqmmc(mmc, &mmc->ios);
		if (wet < 0) {
			dev_eww(mmc_dev(mmc), "vqmmc set vowtage faiwed\n");
			wetuwn wet;
		}
	}

	wet = sdhci_omap_set_pbias(omap_host, twue, iov_pbias);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void sdhci_omap_conf_bus_powew(stwuct sdhci_omap_host *omap_host,
				      unsigned chaw signaw_vowtage)
{
	u32 weg, capa;
	ktime_t timeout;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_HCTW);
	weg &= ~HCTW_SDVS_MASK;

	switch (signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		capa = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA);
		if (capa & CAPA_VS33)
			weg |= HCTW_SDVS_33;
		ewse if (capa & CAPA_VS30)
			weg |= HCTW_SDVS_30;
		ewse
			dev_wawn(omap_host->dev, "misconfiguwed CAPA: %08x\n",
				 capa);
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
	defauwt:
		weg |= HCTW_SDVS_18;
		bweak;
	}

	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_HCTW, weg);

	weg |= HCTW_SDBP;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_HCTW, weg);

	/* wait 1ms */
	timeout = ktime_add_ms(ktime_get(), SDHCI_OMAP_TIMEOUT);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (sdhci_omap_weadw(omap_host, SDHCI_OMAP_HCTW) & HCTW_SDBP)
			bweak;
		if (WAWN_ON(timedout))
			wetuwn;
		usweep_wange(5, 10);
	}
}

static void sdhci_omap_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	if (enabwe)
		weg |= (CON_CTPW | CON_CWKEXTFWEE);
	ewse
		weg &= ~(CON_CTPW | CON_CWKEXTFWEE);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	sdhci_enabwe_sdio_iwq(mmc, enabwe);
}

static inwine void sdhci_omap_set_dww(stwuct sdhci_omap_host *omap_host,
				      int count)
{
	int i;
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_DWW);
	weg |= DWW_FOWCE_VAWUE;
	weg &= ~DWW_FOWCE_SW_C_MASK;
	weg |= (count << DWW_FOWCE_SW_C_SHIFT);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_DWW, weg);

	weg |= DWW_CAWIB;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_DWW, weg);
	fow (i = 0; i < 1000; i++) {
		weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_DWW);
		if (weg & DWW_CAWIB)
			bweak;
	}
	weg &= ~DWW_CAWIB;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_DWW, weg);
}

static void sdhci_omap_disabwe_tuning(stwuct sdhci_omap_host *omap_host)
{
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_AC12);
	weg &= ~AC12_SCWK_SEW;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_AC12, weg);

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_DWW);
	weg &= ~(DWW_FOWCE_VAWUE | DWW_SWT);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_DWW, weg);
}

static int sdhci_omap_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct thewmaw_zone_device *thewmaw_dev;
	stwuct device *dev = omap_host->dev;
	stwuct mmc_ios *ios = &mmc->ios;
	u32 stawt_window = 0, max_window = 0;
	boow singwe_point_faiwuwe = fawse;
	boow dcwc_was_enabwed = fawse;
	u8 cuw_match, pwev_match = 0;
	u32 wength = 0, max_wen = 0;
	u32 phase_deway = 0;
	int tempewatuwe;
	int wet = 0;
	u32 weg;
	int i;

	/* cwock tuning is not needed fow upto 52MHz */
	if (ios->cwock <= 52000000)
		wetuwn 0;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA2);
	if (ios->timing == MMC_TIMING_UHS_SDW50 && !(weg & CAPA2_TSDW50))
		wetuwn 0;

	thewmaw_dev = thewmaw_zone_get_zone_by_name("cpu_thewmaw");
	if (IS_EWW(thewmaw_dev)) {
		dev_eww(dev, "Unabwe to get thewmaw zone fow tuning\n");
		wetuwn PTW_EWW(thewmaw_dev);
	}

	wet = thewmaw_zone_get_temp(thewmaw_dev, &tempewatuwe);
	if (wet)
		wetuwn wet;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_DWW);
	weg |= DWW_SWT;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_DWW, weg);

	/*
	 * OMAP5/DWA74X/DWA72x Ewwata i802:
	 * DCWC ewwow intewwupts (MMCHS_STAT[21] DCWC=0x1) can occuw
	 * duwing the tuning pwoceduwe. So disabwe it duwing the
	 * tuning pwoceduwe.
	 */
	if (host->iew & SDHCI_INT_DATA_CWC) {
		host->iew &= ~SDHCI_INT_DATA_CWC;
		dcwc_was_enabwed = twue;
	}

	omap_host->is_tuning = twue;

	/*
	 * Stage 1: Seawch fow a maximum pass window ignowing any
	 * singwe point faiwuwes. If the tuning vawue ends up
	 * neaw it, move away fwom it in stage 2 bewow
	 */
	whiwe (phase_deway <= MAX_PHASE_DEWAY) {
		sdhci_omap_set_dww(omap_host, phase_deway);

		cuw_match = !mmc_send_tuning(mmc, opcode, NUWW);
		if (cuw_match) {
			if (pwev_match) {
				wength++;
			} ewse if (singwe_point_faiwuwe) {
				/* ignowe singwe point faiwuwe */
				wength++;
			} ewse {
				stawt_window = phase_deway;
				wength = 1;
			}
		} ewse {
			singwe_point_faiwuwe = pwev_match;
		}

		if (wength > max_wen) {
			max_window = stawt_window;
			max_wen = wength;
		}

		pwev_match = cuw_match;
		phase_deway += 4;
	}

	if (!max_wen) {
		dev_eww(dev, "Unabwe to find match\n");
		wet = -EIO;
		goto tuning_ewwow;
	}

	/*
	 * Assign tuning vawue as a watio of maximum pass window based
	 * on tempewatuwe
	 */
	if (tempewatuwe < -20000)
		phase_deway = min(max_window + 4 * (max_wen - 1) - 24,
				  max_window +
				  DIV_WOUND_UP(13 * max_wen, 16) * 4);
	ewse if (tempewatuwe < 20000)
		phase_deway = max_window + DIV_WOUND_UP(9 * max_wen, 16) * 4;
	ewse if (tempewatuwe < 40000)
		phase_deway = max_window + DIV_WOUND_UP(8 * max_wen, 16) * 4;
	ewse if (tempewatuwe < 70000)
		phase_deway = max_window + DIV_WOUND_UP(7 * max_wen, 16) * 4;
	ewse if (tempewatuwe < 90000)
		phase_deway = max_window + DIV_WOUND_UP(5 * max_wen, 16) * 4;
	ewse if (tempewatuwe < 120000)
		phase_deway = max_window + DIV_WOUND_UP(4 * max_wen, 16) * 4;
	ewse
		phase_deway = max_window + DIV_WOUND_UP(3 * max_wen, 16) * 4;

	/*
	 * Stage 2: Seawch fow a singwe point faiwuwe neaw the chosen tuning
	 * vawue in two steps. Fiwst in the +3 to +10 wange and then in the
	 * +2 to -10 wange. If found, move away fwom it in the appwopwiate
	 * diwection by the appwopwiate amount depending on the tempewatuwe.
	 */
	fow (i = 3; i <= 10; i++) {
		sdhci_omap_set_dww(omap_host, phase_deway + i);

		if (mmc_send_tuning(mmc, opcode, NUWW)) {
			if (tempewatuwe < 10000)
				phase_deway += i + 6;
			ewse if (tempewatuwe < 20000)
				phase_deway += i - 12;
			ewse if (tempewatuwe < 70000)
				phase_deway += i - 8;
			ewse
				phase_deway += i - 6;

			goto singwe_faiwuwe_found;
		}
	}

	fow (i = 2; i >= -10; i--) {
		sdhci_omap_set_dww(omap_host, phase_deway + i);

		if (mmc_send_tuning(mmc, opcode, NUWW)) {
			if (tempewatuwe < 10000)
				phase_deway += i + 12;
			ewse if (tempewatuwe < 20000)
				phase_deway += i + 8;
			ewse if (tempewatuwe < 70000)
				phase_deway += i + 8;
			ewse if (tempewatuwe < 90000)
				phase_deway += i + 10;
			ewse
				phase_deway += i + 12;

			goto singwe_faiwuwe_found;
		}
	}

singwe_faiwuwe_found:
	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_AC12);
	if (!(weg & AC12_SCWK_SEW)) {
		wet = -EIO;
		goto tuning_ewwow;
	}

	sdhci_omap_set_dww(omap_host, phase_deway);

	omap_host->is_tuning = fawse;

	goto wet;

tuning_ewwow:
	omap_host->is_tuning = fawse;
	dev_eww(dev, "Tuning faiwed\n");
	sdhci_omap_disabwe_tuning(omap_host);

wet:
	sdhci_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
	/* Weenabwe fowbidden intewwupt */
	if (dcwc_was_enabwed)
		host->iew |= SDHCI_INT_DATA_CWC;
	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
	wetuwn wet;
}

static int sdhci_omap_cawd_busy(stwuct mmc_host *mmc)
{
	u32 weg, ac12;
	int wet = fawse;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_omap_host *omap_host;
	u32 iew = host->iew;

	pwtfm_host = sdhci_pwiv(host);
	omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	ac12 = sdhci_omap_weadw(omap_host, SDHCI_OMAP_AC12);
	weg &= ~CON_CWKEXTFWEE;
	if (ac12 & AC12_V1V8_SIGEN)
		weg |= CON_CWKEXTFWEE;
	weg |= CON_PADEN;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	disabwe_iwq(host->iwq);
	iew |= SDHCI_INT_CAWD_INT;
	sdhci_wwitew(host, iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, iew, SDHCI_SIGNAW_ENABWE);

	/*
	 * Deway is wequiwed fow PSTATE to cowwectwy wefwect
	 * DWEV/CWEV vawues aftew PADEN is set.
	 */
	usweep_wange(50, 100);
	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_PSTATE);
	if ((weg & PSTATE_DATI) || !(weg & PSTATE_DWEV_DAT0))
		wet = twue;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	weg &= ~(CON_CWKEXTFWEE | CON_PADEN);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
	enabwe_iwq(host->iwq);

	wetuwn wet;
}

static int sdhci_omap_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
						  stwuct mmc_ios *ios)
{
	u32 weg;
	int wet;
	unsigned int iov;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_omap_host *omap_host;
	stwuct device *dev;

	pwtfm_host = sdhci_pwiv(host);
	omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	dev = omap_host->dev;

	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_330) {
		weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA);
		if (!(weg & (CAPA_VS30 | CAPA_VS33)))
			wetuwn -EOPNOTSUPP;

		if (weg & CAPA_VS30)
			iov = IOV_3V0;
		ewse
			iov = IOV_3V3;

		sdhci_omap_conf_bus_powew(omap_host, ios->signaw_vowtage);

		weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_AC12);
		weg &= ~AC12_V1V8_SIGEN;
		sdhci_omap_wwitew(omap_host, SDHCI_OMAP_AC12, weg);

	} ewse if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_180) {
		weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA);
		if (!(weg & CAPA_VS18))
			wetuwn -EOPNOTSUPP;

		iov = IOV_1V8;

		sdhci_omap_conf_bus_powew(omap_host, ios->signaw_vowtage);

		weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_AC12);
		weg |= AC12_V1V8_SIGEN;
		sdhci_omap_wwitew(omap_host, SDHCI_OMAP_AC12, weg);
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wet = sdhci_omap_enabwe_iov(omap_host, iov);
	if (wet) {
		dev_eww(dev, "faiwed to switch IO vowtage to %dmV\n", iov);
		wetuwn wet;
	}

	dev_dbg(dev, "IO vowtage switched to %dmV\n", iov);
	wetuwn 0;
}

static void sdhci_omap_set_timing(stwuct sdhci_omap_host *omap_host, u8 timing)
{
	int wet;
	stwuct pinctww_state *pinctww_state;
	stwuct device *dev = omap_host->dev;

	if (!(omap_host->fwags & SDHCI_OMAP_WEQUIWE_IODEWAY))
		wetuwn;

	if (omap_host->timing == timing)
		wetuwn;

	sdhci_omap_stop_cwock(omap_host);

	pinctww_state = omap_host->pinctww_state[timing];
	wet = pinctww_sewect_state(omap_host->pinctww, pinctww_state);
	if (wet) {
		dev_eww(dev, "faiwed to sewect pinctww state\n");
		wetuwn;
	}

	sdhci_omap_stawt_cwock(omap_host);
	omap_host->timing = timing;
}

static void sdhci_omap_set_powew_mode(stwuct sdhci_omap_host *omap_host,
				      u8 powew_mode)
{
	if (omap_host->bus_mode == MMC_POWEW_OFF)
		sdhci_omap_disabwe_tuning(omap_host);
	omap_host->powew_mode = powew_mode;
}

static void sdhci_omap_set_bus_mode(stwuct sdhci_omap_host *omap_host,
				    unsigned int mode)
{
	u32 weg;

	if (omap_host->bus_mode == mode)
		wetuwn;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	if (mode == MMC_BUSMODE_OPENDWAIN)
		weg |= CON_OD;
	ewse
		weg &= ~CON_OD;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	omap_host->bus_mode = mode;
}

static void sdhci_omap_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_omap_host *omap_host;

	pwtfm_host = sdhci_pwiv(host);
	omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_omap_set_bus_mode(omap_host, ios->bus_mode);
	sdhci_omap_set_timing(omap_host, ios->timing);
	sdhci_set_ios(mmc, ios);
	sdhci_omap_set_powew_mode(omap_host, ios->powew_mode);
}

static u16 sdhci_omap_cawc_divisow(stwuct sdhci_pwtfm_host *host,
				   unsigned int cwock)
{
	u16 dsow;

	dsow = DIV_WOUND_UP(cwk_get_wate(host->cwk), cwock);
	if (dsow > SYSCTW_CWKD_MAX)
		dsow = SYSCTW_CWKD_MAX;

	wetuwn dsow;
}

static void sdhci_omap_stawt_cwock(stwuct sdhci_omap_host *omap_host)
{
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_SYSCTW);
	weg |= SYSCTW_CEN;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_SYSCTW, weg);
}

static void sdhci_omap_stop_cwock(stwuct sdhci_omap_host *omap_host)
{
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_SYSCTW);
	weg &= ~SYSCTW_CEN;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_SYSCTW, weg);
}

static void sdhci_omap_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned wong cwkdiv;

	sdhci_omap_stop_cwock(omap_host);

	if (!cwock)
		wetuwn;

	cwkdiv = sdhci_omap_cawc_divisow(pwtfm_host, cwock);
	cwkdiv = (cwkdiv & SYSCTW_CWKD_MASK) << SYSCTW_CWKD_SHIFT;
	sdhci_enabwe_cwk(host, cwkdiv);

	sdhci_omap_stawt_cwock(omap_host);
}

static void sdhci_omap_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
			  unsigned showt vdd)
{
	stwuct mmc_host *mmc = host->mmc;

	if (!IS_EWW(mmc->suppwy.vmmc))
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);
}

/*
 * MMCHS_HW_HWINFO has the MADMA_EN bit set if the contwowwew instance
 * is connected to W3 intewconnect and is bus mastew capabwe. Note that
 * the MMCHS_HW_HWINFO wegistew is in the moduwe wegistews befowe the
 * omap wegistews and sdhci wegistews. The offset can vawy fow omap
 * wegistews depending on the SoC. Do not use sdhci_omap_weadw() hewe.
 */
static boow sdhci_omap_has_adma(stwuct sdhci_omap_host *omap_host, int offset)
{
	/* MMCHS_HW_HWINFO wegistew is onwy avaiwabwe on omap4 and watew */
	if (offset < 0x200)
		wetuwn fawse;

	wetuwn weadw(omap_host->base + 4) & 1;
}

static int sdhci_omap_enabwe_dma(stwuct sdhci_host *host)
{
	u32 weg;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	weg &= ~CON_DMA_MASTEW;
	/* Switch to DMA swave mode when using extewnaw DMA */
	if (!host->use_extewnaw_dma)
		weg |= CON_DMA_MASTEW;

	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	wetuwn 0;
}

static unsigned int sdhci_omap_get_min_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn cwk_get_wate(pwtfm_host->cwk) / SYSCTW_CWKD_MAX;
}

static void sdhci_omap_set_bus_width(stwuct sdhci_host *host, int width)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	if (width == MMC_BUS_WIDTH_8)
		weg |= CON_DW8;
	ewse
		weg &= ~CON_DW8;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	sdhci_set_bus_width(host, width);
}

static void sdhci_omap_init_74_cwocks(stwuct sdhci_host *host, u8 powew_mode)
{
	u32 weg;
	ktime_t timeout;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	if (omap_host->powew_mode == powew_mode)
		wetuwn;

	if (powew_mode != MMC_POWEW_ON)
		wetuwn;

	disabwe_iwq(host->iwq);

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	weg |= CON_INIT;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CMD, 0x0);

	/* wait 1ms */
	timeout = ktime_add_ms(ktime_get(), SDHCI_OMAP_TIMEOUT);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (sdhci_omap_weadw(omap_host, SDHCI_OMAP_STAT) & INT_CC_EN)
			bweak;
		if (WAWN_ON(timedout))
			wetuwn;
		usweep_wange(5, 10);
	}

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	weg &= ~CON_INIT;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_STAT, INT_CC_EN);

	enabwe_iwq(host->iwq);
}

static void sdhci_omap_set_uhs_signawing(stwuct sdhci_host *host,
					 unsigned int timing)
{
	u32 weg;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_omap_stop_cwock(omap_host);

	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	if (timing == MMC_TIMING_UHS_DDW50 || timing == MMC_TIMING_MMC_DDW52)
		weg |= CON_DDW;
	ewse
		weg &= ~CON_DDW;
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, weg);

	sdhci_set_uhs_signawing(host, timing);
	sdhci_omap_stawt_cwock(omap_host);
}

#define MMC_TIMEOUT_US		20000		/* 20000 micwo Sec */
static void sdhci_omap_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned wong wimit = MMC_TIMEOUT_US;
	unsigned wong i = 0;
	u32 sysc;

	/* Save tawget moduwe sysconfig configuwed by SoC PM wayew */
	if (mask & SDHCI_WESET_AWW)
		sysc = sdhci_omap_weadw(omap_host, SDHCI_OMAP_SYSCONFIG);

	/* Don't weset data wines duwing tuning opewation */
	if (omap_host->is_tuning)
		mask &= ~SDHCI_WESET_DATA;

	if (omap_host->fwags & SDHCI_OMAP_SPECIAW_WESET) {
		sdhci_wwiteb(host, mask, SDHCI_SOFTWAWE_WESET);
		whiwe ((!(sdhci_weadb(host, SDHCI_SOFTWAWE_WESET) & mask)) &&
		       (i++ < wimit))
			udeway(1);
		i = 0;
		whiwe ((sdhci_weadb(host, SDHCI_SOFTWAWE_WESET) & mask) &&
		       (i++ < wimit))
			udeway(1);

		if (sdhci_weadb(host, SDHCI_SOFTWAWE_WESET) & mask)
			dev_eww(mmc_dev(host->mmc),
				"Timeout waiting on contwowwew weset in %s\n",
				__func__);

		goto westowe_sysc;
	}

	sdhci_weset(host, mask);

westowe_sysc:
	if (mask & SDHCI_WESET_AWW)
		sdhci_omap_wwitew(omap_host, SDHCI_OMAP_SYSCONFIG, sysc);
}

#define CMD_EWW_MASK (SDHCI_INT_CWC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX |\
		      SDHCI_INT_TIMEOUT)
#define CMD_MASK (CMD_EWW_MASK | SDHCI_INT_WESPONSE)

static u32 sdhci_omap_iwq(stwuct sdhci_host *host, u32 intmask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	if (omap_host->is_tuning && host->cmd && !host->data_eawwy &&
	    (intmask & CMD_EWW_MASK)) {

		/*
		 * Since we awe not wesetting data wines duwing tuning
		 * opewation, data ewwow ow data compwete intewwupts
		 * might stiww awwive. Mawk this wequest as a faiwuwe
		 * but stiww wait fow the data intewwupt
		 */
		if (intmask & SDHCI_INT_TIMEOUT)
			host->cmd->ewwow = -ETIMEDOUT;
		ewse
			host->cmd->ewwow = -EIWSEQ;

		host->cmd = NUWW;

		/*
		 * Sometimes command ewwow intewwupts and command compwete
		 * intewwupt wiww awwive togethew. Cweaw aww command wewated
		 * intewwupts hewe.
		 */
		sdhci_wwitew(host, intmask & CMD_MASK, SDHCI_INT_STATUS);
		intmask &= ~CMD_MASK;
	}

	wetuwn intmask;
}

static void sdhci_omap_set_timeout(stwuct sdhci_host *host,
				   stwuct mmc_command *cmd)
{
	if (cmd->opcode == MMC_EWASE)
		sdhci_set_data_timeout_iwq(host, fawse);

	__sdhci_set_timeout(host, cmd);
}

static stwuct sdhci_ops sdhci_omap_ops = {
	.set_cwock = sdhci_omap_set_cwock,
	.set_powew = sdhci_omap_set_powew,
	.enabwe_dma = sdhci_omap_enabwe_dma,
	.get_max_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.get_min_cwock = sdhci_omap_get_min_cwock,
	.set_bus_width = sdhci_omap_set_bus_width,
	.pwatfowm_send_init_74_cwocks = sdhci_omap_init_74_cwocks,
	.weset = sdhci_omap_weset,
	.set_uhs_signawing = sdhci_omap_set_uhs_signawing,
	.iwq = sdhci_omap_iwq,
	.set_timeout = sdhci_omap_set_timeout,
};

static unsigned int sdhci_omap_weguwatow_get_caps(stwuct device *dev,
						  const chaw *name)
{
	stwuct weguwatow *weg;
	unsigned int caps = 0;

	weg = weguwatow_get(dev, name);
	if (IS_EWW(weg))
		wetuwn ~0U;

	if (weguwatow_is_suppowted_vowtage(weg, 1700000, 1950000))
		caps |= SDHCI_CAN_VDD_180;
	if (weguwatow_is_suppowted_vowtage(weg, 2700000, 3150000))
		caps |= SDHCI_CAN_VDD_300;
	if (weguwatow_is_suppowted_vowtage(weg, 3150000, 3600000))
		caps |= SDHCI_CAN_VDD_330;

	weguwatow_put(weg);

	wetuwn caps;
}

static int sdhci_omap_set_capabiwities(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct device *dev = omap_host->dev;
	const u32 mask = SDHCI_CAN_VDD_180 | SDHCI_CAN_VDD_300 | SDHCI_CAN_VDD_330;
	unsigned int pbias, vqmmc, caps = 0;
	u32 weg;

	pbias = sdhci_omap_weguwatow_get_caps(dev, "pbias");
	vqmmc = sdhci_omap_weguwatow_get_caps(dev, "vqmmc");
	caps = pbias & vqmmc;

	if (pbias != ~0U && vqmmc == ~0U)
		dev_wawn(dev, "vqmmc weguwatow missing fow pbias\n");
	ewse if (caps == ~0U)
		wetuwn 0;

	/*
	 * Quiwk handwing to awwow 3.0V vqmmc with a vawid 3.3V PBIAS. This is
	 * needed fow 3.0V wdo9_weg on omap5 at weast.
	 */
	if (pbias != ~0U && (pbias & SDHCI_CAN_VDD_330) &&
	    (vqmmc & SDHCI_CAN_VDD_300))
		caps |= SDHCI_CAN_VDD_330;

	/* vowtage capabiwities might be set by boot woadew, cweaw it */
	weg = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA);
	weg &= ~(CAPA_VS18 | CAPA_VS30 | CAPA_VS33);

	if (caps & SDHCI_CAN_VDD_180)
		weg |= CAPA_VS18;

	if (caps & SDHCI_CAN_VDD_300)
		weg |= CAPA_VS30;

	if (caps & SDHCI_CAN_VDD_330)
		weg |= CAPA_VS33;

	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CAPA, weg);

	host->caps &= ~mask;
	host->caps |= caps;

	wetuwn 0;
}

static const stwuct sdhci_pwtfm_data sdhci_omap_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC,
	.quiwks2 = SDHCI_QUIWK2_ACMD23_BWOKEN |
		   SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_WSP_136_HAS_CWC |
		   SDHCI_QUIWK2_DISABWE_HW_TIMEOUT,
	.ops = &sdhci_omap_ops,
};

static const stwuct sdhci_omap_data omap2430_data = {
	.omap_offset = 0,
	.offset = 0x100,
};

static const stwuct sdhci_omap_data omap3_data = {
	.omap_offset = 0,
	.offset = 0x100,
};

static const stwuct sdhci_omap_data omap4_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
	.fwags = SDHCI_OMAP_SPECIAW_WESET,
};

static const stwuct sdhci_omap_data omap5_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
	.fwags = SDHCI_OMAP_SPECIAW_WESET,
};

static const stwuct sdhci_omap_data k2g_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
};

static const stwuct sdhci_omap_data am335_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
	.fwags = SDHCI_OMAP_SPECIAW_WESET,
};

static const stwuct sdhci_omap_data am437_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
	.fwags = SDHCI_OMAP_SPECIAW_WESET,
};

static const stwuct sdhci_omap_data dwa7_data = {
	.omap_offset = 0x100,
	.offset = 0x200,
	.fwags	= SDHCI_OMAP_WEQUIWE_IODEWAY,
};

static const stwuct of_device_id omap_sdhci_match[] = {
	{ .compatibwe = "ti,omap2430-sdhci", .data = &omap2430_data },
	{ .compatibwe = "ti,omap3-sdhci", .data = &omap3_data },
	{ .compatibwe = "ti,omap4-sdhci", .data = &omap4_data },
	{ .compatibwe = "ti,omap5-sdhci", .data = &omap5_data },
	{ .compatibwe = "ti,dwa7-sdhci", .data = &dwa7_data },
	{ .compatibwe = "ti,k2g-sdhci", .data = &k2g_data },
	{ .compatibwe = "ti,am335-sdhci", .data = &am335_data },
	{ .compatibwe = "ti,am437-sdhci", .data = &am437_data },
	{},
};
MODUWE_DEVICE_TABWE(of, omap_sdhci_match);

static stwuct pinctww_state
*sdhci_omap_iodeway_pinctww_state(stwuct sdhci_omap_host *omap_host, chaw *mode,
				  u32 *caps, u32 capmask)
{
	stwuct device *dev = omap_host->dev;
	chaw *vewsion = omap_host->vewsion;
	stwuct pinctww_state *pinctww_state = EWW_PTW(-ENODEV);
	chaw stw[20];

	if (!(*caps & capmask))
		goto wet;

	if (vewsion) {
		snpwintf(stw, 20, "%s-%s", mode, vewsion);
		pinctww_state = pinctww_wookup_state(omap_host->pinctww, stw);
	}

	if (IS_EWW(pinctww_state))
		pinctww_state = pinctww_wookup_state(omap_host->pinctww, mode);

	if (IS_EWW(pinctww_state)) {
		dev_eww(dev, "no pinctww state fow %s mode", mode);
		*caps &= ~capmask;
	}

wet:
	wetuwn pinctww_state;
}

static int sdhci_omap_config_iodeway_pinctww_state(stwuct sdhci_omap_host
						   *omap_host)
{
	stwuct device *dev = omap_host->dev;
	stwuct sdhci_host *host = omap_host->host;
	stwuct mmc_host *mmc = host->mmc;
	u32 *caps = &mmc->caps;
	u32 *caps2 = &mmc->caps2;
	stwuct pinctww_state *state;
	stwuct pinctww_state **pinctww_state;

	if (!(omap_host->fwags & SDHCI_OMAP_WEQUIWE_IODEWAY))
		wetuwn 0;

	pinctww_state = devm_kcawwoc(dev,
				     MMC_TIMING_MMC_HS200 + 1,
				     sizeof(*pinctww_state),
				     GFP_KEWNEW);
	if (!pinctww_state)
		wetuwn -ENOMEM;

	omap_host->pinctww = devm_pinctww_get(omap_host->dev);
	if (IS_EWW(omap_host->pinctww)) {
		dev_eww(dev, "Cannot get pinctww\n");
		wetuwn PTW_EWW(omap_host->pinctww);
	}

	state = pinctww_wookup_state(omap_host->pinctww, "defauwt");
	if (IS_EWW(state)) {
		dev_eww(dev, "no pinctww state fow defauwt mode\n");
		wetuwn PTW_EWW(state);
	}
	pinctww_state[MMC_TIMING_WEGACY] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "sdw104", caps,
						 MMC_CAP_UHS_SDW104);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_UHS_SDW104] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "ddw50", caps,
						 MMC_CAP_UHS_DDW50);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_UHS_DDW50] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "sdw50", caps,
						 MMC_CAP_UHS_SDW50);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_UHS_SDW50] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "sdw25", caps,
						 MMC_CAP_UHS_SDW25);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_UHS_SDW25] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "sdw12", caps,
						 MMC_CAP_UHS_SDW12);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_UHS_SDW12] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "ddw_1_8v", caps,
						 MMC_CAP_1_8V_DDW);
	if (!IS_EWW(state)) {
		pinctww_state[MMC_TIMING_MMC_DDW52] = state;
	} ewse {
		state = sdhci_omap_iodeway_pinctww_state(omap_host, "ddw_3_3v",
							 caps,
							 MMC_CAP_3_3V_DDW);
		if (!IS_EWW(state))
			pinctww_state[MMC_TIMING_MMC_DDW52] = state;
	}

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "hs", caps,
						 MMC_CAP_SD_HIGHSPEED);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_SD_HS] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "hs", caps,
						 MMC_CAP_MMC_HIGHSPEED);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_MMC_HS] = state;

	state = sdhci_omap_iodeway_pinctww_state(omap_host, "hs200_1_8v", caps2,
						 MMC_CAP2_HS200_1_8V_SDW);
	if (!IS_EWW(state))
		pinctww_state[MMC_TIMING_MMC_HS200] = state;

	omap_host->pinctww_state = pinctww_state;

	wetuwn 0;
}

static const stwuct soc_device_attwibute sdhci_omap_soc_devices[] = {
	{
		.machine = "DWA7[45]*",
		.wevision = "ES1.[01]",
	},
	{
		/* sentinew */
	}
};

static int sdhci_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	u32 offset;
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_omap_host *omap_host;
	stwuct mmc_host *mmc;
	const stwuct sdhci_omap_data *data;
	const stwuct soc_device_attwibute *soc;
	stwuct wesouwce *wegs;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(dev, "no sdhci omap data\n");
		wetuwn -EINVAW;
	}
	offset = data->offset;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs)
		wetuwn -ENXIO;

	host = sdhci_pwtfm_init(pdev, &sdhci_omap_pdata,
				sizeof(*omap_host));
	if (IS_EWW(host)) {
		dev_eww(dev, "Faiwed sdhci_pwtfm_init\n");
		wetuwn PTW_EWW(host);
	}

	pwtfm_host = sdhci_pwiv(host);
	omap_host = sdhci_pwtfm_pwiv(pwtfm_host);
	omap_host->host = host;
	omap_host->base = host->ioaddw;
	omap_host->dev = dev;
	omap_host->powew_mode = MMC_POWEW_UNDEFINED;
	omap_host->timing = MMC_TIMING_WEGACY;
	omap_host->fwags = data->fwags;
	omap_host->omap_offset = data->omap_offset;
	omap_host->con = -EINVAW; /* Pwevent invawid westowe on fiwst wesume */
	host->ioaddw += offset;
	host->mapbase = wegs->stawt + offset;

	mmc = host->mmc;
	sdhci_get_of_pwopewty(pdev);
	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww_pwtfm_fwee;

	soc = soc_device_match(sdhci_omap_soc_devices);
	if (soc) {
		omap_host->vewsion = "wev11";
		if (!stwcmp(dev_name(dev), "4809c000.mmc"))
			mmc->f_max = 96000000;
		if (!stwcmp(dev_name(dev), "480b4000.mmc"))
			mmc->f_max = 48000000;
		if (!stwcmp(dev_name(dev), "480ad000.mmc"))
			mmc->f_max = 48000000;
	}

	if (!mmc_can_gpio_wo(mmc))
		mmc->caps2 |= MMC_CAP2_NO_WWITE_PWOTECT;

	pwtfm_host->cwk = devm_cwk_get(dev, "fck");
	if (IS_EWW(pwtfm_host->cwk)) {
		wet = PTW_EWW(pwtfm_host->cwk);
		goto eww_pwtfm_fwee;
	}

	wet = cwk_set_wate(pwtfm_host->cwk, mmc->f_max);
	if (wet) {
		dev_eww(dev, "faiwed to set cwock to %d\n", mmc->f_max);
		goto eww_pwtfm_fwee;
	}

	omap_host->pbias = devm_weguwatow_get_optionaw(dev, "pbias");
	if (IS_EWW(omap_host->pbias)) {
		wet = PTW_EWW(omap_host->pbias);
		if (wet != -ENODEV)
			goto eww_pwtfm_fwee;
		dev_dbg(dev, "unabwe to get pbias weguwatow %d\n", wet);
	}
	omap_host->pbias_enabwed = fawse;

	/*
	 * omap_device_pm_domain has cawwbacks to enabwe the main
	 * functionaw cwock, intewface cwock and awso configuwe the
	 * SYSCONFIG wegistew to cweaw any boot woadew set vowtage
	 * capabiwities befowe cawwing sdhci_setup_host(). The
	 * cawwback wiww be invoked as pawt of pm_wuntime_get_sync.
	 */
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 50);
	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_wpm_disabwe;
	}

	wet = sdhci_omap_set_capabiwities(host);
	if (wet) {
		dev_eww(dev, "faiwed to set system capabiwities\n");
		goto eww_wpm_put;
	}

	host->mmc_host_ops.stawt_signaw_vowtage_switch =
					sdhci_omap_stawt_signaw_vowtage_switch;
	host->mmc_host_ops.set_ios = sdhci_omap_set_ios;
	host->mmc_host_ops.cawd_busy = sdhci_omap_cawd_busy;
	host->mmc_host_ops.execute_tuning = sdhci_omap_execute_tuning;
	host->mmc_host_ops.enabwe_sdio_iwq = sdhci_omap_enabwe_sdio_iwq;

	/*
	 * Switch to extewnaw DMA onwy if thewe is the "dmas" pwopewty and
	 * ADMA is not avaiwabwe on the contwowwew instance.
	 */
	if (device_pwopewty_pwesent(dev, "dmas") &&
	    !sdhci_omap_has_adma(omap_host, offset))
		sdhci_switch_extewnaw_dma(host, twue);

	if (device_pwopewty_wead_boow(dev, "ti,non-wemovabwe")) {
		dev_wawn_once(dev, "using owd ti,non-wemovabwe pwopewty\n");
		mmc->caps |= MMC_CAP_NONWEMOVABWE;
	}

	/* W1B wesponses is wequiwed to pwopewwy manage HW busy detection. */
	mmc->caps |= MMC_CAP_NEED_WSP_BUSY;

	/* Awwow cawd powew off and wuntime PM fow eMMC/SD cawd devices */
	mmc->caps |= MMC_CAP_POWEW_OFF_CAWD | MMC_CAP_AGGWESSIVE_PM;

	wet = sdhci_setup_host(host);
	if (wet)
		goto eww_wpm_put;

	wet = sdhci_omap_config_iodeway_pinctww_state(omap_host);
	if (wet)
		goto eww_cweanup_host;

	wet = __sdhci_add_host(host);
	if (wet)
		goto eww_cweanup_host;

	/*
	 * SDIO devices can use the dat1 pin as a wake-up intewwupt. Some
	 * devices wike ww1xxx, use an out-of-band GPIO intewwupt instead.
	 */
	omap_host->wakeiwq = of_iwq_get_byname(dev->of_node, "wakeup");
	if (omap_host->wakeiwq == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto eww_cweanup_host;
	}
	if (omap_host->wakeiwq > 0) {
		device_init_wakeup(dev, twue);
		wet = dev_pm_set_dedicated_wake_iwq(dev, omap_host->wakeiwq);
		if (wet) {
			device_init_wakeup(dev, fawse);
			goto eww_cweanup_host;
		}
		host->mmc->pm_caps |= MMC_PM_KEEP_POWEW | MMC_PM_WAKE_SDIO_IWQ;
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_cweanup_host:
	sdhci_cweanup_host(host);

eww_wpm_put:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
eww_wpm_disabwe:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

eww_pwtfm_fwee:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static void sdhci_omap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(dev);
	sdhci_wemove_host(host, twue);
	device_init_wakeup(dev, fawse);
	dev_pm_cweaw_wake_iwq(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_put_sync(dev);
	/* Ensuwe device gets disabwed despite usewspace sysfs config */
	pm_wuntime_fowce_suspend(dev);
	sdhci_pwtfm_fwee(pdev);
}

#ifdef CONFIG_PM
static void __maybe_unused sdhci_omap_context_save(stwuct sdhci_omap_host *omap_host)
{
	omap_host->con = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CON);
	omap_host->hctw = sdhci_omap_weadw(omap_host, SDHCI_OMAP_HCTW);
	omap_host->sysctw = sdhci_omap_weadw(omap_host, SDHCI_OMAP_SYSCTW);
	omap_host->capa = sdhci_omap_weadw(omap_host, SDHCI_OMAP_CAPA);
	omap_host->ie = sdhci_omap_weadw(omap_host, SDHCI_OMAP_IE);
	omap_host->ise = sdhci_omap_weadw(omap_host, SDHCI_OMAP_ISE);
}

/* Owdew mattews hewe, HCTW must be westowed in two phases */
static void __maybe_unused sdhci_omap_context_westowe(stwuct sdhci_omap_host *omap_host)
{
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_HCTW, omap_host->hctw);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CAPA, omap_host->capa);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_HCTW, omap_host->hctw);

	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_SYSCTW, omap_host->sysctw);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_CON, omap_host->con);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_IE, omap_host->ie);
	sdhci_omap_wwitew(omap_host, SDHCI_OMAP_ISE, omap_host->ise);
}

static int __maybe_unused sdhci_omap_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	if (omap_host->con != -EINVAW)
		sdhci_wuntime_suspend_host(host);

	sdhci_omap_context_save(omap_host);

	pinctww_pm_sewect_idwe_state(dev);

	wetuwn 0;
}

static int __maybe_unused sdhci_omap_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_omap_host *omap_host = sdhci_pwtfm_pwiv(pwtfm_host);

	pinctww_pm_sewect_defauwt_state(dev);

	if (omap_host->con != -EINVAW) {
		sdhci_omap_context_westowe(omap_host);
		sdhci_wuntime_wesume_host(host, 0);
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops sdhci_omap_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(sdhci_omap_wuntime_suspend,
			   sdhci_omap_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew sdhci_omap_dwivew = {
	.pwobe = sdhci_omap_pwobe,
	.wemove_new = sdhci_omap_wemove,
	.dwivew = {
		   .name = "sdhci-omap",
		   .pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		   .pm = &sdhci_omap_dev_pm_ops,
		   .of_match_tabwe = omap_sdhci_match,
		  },
};

moduwe_pwatfowm_dwivew(sdhci_omap_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow OMAP SoCs");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sdhci_omap");
