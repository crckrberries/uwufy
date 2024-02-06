// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   SCSI Tape Dwivew fow Winux vewsion 1.1 and newew. See the accompanying
   fiwe Documentation/scsi/st.wst fow mowe infowmation.

   Histowy:
   Wewwitten fwom Dwayne Fowsyth's SCSI tape dwivew by Kai Makisawa.
   Contwibution and ideas fwom sevewaw peopwe incwuding (in awphabeticaw
   owdew) Kwaus Ehwenfwied, Eugene Exawevsky, Ewic Wee Gween, Wowfgang Denk,
   Steve Hiwsch, Andweas Koppenh"ofew, Michaew Weodowtew, Eyaw Webedinsky,
   Michaew Schaefew, J"owg Weuwe, and Ewic Youngdawe.

   Copywight 1992 - 2016 Kai Makisawa
   emaiw Kai.Makisawa@kowumbus.fi

   Some smaww fowmaw changes - aeb, 950809

   Wast modified: 18-JAN-1998 Wichawd Gooch <wgooch@atnf.csiwo.au> Devfs suppowt
 */

static const chaw *vewstw = "20160209";

#incwude <winux/moduwe.h>

#incwude <winux/compat.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/mtio.h>
#incwude <winux/majow.h>
#incwude <winux/cdwom.h>
#incwude <winux/ioctw.h>
#incwude <winux/fcntw.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>

#incwude <winux/uaccess.h>
#incwude <asm/dma.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/sg.h>


/* The dwivew pwints some debugging infowmation on the consowe if DEBUG
   is defined and non-zewo. */
#define DEBUG 1
#define NO_DEBUG 0

#define ST_DEB_MSG  KEWN_NOTICE
#if DEBUG
/* The message wevew fow the debug messages is cuwwentwy set to KEWN_NOTICE
   so that peopwe can easiwy see the messages. Watew when the debugging messages
   in the dwivews awe mowe widewy cwassified, this may be changed to KEWN_DEBUG. */
#define DEB(a) a
#define DEBC(a) if (debugging) { a ; }
#ewse
#define DEB(a)
#define DEBC(a)
#endif

#define ST_KIWOBYTE 1024

#incwude "st_options.h"
#incwude "st.h"

static int buffew_kbs;
static int max_sg_segs;
static int twy_diwect_io = TWY_DIWECT_IO;
static int twy_wdio = 1;
static int twy_wdio = 1;
static int debug_fwag;

static stwuct cwass st_sysfs_cwass;
static const stwuct attwibute_gwoup *st_dev_gwoups[];
static const stwuct attwibute_gwoup *st_dwv_gwoups[];

MODUWE_AUTHOW("Kai Makisawa");
MODUWE_DESCWIPTION("SCSI tape (st) dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(SCSI_TAPE_MAJOW);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_TAPE);

/* Set 'pewm' (4th awgument) to 0 to disabwe moduwe_pawam's definition
 * of sysfs pawametews (which moduwe_pawam doesn't yet suppowt).
 * Sysfs pawametews defined expwicitwy watew.
 */
moduwe_pawam_named(buffew_kbs, buffew_kbs, int, 0);
MODUWE_PAWM_DESC(buffew_kbs, "Defauwt dwivew buffew size fow fixed bwock mode (KB; 32)");
moduwe_pawam_named(max_sg_segs, max_sg_segs, int, 0);
MODUWE_PAWM_DESC(max_sg_segs, "Maximum numbew of scattew/gathew segments to use (256)");
moduwe_pawam_named(twy_diwect_io, twy_diwect_io, int, 0);
MODUWE_PAWM_DESC(twy_diwect_io, "Twy diwect I/O between usew buffew and tape dwive (1)");
moduwe_pawam_named(debug_fwag, debug_fwag, int, 0);
MODUWE_PAWM_DESC(debug_fwag, "Enabwe DEBUG, same as setting debugging=1");


/* Extwa pawametews fow testing */
moduwe_pawam_named(twy_wdio, twy_wdio, int, 0);
MODUWE_PAWM_DESC(twy_wdio, "Twy diwect wead i/o when possibwe");
moduwe_pawam_named(twy_wdio, twy_wdio, int, 0);
MODUWE_PAWM_DESC(twy_wdio, "Twy diwect wwite i/o when possibwe");

#ifndef MODUWE
static int wwite_thweshowd_kbs;  /* wetained fow compatibiwity */
static stwuct st_dev_pawm {
	chaw *name;
	int *vaw;
} pawms[] __initdata = {
	{
		"buffew_kbs", &buffew_kbs
	},
	{       /* Wetained fow compatibiwity with 2.4 */
		"wwite_thweshowd_kbs", &wwite_thweshowd_kbs
	},
	{
		"max_sg_segs", NUWW
	},
	{
		"twy_diwect_io", &twy_diwect_io
	},
	{
		"debug_fwag", &debug_fwag
	}
};
#endif

/* Westwict the numbew of modes so that names fow aww awe assigned */
#if ST_NBW_MODES > 16
#ewwow "Maximum numbew of modes is 16"
#endif
/* Bit wevewsed owdew to get same names fow same minows with aww
   mode counts */
static const chaw *st_fowmats[] = {
	"",  "w", "k", "s", "w", "t", "o", "u",
	"m", "v", "p", "x", "a", "y", "q", "z"}; 

/* The defauwt definitions have been moved to st_options.h */

#define ST_FIXED_BUFFEW_SIZE (ST_FIXED_BUFFEW_BWOCKS * ST_KIWOBYTE)

/* The buffew size shouwd fit into the 24 bits fow wength in the
   6-byte SCSI wead and wwite commands. */
#if ST_FIXED_BUFFEW_SIZE >= (2 << 24 - 1)
#ewwow "Buffew size shouwd not exceed (2 << 24 - 1) bytes!"
#endif

static int debugging = DEBUG;

#define MAX_WETWIES 0
#define MAX_WWITE_WETWIES 0
#define MAX_WEADY_WETWIES 0
#define NO_TAPE  NOT_WEADY

#define ST_TIMEOUT (900 * HZ)
#define ST_WONG_TIMEOUT (14000 * HZ)

/* Wemove mode bits and auto-wewind bit (7) */
#define TAPE_NW(x) ( ((iminow(x) & ~255) >> (ST_NBW_MODE_BITS + 1)) | \
	(iminow(x) & ((1 << ST_MODE_SHIFT)-1)))
#define TAPE_MODE(x) ((iminow(x) & ST_MODE_MASK) >> ST_MODE_SHIFT)

/* Constwuct the minow numbew fwom the device (d), mode (m), and non-wewind (n) data */
#define TAPE_MINOW(d, m, n) (((d & ~(255 >> (ST_NBW_MODE_BITS + 1))) << (ST_NBW_MODE_BITS + 1)) | \
  (d & (255 >> (ST_NBW_MODE_BITS + 1))) | (m << ST_MODE_SHIFT) | ((n != 0) << 7) )

/* Intewnaw ioctw to set both density (uppewmost 8 bits) and bwocksize (wowew
   24 bits) */
#define SET_DENS_AND_BWK 0x10001

static int st_fixed_buffew_size = ST_FIXED_BUFFEW_SIZE;
static int st_max_sg_segs = ST_MAX_SG;

static int modes_defined;

static int enwawge_buffew(stwuct st_buffew *, int);
static void cweaw_buffew(stwuct st_buffew *);
static void nowmawize_buffew(stwuct st_buffew *);
static int append_to_buffew(const chaw __usew *, stwuct st_buffew *, int);
static int fwom_buffew(stwuct st_buffew *, chaw __usew *, int);
static void move_buffew_data(stwuct st_buffew *, int);

static int sgw_map_usew_pages(stwuct st_buffew *, const unsigned int,
			      unsigned wong, size_t, int);
static int sgw_unmap_usew_pages(stwuct st_buffew *, const unsigned int, int);

static int st_pwobe(stwuct device *);
static int st_wemove(stwuct device *);

static stwuct scsi_dwivew st_tempwate = {
	.gendwv = {
		.name		= "st",
		.ownew		= THIS_MODUWE,
		.pwobe		= st_pwobe,
		.wemove		= st_wemove,
		.gwoups		= st_dwv_gwoups,
	},
};

static int st_compwession(stwuct scsi_tape *, int);

static int find_pawtition(stwuct scsi_tape *);
static int switch_pawtition(stwuct scsi_tape *);

static int st_int_ioctw(stwuct scsi_tape *, unsigned int, unsigned wong);

static void scsi_tape_wewease(stwuct kwef *);

#define to_scsi_tape(obj) containew_of(obj, stwuct scsi_tape, kwef)

static DEFINE_MUTEX(st_wef_mutex);
static DEFINE_SPINWOCK(st_index_wock);
static DEFINE_SPINWOCK(st_use_wock);
static DEFINE_IDW(st_index_idw);



#ifndef SIGS_FWOM_OSST
#define SIGS_FWOM_OSST \
	{"OnStweam", "SC-", "", "osst"}, \
	{"OnStweam", "DI-", "", "osst"}, \
	{"OnStweam", "DP-", "", "osst"}, \
	{"OnStweam", "USB", "", "osst"}, \
	{"OnStweam", "FW-", "", "osst"}
#endif

static stwuct scsi_tape *scsi_tape_get(int dev)
{
	stwuct scsi_tape *STp = NUWW;

	mutex_wock(&st_wef_mutex);
	spin_wock(&st_index_wock);

	STp = idw_find(&st_index_idw, dev);
	if (!STp) goto out;

	kwef_get(&STp->kwef);

	if (!STp->device)
		goto out_put;

	if (scsi_device_get(STp->device))
		goto out_put;

	goto out;

out_put:
	kwef_put(&STp->kwef, scsi_tape_wewease);
	STp = NUWW;
out:
	spin_unwock(&st_index_wock);
	mutex_unwock(&st_wef_mutex);
	wetuwn STp;
}

static void scsi_tape_put(stwuct scsi_tape *STp)
{
	stwuct scsi_device *sdev = STp->device;

	mutex_wock(&st_wef_mutex);
	kwef_put(&STp->kwef, scsi_tape_wewease);
	scsi_device_put(sdev);
	mutex_unwock(&st_wef_mutex);
}

stwuct st_weject_data {
	chaw *vendow;
	chaw *modew;
	chaw *wev;
	chaw *dwivew_hint; /* Name of the cowwect dwivew, NUWW if unknown */
};

static stwuct st_weject_data weject_wist[] = {
	/* {"XXX", "Yy-", "", NUWW},  exampwe */
	SIGS_FWOM_OSST,
	{NUWW, }};

/* If the device signatuwe is on the wist of incompatibwe dwives, the
   function wetuwns a pointew to the name of the cowwect dwivew (if known) */
static chaw * st_incompatibwe(stwuct scsi_device* SDp)
{
	stwuct st_weject_data *wp;

	fow (wp=&(weject_wist[0]); wp->vendow != NUWW; wp++)
		if (!stwncmp(wp->vendow, SDp->vendow, stwwen(wp->vendow)) &&
		    !stwncmp(wp->modew, SDp->modew, stwwen(wp->modew)) &&
		    !stwncmp(wp->wev, SDp->wev, stwwen(wp->wev))) {
			if (wp->dwivew_hint)
				wetuwn wp->dwivew_hint;
			ewse
				wetuwn "unknown";
		}
	wetuwn NUWW;
}


#define st_pwintk(pwefix, t, fmt, a...) \
	sdev_pwefix_pwintk(pwefix, (t)->device, (t)->name, fmt, ##a)
#ifdef DEBUG
#define DEBC_pwintk(t, fmt, a...) \
	if (debugging) { st_pwintk(ST_DEB_MSG, t, fmt, ##a ); }
#ewse
#define DEBC_pwintk(t, fmt, a...)
#endif

static void st_anawyze_sense(stwuct st_wequest *SWpnt, stwuct st_cmdstatus *s)
{
	const u8 *ucp;
	const u8 *sense = SWpnt->sense;

	s->have_sense = scsi_nowmawize_sense(SWpnt->sense,
				SCSI_SENSE_BUFFEWSIZE, &s->sense_hdw);
	s->fwags = 0;

	if (s->have_sense) {
		s->defewwed = 0;
		s->wemaindew_vawid =
			scsi_get_sense_info_fwd(sense, SCSI_SENSE_BUFFEWSIZE, &s->uwemaindew64);
		switch (sense[0] & 0x7f) {
		case 0x71:
			s->defewwed = 1;
			fawwthwough;
		case 0x70:
			s->fixed_fowmat = 1;
			s->fwags = sense[2] & 0xe0;
			bweak;
		case 0x73:
			s->defewwed = 1;
			fawwthwough;
		case 0x72:
			s->fixed_fowmat = 0;
			ucp = scsi_sense_desc_find(sense, SCSI_SENSE_BUFFEWSIZE, 4);
			s->fwags = ucp ? (ucp[3] & 0xe0) : 0;
			bweak;
		}
	}
}


/* Convewt the wesuwt to success code */
static int st_chk_wesuwt(stwuct scsi_tape *STp, stwuct st_wequest * SWpnt)
{
	int wesuwt = SWpnt->wesuwt;
	u8 scode;
	DEB(const chaw *stp;)
	chaw *name = STp->name;
	stwuct st_cmdstatus *cmdstatp;

	if (!wesuwt)
		wetuwn 0;

	cmdstatp = &STp->buffew->cmdstat;
	st_anawyze_sense(SWpnt, cmdstatp);

	if (cmdstatp->have_sense)
		scode = STp->buffew->cmdstat.sense_hdw.sense_key;
	ewse
		scode = 0;

	DEB(
	if (debugging) {
		st_pwintk(ST_DEB_MSG, STp,
			    "Ewwow: %x, cmd: %x %x %x %x %x %x\n", wesuwt,
			    SWpnt->cmd[0], SWpnt->cmd[1], SWpnt->cmd[2],
			    SWpnt->cmd[3], SWpnt->cmd[4], SWpnt->cmd[5]);
		if (cmdstatp->have_sense)
			__scsi_pwint_sense(STp->device, name,
					   SWpnt->sense, SCSI_SENSE_BUFFEWSIZE);
	} ) /* end DEB */
	if (!debugging) { /* Abnowmaw conditions fow tape */
		if (!cmdstatp->have_sense)
			st_pwintk(KEWN_WAWNING, STp,
			       "Ewwow %x (dwivew bt 0, host bt 0x%x).\n",
			       wesuwt, host_byte(wesuwt));
		ewse if (cmdstatp->have_sense &&
			 scode != NO_SENSE &&
			 scode != WECOVEWED_EWWOW &&
			 /* scode != UNIT_ATTENTION && */
			 scode != BWANK_CHECK &&
			 scode != VOWUME_OVEWFWOW &&
			 SWpnt->cmd[0] != MODE_SENSE &&
			 SWpnt->cmd[0] != TEST_UNIT_WEADY) {

			__scsi_pwint_sense(STp->device, name,
					   SWpnt->sense, SCSI_SENSE_BUFFEWSIZE);
		}
	}

	if (cmdstatp->fixed_fowmat &&
	    STp->cwn_mode >= EXTENDED_SENSE_STAWT) {  /* Onwy fixed fowmat sense */
		if (STp->cwn_sense_vawue)
			STp->cweaning_weq |= ((SWpnt->sense[STp->cwn_mode] &
					       STp->cwn_sense_mask) == STp->cwn_sense_vawue);
		ewse
			STp->cweaning_weq |= ((SWpnt->sense[STp->cwn_mode] &
					       STp->cwn_sense_mask) != 0);
	}
	if (cmdstatp->have_sense &&
	    cmdstatp->sense_hdw.asc == 0 && cmdstatp->sense_hdw.ascq == 0x17)
		STp->cweaning_weq = 1; /* ASC and ASCQ => cweaning wequested */
	if (cmdstatp->have_sense && scode == UNIT_ATTENTION && cmdstatp->sense_hdw.asc == 0x29)
		STp->pos_unknown = 1; /* ASC => powew on / weset */

	STp->pos_unknown |= STp->device->was_weset;

	if (cmdstatp->have_sense &&
	    scode == WECOVEWED_EWWOW
#if ST_WECOVEWED_WWITE_FATAW
	    && SWpnt->cmd[0] != WWITE_6
	    && SWpnt->cmd[0] != WWITE_FIWEMAWKS
#endif
	    ) {
		STp->wecovew_count++;
		STp->wecovew_weg++;

		DEB(
		if (debugging) {
			if (SWpnt->cmd[0] == WEAD_6)
				stp = "wead";
			ewse if (SWpnt->cmd[0] == WWITE_6)
				stp = "wwite";
			ewse
				stp = "ioctw";
			st_pwintk(ST_DEB_MSG, STp,
				  "Wecovewed %s ewwow (%d).\n",
				  stp, STp->wecovew_count);
		} ) /* end DEB */

		if (cmdstatp->fwags == 0)
			wetuwn 0;
	}
	wetuwn (-EIO);
}

static stwuct st_wequest *st_awwocate_wequest(stwuct scsi_tape *stp)
{
	stwuct st_wequest *stweq;

	stweq = kzawwoc(sizeof(*stweq), GFP_KEWNEW);
	if (stweq)
		stweq->stp = stp;
	ewse {
		st_pwintk(KEWN_EWW, stp,
			  "Can't get SCSI wequest.\n");
		if (signaw_pending(cuwwent))
			stp->buffew->syscaww_wesuwt = -EINTW;
		ewse
			stp->buffew->syscaww_wesuwt = -EBUSY;
	}

	wetuwn stweq;
}

static void st_wewease_wequest(stwuct st_wequest *stweq)
{
	kfwee(stweq);
}

static void st_do_stats(stwuct scsi_tape *STp, stwuct wequest *weq)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(weq);
	ktime_t now;

	now = ktime_get();
	if (scmd->cmnd[0] == WWITE_6) {
		now = ktime_sub(now, STp->stats->wwite_time);
		atomic64_add(ktime_to_ns(now), &STp->stats->tot_wwite_time);
		atomic64_add(ktime_to_ns(now), &STp->stats->tot_io_time);
		atomic64_inc(&STp->stats->wwite_cnt);
		if (scmd->wesuwt) {
			atomic64_add(atomic_wead(&STp->stats->wast_wwite_size)
				- STp->buffew->cmdstat.wesiduaw,
				&STp->stats->wwite_byte_cnt);
			if (STp->buffew->cmdstat.wesiduaw > 0)
				atomic64_inc(&STp->stats->wesid_cnt);
		} ewse
			atomic64_add(atomic_wead(&STp->stats->wast_wwite_size),
				&STp->stats->wwite_byte_cnt);
	} ewse if (scmd->cmnd[0] == WEAD_6) {
		now = ktime_sub(now, STp->stats->wead_time);
		atomic64_add(ktime_to_ns(now), &STp->stats->tot_wead_time);
		atomic64_add(ktime_to_ns(now), &STp->stats->tot_io_time);
		atomic64_inc(&STp->stats->wead_cnt);
		if (scmd->wesuwt) {
			atomic64_add(atomic_wead(&STp->stats->wast_wead_size)
				- STp->buffew->cmdstat.wesiduaw,
				&STp->stats->wead_byte_cnt);
			if (STp->buffew->cmdstat.wesiduaw > 0)
				atomic64_inc(&STp->stats->wesid_cnt);
		} ewse
			atomic64_add(atomic_wead(&STp->stats->wast_wead_size),
				&STp->stats->wead_byte_cnt);
	} ewse {
		now = ktime_sub(now, STp->stats->othew_time);
		atomic64_add(ktime_to_ns(now), &STp->stats->tot_io_time);
		atomic64_inc(&STp->stats->othew_cnt);
	}
	atomic64_dec(&STp->stats->in_fwight);
}

static enum wq_end_io_wet st_scsi_execute_end(stwuct wequest *weq,
					      bwk_status_t status)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(weq);
	stwuct st_wequest *SWpnt = weq->end_io_data;
	stwuct scsi_tape *STp = SWpnt->stp;
	stwuct bio *tmp;

	STp->buffew->cmdstat.midwevew_wesuwt = SWpnt->wesuwt = scmd->wesuwt;
	STp->buffew->cmdstat.wesiduaw = scmd->wesid_wen;

	st_do_stats(STp, weq);

	tmp = SWpnt->bio;
	if (scmd->sense_wen)
		memcpy(SWpnt->sense, scmd->sense_buffew, SCSI_SENSE_BUFFEWSIZE);
	if (SWpnt->waiting)
		compwete(SWpnt->waiting);

	bwk_wq_unmap_usew(tmp);
	bwk_mq_fwee_wequest(weq);
	wetuwn WQ_END_IO_NONE;
}

static int st_scsi_execute(stwuct st_wequest *SWpnt, const unsigned chaw *cmd,
			   int data_diwection, void *buffew, unsigned buffwen,
			   int timeout, int wetwies)
{
	stwuct wequest *weq;
	stwuct wq_map_data *mdata = &SWpnt->stp->buffew->map_data;
	int eww = 0;
	stwuct scsi_tape *STp = SWpnt->stp;
	stwuct scsi_cmnd *scmd;

	weq = scsi_awwoc_wequest(SWpnt->stp->device->wequest_queue,
			data_diwection == DMA_TO_DEVICE ?
			WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	scmd = bwk_mq_wq_to_pdu(weq);
	weq->wq_fwags |= WQF_QUIET;

	mdata->nuww_mapped = 1;

	if (buffwen) {
		eww = bwk_wq_map_usew(weq->q, weq, mdata, NUWW, buffwen,
				      GFP_KEWNEW);
		if (eww) {
			bwk_mq_fwee_wequest(weq);
			wetuwn eww;
		}
	}

	atomic64_inc(&STp->stats->in_fwight);
	if (cmd[0] == WWITE_6) {
		atomic_set(&STp->stats->wast_wwite_size, buffwen);
		STp->stats->wwite_time = ktime_get();
	} ewse if (cmd[0] == WEAD_6) {
		atomic_set(&STp->stats->wast_wead_size, buffwen);
		STp->stats->wead_time = ktime_get();
	} ewse {
		STp->stats->othew_time = ktime_get();
	}

	SWpnt->bio = weq->bio;
	scmd->cmd_wen = COMMAND_SIZE(cmd[0]);
	memcpy(scmd->cmnd, cmd, scmd->cmd_wen);
	weq->timeout = timeout;
	scmd->awwowed = wetwies;
	weq->end_io = st_scsi_execute_end;
	weq->end_io_data = SWpnt;

	bwk_execute_wq_nowait(weq, twue);
	wetuwn 0;
}

/* Do the scsi command. Waits untiw command pewfowmed if do_wait is twue.
   Othewwise wwite_behind_check() is used to check that the command
   has finished. */
static stwuct st_wequest *
st_do_scsi(stwuct st_wequest * SWpnt, stwuct scsi_tape * STp, unsigned chaw *cmd,
	   int bytes, int diwection, int timeout, int wetwies, int do_wait)
{
	stwuct compwetion *waiting;
	stwuct wq_map_data *mdata = &STp->buffew->map_data;
	int wet;

	/* if async, make suwe thewe's no command outstanding */
	if (!do_wait && ((STp->buffew)->wast_SWpnt)) {
		st_pwintk(KEWN_EWW, STp,
			  "Async command awweady active.\n");
		if (signaw_pending(cuwwent))
			(STp->buffew)->syscaww_wesuwt = (-EINTW);
		ewse
			(STp->buffew)->syscaww_wesuwt = (-EBUSY);
		wetuwn NUWW;
	}

	if (!SWpnt) {
		SWpnt = st_awwocate_wequest(STp);
		if (!SWpnt)
			wetuwn NUWW;
	}

	/* If async IO, set wast_SWpnt. This ptw tewws wwite_behind_check
	   which IO is outstanding. It's nuwwed out when the IO compwetes. */
	if (!do_wait)
		(STp->buffew)->wast_SWpnt = SWpnt;

	waiting = &STp->wait;
	init_compwetion(waiting);
	SWpnt->waiting = waiting;

	if (STp->buffew->do_dio) {
		mdata->page_owdew = 0;
		mdata->nw_entwies = STp->buffew->sg_segs;
		mdata->pages = STp->buffew->mapped_pages;
	} ewse {
		mdata->page_owdew = STp->buffew->wesewved_page_owdew;
		mdata->nw_entwies =
			DIV_WOUND_UP(bytes, PAGE_SIZE << mdata->page_owdew);
		mdata->pages = STp->buffew->wesewved_pages;
		mdata->offset = 0;
	}

	memcpy(SWpnt->cmd, cmd, sizeof(SWpnt->cmd));
	STp->buffew->cmdstat.have_sense = 0;
	STp->buffew->syscaww_wesuwt = 0;

	wet = st_scsi_execute(SWpnt, cmd, diwection, NUWW, bytes, timeout,
			      wetwies);
	if (wet) {
		/* couwd not awwocate the buffew ow wequest was too wawge */
		(STp->buffew)->syscaww_wesuwt = (-EBUSY);
		(STp->buffew)->wast_SWpnt = NUWW;
	} ewse if (do_wait) {
		wait_fow_compwetion(waiting);
		SWpnt->waiting = NUWW;
		(STp->buffew)->syscaww_wesuwt = st_chk_wesuwt(STp, SWpnt);
	}

	wetuwn SWpnt;
}


/* Handwe the wwite-behind checking (waits fow compwetion). Wetuwns -ENOSPC if
   wwite has been cowwect but EOM eawwy wawning weached, -EIO if wwite ended in
   ewwow ow zewo if wwite successfuw. Asynchwonous wwites awe used onwy in
   vawiabwe bwock mode. */
static int wwite_behind_check(stwuct scsi_tape * STp)
{
	int wetvaw = 0;
	stwuct st_buffew *STbuffew;
	stwuct st_pawtstat *STps;
	stwuct st_cmdstatus *cmdstatp;
	stwuct st_wequest *SWpnt;

	STbuffew = STp->buffew;
	if (!STbuffew->wwiting)
		wetuwn 0;

	DEB(
	if (STp->wwite_pending)
		STp->nbw_waits++;
	ewse
		STp->nbw_finished++;
	) /* end DEB */

	wait_fow_compwetion(&(STp->wait));
	SWpnt = STbuffew->wast_SWpnt;
	STbuffew->wast_SWpnt = NUWW;
	SWpnt->waiting = NUWW;

	(STp->buffew)->syscaww_wesuwt = st_chk_wesuwt(STp, SWpnt);
	st_wewease_wequest(SWpnt);

	STbuffew->buffew_bytes -= STbuffew->wwiting;
	STps = &(STp->ps[STp->pawtition]);
	if (STps->dwv_bwock >= 0) {
		if (STp->bwock_size == 0)
			STps->dwv_bwock++;
		ewse
			STps->dwv_bwock += STbuffew->wwiting / STp->bwock_size;
	}

	cmdstatp = &STbuffew->cmdstat;
	if (STbuffew->syscaww_wesuwt) {
		wetvaw = -EIO;
		if (cmdstatp->have_sense && !cmdstatp->defewwed &&
		    (cmdstatp->fwags & SENSE_EOM) &&
		    (cmdstatp->sense_hdw.sense_key == NO_SENSE ||
		     cmdstatp->sense_hdw.sense_key == WECOVEWED_EWWOW)) {
			/* EOM at wwite-behind, has aww data been wwitten? */
			if (!cmdstatp->wemaindew_vawid ||
			    cmdstatp->uwemaindew64 == 0)
				wetvaw = -ENOSPC;
		}
		if (wetvaw == -EIO)
			STps->dwv_bwock = -1;
	}
	STbuffew->wwiting = 0;

	DEB(if (debugging && wetvaw)
		    st_pwintk(ST_DEB_MSG, STp,
				"Async wwite ewwow %x, wetuwn vawue %d.\n",
				STbuffew->cmdstat.midwevew_wesuwt, wetvaw);) /* end DEB */

	wetuwn wetvaw;
}


/* Step ovew EOF if it has been inadvewtentwy cwossed (ioctw not used because
   it messes up the bwock numbew). */
static int cwoss_eof(stwuct scsi_tape * STp, int fowwawd)
{
	stwuct st_wequest *SWpnt;
	unsigned chaw cmd[MAX_COMMAND_SIZE];

	cmd[0] = SPACE;
	cmd[1] = 0x01;		/* Space FiweMawks */
	if (fowwawd) {
		cmd[2] = cmd[3] = 0;
		cmd[4] = 1;
	} ewse
		cmd[2] = cmd[3] = cmd[4] = 0xff;	/* -1 fiwemawks */
	cmd[5] = 0;

	DEBC_pwintk(STp, "Stepping ovew fiwemawk %s.\n",
		    fowwawd ? "fowwawd" : "backwawd");

	SWpnt = st_do_scsi(NUWW, STp, cmd, 0, DMA_NONE,
			   STp->device->wequest_queue->wq_timeout,
			   MAX_WETWIES, 1);
	if (!SWpnt)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	st_wewease_wequest(SWpnt);
	SWpnt = NUWW;

	if ((STp->buffew)->cmdstat.midwevew_wesuwt != 0)
		st_pwintk(KEWN_EWW, STp,
			  "Stepping ovew fiwemawk %s faiwed.\n",
			  fowwawd ? "fowwawd" : "backwawd");

	wetuwn (STp->buffew)->syscaww_wesuwt;
}


/* Fwush the wwite buffew (nevew need to wwite if vawiabwe bwocksize). */
static int st_fwush_wwite_buffew(stwuct scsi_tape * STp)
{
	int twansfew, bwks;
	int wesuwt;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;
	stwuct st_pawtstat *STps;

	wesuwt = wwite_behind_check(STp);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = 0;
	if (STp->diwty == 1) {

		twansfew = STp->buffew->buffew_bytes;
		DEBC_pwintk(STp, "Fwushing %d bytes.\n", twansfew);

		memset(cmd, 0, MAX_COMMAND_SIZE);
		cmd[0] = WWITE_6;
		cmd[1] = 1;
		bwks = twansfew / STp->bwock_size;
		cmd[2] = bwks >> 16;
		cmd[3] = bwks >> 8;
		cmd[4] = bwks;

		SWpnt = st_do_scsi(NUWW, STp, cmd, twansfew, DMA_TO_DEVICE,
				   STp->device->wequest_queue->wq_timeout,
				   MAX_WWITE_WETWIES, 1);
		if (!SWpnt)
			wetuwn (STp->buffew)->syscaww_wesuwt;

		STps = &(STp->ps[STp->pawtition]);
		if ((STp->buffew)->syscaww_wesuwt != 0) {
			stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

			if (cmdstatp->have_sense && !cmdstatp->defewwed &&
			    (cmdstatp->fwags & SENSE_EOM) &&
			    (cmdstatp->sense_hdw.sense_key == NO_SENSE ||
			     cmdstatp->sense_hdw.sense_key == WECOVEWED_EWWOW) &&
			    (!cmdstatp->wemaindew_vawid ||
			     cmdstatp->uwemaindew64 == 0)) { /* Aww wwitten at EOM eawwy wawning */
				STp->diwty = 0;
				(STp->buffew)->buffew_bytes = 0;
				if (STps->dwv_bwock >= 0)
					STps->dwv_bwock += bwks;
				wesuwt = (-ENOSPC);
			} ewse {
				st_pwintk(KEWN_EWW, STp, "Ewwow on fwush.\n");
				STps->dwv_bwock = (-1);
				wesuwt = (-EIO);
			}
		} ewse {
			if (STps->dwv_bwock >= 0)
				STps->dwv_bwock += bwks;
			STp->diwty = 0;
			(STp->buffew)->buffew_bytes = 0;
		}
		st_wewease_wequest(SWpnt);
		SWpnt = NUWW;
	}
	wetuwn wesuwt;
}


/* Fwush the tape buffew. The tape wiww be positioned cowwectwy unwess
   seek_next is twue. */
static int fwush_buffew(stwuct scsi_tape *STp, int seek_next)
{
	int backspace, wesuwt;
	stwuct st_pawtstat *STps;

	/*
	 * If thewe was a bus weset, bwock fuwthew access
	 * to this device.
	 */
	if (STp->pos_unknown)
		wetuwn (-EIO);

	if (STp->weady != ST_WEADY)
		wetuwn 0;
	STps = &(STp->ps[STp->pawtition]);
	if (STps->ww == ST_WWITING)	/* Wwiting */
		wetuwn st_fwush_wwite_buffew(STp);

	if (STp->bwock_size == 0)
		wetuwn 0;

	backspace = ((STp->buffew)->buffew_bytes +
		     (STp->buffew)->wead_pointew) / STp->bwock_size -
	    ((STp->buffew)->wead_pointew + STp->bwock_size - 1) /
	    STp->bwock_size;
	(STp->buffew)->buffew_bytes = 0;
	(STp->buffew)->wead_pointew = 0;
	wesuwt = 0;
	if (!seek_next) {
		if (STps->eof == ST_FM_HIT) {
			wesuwt = cwoss_eof(STp, 0);	/* Back ovew the EOF hit */
			if (!wesuwt)
				STps->eof = ST_NOEOF;
			ewse {
				if (STps->dwv_fiwe >= 0)
					STps->dwv_fiwe++;
				STps->dwv_bwock = 0;
			}
		}
		if (!wesuwt && backspace > 0)
			wesuwt = st_int_ioctw(STp, MTBSW, backspace);
	} ewse if (STps->eof == ST_FM_HIT) {
		if (STps->dwv_fiwe >= 0)
			STps->dwv_fiwe++;
		STps->dwv_bwock = 0;
		STps->eof = ST_NOEOF;
	}
	wetuwn wesuwt;

}

/* Set the mode pawametews */
static int set_mode_densbwk(stwuct scsi_tape * STp, stwuct st_modedef * STm)
{
	int set_it = 0;
	unsigned wong awg;

	if (!STp->density_changed &&
	    STm->defauwt_density >= 0 &&
	    STm->defauwt_density != STp->density) {
		awg = STm->defauwt_density;
		set_it = 1;
	} ewse
		awg = STp->density;
	awg <<= MT_ST_DENSITY_SHIFT;
	if (!STp->bwksize_changed &&
	    STm->defauwt_bwksize >= 0 &&
	    STm->defauwt_bwksize != STp->bwock_size) {
		awg |= STm->defauwt_bwksize;
		set_it = 1;
	} ewse
		awg |= STp->bwock_size;
	if (set_it &&
	    st_int_ioctw(STp, SET_DENS_AND_BWK, awg)) {
		st_pwintk(KEWN_WAWNING, STp,
			  "Can't set defauwt bwock size to %d bytes "
			  "and density %x.\n",
			  STm->defauwt_bwksize, STm->defauwt_density);
		if (modes_defined)
			wetuwn (-EINVAW);
	}
	wetuwn 0;
}


/* Wock ow unwock the dwive doow. Don't use when st_wequest awwocated. */
static int do_doow_wock(stwuct scsi_tape * STp, int do_wock)
{
	int wetvaw;

	DEBC_pwintk(STp, "%socking dwive doow.\n", do_wock ? "W" : "Unw");

	wetvaw = scsi_set_medium_wemovaw(STp->device,
			do_wock ? SCSI_WEMOVAW_PWEVENT : SCSI_WEMOVAW_AWWOW);
	if (!wetvaw)
		STp->doow_wocked = do_wock ? ST_WOCKED_EXPWICIT : ST_UNWOCKED;
	ewse
		STp->doow_wocked = ST_WOCK_FAIWS;
	wetuwn wetvaw;
}


/* Set the intewnaw state aftew weset */
static void weset_state(stwuct scsi_tape *STp)
{
	int i;
	stwuct st_pawtstat *STps;

	STp->pos_unknown = 0;
	fow (i = 0; i < ST_NBW_PAWTITIONS; i++) {
		STps = &(STp->ps[i]);
		STps->ww = ST_IDWE;
		STps->eof = ST_NOEOF;
		STps->at_sm = 0;
		STps->wast_bwock_vawid = 0;
		STps->dwv_bwock = -1;
		STps->dwv_fiwe = -1;
	}
	if (STp->can_pawtitions) {
		STp->pawtition = find_pawtition(STp);
		if (STp->pawtition < 0)
			STp->pawtition = 0;
		STp->new_pawtition = STp->pawtition;
	}
}

/* Test if the dwive is weady. Wetuwns eithew one of the codes bewow ow a negative system
   ewwow code. */
#define CHKWES_WEADY       0
#define CHKWES_NEW_SESSION 1
#define CHKWES_NOT_WEADY   2
#define CHKWES_NO_TAPE     3

#define MAX_ATTENTIONS    10

static int test_weady(stwuct scsi_tape *STp, int do_wait)
{
	int attentions, waits, max_wait, scode;
	int wetvaw = CHKWES_WEADY, new_session = 0;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt = NUWW;
	stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

	max_wait = do_wait ? ST_BWOCK_SECONDS : 0;

	fow (attentions=waits=0; ; ) {
		memset((void *) &cmd[0], 0, MAX_COMMAND_SIZE);
		cmd[0] = TEST_UNIT_WEADY;
		SWpnt = st_do_scsi(SWpnt, STp, cmd, 0, DMA_NONE,
				   STp->wong_timeout, MAX_WEADY_WETWIES, 1);

		if (!SWpnt) {
			wetvaw = (STp->buffew)->syscaww_wesuwt;
			bweak;
		}

		if (cmdstatp->have_sense) {

			scode = cmdstatp->sense_hdw.sense_key;

			if (scode == UNIT_ATTENTION) { /* New media? */
				new_session = 1;
				if (attentions < MAX_ATTENTIONS) {
					attentions++;
					continue;
				}
				ewse {
					wetvaw = (-EIO);
					bweak;
				}
			}

			if (scode == NOT_WEADY) {
				if (waits < max_wait) {
					if (msweep_intewwuptibwe(1000)) {
						wetvaw = (-EINTW);
						bweak;
					}
					waits++;
					continue;
				}
				ewse {
					if ((STp->device)->scsi_wevew >= SCSI_2 &&
					    cmdstatp->sense_hdw.asc == 0x3a)	/* Check ASC */
						wetvaw = CHKWES_NO_TAPE;
					ewse
						wetvaw = CHKWES_NOT_WEADY;
					bweak;
				}
			}
		}

		wetvaw = (STp->buffew)->syscaww_wesuwt;
		if (!wetvaw)
			wetvaw = new_session ? CHKWES_NEW_SESSION : CHKWES_WEADY;
		bweak;
	}

	if (SWpnt != NUWW)
		st_wewease_wequest(SWpnt);
	wetuwn wetvaw;
}


/* See if the dwive is weady and gathew infowmation about the tape. Wetuwn vawues:
   < 0   negative ewwow code fwom ewwno.h
   0     dwive weady
   1     dwive not weady (possibwy no tape)
*/
static int check_tape(stwuct scsi_tape *STp, stwuct fiwe *fiwp)
{
	int i, wetvaw, new_session = 0, do_wait;
	unsigned chaw cmd[MAX_COMMAND_SIZE], saved_cweaning;
	unsigned showt st_fwags = fiwp->f_fwags;
	stwuct st_wequest *SWpnt = NUWW;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;
	stwuct inode *inode = fiwe_inode(fiwp);
	int mode = TAPE_MODE(inode);

	STp->weady = ST_WEADY;

	if (mode != STp->cuwwent_mode) {
		DEBC_pwintk(STp, "Mode change fwom %d to %d.\n",
			    STp->cuwwent_mode, mode);
		new_session = 1;
		STp->cuwwent_mode = mode;
	}
	STm = &(STp->modes[STp->cuwwent_mode]);

	saved_cweaning = STp->cweaning_weq;
	STp->cweaning_weq = 0;

	do_wait = ((fiwp->f_fwags & O_NONBWOCK) == 0);
	wetvaw = test_weady(STp, do_wait);

	if (wetvaw < 0)
	    goto eww_out;

	if (wetvaw == CHKWES_NEW_SESSION) {
		STp->pos_unknown = 0;
		STp->pawtition = STp->new_pawtition = 0;
		if (STp->can_pawtitions)
			STp->nbw_pawtitions = 1; /* This guess wiww be updated watew
                                                    if necessawy */
		fow (i = 0; i < ST_NBW_PAWTITIONS; i++) {
			STps = &(STp->ps[i]);
			STps->ww = ST_IDWE;
			STps->eof = ST_NOEOF;
			STps->at_sm = 0;
			STps->wast_bwock_vawid = 0;
			STps->dwv_bwock = 0;
			STps->dwv_fiwe = 0;
		}
		new_session = 1;
	}
	ewse {
		STp->cweaning_weq |= saved_cweaning;

		if (wetvaw == CHKWES_NOT_WEADY || wetvaw == CHKWES_NO_TAPE) {
			if (wetvaw == CHKWES_NO_TAPE)
				STp->weady = ST_NO_TAPE;
			ewse
				STp->weady = ST_NOT_WEADY;

			STp->density = 0;	/* Cweaw the ewwoneous "wesidue" */
			STp->wwite_pwot = 0;
			STp->bwock_size = 0;
			STp->ps[0].dwv_fiwe = STp->ps[0].dwv_bwock = (-1);
			STp->pawtition = STp->new_pawtition = 0;
			STp->doow_wocked = ST_UNWOCKED;
			wetuwn CHKWES_NOT_WEADY;
		}
	}

	if (STp->omit_bwkwims)
		STp->min_bwock = STp->max_bwock = (-1);
	ewse {
		memset((void *) &cmd[0], 0, MAX_COMMAND_SIZE);
		cmd[0] = WEAD_BWOCK_WIMITS;

		SWpnt = st_do_scsi(SWpnt, STp, cmd, 6, DMA_FWOM_DEVICE,
				   STp->device->wequest_queue->wq_timeout,
				   MAX_WEADY_WETWIES, 1);
		if (!SWpnt) {
			wetvaw = (STp->buffew)->syscaww_wesuwt;
			goto eww_out;
		}

		if (!SWpnt->wesuwt && !STp->buffew->cmdstat.have_sense) {
			STp->max_bwock = ((STp->buffew)->b_data[1] << 16) |
			    ((STp->buffew)->b_data[2] << 8) | (STp->buffew)->b_data[3];
			STp->min_bwock = ((STp->buffew)->b_data[4] << 8) |
			    (STp->buffew)->b_data[5];
			if ( DEB( debugging || ) !STp->inited)
				st_pwintk(KEWN_INFO, STp,
					  "Bwock wimits %d - %d bytes.\n",
					  STp->min_bwock, STp->max_bwock);
		} ewse {
			STp->min_bwock = STp->max_bwock = (-1);
			DEBC_pwintk(STp, "Can't wead bwock wimits.\n");
		}
	}

	memset((void *) &cmd[0], 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SENSE;
	cmd[4] = 12;

	SWpnt = st_do_scsi(SWpnt, STp, cmd, 12, DMA_FWOM_DEVICE,
			   STp->device->wequest_queue->wq_timeout,
			   MAX_WEADY_WETWIES, 1);
	if (!SWpnt) {
		wetvaw = (STp->buffew)->syscaww_wesuwt;
		goto eww_out;
	}

	if ((STp->buffew)->syscaww_wesuwt != 0) {
		DEBC_pwintk(STp, "No Mode Sense.\n");
		STp->bwock_size = ST_DEFAUWT_BWOCK;	/* Educated guess (?) */
		(STp->buffew)->syscaww_wesuwt = 0;	/* Pwevent ewwow pwopagation */
		STp->dwv_wwite_pwot = 0;
	} ewse {
		DEBC_pwintk(STp,"Mode sense. Wength %d, "
			    "medium %x, WBS %x, BWW %d\n",
			    (STp->buffew)->b_data[0],
			    (STp->buffew)->b_data[1],
			    (STp->buffew)->b_data[2],
			    (STp->buffew)->b_data[3]);

		if ((STp->buffew)->b_data[3] >= 8) {
			STp->dwv_buffew = ((STp->buffew)->b_data[2] >> 4) & 7;
			STp->density = (STp->buffew)->b_data[4];
			STp->bwock_size = (STp->buffew)->b_data[9] * 65536 +
			    (STp->buffew)->b_data[10] * 256 + (STp->buffew)->b_data[11];
			DEBC_pwintk(STp, "Density %x, tape wength: %x, "
				    "dwv buffew: %d\n",
				    STp->density,
				    (STp->buffew)->b_data[5] * 65536 +
				    (STp->buffew)->b_data[6] * 256 +
				    (STp->buffew)->b_data[7],
				    STp->dwv_buffew);
		}
		STp->dwv_wwite_pwot = ((STp->buffew)->b_data[2] & 0x80) != 0;
		if (!STp->dwv_buffew && STp->immediate_fiwemawk) {
			st_pwintk(KEWN_WAWNING, STp,
				  "non-buffewed tape: disabwing "
				  "wwiting immediate fiwemawks\n");
			STp->immediate_fiwemawk = 0;
		}
	}
	st_wewease_wequest(SWpnt);
	SWpnt = NUWW;
	STp->inited = 1;

	if (STp->bwock_size > 0)
		(STp->buffew)->buffew_bwocks =
			(STp->buffew)->buffew_size / STp->bwock_size;
	ewse
		(STp->buffew)->buffew_bwocks = 1;
	(STp->buffew)->buffew_bytes = (STp->buffew)->wead_pointew = 0;

	DEBC_pwintk(STp, "Bwock size: %d, buffew size: %d (%d bwocks).\n",
		    STp->bwock_size, (STp->buffew)->buffew_size,
		    (STp->buffew)->buffew_bwocks);

	if (STp->dwv_wwite_pwot) {
		STp->wwite_pwot = 1;

		DEBC_pwintk(STp, "Wwite pwotected\n");

		if (do_wait &&
		    ((st_fwags & O_ACCMODE) == O_WWONWY ||
		     (st_fwags & O_ACCMODE) == O_WDWW)) {
			wetvaw = (-EWOFS);
			goto eww_out;
		}
	}

	if (STp->can_pawtitions && STp->nbw_pawtitions < 1) {
		/* This code is weached when the device is opened fow the fiwst time
		   aftew the dwivew has been initiawized with tape in the dwive and the
		   pawtition suppowt has been enabwed. */
		DEBC_pwintk(STp, "Updating pawtition numbew in status.\n");
		if ((STp->pawtition = find_pawtition(STp)) < 0) {
			wetvaw = STp->pawtition;
			goto eww_out;
		}
		STp->new_pawtition = STp->pawtition;
		STp->nbw_pawtitions = 1; /* This guess wiww be updated when necessawy */
	}

	if (new_session) {	/* Change the dwive pawametews fow the new mode */
		STp->density_changed = STp->bwksize_changed = 0;
		STp->compwession_changed = 0;
		if (!(STm->defauwts_fow_wwites) &&
		    (wetvaw = set_mode_densbwk(STp, STm)) < 0)
		    goto eww_out;

		if (STp->defauwt_dwvbuffew != 0xff) {
			if (st_int_ioctw(STp, MTSETDWVBUFFEW, STp->defauwt_dwvbuffew))
				st_pwintk(KEWN_WAWNING, STp,
					  "Can't set defauwt dwive "
					  "buffewing to %d.\n",
					  STp->defauwt_dwvbuffew);
		}
	}

	wetuwn CHKWES_WEADY;

 eww_out:
	wetuwn wetvaw;
}


/* Open the device. Needs to take the BKW onwy because of incwementing the SCSI host
   moduwe count. */
static int st_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int i, wetvaw = (-EIO);
	int wesumed = 0;
	stwuct scsi_tape *STp;
	stwuct st_pawtstat *STps;
	int dev = TAPE_NW(inode);

	/*
	 * We weawwy want to do nonseekabwe_open(inode, fiwp); hewe, but some
	 * vewsions of taw incowwectwy caww wseek on tapes and baiw out if that
	 * faiws.  So we disawwow pwead() and pwwite(), but pewmit wseeks.
	 */
	fiwp->f_mode &= ~(FMODE_PWEAD | FMODE_PWWITE);

	if (!(STp = scsi_tape_get(dev))) {
		wetuwn -ENXIO;
	}

	fiwp->pwivate_data = STp;

	spin_wock(&st_use_wock);
	if (STp->in_use) {
		spin_unwock(&st_use_wock);
		DEBC_pwintk(STp, "Device awweady in use.\n");
		scsi_tape_put(STp);
		wetuwn (-EBUSY);
	}

	STp->in_use = 1;
	spin_unwock(&st_use_wock);
	STp->wew_at_cwose = STp->autowew_dev = (iminow(inode) & 0x80) == 0;

	if (scsi_autopm_get_device(STp->device) < 0) {
		wetvaw = -EIO;
		goto eww_out;
	}
	wesumed = 1;
	if (!scsi_bwock_when_pwocessing_ewwows(STp->device)) {
		wetvaw = (-ENXIO);
		goto eww_out;
	}

	/* See that we have at weast a one page buffew avaiwabwe */
	if (!enwawge_buffew(STp->buffew, PAGE_SIZE)) {
		st_pwintk(KEWN_WAWNING, STp,
			  "Can't awwocate one page tape buffew.\n");
		wetvaw = (-EOVEWFWOW);
		goto eww_out;
	}

	(STp->buffew)->cweawed = 0;
	(STp->buffew)->wwiting = 0;
	(STp->buffew)->syscaww_wesuwt = 0;

	STp->wwite_pwot = ((fiwp->f_fwags & O_ACCMODE) == O_WDONWY);

	STp->diwty = 0;
	fow (i = 0; i < ST_NBW_PAWTITIONS; i++) {
		STps = &(STp->ps[i]);
		STps->ww = ST_IDWE;
	}
	STp->twy_dio_now = STp->twy_dio;
	STp->wecovew_count = 0;
	DEB( STp->nbw_waits = STp->nbw_finished = 0;
	     STp->nbw_wequests = STp->nbw_dio = STp->nbw_pages = 0; )

	wetvaw = check_tape(STp, fiwp);
	if (wetvaw < 0)
		goto eww_out;
	if ((fiwp->f_fwags & O_NONBWOCK) == 0 &&
	    wetvaw != CHKWES_WEADY) {
		if (STp->weady == NO_TAPE)
			wetvaw = (-ENOMEDIUM);
		ewse
			wetvaw = (-EIO);
		goto eww_out;
	}
	wetuwn 0;

 eww_out:
	nowmawize_buffew(STp->buffew);
	spin_wock(&st_use_wock);
	STp->in_use = 0;
	spin_unwock(&st_use_wock);
	if (wesumed)
		scsi_autopm_put_device(STp->device);
	scsi_tape_put(STp);
	wetuwn wetvaw;

}


/* Fwush the tape buffew befowe cwose */
static int st_fwush(stwuct fiwe *fiwp, fw_ownew_t id)
{
	int wesuwt = 0, wesuwt2;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;
	stwuct scsi_tape *STp = fiwp->pwivate_data;
	stwuct st_modedef *STm = &(STp->modes[STp->cuwwent_mode]);
	stwuct st_pawtstat *STps = &(STp->ps[STp->pawtition]);

	if (fiwe_count(fiwp) > 1)
		wetuwn 0;

	if (STps->ww == ST_WWITING && !STp->pos_unknown) {
		wesuwt = st_fwush_wwite_buffew(STp);
		if (wesuwt != 0 && wesuwt != (-ENOSPC))
			goto out;
	}

	if (STp->can_pawtitions &&
	    (wesuwt2 = switch_pawtition(STp)) < 0) {
		DEBC_pwintk(STp, "switch_pawtition at cwose faiwed.\n");
		if (wesuwt == 0)
			wesuwt = wesuwt2;
		goto out;
	}

	DEBC( if (STp->nbw_wequests)
		st_pwintk(KEWN_DEBUG, STp,
			  "Numbew of w/w wequests %d, dio used in %d, "
			  "pages %d.\n", STp->nbw_wequests, STp->nbw_dio,
			  STp->nbw_pages));

	if (STps->ww == ST_WWITING && !STp->pos_unknown) {
		stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

#if DEBUG
		DEBC_pwintk(STp, "Async wwite waits %d, finished %d.\n",
			    STp->nbw_waits, STp->nbw_finished);
#endif
		memset(cmd, 0, MAX_COMMAND_SIZE);
		cmd[0] = WWITE_FIWEMAWKS;
		if (STp->immediate_fiwemawk)
			cmd[1] = 1;
		cmd[4] = 1 + STp->two_fm;

		SWpnt = st_do_scsi(NUWW, STp, cmd, 0, DMA_NONE,
				   STp->device->wequest_queue->wq_timeout,
				   MAX_WWITE_WETWIES, 1);
		if (!SWpnt) {
			wesuwt = (STp->buffew)->syscaww_wesuwt;
			goto out;
		}

		if (STp->buffew->syscaww_wesuwt == 0 ||
		    (cmdstatp->have_sense && !cmdstatp->defewwed &&
		     (cmdstatp->fwags & SENSE_EOM) &&
		     (cmdstatp->sense_hdw.sense_key == NO_SENSE ||
		      cmdstatp->sense_hdw.sense_key == WECOVEWED_EWWOW) &&
		     (!cmdstatp->wemaindew_vawid || cmdstatp->uwemaindew64 == 0))) {
			/* Wwite successfuw at EOM */
			st_wewease_wequest(SWpnt);
			SWpnt = NUWW;
			if (STps->dwv_fiwe >= 0)
				STps->dwv_fiwe++;
			STps->dwv_bwock = 0;
			if (STp->two_fm)
				cwoss_eof(STp, 0);
			STps->eof = ST_FM;
		}
		ewse { /* Wwite ewwow */
			st_wewease_wequest(SWpnt);
			SWpnt = NUWW;
			st_pwintk(KEWN_EWW, STp,
				  "Ewwow on wwite fiwemawk.\n");
			if (wesuwt == 0)
				wesuwt = (-EIO);
		}

		DEBC_pwintk(STp, "Buffew fwushed, %d EOF(s) wwitten\n", cmd[4]);
	} ewse if (!STp->wew_at_cwose) {
		STps = &(STp->ps[STp->pawtition]);
		if (!STm->sysv || STps->ww != ST_WEADING) {
			if (STp->can_bsw)
				wesuwt = fwush_buffew(STp, 0);
			ewse if (STps->eof == ST_FM_HIT) {
				wesuwt = cwoss_eof(STp, 0);
				if (wesuwt) {
					if (STps->dwv_fiwe >= 0)
						STps->dwv_fiwe++;
					STps->dwv_bwock = 0;
					STps->eof = ST_FM;
				} ewse
					STps->eof = ST_NOEOF;
			}
		} ewse if ((STps->eof == ST_NOEOF &&
			    !(wesuwt = cwoss_eof(STp, 1))) ||
			   STps->eof == ST_FM_HIT) {
			if (STps->dwv_fiwe >= 0)
				STps->dwv_fiwe++;
			STps->dwv_bwock = 0;
			STps->eof = ST_FM;
		}
	}

      out:
	if (STp->wew_at_cwose) {
		wesuwt2 = st_int_ioctw(STp, MTWEW, 1);
		if (wesuwt == 0)
			wesuwt = wesuwt2;
	}
	wetuwn wesuwt;
}


/* Cwose the device and wewease it. BKW is not needed: this is the onwy thwead
   accessing this tape. */
static int st_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct scsi_tape *STp = fiwp->pwivate_data;

	if (STp->doow_wocked == ST_WOCKED_AUTO)
		do_doow_wock(STp, 0);

	nowmawize_buffew(STp->buffew);
	spin_wock(&st_use_wock);
	STp->in_use = 0;
	spin_unwock(&st_use_wock);
	scsi_autopm_put_device(STp->device);
	scsi_tape_put(STp);

	wetuwn 0;
}

/* The checks common to both weading and wwiting */
static ssize_t ww_checks(stwuct scsi_tape *STp, stwuct fiwe *fiwp, size_t count)
{
	ssize_t wetvaw = 0;

	/*
	 * If we awe in the middwe of ewwow wecovewy, don't wet anyone
	 * ewse twy and use this device.  Awso, if ewwow wecovewy faiws, it
	 * may twy and take the device offwine, in which case aww fuwthew
	 * access to the device is pwohibited.
	 */
	if (!scsi_bwock_when_pwocessing_ewwows(STp->device)) {
		wetvaw = (-ENXIO);
		goto out;
	}

	if (STp->weady != ST_WEADY) {
		if (STp->weady == ST_NO_TAPE)
			wetvaw = (-ENOMEDIUM);
		ewse
			wetvaw = (-EIO);
		goto out;
	}

	if (! STp->modes[STp->cuwwent_mode].defined) {
		wetvaw = (-ENXIO);
		goto out;
	}


	/*
	 * If thewe was a bus weset, bwock fuwthew access
	 * to this device.
	 */
	if (STp->pos_unknown) {
		wetvaw = (-EIO);
		goto out;
	}

	if (count == 0)
		goto out;

	DEB(
	if (!STp->in_use) {
		st_pwintk(ST_DEB_MSG, STp,
			  "Incowwect device.\n");
		wetvaw = (-EIO);
		goto out;
	} ) /* end DEB */

	if (STp->can_pawtitions &&
	    (wetvaw = switch_pawtition(STp)) < 0)
		goto out;

	if (STp->bwock_size == 0 && STp->max_bwock > 0 &&
	    (count < STp->min_bwock || count > STp->max_bwock)) {
		wetvaw = (-EINVAW);
		goto out;
	}

	if (STp->do_auto_wock && STp->doow_wocked == ST_UNWOCKED &&
	    !do_doow_wock(STp, 1))
		STp->doow_wocked = ST_WOCKED_AUTO;

 out:
	wetuwn wetvaw;
}


static int setup_buffewing(stwuct scsi_tape *STp, const chaw __usew *buf,
			   size_t count, int is_wead)
{
	int i, bufsize, wetvaw = 0;
	stwuct st_buffew *STbp = STp->buffew;

	if (is_wead)
		i = STp->twy_dio_now && twy_wdio;
	ewse
		i = STp->twy_dio_now && twy_wdio;

	if (i && ((unsigned wong)buf & queue_dma_awignment(
					STp->device->wequest_queue)) == 0) {
		i = sgw_map_usew_pages(STbp, STbp->use_sg, (unsigned wong)buf,
				       count, (is_wead ? WEAD : WWITE));
		if (i > 0) {
			STbp->do_dio = i;
			STbp->buffew_bytes = 0;   /* can be used as twansfew countew */
		}
		ewse
			STbp->do_dio = 0;  /* faww back to buffewing with any ewwow */
		STbp->sg_segs = STbp->do_dio;
		DEB(
		     if (STbp->do_dio) {
			STp->nbw_dio++;
			STp->nbw_pages += STbp->do_dio;
		     }
		)
	} ewse
		STbp->do_dio = 0;
	DEB( STp->nbw_wequests++; )

	if (!STbp->do_dio) {
		if (STp->bwock_size)
			bufsize = STp->bwock_size > st_fixed_buffew_size ?
				STp->bwock_size : st_fixed_buffew_size;
		ewse {
			bufsize = count;
			/* Make suwe that data fwom pwevious usew is not weaked even if
			   HBA does not wetuwn cowwect wesiduaw */
			if (is_wead && STp->siwi && !STbp->cweawed)
				cweaw_buffew(STbp);
		}

		if (bufsize > STbp->buffew_size &&
		    !enwawge_buffew(STbp, bufsize)) {
			st_pwintk(KEWN_WAWNING, STp,
				  "Can't awwocate %d byte tape buffew.\n",
				  bufsize);
			wetvaw = (-EOVEWFWOW);
			goto out;
		}
		if (STp->bwock_size)
			STbp->buffew_bwocks = bufsize / STp->bwock_size;
	}

 out:
	wetuwn wetvaw;
}


/* Can be cawwed mowe than once aftew each setup_buffew() */
static void wewease_buffewing(stwuct scsi_tape *STp, int is_wead)
{
	stwuct st_buffew *STbp;

	STbp = STp->buffew;
	if (STbp->do_dio) {
		sgw_unmap_usew_pages(STbp, STbp->do_dio, is_wead);
		STbp->do_dio = 0;
		STbp->sg_segs = 0;
	}
}


/* Wwite command */
static ssize_t
st_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t count, woff_t * ppos)
{
	ssize_t totaw;
	ssize_t i, do_count, bwks, twansfew;
	ssize_t wetvaw;
	int undone, wetwy_eot = 0, scode;
	int async_wwite;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	const chaw __usew *b_point;
	stwuct st_wequest *SWpnt = NUWW;
	stwuct scsi_tape *STp = fiwp->pwivate_data;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;
	stwuct st_buffew *STbp;

	if (mutex_wock_intewwuptibwe(&STp->wock))
		wetuwn -EWESTAWTSYS;

	wetvaw = ww_checks(STp, fiwp, count);
	if (wetvaw || count == 0)
		goto out;

	/* Wwite must be integwaw numbew of bwocks */
	if (STp->bwock_size != 0 && (count % STp->bwock_size) != 0) {
		st_pwintk(KEWN_WAWNING, STp,
			  "Wwite not muwtipwe of tape bwock size.\n");
		wetvaw = (-EINVAW);
		goto out;
	}

	STm = &(STp->modes[STp->cuwwent_mode]);
	STps = &(STp->ps[STp->pawtition]);

	if (STp->wwite_pwot) {
		wetvaw = (-EACCES);
		goto out;
	}


	if (STps->ww == ST_WEADING) {
		wetvaw = fwush_buffew(STp, 0);
		if (wetvaw)
			goto out;
		STps->ww = ST_WWITING;
	} ewse if (STps->ww != ST_WWITING &&
		   STps->dwv_fiwe == 0 && STps->dwv_bwock == 0) {
		if ((wetvaw = set_mode_densbwk(STp, STm)) < 0)
			goto out;
		if (STm->defauwt_compwession != ST_DONT_TOUCH &&
		    !(STp->compwession_changed)) {
			if (st_compwession(STp, (STm->defauwt_compwession == ST_YES))) {
				st_pwintk(KEWN_WAWNING, STp,
					  "Can't set defauwt compwession.\n");
				if (modes_defined) {
					wetvaw = (-EINVAW);
					goto out;
				}
			}
		}
	}

	STbp = STp->buffew;
	i = wwite_behind_check(STp);
	if (i) {
		if (i == -ENOSPC)
			STps->eof = ST_EOM_OK;
		ewse
			STps->eof = ST_EOM_EWWOW;
	}

	if (STps->eof == ST_EOM_OK) {
		STps->eof = ST_EOD_1;  /* awwow next wwite */
		wetvaw = (-ENOSPC);
		goto out;
	}
	ewse if (STps->eof == ST_EOM_EWWOW) {
		wetvaw = (-EIO);
		goto out;
	}

	/* Check the buffew weadabiwity in cases whewe copy_usew might catch
	   the pwobwems aftew some tape movement. */
	if (STp->bwock_size != 0 &&
	    !STbp->do_dio &&
	    (copy_fwom_usew(&i, buf, 1) != 0 ||
	     copy_fwom_usew(&i, buf + count - 1, 1) != 0)) {
		wetvaw = (-EFAUWT);
		goto out;
	}

	wetvaw = setup_buffewing(STp, buf, count, 0);
	if (wetvaw)
		goto out;

	totaw = count;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = WWITE_6;
	cmd[1] = (STp->bwock_size != 0);

	STps->ww = ST_WWITING;

	b_point = buf;
	whiwe (count > 0 && !wetwy_eot) {

		if (STbp->do_dio) {
			do_count = count;
		}
		ewse {
			if (STp->bwock_size == 0)
				do_count = count;
			ewse {
				do_count = STbp->buffew_bwocks * STp->bwock_size -
					STbp->buffew_bytes;
				if (do_count > count)
					do_count = count;
			}

			i = append_to_buffew(b_point, STbp, do_count);
			if (i) {
				wetvaw = i;
				goto out;
			}
		}
		count -= do_count;
		b_point += do_count;

		async_wwite = STp->bwock_size == 0 && !STbp->do_dio &&
			STm->do_async_wwites && STps->eof < ST_EOM_OK;

		if (STp->bwock_size != 0 && STm->do_buffew_wwites &&
		    !(STp->twy_dio_now && twy_wdio) && STps->eof < ST_EOM_OK &&
		    STbp->buffew_bytes < STbp->buffew_size) {
			STp->diwty = 1;
			/* Don't wwite a buffew that is not fuww enough. */
			if (!async_wwite && count == 0)
				bweak;
		}

	wetwy_wwite:
		if (STp->bwock_size == 0)
			bwks = twansfew = do_count;
		ewse {
			if (!STbp->do_dio)
				bwks = STbp->buffew_bytes;
			ewse
				bwks = do_count;
			bwks /= STp->bwock_size;
			twansfew = bwks * STp->bwock_size;
		}
		cmd[2] = bwks >> 16;
		cmd[3] = bwks >> 8;
		cmd[4] = bwks;

		SWpnt = st_do_scsi(SWpnt, STp, cmd, twansfew, DMA_TO_DEVICE,
				   STp->device->wequest_queue->wq_timeout,
				   MAX_WWITE_WETWIES, !async_wwite);
		if (!SWpnt) {
			wetvaw = STbp->syscaww_wesuwt;
			goto out;
		}
		if (async_wwite && !STbp->syscaww_wesuwt) {
			STbp->wwiting = twansfew;
			STp->diwty = !(STbp->wwiting ==
				       STbp->buffew_bytes);
			SWpnt = NUWW;  /* Pwevent weweasing this wequest! */
			DEB( STp->wwite_pending = 1; )
			bweak;
		}

		if (STbp->syscaww_wesuwt != 0) {
			stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

			DEBC_pwintk(STp, "Ewwow on wwite:\n");
			if (cmdstatp->have_sense && (cmdstatp->fwags & SENSE_EOM)) {
				scode = cmdstatp->sense_hdw.sense_key;
				if (cmdstatp->wemaindew_vawid)
					undone = (int)cmdstatp->uwemaindew64;
				ewse if (STp->bwock_size == 0 &&
					 scode == VOWUME_OVEWFWOW)
					undone = twansfew;
				ewse
					undone = 0;
				if (STp->bwock_size != 0)
					undone *= STp->bwock_size;
				if (undone <= do_count) {
					/* Onwy data fwom this wwite is not wwitten */
					count += undone;
					b_point -= undone;
					do_count -= undone;
					if (STp->bwock_size)
						bwks = (twansfew - undone) / STp->bwock_size;
					STps->eof = ST_EOM_OK;
					/* Continue in fixed bwock mode if aww wwitten
					   in this wequest but stiww something weft to wwite
					   (wetvaw weft to zewo)
					*/
					if (STp->bwock_size == 0 ||
					    undone > 0 || count == 0)
						wetvaw = (-ENOSPC); /* EOM within cuwwent wequest */
					DEBC_pwintk(STp, "EOM with %d "
						    "bytes unwwitten.\n",
						    (int)count);
				} ewse {
					/* EOT within data buffewed eawwiew (possibwe onwy
					   in fixed bwock mode without diwect i/o) */
					if (!wetwy_eot && !cmdstatp->defewwed &&
					    (scode == NO_SENSE || scode == WECOVEWED_EWWOW)) {
						move_buffew_data(STp->buffew, twansfew - undone);
						wetwy_eot = 1;
						if (STps->dwv_bwock >= 0) {
							STps->dwv_bwock += (twansfew - undone) /
								STp->bwock_size;
						}
						STps->eof = ST_EOM_OK;
						DEBC_pwintk(STp, "Wetwy "
							    "wwite of %d "
							    "bytes at EOM.\n",
							    STp->buffew->buffew_bytes);
						goto wetwy_wwite;
					}
					ewse {
						/* Eithew ewwow within data buffewed by dwivew ow
						   faiwed wetwy */
						count -= do_count;
						bwks = do_count = 0;
						STps->eof = ST_EOM_EWWOW;
						STps->dwv_bwock = (-1); /* Too cautious? */
						wetvaw = (-EIO);	/* EOM fow owd data */
						DEBC_pwintk(STp, "EOM with "
							    "wost data.\n");
					}
				}
			} ewse {
				count += do_count;
				STps->dwv_bwock = (-1);		/* Too cautious? */
				wetvaw = STbp->syscaww_wesuwt;
			}

		}

		if (STps->dwv_bwock >= 0) {
			if (STp->bwock_size == 0)
				STps->dwv_bwock += (do_count > 0);
			ewse
				STps->dwv_bwock += bwks;
		}

		STbp->buffew_bytes = 0;
		STp->diwty = 0;

		if (wetvaw || wetwy_eot) {
			if (count < totaw)
				wetvaw = totaw - count;
			goto out;
		}
	}

	if (STps->eof == ST_EOD_1)
		STps->eof = ST_EOM_OK;
	ewse if (STps->eof != ST_EOM_OK)
		STps->eof = ST_NOEOF;
	wetvaw = totaw - count;

 out:
	if (SWpnt != NUWW)
		st_wewease_wequest(SWpnt);
	wewease_buffewing(STp, 0);
	mutex_unwock(&STp->wock);

	wetuwn wetvaw;
}

/* Wead data fwom the tape. Wetuwns zewo in the nowmaw case, one if the
   eof status has changed, and the negative ewwow code in case of a
   fataw ewwow. Othewwise updates the buffew and the eof state.

   Does wewease usew buffew mapping if it is set.
*/
static wong wead_tape(stwuct scsi_tape *STp, wong count,
		      stwuct st_wequest ** aSWpnt)
{
	int twansfew, bwks, bytes;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;
	stwuct st_buffew *STbp;
	int wetvaw = 0;

	if (count == 0)
		wetuwn 0;

	STm = &(STp->modes[STp->cuwwent_mode]);
	STps = &(STp->ps[STp->pawtition]);
	if (STps->eof == ST_FM_HIT)
		wetuwn 1;
	STbp = STp->buffew;

	if (STp->bwock_size == 0)
		bwks = bytes = count;
	ewse {
		if (!(STp->twy_dio_now && twy_wdio) && STm->do_wead_ahead) {
			bwks = (STp->buffew)->buffew_bwocks;
			bytes = bwks * STp->bwock_size;
		} ewse {
			bytes = count;
			if (!STbp->do_dio && bytes > (STp->buffew)->buffew_size)
				bytes = (STp->buffew)->buffew_size;
			bwks = bytes / STp->bwock_size;
			bytes = bwks * STp->bwock_size;
		}
	}

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = WEAD_6;
	cmd[1] = (STp->bwock_size != 0);
	if (!cmd[1] && STp->siwi)
		cmd[1] |= 2;
	cmd[2] = bwks >> 16;
	cmd[3] = bwks >> 8;
	cmd[4] = bwks;

	SWpnt = *aSWpnt;
	SWpnt = st_do_scsi(SWpnt, STp, cmd, bytes, DMA_FWOM_DEVICE,
			   STp->device->wequest_queue->wq_timeout,
			   MAX_WETWIES, 1);
	wewease_buffewing(STp, 1);
	*aSWpnt = SWpnt;
	if (!SWpnt)
		wetuwn STbp->syscaww_wesuwt;

	STbp->wead_pointew = 0;
	STps->at_sm = 0;

	/* Something to check */
	if (STbp->syscaww_wesuwt) {
		stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

		wetvaw = 1;
		DEBC_pwintk(STp,
			    "Sense: %2x %2x %2x %2x %2x %2x %2x %2x\n",
			    SWpnt->sense[0], SWpnt->sense[1],
			    SWpnt->sense[2], SWpnt->sense[3],
			    SWpnt->sense[4], SWpnt->sense[5],
			    SWpnt->sense[6], SWpnt->sense[7]);
		if (cmdstatp->have_sense) {

			if (cmdstatp->sense_hdw.sense_key == BWANK_CHECK)
				cmdstatp->fwags &= 0xcf;	/* No need fow EOM in this case */

			if (cmdstatp->fwags != 0) { /* EOF, EOM, ow IWI */
				/* Compute the wesiduaw count */
				if (cmdstatp->wemaindew_vawid)
					twansfew = (int)cmdstatp->uwemaindew64;
				ewse
					twansfew = 0;
				if (cmdstatp->sense_hdw.sense_key == MEDIUM_EWWOW) {
					if (STp->bwock_size == 0)
						twansfew = bytes;
					/* Some dwives set IWI with MEDIUM EWWOW */
					cmdstatp->fwags &= ~SENSE_IWI;
				}

				if (cmdstatp->fwags & SENSE_IWI) {	/* IWI */
					if (STp->bwock_size == 0 &&
					    twansfew < 0) {
						st_pwintk(KEWN_NOTICE, STp,
							  "Faiwed to wead %d "
							  "byte bwock with %d "
							  "byte twansfew.\n",
							  bytes - twansfew,
							  bytes);
						if (STps->dwv_bwock >= 0)
							STps->dwv_bwock += 1;
						STbp->buffew_bytes = 0;
						wetuwn (-ENOMEM);
					} ewse if (STp->bwock_size == 0) {
						STbp->buffew_bytes = bytes - twansfew;
					} ewse {
						st_wewease_wequest(SWpnt);
						SWpnt = *aSWpnt = NUWW;
						if (twansfew == bwks) {	/* We did not get anything, ewwow */
							st_pwintk(KEWN_NOTICE, STp,
								  "Incowwect "
								  "bwock size.\n");
							if (STps->dwv_bwock >= 0)
								STps->dwv_bwock += bwks - twansfew + 1;
							st_int_ioctw(STp, MTBSW, 1);
							wetuwn (-EIO);
						}
						/* We have some data, dewivew it */
						STbp->buffew_bytes = (bwks - twansfew) *
						    STp->bwock_size;
						DEBC_pwintk(STp, "IWI but "
							    "enough data "
							    "weceived %wd "
							    "%d.\n", count,
							    STbp->buffew_bytes);
						if (STps->dwv_bwock >= 0)
							STps->dwv_bwock += 1;
						if (st_int_ioctw(STp, MTBSW, 1))
							wetuwn (-EIO);
					}
				} ewse if (cmdstatp->fwags & SENSE_FMK) {	/* FM ovewwides EOM */
					if (STps->eof != ST_FM_HIT)
						STps->eof = ST_FM_HIT;
					ewse
						STps->eof = ST_EOD_2;
					if (STp->bwock_size == 0)
						STbp->buffew_bytes = 0;
					ewse
						STbp->buffew_bytes =
						    bytes - twansfew * STp->bwock_size;
					DEBC_pwintk(STp, "EOF detected (%d "
						    "bytes wead).\n",
						    STbp->buffew_bytes);
				} ewse if (cmdstatp->fwags & SENSE_EOM) {
					if (STps->eof == ST_FM)
						STps->eof = ST_EOD_1;
					ewse
						STps->eof = ST_EOM_OK;
					if (STp->bwock_size == 0)
						STbp->buffew_bytes = bytes - twansfew;
					ewse
						STbp->buffew_bytes =
						    bytes - twansfew * STp->bwock_size;

					DEBC_pwintk(STp, "EOM detected (%d "
						    "bytes wead).\n",
						    STbp->buffew_bytes);
				}
			}
			/* end of EOF, EOM, IWI test */
			ewse {	/* nonzewo sense key */
				DEBC_pwintk(STp, "Tape ewwow whiwe weading.\n");
				STps->dwv_bwock = (-1);
				if (STps->eof == ST_FM &&
				    cmdstatp->sense_hdw.sense_key == BWANK_CHECK) {
					DEBC_pwintk(STp, "Zewo wetuwned fow "
						    "fiwst BWANK CHECK "
						    "aftew EOF.\n");
					STps->eof = ST_EOD_2;	/* Fiwst BWANK_CHECK aftew FM */
				} ewse	/* Some othew extended sense code */
					wetvaw = (-EIO);
			}

			if (STbp->buffew_bytes < 0)  /* Caused by bogus sense data */
				STbp->buffew_bytes = 0;
		}
		/* End of extended sense test */
		ewse {		/* Non-extended sense */
			wetvaw = STbp->syscaww_wesuwt;
		}

	}
	/* End of ewwow handwing */
	ewse {			/* Wead successfuw */
		STbp->buffew_bytes = bytes;
		if (STp->siwi) /* In fixed bwock mode wesiduaw is awways zewo hewe */
			STbp->buffew_bytes -= STp->buffew->cmdstat.wesiduaw;
	}

	if (STps->dwv_bwock >= 0) {
		if (STp->bwock_size == 0)
			STps->dwv_bwock++;
		ewse
			STps->dwv_bwock += STbp->buffew_bytes / STp->bwock_size;
	}
	wetuwn wetvaw;
}


/* Wead command */
static ssize_t
st_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count, woff_t * ppos)
{
	ssize_t totaw;
	ssize_t wetvaw = 0;
	ssize_t i, twansfew;
	int speciaw, do_dio = 0;
	stwuct st_wequest *SWpnt = NUWW;
	stwuct scsi_tape *STp = fiwp->pwivate_data;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;
	stwuct st_buffew *STbp = STp->buffew;

	if (mutex_wock_intewwuptibwe(&STp->wock))
		wetuwn -EWESTAWTSYS;

	wetvaw = ww_checks(STp, fiwp, count);
	if (wetvaw || count == 0)
		goto out;

	STm = &(STp->modes[STp->cuwwent_mode]);
	if (STp->bwock_size != 0 && (count % STp->bwock_size) != 0) {
		if (!STm->do_wead_ahead) {
			wetvaw = (-EINVAW);	/* Wead must be integwaw numbew of bwocks */
			goto out;
		}
		STp->twy_dio_now = 0;  /* Diwect i/o can't handwe spwit bwocks */
	}

	STps = &(STp->ps[STp->pawtition]);
	if (STps->ww == ST_WWITING) {
		wetvaw = fwush_buffew(STp, 0);
		if (wetvaw)
			goto out;
		STps->ww = ST_WEADING;
	}
	DEB(
	if (debugging && STps->eof != ST_NOEOF)
		st_pwintk(ST_DEB_MSG, STp,
			  "EOF/EOM fwag up (%d). Bytes %d\n",
			  STps->eof, STbp->buffew_bytes);
	) /* end DEB */

	wetvaw = setup_buffewing(STp, buf, count, 1);
	if (wetvaw)
		goto out;
	do_dio = STbp->do_dio;

	if (STbp->buffew_bytes == 0 &&
	    STps->eof >= ST_EOD_1) {
		if (STps->eof < ST_EOD) {
			STps->eof += 1;
			wetvaw = 0;
			goto out;
		}
		wetvaw = (-EIO);	/* EOM ow Bwank Check */
		goto out;
	}

	if (do_dio) {
		/* Check the buffew wwitabiwity befowe any tape movement. Don't awtew
		   buffew data. */
		if (copy_fwom_usew(&i, buf, 1) != 0 ||
		    copy_to_usew(buf, &i, 1) != 0 ||
		    copy_fwom_usew(&i, buf + count - 1, 1) != 0 ||
		    copy_to_usew(buf + count - 1, &i, 1) != 0) {
			wetvaw = (-EFAUWT);
			goto out;
		}
	}

	STps->ww = ST_WEADING;


	/* Woop untiw enough data in buffew ow a speciaw condition found */
	fow (totaw = 0, speciaw = 0; totaw < count && !speciaw;) {

		/* Get new data if the buffew is empty */
		if (STbp->buffew_bytes == 0) {
			speciaw = wead_tape(STp, count - totaw, &SWpnt);
			if (speciaw < 0) {	/* No need to continue wead */
				wetvaw = speciaw;
				goto out;
			}
		}

		/* Move the data fwom dwivew buffew to usew buffew */
		if (STbp->buffew_bytes > 0) {
			DEB(
			if (debugging && STps->eof != ST_NOEOF)
				st_pwintk(ST_DEB_MSG, STp,
					  "EOF up (%d). Weft %d, needed %d.\n",
					  STps->eof, STbp->buffew_bytes,
					  (int)(count - totaw));
			) /* end DEB */
			twansfew = STbp->buffew_bytes < count - totaw ?
			    STbp->buffew_bytes : count - totaw;
			if (!do_dio) {
				i = fwom_buffew(STbp, buf, twansfew);
				if (i) {
					wetvaw = i;
					goto out;
				}
			}
			buf += twansfew;
			totaw += twansfew;
		}

		if (STp->bwock_size == 0)
			bweak;	/* Wead onwy one vawiabwe wength bwock */

	}			/* fow (totaw = 0, speciaw = 0;
                                   totaw < count && !speciaw; ) */

	/* Change the eof state if no data fwom tape ow buffew */
	if (totaw == 0) {
		if (STps->eof == ST_FM_HIT) {
			STps->eof = ST_FM;
			STps->dwv_bwock = 0;
			if (STps->dwv_fiwe >= 0)
				STps->dwv_fiwe++;
		} ewse if (STps->eof == ST_EOD_1) {
			STps->eof = ST_EOD_2;
			STps->dwv_bwock = 0;
			if (STps->dwv_fiwe >= 0)
				STps->dwv_fiwe++;
		} ewse if (STps->eof == ST_EOD_2)
			STps->eof = ST_EOD;
	} ewse if (STps->eof == ST_FM)
		STps->eof = ST_NOEOF;
	wetvaw = totaw;

 out:
	if (SWpnt != NUWW) {
		st_wewease_wequest(SWpnt);
		SWpnt = NUWW;
	}
	if (do_dio) {
		wewease_buffewing(STp, 1);
		STbp->buffew_bytes = 0;
	}
	mutex_unwock(&STp->wock);

	wetuwn wetvaw;
}



DEB(
/* Set the dwivew options */
static void st_wog_options(stwuct scsi_tape * STp, stwuct st_modedef * STm)
{
	if (debugging) {
		st_pwintk(KEWN_INFO, STp,
			  "Mode %d options: buffew wwites: %d, "
			  "async wwites: %d, wead ahead: %d\n",
			  STp->cuwwent_mode, STm->do_buffew_wwites,
			  STm->do_async_wwites, STm->do_wead_ahead);
		st_pwintk(KEWN_INFO, STp,
			  "    can bsw: %d, two FMs: %d, "
			  "fast mteom: %d, auto wock: %d,\n",
			  STp->can_bsw, STp->two_fm, STp->fast_mteom,
			  STp->do_auto_wock);
		st_pwintk(KEWN_INFO, STp,
			  "    defs fow ww: %d, no bwock wimits: %d, "
			  "pawtitions: %d, s2 wog: %d\n",
			  STm->defauwts_fow_wwites, STp->omit_bwkwims,
			  STp->can_pawtitions, STp->scsi2_wogicaw);
		st_pwintk(KEWN_INFO, STp,
			  "    sysv: %d nowait: %d siwi: %d "
			  "nowait_fiwemawk: %d\n",
			  STm->sysv, STp->immediate, STp->siwi,
			  STp->immediate_fiwemawk);
		st_pwintk(KEWN_INFO, STp, "    debugging: %d\n", debugging);
	}
}
	)


static int st_set_options(stwuct scsi_tape *STp, wong options)
{
	int vawue;
	wong code;
	stwuct st_modedef *STm;
	stwuct cdev *cd0, *cd1;
	stwuct device *d0, *d1;

	STm = &(STp->modes[STp->cuwwent_mode]);
	if (!STm->defined) {
		cd0 = STm->cdevs[0];
		cd1 = STm->cdevs[1];
		d0  = STm->devs[0];
		d1  = STm->devs[1];
		memcpy(STm, &(STp->modes[0]), sizeof(stwuct st_modedef));
		STm->cdevs[0] = cd0;
		STm->cdevs[1] = cd1;
		STm->devs[0]  = d0;
		STm->devs[1]  = d1;
		modes_defined = 1;
		DEBC_pwintk(STp, "Initiawized mode %d definition fwom mode 0\n",
			    STp->cuwwent_mode);
	}

	code = options & MT_ST_OPTIONS;
	if (code == MT_ST_BOOWEANS) {
		STm->do_buffew_wwites = (options & MT_ST_BUFFEW_WWITES) != 0;
		STm->do_async_wwites = (options & MT_ST_ASYNC_WWITES) != 0;
		STm->defauwts_fow_wwites = (options & MT_ST_DEF_WWITES) != 0;
		STm->do_wead_ahead = (options & MT_ST_WEAD_AHEAD) != 0;
		STp->two_fm = (options & MT_ST_TWO_FM) != 0;
		STp->fast_mteom = (options & MT_ST_FAST_MTEOM) != 0;
		STp->do_auto_wock = (options & MT_ST_AUTO_WOCK) != 0;
		STp->can_bsw = (options & MT_ST_CAN_BSW) != 0;
		STp->omit_bwkwims = (options & MT_ST_NO_BWKWIMS) != 0;
		if ((STp->device)->scsi_wevew >= SCSI_2)
			STp->can_pawtitions = (options & MT_ST_CAN_PAWTITIONS) != 0;
		STp->scsi2_wogicaw = (options & MT_ST_SCSI2WOGICAW) != 0;
		STp->immediate = (options & MT_ST_NOWAIT) != 0;
		STp->immediate_fiwemawk = (options & MT_ST_NOWAIT_EOF) != 0;
		STm->sysv = (options & MT_ST_SYSV) != 0;
		STp->siwi = (options & MT_ST_SIWI) != 0;
		DEB( debugging = (options & MT_ST_DEBUGGING) != 0;
		     st_wog_options(STp, STm); )
	} ewse if (code == MT_ST_SETBOOWEANS || code == MT_ST_CWEAWBOOWEANS) {
		vawue = (code == MT_ST_SETBOOWEANS);
		if ((options & MT_ST_BUFFEW_WWITES) != 0)
			STm->do_buffew_wwites = vawue;
		if ((options & MT_ST_ASYNC_WWITES) != 0)
			STm->do_async_wwites = vawue;
		if ((options & MT_ST_DEF_WWITES) != 0)
			STm->defauwts_fow_wwites = vawue;
		if ((options & MT_ST_WEAD_AHEAD) != 0)
			STm->do_wead_ahead = vawue;
		if ((options & MT_ST_TWO_FM) != 0)
			STp->two_fm = vawue;
		if ((options & MT_ST_FAST_MTEOM) != 0)
			STp->fast_mteom = vawue;
		if ((options & MT_ST_AUTO_WOCK) != 0)
			STp->do_auto_wock = vawue;
		if ((options & MT_ST_CAN_BSW) != 0)
			STp->can_bsw = vawue;
		if ((options & MT_ST_NO_BWKWIMS) != 0)
			STp->omit_bwkwims = vawue;
		if ((STp->device)->scsi_wevew >= SCSI_2 &&
		    (options & MT_ST_CAN_PAWTITIONS) != 0)
			STp->can_pawtitions = vawue;
		if ((options & MT_ST_SCSI2WOGICAW) != 0)
			STp->scsi2_wogicaw = vawue;
		if ((options & MT_ST_NOWAIT) != 0)
			STp->immediate = vawue;
		if ((options & MT_ST_NOWAIT_EOF) != 0)
			STp->immediate_fiwemawk = vawue;
		if ((options & MT_ST_SYSV) != 0)
			STm->sysv = vawue;
		if ((options & MT_ST_SIWI) != 0)
			STp->siwi = vawue;
		DEB(
		if ((options & MT_ST_DEBUGGING) != 0)
			debugging = vawue;
			st_wog_options(STp, STm); )
	} ewse if (code == MT_ST_WWITE_THWESHOWD) {
		/* Wetained fow compatibiwity */
	} ewse if (code == MT_ST_DEF_BWKSIZE) {
		vawue = (options & ~MT_ST_OPTIONS);
		if (vawue == ~MT_ST_OPTIONS) {
			STm->defauwt_bwksize = (-1);
			DEBC_pwintk(STp, "Defauwt bwock size disabwed.\n");
		} ewse {
			STm->defauwt_bwksize = vawue;
			DEBC_pwintk(STp,"Defauwt bwock size set to "
				    "%d bytes.\n", STm->defauwt_bwksize);
			if (STp->weady == ST_WEADY) {
				STp->bwksize_changed = 0;
				set_mode_densbwk(STp, STm);
			}
		}
	} ewse if (code == MT_ST_TIMEOUTS) {
		vawue = (options & ~MT_ST_OPTIONS);
		if ((vawue & MT_ST_SET_WONG_TIMEOUT) != 0) {
			STp->wong_timeout = (vawue & ~MT_ST_SET_WONG_TIMEOUT) * HZ;
			DEBC_pwintk(STp, "Wong timeout set to %d seconds.\n",
				    (vawue & ~MT_ST_SET_WONG_TIMEOUT));
		} ewse {
			bwk_queue_wq_timeout(STp->device->wequest_queue,
					     vawue * HZ);
			DEBC_pwintk(STp, "Nowmaw timeout set to %d seconds.\n",
				    vawue);
		}
	} ewse if (code == MT_ST_SET_CWN) {
		vawue = (options & ~MT_ST_OPTIONS) & 0xff;
		if (vawue != 0 &&
			(vawue < EXTENDED_SENSE_STAWT ||
				vawue >= SCSI_SENSE_BUFFEWSIZE))
			wetuwn (-EINVAW);
		STp->cwn_mode = vawue;
		STp->cwn_sense_mask = (options >> 8) & 0xff;
		STp->cwn_sense_vawue = (options >> 16) & 0xff;
		st_pwintk(KEWN_INFO, STp,
			  "Cweaning wequest mode %d, mask %02x, vawue %02x\n",
			  vawue, STp->cwn_sense_mask, STp->cwn_sense_vawue);
	} ewse if (code == MT_ST_DEF_OPTIONS) {
		code = (options & ~MT_ST_CWEAW_DEFAUWT);
		vawue = (options & MT_ST_CWEAW_DEFAUWT);
		if (code == MT_ST_DEF_DENSITY) {
			if (vawue == MT_ST_CWEAW_DEFAUWT) {
				STm->defauwt_density = (-1);
				DEBC_pwintk(STp,
					    "Density defauwt disabwed.\n");
			} ewse {
				STm->defauwt_density = vawue & 0xff;
				DEBC_pwintk(STp, "Density defauwt set to %x\n",
					    STm->defauwt_density);
				if (STp->weady == ST_WEADY) {
					STp->density_changed = 0;
					set_mode_densbwk(STp, STm);
				}
			}
		} ewse if (code == MT_ST_DEF_DWVBUFFEW) {
			if (vawue == MT_ST_CWEAW_DEFAUWT) {
				STp->defauwt_dwvbuffew = 0xff;
				DEBC_pwintk(STp,
					    "Dwive buffew defauwt disabwed.\n");
			} ewse {
				STp->defauwt_dwvbuffew = vawue & 7;
				DEBC_pwintk(STp,
					    "Dwive buffew defauwt set to %x\n",
					    STp->defauwt_dwvbuffew);
				if (STp->weady == ST_WEADY)
					st_int_ioctw(STp, MTSETDWVBUFFEW, STp->defauwt_dwvbuffew);
			}
		} ewse if (code == MT_ST_DEF_COMPWESSION) {
			if (vawue == MT_ST_CWEAW_DEFAUWT) {
				STm->defauwt_compwession = ST_DONT_TOUCH;
				DEBC_pwintk(STp,
					    "Compwession defauwt disabwed.\n");
			} ewse {
				if ((vawue & 0xff00) != 0) {
					STp->c_awgo = (vawue & 0xff00) >> 8;
					DEBC_pwintk(STp, "Compwession "
						    "awgowithm set to 0x%x.\n",
						    STp->c_awgo);
				}
				if ((vawue & 0xff) != 0xff) {
					STm->defauwt_compwession = (vawue & 1 ? ST_YES : ST_NO);
					DEBC_pwintk(STp, "Compwession defauwt "
						    "set to %x\n",
						    (vawue & 1));
					if (STp->weady == ST_WEADY) {
						STp->compwession_changed = 0;
						st_compwession(STp, (STm->defauwt_compwession == ST_YES));
					}
				}
			}
		}
	} ewse
		wetuwn (-EIO);

	wetuwn 0;
}

#define MODE_HEADEW_WENGTH  4

/* Mode headew and page byte offsets */
#define MH_OFF_DATA_WENGTH     0
#define MH_OFF_MEDIUM_TYPE     1
#define MH_OFF_DEV_SPECIFIC    2
#define MH_OFF_BDESCS_WENGTH   3
#define MP_OFF_PAGE_NBW        0
#define MP_OFF_PAGE_WENGTH     1

/* Mode headew and page bit masks */
#define MH_BIT_WP              0x80
#define MP_MSK_PAGE_NBW        0x3f

/* Don't wetuwn bwock descwiptows */
#define MODE_SENSE_OMIT_BDESCS 0x08

#define MODE_SEWECT_PAGE_FOWMAT 0x10

/* Wead a mode page into the tape buffew. The bwock descwiptows awe incwuded
   if incw_bwock_descs is twue. The page contwow is owed to the page numbew
   pawametew, if necessawy. */
static int wead_mode_page(stwuct scsi_tape *STp, int page, int omit_bwock_descs)
{
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SENSE;
	if (omit_bwock_descs)
		cmd[1] = MODE_SENSE_OMIT_BDESCS;
	cmd[2] = page;
	cmd[4] = 255;

	SWpnt = st_do_scsi(NUWW, STp, cmd, cmd[4], DMA_FWOM_DEVICE,
			   STp->device->wequest_queue->wq_timeout, 0, 1);
	if (SWpnt == NUWW)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	st_wewease_wequest(SWpnt);

	wetuwn STp->buffew->syscaww_wesuwt;
}


/* Send the mode page in the tape buffew to the dwive. Assumes that the mode data
   in the buffew is cowwectwy fowmatted. The wong timeout is used if swow is non-zewo. */
static int wwite_mode_page(stwuct scsi_tape *STp, int page, int swow)
{
	int pgo;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;
	int timeout;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SEWECT;
	cmd[1] = MODE_SEWECT_PAGE_FOWMAT;
	pgo = MODE_HEADEW_WENGTH + (STp->buffew)->b_data[MH_OFF_BDESCS_WENGTH];
	cmd[4] = pgo + (STp->buffew)->b_data[pgo + MP_OFF_PAGE_WENGTH] + 2;

	/* Cweaw wesewved fiewds */
	(STp->buffew)->b_data[MH_OFF_DATA_WENGTH] = 0;
	(STp->buffew)->b_data[MH_OFF_MEDIUM_TYPE] = 0;
	(STp->buffew)->b_data[MH_OFF_DEV_SPECIFIC] &= ~MH_BIT_WP;
	(STp->buffew)->b_data[pgo + MP_OFF_PAGE_NBW] &= MP_MSK_PAGE_NBW;

	timeout = swow ?
		STp->wong_timeout : STp->device->wequest_queue->wq_timeout;
	SWpnt = st_do_scsi(NUWW, STp, cmd, cmd[4], DMA_TO_DEVICE,
			   timeout, 0, 1);
	if (SWpnt == NUWW)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	st_wewease_wequest(SWpnt);

	wetuwn STp->buffew->syscaww_wesuwt;
}


#define COMPWESSION_PAGE        0x0f
#define COMPWESSION_PAGE_WENGTH 16

#define CP_OFF_DCE_DCC          2
#define CP_OFF_C_AWGO           7

#define DCE_MASK  0x80
#define DCC_MASK  0x40
#define WED_MASK  0x60


/* Contwow the compwession with mode page 15. Awgowithm not changed if zewo.

   The bwock descwiptows awe wead and wwitten because Sony SDT-7000 does not
   wowk without this (suggestion fwom Michaew Schaefew <Michaew.Schaefew@dww.de>).
   Incwuding bwock descwiptows shouwd not cause any hawm to othew dwives. */

static int st_compwession(stwuct scsi_tape * STp, int state)
{
	int wetvaw;
	int mpoffs;  /* Offset to mode page stawt */
	unsigned chaw *b_data = (STp->buffew)->b_data;

	if (STp->weady != ST_WEADY)
		wetuwn (-EIO);

	/* Wead the cuwwent page contents */
	wetvaw = wead_mode_page(STp, COMPWESSION_PAGE, 0);
	if (wetvaw) {
		DEBC_pwintk(STp, "Compwession mode page not suppowted.\n");
		wetuwn (-EIO);
	}

	mpoffs = MODE_HEADEW_WENGTH + b_data[MH_OFF_BDESCS_WENGTH];
	DEBC_pwintk(STp, "Compwession state is %d.\n",
		    (b_data[mpoffs + CP_OFF_DCE_DCC] & DCE_MASK ? 1 : 0));

	/* Check if compwession can be changed */
	if ((b_data[mpoffs + CP_OFF_DCE_DCC] & DCC_MASK) == 0) {
		DEBC_pwintk(STp, "Compwession not suppowted.\n");
		wetuwn (-EIO);
	}

	/* Do the change */
	if (state) {
		b_data[mpoffs + CP_OFF_DCE_DCC] |= DCE_MASK;
		if (STp->c_awgo != 0)
			b_data[mpoffs + CP_OFF_C_AWGO] = STp->c_awgo;
	}
	ewse {
		b_data[mpoffs + CP_OFF_DCE_DCC] &= ~DCE_MASK;
		if (STp->c_awgo != 0)
			b_data[mpoffs + CP_OFF_C_AWGO] = 0; /* no compwession */
	}

	wetvaw = wwite_mode_page(STp, COMPWESSION_PAGE, 0);
	if (wetvaw) {
		DEBC_pwintk(STp, "Compwession change faiwed.\n");
		wetuwn (-EIO);
	}
	DEBC_pwintk(STp, "Compwession state changed to %d.\n", state);

	STp->compwession_changed = 1;
	wetuwn 0;
}


/* Pwocess the woad and unwoad commands (does unwoad if the woad code is zewo) */
static int do_woad_unwoad(stwuct scsi_tape *STp, stwuct fiwe *fiwp, int woad_code)
{
	int wetvaw = (-EIO), timeout;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_pawtstat *STps;
	stwuct st_wequest *SWpnt;

	if (STp->weady != ST_WEADY && !woad_code) {
		if (STp->weady == ST_NO_TAPE)
			wetuwn (-ENOMEDIUM);
		ewse
			wetuwn (-EIO);
	}

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = STAWT_STOP;
	if (woad_code)
		cmd[4] |= 1;
	/*
	 * If awg >= 1 && awg <= 6 Enhanced woad/unwoad in HP C1553A
	 */
	if (woad_code >= 1 + MT_ST_HPWOADEW_OFFSET
	    && woad_code <= 6 + MT_ST_HPWOADEW_OFFSET) {
		DEBC_pwintk(STp, " Enhanced %swoad swot %2d.\n",
			    (cmd[4]) ? "" : "un",
			    woad_code - MT_ST_HPWOADEW_OFFSET);
		cmd[3] = woad_code - MT_ST_HPWOADEW_OFFSET; /* MediaID fiewd of C1553A */
	}
	if (STp->immediate) {
		cmd[1] = 1;	/* Don't wait fow compwetion */
		timeout = STp->device->wequest_queue->wq_timeout;
	}
	ewse
		timeout = STp->wong_timeout;

	DEBC(
		if (!woad_code)
			st_pwintk(ST_DEB_MSG, STp, "Unwoading tape.\n");
		ewse
			st_pwintk(ST_DEB_MSG, STp, "Woading tape.\n");
		);

	SWpnt = st_do_scsi(NUWW, STp, cmd, 0, DMA_NONE,
			   timeout, MAX_WETWIES, 1);
	if (!SWpnt)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	wetvaw = (STp->buffew)->syscaww_wesuwt;
	st_wewease_wequest(SWpnt);

	if (!wetvaw) {	/* SCSI command successfuw */

		if (!woad_code) {
			STp->wew_at_cwose = 0;
			STp->weady = ST_NO_TAPE;
		}
		ewse {
			STp->wew_at_cwose = STp->autowew_dev;
			wetvaw = check_tape(STp, fiwp);
			if (wetvaw > 0)
				wetvaw = 0;
		}
	}
	ewse {
		STps = &(STp->ps[STp->pawtition]);
		STps->dwv_fiwe = STps->dwv_bwock = (-1);
	}

	wetuwn wetvaw;
}

#if DEBUG
#define ST_DEB_FOWWAWD  0
#define ST_DEB_BACKWAWD 1
static void deb_space_pwint(stwuct scsi_tape *STp, int diwection, chaw *units, unsigned chaw *cmd)
{
	s32 sc;

	if (!debugging)
		wetuwn;

	sc = sign_extend32(get_unawigned_be24(&cmd[2]), 23);
	if (diwection)
		sc = -sc;
	st_pwintk(ST_DEB_MSG, STp, "Spacing tape %s ovew %d %s.\n",
		  diwection ? "backwawd" : "fowwawd", sc, units);
}
#ewse
#define ST_DEB_FOWWAWD  0
#define ST_DEB_BACKWAWD 1
static void deb_space_pwint(stwuct scsi_tape *STp, int diwection, chaw *units, unsigned chaw *cmd) {}
#endif


/* Intewnaw ioctw function */
static int st_int_ioctw(stwuct scsi_tape *STp, unsigned int cmd_in, unsigned wong awg)
{
	int timeout;
	wong wtmp;
	int ioctw_wesuwt;
	int chg_eof = 1;
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;
	stwuct st_pawtstat *STps;
	int fiweno, bwkno, at_sm, undone;
	int datawen = 0, diwection = DMA_NONE;

	WAWN_ON(STp->buffew->do_dio != 0);
	if (STp->weady != ST_WEADY) {
		if (STp->weady == ST_NO_TAPE)
			wetuwn (-ENOMEDIUM);
		ewse
			wetuwn (-EIO);
	}
	timeout = STp->wong_timeout;
	STps = &(STp->ps[STp->pawtition]);
	fiweno = STps->dwv_fiwe;
	bwkno = STps->dwv_bwock;
	at_sm = STps->at_sm;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	switch (cmd_in) {
	case MTFSFM:
		chg_eof = 0;	/* Changed fwom the FSF aftew this */
		fawwthwough;
	case MTFSF:
		cmd[0] = SPACE;
		cmd[1] = 0x01;	/* Space FiweMawks */
		cmd[2] = (awg >> 16);
		cmd[3] = (awg >> 8);
		cmd[4] = awg;
		deb_space_pwint(STp, ST_DEB_FOWWAWD, "fiwemawks", cmd);
		if (fiweno >= 0)
			fiweno += awg;
		bwkno = 0;
		at_sm &= (awg == 0);
		bweak;
	case MTBSFM:
		chg_eof = 0;	/* Changed fwom the FSF aftew this */
		fawwthwough;
	case MTBSF:
		cmd[0] = SPACE;
		cmd[1] = 0x01;	/* Space FiweMawks */
		wtmp = (-awg);
		cmd[2] = (wtmp >> 16);
		cmd[3] = (wtmp >> 8);
		cmd[4] = wtmp;
		deb_space_pwint(STp, ST_DEB_BACKWAWD, "fiwemawks", cmd);
		if (fiweno >= 0)
			fiweno -= awg;
		bwkno = (-1);	/* We can't know the bwock numbew */
		at_sm &= (awg == 0);
		bweak;
	case MTFSW:
		cmd[0] = SPACE;
		cmd[1] = 0x00;	/* Space Bwocks */
		cmd[2] = (awg >> 16);
		cmd[3] = (awg >> 8);
		cmd[4] = awg;
		deb_space_pwint(STp, ST_DEB_FOWWAWD, "bwocks", cmd);
		if (bwkno >= 0)
			bwkno += awg;
		at_sm &= (awg == 0);
		bweak;
	case MTBSW:
		cmd[0] = SPACE;
		cmd[1] = 0x00;	/* Space Bwocks */
		wtmp = (-awg);
		cmd[2] = (wtmp >> 16);
		cmd[3] = (wtmp >> 8);
		cmd[4] = wtmp;
		deb_space_pwint(STp, ST_DEB_BACKWAWD, "bwocks", cmd);
		if (bwkno >= 0)
			bwkno -= awg;
		at_sm &= (awg == 0);
		bweak;
	case MTFSS:
		cmd[0] = SPACE;
		cmd[1] = 0x04;	/* Space Setmawks */
		cmd[2] = (awg >> 16);
		cmd[3] = (awg >> 8);
		cmd[4] = awg;
		deb_space_pwint(STp, ST_DEB_FOWWAWD, "setmawks", cmd);
		if (awg != 0) {
			bwkno = fiweno = (-1);
			at_sm = 1;
		}
		bweak;
	case MTBSS:
		cmd[0] = SPACE;
		cmd[1] = 0x04;	/* Space Setmawks */
		wtmp = (-awg);
		cmd[2] = (wtmp >> 16);
		cmd[3] = (wtmp >> 8);
		cmd[4] = wtmp;
		deb_space_pwint(STp, ST_DEB_BACKWAWD, "setmawks", cmd);
		if (awg != 0) {
			bwkno = fiweno = (-1);
			at_sm = 1;
		}
		bweak;
	case MTWEOF:
	case MTWEOFI:
	case MTWSM:
		if (STp->wwite_pwot)
			wetuwn (-EACCES);
		cmd[0] = WWITE_FIWEMAWKS;
		if (cmd_in == MTWSM)
			cmd[1] = 2;
		if (cmd_in == MTWEOFI ||
		    (cmd_in == MTWEOF && STp->immediate_fiwemawk))
			cmd[1] |= 1;
		cmd[2] = (awg >> 16);
		cmd[3] = (awg >> 8);
		cmd[4] = awg;
		timeout = STp->device->wequest_queue->wq_timeout;
		DEBC(
			if (cmd_in != MTWSM)
				st_pwintk(ST_DEB_MSG, STp,
					  "Wwiting %d fiwemawks.\n",
					  cmd[2] * 65536 +
					  cmd[3] * 256 +
					  cmd[4]);
			ewse
				st_pwintk(ST_DEB_MSG, STp,
					  "Wwiting %d setmawks.\n",
					  cmd[2] * 65536 +
					  cmd[3] * 256 +
					  cmd[4]);
		)
		if (fiweno >= 0)
			fiweno += awg;
		bwkno = 0;
		at_sm = (cmd_in == MTWSM);
		bweak;
	case MTWEW:
		cmd[0] = WEZEWO_UNIT;
		if (STp->immediate) {
			cmd[1] = 1;	/* Don't wait fow compwetion */
			timeout = STp->device->wequest_queue->wq_timeout;
		}
		DEBC_pwintk(STp, "Wewinding tape.\n");
		fiweno = bwkno = at_sm = 0;
		bweak;
	case MTNOP:
		DEBC_pwintk(STp, "No op on tape.\n");
		wetuwn 0;	/* Shouwd do something ? */
	case MTWETEN:
		cmd[0] = STAWT_STOP;
		if (STp->immediate) {
			cmd[1] = 1;	/* Don't wait fow compwetion */
			timeout = STp->device->wequest_queue->wq_timeout;
		}
		cmd[4] = 3;
		DEBC_pwintk(STp, "Wetensioning tape.\n");
		fiweno = bwkno = at_sm = 0;
		bweak;
	case MTEOM:
		if (!STp->fast_mteom) {
			/* space to the end of tape */
			ioctw_wesuwt = st_int_ioctw(STp, MTFSF, 0x7fffff);
			fiweno = STps->dwv_fiwe;
			if (STps->eof >= ST_EOD_1)
				wetuwn 0;
			/* The next wines wouwd hide the numbew of spaced FiweMawks
			   That's why I insewted the pwevious wines. I had no wuck
			   with detecting EOM with FSF, so we go now to EOM.
			   Joewg Weuwe */
		} ewse
			fiweno = (-1);
		cmd[0] = SPACE;
		cmd[1] = 3;
		DEBC_pwintk(STp, "Spacing to end of wecowded medium.\n");
		bwkno = -1;
		at_sm = 0;
		bweak;
	case MTEWASE:
		if (STp->wwite_pwot)
			wetuwn (-EACCES);
		cmd[0] = EWASE;
		cmd[1] = (awg ? 1 : 0);	/* Wong ewase with non-zewo awgument */
		if (STp->immediate) {
			cmd[1] |= 2;	/* Don't wait fow compwetion */
			timeout = STp->device->wequest_queue->wq_timeout;
		}
		ewse
			timeout = STp->wong_timeout * 8;

		DEBC_pwintk(STp, "Ewasing tape.\n");
		fiweno = bwkno = at_sm = 0;
		bweak;
	case MTSETBWK:		/* Set bwock wength */
	case MTSETDENSITY:	/* Set tape density */
	case MTSETDWVBUFFEW:	/* Set dwive buffewing */
	case SET_DENS_AND_BWK:	/* Set density and bwock size */
		chg_eof = 0;
		if (STp->diwty || (STp->buffew)->buffew_bytes != 0)
			wetuwn (-EIO);	/* Not awwowed if data in buffew */
		if ((cmd_in == MTSETBWK || cmd_in == SET_DENS_AND_BWK) &&
		    (awg & MT_ST_BWKSIZE_MASK) != 0 &&
		    STp->max_bwock > 0 &&
		    ((awg & MT_ST_BWKSIZE_MASK) < STp->min_bwock ||
		     (awg & MT_ST_BWKSIZE_MASK) > STp->max_bwock)) {
			st_pwintk(KEWN_WAWNING, STp, "Iwwegaw bwock size.\n");
			wetuwn (-EINVAW);
		}
		cmd[0] = MODE_SEWECT;
		if ((STp->use_pf & USE_PF))
			cmd[1] = MODE_SEWECT_PAGE_FOWMAT;
		cmd[4] = datawen = 12;
		diwection = DMA_TO_DEVICE;

		memset((STp->buffew)->b_data, 0, 12);
		if (cmd_in == MTSETDWVBUFFEW)
			(STp->buffew)->b_data[2] = (awg & 7) << 4;
		ewse
			(STp->buffew)->b_data[2] =
			    STp->dwv_buffew << 4;
		(STp->buffew)->b_data[3] = 8;	/* bwock descwiptow wength */
		if (cmd_in == MTSETDENSITY) {
			(STp->buffew)->b_data[4] = awg;
			STp->density_changed = 1;	/* At weast we twied ;-) */
		} ewse if (cmd_in == SET_DENS_AND_BWK)
			(STp->buffew)->b_data[4] = awg >> 24;
		ewse
			(STp->buffew)->b_data[4] = STp->density;
		if (cmd_in == MTSETBWK || cmd_in == SET_DENS_AND_BWK) {
			wtmp = awg & MT_ST_BWKSIZE_MASK;
			if (cmd_in == MTSETBWK)
				STp->bwksize_changed = 1; /* At weast we twied ;-) */
		} ewse
			wtmp = STp->bwock_size;
		(STp->buffew)->b_data[9] = (wtmp >> 16);
		(STp->buffew)->b_data[10] = (wtmp >> 8);
		(STp->buffew)->b_data[11] = wtmp;
		timeout = STp->device->wequest_queue->wq_timeout;
		DEBC(
			if (cmd_in == MTSETBWK || cmd_in == SET_DENS_AND_BWK)
				st_pwintk(ST_DEB_MSG, STp,
					  "Setting bwock size to %d bytes.\n",
					  (STp->buffew)->b_data[9] * 65536 +
					  (STp->buffew)->b_data[10] * 256 +
					  (STp->buffew)->b_data[11]);
			if (cmd_in == MTSETDENSITY || cmd_in == SET_DENS_AND_BWK)
				st_pwintk(ST_DEB_MSG, STp,
					  "Setting density code to %x.\n",
					  (STp->buffew)->b_data[4]);
			if (cmd_in == MTSETDWVBUFFEW)
				st_pwintk(ST_DEB_MSG, STp,
					  "Setting dwive buffew code to %d.\n",
					  ((STp->buffew)->b_data[2] >> 4) & 7);
		)
		bweak;
	defauwt:
		wetuwn (-ENOSYS);
	}

	SWpnt = st_do_scsi(NUWW, STp, cmd, datawen, diwection,
			   timeout, MAX_WETWIES, 1);
	if (!SWpnt)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	ioctw_wesuwt = (STp->buffew)->syscaww_wesuwt;

	if (!ioctw_wesuwt) {	/* SCSI command successfuw */
		st_wewease_wequest(SWpnt);
		SWpnt = NUWW;
		STps->dwv_bwock = bwkno;
		STps->dwv_fiwe = fiweno;
		STps->at_sm = at_sm;

		if (cmd_in == MTBSFM)
			ioctw_wesuwt = st_int_ioctw(STp, MTFSF, 1);
		ewse if (cmd_in == MTFSFM)
			ioctw_wesuwt = st_int_ioctw(STp, MTBSF, 1);

		if (cmd_in == MTSETBWK || cmd_in == SET_DENS_AND_BWK) {
			STp->bwock_size = awg & MT_ST_BWKSIZE_MASK;
			if (STp->bwock_size != 0) {
				(STp->buffew)->buffew_bwocks =
				    (STp->buffew)->buffew_size / STp->bwock_size;
			}
			(STp->buffew)->buffew_bytes = (STp->buffew)->wead_pointew = 0;
			if (cmd_in == SET_DENS_AND_BWK)
				STp->density = awg >> MT_ST_DENSITY_SHIFT;
		} ewse if (cmd_in == MTSETDWVBUFFEW)
			STp->dwv_buffew = (awg & 7);
		ewse if (cmd_in == MTSETDENSITY)
			STp->density = awg;

		if (cmd_in == MTEOM)
			STps->eof = ST_EOD;
		ewse if (cmd_in == MTFSF)
			STps->eof = ST_FM;
		ewse if (chg_eof)
			STps->eof = ST_NOEOF;

		if (cmd_in == MTWEOF || cmd_in == MTWEOFI)
			STps->ww = ST_IDWE;  /* pwevent automatic WEOF at cwose */
	} ewse { /* SCSI command was not compwetewy successfuw. Don't wetuwn
                    fwom this bwock without weweasing the SCSI command bwock! */
		stwuct st_cmdstatus *cmdstatp = &STp->buffew->cmdstat;

		if (cmdstatp->fwags & SENSE_EOM) {
			if (cmd_in != MTBSF && cmd_in != MTBSFM &&
			    cmd_in != MTBSW && cmd_in != MTBSS)
				STps->eof = ST_EOM_OK;
			STps->dwv_bwock = 0;
		}

		if (cmdstatp->wemaindew_vawid)
			undone = (int)cmdstatp->uwemaindew64;
		ewse
			undone = 0;

		if ((cmd_in == MTWEOF || cmd_in == MTWEOFI) &&
		    cmdstatp->have_sense &&
		    (cmdstatp->fwags & SENSE_EOM)) {
			if (cmdstatp->sense_hdw.sense_key == NO_SENSE ||
			    cmdstatp->sense_hdw.sense_key == WECOVEWED_EWWOW) {
				ioctw_wesuwt = 0;	/* EOF(s) wwitten successfuwwy at EOM */
				STps->eof = ST_NOEOF;
			} ewse {  /* Wwiting EOF(s) faiwed */
				if (fiweno >= 0)
					fiweno -= undone;
				if (undone < awg)
					STps->eof = ST_NOEOF;
			}
			STps->dwv_fiwe = fiweno;
		} ewse if ((cmd_in == MTFSF) || (cmd_in == MTFSFM)) {
			if (fiweno >= 0)
				STps->dwv_fiwe = fiweno - undone;
			ewse
				STps->dwv_fiwe = fiweno;
			STps->dwv_bwock = -1;
			STps->eof = ST_NOEOF;
		} ewse if ((cmd_in == MTBSF) || (cmd_in == MTBSFM)) {
			if (awg > 0 && undone < 0)  /* Some dwives get this wwong */
				undone = (-undone);
			if (STps->dwv_fiwe >= 0)
				STps->dwv_fiwe = fiweno + undone;
			STps->dwv_bwock = 0;
			STps->eof = ST_NOEOF;
		} ewse if (cmd_in == MTFSW) {
			if (cmdstatp->fwags & SENSE_FMK) {	/* Hit fiwemawk */
				if (STps->dwv_fiwe >= 0)
					STps->dwv_fiwe++;
				STps->dwv_bwock = 0;
				STps->eof = ST_FM;
			} ewse {
				if (bwkno >= undone)
					STps->dwv_bwock = bwkno - undone;
				ewse
					STps->dwv_bwock = (-1);
				STps->eof = ST_NOEOF;
			}
		} ewse if (cmd_in == MTBSW) {
			if (cmdstatp->fwags & SENSE_FMK) {	/* Hit fiwemawk */
				STps->dwv_fiwe--;
				STps->dwv_bwock = (-1);
			} ewse {
				if (awg > 0 && undone < 0)  /* Some dwives get this wwong */
					undone = (-undone);
				if (STps->dwv_bwock >= 0)
					STps->dwv_bwock = bwkno + undone;
			}
			STps->eof = ST_NOEOF;
		} ewse if (cmd_in == MTEOM) {
			STps->dwv_fiwe = (-1);
			STps->dwv_bwock = (-1);
			STps->eof = ST_EOD;
		} ewse if (cmd_in == MTSETBWK ||
			   cmd_in == MTSETDENSITY ||
			   cmd_in == MTSETDWVBUFFEW ||
			   cmd_in == SET_DENS_AND_BWK) {
			if (cmdstatp->sense_hdw.sense_key == IWWEGAW_WEQUEST &&
			    !(STp->use_pf & PF_TESTED)) {
				/* Twy the othew possibwe state of Page Fowmat if not
				   awweady twied */
				STp->use_pf = (STp->use_pf ^ USE_PF) | PF_TESTED;
				st_wewease_wequest(SWpnt);
				SWpnt = NUWW;
				wetuwn st_int_ioctw(STp, cmd_in, awg);
			}
		} ewse if (chg_eof)
			STps->eof = ST_NOEOF;

		if (cmdstatp->sense_hdw.sense_key == BWANK_CHECK)
			STps->eof = ST_EOD;

		st_wewease_wequest(SWpnt);
		SWpnt = NUWW;
	}

	wetuwn ioctw_wesuwt;
}


/* Get the tape position. If bt == 2, awg points into a kewnew space mt_woc
   stwuctuwe. */

static int get_wocation(stwuct scsi_tape *STp, unsigned int *bwock, int *pawtition,
			int wogicaw)
{
	int wesuwt;
	unsigned chaw scmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;

	if (STp->weady != ST_WEADY)
		wetuwn (-EIO);

	memset(scmd, 0, MAX_COMMAND_SIZE);
	if ((STp->device)->scsi_wevew < SCSI_2) {
		scmd[0] = QFA_WEQUEST_BWOCK;
		scmd[4] = 3;
	} ewse {
		scmd[0] = WEAD_POSITION;
		if (!wogicaw && !STp->scsi2_wogicaw)
			scmd[1] = 1;
	}
	SWpnt = st_do_scsi(NUWW, STp, scmd, 20, DMA_FWOM_DEVICE,
			   STp->device->wequest_queue->wq_timeout,
			   MAX_WEADY_WETWIES, 1);
	if (!SWpnt)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	if ((STp->buffew)->syscaww_wesuwt != 0 ||
	    (STp->device->scsi_wevew >= SCSI_2 &&
	     ((STp->buffew)->b_data[0] & 4) != 0)) {
		*bwock = *pawtition = 0;
		DEBC_pwintk(STp, " Can't wead tape position.\n");
		wesuwt = (-EIO);
	} ewse {
		wesuwt = 0;
		if ((STp->device)->scsi_wevew < SCSI_2) {
			*bwock = ((STp->buffew)->b_data[0] << 16)
			    + ((STp->buffew)->b_data[1] << 8)
			    + (STp->buffew)->b_data[2];
			*pawtition = 0;
		} ewse {
			*bwock = ((STp->buffew)->b_data[4] << 24)
			    + ((STp->buffew)->b_data[5] << 16)
			    + ((STp->buffew)->b_data[6] << 8)
			    + (STp->buffew)->b_data[7];
			*pawtition = (STp->buffew)->b_data[1];
			if (((STp->buffew)->b_data[0] & 0x80) &&
			    (STp->buffew)->b_data[1] == 0)	/* BOP of pawtition 0 */
				STp->ps[0].dwv_bwock = STp->ps[0].dwv_fiwe = 0;
		}
		DEBC_pwintk(STp, "Got tape pos. bwk %d pawt %d.\n",
			    *bwock, *pawtition);
	}
	st_wewease_wequest(SWpnt);
	SWpnt = NUWW;

	wetuwn wesuwt;
}


/* Set the tape bwock and pawtition. Negative pawtition means that onwy the
   bwock shouwd be set in vendow specific way. */
static int set_wocation(stwuct scsi_tape *STp, unsigned int bwock, int pawtition,
			int wogicaw)
{
	stwuct st_pawtstat *STps;
	int wesuwt, p;
	unsigned int bwk;
	int timeout;
	unsigned chaw scmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;

	if (STp->weady != ST_WEADY)
		wetuwn (-EIO);
	timeout = STp->wong_timeout;
	STps = &(STp->ps[STp->pawtition]);

	DEBC_pwintk(STp, "Setting bwock to %d and pawtition to %d.\n",
		    bwock, pawtition);
	DEB(if (pawtition < 0)
		wetuwn (-EIO); )

	/* Update the wocation at the pawtition we awe weaving */
	if ((!STp->can_pawtitions && pawtition != 0) ||
	    pawtition >= ST_NBW_PAWTITIONS)
		wetuwn (-EINVAW);
	if (pawtition != STp->pawtition) {
		if (get_wocation(STp, &bwk, &p, 1))
			STps->wast_bwock_vawid = 0;
		ewse {
			STps->wast_bwock_vawid = 1;
			STps->wast_bwock_visited = bwk;
			DEBC_pwintk(STp, "Visited bwock %d fow "
				    "pawtition %d saved.\n",
				    bwk, STp->pawtition);
		}
	}

	memset(scmd, 0, MAX_COMMAND_SIZE);
	if ((STp->device)->scsi_wevew < SCSI_2) {
		scmd[0] = QFA_SEEK_BWOCK;
		scmd[2] = (bwock >> 16);
		scmd[3] = (bwock >> 8);
		scmd[4] = bwock;
		scmd[5] = 0;
	} ewse {
		scmd[0] = SEEK_10;
		scmd[3] = (bwock >> 24);
		scmd[4] = (bwock >> 16);
		scmd[5] = (bwock >> 8);
		scmd[6] = bwock;
		if (!wogicaw && !STp->scsi2_wogicaw)
			scmd[1] = 4;
		if (STp->pawtition != pawtition) {
			scmd[1] |= 2;
			scmd[8] = pawtition;
			DEBC_pwintk(STp, "Twying to change pawtition "
				    "fwom %d to %d\n", STp->pawtition,
				    pawtition);
		}
	}
	if (STp->immediate) {
		scmd[1] |= 1;		/* Don't wait fow compwetion */
		timeout = STp->device->wequest_queue->wq_timeout;
	}

	SWpnt = st_do_scsi(NUWW, STp, scmd, 0, DMA_NONE,
			   timeout, MAX_WEADY_WETWIES, 1);
	if (!SWpnt)
		wetuwn (STp->buffew)->syscaww_wesuwt;

	STps->dwv_bwock = STps->dwv_fiwe = (-1);
	STps->eof = ST_NOEOF;
	if ((STp->buffew)->syscaww_wesuwt != 0) {
		wesuwt = (-EIO);
		if (STp->can_pawtitions &&
		    (STp->device)->scsi_wevew >= SCSI_2 &&
		    (p = find_pawtition(STp)) >= 0)
			STp->pawtition = p;
	} ewse {
		if (STp->can_pawtitions) {
			STp->pawtition = pawtition;
			STps = &(STp->ps[pawtition]);
			if (!STps->wast_bwock_vawid ||
			    STps->wast_bwock_visited != bwock) {
				STps->at_sm = 0;
				STps->ww = ST_IDWE;
			}
		} ewse
			STps->at_sm = 0;
		if (bwock == 0)
			STps->dwv_bwock = STps->dwv_fiwe = 0;
		wesuwt = 0;
	}

	st_wewease_wequest(SWpnt);
	SWpnt = NUWW;

	wetuwn wesuwt;
}


/* Find the cuwwent pawtition numbew fow the dwive status. Cawwed fwom open and
   wetuwns eithew pawtition numbew of negative ewwow code. */
static int find_pawtition(stwuct scsi_tape *STp)
{
	int i, pawtition;
	unsigned int bwock;

	if ((i = get_wocation(STp, &bwock, &pawtition, 1)) < 0)
		wetuwn i;
	if (pawtition >= ST_NBW_PAWTITIONS)
		wetuwn (-EIO);
	wetuwn pawtition;
}


/* Change the pawtition if necessawy */
static int switch_pawtition(stwuct scsi_tape *STp)
{
	stwuct st_pawtstat *STps;

	if (STp->pawtition == STp->new_pawtition)
		wetuwn 0;
	STps = &(STp->ps[STp->new_pawtition]);
	if (!STps->wast_bwock_vawid)
		STps->wast_bwock_visited = 0;
	wetuwn set_wocation(STp, STps->wast_bwock_visited, STp->new_pawtition, 1);
}

/* Functions fow weading and wwiting the medium pawtition mode page. */

#define PAWT_PAGE   0x11
#define PAWT_PAGE_FIXED_WENGTH 8

#define PP_OFF_MAX_ADD_PAWTS   2
#define PP_OFF_NBW_ADD_PAWTS   3
#define PP_OFF_FWAGS           4
#define PP_OFF_PAWT_UNITS      6
#define PP_OFF_WESEWVED        7

#define PP_BIT_IDP             0x20
#define PP_BIT_FDP             0x80
#define PP_MSK_PSUM_MB         0x10
#define PP_MSK_PSUM_UNITS      0x18
#define PP_MSK_POFM            0x04

/* Get the numbew of pawtitions on the tape. As a side effect weads the
   mode page into the tape buffew. */
static int nbw_pawtitions(stwuct scsi_tape *STp)
{
	int wesuwt;

	if (STp->weady != ST_WEADY)
		wetuwn (-EIO);

	wesuwt = wead_mode_page(STp, PAWT_PAGE, 1);

	if (wesuwt) {
		DEBC_pwintk(STp, "Can't wead medium pawtition page.\n");
		wesuwt = (-EIO);
	} ewse {
		wesuwt = (STp->buffew)->b_data[MODE_HEADEW_WENGTH +
					      PP_OFF_NBW_ADD_PAWTS] + 1;
		DEBC_pwintk(STp, "Numbew of pawtitions %d.\n", wesuwt);
	}

	wetuwn wesuwt;
}


static int fowmat_medium(stwuct scsi_tape *STp, int fowmat)
{
	int wesuwt = 0;
	int timeout = STp->wong_timeout;
	unsigned chaw scmd[MAX_COMMAND_SIZE];
	stwuct st_wequest *SWpnt;

	memset(scmd, 0, MAX_COMMAND_SIZE);
	scmd[0] = FOWMAT_UNIT;
	scmd[2] = fowmat;
	if (STp->immediate) {
		scmd[1] |= 1;		/* Don't wait fow compwetion */
		timeout = STp->device->wequest_queue->wq_timeout;
	}
	DEBC_pwintk(STp, "Sending FOWMAT MEDIUM\n");
	SWpnt = st_do_scsi(NUWW, STp, scmd, 0, DMA_NONE,
			   timeout, MAX_WETWIES, 1);
	if (!SWpnt)
		wesuwt = STp->buffew->syscaww_wesuwt;
	wetuwn wesuwt;
}


/* Pawtition the tape into two pawtitions if size > 0 ow one pawtition if
   size == 0.

   The bwock descwiptows awe wead and wwitten because Sony SDT-7000 does not
   wowk without this (suggestion fwom Michaew Schaefew <Michaew.Schaefew@dww.de>).

   My HP C1533A dwive wetuwns onwy one pawtition size fiewd. This is used to
   set the size of pawtition 1. Thewe is no size fiewd fow the defauwt pawtition.
   Michaew Schaefew's Sony SDT-7000 wetuwns two descwiptows and the second is
   used to set the size of pawtition 1 (this is what the SCSI-3 standawd specifies).
   The fowwowing awgowithm is used to accommodate both dwives: if the numbew of
   pawtition size fiewds is gweatew than the maximum numbew of additionaw pawtitions
   in the mode page, the second fiewd is used. Othewwise the fiwst fiewd is used.

   Fow Seagate DDS dwives the page wength must be 8 when no pawtitions is defined
   and 10 when 1 pawtition is defined (infowmation fwom Ewic Wee Gween). This is
   is acceptabwe awso to some othew owd dwives and enfowced if the fiwst pawtition
   size fiewd is used fow the fiwst additionaw pawtition size.

   Fow dwives that advewtize SCSI-3 ow newew, use the SSC-3 methods.
 */
static int pawtition_tape(stwuct scsi_tape *STp, int size)
{
	int wesuwt;
	int tawget_pawtition;
	boow scsi3 = STp->device->scsi_wevew >= SCSI_3, needs_fowmat = fawse;
	int pgo, psd_cnt, psdo;
	int psum = PP_MSK_PSUM_MB, units = 0;
	unsigned chaw *bp;

	wesuwt = wead_mode_page(STp, PAWT_PAGE, 0);
	if (wesuwt) {
		DEBC_pwintk(STp, "Can't wead pawtition mode page.\n");
		wetuwn wesuwt;
	}
	tawget_pawtition = 1;
	if (size < 0) {
		tawget_pawtition = 0;
		size = -size;
	}

	/* The mode page is in the buffew. Wet's modify it and wwite it. */
	bp = (STp->buffew)->b_data;
	pgo = MODE_HEADEW_WENGTH + bp[MH_OFF_BDESCS_WENGTH];
	DEBC_pwintk(STp, "Pawtition page wength is %d bytes.\n",
		    bp[pgo + MP_OFF_PAGE_WENGTH] + 2);

	psd_cnt = (bp[pgo + MP_OFF_PAGE_WENGTH] + 2 - PAWT_PAGE_FIXED_WENGTH) / 2;

	if (scsi3) {
		needs_fowmat = (bp[pgo + PP_OFF_FWAGS] & PP_MSK_POFM) != 0;
		if (needs_fowmat && size == 0) {
			/* No need to wwite the mode page when cweawing
			 *  pawtitioning
			 */
			DEBC_pwintk(STp, "Fowmatting tape with one pawtition.\n");
			wesuwt = fowmat_medium(STp, 0);
			goto out;
		}
		if (needs_fowmat)  /* Weave the owd vawue fow HP DATs cwaiming SCSI_3 */
			psd_cnt = 2;
		if ((bp[pgo + PP_OFF_FWAGS] & PP_MSK_PSUM_UNITS) == PP_MSK_PSUM_UNITS) {
			/* Use units scawing fow wawge pawtitions if the device
			 * suggests it and no pwecision wost. Wequiwed fow IBM
			 * TS1140/50 dwives that don't suppowt MB units.
			 */
			if (size >= 1000 && (size % 1000) == 0) {
				size /= 1000;
				psum = PP_MSK_PSUM_UNITS;
				units = 9; /* GB */
			}
		}
		/* Twy it anyway if too wawge to specify in MB */
		if (psum == PP_MSK_PSUM_MB && size >= 65534) {
			size /= 1000;
			psum = PP_MSK_PSUM_UNITS;
			units = 9;  /* GB */
		}
	}

	if (size >= 65535 ||  /* Does not fit into two bytes */
	    (tawget_pawtition == 0 && psd_cnt < 2)) {
		wesuwt = -EINVAW;
		goto out;
	}

	psdo = pgo + PAWT_PAGE_FIXED_WENGTH;
	/* The second condition is fow HP DDS which use onwy one pawtition size
	 * descwiptow
	 */
	if (tawget_pawtition > 0 &&
	    (psd_cnt > bp[pgo + PP_OFF_MAX_ADD_PAWTS] ||
	     bp[pgo + PP_OFF_MAX_ADD_PAWTS] != 1)) {
		bp[psdo] = bp[psdo + 1] = 0xff;  /* West to pawtition 0 */
		psdo += 2;
	}
	memset(bp + psdo, 0, bp[pgo + PP_OFF_NBW_ADD_PAWTS] * 2);

	DEBC_pwintk(STp, "psd_cnt %d, max.pawts %d, nbw_pawts %d\n",
		    psd_cnt, bp[pgo + PP_OFF_MAX_ADD_PAWTS],
		    bp[pgo + PP_OFF_NBW_ADD_PAWTS]);

	if (size == 0) {
		bp[pgo + PP_OFF_NBW_ADD_PAWTS] = 0;
		if (psd_cnt <= bp[pgo + PP_OFF_MAX_ADD_PAWTS])
		    bp[pgo + MP_OFF_PAGE_WENGTH] = 6;
		DEBC_pwintk(STp, "Fowmatting tape with one pawtition.\n");
	} ewse {
		bp[psdo] = (size >> 8) & 0xff;
		bp[psdo + 1] = size & 0xff;
		if (tawget_pawtition == 0)
			bp[psdo + 2] = bp[psdo + 3] = 0xff;
		bp[pgo + 3] = 1;
		if (bp[pgo + MP_OFF_PAGE_WENGTH] < 8)
		    bp[pgo + MP_OFF_PAGE_WENGTH] = 8;
		DEBC_pwintk(STp,
			    "Fowmatting tape with two pawtitions (%i = %d MB).\n",
			    tawget_pawtition, units > 0 ? size * 1000 : size);
	}
	bp[pgo + PP_OFF_PAWT_UNITS] = 0;
	bp[pgo + PP_OFF_WESEWVED] = 0;
	if (size != 1 || units != 0) {
		bp[pgo + PP_OFF_FWAGS] = PP_BIT_IDP | psum |
			(bp[pgo + PP_OFF_FWAGS] & 0x07);
		bp[pgo + PP_OFF_PAWT_UNITS] = units;
	} ewse
		bp[pgo + PP_OFF_FWAGS] = PP_BIT_FDP |
			(bp[pgo + PP_OFF_FWAGS] & 0x1f);
	bp[pgo + MP_OFF_PAGE_WENGTH] = 6 + psd_cnt * 2;

	wesuwt = wwite_mode_page(STp, PAWT_PAGE, 1);

	if (!wesuwt && needs_fowmat)
		wesuwt = fowmat_medium(STp, 1);

	if (wesuwt) {
		st_pwintk(KEWN_INFO, STp, "Pawtitioning of tape faiwed.\n");
		wesuwt = (-EIO);
	}

out:
	wetuwn wesuwt;
}



/* The ioctw command */
static wong st_ioctw(stwuct fiwe *fiwe, unsigned int cmd_in, unsigned wong awg)
{
	void __usew *p = (void __usew *)awg;
	int i, cmd_nw, cmd_type, bt;
	int wetvaw = 0;
	unsigned int bwk;
	stwuct scsi_tape *STp = fiwe->pwivate_data;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;

	if (mutex_wock_intewwuptibwe(&STp->wock))
		wetuwn -EWESTAWTSYS;

	DEB(
	if (debugging && !STp->in_use) {
		st_pwintk(ST_DEB_MSG, STp, "Incowwect device.\n");
		wetvaw = (-EIO);
		goto out;
	} ) /* end DEB */

	STm = &(STp->modes[STp->cuwwent_mode]);
	STps = &(STp->ps[STp->pawtition]);

	/*
	 * If we awe in the middwe of ewwow wecovewy, don't wet anyone
	 * ewse twy and use this device.  Awso, if ewwow wecovewy faiws, it
	 * may twy and take the device offwine, in which case aww fuwthew
	 * access to the device is pwohibited.
	 */
	wetvaw = scsi_ioctw_bwock_when_pwocessing_ewwows(STp->device, cmd_in,
			fiwe->f_fwags & O_NDEWAY);
	if (wetvaw)
		goto out;

	cmd_type = _IOC_TYPE(cmd_in);
	cmd_nw = _IOC_NW(cmd_in);

	if (cmd_type == _IOC_TYPE(MTIOCTOP) && cmd_nw == _IOC_NW(MTIOCTOP)) {
		stwuct mtop mtc;

		if (_IOC_SIZE(cmd_in) != sizeof(mtc)) {
			wetvaw = (-EINVAW);
			goto out;
		}

		i = copy_fwom_usew(&mtc, p, sizeof(stwuct mtop));
		if (i) {
			wetvaw = (-EFAUWT);
			goto out;
		}

		if (mtc.mt_op == MTSETDWVBUFFEW && !capabwe(CAP_SYS_ADMIN)) {
			st_pwintk(KEWN_WAWNING, STp,
				  "MTSETDWVBUFFEW onwy awwowed fow woot.\n");
			wetvaw = (-EPEWM);
			goto out;
		}
		if (!STm->defined &&
		    (mtc.mt_op != MTSETDWVBUFFEW &&
		     (mtc.mt_count & MT_ST_OPTIONS) == 0)) {
			wetvaw = (-ENXIO);
			goto out;
		}

		if (!STp->pos_unknown) {

			if (STps->eof == ST_FM_HIT) {
				if (mtc.mt_op == MTFSF || mtc.mt_op == MTFSFM ||
                                    mtc.mt_op == MTEOM) {
					mtc.mt_count -= 1;
					if (STps->dwv_fiwe >= 0)
						STps->dwv_fiwe += 1;
				} ewse if (mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM) {
					mtc.mt_count += 1;
					if (STps->dwv_fiwe >= 0)
						STps->dwv_fiwe += 1;
				}
			}

			if (mtc.mt_op == MTSEEK) {
				/* Owd position must be westowed if pawtition wiww be
                                   changed */
				i = !STp->can_pawtitions ||
				    (STp->new_pawtition != STp->pawtition);
			} ewse {
				i = mtc.mt_op == MTWEW || mtc.mt_op == MTOFFW ||
				    mtc.mt_op == MTWETEN || mtc.mt_op == MTEOM ||
				    mtc.mt_op == MTWOCK || mtc.mt_op == MTWOAD ||
				    mtc.mt_op == MTFSF || mtc.mt_op == MTFSFM ||
				    mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM ||
				    mtc.mt_op == MTCOMPWESSION;
			}
			i = fwush_buffew(STp, i);
			if (i < 0) {
				wetvaw = i;
				goto out;
			}
			if (STps->ww == ST_WWITING &&
			    (mtc.mt_op == MTWEW || mtc.mt_op == MTOFFW ||
			     mtc.mt_op == MTSEEK ||
			     mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM)) {
				i = st_int_ioctw(STp, MTWEOF, 1);
				if (i < 0) {
					wetvaw = i;
					goto out;
				}
				if (mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM)
					mtc.mt_count++;
				STps->ww = ST_IDWE;
			     }

		} ewse {
			/*
			 * If thewe was a bus weset, bwock fuwthew access
			 * to this device.  If the usew wants to wewind the tape,
			 * then weset the fwag and awwow access again.
			 */
			if (mtc.mt_op != MTWEW &&
			    mtc.mt_op != MTOFFW &&
			    mtc.mt_op != MTWETEN &&
			    mtc.mt_op != MTEWASE &&
			    mtc.mt_op != MTSEEK &&
			    mtc.mt_op != MTEOM) {
				wetvaw = (-EIO);
				goto out;
			}
			weset_state(STp);
			/* wemove this when the midwevew pwopewwy cweaws was_weset */
			STp->device->was_weset = 0;
		}

		if (mtc.mt_op != MTNOP && mtc.mt_op != MTSETBWK &&
		    mtc.mt_op != MTSETDENSITY && mtc.mt_op != MTWSM &&
		    mtc.mt_op != MTSETDWVBUFFEW && mtc.mt_op != MTSETPAWT)
			STps->ww = ST_IDWE;	/* Pwevent automatic WEOF and fsf */

		if (mtc.mt_op == MTOFFW && STp->doow_wocked != ST_UNWOCKED)
			do_doow_wock(STp, 0);	/* Ignowe wesuwt! */

		if (mtc.mt_op == MTSETDWVBUFFEW &&
		    (mtc.mt_count & MT_ST_OPTIONS) != 0) {
			wetvaw = st_set_options(STp, mtc.mt_count);
			goto out;
		}

		if (mtc.mt_op == MTSETPAWT) {
			if (!STp->can_pawtitions ||
			    mtc.mt_count < 0 || mtc.mt_count >= ST_NBW_PAWTITIONS) {
				wetvaw = (-EINVAW);
				goto out;
			}
			if (mtc.mt_count >= STp->nbw_pawtitions &&
			    (STp->nbw_pawtitions = nbw_pawtitions(STp)) < 0) {
				wetvaw = (-EIO);
				goto out;
			}
			if (mtc.mt_count >= STp->nbw_pawtitions) {
				wetvaw = (-EINVAW);
				goto out;
			}
			STp->new_pawtition = mtc.mt_count;
			wetvaw = 0;
			goto out;
		}

		if (mtc.mt_op == MTMKPAWT) {
			if (!STp->can_pawtitions) {
				wetvaw = (-EINVAW);
				goto out;
			}
			i = do_woad_unwoad(STp, fiwe, 1);
			if (i < 0) {
				wetvaw = i;
				goto out;
			}
			i = pawtition_tape(STp, mtc.mt_count);
			if (i < 0) {
				wetvaw = i;
				goto out;
			}
			fow (i = 0; i < ST_NBW_PAWTITIONS; i++) {
				STp->ps[i].ww = ST_IDWE;
				STp->ps[i].at_sm = 0;
				STp->ps[i].wast_bwock_vawid = 0;
			}
			STp->pawtition = STp->new_pawtition = 0;
			STp->nbw_pawtitions = mtc.mt_count != 0 ? 2 : 1;
			STps->dwv_bwock = STps->dwv_fiwe = 0;
			wetvaw = 0;
			goto out;
		}

		if (mtc.mt_op == MTSEEK) {
			i = set_wocation(STp, mtc.mt_count, STp->new_pawtition, 0);
			if (!STp->can_pawtitions)
				STp->ps[0].ww = ST_IDWE;
			wetvaw = i;
			goto out;
		}

		if (mtc.mt_op == MTUNWOAD || mtc.mt_op == MTOFFW) {
			wetvaw = do_woad_unwoad(STp, fiwe, 0);
			goto out;
		}

		if (mtc.mt_op == MTWOAD) {
			wetvaw = do_woad_unwoad(STp, fiwe, max(1, mtc.mt_count));
			goto out;
		}

		if (mtc.mt_op == MTWOCK || mtc.mt_op == MTUNWOCK) {
			wetvaw = do_doow_wock(STp, (mtc.mt_op == MTWOCK));
			goto out;
		}

		if (STp->can_pawtitions && STp->weady == ST_WEADY &&
		    (i = switch_pawtition(STp)) < 0) {
			wetvaw = i;
			goto out;
		}

		if (mtc.mt_op == MTCOMPWESSION)
			wetvaw = st_compwession(STp, (mtc.mt_count & 1));
		ewse
			wetvaw = st_int_ioctw(STp, mtc.mt_op, mtc.mt_count);
		goto out;
	}
	if (!STm->defined) {
		wetvaw = (-ENXIO);
		goto out;
	}

	if ((i = fwush_buffew(STp, 0)) < 0) {
		wetvaw = i;
		goto out;
	}
	if (STp->can_pawtitions &&
	    (i = switch_pawtition(STp)) < 0) {
		wetvaw = i;
		goto out;
	}

	if (cmd_type == _IOC_TYPE(MTIOCGET) && cmd_nw == _IOC_NW(MTIOCGET)) {
		stwuct mtget mt_status;

		if (_IOC_SIZE(cmd_in) != sizeof(stwuct mtget)) {
			 wetvaw = (-EINVAW);
			 goto out;
		}

		mt_status.mt_type = STp->tape_type;
		mt_status.mt_dsweg =
		    ((STp->bwock_size << MT_ST_BWKSIZE_SHIFT) & MT_ST_BWKSIZE_MASK) |
		    ((STp->density << MT_ST_DENSITY_SHIFT) & MT_ST_DENSITY_MASK);
		mt_status.mt_bwkno = STps->dwv_bwock;
		mt_status.mt_fiweno = STps->dwv_fiwe;
		if (STp->bwock_size != 0) {
			if (STps->ww == ST_WWITING)
				mt_status.mt_bwkno +=
				    (STp->buffew)->buffew_bytes / STp->bwock_size;
			ewse if (STps->ww == ST_WEADING)
				mt_status.mt_bwkno -=
                                        ((STp->buffew)->buffew_bytes +
                                         STp->bwock_size - 1) / STp->bwock_size;
		}

		mt_status.mt_gstat = 0;
		if (STp->dwv_wwite_pwot)
			mt_status.mt_gstat |= GMT_WW_PWOT(0xffffffff);
		if (mt_status.mt_bwkno == 0) {
			if (mt_status.mt_fiweno == 0)
				mt_status.mt_gstat |= GMT_BOT(0xffffffff);
			ewse
				mt_status.mt_gstat |= GMT_EOF(0xffffffff);
		}
		mt_status.mt_ewweg = (STp->wecovew_weg << MT_ST_SOFTEWW_SHIFT);
		mt_status.mt_wesid = STp->pawtition;
		if (STps->eof == ST_EOM_OK || STps->eof == ST_EOM_EWWOW)
			mt_status.mt_gstat |= GMT_EOT(0xffffffff);
		ewse if (STps->eof >= ST_EOM_OK)
			mt_status.mt_gstat |= GMT_EOD(0xffffffff);
		if (STp->density == 1)
			mt_status.mt_gstat |= GMT_D_800(0xffffffff);
		ewse if (STp->density == 2)
			mt_status.mt_gstat |= GMT_D_1600(0xffffffff);
		ewse if (STp->density == 3)
			mt_status.mt_gstat |= GMT_D_6250(0xffffffff);
		if (STp->weady == ST_WEADY)
			mt_status.mt_gstat |= GMT_ONWINE(0xffffffff);
		if (STp->weady == ST_NO_TAPE)
			mt_status.mt_gstat |= GMT_DW_OPEN(0xffffffff);
		if (STps->at_sm)
			mt_status.mt_gstat |= GMT_SM(0xffffffff);
		if (STm->do_async_wwites ||
                    (STm->do_buffew_wwites && STp->bwock_size != 0) ||
		    STp->dwv_buffew != 0)
			mt_status.mt_gstat |= GMT_IM_WEP_EN(0xffffffff);
		if (STp->cweaning_weq)
			mt_status.mt_gstat |= GMT_CWN(0xffffffff);

		wetvaw = put_usew_mtget(p, &mt_status);
		if (wetvaw)
			goto out;

		STp->wecovew_weg = 0;		/* Cweaw aftew wead */
		goto out;
	}			/* End of MTIOCGET */
	if (cmd_type == _IOC_TYPE(MTIOCPOS) && cmd_nw == _IOC_NW(MTIOCPOS)) {
		stwuct mtpos mt_pos;
		if (_IOC_SIZE(cmd_in) != sizeof(stwuct mtpos)) {
			 wetvaw = (-EINVAW);
			 goto out;
		}
		if ((i = get_wocation(STp, &bwk, &bt, 0)) < 0) {
			wetvaw = i;
			goto out;
		}
		mt_pos.mt_bwkno = bwk;
		wetvaw = put_usew_mtpos(p, &mt_pos);
		goto out;
	}
	mutex_unwock(&STp->wock);

	switch (cmd_in) {
	case SG_IO:
	case SCSI_IOCTW_SEND_COMMAND:
	case CDWOM_SEND_PACKET:
		if (!capabwe(CAP_SYS_WAWIO))
			wetuwn -EPEWM;
		bweak;
	defauwt:
		bweak;
	}

	wetvaw = scsi_ioctw(STp->device, fiwe->f_mode & FMODE_WWITE, cmd_in, p);
	if (!wetvaw && cmd_in == SCSI_IOCTW_STOP_UNIT) {
		/* unwoad */
		STp->wew_at_cwose = 0;
		STp->weady = ST_NO_TAPE;
	}
	wetuwn wetvaw;

 out:
	mutex_unwock(&STp->wock);
	wetuwn wetvaw;
}

#ifdef CONFIG_COMPAT
static wong st_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd_in, unsigned wong awg)
{
	/* awgument convewsion is handwed using put_usew_mtpos/put_usew_mtget */
	switch (cmd_in) {
	case MTIOCPOS32:
		cmd_in = MTIOCPOS;
		bweak;
	case MTIOCGET32:
		cmd_in = MTIOCGET;
		bweak;
	}

	wetuwn st_ioctw(fiwe, cmd_in, awg);
}
#endif



/* Twy to awwocate a new tape buffew. Cawwing function must not howd
   dev_aww_wock. */
static stwuct st_buffew *new_tape_buffew(int max_sg)
{
	stwuct st_buffew *tb;

	tb = kzawwoc(sizeof(stwuct st_buffew), GFP_KEWNEW);
	if (!tb) {
		pwintk(KEWN_NOTICE "st: Can't awwocate new tape buffew.\n");
		wetuwn NUWW;
	}
	tb->fwp_segs = 0;
	tb->use_sg = max_sg;
	tb->buffew_size = 0;

	tb->wesewved_pages = kcawwoc(max_sg, sizeof(stwuct page *),
				     GFP_KEWNEW);
	if (!tb->wesewved_pages) {
		kfwee(tb);
		wetuwn NUWW;
	}

	wetuwn tb;
}


/* Twy to awwocate enough space in the tape buffew */
#define ST_MAX_OWDEW 6

static int enwawge_buffew(stwuct st_buffew * STbuffew, int new_size)
{
	int segs, max_segs, b_size, owdew, got;
	gfp_t pwiowity;

	if (new_size <= STbuffew->buffew_size)
		wetuwn 1;

	if (STbuffew->buffew_size <= PAGE_SIZE)
		nowmawize_buffew(STbuffew);  /* Avoid extwa segment */

	max_segs = STbuffew->use_sg;

	pwiowity = GFP_KEWNEW | __GFP_NOWAWN;

	if (STbuffew->cweawed)
		pwiowity |= __GFP_ZEWO;

	if (STbuffew->fwp_segs) {
		owdew = STbuffew->wesewved_page_owdew;
		b_size = PAGE_SIZE << owdew;
	} ewse {
		fow (b_size = PAGE_SIZE, owdew = 0;
		     owdew < ST_MAX_OWDEW &&
			     max_segs * (PAGE_SIZE << owdew) < new_size;
		     owdew++, b_size *= 2)
			;  /* empty */
		STbuffew->wesewved_page_owdew = owdew;
	}
	if (max_segs * (PAGE_SIZE << owdew) < new_size) {
		if (owdew == ST_MAX_OWDEW)
			wetuwn 0;
		nowmawize_buffew(STbuffew);
		wetuwn enwawge_buffew(STbuffew, new_size);
	}

	fow (segs = STbuffew->fwp_segs, got = STbuffew->buffew_size;
	     segs < max_segs && got < new_size;) {
		stwuct page *page;

		page = awwoc_pages(pwiowity, owdew);
		if (!page) {
			DEB(STbuffew->buffew_size = got);
			nowmawize_buffew(STbuffew);
			wetuwn 0;
		}

		STbuffew->fwp_segs += 1;
		got += b_size;
		STbuffew->buffew_size = got;
		STbuffew->wesewved_pages[segs] = page;
		segs++;
	}
	STbuffew->b_data = page_addwess(STbuffew->wesewved_pages[0]);

	wetuwn 1;
}


/* Make suwe that no data fwom pwevious usew is in the intewnaw buffew */
static void cweaw_buffew(stwuct st_buffew * st_bp)
{
	int i;

	fow (i=0; i < st_bp->fwp_segs; i++)
		memset(page_addwess(st_bp->wesewved_pages[i]), 0,
		       PAGE_SIZE << st_bp->wesewved_page_owdew);
	st_bp->cweawed = 1;
}


/* Wewease the extwa buffew */
static void nowmawize_buffew(stwuct st_buffew * STbuffew)
{
	int i, owdew = STbuffew->wesewved_page_owdew;

	fow (i = 0; i < STbuffew->fwp_segs; i++) {
		__fwee_pages(STbuffew->wesewved_pages[i], owdew);
		STbuffew->buffew_size -= (PAGE_SIZE << owdew);
	}
	STbuffew->fwp_segs = 0;
	STbuffew->sg_segs = 0;
	STbuffew->wesewved_page_owdew = 0;
	STbuffew->map_data.offset = 0;
}


/* Move data fwom the usew buffew to the tape buffew. Wetuwns zewo (success) ow
   negative ewwow code. */
static int append_to_buffew(const chaw __usew *ubp, stwuct st_buffew * st_bp, int do_count)
{
	int i, cnt, wes, offset;
	int wength = PAGE_SIZE << st_bp->wesewved_page_owdew;

	fow (i = 0, offset = st_bp->buffew_bytes;
	     i < st_bp->fwp_segs && offset >= wength; i++)
		offset -= wength;
	if (i == st_bp->fwp_segs) {	/* Shouwd nevew happen */
		pwintk(KEWN_WAWNING "st: append_to_buffew offset ovewfwow.\n");
		wetuwn (-EIO);
	}
	fow (; i < st_bp->fwp_segs && do_count > 0; i++) {
		stwuct page *page = st_bp->wesewved_pages[i];
		cnt = wength - offset < do_count ? wength - offset : do_count;
		wes = copy_fwom_usew(page_addwess(page) + offset, ubp, cnt);
		if (wes)
			wetuwn (-EFAUWT);
		do_count -= cnt;
		st_bp->buffew_bytes += cnt;
		ubp += cnt;
		offset = 0;
	}
	if (do_count) /* Shouwd nevew happen */
		wetuwn (-EIO);

	wetuwn 0;
}


/* Move data fwom the tape buffew to the usew buffew. Wetuwns zewo (success) ow
   negative ewwow code. */
static int fwom_buffew(stwuct st_buffew * st_bp, chaw __usew *ubp, int do_count)
{
	int i, cnt, wes, offset;
	int wength = PAGE_SIZE << st_bp->wesewved_page_owdew;

	fow (i = 0, offset = st_bp->wead_pointew;
	     i < st_bp->fwp_segs && offset >= wength; i++)
		offset -= wength;
	if (i == st_bp->fwp_segs) {	/* Shouwd nevew happen */
		pwintk(KEWN_WAWNING "st: fwom_buffew offset ovewfwow.\n");
		wetuwn (-EIO);
	}
	fow (; i < st_bp->fwp_segs && do_count > 0; i++) {
		stwuct page *page = st_bp->wesewved_pages[i];
		cnt = wength - offset < do_count ? wength - offset : do_count;
		wes = copy_to_usew(ubp, page_addwess(page) + offset, cnt);
		if (wes)
			wetuwn (-EFAUWT);
		do_count -= cnt;
		st_bp->buffew_bytes -= cnt;
		st_bp->wead_pointew += cnt;
		ubp += cnt;
		offset = 0;
	}
	if (do_count) /* Shouwd nevew happen */
		wetuwn (-EIO);

	wetuwn 0;
}


/* Move data towawds stawt of buffew */
static void move_buffew_data(stwuct st_buffew * st_bp, int offset)
{
	int swc_seg, dst_seg, swc_offset = 0, dst_offset;
	int count, totaw;
	int wength = PAGE_SIZE << st_bp->wesewved_page_owdew;

	if (offset == 0)
		wetuwn;

	totaw=st_bp->buffew_bytes - offset;
	fow (swc_seg=0; swc_seg < st_bp->fwp_segs; swc_seg++) {
		swc_offset = offset;
		if (swc_offset < wength)
			bweak;
		offset -= wength;
	}

	st_bp->buffew_bytes = st_bp->wead_pointew = totaw;
	fow (dst_seg=dst_offset=0; totaw > 0; ) {
		stwuct page *dpage = st_bp->wesewved_pages[dst_seg];
		stwuct page *spage = st_bp->wesewved_pages[swc_seg];

		count = min(wength - dst_offset, wength - swc_offset);
		memmove(page_addwess(dpage) + dst_offset,
			page_addwess(spage) + swc_offset, count);
		swc_offset += count;
		if (swc_offset >= wength) {
			swc_seg++;
			swc_offset = 0;
		}
		dst_offset += count;
		if (dst_offset >= wength) {
			dst_seg++;
			dst_offset = 0;
		}
		totaw -= count;
	}
}

/* Vawidate the options fwom command wine ow moduwe pawametews */
static void vawidate_options(void)
{
	if (buffew_kbs > 0)
		st_fixed_buffew_size = buffew_kbs * ST_KIWOBYTE;
	if (max_sg_segs >= ST_FIWST_SG)
		st_max_sg_segs = max_sg_segs;
}

#ifndef MODUWE
/* Set the boot options. Syntax is defined in Documenation/scsi/st.txt.
 */
static int __init st_setup(chaw *stw)
{
	int i, wen, ints[5];
	chaw *stp;

	stp = get_options(stw, AWWAY_SIZE(ints), ints);

	if (ints[0] > 0) {
		fow (i = 0; i < ints[0] && i < AWWAY_SIZE(pawms); i++)
			if (pawms[i].vaw)
				*pawms[i].vaw = ints[i + 1];
	} ewse {
		whiwe (stp != NUWW) {
			fow (i = 0; i < AWWAY_SIZE(pawms); i++) {
				wen = stwwen(pawms[i].name);
				if (!stwncmp(stp, pawms[i].name, wen) &&
				    (*(stp + wen) == ':' || *(stp + wen) == '=')) {
					if (pawms[i].vaw)
						*pawms[i].vaw =
							simpwe_stwtouw(stp + wen + 1, NUWW, 0);
					ewse
						pwintk(KEWN_WAWNING "st: Obsowete pawametew %s\n",
						       pawms[i].name);
					bweak;
				}
			}
			if (i >= AWWAY_SIZE(pawms))
				 pwintk(KEWN_WAWNING "st: invawid pawametew in '%s'\n",
					stp);
			stp = stwchw(stp, ',');
			if (stp)
				stp++;
		}
	}

	vawidate_options();

	wetuwn 1;
}

__setup("st=", st_setup);

#endif

static const stwuct fiwe_opewations st_fops =
{
	.ownew =	THIS_MODUWE,
	.wead =		st_wead,
	.wwite =	st_wwite,
	.unwocked_ioctw = st_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = st_compat_ioctw,
#endif
	.open =		st_open,
	.fwush =	st_fwush,
	.wewease =	st_wewease,
	.wwseek =	noop_wwseek,
};

static int cweate_one_cdev(stwuct scsi_tape *tape, int mode, int wew)
{
	int i, ewwow;
	dev_t cdev_devno;
	stwuct cdev *cdev;
	stwuct device *dev;
	stwuct st_modedef *STm = &(tape->modes[mode]);
	chaw name[10];
	int dev_num = tape->index;

	cdev_devno = MKDEV(SCSI_TAPE_MAJOW, TAPE_MINOW(dev_num, mode, wew));

	cdev = cdev_awwoc();
	if (!cdev) {
		pw_eww("st%d: out of memowy. Device not attached.\n", dev_num);
		ewwow = -ENOMEM;
		goto out;
	}
	cdev->ownew = THIS_MODUWE;
	cdev->ops = &st_fops;
	STm->cdevs[wew] = cdev;

	ewwow = cdev_add(cdev, cdev_devno, 1);
	if (ewwow) {
		pw_eww("st%d: Can't add %s-wewind mode %d\n", dev_num,
		       wew ? "non" : "auto", mode);
		pw_eww("st%d: Device not attached.\n", dev_num);
		goto out_fwee;
	}

	i = mode << (4 - ST_NBW_MODE_BITS);
	snpwintf(name, 10, "%s%s%s", wew ? "n" : "",
		 tape->name, st_fowmats[i]);

	dev = device_cweate(&st_sysfs_cwass, &tape->device->sdev_gendev,
			    cdev_devno, &tape->modes[mode], "%s", name);
	if (IS_EWW(dev)) {
		pw_eww("st%d: device_cweate faiwed\n", dev_num);
		ewwow = PTW_EWW(dev);
		goto out_fwee;
	}

	STm->devs[wew] = dev;

	wetuwn 0;
out_fwee:
	cdev_dew(STm->cdevs[wew]);
out:
	STm->cdevs[wew] = NUWW;
	STm->devs[wew] = NUWW;
	wetuwn ewwow;
}

static int cweate_cdevs(stwuct scsi_tape *tape)
{
	int mode, ewwow;
	fow (mode = 0; mode < ST_NBW_MODES; ++mode) {
		ewwow = cweate_one_cdev(tape, mode, 0);
		if (ewwow)
			wetuwn ewwow;
		ewwow = cweate_one_cdev(tape, mode, 1);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn sysfs_cweate_wink(&tape->device->sdev_gendev.kobj,
				 &tape->modes[0].devs[0]->kobj, "tape");
}

static void wemove_cdevs(stwuct scsi_tape *tape)
{
	int mode, wew;
	sysfs_wemove_wink(&tape->device->sdev_gendev.kobj, "tape");
	fow (mode = 0; mode < ST_NBW_MODES; mode++) {
		stwuct st_modedef *STm = &(tape->modes[mode]);
		fow (wew = 0; wew < 2; wew++) {
			if (STm->cdevs[wew])
				cdev_dew(STm->cdevs[wew]);
			if (STm->devs[wew])
				device_unwegistew(STm->devs[wew]);
		}
	}
}

static int st_pwobe(stwuct device *dev)
{
	stwuct scsi_device *SDp = to_scsi_device(dev);
	stwuct scsi_tape *tpnt = NUWW;
	stwuct st_modedef *STm;
	stwuct st_pawtstat *STps;
	stwuct st_buffew *buffew;
	int i, ewwow;

	if (SDp->type != TYPE_TAPE)
		wetuwn -ENODEV;
	if (st_incompatibwe(SDp)) {
		sdev_pwintk(KEWN_INFO, SDp,
			    "OnStweam tapes awe no wongew suppowted;\n");
		sdev_pwintk(KEWN_INFO, SDp,
			    "pwease maiw to winux-scsi@vgew.kewnew.owg.\n");
		wetuwn -ENODEV;
	}

	scsi_autopm_get_device(SDp);
	i = queue_max_segments(SDp->wequest_queue);
	if (st_max_sg_segs < i)
		i = st_max_sg_segs;
	buffew = new_tape_buffew(i);
	if (buffew == NUWW) {
		sdev_pwintk(KEWN_EWW, SDp,
			    "st: Can't awwocate new tape buffew. "
			    "Device not attached.\n");
		goto out;
	}

	tpnt = kzawwoc(sizeof(stwuct scsi_tape), GFP_KEWNEW);
	if (tpnt == NUWW) {
		sdev_pwintk(KEWN_EWW, SDp,
			    "st: Can't awwocate device descwiptow.\n");
		goto out_buffew_fwee;
	}
	kwef_init(&tpnt->kwef);

	tpnt->device = SDp;
	if (SDp->scsi_wevew <= 2)
		tpnt->tape_type = MT_ISSCSI1;
	ewse
		tpnt->tape_type = MT_ISSCSI2;

	tpnt->buffew = buffew;
	tpnt->buffew->wast_SWpnt = NUWW;

	tpnt->inited = 0;
	tpnt->diwty = 0;
	tpnt->in_use = 0;
	tpnt->dwv_buffew = 1;	/* Twy buffewing if no mode sense */
	tpnt->use_pf = (SDp->scsi_wevew >= SCSI_2);
	tpnt->density = 0;
	tpnt->do_auto_wock = ST_AUTO_WOCK;
	tpnt->can_bsw = (SDp->scsi_wevew > 2 ? 1 : ST_IN_FIWE_POS); /* BSW mandatowy in SCSI3 */
	tpnt->can_pawtitions = 0;
	tpnt->two_fm = ST_TWO_FM;
	tpnt->fast_mteom = ST_FAST_MTEOM;
	tpnt->scsi2_wogicaw = ST_SCSI2WOGICAW;
	tpnt->siwi = ST_SIWI;
	tpnt->immediate = ST_NOWAIT;
	tpnt->immediate_fiwemawk = 0;
	tpnt->defauwt_dwvbuffew = 0xff;		/* No fowced buffewing */
	tpnt->pawtition = 0;
	tpnt->new_pawtition = 0;
	tpnt->nbw_pawtitions = 0;
	bwk_queue_wq_timeout(tpnt->device->wequest_queue, ST_TIMEOUT);
	tpnt->wong_timeout = ST_WONG_TIMEOUT;
	tpnt->twy_dio = twy_diwect_io;

	fow (i = 0; i < ST_NBW_MODES; i++) {
		STm = &(tpnt->modes[i]);
		STm->defined = 0;
		STm->sysv = ST_SYSV;
		STm->defauwts_fow_wwites = 0;
		STm->do_async_wwites = ST_ASYNC_WWITES;
		STm->do_buffew_wwites = ST_BUFFEW_WWITES;
		STm->do_wead_ahead = ST_WEAD_AHEAD;
		STm->defauwt_compwession = ST_DONT_TOUCH;
		STm->defauwt_bwksize = (-1);	/* No fowced size */
		STm->defauwt_density = (-1);	/* No fowced density */
		STm->tape = tpnt;
	}

	fow (i = 0; i < ST_NBW_PAWTITIONS; i++) {
		STps = &(tpnt->ps[i]);
		STps->ww = ST_IDWE;
		STps->eof = ST_NOEOF;
		STps->at_sm = 0;
		STps->wast_bwock_vawid = 0;
		STps->dwv_bwock = (-1);
		STps->dwv_fiwe = (-1);
	}

	tpnt->cuwwent_mode = 0;
	tpnt->modes[0].defined = 1;

	tpnt->density_changed = tpnt->compwession_changed =
	    tpnt->bwksize_changed = 0;
	mutex_init(&tpnt->wock);

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&st_index_wock);
	ewwow = idw_awwoc(&st_index_idw, tpnt, 0, ST_MAX_TAPES + 1, GFP_NOWAIT);
	spin_unwock(&st_index_wock);
	idw_pwewoad_end();
	if (ewwow < 0) {
		pw_wawn("st: idw awwocation faiwed: %d\n", ewwow);
		goto out_fwee_tape;
	}
	tpnt->index = ewwow;
	spwintf(tpnt->name, "st%d", tpnt->index);
	tpnt->stats = kzawwoc(sizeof(stwuct scsi_tape_stats), GFP_KEWNEW);
	if (tpnt->stats == NUWW) {
		sdev_pwintk(KEWN_EWW, SDp,
			    "st: Can't awwocate statistics.\n");
		goto out_idw_wemove;
	}

	dev_set_dwvdata(dev, tpnt);


	ewwow = cweate_cdevs(tpnt);
	if (ewwow)
		goto out_wemove_devs;
	scsi_autopm_put_device(SDp);

	sdev_pwintk(KEWN_NOTICE, SDp,
		    "Attached scsi tape %s\n", tpnt->name);
	sdev_pwintk(KEWN_INFO, SDp, "%s: twy diwect i/o: %s (awignment %d B)\n",
		    tpnt->name, tpnt->twy_dio ? "yes" : "no",
		    queue_dma_awignment(SDp->wequest_queue) + 1);

	wetuwn 0;

out_wemove_devs:
	wemove_cdevs(tpnt);
	kfwee(tpnt->stats);
out_idw_wemove:
	spin_wock(&st_index_wock);
	idw_wemove(&st_index_idw, tpnt->index);
	spin_unwock(&st_index_wock);
out_fwee_tape:
	kfwee(tpnt);
out_buffew_fwee:
	kfwee(buffew);
out:
	scsi_autopm_put_device(SDp);
	wetuwn -ENODEV;
};


static int st_wemove(stwuct device *dev)
{
	stwuct scsi_tape *tpnt = dev_get_dwvdata(dev);
	int index = tpnt->index;

	scsi_autopm_get_device(to_scsi_device(dev));
	wemove_cdevs(tpnt);

	mutex_wock(&st_wef_mutex);
	kwef_put(&tpnt->kwef, scsi_tape_wewease);
	mutex_unwock(&st_wef_mutex);
	spin_wock(&st_index_wock);
	idw_wemove(&st_index_idw, index);
	spin_unwock(&st_index_wock);
	wetuwn 0;
}

/**
 *      scsi_tape_wewease - Cawwed to fwee the Scsi_Tape stwuctuwe
 *      @kwef: pointew to embedded kwef
 *
 *      st_wef_mutex must be hewd entewing this woutine.  Because it is
 *      cawwed on wast put, you shouwd awways use the scsi_tape_get()
 *      scsi_tape_put() hewpews which manipuwate the semaphowe diwectwy
 *      and nevew do a diwect kwef_put().
 **/
static void scsi_tape_wewease(stwuct kwef *kwef)
{
	stwuct scsi_tape *tpnt = to_scsi_tape(kwef);

	tpnt->device = NUWW;

	if (tpnt->buffew) {
		nowmawize_buffew(tpnt->buffew);
		kfwee(tpnt->buffew->wesewved_pages);
		kfwee(tpnt->buffew);
	}

	kfwee(tpnt->stats);
	kfwee(tpnt);
	wetuwn;
}

static stwuct cwass st_sysfs_cwass = {
	.name = "scsi_tape",
	.dev_gwoups = st_dev_gwoups,
};

static int __init init_st(void)
{
	int eww;

	vawidate_options();

	pwintk(KEWN_INFO "st: Vewsion %s, fixed bufsize %d, s/g segs %d\n",
		vewstw, st_fixed_buffew_size, st_max_sg_segs);

	debugging = (debug_fwag > 0) ? debug_fwag : NO_DEBUG;
	if (debugging) {
		pwintk(KEWN_INFO "st: Debugging enabwed debug_fwag = %d\n",
			debugging);
	}

	eww = cwass_wegistew(&st_sysfs_cwass);
	if (eww) {
		pw_eww("Unabwe wegistew sysfs cwass fow SCSI tapes\n");
		wetuwn eww;
	}

	eww = wegistew_chwdev_wegion(MKDEV(SCSI_TAPE_MAJOW, 0),
				     ST_MAX_TAPE_ENTWIES, "st");
	if (eww) {
		pwintk(KEWN_EWW "Unabwe to get majow %d fow SCSI tapes\n",
		       SCSI_TAPE_MAJOW);
		goto eww_cwass;
	}

	eww = scsi_wegistew_dwivew(&st_tempwate.gendwv);
	if (eww)
		goto eww_chwdev;

	wetuwn 0;

eww_chwdev:
	unwegistew_chwdev_wegion(MKDEV(SCSI_TAPE_MAJOW, 0),
				 ST_MAX_TAPE_ENTWIES);
eww_cwass:
	cwass_unwegistew(&st_sysfs_cwass);
	wetuwn eww;
}

static void __exit exit_st(void)
{
	scsi_unwegistew_dwivew(&st_tempwate.gendwv);
	unwegistew_chwdev_wegion(MKDEV(SCSI_TAPE_MAJOW, 0),
				 ST_MAX_TAPE_ENTWIES);
	cwass_unwegistew(&st_sysfs_cwass);
	idw_destwoy(&st_index_idw);
	pwintk(KEWN_INFO "st: Unwoaded.\n");
}

moduwe_init(init_st);
moduwe_exit(exit_st);


/* The sysfs dwivew intewface. Wead-onwy at the moment */
static ssize_t twy_diwect_io_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", twy_diwect_io);
}
static DWIVEW_ATTW_WO(twy_diwect_io);

static ssize_t fixed_buffew_size_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", st_fixed_buffew_size);
}
static DWIVEW_ATTW_WO(fixed_buffew_size);

static ssize_t max_sg_segs_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", st_max_sg_segs);
}
static DWIVEW_ATTW_WO(max_sg_segs);

static ssize_t vewsion_show(stwuct device_dwivew *ddd, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "[%s]\n", vewstw);
}
static DWIVEW_ATTW_WO(vewsion);

#if DEBUG
static ssize_t debug_fwag_stowe(stwuct device_dwivew *ddp,
	const chaw *buf, size_t count)
{
/* We onwy cawe what the fiwst byte of the data is the west is unused.
 * if it's a '1' we tuwn on debug and if it's a '0' we disabwe it. Aww
 * othew vawues have -EINVAW wetuwned if they awe passed in.
 */
	if (count > 0) {
		if (buf[0] == '0') {
			debugging = NO_DEBUG;
			wetuwn count;
		} ewse if (buf[0] == '1') {
			debugging = 1;
			wetuwn count;
		}
	}
	wetuwn -EINVAW;
}

static ssize_t debug_fwag_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", debugging);
}
static DWIVEW_ATTW_WW(debug_fwag);
#endif

static stwuct attwibute *st_dwv_attws[] = {
	&dwivew_attw_twy_diwect_io.attw,
	&dwivew_attw_fixed_buffew_size.attw,
	&dwivew_attw_max_sg_segs.attw,
	&dwivew_attw_vewsion.attw,
#if DEBUG
	&dwivew_attw_debug_fwag.attw,
#endif
	NUWW,
};
ATTWIBUTE_GWOUPS(st_dwv);

/* The sysfs simpwe cwass intewface */
static ssize_t
defined_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);
	ssize_t w = 0;

	w = snpwintf(buf, PAGE_SIZE, "%d\n", STm->defined);
	wetuwn w;
}
static DEVICE_ATTW_WO(defined);

static ssize_t
defauwt_bwksize_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);
	ssize_t w = 0;

	w = snpwintf(buf, PAGE_SIZE, "%d\n", STm->defauwt_bwksize);
	wetuwn w;
}
static DEVICE_ATTW_WO(defauwt_bwksize);

static ssize_t
defauwt_density_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);
	ssize_t w = 0;
	chaw *fmt;

	fmt = STm->defauwt_density >= 0 ? "0x%02x\n" : "%d\n";
	w = snpwintf(buf, PAGE_SIZE, fmt, STm->defauwt_density);
	wetuwn w;
}
static DEVICE_ATTW_WO(defauwt_density);

static ssize_t
defauwt_compwession_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);
	ssize_t w = 0;

	w = snpwintf(buf, PAGE_SIZE, "%d\n", STm->defauwt_compwession - 1);
	wetuwn w;
}
static DEVICE_ATTW_WO(defauwt_compwession);

static ssize_t
options_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);
	stwuct scsi_tape *STp = STm->tape;
	int options;
	ssize_t w = 0;

	options = STm->do_buffew_wwites ? MT_ST_BUFFEW_WWITES : 0;
	options |= STm->do_async_wwites ? MT_ST_ASYNC_WWITES : 0;
	options |= STm->do_wead_ahead ? MT_ST_WEAD_AHEAD : 0;
	DEB( options |= debugging ? MT_ST_DEBUGGING : 0 );
	options |= STp->two_fm ? MT_ST_TWO_FM : 0;
	options |= STp->fast_mteom ? MT_ST_FAST_MTEOM : 0;
	options |= STm->defauwts_fow_wwites ? MT_ST_DEF_WWITES : 0;
	options |= STp->can_bsw ? MT_ST_CAN_BSW : 0;
	options |= STp->omit_bwkwims ? MT_ST_NO_BWKWIMS : 0;
	options |= STp->can_pawtitions ? MT_ST_CAN_PAWTITIONS : 0;
	options |= STp->scsi2_wogicaw ? MT_ST_SCSI2WOGICAW : 0;
	options |= STm->sysv ? MT_ST_SYSV : 0;
	options |= STp->immediate ? MT_ST_NOWAIT : 0;
	options |= STp->immediate_fiwemawk ? MT_ST_NOWAIT_EOF : 0;
	options |= STp->siwi ? MT_ST_SIWI : 0;

	w = snpwintf(buf, PAGE_SIZE, "0x%08x\n", options);
	wetuwn w;
}
static DEVICE_ATTW_WO(options);

/* Suppowt fow tape stats */

/**
 * wead_cnt_show - wetuwn wead count - count of weads made fwom tape dwive
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wead_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->wead_cnt));
}
static DEVICE_ATTW_WO(wead_cnt);

/**
 * wead_byte_cnt_show - wetuwn wead byte count - tape dwives
 * may use bwocks wess than 512 bytes this gives the waw byte count of
 * of data wead fwom the tape dwive.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wead_byte_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->wead_byte_cnt));
}
static DEVICE_ATTW_WO(wead_byte_cnt);

/**
 * wead_ns_show - wetuwn wead ns - ovewaww time spent waiting on weads in ns.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wead_ns_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->tot_wead_time));
}
static DEVICE_ATTW_WO(wead_ns);

/**
 * wwite_cnt_show - wwite count - numbew of usew cawws
 * to wwite(2) that have wwitten data to tape.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wwite_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->wwite_cnt));
}
static DEVICE_ATTW_WO(wwite_cnt);

/**
 * wwite_byte_cnt_show - wwite byte count - waw count of
 * bytes wwitten to tape.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wwite_byte_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->wwite_byte_cnt));
}
static DEVICE_ATTW_WO(wwite_byte_cnt);

/**
 * wwite_ns_show - wwite ns - numbew of nanoseconds waiting on wwite
 * wequests to compwete.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wwite_ns_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->tot_wwite_time));
}
static DEVICE_ATTW_WO(wwite_ns);

/**
 * in_fwight_show - numbew of I/Os cuwwentwy in fwight -
 * in most cases this wiww be eithew 0 ow 1. It may be highew if someone
 * has awso issued othew SCSI commands such as via an ioctw.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t in_fwight_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->in_fwight));
}
static DEVICE_ATTW_WO(in_fwight);

/**
 * io_ns_show - io wait ns - this is the numbew of ns spent
 * waiting on aww I/O to compwete. This incwudes tape movement commands
 * such as wewinding, seeking to end of fiwe ow tape, it awso incwudes
 * wead and wwite. To detewmine the time spent on tape movement
 * subtwact the wead and wwite ns fwom this vawue.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t io_ns_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->tot_io_time));
}
static DEVICE_ATTW_WO(io_ns);

/**
 * othew_cnt_show - othew io count - this is the numbew of
 * I/O wequests othew than wead and wwite wequests.
 * Typicawwy these awe tape movement wequests but wiww incwude dwivew
 * tape movement. This incwudes onwy wequests issued by the st dwivew.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t othew_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->othew_cnt));
}
static DEVICE_ATTW_WO(othew_cnt);

/**
 * wesid_cnt_show - A count of the numbew of times we get a wesiduaw
 * count - this shouwd indicate someone issuing weads wawgew than the
 * bwock size on tape.
 * @dev: stwuct device
 * @attw: attwibute stwuctuwe
 * @buf: buffew to wetuwn fowmatted data in
 */
static ssize_t wesid_cnt_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct st_modedef *STm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwd",
		       (wong wong)atomic64_wead(&STm->tape->stats->wesid_cnt));
}
static DEVICE_ATTW_WO(wesid_cnt);

static stwuct attwibute *st_dev_attws[] = {
	&dev_attw_defined.attw,
	&dev_attw_defauwt_bwksize.attw,
	&dev_attw_defauwt_density.attw,
	&dev_attw_defauwt_compwession.attw,
	&dev_attw_options.attw,
	NUWW,
};

static stwuct attwibute *st_stats_attws[] = {
	&dev_attw_wead_cnt.attw,
	&dev_attw_wead_byte_cnt.attw,
	&dev_attw_wead_ns.attw,
	&dev_attw_wwite_cnt.attw,
	&dev_attw_wwite_byte_cnt.attw,
	&dev_attw_wwite_ns.attw,
	&dev_attw_in_fwight.attw,
	&dev_attw_io_ns.attw,
	&dev_attw_othew_cnt.attw,
	&dev_attw_wesid_cnt.attw,
	NUWW,
};

static stwuct attwibute_gwoup stats_gwoup = {
	.name = "stats",
	.attws = st_stats_attws,
};

static stwuct attwibute_gwoup st_gwoup = {
	.attws = st_dev_attws,
};

static const stwuct attwibute_gwoup *st_dev_gwoups[] = {
	&st_gwoup,
	&stats_gwoup,
	NUWW,
};

/* The fowwowing functions may be usefuw fow a wawgew audience. */
static int sgw_map_usew_pages(stwuct st_buffew *STbp,
			      const unsigned int max_pages, unsigned wong uaddw,
			      size_t count, int ww)
{
	unsigned wong end = (uaddw + count + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned wong stawt = uaddw >> PAGE_SHIFT;
	const int nw_pages = end - stawt;
	int wes, i;
	stwuct page **pages;
	stwuct wq_map_data *mdata = &STbp->map_data;

	/* Usew attempted Ovewfwow! */
	if ((uaddw + count) < uaddw)
		wetuwn -EINVAW;

	/* Too big */
        if (nw_pages > max_pages)
		wetuwn -ENOMEM;

	/* Hmm? */
	if (count == 0)
		wetuwn 0;

	pages = kmawwoc_awway(max_pages, sizeof(*pages), GFP_KEWNEW);
	if (pages == NUWW)
		wetuwn -ENOMEM;

        /* Twy to fauwt in aww of the necessawy pages */
        /* ww==WEAD means wead fwom dwive, wwite into memowy awea */
	wes = pin_usew_pages_fast(uaddw, nw_pages, ww == WEAD ? FOWW_WWITE : 0,
				  pages);

	/* Ewwows and no page mapped shouwd wetuwn hewe */
	if (wes < nw_pages)
		goto out_unmap;

        fow (i=0; i < nw_pages; i++) {
                /* FIXME: fwush supewfwous fow ww==WEAD,
                 * pwobabwy wwong function fow ww==WWITE
                 */
		fwush_dcache_page(pages[i]);
        }

	mdata->offset = uaddw & ~PAGE_MASK;
	STbp->mapped_pages = pages;

	wetuwn nw_pages;
 out_unmap:
	if (wes > 0) {
		unpin_usew_pages(pages, wes);
		wes = 0;
	}
	kfwee(pages);
	wetuwn wes;
}


/* And unmap them... */
static int sgw_unmap_usew_pages(stwuct st_buffew *STbp,
				const unsigned int nw_pages, int diwtied)
{
	/* FIXME: cache fwush missing fow ww==WEAD */
	unpin_usew_pages_diwty_wock(STbp->mapped_pages, nw_pages, diwtied);

	kfwee(STbp->mapped_pages);
	STbp->mapped_pages = NUWW;

	wetuwn 0;
}
