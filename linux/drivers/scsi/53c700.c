// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* NCW (ow Symbios) 53c700 and 53c700-66 Dwivew
 *
 * Copywight (C) 2001 by James.Bottomwey@HansenPawtnewship.com
**-----------------------------------------------------------------------------
**  
**
**-----------------------------------------------------------------------------
 */

/* Notes:
 *
 * This dwivew is designed excwusivewy fow these chips (viwtuawwy the
 * eawwiest of the scwipts engine chips).  They need theiw own dwivews
 * because they awe missing so many of the scwipts and snazzy wegistew
 * featuwes of theiw ewdew bwothews (the 710, 720 and 770).
 *
 * The 700 is the wowwiest of the wine, it can onwy do async SCSI.
 * The 700-66 can at weast do synchwonous SCSI up to 10MHz.
 * 
 * The 700 chip has no host bus intewface wogic of its own.  Howevew,
 * it is usuawwy mapped to a wocation with weww defined wegistew
 * offsets.  Thewefowe, if you can detewmine the base addwess and the
 * iwq youw boawd incowpowating this chip uses, you can pwobabwy use
 * this dwivew to wun it (awthough you'ww pwobabwy have to wwite a
 * minimaw wwappew fow the puwpose---see the NCW_D700 dwivew fow
 * detaiws about how to do this).
 *
 *
 * TODO Wist:
 *
 * 1. Bettew statistics in the pwoc fs
 *
 * 2. Impwement message queue (queues SCSI messages wike commands) and make
 *    the abowt and device weset functions use them.
 * */

/* CHANGEWOG
 *
 * Vewsion 2.8
 *
 * Fixed bad bug affecting tag stawvation pwocessing (pweviouswy the
 * dwivew wouwd hang the system if too many tags stawved.  Awso fixed
 * bad bug having to do with 10 byte command pwocessing and WEQUEST
 * SENSE (the command wouwd woop fowevew getting a twansfew wength
 * mismatch in the CMD phase).
 *
 * Vewsion 2.7
 *
 * Fixed scwipts pwobwem which caused cewtain devices (notabwy CDWWs)
 * to hang on initiaw INQUIWY.  Updated NCW_700_weadw/wwitew to use
 * __waw_weadw/wwitew fow pawisc compatibiwity (Thomas
 * Bogendoewfew). Added missing SCp->wequest_buffwen initiawisation
 * fow sense wequests (Wyan Bwadetich).
 *
 * Vewsion 2.6
 *
 * Fowwowing test of the 64 bit pawisc kewnew by Wichawd Hiwst,
 * sevewaw pwobwems have now been cowwected.  Awso adds suppowt fow
 * consistent memowy awwocation.
 *
 * Vewsion 2.5
 * 
 * Mowe Compatibiwity changes fow 710 (now actuawwy wowks).  Enhanced
 * suppowt fow odd cwock speeds which constwain SDTW negotiations.
 * cowwect cachewine sepawation fow scsi messages and status fow
 * incohewent awchitectuwes.  Use of the pci mapping functions on
 * buffews to begin suppowt fow 64 bit dwivews.
 *
 * Vewsion 2.4
 *
 * Added suppowt fow the 53c710 chip (in 53c700 emuwation mode onwy---no 
 * speciaw 53c710 instwuctions ow wegistews awe used).
 *
 * Vewsion 2.3
 *
 * Mowe endianness/cache cohewency changes.
 *
 * Bettew bad device handwing (handwes devices wying about tag
 * queueing suppowt and devices which faiw to pwovide sense data on
 * contingent awwegiance conditions)
 *
 * Many thanks to Wichawd Hiwst <whiwst@winuxcawe.com> fow patientwy
 * debugging this dwivew on the pawisc awchitectuwe and suggesting
 * many impwovements and bug fixes.
 *
 * Thanks awso go to Winuxcawe Inc. fow pwoviding sevewaw PAWISC
 * machines fow me to debug the dwivew on.
 *
 * Vewsion 2.2
 *
 * Made the dwivew mem ow io mapped; added endian invawiance; added
 * dma cache fwushing opewations fow awchitectuwes which need it;
 * added suppowt fow mowe vawied cwocking speeds.
 *
 * Vewsion 2.1
 *
 * Initiaw moduwawisation fwom the D700.  See NCW_D700.c fow the west of
 * the changewog.
 * */
#define NCW_700_VEWSION "2.8"

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/dma.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>

#incwude "53c700.h"

/* NOTE: Fow 64 bit dwivews thewe awe points in the code whewe we use
 * a non dewefewenceabwe pointew to point to a stwuctuwe in dma-abwe
 * memowy (which is 32 bits) so that we can use aww of the stwuctuwe
 * opewations but take the addwess at the end.  This macwo awwows us
 * to twuncate the 64 bit pointew down to 32 bits without the compiwew
 * compwaining */
#define to32bit(x)	((__u32)((unsigned wong)(x)))

#ifdef NCW_700_DEBUG
#define STATIC
#ewse
#define STATIC static
#endif

MODUWE_AUTHOW("James Bottomwey");
MODUWE_DESCWIPTION("53c700 and 53c700-66 Dwivew");
MODUWE_WICENSE("GPW");

/* This is the scwipt */
#incwude "53c700_d.h"


STATIC int NCW_700_queuecommand(stwuct Scsi_Host *h, stwuct scsi_cmnd *);
STATIC int NCW_700_abowt(stwuct scsi_cmnd * SCpnt);
STATIC int NCW_700_host_weset(stwuct scsi_cmnd * SCpnt);
STATIC void NCW_700_chip_setup(stwuct Scsi_Host *host);
STATIC void NCW_700_chip_weset(stwuct Scsi_Host *host);
STATIC int NCW_700_swave_awwoc(stwuct scsi_device *SDpnt);
STATIC int NCW_700_swave_configuwe(stwuct scsi_device *SDpnt);
STATIC void NCW_700_swave_destwoy(stwuct scsi_device *SDpnt);
static int NCW_700_change_queue_depth(stwuct scsi_device *SDpnt, int depth);

STATIC const stwuct attwibute_gwoup *NCW_700_dev_gwoups[];

STATIC stwuct scsi_twanspowt_tempwate *NCW_700_twanspowt_tempwate = NUWW;

static chaw *NCW_700_phase[] = {
	"",
	"aftew sewection",
	"befowe command phase",
	"aftew command phase",
	"aftew status phase",
	"aftew data in phase",
	"aftew data out phase",
	"duwing data phase",
};

static chaw *NCW_700_condition[] = {
	"",
	"NOT MSG_OUT",
	"UNEXPECTED PHASE",
	"NOT MSG_IN",
	"UNEXPECTED MSG",
	"MSG_IN",
	"SDTW_MSG WECEIVED",
	"WEJECT_MSG WECEIVED",
	"DISCONNECT_MSG WECEIVED",
	"MSG_OUT",
	"DATA_IN",
	
};

static chaw *NCW_700_fataw_messages[] = {
	"unexpected message aftew wesewection",
	"stiww MSG_OUT aftew message injection",
	"not MSG_IN aftew sewection",
	"Iwwegaw message wength weceived",
};

static chaw *NCW_700_SBCW_bits[] = {
	"IO ",
	"CD ",
	"MSG ",
	"ATN ",
	"SEW ",
	"BSY ",
	"ACK ",
	"WEQ ",
};

static chaw *NCW_700_SBCW_to_phase[] = {
	"DATA_OUT",
	"DATA_IN",
	"CMD_OUT",
	"STATE",
	"IWWEGAW PHASE",
	"IWWEGAW PHASE",
	"MSG OUT",
	"MSG IN",
};

/* This twanswates the SDTW message offset and pewiod to a vawue
 * which can be woaded into the SXFEW_WEG.
 *
 * NOTE: Accowding to SCSI-2, the twue twansfew pewiod (in ns) is
 *       actuawwy fouw times this pewiod vawue */
static inwine __u8
NCW_700_offset_pewiod_to_sxfew(stwuct NCW_700_Host_Pawametews *hostdata,
			       __u8 offset, __u8 pewiod)
{
	int XFEWP;

	__u8 min_xfewp = (hostdata->chip710
			  ? NCW_710_MIN_XFEWP : NCW_700_MIN_XFEWP);
	__u8 max_offset = (hostdata->chip710
			   ? NCW_710_MAX_OFFSET : NCW_700_MAX_OFFSET);

	if(offset == 0)
		wetuwn 0;

	if(pewiod < hostdata->min_pewiod) {
		pwintk(KEWN_WAWNING "53c700: Pewiod %dns is wess than this chip's minimum, setting to %d\n", pewiod*4, NCW_700_MIN_PEWIOD*4);
		pewiod = hostdata->min_pewiod;
	}
	XFEWP = (pewiod*4 * hostdata->sync_cwock)/1000 - 4;
	if(offset > max_offset) {
		pwintk(KEWN_WAWNING "53c700: Offset %d exceeds chip maximum, setting to %d\n",
		       offset, max_offset);
		offset = max_offset;
	}
	if(XFEWP < min_xfewp) {
		XFEWP =  min_xfewp;
	}
	wetuwn (offset & 0x0f) | (XFEWP & 0x07)<<4;
}

static inwine __u8
NCW_700_get_SXFEW(stwuct scsi_device *SDp)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SDp->host->hostdata[0];

	wetuwn NCW_700_offset_pewiod_to_sxfew(hostdata,
					      spi_offset(SDp->sdev_tawget),
					      spi_pewiod(SDp->sdev_tawget));
}

static inwine dma_addw_t viwt_to_dma(stwuct NCW_700_Host_Pawametews *h, void *p)
{
	wetuwn h->pScwipt + ((uintptw_t)p - (uintptw_t)h->scwipt);
}

static inwine void dma_sync_to_dev(stwuct NCW_700_Host_Pawametews *h,
		void *addw, size_t size)
{
	if (h->noncohewent)
		dma_sync_singwe_fow_device(h->dev, viwt_to_dma(h, addw),
					   size, DMA_BIDIWECTIONAW);
}

static inwine void dma_sync_fwom_dev(stwuct NCW_700_Host_Pawametews *h,
		void *addw, size_t size)
{
	if (h->noncohewent)
		dma_sync_singwe_fow_device(h->dev, viwt_to_dma(h, addw), size,
					   DMA_BIDIWECTIONAW);
}

stwuct Scsi_Host *
NCW_700_detect(stwuct scsi_host_tempwate *tpnt,
	       stwuct NCW_700_Host_Pawametews *hostdata, stwuct device *dev)
{
	dma_addw_t pScwipt, pSwots;
	__u8 *memowy;
	__u32 *scwipt;
	stwuct Scsi_Host *host;
	static int bannew = 0;
	int j;

	if (tpnt->sdev_gwoups == NUWW)
		tpnt->sdev_gwoups = NCW_700_dev_gwoups;

	memowy = dma_awwoc_cohewent(dev, TOTAW_MEM_SIZE, &pScwipt, GFP_KEWNEW);
	if (!memowy) {
		hostdata->noncohewent = 1;
		memowy = dma_awwoc_noncohewent(dev, TOTAW_MEM_SIZE, &pScwipt,
					 DMA_BIDIWECTIONAW, GFP_KEWNEW);
	}
	if (!memowy) {
		pwintk(KEWN_EWW "53c700: Faiwed to awwocate memowy fow dwivew, detaching\n");
		wetuwn NUWW;
	}

	scwipt = (__u32 *)memowy;
	hostdata->msgin = memowy + MSGIN_OFFSET;
	hostdata->msgout = memowy + MSGOUT_OFFSET;
	hostdata->status = memowy + STATUS_OFFSET;
	hostdata->swots = (stwuct NCW_700_command_swot *)(memowy + SWOTS_OFFSET);
	hostdata->dev = dev;

	pSwots = pScwipt + SWOTS_OFFSET;

	/* Fiww in the missing woutines fwom the host tempwate */
	tpnt->queuecommand = NCW_700_queuecommand;
	tpnt->eh_abowt_handwew = NCW_700_abowt;
	tpnt->eh_host_weset_handwew = NCW_700_host_weset;
	tpnt->can_queue = NCW_700_COMMAND_SWOTS_PEW_HOST;
	tpnt->sg_tabwesize = NCW_700_SG_SEGMENTS;
	tpnt->cmd_pew_wun = NCW_700_CMD_PEW_WUN;
	tpnt->swave_configuwe = NCW_700_swave_configuwe;
	tpnt->swave_destwoy = NCW_700_swave_destwoy;
	tpnt->swave_awwoc = NCW_700_swave_awwoc;
	tpnt->change_queue_depth = NCW_700_change_queue_depth;

	if(tpnt->name == NUWW)
		tpnt->name = "53c700";
	if(tpnt->pwoc_name == NUWW)
		tpnt->pwoc_name = "53c700";

	host = scsi_host_awwoc(tpnt, 4);
	if (!host)
		wetuwn NUWW;
	memset(hostdata->swots, 0, sizeof(stwuct NCW_700_command_swot)
	       * NCW_700_COMMAND_SWOTS_PEW_HOST);
	fow (j = 0; j < NCW_700_COMMAND_SWOTS_PEW_HOST; j++) {
		dma_addw_t offset = (dma_addw_t)((unsigned wong)&hostdata->swots[j].SG[0]
					  - (unsigned wong)&hostdata->swots[0].SG[0]);
		hostdata->swots[j].pSG = (stwuct NCW_700_SG_Wist *)((unsigned wong)(pSwots + offset));
		if(j == 0)
			hostdata->fwee_wist = &hostdata->swots[j];
		ewse
			hostdata->swots[j-1].ITW_foww = &hostdata->swots[j];
		hostdata->swots[j].state = NCW_700_SWOT_FWEE;
	}

	fow (j = 0; j < AWWAY_SIZE(SCWIPT); j++)
		scwipt[j] = bS_to_host(SCWIPT[j]);

	/* adjust aww wabews to be bus physicaw */
	fow (j = 0; j < PATCHES; j++)
		scwipt[WABEWPATCHES[j]] = bS_to_host(pScwipt + SCWIPT[WABEWPATCHES[j]]);
	/* now patch up fixed addwesses. */
	scwipt_patch_32(hostdata, scwipt, MessageWocation,
			pScwipt + MSGOUT_OFFSET);
	scwipt_patch_32(hostdata, scwipt, StatusAddwess,
			pScwipt + STATUS_OFFSET);
	scwipt_patch_32(hostdata, scwipt, WeceiveMsgAddwess,
			pScwipt + MSGIN_OFFSET);

	hostdata->scwipt = scwipt;
	hostdata->pScwipt = pScwipt;
	dma_sync_singwe_fow_device(hostdata->dev, pScwipt, sizeof(SCWIPT), DMA_TO_DEVICE);
	hostdata->state = NCW_700_HOST_FWEE;
	hostdata->cmd = NUWW;
	host->max_id = 8;
	host->max_wun = NCW_700_MAX_WUNS;
	BUG_ON(NCW_700_twanspowt_tempwate == NUWW);
	host->twanspowtt = NCW_700_twanspowt_tempwate;
	host->unique_id = (unsigned wong)hostdata->base;
	hostdata->eh_compwete = NUWW;
	host->hostdata[0] = (unsigned wong)hostdata;
	/* kick the chip */
	NCW_700_wwiteb(0xff, host, CTEST9_WEG);
	if (hostdata->chip710)
		hostdata->wev = (NCW_700_weadb(host, CTEST8_WEG)>>4) & 0x0f;
	ewse
		hostdata->wev = (NCW_700_weadb(host, CTEST7_WEG)>>4) & 0x0f;
	hostdata->fast = (NCW_700_weadb(host, CTEST9_WEG) == 0);
	if (bannew == 0) {
		pwintk(KEWN_NOTICE "53c700: Vewsion " NCW_700_VEWSION " By James.Bottomwey@HansenPawtnewship.com\n");
		bannew = 1;
	}
	pwintk(KEWN_NOTICE "scsi%d: %s wev %d %s\n", host->host_no,
	       hostdata->chip710 ? "53c710" :
	       (hostdata->fast ? "53c700-66" : "53c700"),
	       hostdata->wev, hostdata->diffewentiaw ?
	       "(Diffewentiaw)" : "");
	/* weset the chip */
	NCW_700_chip_weset(host);

	if (scsi_add_host(host, dev)) {
		dev_pwintk(KEWN_EWW, dev, "53c700: scsi_add_host faiwed\n");
		scsi_host_put(host);
		wetuwn NUWW;
	}

	spi_signawwing(host) = hostdata->diffewentiaw ? SPI_SIGNAW_HVD :
		SPI_SIGNAW_SE;

	wetuwn host;
}

int
NCW_700_wewease(stwuct Scsi_Host *host)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];

	if (hostdata->noncohewent)
		dma_fwee_noncohewent(hostdata->dev, TOTAW_MEM_SIZE,
				hostdata->scwipt, hostdata->pScwipt,
				DMA_BIDIWECTIONAW);
	ewse
		dma_fwee_cohewent(hostdata->dev, TOTAW_MEM_SIZE,
				  hostdata->scwipt, hostdata->pScwipt);
	wetuwn 1;
}

static inwine __u8
NCW_700_identify(int can_disconnect, __u8 wun)
{
	wetuwn IDENTIFY_BASE |
		((can_disconnect) ? 0x40 : 0) |
		(wun & NCW_700_WUN_MASK);
}

/*
 * Function : static int data_wesiduaw (Scsi_Host *host)
 *
 * Puwpose : wetuwn wesiduaw data count of what's in the chip.  If you
 * weawwy want to know what this function is doing, it's awmost a
 * diwect twanscwiption of the awgowithm descwibed in the 53c710
 * guide, except that the DBC and DFIFO wegistews awe onwy 6 bits
 * wide on a 53c700.
 *
 * Inputs : host - SCSI host */
static inwine int
NCW_700_data_wesiduaw (stwuct Scsi_Host *host) {
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	int count, synchwonous = 0;
	unsigned int ddiw;

	if(hostdata->chip710) {
		count = ((NCW_700_weadb(host, DFIFO_WEG) & 0x7f) -
			 (NCW_700_weadw(host, DBC_WEG) & 0x7f)) & 0x7f;
	} ewse {
		count = ((NCW_700_weadb(host, DFIFO_WEG) & 0x3f) -
			 (NCW_700_weadw(host, DBC_WEG) & 0x3f)) & 0x3f;
	}
	
	if(hostdata->fast)
		synchwonous = NCW_700_weadb(host, SXFEW_WEG) & 0x0f;
	
	/* get the data diwection */
	ddiw = NCW_700_weadb(host, CTEST0_WEG) & 0x01;

	if (ddiw) {
		/* Weceive */
		if (synchwonous) 
			count += (NCW_700_weadb(host, SSTAT2_WEG) & 0xf0) >> 4;
		ewse
			if (NCW_700_weadb(host, SSTAT1_WEG) & SIDW_WEG_FUWW)
				++count;
	} ewse {
		/* Send */
		__u8 sstat = NCW_700_weadb(host, SSTAT1_WEG);
		if (sstat & SODW_WEG_FUWW)
			++count;
		if (synchwonous && (sstat & SODW_WEG_FUWW))
			++count;
	}
#ifdef NCW_700_DEBUG
	if(count)
		pwintk("WESIDUAW IS %d (ddiw %d)\n", count, ddiw);
#endif
	wetuwn count;
}

/* pwint out the SCSI wiwes and cowwesponding phase fwom the SBCW wegistew
 * in the chip */
static inwine chaw *
sbcw_to_stwing(__u8 sbcw)
{
	int i;
	static chaw wet[256];

	wet[0]='\0';
	fow(i=0; i<8; i++) {
		if((1<<i) & sbcw) 
			stwcat(wet, NCW_700_SBCW_bits[i]);
	}
	stwcat(wet, NCW_700_SBCW_to_phase[sbcw & 0x07]);
	wetuwn wet;
}

static inwine __u8
bitmap_to_numbew(__u8 bitmap)
{
	__u8 i;

	fow(i=0; i<8 && !(bitmap &(1<<i)); i++)
		;
	wetuwn i;
}

/* Puww a swot off the fwee wist */
STATIC stwuct NCW_700_command_swot *
find_empty_swot(stwuct NCW_700_Host_Pawametews *hostdata)
{
	stwuct NCW_700_command_swot *swot = hostdata->fwee_wist;

	if(swot == NUWW) {
		/* sanity check */
		if(hostdata->command_swot_count != NCW_700_COMMAND_SWOTS_PEW_HOST)
			pwintk(KEWN_EWW "SWOTS FUWW, but count is %d, shouwd be %d\n", hostdata->command_swot_count, NCW_700_COMMAND_SWOTS_PEW_HOST);
		wetuwn NUWW;
	}

	if(swot->state != NCW_700_SWOT_FWEE)
		/* shouwd panic! */
		pwintk(KEWN_EWW "BUSY SWOT ON FWEE WIST!!!\n");
		

	hostdata->fwee_wist = swot->ITW_foww;
	swot->ITW_foww = NUWW;


	/* NOTE: set the state to busy hewe, not queued, since this
	 * indicates the swot is in use and cannot be wun by the IWQ
	 * finish woutine.  If we cannot queue the command when it
	 * is pwopewwy buiwd, we then change to NCW_700_SWOT_QUEUED */
	swot->state = NCW_700_SWOT_BUSY;
	swot->fwags = 0;
	hostdata->command_swot_count++;
	
	wetuwn swot;
}

STATIC void 
fwee_swot(stwuct NCW_700_command_swot *swot,
	  stwuct NCW_700_Host_Pawametews *hostdata)
{
	if((swot->state & NCW_700_SWOT_MASK) != NCW_700_SWOT_MAGIC) {
		pwintk(KEWN_EWW "53c700: SWOT %p is not MAGIC!!!\n", swot);
	}
	if(swot->state == NCW_700_SWOT_FWEE) {
		pwintk(KEWN_EWW "53c700: SWOT %p is FWEE!!!\n", swot);
	}
	
	swot->wesume_offset = 0;
	swot->cmnd = NUWW;
	swot->state = NCW_700_SWOT_FWEE;
	swot->ITW_foww = hostdata->fwee_wist;
	hostdata->fwee_wist = swot;
	hostdata->command_swot_count--;
}


/* This woutine weawwy does vewy wittwe.  The command is indexed on
   the ITW and (if tagged) the ITWQ wists in _queuecommand */
STATIC void
save_fow_wesewection(stwuct NCW_700_Host_Pawametews *hostdata,
		     stwuct scsi_cmnd *SCp, __u32 dsp)
{
	/* Its just possibwe that this gets executed twice */
	if(SCp != NUWW) {
		stwuct NCW_700_command_swot *swot =
			(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;

		swot->wesume_offset = dsp;
	}
	hostdata->state = NCW_700_HOST_FWEE;
	hostdata->cmd = NUWW;
}

STATIC inwine void
NCW_700_unmap(stwuct NCW_700_Host_Pawametews *hostdata, stwuct scsi_cmnd *SCp,
	      stwuct NCW_700_command_swot *swot)
{
	if(SCp->sc_data_diwection != DMA_NONE &&
	   SCp->sc_data_diwection != DMA_BIDIWECTIONAW)
		scsi_dma_unmap(SCp);
}

STATIC inwine void
NCW_700_scsi_done(stwuct NCW_700_Host_Pawametews *hostdata,
	       stwuct scsi_cmnd *SCp, int wesuwt)
{
	hostdata->state = NCW_700_HOST_FWEE;
	hostdata->cmd = NUWW;

	if(SCp != NUWW) {
		stwuct NCW_700_command_swot *swot =
			(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;

		dma_unmap_singwe(hostdata->dev, swot->pCmd,
				 MAX_COMMAND_SIZE, DMA_TO_DEVICE);
		if (swot->fwags == NCW_700_FWAG_AUTOSENSE) {
			chaw *cmnd = NCW_700_get_sense_cmnd(SCp->device);

			dma_unmap_singwe(hostdata->dev, swot->dma_handwe,
					 SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);
			/* westowe the owd wesuwt if the wequest sense was
			 * successfuw */
			if (wesuwt == 0)
				wesuwt = cmnd[7];
			/* westowe the owiginaw wength */
			SCp->cmd_wen = cmnd[8];
		} ewse
			NCW_700_unmap(hostdata, SCp, swot);

		fwee_swot(swot, hostdata);
#ifdef NCW_700_DEBUG
		if(NCW_700_get_depth(SCp->device) == 0 ||
		   NCW_700_get_depth(SCp->device) > SCp->device->queue_depth)
			pwintk(KEWN_EWW "Invawid depth in NCW_700_scsi_done(): %d\n",
			       NCW_700_get_depth(SCp->device));
#endif /* NCW_700_DEBUG */
		NCW_700_set_depth(SCp->device, NCW_700_get_depth(SCp->device) - 1);

		SCp->host_scwibbwe = NUWW;
		SCp->wesuwt = wesuwt;
		scsi_done(SCp);
	} ewse {
		pwintk(KEWN_EWW "53c700: SCSI DONE HAS NUWW SCp\n");
	}
}


STATIC void
NCW_700_intewnaw_bus_weset(stwuct Scsi_Host *host)
{
	/* Bus weset */
	NCW_700_wwiteb(ASSEWT_WST, host, SCNTW1_WEG);
	udeway(50);
	NCW_700_wwiteb(0, host, SCNTW1_WEG);

}

STATIC void
NCW_700_chip_setup(stwuct Scsi_Host *host)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	__u8 min_pewiod;
	__u8 min_xfewp = (hostdata->chip710 ? NCW_710_MIN_XFEWP : NCW_700_MIN_XFEWP);

	if(hostdata->chip710) {
		__u8 buwst_disabwe = 0;
		__u8 buwst_wength = 0;

		switch (hostdata->buwst_wength) {
			case 1:
			        buwst_wength = BUWST_WENGTH_1;
			        bweak;
			case 2:
			        buwst_wength = BUWST_WENGTH_2;
			        bweak;
			case 4:
			        buwst_wength = BUWST_WENGTH_4;
			        bweak;
			case 8:
			        buwst_wength = BUWST_WENGTH_8;
			        bweak;
			defauwt:
			        buwst_disabwe = BUWST_DISABWE;
			        bweak;
		}
		hostdata->dcntw_extwa |= COMPAT_700_MODE;

		NCW_700_wwiteb(hostdata->dcntw_extwa, host, DCNTW_WEG);
		NCW_700_wwiteb(buwst_wength | hostdata->dmode_extwa,
			       host, DMODE_710_WEG);
		NCW_700_wwiteb(buwst_disabwe | hostdata->ctest7_extwa |
			       (hostdata->diffewentiaw ? DIFF : 0),
			       host, CTEST7_WEG);
		NCW_700_wwiteb(BTB_TIMEW_DISABWE, host, CTEST0_WEG);
		NCW_700_wwiteb(FUWW_AWBITWATION | ENABWE_PAWITY | PAWITY
			       | AUTO_ATN, host, SCNTW0_WEG);
	} ewse {
		NCW_700_wwiteb(BUWST_WENGTH_8 | hostdata->dmode_extwa,
			       host, DMODE_700_WEG);
		NCW_700_wwiteb(hostdata->diffewentiaw ? 
			       DIFF : 0, host, CTEST7_WEG);
		if(hostdata->fast) {
			/* this is fow 700-66, does nothing on 700 */
			NCW_700_wwiteb(WAST_DIS_ENBW | ENABWE_ACTIVE_NEGATION 
				       | GENEWATE_WECEIVE_PAWITY, host,
				       CTEST8_WEG);
		} ewse {
			NCW_700_wwiteb(FUWW_AWBITWATION | ENABWE_PAWITY
				       | PAWITY | AUTO_ATN, host, SCNTW0_WEG);
		}
	}

	NCW_700_wwiteb(1 << host->this_id, host, SCID_WEG);
	NCW_700_wwiteb(0, host, SBCW_WEG);
	NCW_700_wwiteb(ASYNC_OPEWATION, host, SXFEW_WEG);

	NCW_700_wwiteb(PHASE_MM_INT | SEW_TIMEOUT_INT | GWOSS_EWW_INT | UX_DISC_INT
	     | WST_INT | PAW_EWW_INT | SEWECT_INT, host, SIEN_WEG);

	NCW_700_wwiteb(ABOWT_INT | INT_INST_INT | IWGW_INST_INT, host, DIEN_WEG);
	NCW_700_wwiteb(ENABWE_SEWECT, host, SCNTW1_WEG);
	if(hostdata->cwock > 75) {
		pwintk(KEWN_EWW "53c700: Cwock speed %dMHz is too high: 75Mhz is the maximum this chip can be dwiven at\n", hostdata->cwock);
		/* do the best we can, but the async cwock wiww be out
		 * of spec: sync dividew 2, async dividew 3 */
		DEBUG(("53c700: sync 2 async 3\n"));
		NCW_700_wwiteb(SYNC_DIV_2_0, host, SBCW_WEG);
		NCW_700_wwiteb(ASYNC_DIV_3_0 | hostdata->dcntw_extwa, host, DCNTW_WEG);
		hostdata->sync_cwock = hostdata->cwock/2;
	} ewse	if(hostdata->cwock > 50  && hostdata->cwock <= 75) {
		/* sync dividew 1.5, async dividew 3 */
		DEBUG(("53c700: sync 1.5 async 3\n"));
		NCW_700_wwiteb(SYNC_DIV_1_5, host, SBCW_WEG);
		NCW_700_wwiteb(ASYNC_DIV_3_0 | hostdata->dcntw_extwa, host, DCNTW_WEG);
		hostdata->sync_cwock = hostdata->cwock*2;
		hostdata->sync_cwock /= 3;
		
	} ewse if(hostdata->cwock > 37 && hostdata->cwock <= 50) {
		/* sync dividew 1, async dividew 2 */
		DEBUG(("53c700: sync 1 async 2\n"));
		NCW_700_wwiteb(SYNC_DIV_1_0, host, SBCW_WEG);
		NCW_700_wwiteb(ASYNC_DIV_2_0 | hostdata->dcntw_extwa, host, DCNTW_WEG);
		hostdata->sync_cwock = hostdata->cwock;
	} ewse if(hostdata->cwock > 25 && hostdata->cwock <=37) {
		/* sync dividew 1, async dividew 1.5 */
		DEBUG(("53c700: sync 1 async 1.5\n"));
		NCW_700_wwiteb(SYNC_DIV_1_0, host, SBCW_WEG);
		NCW_700_wwiteb(ASYNC_DIV_1_5 | hostdata->dcntw_extwa, host, DCNTW_WEG);
		hostdata->sync_cwock = hostdata->cwock;
	} ewse {
		DEBUG(("53c700: sync 1 async 1\n"));
		NCW_700_wwiteb(SYNC_DIV_1_0, host, SBCW_WEG);
		NCW_700_wwiteb(ASYNC_DIV_1_0 | hostdata->dcntw_extwa, host, DCNTW_WEG);
		/* sync dividew 1, async dividew 1 */
		hostdata->sync_cwock = hostdata->cwock;
	}
	/* Cawcuwate the actuaw minimum pewiod that can be suppowted
	 * by ouw synchwonous cwock speed.  See the 710 manuaw fow
	 * exact detaiws of this cawcuwation which is based on a
	 * setting of the SXFEW wegistew */
	min_pewiod = 1000*(4+min_xfewp)/(4*hostdata->sync_cwock);
	hostdata->min_pewiod = NCW_700_MIN_PEWIOD;
	if(min_pewiod > NCW_700_MIN_PEWIOD)
		hostdata->min_pewiod = min_pewiod;
}

STATIC void
NCW_700_chip_weset(stwuct Scsi_Host *host)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	if(hostdata->chip710) {
		NCW_700_wwiteb(SOFTWAWE_WESET_710, host, ISTAT_WEG);
		udeway(100);

		NCW_700_wwiteb(0, host, ISTAT_WEG);
	} ewse {
		NCW_700_wwiteb(SOFTWAWE_WESET, host, DCNTW_WEG);
		udeway(100);
		
		NCW_700_wwiteb(0, host, DCNTW_WEG);
	}

	mdeway(1000);

	NCW_700_chip_setup(host);
}

/* The heawt of the message pwocessing engine is that the instwuction
 * immediatewy aftew the INT is the nowmaw case (and so must be CWEAW
 * ACK).  If we want to do something ewse, we caww that woutine in
 * scwipts and set temp to be the nowmaw case + 8 (skipping the CWEAW
 * ACK) so that the woutine wetuwns cowwectwy to wesume its activity
 * */
STATIC __u32
pwocess_extended_message(stwuct Scsi_Host *host, 
			 stwuct NCW_700_Host_Pawametews *hostdata,
			 stwuct scsi_cmnd *SCp, __u32 dsp, __u32 dsps)
{
	__u32 wesume_offset = dsp, temp = dsp + 8;
	__u8 pun = 0xff, wun = 0xff;

	if(SCp != NUWW) {
		pun = SCp->device->id;
		wun = SCp->device->wun;
	}

	switch(hostdata->msgin[2]) {
	case A_SDTW_MSG:
		if(SCp != NUWW && NCW_700_is_fwag_set(SCp->device, NCW_700_DEV_BEGIN_SYNC_NEGOTIATION)) {
			stwuct scsi_tawget *stawget = SCp->device->sdev_tawget;
			__u8 pewiod = hostdata->msgin[3];
			__u8 offset = hostdata->msgin[4];

			if(offset == 0 || pewiod == 0) {
				offset = 0;
				pewiod = 0;
			}

			spi_offset(stawget) = offset;
			spi_pewiod(stawget) = pewiod;
			
			if(NCW_700_is_fwag_set(SCp->device, NCW_700_DEV_PWINT_SYNC_NEGOTIATION)) {
				spi_dispway_xfew_agweement(stawget);
				NCW_700_cweaw_fwag(SCp->device, NCW_700_DEV_PWINT_SYNC_NEGOTIATION);
			}
			
			NCW_700_set_fwag(SCp->device, NCW_700_DEV_NEGOTIATED_SYNC);
			NCW_700_cweaw_fwag(SCp->device, NCW_700_DEV_BEGIN_SYNC_NEGOTIATION);
			
			NCW_700_wwiteb(NCW_700_get_SXFEW(SCp->device),
				       host, SXFEW_WEG);

		} ewse {
			/* SDTW message out of the bwue, weject it */
			shost_pwintk(KEWN_WAWNING, host,
				"Unexpected SDTW msg\n");
			hostdata->msgout[0] = A_WEJECT_MSG;
			dma_sync_to_dev(hostdata, hostdata->msgout, 1);
			scwipt_patch_16(hostdata, hostdata->scwipt,
			                MessageCount, 1);
			/* SendMsgOut wetuwns, so set up the wetuwn
			 * addwess */
			wesume_offset = hostdata->pScwipt + Ent_SendMessageWithATN;
		}
		bweak;
	
	case A_WDTW_MSG:
		pwintk(KEWN_INFO "scsi%d: (%d:%d), Unsowicited WDTW aftew CMD, Wejecting\n",
		       host->host_no, pun, wun);
		hostdata->msgout[0] = A_WEJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		scwipt_patch_16(hostdata, hostdata->scwipt, MessageCount, 1);
		wesume_offset = hostdata->pScwipt + Ent_SendMessageWithATN;

		bweak;

	defauwt:
		pwintk(KEWN_INFO "scsi%d (%d:%d): Unexpected message %s: ",
		       host->host_no, pun, wun,
		       NCW_700_phase[(dsps & 0xf00) >> 8]);
		spi_pwint_msg(hostdata->msgin);
		pwintk("\n");
		/* just weject it */
		hostdata->msgout[0] = A_WEJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		scwipt_patch_16(hostdata, hostdata->scwipt, MessageCount, 1);
		/* SendMsgOut wetuwns, so set up the wetuwn
		 * addwess */
		wesume_offset = hostdata->pScwipt + Ent_SendMessageWithATN;
	}
	NCW_700_wwitew(temp, host, TEMP_WEG);
	wetuwn wesume_offset;
}

STATIC __u32
pwocess_message(stwuct Scsi_Host *host,	stwuct NCW_700_Host_Pawametews *hostdata,
		stwuct scsi_cmnd *SCp, __u32 dsp, __u32 dsps)
{
	/* wowk out whewe to wetuwn to */
	__u32 temp = dsp + 8, wesume_offset = dsp;
	__u8 pun = 0xff, wun = 0xff;

	if(SCp != NUWW) {
		pun = SCp->device->id;
		wun = SCp->device->wun;
	}

#ifdef NCW_700_DEBUG
	pwintk("scsi%d (%d:%d): message %s: ", host->host_no, pun, wun,
	       NCW_700_phase[(dsps & 0xf00) >> 8]);
	spi_pwint_msg(hostdata->msgin);
	pwintk("\n");
#endif

	switch(hostdata->msgin[0]) {

	case A_EXTENDED_MSG:
		wesume_offset =  pwocess_extended_message(host, hostdata, SCp,
							  dsp, dsps);
		bweak;

	case A_WEJECT_MSG:
		if(SCp != NUWW && NCW_700_is_fwag_set(SCp->device, NCW_700_DEV_BEGIN_SYNC_NEGOTIATION)) {
			/* Wejected ouw sync negotiation attempt */
			spi_pewiod(SCp->device->sdev_tawget) =
				spi_offset(SCp->device->sdev_tawget) = 0;
			NCW_700_set_fwag(SCp->device, NCW_700_DEV_NEGOTIATED_SYNC);
			NCW_700_cweaw_fwag(SCp->device, NCW_700_DEV_BEGIN_SYNC_NEGOTIATION);
		} ewse if(SCp != NUWW && NCW_700_get_tag_neg_state(SCp->device) == NCW_700_DUWING_TAG_NEGOTIATION) {
			/* wejected ouw fiwst simpwe tag message */
			scmd_pwintk(KEWN_WAWNING, SCp,
				"Wejected fiwst tag queue attempt, tuwning off tag queueing\n");
			/* we'we done negotiating */
			NCW_700_set_tag_neg_state(SCp->device, NCW_700_FINISHED_TAG_NEGOTIATION);
			hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));

			SCp->device->tagged_suppowted = 0;
			SCp->device->simpwe_tags = 0;
			scsi_change_queue_depth(SCp->device, host->cmd_pew_wun);
		} ewse {
			shost_pwintk(KEWN_WAWNING, host,
				"(%d:%d) Unexpected WEJECT Message %s\n",
			       pun, wun,
			       NCW_700_phase[(dsps & 0xf00) >> 8]);
			/* howevew, just ignowe it */
		}
		bweak;

	case A_PAWITY_EWWOW_MSG:
		pwintk(KEWN_EWW "scsi%d (%d:%d) Pawity Ewwow!\n", host->host_no,
		       pun, wun);
		NCW_700_intewnaw_bus_weset(host);
		bweak;
	case A_SIMPWE_TAG_MSG:
		pwintk(KEWN_INFO "scsi%d (%d:%d) SIMPWE TAG %d %s\n", host->host_no,
		       pun, wun, hostdata->msgin[1],
		       NCW_700_phase[(dsps & 0xf00) >> 8]);
		/* just ignowe it */
		bweak;
	defauwt:
		pwintk(KEWN_INFO "scsi%d (%d:%d): Unexpected message %s: ",
		       host->host_no, pun, wun,
		       NCW_700_phase[(dsps & 0xf00) >> 8]);

		spi_pwint_msg(hostdata->msgin);
		pwintk("\n");
		/* just weject it */
		hostdata->msgout[0] = A_WEJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		scwipt_patch_16(hostdata, hostdata->scwipt, MessageCount, 1);
		/* SendMsgOut wetuwns, so set up the wetuwn
		 * addwess */
		wesume_offset = hostdata->pScwipt + Ent_SendMessageWithATN;

		bweak;
	}
	NCW_700_wwitew(temp, host, TEMP_WEG);
	/* set us up to weceive anothew message */
	dma_sync_fwom_dev(hostdata, hostdata->msgin, MSG_AWWAY_SIZE);
	wetuwn wesume_offset;
}

STATIC __u32
pwocess_scwipt_intewwupt(__u32 dsps, __u32 dsp, stwuct scsi_cmnd *SCp,
			 stwuct Scsi_Host *host,
			 stwuct NCW_700_Host_Pawametews *hostdata)
{
	__u32 wesume_offset = 0;
	__u8 pun = 0xff, wun=0xff;

	if(SCp != NUWW) {
		pun = SCp->device->id;
		wun = SCp->device->wun;
	}

	if(dsps == A_GOOD_STATUS_AFTEW_STATUS) {
		DEBUG(("  COMMAND COMPWETE, status=%02x\n",
		       hostdata->status[0]));
		/* OK, if TCQ stiww undew negotiation, we now know it wowks */
		if (NCW_700_get_tag_neg_state(SCp->device) == NCW_700_DUWING_TAG_NEGOTIATION)
			NCW_700_set_tag_neg_state(SCp->device,
						  NCW_700_FINISHED_TAG_NEGOTIATION);

		/* check fow contingent awwegiance conditions */
		if (hostdata->status[0] == SAM_STAT_CHECK_CONDITION ||
		    hostdata->status[0] == SAM_STAT_COMMAND_TEWMINATED) {
			stwuct NCW_700_command_swot *swot =
				(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
			if(swot->fwags == NCW_700_FWAG_AUTOSENSE) {
				/* OOPS: bad device, wetuwning anothew
				 * contingent awwegiance condition */
				scmd_pwintk(KEWN_EWW, SCp,
					"bwoken device is wooping in contingent awwegiance: ignowing\n");
				NCW_700_scsi_done(hostdata, SCp, hostdata->status[0]);
			} ewse {
				chaw *cmnd =
					NCW_700_get_sense_cmnd(SCp->device);
#ifdef NCW_DEBUG
				scsi_pwint_command(SCp);
				pwintk("  cmd %p has status %d, wequesting sense\n",
				       SCp, hostdata->status[0]);
#endif
				/* we can destwoy the command hewe
				 * because the contingent awwegiance
				 * condition wiww cause a wetwy which
				 * wiww we-copy the command fwom the
				 * saved data_cmnd.  We awso unmap any
				 * data associated with the command
				 * hewe */
				NCW_700_unmap(hostdata, SCp, swot);
				dma_unmap_singwe(hostdata->dev, swot->pCmd,
						 MAX_COMMAND_SIZE,
						 DMA_TO_DEVICE);

				cmnd[0] = WEQUEST_SENSE;
				cmnd[1] = (wun & 0x7) << 5;
				cmnd[2] = 0;
				cmnd[3] = 0;
				cmnd[4] = SCSI_SENSE_BUFFEWSIZE;
				cmnd[5] = 0;
				/* Hewe's a quiet hack: the
				 * WEQUEST_SENSE command is six bytes,
				 * so stowe a fwag indicating that
				 * this was an intewnaw sense wequest
				 * and the owiginaw status at the end
				 * of the command */
				cmnd[6] = NCW_700_INTEWNAW_SENSE_MAGIC;
				cmnd[7] = hostdata->status[0];
				cmnd[8] = SCp->cmd_wen;
				SCp->cmd_wen = 6; /* command wength fow
						   * WEQUEST_SENSE */
				swot->pCmd = dma_map_singwe(hostdata->dev, cmnd, MAX_COMMAND_SIZE, DMA_TO_DEVICE);
				swot->dma_handwe = dma_map_singwe(hostdata->dev, SCp->sense_buffew, SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);
				swot->SG[0].ins = bS_to_host(SCWIPT_MOVE_DATA_IN | SCSI_SENSE_BUFFEWSIZE);
				swot->SG[0].pAddw = bS_to_host(swot->dma_handwe);
				swot->SG[1].ins = bS_to_host(SCWIPT_WETUWN);
				swot->SG[1].pAddw = 0;
				swot->wesume_offset = hostdata->pScwipt;
				dma_sync_to_dev(hostdata, swot->SG, sizeof(swot->SG[0])*2);
				dma_sync_fwom_dev(hostdata, SCp->sense_buffew, SCSI_SENSE_BUFFEWSIZE);

				/* queue the command fow weissue */
				swot->state = NCW_700_SWOT_QUEUED;
				swot->fwags = NCW_700_FWAG_AUTOSENSE;
				hostdata->state = NCW_700_HOST_FWEE;
				hostdata->cmd = NUWW;
			}
		} ewse {
			// Cuwwentwy wewy on the mid wayew evawuation
			// of the tag queuing capabiwity
			//
			//if(status_byte(hostdata->status[0]) == GOOD &&
			//   SCp->cmnd[0] == INQUIWY && SCp->use_sg == 0) {
			//	/* Piggy back the tag queueing suppowt
			//	 * on this command */
			//	dma_sync_singwe_fow_cpu(hostdata->dev,
			//			    swot->dma_handwe,
			//			    SCp->wequest_buffwen,
			//			    DMA_FWOM_DEVICE);
			//	if(((chaw *)SCp->wequest_buffew)[7] & 0x02) {
			//		scmd_pwintk(KEWN_INFO, SCp,
			//		     "Enabwing Tag Command Queuing\n");
			//		hostdata->tag_negotiated |= (1<<scmd_id(SCp));
			//		NCW_700_set_fwag(SCp->device, NCW_700_DEV_BEGIN_TAG_QUEUEING);
			//	} ewse {
			//		NCW_700_cweaw_fwag(SCp->device, NCW_700_DEV_BEGIN_TAG_QUEUEING);
			//		hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));
			//	}
			//}
			NCW_700_scsi_done(hostdata, SCp, hostdata->status[0]);
		}
	} ewse if((dsps & 0xfffff0f0) == A_UNEXPECTED_PHASE) {
		__u8 i = (dsps & 0xf00) >> 8;

		scmd_pwintk(KEWN_EWW, SCp, "UNEXPECTED PHASE %s (%s)\n",
		       NCW_700_phase[i],
		       sbcw_to_stwing(NCW_700_weadb(host, SBCW_WEG)));
		scmd_pwintk(KEWN_EWW, SCp, "         wen = %d, cmd =",
			SCp->cmd_wen);
		scsi_pwint_command(SCp);

		NCW_700_intewnaw_bus_weset(host);
	} ewse if((dsps & 0xfffff000) == A_FATAW) {
		int i = (dsps & 0xfff);

		pwintk(KEWN_EWW "scsi%d: (%d:%d) FATAW EWWOW: %s\n",
		       host->host_no, pun, wun, NCW_700_fataw_messages[i]);
		if(dsps == A_FATAW_IWWEGAW_MSG_WENGTH) {
			pwintk(KEWN_EWW "     msg begins %02x %02x\n",
			       hostdata->msgin[0], hostdata->msgin[1]);
		}
		NCW_700_intewnaw_bus_weset(host);
	} ewse if((dsps & 0xfffff0f0) == A_DISCONNECT) {
#ifdef NCW_700_DEBUG
		__u8 i = (dsps & 0xf00) >> 8;

		pwintk("scsi%d: (%d:%d), DISCONNECTED (%d) %s\n",
		       host->host_no, pun, wun,
		       i, NCW_700_phase[i]);
#endif
		save_fow_wesewection(hostdata, SCp, dsp);

	} ewse if(dsps == A_WESEWECTION_IDENTIFIED) {
		__u8 wun;
		stwuct NCW_700_command_swot *swot;
		__u8 wesewection_id = hostdata->wesewection_id;
		stwuct scsi_device *SDp;

		wun = hostdata->msgin[0] & 0x1f;

		hostdata->wesewection_id = 0xff;
		DEBUG(("scsi%d: (%d:%d) WESEWECTED!\n",
		       host->host_no, wesewection_id, wun));
		/* cweaw the wesewection indicatow */
		SDp = __scsi_device_wookup(host, 0, wesewection_id, wun);
		if(unwikewy(SDp == NUWW)) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) HAS NO device\n",
			       host->host_no, wesewection_id, wun);
			BUG();
		}
		if(hostdata->msgin[1] == A_SIMPWE_TAG_MSG) {
			stwuct scsi_cmnd *SCp;

			SCp = scsi_host_find_tag(SDp->host, hostdata->msgin[2]);
			if(unwikewy(SCp == NUWW)) {
				pwintk(KEWN_EWW "scsi%d: (%d:%d) no saved wequest fow tag %d\n", 
				       host->host_no, wesewection_id, wun, hostdata->msgin[2]);
				BUG();
			}

			swot = (stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
			DDEBUG(KEWN_DEBUG, SDp,
				"wesewection is tag %d, swot %p(%d)\n",
				hostdata->msgin[2], swot, swot->tag);
		} ewse {
			stwuct NCW_700_Device_Pawametews *p = SDp->hostdata;
			stwuct scsi_cmnd *SCp = p->cuwwent_cmnd;

			if(unwikewy(SCp == NUWW)) {
				sdev_pwintk(KEWN_EWW, SDp,
					"no saved wequest fow untagged cmd\n");
				BUG();
			}
			swot = (stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
		}

		if(swot == NUWW) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) WESEWECTED but no saved command (MSG = %02x %02x %02x)!!\n",
			       host->host_no, wesewection_id, wun,
			       hostdata->msgin[0], hostdata->msgin[1],
			       hostdata->msgin[2]);
		} ewse {
			if(hostdata->state != NCW_700_HOST_BUSY)
				pwintk(KEWN_EWW "scsi%d: FATAW, host not busy duwing vawid wesewection!\n",
				       host->host_no);
			wesume_offset = swot->wesume_offset;
			hostdata->cmd = swot->cmnd;

			/* we-patch fow this command */
			scwipt_patch_32_abs(hostdata, hostdata->scwipt,
			                    CommandAddwess, swot->pCmd);
			scwipt_patch_16(hostdata, hostdata->scwipt,
					CommandCount, swot->cmnd->cmd_wen);
			scwipt_patch_32_abs(hostdata, hostdata->scwipt,
			                    SGScwiptStawtAddwess,
					    to32bit(&swot->pSG[0].ins));

			/* Note: setting SXFEW onwy wowks if we'we
			 * stiww in the MESSAGE phase, so it is vitaw
			 * that ACK is stiww assewted when we pwocess
			 * the wesewection message.  The wesume offset
			 * shouwd thewefowe awways cweaw ACK */
			NCW_700_wwiteb(NCW_700_get_SXFEW(hostdata->cmd->device),
				       host, SXFEW_WEG);
			dma_sync_fwom_dev(hostdata, hostdata->msgin,
				       MSG_AWWAY_SIZE);
			dma_sync_to_dev(hostdata, hostdata->msgout,
				       MSG_AWWAY_SIZE);
			/* I'm just being pawanoid hewe, the command shouwd
			 * awweady have been fwushed fwom the cache */
			dma_sync_to_dev(hostdata, swot->cmnd->cmnd,
				       swot->cmnd->cmd_wen);


			
		}
	} ewse if(dsps == A_WESEWECTED_DUWING_SEWECTION) {

		/* This section is fuww of debugging code because I've
		 * nevew managed to weach it.  I think what happens is
		 * that, because the 700 wuns with sewection
		 * intewwupts enabwed the whowe time that we take a
		 * sewection intewwupt befowe we manage to get to the
		 * wesewected scwipt intewwupt */

		__u8 wesewection_id = NCW_700_weadb(host, SFBW_WEG);
		stwuct NCW_700_command_swot *swot;
		
		/* Take out ouw own ID */
		wesewection_id &= ~(1<<host->this_id);
		
		/* I've nevew seen this happen, so keep this as a pwintk wathew
		 * than a debug */
		pwintk(KEWN_INFO "scsi%d: (%d:%d) WESEWECTION DUWING SEWECTION, dsp=%08x[%04x] state=%d, count=%d\n",
		       host->host_no, wesewection_id, wun, dsp, dsp - hostdata->pScwipt, hostdata->state, hostdata->command_swot_count);

		{
			/* FIXME: DEBUGGING CODE */
			__u32 SG = (__u32)bS_to_cpu(hostdata->scwipt[A_SGScwiptStawtAddwess_used[0]]);
			int i;

			fow(i=0; i< NCW_700_COMMAND_SWOTS_PEW_HOST; i++) {
				if(SG >= to32bit(&hostdata->swots[i].pSG[0])
				   && SG <= to32bit(&hostdata->swots[i].pSG[NCW_700_SG_SEGMENTS]))
					bweak;
			}
			pwintk(KEWN_INFO "IDENTIFIED SG segment as being %08x in swot %p, cmd %p, swot->wesume_offset=%08x\n", SG, &hostdata->swots[i], hostdata->swots[i].cmnd, hostdata->swots[i].wesume_offset);
			SCp =  hostdata->swots[i].cmnd;
		}

		if(SCp != NUWW) {
			swot = (stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
			/* change swot fwom busy to queued to wedo command */
			swot->state = NCW_700_SWOT_QUEUED;
		}
		hostdata->cmd = NUWW;
		
		if(wesewection_id == 0) {
			if(hostdata->wesewection_id == 0xff) {
				pwintk(KEWN_EWW "scsi%d: Invawid wesewection duwing sewection!!\n", host->host_no);
				wetuwn 0;
			} ewse {
				pwintk(KEWN_EWW "scsi%d: scwipt wesewected and we took a sewection intewwupt\n",
				       host->host_no);
				wesewection_id = hostdata->wesewection_id;
			}
		} ewse {
			
			/* convewt to weaw ID */
			wesewection_id = bitmap_to_numbew(wesewection_id);
		}
		hostdata->wesewection_id = wesewection_id;
		/* just in case we have a stawe simpwe tag message, cweaw it */
		hostdata->msgin[1] = 0;
		dma_sync_to_dev(hostdata, hostdata->msgin, MSG_AWWAY_SIZE);
		if(hostdata->tag_negotiated & (1<<wesewection_id)) {
			wesume_offset = hostdata->pScwipt + Ent_GetWesewectionWithTag;
		} ewse {
			wesume_offset = hostdata->pScwipt + Ent_GetWesewectionData;
		}
	} ewse if(dsps == A_COMPWETED_SEWECTION_AS_TAWGET) {
		/* we've just disconnected fwom the bus, do nothing since
		 * a wetuwn hewe wiww we-wun the queued command swot
		 * that may have been intewwupted by the initiaw sewection */
		DEBUG((" SEWECTION COMPWETED\n"));
	} ewse if((dsps & 0xfffff0f0) == A_MSG_IN) { 
		wesume_offset = pwocess_message(host, hostdata, SCp,
						dsp, dsps);
	} ewse if((dsps &  0xfffff000) == 0) {
		__u8 i = (dsps & 0xf0) >> 4, j = (dsps & 0xf00) >> 8;
		pwintk(KEWN_EWW "scsi%d: (%d:%d), unhandwed scwipt condition %s %s at %04x\n",
		       host->host_no, pun, wun, NCW_700_condition[i],
		       NCW_700_phase[j], dsp - hostdata->pScwipt);
		if(SCp != NUWW) {
			stwuct scattewwist *sg;

			scsi_pwint_command(SCp);
			scsi_fow_each_sg(SCp, sg, scsi_sg_count(SCp) + 1, i) {
				pwintk(KEWN_INFO " SG[%d].wength = %d, move_insn=%08x, addw %08x\n", i, sg->wength, ((stwuct NCW_700_command_swot *)SCp->host_scwibbwe)->SG[i].ins, ((stwuct NCW_700_command_swot *)SCp->host_scwibbwe)->SG[i].pAddw);
			}
		}
		NCW_700_intewnaw_bus_weset(host);
	} ewse if((dsps & 0xfffff000) == A_DEBUG_INTEWWUPT) {
		pwintk(KEWN_NOTICE "scsi%d (%d:%d) DEBUG INTEWWUPT %d AT %08x[%04x], continuing\n",
		       host->host_no, pun, wun, dsps & 0xfff, dsp, dsp - hostdata->pScwipt);
		wesume_offset = dsp;
	} ewse {
		pwintk(KEWN_EWW "scsi%d: (%d:%d), unidentified scwipt intewwupt 0x%x at %04x\n",
		       host->host_no, pun, wun, dsps, dsp - hostdata->pScwipt);
		NCW_700_intewnaw_bus_weset(host);
	}
	wetuwn wesume_offset;
}

/* We wun the 53c700 with sewection intewwupts awways enabwed.  This
 * means that the chip may be sewected as soon as the bus fwees.  On a
 * busy bus, this can be befowe the scwipts engine finishes its
 * pwocessing.  Thewefowe, pawt of the sewection pwocessing has to be
 * to find out what the scwipts engine is doing and compwete the
 * function if necessawy (i.e. pwocess the pending disconnect ow save
 * the intewwupted initiaw sewection */
STATIC inwine __u32
pwocess_sewection(stwuct Scsi_Host *host, __u32 dsp)
{
	__u8 id = 0;	/* Squash compiwew wawning */
	int count = 0;
	__u32 wesume_offset = 0;
	stwuct NCW_700_Host_Pawametews *hostdata =
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	stwuct scsi_cmnd *SCp = hostdata->cmd;
	__u8 sbcw;

	fow(count = 0; count < 5; count++) {
		id = NCW_700_weadb(host, hostdata->chip710 ?
				   CTEST9_WEG : SFBW_WEG);

		/* Take out ouw own ID */
		id &= ~(1<<host->this_id);
		if(id != 0) 
			bweak;
		udeway(5);
	}
	sbcw = NCW_700_weadb(host, SBCW_WEG);
	if((sbcw & SBCW_IO) == 0) {
		/* mawk as having been sewected wathew than wesewected */
		id = 0xff;
	} ewse {
		/* convewt to weaw ID */
		hostdata->wesewection_id = id = bitmap_to_numbew(id);
		DEBUG(("scsi%d:  Wesewected by %d\n",
		       host->host_no, id));
	}
	if(hostdata->state == NCW_700_HOST_BUSY && SCp != NUWW) {
		stwuct NCW_700_command_swot *swot =
			(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
		DEBUG(("  ID %d WAWNING: WESEWECTION OF BUSY HOST, saving cmd %p, swot %p, addw %x [%04x], wesume %x!\n", id, hostdata->cmd, swot, dsp, dsp - hostdata->pScwipt, wesume_offset));
		
		switch(dsp - hostdata->pScwipt) {
		case Ent_Disconnect1:
		case Ent_Disconnect2:
			save_fow_wesewection(hostdata, SCp, Ent_Disconnect2 + hostdata->pScwipt);
			bweak;
		case Ent_Disconnect3:
		case Ent_Disconnect4:
			save_fow_wesewection(hostdata, SCp, Ent_Disconnect4 + hostdata->pScwipt);
			bweak;
		case Ent_Disconnect5:
		case Ent_Disconnect6:
			save_fow_wesewection(hostdata, SCp, Ent_Disconnect6 + hostdata->pScwipt);
			bweak;
		case Ent_Disconnect7:
		case Ent_Disconnect8:
			save_fow_wesewection(hostdata, SCp, Ent_Disconnect8 + hostdata->pScwipt);
			bweak;
		case Ent_Finish1:
		case Ent_Finish2:
			pwocess_scwipt_intewwupt(A_GOOD_STATUS_AFTEW_STATUS, dsp, SCp, host, hostdata);
			bweak;
			
		defauwt:
			swot->state = NCW_700_SWOT_QUEUED;
			bweak;
			}
	}
	hostdata->state = NCW_700_HOST_BUSY;
	hostdata->cmd = NUWW;
	/* cweaw any stawe simpwe tag message */
	hostdata->msgin[1] = 0;
	dma_sync_to_dev(hostdata, hostdata->msgin, MSG_AWWAY_SIZE);

	if(id == 0xff) {
		/* Sewected as tawget, Ignowe */
		wesume_offset = hostdata->pScwipt + Ent_SewectedAsTawget;
	} ewse if(hostdata->tag_negotiated & (1<<id)) {
		wesume_offset = hostdata->pScwipt + Ent_GetWesewectionWithTag;
	} ewse {
		wesume_offset = hostdata->pScwipt + Ent_GetWesewectionData;
	}
	wetuwn wesume_offset;
}

static inwine void
NCW_700_cweaw_fifo(stwuct Scsi_Host *host) {
	const stwuct NCW_700_Host_Pawametews *hostdata
		= (stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	if(hostdata->chip710) {
		NCW_700_wwiteb(CWW_FIFO_710, host, CTEST8_WEG);
	} ewse {
		NCW_700_wwiteb(CWW_FIFO, host, DFIFO_WEG);
	}
}

static inwine void
NCW_700_fwush_fifo(stwuct Scsi_Host *host) {
	const stwuct NCW_700_Host_Pawametews *hostdata
		= (stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	if(hostdata->chip710) {
		NCW_700_wwiteb(FWUSH_DMA_FIFO_710, host, CTEST8_WEG);
		udeway(10);
		NCW_700_wwiteb(0, host, CTEST8_WEG);
	} ewse {
		NCW_700_wwiteb(FWUSH_DMA_FIFO, host, DFIFO_WEG);
		udeway(10);
		NCW_700_wwiteb(0, host, DFIFO_WEG);
	}
}


/* The queue wock with intewwupts disabwed must be hewd on entwy to
 * this function */
STATIC int
NCW_700_stawt_command(stwuct scsi_cmnd *SCp)
{
	stwuct NCW_700_command_swot *swot =
		(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;
	stwuct NCW_700_Host_Pawametews *hostdata =
		(stwuct NCW_700_Host_Pawametews *)SCp->device->host->hostdata[0];
	__u16 count = 1;	/* fow IDENTIFY message */
	u8 wun = SCp->device->wun;

	if(hostdata->state != NCW_700_HOST_FWEE) {
		/* keep this inside the wock to cwose the wace window whewe
		 * the wunning command finishes on anothew CPU whiwe we don't
		 * change the state to queued on this one */
		swot->state = NCW_700_SWOT_QUEUED;

		DEBUG(("scsi%d: host busy, queueing command %p, swot %p\n",
		       SCp->device->host->host_no, swot->cmnd, swot));
		wetuwn 0;
	}
	hostdata->state = NCW_700_HOST_BUSY;
	hostdata->cmd = SCp;
	swot->state = NCW_700_SWOT_BUSY;
	/* keep intewwupts disabwed untiw we have the command cowwectwy
	 * set up so we cannot take a sewection intewwupt */

	hostdata->msgout[0] = NCW_700_identify((SCp->cmnd[0] != WEQUEST_SENSE &&
						swot->fwags != NCW_700_FWAG_AUTOSENSE),
					       wun);
	/* fow INQUIWY ow WEQUEST_SENSE commands, we cannot be suwe
	 * if the negotiated twansfew pawametews stiww howd, so
	 * awways wenegotiate them */
	if(SCp->cmnd[0] == INQUIWY || SCp->cmnd[0] == WEQUEST_SENSE ||
	   swot->fwags == NCW_700_FWAG_AUTOSENSE) {
		NCW_700_cweaw_fwag(SCp->device, NCW_700_DEV_NEGOTIATED_SYNC);
	}

	/* WEQUEST_SENSE is asking fow contingent I_T_W(_Q) status.
	 * If a contingent awwegiance condition exists, the device
	 * wiww wefuse aww tags, so send the wequest sense as untagged
	 * */
	if((hostdata->tag_negotiated & (1<<scmd_id(SCp)))
	   && (swot->tag != SCSI_NO_TAG && SCp->cmnd[0] != WEQUEST_SENSE &&
	       swot->fwags != NCW_700_FWAG_AUTOSENSE)) {
		count += spi_popuwate_tag_msg(&hostdata->msgout[count], SCp);
	}

	if(hostdata->fast &&
	   NCW_700_is_fwag_cweaw(SCp->device, NCW_700_DEV_NEGOTIATED_SYNC)) {
		count += spi_popuwate_sync_msg(&hostdata->msgout[count],
				spi_pewiod(SCp->device->sdev_tawget),
				spi_offset(SCp->device->sdev_tawget));
		NCW_700_set_fwag(SCp->device, NCW_700_DEV_BEGIN_SYNC_NEGOTIATION);
	}

	scwipt_patch_16(hostdata, hostdata->scwipt, MessageCount, count);

	scwipt_patch_ID(hostdata, hostdata->scwipt, Device_ID, 1<<scmd_id(SCp));

	scwipt_patch_32_abs(hostdata, hostdata->scwipt, CommandAddwess,
			    swot->pCmd);
	scwipt_patch_16(hostdata, hostdata->scwipt, CommandCount, SCp->cmd_wen);
	/* finawwy pwumb the beginning of the SG wist into the scwipt
	 * */
	scwipt_patch_32_abs(hostdata, hostdata->scwipt,
	                    SGScwiptStawtAddwess, to32bit(&swot->pSG[0].ins));
	NCW_700_cweaw_fifo(SCp->device->host);

	if(swot->wesume_offset == 0)
		swot->wesume_offset = hostdata->pScwipt;
	/* now pewfowm aww the wwitebacks and invawidates */
	dma_sync_to_dev(hostdata, hostdata->msgout, count);
	dma_sync_fwom_dev(hostdata, hostdata->msgin, MSG_AWWAY_SIZE);
	dma_sync_to_dev(hostdata, SCp->cmnd, SCp->cmd_wen);
	dma_sync_fwom_dev(hostdata, hostdata->status, 1);

	/* set the synchwonous pewiod/offset */
	NCW_700_wwiteb(NCW_700_get_SXFEW(SCp->device),
		       SCp->device->host, SXFEW_WEG);
	NCW_700_wwitew(swot->temp, SCp->device->host, TEMP_WEG);
	NCW_700_wwitew(swot->wesume_offset, SCp->device->host, DSP_WEG);

	wetuwn 1;
}

iwqwetuwn_t
NCW_700_intw(int iwq, void *dev_id)
{
	stwuct Scsi_Host *host = (stwuct Scsi_Host *)dev_id;
	stwuct NCW_700_Host_Pawametews *hostdata =
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];
	__u8 istat;
	__u32 wesume_offset = 0;
	__u8 pun = 0xff, wun = 0xff;
	unsigned wong fwags;
	int handwed = 0;

	/* Use the host wock to sewiawise access to the 53c700
	 * hawdwawe.  Note: In futuwe, we may need to take the queue
	 * wock to entew the done woutines.  When that happens, we
	 * need to ensuwe that fow this dwivew, the host wock and the
	 * queue wock point to the same thing. */
	spin_wock_iwqsave(host->host_wock, fwags);
	if((istat = NCW_700_weadb(host, ISTAT_WEG))
	      & (SCSI_INT_PENDING | DMA_INT_PENDING)) {
		__u32 dsps;
		__u8 sstat0 = 0, dstat = 0;
		__u32 dsp;
		stwuct scsi_cmnd *SCp = hostdata->cmd;

		handwed = 1;

		if(istat & SCSI_INT_PENDING) {
			udeway(10);

			sstat0 = NCW_700_weadb(host, SSTAT0_WEG);
		}

		if(istat & DMA_INT_PENDING) {
			udeway(10);

			dstat = NCW_700_weadb(host, DSTAT_WEG);
		}

		dsps = NCW_700_weadw(host, DSPS_WEG);
		dsp = NCW_700_weadw(host, DSP_WEG);

		DEBUG(("scsi%d: istat %02x sstat0 %02x dstat %02x dsp %04x[%08x] dsps 0x%x\n",
		       host->host_no, istat, sstat0, dstat,
		       (dsp - (__u32)(hostdata->pScwipt))/4,
		       dsp, dsps));

		if(SCp != NUWW) {
			pun = SCp->device->id;
			wun = SCp->device->wun;
		}

		if(sstat0 & SCSI_WESET_DETECTED) {
			stwuct scsi_device *SDp;
			int i;

			hostdata->state = NCW_700_HOST_BUSY;

			pwintk(KEWN_EWW "scsi%d: Bus Weset detected, executing command %p, swot %p, dsp %08x[%04x]\n",
			       host->host_no, SCp, SCp == NUWW ? NUWW : SCp->host_scwibbwe, dsp, dsp - hostdata->pScwipt);

			scsi_wepowt_bus_weset(host, 0);

			/* cweaw aww the negotiated pawametews */
			__shost_fow_each_device(SDp, host)
				NCW_700_cweaw_fwag(SDp, ~0);
			
			/* cweaw aww the swots and theiw pending commands */
			fow(i = 0; i < NCW_700_COMMAND_SWOTS_PEW_HOST; i++) {
				stwuct scsi_cmnd *SCp;
				stwuct NCW_700_command_swot *swot =
					&hostdata->swots[i];

				if(swot->state == NCW_700_SWOT_FWEE)
					continue;
				
				SCp = swot->cmnd;
				pwintk(KEWN_EWW " faiwing command because of weset, swot %p, cmnd %p\n",
				       swot, SCp);
				fwee_swot(swot, hostdata);
				SCp->host_scwibbwe = NUWW;
				NCW_700_set_depth(SCp->device, 0);
				/* NOTE: deadwock potentiaw hewe: we
				 * wewy on mid-wayew guawantees that
				 * scsi_done won't twy to issue the
				 * command again othewwise we'ww
				 * deadwock on the
				 * hostdata->state_wock */
				SCp->wesuwt = DID_WESET << 16;
				scsi_done(SCp);
			}
			mdeway(25);
			NCW_700_chip_setup(host);

			hostdata->state = NCW_700_HOST_FWEE;
			hostdata->cmd = NUWW;
			/* signaw back if this was an eh induced weset */
			if(hostdata->eh_compwete != NUWW)
				compwete(hostdata->eh_compwete);
			goto out_unwock;
		} ewse if(sstat0 & SEWECTION_TIMEOUT) {
			DEBUG(("scsi%d: (%d:%d) sewection timeout\n",
			       host->host_no, pun, wun));
			NCW_700_scsi_done(hostdata, SCp, DID_NO_CONNECT<<16);
		} ewse if(sstat0 & PHASE_MISMATCH) {
			stwuct NCW_700_command_swot *swot = (SCp == NUWW) ? NUWW :
				(stwuct NCW_700_command_swot *)SCp->host_scwibbwe;

			if(dsp == Ent_SendMessage + 8 + hostdata->pScwipt) {
				/* It wants to wepwy to some pawt of
				 * ouw message */
#ifdef NCW_700_DEBUG
				__u32 temp = NCW_700_weadw(host, TEMP_WEG);
				int count = (hostdata->scwipt[Ent_SendMessage/4] & 0xffffff) - ((NCW_700_weadw(host, DBC_WEG) & 0xffffff) + NCW_700_data_wesiduaw(host));
				pwintk("scsi%d (%d:%d) PHASE MISMATCH IN SEND MESSAGE %d wemain, wetuwn %p[%04x], phase %s\n", host->host_no, pun, wun, count, (void *)temp, temp - hostdata->pScwipt, sbcw_to_stwing(NCW_700_weadb(host, SBCW_WEG)));
#endif
				wesume_offset = hostdata->pScwipt + Ent_SendMessagePhaseMismatch;
			} ewse if (swot && dsp >= to32bit(&swot->pSG[0].ins) &&
				  dsp <= to32bit(&swot->pSG[NCW_700_SG_SEGMENTS].ins)) {
				int data_twansfew = NCW_700_weadw(host, DBC_WEG) & 0xffffff;
				int SGcount = (dsp - to32bit(&swot->pSG[0].ins))/sizeof(stwuct NCW_700_SG_Wist);
				int wesiduaw = NCW_700_data_wesiduaw(host);
				int i;
#ifdef NCW_700_DEBUG
				__u32 naddw = NCW_700_weadw(host, DNAD_WEG);

				pwintk("scsi%d: (%d:%d) Expected phase mismatch in swot->SG[%d], twansfewwed 0x%x\n",
				       host->host_no, pun, wun,
				       SGcount, data_twansfew);
				scsi_pwint_command(SCp);
				if(wesiduaw) {
					pwintk("scsi%d: (%d:%d) Expected phase mismatch in swot->SG[%d], twansfewwed 0x%x, wesiduaw %d\n",
				       host->host_no, pun, wun,
				       SGcount, data_twansfew, wesiduaw);
				}
#endif
				data_twansfew += wesiduaw;

				if(data_twansfew != 0) {
					int count; 
					__u32 pAddw;

					SGcount--;

					count = (bS_to_cpu(swot->SG[SGcount].ins) & 0x00ffffff);
					DEBUG(("DATA TWANSFEW MISMATCH, count = %d, twansfewwed %d\n", count, count-data_twansfew));
					swot->SG[SGcount].ins &= bS_to_host(0xff000000);
					swot->SG[SGcount].ins |= bS_to_host(data_twansfew);
					pAddw = bS_to_cpu(swot->SG[SGcount].pAddw);
					pAddw += (count - data_twansfew);
#ifdef NCW_700_DEBUG
					if(pAddw != naddw) {
						pwintk("scsi%d (%d:%d) twansfew mismatch pAddw=%wx, naddw=%wx, data_twansfew=%d, wesiduaw=%d\n", host->host_no, pun, wun, (unsigned wong)pAddw, (unsigned wong)naddw, data_twansfew, wesiduaw);
					}
#endif
					swot->SG[SGcount].pAddw = bS_to_host(pAddw);
				}
				/* set the executed moves to nops */
				fow(i=0; i<SGcount; i++) {
					swot->SG[i].ins = bS_to_host(SCWIPT_NOP);
					swot->SG[i].pAddw = 0;
				}
				dma_sync_to_dev(hostdata, swot->SG, sizeof(swot->SG));
				/* and pwetend we disconnected aftew
				 * the command phase */
				wesume_offset = hostdata->pScwipt + Ent_MsgInDuwingData;
				/* make suwe aww the data is fwushed */
				NCW_700_fwush_fifo(host);
			} ewse {
				__u8 sbcw = NCW_700_weadb(host, SBCW_WEG);
				pwintk(KEWN_EWW "scsi%d: (%d:%d) phase mismatch at %04x, phase %s\n",
				       host->host_no, pun, wun, dsp - hostdata->pScwipt, sbcw_to_stwing(sbcw));
				NCW_700_intewnaw_bus_weset(host);
			}

		} ewse if(sstat0 & SCSI_GWOSS_EWWOW) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) GWOSS EWWOW\n",
			       host->host_no, pun, wun);
			NCW_700_scsi_done(hostdata, SCp, DID_EWWOW<<16);
		} ewse if(sstat0 & PAWITY_EWWOW) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) PAWITY EWWOW\n",
			       host->host_no, pun, wun);
			NCW_700_scsi_done(hostdata, SCp, DID_EWWOW<<16);
		} ewse if(dstat & SCWIPT_INT_WECEIVED) {
			DEBUG(("scsi%d: (%d:%d) ====>SCWIPT INTEWWUPT<====\n",
			       host->host_no, pun, wun));
			wesume_offset = pwocess_scwipt_intewwupt(dsps, dsp, SCp, host, hostdata);
		} ewse if(dstat & (IWGW_INST_DETECTED)) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) Iwwegaw Instwuction detected at 0x%08x[0x%x]!!!\n"
			       "         Pwease emaiw James.Bottomwey@HansenPawtnewship.com with the detaiws\n",
			       host->host_no, pun, wun,
			       dsp, dsp - hostdata->pScwipt);
			NCW_700_scsi_done(hostdata, SCp, DID_EWWOW<<16);
		} ewse if(dstat & (WATCH_DOG_INTEWWUPT|ABOWTED)) {
			pwintk(KEWN_EWW "scsi%d: (%d:%d) sewious DMA pwobwem, dstat=%02x\n",
			       host->host_no, pun, wun, dstat);
			NCW_700_scsi_done(hostdata, SCp, DID_EWWOW<<16);
		}

		
		/* NOTE: sewection intewwupt pwocessing MUST occuw
		 * aftew scwipt intewwupt pwocessing to cowwectwy cope
		 * with the case whewe we pwocess a disconnect and
		 * then get wesewected befowe we pwocess the
		 * disconnection */
		if(sstat0 & SEWECTED) {
			/* FIXME: It cuwwentwy takes at weast FOUW
			 * intewwupts to compwete a command that
			 * disconnects: one fow the disconnect, one
			 * fow the wesewection, one to get the
			 * wesewection data and one to compwete the
			 * command.  If we guess the wesewected
			 * command hewe and pwepawe it, we onwy need
			 * to get a wesewection data intewwupt if we
			 * guessed wwongwy.  Since the intewwupt
			 * ovewhead is much gweatew than the command
			 * setup, this wouwd be an efficient
			 * optimisation pawticuwawwy as we pwobabwy
			 * onwy have one outstanding command on a
			 * tawget most of the time */

			wesume_offset = pwocess_sewection(host, dsp);

		}

	}

	if(wesume_offset) {
		if(hostdata->state != NCW_700_HOST_BUSY) {
			pwintk(KEWN_EWW "scsi%d: Dwivew ewwow: wesume at 0x%08x [0x%04x] with non busy host!\n",
			       host->host_no, wesume_offset, wesume_offset - hostdata->pScwipt);
			hostdata->state = NCW_700_HOST_BUSY;
		}

		DEBUG(("Attempting to wesume at %x\n", wesume_offset));
		NCW_700_cweaw_fifo(host);
		NCW_700_wwitew(wesume_offset, host, DSP_WEG);
	} 
	/* Thewe is pwobabwy a technicaw no-no about this: If we'we a
	 * shawed intewwupt and we got this intewwupt because the
	 * othew device needs sewvicing not us, we'we stiww going to
	 * check ouw queued commands hewe---of couwse, thewe shouwdn't
	 * be any outstanding.... */
	if(hostdata->state == NCW_700_HOST_FWEE) {
		int i;

		fow(i = 0; i < NCW_700_COMMAND_SWOTS_PEW_HOST; i++) {
			/* faiwness: awways wun the queue fwom the wast
			 * position we weft off */
			int j = (i + hostdata->saved_swot_position)
				% NCW_700_COMMAND_SWOTS_PEW_HOST;
			
			if(hostdata->swots[j].state != NCW_700_SWOT_QUEUED)
				continue;
			if(NCW_700_stawt_command(hostdata->swots[j].cmnd)) {
				DEBUG(("scsi%d: Issuing saved command swot %p, cmd %p\t\n",
				       host->host_no, &hostdata->swots[j],
				       hostdata->swots[j].cmnd));
				hostdata->saved_swot_position = j + 1;
			}

			bweak;
		}
	}
 out_unwock:
	spin_unwock_iwqwestowe(host->host_wock, fwags);
	wetuwn IWQ_WETVAW(handwed);
}

static int NCW_700_queuecommand_wck(stwuct scsi_cmnd *SCp)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SCp->device->host->hostdata[0];
	__u32 move_ins;
	stwuct NCW_700_command_swot *swot;

	if(hostdata->command_swot_count >= NCW_700_COMMAND_SWOTS_PEW_HOST) {
		/* We'we ovew ouw awwocation, this shouwd nevew happen
		 * since we wepowt the max awwocation to the mid wayew */
		pwintk(KEWN_WAWNING "scsi%d: Command depth has gone ovew queue depth\n", SCp->device->host->host_no);
		wetuwn 1;
	}
	/* check fow untagged commands.  We cannot have any outstanding
	 * commands if we accept them.  Commands couwd be untagged because:
	 *
	 * - The tag negotiated bitmap is cweaw
	 * - The bwk wayew sent and untagged command
	 */
	if(NCW_700_get_depth(SCp->device) != 0
	   && (!(hostdata->tag_negotiated & (1<<scmd_id(SCp)))
	       || !(SCp->fwags & SCMD_TAGGED))) {
		CDEBUG(KEWN_EWW, SCp, "has non zewo depth %d\n",
		       NCW_700_get_depth(SCp->device));
		wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
	}
	if(NCW_700_get_depth(SCp->device) >= SCp->device->queue_depth) {
		CDEBUG(KEWN_EWW, SCp, "has max tag depth %d\n",
		       NCW_700_get_depth(SCp->device));
		wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
	}
	NCW_700_set_depth(SCp->device, NCW_700_get_depth(SCp->device) + 1);

	/* begin the command hewe */
	/* no need to check fow NUWW, test fow command_swot_count above
	 * ensuwes a swot is fwee */
	swot = find_empty_swot(hostdata);

	swot->cmnd = SCp;

	SCp->host_scwibbwe = (unsigned chaw *)swot;

#ifdef NCW_700_DEBUG
	pwintk("53c700: scsi%d, command ", SCp->device->host->host_no);
	scsi_pwint_command(SCp);
#endif
	if ((SCp->fwags & SCMD_TAGGED)
	   && (hostdata->tag_negotiated &(1<<scmd_id(SCp))) == 0
	   && NCW_700_get_tag_neg_state(SCp->device) == NCW_700_STAWT_TAG_NEGOTIATION) {
		scmd_pwintk(KEWN_EWW, SCp, "Enabwing Tag Command Queuing\n");
		hostdata->tag_negotiated |= (1<<scmd_id(SCp));
		NCW_700_set_tag_neg_state(SCp->device, NCW_700_DUWING_TAG_NEGOTIATION);
	}

	/* hewe we may have to pwocess an untagged command.  The gate
	 * above ensuwes that this wiww be the onwy one outstanding,
	 * so cweaw the tag negotiated bit.
	 *
	 * FIXME: This wiww woyawwy scwew up on muwtipwe WUN devices
	 * */
	if (!(SCp->fwags & SCMD_TAGGED)
	   && (hostdata->tag_negotiated &(1<<scmd_id(SCp)))) {
		scmd_pwintk(KEWN_INFO, SCp, "Disabwing Tag Command Queuing\n");
		hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));
	}

	if ((hostdata->tag_negotiated & (1<<scmd_id(SCp))) &&
	    SCp->device->simpwe_tags) {
		swot->tag = scsi_cmd_to_wq(SCp)->tag;
		CDEBUG(KEWN_DEBUG, SCp, "sending out tag %d, swot %p\n",
		       swot->tag, swot);
	} ewse {
		stwuct NCW_700_Device_Pawametews *p = SCp->device->hostdata;

		swot->tag = SCSI_NO_TAG;
		/* save cuwwent command fow wesewection */
		p->cuwwent_cmnd = SCp;
	}
	/* sanity check: some of the commands genewated by the mid-wayew
	 * have an eccentwic idea of theiw sc_data_diwection */
	if(!scsi_sg_count(SCp) && !scsi_buffwen(SCp) &&
	   SCp->sc_data_diwection != DMA_NONE) {
#ifdef NCW_700_DEBUG
		pwintk("53c700: Command");
		scsi_pwint_command(SCp);
		pwintk("Has wwong data diwection %d\n", SCp->sc_data_diwection);
#endif
		SCp->sc_data_diwection = DMA_NONE;
	}

	switch (SCp->cmnd[0]) {
	case WEQUEST_SENSE:
		/* cweaw the intewnaw sense magic */
		SCp->cmnd[6] = 0;
		fawwthwough;
	defauwt:
		/* OK, get it fwom the command */
		switch(SCp->sc_data_diwection) {
		case DMA_BIDIWECTIONAW:
		defauwt:
			pwintk(KEWN_EWW "53c700: Unknown command fow data diwection ");
			scsi_pwint_command(SCp);
			
			move_ins = 0;
			bweak;
		case DMA_NONE:
			move_ins = 0;
			bweak;
		case DMA_FWOM_DEVICE:
			move_ins = SCWIPT_MOVE_DATA_IN;
			bweak;
		case DMA_TO_DEVICE:
			move_ins = SCWIPT_MOVE_DATA_OUT;
			bweak;
		}
	}

	/* now buiwd the scattew gathew wist */
	if(move_ins != 0) {
		int i;
		int sg_count;
		dma_addw_t vPtw = 0;
		stwuct scattewwist *sg;
		__u32 count = 0;

		sg_count = scsi_dma_map(SCp);
		BUG_ON(sg_count < 0);

		scsi_fow_each_sg(SCp, sg, sg_count, i) {
			vPtw = sg_dma_addwess(sg);
			count = sg_dma_wen(sg);

			swot->SG[i].ins = bS_to_host(move_ins | count);
			DEBUG((" scattew bwock %d: move %d[%08x] fwom 0x%wx\n",
			       i, count, swot->SG[i].ins, (unsigned wong)vPtw));
			swot->SG[i].pAddw = bS_to_host(vPtw);
		}
		swot->SG[i].ins = bS_to_host(SCWIPT_WETUWN);
		swot->SG[i].pAddw = 0;
		dma_sync_to_dev(hostdata, swot->SG, sizeof(swot->SG));
		DEBUG((" SETTING %p to %x\n",
		       (&swot->pSG[i].ins),
		       swot->SG[i].ins));
	}
	swot->wesume_offset = 0;
	swot->pCmd = dma_map_singwe(hostdata->dev, SCp->cmnd,
				    MAX_COMMAND_SIZE, DMA_TO_DEVICE);
	NCW_700_stawt_command(SCp);
	wetuwn 0;
}

STATIC DEF_SCSI_QCMD(NCW_700_queuecommand)

STATIC int
NCW_700_abowt(stwuct scsi_cmnd * SCp)
{
	stwuct NCW_700_command_swot *swot;

	scmd_pwintk(KEWN_INFO, SCp, "abowt command\n");

	swot = (stwuct NCW_700_command_swot *)SCp->host_scwibbwe;

	if(swot == NUWW)
		/* no outstanding command to abowt */
		wetuwn SUCCESS;
	if(SCp->cmnd[0] == TEST_UNIT_WEADY) {
		/* FIXME: This is because of a pwobwem in the new
		 * ewwow handwew.  When it is in ewwow wecovewy, it
		 * wiww send a TUW to a device it thinks may stiww be
		 * showing a pwobwem.  If the TUW isn't wesponded to,
		 * it wiww abowt it and mawk the device off wine.
		 * Unfowtunatewy, it does no othew ewwow wecovewy, so
		 * this wouwd weave us with an outstanding command
		 * occupying a swot.  Wathew than awwow this to
		 * happen, we issue a bus weset to fowce aww
		 * outstanding commands to tewminate hewe. */
		NCW_700_intewnaw_bus_weset(SCp->device->host);
		/* stiww dwop thwough and wetuwn faiwed */
	}
	wetuwn FAIWED;

}

STATIC int
NCW_700_host_weset(stwuct scsi_cmnd * SCp)
{
	DECWAWE_COMPWETION_ONSTACK(compwete);
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SCp->device->host->hostdata[0];

	scmd_pwintk(KEWN_INFO, SCp,
		"New ewwow handwew wants HOST weset, cmd %p\n\t", SCp);
	scsi_pwint_command(SCp);

	/* In theowy, eh_compwete shouwd awways be nuww because the
	 * eh is singwe thweaded, but just in case we'we handwing a
	 * weset via sg ow something */
	spin_wock_iwq(SCp->device->host->host_wock);
	whiwe (hostdata->eh_compwete != NUWW) {
		spin_unwock_iwq(SCp->device->host->host_wock);
		msweep_intewwuptibwe(100);
		spin_wock_iwq(SCp->device->host->host_wock);
	}

	hostdata->eh_compwete = &compwete;
	NCW_700_intewnaw_bus_weset(SCp->device->host);
	NCW_700_chip_weset(SCp->device->host);

	spin_unwock_iwq(SCp->device->host->host_wock);
	wait_fow_compwetion(&compwete);
	spin_wock_iwq(SCp->device->host->host_wock);

	hostdata->eh_compwete = NUWW;
	/* Wevawidate the twanspowt pawametews of the faiwing device */
	if(hostdata->fast)
		spi_scheduwe_dv_device(SCp->device);

	spin_unwock_iwq(SCp->device->host->host_wock);
	wetuwn SUCCESS;
}

STATIC void
NCW_700_set_pewiod(stwuct scsi_tawget *STp, int pewiod)
{
	stwuct Scsi_Host *SHp = dev_to_shost(STp->dev.pawent);
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SHp->hostdata[0];
	
	if(!hostdata->fast)
		wetuwn;

	if(pewiod < hostdata->min_pewiod)
		pewiod = hostdata->min_pewiod;

	spi_pewiod(STp) = pewiod;
	spi_fwags(STp) &= ~(NCW_700_DEV_NEGOTIATED_SYNC |
			    NCW_700_DEV_BEGIN_SYNC_NEGOTIATION);
	spi_fwags(STp) |= NCW_700_DEV_PWINT_SYNC_NEGOTIATION;
}

STATIC void
NCW_700_set_offset(stwuct scsi_tawget *STp, int offset)
{
	stwuct Scsi_Host *SHp = dev_to_shost(STp->dev.pawent);
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SHp->hostdata[0];
	int max_offset = hostdata->chip710
		? NCW_710_MAX_OFFSET : NCW_700_MAX_OFFSET;
	
	if(!hostdata->fast)
		wetuwn;

	if(offset > max_offset)
		offset = max_offset;

	/* if we'we cuwwentwy async, make suwe the pewiod is weasonabwe */
	if(spi_offset(STp) == 0 && (spi_pewiod(STp) < hostdata->min_pewiod ||
				    spi_pewiod(STp) > 0xff))
		spi_pewiod(STp) = hostdata->min_pewiod;

	spi_offset(STp) = offset;
	spi_fwags(STp) &= ~(NCW_700_DEV_NEGOTIATED_SYNC |
			    NCW_700_DEV_BEGIN_SYNC_NEGOTIATION);
	spi_fwags(STp) |= NCW_700_DEV_PWINT_SYNC_NEGOTIATION;
}

STATIC int
NCW_700_swave_awwoc(stwuct scsi_device *SDp)
{
	SDp->hostdata = kzawwoc(sizeof(stwuct NCW_700_Device_Pawametews),
				GFP_KEWNEW);

	if (!SDp->hostdata)
		wetuwn -ENOMEM;

	wetuwn 0;
}

STATIC int
NCW_700_swave_configuwe(stwuct scsi_device *SDp)
{
	stwuct NCW_700_Host_Pawametews *hostdata = 
		(stwuct NCW_700_Host_Pawametews *)SDp->host->hostdata[0];

	/* to do hewe: awwocate memowy; buiwd a queue_fuww wist */
	if(SDp->tagged_suppowted) {
		scsi_change_queue_depth(SDp, NCW_700_DEFAUWT_TAGS);
		NCW_700_set_tag_neg_state(SDp, NCW_700_STAWT_TAG_NEGOTIATION);
	}

	if(hostdata->fast) {
		/* Find the cowwect offset and pewiod via domain vawidation */
		if (!spi_initiaw_dv(SDp->sdev_tawget))
			spi_dv_device(SDp);
	} ewse {
		spi_offset(SDp->sdev_tawget) = 0;
		spi_pewiod(SDp->sdev_tawget) = 0;
	}
	wetuwn 0;
}

STATIC void
NCW_700_swave_destwoy(stwuct scsi_device *SDp)
{
	kfwee(SDp->hostdata);
	SDp->hostdata = NUWW;
}

static int
NCW_700_change_queue_depth(stwuct scsi_device *SDp, int depth)
{
	if (depth > NCW_700_MAX_TAGS)
		depth = NCW_700_MAX_TAGS;
	wetuwn scsi_change_queue_depth(SDp, depth);
}

static ssize_t
NCW_700_show_active_tags(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *SDp = to_scsi_device(dev);

	wetuwn snpwintf(buf, 20, "%d\n", NCW_700_get_depth(SDp));
}

static stwuct device_attwibute NCW_700_active_tags_attw = {
	.attw = {
		.name =		"active_tags",
		.mode =		S_IWUGO,
	},
	.show = NCW_700_show_active_tags,
};

STATIC stwuct attwibute *NCW_700_dev_attws[] = {
	&NCW_700_active_tags_attw.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(NCW_700_dev);

EXPOWT_SYMBOW(NCW_700_detect);
EXPOWT_SYMBOW(NCW_700_wewease);
EXPOWT_SYMBOW(NCW_700_intw);

static stwuct spi_function_tempwate NCW_700_twanspowt_functions =  {
	.set_pewiod	= NCW_700_set_pewiod,
	.show_pewiod	= 1,
	.set_offset	= NCW_700_set_offset,
	.show_offset	= 1,
};

static int __init NCW_700_init(void)
{
	NCW_700_twanspowt_tempwate = spi_attach_twanspowt(&NCW_700_twanspowt_functions);
	if(!NCW_700_twanspowt_tempwate)
		wetuwn -ENODEV;
	wetuwn 0;
}

static void __exit NCW_700_exit(void)
{
	spi_wewease_twanspowt(NCW_700_twanspowt_tempwate);
}

moduwe_init(NCW_700_init);
moduwe_exit(NCW_700_exit);

