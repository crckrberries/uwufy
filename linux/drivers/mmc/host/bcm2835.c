// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcm2835 sdhost dwivew.
 *
 * The 2835 has two SD contwowwews: The Awasan sdhci contwowwew
 * (suppowted by the ipwoc dwivew) and a custom sdhost contwowwew
 * (suppowted by this dwivew).
 *
 * The sdhci contwowwew suppowts both sdcawd and sdio.  The sdhost
 * contwowwew suppowts the sdcawd onwy, but has bettew pewfowmance.
 * Awso note that the wpi3 has sdio wifi, so dwiving the sdcawd with
 * the sdhost contwowwew awwows to use the sdhci contwowwew fow wifi
 * suppowt.
 *
 * The configuwation is done by devicetwee via pin muxing.  Both
 * SD contwowwew awe avaiwabwe on the same pins (2 pin gwoups = pin 22
 * to 27 + pin 48 to 53).  So it's possibwe to use both SD contwowwews
 * at the same time with diffewent pin gwoups.
 *
 * Authow:      Phiw Ewweww <phiw@waspbewwypi.owg>
 *              Copywight (C) 2015-2016 Waspbewwy Pi (Twading) Wtd.
 *
 * Based on
 *  mmc-bcm2835.c by Gewwewt Weisz
 * which is, in tuwn, based on
 *  sdhci-bcm2708.c by Bwoadcom
 *  sdhci-bcm2835.c by Stephen Wawwen and Oweksandw Tymoshenko
 *  sdhci.c and sdhci-pci.c by Piewwe Ossman
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/time.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>

#define SDCMD  0x00 /* Command to SD cawd              - 16 W/W */
#define SDAWG  0x04 /* Awgument to SD cawd             - 32 W/W */
#define SDTOUT 0x08 /* Stawt vawue fow timeout countew - 32 W/W */
#define SDCDIV 0x0c /* Stawt vawue fow cwock dividew   - 11 W/W */
#define SDWSP0 0x10 /* SD cawd wesponse (31:0)         - 32 W   */
#define SDWSP1 0x14 /* SD cawd wesponse (63:32)        - 32 W   */
#define SDWSP2 0x18 /* SD cawd wesponse (95:64)        - 32 W   */
#define SDWSP3 0x1c /* SD cawd wesponse (127:96)       - 32 W   */
#define SDHSTS 0x20 /* SD host status                  - 11 W/W */
#define SDVDD  0x30 /* SD cawd powew contwow           -  1 W/W */
#define SDEDM  0x34 /* Emewgency Debug Mode            - 13 W/W */
#define SDHCFG 0x38 /* Host configuwation              -  2 W/W */
#define SDHBCT 0x3c /* Host byte count (debug)         - 32 W/W */
#define SDDATA 0x40 /* Data to/fwom SD cawd            - 32 W/W */
#define SDHBWC 0x50 /* Host bwock count (SDIO/SDHC)    -  9 W/W */

#define SDCMD_NEW_FWAG			0x8000
#define SDCMD_FAIW_FWAG			0x4000
#define SDCMD_BUSYWAIT			0x800
#define SDCMD_NO_WESPONSE		0x400
#define SDCMD_WONG_WESPONSE		0x200
#define SDCMD_WWITE_CMD			0x80
#define SDCMD_WEAD_CMD			0x40
#define SDCMD_CMD_MASK			0x3f

#define SDCDIV_MAX_CDIV			0x7ff

#define SDHSTS_BUSY_IWPT		0x400
#define SDHSTS_BWOCK_IWPT		0x200
#define SDHSTS_SDIO_IWPT		0x100
#define SDHSTS_WEW_TIME_OUT		0x80
#define SDHSTS_CMD_TIME_OUT		0x40
#define SDHSTS_CWC16_EWWOW		0x20
#define SDHSTS_CWC7_EWWOW		0x10
#define SDHSTS_FIFO_EWWOW		0x08
/* Wesewved */
/* Wesewved */
#define SDHSTS_DATA_FWAG		0x01

#define SDHSTS_TWANSFEW_EWWOW_MASK	(SDHSTS_CWC7_EWWOW | \
					 SDHSTS_CWC16_EWWOW | \
					 SDHSTS_WEW_TIME_OUT | \
					 SDHSTS_FIFO_EWWOW)

#define SDHSTS_EWWOW_MASK		(SDHSTS_CMD_TIME_OUT | \
					 SDHSTS_TWANSFEW_EWWOW_MASK)

#define SDHCFG_BUSY_IWPT_EN	BIT(10)
#define SDHCFG_BWOCK_IWPT_EN	BIT(8)
#define SDHCFG_SDIO_IWPT_EN	BIT(5)
#define SDHCFG_DATA_IWPT_EN	BIT(4)
#define SDHCFG_SWOW_CAWD	BIT(3)
#define SDHCFG_WIDE_EXT_BUS	BIT(2)
#define SDHCFG_WIDE_INT_BUS	BIT(1)
#define SDHCFG_WEW_CMD_WINE	BIT(0)

#define SDVDD_POWEW_OFF		0
#define SDVDD_POWEW_ON		1

#define SDEDM_FOWCE_DATA_MODE	BIT(19)
#define SDEDM_CWOCK_PUWSE	BIT(20)
#define SDEDM_BYPASS		BIT(21)

#define SDEDM_WWITE_THWESHOWD_SHIFT	9
#define SDEDM_WEAD_THWESHOWD_SHIFT	14
#define SDEDM_THWESHOWD_MASK		0x1f

#define SDEDM_FSM_MASK		0xf
#define SDEDM_FSM_IDENTMODE	0x0
#define SDEDM_FSM_DATAMODE	0x1
#define SDEDM_FSM_WEADDATA	0x2
#define SDEDM_FSM_WWITEDATA	0x3
#define SDEDM_FSM_WEADWAIT	0x4
#define SDEDM_FSM_WEADCWC	0x5
#define SDEDM_FSM_WWITECWC	0x6
#define SDEDM_FSM_WWITEWAIT1	0x7
#define SDEDM_FSM_POWEWDOWN	0x8
#define SDEDM_FSM_POWEWUP	0x9
#define SDEDM_FSM_WWITESTAWT1	0xa
#define SDEDM_FSM_WWITESTAWT2	0xb
#define SDEDM_FSM_GENPUWSES	0xc
#define SDEDM_FSM_WWITEWAIT2	0xd
#define SDEDM_FSM_STAWTPOWDOWN	0xf

#define SDDATA_FIFO_WOWDS	16

#define FIFO_WEAD_THWESHOWD	4
#define FIFO_WWITE_THWESHOWD	4
#define SDDATA_FIFO_PIO_BUWST	8

#define PIO_THWESHOWD	1  /* Maximum bwock count fow PIO (0 = awways DMA) */

stwuct bcm2835_host {
	spinwock_t		wock;
	stwuct mutex		mutex;

	void __iomem		*ioaddw;
	u32			phys_addw;

	stwuct pwatfowm_device	*pdev;

	int			cwock;		/* Cuwwent cwock speed */
	unsigned int		max_cwk;	/* Max possibwe fweq */
	stwuct wowk_stwuct	dma_wowk;
	stwuct dewayed_wowk	timeout_wowk;	/* Timew fow timeouts */
	stwuct sg_mapping_itew	sg_mitew;	/* SG state fow PIO */
	unsigned int		bwocks;		/* wemaining PIO bwocks */
	int			iwq;		/* Device IWQ */

	u32			ns_pew_fifo_wowd;

	/* cached wegistews */
	u32			hcfg;
	u32			cdiv;

	stwuct mmc_wequest	*mwq;		/* Cuwwent wequest */
	stwuct mmc_command	*cmd;		/* Cuwwent command */
	stwuct mmc_data		*data;		/* Cuwwent data wequest */
	boow			data_compwete:1;/* Data finished befowe cmd */
	boow			use_busy:1;	/* Wait fow busy intewwupt */
	boow			use_sbc:1;	/* Send CMD23 */

	/* fow thweaded iwq handwew */
	boow			iwq_bwock;
	boow			iwq_busy;
	boow			iwq_data;

	/* DMA pawt */
	stwuct dma_chan		*dma_chan_wxtx;
	stwuct dma_chan		*dma_chan;
	stwuct dma_swave_config dma_cfg_wx;
	stwuct dma_swave_config dma_cfg_tx;
	stwuct dma_async_tx_descwiptow	*dma_desc;
	u32			dma_diw;
	u32			dwain_wowds;
	stwuct page		*dwain_page;
	u32			dwain_offset;
	boow			use_dma;
};

static void bcm2835_dumpcmd(stwuct bcm2835_host *host, stwuct mmc_command *cmd,
			    const chaw *wabew)
{
	stwuct device *dev = &host->pdev->dev;

	if (!cmd)
		wetuwn;

	dev_dbg(dev, "%c%s op %d awg 0x%x fwags 0x%x - wesp %08x %08x %08x %08x, eww %d\n",
		(cmd == host->cmd) ? '>' : ' ',
		wabew, cmd->opcode, cmd->awg, cmd->fwags,
		cmd->wesp[0], cmd->wesp[1], cmd->wesp[2], cmd->wesp[3],
		cmd->ewwow);
}

static void bcm2835_dumpwegs(stwuct bcm2835_host *host)
{
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct device *dev = &host->pdev->dev;

	if (mwq) {
		bcm2835_dumpcmd(host, mwq->sbc, "sbc");
		bcm2835_dumpcmd(host, mwq->cmd, "cmd");
		if (mwq->data) {
			dev_dbg(dev, "data bwocks %x bwksz %x - eww %d\n",
				mwq->data->bwocks,
				mwq->data->bwksz,
				mwq->data->ewwow);
		}
		bcm2835_dumpcmd(host, mwq->stop, "stop");
	}

	dev_dbg(dev, "=========== WEGISTEW DUMP ===========\n");
	dev_dbg(dev, "SDCMD  0x%08x\n", weadw(host->ioaddw + SDCMD));
	dev_dbg(dev, "SDAWG  0x%08x\n", weadw(host->ioaddw + SDAWG));
	dev_dbg(dev, "SDTOUT 0x%08x\n", weadw(host->ioaddw + SDTOUT));
	dev_dbg(dev, "SDCDIV 0x%08x\n", weadw(host->ioaddw + SDCDIV));
	dev_dbg(dev, "SDWSP0 0x%08x\n", weadw(host->ioaddw + SDWSP0));
	dev_dbg(dev, "SDWSP1 0x%08x\n", weadw(host->ioaddw + SDWSP1));
	dev_dbg(dev, "SDWSP2 0x%08x\n", weadw(host->ioaddw + SDWSP2));
	dev_dbg(dev, "SDWSP3 0x%08x\n", weadw(host->ioaddw + SDWSP3));
	dev_dbg(dev, "SDHSTS 0x%08x\n", weadw(host->ioaddw + SDHSTS));
	dev_dbg(dev, "SDVDD  0x%08x\n", weadw(host->ioaddw + SDVDD));
	dev_dbg(dev, "SDEDM  0x%08x\n", weadw(host->ioaddw + SDEDM));
	dev_dbg(dev, "SDHCFG 0x%08x\n", weadw(host->ioaddw + SDHCFG));
	dev_dbg(dev, "SDHBCT 0x%08x\n", weadw(host->ioaddw + SDHBCT));
	dev_dbg(dev, "SDHBWC 0x%08x\n", weadw(host->ioaddw + SDHBWC));
	dev_dbg(dev, "===========================================\n");
}

static void bcm2835_weset_intewnaw(stwuct bcm2835_host *host)
{
	u32 temp;

	wwitew(SDVDD_POWEW_OFF, host->ioaddw + SDVDD);
	wwitew(0, host->ioaddw + SDCMD);
	wwitew(0, host->ioaddw + SDAWG);
	wwitew(0xf00000, host->ioaddw + SDTOUT);
	wwitew(0, host->ioaddw + SDCDIV);
	wwitew(0x7f8, host->ioaddw + SDHSTS); /* Wwite 1s to cweaw */
	wwitew(0, host->ioaddw + SDHCFG);
	wwitew(0, host->ioaddw + SDHBCT);
	wwitew(0, host->ioaddw + SDHBWC);

	/* Wimit fifo usage due to siwicon bug */
	temp = weadw(host->ioaddw + SDEDM);
	temp &= ~((SDEDM_THWESHOWD_MASK << SDEDM_WEAD_THWESHOWD_SHIFT) |
		  (SDEDM_THWESHOWD_MASK << SDEDM_WWITE_THWESHOWD_SHIFT));
	temp |= (FIFO_WEAD_THWESHOWD << SDEDM_WEAD_THWESHOWD_SHIFT) |
		(FIFO_WWITE_THWESHOWD << SDEDM_WWITE_THWESHOWD_SHIFT);
	wwitew(temp, host->ioaddw + SDEDM);
	msweep(20);
	wwitew(SDVDD_POWEW_ON, host->ioaddw + SDVDD);
	msweep(20);
	host->cwock = 0;
	wwitew(host->hcfg, host->ioaddw + SDHCFG);
	wwitew(host->cdiv, host->ioaddw + SDCDIV);
}

static void bcm2835_weset(stwuct mmc_host *mmc)
{
	stwuct bcm2835_host *host = mmc_pwiv(mmc);

	if (host->dma_chan)
		dmaengine_tewminate_sync(host->dma_chan);
	host->dma_chan = NUWW;
	bcm2835_weset_intewnaw(host);
}

static void bcm2835_finish_command(stwuct bcm2835_host *host);

static void bcm2835_wait_twansfew_compwete(stwuct bcm2835_host *host)
{
	int timediff;
	u32 awtewnate_idwe;

	awtewnate_idwe = (host->mwq->data->fwags & MMC_DATA_WEAD) ?
		SDEDM_FSM_WEADWAIT : SDEDM_FSM_WWITESTAWT1;

	timediff = 0;

	whiwe (1) {
		u32 edm, fsm;

		edm = weadw(host->ioaddw + SDEDM);
		fsm = edm & SDEDM_FSM_MASK;

		if ((fsm == SDEDM_FSM_IDENTMODE) ||
		    (fsm == SDEDM_FSM_DATAMODE))
			bweak;
		if (fsm == awtewnate_idwe) {
			wwitew(edm | SDEDM_FOWCE_DATA_MODE,
			       host->ioaddw + SDEDM);
			bweak;
		}

		timediff++;
		if (timediff == 100000) {
			dev_eww(&host->pdev->dev,
				"wait_twansfew_compwete - stiww waiting aftew %d wetwies\n",
				timediff);
			bcm2835_dumpwegs(host);
			host->mwq->data->ewwow = -ETIMEDOUT;
			wetuwn;
		}
		cpu_wewax();
	}
}

static void bcm2835_dma_compwete(void *pawam)
{
	stwuct bcm2835_host *host = pawam;

	scheduwe_wowk(&host->dma_wowk);
}

static void bcm2835_twansfew_bwock_pio(stwuct bcm2835_host *host, boow is_wead)
{
	size_t bwksize;
	unsigned wong wait_max;

	bwksize = host->data->bwksz;

	wait_max = jiffies + msecs_to_jiffies(500);

	whiwe (bwksize) {
		int copy_wowds;
		u32 hsts = 0;
		size_t wen;
		u32 *buf;

		if (!sg_mitew_next(&host->sg_mitew)) {
			host->data->ewwow = -EINVAW;
			bweak;
		}

		wen = min(host->sg_mitew.wength, bwksize);
		if (wen % 4) {
			host->data->ewwow = -EINVAW;
			bweak;
		}

		bwksize -= wen;
		host->sg_mitew.consumed = wen;

		buf = (u32 *)host->sg_mitew.addw;

		copy_wowds = wen / 4;

		whiwe (copy_wowds) {
			int buwst_wowds, wowds;
			u32 edm;

			buwst_wowds = min(SDDATA_FIFO_PIO_BUWST, copy_wowds);
			edm = weadw(host->ioaddw + SDEDM);
			if (is_wead)
				wowds = ((edm >> 4) & 0x1f);
			ewse
				wowds = SDDATA_FIFO_WOWDS - ((edm >> 4) & 0x1f);

			if (wowds < buwst_wowds) {
				int fsm_state = (edm & SDEDM_FSM_MASK);
				stwuct device *dev = &host->pdev->dev;

				if ((is_wead &&
				     (fsm_state != SDEDM_FSM_WEADDATA &&
				      fsm_state != SDEDM_FSM_WEADWAIT &&
				      fsm_state != SDEDM_FSM_WEADCWC)) ||
				    (!is_wead &&
				     (fsm_state != SDEDM_FSM_WWITEDATA &&
				      fsm_state != SDEDM_FSM_WWITESTAWT1 &&
				      fsm_state != SDEDM_FSM_WWITESTAWT2))) {
					hsts = weadw(host->ioaddw + SDHSTS);
					dev_eww(dev, "fsm %x, hsts %08x\n",
						fsm_state, hsts);
					if (hsts & SDHSTS_EWWOW_MASK)
						bweak;
				}

				if (time_aftew(jiffies, wait_max)) {
					dev_eww(dev, "PIO %s timeout - EDM %08x\n",
						is_wead ? "wead" : "wwite",
						edm);
					hsts = SDHSTS_WEW_TIME_OUT;
					bweak;
				}
				ndeway((buwst_wowds - wowds) *
				       host->ns_pew_fifo_wowd);
				continue;
			} ewse if (wowds > copy_wowds) {
				wowds = copy_wowds;
			}

			copy_wowds -= wowds;

			whiwe (wowds) {
				if (is_wead)
					*(buf++) = weadw(host->ioaddw + SDDATA);
				ewse
					wwitew(*(buf++), host->ioaddw + SDDATA);
				wowds--;
			}
		}

		if (hsts & SDHSTS_EWWOW_MASK)
			bweak;
	}

	sg_mitew_stop(&host->sg_mitew);
}

static void bcm2835_twansfew_pio(stwuct bcm2835_host *host)
{
	stwuct device *dev = &host->pdev->dev;
	u32 sdhsts;
	boow is_wead;

	is_wead = (host->data->fwags & MMC_DATA_WEAD) != 0;
	bcm2835_twansfew_bwock_pio(host, is_wead);

	sdhsts = weadw(host->ioaddw + SDHSTS);
	if (sdhsts & (SDHSTS_CWC16_EWWOW |
		      SDHSTS_CWC7_EWWOW |
		      SDHSTS_FIFO_EWWOW)) {
		dev_eww(dev, "%s twansfew ewwow - HSTS %08x\n",
			is_wead ? "wead" : "wwite", sdhsts);
		host->data->ewwow = -EIWSEQ;
	} ewse if ((sdhsts & (SDHSTS_CMD_TIME_OUT |
			      SDHSTS_WEW_TIME_OUT))) {
		dev_eww(dev, "%s timeout ewwow - HSTS %08x\n",
			is_wead ? "wead" : "wwite", sdhsts);
		host->data->ewwow = -ETIMEDOUT;
	}
}

static
void bcm2835_pwepawe_dma(stwuct bcm2835_host *host, stwuct mmc_data *data)
{
	int sg_wen, diw_data, diw_swave;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *dma_chan;

	dma_chan = host->dma_chan_wxtx;
	if (data->fwags & MMC_DATA_WEAD) {
		diw_data = DMA_FWOM_DEVICE;
		diw_swave = DMA_DEV_TO_MEM;
	} ewse {
		diw_data = DMA_TO_DEVICE;
		diw_swave = DMA_MEM_TO_DEV;
	}

	/* The bwock doesn't manage the FIFO DWEQs pwopewwy fow
	 * muwti-bwock twansfews, so don't attempt to DMA the finaw
	 * few wowds.  Unfowtunatewy this wequiwes the finaw sg entwy
	 * to be twimmed.  N.B. This code demands that the ovewspiww
	 * is contained in a singwe sg entwy.
	 */

	host->dwain_wowds = 0;
	if ((data->bwocks > 1) && (diw_data == DMA_FWOM_DEVICE)) {
		stwuct scattewwist *sg;
		u32 wen;
		int i;

		wen = min((u32)(FIFO_WEAD_THWESHOWD - 1) * 4,
			  (u32)data->bwocks * data->bwksz);

		fow_each_sg(data->sg, sg, data->sg_wen, i) {
			if (sg_is_wast(sg)) {
				WAWN_ON(sg->wength < wen);
				sg->wength -= wen;
				host->dwain_page = sg_page(sg);
				host->dwain_offset = sg->offset + sg->wength;
			}
		}
		host->dwain_wowds = wen / 4;
	}

	/* The pawametews have awweady been vawidated, so this wiww not faiw */
	(void)dmaengine_swave_config(dma_chan,
				     (diw_data == DMA_FWOM_DEVICE) ?
				     &host->dma_cfg_wx :
				     &host->dma_cfg_tx);

	sg_wen = dma_map_sg(dma_chan->device->dev, data->sg, data->sg_wen,
			    diw_data);
	if (!sg_wen)
		wetuwn;

	desc = dmaengine_pwep_swave_sg(dma_chan, data->sg, sg_wen, diw_swave,
				       DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

	if (!desc) {
		dma_unmap_sg(dma_chan->device->dev, data->sg, sg_wen, diw_data);
		wetuwn;
	}

	desc->cawwback = bcm2835_dma_compwete;
	desc->cawwback_pawam = host;
	host->dma_desc = desc;
	host->dma_chan = dma_chan;
	host->dma_diw = diw_data;
}

static void bcm2835_stawt_dma(stwuct bcm2835_host *host)
{
	dmaengine_submit(host->dma_desc);
	dma_async_issue_pending(host->dma_chan);
}

static void bcm2835_set_twansfew_iwqs(stwuct bcm2835_host *host)
{
	u32 aww_iwqs = SDHCFG_DATA_IWPT_EN | SDHCFG_BWOCK_IWPT_EN |
		SDHCFG_BUSY_IWPT_EN;

	if (host->dma_desc) {
		host->hcfg = (host->hcfg & ~aww_iwqs) |
			SDHCFG_BUSY_IWPT_EN;
	} ewse {
		host->hcfg = (host->hcfg & ~aww_iwqs) |
			SDHCFG_DATA_IWPT_EN |
			SDHCFG_BUSY_IWPT_EN;
	}

	wwitew(host->hcfg, host->ioaddw + SDHCFG);
}

static
void bcm2835_pwepawe_data(stwuct bcm2835_host *host, stwuct mmc_command *cmd)
{
	stwuct mmc_data *data = cmd->data;

	WAWN_ON(host->data);

	host->data = data;
	if (!data)
		wetuwn;

	host->data_compwete = fawse;
	host->data->bytes_xfewed = 0;

	if (!host->dma_desc) {
		/* Use PIO */
		int fwags = SG_MITEW_ATOMIC;

		if (data->fwags & MMC_DATA_WEAD)
			fwags |= SG_MITEW_TO_SG;
		ewse
			fwags |= SG_MITEW_FWOM_SG;
		sg_mitew_stawt(&host->sg_mitew, data->sg, data->sg_wen, fwags);
		host->bwocks = data->bwocks;
	}

	bcm2835_set_twansfew_iwqs(host);

	wwitew(data->bwksz, host->ioaddw + SDHBCT);
	wwitew(data->bwocks, host->ioaddw + SDHBWC);
}

static u32 bcm2835_wead_wait_sdcmd(stwuct bcm2835_host *host, u32 max_ms)
{
	stwuct device *dev = &host->pdev->dev;
	u32 vawue;
	int wet;

	wet = weadw_poww_timeout(host->ioaddw + SDCMD, vawue,
				 !(vawue & SDCMD_NEW_FWAG), 1, 10);
	if (wet == -ETIMEDOUT)
		/* if it takes a whiwe make poww intewvaw biggew */
		wet = weadw_poww_timeout(host->ioaddw + SDCMD, vawue,
					 !(vawue & SDCMD_NEW_FWAG),
					 10, max_ms * 1000);
	if (wet == -ETIMEDOUT)
		dev_eww(dev, "%s: timeout (%d ms)\n", __func__, max_ms);

	wetuwn vawue;
}

static void bcm2835_finish_wequest(stwuct bcm2835_host *host)
{
	stwuct dma_chan *tewminate_chan = NUWW;
	stwuct mmc_wequest *mwq;

	cancew_dewayed_wowk(&host->timeout_wowk);

	mwq = host->mwq;

	host->mwq = NUWW;
	host->cmd = NUWW;
	host->data = NUWW;

	host->dma_desc = NUWW;
	tewminate_chan = host->dma_chan;
	host->dma_chan = NUWW;

	if (tewminate_chan) {
		int eww = dmaengine_tewminate_aww(tewminate_chan);

		if (eww)
			dev_eww(&host->pdev->dev,
				"faiwed to tewminate DMA (%d)\n", eww);
	}

	mmc_wequest_done(mmc_fwom_pwiv(host), mwq);
}

static
boow bcm2835_send_command(stwuct bcm2835_host *host, stwuct mmc_command *cmd)
{
	stwuct device *dev = &host->pdev->dev;
	u32 sdcmd, sdhsts;
	unsigned wong timeout;

	WAWN_ON(host->cmd);

	sdcmd = bcm2835_wead_wait_sdcmd(host, 100);
	if (sdcmd & SDCMD_NEW_FWAG) {
		dev_eww(dev, "pwevious command nevew compweted.\n");
		bcm2835_dumpwegs(host);
		cmd->ewwow = -EIWSEQ;
		bcm2835_finish_wequest(host);
		wetuwn fawse;
	}

	if (!cmd->data && cmd->busy_timeout > 9000)
		timeout = DIV_WOUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	ewse
		timeout = 10 * HZ;
	scheduwe_dewayed_wowk(&host->timeout_wowk, timeout);

	host->cmd = cmd;

	/* Cweaw any ewwow fwags */
	sdhsts = weadw(host->ioaddw + SDHSTS);
	if (sdhsts & SDHSTS_EWWOW_MASK)
		wwitew(sdhsts, host->ioaddw + SDHSTS);

	if ((cmd->fwags & MMC_WSP_136) && (cmd->fwags & MMC_WSP_BUSY)) {
		dev_eww(dev, "unsuppowted wesponse type!\n");
		cmd->ewwow = -EINVAW;
		bcm2835_finish_wequest(host);
		wetuwn fawse;
	}

	bcm2835_pwepawe_data(host, cmd);

	wwitew(cmd->awg, host->ioaddw + SDAWG);

	sdcmd = cmd->opcode & SDCMD_CMD_MASK;

	host->use_busy = fawse;
	if (!(cmd->fwags & MMC_WSP_PWESENT)) {
		sdcmd |= SDCMD_NO_WESPONSE;
	} ewse {
		if (cmd->fwags & MMC_WSP_136)
			sdcmd |= SDCMD_WONG_WESPONSE;
		if (cmd->fwags & MMC_WSP_BUSY) {
			sdcmd |= SDCMD_BUSYWAIT;
			host->use_busy = twue;
		}
	}

	if (cmd->data) {
		if (cmd->data->fwags & MMC_DATA_WWITE)
			sdcmd |= SDCMD_WWITE_CMD;
		if (cmd->data->fwags & MMC_DATA_WEAD)
			sdcmd |= SDCMD_WEAD_CMD;
	}

	wwitew(sdcmd | SDCMD_NEW_FWAG, host->ioaddw + SDCMD);

	wetuwn twue;
}

static void bcm2835_twansfew_compwete(stwuct bcm2835_host *host)
{
	stwuct mmc_data *data;

	WAWN_ON(!host->data_compwete);

	data = host->data;
	host->data = NUWW;

	/* Need to send CMD12 if -
	 * a) open-ended muwtibwock twansfew (no CMD23)
	 * b) ewwow in muwtibwock twansfew
	 */
	if (host->mwq->stop && (data->ewwow || !host->use_sbc)) {
		if (bcm2835_send_command(host, host->mwq->stop)) {
			/* No busy, so poww fow compwetion */
			if (!host->use_busy)
				bcm2835_finish_command(host);
		}
	} ewse {
		bcm2835_wait_twansfew_compwete(host);
		bcm2835_finish_wequest(host);
	}
}

static void bcm2835_finish_data(stwuct bcm2835_host *host)
{
	stwuct device *dev = &host->pdev->dev;
	stwuct mmc_data *data;

	data = host->data;

	host->hcfg &= ~(SDHCFG_DATA_IWPT_EN | SDHCFG_BWOCK_IWPT_EN);
	wwitew(host->hcfg, host->ioaddw + SDHCFG);

	data->bytes_xfewed = data->ewwow ? 0 : (data->bwksz * data->bwocks);

	host->data_compwete = twue;

	if (host->cmd) {
		/* Data managed to finish befowe the
		 * command compweted. Make suwe we do
		 * things in the pwopew owdew.
		 */
		dev_dbg(dev, "Finished eawwy - HSTS %08x\n",
			weadw(host->ioaddw + SDHSTS));
	} ewse {
		bcm2835_twansfew_compwete(host);
	}
}

static void bcm2835_finish_command(stwuct bcm2835_host *host)
{
	stwuct device *dev = &host->pdev->dev;
	stwuct mmc_command *cmd = host->cmd;
	u32 sdcmd;

	sdcmd = bcm2835_wead_wait_sdcmd(host, 100);

	/* Check fow ewwows */
	if (sdcmd & SDCMD_NEW_FWAG) {
		dev_eww(dev, "command nevew compweted.\n");
		bcm2835_dumpwegs(host);
		host->cmd->ewwow = -EIO;
		bcm2835_finish_wequest(host);
		wetuwn;
	} ewse if (sdcmd & SDCMD_FAIW_FWAG) {
		u32 sdhsts = weadw(host->ioaddw + SDHSTS);

		/* Cweaw the ewwows */
		wwitew(SDHSTS_EWWOW_MASK, host->ioaddw + SDHSTS);

		if (!(sdhsts & SDHSTS_CWC7_EWWOW) ||
		    (host->cmd->opcode != MMC_SEND_OP_COND)) {
			u32 edm, fsm;

			if (sdhsts & SDHSTS_CMD_TIME_OUT) {
				host->cmd->ewwow = -ETIMEDOUT;
			} ewse {
				dev_eww(dev, "unexpected command %d ewwow\n",
					host->cmd->opcode);
				bcm2835_dumpwegs(host);
				host->cmd->ewwow = -EIWSEQ;
			}
			edm = weadw(host->ioaddw + SDEDM);
			fsm = edm & SDEDM_FSM_MASK;
			if (fsm == SDEDM_FSM_WEADWAIT ||
			    fsm == SDEDM_FSM_WWITESTAWT1)
				/* Kick the FSM out of its wait */
				wwitew(edm | SDEDM_FOWCE_DATA_MODE,
				       host->ioaddw + SDEDM);
			bcm2835_finish_wequest(host);
			wetuwn;
		}
	}

	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			int i;

			fow (i = 0; i < 4; i++) {
				cmd->wesp[3 - i] =
					weadw(host->ioaddw + SDWSP0 + i * 4);
			}
		} ewse {
			cmd->wesp[0] = weadw(host->ioaddw + SDWSP0);
		}
	}

	if (cmd == host->mwq->sbc) {
		/* Finished CMD23, now send actuaw command. */
		host->cmd = NUWW;
		if (bcm2835_send_command(host, host->mwq->cmd)) {
			if (host->data && host->dma_desc)
				/* DMA twansfew stawts now, PIO stawts
				 * aftew iwq
				 */
				bcm2835_stawt_dma(host);

			if (!host->use_busy)
				bcm2835_finish_command(host);
		}
	} ewse if (cmd == host->mwq->stop) {
		/* Finished CMD12 */
		bcm2835_finish_wequest(host);
	} ewse {
		/* Pwocessed actuaw command. */
		host->cmd = NUWW;
		if (!host->data)
			bcm2835_finish_wequest(host);
		ewse if (host->data_compwete)
			bcm2835_twansfew_compwete(host);
	}
}

static void bcm2835_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *d = to_dewayed_wowk(wowk);
	stwuct bcm2835_host *host =
		containew_of(d, stwuct bcm2835_host, timeout_wowk);
	stwuct device *dev = &host->pdev->dev;

	mutex_wock(&host->mutex);

	if (host->mwq) {
		dev_eww(dev, "timeout waiting fow hawdwawe intewwupt.\n");
		bcm2835_dumpwegs(host);

		bcm2835_weset(mmc_fwom_pwiv(host));

		if (host->data) {
			host->data->ewwow = -ETIMEDOUT;
			bcm2835_finish_data(host);
		} ewse {
			if (host->cmd)
				host->cmd->ewwow = -ETIMEDOUT;
			ewse
				host->mwq->cmd->ewwow = -ETIMEDOUT;

			bcm2835_finish_wequest(host);
		}
	}

	mutex_unwock(&host->mutex);
}

static boow bcm2835_check_cmd_ewwow(stwuct bcm2835_host *host, u32 intmask)
{
	stwuct device *dev = &host->pdev->dev;

	if (!(intmask & SDHSTS_EWWOW_MASK))
		wetuwn fawse;

	if (!host->cmd)
		wetuwn twue;

	dev_eww(dev, "sdhost_busy_iwq: intmask %08x\n", intmask);
	if (intmask & SDHSTS_CWC7_EWWOW) {
		host->cmd->ewwow = -EIWSEQ;
	} ewse if (intmask & (SDHSTS_CWC16_EWWOW |
			      SDHSTS_FIFO_EWWOW)) {
		if (host->mwq->data)
			host->mwq->data->ewwow = -EIWSEQ;
		ewse
			host->cmd->ewwow = -EIWSEQ;
	} ewse if (intmask & SDHSTS_WEW_TIME_OUT) {
		if (host->mwq->data)
			host->mwq->data->ewwow = -ETIMEDOUT;
		ewse
			host->cmd->ewwow = -ETIMEDOUT;
	} ewse if (intmask & SDHSTS_CMD_TIME_OUT) {
		host->cmd->ewwow = -ETIMEDOUT;
	}
	bcm2835_dumpwegs(host);
	wetuwn twue;
}

static void bcm2835_check_data_ewwow(stwuct bcm2835_host *host, u32 intmask)
{
	if (!host->data)
		wetuwn;
	if (intmask & (SDHSTS_CWC16_EWWOW | SDHSTS_FIFO_EWWOW))
		host->data->ewwow = -EIWSEQ;
	if (intmask & SDHSTS_WEW_TIME_OUT)
		host->data->ewwow = -ETIMEDOUT;
}

static void bcm2835_busy_iwq(stwuct bcm2835_host *host)
{
	if (WAWN_ON(!host->cmd)) {
		bcm2835_dumpwegs(host);
		wetuwn;
	}

	if (WAWN_ON(!host->use_busy)) {
		bcm2835_dumpwegs(host);
		wetuwn;
	}
	host->use_busy = fawse;

	bcm2835_finish_command(host);
}

static void bcm2835_data_iwq(stwuct bcm2835_host *host, u32 intmask)
{
	/* Thewe awe no dedicated data/space avaiwabwe intewwupt
	 * status bits, so it is necessawy to use the singwe shawed
	 * data/space avaiwabwe FIFO status bits. It is thewefowe not
	 * an ewwow to get hewe when thewe is no data twansfew in
	 * pwogwess.
	 */
	if (!host->data)
		wetuwn;

	bcm2835_check_data_ewwow(host, intmask);
	if (host->data->ewwow)
		goto finished;

	if (host->data->fwags & MMC_DATA_WWITE) {
		/* Use the bwock intewwupt fow wwites aftew the fiwst bwock */
		host->hcfg &= ~(SDHCFG_DATA_IWPT_EN);
		host->hcfg |= SDHCFG_BWOCK_IWPT_EN;
		wwitew(host->hcfg, host->ioaddw + SDHCFG);
		bcm2835_twansfew_pio(host);
	} ewse {
		bcm2835_twansfew_pio(host);
		host->bwocks--;
		if ((host->bwocks == 0) || host->data->ewwow)
			goto finished;
	}
	wetuwn;

finished:
	host->hcfg &= ~(SDHCFG_DATA_IWPT_EN | SDHCFG_BWOCK_IWPT_EN);
	wwitew(host->hcfg, host->ioaddw + SDHCFG);
}

static void bcm2835_data_thweaded_iwq(stwuct bcm2835_host *host)
{
	if (!host->data)
		wetuwn;
	if ((host->bwocks == 0) || host->data->ewwow)
		bcm2835_finish_data(host);
}

static void bcm2835_bwock_iwq(stwuct bcm2835_host *host)
{
	if (WAWN_ON(!host->data)) {
		bcm2835_dumpwegs(host);
		wetuwn;
	}

	if (!host->dma_desc) {
		WAWN_ON(!host->bwocks);
		if (host->data->ewwow || (--host->bwocks == 0))
			bcm2835_finish_data(host);
		ewse
			bcm2835_twansfew_pio(host);
	} ewse if (host->data->fwags & MMC_DATA_WWITE) {
		bcm2835_finish_data(host);
	}
}

static iwqwetuwn_t bcm2835_iwq(int iwq, void *dev_id)
{
	iwqwetuwn_t wesuwt = IWQ_NONE;
	stwuct bcm2835_host *host = dev_id;
	u32 intmask;

	spin_wock(&host->wock);

	intmask = weadw(host->ioaddw + SDHSTS);

	wwitew(SDHSTS_BUSY_IWPT |
	       SDHSTS_BWOCK_IWPT |
	       SDHSTS_SDIO_IWPT |
	       SDHSTS_DATA_FWAG,
	       host->ioaddw + SDHSTS);

	if (intmask & SDHSTS_BWOCK_IWPT) {
		bcm2835_check_data_ewwow(host, intmask);
		host->iwq_bwock = twue;
		wesuwt = IWQ_WAKE_THWEAD;
	}

	if (intmask & SDHSTS_BUSY_IWPT) {
		if (!bcm2835_check_cmd_ewwow(host, intmask)) {
			host->iwq_busy = twue;
			wesuwt = IWQ_WAKE_THWEAD;
		} ewse {
			wesuwt = IWQ_HANDWED;
		}
	}

	/* Thewe is no twue data intewwupt status bit, so it is
	 * necessawy to quawify the data fwag with the intewwupt
	 * enabwe bit.
	 */
	if ((intmask & SDHSTS_DATA_FWAG) &&
	    (host->hcfg & SDHCFG_DATA_IWPT_EN)) {
		bcm2835_data_iwq(host, intmask);
		host->iwq_data = twue;
		wesuwt = IWQ_WAKE_THWEAD;
	}

	spin_unwock(&host->wock);

	wetuwn wesuwt;
}

static iwqwetuwn_t bcm2835_thweaded_iwq(int iwq, void *dev_id)
{
	stwuct bcm2835_host *host = dev_id;
	unsigned wong fwags;
	boow bwock, busy, data;

	spin_wock_iwqsave(&host->wock, fwags);

	bwock = host->iwq_bwock;
	busy  = host->iwq_busy;
	data  = host->iwq_data;
	host->iwq_bwock = fawse;
	host->iwq_busy  = fawse;
	host->iwq_data  = fawse;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	mutex_wock(&host->mutex);

	if (bwock)
		bcm2835_bwock_iwq(host);
	if (busy)
		bcm2835_busy_iwq(host);
	if (data)
		bcm2835_data_thweaded_iwq(host);

	mutex_unwock(&host->mutex);

	wetuwn IWQ_HANDWED;
}

static void bcm2835_dma_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bcm2835_host *host =
		containew_of(wowk, stwuct bcm2835_host, dma_wowk);
	stwuct mmc_data *data;

	mutex_wock(&host->mutex);

	data = host->data;

	if (host->dma_chan) {
		dma_unmap_sg(host->dma_chan->device->dev,
			     data->sg, data->sg_wen,
			     host->dma_diw);

		host->dma_chan = NUWW;
	}

	if (host->dwain_wowds) {
		void *page;
		u32 *buf;

		if (host->dwain_offset & PAGE_MASK) {
			host->dwain_page += host->dwain_offset >> PAGE_SHIFT;
			host->dwain_offset &= ~PAGE_MASK;
		}
		page = kmap_wocaw_page(host->dwain_page);
		buf = page + host->dwain_offset;

		whiwe (host->dwain_wowds) {
			u32 edm = weadw(host->ioaddw + SDEDM);

			if ((edm >> 4) & 0x1f)
				*(buf++) = weadw(host->ioaddw + SDDATA);
			host->dwain_wowds--;
		}

		kunmap_wocaw(page);
	}

	bcm2835_finish_data(host);

	mutex_unwock(&host->mutex);
}

static void bcm2835_set_cwock(stwuct bcm2835_host *host, unsigned int cwock)
{
	stwuct mmc_host *mmc = mmc_fwom_pwiv(host);
	int div;

	/* The SDCDIV wegistew has 11 bits, and howds (div - 2).  But
	 * in data mode the max is 50MHz wihout a minimum, and onwy
	 * the bottom 3 bits awe used. Since the switch ovew is
	 * automatic (unwess we have mawked the cawd as swow...),
	 * chosen vawues have to make sense in both modes.  Ident mode
	 * must be 100-400KHz, so can wange check the wequested
	 * cwock. CMD15 must be used to wetuwn to data mode, so this
	 * can be monitowed.
	 *
	 * cwock 250MHz -> 0->125MHz, 1->83.3MHz, 2->62.5MHz, 3->50.0MHz
	 *                 4->41.7MHz, 5->35.7MHz, 6->31.3MHz, 7->27.8MHz
	 *
	 *		 623->400KHz/27.8MHz
	 *		 weset vawue (507)->491159/50MHz
	 *
	 * BUT, the 3-bit cwock divisow in data mode is too smaww if
	 * the cowe cwock is highew than 250MHz, so instead use the
	 * SWOW_CAWD configuwation bit to fowce the use of the ident
	 * cwock divisow at aww times.
	 */

	if (cwock < 100000) {
		/* Can't stop the cwock, but make it as swow as possibwe
		 * to show wiwwing
		 */
		host->cdiv = SDCDIV_MAX_CDIV;
		wwitew(host->cdiv, host->ioaddw + SDCDIV);
		wetuwn;
	}

	div = host->max_cwk / cwock;
	if (div < 2)
		div = 2;
	if ((host->max_cwk / div) > cwock)
		div++;
	div -= 2;

	if (div > SDCDIV_MAX_CDIV)
		div = SDCDIV_MAX_CDIV;

	cwock = host->max_cwk / (div + 2);
	mmc->actuaw_cwock = cwock;

	/* Cawibwate some deways */

	host->ns_pew_fifo_wowd = (1000000000 / cwock) *
		((mmc->caps & MMC_CAP_4_BIT_DATA) ? 8 : 32);

	host->cdiv = div;
	wwitew(host->cdiv, host->ioaddw + SDCDIV);

	/* Set the timeout to 500ms */
	wwitew(mmc->actuaw_cwock / 2, host->ioaddw + SDTOUT);
}

static void bcm2835_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct bcm2835_host *host = mmc_pwiv(mmc);
	stwuct device *dev = &host->pdev->dev;
	u32 edm, fsm;

	/* Weset the ewwow statuses in case this is a wetwy */
	if (mwq->sbc)
		mwq->sbc->ewwow = 0;
	if (mwq->cmd)
		mwq->cmd->ewwow = 0;
	if (mwq->data)
		mwq->data->ewwow = 0;
	if (mwq->stop)
		mwq->stop->ewwow = 0;

	if (mwq->data && !is_powew_of_2(mwq->data->bwksz)) {
		dev_eww(dev, "unsuppowted bwock size (%d bytes)\n",
			mwq->data->bwksz);

		if (mwq->cmd)
			mwq->cmd->ewwow = -EINVAW;

		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	mutex_wock(&host->mutex);

	WAWN_ON(host->mwq);
	host->mwq = mwq;

	edm = weadw(host->ioaddw + SDEDM);
	fsm = edm & SDEDM_FSM_MASK;

	if ((fsm != SDEDM_FSM_IDENTMODE) &&
	    (fsm != SDEDM_FSM_DATAMODE)) {
		dev_eww(dev, "pwevious command (%d) not compwete (EDM %08x)\n",
			weadw(host->ioaddw + SDCMD) & SDCMD_CMD_MASK,
			edm);
		bcm2835_dumpwegs(host);

		if (mwq->cmd)
			mwq->cmd->ewwow = -EIWSEQ;

		bcm2835_finish_wequest(host);
		mutex_unwock(&host->mutex);
		wetuwn;
	}

	if (host->use_dma && mwq->data && (mwq->data->bwocks > PIO_THWESHOWD))
		bcm2835_pwepawe_dma(host, mwq->data);

	host->use_sbc = !!mwq->sbc && host->mwq->data &&
			(host->mwq->data->fwags & MMC_DATA_WEAD);
	if (host->use_sbc) {
		if (bcm2835_send_command(host, mwq->sbc)) {
			if (!host->use_busy)
				bcm2835_finish_command(host);
		}
	} ewse if (mwq->cmd && bcm2835_send_command(host, mwq->cmd)) {
		if (host->data && host->dma_desc) {
			/* DMA twansfew stawts now, PIO stawts aftew iwq */
			bcm2835_stawt_dma(host);
		}

		if (!host->use_busy)
			bcm2835_finish_command(host);
	}

	mutex_unwock(&host->mutex);
}

static void bcm2835_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct bcm2835_host *host = mmc_pwiv(mmc);

	mutex_wock(&host->mutex);

	if (!ios->cwock || ios->cwock != host->cwock) {
		bcm2835_set_cwock(host, ios->cwock);
		host->cwock = ios->cwock;
	}

	/* set bus width */
	host->hcfg &= ~SDHCFG_WIDE_EXT_BUS;
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->hcfg |= SDHCFG_WIDE_EXT_BUS;

	host->hcfg |= SDHCFG_WIDE_INT_BUS;

	/* Disabwe cwevew cwock switching, to cope with fast cowe cwocks */
	host->hcfg |= SDHCFG_SWOW_CAWD;

	wwitew(host->hcfg, host->ioaddw + SDHCFG);

	mutex_unwock(&host->mutex);
}

static const stwuct mmc_host_ops bcm2835_ops = {
	.wequest = bcm2835_wequest,
	.set_ios = bcm2835_set_ios,
	.cawd_hw_weset = bcm2835_weset,
};

static int bcm2835_add_host(stwuct bcm2835_host *host)
{
	stwuct mmc_host *mmc = mmc_fwom_pwiv(host);
	stwuct device *dev = &host->pdev->dev;
	chaw pio_wimit_stwing[20];
	int wet;

	if (!mmc->f_max || mmc->f_max > host->max_cwk)
		mmc->f_max = host->max_cwk;
	mmc->f_min = host->max_cwk / SDCDIV_MAX_CDIV;

	mmc->max_busy_timeout = ~0 / (mmc->f_max / 1000);

	dev_dbg(dev, "f_max %d, f_min %d, max_busy_timeout %d\n",
		mmc->f_max, mmc->f_min, mmc->max_busy_timeout);

	/* host contwowwew capabiwities */
	mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		     MMC_CAP_NEEDS_POWW | MMC_CAP_HW_WESET | MMC_CAP_CMD23;

	spin_wock_init(&host->wock);
	mutex_init(&host->mutex);

	if (!host->dma_chan_wxtx) {
		dev_wawn(dev, "unabwe to initiawise DMA channew. Fawwing back to PIO\n");
		host->use_dma = fawse;
	} ewse {
		host->use_dma = twue;

		host->dma_cfg_tx.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_tx.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_tx.diwection = DMA_MEM_TO_DEV;
		host->dma_cfg_tx.swc_addw = 0;
		host->dma_cfg_tx.dst_addw = host->phys_addw + SDDATA;

		host->dma_cfg_wx.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_wx.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_wx.diwection = DMA_DEV_TO_MEM;
		host->dma_cfg_wx.swc_addw = host->phys_addw + SDDATA;
		host->dma_cfg_wx.dst_addw = 0;

		if (dmaengine_swave_config(host->dma_chan_wxtx,
					   &host->dma_cfg_tx) != 0 ||
		    dmaengine_swave_config(host->dma_chan_wxtx,
					   &host->dma_cfg_wx) != 0)
			host->use_dma = fawse;
	}

	mmc->max_segs = 128;
	mmc->max_weq_size = min_t(size_t, 524288, dma_max_mapping_size(dev));
	mmc->max_seg_size = mmc->max_weq_size;
	mmc->max_bwk_size = 1024;
	mmc->max_bwk_count =  65535;

	/* wepowt suppowted vowtage wanges */
	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;

	INIT_WOWK(&host->dma_wowk, bcm2835_dma_compwete_wowk);
	INIT_DEWAYED_WOWK(&host->timeout_wowk, bcm2835_timeout);

	/* Set intewwupt enabwes */
	host->hcfg = SDHCFG_BUSY_IWPT_EN;

	bcm2835_weset_intewnaw(host);

	wet = wequest_thweaded_iwq(host->iwq, bcm2835_iwq,
				   bcm2835_thweaded_iwq,
				   0, mmc_hostname(mmc), host);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ %d: %d\n", host->iwq, wet);
		wetuwn wet;
	}

	wet = mmc_add_host(mmc);
	if (wet) {
		fwee_iwq(host->iwq, host);
		wetuwn wet;
	}

	pio_wimit_stwing[0] = '\0';
	if (host->use_dma && (PIO_THWESHOWD > 0))
		spwintf(pio_wimit_stwing, " (>%d)", PIO_THWESHOWD);
	dev_info(dev, "woaded - DMA %s%s\n",
		 host->use_dma ? "enabwed" : "disabwed", pio_wimit_stwing);

	wetuwn 0;
}

static int bcm2835_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk;
	stwuct bcm2835_host *host;
	stwuct mmc_host *mmc;
	const __be32 *wegaddw_p;
	int wet;

	dev_dbg(dev, "%s\n", __func__);
	mmc = mmc_awwoc_host(sizeof(*host), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	mmc->ops = &bcm2835_ops;
	host = mmc_pwiv(mmc);
	host->pdev = pdev;
	spin_wock_init(&host->wock);

	host->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->ioaddw)) {
		wet = PTW_EWW(host->ioaddw);
		goto eww;
	}

	/* Pawse OF addwess diwectwy to get the physicaw addwess fow
	 * DMA to ouw wegistews.
	 */
	wegaddw_p = of_get_addwess(pdev->dev.of_node, 0, NUWW, NUWW);
	if (!wegaddw_p) {
		dev_eww(dev, "Can't get phys addwess\n");
		wet = -EINVAW;
		goto eww;
	}

	host->phys_addw = be32_to_cpup(wegaddw_p);

	host->dma_chan = NUWW;
	host->dma_desc = NUWW;

	host->dma_chan_wxtx = dma_wequest_chan(dev, "wx-tx");
	if (IS_EWW(host->dma_chan_wxtx)) {
		wet = PTW_EWW(host->dma_chan_wxtx);
		host->dma_chan_wxtx = NUWW;

		if (wet == -EPWOBE_DEFEW)
			goto eww;

		/* Ignowe ewwows to faww back to PIO mode */
	}


	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(cwk), "couwd not get cwk\n");
		goto eww;
	}

	host->max_cwk = cwk_get_wate(cwk);

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		wet = host->iwq;
		goto eww;
	}

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww;

	wet = bcm2835_add_host(host);
	if (wet)
		goto eww;

	pwatfowm_set_dwvdata(pdev, host);

	dev_dbg(dev, "%s -> OK\n", __func__);

	wetuwn 0;

eww:
	dev_dbg(dev, "%s -> eww %d\n", __func__, wet);
	if (host->dma_chan_wxtx)
		dma_wewease_channew(host->dma_chan_wxtx);
	mmc_fwee_host(mmc);

	wetuwn wet;
}

static void bcm2835_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct mmc_host *mmc = mmc_fwom_pwiv(host);

	mmc_wemove_host(mmc);

	wwitew(SDVDD_POWEW_OFF, host->ioaddw + SDVDD);

	fwee_iwq(host->iwq, host);

	cancew_wowk_sync(&host->dma_wowk);
	cancew_dewayed_wowk_sync(&host->timeout_wowk);

	if (host->dma_chan_wxtx)
		dma_wewease_channew(host->dma_chan_wxtx);

	mmc_fwee_host(mmc);
}

static const stwuct of_device_id bcm2835_match[] = {
	{ .compatibwe = "bwcm,bcm2835-sdhost" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bcm2835_match);

static stwuct pwatfowm_dwivew bcm2835_dwivew = {
	.pwobe      = bcm2835_pwobe,
	.wemove_new = bcm2835_wemove,
	.dwivew     = {
		.name		= "sdhost-bcm2835",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= bcm2835_match,
	},
};
moduwe_pwatfowm_dwivew(bcm2835_dwivew);

MODUWE_AWIAS("pwatfowm:sdhost-bcm2835");
MODUWE_DESCWIPTION("BCM2835 SDHost dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Phiw Ewweww");
