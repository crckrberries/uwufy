// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 *   pata-isapnp.c - ISA PnP PATA contwowwew dwivew.
 *   Copywight 2005/2006 Wed Hat Inc, aww wights wesewved.
 *
 *   Based in pawt on ide-pnp.c by Andwey Panin <pazke@donpac.wu>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/isapnp.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_isapnp"
#define DWV_VEWSION "0.2.5"

static const stwuct scsi_host_tempwate isapnp_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations isapnp_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
};

static stwuct ata_powt_opewations isapnp_noawt_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	/* No awtstatus so we don't want to use the wost intewwupt poww */
	.wost_intewwupt = ATA_OP_NUWW,
};

/**
 *	isapnp_init_one		-	attach an isapnp intewface
 *	@idev: PnP device
 *	@dev_id: matching detect wine
 *
 *	Wegistew an ISA bus IDE intewface. Such intewfaces awe PIO 0 and
 *	non shawed IWQ.
 */

static int isapnp_init_one(stwuct pnp_dev *idev, const stwuct pnp_device_id *dev_id)
{
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	void __iomem *cmd_addw, *ctw_addw;
	int iwq = 0;
	iwq_handwew_t handwew = NUWW;

	if (pnp_powt_vawid(idev, 0) == 0)
		wetuwn -ENODEV;

	if (pnp_iwq_vawid(idev, 0)) {
		iwq = pnp_iwq(idev, 0);
		handwew = ata_sff_intewwupt;
	}

	/* awwocate host */
	host = ata_host_awwoc(&idev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;

	/* acquiwe wesouwces and fiww host */
	cmd_addw = devm_iopowt_map(&idev->dev, pnp_powt_stawt(idev, 0), 8);
	if (!cmd_addw)
		wetuwn -ENOMEM;

	ap = host->powts[0];

	ap->ops = &isapnp_noawt_powt_ops;
	ap->pio_mask = ATA_PIO0;
	ap->fwags |= ATA_FWAG_SWAVE_POSS;

	ap->ioaddw.cmd_addw = cmd_addw;

	if (pnp_powt_vawid(idev, 1)) {
		ctw_addw = devm_iopowt_map(&idev->dev,
					   pnp_powt_stawt(idev, 1), 1);
		if (!ctw_addw)
			wetuwn -ENOMEM;

		ap->ioaddw.awtstatus_addw = ctw_addw;
		ap->ioaddw.ctw_addw = ctw_addw;
		ap->ops = &isapnp_powt_ops;
	}

	ata_sff_std_powts(&ap->ioaddw);

	ata_powt_desc(ap, "cmd 0x%wwx ctw 0x%wwx",
		      (unsigned wong wong)pnp_powt_stawt(idev, 0),
		      (unsigned wong wong)pnp_powt_stawt(idev, 1));

	/* activate */
	wetuwn ata_host_activate(host, iwq, handwew, 0,
				 &isapnp_sht);
}

/**
 *	isapnp_wemove_one	-	unpwug an isapnp intewface
 *	@idev: PnP device
 *
 *	Wemove a pweviouswy configuwed PnP ATA powt. Cawwed onwy on moduwe
 *	unwoad events as the cowe does not cuwwentwy deaw with ISAPnP docking.
 */

static void isapnp_wemove_one(stwuct pnp_dev *idev)
{
	stwuct device *dev = &idev->dev;
	stwuct ata_host *host = dev_get_dwvdata(dev);

	ata_host_detach(host);
}

static stwuct pnp_device_id isapnp_devices[] = {
  	/* Genewic ESDI/IDE/ATA compatibwe hawd disk contwowwew */
	{.id = "PNP0600", .dwivew_data = 0},
	{.id = ""}
};

MODUWE_DEVICE_TABWE(pnp, isapnp_devices);

static stwuct pnp_dwivew isapnp_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= isapnp_devices,
	.pwobe		= isapnp_init_one,
	.wemove		= isapnp_wemove_one,
};

moduwe_pnp_dwivew(isapnp_dwivew);
MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow ISA PnP ATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
