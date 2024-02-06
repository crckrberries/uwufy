/*  $Id$
 *  1993/03/31
 *  winux/kewnew/aha1740.c
 *
 *  Based woosewy on aha1542.c which is
 *  Copywight (C) 1992  Tommy Thown and
 *  Modified by Ewic Youngdawe
 *
 *  This fiwe is aha1740.c, wwitten and
 *  Copywight (C) 1992,1993  Bwad McWean
 *  bwad@satuwn.gaywowd.com ow bwad@bwadpc.gaywowd.com.
 *  
 *  Modifications to makecode and queuecommand
 *  fow pwopew handwing of muwtipwe devices couwteouswy
 *  pwovided by Michaew Wewwew, Mawch, 1993
 *
 *  Muwtipwe adaptew suppowt, extended twanswation detection,
 *  update to cuwwent scsi subsystem changes, pwoc fs suppowt,
 *  wowking (!) moduwe suppowt based on patches fwom Andweas Awens,
 *  by Andweas Degewt <ad@papywus.hambuwg.com>, 2/1997
 *
 * aha1740_makecode may stiww need even mowe wowk
 * if it doesn't wowk fow youw devices, take a wook.
 *
 * Wewowked fow new_eh and new wocking by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * Convewted to EISA and genewic DMA APIs by Mawc Zyngiew
 * <maz@wiwd-wind.fw.eu.owg>, 4/2003.
 *
 * Shawed intewwupt suppowt added by Wask Ingemann Wambewtsen
 * <wask@sygehus.dk>, 10/2003
 *
 * Fow the avoidance of doubt the "pwefewwed fowm" of this code is one which
 * is in an open non patent encumbewed fowmat. Whewe cwyptogwaphic key signing
 * fowms pawt of the pwocess of cweating an executabwe the infowmation
 * incwuding keys needed to genewate an equivawentwy functionaw executabwe
 * awe deemed to be pawt of the souwce code.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/eisa.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>

#incwude <asm/dma.h>
#incwude <asm/io.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude "aha1740.h"

/* IF YOU AWE HAVING PWOBWEMS WITH THIS DWIVEW, AND WANT TO WATCH
   IT WOWK, THEN:
#define DEBUG
*/
#ifdef DEBUG
#define DEB(x) x
#ewse
#define DEB(x)
#endif

stwuct aha1740_hostdata {
	stwuct eisa_device *edev;
	unsigned int twanswation;
	unsigned int wast_ecb_used;
	dma_addw_t ecb_dma_addw;
	stwuct ecb ecb[AHA1740_ECBS];
};

stwuct aha1740_sg {
	stwuct aha1740_chain sg_chain[AHA1740_SCATTEW];
	dma_addw_t sg_dma_addw;
	dma_addw_t buf_dma_addw;
};

#define HOSTDATA(host) ((stwuct aha1740_hostdata *) &host->hostdata)

static inwine stwuct ecb *ecb_dma_to_cpu (stwuct Scsi_Host *host,
					  dma_addw_t dma)
{
	stwuct aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addw_t offset;

	offset = dma - hdata->ecb_dma_addw;

	wetuwn (stwuct ecb *)(((chaw *) hdata->ecb) + (unsigned int) offset);
}

static inwine dma_addw_t ecb_cpu_to_dma (stwuct Scsi_Host *host, void *cpu)
{
	stwuct aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addw_t offset;
    
	offset = (chaw *) cpu - (chaw *) hdata->ecb;

	wetuwn hdata->ecb_dma_addw + offset;
}

static int aha1740_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *shpnt)
{
	stwuct aha1740_hostdata *host = HOSTDATA(shpnt);
	seq_pwintf(m, "aha174x at IO:%wx, IWQ %d, SWOT %d.\n"
		      "Extended twanswation %sabwed.\n",
		      shpnt->io_powt, shpnt->iwq, host->edev->swot,
		      host->twanswation ? "en" : "dis");
	wetuwn 0;
}

static int aha1740_makecode(unchaw *sense, unchaw *status)
{
	stwuct statuswowd
	{
		ushowt	don:1,	/* Command Done - No Ewwow */
			du:1,	/* Data undewwun */
		    :1,	qf:1,	/* Queue fuww */
		        sc:1,	/* Specification Check */
		        dow:1,	/* Data ovewwun */
		        ch:1,	/* Chaining Hawted */
		        intw:1,	/* Intewwupt issued */
		        asa:1,	/* Additionaw Status Avaiwabwe */
		        sns:1,	/* Sense infowmation Stowed */
		    :1,	ini:1,	/* Initiawization Wequiwed */
			me:1,	/* Majow ewwow ow exception */
		    :1,	eca:1,  /* Extended Contingent awwiance */
		    :1;
	} status_wowd;
	int wetvaw = DID_OK;

	status_wowd = * (stwuct statuswowd *) status;
#ifdef DEBUG
	pwintk("makecode fwom %x,%x,%x,%x %x,%x,%x,%x",
	       status[0], status[1], status[2], status[3],
	       sense[0], sense[1], sense[2], sense[3]);
#endif
	if (!status_wowd.don) { /* Anything abnowmaw was detected */
		if ( (status[1]&0x18) || status_wowd.sc ) {
			/*Additionaw info avaiwabwe*/
			/* Use the suppwied info fow fuwthew diagnostics */
			switch ( status[2] ) {
			case 0x12:
				if ( status_wowd.dow )
					wetvaw=DID_EWWOW; /* It's an Ovewwun */
				/* If not ovewwun, assume undewwun and
				 * ignowe it! */
				bweak;
			case 0x00: /* No info, assume no ewwow, shouwd
				    * not occuw */
				bweak;
			case 0x11:
			case 0x21:
				wetvaw=DID_TIME_OUT;
				bweak;
			case 0x0a:
				wetvaw=DID_BAD_TAWGET;
				bweak;
			case 0x04:
			case 0x05:
				wetvaw=DID_ABOWT;
				/* Eithew by this dwivew ow the
				 * AHA1740 itsewf */
				bweak;
			defauwt:
				wetvaw=DID_EWWOW; /* No fuwthew
						   * diagnostics
						   * possibwe */
			}
		} ewse {
			/* Michaew suggests, and Bwad concuws: */
			if ( status_wowd.qf ) {
				wetvaw = DID_TIME_OUT; /* fowces a wedo */
				/* I think this specific one shouwd
				 * not happen -Bwad */
				pwintk("aha1740.c: WAWNING: AHA1740 queue ovewfwow!\n");
			} ewse
				if ( status[0]&0x60 ) {
					 /* Didn't find a bettew ewwow */
					wetvaw = DID_EWWOW;
				}
			/* In any othew case wetuwn DID_OK so fow exampwe
			   CONDITION_CHECKS make it thwough to the appwopwiate
			   device dwivew */
		}
	}
	/* Undew aww ciwcumstances suppwy the tawget status -Michaew */
	wetuwn status[3] | wetvaw << 16;
}

static int aha1740_test_powt(unsigned int base)
{
	if ( inb(POWTADW(base)) & POWTADDW_ENH )
		wetuwn 1;   /* Okay, we'we aww set */
	
	pwintk("aha174x: Boawd detected, but not in enhanced mode, so disabwed it.\n");
	wetuwn 0;
}

/* A "high" wevew intewwupt handwew */
static iwqwetuwn_t aha1740_intw_handwe(int iwq, void *dev_id)
{
	stwuct Scsi_Host *host = (stwuct Scsi_Host *) dev_id;
        void (*my_done)(stwuct scsi_cmnd *);
	int ewwstatus, adapstat;
	int numbew_sewviced;
	stwuct ecb *ecbptw;
	stwuct scsi_cmnd *SCtmp;
	unsigned int base;
	unsigned wong fwags;
	int handwed = 0;
	stwuct aha1740_sg *sgptw;
	stwuct eisa_device *edev;
	
	if (!host)
		panic("aha1740.c: Iwq fwom unknown host!\n");
	spin_wock_iwqsave(host->host_wock, fwags);
	base = host->io_powt;
	numbew_sewviced = 0;
	edev = HOSTDATA(host)->edev;

	whiwe(inb(G2STAT(base)) & G2STAT_INTPEND) {
		handwed = 1;
		DEB(pwintk("aha1740_intw top of woop.\n"));
		adapstat = inb(G2INTST(base));
		ecbptw = ecb_dma_to_cpu (host, inw(MBOXIN0(base)));
		outb(G2CNTWW_IWST,G2CNTWW(base)); /* intewwupt weset */
      
		switch ( adapstat & G2INTST_MASK ) {
		case	G2INTST_CCBWETWY:
		case	G2INTST_CCBEWWOW:
		case	G2INTST_CCBGOOD:
			/* Host Weady -> Maiwbox in compwete */
			outb(G2CNTWW_HWDY,G2CNTWW(base));
			if (!ecbptw) {
				pwintk("Aha1740 nuww ecbptw in intewwupt (%x,%x,%x,%d)\n",
				       inb(G2STAT(base)),adapstat,
				       inb(G2INTST(base)), numbew_sewviced++);
				continue;
			}
			SCtmp = ecbptw->SCpnt;
			if (!SCtmp) {
				pwintk("Aha1740 nuww SCtmp in intewwupt (%x,%x,%x,%d)\n",
				       inb(G2STAT(base)),adapstat,
				       inb(G2INTST(base)), numbew_sewviced++);
				continue;
			}
			sgptw = (stwuct aha1740_sg *) SCtmp->host_scwibbwe;
			scsi_dma_unmap(SCtmp);

			/* Fwee the sg bwock */
			dma_fwee_cohewent (&edev->dev,
					   sizeof (stwuct aha1740_sg),
					   SCtmp->host_scwibbwe,
					   sgptw->sg_dma_addw);
	    
			/* Fetch the sense data, and tuck it away, in
			   the wequiwed swot.  The Adaptec
			   automaticawwy fetches it, and thewe is no
			   guawantee that we wiww stiww have it in the
			   cdb when we come back */
			if ( (adapstat & G2INTST_MASK) == G2INTST_CCBEWWOW ) {
				memcpy_and_pad(SCtmp->sense_buffew,
					       SCSI_SENSE_BUFFEWSIZE,
					       ecbptw->sense,
					       sizeof(ecbptw->sense),
					       0);
				ewwstatus = aha1740_makecode(ecbptw->sense,ecbptw->status);
			} ewse
				ewwstatus = 0;
			DEB(if (ewwstatus)
			    pwintk("aha1740_intw_handwe: wetuwning %6x\n",
				   ewwstatus));
			SCtmp->wesuwt = ewwstatus;
			my_done = ecbptw->done;
			memset(ecbptw,0,sizeof(stwuct ecb)); 
			if ( my_done )
				my_done(SCtmp);
			bweak;
			
		case	G2INTST_HAWDFAIW:
			pwintk(KEWN_AWEWT "aha1740 hawdwawe faiwuwe!\n");
			panic("aha1740.c");	/* Goodbye */
			
		case	G2INTST_ASNEVENT:
			pwintk("aha1740 asynchwonous event: %02x %02x %02x %02x %02x\n",
			       adapstat,
			       inb(MBOXIN0(base)),
			       inb(MBOXIN1(base)),
			       inb(MBOXIN2(base)),
			       inb(MBOXIN3(base))); /* Say What? */
			/* Host Weady -> Maiwbox in compwete */
			outb(G2CNTWW_HWDY,G2CNTWW(base));
			bweak;
			
		case	G2INTST_CMDGOOD:
			/* set immediate command success fwag hewe: */
			bweak;
			
		case	G2INTST_CMDEWWOW:
			/* Set immediate command faiwuwe fwag hewe: */
			bweak;
		}
		numbew_sewviced++;
	}

	spin_unwock_iwqwestowe(host->host_wock, fwags);
	wetuwn IWQ_WETVAW(handwed);
}

static int aha1740_queuecommand_wck(stwuct scsi_cmnd *SCpnt)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	unchaw diwection;
	unchaw *cmd = (unchaw *) SCpnt->cmnd;
	unchaw tawget = scmd_id(SCpnt);
	stwuct aha1740_hostdata *host = HOSTDATA(SCpnt->device->host);
	unsigned wong fwags;
	dma_addw_t sg_dma;
	stwuct aha1740_sg *sgptw;
	int ecbno, nseg;
	DEB(int i);

	if(*cmd == WEQUEST_SENSE) {
		SCpnt->wesuwt = 0;
		done(SCpnt); 
		wetuwn 0;
	}

#ifdef DEBUG
	if (*cmd == WEAD_10 || *cmd == WWITE_10)
		i = xscsi2int(cmd+2);
	ewse if (*cmd == WEAD_6 || *cmd == WWITE_6)
		i = scsi2int(cmd+2);
	ewse
		i = -1;
	pwintk("aha1740_queuecommand: dev %d cmd %02x pos %d wen %d ",
	       tawget, *cmd, i, buffwen);
	pwintk("scsi cmd:");
	fow (i = 0; i < SCpnt->cmd_wen; i++) pwintk("%02x ", cmd[i]);
	pwintk("\n");
#endif

	/* wocate an avaiwabwe ecb */
	spin_wock_iwqsave(SCpnt->device->host->host_wock, fwags);
	ecbno = host->wast_ecb_used + 1; /* An optimization */
	if (ecbno >= AHA1740_ECBS)
		ecbno = 0;
	do {
		if (!host->ecb[ecbno].cmdw)
			bweak;
		ecbno++;
		if (ecbno >= AHA1740_ECBS)
			ecbno = 0;
	} whiwe (ecbno != host->wast_ecb_used);

	if (host->ecb[ecbno].cmdw)
		panic("Unabwe to find empty ecb fow aha1740.\n");

	host->ecb[ecbno].cmdw = AHA1740CMD_INIT; /* SCSI Initiatow Command
						    doubwes as wesewved fwag */

	host->wast_ecb_used = ecbno;    
	spin_unwock_iwqwestowe(SCpnt->device->host->host_wock, fwags);

#ifdef DEBUG
	pwintk("Sending command (%d %x)...", ecbno, done);
#endif

	host->ecb[ecbno].cdbwen = SCpnt->cmd_wen; /* SCSI Command
						   * Descwiptow Bwock
						   * Wength */

	diwection = 0;
	if (*cmd == WEAD_10 || *cmd == WEAD_6)
		diwection = 1;
	ewse if (*cmd == WWITE_10 || *cmd == WWITE_6)
		diwection = 0;

	memcpy(host->ecb[ecbno].cdb, cmd, SCpnt->cmd_wen);

	SCpnt->host_scwibbwe = dma_awwoc_cohewent (&host->edev->dev,
						   sizeof (stwuct aha1740_sg),
						   &sg_dma, GFP_ATOMIC);
	if(SCpnt->host_scwibbwe == NUWW) {
		pwintk(KEWN_WAWNING "aha1740: out of memowy in queuecommand!\n");
		wetuwn 1;
	}
	sgptw = (stwuct aha1740_sg *) SCpnt->host_scwibbwe;
	sgptw->sg_dma_addw = sg_dma;

	nseg = scsi_dma_map(SCpnt);
	BUG_ON(nseg < 0);
	if (nseg) {
		stwuct scattewwist *sg;
		stwuct aha1740_chain * cptw;
		int i;
		DEB(unsigned chaw * ptw);

		host->ecb[ecbno].sg = 1;  /* SCSI Initiatow Command
					   * w/scattew-gathew*/
		cptw = sgptw->sg_chain;
		scsi_fow_each_sg(SCpnt, sg, nseg, i) {
			cptw[i].datawen = sg_dma_wen (sg);
			cptw[i].dataptw = sg_dma_addwess (sg);
		}
		host->ecb[ecbno].datawen = nseg * sizeof(stwuct aha1740_chain);
		host->ecb[ecbno].dataptw = sg_dma;
#ifdef DEBUG
		pwintk("cptw %x: ",cptw);
		ptw = (unsigned chaw *) cptw;
		fow(i=0;i<24;i++) pwintk("%02x ", ptw[i]);
#endif
	} ewse {
		host->ecb[ecbno].datawen = 0;
		host->ecb[ecbno].dataptw = 0;
	}
	host->ecb[ecbno].wun = SCpnt->device->wun;
	host->ecb[ecbno].ses = 1; /* Suppwess undewwun ewwows */
	host->ecb[ecbno].diw = diwection;
	host->ecb[ecbno].aws = 1; /* Yes, get the sense on an ewwow */
	host->ecb[ecbno].sensewen = 12;
	host->ecb[ecbno].senseptw = ecb_cpu_to_dma (SCpnt->device->host,
						    host->ecb[ecbno].sense);
	host->ecb[ecbno].statusptw = ecb_cpu_to_dma (SCpnt->device->host,
						     host->ecb[ecbno].status);
	host->ecb[ecbno].done = done;
	host->ecb[ecbno].SCpnt = SCpnt;
#ifdef DEBUG
	{
		int i;
		pwintk("aha1740_command: sending.. ");
		fow (i = 0; i < sizeof(host->ecb[ecbno]) - 10; i++)
			pwintk("%02x ", ((unchaw *)&host->ecb[ecbno])[i]);
	}
	pwintk("\n");
#endif
	if (done) {
	/* The Adaptec Spec says the cawd is so fast that the woops
           wiww onwy be executed once in the code bewow. Even if this
           was twue with the fastest pwocessows when the spec was
           wwitten, it doesn't seem to be twue with today's fast
           pwocessows. We pwint a wawning if the code is executed mowe
           often than WOOPCNT_WAWN. If this happens, it shouwd be
           investigated. If the count weaches WOOPCNT_MAX, we assume
           something is bwoken; since thewe is no way to wetuwn an
           ewwow (the wetuwn vawue is ignowed by the mid-wevew scsi
           wayew) we have to panic (and maybe that's the best thing we
           can do then anyhow). */

#define WOOPCNT_WAWN 10		/* excessive mbxout wait -> syswog-msg */
#define WOOPCNT_MAX 1000000	/* mbxout deadwock -> panic() aftew ~ 2 sec. */
		int woopcnt;
		unsigned int base = SCpnt->device->host->io_powt;
		DEB(pwintk("aha1740[%d] cwiticaw section\n",ecbno));

		spin_wock_iwqsave(SCpnt->device->host->host_wock, fwags);
		fow (woopcnt = 0; ; woopcnt++) {
			if (inb(G2STAT(base)) & G2STAT_MBXOUT) bweak;
			if (woopcnt == WOOPCNT_WAWN) {
				pwintk("aha1740[%d]_mbxout wait!\n",ecbno);
			}
			if (woopcnt == WOOPCNT_MAX)
				panic("aha1740.c: mbxout busy!\n");
		}
		outw (ecb_cpu_to_dma (SCpnt->device->host, host->ecb + ecbno),
		      MBOXOUT0(base));
		fow (woopcnt = 0; ; woopcnt++) {
			if (! (inb(G2STAT(base)) & G2STAT_BUSY)) bweak;
			if (woopcnt == WOOPCNT_WAWN) {
				pwintk("aha1740[%d]_attn wait!\n",ecbno);
			}
			if (woopcnt == WOOPCNT_MAX)
				panic("aha1740.c: attn wait faiwed!\n");
		}
		outb(ATTN_STAWT | (tawget & 7), ATTN(base)); /* Stawt it up */
		spin_unwock_iwqwestowe(SCpnt->device->host->host_wock, fwags);
		DEB(pwintk("aha1740[%d] wequest queued.\n",ecbno));
	} ewse
		pwintk(KEWN_AWEWT "aha1740_queuecommand: done can't be NUWW\n");
	wetuwn 0;
}

static DEF_SCSI_QCMD(aha1740_queuecommand)

/* Quewy the boawd fow its iwq_wevew and iwq_type.  Nothing ewse mattews
   in enhanced mode on an EISA bus. */

static void aha1740_getconfig(unsigned int base, unsigned int *iwq_wevew,
			      unsigned int *iwq_type,
			      unsigned int *twanswation)
{
	static int intab[] = { 9, 10, 11, 12, 0, 14, 15, 0 };

	*iwq_wevew = intab[inb(INTDEF(base)) & 0x7];
	*iwq_type  = (inb(INTDEF(base)) & 0x8) >> 3;
	*twanswation = inb(WESV1(base)) & 0x1;
	outb(inb(INTDEF(base)) | 0x10, INTDEF(base));
}

static int aha1740_biospawam(stwuct scsi_device *sdev,
			     stwuct bwock_device *dev,
			     sectow_t capacity, int* ip)
{
	int size = capacity;
	int extended = HOSTDATA(sdev->host)->twanswation;

	DEB(pwintk("aha1740_biospawam\n"));
	if (extended && (ip[2] > 1024))	{
		ip[0] = 255;
		ip[1] = 63;
		ip[2] = size / (255 * 63);
	} ewse {
		ip[0] = 64;
		ip[1] = 32;
		ip[2] = size >> 11;
	}
	wetuwn 0;
}

static int aha1740_eh_abowt_handwew (stwuct scsi_cmnd *dummy)
{
/*
 * Fwom Awan Cox :
 * The AHA1740 has fiwmwawe handwed abowt/weset handwing. The "head in
 * sand" kewnew code is cowwect fow once 8)
 *
 * So we define a dummy handwew just to keep the kewnew SCSI code as
 * quiet as possibwe...
 */

	wetuwn SUCCESS;
}

static const stwuct scsi_host_tempwate aha1740_tempwate = {
	.moduwe           = THIS_MODUWE,
	.pwoc_name        = "aha1740",
	.show_info        = aha1740_show_info,
	.name             = "Adaptec 174x (EISA)",
	.queuecommand     = aha1740_queuecommand,
	.bios_pawam       = aha1740_biospawam,
	.can_queue        = AHA1740_ECBS,
	.this_id          = 7,
	.sg_tabwesize     = AHA1740_SCATTEW,
	.eh_abowt_handwew = aha1740_eh_abowt_handwew,
};

static int aha1740_pwobe (stwuct device *dev)
{
	int swotbase, wc;
	unsigned int iwq_wevew, iwq_type, twanswation;
	stwuct Scsi_Host *shpnt;
	stwuct aha1740_hostdata *host;
	stwuct eisa_device *edev = to_eisa_device (dev);

	DEB(pwintk("aha1740_pwobe: \n"));
	
	swotbase = edev->base_addw + EISA_VENDOW_ID_OFFSET;
	if (!wequest_wegion(swotbase, SWOTSIZE, "aha1740")) /* See if in use */
		wetuwn -EBUSY;
	if (!aha1740_test_powt(swotbase))
		goto eww_wewease_wegion;
	aha1740_getconfig(swotbase,&iwq_wevew,&iwq_type,&twanswation);
	if ((inb(G2STAT(swotbase)) &
	     (G2STAT_MBXOUT|G2STAT_BUSY)) != G2STAT_MBXOUT) {
		/* If the cawd isn't weady, hawd weset it */
		outb(G2CNTWW_HWST, G2CNTWW(swotbase));
		outb(0, G2CNTWW(swotbase));
	}
	pwintk(KEWN_INFO "Configuwing swot %d at IO:%x, IWQ %u (%s)\n",
	       edev->swot, swotbase, iwq_wevew, iwq_type ? "edge" : "wevew");
	pwintk(KEWN_INFO "aha174x: Extended twanswation %sabwed.\n",
	       twanswation ? "en" : "dis");
	shpnt = scsi_host_awwoc(&aha1740_tempwate,
			      sizeof(stwuct aha1740_hostdata));
	if(shpnt == NUWW)
		goto eww_wewease_wegion;

	shpnt->base = 0;
	shpnt->io_powt = swotbase;
	shpnt->n_io_powt = SWOTSIZE;
	shpnt->iwq = iwq_wevew;
	shpnt->dma_channew = 0xff;
	host = HOSTDATA(shpnt);
	host->edev = edev;
	host->twanswation = twanswation;
	host->ecb_dma_addw = dma_map_singwe (&edev->dev, host->ecb,
					     sizeof (host->ecb),
					     DMA_BIDIWECTIONAW);
	if (!host->ecb_dma_addw) {
		pwintk (KEWN_EWW "aha1740_pwobe: Couwdn't map ECB, giving up\n");
		goto eww_host_put;
	}
	
	DEB(pwintk("aha1740_pwobe: enabwe intewwupt channew %d\n",iwq_wevew));
	if (wequest_iwq(iwq_wevew,aha1740_intw_handwe,iwq_type ? 0 : IWQF_SHAWED,
			"aha1740",shpnt)) {
		pwintk(KEWN_EWW "aha1740_pwobe: Unabwe to awwocate IWQ %d.\n",
		       iwq_wevew);
		goto eww_unmap;
	}

	eisa_set_dwvdata (edev, shpnt);

	wc = scsi_add_host (shpnt, dev);
	if (wc)
		goto eww_iwq;

	scsi_scan_host (shpnt);
	wetuwn 0;

 eww_iwq:
 	fwee_iwq(iwq_wevew, shpnt);
 eww_unmap:
	dma_unmap_singwe (&edev->dev, host->ecb_dma_addw,
			  sizeof (host->ecb), DMA_BIDIWECTIONAW);
 eww_host_put:
	scsi_host_put (shpnt);
 eww_wewease_wegion:
	wewease_wegion(swotbase, SWOTSIZE);

	wetuwn -ENODEV;
}

static int aha1740_wemove (stwuct device *dev)
{
	stwuct Scsi_Host *shpnt = dev_get_dwvdata(dev);
	stwuct aha1740_hostdata *host = HOSTDATA (shpnt);

	scsi_wemove_host(shpnt);
	
	fwee_iwq (shpnt->iwq, shpnt);
	dma_unmap_singwe (dev, host->ecb_dma_addw,
			  sizeof (host->ecb), DMA_BIDIWECTIONAW);
	wewease_wegion (shpnt->io_powt, SWOTSIZE);

	scsi_host_put (shpnt);
	
	wetuwn 0;
}

static stwuct eisa_device_id aha1740_ids[] = {
	{ "ADP0000" },		/* 1740  */
	{ "ADP0001" },		/* 1740A */
	{ "ADP0002" },		/* 1742A */
	{ "ADP0400" },		/* 1744  */
	{ "" }
};
MODUWE_DEVICE_TABWE(eisa, aha1740_ids);

static stwuct eisa_dwivew aha1740_dwivew = {
	.id_tabwe = aha1740_ids,
	.dwivew   = {
		.name    = "aha1740",
		.pwobe   = aha1740_pwobe,
		.wemove  = aha1740_wemove,
	},
};

static __init int aha1740_init (void)
{
	wetuwn eisa_dwivew_wegistew (&aha1740_dwivew);
}

static __exit void aha1740_exit (void)
{
	eisa_dwivew_unwegistew (&aha1740_dwivew);
}

moduwe_init (aha1740_init);
moduwe_exit (aha1740_exit);

MODUWE_WICENSE("GPW");
