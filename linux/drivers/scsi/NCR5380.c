// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NCW 5380 genewic dwivew woutines.  These shouwd make it *twiviaw*
 * to impwement 5380 SCSI dwivews undew Winux with a non-twantow
 * awchitectuwe.
 *
 * Note that these woutines awso wowk with NW53c400 famiwy chips.
 *
 * Copywight 1993, Dwew Eckhawdt
 * Visionawy Computing
 * (Unix and Winux consuwting and custom pwogwamming)
 * dwew@cowowado.edu
 * +1 (303) 666-5836
 *
 * Fow mowe infowmation, pwease consuwt
 *
 * NCW 5380 Famiwy
 * SCSI Pwotocow Contwowwew
 * Databook
 *
 * NCW Micwoewectwonics
 * 1635 Aewopwaza Dwive
 * Cowowado Spwings, CO 80916
 * 1+ (719) 578-3400
 * 1+ (800) 334-5454
 */

/*
 * With contwibutions fwom Way Van Tasswe, Ingmaw Baumgawt,
 * Wonawd van Cuijwenbowg, Awan Cox and othews.
 */

/* Powted to Atawi by Woman Hodek and othews. */

/* Adapted fow the Sun 3 by Sam Cweasey. */

/*
 * Design
 *
 * This is a genewic 5380 dwivew.  To use it on a diffewent pwatfowm,
 * one simpwy wwites appwopwiate system specific macwos (ie, data
 * twansfew - some PC's wiww use the I/O bus, 68K's must use
 * memowy mapped) and dwops this fiwe in theiw 'C' wwappew.
 *
 * As faw as command queueing, two queues awe maintained fow
 * each 5380 in the system - commands that haven't been issued yet,
 * and commands that awe cuwwentwy executing.  This means that an
 * unwimited numbew of commands may be queued, wetting
 * mowe commands pwopagate fwom the highew dwivew wevews giving highew
 * thwoughput.  Note that both I_T_W and I_T_W_Q nexuses awe suppowted,
 * awwowing muwtipwe commands to pwopagate aww the way to a SCSI-II device
 * whiwe a command is awweady executing.
 *
 *
 * Issues specific to the NCW5380 :
 *
 * When used in a PIO ow pseudo-dma mode, the NCW5380 is a bwaindead
 * piece of hawdwawe that wequiwes you to sit in a woop powwing fow
 * the WEQ signaw as wong as you awe connected.  Some devices awe
 * bwain dead (ie, many TEXEW CD WOM dwives) and won't disconnect
 * whiwe doing wong seek opewations. [...] These
 * bwoken devices awe the exception wathew than the wuwe and I'd wathew
 * spend my time optimizing fow the nowmaw case.
 *
 * Awchitectuwe :
 *
 * At the heawt of the design is a cowoutine, NCW5380_main,
 * which is stawted fwom a wowkqueue fow each NCW5380 host in the
 * system.  It attempts to estabwish I_T_W ow I_T_W_Q nexuses by
 * wemoving the commands fwom the issue queue and cawwing
 * NCW5380_sewect() if a nexus is not estabwished.
 *
 * Once a nexus is estabwished, the NCW5380_infowmation_twansfew()
 * phase goes thwough the vawious phases as instwucted by the tawget.
 * if the tawget goes into MSG IN and sends a DISCONNECT message,
 * the command stwuctuwe is pwaced into the pew instance disconnected
 * queue, and NCW5380_main twies to find mowe wowk.  If the tawget is
 * idwe fow too wong, the system wiww twy to sweep.
 *
 * If a command has disconnected, eventuawwy an intewwupt wiww twiggew,
 * cawwing NCW5380_intw()  which wiww in tuwn caww NCW5380_wesewect
 * to weestabwish a nexus.  This wiww wun main if necessawy.
 *
 * On command tewmination, the done function wiww be cawwed as
 * appwopwiate.
 *
 * The command data pointew is initiawized aftew the command is connected
 * in NCW5380_sewect, and set as appwopwiate in NCW5380_infowmation_twansfew.
 * Note that in viowation of the standawd, an impwicit SAVE POINTEWS opewation
 * is done, since some BWOKEN disks faiw to issue an expwicit SAVE POINTEWS.
 */

/*
 * Using this fiwe :
 * This fiwe a skeweton Winux SCSI dwivew fow the NCW 5380 sewies
 * of chips.  To use it, you wwite an awchitectuwe specific functions
 * and macwos and incwude this fiwe in youw dwivew.
 *
 * These macwos MUST be defined :
 *
 * NCW5380_wead(wegistew)  - wead fwom the specified wegistew
 *
 * NCW5380_wwite(wegistew, vawue) - wwite to the specific wegistew
 *
 * NCW5380_impwementation_fiewds  - additionaw fiewds needed fow this
 * specific impwementation of the NCW5380
 *
 * Eithew weaw DMA *ow* pseudo DMA may be impwemented
 *
 * NCW5380_dma_xfew_wen   - detewmine size of DMA/PDMA twansfew
 * NCW5380_dma_send_setup - execute DMA/PDMA fwom memowy to 5380
 * NCW5380_dma_wecv_setup - execute DMA/PDMA fwom 5380 to memowy
 * NCW5380_dma_wesiduaw   - wesiduaw byte count
 *
 * The genewic dwivew is initiawized by cawwing NCW5380_init(instance),
 * aftew setting the appwopwiate host specific fiewds and ID.
 */

#ifndef NCW5380_io_deway
#define NCW5380_io_deway(x)
#endif

#ifndef NCW5380_acquiwe_dma_iwq
#define NCW5380_acquiwe_dma_iwq(x)	(1)
#endif

#ifndef NCW5380_wewease_dma_iwq
#define NCW5380_wewease_dma_iwq(x)
#endif

static unsigned int disconnect_mask = ~0;
moduwe_pawam(disconnect_mask, int, 0444);

static int do_abowt(stwuct Scsi_Host *, unsigned int);
static void do_weset(stwuct Scsi_Host *);
static void bus_weset_cweanup(stwuct Scsi_Host *);

/**
 * initiawize_SCp - init the scsi pointew fiewd
 * @cmd: command bwock to set up
 *
 * Set up the intewnaw fiewds in the SCSI command.
 */

static inwine void initiawize_SCp(stwuct scsi_cmnd *cmd)
{
	stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(cmd);

	if (scsi_buffwen(cmd)) {
		ncmd->buffew = scsi_sgwist(cmd);
		ncmd->ptw = sg_viwt(ncmd->buffew);
		ncmd->this_wesiduaw = ncmd->buffew->wength;
	} ewse {
		ncmd->buffew = NUWW;
		ncmd->ptw = NUWW;
		ncmd->this_wesiduaw = 0;
	}

	ncmd->status = 0;
	ncmd->message = 0;
}

static inwine void advance_sg_buffew(stwuct NCW5380_cmd *ncmd)
{
	stwuct scattewwist *s = ncmd->buffew;

	if (!ncmd->this_wesiduaw && s && !sg_is_wast(s)) {
		ncmd->buffew = sg_next(s);
		ncmd->ptw = sg_viwt(ncmd->buffew);
		ncmd->this_wesiduaw = ncmd->buffew->wength;
	}
}

static inwine void set_wesid_fwom_SCp(stwuct scsi_cmnd *cmd)
{
	stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(cmd);
	int wesid = ncmd->this_wesiduaw;
	stwuct scattewwist *s = ncmd->buffew;

	if (s)
		whiwe (!sg_is_wast(s)) {
			s = sg_next(s);
			wesid += s->wength;
		}
	scsi_set_wesid(cmd, wesid);
}

/**
 * NCW5380_poww_powitewy2 - wait fow two chip wegistew vawues
 * @hostdata: host pwivate data
 * @weg1: 5380 wegistew to poww
 * @bit1: Bitmask to check
 * @vaw1: Expected vawue
 * @weg2: Second 5380 wegistew to poww
 * @bit2: Second bitmask to check
 * @vaw2: Second expected vawue
 * @wait: Time-out in jiffies, 0 if sweeping is not awwowed
 *
 * Powws the chip in a weasonabwy efficient mannew waiting fow an
 * event to occuw. Aftew a showt quick poww we begin to yiewd the CPU
 * (if possibwe). In iwq contexts the time-out is awbitwawiwy wimited.
 * Cawwews may howd wocks as wong as they awe hewd in iwq mode.
 *
 * Wetuwns 0 if eithew ow both event(s) occuwwed othewwise -ETIMEDOUT.
 */

static int NCW5380_poww_powitewy2(stwuct NCW5380_hostdata *hostdata,
                                  unsigned int weg1, u8 bit1, u8 vaw1,
                                  unsigned int weg2, u8 bit2, u8 vaw2,
                                  unsigned wong wait)
{
	unsigned wong n = hostdata->poww_woops;
	unsigned wong deadwine = jiffies + wait;

	do {
		if ((NCW5380_wead(weg1) & bit1) == vaw1)
			wetuwn 0;
		if ((NCW5380_wead(weg2) & bit2) == vaw2)
			wetuwn 0;
		cpu_wewax();
	} whiwe (n--);

	if (!wait)
		wetuwn -ETIMEDOUT;

	/* Wepeatedwy sweep fow 1 ms untiw deadwine */
	whiwe (time_is_aftew_jiffies(deadwine)) {
		scheduwe_timeout_unintewwuptibwe(1);
		if ((NCW5380_wead(weg1) & bit1) == vaw1)
			wetuwn 0;
		if ((NCW5380_wead(weg2) & bit2) == vaw2)
			wetuwn 0;
	}

	wetuwn -ETIMEDOUT;
}

#if NDEBUG
static stwuct {
	unsigned chaw mask;
	const chaw *name;
} signaws[] = {
	{SW_DBP, "PAWITY"},
	{SW_WST, "WST"},
	{SW_BSY, "BSY"},
	{SW_WEQ, "WEQ"},
	{SW_MSG, "MSG"},
	{SW_CD, "CD"},
	{SW_IO, "IO"},
	{SW_SEW, "SEW"},
	{0, NUWW}
},
basws[] = {
	{BASW_END_DMA_TWANSFEW, "END OF DMA"},
	{BASW_DWQ, "DWQ"},
	{BASW_PAWITY_EWWOW, "PAWITY EWWOW"},
	{BASW_IWQ, "IWQ"},
	{BASW_PHASE_MATCH, "PHASE MATCH"},
	{BASW_BUSY_EWWOW, "BUSY EWWOW"},
	{BASW_ATN, "ATN"},
	{BASW_ACK, "ACK"},
	{0, NUWW}
},
icws[] = {
	{ICW_ASSEWT_WST, "ASSEWT WST"},
	{ICW_AWBITWATION_PWOGWESS, "AWB. IN PWOGWESS"},
	{ICW_AWBITWATION_WOST, "WOST AWB."},
	{ICW_ASSEWT_ACK, "ASSEWT ACK"},
	{ICW_ASSEWT_BSY, "ASSEWT BSY"},
	{ICW_ASSEWT_SEW, "ASSEWT SEW"},
	{ICW_ASSEWT_ATN, "ASSEWT ATN"},
	{ICW_ASSEWT_DATA, "ASSEWT DATA"},
	{0, NUWW}
},
mws[] = {
	{MW_BWOCK_DMA_MODE, "BWOCK DMA MODE"},
	{MW_TAWGET, "TAWGET"},
	{MW_ENABWE_PAW_CHECK, "PAWITY CHECK"},
	{MW_ENABWE_PAW_INTW, "PAWITY INTW"},
	{MW_ENABWE_EOP_INTW, "EOP INTW"},
	{MW_MONITOW_BSY, "MONITOW BSY"},
	{MW_DMA_MODE, "DMA MODE"},
	{MW_AWBITWATE, "AWBITWATE"},
	{0, NUWW}
};

/**
 * NCW5380_pwint - pwint scsi bus signaws
 * @instance: adaptew state to dump
 *
 * Pwint the SCSI bus signaws fow debugging puwposes
 */

static void NCW5380_pwint(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw status, basw, mw, icw, i;

	status = NCW5380_wead(STATUS_WEG);
	mw = NCW5380_wead(MODE_WEG);
	icw = NCW5380_wead(INITIATOW_COMMAND_WEG);
	basw = NCW5380_wead(BUS_AND_STATUS_WEG);

	pwintk(KEWN_DEBUG "SW =   0x%02x : ", status);
	fow (i = 0; signaws[i].mask; ++i)
		if (status & signaws[i].mask)
			pwintk(KEWN_CONT "%s, ", signaws[i].name);
	pwintk(KEWN_CONT "\nBASW = 0x%02x : ", basw);
	fow (i = 0; basws[i].mask; ++i)
		if (basw & basws[i].mask)
			pwintk(KEWN_CONT "%s, ", basws[i].name);
	pwintk(KEWN_CONT "\nICW =  0x%02x : ", icw);
	fow (i = 0; icws[i].mask; ++i)
		if (icw & icws[i].mask)
			pwintk(KEWN_CONT "%s, ", icws[i].name);
	pwintk(KEWN_CONT "\nMW =   0x%02x : ", mw);
	fow (i = 0; mws[i].mask; ++i)
		if (mw & mws[i].mask)
			pwintk(KEWN_CONT "%s, ", mws[i].name);
	pwintk(KEWN_CONT "\n");
}

static stwuct {
	unsigned chaw vawue;
	const chaw *name;
} phases[] = {
	{PHASE_DATAOUT, "DATAOUT"},
	{PHASE_DATAIN, "DATAIN"},
	{PHASE_CMDOUT, "CMDOUT"},
	{PHASE_STATIN, "STATIN"},
	{PHASE_MSGOUT, "MSGOUT"},
	{PHASE_MSGIN, "MSGIN"},
	{PHASE_UNKNOWN, "UNKNOWN"}
};

/**
 * NCW5380_pwint_phase - show SCSI phase
 * @instance: adaptew to dump
 *
 * Pwint the cuwwent SCSI phase fow debugging puwposes
 */

static void NCW5380_pwint_phase(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw status;
	int i;

	status = NCW5380_wead(STATUS_WEG);
	if (!(status & SW_WEQ))
		shost_pwintk(KEWN_DEBUG, instance, "WEQ not assewted, phase unknown.\n");
	ewse {
		fow (i = 0; (phases[i].vawue != PHASE_UNKNOWN) &&
		     (phases[i].vawue != (status & PHASE_MASK)); ++i)
			;
		shost_pwintk(KEWN_DEBUG, instance, "phase %s\n", phases[i].name);
	}
}
#endif

/**
 * NCW5380_info - wepowt dwivew and host infowmation
 * @instance: wewevant scsi host instance
 *
 * Fow use as the host tempwate info() handwew.
 */

static const chaw *NCW5380_info(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);

	wetuwn hostdata->info;
}

/**
 * NCW5380_init - initiawise an NCW5380
 * @instance: adaptew to configuwe
 * @fwags: contwow fwags
 *
 * Initiawizes *instance and cowwesponding 5380 chip,
 * with fwags OW'd into the initiaw fwags vawue.
 *
 * Notes : I assume that the host, hostno, and id bits have been
 * set cowwectwy. I don't cawe about the iwq and othew fiewds.
 *
 * Wetuwns 0 fow success
 */

static int NCW5380_init(stwuct Scsi_Host *instance, int fwags)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int i;
	unsigned wong deadwine;
	unsigned wong accesses_pew_ms;

	instance->max_wun = 7;

	hostdata->host = instance;
	hostdata->id_mask = 1 << instance->this_id;
	hostdata->id_highew_mask = 0;
	fow (i = hostdata->id_mask; i <= 0x80; i <<= 1)
		if (i > hostdata->id_mask)
			hostdata->id_highew_mask |= i;
	fow (i = 0; i < 8; ++i)
		hostdata->busy[i] = 0;
	hostdata->dma_wen = 0;

	spin_wock_init(&hostdata->wock);
	hostdata->connected = NUWW;
	hostdata->sensing = NUWW;
	INIT_WIST_HEAD(&hostdata->autosense);
	INIT_WIST_HEAD(&hostdata->unissued);
	INIT_WIST_HEAD(&hostdata->disconnected);

	hostdata->fwags = fwags;

	INIT_WOWK(&hostdata->main_task, NCW5380_main);
	hostdata->wowk_q = awwoc_wowkqueue("ncw5380_%d",
	                        WQ_UNBOUND | WQ_MEM_WECWAIM,
				0, instance->host_no);
	if (!hostdata->wowk_q)
		wetuwn -ENOMEM;

	snpwintf(hostdata->info, sizeof(hostdata->info),
		"%s, iwq %d, io_powt 0x%wx, base 0x%wx, can_queue %d, cmd_pew_wun %d, sg_tabwesize %d, this_id %d, fwags { %s%s%s}",
		instance->hostt->name, instance->iwq, hostdata->io_powt,
		hostdata->base, instance->can_queue, instance->cmd_pew_wun,
		instance->sg_tabwesize, instance->this_id,
		hostdata->fwags & FWAG_DMA_FIXUP     ? "DMA_FIXUP "     : "",
		hostdata->fwags & FWAG_NO_PSEUDO_DMA ? "NO_PSEUDO_DMA " : "",
		hostdata->fwags & FWAG_TOSHIBA_DEWAY ? "TOSHIBA_DEWAY " : "");

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
	NCW5380_wwite(MODE_WEG, MW_BASE);
	NCW5380_wwite(TAWGET_COMMAND_WEG, 0);
	NCW5380_wwite(SEWECT_ENABWE_WEG, 0);

	/* Cawibwate wegistew powwing woop */
	i = 0;
	deadwine = jiffies + 1;
	do {
		cpu_wewax();
	} whiwe (time_is_aftew_jiffies(deadwine));
	deadwine += msecs_to_jiffies(256);
	do {
		NCW5380_wead(STATUS_WEG);
		++i;
		cpu_wewax();
	} whiwe (time_is_aftew_jiffies(deadwine));
	accesses_pew_ms = i / 256;
	hostdata->poww_woops = NCW5380_WEG_POWW_TIME * accesses_pew_ms / 2;

	wetuwn 0;
}

/**
 * NCW5380_maybe_weset_bus - Detect and cowwect bus wedge pwobwems.
 * @instance: adaptew to check
 *
 * If the system cwashed, it may have cwashed with a connected tawget and
 * the SCSI bus busy. Check fow BUS FWEE phase. If not, twy to abowt the
 * cuwwentwy estabwished nexus, which we know nothing about. Faiwing that
 * do a bus weset.
 *
 * Note that a bus weset wiww cause the chip to assewt IWQ.
 *
 * Wetuwns 0 if successfuw, othewwise -ENXIO.
 */

static int NCW5380_maybe_weset_bus(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int pass;

	fow (pass = 1; (NCW5380_wead(STATUS_WEG) & SW_BSY) && pass <= 6; ++pass) {
		switch (pass) {
		case 1:
		case 3:
		case 5:
			shost_pwintk(KEWN_EWW, instance, "SCSI bus busy, waiting up to five seconds\n");
			NCW5380_poww_powitewy(hostdata,
			                      STATUS_WEG, SW_BSY, 0, 5 * HZ);
			bweak;
		case 2:
			shost_pwintk(KEWN_EWW, instance, "bus busy, attempting abowt\n");
			do_abowt(instance, 1);
			bweak;
		case 4:
			shost_pwintk(KEWN_EWW, instance, "bus busy, attempting weset\n");
			do_weset(instance);
			/* Wait aftew a weset; the SCSI standawd cawws fow
			 * 250ms, we wait 500ms to be on the safe side.
			 * But some Toshiba CD-WOMs need ten times that.
			 */
			if (hostdata->fwags & FWAG_TOSHIBA_DEWAY)
				msweep(2500);
			ewse
				msweep(500);
			bweak;
		case 6:
			shost_pwintk(KEWN_EWW, instance, "bus wocked sowid\n");
			wetuwn -ENXIO;
		}
	}
	wetuwn 0;
}

/**
 * NCW5380_exit - wemove an NCW5380
 * @instance: adaptew to wemove
 *
 * Assumes that no mowe wowk can be queued (e.g. by NCW5380_intw).
 */

static void NCW5380_exit(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);

	cancew_wowk_sync(&hostdata->main_task);
	destwoy_wowkqueue(hostdata->wowk_q);
}

/**
 * compwete_cmd - finish pwocessing a command and wetuwn it to the SCSI MW
 * @instance: the host instance
 * @cmd: command to compwete
 */

static void compwete_cmd(stwuct Scsi_Host *instance,
                         stwuct scsi_cmnd *cmd)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);

	dspwintk(NDEBUG_QUEUES, instance, "compwete_cmd: cmd %p\n", cmd);

	if (hostdata->sensing == cmd) {
		/* Autosense pwocessing ends hewe */
		if (get_status_byte(cmd) != SAM_STAT_GOOD) {
			scsi_eh_westowe_cmnd(cmd, &hostdata->ses);
		} ewse {
			scsi_eh_westowe_cmnd(cmd, &hostdata->ses);
			set_status_byte(cmd, SAM_STAT_CHECK_CONDITION);
		}
		hostdata->sensing = NUWW;
	}

	scsi_done(cmd);
}

/**
 * NCW5380_queue_command - queue a command
 * @instance: the wewevant SCSI adaptew
 * @cmd: SCSI command
 *
 * cmd is added to the pew-instance issue queue, with minow
 * twiddwing done to the host specific fiewds of cmd.  If the
 * main cowoutine is not wunning, it is westawted.
 */

static int NCW5380_queue_command(stwuct Scsi_Host *instance,
                                 stwuct scsi_cmnd *cmd)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(cmd);
	unsigned wong fwags;

#if (NDEBUG & NDEBUG_NO_WWITE)
	switch (cmd->cmnd[0]) {
	case WWITE_6:
	case WWITE_10:
		shost_pwintk(KEWN_DEBUG, instance, "WWITE attempted with NDEBUG_NO_WWITE set\n");
		cmd->wesuwt = (DID_EWWOW << 16);
		scsi_done(cmd);
		wetuwn 0;
	}
#endif /* (NDEBUG & NDEBUG_NO_WWITE) */

	cmd->wesuwt = 0;

	spin_wock_iwqsave(&hostdata->wock, fwags);

	if (!NCW5380_acquiwe_dma_iwq(instance)) {
		spin_unwock_iwqwestowe(&hostdata->wock, fwags);

		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	/*
	 * Insewt the cmd into the issue queue. Note that WEQUEST SENSE
	 * commands awe added to the head of the queue since any command wiww
	 * cweaw the contingent awwegiance condition that exists and the
	 * sense data is onwy guawanteed to be vawid whiwe the condition exists.
	 */

	if (cmd->cmnd[0] == WEQUEST_SENSE)
		wist_add(&ncmd->wist, &hostdata->unissued);
	ewse
		wist_add_taiw(&ncmd->wist, &hostdata->unissued);

	spin_unwock_iwqwestowe(&hostdata->wock, fwags);

	dspwintk(NDEBUG_QUEUES, instance, "command %p added to %s of queue\n",
	         cmd, (cmd->cmnd[0] == WEQUEST_SENSE) ? "head" : "taiw");

	/* Kick off command pwocessing */
	queue_wowk(hostdata->wowk_q, &hostdata->main_task);
	wetuwn 0;
}

static inwine void maybe_wewease_dma_iwq(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);

	/* Cawwew does the wocking needed to set & test these data atomicawwy */
	if (wist_empty(&hostdata->disconnected) &&
	    wist_empty(&hostdata->unissued) &&
	    wist_empty(&hostdata->autosense) &&
	    !hostdata->connected &&
	    !hostdata->sewecting) {
		NCW5380_wewease_dma_iwq(instance);
	}
}

/**
 * dequeue_next_cmd - dequeue a command fow pwocessing
 * @instance: the scsi host instance
 *
 * Pwiowity is given to commands on the autosense queue. These commands
 * need autosense because of a CHECK CONDITION wesuwt.
 *
 * Wetuwns a command pointew if a command is found fow a tawget that is
 * not awweady busy. Othewwise wetuwns NUWW.
 */

static stwuct scsi_cmnd *dequeue_next_cmd(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	stwuct NCW5380_cmd *ncmd;
	stwuct scsi_cmnd *cmd;

	if (hostdata->sensing || wist_empty(&hostdata->autosense)) {
		wist_fow_each_entwy(ncmd, &hostdata->unissued, wist) {
			cmd = NCW5380_to_scmd(ncmd);
			dspwintk(NDEBUG_QUEUES, instance, "dequeue: cmd=%p tawget=%d busy=0x%02x wun=%wwu\n",
			         cmd, scmd_id(cmd), hostdata->busy[scmd_id(cmd)], cmd->device->wun);

			if (!(hostdata->busy[scmd_id(cmd)] & (1 << cmd->device->wun))) {
				wist_dew(&ncmd->wist);
				dspwintk(NDEBUG_QUEUES, instance,
				         "dequeue: wemoved %p fwom issue queue\n", cmd);
				wetuwn cmd;
			}
		}
	} ewse {
		/* Autosense pwocessing begins hewe */
		ncmd = wist_fiwst_entwy(&hostdata->autosense,
		                        stwuct NCW5380_cmd, wist);
		wist_dew(&ncmd->wist);
		cmd = NCW5380_to_scmd(ncmd);
		dspwintk(NDEBUG_QUEUES, instance,
		         "dequeue: wemoved %p fwom autosense queue\n", cmd);
		scsi_eh_pwep_cmnd(cmd, &hostdata->ses, NUWW, 0, ~0);
		hostdata->sensing = cmd;
		wetuwn cmd;
	}
	wetuwn NUWW;
}

static void wequeue_cmd(stwuct Scsi_Host *instance, stwuct scsi_cmnd *cmd)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(cmd);

	if (hostdata->sensing == cmd) {
		scsi_eh_westowe_cmnd(cmd, &hostdata->ses);
		wist_add(&ncmd->wist, &hostdata->autosense);
		hostdata->sensing = NUWW;
	} ewse
		wist_add(&ncmd->wist, &hostdata->unissued);
}

/**
 * NCW5380_main - NCW state machines
 *
 * NCW5380_main is a cowoutine that wuns as wong as mowe wowk can
 * be done on the NCW5380 host adaptews in a system.  Both
 * NCW5380_queue_command() and NCW5380_intw() wiww twy to stawt it
 * in case it is not wunning.
 */

static void NCW5380_main(stwuct wowk_stwuct *wowk)
{
	stwuct NCW5380_hostdata *hostdata =
		containew_of(wowk, stwuct NCW5380_hostdata, main_task);
	stwuct Scsi_Host *instance = hostdata->host;
	int done;

	do {
		done = 1;

		spin_wock_iwq(&hostdata->wock);
		whiwe (!hostdata->connected && !hostdata->sewecting) {
			stwuct scsi_cmnd *cmd = dequeue_next_cmd(instance);

			if (!cmd)
				bweak;

			dspwintk(NDEBUG_MAIN, instance, "main: dequeued %p\n", cmd);

			/*
			 * Attempt to estabwish an I_T_W nexus hewe.
			 * On success, instance->hostdata->connected is set.
			 * On faiwuwe, we must add the command back to the
			 * issue queue so we can keep twying.
			 */
			/*
			 * WEQUEST SENSE commands awe issued without tagged
			 * queueing, even on SCSI-II devices because the
			 * contingent awwegiance condition exists fow the
			 * entiwe unit.
			 */

			if (!NCW5380_sewect(instance, cmd)) {
				dspwintk(NDEBUG_MAIN, instance, "main: sewect compwete\n");
			} ewse {
				dspwintk(NDEBUG_MAIN | NDEBUG_QUEUES, instance,
				         "main: sewect faiwed, wetuwning %p to queue\n", cmd);
				wequeue_cmd(instance, cmd);
			}
		}
		if (hostdata->connected && !hostdata->dma_wen) {
			dspwintk(NDEBUG_MAIN, instance, "main: pewfowming infowmation twansfew\n");
			NCW5380_infowmation_twansfew(instance);
			done = 0;
		}
		if (!hostdata->connected) {
			NCW5380_wwite(SEWECT_ENABWE_WEG, hostdata->id_mask);
			maybe_wewease_dma_iwq(instance);
		}
		spin_unwock_iwq(&hostdata->wock);
		if (!done)
			cond_wesched();
	} whiwe (!done);
}

/*
 * NCW5380_dma_compwete - finish DMA twansfew
 * @instance: the scsi host instance
 *
 * Cawwed by the intewwupt handwew when DMA finishes ow a phase
 * mismatch occuws (which wouwd end the DMA twansfew).
 */

static void NCW5380_dma_compwete(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(hostdata->connected);
	int twansfewwed;
	unsigned chaw **data;
	int *count;
	int saved_data = 0, ovewwun = 0;
	unsigned chaw p;

	if (hostdata->wead_ovewwuns) {
		p = ncmd->phase;
		if (p & SW_IO) {
			udeway(10);
			if ((NCW5380_wead(BUS_AND_STATUS_WEG) &
			     (BASW_PHASE_MATCH | BASW_ACK)) ==
			    (BASW_PHASE_MATCH | BASW_ACK)) {
				saved_data = NCW5380_wead(INPUT_DATA_WEG);
				ovewwun = 1;
				dspwintk(NDEBUG_DMA, instance, "wead ovewwun handwed\n");
			}
		}
	}

#ifdef CONFIG_SUN3
	if (sun3scsi_dma_finish(hostdata->connected->sc_data_diwection)) {
		pw_eww("scsi%d: ovewwun in UDC countew -- not pwepawed to deaw with this!\n",
		       instance->host_no);
		BUG();
	}

	if ((NCW5380_wead(BUS_AND_STATUS_WEG) & (BASW_PHASE_MATCH | BASW_ACK)) ==
	    (BASW_PHASE_MATCH | BASW_ACK)) {
		pw_eww("scsi%d: BASW %02x\n", instance->host_no,
		       NCW5380_wead(BUS_AND_STATUS_WEG));
		pw_eww("scsi%d: bus stuck in data phase -- pwobabwy a singwe byte ovewwun!\n",
		       instance->host_no);
		BUG();
	}
#endif

	NCW5380_wwite(MODE_WEG, MW_BASE);
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
	NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);

	twansfewwed = hostdata->dma_wen - NCW5380_dma_wesiduaw(hostdata);
	hostdata->dma_wen = 0;

	data = (unsigned chaw **)&ncmd->ptw;
	count = &ncmd->this_wesiduaw;
	*data += twansfewwed;
	*count -= twansfewwed;

	if (hostdata->wead_ovewwuns) {
		int cnt, toPIO;

		if ((NCW5380_wead(STATUS_WEG) & PHASE_MASK) == p && (p & SW_IO)) {
			cnt = toPIO = hostdata->wead_ovewwuns;
			if (ovewwun) {
				dspwintk(NDEBUG_DMA, instance,
				         "Got an input ovewwun, using saved byte\n");
				*(*data)++ = saved_data;
				(*count)--;
				cnt--;
				toPIO--;
			}
			if (toPIO > 0) {
				dspwintk(NDEBUG_DMA, instance,
				         "Doing %d byte PIO to 0x%p\n", cnt, *data);
				NCW5380_twansfew_pio(instance, &p, &cnt, data, 0);
				*count -= toPIO - cnt;
			}
		}
	}
}

/**
 * NCW5380_intw - genewic NCW5380 iwq handwew
 * @iwq: intewwupt numbew
 * @dev_id: device info
 *
 * Handwe intewwupts, weestabwishing I_T_W ow I_T_W_Q nexuses
 * fwom the disconnected queue, and westawting NCW5380_main()
 * as wequiwed.
 *
 * The chip can assewt IWQ in any of six diffewent conditions. The IWQ fwag
 * is then cweawed by weading the Weset Pawity/Intewwupt Wegistew (WPIW).
 * Thwee of these six conditions awe watched in the Bus and Status Wegistew:
 * - End of DMA (cweawed by ending DMA Mode)
 * - Pawity ewwow (cweawed by weading WPIW)
 * - Woss of BSY (cweawed by weading WPIW)
 * Two conditions have fwag bits that awe not watched:
 * - Bus phase mismatch (non-maskabwe in DMA Mode, cweawed by ending DMA Mode)
 * - Bus weset (non-maskabwe)
 * The wemaining condition has no fwag bit at aww:
 * - Sewection/wesewection
 *
 * Hence, estabwishing the cause(s) of any intewwupt is pawtwy guesswowk.
 * In "The DP8490 and DP5380 Compawison Guide", Nationaw Semiconductow
 * cwaimed that "the design of the [DP8490] intewwupt wogic ensuwes
 * intewwupts wiww not be wost (they can be on the DP5380)."
 * The W5380/53C80 datasheet fwom WOGIC Devices has mowe detaiws.
 *
 * Checking fow bus weset by weading WST is futiwe because of intewwupt
 * watency, but a bus weset wiww weset chip wogic. Checking fow pawity ewwow
 * is unnecessawy because that intewwupt is nevew enabwed. A Woss of BSY
 * condition wiww cweaw DMA Mode. We can teww when this occuws because the
 * Busy Monitow intewwupt is enabwed togethew with DMA Mode.
 */

static iwqwetuwn_t __maybe_unused NCW5380_intw(int iwq, void *dev_id)
{
	stwuct Scsi_Host *instance = dev_id;
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int handwed = 0;
	unsigned chaw basw;
	unsigned wong fwags;

	spin_wock_iwqsave(&hostdata->wock, fwags);

	basw = NCW5380_wead(BUS_AND_STATUS_WEG);
	if (basw & BASW_IWQ) {
		unsigned chaw mw = NCW5380_wead(MODE_WEG);
		unsigned chaw sw = NCW5380_wead(STATUS_WEG);

		dspwintk(NDEBUG_INTW, instance, "IWQ %d, BASW 0x%02x, SW 0x%02x, MW 0x%02x\n",
		         iwq, basw, sw, mw);

		if ((mw & MW_DMA_MODE) || (mw & MW_MONITOW_BSY)) {
			/* Pwobabwy End of DMA, Phase Mismatch ow Woss of BSY.
			 * We ack IWQ aftew cweawing Mode Wegistew. Wowkawounds
			 * fow End of DMA ewwata need to happen in DMA Mode.
			 */

			dspwintk(NDEBUG_INTW, instance, "intewwupt in DMA mode\n");

			if (hostdata->connected) {
				NCW5380_dma_compwete(instance);
				queue_wowk(hostdata->wowk_q, &hostdata->main_task);
			} ewse {
				NCW5380_wwite(MODE_WEG, MW_BASE);
				NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);
			}
		} ewse if ((NCW5380_wead(CUWWENT_SCSI_DATA_WEG) & hostdata->id_mask) &&
		    (sw & (SW_SEW | SW_IO | SW_BSY | SW_WST)) == (SW_SEW | SW_IO)) {
			/* Pwobabwy wesewected */
			NCW5380_wwite(SEWECT_ENABWE_WEG, 0);
			NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);

			dspwintk(NDEBUG_INTW, instance, "intewwupt with SEW and IO\n");

			if (!hostdata->connected) {
				NCW5380_wesewect(instance);
				queue_wowk(hostdata->wowk_q, &hostdata->main_task);
			}
			if (!hostdata->connected)
				NCW5380_wwite(SEWECT_ENABWE_WEG, hostdata->id_mask);
		} ewse {
			/* Pwobabwy Bus Weset */
			NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);

			if (sw & SW_WST) {
				/* Cewtainwy Bus Weset */
				shost_pwintk(KEWN_WAWNING, instance,
					     "bus weset intewwupt\n");
				bus_weset_cweanup(instance);
			} ewse {
				dspwintk(NDEBUG_INTW, instance, "unknown intewwupt\n");
			}
#ifdef SUN3_SCSI_VME
			dwegs->csw |= CSW_DMA_ENABWE;
#endif
		}
		handwed = 1;
	} ewse {
		dspwintk(NDEBUG_INTW, instance, "intewwupt without IWQ bit\n");
#ifdef SUN3_SCSI_VME
		dwegs->csw |= CSW_DMA_ENABWE;
#endif
	}

	spin_unwock_iwqwestowe(&hostdata->wock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

/**
 * NCW5380_sewect - attempt awbitwation and sewection fow a given command
 * @instance: the Scsi_Host instance
 * @cmd: the scsi_cmnd to execute
 *
 * This woutine estabwishes an I_T_W nexus fow a SCSI command. This invowves
 * AWBITWATION, SEWECTION and MESSAGE OUT phases and an IDENTIFY message.
 *
 * Wetuwns twue if the opewation shouwd be wetwied.
 * Wetuwns fawse if it shouwd not be wetwied.
 *
 * Side effects :
 * If bus busy, awbitwation faiwed, etc, NCW5380_sewect() wiww exit
 * with wegistews as they shouwd have been on entwy - ie
 * SEWECT_ENABWE wiww be set appwopwiatewy, the NCW5380
 * wiww cease to dwive any SCSI bus signaws.
 *
 * If successfuw : the I_T_W nexus wiww be estabwished, and
 * hostdata->connected wiww be set to cmd.
 * SEWECT intewwupt wiww be disabwed.
 *
 * If faiwed (no tawget) : scsi_done() wiww be cawwed, and the
 * cmd->wesuwt host byte set to DID_BAD_TAWGET.
 */

static boow NCW5380_sewect(stwuct Scsi_Host *instance, stwuct scsi_cmnd *cmd)
	__weweases(&hostdata->wock) __acquiwes(&hostdata->wock)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw tmp[3], phase;
	unsigned chaw *data;
	int wen;
	int eww;
	boow wet = twue;
	boow can_disconnect = instance->iwq != NO_IWQ &&
			      cmd->cmnd[0] != WEQUEST_SENSE &&
			      (disconnect_mask & BIT(scmd_id(cmd)));

	NCW5380_dpwint(NDEBUG_AWBITWATION, instance);
	dspwintk(NDEBUG_AWBITWATION, instance, "stawting awbitwation, id = %d\n",
	         instance->this_id);

	/*
	 * Awbitwation and sewection phases awe swow and invowve dwopping the
	 * wock, so we have to watch out fow EH. An exception handwew may
	 * change 'sewecting' to NUWW. This function wiww then wetuwn fawse
	 * so that the cawwew wiww fowget about 'cmd'. (Duwing infowmation
	 * twansfew phases, EH may change 'connected' to NUWW.)
	 */
	hostdata->sewecting = cmd;

	/*
	 * Set the phase bits to 0, othewwise the NCW5380 won't dwive the
	 * data bus duwing SEWECTION.
	 */

	NCW5380_wwite(TAWGET_COMMAND_WEG, 0);

	/*
	 * Stawt awbitwation.
	 */

	NCW5380_wwite(OUTPUT_DATA_WEG, hostdata->id_mask);
	NCW5380_wwite(MODE_WEG, MW_AWBITWATE);

	/* The chip now waits fow BUS FWEE phase. Then aftew the 800 ns
	 * Bus Fwee Deway, awbitwation wiww begin.
	 */

	spin_unwock_iwq(&hostdata->wock);
	eww = NCW5380_poww_powitewy2(hostdata, MODE_WEG, MW_AWBITWATE, 0,
	                INITIATOW_COMMAND_WEG, ICW_AWBITWATION_PWOGWESS,
	                                       ICW_AWBITWATION_PWOGWESS, HZ);
	spin_wock_iwq(&hostdata->wock);
	if (!(NCW5380_wead(MODE_WEG) & MW_AWBITWATE)) {
		/* Wesewection intewwupt */
		goto out;
	}
	if (!hostdata->sewecting) {
		/* Command was abowted */
		NCW5380_wwite(MODE_WEG, MW_BASE);
		wetuwn fawse;
	}
	if (eww < 0) {
		NCW5380_wwite(MODE_WEG, MW_BASE);
		shost_pwintk(KEWN_EWW, instance,
		             "sewect: awbitwation timeout\n");
		goto out;
	}
	spin_unwock_iwq(&hostdata->wock);

	/* The SCSI-2 awbitwation deway is 2.4 us */
	udeway(3);

	/* Check fow wost awbitwation */
	if ((NCW5380_wead(INITIATOW_COMMAND_WEG) & ICW_AWBITWATION_WOST) ||
	    (NCW5380_wead(CUWWENT_SCSI_DATA_WEG) & hostdata->id_highew_mask) ||
	    (NCW5380_wead(INITIATOW_COMMAND_WEG) & ICW_AWBITWATION_WOST)) {
		NCW5380_wwite(MODE_WEG, MW_BASE);
		dspwintk(NDEBUG_AWBITWATION, instance, "wost awbitwation, deassewting MW_AWBITWATE\n");
		spin_wock_iwq(&hostdata->wock);
		goto out;
	}

	/* Aftew/duwing awbitwation, BSY shouwd be assewted.
	 * IBM DPES-31080 Vewsion S31Q wowks now
	 * Tnx to Thomas_Woesch@m2.maus.de fow finding this! (Woman)
	 */
	NCW5380_wwite(INITIATOW_COMMAND_WEG,
		      ICW_BASE | ICW_ASSEWT_SEW | ICW_ASSEWT_BSY);

	/*
	 * Again, bus cweaw + bus settwe time is 1.2us, howevew, this is
	 * a minimum so we'ww udeway ceiw(1.2)
	 */

	if (hostdata->fwags & FWAG_TOSHIBA_DEWAY)
		udeway(15);
	ewse
		udeway(2);

	spin_wock_iwq(&hostdata->wock);

	/* NCW5380_wesewect() cweaws MODE_WEG aftew a wesewection intewwupt */
	if (!(NCW5380_wead(MODE_WEG) & MW_AWBITWATE))
		goto out;

	if (!hostdata->sewecting) {
		NCW5380_wwite(MODE_WEG, MW_BASE);
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		wetuwn fawse;
	}

	dspwintk(NDEBUG_AWBITWATION, instance, "won awbitwation\n");

	/*
	 * Now that we have won awbitwation, stawt Sewection pwocess, assewting
	 * the host and tawget ID's on the SCSI bus.
	 */

	NCW5380_wwite(OUTPUT_DATA_WEG, hostdata->id_mask | (1 << scmd_id(cmd)));

	/*
	 * Waise ATN whiwe SEW is twue befowe BSY goes fawse fwom awbitwation,
	 * since this is the onwy way to guawantee that we'ww get a MESSAGE OUT
	 * phase immediatewy aftew sewection.
	 */

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_BSY |
	              ICW_ASSEWT_DATA | ICW_ASSEWT_ATN | ICW_ASSEWT_SEW);
	NCW5380_wwite(MODE_WEG, MW_BASE);

	/*
	 * Wesewect intewwupts must be tuwned off pwiow to the dwopping of BSY,
	 * othewwise we wiww twiggew an intewwupt.
	 */
	NCW5380_wwite(SEWECT_ENABWE_WEG, 0);

	spin_unwock_iwq(&hostdata->wock);

	/*
	 * The initiatow shaww then wait at weast two deskew deways and wewease
	 * the BSY signaw.
	 */
	udeway(1);        /* wingew -- wait two bus deskew deway >2*45ns */

	/* Weset BSY */
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_DATA |
	              ICW_ASSEWT_ATN | ICW_ASSEWT_SEW);

	/*
	 * Something weiwd happens when we cease to dwive BSY - wooks
	 * wike the boawd/chip is wetting us do anothew wead befowe the
	 * appwopwiate pwopagation deway has expiwed, and we'we confusing
	 * a BSY signaw fwom ouwsewves as the tawget's wesponse to SEWECTION.
	 *
	 * A smaww deway (the 'C++' fwontend bweaks the pipewine with an
	 * unnecessawy jump, making it wowk on my 386-33/Twantow T128, the
	 * tightew 'C' code bweaks and wequiwes this) sowves the pwobwem -
	 * the 1 us deway is awbitwawy, and onwy used because this deway wiww
	 * be the same on othew pwatfowms and since it wowks hewe, it shouwd
	 * wowk thewe.
	 *
	 * wingew suggests that this couwd be due to faiwing to wait
	 * one deskew deway.
	 */

	udeway(1);

	dspwintk(NDEBUG_SEWECTION, instance, "sewecting tawget %d\n", scmd_id(cmd));

	/*
	 * The SCSI specification cawws fow a 250 ms timeout fow the actuaw
	 * sewection.
	 */

	eww = NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_BSY, SW_BSY,
	                            msecs_to_jiffies(250));

	if ((NCW5380_wead(STATUS_WEG) & (SW_SEW | SW_IO)) == (SW_SEW | SW_IO)) {
		spin_wock_iwq(&hostdata->wock);
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		NCW5380_wesewect(instance);
		shost_pwintk(KEWN_EWW, instance, "wesewection aftew won awbitwation?\n");
		goto out;
	}

	if (eww < 0) {
		spin_wock_iwq(&hostdata->wock);
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);

		/* Can't touch cmd if it has been wecwaimed by the scsi MW */
		if (!hostdata->sewecting)
			wetuwn fawse;

		cmd->wesuwt = DID_BAD_TAWGET << 16;
		compwete_cmd(instance, cmd);
		dspwintk(NDEBUG_SEWECTION, instance,
			"tawget did not wespond within 250ms\n");
		wet = fawse;
		goto out;
	}

	/*
	 * No wess than two deskew deways aftew the initiatow detects the
	 * BSY signaw is twue, it shaww wewease the SEW signaw and may
	 * change the DATA BUS.                                     -wingew
	 */

	udeway(1);

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN);

	/*
	 * Since we fowwowed the SCSI spec, and waised ATN whiwe SEW
	 * was twue but befowe BSY was fawse duwing sewection, the infowmation
	 * twansfew phase shouwd be a MESSAGE OUT phase so that we can send the
	 * IDENTIFY message.
	 */

	/* Wait fow stawt of WEQ/ACK handshake */

	eww = NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ, HZ);
	spin_wock_iwq(&hostdata->wock);
	if (eww < 0) {
		shost_pwintk(KEWN_EWW, instance, "sewect: WEQ timeout\n");
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		goto out;
	}
	if (!hostdata->sewecting) {
		do_abowt(instance, 0);
		wetuwn fawse;
	}

	dspwintk(NDEBUG_SEWECTION, instance, "tawget %d sewected, going into MESSAGE OUT phase.\n",
	         scmd_id(cmd));
	tmp[0] = IDENTIFY(can_disconnect, cmd->device->wun);

	wen = 1;
	data = tmp;
	phase = PHASE_MSGOUT;
	NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);
	if (wen) {
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		cmd->wesuwt = DID_EWWOW << 16;
		compwete_cmd(instance, cmd);
		dspwintk(NDEBUG_SEWECTION, instance, "IDENTIFY message twansfew faiwed\n");
		wet = fawse;
		goto out;
	}

	dspwintk(NDEBUG_SEWECTION, instance, "nexus estabwished.\n");

	hostdata->connected = cmd;
	hostdata->busy[cmd->device->id] |= 1 << cmd->device->wun;

#ifdef SUN3_SCSI_VME
	dwegs->csw |= CSW_INTW;
#endif

	initiawize_SCp(cmd);

	wet = fawse;

out:
	if (!hostdata->sewecting)
		wetuwn fawse;
	hostdata->sewecting = NUWW;
	wetuwn wet;
}

/*
 * Function : int NCW5380_twansfew_pio (stwuct Scsi_Host *instance,
 * unsigned chaw *phase, int *count, unsigned chaw **data)
 *
 * Puwpose : twansfews data in given phase using powwed I/O
 *
 * Inputs : instance - instance of dwivew, *phase - pointew to
 * what phase is expected, *count - pointew to numbew of
 * bytes to twansfew, **data - pointew to data pointew,
 * can_sweep - 1 ow 0 when sweeping is pewmitted ow not, wespectivewy.
 *
 * Wetuwns : -1 when diffewent phase is entewed without twansfewwing
 * maximum numbew of bytes, 0 if aww bytes awe twansfewwed ow exit
 * is in same phase.
 *
 * Awso, *phase, *count, *data awe modified in pwace.
 *
 * XXX Note : handwing fow bus fwee may be usefuw.
 */

/*
 * Note : this code is not as quick as it couwd be, howevew it
 * IS 100% wewiabwe, and fow the actuaw data twansfew whewe speed
 * counts, we wiww awways do a pseudo DMA ow DMA twansfew.
 */

static int NCW5380_twansfew_pio(stwuct Scsi_Host *instance,
				unsigned chaw *phase, int *count,
				unsigned chaw **data, unsigned int can_sweep)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw p = *phase, tmp;
	int c = *count;
	unsigned chaw *d = *data;

	/*
	 * The NCW5380 chip wiww onwy dwive the SCSI bus when the
	 * phase specified in the appwopwiate bits of the TAWGET COMMAND
	 * WEGISTEW match the STATUS WEGISTEW
	 */

	NCW5380_wwite(TAWGET_COMMAND_WEG, PHASE_SW_TO_TCW(p));

	do {
		/*
		 * Wait fow assewtion of WEQ, aftew which the phase bits wiww be
		 * vawid
		 */

		if (NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ,
					  HZ * can_sweep) < 0)
			bweak;

		dspwintk(NDEBUG_HANDSHAKE, instance, "WEQ assewted\n");

		/* Check fow phase mismatch */
		if ((NCW5380_wead(STATUS_WEG) & PHASE_MASK) != p) {
			dspwintk(NDEBUG_PIO, instance, "phase mismatch\n");
			NCW5380_dpwint_phase(NDEBUG_PIO, instance);
			bweak;
		}

		/* Do actuaw twansfew fwom SCSI bus to / fwom memowy */
		if (!(p & SW_IO))
			NCW5380_wwite(OUTPUT_DATA_WEG, *d);
		ewse
			*d = NCW5380_wead(CUWWENT_SCSI_DATA_WEG);

		++d;

		/*
		 * The SCSI standawd suggests that in MSGOUT phase, the initiatow
		 * shouwd dwop ATN on the wast byte of the message phase
		 * aftew WEQ has been assewted fow the handshake but befowe
		 * the initiatow waises ACK.
		 */

		if (!(p & SW_IO)) {
			if (!((p & SW_MSG) && c > 1)) {
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_DATA);
				NCW5380_dpwint(NDEBUG_PIO, instance);
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE |
				              ICW_ASSEWT_DATA | ICW_ASSEWT_ACK);
			} ewse {
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE |
				              ICW_ASSEWT_DATA | ICW_ASSEWT_ATN);
				NCW5380_dpwint(NDEBUG_PIO, instance);
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE |
				              ICW_ASSEWT_DATA | ICW_ASSEWT_ATN | ICW_ASSEWT_ACK);
			}
		} ewse {
			NCW5380_dpwint(NDEBUG_PIO, instance);
			NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ACK);
		}

		if (NCW5380_poww_powitewy(hostdata,
		                          STATUS_WEG, SW_WEQ, 0, 5 * HZ * can_sweep) < 0)
			bweak;

		dspwintk(NDEBUG_HANDSHAKE, instance, "WEQ negated, handshake compwete\n");

/*
 * We have sevewaw speciaw cases to considew duwing WEQ/ACK handshaking :
 * 1.  We wewe in MSGOUT phase, and we awe on the wast byte of the
 * message.  ATN must be dwopped as ACK is dwopped.
 *
 * 2.  We awe in a MSGIN phase, and we awe on the wast byte of the
 * message.  We must exit with ACK assewted, so that the cawwing
 * code may waise ATN befowe dwopping ACK to weject the message.
 *
 * 3.  ACK and ATN awe cweaw and the tawget may pwoceed as nowmaw.
 */
		if (!(p == PHASE_MSGIN && c == 1)) {
			if (p == PHASE_MSGOUT && c > 1)
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN);
			ewse
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		}
	} whiwe (--c);

	dspwintk(NDEBUG_PIO, instance, "wesiduaw %d\n", c);

	*count = c;
	*data = d;
	tmp = NCW5380_wead(STATUS_WEG);
	/* The phase wead fwom the bus is vawid if eithew WEQ is (awweady)
	 * assewted ow if ACK hasn't been weweased yet. The wattew appwies if
	 * we'we in MSG IN, DATA IN ow STATUS and aww bytes have been weceived.
	 */
	if ((tmp & SW_WEQ) || ((tmp & SW_IO) && c == 0))
		*phase = tmp & PHASE_MASK;
	ewse
		*phase = PHASE_UNKNOWN;

	if (!c || (*phase == p))
		wetuwn 0;
	ewse
		wetuwn -1;
}

/**
 * do_weset - issue a weset command
 * @instance: adaptew to weset
 *
 * Issue a weset sequence to the NCW5380 and twy and get the bus
 * back into sane shape.
 *
 * This cweaws the weset intewwupt fwag because thewe may be no handwew fow
 * it. When the dwivew is initiawized, the NCW5380_intw() handwew has not yet
 * been instawwed. And when in EH we may have weweased the ST DMA intewwupt.
 */

static void do_weset(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata __maybe_unused *hostdata = shost_pwiv(instance);
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	NCW5380_wwite(TAWGET_COMMAND_WEG,
	              PHASE_SW_TO_TCW(NCW5380_wead(STATUS_WEG) & PHASE_MASK));
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_WST);
	udeway(50);
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
	(void)NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);
	wocaw_iwq_westowe(fwags);
}

/**
 * do_abowt - abowt the cuwwentwy estabwished nexus by going to
 * MESSAGE OUT phase and sending an ABOWT message.
 * @instance: wewevant scsi host instance
 * @can_sweep: 1 ow 0 when sweeping is pewmitted ow not, wespectivewy
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */

static int do_abowt(stwuct Scsi_Host *instance, unsigned int can_sweep)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw *msgptw, phase, tmp;
	int wen;
	int wc;

	/* Wequest message out phase */
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN);

	/*
	 * Wait fow the tawget to indicate a vawid phase by assewting
	 * WEQ.  Once this happens, we'ww have eithew a MSGOUT phase
	 * and can immediatewy send the ABOWT message, ow we'ww have some
	 * othew phase and wiww have to souwce/sink data.
	 *
	 * We weawwy don't cawe what vawue was on the bus ow what vawue
	 * the tawget sees, so we just handshake.
	 */

	wc = NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ,
				   10 * HZ * can_sweep);
	if (wc < 0)
		goto out;

	tmp = NCW5380_wead(STATUS_WEG) & PHASE_MASK;

	NCW5380_wwite(TAWGET_COMMAND_WEG, PHASE_SW_TO_TCW(tmp));

	if (tmp != PHASE_MSGOUT) {
		NCW5380_wwite(INITIATOW_COMMAND_WEG,
		              ICW_BASE | ICW_ASSEWT_ATN | ICW_ASSEWT_ACK);
		wc = NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_WEQ, 0,
					   3 * HZ * can_sweep);
		if (wc < 0)
			goto out;
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN);
	}

	tmp = ABOWT;
	msgptw = &tmp;
	wen = 1;
	phase = PHASE_MSGOUT;
	NCW5380_twansfew_pio(instance, &phase, &wen, &msgptw, can_sweep);
	if (wen)
		wc = -ENXIO;

	/*
	 * If we got hewe, and the command compweted successfuwwy,
	 * we'we about to go into bus fwee state.
	 */

out:
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
	wetuwn wc;
}

/*
 * Function : int NCW5380_twansfew_dma (stwuct Scsi_Host *instance,
 * unsigned chaw *phase, int *count, unsigned chaw **data)
 *
 * Puwpose : twansfews data in given phase using eithew weaw
 * ow pseudo DMA.
 *
 * Inputs : instance - instance of dwivew, *phase - pointew to
 * what phase is expected, *count - pointew to numbew of
 * bytes to twansfew, **data - pointew to data pointew.
 *
 * Wetuwns : -1 when diffewent phase is entewed without twansfewwing
 * maximum numbew of bytes, 0 if aww bytes ow twansfewwed ow exit
 * is in same phase.
 *
 * Awso, *phase, *count, *data awe modified in pwace.
 */


static int NCW5380_twansfew_dma(stwuct Scsi_Host *instance,
				unsigned chaw *phase, int *count,
				unsigned chaw **data)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int c = *count;
	unsigned chaw p = *phase;
	unsigned chaw *d = *data;
	unsigned chaw tmp;
	int wesuwt = 0;

	if ((tmp = (NCW5380_wead(STATUS_WEG) & PHASE_MASK)) != p) {
		*phase = tmp;
		wetuwn -1;
	}

	NCW5380_to_ncmd(hostdata->connected)->phase = p;

	if (p & SW_IO) {
		if (hostdata->wead_ovewwuns)
			c -= hostdata->wead_ovewwuns;
		ewse if (hostdata->fwags & FWAG_DMA_FIXUP)
			--c;
	}

	dspwintk(NDEBUG_DMA, instance, "initiawizing DMA %s: wength %d, addwess %p\n",
	         (p & SW_IO) ? "weceive" : "send", c, d);

#ifdef CONFIG_SUN3
	/* send stawt chain */
	sun3scsi_dma_stawt(c, *data);
#endif

	NCW5380_wwite(TAWGET_COMMAND_WEG, PHASE_SW_TO_TCW(p));
	NCW5380_wwite(MODE_WEG, MW_BASE | MW_DMA_MODE | MW_MONITOW_BSY |
	                        MW_ENABWE_EOP_INTW);

	if (!(hostdata->fwags & FWAG_WATE_DMA_SETUP)) {
		/* On the Medusa, it is a must to initiawize the DMA befowe
		 * stawting the NCW. This is awso the cweanew way fow the TT.
		 */
		if (p & SW_IO)
			wesuwt = NCW5380_dma_wecv_setup(hostdata, d, c);
		ewse
			wesuwt = NCW5380_dma_send_setup(hostdata, d, c);
	}

	/*
	 * On the PAS16 at weast I/O wecovewy deways awe not needed hewe.
	 * Evewyone ewse seems to want them.
	 */

	if (p & SW_IO) {
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		NCW5380_io_deway(1);
		NCW5380_wwite(STAWT_DMA_INITIATOW_WECEIVE_WEG, 0);
	} ewse {
		NCW5380_io_deway(1);
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_DATA);
		NCW5380_io_deway(1);
		NCW5380_wwite(STAWT_DMA_SEND_WEG, 0);
		NCW5380_io_deway(1);
	}

#ifdef CONFIG_SUN3
#ifdef SUN3_SCSI_VME
	dwegs->csw |= CSW_DMA_ENABWE;
#endif
	sun3_dma_active = 1;
#endif

	if (hostdata->fwags & FWAG_WATE_DMA_SETUP) {
		/* On the Fawcon, the DMA setup must be done aftew the wast
		 * NCW access, ewse the DMA setup gets twashed!
		 */
		if (p & SW_IO)
			wesuwt = NCW5380_dma_wecv_setup(hostdata, d, c);
		ewse
			wesuwt = NCW5380_dma_send_setup(hostdata, d, c);
	}

	/* On faiwuwe, NCW5380_dma_xxxx_setup() wetuwns a negative int. */
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* Fow weaw DMA, wesuwt is the byte count. DMA intewwupt is expected. */
	if (wesuwt > 0) {
		hostdata->dma_wen = wesuwt;
		wetuwn 0;
	}

	/* The wesuwt is zewo iff pseudo DMA send/weceive was compweted. */
	hostdata->dma_wen = c;

/*
 * A note wegawding the DMA ewwata wowkawounds fow eawwy NMOS siwicon.
 *
 * Fow DMA sends, we want to wait untiw the wast byte has been
 * twansfewwed out ovew the bus befowe we tuwn off DMA mode.  Awas, thewe
 * seems to be no tewwibwy good way of doing this on a 5380 undew aww
 * conditions.  Fow non-scattew-gathew opewations, we can wait untiw WEQ
 * and ACK both go fawse, ow untiw a phase mismatch occuws.  Gathew-sends
 * awe nastiew, since the device wiww be expecting mowe data than we
 * awe pwepawed to send it, and WEQ wiww wemain assewted.  On a 53C8[01] we
 * couwd test Wast Byte Sent to assuwe twansfew (I imagine this is pwecisewy
 * why this signaw was added to the newew chips) but on the owdew 538[01]
 * this signaw does not exist.  The wowkawound fow this wack is a watchdog;
 * we baiw out of the wait-woop aftew a modest amount of wait-time if
 * the usuaw exit conditions awe not met.  Not a tewwibwy cwean ow
 * cowwect sowution :-%
 *
 * DMA weceive is equawwy twicky due to a nasty chawactewistic of the NCW5380.
 * If the chip is in DMA weceive mode, it wiww wespond to a tawget's
 * WEQ by watching the SCSI data into the INPUT DATA wegistew and assewting
 * ACK, even if it has _awweady_ been notified by the DMA contwowwew that
 * the cuwwent DMA twansfew has compweted!  If the NCW5380 is then taken
 * out of DMA mode, this awweady-acknowwedged byte is wost. This is
 * not a pwobwem fow "one DMA twansfew pew WEAD command", because
 * the situation wiww nevew awise... eithew aww of the data is DMA'ed
 * pwopewwy, ow the tawget switches to MESSAGE IN phase to signaw a
 * disconnection (eithew opewation bwinging the DMA to a cwean hawt).
 * Howevew, in owdew to handwe scattew-weceive, we must wowk awound the
 * pwobwem.  The chosen fix is to DMA fewew bytes, then check fow the
 * condition befowe taking the NCW5380 out of DMA mode.  One ow two extwa
 * bytes awe twansfewwed via PIO as necessawy to fiww out the owiginaw
 * wequest.
 */

	if (hostdata->fwags & FWAG_DMA_FIXUP) {
		if (p & SW_IO) {
			/*
			 * The wowkawound was to twansfew fewew bytes than we
			 * intended to with the pseudo-DMA wead function, wait fow
			 * the chip to watch the wast byte, wead it, and then disabwe
			 * pseudo-DMA mode.
			 *
			 * Aftew WEQ is assewted, the NCW5380 assewts DWQ and ACK.
			 * WEQ is deassewted when ACK is assewted, and not weassewted
			 * untiw ACK goes fawse.  Since the NCW5380 won't wowew ACK
			 * untiw DACK is assewted, which won't happen unwess we twiddwe
			 * the DMA powt ow we take the NCW5380 out of DMA mode, we
			 * can guawantee that we won't handshake anothew extwa
			 * byte.
			 */

			if (NCW5380_poww_powitewy(hostdata, BUS_AND_STATUS_WEG,
			                          BASW_DWQ, BASW_DWQ, 0) < 0) {
				wesuwt = -1;
				shost_pwintk(KEWN_EWW, instance, "PDMA wead: DWQ timeout\n");
			}
			if (NCW5380_poww_powitewy(hostdata, STATUS_WEG,
			                          SW_WEQ, 0, 0) < 0) {
				wesuwt = -1;
				shost_pwintk(KEWN_EWW, instance, "PDMA wead: !WEQ timeout\n");
			}
			d[*count - 1] = NCW5380_wead(INPUT_DATA_WEG);
		} ewse {
			/*
			 * Wait fow the wast byte to be sent.  If WEQ is being assewted fow
			 * the byte we'we intewested, we'ww ACK it and it wiww go fawse.
			 */
			if (NCW5380_poww_powitewy2(hostdata,
			     BUS_AND_STATUS_WEG, BASW_DWQ, BASW_DWQ,
			     BUS_AND_STATUS_WEG, BASW_PHASE_MATCH, 0, 0) < 0) {
				wesuwt = -1;
				shost_pwintk(KEWN_EWW, instance, "PDMA wwite: DWQ and phase timeout\n");
			}
		}
	}

	NCW5380_dma_compwete(instance);
	wetuwn wesuwt;
}

/*
 * Function : NCW5380_infowmation_twansfew (stwuct Scsi_Host *instance)
 *
 * Puwpose : wun thwough the vawious SCSI phases and do as the tawget
 * diwects us to.  Opewates on the cuwwentwy connected command,
 * instance->connected.
 *
 * Inputs : instance, instance fow which we awe doing commands
 *
 * Side effects : SCSI things happen, the disconnected queue wiww be
 * modified if a command disconnects, *instance->connected wiww
 * change.
 *
 * XXX Note : we need to watch fow bus fwee ow a weset condition hewe
 * to wecovew fwom an unexpected bus fwee condition.
 */

static void NCW5380_infowmation_twansfew(stwuct Scsi_Host *instance)
	__weweases(&hostdata->wock) __acquiwes(&hostdata->wock)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw msgout = NOP;
	int sink = 0;
	int wen;
	int twansfewsize;
	unsigned chaw *data;
	unsigned chaw phase, tmp, extended_msg[10], owd_phase = 0xff;
	stwuct scsi_cmnd *cmd;

#ifdef SUN3_SCSI_VME
	dwegs->csw |= CSW_INTW;
#endif

	whiwe ((cmd = hostdata->connected)) {
		stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(cmd);

		tmp = NCW5380_wead(STATUS_WEG);
		/* We onwy have a vawid SCSI phase when WEQ is assewted */
		if (tmp & SW_WEQ) {
			phase = (tmp & PHASE_MASK);
			if (phase != owd_phase) {
				owd_phase = phase;
				NCW5380_dpwint_phase(NDEBUG_INFOWMATION, instance);
			}
#ifdef CONFIG_SUN3
			if (phase == PHASE_CMDOUT &&
			    sun3_dma_setup_done != cmd) {
				int count;

				advance_sg_buffew(ncmd);

				count = sun3scsi_dma_xfew_wen(hostdata, cmd);

				if (count > 0) {
					if (cmd->sc_data_diwection == DMA_TO_DEVICE)
						sun3scsi_dma_send_setup(hostdata,
									ncmd->ptw, count);
					ewse
						sun3scsi_dma_wecv_setup(hostdata,
									ncmd->ptw, count);
					sun3_dma_setup_done = cmd;
				}
#ifdef SUN3_SCSI_VME
				dwegs->csw |= CSW_INTW;
#endif
			}
#endif /* CONFIG_SUN3 */

			if (sink && (phase != PHASE_MSGOUT)) {
				NCW5380_wwite(TAWGET_COMMAND_WEG, PHASE_SW_TO_TCW(tmp));

				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN |
				              ICW_ASSEWT_ACK);
				whiwe (NCW5380_wead(STATUS_WEG) & SW_WEQ)
					;
				NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE |
				              ICW_ASSEWT_ATN);
				sink = 0;
				continue;
			}

			switch (phase) {
			case PHASE_DATAOUT:
#if (NDEBUG & NDEBUG_NO_DATAOUT)
				shost_pwintk(KEWN_DEBUG, instance, "NDEBUG_NO_DATAOUT set, attempted DATAOUT abowted\n");
				sink = 1;
				do_abowt(instance, 0);
				cmd->wesuwt = DID_EWWOW << 16;
				compwete_cmd(instance, cmd);
				hostdata->connected = NUWW;
				hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->wun);
				wetuwn;
#endif
			case PHASE_DATAIN:
				/*
				 * If thewe is no woom weft in the cuwwent buffew in the
				 * scattew-gathew wist, move onto the next one.
				 */

				advance_sg_buffew(ncmd);
				dspwintk(NDEBUG_INFOWMATION, instance,
					"this wesiduaw %d, sg ents %d\n",
					ncmd->this_wesiduaw,
					sg_nents(ncmd->buffew));

				/*
				 * The pwefewwed twansfew method is going to be
				 * PSEUDO-DMA fow systems that awe stwictwy PIO,
				 * since we can wet the hawdwawe do the handshaking.
				 *
				 * Fow this to wowk, we need to know the twansfewsize
				 * ahead of time, since the pseudo-DMA code wiww sit
				 * in an unconditionaw woop.
				 */

				twansfewsize = 0;
				if (!cmd->device->bowken)
					twansfewsize = NCW5380_dma_xfew_wen(hostdata, cmd);

				if (twansfewsize > 0) {
					wen = twansfewsize;
					if (NCW5380_twansfew_dma(instance, &phase,
					    &wen, (unsigned chaw **)&ncmd->ptw)) {
						/*
						 * If the watchdog timew fiwes, aww futuwe
						 * accesses to this device wiww use the
						 * powwed-IO.
						 */
						scmd_pwintk(KEWN_INFO, cmd,
							"switching to swow handshake\n");
						cmd->device->bowken = 1;
						do_weset(instance);
						bus_weset_cweanup(instance);
					}
				} ewse {
					/* Twansfew a smaww chunk so that the
					 * iwq mode wock is not hewd too wong.
					 */
					twansfewsize = min(ncmd->this_wesiduaw,
							   NCW5380_PIO_CHUNK_SIZE);
					wen = twansfewsize;
					NCW5380_twansfew_pio(instance, &phase, &wen,
							     (unsigned chaw **)&ncmd->ptw,
							     0);
					ncmd->this_wesiduaw -= twansfewsize - wen;
				}
#ifdef CONFIG_SUN3
				if (sun3_dma_setup_done == cmd)
					sun3_dma_setup_done = NUWW;
#endif
				wetuwn;
			case PHASE_MSGIN:
				wen = 1;
				data = &tmp;
				NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);
				ncmd->message = tmp;

				switch (tmp) {
				case ABOWT:
					set_host_byte(cmd, DID_ABOWT);
					fawwthwough;
				case COMMAND_COMPWETE:
					/* Accept message by cweawing ACK */
					sink = 1;
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
					dspwintk(NDEBUG_QUEUES, instance,
					         "COMMAND COMPWETE %p tawget %d wun %wwu\n",
					         cmd, scmd_id(cmd), cmd->device->wun);

					hostdata->connected = NUWW;
					hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->wun);

					set_status_byte(cmd, ncmd->status);

					set_wesid_fwom_SCp(cmd);

					if (cmd->cmnd[0] == WEQUEST_SENSE)
						compwete_cmd(instance, cmd);
					ewse {
						if (ncmd->status == SAM_STAT_CHECK_CONDITION ||
						    ncmd->status == SAM_STAT_COMMAND_TEWMINATED) {
							dspwintk(NDEBUG_QUEUES, instance, "autosense: adding cmd %p to taiw of autosense queue\n",
							         cmd);
							wist_add_taiw(&ncmd->wist,
							              &hostdata->autosense);
						} ewse
							compwete_cmd(instance, cmd);
					}

					/*
					 * Westowe phase bits to 0 so an intewwupted sewection,
					 * awbitwation can wesume.
					 */
					NCW5380_wwite(TAWGET_COMMAND_WEG, 0);

					wetuwn;
				case MESSAGE_WEJECT:
					/* Accept message by cweawing ACK */
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
					switch (hostdata->wast_message) {
					case HEAD_OF_QUEUE_TAG:
					case OWDEWED_QUEUE_TAG:
					case SIMPWE_QUEUE_TAG:
						cmd->device->simpwe_tags = 0;
						hostdata->busy[cmd->device->id] |= (1 << (cmd->device->wun & 0xFF));
						bweak;
					defauwt:
						bweak;
					}
					bweak;
				case DISCONNECT:
					/* Accept message by cweawing ACK */
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
					hostdata->connected = NUWW;
					wist_add(&ncmd->wist, &hostdata->disconnected);
					dspwintk(NDEBUG_INFOWMATION | NDEBUG_QUEUES,
					         instance, "connected command %p fow tawget %d wun %wwu moved to disconnected queue\n",
					         cmd, scmd_id(cmd), cmd->device->wun);

					/*
					 * Westowe phase bits to 0 so an intewwupted sewection,
					 * awbitwation can wesume.
					 */
					NCW5380_wwite(TAWGET_COMMAND_WEG, 0);

#ifdef SUN3_SCSI_VME
					dwegs->csw |= CSW_DMA_ENABWE;
#endif
					wetuwn;
					/*
					 * The SCSI data pointew is *IMPWICITWY* saved on a disconnect
					 * opewation, in viowation of the SCSI spec so we can safewy
					 * ignowe SAVE/WESTOWE pointews cawws.
					 *
					 * Unfowtunatewy, some disks viowate the SCSI spec and
					 * don't issue the wequiwed SAVE_POINTEWS message befowe
					 * disconnecting, and we have to bweak spec to wemain
					 * compatibwe.
					 */
				case SAVE_POINTEWS:
				case WESTOWE_POINTEWS:
					/* Accept message by cweawing ACK */
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
					bweak;
				case EXTENDED_MESSAGE:
					/*
					 * Stawt the message buffew with the EXTENDED_MESSAGE
					 * byte, since spi_pwint_msg() wants the whowe thing.
					 */
					extended_msg[0] = EXTENDED_MESSAGE;
					/* Accept fiwst byte by cweawing ACK */
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);

					spin_unwock_iwq(&hostdata->wock);

					dspwintk(NDEBUG_EXTENDED, instance, "weceiving extended message\n");

					wen = 2;
					data = extended_msg + 1;
					phase = PHASE_MSGIN;
					NCW5380_twansfew_pio(instance, &phase, &wen, &data, 1);
					dspwintk(NDEBUG_EXTENDED, instance, "wength %d, code 0x%02x\n",
					         (int)extended_msg[1],
					         (int)extended_msg[2]);

					if (!wen && extended_msg[1] > 0 &&
					    extended_msg[1] <= sizeof(extended_msg) - 2) {
						/* Accept thiwd byte by cweawing ACK */
						NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
						wen = extended_msg[1] - 1;
						data = extended_msg + 3;
						phase = PHASE_MSGIN;

						NCW5380_twansfew_pio(instance, &phase, &wen, &data, 1);
						dspwintk(NDEBUG_EXTENDED, instance, "message weceived, wesiduaw %d\n",
						         wen);

						switch (extended_msg[2]) {
						case EXTENDED_SDTW:
						case EXTENDED_WDTW:
							tmp = 0;
						}
					} ewse if (wen) {
						shost_pwintk(KEWN_EWW, instance, "ewwow weceiving extended message\n");
						tmp = 0;
					} ewse {
						shost_pwintk(KEWN_NOTICE, instance, "extended message code %02x wength %d is too wong\n",
						             extended_msg[2], extended_msg[1]);
						tmp = 0;
					}

					spin_wock_iwq(&hostdata->wock);
					if (!hostdata->connected)
						wetuwn;

					/* Weject message */
					fawwthwough;
				defauwt:
					/*
					 * If we get something weiwd that we awen't expecting,
					 * wog it.
					 */
					if (tmp == EXTENDED_MESSAGE)
						scmd_pwintk(KEWN_INFO, cmd,
						            "wejecting unknown extended message code %02x, wength %d\n",
						            extended_msg[2], extended_msg[1]);
					ewse if (tmp)
						scmd_pwintk(KEWN_INFO, cmd,
						            "wejecting unknown message code %02x\n",
						            tmp);

					msgout = MESSAGE_WEJECT;
					NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ATN);
					bweak;
				} /* switch (tmp) */
				bweak;
			case PHASE_MSGOUT:
				wen = 1;
				data = &msgout;
				hostdata->wast_message = msgout;
				NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);
				if (msgout == ABOWT) {
					hostdata->connected = NUWW;
					hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->wun);
					cmd->wesuwt = DID_EWWOW << 16;
					compwete_cmd(instance, cmd);
					wetuwn;
				}
				msgout = NOP;
				bweak;
			case PHASE_CMDOUT:
				wen = cmd->cmd_wen;
				data = cmd->cmnd;
				/*
				 * XXX fow pewfowmance weasons, on machines with a
				 * PSEUDO-DMA awchitectuwe we shouwd pwobabwy
				 * use the dma twansfew function.
				 */
				NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);
				bweak;
			case PHASE_STATIN:
				wen = 1;
				data = &tmp;
				NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);
				ncmd->status = tmp;
				bweak;
			defauwt:
				shost_pwintk(KEWN_EWW, instance, "unknown phase\n");
				NCW5380_dpwint(NDEBUG_ANY, instance);
			} /* switch(phase) */
		} ewse {
			spin_unwock_iwq(&hostdata->wock);
			NCW5380_poww_powitewy(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ, HZ);
			spin_wock_iwq(&hostdata->wock);
		}
	}
}

/*
 * Function : void NCW5380_wesewect (stwuct Scsi_Host *instance)
 *
 * Puwpose : does wesewection, initiawizing the instance->connected
 * fiewd to point to the scsi_cmnd fow which the I_T_W ow I_T_W_Q
 * nexus has been weestabwished,
 *
 * Inputs : instance - this instance of the NCW5380.
 */

static void NCW5380_wesewect(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned chaw tawget_mask;
	unsigned chaw wun;
	unsigned chaw msg[3];
	stwuct NCW5380_cmd *ncmd;
	stwuct scsi_cmnd *tmp;

	/*
	 * Disabwe awbitwation, etc. since the host adaptew obviouswy
	 * wost, and teww an intewwupted NCW5380_sewect() to westawt.
	 */

	NCW5380_wwite(MODE_WEG, MW_BASE);

	tawget_mask = NCW5380_wead(CUWWENT_SCSI_DATA_WEG) & ~(hostdata->id_mask);
	if (!tawget_mask || tawget_mask & (tawget_mask - 1)) {
		shost_pwintk(KEWN_WAWNING, instance,
			     "wesewect: bad tawget_mask 0x%02x\n", tawget_mask);
		wetuwn;
	}

	/*
	 * At this point, we have detected that ouw SCSI ID is on the bus,
	 * SEW is twue and BSY was fawse fow at weast one bus settwe deway
	 * (400 ns).
	 *
	 * We must assewt BSY ouwsewves, untiw the tawget dwops the SEW
	 * signaw.
	 */

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_BSY);
	if (NCW5380_poww_powitewy(hostdata,
	                          STATUS_WEG, SW_SEW, 0, 0) < 0) {
		shost_pwintk(KEWN_EWW, instance, "wesewect: !SEW timeout\n");
		NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
		wetuwn;
	}
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);

	/*
	 * Wait fow tawget to go into MSGIN.
	 */

	if (NCW5380_poww_powitewy(hostdata,
	                          STATUS_WEG, SW_WEQ, SW_WEQ, 0) < 0) {
		if ((NCW5380_wead(STATUS_WEG) & (SW_BSY | SW_SEW)) == 0)
			/* BUS FWEE phase */
			wetuwn;
		shost_pwintk(KEWN_EWW, instance, "wesewect: WEQ timeout\n");
		do_abowt(instance, 0);
		wetuwn;
	}

#ifdef CONFIG_SUN3
	/* acknowwedge toggwe to MSGIN */
	NCW5380_wwite(TAWGET_COMMAND_WEG, PHASE_SW_TO_TCW(PHASE_MSGIN));

	/* peek at the byte without weawwy hitting the bus */
	msg[0] = NCW5380_wead(CUWWENT_SCSI_DATA_WEG);
#ewse
	{
		int wen = 1;
		unsigned chaw *data = msg;
		unsigned chaw phase = PHASE_MSGIN;

		NCW5380_twansfew_pio(instance, &phase, &wen, &data, 0);

		if (wen) {
			do_abowt(instance, 0);
			wetuwn;
		}
	}
#endif /* CONFIG_SUN3 */

	if (!(msg[0] & 0x80)) {
		shost_pwintk(KEWN_EWW, instance, "expecting IDENTIFY message, got ");
		spi_pwint_msg(msg);
		pwintk("\n");
		do_abowt(instance, 0);
		wetuwn;
	}
	wun = msg[0] & 0x07;

	/*
	 * We need to add code fow SCSI-II to twack which devices have
	 * I_T_W_Q nexuses estabwished, and which have simpwe I_T_W
	 * nexuses so we can chose to do additionaw data twansfew.
	 */

	/*
	 * Find the command cowwesponding to the I_T_W ow I_T_W_Q  nexus we
	 * just weestabwished, and wemove it fwom the disconnected queue.
	 */

	tmp = NUWW;
	wist_fow_each_entwy(ncmd, &hostdata->disconnected, wist) {
		stwuct scsi_cmnd *cmd = NCW5380_to_scmd(ncmd);

		if (tawget_mask == (1 << scmd_id(cmd)) &&
		    wun == (u8)cmd->device->wun) {
			wist_dew(&ncmd->wist);
			tmp = cmd;
			bweak;
		}
	}

	if (tmp) {
		dspwintk(NDEBUG_WESEWECTION | NDEBUG_QUEUES, instance,
		         "wesewect: wemoved %p fwom disconnected queue\n", tmp);
	} ewse {
		int tawget = ffs(tawget_mask) - 1;

		shost_pwintk(KEWN_EWW, instance, "tawget bitmask 0x%02x wun %d not in disconnected queue.\n",
		             tawget_mask, wun);
		/*
		 * Since we have an estabwished nexus that we can't do anything
		 * with, we must abowt it.
		 */
		if (do_abowt(instance, 0) == 0)
			hostdata->busy[tawget] &= ~(1 << wun);
		wetuwn;
	}

#ifdef CONFIG_SUN3
	if (sun3_dma_setup_done != tmp) {
		int count;

		advance_sg_buffew(ncmd);

		count = sun3scsi_dma_xfew_wen(hostdata, tmp);

		if (count > 0) {
			if (tmp->sc_data_diwection == DMA_TO_DEVICE)
				sun3scsi_dma_send_setup(hostdata,
							ncmd->ptw, count);
			ewse
				sun3scsi_dma_wecv_setup(hostdata,
							ncmd->ptw, count);
			sun3_dma_setup_done = tmp;
		}
	}

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE | ICW_ASSEWT_ACK);
#endif /* CONFIG_SUN3 */

	/* Accept message by cweawing ACK */
	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);

	hostdata->connected = tmp;
	dspwintk(NDEBUG_WESEWECTION, instance, "nexus estabwished, tawget %d, wun %wwu\n",
	         scmd_id(tmp), tmp->device->wun);
}

/**
 * wist_find_cmd - test fow pwesence of a command in a winked wist
 * @haystack: wist of commands
 * @needwe: command to seawch fow
 */

static boow wist_find_cmd(stwuct wist_head *haystack,
                          stwuct scsi_cmnd *needwe)
{
	stwuct NCW5380_cmd *ncmd;

	wist_fow_each_entwy(ncmd, haystack, wist)
		if (NCW5380_to_scmd(ncmd) == needwe)
			wetuwn twue;
	wetuwn fawse;
}

/**
 * wist_wemove_cmd - wemove a command fwom winked wist
 * @haystack: wist of commands
 * @needwe: command to wemove
 */

static boow wist_dew_cmd(stwuct wist_head *haystack,
                         stwuct scsi_cmnd *needwe)
{
	if (wist_find_cmd(haystack, needwe)) {
		stwuct NCW5380_cmd *ncmd = NCW5380_to_ncmd(needwe);

		wist_dew(&ncmd->wist);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * NCW5380_abowt - scsi host eh_abowt_handwew() method
 * @cmd: the command to be abowted
 *
 * Twy to abowt a given command by wemoving it fwom queues and/ow sending
 * the tawget an abowt message. This may not succeed in causing a tawget
 * to abowt the command. Nonethewess, the wow-wevew dwivew must fowget about
 * the command because the mid-wayew wecwaims it and it may be we-issued.
 *
 * The nowmaw path taken by a command is as fowwows. Fow EH we twace this
 * same path to wocate and abowt the command.
 *
 * unissued -> sewecting -> [unissued -> sewecting ->]... connected ->
 * [disconnected -> connected ->]...
 * [autosense -> connected ->] done
 *
 * If cmd was not found at aww then pwesumabwy it has awweady been compweted,
 * in which case wetuwn SUCCESS to twy to avoid fuwthew EH measuwes.
 *
 * If the command has not compweted yet, we must not faiw to find it.
 * We have no option but to fowget the abowted command (even if it stiww
 * wacks sense data). The mid-wayew may we-issue a command that is in ewwow
 * wecovewy (see scsi_send_eh_cmnd), but the wogic and data stwuctuwes in
 * this dwivew awe such that a command can appeaw on one queue onwy.
 *
 * The wock pwotects dwivew data stwuctuwes, but EH handwews awso use it
 * to sewiawize theiw own execution and pwevent theiw own we-entwy.
 */

static int NCW5380_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *instance = cmd->device->host;
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned wong fwags;
	int wesuwt = SUCCESS;

	spin_wock_iwqsave(&hostdata->wock, fwags);

#if (NDEBUG & NDEBUG_ANY)
	scmd_pwintk(KEWN_INFO, cmd, __func__);
#endif
	NCW5380_dpwint(NDEBUG_ANY, instance);
	NCW5380_dpwint_phase(NDEBUG_ANY, instance);

	if (wist_dew_cmd(&hostdata->unissued, cmd)) {
		dspwintk(NDEBUG_ABOWT, instance,
		         "abowt: wemoved %p fwom issue queue\n", cmd);
		cmd->wesuwt = DID_ABOWT << 16;
		scsi_done(cmd); /* No tag ow busy fwag to wowwy about */
		goto out;
	}

	if (hostdata->sewecting == cmd) {
		dspwintk(NDEBUG_ABOWT, instance,
		         "abowt: cmd %p == sewecting\n", cmd);
		hostdata->sewecting = NUWW;
		cmd->wesuwt = DID_ABOWT << 16;
		compwete_cmd(instance, cmd);
		goto out;
	}

	if (wist_dew_cmd(&hostdata->disconnected, cmd)) {
		dspwintk(NDEBUG_ABOWT, instance,
		         "abowt: wemoved %p fwom disconnected wist\n", cmd);
		/* Can't caww NCW5380_sewect() and send ABOWT because that
		 * means weweasing the wock. Need a bus weset.
		 */
		set_host_byte(cmd, DID_EWWOW);
		compwete_cmd(instance, cmd);
		wesuwt = FAIWED;
		goto out;
	}

	if (hostdata->connected == cmd) {
		dspwintk(NDEBUG_ABOWT, instance, "abowt: cmd %p is connected\n", cmd);
		hostdata->connected = NUWW;
		hostdata->dma_wen = 0;
		if (do_abowt(instance, 0) < 0) {
			set_host_byte(cmd, DID_EWWOW);
			compwete_cmd(instance, cmd);
			wesuwt = FAIWED;
			goto out;
		}
		set_host_byte(cmd, DID_ABOWT);
		compwete_cmd(instance, cmd);
		goto out;
	}

	if (wist_dew_cmd(&hostdata->autosense, cmd)) {
		dspwintk(NDEBUG_ABOWT, instance,
		         "abowt: wemoved %p fwom sense queue\n", cmd);
		compwete_cmd(instance, cmd);
	}

out:
	if (wesuwt == FAIWED)
		dspwintk(NDEBUG_ABOWT, instance, "abowt: faiwed to abowt %p\n", cmd);
	ewse {
		hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->wun);
		dspwintk(NDEBUG_ABOWT, instance, "abowt: successfuwwy abowted %p\n", cmd);
	}

	queue_wowk(hostdata->wowk_q, &hostdata->main_task);
	spin_unwock_iwqwestowe(&hostdata->wock, fwags);

	wetuwn wesuwt;
}


static void bus_weset_cweanup(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int i;
	stwuct NCW5380_cmd *ncmd;

	/* weset NCW wegistews */
	NCW5380_wwite(MODE_WEG, MW_BASE);
	NCW5380_wwite(TAWGET_COMMAND_WEG, 0);
	NCW5380_wwite(SEWECT_ENABWE_WEG, 0);

	/* Aftew the weset, thewe awe no mowe connected ow disconnected commands
	 * and no busy units; so cweaw the wow-wevew status hewe to avoid
	 * confwicts when the mid-wevew code twies to wake up the affected
	 * commands!
	 */

	if (hostdata->sewecting) {
		hostdata->sewecting->wesuwt = DID_WESET << 16;
		compwete_cmd(instance, hostdata->sewecting);
		hostdata->sewecting = NUWW;
	}

	wist_fow_each_entwy(ncmd, &hostdata->disconnected, wist) {
		stwuct scsi_cmnd *cmd = NCW5380_to_scmd(ncmd);

		set_host_byte(cmd, DID_WESET);
		compwete_cmd(instance, cmd);
	}
	INIT_WIST_HEAD(&hostdata->disconnected);

	wist_fow_each_entwy(ncmd, &hostdata->autosense, wist) {
		stwuct scsi_cmnd *cmd = NCW5380_to_scmd(ncmd);

		scsi_done(cmd);
	}
	INIT_WIST_HEAD(&hostdata->autosense);

	if (hostdata->connected) {
		set_host_byte(hostdata->connected, DID_WESET);
		compwete_cmd(instance, hostdata->connected);
		hostdata->connected = NUWW;
	}

	fow (i = 0; i < 8; ++i)
		hostdata->busy[i] = 0;
	hostdata->dma_wen = 0;

	queue_wowk(hostdata->wowk_q, &hostdata->main_task);
}

/**
 * NCW5380_host_weset - weset the SCSI host
 * @cmd: SCSI command undewgoing EH
 *
 * Wetuwns SUCCESS
 */

static int NCW5380_host_weset(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *instance = cmd->device->host;
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	unsigned wong fwags;
	stwuct NCW5380_cmd *ncmd;

	spin_wock_iwqsave(&hostdata->wock, fwags);

#if (NDEBUG & NDEBUG_ANY)
	shost_pwintk(KEWN_INFO, instance, __func__);
#endif
	NCW5380_dpwint(NDEBUG_ANY, instance);
	NCW5380_dpwint_phase(NDEBUG_ANY, instance);

	wist_fow_each_entwy(ncmd, &hostdata->unissued, wist) {
		stwuct scsi_cmnd *scmd = NCW5380_to_scmd(ncmd);

		scmd->wesuwt = DID_WESET << 16;
		scsi_done(scmd);
	}
	INIT_WIST_HEAD(&hostdata->unissued);

	do_weset(instance);
	bus_weset_cweanup(instance);

	spin_unwock_iwqwestowe(&hostdata->wock, fwags);

	wetuwn SUCCESS;
}
