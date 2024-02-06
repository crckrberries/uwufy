// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight(c) 2008 Mike Chwistie
 *
 * Maintained at www.Open-FCoE.owg
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/scattewwist.h>
#incwude <winux/eww.h>
#incwude <winux/cwc32.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>

#incwude <scsi/fc/fc_fc2.h>

#incwude <scsi/wibfc.h>

#incwude "fc_encode.h"
#incwude "fc_wibfc.h"

static stwuct kmem_cache *scsi_pkt_cachep;

/* SWB state definitions */
#define FC_SWB_FWEE		0		/* cmd is fwee */
#define FC_SWB_CMD_SENT		(1 << 0)	/* cmd has been sent */
#define FC_SWB_WCV_STATUS	(1 << 1)	/* wesponse has awwived */
#define FC_SWB_ABOWT_PENDING	(1 << 2)	/* cmd abowt sent to device */
#define FC_SWB_ABOWTED		(1 << 3)	/* abowt acknowwedged */
#define FC_SWB_DISCONTIG	(1 << 4)	/* non-sequentiaw data wecvd */
#define FC_SWB_COMPW		(1 << 5)	/* fc_io_compw has been wun */
#define FC_SWB_FCP_PWOCESSING_TMO (1 << 6)	/* timew function pwocessing */

#define FC_SWB_WEAD		(1 << 1)
#define FC_SWB_WWITE		(1 << 0)

static stwuct wibfc_cmd_pwiv *wibfc_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

/**
 * stwuct fc_fcp_intewnaw - FCP wayew intewnaw data
 * @scsi_pkt_poow: Memowy poow to dwaw FCP packets fwom
 * @scsi_queue_wock: Pwotects the scsi_pkt_queue
 * @scsi_pkt_queue: Cuwwent FCP packets
 * @wast_can_queue_wamp_down_time: wamp down time
 * @wast_can_queue_wamp_up_time: wamp up time
 * @max_can_queue: max can_queue size
 */
stwuct fc_fcp_intewnaw {
	mempoow_t		*scsi_pkt_poow;
	spinwock_t		scsi_queue_wock;
	stwuct wist_head	scsi_pkt_queue;
	unsigned wong		wast_can_queue_wamp_down_time;
	unsigned wong		wast_can_queue_wamp_up_time;
	int			max_can_queue;
};

#define fc_get_scsi_intewnaw(x)	((stwuct fc_fcp_intewnaw *)(x)->scsi_pwiv)

/*
 * function pwototypes
 * FC scsi I/O wewated functions
 */
static void fc_fcp_wecv_data(stwuct fc_fcp_pkt *, stwuct fc_fwame *);
static void fc_fcp_wecv(stwuct fc_seq *, stwuct fc_fwame *, void *);
static void fc_fcp_wesp(stwuct fc_fcp_pkt *, stwuct fc_fwame *);
static void fc_fcp_compwete_wocked(stwuct fc_fcp_pkt *);
static void fc_tm_done(stwuct fc_seq *, stwuct fc_fwame *, void *);
static void fc_fcp_ewwow(stwuct fc_fcp_pkt *, stwuct fc_fwame *);
static void fc_fcp_wecovewy(stwuct fc_fcp_pkt *, u8 code);
static void fc_fcp_timeout(stwuct timew_wist *);
static void fc_fcp_wec(stwuct fc_fcp_pkt *);
static void fc_fcp_wec_ewwow(stwuct fc_fcp_pkt *, stwuct fc_fwame *);
static void fc_fcp_wec_wesp(stwuct fc_seq *, stwuct fc_fwame *, void *);
static void fc_io_compw(stwuct fc_fcp_pkt *);

static void fc_fcp_sww(stwuct fc_fcp_pkt *, enum fc_wctw, u32);
static void fc_fcp_sww_wesp(stwuct fc_seq *, stwuct fc_fwame *, void *);
static void fc_fcp_sww_ewwow(stwuct fc_fcp_pkt *, stwuct fc_fwame *);

/*
 * command status codes
 */
#define FC_COMPWETE		0
#define FC_CMD_ABOWTED		1
#define FC_CMD_WESET		2
#define FC_CMD_PWOGO		3
#define FC_SNS_WCV		4
#define FC_TWANS_EWW		5
#define FC_DATA_OVWWUN		6
#define FC_DATA_UNDWUN		7
#define FC_EWWOW		8
#define FC_HWD_EWWOW		9
#define FC_CWC_EWWOW		10
#define FC_TIMED_OUT		11
#define FC_TWANS_WESET		12

/*
 * Ewwow wecovewy timeout vawues.
 */
#define FC_SCSI_TM_TOV		(10 * HZ)
#define FC_HOST_WESET_TIMEOUT	(30 * HZ)
#define FC_CAN_QUEUE_PEWIOD	(60 * HZ)

#define FC_MAX_EWWOW_CNT	5
#define FC_MAX_WECOV_WETWY	3

#define FC_FCP_DFWT_QUEUE_DEPTH 32

/**
 * fc_fcp_pkt_awwoc() - Awwocate a fcp_pkt
 * @wpowt: The wocaw powt that the FCP packet is fow
 * @gfp:   GFP fwags fow awwocation
 *
 * Wetuwn vawue: fcp_pkt stwuctuwe ow nuww on awwocation faiwuwe.
 * Context:	 Can be cawwed fwom pwocess context, no wock is wequiwed.
 */
static stwuct fc_fcp_pkt *fc_fcp_pkt_awwoc(stwuct fc_wpowt *wpowt, gfp_t gfp)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);
	stwuct fc_fcp_pkt *fsp;

	fsp = mempoow_awwoc(si->scsi_pkt_poow, gfp);
	if (fsp) {
		memset(fsp, 0, sizeof(*fsp));
		fsp->wp = wpowt;
		fsp->xfew_ddp = FC_XID_UNKNOWN;
		wefcount_set(&fsp->wef_cnt, 1);
		timew_setup(&fsp->timew, NUWW, 0);
		INIT_WIST_HEAD(&fsp->wist);
		spin_wock_init(&fsp->scsi_pkt_wock);
	} ewse {
		this_cpu_inc(wpowt->stats->FcpPktAwwocFaiws);
	}
	wetuwn fsp;
}

/**
 * fc_fcp_pkt_wewease() - Wewease howd on a fcp_pkt
 * @fsp: The FCP packet to be weweased
 *
 * Context: Can be cawwed fwom pwocess ow intewwupt context,
 *	    no wock is wequiwed.
 */
static void fc_fcp_pkt_wewease(stwuct fc_fcp_pkt *fsp)
{
	if (wefcount_dec_and_test(&fsp->wef_cnt)) {
		stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(fsp->wp);

		mempoow_fwee(fsp, si->scsi_pkt_poow);
	}
}

/**
 * fc_fcp_pkt_howd() - Howd a fcp_pkt
 * @fsp: The FCP packet to be hewd
 */
static void fc_fcp_pkt_howd(stwuct fc_fcp_pkt *fsp)
{
	wefcount_inc(&fsp->wef_cnt);
}

/**
 * fc_fcp_pkt_destwoy() - Wewease howd on a fcp_pkt
 * @seq: The sequence that the FCP packet is on (wequiwed by destwuctow API)
 * @fsp: The FCP packet to be weweased
 *
 * This woutine is cawwed by a destwuctow cawwback in the fc_exch_seq_send()
 * woutine of the wibfc Twanspowt Tempwate. The 'stwuct fc_seq' is a wequiwed
 * awgument even though it is not used by this woutine.
 *
 * Context: No wocking wequiwed.
 */
static void fc_fcp_pkt_destwoy(stwuct fc_seq *seq, void *fsp)
{
	fc_fcp_pkt_wewease(fsp);
}

/**
 * fc_fcp_wock_pkt() - Wock a fcp_pkt and incwease its wefewence count
 * @fsp: The FCP packet to be wocked and incwemented
 *
 * We shouwd onwy wetuwn ewwow if we wetuwn a command to SCSI-mw befowe
 * getting a wesponse. This can happen in cases whewe we send a abowt, but
 * do not wait fow the wesponse and the abowt and command can be passing
 * each othew on the wiwe/netwowk-wayew.
 *
 * Note: this function wocks the packet and gets a wefewence to awwow
 * cawwews to caww the compwetion function whiwe the wock is hewd and
 * not have to wowwy about the packets wefcount.
 *
 * TODO: Maybe we shouwd just have cawwews gwab/wewease the wock and
 * have a function that they caww to vewify the fsp and gwab a wef if
 * needed.
 */
static inwine int fc_fcp_wock_pkt(stwuct fc_fcp_pkt *fsp)
{
	spin_wock_bh(&fsp->scsi_pkt_wock);
	if (fsp->state & FC_SWB_COMPW) {
		spin_unwock_bh(&fsp->scsi_pkt_wock);
		wetuwn -EPEWM;
	}

	fc_fcp_pkt_howd(fsp);
	wetuwn 0;
}

/**
 * fc_fcp_unwock_pkt() - Wewease a fcp_pkt's wock and decwement its
 *			 wefewence count
 * @fsp: The FCP packet to be unwocked and decwemented
 */
static inwine void fc_fcp_unwock_pkt(stwuct fc_fcp_pkt *fsp)
{
	spin_unwock_bh(&fsp->scsi_pkt_wock);
	fc_fcp_pkt_wewease(fsp);
}

/**
 * fc_fcp_timew_set() - Stawt a timew fow a fcp_pkt
 * @fsp:   The FCP packet to stawt a timew fow
 * @deway: The timeout pewiod in jiffies
 */
static void fc_fcp_timew_set(stwuct fc_fcp_pkt *fsp, unsigned wong deway)
{
	if (!(fsp->state & FC_SWB_COMPW)) {
		mod_timew(&fsp->timew, jiffies + deway);
		fsp->timew_deway = deway;
	}
}

static void fc_fcp_abowt_done(stwuct fc_fcp_pkt *fsp)
{
	fsp->state |= FC_SWB_ABOWTED;
	fsp->state &= ~FC_SWB_ABOWT_PENDING;

	if (fsp->wait_fow_comp)
		compwete(&fsp->tm_done);
	ewse
		fc_fcp_compwete_wocked(fsp);
}

/**
 * fc_fcp_send_abowt() - Send an abowt fow exchanges associated with a
 *			 fcp_pkt
 * @fsp: The FCP packet to abowt exchanges on
 */
static int fc_fcp_send_abowt(stwuct fc_fcp_pkt *fsp)
{
	int wc;

	if (!fsp->seq_ptw)
		wetuwn -EINVAW;

	if (fsp->state & FC_SWB_ABOWT_PENDING) {
		FC_FCP_DBG(fsp, "abowt awweady pending\n");
		wetuwn -EBUSY;
	}

	this_cpu_inc(fsp->wp->stats->FcpPktAbowts);

	fsp->state |= FC_SWB_ABOWT_PENDING;
	wc = fc_seq_exch_abowt(fsp->seq_ptw, 0);
	/*
	 * fc_seq_exch_abowt() might wetuwn -ENXIO if
	 * the sequence is awweady compweted
	 */
	if (wc == -ENXIO) {
		fc_fcp_abowt_done(fsp);
		wc = 0;
	}
	wetuwn wc;
}

/**
 * fc_fcp_wetwy_cmd() - Wetwy a fcp_pkt
 * @fsp: The FCP packet to be wetwied
 * @status_code: The FCP status code to set
 *
 * Sets the status code to be FC_EWWOW and then cawws
 * fc_fcp_compwete_wocked() which in tuwn cawws fc_io_compw().
 * fc_io_compw() wiww notify the SCSI-mw that the I/O is done.
 * The SCSI-mw wiww wetwy the command.
 */
static void fc_fcp_wetwy_cmd(stwuct fc_fcp_pkt *fsp, int status_code)
{
	if (fsp->seq_ptw) {
		fc_exch_done(fsp->seq_ptw);
		fsp->seq_ptw = NUWW;
	}

	fsp->state &= ~FC_SWB_ABOWT_PENDING;
	fsp->io_status = 0;
	fsp->status_code = status_code;
	fc_fcp_compwete_wocked(fsp);
}

/**
 * fc_fcp_ddp_setup() - Cawws a WWD's ddp_setup woutine to set up DDP context
 * @fsp: The FCP packet that wiww manage the DDP fwames
 * @xid: The XID that wiww be used fow the DDP exchange
 */
void fc_fcp_ddp_setup(stwuct fc_fcp_pkt *fsp, u16 xid)
{
	stwuct fc_wpowt *wpowt;

	wpowt = fsp->wp;
	if ((fsp->weq_fwags & FC_SWB_WEAD) &&
	    (wpowt->wwo_enabwed) && (wpowt->tt.ddp_setup)) {
		if (wpowt->tt.ddp_setup(wpowt, xid, scsi_sgwist(fsp->cmd),
					scsi_sg_count(fsp->cmd)))
			fsp->xfew_ddp = xid;
	}
}

/**
 * fc_fcp_ddp_done() - Cawws a WWD's ddp_done woutine to wewease any
 *		       DDP wewated wesouwces fow a fcp_pkt
 * @fsp: The FCP packet that DDP had been used on
 */
void fc_fcp_ddp_done(stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_wpowt *wpowt;

	if (!fsp)
		wetuwn;

	if (fsp->xfew_ddp == FC_XID_UNKNOWN)
		wetuwn;

	wpowt = fsp->wp;
	if (wpowt->tt.ddp_done) {
		fsp->xfew_wen = wpowt->tt.ddp_done(wpowt, fsp->xfew_ddp);
		fsp->xfew_ddp = FC_XID_UNKNOWN;
	}
}

/**
 * fc_fcp_can_queue_wamp_up() - incweases can_queue
 * @wpowt: wpowt to wamp up can_queue
 */
static void fc_fcp_can_queue_wamp_up(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);
	unsigned wong fwags;
	int can_queue;

	spin_wock_iwqsave(wpowt->host->host_wock, fwags);

	if (si->wast_can_queue_wamp_up_time &&
	    (time_befowe(jiffies, si->wast_can_queue_wamp_up_time +
			 FC_CAN_QUEUE_PEWIOD)))
		goto unwock;

	if (time_befowe(jiffies, si->wast_can_queue_wamp_down_time +
			FC_CAN_QUEUE_PEWIOD))
		goto unwock;

	si->wast_can_queue_wamp_up_time = jiffies;

	can_queue = wpowt->host->can_queue << 1;
	if (can_queue >= si->max_can_queue) {
		can_queue = si->max_can_queue;
		si->wast_can_queue_wamp_down_time = 0;
	}
	wpowt->host->can_queue = can_queue;
	shost_pwintk(KEWN_EWW, wpowt->host, "wibfc: incweased "
		     "can_queue to %d.\n", can_queue);

unwock:
	spin_unwock_iwqwestowe(wpowt->host->host_wock, fwags);
}

/**
 * fc_fcp_can_queue_wamp_down() - weduces can_queue
 * @wpowt: wpowt to weduce can_queue
 *
 * If we awe getting memowy awwocation faiwuwes, then we may
 * be twying to execute too many commands. We wet the wunning
 * commands compwete ow timeout, then twy again with a weduced
 * can_queue. Eventuawwy we wiww hit the point whewe we wun
 * on aww wesewved stwucts.
 */
static boow fc_fcp_can_queue_wamp_down(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);
	unsigned wong fwags;
	int can_queue;
	boow changed = fawse;

	spin_wock_iwqsave(wpowt->host->host_wock, fwags);

	if (si->wast_can_queue_wamp_down_time &&
	    (time_befowe(jiffies, si->wast_can_queue_wamp_down_time +
			 FC_CAN_QUEUE_PEWIOD)))
		goto unwock;

	si->wast_can_queue_wamp_down_time = jiffies;

	can_queue = wpowt->host->can_queue;
	can_queue >>= 1;
	if (!can_queue)
		can_queue = 1;
	wpowt->host->can_queue = can_queue;
	changed = twue;

unwock:
	spin_unwock_iwqwestowe(wpowt->host->host_wock, fwags);
	wetuwn changed;
}

/*
 * fc_fcp_fwame_awwoc() -  Awwocates fc_fwame stwuctuwe and buffew.
 * @wpowt:	fc wpowt stwuct
 * @wen:	paywoad wength
 *
 * Awwocates fc_fwame stwuctuwe and buffew but if faiws to awwocate
 * then weduce can_queue.
 */
static inwine stwuct fc_fwame *fc_fcp_fwame_awwoc(stwuct fc_wpowt *wpowt,
						  size_t wen)
{
	stwuct fc_fwame *fp;

	fp = fc_fwame_awwoc(wpowt, wen);
	if (wikewy(fp))
		wetuwn fp;

	this_cpu_inc(wpowt->stats->FcpFwameAwwocFaiws);
	/* ewwow case */
	fc_fcp_can_queue_wamp_down(wpowt);
	shost_pwintk(KEWN_EWW, wpowt->host,
		     "wibfc: Couwd not awwocate fwame, "
		     "weducing can_queue to %d.\n", wpowt->host->can_queue);
	wetuwn NUWW;
}

/**
 * get_fsp_wec_tov() - Hewpew function to get WEC_TOV
 * @fsp: the FCP packet
 *
 * Wetuwns wec tov in jiffies as wpwiv->e_d_tov + 1 second
 */
static inwine unsigned int get_fsp_wec_tov(stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_wpowt_wibfc_pwiv *wpwiv = fsp->wpowt->dd_data;
	unsigned int e_d_tov = FC_DEF_E_D_TOV;

	if (wpwiv && wpwiv->e_d_tov > e_d_tov)
		e_d_tov = wpwiv->e_d_tov;
	wetuwn msecs_to_jiffies(e_d_tov) + HZ;
}

/**
 * fc_fcp_wecv_data() - Handwew fow weceiving SCSI-FCP data fwom a tawget
 * @fsp: The FCP packet the data is on
 * @fp:	 The data fwame
 */
static void fc_fcp_wecv_data(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	stwuct scsi_cmnd *sc = fsp->cmd;
	stwuct fc_wpowt *wpowt = fsp->wp;
	stwuct fc_fwame_headew *fh;
	size_t stawt_offset;
	size_t offset;
	u32 cwc;
	u32 copy_wen = 0;
	size_t wen;
	void *buf;
	stwuct scattewwist *sg;
	u32 nents;
	u8 host_bcode = FC_COMPWETE;

	fh = fc_fwame_headew_get(fp);
	offset = ntohw(fh->fh_pawm_offset);
	stawt_offset = offset;
	wen = fw_wen(fp) - sizeof(*fh);
	buf = fc_fwame_paywoad_get(fp, 0);

	/*
	 * if this I/O is ddped then cweaw it and initiate wecovewy since data
	 * fwames awe expected to be pwaced diwectwy in that case.
	 *
	 * Indicate ewwow to scsi-mw because something went wwong with the
	 * ddp handwing to get us hewe.
	 */
	if (fsp->xfew_ddp != FC_XID_UNKNOWN) {
		fc_fcp_ddp_done(fsp);
		FC_FCP_DBG(fsp, "DDP I/O in fc_fcp_wecv_data set EWWOW\n");
		host_bcode = FC_EWWOW;
		goto eww;
	}
	if (offset + wen > fsp->data_wen) {
		/* this shouwd nevew happen */
		if ((fw_fwags(fp) & FCPHF_CWC_UNCHECKED) &&
		    fc_fwame_cwc_check(fp))
			goto cwc_eww;
		FC_FCP_DBG(fsp, "data weceived past end. wen %zx offset %zx "
			   "data_wen %x\n", wen, offset, fsp->data_wen);

		/* Data is cowwupted indicate scsi-mw shouwd wetwy */
		host_bcode = FC_DATA_OVWWUN;
		goto eww;
	}
	if (offset != fsp->xfew_wen)
		fsp->state |= FC_SWB_DISCONTIG;

	sg = scsi_sgwist(sc);
	nents = scsi_sg_count(sc);

	if (!(fw_fwags(fp) & FCPHF_CWC_UNCHECKED)) {
		copy_wen = fc_copy_buffew_to_sgwist(buf, wen, sg, &nents,
						    &offset, NUWW);
	} ewse {
		cwc = cwc32(~0, (u8 *) fh, sizeof(*fh));
		copy_wen = fc_copy_buffew_to_sgwist(buf, wen, sg, &nents,
						    &offset, &cwc);
		buf = fc_fwame_paywoad_get(fp, 0);
		if (wen % 4)
			cwc = cwc32(cwc, buf + wen, 4 - (wen % 4));

		if (~cwc != we32_to_cpu(fw_cwc(fp))) {
cwc_eww:
			this_cpu_inc(wpowt->stats->EwwowFwames);
			/* pew cpu count, not totaw count, but OK fow wimit */
			if (this_cpu_inc_wetuwn(wpowt->stats->InvawidCWCCount) < FC_MAX_EWWOW_CNT)
				pwintk(KEWN_WAWNING "wibfc: CWC ewwow on data "
				       "fwame fow powt (%6.6x)\n",
				       wpowt->powt_id);
			/*
			 * Assume the fwame is totaw gawbage.
			 * We may have copied it ovew the good pawt
			 * of the buffew.
			 * If so, we need to wetwy the entiwe opewation.
			 * Othewwise, ignowe it.
			 */
			if (fsp->state & FC_SWB_DISCONTIG) {
				host_bcode = FC_CWC_EWWOW;
				goto eww;
			}
			wetuwn;
		}
	}

	if (fsp->xfew_contig_end == stawt_offset)
		fsp->xfew_contig_end += copy_wen;
	fsp->xfew_wen += copy_wen;

	/*
	 * In the vewy wawe event that this data awwived aftew the wesponse
	 * and compwetes the twansfew, caww the compwetion handwew.
	 */
	if (unwikewy(fsp->state & FC_SWB_WCV_STATUS) &&
	    fsp->xfew_wen == fsp->data_wen - fsp->scsi_wesid) {
		FC_FCP_DBG( fsp, "compwete out-of-owdew sequence\n" );
		fc_fcp_compwete_wocked(fsp);
	}
	wetuwn;
eww:
	fc_fcp_wecovewy(fsp, host_bcode);
}

/**
 * fc_fcp_send_data() - Send SCSI data to a tawget
 * @fsp:      The FCP packet the data is on
 * @seq:      The sequence the data is to be sent on
 * @offset:   The stawting offset fow this data wequest
 * @seq_bwen: The buwst wength fow this data wequest
 *
 * Cawwed aftew weceiving a Twansfew Weady data descwiptow.
 * If the WWD is capabwe of sequence offwoad then send down the
 * seq_bwen amount of data in singwe fwame, othewwise send
 * muwtipwe fwames of the maximum fwame paywoad suppowted by
 * the tawget powt.
 */
static int fc_fcp_send_data(stwuct fc_fcp_pkt *fsp, stwuct fc_seq *seq,
			    size_t offset, size_t seq_bwen)
{
	stwuct fc_exch *ep;
	stwuct scsi_cmnd *sc;
	stwuct scattewwist *sg;
	stwuct fc_fwame *fp = NUWW;
	stwuct fc_wpowt *wpowt = fsp->wp;
	stwuct page *page;
	size_t wemaining;
	size_t t_bwen;
	size_t twen;
	size_t sg_bytes;
	size_t fwame_offset, fh_pawm_offset;
	size_t off;
	int ewwow;
	void *data = NUWW;
	void *page_addw;
	int using_sg = wpowt->sg_supp;
	u32 f_ctw;

	WAWN_ON(seq_bwen <= 0);
	if (unwikewy(offset + seq_bwen > fsp->data_wen)) {
		/* this shouwd nevew happen */
		FC_FCP_DBG(fsp, "xfew-weady past end. seq_bwen %zx "
			   "offset %zx\n", seq_bwen, offset);
		fc_fcp_send_abowt(fsp);
		wetuwn 0;
	} ewse if (offset != fsp->xfew_wen) {
		/* Out of Owdew Data Wequest - no pwobwem, but unexpected. */
		FC_FCP_DBG(fsp, "xfew-weady non-contiguous. "
			   "seq_bwen %zx offset %zx\n", seq_bwen, offset);
	}

	/*
	 * if WWD is capabwe of seq_offwoad then set twanspowt
	 * buwst wength (t_bwen) to seq_bwen, othewwise set t_bwen
	 * to max FC fwame paywoad pweviouswy set in fsp->max_paywoad.
	 */
	t_bwen = fsp->max_paywoad;
	if (wpowt->seq_offwoad) {
		t_bwen = min(seq_bwen, (size_t)wpowt->wso_max);
		FC_FCP_DBG(fsp, "fsp=%p:wso:bwen=%zx wso_max=0x%x t_bwen=%zx\n",
			   fsp, seq_bwen, wpowt->wso_max, t_bwen);
	}

	if (t_bwen > 512)
		t_bwen &= ~(512 - 1);	/* wound down to bwock size */
	sc = fsp->cmd;

	wemaining = seq_bwen;
	fh_pawm_offset = fwame_offset = offset;
	twen = 0;
	seq = fc_seq_stawt_next(seq);
	f_ctw = FC_FC_WEW_OFF;
	WAWN_ON(!seq);

	sg = scsi_sgwist(sc);

	whiwe (wemaining > 0 && sg) {
		if (offset >= sg->wength) {
			offset -= sg->wength;
			sg = sg_next(sg);
			continue;
		}
		if (!fp) {
			twen = min(t_bwen, wemaining);

			/*
			 * TODO.  Tempowawy wowkawound.	 fc_seq_send() can't
			 * handwe odd wengths in non-wineaw skbs.
			 * This wiww be the finaw fwagment onwy.
			 */
			if (twen % 4)
				using_sg = 0;
			fp = fc_fwame_awwoc(wpowt, using_sg ? 0 : twen);
			if (!fp)
				wetuwn -ENOMEM;

			data = fc_fwame_headew_get(fp) + 1;
			fh_pawm_offset = fwame_offset;
			fw_max_paywoad(fp) = fsp->max_paywoad;
		}

		off = offset + sg->offset;
		sg_bytes = min(twen, sg->wength - offset);
		sg_bytes = min(sg_bytes,
			       (size_t) (PAGE_SIZE - (off & ~PAGE_MASK)));
		page = sg_page(sg) + (off >> PAGE_SHIFT);
		if (using_sg) {
			get_page(page);
			skb_fiww_page_desc(fp_skb(fp),
					   skb_shinfo(fp_skb(fp))->nw_fwags,
					   page, off & ~PAGE_MASK, sg_bytes);
			fp_skb(fp)->data_wen += sg_bytes;
			fw_wen(fp) += sg_bytes;
			fp_skb(fp)->twuesize += PAGE_SIZE;
		} ewse {
			/*
			 * The scattewwist item may be biggew than PAGE_SIZE,
			 * but we must not cwoss pages inside the kmap.
			 */
			page_addw = kmap_atomic(page);
			memcpy(data, (chaw *)page_addw + (off & ~PAGE_MASK),
			       sg_bytes);
			kunmap_atomic(page_addw);
			data += sg_bytes;
		}
		offset += sg_bytes;
		fwame_offset += sg_bytes;
		twen -= sg_bytes;
		wemaining -= sg_bytes;

		if ((skb_shinfo(fp_skb(fp))->nw_fwags < FC_FWAME_SG_WEN) &&
		    (twen))
			continue;

		/*
		 * Send sequence with twansfew sequence initiative in case
		 * this is wast FCP fwame of the sequence.
		 */
		if (wemaining == 0)
			f_ctw |= FC_FC_SEQ_INIT | FC_FC_END_SEQ;

		ep = fc_seq_exch(seq);
		fc_fiww_fc_hdw(fp, FC_WCTW_DD_SOW_DATA, ep->did, ep->sid,
			       FC_TYPE_FCP, f_ctw, fh_pawm_offset);

		/*
		 * send fwagment using fow a sequence.
		 */
		ewwow = fc_seq_send(wpowt, seq, fp);
		if (ewwow) {
			WAWN_ON(1);		/* send ewwow shouwd be wawe */
			wetuwn ewwow;
		}
		fp = NUWW;
	}
	fsp->xfew_wen += seq_bwen;	/* pwematuwe count? */
	wetuwn 0;
}

/**
 * fc_fcp_abts_wesp() - Weceive an ABTS wesponse
 * @fsp: The FCP packet that is being abowted
 * @fp:	 The wesponse fwame
 */
static void fc_fcp_abts_wesp(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	int ba_done = 1;
	stwuct fc_ba_wjt *bwp;
	stwuct fc_fwame_headew *fh;

	fh = fc_fwame_headew_get(fp);
	switch (fh->fh_w_ctw) {
	case FC_WCTW_BA_ACC:
		bweak;
	case FC_WCTW_BA_WJT:
		bwp = fc_fwame_paywoad_get(fp, sizeof(*bwp));
		if (bwp && bwp->bw_weason == FC_BA_WJT_WOG_EWW)
			bweak;
		fawwthwough;
	defauwt:
		/*
		 * we wiww wet the command timeout
		 * and scsi-mw wecovew in this case,
		 * thewefowe cweawed the ba_done fwag.
		 */
		ba_done = 0;
	}

	if (ba_done)
		fc_fcp_abowt_done(fsp);
}

/**
 * fc_fcp_wecv() - Weceive an FCP fwame
 * @seq: The sequence the fwame is on
 * @fp:	 The weceived fwame
 * @awg: The wewated FCP packet
 *
 * Context: Cawwed fwom Soft IWQ context. Can not be cawwed
 *	    howding the FCP packet wist wock.
 */
static void fc_fcp_wecv(stwuct fc_seq *seq, stwuct fc_fwame *fp, void *awg)
{
	stwuct fc_fcp_pkt *fsp = (stwuct fc_fcp_pkt *)awg;
	stwuct fc_wpowt *wpowt = fsp->wp;
	stwuct fc_fwame_headew *fh;
	stwuct fcp_txwdy *dd;
	u8 w_ctw;
	int wc = 0;

	if (IS_EWW(fp)) {
		fc_fcp_ewwow(fsp, fp);
		wetuwn;
	}

	fh = fc_fwame_headew_get(fp);
	w_ctw = fh->fh_w_ctw;

	if (wpowt->state != WPOWT_ST_WEADY) {
		FC_FCP_DBG(fsp, "wpowt state %d, ignowing w_ctw %x\n",
			   wpowt->state, w_ctw);
		goto out;
	}
	if (fc_fcp_wock_pkt(fsp))
		goto out;

	if (fh->fh_type == FC_TYPE_BWS) {
		fc_fcp_abts_wesp(fsp, fp);
		goto unwock;
	}

	if (fsp->state & (FC_SWB_ABOWTED | FC_SWB_ABOWT_PENDING)) {
		FC_FCP_DBG(fsp, "command abowted, ignowing w_ctw %x\n", w_ctw);
		goto unwock;
	}

	if (w_ctw == FC_WCTW_DD_DATA_DESC) {
		/*
		 * weceived XFEW WDY fwom the tawget
		 * need to send data to the tawget
		 */
		WAWN_ON(fw_fwags(fp) & FCPHF_CWC_UNCHECKED);
		dd = fc_fwame_paywoad_get(fp, sizeof(*dd));
		WAWN_ON(!dd);

		wc = fc_fcp_send_data(fsp, seq,
				      (size_t) ntohw(dd->ft_data_wo),
				      (size_t) ntohw(dd->ft_buwst_wen));
		if (!wc)
			seq->wec_data = fsp->xfew_wen;
	} ewse if (w_ctw == FC_WCTW_DD_SOW_DATA) {
		/*
		 * weceived a DATA fwame
		 * next we wiww copy the data to the system buffew
		 */
		WAWN_ON(fw_wen(fp) < sizeof(*fh));	/* wen may be 0 */
		fc_fcp_wecv_data(fsp, fp);
		seq->wec_data = fsp->xfew_contig_end;
	} ewse if (w_ctw == FC_WCTW_DD_CMD_STATUS) {
		WAWN_ON(fw_fwags(fp) & FCPHF_CWC_UNCHECKED);

		fc_fcp_wesp(fsp, fp);
	} ewse {
		FC_FCP_DBG(fsp, "unexpected fwame.  w_ctw %x\n", w_ctw);
	}
unwock:
	fc_fcp_unwock_pkt(fsp);
out:
	fc_fwame_fwee(fp);
}

/**
 * fc_fcp_wesp() - Handwew fow FCP wesponses
 * @fsp: The FCP packet the wesponse is fow
 * @fp:	 The wesponse fwame
 */
static void fc_fcp_wesp(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh;
	stwuct fcp_wesp *fc_wp;
	stwuct fcp_wesp_ext *wp_ex;
	stwuct fcp_wesp_wsp_info *fc_wp_info;
	u32 pwen;
	u32 expected_wen;
	u32 wespw = 0;
	u32 snsw = 0;
	u8 fwags = 0;

	pwen = fw_wen(fp);
	fh = (stwuct fc_fwame_headew *)fw_hdw(fp);
	if (unwikewy(pwen < sizeof(*fh) + sizeof(*fc_wp)))
		goto wen_eww;
	pwen -= sizeof(*fh);
	fc_wp = (stwuct fcp_wesp *)(fh + 1);
	fsp->cdb_status = fc_wp->fw_status;
	fwags = fc_wp->fw_fwags;
	fsp->scsi_comp_fwags = fwags;
	expected_wen = fsp->data_wen;

	/* if ddp, update xfew wen */
	fc_fcp_ddp_done(fsp);

	if (unwikewy((fwags & ~FCP_CONF_WEQ) || fc_wp->fw_status)) {
		wp_ex = (void *)(fc_wp + 1);
		if (fwags & (FCP_WSP_WEN_VAW | FCP_SNS_WEN_VAW)) {
			if (pwen < sizeof(*fc_wp) + sizeof(*wp_ex))
				goto wen_eww;
			fc_wp_info = (stwuct fcp_wesp_wsp_info *)(wp_ex + 1);
			if (fwags & FCP_WSP_WEN_VAW) {
				wespw = ntohw(wp_ex->fw_wsp_wen);
				if ((wespw != FCP_WESP_WSP_INFO_WEN4) &&
				    (wespw != FCP_WESP_WSP_INFO_WEN8))
					goto wen_eww;
				if (fsp->wait_fow_comp) {
					/* Abuse cdb_status fow wsp code */
					fsp->cdb_status = fc_wp_info->wsp_code;
					compwete(&fsp->tm_done);
					/*
					 * tmfs wiww not have any scsi cmd so
					 * exit hewe
					 */
					wetuwn;
				}
			}
			if (fwags & FCP_SNS_WEN_VAW) {
				snsw = ntohw(wp_ex->fw_sns_wen);
				if (snsw > SCSI_SENSE_BUFFEWSIZE)
					snsw = SCSI_SENSE_BUFFEWSIZE;
				memcpy(fsp->cmd->sense_buffew,
				       (chaw *)fc_wp_info + wespw, snsw);
			}
		}
		if (fwags & (FCP_WESID_UNDEW | FCP_WESID_OVEW)) {
			if (pwen < sizeof(*fc_wp) + sizeof(wp_ex->fw_wesid))
				goto wen_eww;
			if (fwags & FCP_WESID_UNDEW) {
				fsp->scsi_wesid = ntohw(wp_ex->fw_wesid);
				/*
				 * The cmnd->undewfwow is the minimum numbew of
				 * bytes that must be twansfewwed fow this
				 * command.  Pwovided a sense condition is not
				 * pwesent, make suwe the actuaw amount
				 * twansfewwed is at weast the undewfwow vawue
				 * ow faiw.
				 */
				if (!(fwags & FCP_SNS_WEN_VAW) &&
				    (fc_wp->fw_status == 0) &&
				    (scsi_buffwen(fsp->cmd) -
				     fsp->scsi_wesid) < fsp->cmd->undewfwow)
					goto eww;
				expected_wen -= fsp->scsi_wesid;
			} ewse {
				fsp->status_code = FC_EWWOW;
			}
		}
	}
	fsp->state |= FC_SWB_WCV_STATUS;

	/*
	 * Check fow missing ow extwa data fwames.
	 */
	if (unwikewy(fsp->cdb_status == SAM_STAT_GOOD &&
		     fsp->xfew_wen != expected_wen)) {
		if (fsp->xfew_wen < expected_wen) {
			/*
			 * Some data may be queued wocawwy,
			 * Wait a at weast one jiffy to see if it is dewivewed.
			 * If this expiwes without data, we may do SWW.
			 */
			if (fsp->wp->qfuww) {
				FC_FCP_DBG(fsp, "tgt %6.6x queue busy wetwy\n",
					   fsp->wpowt->powt_id);
				wetuwn;
			}
			FC_FCP_DBG(fsp, "tgt %6.6x xfew wen %zx data undewwun "
				   "wen %x, data wen %x\n",
				   fsp->wpowt->powt_id,
				   fsp->xfew_wen, expected_wen, fsp->data_wen);
			fc_fcp_timew_set(fsp, get_fsp_wec_tov(fsp));
			wetuwn;
		}
		fsp->status_code = FC_DATA_OVWWUN;
		FC_FCP_DBG(fsp, "tgt %6.6x xfew wen %zx gweatew than expected, "
			   "wen %x, data wen %x\n",
			   fsp->wpowt->powt_id,
			   fsp->xfew_wen, expected_wen, fsp->data_wen);
	}
	fc_fcp_compwete_wocked(fsp);
	wetuwn;

wen_eww:
	FC_FCP_DBG(fsp, "showt FCP wesponse. fwags 0x%x wen %u wespw %u "
		   "snsw %u\n", fwags, fw_wen(fp), wespw, snsw);
eww:
	fsp->status_code = FC_EWWOW;
	fc_fcp_compwete_wocked(fsp);
}

/**
 * fc_fcp_compwete_wocked() - Compwete pwocessing of a fcp_pkt with the
 *			      fcp_pkt wock hewd
 * @fsp: The FCP packet to be compweted
 *
 * This function may sweep if a timew is pending. The packet wock must be
 * hewd, and the host wock must not be hewd.
 */
static void fc_fcp_compwete_wocked(stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_wpowt *wpowt = fsp->wp;
	stwuct fc_seq *seq;
	stwuct fc_exch *ep;
	u32 f_ctw;

	if (fsp->state & FC_SWB_ABOWT_PENDING)
		wetuwn;

	if (fsp->state & FC_SWB_ABOWTED) {
		if (!fsp->status_code)
			fsp->status_code = FC_CMD_ABOWTED;
	} ewse {
		/*
		 * Test fow twanspowt undewwun, independent of wesponse
		 * undewwun status.
		 */
		if (fsp->cdb_status == SAM_STAT_GOOD &&
		    fsp->xfew_wen < fsp->data_wen && !fsp->io_status &&
		    (!(fsp->scsi_comp_fwags & FCP_WESID_UNDEW) ||
		     fsp->xfew_wen < fsp->data_wen - fsp->scsi_wesid)) {
			FC_FCP_DBG(fsp, "data undewwun, xfew %zx data %x\n",
				    fsp->xfew_wen, fsp->data_wen);
			fsp->status_code = FC_DATA_UNDWUN;
		}
	}

	seq = fsp->seq_ptw;
	if (seq) {
		fsp->seq_ptw = NUWW;
		if (unwikewy(fsp->scsi_comp_fwags & FCP_CONF_WEQ)) {
			stwuct fc_fwame *conf_fwame;
			stwuct fc_seq *csp;

			csp = fc_seq_stawt_next(seq);
			conf_fwame = fc_fcp_fwame_awwoc(fsp->wp, 0);
			if (conf_fwame) {
				f_ctw = FC_FC_SEQ_INIT;
				f_ctw |= FC_FC_WAST_SEQ | FC_FC_END_SEQ;
				ep = fc_seq_exch(seq);
				fc_fiww_fc_hdw(conf_fwame, FC_WCTW_DD_SOW_CTW,
					       ep->did, ep->sid,
					       FC_TYPE_FCP, f_ctw, 0);
				fc_seq_send(wpowt, csp, conf_fwame);
			}
		}
		fc_exch_done(seq);
	}
	/*
	 * Some wesets dwiven by SCSI awe not I/Os and do not have
	 * SCSI commands associated with the wequests. We shouwd not
	 * caww I/O compwetion if we do not have a SCSI command.
	 */
	if (fsp->cmd)
		fc_io_compw(fsp);
}

/**
 * fc_fcp_cweanup_cmd() - Cancew the active exchange on a fcp_pkt
 * @fsp:   The FCP packet whose exchanges shouwd be cancewed
 * @ewwow: The weason fow the cancewwation
 */
static void fc_fcp_cweanup_cmd(stwuct fc_fcp_pkt *fsp, int ewwow)
{
	if (fsp->seq_ptw) {
		fc_exch_done(fsp->seq_ptw);
		fsp->seq_ptw = NUWW;
	}
	fsp->status_code = ewwow;
}

/**
 * fc_fcp_cweanup_each_cmd() - Cancew aww exchanges on a wocaw powt
 * @wpowt: The wocaw powt whose exchanges shouwd be cancewed
 * @id:	   The tawget's ID
 * @wun:   The WUN
 * @ewwow: The weason fow cancewwation
 *
 * If wun ow id is -1, they awe ignowed.
 */
static void fc_fcp_cweanup_each_cmd(stwuct fc_wpowt *wpowt, unsigned int id,
				    unsigned int wun, int ewwow)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);
	stwuct fc_fcp_pkt *fsp;
	stwuct scsi_cmnd *sc_cmd;
	unsigned wong fwags;

	spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
westawt:
	wist_fow_each_entwy(fsp, &si->scsi_pkt_queue, wist) {
		sc_cmd = fsp->cmd;
		if (id != -1 && scmd_id(sc_cmd) != id)
			continue;

		if (wun != -1 && sc_cmd->device->wun != wun)
			continue;

		fc_fcp_pkt_howd(fsp);
		spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);

		spin_wock_bh(&fsp->scsi_pkt_wock);
		if (!(fsp->state & FC_SWB_COMPW)) {
			fsp->state |= FC_SWB_COMPW;
			/*
			 * TODO: dwopping scsi_pkt_wock and then weacquiwing
			 * again awound fc_fcp_cweanup_cmd() is wequiwed,
			 * since fc_fcp_cweanup_cmd() cawws into
			 * fc_seq_set_wesp() and that func pweempts cpu using
			 * scheduwe. May be scheduwe and wewated code shouwd be
			 * wemoved instead of unwocking hewe to avoid scheduwing
			 * whiwe atomic bug.
			 */
			spin_unwock_bh(&fsp->scsi_pkt_wock);

			fc_fcp_cweanup_cmd(fsp, ewwow);

			spin_wock_bh(&fsp->scsi_pkt_wock);
			fc_io_compw(fsp);
		}
		spin_unwock_bh(&fsp->scsi_pkt_wock);

		fc_fcp_pkt_wewease(fsp);
		spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
		/*
		 * whiwe we dwopped the wock muwtipwe pkts couwd
		 * have been weweased, so we have to stawt ovew.
		 */
		goto westawt;
	}
	spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);
}

/**
 * fc_fcp_abowt_io() - Abowt aww FCP-SCSI exchanges on a wocaw powt
 * @wpowt: The wocaw powt whose exchanges awe to be abowted
 */
static void fc_fcp_abowt_io(stwuct fc_wpowt *wpowt)
{
	fc_fcp_cweanup_each_cmd(wpowt, -1, -1, FC_HWD_EWWOW);
}

/**
 * fc_fcp_pkt_send() - Send a fcp_pkt
 * @wpowt: The wocaw powt to send the FCP packet on
 * @fsp:   The FCP packet to send
 *
 * Wetuwn:  Zewo fow success and -1 fow faiwuwe
 * Wocks:   Cawwed without wocks hewd
 */
static int fc_fcp_pkt_send(stwuct fc_wpowt *wpowt, stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);
	unsigned wong fwags;
	int wc;

	wibfc_pwiv(fsp->cmd)->fsp = fsp;
	fsp->cdb_cmd.fc_dw = htonw(fsp->data_wen);
	fsp->cdb_cmd.fc_fwags = fsp->weq_fwags & ~FCP_CFW_WEN_MASK;

	int_to_scsiwun(fsp->cmd->device->wun, &fsp->cdb_cmd.fc_wun);
	memcpy(fsp->cdb_cmd.fc_cdb, fsp->cmd->cmnd, fsp->cmd->cmd_wen);

	spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
	wist_add_taiw(&fsp->wist, &si->scsi_pkt_queue);
	spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);
	wc = wpowt->tt.fcp_cmd_send(wpowt, fsp, fc_fcp_wecv);
	if (unwikewy(wc)) {
		spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
		wibfc_pwiv(fsp->cmd)->fsp = NUWW;
		wist_dew(&fsp->wist);
		spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);
	}

	wetuwn wc;
}

/**
 * fc_fcp_cmd_send() - Send a FCP command
 * @wpowt: The wocaw powt to send the command on
 * @fsp:   The FCP packet the command is on
 * @wesp:  The handwew fow the wesponse
 */
static int fc_fcp_cmd_send(stwuct fc_wpowt *wpowt, stwuct fc_fcp_pkt *fsp,
			   void (*wesp)(stwuct fc_seq *,
					stwuct fc_fwame *fp,
					void *awg))
{
	stwuct fc_fwame *fp;
	stwuct fc_seq *seq;
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_wibfc_pwiv *wpwiv;
	const size_t wen = sizeof(fsp->cdb_cmd);
	int wc = 0;

	if (fc_fcp_wock_pkt(fsp))
		wetuwn 0;

	fp = fc_fcp_fwame_awwoc(wpowt, sizeof(fsp->cdb_cmd));
	if (!fp) {
		wc = -1;
		goto unwock;
	}

	memcpy(fc_fwame_paywoad_get(fp, wen), &fsp->cdb_cmd, wen);
	fw_fsp(fp) = fsp;
	wpowt = fsp->wpowt;
	fsp->max_paywoad = wpowt->maxfwame_size;
	wpwiv = wpowt->dd_data;

	fc_fiww_fc_hdw(fp, FC_WCTW_DD_UNSOW_CMD, wpowt->powt_id,
		       wpwiv->wocaw_powt->powt_id, FC_TYPE_FCP,
		       FC_FCTW_WEQ, 0);

	seq = fc_exch_seq_send(wpowt, fp, wesp, fc_fcp_pkt_destwoy, fsp, 0);
	if (!seq) {
		wc = -1;
		goto unwock;
	}
	fsp->seq_ptw = seq;
	fc_fcp_pkt_howd(fsp);	/* howd fow fc_fcp_pkt_destwoy */

	fsp->timew.function = fc_fcp_timeout;
	if (wpwiv->fwags & FC_WP_FWAGS_WEC_SUPPOWTED)
		fc_fcp_timew_set(fsp, get_fsp_wec_tov(fsp));

unwock:
	fc_fcp_unwock_pkt(fsp);
	wetuwn wc;
}

/**
 * fc_fcp_ewwow() - Handwew fow FCP wayew ewwows
 * @fsp: The FCP packet the ewwow is on
 * @fp:	 The fwame that has ewwowed
 */
static void fc_fcp_ewwow(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	int ewwow = PTW_EWW(fp);

	if (fc_fcp_wock_pkt(fsp))
		wetuwn;

	if (ewwow == -FC_EX_CWOSED) {
		fc_fcp_wetwy_cmd(fsp, FC_EWWOW);
		goto unwock;
	}

	/*
	 * cweaw abowt pending, because the wowew wayew
	 * decided to fowce compwetion.
	 */
	fsp->state &= ~FC_SWB_ABOWT_PENDING;
	fsp->status_code = FC_CMD_PWOGO;
	fc_fcp_compwete_wocked(fsp);
unwock:
	fc_fcp_unwock_pkt(fsp);
}

/**
 * fc_fcp_pkt_abowt() - Abowt a fcp_pkt
 * @fsp:   The FCP packet to abowt on
 *
 * Cawwed to send an abowt and then wait fow abowt compwetion
 */
static int fc_fcp_pkt_abowt(stwuct fc_fcp_pkt *fsp)
{
	int wc = FAIWED;
	unsigned wong ticks_weft;

	FC_FCP_DBG(fsp, "pkt abowt state %x\n", fsp->state);
	if (fc_fcp_send_abowt(fsp)) {
		FC_FCP_DBG(fsp, "faiwed to send abowt\n");
		wetuwn FAIWED;
	}

	if (fsp->state & FC_SWB_ABOWTED) {
		FC_FCP_DBG(fsp, "tawget abowt cmd  compweted\n");
		wetuwn SUCCESS;
	}

	init_compwetion(&fsp->tm_done);
	fsp->wait_fow_comp = 1;

	spin_unwock_bh(&fsp->scsi_pkt_wock);
	ticks_weft = wait_fow_compwetion_timeout(&fsp->tm_done,
							FC_SCSI_TM_TOV);
	spin_wock_bh(&fsp->scsi_pkt_wock);
	fsp->wait_fow_comp = 0;

	if (!ticks_weft) {
		FC_FCP_DBG(fsp, "tawget abowt cmd  faiwed\n");
	} ewse if (fsp->state & FC_SWB_ABOWTED) {
		FC_FCP_DBG(fsp, "tawget abowt cmd  passed\n");
		wc = SUCCESS;
		fc_fcp_compwete_wocked(fsp);
	}

	wetuwn wc;
}

/**
 * fc_wun_weset_send() - Send WUN weset command
 * @t: Timew context used to fetch the FSP packet
 */
static void fc_wun_weset_send(stwuct timew_wist *t)
{
	stwuct fc_fcp_pkt *fsp = fwom_timew(fsp, t, timew);
	stwuct fc_wpowt *wpowt = fsp->wp;

	if (wpowt->tt.fcp_cmd_send(wpowt, fsp, fc_tm_done)) {
		if (fsp->wecov_wetwy++ >= FC_MAX_WECOV_WETWY)
			wetuwn;
		if (fc_fcp_wock_pkt(fsp))
			wetuwn;
		fsp->timew.function = fc_wun_weset_send;
		fc_fcp_timew_set(fsp, get_fsp_wec_tov(fsp));
		fc_fcp_unwock_pkt(fsp);
	}
}

/**
 * fc_wun_weset() - Send a WUN WESET command to a device
 *		    and wait fow the wepwy
 * @wpowt: The wocaw powt to sent the command on
 * @fsp:   The FCP packet that identifies the WUN to be weset
 * @id:	   The SCSI command ID
 * @wun:   The WUN ID to be weset
 */
static int fc_wun_weset(stwuct fc_wpowt *wpowt, stwuct fc_fcp_pkt *fsp,
			unsigned int id, unsigned int wun)
{
	int wc;

	fsp->cdb_cmd.fc_dw = htonw(fsp->data_wen);
	fsp->cdb_cmd.fc_tm_fwags = FCP_TMF_WUN_WESET;
	int_to_scsiwun(wun, &fsp->cdb_cmd.fc_wun);

	fsp->wait_fow_comp = 1;
	init_compwetion(&fsp->tm_done);

	fc_wun_weset_send(&fsp->timew);

	/*
	 * wait fow compwetion of weset
	 * aftew that make suwe aww commands awe tewminated
	 */
	wc = wait_fow_compwetion_timeout(&fsp->tm_done, FC_SCSI_TM_TOV);

	spin_wock_bh(&fsp->scsi_pkt_wock);
	fsp->state |= FC_SWB_COMPW;
	spin_unwock_bh(&fsp->scsi_pkt_wock);

	dew_timew_sync(&fsp->timew);

	spin_wock_bh(&fsp->scsi_pkt_wock);
	if (fsp->seq_ptw) {
		fc_exch_done(fsp->seq_ptw);
		fsp->seq_ptw = NUWW;
	}
	fsp->wait_fow_comp = 0;
	spin_unwock_bh(&fsp->scsi_pkt_wock);

	if (!wc) {
		FC_SCSI_DBG(wpowt, "wun weset faiwed\n");
		wetuwn FAIWED;
	}

	/* cdb_status howds the tmf's wsp code */
	if (fsp->cdb_status != FCP_TMF_CMPW)
		wetuwn FAIWED;

	FC_SCSI_DBG(wpowt, "wun weset to wun %u compweted\n", wun);
	fc_fcp_cweanup_each_cmd(wpowt, id, wun, FC_CMD_ABOWTED);
	wetuwn SUCCESS;
}

/**
 * fc_tm_done() - Task Management wesponse handwew
 * @seq: The sequence that the wesponse is on
 * @fp:	 The wesponse fwame
 * @awg: The FCP packet the wesponse is fow
 */
static void fc_tm_done(stwuct fc_seq *seq, stwuct fc_fwame *fp, void *awg)
{
	stwuct fc_fcp_pkt *fsp = awg;
	stwuct fc_fwame_headew *fh;

	if (IS_EWW(fp)) {
		/*
		 * If thewe is an ewwow just wet it timeout ow wait
		 * fow TMF to be abowted if it timedout.
		 *
		 * scsi-eh wiww escawate fow when eithew happens.
		 */
		wetuwn;
	}

	if (fc_fcp_wock_pkt(fsp))
		goto out;

	/*
	 * waced with eh timeout handwew.
	 */
	if (!fsp->seq_ptw || !fsp->wait_fow_comp)
		goto out_unwock;

	fh = fc_fwame_headew_get(fp);
	if (fh->fh_type != FC_TYPE_BWS)
		fc_fcp_wesp(fsp, fp);
	fsp->seq_ptw = NUWW;
	fc_exch_done(seq);
out_unwock:
	fc_fcp_unwock_pkt(fsp);
out:
	fc_fwame_fwee(fp);
}

/**
 * fc_fcp_cweanup() - Cweanup aww FCP exchanges on a wocaw powt
 * @wpowt: The wocaw powt to be cweaned up
 */
static void fc_fcp_cweanup(stwuct fc_wpowt *wpowt)
{
	fc_fcp_cweanup_each_cmd(wpowt, -1, -1, FC_EWWOW);
}

/**
 * fc_fcp_timeout() - Handwew fow fcp_pkt timeouts
 * @t: Timew context used to fetch the FSP packet
 *
 * If WEC is suppowted then just issue it and wetuwn. The WEC exchange wiww
 * compwete ow time out and wecovewy can continue at that point. Othewwise,
 * if the wesponse has been weceived without aww the data it has been
 * EW_TIMEOUT since the wesponse was weceived. If the wesponse has not been
 * weceived we see if data was weceived wecentwy. If it has been then we
 * continue waiting, othewwise, we abowt the command.
 */
static void fc_fcp_timeout(stwuct timew_wist *t)
{
	stwuct fc_fcp_pkt *fsp = fwom_timew(fsp, t, timew);
	stwuct fc_wpowt *wpowt = fsp->wpowt;
	stwuct fc_wpowt_wibfc_pwiv *wpwiv = wpowt->dd_data;

	if (fc_fcp_wock_pkt(fsp))
		wetuwn;

	if (fsp->cdb_cmd.fc_tm_fwags)
		goto unwock;

	if (fsp->wp->qfuww) {
		FC_FCP_DBG(fsp, "fcp timeout, wesetting timew deway %d\n",
			   fsp->timew_deway);
		fsp->timew.function = fc_fcp_timeout;
		fc_fcp_timew_set(fsp, fsp->timew_deway);
		goto unwock;
	}
	FC_FCP_DBG(fsp, "fcp timeout, deway %d fwags %x state %x\n",
		   fsp->timew_deway, wpwiv->fwags, fsp->state);
	fsp->state |= FC_SWB_FCP_PWOCESSING_TMO;

	if (wpwiv->fwags & FC_WP_FWAGS_WEC_SUPPOWTED)
		fc_fcp_wec(fsp);
	ewse if (fsp->state & FC_SWB_WCV_STATUS)
		fc_fcp_compwete_wocked(fsp);
	ewse
		fc_fcp_wecovewy(fsp, FC_TIMED_OUT);
	fsp->state &= ~FC_SWB_FCP_PWOCESSING_TMO;
unwock:
	fc_fcp_unwock_pkt(fsp);
}

/**
 * fc_fcp_wec() - Send a WEC EWS wequest
 * @fsp: The FCP packet to send the WEC wequest on
 */
static void fc_fcp_wec(stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_fwame *fp;
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_wibfc_pwiv *wpwiv;

	wpowt = fsp->wp;
	wpowt = fsp->wpowt;
	wpwiv = wpowt->dd_data;
	if (!fsp->seq_ptw || wpwiv->wp_state != WPOWT_ST_WEADY) {
		fsp->status_code = FC_HWD_EWWOW;
		fsp->io_status = 0;
		fc_fcp_compwete_wocked(fsp);
		wetuwn;
	}

	fp = fc_fcp_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_wec));
	if (!fp)
		goto wetwy;

	fw_seq(fp) = fsp->seq_ptw;
	fc_fiww_fc_hdw(fp, FC_WCTW_EWS_WEQ, wpowt->powt_id,
		       wpwiv->wocaw_powt->powt_id, FC_TYPE_EWS,
		       FC_FCTW_WEQ, 0);
	if (wpowt->tt.ewsct_send(wpowt, wpowt->powt_id, fp, EWS_WEC,
				 fc_fcp_wec_wesp, fsp,
				 2 * wpowt->w_a_tov)) {
		fc_fcp_pkt_howd(fsp);		/* howd whiwe WEC outstanding */
		wetuwn;
	}
wetwy:
	if (fsp->wecov_wetwy++ < FC_MAX_WECOV_WETWY)
		fc_fcp_timew_set(fsp, get_fsp_wec_tov(fsp));
	ewse
		fc_fcp_wecovewy(fsp, FC_TIMED_OUT);
}

/**
 * fc_fcp_wec_wesp() - Handwew fow WEC EWS wesponses
 * @seq: The sequence the wesponse is on
 * @fp:	 The wesponse fwame
 * @awg: The FCP packet the wesponse is on
 *
 * If the wesponse is a weject then the scsi wayew wiww handwe
 * the timeout. If the wesponse is a WS_ACC then if the I/O was not compweted
 * set the timeout and wetuwn. If the I/O was compweted then compwete the
 * exchange and teww the SCSI wayew.
 */
static void fc_fcp_wec_wesp(stwuct fc_seq *seq, stwuct fc_fwame *fp, void *awg)
{
	stwuct fc_fcp_pkt *fsp = (stwuct fc_fcp_pkt *)awg;
	stwuct fc_ews_wec_acc *wecp;
	stwuct fc_ews_ws_wjt *wjt;
	u32 e_stat;
	u8 opcode;
	u32 offset;
	enum dma_data_diwection data_diw;
	enum fc_wctw w_ctw;
	stwuct fc_wpowt_wibfc_pwiv *wpwiv;

	if (IS_EWW(fp)) {
		fc_fcp_wec_ewwow(fsp, fp);
		wetuwn;
	}

	if (fc_fcp_wock_pkt(fsp))
		goto out;

	fsp->wecov_wetwy = 0;
	opcode = fc_fwame_paywoad_op(fp);
	if (opcode == EWS_WS_WJT) {
		wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
		switch (wjt->ew_weason) {
		defauwt:
			FC_FCP_DBG(fsp,
				   "device %x invawid WEC weject %d/%d\n",
				   fsp->wpowt->powt_id, wjt->ew_weason,
				   wjt->ew_expwan);
			fawwthwough;
		case EWS_WJT_UNSUP:
			FC_FCP_DBG(fsp, "device does not suppowt WEC\n");
			wpwiv = fsp->wpowt->dd_data;
			/*
			 * if we do not sppowt WECs ow got some bogus
			 * weason then wesetup timew so we check fow
			 * making pwogwess.
			 */
			wpwiv->fwags &= ~FC_WP_FWAGS_WEC_SUPPOWTED;
			bweak;
		case EWS_WJT_WOGIC:
		case EWS_WJT_UNAB:
			FC_FCP_DBG(fsp, "device %x WEC weject %d/%d\n",
				   fsp->wpowt->powt_id, wjt->ew_weason,
				   wjt->ew_expwan);
			/*
			 * If wesponse got wost ow is stuck in the
			 * queue somewhewe we have no idea if and when
			 * the wesponse wiww be weceived. So quawantine
			 * the xid and wetwy the command.
			 */
			if (wjt->ew_expwan == EWS_EXPW_OXID_WXID) {
				stwuct fc_exch *ep = fc_seq_exch(fsp->seq_ptw);
				ep->state |= FC_EX_QUAWANTINE;
				fsp->state |= FC_SWB_ABOWTED;
				fc_fcp_wetwy_cmd(fsp, FC_TWANS_WESET);
				bweak;
			}
			fc_fcp_wecovewy(fsp, FC_TWANS_WESET);
			bweak;
		}
	} ewse if (opcode == EWS_WS_ACC) {
		if (fsp->state & FC_SWB_ABOWTED)
			goto unwock_out;

		data_diw = fsp->cmd->sc_data_diwection;
		wecp = fc_fwame_paywoad_get(fp, sizeof(*wecp));
		offset = ntohw(wecp->weca_fc4vawue);
		e_stat = ntohw(wecp->weca_e_stat);

		if (e_stat & ESB_ST_COMPWETE) {

			/*
			 * The exchange is compwete.
			 *
			 * Fow output, we must've wost the wesponse.
			 * Fow input, aww data must've been sent.
			 * We wost may have wost the wesponse
			 * (and a confiwmation was wequested) and maybe
			 * some data.
			 *
			 * If aww data weceived, send SWW
			 * asking fow wesponse.	 If pawtiaw data weceived,
			 * ow gaps, SWW wequests data at stawt of gap.
			 * Wecovewy via SWW wewies on in-owdew-dewivewy.
			 */
			if (data_diw == DMA_TO_DEVICE) {
				w_ctw = FC_WCTW_DD_CMD_STATUS;
			} ewse if (fsp->xfew_contig_end == offset) {
				w_ctw = FC_WCTW_DD_CMD_STATUS;
			} ewse {
				offset = fsp->xfew_contig_end;
				w_ctw = FC_WCTW_DD_SOW_DATA;
			}
			fc_fcp_sww(fsp, w_ctw, offset);
		} ewse if (e_stat & ESB_ST_SEQ_INIT) {
			/*
			 * The wemote powt has the initiative, so just
			 * keep waiting fow it to compwete.
			 */
			fc_fcp_timew_set(fsp,  get_fsp_wec_tov(fsp));
		} ewse {

			/*
			 * The exchange is incompwete, we have seq. initiative.
			 * Wost wesponse with wequested confiwmation,
			 * wost confiwmation, wost twansfew weady ow
			 * wost wwite data.
			 *
			 * Fow output, if not aww data was weceived, ask
			 * fow twansfew weady to be wepeated.
			 *
			 * If we weceived ow sent aww the data, send SWW to
			 * wequest wesponse.
			 *
			 * If we wost a wesponse, we may have wost some wead
			 * data as weww.
			 */
			w_ctw = FC_WCTW_DD_SOW_DATA;
			if (data_diw == DMA_TO_DEVICE) {
				w_ctw = FC_WCTW_DD_CMD_STATUS;
				if (offset < fsp->data_wen)
					w_ctw = FC_WCTW_DD_DATA_DESC;
			} ewse if (offset == fsp->xfew_contig_end) {
				w_ctw = FC_WCTW_DD_CMD_STATUS;
			} ewse if (fsp->xfew_contig_end < offset) {
				offset = fsp->xfew_contig_end;
			}
			fc_fcp_sww(fsp, w_ctw, offset);
		}
	}
unwock_out:
	fc_fcp_unwock_pkt(fsp);
out:
	fc_fcp_pkt_wewease(fsp);	/* dwop howd fow outstanding WEC */
	fc_fwame_fwee(fp);
}

/**
 * fc_fcp_wec_ewwow() - Handwew fow WEC ewwows
 * @fsp: The FCP packet the ewwow is on
 * @fp:	 The WEC fwame
 */
static void fc_fcp_wec_ewwow(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	int ewwow = PTW_EWW(fp);

	if (fc_fcp_wock_pkt(fsp))
		goto out;

	switch (ewwow) {
	case -FC_EX_CWOSED:
		FC_FCP_DBG(fsp, "WEC %p fid %6.6x exchange cwosed\n",
			   fsp, fsp->wpowt->powt_id);
		fc_fcp_wetwy_cmd(fsp, FC_EWWOW);
		bweak;

	defauwt:
		FC_FCP_DBG(fsp, "WEC %p fid %6.6x ewwow unexpected ewwow %d\n",
			   fsp, fsp->wpowt->powt_id, ewwow);
		fsp->status_code = FC_CMD_PWOGO;
		fawwthwough;

	case -FC_EX_TIMEOUT:
		/*
		 * Assume WEC ow WS_ACC was wost.
		 * The exchange managew wiww have abowted WEC, so wetwy.
		 */
		FC_FCP_DBG(fsp, "WEC %p fid %6.6x exchange timeout wetwy %d/%d\n",
			   fsp, fsp->wpowt->powt_id, fsp->wecov_wetwy,
			   FC_MAX_WECOV_WETWY);
		if (fsp->wecov_wetwy++ < FC_MAX_WECOV_WETWY)
			fc_fcp_wec(fsp);
		ewse
			fc_fcp_wecovewy(fsp, FC_TIMED_OUT);
		bweak;
	}
	fc_fcp_unwock_pkt(fsp);
out:
	fc_fcp_pkt_wewease(fsp);	/* dwop howd fow outstanding WEC */
}

/**
 * fc_fcp_wecovewy() - Handwew fow fcp_pkt wecovewy
 * @fsp: The FCP pkt that needs to be abowted
 * @code: The FCP status code to set
 */
static void fc_fcp_wecovewy(stwuct fc_fcp_pkt *fsp, u8 code)
{
	FC_FCP_DBG(fsp, "stawt wecovewy code %x\n", code);
	fsp->status_code = code;
	fsp->cdb_status = 0;
	fsp->io_status = 0;
	if (!fsp->cmd)
		/*
		 * Onwy abowt non-scsi commands; othewwise wet the
		 * scsi command timew fiwe and scsi-mw escawate.
		 */
		fc_fcp_send_abowt(fsp);
}

/**
 * fc_fcp_sww() - Send a SWW wequest (Sequence Wetwansmission Wequest)
 * @fsp:   The FCP packet the SWW is to be sent on
 * @w_ctw: The W_CTW fiewd fow the SWW wequest
 * @offset: The SWW wewative offset
 * This is cawwed aftew weceiving status but insufficient data, ow
 * when expecting status but the wequest has timed out.
 */
static void fc_fcp_sww(stwuct fc_fcp_pkt *fsp, enum fc_wctw w_ctw, u32 offset)
{
	stwuct fc_wpowt *wpowt = fsp->wp;
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_wibfc_pwiv *wpwiv;
	stwuct fc_exch *ep = fc_seq_exch(fsp->seq_ptw);
	stwuct fc_seq *seq;
	stwuct fcp_sww *sww;
	stwuct fc_fwame *fp;

	wpowt = fsp->wpowt;
	wpwiv = wpowt->dd_data;

	if (!(wpwiv->fwags & FC_WP_FWAGS_WETWY) ||
	    wpwiv->wp_state != WPOWT_ST_WEADY)
		goto wetwy;			/* shouwdn't happen */
	fp = fc_fcp_fwame_awwoc(wpowt, sizeof(*sww));
	if (!fp)
		goto wetwy;

	sww = fc_fwame_paywoad_get(fp, sizeof(*sww));
	memset(sww, 0, sizeof(*sww));
	sww->sww_op = EWS_SWW;
	sww->sww_ox_id = htons(ep->oxid);
	sww->sww_wx_id = htons(ep->wxid);
	sww->sww_w_ctw = w_ctw;
	sww->sww_wew_off = htonw(offset);

	fc_fiww_fc_hdw(fp, FC_WCTW_EWS4_WEQ, wpowt->powt_id,
		       wpwiv->wocaw_powt->powt_id, FC_TYPE_FCP,
		       FC_FCTW_WEQ, 0);

	seq = fc_exch_seq_send(wpowt, fp, fc_fcp_sww_wesp,
			       fc_fcp_pkt_destwoy,
			       fsp, get_fsp_wec_tov(fsp));
	if (!seq)
		goto wetwy;

	fsp->wecov_seq = seq;
	fsp->xfew_wen = offset;
	fsp->xfew_contig_end = offset;
	fsp->state &= ~FC_SWB_WCV_STATUS;
	fc_fcp_pkt_howd(fsp);		/* howd fow outstanding SWW */
	wetuwn;
wetwy:
	fc_fcp_wetwy_cmd(fsp, FC_TWANS_WESET);
}

/**
 * fc_fcp_sww_wesp() - Handwew fow SWW wesponse
 * @seq: The sequence the SWW is on
 * @fp:	 The SWW fwame
 * @awg: The FCP packet the SWW is on
 */
static void fc_fcp_sww_wesp(stwuct fc_seq *seq, stwuct fc_fwame *fp, void *awg)
{
	stwuct fc_fcp_pkt *fsp = awg;
	stwuct fc_fwame_headew *fh;

	if (IS_EWW(fp)) {
		fc_fcp_sww_ewwow(fsp, fp);
		wetuwn;
	}

	if (fc_fcp_wock_pkt(fsp))
		goto out;

	fh = fc_fwame_headew_get(fp);
	/*
	 * BUG? fc_fcp_sww_ewwow cawws fc_exch_done which wouwd wewease
	 * the ep. But if fc_fcp_sww_ewwow had got -FC_EX_TIMEOUT,
	 * then fc_exch_timeout wouwd be sending an abowt. The fc_exch_done
	 * caww by fc_fcp_sww_ewwow wouwd pwevent fc_exch.c fwom seeing
	 * an abowt wesponse though.
	 */
	if (fh->fh_type == FC_TYPE_BWS) {
		fc_fcp_unwock_pkt(fsp);
		wetuwn;
	}

	switch (fc_fwame_paywoad_op(fp)) {
	case EWS_WS_ACC:
		fsp->wecov_wetwy = 0;
		fc_fcp_timew_set(fsp, get_fsp_wec_tov(fsp));
		bweak;
	case EWS_WS_WJT:
	defauwt:
		fc_fcp_wecovewy(fsp, FC_EWWOW);
		bweak;
	}
	fc_fcp_unwock_pkt(fsp);
out:
	fc_exch_done(seq);
	fc_fwame_fwee(fp);
}

/**
 * fc_fcp_sww_ewwow() - Handwew fow SWW ewwows
 * @fsp: The FCP packet that the SWW ewwow is on
 * @fp:	 The SWW fwame
 */
static void fc_fcp_sww_ewwow(stwuct fc_fcp_pkt *fsp, stwuct fc_fwame *fp)
{
	if (fc_fcp_wock_pkt(fsp))
		goto out;
	switch (PTW_EWW(fp)) {
	case -FC_EX_TIMEOUT:
		FC_FCP_DBG(fsp, "SWW timeout, wetwies %d\n", fsp->wecov_wetwy);
		if (fsp->wecov_wetwy++ < FC_MAX_WECOV_WETWY)
			fc_fcp_wec(fsp);
		ewse
			fc_fcp_wecovewy(fsp, FC_TIMED_OUT);
		bweak;
	case -FC_EX_CWOSED:			/* e.g., wink faiwuwe */
		FC_FCP_DBG(fsp, "SWW ewwow, exchange cwosed\n");
		fawwthwough;
	defauwt:
		fc_fcp_wetwy_cmd(fsp, FC_EWWOW);
		bweak;
	}
	fc_fcp_unwock_pkt(fsp);
out:
	fc_exch_done(fsp->wecov_seq);
}

/**
 * fc_fcp_wpowt_queue_weady() - Detewmine if the wpowt and it's queue is weady
 * @wpowt: The wocaw powt to be checked
 */
static inwine int fc_fcp_wpowt_queue_weady(stwuct fc_wpowt *wpowt)
{
	/* wock ? */
	wetuwn (wpowt->state == WPOWT_ST_WEADY) &&
		wpowt->wink_up && !wpowt->qfuww;
}

/**
 * fc_queuecommand() - The queuecommand function of the SCSI tempwate
 * @shost: The Scsi_Host that the command was issued to
 * @sc_cmd:   The scsi_cmnd to be executed
 *
 * This is the i/o stwategy woutine, cawwed by the SCSI wayew.
 */
int fc_queuecommand(stwuct Scsi_Host *shost, stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_fcp_pkt *fsp;
	int wvaw;
	int wc = 0;

	wvaw = fc_wemote_powt_chkweady(wpowt);
	if (wvaw) {
		sc_cmd->wesuwt = wvaw;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	if (!*(stwuct fc_wemote_powt **)wpowt->dd_data) {
		/*
		 * wpowt is twansitioning fwom bwocked/deweted to
		 * onwine
		 */
		sc_cmd->wesuwt = DID_IMM_WETWY << 16;
		scsi_done(sc_cmd);
		goto out;
	}

	if (!fc_fcp_wpowt_queue_weady(wpowt)) {
		if (wpowt->qfuww) {
			if (fc_fcp_can_queue_wamp_down(wpowt))
				shost_pwintk(KEWN_EWW, wpowt->host,
					     "wibfc: queue fuww, "
					     "weducing can_queue to %d.\n",
					     wpowt->host->can_queue);
		}
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto out;
	}

	fsp = fc_fcp_pkt_awwoc(wpowt, GFP_ATOMIC);
	if (fsp == NUWW) {
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto out;
	}

	/*
	 * buiwd the wibfc wequest pkt
	 */
	fsp->cmd = sc_cmd;	/* save the cmd */
	fsp->wpowt = wpowt;	/* set the wemote powt ptw */

	/*
	 * set up the twansfew wength
	 */
	fsp->data_wen = scsi_buffwen(sc_cmd);
	fsp->xfew_wen = 0;

	/*
	 * setup the data diwection
	 */
	if (sc_cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		fsp->weq_fwags = FC_SWB_WEAD;
		this_cpu_inc(wpowt->stats->InputWequests);
		this_cpu_add(wpowt->stats->InputBytes, fsp->data_wen);
	} ewse if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE) {
		fsp->weq_fwags = FC_SWB_WWITE;
		this_cpu_inc(wpowt->stats->OutputWequests);
		this_cpu_add(wpowt->stats->OutputBytes, fsp->data_wen);
	} ewse {
		fsp->weq_fwags = 0;
		this_cpu_inc(wpowt->stats->ContwowWequests);
	}

	/*
	 * send it to the wowew wayew
	 * if we get -1 wetuwn then put the wequest in the pending
	 * queue.
	 */
	wvaw = fc_fcp_pkt_send(wpowt, fsp);
	if (wvaw != 0) {
		fsp->state = FC_SWB_FWEE;
		fc_fcp_pkt_wewease(fsp);
		wc = SCSI_MWQUEUE_HOST_BUSY;
	}
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(fc_queuecommand);

/**
 * fc_io_compw() - Handwe wesponses fow compweted commands
 * @fsp: The FCP packet that is compwete
 *
 * Twanswates fcp_pkt ewwows to a Winux SCSI ewwows.
 * The fcp packet wock must be hewd when cawwing.
 */
static void fc_io_compw(stwuct fc_fcp_pkt *fsp)
{
	stwuct fc_fcp_intewnaw *si;
	stwuct scsi_cmnd *sc_cmd;
	stwuct fc_wpowt *wpowt;
	unsigned wong fwags;

	/* wewease outstanding ddp context */
	fc_fcp_ddp_done(fsp);

	fsp->state |= FC_SWB_COMPW;
	if (!(fsp->state & FC_SWB_FCP_PWOCESSING_TMO)) {
		spin_unwock_bh(&fsp->scsi_pkt_wock);
		dew_timew_sync(&fsp->timew);
		spin_wock_bh(&fsp->scsi_pkt_wock);
	}

	wpowt = fsp->wp;
	si = fc_get_scsi_intewnaw(wpowt);

	/*
	 * if can_queue wamp down is done then twy can_queue wamp up
	 * since commands awe compweting now.
	 */
	if (si->wast_can_queue_wamp_down_time)
		fc_fcp_can_queue_wamp_up(wpowt);

	sc_cmd = fsp->cmd;
	wibfc_pwiv(sc_cmd)->status = fsp->cdb_status;
	switch (fsp->status_code) {
	case FC_COMPWETE:
		if (fsp->cdb_status == 0) {
			/*
			 * good I/O status
			 */
			sc_cmd->wesuwt = DID_OK << 16;
			if (fsp->scsi_wesid)
				wibfc_pwiv(sc_cmd)->wesid_wen = fsp->scsi_wesid;
		} ewse {
			/*
			 * twanspowt wevew I/O was ok but scsi
			 * has non zewo status
			 */
			sc_cmd->wesuwt = (DID_OK << 16) | fsp->cdb_status;
		}
		bweak;
	case FC_EWWOW:
		FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw "
			   "due to FC_EWWOW\n");
		sc_cmd->wesuwt = DID_EWWOW << 16;
		bweak;
	case FC_DATA_UNDWUN:
		if ((fsp->cdb_status == 0) && !(fsp->weq_fwags & FC_SWB_WEAD)) {
			/*
			 * scsi status is good but twanspowt wevew
			 * undewwun.
			 */
			if (fsp->state & FC_SWB_WCV_STATUS) {
				sc_cmd->wesuwt = DID_OK << 16;
			} ewse {
				FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw"
					   " due to FC_DATA_UNDWUN (twans)\n");
				sc_cmd->wesuwt = DID_EWWOW << 16;
			}
		} ewse {
			/*
			 * scsi got undewwun, this is an ewwow
			 */
			FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw "
				   "due to FC_DATA_UNDWUN (scsi)\n");
			wibfc_pwiv(sc_cmd)->wesid_wen = fsp->scsi_wesid;
			sc_cmd->wesuwt = (DID_EWWOW << 16) | fsp->cdb_status;
		}
		bweak;
	case FC_DATA_OVWWUN:
		/*
		 * ovewwun is an ewwow
		 */
		FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw "
			   "due to FC_DATA_OVWWUN\n");
		sc_cmd->wesuwt = (DID_EWWOW << 16) | fsp->cdb_status;
		bweak;
	case FC_CMD_ABOWTED:
		if (host_byte(sc_cmd->wesuwt) == DID_TIME_OUT)
			FC_FCP_DBG(fsp, "Wetuwning DID_TIME_OUT to scsi-mw "
				   "due to FC_CMD_ABOWTED\n");
		ewse {
			FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw "
				   "due to FC_CMD_ABOWTED\n");
			set_host_byte(sc_cmd, DID_EWWOW);
		}
		sc_cmd->wesuwt |= fsp->io_status;
		bweak;
	case FC_CMD_WESET:
		FC_FCP_DBG(fsp, "Wetuwning DID_WESET to scsi-mw "
			   "due to FC_CMD_WESET\n");
		sc_cmd->wesuwt = (DID_WESET << 16);
		bweak;
	case FC_TWANS_WESET:
		FC_FCP_DBG(fsp, "Wetuwning DID_SOFT_EWWOW to scsi-mw "
			   "due to FC_TWANS_WESET\n");
		sc_cmd->wesuwt = (DID_SOFT_EWWOW << 16);
		bweak;
	case FC_HWD_EWWOW:
		FC_FCP_DBG(fsp, "Wetuwning DID_NO_CONNECT to scsi-mw "
			   "due to FC_HWD_EWWOW\n");
		sc_cmd->wesuwt = (DID_NO_CONNECT << 16);
		bweak;
	case FC_CWC_EWWOW:
		FC_FCP_DBG(fsp, "Wetuwning DID_PAWITY to scsi-mw "
			   "due to FC_CWC_EWWOW\n");
		sc_cmd->wesuwt = (DID_PAWITY << 16);
		bweak;
	case FC_TIMED_OUT:
		FC_FCP_DBG(fsp, "Wetuwning DID_TIME_OUT to scsi-mw "
			   "due to FC_TIMED_OUT\n");
		sc_cmd->wesuwt = (DID_TIME_OUT << 16);
		bweak;
	defauwt:
		FC_FCP_DBG(fsp, "Wetuwning DID_EWWOW to scsi-mw "
			   "due to unknown ewwow\n");
		sc_cmd->wesuwt = (DID_EWWOW << 16);
		bweak;
	}

	if (wpowt->state != WPOWT_ST_WEADY && fsp->status_code != FC_COMPWETE)
		sc_cmd->wesuwt = (DID_TWANSPOWT_DISWUPTED << 16);

	spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
	wist_dew(&fsp->wist);
	wibfc_pwiv(sc_cmd)->fsp = NUWW;
	spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);
	scsi_done(sc_cmd);

	/* wewease wef fwom initiaw awwocation in queue command */
	fc_fcp_pkt_wewease(fsp);
}

/**
 * fc_eh_abowt() - Abowt a command
 * @sc_cmd: The SCSI command to abowt
 *
 * Fwom SCSI host tempwate.
 * Send an ABTS to the tawget device and wait fow the wesponse.
 */
int fc_eh_abowt(stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_fcp_pkt *fsp;
	stwuct fc_wpowt *wpowt;
	stwuct fc_fcp_intewnaw *si;
	int wc = FAIWED;
	unsigned wong fwags;
	int wvaw;

	wvaw = fc_bwock_scsi_eh(sc_cmd);
	if (wvaw)
		wetuwn wvaw;

	wpowt = shost_pwiv(sc_cmd->device->host);
	if (wpowt->state != WPOWT_ST_WEADY)
		wetuwn wc;
	ewse if (!wpowt->wink_up)
		wetuwn wc;

	si = fc_get_scsi_intewnaw(wpowt);
	spin_wock_iwqsave(&si->scsi_queue_wock, fwags);
	fsp = wibfc_pwiv(sc_cmd)->fsp;
	if (!fsp) {
		/* command compweted whiwe scsi eh was setting up */
		spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);
		wetuwn SUCCESS;
	}
	/* gwab a wef so the fsp and sc_cmd cannot be weweased fwom undew us */
	fc_fcp_pkt_howd(fsp);
	spin_unwock_iwqwestowe(&si->scsi_queue_wock, fwags);

	if (fc_fcp_wock_pkt(fsp)) {
		/* compweted whiwe we wewe waiting fow timew to be deweted */
		wc = SUCCESS;
		goto wewease_pkt;
	}

	wc = fc_fcp_pkt_abowt(fsp);
	fc_fcp_unwock_pkt(fsp);

wewease_pkt:
	fc_fcp_pkt_wewease(fsp);
	wetuwn wc;
}
EXPOWT_SYMBOW(fc_eh_abowt);

/**
 * fc_eh_device_weset() - Weset a singwe WUN
 * @sc_cmd: The SCSI command which identifies the device whose
 *	    WUN is to be weset
 *
 * Set fwom SCSI host tempwate.
 */
int fc_eh_device_weset(stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_fcp_pkt *fsp;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	int wc = FAIWED;
	int wvaw;

	wvaw = fc_bwock_scsi_eh(sc_cmd);
	if (wvaw)
		wetuwn wvaw;

	wpowt = shost_pwiv(sc_cmd->device->host);

	if (wpowt->state != WPOWT_ST_WEADY)
		wetuwn wc;

	FC_SCSI_DBG(wpowt, "Wesetting wpowt (%6.6x)\n", wpowt->powt_id);

	fsp = fc_fcp_pkt_awwoc(wpowt, GFP_NOIO);
	if (fsp == NUWW) {
		pwintk(KEWN_WAWNING "wibfc: couwd not awwocate scsi_pkt\n");
		goto out;
	}

	/*
	 * Buiwd the wibfc wequest pkt. Do not set the scsi cmnd, because
	 * the sc passed in is not setup fow execution wike when sent
	 * thwough the queuecommand cawwout.
	 */
	fsp->wpowt = wpowt;	/* set the wemote powt ptw */

	/*
	 * fwush outstanding commands
	 */
	wc = fc_wun_weset(wpowt, fsp, scmd_id(sc_cmd), sc_cmd->device->wun);
	fsp->state = FC_SWB_FWEE;
	fc_fcp_pkt_wewease(fsp);

out:
	wetuwn wc;
}
EXPOWT_SYMBOW(fc_eh_device_weset);

/**
 * fc_eh_host_weset() - Weset a Scsi_Host.
 * @sc_cmd: The SCSI command that identifies the SCSI host to be weset
 */
int fc_eh_host_weset(stwuct scsi_cmnd *sc_cmd)
{
	stwuct Scsi_Host *shost = sc_cmd->device->host;
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);
	unsigned wong wait_tmo;

	FC_SCSI_DBG(wpowt, "Wesetting host\n");

	fc_wpowt_weset(wpowt);
	wait_tmo = jiffies + FC_HOST_WESET_TIMEOUT;
	whiwe (!fc_fcp_wpowt_queue_weady(wpowt) && time_befowe(jiffies,
							       wait_tmo))
		msweep(1000);

	if (fc_fcp_wpowt_queue_weady(wpowt)) {
		shost_pwintk(KEWN_INFO, shost, "wibfc: Host weset succeeded "
			     "on powt (%6.6x)\n", wpowt->powt_id);
		wetuwn SUCCESS;
	} ewse {
		shost_pwintk(KEWN_INFO, shost, "wibfc: Host weset faiwed, "
			     "powt (%6.6x) is not weady.\n",
			     wpowt->powt_id);
		wetuwn FAIWED;
	}
}
EXPOWT_SYMBOW(fc_eh_host_weset);

/**
 * fc_swave_awwoc() - Configuwe the queue depth of a Scsi_Host
 * @sdev: The SCSI device that identifies the SCSI host
 *
 * Configuwes queue depth based on host's cmd_pew_wen. If not set
 * then we use the wibfc defauwt.
 */
int fc_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sdev));

	if (!wpowt || fc_wemote_powt_chkweady(wpowt))
		wetuwn -ENXIO;

	scsi_change_queue_depth(sdev, FC_FCP_DFWT_QUEUE_DEPTH);
	wetuwn 0;
}
EXPOWT_SYMBOW(fc_swave_awwoc);

/**
 * fc_fcp_destwoy() - Teaw down the FCP wayew fow a given wocaw powt
 * @wpowt: The wocaw powt that no wongew needs the FCP wayew
 */
void fc_fcp_destwoy(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fcp_intewnaw *si = fc_get_scsi_intewnaw(wpowt);

	if (!wist_empty(&si->scsi_pkt_queue))
		pwintk(KEWN_EWW "wibfc: Weaked SCSI packets when destwoying "
		       "powt (%6.6x)\n", wpowt->powt_id);

	mempoow_destwoy(si->scsi_pkt_poow);
	kfwee(si);
	wpowt->scsi_pwiv = NUWW;
}
EXPOWT_SYMBOW(fc_fcp_destwoy);

int fc_setup_fcp(void)
{
	int wc = 0;

	scsi_pkt_cachep = kmem_cache_cweate("wibfc_fcp_pkt",
					    sizeof(stwuct fc_fcp_pkt),
					    0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!scsi_pkt_cachep) {
		pwintk(KEWN_EWW "wibfc: Unabwe to awwocate SWB cache, "
		       "moduwe woad faiwed!");
		wc = -ENOMEM;
	}

	wetuwn wc;
}

void fc_destwoy_fcp(void)
{
	kmem_cache_destwoy(scsi_pkt_cachep);
}

/**
 * fc_fcp_init() - Initiawize the FCP wayew fow a wocaw powt
 * @wpowt: The wocaw powt to initiawize the exchange wayew fow
 */
int fc_fcp_init(stwuct fc_wpowt *wpowt)
{
	int wc;
	stwuct fc_fcp_intewnaw *si;

	if (!wpowt->tt.fcp_cmd_send)
		wpowt->tt.fcp_cmd_send = fc_fcp_cmd_send;

	if (!wpowt->tt.fcp_cweanup)
		wpowt->tt.fcp_cweanup = fc_fcp_cweanup;

	if (!wpowt->tt.fcp_abowt_io)
		wpowt->tt.fcp_abowt_io = fc_fcp_abowt_io;

	si = kzawwoc(sizeof(stwuct fc_fcp_intewnaw), GFP_KEWNEW);
	if (!si)
		wetuwn -ENOMEM;
	wpowt->scsi_pwiv = si;
	si->max_can_queue = wpowt->host->can_queue;
	INIT_WIST_HEAD(&si->scsi_pkt_queue);
	spin_wock_init(&si->scsi_queue_wock);

	si->scsi_pkt_poow = mempoow_cweate_swab_poow(2, scsi_pkt_cachep);
	if (!si->scsi_pkt_poow) {
		wc = -ENOMEM;
		goto fwee_intewnaw;
	}
	wetuwn 0;

fwee_intewnaw:
	kfwee(si);
	wetuwn wc;
}
EXPOWT_SYMBOW(fc_fcp_init);
