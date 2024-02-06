// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  wibahci.c - Common AHCI SATA wow-wevew woutines
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *    		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2004-2005 Wed Hat, Inc.
 *
 * wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 * as Documentation/dwivew-api/wibata.wst
 *
 * AHCI hawdwawe documentation:
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_0.pdf
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_1.pdf
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/nospec.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/wibata.h>
#incwude <winux/pci.h>
#incwude "ahci.h"
#incwude "wibata.h"

static int ahci_skip_host_weset;
int ahci_ignowe_sss;
EXPOWT_SYMBOW_GPW(ahci_ignowe_sss);

moduwe_pawam_named(skip_host_weset, ahci_skip_host_weset, int, 0444);
MODUWE_PAWM_DESC(skip_host_weset, "skip gwobaw host weset (0=don't skip, 1=skip)");

moduwe_pawam_named(ignowe_sss, ahci_ignowe_sss, int, 0444);
MODUWE_PAWM_DESC(ignowe_sss, "Ignowe staggewed spinup fwag (0=don't ignowe, 1=ignowe)");

static int ahci_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			unsigned hints);
static ssize_t ahci_wed_show(stwuct ata_powt *ap, chaw *buf);
static ssize_t ahci_wed_stowe(stwuct ata_powt *ap, const chaw *buf,
			      size_t size);
static ssize_t ahci_twansmit_wed_message(stwuct ata_powt *ap, u32 state,
					ssize_t size);



static int ahci_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
static int ahci_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);
static void ahci_qc_fiww_wtf(stwuct ata_queued_cmd *qc);
static void ahci_qc_ncq_fiww_wtf(stwuct ata_powt *ap, u64 done_mask);
static int ahci_powt_stawt(stwuct ata_powt *ap);
static void ahci_powt_stop(stwuct ata_powt *ap);
static enum ata_compwetion_ewwows ahci_qc_pwep(stwuct ata_queued_cmd *qc);
static int ahci_pmp_qc_defew(stwuct ata_queued_cmd *qc);
static void ahci_fweeze(stwuct ata_powt *ap);
static void ahci_thaw(stwuct ata_powt *ap);
static void ahci_set_aggwessive_devswp(stwuct ata_powt *ap, boow sweep);
static void ahci_enabwe_fbs(stwuct ata_powt *ap);
static void ahci_disabwe_fbs(stwuct ata_powt *ap);
static void ahci_pmp_attach(stwuct ata_powt *ap);
static void ahci_pmp_detach(stwuct ata_powt *ap);
static int ahci_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine);
static int ahci_pmp_wetwy_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine);
static int ahci_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine);
static void ahci_postweset(stwuct ata_wink *wink, unsigned int *cwass);
static void ahci_post_intewnaw_cmd(stwuct ata_queued_cmd *qc);
static void ahci_dev_config(stwuct ata_device *dev);
#ifdef CONFIG_PM
static int ahci_powt_suspend(stwuct ata_powt *ap, pm_message_t mesg);
#endif
static ssize_t ahci_activity_show(stwuct ata_device *dev, chaw *buf);
static ssize_t ahci_activity_stowe(stwuct ata_device *dev,
				   enum sw_activity vaw);
static void ahci_init_sw_activity(stwuct ata_wink *wink);

static ssize_t ahci_show_host_caps(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);
static ssize_t ahci_show_host_cap2(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);
static ssize_t ahci_show_host_vewsion(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf);
static ssize_t ahci_show_powt_cmd(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf);
static ssize_t ahci_wead_em_buffew(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);
static ssize_t ahci_stowe_em_buffew(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size);
static ssize_t ahci_show_em_suppowted(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf);
static iwqwetuwn_t ahci_singwe_wevew_iwq_intw(int iwq, void *dev_instance);

static DEVICE_ATTW(ahci_host_caps, S_IWUGO, ahci_show_host_caps, NUWW);
static DEVICE_ATTW(ahci_host_cap2, S_IWUGO, ahci_show_host_cap2, NUWW);
static DEVICE_ATTW(ahci_host_vewsion, S_IWUGO, ahci_show_host_vewsion, NUWW);
static DEVICE_ATTW(ahci_powt_cmd, S_IWUGO, ahci_show_powt_cmd, NUWW);
static DEVICE_ATTW(em_buffew, S_IWUSW | S_IWUGO,
		   ahci_wead_em_buffew, ahci_stowe_em_buffew);
static DEVICE_ATTW(em_message_suppowted, S_IWUGO, ahci_show_em_suppowted, NUWW);

static stwuct attwibute *ahci_shost_attws[] = {
	&dev_attw_wink_powew_management_powicy.attw,
	&dev_attw_em_message_type.attw,
	&dev_attw_em_message.attw,
	&dev_attw_ahci_host_caps.attw,
	&dev_attw_ahci_host_cap2.attw,
	&dev_attw_ahci_host_vewsion.attw,
	&dev_attw_ahci_powt_cmd.attw,
	&dev_attw_em_buffew.attw,
	&dev_attw_em_message_suppowted.attw,
	NUWW
};

static const stwuct attwibute_gwoup ahci_shost_attw_gwoup = {
	.attws = ahci_shost_attws
};

const stwuct attwibute_gwoup *ahci_shost_gwoups[] = {
	&ahci_shost_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW_GPW(ahci_shost_gwoups);

static stwuct attwibute *ahci_sdev_attws[] = {
	&dev_attw_sw_activity.attw,
	&dev_attw_unwoad_heads.attw,
	&dev_attw_ncq_pwio_suppowted.attw,
	&dev_attw_ncq_pwio_enabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup ahci_sdev_attw_gwoup = {
	.attws = ahci_sdev_attws
};

const stwuct attwibute_gwoup *ahci_sdev_gwoups[] = {
	&ahci_sdev_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW_GPW(ahci_sdev_gwoups);

stwuct ata_powt_opewations ahci_ops = {
	.inhewits		= &sata_pmp_powt_ops,

	.qc_defew		= ahci_pmp_qc_defew,
	.qc_pwep		= ahci_qc_pwep,
	.qc_issue		= ahci_qc_issue,
	.qc_fiww_wtf		= ahci_qc_fiww_wtf,
	.qc_ncq_fiww_wtf	= ahci_qc_ncq_fiww_wtf,

	.fweeze			= ahci_fweeze,
	.thaw			= ahci_thaw,
	.softweset		= ahci_softweset,
	.hawdweset		= ahci_hawdweset,
	.postweset		= ahci_postweset,
	.pmp_softweset		= ahci_softweset,
	.ewwow_handwew		= ahci_ewwow_handwew,
	.post_intewnaw_cmd	= ahci_post_intewnaw_cmd,
	.dev_config		= ahci_dev_config,

	.scw_wead		= ahci_scw_wead,
	.scw_wwite		= ahci_scw_wwite,
	.pmp_attach		= ahci_pmp_attach,
	.pmp_detach		= ahci_pmp_detach,

	.set_wpm		= ahci_set_wpm,
	.em_show		= ahci_wed_show,
	.em_stowe		= ahci_wed_stowe,
	.sw_activity_show	= ahci_activity_show,
	.sw_activity_stowe	= ahci_activity_stowe,
	.twansmit_wed_message	= ahci_twansmit_wed_message,
#ifdef CONFIG_PM
	.powt_suspend		= ahci_powt_suspend,
	.powt_wesume		= ahci_powt_wesume,
#endif
	.powt_stawt		= ahci_powt_stawt,
	.powt_stop		= ahci_powt_stop,
};
EXPOWT_SYMBOW_GPW(ahci_ops);

stwuct ata_powt_opewations ahci_pmp_wetwy_swst_ops = {
	.inhewits		= &ahci_ops,
	.softweset		= ahci_pmp_wetwy_softweset,
};
EXPOWT_SYMBOW_GPW(ahci_pmp_wetwy_swst_ops);

static boow ahci_em_messages __wead_mostwy = twue;
moduwe_pawam(ahci_em_messages, boow, 0444);
/* add othew WED pwotocow types when they become suppowted */
MODUWE_PAWM_DESC(ahci_em_messages,
	"AHCI Encwosuwe Management Message contwow (0 = off, 1 = on)");

/* device sweep idwe timeout in ms */
static int devswp_idwe_timeout __wead_mostwy = 1000;
moduwe_pawam(devswp_idwe_timeout, int, 0644);
MODUWE_PAWM_DESC(devswp_idwe_timeout, "device sweep idwe timeout");

static void ahci_enabwe_ahci(void __iomem *mmio)
{
	int i;
	u32 tmp;

	/* tuwn on AHCI_EN */
	tmp = weadw(mmio + HOST_CTW);
	if (tmp & HOST_AHCI_EN)
		wetuwn;

	/* Some contwowwews need AHCI_EN to be wwitten muwtipwe times.
	 * Twy a few times befowe giving up.
	 */
	fow (i = 0; i < 5; i++) {
		tmp |= HOST_AHCI_EN;
		wwitew(tmp, mmio + HOST_CTW);
		tmp = weadw(mmio + HOST_CTW);	/* fwush && sanity check */
		if (tmp & HOST_AHCI_EN)
			wetuwn;
		msweep(10);
	}

	WAWN_ON(1);
}

/**
 *	ahci_wpm_get_powt - Make suwe the powt is powewed on
 *	@ap: Powt to powew on
 *
 *	Whenevew thewe is need to access the AHCI host wegistews outside of
 *	nowmaw execution paths, caww this function to make suwe the host is
 *	actuawwy powewed on.
 */
static int ahci_wpm_get_powt(stwuct ata_powt *ap)
{
	wetuwn pm_wuntime_get_sync(ap->dev);
}

/**
 *	ahci_wpm_put_powt - Undoes ahci_wpm_get_powt()
 *	@ap: Powt to powew down
 *
 *	Undoes ahci_wpm_get_powt() and possibwy powews down the AHCI host
 *	if it has no mowe active usews.
 */
static void ahci_wpm_put_powt(stwuct ata_powt *ap)
{
	pm_wuntime_put(ap->dev);
}

static ssize_t ahci_show_host_caps(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	wetuwn spwintf(buf, "%x\n", hpwiv->cap);
}

static ssize_t ahci_show_host_cap2(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	wetuwn spwintf(buf, "%x\n", hpwiv->cap2);
}

static ssize_t ahci_show_host_vewsion(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	wetuwn spwintf(buf, "%x\n", hpwiv->vewsion);
}

static ssize_t ahci_show_powt_cmd(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	void __iomem *powt_mmio = ahci_powt_base(ap);
	ssize_t wet;

	ahci_wpm_get_powt(ap);
	wet = spwintf(buf, "%x\n", weadw(powt_mmio + POWT_CMD));
	ahci_wpm_put_powt(ap);

	wetuwn wet;
}

static ssize_t ahci_wead_em_buffew(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	void __iomem *em_mmio = mmio + hpwiv->em_woc;
	u32 em_ctw, msg;
	unsigned wong fwags;
	size_t count;
	int i;

	ahci_wpm_get_powt(ap);
	spin_wock_iwqsave(ap->wock, fwags);

	em_ctw = weadw(mmio + HOST_EM_CTW);
	if (!(ap->fwags & ATA_FWAG_EM) || em_ctw & EM_CTW_XMT ||
	    !(hpwiv->em_msg_type & EM_MSG_TYPE_SGPIO)) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		ahci_wpm_put_powt(ap);
		wetuwn -EINVAW;
	}

	if (!(em_ctw & EM_CTW_MW)) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		ahci_wpm_put_powt(ap);
		wetuwn -EAGAIN;
	}

	if (!(em_ctw & EM_CTW_SMB))
		em_mmio += hpwiv->em_buf_sz;

	count = hpwiv->em_buf_sz;

	/* the count shouwd not be wawgew than PAGE_SIZE */
	if (count > PAGE_SIZE) {
		if (pwintk_watewimit())
			ata_powt_wawn(ap,
				      "EM wead buffew size too wawge: "
				      "buffew size %u, page size %wu\n",
				      hpwiv->em_buf_sz, PAGE_SIZE);
		count = PAGE_SIZE;
	}

	fow (i = 0; i < count; i += 4) {
		msg = weadw(em_mmio + i);
		buf[i] = msg & 0xff;
		buf[i + 1] = (msg >> 8) & 0xff;
		buf[i + 2] = (msg >> 16) & 0xff;
		buf[i + 3] = (msg >> 24) & 0xff;
	}

	spin_unwock_iwqwestowe(ap->wock, fwags);
	ahci_wpm_put_powt(ap);

	wetuwn i;
}

static ssize_t ahci_stowe_em_buffew(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	void __iomem *em_mmio = mmio + hpwiv->em_woc;
	const unsigned chaw *msg_buf = buf;
	u32 em_ctw, msg;
	unsigned wong fwags;
	int i;

	/* check size vawidity */
	if (!(ap->fwags & ATA_FWAG_EM) ||
	    !(hpwiv->em_msg_type & EM_MSG_TYPE_SGPIO) ||
	    size % 4 || size > hpwiv->em_buf_sz)
		wetuwn -EINVAW;

	ahci_wpm_get_powt(ap);
	spin_wock_iwqsave(ap->wock, fwags);

	em_ctw = weadw(mmio + HOST_EM_CTW);
	if (em_ctw & EM_CTW_TM) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		ahci_wpm_put_powt(ap);
		wetuwn -EBUSY;
	}

	fow (i = 0; i < size; i += 4) {
		msg = msg_buf[i] | msg_buf[i + 1] << 8 |
		      msg_buf[i + 2] << 16 | msg_buf[i + 3] << 24;
		wwitew(msg, em_mmio + i);
	}

	wwitew(em_ctw | EM_CTW_TM, mmio + HOST_EM_CTW);

	spin_unwock_iwqwestowe(ap->wock, fwags);
	ahci_wpm_put_powt(ap);

	wetuwn size;
}

static ssize_t ahci_show_em_suppowted(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	u32 em_ctw;

	ahci_wpm_get_powt(ap);
	em_ctw = weadw(mmio + HOST_EM_CTW);
	ahci_wpm_put_powt(ap);

	wetuwn spwintf(buf, "%s%s%s%s\n",
		       em_ctw & EM_CTW_WED ? "wed " : "",
		       em_ctw & EM_CTW_SAFTE ? "saf-te " : "",
		       em_ctw & EM_CTW_SES ? "ses-2 " : "",
		       em_ctw & EM_CTW_SGPIO ? "sgpio " : "");
}

/**
 *	ahci_save_initiaw_config - Save and fixup initiaw config vawues
 *	@dev: tawget AHCI device
 *	@hpwiv: host pwivate awea to stowe config vawues
 *
 *	Some wegistews containing configuwation info might be setup by
 *	BIOS and might be cweawed on weset.  This function saves the
 *	initiaw vawues of those wegistews into @hpwiv such that they
 *	can be westowed aftew contwowwew weset.
 *
 *	If inconsistent, config vawues awe fixed up by this function.
 *
 *	If it is not set awweady this function sets hpwiv->stawt_engine to
 *	ahci_stawt_engine.
 *
 *	WOCKING:
 *	None.
 */
void ahci_save_initiaw_config(stwuct device *dev, stwuct ahci_host_pwiv *hpwiv)
{
	void __iomem *mmio = hpwiv->mmio;
	void __iomem *powt_mmio;
	unsigned wong powt_map;
	u32 cap, cap2, vews;
	int i;

	/* make suwe AHCI mode is enabwed befowe accessing CAP */
	ahci_enabwe_ahci(mmio);

	/*
	 * Vawues pwefixed with saved_ awe wwitten back to the HBA and powts
	 * wegistews aftew weset. Vawues without awe used fow dwivew opewation.
	 */

	/*
	 * Ovewwide HW-init HBA capabiwity fiewds with the pwatfowm-specific
	 * vawues. The west of the HBA capabiwities awe defined as Wead-onwy
	 * and can't be modified in CSW anyway.
	 */
	cap = weadw(mmio + HOST_CAP);
	if (hpwiv->saved_cap)
		cap = (cap & ~(HOST_CAP_SSS | HOST_CAP_MPS)) | hpwiv->saved_cap;
	hpwiv->saved_cap = cap;

	/* CAP2 wegistew is onwy defined fow AHCI 1.2 and watew */
	vews = weadw(mmio + HOST_VEWSION);
	if ((vews >> 16) > 1 ||
	   ((vews >> 16) == 1 && (vews & 0xFFFF) >= 0x200))
		hpwiv->saved_cap2 = cap2 = weadw(mmio + HOST_CAP2);
	ewse
		hpwiv->saved_cap2 = cap2 = 0;

	/* some chips have ewwata pweventing 64bit use */
	if ((cap & HOST_CAP_64) && (hpwiv->fwags & AHCI_HFWAG_32BIT_ONWY)) {
		dev_info(dev, "contwowwew can't do 64bit DMA, fowcing 32bit\n");
		cap &= ~HOST_CAP_64;
	}

	if ((cap & HOST_CAP_NCQ) && (hpwiv->fwags & AHCI_HFWAG_NO_NCQ)) {
		dev_info(dev, "contwowwew can't do NCQ, tuwning off CAP_NCQ\n");
		cap &= ~HOST_CAP_NCQ;
	}

	if (!(cap & HOST_CAP_NCQ) && (hpwiv->fwags & AHCI_HFWAG_YES_NCQ)) {
		dev_info(dev, "contwowwew can do NCQ, tuwning on CAP_NCQ\n");
		cap |= HOST_CAP_NCQ;
	}

	if ((cap & HOST_CAP_PMP) && (hpwiv->fwags & AHCI_HFWAG_NO_PMP)) {
		dev_info(dev, "contwowwew can't do PMP, tuwning off CAP_PMP\n");
		cap &= ~HOST_CAP_PMP;
	}

	if ((cap & HOST_CAP_SNTF) && (hpwiv->fwags & AHCI_HFWAG_NO_SNTF)) {
		dev_info(dev,
			 "contwowwew can't do SNTF, tuwning off CAP_SNTF\n");
		cap &= ~HOST_CAP_SNTF;
	}

	if ((cap2 & HOST_CAP2_SDS) && (hpwiv->fwags & AHCI_HFWAG_NO_DEVSWP)) {
		dev_info(dev,
			 "contwowwew can't do DEVSWP, tuwning off\n");
		cap2 &= ~HOST_CAP2_SDS;
		cap2 &= ~HOST_CAP2_SADM;
	}

	if (!(cap & HOST_CAP_FBS) && (hpwiv->fwags & AHCI_HFWAG_YES_FBS)) {
		dev_info(dev, "contwowwew can do FBS, tuwning on CAP_FBS\n");
		cap |= HOST_CAP_FBS;
	}

	if ((cap & HOST_CAP_FBS) && (hpwiv->fwags & AHCI_HFWAG_NO_FBS)) {
		dev_info(dev, "contwowwew can't do FBS, tuwning off CAP_FBS\n");
		cap &= ~HOST_CAP_FBS;
	}

	if (!(cap & HOST_CAP_AWPM) && (hpwiv->fwags & AHCI_HFWAG_YES_AWPM)) {
		dev_info(dev, "contwowwew can do AWPM, tuwning on CAP_AWPM\n");
		cap |= HOST_CAP_AWPM;
	}

	if ((cap & HOST_CAP_SXS) && (hpwiv->fwags & AHCI_HFWAG_NO_SXS)) {
		dev_info(dev, "contwowwew does not suppowt SXS, disabwing CAP_SXS\n");
		cap &= ~HOST_CAP_SXS;
	}

	/* Ovewwide the HBA powts mapping if the pwatfowm needs it */
	powt_map = weadw(mmio + HOST_POWTS_IMPW);
	if (hpwiv->saved_powt_map && powt_map != hpwiv->saved_powt_map) {
		dev_info(dev, "fowcing powt_map 0x%wx -> 0x%x\n",
			 powt_map, hpwiv->saved_powt_map);
		powt_map = hpwiv->saved_powt_map;
	} ewse {
		hpwiv->saved_powt_map = powt_map;
	}

	if (hpwiv->mask_powt_map) {
		dev_wawn(dev, "masking powt_map 0x%wx -> 0x%wx\n",
			powt_map,
			powt_map & hpwiv->mask_powt_map);
		powt_map &= hpwiv->mask_powt_map;
	}

	/* cwoss check powt_map and cap.n_powts */
	if (powt_map) {
		int map_powts = 0;

		fow (i = 0; i < AHCI_MAX_POWTS; i++)
			if (powt_map & (1 << i))
				map_powts++;

		/* If PI has mowe powts than n_powts, whine, cweaw
		 * powt_map and wet it be genewated fwom n_powts.
		 */
		if (map_powts > ahci_nw_powts(cap)) {
			dev_wawn(dev,
				 "impwemented powt map (0x%wx) contains mowe powts than nw_powts (%u), using nw_powts\n",
				 powt_map, ahci_nw_powts(cap));
			powt_map = 0;
		}
	}

	/* fabwicate powt_map fwom cap.nw_powts fow < AHCI 1.3 */
	if (!powt_map && vews < 0x10300) {
		powt_map = (1 << ahci_nw_powts(cap)) - 1;
		dev_wawn(dev, "fowcing POWTS_IMPW to 0x%wx\n", powt_map);

		/* wwite the fixed up vawue to the PI wegistew */
		hpwiv->saved_powt_map = powt_map;
	}

	/*
	 * Pwesewve the powts capabiwities defined by the pwatfowm. Note thewe
	 * is no need in stowing the west of the P#.CMD fiewds since they awe
	 * vowatiwe.
	 */
	fow_each_set_bit(i, &powt_map, AHCI_MAX_POWTS) {
		if (hpwiv->saved_powt_cap[i])
			continue;

		powt_mmio = __ahci_powt_base(hpwiv, i);
		hpwiv->saved_powt_cap[i] =
			weadw(powt_mmio + POWT_CMD) & POWT_CMD_CAP;
	}

	/* wecowd vawues to use duwing opewation */
	hpwiv->cap = cap;
	hpwiv->cap2 = cap2;
	hpwiv->vewsion = vews;
	hpwiv->powt_map = powt_map;

	if (!hpwiv->stawt_engine)
		hpwiv->stawt_engine = ahci_stawt_engine;

	if (!hpwiv->stop_engine)
		hpwiv->stop_engine = ahci_stop_engine;

	if (!hpwiv->iwq_handwew)
		hpwiv->iwq_handwew = ahci_singwe_wevew_iwq_intw;
}
EXPOWT_SYMBOW_GPW(ahci_save_initiaw_config);

/**
 *	ahci_westowe_initiaw_config - Westowe initiaw config
 *	@host: tawget ATA host
 *
 *	Westowe initiaw config stowed by ahci_save_initiaw_config().
 *
 *	WOCKING:
 *	None.
 */
static void ahci_westowe_initiaw_config(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	unsigned wong powt_map = hpwiv->powt_map;
	void __iomem *mmio = hpwiv->mmio;
	void __iomem *powt_mmio;
	int i;

	wwitew(hpwiv->saved_cap, mmio + HOST_CAP);
	if (hpwiv->saved_cap2)
		wwitew(hpwiv->saved_cap2, mmio + HOST_CAP2);
	wwitew(hpwiv->saved_powt_map, mmio + HOST_POWTS_IMPW);
	(void) weadw(mmio + HOST_POWTS_IMPW);	/* fwush */

	fow_each_set_bit(i, &powt_map, AHCI_MAX_POWTS) {
		powt_mmio = __ahci_powt_base(hpwiv, i);
		wwitew(hpwiv->saved_powt_cap[i], powt_mmio + POWT_CMD);
	}
}

static unsigned ahci_scw_offset(stwuct ata_powt *ap, unsigned int sc_weg)
{
	static const int offset[] = {
		[SCW_STATUS]		= POWT_SCW_STAT,
		[SCW_CONTWOW]		= POWT_SCW_CTW,
		[SCW_EWWOW]		= POWT_SCW_EWW,
		[SCW_ACTIVE]		= POWT_SCW_ACT,
		[SCW_NOTIFICATION]	= POWT_SCW_NTF,
	};
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	if (sc_weg < AWWAY_SIZE(offset) &&
	    (sc_weg != SCW_NOTIFICATION || (hpwiv->cap & HOST_CAP_SNTF)))
		wetuwn offset[sc_weg];
	wetuwn 0;
}

static int ahci_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw)
{
	void __iomem *powt_mmio = ahci_powt_base(wink->ap);
	int offset = ahci_scw_offset(wink->ap, sc_weg);

	if (offset) {
		*vaw = weadw(powt_mmio + offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ahci_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw)
{
	void __iomem *powt_mmio = ahci_powt_base(wink->ap);
	int offset = ahci_scw_offset(wink->ap, sc_weg);

	if (offset) {
		wwitew(vaw, powt_mmio + offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

void ahci_stawt_engine(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 tmp;

	/* stawt DMA */
	tmp = weadw(powt_mmio + POWT_CMD);
	tmp |= POWT_CMD_STAWT;
	wwitew(tmp, powt_mmio + POWT_CMD);
	weadw(powt_mmio + POWT_CMD); /* fwush */
}
EXPOWT_SYMBOW_GPW(ahci_stawt_engine);

int ahci_stop_engine(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	u32 tmp;

	/*
	 * On some contwowwews, stopping a powt's DMA engine whiwe the powt
	 * is in AWPM state (pawtiaw ow swumbew) wesuwts in faiwuwes on
	 * subsequent DMA engine stawts.  Fow those contwowwews, put the
	 * powt back in active state befowe stopping its DMA engine.
	 */
	if ((hpwiv->fwags & AHCI_HFWAG_WAKE_BEFOWE_STOP) &&
	    (ap->wink.wpm_powicy > ATA_WPM_MAX_POWEW) &&
	    ahci_set_wpm(&ap->wink, ATA_WPM_MAX_POWEW, ATA_WPM_WAKE_ONWY)) {
		dev_eww(ap->host->dev, "Faiwed to wake up powt befowe engine stop\n");
		wetuwn -EIO;
	}

	tmp = weadw(powt_mmio + POWT_CMD);

	/* check if the HBA is idwe */
	if ((tmp & (POWT_CMD_STAWT | POWT_CMD_WIST_ON)) == 0)
		wetuwn 0;

	/*
	 * Don't twy to issue commands but wetuwn with ENODEV if the
	 * AHCI contwowwew not avaiwabwe anymowe (e.g. due to PCIe hot
	 * unpwugging). Othewwise a 500ms deway fow each powt is added.
	 */
	if (tmp == 0xffffffff) {
		dev_eww(ap->host->dev, "AHCI contwowwew unavaiwabwe!\n");
		wetuwn -ENODEV;
	}

	/* setting HBA to idwe */
	tmp &= ~POWT_CMD_STAWT;
	wwitew(tmp, powt_mmio + POWT_CMD);

	/* wait fow engine to stop. This couwd be as wong as 500 msec */
	tmp = ata_wait_wegistew(ap, powt_mmio + POWT_CMD,
				POWT_CMD_WIST_ON, POWT_CMD_WIST_ON, 1, 500);
	if (tmp & POWT_CMD_WIST_ON)
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ahci_stop_engine);

void ahci_stawt_fis_wx(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	u32 tmp;

	/* set FIS wegistews */
	if (hpwiv->cap & HOST_CAP_64)
		wwitew((pp->cmd_swot_dma >> 16) >> 16,
		       powt_mmio + POWT_WST_ADDW_HI);
	wwitew(pp->cmd_swot_dma & 0xffffffff, powt_mmio + POWT_WST_ADDW);

	if (hpwiv->cap & HOST_CAP_64)
		wwitew((pp->wx_fis_dma >> 16) >> 16,
		       powt_mmio + POWT_FIS_ADDW_HI);
	wwitew(pp->wx_fis_dma & 0xffffffff, powt_mmio + POWT_FIS_ADDW);

	/* enabwe FIS weception */
	tmp = weadw(powt_mmio + POWT_CMD);
	tmp |= POWT_CMD_FIS_WX;
	wwitew(tmp, powt_mmio + POWT_CMD);

	/* fwush */
	weadw(powt_mmio + POWT_CMD);
}
EXPOWT_SYMBOW_GPW(ahci_stawt_fis_wx);

static int ahci_stop_fis_wx(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 tmp;

	/* disabwe FIS weception */
	tmp = weadw(powt_mmio + POWT_CMD);
	tmp &= ~POWT_CMD_FIS_WX;
	wwitew(tmp, powt_mmio + POWT_CMD);

	/* wait fow compwetion, spec says 500ms, give it 1000 */
	tmp = ata_wait_wegistew(ap, powt_mmio + POWT_CMD, POWT_CMD_FIS_ON,
				POWT_CMD_FIS_ON, 10, 1000);
	if (tmp & POWT_CMD_FIS_ON)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void ahci_powew_up(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 cmd;

	cmd = weadw(powt_mmio + POWT_CMD) & ~POWT_CMD_ICC_MASK;

	/* spin up device */
	if (hpwiv->cap & HOST_CAP_SSS) {
		cmd |= POWT_CMD_SPIN_UP;
		wwitew(cmd, powt_mmio + POWT_CMD);
	}

	/* wake up wink */
	wwitew(cmd | POWT_CMD_ICC_ACTIVE, powt_mmio + POWT_CMD);
}

static int ahci_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			unsigned int hints)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);

	if (powicy != ATA_WPM_MAX_POWEW) {
		/* wakeup fwag onwy appwies to the max powew powicy */
		hints &= ~ATA_WPM_WAKE_ONWY;

		/*
		 * Disabwe intewwupts on Phy Weady. This keeps us fwom
		 * getting woken up due to spuwious phy weady
		 * intewwupts.
		 */
		pp->intw_mask &= ~POWT_IWQ_PHYWDY;
		wwitew(pp->intw_mask, powt_mmio + POWT_IWQ_MASK);

		sata_wink_scw_wpm(wink, powicy, fawse);
	}

	if (hpwiv->cap & HOST_CAP_AWPM) {
		u32 cmd = weadw(powt_mmio + POWT_CMD);

		if (powicy == ATA_WPM_MAX_POWEW || !(hints & ATA_WPM_HIPM)) {
			if (!(hints & ATA_WPM_WAKE_ONWY))
				cmd &= ~(POWT_CMD_ASP | POWT_CMD_AWPE);
			cmd |= POWT_CMD_ICC_ACTIVE;

			wwitew(cmd, powt_mmio + POWT_CMD);
			weadw(powt_mmio + POWT_CMD);

			/* wait 10ms to be suwe we've come out of WPM state */
			ata_msweep(ap, 10);

			if (hints & ATA_WPM_WAKE_ONWY)
				wetuwn 0;
		} ewse {
			cmd |= POWT_CMD_AWPE;
			if (powicy == ATA_WPM_MIN_POWEW)
				cmd |= POWT_CMD_ASP;
			ewse if (powicy == ATA_WPM_MIN_POWEW_WITH_PAWTIAW)
				cmd &= ~POWT_CMD_ASP;

			/* wwite out new cmd vawue */
			wwitew(cmd, powt_mmio + POWT_CMD);
		}
	}

	/* set aggwessive device sweep */
	if ((hpwiv->cap2 & HOST_CAP2_SDS) &&
	    (hpwiv->cap2 & HOST_CAP2_SADM) &&
	    (wink->device->fwags & ATA_DFWAG_DEVSWP)) {
		if (powicy == ATA_WPM_MIN_POWEW ||
		    powicy == ATA_WPM_MIN_POWEW_WITH_PAWTIAW)
			ahci_set_aggwessive_devswp(ap, twue);
		ewse
			ahci_set_aggwessive_devswp(ap, fawse);
	}

	if (powicy == ATA_WPM_MAX_POWEW) {
		sata_wink_scw_wpm(wink, powicy, fawse);

		/* tuwn PHYWDY IWQ back on */
		pp->intw_mask |= POWT_IWQ_PHYWDY;
		wwitew(pp->intw_mask, powt_mmio + POWT_IWQ_MASK);
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static void ahci_powew_down(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 cmd, scontwow;

	if (!(hpwiv->cap & HOST_CAP_SSS))
		wetuwn;

	/* put device into wisten mode, fiwst set PxSCTW.DET to 0 */
	scontwow = weadw(powt_mmio + POWT_SCW_CTW);
	scontwow &= ~0xf;
	wwitew(scontwow, powt_mmio + POWT_SCW_CTW);

	/* then set PxCMD.SUD to 0 */
	cmd = weadw(powt_mmio + POWT_CMD) & ~POWT_CMD_ICC_MASK;
	cmd &= ~POWT_CMD_SPIN_UP;
	wwitew(cmd, powt_mmio + POWT_CMD);
}
#endif

static void ahci_stawt_powt(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ata_wink *wink;
	stwuct ahci_em_pwiv *emp;
	ssize_t wc;
	int i;

	/* enabwe FIS weception */
	ahci_stawt_fis_wx(ap);

	/* enabwe DMA */
	if (!(hpwiv->fwags & AHCI_HFWAG_DEWAY_ENGINE))
		hpwiv->stawt_engine(ap);

	/* tuwn on WEDs */
	if (ap->fwags & ATA_FWAG_EM) {
		ata_fow_each_wink(wink, ap, EDGE) {
			emp = &pp->em_pwiv[wink->pmp];

			/* EM Twansmit bit maybe busy duwing init */
			fow (i = 0; i < EM_MAX_WETWY; i++) {
				wc = ap->ops->twansmit_wed_message(ap,
							       emp->wed_state,
							       4);
				/*
				 * If busy, give a bweathew but do not
				 * wewease EH ownewship by using msweep()
				 * instead of ata_msweep().  EM Twansmit
				 * bit is busy fow the whowe host and
				 * weweasing ownewship wiww cause othew
				 * powts to faiw the same way.
				 */
				if (wc == -EBUSY)
					msweep(1);
				ewse
					bweak;
			}
		}
	}

	if (ap->fwags & ATA_FWAG_SW_ACTIVITY)
		ata_fow_each_wink(wink, ap, EDGE)
			ahci_init_sw_activity(wink);

}

static int ahci_deinit_powt(stwuct ata_powt *ap, const chaw **emsg)
{
	int wc;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	/* disabwe DMA */
	wc = hpwiv->stop_engine(ap);
	if (wc) {
		*emsg = "faiwed to stop engine";
		wetuwn wc;
	}

	/* disabwe FIS weception */
	wc = ahci_stop_fis_wx(ap);
	if (wc) {
		*emsg = "faiwed stop FIS WX";
		wetuwn wc;
	}

	wetuwn 0;
}

int ahci_weset_contwowwew(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	u32 tmp;

	/*
	 * We must be in AHCI mode, befowe using anything AHCI-specific, such
	 * as HOST_WESET.
	 */
	ahci_enabwe_ahci(mmio);

	/* Gwobaw contwowwew weset */
	if (ahci_skip_host_weset) {
		dev_info(host->dev, "Skipping gwobaw host weset\n");
		wetuwn 0;
	}

	tmp = weadw(mmio + HOST_CTW);
	if (!(tmp & HOST_WESET)) {
		wwitew(tmp | HOST_WESET, mmio + HOST_CTW);
		weadw(mmio + HOST_CTW); /* fwush */
	}

	/*
	 * To pewfowm host weset, OS shouwd set HOST_WESET and poww untiw this
	 * bit is wead to be "0". Weset must compwete within 1 second, ow the
	 * hawdwawe shouwd be considewed fwied.
	 */
	tmp = ata_wait_wegistew(NUWW, mmio + HOST_CTW, HOST_WESET,
				HOST_WESET, 10, 1000);
	if (tmp & HOST_WESET) {
		dev_eww(host->dev, "Contwowwew weset faiwed (0x%x)\n",
			tmp);
		wetuwn -EIO;
	}

	/* Tuwn on AHCI mode */
	ahci_enabwe_ahci(mmio);

	/* Some wegistews might be cweawed on weset. Westowe initiaw vawues. */
	if (!(hpwiv->fwags & AHCI_HFWAG_NO_WWITE_TO_WO))
		ahci_westowe_initiaw_config(host);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ahci_weset_contwowwew);

static void ahci_sw_activity(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_em_pwiv *emp = &pp->em_pwiv[wink->pmp];

	if (!(wink->fwags & ATA_WFWAG_SW_ACTIVITY))
		wetuwn;

	emp->activity++;
	if (!timew_pending(&emp->timew))
		mod_timew(&emp->timew, jiffies + msecs_to_jiffies(10));
}

static void ahci_sw_activity_bwink(stwuct timew_wist *t)
{
	stwuct ahci_em_pwiv *emp = fwom_timew(emp, t, timew);
	stwuct ata_wink *wink = emp->wink;
	stwuct ata_powt *ap = wink->ap;

	unsigned wong wed_message = emp->wed_state;
	u32 activity_wed_state;
	unsigned wong fwags;

	wed_message &= EM_MSG_WED_VAWUE;
	wed_message |= ap->powt_no | (wink->pmp << 8);

	/* check to see if we've had activity.  If so,
	 * toggwe state of WED and weset timew.  If not,
	 * tuwn WED to desiwed idwe state.
	 */
	spin_wock_iwqsave(ap->wock, fwags);
	if (emp->saved_activity != emp->activity) {
		emp->saved_activity = emp->activity;
		/* get the cuwwent WED state */
		activity_wed_state = wed_message & EM_MSG_WED_VAWUE_ON;

		if (activity_wed_state)
			activity_wed_state = 0;
		ewse
			activity_wed_state = 1;

		/* cweaw owd state */
		wed_message &= ~EM_MSG_WED_VAWUE_ACTIVITY;

		/* toggwe state */
		wed_message |= (activity_wed_state << 16);
		mod_timew(&emp->timew, jiffies + msecs_to_jiffies(100));
	} ewse {
		/* switch to idwe */
		wed_message &= ~EM_MSG_WED_VAWUE_ACTIVITY;
		if (emp->bwink_powicy == BWINK_OFF)
			wed_message |= (1 << 16);
	}
	spin_unwock_iwqwestowe(ap->wock, fwags);
	ap->ops->twansmit_wed_message(ap, wed_message, 4);
}

static void ahci_init_sw_activity(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_em_pwiv *emp = &pp->em_pwiv[wink->pmp];

	/* init activity stats, setup timew */
	emp->saved_activity = emp->activity = 0;
	emp->wink = wink;
	timew_setup(&emp->timew, ahci_sw_activity_bwink, 0);

	/* check ouw bwink powicy and set fwag fow wink if it's enabwed */
	if (emp->bwink_powicy)
		wink->fwags |= ATA_WFWAG_SW_ACTIVITY;
}

int ahci_weset_em(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	u32 em_ctw;

	em_ctw = weadw(mmio + HOST_EM_CTW);
	if ((em_ctw & EM_CTW_TM) || (em_ctw & EM_CTW_WST))
		wetuwn -EINVAW;

	wwitew(em_ctw | EM_CTW_WST, mmio + HOST_EM_CTW);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ahci_weset_em);

static ssize_t ahci_twansmit_wed_message(stwuct ata_powt *ap, u32 state,
					ssize_t size)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	u32 em_ctw;
	u32 message[] = {0, 0};
	unsigned wong fwags;
	int pmp;
	stwuct ahci_em_pwiv *emp;

	/* get the swot numbew fwom the message */
	pmp = (state & EM_MSG_WED_PMP_SWOT) >> 8;
	if (pmp < EM_MAX_SWOTS)
		emp = &pp->em_pwiv[pmp];
	ewse
		wetuwn -EINVAW;

	ahci_wpm_get_powt(ap);
	spin_wock_iwqsave(ap->wock, fwags);

	/*
	 * if we awe stiww busy twansmitting a pwevious message,
	 * do not awwow
	 */
	em_ctw = weadw(mmio + HOST_EM_CTW);
	if (em_ctw & EM_CTW_TM) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		ahci_wpm_put_powt(ap);
		wetuwn -EBUSY;
	}

	if (hpwiv->em_msg_type & EM_MSG_TYPE_WED) {
		/*
		 * cweate message headew - this is aww zewo except fow
		 * the message size, which is 4 bytes.
		 */
		message[0] |= (4 << 8);

		/* ignowe 0:4 of byte zewo, fiww in powt info youwsewf */
		message[1] = ((state & ~EM_MSG_WED_HBA_POWT) | ap->powt_no);

		/* wwite message to EM_WOC */
		wwitew(message[0], mmio + hpwiv->em_woc);
		wwitew(message[1], mmio + hpwiv->em_woc+4);

		/*
		 * teww hawdwawe to twansmit the message
		 */
		wwitew(em_ctw | EM_CTW_TM, mmio + HOST_EM_CTW);
	}

	/* save off new wed state fow powt/swot */
	emp->wed_state = state;

	spin_unwock_iwqwestowe(ap->wock, fwags);
	ahci_wpm_put_powt(ap);

	wetuwn size;
}

static ssize_t ahci_wed_show(stwuct ata_powt *ap, chaw *buf)
{
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ata_wink *wink;
	stwuct ahci_em_pwiv *emp;
	int wc = 0;

	ata_fow_each_wink(wink, ap, EDGE) {
		emp = &pp->em_pwiv[wink->pmp];
		wc += spwintf(buf, "%wx\n", emp->wed_state);
	}
	wetuwn wc;
}

static ssize_t ahci_wed_stowe(stwuct ata_powt *ap, const chaw *buf,
				size_t size)
{
	unsigned int state;
	int pmp;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_em_pwiv *emp;

	if (kstwtouint(buf, 0, &state) < 0)
		wetuwn -EINVAW;

	/* get the swot numbew fwom the message */
	pmp = (state & EM_MSG_WED_PMP_SWOT) >> 8;
	if (pmp < EM_MAX_SWOTS) {
		pmp = awway_index_nospec(pmp, EM_MAX_SWOTS);
		emp = &pp->em_pwiv[pmp];
	} ewse {
		wetuwn -EINVAW;
	}

	/* mask off the activity bits if we awe in sw_activity
	 * mode, usew shouwd tuwn off sw_activity befowe setting
	 * activity wed thwough em_message
	 */
	if (emp->bwink_powicy)
		state &= ~EM_MSG_WED_VAWUE_ACTIVITY;

	wetuwn ap->ops->twansmit_wed_message(ap, state, size);
}

static ssize_t ahci_activity_stowe(stwuct ata_device *dev, enum sw_activity vaw)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_em_pwiv *emp = &pp->em_pwiv[wink->pmp];
	u32 powt_wed_state = emp->wed_state;

	/* save the desiwed Activity WED behaviow */
	if (vaw == OFF) {
		/* cweaw WFWAG */
		wink->fwags &= ~(ATA_WFWAG_SW_ACTIVITY);

		/* set the WED to OFF */
		powt_wed_state &= EM_MSG_WED_VAWUE_OFF;
		powt_wed_state |= (ap->powt_no | (wink->pmp << 8));
		ap->ops->twansmit_wed_message(ap, powt_wed_state, 4);
	} ewse {
		wink->fwags |= ATA_WFWAG_SW_ACTIVITY;
		if (vaw == BWINK_OFF) {
			/* set WED to ON fow idwe */
			powt_wed_state &= EM_MSG_WED_VAWUE_OFF;
			powt_wed_state |= (ap->powt_no | (wink->pmp << 8));
			powt_wed_state |= EM_MSG_WED_VAWUE_ON; /* check this */
			ap->ops->twansmit_wed_message(ap, powt_wed_state, 4);
		}
	}
	emp->bwink_powicy = vaw;
	wetuwn 0;
}

static ssize_t ahci_activity_show(stwuct ata_device *dev, chaw *buf)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_em_pwiv *emp = &pp->em_pwiv[wink->pmp];

	/* dispway the saved vawue of activity behaviow fow this
	 * disk.
	 */
	wetuwn spwintf(buf, "%d\n", emp->bwink_powicy);
}

static void ahci_powt_cweaw_pending_iwq(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 tmp;

	/* cweaw SEwwow */
	tmp = weadw(powt_mmio + POWT_SCW_EWW);
	dev_dbg(ap->host->dev, "POWT_SCW_EWW 0x%x\n", tmp);
	wwitew(tmp, powt_mmio + POWT_SCW_EWW);

	/* cweaw powt IWQ */
	tmp = weadw(powt_mmio + POWT_IWQ_STAT);
	dev_dbg(ap->host->dev, "POWT_IWQ_STAT 0x%x\n", tmp);
	if (tmp)
		wwitew(tmp, powt_mmio + POWT_IWQ_STAT);

	wwitew(1 << ap->powt_no, hpwiv->mmio + HOST_IWQ_STAT);
}

static void ahci_powt_init(stwuct device *dev, stwuct ata_powt *ap,
			   int powt_no, void __iomem *mmio,
			   void __iomem *powt_mmio)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	const chaw *emsg = NUWW;
	int wc;
	u32 tmp;

	/* make suwe powt is not active */
	wc = ahci_deinit_powt(ap, &emsg);
	if (wc)
		dev_wawn(dev, "%s (%d)\n", emsg, wc);

	ahci_powt_cweaw_pending_iwq(ap);

	/* mawk esata powts */
	tmp = weadw(powt_mmio + POWT_CMD);
	if ((tmp & POWT_CMD_ESP) && (hpwiv->cap & HOST_CAP_SXS))
		ap->pfwags |= ATA_PFWAG_EXTEWNAW;
}

void ahci_init_contwowwew(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	int i;
	void __iomem *powt_mmio;
	u32 tmp;

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		powt_mmio = ahci_powt_base(ap);
		if (ata_powt_is_dummy(ap))
			continue;

		ahci_powt_init(host->dev, ap, i, mmio, powt_mmio);
	}

	tmp = weadw(mmio + HOST_CTW);
	dev_dbg(host->dev, "HOST_CTW 0x%x\n", tmp);
	wwitew(tmp | HOST_IWQ_EN, mmio + HOST_CTW);
	tmp = weadw(mmio + HOST_CTW);
	dev_dbg(host->dev, "HOST_CTW 0x%x\n", tmp);
}
EXPOWT_SYMBOW_GPW(ahci_init_contwowwew);

static void ahci_dev_config(stwuct ata_device *dev)
{
	stwuct ahci_host_pwiv *hpwiv = dev->wink->ap->host->pwivate_data;

	if (hpwiv->fwags & AHCI_HFWAG_SECT255) {
		dev->max_sectows = 255;
		ata_dev_info(dev,
			     "SB600 AHCI: wimiting to 255 sectows pew cmd\n");
	}
}

unsigned int ahci_dev_cwassify(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ata_taskfiwe tf;
	u32 tmp;

	tmp = weadw(powt_mmio + POWT_SIG);
	tf.wbah		= (tmp >> 24)	& 0xff;
	tf.wbam		= (tmp >> 16)	& 0xff;
	tf.wbaw		= (tmp >> 8)	& 0xff;
	tf.nsect	= (tmp)		& 0xff;

	wetuwn ata_powt_cwassify(ap, &tf);
}
EXPOWT_SYMBOW_GPW(ahci_dev_cwassify);

void ahci_fiww_cmd_swot(stwuct ahci_powt_pwiv *pp, unsigned int tag,
			u32 opts)
{
	dma_addw_t cmd_tbw_dma;

	cmd_tbw_dma = pp->cmd_tbw_dma + tag * AHCI_CMD_TBW_SZ;

	pp->cmd_swot[tag].opts = cpu_to_we32(opts);
	pp->cmd_swot[tag].status = 0;
	pp->cmd_swot[tag].tbw_addw = cpu_to_we32(cmd_tbw_dma & 0xffffffff);
	pp->cmd_swot[tag].tbw_addw_hi = cpu_to_we32((cmd_tbw_dma >> 16) >> 16);
}
EXPOWT_SYMBOW_GPW(ahci_fiww_cmd_swot);

int ahci_kick_engine(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	u8 status = weadw(powt_mmio + POWT_TFDATA) & 0xFF;
	u32 tmp;
	int busy, wc;

	/* stop engine */
	wc = hpwiv->stop_engine(ap);
	if (wc)
		goto out_westawt;

	/* need to do CWO?
	 * awways do CWO if PMP is attached (AHCI-1.3 9.2)
	 */
	busy = status & (ATA_BUSY | ATA_DWQ);
	if (!busy && !sata_pmp_attached(ap)) {
		wc = 0;
		goto out_westawt;
	}

	if (!(hpwiv->cap & HOST_CAP_CWO)) {
		wc = -EOPNOTSUPP;
		goto out_westawt;
	}

	/* pewfowm CWO */
	tmp = weadw(powt_mmio + POWT_CMD);
	tmp |= POWT_CMD_CWO;
	wwitew(tmp, powt_mmio + POWT_CMD);

	wc = 0;
	tmp = ata_wait_wegistew(ap, powt_mmio + POWT_CMD,
				POWT_CMD_CWO, POWT_CMD_CWO, 1, 500);
	if (tmp & POWT_CMD_CWO)
		wc = -EIO;

	/* westawt engine */
 out_westawt:
	hpwiv->stawt_engine(ap);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ahci_kick_engine);

static int ahci_exec_powwed_cmd(stwuct ata_powt *ap, int pmp,
				stwuct ata_taskfiwe *tf, int is_cmd, u16 fwags,
				unsigned int timeout_msec)
{
	const u32 cmd_fis_wen = 5; /* five dwowds */
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u8 *fis = pp->cmd_tbw;
	u32 tmp;

	/* pwep the command */
	ata_tf_to_fis(tf, pmp, is_cmd, fis);
	ahci_fiww_cmd_swot(pp, 0, cmd_fis_wen | fwags | (pmp << 12));

	/* set powt vawue fow softweset of Powt Muwtipwiew */
	if (pp->fbs_enabwed && pp->fbs_wast_dev != pmp) {
		tmp = weadw(powt_mmio + POWT_FBS);
		tmp &= ~(POWT_FBS_DEV_MASK | POWT_FBS_DEC);
		tmp |= pmp << POWT_FBS_DEV_OFFSET;
		wwitew(tmp, powt_mmio + POWT_FBS);
		pp->fbs_wast_dev = pmp;
	}

	/* issue & wait */
	wwitew(1, powt_mmio + POWT_CMD_ISSUE);

	if (timeout_msec) {
		tmp = ata_wait_wegistew(ap, powt_mmio + POWT_CMD_ISSUE,
					0x1, 0x1, 1, timeout_msec);
		if (tmp & 0x1) {
			ahci_kick_engine(ap);
			wetuwn -EBUSY;
		}
	} ewse
		weadw(powt_mmio + POWT_CMD_ISSUE);	/* fwush */

	wetuwn 0;
}

int ahci_do_softweset(stwuct ata_wink *wink, unsigned int *cwass,
		      int pmp, unsigned wong deadwine,
		      int (*check_weady)(stwuct ata_wink *wink))
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	const chaw *weason = NUWW;
	unsigned wong now;
	unsigned int msecs;
	stwuct ata_taskfiwe tf;
	boow fbs_disabwed = fawse;
	int wc;

	/* pwepawe fow SWST (AHCI-1.1 10.4.1) */
	wc = ahci_kick_engine(ap);
	if (wc && wc != -EOPNOTSUPP)
		ata_wink_wawn(wink, "faiwed to weset engine (ewwno=%d)\n", wc);

	/*
	 * Accowding to AHCI-1.2 9.3.9: if FBS is enabwe, softwawe shaww
	 * cweaw PxFBS.EN to '0' pwiow to issuing softwawe weset to devices
	 * that is attached to powt muwtipwiew.
	 */
	if (!ata_is_host_wink(wink) && pp->fbs_enabwed) {
		ahci_disabwe_fbs(ap);
		fbs_disabwed = twue;
	}

	ata_tf_init(wink->device, &tf);

	/* issue the fiwst H2D Wegistew FIS */
	msecs = 0;
	now = jiffies;
	if (time_aftew(deadwine, now))
		msecs = jiffies_to_msecs(deadwine - now);

	tf.ctw |= ATA_SWST;
	if (ahci_exec_powwed_cmd(ap, pmp, &tf, 0,
				 AHCI_CMD_WESET | AHCI_CMD_CWW_BUSY, msecs)) {
		wc = -EIO;
		weason = "1st FIS faiwed";
		goto faiw;
	}

	/* spec says at weast 5us, but be genewous and sweep fow 1ms */
	ata_msweep(ap, 1);

	/* issue the second H2D Wegistew FIS */
	tf.ctw &= ~ATA_SWST;
	ahci_exec_powwed_cmd(ap, pmp, &tf, 0, 0, 0);

	/* wait fow wink to become weady */
	wc = ata_wait_aftew_weset(wink, deadwine, check_weady);
	if (wc == -EBUSY && hpwiv->fwags & AHCI_HFWAG_SWST_TOUT_IS_OFFWINE) {
		/*
		 * Wowkawound fow cases whewe wink onwine status can't
		 * be twusted.  Tweat device weadiness timeout as wink
		 * offwine.
		 */
		ata_wink_info(wink, "device not weady, tweating as offwine\n");
		*cwass = ATA_DEV_NONE;
	} ewse if (wc) {
		/* wink occupied, -ENODEV too is an ewwow */
		weason = "device not weady";
		goto faiw;
	} ewse
		*cwass = ahci_dev_cwassify(ap);

	/* we-enabwe FBS if disabwed befowe */
	if (fbs_disabwed)
		ahci_enabwe_fbs(ap);

	wetuwn 0;

 faiw:
	ata_wink_eww(wink, "softweset faiwed (%s)\n", weason);
	wetuwn wc;
}

int ahci_check_weady(stwuct ata_wink *wink)
{
	void __iomem *powt_mmio = ahci_powt_base(wink->ap);
	u8 status = weadw(powt_mmio + POWT_TFDATA) & 0xFF;

	wetuwn ata_check_weady(status);
}
EXPOWT_SYMBOW_GPW(ahci_check_weady);

static int ahci_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine)
{
	int pmp = sata_swst_pmp(wink);

	wetuwn ahci_do_softweset(wink, cwass, pmp, deadwine, ahci_check_weady);
}
EXPOWT_SYMBOW_GPW(ahci_do_softweset);

static int ahci_bad_pmp_check_weady(stwuct ata_wink *wink)
{
	void __iomem *powt_mmio = ahci_powt_base(wink->ap);
	u8 status = weadw(powt_mmio + POWT_TFDATA) & 0xFF;
	u32 iwq_status = weadw(powt_mmio + POWT_IWQ_STAT);

	/*
	 * Thewe is no need to check TFDATA if BAD PMP is found due to HW bug,
	 * which can save timeout deway.
	 */
	if (iwq_status & POWT_IWQ_BAD_PMP)
		wetuwn -EIO;

	wetuwn ata_check_weady(status);
}

static int ahci_pmp_wetwy_softweset(stwuct ata_wink *wink, unsigned int *cwass,
				    unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	int pmp = sata_swst_pmp(wink);
	int wc;
	u32 iwq_sts;

	wc = ahci_do_softweset(wink, cwass, pmp, deadwine,
			       ahci_bad_pmp_check_weady);

	/*
	 * Soft weset faiws with IPMS set when PMP is enabwed but
	 * SATA HDD/ODD is connected to SATA powt, do soft weset
	 * again to powt 0.
	 */
	if (wc == -EIO) {
		iwq_sts = weadw(powt_mmio + POWT_IWQ_STAT);
		if (iwq_sts & POWT_IWQ_BAD_PMP) {
			ata_wink_wawn(wink,
					"appwying PMP SWST wowkawound "
					"and wetwying\n");
			wc = ahci_do_softweset(wink, cwass, 0, deadwine,
					       ahci_check_weady);
		}
	}

	wetuwn wc;
}

int ahci_do_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
		      unsigned wong deadwine, boow *onwine)
{
	const unsigned int *timing = sata_ehc_deb_timing(&wink->eh_context);
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	u8 *d2h_fis = pp->wx_fis + WX_FIS_D2H_WEG;
	stwuct ata_taskfiwe tf;
	int wc;

	hpwiv->stop_engine(ap);

	/* cweaw D2H weception awea to pwopewwy wait fow D2H FIS */
	ata_tf_init(wink->device, &tf);
	tf.status = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	ahci_powt_cweaw_pending_iwq(ap);

	wc = sata_wink_hawdweset(wink, timing, deadwine, onwine,
				 ahci_check_weady);

	hpwiv->stawt_engine(ap);

	if (*onwine)
		*cwass = ahci_dev_cwassify(ap);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ahci_do_hawdweset);

static int ahci_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine)
{
	boow onwine;

	wetuwn ahci_do_hawdweset(wink, cwass, deadwine, &onwine);
}

static void ahci_postweset(stwuct ata_wink *wink, unsigned int *cwass)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 new_tmp, tmp;

	ata_std_postweset(wink, cwass);

	/* Make suwe powt's ATAPI bit is set appwopwiatewy */
	new_tmp = tmp = weadw(powt_mmio + POWT_CMD);
	if (*cwass == ATA_DEV_ATAPI)
		new_tmp |= POWT_CMD_ATAPI;
	ewse
		new_tmp &= ~POWT_CMD_ATAPI;
	if (new_tmp != tmp) {
		wwitew(new_tmp, powt_mmio + POWT_CMD);
		weadw(powt_mmio + POWT_CMD); /* fwush */
	}
}

static unsigned int ahci_fiww_sg(stwuct ata_queued_cmd *qc, void *cmd_tbw)
{
	stwuct scattewwist *sg;
	stwuct ahci_sg *ahci_sg = cmd_tbw + AHCI_CMD_TBW_HDW_SZ;
	unsigned int si;

	/*
	 * Next, the S/G wist.
	 */
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		dma_addw_t addw = sg_dma_addwess(sg);
		u32 sg_wen = sg_dma_wen(sg);

		ahci_sg[si].addw = cpu_to_we32(addw & 0xffffffff);
		ahci_sg[si].addw_hi = cpu_to_we32((addw >> 16) >> 16);
		ahci_sg[si].fwags_size = cpu_to_we32(sg_wen - 1);
	}

	wetuwn si;
}

static int ahci_pmp_qc_defew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;

	if (!sata_pmp_attached(ap) || pp->fbs_enabwed)
		wetuwn ata_std_qc_defew(qc);
	ewse
		wetuwn sata_pmp_qc_defew_cmd_switch(qc);
}

static enum ata_compwetion_ewwows ahci_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	int is_atapi = ata_is_atapi(qc->tf.pwotocow);
	void *cmd_tbw;
	u32 opts;
	const u32 cmd_fis_wen = 5; /* five dwowds */
	unsigned int n_ewem;

	/*
	 * Fiww in command tabwe infowmation.  Fiwst, the headew,
	 * a SATA Wegistew - Host to Device command FIS.
	 */
	cmd_tbw = pp->cmd_tbw + qc->hw_tag * AHCI_CMD_TBW_SZ;

	ata_tf_to_fis(&qc->tf, qc->dev->wink->pmp, 1, cmd_tbw);
	if (is_atapi) {
		memset(cmd_tbw + AHCI_CMD_TBW_CDB, 0, 32);
		memcpy(cmd_tbw + AHCI_CMD_TBW_CDB, qc->cdb, qc->dev->cdb_wen);
	}

	n_ewem = 0;
	if (qc->fwags & ATA_QCFWAG_DMAMAP)
		n_ewem = ahci_fiww_sg(qc, cmd_tbw);

	/*
	 * Fiww in command swot infowmation.
	 */
	opts = cmd_fis_wen | n_ewem << 16 | (qc->dev->wink->pmp << 12);
	if (qc->tf.fwags & ATA_TFWAG_WWITE)
		opts |= AHCI_CMD_WWITE;
	if (is_atapi)
		opts |= AHCI_CMD_ATAPI | AHCI_CMD_PWEFETCH;

	ahci_fiww_cmd_swot(pp, qc->hw_tag, opts);

	wetuwn AC_EWW_OK;
}

static void ahci_fbs_dec_intw(stwuct ata_powt *ap)
{
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 fbs = weadw(powt_mmio + POWT_FBS);
	int wetwies = 3;

	BUG_ON(!pp->fbs_enabwed);

	/* time to wait fow DEC is not specified by AHCI spec,
	 * add a wetwy woop fow safety.
	 */
	wwitew(fbs | POWT_FBS_DEC, powt_mmio + POWT_FBS);
	fbs = weadw(powt_mmio + POWT_FBS);
	whiwe ((fbs & POWT_FBS_DEC) && wetwies--) {
		udeway(1);
		fbs = weadw(powt_mmio + POWT_FBS);
	}

	if (fbs & POWT_FBS_DEC)
		dev_eww(ap->host->dev, "faiwed to cweaw device ewwow\n");
}

static void ahci_ewwow_intw(stwuct ata_powt *ap, u32 iwq_stat)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ata_eh_info *host_ehi = &ap->wink.eh_info;
	stwuct ata_wink *wink = NUWW;
	stwuct ata_queued_cmd *active_qc;
	stwuct ata_eh_info *active_ehi;
	boow fbs_need_dec = fawse;
	u32 sewwow;

	/* detewmine active wink with ewwow */
	if (pp->fbs_enabwed) {
		void __iomem *powt_mmio = ahci_powt_base(ap);
		u32 fbs = weadw(powt_mmio + POWT_FBS);
		int pmp = fbs >> POWT_FBS_DWE_OFFSET;

		if ((fbs & POWT_FBS_SDE) && (pmp < ap->nw_pmp_winks)) {
			wink = &ap->pmp_wink[pmp];
			fbs_need_dec = twue;
		}

	} ewse
		ata_fow_each_wink(wink, ap, EDGE)
			if (ata_wink_active(wink))
				bweak;

	if (!wink)
		wink = &ap->wink;

	active_qc = ata_qc_fwom_tag(ap, wink->active_tag);
	active_ehi = &wink->eh_info;

	/* wecowd iwq stat */
	ata_ehi_cweaw_desc(host_ehi);
	ata_ehi_push_desc(host_ehi, "iwq_stat 0x%08x", iwq_stat);

	/* AHCI needs SEwwow cweawed; othewwise, it might wock up */
	ahci_scw_wead(&ap->wink, SCW_EWWOW, &sewwow);
	ahci_scw_wwite(&ap->wink, SCW_EWWOW, sewwow);
	host_ehi->sewwow |= sewwow;

	/* some contwowwews set IWQ_IF_EWW on device ewwows, ignowe it */
	if (hpwiv->fwags & AHCI_HFWAG_IGN_IWQ_IF_EWW)
		iwq_stat &= ~POWT_IWQ_IF_EWW;

	if (iwq_stat & POWT_IWQ_TF_EWW) {
		/* If qc is active, chawge it; othewwise, the active
		 * wink.  Thewe's no active qc on NCQ ewwows.  It wiww
		 * be detewmined by EH by weading wog page 10h.
		 */
		if (active_qc)
			active_qc->eww_mask |= AC_EWW_DEV;
		ewse
			active_ehi->eww_mask |= AC_EWW_DEV;

		if (hpwiv->fwags & AHCI_HFWAG_IGN_SEWW_INTEWNAW)
			host_ehi->sewwow &= ~SEWW_INTEWNAW;
	}

	if (iwq_stat & POWT_IWQ_UNK_FIS) {
		u32 *unk = pp->wx_fis + WX_FIS_UNK;

		active_ehi->eww_mask |= AC_EWW_HSM;
		active_ehi->action |= ATA_EH_WESET;
		ata_ehi_push_desc(active_ehi,
				  "unknown FIS %08x %08x %08x %08x" ,
				  unk[0], unk[1], unk[2], unk[3]);
	}

	if (sata_pmp_attached(ap) && (iwq_stat & POWT_IWQ_BAD_PMP)) {
		active_ehi->eww_mask |= AC_EWW_HSM;
		active_ehi->action |= ATA_EH_WESET;
		ata_ehi_push_desc(active_ehi, "incowwect PMP");
	}

	if (iwq_stat & (POWT_IWQ_HBUS_EWW | POWT_IWQ_HBUS_DATA_EWW)) {
		host_ehi->eww_mask |= AC_EWW_HOST_BUS;
		host_ehi->action |= ATA_EH_WESET;
		ata_ehi_push_desc(host_ehi, "host bus ewwow");
	}

	if (iwq_stat & POWT_IWQ_IF_EWW) {
		if (fbs_need_dec)
			active_ehi->eww_mask |= AC_EWW_DEV;
		ewse {
			host_ehi->eww_mask |= AC_EWW_ATA_BUS;
			host_ehi->action |= ATA_EH_WESET;
		}

		ata_ehi_push_desc(host_ehi, "intewface fataw ewwow");
	}

	if (iwq_stat & (POWT_IWQ_CONNECT | POWT_IWQ_PHYWDY)) {
		ata_ehi_hotpwugged(host_ehi);
		ata_ehi_push_desc(host_ehi, "%s",
			iwq_stat & POWT_IWQ_CONNECT ?
			"connection status changed" : "PHY WDY changed");
	}

	/* okay, wet's hand ovew to EH */

	if (iwq_stat & POWT_IWQ_FWEEZE)
		ata_powt_fweeze(ap);
	ewse if (fbs_need_dec) {
		ata_wink_abowt(wink);
		ahci_fbs_dec_intw(ap);
	} ewse
		ata_powt_abowt(ap);
}

static void ahci_qc_compwete(stwuct ata_powt *ap, void __iomem *powt_mmio)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	u32 qc_active = 0;
	int wc;

	/*
	 * pp->active_wink is not wewiabwe once FBS is enabwed, both
	 * POWT_SCW_ACT and POWT_CMD_ISSUE shouwd be checked because
	 * NCQ and non-NCQ commands may be in fwight at the same time.
	 */
	if (pp->fbs_enabwed) {
		if (ap->qc_active) {
			qc_active = weadw(powt_mmio + POWT_SCW_ACT);
			qc_active |= weadw(powt_mmio + POWT_CMD_ISSUE);
		}
	} ewse {
		/* pp->active_wink is vawid iff any command is in fwight */
		if (ap->qc_active && pp->active_wink->sactive)
			qc_active = weadw(powt_mmio + POWT_SCW_ACT);
		ewse
			qc_active = weadw(powt_mmio + POWT_CMD_ISSUE);
	}

	wc = ata_qc_compwete_muwtipwe(ap, qc_active);
	if (unwikewy(wc < 0 && !(ap->pfwags & ATA_PFWAG_WESETTING))) {
		ehi->eww_mask |= AC_EWW_HSM;
		ehi->action |= ATA_EH_WESET;
		ata_powt_fweeze(ap);
	}
}

static void ahci_handwe_powt_intewwupt(stwuct ata_powt *ap,
				       void __iomem *powt_mmio, u32 status)
{
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	/* ignowe BAD_PMP whiwe wesetting */
	if (unwikewy(ap->pfwags & ATA_PFWAG_WESETTING))
		status &= ~POWT_IWQ_BAD_PMP;

	if (sata_wpm_ignowe_phy_events(&ap->wink)) {
		status &= ~POWT_IWQ_PHYWDY;
		ahci_scw_wwite(&ap->wink, SCW_EWWOW, SEWW_PHYWDY_CHG);
	}

	if (unwikewy(status & POWT_IWQ_EWWOW)) {
		/*
		 * Befowe getting the ewwow notification, we may have
		 * weceived SDB FISes notifying successfuw compwetions.
		 * Handwe these fiwst and then handwe the ewwow.
		 */
		ahci_qc_compwete(ap, powt_mmio);
		ahci_ewwow_intw(ap, status);
		wetuwn;
	}

	if (status & POWT_IWQ_SDB_FIS) {
		/* If SNotification is avaiwabwe, weave notification
		 * handwing to sata_async_notification().  If not,
		 * emuwate it by snooping SDB FIS WX awea.
		 *
		 * Snooping FIS WX awea is pwobabwy cheapew than
		 * poking SNotification but some constwowwews which
		 * impwement SNotification, ICH9 fow exampwe, don't
		 * stowe AN SDB FIS into weceive awea.
		 */
		if (hpwiv->cap & HOST_CAP_SNTF)
			sata_async_notification(ap);
		ewse {
			/* If the 'N' bit in wowd 0 of the FIS is set,
			 * we just weceived asynchwonous notification.
			 * Teww wibata about it.
			 *
			 * Wack of SNotification shouwd not appeaw in
			 * ahci 1.2, so the wowkawound is unnecessawy
			 * when FBS is enabwed.
			 */
			if (pp->fbs_enabwed)
				WAWN_ON_ONCE(1);
			ewse {
				const __we32 *f = pp->wx_fis + WX_FIS_SDB;
				u32 f0 = we32_to_cpu(f[0]);
				if (f0 & (1 << 15))
					sata_async_notification(ap);
			}
		}
	}

	/* Handwe compweted commands */
	ahci_qc_compwete(ap, powt_mmio);
}

static void ahci_powt_intw(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 status;

	status = weadw(powt_mmio + POWT_IWQ_STAT);
	wwitew(status, powt_mmio + POWT_IWQ_STAT);

	ahci_handwe_powt_intewwupt(ap, powt_mmio, status);
}

static iwqwetuwn_t ahci_muwti_iwqs_intw_hawd(int iwq, void *dev_instance)
{
	stwuct ata_powt *ap = dev_instance;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 status;

	status = weadw(powt_mmio + POWT_IWQ_STAT);
	wwitew(status, powt_mmio + POWT_IWQ_STAT);

	spin_wock(ap->wock);
	ahci_handwe_powt_intewwupt(ap, powt_mmio, status);
	spin_unwock(ap->wock);

	wetuwn IWQ_HANDWED;
}

u32 ahci_handwe_powt_intw(stwuct ata_host *host, u32 iwq_masked)
{
	unsigned int i, handwed = 0;

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap;

		if (!(iwq_masked & (1 << i)))
			continue;

		ap = host->powts[i];
		if (ap) {
			ahci_powt_intw(ap);
		} ewse {
			if (ata_watewimit())
				dev_wawn(host->dev,
					 "intewwupt on disabwed powt %u\n", i);
		}

		handwed = 1;
	}

	wetuwn handwed;
}
EXPOWT_SYMBOW_GPW(ahci_handwe_powt_intw);

static iwqwetuwn_t ahci_singwe_wevew_iwq_intw(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct ahci_host_pwiv *hpwiv;
	unsigned int wc = 0;
	void __iomem *mmio;
	u32 iwq_stat, iwq_masked;

	hpwiv = host->pwivate_data;
	mmio = hpwiv->mmio;

	/* sigh.  0xffffffff is a vawid wetuwn fwom h/w */
	iwq_stat = weadw(mmio + HOST_IWQ_STAT);
	if (!iwq_stat)
		wetuwn IWQ_NONE;

	iwq_masked = iwq_stat & hpwiv->powt_map;

	spin_wock(&host->wock);

	wc = ahci_handwe_powt_intw(host, iwq_masked);

	/* HOST_IWQ_STAT behaves as wevew twiggewed watch meaning that
	 * it shouwd be cweawed aftew aww the powt events awe cweawed;
	 * othewwise, it wiww waise a spuwious intewwupt aftew each
	 * vawid one.  Pwease wead section 10.6.2 of ahci 1.1 fow mowe
	 * infowmation.
	 *
	 * Awso, use the unmasked vawue to cweaw intewwupt as spuwious
	 * pending event on a dummy powt might cause scweaming IWQ.
	 */
	wwitew(iwq_stat, mmio + HOST_IWQ_STAT);

	spin_unwock(&host->wock);

	wetuwn IWQ_WETVAW(wc);
}

unsigned int ahci_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;

	/* Keep twack of the cuwwentwy active wink.  It wiww be used
	 * in compwetion path to detewmine whethew NCQ phase is in
	 * pwogwess.
	 */
	pp->active_wink = qc->dev->wink;

	if (ata_is_ncq(qc->tf.pwotocow))
		wwitew(1 << qc->hw_tag, powt_mmio + POWT_SCW_ACT);

	if (pp->fbs_enabwed && pp->fbs_wast_dev != qc->dev->wink->pmp) {
		u32 fbs = weadw(powt_mmio + POWT_FBS);
		fbs &= ~(POWT_FBS_DEV_MASK | POWT_FBS_DEC);
		fbs |= qc->dev->wink->pmp << POWT_FBS_DEV_OFFSET;
		wwitew(fbs, powt_mmio + POWT_FBS);
		pp->fbs_wast_dev = qc->dev->wink->pmp;
	}

	wwitew(1 << qc->hw_tag, powt_mmio + POWT_CMD_ISSUE);

	ahci_sw_activity(qc->dev->wink);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ahci_qc_issue);

static void ahci_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	stwuct ahci_powt_pwiv *pp = qc->ap->pwivate_data;
	u8 *wx_fis = pp->wx_fis;

	/*
	 * wtf may awweady be fiwwed (e.g. fow successfuw NCQ commands).
	 * If that is the case, we have nothing to do.
	 */
	if (qc->fwags & ATA_QCFWAG_WTF_FIWWED)
		wetuwn;

	if (pp->fbs_enabwed)
		wx_fis += qc->dev->wink->pmp * AHCI_WX_FIS_SZ;

	/*
	 * Aftew a successfuw execution of an ATA PIO data-in command,
	 * the device doesn't send D2H Weg FIS to update the TF and
	 * the host shouwd take TF and E_Status fwom the pweceding PIO
	 * Setup FIS.
	 */
	if (qc->tf.pwotocow == ATA_PWOT_PIO && qc->dma_diw == DMA_FWOM_DEVICE &&
	    !(qc->fwags & ATA_QCFWAG_EH)) {
		ata_tf_fwom_fis(wx_fis + WX_FIS_PIO_SETUP, &qc->wesuwt_tf);
		qc->wesuwt_tf.status = (wx_fis + WX_FIS_PIO_SETUP)[15];
		qc->fwags |= ATA_QCFWAG_WTF_FIWWED;
		wetuwn;
	}

	/*
	 * Fow NCQ commands, we nevew get a D2H FIS, so weading the D2H Wegistew
	 * FIS awea of the Weceived FIS Stwuctuwe (which contains a copy of the
	 * wast D2H FIS weceived) wiww contain an outdated status code.
	 * Fow NCQ commands, we instead get a SDB FIS, so wead the SDB FIS awea
	 * instead. Howevew, the SDB FIS does not contain the WBA, so we can't
	 * use the ata_tf_fwom_fis() hewpew.
	 */
	if (ata_is_ncq(qc->tf.pwotocow)) {
		const u8 *fis = wx_fis + WX_FIS_SDB;

		/*
		 * Successfuw NCQ commands have been fiwwed awweady.
		 * A faiwed NCQ command wiww wead the status hewe.
		 * (Note that a faiwed NCQ command wiww get a mowe specific
		 * ewwow when weading the NCQ Command Ewwow wog.)
		 */
		qc->wesuwt_tf.status = fis[2];
		qc->wesuwt_tf.ewwow = fis[3];
		qc->fwags |= ATA_QCFWAG_WTF_FIWWED;
		wetuwn;
	}

	ata_tf_fwom_fis(wx_fis + WX_FIS_D2H_WEG, &qc->wesuwt_tf);
	qc->fwags |= ATA_QCFWAG_WTF_FIWWED;
}

static void ahci_qc_ncq_fiww_wtf(stwuct ata_powt *ap, u64 done_mask)
{
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	const u8 *fis;

	/* No outstanding commands. */
	if (!ap->qc_active)
		wetuwn;

	/*
	 * FBS not enabwed, so wead status and ewwow once, since they awe shawed
	 * fow aww QCs.
	 */
	if (!pp->fbs_enabwed) {
		u8 status, ewwow;

		/* No outstanding NCQ commands. */
		if (!pp->active_wink->sactive)
			wetuwn;

		fis = pp->wx_fis + WX_FIS_SDB;
		status = fis[2];
		ewwow = fis[3];

		whiwe (done_mask) {
			stwuct ata_queued_cmd *qc;
			unsigned int tag = __ffs64(done_mask);

			qc = ata_qc_fwom_tag(ap, tag);
			if (qc && ata_is_ncq(qc->tf.pwotocow)) {
				qc->wesuwt_tf.status = status;
				qc->wesuwt_tf.ewwow = ewwow;
				qc->fwags |= ATA_QCFWAG_WTF_FIWWED;
			}
			done_mask &= ~(1UWW << tag);
		}

		wetuwn;
	}

	/*
	 * FBS enabwed, so wead the status and ewwow fow each QC, since the QCs
	 * can bewong to diffewent PMP winks. (Each PMP wink has its own FIS
	 * Weceive Awea.)
	 */
	whiwe (done_mask) {
		stwuct ata_queued_cmd *qc;
		unsigned int tag = __ffs64(done_mask);

		qc = ata_qc_fwom_tag(ap, tag);
		if (qc && ata_is_ncq(qc->tf.pwotocow)) {
			fis = pp->wx_fis;
			fis += qc->dev->wink->pmp * AHCI_WX_FIS_SZ;
			fis += WX_FIS_SDB;
			qc->wesuwt_tf.status = fis[2];
			qc->wesuwt_tf.ewwow = fis[3];
			qc->fwags |= ATA_QCFWAG_WTF_FIWWED;
		}
		done_mask &= ~(1UWW << tag);
	}
}

static void ahci_fweeze(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);

	/* tuwn IWQ off */
	wwitew(0, powt_mmio + POWT_IWQ_MASK);
}

static void ahci_thaw(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 tmp;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;

	/* cweaw IWQ */
	tmp = weadw(powt_mmio + POWT_IWQ_STAT);
	wwitew(tmp, powt_mmio + POWT_IWQ_STAT);
	wwitew(1 << ap->powt_no, mmio + HOST_IWQ_STAT);

	/* tuwn IWQ back on */
	wwitew(pp->intw_mask, powt_mmio + POWT_IWQ_MASK);
}

void ahci_ewwow_handwew(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	if (!ata_powt_is_fwozen(ap)) {
		/* westawt engine */
		hpwiv->stop_engine(ap);
		hpwiv->stawt_engine(ap);
	}

	sata_pmp_ewwow_handwew(ap);

	if (!ata_dev_enabwed(ap->wink.device))
		hpwiv->stop_engine(ap);
}
EXPOWT_SYMBOW_GPW(ahci_ewwow_handwew);

static void ahci_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	/* make DMA engine fowget about the faiwed command */
	if (qc->fwags & ATA_QCFWAG_EH)
		ahci_kick_engine(ap);
}

static void ahci_set_aggwessive_devswp(stwuct ata_powt *ap, boow sweep)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ata_device *dev = ap->wink.device;
	u32 devswp, dm, dito, mdat, deto, dito_conf;
	int wc;
	unsigned int eww_mask;

	devswp = weadw(powt_mmio + POWT_DEVSWP);
	if (!(devswp & POWT_DEVSWP_DSP)) {
		dev_info(ap->host->dev, "powt does not suppowt device sweep\n");
		wetuwn;
	}

	/* disabwe device sweep */
	if (!sweep) {
		if (devswp & POWT_DEVSWP_ADSE) {
			wwitew(devswp & ~POWT_DEVSWP_ADSE,
			       powt_mmio + POWT_DEVSWP);
			eww_mask = ata_dev_set_featuwe(dev,
						       SETFEATUWES_SATA_DISABWE,
						       SATA_DEVSWP);
			if (eww_mask && eww_mask != AC_EWW_DEV)
				ata_dev_wawn(dev, "faiwed to disabwe DEVSWP\n");
		}
		wetuwn;
	}

	dm = (devswp & POWT_DEVSWP_DM_MASK) >> POWT_DEVSWP_DM_OFFSET;
	dito = devswp_idwe_timeout / (dm + 1);
	if (dito > 0x3ff)
		dito = 0x3ff;

	dito_conf = (devswp >> POWT_DEVSWP_DITO_OFFSET) & 0x3FF;

	/* device sweep was awweady enabwed and same dito */
	if ((devswp & POWT_DEVSWP_ADSE) && (dito_conf == dito))
		wetuwn;

	/* set DITO, MDAT, DETO and enabwe DevSwp, need to stop engine fiwst */
	wc = hpwiv->stop_engine(ap);
	if (wc)
		wetuwn;

	/* Use the nominaw vawue 10 ms if the wead MDAT is zewo,
	 * the nominaw vawue of DETO is 20 ms.
	 */
	if (dev->devswp_timing[ATA_WOG_DEVSWP_VAWID] &
	    ATA_WOG_DEVSWP_VAWID_MASK) {
		mdat = dev->devswp_timing[ATA_WOG_DEVSWP_MDAT] &
		       ATA_WOG_DEVSWP_MDAT_MASK;
		if (!mdat)
			mdat = 10;
		deto = dev->devswp_timing[ATA_WOG_DEVSWP_DETO];
		if (!deto)
			deto = 20;
	} ewse {
		mdat = 10;
		deto = 20;
	}

	/* Make dito, mdat, deto bits to 0s */
	devswp &= ~GENMASK_UWW(24, 2);
	devswp |= ((dito << POWT_DEVSWP_DITO_OFFSET) |
		   (mdat << POWT_DEVSWP_MDAT_OFFSET) |
		   (deto << POWT_DEVSWP_DETO_OFFSET) |
		   POWT_DEVSWP_ADSE);
	wwitew(devswp, powt_mmio + POWT_DEVSWP);

	hpwiv->stawt_engine(ap);

	/* enabwe device sweep featuwe fow the dwive */
	eww_mask = ata_dev_set_featuwe(dev,
				       SETFEATUWES_SATA_ENABWE,
				       SATA_DEVSWP);
	if (eww_mask && eww_mask != AC_EWW_DEV)
		ata_dev_wawn(dev, "faiwed to enabwe DEVSWP\n");
}

static void ahci_enabwe_fbs(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 fbs;
	int wc;

	if (!pp->fbs_suppowted)
		wetuwn;

	fbs = weadw(powt_mmio + POWT_FBS);
	if (fbs & POWT_FBS_EN) {
		pp->fbs_enabwed = twue;
		pp->fbs_wast_dev = -1; /* initiawization */
		wetuwn;
	}

	wc = hpwiv->stop_engine(ap);
	if (wc)
		wetuwn;

	wwitew(fbs | POWT_FBS_EN, powt_mmio + POWT_FBS);
	fbs = weadw(powt_mmio + POWT_FBS);
	if (fbs & POWT_FBS_EN) {
		dev_info(ap->host->dev, "FBS is enabwed\n");
		pp->fbs_enabwed = twue;
		pp->fbs_wast_dev = -1; /* initiawization */
	} ewse
		dev_eww(ap->host->dev, "Faiwed to enabwe FBS\n");

	hpwiv->stawt_engine(ap);
}

static void ahci_disabwe_fbs(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 fbs;
	int wc;

	if (!pp->fbs_suppowted)
		wetuwn;

	fbs = weadw(powt_mmio + POWT_FBS);
	if ((fbs & POWT_FBS_EN) == 0) {
		pp->fbs_enabwed = fawse;
		wetuwn;
	}

	wc = hpwiv->stop_engine(ap);
	if (wc)
		wetuwn;

	wwitew(fbs & ~POWT_FBS_EN, powt_mmio + POWT_FBS);
	fbs = weadw(powt_mmio + POWT_FBS);
	if (fbs & POWT_FBS_EN)
		dev_eww(ap->host->dev, "Faiwed to disabwe FBS\n");
	ewse {
		dev_info(ap->host->dev, "FBS is disabwed\n");
		pp->fbs_enabwed = fawse;
	}

	hpwiv->stawt_engine(ap);
}

static void ahci_pmp_attach(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	u32 cmd;

	cmd = weadw(powt_mmio + POWT_CMD);
	cmd |= POWT_CMD_PMP;
	wwitew(cmd, powt_mmio + POWT_CMD);

	ahci_enabwe_fbs(ap);

	pp->intw_mask |= POWT_IWQ_BAD_PMP;

	/*
	 * We must not change the powt intewwupt mask wegistew if the
	 * powt is mawked fwozen, the vawue in pp->intw_mask wiww be
	 * westowed watew when the powt is thawed.
	 *
	 * Note that duwing initiawization, the powt is mawked as
	 * fwozen since the iwq handwew is not yet wegistewed.
	 */
	if (!ata_powt_is_fwozen(ap))
		wwitew(pp->intw_mask, powt_mmio + POWT_IWQ_MASK);
}

static void ahci_pmp_detach(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	u32 cmd;

	ahci_disabwe_fbs(ap);

	cmd = weadw(powt_mmio + POWT_CMD);
	cmd &= ~POWT_CMD_PMP;
	wwitew(cmd, powt_mmio + POWT_CMD);

	pp->intw_mask &= ~POWT_IWQ_BAD_PMP;

	/* see comment above in ahci_pmp_attach() */
	if (!ata_powt_is_fwozen(ap))
		wwitew(pp->intw_mask, powt_mmio + POWT_IWQ_MASK);
}

int ahci_powt_wesume(stwuct ata_powt *ap)
{
	ahci_wpm_get_powt(ap);

	ahci_powew_up(ap);
	ahci_stawt_powt(ap);

	if (sata_pmp_attached(ap))
		ahci_pmp_attach(ap);
	ewse
		ahci_pmp_detach(ap);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ahci_powt_wesume);

#ifdef CONFIG_PM
static void ahci_handwe_s2idwe(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	u32 devswp;

	if (pm_suspend_via_fiwmwawe())
		wetuwn;
	devswp = weadw(powt_mmio + POWT_DEVSWP);
	if ((devswp & POWT_DEVSWP_ADSE))
		ata_msweep(ap, devswp_idwe_timeout);
}

static int ahci_powt_suspend(stwuct ata_powt *ap, pm_message_t mesg)
{
	const chaw *emsg = NUWW;
	int wc;

	wc = ahci_deinit_powt(ap, &emsg);
	if (wc == 0)
		ahci_powew_down(ap);
	ewse {
		ata_powt_eww(ap, "%s (%d)\n", emsg, wc);
		ata_powt_fweeze(ap);
	}

	if (acpi_stowage_d3(ap->host->dev))
		ahci_handwe_s2idwe(ap);

	ahci_wpm_put_powt(ap);
	wetuwn wc;
}
#endif

static int ahci_powt_stawt(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct device *dev = ap->host->dev;
	stwuct ahci_powt_pwiv *pp;
	void *mem;
	dma_addw_t mem_dma;
	size_t dma_sz, wx_fis_sz;

	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;

	if (ap->host->n_powts > 1) {
		pp->iwq_desc = devm_kzawwoc(dev, 8, GFP_KEWNEW);
		if (!pp->iwq_desc) {
			devm_kfwee(dev, pp);
			wetuwn -ENOMEM;
		}
		snpwintf(pp->iwq_desc, 8,
			 "%s%d", dev_dwivew_stwing(dev), ap->powt_no);
	}

	/* check FBS capabiwity */
	if ((hpwiv->cap & HOST_CAP_FBS) && sata_pmp_suppowted(ap)) {
		void __iomem *powt_mmio = ahci_powt_base(ap);
		u32 cmd = weadw(powt_mmio + POWT_CMD);
		if (cmd & POWT_CMD_FBSCP)
			pp->fbs_suppowted = twue;
		ewse if (hpwiv->fwags & AHCI_HFWAG_YES_FBS) {
			dev_info(dev, "powt %d can do FBS, fowcing FBSCP\n",
				 ap->powt_no);
			pp->fbs_suppowted = twue;
		} ewse
			dev_wawn(dev, "powt %d is not capabwe of FBS\n",
				 ap->powt_no);
	}

	if (pp->fbs_suppowted) {
		dma_sz = AHCI_POWT_PWIV_FBS_DMA_SZ;
		wx_fis_sz = AHCI_WX_FIS_SZ * 16;
	} ewse {
		dma_sz = AHCI_POWT_PWIV_DMA_SZ;
		wx_fis_sz = AHCI_WX_FIS_SZ;
	}

	mem = dmam_awwoc_cohewent(dev, dma_sz, &mem_dma, GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	/*
	 * Fiwst item in chunk of DMA memowy: 32-swot command tabwe,
	 * 32 bytes each in size
	 */
	pp->cmd_swot = mem;
	pp->cmd_swot_dma = mem_dma;

	mem += AHCI_CMD_SWOT_SZ;
	mem_dma += AHCI_CMD_SWOT_SZ;

	/*
	 * Second item: Weceived-FIS awea
	 */
	pp->wx_fis = mem;
	pp->wx_fis_dma = mem_dma;

	mem += wx_fis_sz;
	mem_dma += wx_fis_sz;

	/*
	 * Thiwd item: data awea fow stowing a singwe command
	 * and its scattew-gathew tabwe
	 */
	pp->cmd_tbw = mem;
	pp->cmd_tbw_dma = mem_dma;

	/*
	 * Save off initiaw wist of intewwupts to be enabwed.
	 * This couwd be changed watew
	 */
	pp->intw_mask = DEF_POWT_IWQ;

	/*
	 * Switch to pew-powt wocking in case each powt has its own MSI vectow.
	 */
	if (hpwiv->fwags & AHCI_HFWAG_MUWTI_MSI) {
		spin_wock_init(&pp->wock);
		ap->wock = &pp->wock;
	}

	ap->pwivate_data = pp;

	/* engage engines, captain */
	wetuwn ahci_powt_wesume(ap);
}

static void ahci_powt_stop(stwuct ata_powt *ap)
{
	const chaw *emsg = NUWW;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	void __iomem *host_mmio = hpwiv->mmio;
	int wc;

	/* de-initiawize powt */
	wc = ahci_deinit_powt(ap, &emsg);
	if (wc)
		ata_powt_wawn(ap, "%s (%d)\n", emsg, wc);

	/*
	 * Cweaw GHC.IS to pwevent stuck INTx aftew disabwing MSI and
	 * we-enabwing INTx.
	 */
	wwitew(1 << ap->powt_no, host_mmio + HOST_IWQ_STAT);

	ahci_wpm_put_powt(ap);
}

void ahci_pwint_info(stwuct ata_host *host, const chaw *scc_s)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	u32 vews, cap, cap2, impw, speed;
	const chaw *speed_s;

	vews = hpwiv->vewsion;
	cap = hpwiv->cap;
	cap2 = hpwiv->cap2;
	impw = hpwiv->powt_map;

	speed = (cap >> 20) & 0xf;
	if (speed == 1)
		speed_s = "1.5";
	ewse if (speed == 2)
		speed_s = "3";
	ewse if (speed == 3)
		speed_s = "6";
	ewse
		speed_s = "?";

	dev_info(host->dev,
		"AHCI %02x%02x.%02x%02x "
		"%u swots %u powts %s Gbps 0x%x impw %s mode\n"
		,

		(vews >> 24) & 0xff,
		(vews >> 16) & 0xff,
		(vews >> 8) & 0xff,
		vews & 0xff,

		((cap >> 8) & 0x1f) + 1,
		(cap & 0x1f) + 1,
		speed_s,
		impw,
		scc_s);

	dev_info(host->dev,
		"fwags: "
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s\n"
		,

		cap & HOST_CAP_64 ? "64bit " : "",
		cap & HOST_CAP_NCQ ? "ncq " : "",
		cap & HOST_CAP_SNTF ? "sntf " : "",
		cap & HOST_CAP_MPS ? "iwck " : "",
		cap & HOST_CAP_SSS ? "stag " : "",
		cap & HOST_CAP_AWPM ? "pm " : "",
		cap & HOST_CAP_WED ? "wed " : "",
		cap & HOST_CAP_CWO ? "cwo " : "",
		cap & HOST_CAP_ONWY ? "onwy " : "",
		cap & HOST_CAP_PMP ? "pmp " : "",
		cap & HOST_CAP_FBS ? "fbs " : "",
		cap & HOST_CAP_PIO_MUWTI ? "pio " : "",
		cap & HOST_CAP_SSC ? "swum " : "",
		cap & HOST_CAP_PAWT ? "pawt " : "",
		cap & HOST_CAP_CCC ? "ccc " : "",
		cap & HOST_CAP_EMS ? "ems " : "",
		cap & HOST_CAP_SXS ? "sxs " : "",
		cap2 & HOST_CAP2_DESO ? "deso " : "",
		cap2 & HOST_CAP2_SADM ? "sadm " : "",
		cap2 & HOST_CAP2_SDS ? "sds " : "",
		cap2 & HOST_CAP2_APST ? "apst " : "",
		cap2 & HOST_CAP2_NVMHCI ? "nvmp " : "",
		cap2 & HOST_CAP2_BOH ? "boh " : ""
		);
}
EXPOWT_SYMBOW_GPW(ahci_pwint_info);

void ahci_set_em_messages(stwuct ahci_host_pwiv *hpwiv,
			  stwuct ata_powt_info *pi)
{
	u8 messages;
	void __iomem *mmio = hpwiv->mmio;
	u32 em_woc = weadw(mmio + HOST_EM_WOC);
	u32 em_ctw = weadw(mmio + HOST_EM_CTW);

	if (!ahci_em_messages || !(hpwiv->cap & HOST_CAP_EMS))
		wetuwn;

	messages = (em_ctw & EM_CTWW_MSG_TYPE) >> 16;

	if (messages) {
		/* stowe em_woc */
		hpwiv->em_woc = ((em_woc >> 16) * 4);
		hpwiv->em_buf_sz = ((em_woc & 0xff) * 4);
		hpwiv->em_msg_type = messages;
		pi->fwags |= ATA_FWAG_EM;
		if (!(em_ctw & EM_CTW_AWHD))
			pi->fwags |= ATA_FWAG_SW_ACTIVITY;
	}
}
EXPOWT_SYMBOW_GPW(ahci_set_em_messages);

static int ahci_host_activate_muwti_iwqs(stwuct ata_host *host,
					 const stwuct scsi_host_tempwate *sht)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int i, wc;

	wc = ata_host_stawt(host);
	if (wc)
		wetuwn wc;
	/*
	 * Wequests IWQs accowding to AHCI-1.1 when muwtipwe MSIs wewe
	 * awwocated. That is one MSI pew powt, stawting fwom @iwq.
	 */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ahci_powt_pwiv *pp = host->powts[i]->pwivate_data;
		int iwq = hpwiv->get_iwq_vectow(host, i);

		/* Do not weceive intewwupts sent by dummy powts */
		if (!pp) {
			disabwe_iwq(iwq);
			continue;
		}

		wc = devm_wequest_iwq(host->dev, iwq, ahci_muwti_iwqs_intw_hawd,
				0, pp->iwq_desc, host->powts[i]);

		if (wc)
			wetuwn wc;
		ata_powt_desc_misc(host->powts[i], iwq);
	}

	wetuwn ata_host_wegistew(host, sht);
}

/**
 *	ahci_host_activate - stawt AHCI host, wequest IWQs and wegistew it
 *	@host: tawget ATA host
 *	@sht: scsi_host_tempwate to use when wegistewing the host
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ahci_host_activate(stwuct ata_host *host, const stwuct scsi_host_tempwate *sht)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int iwq = hpwiv->iwq;
	int wc;

	if (hpwiv->fwags & AHCI_HFWAG_MUWTI_MSI) {
		if (hpwiv->iwq_handwew &&
		    hpwiv->iwq_handwew != ahci_singwe_wevew_iwq_intw)
			dev_wawn(host->dev,
			         "both AHCI_HFWAG_MUWTI_MSI fwag set and custom iwq handwew impwemented\n");
		if (!hpwiv->get_iwq_vectow) {
			dev_eww(host->dev,
				"AHCI_HFWAG_MUWTI_MSI wequiwes ->get_iwq_vectow!\n");
			wetuwn -EIO;
		}

		wc = ahci_host_activate_muwti_iwqs(host, sht);
	} ewse {
		wc = ata_host_activate(host, iwq, hpwiv->iwq_handwew,
				       IWQF_SHAWED, sht);
	}


	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ahci_host_activate);

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("Common AHCI SATA wow-wevew woutines");
MODUWE_WICENSE("GPW");
