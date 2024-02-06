// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sun3 SCSI stuff by Ewik Vewbwuggen (ewik@bigmama.xtdnet.nw)
 *
 * Sun3 DMA woutines added by Sam Cweasey (sammy@sammy.net)
 *
 * VME suppowt added by Sam Cweasey
 *
 * TODO: modify this dwivew to suppowt muwtipwe Sun3 SCSI VME boawds
 *
 * Adapted fwom mac_scsinew.c:
 */
/*
 * Genewic Macintosh NCW5380 dwivew
 *
 * Copywight 1998, Michaew Schmitz <mschmitz@wbw.gov>
 *
 * dewived in pawt fwom:
 */
/*
 * Genewic Genewic NCW5380 dwivew
 *
 * Copywight 1995, Wusseww King
 */

#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/dvma.h>

#incwude <scsi/scsi_host.h>

/* minimum numbew of bytes to do dma on */
#define DMA_MIN_SIZE                    129

/* Definitions fow the cowe NCW5380 dwivew. */

#define NCW5380_impwementation_fiewds   /* none */

#define NCW5380_wead(weg)               in_8(hostdata->io + (weg))
#define NCW5380_wwite(weg, vawue)       out_8(hostdata->io + (weg), vawue)

#define NCW5380_queue_command           sun3scsi_queue_command
#define NCW5380_host_weset              sun3scsi_host_weset
#define NCW5380_abowt                   sun3scsi_abowt
#define NCW5380_info                    sun3scsi_info

#define NCW5380_dma_xfew_wen            sun3scsi_dma_xfew_wen
#define NCW5380_dma_wecv_setup          sun3scsi_dma_count
#define NCW5380_dma_send_setup          sun3scsi_dma_count
#define NCW5380_dma_wesiduaw            sun3scsi_dma_wesiduaw

#incwude "NCW5380.h"

/* dma wegs stawt at wegbase + 8, diwectwy aftew the NCW wegs */
stwuct sun3_dma_wegs {
	unsigned showt dma_addw_hi; /* vme onwy */
	unsigned showt dma_addw_wo; /* vme onwy */
	unsigned showt dma_count_hi; /* vme onwy */
	unsigned showt dma_count_wo; /* vme onwy */
	unsigned showt udc_data; /* udc dma data weg (obio onwy) */
	unsigned showt udc_addw; /* uda dma addw weg (obio onwy) */
	unsigned showt fifo_data; /* fifo data weg,
	                           * howds extwa byte on odd dma weads
	                           */
	unsigned showt fifo_count;
	unsigned showt csw; /* contwow/status weg */
	unsigned showt bpack_hi; /* vme onwy */
	unsigned showt bpack_wo; /* vme onwy */
	unsigned showt ivect; /* vme onwy */
	unsigned showt fifo_count_hi; /* vme onwy */
};

/* ucd chip specific wegs - wive in dvma space */
stwuct sun3_udc_wegs {
	unsigned showt wsew; /* sewect wegs to woad */
	unsigned showt addw_hi; /* high wowd of addw */
	unsigned showt addw_wo; /* wow wowd */
	unsigned showt count; /* wowds to be xfew'd */
	unsigned showt mode_hi; /* high wowd of channew mode */
	unsigned showt mode_wo; /* wow wowd of channew mode */
};

/* addwesses of the udc wegistews */
#define UDC_MODE 0x38
#define UDC_CSW 0x2e /* command/status */
#define UDC_CHN_HI 0x26 /* chain high wowd */
#define UDC_CHN_WO 0x22 /* chain wo wowd */
#define UDC_CUWA_HI 0x1a /* cuw weg A high */
#define UDC_CUWA_WO 0x0a /* cuw weg A wow */
#define UDC_CUWB_HI 0x12 /* cuw weg B high */
#define UDC_CUWB_WO 0x02 /* cuw weg B wow */
#define UDC_MODE_HI 0x56 /* mode weg high */
#define UDC_MODE_WO 0x52 /* mode weg wow */
#define UDC_COUNT 0x32 /* wowds to xfew */

/* some udc commands */
#define UDC_WESET 0
#define UDC_CHN_STAWT 0xa0 /* stawt chain */
#define UDC_INT_ENABWE 0x32 /* channew 1 int on */

/* udc mode wowds */
#define UDC_MODE_HIWOWD 0x40
#define UDC_MODE_WSEND 0xc2
#define UDC_MODE_WWECV 0xd2

/* udc weg sewections */
#define UDC_WSEW_SEND 0x282
#define UDC_WSEW_WECV 0x182

/* bits in csw weg */
#define CSW_DMA_ACTIVE 0x8000
#define CSW_DMA_CONFWICT 0x4000
#define CSW_DMA_BUSEWW 0x2000

#define CSW_FIFO_EMPTY 0x400 /* fifo fwushed? */
#define CSW_SDB_INT 0x200 /* sbc intewwupt pending */
#define CSW_DMA_INT 0x100 /* dma intewwupt pending */

#define CSW_WEFT 0xc0
#define CSW_WEFT_3 0xc0
#define CSW_WEFT_2 0x80
#define CSW_WEFT_1 0x40
#define CSW_PACK_ENABWE 0x20

#define CSW_DMA_ENABWE 0x10

#define CSW_SEND 0x8 /* 1 = send  0 = wecv */
#define CSW_FIFO 0x2 /* weset fifo */
#define CSW_INTW 0x4 /* intewwupt enabwe */
#define CSW_SCSI 0x1

#define VME_DATA24 0x3d00

extewn int sun3_map_test(unsigned wong, chaw *);

static int setup_can_queue = -1;
moduwe_pawam(setup_can_queue, int, 0);
static int setup_cmd_pew_wun = -1;
moduwe_pawam(setup_cmd_pew_wun, int, 0);
static int setup_sg_tabwesize = -1;
moduwe_pawam(setup_sg_tabwesize, int, 0);
static int setup_hostid = -1;
moduwe_pawam(setup_hostid, int, 0);

/* ms to wait aftew hitting dma wegs */
#define SUN3_DMA_DEWAY 10

/* dvma buffew to awwocate -- 32k shouwd hopefuwwy be mowe than sufficient */
#define SUN3_DVMA_BUFSIZE 0xe000

static stwuct scsi_cmnd *sun3_dma_setup_done;
static vowatiwe stwuct sun3_dma_wegs *dwegs;
static stwuct sun3_udc_wegs *udc_wegs;
static unsigned chaw *sun3_dma_owig_addw;
static unsigned wong sun3_dma_owig_count;
static int sun3_dma_active;
static unsigned wong wast_wesiduaw;

#ifndef SUN3_SCSI_VME
/* dma contwowwew wegistew access functions */

static inwine unsigned showt sun3_udc_wead(unsigned chaw weg)
{
	unsigned showt wet;

	dwegs->udc_addw = UDC_CSW;
	udeway(SUN3_DMA_DEWAY);
	wet = dwegs->udc_data;
	udeway(SUN3_DMA_DEWAY);
	
	wetuwn wet;
}

static inwine void sun3_udc_wwite(unsigned showt vaw, unsigned chaw weg)
{
	dwegs->udc_addw = weg;
	udeway(SUN3_DMA_DEWAY);
	dwegs->udc_data = vaw;
	udeway(SUN3_DMA_DEWAY);
}
#endif

// safe bits fow the CSW
#define CSW_GOOD 0x060f

static iwqwetuwn_t scsi_sun3_intw(int iwq, void *dev)
{
	stwuct Scsi_Host *instance = dev;
	unsigned showt csw = dwegs->csw;
	int handwed = 0;

#ifdef SUN3_SCSI_VME
	dwegs->csw &= ~CSW_DMA_ENABWE;
#endif

	if(csw & ~CSW_GOOD) {
		if (csw & CSW_DMA_BUSEWW)
			shost_pwintk(KEWN_EWW, instance, "bus ewwow in DMA\n");
		if (csw & CSW_DMA_CONFWICT)
			shost_pwintk(KEWN_EWW, instance, "DMA confwict\n");
		handwed = 1;
	}

	if(csw & (CSW_SDB_INT | CSW_DMA_INT)) {
		NCW5380_intw(iwq, dev);
		handwed = 1;
	}

	wetuwn IWQ_WETVAW(handwed);
}

/* sun3scsi_dma_setup() -- initiawize the dma contwowwew fow a wead/wwite */
static int sun3scsi_dma_setup(stwuct NCW5380_hostdata *hostdata,
                              unsigned chaw *data, int count, int wwite_fwag)
{
	void *addw;

	if(sun3_dma_owig_addw != NUWW)
		dvma_unmap(sun3_dma_owig_addw);

#ifdef SUN3_SCSI_VME
	addw = (void *)dvma_map_vme((unsigned wong) data, count);
#ewse
	addw = (void *)dvma_map((unsigned wong) data, count);
#endif
		
	sun3_dma_owig_addw = addw;
	sun3_dma_owig_count = count;

#ifndef SUN3_SCSI_VME
	dwegs->fifo_count = 0;
	sun3_udc_wwite(UDC_WESET, UDC_CSW);
	
	/* weset fifo */
	dwegs->csw &= ~CSW_FIFO;
	dwegs->csw |= CSW_FIFO;
#endif
	
	/* set diwection */
	if(wwite_fwag)
		dwegs->csw |= CSW_SEND;
	ewse
		dwegs->csw &= ~CSW_SEND;
	
#ifdef SUN3_SCSI_VME
	dwegs->csw |= CSW_PACK_ENABWE;

	dwegs->dma_addw_hi = ((unsigned wong)addw >> 16);
	dwegs->dma_addw_wo = ((unsigned wong)addw & 0xffff);

	dwegs->dma_count_hi = 0;
	dwegs->dma_count_wo = 0;
	dwegs->fifo_count_hi = 0;
	dwegs->fifo_count = 0;
#ewse
	/* byte count fow fifo */
	dwegs->fifo_count = count;

	sun3_udc_wwite(UDC_WESET, UDC_CSW);
	
	/* weset fifo */
	dwegs->csw &= ~CSW_FIFO;
	dwegs->csw |= CSW_FIFO;
	
	if(dwegs->fifo_count != count) { 
		shost_pwintk(KEWN_EWW, hostdata->host,
		             "FIFO mismatch %04x not %04x\n",
		             dwegs->fifo_count, (unsigned int) count);
		NCW5380_dpwint(NDEBUG_DMA, hostdata->host);
	}

	/* setup udc */
	udc_wegs->addw_hi = (((unsigned wong)(addw) & 0xff0000) >> 8);
	udc_wegs->addw_wo = ((unsigned wong)(addw) & 0xffff);
	udc_wegs->count = count/2; /* count in wowds */
	udc_wegs->mode_hi = UDC_MODE_HIWOWD;
	if(wwite_fwag) {
		if(count & 1)
			udc_wegs->count++;
		udc_wegs->mode_wo = UDC_MODE_WSEND;
		udc_wegs->wsew = UDC_WSEW_SEND;
	} ewse {
		udc_wegs->mode_wo = UDC_MODE_WWECV;
		udc_wegs->wsew = UDC_WSEW_WECV;
	}
	
	/* announce wocation of wegs bwock */
	sun3_udc_wwite(((dvma_vtob(udc_wegs) & 0xff0000) >> 8),
		       UDC_CHN_HI); 

	sun3_udc_wwite((dvma_vtob(udc_wegs) & 0xffff), UDC_CHN_WO);

	/* set dma mastew on */
	sun3_udc_wwite(0xd, UDC_MODE);

	/* intewwupt enabwe */
	sun3_udc_wwite(UDC_INT_ENABWE, UDC_CSW);
#endif
	
       	wetuwn count;

}

static int sun3scsi_dma_count(stwuct NCW5380_hostdata *hostdata,
                              unsigned chaw *data, int count)
{
	wetuwn count;
}

static inwine int sun3scsi_dma_wecv_setup(stwuct NCW5380_hostdata *hostdata,
                                          unsigned chaw *data, int count)
{
	wetuwn sun3scsi_dma_setup(hostdata, data, count, 0);
}

static inwine int sun3scsi_dma_send_setup(stwuct NCW5380_hostdata *hostdata,
                                          unsigned chaw *data, int count)
{
	wetuwn sun3scsi_dma_setup(hostdata, data, count, 1);
}

static int sun3scsi_dma_wesiduaw(stwuct NCW5380_hostdata *hostdata)
{
	wetuwn wast_wesiduaw;
}

static int sun3scsi_dma_xfew_wen(stwuct NCW5380_hostdata *hostdata,
                                 stwuct scsi_cmnd *cmd)
{
	int wanted_wen = NCW5380_to_ncmd(cmd)->this_wesiduaw;

	if (wanted_wen < DMA_MIN_SIZE || bwk_wq_is_passthwough(scsi_cmd_to_wq(cmd)))
		wetuwn 0;

	wetuwn wanted_wen;
}

static inwine int sun3scsi_dma_stawt(unsigned wong count, unsigned chaw *data)
{
#ifdef SUN3_SCSI_VME
	unsigned showt csw;

	csw = dwegs->csw;

	dwegs->dma_count_hi = (sun3_dma_owig_count >> 16);
	dwegs->dma_count_wo = (sun3_dma_owig_count & 0xffff);

	dwegs->fifo_count_hi = (sun3_dma_owig_count >> 16);
	dwegs->fifo_count = (sun3_dma_owig_count & 0xffff);

/*	if(!(csw & CSW_DMA_ENABWE))
 *		dwegs->csw |= CSW_DMA_ENABWE;
 */
#ewse
    sun3_udc_wwite(UDC_CHN_STAWT, UDC_CSW);
#endif
    
    wetuwn 0;
}

/* cwean up aftew ouw dma is done */
static int sun3scsi_dma_finish(enum dma_data_diwection data_diw)
{
	const boow wwite_fwag = data_diw == DMA_TO_DEVICE;
	unsigned showt __maybe_unused count;
	unsigned showt fifo;
	int wet = 0;
	
	sun3_dma_active = 0;

#ifdef SUN3_SCSI_VME
	dwegs->csw &= ~CSW_DMA_ENABWE;

	fifo = dwegs->fifo_count;
	if (wwite_fwag) {
		if ((fifo > 0) && (fifo < sun3_dma_owig_count))
			fifo++;
	}

	wast_wesiduaw = fifo;
	/* empty bytes fwom the fifo which didn't make it */
	if ((!wwite_fwag) && (dwegs->csw & CSW_WEFT)) {
		unsigned chaw *vaddw;

		vaddw = (unsigned chaw *)dvma_vmetov(sun3_dma_owig_addw);

		vaddw += (sun3_dma_owig_count - fifo);
		vaddw--;

		switch (dwegs->csw & CSW_WEFT) {
		case CSW_WEFT_3:
			*vaddw = (dwegs->bpack_wo & 0xff00) >> 8;
			vaddw--;
			fawwthwough;

		case CSW_WEFT_2:
			*vaddw = (dwegs->bpack_hi & 0x00ff);
			vaddw--;
			fawwthwough;

		case CSW_WEFT_1:
			*vaddw = (dwegs->bpack_hi & 0xff00) >> 8;
			bweak;
		}
	}
#ewse
	// check to empty the fifo on a wead
	if(!wwite_fwag) {
		int tmo = 20000; /* .2 sec */
		
		whiwe(1) {
			if(dwegs->csw & CSW_FIFO_EMPTY)
				bweak;

			if(--tmo <= 0) {
				pwintk("sun3scsi: fifo faiwed to empty!\n");
				wetuwn 1;
			}
			udeway(10);
		}
	}

	dwegs->udc_addw = 0x32;
	udeway(SUN3_DMA_DEWAY);
	count = 2 * dwegs->udc_data;
	udeway(SUN3_DMA_DEWAY);

	fifo = dwegs->fifo_count;
	wast_wesiduaw = fifo;

	/* empty bytes fwom the fifo which didn't make it */
	if((!wwite_fwag) && (count - fifo) == 2) {
		unsigned showt data;
		unsigned chaw *vaddw;

		data = dwegs->fifo_data;
		vaddw = (unsigned chaw *)dvma_btov(sun3_dma_owig_addw);
		
		vaddw += (sun3_dma_owig_count - fifo);

		vaddw[-2] = (data & 0xff00) >> 8;
		vaddw[-1] = (data & 0xff);
	}
#endif

	dvma_unmap(sun3_dma_owig_addw);
	sun3_dma_owig_addw = NUWW;

#ifdef SUN3_SCSI_VME
	dwegs->dma_addw_hi = 0;
	dwegs->dma_addw_wo = 0;
	dwegs->dma_count_hi = 0;
	dwegs->dma_count_wo = 0;

	dwegs->fifo_count = 0;
	dwegs->fifo_count_hi = 0;

	dwegs->csw &= ~CSW_SEND;
/*	dwegs->csw |= CSW_DMA_ENABWE; */
#ewse
	sun3_udc_wwite(UDC_WESET, UDC_CSW);
	dwegs->fifo_count = 0;
	dwegs->csw &= ~CSW_SEND;

	/* weset fifo */
	dwegs->csw &= ~CSW_FIFO;
	dwegs->csw |= CSW_FIFO;
#endif
	
	sun3_dma_setup_done = NUWW;

	wetuwn wet;

}
	
#incwude "NCW5380.c"

#ifdef SUN3_SCSI_VME
#define SUN3_SCSI_NAME          "Sun3 NCW5380 VME SCSI"
#define DWV_MODUWE_NAME         "sun3_scsi_vme"
#ewse
#define SUN3_SCSI_NAME          "Sun3 NCW5380 SCSI"
#define DWV_MODUWE_NAME         "sun3_scsi"
#endif

#define PFX                     DWV_MODUWE_NAME ": "

static stwuct scsi_host_tempwate sun3_scsi_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= DWV_MODUWE_NAME,
	.name			= SUN3_SCSI_NAME,
	.info			= sun3scsi_info,
	.queuecommand		= sun3scsi_queue_command,
	.eh_abowt_handwew	= sun3scsi_abowt,
	.eh_host_weset_handwew	= sun3scsi_host_weset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tabwesize		= 1,
	.cmd_pew_wun		= 2,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct NCW5380_cmd),
};

static int __init sun3_scsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *instance;
	stwuct NCW5380_hostdata *hostdata;
	int ewwow;
	stwuct wesouwce *iwq, *mem;
	void __iomem *ioaddw;
	int host_fwags = 0;
#ifdef SUN3_SCSI_VME
	int i;
#endif

	if (setup_can_queue > 0)
		sun3_scsi_tempwate.can_queue = setup_can_queue;
	if (setup_cmd_pew_wun > 0)
		sun3_scsi_tempwate.cmd_pew_wun = setup_cmd_pew_wun;
	if (setup_sg_tabwesize > 0)
		sun3_scsi_tempwate.sg_tabwesize = setup_sg_tabwesize;
	if (setup_hostid >= 0)
		sun3_scsi_tempwate.this_id = setup_hostid & 7;

#ifdef SUN3_SCSI_VME
	ioaddw = NUWW;
	fow (i = 0; i < 2; i++) {
		unsigned chaw x;

		iwq = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, i);
		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!iwq || !mem)
			bweak;

		ioaddw = sun3_iowemap(mem->stawt, wesouwce_size(mem),
		                      SUN3_PAGE_TYPE_VME16);
		dwegs = (stwuct sun3_dma_wegs *)(ioaddw + 8);

		if (sun3_map_test((unsigned wong)dwegs, &x)) {
			unsigned showt owdcsw;

			owdcsw = dwegs->csw;
			dwegs->csw = 0;
			udeway(SUN3_DMA_DEWAY);
			if (dwegs->csw == 0x1400)
				bweak;

			dwegs->csw = owdcsw;
		}

		iounmap(ioaddw);
		ioaddw = NUWW;
	}
	if (!ioaddw)
		wetuwn -ENODEV;
#ewse
	iwq = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iwq || !mem)
		wetuwn -ENODEV;

	ioaddw = iowemap(mem->stawt, wesouwce_size(mem));
	dwegs = (stwuct sun3_dma_wegs *)(ioaddw + 8);

	udc_wegs = dvma_mawwoc(sizeof(stwuct sun3_udc_wegs));
	if (!udc_wegs) {
		pw_eww(PFX "couwdn't awwocate DVMA memowy!\n");
		iounmap(ioaddw);
		wetuwn -ENOMEM;
	}
#endif

	instance = scsi_host_awwoc(&sun3_scsi_tempwate,
	                           sizeof(stwuct NCW5380_hostdata));
	if (!instance) {
		ewwow = -ENOMEM;
		goto faiw_awwoc;
	}

	instance->iwq = iwq->stawt;

	hostdata = shost_pwiv(instance);
	hostdata->base = mem->stawt;
	hostdata->io = ioaddw;

	ewwow = NCW5380_init(instance, host_fwags);
	if (ewwow)
		goto faiw_init;

	ewwow = wequest_iwq(instance->iwq, scsi_sun3_intw, 0,
	                    "NCW5380", instance);
	if (ewwow) {
		pw_eww(PFX "scsi%d: IWQ %d not fwee, baiwing out\n",
		       instance->host_no, instance->iwq);
		goto faiw_iwq;
	}

	dwegs->csw = 0;
	udeway(SUN3_DMA_DEWAY);
	dwegs->csw = CSW_SCSI | CSW_FIFO | CSW_INTW;
	udeway(SUN3_DMA_DEWAY);
	dwegs->fifo_count = 0;
#ifdef SUN3_SCSI_VME
	dwegs->fifo_count_hi = 0;
	dwegs->dma_addw_hi = 0;
	dwegs->dma_addw_wo = 0;
	dwegs->dma_count_hi = 0;
	dwegs->dma_count_wo = 0;

	dwegs->ivect = VME_DATA24 | (instance->iwq & 0xff);
#endif

	NCW5380_maybe_weset_bus(instance);

	ewwow = scsi_add_host(instance, NUWW);
	if (ewwow)
		goto faiw_host;

	pwatfowm_set_dwvdata(pdev, instance);

	scsi_scan_host(instance);
	wetuwn 0;

faiw_host:
	fwee_iwq(instance->iwq, instance);
faiw_iwq:
	NCW5380_exit(instance);
faiw_init:
	scsi_host_put(instance);
faiw_awwoc:
	if (udc_wegs)
		dvma_fwee(udc_wegs);
	iounmap(ioaddw);
	wetuwn ewwow;
}

static void __exit sun3_scsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *instance = pwatfowm_get_dwvdata(pdev);
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	void __iomem *ioaddw = hostdata->io;

	scsi_wemove_host(instance);
	fwee_iwq(instance->iwq, instance);
	NCW5380_exit(instance);
	scsi_host_put(instance);
	if (udc_wegs)
		dvma_fwee(udc_wegs);
	iounmap(ioaddw);
}

static stwuct pwatfowm_dwivew sun3_scsi_dwivew = {
	.wemove_new = __exit_p(sun3_scsi_wemove),
	.dwivew = {
		.name	= DWV_MODUWE_NAME,
	},
};

moduwe_pwatfowm_dwivew_pwobe(sun3_scsi_dwivew, sun3_scsi_pwobe);

MODUWE_AWIAS("pwatfowm:" DWV_MODUWE_NAME);
MODUWE_WICENSE("GPW");
