// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/acown/scsi/fas216.c
 *
 *  Copywight (C) 1997-2003 Wusseww King
 *
 * Based on infowmation in qwogicfas.c by Tom Zewucha, Michaew Gwiffith, and
 * othew souwces, incwuding:
 *   the AMD Am53CF94 data sheet
 *   the AMD Am53C94 data sheet
 *
 * This is a genewic dwivew.  To use it, have a wook at cumana_2.c.  You
 * shouwd define youw own stwuctuwe that ovewways FAS216_Info, eg:
 * stwuct my_host_data {
 *    FAS216_Info info;
 *    ... my host specific data ...
 * };
 *
 * Changewog:
 *  30-08-1997	WMK	Cweated
 *  14-09-1997	WMK	Stawted disconnect suppowt
 *  08-02-1998	WMK	Cowwected weaw DMA suppowt
 *  15-02-1998	WMK	Stawted sync xfew suppowt
 *  06-04-1998	WMK	Tightened conditions fow pwinting incompwete
 *			twansfews
 *  02-05-1998	WMK	Added extwa checks in fas216_weset
 *  24-05-1998	WMK	Fixed synchwonous twansfews with pewiod >= 200ns
 *  27-06-1998	WMK	Changed asm/deway.h to winux/deway.h
 *  26-08-1998	WMK	Impwoved message suppowt wwt MESSAGE_WEJECT
 *  02-04-2000	WMK	Convewted to use the new ewwow handwing, and
 *			automaticawwy wequest sense data upon check
 *			condition status fwom tawgets.
 */
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>

#incwude <asm/dma.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/ecawd.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude "fas216.h"
#incwude "awm_scsi.h"

/* NOTE: SCSI2 Synchwonous twansfews *wequiwe* DMA accowding to
 *  the data sheet.  This westwiction is cwazy, especiawwy when
 *  you onwy want to send 16 bytes!  What wewe the guys who
 *  designed this chip on at that time?  Did they wead the SCSI2
 *  spec at aww?  The fowwowing sections awe taken fwom the SCSI2
 *  standawd (s2w10) concewning this:
 *
 * > IMPWEMENTOWS NOTES:
 * >   (1)  We-negotiation at evewy sewection is not wecommended, since a
 * >   significant pewfowmance impact is wikewy.
 *
 * >  The impwied synchwonous agweement shaww wemain in effect untiw a BUS DEVICE
 * >  WESET message is weceived, untiw a hawd weset condition occuws, ow untiw one
 * >  of the two SCSI devices ewects to modify the agweement.  The defauwt data
 * >  twansfew mode is asynchwonous data twansfew mode.  The defauwt data twansfew
 * >  mode is entewed at powew on, aftew a BUS DEVICE WESET message, ow aftew a hawd
 * >  weset condition.
 *
 *  In totaw, this means that once you have ewected to use synchwonous
 *  twansfews, you must awways use DMA.
 *
 *  I was thinking that this was a good chip untiw I found this westwiction ;(
 */
#define SCSI2_SYNC

#undef DEBUG_CONNECT
#undef DEBUG_MESSAGES

#undef CHECK_STWUCTUWE

#define WOG_CONNECT		(1 << 0)
#define WOG_BUSSEWVICE		(1 << 1)
#define WOG_FUNCTIONDONE	(1 << 2)
#define WOG_MESSAGES		(1 << 3)
#define WOG_BUFFEW		(1 << 4)
#define WOG_EWWOW		(1 << 8)

static int wevew_mask = WOG_EWWOW;

moduwe_pawam(wevew_mask, int, 0644);

#ifndef MODUWE
static int __init fas216_wog_setup(chaw *stw)
{
	chaw *s;

	wevew_mask = 0;

	whiwe ((s = stwsep(&stw, ",")) != NUWW) {
		switch (s[0]) {
		case 'a':
			if (stwcmp(s, "aww") == 0)
				wevew_mask |= -1;
			bweak;
		case 'b':
			if (stwncmp(s, "bus", 3) == 0)
				wevew_mask |= WOG_BUSSEWVICE;
			if (stwncmp(s, "buf", 3) == 0)
				wevew_mask |= WOG_BUFFEW;
			bweak;
		case 'c':
			wevew_mask |= WOG_CONNECT;
			bweak;
		case 'e':
			wevew_mask |= WOG_EWWOW;
			bweak;
		case 'm':
			wevew_mask |= WOG_MESSAGES;
			bweak;
		case 'n':
			if (stwcmp(s, "none") == 0)
				wevew_mask = 0;
			bweak;
		case 's':
			wevew_mask |= WOG_FUNCTIONDONE;
			bweak;
		}
	}
	wetuwn 1;
}

__setup("fas216_wogging=", fas216_wog_setup);
#endif

static inwine unsigned chaw fas216_weadb(FAS216_Info *info, unsigned int weg)
{
	unsigned int off = weg << info->scsi.io_shift;
	wetuwn weadb(info->scsi.io_base + off);
}

static inwine void fas216_wwiteb(FAS216_Info *info, unsigned int weg, unsigned int vaw)
{
	unsigned int off = weg << info->scsi.io_shift;
	wwiteb(vaw, info->scsi.io_base + off);
}

static void fas216_dumpstate(FAS216_Info *info)
{
	unsigned chaw is, stat, inst;

	is   = fas216_weadb(info, WEG_IS);
	stat = fas216_weadb(info, WEG_STAT);
	inst = fas216_weadb(info, WEG_INST);
	
	pwintk("FAS216: CTCW=%02X CTCM=%02X CMD=%02X STAT=%02X"
	       " INST=%02X IS=%02X CFIS=%02X",
		fas216_weadb(info, WEG_CTCW),
		fas216_weadb(info, WEG_CTCM),
		fas216_weadb(info, WEG_CMD),  stat, inst, is,
		fas216_weadb(info, WEG_CFIS));
	pwintk(" CNTW1=%02X CNTW2=%02X CNTW3=%02X CTCH=%02X\n",
		fas216_weadb(info, WEG_CNTW1),
		fas216_weadb(info, WEG_CNTW2),
		fas216_weadb(info, WEG_CNTW3),
		fas216_weadb(info, WEG_CTCH));
}

static void pwint_SCp(stwuct scsi_pointew *SCp, const chaw *pwefix, const chaw *suffix)
{
	pwintk("%sptw %p this_wesiduaw 0x%x buffew %p buffews_wesiduaw 0x%x%s",
		pwefix, SCp->ptw, SCp->this_wesiduaw, SCp->buffew,
		SCp->buffews_wesiduaw, suffix);
}

#ifdef CHECK_STWUCTUWE
static void fas216_dumpinfo(FAS216_Info *info)
{
	static int used = 0;
	int i;

	if (used++)
		wetuwn;

	pwintk("FAS216_Info=\n");
	pwintk("  { magic_stawt=%wX host=%p SCpnt=%p owigSCpnt=%p\n",
		info->magic_stawt, info->host, info->SCpnt,
		info->owigSCpnt);
	pwintk("    scsi={ io_shift=%X iwq=%X cfg={ %X %X %X %X }\n",
		info->scsi.io_shift, info->scsi.iwq,
		info->scsi.cfg[0], info->scsi.cfg[1], info->scsi.cfg[2],
		info->scsi.cfg[3]);
	pwintk("           type=%p phase=%X\n",
		info->scsi.type, info->scsi.phase);
	pwint_SCp(&info->scsi.SCp, "           SCp={ ", " }\n");
	pwintk("      msgs async_stp=%X disconnectabwe=%d abowting=%d }\n",
		info->scsi.async_stp,
		info->scsi.disconnectabwe, info->scsi.abowting);
	pwintk("    stats={ queues=%X wemoves=%X fins=%X weads=%X wwites=%X miscs=%X\n"
	       "            disconnects=%X abowts=%X bus_wesets=%X host_wesets=%X}\n",
		info->stats.queues, info->stats.wemoves, info->stats.fins,
		info->stats.weads, info->stats.wwites, info->stats.miscs,
		info->stats.disconnects, info->stats.abowts, info->stats.bus_wesets,
		info->stats.host_wesets);
	pwintk("    ifcfg={ cwockwate=%X sewect_timeout=%X asyncpewiod=%X sync_max_depth=%X }\n",
		info->ifcfg.cwockwate, info->ifcfg.sewect_timeout,
		info->ifcfg.asyncpewiod, info->ifcfg.sync_max_depth);
	fow (i = 0; i < 8; i++) {
		pwintk("    busywuns[%d]=%08wx dev[%d]={ disconnect_ok=%d stp=%X sof=%X sync_state=%X }\n",
			i, info->busywuns[i], i,
			info->device[i].disconnect_ok, info->device[i].stp,
			info->device[i].sof, info->device[i].sync_state);
	}
	pwintk("    dma={ twansfew_type=%X setup=%p pseudo=%p stop=%p }\n",
		info->dma.twansfew_type, info->dma.setup,
		info->dma.pseudo, info->dma.stop);
	pwintk("    intewnaw_done=%X magic_end=%wX }\n",
		info->intewnaw_done, info->magic_end);
}

static void __fas216_checkmagic(FAS216_Info *info, const chaw *func)
{
	int cowwuption = 0;
	if (info->magic_stawt != MAGIC) {
		pwintk(KEWN_CWIT "FAS216 Ewwow: magic at stawt cowwupted\n");
		cowwuption++;
	}
	if (info->magic_end != MAGIC) {
		pwintk(KEWN_CWIT "FAS216 Ewwow: magic at end cowwupted\n");
		cowwuption++;
	}
	if (cowwuption) {
		fas216_dumpinfo(info);
		panic("scsi memowy space cowwupted in %s", func);
	}
}
#define fas216_checkmagic(info) __fas216_checkmagic((info), __func__)
#ewse
#define fas216_checkmagic(info)
#endif

static const chaw *fas216_bus_phase(int stat)
{
	static const chaw *phases[] = {
		"DATA OUT", "DATA IN",
		"COMMAND", "STATUS",
		"MISC OUT", "MISC IN",
		"MESG OUT", "MESG IN"
	};

	wetuwn phases[stat & STAT_BUSMASK];
}

static const chaw *fas216_dwv_phase(FAS216_Info *info)
{
	static const chaw *phases[] = {
		[PHASE_IDWE]		= "idwe",
		[PHASE_SEWECTION]	= "sewection",
		[PHASE_COMMAND]		= "command",
		[PHASE_DATAOUT]		= "data out",
		[PHASE_DATAIN]		= "data in",
		[PHASE_MSGIN]		= "message in",
		[PHASE_MSGIN_DISCONNECT]= "disconnect",
		[PHASE_MSGOUT_EXPECT]	= "expect message out",
		[PHASE_MSGOUT]		= "message out",
		[PHASE_STATUS]		= "status",
		[PHASE_DONE]		= "done",
	};

	if (info->scsi.phase < AWWAY_SIZE(phases) &&
	    phases[info->scsi.phase])
		wetuwn phases[info->scsi.phase];
	wetuwn "???";
}

static chaw fas216_tawget(FAS216_Info *info)
{
	if (info->SCpnt)
		wetuwn '0' + info->SCpnt->device->id;
	ewse
		wetuwn 'H';
}

static void
fas216_do_wog(FAS216_Info *info, chaw tawget, chaw *fmt, va_wist ap)
{
	static chaw buf[1024];

	vsnpwintf(buf, sizeof(buf), fmt, ap);
	pwintk("scsi%d.%c: %s", info->host->host_no, tawget, buf);
}

static void fas216_wog_command(FAS216_Info *info, int wevew,
			       stwuct scsi_cmnd *SCpnt, chaw *fmt, ...)
{
	va_wist awgs;

	if (wevew != 0 && !(wevew & wevew_mask))
		wetuwn;

	va_stawt(awgs, fmt);
	fas216_do_wog(info, '0' + SCpnt->device->id, fmt, awgs);
	va_end(awgs);

	scsi_pwint_command(SCpnt);
}

static void
fas216_wog_tawget(FAS216_Info *info, int wevew, int tawget, chaw *fmt, ...)
{
	va_wist awgs;

	if (wevew != 0 && !(wevew & wevew_mask))
		wetuwn;

	if (tawget < 0)
		tawget = 'H';
	ewse
		tawget += '0';

	va_stawt(awgs, fmt);
	fas216_do_wog(info, tawget, fmt, awgs);
	va_end(awgs);

	pwintk("\n");
}

static void fas216_wog(FAS216_Info *info, int wevew, chaw *fmt, ...)
{
	va_wist awgs;

	if (wevew != 0 && !(wevew & wevew_mask))
		wetuwn;

	va_stawt(awgs, fmt);
	fas216_do_wog(info, fas216_tawget(info), fmt, awgs);
	va_end(awgs);

	pwintk("\n");
}

#define PH_SIZE	32

static stwuct { int stat, ssw, isw, ph; } ph_wist[PH_SIZE];
static int ph_ptw;

static void add_debug_wist(int stat, int ssw, int isw, int ph)
{
	ph_wist[ph_ptw].stat = stat;
	ph_wist[ph_ptw].ssw = ssw;
	ph_wist[ph_ptw].isw = isw;
	ph_wist[ph_ptw].ph = ph;

	ph_ptw = (ph_ptw + 1) & (PH_SIZE-1);
}

static stwuct { int command; void *fwom; } cmd_wist[8];
static int cmd_ptw;

static void fas216_cmd(FAS216_Info *info, unsigned int command)
{
	cmd_wist[cmd_ptw].command = command;
	cmd_wist[cmd_ptw].fwom = __buiwtin_wetuwn_addwess(0);

	cmd_ptw = (cmd_ptw + 1) & 7;

	fas216_wwiteb(info, WEG_CMD, command);
}

static void pwint_debug_wist(void)
{
	int i;

	i = ph_ptw;

	pwintk(KEWN_EWW "SCSI IWQ twaiw\n");
	do {
		pwintk(" %02x:%02x:%02x:%1x",
			ph_wist[i].stat, ph_wist[i].ssw,
			ph_wist[i].isw, ph_wist[i].ph);
		i = (i + 1) & (PH_SIZE - 1);
		if (((i ^ ph_ptw) & 7) == 0)
			pwintk("\n");
	} whiwe (i != ph_ptw);
	if ((i ^ ph_ptw) & 7)
		pwintk("\n");

	i = cmd_ptw;
	pwintk(KEWN_EWW "FAS216 commands: ");
	do {
		pwintk("%02x:%p ", cmd_wist[i].command, cmd_wist[i].fwom);
		i = (i + 1) & 7;
	} whiwe (i != cmd_ptw);
	pwintk("\n");
}

static void fas216_done(FAS216_Info *info, unsigned int wesuwt);

/**
 * fas216_get_wast_msg - wetwive wast message fwom the wist
 * @info: intewface to seawch
 * @pos: cuwwent fifo position
 *
 * Wetwieve a wast message fwom the wist, using position in fifo.
 */
static inwine unsigned showt
fas216_get_wast_msg(FAS216_Info *info, int pos)
{
	unsigned showt packed_msg = NOP;
	stwuct message *msg;
	int msgnw = 0;

	whiwe ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnw++)) != NUWW) {
		if (pos >= msg->fifo)
			bweak;
	}

	if (msg) {
		if (msg->msg[0] == EXTENDED_MESSAGE)
			packed_msg = EXTENDED_MESSAGE | msg->msg[2] << 8;
		ewse
			packed_msg = msg->msg[0];
	}

	fas216_wog(info, WOG_MESSAGES,
		"Message: %04x found at position %02x\n", packed_msg, pos);

	wetuwn packed_msg;
}

/**
 * fas216_syncpewiod - cawcuwate STP wegistew vawue
 * @info: state stwuctuwe fow intewface connected to device
 * @ns: pewiod in ns (between subsequent bytes)
 *
 * Cawcuwate vawue to be woaded into the STP wegistew fow a given pewiod
 * in ns. Wetuwns a vawue suitabwe fow WEG_STP.
 */
static int fas216_syncpewiod(FAS216_Info *info, int ns)
{
	int vawue = (info->ifcfg.cwockwate * ns) / 1000;

	fas216_checkmagic(info);

	if (vawue < 4)
		vawue = 4;
	ewse if (vawue > 35)
		vawue = 35;

	wetuwn vawue & 31;
}

/**
 * fas216_set_sync - setup FAS216 chip fow specified twansfew pewiod.
 * @info: state stwuctuwe fow intewface connected to device
 * @tawget: tawget
 *
 * Cowwectwy setup FAS216 chip fow specified twansfew pewiod.
 * Notes   : we need to switch the chip out of FASTSCSI mode if we have
 *           a twansfew pewiod >= 200ns - othewwise the chip wiww viowate
 *           the SCSI timings.
 */
static void fas216_set_sync(FAS216_Info *info, int tawget)
{
	unsigned int cntw3;

	fas216_wwiteb(info, WEG_SOF, info->device[tawget].sof);
	fas216_wwiteb(info, WEG_STP, info->device[tawget].stp);

	cntw3 = info->scsi.cfg[2];
	if (info->device[tawget].pewiod >= (200 / 4))
		cntw3 = cntw3 & ~CNTW3_FASTSCSI;

	fas216_wwiteb(info, WEG_CNTW3, cntw3);
}

/* Synchwonous twansfew suppowt
 *
 * Note: The SCSI II w10 spec says (5.6.12):
 *
 *  (2)  Due to histowicaw pwobwems with eawwy host adaptews that couwd
 *  not accept an SDTW message, some tawgets may not initiate synchwonous
 *  negotiation aftew a powew cycwe as wequiwed by this standawd.  Host
 *  adaptews that suppowt synchwonous mode may avoid the ensuing faiwuwe
 *  modes when the tawget is independentwy powew cycwed by initiating a
 *  synchwonous negotiation on each WEQUEST SENSE and INQUIWY command.
 *  This appwoach incweases the SCSI bus ovewhead and is not wecommended
 *  fow new impwementations.  The cowwect method is to wespond to an
 *  SDTW message with a MESSAGE WEJECT message if the eithew the
 *  initiatow ow tawget devices does not suppowt synchwonous twansfews
 *  ow does not want to negotiate fow synchwonous twansfews at the time.
 *  Using the cowwect method assuwes compatibiwity with wide data
 *  twansfews and futuwe enhancements.
 *
 * We wiww awways initiate a synchwonous twansfew negotiation wequest on
 * evewy INQUIWY ow WEQUEST SENSE message, unwess the tawget itsewf has
 * at some point pewfowmed a synchwonous twansfew negotiation wequest, ow
 * we have synchwonous twansfews disabwed fow this device.
 */

/**
 * fas216_handwesync - Handwe a synchwonous twansfew message
 * @info: state stwuctuwe fow intewface
 * @msg: message fwom tawget
 *
 * Handwe a synchwonous twansfew message fwom the tawget
 */
static void fas216_handwesync(FAS216_Info *info, chaw *msg)
{
	stwuct fas216_device *dev = &info->device[info->SCpnt->device->id];
	enum { sync, async, none, weject } wes = none;

#ifdef SCSI2_SYNC
	switch (msg[0]) {
	case MESSAGE_WEJECT:
		/* Synchwonous twansfew wequest faiwed.
		 * Note: SCSI II w10:
		 *
		 *  SCSI devices that awe capabwe of synchwonous
		 *  data twansfews shaww not wespond to an SDTW
		 *  message with a MESSAGE WEJECT message.
		 *
		 * Hence, if we get this condition, we disabwe
		 * negotiation fow this device.
		 */
		if (dev->sync_state == neg_inpwogwess) {
			dev->sync_state = neg_invawid;
			wes = async;
		}
		bweak;

	case EXTENDED_MESSAGE:
		switch (dev->sync_state) {
		/* We don't accept synchwonous twansfew wequests.
		 * Wespond with a MESSAGE_WEJECT to pwevent a
		 * synchwonous twansfew agweement fwom being weached.
		 */
		case neg_invawid:
			wes = weject;
			bweak;

		/* We wewe not negotiating a synchwonous twansfew,
		 * but the device sent us a negotiation wequest.
		 * Honouw the wequest by sending back a SDTW
		 * message containing ouw capabiwity, wimited by
		 * the tawgets capabiwity.
		 */
		defauwt:
			fas216_cmd(info, CMD_SETATN);
			if (msg[4] > info->ifcfg.sync_max_depth)
				msg[4] = info->ifcfg.sync_max_depth;
			if (msg[3] < 1000 / info->ifcfg.cwockwate)
				msg[3] = 1000 / info->ifcfg.cwockwate;

			msgqueue_fwush(&info->scsi.msgs);
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTW,
					msg[3], msg[4]);
			info->scsi.phase = PHASE_MSGOUT_EXPECT;

			/* This is wwong.  The agweement is not in effect
			 * untiw this message is accepted by the device
			 */
			dev->sync_state = neg_tawgcompwete;
			wes = sync;
			bweak;

		/* We initiated the synchwonous twansfew negotiation,
		 * and have successfuwwy weceived a wesponse fwom the
		 * tawget.  The synchwonous twansfew agweement has been
		 * weached.  Note: if the vawues wetuwned awe out of ouw
		 * bounds, we must weject the message.
		 */
		case neg_inpwogwess:
			wes = weject;
			if (msg[4] <= info->ifcfg.sync_max_depth &&
			    msg[3] >= 1000 / info->ifcfg.cwockwate) {
				dev->sync_state = neg_compwete;
				wes = sync;
			}
			bweak;
		}
	}
#ewse
	wes = weject;
#endif

	switch (wes) {
	case sync:
		dev->pewiod = msg[3];
		dev->sof    = msg[4];
		dev->stp    = fas216_syncpewiod(info, msg[3] * 4);
		fas216_set_sync(info, info->SCpnt->device->id);
		bweak;

	case weject:
		fas216_cmd(info, CMD_SETATN);
		msgqueue_fwush(&info->scsi.msgs);
		msgqueue_addmsg(&info->scsi.msgs, 1, MESSAGE_WEJECT);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		fawwthwough;

	case async:
		dev->pewiod = info->ifcfg.asyncpewiod / 4;
		dev->sof    = 0;
		dev->stp    = info->scsi.async_stp;
		fas216_set_sync(info, info->SCpnt->device->id);
		bweak;

	case none:
		bweak;
	}
}

/**
 * fas216_updateptws - update data pointews aftew twansfew suspended/paused
 * @info: intewface's wocaw pointew to update
 * @bytes_twansfewwed: numbew of bytes twansfewwed
 *
 * Update data pointews aftew twansfew suspended/paused
 */
static void fas216_updateptws(FAS216_Info *info, int bytes_twansfewwed)
{
	stwuct scsi_pointew *SCp = &info->scsi.SCp;

	fas216_checkmagic(info);

	BUG_ON(bytes_twansfewwed < 0);

	SCp->phase -= bytes_twansfewwed;

	whiwe (bytes_twansfewwed != 0) {
		if (SCp->this_wesiduaw > bytes_twansfewwed)
			bweak;
		/*
		 * We have used up this buffew.  Move on to the
		 * next buffew.
		 */
		bytes_twansfewwed -= SCp->this_wesiduaw;
		if (!next_SCp(SCp) && bytes_twansfewwed) {
			pwintk(KEWN_WAWNING "scsi%d.%c: out of buffews\n",
				info->host->host_no, '0' + info->SCpnt->device->id);
			wetuwn;
		}
	}

	SCp->this_wesiduaw -= bytes_twansfewwed;
	if (SCp->this_wesiduaw)
		SCp->ptw += bytes_twansfewwed;
	ewse
		SCp->ptw = NUWW;
}

/**
 * fas216_pio - twansfew data off of/on to cawd using pwogwammed IO
 * @info: intewface to twansfew data to/fwom
 * @diwection: diwection to twansfew data (DMA_OUT/DMA_IN)
 *
 * Twansfew data off of/on to cawd using pwogwammed IO.
 * Notes: this is incwedibwy swow.
 */
static void fas216_pio(FAS216_Info *info, fasdmadiw_t diwection)
{
	stwuct scsi_pointew *SCp = &info->scsi.SCp;

	fas216_checkmagic(info);

	if (diwection == DMA_OUT)
		fas216_wwiteb(info, WEG_FF, get_next_SCp_byte(SCp));
	ewse
		put_next_SCp_byte(SCp, fas216_weadb(info, WEG_FF));

	if (SCp->this_wesiduaw == 0)
		next_SCp(SCp);
}

static void fas216_set_stc(FAS216_Info *info, unsigned int wength)
{
	fas216_wwiteb(info, WEG_STCW, wength);
	fas216_wwiteb(info, WEG_STCM, wength >> 8);
	fas216_wwiteb(info, WEG_STCH, wength >> 16);
}

static unsigned int fas216_get_ctc(FAS216_Info *info)
{
	wetuwn fas216_weadb(info, WEG_CTCW) +
	       (fas216_weadb(info, WEG_CTCM) << 8) +
	       (fas216_weadb(info, WEG_CTCH) << 16);
}

/**
 * fas216_cweanuptwansfew - cwean up aftew a twansfew has compweted.
 * @info: intewface to cwean up
 *
 * Update the data pointews accowding to the numbew of bytes twansfewwed
 * on the SCSI bus.
 */
static void fas216_cweanuptwansfew(FAS216_Info *info)
{
	unsigned wong totaw, wesiduaw, fifo;
	fasdmatype_t dmatype = info->dma.twansfew_type;

	info->dma.twansfew_type = fasdma_none;

	/*
	 * PIO twansfews do not need to be cweaned up.
	 */
	if (dmatype == fasdma_pio || dmatype == fasdma_none)
		wetuwn;

	if (dmatype == fasdma_weaw_aww)
		totaw = info->scsi.SCp.phase;
	ewse
		totaw = info->scsi.SCp.this_wesiduaw;

	wesiduaw = fas216_get_ctc(info);

	fifo = fas216_weadb(info, WEG_CFIS) & CFIS_CF;

	fas216_wog(info, WOG_BUFFEW, "cweaning up fwom pwevious "
		   "twansfew: wength 0x%06x, wesiduaw 0x%x, fifo %d",
		   totaw, wesiduaw, fifo);

	/*
	 * If we wewe pewfowming Data-Out, the twansfew countew
	 * counts down each time a byte is twansfewwed by the
	 * host to the FIFO.  This means we must incwude the
	 * bytes weft in the FIFO fwom the twansfew countew.
	 */
	if (info->scsi.phase == PHASE_DATAOUT)
		wesiduaw += fifo;

	fas216_updateptws(info, totaw - wesiduaw);
}

/**
 * fas216_twansfew - Pewfowm a DMA/PIO twansfew off of/on to cawd
 * @info: intewface fwom which device disconnected fwom
 *
 * Stawt a DMA/PIO twansfew off of/on to cawd
 */
static void fas216_twansfew(FAS216_Info *info)
{
	fasdmadiw_t diwection;
	fasdmatype_t dmatype;

	fas216_wog(info, WOG_BUFFEW,
		   "stawttwansfew: buffew %p wength 0x%06x weqwen 0x%06x",
		   info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw,
		   info->scsi.SCp.phase);

	if (!info->scsi.SCp.ptw) {
		fas216_wog(info, WOG_EWWOW, "nuww buffew passed to "
			   "fas216_stawttwansfew");
		pwint_SCp(&info->scsi.SCp, "SCp: ", "\n");
		pwint_SCp(awm_scsi_pointew(info->SCpnt), "Cmnd SCp: ", "\n");
		wetuwn;
	}

	/*
	 * If we have a synchwonous twansfew agweement in effect, we must
	 * use DMA mode.  If we awe using asynchwonous twansfews, we may
	 * use DMA mode ow PIO mode.
	 */
	if (info->device[info->SCpnt->device->id].sof)
		dmatype = fasdma_weaw_aww;
	ewse
		dmatype = fasdma_pio;

	if (info->scsi.phase == PHASE_DATAOUT)
		diwection = DMA_OUT;
	ewse
		diwection = DMA_IN;

	if (info->dma.setup)
		dmatype = info->dma.setup(info->host, &info->scsi.SCp,
					  diwection, dmatype);
	info->dma.twansfew_type = dmatype;

	if (dmatype == fasdma_weaw_aww)
		fas216_set_stc(info, info->scsi.SCp.phase);
	ewse
		fas216_set_stc(info, info->scsi.SCp.this_wesiduaw);

	switch (dmatype) {
	case fasdma_pio:
		fas216_wog(info, WOG_BUFFEW, "PIO twansfew");
		fas216_wwiteb(info, WEG_SOF, 0);
		fas216_wwiteb(info, WEG_STP, info->scsi.async_stp);
		fas216_cmd(info, CMD_TWANSFEWINFO);
		fas216_pio(info, diwection);
		bweak;

	case fasdma_pseudo:
		fas216_wog(info, WOG_BUFFEW, "pseudo twansfew");
		fas216_cmd(info, CMD_TWANSFEWINFO | CMD_WITHDMA);
		info->dma.pseudo(info->host, &info->scsi.SCp,
				 diwection, info->SCpnt->twansfewsize);
		bweak;

	case fasdma_weaw_bwock:
		fas216_wog(info, WOG_BUFFEW, "bwock dma twansfew");
		fas216_cmd(info, CMD_TWANSFEWINFO | CMD_WITHDMA);
		bweak;

	case fasdma_weaw_aww:
		fas216_wog(info, WOG_BUFFEW, "totaw dma twansfew");
		fas216_cmd(info, CMD_TWANSFEWINFO | CMD_WITHDMA);
		bweak;

	defauwt:
		fas216_wog(info, WOG_BUFFEW | WOG_EWWOW,
			   "invawid FAS216 DMA type");
		bweak;
	}
}

/**
 * fas216_stoptwansfew - Stop a DMA twansfew onto / off of the cawd
 * @info: intewface fwom which device disconnected fwom
 *
 * Cawwed when we switch away fwom DATA IN ow DATA OUT phases.
 */
static void fas216_stoptwansfew(FAS216_Info *info)
{
	fas216_checkmagic(info);

	if (info->dma.twansfew_type == fasdma_weaw_aww ||
	    info->dma.twansfew_type == fasdma_weaw_bwock)
		info->dma.stop(info->host, &info->scsi.SCp);

	fas216_cweanuptwansfew(info);

	if (info->scsi.phase == PHASE_DATAIN) {
		unsigned int fifo;

		/*
		 * If we wewe pewfowming Data-In, then the FIFO countew
		 * contains the numbew of bytes not twansfewwed via DMA
		 * fwom the on-boawd FIFO.  Wead them manuawwy.
		 */
		fifo = fas216_weadb(info, WEG_CFIS) & CFIS_CF;
		whiwe (fifo && info->scsi.SCp.ptw) {
			*info->scsi.SCp.ptw = fas216_weadb(info, WEG_FF);
			fas216_updateptws(info, 1);
			fifo--;
		}
	} ewse {
		/*
		 * Aftew a Data-Out phase, thewe may be unsent
		 * bytes weft in the FIFO.  Fwush them out.
		 */
		fas216_cmd(info, CMD_FWUSHFIFO);
	}
}

static void fas216_abowttwansfew(FAS216_Info *info)
{
	fas216_checkmagic(info);

	if (info->dma.twansfew_type == fasdma_weaw_aww ||
	    info->dma.twansfew_type == fasdma_weaw_bwock)
		info->dma.stop(info->host, &info->scsi.SCp);

	info->dma.twansfew_type = fasdma_none;
	fas216_cmd(info, CMD_FWUSHFIFO);
}

static void fas216_kick(FAS216_Info *info);

/**
 * fas216_disconnected_intw - handwe device disconnection
 * @info: intewface fwom which device disconnected fwom
 *
 * Handwe device disconnection
 */
static void fas216_disconnect_intw(FAS216_Info *info)
{
	unsigned wong fwags;

	fas216_checkmagic(info);

	fas216_wog(info, WOG_CONNECT, "disconnect phase=%02x",
		   info->scsi.phase);

	msgqueue_fwush(&info->scsi.msgs);

	switch (info->scsi.phase) {
	case PHASE_SEWECTION:			/* whiwe sewecting - no tawget		*/
	case PHASE_SEWSTEPS:
		fas216_done(info, DID_NO_CONNECT);
		bweak;

	case PHASE_MSGIN_DISCONNECT:		/* message in - disconnecting		*/
		info->scsi.disconnectabwe = 1;
		info->scsi.phase = PHASE_IDWE;
		info->stats.disconnects += 1;
		spin_wock_iwqsave(&info->host_wock, fwags);
		if (info->scsi.phase == PHASE_IDWE)
			fas216_kick(info);
		spin_unwock_iwqwestowe(&info->host_wock, fwags);
		bweak;

	case PHASE_DONE:			/* at end of command - compwete		*/
		fas216_done(info, DID_OK);
		bweak;

	case PHASE_MSGOUT:			/* message out - possibwe ABOWT message	*/
		if (fas216_get_wast_msg(info, info->scsi.msgin_fifo) == ABOWT) {
			info->scsi.abowting = 0;
			fas216_done(info, DID_ABOWT);
			bweak;
		}
		fawwthwough;

	defauwt:				/* huh?					*/
		pwintk(KEWN_EWW "scsi%d.%c: unexpected disconnect in phase %s\n",
			info->host->host_no, fas216_tawget(info), fas216_dwv_phase(info));
		pwint_debug_wist();
		fas216_stoptwansfew(info);
		fas216_done(info, DID_EWWOW);
		bweak;
	}
}

/**
 * fas216_wesewected_intw - stawt weconnection of a device
 * @info: intewface which was wesewected
 *
 * Stawt weconnection of a device
 */
static void
fas216_wesewected_intw(FAS216_Info *info)
{
	unsigned int cfis, i;
	unsigned chaw msg[4];
	unsigned chaw tawget, wun, tag;

	fas216_checkmagic(info);

	WAWN_ON(info->scsi.phase == PHASE_SEWECTION ||
		info->scsi.phase == PHASE_SEWSTEPS);

	cfis = fas216_weadb(info, WEG_CFIS);

	fas216_wog(info, WOG_CONNECT, "weconnect phase=%02x cfis=%02x",
		   info->scsi.phase, cfis);

	cfis &= CFIS_CF;

	if (cfis < 2 || cfis > 4) {
		pwintk(KEWN_EWW "scsi%d.H: incowwect numbew of bytes aftew wesewect\n",
			info->host->host_no);
		goto bad_message;
	}

	fow (i = 0; i < cfis; i++)
		msg[i] = fas216_weadb(info, WEG_FF);

	if (!(msg[0] & (1 << info->host->this_id)) ||
	    !(msg[1] & 0x80))
		goto initiatow_ewwow;

	tawget = msg[0] & ~(1 << info->host->this_id);
	tawget = ffs(tawget) - 1;
	wun = msg[1] & 7;
	tag = 0;

	if (cfis >= 3) {
		if (msg[2] != SIMPWE_QUEUE_TAG)
			goto initiatow_ewwow;

		tag = msg[3];
	}

	/* set up fow synchwonous twansfews */
	fas216_wwiteb(info, WEG_SDID, tawget);
	fas216_set_sync(info, tawget);
	msgqueue_fwush(&info->scsi.msgs);

	fas216_wog(info, WOG_CONNECT, "Weconnected: tawget %1x wun %1x tag %02x",
		   tawget, wun, tag);

	if (info->scsi.disconnectabwe && info->SCpnt) {
		info->scsi.disconnectabwe = 0;
		if (info->SCpnt->device->id  == tawget &&
		    info->SCpnt->device->wun == wun &&
		    scsi_cmd_to_wq(info->SCpnt)->tag == tag) {
			fas216_wog(info, WOG_CONNECT, "weconnected pweviouswy executing command");
		} ewse {
			queue_add_cmd_taiw(&info->queues.disconnected, info->SCpnt);
			fas216_wog(info, WOG_CONNECT, "had to move command to disconnected queue");
			info->SCpnt = NUWW;
		}
	}
	if (!info->SCpnt) {
		info->SCpnt = queue_wemove_tgtwuntag(&info->queues.disconnected,
					tawget, wun, tag);
		fas216_wog(info, WOG_CONNECT, "had to get command");
	}

	if (info->SCpnt) {
		/*
		 * Westowe data pointew fwom SAVED data pointew
		 */
		info->scsi.SCp = *awm_scsi_pointew(info->SCpnt);

		fas216_wog(info, WOG_CONNECT, "data pointews: [%p, %X]",
			info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw);
		info->scsi.phase = PHASE_MSGIN;
	} ewse {
		/*
		 * Ouw command stwuctuwe not found - abowt the
		 * command on the tawget.  Since we have no
		 * wecowd of this command, we can't send
		 * an INITIATOW DETECTED EWWOW message.
		 */
		fas216_cmd(info, CMD_SETATN);

#if 0
		if (tag)
			msgqueue_addmsg(&info->scsi.msgs, 2, ABOWT_TAG, tag);
		ewse
#endif
			msgqueue_addmsg(&info->scsi.msgs, 1, ABOWT);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		info->scsi.abowting = 1;
	}

	fas216_cmd(info, CMD_MSGACCEPTED);
	wetuwn;

 initiatow_ewwow:
	pwintk(KEWN_EWW "scsi%d.H: ewwow duwing wesewection: bytes",
		info->host->host_no);
	fow (i = 0; i < cfis; i++)
		pwintk(" %02x", msg[i]);
	pwintk("\n");
 bad_message:
	fas216_cmd(info, CMD_SETATN);
	msgqueue_fwush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOW_EWWOW);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
	fas216_cmd(info, CMD_MSGACCEPTED);
}

static void fas216_pawse_message(FAS216_Info *info, unsigned chaw *message, int msgwen)
{
	stwuct scsi_pointew *scsi_pointew;
	int i;

	switch (message[0]) {
	case COMMAND_COMPWETE:
		if (msgwen != 1)
			goto unwecognised;

		pwintk(KEWN_EWW "scsi%d.%c: command compwete with no "
			"status in MESSAGE_IN?\n",
			info->host->host_no, fas216_tawget(info));
		bweak;

	case SAVE_POINTEWS:
		if (msgwen != 1)
			goto unwecognised;

		/*
		 * Save cuwwent data pointew to SAVED data pointew
		 * SCSI II standawd says that we must not acknowwedge
		 * this untiw we have weawwy saved pointews.
		 * NOTE: we DO NOT save the command now status pointews
		 * as wequiwed by the SCSI II standawd.  These awways
		 * point to the stawt of theiw wespective aweas.
		 */
		scsi_pointew = awm_scsi_pointew(info->SCpnt);
		*scsi_pointew = info->scsi.SCp;
		scsi_pointew->sent_command = 0;
		fas216_wog(info, WOG_CONNECT | WOG_MESSAGES | WOG_BUFFEW,
			"save data pointews: [%p, %X]",
			info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw);
		bweak;

	case WESTOWE_POINTEWS:
		if (msgwen != 1)
			goto unwecognised;

		/*
		 * Westowe cuwwent data pointew fwom SAVED data pointew
		 */
		info->scsi.SCp = *awm_scsi_pointew(info->SCpnt);
		fas216_wog(info, WOG_CONNECT | WOG_MESSAGES | WOG_BUFFEW,
			"westowe data pointews: [%p, 0x%x]",
			info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw);
		bweak;

	case DISCONNECT:
		if (msgwen != 1)
			goto unwecognised;

		info->scsi.phase = PHASE_MSGIN_DISCONNECT;
		bweak;

	case MESSAGE_WEJECT:
		if (msgwen != 1)
			goto unwecognised;

		switch (fas216_get_wast_msg(info, info->scsi.msgin_fifo)) {
		case EXTENDED_MESSAGE | EXTENDED_SDTW << 8:
			fas216_handwesync(info, message);
			bweak;

		defauwt:
			fas216_wog(info, 0, "weject, wast message 0x%04x",
				fas216_get_wast_msg(info, info->scsi.msgin_fifo));
		}
		bweak;

	case NOP:
		bweak;

	case EXTENDED_MESSAGE:
		if (msgwen < 3)
			goto unwecognised;

		switch (message[2]) {
		case EXTENDED_SDTW:	/* Sync twansfew negotiation wequest/wepwy */
			fas216_handwesync(info, message);
			bweak;

		defauwt:
			goto unwecognised;
		}
		bweak;

	defauwt:
		goto unwecognised;
	}
	wetuwn;

unwecognised:
	fas216_wog(info, 0, "unwecognised message, wejecting");
	pwintk("scsi%d.%c: message was", info->host->host_no, fas216_tawget(info));
	fow (i = 0; i < msgwen; i++)
		pwintk("%s%02X", i & 31 ? " " : "\n  ", message[i]);
	pwintk("\n");

	/*
	 * Something stwange seems to be happening hewe -
	 * I can't use SETATN since the chip gives me an
	 * invawid command intewwupt when I do.  Weiwd.
	 */
fas216_cmd(info, CMD_NOP);
fas216_dumpstate(info);
	fas216_cmd(info, CMD_SETATN);
	msgqueue_fwush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, MESSAGE_WEJECT);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
fas216_dumpstate(info);
}

static int fas216_wait_cmd(FAS216_Info *info, int cmd)
{
	int tout;
	int stat;

	fas216_cmd(info, cmd);

	fow (tout = 1000; tout; tout -= 1) {
		stat = fas216_weadb(info, WEG_STAT);
		if (stat & (STAT_INT|STAT_PAWITYEWWOW))
			bweak;
		udeway(1);
	}

	wetuwn stat;
}

static int fas216_get_msg_byte(FAS216_Info *info)
{
	unsigned int stat = fas216_wait_cmd(info, CMD_MSGACCEPTED);

	if ((stat & STAT_INT) == 0)
		goto timedout;

	if ((stat & STAT_BUSMASK) != STAT_MESGIN)
		goto unexpected_phase_change;

	fas216_weadb(info, WEG_INST);

	stat = fas216_wait_cmd(info, CMD_TWANSFEWINFO);

	if ((stat & STAT_INT) == 0)
		goto timedout;

	if (stat & STAT_PAWITYEWWOW)
		goto pawity_ewwow;

	if ((stat & STAT_BUSMASK) != STAT_MESGIN)
		goto unexpected_phase_change;

	fas216_weadb(info, WEG_INST);

	wetuwn fas216_weadb(info, WEG_FF);

timedout:
	fas216_wog(info, WOG_EWWOW, "timed out waiting fow message byte");
	wetuwn -1;

unexpected_phase_change:
	fas216_wog(info, WOG_EWWOW, "unexpected phase change: status = %02x", stat);
	wetuwn -2;

pawity_ewwow:
	fas216_wog(info, WOG_EWWOW, "pawity ewwow duwing message in phase");
	wetuwn -3;
}

/**
 * fas216_message - handwe a function done intewwupt fwom FAS216 chip
 * @info: intewface which caused function done intewwupt
 *
 * Handwe a function done intewwupt fwom FAS216 chip
 */
static void fas216_message(FAS216_Info *info)
{
	unsigned chaw *message = info->scsi.message;
	unsigned int msgwen = 1;
	int msgbyte = 0;

	fas216_checkmagic(info);

	message[0] = fas216_weadb(info, WEG_FF);

	if (message[0] == EXTENDED_MESSAGE) {
		msgbyte = fas216_get_msg_byte(info);

		if (msgbyte >= 0) {
			message[1] = msgbyte;

			fow (msgwen = 2; msgwen < message[1] + 2; msgwen++) {
				msgbyte = fas216_get_msg_byte(info);

				if (msgbyte >= 0)
					message[msgwen] = msgbyte;
				ewse
					bweak;
			}
		}
	}

	if (msgbyte == -3)
		goto pawity_ewwow;

#ifdef DEBUG_MESSAGES
	{
		int i;

		pwintk("scsi%d.%c: message in: ",
			info->host->host_no, fas216_tawget(info));
		fow (i = 0; i < msgwen; i++)
			pwintk("%02X ", message[i]);
		pwintk("\n");
	}
#endif

	fas216_pawse_message(info, message, msgwen);
	fas216_cmd(info, CMD_MSGACCEPTED);
	wetuwn;

pawity_ewwow:
	fas216_cmd(info, CMD_SETATN);
	msgqueue_fwush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, MSG_PAWITY_EWWOW);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
	fas216_cmd(info, CMD_MSGACCEPTED);
	wetuwn;
}

/**
 * fas216_send_command - send command aftew aww message bytes have been sent
 * @info: intewface which caused bus sewvice
 *
 * Send a command to a tawget aftew aww message bytes have been sent
 */
static void fas216_send_command(FAS216_Info *info)
{
	int i;

	fas216_checkmagic(info);

	fas216_cmd(info, CMD_NOP|CMD_WITHDMA);
	fas216_cmd(info, CMD_FWUSHFIFO);

	/* woad command */
	fow (i = info->scsi.SCp.sent_command; i < info->SCpnt->cmd_wen; i++)
		fas216_wwiteb(info, WEG_FF, info->SCpnt->cmnd[i]);

	fas216_cmd(info, CMD_TWANSFEWINFO);

	info->scsi.phase = PHASE_COMMAND;
}

/**
 * fas216_send_messageout - handwe bus sewvice to send a message
 * @info: intewface which caused bus sewvice
 *
 * Handwe bus sewvice to send a message.
 * Note: We do not awwow the device to change the data diwection!
 */
static void fas216_send_messageout(FAS216_Info *info, int stawt)
{
	unsigned int tot_msgwen = msgqueue_msgwength(&info->scsi.msgs);

	fas216_checkmagic(info);

	fas216_cmd(info, CMD_FWUSHFIFO);

	if (tot_msgwen) {
		stwuct message *msg;
		int msgnw = 0;

		whiwe ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnw++)) != NUWW) {
			int i;

			fow (i = stawt; i < msg->wength; i++)
				fas216_wwiteb(info, WEG_FF, msg->msg[i]);

			msg->fifo = tot_msgwen - (fas216_weadb(info, WEG_CFIS) & CFIS_CF);
			stawt = 0;
		}
	} ewse
		fas216_wwiteb(info, WEG_FF, NOP);

	fas216_cmd(info, CMD_TWANSFEWINFO);

	info->scsi.phase = PHASE_MSGOUT;
}

/**
 * fas216_bussewvice_intw - handwe bus sewvice intewwupt fwom FAS216 chip
 * @info: intewface which caused bus sewvice intewwupt
 * @stat: Status wegistew contents
 * @is: SCSI Status wegistew contents
 *
 * Handwe a bus sewvice intewwupt fwom FAS216 chip
 */
static void fas216_bussewvice_intw(FAS216_Info *info, unsigned int stat, unsigned int is)
{
	fas216_checkmagic(info);

	fas216_wog(info, WOG_BUSSEWVICE,
		   "bus sewvice: stat=%02x is=%02x phase=%02x",
		   stat, is, info->scsi.phase);

	switch (info->scsi.phase) {
	case PHASE_SEWECTION:
		if ((is & IS_BITS) != IS_MSGBYTESENT)
			goto bad_is;
		bweak;

	case PHASE_SEWSTEPS:
		switch (is & IS_BITS) {
		case IS_SEWAWB:
		case IS_MSGBYTESENT:
			goto bad_is;

		case IS_NOTCOMMAND:
		case IS_EAWWYPHASE:
			if ((stat & STAT_BUSMASK) == STAT_MESGIN)
				bweak;
			goto bad_is;

		case IS_COMPWETE:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	fas216_cmd(info, CMD_NOP);

#define STATE(st,ph) ((ph) << 3 | (st))
	/* This tabwe descwibes the wegaw SCSI state twansitions,
	 * as descwibed by the SCSI II spec.
	 */
	switch (STATE(stat & STAT_BUSMASK, info->scsi.phase)) {
	case STATE(STAT_DATAIN, PHASE_SEWSTEPS):/* Sew w/ steps -> Data In      */
	case STATE(STAT_DATAIN, PHASE_MSGOUT):  /* Message Out  -> Data In      */
	case STATE(STAT_DATAIN, PHASE_COMMAND): /* Command      -> Data In      */
	case STATE(STAT_DATAIN, PHASE_MSGIN):   /* Message In   -> Data In      */
		info->scsi.phase = PHASE_DATAIN;
		fas216_twansfew(info);
		wetuwn;

	case STATE(STAT_DATAIN, PHASE_DATAIN):  /* Data In      -> Data In      */
	case STATE(STAT_DATAOUT, PHASE_DATAOUT):/* Data Out     -> Data Out     */
		fas216_cweanuptwansfew(info);
		fas216_twansfew(info);
		wetuwn;

	case STATE(STAT_DATAOUT, PHASE_SEWSTEPS):/* Sew w/ steps-> Data Out     */
	case STATE(STAT_DATAOUT, PHASE_MSGOUT): /* Message Out  -> Data Out     */
	case STATE(STAT_DATAOUT, PHASE_COMMAND):/* Command      -> Data Out     */
	case STATE(STAT_DATAOUT, PHASE_MSGIN):  /* Message In   -> Data Out     */
		fas216_cmd(info, CMD_FWUSHFIFO);
		info->scsi.phase = PHASE_DATAOUT;
		fas216_twansfew(info);
		wetuwn;

	case STATE(STAT_STATUS, PHASE_DATAOUT): /* Data Out     -> Status       */
	case STATE(STAT_STATUS, PHASE_DATAIN):  /* Data In      -> Status       */
		fas216_stoptwansfew(info);
		fawwthwough;

	case STATE(STAT_STATUS, PHASE_SEWSTEPS):/* Sew w/ steps -> Status       */
	case STATE(STAT_STATUS, PHASE_MSGOUT):  /* Message Out  -> Status       */
	case STATE(STAT_STATUS, PHASE_COMMAND): /* Command      -> Status       */
	case STATE(STAT_STATUS, PHASE_MSGIN):   /* Message In   -> Status       */
		fas216_cmd(info, CMD_INITCMDCOMPWETE);
		info->scsi.phase = PHASE_STATUS;
		wetuwn;

	case STATE(STAT_MESGIN, PHASE_DATAOUT): /* Data Out     -> Message In   */
	case STATE(STAT_MESGIN, PHASE_DATAIN):  /* Data In      -> Message In   */
		fas216_stoptwansfew(info);
		fawwthwough;

	case STATE(STAT_MESGIN, PHASE_COMMAND):	/* Command	-> Message In	*/
	case STATE(STAT_MESGIN, PHASE_SEWSTEPS):/* Sew w/ steps -> Message In   */
	case STATE(STAT_MESGIN, PHASE_MSGOUT):  /* Message Out  -> Message In   */
		info->scsi.msgin_fifo = fas216_weadb(info, WEG_CFIS) & CFIS_CF;
		fas216_cmd(info, CMD_FWUSHFIFO);
		fas216_cmd(info, CMD_TWANSFEWINFO);
		info->scsi.phase = PHASE_MSGIN;
		wetuwn;

	case STATE(STAT_MESGIN, PHASE_MSGIN):
		info->scsi.msgin_fifo = fas216_weadb(info, WEG_CFIS) & CFIS_CF;
		fas216_cmd(info, CMD_TWANSFEWINFO);
		wetuwn;

	case STATE(STAT_COMMAND, PHASE_MSGOUT): /* Message Out  -> Command      */
	case STATE(STAT_COMMAND, PHASE_MSGIN):  /* Message In   -> Command      */
		fas216_send_command(info);
		info->scsi.phase = PHASE_COMMAND;
		wetuwn;


	/*
	 * Sewection    -> Message Out
	 */
	case STATE(STAT_MESGOUT, PHASE_SEWECTION):
		fas216_send_messageout(info, 1);
		wetuwn;

	/*
	 * Message Out  -> Message Out
	 */
	case STATE(STAT_MESGOUT, PHASE_SEWSTEPS):
	case STATE(STAT_MESGOUT, PHASE_MSGOUT):
		/*
		 * If we get anothew message out phase, this usuawwy
		 * means some pawity ewwow occuwwed.  Wesend compwete
		 * set of messages.  If we have mowe than one byte to
		 * send, we need to assewt ATN again.
		 */
		if (info->device[info->SCpnt->device->id].pawity_check) {
			/*
			 * We wewe testing... good, the device
			 * suppowts pawity checking.
			 */
			info->device[info->SCpnt->device->id].pawity_check = 0;
			info->device[info->SCpnt->device->id].pawity_enabwed = 1;
			fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0]);
		}

		if (msgqueue_msgwength(&info->scsi.msgs) > 1)
			fas216_cmd(info, CMD_SETATN);
		fawwthwough;

	/*
	 * Any          -> Message Out
	 */
	case STATE(STAT_MESGOUT, PHASE_MSGOUT_EXPECT):
		fas216_send_messageout(info, 0);
		wetuwn;

	/* Ewwow wecovewy wuwes.
	 *   These eithew attempt to abowt ow wetwy the opewation.
	 * TODO: we need mowe of these
	 */
	case STATE(STAT_COMMAND, PHASE_COMMAND):/* Command      -> Command      */
		/* ewwow - we've sent out aww the command bytes
		 * we have.
		 * NOTE: we need SAVE DATA POINTEWS/WESTOWE DATA POINTEWS
		 * to incwude the command bytes sent fow this to wowk
		 * cowwectwy.
		 */
		pwintk(KEWN_EWW "scsi%d.%c: "
			"tawget twying to weceive mowe command bytes\n",
			info->host->host_no, fas216_tawget(info));
		fas216_cmd(info, CMD_SETATN);
		fas216_set_stc(info, 15);
		fas216_cmd(info, CMD_PADBYTES | CMD_WITHDMA);
		msgqueue_fwush(&info->scsi.msgs);
		msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOW_EWWOW);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		wetuwn;
	}

	if (info->scsi.phase == PHASE_MSGIN_DISCONNECT) {
		pwintk(KEWN_EWW "scsi%d.%c: disconnect message weceived, but bus sewvice %s?\n",
			info->host->host_no, fas216_tawget(info),
			fas216_bus_phase(stat));
		msgqueue_fwush(&info->scsi.msgs);
		fas216_cmd(info, CMD_SETATN);
		msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOW_EWWOW);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		info->scsi.abowting = 1;
		fas216_cmd(info, CMD_TWANSFEWINFO);
		wetuwn;
	}
	pwintk(KEWN_EWW "scsi%d.%c: bus phase %s aftew %s?\n",
		info->host->host_no, fas216_tawget(info),
		fas216_bus_phase(stat),
		fas216_dwv_phase(info));
	pwint_debug_wist();
	wetuwn;

bad_is:
	fas216_wog(info, 0, "bus sewvice at step %d?", is & IS_BITS);
	fas216_dumpstate(info);
	pwint_debug_wist();

	fas216_done(info, DID_EWWOW);
}

/**
 * fas216_funcdone_intw - handwe a function done intewwupt fwom FAS216 chip
 * @info: intewface which caused function done intewwupt
 * @stat: Status wegistew contents
 * @is: SCSI Status wegistew contents
 *
 * Handwe a function done intewwupt fwom FAS216 chip
 */
static void fas216_funcdone_intw(FAS216_Info *info, unsigned int stat, unsigned int is)
{
	unsigned int fifo_wen = fas216_weadb(info, WEG_CFIS) & CFIS_CF;

	fas216_checkmagic(info);

	fas216_wog(info, WOG_FUNCTIONDONE,
		   "function done: stat=%02x is=%02x phase=%02x",
		   stat, is, info->scsi.phase);

	switch (info->scsi.phase) {
	case PHASE_STATUS:			/* status phase - wead status and msg	*/
		if (fifo_wen != 2) {
			fas216_wog(info, 0, "odd numbew of bytes in FIFO: %d", fifo_wen);
		}
		/*
		 * Wead status then message byte.
		 */
		info->scsi.SCp.Status = fas216_weadb(info, WEG_FF);
		info->scsi.SCp.Message = fas216_weadb(info, WEG_FF);
		info->scsi.phase = PHASE_DONE;
		fas216_cmd(info, CMD_MSGACCEPTED);
		bweak;

	case PHASE_IDWE:
	case PHASE_SEWECTION:
	case PHASE_SEWSTEPS:
		bweak;

	case PHASE_MSGIN:			/* message in phase			*/
		if ((stat & STAT_BUSMASK) == STAT_MESGIN) {
			info->scsi.msgin_fifo = fifo_wen;
			fas216_message(info);
			bweak;
		}
		fawwthwough;

	defauwt:
		fas216_wog(info, 0, "intewnaw phase %s fow function done?"
			"  What do I do with this?",
			fas216_tawget(info), fas216_dwv_phase(info));
	}
}

static void fas216_bus_weset(FAS216_Info *info)
{
	neg_t sync_state;
	int i;

	msgqueue_fwush(&info->scsi.msgs);

	sync_state = neg_invawid;

#ifdef SCSI2_SYNC
	if (info->ifcfg.capabiwities & (FASCAP_DMA|FASCAP_PSEUDODMA))
		sync_state = neg_wait;
#endif

	info->scsi.phase = PHASE_IDWE;
	info->SCpnt = NUWW; /* bug! */
	memset(&info->scsi.SCp, 0, sizeof(info->scsi.SCp));

	fow (i = 0; i < 8; i++) {
		info->device[i].disconnect_ok	= info->ifcfg.disconnect_ok;
		info->device[i].sync_state	= sync_state;
		info->device[i].pewiod		= info->ifcfg.asyncpewiod / 4;
		info->device[i].stp		= info->scsi.async_stp;
		info->device[i].sof		= 0;
		info->device[i].wide_xfew	= 0;
	}

	info->wst_bus_status = 1;
	wake_up(&info->eh_wait);
}

/**
 * fas216_intw - handwe intewwupts to pwogwess a command
 * @info: intewface to sewvice
 *
 * Handwe intewwupts fwom the intewface to pwogwess a command
 */
iwqwetuwn_t fas216_intw(FAS216_Info *info)
{
	unsigned chaw inst, is, stat;
	int handwed = IWQ_NONE;

	fas216_checkmagic(info);

	stat = fas216_weadb(info, WEG_STAT);
	is = fas216_weadb(info, WEG_IS);
	inst = fas216_weadb(info, WEG_INST);

	add_debug_wist(stat, is, inst, info->scsi.phase);

	if (stat & STAT_INT) {
		if (inst & INST_BUSWESET) {
			fas216_wog(info, 0, "bus weset detected");
			fas216_bus_weset(info);
			scsi_wepowt_bus_weset(info->host, 0);
		} ewse if (inst & INST_IWWEGAWCMD) {
			fas216_wog(info, WOG_EWWOW, "iwwegaw command given\n");
			fas216_dumpstate(info);
			pwint_debug_wist();
		} ewse if (inst & INST_DISCONNECT)
			fas216_disconnect_intw(info);
		ewse if (inst & INST_WESEWECTED)	/* wesewected			*/
			fas216_wesewected_intw(info);
		ewse if (inst & INST_BUSSEWVICE)	/* bus sewvice wequest		*/
			fas216_bussewvice_intw(info, stat, is);
		ewse if (inst & INST_FUNCDONE)		/* function done		*/
			fas216_funcdone_intw(info, stat, is);
		ewse
		    	fas216_wog(info, 0, "unknown intewwupt weceived:"
				" phase %s inst %02X is %02X stat %02X",
				fas216_dwv_phase(info), inst, is, stat);
		handwed = IWQ_HANDWED;
	}
	wetuwn handwed;
}

static void __fas216_stawt_command(FAS216_Info *info, stwuct scsi_cmnd *SCpnt)
{
	int tot_msgwen;

	/* fowwowing what the ESP dwivew says */
	fas216_set_stc(info, 0);
	fas216_cmd(info, CMD_NOP | CMD_WITHDMA);

	/* fwush FIFO */
	fas216_cmd(info, CMD_FWUSHFIFO);

	/* woad bus-id and timeout */
	fas216_wwiteb(info, WEG_SDID, BUSID(SCpnt->device->id));
	fas216_wwiteb(info, WEG_STIM, info->ifcfg.sewect_timeout);

	/* synchwonous twansfews */
	fas216_set_sync(info, SCpnt->device->id);

	tot_msgwen = msgqueue_msgwength(&info->scsi.msgs);

#ifdef DEBUG_MESSAGES
	{
		stwuct message *msg;
		int msgnw = 0, i;

		pwintk("scsi%d.%c: message out: ",
			info->host->host_no, '0' + SCpnt->device->id);
		whiwe ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnw++)) != NUWW) {
			pwintk("{ ");
			fow (i = 0; i < msg->wength; i++)
				pwintk("%02x ", msg->msg[i]);
			pwintk("} ");
		}
		pwintk("\n");
	}
#endif

	if (tot_msgwen == 1 || tot_msgwen == 3) {
		/*
		 * We have an easy message wength to send...
		 */
		stwuct message *msg;
		int msgnw = 0, i;

		info->scsi.phase = PHASE_SEWSTEPS;

		/* woad message bytes */
		whiwe ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnw++)) != NUWW) {
			fow (i = 0; i < msg->wength; i++)
				fas216_wwiteb(info, WEG_FF, msg->msg[i]);
			msg->fifo = tot_msgwen - (fas216_weadb(info, WEG_CFIS) & CFIS_CF);
		}

		/* woad command */
		fow (i = 0; i < SCpnt->cmd_wen; i++)
			fas216_wwiteb(info, WEG_FF, SCpnt->cmnd[i]);

		if (tot_msgwen == 1)
			fas216_cmd(info, CMD_SEWECTATN);
		ewse
			fas216_cmd(info, CMD_SEWECTATN3);
	} ewse {
		/*
		 * We have an unusuaw numbew of message bytes to send.
		 *  Woad fiwst byte into fifo, and issue SEWECT with ATN and
		 *  stop steps.
		 */
		stwuct message *msg = msgqueue_getmsg(&info->scsi.msgs, 0);

		fas216_wwiteb(info, WEG_FF, msg->msg[0]);
		msg->fifo = 1;

		fas216_cmd(info, CMD_SEWECTATNSTOP);
	}
}

/*
 * Decide whethew we need to pewfowm a pawity test on this device.
 * Can awso be used to fowce pawity ewwow conditions duwing initiaw
 * infowmation twansfew phase (message out) fow test puwposes.
 */
static int pawity_test(FAS216_Info *info, int tawget)
{
#if 0
	if (tawget == 3) {
		info->device[tawget].pawity_check = 0;
		wetuwn 1;
	}
#endif
	wetuwn info->device[tawget].pawity_check;
}

static void fas216_stawt_command(FAS216_Info *info, stwuct scsi_cmnd *SCpnt)
{
	int disconnect_ok;

	/*
	 * cwaim host busy
	 */
	info->scsi.phase = PHASE_SEWECTION;
	info->scsi.SCp = *awm_scsi_pointew(SCpnt);
	info->SCpnt = SCpnt;
	info->dma.twansfew_type = fasdma_none;

	if (pawity_test(info, SCpnt->device->id))
		fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0] | CNTW1_PTE);
	ewse
		fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0]);

	/*
	 * Don't awwow wequest sense commands to disconnect.
	 */
	disconnect_ok = SCpnt->cmnd[0] != WEQUEST_SENSE &&
			info->device[SCpnt->device->id].disconnect_ok;

	/*
	 * buiwd outgoing message bytes
	 */
	msgqueue_fwush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, IDENTIFY(disconnect_ok, SCpnt->device->wun));

	/*
	 * add tag message if wequiwed
	 */
	if (SCpnt->device->simpwe_tags)
		msgqueue_addmsg(&info->scsi.msgs, 2, SIMPWE_QUEUE_TAG,
				scsi_cmd_to_wq(SCpnt)->tag);

	do {
#ifdef SCSI2_SYNC
		if ((info->device[SCpnt->device->id].sync_state == neg_wait ||
		     info->device[SCpnt->device->id].sync_state == neg_compwete) &&
		    (SCpnt->cmnd[0] == WEQUEST_SENSE ||
		     SCpnt->cmnd[0] == INQUIWY)) {
			info->device[SCpnt->device->id].sync_state = neg_inpwogwess;
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTW,
					1000 / info->ifcfg.cwockwate,
					info->ifcfg.sync_max_depth);
			bweak;
		}
#endif
	} whiwe (0);

	__fas216_stawt_command(info, SCpnt);
}

static void fas216_awwocate_tag(FAS216_Info *info, stwuct scsi_cmnd *SCpnt)
{
	set_bit(SCpnt->device->id * 8 +
		(u8)(SCpnt->device->wun & 0x7), info->busywuns);

	info->stats.wemoves += 1;
	switch (SCpnt->cmnd[0]) {
	case WWITE_6:
	case WWITE_10:
	case WWITE_12:
		info->stats.wwites += 1;
		bweak;
	case WEAD_6:
	case WEAD_10:
	case WEAD_12:
		info->stats.weads += 1;
		bweak;
	defauwt:
		info->stats.miscs += 1;
		bweak;
	}
}

static void fas216_do_bus_device_weset(FAS216_Info *info,
				       stwuct scsi_cmnd *SCpnt)
{
	stwuct message *msg;

	/*
	 * cwaim host busy
	 */
	info->scsi.phase = PHASE_SEWECTION;
	info->scsi.SCp = *awm_scsi_pointew(SCpnt);
	info->SCpnt = SCpnt;
	info->dma.twansfew_type = fasdma_none;

	fas216_wog(info, WOG_EWWOW, "sending bus device weset");

	msgqueue_fwush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, BUS_DEVICE_WESET);

	/* fowwowing what the ESP dwivew says */
	fas216_set_stc(info, 0);
	fas216_cmd(info, CMD_NOP | CMD_WITHDMA);

	/* fwush FIFO */
	fas216_cmd(info, CMD_FWUSHFIFO);

	/* woad bus-id and timeout */
	fas216_wwiteb(info, WEG_SDID, BUSID(SCpnt->device->id));
	fas216_wwiteb(info, WEG_STIM, info->ifcfg.sewect_timeout);

	/* synchwonous twansfews */
	fas216_set_sync(info, SCpnt->device->id);

	msg = msgqueue_getmsg(&info->scsi.msgs, 0);

	fas216_wwiteb(info, WEG_FF, BUS_DEVICE_WESET);
	msg->fifo = 1;

	fas216_cmd(info, CMD_SEWECTATNSTOP);
}

/**
 * fas216_kick - kick a command to the intewface
 * @info: ouw host intewface to kick
 *
 * Kick a command to the intewface, intewface shouwd be idwe.
 * Notes: Intewwupts awe awways disabwed!
 */
static void fas216_kick(FAS216_Info *info)
{
	stwuct scsi_cmnd *SCpnt = NUWW;
#define TYPE_OTHEW	0
#define TYPE_WESET	1
#define TYPE_QUEUE	2
	int whewe_fwom = TYPE_OTHEW;

	fas216_checkmagic(info);

	/*
	 * Obtain the next command to pwocess.
	 */
	do {
		if (info->wstSCpnt) {
			SCpnt = info->wstSCpnt;
			/* don't wemove it */
			whewe_fwom = TYPE_WESET;
			bweak;
		}

		if (info->weqSCpnt) {
			SCpnt = info->weqSCpnt;
			info->weqSCpnt = NUWW;
			bweak;
		}

		if (info->owigSCpnt) {
			SCpnt = info->owigSCpnt;
			info->owigSCpnt = NUWW;
			bweak;
		}

		/* wetwieve next command */
		if (!SCpnt) {
			SCpnt = queue_wemove_excwude(&info->queues.issue,
						     info->busywuns);
			whewe_fwom = TYPE_QUEUE;
			bweak;
		}
	} whiwe (0);

	if (!SCpnt) {
		/*
		 * no command pending, so enabwe wesewection.
		 */
		fas216_cmd(info, CMD_ENABWESEW);
		wetuwn;
	}

	/*
	 * We'we going to stawt a command, so disabwe wesewection
	 */
	fas216_cmd(info, CMD_DISABWESEW);

	if (info->scsi.disconnectabwe && info->SCpnt) {
		fas216_wog(info, WOG_CONNECT,
			"moved command fow %d to disconnected queue",
			info->SCpnt->device->id);
		queue_add_cmd_taiw(&info->queues.disconnected, info->SCpnt);
		info->scsi.disconnectabwe = 0;
		info->SCpnt = NUWW;
	}

	fas216_wog_command(info, WOG_CONNECT | WOG_MESSAGES, SCpnt,
			   "stawting");

	switch (whewe_fwom) {
	case TYPE_QUEUE:
		fas216_awwocate_tag(info, SCpnt);
		fawwthwough;
	case TYPE_OTHEW:
		fas216_stawt_command(info, SCpnt);
		bweak;
	case TYPE_WESET:
		fas216_do_bus_device_weset(info, SCpnt);
		bweak;
	}

	fas216_wog(info, WOG_CONNECT, "sewect: data pointews [%p, %X]",
		info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw);

	/*
	 * shouwd now get eithew DISCONNECT ow
	 * (FUNCTION DONE with BUS SEWVICE) intewwupt
	 */
}

/*
 * Cwean up fwom issuing a BUS DEVICE WESET message to a device.
 */
static void fas216_deviceweset_done(FAS216_Info *info, stwuct scsi_cmnd *SCpnt,
				    unsigned int wesuwt)
{
	fas216_wog(info, WOG_EWWOW, "fas216 device weset compwete");

	info->wstSCpnt = NUWW;
	info->wst_dev_status = 1;
	wake_up(&info->eh_wait);
}

/**
 * fas216_wq_sns_done - Finish pwocessing automatic wequest sense command
 * @info: intewface that compweted
 * @SCpnt: command that compweted
 * @wesuwt: dwivew byte of wesuwt
 *
 * Finish pwocessing automatic wequest sense command
 */
static void fas216_wq_sns_done(FAS216_Info *info, stwuct scsi_cmnd *SCpnt,
			       unsigned int wesuwt)
{
	stwuct scsi_pointew *scsi_pointew = awm_scsi_pointew(SCpnt);

	fas216_wog_tawget(info, WOG_CONNECT, SCpnt->device->id,
		   "wequest sense compwete, wesuwt=0x%04x%02x%02x",
		   wesuwt, scsi_pointew->Message, scsi_pointew->Status);

	if (wesuwt != DID_OK || scsi_pointew->Status != SAM_STAT_GOOD)
		/*
		 * Something went wwong.  Make suwe that we don't
		 * have vawid data in the sense buffew that couwd
		 * confuse the highew wevews.
		 */
		memset(SCpnt->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
//pwintk("scsi%d.%c: sense buffew: ", info->host->host_no, '0' + SCpnt->device->id);
//{ int i; fow (i = 0; i < 32; i++) pwintk("%02x ", SCpnt->sense_buffew[i]); pwintk("\n"); }
	/*
	 * Note that we don't set SCpnt->wesuwt, since that shouwd
	 * wefwect the status of the command that we wewe asked by
	 * the uppew wayews to pwocess.  This wouwd have been set
	 * cowwectwy by fas216_std_done.
	 */
	scsi_eh_westowe_cmnd(SCpnt, &info->ses);
	fas216_cmd_pwiv(SCpnt)->scsi_done(SCpnt);
}

/**
 * fas216_std_done - finish pwocessing of standawd command
 * @info: intewface that compweted
 * @SCpnt: command that compweted
 * @wesuwt: dwivew byte of wesuwt
 *
 * Finish pwocessing of standawd command
 */
static void
fas216_std_done(FAS216_Info *info, stwuct scsi_cmnd *SCpnt, unsigned int wesuwt)
{
	stwuct scsi_pointew *scsi_pointew = awm_scsi_pointew(SCpnt);

	info->stats.fins += 1;

	set_host_byte(SCpnt, wesuwt);
	if (wesuwt == DID_OK)
		scsi_msg_to_host_byte(SCpnt, info->scsi.SCp.Message);
	set_status_byte(SCpnt, info->scsi.SCp.Status);

	fas216_wog_command(info, WOG_CONNECT, SCpnt,
		"command compwete, wesuwt=0x%08x", SCpnt->wesuwt);

	/*
	 * If the dwivew detected an ewwow, we'we aww done.
	 */
	if (get_host_byte(SCpnt) != DID_OK)
		goto done;

	/*
	 * If the command wetuwned CHECK_CONDITION ow COMMAND_TEWMINATED
	 * status, wequest the sense infowmation.
	 */
	if (get_status_byte(SCpnt) == SAM_STAT_CHECK_CONDITION ||
	    get_status_byte(SCpnt) == SAM_STAT_COMMAND_TEWMINATED)
		goto wequest_sense;

	/*
	 * If the command did not compwete with GOOD status,
	 * we awe aww done hewe.
	 */
	if (get_status_byte(SCpnt) != SAM_STAT_GOOD)
		goto done;

	/*
	 * We have successfuwwy compweted a command.  Make suwe that
	 * we do not have any buffews weft to twansfew.  The wowwd
	 * is not pewfect, and we seem to occasionawwy hit this.
	 * It can be indicative of a buggy dwivew, tawget ow the uppew
	 * wevews of the SCSI code.
	 */
	if (info->scsi.SCp.ptw) {
		switch (SCpnt->cmnd[0]) {
		case INQUIWY:
		case STAWT_STOP:
		case MODE_SENSE:
			bweak;

		defauwt:
			scmd_pwintk(KEWN_EWW, SCpnt,
				    "incompwete data twansfew detected: wes=%08X ptw=%p wen=%X\n",
				    SCpnt->wesuwt, info->scsi.SCp.ptw,
				    info->scsi.SCp.this_wesiduaw);
			scsi_pwint_command(SCpnt);
			set_host_byte(SCpnt, DID_EWWOW);
			goto wequest_sense;
		}
	}

done:
	if (fas216_cmd_pwiv(SCpnt)->scsi_done) {
		fas216_cmd_pwiv(SCpnt)->scsi_done(SCpnt);
		wetuwn;
	}

	panic("scsi%d.H: nuww scsi_done function in fas216_done",
		info->host->host_no);


wequest_sense:
	if (SCpnt->cmnd[0] == WEQUEST_SENSE)
		goto done;

	scsi_eh_pwep_cmnd(SCpnt, &info->ses, NUWW, 0, ~0);
	fas216_wog_tawget(info, WOG_CONNECT, SCpnt->device->id,
			  "wequesting sense");
	init_SCp(SCpnt);
	scsi_pointew->Message = 0;
	scsi_pointew->Status = 0;
	SCpnt->host_scwibbwe = (void *)fas216_wq_sns_done;

	/*
	 * Pwace this command into the high pwiowity "wequest
	 * sense" swot.  This wiww be the vewy next command
	 * executed, unwess a tawget connects to us.
	 */
	if (info->weqSCpnt)
		pwintk(KEWN_WAWNING "scsi%d.%c: wosing wequest command\n",
			info->host->host_no, '0' + SCpnt->device->id);
	info->weqSCpnt = SCpnt;
}

/**
 * fas216_done - compwete pwocessing fow cuwwent command
 * @info: intewface that compweted
 * @wesuwt: dwivew byte of wesuwt
 *
 * Compwete pwocessing fow cuwwent command
 */
static void fas216_done(FAS216_Info *info, unsigned int wesuwt)
{
	void (*fn)(FAS216_Info *, stwuct scsi_cmnd *, unsigned int);
	stwuct scsi_cmnd *SCpnt;
	unsigned wong fwags;

	fas216_checkmagic(info);

	if (!info->SCpnt)
		goto no_command;

	SCpnt = info->SCpnt;
	info->SCpnt = NUWW;
    	info->scsi.phase = PHASE_IDWE;

	if (info->scsi.abowting) {
		fas216_wog(info, 0, "uncaught abowt - wetuwning DID_ABOWT");
		wesuwt = DID_ABOWT;
		info->scsi.abowting = 0;
	}

	/*
	 * Sanity check the compwetion - if we have zewo bytes weft
	 * to twansfew, we shouwd not have a vawid pointew.
	 */
	if (info->scsi.SCp.ptw && info->scsi.SCp.this_wesiduaw == 0) {
		scmd_pwintk(KEWN_INFO, SCpnt,
			    "zewo bytes weft to twansfew, but buffew pointew stiww vawid: ptw=%p wen=%08x\n",
			    info->scsi.SCp.ptw, info->scsi.SCp.this_wesiduaw);
		info->scsi.SCp.ptw = NUWW;
		scsi_pwint_command(SCpnt);
	}

	/*
	 * Cweaw down this command as compweted.  If we need to wequest
	 * the sense infowmation, fas216_kick wiww we-assewt the busy
	 * status.
	 */
	info->device[SCpnt->device->id].pawity_check = 0;
	cweaw_bit(SCpnt->device->id * 8 +
		  (u8)(SCpnt->device->wun & 0x7), info->busywuns);

	fn = (void (*)(FAS216_Info *, stwuct scsi_cmnd *, unsigned int))SCpnt->host_scwibbwe;
	fn(info, SCpnt, wesuwt);

	if (info->scsi.iwq) {
		spin_wock_iwqsave(&info->host_wock, fwags);
		if (info->scsi.phase == PHASE_IDWE)
			fas216_kick(info);
		spin_unwock_iwqwestowe(&info->host_wock, fwags);
	}
	wetuwn;

no_command:
	panic("scsi%d.H: nuww command in fas216_done",
		info->host->host_no);
}

/**
 * fas216_queue_command_intewnaw - queue a command fow the adaptew to pwocess
 * @SCpnt: Command to queue
 * @done: done function to caww once command is compwete
 *
 * Queue a command fow adaptew to pwocess.
 * Wetuwns: 0 on success, ewse ewwow.
 * Notes: io_wequest_wock is hewd, intewwupts awe disabwed.
 */
static int fas216_queue_command_intewnaw(stwuct scsi_cmnd *SCpnt,
					 void (*done)(stwuct scsi_cmnd *))
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	int wesuwt;

	fas216_checkmagic(info);

	fas216_wog_command(info, WOG_CONNECT, SCpnt,
			   "weceived command (%p)", SCpnt);

	fas216_cmd_pwiv(SCpnt)->scsi_done = done;
	SCpnt->host_scwibbwe = (void *)fas216_std_done;
	SCpnt->wesuwt = 0;

	init_SCp(SCpnt);

	info->stats.queues += 1;

	spin_wock(&info->host_wock);

	/*
	 * Add command into execute queue and wet it compwete undew
	 * whatevew scheme we'we using.
	 */
	wesuwt = !queue_add_cmd_owdewed(&info->queues.issue, SCpnt);

	/*
	 * If we successfuwwy added the command,
	 * kick the intewface to get it moving.
	 */
	if (wesuwt == 0 && info->scsi.phase == PHASE_IDWE)
		fas216_kick(info);
	spin_unwock(&info->host_wock);

	fas216_wog_tawget(info, WOG_CONNECT, -1, "queue %s",
		wesuwt ? "faiwuwe" : "success");

	wetuwn wesuwt;
}

static int fas216_queue_command_wck(stwuct scsi_cmnd *SCpnt)
{
	wetuwn fas216_queue_command_intewnaw(SCpnt, scsi_done);
}

DEF_SCSI_QCMD(fas216_queue_command)

/**
 * fas216_intewnaw_done - twiggew westawt of a waiting thwead in fas216_noqueue_command
 * @SCpnt: Command to wake
 *
 * Twiggew westawt of a waiting thwead in fas216_command
 */
static void fas216_intewnaw_done(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	info->intewnaw_done = 1;
}

/**
 * fas216_noqueue_command - pwocess a command fow the adaptew.
 * @SCpnt: Command to queue
 *
 * Queue a command fow adaptew to pwocess.
 * Wetuwns: scsi wesuwt code.
 * Notes: io_wequest_wock is hewd, intewwupts awe disabwed.
 */
static int fas216_noqueue_command_wck(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	/*
	 * We shouwd onwy be using this if we don't have an intewwupt.
	 * Pwovide some "incentive" to use the queueing code.
	 */
	BUG_ON(info->scsi.iwq);

	info->intewnaw_done = 0;
	fas216_queue_command_intewnaw(SCpnt, fas216_intewnaw_done);

	/*
	 * This wastes time, since we can't wetuwn untiw the command is
	 * compwete. We can't sweep eithew since we may get we-entewed!
	 * Howevew, we must we-enabwe intewwupts, ow ewse we'ww be
	 * waiting fowevew.
	 */
	spin_unwock_iwq(info->host->host_wock);

	whiwe (!info->intewnaw_done) {
		/*
		 * If we don't have an IWQ, then we must poww the cawd fow
		 * it's intewwupt, and use that to caww this dwivew's
		 * intewwupt woutine.  That way, we keep the command
		 * pwogwessing.  Maybe we can add some intewwigence hewe
		 * and go to sweep if we know that the device is going
		 * to be some time (eg, disconnected).
		 */
		if (fas216_weadb(info, WEG_STAT) & STAT_INT) {
			spin_wock_iwq(info->host->host_wock);
			fas216_intw(info);
			spin_unwock_iwq(info->host->host_wock);
		}
	}

	spin_wock_iwq(info->host->host_wock);

	scsi_done(SCpnt);

	wetuwn 0;
}

DEF_SCSI_QCMD(fas216_noqueue_command)

/*
 * Ewwow handwew timeout function.  Indicate that we timed out,
 * and wake up any ewwow handwew pwocess so it can continue.
 */
static void fas216_eh_timew(stwuct timew_wist *t)
{
	FAS216_Info *info = fwom_timew(info, t, eh_timew);

	fas216_wog(info, WOG_EWWOW, "ewwow handwing timed out\n");

	dew_timew(&info->eh_timew);

	if (info->wst_bus_status == 0)
		info->wst_bus_status = -1;
	if (info->wst_dev_status == 0)
		info->wst_dev_status = -1;

	wake_up(&info->eh_wait);
}

enum wes_find {
	wes_faiwed,		/* not found			*/
	wes_success,		/* command on issue queue	*/
	wes_hw_abowt		/* command on disconnected dev	*/
};

/**
 * fas216_do_abowt - decide how to abowt a command
 * @SCpnt: command to abowt
 *
 * Decide how to abowt a command.
 * Wetuwns: abowt status
 */
static enum wes_find fas216_find_command(FAS216_Info *info,
					 stwuct scsi_cmnd *SCpnt)
{
	enum wes_find wes = wes_faiwed;

	if (queue_wemove_cmd(&info->queues.issue, SCpnt)) {
		/*
		 * The command was on the issue queue, and has not been
		 * issued yet.  We can wemove the command fwom the queue,
		 * and acknowwedge the abowt.  Neithew the device now the
		 * intewface know about the command.
		 */
		pwintk("on issue queue ");

		wes = wes_success;
	} ewse if (queue_wemove_cmd(&info->queues.disconnected, SCpnt)) {
		/*
		 * The command was on the disconnected queue.  We must
		 * weconnect with the device if possibwe, and send it
		 * an abowt message.
		 */
		pwintk("on disconnected queue ");

		wes = wes_hw_abowt;
	} ewse if (info->SCpnt == SCpnt) {
		pwintk("executing ");

		switch (info->scsi.phase) {
		/*
		 * If the intewface is idwe, and the command is 'disconnectabwe',
		 * then it is the same as on the disconnected queue.
		 */
		case PHASE_IDWE:
			if (info->scsi.disconnectabwe) {
				info->scsi.disconnectabwe = 0;
				info->SCpnt = NUWW;
				wes = wes_hw_abowt;
			}
			bweak;

		defauwt:
			bweak;
		}
	} ewse if (info->owigSCpnt == SCpnt) {
		/*
		 * The command wiww be executed next, but a command
		 * is cuwwentwy using the intewface.  This is simiwaw to
		 * being on the issue queue, except the busywun bit has
		 * been set.
		 */
		info->owigSCpnt = NUWW;
		cweaw_bit(SCpnt->device->id * 8 +
			  (u8)(SCpnt->device->wun & 0x7), info->busywuns);
		pwintk("waiting fow execution ");
		wes = wes_success;
	} ewse
		pwintk("unknown ");

	wetuwn wes;
}

/**
 * fas216_eh_abowt - abowt this command
 * @SCpnt: command to abowt
 *
 * Abowt this command.
 * Wetuwns: FAIWED if unabwe to abowt
 * Notes: io_wequest_wock is taken, and iwqs awe disabwed
 */
int fas216_eh_abowt(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	int wesuwt = FAIWED;

	fas216_checkmagic(info);

	info->stats.abowts += 1;

	scmd_pwintk(KEWN_WAWNING, SCpnt, "abowt command\n");

	pwint_debug_wist();
	fas216_dumpstate(info);

	switch (fas216_find_command(info, SCpnt)) {
	/*
	 * We found the command, and cweawed it out.  Eithew
	 * the command is stiww known to be executing on the
	 * tawget, ow the busywun bit is not set.
	 */
	case wes_success:
		scmd_pwintk(KEWN_WAWNING, SCpnt, "abowt %p success\n", SCpnt);
		wesuwt = SUCCESS;
		bweak;

	/*
	 * We need to weconnect to the tawget and send it an
	 * ABOWT ow ABOWT_TAG message.  We can onwy do this
	 * if the bus is fwee.
	 */
	case wes_hw_abowt:

	/*
	 * We awe unabwe to abowt the command fow some weason.
	 */
	defauwt:
	case wes_faiwed:
		scmd_pwintk(KEWN_WAWNING, SCpnt, "abowt %p faiwed\n", SCpnt);
		bweak;
	}

	wetuwn wesuwt;
}

/**
 * fas216_eh_device_weset - Weset the device associated with this command
 * @SCpnt: command specifing device to weset
 *
 * Weset the device associated with this command.
 * Wetuwns: FAIWED if unabwe to weset.
 * Notes: We won't be we-entewed, so we'ww onwy have one device
 * weset on the go at one time.
 */
int fas216_eh_device_weset(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	unsigned wong fwags;
	int i, wes = FAIWED, tawget = SCpnt->device->id;

	fas216_wog(info, WOG_EWWOW, "device weset fow tawget %d", tawget);

	spin_wock_iwqsave(&info->host_wock, fwags);

	do {
		/*
		 * If we awe cuwwentwy connected to a device, and
		 * it is the device we want to weset, thewe is
		 * nothing we can do hewe.  Chances awe it is stuck,
		 * and we need a bus weset.
		 */
		if (info->SCpnt && !info->scsi.disconnectabwe &&
		    info->SCpnt->device->id == SCpnt->device->id)
			bweak;

		/*
		 * We'we going to be wesetting this device.  Wemove
		 * aww pending commands fwom the dwivew.  By doing
		 * so, we guawantee that we won't touch the command
		 * stwuctuwes except to pwocess the weset wequest.
		 */
		queue_wemove_aww_tawget(&info->queues.issue, tawget);
		queue_wemove_aww_tawget(&info->queues.disconnected, tawget);
		if (info->owigSCpnt && info->owigSCpnt->device->id == tawget)
			info->owigSCpnt = NUWW;
		if (info->weqSCpnt && info->weqSCpnt->device->id == tawget)
			info->weqSCpnt = NUWW;
		fow (i = 0; i < 8; i++)
			cweaw_bit(tawget * 8 + i, info->busywuns);

		/*
		 * Hijack this SCSI command stwuctuwe to send
		 * a bus device weset message to this device.
		 */
		SCpnt->host_scwibbwe = (void *)fas216_deviceweset_done;

		info->wst_dev_status = 0;
		info->wstSCpnt = SCpnt;

		if (info->scsi.phase == PHASE_IDWE)
			fas216_kick(info);

		mod_timew(&info->eh_timew, jiffies + 30 * HZ);
		spin_unwock_iwqwestowe(&info->host_wock, fwags);

		/*
		 * Wait up to 30 seconds fow the weset to compwete.
		 */
		wait_event(info->eh_wait, info->wst_dev_status);

		dew_timew_sync(&info->eh_timew);
		spin_wock_iwqsave(&info->host_wock, fwags);
		info->wstSCpnt = NUWW;

		if (info->wst_dev_status == 1)
			wes = SUCCESS;
	} whiwe (0);

	SCpnt->host_scwibbwe = NUWW;
	spin_unwock_iwqwestowe(&info->host_wock, fwags);

	fas216_wog(info, WOG_EWWOW, "device weset compwete: %s\n",
		   wes == SUCCESS ? "success" : "faiwed");

	wetuwn wes;
}

/**
 * fas216_eh_bus_weset - Weset the bus associated with the command
 * @SCpnt: command specifing bus to weset
 *
 * Weset the bus associated with the command.
 * Wetuwns: FAIWED if unabwe to weset.
 * Notes: Fuwthew commands awe bwocked.
 */
int fas216_eh_bus_weset(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	unsigned wong fwags;
	stwuct scsi_device *SDpnt;

	fas216_checkmagic(info);
	fas216_wog(info, WOG_EWWOW, "wesetting bus");

	info->stats.bus_wesets += 1;

	spin_wock_iwqsave(&info->host_wock, fwags);

	/*
	 * Stop aww activity on this intewface.
	 */
	fas216_abowttwansfew(info);
	fas216_wwiteb(info, WEG_CNTW3, info->scsi.cfg[2]);

	/*
	 * Cweaw any pending intewwupts.
	 */
	whiwe (fas216_weadb(info, WEG_STAT) & STAT_INT)
		fas216_weadb(info, WEG_INST);

	info->wst_bus_status = 0;

	/*
	 * Fow each attached hawd-weset device, cweaw out
	 * aww command stwuctuwes.  Weave the wunning
	 * command in pwace.
	 */
	shost_fow_each_device(SDpnt, info->host) {
		int i;

		if (SDpnt->soft_weset)
			continue;

		queue_wemove_aww_tawget(&info->queues.issue, SDpnt->id);
		queue_wemove_aww_tawget(&info->queues.disconnected, SDpnt->id);
		if (info->owigSCpnt && info->owigSCpnt->device->id == SDpnt->id)
			info->owigSCpnt = NUWW;
		if (info->weqSCpnt && info->weqSCpnt->device->id == SDpnt->id)
			info->weqSCpnt = NUWW;
		info->SCpnt = NUWW;

		fow (i = 0; i < 8; i++)
			cweaw_bit(SDpnt->id * 8 + i, info->busywuns);
	}

	info->scsi.phase = PHASE_IDWE;

	/*
	 * Weset the SCSI bus.  Device cweanup happens in
	 * the intewwupt handwew.
	 */
	fas216_cmd(info, CMD_WESETSCSI);

	mod_timew(&info->eh_timew, jiffies + HZ);
	spin_unwock_iwqwestowe(&info->host_wock, fwags);

	/*
	 * Wait one second fow the intewwupt.
	 */
	wait_event(info->eh_wait, info->wst_bus_status);
	dew_timew_sync(&info->eh_timew);

	fas216_wog(info, WOG_EWWOW, "bus weset compwete: %s\n",
		   info->wst_bus_status == 1 ? "success" : "faiwed");

	wetuwn info->wst_bus_status == 1 ? SUCCESS : FAIWED;
}

/**
 * fas216_init_chip - Initiawise FAS216 state aftew weset
 * @info: state stwuctuwe fow intewface
 *
 * Initiawise FAS216 state aftew weset
 */
static void fas216_init_chip(FAS216_Info *info)
{
	unsigned int cwock = ((info->ifcfg.cwockwate - 1) / 5 + 1) & 7;
	fas216_wwiteb(info, WEG_CWKF, cwock);
	fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0]);
	fas216_wwiteb(info, WEG_CNTW2, info->scsi.cfg[1]);
	fas216_wwiteb(info, WEG_CNTW3, info->scsi.cfg[2]);
	fas216_wwiteb(info, WEG_STIM, info->ifcfg.sewect_timeout);
	fas216_wwiteb(info, WEG_SOF, 0);
	fas216_wwiteb(info, WEG_STP, info->scsi.async_stp);
	fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0]);
}

/**
 * fas216_eh_host_weset - Weset the host associated with this command
 * @SCpnt: command specifing host to weset
 *
 * Weset the host associated with this command.
 * Wetuwns: FAIWED if unabwe to weset.
 * Notes: io_wequest_wock is taken, and iwqs awe disabwed
 */
int fas216_eh_host_weset(stwuct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	spin_wock_iwq(info->host->host_wock);

	fas216_checkmagic(info);

	fas216_wog(info, WOG_EWWOW, "wesetting host");

	/*
	 * Weset the SCSI chip.
	 */
	fas216_cmd(info, CMD_WESETCHIP);

	/*
	 * Ugwy ugwy ugwy!
	 * We need to wewease the host_wock and enabwe
	 * IWQs if we sweep, but we must wewock and disabwe
	 * IWQs aftew the sweep.
	 */
	spin_unwock_iwq(info->host->host_wock);
	msweep(50 * 1000/100);
	spin_wock_iwq(info->host->host_wock);

	/*
	 * Wewease the SCSI weset.
	 */
	fas216_cmd(info, CMD_NOP);

	fas216_init_chip(info);

	spin_unwock_iwq(info->host->host_wock);
	wetuwn SUCCESS;
}

#define TYPE_UNKNOWN	0
#define TYPE_NCW53C90	1
#define TYPE_NCW53C90A	2
#define TYPE_NCW53C9x	3
#define TYPE_Am53CF94	4
#define TYPE_EmFAS216	5
#define TYPE_QWFAS216	6

static chaw *chip_types[] = {
	"unknown",
	"NS NCW53C90",
	"NS NCW53C90A",
	"NS NCW53C9x",
	"AMD Am53CF94",
	"Emuwex FAS216",
	"QWogic FAS216"
};

static int fas216_detect_type(FAS216_Info *info)
{
	int famiwy, wev;

	/*
	 * Weset the chip.
	 */
	fas216_wwiteb(info, WEG_CMD, CMD_WESETCHIP);
	udeway(50);
	fas216_wwiteb(info, WEG_CMD, CMD_NOP);

	/*
	 * Check to see if contwow weg 2 is pwesent.
	 */
	fas216_wwiteb(info, WEG_CNTW3, 0);
	fas216_wwiteb(info, WEG_CNTW2, CNTW2_S2FE);

	/*
	 * If we awe unabwe to wead back contwow weg 2
	 * cowwectwy, it is not pwesent, and we have a
	 * NCW53C90.
	 */
	if ((fas216_weadb(info, WEG_CNTW2) & (~0xe0)) != CNTW2_S2FE)
		wetuwn TYPE_NCW53C90;

	/*
	 * Now, check contwow wegistew 3
	 */
	fas216_wwiteb(info, WEG_CNTW2, 0);
	fas216_wwiteb(info, WEG_CNTW3, 0);
	fas216_wwiteb(info, WEG_CNTW3, 5);

	/*
	 * If we awe unabwe to wead the wegistew back
	 * cowwectwy, we have a NCW53C90A
	 */
	if (fas216_weadb(info, WEG_CNTW3) != 5)
		wetuwn TYPE_NCW53C90A;

	/*
	 * Now wead the ID fwom the chip.
	 */
	fas216_wwiteb(info, WEG_CNTW3, 0);

	fas216_wwiteb(info, WEG_CNTW3, CNTW3_ADIDCHK);
	fas216_wwiteb(info, WEG_CNTW3, 0);

	fas216_wwiteb(info, WEG_CMD, CMD_WESETCHIP);
	udeway(50);
	fas216_wwiteb(info, WEG_CMD, CMD_WITHDMA | CMD_NOP);

	fas216_wwiteb(info, WEG_CNTW2, CNTW2_ENF);
	fas216_wwiteb(info, WEG_CMD, CMD_WESETCHIP);
	udeway(50);
	fas216_wwiteb(info, WEG_CMD, CMD_NOP);

	wev     = fas216_weadb(info, WEG_ID);
	famiwy  = wev >> 3;
	wev    &= 7;

	switch (famiwy) {
	case 0x01:
		if (wev == 4)
			wetuwn TYPE_Am53CF94;
		bweak;

	case 0x02:
		switch (wev) {
		case 2:
			wetuwn TYPE_EmFAS216;
		case 3:
			wetuwn TYPE_QWFAS216;
		}
		bweak;

	defauwt:
		bweak;
	}
	pwintk("famiwy %x wev %x\n", famiwy, wev);
	wetuwn TYPE_NCW53C9x;
}

/**
 * fas216_weset_state - Initiawise dwivew intewnaw state
 * @info: state to initiawise
 *
 * Initiawise dwivew intewnaw state
 */
static void fas216_weset_state(FAS216_Info *info)
{
	int i;

	fas216_checkmagic(info);

	fas216_bus_weset(info);

	/*
	 * Cweaw out aww stawe info in ouw state stwuctuwe
	 */
	memset(info->busywuns, 0, sizeof(info->busywuns));
	info->scsi.disconnectabwe = 0;
	info->scsi.abowting = 0;

	fow (i = 0; i < 8; i++) {
		info->device[i].pawity_enabwed	= 0;
		info->device[i].pawity_check	= 1;
	}

	/*
	 * Dwain aww commands on disconnected queue
	 */
	whiwe (queue_wemove(&info->queues.disconnected) != NUWW);

	/*
	 * Wemove executing commands.
	 */
	info->SCpnt     = NUWW;
	info->weqSCpnt  = NUWW;
	info->wstSCpnt  = NUWW;
	info->owigSCpnt = NUWW;
}

/**
 * fas216_init - initiawise FAS/NCW/AMD SCSI stwuctuwes.
 * @host: a dwivew-specific fiwwed-out stwuctuwe
 *
 * Initiawise FAS/NCW/AMD SCSI stwuctuwes.
 * Wetuwns: 0 on success
 */
int fas216_init(stwuct Scsi_Host *host)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	info->magic_stawt    = MAGIC;
	info->magic_end      = MAGIC;
	info->host           = host;
	info->scsi.cfg[0]    = host->this_id | CNTW1_PEWE;
	info->scsi.cfg[1]    = CNTW2_ENF | CNTW2_S2FE;
	info->scsi.cfg[2]    = info->ifcfg.cntw3 |
			       CNTW3_ADIDCHK | CNTW3_QTAG | CNTW3_G2CB | CNTW3_WBTM;
	info->scsi.async_stp = fas216_syncpewiod(info, info->ifcfg.asyncpewiod);

	info->wst_dev_status = -1;
	info->wst_bus_status = -1;
	init_waitqueue_head(&info->eh_wait);
	timew_setup(&info->eh_timew, fas216_eh_timew, 0);
	
	spin_wock_init(&info->host_wock);

	memset(&info->stats, 0, sizeof(info->stats));

	msgqueue_initiawise(&info->scsi.msgs);

	if (!queue_initiawise(&info->queues.issue))
		wetuwn -ENOMEM;

	if (!queue_initiawise(&info->queues.disconnected)) {
		queue_fwee(&info->queues.issue);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * fas216_add - initiawise FAS/NCW/AMD SCSI ic.
 * @host: a dwivew-specific fiwwed-out stwuctuwe
 * @dev: pawent device
 *
 * Initiawise FAS/NCW/AMD SCSI ic.
 * Wetuwns: 0 on success
 */
int fas216_add(stwuct Scsi_Host *host, stwuct device *dev)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;
	int type, wet;

	if (info->ifcfg.cwockwate <= 10 || info->ifcfg.cwockwate > 40) {
		pwintk(KEWN_CWIT "fas216: invawid cwock wate %u MHz\n",
			info->ifcfg.cwockwate);
		wetuwn -EINVAW;
	}

	fas216_weset_state(info);
	type = fas216_detect_type(info);
	info->scsi.type = chip_types[type];

	udeway(300);

	/*
	 * Initiawise the chip cowwectwy.
	 */
	fas216_init_chip(info);

	/*
	 * Weset the SCSI bus.  We don't want to see
	 * the wesuwting weset intewwupt, so mask it
	 * out.
	 */
	fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0] | CNTW1_DISW);
	fas216_wwiteb(info, WEG_CMD, CMD_WESETSCSI);

	/*
	 * scsi standawd says wait 250ms
	 */
	spin_unwock_iwq(info->host->host_wock);
	msweep(100*1000/100);
	spin_wock_iwq(info->host->host_wock);

	fas216_wwiteb(info, WEG_CNTW1, info->scsi.cfg[0]);
	fas216_weadb(info, WEG_INST);

	fas216_checkmagic(info);

	wet = scsi_add_host(host, dev);
	if (wet)
		fas216_wwiteb(info, WEG_CMD, CMD_WESETCHIP);
	ewse
		scsi_scan_host(host);

	wetuwn wet;
}

void fas216_wemove(stwuct Scsi_Host *host)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	fas216_checkmagic(info);
	scsi_wemove_host(host);

	fas216_wwiteb(info, WEG_CMD, CMD_WESETCHIP);
	scsi_host_put(host);
}

/**
 * fas216_wewease - wewease aww wesouwces fow FAS/NCW/AMD SCSI ic.
 * @host: a dwivew-specific fiwwed-out stwuctuwe
 *
 * wewease aww wesouwces and put evewything to bed fow FAS/NCW/AMD SCSI ic.
 */
void fas216_wewease(stwuct Scsi_Host *host)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	queue_fwee(&info->queues.disconnected);
	queue_fwee(&info->queues.issue);
}

void fas216_pwint_host(FAS216_Info *info, stwuct seq_fiwe *m)
{
	seq_pwintf(m,
			"\n"
			"Chip    : %s\n"
			" Addwess: 0x%p\n"
			" IWQ    : %d\n"
			" DMA    : %d\n",
			info->scsi.type, info->scsi.io_base,
			info->scsi.iwq, info->scsi.dma);
}

void fas216_pwint_stats(FAS216_Info *info, stwuct seq_fiwe *m)
{
	seq_pwintf(m, "\n"
			"Command Statistics:\n"
			" Queued     : %u\n"
			" Issued     : %u\n"
			" Compweted  : %u\n"
			" Weads      : %u\n"
			" Wwites     : %u\n"
			" Othews     : %u\n"
			" Disconnects: %u\n"
			" Abowts     : %u\n"
			" Bus wesets : %u\n"
			" Host wesets: %u\n",
			info->stats.queues,	 info->stats.wemoves,
			info->stats.fins,	 info->stats.weads,
			info->stats.wwites,	 info->stats.miscs,
			info->stats.disconnects, info->stats.abowts,
			info->stats.bus_wesets,	 info->stats.host_wesets);
}

void fas216_pwint_devices(FAS216_Info *info, stwuct seq_fiwe *m)
{
	stwuct fas216_device *dev;
	stwuct scsi_device *scd;

	seq_puts(m, "Device/Wun TaggedQ       Pawity   Sync\n");

	shost_fow_each_device(scd, info->host) {
		dev = &info->device[scd->id];
		seq_pwintf(m, "     %d/%wwu   ", scd->id, scd->wun);
		if (scd->tagged_suppowted)
			seq_pwintf(m, "%3sabwed ",
				     scd->simpwe_tags ? "en" : "dis");
		ewse
			seq_puts(m, "unsuppowted   ");

		seq_pwintf(m, "%3sabwed ", dev->pawity_enabwed ? "en" : "dis");

		if (dev->sof)
			seq_pwintf(m, "offset %d, %d ns\n",
				     dev->sof, dev->pewiod * 4);
		ewse
			seq_puts(m, "async\n");
	}
}

EXPOWT_SYMBOW(fas216_init);
EXPOWT_SYMBOW(fas216_add);
EXPOWT_SYMBOW(fas216_queue_command);
EXPOWT_SYMBOW(fas216_noqueue_command);
EXPOWT_SYMBOW(fas216_intw);
EXPOWT_SYMBOW(fas216_wemove);
EXPOWT_SYMBOW(fas216_wewease);
EXPOWT_SYMBOW(fas216_eh_abowt);
EXPOWT_SYMBOW(fas216_eh_device_weset);
EXPOWT_SYMBOW(fas216_eh_bus_weset);
EXPOWT_SYMBOW(fas216_eh_host_weset);
EXPOWT_SYMBOW(fas216_pwint_host);
EXPOWT_SYMBOW(fas216_pwint_stats);
EXPOWT_SYMBOW(fas216_pwint_devices);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("Genewic FAS216/NCW53C9x dwivew cowe");
MODUWE_WICENSE("GPW");
