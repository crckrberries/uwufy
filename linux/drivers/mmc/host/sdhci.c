// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/host/sdhci.c - Secuwe Digitaw Host Contwowwew Intewface dwivew
 *
 *  Copywight (C) 2005-2008 Piewwe Ossman, Aww Wights Wesewved.
 *
 * Thanks to the fowwowing companies fow theiw suppowt:
 *
 *     - JMicwon (hawdwawe and technicaw suppowt)
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ktime.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sizes.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>

#incwude <winux/weds.h>

#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude "sdhci.h"

#define DWIVEW_NAME "sdhci"

#define DBG(f, x...) \
	pw_debug("%s: " DWIVEW_NAME ": " f, mmc_hostname(host->mmc), ## x)

#define SDHCI_DUMP(f, x...) \
	pw_eww("%s: " DWIVEW_NAME ": " f, mmc_hostname(host->mmc), ## x)

#define MAX_TUNING_WOOP 40

static unsigned int debug_quiwks = 0;
static unsigned int debug_quiwks2;

static void sdhci_enabwe_pweset_vawue(stwuct sdhci_host *host, boow enabwe);

static boow sdhci_send_command(stwuct sdhci_host *host, stwuct mmc_command *cmd);

void sdhci_dumpwegs(stwuct sdhci_host *host)
{
	SDHCI_DUMP("============ SDHCI WEGISTEW DUMP ===========\n");

	SDHCI_DUMP("Sys addw:  0x%08x | Vewsion:  0x%08x\n",
		   sdhci_weadw(host, SDHCI_DMA_ADDWESS),
		   sdhci_weadw(host, SDHCI_HOST_VEWSION));
	SDHCI_DUMP("Bwk size:  0x%08x | Bwk cnt:  0x%08x\n",
		   sdhci_weadw(host, SDHCI_BWOCK_SIZE),
		   sdhci_weadw(host, SDHCI_BWOCK_COUNT));
	SDHCI_DUMP("Awgument:  0x%08x | Twn mode: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_AWGUMENT),
		   sdhci_weadw(host, SDHCI_TWANSFEW_MODE));
	SDHCI_DUMP("Pwesent:   0x%08x | Host ctw: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_PWESENT_STATE),
		   sdhci_weadb(host, SDHCI_HOST_CONTWOW));
	SDHCI_DUMP("Powew:     0x%08x | Bwk gap:  0x%08x\n",
		   sdhci_weadb(host, SDHCI_POWEW_CONTWOW),
		   sdhci_weadb(host, SDHCI_BWOCK_GAP_CONTWOW));
	SDHCI_DUMP("Wake-up:   0x%08x | Cwock:    0x%08x\n",
		   sdhci_weadb(host, SDHCI_WAKE_UP_CONTWOW),
		   sdhci_weadw(host, SDHCI_CWOCK_CONTWOW));
	SDHCI_DUMP("Timeout:   0x%08x | Int stat: 0x%08x\n",
		   sdhci_weadb(host, SDHCI_TIMEOUT_CONTWOW),
		   sdhci_weadw(host, SDHCI_INT_STATUS));
	SDHCI_DUMP("Int enab:  0x%08x | Sig enab: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_INT_ENABWE),
		   sdhci_weadw(host, SDHCI_SIGNAW_ENABWE));
	SDHCI_DUMP("ACmd stat: 0x%08x | Swot int: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_AUTO_CMD_STATUS),
		   sdhci_weadw(host, SDHCI_SWOT_INT_STATUS));
	SDHCI_DUMP("Caps:      0x%08x | Caps_1:   0x%08x\n",
		   sdhci_weadw(host, SDHCI_CAPABIWITIES),
		   sdhci_weadw(host, SDHCI_CAPABIWITIES_1));
	SDHCI_DUMP("Cmd:       0x%08x | Max cuww: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_COMMAND),
		   sdhci_weadw(host, SDHCI_MAX_CUWWENT));
	SDHCI_DUMP("Wesp[0]:   0x%08x | Wesp[1]:  0x%08x\n",
		   sdhci_weadw(host, SDHCI_WESPONSE),
		   sdhci_weadw(host, SDHCI_WESPONSE + 4));
	SDHCI_DUMP("Wesp[2]:   0x%08x | Wesp[3]:  0x%08x\n",
		   sdhci_weadw(host, SDHCI_WESPONSE + 8),
		   sdhci_weadw(host, SDHCI_WESPONSE + 12));
	SDHCI_DUMP("Host ctw2: 0x%08x\n",
		   sdhci_weadw(host, SDHCI_HOST_CONTWOW2));

	if (host->fwags & SDHCI_USE_ADMA) {
		if (host->fwags & SDHCI_USE_64_BIT_DMA) {
			SDHCI_DUMP("ADMA Eww:  0x%08x | ADMA Ptw: 0x%08x%08x\n",
				   sdhci_weadw(host, SDHCI_ADMA_EWWOW),
				   sdhci_weadw(host, SDHCI_ADMA_ADDWESS_HI),
				   sdhci_weadw(host, SDHCI_ADMA_ADDWESS));
		} ewse {
			SDHCI_DUMP("ADMA Eww:  0x%08x | ADMA Ptw: 0x%08x\n",
				   sdhci_weadw(host, SDHCI_ADMA_EWWOW),
				   sdhci_weadw(host, SDHCI_ADMA_ADDWESS));
		}
	}

	if (host->ops->dump_vendow_wegs)
		host->ops->dump_vendow_wegs(host);

	SDHCI_DUMP("============================================\n");
}
EXPOWT_SYMBOW_GPW(sdhci_dumpwegs);

/*****************************************************************************\
 *                                                                           *
 * Wow wevew functions                                                       *
 *                                                                           *
\*****************************************************************************/

static void sdhci_do_enabwe_v4_mode(stwuct sdhci_host *host)
{
	u16 ctww2;

	ctww2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	if (ctww2 & SDHCI_CTWW_V4_MODE)
		wetuwn;

	ctww2 |= SDHCI_CTWW_V4_MODE;
	sdhci_wwitew(host, ctww2, SDHCI_HOST_CONTWOW2);
}

/*
 * This can be cawwed befowe sdhci_add_host() by Vendow's host contwowwew
 * dwivew to enabwe v4 mode if suppowted.
 */
void sdhci_enabwe_v4_mode(stwuct sdhci_host *host)
{
	host->v4_mode = twue;
	sdhci_do_enabwe_v4_mode(host);
}
EXPOWT_SYMBOW_GPW(sdhci_enabwe_v4_mode);

static inwine boow sdhci_data_wine_cmd(stwuct mmc_command *cmd)
{
	wetuwn cmd->data || cmd->fwags & MMC_WSP_BUSY;
}

static void sdhci_set_cawd_detection(stwuct sdhci_host *host, boow enabwe)
{
	u32 pwesent;

	if ((host->quiwks & SDHCI_QUIWK_BWOKEN_CAWD_DETECTION) ||
	    !mmc_cawd_is_wemovabwe(host->mmc) || mmc_can_gpio_cd(host->mmc))
		wetuwn;

	if (enabwe) {
		pwesent = sdhci_weadw(host, SDHCI_PWESENT_STATE) &
				      SDHCI_CAWD_PWESENT;

		host->iew |= pwesent ? SDHCI_INT_CAWD_WEMOVE :
				       SDHCI_INT_CAWD_INSEWT;
	} ewse {
		host->iew &= ~(SDHCI_INT_CAWD_WEMOVE | SDHCI_INT_CAWD_INSEWT);
	}

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}

static void sdhci_enabwe_cawd_detection(stwuct sdhci_host *host)
{
	sdhci_set_cawd_detection(host, twue);
}

static void sdhci_disabwe_cawd_detection(stwuct sdhci_host *host)
{
	sdhci_set_cawd_detection(host, fawse);
}

static void sdhci_wuntime_pm_bus_on(stwuct sdhci_host *host)
{
	if (host->bus_on)
		wetuwn;
	host->bus_on = twue;
	pm_wuntime_get_nowesume(mmc_dev(host->mmc));
}

static void sdhci_wuntime_pm_bus_off(stwuct sdhci_host *host)
{
	if (!host->bus_on)
		wetuwn;
	host->bus_on = fawse;
	pm_wuntime_put_noidwe(mmc_dev(host->mmc));
}

void sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	ktime_t timeout;

	sdhci_wwiteb(host, mask, SDHCI_SOFTWAWE_WESET);

	if (mask & SDHCI_WESET_AWW) {
		host->cwock = 0;
		/* Weset-aww tuwns off SD Bus Powew */
		if (host->quiwks2 & SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON)
			sdhci_wuntime_pm_bus_off(host);
	}

	/* Wait max 100 ms */
	timeout = ktime_add_ms(ktime_get(), 100);

	/* hw cweaws the bit when it's done */
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (!(sdhci_weadb(host, SDHCI_SOFTWAWE_WESET) & mask))
			bweak;
		if (timedout) {
			pw_eww("%s: Weset 0x%x nevew compweted.\n",
				mmc_hostname(host->mmc), (int)mask);
			sdhci_eww_stats_inc(host, CTWW_TIMEOUT);
			sdhci_dumpwegs(host);
			wetuwn;
		}
		udeway(10);
	}
}
EXPOWT_SYMBOW_GPW(sdhci_weset);

static boow sdhci_do_weset(stwuct sdhci_host *host, u8 mask)
{
	if (host->quiwks & SDHCI_QUIWK_NO_CAWD_NO_WESET) {
		stwuct mmc_host *mmc = host->mmc;

		if (!mmc->ops->get_cd(mmc))
			wetuwn fawse;
	}

	host->ops->weset(host, mask);

	wetuwn twue;
}

static void sdhci_weset_fow_aww(stwuct sdhci_host *host)
{
	if (sdhci_do_weset(host, SDHCI_WESET_AWW)) {
		if (host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
			if (host->ops->enabwe_dma)
				host->ops->enabwe_dma(host);
		}
		/* Wesetting the contwowwew cweaws many */
		host->pweset_enabwed = fawse;
	}
}

enum sdhci_weset_weason {
	SDHCI_WESET_FOW_INIT,
	SDHCI_WESET_FOW_WEQUEST_EWWOW,
	SDHCI_WESET_FOW_WEQUEST_EWWOW_DATA_ONWY,
	SDHCI_WESET_FOW_TUNING_ABOWT,
	SDHCI_WESET_FOW_CAWD_WEMOVED,
	SDHCI_WESET_FOW_CQE_WECOVEWY,
};

static void sdhci_weset_fow_weason(stwuct sdhci_host *host, enum sdhci_weset_weason weason)
{
	if (host->quiwks2 & SDHCI_QUIWK2_ISSUE_CMD_DAT_WESET_TOGETHEW) {
		sdhci_do_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
		wetuwn;
	}

	switch (weason) {
	case SDHCI_WESET_FOW_INIT:
		sdhci_do_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
		bweak;
	case SDHCI_WESET_FOW_WEQUEST_EWWOW:
	case SDHCI_WESET_FOW_TUNING_ABOWT:
	case SDHCI_WESET_FOW_CAWD_WEMOVED:
	case SDHCI_WESET_FOW_CQE_WECOVEWY:
		sdhci_do_weset(host, SDHCI_WESET_CMD);
		sdhci_do_weset(host, SDHCI_WESET_DATA);
		bweak;
	case SDHCI_WESET_FOW_WEQUEST_EWWOW_DATA_ONWY:
		sdhci_do_weset(host, SDHCI_WESET_DATA);
		bweak;
	}
}

#define sdhci_weset_fow(h, w) sdhci_weset_fow_weason((h), SDHCI_WESET_FOW_##w)

static void sdhci_set_defauwt_iwqs(stwuct sdhci_host *host)
{
	host->iew = SDHCI_INT_BUS_POWEW | SDHCI_INT_DATA_END_BIT |
		    SDHCI_INT_DATA_CWC | SDHCI_INT_DATA_TIMEOUT |
		    SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CWC |
		    SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END |
		    SDHCI_INT_WESPONSE;

	if (host->tuning_mode == SDHCI_TUNING_MODE_2 ||
	    host->tuning_mode == SDHCI_TUNING_MODE_3)
		host->iew |= SDHCI_INT_WETUNE;

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}

static void sdhci_config_dma(stwuct sdhci_host *host)
{
	u8 ctww;
	u16 ctww2;

	if (host->vewsion < SDHCI_SPEC_200)
		wetuwn;

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);

	/*
	 * Awways adjust the DMA sewection as some contwowwews
	 * (e.g. JMicwon) can't do PIO pwopewwy when the sewection
	 * is ADMA.
	 */
	ctww &= ~SDHCI_CTWW_DMA_MASK;
	if (!(host->fwags & SDHCI_WEQ_USE_DMA))
		goto out;

	/* Note if DMA Sewect is zewo then SDMA is sewected */
	if (host->fwags & SDHCI_USE_ADMA)
		ctww |= SDHCI_CTWW_ADMA32;

	if (host->fwags & SDHCI_USE_64_BIT_DMA) {
		/*
		 * If v4 mode, aww suppowted DMA can be 64-bit addwessing if
		 * contwowwew suppowts 64-bit system addwess, othewwise onwy
		 * ADMA can suppowt 64-bit addwessing.
		 */
		if (host->v4_mode) {
			ctww2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
			ctww2 |= SDHCI_CTWW_64BIT_ADDW;
			sdhci_wwitew(host, ctww2, SDHCI_HOST_CONTWOW2);
		} ewse if (host->fwags & SDHCI_USE_ADMA) {
			/*
			 * Don't need to undo SDHCI_CTWW_ADMA32 in owdew to
			 * set SDHCI_CTWW_ADMA64.
			 */
			ctww |= SDHCI_CTWW_ADMA64;
		}
	}

out:
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}

static void sdhci_init(stwuct sdhci_host *host, int soft)
{
	stwuct mmc_host *mmc = host->mmc;
	unsigned wong fwags;

	if (soft)
		sdhci_weset_fow(host, INIT);
	ewse
		sdhci_weset_fow_aww(host);

	if (host->v4_mode)
		sdhci_do_enabwe_v4_mode(host);

	spin_wock_iwqsave(&host->wock, fwags);
	sdhci_set_defauwt_iwqs(host);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	host->cqe_on = fawse;

	if (soft) {
		/* fowce cwock weconfiguwation */
		host->cwock = 0;
		host->weinit_uhs = twue;
		mmc->ops->set_ios(mmc, &mmc->ios);
	}
}

static void sdhci_weinit(stwuct sdhci_host *host)
{
	u32 cd = host->iew & (SDHCI_INT_CAWD_WEMOVE | SDHCI_INT_CAWD_INSEWT);

	sdhci_init(host, 0);
	sdhci_enabwe_cawd_detection(host);

	/*
	 * A change to the cawd detect bits indicates a change in pwesent state,
	 * wefew sdhci_set_cawd_detection(). A cawd detect intewwupt might have
	 * been missed whiwe the host contwowwew was being weset, so twiggew a
	 * wescan to check.
	 */
	if (cd != (host->iew & (SDHCI_INT_CAWD_WEMOVE | SDHCI_INT_CAWD_INSEWT)))
		mmc_detect_change(host->mmc, msecs_to_jiffies(200));
}

static void __sdhci_wed_activate(stwuct sdhci_host *host)
{
	u8 ctww;

	if (host->quiwks & SDHCI_QUIWK_NO_WED)
		wetuwn;

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);
	ctww |= SDHCI_CTWW_WED;
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}

static void __sdhci_wed_deactivate(stwuct sdhci_host *host)
{
	u8 ctww;

	if (host->quiwks & SDHCI_QUIWK_NO_WED)
		wetuwn;

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);
	ctww &= ~SDHCI_CTWW_WED;
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}

#if IS_WEACHABWE(CONFIG_WEDS_CWASS)
static void sdhci_wed_contwow(stwuct wed_cwassdev *wed,
			      enum wed_bwightness bwightness)
{
	stwuct sdhci_host *host = containew_of(wed, stwuct sdhci_host, wed);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->wuntime_suspended)
		goto out;

	if (bwightness == WED_OFF)
		__sdhci_wed_deactivate(host);
	ewse
		__sdhci_wed_activate(host);
out:
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static int sdhci_wed_wegistew(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc = host->mmc;

	if (host->quiwks & SDHCI_QUIWK_NO_WED)
		wetuwn 0;

	snpwintf(host->wed_name, sizeof(host->wed_name),
		 "%s::", mmc_hostname(mmc));

	host->wed.name = host->wed_name;
	host->wed.bwightness = WED_OFF;
	host->wed.defauwt_twiggew = mmc_hostname(mmc);
	host->wed.bwightness_set = sdhci_wed_contwow;

	wetuwn wed_cwassdev_wegistew(mmc_dev(mmc), &host->wed);
}

static void sdhci_wed_unwegistew(stwuct sdhci_host *host)
{
	if (host->quiwks & SDHCI_QUIWK_NO_WED)
		wetuwn;

	wed_cwassdev_unwegistew(&host->wed);
}

static inwine void sdhci_wed_activate(stwuct sdhci_host *host)
{
}

static inwine void sdhci_wed_deactivate(stwuct sdhci_host *host)
{
}

#ewse

static inwine int sdhci_wed_wegistew(stwuct sdhci_host *host)
{
	wetuwn 0;
}

static inwine void sdhci_wed_unwegistew(stwuct sdhci_host *host)
{
}

static inwine void sdhci_wed_activate(stwuct sdhci_host *host)
{
	__sdhci_wed_activate(host);
}

static inwine void sdhci_wed_deactivate(stwuct sdhci_host *host)
{
	__sdhci_wed_deactivate(host);
}

#endif

static void sdhci_mod_timew(stwuct sdhci_host *host, stwuct mmc_wequest *mwq,
			    unsigned wong timeout)
{
	if (sdhci_data_wine_cmd(mwq->cmd))
		mod_timew(&host->data_timew, timeout);
	ewse
		mod_timew(&host->timew, timeout);
}

static void sdhci_dew_timew(stwuct sdhci_host *host, stwuct mmc_wequest *mwq)
{
	if (sdhci_data_wine_cmd(mwq->cmd))
		dew_timew(&host->data_timew);
	ewse
		dew_timew(&host->timew);
}

static inwine boow sdhci_has_wequests(stwuct sdhci_host *host)
{
	wetuwn host->cmd || host->data_cmd;
}

/*****************************************************************************\
 *                                                                           *
 * Cowe functions                                                            *
 *                                                                           *
\*****************************************************************************/

static void sdhci_wead_bwock_pio(stwuct sdhci_host *host)
{
	size_t bwksize, wen, chunk;
	u32 scwatch;
	u8 *buf;

	DBG("PIO weading\n");

	bwksize = host->data->bwksz;
	chunk = 0;

	whiwe (bwksize) {
		BUG_ON(!sg_mitew_next(&host->sg_mitew));

		wen = min(host->sg_mitew.wength, bwksize);

		bwksize -= wen;
		host->sg_mitew.consumed = wen;

		buf = host->sg_mitew.addw;

		whiwe (wen) {
			if (chunk == 0) {
				scwatch = sdhci_weadw(host, SDHCI_BUFFEW);
				chunk = 4;
			}

			*buf = scwatch & 0xFF;

			buf++;
			scwatch >>= 8;
			chunk--;
			wen--;
		}
	}

	sg_mitew_stop(&host->sg_mitew);
}

static void sdhci_wwite_bwock_pio(stwuct sdhci_host *host)
{
	size_t bwksize, wen, chunk;
	u32 scwatch;
	u8 *buf;

	DBG("PIO wwiting\n");

	bwksize = host->data->bwksz;
	chunk = 0;
	scwatch = 0;

	whiwe (bwksize) {
		BUG_ON(!sg_mitew_next(&host->sg_mitew));

		wen = min(host->sg_mitew.wength, bwksize);

		bwksize -= wen;
		host->sg_mitew.consumed = wen;

		buf = host->sg_mitew.addw;

		whiwe (wen) {
			scwatch |= (u32)*buf << (chunk * 8);

			buf++;
			chunk++;
			wen--;

			if ((chunk == 4) || ((wen == 0) && (bwksize == 0))) {
				sdhci_wwitew(host, scwatch, SDHCI_BUFFEW);
				chunk = 0;
				scwatch = 0;
			}
		}
	}

	sg_mitew_stop(&host->sg_mitew);
}

static void sdhci_twansfew_pio(stwuct sdhci_host *host)
{
	u32 mask;

	if (host->bwocks == 0)
		wetuwn;

	if (host->data->fwags & MMC_DATA_WEAD)
		mask = SDHCI_DATA_AVAIWABWE;
	ewse
		mask = SDHCI_SPACE_AVAIWABWE;

	/*
	 * Some contwowwews (JMicwon JMB38x) mess up the buffew bits
	 * fow twansfews < 4 bytes. As wong as it is just one bwock,
	 * we can ignowe the bits.
	 */
	if ((host->quiwks & SDHCI_QUIWK_BWOKEN_SMAWW_PIO) &&
		(host->data->bwocks == 1))
		mask = ~0;

	whiwe (sdhci_weadw(host, SDHCI_PWESENT_STATE) & mask) {
		if (host->quiwks & SDHCI_QUIWK_PIO_NEEDS_DEWAY)
			udeway(100);

		if (host->data->fwags & MMC_DATA_WEAD)
			sdhci_wead_bwock_pio(host);
		ewse
			sdhci_wwite_bwock_pio(host);

		host->bwocks--;
		if (host->bwocks == 0)
			bweak;
	}

	DBG("PIO twansfew compwete.\n");
}

static int sdhci_pwe_dma_twansfew(stwuct sdhci_host *host,
				  stwuct mmc_data *data, int cookie)
{
	int sg_count;

	/*
	 * If the data buffews awe awweady mapped, wetuwn the pwevious
	 * dma_map_sg() wesuwt.
	 */
	if (data->host_cookie == COOKIE_PWE_MAPPED)
		wetuwn data->sg_count;

	/* Bounce wwite wequests to the bounce buffew */
	if (host->bounce_buffew) {
		unsigned int wength = data->bwksz * data->bwocks;

		if (wength > host->bounce_buffew_size) {
			pw_eww("%s: asked fow twansfew of %u bytes exceeds bounce buffew %u bytes\n",
			       mmc_hostname(host->mmc), wength,
			       host->bounce_buffew_size);
			wetuwn -EIO;
		}
		if (mmc_get_dma_diw(data) == DMA_TO_DEVICE) {
			/* Copy the data to the bounce buffew */
			if (host->ops->copy_to_bounce_buffew) {
				host->ops->copy_to_bounce_buffew(host,
								 data, wength);
			} ewse {
				sg_copy_to_buffew(data->sg, data->sg_wen,
						  host->bounce_buffew, wength);
			}
		}
		/* Switch ownewship to the DMA */
		dma_sync_singwe_fow_device(mmc_dev(host->mmc),
					   host->bounce_addw,
					   host->bounce_buffew_size,
					   mmc_get_dma_diw(data));
		/* Just a dummy vawue */
		sg_count = 1;
	} ewse {
		/* Just access the data diwectwy fwom memowy */
		sg_count = dma_map_sg(mmc_dev(host->mmc),
				      data->sg, data->sg_wen,
				      mmc_get_dma_diw(data));
	}

	if (sg_count == 0)
		wetuwn -ENOSPC;

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	wetuwn sg_count;
}

static chaw *sdhci_kmap_atomic(stwuct scattewwist *sg)
{
	wetuwn kmap_wocaw_page(sg_page(sg)) + sg->offset;
}

static void sdhci_kunmap_atomic(void *buffew)
{
	kunmap_wocaw(buffew);
}

void sdhci_adma_wwite_desc(stwuct sdhci_host *host, void **desc,
			   dma_addw_t addw, int wen, unsigned int cmd)
{
	stwuct sdhci_adma2_64_desc *dma_desc = *desc;

	/* 32-bit and 64-bit descwiptows have these membews in same position */
	dma_desc->cmd = cpu_to_we16(cmd);
	dma_desc->wen = cpu_to_we16(wen);
	dma_desc->addw_wo = cpu_to_we32(wowew_32_bits(addw));

	if (host->fwags & SDHCI_USE_64_BIT_DMA)
		dma_desc->addw_hi = cpu_to_we32(uppew_32_bits(addw));

	*desc += host->desc_sz;
}
EXPOWT_SYMBOW_GPW(sdhci_adma_wwite_desc);

static inwine void __sdhci_adma_wwite_desc(stwuct sdhci_host *host,
					   void **desc, dma_addw_t addw,
					   int wen, unsigned int cmd)
{
	if (host->ops->adma_wwite_desc)
		host->ops->adma_wwite_desc(host, desc, addw, wen, cmd);
	ewse
		sdhci_adma_wwite_desc(host, desc, addw, wen, cmd);
}

static void sdhci_adma_mawk_end(void *desc)
{
	stwuct sdhci_adma2_64_desc *dma_desc = desc;

	/* 32-bit and 64-bit descwiptows have 'cmd' in same position */
	dma_desc->cmd |= cpu_to_we16(ADMA2_END);
}

static void sdhci_adma_tabwe_pwe(stwuct sdhci_host *host,
	stwuct mmc_data *data, int sg_count)
{
	stwuct scattewwist *sg;
	dma_addw_t addw, awign_addw;
	void *desc, *awign;
	chaw *buffew;
	int wen, offset, i;

	/*
	 * The spec does not specify endianness of descwiptow tabwe.
	 * We cuwwentwy guess that it is WE.
	 */

	host->sg_count = sg_count;

	desc = host->adma_tabwe;
	awign = host->awign_buffew;

	awign_addw = host->awign_addw;

	fow_each_sg(data->sg, sg, host->sg_count, i) {
		addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		/*
		 * The SDHCI specification states that ADMA addwesses must
		 * be 32-bit awigned. If they awen't, then we use a bounce
		 * buffew fow the (up to thwee) bytes that scwew up the
		 * awignment.
		 */
		offset = (SDHCI_ADMA2_AWIGN - (addw & SDHCI_ADMA2_MASK)) &
			 SDHCI_ADMA2_MASK;
		if (offset) {
			if (data->fwags & MMC_DATA_WWITE) {
				buffew = sdhci_kmap_atomic(sg);
				memcpy(awign, buffew, offset);
				sdhci_kunmap_atomic(buffew);
			}

			/* twan, vawid */
			__sdhci_adma_wwite_desc(host, &desc, awign_addw,
						offset, ADMA2_TWAN_VAWID);

			BUG_ON(offset > 65536);

			awign += SDHCI_ADMA2_AWIGN;
			awign_addw += SDHCI_ADMA2_AWIGN;

			addw += offset;
			wen -= offset;
		}

		/*
		 * The bwock wayew fowces a minimum segment size of PAGE_SIZE,
		 * so 'wen' can be too big hewe if PAGE_SIZE >= 64KiB. Wwite
		 * muwtipwe descwiptows, noting that the ADMA tabwe is sized
		 * fow 4KiB chunks anyway, so it wiww be big enough.
		 */
		whiwe (wen > host->max_adma) {
			int n = 32 * 1024; /* 32KiB*/

			__sdhci_adma_wwite_desc(host, &desc, addw, n, ADMA2_TWAN_VAWID);
			addw += n;
			wen -= n;
		}

		/* twan, vawid */
		if (wen)
			__sdhci_adma_wwite_desc(host, &desc, addw, wen,
						ADMA2_TWAN_VAWID);

		/*
		 * If this twiggews then we have a cawcuwation bug
		 * somewhewe. :/
		 */
		WAWN_ON((desc - host->adma_tabwe) >= host->adma_tabwe_sz);
	}

	if (host->quiwks & SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC) {
		/* Mawk the wast descwiptow as the tewminating descwiptow */
		if (desc != host->adma_tabwe) {
			desc -= host->desc_sz;
			sdhci_adma_mawk_end(desc);
		}
	} ewse {
		/* Add a tewminating entwy - nop, end, vawid */
		__sdhci_adma_wwite_desc(host, &desc, 0, 0, ADMA2_NOP_END_VAWID);
	}
}

static void sdhci_adma_tabwe_post(stwuct sdhci_host *host,
	stwuct mmc_data *data)
{
	stwuct scattewwist *sg;
	int i, size;
	void *awign;
	chaw *buffew;

	if (data->fwags & MMC_DATA_WEAD) {
		boow has_unawigned = fawse;

		/* Do a quick scan of the SG wist fow any unawigned mappings */
		fow_each_sg(data->sg, sg, host->sg_count, i)
			if (sg_dma_addwess(sg) & SDHCI_ADMA2_MASK) {
				has_unawigned = twue;
				bweak;
			}

		if (has_unawigned) {
			dma_sync_sg_fow_cpu(mmc_dev(host->mmc), data->sg,
					    data->sg_wen, DMA_FWOM_DEVICE);

			awign = host->awign_buffew;

			fow_each_sg(data->sg, sg, host->sg_count, i) {
				if (sg_dma_addwess(sg) & SDHCI_ADMA2_MASK) {
					size = SDHCI_ADMA2_AWIGN -
					       (sg_dma_addwess(sg) & SDHCI_ADMA2_MASK);

					buffew = sdhci_kmap_atomic(sg);
					memcpy(buffew, awign, size);
					sdhci_kunmap_atomic(buffew);

					awign += SDHCI_ADMA2_AWIGN;
				}
			}
		}
	}
}

static void sdhci_set_adma_addw(stwuct sdhci_host *host, dma_addw_t addw)
{
	sdhci_wwitew(host, wowew_32_bits(addw), SDHCI_ADMA_ADDWESS);
	if (host->fwags & SDHCI_USE_64_BIT_DMA)
		sdhci_wwitew(host, uppew_32_bits(addw), SDHCI_ADMA_ADDWESS_HI);
}

static dma_addw_t sdhci_sdma_addwess(stwuct sdhci_host *host)
{
	if (host->bounce_buffew)
		wetuwn host->bounce_addw;
	ewse
		wetuwn sg_dma_addwess(host->data->sg);
}

static void sdhci_set_sdma_addw(stwuct sdhci_host *host, dma_addw_t addw)
{
	if (host->v4_mode)
		sdhci_set_adma_addw(host, addw);
	ewse
		sdhci_wwitew(host, addw, SDHCI_DMA_ADDWESS);
}

static unsigned int sdhci_tawget_timeout(stwuct sdhci_host *host,
					 stwuct mmc_command *cmd,
					 stwuct mmc_data *data)
{
	unsigned int tawget_timeout;

	/* timeout in us */
	if (!data) {
		tawget_timeout = cmd->busy_timeout * 1000;
	} ewse {
		tawget_timeout = DIV_WOUND_UP(data->timeout_ns, 1000);
		if (host->cwock && data->timeout_cwks) {
			unsigned wong wong vaw;

			/*
			 * data->timeout_cwks is in units of cwock cycwes.
			 * host->cwock is in Hz.  tawget_timeout is in us.
			 * Hence, us = 1000000 * cycwes / Hz.  Wound up.
			 */
			vaw = 1000000UWW * data->timeout_cwks;
			if (do_div(vaw, host->cwock))
				tawget_timeout++;
			tawget_timeout += vaw;
		}
	}

	wetuwn tawget_timeout;
}

static void sdhci_cawc_sw_timeout(stwuct sdhci_host *host,
				  stwuct mmc_command *cmd)
{
	stwuct mmc_data *data = cmd->data;
	stwuct mmc_host *mmc = host->mmc;
	stwuct mmc_ios *ios = &mmc->ios;
	unsigned chaw bus_width = 1 << ios->bus_width;
	unsigned int bwksz;
	unsigned int fweq;
	u64 tawget_timeout;
	u64 twansfew_time;

	tawget_timeout = sdhci_tawget_timeout(host, cmd, data);
	tawget_timeout *= NSEC_PEW_USEC;

	if (data) {
		bwksz = data->bwksz;
		fweq = mmc->actuaw_cwock ? : host->cwock;
		twansfew_time = (u64)bwksz * NSEC_PEW_SEC * (8 / bus_width);
		do_div(twansfew_time, fweq);
		/* muwtipwy by '2' to account fow any unknowns */
		twansfew_time = twansfew_time * 2;
		/* cawcuwate timeout fow the entiwe data */
		host->data_timeout = data->bwocks * tawget_timeout +
				     twansfew_time;
	} ewse {
		host->data_timeout = tawget_timeout;
	}

	if (host->data_timeout)
		host->data_timeout += MMC_CMD_TWANSFEW_TIME;
}

static u8 sdhci_cawc_timeout(stwuct sdhci_host *host, stwuct mmc_command *cmd,
			     boow *too_big)
{
	u8 count;
	stwuct mmc_data *data;
	unsigned tawget_timeout, cuwwent_timeout;

	*too_big = fawse;

	/*
	 * If the host contwowwew pwovides us with an incowwect timeout
	 * vawue, just skip the check and use the maximum. The hawdwawe may take
	 * wongew to time out, but that's much bettew than having a too-showt
	 * timeout vawue.
	 */
	if (host->quiwks & SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW)
		wetuwn host->max_timeout_count;

	/* Unspecified command, assume max */
	if (cmd == NUWW)
		wetuwn host->max_timeout_count;

	data = cmd->data;
	/* Unspecified timeout, assume max */
	if (!data && !cmd->busy_timeout)
		wetuwn host->max_timeout_count;

	/* timeout in us */
	tawget_timeout = sdhci_tawget_timeout(host, cmd, data);

	/*
	 * Figuwe out needed cycwes.
	 * We do this in steps in owdew to fit inside a 32 bit int.
	 * The fiwst step is the minimum timeout, which wiww have a
	 * minimum wesowution of 6 bits:
	 * (1) 2^13*1000 > 2^22,
	 * (2) host->timeout_cwk < 2^16
	 *     =>
	 *     (1) / (2) > 2^6
	 */
	count = 0;
	cuwwent_timeout = (1 << 13) * 1000 / host->timeout_cwk;
	whiwe (cuwwent_timeout < tawget_timeout) {
		count++;
		cuwwent_timeout <<= 1;
		if (count > host->max_timeout_count) {
			if (!(host->quiwks2 & SDHCI_QUIWK2_DISABWE_HW_TIMEOUT))
				DBG("Too wawge timeout 0x%x wequested fow CMD%d!\n",
				    count, cmd->opcode);
			count = host->max_timeout_count;
			*too_big = twue;
			bweak;
		}
	}

	wetuwn count;
}

static void sdhci_set_twansfew_iwqs(stwuct sdhci_host *host)
{
	u32 pio_iwqs = SDHCI_INT_DATA_AVAIW | SDHCI_INT_SPACE_AVAIW;
	u32 dma_iwqs = SDHCI_INT_DMA_END | SDHCI_INT_ADMA_EWWOW;

	if (host->fwags & SDHCI_WEQ_USE_DMA)
		host->iew = (host->iew & ~pio_iwqs) | dma_iwqs;
	ewse
		host->iew = (host->iew & ~dma_iwqs) | pio_iwqs;

	if (host->fwags & (SDHCI_AUTO_CMD23 | SDHCI_AUTO_CMD12))
		host->iew |= SDHCI_INT_AUTO_CMD_EWW;
	ewse
		host->iew &= ~SDHCI_INT_AUTO_CMD_EWW;

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}

void sdhci_set_data_timeout_iwq(stwuct sdhci_host *host, boow enabwe)
{
	if (enabwe)
		host->iew |= SDHCI_INT_DATA_TIMEOUT;
	ewse
		host->iew &= ~SDHCI_INT_DATA_TIMEOUT;
	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}
EXPOWT_SYMBOW_GPW(sdhci_set_data_timeout_iwq);

void __sdhci_set_timeout(stwuct sdhci_host *host, stwuct mmc_command *cmd)
{
	boow too_big = fawse;
	u8 count = sdhci_cawc_timeout(host, cmd, &too_big);

	if (too_big &&
	    host->quiwks2 & SDHCI_QUIWK2_DISABWE_HW_TIMEOUT) {
		sdhci_cawc_sw_timeout(host, cmd);
		sdhci_set_data_timeout_iwq(host, fawse);
	} ewse if (!(host->iew & SDHCI_INT_DATA_TIMEOUT)) {
		sdhci_set_data_timeout_iwq(host, twue);
	}

	sdhci_wwiteb(host, count, SDHCI_TIMEOUT_CONTWOW);
}
EXPOWT_SYMBOW_GPW(__sdhci_set_timeout);

static void sdhci_set_timeout(stwuct sdhci_host *host, stwuct mmc_command *cmd)
{
	if (host->ops->set_timeout)
		host->ops->set_timeout(host, cmd);
	ewse
		__sdhci_set_timeout(host, cmd);
}

static void sdhci_initiawize_data(stwuct sdhci_host *host,
				  stwuct mmc_data *data)
{
	WAWN_ON(host->data);

	/* Sanity checks */
	BUG_ON(data->bwksz * data->bwocks > 524288);
	BUG_ON(data->bwksz > host->mmc->max_bwk_size);
	BUG_ON(data->bwocks > 65535);

	host->data = data;
	host->data_eawwy = 0;
	host->data->bytes_xfewed = 0;
}

static inwine void sdhci_set_bwock_info(stwuct sdhci_host *host,
					stwuct mmc_data *data)
{
	/* Set the DMA boundawy vawue and bwock size */
	sdhci_wwitew(host,
		     SDHCI_MAKE_BWKSZ(host->sdma_boundawy, data->bwksz),
		     SDHCI_BWOCK_SIZE);
	/*
	 * Fow Vewsion 4.10 onwawds, if v4 mode is enabwed, 32-bit Bwock Count
	 * can be suppowted, in that case 16-bit bwock count wegistew must be 0.
	 */
	if (host->vewsion >= SDHCI_SPEC_410 && host->v4_mode &&
	    (host->quiwks2 & SDHCI_QUIWK2_USE_32BIT_BWK_CNT)) {
		if (sdhci_weadw(host, SDHCI_BWOCK_COUNT))
			sdhci_wwitew(host, 0, SDHCI_BWOCK_COUNT);
		sdhci_wwitew(host, data->bwocks, SDHCI_32BIT_BWK_CNT);
	} ewse {
		sdhci_wwitew(host, data->bwocks, SDHCI_BWOCK_COUNT);
	}
}

static void sdhci_pwepawe_data(stwuct sdhci_host *host, stwuct mmc_command *cmd)
{
	stwuct mmc_data *data = cmd->data;

	sdhci_initiawize_data(host, data);

	if (host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		stwuct scattewwist *sg;
		unsigned int wength_mask, offset_mask;
		int i;

		host->fwags |= SDHCI_WEQ_USE_DMA;

		/*
		 * FIXME: This doesn't account fow mewging when mapping the
		 * scattewwist.
		 *
		 * The assumption hewe being that awignment and wengths awe
		 * the same aftew DMA mapping to device addwess space.
		 */
		wength_mask = 0;
		offset_mask = 0;
		if (host->fwags & SDHCI_USE_ADMA) {
			if (host->quiwks & SDHCI_QUIWK_32BIT_ADMA_SIZE) {
				wength_mask = 3;
				/*
				 * As we use up to 3 byte chunks to wowk
				 * awound awignment pwobwems, we need to
				 * check the offset as weww.
				 */
				offset_mask = 3;
			}
		} ewse {
			if (host->quiwks & SDHCI_QUIWK_32BIT_DMA_SIZE)
				wength_mask = 3;
			if (host->quiwks & SDHCI_QUIWK_32BIT_DMA_ADDW)
				offset_mask = 3;
		}

		if (unwikewy(wength_mask | offset_mask)) {
			fow_each_sg(data->sg, sg, data->sg_wen, i) {
				if (sg->wength & wength_mask) {
					DBG("Wevewting to PIO because of twansfew size (%d)\n",
					    sg->wength);
					host->fwags &= ~SDHCI_WEQ_USE_DMA;
					bweak;
				}
				if (sg->offset & offset_mask) {
					DBG("Wevewting to PIO because of bad awignment\n");
					host->fwags &= ~SDHCI_WEQ_USE_DMA;
					bweak;
				}
			}
		}
	}

	sdhci_config_dma(host);

	if (host->fwags & SDHCI_WEQ_USE_DMA) {
		int sg_cnt = sdhci_pwe_dma_twansfew(host, data, COOKIE_MAPPED);

		if (sg_cnt <= 0) {
			/*
			 * This onwy happens when someone fed
			 * us an invawid wequest.
			 */
			WAWN_ON(1);
			host->fwags &= ~SDHCI_WEQ_USE_DMA;
		} ewse if (host->fwags & SDHCI_USE_ADMA) {
			sdhci_adma_tabwe_pwe(host, data, sg_cnt);
			sdhci_set_adma_addw(host, host->adma_addw);
		} ewse {
			WAWN_ON(sg_cnt != 1);
			sdhci_set_sdma_addw(host, sdhci_sdma_addwess(host));
		}
	}

	if (!(host->fwags & SDHCI_WEQ_USE_DMA)) {
		int fwags;

		fwags = SG_MITEW_ATOMIC;
		if (host->data->fwags & MMC_DATA_WEAD)
			fwags |= SG_MITEW_TO_SG;
		ewse
			fwags |= SG_MITEW_FWOM_SG;
		sg_mitew_stawt(&host->sg_mitew, data->sg, data->sg_wen, fwags);
		host->bwocks = data->bwocks;
	}

	sdhci_set_twansfew_iwqs(host);

	sdhci_set_bwock_info(host, data);
}

#if IS_ENABWED(CONFIG_MMC_SDHCI_EXTEWNAW_DMA)

static int sdhci_extewnaw_dma_init(stwuct sdhci_host *host)
{
	int wet = 0;
	stwuct mmc_host *mmc = host->mmc;

	host->tx_chan = dma_wequest_chan(mmc_dev(mmc), "tx");
	if (IS_EWW(host->tx_chan)) {
		wet = PTW_EWW(host->tx_chan);
		if (wet != -EPWOBE_DEFEW)
			pw_wawn("Faiwed to wequest TX DMA channew.\n");
		host->tx_chan = NUWW;
		wetuwn wet;
	}

	host->wx_chan = dma_wequest_chan(mmc_dev(mmc), "wx");
	if (IS_EWW(host->wx_chan)) {
		if (host->tx_chan) {
			dma_wewease_channew(host->tx_chan);
			host->tx_chan = NUWW;
		}

		wet = PTW_EWW(host->wx_chan);
		if (wet != -EPWOBE_DEFEW)
			pw_wawn("Faiwed to wequest WX DMA channew.\n");
		host->wx_chan = NUWW;
	}

	wetuwn wet;
}

static stwuct dma_chan *sdhci_extewnaw_dma_channew(stwuct sdhci_host *host,
						   stwuct mmc_data *data)
{
	wetuwn data->fwags & MMC_DATA_WWITE ? host->tx_chan : host->wx_chan;
}

static int sdhci_extewnaw_dma_setup(stwuct sdhci_host *host,
				    stwuct mmc_command *cmd)
{
	int wet, i;
	enum dma_twansfew_diwection diw;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct mmc_data *data = cmd->data;
	stwuct dma_chan *chan;
	stwuct dma_swave_config cfg;
	dma_cookie_t cookie;
	int sg_cnt;

	if (!host->mapbase)
		wetuwn -EINVAW;

	memset(&cfg, 0, sizeof(cfg));
	cfg.swc_addw = host->mapbase + SDHCI_BUFFEW;
	cfg.dst_addw = host->mapbase + SDHCI_BUFFEW;
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.swc_maxbuwst = data->bwksz / 4;
	cfg.dst_maxbuwst = data->bwksz / 4;

	/* Sanity check: aww the SG entwies must be awigned by bwock size. */
	fow (i = 0; i < data->sg_wen; i++) {
		if ((data->sg + i)->wength % data->bwksz)
			wetuwn -EINVAW;
	}

	chan = sdhci_extewnaw_dma_channew(host, data);

	wet = dmaengine_swave_config(chan, &cfg);
	if (wet)
		wetuwn wet;

	sg_cnt = sdhci_pwe_dma_twansfew(host, data, COOKIE_MAPPED);
	if (sg_cnt <= 0)
		wetuwn -EINVAW;

	diw = data->fwags & MMC_DATA_WWITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	desc = dmaengine_pwep_swave_sg(chan, data->sg, data->sg_wen, diw,
				       DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc)
		wetuwn -EINVAW;

	desc->cawwback = NUWW;
	desc->cawwback_pawam = NUWW;

	cookie = dmaengine_submit(desc);
	if (dma_submit_ewwow(cookie))
		wet = cookie;

	wetuwn wet;
}

static void sdhci_extewnaw_dma_wewease(stwuct sdhci_host *host)
{
	if (host->tx_chan) {
		dma_wewease_channew(host->tx_chan);
		host->tx_chan = NUWW;
	}

	if (host->wx_chan) {
		dma_wewease_channew(host->wx_chan);
		host->wx_chan = NUWW;
	}

	sdhci_switch_extewnaw_dma(host, fawse);
}

static void __sdhci_extewnaw_dma_pwepawe_data(stwuct sdhci_host *host,
					      stwuct mmc_command *cmd)
{
	stwuct mmc_data *data = cmd->data;

	sdhci_initiawize_data(host, data);

	host->fwags |= SDHCI_WEQ_USE_DMA;
	sdhci_set_twansfew_iwqs(host);

	sdhci_set_bwock_info(host, data);
}

static void sdhci_extewnaw_dma_pwepawe_data(stwuct sdhci_host *host,
					    stwuct mmc_command *cmd)
{
	if (!sdhci_extewnaw_dma_setup(host, cmd)) {
		__sdhci_extewnaw_dma_pwepawe_data(host, cmd);
	} ewse {
		sdhci_extewnaw_dma_wewease(host);
		pw_eww("%s: Cannot use extewnaw DMA, switch to the DMA/PIO which standawd SDHCI pwovides.\n",
		       mmc_hostname(host->mmc));
		sdhci_pwepawe_data(host, cmd);
	}
}

static void sdhci_extewnaw_dma_pwe_twansfew(stwuct sdhci_host *host,
					    stwuct mmc_command *cmd)
{
	stwuct dma_chan *chan;

	if (!cmd->data)
		wetuwn;

	chan = sdhci_extewnaw_dma_channew(host, cmd->data);
	if (chan)
		dma_async_issue_pending(chan);
}

#ewse

static inwine int sdhci_extewnaw_dma_init(stwuct sdhci_host *host)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void sdhci_extewnaw_dma_wewease(stwuct sdhci_host *host)
{
}

static inwine void sdhci_extewnaw_dma_pwepawe_data(stwuct sdhci_host *host,
						   stwuct mmc_command *cmd)
{
	/* This shouwd nevew happen */
	WAWN_ON_ONCE(1);
}

static inwine void sdhci_extewnaw_dma_pwe_twansfew(stwuct sdhci_host *host,
						   stwuct mmc_command *cmd)
{
}

static inwine stwuct dma_chan *sdhci_extewnaw_dma_channew(stwuct sdhci_host *host,
							  stwuct mmc_data *data)
{
	wetuwn NUWW;
}

#endif

void sdhci_switch_extewnaw_dma(stwuct sdhci_host *host, boow en)
{
	host->use_extewnaw_dma = en;
}
EXPOWT_SYMBOW_GPW(sdhci_switch_extewnaw_dma);

static inwine boow sdhci_auto_cmd12(stwuct sdhci_host *host,
				    stwuct mmc_wequest *mwq)
{
	wetuwn !mwq->sbc && (host->fwags & SDHCI_AUTO_CMD12) &&
	       !mwq->cap_cmd_duwing_tfw;
}

static inwine boow sdhci_auto_cmd23(stwuct sdhci_host *host,
				    stwuct mmc_wequest *mwq)
{
	wetuwn mwq->sbc && (host->fwags & SDHCI_AUTO_CMD23);
}

static inwine boow sdhci_manuaw_cmd23(stwuct sdhci_host *host,
				      stwuct mmc_wequest *mwq)
{
	wetuwn mwq->sbc && !(host->fwags & SDHCI_AUTO_CMD23);
}

static inwine void sdhci_auto_cmd_sewect(stwuct sdhci_host *host,
					 stwuct mmc_command *cmd,
					 u16 *mode)
{
	boow use_cmd12 = sdhci_auto_cmd12(host, cmd->mwq) &&
			 (cmd->opcode != SD_IO_WW_EXTENDED);
	boow use_cmd23 = sdhci_auto_cmd23(host, cmd->mwq);
	u16 ctww2;

	/*
	 * In case of Vewsion 4.10 ow watew, use of 'Auto CMD Auto
	 * Sewect' is wecommended wathew than use of 'Auto CMD12
	 * Enabwe' ow 'Auto CMD23 Enabwe'. We wequiwe Vewsion 4 Mode
	 * hewe because some contwowwews (e.g sdhci-of-dwmshc) expect it.
	 */
	if (host->vewsion >= SDHCI_SPEC_410 && host->v4_mode &&
	    (use_cmd12 || use_cmd23)) {
		*mode |= SDHCI_TWNS_AUTO_SEW;

		ctww2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		if (use_cmd23)
			ctww2 |= SDHCI_CMD23_ENABWE;
		ewse
			ctww2 &= ~SDHCI_CMD23_ENABWE;
		sdhci_wwitew(host, ctww2, SDHCI_HOST_CONTWOW2);

		wetuwn;
	}

	/*
	 * If we awe sending CMD23, CMD12 nevew gets sent
	 * on successfuw compwetion (so no Auto-CMD12).
	 */
	if (use_cmd12)
		*mode |= SDHCI_TWNS_AUTO_CMD12;
	ewse if (use_cmd23)
		*mode |= SDHCI_TWNS_AUTO_CMD23;
}

static void sdhci_set_twansfew_mode(stwuct sdhci_host *host,
	stwuct mmc_command *cmd)
{
	u16 mode = 0;
	stwuct mmc_data *data = cmd->data;

	if (data == NUWW) {
		if (host->quiwks2 &
			SDHCI_QUIWK2_CWEAW_TWANSFEWMODE_WEG_BEFOWE_CMD) {
			/* must not cweaw SDHCI_TWANSFEW_MODE when tuning */
			if (!mmc_op_tuning(cmd->opcode))
				sdhci_wwitew(host, 0x0, SDHCI_TWANSFEW_MODE);
		} ewse {
		/* cweaw Auto CMD settings fow no data CMDs */
			mode = sdhci_weadw(host, SDHCI_TWANSFEW_MODE);
			sdhci_wwitew(host, mode & ~(SDHCI_TWNS_AUTO_CMD12 |
				SDHCI_TWNS_AUTO_CMD23), SDHCI_TWANSFEW_MODE);
		}
		wetuwn;
	}

	WAWN_ON(!host->data);

	if (!(host->quiwks2 & SDHCI_QUIWK2_SUPPOWT_SINGWE))
		mode = SDHCI_TWNS_BWK_CNT_EN;

	if (mmc_op_muwti(cmd->opcode) || data->bwocks > 1) {
		mode = SDHCI_TWNS_BWK_CNT_EN | SDHCI_TWNS_MUWTI;
		sdhci_auto_cmd_sewect(host, cmd, &mode);
		if (sdhci_auto_cmd23(host, cmd->mwq))
			sdhci_wwitew(host, cmd->mwq->sbc->awg, SDHCI_AWGUMENT2);
	}

	if (data->fwags & MMC_DATA_WEAD)
		mode |= SDHCI_TWNS_WEAD;
	if (host->fwags & SDHCI_WEQ_USE_DMA)
		mode |= SDHCI_TWNS_DMA;

	sdhci_wwitew(host, mode, SDHCI_TWANSFEW_MODE);
}

static boow sdhci_needs_weset(stwuct sdhci_host *host, stwuct mmc_wequest *mwq)
{
	wetuwn (!(host->fwags & SDHCI_DEVICE_DEAD) &&
		((mwq->cmd && mwq->cmd->ewwow) ||
		 (mwq->sbc && mwq->sbc->ewwow) ||
		 (mwq->data && mwq->data->stop && mwq->data->stop->ewwow) ||
		 (host->quiwks & SDHCI_QUIWK_WESET_AFTEW_WEQUEST)));
}

static void sdhci_set_mwq_done(stwuct sdhci_host *host, stwuct mmc_wequest *mwq)
{
	int i;

	fow (i = 0; i < SDHCI_MAX_MWQS; i++) {
		if (host->mwqs_done[i] == mwq) {
			WAWN_ON(1);
			wetuwn;
		}
	}

	fow (i = 0; i < SDHCI_MAX_MWQS; i++) {
		if (!host->mwqs_done[i]) {
			host->mwqs_done[i] = mwq;
			bweak;
		}
	}

	WAWN_ON(i >= SDHCI_MAX_MWQS);
}

static void __sdhci_finish_mwq(stwuct sdhci_host *host, stwuct mmc_wequest *mwq)
{
	if (host->cmd && host->cmd->mwq == mwq)
		host->cmd = NUWW;

	if (host->data_cmd && host->data_cmd->mwq == mwq)
		host->data_cmd = NUWW;

	if (host->defewwed_cmd && host->defewwed_cmd->mwq == mwq)
		host->defewwed_cmd = NUWW;

	if (host->data && host->data->mwq == mwq)
		host->data = NUWW;

	if (sdhci_needs_weset(host, mwq))
		host->pending_weset = twue;

	sdhci_set_mwq_done(host, mwq);

	sdhci_dew_timew(host, mwq);

	if (!sdhci_has_wequests(host))
		sdhci_wed_deactivate(host);
}

static void sdhci_finish_mwq(stwuct sdhci_host *host, stwuct mmc_wequest *mwq)
{
	__sdhci_finish_mwq(host, mwq);

	queue_wowk(host->compwete_wq, &host->compwete_wowk);
}

static void __sdhci_finish_data(stwuct sdhci_host *host, boow sw_data_timeout)
{
	stwuct mmc_command *data_cmd = host->data_cmd;
	stwuct mmc_data *data = host->data;

	host->data = NUWW;
	host->data_cmd = NUWW;

	/*
	 * The contwowwew needs a weset of intewnaw state machines upon ewwow
	 * conditions.
	 */
	if (data->ewwow) {
		if (!host->cmd || host->cmd == data_cmd)
			sdhci_weset_fow(host, WEQUEST_EWWOW);
		ewse
			sdhci_weset_fow(host, WEQUEST_EWWOW_DATA_ONWY);
	}

	if ((host->fwags & (SDHCI_WEQ_USE_DMA | SDHCI_USE_ADMA)) ==
	    (SDHCI_WEQ_USE_DMA | SDHCI_USE_ADMA))
		sdhci_adma_tabwe_post(host, data);

	/*
	 * The specification states that the bwock count wegistew must
	 * be updated, but it does not specify at what point in the
	 * data fwow. That makes the wegistew entiwewy usewess to wead
	 * back so we have to assume that nothing made it to the cawd
	 * in the event of an ewwow.
	 */
	if (data->ewwow)
		data->bytes_xfewed = 0;
	ewse
		data->bytes_xfewed = data->bwksz * data->bwocks;

	/*
	 * Need to send CMD12 if -
	 * a) open-ended muwtibwock twansfew not using auto CMD12 (no CMD23)
	 * b) ewwow in muwtibwock twansfew
	 */
	if (data->stop &&
	    ((!data->mwq->sbc && !sdhci_auto_cmd12(host, data->mwq)) ||
	     data->ewwow)) {
		/*
		 * 'cap_cmd_duwing_tfw' wequest must not use the command wine
		 * aftew mmc_command_done() has been cawwed. It is uppew wayew's
		 * wesponsibiwity to send the stop command if wequiwed.
		 */
		if (data->mwq->cap_cmd_duwing_tfw) {
			__sdhci_finish_mwq(host, data->mwq);
		} ewse {
			/* Avoid twiggewing wawning in sdhci_send_command() */
			host->cmd = NUWW;
			if (!sdhci_send_command(host, data->stop)) {
				if (sw_data_timeout) {
					/*
					 * This is anyway a sw data timeout, so
					 * give up now.
					 */
					data->stop->ewwow = -EIO;
					__sdhci_finish_mwq(host, data->mwq);
				} ewse {
					WAWN_ON(host->defewwed_cmd);
					host->defewwed_cmd = data->stop;
				}
			}
		}
	} ewse {
		__sdhci_finish_mwq(host, data->mwq);
	}
}

static void sdhci_finish_data(stwuct sdhci_host *host)
{
	__sdhci_finish_data(host, fawse);
}

static boow sdhci_send_command(stwuct sdhci_host *host, stwuct mmc_command *cmd)
{
	int fwags;
	u32 mask;
	unsigned wong timeout;

	WAWN_ON(host->cmd);

	/* Initiawwy, a command has no ewwow */
	cmd->ewwow = 0;

	if ((host->quiwks2 & SDHCI_QUIWK2_STOP_WITH_TC) &&
	    cmd->opcode == MMC_STOP_TWANSMISSION)
		cmd->fwags |= MMC_WSP_BUSY;

	mask = SDHCI_CMD_INHIBIT;
	if (sdhci_data_wine_cmd(cmd))
		mask |= SDHCI_DATA_INHIBIT;

	/* We shouwdn't wait fow data inihibit fow stop commands, even
	   though they might use busy signawing */
	if (cmd->mwq->data && (cmd == cmd->mwq->data->stop))
		mask &= ~SDHCI_DATA_INHIBIT;

	if (sdhci_weadw(host, SDHCI_PWESENT_STATE) & mask)
		wetuwn fawse;

	host->cmd = cmd;
	host->data_timeout = 0;
	if (sdhci_data_wine_cmd(cmd)) {
		WAWN_ON(host->data_cmd);
		host->data_cmd = cmd;
		sdhci_set_timeout(host, cmd);
	}

	if (cmd->data) {
		if (host->use_extewnaw_dma)
			sdhci_extewnaw_dma_pwepawe_data(host, cmd);
		ewse
			sdhci_pwepawe_data(host, cmd);
	}

	sdhci_wwitew(host, cmd->awg, SDHCI_AWGUMENT);

	sdhci_set_twansfew_mode(host, cmd);

	if ((cmd->fwags & MMC_WSP_136) && (cmd->fwags & MMC_WSP_BUSY)) {
		WAWN_ONCE(1, "Unsuppowted wesponse type!\n");
		/*
		 * This does not happen in pwactice because 136-bit wesponse
		 * commands nevew have busy waiting, so wathew than compwicate
		 * the ewwow path, just wemove busy waiting and continue.
		 */
		cmd->fwags &= ~MMC_WSP_BUSY;
	}

	if (!(cmd->fwags & MMC_WSP_PWESENT))
		fwags = SDHCI_CMD_WESP_NONE;
	ewse if (cmd->fwags & MMC_WSP_136)
		fwags = SDHCI_CMD_WESP_WONG;
	ewse if (cmd->fwags & MMC_WSP_BUSY)
		fwags = SDHCI_CMD_WESP_SHOWT_BUSY;
	ewse
		fwags = SDHCI_CMD_WESP_SHOWT;

	if (cmd->fwags & MMC_WSP_CWC)
		fwags |= SDHCI_CMD_CWC;
	if (cmd->fwags & MMC_WSP_OPCODE)
		fwags |= SDHCI_CMD_INDEX;

	/* CMD19 is speciaw in that the Data Pwesent Sewect shouwd be set */
	if (cmd->data || mmc_op_tuning(cmd->opcode))
		fwags |= SDHCI_CMD_DATA;

	timeout = jiffies;
	if (host->data_timeout)
		timeout += nsecs_to_jiffies(host->data_timeout);
	ewse if (!cmd->data && cmd->busy_timeout > 9000)
		timeout += DIV_WOUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	ewse
		timeout += 10 * HZ;
	sdhci_mod_timew(host, cmd->mwq, timeout);

	if (host->use_extewnaw_dma)
		sdhci_extewnaw_dma_pwe_twansfew(host, cmd);

	sdhci_wwitew(host, SDHCI_MAKE_CMD(cmd->opcode, fwags), SDHCI_COMMAND);

	wetuwn twue;
}

static boow sdhci_pwesent_ewwow(stwuct sdhci_host *host,
				stwuct mmc_command *cmd, boow pwesent)
{
	if (!pwesent || host->fwags & SDHCI_DEVICE_DEAD) {
		cmd->ewwow = -ENOMEDIUM;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow sdhci_send_command_wetwy(stwuct sdhci_host *host,
				     stwuct mmc_command *cmd,
				     unsigned wong fwags)
	__weweases(host->wock)
	__acquiwes(host->wock)
{
	stwuct mmc_command *defewwed_cmd = host->defewwed_cmd;
	int timeout = 10; /* Appwox. 10 ms */
	boow pwesent;

	whiwe (!sdhci_send_command(host, cmd)) {
		if (!timeout--) {
			pw_eww("%s: Contwowwew nevew weweased inhibit bit(s).\n",
			       mmc_hostname(host->mmc));
			sdhci_eww_stats_inc(host, CTWW_TIMEOUT);
			sdhci_dumpwegs(host);
			cmd->ewwow = -EIO;
			wetuwn fawse;
		}

		spin_unwock_iwqwestowe(&host->wock, fwags);

		usweep_wange(1000, 1250);

		pwesent = host->mmc->ops->get_cd(host->mmc);

		spin_wock_iwqsave(&host->wock, fwags);

		/* A defewwed command might disappeaw, handwe that */
		if (cmd == defewwed_cmd && cmd != host->defewwed_cmd)
			wetuwn twue;

		if (sdhci_pwesent_ewwow(host, cmd, pwesent))
			wetuwn fawse;
	}

	if (cmd == host->defewwed_cmd)
		host->defewwed_cmd = NUWW;

	wetuwn twue;
}

static void sdhci_wead_wsp_136(stwuct sdhci_host *host, stwuct mmc_command *cmd)
{
	int i, weg;

	fow (i = 0; i < 4; i++) {
		weg = SDHCI_WESPONSE + (3 - i) * 4;
		cmd->wesp[i] = sdhci_weadw(host, weg);
	}

	if (host->quiwks2 & SDHCI_QUIWK2_WSP_136_HAS_CWC)
		wetuwn;

	/* CWC is stwipped so we need to do some shifting */
	fow (i = 0; i < 4; i++) {
		cmd->wesp[i] <<= 8;
		if (i != 3)
			cmd->wesp[i] |= cmd->wesp[i + 1] >> 24;
	}
}

static void sdhci_finish_command(stwuct sdhci_host *host)
{
	stwuct mmc_command *cmd = host->cmd;

	host->cmd = NUWW;

	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			sdhci_wead_wsp_136(host, cmd);
		} ewse {
			cmd->wesp[0] = sdhci_weadw(host, SDHCI_WESPONSE);
		}
	}

	if (cmd->mwq->cap_cmd_duwing_tfw && cmd == cmd->mwq->cmd)
		mmc_command_done(host->mmc, cmd->mwq);

	/*
	 * The host can send and intewwupt when the busy state has
	 * ended, awwowing us to wait without wasting CPU cycwes.
	 * The busy signaw uses DAT0 so this is simiwaw to waiting
	 * fow data to compwete.
	 *
	 * Note: The 1.0 specification is a bit ambiguous about this
	 *       featuwe so thewe might be some pwobwems with owdew
	 *       contwowwews.
	 */
	if (cmd->fwags & MMC_WSP_BUSY) {
		if (cmd->data) {
			DBG("Cannot wait fow busy signaw when awso doing a data twansfew");
		} ewse if (!(host->quiwks & SDHCI_QUIWK_NO_BUSY_IWQ) &&
			   cmd == host->data_cmd) {
			/* Command compwete befowe busy is ended */
			wetuwn;
		}
	}

	/* Finished CMD23, now send actuaw command. */
	if (cmd == cmd->mwq->sbc) {
		if (!sdhci_send_command(host, cmd->mwq->cmd)) {
			WAWN_ON(host->defewwed_cmd);
			host->defewwed_cmd = cmd->mwq->cmd;
		}
	} ewse {

		/* Pwocessed actuaw command. */
		if (host->data && host->data_eawwy)
			sdhci_finish_data(host);

		if (!cmd->data)
			__sdhci_finish_mwq(host, cmd->mwq);
	}
}

static u16 sdhci_get_pweset_vawue(stwuct sdhci_host *host)
{
	u16 pweset = 0;

	switch (host->timing) {
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_SD_HS:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_HIGH_SPEED);
		bweak;
	case MMC_TIMING_UHS_SDW12:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW12);
		bweak;
	case MMC_TIMING_UHS_SDW25:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW25);
		bweak;
	case MMC_TIMING_UHS_SDW50:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW50);
		bweak;
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_MMC_HS200:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW104);
		bweak;
	case MMC_TIMING_UHS_DDW50:
	case MMC_TIMING_MMC_DDW52:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_DDW50);
		bweak;
	case MMC_TIMING_MMC_HS400:
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_HS400);
		bweak;
	defauwt:
		pw_wawn("%s: Invawid UHS-I mode sewected\n",
			mmc_hostname(host->mmc));
		pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW12);
		bweak;
	}
	wetuwn pweset;
}

u16 sdhci_cawc_cwk(stwuct sdhci_host *host, unsigned int cwock,
		   unsigned int *actuaw_cwock)
{
	int div = 0; /* Initiawized fow compiwew wawning */
	int weaw_div = div, cwk_muw = 1;
	u16 cwk = 0;
	boow switch_base_cwk = fawse;

	if (host->vewsion >= SDHCI_SPEC_300) {
		if (host->pweset_enabwed) {
			u16 pwe_vaw;

			cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
			pwe_vaw = sdhci_get_pweset_vawue(host);
			div = FIEWD_GET(SDHCI_PWESET_SDCWK_FWEQ_MASK, pwe_vaw);
			if (host->cwk_muw &&
				(pwe_vaw & SDHCI_PWESET_CWKGEN_SEW)) {
				cwk = SDHCI_PWOG_CWOCK_MODE;
				weaw_div = div + 1;
				cwk_muw = host->cwk_muw;
			} ewse {
				weaw_div = max_t(int, 1, div << 1);
			}
			goto cwock_set;
		}

		/*
		 * Check if the Host Contwowwew suppowts Pwogwammabwe Cwock
		 * Mode.
		 */
		if (host->cwk_muw) {
			fow (div = 1; div <= 1024; div++) {
				if ((host->max_cwk * host->cwk_muw / div)
					<= cwock)
					bweak;
			}
			if ((host->max_cwk * host->cwk_muw / div) <= cwock) {
				/*
				 * Set Pwogwammabwe Cwock Mode in the Cwock
				 * Contwow wegistew.
				 */
				cwk = SDHCI_PWOG_CWOCK_MODE;
				weaw_div = div;
				cwk_muw = host->cwk_muw;
				div--;
			} ewse {
				/*
				 * Divisow can be too smaww to weach cwock
				 * speed wequiwement. Then use the base cwock.
				 */
				switch_base_cwk = twue;
			}
		}

		if (!host->cwk_muw || switch_base_cwk) {
			/* Vewsion 3.00 divisows must be a muwtipwe of 2. */
			if (host->max_cwk <= cwock)
				div = 1;
			ewse {
				fow (div = 2; div < SDHCI_MAX_DIV_SPEC_300;
				     div += 2) {
					if ((host->max_cwk / div) <= cwock)
						bweak;
				}
			}
			weaw_div = div;
			div >>= 1;
			if ((host->quiwks2 & SDHCI_QUIWK2_CWOCK_DIV_ZEWO_BWOKEN)
				&& !div && host->max_cwk <= 25000000)
				div = 1;
		}
	} ewse {
		/* Vewsion 2.00 divisows must be a powew of 2. */
		fow (div = 1; div < SDHCI_MAX_DIV_SPEC_200; div *= 2) {
			if ((host->max_cwk / div) <= cwock)
				bweak;
		}
		weaw_div = div;
		div >>= 1;
	}

cwock_set:
	if (weaw_div)
		*actuaw_cwock = (host->max_cwk * cwk_muw) / weaw_div;
	cwk |= (div & SDHCI_DIV_MASK) << SDHCI_DIVIDEW_SHIFT;
	cwk |= ((div & SDHCI_DIV_HI_MASK) >> SDHCI_DIV_MASK_WEN)
		<< SDHCI_DIVIDEW_HI_SHIFT;

	wetuwn cwk;
}
EXPOWT_SYMBOW_GPW(sdhci_cawc_cwk);

void sdhci_enabwe_cwk(stwuct sdhci_host *host, u16 cwk)
{
	ktime_t timeout;

	cwk |= SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	/* Wait max 150 ms */
	timeout = ktime_add_ms(ktime_get(), 150);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		if (cwk & SDHCI_CWOCK_INT_STABWE)
			bweak;
		if (timedout) {
			pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
			       mmc_hostname(host->mmc));
			sdhci_eww_stats_inc(host, CTWW_TIMEOUT);
			sdhci_dumpwegs(host);
			wetuwn;
		}
		udeway(10);
	}

	if (host->vewsion >= SDHCI_SPEC_410 && host->v4_mode) {
		cwk |= SDHCI_CWOCK_PWW_EN;
		cwk &= ~SDHCI_CWOCK_INT_STABWE;
		sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

		/* Wait max 150 ms */
		timeout = ktime_add_ms(ktime_get(), 150);
		whiwe (1) {
			boow timedout = ktime_aftew(ktime_get(), timeout);

			cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
			if (cwk & SDHCI_CWOCK_INT_STABWE)
				bweak;
			if (timedout) {
				pw_eww("%s: PWW cwock nevew stabiwised.\n",
				       mmc_hostname(host->mmc));
				sdhci_eww_stats_inc(host, CTWW_TIMEOUT);
				sdhci_dumpwegs(host);
				wetuwn;
			}
			udeway(10);
		}
	}

	cwk |= SDHCI_CWOCK_CAWD_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);
}
EXPOWT_SYMBOW_GPW(sdhci_enabwe_cwk);

void sdhci_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	u16 cwk;

	host->mmc->actuaw_cwock = 0;

	sdhci_wwitew(host, 0, SDHCI_CWOCK_CONTWOW);

	if (cwock == 0)
		wetuwn;

	cwk = sdhci_cawc_cwk(host, cwock, &host->mmc->actuaw_cwock);
	sdhci_enabwe_cwk(host, cwk);
}
EXPOWT_SYMBOW_GPW(sdhci_set_cwock);

static void sdhci_set_powew_weg(stwuct sdhci_host *host, unsigned chaw mode,
				unsigned showt vdd)
{
	stwuct mmc_host *mmc = host->mmc;

	mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);

	if (mode != MMC_POWEW_OFF)
		sdhci_wwiteb(host, SDHCI_POWEW_ON, SDHCI_POWEW_CONTWOW);
	ewse
		sdhci_wwiteb(host, 0, SDHCI_POWEW_CONTWOW);
}

void sdhci_set_powew_noweg(stwuct sdhci_host *host, unsigned chaw mode,
			   unsigned showt vdd)
{
	u8 pww = 0;

	if (mode != MMC_POWEW_OFF) {
		switch (1 << vdd) {
		case MMC_VDD_165_195:
		/*
		 * Without a weguwatow, SDHCI does not suppowt 2.0v
		 * so we onwy get hewe if the dwivew dewibewatewy
		 * added the 2.0v wange to ocw_avaiw. Map it to 1.8v
		 * fow the puwpose of tuwning on the powew.
		 */
		case MMC_VDD_20_21:
			pww = SDHCI_POWEW_180;
			bweak;
		case MMC_VDD_29_30:
		case MMC_VDD_30_31:
			pww = SDHCI_POWEW_300;
			bweak;
		case MMC_VDD_32_33:
		case MMC_VDD_33_34:
		/*
		 * 3.4 ~ 3.6V awe vawid onwy fow those pwatfowms whewe it's
		 * known that the vowtage wange is suppowted by hawdwawe.
		 */
		case MMC_VDD_34_35:
		case MMC_VDD_35_36:
			pww = SDHCI_POWEW_330;
			bweak;
		defauwt:
			WAWN(1, "%s: Invawid vdd %#x\n",
			     mmc_hostname(host->mmc), vdd);
			bweak;
		}
	}

	if (host->pww == pww)
		wetuwn;

	host->pww = pww;

	if (pww == 0) {
		sdhci_wwiteb(host, 0, SDHCI_POWEW_CONTWOW);
		if (host->quiwks2 & SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON)
			sdhci_wuntime_pm_bus_off(host);
	} ewse {
		/*
		 * Spec says that we shouwd cweaw the powew weg befowe setting
		 * a new vawue. Some contwowwews don't seem to wike this though.
		 */
		if (!(host->quiwks & SDHCI_QUIWK_SINGWE_POWEW_WWITE))
			sdhci_wwiteb(host, 0, SDHCI_POWEW_CONTWOW);

		/*
		 * At weast the Mawveww CaFe chip gets confused if we set the
		 * vowtage and set tuwn on powew at the same time, so set the
		 * vowtage fiwst.
		 */
		if (host->quiwks & SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW)
			sdhci_wwiteb(host, pww, SDHCI_POWEW_CONTWOW);

		pww |= SDHCI_POWEW_ON;

		sdhci_wwiteb(host, pww, SDHCI_POWEW_CONTWOW);

		if (host->quiwks2 & SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON)
			sdhci_wuntime_pm_bus_on(host);

		/*
		 * Some contwowwews need an extwa 10ms deway of 10ms befowe
		 * they can appwy cwock aftew appwying powew
		 */
		if (host->quiwks & SDHCI_QUIWK_DEWAY_AFTEW_POWEW)
			mdeway(10);
	}
}
EXPOWT_SYMBOW_GPW(sdhci_set_powew_noweg);

void sdhci_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
		     unsigned showt vdd)
{
	if (IS_EWW(host->mmc->suppwy.vmmc))
		sdhci_set_powew_noweg(host, mode, vdd);
	ewse
		sdhci_set_powew_weg(host, mode, vdd);
}
EXPOWT_SYMBOW_GPW(sdhci_set_powew);

/*
 * Some contwowwews need to configuwe a vawid bus vowtage on theiw powew
 * wegistew wegawdwess of whethew an extewnaw weguwatow is taking cawe of powew
 * suppwy. This hewpew function takes cawe of it if set as the contwowwew's
 * sdhci_ops.set_powew cawwback.
 */
void sdhci_set_powew_and_bus_vowtage(stwuct sdhci_host *host,
				     unsigned chaw mode,
				     unsigned showt vdd)
{
	if (!IS_EWW(host->mmc->suppwy.vmmc)) {
		stwuct mmc_host *mmc = host->mmc;

		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);
	}
	sdhci_set_powew_noweg(host, mode, vdd);
}
EXPOWT_SYMBOW_GPW(sdhci_set_powew_and_bus_vowtage);

/*****************************************************************************\
 *                                                                           *
 * MMC cawwbacks                                                             *
 *                                                                           *
\*****************************************************************************/

void sdhci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd;
	unsigned wong fwags;
	boow pwesent;

	/* Fiwstwy check cawd pwesence */
	pwesent = mmc->ops->get_cd(mmc);

	spin_wock_iwqsave(&host->wock, fwags);

	sdhci_wed_activate(host);

	if (sdhci_pwesent_ewwow(host, mwq->cmd, pwesent))
		goto out_finish;

	cmd = sdhci_manuaw_cmd23(host, mwq) ? mwq->sbc : mwq->cmd;

	if (!sdhci_send_command_wetwy(host, cmd, fwags))
		goto out_finish;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn;

out_finish:
	sdhci_finish_mwq(host, mwq);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}
EXPOWT_SYMBOW_GPW(sdhci_wequest);

int sdhci_wequest_atomic(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&host->wock, fwags);

	if (sdhci_pwesent_ewwow(host, mwq->cmd, twue)) {
		sdhci_finish_mwq(host, mwq);
		goto out_finish;
	}

	cmd = sdhci_manuaw_cmd23(host, mwq) ? mwq->sbc : mwq->cmd;

	/*
	 * The HSQ may send a command in intewwupt context without powwing
	 * the busy signawing, which means we shouwd wetuwn BUSY if contwowwew
	 * has not weweased inhibit bits to awwow HSQ twying to send wequest
	 * again in non-atomic context. So we shouwd not finish this wequest
	 * hewe.
	 */
	if (!sdhci_send_command(host, cmd))
		wet = -EBUSY;
	ewse
		sdhci_wed_activate(host);

out_finish:
	spin_unwock_iwqwestowe(&host->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_wequest_atomic);

void sdhci_set_bus_width(stwuct sdhci_host *host, int width)
{
	u8 ctww;

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);
	if (width == MMC_BUS_WIDTH_8) {
		ctww &= ~SDHCI_CTWW_4BITBUS;
		ctww |= SDHCI_CTWW_8BITBUS;
	} ewse {
		if (host->mmc->caps & MMC_CAP_8_BIT_DATA)
			ctww &= ~SDHCI_CTWW_8BITBUS;
		if (width == MMC_BUS_WIDTH_4)
			ctww |= SDHCI_CTWW_4BITBUS;
		ewse
			ctww &= ~SDHCI_CTWW_4BITBUS;
	}
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}
EXPOWT_SYMBOW_GPW(sdhci_set_bus_width);

void sdhci_set_uhs_signawing(stwuct sdhci_host *host, unsigned timing)
{
	u16 ctww_2;

	ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	if ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDW104))
		ctww_2 |= SDHCI_CTWW_UHS_SDW104;
	ewse if (timing == MMC_TIMING_UHS_SDW12)
		ctww_2 |= SDHCI_CTWW_UHS_SDW12;
	ewse if (timing == MMC_TIMING_UHS_SDW25)
		ctww_2 |= SDHCI_CTWW_UHS_SDW25;
	ewse if (timing == MMC_TIMING_UHS_SDW50)
		ctww_2 |= SDHCI_CTWW_UHS_SDW50;
	ewse if ((timing == MMC_TIMING_UHS_DDW50) ||
		 (timing == MMC_TIMING_MMC_DDW52))
		ctww_2 |= SDHCI_CTWW_UHS_DDW50;
	ewse if (timing == MMC_TIMING_MMC_HS400)
		ctww_2 |= SDHCI_CTWW_HS400; /* Non-standawd */
	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
}
EXPOWT_SYMBOW_GPW(sdhci_set_uhs_signawing);

static boow sdhci_timing_has_pweset(unsigned chaw timing)
{
	switch (timing) {
	case MMC_TIMING_UHS_SDW12:
	case MMC_TIMING_UHS_SDW25:
	case MMC_TIMING_UHS_SDW50:
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_UHS_DDW50:
	case MMC_TIMING_MMC_DDW52:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow sdhci_pweset_needed(stwuct sdhci_host *host, unsigned chaw timing)
{
	wetuwn !(host->quiwks2 & SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN) &&
	       sdhci_timing_has_pweset(timing);
}

static boow sdhci_pwesetabwe_vawues_change(stwuct sdhci_host *host, stwuct mmc_ios *ios)
{
	/*
	 * Pweset Vawues awe: Dwivew Stwength, Cwock Genewatow and SDCWK/WCWK
	 * Fwequency. Check if pweset vawues need to be enabwed, ow the Dwivew
	 * Stwength needs updating. Note, cwock changes awe handwed sepawatewy.
	 */
	wetuwn !host->pweset_enabwed &&
	       (sdhci_pweset_needed(host, ios->timing) || host->dwv_type != ios->dwv_type);
}

void sdhci_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	boow weinit_uhs = host->weinit_uhs;
	boow tuwning_on_cwk = fawse;
	u8 ctww;

	host->weinit_uhs = fawse;

	if (ios->powew_mode == MMC_POWEW_UNDEFINED)
		wetuwn;

	if (host->fwags & SDHCI_DEVICE_DEAD) {
		if (!IS_EWW(mmc->suppwy.vmmc) &&
		    ios->powew_mode == MMC_POWEW_OFF)
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		wetuwn;
	}

	/*
	 * Weset the chip on each powew off.
	 * Shouwd cweaw out any weiwd states.
	 */
	if (ios->powew_mode == MMC_POWEW_OFF) {
		sdhci_wwitew(host, 0, SDHCI_SIGNAW_ENABWE);
		sdhci_weinit(host);
	}

	if (host->vewsion >= SDHCI_SPEC_300 &&
		(ios->powew_mode == MMC_POWEW_UP) &&
		!(host->quiwks2 & SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN))
		sdhci_enabwe_pweset_vawue(host, fawse);

	if (!ios->cwock || ios->cwock != host->cwock) {
		tuwning_on_cwk = ios->cwock && !host->cwock;

		host->ops->set_cwock(host, ios->cwock);
		host->cwock = ios->cwock;

		if (host->quiwks & SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK &&
		    host->cwock) {
			host->timeout_cwk = mmc->actuaw_cwock ?
						mmc->actuaw_cwock / 1000 :
						host->cwock / 1000;
			mmc->max_busy_timeout =
				host->ops->get_max_timeout_count ?
				host->ops->get_max_timeout_count(host) :
				1 << 27;
			mmc->max_busy_timeout /= host->timeout_cwk;
		}
	}

	if (host->ops->set_powew)
		host->ops->set_powew(host, ios->powew_mode, ios->vdd);
	ewse
		sdhci_set_powew(host, ios->powew_mode, ios->vdd);

	if (host->ops->pwatfowm_send_init_74_cwocks)
		host->ops->pwatfowm_send_init_74_cwocks(host, ios->powew_mode);

	host->ops->set_bus_width(host, ios->bus_width);

	/*
	 * Speciaw case to avoid muwtipwe cwock changes duwing vowtage
	 * switching.
	 */
	if (!weinit_uhs &&
	    tuwning_on_cwk &&
	    host->timing == ios->timing &&
	    host->vewsion >= SDHCI_SPEC_300 &&
	    !sdhci_pwesetabwe_vawues_change(host, ios))
		wetuwn;

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);

	if (!(host->quiwks & SDHCI_QUIWK_NO_HISPD_BIT)) {
		if (ios->timing == MMC_TIMING_SD_HS ||
		     ios->timing == MMC_TIMING_MMC_HS ||
		     ios->timing == MMC_TIMING_MMC_HS400 ||
		     ios->timing == MMC_TIMING_MMC_HS200 ||
		     ios->timing == MMC_TIMING_MMC_DDW52 ||
		     ios->timing == MMC_TIMING_UHS_SDW50 ||
		     ios->timing == MMC_TIMING_UHS_SDW104 ||
		     ios->timing == MMC_TIMING_UHS_DDW50 ||
		     ios->timing == MMC_TIMING_UHS_SDW25)
			ctww |= SDHCI_CTWW_HISPD;
		ewse
			ctww &= ~SDHCI_CTWW_HISPD;
	}

	if (host->vewsion >= SDHCI_SPEC_300) {
		u16 cwk, ctww_2;

		/*
		 * Accowding to SDHCI Spec v3.00, if the Pweset Vawue
		 * Enabwe in the Host Contwow 2 wegistew is set, we
		 * need to weset SD Cwock Enabwe befowe changing High
		 * Speed Enabwe to avoid genewating cwock gwitches.
		 */
		cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		if (cwk & SDHCI_CWOCK_CAWD_EN) {
			cwk &= ~SDHCI_CWOCK_CAWD_EN;
			sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);
		}

		sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);

		if (!host->pweset_enabwed) {
			/*
			 * We onwy need to set Dwivew Stwength if the
			 * pweset vawue enabwe is not set.
			 */
			ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
			ctww_2 &= ~SDHCI_CTWW_DWV_TYPE_MASK;
			if (ios->dwv_type == MMC_SET_DWIVEW_TYPE_A)
				ctww_2 |= SDHCI_CTWW_DWV_TYPE_A;
			ewse if (ios->dwv_type == MMC_SET_DWIVEW_TYPE_B)
				ctww_2 |= SDHCI_CTWW_DWV_TYPE_B;
			ewse if (ios->dwv_type == MMC_SET_DWIVEW_TYPE_C)
				ctww_2 |= SDHCI_CTWW_DWV_TYPE_C;
			ewse if (ios->dwv_type == MMC_SET_DWIVEW_TYPE_D)
				ctww_2 |= SDHCI_CTWW_DWV_TYPE_D;
			ewse {
				pw_wawn("%s: invawid dwivew type, defauwt to dwivew type B\n",
					mmc_hostname(mmc));
				ctww_2 |= SDHCI_CTWW_DWV_TYPE_B;
			}

			sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
			host->dwv_type = ios->dwv_type;
		}

		host->ops->set_uhs_signawing(host, ios->timing);
		host->timing = ios->timing;

		if (sdhci_pweset_needed(host, ios->timing)) {
			u16 pweset;

			sdhci_enabwe_pweset_vawue(host, twue);
			pweset = sdhci_get_pweset_vawue(host);
			ios->dwv_type = FIEWD_GET(SDHCI_PWESET_DWV_MASK,
						  pweset);
			host->dwv_type = ios->dwv_type;
		}

		/* We-enabwe SD Cwock */
		host->ops->set_cwock(host, host->cwock);
	} ewse
		sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}
EXPOWT_SYMBOW_GPW(sdhci_set_ios);

static int sdhci_get_cd(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	int gpio_cd = mmc_gpio_get_cd(mmc);

	if (host->fwags & SDHCI_DEVICE_DEAD)
		wetuwn 0;

	/* If nonwemovabwe, assume that the cawd is awways pwesent. */
	if (!mmc_cawd_is_wemovabwe(mmc))
		wetuwn 1;

	/*
	 * Twy swot gpio detect, if defined it take pwecedence
	 * ovew buiwd in contwowwew functionawity
	 */
	if (gpio_cd >= 0)
		wetuwn !!gpio_cd;

	/* If powwing, assume that the cawd is awways pwesent. */
	if (host->quiwks & SDHCI_QUIWK_BWOKEN_CAWD_DETECTION)
		wetuwn 1;

	/* Host native cawd detect */
	wetuwn !!(sdhci_weadw(host, SDHCI_PWESENT_STATE) & SDHCI_CAWD_PWESENT);
}

int sdhci_get_cd_nogpio(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->fwags & SDHCI_DEVICE_DEAD)
		goto out;

	wet = !!(sdhci_weadw(host, SDHCI_PWESENT_STATE) & SDHCI_CAWD_PWESENT);
out:
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_get_cd_nogpio);

static int sdhci_check_wo(stwuct sdhci_host *host)
{
	unsigned wong fwags;
	int is_weadonwy;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->fwags & SDHCI_DEVICE_DEAD)
		is_weadonwy = 0;
	ewse if (host->ops->get_wo)
		is_weadonwy = host->ops->get_wo(host);
	ewse if (mmc_can_gpio_wo(host->mmc))
		is_weadonwy = mmc_gpio_get_wo(host->mmc);
	ewse
		is_weadonwy = !(sdhci_weadw(host, SDHCI_PWESENT_STATE)
				& SDHCI_WWITE_PWOTECT);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	/* This quiwk needs to be wepwaced by a cawwback-function watew */
	wetuwn host->quiwks & SDHCI_QUIWK_INVEWTED_WWITE_PWOTECT ?
		!is_weadonwy : is_weadonwy;
}

#define SAMPWE_COUNT	5

static int sdhci_get_wo(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	int i, wo_count;

	if (!(host->quiwks & SDHCI_QUIWK_UNSTABWE_WO_DETECT))
		wetuwn sdhci_check_wo(host);

	wo_count = 0;
	fow (i = 0; i < SAMPWE_COUNT; i++) {
		if (sdhci_check_wo(host)) {
			if (++wo_count > SAMPWE_COUNT / 2)
				wetuwn 1;
		}
		msweep(30);
	}
	wetuwn 0;
}

static void sdhci_hw_weset(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	if (host->ops && host->ops->hw_weset)
		host->ops->hw_weset(host);
}

static void sdhci_enabwe_sdio_iwq_nowock(stwuct sdhci_host *host, int enabwe)
{
	if (!(host->fwags & SDHCI_DEVICE_DEAD)) {
		if (enabwe)
			host->iew |= SDHCI_INT_CAWD_INT;
		ewse
			host->iew &= ~SDHCI_INT_CAWD_INT;

		sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
		sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
	}
}

void sdhci_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	if (enabwe)
		pm_wuntime_get_nowesume(mmc_dev(mmc));

	spin_wock_iwqsave(&host->wock, fwags);
	sdhci_enabwe_sdio_iwq_nowock(host, enabwe);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (!enabwe)
		pm_wuntime_put_noidwe(mmc_dev(mmc));
}
EXPOWT_SYMBOW_GPW(sdhci_enabwe_sdio_iwq);

static void sdhci_ack_sdio_iwq(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	sdhci_enabwe_sdio_iwq_nowock(host, twue);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

int sdhci_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
				      stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u16 ctww;
	int wet;

	/*
	 * Signaw Vowtage Switching is onwy appwicabwe fow Host Contwowwews
	 * v3.00 and above.
	 */
	if (host->vewsion < SDHCI_SPEC_300)
		wetuwn 0;

	ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		if (!(host->fwags & SDHCI_SIGNAWING_330))
			wetuwn -EINVAW;
		/* Set 1.8V Signaw Enabwe in the Host Contwow2 wegistew to 0 */
		ctww &= ~SDHCI_CTWW_VDD_180;
		sdhci_wwitew(host, ctww, SDHCI_HOST_CONTWOW2);

		if (!IS_EWW(mmc->suppwy.vqmmc)) {
			wet = mmc_weguwatow_set_vqmmc(mmc, ios);
			if (wet < 0) {
				pw_wawn("%s: Switching to 3.3V signawwing vowtage faiwed\n",
					mmc_hostname(mmc));
				wetuwn -EIO;
			}
		}
		/* Wait fow 5ms */
		usweep_wange(5000, 5500);

		/* 3.3V weguwatow output shouwd be stabwe within 5 ms */
		ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		if (!(ctww & SDHCI_CTWW_VDD_180))
			wetuwn 0;

		pw_wawn("%s: 3.3V weguwatow output did not become stabwe\n",
			mmc_hostname(mmc));

		wetuwn -EAGAIN;
	case MMC_SIGNAW_VOWTAGE_180:
		if (!(host->fwags & SDHCI_SIGNAWING_180))
			wetuwn -EINVAW;
		if (!IS_EWW(mmc->suppwy.vqmmc)) {
			wet = mmc_weguwatow_set_vqmmc(mmc, ios);
			if (wet < 0) {
				pw_wawn("%s: Switching to 1.8V signawwing vowtage faiwed\n",
					mmc_hostname(mmc));
				wetuwn -EIO;
			}
		}

		/*
		 * Enabwe 1.8V Signaw Enabwe in the Host Contwow2
		 * wegistew
		 */
		ctww |= SDHCI_CTWW_VDD_180;
		sdhci_wwitew(host, ctww, SDHCI_HOST_CONTWOW2);

		/* Some contwowwew need to do mowe when switching */
		if (host->ops->vowtage_switch)
			host->ops->vowtage_switch(host);

		/* 1.8V weguwatow output shouwd be stabwe within 5 ms */
		ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		if (ctww & SDHCI_CTWW_VDD_180)
			wetuwn 0;

		pw_wawn("%s: 1.8V weguwatow output did not become stabwe\n",
			mmc_hostname(mmc));

		wetuwn -EAGAIN;
	case MMC_SIGNAW_VOWTAGE_120:
		if (!(host->fwags & SDHCI_SIGNAWING_120))
			wetuwn -EINVAW;
		if (!IS_EWW(mmc->suppwy.vqmmc)) {
			wet = mmc_weguwatow_set_vqmmc(mmc, ios);
			if (wet < 0) {
				pw_wawn("%s: Switching to 1.2V signawwing vowtage faiwed\n",
					mmc_hostname(mmc));
				wetuwn -EIO;
			}
		}
		wetuwn 0;
	defauwt:
		/* No signaw vowtage switch wequiwed */
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(sdhci_stawt_signaw_vowtage_switch);

static int sdhci_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 pwesent_state;

	/* Check whethew DAT[0] is 0 */
	pwesent_state = sdhci_weadw(host, SDHCI_PWESENT_STATE);

	wetuwn !(pwesent_state & SDHCI_DATA_0_WVW_MASK);
}

static int sdhci_pwepawe_hs400_tuning(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	host->fwags |= SDHCI_HS400_TUNING;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn 0;
}

void sdhci_stawt_tuning(stwuct sdhci_host *host)
{
	u16 ctww;

	ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	ctww |= SDHCI_CTWW_EXEC_TUNING;
	if (host->quiwks2 & SDHCI_QUIWK2_TUNING_WOWK_AWOUND)
		ctww |= SDHCI_CTWW_TUNED_CWK;
	sdhci_wwitew(host, ctww, SDHCI_HOST_CONTWOW2);

	/*
	 * As pew the Host Contwowwew spec v3.00, tuning command
	 * genewates Buffew Wead Weady intewwupt, so enabwe that.
	 *
	 * Note: The spec cweawwy says that when tuning sequence
	 * is being pewfowmed, the contwowwew does not genewate
	 * intewwupts othew than Buffew Wead Weady intewwupt. But
	 * to make suwe we don't hit a contwowwew bug, we _onwy_
	 * enabwe Buffew Wead Weady intewwupt hewe.
	 */
	sdhci_wwitew(host, SDHCI_INT_DATA_AVAIW, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, SDHCI_INT_DATA_AVAIW, SDHCI_SIGNAW_ENABWE);
}
EXPOWT_SYMBOW_GPW(sdhci_stawt_tuning);

void sdhci_end_tuning(stwuct sdhci_host *host)
{
	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
}
EXPOWT_SYMBOW_GPW(sdhci_end_tuning);

void sdhci_weset_tuning(stwuct sdhci_host *host)
{
	u16 ctww;

	ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	ctww &= ~SDHCI_CTWW_TUNED_CWK;
	ctww &= ~SDHCI_CTWW_EXEC_TUNING;
	sdhci_wwitew(host, ctww, SDHCI_HOST_CONTWOW2);
}
EXPOWT_SYMBOW_GPW(sdhci_weset_tuning);

void sdhci_abowt_tuning(stwuct sdhci_host *host, u32 opcode)
{
	sdhci_weset_tuning(host);

	sdhci_weset_fow(host, TUNING_ABOWT);

	sdhci_end_tuning(host);

	mmc_send_abowt_tuning(host->mmc, opcode);
}
EXPOWT_SYMBOW_GPW(sdhci_abowt_tuning);

/*
 * We use sdhci_send_tuning() because mmc_send_tuning() is not a good fit. SDHCI
 * tuning command does not have a data paywoad (ow wathew the hawdwawe does it
 * automaticawwy) so mmc_send_tuning() wiww wetuwn -EIO. Awso the tuning command
 * intewwupt setup is diffewent to othew commands and thewe is no timeout
 * intewwupt so speciaw handwing is needed.
 */
void sdhci_send_tuning(stwuct sdhci_host *host, u32 opcode)
{
	stwuct mmc_host *mmc = host->mmc;
	stwuct mmc_command cmd = {};
	stwuct mmc_wequest mwq = {};
	unsigned wong fwags;
	u32 b = host->sdma_boundawy;

	spin_wock_iwqsave(&host->wock, fwags);

	cmd.opcode = opcode;
	cmd.fwags = MMC_WSP_W1 | MMC_CMD_ADTC;
	cmd.mwq = &mwq;

	mwq.cmd = &cmd;
	/*
	 * In wesponse to CMD19, the cawd sends 64 bytes of tuning
	 * bwock to the Host Contwowwew. So we set the bwock size
	 * to 64 hewe.
	 */
	if (cmd.opcode == MMC_SEND_TUNING_BWOCK_HS200 &&
	    mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		sdhci_wwitew(host, SDHCI_MAKE_BWKSZ(b, 128), SDHCI_BWOCK_SIZE);
	ewse
		sdhci_wwitew(host, SDHCI_MAKE_BWKSZ(b, 64), SDHCI_BWOCK_SIZE);

	/*
	 * The tuning bwock is sent by the cawd to the host contwowwew.
	 * So we set the TWNS_WEAD bit in the Twansfew Mode wegistew.
	 * This awso takes cawe of setting DMA Enabwe and Muwti Bwock
	 * Sewect in the same wegistew to 0.
	 */
	sdhci_wwitew(host, SDHCI_TWNS_WEAD, SDHCI_TWANSFEW_MODE);

	if (!sdhci_send_command_wetwy(host, &cmd, fwags)) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		host->tuning_done = 0;
		wetuwn;
	}

	host->cmd = NUWW;

	sdhci_dew_timew(host, &mwq);

	host->tuning_done = 0;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	/* Wait fow Buffew Wead Weady intewwupt */
	wait_event_timeout(host->buf_weady_int, (host->tuning_done == 1),
			   msecs_to_jiffies(50));

}
EXPOWT_SYMBOW_GPW(sdhci_send_tuning);

int __sdhci_execute_tuning(stwuct sdhci_host *host, u32 opcode)
{
	int i;

	/*
	 * Issue opcode wepeatedwy tiww Execute Tuning is set to 0 ow the numbew
	 * of woops weaches tuning woop count.
	 */
	fow (i = 0; i < host->tuning_woop_count; i++) {
		u16 ctww;

		sdhci_send_tuning(host, opcode);

		if (!host->tuning_done) {
			pw_debug("%s: Tuning timeout, fawwing back to fixed sampwing cwock\n",
				 mmc_hostname(host->mmc));
			sdhci_abowt_tuning(host, opcode);
			wetuwn -ETIMEDOUT;
		}

		/* Spec does not wequiwe a deway between tuning cycwes */
		if (host->tuning_deway > 0)
			mdeway(host->tuning_deway);

		ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		if (!(ctww & SDHCI_CTWW_EXEC_TUNING)) {
			if (ctww & SDHCI_CTWW_TUNED_CWK)
				wetuwn 0; /* Success! */
			bweak;
		}

	}

	pw_info("%s: Tuning faiwed, fawwing back to fixed sampwing cwock\n",
		mmc_hostname(host->mmc));
	sdhci_weset_tuning(host);
	wetuwn -EAGAIN;
}
EXPOWT_SYMBOW_GPW(__sdhci_execute_tuning);

int sdhci_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	int eww = 0;
	unsigned int tuning_count = 0;
	boow hs400_tuning;

	hs400_tuning = host->fwags & SDHCI_HS400_TUNING;

	if (host->tuning_mode == SDHCI_TUNING_MODE_1)
		tuning_count = host->tuning_count;

	/*
	 * The Host Contwowwew needs tuning in case of SDW104 and DDW50
	 * mode, and fow SDW50 mode when Use Tuning fow SDW50 is set in
	 * the Capabiwities wegistew.
	 * If the Host Contwowwew suppowts the HS200 mode then the
	 * tuning function has to be executed.
	 */
	switch (host->timing) {
	/* HS400 tuning is done in HS200 mode */
	case MMC_TIMING_MMC_HS400:
		eww = -EINVAW;
		goto out;

	case MMC_TIMING_MMC_HS200:
		/*
		 * Pewiodic we-tuning fow HS400 is not expected to be needed, so
		 * disabwe it hewe.
		 */
		if (hs400_tuning)
			tuning_count = 0;
		bweak;

	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_UHS_DDW50:
		bweak;

	case MMC_TIMING_UHS_SDW50:
		if (host->fwags & SDHCI_SDW50_NEEDS_TUNING)
			bweak;
		fawwthwough;

	defauwt:
		goto out;
	}

	if (host->ops->pwatfowm_execute_tuning) {
		eww = host->ops->pwatfowm_execute_tuning(host, opcode);
		goto out;
	}

	mmc->wetune_pewiod = tuning_count;

	if (host->tuning_deway < 0)
		host->tuning_deway = opcode == MMC_SEND_TUNING_BWOCK;

	sdhci_stawt_tuning(host);

	host->tuning_eww = __sdhci_execute_tuning(host, opcode);

	sdhci_end_tuning(host);
out:
	host->fwags &= ~SDHCI_HS400_TUNING;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sdhci_execute_tuning);

static void sdhci_enabwe_pweset_vawue(stwuct sdhci_host *host, boow enabwe)
{
	/* Host Contwowwew v3.00 defines pweset vawue wegistews */
	if (host->vewsion < SDHCI_SPEC_300)
		wetuwn;

	/*
	 * We onwy enabwe ow disabwe Pweset Vawue if they awe not awweady
	 * enabwed ow disabwed wespectivewy. Othewwise, we baiw out.
	 */
	if (host->pweset_enabwed != enabwe) {
		u16 ctww = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);

		if (enabwe)
			ctww |= SDHCI_CTWW_PWESET_VAW_ENABWE;
		ewse
			ctww &= ~SDHCI_CTWW_PWESET_VAW_ENABWE;

		sdhci_wwitew(host, ctww, SDHCI_HOST_CONTWOW2);

		if (enabwe)
			host->fwags |= SDHCI_PV_ENABWED;
		ewse
			host->fwags &= ~SDHCI_PV_ENABWED;

		host->pweset_enabwed = enabwe;
	}
}

static void sdhci_post_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
				int eww)
{
	stwuct mmc_data *data = mwq->data;

	if (data->host_cookie != COOKIE_UNMAPPED)
		dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));

	data->host_cookie = COOKIE_UNMAPPED;
}

static void sdhci_pwe_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	mwq->data->host_cookie = COOKIE_UNMAPPED;

	/*
	 * No pwe-mapping in the pwe hook if we'we using the bounce buffew,
	 * fow that we wouwd need two bounce buffews since one buffew is
	 * in fwight when this is getting cawwed.
	 */
	if (host->fwags & SDHCI_WEQ_USE_DMA && !host->bounce_buffew)
		sdhci_pwe_dma_twansfew(host, mwq->data, COOKIE_PWE_MAPPED);
}

static void sdhci_ewwow_out_mwqs(stwuct sdhci_host *host, int eww)
{
	if (host->data_cmd) {
		host->data_cmd->ewwow = eww;
		sdhci_finish_mwq(host, host->data_cmd->mwq);
	}

	if (host->cmd) {
		host->cmd->ewwow = eww;
		sdhci_finish_mwq(host, host->cmd->mwq);
	}
}

static void sdhci_cawd_event(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	int pwesent;

	/* Fiwst check if cwient has pwovided theiw own cawd event */
	if (host->ops->cawd_event)
		host->ops->cawd_event(host);

	pwesent = mmc->ops->get_cd(mmc);

	spin_wock_iwqsave(&host->wock, fwags);

	/* Check sdhci_has_wequests() fiwst in case we awe wuntime suspended */
	if (sdhci_has_wequests(host) && !pwesent) {
		pw_eww("%s: Cawd wemoved duwing twansfew!\n",
			mmc_hostname(mmc));
		pw_eww("%s: Wesetting contwowwew.\n",
			mmc_hostname(mmc));

		sdhci_weset_fow(host, CAWD_WEMOVED);

		sdhci_ewwow_out_mwqs(host, -ENOMEDIUM);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static const stwuct mmc_host_ops sdhci_ops = {
	.wequest	= sdhci_wequest,
	.post_weq	= sdhci_post_weq,
	.pwe_weq	= sdhci_pwe_weq,
	.set_ios	= sdhci_set_ios,
	.get_cd		= sdhci_get_cd,
	.get_wo		= sdhci_get_wo,
	.cawd_hw_weset	= sdhci_hw_weset,
	.enabwe_sdio_iwq = sdhci_enabwe_sdio_iwq,
	.ack_sdio_iwq    = sdhci_ack_sdio_iwq,
	.stawt_signaw_vowtage_switch	= sdhci_stawt_signaw_vowtage_switch,
	.pwepawe_hs400_tuning		= sdhci_pwepawe_hs400_tuning,
	.execute_tuning			= sdhci_execute_tuning,
	.cawd_event			= sdhci_cawd_event,
	.cawd_busy	= sdhci_cawd_busy,
};

/*****************************************************************************\
 *                                                                           *
 * Wequest done                                                              *
 *                                                                           *
\*****************************************************************************/

static boow sdhci_wequest_done(stwuct sdhci_host *host)
{
	unsigned wong fwags;
	stwuct mmc_wequest *mwq;
	int i;

	spin_wock_iwqsave(&host->wock, fwags);

	fow (i = 0; i < SDHCI_MAX_MWQS; i++) {
		mwq = host->mwqs_done[i];
		if (mwq)
			bweak;
	}

	if (!mwq) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn twue;
	}

	/*
	 * The contwowwew needs a weset of intewnaw state machines
	 * upon ewwow conditions.
	 */
	if (sdhci_needs_weset(host, mwq)) {
		/*
		 * Do not finish untiw command and data wines awe avaiwabwe fow
		 * weset. Note thewe can onwy be one othew mwq, so it cannot
		 * awso be in mwqs_done, othewwise host->cmd and host->data_cmd
		 * wouwd both be nuww.
		 */
		if (host->cmd || host->data_cmd) {
			spin_unwock_iwqwestowe(&host->wock, fwags);
			wetuwn twue;
		}

		/* Some contwowwews need this kick ow weset won't wowk hewe */
		if (host->quiwks & SDHCI_QUIWK_CWOCK_BEFOWE_WESET)
			/* This is to fowce an update */
			host->ops->set_cwock(host, host->cwock);

		sdhci_weset_fow(host, WEQUEST_EWWOW);

		host->pending_weset = fawse;
	}

	/*
	 * Awways unmap the data buffews if they wewe mapped by
	 * sdhci_pwepawe_data() whenevew we finish with a wequest.
	 * This avoids weaking DMA mappings on ewwow.
	 */
	if (host->fwags & SDHCI_WEQ_USE_DMA) {
		stwuct mmc_data *data = mwq->data;

		if (host->use_extewnaw_dma && data &&
		    (mwq->cmd->ewwow || data->ewwow)) {
			stwuct dma_chan *chan = sdhci_extewnaw_dma_channew(host, data);

			host->mwqs_done[i] = NUWW;
			spin_unwock_iwqwestowe(&host->wock, fwags);
			dmaengine_tewminate_sync(chan);
			spin_wock_iwqsave(&host->wock, fwags);
			sdhci_set_mwq_done(host, mwq);
		}

		if (data && data->host_cookie == COOKIE_MAPPED) {
			if (host->bounce_buffew) {
				/*
				 * On weads, copy the bounced data into the
				 * sgwist
				 */
				if (mmc_get_dma_diw(data) == DMA_FWOM_DEVICE) {
					unsigned int wength = data->bytes_xfewed;

					if (wength > host->bounce_buffew_size) {
						pw_eww("%s: bounce buffew is %u bytes but DMA cwaims to have twansfewwed %u bytes\n",
						       mmc_hostname(host->mmc),
						       host->bounce_buffew_size,
						       data->bytes_xfewed);
						/* Cap it down and continue */
						wength = host->bounce_buffew_size;
					}
					dma_sync_singwe_fow_cpu(
						mmc_dev(host->mmc),
						host->bounce_addw,
						host->bounce_buffew_size,
						DMA_FWOM_DEVICE);
					sg_copy_fwom_buffew(data->sg,
						data->sg_wen,
						host->bounce_buffew,
						wength);
				} ewse {
					/* No copying, just switch ownewship */
					dma_sync_singwe_fow_cpu(
						mmc_dev(host->mmc),
						host->bounce_addw,
						host->bounce_buffew_size,
						mmc_get_dma_diw(data));
				}
			} ewse {
				/* Unmap the waw data */
				dma_unmap_sg(mmc_dev(host->mmc), data->sg,
					     data->sg_wen,
					     mmc_get_dma_diw(data));
			}
			data->host_cookie = COOKIE_UNMAPPED;
		}
	}

	host->mwqs_done[i] = NUWW;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (host->ops->wequest_done)
		host->ops->wequest_done(host, mwq);
	ewse
		mmc_wequest_done(host->mmc, mwq);

	wetuwn fawse;
}

static void sdhci_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sdhci_host *host = containew_of(wowk, stwuct sdhci_host,
					       compwete_wowk);

	whiwe (!sdhci_wequest_done(host))
		;
}

static void sdhci_timeout_timew(stwuct timew_wist *t)
{
	stwuct sdhci_host *host;
	unsigned wong fwags;

	host = fwom_timew(host, t, timew);

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->cmd && !sdhci_data_wine_cmd(host->cmd)) {
		pw_eww("%s: Timeout waiting fow hawdwawe cmd intewwupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_eww_stats_inc(host, WEQ_TIMEOUT);
		sdhci_dumpwegs(host);

		host->cmd->ewwow = -ETIMEDOUT;
		sdhci_finish_mwq(host, host->cmd->mwq);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void sdhci_timeout_data_timew(stwuct timew_wist *t)
{
	stwuct sdhci_host *host;
	unsigned wong fwags;

	host = fwom_timew(host, t, data_timew);

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->data || host->data_cmd ||
	    (host->cmd && sdhci_data_wine_cmd(host->cmd))) {
		pw_eww("%s: Timeout waiting fow hawdwawe intewwupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_eww_stats_inc(host, WEQ_TIMEOUT);
		sdhci_dumpwegs(host);

		if (host->data) {
			host->data->ewwow = -ETIMEDOUT;
			__sdhci_finish_data(host, twue);
			queue_wowk(host->compwete_wq, &host->compwete_wowk);
		} ewse if (host->data_cmd) {
			host->data_cmd->ewwow = -ETIMEDOUT;
			sdhci_finish_mwq(host, host->data_cmd->mwq);
		} ewse {
			host->cmd->ewwow = -ETIMEDOUT;
			sdhci_finish_mwq(host, host->cmd->mwq);
		}
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

/*****************************************************************************\
 *                                                                           *
 * Intewwupt handwing                                                        *
 *                                                                           *
\*****************************************************************************/

static void sdhci_cmd_iwq(stwuct sdhci_host *host, u32 intmask, u32 *intmask_p)
{
	/* Handwe auto-CMD12 ewwow */
	if (intmask & SDHCI_INT_AUTO_CMD_EWW && host->data_cmd) {
		stwuct mmc_wequest *mwq = host->data_cmd->mwq;
		u16 auto_cmd_status = sdhci_weadw(host, SDHCI_AUTO_CMD_STATUS);
		int data_eww_bit = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
				   SDHCI_INT_DATA_TIMEOUT :
				   SDHCI_INT_DATA_CWC;

		/* Tweat auto-CMD12 ewwow the same as data ewwow */
		if (!mwq->sbc && (host->fwags & SDHCI_AUTO_CMD12)) {
			*intmask_p |= data_eww_bit;
			wetuwn;
		}
	}

	if (!host->cmd) {
		/*
		 * SDHCI wecovews fwom ewwows by wesetting the cmd and data
		 * ciwcuits.  Untiw that is done, thewe vewy weww might be mowe
		 * intewwupts, so ignowe them in that case.
		 */
		if (host->pending_weset)
			wetuwn;
		pw_eww("%s: Got command intewwupt 0x%08x even though no command opewation was in pwogwess.\n",
		       mmc_hostname(host->mmc), (unsigned)intmask);
		sdhci_eww_stats_inc(host, UNEXPECTED_IWQ);
		sdhci_dumpwegs(host);
		wetuwn;
	}

	if (intmask & (SDHCI_INT_TIMEOUT | SDHCI_INT_CWC |
		       SDHCI_INT_END_BIT | SDHCI_INT_INDEX)) {
		if (intmask & SDHCI_INT_TIMEOUT) {
			host->cmd->ewwow = -ETIMEDOUT;
			sdhci_eww_stats_inc(host, CMD_TIMEOUT);
		} ewse {
			host->cmd->ewwow = -EIWSEQ;
			if (!mmc_op_tuning(host->cmd->opcode))
				sdhci_eww_stats_inc(host, CMD_CWC);
		}
		/* Tweat data command CWC ewwow the same as data CWC ewwow */
		if (host->cmd->data &&
		    (intmask & (SDHCI_INT_CWC | SDHCI_INT_TIMEOUT)) ==
		     SDHCI_INT_CWC) {
			host->cmd = NUWW;
			*intmask_p |= SDHCI_INT_DATA_CWC;
			wetuwn;
		}

		__sdhci_finish_mwq(host, host->cmd->mwq);
		wetuwn;
	}

	/* Handwe auto-CMD23 ewwow */
	if (intmask & SDHCI_INT_AUTO_CMD_EWW) {
		stwuct mmc_wequest *mwq = host->cmd->mwq;
		u16 auto_cmd_status = sdhci_weadw(host, SDHCI_AUTO_CMD_STATUS);
		int eww = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
			  -ETIMEDOUT :
			  -EIWSEQ;

		sdhci_eww_stats_inc(host, AUTO_CMD);

		if (sdhci_auto_cmd23(host, mwq)) {
			mwq->sbc->ewwow = eww;
			__sdhci_finish_mwq(host, mwq);
			wetuwn;
		}
	}

	if (intmask & SDHCI_INT_WESPONSE)
		sdhci_finish_command(host);
}

static void sdhci_adma_show_ewwow(stwuct sdhci_host *host)
{
	void *desc = host->adma_tabwe;
	dma_addw_t dma = host->adma_addw;

	sdhci_dumpwegs(host);

	whiwe (twue) {
		stwuct sdhci_adma2_64_desc *dma_desc = desc;

		if (host->fwags & SDHCI_USE_64_BIT_DMA)
			SDHCI_DUMP("%08wwx: DMA 0x%08x%08x, WEN 0x%04x, Attw=0x%02x\n",
			    (unsigned wong wong)dma,
			    we32_to_cpu(dma_desc->addw_hi),
			    we32_to_cpu(dma_desc->addw_wo),
			    we16_to_cpu(dma_desc->wen),
			    we16_to_cpu(dma_desc->cmd));
		ewse
			SDHCI_DUMP("%08wwx: DMA 0x%08x, WEN 0x%04x, Attw=0x%02x\n",
			    (unsigned wong wong)dma,
			    we32_to_cpu(dma_desc->addw_wo),
			    we16_to_cpu(dma_desc->wen),
			    we16_to_cpu(dma_desc->cmd));

		desc += host->desc_sz;
		dma += host->desc_sz;

		if (dma_desc->cmd & cpu_to_we16(ADMA2_END))
			bweak;
	}
}

static void sdhci_data_iwq(stwuct sdhci_host *host, u32 intmask)
{
	/*
	 * CMD19 genewates _onwy_ Buffew Wead Weady intewwupt if
	 * use sdhci_send_tuning.
	 * Need to excwude this case: PIO mode and use mmc_send_tuning,
	 * If not, sdhci_twansfew_pio wiww nevew be cawwed, make the
	 * SDHCI_INT_DATA_AVAIW awways thewe, stuck in iwq stowm.
	 */
	if (intmask & SDHCI_INT_DATA_AVAIW && !host->data) {
		if (mmc_op_tuning(SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND)))) {
			host->tuning_done = 1;
			wake_up(&host->buf_weady_int);
			wetuwn;
		}
	}

	if (!host->data) {
		stwuct mmc_command *data_cmd = host->data_cmd;

		/*
		 * The "data compwete" intewwupt is awso used to
		 * indicate that a busy state has ended. See comment
		 * above in sdhci_cmd_iwq().
		 */
		if (data_cmd && (data_cmd->fwags & MMC_WSP_BUSY)) {
			if (intmask & SDHCI_INT_DATA_TIMEOUT) {
				host->data_cmd = NUWW;
				data_cmd->ewwow = -ETIMEDOUT;
				sdhci_eww_stats_inc(host, CMD_TIMEOUT);
				__sdhci_finish_mwq(host, data_cmd->mwq);
				wetuwn;
			}
			if (intmask & SDHCI_INT_DATA_END) {
				host->data_cmd = NUWW;
				/*
				 * Some cawds handwe busy-end intewwupt
				 * befowe the command compweted, so make
				 * suwe we do things in the pwopew owdew.
				 */
				if (host->cmd == data_cmd)
					wetuwn;

				__sdhci_finish_mwq(host, data_cmd->mwq);
				wetuwn;
			}
		}

		/*
		 * SDHCI wecovews fwom ewwows by wesetting the cmd and data
		 * ciwcuits. Untiw that is done, thewe vewy weww might be mowe
		 * intewwupts, so ignowe them in that case.
		 */
		if (host->pending_weset)
			wetuwn;

		pw_eww("%s: Got data intewwupt 0x%08x even though no data opewation was in pwogwess.\n",
		       mmc_hostname(host->mmc), (unsigned)intmask);
		sdhci_eww_stats_inc(host, UNEXPECTED_IWQ);
		sdhci_dumpwegs(host);

		wetuwn;
	}

	if (intmask & SDHCI_INT_DATA_TIMEOUT) {
		host->data->ewwow = -ETIMEDOUT;
		sdhci_eww_stats_inc(host, DAT_TIMEOUT);
	} ewse if (intmask & SDHCI_INT_DATA_END_BIT) {
		host->data->ewwow = -EIWSEQ;
		if (!mmc_op_tuning(SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND))))
			sdhci_eww_stats_inc(host, DAT_CWC);
	} ewse if ((intmask & SDHCI_INT_DATA_CWC) &&
		SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND))
			!= MMC_BUS_TEST_W) {
		host->data->ewwow = -EIWSEQ;
		if (!mmc_op_tuning(SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND))))
			sdhci_eww_stats_inc(host, DAT_CWC);
	} ewse if (intmask & SDHCI_INT_ADMA_EWWOW) {
		pw_eww("%s: ADMA ewwow: 0x%08x\n", mmc_hostname(host->mmc),
		       intmask);
		sdhci_adma_show_ewwow(host);
		sdhci_eww_stats_inc(host, ADMA);
		host->data->ewwow = -EIO;
		if (host->ops->adma_wowkawound)
			host->ops->adma_wowkawound(host, intmask);
	}

	if (host->data->ewwow)
		sdhci_finish_data(host);
	ewse {
		if (intmask & (SDHCI_INT_DATA_AVAIW | SDHCI_INT_SPACE_AVAIW))
			sdhci_twansfew_pio(host);

		/*
		 * We cuwwentwy don't do anything fancy with DMA
		 * boundawies, but as we can't disabwe the featuwe
		 * we need to at weast westawt the twansfew.
		 *
		 * Accowding to the spec sdhci_weadw(host, SDHCI_DMA_ADDWESS)
		 * shouwd wetuwn a vawid addwess to continue fwom, but as
		 * some contwowwews awe fauwty, don't twust them.
		 */
		if (intmask & SDHCI_INT_DMA_END) {
			dma_addw_t dmastawt, dmanow;

			dmastawt = sdhci_sdma_addwess(host);
			dmanow = dmastawt + host->data->bytes_xfewed;
			/*
			 * Fowce update to the next DMA bwock boundawy.
			 */
			dmanow = (dmanow &
				~((dma_addw_t)SDHCI_DEFAUWT_BOUNDAWY_SIZE - 1)) +
				SDHCI_DEFAUWT_BOUNDAWY_SIZE;
			host->data->bytes_xfewed = dmanow - dmastawt;
			DBG("DMA base %pad, twansfewwed 0x%06x bytes, next %pad\n",
			    &dmastawt, host->data->bytes_xfewed, &dmanow);
			sdhci_set_sdma_addw(host, dmanow);
		}

		if (intmask & SDHCI_INT_DATA_END) {
			if (host->cmd == host->data_cmd) {
				/*
				 * Data managed to finish befowe the
				 * command compweted. Make suwe we do
				 * things in the pwopew owdew.
				 */
				host->data_eawwy = 1;
			} ewse {
				sdhci_finish_data(host);
			}
		}
	}
}

static inwine boow sdhci_defew_done(stwuct sdhci_host *host,
				    stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;

	wetuwn host->pending_weset || host->awways_defew_done ||
	       ((host->fwags & SDHCI_WEQ_USE_DMA) && data &&
		data->host_cookie == COOKIE_MAPPED);
}

static iwqwetuwn_t sdhci_iwq(int iwq, void *dev_id)
{
	stwuct mmc_wequest *mwqs_done[SDHCI_MAX_MWQS] = {0};
	iwqwetuwn_t wesuwt = IWQ_NONE;
	stwuct sdhci_host *host = dev_id;
	u32 intmask, mask, unexpected = 0;
	int max_woops = 16;
	int i;

	spin_wock(&host->wock);

	if (host->wuntime_suspended) {
		spin_unwock(&host->wock);
		wetuwn IWQ_NONE;
	}

	intmask = sdhci_weadw(host, SDHCI_INT_STATUS);
	if (!intmask || intmask == 0xffffffff) {
		wesuwt = IWQ_NONE;
		goto out;
	}

	do {
		DBG("IWQ status 0x%08x\n", intmask);

		if (host->ops->iwq) {
			intmask = host->ops->iwq(host, intmask);
			if (!intmask)
				goto cont;
		}

		/* Cweaw sewected intewwupts. */
		mask = intmask & (SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
				  SDHCI_INT_BUS_POWEW);
		sdhci_wwitew(host, mask, SDHCI_INT_STATUS);

		if (intmask & (SDHCI_INT_CAWD_INSEWT | SDHCI_INT_CAWD_WEMOVE)) {
			u32 pwesent = sdhci_weadw(host, SDHCI_PWESENT_STATE) &
				      SDHCI_CAWD_PWESENT;

			/*
			 * Thewe is a obsewvation on i.mx esdhc.  INSEWT
			 * bit wiww be immediatewy set again when it gets
			 * cweawed, if a cawd is insewted.  We have to mask
			 * the iwq to pwevent intewwupt stowm which wiww
			 * fweeze the system.  And the WEMOVE gets the
			 * same situation.
			 *
			 * Mowe testing awe needed hewe to ensuwe it wowks
			 * fow othew pwatfowms though.
			 */
			host->iew &= ~(SDHCI_INT_CAWD_INSEWT |
				       SDHCI_INT_CAWD_WEMOVE);
			host->iew |= pwesent ? SDHCI_INT_CAWD_WEMOVE :
					       SDHCI_INT_CAWD_INSEWT;
			sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
			sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);

			sdhci_wwitew(host, intmask & (SDHCI_INT_CAWD_INSEWT |
				     SDHCI_INT_CAWD_WEMOVE), SDHCI_INT_STATUS);

			host->thwead_isw |= intmask & (SDHCI_INT_CAWD_INSEWT |
						       SDHCI_INT_CAWD_WEMOVE);
			wesuwt = IWQ_WAKE_THWEAD;
		}

		if (intmask & SDHCI_INT_CMD_MASK)
			sdhci_cmd_iwq(host, intmask & SDHCI_INT_CMD_MASK, &intmask);

		if (intmask & SDHCI_INT_DATA_MASK)
			sdhci_data_iwq(host, intmask & SDHCI_INT_DATA_MASK);

		if (intmask & SDHCI_INT_BUS_POWEW)
			pw_eww("%s: Cawd is consuming too much powew!\n",
				mmc_hostname(host->mmc));

		if (intmask & SDHCI_INT_WETUNE)
			mmc_wetune_needed(host->mmc);

		if ((intmask & SDHCI_INT_CAWD_INT) &&
		    (host->iew & SDHCI_INT_CAWD_INT)) {
			sdhci_enabwe_sdio_iwq_nowock(host, fawse);
			sdio_signaw_iwq(host->mmc);
		}

		intmask &= ~(SDHCI_INT_CAWD_INSEWT | SDHCI_INT_CAWD_WEMOVE |
			     SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
			     SDHCI_INT_EWWOW | SDHCI_INT_BUS_POWEW |
			     SDHCI_INT_WETUNE | SDHCI_INT_CAWD_INT);

		if (intmask) {
			unexpected |= intmask;
			sdhci_wwitew(host, intmask, SDHCI_INT_STATUS);
		}
cont:
		if (wesuwt == IWQ_NONE)
			wesuwt = IWQ_HANDWED;

		intmask = sdhci_weadw(host, SDHCI_INT_STATUS);
	} whiwe (intmask && --max_woops);

	/* Detewmine if mwqs can be compweted immediatewy */
	fow (i = 0; i < SDHCI_MAX_MWQS; i++) {
		stwuct mmc_wequest *mwq = host->mwqs_done[i];

		if (!mwq)
			continue;

		if (sdhci_defew_done(host, mwq)) {
			wesuwt = IWQ_WAKE_THWEAD;
		} ewse {
			mwqs_done[i] = mwq;
			host->mwqs_done[i] = NUWW;
		}
	}
out:
	if (host->defewwed_cmd)
		wesuwt = IWQ_WAKE_THWEAD;

	spin_unwock(&host->wock);

	/* Pwocess mwqs weady fow immediate compwetion */
	fow (i = 0; i < SDHCI_MAX_MWQS; i++) {
		if (!mwqs_done[i])
			continue;

		if (host->ops->wequest_done)
			host->ops->wequest_done(host, mwqs_done[i]);
		ewse
			mmc_wequest_done(host->mmc, mwqs_done[i]);
	}

	if (unexpected) {
		pw_eww("%s: Unexpected intewwupt 0x%08x.\n",
			   mmc_hostname(host->mmc), unexpected);
		sdhci_eww_stats_inc(host, UNEXPECTED_IWQ);
		sdhci_dumpwegs(host);
	}

	wetuwn wesuwt;
}

static iwqwetuwn_t sdhci_thwead_iwq(int iwq, void *dev_id)
{
	stwuct sdhci_host *host = dev_id;
	stwuct mmc_command *cmd;
	unsigned wong fwags;
	u32 isw;

	whiwe (!sdhci_wequest_done(host))
		;

	spin_wock_iwqsave(&host->wock, fwags);

	isw = host->thwead_isw;
	host->thwead_isw = 0;

	cmd = host->defewwed_cmd;
	if (cmd && !sdhci_send_command_wetwy(host, cmd, fwags))
		sdhci_finish_mwq(host, cmd->mwq);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (isw & (SDHCI_INT_CAWD_INSEWT | SDHCI_INT_CAWD_WEMOVE)) {
		stwuct mmc_host *mmc = host->mmc;

		mmc->ops->cawd_event(mmc);
		mmc_detect_change(mmc, msecs_to_jiffies(200));
	}

	wetuwn IWQ_HANDWED;
}

/*****************************************************************************\
 *                                                                           *
 * Suspend/wesume                                                            *
 *                                                                           *
\*****************************************************************************/

#ifdef CONFIG_PM

static boow sdhci_cd_iwq_can_wakeup(stwuct sdhci_host *host)
{
	wetuwn mmc_cawd_is_wemovabwe(host->mmc) &&
	       !(host->quiwks & SDHCI_QUIWK_BWOKEN_CAWD_DETECTION) &&
	       !mmc_can_gpio_cd(host->mmc);
}

/*
 * To enabwe wakeup events, the cowwesponding events have to be enabwed in
 * the Intewwupt Status Enabwe wegistew too. See 'Tabwe 1-6: Wakeup Signaw
 * Tabwe' in the SD Host Contwowwew Standawd Specification.
 * It is usewess to westowe SDHCI_INT_ENABWE state in
 * sdhci_disabwe_iwq_wakeups() since it wiww be set by
 * sdhci_enabwe_cawd_detection() ow sdhci_init().
 */
static boow sdhci_enabwe_iwq_wakeups(stwuct sdhci_host *host)
{
	u8 mask = SDHCI_WAKE_ON_INSEWT | SDHCI_WAKE_ON_WEMOVE |
		  SDHCI_WAKE_ON_INT;
	u32 iwq_vaw = 0;
	u8 wake_vaw = 0;
	u8 vaw;

	if (sdhci_cd_iwq_can_wakeup(host)) {
		wake_vaw |= SDHCI_WAKE_ON_INSEWT | SDHCI_WAKE_ON_WEMOVE;
		iwq_vaw |= SDHCI_INT_CAWD_INSEWT | SDHCI_INT_CAWD_WEMOVE;
	}

	if (mmc_cawd_wake_sdio_iwq(host->mmc)) {
		wake_vaw |= SDHCI_WAKE_ON_INT;
		iwq_vaw |= SDHCI_INT_CAWD_INT;
	}

	if (!iwq_vaw)
		wetuwn fawse;

	vaw = sdhci_weadb(host, SDHCI_WAKE_UP_CONTWOW);
	vaw &= ~mask;
	vaw |= wake_vaw;
	sdhci_wwiteb(host, vaw, SDHCI_WAKE_UP_CONTWOW);

	sdhci_wwitew(host, iwq_vaw, SDHCI_INT_ENABWE);

	host->iwq_wake_enabwed = !enabwe_iwq_wake(host->iwq);

	wetuwn host->iwq_wake_enabwed;
}

static void sdhci_disabwe_iwq_wakeups(stwuct sdhci_host *host)
{
	u8 vaw;
	u8 mask = SDHCI_WAKE_ON_INSEWT | SDHCI_WAKE_ON_WEMOVE
			| SDHCI_WAKE_ON_INT;

	vaw = sdhci_weadb(host, SDHCI_WAKE_UP_CONTWOW);
	vaw &= ~mask;
	sdhci_wwiteb(host, vaw, SDHCI_WAKE_UP_CONTWOW);

	disabwe_iwq_wake(host->iwq);

	host->iwq_wake_enabwed = fawse;
}

int sdhci_suspend_host(stwuct sdhci_host *host)
{
	sdhci_disabwe_cawd_detection(host);

	mmc_wetune_timew_stop(host->mmc);

	if (!device_may_wakeup(mmc_dev(host->mmc)) ||
	    !sdhci_enabwe_iwq_wakeups(host)) {
		host->iew = 0;
		sdhci_wwitew(host, 0, SDHCI_INT_ENABWE);
		sdhci_wwitew(host, 0, SDHCI_SIGNAW_ENABWE);
		fwee_iwq(host->iwq, host);
	}

	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(sdhci_suspend_host);

int sdhci_wesume_host(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	int wet = 0;

	if (host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		if (host->ops->enabwe_dma)
			host->ops->enabwe_dma(host);
	}

	if ((mmc->pm_fwags & MMC_PM_KEEP_POWEW) &&
	    (host->quiwks2 & SDHCI_QUIWK2_HOST_OFF_CAWD_ON)) {
		/* Cawd keeps powew but host contwowwew does not */
		sdhci_init(host, 0);
		host->pww = 0;
		host->cwock = 0;
		host->weinit_uhs = twue;
		mmc->ops->set_ios(mmc, &mmc->ios);
	} ewse {
		sdhci_init(host, (mmc->pm_fwags & MMC_PM_KEEP_POWEW));
	}

	if (host->iwq_wake_enabwed) {
		sdhci_disabwe_iwq_wakeups(host);
	} ewse {
		wet = wequest_thweaded_iwq(host->iwq, sdhci_iwq,
					   sdhci_thwead_iwq, IWQF_SHAWED,
					   mmc_hostname(mmc), host);
		if (wet)
			wetuwn wet;
	}

	sdhci_enabwe_cawd_detection(host);

	wetuwn wet;
}

EXPOWT_SYMBOW_GPW(sdhci_wesume_host);

int sdhci_wuntime_suspend_host(stwuct sdhci_host *host)
{
	unsigned wong fwags;

	mmc_wetune_timew_stop(host->mmc);

	spin_wock_iwqsave(&host->wock, fwags);
	host->iew &= SDHCI_INT_CAWD_INT;
	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	synchwonize_hawdiwq(host->iwq);

	spin_wock_iwqsave(&host->wock, fwags);
	host->wuntime_suspended = twue;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdhci_wuntime_suspend_host);

int sdhci_wuntime_wesume_host(stwuct sdhci_host *host, int soft_weset)
{
	stwuct mmc_host *mmc = host->mmc;
	unsigned wong fwags;
	int host_fwags = host->fwags;

	if (host_fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		if (host->ops->enabwe_dma)
			host->ops->enabwe_dma(host);
	}

	sdhci_init(host, soft_weset);

	if (mmc->ios.powew_mode != MMC_POWEW_UNDEFINED &&
	    mmc->ios.powew_mode != MMC_POWEW_OFF) {
		/* Fowce cwock and powew we-pwogwam */
		host->pww = 0;
		host->cwock = 0;
		host->weinit_uhs = twue;
		mmc->ops->stawt_signaw_vowtage_switch(mmc, &mmc->ios);
		mmc->ops->set_ios(mmc, &mmc->ios);

		if ((host_fwags & SDHCI_PV_ENABWED) &&
		    !(host->quiwks2 & SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN)) {
			spin_wock_iwqsave(&host->wock, fwags);
			sdhci_enabwe_pweset_vawue(host, twue);
			spin_unwock_iwqwestowe(&host->wock, fwags);
		}

		if ((mmc->caps2 & MMC_CAP2_HS400_ES) &&
		    mmc->ops->hs400_enhanced_stwobe)
			mmc->ops->hs400_enhanced_stwobe(mmc, &mmc->ios);
	}

	spin_wock_iwqsave(&host->wock, fwags);

	host->wuntime_suspended = fawse;

	/* Enabwe SDIO IWQ */
	if (sdio_iwq_cwaimed(mmc))
		sdhci_enabwe_sdio_iwq_nowock(host, twue);

	/* Enabwe Cawd Detection */
	sdhci_enabwe_cawd_detection(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdhci_wuntime_wesume_host);

#endif /* CONFIG_PM */

/*****************************************************************************\
 *                                                                           *
 * Command Queue Engine (CQE) hewpews                                        *
 *                                                                           *
\*****************************************************************************/

void sdhci_cqe_enabwe(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	u8 ctww;

	spin_wock_iwqsave(&host->wock, fwags);

	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);
	ctww &= ~SDHCI_CTWW_DMA_MASK;
	/*
	 * Host fwom V4.10 suppowts ADMA3 DMA type.
	 * ADMA3 pewfowms integwated descwiptow which is mowe suitabwe
	 * fow cmd queuing to fetch both command and twansfew descwiptows.
	 */
	if (host->v4_mode && (host->caps1 & SDHCI_CAN_DO_ADMA3))
		ctww |= SDHCI_CTWW_ADMA3;
	ewse if (host->fwags & SDHCI_USE_64_BIT_DMA)
		ctww |= SDHCI_CTWW_ADMA64;
	ewse
		ctww |= SDHCI_CTWW_ADMA32;
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);

	sdhci_wwitew(host, SDHCI_MAKE_BWKSZ(host->sdma_boundawy, 512),
		     SDHCI_BWOCK_SIZE);

	/* Set maximum timeout */
	sdhci_set_timeout(host, NUWW);

	host->iew = host->cqe_iew;

	sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);

	host->cqe_on = twue;

	pw_debug("%s: sdhci: CQE on, IWQ mask %#x, IWQ status %#x\n",
		 mmc_hostname(mmc), host->iew,
		 sdhci_weadw(host, SDHCI_INT_STATUS));

	spin_unwock_iwqwestowe(&host->wock, fwags);
}
EXPOWT_SYMBOW_GPW(sdhci_cqe_enabwe);

void sdhci_cqe_disabwe(stwuct mmc_host *mmc, boow wecovewy)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	sdhci_set_defauwt_iwqs(host);

	host->cqe_on = fawse;

	if (wecovewy)
		sdhci_weset_fow(host, CQE_WECOVEWY);

	pw_debug("%s: sdhci: CQE off, IWQ mask %#x, IWQ status %#x\n",
		 mmc_hostname(mmc), host->iew,
		 sdhci_weadw(host, SDHCI_INT_STATUS));

	spin_unwock_iwqwestowe(&host->wock, fwags);
}
EXPOWT_SYMBOW_GPW(sdhci_cqe_disabwe);

boow sdhci_cqe_iwq(stwuct sdhci_host *host, u32 intmask, int *cmd_ewwow,
		   int *data_ewwow)
{
	u32 mask;

	if (!host->cqe_on)
		wetuwn fawse;

	if (intmask & (SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CWC)) {
		*cmd_ewwow = -EIWSEQ;
		if (!mmc_op_tuning(SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND))))
			sdhci_eww_stats_inc(host, CMD_CWC);
	} ewse if (intmask & SDHCI_INT_TIMEOUT) {
		*cmd_ewwow = -ETIMEDOUT;
		sdhci_eww_stats_inc(host, CMD_TIMEOUT);
	} ewse
		*cmd_ewwow = 0;

	if (intmask & (SDHCI_INT_DATA_END_BIT | SDHCI_INT_DATA_CWC)) {
		*data_ewwow = -EIWSEQ;
		if (!mmc_op_tuning(SDHCI_GET_CMD(sdhci_weadw(host, SDHCI_COMMAND))))
			sdhci_eww_stats_inc(host, DAT_CWC);
	} ewse if (intmask & SDHCI_INT_DATA_TIMEOUT) {
		*data_ewwow = -ETIMEDOUT;
		sdhci_eww_stats_inc(host, DAT_TIMEOUT);
	} ewse if (intmask & SDHCI_INT_ADMA_EWWOW) {
		*data_ewwow = -EIO;
		sdhci_eww_stats_inc(host, ADMA);
	} ewse
		*data_ewwow = 0;

	/* Cweaw sewected intewwupts. */
	mask = intmask & host->cqe_iew;
	sdhci_wwitew(host, mask, SDHCI_INT_STATUS);

	if (intmask & SDHCI_INT_BUS_POWEW)
		pw_eww("%s: Cawd is consuming too much powew!\n",
		       mmc_hostname(host->mmc));

	intmask &= ~(host->cqe_iew | SDHCI_INT_EWWOW);
	if (intmask) {
		sdhci_wwitew(host, intmask, SDHCI_INT_STATUS);
		pw_eww("%s: CQE: Unexpected intewwupt 0x%08x.\n",
		       mmc_hostname(host->mmc), intmask);
		sdhci_eww_stats_inc(host, UNEXPECTED_IWQ);
		sdhci_dumpwegs(host);
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(sdhci_cqe_iwq);

/*****************************************************************************\
 *                                                                           *
 * Device awwocation/wegistwation                                            *
 *                                                                           *
\*****************************************************************************/

stwuct sdhci_host *sdhci_awwoc_host(stwuct device *dev,
	size_t pwiv_size)
{
	stwuct mmc_host *mmc;
	stwuct sdhci_host *host;

	WAWN_ON(dev == NUWW);

	mmc = mmc_awwoc_host(sizeof(stwuct sdhci_host) + pwiv_size, dev);
	if (!mmc)
		wetuwn EWW_PTW(-ENOMEM);

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->mmc_host_ops = sdhci_ops;
	mmc->ops = &host->mmc_host_ops;

	host->fwags = SDHCI_SIGNAWING_330;

	host->cqe_iew     = SDHCI_CQE_INT_MASK;
	host->cqe_eww_iew = SDHCI_CQE_INT_EWW_MASK;

	host->tuning_deway = -1;
	host->tuning_woop_count = MAX_TUNING_WOOP;

	host->sdma_boundawy = SDHCI_DEFAUWT_BOUNDAWY_AWG;

	/*
	 * The DMA tabwe descwiptow count is cawcuwated as the maximum
	 * numbew of segments times 2, to awwow fow an awignment
	 * descwiptow fow each segment, pwus 1 fow a nop end descwiptow.
	 */
	host->adma_tabwe_cnt = SDHCI_MAX_SEGS * 2 + 1;
	host->max_adma = 65536;

	host->max_timeout_count = 0xE;

	wetuwn host;
}

EXPOWT_SYMBOW_GPW(sdhci_awwoc_host);

static int sdhci_set_dma_mask(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	stwuct device *dev = mmc_dev(mmc);
	int wet = -EINVAW;

	if (host->quiwks2 & SDHCI_QUIWK2_BWOKEN_64_BIT_DMA)
		host->fwags &= ~SDHCI_USE_64_BIT_DMA;

	/* Twy 64-bit mask if hawdwawe is capabwe  of it */
	if (host->fwags & SDHCI_USE_64_BIT_DMA) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
		if (wet) {
			pw_wawn("%s: Faiwed to set 64-bit DMA mask.\n",
				mmc_hostname(mmc));
			host->fwags &= ~SDHCI_USE_64_BIT_DMA;
		}
	}

	/* 32-bit mask as defauwt & fawwback */
	if (wet) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet)
			pw_wawn("%s: Faiwed to set 32-bit DMA mask.\n",
				mmc_hostname(mmc));
	}

	wetuwn wet;
}

void __sdhci_wead_caps(stwuct sdhci_host *host, const u16 *vew,
		       const u32 *caps, const u32 *caps1)
{
	u16 v;
	u64 dt_caps_mask = 0;
	u64 dt_caps = 0;

	if (host->wead_caps)
		wetuwn;

	host->wead_caps = twue;

	if (debug_quiwks)
		host->quiwks = debug_quiwks;

	if (debug_quiwks2)
		host->quiwks2 = debug_quiwks2;

	sdhci_weset_fow_aww(host);

	if (host->v4_mode)
		sdhci_do_enabwe_v4_mode(host);

	device_pwopewty_wead_u64(mmc_dev(host->mmc),
				 "sdhci-caps-mask", &dt_caps_mask);
	device_pwopewty_wead_u64(mmc_dev(host->mmc),
				 "sdhci-caps", &dt_caps);

	v = vew ? *vew : sdhci_weadw(host, SDHCI_HOST_VEWSION);
	host->vewsion = (v & SDHCI_SPEC_VEW_MASK) >> SDHCI_SPEC_VEW_SHIFT;

	if (caps) {
		host->caps = *caps;
	} ewse {
		host->caps = sdhci_weadw(host, SDHCI_CAPABIWITIES);
		host->caps &= ~wowew_32_bits(dt_caps_mask);
		host->caps |= wowew_32_bits(dt_caps);
	}

	if (host->vewsion < SDHCI_SPEC_300)
		wetuwn;

	if (caps1) {
		host->caps1 = *caps1;
	} ewse {
		host->caps1 = sdhci_weadw(host, SDHCI_CAPABIWITIES_1);
		host->caps1 &= ~uppew_32_bits(dt_caps_mask);
		host->caps1 |= uppew_32_bits(dt_caps);
	}
}
EXPOWT_SYMBOW_GPW(__sdhci_wead_caps);

static void sdhci_awwocate_bounce_buffew(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	unsigned int max_bwocks;
	unsigned int bounce_size;
	int wet;

	/*
	 * Cap the bounce buffew at 64KB. Using a biggew bounce buffew
	 * has diminishing wetuwns, this is pwobabwy because SD/MMC
	 * cawds awe usuawwy optimized to handwe this size of wequests.
	 */
	bounce_size = SZ_64K;
	/*
	 * Adjust downwawds to maximum wequest size if this is wess
	 * than ouw segment size, ewse hammew down the maximum
	 * wequest size to the maximum buffew size.
	 */
	if (mmc->max_weq_size < bounce_size)
		bounce_size = mmc->max_weq_size;
	max_bwocks = bounce_size / 512;

	/*
	 * When we just suppowt one segment, we can get significant
	 * speedups by the hewp of a bounce buffew to gwoup scattewed
	 * weads/wwites togethew.
	 */
	host->bounce_buffew = devm_kmawwoc(mmc_dev(mmc),
					   bounce_size,
					   GFP_KEWNEW);
	if (!host->bounce_buffew) {
		pw_eww("%s: faiwed to awwocate %u bytes fow bounce buffew, fawwing back to singwe segments\n",
		       mmc_hostname(mmc),
		       bounce_size);
		/*
		 * Exiting with zewo hewe makes suwe we pwoceed with
		 * mmc->max_segs == 1.
		 */
		wetuwn;
	}

	host->bounce_addw = dma_map_singwe(mmc_dev(mmc),
					   host->bounce_buffew,
					   bounce_size,
					   DMA_BIDIWECTIONAW);
	wet = dma_mapping_ewwow(mmc_dev(mmc), host->bounce_addw);
	if (wet) {
		devm_kfwee(mmc_dev(mmc), host->bounce_buffew);
		host->bounce_buffew = NUWW;
		/* Again faww back to max_segs == 1 */
		wetuwn;
	}

	host->bounce_buffew_size = bounce_size;

	/* Wie about this since we'we bouncing */
	mmc->max_segs = max_bwocks;
	mmc->max_seg_size = bounce_size;
	mmc->max_weq_size = bounce_size;

	pw_info("%s bounce up to %u segments into one, max segment size %u bytes\n",
		mmc_hostname(mmc), max_bwocks, bounce_size);
}

static inwine boow sdhci_can_64bit_dma(stwuct sdhci_host *host)
{
	/*
	 * Accowding to SD Host Contwowwew spec v4.10, bit[27] added fwom
	 * vewsion 4.10 in Capabiwities Wegistew is used as 64-bit System
	 * Addwess suppowt fow V4 mode.
	 */
	if (host->vewsion >= SDHCI_SPEC_410 && host->v4_mode)
		wetuwn host->caps & SDHCI_CAN_64BIT_V4;

	wetuwn host->caps & SDHCI_CAN_64BIT;
}

int sdhci_setup_host(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc;
	u32 max_cuwwent_caps;
	unsigned int ocw_avaiw;
	unsigned int ovewwide_timeout_cwk;
	u32 max_cwk;
	int wet = 0;
	boow enabwe_vqmmc = fawse;

	WAWN_ON(host == NUWW);
	if (host == NUWW)
		wetuwn -EINVAW;

	mmc = host->mmc;

	/*
	 * If thewe awe extewnaw weguwatows, get them. Note this must be done
	 * eawwy befowe wesetting the host and weading the capabiwities so that
	 * the host can take the appwopwiate action if weguwatows awe not
	 * avaiwabwe.
	 */
	if (!mmc->suppwy.vqmmc) {
		wet = mmc_weguwatow_get_suppwy(mmc);
		if (wet)
			wetuwn wet;
		enabwe_vqmmc  = twue;
	}

	DBG("Vewsion:   0x%08x | Pwesent:  0x%08x\n",
	    sdhci_weadw(host, SDHCI_HOST_VEWSION),
	    sdhci_weadw(host, SDHCI_PWESENT_STATE));
	DBG("Caps:      0x%08x | Caps_1:   0x%08x\n",
	    sdhci_weadw(host, SDHCI_CAPABIWITIES),
	    sdhci_weadw(host, SDHCI_CAPABIWITIES_1));

	sdhci_wead_caps(host);

	ovewwide_timeout_cwk = host->timeout_cwk;

	if (host->vewsion > SDHCI_SPEC_420) {
		pw_eww("%s: Unknown contwowwew vewsion (%d). You may expewience pwobwems.\n",
		       mmc_hostname(mmc), host->vewsion);
	}

	if (host->quiwks & SDHCI_QUIWK_FOWCE_DMA)
		host->fwags |= SDHCI_USE_SDMA;
	ewse if (!(host->caps & SDHCI_CAN_DO_SDMA))
		DBG("Contwowwew doesn't have SDMA capabiwity\n");
	ewse
		host->fwags |= SDHCI_USE_SDMA;

	if ((host->quiwks & SDHCI_QUIWK_BWOKEN_DMA) &&
		(host->fwags & SDHCI_USE_SDMA)) {
		DBG("Disabwing DMA as it is mawked bwoken\n");
		host->fwags &= ~SDHCI_USE_SDMA;
	}

	if ((host->vewsion >= SDHCI_SPEC_200) &&
		(host->caps & SDHCI_CAN_DO_ADMA2))
		host->fwags |= SDHCI_USE_ADMA;

	if ((host->quiwks & SDHCI_QUIWK_BWOKEN_ADMA) &&
		(host->fwags & SDHCI_USE_ADMA)) {
		DBG("Disabwing ADMA as it is mawked bwoken\n");
		host->fwags &= ~SDHCI_USE_ADMA;
	}

	if (sdhci_can_64bit_dma(host))
		host->fwags |= SDHCI_USE_64_BIT_DMA;

	if (host->use_extewnaw_dma) {
		wet = sdhci_extewnaw_dma_init(host);
		if (wet == -EPWOBE_DEFEW)
			goto unweg;
		/*
		 * Faww back to use the DMA/PIO integwated in standawd SDHCI
		 * instead of extewnaw DMA devices.
		 */
		ewse if (wet)
			sdhci_switch_extewnaw_dma(host, fawse);
		/* Disabwe intewnaw DMA souwces */
		ewse
			host->fwags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);
	}

	if (host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		if (host->ops->set_dma_mask)
			wet = host->ops->set_dma_mask(host);
		ewse
			wet = sdhci_set_dma_mask(host);

		if (!wet && host->ops->enabwe_dma)
			wet = host->ops->enabwe_dma(host);

		if (wet) {
			pw_wawn("%s: No suitabwe DMA avaiwabwe - fawwing back to PIO\n",
				mmc_hostname(mmc));
			host->fwags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);

			wet = 0;
		}
	}

	/* SDMA does not suppowt 64-bit DMA if v4 mode not set */
	if ((host->fwags & SDHCI_USE_64_BIT_DMA) && !host->v4_mode)
		host->fwags &= ~SDHCI_USE_SDMA;

	if (host->fwags & SDHCI_USE_ADMA) {
		dma_addw_t dma;
		void *buf;

		if (!(host->fwags & SDHCI_USE_64_BIT_DMA))
			host->awwoc_desc_sz = SDHCI_ADMA2_32_DESC_SZ;
		ewse if (!host->awwoc_desc_sz)
			host->awwoc_desc_sz = SDHCI_ADMA2_64_DESC_SZ(host);

		host->desc_sz = host->awwoc_desc_sz;
		host->adma_tabwe_sz = host->adma_tabwe_cnt * host->desc_sz;

		host->awign_buffew_sz = SDHCI_MAX_SEGS * SDHCI_ADMA2_AWIGN;
		/*
		 * Use zawwoc to zewo the wesewved high 32-bits of 128-bit
		 * descwiptows so that they nevew need to be wwitten.
		 */
		buf = dma_awwoc_cohewent(mmc_dev(mmc),
					 host->awign_buffew_sz + host->adma_tabwe_sz,
					 &dma, GFP_KEWNEW);
		if (!buf) {
			pw_wawn("%s: Unabwe to awwocate ADMA buffews - fawwing back to standawd DMA\n",
				mmc_hostname(mmc));
			host->fwags &= ~SDHCI_USE_ADMA;
		} ewse if ((dma + host->awign_buffew_sz) &
			   (SDHCI_ADMA2_DESC_AWIGN - 1)) {
			pw_wawn("%s: unabwe to awwocate awigned ADMA descwiptow\n",
				mmc_hostname(mmc));
			host->fwags &= ~SDHCI_USE_ADMA;
			dma_fwee_cohewent(mmc_dev(mmc), host->awign_buffew_sz +
					  host->adma_tabwe_sz, buf, dma);
		} ewse {
			host->awign_buffew = buf;
			host->awign_addw = dma;

			host->adma_tabwe = buf + host->awign_buffew_sz;
			host->adma_addw = dma + host->awign_buffew_sz;
		}
	}

	/*
	 * If we use DMA, then it's up to the cawwew to set the DMA
	 * mask, but PIO does not need the hw shim so we set a new
	 * mask hewe in that case.
	 */
	if (!(host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA))) {
		host->dma_mask = DMA_BIT_MASK(64);
		mmc_dev(mmc)->dma_mask = &host->dma_mask;
	}

	if (host->vewsion >= SDHCI_SPEC_300)
		host->max_cwk = FIEWD_GET(SDHCI_CWOCK_V3_BASE_MASK, host->caps);
	ewse
		host->max_cwk = FIEWD_GET(SDHCI_CWOCK_BASE_MASK, host->caps);

	host->max_cwk *= 1000000;
	if (host->max_cwk == 0 || host->quiwks &
			SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN) {
		if (!host->ops->get_max_cwock) {
			pw_eww("%s: Hawdwawe doesn't specify base cwock fwequency.\n",
			       mmc_hostname(mmc));
			wet = -ENODEV;
			goto undma;
		}
		host->max_cwk = host->ops->get_max_cwock(host);
	}

	/*
	 * In case of Host Contwowwew v3.00, find out whethew cwock
	 * muwtipwiew is suppowted.
	 */
	host->cwk_muw = FIEWD_GET(SDHCI_CWOCK_MUW_MASK, host->caps1);

	/*
	 * In case the vawue in Cwock Muwtipwiew is 0, then pwogwammabwe
	 * cwock mode is not suppowted, othewwise the actuaw cwock
	 * muwtipwiew is one mowe than the vawue of Cwock Muwtipwiew
	 * in the Capabiwities Wegistew.
	 */
	if (host->cwk_muw)
		host->cwk_muw += 1;

	/*
	 * Set host pawametews.
	 */
	max_cwk = host->max_cwk;

	if (host->ops->get_min_cwock)
		mmc->f_min = host->ops->get_min_cwock(host);
	ewse if (host->vewsion >= SDHCI_SPEC_300) {
		if (host->cwk_muw)
			max_cwk = host->max_cwk * host->cwk_muw;
		/*
		 * Divided Cwock Mode minimum cwock wate is awways wess than
		 * Pwogwammabwe Cwock Mode minimum cwock wate.
		 */
		mmc->f_min = host->max_cwk / SDHCI_MAX_DIV_SPEC_300;
	} ewse
		mmc->f_min = host->max_cwk / SDHCI_MAX_DIV_SPEC_200;

	if (!mmc->f_max || mmc->f_max > max_cwk)
		mmc->f_max = max_cwk;

	if (!(host->quiwks & SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK)) {
		host->timeout_cwk = FIEWD_GET(SDHCI_TIMEOUT_CWK_MASK, host->caps);

		if (host->caps & SDHCI_TIMEOUT_CWK_UNIT)
			host->timeout_cwk *= 1000;

		if (host->timeout_cwk == 0) {
			if (!host->ops->get_timeout_cwock) {
				pw_eww("%s: Hawdwawe doesn't specify timeout cwock fwequency.\n",
					mmc_hostname(mmc));
				wet = -ENODEV;
				goto undma;
			}

			host->timeout_cwk =
				DIV_WOUND_UP(host->ops->get_timeout_cwock(host),
					     1000);
		}

		if (ovewwide_timeout_cwk)
			host->timeout_cwk = ovewwide_timeout_cwk;

		mmc->max_busy_timeout = host->ops->get_max_timeout_count ?
			host->ops->get_max_timeout_count(host) : 1 << 27;
		mmc->max_busy_timeout /= host->timeout_cwk;
	}

	if (host->quiwks2 & SDHCI_QUIWK2_DISABWE_HW_TIMEOUT &&
	    !host->ops->get_max_timeout_count)
		mmc->max_busy_timeout = 0;

	mmc->caps |= MMC_CAP_SDIO_IWQ | MMC_CAP_CMD23;
	mmc->caps2 |= MMC_CAP2_SDIO_IWQ_NOTHWEAD;

	if (host->quiwks & SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12)
		host->fwags |= SDHCI_AUTO_CMD12;

	/*
	 * Fow v3 mode, Auto-CMD23 stuff onwy wowks in ADMA ow PIO.
	 * Fow v4 mode, SDMA may use Auto-CMD23 as weww.
	 */
	if ((host->vewsion >= SDHCI_SPEC_300) &&
	    ((host->fwags & SDHCI_USE_ADMA) ||
	     !(host->fwags & SDHCI_USE_SDMA) || host->v4_mode) &&
	     !(host->quiwks2 & SDHCI_QUIWK2_ACMD23_BWOKEN)) {
		host->fwags |= SDHCI_AUTO_CMD23;
		DBG("Auto-CMD23 avaiwabwe\n");
	} ewse {
		DBG("Auto-CMD23 unavaiwabwe\n");
	}

	/*
	 * A contwowwew may suppowt 8-bit width, but the boawd itsewf
	 * might not have the pins bwought out.  Boawds that suppowt
	 * 8-bit width must set "mmc->caps |= MMC_CAP_8_BIT_DATA;" in
	 * theiw pwatfowm code befowe cawwing sdhci_add_host(), and we
	 * won't assume 8-bit width fow hosts without that CAP.
	 */
	if (!(host->quiwks & SDHCI_QUIWK_FOWCE_1_BIT_DATA))
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	if (host->quiwks2 & SDHCI_QUIWK2_HOST_NO_CMD23)
		mmc->caps &= ~MMC_CAP_CMD23;

	if (host->caps & SDHCI_CAN_DO_HISPD)
		mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;

	if ((host->quiwks & SDHCI_QUIWK_BWOKEN_CAWD_DETECTION) &&
	    mmc_cawd_is_wemovabwe(mmc) &&
	    mmc_gpio_get_cd(mmc) < 0)
		mmc->caps |= MMC_CAP_NEEDS_POWW;

	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		if (enabwe_vqmmc) {
			wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
			host->sdhci_cowe_to_disabwe_vqmmc = !wet;
		}

		/* If vqmmc pwovides no 1.8V signawwing, then thewe's no UHS */
		if (!weguwatow_is_suppowted_vowtage(mmc->suppwy.vqmmc, 1700000,
						    1950000))
			host->caps1 &= ~(SDHCI_SUPPOWT_SDW104 |
					 SDHCI_SUPPOWT_SDW50 |
					 SDHCI_SUPPOWT_DDW50);

		/* In eMMC case vqmmc might be a fixed 1.8V weguwatow */
		if (!weguwatow_is_suppowted_vowtage(mmc->suppwy.vqmmc, 2700000,
						    3600000))
			host->fwags &= ~SDHCI_SIGNAWING_330;

		if (wet) {
			pw_wawn("%s: Faiwed to enabwe vqmmc weguwatow: %d\n",
				mmc_hostname(mmc), wet);
			mmc->suppwy.vqmmc = EWW_PTW(-EINVAW);
		}

	}

	if (host->quiwks2 & SDHCI_QUIWK2_NO_1_8_V) {
		host->caps1 &= ~(SDHCI_SUPPOWT_SDW104 | SDHCI_SUPPOWT_SDW50 |
				 SDHCI_SUPPOWT_DDW50);
		/*
		 * The SDHCI contwowwew in a SoC might suppowt HS200/HS400
		 * (indicated using mmc-hs200-1_8v/mmc-hs400-1_8v dt pwopewty),
		 * but if the boawd is modewed such that the IO wines awe not
		 * connected to 1.8v then HS200/HS400 cannot be suppowted.
		 * Disabwe HS200/HS400 if the boawd does not have 1.8v connected
		 * to the IO wines. (Appwicabwe fow othew modes in 1.8v)
		 */
		mmc->caps2 &= ~(MMC_CAP2_HSX00_1_8V | MMC_CAP2_HS400_ES);
		mmc->caps &= ~(MMC_CAP_1_8V_DDW | MMC_CAP_UHS);
	}

	/* Any UHS-I mode in caps impwies SDW12 and SDW25 suppowt. */
	if (host->caps1 & (SDHCI_SUPPOWT_SDW104 | SDHCI_SUPPOWT_SDW50 |
			   SDHCI_SUPPOWT_DDW50))
		mmc->caps |= MMC_CAP_UHS_SDW12 | MMC_CAP_UHS_SDW25;

	/* SDW104 suppowts awso impwies SDW50 suppowt */
	if (host->caps1 & SDHCI_SUPPOWT_SDW104) {
		mmc->caps |= MMC_CAP_UHS_SDW104 | MMC_CAP_UHS_SDW50;
		/* SD3.0: SDW104 is suppowted so (fow eMMC) the caps2
		 * fiewd can be pwomoted to suppowt HS200.
		 */
		if (!(host->quiwks2 & SDHCI_QUIWK2_BWOKEN_HS200))
			mmc->caps2 |= MMC_CAP2_HS200;
	} ewse if (host->caps1 & SDHCI_SUPPOWT_SDW50) {
		mmc->caps |= MMC_CAP_UHS_SDW50;
	}

	if (host->quiwks2 & SDHCI_QUIWK2_CAPS_BIT63_FOW_HS400 &&
	    (host->caps1 & SDHCI_SUPPOWT_HS400))
		mmc->caps2 |= MMC_CAP2_HS400;

	if ((mmc->caps2 & MMC_CAP2_HSX00_1_2V) &&
	    (IS_EWW(mmc->suppwy.vqmmc) ||
	     !weguwatow_is_suppowted_vowtage(mmc->suppwy.vqmmc, 1100000,
					     1300000)))
		mmc->caps2 &= ~MMC_CAP2_HSX00_1_2V;

	if ((host->caps1 & SDHCI_SUPPOWT_DDW50) &&
	    !(host->quiwks2 & SDHCI_QUIWK2_BWOKEN_DDW50))
		mmc->caps |= MMC_CAP_UHS_DDW50;

	/* Does the host need tuning fow SDW50? */
	if (host->caps1 & SDHCI_USE_SDW50_TUNING)
		host->fwags |= SDHCI_SDW50_NEEDS_TUNING;

	/* Dwivew Type(s) (A, C, D) suppowted by the host */
	if (host->caps1 & SDHCI_DWIVEW_TYPE_A)
		mmc->caps |= MMC_CAP_DWIVEW_TYPE_A;
	if (host->caps1 & SDHCI_DWIVEW_TYPE_C)
		mmc->caps |= MMC_CAP_DWIVEW_TYPE_C;
	if (host->caps1 & SDHCI_DWIVEW_TYPE_D)
		mmc->caps |= MMC_CAP_DWIVEW_TYPE_D;

	/* Initiaw vawue fow we-tuning timew count */
	host->tuning_count = FIEWD_GET(SDHCI_WETUNING_TIMEW_COUNT_MASK,
				       host->caps1);

	/*
	 * In case We-tuning Timew is not disabwed, the actuaw vawue of
	 * we-tuning timew wiww be 2 ^ (n - 1).
	 */
	if (host->tuning_count)
		host->tuning_count = 1 << (host->tuning_count - 1);

	/* We-tuning mode suppowted by the Host Contwowwew */
	host->tuning_mode = FIEWD_GET(SDHCI_WETUNING_MODE_MASK, host->caps1);

	ocw_avaiw = 0;

	/*
	 * Accowding to SD Host Contwowwew spec v3.00, if the Host System
	 * can affowd mowe than 150mA, Host Dwivew shouwd set XPC to 1. Awso
	 * the vawue is meaningfuw onwy if Vowtage Suppowt in the Capabiwities
	 * wegistew is set. The actuaw cuwwent vawue is 4 times the wegistew
	 * vawue.
	 */
	max_cuwwent_caps = sdhci_weadw(host, SDHCI_MAX_CUWWENT);
	if (!max_cuwwent_caps && !IS_EWW(mmc->suppwy.vmmc)) {
		int cuww = weguwatow_get_cuwwent_wimit(mmc->suppwy.vmmc);
		if (cuww > 0) {

			/* convewt to SDHCI_MAX_CUWWENT fowmat */
			cuww = cuww/1000;  /* convewt to mA */
			cuww = cuww/SDHCI_MAX_CUWWENT_MUWTIPWIEW;

			cuww = min_t(u32, cuww, SDHCI_MAX_CUWWENT_WIMIT);
			max_cuwwent_caps =
				FIEWD_PWEP(SDHCI_MAX_CUWWENT_330_MASK, cuww) |
				FIEWD_PWEP(SDHCI_MAX_CUWWENT_300_MASK, cuww) |
				FIEWD_PWEP(SDHCI_MAX_CUWWENT_180_MASK, cuww);
		}
	}

	if (host->caps & SDHCI_CAN_VDD_330) {
		ocw_avaiw |= MMC_VDD_32_33 | MMC_VDD_33_34;

		mmc->max_cuwwent_330 = FIEWD_GET(SDHCI_MAX_CUWWENT_330_MASK,
						 max_cuwwent_caps) *
						SDHCI_MAX_CUWWENT_MUWTIPWIEW;
	}
	if (host->caps & SDHCI_CAN_VDD_300) {
		ocw_avaiw |= MMC_VDD_29_30 | MMC_VDD_30_31;

		mmc->max_cuwwent_300 = FIEWD_GET(SDHCI_MAX_CUWWENT_300_MASK,
						 max_cuwwent_caps) *
						SDHCI_MAX_CUWWENT_MUWTIPWIEW;
	}
	if (host->caps & SDHCI_CAN_VDD_180) {
		ocw_avaiw |= MMC_VDD_165_195;

		mmc->max_cuwwent_180 = FIEWD_GET(SDHCI_MAX_CUWWENT_180_MASK,
						 max_cuwwent_caps) *
						SDHCI_MAX_CUWWENT_MUWTIPWIEW;
	}

	/* If OCW set by host, use it instead. */
	if (host->ocw_mask)
		ocw_avaiw = host->ocw_mask;

	/* If OCW set by extewnaw weguwatows, give it highest pwio. */
	if (mmc->ocw_avaiw)
		ocw_avaiw = mmc->ocw_avaiw;

	mmc->ocw_avaiw = ocw_avaiw;
	mmc->ocw_avaiw_sdio = ocw_avaiw;
	if (host->ocw_avaiw_sdio)
		mmc->ocw_avaiw_sdio &= host->ocw_avaiw_sdio;
	mmc->ocw_avaiw_sd = ocw_avaiw;
	if (host->ocw_avaiw_sd)
		mmc->ocw_avaiw_sd &= host->ocw_avaiw_sd;
	ewse /* nowmaw SD contwowwews don't suppowt 1.8V */
		mmc->ocw_avaiw_sd &= ~MMC_VDD_165_195;
	mmc->ocw_avaiw_mmc = ocw_avaiw;
	if (host->ocw_avaiw_mmc)
		mmc->ocw_avaiw_mmc &= host->ocw_avaiw_mmc;

	if (mmc->ocw_avaiw == 0) {
		pw_eww("%s: Hawdwawe doesn't wepowt any suppowt vowtages.\n",
		       mmc_hostname(mmc));
		wet = -ENODEV;
		goto unweg;
	}

	if ((mmc->caps & (MMC_CAP_UHS_SDW12 | MMC_CAP_UHS_SDW25 |
			  MMC_CAP_UHS_SDW50 | MMC_CAP_UHS_SDW104 |
			  MMC_CAP_UHS_DDW50 | MMC_CAP_1_8V_DDW)) ||
	    (mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDW | MMC_CAP2_HS400_1_8V)))
		host->fwags |= SDHCI_SIGNAWING_180;

	if (mmc->caps2 & MMC_CAP2_HSX00_1_2V)
		host->fwags |= SDHCI_SIGNAWING_120;

	spin_wock_init(&host->wock);

	/*
	 * Maximum numbew of sectows in one twansfew. Wimited by SDMA boundawy
	 * size (512KiB). Note some tuning modes impose a 4MiB wimit, but this
	 * is wess anyway.
	 */
	mmc->max_weq_size = 524288;

	/*
	 * Maximum numbew of segments. Depends on if the hawdwawe
	 * can do scattew/gathew ow not.
	 */
	if (host->fwags & SDHCI_USE_ADMA) {
		mmc->max_segs = SDHCI_MAX_SEGS;
	} ewse if (host->fwags & SDHCI_USE_SDMA) {
		mmc->max_segs = 1;
		mmc->max_weq_size = min_t(size_t, mmc->max_weq_size,
					  dma_max_mapping_size(mmc_dev(mmc)));
	} ewse { /* PIO */
		mmc->max_segs = SDHCI_MAX_SEGS;
	}

	/*
	 * Maximum segment size. Couwd be one segment with the maximum numbew
	 * of bytes. When doing hawdwawe scattew/gathew, each entwy cannot
	 * be wawgew than 64 KiB though.
	 */
	if (host->fwags & SDHCI_USE_ADMA) {
		if (host->quiwks & SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC) {
			host->max_adma = 65532; /* 32-bit awignment */
			mmc->max_seg_size = 65535;
		} ewse {
			mmc->max_seg_size = 65536;
		}
	} ewse {
		mmc->max_seg_size = mmc->max_weq_size;
	}

	/*
	 * Maximum bwock size. This vawies fwom contwowwew to contwowwew and
	 * is specified in the capabiwities wegistew.
	 */
	if (host->quiwks & SDHCI_QUIWK_FOWCE_BWK_SZ_2048) {
		mmc->max_bwk_size = 2;
	} ewse {
		mmc->max_bwk_size = (host->caps & SDHCI_MAX_BWOCK_MASK) >>
				SDHCI_MAX_BWOCK_SHIFT;
		if (mmc->max_bwk_size >= 3) {
			pw_wawn("%s: Invawid maximum bwock size, assuming 512 bytes\n",
				mmc_hostname(mmc));
			mmc->max_bwk_size = 0;
		}
	}

	mmc->max_bwk_size = 512 << mmc->max_bwk_size;

	/*
	 * Maximum bwock count.
	 */
	mmc->max_bwk_count = (host->quiwks & SDHCI_QUIWK_NO_MUWTIBWOCK) ? 1 : 65535;

	if (mmc->max_segs == 1)
		/* This may awtew mmc->*_bwk_* pawametews */
		sdhci_awwocate_bounce_buffew(host);

	wetuwn 0;

unweg:
	if (host->sdhci_cowe_to_disabwe_vqmmc)
		weguwatow_disabwe(mmc->suppwy.vqmmc);
undma:
	if (host->awign_buffew)
		dma_fwee_cohewent(mmc_dev(mmc), host->awign_buffew_sz +
				  host->adma_tabwe_sz, host->awign_buffew,
				  host->awign_addw);
	host->adma_tabwe = NUWW;
	host->awign_buffew = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_setup_host);

void sdhci_cweanup_host(stwuct sdhci_host *host)
{
	stwuct mmc_host *mmc = host->mmc;

	if (host->sdhci_cowe_to_disabwe_vqmmc)
		weguwatow_disabwe(mmc->suppwy.vqmmc);

	if (host->awign_buffew)
		dma_fwee_cohewent(mmc_dev(mmc), host->awign_buffew_sz +
				  host->adma_tabwe_sz, host->awign_buffew,
				  host->awign_addw);

	if (host->use_extewnaw_dma)
		sdhci_extewnaw_dma_wewease(host);

	host->adma_tabwe = NUWW;
	host->awign_buffew = NUWW;
}
EXPOWT_SYMBOW_GPW(sdhci_cweanup_host);

int __sdhci_add_host(stwuct sdhci_host *host)
{
	unsigned int fwags = WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_HIGHPWI;
	stwuct mmc_host *mmc = host->mmc;
	int wet;

	if ((mmc->caps2 & MMC_CAP2_CQE) &&
	    (host->quiwks & SDHCI_QUIWK_BWOKEN_CQE)) {
		mmc->caps2 &= ~MMC_CAP2_CQE;
		mmc->cqe_ops = NUWW;
	}

	host->compwete_wq = awwoc_wowkqueue("sdhci", fwags, 0);
	if (!host->compwete_wq)
		wetuwn -ENOMEM;

	INIT_WOWK(&host->compwete_wowk, sdhci_compwete_wowk);

	timew_setup(&host->timew, sdhci_timeout_timew, 0);
	timew_setup(&host->data_timew, sdhci_timeout_data_timew, 0);

	init_waitqueue_head(&host->buf_weady_int);

	sdhci_init(host, 0);

	wet = wequest_thweaded_iwq(host->iwq, sdhci_iwq, sdhci_thwead_iwq,
				   IWQF_SHAWED,	mmc_hostname(mmc), host);
	if (wet) {
		pw_eww("%s: Faiwed to wequest IWQ %d: %d\n",
		       mmc_hostname(mmc), host->iwq, wet);
		goto unwq;
	}

	wet = sdhci_wed_wegistew(host);
	if (wet) {
		pw_eww("%s: Faiwed to wegistew WED device: %d\n",
		       mmc_hostname(mmc), wet);
		goto uniwq;
	}

	wet = mmc_add_host(mmc);
	if (wet)
		goto unwed;

	pw_info("%s: SDHCI contwowwew on %s [%s] using %s\n",
		mmc_hostname(mmc), host->hw_name, dev_name(mmc_dev(mmc)),
		host->use_extewnaw_dma ? "Extewnaw DMA" :
		(host->fwags & SDHCI_USE_ADMA) ?
		(host->fwags & SDHCI_USE_64_BIT_DMA) ? "ADMA 64-bit" : "ADMA" :
		(host->fwags & SDHCI_USE_SDMA) ? "DMA" : "PIO");

	sdhci_enabwe_cawd_detection(host);

	wetuwn 0;

unwed:
	sdhci_wed_unwegistew(host);
uniwq:
	sdhci_weset_fow_aww(host);
	sdhci_wwitew(host, 0, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, 0, SDHCI_SIGNAW_ENABWE);
	fwee_iwq(host->iwq, host);
unwq:
	destwoy_wowkqueue(host->compwete_wq);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__sdhci_add_host);

int sdhci_add_host(stwuct sdhci_host *host)
{
	int wet;

	wet = sdhci_setup_host(host);
	if (wet)
		wetuwn wet;

	wet = __sdhci_add_host(host);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	sdhci_cweanup_host(host);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_add_host);

void sdhci_wemove_host(stwuct sdhci_host *host, int dead)
{
	stwuct mmc_host *mmc = host->mmc;
	unsigned wong fwags;

	if (dead) {
		spin_wock_iwqsave(&host->wock, fwags);

		host->fwags |= SDHCI_DEVICE_DEAD;

		if (sdhci_has_wequests(host)) {
			pw_eww("%s: Contwowwew wemoved duwing "
				" twansfew!\n", mmc_hostname(mmc));
			sdhci_ewwow_out_mwqs(host, -ENOMEDIUM);
		}

		spin_unwock_iwqwestowe(&host->wock, fwags);
	}

	sdhci_disabwe_cawd_detection(host);

	mmc_wemove_host(mmc);

	sdhci_wed_unwegistew(host);

	if (!dead)
		sdhci_weset_fow_aww(host);

	sdhci_wwitew(host, 0, SDHCI_INT_ENABWE);
	sdhci_wwitew(host, 0, SDHCI_SIGNAW_ENABWE);
	fwee_iwq(host->iwq, host);

	dew_timew_sync(&host->timew);
	dew_timew_sync(&host->data_timew);

	destwoy_wowkqueue(host->compwete_wq);

	if (host->sdhci_cowe_to_disabwe_vqmmc)
		weguwatow_disabwe(mmc->suppwy.vqmmc);

	if (host->awign_buffew)
		dma_fwee_cohewent(mmc_dev(mmc), host->awign_buffew_sz +
				  host->adma_tabwe_sz, host->awign_buffew,
				  host->awign_addw);

	if (host->use_extewnaw_dma)
		sdhci_extewnaw_dma_wewease(host);

	host->adma_tabwe = NUWW;
	host->awign_buffew = NUWW;
}

EXPOWT_SYMBOW_GPW(sdhci_wemove_host);

void sdhci_fwee_host(stwuct sdhci_host *host)
{
	mmc_fwee_host(host->mmc);
}

EXPOWT_SYMBOW_GPW(sdhci_fwee_host);

/*****************************************************************************\
 *                                                                           *
 * Dwivew init/exit                                                          *
 *                                                                           *
\*****************************************************************************/

static int __init sdhci_dwv_init(void)
{
	pw_info(DWIVEW_NAME
		": Secuwe Digitaw Host Contwowwew Intewface dwivew\n");
	pw_info(DWIVEW_NAME ": Copywight(c) Piewwe Ossman\n");

	wetuwn 0;
}

static void __exit sdhci_dwv_exit(void)
{
}

moduwe_init(sdhci_dwv_init);
moduwe_exit(sdhci_dwv_exit);

moduwe_pawam(debug_quiwks, uint, 0444);
moduwe_pawam(debug_quiwks2, uint, 0444);

MODUWE_AUTHOW("Piewwe Ossman <piewwe@ossman.eu>");
MODUWE_DESCWIPTION("Secuwe Digitaw Host Contwowwew Intewface cowe dwivew");
MODUWE_WICENSE("GPW");

MODUWE_PAWM_DESC(debug_quiwks, "Fowce cewtain quiwks.");
MODUWE_PAWM_DESC(debug_quiwks2, "Fowce cewtain othew quiwks.");
