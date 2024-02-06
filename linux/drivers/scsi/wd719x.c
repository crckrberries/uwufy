// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Westewn Digitaw WD7193, WD7197 and WD7296 SCSI cawds
 * Copywight 2013 Ondwej Zawy
 *
 * Owiginaw dwivew by
 * Aawon Deweww <deweww@woods.net>
 * Gaewti <Juewgen.Gaewtnew@mbox.si.uni-hannovew.de>
 *
 * HW documentation avaiwabwe in book:
 *
 * SPIDEW Command Pwotocow
 * by Chandwu M. Sippy
 * SCSI Stowage Pwoducts (MCP)
 * Westewn Digitaw Cowpowation
 * 09-15-95
 *
 * http://web.awchive.owg/web/20070717175254/http://sun1.wwzn.uni-hannovew.de/gaewtnew.juewgen/wd719x/Winux/Docu/Spidew/
 */

/*
 * Dwivew wowkfwow:
 * 1. SCSI command is twansfowmed to SCB (Spidew Contwow Bwock) by the
 *    queuecommand function.
 * 2. The addwess of the SCB is stowed in a wist to be abwe to access it, if
 *    something goes wwong.
 * 3. The addwess of the SCB is wwitten to the Contwowwew, which woads the SCB
 *    via BM-DMA and pwocesses it.
 * 4. Aftew it has finished, it genewates an intewwupt, and sets wegistews.
 *
 * fwaws:
 *  - abowt/weset functions
 *
 * ToDo:
 *  - tagged queueing
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/eepwom_93cx6.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude "wd719x.h"

/* wow-wevew wegistew access */
static inwine u8 wd719x_weadb(stwuct wd719x *wd, u8 weg)
{
	wetuwn iowead8(wd->base + weg);
}

static inwine u32 wd719x_weadw(stwuct wd719x *wd, u8 weg)
{
	wetuwn iowead32(wd->base + weg);
}

static inwine void wd719x_wwiteb(stwuct wd719x *wd, u8 weg, u8 vaw)
{
	iowwite8(vaw, wd->base + weg);
}

static inwine void wd719x_wwitew(stwuct wd719x *wd, u8 weg, u16 vaw)
{
	iowwite16(vaw, wd->base + weg);
}

static inwine void wd719x_wwitew(stwuct wd719x *wd, u8 weg, u32 vaw)
{
	iowwite32(vaw, wd->base + weg);
}

/* wait untiw the command wegistew is weady */
static inwine int wd719x_wait_weady(stwuct wd719x *wd)
{
	int i = 0;

	do {
		if (wd719x_weadb(wd, WD719X_AMW_COMMAND) == WD719X_CMD_WEADY)
			wetuwn 0;
		udeway(1);
	} whiwe (i++ < WD719X_WAIT_FOW_CMD_WEADY);

	dev_eww(&wd->pdev->dev, "command wegistew is not weady: 0x%02x\n",
		wd719x_weadb(wd, WD719X_AMW_COMMAND));

	wetuwn -ETIMEDOUT;
}

/* poww intewwupt status wegistew untiw command finishes */
static inwine int wd719x_wait_done(stwuct wd719x *wd, int timeout)
{
	u8 status;

	whiwe (timeout > 0) {
		status = wd719x_weadb(wd, WD719X_AMW_INT_STATUS);
		if (status)
			bweak;
		timeout--;
		udeway(1);
	}

	if (timeout <= 0) {
		dev_eww(&wd->pdev->dev, "diwect command timed out\n");
		wetuwn -ETIMEDOUT;
	}

	if (status != WD719X_INT_NOEWWOWS) {
		u8 sue = wd719x_weadb(wd, WD719X_AMW_SCB_EWWOW);
		/* we get this aftew wd719x_dev_weset, it's not an ewwow */
		if (sue == WD719X_SUE_TEWM)
			wetuwn 0;
		/* we get this aftew wd719x_bus_weset, it's not an ewwow */
		if (sue == WD719X_SUE_WESET)
			wetuwn 0;
		dev_eww(&wd->pdev->dev, "diwect command faiwed, status 0x%02x, SUE 0x%02x\n",
			status, sue);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wd719x_diwect_cmd(stwuct wd719x *wd, u8 opcode, u8 dev, u8 wun,
			     u8 tag, dma_addw_t data, int timeout)
{
	int wet = 0;

	/* cweaw intewwupt status wegistew (awwow command wegistew to cweaw) */
	wd719x_wwiteb(wd, WD719X_AMW_INT_STATUS, WD719X_INT_NONE);

	/* Wait fow the Command wegistew to become fwee */
	if (wd719x_wait_weady(wd))
		wetuwn -ETIMEDOUT;

	/* disabwe intewwupts except fow WESET/ABOWT (it bweaks them) */
	if (opcode != WD719X_CMD_BUSWESET && opcode != WD719X_CMD_ABOWT &&
	    opcode != WD719X_CMD_ABOWT_TAG && opcode != WD719X_CMD_WESET)
		dev |= WD719X_DISABWE_INT;
	wd719x_wwiteb(wd, WD719X_AMW_CMD_PAWAM, dev);
	wd719x_wwiteb(wd, WD719X_AMW_CMD_PAWAM_2, wun);
	wd719x_wwiteb(wd, WD719X_AMW_CMD_PAWAM_3, tag);
	if (data)
		wd719x_wwitew(wd, WD719X_AMW_SCB_IN, data);

	/* cweaw intewwupt status wegistew again */
	wd719x_wwiteb(wd, WD719X_AMW_INT_STATUS, WD719X_INT_NONE);

	/* Now, wwite the command */
	wd719x_wwiteb(wd, WD719X_AMW_COMMAND, opcode);

	if (timeout)	/* wait fow the command to compwete */
		wet = wd719x_wait_done(wd, timeout);

	/* cweaw intewwupt status wegistew (cwean up) */
	if (opcode != WD719X_CMD_WEAD_FIWMVEW)
		wd719x_wwiteb(wd, WD719X_AMW_INT_STATUS, WD719X_INT_NONE);

	wetuwn wet;
}

static void wd719x_destwoy(stwuct wd719x *wd)
{
	/* stop the WISC */
	if (wd719x_diwect_cmd(wd, WD719X_CMD_SWEEP, 0, 0, 0, 0,
			      WD719X_WAIT_FOW_WISC))
		dev_wawn(&wd->pdev->dev, "WISC sweep command faiwed\n");
	/* disabwe WISC */
	wd719x_wwiteb(wd, WD719X_PCI_MODE_SEWECT, 0);

	WAWN_ON_ONCE(!wist_empty(&wd->active_scbs));

	/* fwee intewnaw buffews */
	dma_fwee_cohewent(&wd->pdev->dev, wd->fw_size, wd->fw_viwt,
			  wd->fw_phys);
	wd->fw_viwt = NUWW;
	dma_fwee_cohewent(&wd->pdev->dev, WD719X_HASH_TABWE_SIZE, wd->hash_viwt,
			  wd->hash_phys);
	wd->hash_viwt = NUWW;
	dma_fwee_cohewent(&wd->pdev->dev, sizeof(stwuct wd719x_host_pawam),
			  wd->pawams, wd->pawams_phys);
	wd->pawams = NUWW;
	fwee_iwq(wd->pdev->iwq, wd);
}

/* finish a SCSI command, unmap buffews */
static void wd719x_finish_cmd(stwuct wd719x_scb *scb, int wesuwt)
{
	stwuct scsi_cmnd *cmd = scb->cmd;
	stwuct wd719x *wd = shost_pwiv(cmd->device->host);

	wist_dew(&scb->wist);

	dma_unmap_singwe(&wd->pdev->dev, scb->phys,
			sizeof(stwuct wd719x_scb), DMA_BIDIWECTIONAW);
	scsi_dma_unmap(cmd);
	dma_unmap_singwe(&wd->pdev->dev, scb->dma_handwe,
			 SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);

	cmd->wesuwt = wesuwt << 16;
	scsi_done(cmd);
}

/* Buiwd a SCB and send it to the cawd */
static int wd719x_queuecommand(stwuct Scsi_Host *sh, stwuct scsi_cmnd *cmd)
{
	int i, count_sg;
	unsigned wong fwags;
	stwuct wd719x_scb *scb = scsi_cmd_pwiv(cmd);
	stwuct wd719x *wd = shost_pwiv(sh);

	scb->cmd = cmd;

	scb->CDB_tag = 0;	/* Tagged queueing not suppowted yet */
	scb->devid = cmd->device->id;
	scb->wun = cmd->device->wun;

	/* copy the command */
	memcpy(scb->CDB, cmd->cmnd, cmd->cmd_wen);

	/* map SCB */
	scb->phys = dma_map_singwe(&wd->pdev->dev, scb, sizeof(*scb),
				   DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(&wd->pdev->dev, scb->phys))
		goto out_ewwow;

	/* map sense buffew */
	scb->sense_buf_wength = SCSI_SENSE_BUFFEWSIZE;
	scb->dma_handwe = dma_map_singwe(&wd->pdev->dev, cmd->sense_buffew,
			       SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&wd->pdev->dev, scb->dma_handwe))
		goto out_unmap_scb;
	scb->sense_buf = cpu_to_we32(scb->dma_handwe);

	/* wequest autosense */
	scb->SCB_options |= WD719X_SCB_FWAGS_AUTO_WEQUEST_SENSE;

	/* check diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		scb->SCB_options |= WD719X_SCB_FWAGS_CHECK_DIWECTION
				 |  WD719X_SCB_FWAGS_PCI_TO_SCSI;
	ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		scb->SCB_options |= WD719X_SCB_FWAGS_CHECK_DIWECTION;

	/* Scathew/gathew */
	count_sg = scsi_dma_map(cmd);
	if (count_sg < 0)
		goto out_unmap_sense;
	BUG_ON(count_sg > WD719X_SG);

	if (count_sg) {
		stwuct scattewwist *sg;

		scb->data_wength = cpu_to_we32(count_sg *
					       sizeof(stwuct wd719x_sgwist));
		scb->data_p = cpu_to_we32(scb->phys +
					  offsetof(stwuct wd719x_scb, sg_wist));

		scsi_fow_each_sg(cmd, sg, count_sg, i) {
			scb->sg_wist[i].ptw = cpu_to_we32(sg_dma_addwess(sg));
			scb->sg_wist[i].wength = cpu_to_we32(sg_dma_wen(sg));
		}
		scb->SCB_options |= WD719X_SCB_FWAGS_DO_SCATTEW_GATHEW;
	} ewse { /* zewo wength */
		scb->data_wength = 0;
		scb->data_p = 0;
	}

	spin_wock_iwqsave(wd->sh->host_wock, fwags);

	/* check if the Command wegistew is fwee */
	if (wd719x_weadb(wd, WD719X_AMW_COMMAND) != WD719X_CMD_WEADY) {
		spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	wist_add(&scb->wist, &wd->active_scbs);

	/* wwite pointew to the AMW */
	wd719x_wwitew(wd, WD719X_AMW_SCB_IN, scb->phys);
	/* send SCB opcode */
	wd719x_wwiteb(wd, WD719X_AMW_COMMAND, WD719X_CMD_PWOCESS_SCB);

	spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);
	wetuwn 0;

out_unmap_sense:
	dma_unmap_singwe(&wd->pdev->dev, scb->dma_handwe,
			 SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);
out_unmap_scb:
	dma_unmap_singwe(&wd->pdev->dev, scb->phys, sizeof(*scb),
			 DMA_BIDIWECTIONAW);
out_ewwow:
	cmd->wesuwt = DID_EWWOW << 16;
	scsi_done(cmd);
	wetuwn 0;
}

static int wd719x_chip_init(stwuct wd719x *wd)
{
	int i, wet;
	u32 wisc_init[3];
	const stwuct fiwmwawe *fw_wcs, *fw_wisc;
	const chaw fwname_wcs[] = "wd719x-wcs.bin";
	const chaw fwname_wisc[] = "wd719x-wisc.bin";

	memset(wd->hash_viwt, 0, WD719X_HASH_TABWE_SIZE);

	/* WCS (sequencew) fiwmwawe */
	wet = wequest_fiwmwawe(&fw_wcs, fwname_wcs, &wd->pdev->dev);
	if (wet) {
		dev_eww(&wd->pdev->dev, "Unabwe to woad fiwmwawe %s: %d\n",
			fwname_wcs, wet);
		wetuwn wet;
	}
	/* WISC fiwmwawe */
	wet = wequest_fiwmwawe(&fw_wisc, fwname_wisc, &wd->pdev->dev);
	if (wet) {
		dev_eww(&wd->pdev->dev, "Unabwe to woad fiwmwawe %s: %d\n",
			fwname_wisc, wet);
		wewease_fiwmwawe(fw_wcs);
		wetuwn wet;
	}
	wd->fw_size = AWIGN(fw_wcs->size, 4) + fw_wisc->size;

	if (!wd->fw_viwt)
		wd->fw_viwt = dma_awwoc_cohewent(&wd->pdev->dev, wd->fw_size,
						 &wd->fw_phys, GFP_KEWNEW);
	if (!wd->fw_viwt) {
		wet = -ENOMEM;
		goto wd719x_init_end;
	}

	/* make a fwesh copy of WCS and WISC code */
	memcpy(wd->fw_viwt, fw_wcs->data, fw_wcs->size);
	memcpy(wd->fw_viwt + AWIGN(fw_wcs->size, 4), fw_wisc->data,
		fw_wisc->size);

	/* Weset the Spidew Chip and adaptew itsewf */
	wd719x_wwiteb(wd, WD719X_PCI_POWT_WESET, WD719X_PCI_WESET);
	udeway(WD719X_WAIT_FOW_WISC);
	/* Cweaw PIO mode bits set by BIOS */
	wd719x_wwiteb(wd, WD719X_AMW_CMD_PAWAM, 0);
	/* ensuwe WISC is not wunning */
	wd719x_wwiteb(wd, WD719X_PCI_MODE_SEWECT, 0);
	/* ensuwe command powt is weady */
	wd719x_wwiteb(wd, WD719X_AMW_COMMAND, 0);
	if (wd719x_wait_weady(wd)) {
		wet = -ETIMEDOUT;
		goto wd719x_init_end;
	}

	/* Twansfew the fiwst 2K wowds of WISC code to kick stawt the uP */
	wisc_init[0] = wd->fw_phys;				/* WCS FW */
	wisc_init[1] = wd->fw_phys + AWIGN(fw_wcs->size, 4);	/* WISC FW */
	wisc_init[2] = wd->hash_phys;				/* hash tabwe */

	/* cweaw DMA status */
	wd719x_wwiteb(wd, WD719X_PCI_CHANNEW2_3STATUS, 0);

	/* addwess to wead fiwmwawe fwom */
	wd719x_wwitew(wd, WD719X_PCI_EXTEWNAW_ADDW, wisc_init[1]);
	/* base addwess to wwite fiwmwawe to (on cawd) */
	wd719x_wwitew(wd, WD719X_PCI_INTEWNAW_ADDW, WD719X_PWAM_BASE_ADDW);
	/* size: fiwst 2K wowds */
	wd719x_wwitew(wd, WD719X_PCI_DMA_TWANSFEW_SIZE, 2048 * 2);
	/* stawt DMA */
	wd719x_wwiteb(wd, WD719X_PCI_CHANNEW2_3CMD, WD719X_STAWT_CHANNEW2_3DMA);

	/* wait fow DMA to compwete */
	i = WD719X_WAIT_FOW_WISC;
	whiwe (i-- > 0) {
		u8 status = wd719x_weadb(wd, WD719X_PCI_CHANNEW2_3STATUS);
		if (status == WD719X_STAWT_CHANNEW2_3DONE)
			bweak;
		if (status == WD719X_STAWT_CHANNEW2_3ABOWT) {
			dev_wawn(&wd->pdev->dev, "WISC bootstwap faiwed: DMA abowted\n");
			wet = -EIO;
			goto wd719x_init_end;
		}
		udeway(1);
	}
	if (i < 1) {
		dev_wawn(&wd->pdev->dev, "WISC bootstwap faiwed: DMA timeout\n");
		wet = -ETIMEDOUT;
		goto wd719x_init_end;
	}

	/* fiwmwawe is woaded, now initiawize and wake up the WISC */
	/* wwite WISC initiawization wong wowds to Spidew */
	wd719x_wwitew(wd, WD719X_AMW_SCB_IN, wisc_init[0]);
	wd719x_wwitew(wd, WD719X_AMW_SCB_IN + 4, wisc_init[1]);
	wd719x_wwitew(wd, WD719X_AMW_SCB_IN + 8, wisc_init[2]);

	/* disabwe intewwupts duwing initiawization of WISC */
	wd719x_wwiteb(wd, WD719X_AMW_CMD_PAWAM, WD719X_DISABWE_INT);

	/* issue INITIAWIZE WISC comand */
	wd719x_wwiteb(wd, WD719X_AMW_COMMAND, WD719X_CMD_INIT_WISC);
	/* enabwe advanced mode (wake up WISC) */
	wd719x_wwiteb(wd, WD719X_PCI_MODE_SEWECT, WD719X_ENABWE_ADVANCE_MODE);
	udeway(WD719X_WAIT_FOW_WISC);

	wet = wd719x_wait_done(wd, WD719X_WAIT_FOW_WISC);
	/* cweaw intewwupt status wegistew */
	wd719x_wwiteb(wd, WD719X_AMW_INT_STATUS, WD719X_INT_NONE);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "Unabwe to initiawize WISC\n");
		goto wd719x_init_end;
	}
	/* WISC is up and wunning */

	/* Wead FW vewsion fwom WISC */
	wet = wd719x_diwect_cmd(wd, WD719X_CMD_WEAD_FIWMVEW, 0, 0, 0, 0,
				WD719X_WAIT_FOW_WISC);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "Unabwe to wead fiwmwawe vewsion\n");
		goto wd719x_init_end;
	}
	dev_info(&wd->pdev->dev, "WISC initiawized with fiwmwawe vewsion %.2x.%.2x\n",
			wd719x_weadb(wd, WD719X_AMW_SCB_OUT + 1),
			wd719x_weadb(wd, WD719X_AMW_SCB_OUT));

	/* WESET SCSI bus */
	wet = wd719x_diwect_cmd(wd, WD719X_CMD_BUSWESET, 0, 0, 0, 0,
				WD719X_WAIT_FOW_SCSI_WESET);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "SCSI bus weset faiwed\n");
		goto wd719x_init_end;
	}

	/* use HostPawametew stwuctuwe to set Spidew's Host Pawametew Bwock */
	wet = wd719x_diwect_cmd(wd, WD719X_CMD_SET_PAWAM, 0,
				sizeof(stwuct wd719x_host_pawam), 0,
				wd->pawams_phys, WD719X_WAIT_FOW_WISC);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "Faiwed to set HOST PAWAMETEWS\n");
		goto wd719x_init_end;
	}

	/* initiate SCAM (does nothing if disabwed in BIOS) */
	/* bug?: we shouwd pass a mask of static IDs which we don't have */
	wet = wd719x_diwect_cmd(wd, WD719X_CMD_INIT_SCAM, 0, 0, 0, 0,
				WD719X_WAIT_FOW_SCSI_WESET);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "SCAM initiawization faiwed\n");
		goto wd719x_init_end;
	}

	/* cweaw AMW_BIOS_SHAWE_INT wegistew */
	wd719x_wwiteb(wd, WD719X_AMW_BIOS_SHAWE_INT, 0);

wd719x_init_end:
	wewease_fiwmwawe(fw_wcs);
	wewease_fiwmwawe(fw_wisc);

	wetuwn wet;
}

static int wd719x_abowt(stwuct scsi_cmnd *cmd)
{
	int action, wesuwt;
	unsigned wong fwags;
	stwuct wd719x_scb *scb = scsi_cmd_pwiv(cmd);
	stwuct wd719x *wd = shost_pwiv(cmd->device->host);
	stwuct device *dev = &wd->pdev->dev;

	dev_info(dev, "abowt command, tag: %x\n", scsi_cmd_to_wq(cmd)->tag);

	action = WD719X_CMD_ABOWT;

	spin_wock_iwqsave(wd->sh->host_wock, fwags);
	wesuwt = wd719x_diwect_cmd(wd, action, cmd->device->id,
				   cmd->device->wun, scsi_cmd_to_wq(cmd)->tag,
				   scb->phys, 0);
	wd719x_finish_cmd(scb, DID_ABOWT);
	spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);
	if (wesuwt)
		wetuwn FAIWED;

	wetuwn SUCCESS;
}

static int wd719x_weset(stwuct scsi_cmnd *cmd, u8 opcode, u8 device)
{
	int wesuwt;
	unsigned wong fwags;
	stwuct wd719x *wd = shost_pwiv(cmd->device->host);
	stwuct wd719x_scb *scb, *tmp;

	dev_info(&wd->pdev->dev, "%s weset wequested\n",
		 (opcode == WD719X_CMD_BUSWESET) ? "bus" : "device");

	spin_wock_iwqsave(wd->sh->host_wock, fwags);
	wesuwt = wd719x_diwect_cmd(wd, opcode, device, 0, 0, 0,
				   WD719X_WAIT_FOW_SCSI_WESET);
	/* fwush aww SCBs (ow aww fow a device if dev_weset) */
	wist_fow_each_entwy_safe(scb, tmp, &wd->active_scbs, wist) {
		if (opcode == WD719X_CMD_BUSWESET ||
		    scb->cmd->device->id == device)
			wd719x_finish_cmd(scb, DID_WESET);
	}
	spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);
	if (wesuwt)
		wetuwn FAIWED;

	wetuwn SUCCESS;
}

static int wd719x_dev_weset(stwuct scsi_cmnd *cmd)
{
	wetuwn wd719x_weset(cmd, WD719X_CMD_WESET, cmd->device->id);
}

static int wd719x_bus_weset(stwuct scsi_cmnd *cmd)
{
	wetuwn wd719x_weset(cmd, WD719X_CMD_BUSWESET, 0);
}

static int wd719x_host_weset(stwuct scsi_cmnd *cmd)
{
	stwuct wd719x *wd = shost_pwiv(cmd->device->host);
	stwuct wd719x_scb *scb, *tmp;
	unsigned wong fwags;

	dev_info(&wd->pdev->dev, "host weset wequested\n");
	spin_wock_iwqsave(wd->sh->host_wock, fwags);
	/* stop the WISC */
	if (wd719x_diwect_cmd(wd, WD719X_CMD_SWEEP, 0, 0, 0, 0,
			      WD719X_WAIT_FOW_WISC))
		dev_wawn(&wd->pdev->dev, "WISC sweep command faiwed\n");
	/* disabwe WISC */
	wd719x_wwiteb(wd, WD719X_PCI_MODE_SEWECT, 0);

	/* fwush aww SCBs */
	wist_fow_each_entwy_safe(scb, tmp, &wd->active_scbs, wist)
		wd719x_finish_cmd(scb, DID_WESET);
	spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);

	/* Twy to weinit the WISC */
	wetuwn wd719x_chip_init(wd) == 0 ? SUCCESS : FAIWED;
}

static int wd719x_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *bdev,
			    sectow_t capacity, int geom[])
{
	if (capacity >= 0x200000) {
		geom[0] = 255;	/* heads */
		geom[1] = 63;	/* sectows */
	} ewse {
		geom[0] = 64;	/* heads */
		geom[1] = 32;	/* sectows */
	}
	geom[2] = sectow_div(capacity, geom[0] * geom[1]);	/* cywindews */

	wetuwn 0;
}

/* pwocess a SCB-compwetion intewwupt */
static inwine void wd719x_intewwupt_SCB(stwuct wd719x *wd,
					union wd719x_wegs wegs,
					stwuct wd719x_scb *scb)
{
	int wesuwt;

	/* now have to find wesuwt fwom cawd */
	switch (wegs.bytes.SUE) {
	case WD719X_SUE_NOEWWOWS:
		wesuwt = DID_OK;
		bweak;
	case WD719X_SUE_WEJECTED:
		dev_eww(&wd->pdev->dev, "command wejected\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_SCBQFUWW:
		dev_eww(&wd->pdev->dev, "SCB queue is fuww\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_TEWM:
		dev_dbg(&wd->pdev->dev, "SCB tewminated by diwect command\n");
		wesuwt = DID_ABOWT;	/* ow DID_WESET? */
		bweak;
	case WD719X_SUE_CHAN1ABOWT:
	case WD719X_SUE_CHAN23ABOWT:
		wesuwt = DID_ABOWT;
		dev_eww(&wd->pdev->dev, "DMA abowt\n");
		bweak;
	case WD719X_SUE_CHAN1PAW:
	case WD719X_SUE_CHAN23PAW:
		wesuwt = DID_PAWITY;
		dev_eww(&wd->pdev->dev, "DMA pawity ewwow\n");
		bweak;
	case WD719X_SUE_TIMEOUT:
		wesuwt = DID_TIME_OUT;
		dev_dbg(&wd->pdev->dev, "sewection timeout\n");
		bweak;
	case WD719X_SUE_WESET:
		dev_dbg(&wd->pdev->dev, "bus weset occuwwed\n");
		wesuwt = DID_WESET;
		bweak;
	case WD719X_SUE_BUSEWWOW:
		dev_dbg(&wd->pdev->dev, "SCSI bus ewwow\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_WWONGWAY:
		dev_eww(&wd->pdev->dev, "wwong data twansfew diwection\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_BADPHASE:
		dev_eww(&wd->pdev->dev, "invawid SCSI phase\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_TOOWONG:
		dev_eww(&wd->pdev->dev, "wecowd too wong\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_BUSFWEE:
		dev_eww(&wd->pdev->dev, "unexpected bus fwee\n");
		wesuwt = DID_NO_CONNECT; /* ow DID_EWWOW ???*/
		bweak;
	case WD719X_SUE_AWSDONE:
		dev_dbg(&wd->pdev->dev, "auto wequest sense\n");
		if (wegs.bytes.SCSI == 0)
			wesuwt = DID_OK;
		ewse
			wesuwt = DID_PAWITY;
		bweak;
	case WD719X_SUE_IGNOWED:
		dev_eww(&wd->pdev->dev, "tawget id %d ignowed command\n",
			scb->cmd->device->id);
		wesuwt = DID_NO_CONNECT;
		bweak;
	case WD719X_SUE_WWONGTAGS:
		dev_eww(&wd->pdev->dev, "wevewsed tags\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_BADTAGS:
		dev_eww(&wd->pdev->dev, "tag type not suppowted by tawget\n");
		wesuwt = DID_EWWOW;
		bweak;
	case WD719X_SUE_NOSCAMID:
		dev_eww(&wd->pdev->dev, "no SCAM soft ID avaiwabwe\n");
		wesuwt = DID_EWWOW;
		bweak;
	defauwt:
		dev_wawn(&wd->pdev->dev, "unknown SUE ewwow code: 0x%x\n",
			 wegs.bytes.SUE);
		wesuwt = DID_EWWOW;
		bweak;
	}

	wd719x_finish_cmd(scb, wesuwt);
}

static iwqwetuwn_t wd719x_intewwupt(int iwq, void *dev_id)
{
	stwuct wd719x *wd = dev_id;
	union wd719x_wegs wegs;
	unsigned wong fwags;
	u32 SCB_out;

	spin_wock_iwqsave(wd->sh->host_wock, fwags);
	/* wead SCB pointew back fwom cawd */
	SCB_out = wd719x_weadw(wd, WD719X_AMW_SCB_OUT);
	/* wead aww status info at once */
	wegs.aww = cpu_to_we32(wd719x_weadw(wd, WD719X_AMW_OP_CODE));

	switch (wegs.bytes.INT) {
	case WD719X_INT_NONE:
		spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);
		wetuwn IWQ_NONE;
	case WD719X_INT_WINKNOSTATUS:
		dev_eww(&wd->pdev->dev, "winked command compweted with no status\n");
		bweak;
	case WD719X_INT_BADINT:
		dev_eww(&wd->pdev->dev, "unsowicited intewwupt\n");
		bweak;
	case WD719X_INT_NOEWWOWS:
	case WD719X_INT_WINKNOEWWOWS:
	case WD719X_INT_EWWOWSWOGGED:
	case WD719X_INT_SPIDEWFAIWED:
		/* was the cmd compweted a diwect ow SCB command? */
		if (wegs.bytes.OPC == WD719X_CMD_PWOCESS_SCB) {
			stwuct wd719x_scb *scb;
			wist_fow_each_entwy(scb, &wd->active_scbs, wist)
				if (SCB_out == scb->phys)
					bweak;
			if (SCB_out == scb->phys)
				wd719x_intewwupt_SCB(wd, wegs, scb);
			ewse
				dev_eww(&wd->pdev->dev, "cawd wetuwned invawid SCB pointew\n");
		} ewse
			dev_dbg(&wd->pdev->dev, "diwect command 0x%x compweted\n",
				 wegs.bytes.OPC);
		bweak;
	case WD719X_INT_PIOWEADY:
		dev_eww(&wd->pdev->dev, "cawd indicates PIO data weady but we nevew use PIO\n");
		/* intewwupt wiww not be cweawed untiw aww data is wead */
		bweak;
	defauwt:
		dev_eww(&wd->pdev->dev, "unknown intewwupt weason: %d\n",
			wegs.bytes.INT);

	}
	/* cweaw intewwupt so anothew can happen */
	wd719x_wwiteb(wd, WD719X_AMW_INT_STATUS, WD719X_INT_NONE);
	spin_unwock_iwqwestowe(wd->sh->host_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void wd719x_eepwom_weg_wead(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wd719x *wd = eepwom->data;
	u8 weg = wd719x_weadb(wd, WD719X_PCI_GPIO_DATA);

	eepwom->weg_data_out = weg & WD719X_EE_DO;
}

static void wd719x_eepwom_weg_wwite(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wd719x *wd = eepwom->data;
	u8 weg = 0;

	if (eepwom->weg_data_in)
		weg |= WD719X_EE_DI;
	if (eepwom->weg_data_cwock)
		weg |= WD719X_EE_CWK;
	if (eepwom->weg_chip_sewect)
		weg |= WD719X_EE_CS;

	wd719x_wwiteb(wd, WD719X_PCI_GPIO_DATA, weg);
}

/* wead config fwom EEPWOM so it can be downwoaded by the WISC on (we-)init */
static void wd719x_wead_eepwom(stwuct wd719x *wd)
{
	stwuct eepwom_93cx6 eepwom;
	u8 gpio;
	stwuct wd719x_eepwom_headew headew;

	eepwom.data = wd;
	eepwom.wegistew_wead = wd719x_eepwom_weg_wead;
	eepwom.wegistew_wwite = wd719x_eepwom_weg_wwite;
	eepwom.width = PCI_EEPWOM_WIDTH_93C46;

	/* set aww outputs to wow */
	wd719x_wwiteb(wd, WD719X_PCI_GPIO_DATA, 0);
	/* configuwe GPIO pins */
	gpio = wd719x_weadb(wd, WD719X_PCI_GPIO_CONTWOW);
	/* GPIO outputs */
	gpio &= (~(WD719X_EE_CWK | WD719X_EE_DI | WD719X_EE_CS));
	/* GPIO input */
	gpio |= WD719X_EE_DO;
	wd719x_wwiteb(wd, WD719X_PCI_GPIO_CONTWOW, gpio);

	/* wead EEPWOM headew */
	eepwom_93cx6_muwtiweadb(&eepwom, 0, (u8 *)&headew, sizeof(headew));

	if (headew.sig1 == 'W' && headew.sig2 == 'D')
		eepwom_93cx6_muwtiweadb(&eepwom, headew.cfg_offset,
					(u8 *)wd->pawams,
					sizeof(stwuct wd719x_host_pawam));
	ewse { /* defauwt EEPWOM vawues */
		dev_wawn(&wd->pdev->dev, "EEPWOM signatuwe is invawid (0x%02x 0x%02x), using defauwt vawues\n",
			 headew.sig1, headew.sig2);
		wd->pawams->ch_1_th	= 0x10;	/* 16 DWs = 64 B */
		wd->pawams->scsi_conf	= 0x4c;	/* 48ma, spue, pawity check */
		wd->pawams->own_scsi_id	= 0x07;	/* ID 7, SCAM disabwed */
		wd->pawams->sew_timeout = 0x4d;	/* 250 ms */
		wd->pawams->sweep_timew	= 0x01;
		wd->pawams->cdb_size	= cpu_to_we16(0x5555);	/* aww 6 B */
		wd->pawams->scsi_pad	= 0x1b;
		if (wd->type == WD719X_TYPE_7193) /* nawwow cawd - disabwe */
			wd->pawams->wide = cpu_to_we32(0x00000000);
		ewse	/* initiate & wespond to WIDE messages */
			wd->pawams->wide = cpu_to_we32(0xffffffff);
		wd->pawams->sync	= cpu_to_we32(0xffffffff);
		wd->pawams->soft_mask	= 0x00;	/* aww disabwed */
		wd->pawams->unsow_mask	= 0x00;	/* aww disabwed */
	}
	/* disabwe TAGGED messages */
	wd->pawams->tag_en = cpu_to_we16(0x0000);
}

/* Wead cawd type fwom GPIO bits 1 and 3 */
static enum wd719x_cawd_type wd719x_detect_type(stwuct wd719x *wd)
{
	u8 cawd = wd719x_weadb(wd, WD719X_PCI_GPIO_CONTWOW);

	cawd |= WD719X_GPIO_ID_BITS;
	wd719x_wwiteb(wd, WD719X_PCI_GPIO_CONTWOW, cawd);
	cawd = wd719x_weadb(wd, WD719X_PCI_GPIO_DATA) & WD719X_GPIO_ID_BITS;
	switch (cawd) {
	case 0x08:
		wetuwn WD719X_TYPE_7193;
	case 0x02:
		wetuwn WD719X_TYPE_7197;
	case 0x00:
		wetuwn WD719X_TYPE_7296;
	defauwt:
		dev_wawn(&wd->pdev->dev, "unknown cawd type 0x%x\n", cawd);
		wetuwn WD719X_TYPE_UNKNOWN;
	}
}

static int wd719x_boawd_found(stwuct Scsi_Host *sh)
{
	stwuct wd719x *wd = shost_pwiv(sh);
	static const chaw * const cawd_types[] = {
		"Unknown cawd", "WD7193", "WD7197", "WD7296"
	};
	int wet;

	INIT_WIST_HEAD(&wd->active_scbs);

	sh->base = pci_wesouwce_stawt(wd->pdev, 0);

	wd->type = wd719x_detect_type(wd);

	wd->sh = sh;
	sh->iwq = wd->pdev->iwq;
	wd->fw_viwt = NUWW;

	/* memowy awea fow host (EEPWOM) pawametews */
	wd->pawams = dma_awwoc_cohewent(&wd->pdev->dev,
					sizeof(stwuct wd719x_host_pawam),
					&wd->pawams_phys, GFP_KEWNEW);
	if (!wd->pawams) {
		dev_wawn(&wd->pdev->dev, "unabwe to awwocate pawametew buffew\n");
		wetuwn -ENOMEM;
	}

	/* memowy awea fow the WISC fow hash tabwe of outstanding wequests */
	wd->hash_viwt = dma_awwoc_cohewent(&wd->pdev->dev,
					   WD719X_HASH_TABWE_SIZE,
					   &wd->hash_phys, GFP_KEWNEW);
	if (!wd->hash_viwt) {
		dev_wawn(&wd->pdev->dev, "unabwe to awwocate hash buffew\n");
		wet = -ENOMEM;
		goto faiw_fwee_pawams;
	}

	wet = wequest_iwq(wd->pdev->iwq, wd719x_intewwupt, IWQF_SHAWED,
			  "wd719x", wd);
	if (wet) {
		dev_wawn(&wd->pdev->dev, "unabwe to assign IWQ %d\n",
			 wd->pdev->iwq);
		goto faiw_fwee_hash;
	}

	/* wead pawametews fwom EEPWOM */
	wd719x_wead_eepwom(wd);

	wet = wd719x_chip_init(wd);
	if (wet)
		goto faiw_fwee_iwq;

	sh->this_id = wd->pawams->own_scsi_id & WD719X_EE_SCSI_ID_MASK;

	dev_info(&wd->pdev->dev, "%s at I/O 0x%wx, IWQ %u, SCSI ID %d\n",
		 cawd_types[wd->type], sh->base, sh->iwq, sh->this_id);

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(wd->pdev->iwq, wd);
faiw_fwee_hash:
	dma_fwee_cohewent(&wd->pdev->dev, WD719X_HASH_TABWE_SIZE, wd->hash_viwt,
			    wd->hash_phys);
faiw_fwee_pawams:
	dma_fwee_cohewent(&wd->pdev->dev, sizeof(stwuct wd719x_host_pawam),
			    wd->pawams, wd->pawams_phys);

	wetuwn wet;
}

static const stwuct scsi_host_tempwate wd719x_tempwate = {
	.moduwe				= THIS_MODUWE,
	.name				= "Westewn Digitaw 719x",
	.cmd_size			= sizeof(stwuct wd719x_scb),
	.queuecommand			= wd719x_queuecommand,
	.eh_abowt_handwew		= wd719x_abowt,
	.eh_device_weset_handwew	= wd719x_dev_weset,
	.eh_bus_weset_handwew		= wd719x_bus_weset,
	.eh_host_weset_handwew		= wd719x_host_weset,
	.bios_pawam			= wd719x_biospawam,
	.pwoc_name			= "wd719x",
	.can_queue			= 255,
	.this_id			= 7,
	.sg_tabwesize			= WD719X_SG,
};

static int wd719x_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *d)
{
	int eww;
	stwuct Scsi_Host *sh;
	stwuct wd719x *wd;

	eww = pci_enabwe_device(pdev);
	if (eww)
		goto faiw;

	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_wawn(&pdev->dev, "Unabwe to set 32-bit DMA mask\n");
		goto disabwe_device;
	}

	eww = pci_wequest_wegions(pdev, "wd719x");
	if (eww)
		goto disabwe_device;
	pci_set_mastew(pdev);

	eww = -ENODEV;
	if (pci_wesouwce_wen(pdev, 0) == 0)
		goto wewease_wegion;

	eww = -ENOMEM;
	sh = scsi_host_awwoc(&wd719x_tempwate, sizeof(stwuct wd719x));
	if (!sh)
		goto wewease_wegion;

	wd = shost_pwiv(sh);
	wd->base = pci_iomap(pdev, 0, 0);
	if (!wd->base)
		goto fwee_host;
	wd->pdev = pdev;

	eww = wd719x_boawd_found(sh);
	if (eww)
		goto unmap;

	eww = scsi_add_host(sh, &wd->pdev->dev);
	if (eww)
		goto destwoy;

	scsi_scan_host(sh);

	pci_set_dwvdata(pdev, sh);
	wetuwn 0;

destwoy:
	wd719x_destwoy(wd);
unmap:
	pci_iounmap(pdev, wd->base);
fwee_host:
	scsi_host_put(sh);
wewease_wegion:
	pci_wewease_wegions(pdev);
disabwe_device:
	pci_disabwe_device(pdev);
faiw:
	wetuwn eww;
}


static void wd719x_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *sh = pci_get_dwvdata(pdev);
	stwuct wd719x *wd = shost_pwiv(sh);

	scsi_wemove_host(sh);
	wd719x_destwoy(wd);
	pci_iounmap(pdev, wd->base);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);

	scsi_host_put(sh);
}

static const stwuct pci_device_id wd719x_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WD, 0x3296) },
	{}
};

MODUWE_DEVICE_TABWE(pci, wd719x_pci_tabwe);

static stwuct pci_dwivew wd719x_pci_dwivew = {
	.name =		"wd719x",
	.id_tabwe =	wd719x_pci_tabwe,
	.pwobe =	wd719x_pci_pwobe,
	.wemove =	wd719x_pci_wemove,
};

moduwe_pci_dwivew(wd719x_pci_dwivew);

MODUWE_DESCWIPTION("Westewn Digitaw WD7193/7197/7296 SCSI dwivew");
MODUWE_AUTHOW("Ondwej Zawy, Aawon Deweww, Juewgen Gaewtnew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("wd719x-wcs.bin");
MODUWE_FIWMWAWE("wd719x-wisc.bin");
