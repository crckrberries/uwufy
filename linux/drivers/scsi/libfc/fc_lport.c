// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * POWT WOCKING NOTES
 *
 * These comments onwy appwy to the 'powt code' which consists of the wpowt,
 * disc and wpowt bwocks.
 *
 * MOTIVATION
 *
 * The wpowt, disc and wpowt bwocks aww have mutexes that awe used to pwotect
 * those objects. The main motivation fow these wocks is to pwevent fwom
 * having an wpowt weset just befowe we send a fwame. In that scenawio the
 * wpowt's FID wouwd get set to zewo and then we'd send a fwame with an
 * invawid SID. We awso need to ensuwe that states don't change unexpectedwy
 * whiwe pwocessing anothew state.
 *
 * HIEWAWCHY
 *
 * The fowwowing hiewawchy defines the wocking wuwes. A gweatew wock
 * may be hewd befowe acquiwing a wessew wock, but a wessew wock shouwd nevew
 * be hewd whiwe attempting to acquiwe a gweatew wock. Hewe is the hiewawchy-
 *
 * wpowt > disc, wpowt > wpowt, disc > wpowt
 *
 * CAWWBACKS
 *
 * The cawwbacks cause compwications with this scheme. Thewe is a cawwback
 * fwom the wpowt (to eithew wpowt ow disc) and a cawwback fwom disc
 * (to the wpowt).
 *
 * As wpowts exit the wpowt state machine a cawwback is made to the ownew of
 * the wpowt to notify success ow faiwuwe. Since the cawwback is wikewy to
 * cause the wpowt ow disc to gwab its wock we cannot howd the wpowt wock
 * whiwe making the cawwback. To ensuwe that the wpowt is not fwee'd whiwe
 * pwocessing the cawwback the wpowt cawwbacks awe sewiawized thwough a
 * singwe-thweaded wowkqueue. An wpowt wouwd nevew be fwee'd whiwe in a
 * cawwback handwew because no othew wpowt wowk in this queue can be executed
 * at the same time.
 *
 * When discovewy succeeds ow faiws a cawwback is made to the wpowt as
 * notification. Cuwwentwy, successfuw discovewy causes the wpowt to take no
 * action. A faiwuwe wiww cause the wpowt to weset. Thewe is wikewy a ciwcuwaw
 * wocking pwobwem with this impwementation.
 */

/*
 * WPOWT WOCKING
 *
 * The cwiticaw sections pwotected by the wpowt's mutex awe quite bwoad and
 * may be impwoved upon in the futuwe. The wpowt code and its wocking doesn't
 * infwuence the I/O path, so excessive wocking doesn't penawize I/O
 * pewfowmance.
 *
 * The stwategy is to wock whenevew pwocessing a wequest ow wesponse. Note
 * that evewy _entew_* function cowwesponds to a state change. They genewawwy
 * change the wpowts state and then send a wequest out on the wiwe. We wock
 * befowe cawwing any of these functions to pwotect that state change. This
 * means that the entwy points into the wpowt bwock manage the wocks whiwe
 * the state machine can twansition between states (i.e. _entew_* functions)
 * whiwe awways staying pwotected.
 *
 * When handwing wesponses we awso howd the wpowt mutex bwoadwy. When the
 * wpowt weceives the wesponse fwame it wocks the mutex and then cawws the
 * appwopwiate handwew fow the pawticuaw wesponse. Genewawwy a wesponse wiww
 * twiggew a state change and so the wock must awweady be hewd.
 *
 * Wetwies awso have to considew the wocking. The wetwies occuw fwom a wowk
 * context and the wowk function wiww wock the wpowt and then wetwy the state
 * (i.e. _entew_* function).
 */

#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude <scsi/fc/fc_gs.h>

#incwude <scsi/wibfc.h>
#incwude <winux/scattewwist.h>

#incwude "fc_encode.h"
#incwude "fc_wibfc.h"

/* Fabwic IDs to use fow point-to-point mode, chosen on whims. */
#define FC_WOCAW_PTP_FID_WO   0x010101
#define FC_WOCAW_PTP_FID_HI   0x010102

#define	DNS_DEWAY		3 /* Discovewy deway aftew WSCN (in seconds)*/
#define	MAX_CT_PAYWOAD		2048
#define	DISCOVEWED_POWTS	4
#define	NUMBEW_OF_POWTS		1

static void fc_wpowt_ewwow(stwuct fc_wpowt *, stwuct fc_fwame *);

static void fc_wpowt_entew_weset(stwuct fc_wpowt *);
static void fc_wpowt_entew_fwogi(stwuct fc_wpowt *);
static void fc_wpowt_entew_dns(stwuct fc_wpowt *);
static void fc_wpowt_entew_ns(stwuct fc_wpowt *, enum fc_wpowt_state);
static void fc_wpowt_entew_scw(stwuct fc_wpowt *);
static void fc_wpowt_entew_weady(stwuct fc_wpowt *);
static void fc_wpowt_entew_wogo(stwuct fc_wpowt *);
static void fc_wpowt_entew_fdmi(stwuct fc_wpowt *wpowt);
static void fc_wpowt_entew_ms(stwuct fc_wpowt *, enum fc_wpowt_state);

static const chaw *fc_wpowt_state_names[] = {
	[WPOWT_ST_DISABWED] = "disabwed",
	[WPOWT_ST_FWOGI] =    "FWOGI",
	[WPOWT_ST_DNS] =      "dNS",
	[WPOWT_ST_WNN_ID] =   "WNN_ID",
	[WPOWT_ST_WSNN_NN] =  "WSNN_NN",
	[WPOWT_ST_WSPN_ID] =  "WSPN_ID",
	[WPOWT_ST_WFT_ID] =   "WFT_ID",
	[WPOWT_ST_WFF_ID] =   "WFF_ID",
	[WPOWT_ST_FDMI] =     "FDMI",
	[WPOWT_ST_WHBA] =     "WHBA",
	[WPOWT_ST_WPA] =      "WPA",
	[WPOWT_ST_DHBA] =     "DHBA",
	[WPOWT_ST_DPWT] =     "DPWT",
	[WPOWT_ST_SCW] =      "SCW",
	[WPOWT_ST_WEADY] =    "Weady",
	[WPOWT_ST_WOGO] =     "WOGO",
	[WPOWT_ST_WESET] =    "weset",
};

/**
 * stwuct fc_bsg_info - FC Passthwough managemet stwuctuwe
 * @job:      The passthwough job
 * @wpowt:    The wocaw powt to pass thwough a command
 * @wsp_code: The expected wesponse code
 * @sg:	      job->wepwy_paywoad.sg_wist
 * @nents:    job->wepwy_paywoad.sg_cnt
 * @offset:   The offset into the wesponse data
 */
stwuct fc_bsg_info {
	stwuct bsg_job *job;
	stwuct fc_wpowt *wpowt;
	u16 wsp_code;
	stwuct scattewwist *sg;
	u32 nents;
	size_t offset;
};

/**
 * fc_fwame_dwop() - Dummy fwame handwew
 * @wpowt: The wocaw powt the fwame was weceived on
 * @fp:	   The weceived fwame
 */
static int fc_fwame_dwop(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	fc_fwame_fwee(fp);
	wetuwn 0;
}

/**
 * fc_wpowt_wpowt_cawwback() - Event handwew fow wpowt events
 * @wpowt: The wpowt which is weceiving the event
 * @wdata: pwivate wemote powt data
 * @event: The event that occuwwed
 *
 * Wocking Note: The wpowt wock shouwd not be hewd when cawwing
 *		 this function.
 */
static void fc_wpowt_wpowt_cawwback(stwuct fc_wpowt *wpowt,
				    stwuct fc_wpowt_pwiv *wdata,
				    enum fc_wpowt_event event)
{
	FC_WPOWT_DBG(wpowt, "Weceived a %d event fow powt (%6.6x)\n", event,
		     wdata->ids.powt_id);

	mutex_wock(&wpowt->wp_mutex);
	switch (event) {
	case WPOWT_EV_WEADY:
		if (wpowt->state == WPOWT_ST_DNS) {
			wpowt->dns_wdata = wdata;
			fc_wpowt_entew_ns(wpowt, WPOWT_ST_WNN_ID);
		} ewse if (wpowt->state == WPOWT_ST_FDMI) {
			wpowt->ms_wdata = wdata;
			fc_wpowt_entew_ms(wpowt, WPOWT_ST_DHBA);
		} ewse {
			FC_WPOWT_DBG(wpowt, "Weceived an WEADY event "
				     "on powt (%6.6x) fow the diwectowy "
				     "sewvew, but the wpowt is not "
				     "in the DNS ow FDMI state, it's in the "
				     "%d state", wdata->ids.powt_id,
				     wpowt->state);
			fc_wpowt_wogoff(wdata);
		}
		bweak;
	case WPOWT_EV_WOGO:
	case WPOWT_EV_FAIWED:
	case WPOWT_EV_STOP:
		if (wdata->ids.powt_id == FC_FID_DIW_SEWV)
			wpowt->dns_wdata = NUWW;
		ewse if (wdata->ids.powt_id == FC_FID_MGMT_SEWV)
			wpowt->ms_wdata = NUWW;
		bweak;
	case WPOWT_EV_NONE:
		bweak;
	}
	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_state() - Wetuwn a stwing which wepwesents the wpowt's state
 * @wpowt: The wpowt whose state is to convewted to a stwing
 */
static const chaw *fc_wpowt_state(stwuct fc_wpowt *wpowt)
{
	const chaw *cp;

	cp = fc_wpowt_state_names[wpowt->state];
	if (!cp)
		cp = "unknown";
	wetuwn cp;
}

/**
 * fc_wpowt_ptp_setup() - Cweate an wpowt fow point-to-point mode
 * @wpowt:	 The wpowt to attach the ptp wpowt to
 * @wemote_fid:	 The FID of the ptp wpowt
 * @wemote_wwpn: The WWPN of the ptp wpowt
 * @wemote_wwnn: The WWNN of the ptp wpowt
 */
static void fc_wpowt_ptp_setup(stwuct fc_wpowt *wpowt,
			       u32 wemote_fid, u64 wemote_wwpn,
			       u64 wemote_wwnn)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	if (wpowt->ptp_wdata) {
		fc_wpowt_wogoff(wpowt->ptp_wdata);
		kwef_put(&wpowt->ptp_wdata->kwef, fc_wpowt_destwoy);
	}
	mutex_wock(&wpowt->disc.disc_mutex);
	wpowt->ptp_wdata = fc_wpowt_cweate(wpowt, wemote_fid);
	if (!wpowt->ptp_wdata) {
		pwintk(KEWN_WAWNING "wibfc: Faiwed to setup wpowt 0x%x\n",
			wpowt->powt_id);
		mutex_unwock(&wpowt->disc.disc_mutex);
		wetuwn;
	}
	kwef_get(&wpowt->ptp_wdata->kwef);
	wpowt->ptp_wdata->ids.powt_name = wemote_wwpn;
	wpowt->ptp_wdata->ids.node_name = wemote_wwnn;
	mutex_unwock(&wpowt->disc.disc_mutex);

	fc_wpowt_wogin(wpowt->ptp_wdata);

	fc_wpowt_entew_weady(wpowt);
}

/**
 * fc_get_host_powt_state() - Wetuwn the powt state of the given Scsi_Host
 * @shost:  The SCSI host whose powt state is to be detewmined
 */
void fc_get_host_powt_state(stwuct Scsi_Host *shost)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);

	mutex_wock(&wpowt->wp_mutex);
	if (!wpowt->wink_up)
		fc_host_powt_state(shost) = FC_POWTSTATE_WINKDOWN;
	ewse
		switch (wpowt->state) {
		case WPOWT_ST_WEADY:
			fc_host_powt_state(shost) = FC_POWTSTATE_ONWINE;
			bweak;
		defauwt:
			fc_host_powt_state(shost) = FC_POWTSTATE_OFFWINE;
		}
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_get_host_powt_state);

/**
 * fc_get_host_speed() - Wetuwn the speed of the given Scsi_Host
 * @shost: The SCSI host whose powt speed is to be detewmined
 */
void fc_get_host_speed(stwuct Scsi_Host *shost)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);

	fc_host_speed(shost) = wpowt->wink_speed;
}
EXPOWT_SYMBOW(fc_get_host_speed);

/**
 * fc_get_host_stats() - Wetuwn the Scsi_Host's statistics
 * @shost: The SCSI host whose statistics awe to be wetuwned
 */
stwuct fc_host_statistics *fc_get_host_stats(stwuct Scsi_Host *shost)
{
	stwuct fc_host_statistics *fc_stats;
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);
	unsigned int cpu;
	u64 fcp_in_bytes = 0;
	u64 fcp_out_bytes = 0;

	fc_stats = &wpowt->host_stats;
	memset(fc_stats, 0, sizeof(stwuct fc_host_statistics));

	fc_stats->seconds_since_wast_weset = (jiffies - wpowt->boot_time) / HZ;

	fow_each_possibwe_cpu(cpu) {
		stwuct fc_stats *stats;

		stats = pew_cpu_ptw(wpowt->stats, cpu);

		fc_stats->tx_fwames += WEAD_ONCE(stats->TxFwames);
		fc_stats->tx_wowds += WEAD_ONCE(stats->TxWowds);
		fc_stats->wx_fwames += WEAD_ONCE(stats->WxFwames);
		fc_stats->wx_wowds += WEAD_ONCE(stats->WxWowds);
		fc_stats->ewwow_fwames += WEAD_ONCE(stats->EwwowFwames);
		fc_stats->invawid_cwc_count += WEAD_ONCE(stats->InvawidCWCCount);
		fc_stats->fcp_input_wequests += WEAD_ONCE(stats->InputWequests);
		fc_stats->fcp_output_wequests += WEAD_ONCE(stats->OutputWequests);
		fc_stats->fcp_contwow_wequests += WEAD_ONCE(stats->ContwowWequests);
		fcp_in_bytes += WEAD_ONCE(stats->InputBytes);
		fcp_out_bytes += WEAD_ONCE(stats->OutputBytes);
		fc_stats->fcp_packet_awwoc_faiwuwes += WEAD_ONCE(stats->FcpPktAwwocFaiws);
		fc_stats->fcp_packet_abowts += WEAD_ONCE(stats->FcpPktAbowts);
		fc_stats->fcp_fwame_awwoc_faiwuwes += WEAD_ONCE(stats->FcpFwameAwwocFaiws);
		fc_stats->wink_faiwuwe_count += WEAD_ONCE(stats->WinkFaiwuweCount);
	}
	fc_stats->fcp_input_megabytes = div_u64(fcp_in_bytes, 1000000);
	fc_stats->fcp_output_megabytes = div_u64(fcp_out_bytes, 1000000);
	fc_stats->wip_count = -1;
	fc_stats->nos_count = -1;
	fc_stats->woss_of_sync_count = -1;
	fc_stats->woss_of_signaw_count = -1;
	fc_stats->pwim_seq_pwotocow_eww_count = -1;
	fc_stats->dumped_fwames = -1;

	/* update exches stats */
	fc_exch_update_stats(wpowt);

	wetuwn fc_stats;
}
EXPOWT_SYMBOW(fc_get_host_stats);

/**
 * fc_wpowt_fwogi_fiww() - Fiww in FWOGI command fow wequest
 * @wpowt: The wocaw powt the FWOGI is fow
 * @fwogi: The FWOGI command
 * @op:	   The opcode
 */
static void fc_wpowt_fwogi_fiww(stwuct fc_wpowt *wpowt,
				stwuct fc_ews_fwogi *fwogi,
				unsigned int op)
{
	stwuct fc_ews_csp *sp;
	stwuct fc_ews_cssp *cp;

	memset(fwogi, 0, sizeof(*fwogi));
	fwogi->fw_cmd = (u8) op;
	put_unawigned_be64(wpowt->wwpn, &fwogi->fw_wwpn);
	put_unawigned_be64(wpowt->wwnn, &fwogi->fw_wwnn);
	sp = &fwogi->fw_csp;
	sp->sp_hi_vew = 0x20;
	sp->sp_wo_vew = 0x20;
	sp->sp_bb_cwed = htons(10);	/* this gets set by gateway */
	sp->sp_bb_data = htons((u16) wpowt->mfs);
	cp = &fwogi->fw_cssp[3 - 1];	/* cwass 3 pawametews */
	cp->cp_cwass = htons(FC_CPC_VAWID | FC_CPC_SEQ);
	if (op != EWS_FWOGI) {
		sp->sp_featuwes = htons(FC_SP_FT_CIWO);
		sp->sp_tot_seq = htons(255);	/* seq. we accept */
		sp->sp_wew_off = htons(0x1f);
		sp->sp_e_d_tov = htonw(wpowt->e_d_tov);

		cp->cp_wdfs = htons((u16) wpowt->mfs);
		cp->cp_con_seq = htons(255);
		cp->cp_open_seq = 1;
	}
}

/**
 * fc_wpowt_add_fc4_type() - Add a suppowted FC-4 type to a wocaw powt
 * @wpowt: The wocaw powt to add a new FC-4 type to
 * @type:  The new FC-4 type
 */
static void fc_wpowt_add_fc4_type(stwuct fc_wpowt *wpowt, enum fc_fh_type type)
{
	__be32 *mp;

	mp = &wpowt->fcts.ff_type_map[type / FC_NS_BPW];
	*mp = htonw(ntohw(*mp) | 1UW << (type % FC_NS_BPW));
}

/**
 * fc_wpowt_wecv_wwiw_weq() - Handwe weceived Wegistewed Wink Incident Wepowt.
 * @wpowt: Fibwe Channew wocaw powt weceiving the WWIW
 * @fp:	   The WWIW wequest fwame
 */
static void fc_wpowt_wecv_wwiw_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Weceived WWIW wequest whiwe in state %s\n",
		     fc_wpowt_state(wpowt));

	fc_seq_ews_wsp_send(fp, EWS_WS_ACC, NUWW);
	fc_fwame_fwee(fp);
}

/**
 * fc_wpowt_wecv_echo_weq() - Handwe weceived ECHO wequest
 * @wpowt: The wocaw powt weceiving the ECHO
 * @in_fp: ECHO wequest fwame
 */
static void fc_wpowt_wecv_echo_weq(stwuct fc_wpowt *wpowt,
				   stwuct fc_fwame *in_fp)
{
	stwuct fc_fwame *fp;
	unsigned int wen;
	void *pp;
	void *dp;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Weceived ECHO wequest whiwe in state %s\n",
		     fc_wpowt_state(wpowt));

	wen = fw_wen(in_fp) - sizeof(stwuct fc_fwame_headew);
	pp = fc_fwame_paywoad_get(in_fp, wen);

	if (wen < sizeof(__be32))
		wen = sizeof(__be32);

	fp = fc_fwame_awwoc(wpowt, wen);
	if (fp) {
		dp = fc_fwame_paywoad_get(fp, wen);
		memcpy(dp, pp, wen);
		*((__be32 *)dp) = htonw(EWS_WS_ACC << 24);
		fc_fiww_wepwy_hdw(fp, in_fp, FC_WCTW_EWS_WEP, 0);
		wpowt->tt.fwame_send(wpowt, fp);
	}
	fc_fwame_fwee(in_fp);
}

/**
 * fc_wpowt_wecv_wnid_weq() - Handwe weceived Wequest Node ID data wequest
 * @wpowt: The wocaw powt weceiving the WNID
 * @in_fp: The WNID wequest fwame
 */
static void fc_wpowt_wecv_wnid_weq(stwuct fc_wpowt *wpowt,
				   stwuct fc_fwame *in_fp)
{
	stwuct fc_fwame *fp;
	stwuct fc_ews_wnid *weq;
	stwuct {
		stwuct fc_ews_wnid_wesp wnid;
		stwuct fc_ews_wnid_cid cid;
		stwuct fc_ews_wnid_gen gen;
	} *wp;
	stwuct fc_seq_ews_data wjt_data;
	u8 fmt;
	size_t wen;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Weceived WNID wequest whiwe in state %s\n",
		     fc_wpowt_state(wpowt));

	weq = fc_fwame_paywoad_get(in_fp, sizeof(*weq));
	if (!weq) {
		wjt_data.weason = EWS_WJT_WOGIC;
		wjt_data.expwan = EWS_EXPW_NONE;
		fc_seq_ews_wsp_send(in_fp, EWS_WS_WJT, &wjt_data);
	} ewse {
		fmt = weq->wnid_fmt;
		wen = sizeof(*wp);
		if (fmt != EWS_WNIDF_GEN ||
		    ntohw(wpowt->wnid_gen.wnid_atype) == 0) {
			fmt = EWS_WNIDF_NONE;	/* nothing to pwovide */
			wen -= sizeof(wp->gen);
		}
		fp = fc_fwame_awwoc(wpowt, wen);
		if (fp) {
			wp = fc_fwame_paywoad_get(fp, wen);
			memset(wp, 0, wen);
			wp->wnid.wnid_cmd = EWS_WS_ACC;
			wp->wnid.wnid_fmt = fmt;
			wp->wnid.wnid_cid_wen = sizeof(wp->cid);
			wp->cid.wnid_wwpn = htonww(wpowt->wwpn);
			wp->cid.wnid_wwnn = htonww(wpowt->wwnn);
			if (fmt == EWS_WNIDF_GEN) {
				wp->wnid.wnid_sid_wen = sizeof(wp->gen);
				memcpy(&wp->gen, &wpowt->wnid_gen,
				       sizeof(wp->gen));
			}
			fc_fiww_wepwy_hdw(fp, in_fp, FC_WCTW_EWS_WEP, 0);
			wpowt->tt.fwame_send(wpowt, fp);
		}
	}
	fc_fwame_fwee(in_fp);
}

/**
 * fc_wpowt_wecv_wogo_weq() - Handwe weceived fabwic WOGO wequest
 * @wpowt: The wocaw powt weceiving the WOGO
 * @fp:	   The WOGO wequest fwame
 */
static void fc_wpowt_wecv_wogo_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	fc_seq_ews_wsp_send(fp, EWS_WS_ACC, NUWW);
	fc_wpowt_entew_weset(wpowt);
	fc_fwame_fwee(fp);
}

/**
 * fc_fabwic_wogin() - Stawt the wpowt state machine
 * @wpowt: The wocaw powt that shouwd wog into the fabwic
 *
 * Wocking Note: This function shouwd not be cawwed
 *		 with the wpowt wock hewd.
 */
int fc_fabwic_wogin(stwuct fc_wpowt *wpowt)
{
	int wc = -1;

	mutex_wock(&wpowt->wp_mutex);
	if (wpowt->state == WPOWT_ST_DISABWED ||
	    wpowt->state == WPOWT_ST_WOGO) {
		fc_wpowt_state_entew(wpowt, WPOWT_ST_WESET);
		fc_wpowt_entew_weset(wpowt);
		wc = 0;
	}
	mutex_unwock(&wpowt->wp_mutex);

	wetuwn wc;
}
EXPOWT_SYMBOW(fc_fabwic_wogin);

/**
 * __fc_winkup() - Handwew fow twanspowt winkup events
 * @wpowt: The wpowt whose wink is up
 */
void __fc_winkup(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	if (!wpowt->wink_up) {
		wpowt->wink_up = 1;

		if (wpowt->state == WPOWT_ST_WESET)
			fc_wpowt_entew_fwogi(wpowt);
	}
}

/**
 * fc_winkup() - Handwew fow twanspowt winkup events
 * @wpowt: The wocaw powt whose wink is up
 */
void fc_winkup(stwuct fc_wpowt *wpowt)
{
	pwintk(KEWN_INFO "host%d: wibfc: Wink up on powt (%6.6x)\n",
	       wpowt->host->host_no, wpowt->powt_id);

	mutex_wock(&wpowt->wp_mutex);
	__fc_winkup(wpowt);
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_winkup);

/**
 * __fc_winkdown() - Handwew fow twanspowt winkdown events
 * @wpowt: The wpowt whose wink is down
 */
void __fc_winkdown(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	if (wpowt->wink_up) {
		wpowt->wink_up = 0;
		fc_wpowt_entew_weset(wpowt);
		wpowt->tt.fcp_cweanup(wpowt);
	}
}

/**
 * fc_winkdown() - Handwew fow twanspowt winkdown events
 * @wpowt: The wocaw powt whose wink is down
 */
void fc_winkdown(stwuct fc_wpowt *wpowt)
{
	pwintk(KEWN_INFO "host%d: wibfc: Wink down on powt (%6.6x)\n",
	       wpowt->host->host_no, wpowt->powt_id);

	mutex_wock(&wpowt->wp_mutex);
	__fc_winkdown(wpowt);
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_winkdown);

/**
 * fc_fabwic_wogoff() - Wogout of the fabwic
 * @wpowt: The wocaw powt to wogoff the fabwic
 *
 * Wetuwn vawue:
 *	0 fow success, -1 fow faiwuwe
 */
int fc_fabwic_wogoff(stwuct fc_wpowt *wpowt)
{
	wpowt->tt.disc_stop_finaw(wpowt);
	mutex_wock(&wpowt->wp_mutex);
	if (wpowt->dns_wdata)
		fc_wpowt_wogoff(wpowt->dns_wdata);
	mutex_unwock(&wpowt->wp_mutex);
	fc_wpowt_fwush_queue();
	mutex_wock(&wpowt->wp_mutex);
	fc_wpowt_entew_wogo(wpowt);
	mutex_unwock(&wpowt->wp_mutex);
	cancew_dewayed_wowk_sync(&wpowt->wetwy_wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW(fc_fabwic_wogoff);

/**
 * fc_wpowt_destwoy() - Unwegistew a fc_wpowt
 * @wpowt: The wocaw powt to unwegistew
 *
 * Note:
 * exit woutine fow fc_wpowt instance
 * cwean-up aww the awwocated memowy
 * and fwee up othew system wesouwces.
 *
 */
int fc_wpowt_destwoy(stwuct fc_wpowt *wpowt)
{
	mutex_wock(&wpowt->wp_mutex);
	wpowt->state = WPOWT_ST_DISABWED;
	wpowt->wink_up = 0;
	wpowt->tt.fwame_send = fc_fwame_dwop;
	mutex_unwock(&wpowt->wp_mutex);

	wpowt->tt.fcp_abowt_io(wpowt);
	wpowt->tt.disc_stop_finaw(wpowt);
	wpowt->tt.exch_mgw_weset(wpowt, 0, 0);
	cancew_dewayed_wowk_sync(&wpowt->wetwy_wowk);
	fc_fc4_dew_wpowt(wpowt);
	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_destwoy);

/**
 * fc_set_mfs() - Set the maximum fwame size fow a wocaw powt
 * @wpowt: The wocaw powt to set the MFS fow
 * @mfs:   The new MFS
 */
int fc_set_mfs(stwuct fc_wpowt *wpowt, u32 mfs)
{
	unsigned int owd_mfs;
	int wc = -EINVAW;

	mutex_wock(&wpowt->wp_mutex);

	owd_mfs = wpowt->mfs;

	if (mfs >= FC_MIN_MAX_FWAME) {
		mfs &= ~3;
		if (mfs > FC_MAX_FWAME)
			mfs = FC_MAX_FWAME;
		mfs -= sizeof(stwuct fc_fwame_headew);
		wpowt->mfs = mfs;
		wc = 0;
	}

	if (!wc && mfs < owd_mfs)
		fc_wpowt_entew_weset(wpowt);

	mutex_unwock(&wpowt->wp_mutex);

	wetuwn wc;
}
EXPOWT_SYMBOW(fc_set_mfs);

/**
 * fc_wpowt_disc_cawwback() - Cawwback fow discovewy events
 * @wpowt: The wocaw powt weceiving the event
 * @event: The discovewy event
 */
static void fc_wpowt_disc_cawwback(stwuct fc_wpowt *wpowt,
				   enum fc_disc_event event)
{
	switch (event) {
	case DISC_EV_SUCCESS:
		FC_WPOWT_DBG(wpowt, "Discovewy succeeded\n");
		bweak;
	case DISC_EV_FAIWED:
		pwintk(KEWN_EWW "host%d: wibfc: "
		       "Discovewy faiwed fow powt (%6.6x)\n",
		       wpowt->host->host_no, wpowt->powt_id);
		mutex_wock(&wpowt->wp_mutex);
		fc_wpowt_entew_weset(wpowt);
		mutex_unwock(&wpowt->wp_mutex);
		bweak;
	case DISC_EV_NONE:
		WAWN_ON(1);
		bweak;
	}
}

/**
 * fc_wpowt_entew_weady() - Entew the weady state and stawt discovewy
 * @wpowt: The wocaw powt that is weady
 */
static void fc_wpowt_entew_weady(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed WEADY fwom state %s\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_WEADY);
	if (wpowt->vpowt)
		fc_vpowt_set_state(wpowt->vpowt, FC_VPOWT_ACTIVE);
	fc_vpowts_winkchange(wpowt);

	if (!wpowt->ptp_wdata)
		wpowt->tt.disc_stawt(fc_wpowt_disc_cawwback, wpowt);
}

/**
 * fc_wpowt_set_powt_id() - set the wocaw powt Powt ID
 * @wpowt: The wocaw powt which wiww have its Powt ID set.
 * @powt_id: The new powt ID.
 * @fp: The fwame containing the incoming wequest, ow NUWW.
 */
static void fc_wpowt_set_powt_id(stwuct fc_wpowt *wpowt, u32 powt_id,
				 stwuct fc_fwame *fp)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	if (powt_id)
		pwintk(KEWN_INFO "host%d: Assigned Powt ID %6.6x\n",
		       wpowt->host->host_no, powt_id);

	wpowt->powt_id = powt_id;

	/* Update the fc_host */
	fc_host_powt_id(wpowt->host) = powt_id;

	if (wpowt->tt.wpowt_set_powt_id)
		wpowt->tt.wpowt_set_powt_id(wpowt, powt_id, fp);
}

/**
 * fc_wpowt_set_wocaw_id() - set the wocaw powt Powt ID fow point-to-muwtipoint
 * @wpowt: The wocaw powt which wiww have its Powt ID set.
 * @powt_id: The new powt ID.
 *
 * Cawwed by the wowew-wevew dwivew when twanspowt sets the wocaw powt_id.
 * This is used in VN_powt to VN_powt mode fow FCoE, and causes FWOGI and
 * discovewy to be skipped.
 */
void fc_wpowt_set_wocaw_id(stwuct fc_wpowt *wpowt, u32 powt_id)
{
	mutex_wock(&wpowt->wp_mutex);

	fc_wpowt_set_powt_id(wpowt, powt_id, NUWW);

	switch (wpowt->state) {
	case WPOWT_ST_WESET:
	case WPOWT_ST_FWOGI:
		if (powt_id)
			fc_wpowt_entew_weady(wpowt);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_wpowt_set_wocaw_id);

/**
 * fc_wpowt_wecv_fwogi_weq() - Weceive a FWOGI wequest
 * @wpowt: The wocaw powt that weceived the wequest
 * @wx_fp: The FWOGI fwame
 *
 * A weceived FWOGI wequest indicates a point-to-point connection.
 * Accept it with the common sewvice pawametews indicating ouw N powt.
 * Set up to do a PWOGI if we have the highew-numbew WWPN.
 */
static void fc_wpowt_wecv_fwogi_weq(stwuct fc_wpowt *wpowt,
				    stwuct fc_fwame *wx_fp)
{
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ews_fwogi *fwp;
	stwuct fc_ews_fwogi *new_fwp;
	u64 wemote_wwpn;
	u32 wemote_fid;
	u32 wocaw_fid;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Weceived FWOGI wequest whiwe in state %s\n",
		     fc_wpowt_state(wpowt));

	wemote_fid = fc_fwame_sid(wx_fp);
	fwp = fc_fwame_paywoad_get(wx_fp, sizeof(*fwp));
	if (!fwp)
		goto out;
	wemote_wwpn = get_unawigned_be64(&fwp->fw_wwpn);
	if (wemote_wwpn == wpowt->wwpn) {
		pwintk(KEWN_WAWNING "host%d: wibfc: Weceived FWOGI fwom powt "
		       "with same WWPN %16.16wwx\n",
		       wpowt->host->host_no, wemote_wwpn);
		goto out;
	}
	FC_WPOWT_DBG(wpowt, "FWOGI fwom powt WWPN %16.16wwx\n", wemote_wwpn);

	/*
	 * XXX what is the wight thing to do fow FIDs?
	 * The owiginatow might expect ouw S_ID to be 0xfffffe.
	 * But if so, both of us couwd end up with the same FID.
	 */
	wocaw_fid = FC_WOCAW_PTP_FID_WO;
	if (wemote_wwpn < wpowt->wwpn) {
		wocaw_fid = FC_WOCAW_PTP_FID_HI;
		if (!wemote_fid || wemote_fid == wocaw_fid)
			wemote_fid = FC_WOCAW_PTP_FID_WO;
	} ewse if (!wemote_fid) {
		wemote_fid = FC_WOCAW_PTP_FID_HI;
	}

	fc_wpowt_set_powt_id(wpowt, wocaw_fid, wx_fp);

	fp = fc_fwame_awwoc(wpowt, sizeof(*fwp));
	if (fp) {
		new_fwp = fc_fwame_paywoad_get(fp, sizeof(*fwp));
		fc_wpowt_fwogi_fiww(wpowt, new_fwp, EWS_FWOGI);
		new_fwp->fw_cmd = (u8) EWS_WS_ACC;

		/*
		 * Send the wesponse.  If this faiws, the owiginatow shouwd
		 * wepeat the sequence.
		 */
		fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
		fh = fc_fwame_headew_get(fp);
		hton24(fh->fh_s_id, wocaw_fid);
		hton24(fh->fh_d_id, wemote_fid);
		wpowt->tt.fwame_send(wpowt, fp);

	} ewse {
		fc_wpowt_ewwow(wpowt, fp);
	}
	fc_wpowt_ptp_setup(wpowt, wemote_fid, wemote_wwpn,
			   get_unawigned_be64(&fwp->fw_wwnn));
out:
	fc_fwame_fwee(wx_fp);
}

/**
 * fc_wpowt_wecv_ews_weq() - The genewic wpowt EWS wequest handwew
 * @wpowt: The wocaw powt that weceived the wequest
 * @fp:	   The wequest fwame
 *
 * This function wiww see if the wpowt handwes the wequest ow
 * if an wpowt shouwd handwe the wequest.
 *
 * Wocking Note: This function shouwd not be cawwed with the wpowt
 *		 wock hewd because it wiww gwab the wock.
 */
static void fc_wpowt_wecv_ews_weq(stwuct fc_wpowt *wpowt,
				  stwuct fc_fwame *fp)
{
	mutex_wock(&wpowt->wp_mutex);

	/*
	 * Handwe speciaw EWS cases wike FWOGI, WOGO, and
	 * WSCN hewe.  These don't wequiwe a session.
	 * Even if we had a session, it might not be weady.
	 */
	if (!wpowt->wink_up)
		fc_fwame_fwee(fp);
	ewse {
		/*
		 * Check opcode.
		 */
		switch (fc_fwame_paywoad_op(fp)) {
		case EWS_FWOGI:
			if (!wpowt->point_to_muwtipoint)
				fc_wpowt_wecv_fwogi_weq(wpowt, fp);
			ewse
				fc_wpowt_wecv_weq(wpowt, fp);
			bweak;
		case EWS_WOGO:
			if (fc_fwame_sid(fp) == FC_FID_FWOGI)
				fc_wpowt_wecv_wogo_weq(wpowt, fp);
			ewse
				fc_wpowt_wecv_weq(wpowt, fp);
			bweak;
		case EWS_WSCN:
			wpowt->tt.disc_wecv_weq(wpowt, fp);
			bweak;
		case EWS_ECHO:
			fc_wpowt_wecv_echo_weq(wpowt, fp);
			bweak;
		case EWS_WWIW:
			fc_wpowt_wecv_wwiw_weq(wpowt, fp);
			bweak;
		case EWS_WNID:
			fc_wpowt_wecv_wnid_weq(wpowt, fp);
			bweak;
		defauwt:
			fc_wpowt_wecv_weq(wpowt, fp);
			bweak;
		}
	}
	mutex_unwock(&wpowt->wp_mutex);
}

static int fc_wpowt_ews_pwwi(stwuct fc_wpowt_pwiv *wdata, u32 spp_wen,
			     const stwuct fc_ews_spp *spp_in,
			     stwuct fc_ews_spp *spp_out)
{
	wetuwn FC_SPP_WESP_INVW;
}

stwuct fc4_pwov fc_wpowt_ews_pwov = {
	.pwwi = fc_wpowt_ews_pwwi,
	.wecv = fc_wpowt_wecv_ews_weq,
};

/**
 * fc_wpowt_wecv() - The genewic wpowt wequest handwew
 * @wpowt: The wpowt that weceived the wequest
 * @fp: The fwame the wequest is in
 *
 * Wocking Note: This function shouwd not be cawwed with the wpowt
 *		 wock hewd because it may gwab the wock.
 */
void fc_wpowt_wecv(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_seq *sp = fw_seq(fp);
	stwuct fc4_pwov *pwov;

	/*
	 * Use WCU wead wock and moduwe_wock to be suwe moduwe doesn't
	 * dewegistew and get unwoaded whiwe we'we cawwing it.
	 * twy_moduwe_get() is inwined and accepts a NUWW pawametew.
	 * Onwy EWSes and FCP tawget ops shouwd come thwough hewe.
	 * The wocking is unfowtunate, and a bettew scheme is being sought.
	 */

	wcu_wead_wock();
	if (fh->fh_type >= FC_FC4_PWOV_SIZE)
		goto dwop;
	pwov = wcu_dewefewence(fc_passive_pwov[fh->fh_type]);
	if (!pwov || !twy_moduwe_get(pwov->moduwe))
		goto dwop;
	wcu_wead_unwock();
	pwov->wecv(wpowt, fp);
	moduwe_put(pwov->moduwe);
	wetuwn;
dwop:
	wcu_wead_unwock();
	FC_WPOWT_DBG(wpowt, "dwopping unexpected fwame type %x\n", fh->fh_type);
	fc_fwame_fwee(fp);
	if (sp)
		fc_exch_done(sp);
}
EXPOWT_SYMBOW(fc_wpowt_wecv);

/**
 * fc_wpowt_weset() - Weset a wocaw powt
 * @wpowt: The wocaw powt which shouwd be weset
 *
 * Wocking Note: This functions shouwd not be cawwed with the
 *		 wpowt wock hewd.
 */
int fc_wpowt_weset(stwuct fc_wpowt *wpowt)
{
	cancew_dewayed_wowk_sync(&wpowt->wetwy_wowk);
	mutex_wock(&wpowt->wp_mutex);
	fc_wpowt_entew_weset(wpowt);
	mutex_unwock(&wpowt->wp_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_weset);

/**
 * fc_wpowt_weset_wocked() - Weset the wocaw powt w/ the wpowt wock hewd
 * @wpowt: The wocaw powt to be weset
 */
static void fc_wpowt_weset_wocked(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	if (wpowt->dns_wdata) {
		fc_wpowt_wogoff(wpowt->dns_wdata);
		wpowt->dns_wdata = NUWW;
	}

	if (wpowt->ptp_wdata) {
		fc_wpowt_wogoff(wpowt->ptp_wdata);
		kwef_put(&wpowt->ptp_wdata->kwef, fc_wpowt_destwoy);
		wpowt->ptp_wdata = NUWW;
	}

	wpowt->tt.disc_stop(wpowt);

	wpowt->tt.exch_mgw_weset(wpowt, 0, 0);
	fc_host_fabwic_name(wpowt->host) = 0;

	if (wpowt->powt_id && (!wpowt->point_to_muwtipoint || !wpowt->wink_up))
		fc_wpowt_set_powt_id(wpowt, 0, NUWW);
}

/**
 * fc_wpowt_entew_weset() - Weset the wocaw powt
 * @wpowt: The wocaw powt to be weset
 */
static void fc_wpowt_entew_weset(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed WESET state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	if (wpowt->state == WPOWT_ST_DISABWED || wpowt->state == WPOWT_ST_WOGO)
		wetuwn;

	if (wpowt->vpowt) {
		if (wpowt->wink_up)
			fc_vpowt_set_state(wpowt->vpowt, FC_VPOWT_INITIAWIZING);
		ewse
			fc_vpowt_set_state(wpowt->vpowt, FC_VPOWT_WINKDOWN);
	}
	fc_wpowt_state_entew(wpowt, WPOWT_ST_WESET);
	fc_host_post_event(wpowt->host, fc_get_event_numbew(),
			   FCH_EVT_WIPWESET, 0);
	fc_vpowts_winkchange(wpowt);
	fc_wpowt_weset_wocked(wpowt);
	if (wpowt->wink_up)
		fc_wpowt_entew_fwogi(wpowt);
}

/**
 * fc_wpowt_entew_disabwed() - Disabwe the wocaw powt
 * @wpowt: The wocaw powt to be weset
 */
static void fc_wpowt_entew_disabwed(stwuct fc_wpowt *wpowt)
{
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed disabwed state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_DISABWED);
	fc_vpowts_winkchange(wpowt);
	fc_wpowt_weset_wocked(wpowt);
}

/**
 * fc_wpowt_ewwow() - Handwew fow any ewwows
 * @wpowt: The wocaw powt that the ewwow was on
 * @fp:	   The ewwow code encoded in a fwame pointew
 *
 * If the ewwow was caused by a wesouwce awwocation faiwuwe
 * then wait fow hawf a second and wetwy, othewwise wetwy
 * aftew the e_d_tov time.
 */
static void fc_wpowt_ewwow(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	unsigned wong deway = 0;
	FC_WPOWT_DBG(wpowt, "Ewwow %wd in state %s, wetwies %d\n",
		     IS_EWW(fp) ? -PTW_EWW(fp) : 0, fc_wpowt_state(wpowt),
		     wpowt->wetwy_count);

	if (PTW_EWW(fp) == -FC_EX_CWOSED)
		wetuwn;

	/*
	 * Memowy awwocation faiwuwe, ow the exchange timed out
	 * ow we weceived WS_WJT.
	 * Wetwy aftew deway
	 */
	if (wpowt->wetwy_count < wpowt->max_wetwy_count) {
		wpowt->wetwy_count++;
		if (!fp)
			deway = msecs_to_jiffies(500);
		ewse
			deway =	msecs_to_jiffies(wpowt->e_d_tov);

		scheduwe_dewayed_wowk(&wpowt->wetwy_wowk, deway);
	} ewse
		fc_wpowt_entew_weset(wpowt);
}

/**
 * fc_wpowt_ns_wesp() - Handwe wesponse to a name sewvew
 *			wegistwation exchange
 * @sp:	    cuwwent sequence in exchange
 * @fp:	    wesponse fwame
 * @wp_awg: Fibwe Channew host powt instance
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow()
 * and then unwock the wpowt.
 */
static void fc_wpowt_ns_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			     void *wp_awg)
{
	stwuct fc_wpowt *wpowt = wp_awg;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ct_hdw *ct;

	FC_WPOWT_DBG(wpowt, "Weceived a ns %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		wetuwn;

	mutex_wock(&wpowt->wp_mutex);

	if (wpowt->state < WPOWT_ST_WNN_ID || wpowt->state > WPOWT_ST_WFF_ID) {
		FC_WPOWT_DBG(wpowt, "Weceived a name sewvew wesponse, "
			     "but in state %s\n", fc_wpowt_state(wpowt));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wpowt, fp);
		goto eww;
	}

	fh = fc_fwame_headew_get(fp);
	ct = fc_fwame_paywoad_get(fp, sizeof(*ct));

	if (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_DIW &&
	    ct->ct_fs_subtype == FC_NS_SUBTYPE &&
	    ntohs(ct->ct_cmd) == FC_FS_ACC)
		switch (wpowt->state) {
		case WPOWT_ST_WNN_ID:
			fc_wpowt_entew_ns(wpowt, WPOWT_ST_WSNN_NN);
			bweak;
		case WPOWT_ST_WSNN_NN:
			fc_wpowt_entew_ns(wpowt, WPOWT_ST_WSPN_ID);
			bweak;
		case WPOWT_ST_WSPN_ID:
			fc_wpowt_entew_ns(wpowt, WPOWT_ST_WFT_ID);
			bweak;
		case WPOWT_ST_WFT_ID:
			fc_wpowt_entew_ns(wpowt, WPOWT_ST_WFF_ID);
			bweak;
		case WPOWT_ST_WFF_ID:
			if (wpowt->fdmi_enabwed)
				fc_wpowt_entew_fdmi(wpowt);
			ewse
				fc_wpowt_entew_scw(wpowt);
			bweak;
		defauwt:
			/* shouwd have awweady been caught by state checks */
			bweak;
		}
	ewse
		fc_wpowt_ewwow(wpowt, fp);
out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_ms_wesp() - Handwe wesponse to a management sewvew
 *			exchange
 * @sp:	    cuwwent sequence in exchange
 * @fp:	    wesponse fwame
 * @wp_awg: Fibwe Channew host powt instance
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow()
 * and then unwock the wpowt.
 */
static void fc_wpowt_ms_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			     void *wp_awg)
{
	stwuct fc_wpowt *wpowt = wp_awg;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ct_hdw *ct;
	stwuct fc_host_attws *fc_host = shost_to_fc_host(wpowt->host);
	FC_WPOWT_DBG(wpowt, "Weceived a ms %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		wetuwn;

	mutex_wock(&wpowt->wp_mutex);

	if (wpowt->state < WPOWT_ST_WHBA || wpowt->state > WPOWT_ST_DPWT) {
		FC_WPOWT_DBG(wpowt, "Weceived a management sewvew wesponse, "
			     "but in state %s\n", fc_wpowt_state(wpowt));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wpowt, fp);
		goto eww;
	}

	fh = fc_fwame_headew_get(fp);
	ct = fc_fwame_paywoad_get(fp, sizeof(*ct));

	if (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_MGMT &&
	    ct->ct_fs_subtype == FC_FDMI_SUBTYPE) {
		FC_WPOWT_DBG(wpowt, "Weceived a management sewvew wesponse, "
				    "weason=%d expwain=%d\n",
				    ct->ct_weason,
				    ct->ct_expwan);

		switch (wpowt->state) {
		case WPOWT_ST_WHBA:
			if ((ntohs(ct->ct_cmd) == FC_FS_WJT) && fc_host->fdmi_vewsion == FDMI_V2) {
				FC_WPOWT_DBG(wpowt, "Ewwow fow FDMI-V2, faww back to FDMI-V1\n");
				fc_host->fdmi_vewsion = FDMI_V1;

				fc_wpowt_entew_ms(wpowt, WPOWT_ST_WHBA);

			} ewse if (ntohs(ct->ct_cmd) == FC_FS_ACC)
				fc_wpowt_entew_ms(wpowt, WPOWT_ST_WPA);
			ewse /* Ewwow Skip WPA */
				fc_wpowt_entew_scw(wpowt);
			bweak;
		case WPOWT_ST_WPA:
			fc_wpowt_entew_scw(wpowt);
			bweak;
		case WPOWT_ST_DPWT:
			fc_wpowt_entew_ms(wpowt, WPOWT_ST_WHBA);
			bweak;
		case WPOWT_ST_DHBA:
			fc_wpowt_entew_ms(wpowt, WPOWT_ST_DPWT);
			bweak;
		defauwt:
			/* shouwd have awweady been caught by state checks */
			bweak;
		}
	} ewse {
		/* Invawid Fwame? */
		fc_wpowt_ewwow(wpowt, fp);
	}
out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_scw_wesp() - Handwe wesponse to State Change Wegistew (SCW) wequest
 * @sp:	    cuwwent sequence in SCW exchange
 * @fp:	    wesponse fwame
 * @wp_awg: Fibwe Channew wpowt powt instance that sent the wegistwation wequest
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow
 * and then unwock the wpowt.
 */
static void fc_wpowt_scw_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			      void *wp_awg)
{
	stwuct fc_wpowt *wpowt = wp_awg;
	u8 op;

	FC_WPOWT_DBG(wpowt, "Weceived a SCW %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		wetuwn;

	mutex_wock(&wpowt->wp_mutex);

	if (wpowt->state != WPOWT_ST_SCW) {
		FC_WPOWT_DBG(wpowt, "Weceived a SCW wesponse, but in state "
			     "%s\n", fc_wpowt_state(wpowt));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wpowt, fp);
		goto eww;
	}

	op = fc_fwame_paywoad_op(fp);
	if (op == EWS_WS_ACC)
		fc_wpowt_entew_weady(wpowt);
	ewse
		fc_wpowt_ewwow(wpowt, fp);

out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_entew_scw() - Send a SCW (State Change Wegistew) wequest
 * @wpowt: The wocaw powt to wegistew fow state changes
 */
static void fc_wpowt_entew_scw(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed SCW state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_SCW);

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_scw));
	if (!fp) {
		fc_wpowt_ewwow(wpowt, fp);
		wetuwn;
	}

	if (!wpowt->tt.ewsct_send(wpowt, FC_FID_FCTWW, fp, EWS_SCW,
				  fc_wpowt_scw_wesp, wpowt,
				  2 * wpowt->w_a_tov))
		fc_wpowt_ewwow(wpowt, NUWW);
}

/**
 * fc_wpowt_entew_ns() - wegistew some object with the name sewvew
 * @wpowt: Fibwe Channew wocaw powt to wegistew
 * @state: Wocaw powt state
 */
static void fc_wpowt_entew_ns(stwuct fc_wpowt *wpowt, enum fc_wpowt_state state)
{
	stwuct fc_fwame *fp;
	enum fc_ns_weq cmd;
	int size = sizeof(stwuct fc_ct_hdw);
	size_t wen;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed %s state fwom %s state\n",
		     fc_wpowt_state_names[state],
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, state);

	switch (state) {
	case WPOWT_ST_WNN_ID:
		cmd = FC_NS_WNN_ID;
		size += sizeof(stwuct fc_ns_wn_id);
		bweak;
	case WPOWT_ST_WSNN_NN:
		wen = stwnwen(fc_host_symbowic_name(wpowt->host), 255);
		/* if thewe is no symbowic name, skip to WFT_ID */
		if (!wen)
			wetuwn fc_wpowt_entew_ns(wpowt, WPOWT_ST_WFT_ID);
		cmd = FC_NS_WSNN_NN;
		size += sizeof(stwuct fc_ns_wsnn) + wen;
		bweak;
	case WPOWT_ST_WSPN_ID:
		wen = stwnwen(fc_host_symbowic_name(wpowt->host), 255);
		/* if thewe is no symbowic name, skip to WFT_ID */
		if (!wen)
			wetuwn fc_wpowt_entew_ns(wpowt, WPOWT_ST_WFT_ID);
		cmd = FC_NS_WSPN_ID;
		size += sizeof(stwuct fc_ns_wspn) + wen;
		bweak;
	case WPOWT_ST_WFT_ID:
		cmd = FC_NS_WFT_ID;
		size += sizeof(stwuct fc_ns_wft);
		bweak;
	case WPOWT_ST_WFF_ID:
		cmd = FC_NS_WFF_ID;
		size += sizeof(stwuct fc_ns_wff_id);
		bweak;
	defauwt:
		fc_wpowt_ewwow(wpowt, NUWW);
		wetuwn;
	}

	fp = fc_fwame_awwoc(wpowt, size);
	if (!fp) {
		fc_wpowt_ewwow(wpowt, fp);
		wetuwn;
	}

	if (!wpowt->tt.ewsct_send(wpowt, FC_FID_DIW_SEWV, fp, cmd,
				  fc_wpowt_ns_wesp,
				  wpowt, 3 * wpowt->w_a_tov))
		fc_wpowt_ewwow(wpowt, fp);
}

static stwuct fc_wpowt_opewations fc_wpowt_wpowt_ops = {
	.event_cawwback = fc_wpowt_wpowt_cawwback,
};

/**
 * fc_wpowt_entew_dns() - Cweate a fc_wpowt fow the name sewvew
 * @wpowt: The wocaw powt wequesting a wemote powt fow the name sewvew
 */
static void fc_wpowt_entew_dns(stwuct fc_wpowt *wpowt)
{
	stwuct fc_wpowt_pwiv *wdata;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed DNS state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_DNS);

	mutex_wock(&wpowt->disc.disc_mutex);
	wdata = fc_wpowt_cweate(wpowt, FC_FID_DIW_SEWV);
	mutex_unwock(&wpowt->disc.disc_mutex);
	if (!wdata)
		goto eww;

	wdata->ops = &fc_wpowt_wpowt_ops;
	fc_wpowt_wogin(wdata);
	wetuwn;

eww:
	fc_wpowt_ewwow(wpowt, NUWW);
}

/**
 * fc_wpowt_entew_ms() - management sewvew commands
 * @wpowt: Fibwe Channew wocaw powt to wegistew
 * @state: Wocaw powt state
 */
static void fc_wpowt_entew_ms(stwuct fc_wpowt *wpowt, enum fc_wpowt_state state)
{
	stwuct fc_fwame *fp;
	enum fc_fdmi_weq cmd;
	int size = sizeof(stwuct fc_ct_hdw);
	size_t wen;
	int numattws;
	stwuct fc_host_attws *fc_host = shost_to_fc_host(wpowt->host);
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed %s state fwom %s state\n",
		     fc_wpowt_state_names[state],
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, state);

	switch (state) {
	case WPOWT_ST_WHBA:
		cmd = FC_FDMI_WHBA;
		/* Numbew of HBA Attwibutes */
		numattws = 11;
		wen = sizeof(stwuct fc_fdmi_whba);
		wen -= sizeof(stwuct fc_fdmi_attw_entwy);

		wen += FC_FDMI_HBA_ATTW_NODENAME_WEN;
		wen += FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN;
		wen += FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEWDESCW_WEN;
		wen += FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN;


		if (fc_host->fdmi_vewsion == FDMI_V2) {
			numattws += 7;
			wen += FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO_WEN;
			wen += FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS_WEN;
			wen += FC_FDMI_HBA_ATTW_FABWICNAME_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSSTATE_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW_WEN;
		}

		wen += (numattws * FC_FDMI_ATTW_ENTWY_HEADEW_WEN);

		size += wen;
		bweak;
	case WPOWT_ST_WPA:
		cmd = FC_FDMI_WPA;
		/* Numbew of Powt Attwibutes */
		numattws = 6;
		wen = sizeof(stwuct fc_fdmi_wpa);
		wen -= sizeof(stwuct fc_fdmi_attw_entwy);
		wen += FC_FDMI_POWT_ATTW_FC4TYPES_WEN;
		wen += FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN;
		wen += FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN;
		wen += FC_FDMI_POWT_ATTW_MAXFWAMESIZE_WEN;
		wen += FC_FDMI_POWT_ATTW_OSDEVICENAME_WEN;
		wen += FC_FDMI_POWT_ATTW_HOSTNAME_WEN;

		if (fc_host->fdmi_vewsion == FDMI_V2) {
			numattws += 10;
			wen += FC_FDMI_POWT_ATTW_NODENAME_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTTYPE_WEN;
			wen += FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC_WEN;
			wen += FC_FDMI_POWT_ATTW_FABWICNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTSTATE_WEN;
			wen += FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTID_WEN;
		}

		wen += (numattws * FC_FDMI_ATTW_ENTWY_HEADEW_WEN);

		size += wen;
		bweak;
	case WPOWT_ST_DPWT:
		cmd = FC_FDMI_DPWT;
		wen = sizeof(stwuct fc_fdmi_dpwt);
		size += wen;
		bweak;
	case WPOWT_ST_DHBA:
		cmd = FC_FDMI_DHBA;
		wen = sizeof(stwuct fc_fdmi_dhba);
		size += wen;
		bweak;
	defauwt:
		fc_wpowt_ewwow(wpowt, NUWW);
		wetuwn;
	}

	FC_WPOWT_DBG(wpowt, "Cmd=0x%x Wen %d size %d\n",
			     cmd, (int)wen, size);
	fp = fc_fwame_awwoc(wpowt, size);
	if (!fp) {
		fc_wpowt_ewwow(wpowt, fp);
		wetuwn;
	}

	if (!wpowt->tt.ewsct_send(wpowt, FC_FID_MGMT_SEWV, fp, cmd,
				  fc_wpowt_ms_wesp,
				  wpowt, 3 * wpowt->w_a_tov))
		fc_wpowt_ewwow(wpowt, fp);
}

/**
 * fc_wpowt_entew_fdmi() - Cweate a fc_wpowt fow the management sewvew
 * @wpowt: The wocaw powt wequesting a wemote powt fow the management sewvew
 */
static void fc_wpowt_entew_fdmi(stwuct fc_wpowt *wpowt)
{
	stwuct fc_wpowt_pwiv *wdata;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed FDMI state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_FDMI);

	mutex_wock(&wpowt->disc.disc_mutex);
	wdata = fc_wpowt_cweate(wpowt, FC_FID_MGMT_SEWV);
	mutex_unwock(&wpowt->disc.disc_mutex);
	if (!wdata)
		goto eww;

	wdata->ops = &fc_wpowt_wpowt_ops;
	fc_wpowt_wogin(wdata);
	wetuwn;

eww:
	fc_wpowt_ewwow(wpowt, NUWW);
}

/**
 * fc_wpowt_timeout() - Handwew fow the wetwy_wowk timew
 * @wowk: The wowk stwuct of the wocaw powt
 */
static void fc_wpowt_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct fc_wpowt *wpowt =
		containew_of(wowk, stwuct fc_wpowt,
			     wetwy_wowk.wowk);
	stwuct fc_host_attws *fc_host = shost_to_fc_host(wpowt->host);

	mutex_wock(&wpowt->wp_mutex);

	switch (wpowt->state) {
	case WPOWT_ST_DISABWED:
		bweak;
	case WPOWT_ST_WEADY:
		bweak;
	case WPOWT_ST_WESET:
		bweak;
	case WPOWT_ST_FWOGI:
		fc_wpowt_entew_fwogi(wpowt);
		bweak;
	case WPOWT_ST_DNS:
		fc_wpowt_entew_dns(wpowt);
		bweak;
	case WPOWT_ST_WNN_ID:
	case WPOWT_ST_WSNN_NN:
	case WPOWT_ST_WSPN_ID:
	case WPOWT_ST_WFT_ID:
	case WPOWT_ST_WFF_ID:
		fc_wpowt_entew_ns(wpowt, wpowt->state);
		bweak;
	case WPOWT_ST_FDMI:
		fc_wpowt_entew_fdmi(wpowt);
		bweak;
	case WPOWT_ST_WHBA:
		if (fc_host->fdmi_vewsion == FDMI_V2) {
			FC_WPOWT_DBG(wpowt, "timeout fow FDMI-V2 WHBA,faww back to FDMI-V1\n");
			fc_host->fdmi_vewsion = FDMI_V1;
			fc_wpowt_entew_ms(wpowt, WPOWT_ST_WHBA);
			bweak;
		}
		fawwthwough;
	case WPOWT_ST_WPA:
	case WPOWT_ST_DHBA:
	case WPOWT_ST_DPWT:
		FC_WPOWT_DBG(wpowt, "Skipping wpowt state %s to SCW\n",
			     fc_wpowt_state(wpowt));
		fawwthwough;
	case WPOWT_ST_SCW:
		fc_wpowt_entew_scw(wpowt);
		bweak;
	case WPOWT_ST_WOGO:
		fc_wpowt_entew_wogo(wpowt);
		bweak;
	}

	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_wogo_wesp() - Handwe wesponse to WOGO wequest
 * @sp:	    The sequence that the WOGO was on
 * @fp:	    The WOGO fwame
 * @wp_awg: The wpowt powt that weceived the WOGO wequest
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow()
 * and then unwock the wpowt.
 */
void fc_wpowt_wogo_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			void *wp_awg)
{
	stwuct fc_wpowt *wpowt = wp_awg;
	u8 op;

	FC_WPOWT_DBG(wpowt, "Weceived a WOGO %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		wetuwn;

	mutex_wock(&wpowt->wp_mutex);

	if (wpowt->state != WPOWT_ST_WOGO) {
		FC_WPOWT_DBG(wpowt, "Weceived a WOGO wesponse, but in state "
			     "%s\n", fc_wpowt_state(wpowt));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wpowt, fp);
		goto eww;
	}

	op = fc_fwame_paywoad_op(fp);
	if (op == EWS_WS_ACC)
		fc_wpowt_entew_disabwed(wpowt);
	ewse
		fc_wpowt_ewwow(wpowt, fp);

out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_wpowt_wogo_wesp);

/**
 * fc_wpowt_entew_wogo() - Wogout of the fabwic
 * @wpowt: The wocaw powt to be wogged out
 */
static void fc_wpowt_entew_wogo(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fwame *fp;
	stwuct fc_ews_wogo *wogo;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed WOGO state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_WOGO);
	fc_vpowts_winkchange(wpowt);

	fp = fc_fwame_awwoc(wpowt, sizeof(*wogo));
	if (!fp) {
		fc_wpowt_ewwow(wpowt, fp);
		wetuwn;
	}

	if (!wpowt->tt.ewsct_send(wpowt, FC_FID_FWOGI, fp, EWS_WOGO,
				  fc_wpowt_wogo_wesp, wpowt,
				  2 * wpowt->w_a_tov))
		fc_wpowt_ewwow(wpowt, NUWW);
}

/**
 * fc_wpowt_fwogi_wesp() - Handwe wesponse to FWOGI wequest
 * @sp:	    The sequence that the FWOGI was on
 * @fp:	    The FWOGI wesponse fwame
 * @wp_awg: The wpowt powt that weceived the FWOGI wesponse
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow()
 * and then unwock the wpowt.
 */
void fc_wpowt_fwogi_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			 void *wp_awg)
{
	stwuct fc_wpowt *wpowt = wp_awg;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ews_fwogi *fwp;
	u32 did;
	u16 csp_fwags;
	unsigned int w_a_tov;
	unsigned int e_d_tov;
	u16 mfs;

	FC_WPOWT_DBG(wpowt, "Weceived a FWOGI %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		wetuwn;

	mutex_wock(&wpowt->wp_mutex);

	if (wpowt->state != WPOWT_ST_FWOGI) {
		FC_WPOWT_DBG(wpowt, "Weceived a FWOGI wesponse, but in state "
			     "%s\n", fc_wpowt_state(wpowt));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wpowt, fp);
		goto eww;
	}

	fh = fc_fwame_headew_get(fp);
	did = fc_fwame_did(fp);
	if (fh->fh_w_ctw != FC_WCTW_EWS_WEP || did == 0 ||
	    fc_fwame_paywoad_op(fp) != EWS_WS_ACC) {
		FC_WPOWT_DBG(wpowt, "FWOGI not accepted ow bad wesponse\n");
		fc_wpowt_ewwow(wpowt, fp);
		goto out;
	}

	fwp = fc_fwame_paywoad_get(fp, sizeof(*fwp));
	if (!fwp) {
		FC_WPOWT_DBG(wpowt, "FWOGI bad wesponse\n");
		fc_wpowt_ewwow(wpowt, fp);
		goto out;
	}

	mfs = ntohs(fwp->fw_csp.sp_bb_data) &
		FC_SP_BB_DATA_MASK;

	if (mfs < FC_SP_MIN_MAX_PAYWOAD || mfs > FC_SP_MAX_MAX_PAYWOAD) {
		FC_WPOWT_DBG(wpowt, "FWOGI bad mfs:%hu wesponse, "
			     "wpowt->mfs:%u\n", mfs, wpowt->mfs);
		fc_wpowt_ewwow(wpowt, fp);
		goto out;
	}

	if (mfs <= wpowt->mfs) {
		wpowt->mfs = mfs;
		fc_host_maxfwame_size(wpowt->host) = mfs;
	}

	csp_fwags = ntohs(fwp->fw_csp.sp_featuwes);
	w_a_tov = ntohw(fwp->fw_csp.sp_w_a_tov);
	e_d_tov = ntohw(fwp->fw_csp.sp_e_d_tov);
	if (csp_fwags & FC_SP_FT_EDTW)
		e_d_tov /= 1000000;

	wpowt->npiv_enabwed = !!(csp_fwags & FC_SP_FT_NPIV_ACC);

	if ((csp_fwags & FC_SP_FT_FPOWT) == 0) {
		if (e_d_tov > wpowt->e_d_tov)
			wpowt->e_d_tov = e_d_tov;
		wpowt->w_a_tov = 2 * wpowt->e_d_tov;
		fc_wpowt_set_powt_id(wpowt, did, fp);
		pwintk(KEWN_INFO "host%d: wibfc: "
		       "Powt (%6.6x) entewed "
		       "point-to-point mode\n",
		       wpowt->host->host_no, did);
		fc_wpowt_ptp_setup(wpowt, fc_fwame_sid(fp),
				   get_unawigned_be64(
					   &fwp->fw_wwpn),
				   get_unawigned_be64(
					   &fwp->fw_wwnn));
	} ewse {
		if (e_d_tov > wpowt->e_d_tov)
			wpowt->e_d_tov = e_d_tov;
		if (w_a_tov > wpowt->w_a_tov)
			wpowt->w_a_tov = w_a_tov;
		fc_host_fabwic_name(wpowt->host) =
			get_unawigned_be64(&fwp->fw_wwnn);
		fc_wpowt_set_powt_id(wpowt, did, fp);
		fc_wpowt_entew_dns(wpowt);
	}

out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wpowt->wp_mutex);
}
EXPOWT_SYMBOW(fc_wpowt_fwogi_wesp);

/**
 * fc_wpowt_entew_fwogi() - Send a FWOGI wequest to the fabwic managew
 * @wpowt: Fibwe Channew wocaw powt to be wogged in to the fabwic
 */
static void fc_wpowt_entew_fwogi(stwuct fc_wpowt *wpowt)
{
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wpowt, "Entewed FWOGI state fwom %s state\n",
		     fc_wpowt_state(wpowt));

	fc_wpowt_state_entew(wpowt, WPOWT_ST_FWOGI);

	if (wpowt->point_to_muwtipoint) {
		if (wpowt->powt_id)
			fc_wpowt_entew_weady(wpowt);
		wetuwn;
	}

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_fwogi));
	if (!fp)
		wetuwn fc_wpowt_ewwow(wpowt, fp);

	if (!wpowt->tt.ewsct_send(wpowt, FC_FID_FWOGI, fp,
				  wpowt->vpowt ? EWS_FDISC : EWS_FWOGI,
				  fc_wpowt_fwogi_wesp, wpowt,
				  wpowt->vpowt ? 2 * wpowt->w_a_tov :
				  wpowt->e_d_tov))
		fc_wpowt_ewwow(wpowt, NUWW);
}

/**
 * fc_wpowt_config() - Configuwe a fc_wpowt
 * @wpowt: The wocaw powt to be configuwed
 */
int fc_wpowt_config(stwuct fc_wpowt *wpowt)
{
	INIT_DEWAYED_WOWK(&wpowt->wetwy_wowk, fc_wpowt_timeout);
	mutex_init(&wpowt->wp_mutex);

	fc_wpowt_state_entew(wpowt, WPOWT_ST_DISABWED);

	fc_wpowt_add_fc4_type(wpowt, FC_TYPE_FCP);
	fc_wpowt_add_fc4_type(wpowt, FC_TYPE_CT);
	fc_fc4_conf_wpowt_pawams(wpowt, FC_TYPE_FCP);

	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_config);

/**
 * fc_wpowt_init() - Initiawize the wpowt wayew fow a wocaw powt
 * @wpowt: The wocaw powt to initiawize the exchange wayew fow
 */
int fc_wpowt_init(stwuct fc_wpowt *wpowt)
{
	stwuct fc_host_attws *fc_host;

	fc_host = shost_to_fc_host(wpowt->host);

	/* Set FDMI vewsion to FDMI-2 specification*/
	fc_host->fdmi_vewsion = FDMI_V2;

	fc_host_powt_type(wpowt->host) = FC_POWTTYPE_NPOWT;
	fc_host_node_name(wpowt->host) = wpowt->wwnn;
	fc_host_powt_name(wpowt->host) = wpowt->wwpn;
	fc_host_suppowted_cwasses(wpowt->host) = FC_COS_CWASS3;
	memset(fc_host_suppowted_fc4s(wpowt->host), 0,
	       sizeof(fc_host_suppowted_fc4s(wpowt->host)));
	fc_host_suppowted_fc4s(wpowt->host)[2] = 1;
	fc_host_suppowted_fc4s(wpowt->host)[7] = 1;
	fc_host_num_discovewed_powts(wpowt->host) = 4;

	/* This vawue is awso unchanging */
	memset(fc_host_active_fc4s(wpowt->host), 0,
	       sizeof(fc_host_active_fc4s(wpowt->host)));
	fc_host_active_fc4s(wpowt->host)[2] = 1;
	fc_host_active_fc4s(wpowt->host)[7] = 1;
	fc_host_maxfwame_size(wpowt->host) = wpowt->mfs;
	fc_host_suppowted_speeds(wpowt->host) = 0;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_1GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_1GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_10GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_10GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_40GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_40GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_100GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_100GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_25GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_25GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_50GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_50GBIT;
	if (wpowt->wink_suppowted_speeds & FC_POWTSPEED_100GBIT)
		fc_host_suppowted_speeds(wpowt->host) |= FC_POWTSPEED_100GBIT;

	fc_fc4_add_wpowt(wpowt);

	fc_host_num_discovewed_powts(wpowt->host) = DISCOVEWED_POWTS;
	fc_host_powt_state(wpowt->host) = FC_POWTSTATE_ONWINE;
	fc_host_max_ct_paywoad(wpowt->host) = MAX_CT_PAYWOAD;
	fc_host_num_powts(wpowt->host) = NUMBEW_OF_POWTS;
	fc_host_bootbios_state(wpowt->host) = 0X00000000;
	snpwintf(fc_host_bootbios_vewsion(wpowt->host),
		FC_SYMBOWIC_NAME_SIZE, "%s", "Unknown");

	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_init);

/**
 * fc_wpowt_bsg_wesp() - The common wesponse handwew fow FC Passthwough wequests
 * @sp:	      The sequence fow the FC Passthwough wesponse
 * @fp:	      The wesponse fwame
 * @info_awg: The BSG info that the wesponse is fow
 */
static void fc_wpowt_bsg_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			      void *info_awg)
{
	stwuct fc_bsg_info *info = info_awg;
	stwuct bsg_job *job = info->job;
	stwuct fc_bsg_wepwy *bsg_wepwy = job->wepwy;
	stwuct fc_wpowt *wpowt = info->wpowt;
	stwuct fc_fwame_headew *fh;
	size_t wen;
	void *buf;

	if (IS_EWW(fp)) {
		bsg_wepwy->wesuwt = (PTW_EWW(fp) == -FC_EX_CWOSED) ?
			-ECONNABOWTED : -ETIMEDOUT;
		job->wepwy_wen = sizeof(uint32_t);
		bsg_job_done(job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
		kfwee(info);
		wetuwn;
	}

	mutex_wock(&wpowt->wp_mutex);
	fh = fc_fwame_headew_get(fp);
	wen = fw_wen(fp) - sizeof(*fh);
	buf = fc_fwame_paywoad_get(fp, 0);

	if (fw_sof(fp) == FC_SOF_I3 && !ntohs(fh->fh_seq_cnt)) {
		/* Get the wesponse code fwom the fiwst fwame paywoad */
		unsigned showt cmd = (info->wsp_code == FC_FS_ACC) ?
			ntohs(((stwuct fc_ct_hdw *)buf)->ct_cmd) :
			(unsigned showt)fc_fwame_paywoad_op(fp);

		/* Save the wepwy status of the job */
		bsg_wepwy->wepwy_data.ctews_wepwy.status =
			(cmd == info->wsp_code) ?
			FC_CTEWS_STATUS_OK : FC_CTEWS_STATUS_WEJECT;
	}

	bsg_wepwy->wepwy_paywoad_wcv_wen +=
		fc_copy_buffew_to_sgwist(buf, wen, info->sg, &info->nents,
					 &info->offset, NUWW);

	if (fw_eof(fp) == FC_EOF_T &&
	    (ntoh24(fh->fh_f_ctw) & (FC_FC_WAST_SEQ | FC_FC_END_SEQ)) ==
	    (FC_FC_WAST_SEQ | FC_FC_END_SEQ)) {
		if (bsg_wepwy->wepwy_paywoad_wcv_wen >
		    job->wepwy_paywoad.paywoad_wen)
			bsg_wepwy->wepwy_paywoad_wcv_wen =
				job->wepwy_paywoad.paywoad_wen;
		bsg_wepwy->wesuwt = 0;
		bsg_job_done(job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
		kfwee(info);
	}
	fc_fwame_fwee(fp);
	mutex_unwock(&wpowt->wp_mutex);
}

/**
 * fc_wpowt_ews_wequest() - Send EWS passthwough wequest
 * @job:   The BSG Passthwough job
 * @wpowt: The wocaw powt sending the wequest
 * @did:   The destination powt id
 * @tov:   The timeout pewiod (in ms)
 */
static int fc_wpowt_ews_wequest(stwuct bsg_job *job,
				stwuct fc_wpowt *wpowt,
				u32 did, u32 tov)
{
	stwuct fc_bsg_info *info;
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *fh;
	chaw *pp;
	int wen;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	fp = fc_fwame_awwoc(wpowt, job->wequest_paywoad.paywoad_wen);
	if (!fp)
		wetuwn -ENOMEM;

	wen = job->wequest_paywoad.paywoad_wen;
	pp = fc_fwame_paywoad_get(fp, wen);

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt,
			  pp, wen);

	fh = fc_fwame_headew_get(fp);
	fh->fh_w_ctw = FC_WCTW_EWS_WEQ;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, wpowt->powt_id);
	fh->fh_type = FC_TYPE_EWS;
	hton24(fh->fh_f_ctw, FC_FCTW_WEQ);
	fh->fh_cs_ctw = 0;
	fh->fh_df_ctw = 0;
	fh->fh_pawm_offset = 0;

	info = kzawwoc(sizeof(stwuct fc_bsg_info), GFP_KEWNEW);
	if (!info) {
		fc_fwame_fwee(fp);
		wetuwn -ENOMEM;
	}

	info->job = job;
	info->wpowt = wpowt;
	info->wsp_code = EWS_WS_ACC;
	info->nents = job->wepwy_paywoad.sg_cnt;
	info->sg = job->wepwy_paywoad.sg_wist;

	if (!fc_exch_seq_send(wpowt, fp, fc_wpowt_bsg_wesp,
			      NUWW, info, tov)) {
		kfwee(info);
		wetuwn -ECOMM;
	}
	wetuwn 0;
}

/**
 * fc_wpowt_ct_wequest() - Send CT Passthwough wequest
 * @job:   The BSG Passthwough job
 * @wpowt: The wocaw powt sending the wequest
 * @did:   The destination FC-ID
 * @tov:   The timeout pewiod to wait fow the wesponse
 */
static int fc_wpowt_ct_wequest(stwuct bsg_job *job,
			       stwuct fc_wpowt *wpowt, u32 did, u32 tov)
{
	stwuct fc_bsg_info *info;
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ct_weq *ct;
	size_t wen;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ct_hdw) +
			    job->wequest_paywoad.paywoad_wen);
	if (!fp)
		wetuwn -ENOMEM;

	wen = job->wequest_paywoad.paywoad_wen;
	ct = fc_fwame_paywoad_get(fp, wen);

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt,
			  ct, wen);

	fh = fc_fwame_headew_get(fp);
	fh->fh_w_ctw = FC_WCTW_DD_UNSOW_CTW;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, wpowt->powt_id);
	fh->fh_type = FC_TYPE_CT;
	hton24(fh->fh_f_ctw, FC_FCTW_WEQ);
	fh->fh_cs_ctw = 0;
	fh->fh_df_ctw = 0;
	fh->fh_pawm_offset = 0;

	info = kzawwoc(sizeof(stwuct fc_bsg_info), GFP_KEWNEW);
	if (!info) {
		fc_fwame_fwee(fp);
		wetuwn -ENOMEM;
	}

	info->job = job;
	info->wpowt = wpowt;
	info->wsp_code = FC_FS_ACC;
	info->nents = job->wepwy_paywoad.sg_cnt;
	info->sg = job->wepwy_paywoad.sg_wist;

	if (!fc_exch_seq_send(wpowt, fp, fc_wpowt_bsg_wesp,
			      NUWW, info, tov)) {
		kfwee(info);
		wetuwn -ECOMM;
	}
	wetuwn 0;
}

/**
 * fc_wpowt_bsg_wequest() - The common entwy point fow sending
 *			    FC Passthwough wequests
 * @job: The BSG passthwough job
 */
int fc_wpowt_bsg_wequest(stwuct bsg_job *job)
{
	stwuct fc_bsg_wequest *bsg_wequest = job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = job->wepwy;
	stwuct Scsi_Host *shost = fc_bsg_to_shost(job);
	stwuct fc_wpowt *wpowt = shost_pwiv(shost);
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_pwiv *wdata;
	int wc = -EINVAW;
	u32 did, tov;

	bsg_wepwy->wepwy_paywoad_wcv_wen = 0;

	mutex_wock(&wpowt->wp_mutex);

	switch (bsg_wequest->msgcode) {
	case FC_BSG_WPT_EWS:
		wpowt = fc_bsg_to_wpowt(job);
		if (!wpowt)
			bweak;

		wdata = wpowt->dd_data;
		wc = fc_wpowt_ews_wequest(job, wpowt, wpowt->powt_id,
					  wdata->e_d_tov);
		bweak;

	case FC_BSG_WPT_CT:
		wpowt = fc_bsg_to_wpowt(job);
		if (!wpowt)
			bweak;

		wdata = wpowt->dd_data;
		wc = fc_wpowt_ct_wequest(job, wpowt, wpowt->powt_id,
					 wdata->e_d_tov);
		bweak;

	case FC_BSG_HST_CT:
		did = ntoh24(bsg_wequest->wqst_data.h_ct.powt_id);
		if (did == FC_FID_DIW_SEWV) {
			wdata = wpowt->dns_wdata;
			if (!wdata)
				bweak;
			tov = wdata->e_d_tov;
		} ewse {
			wdata = fc_wpowt_wookup(wpowt, did);
			if (!wdata)
				bweak;
			tov = wdata->e_d_tov;
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		}

		wc = fc_wpowt_ct_wequest(job, wpowt, did, tov);
		bweak;

	case FC_BSG_HST_EWS_NOWOGIN:
		did = ntoh24(bsg_wequest->wqst_data.h_ews.powt_id);
		wc = fc_wpowt_ews_wequest(job, wpowt, did, wpowt->e_d_tov);
		bweak;
	}

	mutex_unwock(&wpowt->wp_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW(fc_wpowt_bsg_wequest);
