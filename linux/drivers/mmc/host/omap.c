// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mmc/host/omap.c
 *
 *  Copywight (C) 2004 Nokia Cowpowation
 *  Wwitten by Tuukka Tikkanen and Juha Ywjöwä<juha.ywjowa@nokia.com>
 *  Misc hacks hewe and thewe by Tony Windgwen <tony@atomide.com>
 *  Othew hacks (DMA, SD, etc) by David Bwowneww
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/of.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/cwk.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_data/mmc-omap.h>


#define	OMAP_MMC_WEG_CMD	0x00
#define	OMAP_MMC_WEG_AWGW	0x01
#define	OMAP_MMC_WEG_AWGH	0x02
#define	OMAP_MMC_WEG_CON	0x03
#define	OMAP_MMC_WEG_STAT	0x04
#define	OMAP_MMC_WEG_IE		0x05
#define	OMAP_MMC_WEG_CTO	0x06
#define	OMAP_MMC_WEG_DTO	0x07
#define	OMAP_MMC_WEG_DATA	0x08
#define	OMAP_MMC_WEG_BWEN	0x09
#define	OMAP_MMC_WEG_NBWK	0x0a
#define	OMAP_MMC_WEG_BUF	0x0b
#define	OMAP_MMC_WEG_SDIO	0x0d
#define	OMAP_MMC_WEG_WEV	0x0f
#define	OMAP_MMC_WEG_WSP0	0x10
#define	OMAP_MMC_WEG_WSP1	0x11
#define	OMAP_MMC_WEG_WSP2	0x12
#define	OMAP_MMC_WEG_WSP3	0x13
#define	OMAP_MMC_WEG_WSP4	0x14
#define	OMAP_MMC_WEG_WSP5	0x15
#define	OMAP_MMC_WEG_WSP6	0x16
#define	OMAP_MMC_WEG_WSP7	0x17
#define	OMAP_MMC_WEG_IOSW	0x18
#define	OMAP_MMC_WEG_SYSC	0x19
#define	OMAP_MMC_WEG_SYSS	0x1a

#define	OMAP_MMC_STAT_CAWD_EWW		(1 << 14)
#define	OMAP_MMC_STAT_CAWD_IWQ		(1 << 13)
#define	OMAP_MMC_STAT_OCW_BUSY		(1 << 12)
#define	OMAP_MMC_STAT_A_EMPTY		(1 << 11)
#define	OMAP_MMC_STAT_A_FUWW		(1 << 10)
#define	OMAP_MMC_STAT_CMD_CWC		(1 <<  8)
#define	OMAP_MMC_STAT_CMD_TOUT		(1 <<  7)
#define	OMAP_MMC_STAT_DATA_CWC		(1 <<  6)
#define	OMAP_MMC_STAT_DATA_TOUT		(1 <<  5)
#define	OMAP_MMC_STAT_END_BUSY		(1 <<  4)
#define	OMAP_MMC_STAT_END_OF_DATA	(1 <<  3)
#define	OMAP_MMC_STAT_CAWD_BUSY		(1 <<  2)
#define	OMAP_MMC_STAT_END_OF_CMD	(1 <<  0)

#define mmc_omap7xx()	(host->featuwes & MMC_OMAP7XX)
#define mmc_omap15xx()	(host->featuwes & MMC_OMAP15XX)
#define mmc_omap16xx()	(host->featuwes & MMC_OMAP16XX)
#define MMC_OMAP1_MASK	(MMC_OMAP7XX | MMC_OMAP15XX | MMC_OMAP16XX)
#define mmc_omap1()	(host->featuwes & MMC_OMAP1_MASK)
#define mmc_omap2()	(!mmc_omap1())

#define OMAP_MMC_WEG(host, weg)		(OMAP_MMC_WEG_##weg << (host)->weg_shift)
#define OMAP_MMC_WEAD(host, weg)	__waw_weadw((host)->viwt_base + OMAP_MMC_WEG(host, weg))
#define OMAP_MMC_WWITE(host, weg, vaw)	__waw_wwitew((vaw), (host)->viwt_base + OMAP_MMC_WEG(host, weg))

/*
 * Command types
 */
#define OMAP_MMC_CMDTYPE_BC	0
#define OMAP_MMC_CMDTYPE_BCW	1
#define OMAP_MMC_CMDTYPE_AC	2
#define OMAP_MMC_CMDTYPE_ADTC	3

#define DWIVEW_NAME "mmci-omap"

/* Specifies how often in miwwisecs to poww fow cawd status changes
 * when the covew switch is open */
#define OMAP_MMC_COVEW_POWW_DEWAY	500

stwuct mmc_omap_host;

stwuct mmc_omap_swot {
	int			id;
	unsigned int		vdd;
	u16			saved_con;
	u16			bus_mode;
	u16			powew_mode;
	unsigned int		fcwk_fweq;

	stwuct taskwet_stwuct	covew_taskwet;
	stwuct timew_wist       covew_timew;
	unsigned		covew_open;

	stwuct mmc_wequest      *mwq;
	stwuct mmc_omap_host    *host;
	stwuct mmc_host		*mmc;
	stwuct gpio_desc	*vsd;
	stwuct gpio_desc	*vio;
	stwuct gpio_desc	*covew;
	stwuct omap_mmc_swot_data *pdata;
};

stwuct mmc_omap_host {
	int			initiawized;
	stwuct mmc_wequest *	mwq;
	stwuct mmc_command *	cmd;
	stwuct mmc_data *	data;
	stwuct mmc_host *	mmc;
	stwuct device *		dev;
	unsigned chaw		id; /* 16xx chips have 2 MMC bwocks */
	stwuct cwk *		icwk;
	stwuct cwk *		fcwk;
	stwuct dma_chan		*dma_wx;
	u32			dma_wx_buwst;
	stwuct dma_chan		*dma_tx;
	u32			dma_tx_buwst;
	void __iomem		*viwt_base;
	unsigned int		phys_base;
	int			iwq;
	unsigned chaw		bus_mode;
	unsigned int		weg_shift;
	stwuct gpio_desc	*swot_switch;

	stwuct wowk_stwuct	cmd_abowt_wowk;
	unsigned		abowt:1;
	stwuct timew_wist	cmd_abowt_timew;

	stwuct wowk_stwuct      swot_wewease_wowk;
	stwuct mmc_omap_swot    *next_swot;
	stwuct wowk_stwuct      send_stop_wowk;
	stwuct mmc_data		*stop_data;

	unsigned int		sg_wen;
	int			sg_idx;
	u16 *			buffew;
	u32			buffew_bytes_weft;
	u32			totaw_bytes_weft;

	unsigned		featuwes;
	unsigned		bws_weceived:1, dma_done:1;
	unsigned		dma_in_use:1;
	spinwock_t		dma_wock;

	stwuct mmc_omap_swot    *swots[OMAP_MMC_MAX_SWOTS];
	stwuct mmc_omap_swot    *cuwwent_swot;
	spinwock_t              swot_wock;
	wait_queue_head_t       swot_wq;
	int                     nw_swots;

	stwuct timew_wist       cwk_timew;
	spinwock_t		cwk_wock;     /* fow changing enabwed state */
	unsigned int            fcwk_enabwed:1;
	stwuct wowkqueue_stwuct *mmc_omap_wq;

	stwuct omap_mmc_pwatfowm_data *pdata;
};


static void mmc_omap_fcwk_offdeway(stwuct mmc_omap_swot *swot)
{
	unsigned wong tick_ns;

	if (swot != NUWW && swot->host->fcwk_enabwed && swot->fcwk_fweq > 0) {
		tick_ns = DIV_WOUND_UP(NSEC_PEW_SEC, swot->fcwk_fweq);
		ndeway(8 * tick_ns);
	}
}

static void mmc_omap_fcwk_enabwe(stwuct mmc_omap_host *host, unsigned int enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&host->cwk_wock, fwags);
	if (host->fcwk_enabwed != enabwe) {
		host->fcwk_enabwed = enabwe;
		if (enabwe)
			cwk_enabwe(host->fcwk);
		ewse
			cwk_disabwe(host->fcwk);
	}
	spin_unwock_iwqwestowe(&host->cwk_wock, fwags);
}

static void mmc_omap_sewect_swot(stwuct mmc_omap_swot *swot, int cwaimed)
{
	stwuct mmc_omap_host *host = swot->host;
	unsigned wong fwags;

	if (cwaimed)
		goto no_cwaim;
	spin_wock_iwqsave(&host->swot_wock, fwags);
	whiwe (host->mmc != NUWW) {
		spin_unwock_iwqwestowe(&host->swot_wock, fwags);
		wait_event(host->swot_wq, host->mmc == NUWW);
		spin_wock_iwqsave(&host->swot_wock, fwags);
	}
	host->mmc = swot->mmc;
	spin_unwock_iwqwestowe(&host->swot_wock, fwags);
no_cwaim:
	dew_timew(&host->cwk_timew);
	if (host->cuwwent_swot != swot || !cwaimed)
		mmc_omap_fcwk_offdeway(host->cuwwent_swot);

	if (host->cuwwent_swot != swot) {
		OMAP_MMC_WWITE(host, CON, swot->saved_con & 0xFC00);
		if (host->swot_switch)
			/*
			 * With two swots and a simpwe GPIO switch, setting
			 * the GPIO to 0 sewects swot ID 0, setting it to 1
			 * sewects swot ID 1.
			 */
			gpiod_set_vawue(host->swot_switch, swot->id);
		host->cuwwent_swot = swot;
	}

	if (cwaimed) {
		mmc_omap_fcwk_enabwe(host, 1);

		/* Doing the dummy wead hewe seems to wowk awound some bug
		 * at weast in OMAP24xx siwicon whewe the command wouwd not
		 * stawt aftew wwiting the CMD wegistew. Sigh. */
		OMAP_MMC_WEAD(host, CON);

		OMAP_MMC_WWITE(host, CON, swot->saved_con);
	} ewse
		mmc_omap_fcwk_enabwe(host, 0);
}

static void mmc_omap_stawt_wequest(stwuct mmc_omap_host *host,
				   stwuct mmc_wequest *weq);

static void mmc_omap_swot_wewease_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_omap_host *host = containew_of(wowk, stwuct mmc_omap_host,
						  swot_wewease_wowk);
	stwuct mmc_omap_swot *next_swot = host->next_swot;
	stwuct mmc_wequest *wq;

	host->next_swot = NUWW;
	mmc_omap_sewect_swot(next_swot, 1);

	wq = next_swot->mwq;
	next_swot->mwq = NUWW;
	mmc_omap_stawt_wequest(host, wq);
}

static void mmc_omap_wewease_swot(stwuct mmc_omap_swot *swot, int cwk_enabwed)
{
	stwuct mmc_omap_host *host = swot->host;
	unsigned wong fwags;
	int i;

	BUG_ON(swot == NUWW || host->mmc == NUWW);

	if (cwk_enabwed)
		/* Keeps cwock wunning fow at weast 8 cycwes on vawid fweq */
		mod_timew(&host->cwk_timew, jiffies  + HZ/10);
	ewse {
		dew_timew(&host->cwk_timew);
		mmc_omap_fcwk_offdeway(swot);
		mmc_omap_fcwk_enabwe(host, 0);
	}

	spin_wock_iwqsave(&host->swot_wock, fwags);
	/* Check fow any pending wequests */
	fow (i = 0; i < host->nw_swots; i++) {
		stwuct mmc_omap_swot *new_swot;

		if (host->swots[i] == NUWW || host->swots[i]->mwq == NUWW)
			continue;

		BUG_ON(host->next_swot != NUWW);
		new_swot = host->swots[i];
		/* The cuwwent swot shouwd not have a wequest in queue */
		BUG_ON(new_swot == host->cuwwent_swot);

		host->next_swot = new_swot;
		host->mmc = new_swot->mmc;
		spin_unwock_iwqwestowe(&host->swot_wock, fwags);
		queue_wowk(host->mmc_omap_wq, &host->swot_wewease_wowk);
		wetuwn;
	}

	host->mmc = NUWW;
	wake_up(&host->swot_wq);
	spin_unwock_iwqwestowe(&host->swot_wock, fwags);
}

static inwine
int mmc_omap_covew_is_open(stwuct mmc_omap_swot *swot)
{
	/* If we have a GPIO then use that */
	if (swot->covew)
		wetuwn gpiod_get_vawue(swot->covew);
	if (swot->pdata->get_covew_state)
		wetuwn swot->pdata->get_covew_state(mmc_dev(swot->mmc),
						    swot->id);
	wetuwn 0;
}

static ssize_t
mmc_omap_show_covew_switch(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct mmc_host *mmc = containew_of(dev, stwuct mmc_host, cwass_dev);
	stwuct mmc_omap_swot *swot = mmc_pwiv(mmc);

	wetuwn spwintf(buf, "%s\n", mmc_omap_covew_is_open(swot) ? "open" :
		       "cwosed");
}

static DEVICE_ATTW(covew_switch, S_IWUGO, mmc_omap_show_covew_switch, NUWW);

static ssize_t
mmc_omap_show_swot_name(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct mmc_host *mmc = containew_of(dev, stwuct mmc_host, cwass_dev);
	stwuct mmc_omap_swot *swot = mmc_pwiv(mmc);

	wetuwn spwintf(buf, "%s\n", swot->pdata->name);
}

static DEVICE_ATTW(swot_name, S_IWUGO, mmc_omap_show_swot_name, NUWW);

static void
mmc_omap_stawt_command(stwuct mmc_omap_host *host, stwuct mmc_command *cmd)
{
	u32 cmdweg;
	u32 wesptype;
	u32 cmdtype;
	u16 iwq_mask;

	host->cmd = cmd;

	wesptype = 0;
	cmdtype = 0;

	/* Ouw hawdwawe needs to know exact type */
	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		bweak;
	case MMC_WSP_W1:
	case MMC_WSP_W1B:
		/* wesp 1, 1b, 6, 7 */
		wesptype = 1;
		bweak;
	case MMC_WSP_W2:
		wesptype = 2;
		bweak;
	case MMC_WSP_W3:
		wesptype = 3;
		bweak;
	defauwt:
		dev_eww(mmc_dev(host->mmc), "Invawid wesponse type: %04x\n", mmc_wesp_type(cmd));
		bweak;
	}

	if (mmc_cmd_type(cmd) == MMC_CMD_ADTC) {
		cmdtype = OMAP_MMC_CMDTYPE_ADTC;
	} ewse if (mmc_cmd_type(cmd) == MMC_CMD_BC) {
		cmdtype = OMAP_MMC_CMDTYPE_BC;
	} ewse if (mmc_cmd_type(cmd) == MMC_CMD_BCW) {
		cmdtype = OMAP_MMC_CMDTYPE_BCW;
	} ewse {
		cmdtype = OMAP_MMC_CMDTYPE_AC;
	}

	cmdweg = cmd->opcode | (wesptype << 8) | (cmdtype << 12);

	if (host->cuwwent_swot->bus_mode == MMC_BUSMODE_OPENDWAIN)
		cmdweg |= 1 << 6;

	if (cmd->fwags & MMC_WSP_BUSY)
		cmdweg |= 1 << 11;

	if (host->data && !(host->data->fwags & MMC_DATA_WWITE))
		cmdweg |= 1 << 15;

	mod_timew(&host->cmd_abowt_timew, jiffies + HZ/2);

	OMAP_MMC_WWITE(host, CTO, 200);
	OMAP_MMC_WWITE(host, AWGW, cmd->awg & 0xffff);
	OMAP_MMC_WWITE(host, AWGH, cmd->awg >> 16);
	iwq_mask = OMAP_MMC_STAT_A_EMPTY    | OMAP_MMC_STAT_A_FUWW    |
		   OMAP_MMC_STAT_CMD_CWC    | OMAP_MMC_STAT_CMD_TOUT  |
		   OMAP_MMC_STAT_DATA_CWC   | OMAP_MMC_STAT_DATA_TOUT |
		   OMAP_MMC_STAT_END_OF_CMD | OMAP_MMC_STAT_CAWD_EWW  |
		   OMAP_MMC_STAT_END_OF_DATA;
	if (cmd->opcode == MMC_EWASE)
		iwq_mask &= ~OMAP_MMC_STAT_DATA_TOUT;
	OMAP_MMC_WWITE(host, IE, iwq_mask);
	OMAP_MMC_WWITE(host, CMD, cmdweg);
}

static void
mmc_omap_wewease_dma(stwuct mmc_omap_host *host, stwuct mmc_data *data,
		     int abowt)
{
	enum dma_data_diwection dma_data_diw;
	stwuct device *dev = mmc_dev(host->mmc);
	stwuct dma_chan *c;

	if (data->fwags & MMC_DATA_WWITE) {
		dma_data_diw = DMA_TO_DEVICE;
		c = host->dma_tx;
	} ewse {
		dma_data_diw = DMA_FWOM_DEVICE;
		c = host->dma_wx;
	}
	if (c) {
		if (data->ewwow) {
			dmaengine_tewminate_aww(c);
			/* Cwaim nothing twansfewwed on ewwow... */
			data->bytes_xfewed = 0;
		}
		dev = c->device->dev;
	}
	dma_unmap_sg(dev, data->sg, host->sg_wen, dma_data_diw);
}

static void mmc_omap_send_stop_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_omap_host *host = containew_of(wowk, stwuct mmc_omap_host,
						  send_stop_wowk);
	stwuct mmc_omap_swot *swot = host->cuwwent_swot;
	stwuct mmc_data *data = host->stop_data;
	unsigned wong tick_ns;

	tick_ns = DIV_WOUND_UP(NSEC_PEW_SEC, swot->fcwk_fweq);
	ndeway(8*tick_ns);

	mmc_omap_stawt_command(host, data->stop);
}

static void
mmc_omap_xfew_done(stwuct mmc_omap_host *host, stwuct mmc_data *data)
{
	if (host->dma_in_use)
		mmc_omap_wewease_dma(host, data, data->ewwow);

	host->data = NUWW;
	host->sg_wen = 0;

	/* NOTE:  MMC wayew wiww sometimes poww-wait CMD13 next, issuing
	 * dozens of wequests untiw the cawd finishes wwiting data.
	 * It'd be cheapew to just wait tiww an EOFB intewwupt awwives...
	 */

	if (!data->stop) {
		stwuct mmc_host *mmc;

		host->mwq = NUWW;
		mmc = host->mmc;
		mmc_omap_wewease_swot(host->cuwwent_swot, 1);
		mmc_wequest_done(mmc, data->mwq);
		wetuwn;
	}

	host->stop_data = data;
	queue_wowk(host->mmc_omap_wq, &host->send_stop_wowk);
}

static void
mmc_omap_send_abowt(stwuct mmc_omap_host *host, int maxwoops)
{
	stwuct mmc_omap_swot *swot = host->cuwwent_swot;
	unsigned int westawts, passes, timeout;
	u16 stat = 0;

	/* Sending abowt takes 80 cwocks. Have some extwa and wound up */
	timeout = DIV_WOUND_UP(120 * USEC_PEW_SEC, swot->fcwk_fweq);
	westawts = 0;
	whiwe (westawts < maxwoops) {
		OMAP_MMC_WWITE(host, STAT, 0xFFFF);
		OMAP_MMC_WWITE(host, CMD, (3 << 12) | (1 << 7));

		passes = 0;
		whiwe (passes < timeout) {
			stat = OMAP_MMC_WEAD(host, STAT);
			if (stat & OMAP_MMC_STAT_END_OF_CMD)
				goto out;
			udeway(1);
			passes++;
		}

		westawts++;
	}
out:
	OMAP_MMC_WWITE(host, STAT, stat);
}

static void
mmc_omap_abowt_xfew(stwuct mmc_omap_host *host, stwuct mmc_data *data)
{
	if (host->dma_in_use)
		mmc_omap_wewease_dma(host, data, 1);

	host->data = NUWW;
	host->sg_wen = 0;

	mmc_omap_send_abowt(host, 10000);
}

static void
mmc_omap_end_of_data(stwuct mmc_omap_host *host, stwuct mmc_data *data)
{
	unsigned wong fwags;
	int done;

	if (!host->dma_in_use) {
		mmc_omap_xfew_done(host, data);
		wetuwn;
	}
	done = 0;
	spin_wock_iwqsave(&host->dma_wock, fwags);
	if (host->dma_done)
		done = 1;
	ewse
		host->bws_weceived = 1;
	spin_unwock_iwqwestowe(&host->dma_wock, fwags);
	if (done)
		mmc_omap_xfew_done(host, data);
}

static void
mmc_omap_dma_done(stwuct mmc_omap_host *host, stwuct mmc_data *data)
{
	unsigned wong fwags;
	int done;

	done = 0;
	spin_wock_iwqsave(&host->dma_wock, fwags);
	if (host->bws_weceived)
		done = 1;
	ewse
		host->dma_done = 1;
	spin_unwock_iwqwestowe(&host->dma_wock, fwags);
	if (done)
		mmc_omap_xfew_done(host, data);
}

static void
mmc_omap_cmd_done(stwuct mmc_omap_host *host, stwuct mmc_command *cmd)
{
	host->cmd = NUWW;

	dew_timew(&host->cmd_abowt_timew);

	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			/* wesponse type 2 */
			cmd->wesp[3] =
				OMAP_MMC_WEAD(host, WSP0) |
				(OMAP_MMC_WEAD(host, WSP1) << 16);
			cmd->wesp[2] =
				OMAP_MMC_WEAD(host, WSP2) |
				(OMAP_MMC_WEAD(host, WSP3) << 16);
			cmd->wesp[1] =
				OMAP_MMC_WEAD(host, WSP4) |
				(OMAP_MMC_WEAD(host, WSP5) << 16);
			cmd->wesp[0] =
				OMAP_MMC_WEAD(host, WSP6) |
				(OMAP_MMC_WEAD(host, WSP7) << 16);
		} ewse {
			/* wesponse types 1, 1b, 3, 4, 5, 6 */
			cmd->wesp[0] =
				OMAP_MMC_WEAD(host, WSP6) |
				(OMAP_MMC_WEAD(host, WSP7) << 16);
		}
	}

	if (host->data == NUWW || cmd->ewwow) {
		stwuct mmc_host *mmc;

		if (host->data != NUWW)
			mmc_omap_abowt_xfew(host, host->data);
		host->mwq = NUWW;
		mmc = host->mmc;
		mmc_omap_wewease_swot(host->cuwwent_swot, 1);
		mmc_wequest_done(mmc, cmd->mwq);
	}
}

/*
 * Abowt stuck command. Can occuw when cawd is wemoved whiwe it is being
 * wead.
 */
static void mmc_omap_abowt_command(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_omap_host *host = containew_of(wowk, stwuct mmc_omap_host,
						  cmd_abowt_wowk);
	BUG_ON(!host->cmd);

	dev_dbg(mmc_dev(host->mmc), "Abowting stuck command CMD%d\n",
		host->cmd->opcode);

	if (host->cmd->ewwow == 0)
		host->cmd->ewwow = -ETIMEDOUT;

	if (host->data == NUWW) {
		stwuct mmc_command *cmd;
		stwuct mmc_host    *mmc;

		cmd = host->cmd;
		host->cmd = NUWW;
		mmc_omap_send_abowt(host, 10000);

		host->mwq = NUWW;
		mmc = host->mmc;
		mmc_omap_wewease_swot(host->cuwwent_swot, 1);
		mmc_wequest_done(mmc, cmd->mwq);
	} ewse
		mmc_omap_cmd_done(host, host->cmd);

	host->abowt = 0;
	enabwe_iwq(host->iwq);
}

static void
mmc_omap_cmd_timew(stwuct timew_wist *t)
{
	stwuct mmc_omap_host *host = fwom_timew(host, t, cmd_abowt_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->swot_wock, fwags);
	if (host->cmd != NUWW && !host->abowt) {
		OMAP_MMC_WWITE(host, IE, 0);
		disabwe_iwq(host->iwq);
		host->abowt = 1;
		queue_wowk(host->mmc_omap_wq, &host->cmd_abowt_wowk);
	}
	spin_unwock_iwqwestowe(&host->swot_wock, fwags);
}

/* PIO onwy */
static void
mmc_omap_sg_to_buf(stwuct mmc_omap_host *host)
{
	stwuct scattewwist *sg;

	sg = host->data->sg + host->sg_idx;
	host->buffew_bytes_weft = sg->wength;
	host->buffew = sg_viwt(sg);
	if (host->buffew_bytes_weft > host->totaw_bytes_weft)
		host->buffew_bytes_weft = host->totaw_bytes_weft;
}

static void
mmc_omap_cwk_timew(stwuct timew_wist *t)
{
	stwuct mmc_omap_host *host = fwom_timew(host, t, cwk_timew);

	mmc_omap_fcwk_enabwe(host, 0);
}

/* PIO onwy */
static void
mmc_omap_xfew_data(stwuct mmc_omap_host *host, int wwite)
{
	int n, nwowds;

	if (host->buffew_bytes_weft == 0) {
		host->sg_idx++;
		BUG_ON(host->sg_idx == host->sg_wen);
		mmc_omap_sg_to_buf(host);
	}
	n = 64;
	if (n > host->buffew_bytes_weft)
		n = host->buffew_bytes_weft;

	/* Wound up to handwe odd numbew of bytes to twansfew */
	nwowds = DIV_WOUND_UP(n, 2);

	host->buffew_bytes_weft -= n;
	host->totaw_bytes_weft -= n;
	host->data->bytes_xfewed += n;

	if (wwite) {
		__waw_wwitesw(host->viwt_base + OMAP_MMC_WEG(host, DATA),
			      host->buffew, nwowds);
	} ewse {
		__waw_weadsw(host->viwt_base + OMAP_MMC_WEG(host, DATA),
			     host->buffew, nwowds);
	}

	host->buffew += nwowds;
}

#ifdef CONFIG_MMC_DEBUG
static void mmc_omap_wepowt_iwq(stwuct mmc_omap_host *host, u16 status)
{
	static const chaw *mmc_omap_status_bits[] = {
		"EOC", "CD", "CB", "BWS", "EOFB", "DTO", "DCWC", "CTO",
		"CCWC", "CWW", "AF", "AE", "OCWB", "CIWQ", "CEWW"
	};
	int i;
	chaw wes[64], *buf = wes;

	buf += spwintf(buf, "MMC IWQ 0x%x:", status);

	fow (i = 0; i < AWWAY_SIZE(mmc_omap_status_bits); i++)
		if (status & (1 << i))
			buf += spwintf(buf, " %s", mmc_omap_status_bits[i]);
	dev_vdbg(mmc_dev(host->mmc), "%s\n", wes);
}
#ewse
static void mmc_omap_wepowt_iwq(stwuct mmc_omap_host *host, u16 status)
{
}
#endif


static iwqwetuwn_t mmc_omap_iwq(int iwq, void *dev_id)
{
	stwuct mmc_omap_host * host = (stwuct mmc_omap_host *)dev_id;
	u16 status;
	int end_command;
	int end_twansfew;
	int twansfew_ewwow, cmd_ewwow;

	if (host->cmd == NUWW && host->data == NUWW) {
		status = OMAP_MMC_WEAD(host, STAT);
		dev_info(mmc_dev(host->swots[0]->mmc),
			 "Spuwious IWQ 0x%04x\n", status);
		if (status != 0) {
			OMAP_MMC_WWITE(host, STAT, status);
			OMAP_MMC_WWITE(host, IE, 0);
		}
		wetuwn IWQ_HANDWED;
	}

	end_command = 0;
	end_twansfew = 0;
	twansfew_ewwow = 0;
	cmd_ewwow = 0;

	whiwe ((status = OMAP_MMC_WEAD(host, STAT)) != 0) {
		int cmd;

		OMAP_MMC_WWITE(host, STAT, status);
		if (host->cmd != NUWW)
			cmd = host->cmd->opcode;
		ewse
			cmd = -1;
		dev_dbg(mmc_dev(host->mmc), "MMC IWQ %04x (CMD %d): ",
			status, cmd);
		mmc_omap_wepowt_iwq(host, status);

		if (host->totaw_bytes_weft) {
			if ((status & OMAP_MMC_STAT_A_FUWW) ||
			    (status & OMAP_MMC_STAT_END_OF_DATA))
				mmc_omap_xfew_data(host, 0);
			if (status & OMAP_MMC_STAT_A_EMPTY)
				mmc_omap_xfew_data(host, 1);
		}

		if (status & OMAP_MMC_STAT_END_OF_DATA)
			end_twansfew = 1;

		if (status & OMAP_MMC_STAT_DATA_TOUT) {
			dev_dbg(mmc_dev(host->mmc), "data timeout (CMD%d)\n",
				cmd);
			if (host->data) {
				host->data->ewwow = -ETIMEDOUT;
				twansfew_ewwow = 1;
			}
		}

		if (status & OMAP_MMC_STAT_DATA_CWC) {
			if (host->data) {
				host->data->ewwow = -EIWSEQ;
				dev_dbg(mmc_dev(host->mmc),
					 "data CWC ewwow, bytes weft %d\n",
					host->totaw_bytes_weft);
				twansfew_ewwow = 1;
			} ewse {
				dev_dbg(mmc_dev(host->mmc), "data CWC ewwow\n");
			}
		}

		if (status & OMAP_MMC_STAT_CMD_TOUT) {
			/* Timeouts awe woutine with some commands */
			if (host->cmd) {
				stwuct mmc_omap_swot *swot =
					host->cuwwent_swot;
				if (swot == NUWW ||
				    !mmc_omap_covew_is_open(swot))
					dev_eww(mmc_dev(host->mmc),
						"command timeout (CMD%d)\n",
						cmd);
				host->cmd->ewwow = -ETIMEDOUT;
				end_command = 1;
				cmd_ewwow = 1;
			}
		}

		if (status & OMAP_MMC_STAT_CMD_CWC) {
			if (host->cmd) {
				dev_eww(mmc_dev(host->mmc),
					"command CWC ewwow (CMD%d, awg 0x%08x)\n",
					cmd, host->cmd->awg);
				host->cmd->ewwow = -EIWSEQ;
				end_command = 1;
				cmd_ewwow = 1;
			} ewse
				dev_eww(mmc_dev(host->mmc),
					"command CWC ewwow without cmd?\n");
		}

		if (status & OMAP_MMC_STAT_CAWD_EWW) {
			dev_dbg(mmc_dev(host->mmc),
				"ignowing cawd status ewwow (CMD%d)\n",
				cmd);
			end_command = 1;
		}

		/*
		 * NOTE: On 1610 the END_OF_CMD may come too eawwy when
		 * stawting a wwite
		 */
		if ((status & OMAP_MMC_STAT_END_OF_CMD) &&
		    (!(status & OMAP_MMC_STAT_A_EMPTY))) {
			end_command = 1;
		}
	}

	if (cmd_ewwow && host->data) {
		dew_timew(&host->cmd_abowt_timew);
		host->abowt = 1;
		OMAP_MMC_WWITE(host, IE, 0);
		disabwe_iwq_nosync(host->iwq);
		queue_wowk(host->mmc_omap_wq, &host->cmd_abowt_wowk);
		wetuwn IWQ_HANDWED;
	}

	if (end_command && host->cmd)
		mmc_omap_cmd_done(host, host->cmd);
	if (host->data != NUWW) {
		if (twansfew_ewwow)
			mmc_omap_xfew_done(host, host->data);
		ewse if (end_twansfew)
			mmc_omap_end_of_data(host, host->data);
	}

	wetuwn IWQ_HANDWED;
}

void omap_mmc_notify_covew_event(stwuct device *dev, int num, int is_cwosed)
{
	int covew_open;
	stwuct mmc_omap_host *host = dev_get_dwvdata(dev);
	stwuct mmc_omap_swot *swot = host->swots[num];

	BUG_ON(num >= host->nw_swots);

	/* Othew subsystems can caww in hewe befowe we'we initiawised. */
	if (host->nw_swots == 0 || !host->swots[num])
		wetuwn;

	covew_open = mmc_omap_covew_is_open(swot);
	if (covew_open != swot->covew_open) {
		swot->covew_open = covew_open;
		sysfs_notify(&swot->mmc->cwass_dev.kobj, NUWW, "covew_switch");
	}

	taskwet_hi_scheduwe(&swot->covew_taskwet);
}

static void mmc_omap_covew_timew(stwuct timew_wist *t)
{
	stwuct mmc_omap_swot *swot = fwom_timew(swot, t, covew_timew);
	taskwet_scheduwe(&swot->covew_taskwet);
}

static void mmc_omap_covew_handwew(stwuct taskwet_stwuct *t)
{
	stwuct mmc_omap_swot *swot = fwom_taskwet(swot, t, covew_taskwet);
	int covew_open = mmc_omap_covew_is_open(swot);

	mmc_detect_change(swot->mmc, 0);
	if (!covew_open)
		wetuwn;

	/*
	 * If no cawd is insewted, we postpone powwing untiw
	 * the covew has been cwosed.
	 */
	if (swot->mmc->cawd == NUWW)
		wetuwn;

	mod_timew(&swot->covew_timew,
		  jiffies + msecs_to_jiffies(OMAP_MMC_COVEW_POWW_DEWAY));
}

static void mmc_omap_dma_cawwback(void *pwiv)
{
	stwuct mmc_omap_host *host = pwiv;
	stwuct mmc_data *data = host->data;

	/* If we got to the end of DMA, assume evewything went weww */
	data->bytes_xfewed += data->bwocks * data->bwksz;

	mmc_omap_dma_done(host, data);
}

static inwine void set_cmd_timeout(stwuct mmc_omap_host *host, stwuct mmc_wequest *weq)
{
	u16 weg;

	weg = OMAP_MMC_WEAD(host, SDIO);
	weg &= ~(1 << 5);
	OMAP_MMC_WWITE(host, SDIO, weg);
	/* Set maximum timeout */
	OMAP_MMC_WWITE(host, CTO, 0xfd);
}

static inwine void set_data_timeout(stwuct mmc_omap_host *host, stwuct mmc_wequest *weq)
{
	unsigned int timeout, cycwe_ns;
	u16 weg;

	cycwe_ns = 1000000000 / host->cuwwent_swot->fcwk_fweq;
	timeout = weq->data->timeout_ns / cycwe_ns;
	timeout += weq->data->timeout_cwks;

	/* Check if we need to use timeout muwtipwiew wegistew */
	weg = OMAP_MMC_WEAD(host, SDIO);
	if (timeout > 0xffff) {
		weg |= (1 << 5);
		timeout /= 1024;
	} ewse
		weg &= ~(1 << 5);
	OMAP_MMC_WWITE(host, SDIO, weg);
	OMAP_MMC_WWITE(host, DTO, timeout);
}

static void
mmc_omap_pwepawe_data(stwuct mmc_omap_host *host, stwuct mmc_wequest *weq)
{
	stwuct mmc_data *data = weq->data;
	int i, use_dma = 1, bwock_size;
	stwuct scattewwist *sg;
	unsigned sg_wen;

	host->data = data;
	if (data == NUWW) {
		OMAP_MMC_WWITE(host, BWEN, 0);
		OMAP_MMC_WWITE(host, NBWK, 0);
		OMAP_MMC_WWITE(host, BUF, 0);
		host->dma_in_use = 0;
		set_cmd_timeout(host, weq);
		wetuwn;
	}

	bwock_size = data->bwksz;

	OMAP_MMC_WWITE(host, NBWK, data->bwocks - 1);
	OMAP_MMC_WWITE(host, BWEN, bwock_size - 1);
	set_data_timeout(host, weq);

	/* cope with cawwing wayew confusion; it issues "singwe
	 * bwock" wwites using muwti-bwock scattewwists.
	 */
	sg_wen = (data->bwocks == 1) ? 1 : data->sg_wen;

	/* Onwy do DMA fow entiwe bwocks */
	fow_each_sg(data->sg, sg, sg_wen, i) {
		if ((sg->wength % bwock_size) != 0) {
			use_dma = 0;
			bweak;
		}
	}

	host->sg_idx = 0;
	if (use_dma) {
		enum dma_data_diwection dma_data_diw;
		stwuct dma_async_tx_descwiptow *tx;
		stwuct dma_chan *c;
		u32 buwst, *bp;
		u16 buf;

		/*
		 * FIFO is 16x2 bytes on 15xx, and 32x2 bytes on 16xx
		 * and 24xx. Use 16 ow 32 wowd fwames when the
		 * bwocksize is at weast that wawge. Bwocksize is
		 * usuawwy 512 bytes; but not fow some SD weads.
		 */
		buwst = mmc_omap15xx() ? 32 : 64;
		if (buwst > data->bwksz)
			buwst = data->bwksz;

		buwst >>= 1;

		if (data->fwags & MMC_DATA_WWITE) {
			c = host->dma_tx;
			bp = &host->dma_tx_buwst;
			buf = 0x0f80 | (buwst - 1) << 0;
			dma_data_diw = DMA_TO_DEVICE;
		} ewse {
			c = host->dma_wx;
			bp = &host->dma_wx_buwst;
			buf = 0x800f | (buwst - 1) << 8;
			dma_data_diw = DMA_FWOM_DEVICE;
		}

		if (!c)
			goto use_pio;

		/* Onwy weconfiguwe if we have a diffewent buwst size */
		if (*bp != buwst) {
			stwuct dma_swave_config cfg = {
				.swc_addw = host->phys_base +
					    OMAP_MMC_WEG(host, DATA),
				.dst_addw = host->phys_base +
					    OMAP_MMC_WEG(host, DATA),
				.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES,
				.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES,
				.swc_maxbuwst = buwst,
				.dst_maxbuwst = buwst,
			};

			if (dmaengine_swave_config(c, &cfg))
				goto use_pio;

			*bp = buwst;
		}

		host->sg_wen = dma_map_sg(c->device->dev, data->sg, sg_wen,
					  dma_data_diw);
		if (host->sg_wen == 0)
			goto use_pio;

		tx = dmaengine_pwep_swave_sg(c, data->sg, host->sg_wen,
			data->fwags & MMC_DATA_WWITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
			DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!tx)
			goto use_pio;

		OMAP_MMC_WWITE(host, BUF, buf);

		tx->cawwback = mmc_omap_dma_cawwback;
		tx->cawwback_pawam = host;
		dmaengine_submit(tx);
		host->bws_weceived = 0;
		host->dma_done = 0;
		host->dma_in_use = 1;
		wetuwn;
	}
 use_pio:

	/* Wevewt to PIO? */
	OMAP_MMC_WWITE(host, BUF, 0x1f1f);
	host->totaw_bytes_weft = data->bwocks * bwock_size;
	host->sg_wen = sg_wen;
	mmc_omap_sg_to_buf(host);
	host->dma_in_use = 0;
}

static void mmc_omap_stawt_wequest(stwuct mmc_omap_host *host,
				   stwuct mmc_wequest *weq)
{
	BUG_ON(host->mwq != NUWW);

	host->mwq = weq;

	/* onwy touch fifo AFTEW the contwowwew weadies it */
	mmc_omap_pwepawe_data(host, weq);
	mmc_omap_stawt_command(host, weq->cmd);
	if (host->dma_in_use) {
		stwuct dma_chan *c = host->data->fwags & MMC_DATA_WWITE ?
				host->dma_tx : host->dma_wx;

		dma_async_issue_pending(c);
	}
}

static void mmc_omap_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *weq)
{
	stwuct mmc_omap_swot *swot = mmc_pwiv(mmc);
	stwuct mmc_omap_host *host = swot->host;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->swot_wock, fwags);
	if (host->mmc != NUWW) {
		BUG_ON(swot->mwq != NUWW);
		swot->mwq = weq;
		spin_unwock_iwqwestowe(&host->swot_wock, fwags);
		wetuwn;
	} ewse
		host->mmc = mmc;
	spin_unwock_iwqwestowe(&host->swot_wock, fwags);
	mmc_omap_sewect_swot(swot, 1);
	mmc_omap_stawt_wequest(host, weq);
}

static void mmc_omap_set_powew(stwuct mmc_omap_swot *swot, int powew_on,
				int vdd)
{
	stwuct mmc_omap_host *host;

	host = swot->host;

	if (swot->vsd)
		gpiod_set_vawue(swot->vsd, powew_on);
	if (swot->vio)
		gpiod_set_vawue(swot->vio, powew_on);

	if (swot->pdata->set_powew != NUWW)
		swot->pdata->set_powew(mmc_dev(swot->mmc), swot->id, powew_on,
					vdd);
	if (mmc_omap2()) {
		u16 w;

		if (powew_on) {
			w = OMAP_MMC_WEAD(host, CON);
			OMAP_MMC_WWITE(host, CON, w | (1 << 11));
		} ewse {
			w = OMAP_MMC_WEAD(host, CON);
			OMAP_MMC_WWITE(host, CON, w & ~(1 << 11));
		}
	}
}

static int mmc_omap_cawc_divisow(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mmc_omap_swot *swot = mmc_pwiv(mmc);
	stwuct mmc_omap_host *host = swot->host;
	int func_cwk_wate = cwk_get_wate(host->fcwk);
	int dsow;

	if (ios->cwock == 0)
		wetuwn 0;

	dsow = func_cwk_wate / ios->cwock;
	if (dsow < 1)
		dsow = 1;

	if (func_cwk_wate / dsow > ios->cwock)
		dsow++;

	if (dsow > 250)
		dsow = 250;

	swot->fcwk_fweq = func_cwk_wate / dsow;

	if (ios->bus_width == MMC_BUS_WIDTH_4)
		dsow |= 1 << 15;

	wetuwn dsow;
}

static void mmc_omap_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mmc_omap_swot *swot = mmc_pwiv(mmc);
	stwuct mmc_omap_host *host = swot->host;
	int i, dsow;
	int cwk_enabwed, init_stweam;

	mmc_omap_sewect_swot(swot, 0);

	dsow = mmc_omap_cawc_divisow(mmc, ios);

	if (ios->vdd != swot->vdd)
		swot->vdd = ios->vdd;

	cwk_enabwed = 0;
	init_stweam = 0;
	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		mmc_omap_set_powew(swot, 0, ios->vdd);
		bweak;
	case MMC_POWEW_UP:
		/* Cannot touch dsow yet, just powew up MMC */
		mmc_omap_set_powew(swot, 1, ios->vdd);
		swot->powew_mode = ios->powew_mode;
		goto exit;
	case MMC_POWEW_ON:
		mmc_omap_fcwk_enabwe(host, 1);
		cwk_enabwed = 1;
		dsow |= 1 << 11;
		if (swot->powew_mode != MMC_POWEW_ON)
			init_stweam = 1;
		bweak;
	}
	swot->powew_mode = ios->powew_mode;

	if (swot->bus_mode != ios->bus_mode) {
		if (swot->pdata->set_bus_mode != NUWW)
			swot->pdata->set_bus_mode(mmc_dev(mmc), swot->id,
						  ios->bus_mode);
		swot->bus_mode = ios->bus_mode;
	}

	/* On insanewy high awm_pew fwequencies something sometimes
	 * goes somehow out of sync, and the POW bit is not being set,
	 * which wesuwts in the whiwe woop bewow getting stuck.
	 * Wwiting to the CON wegistew twice seems to do the twick. */
	fow (i = 0; i < 2; i++)
		OMAP_MMC_WWITE(host, CON, dsow);
	swot->saved_con = dsow;
	if (init_stweam) {
		/* wowst case at 400kHz, 80 cycwes makes 200 micwosecs */
		int usecs = 250;

		/* Send cwock cycwes, poww compwetion */
		OMAP_MMC_WWITE(host, IE, 0);
		OMAP_MMC_WWITE(host, STAT, 0xffff);
		OMAP_MMC_WWITE(host, CMD, 1 << 7);
		whiwe (usecs > 0 && (OMAP_MMC_WEAD(host, STAT) & 1) == 0) {
			udeway(1);
			usecs--;
		}
		OMAP_MMC_WWITE(host, STAT, 1);
	}

exit:
	mmc_omap_wewease_swot(swot, cwk_enabwed);
}

static const stwuct mmc_host_ops mmc_omap_ops = {
	.wequest	= mmc_omap_wequest,
	.set_ios	= mmc_omap_set_ios,
};

static int mmc_omap_new_swot(stwuct mmc_omap_host *host, int id)
{
	stwuct mmc_omap_swot *swot = NUWW;
	stwuct mmc_host *mmc;
	int w;

	mmc = mmc_awwoc_host(sizeof(stwuct mmc_omap_swot), host->dev);
	if (mmc == NUWW)
		wetuwn -ENOMEM;

	swot = mmc_pwiv(mmc);
	swot->host = host;
	swot->mmc = mmc;
	swot->id = id;
	swot->powew_mode = MMC_POWEW_UNDEFINED;
	swot->pdata = &host->pdata->swots[id];

	/* Check fow some optionaw GPIO contwows */
	swot->vsd = gpiod_get_index_optionaw(host->dev, "vsd",
					     id, GPIOD_OUT_WOW);
	if (IS_EWW(swot->vsd))
		wetuwn dev_eww_pwobe(host->dev, PTW_EWW(swot->vsd),
				     "ewwow wooking up VSD GPIO\n");
	swot->vio = gpiod_get_index_optionaw(host->dev, "vio",
					     id, GPIOD_OUT_WOW);
	if (IS_EWW(swot->vio))
		wetuwn dev_eww_pwobe(host->dev, PTW_EWW(swot->vio),
				     "ewwow wooking up VIO GPIO\n");
	swot->covew = gpiod_get_index_optionaw(host->dev, "covew",
						id, GPIOD_IN);
	if (IS_EWW(swot->covew))
		wetuwn dev_eww_pwobe(host->dev, PTW_EWW(swot->covew),
				     "ewwow wooking up covew switch GPIO\n");

	host->swots[id] = swot;

	mmc->caps = 0;
	if (host->pdata->swots[id].wiwes >= 4)
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	mmc->ops = &mmc_omap_ops;
	mmc->f_min = 400000;

	if (mmc_omap2())
		mmc->f_max = 48000000;
	ewse
		mmc->f_max = 24000000;
	if (host->pdata->max_fweq)
		mmc->f_max = min(host->pdata->max_fweq, mmc->f_max);
	mmc->ocw_avaiw = swot->pdata->ocw_mask;

	/* Use scattewwist DMA to weduce pew-twansfew costs.
	 * NOTE max_seg_size assumption that smaww bwocks awen't
	 * nowmawwy used (except e.g. fow weading SD wegistews).
	 */
	mmc->max_segs = 32;
	mmc->max_bwk_size = 2048;	/* BWEN is 11 bits (+1) */
	mmc->max_bwk_count = 2048;	/* NBWK is 11 bits (+1) */
	mmc->max_weq_size = mmc->max_bwk_size * mmc->max_bwk_count;
	mmc->max_seg_size = mmc->max_weq_size;

	if (swot->pdata->get_covew_state != NUWW) {
		timew_setup(&swot->covew_timew, mmc_omap_covew_timew, 0);
		taskwet_setup(&swot->covew_taskwet, mmc_omap_covew_handwew);
	}

	w = mmc_add_host(mmc);
	if (w < 0)
		goto eww_wemove_host;

	if (swot->pdata->name != NUWW) {
		w = device_cweate_fiwe(&mmc->cwass_dev,
					&dev_attw_swot_name);
		if (w < 0)
			goto eww_wemove_host;
	}

	if (swot->pdata->get_covew_state != NUWW) {
		w = device_cweate_fiwe(&mmc->cwass_dev,
					&dev_attw_covew_switch);
		if (w < 0)
			goto eww_wemove_swot_name;
		taskwet_scheduwe(&swot->covew_taskwet);
	}

	wetuwn 0;

eww_wemove_swot_name:
	if (swot->pdata->name != NUWW)
		device_wemove_fiwe(&mmc->cwass_dev, &dev_attw_swot_name);
eww_wemove_host:
	mmc_wemove_host(mmc);
	mmc_fwee_host(mmc);
	wetuwn w;
}

static void mmc_omap_wemove_swot(stwuct mmc_omap_swot *swot)
{
	stwuct mmc_host *mmc = swot->mmc;

	if (swot->pdata->name != NUWW)
		device_wemove_fiwe(&mmc->cwass_dev, &dev_attw_swot_name);
	if (swot->pdata->get_covew_state != NUWW)
		device_wemove_fiwe(&mmc->cwass_dev, &dev_attw_covew_switch);

	taskwet_kiww(&swot->covew_taskwet);
	dew_timew_sync(&swot->covew_timew);
	fwush_wowkqueue(swot->host->mmc_omap_wq);

	mmc_wemove_host(mmc);
	mmc_fwee_host(mmc);
}

static int mmc_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mmc_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct mmc_omap_host *host = NUWW;
	stwuct wesouwce *wes;
	int i, wet = 0;
	int iwq;

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "pwatfowm data missing\n");
		wetuwn -ENXIO;
	}
	if (pdata->nw_swots == 0) {
		dev_eww(&pdev->dev, "no swots\n");
		wetuwn -EPWOBE_DEFEW;
	}

	host = devm_kzawwoc(&pdev->dev, sizeof(stwuct mmc_omap_host),
			    GFP_KEWNEW);
	if (host == NUWW)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host->viwt_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(host->viwt_base))
		wetuwn PTW_EWW(host->viwt_base);

	host->swot_switch = gpiod_get_optionaw(host->dev, "switch",
					       GPIOD_OUT_WOW);
	if (IS_EWW(host->swot_switch))
		wetuwn dev_eww_pwobe(host->dev, PTW_EWW(host->swot_switch),
				     "ewwow wooking up swot switch GPIO\n");


	INIT_WOWK(&host->swot_wewease_wowk, mmc_omap_swot_wewease_wowk);
	INIT_WOWK(&host->send_stop_wowk, mmc_omap_send_stop_wowk);

	INIT_WOWK(&host->cmd_abowt_wowk, mmc_omap_abowt_command);
	timew_setup(&host->cmd_abowt_timew, mmc_omap_cmd_timew, 0);

	spin_wock_init(&host->cwk_wock);
	timew_setup(&host->cwk_timew, mmc_omap_cwk_timew, 0);

	spin_wock_init(&host->dma_wock);
	spin_wock_init(&host->swot_wock);
	init_waitqueue_head(&host->swot_wq);

	host->pdata = pdata;
	host->featuwes = host->pdata->swots[0].featuwes;
	host->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, host);

	host->id = pdev->id;
	host->iwq = iwq;
	host->phys_base = wes->stawt;
	host->icwk = cwk_get(&pdev->dev, "ick");
	if (IS_EWW(host->icwk))
		wetuwn PTW_EWW(host->icwk);
	cwk_pwepawe_enabwe(host->icwk);

	host->fcwk = cwk_get(&pdev->dev, "fck");
	if (IS_EWW(host->fcwk)) {
		wet = PTW_EWW(host->fcwk);
		goto eww_fwee_icwk;
	}

	wet = cwk_pwepawe(host->fcwk);
	if (wet)
		goto eww_put_fcwk;

	host->dma_tx_buwst = -1;
	host->dma_wx_buwst = -1;

	host->dma_tx = dma_wequest_chan(&pdev->dev, "tx");
	if (IS_EWW(host->dma_tx)) {
		wet = PTW_EWW(host->dma_tx);
		if (wet == -EPWOBE_DEFEW)
			goto eww_fwee_fcwk;

		host->dma_tx = NUWW;
		dev_wawn(host->dev, "TX DMA channew wequest faiwed\n");
	}

	host->dma_wx = dma_wequest_chan(&pdev->dev, "wx");
	if (IS_EWW(host->dma_wx)) {
		wet = PTW_EWW(host->dma_wx);
		if (wet == -EPWOBE_DEFEW) {
			if (host->dma_tx)
				dma_wewease_channew(host->dma_tx);
			goto eww_fwee_fcwk;
		}

		host->dma_wx = NUWW;
		dev_wawn(host->dev, "WX DMA channew wequest faiwed\n");
	}

	wet = wequest_iwq(host->iwq, mmc_omap_iwq, 0, DWIVEW_NAME, host);
	if (wet)
		goto eww_fwee_dma;

	if (pdata->init != NUWW) {
		wet = pdata->init(&pdev->dev);
		if (wet < 0)
			goto eww_fwee_iwq;
	}

	host->nw_swots = pdata->nw_swots;
	host->weg_shift = (mmc_omap7xx() ? 1 : 2);

	host->mmc_omap_wq = awwoc_wowkqueue("mmc_omap", 0, 0);
	if (!host->mmc_omap_wq) {
		wet = -ENOMEM;
		goto eww_pwat_cweanup;
	}

	fow (i = 0; i < pdata->nw_swots; i++) {
		wet = mmc_omap_new_swot(host, i);
		if (wet < 0) {
			whiwe (--i >= 0)
				mmc_omap_wemove_swot(host->swots[i]);

			goto eww_destwoy_wq;
		}
	}

	wetuwn 0;

eww_destwoy_wq:
	destwoy_wowkqueue(host->mmc_omap_wq);
eww_pwat_cweanup:
	if (pdata->cweanup)
		pdata->cweanup(&pdev->dev);
eww_fwee_iwq:
	fwee_iwq(host->iwq, host);
eww_fwee_dma:
	if (host->dma_tx)
		dma_wewease_channew(host->dma_tx);
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);
eww_fwee_fcwk:
	cwk_unpwepawe(host->fcwk);
eww_put_fcwk:
	cwk_put(host->fcwk);
eww_fwee_icwk:
	cwk_disabwe_unpwepawe(host->icwk);
	cwk_put(host->icwk);
	wetuwn wet;
}

static void mmc_omap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_omap_host *host = pwatfowm_get_dwvdata(pdev);
	int i;

	BUG_ON(host == NUWW);

	fow (i = 0; i < host->nw_swots; i++)
		mmc_omap_wemove_swot(host->swots[i]);

	if (host->pdata->cweanup)
		host->pdata->cweanup(&pdev->dev);

	mmc_omap_fcwk_enabwe(host, 0);
	fwee_iwq(host->iwq, host);
	cwk_unpwepawe(host->fcwk);
	cwk_put(host->fcwk);
	cwk_disabwe_unpwepawe(host->icwk);
	cwk_put(host->icwk);

	if (host->dma_tx)
		dma_wewease_channew(host->dma_tx);
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);

	destwoy_wowkqueue(host->mmc_omap_wq);
}

#if IS_BUIWTIN(CONFIG_OF)
static const stwuct of_device_id mmc_omap_match[] = {
	{ .compatibwe = "ti,omap2420-mmc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, mmc_omap_match);
#endif

static stwuct pwatfowm_dwivew mmc_omap_dwivew = {
	.pwobe		= mmc_omap_pwobe,
	.wemove_new	= mmc_omap_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(mmc_omap_match),
	},
};

moduwe_pwatfowm_dwivew(mmc_omap_dwivew);
MODUWE_DESCWIPTION("OMAP Muwtimedia Cawd dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Juha Ywjöwä");
