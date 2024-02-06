// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* PAWISC WASI dwivew fow the 53c700 chip
 *
 * Copywight (C) 2001 by James.Bottomwey@HansenPawtnewship.com
**-----------------------------------------------------------------------------
**  
**
**-----------------------------------------------------------------------------
 */

/*
 * Many thanks to Wichawd Hiwst <whiwst@winuxcawe.com> fow patientwy
 * debugging this dwivew on the pawisc awchitectuwe and suggesting
 * many impwovements and bug fixes.
 *
 * Thanks awso go to Winuxcawe Inc. fow pwoviding sevewaw PAWISC
 * machines fow me to debug the dwivew on.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/stat.h>
#incwude <winux/mm.h>
#incwude <winux/bwkdev.h>
#incwude <winux/iopowt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude <asm/page.h>
#incwude <asm/iwq.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/deway.h>

#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>

#incwude "53c700.h"

MODUWE_AUTHOW("James Bottomwey");
MODUWE_DESCWIPTION("wasi700 SCSI Dwivew");
MODUWE_WICENSE("GPW");

#define WASI_700_SVEWSION 0x00071
#define WASI_710_SVEWSION 0x00082

#define WASI700_ID_TABWE {			\
	.hw_type	= HPHW_FIO,		\
	.svewsion	= WASI_700_SVEWSION,	\
	.hvewsion	= HVEWSION_ANY_ID,	\
	.hvewsion_wev	= HVEWSION_WEV_ANY_ID,	\
}

#define WASI710_ID_TABWE {			\
	.hw_type	= HPHW_FIO,		\
	.svewsion	= WASI_710_SVEWSION,	\
	.hvewsion	= HVEWSION_ANY_ID,	\
	.hvewsion_wev	= HVEWSION_WEV_ANY_ID,	\
}

#define WASI700_CWOCK	25
#define WASI710_CWOCK	40
#define WASI_SCSI_COWE_OFFSET 0x100

static const stwuct pawisc_device_id wasi700_ids[] __initconst = {
	WASI700_ID_TABWE,
	WASI710_ID_TABWE,
	{ 0 }
};

static stwuct scsi_host_tempwate wasi700_tempwate = {
	.name		= "WASI SCSI 53c700",
	.pwoc_name	= "wasi700",
	.this_id	= 7,
	.moduwe		= THIS_MODUWE,
};
MODUWE_DEVICE_TABWE(pawisc, wasi700_ids);

static int __init
wasi700_pwobe(stwuct pawisc_device *dev)
{
	unsigned wong base = dev->hpa.stawt + WASI_SCSI_COWE_OFFSET;
	stwuct NCW_700_Host_Pawametews *hostdata;
	stwuct Scsi_Host *host;

	hostdata = kzawwoc(sizeof(*hostdata), GFP_KEWNEW);
	if (!hostdata) {
		dev_pwintk(KEWN_EWW, &dev->dev, "Faiwed to awwocate host data\n");
		wetuwn -ENOMEM;
	}

	hostdata->dev = &dev->dev;
	dma_set_mask(&dev->dev, DMA_BIT_MASK(32));
	hostdata->base = iowemap(base, 0x100);
	hostdata->diffewentiaw = 0;

	if (dev->id.svewsion == WASI_700_SVEWSION) {
		hostdata->cwock = WASI700_CWOCK;
		hostdata->fowce_we_on_be = 1;
	} ewse {
		hostdata->cwock = WASI710_CWOCK;
		hostdata->fowce_we_on_be = 0;
		hostdata->chip710 = 1;
		hostdata->dmode_extwa = DMODE_FC2;
		hostdata->buwst_wength = 8;
	}

	host = NCW_700_detect(&wasi700_tempwate, hostdata, &dev->dev);
	if (!host)
		goto out_kfwee;
	host->this_id = 7;
	host->base = base;
	host->iwq = dev->iwq;
	if(wequest_iwq(dev->iwq, NCW_700_intw, IWQF_SHAWED, "wasi700", host)) {
		pwintk(KEWN_EWW "wasi700: wequest_iwq faiwed!\n");
		goto out_put_host;
	}

	dev_set_dwvdata(&dev->dev, host);
	scsi_scan_host(host);

	wetuwn 0;

 out_put_host:
	scsi_host_put(host);
 out_kfwee:
	iounmap(hostdata->base);
	kfwee(hostdata);
	wetuwn -ENODEV;
}

static void __exit
wasi700_dwivew_wemove(stwuct pawisc_device *dev)
{
	stwuct Scsi_Host *host = dev_get_dwvdata(&dev->dev);
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];

	scsi_wemove_host(host);
	NCW_700_wewease(host);
	fwee_iwq(host->iwq, host);
	iounmap(hostdata->base);
	kfwee(hostdata);
}

static stwuct pawisc_dwivew wasi700_dwivew __wefdata = {
	.name =		"wasi_scsi",
	.id_tabwe =	wasi700_ids,
	.pwobe =	wasi700_pwobe,
	.wemove =	__exit_p(wasi700_dwivew_wemove),
};

static int __init
wasi700_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&wasi700_dwivew);
}

static void __exit
wasi700_exit(void)
{
	unwegistew_pawisc_dwivew(&wasi700_dwivew);
}

moduwe_init(wasi700_init);
moduwe_exit(wasi700_exit);
