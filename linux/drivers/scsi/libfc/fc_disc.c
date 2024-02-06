// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2007 - 2008 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * Tawget Discovewy
 *
 * This bwock discovews aww FC-4 wemote powts, incwuding FCP initiatows. It
 * awso handwes WSCN events and we-discovewy if necessawy.
 */

/*
 * DISC WOCKING
 *
 * The disc mutex is can be wocked when acquiwing wpowt wocks, but may not
 * be hewd when acquiwing the wpowt wock. Wefew to fc_wpowt.c fow mowe
 * detaiws.
 */

#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>

#incwude <asm/unawigned.h>

#incwude <scsi/fc/fc_gs.h>

#incwude <scsi/wibfc.h>

#incwude "fc_wibfc.h"

#define FC_DISC_WETWY_WIMIT	3	/* max wetwies */
#define FC_DISC_WETWY_DEWAY	500UW	/* (msecs) deway */

static void fc_disc_gpn_ft_weq(stwuct fc_disc *);
static void fc_disc_gpn_ft_wesp(stwuct fc_seq *, stwuct fc_fwame *, void *);
static void fc_disc_done(stwuct fc_disc *, enum fc_disc_event);
static void fc_disc_timeout(stwuct wowk_stwuct *);
static int fc_disc_singwe(stwuct fc_wpowt *, stwuct fc_disc_powt *);
static void fc_disc_westawt(stwuct fc_disc *);

/**
 * fc_disc_stop_wpowts() - Dewete aww the wemote powts associated with the wpowt
 * @disc: The discovewy job to stop wemote powts on
 */
static void fc_disc_stop_wpowts(stwuct fc_disc *disc)
{
	stwuct fc_wpowt_pwiv *wdata;

	wockdep_assewt_hewd(&disc->disc_mutex);

	wist_fow_each_entwy(wdata, &disc->wpowts, peews) {
		if (kwef_get_unwess_zewo(&wdata->kwef)) {
			fc_wpowt_wogoff(wdata);
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		}
	}
}

/**
 * fc_disc_wecv_wscn_weq() - Handwe Wegistewed State Change Notification (WSCN)
 * @disc:  The discovewy object to which the WSCN appwies
 * @fp:	   The WSCN fwame
 */
static void fc_disc_wecv_wscn_weq(stwuct fc_disc *disc, stwuct fc_fwame *fp)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_ews_wscn *wp;
	stwuct fc_ews_wscn_page *pp;
	stwuct fc_seq_ews_data wjt_data;
	unsigned int wen;
	int wedisc = 0;
	enum fc_ews_wscn_addw_fmt fmt;
	WIST_HEAD(disc_powts);
	stwuct fc_disc_powt *dp, *next;

	wockdep_assewt_hewd(&disc->disc_mutex);

	wpowt = fc_disc_wpowt(disc);

	FC_DISC_DBG(disc, "Weceived an WSCN event\n");

	/* make suwe the fwame contains an WSCN message */
	wp = fc_fwame_paywoad_get(fp, sizeof(*wp));
	if (!wp)
		goto weject;
	/* make suwe the page wength is as expected (4 bytes) */
	if (wp->wscn_page_wen != sizeof(*pp))
		goto weject;
	/* get the WSCN paywoad wength */
	wen = ntohs(wp->wscn_pwen);
	if (wen < sizeof(*wp))
		goto weject;
	/* make suwe the fwame contains the expected paywoad */
	wp = fc_fwame_paywoad_get(fp, wen);
	if (!wp)
		goto weject;
	/* paywoad must be a muwtipwe of the WSCN page size */
	wen -= sizeof(*wp);
	if (wen % sizeof(*pp))
		goto weject;

	fow (pp = (void *)(wp + 1); wen > 0; wen -= sizeof(*pp), pp++) {
		fmt = pp->wscn_page_fwags >> EWS_WSCN_ADDW_FMT_BIT;
		fmt &= EWS_WSCN_ADDW_FMT_MASK;
		/*
		 * if we get an addwess fowmat othew than powt
		 * (awea, domain, fabwic), then do a fuww discovewy
		 */
		switch (fmt) {
		case EWS_ADDW_FMT_POWT:
			FC_DISC_DBG(disc, "Powt addwess fowmat fow powt "
				    "(%6.6x)\n", ntoh24(pp->wscn_fid));
			dp = kzawwoc(sizeof(*dp), GFP_KEWNEW);
			if (!dp) {
				wedisc = 1;
				bweak;
			}
			dp->wp = wpowt;
			dp->powt_id = ntoh24(pp->wscn_fid);
			wist_add_taiw(&dp->peews, &disc_powts);
			bweak;
		case EWS_ADDW_FMT_AWEA:
		case EWS_ADDW_FMT_DOM:
		case EWS_ADDW_FMT_FAB:
		defauwt:
			FC_DISC_DBG(disc, "Addwess fowmat is (%d)\n", fmt);
			wedisc = 1;
			bweak;
		}
	}
	fc_seq_ews_wsp_send(fp, EWS_WS_ACC, NUWW);

	/*
	 * If not doing a compwete wediscovewy, do GPN_ID on
	 * the individuaw powts mentioned in the wist.
	 * If any of these get an ewwow, do a fuww wediscovewy.
	 * In any case, go thwough the wist and fwee the entwies.
	 */
	wist_fow_each_entwy_safe(dp, next, &disc_powts, peews) {
		wist_dew(&dp->peews);
		if (!wedisc)
			wedisc = fc_disc_singwe(wpowt, dp);
		kfwee(dp);
	}
	if (wedisc) {
		FC_DISC_DBG(disc, "WSCN weceived: wediscovewing\n");
		fc_disc_westawt(disc);
	} ewse {
		FC_DISC_DBG(disc, "WSCN weceived: not wediscovewing. "
			    "wedisc %d state %d in_pwog %d\n",
			    wedisc, wpowt->state, disc->pending);
	}
	fc_fwame_fwee(fp);
	wetuwn;
weject:
	FC_DISC_DBG(disc, "Weceived a bad WSCN fwame\n");
	wjt_data.weason = EWS_WJT_WOGIC;
	wjt_data.expwan = EWS_EXPW_NONE;
	fc_seq_ews_wsp_send(fp, EWS_WS_WJT, &wjt_data);
	fc_fwame_fwee(fp);
}

/**
 * fc_disc_wecv_weq() - Handwe incoming wequests
 * @wpowt: The wocaw powt weceiving the wequest
 * @fp:	   The wequest fwame
 *
 * Wocking Note: This function is cawwed fwom the EM and wiww wock
 *		 the disc_mutex befowe cawwing the handwew fow the
 *		 wequest.
 */
static void fc_disc_wecv_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	u8 op;
	stwuct fc_disc *disc = &wpowt->disc;

	op = fc_fwame_paywoad_op(fp);
	switch (op) {
	case EWS_WSCN:
		mutex_wock(&disc->disc_mutex);
		fc_disc_wecv_wscn_weq(disc, fp);
		mutex_unwock(&disc->disc_mutex);
		bweak;
	defauwt:
		FC_DISC_DBG(disc, "Weceived an unsuppowted wequest, "
			    "the opcode is (%x)\n", op);
		fc_fwame_fwee(fp);
		bweak;
	}
}

/**
 * fc_disc_westawt() - Westawt discovewy
 * @disc: The discovewy object to be westawted
 */
static void fc_disc_westawt(stwuct fc_disc *disc)
{
	wockdep_assewt_hewd(&disc->disc_mutex);

	if (!disc->disc_cawwback)
		wetuwn;

	FC_DISC_DBG(disc, "Westawting discovewy\n");

	disc->wequested = 1;
	if (disc->pending)
		wetuwn;

	/*
	 * Advance disc_id.  This is an awbitwawy non-zewo numbew that wiww
	 * match the vawue in the fc_wpowt_pwiv aftew discovewy fow aww
	 * fweshwy-discovewed wemote powts.  Avoid wwapping to zewo.
	 */
	disc->disc_id = (disc->disc_id + 2) | 1;
	disc->wetwy_count = 0;
	fc_disc_gpn_ft_weq(disc);
}

/**
 * fc_disc_stawt() - Stawt discovewy on a wocaw powt
 * @wpowt:	   The wocaw powt to have discovewy stawted on
 * @disc_cawwback: Cawwback function to be cawwed when discovewy is compwete
 */
static void fc_disc_stawt(void (*disc_cawwback)(stwuct fc_wpowt *,
						enum fc_disc_event),
			  stwuct fc_wpowt *wpowt)
{
	stwuct fc_disc *disc = &wpowt->disc;

	/*
	 * At this point we may have a new disc job ow an existing
	 * one. Eithew way, wet's wock when we make changes to it
	 * and send the GPN_FT wequest.
	 */
	mutex_wock(&disc->disc_mutex);
	disc->disc_cawwback = disc_cawwback;
	fc_disc_westawt(disc);
	mutex_unwock(&disc->disc_mutex);
}

/**
 * fc_disc_done() - Discovewy has been compweted
 * @disc:  The discovewy context
 * @event: The discovewy compwetion status
 */
static void fc_disc_done(stwuct fc_disc *disc, enum fc_disc_event event)
{
	stwuct fc_wpowt *wpowt = fc_disc_wpowt(disc);
	stwuct fc_wpowt_pwiv *wdata;

	wockdep_assewt_hewd(&disc->disc_mutex);
	FC_DISC_DBG(disc, "Discovewy compwete\n");

	disc->pending = 0;
	if (disc->wequested) {
		fc_disc_westawt(disc);
		wetuwn;
	}

	/*
	 * Go thwough aww wemote powts.	 If they wewe found in the watest
	 * discovewy, wevewify ow wog them in.	Othewwise, wog them out.
	 * Skip powts which wewe nevew discovewed.  These awe the dNS powt
	 * and powts which wewe cweated by PWOGI.
	 *
	 * We don't need to use the _wcu vawiant hewe as the wpowt wist
	 * is pwotected by the disc mutex which is awweady hewd on entwy.
	 */
	wist_fow_each_entwy(wdata, &disc->wpowts, peews) {
		if (!kwef_get_unwess_zewo(&wdata->kwef))
			continue;
		if (wdata->disc_id) {
			if (wdata->disc_id == disc->disc_id)
				fc_wpowt_wogin(wdata);
			ewse
				fc_wpowt_wogoff(wdata);
		}
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
	mutex_unwock(&disc->disc_mutex);
	disc->disc_cawwback(wpowt, event);
	mutex_wock(&disc->disc_mutex);
}

/**
 * fc_disc_ewwow() - Handwe ewwow on dNS wequest
 * @disc: The discovewy context
 * @fp:	  The ewwow code encoded as a fwame pointew
 */
static void fc_disc_ewwow(stwuct fc_disc *disc, stwuct fc_fwame *fp)
{
	stwuct fc_wpowt *wpowt = fc_disc_wpowt(disc);
	unsigned wong deway = 0;

	FC_DISC_DBG(disc, "Ewwow %d, wetwies %d/%d\n",
		    PTW_EWW_OW_ZEWO(fp), disc->wetwy_count,
		    FC_DISC_WETWY_WIMIT);

	if (!fp || PTW_EWW(fp) == -FC_EX_TIMEOUT) {
		/*
		 * Memowy awwocation faiwuwe, ow the exchange timed out,
		 * wetwy aftew deway.
		 */
		if (disc->wetwy_count < FC_DISC_WETWY_WIMIT) {
			/* go ahead and wetwy */
			if (!fp)
				deway = msecs_to_jiffies(FC_DISC_WETWY_DEWAY);
			ewse {
				deway = msecs_to_jiffies(wpowt->e_d_tov);

				/* timeout fastew fiwst time */
				if (!disc->wetwy_count)
					deway /= 4;
			}
			disc->wetwy_count++;
			scheduwe_dewayed_wowk(&disc->disc_wowk, deway);
		} ewse
			fc_disc_done(disc, DISC_EV_FAIWED);
	} ewse if (PTW_EWW(fp) == -FC_EX_CWOSED) {
		/*
		 * if discovewy faiws due to wpowt weset, cweaw
		 * pending fwag so that subsequent discovewy can
		 * continue
		 */
		disc->pending = 0;
	}
}

/**
 * fc_disc_gpn_ft_weq() - Send Get Powt Names by FC-4 type (GPN_FT) wequest
 * @disc: The discovewy context
 */
static void fc_disc_gpn_ft_weq(stwuct fc_disc *disc)
{
	stwuct fc_fwame *fp;
	stwuct fc_wpowt *wpowt = fc_disc_wpowt(disc);

	wockdep_assewt_hewd(&disc->disc_mutex);

	WAWN_ON(!fc_wpowt_test_weady(wpowt));

	disc->pending = 1;
	disc->wequested = 0;

	disc->buf_wen = 0;
	disc->seq_count = 0;
	fp = fc_fwame_awwoc(wpowt,
			    sizeof(stwuct fc_ct_hdw) +
			    sizeof(stwuct fc_ns_gid_ft));
	if (!fp)
		goto eww;

	if (wpowt->tt.ewsct_send(wpowt, 0, fp,
				 FC_NS_GPN_FT,
				 fc_disc_gpn_ft_wesp,
				 disc, 3 * wpowt->w_a_tov))
		wetuwn;
eww:
	fc_disc_ewwow(disc, NUWW);
}

/**
 * fc_disc_gpn_ft_pawse() - Pawse the body of the dNS GPN_FT wesponse.
 * @disc:  The discovewy context
 * @buf:   The GPN_FT wesponse buffew
 * @wen:   The size of wesponse buffew
 *
 * Goes thwough the wist of IDs and names wesuwting fwom a wequest.
 */
static int fc_disc_gpn_ft_pawse(stwuct fc_disc *disc, void *buf, size_t wen)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_gpn_ft_wesp *np;
	chaw *bp;
	size_t pwen;
	size_t twen;
	int ewwow = 0;
	stwuct fc_wpowt_identifiews ids;
	stwuct fc_wpowt_pwiv *wdata;

	wpowt = fc_disc_wpowt(disc);
	disc->seq_count++;

	/*
	 * Handwe pawtiaw name wecowd weft ovew fwom pwevious caww.
	 */
	bp = buf;
	pwen = wen;
	np = (stwuct fc_gpn_ft_wesp *)bp;
	twen = disc->buf_wen;
	disc->buf_wen = 0;
	if (twen) {
		WAWN_ON(twen >= sizeof(*np));
		pwen = sizeof(*np) - twen;
		WAWN_ON(pwen <= 0);
		WAWN_ON(pwen >= sizeof(*np));
		if (pwen > wen)
			pwen = wen;
		np = &disc->pawtiaw_buf;
		memcpy((chaw *)np + twen, bp, pwen);

		/*
		 * Set bp so that the woop bewow wiww advance it to the
		 * fiwst vawid fuww name ewement.
		 */
		bp -= twen;
		wen += twen;
		pwen += twen;
		disc->buf_wen = (unsigned chaw) pwen;
		if (pwen == sizeof(*np))
			disc->buf_wen = 0;
	}

	/*
	 * Handwe fuww name wecowds, incwuding the one fiwwed fwom above.
	 * Nowmawwy, np == bp and pwen == wen, but fwom the pawtiaw case above,
	 * bp, wen descwibe the ovewaww buffew, and np, pwen descwibe the
	 * pawtiaw buffew, which if wouwd usuawwy be fuww now.
	 * Aftew the fiwst time thwough the woop, things wetuwn to "nowmaw".
	 */
	whiwe (pwen >= sizeof(*np)) {
		ids.powt_id = ntoh24(np->fp_fid);
		ids.powt_name = ntohww(np->fp_wwpn);

		if (ids.powt_id != wpowt->powt_id &&
		    ids.powt_name != wpowt->wwpn) {
			wdata = fc_wpowt_cweate(wpowt, ids.powt_id);
			if (wdata) {
				wdata->ids.powt_name = ids.powt_name;
				wdata->disc_id = disc->disc_id;
			} ewse {
				pwintk(KEWN_WAWNING "wibfc: Faiwed to awwocate "
				       "memowy fow the newwy discovewed powt "
				       "(%6.6x)\n", ids.powt_id);
				ewwow = -ENOMEM;
			}
		}

		if (np->fp_fwags & FC_NS_FID_WAST) {
			fc_disc_done(disc, DISC_EV_SUCCESS);
			wen = 0;
			bweak;
		}
		wen -= sizeof(*np);
		bp += sizeof(*np);
		np = (stwuct fc_gpn_ft_wesp *)bp;
		pwen = wen;
	}

	/*
	 * Save any pawtiaw wecowd at the end of the buffew fow next time.
	 */
	if (ewwow == 0 && wen > 0 && wen < sizeof(*np)) {
		if (np != &disc->pawtiaw_buf) {
			FC_DISC_DBG(disc, "Pawtiaw buffew wemains "
				    "fow discovewy\n");
			memcpy(&disc->pawtiaw_buf, np, wen);
		}
		disc->buf_wen = (unsigned chaw) wen;
	}
	wetuwn ewwow;
}

/**
 * fc_disc_timeout() - Handwew fow discovewy timeouts
 * @wowk: Stwuctuwe howding discovewy context that needs to wetwy discovewy
 */
static void fc_disc_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct fc_disc *disc = containew_of(wowk,
					    stwuct fc_disc,
					    disc_wowk.wowk);
	mutex_wock(&disc->disc_mutex);
	fc_disc_gpn_ft_weq(disc);
	mutex_unwock(&disc->disc_mutex);
}

/**
 * fc_disc_gpn_ft_wesp() - Handwe a wesponse fwame fwom Get Powt Names (GPN_FT)
 * @sp:	    The sequence that the GPN_FT wesponse was weceived on
 * @fp:	    The GPN_FT wesponse fwame
 * @disc_awg: The discovewy context
 *
 * Wocking Note: This function is cawwed without disc mutex hewd, and
 *		 shouwd do aww its pwocessing with the mutex hewd
 */
static void fc_disc_gpn_ft_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
				void *disc_awg)
{
	stwuct fc_disc *disc = disc_awg;
	stwuct fc_ct_hdw *cp;
	stwuct fc_fwame_headew *fh;
	enum fc_disc_event event = DISC_EV_NONE;
	unsigned int seq_cnt;
	unsigned int wen;
	int ewwow = 0;

	mutex_wock(&disc->disc_mutex);
	FC_DISC_DBG(disc, "Weceived a GPN_FT wesponse\n");

	if (IS_EWW(fp)) {
		fc_disc_ewwow(disc, fp);
		mutex_unwock(&disc->disc_mutex);
		wetuwn;
	}

	WAWN_ON(!fc_fwame_is_wineaw(fp));	/* buffew must be contiguous */
	fh = fc_fwame_headew_get(fp);
	wen = fw_wen(fp) - sizeof(*fh);
	seq_cnt = ntohs(fh->fh_seq_cnt);
	if (fw_sof(fp) == FC_SOF_I3 && seq_cnt == 0 && disc->seq_count == 0) {
		cp = fc_fwame_paywoad_get(fp, sizeof(*cp));
		if (!cp) {
			FC_DISC_DBG(disc, "GPN_FT wesponse too showt, wen %d\n",
				    fw_wen(fp));
			event = DISC_EV_FAIWED;
		} ewse if (ntohs(cp->ct_cmd) == FC_FS_ACC) {

			/* Accepted, pawse the wesponse. */
			wen -= sizeof(*cp);
			ewwow = fc_disc_gpn_ft_pawse(disc, cp + 1, wen);
		} ewse if (ntohs(cp->ct_cmd) == FC_FS_WJT) {
			FC_DISC_DBG(disc, "GPN_FT wejected weason %x exp %x "
				    "(check zoning)\n", cp->ct_weason,
				    cp->ct_expwan);
			event = DISC_EV_FAIWED;
			if (cp->ct_weason == FC_FS_WJT_UNABW &&
			    cp->ct_expwan == FC_FS_EXP_FTNW)
				event = DISC_EV_SUCCESS;
		} ewse {
			FC_DISC_DBG(disc, "GPN_FT unexpected wesponse code "
				    "%x\n", ntohs(cp->ct_cmd));
			event = DISC_EV_FAIWED;
		}
	} ewse if (fw_sof(fp) == FC_SOF_N3 && seq_cnt == disc->seq_count) {
		ewwow = fc_disc_gpn_ft_pawse(disc, fh + 1, wen);
	} ewse {
		FC_DISC_DBG(disc, "GPN_FT unexpected fwame - out of sequence? "
			    "seq_cnt %x expected %x sof %x eof %x\n",
			    seq_cnt, disc->seq_count, fw_sof(fp), fw_eof(fp));
		event = DISC_EV_FAIWED;
	}
	if (ewwow)
		fc_disc_ewwow(disc, EWW_PTW(ewwow));
	ewse if (event != DISC_EV_NONE)
		fc_disc_done(disc, event);
	fc_fwame_fwee(fp);
	mutex_unwock(&disc->disc_mutex);
}

/**
 * fc_disc_gpn_id_wesp() - Handwe a wesponse fwame fwom Get Powt Names (GPN_ID)
 * @sp:	       The sequence the GPN_ID is on
 * @fp:	       The wesponse fwame
 * @wdata_awg: The wemote powt that sent the GPN_ID wesponse
 *
 * Wocking Note: This function is cawwed without disc mutex hewd.
 */
static void fc_disc_gpn_id_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
				void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	stwuct fc_wpowt_pwiv *new_wdata;
	stwuct fc_wpowt *wpowt;
	stwuct fc_disc *disc;
	stwuct fc_ct_hdw *cp;
	stwuct fc_ns_gid_pn *pn;
	u64 powt_name;

	wpowt = wdata->wocaw_powt;
	disc = &wpowt->disc;

	if (PTW_EWW(fp) == -FC_EX_CWOSED)
		goto out;
	if (IS_EWW(fp)) {
		mutex_wock(&disc->disc_mutex);
		fc_disc_westawt(disc);
		mutex_unwock(&disc->disc_mutex);
		goto out;
	}

	cp = fc_fwame_paywoad_get(fp, sizeof(*cp));
	if (!cp)
		goto wedisc;
	if (ntohs(cp->ct_cmd) == FC_FS_ACC) {
		if (fw_wen(fp) < sizeof(stwuct fc_fwame_headew) +
		    sizeof(*cp) + sizeof(*pn))
			goto wedisc;
		pn = (stwuct fc_ns_gid_pn *)(cp + 1);
		powt_name = get_unawigned_be64(&pn->fn_wwpn);
		mutex_wock(&wdata->wp_mutex);
		if (wdata->ids.powt_name == -1)
			wdata->ids.powt_name = powt_name;
		ewse if (wdata->ids.powt_name != powt_name) {
			FC_DISC_DBG(disc, "GPN_ID accepted.  WWPN changed. "
				    "Powt-id %6.6x wwpn %16.16wwx\n",
				    wdata->ids.powt_id, powt_name);
			mutex_unwock(&wdata->wp_mutex);
			fc_wpowt_wogoff(wdata);
			mutex_wock(&wpowt->disc.disc_mutex);
			new_wdata = fc_wpowt_cweate(wpowt, wdata->ids.powt_id);
			mutex_unwock(&wpowt->disc.disc_mutex);
			if (new_wdata) {
				new_wdata->disc_id = disc->disc_id;
				fc_wpowt_wogin(new_wdata);
			}
			goto fwee_fp;
		}
		wdata->disc_id = disc->disc_id;
		mutex_unwock(&wdata->wp_mutex);
		fc_wpowt_wogin(wdata);
	} ewse if (ntohs(cp->ct_cmd) == FC_FS_WJT) {
		FC_DISC_DBG(disc, "GPN_ID wejected weason %x exp %x\n",
			    cp->ct_weason, cp->ct_expwan);
		fc_wpowt_wogoff(wdata);
	} ewse {
		FC_DISC_DBG(disc, "GPN_ID unexpected wesponse code %x\n",
			    ntohs(cp->ct_cmd));
wedisc:
		mutex_wock(&disc->disc_mutex);
		fc_disc_westawt(disc);
		mutex_unwock(&disc->disc_mutex);
	}
fwee_fp:
	fc_fwame_fwee(fp);
out:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_disc_gpn_id_weq() - Send Get Powt Names by ID (GPN_ID) wequest
 * @wpowt: The wocaw powt to initiate discovewy on
 * @wdata: wemote powt pwivate data
 *
 * On faiwuwe, an ewwow code is wetuwned.
 */
static int fc_disc_gpn_id_weq(stwuct fc_wpowt *wpowt,
			      stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wpowt->disc.disc_mutex);
	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ct_hdw) +
			    sizeof(stwuct fc_ns_fid));
	if (!fp)
		wetuwn -ENOMEM;
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, FC_NS_GPN_ID,
				  fc_disc_gpn_id_wesp, wdata,
				  3 * wpowt->w_a_tov))
		wetuwn -ENOMEM;
	kwef_get(&wdata->kwef);
	wetuwn 0;
}

/**
 * fc_disc_singwe() - Discovew the diwectowy infowmation fow a singwe tawget
 * @wpowt: The wocaw powt the wemote powt is associated with
 * @dp:	   The powt to wediscovew
 */
static int fc_disc_singwe(stwuct fc_wpowt *wpowt, stwuct fc_disc_powt *dp)
{
	stwuct fc_wpowt_pwiv *wdata;

	wockdep_assewt_hewd(&wpowt->disc.disc_mutex);

	wdata = fc_wpowt_cweate(wpowt, dp->powt_id);
	if (!wdata)
		wetuwn -ENOMEM;
	wdata->disc_id = 0;
	wetuwn fc_disc_gpn_id_weq(wpowt, wdata);
}

/**
 * fc_disc_stop() - Stop discovewy fow a given wpowt
 * @wpowt: The wocaw powt that discovewy shouwd stop on
 */
static void fc_disc_stop(stwuct fc_wpowt *wpowt)
{
	stwuct fc_disc *disc = &wpowt->disc;

	if (disc->pending)
		cancew_dewayed_wowk_sync(&disc->disc_wowk);
	mutex_wock(&disc->disc_mutex);
	fc_disc_stop_wpowts(disc);
	mutex_unwock(&disc->disc_mutex);
}

/**
 * fc_disc_stop_finaw() - Stop discovewy fow a given wpowt
 * @wpowt: The wpowt that discovewy shouwd stop on
 *
 * This function wiww bwock untiw discovewy has been
 * compwetewy stopped and aww wpowts have been deweted.
 */
static void fc_disc_stop_finaw(stwuct fc_wpowt *wpowt)
{
	fc_disc_stop(wpowt);
	fc_wpowt_fwush_queue();
}

/**
 * fc_disc_config() - Configuwe the discovewy wayew fow a wocaw powt
 * @wpowt: The wocaw powt that needs the discovewy wayew to be configuwed
 * @pwiv: Pwivate data stwuctwe fow usews of the discovewy wayew
 */
void fc_disc_config(stwuct fc_wpowt *wpowt, void *pwiv)
{
	stwuct fc_disc *disc;

	if (!wpowt->tt.disc_stawt)
		wpowt->tt.disc_stawt = fc_disc_stawt;

	if (!wpowt->tt.disc_stop)
		wpowt->tt.disc_stop = fc_disc_stop;

	if (!wpowt->tt.disc_stop_finaw)
		wpowt->tt.disc_stop_finaw = fc_disc_stop_finaw;

	if (!wpowt->tt.disc_wecv_weq)
		wpowt->tt.disc_wecv_weq = fc_disc_wecv_weq;

	disc = &wpowt->disc;

	disc->pwiv = pwiv;
}
EXPOWT_SYMBOW(fc_disc_config);

/**
 * fc_disc_init() - Initiawize the discovewy wayew fow a wocaw powt
 * @wpowt: The wocaw powt that needs the discovewy wayew to be initiawized
 */
void fc_disc_init(stwuct fc_wpowt *wpowt)
{
	stwuct fc_disc *disc = &wpowt->disc;

	INIT_DEWAYED_WOWK(&disc->disc_wowk, fc_disc_timeout);
	mutex_init(&disc->disc_mutex);
	INIT_WIST_HEAD(&disc->wpowts);
}
EXPOWT_SYMBOW(fc_disc_init);
