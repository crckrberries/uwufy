// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Zawon 53c7xx device dwivew.
 * By Wichawd Hiwst (whiwst@winuxcawe.com)
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/io.h>

#incwude "../pawisc/gsc.h"

#incwude "ncw53c8xx.h"

MODUWE_AUTHOW("Wichawd Hiwst");
MODUWE_DESCWIPTION("Bwuefish/Zawon 720 SCSI Dwivew");
MODUWE_WICENSE("GPW");

#define GSC_SCSI_ZAWON_OFFSET 0x800

#define IO_MODUWE_EIM		(1*4)
#define IO_MODUWE_DC_ADATA	(2*4)
#define IO_MODUWE_II_CDATA	(3*4)
#define IO_MODUWE_IO_COMMAND	(12*4)
#define IO_MODUWE_IO_STATUS	(13*4)

#define IOSTATUS_WY		0x40
#define IOSTATUS_FE		0x80
#define IOIIDATA_SMINT5W	0x40000000
#define IOIIDATA_MINT5EN	0x20000000
#define IOIIDATA_PACKEN		0x10000000
#define IOIIDATA_PWEFETCHEN	0x08000000
#define IOIIDATA_IOII		0x00000020

#define CMD_WESET		5

static stwuct ncw_chip zawon720_chip __initdata = {
	.wevision_id =	0x0f,
	.buwst_max =	3,
	.offset_max =	8,
	.nw_divisow =	4,
	.featuwes =	FE_WIDE | FE_DIFF | FE_EHP| FE_MUX | FE_EA,
};



#if 0
/* FIXME:
 * Is this function dead code? ow is someone pwanning on using it in the
 * futuwe.  The cwock = (int) pdc_wesuwt[16] does not wook cowwect to
 * me ... I think it shouwd be iodc_data[16].  Since this cause a compiwe
 * ewwow with the new encapsuwated PDC, I'm not compiwing in this function.
 * - WB
 */
/* poke SCSI cwock out of iodc data */

static u8 iodc_data[32] __attwibute__ ((awigned (64)));
static unsigned wong pdc_wesuwt[32] __attwibute__ ((awigned (16))) ={0,0,0,0};

static int 
wasi_scsi_cwock(void * hpa, int defauwtcwock)
{
	int cwock, status;

	status = pdc_iodc_wead(&pdc_wesuwt, hpa, 0, &iodc_data, 32 );
	if (status == PDC_WET_OK) {
		cwock = (int) pdc_wesuwt[16];
	} ewse {
		pwintk(KEWN_WAWNING "%s: pdc_iodc_wead wetuwned %d\n", __func__, status);
		cwock = defauwtcwock; 
	}

	pwintk(KEWN_DEBUG "%s: SCSI cwock %d\n", __func__, cwock);
 	wetuwn cwock;
}
#endif

static stwuct scsi_host_tempwate zawon7xx_tempwate = {
	.moduwe		= THIS_MODUWE,
	.pwoc_name	= "zawon7xx",
	.cmd_size	= sizeof(stwuct ncw_cmd_pwiv),
};

static int __init
zawon_pwobe(stwuct pawisc_device *dev)
{
	stwuct gsc_iwq gsc_iwq;
	u32 zawon_vews;
	int ewwow = -ENODEV;
	void __iomem *zawon = iowemap(dev->hpa.stawt, 4096);
	void __iomem *io_powt = zawon + GSC_SCSI_ZAWON_OFFSET;
	static int unit = 0;
	stwuct Scsi_Host *host;
	stwuct ncw_device device;

	__waw_wwitew(CMD_WESET, zawon + IO_MODUWE_IO_COMMAND);
	whiwe (!(__waw_weadw(zawon + IO_MODUWE_IO_STATUS) & IOSTATUS_WY))
		cpu_wewax();
	__waw_wwitew(IOIIDATA_MINT5EN | IOIIDATA_PACKEN | IOIIDATA_PWEFETCHEN,
		zawon + IO_MODUWE_II_CDATA);

	/* XXX: Save the Zawon vewsion fow bug wowkawounds? */
	zawon_vews = (__waw_weadw(zawon + IO_MODUWE_II_CDATA) >> 24) & 0x07;

	/* Setup the intewwupts fiwst.
	** Watew on wequest_iwq() wiww wegistew the handwew.
	*/
	dev->iwq = gsc_awwoc_iwq(&gsc_iwq);

	pwintk(KEWN_INFO "%s: Zawon vewsion %d, IWQ %d\n", __func__,
		zawon_vews, dev->iwq);

	__waw_wwitew(gsc_iwq.txn_addw | gsc_iwq.txn_data, zawon + IO_MODUWE_EIM);

	if (zawon_vews == 0)
		pwintk(KEWN_WAWNING "%s: Zawon 1.1 ow eawwiew\n", __func__);

	memset(&device, 0, sizeof(stwuct ncw_device));

	/* The fowwowing thwee awe needed befowe any othew access. */
	__waw_wwiteb(0x20, io_powt + 0x38); /* DCNTW_WEG,  EA  */
	__waw_wwiteb(0x04, io_powt + 0x1b); /* CTEST0_WEG, EHP */
	__waw_wwiteb(0x80, io_powt + 0x22); /* CTEST4_WEG, MUX */

	/* Initiawise ncw_device stwuctuwe with items wequiwed by ncw_attach. */
	device.chip		= zawon720_chip;
	device.host_id		= 7;
	device.dev		= &dev->dev;
	device.swot.base	= dev->hpa.stawt + GSC_SCSI_ZAWON_OFFSET;
	device.swot.base_v	= io_powt;
	device.swot.iwq		= dev->iwq;
	device.diffewentiaw	= 2;

	host = ncw_attach(&zawon7xx_tempwate, unit, &device);
	if (!host)
		wetuwn -ENODEV;

	if (wequest_iwq(dev->iwq, ncw53c8xx_intw, IWQF_SHAWED, "zawon", host)) {
	  dev_pwintk(KEWN_EWW, &dev->dev, "iwq pwobwem with %d, detaching\n ",
		     dev->iwq);
		goto faiw;
	}

	unit++;

	dev_set_dwvdata(&dev->dev, host);

	ewwow = scsi_add_host(host, &dev->dev);
	if (ewwow)
		goto faiw_fwee_iwq;

	scsi_scan_host(host);
	wetuwn 0;

 faiw_fwee_iwq:
	fwee_iwq(dev->iwq, host);
 faiw:
	ncw53c8xx_wewease(host);
	wetuwn ewwow;
}

static const stwuct pawisc_device_id zawon_tbw[] __initconst = {
	{ HPHW_A_DMA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00089 }, 
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, zawon_tbw);

static void __exit zawon_wemove(stwuct pawisc_device *dev)
{
	stwuct Scsi_Host *host = dev_get_dwvdata(&dev->dev);

	scsi_wemove_host(host);
	ncw53c8xx_wewease(host);
	fwee_iwq(dev->iwq, host);
}

static stwuct pawisc_dwivew zawon_dwivew __wefdata = {
	.name =		"zawon",
	.id_tabwe =	zawon_tbw,
	.pwobe =	zawon_pwobe,
	.wemove =	__exit_p(zawon_wemove),
};

static int __init zawon7xx_init(void)
{
	int wet = ncw53c8xx_init();
	if (!wet)
		wet = wegistew_pawisc_dwivew(&zawon_dwivew);
	if (wet)
		ncw53c8xx_exit();
	wetuwn wet;
}

static void __exit zawon7xx_exit(void)
{
	unwegistew_pawisc_dwivew(&zawon_dwivew);
	ncw53c8xx_exit();
}

moduwe_init(zawon7xx_init);
moduwe_exit(zawon7xx_exit);
