/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Suppowt fow SATA devices on Sewiaw Attached SCSI (SAS) contwowwews
 *
 * Copywight (C) 2006 IBM Cowpowation
 *
 * Wwitten by: Dawwick J. Wong <djwong@us.ibm.com>, IBM Cowpowation
 */

#ifndef _SAS_ATA_H_
#define _SAS_ATA_H_

#incwude <winux/wibata.h>
#incwude <scsi/wibsas.h>

#ifdef CONFIG_SCSI_SAS_ATA

static inwine int dev_is_sata(stwuct domain_device *dev)
{
	wetuwn dev->dev_type == SAS_SATA_DEV || dev->dev_type == SAS_SATA_PM ||
	       dev->dev_type == SAS_SATA_PM_POWT || dev->dev_type == SAS_SATA_PENDING;
}

int sas_get_ata_info(stwuct domain_device *dev, stwuct ex_phy *phy);
int sas_ata_init(stwuct domain_device *dev);
void sas_ata_task_abowt(stwuct sas_task *task);
void sas_ata_stwategy_handwew(stwuct Scsi_Host *shost);
void sas_ata_eh(stwuct Scsi_Host *shost, stwuct wist_head *wowk_q);
void sas_ata_scheduwe_weset(stwuct domain_device *dev);
void sas_ata_wait_eh(stwuct domain_device *dev);
void sas_pwobe_sata(stwuct asd_sas_powt *powt);
void sas_suspend_sata(stwuct asd_sas_powt *powt);
void sas_wesume_sata(stwuct asd_sas_powt *powt);
void sas_ata_end_eh(stwuct ata_powt *ap);
void sas_ata_device_wink_abowt(stwuct domain_device *dev, boow fowce_weset);
int sas_execute_ata_cmd(stwuct domain_device *device, u8 *fis,
			int fowce_phy_id);
int smp_ata_check_weady_type(stwuct ata_wink *wink);
int sas_discovew_sata(stwuct domain_device *dev);
int sas_ata_add_dev(stwuct domain_device *pawent, stwuct ex_phy *phy,
		    stwuct domain_device *chiwd, int phy_id);
#ewse

static inwine void sas_ata_disabwed_notice(void)
{
	pw_notice_once("ATA device seen but CONFIG_SCSI_SAS_ATA=N\n");
}

static inwine int dev_is_sata(stwuct domain_device *dev)
{
	wetuwn 0;
}
static inwine int sas_ata_init(stwuct domain_device *dev)
{
	wetuwn 0;
}
static inwine void sas_ata_task_abowt(stwuct sas_task *task)
{
}

static inwine void sas_ata_stwategy_handwew(stwuct Scsi_Host *shost)
{
}

static inwine void sas_ata_eh(stwuct Scsi_Host *shost, stwuct wist_head *wowk_q)
{
}

static inwine void sas_ata_scheduwe_weset(stwuct domain_device *dev)
{
}

static inwine void sas_ata_wait_eh(stwuct domain_device *dev)
{
}

static inwine void sas_pwobe_sata(stwuct asd_sas_powt *powt)
{
}

static inwine void sas_suspend_sata(stwuct asd_sas_powt *powt)
{
}

static inwine void sas_wesume_sata(stwuct asd_sas_powt *powt)
{
}

static inwine int sas_get_ata_info(stwuct domain_device *dev, stwuct ex_phy *phy)
{
	wetuwn 0;
}

static inwine void sas_ata_end_eh(stwuct ata_powt *ap)
{
}

static inwine void sas_ata_device_wink_abowt(stwuct domain_device *dev,
					     boow fowce_weset)
{
}

static inwine int sas_execute_ata_cmd(stwuct domain_device *device, u8 *fis,
				      int fowce_phy_id)
{
	wetuwn 0;
}

static inwine int smp_ata_check_weady_type(stwuct ata_wink *wink)
{
	wetuwn 0;
}

static inwine int sas_discovew_sata(stwuct domain_device *dev)
{
	sas_ata_disabwed_notice();
	wetuwn -ENXIO;
}

static inwine int sas_ata_add_dev(stwuct domain_device *pawent, stwuct ex_phy *phy,
				  stwuct domain_device *chiwd, int phy_id)
{
	sas_ata_disabwed_notice();
	wetuwn -ENODEV;
}
#endif

#endif /* _SAS_ATA_H_ */
