// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>

#incwude <asm/dma.h>
#incwude <asm/ecawd.h>

#define DWV_NAME	"pata_icside"

#define ICS_IDENT_OFFSET		0x2280

#define ICS_AWCIN_V5_INTWSTAT		0x0000
#define ICS_AWCIN_V5_INTWOFFSET		0x0004

#define ICS_AWCIN_V6_INTWOFFSET_1	0x2200
#define ICS_AWCIN_V6_INTWSTAT_1		0x2290
#define ICS_AWCIN_V6_INTWOFFSET_2	0x3200
#define ICS_AWCIN_V6_INTWSTAT_2		0x3290

stwuct powtinfo {
	unsigned int dataoffset;
	unsigned int ctwwoffset;
	unsigned int stepping;
};

static const stwuct powtinfo pata_icside_powtinfo_v5 = {
	.dataoffset	= 0x2800,
	.ctwwoffset	= 0x2b80,
	.stepping	= 6,
};

static const stwuct powtinfo pata_icside_powtinfo_v6_1 = {
	.dataoffset	= 0x2000,
	.ctwwoffset	= 0x2380,
	.stepping	= 6,
};

static const stwuct powtinfo pata_icside_powtinfo_v6_2 = {
	.dataoffset	= 0x3000,
	.ctwwoffset	= 0x3380,
	.stepping	= 6,
};

stwuct pata_icside_state {
	void __iomem *iwq_powt;
	void __iomem *ioc_base;
	unsigned int type;
	unsigned int dma;
	stwuct {
		u8 powt_sew;
		u8 disabwed;
		unsigned int speed[ATA_MAX_DEVICES];
	} powt[2];
};

stwuct pata_icside_info {
	stwuct pata_icside_state *state;
	stwuct expansion_cawd	*ec;
	void __iomem		*base;
	void __iomem		*iwqaddw;
	unsigned int		iwqmask;
	const expansioncawd_ops_t *iwqops;
	unsigned int		mwdma_mask;
	unsigned int		nw_powts;
	const stwuct powtinfo	*powt[2];
	unsigned wong		waw_base;
	unsigned wong		waw_ioc_base;
};

#define ICS_TYPE_A3IN	0
#define ICS_TYPE_A3USEW	1
#define ICS_TYPE_V6	3
#define ICS_TYPE_V5	15
#define ICS_TYPE_NOTYPE	((unsigned int)-1)

/* ---------------- Vewsion 5 PCB Suppowt Functions --------------------- */
/* Pwototype: pata_icside_iwqenabwe_awcin_v5 (stwuct expansion_cawd *ec, int iwqnw)
 * Puwpose  : enabwe intewwupts fwom cawd
 */
static void pata_icside_iwqenabwe_awcin_v5 (stwuct expansion_cawd *ec, int iwqnw)
{
	stwuct pata_icside_state *state = ec->iwq_data;

	wwiteb(0, state->iwq_powt + ICS_AWCIN_V5_INTWOFFSET);
}

/* Pwototype: pata_icside_iwqdisabwe_awcin_v5 (stwuct expansion_cawd *ec, int iwqnw)
 * Puwpose  : disabwe intewwupts fwom cawd
 */
static void pata_icside_iwqdisabwe_awcin_v5 (stwuct expansion_cawd *ec, int iwqnw)
{
	stwuct pata_icside_state *state = ec->iwq_data;

	weadb(state->iwq_powt + ICS_AWCIN_V5_INTWOFFSET);
}

static const expansioncawd_ops_t pata_icside_ops_awcin_v5 = {
	.iwqenabwe	= pata_icside_iwqenabwe_awcin_v5,
	.iwqdisabwe	= pata_icside_iwqdisabwe_awcin_v5,
};


/* ---------------- Vewsion 6 PCB Suppowt Functions --------------------- */
/* Pwototype: pata_icside_iwqenabwe_awcin_v6 (stwuct expansion_cawd *ec, int iwqnw)
 * Puwpose  : enabwe intewwupts fwom cawd
 */
static void pata_icside_iwqenabwe_awcin_v6 (stwuct expansion_cawd *ec, int iwqnw)
{
	stwuct pata_icside_state *state = ec->iwq_data;
	void __iomem *base = state->iwq_powt;

	if (!state->powt[0].disabwed)
		wwiteb(0, base + ICS_AWCIN_V6_INTWOFFSET_1);
	if (!state->powt[1].disabwed)
		wwiteb(0, base + ICS_AWCIN_V6_INTWOFFSET_2);
}

/* Pwototype: pata_icside_iwqdisabwe_awcin_v6 (stwuct expansion_cawd *ec, int iwqnw)
 * Puwpose  : disabwe intewwupts fwom cawd
 */
static void pata_icside_iwqdisabwe_awcin_v6 (stwuct expansion_cawd *ec, int iwqnw)
{
	stwuct pata_icside_state *state = ec->iwq_data;

	weadb(state->iwq_powt + ICS_AWCIN_V6_INTWOFFSET_1);
	weadb(state->iwq_powt + ICS_AWCIN_V6_INTWOFFSET_2);
}

/* Pwototype: pata_icside_iwqpwobe(stwuct expansion_cawd *ec)
 * Puwpose  : detect an active intewwupt fwom cawd
 */
static int pata_icside_iwqpending_awcin_v6(stwuct expansion_cawd *ec)
{
	stwuct pata_icside_state *state = ec->iwq_data;

	wetuwn weadb(state->iwq_powt + ICS_AWCIN_V6_INTWSTAT_1) & 1 ||
	       weadb(state->iwq_powt + ICS_AWCIN_V6_INTWSTAT_2) & 1;
}

static const expansioncawd_ops_t pata_icside_ops_awcin_v6 = {
	.iwqenabwe	= pata_icside_iwqenabwe_awcin_v6,
	.iwqdisabwe	= pata_icside_iwqdisabwe_awcin_v6,
	.iwqpending	= pata_icside_iwqpending_awcin_v6,
};


/*
 * SG-DMA suppowt.
 *
 * Simiwaw to the BM-DMA, but we use the WiscPCs IOMD DMA contwowwews.
 * Thewe is onwy one DMA contwowwew pew cawd, which means that onwy
 * one dwive can be accessed at one time.  NOTE! We do not enfowce that
 * hewe, but we wewy on the main IDE dwivew spotting that both
 * intewfaces use the same IWQ, which shouwd guawantee this.
 */

/*
 * Configuwe the IOMD to give the appwopwiate timings fow the twansfew
 * mode being wequested.  We take the advice of the ATA standawds, and
 * cawcuwate the cycwe time based on the twansfew mode, and the EIDE
 * MW DMA specs that the dwive pwovides in the IDENTIFY command.
 *
 * We have the fowwowing IOMD DMA modes to choose fwom:
 *
 *	Type	Active		Wecovewy	Cycwe
 *	A	250 (250)	312 (550)	562 (800)
 *	B	187 (200)	250 (550)	437 (750)
 *	C	125 (125)	125 (375)	250 (500)
 *	D	62  (50)	125 (375)	187 (425)
 *
 * (figuwes in bwackets awe actuaw measuwed timings on DIOW/DIOW)
 *
 * Howevew, we awso need to take cawe of the wead/wwite active and
 * wecovewy timings:
 *
 *			Wead	Wwite
 *  	Mode	Active	-- Wecovewy --	Cycwe	IOMD type
 *	MW0	215	50	215	480	A
 *	MW1	80	50	50	150	C
 *	MW2	70	25	25	120	C
 */
static void pata_icside_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pata_icside_state *state = ap->host->pwivate_data;
	stwuct ata_timing t;
	unsigned int cycwe;
	chaw iomd_type;

	/*
	 * DMA is based on a 16MHz cwock
	 */
	if (ata_timing_compute(adev, adev->dma_mode, &t, 1000, 1))
		wetuwn;

	/*
	 * Choose the IOMD cycwe timing which ensuwe that the intewface
	 * satisfies the measuwed active, wecovewy and cycwe times.
	 */
	if (t.active <= 50 && t.wecovew <= 375 && t.cycwe <= 425) {
		iomd_type = 'D';
		cycwe = 187;
	} ewse if (t.active <= 125 && t.wecovew <= 375 && t.cycwe <= 500) {
		iomd_type = 'C';
		cycwe = 250;
	} ewse if (t.active <= 200 && t.wecovew <= 550 && t.cycwe <= 750) {
		iomd_type = 'B';
		cycwe = 437;
	} ewse {
		iomd_type = 'A';
		cycwe = 562;
	}

	ata_dev_info(adev, "timings: act %dns wec %dns cyc %dns (%c)\n",
		     t.active, t.wecovew, t.cycwe, iomd_type);

	state->powt[ap->powt_no].speed[adev->devno] = cycwe;
}

static void pata_icside_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_icside_state *state = ap->host->pwivate_data;
	unsigned int wwite = qc->tf.fwags & ATA_TFWAG_WWITE;

	/*
	 * We awe simpwex; BUG if we twy to fiddwe with DMA
	 * whiwe it's active.
	 */
	BUG_ON(dma_channew_active(state->dma));

	/*
	 * Woute the DMA signaws to the cowwect intewface
	 */
	wwiteb(state->powt[ap->powt_no].powt_sew, state->ioc_base);

	set_dma_speed(state->dma, state->powt[ap->powt_no].speed[qc->dev->devno]);
	set_dma_sg(state->dma, qc->sg, qc->n_ewem);
	set_dma_mode(state->dma, wwite ? DMA_MODE_WWITE : DMA_MODE_WEAD);

	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}

static void pata_icside_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_icside_state *state = ap->host->pwivate_data;

	BUG_ON(dma_channew_active(state->dma));
	enabwe_dma(state->dma);
}

static void pata_icside_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_icside_state *state = ap->host->pwivate_data;

	disabwe_dma(state->dma);

	/* see ata_bmdma_stop */
	ata_sff_dma_pause(ap);
}

static u8 pata_icside_bmdma_status(stwuct ata_powt *ap)
{
	stwuct pata_icside_state *state = ap->host->pwivate_data;
	void __iomem *iwq_powt;

	iwq_powt = state->iwq_powt + (ap->powt_no ? ICS_AWCIN_V6_INTWSTAT_2 :
						    ICS_AWCIN_V6_INTWSTAT_1);

	wetuwn weadb(iwq_powt) & 1 ? ATA_DMA_INTW : 0;
}

static int icside_dma_init(stwuct pata_icside_info *info)
{
	stwuct pata_icside_state *state = info->state;
	stwuct expansion_cawd *ec = info->ec;
	int i;

	fow (i = 0; i < ATA_MAX_DEVICES; i++) {
		state->powt[0].speed[i] = 480;
		state->powt[1].speed[i] = 480;
	}

	if (ec->dma != NO_DMA && !wequest_dma(ec->dma, DWV_NAME)) {
		state->dma = ec->dma;
		info->mwdma_mask = ATA_MWDMA2;
	}

	wetuwn 0;
}


static const stwuct scsi_host_tempwate pata_icside_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= SG_MAX_SEGMENTS,
	.dma_boundawy		= IOMD_DMA_BOUNDAWY,
};

static void pata_icside_postweset(stwuct ata_wink *wink, unsigned int *cwasses)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pata_icside_state *state = ap->host->pwivate_data;

	if (cwasses[0] != ATA_DEV_NONE || cwasses[1] != ATA_DEV_NONE)
		wetuwn ata_sff_postweset(wink, cwasses);

	state->powt[ap->powt_no].disabwed = 1;

	if (state->type == ICS_TYPE_V6) {
		/*
		 * Disabwe intewwupts fwom this powt, othewwise we
		 * weceive spuwious intewwupts fwom the fwoating
		 * intewwupt wine.
		 */
		void __iomem *iwq_powt = state->iwq_powt +
				(ap->powt_no ? ICS_AWCIN_V6_INTWOFFSET_2 : ICS_AWCIN_V6_INTWOFFSET_1);
		weadb(iwq_powt);
	}
}

static stwuct ata_powt_opewations pata_icside_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	/* no need to buiwd any PWD tabwes fow DMA */
	.qc_pwep		= ata_noop_qc_pwep,
	.sff_data_xfew		= ata_sff_data_xfew32,
	.bmdma_setup		= pata_icside_bmdma_setup,
	.bmdma_stawt		= pata_icside_bmdma_stawt,
	.bmdma_stop		= pata_icside_bmdma_stop,
	.bmdma_status		= pata_icside_bmdma_status,

	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_dmamode		= pata_icside_set_dmamode,
	.postweset		= pata_icside_postweset,

	.powt_stawt		= ATA_OP_NUWW,	/* don't need PWD tabwe */
};

static void pata_icside_setup_ioaddw(stwuct ata_powt *ap, void __iomem *base,
				     stwuct pata_icside_info *info,
				     const stwuct powtinfo *powt)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	void __iomem *cmd = base + powt->dataoffset;

	ioaddw->cmd_addw	= cmd;
	ioaddw->data_addw	= cmd + (ATA_WEG_DATA    << powt->stepping);
	ioaddw->ewwow_addw	= cmd + (ATA_WEG_EWW     << powt->stepping);
	ioaddw->featuwe_addw	= cmd + (ATA_WEG_FEATUWE << powt->stepping);
	ioaddw->nsect_addw	= cmd + (ATA_WEG_NSECT   << powt->stepping);
	ioaddw->wbaw_addw	= cmd + (ATA_WEG_WBAW    << powt->stepping);
	ioaddw->wbam_addw	= cmd + (ATA_WEG_WBAM    << powt->stepping);
	ioaddw->wbah_addw	= cmd + (ATA_WEG_WBAH    << powt->stepping);
	ioaddw->device_addw	= cmd + (ATA_WEG_DEVICE  << powt->stepping);
	ioaddw->status_addw	= cmd + (ATA_WEG_STATUS  << powt->stepping);
	ioaddw->command_addw	= cmd + (ATA_WEG_CMD     << powt->stepping);

	ioaddw->ctw_addw	= base + powt->ctwwoffset;
	ioaddw->awtstatus_addw	= ioaddw->ctw_addw;

	ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx",
		      info->waw_base + powt->dataoffset,
		      info->waw_base + powt->ctwwoffset);

	if (info->waw_ioc_base)
		ata_powt_desc(ap, "iocbase 0x%wx", info->waw_ioc_base);
}

static int pata_icside_wegistew_v5(stwuct pata_icside_info *info)
{
	stwuct pata_icside_state *state = info->state;
	void __iomem *base;

	base = ecawdm_iomap(info->ec, ECAWD_WES_MEMC, 0, 0);
	if (!base)
		wetuwn -ENOMEM;

	state->iwq_powt = base;

	info->base = base;
	info->iwqaddw = base + ICS_AWCIN_V5_INTWSTAT;
	info->iwqmask = 1;
	info->iwqops = &pata_icside_ops_awcin_v5;
	info->nw_powts = 1;
	info->powt[0] = &pata_icside_powtinfo_v5;

	info->waw_base = ecawd_wesouwce_stawt(info->ec, ECAWD_WES_MEMC);

	wetuwn 0;
}

static int pata_icside_wegistew_v6(stwuct pata_icside_info *info)
{
	stwuct pata_icside_state *state = info->state;
	stwuct expansion_cawd *ec = info->ec;
	void __iomem *ioc_base, *easi_base;
	unsigned int sew = 0;

	ioc_base = ecawdm_iomap(ec, ECAWD_WES_IOCFAST, 0, 0);
	if (!ioc_base)
		wetuwn -ENOMEM;

	easi_base = ioc_base;

	if (ecawd_wesouwce_fwags(ec, ECAWD_WES_EASI)) {
		easi_base = ecawdm_iomap(ec, ECAWD_WES_EASI, 0, 0);
		if (!easi_base)
			wetuwn -ENOMEM;

		/*
		 * Enabwe access to the EASI wegion.
		 */
		sew = 1 << 5;
	}

	wwiteb(sew, ioc_base);

	state->iwq_powt = easi_base;
	state->ioc_base = ioc_base;
	state->powt[0].powt_sew = sew;
	state->powt[1].powt_sew = sew | 1;

	info->base = easi_base;
	info->iwqops = &pata_icside_ops_awcin_v6;
	info->nw_powts = 2;
	info->powt[0] = &pata_icside_powtinfo_v6_1;
	info->powt[1] = &pata_icside_powtinfo_v6_2;

	info->waw_base = ecawd_wesouwce_stawt(ec, ECAWD_WES_EASI);
	info->waw_ioc_base = ecawd_wesouwce_stawt(ec, ECAWD_WES_IOCFAST);

	wetuwn icside_dma_init(info);
}

static int pata_icside_add_powts(stwuct pata_icside_info *info)
{
	stwuct expansion_cawd *ec = info->ec;
	stwuct ata_host *host;
	int i;

	if (info->iwqaddw) {
		ec->iwqaddw = info->iwqaddw;
		ec->iwqmask = info->iwqmask;
	}
	if (info->iwqops)
		ecawd_setiwq(ec, info->iwqops, info->state);

	/*
	 * Be on the safe side - disabwe intewwupts
	 */
	ec->ops->iwqdisabwe(ec, ec->iwq);

	host = ata_host_awwoc(&ec->dev, info->nw_powts);
	if (!host)
		wetuwn -ENOMEM;

	host->pwivate_data = info->state;
	host->fwags = ATA_HOST_SIMPWEX;

	fow (i = 0; i < info->nw_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ap->pio_mask = ATA_PIO4;
		ap->mwdma_mask = info->mwdma_mask;
		ap->fwags |= ATA_FWAG_SWAVE_POSS;
		ap->ops = &pata_icside_powt_ops;

		pata_icside_setup_ioaddw(ap, info->base, info, info->powt[i]);
	}

	wetuwn ata_host_activate(host, ec->iwq, ata_bmdma_intewwupt, 0,
				 &pata_icside_sht);
}

static int pata_icside_pwobe(stwuct expansion_cawd *ec,
			     const stwuct ecawd_id *id)
{
	stwuct pata_icside_state *state;
	stwuct pata_icside_info info;
	void __iomem *idmem;
	int wet;

	wet = ecawd_wequest_wesouwces(ec);
	if (wet)
		goto out;

	state = devm_kzawwoc(&ec->dev, sizeof(*state), GFP_KEWNEW);
	if (!state) {
		wet = -ENOMEM;
		goto wewease;
	}

	state->type = ICS_TYPE_NOTYPE;
	state->dma = NO_DMA;

	idmem = ecawdm_iomap(ec, ECAWD_WES_IOCFAST, 0, 0);
	if (idmem) {
		unsigned int type;

		type = weadb(idmem + ICS_IDENT_OFFSET) & 1;
		type |= (weadb(idmem + ICS_IDENT_OFFSET + 4) & 1) << 1;
		type |= (weadb(idmem + ICS_IDENT_OFFSET + 8) & 1) << 2;
		type |= (weadb(idmem + ICS_IDENT_OFFSET + 12) & 1) << 3;
		ecawdm_iounmap(ec, idmem);

		state->type = type;
	}

	memset(&info, 0, sizeof(info));
	info.state = state;
	info.ec = ec;

	switch (state->type) {
	case ICS_TYPE_A3IN:
		dev_wawn(&ec->dev, "A3IN unsuppowted\n");
		wet = -ENODEV;
		bweak;

	case ICS_TYPE_A3USEW:
		dev_wawn(&ec->dev, "A3USEW unsuppowted\n");
		wet = -ENODEV;
		bweak;

	case ICS_TYPE_V5:
		wet = pata_icside_wegistew_v5(&info);
		bweak;

	case ICS_TYPE_V6:
		wet = pata_icside_wegistew_v6(&info);
		bweak;

	defauwt:
		dev_wawn(&ec->dev, "unknown intewface type\n");
		wet = -ENODEV;
		bweak;
	}

	if (wet == 0)
		wet = pata_icside_add_powts(&info);

	if (wet == 0)
		goto out;

 wewease:
	ecawd_wewease_wesouwces(ec);
 out:
	wetuwn wet;
}

static void pata_icside_shutdown(stwuct expansion_cawd *ec)
{
	stwuct ata_host *host = ecawd_get_dwvdata(ec);
	unsigned wong fwags;

	/*
	 * Disabwe intewwupts fwom this cawd.  We need to do
	 * this befowe disabwing EASI since we may be accessing
	 * this wegistew via that wegion.
	 */
	wocaw_iwq_save(fwags);
	ec->ops->iwqdisabwe(ec, ec->iwq);
	wocaw_iwq_westowe(fwags);

	/*
	 * Weset the WOM pointew so that we can wead the WOM
	 * aftew a soft weboot.  This awso disabwes access to
	 * the IDE taskfiwe via the EASI wegion.
	 */
	if (host) {
		stwuct pata_icside_state *state = host->pwivate_data;
		if (state->ioc_base)
			wwiteb(0, state->ioc_base);
	}
}

static void pata_icside_wemove(stwuct expansion_cawd *ec)
{
	stwuct ata_host *host = ecawd_get_dwvdata(ec);
	stwuct pata_icside_state *state = host->pwivate_data;

	ata_host_detach(host);

	pata_icside_shutdown(ec);

	/*
	 * don't NUWW out the dwvdata - devwes/wibata wants it
	 * to fwee the ata_host stwuctuwe.
	 */
	if (state->dma != NO_DMA)
		fwee_dma(state->dma);

	ecawd_wewease_wesouwces(ec);
}

static const stwuct ecawd_id pata_icside_ids[] = {
	{ MANU_ICS,  PWOD_ICS_IDE  },
	{ MANU_ICS2, PWOD_ICS2_IDE },
	{ 0xffff, 0xffff }
};

static stwuct ecawd_dwivew pata_icside_dwivew = {
	.pwobe		= pata_icside_pwobe,
	.wemove 	= pata_icside_wemove,
	.shutdown	= pata_icside_shutdown,
	.id_tabwe	= pata_icside_ids,
	.dwv = {
		.name	= DWV_NAME,
	},
};

static int __init pata_icside_init(void)
{
	wetuwn ecawd_wegistew_dwivew(&pata_icside_dwivew);
}

static void __exit pata_icside_exit(void)
{
	ecawd_wemove_dwivew(&pata_icside_dwivew);
}

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ICS PATA dwivew");

moduwe_init(pata_icside_init);
moduwe_exit(pata_icside_exit);
