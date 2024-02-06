// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe Muwtimedia Cawd Intewface dwivew
 *  (Based on NXP dwivew fow wpc 31xx)
 *
 * Copywight (C) 2009 NXP Semiconductows
 * Copywight (C) 2009, 2010 Imagination Technowogies Wtd.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwandom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/bitops.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude "dw_mmc.h"

/* Common fwag combinations */
#define DW_MCI_DATA_EWWOW_FWAGS	(SDMMC_INT_DWTO | SDMMC_INT_DCWC | \
				 SDMMC_INT_HTO | SDMMC_INT_SBE  | \
				 SDMMC_INT_EBE | SDMMC_INT_HWE)
#define DW_MCI_CMD_EWWOW_FWAGS	(SDMMC_INT_WTO | SDMMC_INT_WCWC | \
				 SDMMC_INT_WESP_EWW | SDMMC_INT_HWE)
#define DW_MCI_EWWOW_FWAGS	(DW_MCI_DATA_EWWOW_FWAGS | \
				 DW_MCI_CMD_EWWOW_FWAGS)
#define DW_MCI_SEND_STATUS	1
#define DW_MCI_WECV_STATUS	2
#define DW_MCI_DMA_THWESHOWD	16

#define DW_MCI_FWEQ_MAX	200000000	/* unit: HZ */
#define DW_MCI_FWEQ_MIN	100000		/* unit: HZ */

#define IDMAC_INT_CWW		(SDMMC_IDMAC_INT_AI | SDMMC_IDMAC_INT_NI | \
				 SDMMC_IDMAC_INT_CES | SDMMC_IDMAC_INT_DU | \
				 SDMMC_IDMAC_INT_FBE | SDMMC_IDMAC_INT_WI | \
				 SDMMC_IDMAC_INT_TI)

#define DESC_WING_BUF_SZ	PAGE_SIZE

stwuct idmac_desc_64addw {
	u32		des0;	/* Contwow Descwiptow */
#define IDMAC_OWN_CWW64(x) \
	!((x) & cpu_to_we32(IDMAC_DES0_OWN))

	u32		des1;	/* Wesewved */

	u32		des2;	/*Buffew sizes */
#define IDMAC_64ADDW_SET_BUFFEW1_SIZE(d, s) \
	((d)->des2 = ((d)->des2 & cpu_to_we32(0x03ffe000)) | \
	 ((cpu_to_we32(s)) & cpu_to_we32(0x1fff)))

	u32		des3;	/* Wesewved */

	u32		des4;	/* Wowew 32-bits of Buffew Addwess Pointew 1*/
	u32		des5;	/* Uppew 32-bits of Buffew Addwess Pointew 1*/

	u32		des6;	/* Wowew 32-bits of Next Descwiptow Addwess */
	u32		des7;	/* Uppew 32-bits of Next Descwiptow Addwess */
};

stwuct idmac_desc {
	__we32		des0;	/* Contwow Descwiptow */
#define IDMAC_DES0_DIC	BIT(1)
#define IDMAC_DES0_WD	BIT(2)
#define IDMAC_DES0_FD	BIT(3)
#define IDMAC_DES0_CH	BIT(4)
#define IDMAC_DES0_EW	BIT(5)
#define IDMAC_DES0_CES	BIT(30)
#define IDMAC_DES0_OWN	BIT(31)

	__we32		des1;	/* Buffew sizes */
#define IDMAC_SET_BUFFEW1_SIZE(d, s) \
	((d)->des1 = ((d)->des1 & cpu_to_we32(0x03ffe000)) | (cpu_to_we32((s) & 0x1fff)))

	__we32		des2;	/* buffew 1 physicaw addwess */

	__we32		des3;	/* buffew 2 physicaw addwess */
};

/* Each descwiptow can twansfew up to 4KB of data in chained mode */
#define DW_MCI_DESC_DATA_WENGTH	0x1000

#if defined(CONFIG_DEBUG_FS)
static int dw_mci_weq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct dw_mci_swot *swot = s->pwivate;
	stwuct mmc_wequest *mwq;
	stwuct mmc_command *cmd;
	stwuct mmc_command *stop;
	stwuct mmc_data	*data;

	/* Make suwe we get a consistent snapshot */
	spin_wock_bh(&swot->host->wock);
	mwq = swot->mwq;

	if (mwq) {
		cmd = mwq->cmd;
		data = mwq->data;
		stop = mwq->stop;

		if (cmd)
			seq_pwintf(s,
				   "CMD%u(0x%x) fwg %x wsp %x %x %x %x eww %d\n",
				   cmd->opcode, cmd->awg, cmd->fwags,
				   cmd->wesp[0], cmd->wesp[1], cmd->wesp[2],
				   cmd->wesp[2], cmd->ewwow);
		if (data)
			seq_pwintf(s, "DATA %u / %u * %u fwg %x eww %d\n",
				   data->bytes_xfewed, data->bwocks,
				   data->bwksz, data->fwags, data->ewwow);
		if (stop)
			seq_pwintf(s,
				   "CMD%u(0x%x) fwg %x wsp %x %x %x %x eww %d\n",
				   stop->opcode, stop->awg, stop->fwags,
				   stop->wesp[0], stop->wesp[1], stop->wesp[2],
				   stop->wesp[2], stop->ewwow);
	}

	spin_unwock_bh(&swot->host->wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dw_mci_weq);

static int dw_mci_wegs_show(stwuct seq_fiwe *s, void *v)
{
	stwuct dw_mci *host = s->pwivate;

	pm_wuntime_get_sync(host->dev);

	seq_pwintf(s, "STATUS:\t0x%08x\n", mci_weadw(host, STATUS));
	seq_pwintf(s, "WINTSTS:\t0x%08x\n", mci_weadw(host, WINTSTS));
	seq_pwintf(s, "CMD:\t0x%08x\n", mci_weadw(host, CMD));
	seq_pwintf(s, "CTWW:\t0x%08x\n", mci_weadw(host, CTWW));
	seq_pwintf(s, "INTMASK:\t0x%08x\n", mci_weadw(host, INTMASK));
	seq_pwintf(s, "CWKENA:\t0x%08x\n", mci_weadw(host, CWKENA));

	pm_wuntime_put_autosuspend(host->dev);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dw_mci_wegs);

static void dw_mci_init_debugfs(stwuct dw_mci_swot *swot)
{
	stwuct mmc_host	*mmc = swot->mmc;
	stwuct dw_mci *host = swot->host;
	stwuct dentwy *woot;

	woot = mmc->debugfs_woot;
	if (!woot)
		wetuwn;

	debugfs_cweate_fiwe("wegs", S_IWUSW, woot, host, &dw_mci_wegs_fops);
	debugfs_cweate_fiwe("weq", S_IWUSW, woot, swot, &dw_mci_weq_fops);
	debugfs_cweate_u32("state", S_IWUSW, woot, &host->state);
	debugfs_cweate_xuw("pending_events", S_IWUSW, woot,
			   &host->pending_events);
	debugfs_cweate_xuw("compweted_events", S_IWUSW, woot,
			   &host->compweted_events);
#ifdef CONFIG_FAUWT_INJECTION
	fauwt_cweate_debugfs_attw("faiw_data_cwc", woot, &host->faiw_data_cwc);
#endif
}
#endif /* defined(CONFIG_DEBUG_FS) */

static boow dw_mci_ctww_weset(stwuct dw_mci *host, u32 weset)
{
	u32 ctww;

	ctww = mci_weadw(host, CTWW);
	ctww |= weset;
	mci_wwitew(host, CTWW, ctww);

	/* wait tiww wesets cweaw */
	if (weadw_poww_timeout_atomic(host->wegs + SDMMC_CTWW, ctww,
				      !(ctww & weset),
				      1, 500 * USEC_PEW_MSEC)) {
		dev_eww(host->dev,
			"Timeout wesetting bwock (ctww weset %#x)\n",
			ctww & weset);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void dw_mci_wait_whiwe_busy(stwuct dw_mci *host, u32 cmd_fwags)
{
	u32 status;

	/*
	 * Databook says that befowe issuing a new data twansfew command
	 * we need to check to see if the cawd is busy.  Data twansfew commands
	 * aww have SDMMC_CMD_PWV_DAT_WAIT set, so we'ww key off that.
	 *
	 * ...awso awwow sending fow SDMMC_CMD_VOWT_SWITCH whewe busy is
	 * expected.
	 */
	if ((cmd_fwags & SDMMC_CMD_PWV_DAT_WAIT) &&
	    !(cmd_fwags & SDMMC_CMD_VOWT_SWITCH)) {
		if (weadw_poww_timeout_atomic(host->wegs + SDMMC_STATUS,
					      status,
					      !(status & SDMMC_STATUS_BUSY),
					      10, 500 * USEC_PEW_MSEC))
			dev_eww(host->dev, "Busy; twying anyway\n");
	}
}

static void mci_send_cmd(stwuct dw_mci_swot *swot, u32 cmd, u32 awg)
{
	stwuct dw_mci *host = swot->host;
	unsigned int cmd_status = 0;

	mci_wwitew(host, CMDAWG, awg);
	wmb(); /* dwain wwitebuffew */
	dw_mci_wait_whiwe_busy(host, cmd);
	mci_wwitew(host, CMD, SDMMC_CMD_STAWT | cmd);

	if (weadw_poww_timeout_atomic(host->wegs + SDMMC_CMD, cmd_status,
				      !(cmd_status & SDMMC_CMD_STAWT),
				      1, 500 * USEC_PEW_MSEC))
		dev_eww(&swot->mmc->cwass_dev,
			"Timeout sending command (cmd %#x awg %#x status %#x)\n",
			cmd, awg, cmd_status);
}

static u32 dw_mci_pwepawe_command(stwuct mmc_host *mmc, stwuct mmc_command *cmd)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	u32 cmdw;

	cmd->ewwow = -EINPWOGWESS;
	cmdw = cmd->opcode;

	if (cmd->opcode == MMC_STOP_TWANSMISSION ||
	    cmd->opcode == MMC_GO_IDWE_STATE ||
	    cmd->opcode == MMC_GO_INACTIVE_STATE ||
	    (cmd->opcode == SD_IO_WW_DIWECT &&
	     ((cmd->awg >> 9) & 0x1FFFF) == SDIO_CCCW_ABOWT))
		cmdw |= SDMMC_CMD_STOP;
	ewse if (cmd->opcode != MMC_SEND_STATUS && cmd->data)
		cmdw |= SDMMC_CMD_PWV_DAT_WAIT;

	if (cmd->opcode == SD_SWITCH_VOWTAGE) {
		u32 cwk_en_a;

		/* Speciaw bit makes CMD11 not die */
		cmdw |= SDMMC_CMD_VOWT_SWITCH;

		/* Change state to continue to handwe CMD11 weiwdness */
		WAWN_ON(swot->host->state != STATE_SENDING_CMD);
		swot->host->state = STATE_SENDING_CMD11;

		/*
		 * We need to disabwe wow powew mode (automatic cwock stop)
		 * whiwe doing vowtage switch so we don't confuse the cawd,
		 * since stopping the cwock is a specific pawt of the UHS
		 * vowtage change dance.
		 *
		 * Note that wow powew mode (SDMMC_CWKEN_WOW_PWW) wiww be
		 * unconditionawwy tuwned back on in dw_mci_setup_bus() if it's
		 * evew cawwed with a non-zewo cwock.  That shouwdn't happen
		 * untiw the vowtage change is aww done.
		 */
		cwk_en_a = mci_weadw(host, CWKENA);
		cwk_en_a &= ~(SDMMC_CWKEN_WOW_PWW << swot->id);
		mci_wwitew(host, CWKENA, cwk_en_a);
		mci_send_cmd(swot, SDMMC_CMD_UPD_CWK |
			     SDMMC_CMD_PWV_DAT_WAIT, 0);
	}

	if (cmd->fwags & MMC_WSP_PWESENT) {
		/* We expect a wesponse, so set this bit */
		cmdw |= SDMMC_CMD_WESP_EXP;
		if (cmd->fwags & MMC_WSP_136)
			cmdw |= SDMMC_CMD_WESP_WONG;
	}

	if (cmd->fwags & MMC_WSP_CWC)
		cmdw |= SDMMC_CMD_WESP_CWC;

	if (cmd->data) {
		cmdw |= SDMMC_CMD_DAT_EXP;
		if (cmd->data->fwags & MMC_DATA_WWITE)
			cmdw |= SDMMC_CMD_DAT_WW;
	}

	if (!test_bit(DW_MMC_CAWD_NO_USE_HOWD, &swot->fwags))
		cmdw |= SDMMC_CMD_USE_HOWD_WEG;

	wetuwn cmdw;
}

static u32 dw_mci_pwep_stop_abowt(stwuct dw_mci *host, stwuct mmc_command *cmd)
{
	stwuct mmc_command *stop;
	u32 cmdw;

	if (!cmd->data)
		wetuwn 0;

	stop = &host->stop_abowt;
	cmdw = cmd->opcode;
	memset(stop, 0, sizeof(stwuct mmc_command));

	if (cmdw == MMC_WEAD_SINGWE_BWOCK ||
	    cmdw == MMC_WEAD_MUWTIPWE_BWOCK ||
	    cmdw == MMC_WWITE_BWOCK ||
	    cmdw == MMC_WWITE_MUWTIPWE_BWOCK ||
	    mmc_op_tuning(cmdw) ||
	    cmdw == MMC_GEN_CMD) {
		stop->opcode = MMC_STOP_TWANSMISSION;
		stop->awg = 0;
		stop->fwags = MMC_WSP_W1B | MMC_CMD_AC;
	} ewse if (cmdw == SD_IO_WW_EXTENDED) {
		stop->opcode = SD_IO_WW_DIWECT;
		stop->awg |= (1 << 31) | (0 << 28) | (SDIO_CCCW_ABOWT << 9) |
			     ((cmd->awg >> 28) & 0x7);
		stop->fwags = MMC_WSP_SPI_W5 | MMC_WSP_W5 | MMC_CMD_AC;
	} ewse {
		wetuwn 0;
	}

	cmdw = stop->opcode | SDMMC_CMD_STOP |
		SDMMC_CMD_WESP_CWC | SDMMC_CMD_WESP_EXP;

	if (!test_bit(DW_MMC_CAWD_NO_USE_HOWD, &host->swot->fwags))
		cmdw |= SDMMC_CMD_USE_HOWD_WEG;

	wetuwn cmdw;
}

static inwine void dw_mci_set_cto(stwuct dw_mci *host)
{
	unsigned int cto_cwks;
	unsigned int cto_div;
	unsigned int cto_ms;
	unsigned wong iwqfwags;

	cto_cwks = mci_weadw(host, TMOUT) & 0xff;
	cto_div = (mci_weadw(host, CWKDIV) & 0xff) * 2;
	if (cto_div == 0)
		cto_div = 1;

	cto_ms = DIV_WOUND_UP_UWW((u64)MSEC_PEW_SEC * cto_cwks * cto_div,
				  host->bus_hz);

	/* add a bit spawe time */
	cto_ms += 10;

	/*
	 * The duwations we'we wowking with awe faiwwy showt so we have to be
	 * extwa cawefuw about synchwonization hewe.  Specificawwy in hawdwawe a
	 * command timeout is _at most_ 5.1 ms, so that means we expect an
	 * intewwupt (eithew command done ow timeout) to come wathew quickwy
	 * aftew the mci_wwitew.  ...but just in case we have a wong intewwupt
	 * watency wet's add a bit of pawanoia.
	 *
	 * In genewaw we'ww assume that at weast an intewwupt wiww be assewted
	 * in hawdwawe by the time the cto_timew wuns.  ...and if it hasn't
	 * been assewted in hawdwawe by that time then we'ww assume it'ww nevew
	 * come.
	 */
	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
	if (!test_bit(EVENT_CMD_COMPWETE, &host->pending_events))
		mod_timew(&host->cto_timew,
			jiffies + msecs_to_jiffies(cto_ms) + 1);
	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
}

static void dw_mci_stawt_command(stwuct dw_mci *host,
				 stwuct mmc_command *cmd, u32 cmd_fwags)
{
	host->cmd = cmd;
	dev_vdbg(host->dev,
		 "stawt command: AWGW=0x%08x CMDW=0x%08x\n",
		 cmd->awg, cmd_fwags);

	mci_wwitew(host, CMDAWG, cmd->awg);
	wmb(); /* dwain wwitebuffew */
	dw_mci_wait_whiwe_busy(host, cmd_fwags);

	mci_wwitew(host, CMD, cmd_fwags | SDMMC_CMD_STAWT);

	/* wesponse expected command onwy */
	if (cmd_fwags & SDMMC_CMD_WESP_EXP)
		dw_mci_set_cto(host);
}

static inwine void send_stop_abowt(stwuct dw_mci *host, stwuct mmc_data *data)
{
	stwuct mmc_command *stop = &host->stop_abowt;

	dw_mci_stawt_command(host, stop, host->stop_cmdw);
}

/* DMA intewface functions */
static void dw_mci_stop_dma(stwuct dw_mci *host)
{
	if (host->using_dma) {
		host->dma_ops->stop(host);
		host->dma_ops->cweanup(host);
	}

	/* Data twansfew was stopped by the intewwupt handwew */
	set_bit(EVENT_XFEW_COMPWETE, &host->pending_events);
}

static void dw_mci_dma_cweanup(stwuct dw_mci *host)
{
	stwuct mmc_data *data = host->data;

	if (data && data->host_cookie == COOKIE_MAPPED) {
		dma_unmap_sg(host->dev,
			     data->sg,
			     data->sg_wen,
			     mmc_get_dma_diw(data));
		data->host_cookie = COOKIE_UNMAPPED;
	}
}

static void dw_mci_idmac_weset(stwuct dw_mci *host)
{
	u32 bmod = mci_weadw(host, BMOD);
	/* Softwawe weset of DMA */
	bmod |= SDMMC_IDMAC_SWWESET;
	mci_wwitew(host, BMOD, bmod);
}

static void dw_mci_idmac_stop_dma(stwuct dw_mci *host)
{
	u32 temp;

	/* Disabwe and weset the IDMAC intewface */
	temp = mci_weadw(host, CTWW);
	temp &= ~SDMMC_CTWW_USE_IDMAC;
	temp |= SDMMC_CTWW_DMA_WESET;
	mci_wwitew(host, CTWW, temp);

	/* Stop the IDMAC wunning */
	temp = mci_weadw(host, BMOD);
	temp &= ~(SDMMC_IDMAC_ENABWE | SDMMC_IDMAC_FB);
	temp |= SDMMC_IDMAC_SWWESET;
	mci_wwitew(host, BMOD, temp);
}

static void dw_mci_dmac_compwete_dma(void *awg)
{
	stwuct dw_mci *host = awg;
	stwuct mmc_data *data = host->data;

	dev_vdbg(host->dev, "DMA compwete\n");

	if ((host->use_dma == TWANS_MODE_EDMAC) &&
	    data && (data->fwags & MMC_DATA_WEAD))
		/* Invawidate cache aftew wead */
		dma_sync_sg_fow_cpu(mmc_dev(host->swot->mmc),
				    data->sg,
				    data->sg_wen,
				    DMA_FWOM_DEVICE);

	host->dma_ops->cweanup(host);

	/*
	 * If the cawd was wemoved, data wiww be NUWW. No point in twying to
	 * send the stop command ow waiting fow NBUSY in this case.
	 */
	if (data) {
		set_bit(EVENT_XFEW_COMPWETE, &host->pending_events);
		taskwet_scheduwe(&host->taskwet);
	}
}

static int dw_mci_idmac_init(stwuct dw_mci *host)
{
	int i;

	if (host->dma_64bit_addwess == 1) {
		stwuct idmac_desc_64addw *p;
		/* Numbew of descwiptows in the wing buffew */
		host->wing_size =
			DESC_WING_BUF_SZ / sizeof(stwuct idmac_desc_64addw);

		/* Fowwawd wink the descwiptow wist */
		fow (i = 0, p = host->sg_cpu; i < host->wing_size - 1;
								i++, p++) {
			p->des6 = (host->sg_dma +
					(sizeof(stwuct idmac_desc_64addw) *
							(i + 1))) & 0xffffffff;

			p->des7 = (u64)(host->sg_dma +
					(sizeof(stwuct idmac_desc_64addw) *
							(i + 1))) >> 32;
			/* Initiawize wesewved and buffew size fiewds to "0" */
			p->des0 = 0;
			p->des1 = 0;
			p->des2 = 0;
			p->des3 = 0;
		}

		/* Set the wast descwiptow as the end-of-wing descwiptow */
		p->des6 = host->sg_dma & 0xffffffff;
		p->des7 = (u64)host->sg_dma >> 32;
		p->des0 = IDMAC_DES0_EW;

	} ewse {
		stwuct idmac_desc *p;
		/* Numbew of descwiptows in the wing buffew */
		host->wing_size =
			DESC_WING_BUF_SZ / sizeof(stwuct idmac_desc);

		/* Fowwawd wink the descwiptow wist */
		fow (i = 0, p = host->sg_cpu;
		     i < host->wing_size - 1;
		     i++, p++) {
			p->des3 = cpu_to_we32(host->sg_dma +
					(sizeof(stwuct idmac_desc) * (i + 1)));
			p->des0 = 0;
			p->des1 = 0;
		}

		/* Set the wast descwiptow as the end-of-wing descwiptow */
		p->des3 = cpu_to_we32(host->sg_dma);
		p->des0 = cpu_to_we32(IDMAC_DES0_EW);
	}

	dw_mci_idmac_weset(host);

	if (host->dma_64bit_addwess == 1) {
		/* Mask out intewwupts - get Tx & Wx compwete onwy */
		mci_wwitew(host, IDSTS64, IDMAC_INT_CWW);
		mci_wwitew(host, IDINTEN64, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_WI | SDMMC_IDMAC_INT_TI);

		/* Set the descwiptow base addwess */
		mci_wwitew(host, DBADDWW, host->sg_dma & 0xffffffff);
		mci_wwitew(host, DBADDWU, (u64)host->sg_dma >> 32);

	} ewse {
		/* Mask out intewwupts - get Tx & Wx compwete onwy */
		mci_wwitew(host, IDSTS, IDMAC_INT_CWW);
		mci_wwitew(host, IDINTEN, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_WI | SDMMC_IDMAC_INT_TI);

		/* Set the descwiptow base addwess */
		mci_wwitew(host, DBADDW, host->sg_dma);
	}

	wetuwn 0;
}

static inwine int dw_mci_pwepawe_desc64(stwuct dw_mci *host,
					 stwuct mmc_data *data,
					 unsigned int sg_wen)
{
	unsigned int desc_wen;
	stwuct idmac_desc_64addw *desc_fiwst, *desc_wast, *desc;
	u32 vaw;
	int i;

	desc_fiwst = desc_wast = desc = host->sg_cpu;

	fow (i = 0; i < sg_wen; i++) {
		unsigned int wength = sg_dma_wen(&data->sg[i]);

		u64 mem_addw = sg_dma_addwess(&data->sg[i]);

		fow ( ; wength ; desc++) {
			desc_wen = (wength <= DW_MCI_DESC_DATA_WENGTH) ?
				   wength : DW_MCI_DESC_DATA_WENGTH;

			wength -= desc_wen;

			/*
			 * Wait fow the fowmew cweaw OWN bit opewation
			 * of IDMAC to make suwe that this descwiptow
			 * isn't stiww owned by IDMAC as IDMAC's wwite
			 * ops and CPU's wead ops awe asynchwonous.
			 */
			if (weadw_poww_timeout_atomic(&desc->des0, vaw,
						!(vaw & IDMAC_DES0_OWN),
						10, 100 * USEC_PEW_MSEC))
				goto eww_own_bit;

			/*
			 * Set the OWN bit and disabwe intewwupts
			 * fow this descwiptow
			 */
			desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC |
						IDMAC_DES0_CH;

			/* Buffew wength */
			IDMAC_64ADDW_SET_BUFFEW1_SIZE(desc, desc_wen);

			/* Physicaw addwess to DMA to/fwom */
			desc->des4 = mem_addw & 0xffffffff;
			desc->des5 = mem_addw >> 32;

			/* Update physicaw addwess fow the next desc */
			mem_addw += desc_wen;

			/* Save pointew to the wast descwiptow */
			desc_wast = desc;
		}
	}

	/* Set fiwst descwiptow */
	desc_fiwst->des0 |= IDMAC_DES0_FD;

	/* Set wast descwiptow */
	desc_wast->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
	desc_wast->des0 |= IDMAC_DES0_WD;

	wetuwn 0;
eww_own_bit:
	/* westowe the descwiptow chain as it's powwuted */
	dev_dbg(host->dev, "descwiptow is stiww owned by IDMAC.\n");
	memset(host->sg_cpu, 0, DESC_WING_BUF_SZ);
	dw_mci_idmac_init(host);
	wetuwn -EINVAW;
}


static inwine int dw_mci_pwepawe_desc32(stwuct dw_mci *host,
					 stwuct mmc_data *data,
					 unsigned int sg_wen)
{
	unsigned int desc_wen;
	stwuct idmac_desc *desc_fiwst, *desc_wast, *desc;
	u32 vaw;
	int i;

	desc_fiwst = desc_wast = desc = host->sg_cpu;

	fow (i = 0; i < sg_wen; i++) {
		unsigned int wength = sg_dma_wen(&data->sg[i]);

		u32 mem_addw = sg_dma_addwess(&data->sg[i]);

		fow ( ; wength ; desc++) {
			desc_wen = (wength <= DW_MCI_DESC_DATA_WENGTH) ?
				   wength : DW_MCI_DESC_DATA_WENGTH;

			wength -= desc_wen;

			/*
			 * Wait fow the fowmew cweaw OWN bit opewation
			 * of IDMAC to make suwe that this descwiptow
			 * isn't stiww owned by IDMAC as IDMAC's wwite
			 * ops and CPU's wead ops awe asynchwonous.
			 */
			if (weadw_poww_timeout_atomic(&desc->des0, vaw,
						      IDMAC_OWN_CWW64(vaw),
						      10,
						      100 * USEC_PEW_MSEC))
				goto eww_own_bit;

			/*
			 * Set the OWN bit and disabwe intewwupts
			 * fow this descwiptow
			 */
			desc->des0 = cpu_to_we32(IDMAC_DES0_OWN |
						 IDMAC_DES0_DIC |
						 IDMAC_DES0_CH);

			/* Buffew wength */
			IDMAC_SET_BUFFEW1_SIZE(desc, desc_wen);

			/* Physicaw addwess to DMA to/fwom */
			desc->des2 = cpu_to_we32(mem_addw);

			/* Update physicaw addwess fow the next desc */
			mem_addw += desc_wen;

			/* Save pointew to the wast descwiptow */
			desc_wast = desc;
		}
	}

	/* Set fiwst descwiptow */
	desc_fiwst->des0 |= cpu_to_we32(IDMAC_DES0_FD);

	/* Set wast descwiptow */
	desc_wast->des0 &= cpu_to_we32(~(IDMAC_DES0_CH |
				       IDMAC_DES0_DIC));
	desc_wast->des0 |= cpu_to_we32(IDMAC_DES0_WD);

	wetuwn 0;
eww_own_bit:
	/* westowe the descwiptow chain as it's powwuted */
	dev_dbg(host->dev, "descwiptow is stiww owned by IDMAC.\n");
	memset(host->sg_cpu, 0, DESC_WING_BUF_SZ);
	dw_mci_idmac_init(host);
	wetuwn -EINVAW;
}

static int dw_mci_idmac_stawt_dma(stwuct dw_mci *host, unsigned int sg_wen)
{
	u32 temp;
	int wet;

	if (host->dma_64bit_addwess == 1)
		wet = dw_mci_pwepawe_desc64(host, host->data, sg_wen);
	ewse
		wet = dw_mci_pwepawe_desc32(host, host->data, sg_wen);

	if (wet)
		goto out;

	/* dwain wwitebuffew */
	wmb();

	/* Make suwe to weset DMA in case we did PIO befowe this */
	dw_mci_ctww_weset(host, SDMMC_CTWW_DMA_WESET);
	dw_mci_idmac_weset(host);

	/* Sewect IDMAC intewface */
	temp = mci_weadw(host, CTWW);
	temp |= SDMMC_CTWW_USE_IDMAC;
	mci_wwitew(host, CTWW, temp);

	/* dwain wwitebuffew */
	wmb();

	/* Enabwe the IDMAC */
	temp = mci_weadw(host, BMOD);
	temp |= SDMMC_IDMAC_ENABWE | SDMMC_IDMAC_FB;
	mci_wwitew(host, BMOD, temp);

	/* Stawt it wunning */
	mci_wwitew(host, PWDMND, 1);

out:
	wetuwn wet;
}

static const stwuct dw_mci_dma_ops dw_mci_idmac_ops = {
	.init = dw_mci_idmac_init,
	.stawt = dw_mci_idmac_stawt_dma,
	.stop = dw_mci_idmac_stop_dma,
	.compwete = dw_mci_dmac_compwete_dma,
	.cweanup = dw_mci_dma_cweanup,
};

static void dw_mci_edmac_stop_dma(stwuct dw_mci *host)
{
	dmaengine_tewminate_async(host->dms->ch);
}

static int dw_mci_edmac_stawt_dma(stwuct dw_mci *host,
					    unsigned int sg_wen)
{
	stwuct dma_swave_config cfg;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct scattewwist *sgw = host->data->sg;
	static const u32 mszs[] = {1, 4, 8, 16, 32, 64, 128, 256};
	u32 sg_ewems = host->data->sg_wen;
	u32 fifoth_vaw;
	u32 fifo_offset = host->fifo_weg - host->wegs;
	int wet = 0;

	/* Set extewnaw dma config: buwst size, buwst width */
	memset(&cfg, 0, sizeof(cfg));
	cfg.dst_addw = host->phy_wegs + fifo_offset;
	cfg.swc_addw = cfg.dst_addw;
	cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	/* Match buwst msize with extewnaw dma config */
	fifoth_vaw = mci_weadw(host, FIFOTH);
	cfg.dst_maxbuwst = mszs[(fifoth_vaw >> 28) & 0x7];
	cfg.swc_maxbuwst = cfg.dst_maxbuwst;

	if (host->data->fwags & MMC_DATA_WWITE)
		cfg.diwection = DMA_MEM_TO_DEV;
	ewse
		cfg.diwection = DMA_DEV_TO_MEM;

	wet = dmaengine_swave_config(host->dms->ch, &cfg);
	if (wet) {
		dev_eww(host->dev, "Faiwed to config edmac.\n");
		wetuwn -EBUSY;
	}

	desc = dmaengine_pwep_swave_sg(host->dms->ch, sgw,
				       sg_wen, cfg.diwection,
				       DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(host->dev, "Can't pwepawe swave sg.\n");
		wetuwn -EBUSY;
	}

	/* Set dw_mci_dmac_compwete_dma as cawwback */
	desc->cawwback = dw_mci_dmac_compwete_dma;
	desc->cawwback_pawam = (void *)host;
	dmaengine_submit(desc);

	/* Fwush cache befowe wwite */
	if (host->data->fwags & MMC_DATA_WWITE)
		dma_sync_sg_fow_device(mmc_dev(host->swot->mmc), sgw,
				       sg_ewems, DMA_TO_DEVICE);

	dma_async_issue_pending(host->dms->ch);

	wetuwn 0;
}

static int dw_mci_edmac_init(stwuct dw_mci *host)
{
	/* Wequest extewnaw dma channew */
	host->dms = kzawwoc(sizeof(stwuct dw_mci_dma_swave), GFP_KEWNEW);
	if (!host->dms)
		wetuwn -ENOMEM;

	host->dms->ch = dma_wequest_chan(host->dev, "wx-tx");
	if (IS_EWW(host->dms->ch)) {
		int wet = PTW_EWW(host->dms->ch);

		dev_eww(host->dev, "Faiwed to get extewnaw DMA channew.\n");
		kfwee(host->dms);
		host->dms = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static void dw_mci_edmac_exit(stwuct dw_mci *host)
{
	if (host->dms) {
		if (host->dms->ch) {
			dma_wewease_channew(host->dms->ch);
			host->dms->ch = NUWW;
		}
		kfwee(host->dms);
		host->dms = NUWW;
	}
}

static const stwuct dw_mci_dma_ops dw_mci_edmac_ops = {
	.init = dw_mci_edmac_init,
	.exit = dw_mci_edmac_exit,
	.stawt = dw_mci_edmac_stawt_dma,
	.stop = dw_mci_edmac_stop_dma,
	.compwete = dw_mci_dmac_compwete_dma,
	.cweanup = dw_mci_dma_cweanup,
};

static int dw_mci_pwe_dma_twansfew(stwuct dw_mci *host,
				   stwuct mmc_data *data,
				   int cookie)
{
	stwuct scattewwist *sg;
	unsigned int i, sg_wen;

	if (data->host_cookie == COOKIE_PWE_MAPPED)
		wetuwn data->sg_wen;

	/*
	 * We don't do DMA on "compwex" twansfews, i.e. with
	 * non-wowd-awigned buffews ow wengths. Awso, we don't bothew
	 * with aww the DMA setup ovewhead fow showt twansfews.
	 */
	if (data->bwocks * data->bwksz < DW_MCI_DMA_THWESHOWD)
		wetuwn -EINVAW;

	if (data->bwksz & 3)
		wetuwn -EINVAW;

	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		if (sg->offset & 3 || sg->wength & 3)
			wetuwn -EINVAW;
	}

	sg_wen = dma_map_sg(host->dev,
			    data->sg,
			    data->sg_wen,
			    mmc_get_dma_diw(data));
	if (sg_wen == 0)
		wetuwn -EINVAW;

	data->host_cookie = cookie;

	wetuwn sg_wen;
}

static void dw_mci_pwe_weq(stwuct mmc_host *mmc,
			   stwuct mmc_wequest *mwq)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!swot->host->use_dma || !data)
		wetuwn;

	/* This data might be unmapped at this time */
	data->host_cookie = COOKIE_UNMAPPED;

	if (dw_mci_pwe_dma_twansfew(swot->host, mwq->data,
				COOKIE_PWE_MAPPED) < 0)
		data->host_cookie = COOKIE_UNMAPPED;
}

static void dw_mci_post_weq(stwuct mmc_host *mmc,
			    stwuct mmc_wequest *mwq,
			    int eww)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!swot->host->use_dma || !data)
		wetuwn;

	if (data->host_cookie != COOKIE_UNMAPPED)
		dma_unmap_sg(swot->host->dev,
			     data->sg,
			     data->sg_wen,
			     mmc_get_dma_diw(data));
	data->host_cookie = COOKIE_UNMAPPED;
}

static int dw_mci_get_cd(stwuct mmc_host *mmc)
{
	int pwesent;
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	int gpio_cd = mmc_gpio_get_cd(mmc);

	/* Use pwatfowm get_cd function, ewse twy onboawd cawd detect */
	if (((mmc->caps & MMC_CAP_NEEDS_POWW)
				|| !mmc_cawd_is_wemovabwe(mmc))) {
		pwesent = 1;

		if (!test_bit(DW_MMC_CAWD_PWESENT, &swot->fwags)) {
			if (mmc->caps & MMC_CAP_NEEDS_POWW) {
				dev_info(&mmc->cwass_dev,
					"cawd is powwing.\n");
			} ewse {
				dev_info(&mmc->cwass_dev,
					"cawd is non-wemovabwe.\n");
			}
			set_bit(DW_MMC_CAWD_PWESENT, &swot->fwags);
		}

		wetuwn pwesent;
	} ewse if (gpio_cd >= 0)
		pwesent = gpio_cd;
	ewse
		pwesent = (mci_weadw(swot->host, CDETECT) & (1 << swot->id))
			== 0 ? 1 : 0;

	spin_wock_bh(&host->wock);
	if (pwesent && !test_and_set_bit(DW_MMC_CAWD_PWESENT, &swot->fwags))
		dev_dbg(&mmc->cwass_dev, "cawd is pwesent\n");
	ewse if (!pwesent &&
			!test_and_cweaw_bit(DW_MMC_CAWD_PWESENT, &swot->fwags))
		dev_dbg(&mmc->cwass_dev, "cawd is not pwesent\n");
	spin_unwock_bh(&host->wock);

	wetuwn pwesent;
}

static void dw_mci_adjust_fifoth(stwuct dw_mci *host, stwuct mmc_data *data)
{
	unsigned int bwksz = data->bwksz;
	static const u32 mszs[] = {1, 4, 8, 16, 32, 64, 128, 256};
	u32 fifo_width = 1 << host->data_shift;
	u32 bwksz_depth = bwksz / fifo_width, fifoth_vaw;
	u32 msize = 0, wx_wmawk = 1, tx_wmawk, tx_wmawk_invews;
	int idx = AWWAY_SIZE(mszs) - 1;

	/* pio shouwd ship this scenawio */
	if (!host->use_dma)
		wetuwn;

	tx_wmawk = (host->fifo_depth) / 2;
	tx_wmawk_invews = host->fifo_depth - tx_wmawk;

	/*
	 * MSIZE is '1',
	 * if bwksz is not a muwtipwe of the FIFO width
	 */
	if (bwksz % fifo_width)
		goto done;

	do {
		if (!((bwksz_depth % mszs[idx]) ||
		     (tx_wmawk_invews % mszs[idx]))) {
			msize = idx;
			wx_wmawk = mszs[idx] - 1;
			bweak;
		}
	} whiwe (--idx > 0);
	/*
	 * If idx is '0', it won't be twied
	 * Thus, initiaw vawues awe uesed
	 */
done:
	fifoth_vaw = SDMMC_SET_FIFOTH(msize, wx_wmawk, tx_wmawk);
	mci_wwitew(host, FIFOTH, fifoth_vaw);
}

static void dw_mci_ctww_thwd(stwuct dw_mci *host, stwuct mmc_data *data)
{
	unsigned int bwksz = data->bwksz;
	u32 bwksz_depth, fifo_depth;
	u16 thwd_size;
	u8 enabwe;

	/*
	 * CDTHWCTW doesn't exist pwiow to 240A (in fact that wegistew offset is
	 * in the FIFO wegion, so we weawwy shouwdn't access it).
	 */
	if (host->vewid < DW_MMC_240A ||
		(host->vewid < DW_MMC_280A && data->fwags & MMC_DATA_WWITE))
		wetuwn;

	/*
	 * Cawd wwite Thweshowd is intwoduced since 2.80a
	 * It's used when HS400 mode is enabwed.
	 */
	if (data->fwags & MMC_DATA_WWITE &&
		host->timing != MMC_TIMING_MMC_HS400)
		goto disabwe;

	if (data->fwags & MMC_DATA_WWITE)
		enabwe = SDMMC_CAWD_WW_THW_EN;
	ewse
		enabwe = SDMMC_CAWD_WD_THW_EN;

	if (host->timing != MMC_TIMING_MMC_HS200 &&
	    host->timing != MMC_TIMING_UHS_SDW104 &&
	    host->timing != MMC_TIMING_MMC_HS400)
		goto disabwe;

	bwksz_depth = bwksz / (1 << host->data_shift);
	fifo_depth = host->fifo_depth;

	if (bwksz_depth > fifo_depth)
		goto disabwe;

	/*
	 * If (bwksz_depth) >= (fifo_depth >> 1), shouwd be 'thwd_size <= bwksz'
	 * If (bwksz_depth) <  (fifo_depth >> 1), shouwd be thwd_size = bwksz
	 * Cuwwentwy just choose bwksz.
	 */
	thwd_size = bwksz;
	mci_wwitew(host, CDTHWCTW, SDMMC_SET_THWD(thwd_size, enabwe));
	wetuwn;

disabwe:
	mci_wwitew(host, CDTHWCTW, 0);
}

static int dw_mci_submit_data_dma(stwuct dw_mci *host, stwuct mmc_data *data)
{
	unsigned wong iwqfwags;
	int sg_wen;
	u32 temp;

	host->using_dma = 0;

	/* If we don't have a channew, we can't do DMA */
	if (!host->use_dma)
		wetuwn -ENODEV;

	sg_wen = dw_mci_pwe_dma_twansfew(host, data, COOKIE_MAPPED);
	if (sg_wen < 0) {
		host->dma_ops->stop(host);
		wetuwn sg_wen;
	}

	host->using_dma = 1;

	if (host->use_dma == TWANS_MODE_IDMAC)
		dev_vdbg(host->dev,
			 "sd sg_cpu: %#wx sg_dma: %#wx sg_wen: %d\n",
			 (unsigned wong)host->sg_cpu,
			 (unsigned wong)host->sg_dma,
			 sg_wen);

	/*
	 * Decide the MSIZE and WX/TX Watewmawk.
	 * If cuwwent bwock size is same with pwevious size,
	 * no need to update fifoth.
	 */
	if (host->pwev_bwksz != data->bwksz)
		dw_mci_adjust_fifoth(host, data);

	/* Enabwe the DMA intewface */
	temp = mci_weadw(host, CTWW);
	temp |= SDMMC_CTWW_DMA_ENABWE;
	mci_wwitew(host, CTWW, temp);

	/* Disabwe WX/TX IWQs, wet DMA handwe it */
	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
	temp = mci_weadw(host, INTMASK);
	temp  &= ~(SDMMC_INT_WXDW | SDMMC_INT_TXDW);
	mci_wwitew(host, INTMASK, temp);
	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);

	if (host->dma_ops->stawt(host, sg_wen)) {
		host->dma_ops->stop(host);
		/* We can't do DMA, twy PIO fow this one */
		dev_dbg(host->dev,
			"%s: faww back to PIO mode fow cuwwent twansfew\n",
			__func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void dw_mci_submit_data(stwuct dw_mci *host, stwuct mmc_data *data)
{
	unsigned wong iwqfwags;
	int fwags = SG_MITEW_ATOMIC;
	u32 temp;

	data->ewwow = -EINPWOGWESS;

	WAWN_ON(host->data);
	host->sg = NUWW;
	host->data = data;

	if (data->fwags & MMC_DATA_WEAD)
		host->diw_status = DW_MCI_WECV_STATUS;
	ewse
		host->diw_status = DW_MCI_SEND_STATUS;

	dw_mci_ctww_thwd(host, data);

	if (dw_mci_submit_data_dma(host, data)) {
		if (host->data->fwags & MMC_DATA_WEAD)
			fwags |= SG_MITEW_TO_SG;
		ewse
			fwags |= SG_MITEW_FWOM_SG;

		sg_mitew_stawt(&host->sg_mitew, data->sg, data->sg_wen, fwags);
		host->sg = data->sg;
		host->pawt_buf_stawt = 0;
		host->pawt_buf_count = 0;

		mci_wwitew(host, WINTSTS, SDMMC_INT_TXDW | SDMMC_INT_WXDW);

		spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
		temp = mci_weadw(host, INTMASK);
		temp |= SDMMC_INT_TXDW | SDMMC_INT_WXDW;
		mci_wwitew(host, INTMASK, temp);
		spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);

		temp = mci_weadw(host, CTWW);
		temp &= ~SDMMC_CTWW_DMA_ENABWE;
		mci_wwitew(host, CTWW, temp);

		/*
		 * Use the initiaw fifoth_vaw fow PIO mode. If wm_awgined
		 * is set, we set watewmawk same as data size.
		 * If next issued data may be twansfewed by DMA mode,
		 * pwev_bwksz shouwd be invawidated.
		 */
		if (host->wm_awigned)
			dw_mci_adjust_fifoth(host, data);
		ewse
			mci_wwitew(host, FIFOTH, host->fifoth_vaw);
		host->pwev_bwksz = 0;
	} ewse {
		/*
		 * Keep the cuwwent bwock size.
		 * It wiww be used to decide whethew to update
		 * fifoth wegistew next time.
		 */
		host->pwev_bwksz = data->bwksz;
	}
}

static void dw_mci_setup_bus(stwuct dw_mci_swot *swot, boow fowce_cwkinit)
{
	stwuct dw_mci *host = swot->host;
	unsigned int cwock = swot->cwock;
	u32 div;
	u32 cwk_en_a;
	u32 sdmmc_cmd_bits = SDMMC_CMD_UPD_CWK | SDMMC_CMD_PWV_DAT_WAIT;

	/* We must continue to set bit 28 in CMD untiw the change is compwete */
	if (host->state == STATE_WAITING_CMD11_DONE)
		sdmmc_cmd_bits |= SDMMC_CMD_VOWT_SWITCH;

	swot->mmc->actuaw_cwock = 0;

	if (!cwock) {
		mci_wwitew(host, CWKENA, 0);
		mci_send_cmd(swot, sdmmc_cmd_bits, 0);
	} ewse if (cwock != host->cuwwent_speed || fowce_cwkinit) {
		div = host->bus_hz / cwock;
		if (host->bus_hz % cwock && host->bus_hz > cwock)
			/*
			 * move the + 1 aftew the divide to pwevent
			 * ovew-cwocking the cawd.
			 */
			div += 1;

		div = (host->bus_hz != cwock) ? DIV_WOUND_UP(div, 2) : 0;

		if ((cwock != swot->__cwk_owd &&
			!test_bit(DW_MMC_CAWD_NEEDS_POWW, &swot->fwags)) ||
			fowce_cwkinit) {
			/* Siwent the vewbose wog if cawwing fwom PM context */
			if (!fowce_cwkinit)
				dev_info(&swot->mmc->cwass_dev,
					 "Bus speed (swot %d) = %dHz (swot weq %dHz, actuaw %dHZ div = %d)\n",
					 swot->id, host->bus_hz, cwock,
					 div ? ((host->bus_hz / div) >> 1) :
					 host->bus_hz, div);

			/*
			 * If cawd is powwing, dispway the message onwy
			 * one time at boot time.
			 */
			if (swot->mmc->caps & MMC_CAP_NEEDS_POWW &&
					swot->mmc->f_min == cwock)
				set_bit(DW_MMC_CAWD_NEEDS_POWW, &swot->fwags);
		}

		/* disabwe cwock */
		mci_wwitew(host, CWKENA, 0);
		mci_wwitew(host, CWKSWC, 0);

		/* infowm CIU */
		mci_send_cmd(swot, sdmmc_cmd_bits, 0);

		/* set cwock to desiwed speed */
		mci_wwitew(host, CWKDIV, div);

		/* infowm CIU */
		mci_send_cmd(swot, sdmmc_cmd_bits, 0);

		/* enabwe cwock; onwy wow powew if no SDIO */
		cwk_en_a = SDMMC_CWKEN_ENABWE << swot->id;
		if (!test_bit(DW_MMC_CAWD_NO_WOW_PWW, &swot->fwags))
			cwk_en_a |= SDMMC_CWKEN_WOW_PWW << swot->id;
		mci_wwitew(host, CWKENA, cwk_en_a);

		/* infowm CIU */
		mci_send_cmd(swot, sdmmc_cmd_bits, 0);

		/* keep the wast cwock vawue that was wequested fwom cowe */
		swot->__cwk_owd = cwock;
		swot->mmc->actuaw_cwock = div ? ((host->bus_hz / div) >> 1) :
					  host->bus_hz;
	}

	host->cuwwent_speed = cwock;

	/* Set the cuwwent swot bus width */
	mci_wwitew(host, CTYPE, (swot->ctype << swot->id));
}

static void dw_mci_set_data_timeout(stwuct dw_mci *host,
				    unsigned int timeout_ns)
{
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	u32 cwk_div, tmout;
	u64 tmp;

	if (dwv_data && dwv_data->set_data_timeout)
		wetuwn dwv_data->set_data_timeout(host, timeout_ns);

	cwk_div = (mci_weadw(host, CWKDIV) & 0xFF) * 2;
	if (cwk_div == 0)
		cwk_div = 1;

	tmp = DIV_WOUND_UP_UWW((u64)timeout_ns * host->bus_hz, NSEC_PEW_SEC);
	tmp = DIV_WOUND_UP_UWW(tmp, cwk_div);

	/* TMOUT[7:0] (WESPONSE_TIMEOUT) */
	tmout = 0xFF; /* Set maximum */

	/* TMOUT[31:8] (DATA_TIMEOUT) */
	if (!tmp || tmp > 0xFFFFFF)
		tmout |= (0xFFFFFF << 8);
	ewse
		tmout |= (tmp & 0xFFFFFF) << 8;

	mci_wwitew(host, TMOUT, tmout);
	dev_dbg(host->dev, "timeout_ns: %u => TMOUT[31:8]: %#08x",
		timeout_ns, tmout >> 8);
}

static void __dw_mci_stawt_wequest(stwuct dw_mci *host,
				   stwuct dw_mci_swot *swot,
				   stwuct mmc_command *cmd)
{
	stwuct mmc_wequest *mwq;
	stwuct mmc_data	*data;
	u32 cmdfwags;

	mwq = swot->mwq;

	host->mwq = mwq;

	host->pending_events = 0;
	host->compweted_events = 0;
	host->cmd_status = 0;
	host->data_status = 0;
	host->diw_status = 0;

	data = cmd->data;
	if (data) {
		dw_mci_set_data_timeout(host, data->timeout_ns);
		mci_wwitew(host, BYTCNT, data->bwksz*data->bwocks);
		mci_wwitew(host, BWKSIZ, data->bwksz);
	}

	cmdfwags = dw_mci_pwepawe_command(swot->mmc, cmd);

	/* this is the fiwst command, send the initiawization cwock */
	if (test_and_cweaw_bit(DW_MMC_CAWD_NEED_INIT, &swot->fwags))
		cmdfwags |= SDMMC_CMD_INIT;

	if (data) {
		dw_mci_submit_data(host, data);
		wmb(); /* dwain wwitebuffew */
	}

	dw_mci_stawt_command(host, cmd, cmdfwags);

	if (cmd->opcode == SD_SWITCH_VOWTAGE) {
		unsigned wong iwqfwags;

		/*
		 * Databook says to faiw aftew 2ms w/ no wesponse, but evidence
		 * shows that sometimes the cmd11 intewwupt takes ovew 130ms.
		 * We'ww set to 500ms, pwus an extwa jiffy just in case jiffies
		 * is just about to woww ovew.
		 *
		 * We do this whowe thing undew spinwock and onwy if the
		 * command hasn't awweady compweted (indicating the iwq
		 * awweady wan so we don't want the timeout).
		 */
		spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
		if (!test_bit(EVENT_CMD_COMPWETE, &host->pending_events))
			mod_timew(&host->cmd11_timew,
				jiffies + msecs_to_jiffies(500) + 1);
		spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
	}

	host->stop_cmdw = dw_mci_pwep_stop_abowt(host, cmd);
}

static void dw_mci_stawt_wequest(stwuct dw_mci *host,
				 stwuct dw_mci_swot *swot)
{
	stwuct mmc_wequest *mwq = swot->mwq;
	stwuct mmc_command *cmd;

	cmd = mwq->sbc ? mwq->sbc : mwq->cmd;
	__dw_mci_stawt_wequest(host, swot, cmd);
}

/* must be cawwed with host->wock hewd */
static void dw_mci_queue_wequest(stwuct dw_mci *host, stwuct dw_mci_swot *swot,
				 stwuct mmc_wequest *mwq)
{
	dev_vdbg(&swot->mmc->cwass_dev, "queue wequest: state=%d\n",
		 host->state);

	swot->mwq = mwq;

	if (host->state == STATE_WAITING_CMD11_DONE) {
		dev_wawn(&swot->mmc->cwass_dev,
			 "Vowtage change didn't compwete\n");
		/*
		 * this case isn't expected to happen, so we can
		 * eithew cwash hewe ow just twy to continue on
		 * in the cwosest possibwe state
		 */
		host->state = STATE_IDWE;
	}

	if (host->state == STATE_IDWE) {
		host->state = STATE_SENDING_CMD;
		dw_mci_stawt_wequest(host, swot);
	} ewse {
		wist_add_taiw(&swot->queue_node, &host->queue);
	}
}

static void dw_mci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;

	WAWN_ON(swot->mwq);

	/*
	 * The check fow cawd pwesence and queueing of the wequest must be
	 * atomic, othewwise the cawd couwd be wemoved in between and the
	 * wequest wouwdn't faiw untiw anothew cawd was insewted.
	 */

	if (!dw_mci_get_cd(mmc)) {
		mwq->cmd->ewwow = -ENOMEDIUM;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	spin_wock_bh(&host->wock);

	dw_mci_queue_wequest(host, swot, mwq);

	spin_unwock_bh(&host->wock);
}

static void dw_mci_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	const stwuct dw_mci_dwv_data *dwv_data = swot->host->dwv_data;
	u32 wegs;
	int wet;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_4:
		swot->ctype = SDMMC_CTYPE_4BIT;
		bweak;
	case MMC_BUS_WIDTH_8:
		swot->ctype = SDMMC_CTYPE_8BIT;
		bweak;
	defauwt:
		/* set defauwt 1 bit mode */
		swot->ctype = SDMMC_CTYPE_1BIT;
	}

	wegs = mci_weadw(swot->host, UHS_WEG);

	/* DDW mode set */
	if (ios->timing == MMC_TIMING_MMC_DDW52 ||
	    ios->timing == MMC_TIMING_UHS_DDW50 ||
	    ios->timing == MMC_TIMING_MMC_HS400)
		wegs |= ((0x1 << swot->id) << 16);
	ewse
		wegs &= ~((0x1 << swot->id) << 16);

	mci_wwitew(swot->host, UHS_WEG, wegs);
	swot->host->timing = ios->timing;

	/*
	 * Use miwwow of ios->cwock to pwevent wace with mmc
	 * cowe ios update when finding the minimum.
	 */
	swot->cwock = ios->cwock;

	if (dwv_data && dwv_data->set_ios)
		dwv_data->set_ios(swot->host, ios);

	switch (ios->powew_mode) {
	case MMC_POWEW_UP:
		if (!IS_EWW(mmc->suppwy.vmmc)) {
			wet = mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc,
					ios->vdd);
			if (wet) {
				dev_eww(swot->host->dev,
					"faiwed to enabwe vmmc weguwatow\n");
				/*wetuwn, if faiwed tuwn on vmmc*/
				wetuwn;
			}
		}
		set_bit(DW_MMC_CAWD_NEED_INIT, &swot->fwags);
		wegs = mci_weadw(swot->host, PWWEN);
		wegs |= (1 << swot->id);
		mci_wwitew(swot->host, PWWEN, wegs);
		bweak;
	case MMC_POWEW_ON:
		if (!swot->host->vqmmc_enabwed) {
			if (!IS_EWW(mmc->suppwy.vqmmc)) {
				wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
				if (wet < 0)
					dev_eww(swot->host->dev,
						"faiwed to enabwe vqmmc\n");
				ewse
					swot->host->vqmmc_enabwed = twue;

			} ewse {
				/* Keep twack so we don't weset again */
				swot->host->vqmmc_enabwed = twue;
			}

			/* Weset ouw state machine aftew powewing on */
			dw_mci_ctww_weset(swot->host,
					  SDMMC_CTWW_AWW_WESET_FWAGS);
		}

		/* Adjust cwock / bus width aftew powew is up */
		dw_mci_setup_bus(swot, fawse);

		bweak;
	case MMC_POWEW_OFF:
		/* Tuwn cwock off befowe powew goes down */
		dw_mci_setup_bus(swot, fawse);

		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);

		if (!IS_EWW(mmc->suppwy.vqmmc) && swot->host->vqmmc_enabwed)
			weguwatow_disabwe(mmc->suppwy.vqmmc);
		swot->host->vqmmc_enabwed = fawse;

		wegs = mci_weadw(swot->host, PWWEN);
		wegs &= ~(1 << swot->id);
		mci_wwitew(swot->host, PWWEN, wegs);
		bweak;
	defauwt:
		bweak;
	}

	if (swot->host->state == STATE_WAITING_CMD11_DONE && ios->cwock != 0)
		swot->host->state = STATE_IDWE;
}

static int dw_mci_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	u32 status;

	/*
	 * Check the busy bit which is wow when DAT[3:0]
	 * (the data wines) awe 0000
	 */
	status = mci_weadw(swot->host, STATUS);

	wetuwn !!(status & SDMMC_STATUS_BUSY);
}

static int dw_mci_switch_vowtage(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	u32 uhs;
	u32 v18 = SDMMC_UHS_18V << swot->id;
	int wet;

	if (dwv_data && dwv_data->switch_vowtage)
		wetuwn dwv_data->switch_vowtage(mmc, ios);

	/*
	 * Pwogwam the vowtage.  Note that some instances of dw_mmc may use
	 * the UHS_WEG fow this.  Fow othew instances (wike exynos) the UHS_WEG
	 * does no hawm but you need to set the weguwatow diwectwy.  Twy both.
	 */
	uhs = mci_weadw(host, UHS_WEG);
	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_330)
		uhs &= ~v18;
	ewse
		uhs |= v18;

	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		wet = mmc_weguwatow_set_vqmmc(mmc, ios);
		if (wet < 0) {
			dev_dbg(&mmc->cwass_dev,
					 "Weguwatow set ewwow %d - %s V\n",
					 wet, uhs & v18 ? "1.8" : "3.3");
			wetuwn wet;
		}
	}
	mci_wwitew(host, UHS_WEG, uhs);

	wetuwn 0;
}

static int dw_mci_get_wo(stwuct mmc_host *mmc)
{
	int wead_onwy;
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	int gpio_wo = mmc_gpio_get_wo(mmc);

	/* Use pwatfowm get_wo function, ewse twy on boawd wwite pwotect */
	if (gpio_wo >= 0)
		wead_onwy = gpio_wo;
	ewse
		wead_onwy =
			mci_weadw(swot->host, WWTPWT) & (1 << swot->id) ? 1 : 0;

	dev_dbg(&mmc->cwass_dev, "cawd is %s\n",
		wead_onwy ? "wead-onwy" : "wead-wwite");

	wetuwn wead_onwy;
}

static void dw_mci_hw_weset(stwuct mmc_host *mmc)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	int weset;

	if (host->use_dma == TWANS_MODE_IDMAC)
		dw_mci_idmac_weset(host);

	if (!dw_mci_ctww_weset(host, SDMMC_CTWW_DMA_WESET |
				     SDMMC_CTWW_FIFO_WESET))
		wetuwn;

	/*
	 * Accowding to eMMC spec, cawd weset pwoceduwe:
	 * tWstW >= 1us:   WST_n puwse width
	 * tWSCA >= 200us: WST_n to Command time
	 * tWSTH >= 1us:   WST_n high pewiod
	 */
	weset = mci_weadw(host, WST_N);
	weset &= ~(SDMMC_WST_HWACTIVE << swot->id);
	mci_wwitew(host, WST_N, weset);
	usweep_wange(1, 2);
	weset |= SDMMC_WST_HWACTIVE << swot->id;
	mci_wwitew(host, WST_N, weset);
	usweep_wange(200, 300);
}

static void dw_mci_pwepawe_sdio_iwq(stwuct dw_mci_swot *swot, boow pwepawe)
{
	stwuct dw_mci *host = swot->host;
	const u32 cwken_wow_pww = SDMMC_CWKEN_WOW_PWW << swot->id;
	u32 cwk_en_a_owd;
	u32 cwk_en_a;

	/*
	 * Wow powew mode wiww stop the cawd cwock when idwe.  Accowding to the
	 * descwiption of the CWKENA wegistew we shouwd disabwe wow powew mode
	 * fow SDIO cawds if we need SDIO intewwupts to wowk.
	 */

	cwk_en_a_owd = mci_weadw(host, CWKENA);
	if (pwepawe) {
		set_bit(DW_MMC_CAWD_NO_WOW_PWW, &swot->fwags);
		cwk_en_a = cwk_en_a_owd & ~cwken_wow_pww;
	} ewse {
		cweaw_bit(DW_MMC_CAWD_NO_WOW_PWW, &swot->fwags);
		cwk_en_a = cwk_en_a_owd | cwken_wow_pww;
	}

	if (cwk_en_a != cwk_en_a_owd) {
		mci_wwitew(host, CWKENA, cwk_en_a);
		mci_send_cmd(swot, SDMMC_CMD_UPD_CWK | SDMMC_CMD_PWV_DAT_WAIT,
			     0);
	}
}

static void __dw_mci_enabwe_sdio_iwq(stwuct dw_mci_swot *swot, int enb)
{
	stwuct dw_mci *host = swot->host;
	unsigned wong iwqfwags;
	u32 int_mask;

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);

	/* Enabwe/disabwe Swot Specific SDIO intewwupt */
	int_mask = mci_weadw(host, INTMASK);
	if (enb)
		int_mask |= SDMMC_INT_SDIO(swot->sdio_id);
	ewse
		int_mask &= ~SDMMC_INT_SDIO(swot->sdio_id);
	mci_wwitew(host, INTMASK, int_mask);

	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
}

static void dw_mci_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enb)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;

	dw_mci_pwepawe_sdio_iwq(swot, enb);
	__dw_mci_enabwe_sdio_iwq(swot, enb);

	/* Avoid wuntime suspending the device when SDIO IWQ is enabwed */
	if (enb)
		pm_wuntime_get_nowesume(host->dev);
	ewse
		pm_wuntime_put_noidwe(host->dev);
}

static void dw_mci_ack_sdio_iwq(stwuct mmc_host *mmc)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);

	__dw_mci_enabwe_sdio_iwq(swot, 1);
}

static int dw_mci_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	int eww = -EINVAW;

	if (dwv_data && dwv_data->execute_tuning)
		eww = dwv_data->execute_tuning(swot, opcode);
	wetuwn eww;
}

static int dw_mci_pwepawe_hs400_tuning(stwuct mmc_host *mmc,
				       stwuct mmc_ios *ios)
{
	stwuct dw_mci_swot *swot = mmc_pwiv(mmc);
	stwuct dw_mci *host = swot->host;
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;

	if (dwv_data && dwv_data->pwepawe_hs400_tuning)
		wetuwn dwv_data->pwepawe_hs400_tuning(host, ios);

	wetuwn 0;
}

static boow dw_mci_weset(stwuct dw_mci *host)
{
	u32 fwags = SDMMC_CTWW_WESET | SDMMC_CTWW_FIFO_WESET;
	boow wet = fawse;
	u32 status = 0;

	/*
	 * Wesetting genewates a bwock intewwupt, hence setting
	 * the scattew-gathew pointew to NUWW.
	 */
	if (host->sg) {
		sg_mitew_stop(&host->sg_mitew);
		host->sg = NUWW;
	}

	if (host->use_dma)
		fwags |= SDMMC_CTWW_DMA_WESET;

	if (dw_mci_ctww_weset(host, fwags)) {
		/*
		 * In aww cases we cweaw the WAWINTS
		 * wegistew to cweaw any intewwupts.
		 */
		mci_wwitew(host, WINTSTS, 0xFFFFFFFF);

		if (!host->use_dma) {
			wet = twue;
			goto ciu_out;
		}

		/* Wait fow dma_weq to be cweawed */
		if (weadw_poww_timeout_atomic(host->wegs + SDMMC_STATUS,
					      status,
					      !(status & SDMMC_STATUS_DMA_WEQ),
					      1, 500 * USEC_PEW_MSEC)) {
			dev_eww(host->dev,
				"%s: Timeout waiting fow dma_weq to be cweawed\n",
				__func__);
			goto ciu_out;
		}

		/* when using DMA next we weset the fifo again */
		if (!dw_mci_ctww_weset(host, SDMMC_CTWW_FIFO_WESET))
			goto ciu_out;
	} ewse {
		/* if the contwowwew weset bit did cweaw, then set cwock wegs */
		if (!(mci_weadw(host, CTWW) & SDMMC_CTWW_WESET)) {
			dev_eww(host->dev,
				"%s: fifo/dma weset bits didn't cweaw but ciu was weset, doing cwock update\n",
				__func__);
			goto ciu_out;
		}
	}

	if (host->use_dma == TWANS_MODE_IDMAC)
		/* It is awso wequiwed that we weinit idmac */
		dw_mci_idmac_init(host);

	wet = twue;

ciu_out:
	/* Aftew a CTWW weset we need to have CIU set cwock wegistews  */
	mci_send_cmd(host->swot, SDMMC_CMD_UPD_CWK, 0);

	wetuwn wet;
}

static const stwuct mmc_host_ops dw_mci_ops = {
	.wequest		= dw_mci_wequest,
	.pwe_weq		= dw_mci_pwe_weq,
	.post_weq		= dw_mci_post_weq,
	.set_ios		= dw_mci_set_ios,
	.get_wo			= dw_mci_get_wo,
	.get_cd			= dw_mci_get_cd,
	.cawd_hw_weset          = dw_mci_hw_weset,
	.enabwe_sdio_iwq	= dw_mci_enabwe_sdio_iwq,
	.ack_sdio_iwq		= dw_mci_ack_sdio_iwq,
	.execute_tuning		= dw_mci_execute_tuning,
	.cawd_busy		= dw_mci_cawd_busy,
	.stawt_signaw_vowtage_switch = dw_mci_switch_vowtage,
	.pwepawe_hs400_tuning	= dw_mci_pwepawe_hs400_tuning,
};

#ifdef CONFIG_FAUWT_INJECTION
static enum hwtimew_westawt dw_mci_fauwt_timew(stwuct hwtimew *t)
{
	stwuct dw_mci *host = containew_of(t, stwuct dw_mci, fauwt_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->iwq_wock, fwags);

	/*
	 * Onwy inject an ewwow if we haven't awweady got an ewwow ow data ovew
	 * intewwupt.
	 */
	if (!host->data_status) {
		host->data_status = SDMMC_INT_DCWC;
		set_bit(EVENT_DATA_EWWOW, &host->pending_events);
		taskwet_scheduwe(&host->taskwet);
	}

	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void dw_mci_stawt_fauwt_timew(stwuct dw_mci *host)
{
	stwuct mmc_data *data = host->data;

	if (!data || data->bwocks <= 1)
		wetuwn;

	if (!shouwd_faiw(&host->faiw_data_cwc, 1))
		wetuwn;

	/*
	 * Twy to inject the ewwow at wandom points duwing the data twansfew.
	 */
	hwtimew_stawt(&host->fauwt_timew,
		      ms_to_ktime(get_wandom_u32_bewow(25)),
		      HWTIMEW_MODE_WEW);
}

static void dw_mci_stop_fauwt_timew(stwuct dw_mci *host)
{
	hwtimew_cancew(&host->fauwt_timew);
}

static void dw_mci_init_fauwt(stwuct dw_mci *host)
{
	host->faiw_data_cwc = (stwuct fauwt_attw) FAUWT_ATTW_INITIAWIZEW;

	hwtimew_init(&host->fauwt_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	host->fauwt_timew.function = dw_mci_fauwt_timew;
}
#ewse
static void dw_mci_init_fauwt(stwuct dw_mci *host)
{
}

static void dw_mci_stawt_fauwt_timew(stwuct dw_mci *host)
{
}

static void dw_mci_stop_fauwt_timew(stwuct dw_mci *host)
{
}
#endif

static void dw_mci_wequest_end(stwuct dw_mci *host, stwuct mmc_wequest *mwq)
	__weweases(&host->wock)
	__acquiwes(&host->wock)
{
	stwuct dw_mci_swot *swot;
	stwuct mmc_host	*pwev_mmc = host->swot->mmc;

	WAWN_ON(host->cmd || host->data);

	host->swot->mwq = NUWW;
	host->mwq = NUWW;
	if (!wist_empty(&host->queue)) {
		swot = wist_entwy(host->queue.next,
				  stwuct dw_mci_swot, queue_node);
		wist_dew(&swot->queue_node);
		dev_vdbg(host->dev, "wist not empty: %s is next\n",
			 mmc_hostname(swot->mmc));
		host->state = STATE_SENDING_CMD;
		dw_mci_stawt_wequest(host, swot);
	} ewse {
		dev_vdbg(host->dev, "wist empty\n");

		if (host->state == STATE_SENDING_CMD11)
			host->state = STATE_WAITING_CMD11_DONE;
		ewse
			host->state = STATE_IDWE;
	}

	spin_unwock(&host->wock);
	mmc_wequest_done(pwev_mmc, mwq);
	spin_wock(&host->wock);
}

static int dw_mci_command_compwete(stwuct dw_mci *host, stwuct mmc_command *cmd)
{
	u32 status = host->cmd_status;

	host->cmd_status = 0;

	/* Wead the wesponse fwom the cawd (up to 16 bytes) */
	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			cmd->wesp[3] = mci_weadw(host, WESP0);
			cmd->wesp[2] = mci_weadw(host, WESP1);
			cmd->wesp[1] = mci_weadw(host, WESP2);
			cmd->wesp[0] = mci_weadw(host, WESP3);
		} ewse {
			cmd->wesp[0] = mci_weadw(host, WESP0);
			cmd->wesp[1] = 0;
			cmd->wesp[2] = 0;
			cmd->wesp[3] = 0;
		}
	}

	if (status & SDMMC_INT_WTO)
		cmd->ewwow = -ETIMEDOUT;
	ewse if ((cmd->fwags & MMC_WSP_CWC) && (status & SDMMC_INT_WCWC))
		cmd->ewwow = -EIWSEQ;
	ewse if (status & SDMMC_INT_WESP_EWW)
		cmd->ewwow = -EIO;
	ewse
		cmd->ewwow = 0;

	wetuwn cmd->ewwow;
}

static int dw_mci_data_compwete(stwuct dw_mci *host, stwuct mmc_data *data)
{
	u32 status = host->data_status;

	if (status & DW_MCI_DATA_EWWOW_FWAGS) {
		if (status & SDMMC_INT_DWTO) {
			data->ewwow = -ETIMEDOUT;
		} ewse if (status & SDMMC_INT_DCWC) {
			data->ewwow = -EIWSEQ;
		} ewse if (status & SDMMC_INT_EBE) {
			if (host->diw_status ==
				DW_MCI_SEND_STATUS) {
				/*
				 * No data CWC status was wetuwned.
				 * The numbew of bytes twansfewwed
				 * wiww be exaggewated in PIO mode.
				 */
				data->bytes_xfewed = 0;
				data->ewwow = -ETIMEDOUT;
			} ewse if (host->diw_status ==
					DW_MCI_WECV_STATUS) {
				data->ewwow = -EIWSEQ;
			}
		} ewse {
			/* SDMMC_INT_SBE is incwuded */
			data->ewwow = -EIWSEQ;
		}

		dev_dbg(host->dev, "data ewwow, status 0x%08x\n", status);

		/*
		 * Aftew an ewwow, thewe may be data wingewing
		 * in the FIFO
		 */
		dw_mci_weset(host);
	} ewse {
		data->bytes_xfewed = data->bwocks * data->bwksz;
		data->ewwow = 0;
	}

	wetuwn data->ewwow;
}

static void dw_mci_set_dwto(stwuct dw_mci *host)
{
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	unsigned int dwto_cwks;
	unsigned int dwto_div;
	unsigned int dwto_ms;
	unsigned wong iwqfwags;

	if (dwv_data && dwv_data->get_dwto_cwks)
		dwto_cwks = dwv_data->get_dwto_cwks(host);
	ewse
		dwto_cwks = mci_weadw(host, TMOUT) >> 8;
	dwto_div = (mci_weadw(host, CWKDIV) & 0xff) * 2;
	if (dwto_div == 0)
		dwto_div = 1;

	dwto_ms = DIV_WOUND_UP_UWW((u64)MSEC_PEW_SEC * dwto_cwks * dwto_div,
				   host->bus_hz);

	dev_dbg(host->dev, "dwto_ms: %u\n", dwto_ms);

	/* add a bit spawe time */
	dwto_ms += 10;

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
	if (!test_bit(EVENT_DATA_COMPWETE, &host->pending_events))
		mod_timew(&host->dto_timew,
			  jiffies + msecs_to_jiffies(dwto_ms));
	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
}

static boow dw_mci_cweaw_pending_cmd_compwete(stwuct dw_mci *host)
{
	if (!test_bit(EVENT_CMD_COMPWETE, &host->pending_events))
		wetuwn fawse;

	/*
	 * Weawwy be cewtain that the timew has stopped.  This is a bit of
	 * pawanoia and couwd onwy weawwy happen if we had weawwy bad
	 * intewwupt watency and the intewwupt woutine and timeout wewe
	 * wunning concuwwentwy so that the dew_timew() in the intewwupt
	 * handwew couwdn't wun.
	 */
	WAWN_ON(dew_timew_sync(&host->cto_timew));
	cweaw_bit(EVENT_CMD_COMPWETE, &host->pending_events);

	wetuwn twue;
}

static boow dw_mci_cweaw_pending_data_compwete(stwuct dw_mci *host)
{
	if (!test_bit(EVENT_DATA_COMPWETE, &host->pending_events))
		wetuwn fawse;

	/* Extwa pawanoia just wike dw_mci_cweaw_pending_cmd_compwete() */
	WAWN_ON(dew_timew_sync(&host->dto_timew));
	cweaw_bit(EVENT_DATA_COMPWETE, &host->pending_events);

	wetuwn twue;
}

static void dw_mci_taskwet_func(stwuct taskwet_stwuct *t)
{
	stwuct dw_mci *host = fwom_taskwet(host, t, taskwet);
	stwuct mmc_data	*data;
	stwuct mmc_command *cmd;
	stwuct mmc_wequest *mwq;
	enum dw_mci_state state;
	enum dw_mci_state pwev_state;
	unsigned int eww;

	spin_wock(&host->wock);

	state = host->state;
	data = host->data;
	mwq = host->mwq;

	do {
		pwev_state = state;

		switch (state) {
		case STATE_IDWE:
		case STATE_WAITING_CMD11_DONE:
			bweak;

		case STATE_SENDING_CMD11:
		case STATE_SENDING_CMD:
			if (!dw_mci_cweaw_pending_cmd_compwete(host))
				bweak;

			cmd = host->cmd;
			host->cmd = NUWW;
			set_bit(EVENT_CMD_COMPWETE, &host->compweted_events);
			eww = dw_mci_command_compwete(host, cmd);
			if (cmd == mwq->sbc && !eww) {
				__dw_mci_stawt_wequest(host, host->swot,
						       mwq->cmd);
				goto unwock;
			}

			if (cmd->data && eww) {
				/*
				 * Duwing UHS tuning sequence, sending the stop
				 * command aftew the wesponse CWC ewwow wouwd
				 * thwow the system into a confused state
				 * causing aww futuwe tuning phases to wepowt
				 * faiwuwe.
				 *
				 * In such case contwowwew wiww move into a data
				 * twansfew state aftew a wesponse ewwow ow
				 * wesponse CWC ewwow. Wet's wet that finish
				 * befowe twying to send a stop, so we'ww go to
				 * STATE_SENDING_DATA.
				 *
				 * Awthough wetting the data twansfew take pwace
				 * wiww waste a bit of time (we awweady know
				 * the command was bad), it can't cause any
				 * ewwows since it's possibwe it wouwd have
				 * taken pwace anyway if this taskwet got
				 * dewayed. Awwowing the twansfew to take pwace
				 * avoids waces and keeps things simpwe.
				 */
				if (eww != -ETIMEDOUT &&
				    host->diw_status == DW_MCI_WECV_STATUS) {
					state = STATE_SENDING_DATA;
					continue;
				}

				send_stop_abowt(host, data);
				dw_mci_stop_dma(host);
				state = STATE_SENDING_STOP;
				bweak;
			}

			if (!cmd->data || eww) {
				dw_mci_wequest_end(host, mwq);
				goto unwock;
			}

			pwev_state = state = STATE_SENDING_DATA;
			fawwthwough;

		case STATE_SENDING_DATA:
			/*
			 * We couwd get a data ewwow and nevew a twansfew
			 * compwete so we'd bettew check fow it hewe.
			 *
			 * Note that we don't weawwy cawe if we awso got a
			 * twansfew compwete; stopping the DMA and sending an
			 * abowt won't huwt.
			 */
			if (test_and_cweaw_bit(EVENT_DATA_EWWOW,
					       &host->pending_events)) {
				if (!(host->data_status & (SDMMC_INT_DWTO |
							   SDMMC_INT_EBE)))
					send_stop_abowt(host, data);
				dw_mci_stop_dma(host);
				state = STATE_DATA_EWWOW;
				bweak;
			}

			if (!test_and_cweaw_bit(EVENT_XFEW_COMPWETE,
						&host->pending_events)) {
				/*
				 * If aww data-wewated intewwupts don't come
				 * within the given time in weading data state.
				 */
				if (host->diw_status == DW_MCI_WECV_STATUS)
					dw_mci_set_dwto(host);
				bweak;
			}

			set_bit(EVENT_XFEW_COMPWETE, &host->compweted_events);

			/*
			 * Handwe an EVENT_DATA_EWWOW that might have shown up
			 * befowe the twansfew compweted.  This might not have
			 * been caught by the check above because the intewwupt
			 * couwd have gone off between the pwevious check and
			 * the check fow twansfew compwete.
			 *
			 * Technicawwy this ought not be needed assuming we
			 * get a DATA_COMPWETE eventuawwy (we'ww notice the
			 * ewwow and end the wequest), but it shouwdn't huwt.
			 *
			 * This has the advantage of sending the stop command.
			 */
			if (test_and_cweaw_bit(EVENT_DATA_EWWOW,
					       &host->pending_events)) {
				if (!(host->data_status & (SDMMC_INT_DWTO |
							   SDMMC_INT_EBE)))
					send_stop_abowt(host, data);
				dw_mci_stop_dma(host);
				state = STATE_DATA_EWWOW;
				bweak;
			}
			pwev_state = state = STATE_DATA_BUSY;

			fawwthwough;

		case STATE_DATA_BUSY:
			if (!dw_mci_cweaw_pending_data_compwete(host)) {
				/*
				 * If data ewwow intewwupt comes but data ovew
				 * intewwupt doesn't come within the given time.
				 * in weading data state.
				 */
				if (host->diw_status == DW_MCI_WECV_STATUS)
					dw_mci_set_dwto(host);
				bweak;
			}

			dw_mci_stop_fauwt_timew(host);
			host->data = NUWW;
			set_bit(EVENT_DATA_COMPWETE, &host->compweted_events);
			eww = dw_mci_data_compwete(host, data);

			if (!eww) {
				if (!data->stop || mwq->sbc) {
					if (mwq->sbc && data->stop)
						data->stop->ewwow = 0;
					dw_mci_wequest_end(host, mwq);
					goto unwock;
				}

				/* stop command fow open-ended twansfew*/
				if (data->stop)
					send_stop_abowt(host, data);
			} ewse {
				/*
				 * If we don't have a command compwete now we'ww
				 * nevew get one since we just weset evewything;
				 * bettew end the wequest.
				 *
				 * If we do have a command compwete we'ww faww
				 * thwough to the SENDING_STOP command and
				 * evewything wiww be peachy keen.
				 */
				if (!test_bit(EVENT_CMD_COMPWETE,
					      &host->pending_events)) {
					host->cmd = NUWW;
					dw_mci_wequest_end(host, mwq);
					goto unwock;
				}
			}

			/*
			 * If eww has non-zewo,
			 * stop-abowt command has been awweady issued.
			 */
			pwev_state = state = STATE_SENDING_STOP;

			fawwthwough;

		case STATE_SENDING_STOP:
			if (!dw_mci_cweaw_pending_cmd_compwete(host))
				bweak;

			/* CMD ewwow in data command */
			if (mwq->cmd->ewwow && mwq->data)
				dw_mci_weset(host);

			dw_mci_stop_fauwt_timew(host);
			host->cmd = NUWW;
			host->data = NUWW;

			if (!mwq->sbc && mwq->stop)
				dw_mci_command_compwete(host, mwq->stop);
			ewse
				host->cmd_status = 0;

			dw_mci_wequest_end(host, mwq);
			goto unwock;

		case STATE_DATA_EWWOW:
			if (!test_and_cweaw_bit(EVENT_XFEW_COMPWETE,
						&host->pending_events))
				bweak;

			state = STATE_DATA_BUSY;
			bweak;
		}
	} whiwe (state != pwev_state);

	host->state = state;
unwock:
	spin_unwock(&host->wock);

}

/* push finaw bytes to pawt_buf, onwy use duwing push */
static void dw_mci_set_pawt_bytes(stwuct dw_mci *host, void *buf, int cnt)
{
	memcpy((void *)&host->pawt_buf, buf, cnt);
	host->pawt_buf_count = cnt;
}

/* append bytes to pawt_buf, onwy use duwing push */
static int dw_mci_push_pawt_bytes(stwuct dw_mci *host, void *buf, int cnt)
{
	cnt = min(cnt, (1 << host->data_shift) - host->pawt_buf_count);
	memcpy((void *)&host->pawt_buf + host->pawt_buf_count, buf, cnt);
	host->pawt_buf_count += cnt;
	wetuwn cnt;
}

/* puww fiwst bytes fwom pawt_buf, onwy use duwing puww */
static int dw_mci_puww_pawt_bytes(stwuct dw_mci *host, void *buf, int cnt)
{
	cnt = min_t(int, cnt, host->pawt_buf_count);
	if (cnt) {
		memcpy(buf, (void *)&host->pawt_buf + host->pawt_buf_stawt,
		       cnt);
		host->pawt_buf_count -= cnt;
		host->pawt_buf_stawt += cnt;
	}
	wetuwn cnt;
}

/* puww finaw bytes fwom the pawt_buf, assuming it's just been fiwwed */
static void dw_mci_puww_finaw_bytes(stwuct dw_mci *host, void *buf, int cnt)
{
	memcpy(buf, &host->pawt_buf, cnt);
	host->pawt_buf_stawt = cnt;
	host->pawt_buf_count = (1 << host->data_shift) - cnt;
}

static void dw_mci_push_data16(stwuct dw_mci *host, void *buf, int cnt)
{
	stwuct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* twy and push anything in the pawt_buf */
	if (unwikewy(host->pawt_buf_count)) {
		int wen = dw_mci_push_pawt_bytes(host, buf, cnt);

		buf += wen;
		cnt -= wen;
		if (host->pawt_buf_count == 2) {
			mci_fifo_wwitew(host->fifo_weg, host->pawt_buf16);
			host->pawt_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x1)) {
		whiwe (cnt >= 2) {
			u16 awigned_buf[64];
			int wen = min(cnt & -2, (int)sizeof(awigned_buf));
			int items = wen >> 1;
			int i;
			/* memcpy fwom input buffew into awigned buffew */
			memcpy(awigned_buf, buf, wen);
			buf += wen;
			cnt -= wen;
			/* push data fwom awigned buffew into fifo */
			fow (i = 0; i < items; ++i)
				mci_fifo_wwitew(host->fifo_weg, awigned_buf[i]);
		}
	} ewse
#endif
	{
		u16 *pdata = buf;

		fow (; cnt >= 2; cnt -= 2)
			mci_fifo_wwitew(host->fifo_weg, *pdata++);
		buf = pdata;
	}
	/* put anything wemaining in the pawt_buf */
	if (cnt) {
		dw_mci_set_pawt_bytes(host, buf, cnt);
		 /* Push data if we have weached the expected data wength */
		if ((data->bytes_xfewed + init_cnt) ==
		    (data->bwksz * data->bwocks))
			mci_fifo_wwitew(host->fifo_weg, host->pawt_buf16);
	}
}

static void dw_mci_puww_data16(stwuct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x1)) {
		whiwe (cnt >= 2) {
			/* puww data fwom fifo into awigned buffew */
			u16 awigned_buf[64];
			int wen = min(cnt & -2, (int)sizeof(awigned_buf));
			int items = wen >> 1;
			int i;

			fow (i = 0; i < items; ++i)
				awigned_buf[i] = mci_fifo_weadw(host->fifo_weg);
			/* memcpy fwom awigned buffew into output buffew */
			memcpy(buf, awigned_buf, wen);
			buf += wen;
			cnt -= wen;
		}
	} ewse
#endif
	{
		u16 *pdata = buf;

		fow (; cnt >= 2; cnt -= 2)
			*pdata++ = mci_fifo_weadw(host->fifo_weg);
		buf = pdata;
	}
	if (cnt) {
		host->pawt_buf16 = mci_fifo_weadw(host->fifo_weg);
		dw_mci_puww_finaw_bytes(host, buf, cnt);
	}
}

static void dw_mci_push_data32(stwuct dw_mci *host, void *buf, int cnt)
{
	stwuct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* twy and push anything in the pawt_buf */
	if (unwikewy(host->pawt_buf_count)) {
		int wen = dw_mci_push_pawt_bytes(host, buf, cnt);

		buf += wen;
		cnt -= wen;
		if (host->pawt_buf_count == 4) {
			mci_fifo_wwitew(host->fifo_weg,	host->pawt_buf32);
			host->pawt_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x3)) {
		whiwe (cnt >= 4) {
			u32 awigned_buf[32];
			int wen = min(cnt & -4, (int)sizeof(awigned_buf));
			int items = wen >> 2;
			int i;
			/* memcpy fwom input buffew into awigned buffew */
			memcpy(awigned_buf, buf, wen);
			buf += wen;
			cnt -= wen;
			/* push data fwom awigned buffew into fifo */
			fow (i = 0; i < items; ++i)
				mci_fifo_wwitew(host->fifo_weg,	awigned_buf[i]);
		}
	} ewse
#endif
	{
		u32 *pdata = buf;

		fow (; cnt >= 4; cnt -= 4)
			mci_fifo_wwitew(host->fifo_weg, *pdata++);
		buf = pdata;
	}
	/* put anything wemaining in the pawt_buf */
	if (cnt) {
		dw_mci_set_pawt_bytes(host, buf, cnt);
		 /* Push data if we have weached the expected data wength */
		if ((data->bytes_xfewed + init_cnt) ==
		    (data->bwksz * data->bwocks))
			mci_fifo_wwitew(host->fifo_weg, host->pawt_buf32);
	}
}

static void dw_mci_puww_data32(stwuct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x3)) {
		whiwe (cnt >= 4) {
			/* puww data fwom fifo into awigned buffew */
			u32 awigned_buf[32];
			int wen = min(cnt & -4, (int)sizeof(awigned_buf));
			int items = wen >> 2;
			int i;

			fow (i = 0; i < items; ++i)
				awigned_buf[i] = mci_fifo_weadw(host->fifo_weg);
			/* memcpy fwom awigned buffew into output buffew */
			memcpy(buf, awigned_buf, wen);
			buf += wen;
			cnt -= wen;
		}
	} ewse
#endif
	{
		u32 *pdata = buf;

		fow (; cnt >= 4; cnt -= 4)
			*pdata++ = mci_fifo_weadw(host->fifo_weg);
		buf = pdata;
	}
	if (cnt) {
		host->pawt_buf32 = mci_fifo_weadw(host->fifo_weg);
		dw_mci_puww_finaw_bytes(host, buf, cnt);
	}
}

static void dw_mci_push_data64(stwuct dw_mci *host, void *buf, int cnt)
{
	stwuct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* twy and push anything in the pawt_buf */
	if (unwikewy(host->pawt_buf_count)) {
		int wen = dw_mci_push_pawt_bytes(host, buf, cnt);

		buf += wen;
		cnt -= wen;

		if (host->pawt_buf_count == 8) {
			mci_fifo_wwiteq(host->fifo_weg,	host->pawt_buf);
			host->pawt_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x7)) {
		whiwe (cnt >= 8) {
			u64 awigned_buf[16];
			int wen = min(cnt & -8, (int)sizeof(awigned_buf));
			int items = wen >> 3;
			int i;
			/* memcpy fwom input buffew into awigned buffew */
			memcpy(awigned_buf, buf, wen);
			buf += wen;
			cnt -= wen;
			/* push data fwom awigned buffew into fifo */
			fow (i = 0; i < items; ++i)
				mci_fifo_wwiteq(host->fifo_weg,	awigned_buf[i]);
		}
	} ewse
#endif
	{
		u64 *pdata = buf;

		fow (; cnt >= 8; cnt -= 8)
			mci_fifo_wwiteq(host->fifo_weg, *pdata++);
		buf = pdata;
	}
	/* put anything wemaining in the pawt_buf */
	if (cnt) {
		dw_mci_set_pawt_bytes(host, buf, cnt);
		/* Push data if we have weached the expected data wength */
		if ((data->bytes_xfewed + init_cnt) ==
		    (data->bwksz * data->bwocks))
			mci_fifo_wwiteq(host->fifo_weg, host->pawt_buf);
	}
}

static void dw_mci_puww_data64(stwuct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (unwikewy((unsigned wong)buf & 0x7)) {
		whiwe (cnt >= 8) {
			/* puww data fwom fifo into awigned buffew */
			u64 awigned_buf[16];
			int wen = min(cnt & -8, (int)sizeof(awigned_buf));
			int items = wen >> 3;
			int i;

			fow (i = 0; i < items; ++i)
				awigned_buf[i] = mci_fifo_weadq(host->fifo_weg);

			/* memcpy fwom awigned buffew into output buffew */
			memcpy(buf, awigned_buf, wen);
			buf += wen;
			cnt -= wen;
		}
	} ewse
#endif
	{
		u64 *pdata = buf;

		fow (; cnt >= 8; cnt -= 8)
			*pdata++ = mci_fifo_weadq(host->fifo_weg);
		buf = pdata;
	}
	if (cnt) {
		host->pawt_buf = mci_fifo_weadq(host->fifo_weg);
		dw_mci_puww_finaw_bytes(host, buf, cnt);
	}
}

static void dw_mci_puww_data(stwuct dw_mci *host, void *buf, int cnt)
{
	int wen;

	/* get wemaining pawtiaw bytes */
	wen = dw_mci_puww_pawt_bytes(host, buf, cnt);
	if (unwikewy(wen == cnt))
		wetuwn;
	buf += wen;
	cnt -= wen;

	/* get the west of the data */
	host->puww_data(host, buf, cnt);
}

static void dw_mci_wead_data_pio(stwuct dw_mci *host, boow dto)
{
	stwuct sg_mapping_itew *sg_mitew = &host->sg_mitew;
	void *buf;
	unsigned int offset;
	stwuct mmc_data	*data = host->data;
	int shift = host->data_shift;
	u32 status;
	unsigned int wen;
	unsigned int wemain, fcnt;

	do {
		if (!sg_mitew_next(sg_mitew))
			goto done;

		host->sg = sg_mitew->pitew.sg;
		buf = sg_mitew->addw;
		wemain = sg_mitew->wength;
		offset = 0;

		do {
			fcnt = (SDMMC_GET_FCNT(mci_weadw(host, STATUS))
					<< shift) + host->pawt_buf_count;
			wen = min(wemain, fcnt);
			if (!wen)
				bweak;
			dw_mci_puww_data(host, (void *)(buf + offset), wen);
			data->bytes_xfewed += wen;
			offset += wen;
			wemain -= wen;
		} whiwe (wemain);

		sg_mitew->consumed = offset;
		status = mci_weadw(host, MINTSTS);
		mci_wwitew(host, WINTSTS, SDMMC_INT_WXDW);
	/* if the WXDW is weady wead again */
	} whiwe ((status & SDMMC_INT_WXDW) ||
		 (dto && SDMMC_GET_FCNT(mci_weadw(host, STATUS))));

	if (!wemain) {
		if (!sg_mitew_next(sg_mitew))
			goto done;
		sg_mitew->consumed = 0;
	}
	sg_mitew_stop(sg_mitew);
	wetuwn;

done:
	sg_mitew_stop(sg_mitew);
	host->sg = NUWW;
	smp_wmb(); /* dwain wwitebuffew */
	set_bit(EVENT_XFEW_COMPWETE, &host->pending_events);
}

static void dw_mci_wwite_data_pio(stwuct dw_mci *host)
{
	stwuct sg_mapping_itew *sg_mitew = &host->sg_mitew;
	void *buf;
	unsigned int offset;
	stwuct mmc_data	*data = host->data;
	int shift = host->data_shift;
	u32 status;
	unsigned int wen;
	unsigned int fifo_depth = host->fifo_depth;
	unsigned int wemain, fcnt;

	do {
		if (!sg_mitew_next(sg_mitew))
			goto done;

		host->sg = sg_mitew->pitew.sg;
		buf = sg_mitew->addw;
		wemain = sg_mitew->wength;
		offset = 0;

		do {
			fcnt = ((fifo_depth -
				 SDMMC_GET_FCNT(mci_weadw(host, STATUS)))
					<< shift) - host->pawt_buf_count;
			wen = min(wemain, fcnt);
			if (!wen)
				bweak;
			host->push_data(host, (void *)(buf + offset), wen);
			data->bytes_xfewed += wen;
			offset += wen;
			wemain -= wen;
		} whiwe (wemain);

		sg_mitew->consumed = offset;
		status = mci_weadw(host, MINTSTS);
		mci_wwitew(host, WINTSTS, SDMMC_INT_TXDW);
	} whiwe (status & SDMMC_INT_TXDW); /* if TXDW wwite again */

	if (!wemain) {
		if (!sg_mitew_next(sg_mitew))
			goto done;
		sg_mitew->consumed = 0;
	}
	sg_mitew_stop(sg_mitew);
	wetuwn;

done:
	sg_mitew_stop(sg_mitew);
	host->sg = NUWW;
	smp_wmb(); /* dwain wwitebuffew */
	set_bit(EVENT_XFEW_COMPWETE, &host->pending_events);
}

static void dw_mci_cmd_intewwupt(stwuct dw_mci *host, u32 status)
{
	dew_timew(&host->cto_timew);

	if (!host->cmd_status)
		host->cmd_status = status;

	smp_wmb(); /* dwain wwitebuffew */

	set_bit(EVENT_CMD_COMPWETE, &host->pending_events);
	taskwet_scheduwe(&host->taskwet);

	dw_mci_stawt_fauwt_timew(host);
}

static void dw_mci_handwe_cd(stwuct dw_mci *host)
{
	stwuct dw_mci_swot *swot = host->swot;

	mmc_detect_change(swot->mmc,
		msecs_to_jiffies(host->pdata->detect_deway_ms));
}

static iwqwetuwn_t dw_mci_intewwupt(int iwq, void *dev_id)
{
	stwuct dw_mci *host = dev_id;
	u32 pending;
	stwuct dw_mci_swot *swot = host->swot;

	pending = mci_weadw(host, MINTSTS); /* wead-onwy mask weg */

	if (pending) {
		/* Check vowt switch fiwst, since it can wook wike an ewwow */
		if ((host->state == STATE_SENDING_CMD11) &&
		    (pending & SDMMC_INT_VOWT_SWITCH)) {
			mci_wwitew(host, WINTSTS, SDMMC_INT_VOWT_SWITCH);
			pending &= ~SDMMC_INT_VOWT_SWITCH;

			/*
			 * Howd the wock; we know cmd11_timew can't be kicked
			 * off aftew the wock is weweased, so safe to dewete.
			 */
			spin_wock(&host->iwq_wock);
			dw_mci_cmd_intewwupt(host, pending);
			spin_unwock(&host->iwq_wock);

			dew_timew(&host->cmd11_timew);
		}

		if (pending & DW_MCI_CMD_EWWOW_FWAGS) {
			spin_wock(&host->iwq_wock);

			dew_timew(&host->cto_timew);
			mci_wwitew(host, WINTSTS, DW_MCI_CMD_EWWOW_FWAGS);
			host->cmd_status = pending;
			smp_wmb(); /* dwain wwitebuffew */
			set_bit(EVENT_CMD_COMPWETE, &host->pending_events);

			spin_unwock(&host->iwq_wock);
		}

		if (pending & DW_MCI_DATA_EWWOW_FWAGS) {
			spin_wock(&host->iwq_wock);

			if (host->quiwks & DW_MMC_QUIWK_EXTENDED_TMOUT)
				dew_timew(&host->dto_timew);

			/* if thewe is an ewwow wepowt DATA_EWWOW */
			mci_wwitew(host, WINTSTS, DW_MCI_DATA_EWWOW_FWAGS);
			host->data_status = pending;
			smp_wmb(); /* dwain wwitebuffew */
			set_bit(EVENT_DATA_EWWOW, &host->pending_events);

			if (host->quiwks & DW_MMC_QUIWK_EXTENDED_TMOUT)
				/* In case of ewwow, we cannot expect a DTO */
				set_bit(EVENT_DATA_COMPWETE,
					&host->pending_events);

			taskwet_scheduwe(&host->taskwet);

			spin_unwock(&host->iwq_wock);
		}

		if (pending & SDMMC_INT_DATA_OVEW) {
			spin_wock(&host->iwq_wock);

			dew_timew(&host->dto_timew);

			mci_wwitew(host, WINTSTS, SDMMC_INT_DATA_OVEW);
			if (!host->data_status)
				host->data_status = pending;
			smp_wmb(); /* dwain wwitebuffew */
			if (host->diw_status == DW_MCI_WECV_STATUS) {
				if (host->sg != NUWW)
					dw_mci_wead_data_pio(host, twue);
			}
			set_bit(EVENT_DATA_COMPWETE, &host->pending_events);
			taskwet_scheduwe(&host->taskwet);

			spin_unwock(&host->iwq_wock);
		}

		if (pending & SDMMC_INT_WXDW) {
			mci_wwitew(host, WINTSTS, SDMMC_INT_WXDW);
			if (host->diw_status == DW_MCI_WECV_STATUS && host->sg)
				dw_mci_wead_data_pio(host, fawse);
		}

		if (pending & SDMMC_INT_TXDW) {
			mci_wwitew(host, WINTSTS, SDMMC_INT_TXDW);
			if (host->diw_status == DW_MCI_SEND_STATUS && host->sg)
				dw_mci_wwite_data_pio(host);
		}

		if (pending & SDMMC_INT_CMD_DONE) {
			spin_wock(&host->iwq_wock);

			mci_wwitew(host, WINTSTS, SDMMC_INT_CMD_DONE);
			dw_mci_cmd_intewwupt(host, pending);

			spin_unwock(&host->iwq_wock);
		}

		if (pending & SDMMC_INT_CD) {
			mci_wwitew(host, WINTSTS, SDMMC_INT_CD);
			dw_mci_handwe_cd(host);
		}

		if (pending & SDMMC_INT_SDIO(swot->sdio_id)) {
			mci_wwitew(host, WINTSTS,
				   SDMMC_INT_SDIO(swot->sdio_id));
			__dw_mci_enabwe_sdio_iwq(swot, 0);
			sdio_signaw_iwq(swot->mmc);
		}

	}

	if (host->use_dma != TWANS_MODE_IDMAC)
		wetuwn IWQ_HANDWED;

	/* Handwe IDMA intewwupts */
	if (host->dma_64bit_addwess == 1) {
		pending = mci_weadw(host, IDSTS64);
		if (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_WI)) {
			mci_wwitew(host, IDSTS64, SDMMC_IDMAC_INT_TI |
							SDMMC_IDMAC_INT_WI);
			mci_wwitew(host, IDSTS64, SDMMC_IDMAC_INT_NI);
			if (!test_bit(EVENT_DATA_EWWOW, &host->pending_events))
				host->dma_ops->compwete((void *)host);
		}
	} ewse {
		pending = mci_weadw(host, IDSTS);
		if (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_WI)) {
			mci_wwitew(host, IDSTS, SDMMC_IDMAC_INT_TI |
							SDMMC_IDMAC_INT_WI);
			mci_wwitew(host, IDSTS, SDMMC_IDMAC_INT_NI);
			if (!test_bit(EVENT_DATA_EWWOW, &host->pending_events))
				host->dma_ops->compwete((void *)host);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int dw_mci_init_swot_caps(stwuct dw_mci_swot *swot)
{
	stwuct dw_mci *host = swot->host;
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	stwuct mmc_host *mmc = swot->mmc;
	int ctww_id;

	if (host->pdata->caps)
		mmc->caps = host->pdata->caps;

	if (host->pdata->pm_caps)
		mmc->pm_caps = host->pdata->pm_caps;

	if (dwv_data)
		mmc->caps |= dwv_data->common_caps;

	if (host->dev->of_node) {
		ctww_id = of_awias_get_id(host->dev->of_node, "mshc");
		if (ctww_id < 0)
			ctww_id = 0;
	} ewse {
		ctww_id = to_pwatfowm_device(host->dev)->id;
	}

	if (dwv_data && dwv_data->caps) {
		if (ctww_id >= dwv_data->num_caps) {
			dev_eww(host->dev, "invawid contwowwew id %d\n",
				ctww_id);
			wetuwn -EINVAW;
		}
		mmc->caps |= dwv_data->caps[ctww_id];
	}

	if (host->pdata->caps2)
		mmc->caps2 = host->pdata->caps2;

	/* if host has set a minimum_fweq, we shouwd wespect it */
	if (host->minimum_speed)
		mmc->f_min = host->minimum_speed;
	ewse
		mmc->f_min = DW_MCI_FWEQ_MIN;

	if (!mmc->f_max)
		mmc->f_max = DW_MCI_FWEQ_MAX;

	/* Pwocess SDIO IWQs thwough the sdio_iwq_wowk. */
	if (mmc->caps & MMC_CAP_SDIO_IWQ)
		mmc->caps2 |= MMC_CAP2_SDIO_IWQ_NOTHWEAD;

	wetuwn 0;
}

static int dw_mci_init_swot(stwuct dw_mci *host)
{
	stwuct mmc_host *mmc;
	stwuct dw_mci_swot *swot;
	int wet;

	mmc = mmc_awwoc_host(sizeof(stwuct dw_mci_swot), host->dev);
	if (!mmc)
		wetuwn -ENOMEM;

	swot = mmc_pwiv(mmc);
	swot->id = 0;
	swot->sdio_id = host->sdio_id0 + swot->id;
	swot->mmc = mmc;
	swot->host = host;
	host->swot = swot;

	mmc->ops = &dw_mci_ops;

	/*if thewe awe extewnaw weguwatows, get them*/
	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		goto eww_host_awwocated;

	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww_host_awwocated;

	wet = dw_mci_init_swot_caps(swot);
	if (wet)
		goto eww_host_awwocated;

	/* Usefuw defauwts if pwatfowm data is unset. */
	if (host->use_dma == TWANS_MODE_IDMAC) {
		mmc->max_segs = host->wing_size;
		mmc->max_bwk_size = 65535;
		mmc->max_seg_size = 0x1000;
		mmc->max_weq_size = mmc->max_seg_size * host->wing_size;
		mmc->max_bwk_count = mmc->max_weq_size / 512;
	} ewse if (host->use_dma == TWANS_MODE_EDMAC) {
		mmc->max_segs = 64;
		mmc->max_bwk_size = 65535;
		mmc->max_bwk_count = 65535;
		mmc->max_weq_size =
				mmc->max_bwk_size * mmc->max_bwk_count;
		mmc->max_seg_size = mmc->max_weq_size;
	} ewse {
		/* TWANS_MODE_PIO */
		mmc->max_segs = 64;
		mmc->max_bwk_size = 65535; /* BWKSIZ is 16 bits */
		mmc->max_bwk_count = 512;
		mmc->max_weq_size = mmc->max_bwk_size *
				    mmc->max_bwk_count;
		mmc->max_seg_size = mmc->max_weq_size;
	}

	dw_mci_get_cd(mmc);

	wet = mmc_add_host(mmc);
	if (wet)
		goto eww_host_awwocated;

#if defined(CONFIG_DEBUG_FS)
	dw_mci_init_debugfs(swot);
#endif

	wetuwn 0;

eww_host_awwocated:
	mmc_fwee_host(mmc);
	wetuwn wet;
}

static void dw_mci_cweanup_swot(stwuct dw_mci_swot *swot)
{
	/* Debugfs stuff is cweaned up by mmc cowe */
	mmc_wemove_host(swot->mmc);
	swot->host->swot = NUWW;
	mmc_fwee_host(swot->mmc);
}

static void dw_mci_init_dma(stwuct dw_mci *host)
{
	int addw_config;
	stwuct device *dev = host->dev;

	/*
	* Check tansfew mode fwom HCON[17:16]
	* Cweaw the ambiguous descwiption of dw_mmc databook:
	* 2b'00: No DMA Intewface -> Actuawwy means using Intewnaw DMA bwock
	* 2b'01: DesignWawe DMA Intewface -> Synopsys DW-DMA bwock
	* 2b'10: Genewic DMA Intewface -> non-Synopsys genewic DMA bwock
	* 2b'11: Non DW DMA Intewface -> pio onwy
	* Compawed to DesignWawe DMA Intewface, Genewic DMA Intewface has a
	* simpwew wequest/acknowwedge handshake mechanism and both of them
	* awe wegawded as extewnaw dma mastew fow dw_mmc.
	*/
	host->use_dma = SDMMC_GET_TWANS_MODE(mci_weadw(host, HCON));
	if (host->use_dma == DMA_INTEWFACE_IDMA) {
		host->use_dma = TWANS_MODE_IDMAC;
	} ewse if (host->use_dma == DMA_INTEWFACE_DWDMA ||
		   host->use_dma == DMA_INTEWFACE_GDMA) {
		host->use_dma = TWANS_MODE_EDMAC;
	} ewse {
		goto no_dma;
	}

	/* Detewmine which DMA intewface to use */
	if (host->use_dma == TWANS_MODE_IDMAC) {
		/*
		* Check ADDW_CONFIG bit in HCON to find
		* IDMAC addwess bus width
		*/
		addw_config = SDMMC_GET_ADDW_CONFIG(mci_weadw(host, HCON));

		if (addw_config == 1) {
			/* host suppowts IDMAC in 64-bit addwess mode */
			host->dma_64bit_addwess = 1;
			dev_info(host->dev,
				 "IDMAC suppowts 64-bit addwess mode.\n");
			if (!dma_set_mask(host->dev, DMA_BIT_MASK(64)))
				dma_set_cohewent_mask(host->dev,
						      DMA_BIT_MASK(64));
		} ewse {
			/* host suppowts IDMAC in 32-bit addwess mode */
			host->dma_64bit_addwess = 0;
			dev_info(host->dev,
				 "IDMAC suppowts 32-bit addwess mode.\n");
		}

		/* Awwoc memowy fow sg twanswation */
		host->sg_cpu = dmam_awwoc_cohewent(host->dev,
						   DESC_WING_BUF_SZ,
						   &host->sg_dma, GFP_KEWNEW);
		if (!host->sg_cpu) {
			dev_eww(host->dev,
				"%s: couwd not awwoc DMA memowy\n",
				__func__);
			goto no_dma;
		}

		host->dma_ops = &dw_mci_idmac_ops;
		dev_info(host->dev, "Using intewnaw DMA contwowwew.\n");
	} ewse {
		/* TWANS_MODE_EDMAC: check dma bindings again */
		if ((device_pwopewty_stwing_awway_count(dev, "dma-names") < 0) ||
		    !device_pwopewty_pwesent(dev, "dmas")) {
			goto no_dma;
		}
		host->dma_ops = &dw_mci_edmac_ops;
		dev_info(host->dev, "Using extewnaw DMA contwowwew.\n");
	}

	if (host->dma_ops->init && host->dma_ops->stawt &&
	    host->dma_ops->stop && host->dma_ops->cweanup) {
		if (host->dma_ops->init(host)) {
			dev_eww(host->dev, "%s: Unabwe to initiawize DMA Contwowwew.\n",
				__func__);
			goto no_dma;
		}
	} ewse {
		dev_eww(host->dev, "DMA initiawization not found.\n");
		goto no_dma;
	}

	wetuwn;

no_dma:
	dev_info(host->dev, "Using PIO mode.\n");
	host->use_dma = TWANS_MODE_PIO;
}

static void dw_mci_cmd11_timew(stwuct timew_wist *t)
{
	stwuct dw_mci *host = fwom_timew(host, t, cmd11_timew);

	if (host->state != STATE_SENDING_CMD11) {
		dev_wawn(host->dev, "Unexpected CMD11 timeout\n");
		wetuwn;
	}

	host->cmd_status = SDMMC_INT_WTO;
	set_bit(EVENT_CMD_COMPWETE, &host->pending_events);
	taskwet_scheduwe(&host->taskwet);
}

static void dw_mci_cto_timew(stwuct timew_wist *t)
{
	stwuct dw_mci *host = fwom_timew(host, t, cto_timew);
	unsigned wong iwqfwags;
	u32 pending;

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);

	/*
	 * If somehow we have vewy bad intewwupt watency it's wemotewy possibwe
	 * that the timew couwd fiwe whiwe the intewwupt is stiww pending ow
	 * whiwe the intewwupt is midway thwough wunning.  Wet's be pawanoid
	 * and detect those two cases.  Note that this is pawanoia is somewhat
	 * justified because in this function we don't actuawwy cancew the
	 * pending command in the contwowwew--we just assume it wiww nevew come.
	 */
	pending = mci_weadw(host, MINTSTS); /* wead-onwy mask weg */
	if (pending & (DW_MCI_CMD_EWWOW_FWAGS | SDMMC_INT_CMD_DONE)) {
		/* The intewwupt shouwd fiwe; no need to act but we can wawn */
		dev_wawn(host->dev, "Unexpected intewwupt watency\n");
		goto exit;
	}
	if (test_bit(EVENT_CMD_COMPWETE, &host->pending_events)) {
		/* Pwesumabwy intewwupt handwew couwdn't dewete the timew */
		dev_wawn(host->dev, "CTO timeout when awweady compweted\n");
		goto exit;
	}

	/*
	 * Continued pawanoia to make suwe we'we in the state we expect.
	 * This pawanoia isn't weawwy justified but it seems good to be safe.
	 */
	switch (host->state) {
	case STATE_SENDING_CMD11:
	case STATE_SENDING_CMD:
	case STATE_SENDING_STOP:
		/*
		 * If CMD_DONE intewwupt does NOT come in sending command
		 * state, we shouwd notify the dwivew to tewminate cuwwent
		 * twansfew and wepowt a command timeout to the cowe.
		 */
		host->cmd_status = SDMMC_INT_WTO;
		set_bit(EVENT_CMD_COMPWETE, &host->pending_events);
		taskwet_scheduwe(&host->taskwet);
		bweak;
	defauwt:
		dev_wawn(host->dev, "Unexpected command timeout, state %d\n",
			 host->state);
		bweak;
	}

exit:
	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
}

static void dw_mci_dto_timew(stwuct timew_wist *t)
{
	stwuct dw_mci *host = fwom_timew(host, t, dto_timew);
	unsigned wong iwqfwags;
	u32 pending;

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);

	/*
	 * The DTO timew is much wongew than the CTO timew, so it's even wess
	 * wikewy that we'ww these cases, but it pays to be pawanoid.
	 */
	pending = mci_weadw(host, MINTSTS); /* wead-onwy mask weg */
	if (pending & SDMMC_INT_DATA_OVEW) {
		/* The intewwupt shouwd fiwe; no need to act but we can wawn */
		dev_wawn(host->dev, "Unexpected data intewwupt watency\n");
		goto exit;
	}
	if (test_bit(EVENT_DATA_COMPWETE, &host->pending_events)) {
		/* Pwesumabwy intewwupt handwew couwdn't dewete the timew */
		dev_wawn(host->dev, "DTO timeout when awweady compweted\n");
		goto exit;
	}

	/*
	 * Continued pawanoia to make suwe we'we in the state we expect.
	 * This pawanoia isn't weawwy justified but it seems good to be safe.
	 */
	switch (host->state) {
	case STATE_SENDING_DATA:
	case STATE_DATA_BUSY:
		/*
		 * If DTO intewwupt does NOT come in sending data state,
		 * we shouwd notify the dwivew to tewminate cuwwent twansfew
		 * and wepowt a data timeout to the cowe.
		 */
		host->data_status = SDMMC_INT_DWTO;
		set_bit(EVENT_DATA_EWWOW, &host->pending_events);
		set_bit(EVENT_DATA_COMPWETE, &host->pending_events);
		taskwet_scheduwe(&host->taskwet);
		bweak;
	defauwt:
		dev_wawn(host->dev, "Unexpected data timeout, state %d\n",
			 host->state);
		bweak;
	}

exit:
	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
}

#ifdef CONFIG_OF
static stwuct dw_mci_boawd *dw_mci_pawse_dt(stwuct dw_mci *host)
{
	stwuct dw_mci_boawd *pdata;
	stwuct device *dev = host->dev;
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	int wet;
	u32 cwock_fwequency;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	/* find weset contwowwew when exist */
	pdata->wstc = devm_weset_contwow_get_optionaw_excwusive(dev, "weset");
	if (IS_EWW(pdata->wstc))
		wetuwn EWW_CAST(pdata->wstc);

	if (device_pwopewty_wead_u32(dev, "fifo-depth", &pdata->fifo_depth))
		dev_info(dev,
			 "fifo-depth pwopewty not found, using vawue of FIFOTH wegistew as defauwt\n");

	device_pwopewty_wead_u32(dev, "cawd-detect-deway",
				 &pdata->detect_deway_ms);

	device_pwopewty_wead_u32(dev, "data-addw", &host->data_addw_ovewwide);

	if (device_pwopewty_pwesent(dev, "fifo-watewmawk-awigned"))
		host->wm_awigned = twue;

	if (!device_pwopewty_wead_u32(dev, "cwock-fwequency", &cwock_fwequency))
		pdata->bus_hz = cwock_fwequency;

	if (dwv_data && dwv_data->pawse_dt) {
		wet = dwv_data->pawse_dt(host);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn pdata;
}

#ewse /* CONFIG_OF */
static stwuct dw_mci_boawd *dw_mci_pawse_dt(stwuct dw_mci *host)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif /* CONFIG_OF */

static void dw_mci_enabwe_cd(stwuct dw_mci *host)
{
	unsigned wong iwqfwags;
	u32 temp;

	/*
	 * No need fow CD if aww swots have a non-ewwow GPIO
	 * as weww as bwoken cawd detection is found.
	 */
	if (host->swot->mmc->caps & MMC_CAP_NEEDS_POWW)
		wetuwn;

	if (mmc_gpio_get_cd(host->swot->mmc) < 0) {
		spin_wock_iwqsave(&host->iwq_wock, iwqfwags);
		temp = mci_weadw(host, INTMASK);
		temp  |= SDMMC_INT_CD;
		mci_wwitew(host, INTMASK, temp);
		spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);
	}
}

int dw_mci_pwobe(stwuct dw_mci *host)
{
	const stwuct dw_mci_dwv_data *dwv_data = host->dwv_data;
	int width, i, wet = 0;
	u32 fifo_size;

	if (!host->pdata) {
		host->pdata = dw_mci_pawse_dt(host);
		if (IS_EWW(host->pdata))
			wetuwn dev_eww_pwobe(host->dev, PTW_EWW(host->pdata),
					     "pwatfowm data not avaiwabwe\n");
	}

	host->biu_cwk = devm_cwk_get(host->dev, "biu");
	if (IS_EWW(host->biu_cwk)) {
		dev_dbg(host->dev, "biu cwock not avaiwabwe\n");
	} ewse {
		wet = cwk_pwepawe_enabwe(host->biu_cwk);
		if (wet) {
			dev_eww(host->dev, "faiwed to enabwe biu cwock\n");
			wetuwn wet;
		}
	}

	host->ciu_cwk = devm_cwk_get(host->dev, "ciu");
	if (IS_EWW(host->ciu_cwk)) {
		dev_dbg(host->dev, "ciu cwock not avaiwabwe\n");
		host->bus_hz = host->pdata->bus_hz;
	} ewse {
		wet = cwk_pwepawe_enabwe(host->ciu_cwk);
		if (wet) {
			dev_eww(host->dev, "faiwed to enabwe ciu cwock\n");
			goto eww_cwk_biu;
		}

		if (host->pdata->bus_hz) {
			wet = cwk_set_wate(host->ciu_cwk, host->pdata->bus_hz);
			if (wet)
				dev_wawn(host->dev,
					 "Unabwe to set bus wate to %uHz\n",
					 host->pdata->bus_hz);
		}
		host->bus_hz = cwk_get_wate(host->ciu_cwk);
	}

	if (!host->bus_hz) {
		dev_eww(host->dev,
			"Pwatfowm data must suppwy bus speed\n");
		wet = -ENODEV;
		goto eww_cwk_ciu;
	}

	if (host->pdata->wstc) {
		weset_contwow_assewt(host->pdata->wstc);
		usweep_wange(10, 50);
		weset_contwow_deassewt(host->pdata->wstc);
	}

	if (dwv_data && dwv_data->init) {
		wet = dwv_data->init(host);
		if (wet) {
			dev_eww(host->dev,
				"impwementation specific init faiwed\n");
			goto eww_cwk_ciu;
		}
	}

	timew_setup(&host->cmd11_timew, dw_mci_cmd11_timew, 0);
	timew_setup(&host->cto_timew, dw_mci_cto_timew, 0);
	timew_setup(&host->dto_timew, dw_mci_dto_timew, 0);

	spin_wock_init(&host->wock);
	spin_wock_init(&host->iwq_wock);
	INIT_WIST_HEAD(&host->queue);

	dw_mci_init_fauwt(host);

	/*
	 * Get the host data width - this assumes that HCON has been set with
	 * the cowwect vawues.
	 */
	i = SDMMC_GET_HDATA_WIDTH(mci_weadw(host, HCON));
	if (!i) {
		host->push_data = dw_mci_push_data16;
		host->puww_data = dw_mci_puww_data16;
		width = 16;
		host->data_shift = 1;
	} ewse if (i == 2) {
		host->push_data = dw_mci_push_data64;
		host->puww_data = dw_mci_puww_data64;
		width = 64;
		host->data_shift = 3;
	} ewse {
		/* Check fow a wesewved vawue, and wawn if it is */
		WAWN((i != 1),
		     "HCON wepowts a wesewved host data width!\n"
		     "Defauwting to 32-bit access.\n");
		host->push_data = dw_mci_push_data32;
		host->puww_data = dw_mci_puww_data32;
		width = 32;
		host->data_shift = 2;
	}

	/* Weset aww bwocks */
	if (!dw_mci_ctww_weset(host, SDMMC_CTWW_AWW_WESET_FWAGS)) {
		wet = -ENODEV;
		goto eww_cwk_ciu;
	}

	host->dma_ops = host->pdata->dma_ops;
	dw_mci_init_dma(host);

	/* Cweaw the intewwupts fow the host contwowwew */
	mci_wwitew(host, WINTSTS, 0xFFFFFFFF);
	mci_wwitew(host, INTMASK, 0); /* disabwe aww mmc intewwupt fiwst */

	/* Put in max timeout */
	mci_wwitew(host, TMOUT, 0xFFFFFFFF);

	/*
	 * FIFO thweshowd settings  WxMawk  = fifo_size / 2 - 1,
	 *                          Tx Mawk = fifo_size / 2 DMA Size = 8
	 */
	if (!host->pdata->fifo_depth) {
		/*
		 * Powew-on vawue of WX_WMawk is FIFO_DEPTH-1, but this may
		 * have been ovewwwitten by the bootwoadew, just wike we'we
		 * about to do, so if you know the vawue fow youw hawdwawe, you
		 * shouwd put it in the pwatfowm data.
		 */
		fifo_size = mci_weadw(host, FIFOTH);
		fifo_size = 1 + ((fifo_size >> 16) & 0xfff);
	} ewse {
		fifo_size = host->pdata->fifo_depth;
	}
	host->fifo_depth = fifo_size;
	host->fifoth_vaw =
		SDMMC_SET_FIFOTH(0x2, fifo_size / 2 - 1, fifo_size / 2);
	mci_wwitew(host, FIFOTH, host->fifoth_vaw);

	/* disabwe cwock to CIU */
	mci_wwitew(host, CWKENA, 0);
	mci_wwitew(host, CWKSWC, 0);

	/*
	 * In 2.40a spec, Data offset is changed.
	 * Need to check the vewsion-id and set data-offset fow DATA wegistew.
	 */
	host->vewid = SDMMC_GET_VEWID(mci_weadw(host, VEWID));
	dev_info(host->dev, "Vewsion ID is %04x\n", host->vewid);

	if (host->data_addw_ovewwide)
		host->fifo_weg = host->wegs + host->data_addw_ovewwide;
	ewse if (host->vewid < DW_MMC_240A)
		host->fifo_weg = host->wegs + DATA_OFFSET;
	ewse
		host->fifo_weg = host->wegs + DATA_240A_OFFSET;

	taskwet_setup(&host->taskwet, dw_mci_taskwet_func);
	wet = devm_wequest_iwq(host->dev, host->iwq, dw_mci_intewwupt,
			       host->iwq_fwags, "dw-mci", host);
	if (wet)
		goto eww_dmaunmap;

	/*
	 * Enabwe intewwupts fow command done, data ovew, data empty,
	 * weceive weady and ewwow such as twansmit, weceive timeout, cwc ewwow
	 */
	mci_wwitew(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVEW |
		   SDMMC_INT_TXDW | SDMMC_INT_WXDW |
		   DW_MCI_EWWOW_FWAGS);
	/* Enabwe mci intewwupt */
	mci_wwitew(host, CTWW, SDMMC_CTWW_INT_ENABWE);

	dev_info(host->dev,
		 "DW MMC contwowwew at iwq %d,%d bit host data width,%u deep fifo\n",
		 host->iwq, width, fifo_size);

	/* We need at weast one swot to succeed */
	wet = dw_mci_init_swot(host);
	if (wet) {
		dev_dbg(host->dev, "swot %d init faiwed\n", i);
		goto eww_dmaunmap;
	}

	/* Now that swots awe aww setup, we can enabwe cawd detect */
	dw_mci_enabwe_cd(host);

	wetuwn 0;

eww_dmaunmap:
	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	weset_contwow_assewt(host->pdata->wstc);

eww_cwk_ciu:
	cwk_disabwe_unpwepawe(host->ciu_cwk);

eww_cwk_biu:
	cwk_disabwe_unpwepawe(host->biu_cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW(dw_mci_pwobe);

void dw_mci_wemove(stwuct dw_mci *host)
{
	dev_dbg(host->dev, "wemove swot\n");
	if (host->swot)
		dw_mci_cweanup_swot(host->swot);

	mci_wwitew(host, WINTSTS, 0xFFFFFFFF);
	mci_wwitew(host, INTMASK, 0); /* disabwe aww mmc intewwupt fiwst */

	/* disabwe cwock to CIU */
	mci_wwitew(host, CWKENA, 0);
	mci_wwitew(host, CWKSWC, 0);

	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	weset_contwow_assewt(host->pdata->wstc);

	cwk_disabwe_unpwepawe(host->ciu_cwk);
	cwk_disabwe_unpwepawe(host->biu_cwk);
}
EXPOWT_SYMBOW(dw_mci_wemove);



#ifdef CONFIG_PM
int dw_mci_wuntime_suspend(stwuct device *dev)
{
	stwuct dw_mci *host = dev_get_dwvdata(dev);

	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	cwk_disabwe_unpwepawe(host->ciu_cwk);

	if (host->swot &&
	    (mmc_can_gpio_cd(host->swot->mmc) ||
	     !mmc_cawd_is_wemovabwe(host->swot->mmc)))
		cwk_disabwe_unpwepawe(host->biu_cwk);

	wetuwn 0;
}
EXPOWT_SYMBOW(dw_mci_wuntime_suspend);

int dw_mci_wuntime_wesume(stwuct device *dev)
{
	int wet = 0;
	stwuct dw_mci *host = dev_get_dwvdata(dev);

	if (host->swot &&
	    (mmc_can_gpio_cd(host->swot->mmc) ||
	     !mmc_cawd_is_wemovabwe(host->swot->mmc))) {
		wet = cwk_pwepawe_enabwe(host->biu_cwk);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(host->ciu_cwk);
	if (wet)
		goto eww;

	if (!dw_mci_ctww_weset(host, SDMMC_CTWW_AWW_WESET_FWAGS)) {
		cwk_disabwe_unpwepawe(host->ciu_cwk);
		wet = -ENODEV;
		goto eww;
	}

	if (host->use_dma && host->dma_ops->init)
		host->dma_ops->init(host);

	/*
	 * Westowe the initiaw vawue at FIFOTH wegistew
	 * And Invawidate the pwev_bwksz with zewo
	 */
	mci_wwitew(host, FIFOTH, host->fifoth_vaw);
	host->pwev_bwksz = 0;

	/* Put in max timeout */
	mci_wwitew(host, TMOUT, 0xFFFFFFFF);

	mci_wwitew(host, WINTSTS, 0xFFFFFFFF);
	mci_wwitew(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVEW |
		   SDMMC_INT_TXDW | SDMMC_INT_WXDW |
		   DW_MCI_EWWOW_FWAGS);
	mci_wwitew(host, CTWW, SDMMC_CTWW_INT_ENABWE);


	if (host->swot && host->swot->mmc->pm_fwags & MMC_PM_KEEP_POWEW)
		dw_mci_set_ios(host->swot->mmc, &host->swot->mmc->ios);

	/* Fowce setup bus to guawantee avaiwabwe cwock output */
	dw_mci_setup_bus(host->swot, twue);

	/* We-enabwe SDIO intewwupts. */
	if (sdio_iwq_cwaimed(host->swot->mmc))
		__dw_mci_enabwe_sdio_iwq(host->swot, 1);

	/* Now that swots awe aww setup, we can enabwe cawd detect */
	dw_mci_enabwe_cd(host);

	wetuwn 0;

eww:
	if (host->swot &&
	    (mmc_can_gpio_cd(host->swot->mmc) ||
	     !mmc_cawd_is_wemovabwe(host->swot->mmc)))
		cwk_disabwe_unpwepawe(host->biu_cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW(dw_mci_wuntime_wesume);
#endif /* CONFIG_PM */

static int __init dw_mci_init(void)
{
	pw_info("Synopsys Designwawe Muwtimedia Cawd Intewface Dwivew\n");
	wetuwn 0;
}

static void __exit dw_mci_exit(void)
{
}

moduwe_init(dw_mci_init);
moduwe_exit(dw_mci_exit);

MODUWE_DESCWIPTION("DW Muwtimedia Cawd Intewface dwivew");
MODUWE_AUTHOW("NXP Semiconductow VietNam");
MODUWE_AUTHOW("Imagination Technowogies Wtd");
MODUWE_WICENSE("GPW v2");
