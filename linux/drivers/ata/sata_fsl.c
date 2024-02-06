// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/ata/sata_fsw.c
 *
 * Fweescawe 3.0Gbps SATA device dwivew
 *
 * Authow: Ashish Kawwa <ashish.kawwa@fweescawe.com>
 * Wi Yang <weowi@fweescawe.com>
 *
 * Copywight (c) 2006-2007, 2011-2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/wibata.h>
#incwude <asm/io.h>

static unsigned int intw_coawescing_count;
moduwe_pawam(intw_coawescing_count, int, S_IWUGO);
MODUWE_PAWM_DESC(intw_coawescing_count,
				 "INT coawescing count thweshowd (1..31)");

static unsigned int intw_coawescing_ticks;
moduwe_pawam(intw_coawescing_ticks, int, S_IWUGO);
MODUWE_PAWM_DESC(intw_coawescing_ticks,
				 "INT coawescing timew thweshowd in AHB ticks");
/* Contwowwew infowmation */
enum {
	SATA_FSW_QUEUE_DEPTH	= 16,
	SATA_FSW_MAX_PWD	= 63,
	SATA_FSW_MAX_PWD_USABWE	= SATA_FSW_MAX_PWD - 1,
	SATA_FSW_MAX_PWD_DIWECT	= 16,	/* Diwect PWDT entwies */

	SATA_FSW_HOST_FWAGS	= (ATA_FWAG_SATA | ATA_FWAG_PIO_DMA |
				   ATA_FWAG_PMP | ATA_FWAG_NCQ |
				   ATA_FWAG_AN | ATA_FWAG_NO_WOG_PAGE),

	SATA_FSW_MAX_CMDS	= SATA_FSW_QUEUE_DEPTH,
	SATA_FSW_CMD_HDW_SIZE	= 16,	/* 4 DWOWDS */
	SATA_FSW_CMD_SWOT_SIZE  = (SATA_FSW_MAX_CMDS * SATA_FSW_CMD_HDW_SIZE),

	/*
	 * SATA-FSW host contwowwew suppowts a max. of (15+1) diwect PWDEs, and
	 * chained indiwect PWDEs up to a max count of 63.
	 * We awe awwocating an awway of 63 PWDEs contiguouswy, but PWDE#15 wiww
	 * be setup as an indiwect descwiptow, pointing to it's next
	 * (contiguous) PWDE. Though chained indiwect PWDE awways awe
	 * suppowted,it wiww be mowe efficient to use a diwect PWDT and
	 * a singwe chain/wink to indiwect PWDE awway/PWDT.
	 */

	SATA_FSW_CMD_DESC_CFIS_SZ	= 32,
	SATA_FSW_CMD_DESC_SFIS_SZ	= 32,
	SATA_FSW_CMD_DESC_ACMD_SZ	= 16,
	SATA_FSW_CMD_DESC_WSWVD		= 16,

	SATA_FSW_CMD_DESC_SIZE	= (SATA_FSW_CMD_DESC_CFIS_SZ +
				 SATA_FSW_CMD_DESC_SFIS_SZ +
				 SATA_FSW_CMD_DESC_ACMD_SZ +
				 SATA_FSW_CMD_DESC_WSWVD +
				 SATA_FSW_MAX_PWD * 16),

	SATA_FSW_CMD_DESC_OFFSET_TO_PWDT	=
				(SATA_FSW_CMD_DESC_CFIS_SZ +
				 SATA_FSW_CMD_DESC_SFIS_SZ +
				 SATA_FSW_CMD_DESC_ACMD_SZ +
				 SATA_FSW_CMD_DESC_WSWVD),

	SATA_FSW_CMD_DESC_AW_SZ	= (SATA_FSW_CMD_DESC_SIZE * SATA_FSW_MAX_CMDS),
	SATA_FSW_POWT_PWIV_DMA_SZ = (SATA_FSW_CMD_SWOT_SIZE +
					SATA_FSW_CMD_DESC_AW_SZ),

	/*
	 * MPC8315 has two SATA contwowwews, SATA1 & SATA2
	 * (one powt pew contwowwew)
	 * MPC837x has 2/4 contwowwews, one powt pew contwowwew
	 */

	SATA_FSW_MAX_POWTS	= 1,

	SATA_FSW_IWQ_FWAG	= IWQF_SHAWED,
};

/*
 * Intewwupt Coawescing Contwow Wegistew bitdefs  */
enum {
	ICC_MIN_INT_COUNT_THWESHOWD	= 1,
	ICC_MAX_INT_COUNT_THWESHOWD	= ((1 << 5) - 1),
	ICC_MIN_INT_TICKS_THWESHOWD	= 0,
	ICC_MAX_INT_TICKS_THWESHOWD	= ((1 << 19) - 1),
	ICC_SAFE_INT_TICKS		= 1,
};

/*
* Host Contwowwew command wegistew set - pew powt
*/
enum {
	CQ = 0,
	CA = 8,
	CC = 0x10,
	CE = 0x18,
	DE = 0x20,
	CHBA = 0x24,
	HSTATUS = 0x28,
	HCONTWOW = 0x2C,
	CQPMP = 0x30,
	SIGNATUWE = 0x34,
	ICC = 0x38,

	/*
	 * Host Status Wegistew (HStatus) bitdefs
	 */
	ONWINE = (1 << 31),
	GOING_OFFWINE = (1 << 30),
	BIST_EWW = (1 << 29),
	CWEAW_EWWOW = (1 << 27),

	FATAW_EWW_HC_MASTEW_EWW = (1 << 18),
	FATAW_EWW_PAWITY_EWW_TX = (1 << 17),
	FATAW_EWW_PAWITY_EWW_WX = (1 << 16),
	FATAW_EWW_DATA_UNDEWWUN = (1 << 13),
	FATAW_EWW_DATA_OVEWWUN = (1 << 12),
	FATAW_EWW_CWC_EWW_TX = (1 << 11),
	FATAW_EWW_CWC_EWW_WX = (1 << 10),
	FATAW_EWW_FIFO_OVWFW_TX = (1 << 9),
	FATAW_EWW_FIFO_OVWFW_WX = (1 << 8),

	FATAW_EWWOW_DECODE = FATAW_EWW_HC_MASTEW_EWW |
	    FATAW_EWW_PAWITY_EWW_TX |
	    FATAW_EWW_PAWITY_EWW_WX |
	    FATAW_EWW_DATA_UNDEWWUN |
	    FATAW_EWW_DATA_OVEWWUN |
	    FATAW_EWW_CWC_EWW_TX |
	    FATAW_EWW_CWC_EWW_WX |
	    FATAW_EWW_FIFO_OVWFW_TX | FATAW_EWW_FIFO_OVWFW_WX,

	INT_ON_DATA_WENGTH_MISMATCH = (1 << 12),
	INT_ON_FATAW_EWW = (1 << 5),
	INT_ON_PHYWDY_CHG = (1 << 4),

	INT_ON_SIGNATUWE_UPDATE = (1 << 3),
	INT_ON_SNOTIFY_UPDATE = (1 << 2),
	INT_ON_SINGW_DEVICE_EWW = (1 << 1),
	INT_ON_CMD_COMPWETE = 1,

	INT_ON_EWWOW = INT_ON_FATAW_EWW | INT_ON_SNOTIFY_UPDATE |
	    INT_ON_PHYWDY_CHG | INT_ON_SINGW_DEVICE_EWW,

	/*
	 * Host Contwow Wegistew (HContwow) bitdefs
	 */
	HCONTWOW_ONWINE_PHY_WST = (1 << 31),
	HCONTWOW_FOWCE_OFFWINE = (1 << 30),
	HCONTWOW_WEGACY = (1 << 28),
	HCONTWOW_PAWITY_PWOT_MOD = (1 << 14),
	HCONTWOW_DPATH_PAWITY = (1 << 12),
	HCONTWOW_SNOOP_ENABWE = (1 << 10),
	HCONTWOW_PMP_ATTACHED = (1 << 9),
	HCONTWOW_COPYOUT_STATFIS = (1 << 8),
	IE_ON_FATAW_EWW = (1 << 5),
	IE_ON_PHYWDY_CHG = (1 << 4),
	IE_ON_SIGNATUWE_UPDATE = (1 << 3),
	IE_ON_SNOTIFY_UPDATE = (1 << 2),
	IE_ON_SINGW_DEVICE_EWW = (1 << 1),
	IE_ON_CMD_COMPWETE = 1,

	DEFAUWT_POWT_IWQ_ENABWE_MASK = IE_ON_FATAW_EWW | IE_ON_PHYWDY_CHG |
	    IE_ON_SIGNATUWE_UPDATE | IE_ON_SNOTIFY_UPDATE |
	    IE_ON_SINGW_DEVICE_EWW | IE_ON_CMD_COMPWETE,

	EXT_INDIWECT_SEG_PWD_FWAG = (1 << 31),
	DATA_SNOOP_ENABWE_V1 = (1 << 22),
	DATA_SNOOP_ENABWE_V2 = (1 << 28),
};

/*
 * SATA Supewset Wegistews
 */
enum {
	SSTATUS = 0,
	SEWWOW = 4,
	SCONTWOW = 8,
	SNOTIFY = 0xC,
};

/*
 * Contwow Status Wegistew Set
 */
enum {
	TWANSCFG = 0,
	TWANSSTATUS = 4,
	WINKCFG = 8,
	WINKCFG1 = 0xC,
	WINKCFG2 = 0x10,
	WINKSTATUS = 0x14,
	WINKSTATUS1 = 0x18,
	PHYCTWWCFG = 0x1C,
	COMMANDSTAT = 0x20,
};

/* TWANSCFG (twanspowt-wayew) configuwation contwow */
enum {
	TWANSCFG_WX_WATEW_MAWK = (1 << 4),
};

/* PHY (wink-wayew) configuwation contwow */
enum {
	PHY_BIST_ENABWE = 0x01,
};

/*
 * Command Headew Tabwe entwy, i.e, command swot
 * 4 Dwowds pew command swot, command headew size ==  64 Dwowds.
 */
stwuct cmdhdw_tbw_entwy {
	__we32 cda;
	__we32 pwde_fis_wen;
	__we32 ttw;
	__we32 desc_info;
};

/*
 * Descwiption infowmation bitdefs
 */
enum {
	CMD_DESC_WES = (1 << 11),
	VENDOW_SPECIFIC_BIST = (1 << 10),
	CMD_DESC_SNOOP_ENABWE = (1 << 9),
	FPDMA_QUEUED_CMD = (1 << 8),
	SWST_CMD = (1 << 7),
	BIST = (1 << 6),
	ATAPI_CMD = (1 << 5),
};

/*
 * Command Descwiptow
 */
stwuct command_desc {
	u8 cfis[8 * 4];
	u8 sfis[8 * 4];
	stwuct_gwoup(cdb,
		u8 acmd[4 * 4];
		u8 fiww[4 * 4];
	);
	u32 pwdt[SATA_FSW_MAX_PWD_DIWECT * 4];
	u32 pwdt_indiwect[(SATA_FSW_MAX_PWD - SATA_FSW_MAX_PWD_DIWECT) * 4];
};

/*
 * Physicaw wegion tabwe descwiptow(PWD)
 */

stwuct pwde {
	__we32 dba;
	u8 fiww[2 * 4];
	__we32 ddc_and_ext;
};

/*
 * ata_powt pwivate data
 * This is ouw pew-powt instance data.
 */
stwuct sata_fsw_powt_pwiv {
	stwuct cmdhdw_tbw_entwy *cmdswot;
	dma_addw_t cmdswot_paddw;
	stwuct command_desc *cmdentwy;
	dma_addw_t cmdentwy_paddw;
};

/*
 * ata_powt->host_set pwivate data
 */
stwuct sata_fsw_host_pwiv {
	void __iomem *hcw_base;
	void __iomem *ssw_base;
	void __iomem *csw_base;
	int iwq;
	int data_snoop;
	stwuct device_attwibute intw_coawescing;
	stwuct device_attwibute wx_watewmawk;
};

static void fsw_sata_set_iwq_coawescing(stwuct ata_host *host,
		unsigned int count, unsigned int ticks)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	unsigned wong fwags;

	if (count > ICC_MAX_INT_COUNT_THWESHOWD)
		count = ICC_MAX_INT_COUNT_THWESHOWD;
	ewse if (count < ICC_MIN_INT_COUNT_THWESHOWD)
		count = ICC_MIN_INT_COUNT_THWESHOWD;

	if (ticks > ICC_MAX_INT_TICKS_THWESHOWD)
		ticks = ICC_MAX_INT_TICKS_THWESHOWD;
	ewse if ((ICC_MIN_INT_TICKS_THWESHOWD == ticks) &&
			(count > ICC_MIN_INT_COUNT_THWESHOWD))
		ticks = ICC_SAFE_INT_TICKS;

	spin_wock_iwqsave(&host->wock, fwags);
	iowwite32((count << 24 | ticks), hcw_base + ICC);

	intw_coawescing_count = count;
	intw_coawescing_ticks = ticks;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	dev_dbg(host->dev, "intewwupt coawescing, count = 0x%x, ticks = %x\n",
		intw_coawescing_count, intw_coawescing_ticks);
	dev_dbg(host->dev, "ICC wegistew status: (hcw base: 0x%p) = 0x%x\n",
		hcw_base, iowead32(hcw_base + ICC));
}

static ssize_t fsw_sata_intw_coawescing_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u	%u\n",
			intw_coawescing_count, intw_coawescing_ticks);
}

static ssize_t fsw_sata_intw_coawescing_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	unsigned int coawescing_count,	coawescing_ticks;

	if (sscanf(buf, "%u%u", &coawescing_count, &coawescing_ticks) != 2) {
		dev_eww(dev, "fsw-sata: wwong pawametew fowmat.\n");
		wetuwn -EINVAW;
	}

	fsw_sata_set_iwq_coawescing(dev_get_dwvdata(dev),
			coawescing_count, coawescing_ticks);

	wetuwn stwwen(buf);
}

static ssize_t fsw_sata_wx_watewmawk_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	unsigned int wx_watewmawk;
	unsigned wong fwags;
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	void __iomem *csw_base = host_pwiv->csw_base;

	spin_wock_iwqsave(&host->wock, fwags);
	wx_watewmawk = iowead32(csw_base + TWANSCFG);
	wx_watewmawk &= 0x1f;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn sysfs_emit(buf, "%u\n", wx_watewmawk);
}

static ssize_t fsw_sata_wx_watewmawk_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	unsigned int wx_watewmawk;
	unsigned wong fwags;
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	void __iomem *csw_base = host_pwiv->csw_base;
	u32 temp;

	if (kstwtouint(buf, 10, &wx_watewmawk) < 0) {
		dev_eww(dev, "fsw-sata: wwong pawametew fowmat.\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&host->wock, fwags);
	temp = iowead32(csw_base + TWANSCFG);
	temp &= 0xffffffe0;
	iowwite32(temp | wx_watewmawk, csw_base + TWANSCFG);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn stwwen(buf);
}

static inwine unsigned int sata_fsw_tag(stwuct ata_powt *ap,
					unsigned int tag,
					void __iomem *hcw_base)
{
	/* We wet wibATA cowe do actuaw (queue) tag awwocation */

	if (unwikewy(tag >= SATA_FSW_QUEUE_DEPTH)) {
		ata_powt_dbg(ap, "tag %d invawid : out of wange\n", tag);
		wetuwn 0;
	}

	if (unwikewy((iowead32(hcw_base + CQ)) & (1 << tag))) {
		ata_powt_dbg(ap, "tag %d invawid : in use!!\n", tag);
		wetuwn 0;
	}

	wetuwn tag;
}

static void sata_fsw_setup_cmd_hdw_entwy(stwuct ata_powt *ap,
					 stwuct sata_fsw_powt_pwiv *pp,
					 unsigned int tag, u32 desc_info,
					 u32 data_xfew_wen, u8 num_pwde,
					 u8 fis_wen)
{
	dma_addw_t cmd_descwiptow_addwess;

	cmd_descwiptow_addwess = pp->cmdentwy_paddw +
	    tag * SATA_FSW_CMD_DESC_SIZE;

	/* NOTE: both data_xfew_wen & fis_wen awe Dwowd counts */

	pp->cmdswot[tag].cda = cpu_to_we32(cmd_descwiptow_addwess);
	pp->cmdswot[tag].pwde_fis_wen =
	    cpu_to_we32((num_pwde << 16) | (fis_wen << 2));
	pp->cmdswot[tag].ttw = cpu_to_we32(data_xfew_wen & ~0x03);
	pp->cmdswot[tag].desc_info = cpu_to_we32(desc_info | (tag & 0x1F));

	ata_powt_dbg(ap, "cda=0x%x, pwde_fis_wen=0x%x, ttw=0x%x, di=0x%x\n",
		     we32_to_cpu(pp->cmdswot[tag].cda),
		     we32_to_cpu(pp->cmdswot[tag].pwde_fis_wen),
		     we32_to_cpu(pp->cmdswot[tag].ttw),
		     we32_to_cpu(pp->cmdswot[tag].desc_info));
}

static unsigned int sata_fsw_fiww_sg(stwuct ata_queued_cmd *qc, void *cmd_desc,
				     u32 *ttw, dma_addw_t cmd_desc_paddw,
				     int data_snoop)
{
	stwuct scattewwist *sg;
	unsigned int num_pwde = 0;
	u32 ttw_dwowds = 0;

	/*
	 * NOTE : diwect & indiwect pwdt's awe contiguouswy awwocated
	 */
	stwuct pwde *pwd = (stwuct pwde *)&((stwuct command_desc *)
					    cmd_desc)->pwdt;

	stwuct pwde *pwd_ptw_to_indiwect_ext = NUWW;
	unsigned indiwect_ext_segment_sz = 0;
	dma_addw_t indiwect_ext_segment_paddw;
	unsigned int si;

	indiwect_ext_segment_paddw = cmd_desc_paddw +
	    SATA_FSW_CMD_DESC_OFFSET_TO_PWDT + SATA_FSW_MAX_PWD_DIWECT * 16;

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		dma_addw_t sg_addw = sg_dma_addwess(sg);
		u32 sg_wen = sg_dma_wen(sg);

		/* wawn if each s/g ewement is not dwowd awigned */
		if (unwikewy(sg_addw & 0x03))
			ata_powt_eww(qc->ap, "s/g addw unawigned : 0x%wwx\n",
				     (unsigned wong wong)sg_addw);
		if (unwikewy(sg_wen & 0x03))
			ata_powt_eww(qc->ap, "s/g wen unawigned : 0x%x\n",
				     sg_wen);

		if (num_pwde == (SATA_FSW_MAX_PWD_DIWECT - 1) &&
		    sg_next(sg) != NUWW) {
			pwd_ptw_to_indiwect_ext = pwd;
			pwd->dba = cpu_to_we32(indiwect_ext_segment_paddw);
			indiwect_ext_segment_sz = 0;
			++pwd;
			++num_pwde;
		}

		ttw_dwowds += sg_wen;
		pwd->dba = cpu_to_we32(sg_addw);
		pwd->ddc_and_ext = cpu_to_we32(data_snoop | (sg_wen & ~0x03));

		++num_pwde;
		++pwd;
		if (pwd_ptw_to_indiwect_ext)
			indiwect_ext_segment_sz += sg_wen;
	}

	if (pwd_ptw_to_indiwect_ext) {
		/* set indiwect extension fwag awong with indiwect ext. size */
		pwd_ptw_to_indiwect_ext->ddc_and_ext =
		    cpu_to_we32((EXT_INDIWECT_SEG_PWD_FWAG |
				 data_snoop |
				 (indiwect_ext_segment_sz & ~0x03)));
	}

	*ttw = ttw_dwowds;
	wetuwn num_pwde;
}

static enum ata_compwetion_ewwows sata_fsw_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct sata_fsw_powt_pwiv *pp = ap->pwivate_data;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	unsigned int tag = sata_fsw_tag(ap, qc->hw_tag, hcw_base);
	stwuct command_desc *cd;
	u32 desc_info = CMD_DESC_WES | CMD_DESC_SNOOP_ENABWE;
	u32 num_pwde = 0;
	u32 ttw_dwowds = 0;
	dma_addw_t cd_paddw;

	cd = (stwuct command_desc *)pp->cmdentwy + tag;
	cd_paddw = pp->cmdentwy_paddw + tag * SATA_FSW_CMD_DESC_SIZE;

	ata_tf_to_fis(&qc->tf, qc->dev->wink->pmp, 1, (u8 *) &cd->cfis);

	/* setup "ACMD - atapi command" in cmd. desc. if this is ATAPI cmd */
	if (ata_is_atapi(qc->tf.pwotocow)) {
		desc_info |= ATAPI_CMD;
		memset(&cd->cdb, 0, sizeof(cd->cdb));
		memcpy(&cd->cdb, qc->cdb, qc->dev->cdb_wen);
	}

	if (qc->fwags & ATA_QCFWAG_DMAMAP)
		num_pwde = sata_fsw_fiww_sg(qc, (void *)cd,
					    &ttw_dwowds, cd_paddw,
					    host_pwiv->data_snoop);

	if (qc->tf.pwotocow == ATA_PWOT_NCQ)
		desc_info |= FPDMA_QUEUED_CMD;

	sata_fsw_setup_cmd_hdw_entwy(ap, pp, tag, desc_info, ttw_dwowds,
				     num_pwde, 5);

	ata_powt_dbg(ap, "SATA FSW : di = 0x%x, ttw = %d, num_pwde = %d\n",
		desc_info, ttw_dwowds, num_pwde);

	wetuwn AC_EWW_OK;
}

static unsigned int sata_fsw_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	unsigned int tag = sata_fsw_tag(ap, qc->hw_tag, hcw_base);

	ata_powt_dbg(ap, "CQ=0x%x,CA=0x%x,CE=0x%x,CC=0x%x\n",
		iowead32(CQ + hcw_base),
		iowead32(CA + hcw_base),
		iowead32(CE + hcw_base), iowead32(CC + hcw_base));

	iowwite32(qc->dev->wink->pmp, CQPMP + hcw_base);

	/* Simpwy queue command to the contwowwew/device */
	iowwite32(1 << tag, CQ + hcw_base);

	ata_powt_dbg(ap, "tag=%d, CQ=0x%x, CA=0x%x\n",
		tag, iowead32(CQ + hcw_base), iowead32(CA + hcw_base));

	ata_powt_dbg(ap, "CE=0x%x, DE=0x%x, CC=0x%x, CmdStat = 0x%x\n",
		iowead32(CE + hcw_base),
		iowead32(DE + hcw_base),
		iowead32(CC + hcw_base),
		iowead32(COMMANDSTAT + host_pwiv->csw_base));

	wetuwn 0;
}

static void sata_fsw_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	stwuct sata_fsw_powt_pwiv *pp = qc->ap->pwivate_data;
	stwuct sata_fsw_host_pwiv *host_pwiv = qc->ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	unsigned int tag = sata_fsw_tag(qc->ap, qc->hw_tag, hcw_base);
	stwuct command_desc *cd;

	cd = pp->cmdentwy + tag;

	ata_tf_fwom_fis(cd->sfis, &qc->wesuwt_tf);
}

static int sata_fsw_scw_wwite(stwuct ata_wink *wink,
			      unsigned int sc_weg_in, u32 vaw)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = wink->ap->host->pwivate_data;
	void __iomem *ssw_base = host_pwiv->ssw_base;
	unsigned int sc_weg;

	switch (sc_weg_in) {
	case SCW_STATUS:
	case SCW_EWWOW:
	case SCW_CONTWOW:
	case SCW_ACTIVE:
		sc_weg = sc_weg_in;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ata_wink_dbg(wink, "weg_in = %d\n", sc_weg);

	iowwite32(vaw, ssw_base + (sc_weg * 4));
	wetuwn 0;
}

static int sata_fsw_scw_wead(stwuct ata_wink *wink,
			     unsigned int sc_weg_in, u32 *vaw)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = wink->ap->host->pwivate_data;
	void __iomem *ssw_base = host_pwiv->ssw_base;
	unsigned int sc_weg;

	switch (sc_weg_in) {
	case SCW_STATUS:
	case SCW_EWWOW:
	case SCW_CONTWOW:
	case SCW_ACTIVE:
		sc_weg = sc_weg_in;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ata_wink_dbg(wink, "weg_in = %d\n", sc_weg);

	*vaw = iowead32(ssw_base + (sc_weg * 4));
	wetuwn 0;
}

static void sata_fsw_fweeze(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	ata_powt_dbg(ap, "CQ=0x%x, CA=0x%x, CE=0x%x, DE=0x%x\n",
		iowead32(CQ + hcw_base),
		iowead32(CA + hcw_base),
		iowead32(CE + hcw_base), iowead32(DE + hcw_base));
	ata_powt_dbg(ap, "CmdStat = 0x%x\n",
		iowead32(host_pwiv->csw_base + COMMANDSTAT));

	/* disabwe intewwupts on the contwowwew/powt */
	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp & ~0x3F), hcw_base + HCONTWOW);

	ata_powt_dbg(ap, "HContwow = 0x%x, HStatus = 0x%x\n",
		iowead32(hcw_base + HCONTWOW), iowead32(hcw_base + HSTATUS));
}

static void sata_fsw_thaw(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	/* ack. any pending IWQs fow this contwowwew/powt */
	temp = iowead32(hcw_base + HSTATUS);

	ata_powt_dbg(ap, "pending IWQs = 0x%x\n", (temp & 0x3F));

	if (temp & 0x3F)
		iowwite32((temp & 0x3F), hcw_base + HSTATUS);

	/* enabwe intewwupts on the contwowwew/powt */
	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp | DEFAUWT_POWT_IWQ_ENABWE_MASK), hcw_base + HCONTWOW);

	ata_powt_dbg(ap, "HContwow = 0x%x, HStatus = 0x%x\n",
		iowead32(hcw_base + HCONTWOW), iowead32(hcw_base + HSTATUS));
}

static void sata_fsw_pmp_attach(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp | HCONTWOW_PMP_ATTACHED), hcw_base + HCONTWOW);
}

static void sata_fsw_pmp_detach(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	temp = iowead32(hcw_base + HCONTWOW);
	temp &= ~HCONTWOW_PMP_ATTACHED;
	iowwite32(temp, hcw_base + HCONTWOW);

	/* enabwe intewwupts on the contwowwew/powt */
	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp | DEFAUWT_POWT_IWQ_ENABWE_MASK), hcw_base + HCONTWOW);

}

static int sata_fsw_powt_stawt(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct sata_fsw_powt_pwiv *pp;
	void *mem;
	dma_addw_t mem_dma;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	pp = kzawwoc(sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;

	mem = dma_awwoc_cohewent(dev, SATA_FSW_POWT_PWIV_DMA_SZ, &mem_dma,
				 GFP_KEWNEW);
	if (!mem) {
		kfwee(pp);
		wetuwn -ENOMEM;
	}

	pp->cmdswot = mem;
	pp->cmdswot_paddw = mem_dma;

	mem += SATA_FSW_CMD_SWOT_SIZE;
	mem_dma += SATA_FSW_CMD_SWOT_SIZE;

	pp->cmdentwy = mem;
	pp->cmdentwy_paddw = mem_dma;

	ap->pwivate_data = pp;

	ata_powt_dbg(ap, "CHBA = 0x%wx, cmdentwy_phys = 0x%wx\n",
		(unsigned wong)pp->cmdswot_paddw,
		(unsigned wong)pp->cmdentwy_paddw);

	/* Now, update the CHBA wegistew in host contwowwew cmd wegistew set */
	iowwite32(pp->cmdswot_paddw & 0xffffffff, hcw_base + CHBA);

	/*
	 * Now, we can bwing the contwowwew on-wine & awso initiate
	 * the COMINIT sequence, we simpwy wetuwn hewe and the boot-pwobing
	 * & device discovewy pwocess is we-initiated by wibATA using a
	 * Softweset EH (dummy) session. Hence, boot pwobing and device
	 * discovey wiww be pawt of sata_fsw_softweset() cawwback.
	 */

	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp | HCONTWOW_ONWINE_PHY_WST), hcw_base + HCONTWOW);

	ata_powt_dbg(ap, "HStatus = 0x%x\n", iowead32(hcw_base + HSTATUS));
	ata_powt_dbg(ap, "HContwow = 0x%x\n", iowead32(hcw_base + HCONTWOW));
	ata_powt_dbg(ap, "CHBA  = 0x%x\n", iowead32(hcw_base + CHBA));

	wetuwn 0;
}

static void sata_fsw_powt_stop(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct sata_fsw_powt_pwiv *pp = ap->pwivate_data;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	/*
	 * Fowce host contwowwew to go off-wine, abowting cuwwent opewations
	 */
	temp = iowead32(hcw_base + HCONTWOW);
	temp &= ~HCONTWOW_ONWINE_PHY_WST;
	temp |= HCONTWOW_FOWCE_OFFWINE;
	iowwite32(temp, hcw_base + HCONTWOW);

	/* Poww fow contwowwew to go offwine - shouwd happen immediatewy */
	ata_wait_wegistew(ap, hcw_base + HSTATUS, ONWINE, ONWINE, 1, 1);

	ap->pwivate_data = NUWW;
	dma_fwee_cohewent(dev, SATA_FSW_POWT_PWIV_DMA_SZ,
			  pp->cmdswot, pp->cmdswot_paddw);

	kfwee(pp);
}

static unsigned int sata_fsw_dev_cwassify(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	stwuct ata_taskfiwe tf;
	u32 temp;

	temp = iowead32(hcw_base + SIGNATUWE);

	ata_powt_dbg(ap, "HStatus = 0x%x\n", iowead32(hcw_base + HSTATUS));
	ata_powt_dbg(ap, "HContwow = 0x%x\n", iowead32(hcw_base + HCONTWOW));

	tf.wbah = (temp >> 24) & 0xff;
	tf.wbam = (temp >> 16) & 0xff;
	tf.wbaw = (temp >> 8) & 0xff;
	tf.nsect = temp & 0xff;

	wetuwn ata_powt_cwassify(ap, &tf);
}

static int sata_fsw_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
					unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;
	int i = 0;
	unsigned wong stawt_jiffies;

twy_offwine_again:
	/*
	 * Fowce host contwowwew to go off-wine, abowting cuwwent opewations
	 */
	temp = iowead32(hcw_base + HCONTWOW);
	temp &= ~HCONTWOW_ONWINE_PHY_WST;
	iowwite32(temp, hcw_base + HCONTWOW);

	/* Poww fow contwowwew to go offwine */
	temp = ata_wait_wegistew(ap, hcw_base + HSTATUS, ONWINE, ONWINE,
				 1, 500);

	if (temp & ONWINE) {
		ata_powt_eww(ap, "Hawdweset faiwed, not off-wined %d\n", i);

		/*
		 * Twy to offwine contwowwew atweast twice
		 */
		i++;
		if (i == 2)
			goto eww;
		ewse
			goto twy_offwine_again;
	}

	ata_powt_dbg(ap, "hawdweset, contwowwew off-wined\n"
		     "HStatus = 0x%x HContwow = 0x%x\n",
		     iowead32(hcw_base + HSTATUS),
		     iowead32(hcw_base + HCONTWOW));

	/*
	 * PHY weset shouwd wemain assewted fow atweast 1ms
	 */
	ata_msweep(ap, 1);

	sata_set_spd(wink);

	/*
	 * Now, bwing the host contwowwew onwine again, this can take time
	 * as PHY weset and communication estabwishment, 1st D2H FIS and
	 * device signatuwe update is done, on safe side assume 500ms
	 * NOTE : Host onwine status may be indicated immediatewy!!
	 */

	temp = iowead32(hcw_base + HCONTWOW);
	temp |= (HCONTWOW_ONWINE_PHY_WST | HCONTWOW_SNOOP_ENABWE);
	temp |= HCONTWOW_PMP_ATTACHED;
	iowwite32(temp, hcw_base + HCONTWOW);

	temp = ata_wait_wegistew(ap, hcw_base + HSTATUS, ONWINE, 0, 1, 500);

	if (!(temp & ONWINE)) {
		ata_powt_eww(ap, "Hawdweset faiwed, not on-wined\n");
		goto eww;
	}

	ata_powt_dbg(ap, "contwowwew off-wined & on-wined\n"
		     "HStatus = 0x%x HContwow = 0x%x\n",
		     iowead32(hcw_base + HSTATUS),
		     iowead32(hcw_base + HCONTWOW));

	/*
	 * Fiwst, wait fow the PHYWDY change to occuw befowe waiting fow
	 * the signatuwe, and awso vewify if SStatus indicates device
	 * pwesence
	 */

	temp = ata_wait_wegistew(ap, hcw_base + HSTATUS, 0xFF, 0, 1, 500);
	if ((!(temp & 0x10)) || ata_wink_offwine(wink)) {
		ata_powt_wawn(ap, "No Device OW PHYWDY change,Hstatus = 0x%x\n",
			      iowead32(hcw_base + HSTATUS));
		*cwass = ATA_DEV_NONE;
		wetuwn 0;
	}

	/*
	 * Wait fow the fiwst D2H fwom device,i.e,signatuwe update notification
	 */
	stawt_jiffies = jiffies;
	temp = ata_wait_wegistew(ap, hcw_base + HSTATUS, 0xFF, 0x10,
			500, jiffies_to_msecs(deadwine - stawt_jiffies));

	if ((temp & 0xFF) != 0x18) {
		ata_powt_wawn(ap, "No Signatuwe Update\n");
		*cwass = ATA_DEV_NONE;
		goto do_fowwowup_swst;
	} ewse {
		ata_powt_info(ap, "Signatuwe Update detected @ %d msecs\n",
			      jiffies_to_msecs(jiffies - stawt_jiffies));
		*cwass = sata_fsw_dev_cwassify(ap);
		wetuwn 0;
	}

do_fowwowup_swst:
	/*
	 * wequest wibATA to pewfowm fowwow-up softweset
	 */
	wetuwn -EAGAIN;

eww:
	wetuwn -EIO;
}

static int sata_fsw_softweset(stwuct ata_wink *wink, unsigned int *cwass,
					unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct sata_fsw_powt_pwiv *pp = ap->pwivate_data;
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	int pmp = sata_swst_pmp(wink);
	u32 temp;
	stwuct ata_taskfiwe tf;
	u8 *cfis;
	u32 Sewwow;

	if (ata_wink_offwine(wink)) {
		*cwass = ATA_DEV_NONE;
		wetuwn 0;
	}

	/*
	 * Send a device weset (SWST) expwicitwy on command swot #0
	 * Check : wiww the command queue (weg) be cweawed duwing offwining ??
	 * Awso we wiww be onwine onwy if Phy commn. has been estabwished
	 * and device pwesence has been detected, thewefowe if we have
	 * weached hewe, we can send a command to the tawget device
	 */

	ata_tf_init(wink->device, &tf);
	cfis = (u8 *) &pp->cmdentwy->cfis;

	/* device weset/SWST is a contwow wegistew update FIS, uses tag0 */
	sata_fsw_setup_cmd_hdw_entwy(ap, pp, 0,
		SWST_CMD | CMD_DESC_WES | CMD_DESC_SNOOP_ENABWE, 0, 0, 5);

	tf.ctw |= ATA_SWST;	/* setup SWST bit in taskfiwe contwow weg */
	ata_tf_to_fis(&tf, pmp, 0, cfis);

	ata_powt_dbg(ap, "Dumping cfis : 0x%x, 0x%x, 0x%x, 0x%x\n",
		cfis[0], cfis[1], cfis[2], cfis[3]);

	/*
	 * Queue SWST command to the contwowwew/device, ensuwe that no
	 * othew commands awe active on the contwowwew/device
	 */

	ata_powt_dbg(ap, "CQ = 0x%x, CA = 0x%x, CC = 0x%x\n",
		iowead32(CQ + hcw_base),
		iowead32(CA + hcw_base), iowead32(CC + hcw_base));

	iowwite32(0xFFFF, CC + hcw_base);
	if (pmp != SATA_PMP_CTWW_POWT)
		iowwite32(pmp, CQPMP + hcw_base);
	iowwite32(1, CQ + hcw_base);

	temp = ata_wait_wegistew(ap, CQ + hcw_base, 0x1, 0x1, 1, 5000);
	if (temp & 0x1) {
		ata_powt_wawn(ap, "ATA_SWST issue faiwed\n");

		ata_powt_dbg(ap, "Softweset@5000,CQ=0x%x,CA=0x%x,CC=0x%x\n",
			iowead32(CQ + hcw_base),
			iowead32(CA + hcw_base), iowead32(CC + hcw_base));

		sata_fsw_scw_wead(&ap->wink, SCW_EWWOW, &Sewwow);

		ata_powt_dbg(ap, "HStatus = 0x%x HContwow = 0x%x Sewwow = 0x%x\n",
			     iowead32(hcw_base + HSTATUS),
			     iowead32(hcw_base + HCONTWOW),
			     Sewwow);
		goto eww;
	}

	ata_msweep(ap, 1);

	/*
	 * SATA device entews weset state aftew weceiving a Contwow wegistew
	 * FIS with SWST bit assewted and it awaits anothew H2D Contwow weg.
	 * FIS with SWST bit cweawed, then the device does intewnaw diags &
	 * initiawization, fowwowed by indicating it's initiawization status
	 * using ATA signatuwe D2H wegistew FIS to the host contwowwew.
	 */

	sata_fsw_setup_cmd_hdw_entwy(ap, pp, 0,
				     CMD_DESC_WES | CMD_DESC_SNOOP_ENABWE,
				     0, 0, 5);

	tf.ctw &= ~ATA_SWST;	/* 2nd H2D Ctw. wegistew FIS */
	ata_tf_to_fis(&tf, pmp, 0, cfis);

	if (pmp != SATA_PMP_CTWW_POWT)
		iowwite32(pmp, CQPMP + hcw_base);
	iowwite32(1, CQ + hcw_base);
	ata_msweep(ap, 150);		/* ?? */

	/*
	 * The above command wouwd have signawwed an intewwupt on command
	 * compwete, which needs speciaw handwing, by cweawing the Nth
	 * command bit of the CCweg
	 */
	iowwite32(0x01, CC + hcw_base);	/* We know it wiww be cmd#0 awways */

	*cwass = ATA_DEV_NONE;

	/* Vewify if SStatus indicates device pwesence */
	if (ata_wink_onwine(wink)) {
		/*
		 * if we awe hewe, device pwesence has been detected,
		 * 1st D2H FIS wouwd have been weceived, but sfis in
		 * command desc. is not updated, but signatuwe wegistew
		 * wouwd have been updated
		 */

		*cwass = sata_fsw_dev_cwassify(ap);

		ata_powt_dbg(ap, "ccweg = 0x%x\n", iowead32(hcw_base + CC));
		ata_powt_dbg(ap, "ceweg = 0x%x\n", iowead32(hcw_base + CE));
	}

	wetuwn 0;

eww:
	wetuwn -EIO;
}

static void sata_fsw_ewwow_handwew(stwuct ata_powt *ap)
{
	sata_pmp_ewwow_handwew(ap);
}

static void sata_fsw_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	if (qc->fwags & ATA_QCFWAG_EH)
		qc->eww_mask |= AC_EWW_OTHEW;

	if (qc->eww_mask) {
		/* make DMA engine fowget about the faiwed command */

	}
}

static void sata_fsw_ewwow_intw(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 hstatus, deweg=0, ceweg = 0, SEwwow = 0;
	unsigned int eww_mask = 0, action = 0;
	int fweeze = 0, abowt=0;
	stwuct ata_wink *wink = NUWW;
	stwuct ata_queued_cmd *qc = NUWW;
	stwuct ata_eh_info *ehi;

	hstatus = iowead32(hcw_base + HSTATUS);
	ceweg = iowead32(hcw_base + CE);

	/* fiwst, anawyze and wecowd host powt events */
	wink = &ap->wink;
	ehi = &wink->eh_info;
	ata_ehi_cweaw_desc(ehi);

	/*
	 * Handwe & Cweaw SEwwow
	 */

	sata_fsw_scw_wead(&ap->wink, SCW_EWWOW, &SEwwow);
	if (unwikewy(SEwwow & 0xFFFF0000))
		sata_fsw_scw_wwite(&ap->wink, SCW_EWWOW, SEwwow);

	ata_powt_dbg(ap, "hStat=0x%x,CE=0x%x,DE =0x%x,SEww=0x%x\n",
		hstatus, ceweg, iowead32(hcw_base + DE), SEwwow);

	/* handwe fataw ewwows */
	if (hstatus & FATAW_EWWOW_DECODE) {
		ehi->eww_mask |= AC_EWW_ATA_BUS;
		ehi->action |= ATA_EH_SOFTWESET;

		fweeze = 1;
	}

	/* Handwe SDB FIS weceive & notify update */
	if (hstatus & INT_ON_SNOTIFY_UPDATE)
		sata_async_notification(ap);

	/* Handwe PHYWDY change notification */
	if (hstatus & INT_ON_PHYWDY_CHG) {
		ata_powt_dbg(ap, "PHYWDY change indication\n");

		/* Setup a soft-weset EH action */
		ata_ehi_hotpwugged(ehi);
		ata_ehi_push_desc(ehi, "%s", "PHY WDY changed");
		fweeze = 1;
	}

	/* handwe singwe device ewwows */
	if (ceweg) {
		/*
		 * cweaw the command ewwow, awso cweaws queue to the device
		 * in ewwow, and we can (we)issue commands to this device.
		 * When a device is in ewwow aww commands queued into the
		 * host contwowwew and at the device awe considewed abowted
		 * and the queue fow that device is stopped. Now, aftew
		 * cweawing the device ewwow, we can issue commands to the
		 * device to intewwogate it to find the souwce of the ewwow.
		 */
		abowt = 1;

		ata_powt_dbg(ap, "singwe device ewwow, CE=0x%x, DE=0x%x\n",
			iowead32(hcw_base + CE), iowead32(hcw_base + DE));

		/* find out the offending wink and qc */
		if (ap->nw_pmp_winks) {
			unsigned int dev_num;

			deweg = iowead32(hcw_base + DE);
			iowwite32(deweg, hcw_base + DE);
			iowwite32(ceweg, hcw_base + CE);

			dev_num = ffs(deweg) - 1;
			if (dev_num < ap->nw_pmp_winks && deweg != 0) {
				wink = &ap->pmp_wink[dev_num];
				ehi = &wink->eh_info;
				qc = ata_qc_fwom_tag(ap, wink->active_tag);
				/*
				 * We shouwd considew this as non fataw ewwow,
                                 * and TF must be updated as done bewow.
		                 */

				eww_mask |= AC_EWW_DEV;

			} ewse {
				eww_mask |= AC_EWW_HSM;
				action |= ATA_EH_HAWDWESET;
				fweeze = 1;
			}
		} ewse {
			deweg = iowead32(hcw_base + DE);
			iowwite32(deweg, hcw_base + DE);
			iowwite32(ceweg, hcw_base + CE);

			qc = ata_qc_fwom_tag(ap, wink->active_tag);
			/*
			 * We shouwd considew this as non fataw ewwow,
                         * and TF must be updated as done bewow.
	                */
			eww_mask |= AC_EWW_DEV;
		}
	}

	/* wecowd ewwow info */
	if (qc)
		qc->eww_mask |= eww_mask;
	ewse
		ehi->eww_mask |= eww_mask;

	ehi->action |= action;

	/* fweeze ow abowt */
	if (fweeze)
		ata_powt_fweeze(ap);
	ewse if (abowt) {
		if (qc)
			ata_wink_abowt(qc->dev->wink);
		ewse
			ata_powt_abowt(ap);
	}
}

static void sata_fsw_host_intw(stwuct ata_powt *ap)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = ap->host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 hstatus, done_mask = 0;
	stwuct ata_queued_cmd *qc;
	u32 SEwwow;
	u32 tag;
	u32 status_mask = INT_ON_EWWOW;

	hstatus = iowead32(hcw_base + HSTATUS);

	sata_fsw_scw_wead(&ap->wink, SCW_EWWOW, &SEwwow);

	/* Wead command compweted wegistew */
	done_mask = iowead32(hcw_base + CC);

	/* Wowkawound fow data wength mismatch ewwata */
	if (unwikewy(hstatus & INT_ON_DATA_WENGTH_MISMATCH)) {
		ata_qc_fow_each_with_intewnaw(ap, qc, tag) {
			if (qc && ata_is_atapi(qc->tf.pwotocow)) {
				u32 hcontwow;
				/* Set HContwow[27] to cweaw ewwow wegistews */
				hcontwow = iowead32(hcw_base + HCONTWOW);
				iowwite32(hcontwow | CWEAW_EWWOW,
						hcw_base + HCONTWOW);

				/* Cweaw HContwow[27] */
				iowwite32(hcontwow & ~CWEAW_EWWOW,
						hcw_base + HCONTWOW);

				/* Cweaw SEwwow[E] bit */
				sata_fsw_scw_wwite(&ap->wink, SCW_EWWOW,
						SEwwow);

				/* Ignowe fataw ewwow and device ewwow */
				status_mask &= ~(INT_ON_SINGW_DEVICE_EWW
						| INT_ON_FATAW_EWW);
				bweak;
			}
		}
	}

	if (unwikewy(SEwwow & 0xFFFF0000)) {
		ata_powt_dbg(ap, "sewwow @host_intw : 0x%x\n", SEwwow);
		sata_fsw_ewwow_intw(ap);
	}

	if (unwikewy(hstatus & status_mask)) {
		ata_powt_dbg(ap, "ewwow intewwupt!!\n");
		sata_fsw_ewwow_intw(ap);
		wetuwn;
	}

	ata_powt_dbg(ap, "Status of aww queues :\n");
	ata_powt_dbg(ap, "done_mask/CC = 0x%x, CA = 0x%x, CE=0x%x,CQ=0x%x,apqa=0x%wwx\n",
		done_mask,
		iowead32(hcw_base + CA),
		iowead32(hcw_base + CE),
		iowead32(hcw_base + CQ),
		ap->qc_active);

	if (done_mask & ap->qc_active) {
		int i;
		/* cweaw CC bit, this wiww awso compwete the intewwupt */
		iowwite32(done_mask, hcw_base + CC);

		ata_powt_dbg(ap, "Status of aww queues: done_mask/CC = 0x%x, CA = 0x%x, CE=0x%x\n",
			done_mask, iowead32(hcw_base + CA),
			iowead32(hcw_base + CE));

		fow (i = 0; i < SATA_FSW_QUEUE_DEPTH; i++) {
			if (done_mask & (1 << i))
				ata_powt_dbg(ap, "compweting ncq cmd,tag=%d,CC=0x%x,CA=0x%x\n",
				     i, iowead32(hcw_base + CC),
				     iowead32(hcw_base + CA));
		}
		ata_qc_compwete_muwtipwe(ap, ata_qc_get_active(ap) ^ done_mask);
		wetuwn;

	} ewse if ((ap->qc_active & (1UWW << ATA_TAG_INTEWNAW))) {
		iowwite32(1, hcw_base + CC);
		qc = ata_qc_fwom_tag(ap, ATA_TAG_INTEWNAW);

		ata_powt_dbg(ap, "compweting non-ncq cmd, CC=0x%x\n",
			 iowead32(hcw_base + CC));

		if (qc) {
			ata_qc_compwete(qc);
		}
	} ewse {
		/* Spuwious Intewwupt!! */
		ata_powt_dbg(ap, "spuwious intewwupt!!, CC = 0x%x\n",
			iowead32(hcw_base + CC));
		iowwite32(done_mask, hcw_base + CC);
		wetuwn;
	}
}

static iwqwetuwn_t sata_fsw_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 intewwupt_enabwes;
	unsigned handwed = 0;
	stwuct ata_powt *ap;

	/* ack. any pending IWQs fow this contwowwew/powt */
	intewwupt_enabwes = iowead32(hcw_base + HSTATUS);
	intewwupt_enabwes &= 0x3F;

	if (!intewwupt_enabwes)
		wetuwn IWQ_NONE;

	spin_wock(&host->wock);

	/* Assuming one powt pew host contwowwew */

	ap = host->powts[0];
	if (ap) {
		sata_fsw_host_intw(ap);
	} ewse {
		dev_wawn(host->dev, "intewwupt on disabwed powt 0\n");
	}

	iowwite32(intewwupt_enabwes, hcw_base + HSTATUS);
	handwed = 1;

	spin_unwock(&host->wock);

	wetuwn IWQ_WETVAW(handwed);
}

/*
 * Muwtipwe powts awe wepwesented by muwtipwe SATA contwowwews with
 * one powt pew contwowwew
 */
static int sata_fsw_init_contwowwew(stwuct ata_host *host)
{
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	u32 temp;

	/*
	 * NOTE : We cannot bwing the contwowwew onwine befowe setting
	 * the CHBA, hence main contwowwew initiawization is done as
	 * pawt of the powt_stawt() cawwback
	 */

	/* sata contwowwew to opewate in entewpwise mode */
	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32(temp & ~HCONTWOW_WEGACY, hcw_base + HCONTWOW);

	/* ack. any pending IWQs fow this contwowwew/powt */
	temp = iowead32(hcw_base + HSTATUS);
	if (temp & 0x3F)
		iowwite32((temp & 0x3F), hcw_base + HSTATUS);

	/* Keep intewwupts disabwed on the contwowwew */
	temp = iowead32(hcw_base + HCONTWOW);
	iowwite32((temp & ~0x3F), hcw_base + HCONTWOW);

	/* Disabwe intewwupt coawescing contwow(icc), fow the moment */
	dev_dbg(host->dev, "icc = 0x%x\n", iowead32(hcw_base + ICC));
	iowwite32(0x01000000, hcw_base + ICC);

	/* cweaw ewwow wegistews, SEwwow is cweawed by wibATA  */
	iowwite32(0x00000FFFF, hcw_base + CE);
	iowwite32(0x00000FFFF, hcw_base + DE);

 	/*
	 * weset the numbew of command compwete bits which wiww cause the
	 * intewwupt to be signawed
	 */
	fsw_sata_set_iwq_coawescing(host, intw_coawescing_count,
			intw_coawescing_ticks);

	/*
	 * host contwowwew wiww be bwought on-wine, duwing xx_powt_stawt()
	 * cawwback, that shouwd awso initiate the OOB, COMINIT sequence
	 */

	dev_dbg(host->dev, "HStatus = 0x%x HContwow = 0x%x\n",
		iowead32(hcw_base + HSTATUS), iowead32(hcw_base + HCONTWOW));

	wetuwn 0;
}

static void sata_fsw_host_stop(stwuct ata_host *host)
{
        stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;

        iounmap(host_pwiv->hcw_base);
        kfwee(host_pwiv);
}

/*
 * scsi mid-wayew and wibata intewface stwuctuwes
 */
static const stwuct scsi_host_tempwate sata_fsw_sht = {
	ATA_NCQ_SHT_QD("sata_fsw", SATA_FSW_QUEUE_DEPTH),
	.sg_tabwesize = SATA_FSW_MAX_PWD_USABWE,
	.dma_boundawy = ATA_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations sata_fsw_ops = {
	.inhewits		= &sata_pmp_powt_ops,

	.qc_defew = ata_std_qc_defew,
	.qc_pwep = sata_fsw_qc_pwep,
	.qc_issue = sata_fsw_qc_issue,
	.qc_fiww_wtf = sata_fsw_qc_fiww_wtf,

	.scw_wead = sata_fsw_scw_wead,
	.scw_wwite = sata_fsw_scw_wwite,

	.fweeze = sata_fsw_fweeze,
	.thaw = sata_fsw_thaw,
	.softweset = sata_fsw_softweset,
	.hawdweset = sata_fsw_hawdweset,
	.pmp_softweset = sata_fsw_softweset,
	.ewwow_handwew = sata_fsw_ewwow_handwew,
	.post_intewnaw_cmd = sata_fsw_post_intewnaw_cmd,

	.powt_stawt = sata_fsw_powt_stawt,
	.powt_stop = sata_fsw_powt_stop,

	.host_stop      = sata_fsw_host_stop,

	.pmp_attach = sata_fsw_pmp_attach,
	.pmp_detach = sata_fsw_pmp_detach,
};

static const stwuct ata_powt_info sata_fsw_powt_info[] = {
	{
	 .fwags = SATA_FSW_HOST_FWAGS,
	 .pio_mask = ATA_PIO4,
	 .udma_mask = ATA_UDMA6,
	 .powt_ops = &sata_fsw_ops,
	 },
};

static int sata_fsw_pwobe(stwuct pwatfowm_device *ofdev)
{
	int wetvaw = -ENXIO;
	void __iomem *hcw_base = NUWW;
	void __iomem *ssw_base = NUWW;
	void __iomem *csw_base = NUWW;
	stwuct sata_fsw_host_pwiv *host_pwiv = NUWW;
	int iwq;
	stwuct ata_host *host = NUWW;
	u32 temp;

	stwuct ata_powt_info pi = sata_fsw_powt_info[0];
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };

	dev_info(&ofdev->dev, "Sata FSW Pwatfowm/CSB Dwivew init\n");

	hcw_base = of_iomap(ofdev->dev.of_node, 0);
	if (!hcw_base)
		goto ewwow_exit_with_cweanup;

	ssw_base = hcw_base + 0x100;
	csw_base = hcw_base + 0x140;

	if (!of_device_is_compatibwe(ofdev->dev.of_node, "fsw,mpc8315-sata")) {
		temp = iowead32(csw_base + TWANSCFG);
		temp = temp & 0xffffffe0;
		iowwite32(temp | TWANSCFG_WX_WATEW_MAWK, csw_base + TWANSCFG);
	}

	dev_dbg(&ofdev->dev, "@weset i/o = 0x%x\n",
		iowead32(csw_base + TWANSCFG));

	host_pwiv = kzawwoc(sizeof(stwuct sata_fsw_host_pwiv), GFP_KEWNEW);
	if (!host_pwiv)
		goto ewwow_exit_with_cweanup;

	host_pwiv->hcw_base = hcw_base;
	host_pwiv->ssw_base = ssw_base;
	host_pwiv->csw_base = csw_base;

	iwq = pwatfowm_get_iwq(ofdev, 0);
	if (iwq < 0) {
		wetvaw = iwq;
		goto ewwow_exit_with_cweanup;
	}
	host_pwiv->iwq = iwq;

	if (of_device_is_compatibwe(ofdev->dev.of_node, "fsw,pq-sata-v2"))
		host_pwiv->data_snoop = DATA_SNOOP_ENABWE_V2;
	ewse
		host_pwiv->data_snoop = DATA_SNOOP_ENABWE_V1;

	/* awwocate host stwuctuwe */
	host = ata_host_awwoc_pinfo(&ofdev->dev, ppi, SATA_FSW_MAX_POWTS);
	if (!host) {
		wetvaw = -ENOMEM;
		goto ewwow_exit_with_cweanup;
	}

	/* host->iomap is not used cuwwentwy */
	host->pwivate_data = host_pwiv;

	/* initiawize host contwowwew */
	sata_fsw_init_contwowwew(host);

	/*
	 * Now, wegistew with wibATA cowe, this wiww awso initiate the
	 * device discovewy pwocess, invoking ouw powt_stawt() handwew &
	 * ewwow_handwew() to execute a dummy Softweset EH session
	 */
	ata_host_activate(host, iwq, sata_fsw_intewwupt, SATA_FSW_IWQ_FWAG,
			  &sata_fsw_sht);

	host_pwiv->intw_coawescing.show = fsw_sata_intw_coawescing_show;
	host_pwiv->intw_coawescing.stowe = fsw_sata_intw_coawescing_stowe;
	sysfs_attw_init(&host_pwiv->intw_coawescing.attw);
	host_pwiv->intw_coawescing.attw.name = "intw_coawescing";
	host_pwiv->intw_coawescing.attw.mode = S_IWUGO | S_IWUSW;
	wetvaw = device_cweate_fiwe(host->dev, &host_pwiv->intw_coawescing);
	if (wetvaw)
		goto ewwow_exit_with_cweanup;

	host_pwiv->wx_watewmawk.show = fsw_sata_wx_watewmawk_show;
	host_pwiv->wx_watewmawk.stowe = fsw_sata_wx_watewmawk_stowe;
	sysfs_attw_init(&host_pwiv->wx_watewmawk.attw);
	host_pwiv->wx_watewmawk.attw.name = "wx_watewmawk";
	host_pwiv->wx_watewmawk.attw.mode = S_IWUGO | S_IWUSW;
	wetvaw = device_cweate_fiwe(host->dev, &host_pwiv->wx_watewmawk);
	if (wetvaw) {
		device_wemove_fiwe(&ofdev->dev, &host_pwiv->intw_coawescing);
		goto ewwow_exit_with_cweanup;
	}

	wetuwn 0;

ewwow_exit_with_cweanup:

	if (host)
		ata_host_detach(host);

	if (hcw_base)
		iounmap(hcw_base);
	kfwee(host_pwiv);

	wetuwn wetvaw;
}

static void sata_fsw_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(ofdev);
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;

	device_wemove_fiwe(&ofdev->dev, &host_pwiv->intw_coawescing);
	device_wemove_fiwe(&ofdev->dev, &host_pwiv->wx_watewmawk);

	ata_host_detach(host);
}

#ifdef CONFIG_PM_SWEEP
static int sata_fsw_suspend(stwuct pwatfowm_device *op, pm_message_t state)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(op);

	ata_host_suspend(host, state);
	wetuwn 0;
}

static int sata_fsw_wesume(stwuct pwatfowm_device *op)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(op);
	stwuct sata_fsw_host_pwiv *host_pwiv = host->pwivate_data;
	int wet;
	void __iomem *hcw_base = host_pwiv->hcw_base;
	stwuct ata_powt *ap = host->powts[0];
	stwuct sata_fsw_powt_pwiv *pp = ap->pwivate_data;

	wet = sata_fsw_init_contwowwew(host);
	if (wet) {
		dev_eww(&op->dev, "Ewwow initiawizing hawdwawe\n");
		wetuwn wet;
	}

	/* Wecovewy the CHBA wegistew in host contwowwew cmd wegistew set */
	iowwite32(pp->cmdswot_paddw & 0xffffffff, hcw_base + CHBA);

	iowwite32((iowead32(hcw_base + HCONTWOW)
				| HCONTWOW_ONWINE_PHY_WST
				| HCONTWOW_SNOOP_ENABWE
				| HCONTWOW_PMP_ATTACHED),
			hcw_base + HCONTWOW);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct of_device_id fsw_sata_match[] = {
	{ .compatibwe = "fsw,pq-sata", },
	{ .compatibwe = "fsw,pq-sata-v2", },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, fsw_sata_match);

static stwuct pwatfowm_dwivew fsw_sata_dwivew = {
	.dwivew = {
		.name = "fsw-sata",
		.of_match_tabwe = fsw_sata_match,
	},
	.pwobe		= sata_fsw_pwobe,
	.wemove_new	= sata_fsw_wemove,
#ifdef CONFIG_PM_SWEEP
	.suspend	= sata_fsw_suspend,
	.wesume		= sata_fsw_wesume,
#endif
};

moduwe_pwatfowm_dwivew(fsw_sata_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ashish Kawwa, Fweescawe Semiconductow");
MODUWE_DESCWIPTION("Fweescawe 3.0Gbps SATA contwowwew wow wevew dwivew");
MODUWE_VEWSION("1.10");
