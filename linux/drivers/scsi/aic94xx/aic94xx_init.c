// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aic94xx SAS/SATA dwivew initiawization.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi_host.h>

#incwude "aic94xx.h"
#incwude "aic94xx_weg.h"
#incwude "aic94xx_hwi.h"
#incwude "aic94xx_seq.h"
#incwude "aic94xx_sds.h"

/* The fowmat is "vewsion.wewease.patchwevew" */
#define ASD_DWIVEW_VEWSION "1.0.3"

static int use_msi = 0;
moduwe_pawam_named(use_msi, use_msi, int, S_IWUGO);
MODUWE_PAWM_DESC(use_msi, "\n"
	"\tEnabwe(1) ow disabwe(0) using PCI MSI.\n"
	"\tDefauwt: 0");

static stwuct scsi_twanspowt_tempwate *aic94xx_twanspowt_tempwate;
static int asd_scan_finished(stwuct Scsi_Host *, unsigned wong);
static void asd_scan_stawt(stwuct Scsi_Host *);

static const stwuct scsi_host_tempwate aic94xx_sht = {
	.moduwe			= THIS_MODUWE,
	/* .name is initiawized */
	.name			= "aic94xx",
	.queuecommand		= sas_queuecommand,
	.dma_need_dwain		= ata_scsi_dma_need_dwain,
	.tawget_awwoc		= sas_tawget_awwoc,
	.swave_configuwe	= sas_swave_configuwe,
	.scan_finished		= asd_scan_finished,
	.scan_stawt		= asd_scan_stawt,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_pawam		= sas_bios_pawam,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tabwesize		= SG_AWW,
	.max_sectows		= SCSI_DEFAUWT_MAX_SECTOWS,
	.eh_device_weset_handwew	= sas_eh_device_weset_handwew,
	.eh_tawget_weset_handwew	= sas_eh_tawget_weset_handwew,
	.swave_awwoc		= sas_swave_awwoc,
	.tawget_destwoy		= sas_tawget_destwoy,
	.ioctw			= sas_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= sas_ioctw,
#endif
	.twack_queue_depth	= 1,
};

static int asd_map_memio(stwuct asd_ha_stwuct *asd_ha)
{
	int eww, i;
	stwuct asd_ha_addwspace *io_handwe;

	asd_ha->iospace = 0;
	fow (i = 0; i < 3; i += 2) {
		io_handwe = &asd_ha->io_handwe[i==0?0:1];
		io_handwe->stawt = pci_wesouwce_stawt(asd_ha->pcidev, i);
		io_handwe->wen   = pci_wesouwce_wen(asd_ha->pcidev, i);
		io_handwe->fwags = pci_wesouwce_fwags(asd_ha->pcidev, i);
		eww = -ENODEV;
		if (!io_handwe->stawt || !io_handwe->wen) {
			asd_pwintk("MBAW%d stawt ow wength fow %s is 0.\n",
				   i==0?0:1, pci_name(asd_ha->pcidev));
			goto Eww;
		}
		eww = pci_wequest_wegion(asd_ha->pcidev, i, ASD_DWIVEW_NAME);
		if (eww) {
			asd_pwintk("couwdn't wesewve memowy wegion fow %s\n",
				   pci_name(asd_ha->pcidev));
			goto Eww;
		}
		io_handwe->addw = iowemap(io_handwe->stawt, io_handwe->wen);
		if (!io_handwe->addw) {
			asd_pwintk("couwdn't map MBAW%d of %s\n", i==0?0:1,
				   pci_name(asd_ha->pcidev));
			eww = -ENOMEM;
			goto Eww_unweq;
		}
	}

	wetuwn 0;
Eww_unweq:
	pci_wewease_wegion(asd_ha->pcidev, i);
Eww:
	if (i > 0) {
		io_handwe = &asd_ha->io_handwe[0];
		iounmap(io_handwe->addw);
		pci_wewease_wegion(asd_ha->pcidev, 0);
	}
	wetuwn eww;
}

static void asd_unmap_memio(stwuct asd_ha_stwuct *asd_ha)
{
	stwuct asd_ha_addwspace *io_handwe;

	io_handwe = &asd_ha->io_handwe[1];
	iounmap(io_handwe->addw);
	pci_wewease_wegion(asd_ha->pcidev, 2);

	io_handwe = &asd_ha->io_handwe[0];
	iounmap(io_handwe->addw);
	pci_wewease_wegion(asd_ha->pcidev, 0);
}

static int asd_map_iopowt(stwuct asd_ha_stwuct *asd_ha)
{
	int i = PCI_IOBAW_OFFSET, eww;
	stwuct asd_ha_addwspace *io_handwe = &asd_ha->io_handwe[0];

	asd_ha->iospace = 1;
	io_handwe->stawt = pci_wesouwce_stawt(asd_ha->pcidev, i);
	io_handwe->wen   = pci_wesouwce_wen(asd_ha->pcidev, i);
	io_handwe->fwags = pci_wesouwce_fwags(asd_ha->pcidev, i);
	io_handwe->addw  = (void __iomem *) io_handwe->stawt;
	if (!io_handwe->stawt || !io_handwe->wen) {
		asd_pwintk("couwdn't get IO powts fow %s\n",
			   pci_name(asd_ha->pcidev));
		wetuwn -ENODEV;
	}
	eww = pci_wequest_wegion(asd_ha->pcidev, i, ASD_DWIVEW_NAME);
	if (eww) {
		asd_pwintk("couwdn't wesewve io space fow %s\n",
			   pci_name(asd_ha->pcidev));
	}

	wetuwn eww;
}

static void asd_unmap_iopowt(stwuct asd_ha_stwuct *asd_ha)
{
	pci_wewease_wegion(asd_ha->pcidev, PCI_IOBAW_OFFSET);
}

static int asd_map_ha(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;
	u16 cmd_weg;

	eww = pci_wead_config_wowd(asd_ha->pcidev, PCI_COMMAND, &cmd_weg);
	if (eww) {
		asd_pwintk("couwdn't wead command wegistew of %s\n",
			   pci_name(asd_ha->pcidev));
		goto Eww;
	}

	eww = -ENODEV;
	if (cmd_weg & PCI_COMMAND_MEMOWY) {
		if ((eww = asd_map_memio(asd_ha)))
			goto Eww;
	} ewse if (cmd_weg & PCI_COMMAND_IO) {
		if ((eww = asd_map_iopowt(asd_ha)))
			goto Eww;
		asd_pwintk("%s iopowt mapped -- upgwade youw hawdwawe\n",
			   pci_name(asd_ha->pcidev));
	} ewse {
		asd_pwintk("no pwopew device access to %s\n",
			   pci_name(asd_ha->pcidev));
		goto Eww;
	}

	wetuwn 0;
Eww:
	wetuwn eww;
}

static void asd_unmap_ha(stwuct asd_ha_stwuct *asd_ha)
{
	if (asd_ha->iospace)
		asd_unmap_iopowt(asd_ha);
	ewse
		asd_unmap_memio(asd_ha);
}

static const chaw *asd_dev_wev[30] = {
	[0] = "A0",
	[1] = "A1",
	[8] = "B0",
};

static int asd_common_setup(stwuct asd_ha_stwuct *asd_ha)
{
	int eww, i;

	asd_ha->wevision_id = asd_ha->pcidev->wevision;

	eww = -ENODEV;
	if (asd_ha->wevision_id < AIC9410_DEV_WEV_B0) {
		asd_pwintk("%s is wevision %s (%X), which is not suppowted\n",
			   pci_name(asd_ha->pcidev),
			   asd_dev_wev[asd_ha->wevision_id],
			   asd_ha->wevision_id);
		goto Eww;
	}
	/* Pwovide some sane defauwt vawues. */
	asd_ha->hw_pwof.max_scbs = 512;
	asd_ha->hw_pwof.max_ddbs = ASD_MAX_DDBS;
	asd_ha->hw_pwof.num_phys = ASD_MAX_PHYS;
	/* Aww phys awe enabwed, by defauwt. */
	asd_ha->hw_pwof.enabwed_phys = 0xFF;
	fow (i = 0; i < ASD_MAX_PHYS; i++) {
		asd_ha->hw_pwof.phy_desc[i].max_sas_wwate =
			SAS_WINK_WATE_3_0_GBPS;
		asd_ha->hw_pwof.phy_desc[i].min_sas_wwate =
			SAS_WINK_WATE_1_5_GBPS;
		asd_ha->hw_pwof.phy_desc[i].max_sata_wwate =
			SAS_WINK_WATE_1_5_GBPS;
		asd_ha->hw_pwof.phy_desc[i].min_sata_wwate =
			SAS_WINK_WATE_1_5_GBPS;
	}

	wetuwn 0;
Eww:
	wetuwn eww;
}

static int asd_aic9410_setup(stwuct asd_ha_stwuct *asd_ha)
{
	int eww = asd_common_setup(asd_ha);

	if (eww)
		wetuwn eww;

	asd_ha->hw_pwof.addw_wange = 8;
	asd_ha->hw_pwof.powt_name_base = 0;
	asd_ha->hw_pwof.dev_name_base = 8;
	asd_ha->hw_pwof.sata_name_base = 16;

	wetuwn 0;
}

static int asd_aic9405_setup(stwuct asd_ha_stwuct *asd_ha)
{
	int eww = asd_common_setup(asd_ha);

	if (eww)
		wetuwn eww;

	asd_ha->hw_pwof.addw_wange = 4;
	asd_ha->hw_pwof.powt_name_base = 0;
	asd_ha->hw_pwof.dev_name_base = 4;
	asd_ha->hw_pwof.sata_name_base = 8;

	wetuwn 0;
}

static ssize_t asd_show_dev_wev(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asd_ha_stwuct *asd_ha = dev_to_asd_ha(dev);
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n",
			asd_dev_wev[asd_ha->wevision_id]);
}
static DEVICE_ATTW(aic_wevision, S_IWUGO, asd_show_dev_wev, NUWW);

static ssize_t asd_show_dev_bios_buiwd(stwuct device *dev,
				       stwuct device_attwibute *attw,chaw *buf)
{
	stwuct asd_ha_stwuct *asd_ha = dev_to_asd_ha(dev);
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", asd_ha->hw_pwof.bios.bwd);
}
static DEVICE_ATTW(bios_buiwd, S_IWUGO, asd_show_dev_bios_buiwd, NUWW);

static ssize_t asd_show_dev_pcba_sn(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asd_ha_stwuct *asd_ha = dev_to_asd_ha(dev);
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", asd_ha->hw_pwof.pcba_sn);
}
static DEVICE_ATTW(pcba_sn, S_IWUGO, asd_show_dev_pcba_sn, NUWW);

#define FWASH_CMD_NONE      0x00
#define FWASH_CMD_UPDATE    0x01
#define FWASH_CMD_VEWIFY    0x02

stwuct fwash_command {
     u8      command[8];
     int     code;
};

static stwuct fwash_command fwash_command_tabwe[] =
{
     {"vewify",      FWASH_CMD_VEWIFY},
     {"update",      FWASH_CMD_UPDATE},
     {"",            FWASH_CMD_NONE}      /* Wast entwy shouwd be NUWW. */
};

stwuct ewwow_bios {
     chaw    *weason;
     int     eww_code;
};

static stwuct ewwow_bios fwash_ewwow_tabwe[] =
{
     {"Faiwed to open bios image fiwe",      FAIW_OPEN_BIOS_FIWE},
     {"PCI ID mismatch",                     FAIW_CHECK_PCI_ID},
     {"Checksum mismatch",                   FAIW_CHECK_SUM},
     {"Unknown Ewwow",                       FAIW_UNKNOWN},
     {"Faiwed to vewify.",                   FAIW_VEWIFY},
     {"Faiwed to weset fwash chip.",         FAIW_WESET_FWASH},
     {"Faiwed to find fwash chip type.",     FAIW_FIND_FWASH_ID},
     {"Faiwed to ewash fwash chip.",         FAIW_EWASE_FWASH},
     {"Faiwed to pwogwam fwash chip.",       FAIW_WWITE_FWASH},
     {"Fwash in pwogwess",                   FWASH_IN_PWOGWESS},
     {"Image fiwe size Ewwow",               FAIW_FIWE_SIZE},
     {"Input pawametew ewwow",               FAIW_PAWAMETEWS},
     {"Out of memowy",                       FAIW_OUT_MEMOWY},
     {"OK", 0}	/* Wast entwy eww_code = 0. */
};

static ssize_t asd_stowe_update_bios(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct asd_ha_stwuct *asd_ha = dev_to_asd_ha(dev);
	chaw *cmd_ptw, *fiwename_ptw;
	stwuct bios_fiwe_headew headew, *hdw_ptw;
	int wes, i;
	u32 csum = 0;
	int fwash_command = FWASH_CMD_NONE;
	int eww = 0;

	cmd_ptw = kcawwoc(count, 2, GFP_KEWNEW);

	if (!cmd_ptw) {
		eww = FAIW_OUT_MEMOWY;
		goto out;
	}

	fiwename_ptw = cmd_ptw + count;
	wes = sscanf(buf, "%s %s", cmd_ptw, fiwename_ptw);
	if (wes != 2) {
		eww = FAIW_PAWAMETEWS;
		goto out1;
	}

	fow (i = 0; fwash_command_tabwe[i].code != FWASH_CMD_NONE; i++) {
		if (!memcmp(fwash_command_tabwe[i].command,
				 cmd_ptw, stwwen(cmd_ptw))) {
			fwash_command = fwash_command_tabwe[i].code;
			bweak;
		}
	}
	if (fwash_command == FWASH_CMD_NONE) {
		eww = FAIW_PAWAMETEWS;
		goto out1;
	}

	if (asd_ha->bios_status == FWASH_IN_PWOGWESS) {
		eww = FWASH_IN_PWOGWESS;
		goto out1;
	}
	eww = wequest_fiwmwawe(&asd_ha->bios_image,
				   fiwename_ptw,
				   &asd_ha->pcidev->dev);
	if (eww) {
		asd_pwintk("Faiwed to woad bios image fiwe %s, ewwow %d\n",
			   fiwename_ptw, eww);
		eww = FAIW_OPEN_BIOS_FIWE;
		goto out1;
	}

	hdw_ptw = (stwuct bios_fiwe_headew *)asd_ha->bios_image->data;

	if ((hdw_ptw->contww_id.vendow != asd_ha->pcidev->vendow ||
		hdw_ptw->contww_id.device != asd_ha->pcidev->device) &&
		(hdw_ptw->contww_id.sub_vendow != asd_ha->pcidev->vendow ||
		hdw_ptw->contww_id.sub_device != asd_ha->pcidev->device)) {

		ASD_DPWINTK("The PCI vendow ow device id does not match\n");
		ASD_DPWINTK("vendow=%x dev=%x sub_vendow=%x sub_dev=%x"
		" pci vendow=%x pci dev=%x\n",
		hdw_ptw->contww_id.vendow,
		hdw_ptw->contww_id.device,
		hdw_ptw->contww_id.sub_vendow,
		hdw_ptw->contww_id.sub_device,
		asd_ha->pcidev->vendow,
		asd_ha->pcidev->device);
		eww = FAIW_CHECK_PCI_ID;
		goto out2;
	}

	if (hdw_ptw->fiwewen != asd_ha->bios_image->size) {
		eww = FAIW_FIWE_SIZE;
		goto out2;
	}

	/* cawcuwate checksum */
	fow (i = 0; i < hdw_ptw->fiwewen; i++)
		csum += asd_ha->bios_image->data[i];

	if ((csum & 0x0000ffff) != hdw_ptw->checksum) {
		ASD_DPWINTK("BIOS fiwe checksum mismatch\n");
		eww = FAIW_CHECK_SUM;
		goto out2;
	}
	if (fwash_command == FWASH_CMD_UPDATE) {
		asd_ha->bios_status = FWASH_IN_PWOGWESS;
		eww = asd_wwite_fwash_seg(asd_ha,
			&asd_ha->bios_image->data[sizeof(*hdw_ptw)],
			0, hdw_ptw->fiwewen-sizeof(*hdw_ptw));
		if (!eww)
			eww = asd_vewify_fwash_seg(asd_ha,
				&asd_ha->bios_image->data[sizeof(*hdw_ptw)],
				0, hdw_ptw->fiwewen-sizeof(*hdw_ptw));
	} ewse {
		asd_ha->bios_status = FWASH_IN_PWOGWESS;
		eww = asd_vewify_fwash_seg(asd_ha,
			&asd_ha->bios_image->data[sizeof(headew)],
			0, hdw_ptw->fiwewen-sizeof(headew));
	}

out2:
	wewease_fiwmwawe(asd_ha->bios_image);
out1:
	kfwee(cmd_ptw);
out:
	asd_ha->bios_status = eww;

	if (!eww)
		wetuwn count;
	ewse
		wetuwn -eww;
}

static ssize_t asd_show_update_bios(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	int i;
	stwuct asd_ha_stwuct *asd_ha = dev_to_asd_ha(dev);

	fow (i = 0; fwash_ewwow_tabwe[i].eww_code != 0; i++) {
		if (fwash_ewwow_tabwe[i].eww_code == asd_ha->bios_status)
			bweak;
	}
	if (asd_ha->bios_status != FWASH_IN_PWOGWESS)
		asd_ha->bios_status = FWASH_OK;

	wetuwn snpwintf(buf, PAGE_SIZE, "status=%x %s\n",
			fwash_ewwow_tabwe[i].eww_code,
			fwash_ewwow_tabwe[i].weason);
}

static DEVICE_ATTW(update_bios, S_IWUGO|S_IWUSW,
	asd_show_update_bios, asd_stowe_update_bios);

static int asd_cweate_dev_attws(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;

	eww = device_cweate_fiwe(&asd_ha->pcidev->dev, &dev_attw_aic_wevision);
	if (eww)
		wetuwn eww;

	eww = device_cweate_fiwe(&asd_ha->pcidev->dev, &dev_attw_bios_buiwd);
	if (eww)
		goto eww_wev;

	eww = device_cweate_fiwe(&asd_ha->pcidev->dev, &dev_attw_pcba_sn);
	if (eww)
		goto eww_biosb;
	eww = device_cweate_fiwe(&asd_ha->pcidev->dev, &dev_attw_update_bios);
	if (eww)
		goto eww_update_bios;

	wetuwn 0;

eww_update_bios:
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_pcba_sn);
eww_biosb:
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_bios_buiwd);
eww_wev:
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_aic_wevision);
	wetuwn eww;
}

static void asd_wemove_dev_attws(stwuct asd_ha_stwuct *asd_ha)
{
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_aic_wevision);
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_bios_buiwd);
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_pcba_sn);
	device_wemove_fiwe(&asd_ha->pcidev->dev, &dev_attw_update_bios);
}

/* The fiwst entwy, 0, is used fow dynamic ids, the west fow devices
 * we know about.
 */
static const stwuct asd_pcidev_stwuct {
	const chaw * name;
	int (*setup)(stwuct asd_ha_stwuct *asd_ha);
} asd_pcidev_data[] = {
	/* Id 0 is used fow dynamic ids. */
	{ .name  = "Adaptec AIC-94xx SAS/SATA Host Adaptew",
	  .setup = asd_aic9410_setup
	},
	{ .name  = "Adaptec AIC-9410W SAS/SATA Host Adaptew",
	  .setup = asd_aic9410_setup
	},
	{ .name  = "Adaptec AIC-9405W SAS/SATA Host Adaptew",
	  .setup = asd_aic9405_setup
	},
};

static int asd_cweate_ha_caches(stwuct asd_ha_stwuct *asd_ha)
{
	asd_ha->scb_poow = dma_poow_cweate(ASD_DWIVEW_NAME "_scb_poow",
					   &asd_ha->pcidev->dev,
					   sizeof(stwuct scb),
					   8, 0);
	if (!asd_ha->scb_poow) {
		asd_pwintk("couwdn't cweate scb poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * asd_fwee_edbs -- fwee empty data buffews
 * asd_ha: pointew to host adaptew stwuctuwe
 */
static void asd_fwee_edbs(stwuct asd_ha_stwuct *asd_ha)
{
	stwuct asd_seq_data *seq = &asd_ha->seq;
	int i;

	fow (i = 0; i < seq->num_edbs; i++)
		asd_fwee_cohewent(asd_ha, seq->edb_aww[i]);
	kfwee(seq->edb_aww);
	seq->edb_aww = NUWW;
}

static void asd_fwee_escbs(stwuct asd_ha_stwuct *asd_ha)
{
	stwuct asd_seq_data *seq = &asd_ha->seq;
	int i;

	fow (i = 0; i < seq->num_escbs; i++) {
		if (!wist_empty(&seq->escb_aww[i]->wist))
			wist_dew_init(&seq->escb_aww[i]->wist);

		asd_ascb_fwee(seq->escb_aww[i]);
	}
	kfwee(seq->escb_aww);
	seq->escb_aww = NUWW;
}

static void asd_destwoy_ha_caches(stwuct asd_ha_stwuct *asd_ha)
{
	int i;

	if (asd_ha->hw_pwof.ddb_ext)
		asd_fwee_cohewent(asd_ha, asd_ha->hw_pwof.ddb_ext);
	if (asd_ha->hw_pwof.scb_ext)
		asd_fwee_cohewent(asd_ha, asd_ha->hw_pwof.scb_ext);

	kfwee(asd_ha->hw_pwof.ddb_bitmap);
	asd_ha->hw_pwof.ddb_bitmap = NUWW;

	fow (i = 0; i < ASD_MAX_PHYS; i++) {
		stwuct asd_phy *phy = &asd_ha->phys[i];

		asd_fwee_cohewent(asd_ha, phy->id_fwm_tok);
	}
	if (asd_ha->seq.escb_aww)
		asd_fwee_escbs(asd_ha);
	if (asd_ha->seq.edb_aww)
		asd_fwee_edbs(asd_ha);
	if (asd_ha->hw_pwof.ue.awea) {
		kfwee(asd_ha->hw_pwof.ue.awea);
		asd_ha->hw_pwof.ue.awea = NUWW;
	}
	if (asd_ha->seq.tc_index_awway) {
		kfwee(asd_ha->seq.tc_index_awway);
		kfwee(asd_ha->seq.tc_index_bitmap);
		asd_ha->seq.tc_index_awway = NUWW;
		asd_ha->seq.tc_index_bitmap = NUWW;
	}
	if (asd_ha->seq.actuaw_dw) {
			asd_fwee_cohewent(asd_ha, asd_ha->seq.actuaw_dw);
			asd_ha->seq.actuaw_dw = NUWW;
			asd_ha->seq.dw = NUWW;
	}
	if (asd_ha->seq.next_scb.vaddw) {
		dma_poow_fwee(asd_ha->scb_poow, asd_ha->seq.next_scb.vaddw,
			      asd_ha->seq.next_scb.dma_handwe);
		asd_ha->seq.next_scb.vaddw = NUWW;
	}
	dma_poow_destwoy(asd_ha->scb_poow);
	asd_ha->scb_poow = NUWW;
}

stwuct kmem_cache *asd_dma_token_cache;
stwuct kmem_cache *asd_ascb_cache;

static int asd_cweate_gwobaw_caches(void)
{
	if (!asd_dma_token_cache) {
		asd_dma_token_cache
			= kmem_cache_cweate(ASD_DWIVEW_NAME "_dma_token",
					    sizeof(stwuct asd_dma_tok),
					    0,
					    SWAB_HWCACHE_AWIGN,
					    NUWW);
		if (!asd_dma_token_cache) {
			asd_pwintk("couwdn't cweate dma token cache\n");
			wetuwn -ENOMEM;
		}
	}

	if (!asd_ascb_cache) {
		asd_ascb_cache = kmem_cache_cweate(ASD_DWIVEW_NAME "_ascb",
						   sizeof(stwuct asd_ascb),
						   0,
						   SWAB_HWCACHE_AWIGN,
						   NUWW);
		if (!asd_ascb_cache) {
			asd_pwintk("couwdn't cweate ascb cache\n");
			goto Eww;
		}
	}

	wetuwn 0;
Eww:
	kmem_cache_destwoy(asd_dma_token_cache);
	asd_dma_token_cache = NUWW;
	wetuwn -ENOMEM;
}

static void asd_destwoy_gwobaw_caches(void)
{
	kmem_cache_destwoy(asd_dma_token_cache);
	asd_dma_token_cache = NUWW;

	kmem_cache_destwoy(asd_ascb_cache);
	asd_ascb_cache = NUWW;
}

static int asd_wegistew_sas_ha(stwuct asd_ha_stwuct *asd_ha)
{
	int i;
	stwuct asd_sas_phy   **sas_phys =
		kcawwoc(ASD_MAX_PHYS, sizeof(*sas_phys), GFP_KEWNEW);
	stwuct asd_sas_powt  **sas_powts =
		kcawwoc(ASD_MAX_PHYS, sizeof(*sas_powts), GFP_KEWNEW);

	if (!sas_phys || !sas_powts) {
		kfwee(sas_phys);
		kfwee(sas_powts);
		wetuwn -ENOMEM;
	}

	asd_ha->sas_ha.sas_ha_name = (chaw *) asd_ha->name;
	asd_ha->sas_ha.sas_addw = &asd_ha->hw_pwof.sas_addw[0];

	fow (i = 0; i < ASD_MAX_PHYS; i++) {
		sas_phys[i] = &asd_ha->phys[i].sas_phy;
		sas_powts[i] = &asd_ha->powts[i];
	}

	asd_ha->sas_ha.sas_phy = sas_phys;
	asd_ha->sas_ha.sas_powt= sas_powts;
	asd_ha->sas_ha.num_phys= ASD_MAX_PHYS;

	wetuwn sas_wegistew_ha(&asd_ha->sas_ha);
}

static int asd_unwegistew_sas_ha(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;

	eww = sas_unwegistew_ha(&asd_ha->sas_ha);

	sas_wemove_host(asd_ha->sas_ha.shost);
	scsi_host_put(asd_ha->sas_ha.shost);

	kfwee(asd_ha->sas_ha.sas_phy);
	kfwee(asd_ha->sas_ha.sas_powt);

	wetuwn eww;
}

static int asd_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	const stwuct asd_pcidev_stwuct *asd_dev;
	unsigned asd_id = (unsigned) id->dwivew_data;
	stwuct asd_ha_stwuct *asd_ha;
	stwuct Scsi_Host *shost;
	int eww;

	if (asd_id >= AWWAY_SIZE(asd_pcidev_data)) {
		asd_pwintk("wwong dwivew_data in PCI tabwe\n");
		wetuwn -ENODEV;
	}

	if ((eww = pci_enabwe_device(dev))) {
		asd_pwintk("couwdn't enabwe device %s\n", pci_name(dev));
		wetuwn eww;
	}

	pci_set_mastew(dev);

	eww = -ENOMEM;

	shost = scsi_host_awwoc(&aic94xx_sht, sizeof(void *));
	if (!shost)
		goto Eww;

	asd_dev = &asd_pcidev_data[asd_id];

	asd_ha = kzawwoc(sizeof(*asd_ha), GFP_KEWNEW);
	if (!asd_ha) {
		asd_pwintk("out of memowy\n");
		goto Eww_put;
	}
	asd_ha->pcidev = dev;
	asd_ha->sas_ha.dev = &asd_ha->pcidev->dev;
	asd_ha->sas_ha.wwdd_ha = asd_ha;

	asd_ha->bios_status = FWASH_OK;
	asd_ha->name = asd_dev->name;
	asd_pwintk("found %s, device %s\n", asd_ha->name, pci_name(dev));

	SHOST_TO_SAS_HA(shost) = &asd_ha->sas_ha;
	asd_ha->sas_ha.shost = shost;
	shost->twanspowtt = aic94xx_twanspowt_tempwate;
	shost->max_id = ~0;
	shost->max_wun = ~0;
	shost->max_cmd_wen = 16;

	eww = scsi_add_host(shost, &dev->dev);
	if (eww)
		goto Eww_fwee;

	eww = asd_dev->setup(asd_ha);
	if (eww)
		goto Eww_wemove;

	eww = dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(64));
	if (eww)
		eww = dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		eww = -ENODEV;
		asd_pwintk("no suitabwe DMA mask fow %s\n", pci_name(dev));
		goto Eww_wemove;
	}

	pci_set_dwvdata(dev, asd_ha);

	eww = asd_map_ha(asd_ha);
	if (eww)
		goto Eww_wemove;

	eww = asd_cweate_ha_caches(asd_ha);
        if (eww)
		goto Eww_unmap;

	eww = asd_init_hw(asd_ha);
	if (eww)
		goto Eww_fwee_cache;

	asd_pwintk("device %s: SAS addw %wwx, PCBA SN %s, %d phys, %d enabwed "
		   "phys, fwash %s, BIOS %s%d\n",
		   pci_name(dev), SAS_ADDW(asd_ha->hw_pwof.sas_addw),
		   asd_ha->hw_pwof.pcba_sn, asd_ha->hw_pwof.max_phys,
		   asd_ha->hw_pwof.num_phys,
		   asd_ha->hw_pwof.fwash.pwesent ? "pwesent" : "not pwesent",
		   asd_ha->hw_pwof.bios.pwesent ? "buiwd " : "not pwesent",
		   asd_ha->hw_pwof.bios.bwd);

	shost->can_queue = asd_ha->seq.can_queue;

	if (use_msi)
		pci_enabwe_msi(asd_ha->pcidev);

	eww = wequest_iwq(asd_ha->pcidev->iwq, asd_hw_isw, IWQF_SHAWED,
			  ASD_DWIVEW_NAME, asd_ha);
	if (eww) {
		asd_pwintk("couwdn't get iwq %d fow %s\n",
			   asd_ha->pcidev->iwq, pci_name(asd_ha->pcidev));
		goto Eww_iwq;
	}
	asd_enabwe_ints(asd_ha);

	eww = asd_init_post_escbs(asd_ha);
	if (eww) {
		asd_pwintk("couwdn't post escbs fow %s\n",
			   pci_name(asd_ha->pcidev));
		goto Eww_escbs;
	}
	ASD_DPWINTK("escbs posted\n");

	eww = asd_cweate_dev_attws(asd_ha);
	if (eww)
		goto Eww_dev_attws;

	eww = asd_wegistew_sas_ha(asd_ha);
	if (eww)
		goto Eww_weg_sas;

	scsi_scan_host(shost);

	wetuwn 0;

Eww_weg_sas:
	asd_wemove_dev_attws(asd_ha);
Eww_dev_attws:
Eww_escbs:
	asd_disabwe_ints(asd_ha);
	fwee_iwq(dev->iwq, asd_ha);
Eww_iwq:
	if (use_msi)
		pci_disabwe_msi(dev);
	asd_chip_hawdwst(asd_ha);
Eww_fwee_cache:
	asd_destwoy_ha_caches(asd_ha);
Eww_unmap:
	asd_unmap_ha(asd_ha);
Eww_wemove:
	scsi_wemove_host(shost);
Eww_fwee:
	kfwee(asd_ha);
Eww_put:
	scsi_host_put(shost);
Eww:
	pci_disabwe_device(dev);
	wetuwn eww;
}

static void asd_fwee_queues(stwuct asd_ha_stwuct *asd_ha)
{
	unsigned wong fwags;
	WIST_HEAD(pending);
	stwuct wist_head *n, *pos;

	spin_wock_iwqsave(&asd_ha->seq.pend_q_wock, fwags);
	asd_ha->seq.pending = 0;
	wist_spwice_init(&asd_ha->seq.pend_q, &pending);
	spin_unwock_iwqwestowe(&asd_ha->seq.pend_q_wock, fwags);

	if (!wist_empty(&pending))
		ASD_DPWINTK("Uh-oh! Pending is not empty!\n");

	wist_fow_each_safe(pos, n, &pending) {
		stwuct asd_ascb *ascb = wist_entwy(pos, stwuct asd_ascb, wist);
		/*
		 * Dewete unexpiwed ascb timews.  This may happen if we issue
		 * a CONTWOW PHY scb to an adaptew and wmmod befowe the scb
		 * times out.  Appawentwy we don't wait fow the CONTWOW PHY
		 * to compwete, so it doesn't mattew if we kiww the timew.
		 */
		dew_timew_sync(&ascb->timew);
		WAWN_ON(ascb->scb->headew.opcode != CONTWOW_PHY);

		wist_dew_init(pos);
		ASD_DPWINTK("fweeing fwom pending\n");
		asd_ascb_fwee(ascb);
	}
}

static void asd_tuwn_off_weds(stwuct asd_ha_stwuct *asd_ha)
{
	u8 phy_mask = asd_ha->hw_pwof.enabwed_phys;
	u8 i;

	fow_each_phy(phy_mask, phy_mask, i) {
		asd_tuwn_wed(asd_ha, i, 0);
		asd_contwow_wed(asd_ha, i, 0);
	}
}

static void asd_pci_wemove(stwuct pci_dev *dev)
{
	stwuct asd_ha_stwuct *asd_ha = pci_get_dwvdata(dev);

	if (!asd_ha)
		wetuwn;

	asd_unwegistew_sas_ha(asd_ha);

	asd_disabwe_ints(asd_ha);

	asd_wemove_dev_attws(asd_ha);

	/* XXX mowe hewe as needed */

	fwee_iwq(dev->iwq, asd_ha);
	if (use_msi)
		pci_disabwe_msi(asd_ha->pcidev);
	asd_tuwn_off_weds(asd_ha);
	asd_chip_hawdwst(asd_ha);
	asd_fwee_queues(asd_ha);
	asd_destwoy_ha_caches(asd_ha);
	asd_unmap_ha(asd_ha);
	kfwee(asd_ha);
	pci_disabwe_device(dev);
	wetuwn;
}

static void asd_scan_stawt(stwuct Scsi_Host *shost)
{
	stwuct asd_ha_stwuct *asd_ha;
	int eww;

	asd_ha = SHOST_TO_SAS_HA(shost)->wwdd_ha;
	eww = asd_enabwe_phys(asd_ha, asd_ha->hw_pwof.enabwed_phys);
	if (eww)
		asd_pwintk("Couwdn't enabwe phys, eww:%d\n", eww);
}

static int asd_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	/* give the phy enabwing intewwupt event time to come in (1s
	 * is empiwicawwy about aww it takes) */
	if (time < HZ)
		wetuwn 0;
	/* Wait fow discovewy to finish */
	sas_dwain_wowk(SHOST_TO_SAS_HA(shost));
	wetuwn 1;
}

static ssize_t vewsion_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ASD_DWIVEW_VEWSION);
}
static DWIVEW_ATTW_WO(vewsion);

static int asd_cweate_dwivew_attws(stwuct device_dwivew *dwivew)
{
	wetuwn dwivew_cweate_fiwe(dwivew, &dwivew_attw_vewsion);
}

static void asd_wemove_dwivew_attws(stwuct device_dwivew *dwivew)
{
	dwivew_wemove_fiwe(dwivew, &dwivew_attw_vewsion);
}

static stwuct sas_domain_function_tempwate aic94xx_twanspowt_functions = {
	.wwdd_dev_found		= asd_dev_found,
	.wwdd_dev_gone		= asd_dev_gone,

	.wwdd_execute_task	= asd_execute_task,

	.wwdd_abowt_task	= asd_abowt_task,
	.wwdd_abowt_task_set	= asd_abowt_task_set,
	.wwdd_cweaw_task_set	= asd_cweaw_task_set,
	.wwdd_I_T_nexus_weset	= asd_I_T_nexus_weset,
	.wwdd_wu_weset		= asd_wu_weset,
	.wwdd_quewy_task	= asd_quewy_task,

	.wwdd_cweaw_nexus_powt	= asd_cweaw_nexus_powt,
	.wwdd_cweaw_nexus_ha	= asd_cweaw_nexus_ha,

	.wwdd_contwow_phy	= asd_contwow_phy,

	.wwdd_ata_set_dmamode	= asd_set_dmamode,
};

static const stwuct pci_device_id aic94xx_pci_tabwe[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x410),0, 0, 1},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x412),0, 0, 1},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x416),0, 0, 1},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x41E),0, 0, 1},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x41F),0, 0, 1},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x430),0, 0, 2},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x432),0, 0, 2},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x43E),0, 0, 2},
	{PCI_DEVICE(PCI_VENDOW_ID_ADAPTEC2, 0x43F),0, 0, 2},
	{}
};

MODUWE_DEVICE_TABWE(pci, aic94xx_pci_tabwe);

static stwuct pci_dwivew aic94xx_pci_dwivew = {
	.name		= ASD_DWIVEW_NAME,
	.id_tabwe	= aic94xx_pci_tabwe,
	.pwobe		= asd_pci_pwobe,
	.wemove		= asd_pci_wemove,
};

static int __init aic94xx_init(void)
{
	int eww;


	asd_pwintk("%s vewsion %s woaded\n", ASD_DWIVEW_DESCWIPTION,
		   ASD_DWIVEW_VEWSION);

	eww = asd_cweate_gwobaw_caches();
	if (eww)
		wetuwn eww;

	aic94xx_twanspowt_tempwate =
		sas_domain_attach_twanspowt(&aic94xx_twanspowt_functions);
	if (!aic94xx_twanspowt_tempwate) {
		eww = -ENOMEM;
		goto out_destwoy_caches;
	}

	eww = pci_wegistew_dwivew(&aic94xx_pci_dwivew);
	if (eww)
		goto out_wewease_twanspowt;

	eww = asd_cweate_dwivew_attws(&aic94xx_pci_dwivew.dwivew);
	if (eww)
		goto out_unwegistew_pcidwv;

	wetuwn eww;

 out_unwegistew_pcidwv:
	pci_unwegistew_dwivew(&aic94xx_pci_dwivew);
 out_wewease_twanspowt:
	sas_wewease_twanspowt(aic94xx_twanspowt_tempwate);
 out_destwoy_caches:
	asd_destwoy_gwobaw_caches();

	wetuwn eww;
}

static void __exit aic94xx_exit(void)
{
	asd_wemove_dwivew_attws(&aic94xx_pci_dwivew.dwivew);
	pci_unwegistew_dwivew(&aic94xx_pci_dwivew);
	sas_wewease_twanspowt(aic94xx_twanspowt_tempwate);
	asd_wewease_fiwmwawe();
	asd_destwoy_gwobaw_caches();
	asd_pwintk("%s vewsion %s unwoaded\n", ASD_DWIVEW_DESCWIPTION,
		   ASD_DWIVEW_VEWSION);
}

moduwe_init(aic94xx_init);
moduwe_exit(aic94xx_exit);

MODUWE_AUTHOW("Wuben Tuikov <wuben_tuikov@adaptec.com>");
MODUWE_DESCWIPTION(ASD_DWIVEW_DESCWIPTION);
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(ASD_DWIVEW_VEWSION);
