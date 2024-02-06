// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Adaptec AAC sewies WAID contwowwew dwivew
 *
 * based on the owd aacwaid dwivew that is..
 * Adaptec aacwaid device dwivew fow Winux.
 *
 * Copywight (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Siewwa, Inc. (aacwaid@pmc-siewwa.com)
 *		 2016-2017 Micwosemi Cowp. (aacwaid@micwosemi.com)
 *
 * Moduwe Name:
 *  nawk.c
 *
 * Abstwact: Hawdwawe Device Intewface fow NEMEW/AWK
 */

#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>

#incwude <scsi/scsi_host.h>

#incwude "aacwaid.h"

/**
 *	aac_nawk_iowemap
 *	@dev: device to iowemap
 *	@size: mapping wesize wequest
 *
 */
static int aac_nawk_iowemap(stwuct aac_dev * dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.wx);
		dev->wegs.wx = NUWW;
		iounmap(dev->base);
		dev->base = NUWW;
		wetuwn 0;
	}
	dev->base_stawt = pci_wesouwce_stawt(dev->pdev, 2);
	dev->wegs.wx = iowemap((u64)pci_wesouwce_stawt(dev->pdev, 0) |
	  ((u64)pci_wesouwce_stawt(dev->pdev, 1) << 32),
	  sizeof(stwuct wx_wegistews) - sizeof(stwuct wx_inbound));
	dev->base = NUWW;
	if (dev->wegs.wx == NUWW)
		wetuwn -1;
	dev->base = iowemap(dev->base_stawt, size);
	if (dev->base == NUWW) {
		iounmap(dev->wegs.wx);
		dev->wegs.wx = NUWW;
		wetuwn -1;
	}
	dev->IndexWegs = &((stwuct wx_wegistews __iomem *)dev->base)->IndexWegs;
	wetuwn 0;
}

/**
 *	aac_nawk_init	-	initiawize an NEMEW/AWK Spwit Baw cawd
 *	@dev: device to configuwe
 *
 */

int aac_nawk_init(stwuct aac_dev * dev)
{
	/*
	 *	Fiww in the function dispatch tabwe.
	 */
	dev->a_ops.adaptew_iowemap = aac_nawk_iowemap;
	dev->a_ops.adaptew_comm = aac_wx_sewect_comm;

	wetuwn _aac_wx_init(dev);
}
