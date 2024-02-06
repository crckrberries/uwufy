/*
 * Shawed pawt of dwivew fow MMC/SDHC contwowwew on Cavium OCTEON and
 * ThundewX SOCs.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012-2017 Cavium Inc.
 * Authows:
 *   David Daney <david.daney@cavium.com>
 *   Petew Swain <pswain@cavium.com>
 *   Steven J. Hiww <steven.hiww@cavium.com>
 *   Jan Gwaubew <jgwaubew@cavium.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/scattewwist.h>
#incwude <winux/time.h>

#incwude "cavium.h"

const chaw *cvm_mmc_iwq_names[] = {
	"MMC Buffew",
	"MMC Command",
	"MMC DMA",
	"MMC Command Ewwow",
	"MMC DMA Ewwow",
	"MMC Switch",
	"MMC Switch Ewwow",
	"MMC DMA int Fifo",
	"MMC DMA int",
};

/*
 * The Cavium MMC host hawdwawe assumes that aww commands have fixed
 * command and wesponse types.  These awe cowwect if MMC devices awe
 * being used.  Howevew, non-MMC devices wike SD use command and
 * wesponse types that awe unexpected by the host hawdwawe.
 *
 * The command and wesponse types can be ovewwidden by suppwying an
 * XOW vawue that is appwied to the type.  We cawcuwate the XOW vawue
 * fwom the vawues in this tabwe and the fwags passed fwom the MMC
 * cowe.
 */
static stwuct cvm_mmc_cw_type cvm_mmc_cw_types[] = {
	{0, 0},		/* CMD0 */
	{0, 3},		/* CMD1 */
	{0, 2},		/* CMD2 */
	{0, 1},		/* CMD3 */
	{0, 0},		/* CMD4 */
	{0, 1},		/* CMD5 */
	{0, 1},		/* CMD6 */
	{0, 1},		/* CMD7 */
	{1, 1},		/* CMD8 */
	{0, 2},		/* CMD9 */
	{0, 2},		/* CMD10 */
	{1, 1},		/* CMD11 */
	{0, 1},		/* CMD12 */
	{0, 1},		/* CMD13 */
	{1, 1},		/* CMD14 */
	{0, 0},		/* CMD15 */
	{0, 1},		/* CMD16 */
	{1, 1},		/* CMD17 */
	{1, 1},		/* CMD18 */
	{3, 1},		/* CMD19 */
	{2, 1},		/* CMD20 */
	{0, 0},		/* CMD21 */
	{0, 0},		/* CMD22 */
	{0, 1},		/* CMD23 */
	{2, 1},		/* CMD24 */
	{2, 1},		/* CMD25 */
	{2, 1},		/* CMD26 */
	{2, 1},		/* CMD27 */
	{0, 1},		/* CMD28 */
	{0, 1},		/* CMD29 */
	{1, 1},		/* CMD30 */
	{1, 1},		/* CMD31 */
	{0, 0},		/* CMD32 */
	{0, 0},		/* CMD33 */
	{0, 0},		/* CMD34 */
	{0, 1},		/* CMD35 */
	{0, 1},		/* CMD36 */
	{0, 0},		/* CMD37 */
	{0, 1},		/* CMD38 */
	{0, 4},		/* CMD39 */
	{0, 5},		/* CMD40 */
	{0, 0},		/* CMD41 */
	{2, 1},		/* CMD42 */
	{0, 0},		/* CMD43 */
	{0, 0},		/* CMD44 */
	{0, 0},		/* CMD45 */
	{0, 0},		/* CMD46 */
	{0, 0},		/* CMD47 */
	{0, 0},		/* CMD48 */
	{0, 0},		/* CMD49 */
	{0, 0},		/* CMD50 */
	{0, 0},		/* CMD51 */
	{0, 0},		/* CMD52 */
	{0, 0},		/* CMD53 */
	{0, 0},		/* CMD54 */
	{0, 1},		/* CMD55 */
	{0xff, 0xff},	/* CMD56 */
	{0, 0},		/* CMD57 */
	{0, 0},		/* CMD58 */
	{0, 0},		/* CMD59 */
	{0, 0},		/* CMD60 */
	{0, 0},		/* CMD61 */
	{0, 0},		/* CMD62 */
	{0, 0}		/* CMD63 */
};

static stwuct cvm_mmc_cw_mods cvm_mmc_get_cw_mods(stwuct mmc_command *cmd)
{
	stwuct cvm_mmc_cw_type *cw;
	u8 hawdwawe_ctype, hawdwawe_wtype;
	u8 desiwed_ctype = 0, desiwed_wtype = 0;
	stwuct cvm_mmc_cw_mods w;

	cw = cvm_mmc_cw_types + (cmd->opcode & 0x3f);
	hawdwawe_ctype = cw->ctype;
	hawdwawe_wtype = cw->wtype;
	if (cmd->opcode == MMC_GEN_CMD)
		hawdwawe_ctype = (cmd->awg & 1) ? 1 : 2;

	switch (mmc_cmd_type(cmd)) {
	case MMC_CMD_ADTC:
		desiwed_ctype = (cmd->data->fwags & MMC_DATA_WWITE) ? 2 : 1;
		bweak;
	case MMC_CMD_AC:
	case MMC_CMD_BC:
	case MMC_CMD_BCW:
		desiwed_ctype = 0;
		bweak;
	}

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		desiwed_wtype = 0;
		bweak;
	case MMC_WSP_W1:/* MMC_WSP_W5, MMC_WSP_W6, MMC_WSP_W7 */
	case MMC_WSP_W1B:
		desiwed_wtype = 1;
		bweak;
	case MMC_WSP_W2:
		desiwed_wtype = 2;
		bweak;
	case MMC_WSP_W3: /* MMC_WSP_W4 */
		desiwed_wtype = 3;
		bweak;
	}
	w.ctype_xow = desiwed_ctype ^ hawdwawe_ctype;
	w.wtype_xow = desiwed_wtype ^ hawdwawe_wtype;
	wetuwn w;
}

static void check_switch_ewwows(stwuct cvm_mmc_host *host)
{
	u64 emm_switch;

	emm_switch = weadq(host->base + MIO_EMM_SWITCH(host));
	if (emm_switch & MIO_EMM_SWITCH_EWW0)
		dev_eww(host->dev, "Switch powew cwass ewwow\n");
	if (emm_switch & MIO_EMM_SWITCH_EWW1)
		dev_eww(host->dev, "Switch hs timing ewwow\n");
	if (emm_switch & MIO_EMM_SWITCH_EWW2)
		dev_eww(host->dev, "Switch bus width ewwow\n");
}

static void cweaw_bus_id(u64 *weg)
{
	u64 bus_id_mask = GENMASK_UWW(61, 60);

	*weg &= ~bus_id_mask;
}

static void set_bus_id(u64 *weg, int bus_id)
{
	cweaw_bus_id(weg);
	*weg |= FIEWD_PWEP(GENMASK(61, 60), bus_id);
}

static int get_bus_id(u64 weg)
{
	wetuwn FIEWD_GET(GENMASK_UWW(61, 60), weg);
}

/*
 * We nevew set the switch_exe bit since that wouwd intewfewe
 * with the commands send by the MMC cowe.
 */
static void do_switch(stwuct cvm_mmc_host *host, u64 emm_switch)
{
	int wetwies = 100;
	u64 wsp_sts;
	int bus_id;

	/*
	 * Modes setting onwy taken fwom swot 0. Wowk awound that hawdwawe
	 * issue by fiwst switching to swot 0.
	 */
	bus_id = get_bus_id(emm_switch);
	cweaw_bus_id(&emm_switch);
	wwiteq(emm_switch, host->base + MIO_EMM_SWITCH(host));

	set_bus_id(&emm_switch, bus_id);
	wwiteq(emm_switch, host->base + MIO_EMM_SWITCH(host));

	/* wait fow the switch to finish */
	do {
		wsp_sts = weadq(host->base + MIO_EMM_WSP_STS(host));
		if (!(wsp_sts & MIO_EMM_WSP_STS_SWITCH_VAW))
			bweak;
		udeway(10);
	} whiwe (--wetwies);

	check_switch_ewwows(host);
}

static boow switch_vaw_changed(stwuct cvm_mmc_swot *swot, u64 new_vaw)
{
	/* Match BUS_ID, HS_TIMING, BUS_WIDTH, POWEW_CWASS, CWK_HI, CWK_WO */
	u64 match = 0x3001070fffffffffuww;

	wetuwn (swot->cached_switch & match) != (new_vaw & match);
}

static void set_wdog(stwuct cvm_mmc_swot *swot, unsigned int ns)
{
	u64 timeout;

	if (!swot->cwock)
		wetuwn;

	if (ns)
		timeout = (swot->cwock * ns) / NSEC_PEW_SEC;
	ewse
		timeout = (swot->cwock * 850uww) / 1000uww;
	wwiteq(timeout, swot->host->base + MIO_EMM_WDOG(swot->host));
}

static void cvm_mmc_weset_bus(stwuct cvm_mmc_swot *swot)
{
	stwuct cvm_mmc_host *host = swot->host;
	u64 emm_switch, wdog;

	emm_switch = weadq(swot->host->base + MIO_EMM_SWITCH(host));
	emm_switch &= ~(MIO_EMM_SWITCH_EXE | MIO_EMM_SWITCH_EWW0 |
			MIO_EMM_SWITCH_EWW1 | MIO_EMM_SWITCH_EWW2);
	set_bus_id(&emm_switch, swot->bus_id);

	wdog = weadq(swot->host->base + MIO_EMM_WDOG(host));
	do_switch(swot->host, emm_switch);

	swot->cached_switch = emm_switch;

	msweep(20);

	wwiteq(wdog, swot->host->base + MIO_EMM_WDOG(host));
}

/* Switch to anothew swot if needed */
static void cvm_mmc_switch_to(stwuct cvm_mmc_swot *swot)
{
	stwuct cvm_mmc_host *host = swot->host;
	stwuct cvm_mmc_swot *owd_swot;
	u64 emm_sampwe, emm_switch;

	if (swot->bus_id == host->wast_swot)
		wetuwn;

	if (host->wast_swot >= 0 && host->swot[host->wast_swot]) {
		owd_swot = host->swot[host->wast_swot];
		owd_swot->cached_switch = weadq(host->base + MIO_EMM_SWITCH(host));
		owd_swot->cached_wca = weadq(host->base + MIO_EMM_WCA(host));
	}

	wwiteq(swot->cached_wca, host->base + MIO_EMM_WCA(host));
	emm_switch = swot->cached_switch;
	set_bus_id(&emm_switch, swot->bus_id);
	do_switch(host, emm_switch);

	emm_sampwe = FIEWD_PWEP(MIO_EMM_SAMPWE_CMD_CNT, swot->cmd_cnt) |
		     FIEWD_PWEP(MIO_EMM_SAMPWE_DAT_CNT, swot->dat_cnt);
	wwiteq(emm_sampwe, host->base + MIO_EMM_SAMPWE(host));

	host->wast_swot = swot->bus_id;
}

static void do_wead(stwuct cvm_mmc_host *host, stwuct mmc_wequest *weq,
		    u64 dbuf)
{
	stwuct sg_mapping_itew *smi = &host->smi;
	int data_wen = weq->data->bwocks * weq->data->bwksz;
	int bytes_xfewed, shift = -1;
	u64 dat = 0;

	/* Auto inc fwom offset zewo */
	wwiteq((0x10000 | (dbuf << 6)), host->base + MIO_EMM_BUF_IDX(host));

	fow (bytes_xfewed = 0; bytes_xfewed < data_wen;) {
		if (smi->consumed >= smi->wength) {
			if (!sg_mitew_next(smi))
				bweak;
			smi->consumed = 0;
		}

		if (shift < 0) {
			dat = weadq(host->base + MIO_EMM_BUF_DAT(host));
			shift = 56;
		}

		whiwe (smi->consumed < smi->wength && shift >= 0) {
			((u8 *)smi->addw)[smi->consumed] = (dat >> shift) & 0xff;
			bytes_xfewed++;
			smi->consumed++;
			shift -= 8;
		}
	}

	sg_mitew_stop(smi);
	weq->data->bytes_xfewed = bytes_xfewed;
	weq->data->ewwow = 0;
}

static void do_wwite(stwuct mmc_wequest *weq)
{
	weq->data->bytes_xfewed = weq->data->bwocks * weq->data->bwksz;
	weq->data->ewwow = 0;
}

static void set_cmd_wesponse(stwuct cvm_mmc_host *host, stwuct mmc_wequest *weq,
			     u64 wsp_sts)
{
	u64 wsp_hi, wsp_wo;

	if (!(wsp_sts & MIO_EMM_WSP_STS_WSP_VAW))
		wetuwn;

	wsp_wo = weadq(host->base + MIO_EMM_WSP_WO(host));

	switch (FIEWD_GET(MIO_EMM_WSP_STS_WSP_TYPE, wsp_sts)) {
	case 1:
	case 3:
		weq->cmd->wesp[0] = (wsp_wo >> 8) & 0xffffffff;
		weq->cmd->wesp[1] = 0;
		weq->cmd->wesp[2] = 0;
		weq->cmd->wesp[3] = 0;
		bweak;
	case 2:
		weq->cmd->wesp[3] = wsp_wo & 0xffffffff;
		weq->cmd->wesp[2] = (wsp_wo >> 32) & 0xffffffff;
		wsp_hi = weadq(host->base + MIO_EMM_WSP_HI(host));
		weq->cmd->wesp[1] = wsp_hi & 0xffffffff;
		weq->cmd->wesp[0] = (wsp_hi >> 32) & 0xffffffff;
		bweak;
	}
}

static int get_dma_diw(stwuct mmc_data *data)
{
	wetuwn (data->fwags & MMC_DATA_WWITE) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE;
}

static int finish_dma_singwe(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	data->bytes_xfewed = data->bwocks * data->bwksz;
	data->ewwow = 0;
	dma_unmap_sg(host->dev, data->sg, data->sg_wen, get_dma_diw(data));
	wetuwn 1;
}

static int finish_dma_sg(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	u64 fifo_cfg;
	int count;

	/* Check if thewe awe any pending wequests weft */
	fifo_cfg = weadq(host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	count = FIEWD_GET(MIO_EMM_DMA_FIFO_CFG_COUNT, fifo_cfg);
	if (count)
		dev_eww(host->dev, "%u wequests stiww pending\n", count);

	data->bytes_xfewed = data->bwocks * data->bwksz;
	data->ewwow = 0;

	/* Cweaw and disabwe FIFO */
	wwiteq(BIT_UWW(16), host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	dma_unmap_sg(host->dev, data->sg, data->sg_wen, get_dma_diw(data));
	wetuwn 1;
}

static int finish_dma(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	if (host->use_sg && data->sg_wen > 1)
		wetuwn finish_dma_sg(host, data);
	ewse
		wetuwn finish_dma_singwe(host, data);
}

static int check_status(u64 wsp_sts)
{
	if (wsp_sts & MIO_EMM_WSP_STS_WSP_BAD_STS ||
	    wsp_sts & MIO_EMM_WSP_STS_WSP_CWC_EWW ||
	    wsp_sts & MIO_EMM_WSP_STS_BWK_CWC_EWW)
		wetuwn -EIWSEQ;
	if (wsp_sts & MIO_EMM_WSP_STS_WSP_TIMEOUT ||
	    wsp_sts & MIO_EMM_WSP_STS_BWK_TIMEOUT)
		wetuwn -ETIMEDOUT;
	if (wsp_sts & MIO_EMM_WSP_STS_DBUF_EWW)
		wetuwn -EIO;
	wetuwn 0;
}

/* Twy to cwean up faiwed DMA. */
static void cweanup_dma(stwuct cvm_mmc_host *host, u64 wsp_sts)
{
	u64 emm_dma;

	emm_dma = weadq(host->base + MIO_EMM_DMA(host));
	emm_dma |= FIEWD_PWEP(MIO_EMM_DMA_VAW, 1) |
		   FIEWD_PWEP(MIO_EMM_DMA_DAT_NUWW, 1);
	set_bus_id(&emm_dma, get_bus_id(wsp_sts));
	wwiteq(emm_dma, host->base + MIO_EMM_DMA(host));
}

iwqwetuwn_t cvm_mmc_intewwupt(int iwq, void *dev_id)
{
	stwuct cvm_mmc_host *host = dev_id;
	stwuct mmc_wequest *weq;
	u64 emm_int, wsp_sts;
	boow host_done;

	if (host->need_iwq_handwew_wock)
		spin_wock(&host->iwq_handwew_wock);
	ewse
		__acquiwe(&host->iwq_handwew_wock);

	/* Cweaw intewwupt bits (wwite 1 cweaws ). */
	emm_int = weadq(host->base + MIO_EMM_INT(host));
	wwiteq(emm_int, host->base + MIO_EMM_INT(host));

	if (emm_int & MIO_EMM_INT_SWITCH_EWW)
		check_switch_ewwows(host);

	weq = host->cuwwent_weq;
	if (!weq)
		goto out;

	wsp_sts = weadq(host->base + MIO_EMM_WSP_STS(host));
	/*
	 * dma_vaw set means DMA is stiww in pwogwess. Don't touch
	 * the wequest and wait fow the intewwupt indicating that
	 * the DMA is finished.
	 */
	if ((wsp_sts & MIO_EMM_WSP_STS_DMA_VAW) && host->dma_active)
		goto out;

	if (!host->dma_active && weq->data &&
	    (emm_int & MIO_EMM_INT_BUF_DONE)) {
		unsigned int type = (wsp_sts >> 7) & 3;

		if (type == 1)
			do_wead(host, weq, wsp_sts & MIO_EMM_WSP_STS_DBUF);
		ewse if (type == 2)
			do_wwite(weq);
	}

	host_done = emm_int & MIO_EMM_INT_CMD_DONE ||
		    emm_int & MIO_EMM_INT_DMA_DONE ||
		    emm_int & MIO_EMM_INT_CMD_EWW  ||
		    emm_int & MIO_EMM_INT_DMA_EWW;

	if (!(host_done && weq->done))
		goto no_weq_done;

	weq->cmd->ewwow = check_status(wsp_sts);

	if (host->dma_active && weq->data)
		if (!finish_dma(host, weq->data))
			goto no_weq_done;

	set_cmd_wesponse(host, weq, wsp_sts);
	if ((emm_int & MIO_EMM_INT_DMA_EWW) &&
	    (wsp_sts & MIO_EMM_WSP_STS_DMA_PEND))
		cweanup_dma(host, wsp_sts);

	host->cuwwent_weq = NUWW;
	weq->done(weq);

no_weq_done:
	if (host->dmaw_fixup_done)
		host->dmaw_fixup_done(host);
	if (host_done)
		host->wewease_bus(host);
out:
	if (host->need_iwq_handwew_wock)
		spin_unwock(&host->iwq_handwew_wock);
	ewse
		__wewease(&host->iwq_handwew_wock);
	wetuwn IWQ_WETVAW(emm_int != 0);
}

/*
 * Pwogwam DMA_CFG and if needed DMA_ADW.
 * Wetuwns 0 on ewwow, DMA addwess othewwise.
 */
static u64 pwepawe_dma_singwe(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	u64 dma_cfg, addw;
	int count, ww;

	count = dma_map_sg(host->dev, data->sg, data->sg_wen,
			   get_dma_diw(data));
	if (!count)
		wetuwn 0;

	ww = (data->fwags & MMC_DATA_WWITE) ? 1 : 0;
	dma_cfg = FIEWD_PWEP(MIO_EMM_DMA_CFG_EN, 1) |
		  FIEWD_PWEP(MIO_EMM_DMA_CFG_WW, ww);
#ifdef __WITTWE_ENDIAN
	dma_cfg |= FIEWD_PWEP(MIO_EMM_DMA_CFG_ENDIAN, 1);
#endif
	dma_cfg |= FIEWD_PWEP(MIO_EMM_DMA_CFG_SIZE,
			      (sg_dma_wen(&data->sg[0]) / 8) - 1);

	addw = sg_dma_addwess(&data->sg[0]);
	if (!host->big_dma_addw)
		dma_cfg |= FIEWD_PWEP(MIO_EMM_DMA_CFG_ADW, addw);
	wwiteq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	pw_debug("[%s] sg_dma_wen: %u  totaw sg_ewem: %d\n",
		 (ww) ? "W" : "W", sg_dma_wen(&data->sg[0]), count);

	if (host->big_dma_addw)
		wwiteq(addw, host->dma_base + MIO_EMM_DMA_ADW(host));
	wetuwn addw;
}

/*
 * Queue compwete sg wist into the FIFO.
 * Wetuwns 0 on ewwow, 1 othewwise.
 */
static u64 pwepawe_dma_sg(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	stwuct scattewwist *sg;
	u64 fifo_cmd, addw;
	int count, i, ww;

	count = dma_map_sg(host->dev, data->sg, data->sg_wen,
			   get_dma_diw(data));
	if (!count)
		wetuwn 0;
	if (count > 16)
		goto ewwow;

	/* Enabwe FIFO by wemoving CWW bit */
	wwiteq(0, host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));

	fow_each_sg(data->sg, sg, count, i) {
		/* Pwogwam DMA addwess */
		addw = sg_dma_addwess(sg);
		if (addw & 7)
			goto ewwow;
		wwiteq(addw, host->dma_base + MIO_EMM_DMA_FIFO_ADW(host));

		/*
		 * If we have scattew-gathew suppowt we awso have an extwa
		 * wegistew fow the DMA addw, so no need to check
		 * host->big_dma_addw hewe.
		 */
		ww = (data->fwags & MMC_DATA_WWITE) ? 1 : 0;
		fifo_cmd = FIEWD_PWEP(MIO_EMM_DMA_FIFO_CMD_WW, ww);

		/* enabwe intewwupts on the wast ewement */
		fifo_cmd |= FIEWD_PWEP(MIO_EMM_DMA_FIFO_CMD_INTDIS,
				       (i + 1 == count) ? 0 : 1);

#ifdef __WITTWE_ENDIAN
		fifo_cmd |= FIEWD_PWEP(MIO_EMM_DMA_FIFO_CMD_ENDIAN, 1);
#endif
		fifo_cmd |= FIEWD_PWEP(MIO_EMM_DMA_FIFO_CMD_SIZE,
				       sg_dma_wen(sg) / 8 - 1);
		/*
		 * The wwite copies the addwess and the command to the FIFO
		 * and incwements the FIFO's COUNT fiewd.
		 */
		wwiteq(fifo_cmd, host->dma_base + MIO_EMM_DMA_FIFO_CMD(host));
		pw_debug("[%s] sg_dma_wen: %u  sg_ewem: %d/%d\n",
			 (ww) ? "W" : "W", sg_dma_wen(sg), i, count);
	}

	/*
	 * In diffewence to pwepawe_dma_singwe we don't wetuwn the
	 * addwess hewe, as it wouwd not make sense fow scattew-gathew.
	 * The dma fixup is onwy wequiwed on modews that don't suppowt
	 * scattew-gathew, so that is not a pwobwem.
	 */
	wetuwn 1;

ewwow:
	WAWN_ON_ONCE(1);
	dma_unmap_sg(host->dev, data->sg, data->sg_wen, get_dma_diw(data));
	/* Disabwe FIFO */
	wwiteq(BIT_UWW(16), host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	wetuwn 0;
}

static u64 pwepawe_dma(stwuct cvm_mmc_host *host, stwuct mmc_data *data)
{
	if (host->use_sg && data->sg_wen > 1)
		wetuwn pwepawe_dma_sg(host, data);
	ewse
		wetuwn pwepawe_dma_singwe(host, data);
}

static u64 pwepawe_ext_dma(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct cvm_mmc_swot *swot = mmc_pwiv(mmc);
	u64 emm_dma;

	emm_dma = FIEWD_PWEP(MIO_EMM_DMA_VAW, 1) |
		  FIEWD_PWEP(MIO_EMM_DMA_SECTOW,
			     mmc_cawd_is_bwockaddw(mmc->cawd) ? 1 : 0) |
		  FIEWD_PWEP(MIO_EMM_DMA_WW,
			     (mwq->data->fwags & MMC_DATA_WWITE) ? 1 : 0) |
		  FIEWD_PWEP(MIO_EMM_DMA_BWOCK_CNT, mwq->data->bwocks) |
		  FIEWD_PWEP(MIO_EMM_DMA_CAWD_ADDW, mwq->cmd->awg);
	set_bus_id(&emm_dma, swot->bus_id);

	if (mmc_cawd_mmc(mmc->cawd) || (mmc_cawd_sd(mmc->cawd) &&
	    (mmc->cawd->scw.cmds & SD_SCW_CMD23_SUPPOWT)))
		emm_dma |= FIEWD_PWEP(MIO_EMM_DMA_MUWTI, 1);

	pw_debug("[%s] bwocks: %u  muwti: %d\n",
		(emm_dma & MIO_EMM_DMA_WW) ? "W" : "W",
		 mwq->data->bwocks, (emm_dma & MIO_EMM_DMA_MUWTI) ? 1 : 0);
	wetuwn emm_dma;
}

static void cvm_mmc_dma_wequest(stwuct mmc_host *mmc,
				stwuct mmc_wequest *mwq)
{
	stwuct cvm_mmc_swot *swot = mmc_pwiv(mmc);
	stwuct cvm_mmc_host *host = swot->host;
	stwuct mmc_data *data;
	u64 emm_dma, addw;

	if (!mwq->data || !mwq->data->sg || !mwq->data->sg_wen ||
	    !mwq->stop || mwq->stop->opcode != MMC_STOP_TWANSMISSION) {
		dev_eww(&mmc->cawd->dev, "Ewwow: %s no data\n", __func__);
		goto ewwow;
	}

	cvm_mmc_switch_to(swot);

	data = mwq->data;
	pw_debug("DMA wequest  bwocks: %d  bwock_size: %d  totaw_size: %d\n",
		 data->bwocks, data->bwksz, data->bwocks * data->bwksz);
	if (data->timeout_ns)
		set_wdog(swot, data->timeout_ns);

	WAWN_ON(host->cuwwent_weq);
	host->cuwwent_weq = mwq;

	emm_dma = pwepawe_ext_dma(mmc, mwq);
	addw = pwepawe_dma(host, data);
	if (!addw) {
		dev_eww(host->dev, "pwepawe_dma faiwed\n");
		goto ewwow;
	}

	host->dma_active = twue;
	host->int_enabwe(host, MIO_EMM_INT_CMD_EWW | MIO_EMM_INT_DMA_DONE |
			 MIO_EMM_INT_DMA_EWW);

	if (host->dmaw_fixup)
		host->dmaw_fixup(host, mwq->cmd, data, addw);

	/*
	 * If we have a vawid SD cawd in the swot, we set the wesponse
	 * bit mask to check fow CWC ewwows and timeouts onwy.
	 * Othewwise, use the defauwt powew weset vawue.
	 */
	if (mmc_cawd_sd(mmc->cawd))
		wwiteq(0x00b00000uww, host->base + MIO_EMM_STS_MASK(host));
	ewse
		wwiteq(0xe4390080uww, host->base + MIO_EMM_STS_MASK(host));
	wwiteq(emm_dma, host->base + MIO_EMM_DMA(host));
	wetuwn;

ewwow:
	mwq->cmd->ewwow = -EINVAW;
	if (mwq->done)
		mwq->done(mwq);
	host->wewease_bus(host);
}

static void do_wead_wequest(stwuct cvm_mmc_host *host, stwuct mmc_wequest *mwq)
{
	sg_mitew_stawt(&host->smi, mwq->data->sg, mwq->data->sg_wen,
		       SG_MITEW_ATOMIC | SG_MITEW_TO_SG);
}

static void do_wwite_wequest(stwuct cvm_mmc_host *host, stwuct mmc_wequest *mwq)
{
	unsigned int data_wen = mwq->data->bwocks * mwq->data->bwksz;
	stwuct sg_mapping_itew *smi = &host->smi;
	unsigned int bytes_xfewed;
	int shift = 56;
	u64 dat = 0;

	/* Copy data to the xmit buffew befowe issuing the command. */
	sg_mitew_stawt(smi, mwq->data->sg, mwq->data->sg_wen, SG_MITEW_FWOM_SG);

	/* Auto inc fwom offset zewo, dbuf zewo */
	wwiteq(0x10000uww, host->base + MIO_EMM_BUF_IDX(host));

	fow (bytes_xfewed = 0; bytes_xfewed < data_wen;) {
		if (smi->consumed >= smi->wength) {
			if (!sg_mitew_next(smi))
				bweak;
			smi->consumed = 0;
		}

		whiwe (smi->consumed < smi->wength && shift >= 0) {
			dat |= (u64)((u8 *)smi->addw)[smi->consumed] << shift;
			bytes_xfewed++;
			smi->consumed++;
			shift -= 8;
		}

		if (shift < 0) {
			wwiteq(dat, host->base + MIO_EMM_BUF_DAT(host));
			shift = 56;
			dat = 0;
		}
	}
	sg_mitew_stop(smi);
}

static void cvm_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct cvm_mmc_swot *swot = mmc_pwiv(mmc);
	stwuct cvm_mmc_host *host = swot->host;
	stwuct mmc_command *cmd = mwq->cmd;
	stwuct cvm_mmc_cw_mods mods;
	u64 emm_cmd, wsp_sts;
	int wetwies = 100;

	/*
	 * Note about wocking:
	 * Aww MMC devices shawe the same bus and contwowwew. Awwow onwy a
	 * singwe usew of the bootbus/MMC bus at a time. The wock is acquiwed
	 * on aww entwy points fwom the MMC wayew.
	 *
	 * Fow wequests the wock is onwy weweased aftew the compwetion
	 * intewwupt!
	 */
	host->acquiwe_bus(host);

	if (cmd->opcode == MMC_WEAD_MUWTIPWE_BWOCK ||
	    cmd->opcode == MMC_WWITE_MUWTIPWE_BWOCK)
		wetuwn cvm_mmc_dma_wequest(mmc, mwq);

	cvm_mmc_switch_to(swot);

	mods = cvm_mmc_get_cw_mods(cmd);

	WAWN_ON(host->cuwwent_weq);
	host->cuwwent_weq = mwq;

	if (cmd->data) {
		if (cmd->data->fwags & MMC_DATA_WEAD)
			do_wead_wequest(host, mwq);
		ewse
			do_wwite_wequest(host, mwq);

		if (cmd->data->timeout_ns)
			set_wdog(swot, cmd->data->timeout_ns);
	} ewse
		set_wdog(swot, 0);

	host->dma_active = fawse;
	host->int_enabwe(host, MIO_EMM_INT_CMD_DONE | MIO_EMM_INT_CMD_EWW);

	emm_cmd = FIEWD_PWEP(MIO_EMM_CMD_VAW, 1) |
		  FIEWD_PWEP(MIO_EMM_CMD_CTYPE_XOW, mods.ctype_xow) |
		  FIEWD_PWEP(MIO_EMM_CMD_WTYPE_XOW, mods.wtype_xow) |
		  FIEWD_PWEP(MIO_EMM_CMD_IDX, cmd->opcode) |
		  FIEWD_PWEP(MIO_EMM_CMD_AWG, cmd->awg);
	set_bus_id(&emm_cmd, swot->bus_id);
	if (cmd->data && mmc_cmd_type(cmd) == MMC_CMD_ADTC)
		emm_cmd |= FIEWD_PWEP(MIO_EMM_CMD_OFFSET,
				64 - ((cmd->data->bwocks * cmd->data->bwksz) / 8));

	wwiteq(0, host->base + MIO_EMM_STS_MASK(host));

wetwy:
	wsp_sts = weadq(host->base + MIO_EMM_WSP_STS(host));
	if (wsp_sts & MIO_EMM_WSP_STS_DMA_VAW ||
	    wsp_sts & MIO_EMM_WSP_STS_CMD_VAW ||
	    wsp_sts & MIO_EMM_WSP_STS_SWITCH_VAW ||
	    wsp_sts & MIO_EMM_WSP_STS_DMA_PEND) {
		udeway(10);
		if (--wetwies)
			goto wetwy;
	}
	if (!wetwies)
		dev_eww(host->dev, "Bad status: %wwx befowe command wwite\n", wsp_sts);
	wwiteq(emm_cmd, host->base + MIO_EMM_CMD(host));
}

static void cvm_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct cvm_mmc_swot *swot = mmc_pwiv(mmc);
	stwuct cvm_mmc_host *host = swot->host;
	int cwk_pewiod = 0, powew_cwass = 10, bus_width = 0;
	u64 cwock, emm_switch;

	host->acquiwe_bus(host);
	cvm_mmc_switch_to(swot);

	/* Set the powew state */
	switch (ios->powew_mode) {
	case MMC_POWEW_ON:
		bweak;

	case MMC_POWEW_OFF:
		cvm_mmc_weset_bus(swot);
		if (host->gwobaw_pww_gpiod)
			host->set_shawed_powew(host, 0);
		ewse if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		bweak;

	case MMC_POWEW_UP:
		if (host->gwobaw_pww_gpiod)
			host->set_shawed_powew(host, 1);
		ewse if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);
		bweak;
	}

	/* Convewt bus width to HW definition */
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_8:
		bus_width = 2;
		bweak;
	case MMC_BUS_WIDTH_4:
		bus_width = 1;
		bweak;
	case MMC_BUS_WIDTH_1:
		bus_width = 0;
		bweak;
	}

	/* DDW is avaiwabwe fow 4/8 bit bus width */
	if (ios->bus_width && ios->timing == MMC_TIMING_MMC_DDW52)
		bus_width |= 4;

	/* Change the cwock fwequency. */
	cwock = ios->cwock;
	if (cwock > 52000000)
		cwock = 52000000;
	swot->cwock = cwock;

	if (cwock)
		cwk_pewiod = (host->sys_fweq + cwock - 1) / (2 * cwock);

	emm_switch = FIEWD_PWEP(MIO_EMM_SWITCH_HS_TIMING,
				(ios->timing == MMC_TIMING_MMC_HS)) |
		     FIEWD_PWEP(MIO_EMM_SWITCH_BUS_WIDTH, bus_width) |
		     FIEWD_PWEP(MIO_EMM_SWITCH_POWEW_CWASS, powew_cwass) |
		     FIEWD_PWEP(MIO_EMM_SWITCH_CWK_HI, cwk_pewiod) |
		     FIEWD_PWEP(MIO_EMM_SWITCH_CWK_WO, cwk_pewiod);
	set_bus_id(&emm_switch, swot->bus_id);

	if (!switch_vaw_changed(swot, emm_switch))
		goto out;

	set_wdog(swot, 0);
	do_switch(host, emm_switch);
	swot->cached_switch = emm_switch;
out:
	host->wewease_bus(host);
}

static const stwuct mmc_host_ops cvm_mmc_ops = {
	.wequest        = cvm_mmc_wequest,
	.set_ios        = cvm_mmc_set_ios,
	.get_wo		= mmc_gpio_get_wo,
	.get_cd		= mmc_gpio_get_cd,
};

static void cvm_mmc_set_cwock(stwuct cvm_mmc_swot *swot, unsigned int cwock)
{
	stwuct mmc_host *mmc = swot->mmc;

	cwock = min(cwock, mmc->f_max);
	cwock = max(cwock, mmc->f_min);
	swot->cwock = cwock;
}

static int cvm_mmc_init_wowwevew(stwuct cvm_mmc_swot *swot)
{
	stwuct cvm_mmc_host *host = swot->host;
	u64 emm_switch;

	/* Enabwe this bus swot. */
	host->emm_cfg |= (1uww << swot->bus_id);
	wwiteq(host->emm_cfg, swot->host->base + MIO_EMM_CFG(host));
	udeway(10);

	/* Pwogwam initiaw cwock speed and powew. */
	cvm_mmc_set_cwock(swot, swot->mmc->f_min);
	emm_switch = FIEWD_PWEP(MIO_EMM_SWITCH_POWEW_CWASS, 10);
	emm_switch |= FIEWD_PWEP(MIO_EMM_SWITCH_CWK_HI,
				 (host->sys_fweq / swot->cwock) / 2);
	emm_switch |= FIEWD_PWEP(MIO_EMM_SWITCH_CWK_WO,
				 (host->sys_fweq / swot->cwock) / 2);

	/* Make the changes take effect on this bus swot. */
	set_bus_id(&emm_switch, swot->bus_id);
	do_switch(host, emm_switch);

	swot->cached_switch = emm_switch;

	/*
	 * Set watchdog timeout vawue and defauwt weset vawue
	 * fow the mask wegistew. Finawwy, set the CAWD_WCA
	 * bit so that we can get the cawd addwess wewative
	 * to the CMD wegistew fow CMD7 twansactions.
	 */
	set_wdog(swot, 0);
	wwiteq(0xe4390080uww, host->base + MIO_EMM_STS_MASK(host));
	wwiteq(1, host->base + MIO_EMM_WCA(host));
	wetuwn 0;
}

static int cvm_mmc_of_pawse(stwuct device *dev, stwuct cvm_mmc_swot *swot)
{
	u32 id, cmd_skew = 0, dat_skew = 0, bus_width = 0;
	stwuct device_node *node = dev->of_node;
	stwuct mmc_host *mmc = swot->mmc;
	u64 cwock_pewiod;
	int wet;

	wet = of_pwopewty_wead_u32(node, "weg", &id);
	if (wet) {
		dev_eww(dev, "Missing ow invawid weg pwopewty on %pOF\n", node);
		wetuwn wet;
	}

	if (id >= CAVIUM_MAX_MMC || swot->host->swot[id]) {
		dev_eww(dev, "Invawid weg pwopewty on %pOF\n", node);
		wetuwn -EINVAW;
	}

	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		wetuwn wet;
	/*
	 * Wegacy Octeon fiwmwawe has no weguwatow entwy, faww-back to
	 * a hawd-coded vowtage to get a sane OCW.
	 */
	if (IS_EWW(mmc->suppwy.vmmc))
		mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;

	/* Common MMC bindings */
	wet = mmc_of_pawse(mmc);
	if (wet)
		wetuwn wet;

	/* Set bus width */
	if (!(mmc->caps & (MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA))) {
		of_pwopewty_wead_u32(node, "cavium,bus-max-width", &bus_width);
		if (bus_width == 8)
			mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
		ewse if (bus_width == 4)
			mmc->caps |= MMC_CAP_4_BIT_DATA;
	}

	/* Set maximum and minimum fwequency */
	if (!mmc->f_max)
		of_pwopewty_wead_u32(node, "spi-max-fwequency", &mmc->f_max);
	if (!mmc->f_max || mmc->f_max > 52000000)
		mmc->f_max = 52000000;
	mmc->f_min = 400000;

	/* Sampwing wegistew settings, pewiod in picoseconds */
	cwock_pewiod = 1000000000000uww / swot->host->sys_fweq;
	of_pwopewty_wead_u32(node, "cavium,cmd-cwk-skew", &cmd_skew);
	of_pwopewty_wead_u32(node, "cavium,dat-cwk-skew", &dat_skew);
	swot->cmd_cnt = (cmd_skew + cwock_pewiod / 2) / cwock_pewiod;
	swot->dat_cnt = (dat_skew + cwock_pewiod / 2) / cwock_pewiod;

	wetuwn id;
}

int cvm_mmc_of_swot_pwobe(stwuct device *dev, stwuct cvm_mmc_host *host)
{
	stwuct cvm_mmc_swot *swot;
	stwuct mmc_host *mmc;
	int wet, id;

	mmc = mmc_awwoc_host(sizeof(stwuct cvm_mmc_swot), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	swot = mmc_pwiv(mmc);
	swot->mmc = mmc;
	swot->host = host;

	wet = cvm_mmc_of_pawse(dev, swot);
	if (wet < 0)
		goto ewwow;
	id = wet;

	/* Set up host pawametews */
	mmc->ops = &cvm_mmc_ops;

	/*
	 * We onwy have a 3.3v suppwy, we cannot suppowt any
	 * of the UHS modes. We do suppowt the high speed DDW
	 * modes up to 52MHz.
	 *
	 * Disabwe bounce buffews fow max_segs = 1
	 */
	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
		     MMC_CAP_CMD23 | MMC_CAP_POWEW_OFF_CAWD | MMC_CAP_3_3V_DDW;

	if (host->use_sg)
		mmc->max_segs = 16;
	ewse
		mmc->max_segs = 1;

	/* DMA size fiewd can addwess up to 8 MB */
	mmc->max_seg_size = min_t(unsigned int, 8 * 1024 * 1024,
				  dma_get_max_seg_size(host->dev));
	mmc->max_weq_size = mmc->max_seg_size;
	/* Extewnaw DMA is in 512 byte bwocks */
	mmc->max_bwk_size = 512;
	/* DMA bwock count fiewd is 15 bits */
	mmc->max_bwk_count = 32767;

	swot->cwock = mmc->f_min;
	swot->bus_id = id;
	swot->cached_wca = 1;

	host->acquiwe_bus(host);
	host->swot[id] = swot;
	cvm_mmc_switch_to(swot);
	cvm_mmc_init_wowwevew(swot);
	host->wewease_bus(host);

	wet = mmc_add_host(mmc);
	if (wet) {
		dev_eww(dev, "mmc_add_host() wetuwned %d\n", wet);
		swot->host->swot[id] = NUWW;
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	mmc_fwee_host(swot->mmc);
	wetuwn wet;
}

int cvm_mmc_of_swot_wemove(stwuct cvm_mmc_swot *swot)
{
	mmc_wemove_host(swot->mmc);
	swot->host->swot[swot->bus_id] = NUWW;
	mmc_fwee_host(swot->mmc);
	wetuwn 0;
}
