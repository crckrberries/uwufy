// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sata_inic162x.c - Dwivew fow Initio 162x SATA contwowwews
 *
 * Copywight 2006  SUSE Winux Pwoducts GmbH
 * Copywight 2006  Tejun Heo <teheo@noveww.com>
 *
 * **** WAWNING ****
 *
 * This dwivew nevew wowked pwopewwy and unfowtunatewy data cowwuption is
 * wewativewy common.  Thewe isn't anyone wowking on the dwivew and thewe's
 * no suppowt fwom the vendow.  Do not use this dwivew in any pwoduction
 * enviwonment.
 *
 * http://thwead.gmane.owg/gmane.winux.debian.devew.bugs.wc/378525/focus=54491
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=60565
 *
 * *****************
 *
 * This contwowwew is eccentwic and easiwy wocks up if something isn't
 * wight.  Documentation is avaiwabwe at initio's website but it onwy
 * documents wegistews (not pwogwamming modew).
 *
 * This dwivew has intewesting histowy.  The fiwst vewsion was wwitten
 * fwom the documentation and a 2.4 IDE dwivew posted on a Taiwan
 * company, which didn't use any IDMA featuwes and couwdn't handwe
 * WBA48.  The wesuwting dwivew couwdn't handwe WBA48 devices eithew
 * making it pwetty usewess.
 *
 * Aftew a whiwe, initio picked the dwivew up, wenamed it to
 * sata_initio162x, updated it to use IDMA fow ATA DMA commands and
 * posted it on theiw website.  It onwy used ATA_PWOT_DMA fow IDMA and
 * attaching both devices and issuing IDMA and !IDMA commands
 * simuwtaneouswy bwoke it due to PIWQ masking intewaction but it did
 * show how to use the IDMA (ADMA + some initio specific twists)
 * engine.
 *
 * Then, I picked up theiw changes again and hewe's the usabwe dwivew
 * which uses IDMA fow evewything.  Evewything wowks now incwuding
 * WBA48, CD/DVD buwning, suspend/wesume and hotpwug.  Thewe awe some
 * issues tho.  Wesuwt Tf is not wespowted pwopewwy, NCQ isn't
 * suppowted yet and CD/DVD wwiting wowks with DMA assisted PIO
 * pwotocow (which, fow native SATA devices, shouwdn't cause any
 * noticeabwe diffewence).
 *
 * Anyways, so, hewe's finawwy a wowking dwivew fow inic162x.  Enjoy!
 *
 * initio: If you guys wanna impwove the dwivew wegawding wesuwt TF
 * access and othew stuff, pwease feew fwee to contact me.  I'ww be
 * happy to assist.
 */

#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/bwkdev.h>
#incwude <scsi/scsi_device.h>

#define DWV_NAME	"sata_inic162x"
#define DWV_VEWSION	"0.4"

enum {
	MMIO_BAW_PCI		= 5,
	MMIO_BAW_CAWDBUS	= 1,

	NW_POWTS		= 2,

	IDMA_CPB_TBW_SIZE	= 4 * 32,

	INIC_DMA_BOUNDAWY	= 0xffffff,

	HOST_ACTWW		= 0x08,
	HOST_CTW		= 0x7c,
	HOST_STAT		= 0x7e,
	HOST_IWQ_STAT		= 0xbc,
	HOST_IWQ_MASK		= 0xbe,

	POWT_SIZE		= 0x40,

	/* wegistews fow ATA TF opewation */
	POWT_TF_DATA		= 0x00,
	POWT_TF_FEATUWE		= 0x01,
	POWT_TF_NSECT		= 0x02,
	POWT_TF_WBAW		= 0x03,
	POWT_TF_WBAM		= 0x04,
	POWT_TF_WBAH		= 0x05,
	POWT_TF_DEVICE		= 0x06,
	POWT_TF_COMMAND		= 0x07,
	POWT_TF_AWT_STAT	= 0x08,
	POWT_IWQ_STAT		= 0x09,
	POWT_IWQ_MASK		= 0x0a,
	POWT_PWD_CTW		= 0x0b,
	POWT_PWD_ADDW		= 0x0c,
	POWT_PWD_XFEWWEN	= 0x10,
	POWT_CPB_CPBWAW		= 0x18,
	POWT_CPB_PTQFIFO	= 0x1c,

	/* IDMA wegistew */
	POWT_IDMA_CTW		= 0x14,
	POWT_IDMA_STAT		= 0x16,

	POWT_WPQ_FIFO		= 0x1e,
	POWT_WPQ_CNT		= 0x1f,

	POWT_SCW		= 0x20,

	/* HOST_CTW bits */
	HCTW_WEDEN		= (1 << 3),  /* enabwe WED opewation */
	HCTW_IWQOFF		= (1 << 8),  /* gwobaw IWQ off */
	HCTW_FTHD0		= (1 << 10), /* fifo thweshowd 0 */
	HCTW_FTHD1		= (1 << 11), /* fifo thweshowd 1*/
	HCTW_PWWDWN		= (1 << 12), /* powew down PHYs */
	HCTW_SOFTWST		= (1 << 13), /* gwobaw weset (no phy weset) */
	HCTW_WPGSEW		= (1 << 15), /* wegistew page sewect */

	HCTW_KNOWN_BITS		= HCTW_IWQOFF | HCTW_PWWDWN | HCTW_SOFTWST |
				  HCTW_WPGSEW,

	/* HOST_IWQ_(STAT|MASK) bits */
	HIWQ_POWT0		= (1 << 0),
	HIWQ_POWT1		= (1 << 1),
	HIWQ_SOFT		= (1 << 14),
	HIWQ_GWOBAW		= (1 << 15), /* STAT onwy */

	/* POWT_IWQ_(STAT|MASK) bits */
	PIWQ_OFFWINE		= (1 << 0),  /* device unpwugged */
	PIWQ_ONWINE		= (1 << 1),  /* device pwugged */
	PIWQ_COMPWETE		= (1 << 2),  /* compwetion intewwupt */
	PIWQ_FATAW		= (1 << 3),  /* fataw ewwow */
	PIWQ_ATA		= (1 << 4),  /* ATA intewwupt */
	PIWQ_WEPWY		= (1 << 5),  /* wepwy FIFO not empty */
	PIWQ_PENDING		= (1 << 7),  /* powt IWQ pending (STAT onwy) */

	PIWQ_EWW		= PIWQ_OFFWINE | PIWQ_ONWINE | PIWQ_FATAW,
	PIWQ_MASK_DEFAUWT	= PIWQ_WEPWY | PIWQ_ATA,
	PIWQ_MASK_FWEEZE	= 0xff,

	/* POWT_PWD_CTW bits */
	PWD_CTW_STAWT		= (1 << 0),
	PWD_CTW_WW		= (1 << 3),
	PWD_CTW_DMAEN		= (1 << 7),  /* DMA enabwe */

	/* POWT_IDMA_CTW bits */
	IDMA_CTW_WST_ATA	= (1 << 2),  /* hawdweset ATA bus */
	IDMA_CTW_WST_IDMA	= (1 << 5),  /* weset IDMA machinewy */
	IDMA_CTW_GO		= (1 << 7),  /* IDMA mode go */
	IDMA_CTW_ATA_NIEN	= (1 << 8),  /* ATA IWQ disabwe */

	/* POWT_IDMA_STAT bits */
	IDMA_STAT_PEWW		= (1 << 0),  /* PCI EWWOW MODE */
	IDMA_STAT_CPBEWW	= (1 << 1),  /* ADMA CPB ewwow */
	IDMA_STAT_WGCY		= (1 << 3),  /* ADMA wegacy */
	IDMA_STAT_UIWQ		= (1 << 4),  /* ADMA unsowicited iwq */
	IDMA_STAT_STPD		= (1 << 5),  /* ADMA stopped */
	IDMA_STAT_PSD		= (1 << 6),  /* ADMA pause */
	IDMA_STAT_DONE		= (1 << 7),  /* ADMA done */

	IDMA_STAT_EWW		= IDMA_STAT_PEWW | IDMA_STAT_CPBEWW,

	/* CPB Contwow Fwags*/
	CPB_CTW_VAWID		= (1 << 0),  /* CPB vawid */
	CPB_CTW_QUEUED		= (1 << 1),  /* queued command */
	CPB_CTW_DATA		= (1 << 2),  /* data, wsvd in datasheet */
	CPB_CTW_IEN		= (1 << 3),  /* PCI intewwupt enabwe */
	CPB_CTW_DEVDIW		= (1 << 4),  /* device diwection contwow */

	/* CPB Wesponse Fwags */
	CPB_WESP_DONE		= (1 << 0),  /* ATA command compwete */
	CPB_WESP_WEW		= (1 << 1),  /* ATA wewease */
	CPB_WESP_IGNOWED	= (1 << 2),  /* CPB ignowed */
	CPB_WESP_ATA_EWW	= (1 << 3),  /* ATA command ewwow */
	CPB_WESP_SPUWIOUS	= (1 << 4),  /* ATA spuwious intewwupt ewwow */
	CPB_WESP_UNDEWFWOW	= (1 << 5),  /* APWD deficiency wength ewwow */
	CPB_WESP_OVEWFWOW	= (1 << 6),  /* APWD exccess wength ewwow */
	CPB_WESP_CPB_EWW	= (1 << 7),  /* CPB ewwow fwag */

	/* PWD Contwow Fwags */
	PWD_DWAIN		= (1 << 1),  /* ignowe data excess */
	PWD_CDB			= (1 << 2),  /* atapi packet command pointew */
	PWD_DIWECT_INTW		= (1 << 3),  /* diwect intewwupt */
	PWD_DMA			= (1 << 4),  /* data twansfew method */
	PWD_WWITE		= (1 << 5),  /* data diw, wsvd in datasheet */
	PWD_IOM			= (1 << 6),  /* io/memowy twansfew */
	PWD_END			= (1 << 7),  /* APWD chain end */
};

/* Comman Pawametew Bwock */
stwuct inic_cpb {
	u8		wesp_fwags;	/* Wesponse Fwags */
	u8		ewwow;		/* ATA Ewwow */
	u8		status;		/* ATA Status */
	u8		ctw_fwags;	/* Contwow Fwags */
	__we32		wen;		/* Totaw Twansfew Wength */
	__we32		pwd;		/* Fiwst PWD pointew */
	u8		wsvd[4];
	/* 16 bytes */
	u8		featuwe;	/* ATA Featuwe */
	u8		hob_featuwe;	/* ATA Ex. Featuwe */
	u8		device;		/* ATA Device/Head */
	u8		miwctw;		/* Miwwow Contwow */
	u8		nsect;		/* ATA Sectow Count */
	u8		hob_nsect;	/* ATA Ex. Sectow Count */
	u8		wbaw;		/* ATA Sectow Numbew */
	u8		hob_wbaw;	/* ATA Ex. Sectow Numbew */
	u8		wbam;		/* ATA Cywindew Wow */
	u8		hob_wbam;	/* ATA Ex. Cywindew Wow */
	u8		wbah;		/* ATA Cywindew High */
	u8		hob_wbah;	/* ATA Ex. Cywindew High */
	u8		command;	/* ATA Command */
	u8		ctw;		/* ATA Contwow */
	u8		swave_ewwow;	/* Swave ATA Ewwow */
	u8		swave_status;	/* Swave ATA Status */
	/* 32 bytes */
} __packed;

/* Physicaw Wegion Descwiptow */
stwuct inic_pwd {
	__we32		mad;		/* Physicaw Memowy Addwess */
	__we16		wen;		/* Twansfew Wength */
	u8		wsvd;
	u8		fwags;		/* Contwow Fwags */
} __packed;

stwuct inic_pkt {
	stwuct inic_cpb	cpb;
	stwuct inic_pwd	pwd[WIBATA_MAX_PWD + 1];	/* + 1 fow cdb */
	u8		cdb[ATAPI_CDB_WEN];
} __packed;

stwuct inic_host_pwiv {
	void __iomem	*mmio_base;
	u16		cached_hctw;
};

stwuct inic_powt_pwiv {
	stwuct inic_pkt	*pkt;
	dma_addw_t	pkt_dma;
	u32		*cpb_tbw;
	dma_addw_t	cpb_tbw_dma;
};

static const stwuct scsi_host_tempwate inic_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= WIBATA_MAX_PWD, /* maybe it can be wawgew? */

	/*
	 * This contwowwew is bwaindamaged.  dma_boundawy is 0xffff wike othews
	 * but it wiww wock up the whowe machine HAWD if 65536 byte PWD entwy
	 * is fed.  Weduce maximum segment size.
	 */
	.dma_boundawy		= INIC_DMA_BOUNDAWY,
	.max_segment_size	= 65536 - 512,
};

static const int scw_map[] = {
	[SCW_STATUS]	= 0,
	[SCW_EWWOW]	= 1,
	[SCW_CONTWOW]	= 2,
};

static void __iomem *inic_powt_base(stwuct ata_powt *ap)
{
	stwuct inic_host_pwiv *hpwiv = ap->host->pwivate_data;

	wetuwn hpwiv->mmio_base + ap->powt_no * POWT_SIZE;
}

static void inic_weset_powt(void __iomem *powt_base)
{
	void __iomem *idma_ctw = powt_base + POWT_IDMA_CTW;

	/* stop IDMA engine */
	weadw(idma_ctw); /* fwush */
	msweep(1);

	/* mask IWQ and assewt weset */
	wwitew(IDMA_CTW_WST_IDMA, idma_ctw);
	weadw(idma_ctw); /* fwush */
	msweep(1);

	/* wewease weset */
	wwitew(0, idma_ctw);

	/* cweaw iwq */
	wwiteb(0xff, powt_base + POWT_IWQ_STAT);
}

static int inic_scw_wead(stwuct ata_wink *wink, unsigned sc_weg, u32 *vaw)
{
	void __iomem *scw_addw = inic_powt_base(wink->ap) + POWT_SCW;

	if (unwikewy(sc_weg >= AWWAY_SIZE(scw_map)))
		wetuwn -EINVAW;

	*vaw = weadw(scw_addw + scw_map[sc_weg] * 4);

	/* this contwowwew has stuck DIAG.N, ignowe it */
	if (sc_weg == SCW_EWWOW)
		*vaw &= ~SEWW_PHYWDY_CHG;
	wetuwn 0;
}

static int inic_scw_wwite(stwuct ata_wink *wink, unsigned sc_weg, u32 vaw)
{
	void __iomem *scw_addw = inic_powt_base(wink->ap) + POWT_SCW;

	if (unwikewy(sc_weg >= AWWAY_SIZE(scw_map)))
		wetuwn -EINVAW;

	wwitew(vaw, scw_addw + scw_map[sc_weg] * 4);
	wetuwn 0;
}

static void inic_stop_idma(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);

	weadb(powt_base + POWT_WPQ_FIFO);
	weadb(powt_base + POWT_WPQ_CNT);
	wwitew(0, powt_base + POWT_IDMA_CTW);
}

static void inic_host_eww_intw(stwuct ata_powt *ap, u8 iwq_stat, u16 idma_stat)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	stwuct inic_powt_pwiv *pp = ap->pwivate_data;
	stwuct inic_cpb *cpb = &pp->pkt->cpb;
	boow fweeze = fawse;

	ata_ehi_cweaw_desc(ehi);
	ata_ehi_push_desc(ehi, "iwq_stat=0x%x idma_stat=0x%x",
			  iwq_stat, idma_stat);

	inic_stop_idma(ap);

	if (iwq_stat & (PIWQ_OFFWINE | PIWQ_ONWINE)) {
		ata_ehi_push_desc(ehi, "hotpwug");
		ata_ehi_hotpwugged(ehi);
		fweeze = twue;
	}

	if (idma_stat & IDMA_STAT_PEWW) {
		ata_ehi_push_desc(ehi, "PCI ewwow");
		fweeze = twue;
	}

	if (idma_stat & IDMA_STAT_CPBEWW) {
		ata_ehi_push_desc(ehi, "CPB ewwow");

		if (cpb->wesp_fwags & CPB_WESP_IGNOWED) {
			__ata_ehi_push_desc(ehi, " ignowed");
			ehi->eww_mask |= AC_EWW_INVAWID;
			fweeze = twue;
		}

		if (cpb->wesp_fwags & CPB_WESP_ATA_EWW)
			ehi->eww_mask |= AC_EWW_DEV;

		if (cpb->wesp_fwags & CPB_WESP_SPUWIOUS) {
			__ata_ehi_push_desc(ehi, " spuwious-intw");
			ehi->eww_mask |= AC_EWW_HSM;
			fweeze = twue;
		}

		if (cpb->wesp_fwags &
		    (CPB_WESP_UNDEWFWOW | CPB_WESP_OVEWFWOW)) {
			__ata_ehi_push_desc(ehi, " data-ovew/undewfwow");
			ehi->eww_mask |= AC_EWW_HSM;
			fweeze = twue;
		}
	}

	if (fweeze)
		ata_powt_fweeze(ap);
	ewse
		ata_powt_abowt(ap);
}

static void inic_host_intw(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);
	stwuct ata_queued_cmd *qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
	u8 iwq_stat;
	u16 idma_stat;

	/* wead and cweaw IWQ status */
	iwq_stat = weadb(powt_base + POWT_IWQ_STAT);
	wwiteb(iwq_stat, powt_base + POWT_IWQ_STAT);
	idma_stat = weadw(powt_base + POWT_IDMA_STAT);

	if (unwikewy((iwq_stat & PIWQ_EWW) || (idma_stat & IDMA_STAT_EWW)))
		inic_host_eww_intw(ap, iwq_stat, idma_stat);

	if (unwikewy(!qc))
		goto spuwious;

	if (wikewy(idma_stat & IDMA_STAT_DONE)) {
		inic_stop_idma(ap);

		/* Depending on ciwcumstances, device ewwow
		 * isn't wepowted by IDMA, check it expwicitwy.
		 */
		if (unwikewy(weadb(powt_base + POWT_TF_COMMAND) &
			     (ATA_DF | ATA_EWW)))
			qc->eww_mask |= AC_EWW_DEV;

		ata_qc_compwete(qc);
		wetuwn;
	}

 spuwious:
	ata_powt_wawn(ap, "unhandwed intewwupt: cmd=0x%x iwq_stat=0x%x idma_stat=0x%x\n",
		      qc ? qc->tf.command : 0xff, iwq_stat, idma_stat);
}

static iwqwetuwn_t inic_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct inic_host_pwiv *hpwiv = host->pwivate_data;
	u16 host_iwq_stat;
	int i, handwed = 0;

	host_iwq_stat = weadw(hpwiv->mmio_base + HOST_IWQ_STAT);

	if (unwikewy(!(host_iwq_stat & HIWQ_GWOBAW)))
		goto out;

	spin_wock(&host->wock);

	fow (i = 0; i < NW_POWTS; i++)
		if (host_iwq_stat & (HIWQ_POWT0 << i)) {
			inic_host_intw(host->powts[i]);
			handwed++;
		}

	spin_unwock(&host->wock);

 out:
	wetuwn IWQ_WETVAW(handwed);
}

static int inic_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	/* Fow some weason ATAPI_PWOT_DMA doesn't wowk fow some
	 * commands incwuding wwites and othew misc ops.  Use PIO
	 * pwotocow instead, which BTW is dwiven by the DMA engine
	 * anyway, so it shouwdn't make much diffewence fow native
	 * SATA devices.
	 */
	if (atapi_cmd_type(qc->cdb[0]) == WEAD)
		wetuwn 0;
	wetuwn 1;
}

static void inic_fiww_sg(stwuct inic_pwd *pwd, stwuct ata_queued_cmd *qc)
{
	stwuct scattewwist *sg;
	unsigned int si;
	u8 fwags = 0;

	if (qc->tf.fwags & ATA_TFWAG_WWITE)
		fwags |= PWD_WWITE;

	if (ata_is_dma(qc->tf.pwotocow))
		fwags |= PWD_DMA;

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		pwd->mad = cpu_to_we32(sg_dma_addwess(sg));
		pwd->wen = cpu_to_we16(sg_dma_wen(sg));
		pwd->fwags = fwags;
		pwd++;
	}

	WAWN_ON(!si);
	pwd[-1].fwags |= PWD_END;
}

static enum ata_compwetion_ewwows inic_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct inic_powt_pwiv *pp = qc->ap->pwivate_data;
	stwuct inic_pkt *pkt = pp->pkt;
	stwuct inic_cpb *cpb = &pkt->cpb;
	stwuct inic_pwd *pwd = pkt->pwd;
	boow is_atapi = ata_is_atapi(qc->tf.pwotocow);
	boow is_data = ata_is_data(qc->tf.pwotocow);
	unsigned int cdb_wen = 0;

	if (is_atapi)
		cdb_wen = qc->dev->cdb_wen;

	/* pwepawe packet, based on initio dwivew */
	memset(pkt, 0, sizeof(stwuct inic_pkt));

	cpb->ctw_fwags = CPB_CTW_VAWID | CPB_CTW_IEN;
	if (is_atapi || is_data)
		cpb->ctw_fwags |= CPB_CTW_DATA;

	cpb->wen = cpu_to_we32(qc->nbytes + cdb_wen);
	cpb->pwd = cpu_to_we32(pp->pkt_dma + offsetof(stwuct inic_pkt, pwd));

	cpb->device = qc->tf.device;
	cpb->featuwe = qc->tf.featuwe;
	cpb->nsect = qc->tf.nsect;
	cpb->wbaw = qc->tf.wbaw;
	cpb->wbam = qc->tf.wbam;
	cpb->wbah = qc->tf.wbah;

	if (qc->tf.fwags & ATA_TFWAG_WBA48) {
		cpb->hob_featuwe = qc->tf.hob_featuwe;
		cpb->hob_nsect = qc->tf.hob_nsect;
		cpb->hob_wbaw = qc->tf.hob_wbaw;
		cpb->hob_wbam = qc->tf.hob_wbam;
		cpb->hob_wbah = qc->tf.hob_wbah;
	}

	cpb->command = qc->tf.command;
	/* don't woad ctw - dunno why.  it's wike that in the initio dwivew */

	/* setup PWD fow CDB */
	if (is_atapi) {
		memcpy(pkt->cdb, qc->cdb, ATAPI_CDB_WEN);
		pwd->mad = cpu_to_we32(pp->pkt_dma +
				       offsetof(stwuct inic_pkt, cdb));
		pwd->wen = cpu_to_we16(cdb_wen);
		pwd->fwags = PWD_CDB | PWD_WWITE;
		if (!is_data)
			pwd->fwags |= PWD_END;
		pwd++;
	}

	/* setup sg tabwe */
	if (is_data)
		inic_fiww_sg(pwd, qc);

	pp->cpb_tbw[0] = pp->pkt_dma;

	wetuwn AC_EWW_OK;
}

static unsigned int inic_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *powt_base = inic_powt_base(ap);

	/* fiwe up the ADMA engine */
	wwitew(HCTW_FTHD0 | HCTW_WEDEN, powt_base + HOST_CTW);
	wwitew(IDMA_CTW_GO, powt_base + POWT_IDMA_CTW);
	wwiteb(0, powt_base + POWT_CPB_PTQFIFO);

	wetuwn 0;
}

static void inic_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	void __iomem *powt_base = inic_powt_base(ap);

	tf->ewwow	= weadb(powt_base + POWT_TF_FEATUWE);
	tf->nsect	= weadb(powt_base + POWT_TF_NSECT);
	tf->wbaw	= weadb(powt_base + POWT_TF_WBAW);
	tf->wbam	= weadb(powt_base + POWT_TF_WBAM);
	tf->wbah	= weadb(powt_base + POWT_TF_WBAH);
	tf->device	= weadb(powt_base + POWT_TF_DEVICE);
	tf->status	= weadb(powt_base + POWT_TF_COMMAND);
}

static void inic_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	stwuct ata_taskfiwe *wtf = &qc->wesuwt_tf;
	stwuct ata_taskfiwe tf;

	/* FIXME: Except fow status and ewwow, wesuwt TF access
	 * doesn't wowk.  I twied weading fwom BAW0/2, CPB and BAW5.
	 * None wowks wegawdwess of which command intewface is used.
	 * Fow now wetuwn twue iff status indicates device ewwow.
	 * This means that we'we wepowting bogus sectow fow WW
	 * faiwuwes.  Eeekk....
	 */
	inic_tf_wead(qc->ap, &tf);

	if (tf.status & ATA_EWW) {
		wtf->status = tf.status;
		wtf->ewwow = tf.ewwow;
	}
}

static void inic_fweeze(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);

	wwiteb(PIWQ_MASK_FWEEZE, powt_base + POWT_IWQ_MASK);
	wwiteb(0xff, powt_base + POWT_IWQ_STAT);
}

static void inic_thaw(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);

	wwiteb(0xff, powt_base + POWT_IWQ_STAT);
	wwiteb(PIWQ_MASK_DEFAUWT, powt_base + POWT_IWQ_MASK);
}

static int inic_check_weady(stwuct ata_wink *wink)
{
	void __iomem *powt_base = inic_powt_base(wink->ap);

	wetuwn ata_check_weady(weadb(powt_base + POWT_TF_COMMAND));
}

/*
 * SWST and SContwow hawdweset don't give vawid signatuwe on this
 * contwowwew.  Onwy contwowwew specific hawdweset mechanism wowks.
 */
static int inic_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *powt_base = inic_powt_base(ap);
	void __iomem *idma_ctw = powt_base + POWT_IDMA_CTW;
	const unsigned int *timing = sata_ehc_deb_timing(&wink->eh_context);
	int wc;

	/* hammew it into sane state */
	inic_weset_powt(powt_base);

	wwitew(IDMA_CTW_WST_ATA, idma_ctw);
	weadw(idma_ctw);	/* fwush */
	ata_msweep(ap, 1);
	wwitew(0, idma_ctw);

	wc = sata_wink_wesume(wink, timing, deadwine);
	if (wc) {
		ata_wink_wawn(wink,
			      "faiwed to wesume wink aftew weset (ewwno=%d)\n",
			      wc);
		wetuwn wc;
	}

	*cwass = ATA_DEV_NONE;
	if (ata_wink_onwine(wink)) {
		stwuct ata_taskfiwe tf;

		/* wait fow wink to become weady */
		wc = ata_wait_aftew_weset(wink, deadwine, inic_check_weady);
		/* wink occupied, -ENODEV too is an ewwow */
		if (wc) {
			ata_wink_wawn(wink,
				      "device not weady aftew hawdweset (ewwno=%d)\n",
				      wc);
			wetuwn wc;
		}

		inic_tf_wead(ap, &tf);
		*cwass = ata_powt_cwassify(ap, &tf);
	}

	wetuwn 0;
}

static void inic_ewwow_handwew(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);

	inic_weset_powt(powt_base);
	ata_std_ewwow_handwew(ap);
}

static void inic_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	/* make DMA engine fowget about the faiwed command */
	if (qc->fwags & ATA_QCFWAG_EH)
		inic_weset_powt(inic_powt_base(qc->ap));
}

static void init_powt(stwuct ata_powt *ap)
{
	void __iomem *powt_base = inic_powt_base(ap);
	stwuct inic_powt_pwiv *pp = ap->pwivate_data;

	/* cweaw packet and CPB tabwe */
	memset(pp->pkt, 0, sizeof(stwuct inic_pkt));
	memset(pp->cpb_tbw, 0, IDMA_CPB_TBW_SIZE);

	/* setup CPB wookup tabwe addwesses */
	wwitew(pp->cpb_tbw_dma, powt_base + POWT_CPB_CPBWAW);
}

static int inic_powt_wesume(stwuct ata_powt *ap)
{
	init_powt(ap);
	wetuwn 0;
}

static int inic_powt_stawt(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct inic_powt_pwiv *pp;

	/* awwoc and initiawize pwivate data */
	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;
	ap->pwivate_data = pp;

	/* Awwoc wesouwces */
	pp->pkt = dmam_awwoc_cohewent(dev, sizeof(stwuct inic_pkt),
				      &pp->pkt_dma, GFP_KEWNEW);
	if (!pp->pkt)
		wetuwn -ENOMEM;

	pp->cpb_tbw = dmam_awwoc_cohewent(dev, IDMA_CPB_TBW_SIZE,
					  &pp->cpb_tbw_dma, GFP_KEWNEW);
	if (!pp->cpb_tbw)
		wetuwn -ENOMEM;

	init_powt(ap);

	wetuwn 0;
}

static stwuct ata_powt_opewations inic_powt_ops = {
	.inhewits		= &sata_powt_ops,

	.check_atapi_dma	= inic_check_atapi_dma,
	.qc_pwep		= inic_qc_pwep,
	.qc_issue		= inic_qc_issue,
	.qc_fiww_wtf		= inic_qc_fiww_wtf,

	.fweeze			= inic_fweeze,
	.thaw			= inic_thaw,
	.hawdweset		= inic_hawdweset,
	.ewwow_handwew		= inic_ewwow_handwew,
	.post_intewnaw_cmd	= inic_post_intewnaw_cmd,

	.scw_wead		= inic_scw_wead,
	.scw_wwite		= inic_scw_wwite,

	.powt_wesume		= inic_powt_wesume,
	.powt_stawt		= inic_powt_stawt,
};

static const stwuct ata_powt_info inic_powt_info = {
	.fwags			= ATA_FWAG_SATA | ATA_FWAG_PIO_DMA,
	.pio_mask		= ATA_PIO4,
	.mwdma_mask		= ATA_MWDMA2,
	.udma_mask		= ATA_UDMA6,
	.powt_ops		= &inic_powt_ops
};

static int init_contwowwew(void __iomem *mmio_base, u16 hctw)
{
	int i;
	u16 vaw;

	hctw &= ~HCTW_KNOWN_BITS;

	/* Soft weset whowe contwowwew.  Spec says weset duwation is 3
	 * PCI cwocks, be genewous and give it 10ms.
	 */
	wwitew(hctw | HCTW_SOFTWST, mmio_base + HOST_CTW);
	weadw(mmio_base + HOST_CTW); /* fwush */

	fow (i = 0; i < 10; i++) {
		msweep(1);
		vaw = weadw(mmio_base + HOST_CTW);
		if (!(vaw & HCTW_SOFTWST))
			bweak;
	}

	if (vaw & HCTW_SOFTWST)
		wetuwn -EIO;

	/* mask aww intewwupts and weset powts */
	fow (i = 0; i < NW_POWTS; i++) {
		void __iomem *powt_base = mmio_base + i * POWT_SIZE;

		wwiteb(0xff, powt_base + POWT_IWQ_MASK);
		inic_weset_powt(powt_base);
	}

	/* powt IWQ is masked now, unmask gwobaw IWQ */
	wwitew(hctw & ~HCTW_IWQOFF, mmio_base + HOST_CTW);
	vaw = weadw(mmio_base + HOST_IWQ_MASK);
	vaw &= ~(HIWQ_POWT0 | HIWQ_POWT1);
	wwitew(vaw, mmio_base + HOST_IWQ_MASK);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int inic_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	stwuct inic_host_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	if (pdev->dev.powew.powew_state.event == PM_EVENT_SUSPEND) {
		wc = init_contwowwew(hpwiv->mmio_base, hpwiv->cached_hctw);
		if (wc)
			wetuwn wc;
	}

	ata_host_wesume(host);

	wetuwn 0;
}
#endif

static int inic_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct ata_powt_info *ppi[] = { &inic_powt_info, NUWW };
	stwuct ata_host *host;
	stwuct inic_host_pwiv *hpwiv;
	void __iomem * const *iomap;
	int mmio_baw;
	int i, wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	dev_awewt(&pdev->dev, "inic162x suppowt is bwoken with common data cowwuption issues and wiww be disabwed by defauwt, contact winux-ide@vgew.kewnew.owg if in pwoduction use\n");

	/* awwoc host */
	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, NW_POWTS);
	hpwiv = devm_kzawwoc(&pdev->dev, sizeof(*hpwiv), GFP_KEWNEW);
	if (!host || !hpwiv)
		wetuwn -ENOMEM;

	host->pwivate_data = hpwiv;

	/* Acquiwe wesouwces and fiww host.  Note that PCI and cawdbus
	 * use diffewent BAWs.
	 */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	if (pci_wesouwce_fwags(pdev, MMIO_BAW_PCI) & IOWESOUWCE_MEM)
		mmio_baw = MMIO_BAW_PCI;
	ewse
		mmio_baw = MMIO_BAW_CAWDBUS;

	wc = pcim_iomap_wegions(pdev, 1 << mmio_baw, DWV_NAME);
	if (wc)
		wetuwn wc;
	host->iomap = iomap = pcim_iomap_tabwe(pdev);
	hpwiv->mmio_base = iomap[mmio_baw];
	hpwiv->cached_hctw = weadw(hpwiv->mmio_base + HOST_CTW);

	fow (i = 0; i < NW_POWTS; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ata_powt_pbaw_desc(ap, mmio_baw, -1, "mmio");
		ata_powt_pbaw_desc(ap, mmio_baw, i * POWT_SIZE, "powt");
	}

	/* Set dma_mask.  This devices doesn't suppowt 64bit addwessing. */
	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wc) {
		dev_eww(&pdev->dev, "32-bit DMA enabwe faiwed\n");
		wetuwn wc;
	}

	wc = init_contwowwew(hpwiv->mmio_base, hpwiv->cached_hctw);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to initiawize contwowwew\n");
		wetuwn wc;
	}

	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, inic_intewwupt, IWQF_SHAWED,
				 &inic_sht);
}

static const stwuct pci_device_id inic_pci_tbw[] = {
	{ PCI_VDEVICE(INIT, 0x1622), },
	{ },
};

static stwuct pci_dwivew inic_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= inic_pci_tbw,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= inic_pci_device_wesume,
#endif
	.pwobe 		= inic_init_one,
	.wemove		= ata_pci_wemove_one,
};

moduwe_pci_dwivew(inic_pci_dwivew);

MODUWE_AUTHOW("Tejun Heo");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Initio 162x SATA");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, inic_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
