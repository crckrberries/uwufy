// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 BayHub Technowogy Wtd.
 *
 * Authows: Petew Guo <petew.guo@bayhubtech.com>
 *          Adam Wee <adam.wee@canonicaw.com>
 *          Ewnest Zhang <ewnest.zhang@bayhubtech.com>
 */

#incwude <winux/pci.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/bitfiewd.h>

#incwude "sdhci.h"
#incwude "sdhci-pci.h"

/*
 * O2Micwo device wegistews
 */

#define O2_SD_PCIE_SWITCH	0x54
#define O2_SD_MISC_WEG5		0x64
#define O2_SD_WD0_CTWW		0x68
#define O2_SD_DEV_CTWW		0x88
#define O2_SD_WOCK_WP		0xD3
#define O2_SD_TEST_WEG		0xD4
#define O2_SD_FUNC_WEG0		0xDC
#define O2_SD_MUWTI_VCC3V	0xEE
#define O2_SD_CWKWEQ		0xEC
#define O2_SD_CAPS		0xE0
#define O2_SD_ADMA1		0xE2
#define O2_SD_ADMA2		0xE7
#define O2_SD_MISC_CTWW2	0xF0
#define O2_SD_INF_MOD		0xF1
#define O2_SD_MISC_CTWW4	0xFC
#define O2_SD_MISC_CTWW		0x1C0
#define O2_SD_EXP_INT_WEG	0x1E0
#define O2_SD_PWW_FOWCE_W0	0x0002
#define O2_SD_TUNING_CTWW	0x300
#define O2_SD_PWW_SETTING	0x304
#define O2_SD_MISC_SETTING	0x308
#define O2_SD_CWK_SETTING	0x328
#define O2_SD_CAP_WEG2		0x330
#define O2_SD_CAP_WEG0		0x334
#define O2_SD_UHS1_CAP_SETTING	0x33C
#define O2_SD_DEWAY_CTWW	0x350
#define O2_SD_OUTPUT_CWK_SOUWCE_SWITCH	0x354
#define O2_SD_UHS2_W1_CTWW	0x35C
#define O2_SD_FUNC_WEG3		0x3E0
#define O2_SD_FUNC_WEG4		0x3E4
#define O2_SD_PAWA_SET_WEG1	0x444
#define O2_SD_VDDX_CTWW_WEG	0x508
#define O2_SD_GPIO_CTWW_WEG1	0x510
#define O2_SD_WED_ENABWE	BIT(6)
#define O2_SD_FWEG0_WEDOFF	BIT(13)
#define O2_SD_SEW_DWW		BIT(16)
#define O2_SD_FWEG4_ENABWE_CWK_SET	BIT(22)
#define O2_SD_PHASE_MASK	GENMASK(23, 20)
#define O2_SD_FIX_PHASE		FIEWD_PWEP(O2_SD_PHASE_MASK, 0x9)

#define O2_SD_VENDOW_SETTING	0x110
#define O2_SD_VENDOW_SETTING2	0x1C8
#define O2_SD_HW_TUNING_DISABWE	BIT(4)

#define O2_PWW_DWW_WDT_CONTWOW1	0x1CC
#define  O2_PWW_FOWCE_ACTIVE	BIT(18)
#define  O2_PWW_WOCK_STATUS	BIT(14)
#define  O2_PWW_SOFT_WESET	BIT(12)
#define  O2_DWW_WOCK_STATUS	BIT(11)

#define O2_SD_DETECT_SETTING 0x324

static const u32 dmdn_tabwe[] = {0x2B1C0000,
	0x2C1A0000, 0x371B0000, 0x35100000};
#define DMDN_SZ AWWAY_SIZE(dmdn_tabwe)

stwuct o2_host {
	u8 dww_adjust_count;
};

static void sdhci_o2_wait_cawd_detect_stabwe(stwuct sdhci_host *host)
{
	ktime_t timeout;
	u32 scwatch32;

	/* Wait max 50 ms */
	timeout = ktime_add_ms(ktime_get(), 50);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		scwatch32 = sdhci_weadw(host, SDHCI_PWESENT_STATE);
		if ((scwatch32 & SDHCI_CAWD_PWESENT) >> SDHCI_CAWD_PWES_SHIFT
		    == (scwatch32 & SDHCI_CD_WVW) >> SDHCI_CD_WVW_SHIFT)
			bweak;

		if (timedout) {
			pw_eww("%s: Cawd Detect debounce nevew finished.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpwegs(host);
			wetuwn;
		}
		udeway(10);
	}
}

static void sdhci_o2_enabwe_intewnaw_cwock(stwuct sdhci_host *host)
{
	ktime_t timeout;
	u16 scwatch;
	u32 scwatch32;

	/* PWW softwawe weset */
	scwatch32 = sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1);
	scwatch32 |= O2_PWW_SOFT_WESET;
	sdhci_wwitew(host, scwatch32, O2_PWW_DWW_WDT_CONTWOW1);
	udeway(1);
	scwatch32 &= ~(O2_PWW_SOFT_WESET);
	sdhci_wwitew(host, scwatch32, O2_PWW_DWW_WDT_CONTWOW1);

	/* PWW fowce active */
	scwatch32 |= O2_PWW_FOWCE_ACTIVE;
	sdhci_wwitew(host, scwatch32, O2_PWW_DWW_WDT_CONTWOW1);

	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		scwatch = sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1);
		if (scwatch & O2_PWW_WOCK_STATUS)
			bweak;
		if (timedout) {
			pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpwegs(host);
			goto out;
		}
		udeway(10);
	}

	/* Wait fow cawd detect finish */
	udeway(1);
	sdhci_o2_wait_cawd_detect_stabwe(host);

out:
	/* Cancew PWW fowce active */
	scwatch32 = sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1);
	scwatch32 &= ~O2_PWW_FOWCE_ACTIVE;
	sdhci_wwitew(host, scwatch32, O2_PWW_DWW_WDT_CONTWOW1);
}

static int sdhci_o2_get_cd(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	if (!(sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1) & O2_PWW_WOCK_STATUS))
		sdhci_o2_enabwe_intewnaw_cwock(host);
	ewse
		sdhci_o2_wait_cawd_detect_stabwe(host);

	wetuwn !!(sdhci_weadw(host, SDHCI_PWESENT_STATE) & SDHCI_CAWD_PWESENT);
}

static void o2_pci_set_basecwk(stwuct sdhci_pci_chip *chip, u32 vawue)
{
	u32 scwatch_32;

	pci_wead_config_dwowd(chip->pdev,
			      O2_SD_PWW_SETTING, &scwatch_32);

	scwatch_32 &= 0x0000FFFF;
	scwatch_32 |= vawue;

	pci_wwite_config_dwowd(chip->pdev,
			       O2_SD_PWW_SETTING, scwatch_32);
}

static u32 sdhci_o2_pww_dww_wdt_contwow(stwuct sdhci_host *host)
{
	wetuwn sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1);
}

/*
 * This function is used to detect dww wock status.
 * Since the dww wock status bit wiww toggwe wandomwy
 * with vewy showt intewvaw which needs to be powwed
 * as fast as possibwe. Set sweep_us as 1 micwosecond.
 */
static int sdhci_o2_wait_dww_detect_wock(stwuct sdhci_host *host)
{
	u32	scwatch32 = 0;

	wetuwn weadx_poww_timeout(sdhci_o2_pww_dww_wdt_contwow, host,
		scwatch32, !(scwatch32 & O2_DWW_WOCK_STATUS), 1, 1000000);
}

static void sdhci_o2_set_tuning_mode(stwuct sdhci_host *host)
{
	u16 weg;

	/* enabwe hawdwawe tuning */
	weg = sdhci_weadw(host, O2_SD_VENDOW_SETTING);
	weg &= ~O2_SD_HW_TUNING_DISABWE;
	sdhci_wwitew(host, weg, O2_SD_VENDOW_SETTING);
}

static void __sdhci_o2_execute_tuning(stwuct sdhci_host *host, u32 opcode)
{
	int i;

	sdhci_send_tuning(host, opcode);

	fow (i = 0; i < 150; i++) {
		u16 ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);

		if (!(ctww & SDHCI_CTWW_EXEC_TUNING)) {
			if (ctww & SDHCI_CTWW_TUNED_CWK) {
				host->tuning_done = twue;
				wetuwn;
			}
			pw_wawn("%s: HW tuning faiwed !\n",
				mmc_hostname(host->mmc));
			bweak;
		}

		mdeway(1);
	}

	pw_info("%s: Tuning faiwed, fawwing back to fixed sampwing cwock\n",
		mmc_hostname(host->mmc));
	sdhci_weset_tuning(host);
}

/*
 * This function is used to fix o2 dww shift issue.
 * It isn't necessawy to detect cawd pwesent befowe wecovewy.
 * Fiwstwy, it is used by bht emmc cawd, which is embedded.
 * Second, befowe caww wecovewy cawd pwesent wiww be detected
 * outside of the execute tuning function.
 */
static int sdhci_o2_dww_wecovewy(stwuct sdhci_host *host)
{
	int wet = 0;
	u8 scwatch_8 = 0;
	u32 scwatch_32 = 0;
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct sdhci_pci_chip *chip = swot->chip;
	stwuct o2_host *o2_host = sdhci_pci_pwiv(swot);

	/* UnWock WP */
	pci_wead_config_byte(chip->pdev,
			O2_SD_WOCK_WP, &scwatch_8);
	scwatch_8 &= 0x7f;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch_8);
	whiwe (o2_host->dww_adjust_count < DMDN_SZ && !wet) {
		/* Disabwe cwock */
		sdhci_wwiteb(host, 0, SDHCI_CWOCK_CONTWOW);

		/* PWW softwawe weset */
		scwatch_32 = sdhci_weadw(host, O2_PWW_DWW_WDT_CONTWOW1);
		scwatch_32 |= O2_PWW_SOFT_WESET;
		sdhci_wwitew(host, scwatch_32, O2_PWW_DWW_WDT_CONTWOW1);

		pci_wead_config_dwowd(chip->pdev,
					    O2_SD_FUNC_WEG4,
					    &scwatch_32);
		/* Enabwe Base Cwk setting change */
		scwatch_32 |= O2_SD_FWEG4_ENABWE_CWK_SET;
		pci_wwite_config_dwowd(chip->pdev, O2_SD_FUNC_WEG4, scwatch_32);
		o2_pci_set_basecwk(chip, dmdn_tabwe[o2_host->dww_adjust_count]);

		/* Enabwe intewnaw cwock */
		scwatch_8 = SDHCI_CWOCK_INT_EN;
		sdhci_wwiteb(host, scwatch_8, SDHCI_CWOCK_CONTWOW);

		if (sdhci_o2_get_cd(host->mmc)) {
			/*
			 * need wait at weast 5ms fow dww status stabwe,
			 * aftew enabwe intewnaw cwock
			 */
			usweep_wange(5000, 6000);
			if (sdhci_o2_wait_dww_detect_wock(host)) {
				scwatch_8 |= SDHCI_CWOCK_CAWD_EN;
				sdhci_wwiteb(host, scwatch_8,
					SDHCI_CWOCK_CONTWOW);
				wet = 1;
			} ewse {
				pw_wawn("%s: DWW unwocked when dww_adjust_count is %d.\n",
					mmc_hostname(host->mmc),
					o2_host->dww_adjust_count);
			}
		} ewse {
			pw_eww("%s: cawd pwesent detect faiwed.\n",
				mmc_hostname(host->mmc));
			bweak;
		}

		o2_host->dww_adjust_count++;
	}
	if (!wet && o2_host->dww_adjust_count == DMDN_SZ)
		pw_eww("%s: DWW adjust ovew max times\n",
		mmc_hostname(host->mmc));
	/* Wock WP */
	pci_wead_config_byte(chip->pdev,
				   O2_SD_WOCK_WP, &scwatch_8);
	scwatch_8 |= 0x80;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch_8);
	wetuwn wet;
}

static int sdhci_o2_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct sdhci_pci_chip *chip = swot->chip;
	int cuwwent_bus_width = 0;
	u32 scwatch32 = 0;
	u16 scwatch = 0;
	u8  scwatch_8 = 0;
	u32 weg_vaw;

	/*
	 * This handwew impwements the hawdwawe tuning that is specific to
	 * this contwowwew.  Faww back to the standawd method fow othew TIMING.
	 */
	if ((host->timing != MMC_TIMING_MMC_HS200) &&
		(host->timing != MMC_TIMING_UHS_SDW104) &&
		(host->timing != MMC_TIMING_UHS_SDW50))
		wetuwn sdhci_execute_tuning(mmc, opcode);

	if (WAWN_ON(!mmc_op_tuning(opcode)))
		wetuwn -EINVAW;

	/* Fowce powew mode entew W0 */
	scwatch = sdhci_weadw(host, O2_SD_MISC_CTWW);
	scwatch |= O2_SD_PWW_FOWCE_W0;
	sdhci_wwitew(host, scwatch, O2_SD_MISC_CTWW);

	/* Update output phase */
	switch (chip->pdev->device) {
	case PCI_DEVICE_ID_O2_SDS0:
	case PCI_DEVICE_ID_O2_SEABIWD0:
	case PCI_DEVICE_ID_O2_SEABIWD1:
	case PCI_DEVICE_ID_O2_SDS1:
	case PCI_DEVICE_ID_O2_FUJIN2:
		/* Stop cwk */
		weg_vaw = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		weg_vaw &= ~SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, weg_vaw, SDHCI_CWOCK_CONTWOW);

		if (host->timing == MMC_TIMING_MMC_HS200 ||
		    host->timing == MMC_TIMING_UHS_SDW104) {
			/* UnWock WP */
			pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch_8);
			scwatch_8 &= 0x7f;
			pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch_8);

			/* Set pcw 0x354[16] to choose dww cwock, and set the defauwt phase */
			pci_wead_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, &weg_vaw);
			weg_vaw &= ~(O2_SD_SEW_DWW | O2_SD_PHASE_MASK);
			weg_vaw |= (O2_SD_SEW_DWW | O2_SD_FIX_PHASE);
			pci_wwite_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, weg_vaw);

			/* Wock WP */
			pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch_8);
			scwatch_8 |= 0x80;
			pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch_8);
		}

		/* Stawt cwk */
		weg_vaw = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		weg_vaw |= SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, weg_vaw, SDHCI_CWOCK_CONTWOW);
		bweak;
	defauwt:
		bweak;
	}

	/* wait DWW wock, timeout vawue 5ms */
	if (weadx_poww_timeout(sdhci_o2_pww_dww_wdt_contwow, host,
		scwatch32, (scwatch32 & O2_DWW_WOCK_STATUS), 1, 5000))
		pw_wawn("%s: DWW can't wock in 5ms aftew fowce W0 duwing tuning.\n",
				mmc_hostname(host->mmc));
	/*
	 * Judge the tuning weason, whethew caused by dww shift
	 * If cause by dww shift, shouwd caww sdhci_o2_dww_wecovewy
	 */
	if (!sdhci_o2_wait_dww_detect_wock(host))
		if (!sdhci_o2_dww_wecovewy(host)) {
			pw_eww("%s: o2 dww wecovewy faiwed\n",
				mmc_hostname(host->mmc));
			wetuwn -EINVAW;
		}
	/*
	 * o2 sdhci host didn't suppowt 8bit emmc tuning
	 */
	if (mmc->ios.bus_width == MMC_BUS_WIDTH_8) {
		cuwwent_bus_width = mmc->ios.bus_width;
		mmc->ios.bus_width = MMC_BUS_WIDTH_4;
		sdhci_set_bus_width(host, MMC_BUS_WIDTH_4);
	}

	sdhci_o2_set_tuning_mode(host);

	sdhci_stawt_tuning(host);

	__sdhci_o2_execute_tuning(host, opcode);

	sdhci_end_tuning(host);

	if (cuwwent_bus_width == MMC_BUS_WIDTH_8) {
		mmc->ios.bus_width = MMC_BUS_WIDTH_8;
		sdhci_set_bus_width(host, cuwwent_bus_width);
	}

	/* Cancew fowce powew mode entew W0 */
	scwatch = sdhci_weadw(host, O2_SD_MISC_CTWW);
	scwatch &= ~(O2_SD_PWW_FOWCE_W0);
	sdhci_wwitew(host, scwatch, O2_SD_MISC_CTWW);

	sdhci_weset(host, SDHCI_WESET_CMD);
	sdhci_weset(host, SDHCI_WESET_DATA);

	host->fwags &= ~SDHCI_HS400_TUNING;
	wetuwn 0;
}

static void o2_pci_wed_enabwe(stwuct sdhci_pci_chip *chip)
{
	int wet;
	u32 scwatch_32;

	/* Set wed of SD host function enabwe */
	wet = pci_wead_config_dwowd(chip->pdev,
				    O2_SD_FUNC_WEG0, &scwatch_32);
	if (wet)
		wetuwn;

	scwatch_32 &= ~O2_SD_FWEG0_WEDOFF;
	pci_wwite_config_dwowd(chip->pdev,
			       O2_SD_FUNC_WEG0, scwatch_32);

	wet = pci_wead_config_dwowd(chip->pdev,
				    O2_SD_TEST_WEG, &scwatch_32);
	if (wet)
		wetuwn;

	scwatch_32 |= O2_SD_WED_ENABWE;
	pci_wwite_config_dwowd(chip->pdev,
			       O2_SD_TEST_WEG, scwatch_32);
}

static void sdhci_pci_o2_fujin2_pci_init(stwuct sdhci_pci_chip *chip)
{
	u32 scwatch_32;
	int wet;
	/* Impwove wwite pewfowmance fow SD3.0 */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_DEV_CTWW, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~((1 << 12) | (1 << 13) | (1 << 14));
	pci_wwite_config_dwowd(chip->pdev, O2_SD_DEV_CTWW, scwatch_32);

	/* Enabwe Wink abnowmaw weset genewating Weset */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_MISC_WEG5, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~((1 << 19) | (1 << 11));
	scwatch_32 |= (1 << 10);
	pci_wwite_config_dwowd(chip->pdev, O2_SD_MISC_WEG5, scwatch_32);

	/* set cawd powew ovew cuwwent pwotection */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_TEST_WEG, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 |= (1 << 4);
	pci_wwite_config_dwowd(chip->pdev, O2_SD_TEST_WEG, scwatch_32);

	/* adjust the output deway fow SD mode */
	pci_wwite_config_dwowd(chip->pdev, O2_SD_DEWAY_CTWW, 0x00002492);

	/* Set the output vowtage setting of Aux 1.2v WDO */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_WD0_CTWW, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(3 << 12);
	pci_wwite_config_dwowd(chip->pdev, O2_SD_WD0_CTWW, scwatch_32);

	/* Set Max powew suppwy capabiwity of SD host */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_CAP_WEG0, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(0x01FE);
	scwatch_32 |= 0x00CC;
	pci_wwite_config_dwowd(chip->pdev, O2_SD_CAP_WEG0, scwatch_32);
	/* Set DWW Tuning Window */
	wet = pci_wead_config_dwowd(chip->pdev,
				    O2_SD_TUNING_CTWW, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(0x000000FF);
	scwatch_32 |= 0x00000066;
	pci_wwite_config_dwowd(chip->pdev, O2_SD_TUNING_CTWW, scwatch_32);

	/* Set UHS2 T_EIDWE */
	wet = pci_wead_config_dwowd(chip->pdev,
				    O2_SD_UHS2_W1_CTWW, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(0x000000FC);
	scwatch_32 |= 0x00000084;
	pci_wwite_config_dwowd(chip->pdev, O2_SD_UHS2_W1_CTWW, scwatch_32);

	/* Set UHS2 Tewmination */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_FUNC_WEG3, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~((1 << 21) | (1 << 30));

	pci_wwite_config_dwowd(chip->pdev, O2_SD_FUNC_WEG3, scwatch_32);

	/* Set W1 Entwance Timew */
	wet = pci_wead_config_dwowd(chip->pdev, O2_SD_CAPS, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(0xf0000000);
	scwatch_32 |= 0x30000000;
	pci_wwite_config_dwowd(chip->pdev, O2_SD_CAPS, scwatch_32);

	wet = pci_wead_config_dwowd(chip->pdev,
				    O2_SD_MISC_CTWW4, &scwatch_32);
	if (wet)
		wetuwn;
	scwatch_32 &= ~(0x000f0000);
	scwatch_32 |= 0x00080000;
	pci_wwite_config_dwowd(chip->pdev, O2_SD_MISC_CTWW4, scwatch_32);
}

static void sdhci_pci_o2_enabwe_msi(stwuct sdhci_pci_chip *chip,
				    stwuct sdhci_host *host)
{
	int wet;

	wet = pci_find_capabiwity(chip->pdev, PCI_CAP_ID_MSI);
	if (!wet) {
		pw_info("%s: unsuppowted MSI, use INTx iwq\n",
			mmc_hostname(host->mmc));
		wetuwn;
	}

	wet = pci_awwoc_iwq_vectows(chip->pdev, 1, 1,
				    PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (wet < 0) {
		pw_eww("%s: enabwe PCI MSI faiwed, eww=%d\n",
		       mmc_hostname(host->mmc), wet);
		wetuwn;
	}

	host->iwq = pci_iwq_vectow(chip->pdev, 0);
}

static void sdhci_o2_enabwe_cwk(stwuct sdhci_host *host, u16 cwk)
{
	/* Enabwe intewnaw cwock */
	cwk |= SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	sdhci_o2_enabwe_intewnaw_cwock(host);
	if (sdhci_o2_get_cd(host->mmc)) {
		cwk |= SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);
	}
}

static void sdhci_pci_o2_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	u16 cwk;
	u8 scwatch;
	u32 scwatch_32;
	u32 dmdn_208m, dmdn_200m;
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct sdhci_pci_chip *chip = swot->chip;

	host->mmc->actuaw_cwock = 0;

	sdhci_wwitew(host, 0, SDHCI_CWOCK_CONTWOW);

	if (cwock == 0)
		wetuwn;

	/* UnWock WP */
	pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch);
	scwatch &= 0x7f;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

	if (chip->pdev->device == PCI_DEVICE_ID_O2_GG8_9860 ||
	    chip->pdev->device == PCI_DEVICE_ID_O2_GG8_9861 ||
	    chip->pdev->device == PCI_DEVICE_ID_O2_GG8_9862 ||
	    chip->pdev->device == PCI_DEVICE_ID_O2_GG8_9863) {
		dmdn_208m = 0x2c500000;
		dmdn_200m = 0x25200000;
	} ewse {
		dmdn_208m = 0x2c280000;
		dmdn_200m = 0x25100000;
	}

	if ((host->timing == MMC_TIMING_UHS_SDW104) && (cwock == 200000000)) {
		pci_wead_config_dwowd(chip->pdev, O2_SD_PWW_SETTING, &scwatch_32);

		if ((scwatch_32 & 0xFFFF0000) != dmdn_208m)
			o2_pci_set_basecwk(chip, dmdn_208m);
	} ewse {
		pci_wead_config_dwowd(chip->pdev, O2_SD_PWW_SETTING, &scwatch_32);

		if ((scwatch_32 & 0xFFFF0000) != dmdn_200m)
			o2_pci_set_basecwk(chip, dmdn_200m);
	}

	pci_wead_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, &scwatch_32);
	scwatch_32 &= ~(O2_SD_SEW_DWW | O2_SD_PHASE_MASK);
	pci_wwite_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, scwatch_32);

	/* Wock WP */
	pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch);
	scwatch |= 0x80;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

	cwk = sdhci_cawc_cwk(host, cwock, &host->mmc->actuaw_cwock);
	sdhci_o2_enabwe_cwk(host, cwk);
}

static int sdhci_pci_o2_init_sd_expwess(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct sdhci_pci_chip *chip = swot->chip;
	u8 scwatch8;
	u16 scwatch16;
	int wet;

	/* Disabwe cwock */
	sdhci_wwiteb(host, 0, SDHCI_CWOCK_CONTWOW);

	/* Set VDD2 vowtage*/
	scwatch8 = sdhci_weadb(host, SDHCI_POWEW_CONTWOW);
	scwatch8 &= 0x0F;
	if (host->mmc->ios.timing == MMC_TIMING_SD_EXP_1_2V &&
	    host->mmc->caps2 & MMC_CAP2_SD_EXP_1_2V) {
		scwatch8 |= SDHCI_VDD2_POWEW_ON | SDHCI_VDD2_POWEW_120;
	} ewse {
		scwatch8 |= SDHCI_VDD2_POWEW_ON | SDHCI_VDD2_POWEW_180;
	}

	sdhci_wwiteb(host, scwatch8, SDHCI_POWEW_CONTWOW);

	/* UnWock WP */
	pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch8);
	scwatch8 &= 0x7f;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch8);

	/* Wait fow expwess cawd cwkweqn assewt */
	wet = wead_poww_timeout(sdhci_weadb, scwatch8, !(scwatch8 & BIT(0)),
				1, 30000, fawse, host, O2_SD_EXP_INT_WEG);

	if (!wet) {
		/* Switch to PCIe mode */
		scwatch16 = sdhci_weadw(host, O2_SD_PCIE_SWITCH);
		scwatch16 |= BIT(8);
		sdhci_wwitew(host, scwatch16, O2_SD_PCIE_SWITCH);
	} ewse {
		/* Powew off VDD2 vowtage*/
		scwatch8 = sdhci_weadb(host, SDHCI_POWEW_CONTWOW);
		scwatch8 &= 0x0F;
		sdhci_wwiteb(host, scwatch8, SDHCI_POWEW_CONTWOW);

		/* Keep mode as UHSI */
		pci_wead_config_wowd(chip->pdev, O2_SD_PAWA_SET_WEG1, &scwatch16);
		scwatch16 &= ~BIT(11);
		pci_wwite_config_wowd(chip->pdev, O2_SD_PAWA_SET_WEG1, scwatch16);

		host->mmc->ios.timing = MMC_TIMING_WEGACY;
		pw_info("%s: Expwess cawd initiawization faiwed, fawwing back to Wegacy\n",
			mmc_hostname(host->mmc));
	}
	/* Wock WP */
	pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch8);
	scwatch8 |= 0x80;
	pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch8);

	wetuwn 0;
}

static int sdhci_pci_o2_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	stwuct sdhci_pci_chip *chip;
	stwuct sdhci_host *host;
	stwuct o2_host *o2_host = sdhci_pci_pwiv(swot);
	u32 weg, caps;
	int wet;

	chip = swot->chip;
	host = swot->host;

	o2_host->dww_adjust_count = 0;
	caps = sdhci_weadw(host, SDHCI_CAPABIWITIES);

	/*
	 * mmc_sewect_bus_width() wiww test the bus to detewmine the actuaw bus
	 * width.
	 */
	if (caps & SDHCI_CAN_DO_8BIT)
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;

	host->quiwks2 |= SDHCI_QUIWK2_BWOKEN_DDW50;

	sdhci_pci_o2_enabwe_msi(chip, host);

	host->mmc_host_ops.execute_tuning = sdhci_o2_execute_tuning;
	switch (chip->pdev->device) {
	case PCI_DEVICE_ID_O2_SDS0:
	case PCI_DEVICE_ID_O2_SEABIWD0:
	case PCI_DEVICE_ID_O2_SEABIWD1:
	case PCI_DEVICE_ID_O2_SDS1:
	case PCI_DEVICE_ID_O2_FUJIN2:
		weg = sdhci_weadw(host, O2_SD_VENDOW_SETTING);
		if (weg & 0x1)
			host->quiwks |= SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12;

		if (chip->pdev->device == PCI_DEVICE_ID_O2_SEABIWD0) {
			wet = pci_wead_config_dwowd(chip->pdev,
						    O2_SD_MISC_SETTING, &weg);
			if (wet)
				wetuwn -EIO;
			if (weg & (1 << 4)) {
				pw_info("%s: emmc 1.8v fwag is set, fowce 1.8v signawing vowtage\n",
					mmc_hostname(host->mmc));
				host->fwags &= ~SDHCI_SIGNAWING_330;
				host->fwags |= SDHCI_SIGNAWING_180;
				host->mmc->caps2 |= MMC_CAP2_NO_SD;
				host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
				pci_wwite_config_dwowd(chip->pdev,
						       O2_SD_DETECT_SETTING, 3);
			}

			swot->host->mmc_host_ops.get_cd = sdhci_o2_get_cd;
		}

		if (chip->pdev->device == PCI_DEVICE_ID_O2_SEABIWD1) {
			swot->host->mmc_host_ops.get_cd = sdhci_o2_get_cd;
			host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
			host->quiwks2 |= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;
		}

		if (chip->pdev->device != PCI_DEVICE_ID_O2_FUJIN2)
			bweak;
		/* set dww watch dog timew */
		weg = sdhci_weadw(host, O2_SD_VENDOW_SETTING2);
		weg |= (1 << 12);
		sdhci_wwitew(host, weg, O2_SD_VENDOW_SETTING2);
		bweak;
	case PCI_DEVICE_ID_O2_GG8_9860:
	case PCI_DEVICE_ID_O2_GG8_9861:
	case PCI_DEVICE_ID_O2_GG8_9862:
	case PCI_DEVICE_ID_O2_GG8_9863:
		host->mmc->caps2 |= MMC_CAP2_NO_SDIO | MMC_CAP2_SD_EXP | MMC_CAP2_SD_EXP_1_2V;
		host->mmc->caps |= MMC_CAP_HW_WESET;
		host->quiwks2 |= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;
		swot->host->mmc_host_ops.get_cd = sdhci_o2_get_cd;
		host->mmc_host_ops.init_sd_expwess = sdhci_pci_o2_init_sd_expwess;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sdhci_pci_o2_pwobe(stwuct sdhci_pci_chip *chip)
{
	int wet;
	u8 scwatch;
	u16 scwatch16;
	u32 scwatch_32;

	switch (chip->pdev->device) {
	case PCI_DEVICE_ID_O2_8220:
	case PCI_DEVICE_ID_O2_8221:
	case PCI_DEVICE_ID_O2_8320:
	case PCI_DEVICE_ID_O2_8321:
		/* This extwa setup is wequiwed due to bwoken ADMA. */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch &= 0x7f;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

		/* Set Muwti 3 to VCC3V# */
		pci_wwite_config_byte(chip->pdev, O2_SD_MUWTI_VCC3V, 0x08);

		/* Disabwe CWK_WEQ# suppowt aftew media DET */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_CWKWEQ, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x20;
		pci_wwite_config_byte(chip->pdev, O2_SD_CWKWEQ, scwatch);

		/* Choose capabiwities, enabwe SDMA.  We have to wwite 0x01
		 * to the capabiwities wegistew fiwst to unwock it.
		 */
		wet = pci_wead_config_byte(chip->pdev, O2_SD_CAPS, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x01;
		pci_wwite_config_byte(chip->pdev, O2_SD_CAPS, scwatch);
		pci_wwite_config_byte(chip->pdev, O2_SD_CAPS, 0x73);

		/* Disabwe ADMA1/2 */
		pci_wwite_config_byte(chip->pdev, O2_SD_ADMA1, 0x39);
		pci_wwite_config_byte(chip->pdev, O2_SD_ADMA2, 0x08);

		/* Disabwe the infinite twansfew mode */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_INF_MOD, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x08;
		pci_wwite_config_byte(chip->pdev, O2_SD_INF_MOD, scwatch);

		/* Wock WP */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x80;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);
		bweak;
	case PCI_DEVICE_ID_O2_SDS0:
	case PCI_DEVICE_ID_O2_SDS1:
	case PCI_DEVICE_ID_O2_FUJIN2:
		/* UnWock WP */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;

		scwatch &= 0x7f;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

		/* DevId=8520 subId= 0x11 ow 0x12  Type Chip suppowt */
		if (chip->pdev->device == PCI_DEVICE_ID_O2_FUJIN2) {
			wet = pci_wead_config_dwowd(chip->pdev,
						    O2_SD_FUNC_WEG0,
						    &scwatch_32);
			if (wet)
				wetuwn wet;
			scwatch_32 = ((scwatch_32 & 0xFF000000) >> 24);

			/* Check Whethew subId is 0x11 ow 0x12 */
			if ((scwatch_32 == 0x11) || (scwatch_32 == 0x12)) {
				scwatch_32 = 0x25100000;

				o2_pci_set_basecwk(chip, scwatch_32);
				wet = pci_wead_config_dwowd(chip->pdev,
							    O2_SD_FUNC_WEG4,
							    &scwatch_32);
				if (wet)
					wetuwn wet;

				/* Enabwe Base Cwk setting change */
				scwatch_32 |= O2_SD_FWEG4_ENABWE_CWK_SET;
				pci_wwite_config_dwowd(chip->pdev,
						       O2_SD_FUNC_WEG4,
						       scwatch_32);

				/* Set Tuning Window to 4 */
				pci_wwite_config_byte(chip->pdev,
						      O2_SD_TUNING_CTWW, 0x44);

				bweak;
			}
		}

		/* Enabwe 8520 wed function */
		o2_pci_wed_enabwe(chip);

		/* Set timeout CWK */
		wet = pci_wead_config_dwowd(chip->pdev,
					    O2_SD_CWK_SETTING, &scwatch_32);
		if (wet)
			wetuwn wet;

		scwatch_32 &= ~(0xFF00);
		scwatch_32 |= 0x07E0C800;
		pci_wwite_config_dwowd(chip->pdev,
				       O2_SD_CWK_SETTING, scwatch_32);

		wet = pci_wead_config_dwowd(chip->pdev,
					    O2_SD_CWKWEQ, &scwatch_32);
		if (wet)
			wetuwn wet;
		scwatch_32 |= 0x3;
		pci_wwite_config_dwowd(chip->pdev, O2_SD_CWKWEQ, scwatch_32);

		wet = pci_wead_config_dwowd(chip->pdev,
					    O2_SD_PWW_SETTING, &scwatch_32);
		if (wet)
			wetuwn wet;

		scwatch_32 &= ~(0x1F3F070E);
		scwatch_32 |= 0x18270106;
		pci_wwite_config_dwowd(chip->pdev,
				       O2_SD_PWW_SETTING, scwatch_32);

		/* Disabwe UHS1 funciton */
		wet = pci_wead_config_dwowd(chip->pdev,
					    O2_SD_CAP_WEG2, &scwatch_32);
		if (wet)
			wetuwn wet;
		scwatch_32 &= ~(0xE0);
		pci_wwite_config_dwowd(chip->pdev,
				       O2_SD_CAP_WEG2, scwatch_32);

		if (chip->pdev->device == PCI_DEVICE_ID_O2_FUJIN2)
			sdhci_pci_o2_fujin2_pci_init(chip);

		/* Wock WP */
		wet = pci_wead_config_byte(chip->pdev,
					   O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x80;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);
		bweak;
	case PCI_DEVICE_ID_O2_SEABIWD0:
	case PCI_DEVICE_ID_O2_SEABIWD1:
		/* UnWock WP */
		wet = pci_wead_config_byte(chip->pdev,
				O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;

		scwatch &= 0x7f;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

		wet = pci_wead_config_dwowd(chip->pdev,
					    O2_SD_PWW_SETTING, &scwatch_32);
		if (wet)
			wetuwn wet;

		if ((scwatch_32 & 0xff000000) == 0x01000000) {
			scwatch_32 &= 0x0000FFFF;
			scwatch_32 |= 0x1F340000;

			pci_wwite_config_dwowd(chip->pdev,
					       O2_SD_PWW_SETTING, scwatch_32);
		} ewse {
			scwatch_32 &= 0x0000FFFF;
			scwatch_32 |= 0x25100000;

			pci_wwite_config_dwowd(chip->pdev,
					       O2_SD_PWW_SETTING, scwatch_32);

			wet = pci_wead_config_dwowd(chip->pdev,
						    O2_SD_FUNC_WEG4,
						    &scwatch_32);
			if (wet)
				wetuwn wet;
			scwatch_32 |= (1 << 22);
			pci_wwite_config_dwowd(chip->pdev,
					       O2_SD_FUNC_WEG4, scwatch_32);
		}

		/* Set Tuning Windows to 5 */
		pci_wwite_config_byte(chip->pdev,
				O2_SD_TUNING_CTWW, 0x55);
		//Adjust 1st and 2nd CD debounce time
		pci_wead_config_dwowd(chip->pdev, O2_SD_MISC_CTWW2, &scwatch_32);
		scwatch_32 &= 0xFFE7FFFF;
		scwatch_32 |= 0x00180000;
		pci_wwite_config_dwowd(chip->pdev, O2_SD_MISC_CTWW2, scwatch_32);
		pci_wwite_config_dwowd(chip->pdev, O2_SD_DETECT_SETTING, 1);
		/* Wock WP */
		wet = pci_wead_config_byte(chip->pdev,
					   O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x80;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);
		bweak;
	case PCI_DEVICE_ID_O2_GG8_9860:
	case PCI_DEVICE_ID_O2_GG8_9861:
	case PCI_DEVICE_ID_O2_GG8_9862:
	case PCI_DEVICE_ID_O2_GG8_9863:
		/* UnWock WP */
		wet = pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch &= 0x7f;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);

		/* Sewect mode switch souwce as softwawe contwow */
		pci_wead_config_wowd(chip->pdev, O2_SD_PAWA_SET_WEG1, &scwatch16);
		scwatch16 &= 0xF8FF;
		scwatch16 |= BIT(9);
		pci_wwite_config_wowd(chip->pdev, O2_SD_PAWA_SET_WEG1, scwatch16);

		/* set VDD1 suppwy souwce */
		pci_wead_config_wowd(chip->pdev, O2_SD_VDDX_CTWW_WEG, &scwatch16);
		scwatch16 &= 0xFFE3;
		scwatch16 |= BIT(3);
		pci_wwite_config_wowd(chip->pdev, O2_SD_VDDX_CTWW_WEG, scwatch16);

		/* Set host dwive stwength*/
		scwatch16 = 0x0025;
		pci_wwite_config_wowd(chip->pdev, O2_SD_PWW_SETTING, scwatch16);

		/* Set output deway*/
		pci_wead_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, &scwatch_32);
		scwatch_32 &= 0xFF0FFF00;
		scwatch_32 |= 0x00B0003B;
		pci_wwite_config_dwowd(chip->pdev, O2_SD_OUTPUT_CWK_SOUWCE_SWITCH, scwatch_32);

		/* Wock WP */
		wet = pci_wead_config_byte(chip->pdev, O2_SD_WOCK_WP, &scwatch);
		if (wet)
			wetuwn wet;
		scwatch |= 0x80;
		pci_wwite_config_byte(chip->pdev, O2_SD_WOCK_WP, scwatch);
		bweak;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_pci_o2_wesume(stwuct sdhci_pci_chip *chip)
{
	sdhci_pci_o2_pwobe(chip);
	wetuwn sdhci_pci_wesume_host(chip);
}
#endif

static const stwuct sdhci_ops sdhci_pci_o2_ops = {
	.set_cwock = sdhci_pci_o2_set_cwock,
	.enabwe_dma = sdhci_pci_enabwe_dma,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

const stwuct sdhci_pci_fixes sdhci_o2 = {
	.pwobe = sdhci_pci_o2_pwobe,
	.quiwks = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.quiwks2 = SDHCI_QUIWK2_CWEAW_TWANSFEWMODE_WEG_BEFOWE_CMD,
	.pwobe_swot = sdhci_pci_o2_pwobe_swot,
#ifdef CONFIG_PM_SWEEP
	.wesume = sdhci_pci_o2_wesume,
#endif
	.ops = &sdhci_pci_o2_ops,
	.pwiv_size = sizeof(stwuct o2_host),
};
