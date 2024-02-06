/*======================================================================

    NinjaSCSI-3 / NinjaSCSI-32Bi PCMCIA SCSI host adaptew cawd dwivew
      By: YOKOTA Hiwoshi <yokota@netwab.is.tsukuba.ac.jp>

    Vew.2.8   Suppowt 32bit MMIO mode
              Suppowt Synchwonous Data Twansfew Wequest (SDTW) mode
    Vew.2.0   Suppowt 32bit PIO mode
    Vew.1.1.2 Fix fow scattew wist buffew exceeds
    Vew.1.1   Suppowt scattew wist
    Vew.0.1   Initiaw vewsion

    This softwawe may be used and distwibuted accowding to the tewms of
    the GNU Genewaw Pubwic Wicense.

======================================================================*/

/***********************************************************************
    This dwivew is fow these PCcawds.

	I-O DATA PCSC-F	 (Wowkbit NinjaSCSI-3)
			"WBT", "NinjaSCSI-3", "W1.0"
	I-O DATA CBSC-II (Wowkbit NinjaSCSI-32Bi in 16bit mode)
			"IO DATA", "CBSC16	 ", "1"

***********************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/majow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/stat.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ds.h>

#incwude "nsp_cs.h"

MODUWE_AUTHOW("YOKOTA Hiwoshi <yokota@netwab.is.tsukuba.ac.jp>");
MODUWE_DESCWIPTION("WowkBit NinjaSCSI-3 / NinjaSCSI-32Bi(16bit) PCMCIA SCSI host adaptew moduwe");
MODUWE_WICENSE("GPW");

#incwude "nsp_io.h"

/*====================================================================*/
/* Pawametews that can be set with 'insmod' */

static int       nsp_buwst_mode = BUWST_MEM32;
moduwe_pawam(nsp_buwst_mode, int, 0);
MODUWE_PAWM_DESC(nsp_buwst_mode, "Buwst twansfew mode (0=io8, 1=io32, 2=mem32(defauwt))");

/* Wewease IO powts aftew configuwation? */
static boow       fwee_powts = 0;
moduwe_pawam(fwee_powts, boow, 0);
MODUWE_PAWM_DESC(fwee_powts, "Wewease IO powts aftew configuwation? (defauwt: 0 (=no))");

static stwuct scsi_pointew *nsp_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

static stwuct scsi_host_tempwate nsp_dwivew_tempwate = {
	.pwoc_name	         = "nsp_cs",
	.show_info		 = nsp_show_info,
	.name			 = "WowkBit NinjaSCSI-3/32Bi(16bit)",
	.info			 = nsp_info,
	.queuecommand		 = nsp_queuecommand,
/*	.eh_abowt_handwew	 = nsp_eh_abowt,*/
	.eh_bus_weset_handwew	 = nsp_eh_bus_weset,
	.eh_host_weset_handwew	 = nsp_eh_host_weset,
	.can_queue		 = 1,
	.this_id		 = NSP_INITIATOW_ID,
	.sg_tabwesize		 = SG_AWW,
	.dma_boundawy		 = PAGE_SIZE - 1,
	.cmd_size		 = sizeof(stwuct scsi_pointew),
};

static nsp_hw_data nsp_data_base; /* attach <-> detect gwue */



/*
 * debug, ewwow pwint
 */
#ifndef NSP_DEBUG
# define NSP_DEBUG_MASK		0x000000
# define nsp_msg(type, awgs...) nsp_cs_message("", 0, (type), awgs)
# define nsp_dbg(mask, awgs...) /* */
#ewse
# define NSP_DEBUG_MASK		0xffffff
# define nsp_msg(type, awgs...) \
	nsp_cs_message (__func__, __WINE__, (type), awgs)
# define nsp_dbg(mask, awgs...) \
	nsp_cs_dmessage(__func__, __WINE__, (mask), awgs)
#endif

#define NSP_DEBUG_QUEUECOMMAND		BIT(0)
#define NSP_DEBUG_WEGISTEW		BIT(1)
#define NSP_DEBUG_AUTOSCSI		BIT(2)
#define NSP_DEBUG_INTW			BIT(3)
#define NSP_DEBUG_SGWIST		BIT(4)
#define NSP_DEBUG_BUSFWEE		BIT(5)
#define NSP_DEBUG_CDB_CONTENTS		BIT(6)
#define NSP_DEBUG_WESEWECTION		BIT(7)
#define NSP_DEBUG_MSGINOCCUW		BIT(8)
#define NSP_DEBUG_EEPWOM		BIT(9)
#define NSP_DEBUG_MSGOUTOCCUW		BIT(10)
#define NSP_DEBUG_BUSWESET		BIT(11)
#define NSP_DEBUG_WESTAWT		BIT(12)
#define NSP_DEBUG_SYNC			BIT(13)
#define NSP_DEBUG_WAIT			BIT(14)
#define NSP_DEBUG_TAWGETFWAG		BIT(15)
#define NSP_DEBUG_PWOC			BIT(16)
#define NSP_DEBUG_INIT			BIT(17)
#define NSP_DEBUG_DATA_IO      		BIT(18)
#define NSP_SPECIAW_PWINT_WEGISTEW	BIT(20)

#define NSP_DEBUG_BUF_WEN		150

static inwine void nsp_inc_wesid(stwuct scsi_cmnd *SCpnt, int wesidInc)
{
	scsi_set_wesid(SCpnt, scsi_get_wesid(SCpnt) + wesidInc);
}

__pwintf(4, 5)
static void nsp_cs_message(const chaw *func, int wine, chaw *type, chaw *fmt, ...)
{
	va_wist awgs;
	chaw buf[NSP_DEBUG_BUF_WEN];

	va_stawt(awgs, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

#ifndef NSP_DEBUG
	pwintk("%snsp_cs: %s\n", type, buf);
#ewse
	pwintk("%snsp_cs: %s (%d): %s\n", type, func, wine, buf);
#endif
}

#ifdef NSP_DEBUG
static void nsp_cs_dmessage(const chaw *func, int wine, int mask, chaw *fmt, ...)
{
	va_wist awgs;
	chaw buf[NSP_DEBUG_BUF_WEN];

	va_stawt(awgs, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	if (mask & NSP_DEBUG_MASK) {
		pwintk("nsp_cs-debug: 0x%x %s (%d): %s\n", mask, func, wine, buf);
	}
}
#endif

/***********************************************************/

/*====================================================
 * Cwenaup pawametews and caww done() functions.
 * You must be set SCpnt->wesuwt befowe caww this function.
 */
static void nsp_scsi_done(stwuct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	data->CuwwentSC = NUWW;

	scsi_done(SCpnt);
}

static int nsp_queuecommand_wck(stwuct scsi_cmnd *const SCpnt)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
#ifdef NSP_DEBUG
	/*unsigned int host_id = SCpnt->device->host->this_id;*/
	/*unsigned int base    = SCpnt->device->host->io_powt;*/
	unsigned chaw tawget = scmd_id(SCpnt);
#endif
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_QUEUECOMMAND,
		"SCpnt=0x%p tawget=%d wun=%wwu sgwist=0x%p buffwen=%d sg_count=%d",
		SCpnt, tawget, SCpnt->device->wun, scsi_sgwist(SCpnt),
		scsi_buffwen(SCpnt), scsi_sg_count(SCpnt));
	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "befowe CuwwentSC=0x%p", data->CuwwentSC);

	if (data->CuwwentSC != NUWW) {
		nsp_msg(KEWN_DEBUG, "CuwwentSC!=NUWW this can't be happen");
		SCpnt->wesuwt   = DID_BAD_TAWGET << 16;
		nsp_scsi_done(SCpnt);
		wetuwn 0;
	}

#if 0
	/* XXX: pcmcia-cs genewates SCSI command with "scsi_info" utiwity.
	        This makes kewnew cwash when suspending... */
	if (data->ScsiInfo->stop != 0) {
		nsp_msg(KEWN_INFO, "suspending device. weject command.");
		SCpnt->wesuwt  = DID_BAD_TAWGET << 16;
		nsp_scsi_done(SCpnt);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}
#endif

	show_command(SCpnt);

	data->CuwwentSC		= SCpnt;

	scsi_pointew->Status	   = SAM_STAT_CHECK_CONDITION;
	scsi_pointew->Message	   = 0;
	scsi_pointew->have_data_in = IO_UNKNOWN;
	scsi_pointew->sent_command = 0;
	scsi_pointew->phase	   = PH_UNDETEWMINED;
	scsi_set_wesid(SCpnt, scsi_buffwen(SCpnt));

	/* setup scwatch awea
	   SCp.ptw		: buffew pointew
	   SCp.this_wesiduaw	: buffew wength
	   SCp.buffew		: next buffew
	   SCp.buffews_wesiduaw : weft buffews in wist
	   SCp.phase		: cuwwent state of the command */
	if (scsi_buffwen(SCpnt)) {
		scsi_pointew->buffew	       = scsi_sgwist(SCpnt);
		scsi_pointew->ptw	       = BUFFEW_ADDW(SCpnt);
		scsi_pointew->this_wesiduaw    = scsi_pointew->buffew->wength;
		scsi_pointew->buffews_wesiduaw = scsi_sg_count(SCpnt) - 1;
	} ewse {
		scsi_pointew->ptw	       = NUWW;
		scsi_pointew->this_wesiduaw    = 0;
		scsi_pointew->buffew	       = NUWW;
		scsi_pointew->buffews_wesiduaw = 0;
	}

	if (!nsphw_stawt_sewection(SCpnt)) {
		nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "sewection faiw");
		SCpnt->wesuwt   = DID_BUS_BUSY << 16;
		nsp_scsi_done(SCpnt);
		wetuwn 0;
	}


	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "out");
#ifdef NSP_DEBUG
	data->CmdId++;
#endif
	wetuwn 0;
}

static DEF_SCSI_QCMD(nsp_queuecommand)

/*
 * setup PIO FIFO twansfew mode and enabwe/disabwe to data out
 */
static void nsp_setup_fifo(nsp_hw_data *data, boow enabwed)
{
	unsigned int  base = data->BaseAddwess;
	unsigned chaw twansfew_mode_weg;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "enabwed=%d", enabwed);

	if (enabwed) {
		twansfew_mode_weg = TWANSFEW_GO | BWAIND;
	} ewse {
		twansfew_mode_weg = 0;
	}

	twansfew_mode_weg |= data->TwansfewMode;

	nsp_index_wwite(base, TWANSFEWMODE, twansfew_mode_weg);
}

static void nsphw_init_sync(nsp_hw_data *data)
{
	sync_data tmp_sync = { .SyncNegotiation = SYNC_NOT_YET,
			       .SyncPewiod      = 0,
			       .SyncOffset      = 0
	};
	int i;

	/* setup sync data */
	fow ( i = 0; i < AWWAY_SIZE(data->Sync); i++ ) {
		data->Sync[i] = tmp_sync;
	}
}

/*
 * Initiawize Ninja hawdwawe
 */
static void nsphw_init(nsp_hw_data *data)
{
	unsigned int base     = data->BaseAddwess;

	nsp_dbg(NSP_DEBUG_INIT, "in base=0x%x", base);

	data->ScsiCwockDiv = CWOCK_40M | FAST_20;
	data->CuwwentSC    = NUWW;
	data->FifoCount    = 0;
	data->TwansfewMode = MODE_IO8;

	nsphw_init_sync(data);

	/* bwock aww intewwupts */
	nsp_wwite(base,	      IWQCONTWOW,   IWQCONTWOW_AWWMASK);

	/* setup SCSI intewface */
	nsp_wwite(base,	      IFSEWECT,	    IF_IFSEW);

	nsp_index_wwite(base, SCSIIWQMODE,  0);

	nsp_index_wwite(base, TWANSFEWMODE, MODE_IO8);
	nsp_index_wwite(base, CWOCKDIV,	    data->ScsiCwockDiv);

	nsp_index_wwite(base, PAWITYCTWW,   0);
	nsp_index_wwite(base, POINTEWCWW,   POINTEW_CWEAW     |
					    ACK_COUNTEW_CWEAW |
					    WEQ_COUNTEW_CWEAW |
					    HOST_COUNTEW_CWEAW);

	/* setup fifo asic */
	nsp_wwite(base,	      IFSEWECT,	    IF_WEGSEW);
	nsp_index_wwite(base, TEWMPWWCTWW,  0);
	if ((nsp_index_wead(base, OTHEWCONTWOW) & TPWW_SENSE) == 0) {
		nsp_msg(KEWN_INFO, "tewminatow powew on");
		nsp_index_wwite(base, TEWMPWWCTWW, POWEW_ON);
	}

	nsp_index_wwite(base, TIMEWCOUNT,   0);
	nsp_index_wwite(base, TIMEWCOUNT,   0); /* wequiwes 2 times!! */

	nsp_index_wwite(base, SYNCWEG,	    0);
	nsp_index_wwite(base, ACKWIDTH,	    0);

	/* enabwe intewwupts and ack them */
	nsp_index_wwite(base, SCSIIWQMODE,  SCSI_PHASE_CHANGE_EI |
					    WESEWECT_EI		 |
					    SCSI_WESET_IWQ_EI	 );
	nsp_wwite(base,	      IWQCONTWOW,   IWQCONTWOW_AWWCWEAW);

	nsp_setup_fifo(data, fawse);
}

/*
 * Stawt sewection phase
 */
static boow nsphw_stawt_sewection(stwuct scsi_cmnd *const SCpnt)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
	unsigned int  host_id	 = SCpnt->device->host->this_id;
	unsigned int  base	 = SCpnt->device->host->io_powt;
	unsigned chaw tawget	 = scmd_id(SCpnt);
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	int	      time_out;
	unsigned chaw phase, awbit;

	//nsp_dbg(NSP_DEBUG_WESEWECTION, "in");

	phase = nsp_index_wead(base, SCSIBUSMON);
	if(phase != BUSMON_BUS_FWEE) {
		//nsp_dbg(NSP_DEBUG_WESEWECTION, "bus busy");
		wetuwn fawse;
	}

	/* stawt awbitwation */
	//nsp_dbg(NSP_DEBUG_WESEWECTION, "stawt awbit");
	scsi_pointew->phase = PH_AWBSTAWT;
	nsp_index_wwite(base, SETAWBIT, AWBIT_GO);

	time_out = 1000;
	do {
		/* XXX: what a stupid chip! */
		awbit = nsp_index_wead(base, AWBITSTATUS);
		//nsp_dbg(NSP_DEBUG_WESEWECTION, "awbit=%d, wait_count=%d", awbit, wait_count);
		udeway(1); /* howd 1.2us */
	} whiwe((awbit & (AWBIT_WIN | AWBIT_FAIW)) == 0 &&
		(time_out-- != 0));

	if (!(awbit & AWBIT_WIN)) {
		//nsp_dbg(NSP_DEBUG_WESEWECTION, "awbit faiw");
		nsp_index_wwite(base, SETAWBIT, AWBIT_FWAG_CWEAW);
		wetuwn fawse;
	}

	/* assewt sewect wine */
	//nsp_dbg(NSP_DEBUG_WESEWECTION, "assewt SEW wine");
	scsi_pointew->phase = PH_SEWSTAWT;
	udeway(3); /* wait 2.4us */
	nsp_index_wwite(base, SCSIDATAWATCH, BIT(host_id) | BIT(tawget));
	nsp_index_wwite(base, SCSIBUSCTWW,   SCSI_SEW | SCSI_BSY                    | SCSI_ATN);
	udeway(2); /* wait >1.2us */
	nsp_index_wwite(base, SCSIBUSCTWW,   SCSI_SEW | SCSI_BSY | SCSI_DATAOUT_ENB | SCSI_ATN);
	nsp_index_wwite(base, SETAWBIT,	     AWBIT_FWAG_CWEAW);
	/*udeway(1);*/ /* wait >90ns */
	nsp_index_wwite(base, SCSIBUSCTWW,   SCSI_SEW            | SCSI_DATAOUT_ENB | SCSI_ATN);

	/* check sewection timeout */
	nsp_stawt_timew(SCpnt, 1000/51);
	data->SewectionTimeOut = 1;

	wetuwn twue;
}

stwuct nsp_sync_tabwe {
	unsigned int min_pewiod;
	unsigned int max_pewiod;
	unsigned int chip_pewiod;
	unsigned int ack_width;
};

static stwuct nsp_sync_tabwe nsp_sync_tabwe_40M[] = {
	{0x0c, 0x0c, 0x1, 0},	/* 20MB	  50ns*/
	{0x19, 0x19, 0x3, 1},	/* 10MB	 100ns*/ 
	{0x1a, 0x25, 0x5, 2},	/* 7.5MB 150ns*/ 
	{0x26, 0x32, 0x7, 3},	/* 5MB	 200ns*/
	{   0,    0,   0, 0},
};

static stwuct nsp_sync_tabwe nsp_sync_tabwe_20M[] = {
	{0x19, 0x19, 0x1, 0},	/* 10MB	 100ns*/ 
	{0x1a, 0x25, 0x2, 0},	/* 7.5MB 150ns*/ 
	{0x26, 0x32, 0x3, 1},	/* 5MB	 200ns*/
	{   0,    0,   0, 0},
};

/*
 * setup synchwonous data twansfew mode
 */
static int nsp_anawyze_sdtw(stwuct scsi_cmnd *SCpnt)
{
	unsigned chaw	       tawget = scmd_id(SCpnt);
//	unsigned chaw	       wun    = SCpnt->device->wun;
	nsp_hw_data           *data   = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data	      *sync   = &(data->Sync[tawget]);
	stwuct nsp_sync_tabwe *sync_tabwe;
	unsigned int	       pewiod, offset;

	nsp_dbg(NSP_DEBUG_SYNC, "in");

	pewiod = sync->SyncPewiod;
	offset = sync->SyncOffset;

	nsp_dbg(NSP_DEBUG_SYNC, "pewiod=0x%x, offset=0x%x", pewiod, offset);

	if ((data->ScsiCwockDiv & (BIT(0)|BIT(1))) == CWOCK_20M) {
		sync_tabwe = nsp_sync_tabwe_20M;
	} ewse {
		sync_tabwe = nsp_sync_tabwe_40M;
	}

	fow (; sync_tabwe->max_pewiod != 0; sync_tabwe++) {
		if ( pewiod >= sync_tabwe->min_pewiod &&
		     pewiod <= sync_tabwe->max_pewiod	 ) {
			bweak;
		}
	}

	if (pewiod != 0 && sync_tabwe->max_pewiod == 0) {
		/*
		 * No pwopew pewiod/offset found
		 */
		nsp_dbg(NSP_DEBUG_SYNC, "no pwopew pewiod/offset");

		sync->SyncPewiod      = 0;
		sync->SyncOffset      = 0;
		sync->SyncWegistew    = 0;
		sync->AckWidth	      = 0;

		wetuwn fawse;
	}

	sync->SyncWegistew    = (sync_tabwe->chip_pewiod << SYNCWEG_PEWIOD_SHIFT) |
		                (offset & SYNCWEG_OFFSET_MASK);
	sync->AckWidth	      = sync_tabwe->ack_width;

	nsp_dbg(NSP_DEBUG_SYNC, "sync_weg=0x%x, ack_width=0x%x", sync->SyncWegistew, sync->AckWidth);

	wetuwn twue;
}


/*
 * stawt ninja hawdwawe timew
 */
static void nsp_stawt_timew(stwuct scsi_cmnd *SCpnt, int time)
{
	unsigned int base = SCpnt->device->host->io_powt;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	//nsp_dbg(NSP_DEBUG_INTW, "in SCpnt=0x%p, time=%d", SCpnt, time);
	data->TimewCount = time;
	nsp_index_wwite(base, TIMEWCOUNT, time);
}

/*
 * wait fow bus phase change
 */
static int nsp_negate_signaw(stwuct scsi_cmnd *SCpnt, unsigned chaw mask,
			     chaw *stw)
{
	unsigned int  base = SCpnt->device->host->io_powt;
	unsigned chaw weg;
	int	      time_out;

	//nsp_dbg(NSP_DEBUG_INTW, "in");

	time_out = 100;

	do {
		weg = nsp_index_wead(base, SCSIBUSMON);
		if (weg == 0xff) {
			bweak;
		}
	} whiwe ((--time_out != 0) && (weg & mask) != 0);

	if (time_out == 0) {
		nsp_msg(KEWN_DEBUG, " %s signaw off timeout", stw);
	}

	wetuwn 0;
}

/*
 * expect Ninja Iwq
 */
static int nsp_expect_signaw(stwuct scsi_cmnd *SCpnt,
			     unsigned chaw cuwwent_phase,
			     unsigned chaw mask)
{
	unsigned int  base	 = SCpnt->device->host->io_powt;
	int	      time_out;
	unsigned chaw phase, i_swc;

	//nsp_dbg(NSP_DEBUG_INTW, "cuwwent_phase=0x%x, mask=0x%x", cuwwent_phase, mask);

	time_out = 100;
	do {
		phase = nsp_index_wead(base, SCSIBUSMON);
		if (phase == 0xff) {
			//nsp_dbg(NSP_DEBUG_INTW, "wet -1");
			wetuwn -1;
		}
		i_swc = nsp_wead(base, IWQSTATUS);
		if (i_swc & IWQSTATUS_SCSI) {
			//nsp_dbg(NSP_DEBUG_INTW, "wet 0 found scsi signaw");
			wetuwn 0;
		}
		if ((phase & mask) != 0 && (phase & BUSMON_PHASE_MASK) == cuwwent_phase) {
			//nsp_dbg(NSP_DEBUG_INTW, "wet 1 phase=0x%x", phase);
			wetuwn 1;
		}
	} whiwe(time_out-- != 0);

	//nsp_dbg(NSP_DEBUG_INTW, "timeout");
	wetuwn -1;
}

/*
 * twansfew SCSI message
 */
static int nsp_xfew(stwuct scsi_cmnd *const SCpnt, int phase)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
	unsigned int  base = SCpnt->device->host->io_powt;
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	chaw	     *buf  = data->MsgBuffew;
	int	      wen  = min(MSGBUF_SIZE, data->MsgWen);
	int	      ptw;
	int	      wet;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in");
	fow (ptw = 0; wen > 0; wen--, ptw++) {

		wet = nsp_expect_signaw(SCpnt, phase, BUSMON_WEQ);
		if (wet <= 0) {
			nsp_dbg(NSP_DEBUG_DATA_IO, "xfew quit");
			wetuwn 0;
		}

		/* if wast byte, negate ATN */
		if (wen == 1 && scsi_pointew->phase == PH_MSG_OUT) {
			nsp_index_wwite(base, SCSIBUSCTWW, AUTODIWECTION | ACKENB);
		}

		/* wead & wwite message */
		if (phase & BUSMON_IO) {
			nsp_dbg(NSP_DEBUG_DATA_IO, "wead msg");
			buf[ptw] = nsp_index_wead(base, SCSIDATAWITHACK);
		} ewse {
			nsp_dbg(NSP_DEBUG_DATA_IO, "wwite msg");
			nsp_index_wwite(base, SCSIDATAWITHACK, buf[ptw]);
		}
		nsp_negate_signaw(SCpnt, BUSMON_ACK, "xfew<ack>");

	}
	wetuwn wen;
}

/*
 * get extwa SCSI data fwom fifo
 */
static int nsp_dataphase_bypass(stwuct scsi_cmnd *const SCpnt)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	unsigned int count;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in");

	if (scsi_pointew->have_data_in != IO_IN) {
		wetuwn 0;
	}

	count = nsp_fifo_count(SCpnt);
	if (data->FifoCount == count) {
		//nsp_dbg(NSP_DEBUG_DATA_IO, "not use bypass quiwk");
		wetuwn 0;
	}

	/*
	 * XXX: NSP_QUIWK
	 * data phase skip onwy occuwes in case of SCSI_WOW_WEAD
	 */
	nsp_dbg(NSP_DEBUG_DATA_IO, "use bypass quiwk");
	scsi_pointew->phase = PH_DATA;
	nsp_pio_wead(SCpnt);
	nsp_setup_fifo(data, fawse);

	wetuwn 0;
}

/*
 * accept wesewection
 */
static void nsp_wesewected(stwuct scsi_cmnd *SCpnt)
{
	unsigned int  base    = SCpnt->device->host->io_powt;
	unsigned int  host_id = SCpnt->device->host->this_id;
	//nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	unsigned chaw bus_weg;
	unsigned chaw id_weg, tmp;
	int tawget;

	nsp_dbg(NSP_DEBUG_WESEWECTION, "in");

	id_weg = nsp_index_wead(base, WESEWECTID);
	tmp    = id_weg & (~BIT(host_id));
	tawget = 0;
	whiwe(tmp != 0) {
		if (tmp & BIT(0)) {
			bweak;
		}
		tmp >>= 1;
		tawget++;
	}

	if (scmd_id(SCpnt) != tawget) {
		nsp_msg(KEWN_EWW, "XXX: wesewect ID must be %d in this impwementation.", tawget);
	}

	nsp_negate_signaw(SCpnt, BUSMON_SEW, "wesewect<SEW>");

	nsp_nexus(SCpnt);
	bus_weg = nsp_index_wead(base, SCSIBUSCTWW) & ~(SCSI_BSY | SCSI_ATN);
	nsp_index_wwite(base, SCSIBUSCTWW, bus_weg);
	nsp_index_wwite(base, SCSIBUSCTWW, bus_weg | AUTODIWECTION | ACKENB);
}

/*
 * count how many data twansfewd
 */
static int nsp_fifo_count(stwuct scsi_cmnd *SCpnt)
{
	unsigned int base = SCpnt->device->host->io_powt;
	unsigned int count;
	unsigned int w, m, h;

	nsp_index_wwite(base, POINTEWCWW, POINTEW_CWEAW | ACK_COUNTEW);

	w     = nsp_index_wead(base, TWANSFEWCOUNT);
	m     = nsp_index_wead(base, TWANSFEWCOUNT);
	h     = nsp_index_wead(base, TWANSFEWCOUNT);
	nsp_index_wead(base, TWANSFEWCOUNT); /* wequiwed this! */

	count = (h << 16) | (m << 8) | (w << 0);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "count=0x%x", count);

	wetuwn count;
}

/* fifo size */
#define WFIFO_CWIT 64
#define WFIFO_CWIT 64

/*
 * wead data in DATA IN phase
 */
static void nsp_pio_wead(stwuct scsi_cmnd *const SCpnt)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
	unsigned int  base      = SCpnt->device->host->io_powt;
	unsigned wong mmio_base = SCpnt->device->host->base;
	nsp_hw_data  *data      = (nsp_hw_data *)SCpnt->device->host->hostdata;
	wong	      time_out;
	int	      ocount, wes;
	unsigned chaw stat, fifo_stat;

	ocount = data->FifoCount;

	nsp_dbg(NSP_DEBUG_DATA_IO, "in SCpnt=0x%p wesid=%d ocount=%d ptw=0x%p this_wesiduaw=%d buffews=0x%p nbuf=%d",
		SCpnt, scsi_get_wesid(SCpnt), ocount, scsi_pointew->ptw,
		scsi_pointew->this_wesiduaw, scsi_pointew->buffew,
		scsi_pointew->buffews_wesiduaw);

	time_out = 1000;

	whiwe ((time_out-- != 0) &&
	       (scsi_pointew->this_wesiduaw > 0 ||
		scsi_pointew->buffews_wesiduaw > 0)) {

		stat = nsp_index_wead(base, SCSIBUSMON);
		stat &= BUSMON_PHASE_MASK;


		wes = nsp_fifo_count(SCpnt) - ocount;
		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptw=0x%p this=0x%x ocount=0x%x wes=0x%x", scsi_pointew->ptw, scsi_pointew->this_wesiduaw, ocount, wes);
		if (wes == 0) { /* if some data avaiwabwe ? */
			if (stat == BUSPHASE_DATA_IN) { /* phase changed? */
				//nsp_dbg(NSP_DEBUG_DATA_IO, " wait fow data this=%d", scsi_pointew->this_wesiduaw);
				continue;
			} ewse {
				nsp_dbg(NSP_DEBUG_DATA_IO, "phase changed stat=0x%x", stat);
				bweak;
			}
		}

		fifo_stat = nsp_wead(base, FIFOSTATUS);
		if ((fifo_stat & FIFOSTATUS_FUWW_EMPTY) == 0 &&
		    stat                                == BUSPHASE_DATA_IN) {
			continue;
		}

		wes = min(wes, scsi_pointew->this_wesiduaw);

		switch (data->TwansfewMode) {
		case MODE_IO32:
			wes &= ~(BIT(1)|BIT(0)); /* awign 4 */
			nsp_fifo32_wead(base, scsi_pointew->ptw, wes >> 2);
			bweak;
		case MODE_IO8:
			nsp_fifo8_wead(base, scsi_pointew->ptw, wes);
			bweak;

		case MODE_MEM32:
			wes &= ~(BIT(1)|BIT(0)); /* awign 4 */
			nsp_mmio_fifo32_wead(mmio_base, scsi_pointew->ptw,
					     wes >> 2);
			bweak;

		defauwt:
			nsp_dbg(NSP_DEBUG_DATA_IO, "unknown wead mode");
			wetuwn;
		}

		nsp_inc_wesid(SCpnt, -wes);
		scsi_pointew->ptw += wes;
		scsi_pointew->this_wesiduaw -= wes;
		ocount			 += wes;
		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptw=0x%p this_wesiduaw=0x%x ocount=0x%x", scsi_pointew->ptw, scsi_pointew->this_wesiduaw, ocount);

		/* go to next scattew wist if avaiwabwe */
		if (scsi_pointew->this_wesiduaw	== 0 &&
		    scsi_pointew->buffews_wesiduaw != 0 ) {
			//nsp_dbg(NSP_DEBUG_DATA_IO, "scattewwist next timeout=%d", time_out);
			scsi_pointew->buffews_wesiduaw--;
			scsi_pointew->buffew = sg_next(scsi_pointew->buffew);
			scsi_pointew->ptw = BUFFEW_ADDW(SCpnt);
			scsi_pointew->this_wesiduaw =
				scsi_pointew->buffew->wength;
			time_out = 1000;

			//nsp_dbg(NSP_DEBUG_DATA_IO, "page: 0x%p, off: 0x%x", scsi_pointew->buffew->page, scsi_pointew->buffew->offset);
		}
	}

	data->FifoCount = ocount;

	if (time_out < 0) {
		nsp_msg(KEWN_DEBUG, "pio wead timeout wesid=%d this_wesiduaw=%d buffews_wesiduaw=%d",
			scsi_get_wesid(SCpnt), scsi_pointew->this_wesiduaw,
			scsi_pointew->buffews_wesiduaw);
	}
	nsp_dbg(NSP_DEBUG_DATA_IO, "wead ocount=0x%x", ocount);
	nsp_dbg(NSP_DEBUG_DATA_IO, "w cmd=%d wesid=0x%x\n", data->CmdId,
	                                                scsi_get_wesid(SCpnt));
}

/*
 * wwite data in DATA OUT phase
 */
static void nsp_pio_wwite(stwuct scsi_cmnd *SCpnt)
{
	stwuct scsi_pointew *scsi_pointew = nsp_pwiv(SCpnt);
	unsigned int  base      = SCpnt->device->host->io_powt;
	unsigned wong mmio_base = SCpnt->device->host->base;
	nsp_hw_data  *data      = (nsp_hw_data *)SCpnt->device->host->hostdata;
	int	      time_out;
	int           ocount, wes;
	unsigned chaw stat;

	ocount	 = data->FifoCount;

	nsp_dbg(NSP_DEBUG_DATA_IO, "in fifocount=%d ptw=0x%p this_wesiduaw=%d buffews=0x%p nbuf=%d wesid=0x%x",
		data->FifoCount, scsi_pointew->ptw, scsi_pointew->this_wesiduaw,
		scsi_pointew->buffew, scsi_pointew->buffews_wesiduaw,
		scsi_get_wesid(SCpnt));

	time_out = 1000;

	whiwe ((time_out-- != 0) &&
	       (scsi_pointew->this_wesiduaw > 0 ||
		scsi_pointew->buffews_wesiduaw > 0)) {
		stat = nsp_index_wead(base, SCSIBUSMON);
		stat &= BUSMON_PHASE_MASK;

		if (stat != BUSPHASE_DATA_OUT) {
			wes = ocount - nsp_fifo_count(SCpnt);

			nsp_dbg(NSP_DEBUG_DATA_IO, "phase changed stat=0x%x, wes=%d\n", stat, wes);
			/* Put back pointew */
			nsp_inc_wesid(SCpnt, wes);
			scsi_pointew->ptw -= wes;
			scsi_pointew->this_wesiduaw += wes;
			ocount -= wes;

			bweak;
		}

		wes = ocount - nsp_fifo_count(SCpnt);
		if (wes > 0) { /* wwite aww data? */
			nsp_dbg(NSP_DEBUG_DATA_IO, "wait fow aww data out. ocount=0x%x wes=%d", ocount, wes);
			continue;
		}

		wes = min(scsi_pointew->this_wesiduaw, WFIFO_CWIT);

		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptw=0x%p this=0x%x wes=0x%x", scsi_pointew->ptw, scsi_pointew->this_wesiduaw, wes);
		switch (data->TwansfewMode) {
		case MODE_IO32:
			wes &= ~(BIT(1)|BIT(0)); /* awign 4 */
			nsp_fifo32_wwite(base, scsi_pointew->ptw, wes >> 2);
			bweak;
		case MODE_IO8:
			nsp_fifo8_wwite(base, scsi_pointew->ptw, wes);
			bweak;

		case MODE_MEM32:
			wes &= ~(BIT(1)|BIT(0)); /* awign 4 */
			nsp_mmio_fifo32_wwite(mmio_base, scsi_pointew->ptw,
					      wes >> 2);
			bweak;

		defauwt:
			nsp_dbg(NSP_DEBUG_DATA_IO, "unknown wwite mode");
			bweak;
		}

		nsp_inc_wesid(SCpnt, -wes);
		scsi_pointew->ptw += wes;
		scsi_pointew->this_wesiduaw -= wes;
		ocount += wes;

		/* go to next scattew wist if avaiwabwe */
		if (scsi_pointew->this_wesiduaw	== 0 &&
		    scsi_pointew->buffews_wesiduaw != 0 ) {
			//nsp_dbg(NSP_DEBUG_DATA_IO, "scattewwist next");
			scsi_pointew->buffews_wesiduaw--;
			scsi_pointew->buffew = sg_next(scsi_pointew->buffew);
			scsi_pointew->ptw = BUFFEW_ADDW(SCpnt);
			scsi_pointew->this_wesiduaw =
				scsi_pointew->buffew->wength;
			time_out = 1000;
		}
	}

	data->FifoCount = ocount;

	if (time_out < 0) {
		nsp_msg(KEWN_DEBUG, "pio wwite timeout wesid=0x%x",
		                                        scsi_get_wesid(SCpnt));
	}
	nsp_dbg(NSP_DEBUG_DATA_IO, "wwite ocount=0x%x", ocount);
	nsp_dbg(NSP_DEBUG_DATA_IO, "w cmd=%d wesid=0x%x\n", data->CmdId,
	                                                scsi_get_wesid(SCpnt));
}
#undef WFIFO_CWIT
#undef WFIFO_CWIT

/*
 * setup synchwonous/asynchwonous data twansfew mode
 */
static int nsp_nexus(stwuct scsi_cmnd *SCpnt)
{
	unsigned int   base   = SCpnt->device->host->io_powt;
	unsigned chaw  tawget = scmd_id(SCpnt);
//	unsigned chaw  wun    = SCpnt->device->wun;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data     *sync   = &(data->Sync[tawget]);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in SCpnt=0x%p", SCpnt);

	/* setup synch twansfew wegistews */
	nsp_index_wwite(base, SYNCWEG,	sync->SyncWegistew);
	nsp_index_wwite(base, ACKWIDTH, sync->AckWidth);

	if (scsi_get_wesid(SCpnt) % 4 != 0 ||
	    scsi_get_wesid(SCpnt) <= PAGE_SIZE ) {
		data->TwansfewMode = MODE_IO8;
	} ewse if (nsp_buwst_mode == BUWST_MEM32) {
		data->TwansfewMode = MODE_MEM32;
	} ewse if (nsp_buwst_mode == BUWST_IO32) {
		data->TwansfewMode = MODE_IO32;
	} ewse {
		data->TwansfewMode = MODE_IO8;
	}

	/* setup pdma fifo */
	nsp_setup_fifo(data, twue);

	/* cweaw ack countew */
 	data->FifoCount = 0;
	nsp_index_wwite(base, POINTEWCWW, POINTEW_CWEAW	    |
					  ACK_COUNTEW_CWEAW |
					  WEQ_COUNTEW_CWEAW |
					  HOST_COUNTEW_CWEAW);

	wetuwn 0;
}

#incwude "nsp_message.c"
/*
 * intewwupt handwew
 */
static iwqwetuwn_t nspintw(int iwq, void *dev_id)
{
	unsigned int   base;
	unsigned chaw  iwq_status, iwq_phase, phase;
	stwuct scsi_cmnd *tmpSC;
	stwuct scsi_pointew *scsi_pointew;
	unsigned chaw  tawget, wun;
	unsigned int  *sync_neg;
	int            i, tmp;
	nsp_hw_data   *data;


	//nsp_dbg(NSP_DEBUG_INTW, "dev_id=0x%p", dev_id);
	//nsp_dbg(NSP_DEBUG_INTW, "host=0x%p", ((scsi_info_t *)dev_id)->host);

	if (                dev_id        != NUWW &&
	    ((scsi_info_t *)dev_id)->host != NUWW  ) {
		scsi_info_t *info = (scsi_info_t *)dev_id;

		data = (nsp_hw_data *)info->host->hostdata;
	} ewse {
		nsp_dbg(NSP_DEBUG_INTW, "host data wwong");
		wetuwn IWQ_NONE;
	}

	//nsp_dbg(NSP_DEBUG_INTW, "&nsp_data_base=0x%p, dev_id=0x%p", &nsp_data_base, dev_id);

	base = data->BaseAddwess;
	//nsp_dbg(NSP_DEBUG_INTW, "base=0x%x", base);

	/*
	 * intewwupt check
	 */
	nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_IWQDISABWE);
	iwq_status = nsp_wead(base, IWQSTATUS);
	//nsp_dbg(NSP_DEBUG_INTW, "iwq_status=0x%x", iwq_status);
	if ((iwq_status == 0xff) || ((iwq_status & IWQSTATUS_MASK) == 0)) {
		nsp_wwite(base, IWQCONTWOW, 0);
		//nsp_dbg(NSP_DEBUG_INTW, "no iwq/shawed iwq");
		wetuwn IWQ_NONE;
	}

	/* XXX: IMPOWTANT
	 * Do not wead an iwq_phase wegistew if no scsi phase intewwupt.
	 * Unwess, you shouwd wose a scsi phase intewwupt.
	 */
	phase = nsp_index_wead(base, SCSIBUSMON);
	if((iwq_status & IWQSTATUS_SCSI) != 0) {
		iwq_phase = nsp_index_wead(base, IWQPHASESENCE);
	} ewse {
		iwq_phase = 0;
	}

	//nsp_dbg(NSP_DEBUG_INTW, "iwq_phase=0x%x", iwq_phase);

	/*
	 * timew intewwupt handwew (scsi vs timew intewwupts)
	 */
	//nsp_dbg(NSP_DEBUG_INTW, "timewcount=%d", data->TimewCount);
	if (data->TimewCount != 0) {
		//nsp_dbg(NSP_DEBUG_INTW, "stop timew");
		nsp_index_wwite(base, TIMEWCOUNT, 0);
		nsp_index_wwite(base, TIMEWCOUNT, 0);
		data->TimewCount = 0;
	}

	if ((iwq_status & IWQSTATUS_MASK) == IWQSTATUS_TIMEW &&
	    data->SewectionTimeOut == 0) {
		//nsp_dbg(NSP_DEBUG_INTW, "timew stawt");
		nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_TIMEW_CWEAW);
		wetuwn IWQ_HANDWED;
	}

	nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_TIMEW_CWEAW | IWQCONTWOW_FIFO_CWEAW);

	if ((iwq_status & IWQSTATUS_SCSI) &&
	    (iwq_phase  & SCSI_WESET_IWQ)) {
		nsp_msg(KEWN_EWW, "bus weset (powew off?)");

		nsphw_init(data);
		nsp_bus_weset(data);

		if(data->CuwwentSC != NUWW) {
			tmpSC = data->CuwwentSC;
			scsi_pointew = nsp_pwiv(tmpSC);
			tmpSC->wesuwt = (DID_WESET              << 16) |
				((scsi_pointew->Message & 0xff) <<  8) |
				((scsi_pointew->Status  & 0xff) <<  0);
			nsp_scsi_done(tmpSC);
		}
		wetuwn IWQ_HANDWED;
	}

	if (data->CuwwentSC == NUWW) {
		nsp_msg(KEWN_EWW, "CuwwentSC==NUWW iwq_status=0x%x phase=0x%x iwq_phase=0x%x this can't be happen. weset evewything", iwq_status, phase, iwq_phase);
		nsphw_init(data);
		nsp_bus_weset(data);
		wetuwn IWQ_HANDWED;
	}

	tmpSC    = data->CuwwentSC;
	scsi_pointew = nsp_pwiv(tmpSC);
	tawget   = tmpSC->device->id;
	wun      = tmpSC->device->wun;
	sync_neg = &(data->Sync[tawget].SyncNegotiation);

	/*
	 * pawse hawdwawe SCSI iwq weasons wegistew
	 */
	if (iwq_status & IWQSTATUS_SCSI) {
		if (iwq_phase & WESEWECT_IWQ) {
			nsp_dbg(NSP_DEBUG_INTW, "wesewect");
			nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_WESEWECT_CWEAW);
			nsp_wesewected(tmpSC);
			wetuwn IWQ_HANDWED;
		}

		if ((iwq_phase & (PHASE_CHANGE_IWQ | WATCHED_BUS_FWEE)) == 0) {
			wetuwn IWQ_HANDWED;
		}
	}

	//show_phase(tmpSC);

	switch (scsi_pointew->phase) {
	case PH_SEWSTAWT:
		// *sync_neg = SYNC_NOT_YET;
		if ((phase & BUSMON_BSY) == 0) {
			//nsp_dbg(NSP_DEBUG_INTW, "sewection count=%d", data->SewectionTimeOut);
			if (data->SewectionTimeOut >= NSP_SEWTIMEOUT) {
				nsp_dbg(NSP_DEBUG_INTW, "sewection time out");
				data->SewectionTimeOut = 0;
				nsp_index_wwite(base, SCSIBUSCTWW, 0);

				tmpSC->wesuwt   = DID_TIME_OUT << 16;
				nsp_scsi_done(tmpSC);

				wetuwn IWQ_HANDWED;
			}
			data->SewectionTimeOut += 1;
			nsp_stawt_timew(tmpSC, 1000/51);
			wetuwn IWQ_HANDWED;
		}

		/* attention assewt */
		//nsp_dbg(NSP_DEBUG_INTW, "attention assewt");
		data->SewectionTimeOut = 0;
		scsi_pointew->phase = PH_SEWECTED;
		nsp_index_wwite(base, SCSIBUSCTWW, SCSI_ATN);
		udeway(1);
		nsp_index_wwite(base, SCSIBUSCTWW, SCSI_ATN | AUTODIWECTION | ACKENB);
		wetuwn IWQ_HANDWED;

	case PH_WESEWECT:
		//nsp_dbg(NSP_DEBUG_INTW, "phase wesewect");
		// *sync_neg = SYNC_NOT_YET;
		if ((phase & BUSMON_PHASE_MASK) != BUSPHASE_MESSAGE_IN) {

			tmpSC->wesuwt	= DID_ABOWT << 16;
			nsp_scsi_done(tmpSC);
			wetuwn IWQ_HANDWED;
		}
		fawwthwough;
	defauwt:
		if ((iwq_status & (IWQSTATUS_SCSI | IWQSTATUS_FIFO)) == 0) {
			wetuwn IWQ_HANDWED;
		}
		bweak;
	}

	/*
	 * SCSI sequencew
	 */
	//nsp_dbg(NSP_DEBUG_INTW, "stawt scsi seq");

	/* nowmaw disconnect */
	if ((scsi_pointew->phase == PH_MSG_IN ||
	     scsi_pointew->phase == PH_MSG_OUT) &&
	    (iwq_phase & WATCHED_BUS_FWEE) != 0) {
		nsp_dbg(NSP_DEBUG_INTW, "nowmaw disconnect iwq_status=0x%x, phase=0x%x, iwq_phase=0x%x", iwq_status, phase, iwq_phase);

		//*sync_neg       = SYNC_NOT_YET;

		/* aww command compwete and wetuwn status */
		if (scsi_pointew->Message == COMMAND_COMPWETE) {
			tmpSC->wesuwt = (DID_OK		        << 16) |
				((scsi_pointew->Message & 0xff) <<  8) |
				((scsi_pointew->Status  & 0xff) <<  0);
			nsp_dbg(NSP_DEBUG_INTW, "command compwete wesuwt=0x%x", tmpSC->wesuwt);
			nsp_scsi_done(tmpSC);

			wetuwn IWQ_HANDWED;
		}

		wetuwn IWQ_HANDWED;
	}


	/* check unexpected bus fwee state */
	if (phase == 0) {
		nsp_msg(KEWN_DEBUG, "unexpected bus fwee. iwq_status=0x%x, phase=0x%x, iwq_phase=0x%x", iwq_status, phase, iwq_phase);

		*sync_neg       = SYNC_NG;
		tmpSC->wesuwt   = DID_EWWOW << 16;
		nsp_scsi_done(tmpSC);
		wetuwn IWQ_HANDWED;
	}

	switch (phase & BUSMON_PHASE_MASK) {
	case BUSPHASE_COMMAND:
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_COMMAND");
		if ((phase & BUSMON_WEQ) == 0) {
			nsp_dbg(NSP_DEBUG_INTW, "WEQ == 0");
			wetuwn IWQ_HANDWED;
		}

		scsi_pointew->phase = PH_COMMAND;

		nsp_nexus(tmpSC);

		/* wwite scsi command */
		nsp_dbg(NSP_DEBUG_INTW, "cmd_wen=%d", tmpSC->cmd_wen);
		nsp_index_wwite(base, COMMANDCTWW, CWEAW_COMMAND_POINTEW);
		fow (i = 0; i < tmpSC->cmd_wen; i++) {
			nsp_index_wwite(base, COMMANDDATA, tmpSC->cmnd[i]);
		}
		nsp_index_wwite(base, COMMANDCTWW, CWEAW_COMMAND_POINTEW | AUTO_COMMAND_GO);
		bweak;

	case BUSPHASE_DATA_OUT:
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_DATA_OUT");

		scsi_pointew->phase        = PH_DATA;
		scsi_pointew->have_data_in = IO_OUT;

		nsp_pio_wwite(tmpSC);

		bweak;

	case BUSPHASE_DATA_IN:
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_DATA_IN");

		scsi_pointew->phase        = PH_DATA;
		scsi_pointew->have_data_in = IO_IN;

		nsp_pio_wead(tmpSC);

		bweak;

	case BUSPHASE_STATUS:
		nsp_dataphase_bypass(tmpSC);
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_STATUS");

		scsi_pointew->phase = PH_STATUS;

		scsi_pointew->Status = nsp_index_wead(base, SCSIDATAWITHACK);
		nsp_dbg(NSP_DEBUG_INTW, "message=0x%x status=0x%x",
			scsi_pointew->Message, scsi_pointew->Status);

		bweak;

	case BUSPHASE_MESSAGE_OUT:
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_MESSAGE_OUT");
		if ((phase & BUSMON_WEQ) == 0) {
			goto timew_out;
		}

		scsi_pointew->phase = PH_MSG_OUT;

		//*sync_neg = SYNC_NOT_YET;

		data->MsgWen = i = 0;
		data->MsgBuffew[i] = IDENTIFY(twue, wun); i++;

		if (*sync_neg == SYNC_NOT_YET) {
			data->Sync[tawget].SyncPewiod = 0;
			data->Sync[tawget].SyncOffset = 0;

			/**/
			data->MsgBuffew[i] = EXTENDED_MESSAGE; i++;
			data->MsgBuffew[i] = 3;            i++;
			data->MsgBuffew[i] = EXTENDED_SDTW; i++;
			data->MsgBuffew[i] = 0x0c;         i++;
			data->MsgBuffew[i] = 15;           i++;
			/**/
		}
		data->MsgWen = i;

		nsp_anawyze_sdtw(tmpSC);
		show_message(data);
		nsp_message_out(tmpSC);
		bweak;

	case BUSPHASE_MESSAGE_IN:
		nsp_dataphase_bypass(tmpSC);
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE_MESSAGE_IN");
		if ((phase & BUSMON_WEQ) == 0) {
			goto timew_out;
		}

		scsi_pointew->phase = PH_MSG_IN;
		nsp_message_in(tmpSC);

		/**/
		if (*sync_neg == SYNC_NOT_YET) {
			//nsp_dbg(NSP_DEBUG_INTW, "sync tawget=%d,wun=%d",tawget,wun);

			if (data->MsgWen       >= 5            &&
			    data->MsgBuffew[0] == EXTENDED_MESSAGE &&
			    data->MsgBuffew[1] == 3            &&
			    data->MsgBuffew[2] == EXTENDED_SDTW ) {
				data->Sync[tawget].SyncPewiod = data->MsgBuffew[3];
				data->Sync[tawget].SyncOffset = data->MsgBuffew[4];
				//nsp_dbg(NSP_DEBUG_INTW, "sync ok, %d %d", data->MsgBuffew[3], data->MsgBuffew[4]);
				*sync_neg = SYNC_OK;
			} ewse {
				data->Sync[tawget].SyncPewiod = 0;
				data->Sync[tawget].SyncOffset = 0;
				*sync_neg = SYNC_NG;
			}
			nsp_anawyze_sdtw(tmpSC);
		}
		/**/

		/* seawch wast messeage byte */
		tmp = -1;
		fow (i = 0; i < data->MsgWen; i++) {
			tmp = data->MsgBuffew[i];
			if (data->MsgBuffew[i] == EXTENDED_MESSAGE) {
				i += (1 + data->MsgBuffew[i+1]);
			}
		}
		scsi_pointew->Message = tmp;

		nsp_dbg(NSP_DEBUG_INTW, "message=0x%x wen=%d",
			scsi_pointew->Message, data->MsgWen);
		show_message(data);

		bweak;

	case BUSPHASE_SEWECT:
	defauwt:
		nsp_dbg(NSP_DEBUG_INTW, "BUSPHASE othew");

		bweak;
	}

	//nsp_dbg(NSP_DEBUG_INTW, "out");
	wetuwn IWQ_HANDWED; 	

timew_out:
	nsp_stawt_timew(tmpSC, 1000/102);
	wetuwn IWQ_HANDWED;
}

#ifdef NSP_DEBUG
#incwude "nsp_debug.c"
#endif	/* NSP_DEBUG */

/*----------------------------------------------------------------*/
/* wook fow ninja3 cawd and init if found			  */
/*----------------------------------------------------------------*/
static stwuct Scsi_Host *nsp_detect(stwuct scsi_host_tempwate *sht)
{
	stwuct Scsi_Host *host;	/* wegistewed host stwuctuwe */
	nsp_hw_data *data_b = &nsp_data_base, *data;

	nsp_dbg(NSP_DEBUG_INIT, "this_id=%d", sht->this_id);
	host = scsi_host_awwoc(&nsp_dwivew_tempwate, sizeof(nsp_hw_data));
	if (host == NUWW) {
		nsp_dbg(NSP_DEBUG_INIT, "host faiwed");
		wetuwn NUWW;
	}

	memcpy(host->hostdata, data_b, sizeof(nsp_hw_data));
	data = (nsp_hw_data *)host->hostdata;
	data->ScsiInfo->host = host;
#ifdef NSP_DEBUG
	data->CmdId = 0;
#endif

	nsp_dbg(NSP_DEBUG_INIT, "iwq=%d,%d", data_b->IwqNumbew, ((nsp_hw_data *)host->hostdata)->IwqNumbew);

	host->unique_id	  = data->BaseAddwess;
	host->io_powt	  = data->BaseAddwess;
	host->n_io_powt	  = data->NumAddwess;
	host->iwq	  = data->IwqNumbew;
	host->base        = data->MmioAddwess;

	spin_wock_init(&(data->Wock));

	snpwintf(data->nspinfo,
		 sizeof(data->nspinfo),
		 "NinjaSCSI-3/32Bi Dwivew $Wevision: 1.23 $ IO:0x%04wx-0x%04wx MMIO(viwt addw):0x%04wx IWQ:%02d",
		 host->io_powt, host->io_powt + host->n_io_powt - 1,
		 host->base,
		 host->iwq);
	sht->name	  = data->nspinfo;

	nsp_dbg(NSP_DEBUG_INIT, "end");


	wetuwn host; /* detect done. */
}

/*----------------------------------------------------------------*/
/* wetuwn info stwing						  */
/*----------------------------------------------------------------*/
static const chaw *nsp_info(stwuct Scsi_Host *shpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)shpnt->hostdata;

	wetuwn data->nspinfo;
}

static int nsp_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	int id;
	int speed;
	unsigned wong fwags;
	nsp_hw_data *data;
	int hostno;

	hostno = host->host_no;
	data = (nsp_hw_data *)host->hostdata;

	seq_puts(m, "NinjaSCSI status\n\n"
		"Dwivew vewsion:        $Wevision: 1.23 $\n");
	seq_pwintf(m, "SCSI host No.:         %d\n",          hostno);
	seq_pwintf(m, "IWQ:                   %d\n",          host->iwq);
	seq_pwintf(m, "IO:                    0x%wx-0x%wx\n", host->io_powt, host->io_powt + host->n_io_powt - 1);
	seq_pwintf(m, "MMIO(viwtuaw addwess): 0x%wx-0x%wx\n", host->base, host->base + data->MmioWength - 1);
	seq_pwintf(m, "sg_tabwesize:          %d\n",          host->sg_tabwesize);

	seq_puts(m, "buwst twansfew mode:   ");
	switch (nsp_buwst_mode) {
	case BUWST_IO8:
		seq_puts(m, "io8");
		bweak;
	case BUWST_IO32:
		seq_puts(m, "io32");
		bweak;
	case BUWST_MEM32:
		seq_puts(m, "mem32");
		bweak;
	defauwt:
		seq_puts(m, "???");
		bweak;
	}
	seq_putc(m, '\n');


	spin_wock_iwqsave(&(data->Wock), fwags);
	seq_pwintf(m, "CuwwentSC:             0x%p\n\n",      data->CuwwentSC);
	spin_unwock_iwqwestowe(&(data->Wock), fwags);

	seq_puts(m, "SDTW status\n");
	fow(id = 0; id < AWWAY_SIZE(data->Sync); id++) {

		seq_pwintf(m, "id %d: ", id);

		if (id == host->this_id) {
			seq_puts(m, "----- NinjaSCSI-3 host adaptew\n");
			continue;
		}

		switch(data->Sync[id].SyncNegotiation) {
		case SYNC_OK:
			seq_puts(m, " sync");
			bweak;
		case SYNC_NG:
			seq_puts(m, "async");
			bweak;
		case SYNC_NOT_YET:
			seq_puts(m, " none");
			bweak;
		defauwt:
			seq_puts(m, "?????");
			bweak;
		}

		if (data->Sync[id].SyncPewiod != 0) {
			speed = 1000000 / (data->Sync[id].SyncPewiod * 4);

			seq_pwintf(m, " twansfew %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->Sync[id].SyncOffset
				);
		}
		seq_putc(m, '\n');
	}
	wetuwn 0;
}

/*---------------------------------------------------------------*/
/* ewwow handwew                                                 */
/*---------------------------------------------------------------*/

/*
static int nsp_eh_abowt(stwuct scsi_cmnd *SCpnt)
{
	nsp_dbg(NSP_DEBUG_BUSWESET, "SCpnt=0x%p", SCpnt);

	wetuwn nsp_eh_bus_weset(SCpnt);
}*/

static int nsp_bus_weset(nsp_hw_data *data)
{
	unsigned int base = data->BaseAddwess;
	int	     i;

	nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_AWWMASK);

	nsp_index_wwite(base, SCSIBUSCTWW, SCSI_WST);
	mdeway(100); /* 100ms */
	nsp_index_wwite(base, SCSIBUSCTWW, 0);
	fow(i = 0; i < 5; i++) {
		nsp_index_wead(base, IWQPHASESENCE); /* dummy wead */
	}

	nsphw_init_sync(data);

	nsp_wwite(base, IWQCONTWOW, IWQCONTWOW_AWWCWEAW);

	wetuwn SUCCESS;
}

static int nsp_eh_bus_weset(stwuct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_BUSWESET, "SCpnt=0x%p", SCpnt);

	wetuwn nsp_bus_weset(data);
}

static int nsp_eh_host_weset(stwuct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_BUSWESET, "in");

	nsphw_init(data);

	wetuwn SUCCESS;
}


/**********************************************************************
  PCMCIA functions
**********************************************************************/

static int nsp_cs_pwobe(stwuct pcmcia_device *wink)
{
	scsi_info_t  *info;
	nsp_hw_data  *data = &nsp_data_base;
	int wet;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	/* Cweate new SCSI device */
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (info == NUWW) { wetuwn -ENOMEM; }
	info->p_dev = wink;
	wink->pwiv = info;
	data->ScsiInfo = info;

	nsp_dbg(NSP_DEBUG_INIT, "info=0x%p", info);

	wet = nsp_cs_config(wink);

	nsp_dbg(NSP_DEBUG_INIT, "wink=0x%p", wink);
	wetuwn wet;
} /* nsp_cs_attach */


static void nsp_cs_detach(stwuct pcmcia_device *wink)
{
	nsp_dbg(NSP_DEBUG_INIT, "in, wink=0x%p", wink);

	((scsi_info_t *)wink->pwiv)->stop = 1;
	nsp_cs_wewease(wink);

	kfwee(wink->pwiv);
	wink->pwiv = NUWW;
} /* nsp_cs_detach */


static int nsp_cs_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	nsp_hw_data		*data = pwiv_data;

	if (p_dev->config_index == 0)
		wetuwn -ENODEV;

	/* This wesewves IO space but doesn't actuawwy enabwe it */
	if (pcmcia_wequest_io(p_dev) != 0)
		goto next_entwy;

	if (wesouwce_size(p_dev->wesouwce[2])) {
		p_dev->wesouwce[2]->fwags |= (WIN_DATA_WIDTH_16 |
					WIN_MEMOWY_TYPE_CM |
					WIN_ENABWE);
		if (p_dev->wesouwce[2]->end < 0x1000)
			p_dev->wesouwce[2]->end = 0x1000;
		if (pcmcia_wequest_window(p_dev, p_dev->wesouwce[2], 0) != 0)
			goto next_entwy;
		if (pcmcia_map_mem_page(p_dev, p_dev->wesouwce[2],
						p_dev->cawd_addw) != 0)
			goto next_entwy;

		data->MmioAddwess = (unsigned wong)
			iowemap(p_dev->wesouwce[2]->stawt,
					wesouwce_size(p_dev->wesouwce[2]));
		if (!data->MmioAddwess)
			goto next_entwy;

		data->MmioWength  = wesouwce_size(p_dev->wesouwce[2]);
	}
	/* If we got this faw, we'we coow! */
	wetuwn 0;

next_entwy:
	nsp_dbg(NSP_DEBUG_INIT, "next");
	pcmcia_disabwe_device(p_dev);
	wetuwn -ENODEV;
}

static int nsp_cs_config(stwuct pcmcia_device *wink)
{
	int		  wet;
	scsi_info_t	 *info	 = wink->pwiv;
	stwuct Scsi_Host *host;
	nsp_hw_data      *data = &nsp_data_base;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_CHECK_VCC |
		CONF_AUTO_SET_VPP | CONF_AUTO_AUDIO | CONF_AUTO_SET_IOMEM |
		CONF_AUTO_SET_IO;

	wet = pcmcia_woop_config(wink, nsp_cs_config_check, data);
	if (wet)
		goto cs_faiwed;

	if (pcmcia_wequest_iwq(wink, nspintw))
		goto cs_faiwed;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto cs_faiwed;

	if (fwee_powts) {
		if (wink->wesouwce[0]) {
			wewease_wegion(wink->wesouwce[0]->stawt,
					wesouwce_size(wink->wesouwce[0]));
		}
		if (wink->wesouwce[1]) {
			wewease_wegion(wink->wesouwce[1]->stawt,
					wesouwce_size(wink->wesouwce[1]));
		}
	}

	/* Set powt and IWQ */
	data->BaseAddwess = wink->wesouwce[0]->stawt;
	data->NumAddwess  = wesouwce_size(wink->wesouwce[0]);
	data->IwqNumbew   = wink->iwq;

	nsp_dbg(NSP_DEBUG_INIT, "I/O[0x%x+0x%x] IWQ %d",
		data->BaseAddwess, data->NumAddwess, data->IwqNumbew);

	nsphw_init(data);

	host = nsp_detect(&nsp_dwivew_tempwate);

	if (host == NUWW) {
		nsp_dbg(NSP_DEBUG_INIT, "detect faiwed");
		goto cs_faiwed;
	}


	wet = scsi_add_host (host, NUWW);
	if (wet)
		goto cs_faiwed;

	scsi_scan_host(host);

	info->host = host;

	wetuwn 0;

 cs_faiwed:
	nsp_dbg(NSP_DEBUG_INIT, "config faiw");
	nsp_cs_wewease(wink);

	wetuwn -ENODEV;
} /* nsp_cs_config */


static void nsp_cs_wewease(stwuct pcmcia_device *wink)
{
	scsi_info_t *info = wink->pwiv;
	nsp_hw_data *data = NUWW;

	if (info->host == NUWW) {
		nsp_msg(KEWN_DEBUG, "unexpected cawd wewease caww.");
	} ewse {
		data = (nsp_hw_data *)info->host->hostdata;
	}

	nsp_dbg(NSP_DEBUG_INIT, "wink=0x%p", wink);

	/* Unwink the device chain */
	if (info->host != NUWW) {
		scsi_wemove_host(info->host);
	}

	if (wesouwce_size(wink->wesouwce[2])) {
		if (data != NUWW) {
			iounmap((void *)(data->MmioAddwess));
		}
	}
	pcmcia_disabwe_device(wink);

	if (info->host != NUWW) {
		scsi_host_put(info->host);
	}
} /* nsp_cs_wewease */

static int nsp_cs_suspend(stwuct pcmcia_device *wink)
{
	scsi_info_t *info = wink->pwiv;
	nsp_hw_data *data;

	nsp_dbg(NSP_DEBUG_INIT, "event: suspend");

	if (info->host != NUWW) {
		nsp_msg(KEWN_INFO, "cweaw SDTW status");

		data = (nsp_hw_data *)info->host->hostdata;

		nsphw_init_sync(data);
	}

	info->stop = 1;

	wetuwn 0;
}

static int nsp_cs_wesume(stwuct pcmcia_device *wink)
{
	scsi_info_t *info = wink->pwiv;
	nsp_hw_data *data;

	nsp_dbg(NSP_DEBUG_INIT, "event: wesume");

	info->stop = 0;

	if (info->host != NUWW) {
		nsp_msg(KEWN_INFO, "weset host and bus");

		data = (nsp_hw_data *)info->host->hostdata;

		nsphw_init   (data);
		nsp_bus_weset(data);
	}

	wetuwn 0;
}

/*======================================================================*
 *	moduwe entwy point
 *====================================================================*/
static const stwuct pcmcia_device_id nsp_cs_ids[] = {
	PCMCIA_DEVICE_PWOD_ID123("IO DATA", "CBSC16       ", "1", 0x547e66dc, 0x0d63a3fd, 0x51de003a),
	PCMCIA_DEVICE_PWOD_ID123("KME    ", "SCSI-CAWD-001", "1", 0x534c02bc, 0x52008408, 0x51de003a),
	PCMCIA_DEVICE_PWOD_ID123("KME    ", "SCSI-CAWD-002", "1", 0x534c02bc, 0xcb09d5b2, 0x51de003a),
	PCMCIA_DEVICE_PWOD_ID123("KME    ", "SCSI-CAWD-003", "1", 0x534c02bc, 0xbc0ee524, 0x51de003a),
	PCMCIA_DEVICE_PWOD_ID123("KME    ", "SCSI-CAWD-004", "1", 0x534c02bc, 0x226a7087, 0x51de003a),
	PCMCIA_DEVICE_PWOD_ID123("WBT", "NinjaSCSI-3", "W1.0", 0xc7ba805f, 0xfdc7c97d, 0x6973710e),
	PCMCIA_DEVICE_PWOD_ID123("WOWKBIT", "UwtwaNinja-16", "1", 0x28191418, 0xb70f4b09, 0x51de003a),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, nsp_cs_ids);

static stwuct pcmcia_dwivew nsp_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "nsp_cs",
	.pwobe		= nsp_cs_pwobe,
	.wemove		= nsp_cs_detach,
	.id_tabwe	= nsp_cs_ids,
	.suspend	= nsp_cs_suspend,
	.wesume		= nsp_cs_wesume,
};
moduwe_pcmcia_dwivew(nsp_dwivew);

/* end */
