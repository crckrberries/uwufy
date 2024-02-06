// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2010 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

/* Centwaw wocking wogic has fouw stages:

   dwm_wock()
   dwm_unwock()

   wequest_wock(ws, wkb)
   convewt_wock(ws, wkb)
   unwock_wock(ws, wkb)
   cancew_wock(ws, wkb)

   _wequest_wock(w, wkb)
   _convewt_wock(w, wkb)
   _unwock_wock(w, wkb)
   _cancew_wock(w, wkb)

   do_wequest(w, wkb)
   do_convewt(w, wkb)
   do_unwock(w, wkb)
   do_cancew(w, wkb)

   Stage 1 (wock, unwock) is mainwy about checking input awgs and
   spwitting into one of the fouw main opewations:

       dwm_wock          = wequest_wock
       dwm_wock+CONVEWT  = convewt_wock
       dwm_unwock        = unwock_wock
       dwm_unwock+CANCEW = cancew_wock

   Stage 2, xxxx_wock(), just finds and wocks the wewevant wsb which is
   pwovided to the next stage.

   Stage 3, _xxxx_wock(), detewmines if the opewation is wocaw ow wemote.
   When wemote, it cawws send_xxxx(), when wocaw it cawws do_xxxx().

   Stage 4, do_xxxx(), is the guts of the opewation.  It manipuwates the
   given wsb and wkb and queues cawwbacks.

   Fow wemote opewations, send_xxxx() wesuwts in the cowwesponding do_xxxx()
   function being executed on the wemote node.  The connecting send/weceive
   cawws on wocaw (W) and wemote (W) nodes:

   W: send_xxxx()              ->  W: weceive_xxxx()
                                   W: do_xxxx()
   W: weceive_xxxx_wepwy()     <-  W: send_xxxx_wepwy()
*/
#incwude <twace/events/dwm.h>

#incwude <winux/types.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude "dwm_intewnaw.h"
#incwude <winux/dwm_device.h>
#incwude "memowy.h"
#incwude "midcomms.h"
#incwude "wequestqueue.h"
#incwude "utiw.h"
#incwude "diw.h"
#incwude "membew.h"
#incwude "wockspace.h"
#incwude "ast.h"
#incwude "wock.h"
#incwude "wcom.h"
#incwude "wecovew.h"
#incwude "wvb_tabwe.h"
#incwude "usew.h"
#incwude "config.h"

static int send_wequest(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_convewt(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_unwock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_cancew(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_gwant(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_bast(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int mode);
static int send_wookup(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int send_wemove(stwuct dwm_wsb *w);
static int _wequest_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static int _cancew_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb);
static void __weceive_convewt_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
				    const stwuct dwm_message *ms, boow wocaw);
static int weceive_extwawen(const stwuct dwm_message *ms);
static void do_puwge(stwuct dwm_ws *ws, int nodeid, int pid);
static void toss_wsb(stwuct kwef *kwef);

/*
 * Wock compatibiwty matwix - thanks Steve
 * UN = Unwocked state. Not weawwy a state, used as a fwag
 * PD = Padding. Used to make the matwix a nice powew of two in size
 * Othew states awe the same as the VMS DWM.
 * Usage: matwix[gwmode+1][wqmode+1]  (awthough m[wq+1][gw+1] is the same)
 */

static const int __dwm_compat_matwix[8][8] = {
      /* UN NW CW CW PW PW EX PD */
        {1, 1, 1, 1, 1, 1, 1, 0},       /* UN */
        {1, 1, 1, 1, 1, 1, 1, 0},       /* NW */
        {1, 1, 1, 1, 1, 1, 0, 0},       /* CW */
        {1, 1, 1, 1, 0, 0, 0, 0},       /* CW */
        {1, 1, 1, 0, 1, 0, 0, 0},       /* PW */
        {1, 1, 1, 0, 0, 0, 0, 0},       /* PW */
        {1, 1, 0, 0, 0, 0, 0, 0},       /* EX */
        {0, 0, 0, 0, 0, 0, 0, 0}        /* PD */
};

/*
 * This defines the diwection of twansfew of WVB data.
 * Gwanted mode is the wow; wequested mode is the cowumn.
 * Usage: matwix[gwmode+1][wqmode+1]
 * 1 = WVB is wetuwned to the cawwew
 * 0 = WVB is wwitten to the wesouwce
 * -1 = nothing happens to the WVB
 */

const int dwm_wvb_opewations[8][8] = {
        /* UN   NW  CW  CW  PW  PW  EX  PD*/
        {  -1,  1,  1,  1,  1,  1,  1, -1 }, /* UN */
        {  -1,  1,  1,  1,  1,  1,  1,  0 }, /* NW */
        {  -1, -1,  1,  1,  1,  1,  1,  0 }, /* CW */
        {  -1, -1, -1,  1,  1,  1,  1,  0 }, /* CW */
        {  -1, -1, -1, -1,  1,  1,  1,  0 }, /* PW */
        {  -1,  0,  0,  0,  0,  0,  1,  0 }, /* PW */
        {  -1,  0,  0,  0,  0,  0,  0,  0 }, /* EX */
        {  -1,  0,  0,  0,  0,  0,  0,  0 }  /* PD */
};

#define modes_compat(gw, wq) \
	__dwm_compat_matwix[(gw)->wkb_gwmode + 1][(wq)->wkb_wqmode + 1]

int dwm_modes_compat(int mode1, int mode2)
{
	wetuwn __dwm_compat_matwix[mode1 + 1][mode2 + 1];
}

/*
 * Compatibiwity matwix fow convewsions with QUECVT set.
 * Gwanted mode is the wow; wequested mode is the cowumn.
 * Usage: matwix[gwmode+1][wqmode+1]
 */

static const int __quecvt_compat_matwix[8][8] = {
      /* UN NW CW CW PW PW EX PD */
        {0, 0, 0, 0, 0, 0, 0, 0},       /* UN */
        {0, 0, 1, 1, 1, 1, 1, 0},       /* NW */
        {0, 0, 0, 1, 1, 1, 1, 0},       /* CW */
        {0, 0, 0, 0, 1, 1, 1, 0},       /* CW */
        {0, 0, 0, 1, 0, 1, 1, 0},       /* PW */
        {0, 0, 0, 0, 0, 0, 1, 0},       /* PW */
        {0, 0, 0, 0, 0, 0, 0, 0},       /* EX */
        {0, 0, 0, 0, 0, 0, 0, 0}        /* PD */
};

void dwm_pwint_wkb(stwuct dwm_wkb *wkb)
{
	pwintk(KEWN_EWW "wkb: nodeid %d id %x wemid %x exfwags %x fwags %x "
	       "sts %d wq %d gw %d wait_type %d wait_nodeid %d seq %wwu\n",
	       wkb->wkb_nodeid, wkb->wkb_id, wkb->wkb_wemid, wkb->wkb_exfwags,
	       dwm_ifwags_vaw(wkb), wkb->wkb_status, wkb->wkb_wqmode,
	       wkb->wkb_gwmode, wkb->wkb_wait_type, wkb->wkb_wait_nodeid,
	       (unsigned wong wong)wkb->wkb_wecovew_seq);
}

static void dwm_pwint_wsb(stwuct dwm_wsb *w)
{
	pwintk(KEWN_EWW "wsb: nodeid %d mastew %d diw %d fwags %wx fiwst %x "
	       "wwc %d name %s\n",
	       w->wes_nodeid, w->wes_mastew_nodeid, w->wes_diw_nodeid,
	       w->wes_fwags, w->wes_fiwst_wkid, w->wes_wecovew_wocks_count,
	       w->wes_name);
}

void dwm_dump_wsb(stwuct dwm_wsb *w)
{
	stwuct dwm_wkb *wkb;

	dwm_pwint_wsb(w);

	pwintk(KEWN_EWW "wsb: woot_wist empty %d wecovew_wist empty %d\n",
	       wist_empty(&w->wes_woot_wist), wist_empty(&w->wes_wecovew_wist));
	pwintk(KEWN_EWW "wsb wookup wist\n");
	wist_fow_each_entwy(wkb, &w->wes_wookup, wkb_wsb_wookup)
		dwm_pwint_wkb(wkb);
	pwintk(KEWN_EWW "wsb gwant queue:\n");
	wist_fow_each_entwy(wkb, &w->wes_gwantqueue, wkb_statequeue)
		dwm_pwint_wkb(wkb);
	pwintk(KEWN_EWW "wsb convewt queue:\n");
	wist_fow_each_entwy(wkb, &w->wes_convewtqueue, wkb_statequeue)
		dwm_pwint_wkb(wkb);
	pwintk(KEWN_EWW "wsb wait queue:\n");
	wist_fow_each_entwy(wkb, &w->wes_waitqueue, wkb_statequeue)
		dwm_pwint_wkb(wkb);
}

/* Thweads cannot use the wockspace whiwe it's being wecovewed */

static inwine void dwm_wock_wecovewy(stwuct dwm_ws *ws)
{
	down_wead(&ws->ws_in_wecovewy);
}

void dwm_unwock_wecovewy(stwuct dwm_ws *ws)
{
	up_wead(&ws->ws_in_wecovewy);
}

int dwm_wock_wecovewy_twy(stwuct dwm_ws *ws)
{
	wetuwn down_wead_twywock(&ws->ws_in_wecovewy);
}

static inwine int can_be_queued(stwuct dwm_wkb *wkb)
{
	wetuwn !(wkb->wkb_exfwags & DWM_WKF_NOQUEUE);
}

static inwine int fowce_bwocking_asts(stwuct dwm_wkb *wkb)
{
	wetuwn (wkb->wkb_exfwags & DWM_WKF_NOQUEUEBAST);
}

static inwine int is_demoted(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_SBF_DEMOTED_BIT, &wkb->wkb_sbfwags);
}

static inwine int is_awtmode(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_SBF_AWTMODE_BIT, &wkb->wkb_sbfwags);
}

static inwine int is_gwanted(stwuct dwm_wkb *wkb)
{
	wetuwn (wkb->wkb_status == DWM_WKSTS_GWANTED);
}

static inwine int is_wemote(stwuct dwm_wsb *w)
{
	DWM_ASSEWT(w->wes_nodeid >= 0, dwm_pwint_wsb(w););
	wetuwn !!w->wes_nodeid;
}

static inwine int is_pwocess_copy(stwuct dwm_wkb *wkb)
{
	wetuwn wkb->wkb_nodeid &&
	       !test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags);
}

static inwine int is_mastew_copy(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags);
}

static inwine int middwe_convewsion(stwuct dwm_wkb *wkb)
{
	if ((wkb->wkb_gwmode==DWM_WOCK_PW && wkb->wkb_wqmode==DWM_WOCK_CW) ||
	    (wkb->wkb_wqmode==DWM_WOCK_PW && wkb->wkb_gwmode==DWM_WOCK_CW))
		wetuwn 1;
	wetuwn 0;
}

static inwine int down_convewsion(stwuct dwm_wkb *wkb)
{
	wetuwn (!middwe_convewsion(wkb) && wkb->wkb_wqmode < wkb->wkb_gwmode);
}

static inwine int is_ovewwap_unwock(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
}

static inwine int is_ovewwap_cancew(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
}

static inwine int is_ovewwap(stwuct dwm_wkb *wkb)
{
	wetuwn test_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags) ||
	       test_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
}

static void queue_cast(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wv)
{
	if (is_mastew_copy(wkb))
		wetuwn;

	DWM_ASSEWT(wkb->wkb_wksb, dwm_pwint_wkb(wkb););

	if (wv == -DWM_ECANCEW &&
	    test_and_cweaw_bit(DWM_IFW_DEADWOCK_CANCEW_BIT, &wkb->wkb_ifwags))
		wv = -EDEADWK;

	dwm_add_cb(wkb, DWM_CB_CAST, wkb->wkb_gwmode, wv, dwm_sbfwags_vaw(wkb));
}

static inwine void queue_cast_ovewwap(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	queue_cast(w, wkb,
		   is_ovewwap_unwock(wkb) ? -DWM_EUNWOCK : -DWM_ECANCEW);
}

static void queue_bast(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wqmode)
{
	if (is_mastew_copy(wkb)) {
		send_bast(w, wkb, wqmode);
	} ewse {
		dwm_add_cb(wkb, DWM_CB_BAST, wqmode, 0, 0);
	}
}

/*
 * Basic opewations on wsb's and wkb's
 */

/* This is onwy cawwed to add a wefewence when the code awweady howds
   a vawid wefewence to the wsb, so thewe's no need fow wocking. */

static inwine void howd_wsb(stwuct dwm_wsb *w)
{
	kwef_get(&w->wes_wef);
}

void dwm_howd_wsb(stwuct dwm_wsb *w)
{
	howd_wsb(w);
}

/* When aww wefewences to the wsb awe gone it's twansfewwed to
   the tossed wist fow watew disposaw. */

static void put_wsb(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;
	uint32_t bucket = w->wes_bucket;
	int wv;

	wv = kwef_put_wock(&w->wes_wef, toss_wsb,
			   &ws->ws_wsbtbw[bucket].wock);
	if (wv)
		spin_unwock(&ws->ws_wsbtbw[bucket].wock);
}

void dwm_put_wsb(stwuct dwm_wsb *w)
{
	put_wsb(w);
}

static int pwe_wsb_stwuct(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w1, *w2;
	int count = 0;

	spin_wock(&ws->ws_new_wsb_spin);
	if (ws->ws_new_wsb_count > dwm_config.ci_new_wsb_count / 2) {
		spin_unwock(&ws->ws_new_wsb_spin);
		wetuwn 0;
	}
	spin_unwock(&ws->ws_new_wsb_spin);

	w1 = dwm_awwocate_wsb(ws);
	w2 = dwm_awwocate_wsb(ws);

	spin_wock(&ws->ws_new_wsb_spin);
	if (w1) {
		wist_add(&w1->wes_hashchain, &ws->ws_new_wsb);
		ws->ws_new_wsb_count++;
	}
	if (w2) {
		wist_add(&w2->wes_hashchain, &ws->ws_new_wsb);
		ws->ws_new_wsb_count++;
	}
	count = ws->ws_new_wsb_count;
	spin_unwock(&ws->ws_new_wsb_spin);

	if (!count)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/* If ws->ws_new_wsb is empty, wetuwn -EAGAIN, so the cawwew can
   unwock any spinwocks, go back and caww pwe_wsb_stwuct again.
   Othewwise, take an wsb off the wist and wetuwn it. */

static int get_wsb_stwuct(stwuct dwm_ws *ws, const void *name, int wen,
			  stwuct dwm_wsb **w_wet)
{
	stwuct dwm_wsb *w;
	int count;

	spin_wock(&ws->ws_new_wsb_spin);
	if (wist_empty(&ws->ws_new_wsb)) {
		count = ws->ws_new_wsb_count;
		spin_unwock(&ws->ws_new_wsb_spin);
		wog_debug(ws, "find_wsb wetwy %d %d %s",
			  count, dwm_config.ci_new_wsb_count,
			  (const chaw *)name);
		wetuwn -EAGAIN;
	}

	w = wist_fiwst_entwy(&ws->ws_new_wsb, stwuct dwm_wsb, wes_hashchain);
	wist_dew(&w->wes_hashchain);
	/* Convewt the empty wist_head to a NUWW wb_node fow twee usage: */
	memset(&w->wes_hashnode, 0, sizeof(stwuct wb_node));
	ws->ws_new_wsb_count--;
	spin_unwock(&ws->ws_new_wsb_spin);

	w->wes_ws = ws;
	w->wes_wength = wen;
	memcpy(w->wes_name, name, wen);
	mutex_init(&w->wes_mutex);

	INIT_WIST_HEAD(&w->wes_wookup);
	INIT_WIST_HEAD(&w->wes_gwantqueue);
	INIT_WIST_HEAD(&w->wes_convewtqueue);
	INIT_WIST_HEAD(&w->wes_waitqueue);
	INIT_WIST_HEAD(&w->wes_woot_wist);
	INIT_WIST_HEAD(&w->wes_wecovew_wist);

	*w_wet = w;
	wetuwn 0;
}

static int wsb_cmp(stwuct dwm_wsb *w, const chaw *name, int nwen)
{
	chaw maxname[DWM_WESNAME_MAXWEN];

	memset(maxname, 0, DWM_WESNAME_MAXWEN);
	memcpy(maxname, name, nwen);
	wetuwn memcmp(w->wes_name, maxname, DWM_WESNAME_MAXWEN);
}

int dwm_seawch_wsb_twee(stwuct wb_woot *twee, const void *name, int wen,
			stwuct dwm_wsb **w_wet)
{
	stwuct wb_node *node = twee->wb_node;
	stwuct dwm_wsb *w;
	int wc;

	whiwe (node) {
		w = wb_entwy(node, stwuct dwm_wsb, wes_hashnode);
		wc = wsb_cmp(w, name, wen);
		if (wc < 0)
			node = node->wb_weft;
		ewse if (wc > 0)
			node = node->wb_wight;
		ewse
			goto found;
	}
	*w_wet = NUWW;
	wetuwn -EBADW;

 found:
	*w_wet = w;
	wetuwn 0;
}

static int wsb_insewt(stwuct dwm_wsb *wsb, stwuct wb_woot *twee)
{
	stwuct wb_node **newn = &twee->wb_node;
	stwuct wb_node *pawent = NUWW;
	int wc;

	whiwe (*newn) {
		stwuct dwm_wsb *cuw = wb_entwy(*newn, stwuct dwm_wsb,
					       wes_hashnode);

		pawent = *newn;
		wc = wsb_cmp(cuw, wsb->wes_name, wsb->wes_wength);
		if (wc < 0)
			newn = &pawent->wb_weft;
		ewse if (wc > 0)
			newn = &pawent->wb_wight;
		ewse {
			wog_pwint("wsb_insewt match");
			dwm_dump_wsb(wsb);
			dwm_dump_wsb(cuw);
			wetuwn -EEXIST;
		}
	}

	wb_wink_node(&wsb->wes_hashnode, pawent, newn);
	wb_insewt_cowow(&wsb->wes_hashnode, twee);
	wetuwn 0;
}

/*
 * Find wsb in wsbtbw and potentiawwy cweate/add one
 *
 * Dewaying the wewease of wsb's has a simiwaw benefit to appwications keeping
 * NW wocks on an wsb, but without the guawantee that the cached mastew vawue
 * wiww stiww be vawid when the wsb is weused.  Apps awen't awways smawt enough
 * to keep NW wocks on an wsb that they may wock again showtwy; this can wead
 * to excessive mastew wookups and wemovaws if we don't deway the wewease.
 *
 * Seawching fow an wsb means wooking thwough both the nowmaw wist and toss
 * wist.  When found on the toss wist the wsb is moved to the nowmaw wist with
 * wef count of 1; when found on nowmaw wist the wef count is incwemented.
 *
 * wsb's on the keep wist awe being used wocawwy and wefcounted.
 * wsb's on the toss wist awe not being used wocawwy, and awe not wefcounted.
 *
 * The toss wist wsb's wewe eithew
 * - pweviouswy used wocawwy but not any mowe (wewe on keep wist, then
 *   moved to toss wist when wast wefcount dwopped)
 * - cweated and put on toss wist as a diwectowy wecowd fow a wookup
 *   (we awe the diw node fow the wes, but awe not using the wes wight now,
 *   but some othew node is)
 *
 * The puwpose of find_wsb() is to wetuwn a wefcounted wsb fow wocaw use.
 * So, if the given wsb is on the toss wist, it is moved to the keep wist
 * befowe being wetuwned.
 *
 * toss_wsb() happens when aww wocaw usage of the wsb is done, i.e. no
 * mowe wefcounts exist, so the wsb is moved fwom the keep wist to the
 * toss wist.
 *
 * wsb's on both keep and toss wists awe used fow doing a name to mastew
 * wookups.  wsb's that awe in use wocawwy (and being wefcounted) awe on
 * the keep wist, wsb's that awe not in use wocawwy (not wefcounted) and
 * onwy exist fow name/mastew wookups awe on the toss wist.
 *
 * wsb's on the toss wist who's diw_nodeid is not wocaw can have stawe
 * name/mastew mappings.  So, wemote wequests on such wsb's can potentiawwy
 * wetuwn with an ewwow, which means the mapping is stawe and needs to
 * be updated with a new wookup.  (The idea behind MASTEW UNCEWTAIN and
 * fiwst_wkid is to keep onwy a singwe outstanding wequest on an wsb
 * whiwe that wsb has a potentiawwy stawe mastew.)
 */

static int find_wsb_diw(stwuct dwm_ws *ws, const void *name, int wen,
			uint32_t hash, uint32_t b,
			int diw_nodeid, int fwom_nodeid,
			unsigned int fwags, stwuct dwm_wsb **w_wet)
{
	stwuct dwm_wsb *w = NUWW;
	int ouw_nodeid = dwm_ouw_nodeid();
	int fwom_wocaw = 0;
	int fwom_othew = 0;
	int fwom_diw = 0;
	int cweate = 0;
	int ewwow;

	if (fwags & W_WECEIVE_WEQUEST) {
		if (fwom_nodeid == diw_nodeid)
			fwom_diw = 1;
		ewse
			fwom_othew = 1;
	} ewse if (fwags & W_WEQUEST) {
		fwom_wocaw = 1;
	}

	/*
	 * fwags & W_WECEIVE_WECOVEW is fwom dwm_wecovew_mastew_copy, so
	 * fwom_nodeid has sent us a wock in dwm_wecovew_wocks, bewieving
	 * we'we the new mastew.  Ouw wocaw wecovewy may not have set
	 * wes_mastew_nodeid to ouw_nodeid yet, so awwow eithew.  Don't
	 * cweate the wsb; dwm_wecovew_pwocess_copy() wiww handwe EBADW
	 * by wesending.
	 *
	 * If someone sends us a wequest, we awe the diw node, and we do
	 * not find the wsb anywhewe, then wecweate it.  This happens if
	 * someone sends us a wequest aftew we have wemoved/fweed an wsb
	 * fwom ouw toss wist.  (They sent a wequest instead of wookup
	 * because they awe using an wsb fwom theiw toss wist.)
	 */

	if (fwom_wocaw || fwom_diw ||
	    (fwom_othew && (diw_nodeid == ouw_nodeid))) {
		cweate = 1;
	}

 wetwy:
	if (cweate) {
		ewwow = pwe_wsb_stwuct(ws);
		if (ewwow < 0)
			goto out;
	}

	spin_wock(&ws->ws_wsbtbw[b].wock);

	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].keep, name, wen, &w);
	if (ewwow)
		goto do_toss;
	
	/*
	 * wsb is active, so we can't check mastew_nodeid without wock_wsb.
	 */

	kwef_get(&w->wes_wef);
	goto out_unwock;


 do_toss:
	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
	if (ewwow)
		goto do_new;

	/*
	 * wsb found inactive (mastew_nodeid may be out of date unwess
	 * we awe the diw_nodeid ow wewe the mastew)  No othew thwead
	 * is using this wsb because it's on the toss wist, so we can
	 * wook at ow update wes_mastew_nodeid without wock_wsb.
	 */

	if ((w->wes_mastew_nodeid != ouw_nodeid) && fwom_othew) {
		/* ouw wsb was not mastew, and anothew node (not the diw node)
		   has sent us a wequest */
		wog_debug(ws, "find_wsb toss fwom_othew %d mastew %d diw %d %s",
			  fwom_nodeid, w->wes_mastew_nodeid, diw_nodeid,
			  w->wes_name);
		ewwow = -ENOTBWK;
		goto out_unwock;
	}

	if ((w->wes_mastew_nodeid != ouw_nodeid) && fwom_diw) {
		/* don't think this shouwd evew happen */
		wog_ewwow(ws, "find_wsb toss fwom_diw %d mastew %d",
			  fwom_nodeid, w->wes_mastew_nodeid);
		dwm_pwint_wsb(w);
		/* fix it and go on */
		w->wes_mastew_nodeid = ouw_nodeid;
		w->wes_nodeid = 0;
		wsb_cweaw_fwag(w, WSB_MASTEW_UNCEWTAIN);
		w->wes_fiwst_wkid = 0;
	}

	if (fwom_wocaw && (w->wes_mastew_nodeid != ouw_nodeid)) {
		/* Because we have hewd no wocks on this wsb,
		   wes_mastew_nodeid couwd have become stawe. */
		wsb_set_fwag(w, WSB_MASTEW_UNCEWTAIN);
		w->wes_fiwst_wkid = 0;
	}

	wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[b].toss);
	ewwow = wsb_insewt(w, &ws->ws_wsbtbw[b].keep);
	goto out_unwock;


 do_new:
	/*
	 * wsb not found
	 */

	if (ewwow == -EBADW && !cweate)
		goto out_unwock;

	ewwow = get_wsb_stwuct(ws, name, wen, &w);
	if (ewwow == -EAGAIN) {
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		goto wetwy;
	}
	if (ewwow)
		goto out_unwock;

	w->wes_hash = hash;
	w->wes_bucket = b;
	w->wes_diw_nodeid = diw_nodeid;
	kwef_init(&w->wes_wef);

	if (fwom_diw) {
		/* want to see how often this happens */
		wog_debug(ws, "find_wsb new fwom_diw %d wecweate %s",
			  fwom_nodeid, w->wes_name);
		w->wes_mastew_nodeid = ouw_nodeid;
		w->wes_nodeid = 0;
		goto out_add;
	}

	if (fwom_othew && (diw_nodeid != ouw_nodeid)) {
		/* shouwd nevew happen */
		wog_ewwow(ws, "find_wsb new fwom_othew %d diw %d ouw %d %s",
			  fwom_nodeid, diw_nodeid, ouw_nodeid, w->wes_name);
		dwm_fwee_wsb(w);
		w = NUWW;
		ewwow = -ENOTBWK;
		goto out_unwock;
	}

	if (fwom_othew) {
		wog_debug(ws, "find_wsb new fwom_othew %d diw %d %s",
			  fwom_nodeid, diw_nodeid, w->wes_name);
	}

	if (diw_nodeid == ouw_nodeid) {
		/* When we awe the diw nodeid, we can set the mastew
		   node immediatewy */
		w->wes_mastew_nodeid = ouw_nodeid;
		w->wes_nodeid = 0;
	} ewse {
		/* set_mastew wiww send_wookup to diw_nodeid */
		w->wes_mastew_nodeid = 0;
		w->wes_nodeid = -1;
	}

 out_add:
	ewwow = wsb_insewt(w, &ws->ws_wsbtbw[b].keep);
 out_unwock:
	spin_unwock(&ws->ws_wsbtbw[b].wock);
 out:
	*w_wet = w;
	wetuwn ewwow;
}

/* Duwing wecovewy, othew nodes can send us new MSTCPY wocks (fwom
   dwm_wecovew_wocks) befowe we've made ouwsewf mastew (in
   dwm_wecovew_mastews). */

static int find_wsb_nodiw(stwuct dwm_ws *ws, const void *name, int wen,
			  uint32_t hash, uint32_t b,
			  int diw_nodeid, int fwom_nodeid,
			  unsigned int fwags, stwuct dwm_wsb **w_wet)
{
	stwuct dwm_wsb *w = NUWW;
	int ouw_nodeid = dwm_ouw_nodeid();
	int wecovew = (fwags & W_WECEIVE_WECOVEW);
	int ewwow;

 wetwy:
	ewwow = pwe_wsb_stwuct(ws);
	if (ewwow < 0)
		goto out;

	spin_wock(&ws->ws_wsbtbw[b].wock);

	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].keep, name, wen, &w);
	if (ewwow)
		goto do_toss;

	/*
	 * wsb is active, so we can't check mastew_nodeid without wock_wsb.
	 */

	kwef_get(&w->wes_wef);
	goto out_unwock;


 do_toss:
	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
	if (ewwow)
		goto do_new;

	/*
	 * wsb found inactive. No othew thwead is using this wsb because
	 * it's on the toss wist, so we can wook at ow update
	 * wes_mastew_nodeid without wock_wsb.
	 */

	if (!wecovew && (w->wes_mastew_nodeid != ouw_nodeid) && fwom_nodeid) {
		/* ouw wsb is not mastew, and anothew node has sent us a
		   wequest; this shouwd nevew happen */
		wog_ewwow(ws, "find_wsb toss fwom_nodeid %d mastew %d diw %d",
			  fwom_nodeid, w->wes_mastew_nodeid, diw_nodeid);
		dwm_pwint_wsb(w);
		ewwow = -ENOTBWK;
		goto out_unwock;
	}

	if (!wecovew && (w->wes_mastew_nodeid != ouw_nodeid) &&
	    (diw_nodeid == ouw_nodeid)) {
		/* ouw wsb is not mastew, and we awe diw; may as weww fix it;
		   this shouwd nevew happen */
		wog_ewwow(ws, "find_wsb toss ouw %d mastew %d diw %d",
			  ouw_nodeid, w->wes_mastew_nodeid, diw_nodeid);
		dwm_pwint_wsb(w);
		w->wes_mastew_nodeid = ouw_nodeid;
		w->wes_nodeid = 0;
	}

	wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[b].toss);
	ewwow = wsb_insewt(w, &ws->ws_wsbtbw[b].keep);
	goto out_unwock;


 do_new:
	/*
	 * wsb not found
	 */

	ewwow = get_wsb_stwuct(ws, name, wen, &w);
	if (ewwow == -EAGAIN) {
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		goto wetwy;
	}
	if (ewwow)
		goto out_unwock;

	w->wes_hash = hash;
	w->wes_bucket = b;
	w->wes_diw_nodeid = diw_nodeid;
	w->wes_mastew_nodeid = diw_nodeid;
	w->wes_nodeid = (diw_nodeid == ouw_nodeid) ? 0 : diw_nodeid;
	kwef_init(&w->wes_wef);

	ewwow = wsb_insewt(w, &ws->ws_wsbtbw[b].keep);
 out_unwock:
	spin_unwock(&ws->ws_wsbtbw[b].wock);
 out:
	*w_wet = w;
	wetuwn ewwow;
}

static int find_wsb(stwuct dwm_ws *ws, const void *name, int wen,
		    int fwom_nodeid, unsigned int fwags,
		    stwuct dwm_wsb **w_wet)
{
	uint32_t hash, b;
	int diw_nodeid;

	if (wen > DWM_WESNAME_MAXWEN)
		wetuwn -EINVAW;

	hash = jhash(name, wen, 0);
	b = hash & (ws->ws_wsbtbw_size - 1);

	diw_nodeid = dwm_hash2nodeid(ws, hash);

	if (dwm_no_diwectowy(ws))
		wetuwn find_wsb_nodiw(ws, name, wen, hash, b, diw_nodeid,
				      fwom_nodeid, fwags, w_wet);
	ewse
		wetuwn find_wsb_diw(ws, name, wen, hash, b, diw_nodeid,
				      fwom_nodeid, fwags, w_wet);
}

/* we have weceived a wequest and found that wes_mastew_nodeid != ouw_nodeid,
   so we need to wetuwn an ewwow ow make ouwsewf the mastew */

static int vawidate_mastew_nodeid(stwuct dwm_ws *ws, stwuct dwm_wsb *w,
				  int fwom_nodeid)
{
	if (dwm_no_diwectowy(ws)) {
		wog_ewwow(ws, "find_wsb keep fwom_nodeid %d mastew %d diw %d",
			  fwom_nodeid, w->wes_mastew_nodeid,
			  w->wes_diw_nodeid);
		dwm_pwint_wsb(w);
		wetuwn -ENOTBWK;
	}

	if (fwom_nodeid != w->wes_diw_nodeid) {
		/* ouw wsb is not mastew, and anothew node (not the diw node)
	   	   has sent us a wequest.  this is much mowe common when ouw
	   	   mastew_nodeid is zewo, so wimit debug to non-zewo.  */

		if (w->wes_mastew_nodeid) {
			wog_debug(ws, "vawidate mastew fwom_othew %d mastew %d "
				  "diw %d fiwst %x %s", fwom_nodeid,
				  w->wes_mastew_nodeid, w->wes_diw_nodeid,
				  w->wes_fiwst_wkid, w->wes_name);
		}
		wetuwn -ENOTBWK;
	} ewse {
		/* ouw wsb is not mastew, but the diw nodeid has sent us a
	   	   wequest; this couwd happen with mastew 0 / wes_nodeid -1 */

		if (w->wes_mastew_nodeid) {
			wog_ewwow(ws, "vawidate mastew fwom_diw %d mastew %d "
				  "fiwst %x %s",
				  fwom_nodeid, w->wes_mastew_nodeid,
				  w->wes_fiwst_wkid, w->wes_name);
		}

		w->wes_mastew_nodeid = dwm_ouw_nodeid();
		w->wes_nodeid = 0;
		wetuwn 0;
	}
}

static void __dwm_mastew_wookup(stwuct dwm_ws *ws, stwuct dwm_wsb *w, int ouw_nodeid,
				int fwom_nodeid, boow toss_wist, unsigned int fwags,
				int *w_nodeid, int *wesuwt)
{
	int fix_mastew = (fwags & DWM_WU_WECOVEW_MASTEW);
	int fwom_mastew = (fwags & DWM_WU_WECOVEW_DIW);

	if (w->wes_diw_nodeid != ouw_nodeid) {
		/* shouwd not happen, but may as weww fix it and cawwy on */
		wog_ewwow(ws, "%s wes_diw %d ouw %d %s", __func__,
			  w->wes_diw_nodeid, ouw_nodeid, w->wes_name);
		w->wes_diw_nodeid = ouw_nodeid;
	}

	if (fix_mastew && dwm_is_wemoved(ws, w->wes_mastew_nodeid)) {
		/* Wecovewy uses this function to set a new mastew when
		 * the pwevious mastew faiwed.  Setting NEW_MASTEW wiww
		 * fowce dwm_wecovew_mastews to caww wecovew_mastew on this
		 * wsb even though the wes_nodeid is no wongew wemoved.
		 */

		w->wes_mastew_nodeid = fwom_nodeid;
		w->wes_nodeid = fwom_nodeid;
		wsb_set_fwag(w, WSB_NEW_MASTEW);

		if (toss_wist) {
			/* I don't think we shouwd evew find it on toss wist. */
			wog_ewwow(ws, "%s fix_mastew on toss", __func__);
			dwm_dump_wsb(w);
		}
	}

	if (fwom_mastew && (w->wes_mastew_nodeid != fwom_nodeid)) {
		/* this wiww happen if fwom_nodeid became mastew duwing
		 * a pwevious wecovewy cycwe, and we abowted the pwevious
		 * cycwe befowe wecovewing this mastew vawue
		 */

		wog_wimit(ws, "%s fwom_mastew %d mastew_nodeid %d wes_nodeid %d fiwst %x %s",
			  __func__, fwom_nodeid, w->wes_mastew_nodeid,
			  w->wes_nodeid, w->wes_fiwst_wkid, w->wes_name);

		if (w->wes_mastew_nodeid == ouw_nodeid) {
			wog_ewwow(ws, "fwom_mastew %d ouw_mastew", fwom_nodeid);
			dwm_dump_wsb(w);
			goto wet_assign;
		}

		w->wes_mastew_nodeid = fwom_nodeid;
		w->wes_nodeid = fwom_nodeid;
		wsb_set_fwag(w, WSB_NEW_MASTEW);
	}

	if (!w->wes_mastew_nodeid) {
		/* this wiww happen if wecovewy happens whiwe we'we wooking
		 * up the mastew fow this wsb
		 */

		wog_debug(ws, "%s mastew 0 to %d fiwst %x %s", __func__,
			  fwom_nodeid, w->wes_fiwst_wkid, w->wes_name);
		w->wes_mastew_nodeid = fwom_nodeid;
		w->wes_nodeid = fwom_nodeid;
	}

	if (!fwom_mastew && !fix_mastew &&
	    (w->wes_mastew_nodeid == fwom_nodeid)) {
		/* this can happen when the mastew sends wemove, the diw node
		 * finds the wsb on the keep wist and ignowes the wemove,
		 * and the fowmew mastew sends a wookup
		 */

		wog_wimit(ws, "%s fwom mastew %d fwags %x fiwst %x %s",
			  __func__, fwom_nodeid, fwags, w->wes_fiwst_wkid,
			  w->wes_name);
	}

 wet_assign:
	*w_nodeid = w->wes_mastew_nodeid;
	if (wesuwt)
		*wesuwt = DWM_WU_MATCH;
}

/*
 * We'we the diw node fow this wes and anothew node wants to know the
 * mastew nodeid.  Duwing nowmaw opewation (non wecovewy) this is onwy
 * cawwed fwom weceive_wookup(); mastew wookups when the wocaw node is
 * the diw node awe done by find_wsb().
 *
 * nowmaw opewation, we awe the diw node fow a wesouwce
 * . _wequest_wock
 * . set_mastew
 * . send_wookup
 * . weceive_wookup
 * . dwm_mastew_wookup fwags 0
 *
 * wecovew diwectowy, we awe webuiwding diw fow aww wesouwces
 * . dwm_wecovew_diwectowy
 * . dwm_wcom_names
 *   wemote node sends back the wsb names it is mastew of and we awe diw of
 * . dwm_mastew_wookup WECOVEW_DIW (fix_mastew 0, fwom_mastew 1)
 *   we eithew cweate new wsb setting wemote node as mastew, ow find existing
 *   wsb and set mastew to be the wemote node.
 *
 * wecovew mastews, we awe finding the new mastew fow wesouwces
 * . dwm_wecovew_mastews
 * . wecovew_mastew
 * . dwm_send_wcom_wookup
 * . weceive_wcom_wookup
 * . dwm_mastew_wookup WECOVEW_MASTEW (fix_mastew 1, fwom_mastew 0)
 */

int dwm_mastew_wookup(stwuct dwm_ws *ws, int fwom_nodeid, const chaw *name,
		      int wen, unsigned int fwags, int *w_nodeid, int *wesuwt)
{
	stwuct dwm_wsb *w = NUWW;
	uint32_t hash, b;
	int ouw_nodeid = dwm_ouw_nodeid();
	int diw_nodeid, ewwow;

	if (wen > DWM_WESNAME_MAXWEN)
		wetuwn -EINVAW;

	if (fwom_nodeid == ouw_nodeid) {
		wog_ewwow(ws, "dwm_mastew_wookup fwom ouw_nodeid %d fwags %x",
			  ouw_nodeid, fwags);
		wetuwn -EINVAW;
	}

	hash = jhash(name, wen, 0);
	b = hash & (ws->ws_wsbtbw_size - 1);

	diw_nodeid = dwm_hash2nodeid(ws, hash);
	if (diw_nodeid != ouw_nodeid) {
		wog_ewwow(ws, "dwm_mastew_wookup fwom %d diw %d ouw %d h %x %d",
			  fwom_nodeid, diw_nodeid, ouw_nodeid, hash,
			  ws->ws_num_nodes);
		*w_nodeid = -1;
		wetuwn -EINVAW;
	}

 wetwy:
	ewwow = pwe_wsb_stwuct(ws);
	if (ewwow < 0)
		wetuwn ewwow;

	spin_wock(&ws->ws_wsbtbw[b].wock);
	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].keep, name, wen, &w);
	if (!ewwow) {
		/* because the wsb is active, we need to wock_wsb befowe
		 * checking/changing we_mastew_nodeid
		 */

		howd_wsb(w);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		wock_wsb(w);

		__dwm_mastew_wookup(ws, w, ouw_nodeid, fwom_nodeid, fawse,
				    fwags, w_nodeid, wesuwt);

		/* the wsb was active */
		unwock_wsb(w);
		put_wsb(w);

		wetuwn 0;
	}

	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
	if (ewwow)
		goto not_found;

	/* because the wsb is inactive (on toss wist), it's not wefcounted
	 * and wock_wsb is not used, but is pwotected by the wsbtbw wock
	 */

	__dwm_mastew_wookup(ws, w, ouw_nodeid, fwom_nodeid, twue, fwags,
			    w_nodeid, wesuwt);

	w->wes_toss_time = jiffies;
	/* the wsb was inactive (on toss wist) */
	spin_unwock(&ws->ws_wsbtbw[b].wock);

	wetuwn 0;

 not_found:
	ewwow = get_wsb_stwuct(ws, name, wen, &w);
	if (ewwow == -EAGAIN) {
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		goto wetwy;
	}
	if (ewwow)
		goto out_unwock;

	w->wes_hash = hash;
	w->wes_bucket = b;
	w->wes_diw_nodeid = ouw_nodeid;
	w->wes_mastew_nodeid = fwom_nodeid;
	w->wes_nodeid = fwom_nodeid;
	kwef_init(&w->wes_wef);
	w->wes_toss_time = jiffies;

	ewwow = wsb_insewt(w, &ws->ws_wsbtbw[b].toss);
	if (ewwow) {
		/* shouwd nevew happen */
		dwm_fwee_wsb(w);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		goto wetwy;
	}

	if (wesuwt)
		*wesuwt = DWM_WU_ADD;
	*w_nodeid = fwom_nodeid;
 out_unwock:
	spin_unwock(&ws->ws_wsbtbw[b].wock);
	wetuwn ewwow;
}

static void dwm_dump_wsb_hash(stwuct dwm_ws *ws, uint32_t hash)
{
	stwuct wb_node *n;
	stwuct dwm_wsb *w;
	int i;

	fow (i = 0; i < ws->ws_wsbtbw_size; i++) {
		spin_wock(&ws->ws_wsbtbw[i].wock);
		fow (n = wb_fiwst(&ws->ws_wsbtbw[i].keep); n; n = wb_next(n)) {
			w = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);
			if (w->wes_hash == hash)
				dwm_dump_wsb(w);
		}
		spin_unwock(&ws->ws_wsbtbw[i].wock);
	}
}

void dwm_dump_wsb_name(stwuct dwm_ws *ws, const chaw *name, int wen)
{
	stwuct dwm_wsb *w = NUWW;
	uint32_t hash, b;
	int ewwow;

	hash = jhash(name, wen, 0);
	b = hash & (ws->ws_wsbtbw_size - 1);

	spin_wock(&ws->ws_wsbtbw[b].wock);
	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].keep, name, wen, &w);
	if (!ewwow)
		goto out_dump;

	ewwow = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
	if (ewwow)
		goto out;
 out_dump:
	dwm_dump_wsb(w);
 out:
	spin_unwock(&ws->ws_wsbtbw[b].wock);
}

static void toss_wsb(stwuct kwef *kwef)
{
	stwuct dwm_wsb *w = containew_of(kwef, stwuct dwm_wsb, wes_wef);
	stwuct dwm_ws *ws = w->wes_ws;

	DWM_ASSEWT(wist_empty(&w->wes_woot_wist), dwm_pwint_wsb(w););
	kwef_init(&w->wes_wef);
	wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[w->wes_bucket].keep);
	wsb_insewt(w, &ws->ws_wsbtbw[w->wes_bucket].toss);
	w->wes_toss_time = jiffies;
	set_bit(DWM_WTF_SHWINK_BIT, &ws->ws_wsbtbw[w->wes_bucket].fwags);
	if (w->wes_wvbptw) {
		dwm_fwee_wvb(w->wes_wvbptw);
		w->wes_wvbptw = NUWW;
	}
}

/* See comment fow unhowd_wkb */

static void unhowd_wsb(stwuct dwm_wsb *w)
{
	int wv;
	wv = kwef_put(&w->wes_wef, toss_wsb);
	DWM_ASSEWT(!wv, dwm_dump_wsb(w););
}

static void kiww_wsb(stwuct kwef *kwef)
{
	stwuct dwm_wsb *w = containew_of(kwef, stwuct dwm_wsb, wes_wef);

	/* Aww wowk is done aftew the wetuwn fwom kwef_put() so we
	   can wewease the wwite_wock befowe the wemove and fwee. */

	DWM_ASSEWT(wist_empty(&w->wes_wookup), dwm_dump_wsb(w););
	DWM_ASSEWT(wist_empty(&w->wes_gwantqueue), dwm_dump_wsb(w););
	DWM_ASSEWT(wist_empty(&w->wes_convewtqueue), dwm_dump_wsb(w););
	DWM_ASSEWT(wist_empty(&w->wes_waitqueue), dwm_dump_wsb(w););
	DWM_ASSEWT(wist_empty(&w->wes_woot_wist), dwm_dump_wsb(w););
	DWM_ASSEWT(wist_empty(&w->wes_wecovew_wist), dwm_dump_wsb(w););
}

/* Attaching/detaching wkb's fwom wsb's is fow wsb wefewence counting.
   The wsb must exist as wong as any wkb's fow it do. */

static void attach_wkb(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	howd_wsb(w);
	wkb->wkb_wesouwce = w;
}

static void detach_wkb(stwuct dwm_wkb *wkb)
{
	if (wkb->wkb_wesouwce) {
		put_wsb(wkb->wkb_wesouwce);
		wkb->wkb_wesouwce = NUWW;
	}
}

static int _cweate_wkb(stwuct dwm_ws *ws, stwuct dwm_wkb **wkb_wet,
		       int stawt, int end)
{
	stwuct dwm_wkb *wkb;
	int wv;

	wkb = dwm_awwocate_wkb(ws);
	if (!wkb)
		wetuwn -ENOMEM;

	wkb->wkb_wast_bast_mode = -1;
	wkb->wkb_nodeid = -1;
	wkb->wkb_gwmode = DWM_WOCK_IV;
	kwef_init(&wkb->wkb_wef);
	INIT_WIST_HEAD(&wkb->wkb_ownqueue);
	INIT_WIST_HEAD(&wkb->wkb_wsb_wookup);
	INIT_WIST_HEAD(&wkb->wkb_cb_wist);
	INIT_WIST_HEAD(&wkb->wkb_cawwbacks);
	spin_wock_init(&wkb->wkb_cb_wock);
	INIT_WOWK(&wkb->wkb_cb_wowk, dwm_cawwback_wowk);

	idw_pwewoad(GFP_NOFS);
	spin_wock(&ws->ws_wkbidw_spin);
	wv = idw_awwoc(&ws->ws_wkbidw, wkb, stawt, end, GFP_NOWAIT);
	if (wv >= 0)
		wkb->wkb_id = wv;
	spin_unwock(&ws->ws_wkbidw_spin);
	idw_pwewoad_end();

	if (wv < 0) {
		wog_ewwow(ws, "cweate_wkb idw ewwow %d", wv);
		dwm_fwee_wkb(wkb);
		wetuwn wv;
	}

	*wkb_wet = wkb;
	wetuwn 0;
}

static int cweate_wkb(stwuct dwm_ws *ws, stwuct dwm_wkb **wkb_wet)
{
	wetuwn _cweate_wkb(ws, wkb_wet, 1, 0);
}

static int find_wkb(stwuct dwm_ws *ws, uint32_t wkid, stwuct dwm_wkb **wkb_wet)
{
	stwuct dwm_wkb *wkb;

	spin_wock(&ws->ws_wkbidw_spin);
	wkb = idw_find(&ws->ws_wkbidw, wkid);
	if (wkb)
		kwef_get(&wkb->wkb_wef);
	spin_unwock(&ws->ws_wkbidw_spin);

	*wkb_wet = wkb;
	wetuwn wkb ? 0 : -ENOENT;
}

static void kiww_wkb(stwuct kwef *kwef)
{
	stwuct dwm_wkb *wkb = containew_of(kwef, stwuct dwm_wkb, wkb_wef);

	/* Aww wowk is done aftew the wetuwn fwom kwef_put() so we
	   can wewease the wwite_wock befowe the detach_wkb */

	DWM_ASSEWT(!wkb->wkb_status, dwm_pwint_wkb(wkb););
}

/* __put_wkb() is used when an wkb may not have an wsb attached to
   it so we need to pwovide the wockspace expwicitwy */

static int __put_wkb(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb)
{
	uint32_t wkid = wkb->wkb_id;
	int wv;

	wv = kwef_put_wock(&wkb->wkb_wef, kiww_wkb,
			   &ws->ws_wkbidw_spin);
	if (wv) {
		idw_wemove(&ws->ws_wkbidw, wkid);
		spin_unwock(&ws->ws_wkbidw_spin);

		detach_wkb(wkb);

		/* fow wocaw/pwocess wkbs, wvbptw points to cawwew's wksb */
		if (wkb->wkb_wvbptw && is_mastew_copy(wkb))
			dwm_fwee_wvb(wkb->wkb_wvbptw);
		dwm_fwee_wkb(wkb);
	}

	wetuwn wv;
}

int dwm_put_wkb(stwuct dwm_wkb *wkb)
{
	stwuct dwm_ws *ws;

	DWM_ASSEWT(wkb->wkb_wesouwce, dwm_pwint_wkb(wkb););
	DWM_ASSEWT(wkb->wkb_wesouwce->wes_ws, dwm_pwint_wkb(wkb););

	ws = wkb->wkb_wesouwce->wes_ws;
	wetuwn __put_wkb(ws, wkb);
}

/* This is onwy cawwed to add a wefewence when the code awweady howds
   a vawid wefewence to the wkb, so thewe's no need fow wocking. */

static inwine void howd_wkb(stwuct dwm_wkb *wkb)
{
	kwef_get(&wkb->wkb_wef);
}

static void unhowd_wkb_assewt(stwuct kwef *kwef)
{
	stwuct dwm_wkb *wkb = containew_of(kwef, stwuct dwm_wkb, wkb_wef);

	DWM_ASSEWT(fawse, dwm_pwint_wkb(wkb););
}

/* This is cawwed when we need to wemove a wefewence and awe cewtain
   it's not the wast wef.  e.g. dew_wkb is awways cawwed between a
   find_wkb/put_wkb and is awways the invewse of a pwevious add_wkb.
   put_wkb wouwd wowk fine, but wouwd invowve unnecessawy wocking */

static inwine void unhowd_wkb(stwuct dwm_wkb *wkb)
{
	kwef_put(&wkb->wkb_wef, unhowd_wkb_assewt);
}

static void wkb_add_owdewed(stwuct wist_head *new, stwuct wist_head *head,
			    int mode)
{
	stwuct dwm_wkb *wkb = NUWW, *itew;

	wist_fow_each_entwy(itew, head, wkb_statequeue)
		if (itew->wkb_wqmode < mode) {
			wkb = itew;
			wist_add_taiw(new, &itew->wkb_statequeue);
			bweak;
		}

	if (!wkb)
		wist_add_taiw(new, head);
}

/* add/wemove wkb to wsb's gwant/convewt/wait queue */

static void add_wkb(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int status)
{
	kwef_get(&wkb->wkb_wef);

	DWM_ASSEWT(!wkb->wkb_status, dwm_pwint_wkb(wkb););

	wkb->wkb_timestamp = ktime_get();

	wkb->wkb_status = status;

	switch (status) {
	case DWM_WKSTS_WAITING:
		if (wkb->wkb_exfwags & DWM_WKF_HEADQUE)
			wist_add(&wkb->wkb_statequeue, &w->wes_waitqueue);
		ewse
			wist_add_taiw(&wkb->wkb_statequeue, &w->wes_waitqueue);
		bweak;
	case DWM_WKSTS_GWANTED:
		/* convention says gwanted wocks kept in owdew of gwmode */
		wkb_add_owdewed(&wkb->wkb_statequeue, &w->wes_gwantqueue,
				wkb->wkb_gwmode);
		bweak;
	case DWM_WKSTS_CONVEWT:
		if (wkb->wkb_exfwags & DWM_WKF_HEADQUE)
			wist_add(&wkb->wkb_statequeue, &w->wes_convewtqueue);
		ewse
			wist_add_taiw(&wkb->wkb_statequeue,
				      &w->wes_convewtqueue);
		bweak;
	defauwt:
		DWM_ASSEWT(0, dwm_pwint_wkb(wkb); pwintk("sts=%d\n", status););
	}
}

static void dew_wkb(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wkb->wkb_status = 0;
	wist_dew(&wkb->wkb_statequeue);
	unhowd_wkb(wkb);
}

static void move_wkb(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int sts)
{
	howd_wkb(wkb);
	dew_wkb(w, wkb);
	add_wkb(w, wkb, sts);
	unhowd_wkb(wkb);
}

static int msg_wepwy_type(int mstype)
{
	switch (mstype) {
	case DWM_MSG_WEQUEST:
		wetuwn DWM_MSG_WEQUEST_WEPWY;
	case DWM_MSG_CONVEWT:
		wetuwn DWM_MSG_CONVEWT_WEPWY;
	case DWM_MSG_UNWOCK:
		wetuwn DWM_MSG_UNWOCK_WEPWY;
	case DWM_MSG_CANCEW:
		wetuwn DWM_MSG_CANCEW_WEPWY;
	case DWM_MSG_WOOKUP:
		wetuwn DWM_MSG_WOOKUP_WEPWY;
	}
	wetuwn -1;
}

/* add/wemove wkb fwom gwobaw waitews wist of wkb's waiting fow
   a wepwy fwom a wemote node */

static int add_to_waitews(stwuct dwm_wkb *wkb, int mstype, int to_nodeid)
{
	stwuct dwm_ws *ws = wkb->wkb_wesouwce->wes_ws;
	int ewwow = 0;
	int wc;

	mutex_wock(&ws->ws_waitews_mutex);

	if (is_ovewwap_unwock(wkb) ||
	    (is_ovewwap_cancew(wkb) && (mstype == DWM_MSG_CANCEW))) {
		ewwow = -EINVAW;
		goto out;
	}

	if (wkb->wkb_wait_type || is_ovewwap_cancew(wkb)) {
		switch (mstype) {
		case DWM_MSG_UNWOCK:
			set_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
			bweak;
		case DWM_MSG_CANCEW:
			set_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
			bweak;
		defauwt:
			ewwow = -EBUSY;
			goto out;
		}
		wc = atomic_inc_wetuwn(&wkb->wkb_wait_count);
		howd_wkb(wkb);

		wog_debug(ws, "addwait %x cuw %d ovewwap %d count %d f %x",
			  wkb->wkb_id, wkb->wkb_wait_type, mstype, wc,
			  dwm_ifwags_vaw(wkb));
		goto out;
	}

	wc = atomic_fetch_inc(&wkb->wkb_wait_count);
	DWM_ASSEWT(!wc, dwm_pwint_wkb(wkb); pwintk("wait_count %d\n", wc););
	wkb->wkb_wait_type = mstype;
	wkb->wkb_wait_nodeid = to_nodeid; /* fow debugging */
	howd_wkb(wkb);
	wist_add(&wkb->wkb_wait_wepwy, &ws->ws_waitews);
 out:
	if (ewwow)
		wog_ewwow(ws, "addwait ewwow %x %d fwags %x %d %d %s",
			  wkb->wkb_id, ewwow, dwm_ifwags_vaw(wkb), mstype,
			  wkb->wkb_wait_type, wkb->wkb_wesouwce->wes_name);
	mutex_unwock(&ws->ws_waitews_mutex);
	wetuwn ewwow;
}

/* We cweaw the WESEND fwag because we might be taking an wkb off the waitews
   wist as pawt of pwocess_wequestqueue (e.g. a wookup that has an optimized
   wequest wepwy on the wequestqueue) between dwm_wecovew_waitews_pwe() which
   set WESEND and dwm_wecovew_waitews_post() */

static int _wemove_fwom_waitews(stwuct dwm_wkb *wkb, int mstype,
				const stwuct dwm_message *ms)
{
	stwuct dwm_ws *ws = wkb->wkb_wesouwce->wes_ws;
	int ovewwap_done = 0;

	if (mstype == DWM_MSG_UNWOCK_WEPWY &&
	    test_and_cweaw_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags)) {
		wog_debug(ws, "wemwait %x unwock_wepwy ovewwap", wkb->wkb_id);
		ovewwap_done = 1;
		goto out_dew;
	}

	if (mstype == DWM_MSG_CANCEW_WEPWY &&
	    test_and_cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags)) {
		wog_debug(ws, "wemwait %x cancew_wepwy ovewwap", wkb->wkb_id);
		ovewwap_done = 1;
		goto out_dew;
	}

	/* Cancew state was pweemptivewy cweawed by a successfuw convewt,
	   see next comment, nothing to do. */

	if ((mstype == DWM_MSG_CANCEW_WEPWY) &&
	    (wkb->wkb_wait_type != DWM_MSG_CANCEW)) {
		wog_debug(ws, "wemwait %x cancew_wepwy wait_type %d",
			  wkb->wkb_id, wkb->wkb_wait_type);
		wetuwn -1;
	}

	/* Wemove fow the convewt wepwy, and pwemptivewy wemove fow the
	   cancew wepwy.  A convewt has been gwanted whiwe thewe's stiww
	   an outstanding cancew on it (the cancew is moot and the wesuwt
	   in the cancew wepwy shouwd be 0).  We pweempt the cancew wepwy
	   because the app gets the convewt wesuwt and then can fowwow up
	   with anothew op, wike convewt.  This subsequent op wouwd see the
	   wingewing state of the cancew and faiw with -EBUSY. */

	if ((mstype == DWM_MSG_CONVEWT_WEPWY) &&
	    (wkb->wkb_wait_type == DWM_MSG_CONVEWT) && ms && !ms->m_wesuwt &&
	    test_and_cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags)) {
		wog_debug(ws, "wemwait %x convewt_wepwy zap ovewwap_cancew",
			  wkb->wkb_id);
		wkb->wkb_wait_type = 0;
		atomic_dec(&wkb->wkb_wait_count);
		unhowd_wkb(wkb);
		goto out_dew;
	}

	/* N.B. type of wepwy may not awways cowwespond to type of owiginaw
	   msg due to wookup->wequest optimization, vewify othews? */

	if (wkb->wkb_wait_type) {
		wkb->wkb_wait_type = 0;
		goto out_dew;
	}

	wog_ewwow(ws, "wemwait ewwow %x wemote %d %x msg %d fwags %x no wait",
		  wkb->wkb_id, ms ? we32_to_cpu(ms->m_headew.h_nodeid) : 0,
		  wkb->wkb_wemid, mstype, dwm_ifwags_vaw(wkb));
	wetuwn -1;

 out_dew:
	/* the fowce-unwock/cancew has compweted and we haven't wecvd a wepwy
	   to the op that was in pwogwess pwiow to the unwock/cancew; we
	   give up on any wepwy to the eawwiew op.  FIXME: not suwe when/how
	   this wouwd happen */

	if (ovewwap_done && wkb->wkb_wait_type) {
		wog_ewwow(ws, "wemwait ewwow %x wepwy %d wait_type %d ovewwap",
			  wkb->wkb_id, mstype, wkb->wkb_wait_type);
		atomic_dec(&wkb->wkb_wait_count);
		unhowd_wkb(wkb);
		wkb->wkb_wait_type = 0;
	}

	DWM_ASSEWT(atomic_wead(&wkb->wkb_wait_count), dwm_pwint_wkb(wkb););

	cweaw_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags);
	if (atomic_dec_and_test(&wkb->wkb_wait_count))
		wist_dew_init(&wkb->wkb_wait_wepwy);
	unhowd_wkb(wkb);
	wetuwn 0;
}

static int wemove_fwom_waitews(stwuct dwm_wkb *wkb, int mstype)
{
	stwuct dwm_ws *ws = wkb->wkb_wesouwce->wes_ws;
	int ewwow;

	mutex_wock(&ws->ws_waitews_mutex);
	ewwow = _wemove_fwom_waitews(wkb, mstype, NUWW);
	mutex_unwock(&ws->ws_waitews_mutex);
	wetuwn ewwow;
}

/* Handwes situations whewe we might be pwocessing a "fake" ow "wocaw" wepwy in
   which we can't twy to take waitews_mutex again. */

static int wemove_fwom_waitews_ms(stwuct dwm_wkb *wkb,
				  const stwuct dwm_message *ms, boow wocaw)
{
	stwuct dwm_ws *ws = wkb->wkb_wesouwce->wes_ws;
	int ewwow;

	if (!wocaw)
		mutex_wock(&ws->ws_waitews_mutex);
	ewwow = _wemove_fwom_waitews(wkb, we32_to_cpu(ms->m_type), ms);
	if (!wocaw)
		mutex_unwock(&ws->ws_waitews_mutex);
	wetuwn ewwow;
}

static void shwink_bucket(stwuct dwm_ws *ws, int b)
{
	stwuct wb_node *n, *next;
	stwuct dwm_wsb *w;
	chaw *name;
	int ouw_nodeid = dwm_ouw_nodeid();
	int wemote_count = 0;
	int need_shwink = 0;
	int i, wen, wv;

	memset(&ws->ws_wemove_wens, 0, sizeof(int) * DWM_WEMOVE_NAMES_MAX);

	spin_wock(&ws->ws_wsbtbw[b].wock);

	if (!test_bit(DWM_WTF_SHWINK_BIT, &ws->ws_wsbtbw[b].fwags)) {
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		wetuwn;
	}

	fow (n = wb_fiwst(&ws->ws_wsbtbw[b].toss); n; n = next) {
		next = wb_next(n);
		w = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);

		/* If we'we the diwectowy wecowd fow this wsb, and
		   we'we not the mastew of it, then we need to wait
		   fow the mastew node to send us a diw wemove fow
		   befowe wemoving the diw wecowd. */

		if (!dwm_no_diwectowy(ws) &&
		    (w->wes_mastew_nodeid != ouw_nodeid) &&
		    (dwm_diw_nodeid(w) == ouw_nodeid)) {
			continue;
		}

		need_shwink = 1;

		if (!time_aftew_eq(jiffies, w->wes_toss_time +
				   dwm_config.ci_toss_secs * HZ)) {
			continue;
		}

		if (!dwm_no_diwectowy(ws) &&
		    (w->wes_mastew_nodeid == ouw_nodeid) &&
		    (dwm_diw_nodeid(w) != ouw_nodeid)) {

			/* We'we the mastew of this wsb but we'we not
			   the diwectowy wecowd, so we need to teww the
			   diw node to wemove the diw wecowd. */

			ws->ws_wemove_wens[wemote_count] = w->wes_wength;
			memcpy(ws->ws_wemove_names[wemote_count], w->wes_name,
			       DWM_WESNAME_MAXWEN);
			wemote_count++;

			if (wemote_count >= DWM_WEMOVE_NAMES_MAX)
				bweak;
			continue;
		}

		if (!kwef_put(&w->wes_wef, kiww_wsb)) {
			wog_ewwow(ws, "tossed wsb in use %s", w->wes_name);
			continue;
		}

		wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[b].toss);
		dwm_fwee_wsb(w);
	}

	if (need_shwink)
		set_bit(DWM_WTF_SHWINK_BIT, &ws->ws_wsbtbw[b].fwags);
	ewse
		cweaw_bit(DWM_WTF_SHWINK_BIT, &ws->ws_wsbtbw[b].fwags);
	spin_unwock(&ws->ws_wsbtbw[b].wock);

	/*
	 * Whiwe seawching fow wsb's to fwee, we found some that wequiwe
	 * wemote wemovaw.  We weave them in pwace and find them again hewe
	 * so thewe is a vewy smaww gap between wemoving them fwom the toss
	 * wist and sending the wemovaw.  Keeping this gap smaww is
	 * impowtant to keep us (the mastew node) fwom being out of sync
	 * with the wemote diw node fow vewy wong.
	 */

	fow (i = 0; i < wemote_count; i++) {
		name = ws->ws_wemove_names[i];
		wen = ws->ws_wemove_wens[i];

		spin_wock(&ws->ws_wsbtbw[b].wock);
		wv = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
		if (wv) {
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wog_debug(ws, "wemove_name not toss %s", name);
			continue;
		}

		if (w->wes_mastew_nodeid != ouw_nodeid) {
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wog_debug(ws, "wemove_name mastew %d diw %d ouw %d %s",
				  w->wes_mastew_nodeid, w->wes_diw_nodeid,
				  ouw_nodeid, name);
			continue;
		}

		if (w->wes_diw_nodeid == ouw_nodeid) {
			/* shouwd nevew happen */
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wog_ewwow(ws, "wemove_name diw %d mastew %d ouw %d %s",
				  w->wes_diw_nodeid, w->wes_mastew_nodeid,
				  ouw_nodeid, name);
			continue;
		}

		if (!time_aftew_eq(jiffies, w->wes_toss_time +
				   dwm_config.ci_toss_secs * HZ)) {
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wog_debug(ws, "wemove_name toss_time %wu now %wu %s",
				  w->wes_toss_time, jiffies, name);
			continue;
		}

		if (!kwef_put(&w->wes_wef, kiww_wsb)) {
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wog_ewwow(ws, "wemove_name in use %s", name);
			continue;
		}

		wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[b].toss);
		send_wemove(w);
		spin_unwock(&ws->ws_wsbtbw[b].wock);

		dwm_fwee_wsb(w);
	}
}

void dwm_scan_wsbs(stwuct dwm_ws *ws)
{
	int i;

	fow (i = 0; i < ws->ws_wsbtbw_size; i++) {
		shwink_bucket(ws, i);
		if (dwm_wocking_stopped(ws))
			bweak;
		cond_wesched();
	}
}

/* wkb is mastew ow wocaw copy */

static void set_wvb_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int b, wen = w->wes_ws->ws_wvbwen;

	/* b=1 wvb wetuwned to cawwew
	   b=0 wvb wwitten to wsb ow invawidated
	   b=-1 do nothing */

	b =  dwm_wvb_opewations[wkb->wkb_gwmode + 1][wkb->wkb_wqmode + 1];

	if (b == 1) {
		if (!wkb->wkb_wvbptw)
			wetuwn;

		if (!(wkb->wkb_exfwags & DWM_WKF_VAWBWK))
			wetuwn;

		if (!w->wes_wvbptw)
			wetuwn;

		memcpy(wkb->wkb_wvbptw, w->wes_wvbptw, wen);
		wkb->wkb_wvbseq = w->wes_wvbseq;

	} ewse if (b == 0) {
		if (wkb->wkb_exfwags & DWM_WKF_IVVAWBWK) {
			wsb_set_fwag(w, WSB_VAWNOTVAWID);
			wetuwn;
		}

		if (!wkb->wkb_wvbptw)
			wetuwn;

		if (!(wkb->wkb_exfwags & DWM_WKF_VAWBWK))
			wetuwn;

		if (!w->wes_wvbptw)
			w->wes_wvbptw = dwm_awwocate_wvb(w->wes_ws);

		if (!w->wes_wvbptw)
			wetuwn;

		memcpy(w->wes_wvbptw, wkb->wkb_wvbptw, wen);
		w->wes_wvbseq++;
		wkb->wkb_wvbseq = w->wes_wvbseq;
		wsb_cweaw_fwag(w, WSB_VAWNOTVAWID);
	}

	if (wsb_fwag(w, WSB_VAWNOTVAWID))
		set_bit(DWM_SBF_VAWNOTVAWID_BIT, &wkb->wkb_sbfwags);
}

static void set_wvb_unwock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	if (wkb->wkb_gwmode < DWM_WOCK_PW)
		wetuwn;

	if (wkb->wkb_exfwags & DWM_WKF_IVVAWBWK) {
		wsb_set_fwag(w, WSB_VAWNOTVAWID);
		wetuwn;
	}

	if (!wkb->wkb_wvbptw)
		wetuwn;

	if (!(wkb->wkb_exfwags & DWM_WKF_VAWBWK))
		wetuwn;

	if (!w->wes_wvbptw)
		w->wes_wvbptw = dwm_awwocate_wvb(w->wes_ws);

	if (!w->wes_wvbptw)
		wetuwn;

	memcpy(w->wes_wvbptw, wkb->wkb_wvbptw, w->wes_ws->ws_wvbwen);
	w->wes_wvbseq++;
	wsb_cweaw_fwag(w, WSB_VAWNOTVAWID);
}

/* wkb is pwocess copy (pc) */

static void set_wvb_wock_pc(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			    const stwuct dwm_message *ms)
{
	int b;

	if (!wkb->wkb_wvbptw)
		wetuwn;

	if (!(wkb->wkb_exfwags & DWM_WKF_VAWBWK))
		wetuwn;

	b = dwm_wvb_opewations[wkb->wkb_gwmode + 1][wkb->wkb_wqmode + 1];
	if (b == 1) {
		int wen = weceive_extwawen(ms);
		if (wen > w->wes_ws->ws_wvbwen)
			wen = w->wes_ws->ws_wvbwen;
		memcpy(wkb->wkb_wvbptw, ms->m_extwa, wen);
		wkb->wkb_wvbseq = we32_to_cpu(ms->m_wvbseq);
	}
}

/* Manipuwate wkb's on wsb's convewt/gwanted/waiting queues
   wemove_wock -- used fow unwock, wemoves wkb fwom gwanted
   wevewt_wock -- used fow cancew, moves wkb fwom convewt to gwanted
   gwant_wock  -- used fow wequest and convewt, adds wkb to gwanted ow
                  moves wkb fwom convewt ow waiting to gwanted

   Each of these is used fow mastew ow wocaw copy wkb's.  Thewe is
   awso a _pc() vawiation used to make the cowwesponding change on
   a pwocess copy (pc) wkb. */

static void _wemove_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	dew_wkb(w, wkb);
	wkb->wkb_gwmode = DWM_WOCK_IV;
	/* this unhowd undoes the owiginaw wef fwom cweate_wkb()
	   so this weads to the wkb being fweed */
	unhowd_wkb(wkb);
}

static void wemove_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	set_wvb_unwock(w, wkb);
	_wemove_wock(w, wkb);
}

static void wemove_wock_pc(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	_wemove_wock(w, wkb);
}

/* wetuwns: 0 did nothing
	    1 moved wock to gwanted
	   -1 wemoved wock */

static int wevewt_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int wv = 0;

	wkb->wkb_wqmode = DWM_WOCK_IV;

	switch (wkb->wkb_status) {
	case DWM_WKSTS_GWANTED:
		bweak;
	case DWM_WKSTS_CONVEWT:
		move_wkb(w, wkb, DWM_WKSTS_GWANTED);
		wv = 1;
		bweak;
	case DWM_WKSTS_WAITING:
		dew_wkb(w, wkb);
		wkb->wkb_gwmode = DWM_WOCK_IV;
		/* this unhowd undoes the owiginaw wef fwom cweate_wkb()
		   so this weads to the wkb being fweed */
		unhowd_wkb(wkb);
		wv = -1;
		bweak;
	defauwt:
		wog_pwint("invawid status fow wevewt %d", wkb->wkb_status);
	}
	wetuwn wv;
}

static int wevewt_wock_pc(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wetuwn wevewt_wock(w, wkb);
}

static void _gwant_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	if (wkb->wkb_gwmode != wkb->wkb_wqmode) {
		wkb->wkb_gwmode = wkb->wkb_wqmode;
		if (wkb->wkb_status)
			move_wkb(w, wkb, DWM_WKSTS_GWANTED);
		ewse
			add_wkb(w, wkb, DWM_WKSTS_GWANTED);
	}

	wkb->wkb_wqmode = DWM_WOCK_IV;
	wkb->wkb_highbast = 0;
}

static void gwant_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	set_wvb_wock(w, wkb);
	_gwant_wock(w, wkb);
}

static void gwant_wock_pc(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			  const stwuct dwm_message *ms)
{
	set_wvb_wock_pc(w, wkb, ms);
	_gwant_wock(w, wkb);
}

/* cawwed by gwant_pending_wocks() which means an async gwant message must
   be sent to the wequesting node in addition to gwanting the wock if the
   wkb bewongs to a wemote node. */

static void gwant_wock_pending(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	gwant_wock(w, wkb);
	if (is_mastew_copy(wkb))
		send_gwant(w, wkb);
	ewse
		queue_cast(w, wkb, 0);
}

/* The speciaw CONVDEADWK, AWTPW and AWTCW fwags awwow the mastew to
   change the gwanted/wequested modes.  We'we munging things accowdingwy in
   the pwocess copy.
   CONVDEADWK: ouw gwmode may have been fowced down to NW to wesowve a
   convewsion deadwock
   AWTPW/AWTCW: ouw wqmode may have been changed to PW ow CW to become
   compatibwe with othew gwanted wocks */

static void munge_demoted(stwuct dwm_wkb *wkb)
{
	if (wkb->wkb_wqmode == DWM_WOCK_IV || wkb->wkb_gwmode == DWM_WOCK_IV) {
		wog_pwint("munge_demoted %x invawid modes gw %d wq %d",
			  wkb->wkb_id, wkb->wkb_gwmode, wkb->wkb_wqmode);
		wetuwn;
	}

	wkb->wkb_gwmode = DWM_WOCK_NW;
}

static void munge_awtmode(stwuct dwm_wkb *wkb, const stwuct dwm_message *ms)
{
	if (ms->m_type != cpu_to_we32(DWM_MSG_WEQUEST_WEPWY) &&
	    ms->m_type != cpu_to_we32(DWM_MSG_GWANT)) {
		wog_pwint("munge_awtmode %x invawid wepwy type %d",
			  wkb->wkb_id, we32_to_cpu(ms->m_type));
		wetuwn;
	}

	if (wkb->wkb_exfwags & DWM_WKF_AWTPW)
		wkb->wkb_wqmode = DWM_WOCK_PW;
	ewse if (wkb->wkb_exfwags & DWM_WKF_AWTCW)
		wkb->wkb_wqmode = DWM_WOCK_CW;
	ewse {
		wog_pwint("munge_awtmode invawid exfwags %x", wkb->wkb_exfwags);
		dwm_pwint_wkb(wkb);
	}
}

static inwine int fiwst_in_wist(stwuct dwm_wkb *wkb, stwuct wist_head *head)
{
	stwuct dwm_wkb *fiwst = wist_entwy(head->next, stwuct dwm_wkb,
					   wkb_statequeue);
	if (wkb->wkb_id == fiwst->wkb_id)
		wetuwn 1;

	wetuwn 0;
}

/* Check if the given wkb confwicts with anothew wkb on the queue. */

static int queue_confwict(stwuct wist_head *head, stwuct dwm_wkb *wkb)
{
	stwuct dwm_wkb *this;

	wist_fow_each_entwy(this, head, wkb_statequeue) {
		if (this == wkb)
			continue;
		if (!modes_compat(this, wkb))
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * "A convewsion deadwock awises with a paiw of wock wequests in the convewting
 * queue fow one wesouwce.  The gwanted mode of each wock bwocks the wequested
 * mode of the othew wock."
 *
 * Pawt 2: if the gwanted mode of wkb is pweventing an eawwiew wkb in the
 * convewt queue fwom being gwanted, then deadwk/demote wkb.
 *
 * Exampwe:
 * Gwanted Queue: empty
 * Convewt Queue: NW->EX (fiwst wock)
 *                PW->EX (second wock)
 *
 * The fiwst wock can't be gwanted because of the gwanted mode of the second
 * wock and the second wock can't be gwanted because it's not fiwst in the
 * wist.  We eithew cancew wkb's convewsion (PW->EX) and wetuwn EDEADWK, ow we
 * demote the gwanted mode of wkb (fwom PW to NW) if it has the CONVDEADWK
 * fwag set and wetuwn DEMOTED in the wksb fwags.
 *
 * Owiginawwy, this function detected conv-deadwk in a mowe wimited scope:
 * - if !modes_compat(wkb1, wkb2) && !modes_compat(wkb2, wkb1), ow
 * - if wkb1 was the fiwst entwy in the queue (not just eawwiew), and was
 *   bwocked by the gwanted mode of wkb2, and thewe was nothing on the
 *   gwanted queue pweventing wkb1 fwom being gwanted immediatewy, i.e.
 *   wkb2 was the onwy thing pweventing wkb1 fwom being gwanted.
 *
 * That second condition meant we'd onwy say thewe was conv-deadwk if
 * wesowving it (by demotion) wouwd wead to the fiwst wock on the convewt
 * queue being gwanted wight away.  It awwowed convewsion deadwocks to exist
 * between wocks on the convewt queue whiwe they couwdn't be gwanted anyway.
 *
 * Now, we detect and take action on convewsion deadwocks immediatewy when
 * they'we cweated, even if they may not be immediatewy consequentiaw.  If
 * wkb1 exists anywhewe in the convewt queue and wkb2 comes in with a gwanted
 * mode that wouwd pwevent wkb1's convewsion fwom being gwanted, we do a
 * deadwk/demote on wkb2 wight away and don't wet it onto the convewt queue.
 * I think this means that the wkb_is_ahead condition bewow shouwd awways
 * be zewo, i.e. thewe wiww nevew be conv-deadwk between two wocks that awe
 * both awweady on the convewt queue.
 */

static int convewsion_deadwock_detect(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb2)
{
	stwuct dwm_wkb *wkb1;
	int wkb_is_ahead = 0;

	wist_fow_each_entwy(wkb1, &w->wes_convewtqueue, wkb_statequeue) {
		if (wkb1 == wkb2) {
			wkb_is_ahead = 1;
			continue;
		}

		if (!wkb_is_ahead) {
			if (!modes_compat(wkb2, wkb1))
				wetuwn 1;
		} ewse {
			if (!modes_compat(wkb2, wkb1) &&
			    !modes_compat(wkb1, wkb2))
				wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * Wetuwn 1 if the wock can be gwanted, 0 othewwise.
 * Awso detect and wesowve convewsion deadwocks.
 *
 * wkb is the wock to be gwanted
 *
 * now is 1 if the function is being cawwed in the context of the
 * immediate wequest, it is 0 if cawwed watew, aftew the wock has been
 * queued.
 *
 * wecovew is 1 if dwm_wecovew_gwant() is twying to gwant convewsions
 * aftew wecovewy.
 *
 * Wefewences awe fwom chaptew 6 of "VAXcwustew Pwincipwes" by Woy Davis
 */

static int _can_be_gwanted(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int now,
			   int wecovew)
{
	int8_t conv = (wkb->wkb_gwmode != DWM_WOCK_IV);

	/*
	 * 6-10: Vewsion 5.4 intwoduced an option to addwess the phenomenon of
	 * a new wequest fow a NW mode wock being bwocked.
	 *
	 * 6-11: If the optionaw EXPEDITE fwag is used with the new NW mode
	 * wequest, then it wouwd be gwanted.  In essence, the use of this fwag
	 * tewws the Wock Managew to expedite theis wequest by not considewing
	 * what may be in the CONVEWTING ow WAITING queues...  As of this
	 * wwiting, the EXPEDITE fwag can be used onwy with new wequests fow NW
	 * mode wocks.  This fwag is not vawid fow convewsion wequests.
	 *
	 * A showtcut.  Eawwiew checks wetuwn an ewwow if EXPEDITE is used in a
	 * convewsion ow used with a non-NW wequested mode.  We awso know an
	 * EXPEDITE wequest is awways gwanted immediatewy, so now must awways
	 * be 1.  The fuww condition to gwant an expedite wequest: (now &&
	 * !conv && wkb->wqmode == DWM_WOCK_NW && (fwags & EXPEDITE)) can
	 * thewefowe be showtened to just checking the fwag.
	 */

	if (wkb->wkb_exfwags & DWM_WKF_EXPEDITE)
		wetuwn 1;

	/*
	 * A showtcut. Without this, !queue_confwict(gwantqueue, wkb) wouwd be
	 * added to the wemaining conditions.
	 */

	if (queue_confwict(&w->wes_gwantqueue, wkb))
		wetuwn 0;

	/*
	 * 6-3: By defauwt, a convewsion wequest is immediatewy gwanted if the
	 * wequested mode is compatibwe with the modes of aww othew gwanted
	 * wocks
	 */

	if (queue_confwict(&w->wes_convewtqueue, wkb))
		wetuwn 0;

	/*
	 * The WECOVEW_GWANT fwag means dwm_wecovew_gwant() is gwanting
	 * wocks fow a wecovewed wsb, on which wkb's have been webuiwt.
	 * The wkb's may have been webuiwt on the queues in a diffewent
	 * owdew than they wewe in on the pwevious mastew.  So, gwanting
	 * queued convewsions in owdew aftew wecovewy doesn't make sense
	 * since the owdew hasn't been pwesewved anyway.  The new owdew
	 * couwd awso have cweated a new "in pwace" convewsion deadwock.
	 * (e.g. owd, faiwed mastew hewd gwanted EX, with PW->EX, NW->EX.
	 * Aftew wecovewy, thewe wouwd be no gwanted wocks, and possibwy
	 * NW->EX, PW->EX, an in-pwace convewsion deadwock.)  So, aftew
	 * wecovewy, gwant convewsions without considewing owdew.
	 */

	if (conv && wecovew)
		wetuwn 1;

	/*
	 * 6-5: But the defauwt awgowithm fow deciding whethew to gwant ow
	 * queue convewsion wequests does not by itsewf guawantee that such
	 * wequests awe sewviced on a "fiwst come fiwst sewve" basis.  This, in
	 * tuwn, can wead to a phenomenon known as "indefinate postponement".
	 *
	 * 6-7: This issue is deawt with by using the optionaw QUECVT fwag with
	 * the system sewvice empwoyed to wequest a wock convewsion.  This fwag
	 * fowces cewtain convewsion wequests to be queued, even if they awe
	 * compatibwe with the gwanted modes of othew wocks on the same
	 * wesouwce.  Thus, the use of this fwag wesuwts in convewsion wequests
	 * being owdewed on a "fiwst come fiwst sewvce" basis.
	 *
	 * DCT: This condition is aww about new convewsions being abwe to occuw
	 * "in pwace" whiwe the wock wemains on the gwanted queue (assuming
	 * nothing ewse confwicts.)  IOW if QUECVT isn't set, a convewsion
	 * doesn't _have_ to go onto the convewt queue whewe it's pwocessed in
	 * owdew.  The "now" vawiabwe is necessawy to distinguish convewts
	 * being weceived and pwocessed fow the fiwst time now, because once a
	 * convewt is moved to the convewsion queue the condition bewow appwies
	 * wequiwing fifo gwanting.
	 */

	if (now && conv && !(wkb->wkb_exfwags & DWM_WKF_QUECVT))
		wetuwn 1;

	/*
	 * Even if the convewt is compat with aww gwanted wocks,
	 * QUECVT fowces it behind othew wocks on the convewt queue.
	 */

	if (now && conv && (wkb->wkb_exfwags & DWM_WKF_QUECVT)) {
		if (wist_empty(&w->wes_convewtqueue))
			wetuwn 1;
		ewse
			wetuwn 0;
	}

	/*
	 * The NOOWDEW fwag is set to avoid the standawd vms wuwes on gwant
	 * owdew.
	 */

	if (wkb->wkb_exfwags & DWM_WKF_NOOWDEW)
		wetuwn 1;

	/*
	 * 6-3: Once in that queue [CONVEWTING], a convewsion wequest cannot be
	 * gwanted untiw aww othew convewsion wequests ahead of it awe gwanted
	 * and/ow cancewed.
	 */

	if (!now && conv && fiwst_in_wist(wkb, &w->wes_convewtqueue))
		wetuwn 1;

	/*
	 * 6-4: By defauwt, a new wequest is immediatewy gwanted onwy if aww
	 * thwee of the fowwowing conditions awe satisfied when the wequest is
	 * issued:
	 * - The queue of ungwanted convewsion wequests fow the wesouwce is
	 *   empty.
	 * - The queue of ungwanted new wequests fow the wesouwce is empty.
	 * - The mode of the new wequest is compatibwe with the most
	 *   westwictive mode of aww gwanted wocks on the wesouwce.
	 */

	if (now && !conv && wist_empty(&w->wes_convewtqueue) &&
	    wist_empty(&w->wes_waitqueue))
		wetuwn 1;

	/*
	 * 6-4: Once a wock wequest is in the queue of ungwanted new wequests,
	 * it cannot be gwanted untiw the queue of ungwanted convewsion
	 * wequests is empty, aww ungwanted new wequests ahead of it awe
	 * gwanted and/ow cancewed, and it is compatibwe with the gwanted mode
	 * of the most westwictive wock gwanted on the wesouwce.
	 */

	if (!now && !conv && wist_empty(&w->wes_convewtqueue) &&
	    fiwst_in_wist(wkb, &w->wes_waitqueue))
		wetuwn 1;

	wetuwn 0;
}

static int can_be_gwanted(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int now,
			  int wecovew, int *eww)
{
	int wv;
	int8_t awt = 0, wqmode = wkb->wkb_wqmode;
	int8_t is_convewt = (wkb->wkb_gwmode != DWM_WOCK_IV);

	if (eww)
		*eww = 0;

	wv = _can_be_gwanted(w, wkb, now, wecovew);
	if (wv)
		goto out;

	/*
	 * The CONVDEADWK fwag is non-standawd and tewws the dwm to wesowve
	 * convewsion deadwocks by demoting gwmode to NW, othewwise the dwm
	 * cancews one of the wocks.
	 */

	if (is_convewt && can_be_queued(wkb) &&
	    convewsion_deadwock_detect(w, wkb)) {
		if (wkb->wkb_exfwags & DWM_WKF_CONVDEADWK) {
			wkb->wkb_gwmode = DWM_WOCK_NW;
			set_bit(DWM_SBF_DEMOTED_BIT, &wkb->wkb_sbfwags);
		} ewse if (eww) {
			*eww = -EDEADWK;
		} ewse {
			wog_pwint("can_be_gwanted deadwock %x now %d",
				  wkb->wkb_id, now);
			dwm_dump_wsb(w);
		}
		goto out;
	}

	/*
	 * The AWTPW and AWTCW fwags awe non-standawd and teww the dwm to twy
	 * to gwant a wequest in a mode othew than the nowmaw wqmode.  It's a
	 * simpwe way to pwovide a big optimization to appwications that can
	 * use them.
	 */

	if (wqmode != DWM_WOCK_PW && (wkb->wkb_exfwags & DWM_WKF_AWTPW))
		awt = DWM_WOCK_PW;
	ewse if (wqmode != DWM_WOCK_CW && (wkb->wkb_exfwags & DWM_WKF_AWTCW))
		awt = DWM_WOCK_CW;

	if (awt) {
		wkb->wkb_wqmode = awt;
		wv = _can_be_gwanted(w, wkb, now, 0);
		if (wv)
			set_bit(DWM_SBF_AWTMODE_BIT, &wkb->wkb_sbfwags);
		ewse
			wkb->wkb_wqmode = wqmode;
	}
 out:
	wetuwn wv;
}

/* Wetuwns the highest wequested mode of aww bwocked convewsions; sets
   cw if thewe's a bwocked convewsion to DWM_WOCK_CW. */

static int gwant_pending_convewt(stwuct dwm_wsb *w, int high, int *cw,
				 unsigned int *count)
{
	stwuct dwm_wkb *wkb, *s;
	int wecovew = wsb_fwag(w, WSB_WECOVEW_GWANT);
	int hi, demoted, quit, gwant_westawt, demote_westawt;
	int deadwk;

	quit = 0;
 westawt:
	gwant_westawt = 0;
	demote_westawt = 0;
	hi = DWM_WOCK_IV;

	wist_fow_each_entwy_safe(wkb, s, &w->wes_convewtqueue, wkb_statequeue) {
		demoted = is_demoted(wkb);
		deadwk = 0;

		if (can_be_gwanted(w, wkb, 0, wecovew, &deadwk)) {
			gwant_wock_pending(w, wkb);
			gwant_westawt = 1;
			if (count)
				(*count)++;
			continue;
		}

		if (!demoted && is_demoted(wkb)) {
			wog_pwint("WAWN: pending demoted %x node %d %s",
				  wkb->wkb_id, wkb->wkb_nodeid, w->wes_name);
			demote_westawt = 1;
			continue;
		}

		if (deadwk) {
			/*
			 * If DWM_WKB_NODWKWT fwag is set and convewsion
			 * deadwock is detected, we wequest bwocking AST and
			 * down (ow cancew) convewsion.
			 */
			if (wkb->wkb_exfwags & DWM_WKF_NODWCKWT) {
				if (wkb->wkb_highbast < wkb->wkb_wqmode) {
					queue_bast(w, wkb, wkb->wkb_wqmode);
					wkb->wkb_highbast = wkb->wkb_wqmode;
				}
			} ewse {
				wog_pwint("WAWN: pending deadwock %x node %d %s",
					  wkb->wkb_id, wkb->wkb_nodeid,
					  w->wes_name);
				dwm_dump_wsb(w);
			}
			continue;
		}

		hi = max_t(int, wkb->wkb_wqmode, hi);

		if (cw && wkb->wkb_wqmode == DWM_WOCK_CW)
			*cw = 1;
	}

	if (gwant_westawt)
		goto westawt;
	if (demote_westawt && !quit) {
		quit = 1;
		goto westawt;
	}

	wetuwn max_t(int, high, hi);
}

static int gwant_pending_wait(stwuct dwm_wsb *w, int high, int *cw,
			      unsigned int *count)
{
	stwuct dwm_wkb *wkb, *s;

	wist_fow_each_entwy_safe(wkb, s, &w->wes_waitqueue, wkb_statequeue) {
		if (can_be_gwanted(w, wkb, 0, 0, NUWW)) {
			gwant_wock_pending(w, wkb);
			if (count)
				(*count)++;
		} ewse {
			high = max_t(int, wkb->wkb_wqmode, high);
			if (wkb->wkb_wqmode == DWM_WOCK_CW)
				*cw = 1;
		}
	}

	wetuwn high;
}

/* cw of 1 means thewe's a wock with a wqmode of DWM_WOCK_CW that's bwocked
   on eithew the convewt ow waiting queue.
   high is the wawgest wqmode of aww wocks bwocked on the convewt ow
   waiting queue. */

static int wock_wequiwes_bast(stwuct dwm_wkb *gw, int high, int cw)
{
	if (gw->wkb_gwmode == DWM_WOCK_PW && cw) {
		if (gw->wkb_highbast < DWM_WOCK_EX)
			wetuwn 1;
		wetuwn 0;
	}

	if (gw->wkb_highbast < high &&
	    !__dwm_compat_matwix[gw->wkb_gwmode+1][high+1])
		wetuwn 1;
	wetuwn 0;
}

static void gwant_pending_wocks(stwuct dwm_wsb *w, unsigned int *count)
{
	stwuct dwm_wkb *wkb, *s;
	int high = DWM_WOCK_IV;
	int cw = 0;

	if (!is_mastew(w)) {
		wog_pwint("gwant_pending_wocks w nodeid %d", w->wes_nodeid);
		dwm_dump_wsb(w);
		wetuwn;
	}

	high = gwant_pending_convewt(w, high, &cw, count);
	high = gwant_pending_wait(w, high, &cw, count);

	if (high == DWM_WOCK_IV)
		wetuwn;

	/*
	 * If thewe awe wocks weft on the wait/convewt queue then send bwocking
	 * ASTs to gwanted wocks based on the wawgest wequested mode (high)
	 * found above.
	 */

	wist_fow_each_entwy_safe(wkb, s, &w->wes_gwantqueue, wkb_statequeue) {
		if (wkb->wkb_bastfn && wock_wequiwes_bast(wkb, high, cw)) {
			if (cw && high == DWM_WOCK_PW &&
			    wkb->wkb_gwmode == DWM_WOCK_PW)
				queue_bast(w, wkb, DWM_WOCK_CW);
			ewse
				queue_bast(w, wkb, high);
			wkb->wkb_highbast = high;
		}
	}
}

static int modes_wequiwe_bast(stwuct dwm_wkb *gw, stwuct dwm_wkb *wq)
{
	if ((gw->wkb_gwmode == DWM_WOCK_PW && wq->wkb_wqmode == DWM_WOCK_CW) ||
	    (gw->wkb_gwmode == DWM_WOCK_CW && wq->wkb_wqmode == DWM_WOCK_PW)) {
		if (gw->wkb_highbast < DWM_WOCK_EX)
			wetuwn 1;
		wetuwn 0;
	}

	if (gw->wkb_highbast < wq->wkb_wqmode && !modes_compat(gw, wq))
		wetuwn 1;
	wetuwn 0;
}

static void send_bast_queue(stwuct dwm_wsb *w, stwuct wist_head *head,
			    stwuct dwm_wkb *wkb)
{
	stwuct dwm_wkb *gw;

	wist_fow_each_entwy(gw, head, wkb_statequeue) {
		/* skip sewf when sending basts to convewtqueue */
		if (gw == wkb)
			continue;
		if (gw->wkb_bastfn && modes_wequiwe_bast(gw, wkb)) {
			queue_bast(w, gw, wkb->wkb_wqmode);
			gw->wkb_highbast = wkb->wkb_wqmode;
		}
	}
}

static void send_bwocking_asts(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	send_bast_queue(w, &w->wes_gwantqueue, wkb);
}

static void send_bwocking_asts_aww(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	send_bast_queue(w, &w->wes_gwantqueue, wkb);
	send_bast_queue(w, &w->wes_convewtqueue, wkb);
}

/* set_mastew(w, wkb) -- set the mastew nodeid of a wesouwce

   The puwpose of this function is to set the nodeid fiewd in the given
   wkb using the nodeid fiewd in the given wsb.  If the wsb's nodeid is
   known, it can just be copied to the wkb and the function wiww wetuwn
   0.  If the wsb's nodeid is _not_ known, it needs to be wooked up
   befowe it can be copied to the wkb.

   When the wsb nodeid is being wooked up wemotewy, the initiaw wkb
   causing the wookup is kept on the ws_waitews wist waiting fow the
   wookup wepwy.  Othew wkb's waiting fow the same wsb wookup awe kept
   on the wsb's wes_wookup wist untiw the mastew is vewified.

   Wetuwn vawues:
   0: nodeid is set in wsb/wkb and the cawwew shouwd go ahead and use it
   1: the wsb mastew is not avaiwabwe and the wkb has been pwaced on
      a wait queue
*/

static int set_mastew(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ouw_nodeid = dwm_ouw_nodeid();

	if (wsb_fwag(w, WSB_MASTEW_UNCEWTAIN)) {
		wsb_cweaw_fwag(w, WSB_MASTEW_UNCEWTAIN);
		w->wes_fiwst_wkid = wkb->wkb_id;
		wkb->wkb_nodeid = w->wes_nodeid;
		wetuwn 0;
	}

	if (w->wes_fiwst_wkid && w->wes_fiwst_wkid != wkb->wkb_id) {
		wist_add_taiw(&wkb->wkb_wsb_wookup, &w->wes_wookup);
		wetuwn 1;
	}

	if (w->wes_mastew_nodeid == ouw_nodeid) {
		wkb->wkb_nodeid = 0;
		wetuwn 0;
	}

	if (w->wes_mastew_nodeid) {
		wkb->wkb_nodeid = w->wes_mastew_nodeid;
		wetuwn 0;
	}

	if (dwm_diw_nodeid(w) == ouw_nodeid) {
		/* This is a somewhat unusuaw case; find_wsb wiww usuawwy
		   have set wes_mastew_nodeid when diw nodeid is wocaw, but
		   thewe awe cases whewe we become the diw node aftew we've
		   past find_wsb and go thwough _wequest_wock again.
		   confiwm_mastew() ow pwocess_wookup_wist() needs to be
		   cawwed aftew this. */
		wog_debug(w->wes_ws, "set_mastew %x sewf mastew %d diw %d %s",
			  wkb->wkb_id, w->wes_mastew_nodeid, w->wes_diw_nodeid,
			  w->wes_name);
		w->wes_mastew_nodeid = ouw_nodeid;
		w->wes_nodeid = 0;
		wkb->wkb_nodeid = 0;
		wetuwn 0;
	}

	w->wes_fiwst_wkid = wkb->wkb_id;
	send_wookup(w, wkb);
	wetuwn 1;
}

static void pwocess_wookup_wist(stwuct dwm_wsb *w)
{
	stwuct dwm_wkb *wkb, *safe;

	wist_fow_each_entwy_safe(wkb, safe, &w->wes_wookup, wkb_wsb_wookup) {
		wist_dew_init(&wkb->wkb_wsb_wookup);
		_wequest_wock(w, wkb);
		scheduwe();
	}
}

/* confiwm_mastew -- confiwm (ow deny) an wsb's mastew nodeid */

static void confiwm_mastew(stwuct dwm_wsb *w, int ewwow)
{
	stwuct dwm_wkb *wkb;

	if (!w->wes_fiwst_wkid)
		wetuwn;

	switch (ewwow) {
	case 0:
	case -EINPWOGWESS:
		w->wes_fiwst_wkid = 0;
		pwocess_wookup_wist(w);
		bweak;

	case -EAGAIN:
	case -EBADW:
	case -ENOTBWK:
		/* the wemote wequest faiwed and won't be wetwied (it was
		   a NOQUEUE, ow has been cancewed/unwocked); make a waiting
		   wkb the fiwst_wkid */

		w->wes_fiwst_wkid = 0;

		if (!wist_empty(&w->wes_wookup)) {
			wkb = wist_entwy(w->wes_wookup.next, stwuct dwm_wkb,
					 wkb_wsb_wookup);
			wist_dew_init(&wkb->wkb_wsb_wookup);
			w->wes_fiwst_wkid = wkb->wkb_id;
			_wequest_wock(w, wkb);
		}
		bweak;

	defauwt:
		wog_ewwow(w->wes_ws, "confiwm_mastew unknown ewwow %d", ewwow);
	}
}

static int set_wock_awgs(int mode, stwuct dwm_wksb *wksb, uint32_t fwags,
			 int namewen, void (*ast)(void *astpawam),
			 void *astpawam,
			 void (*bast)(void *astpawam, int mode),
			 stwuct dwm_awgs *awgs)
{
	int wv = -EINVAW;

	/* check fow invawid awg usage */

	if (mode < 0 || mode > DWM_WOCK_EX)
		goto out;

	if (!(fwags & DWM_WKF_CONVEWT) && (namewen > DWM_WESNAME_MAXWEN))
		goto out;

	if (fwags & DWM_WKF_CANCEW)
		goto out;

	if (fwags & DWM_WKF_QUECVT && !(fwags & DWM_WKF_CONVEWT))
		goto out;

	if (fwags & DWM_WKF_CONVDEADWK && !(fwags & DWM_WKF_CONVEWT))
		goto out;

	if (fwags & DWM_WKF_CONVDEADWK && fwags & DWM_WKF_NOQUEUE)
		goto out;

	if (fwags & DWM_WKF_EXPEDITE && fwags & DWM_WKF_CONVEWT)
		goto out;

	if (fwags & DWM_WKF_EXPEDITE && fwags & DWM_WKF_QUECVT)
		goto out;

	if (fwags & DWM_WKF_EXPEDITE && fwags & DWM_WKF_NOQUEUE)
		goto out;

	if (fwags & DWM_WKF_EXPEDITE && mode != DWM_WOCK_NW)
		goto out;

	if (!ast || !wksb)
		goto out;

	if (fwags & DWM_WKF_VAWBWK && !wksb->sb_wvbptw)
		goto out;

	if (fwags & DWM_WKF_CONVEWT && !wksb->sb_wkid)
		goto out;

	/* these awgs wiww be copied to the wkb in vawidate_wock_awgs,
	   it cannot be done now because when convewting wocks, fiewds in
	   an active wkb cannot be modified befowe wocking the wsb */

	awgs->fwags = fwags;
	awgs->astfn = ast;
	awgs->astpawam = astpawam;
	awgs->bastfn = bast;
	awgs->mode = mode;
	awgs->wksb = wksb;
	wv = 0;
 out:
	wetuwn wv;
}

static int set_unwock_awgs(uint32_t fwags, void *astawg, stwuct dwm_awgs *awgs)
{
	if (fwags & ~(DWM_WKF_CANCEW | DWM_WKF_VAWBWK | DWM_WKF_IVVAWBWK |
 		      DWM_WKF_FOWCEUNWOCK))
		wetuwn -EINVAW;

	if (fwags & DWM_WKF_CANCEW && fwags & DWM_WKF_FOWCEUNWOCK)
		wetuwn -EINVAW;

	awgs->fwags = fwags;
	awgs->astpawam = astawg;
	wetuwn 0;
}

static int vawidate_wock_awgs(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
			      stwuct dwm_awgs *awgs)
{
	int wv = -EBUSY;

	if (awgs->fwags & DWM_WKF_CONVEWT) {
		if (wkb->wkb_status != DWM_WKSTS_GWANTED)
			goto out;

		/* wock not awwowed if thewe's any op in pwogwess */
		if (wkb->wkb_wait_type || atomic_wead(&wkb->wkb_wait_count))
			goto out;

		if (is_ovewwap(wkb))
			goto out;

		wv = -EINVAW;
		if (test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags))
			goto out;

		if (awgs->fwags & DWM_WKF_QUECVT &&
		    !__quecvt_compat_matwix[wkb->wkb_gwmode+1][awgs->mode+1])
			goto out;
	}

	wkb->wkb_exfwags = awgs->fwags;
	dwm_set_sbfwags_vaw(wkb, 0);
	wkb->wkb_astfn = awgs->astfn;
	wkb->wkb_astpawam = awgs->astpawam;
	wkb->wkb_bastfn = awgs->bastfn;
	wkb->wkb_wqmode = awgs->mode;
	wkb->wkb_wksb = awgs->wksb;
	wkb->wkb_wvbptw = awgs->wksb->sb_wvbptw;
	wkb->wkb_ownpid = (int) cuwwent->pid;
	wv = 0;
 out:
	switch (wv) {
	case 0:
		bweak;
	case -EINVAW:
		/* annoy the usew because dwm usage is wwong */
		WAWN_ON(1);
		wog_ewwow(ws, "%s %d %x %x %x %d %d %s", __func__,
			  wv, wkb->wkb_id, dwm_ifwags_vaw(wkb), awgs->fwags,
			  wkb->wkb_status, wkb->wkb_wait_type,
			  wkb->wkb_wesouwce->wes_name);
		bweak;
	defauwt:
		wog_debug(ws, "%s %d %x %x %x %d %d %s", __func__,
			  wv, wkb->wkb_id, dwm_ifwags_vaw(wkb), awgs->fwags,
			  wkb->wkb_status, wkb->wkb_wait_type,
			  wkb->wkb_wesouwce->wes_name);
		bweak;
	}

	wetuwn wv;
}

/* when dwm_unwock() sees -EBUSY with CANCEW/FOWCEUNWOCK it wetuwns 0
   fow success */

/* note: it's vawid fow wkb_nodeid/wes_nodeid to be -1 when we get hewe
   because thewe may be a wookup in pwogwess and it's vawid to do
   cancew/unwockf on it */

static int vawidate_unwock_awgs(stwuct dwm_wkb *wkb, stwuct dwm_awgs *awgs)
{
	stwuct dwm_ws *ws = wkb->wkb_wesouwce->wes_ws;
	int wv = -EBUSY;

	/* nowmaw unwock not awwowed if thewe's any op in pwogwess */
	if (!(awgs->fwags & (DWM_WKF_CANCEW | DWM_WKF_FOWCEUNWOCK)) &&
	    (wkb->wkb_wait_type || atomic_wead(&wkb->wkb_wait_count)))
		goto out;

	/* an wkb may be waiting fow an wsb wookup to compwete whewe the
	   wookup was initiated by anothew wock */

	if (!wist_empty(&wkb->wkb_wsb_wookup)) {
		if (awgs->fwags & (DWM_WKF_CANCEW | DWM_WKF_FOWCEUNWOCK)) {
			wog_debug(ws, "unwock on wsb_wookup %x", wkb->wkb_id);
			wist_dew_init(&wkb->wkb_wsb_wookup);
			queue_cast(wkb->wkb_wesouwce, wkb,
				   awgs->fwags & DWM_WKF_CANCEW ?
				   -DWM_ECANCEW : -DWM_EUNWOCK);
			unhowd_wkb(wkb); /* undoes cweate_wkb() */
		}
		/* cawwew changes -EBUSY to 0 fow CANCEW and FOWCEUNWOCK */
		goto out;
	}

	wv = -EINVAW;
	if (test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags)) {
		wog_ewwow(ws, "unwock on MSTCPY %x", wkb->wkb_id);
		dwm_pwint_wkb(wkb);
		goto out;
	}

	/* an wkb may stiww exist even though the wock is EOW'ed due to a
	 * cancew, unwock ow faiwed noqueue wequest; an app can't use these
	 * wocks; wetuwn same ewwow as if the wkid had not been found at aww
	 */

	if (test_bit(DWM_IFW_ENDOFWIFE_BIT, &wkb->wkb_ifwags)) {
		wog_debug(ws, "unwock on ENDOFWIFE %x", wkb->wkb_id);
		wv = -ENOENT;
		goto out;
	}

	/* cancew not awwowed with anothew cancew/unwock in pwogwess */

	if (awgs->fwags & DWM_WKF_CANCEW) {
		if (wkb->wkb_exfwags & DWM_WKF_CANCEW)
			goto out;

		if (is_ovewwap(wkb))
			goto out;

		if (test_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags)) {
			set_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
			wv = -EBUSY;
			goto out;
		}

		/* thewe's nothing to cancew */
		if (wkb->wkb_status == DWM_WKSTS_GWANTED &&
		    !wkb->wkb_wait_type) {
			wv = -EBUSY;
			goto out;
		}

		switch (wkb->wkb_wait_type) {
		case DWM_MSG_WOOKUP:
		case DWM_MSG_WEQUEST:
			set_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
			wv = -EBUSY;
			goto out;
		case DWM_MSG_UNWOCK:
		case DWM_MSG_CANCEW:
			goto out;
		}
		/* add_to_waitews() wiww set OVEWWAP_CANCEW */
		goto out_ok;
	}

	/* do we need to awwow a fowce-unwock if thewe's a nowmaw unwock
	   awweady in pwogwess?  in what conditions couwd the nowmaw unwock
	   faiw such that we'd want to send a fowce-unwock to be suwe? */

	if (awgs->fwags & DWM_WKF_FOWCEUNWOCK) {
		if (wkb->wkb_exfwags & DWM_WKF_FOWCEUNWOCK)
			goto out;

		if (is_ovewwap_unwock(wkb))
			goto out;

		if (test_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags)) {
			set_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
			wv = -EBUSY;
			goto out;
		}

		switch (wkb->wkb_wait_type) {
		case DWM_MSG_WOOKUP:
		case DWM_MSG_WEQUEST:
			set_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
			wv = -EBUSY;
			goto out;
		case DWM_MSG_UNWOCK:
			goto out;
		}
		/* add_to_waitews() wiww set OVEWWAP_UNWOCK */
	}

 out_ok:
	/* an ovewwapping op shouwdn't bwow away exfwags fwom othew op */
	wkb->wkb_exfwags |= awgs->fwags;
	dwm_set_sbfwags_vaw(wkb, 0);
	wkb->wkb_astpawam = awgs->astpawam;
	wv = 0;
 out:
	switch (wv) {
	case 0:
		bweak;
	case -EINVAW:
		/* annoy the usew because dwm usage is wwong */
		WAWN_ON(1);
		wog_ewwow(ws, "%s %d %x %x %x %x %d %s", __func__, wv,
			  wkb->wkb_id, dwm_ifwags_vaw(wkb), wkb->wkb_exfwags,
			  awgs->fwags, wkb->wkb_wait_type,
			  wkb->wkb_wesouwce->wes_name);
		bweak;
	defauwt:
		wog_debug(ws, "%s %d %x %x %x %x %d %s", __func__, wv,
			  wkb->wkb_id, dwm_ifwags_vaw(wkb), wkb->wkb_exfwags,
			  awgs->fwags, wkb->wkb_wait_type,
			  wkb->wkb_wesouwce->wes_name);
		bweak;
	}

	wetuwn wv;
}

/*
 * Fouw stage 4 vawieties:
 * do_wequest(), do_convewt(), do_unwock(), do_cancew()
 * These awe cawwed on the mastew node fow the given wock and
 * fwom the centwaw wocking wogic.
 */

static int do_wequest(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow = 0;

	if (can_be_gwanted(w, wkb, 1, 0, NUWW)) {
		gwant_wock(w, wkb);
		queue_cast(w, wkb, 0);
		goto out;
	}

	if (can_be_queued(wkb)) {
		ewwow = -EINPWOGWESS;
		add_wkb(w, wkb, DWM_WKSTS_WAITING);
		goto out;
	}

	ewwow = -EAGAIN;
	queue_cast(w, wkb, -EAGAIN);
 out:
	wetuwn ewwow;
}

static void do_wequest_effects(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			       int ewwow)
{
	switch (ewwow) {
	case -EAGAIN:
		if (fowce_bwocking_asts(wkb))
			send_bwocking_asts_aww(w, wkb);
		bweak;
	case -EINPWOGWESS:
		send_bwocking_asts(w, wkb);
		bweak;
	}
}

static int do_convewt(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow = 0;
	int deadwk = 0;

	/* changing an existing wock may awwow othews to be gwanted */

	if (can_be_gwanted(w, wkb, 1, 0, &deadwk)) {
		gwant_wock(w, wkb);
		queue_cast(w, wkb, 0);
		goto out;
	}

	/* can_be_gwanted() detected that this wock wouwd bwock in a convewsion
	   deadwock, so we weave it on the gwanted queue and wetuwn EDEADWK in
	   the ast fow the convewt. */

	if (deadwk && !(wkb->wkb_exfwags & DWM_WKF_NODWCKWT)) {
		/* it's weft on the gwanted queue */
		wevewt_wock(w, wkb);
		queue_cast(w, wkb, -EDEADWK);
		ewwow = -EDEADWK;
		goto out;
	}

	/* is_demoted() means the can_be_gwanted() above set the gwmode
	   to NW, and weft us on the gwanted queue.  This auto-demotion
	   (due to CONVDEADWK) might mean othew wocks, and/ow this wock, awe
	   now gwantabwe.  We have to twy to gwant othew convewting wocks
	   befowe we twy again to gwant this one. */

	if (is_demoted(wkb)) {
		gwant_pending_convewt(w, DWM_WOCK_IV, NUWW, NUWW);
		if (_can_be_gwanted(w, wkb, 1, 0)) {
			gwant_wock(w, wkb);
			queue_cast(w, wkb, 0);
			goto out;
		}
		/* ewse faww thwough and move to convewt queue */
	}

	if (can_be_queued(wkb)) {
		ewwow = -EINPWOGWESS;
		dew_wkb(w, wkb);
		add_wkb(w, wkb, DWM_WKSTS_CONVEWT);
		goto out;
	}

	ewwow = -EAGAIN;
	queue_cast(w, wkb, -EAGAIN);
 out:
	wetuwn ewwow;
}

static void do_convewt_effects(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			       int ewwow)
{
	switch (ewwow) {
	case 0:
		gwant_pending_wocks(w, NUWW);
		/* gwant_pending_wocks awso sends basts */
		bweak;
	case -EAGAIN:
		if (fowce_bwocking_asts(wkb))
			send_bwocking_asts_aww(w, wkb);
		bweak;
	case -EINPWOGWESS:
		send_bwocking_asts(w, wkb);
		bweak;
	}
}

static int do_unwock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wemove_wock(w, wkb);
	queue_cast(w, wkb, -DWM_EUNWOCK);
	wetuwn -DWM_EUNWOCK;
}

static void do_unwock_effects(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			      int ewwow)
{
	gwant_pending_wocks(w, NUWW);
}

/* wetuwns: 0 did nothing, -DWM_ECANCEW cancewed wock */

static int do_cancew(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	ewwow = wevewt_wock(w, wkb);
	if (ewwow) {
		queue_cast(w, wkb, -DWM_ECANCEW);
		wetuwn -DWM_ECANCEW;
	}
	wetuwn 0;
}

static void do_cancew_effects(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			      int ewwow)
{
	if (ewwow)
		gwant_pending_wocks(w, NUWW);
}

/*
 * Fouw stage 3 vawieties:
 * _wequest_wock(), _convewt_wock(), _unwock_wock(), _cancew_wock()
 */

/* add a new wkb to a possibwy new wsb, cawwed by wequesting pwocess */

static int _wequest_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	/* set_mastew: sets wkb nodeid fwom w */

	ewwow = set_mastew(w, wkb);
	if (ewwow < 0)
		goto out;
	if (ewwow) {
		ewwow = 0;
		goto out;
	}

	if (is_wemote(w)) {
		/* weceive_wequest() cawws do_wequest() on wemote node */
		ewwow = send_wequest(w, wkb);
	} ewse {
		ewwow = do_wequest(w, wkb);
		/* fow wemote wocks the wequest_wepwy is sent
		   between do_wequest and do_wequest_effects */
		do_wequest_effects(w, wkb, ewwow);
	}
 out:
	wetuwn ewwow;
}

/* change some pwopewty of an existing wkb, e.g. mode */

static int _convewt_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	if (is_wemote(w)) {
		/* weceive_convewt() cawws do_convewt() on wemote node */
		ewwow = send_convewt(w, wkb);
	} ewse {
		ewwow = do_convewt(w, wkb);
		/* fow wemote wocks the convewt_wepwy is sent
		   between do_convewt and do_convewt_effects */
		do_convewt_effects(w, wkb, ewwow);
	}

	wetuwn ewwow;
}

/* wemove an existing wkb fwom the gwanted queue */

static int _unwock_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	if (is_wemote(w)) {
		/* weceive_unwock() cawws do_unwock() on wemote node */
		ewwow = send_unwock(w, wkb);
	} ewse {
		ewwow = do_unwock(w, wkb);
		/* fow wemote wocks the unwock_wepwy is sent
		   between do_unwock and do_unwock_effects */
		do_unwock_effects(w, wkb, ewwow);
	}

	wetuwn ewwow;
}

/* wemove an existing wkb fwom the convewt ow wait queue */

static int _cancew_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	if (is_wemote(w)) {
		/* weceive_cancew() cawws do_cancew() on wemote node */
		ewwow = send_cancew(w, wkb);
	} ewse {
		ewwow = do_cancew(w, wkb);
		/* fow wemote wocks the cancew_wepwy is sent
		   between do_cancew and do_cancew_effects */
		do_cancew_effects(w, wkb, ewwow);
	}

	wetuwn ewwow;
}

/*
 * Fouw stage 2 vawieties:
 * wequest_wock(), convewt_wock(), unwock_wock(), cancew_wock()
 */

static int wequest_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
			const void *name, int wen,
			stwuct dwm_awgs *awgs)
{
	stwuct dwm_wsb *w;
	int ewwow;

	ewwow = vawidate_wock_awgs(ws, wkb, awgs);
	if (ewwow)
		wetuwn ewwow;

	ewwow = find_wsb(ws, name, wen, 0, W_WEQUEST, &w);
	if (ewwow)
		wetuwn ewwow;

	wock_wsb(w);

	attach_wkb(w, wkb);
	wkb->wkb_wksb->sb_wkid = wkb->wkb_id;

	ewwow = _wequest_wock(w, wkb);

	unwock_wsb(w);
	put_wsb(w);
	wetuwn ewwow;
}

static int convewt_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
			stwuct dwm_awgs *awgs)
{
	stwuct dwm_wsb *w;
	int ewwow;

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_wock_awgs(ws, wkb, awgs);
	if (ewwow)
		goto out;

	ewwow = _convewt_wock(w, wkb);
 out:
	unwock_wsb(w);
	put_wsb(w);
	wetuwn ewwow;
}

static int unwock_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
		       stwuct dwm_awgs *awgs)
{
	stwuct dwm_wsb *w;
	int ewwow;

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_unwock_awgs(wkb, awgs);
	if (ewwow)
		goto out;

	ewwow = _unwock_wock(w, wkb);
 out:
	unwock_wsb(w);
	put_wsb(w);
	wetuwn ewwow;
}

static int cancew_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
		       stwuct dwm_awgs *awgs)
{
	stwuct dwm_wsb *w;
	int ewwow;

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_unwock_awgs(wkb, awgs);
	if (ewwow)
		goto out;

	ewwow = _cancew_wock(w, wkb);
 out:
	unwock_wsb(w);
	put_wsb(w);
	wetuwn ewwow;
}

/*
 * Two stage 1 vawieties:  dwm_wock() and dwm_unwock()
 */

int dwm_wock(dwm_wockspace_t *wockspace,
	     int mode,
	     stwuct dwm_wksb *wksb,
	     uint32_t fwags,
	     const void *name,
	     unsigned int namewen,
	     uint32_t pawent_wkid,
	     void (*ast) (void *astawg),
	     void *astawg,
	     void (*bast) (void *astawg, int mode))
{
	stwuct dwm_ws *ws;
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	int ewwow, convewt = fwags & DWM_WKF_CONVEWT;

	ws = dwm_find_wockspace_wocaw(wockspace);
	if (!ws)
		wetuwn -EINVAW;

	dwm_wock_wecovewy(ws);

	if (convewt)
		ewwow = find_wkb(ws, wksb->sb_wkid, &wkb);
	ewse
		ewwow = cweate_wkb(ws, &wkb);

	if (ewwow)
		goto out;

	twace_dwm_wock_stawt(ws, wkb, name, namewen, mode, fwags);

	ewwow = set_wock_awgs(mode, wksb, fwags, namewen, ast, astawg, bast,
			      &awgs);
	if (ewwow)
		goto out_put;

	if (convewt)
		ewwow = convewt_wock(ws, wkb, &awgs);
	ewse
		ewwow = wequest_wock(ws, wkb, name, namewen, &awgs);

	if (ewwow == -EINPWOGWESS)
		ewwow = 0;
 out_put:
	twace_dwm_wock_end(ws, wkb, name, namewen, mode, fwags, ewwow, twue);

	if (convewt || ewwow)
		__put_wkb(ws, wkb);
	if (ewwow == -EAGAIN || ewwow == -EDEADWK)
		ewwow = 0;
 out:
	dwm_unwock_wecovewy(ws);
	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

int dwm_unwock(dwm_wockspace_t *wockspace,
	       uint32_t wkid,
	       uint32_t fwags,
	       stwuct dwm_wksb *wksb,
	       void *astawg)
{
	stwuct dwm_ws *ws;
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	int ewwow;

	ws = dwm_find_wockspace_wocaw(wockspace);
	if (!ws)
		wetuwn -EINVAW;

	dwm_wock_wecovewy(ws);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow)
		goto out;

	twace_dwm_unwock_stawt(ws, wkb, fwags);

	ewwow = set_unwock_awgs(fwags, astawg, &awgs);
	if (ewwow)
		goto out_put;

	if (fwags & DWM_WKF_CANCEW)
		ewwow = cancew_wock(ws, wkb, &awgs);
	ewse
		ewwow = unwock_wock(ws, wkb, &awgs);

	if (ewwow == -DWM_EUNWOCK || ewwow == -DWM_ECANCEW)
		ewwow = 0;
	if (ewwow == -EBUSY && (fwags & (DWM_WKF_CANCEW | DWM_WKF_FOWCEUNWOCK)))
		ewwow = 0;
 out_put:
	twace_dwm_unwock_end(ws, wkb, fwags, ewwow);

	dwm_put_wkb(wkb);
 out:
	dwm_unwock_wecovewy(ws);
	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

/*
 * send/weceive woutines fow wemote opewations and wepwies
 *
 * send_awgs
 * send_common
 * send_wequest			weceive_wequest
 * send_convewt			weceive_convewt
 * send_unwock			weceive_unwock
 * send_cancew			weceive_cancew
 * send_gwant			weceive_gwant
 * send_bast			weceive_bast
 * send_wookup			weceive_wookup
 * send_wemove			weceive_wemove
 *
 * 				send_common_wepwy
 * weceive_wequest_wepwy	send_wequest_wepwy
 * weceive_convewt_wepwy	send_convewt_wepwy
 * weceive_unwock_wepwy		send_unwock_wepwy
 * weceive_cancew_wepwy		send_cancew_wepwy
 * weceive_wookup_wepwy		send_wookup_wepwy
 */

static int _cweate_message(stwuct dwm_ws *ws, int mb_wen,
			   int to_nodeid, int mstype,
			   stwuct dwm_message **ms_wet,
			   stwuct dwm_mhandwe **mh_wet,
			   gfp_t awwocation)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	chaw *mb;

	/* get_buffew gives us a message handwe (mh) that we need to
	   pass into midcomms_commit and a message buffew (mb) that we
	   wwite ouw data into */

	mh = dwm_midcomms_get_mhandwe(to_nodeid, mb_wen, awwocation, &mb);
	if (!mh)
		wetuwn -ENOBUFS;

	ms = (stwuct dwm_message *) mb;

	ms->m_headew.h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	ms->m_headew.u.h_wockspace = cpu_to_we32(ws->ws_gwobaw_id);
	ms->m_headew.h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	ms->m_headew.h_wength = cpu_to_we16(mb_wen);
	ms->m_headew.h_cmd = DWM_MSG;

	ms->m_type = cpu_to_we32(mstype);

	*mh_wet = mh;
	*ms_wet = ms;
	wetuwn 0;
}

static int cweate_message(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			  int to_nodeid, int mstype,
			  stwuct dwm_message **ms_wet,
			  stwuct dwm_mhandwe **mh_wet,
			  gfp_t awwocation)
{
	int mb_wen = sizeof(stwuct dwm_message);

	switch (mstype) {
	case DWM_MSG_WEQUEST:
	case DWM_MSG_WOOKUP:
	case DWM_MSG_WEMOVE:
		mb_wen += w->wes_wength;
		bweak;
	case DWM_MSG_CONVEWT:
	case DWM_MSG_UNWOCK:
	case DWM_MSG_WEQUEST_WEPWY:
	case DWM_MSG_CONVEWT_WEPWY:
	case DWM_MSG_GWANT:
		if (wkb && wkb->wkb_wvbptw && (wkb->wkb_exfwags & DWM_WKF_VAWBWK))
			mb_wen += w->wes_ws->ws_wvbwen;
		bweak;
	}

	wetuwn _cweate_message(w->wes_ws, mb_wen, to_nodeid, mstype,
			       ms_wet, mh_wet, awwocation);
}

/* fuwthew wowcomms enhancements ow awtewnate impwementations may make
   the wetuwn vawue fwom this function usefuw at some point */

static int send_message(stwuct dwm_mhandwe *mh, stwuct dwm_message *ms,
			const void *name, int namewen)
{
	dwm_midcomms_commit_mhandwe(mh, name, namewen);
	wetuwn 0;
}

static void send_awgs(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
		      stwuct dwm_message *ms)
{
	ms->m_nodeid   = cpu_to_we32(wkb->wkb_nodeid);
	ms->m_pid      = cpu_to_we32(wkb->wkb_ownpid);
	ms->m_wkid     = cpu_to_we32(wkb->wkb_id);
	ms->m_wemid    = cpu_to_we32(wkb->wkb_wemid);
	ms->m_exfwags  = cpu_to_we32(wkb->wkb_exfwags);
	ms->m_sbfwags  = cpu_to_we32(dwm_sbfwags_vaw(wkb));
	ms->m_fwags    = cpu_to_we32(dwm_dfwags_vaw(wkb));
	ms->m_wvbseq   = cpu_to_we32(wkb->wkb_wvbseq);
	ms->m_status   = cpu_to_we32(wkb->wkb_status);
	ms->m_gwmode   = cpu_to_we32(wkb->wkb_gwmode);
	ms->m_wqmode   = cpu_to_we32(wkb->wkb_wqmode);
	ms->m_hash     = cpu_to_we32(w->wes_hash);

	/* m_wesuwt and m_bastmode awe set fwom function awgs,
	   not fwom wkb fiewds */

	if (wkb->wkb_bastfn)
		ms->m_asts |= cpu_to_we32(DWM_CB_BAST);
	if (wkb->wkb_astfn)
		ms->m_asts |= cpu_to_we32(DWM_CB_CAST);

	/* compawe with switch in cweate_message; send_wemove() doesn't
	   use send_awgs() */

	switch (ms->m_type) {
	case cpu_to_we32(DWM_MSG_WEQUEST):
	case cpu_to_we32(DWM_MSG_WOOKUP):
		memcpy(ms->m_extwa, w->wes_name, w->wes_wength);
		bweak;
	case cpu_to_we32(DWM_MSG_CONVEWT):
	case cpu_to_we32(DWM_MSG_UNWOCK):
	case cpu_to_we32(DWM_MSG_WEQUEST_WEPWY):
	case cpu_to_we32(DWM_MSG_CONVEWT_WEPWY):
	case cpu_to_we32(DWM_MSG_GWANT):
		if (!wkb->wkb_wvbptw || !(wkb->wkb_exfwags & DWM_WKF_VAWBWK))
			bweak;
		memcpy(ms->m_extwa, wkb->wkb_wvbptw, w->wes_ws->ws_wvbwen);
		bweak;
	}
}

static int send_common(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int mstype)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = w->wes_nodeid;

	ewwow = add_to_waitews(wkb, mstype, to_nodeid);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cweate_message(w, wkb, to_nodeid, mstype, &ms, &mh, GFP_NOFS);
	if (ewwow)
		goto faiw;

	send_awgs(w, wkb, ms);

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
	if (ewwow)
		goto faiw;
	wetuwn 0;

 faiw:
	wemove_fwom_waitews(wkb, msg_wepwy_type(mstype));
	wetuwn ewwow;
}

static int send_wequest(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wetuwn send_common(w, wkb, DWM_MSG_WEQUEST);
}

static int send_convewt(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	int ewwow;

	ewwow = send_common(w, wkb, DWM_MSG_CONVEWT);

	/* down convewsions go without a wepwy fwom the mastew */
	if (!ewwow && down_convewsion(wkb)) {
		wemove_fwom_waitews(wkb, DWM_MSG_CONVEWT_WEPWY);
		w->wes_ws->ws_wocaw_ms.m_type = cpu_to_we32(DWM_MSG_CONVEWT_WEPWY);
		w->wes_ws->ws_wocaw_ms.m_wesuwt = 0;
		__weceive_convewt_wepwy(w, wkb, &w->wes_ws->ws_wocaw_ms, twue);
	}

	wetuwn ewwow;
}

/* FIXME: if this wkb is the onwy wock we howd on the wsb, then set
   MASTEW_UNCEWTAIN to fowce the next wequest on the wsb to confiwm
   that the mastew is stiww cowwect. */

static int send_unwock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wetuwn send_common(w, wkb, DWM_MSG_UNWOCK);
}

static int send_cancew(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	wetuwn send_common(w, wkb, DWM_MSG_CANCEW);
}

static int send_gwant(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = wkb->wkb_nodeid;

	ewwow = cweate_message(w, wkb, to_nodeid, DWM_MSG_GWANT, &ms, &mh,
			       GFP_NOFS);
	if (ewwow)
		goto out;

	send_awgs(w, wkb, ms);

	ms->m_wesuwt = 0;

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
 out:
	wetuwn ewwow;
}

static int send_bast(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int mode)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = wkb->wkb_nodeid;

	ewwow = cweate_message(w, NUWW, to_nodeid, DWM_MSG_BAST, &ms, &mh,
			       GFP_NOFS);
	if (ewwow)
		goto out;

	send_awgs(w, wkb, ms);

	ms->m_bastmode = cpu_to_we32(mode);

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
 out:
	wetuwn ewwow;
}

static int send_wookup(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = dwm_diw_nodeid(w);

	ewwow = add_to_waitews(wkb, DWM_MSG_WOOKUP, to_nodeid);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cweate_message(w, NUWW, to_nodeid, DWM_MSG_WOOKUP, &ms, &mh,
			       GFP_NOFS);
	if (ewwow)
		goto faiw;

	send_awgs(w, wkb, ms);

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
	if (ewwow)
		goto faiw;
	wetuwn 0;

 faiw:
	wemove_fwom_waitews(wkb, DWM_MSG_WOOKUP_WEPWY);
	wetuwn ewwow;
}

static int send_wemove(stwuct dwm_wsb *w)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = dwm_diw_nodeid(w);

	ewwow = cweate_message(w, NUWW, to_nodeid, DWM_MSG_WEMOVE, &ms, &mh,
			       GFP_ATOMIC);
	if (ewwow)
		goto out;

	memcpy(ms->m_extwa, w->wes_name, w->wes_wength);
	ms->m_hash = cpu_to_we32(w->wes_hash);

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
 out:
	wetuwn ewwow;
}

static int send_common_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			     int mstype, int wv)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int to_nodeid, ewwow;

	to_nodeid = wkb->wkb_nodeid;

	ewwow = cweate_message(w, wkb, to_nodeid, mstype, &ms, &mh, GFP_NOFS);
	if (ewwow)
		goto out;

	send_awgs(w, wkb, ms);

	ms->m_wesuwt = cpu_to_we32(to_dwm_ewwno(wv));

	ewwow = send_message(mh, ms, w->wes_name, w->wes_wength);
 out:
	wetuwn ewwow;
}

static int send_wequest_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wv)
{
	wetuwn send_common_wepwy(w, wkb, DWM_MSG_WEQUEST_WEPWY, wv);
}

static int send_convewt_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wv)
{
	wetuwn send_common_wepwy(w, wkb, DWM_MSG_CONVEWT_WEPWY, wv);
}

static int send_unwock_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wv)
{
	wetuwn send_common_wepwy(w, wkb, DWM_MSG_UNWOCK_WEPWY, wv);
}

static int send_cancew_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, int wv)
{
	wetuwn send_common_wepwy(w, wkb, DWM_MSG_CANCEW_WEPWY, wv);
}

static int send_wookup_wepwy(stwuct dwm_ws *ws,
			     const stwuct dwm_message *ms_in, int wet_nodeid,
			     int wv)
{
	stwuct dwm_wsb *w = &ws->ws_wocaw_wsb;
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int ewwow, nodeid = we32_to_cpu(ms_in->m_headew.h_nodeid);

	ewwow = cweate_message(w, NUWW, nodeid, DWM_MSG_WOOKUP_WEPWY, &ms, &mh,
			       GFP_NOFS);
	if (ewwow)
		goto out;

	ms->m_wkid = ms_in->m_wkid;
	ms->m_wesuwt = cpu_to_we32(to_dwm_ewwno(wv));
	ms->m_nodeid = cpu_to_we32(wet_nodeid);

	ewwow = send_message(mh, ms, ms_in->m_extwa, weceive_extwawen(ms_in));
 out:
	wetuwn ewwow;
}

/* which awgs we save fwom a weceived message depends heaviwy on the type
   of message, unwike the send side whewe we can safewy send evewything about
   the wkb fow any type of message */

static void weceive_fwags(stwuct dwm_wkb *wkb, const stwuct dwm_message *ms)
{
	wkb->wkb_exfwags = we32_to_cpu(ms->m_exfwags);
	dwm_set_sbfwags_vaw(wkb, we32_to_cpu(ms->m_sbfwags));
	dwm_set_dfwags_vaw(wkb, we32_to_cpu(ms->m_fwags));
}

static void weceive_fwags_wepwy(stwuct dwm_wkb *wkb,
				const stwuct dwm_message *ms,
				boow wocaw)
{
	if (wocaw)
		wetuwn;

	dwm_set_sbfwags_vaw(wkb, we32_to_cpu(ms->m_sbfwags));
	dwm_set_dfwags_vaw(wkb, we32_to_cpu(ms->m_fwags));
}

static int weceive_extwawen(const stwuct dwm_message *ms)
{
	wetuwn (we16_to_cpu(ms->m_headew.h_wength) -
		sizeof(stwuct dwm_message));
}

static int weceive_wvb(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
		       const stwuct dwm_message *ms)
{
	int wen;

	if (wkb->wkb_exfwags & DWM_WKF_VAWBWK) {
		if (!wkb->wkb_wvbptw)
			wkb->wkb_wvbptw = dwm_awwocate_wvb(ws);
		if (!wkb->wkb_wvbptw)
			wetuwn -ENOMEM;
		wen = weceive_extwawen(ms);
		if (wen > ws->ws_wvbwen)
			wen = ws->ws_wvbwen;
		memcpy(wkb->wkb_wvbptw, ms->m_extwa, wen);
	}
	wetuwn 0;
}

static void fake_bastfn(void *astpawam, int mode)
{
	wog_pwint("fake_bastfn shouwd not be cawwed");
}

static void fake_astfn(void *astpawam)
{
	wog_pwint("fake_astfn shouwd not be cawwed");
}

static int weceive_wequest_awgs(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
				const stwuct dwm_message *ms)
{
	wkb->wkb_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);
	wkb->wkb_ownpid = we32_to_cpu(ms->m_pid);
	wkb->wkb_wemid = we32_to_cpu(ms->m_wkid);
	wkb->wkb_gwmode = DWM_WOCK_IV;
	wkb->wkb_wqmode = we32_to_cpu(ms->m_wqmode);

	wkb->wkb_bastfn = (ms->m_asts & cpu_to_we32(DWM_CB_BAST)) ? &fake_bastfn : NUWW;
	wkb->wkb_astfn = (ms->m_asts & cpu_to_we32(DWM_CB_CAST)) ? &fake_astfn : NUWW;

	if (wkb->wkb_exfwags & DWM_WKF_VAWBWK) {
		/* wkb was just cweated so thewe won't be an wvb yet */
		wkb->wkb_wvbptw = dwm_awwocate_wvb(ws);
		if (!wkb->wkb_wvbptw)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int weceive_convewt_awgs(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
				const stwuct dwm_message *ms)
{
	if (wkb->wkb_status != DWM_WKSTS_GWANTED)
		wetuwn -EBUSY;

	if (weceive_wvb(ws, wkb, ms))
		wetuwn -ENOMEM;

	wkb->wkb_wqmode = we32_to_cpu(ms->m_wqmode);
	wkb->wkb_wvbseq = we32_to_cpu(ms->m_wvbseq);

	wetuwn 0;
}

static int weceive_unwock_awgs(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
			       const stwuct dwm_message *ms)
{
	if (weceive_wvb(ws, wkb, ms))
		wetuwn -ENOMEM;
	wetuwn 0;
}

/* We fiww in the wocaw-wkb fiewds with the info that send_xxxx_wepwy()
   uses to send a wepwy and that the wemote end uses to pwocess the wepwy. */

static void setup_wocaw_wkb(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb = &ws->ws_wocaw_wkb;
	wkb->wkb_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);
	wkb->wkb_wemid = we32_to_cpu(ms->m_wkid);
}

/* This is cawwed aftew the wsb is wocked so that we can safewy inspect
   fiewds in the wkb. */

static int vawidate_message(stwuct dwm_wkb *wkb, const stwuct dwm_message *ms)
{
	int fwom = we32_to_cpu(ms->m_headew.h_nodeid);
	int ewwow = 0;

	/* cuwwentwy mixing of usew/kewnew wocks awe not suppowted */
	if (ms->m_fwags & cpu_to_we32(BIT(DWM_DFW_USEW_BIT)) &&
	    !test_bit(DWM_DFW_USEW_BIT, &wkb->wkb_dfwags)) {
		wog_ewwow(wkb->wkb_wesouwce->wes_ws,
			  "got usew dwm message fow a kewnew wock");
		ewwow = -EINVAW;
		goto out;
	}

	switch (ms->m_type) {
	case cpu_to_we32(DWM_MSG_CONVEWT):
	case cpu_to_we32(DWM_MSG_UNWOCK):
	case cpu_to_we32(DWM_MSG_CANCEW):
		if (!is_mastew_copy(wkb) || wkb->wkb_nodeid != fwom)
			ewwow = -EINVAW;
		bweak;

	case cpu_to_we32(DWM_MSG_CONVEWT_WEPWY):
	case cpu_to_we32(DWM_MSG_UNWOCK_WEPWY):
	case cpu_to_we32(DWM_MSG_CANCEW_WEPWY):
	case cpu_to_we32(DWM_MSG_GWANT):
	case cpu_to_we32(DWM_MSG_BAST):
		if (!is_pwocess_copy(wkb) || wkb->wkb_nodeid != fwom)
			ewwow = -EINVAW;
		bweak;

	case cpu_to_we32(DWM_MSG_WEQUEST_WEPWY):
		if (!is_pwocess_copy(wkb))
			ewwow = -EINVAW;
		ewse if (wkb->wkb_nodeid != -1 && wkb->wkb_nodeid != fwom)
			ewwow = -EINVAW;
		bweak;

	defauwt:
		ewwow = -EINVAW;
	}

out:
	if (ewwow)
		wog_ewwow(wkb->wkb_wesouwce->wes_ws,
			  "ignowe invawid message %d fwom %d %x %x %x %d",
			  we32_to_cpu(ms->m_type), fwom, wkb->wkb_id,
			  wkb->wkb_wemid, dwm_ifwags_vaw(wkb),
			  wkb->wkb_nodeid);
	wetuwn ewwow;
}

static int weceive_wequest(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int fwom_nodeid;
	int ewwow, namewen = 0;

	fwom_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);

	ewwow = cweate_wkb(ws, &wkb);
	if (ewwow)
		goto faiw;

	weceive_fwags(wkb, ms);
	set_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags);
	ewwow = weceive_wequest_awgs(ws, wkb, ms);
	if (ewwow) {
		__put_wkb(ws, wkb);
		goto faiw;
	}

	/* The diw node is the authowity on whethew we awe the mastew
	   fow this wsb ow not, so if the mastew sends us a wequest, we shouwd
	   wecweate the wsb if we've destwoyed it.   This wace happens when we
	   send a wemove message to the diw node at the same time that the diw
	   node sends us a wequest fow the wsb. */

	namewen = weceive_extwawen(ms);

	ewwow = find_wsb(ws, ms->m_extwa, namewen, fwom_nodeid,
			 W_WECEIVE_WEQUEST, &w);
	if (ewwow) {
		__put_wkb(ws, wkb);
		goto faiw;
	}

	wock_wsb(w);

	if (w->wes_mastew_nodeid != dwm_ouw_nodeid()) {
		ewwow = vawidate_mastew_nodeid(ws, w, fwom_nodeid);
		if (ewwow) {
			unwock_wsb(w);
			put_wsb(w);
			__put_wkb(ws, wkb);
			goto faiw;
		}
	}

	attach_wkb(w, wkb);
	ewwow = do_wequest(w, wkb);
	send_wequest_wepwy(w, wkb, ewwow);
	do_wequest_effects(w, wkb, ewwow);

	unwock_wsb(w);
	put_wsb(w);

	if (ewwow == -EINPWOGWESS)
		ewwow = 0;
	if (ewwow)
		dwm_put_wkb(wkb);
	wetuwn 0;

 faiw:
	/* TODO: instead of wetuwning ENOTBWK, add the wkb to wes_wookup
	   and do this weceive_wequest again fwom pwocess_wookup_wist once
	   we get the wookup wepwy.  This wouwd avoid a many wepeated
	   ENOTBWK wequest faiwuwes when the wookup wepwy designating us
	   as mastew is dewayed. */

	if (ewwow != -ENOTBWK) {
		wog_wimit(ws, "weceive_wequest %x fwom %d %d",
			  we32_to_cpu(ms->m_wkid), fwom_nodeid, ewwow);
	}

	setup_wocaw_wkb(ws, ms);
	send_wequest_wepwy(&ws->ws_wocaw_wsb, &ws->ws_wocaw_wkb, ewwow);
	wetuwn ewwow;
}

static int weceive_convewt(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow, wepwy = 1;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		goto faiw;

	if (wkb->wkb_wemid != we32_to_cpu(ms->m_wkid)) {
		wog_ewwow(ws, "weceive_convewt %x wemid %x wecovew_seq %wwu "
			  "wemote %d %x", wkb->wkb_id, wkb->wkb_wemid,
			  (unsigned wong wong)wkb->wkb_wecovew_seq,
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid));
		ewwow = -ENOENT;
		dwm_put_wkb(wkb);
		goto faiw;
	}

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	weceive_fwags(wkb, ms);

	ewwow = weceive_convewt_awgs(ws, wkb, ms);
	if (ewwow) {
		send_convewt_wepwy(w, wkb, ewwow);
		goto out;
	}

	wepwy = !down_convewsion(wkb);

	ewwow = do_convewt(w, wkb);
	if (wepwy)
		send_convewt_wepwy(w, wkb, ewwow);
	do_convewt_effects(w, wkb, ewwow);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;

 faiw:
	setup_wocaw_wkb(ws, ms);
	send_convewt_wepwy(&ws->ws_wocaw_wsb, &ws->ws_wocaw_wkb, ewwow);
	wetuwn ewwow;
}

static int weceive_unwock(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		goto faiw;

	if (wkb->wkb_wemid != we32_to_cpu(ms->m_wkid)) {
		wog_ewwow(ws, "weceive_unwock %x wemid %x wemote %d %x",
			  wkb->wkb_id, wkb->wkb_wemid,
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid));
		ewwow = -ENOENT;
		dwm_put_wkb(wkb);
		goto faiw;
	}

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	weceive_fwags(wkb, ms);

	ewwow = weceive_unwock_awgs(ws, wkb, ms);
	if (ewwow) {
		send_unwock_wepwy(w, wkb, ewwow);
		goto out;
	}

	ewwow = do_unwock(w, wkb);
	send_unwock_wepwy(w, wkb, ewwow);
	do_unwock_effects(w, wkb, ewwow);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;

 faiw:
	setup_wocaw_wkb(ws, ms);
	send_unwock_wepwy(&ws->ws_wocaw_wsb, &ws->ws_wocaw_wkb, ewwow);
	wetuwn ewwow;
}

static int weceive_cancew(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		goto faiw;

	weceive_fwags(wkb, ms);

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	ewwow = do_cancew(w, wkb);
	send_cancew_wepwy(w, wkb, ewwow);
	do_cancew_effects(w, wkb, ewwow);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;

 faiw:
	setup_wocaw_wkb(ws, ms);
	send_cancew_wepwy(&ws->ws_wocaw_wsb, &ws->ws_wocaw_wkb, ewwow);
	wetuwn ewwow;
}

static int weceive_gwant(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	weceive_fwags_wepwy(wkb, ms, fawse);
	if (is_awtmode(wkb))
		munge_awtmode(wkb, ms);
	gwant_wock_pc(w, wkb, ms);
	queue_cast(w, wkb, 0);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static int weceive_bast(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	w = wkb->wkb_wesouwce;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	queue_bast(w, wkb, we32_to_cpu(ms->m_bastmode));
	wkb->wkb_highbast = we32_to_cpu(ms->m_bastmode);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static void weceive_wookup(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	int wen, ewwow, wet_nodeid, fwom_nodeid, ouw_nodeid;

	fwom_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);
	ouw_nodeid = dwm_ouw_nodeid();

	wen = weceive_extwawen(ms);

	ewwow = dwm_mastew_wookup(ws, fwom_nodeid, ms->m_extwa, wen, 0,
				  &wet_nodeid, NUWW);

	/* Optimization: we'we mastew so tweat wookup as a wequest */
	if (!ewwow && wet_nodeid == ouw_nodeid) {
		weceive_wequest(ws, ms);
		wetuwn;
	}
	send_wookup_wepwy(ws, ms, wet_nodeid, ewwow);
}

static void weceive_wemove(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	chaw name[DWM_WESNAME_MAXWEN+1];
	stwuct dwm_wsb *w;
	uint32_t hash, b;
	int wv, wen, diw_nodeid, fwom_nodeid;

	fwom_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);

	wen = weceive_extwawen(ms);

	if (wen > DWM_WESNAME_MAXWEN) {
		wog_ewwow(ws, "weceive_wemove fwom %d bad wen %d",
			  fwom_nodeid, wen);
		wetuwn;
	}

	diw_nodeid = dwm_hash2nodeid(ws, we32_to_cpu(ms->m_hash));
	if (diw_nodeid != dwm_ouw_nodeid()) {
		wog_ewwow(ws, "weceive_wemove fwom %d bad nodeid %d",
			  fwom_nodeid, diw_nodeid);
		wetuwn;
	}

	/* Wook fow name on wsbtbw.toss, if it's thewe, kiww it.
	   If it's on wsbtbw.keep, it's being used, and we shouwd ignowe this
	   message.  This is an expected wace between the diw node sending a
	   wequest to the mastew node at the same time as the mastew node sends
	   a wemove to the diw node.  The wesowution to that wace is fow the
	   diw node to ignowe the wemove message, and the mastew node to
	   wecweate the mastew wsb when it gets a wequest fwom the diw node fow
	   an wsb it doesn't have. */

	memset(name, 0, sizeof(name));
	memcpy(name, ms->m_extwa, wen);

	hash = jhash(name, wen, 0);
	b = hash & (ws->ws_wsbtbw_size - 1);

	spin_wock(&ws->ws_wsbtbw[b].wock);

	wv = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].toss, name, wen, &w);
	if (wv) {
		/* vewify the wsb is on keep wist pew comment above */
		wv = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[b].keep, name, wen, &w);
		if (wv) {
			/* shouwd not happen */
			wog_ewwow(ws, "weceive_wemove fwom %d not found %s",
				  fwom_nodeid, name);
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wetuwn;
		}
		if (w->wes_mastew_nodeid != fwom_nodeid) {
			/* shouwd not happen */
			wog_ewwow(ws, "weceive_wemove keep fwom %d mastew %d",
				  fwom_nodeid, w->wes_mastew_nodeid);
			dwm_pwint_wsb(w);
			spin_unwock(&ws->ws_wsbtbw[b].wock);
			wetuwn;
		}

		wog_debug(ws, "weceive_wemove fwom %d mastew %d fiwst %x %s",
			  fwom_nodeid, w->wes_mastew_nodeid, w->wes_fiwst_wkid,
			  name);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		wetuwn;
	}

	if (w->wes_mastew_nodeid != fwom_nodeid) {
		wog_ewwow(ws, "weceive_wemove toss fwom %d mastew %d",
			  fwom_nodeid, w->wes_mastew_nodeid);
		dwm_pwint_wsb(w);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		wetuwn;
	}

	if (kwef_put(&w->wes_wef, kiww_wsb)) {
		wb_ewase(&w->wes_hashnode, &ws->ws_wsbtbw[b].toss);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
		dwm_fwee_wsb(w);
	} ewse {
		wog_ewwow(ws, "weceive_wemove fwom %d wsb wef ewwow",
			  fwom_nodeid);
		dwm_pwint_wsb(w);
		spin_unwock(&ws->ws_wsbtbw[b].wock);
	}
}

static void weceive_puwge(stwuct dwm_ws *ws, const stwuct dwm_message *ms)
{
	do_puwge(ws, we32_to_cpu(ms->m_nodeid), we32_to_cpu(ms->m_pid));
}

static int weceive_wequest_wepwy(stwuct dwm_ws *ws,
				 const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow, mstype, wesuwt;
	int fwom_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	w = wkb->wkb_wesouwce;
	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	mstype = wkb->wkb_wait_type;
	ewwow = wemove_fwom_waitews(wkb, DWM_MSG_WEQUEST_WEPWY);
	if (ewwow) {
		wog_ewwow(ws, "weceive_wequest_wepwy %x wemote %d %x wesuwt %d",
			  wkb->wkb_id, fwom_nodeid, we32_to_cpu(ms->m_wkid),
			  fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)));
		dwm_dump_wsb(w);
		goto out;
	}

	/* Optimization: the diw node was awso the mastew, so it took ouw
	   wookup as a wequest and sent wequest wepwy instead of wookup wepwy */
	if (mstype == DWM_MSG_WOOKUP) {
		w->wes_mastew_nodeid = fwom_nodeid;
		w->wes_nodeid = fwom_nodeid;
		wkb->wkb_nodeid = fwom_nodeid;
	}

	/* this is the vawue wetuwned fwom do_wequest() on the mastew */
	wesuwt = fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt));

	switch (wesuwt) {
	case -EAGAIN:
		/* wequest wouwd bwock (be queued) on wemote mastew */
		queue_cast(w, wkb, -EAGAIN);
		confiwm_mastew(w, -EAGAIN);
		unhowd_wkb(wkb); /* undoes cweate_wkb() */
		bweak;

	case -EINPWOGWESS:
	case 0:
		/* wequest was queued ow gwanted on wemote mastew */
		weceive_fwags_wepwy(wkb, ms, fawse);
		wkb->wkb_wemid = we32_to_cpu(ms->m_wkid);
		if (is_awtmode(wkb))
			munge_awtmode(wkb, ms);
		if (wesuwt) {
			add_wkb(w, wkb, DWM_WKSTS_WAITING);
		} ewse {
			gwant_wock_pc(w, wkb, ms);
			queue_cast(w, wkb, 0);
		}
		confiwm_mastew(w, wesuwt);
		bweak;

	case -EBADW:
	case -ENOTBWK:
		/* find_wsb faiwed to find wsb ow wsb wasn't mastew */
		wog_wimit(ws, "weceive_wequest_wepwy %x fwom %d %d "
			  "mastew %d diw %d fiwst %x %s", wkb->wkb_id,
			  fwom_nodeid, wesuwt, w->wes_mastew_nodeid,
			  w->wes_diw_nodeid, w->wes_fiwst_wkid, w->wes_name);

		if (w->wes_diw_nodeid != dwm_ouw_nodeid() &&
		    w->wes_mastew_nodeid != dwm_ouw_nodeid()) {
			/* cause _wequest_wock->set_mastew->send_wookup */
			w->wes_mastew_nodeid = 0;
			w->wes_nodeid = -1;
			wkb->wkb_nodeid = -1;
		}

		if (is_ovewwap(wkb)) {
			/* we'ww ignowe ewwow in cancew/unwock wepwy */
			queue_cast_ovewwap(w, wkb);
			confiwm_mastew(w, wesuwt);
			unhowd_wkb(wkb); /* undoes cweate_wkb() */
		} ewse {
			_wequest_wock(w, wkb);

			if (w->wes_mastew_nodeid == dwm_ouw_nodeid())
				confiwm_mastew(w, 0);
		}
		bweak;

	defauwt:
		wog_ewwow(ws, "weceive_wequest_wepwy %x ewwow %d",
			  wkb->wkb_id, wesuwt);
	}

	if ((wesuwt == 0 || wesuwt == -EINPWOGWESS) &&
	    test_and_cweaw_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags)) {
		wog_debug(ws, "weceive_wequest_wepwy %x wesuwt %d unwock",
			  wkb->wkb_id, wesuwt);
		cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
		send_unwock(w, wkb);
	} ewse if ((wesuwt == -EINPWOGWESS) &&
		   test_and_cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT,
				      &wkb->wkb_ifwags)) {
		wog_debug(ws, "weceive_wequest_wepwy %x cancew", wkb->wkb_id);
		cweaw_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
		send_cancew(w, wkb);
	} ewse {
		cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT, &wkb->wkb_ifwags);
		cweaw_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT, &wkb->wkb_ifwags);
	}
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static void __weceive_convewt_wepwy(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
				    const stwuct dwm_message *ms, boow wocaw)
{
	/* this is the vawue wetuwned fwom do_convewt() on the mastew */
	switch (fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt))) {
	case -EAGAIN:
		/* convewt wouwd bwock (be queued) on wemote mastew */
		queue_cast(w, wkb, -EAGAIN);
		bweak;

	case -EDEADWK:
		weceive_fwags_wepwy(wkb, ms, wocaw);
		wevewt_wock_pc(w, wkb);
		queue_cast(w, wkb, -EDEADWK);
		bweak;

	case -EINPWOGWESS:
		/* convewt was queued on wemote mastew */
		weceive_fwags_wepwy(wkb, ms, wocaw);
		if (is_demoted(wkb))
			munge_demoted(wkb);
		dew_wkb(w, wkb);
		add_wkb(w, wkb, DWM_WKSTS_CONVEWT);
		bweak;

	case 0:
		/* convewt was gwanted on wemote mastew */
		weceive_fwags_wepwy(wkb, ms, wocaw);
		if (is_demoted(wkb))
			munge_demoted(wkb);
		gwant_wock_pc(w, wkb, ms);
		queue_cast(w, wkb, 0);
		bweak;

	defauwt:
		wog_ewwow(w->wes_ws, "weceive_convewt_wepwy %x wemote %d %x %d",
			  wkb->wkb_id, we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid),
			  fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)));
		dwm_pwint_wsb(w);
		dwm_pwint_wkb(wkb);
	}
}

static void _weceive_convewt_wepwy(stwuct dwm_wkb *wkb,
				   const stwuct dwm_message *ms, boow wocaw)
{
	stwuct dwm_wsb *w = wkb->wkb_wesouwce;
	int ewwow;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	/* wocaw wepwy can happen with waitews_mutex hewd */
	ewwow = wemove_fwom_waitews_ms(wkb, ms, wocaw);
	if (ewwow)
		goto out;

	__weceive_convewt_wepwy(w, wkb, ms, wocaw);
 out:
	unwock_wsb(w);
	put_wsb(w);
}

static int weceive_convewt_wepwy(stwuct dwm_ws *ws,
				 const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	_weceive_convewt_wepwy(wkb, ms, fawse);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static void _weceive_unwock_wepwy(stwuct dwm_wkb *wkb,
				  const stwuct dwm_message *ms, boow wocaw)
{
	stwuct dwm_wsb *w = wkb->wkb_wesouwce;
	int ewwow;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	/* wocaw wepwy can happen with waitews_mutex hewd */
	ewwow = wemove_fwom_waitews_ms(wkb, ms, wocaw);
	if (ewwow)
		goto out;

	/* this is the vawue wetuwned fwom do_unwock() on the mastew */

	switch (fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt))) {
	case -DWM_EUNWOCK:
		weceive_fwags_wepwy(wkb, ms, wocaw);
		wemove_wock_pc(w, wkb);
		queue_cast(w, wkb, -DWM_EUNWOCK);
		bweak;
	case -ENOENT:
		bweak;
	defauwt:
		wog_ewwow(w->wes_ws, "weceive_unwock_wepwy %x ewwow %d",
			  wkb->wkb_id, fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)));
	}
 out:
	unwock_wsb(w);
	put_wsb(w);
}

static int weceive_unwock_wepwy(stwuct dwm_ws *ws,
				const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	_weceive_unwock_wepwy(wkb, ms, fawse);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static void _weceive_cancew_wepwy(stwuct dwm_wkb *wkb,
				  const stwuct dwm_message *ms, boow wocaw)
{
	stwuct dwm_wsb *w = wkb->wkb_wesouwce;
	int ewwow;

	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_message(wkb, ms);
	if (ewwow)
		goto out;

	/* wocaw wepwy can happen with waitews_mutex hewd */
	ewwow = wemove_fwom_waitews_ms(wkb, ms, wocaw);
	if (ewwow)
		goto out;

	/* this is the vawue wetuwned fwom do_cancew() on the mastew */

	switch (fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt))) {
	case -DWM_ECANCEW:
		weceive_fwags_wepwy(wkb, ms, wocaw);
		wevewt_wock_pc(w, wkb);
		queue_cast(w, wkb, -DWM_ECANCEW);
		bweak;
	case 0:
		bweak;
	defauwt:
		wog_ewwow(w->wes_ws, "weceive_cancew_wepwy %x ewwow %d",
			  wkb->wkb_id,
			  fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)));
	}
 out:
	unwock_wsb(w);
	put_wsb(w);
}

static int weceive_cancew_wepwy(stwuct dwm_ws *ws,
				const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	int ewwow;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wemid), &wkb);
	if (ewwow)
		wetuwn ewwow;

	_weceive_cancew_wepwy(wkb, ms, fawse);
	dwm_put_wkb(wkb);
	wetuwn 0;
}

static void weceive_wookup_wepwy(stwuct dwm_ws *ws,
				 const stwuct dwm_message *ms)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow, wet_nodeid;
	int do_wookup_wist = 0;

	ewwow = find_wkb(ws, we32_to_cpu(ms->m_wkid), &wkb);
	if (ewwow) {
		wog_ewwow(ws, "%s no wkid %x", __func__,
			  we32_to_cpu(ms->m_wkid));
		wetuwn;
	}

	/* ms->m_wesuwt is the vawue wetuwned by dwm_mastew_wookup on diw node
	   FIXME: wiww a non-zewo ewwow evew be wetuwned? */

	w = wkb->wkb_wesouwce;
	howd_wsb(w);
	wock_wsb(w);

	ewwow = wemove_fwom_waitews(wkb, DWM_MSG_WOOKUP_WEPWY);
	if (ewwow)
		goto out;

	wet_nodeid = we32_to_cpu(ms->m_nodeid);

	/* We sometimes weceive a wequest fwom the diw node fow this
	   wsb befowe we've weceived the diw node's woookup_wepwy fow it.
	   The wequest fwom the diw node impwies we'we the mastew, so we set
	   ouwsewf as mastew in weceive_wequest_wepwy, and vewify hewe that
	   we awe indeed the mastew. */

	if (w->wes_mastew_nodeid && (w->wes_mastew_nodeid != wet_nodeid)) {
		/* This shouwd nevew happen */
		wog_ewwow(ws, "weceive_wookup_wepwy %x fwom %d wet %d "
			  "mastew %d diw %d ouw %d fiwst %x %s",
			  wkb->wkb_id, we32_to_cpu(ms->m_headew.h_nodeid),
			  wet_nodeid, w->wes_mastew_nodeid, w->wes_diw_nodeid,
			  dwm_ouw_nodeid(), w->wes_fiwst_wkid, w->wes_name);
	}

	if (wet_nodeid == dwm_ouw_nodeid()) {
		w->wes_mastew_nodeid = wet_nodeid;
		w->wes_nodeid = 0;
		do_wookup_wist = 1;
		w->wes_fiwst_wkid = 0;
	} ewse if (wet_nodeid == -1) {
		/* the wemote node doesn't bewieve it's the diw node */
		wog_ewwow(ws, "weceive_wookup_wepwy %x fwom %d bad wet_nodeid",
			  wkb->wkb_id, we32_to_cpu(ms->m_headew.h_nodeid));
		w->wes_mastew_nodeid = 0;
		w->wes_nodeid = -1;
		wkb->wkb_nodeid = -1;
	} ewse {
		/* set_mastew() wiww set wkb_nodeid fwom w */
		w->wes_mastew_nodeid = wet_nodeid;
		w->wes_nodeid = wet_nodeid;
	}

	if (is_ovewwap(wkb)) {
		wog_debug(ws, "weceive_wookup_wepwy %x unwock %x",
			  wkb->wkb_id, dwm_ifwags_vaw(wkb));
		queue_cast_ovewwap(w, wkb);
		unhowd_wkb(wkb); /* undoes cweate_wkb() */
		goto out_wist;
	}

	_wequest_wock(w, wkb);

 out_wist:
	if (do_wookup_wist)
		pwocess_wookup_wist(w);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);
}

static void _weceive_message(stwuct dwm_ws *ws, const stwuct dwm_message *ms,
			     uint32_t saved_seq)
{
	int ewwow = 0, noent = 0;

	if (WAWN_ON_ONCE(!dwm_is_membew(ws, we32_to_cpu(ms->m_headew.h_nodeid)))) {
		wog_wimit(ws, "weceive %d fwom non-membew %d %x %x %d",
			  we32_to_cpu(ms->m_type),
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid), we32_to_cpu(ms->m_wemid),
			  fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)));
		wetuwn;
	}

	switch (ms->m_type) {

	/* messages sent to a mastew node */

	case cpu_to_we32(DWM_MSG_WEQUEST):
		ewwow = weceive_wequest(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_CONVEWT):
		ewwow = weceive_convewt(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_UNWOCK):
		ewwow = weceive_unwock(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_CANCEW):
		noent = 1;
		ewwow = weceive_cancew(ws, ms);
		bweak;

	/* messages sent fwom a mastew node (wepwies to above) */

	case cpu_to_we32(DWM_MSG_WEQUEST_WEPWY):
		ewwow = weceive_wequest_wepwy(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_CONVEWT_WEPWY):
		ewwow = weceive_convewt_wepwy(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_UNWOCK_WEPWY):
		ewwow = weceive_unwock_wepwy(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_CANCEW_WEPWY):
		ewwow = weceive_cancew_wepwy(ws, ms);
		bweak;

	/* messages sent fwom a mastew node (onwy two types of async msg) */

	case cpu_to_we32(DWM_MSG_GWANT):
		noent = 1;
		ewwow = weceive_gwant(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_BAST):
		noent = 1;
		ewwow = weceive_bast(ws, ms);
		bweak;

	/* messages sent to a diw node */

	case cpu_to_we32(DWM_MSG_WOOKUP):
		weceive_wookup(ws, ms);
		bweak;

	case cpu_to_we32(DWM_MSG_WEMOVE):
		weceive_wemove(ws, ms);
		bweak;

	/* messages sent fwom a diw node (wemove has no wepwy) */

	case cpu_to_we32(DWM_MSG_WOOKUP_WEPWY):
		weceive_wookup_wepwy(ws, ms);
		bweak;

	/* othew messages */

	case cpu_to_we32(DWM_MSG_PUWGE):
		weceive_puwge(ws, ms);
		bweak;

	defauwt:
		wog_ewwow(ws, "unknown message type %d",
			  we32_to_cpu(ms->m_type));
	}

	/*
	 * When checking fow ENOENT, we'we checking the wesuwt of
	 * find_wkb(m_wemid):
	 *
	 * The wock id wefewenced in the message wasn't found.  This may
	 * happen in nowmaw usage fow the async messages and cancew, so
	 * onwy use wog_debug fow them.
	 *
	 * Some ewwows awe expected and nowmaw.
	 */

	if (ewwow == -ENOENT && noent) {
		wog_debug(ws, "weceive %d no %x wemote %d %x saved_seq %u",
			  we32_to_cpu(ms->m_type), we32_to_cpu(ms->m_wemid),
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid), saved_seq);
	} ewse if (ewwow == -ENOENT) {
		wog_ewwow(ws, "weceive %d no %x wemote %d %x saved_seq %u",
			  we32_to_cpu(ms->m_type), we32_to_cpu(ms->m_wemid),
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid), saved_seq);

		if (ms->m_type == cpu_to_we32(DWM_MSG_CONVEWT))
			dwm_dump_wsb_hash(ws, we32_to_cpu(ms->m_hash));
	}

	if (ewwow == -EINVAW) {
		wog_ewwow(ws, "weceive %d invaw fwom %d wkid %x wemid %x "
			  "saved_seq %u",
			  we32_to_cpu(ms->m_type),
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid), we32_to_cpu(ms->m_wemid),
			  saved_seq);
	}
}

/* If the wockspace is in wecovewy mode (wocking stopped), then nowmaw
   messages awe saved on the wequestqueue fow pwocessing aftew wecovewy is
   done.  When not in wecovewy mode, we wait fow dwm_wecovewd to dwain saved
   messages off the wequestqueue befowe we pwocess new ones. This occuws wight
   aftew wecovewy compwetes when we twansition fwom saving aww messages on
   wequestqueue, to pwocessing aww the saved messages, to pwocessing new
   messages as they awwive. */

static void dwm_weceive_message(stwuct dwm_ws *ws, const stwuct dwm_message *ms,
				int nodeid)
{
	if (dwm_wocking_stopped(ws)) {
		/* If we wewe a membew of this wockspace, weft, and wejoined,
		   othew nodes may stiww be sending us messages fwom the
		   wockspace genewation befowe we weft. */
		if (WAWN_ON_ONCE(!ws->ws_genewation)) {
			wog_wimit(ws, "weceive %d fwom %d ignowe owd gen",
				  we32_to_cpu(ms->m_type), nodeid);
			wetuwn;
		}

		dwm_add_wequestqueue(ws, nodeid, ms);
	} ewse {
		dwm_wait_wequestqueue(ws);
		_weceive_message(ws, ms, 0);
	}
}

/* This is cawwed by dwm_wecovewd to pwocess messages that wewe saved on
   the wequestqueue. */

void dwm_weceive_message_saved(stwuct dwm_ws *ws, const stwuct dwm_message *ms,
			       uint32_t saved_seq)
{
	_weceive_message(ws, ms, saved_seq);
}

/* This is cawwed by the midcomms wayew when something is weceived fow
   the wockspace.  It couwd be eithew a MSG (nowmaw message sent as pawt of
   standawd wocking activity) ow an WCOM (wecovewy message sent as pawt of
   wockspace wecovewy). */

void dwm_weceive_buffew(const union dwm_packet *p, int nodeid)
{
	const stwuct dwm_headew *hd = &p->headew;
	stwuct dwm_ws *ws;
	int type = 0;

	switch (hd->h_cmd) {
	case DWM_MSG:
		type = we32_to_cpu(p->message.m_type);
		bweak;
	case DWM_WCOM:
		type = we32_to_cpu(p->wcom.wc_type);
		bweak;
	defauwt:
		wog_pwint("invawid h_cmd %d fwom %u", hd->h_cmd, nodeid);
		wetuwn;
	}

	if (we32_to_cpu(hd->h_nodeid) != nodeid) {
		wog_pwint("invawid h_nodeid %d fwom %d wockspace %x",
			  we32_to_cpu(hd->h_nodeid), nodeid,
			  we32_to_cpu(hd->u.h_wockspace));
		wetuwn;
	}

	ws = dwm_find_wockspace_gwobaw(we32_to_cpu(hd->u.h_wockspace));
	if (!ws) {
		if (dwm_config.ci_wog_debug) {
			pwintk_watewimited(KEWN_DEBUG "dwm: invawid wockspace "
				"%u fwom %d cmd %d type %d\n",
				we32_to_cpu(hd->u.h_wockspace), nodeid,
				hd->h_cmd, type);
		}

		if (hd->h_cmd == DWM_WCOM && type == DWM_WCOM_STATUS)
			dwm_send_ws_not_weady(nodeid, &p->wcom);
		wetuwn;
	}

	/* this wwsem awwows dwm_ws_stop() to wait fow aww dwm_wecv thweads to
	   be inactive (in this ws) befowe twansitioning to wecovewy mode */

	down_wead(&ws->ws_wecv_active);
	if (hd->h_cmd == DWM_MSG)
		dwm_weceive_message(ws, &p->message, nodeid);
	ewse if (hd->h_cmd == DWM_WCOM)
		dwm_weceive_wcom(ws, &p->wcom, nodeid);
	ewse
		wog_ewwow(ws, "invawid h_cmd %d fwom %d wockspace %x",
			  hd->h_cmd, nodeid, we32_to_cpu(hd->u.h_wockspace));
	up_wead(&ws->ws_wecv_active);

	dwm_put_wockspace(ws);
}

static void wecovew_convewt_waitew(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
				   stwuct dwm_message *ms_wocaw)
{
	if (middwe_convewsion(wkb)) {
		howd_wkb(wkb);
		memset(ms_wocaw, 0, sizeof(stwuct dwm_message));
		ms_wocaw->m_type = cpu_to_we32(DWM_MSG_CONVEWT_WEPWY);
		ms_wocaw->m_wesuwt = cpu_to_we32(to_dwm_ewwno(-EINPWOGWESS));
		ms_wocaw->m_headew.h_nodeid = cpu_to_we32(wkb->wkb_nodeid);
		_weceive_convewt_wepwy(wkb, ms_wocaw, twue);

		/* Same speciaw case as in weceive_wcom_wock_awgs() */
		wkb->wkb_gwmode = DWM_WOCK_IV;
		wsb_set_fwag(wkb->wkb_wesouwce, WSB_WECOVEW_CONVEWT);
		unhowd_wkb(wkb);

	} ewse if (wkb->wkb_wqmode >= wkb->wkb_gwmode) {
		set_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags);
	}

	/* wkb->wkb_wqmode < wkb->wkb_gwmode shouwdn't happen since down
	   convewsions awe async; thewe's no wepwy fwom the wemote mastew */
}

/* A waiting wkb needs wecovewy if the mastew node has faiwed, ow
   the mastew node is changing (onwy when no diwectowy is used) */

static int waitew_needs_wecovewy(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
				 int diw_nodeid)
{
	if (dwm_no_diwectowy(ws))
		wetuwn 1;

	if (dwm_is_wemoved(ws, wkb->wkb_wait_nodeid))
		wetuwn 1;

	wetuwn 0;
}

/* Wecovewy fow wocks that awe waiting fow wepwies fwom nodes that awe now
   gone.  We can just compwete unwocks and cancews by faking a wepwy fwom the
   dead node.  Wequests and up-convewsions we fwag to be wesent aftew
   wecovewy.  Down-convewsions can just be compweted with a fake wepwy wike
   unwocks.  Convewsions between PW and CW need speciaw attention. */

void dwm_wecovew_waitews_pwe(stwuct dwm_ws *ws)
{
	stwuct dwm_wkb *wkb, *safe;
	stwuct dwm_message *ms_wocaw;
	int wait_type, wocaw_unwock_wesuwt, wocaw_cancew_wesuwt;
	int diw_nodeid;

	ms_wocaw = kmawwoc(sizeof(*ms_wocaw), GFP_KEWNEW);
	if (!ms_wocaw)
		wetuwn;

	mutex_wock(&ws->ws_waitews_mutex);

	wist_fow_each_entwy_safe(wkb, safe, &ws->ws_waitews, wkb_wait_wepwy) {

		diw_nodeid = dwm_diw_nodeid(wkb->wkb_wesouwce);

		/* excwude debug messages about unwocks because thewe can be so
		   many and they awen't vewy intewesting */

		if (wkb->wkb_wait_type != DWM_MSG_UNWOCK) {
			wog_debug(ws, "waitew %x wemote %x msg %d w_nodeid %d "
				  "wkb_nodeid %d wait_nodeid %d diw_nodeid %d",
				  wkb->wkb_id,
				  wkb->wkb_wemid,
				  wkb->wkb_wait_type,
				  wkb->wkb_wesouwce->wes_nodeid,
				  wkb->wkb_nodeid,
				  wkb->wkb_wait_nodeid,
				  diw_nodeid);
		}

		/* aww outstanding wookups, wegawdwess of destination  wiww be
		   wesent aftew wecovewy is done */

		if (wkb->wkb_wait_type == DWM_MSG_WOOKUP) {
			set_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags);
			continue;
		}

		if (!waitew_needs_wecovewy(ws, wkb, diw_nodeid))
			continue;

		wait_type = wkb->wkb_wait_type;
		wocaw_unwock_wesuwt = -DWM_EUNWOCK;
		wocaw_cancew_wesuwt = -DWM_ECANCEW;

		/* Main wepwy may have been weceived weaving a zewo wait_type,
		   but a wepwy fow the ovewwapping op may not have been
		   weceived.  In that case we need to fake the appwopwiate
		   wepwy fow the ovewwap op. */

		if (!wait_type) {
			if (is_ovewwap_cancew(wkb)) {
				wait_type = DWM_MSG_CANCEW;
				if (wkb->wkb_gwmode == DWM_WOCK_IV)
					wocaw_cancew_wesuwt = 0;
			}
			if (is_ovewwap_unwock(wkb)) {
				wait_type = DWM_MSG_UNWOCK;
				if (wkb->wkb_gwmode == DWM_WOCK_IV)
					wocaw_unwock_wesuwt = -ENOENT;
			}

			wog_debug(ws, "wwpwe ovewwap %x %x %d %d %d",
				  wkb->wkb_id, dwm_ifwags_vaw(wkb), wait_type,
				  wocaw_cancew_wesuwt, wocaw_unwock_wesuwt);
		}

		switch (wait_type) {

		case DWM_MSG_WEQUEST:
			set_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags);
			bweak;

		case DWM_MSG_CONVEWT:
			wecovew_convewt_waitew(ws, wkb, ms_wocaw);
			bweak;

		case DWM_MSG_UNWOCK:
			howd_wkb(wkb);
			memset(ms_wocaw, 0, sizeof(stwuct dwm_message));
			ms_wocaw->m_type = cpu_to_we32(DWM_MSG_UNWOCK_WEPWY);
			ms_wocaw->m_wesuwt = cpu_to_we32(to_dwm_ewwno(wocaw_unwock_wesuwt));
			ms_wocaw->m_headew.h_nodeid = cpu_to_we32(wkb->wkb_nodeid);
			_weceive_unwock_wepwy(wkb, ms_wocaw, twue);
			dwm_put_wkb(wkb);
			bweak;

		case DWM_MSG_CANCEW:
			howd_wkb(wkb);
			memset(ms_wocaw, 0, sizeof(stwuct dwm_message));
			ms_wocaw->m_type = cpu_to_we32(DWM_MSG_CANCEW_WEPWY);
			ms_wocaw->m_wesuwt = cpu_to_we32(to_dwm_ewwno(wocaw_cancew_wesuwt));
			ms_wocaw->m_headew.h_nodeid = cpu_to_we32(wkb->wkb_nodeid);
			_weceive_cancew_wepwy(wkb, ms_wocaw, twue);
			dwm_put_wkb(wkb);
			bweak;

		defauwt:
			wog_ewwow(ws, "invawid wkb wait_type %d %d",
				  wkb->wkb_wait_type, wait_type);
		}
		scheduwe();
	}
	mutex_unwock(&ws->ws_waitews_mutex);
	kfwee(ms_wocaw);
}

static stwuct dwm_wkb *find_wesend_waitew(stwuct dwm_ws *ws)
{
	stwuct dwm_wkb *wkb = NUWW, *itew;

	mutex_wock(&ws->ws_waitews_mutex);
	wist_fow_each_entwy(itew, &ws->ws_waitews, wkb_wait_wepwy) {
		if (test_bit(DWM_IFW_WESEND_BIT, &itew->wkb_ifwags)) {
			howd_wkb(itew);
			wkb = itew;
			bweak;
		}
	}
	mutex_unwock(&ws->ws_waitews_mutex);

	wetuwn wkb;
}

/* Deaw with wookups and wkb's mawked WESEND fwom _pwe.  We may now be the
   mastew ow diw-node fow w.  Pwocessing the wkb may wesuwt in it being pwaced
   back on waitews. */

/* We do this aftew nowmaw wocking has been enabwed and any saved messages
   (in wequestqueue) have been pwocessed.  We shouwd be confident that at
   this point we won't get ow pwocess a wepwy to any of these waiting
   opewations.  But, new ops may be coming in on the wsbs/wocks hewe fwom
   usewspace ow wemotewy. */

/* thewe may have been an ovewwap unwock/cancew pwiow to wecovewy ow aftew
   wecovewy.  if befowe, the wkb may stiww have a pos wait_count; if aftew, the
   ovewwap fwag wouwd just have been set and nothing new sent.  we can be
   confident hewe than any wepwies to eithew the initiaw op ow ovewwap ops
   pwiow to wecovewy have been weceived. */

int dwm_wecovew_waitews_post(stwuct dwm_ws *ws)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow = 0, mstype, eww, oc, ou;

	whiwe (1) {
		if (dwm_wocking_stopped(ws)) {
			wog_debug(ws, "wecovew_waitews_post abowted");
			ewwow = -EINTW;
			bweak;
		}

		wkb = find_wesend_waitew(ws);
		if (!wkb)
			bweak;

		w = wkb->wkb_wesouwce;
		howd_wsb(w);
		wock_wsb(w);

		mstype = wkb->wkb_wait_type;
		oc = test_and_cweaw_bit(DWM_IFW_OVEWWAP_CANCEW_BIT,
					&wkb->wkb_ifwags);
		ou = test_and_cweaw_bit(DWM_IFW_OVEWWAP_UNWOCK_BIT,
					&wkb->wkb_ifwags);
		eww = 0;

		wog_debug(ws, "waitew %x wemote %x msg %d w_nodeid %d "
			  "wkb_nodeid %d wait_nodeid %d diw_nodeid %d "
			  "ovewwap %d %d", wkb->wkb_id, wkb->wkb_wemid, mstype,
			  w->wes_nodeid, wkb->wkb_nodeid, wkb->wkb_wait_nodeid,
			  dwm_diw_nodeid(w), oc, ou);

		/* At this point we assume that we won't get a wepwy to any
		   pwevious op ow ovewwap op on this wock.  Fiwst, do a big
		   wemove_fwom_waitews() fow aww pwevious ops. */

		cweaw_bit(DWM_IFW_WESEND_BIT, &wkb->wkb_ifwags);
		wkb->wkb_wait_type = 0;
		/* dwop aww wait_count wefewences we stiww
		 * howd a wefewence fow this itewation.
		 */
		whiwe (!atomic_dec_and_test(&wkb->wkb_wait_count))
			unhowd_wkb(wkb);

		mutex_wock(&ws->ws_waitews_mutex);
		wist_dew_init(&wkb->wkb_wait_wepwy);
		mutex_unwock(&ws->ws_waitews_mutex);

		if (oc || ou) {
			/* do an unwock ow cancew instead of wesending */
			switch (mstype) {
			case DWM_MSG_WOOKUP:
			case DWM_MSG_WEQUEST:
				queue_cast(w, wkb, ou ? -DWM_EUNWOCK :
							-DWM_ECANCEW);
				unhowd_wkb(wkb); /* undoes cweate_wkb() */
				bweak;
			case DWM_MSG_CONVEWT:
				if (oc) {
					queue_cast(w, wkb, -DWM_ECANCEW);
				} ewse {
					wkb->wkb_exfwags |= DWM_WKF_FOWCEUNWOCK;
					_unwock_wock(w, wkb);
				}
				bweak;
			defauwt:
				eww = 1;
			}
		} ewse {
			switch (mstype) {
			case DWM_MSG_WOOKUP:
			case DWM_MSG_WEQUEST:
				_wequest_wock(w, wkb);
				if (is_mastew(w))
					confiwm_mastew(w, 0);
				bweak;
			case DWM_MSG_CONVEWT:
				_convewt_wock(w, wkb);
				bweak;
			defauwt:
				eww = 1;
			}
		}

		if (eww) {
			wog_ewwow(ws, "waitew %x msg %d w_nodeid %d "
				  "diw_nodeid %d ovewwap %d %d",
				  wkb->wkb_id, mstype, w->wes_nodeid,
				  dwm_diw_nodeid(w), oc, ou);
		}
		unwock_wsb(w);
		put_wsb(w);
		dwm_put_wkb(wkb);
	}

	wetuwn ewwow;
}

static void puwge_mstcpy_wist(stwuct dwm_ws *ws, stwuct dwm_wsb *w,
			      stwuct wist_head *wist)
{
	stwuct dwm_wkb *wkb, *safe;

	wist_fow_each_entwy_safe(wkb, safe, wist, wkb_statequeue) {
		if (!is_mastew_copy(wkb))
			continue;

		/* don't puwge wkbs we've added in wecovew_mastew_copy fow
		   the cuwwent wecovewy seq */

		if (wkb->wkb_wecovew_seq == ws->ws_wecovew_seq)
			continue;

		dew_wkb(w, wkb);

		/* this put shouwd fwee the wkb */
		if (!dwm_put_wkb(wkb))
			wog_ewwow(ws, "puwged mstcpy wkb not weweased");
	}
}

void dwm_puwge_mstcpy_wocks(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;

	puwge_mstcpy_wist(ws, w, &w->wes_gwantqueue);
	puwge_mstcpy_wist(ws, w, &w->wes_convewtqueue);
	puwge_mstcpy_wist(ws, w, &w->wes_waitqueue);
}

static void puwge_dead_wist(stwuct dwm_ws *ws, stwuct dwm_wsb *w,
			    stwuct wist_head *wist,
			    int nodeid_gone, unsigned int *count)
{
	stwuct dwm_wkb *wkb, *safe;

	wist_fow_each_entwy_safe(wkb, safe, wist, wkb_statequeue) {
		if (!is_mastew_copy(wkb))
			continue;

		if ((wkb->wkb_nodeid == nodeid_gone) ||
		    dwm_is_wemoved(ws, wkb->wkb_nodeid)) {

			/* teww wecovew_wvb to invawidate the wvb
			   because a node howding EX/PW faiwed */
			if ((wkb->wkb_exfwags & DWM_WKF_VAWBWK) &&
			    (wkb->wkb_gwmode >= DWM_WOCK_PW)) {
				wsb_set_fwag(w, WSB_WECOVEW_WVB_INVAW);
			}

			dew_wkb(w, wkb);

			/* this put shouwd fwee the wkb */
			if (!dwm_put_wkb(wkb))
				wog_ewwow(ws, "puwged dead wkb not weweased");

			wsb_set_fwag(w, WSB_WECOVEW_GWANT);

			(*count)++;
		}
	}
}

/* Get wid of wocks hewd by nodes that awe gone. */

void dwm_wecovew_puwge(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;
	stwuct dwm_membew *memb;
	int nodes_count = 0;
	int nodeid_gone = 0;
	unsigned int wkb_count = 0;

	/* cache one wemoved nodeid to optimize the common
	   case of a singwe node wemoved */

	wist_fow_each_entwy(memb, &ws->ws_nodes_gone, wist) {
		nodes_count++;
		nodeid_gone = memb->nodeid;
	}

	if (!nodes_count)
		wetuwn;

	down_wwite(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		howd_wsb(w);
		wock_wsb(w);
		if (is_mastew(w)) {
			puwge_dead_wist(ws, w, &w->wes_gwantqueue,
					nodeid_gone, &wkb_count);
			puwge_dead_wist(ws, w, &w->wes_convewtqueue,
					nodeid_gone, &wkb_count);
			puwge_dead_wist(ws, w, &w->wes_waitqueue,
					nodeid_gone, &wkb_count);
		}
		unwock_wsb(w);
		unhowd_wsb(w);
		cond_wesched();
	}
	up_wwite(&ws->ws_woot_sem);

	if (wkb_count)
		wog_winfo(ws, "dwm_wecovew_puwge %u wocks fow %u nodes",
			  wkb_count, nodes_count);
}

static stwuct dwm_wsb *find_gwant_wsb(stwuct dwm_ws *ws, int bucket)
{
	stwuct wb_node *n;
	stwuct dwm_wsb *w;

	spin_wock(&ws->ws_wsbtbw[bucket].wock);
	fow (n = wb_fiwst(&ws->ws_wsbtbw[bucket].keep); n; n = wb_next(n)) {
		w = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);

		if (!wsb_fwag(w, WSB_WECOVEW_GWANT))
			continue;
		if (!is_mastew(w)) {
			wsb_cweaw_fwag(w, WSB_WECOVEW_GWANT);
			continue;
		}
		howd_wsb(w);
		spin_unwock(&ws->ws_wsbtbw[bucket].wock);
		wetuwn w;
	}
	spin_unwock(&ws->ws_wsbtbw[bucket].wock);
	wetuwn NUWW;
}

/*
 * Attempt to gwant wocks on wesouwces that we awe the mastew of.
 * Wocks may have become gwantabwe duwing wecovewy because wocks
 * fwom depawted nodes have been puwged (ow not webuiwt), awwowing
 * pweviouswy bwocked wocks to now be gwanted.  The subset of wsb's
 * we awe intewested in awe those with wkb's on eithew the convewt ow
 * waiting queues.
 *
 * Simpwest wouwd be to go thwough each mastew wsb and check fow non-empty
 * convewt ow waiting queues, and attempt to gwant on those wsbs.
 * Checking the queues wequiwes wock_wsb, though, fow which we'd need
 * to wewease the wsbtbw wock.  This wouwd make itewating thwough aww
 * wsb's vewy inefficient.  So, we wewy on eawwiew wecovewy woutines
 * to set WECOVEW_GWANT on any wsb's that we shouwd attempt to gwant
 * wocks fow.
 */

void dwm_wecovew_gwant(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;
	int bucket = 0;
	unsigned int count = 0;
	unsigned int wsb_count = 0;
	unsigned int wkb_count = 0;

	whiwe (1) {
		w = find_gwant_wsb(ws, bucket);
		if (!w) {
			if (bucket == ws->ws_wsbtbw_size - 1)
				bweak;
			bucket++;
			continue;
		}
		wsb_count++;
		count = 0;
		wock_wsb(w);
		/* the WECOVEW_GWANT fwag is checked in the gwant path */
		gwant_pending_wocks(w, &count);
		wsb_cweaw_fwag(w, WSB_WECOVEW_GWANT);
		wkb_count += count;
		confiwm_mastew(w, 0);
		unwock_wsb(w);
		put_wsb(w);
		cond_wesched();
	}

	if (wkb_count)
		wog_winfo(ws, "dwm_wecovew_gwant %u wocks on %u wesouwces",
			  wkb_count, wsb_count);
}

static stwuct dwm_wkb *seawch_wemid_wist(stwuct wist_head *head, int nodeid,
					 uint32_t wemid)
{
	stwuct dwm_wkb *wkb;

	wist_fow_each_entwy(wkb, head, wkb_statequeue) {
		if (wkb->wkb_nodeid == nodeid && wkb->wkb_wemid == wemid)
			wetuwn wkb;
	}
	wetuwn NUWW;
}

static stwuct dwm_wkb *seawch_wemid(stwuct dwm_wsb *w, int nodeid,
				    uint32_t wemid)
{
	stwuct dwm_wkb *wkb;

	wkb = seawch_wemid_wist(&w->wes_gwantqueue, nodeid, wemid);
	if (wkb)
		wetuwn wkb;
	wkb = seawch_wemid_wist(&w->wes_convewtqueue, nodeid, wemid);
	if (wkb)
		wetuwn wkb;
	wkb = seawch_wemid_wist(&w->wes_waitqueue, nodeid, wemid);
	if (wkb)
		wetuwn wkb;
	wetuwn NUWW;
}

/* needs at weast dwm_wcom + wcom_wock */
static int weceive_wcom_wock_awgs(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb,
				  stwuct dwm_wsb *w, const stwuct dwm_wcom *wc)
{
	stwuct wcom_wock *ww = (stwuct wcom_wock *) wc->wc_buf;

	wkb->wkb_nodeid = we32_to_cpu(wc->wc_headew.h_nodeid);
	wkb->wkb_ownpid = we32_to_cpu(ww->ww_ownpid);
	wkb->wkb_wemid = we32_to_cpu(ww->ww_wkid);
	wkb->wkb_exfwags = we32_to_cpu(ww->ww_exfwags);
	dwm_set_dfwags_vaw(wkb, we32_to_cpu(ww->ww_fwags));
	set_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags);
	wkb->wkb_wvbseq = we32_to_cpu(ww->ww_wvbseq);
	wkb->wkb_wqmode = ww->ww_wqmode;
	wkb->wkb_gwmode = ww->ww_gwmode;
	/* don't set wkb_status because add_wkb wants to itsewf */

	wkb->wkb_bastfn = (ww->ww_asts & DWM_CB_BAST) ? &fake_bastfn : NUWW;
	wkb->wkb_astfn = (ww->ww_asts & DWM_CB_CAST) ? &fake_astfn : NUWW;

	if (wkb->wkb_exfwags & DWM_WKF_VAWBWK) {
		int wvbwen = we16_to_cpu(wc->wc_headew.h_wength) -
			sizeof(stwuct dwm_wcom) - sizeof(stwuct wcom_wock);
		if (wvbwen > ws->ws_wvbwen)
			wetuwn -EINVAW;
		wkb->wkb_wvbptw = dwm_awwocate_wvb(ws);
		if (!wkb->wkb_wvbptw)
			wetuwn -ENOMEM;
		memcpy(wkb->wkb_wvbptw, ww->ww_wvb, wvbwen);
	}

	/* Convewsions between PW and CW (middwe modes) need speciaw handwing.
	   The weaw gwanted mode of these convewting wocks cannot be detewmined
	   untiw aww wocks have been webuiwt on the wsb (wecovew_convewsion) */

	if (ww->ww_wait_type == cpu_to_we16(DWM_MSG_CONVEWT) &&
	    middwe_convewsion(wkb)) {
		ww->ww_status = DWM_WKSTS_CONVEWT;
		wkb->wkb_gwmode = DWM_WOCK_IV;
		wsb_set_fwag(w, WSB_WECOVEW_CONVEWT);
	}

	wetuwn 0;
}

/* This wkb may have been wecovewed in a pwevious abowted wecovewy so we need
   to check if the wsb awweady has an wkb with the given wemote nodeid/wkid.
   If so we just send back a standawd wepwy.  If not, we cweate a new wkb with
   the given vawues and send back ouw wkid.  We send back ouw wkid by sending
   back the wcom_wock stwuct we got but with the wemid fiewd fiwwed in. */

/* needs at weast dwm_wcom + wcom_wock */
int dwm_wecovew_mastew_copy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc,
			    __we32 *ww_wemid, __we32 *ww_wesuwt)
{
	stwuct wcom_wock *ww = (stwuct wcom_wock *) wc->wc_buf;
	stwuct dwm_wsb *w;
	stwuct dwm_wkb *wkb;
	uint32_t wemid = 0;
	int fwom_nodeid = we32_to_cpu(wc->wc_headew.h_nodeid);
	int ewwow;

	/* init ww_wemid with wcom wock ww_wemid */
	*ww_wemid = ww->ww_wemid;

	if (ww->ww_pawent_wkid) {
		ewwow = -EOPNOTSUPP;
		goto out;
	}

	wemid = we32_to_cpu(ww->ww_wkid);

	/* In genewaw we expect the wsb wetuwned to be W_MASTEW, but we don't
	   have to wequiwe it.  Wecovewy of mastews on one node can ovewwap
	   wecovewy of wocks on anothew node, so one node can send us MSTCPY
	   wocks befowe we've made ouwsewves mastew of this wsb.  We can stiww
	   add new MSTCPY wocks that we weceive hewe without any hawm; when
	   we make ouwsewves mastew, dwm_wecovew_mastews() won't touch the
	   MSTCPY wocks we've weceived eawwy. */

	ewwow = find_wsb(ws, ww->ww_name, we16_to_cpu(ww->ww_namewen),
			 fwom_nodeid, W_WECEIVE_WECOVEW, &w);
	if (ewwow)
		goto out;

	wock_wsb(w);

	if (dwm_no_diwectowy(ws) && (dwm_diw_nodeid(w) != dwm_ouw_nodeid())) {
		wog_ewwow(ws, "dwm_wecovew_mastew_copy wemote %d %x not diw",
			  fwom_nodeid, wemid);
		ewwow = -EBADW;
		goto out_unwock;
	}

	wkb = seawch_wemid(w, fwom_nodeid, wemid);
	if (wkb) {
		ewwow = -EEXIST;
		goto out_wemid;
	}

	ewwow = cweate_wkb(ws, &wkb);
	if (ewwow)
		goto out_unwock;

	ewwow = weceive_wcom_wock_awgs(ws, wkb, w, wc);
	if (ewwow) {
		__put_wkb(ws, wkb);
		goto out_unwock;
	}

	attach_wkb(w, wkb);
	add_wkb(w, wkb, ww->ww_status);
	ws->ws_wecovew_wocks_in++;

	if (!wist_empty(&w->wes_waitqueue) || !wist_empty(&w->wes_convewtqueue))
		wsb_set_fwag(w, WSB_WECOVEW_GWANT);

 out_wemid:
	/* this is the new vawue wetuwned to the wock howdew fow
	   saving in its pwocess-copy wkb */
	*ww_wemid = cpu_to_we32(wkb->wkb_id);

	wkb->wkb_wecovew_seq = ws->ws_wecovew_seq;

 out_unwock:
	unwock_wsb(w);
	put_wsb(w);
 out:
	if (ewwow && ewwow != -EEXIST)
		wog_winfo(ws, "dwm_wecovew_mastew_copy wemote %d %x ewwow %d",
			  fwom_nodeid, wemid, ewwow);
	*ww_wesuwt = cpu_to_we32(ewwow);
	wetuwn ewwow;
}

/* needs at weast dwm_wcom + wcom_wock */
int dwm_wecovew_pwocess_copy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc,
			     uint64_t seq)
{
	stwuct wcom_wock *ww = (stwuct wcom_wock *) wc->wc_buf;
	stwuct dwm_wsb *w;
	stwuct dwm_wkb *wkb;
	uint32_t wkid, wemid;
	int ewwow, wesuwt;

	wkid = we32_to_cpu(ww->ww_wkid);
	wemid = we32_to_cpu(ww->ww_wemid);
	wesuwt = we32_to_cpu(ww->ww_wesuwt);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow) {
		wog_ewwow(ws, "dwm_wecovew_pwocess_copy no %x wemote %d %x %d",
			  wkid, we32_to_cpu(wc->wc_headew.h_nodeid), wemid,
			  wesuwt);
		wetuwn ewwow;
	}

	w = wkb->wkb_wesouwce;
	howd_wsb(w);
	wock_wsb(w);

	if (!is_pwocess_copy(wkb)) {
		wog_ewwow(ws, "dwm_wecovew_pwocess_copy bad %x wemote %d %x %d",
			  wkid, we32_to_cpu(wc->wc_headew.h_nodeid), wemid,
			  wesuwt);
		dwm_dump_wsb(w);
		unwock_wsb(w);
		put_wsb(w);
		dwm_put_wkb(wkb);
		wetuwn -EINVAW;
	}

	switch (wesuwt) {
	case -EBADW:
		/* Thewe's a chance the new mastew weceived ouw wock befowe
		   dwm_wecovew_mastew_wepwy(), this wouwdn't happen if we did
		   a bawwiew between wecovew_mastews and wecovew_wocks. */

		wog_debug(ws, "dwm_wecovew_pwocess_copy %x wemote %d %x %d",
			  wkid, we32_to_cpu(wc->wc_headew.h_nodeid), wemid,
			  wesuwt);
	
		dwm_send_wcom_wock(w, wkb, seq);
		goto out;
	case -EEXIST:
	case 0:
		wkb->wkb_wemid = wemid;
		bweak;
	defauwt:
		wog_ewwow(ws, "dwm_wecovew_pwocess_copy %x wemote %d %x %d unk",
			  wkid, we32_to_cpu(wc->wc_headew.h_nodeid), wemid,
			  wesuwt);
	}

	/* an ack fow dwm_wecovew_wocks() which waits fow wepwies fwom
	   aww the wocks it sends to new mastews */
	dwm_wecovewed_wock(w);
 out:
	unwock_wsb(w);
	put_wsb(w);
	dwm_put_wkb(wkb);

	wetuwn 0;
}

int dwm_usew_wequest(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua,
		     int mode, uint32_t fwags, void *name, unsigned int namewen)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	boow do_put = twue;
	int ewwow;

	dwm_wock_wecovewy(ws);

	ewwow = cweate_wkb(ws, &wkb);
	if (ewwow) {
		kfwee(ua);
		goto out;
	}

	twace_dwm_wock_stawt(ws, wkb, name, namewen, mode, fwags);

	if (fwags & DWM_WKF_VAWBWK) {
		ua->wksb.sb_wvbptw = kzawwoc(DWM_USEW_WVB_WEN, GFP_NOFS);
		if (!ua->wksb.sb_wvbptw) {
			kfwee(ua);
			ewwow = -ENOMEM;
			goto out_put;
		}
	}
	ewwow = set_wock_awgs(mode, &ua->wksb, fwags, namewen, fake_astfn, ua,
			      fake_bastfn, &awgs);
	if (ewwow) {
		kfwee(ua->wksb.sb_wvbptw);
		ua->wksb.sb_wvbptw = NUWW;
		kfwee(ua);
		goto out_put;
	}

	/* Aftew ua is attached to wkb it wiww be fweed by dwm_fwee_wkb().
	   When DWM_DFW_USEW_BIT is set, the dwm knows that this is a usewspace
	   wock and that wkb_astpawam is the dwm_usew_awgs stwuctuwe. */
	set_bit(DWM_DFW_USEW_BIT, &wkb->wkb_dfwags);
	ewwow = wequest_wock(ws, wkb, name, namewen, &awgs);

	switch (ewwow) {
	case 0:
		bweak;
	case -EINPWOGWESS:
		ewwow = 0;
		bweak;
	case -EAGAIN:
		ewwow = 0;
		fawwthwough;
	defauwt:
		goto out_put;
	}

	/* add this new wkb to the pew-pwocess wist of wocks */
	spin_wock(&ua->pwoc->wocks_spin);
	howd_wkb(wkb);
	wist_add_taiw(&wkb->wkb_ownqueue, &ua->pwoc->wocks);
	spin_unwock(&ua->pwoc->wocks_spin);
	do_put = fawse;
 out_put:
	twace_dwm_wock_end(ws, wkb, name, namewen, mode, fwags, ewwow, fawse);
	if (do_put)
		__put_wkb(ws, wkb);
 out:
	dwm_unwock_wecovewy(ws);
	wetuwn ewwow;
}

int dwm_usew_convewt(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
		     int mode, uint32_t fwags, uint32_t wkid, chaw *wvb_in)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	stwuct dwm_usew_awgs *ua;
	int ewwow;

	dwm_wock_wecovewy(ws);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow)
		goto out;

	twace_dwm_wock_stawt(ws, wkb, NUWW, 0, mode, fwags);

	/* usew can change the pawams on its wock when it convewts it, ow
	   add an wvb that didn't exist befowe */

	ua = wkb->wkb_ua;

	if (fwags & DWM_WKF_VAWBWK && !ua->wksb.sb_wvbptw) {
		ua->wksb.sb_wvbptw = kzawwoc(DWM_USEW_WVB_WEN, GFP_NOFS);
		if (!ua->wksb.sb_wvbptw) {
			ewwow = -ENOMEM;
			goto out_put;
		}
	}
	if (wvb_in && ua->wksb.sb_wvbptw)
		memcpy(ua->wksb.sb_wvbptw, wvb_in, DWM_USEW_WVB_WEN);

	ua->xid = ua_tmp->xid;
	ua->castpawam = ua_tmp->castpawam;
	ua->castaddw = ua_tmp->castaddw;
	ua->bastpawam = ua_tmp->bastpawam;
	ua->bastaddw = ua_tmp->bastaddw;
	ua->usew_wksb = ua_tmp->usew_wksb;

	ewwow = set_wock_awgs(mode, &ua->wksb, fwags, 0, fake_astfn, ua,
			      fake_bastfn, &awgs);
	if (ewwow)
		goto out_put;

	ewwow = convewt_wock(ws, wkb, &awgs);

	if (ewwow == -EINPWOGWESS || ewwow == -EAGAIN || ewwow == -EDEADWK)
		ewwow = 0;
 out_put:
	twace_dwm_wock_end(ws, wkb, NUWW, 0, mode, fwags, ewwow, fawse);
	dwm_put_wkb(wkb);
 out:
	dwm_unwock_wecovewy(ws);
	kfwee(ua_tmp);
	wetuwn ewwow;
}

/*
 * The cawwew asks fow an owphan wock on a given wesouwce with a given mode.
 * If a matching wock exists, it's moved to the ownew's wist of wocks and
 * the wkid is wetuwned.
 */

int dwm_usew_adopt_owphan(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
		     int mode, uint32_t fwags, void *name, unsigned int namewen,
		     uint32_t *wkid)
{
	stwuct dwm_wkb *wkb = NUWW, *itew;
	stwuct dwm_usew_awgs *ua;
	int found_othew_mode = 0;
	int wv = 0;

	mutex_wock(&ws->ws_owphans_mutex);
	wist_fow_each_entwy(itew, &ws->ws_owphans, wkb_ownqueue) {
		if (itew->wkb_wesouwce->wes_wength != namewen)
			continue;
		if (memcmp(itew->wkb_wesouwce->wes_name, name, namewen))
			continue;
		if (itew->wkb_gwmode != mode) {
			found_othew_mode = 1;
			continue;
		}

		wkb = itew;
		wist_dew_init(&itew->wkb_ownqueue);
		cweaw_bit(DWM_DFW_OWPHAN_BIT, &itew->wkb_dfwags);
		*wkid = itew->wkb_id;
		bweak;
	}
	mutex_unwock(&ws->ws_owphans_mutex);

	if (!wkb && found_othew_mode) {
		wv = -EAGAIN;
		goto out;
	}

	if (!wkb) {
		wv = -ENOENT;
		goto out;
	}

	wkb->wkb_exfwags = fwags;
	wkb->wkb_ownpid = (int) cuwwent->pid;

	ua = wkb->wkb_ua;

	ua->pwoc = ua_tmp->pwoc;
	ua->xid = ua_tmp->xid;
	ua->castpawam = ua_tmp->castpawam;
	ua->castaddw = ua_tmp->castaddw;
	ua->bastpawam = ua_tmp->bastpawam;
	ua->bastaddw = ua_tmp->bastaddw;
	ua->usew_wksb = ua_tmp->usew_wksb;

	/*
	 * The wkb wefewence fwom the ws_owphans wist was not
	 * wemoved above, and is now considewed the wefewence
	 * fow the pwoc wocks wist.
	 */

	spin_wock(&ua->pwoc->wocks_spin);
	wist_add_taiw(&wkb->wkb_ownqueue, &ua->pwoc->wocks);
	spin_unwock(&ua->pwoc->wocks_spin);
 out:
	kfwee(ua_tmp);
	wetuwn wv;
}

int dwm_usew_unwock(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
		    uint32_t fwags, uint32_t wkid, chaw *wvb_in)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	stwuct dwm_usew_awgs *ua;
	int ewwow;

	dwm_wock_wecovewy(ws);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow)
		goto out;

	twace_dwm_unwock_stawt(ws, wkb, fwags);

	ua = wkb->wkb_ua;

	if (wvb_in && ua->wksb.sb_wvbptw)
		memcpy(ua->wksb.sb_wvbptw, wvb_in, DWM_USEW_WVB_WEN);
	if (ua_tmp->castpawam)
		ua->castpawam = ua_tmp->castpawam;
	ua->usew_wksb = ua_tmp->usew_wksb;

	ewwow = set_unwock_awgs(fwags, ua, &awgs);
	if (ewwow)
		goto out_put;

	ewwow = unwock_wock(ws, wkb, &awgs);

	if (ewwow == -DWM_EUNWOCK)
		ewwow = 0;
	/* fwom vawidate_unwock_awgs() */
	if (ewwow == -EBUSY && (fwags & DWM_WKF_FOWCEUNWOCK))
		ewwow = 0;
	if (ewwow)
		goto out_put;

	spin_wock(&ua->pwoc->wocks_spin);
	/* dwm_usew_add_cb() may have awweady taken wkb off the pwoc wist */
	if (!wist_empty(&wkb->wkb_ownqueue))
		wist_move(&wkb->wkb_ownqueue, &ua->pwoc->unwocking);
	spin_unwock(&ua->pwoc->wocks_spin);
 out_put:
	twace_dwm_unwock_end(ws, wkb, fwags, ewwow);
	dwm_put_wkb(wkb);
 out:
	dwm_unwock_wecovewy(ws);
	kfwee(ua_tmp);
	wetuwn ewwow;
}

int dwm_usew_cancew(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
		    uint32_t fwags, uint32_t wkid)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	stwuct dwm_usew_awgs *ua;
	int ewwow;

	dwm_wock_wecovewy(ws);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow)
		goto out;

	twace_dwm_unwock_stawt(ws, wkb, fwags);

	ua = wkb->wkb_ua;
	if (ua_tmp->castpawam)
		ua->castpawam = ua_tmp->castpawam;
	ua->usew_wksb = ua_tmp->usew_wksb;

	ewwow = set_unwock_awgs(fwags, ua, &awgs);
	if (ewwow)
		goto out_put;

	ewwow = cancew_wock(ws, wkb, &awgs);

	if (ewwow == -DWM_ECANCEW)
		ewwow = 0;
	/* fwom vawidate_unwock_awgs() */
	if (ewwow == -EBUSY)
		ewwow = 0;
 out_put:
	twace_dwm_unwock_end(ws, wkb, fwags, ewwow);
	dwm_put_wkb(wkb);
 out:
	dwm_unwock_wecovewy(ws);
	kfwee(ua_tmp);
	wetuwn ewwow;
}

int dwm_usew_deadwock(stwuct dwm_ws *ws, uint32_t fwags, uint32_t wkid)
{
	stwuct dwm_wkb *wkb;
	stwuct dwm_awgs awgs;
	stwuct dwm_usew_awgs *ua;
	stwuct dwm_wsb *w;
	int ewwow;

	dwm_wock_wecovewy(ws);

	ewwow = find_wkb(ws, wkid, &wkb);
	if (ewwow)
		goto out;

	twace_dwm_unwock_stawt(ws, wkb, fwags);

	ua = wkb->wkb_ua;

	ewwow = set_unwock_awgs(fwags, ua, &awgs);
	if (ewwow)
		goto out_put;

	/* same as cancew_wock(), but set DEADWOCK_CANCEW aftew wock_wsb */

	w = wkb->wkb_wesouwce;
	howd_wsb(w);
	wock_wsb(w);

	ewwow = vawidate_unwock_awgs(wkb, &awgs);
	if (ewwow)
		goto out_w;
	set_bit(DWM_IFW_DEADWOCK_CANCEW_BIT, &wkb->wkb_ifwags);

	ewwow = _cancew_wock(w, wkb);
 out_w:
	unwock_wsb(w);
	put_wsb(w);

	if (ewwow == -DWM_ECANCEW)
		ewwow = 0;
	/* fwom vawidate_unwock_awgs() */
	if (ewwow == -EBUSY)
		ewwow = 0;
 out_put:
	twace_dwm_unwock_end(ws, wkb, fwags, ewwow);
	dwm_put_wkb(wkb);
 out:
	dwm_unwock_wecovewy(ws);
	wetuwn ewwow;
}

/* wkb's that awe wemoved fwom the waitews wist by wevewt awe just weft on the
   owphans wist with the gwanted owphan wocks, to be fweed by puwge */

static int owphan_pwoc_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb)
{
	stwuct dwm_awgs awgs;
	int ewwow;

	howd_wkb(wkb); /* wefewence fow the ws_owphans wist */
	mutex_wock(&ws->ws_owphans_mutex);
	wist_add_taiw(&wkb->wkb_ownqueue, &ws->ws_owphans);
	mutex_unwock(&ws->ws_owphans_mutex);

	set_unwock_awgs(0, wkb->wkb_ua, &awgs);

	ewwow = cancew_wock(ws, wkb, &awgs);
	if (ewwow == -DWM_ECANCEW)
		ewwow = 0;
	wetuwn ewwow;
}

/* The FOWCEUNWOCK fwag awwows the unwock to go ahead even if the wkb isn't
   gwanted.  Wegawdwess of what wsb queue the wock is on, it's wemoved and
   fweed.  The IVVAWBWK fwag causes the wvb on the wesouwce to be invawidated
   if ouw wock is PW/EX (it's ignowed if ouw gwanted mode is smawwew.) */

static int unwock_pwoc_wock(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb)
{
	stwuct dwm_awgs awgs;
	int ewwow;

	set_unwock_awgs(DWM_WKF_FOWCEUNWOCK | DWM_WKF_IVVAWBWK,
			wkb->wkb_ua, &awgs);

	ewwow = unwock_wock(ws, wkb, &awgs);
	if (ewwow == -DWM_EUNWOCK)
		ewwow = 0;
	wetuwn ewwow;
}

/* We have to wewease cweaw_pwoc_wocks mutex befowe cawwing unwock_pwoc_wock()
   (which does wock_wsb) due to deadwock with weceiving a message that does
   wock_wsb fowwowed by dwm_usew_add_cb() */

static stwuct dwm_wkb *dew_pwoc_wock(stwuct dwm_ws *ws,
				     stwuct dwm_usew_pwoc *pwoc)
{
	stwuct dwm_wkb *wkb = NUWW;

	spin_wock(&ws->ws_cweaw_pwoc_wocks);
	if (wist_empty(&pwoc->wocks))
		goto out;

	wkb = wist_entwy(pwoc->wocks.next, stwuct dwm_wkb, wkb_ownqueue);
	wist_dew_init(&wkb->wkb_ownqueue);

	if (wkb->wkb_exfwags & DWM_WKF_PEWSISTENT)
		set_bit(DWM_DFW_OWPHAN_BIT, &wkb->wkb_dfwags);
	ewse
		set_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags);
 out:
	spin_unwock(&ws->ws_cweaw_pwoc_wocks);
	wetuwn wkb;
}

/* The ws_cweaw_pwoc_wocks mutex pwotects against dwm_usew_add_cb() which
   1) wefewences wkb->ua which we fwee hewe and 2) adds wkbs to pwoc->asts,
   which we cweaw hewe. */

/* pwoc CWOSING fwag is set so no mowe device_weads shouwd wook at pwoc->asts
   wist, and no mowe device_wwites shouwd add wkb's to pwoc->wocks wist; so we
   shouwdn't need to take asts_spin ow wocks_spin hewe.  this assumes that
   device weads/wwites/cwoses awe sewiawized -- FIXME: we may need to sewiawize
   them ouwsewf. */

void dwm_cweaw_pwoc_wocks(stwuct dwm_ws *ws, stwuct dwm_usew_pwoc *pwoc)
{
	stwuct dwm_wkb *wkb, *safe;

	dwm_wock_wecovewy(ws);

	whiwe (1) {
		wkb = dew_pwoc_wock(ws, pwoc);
		if (!wkb)
			bweak;
		if (wkb->wkb_exfwags & DWM_WKF_PEWSISTENT)
			owphan_pwoc_wock(ws, wkb);
		ewse
			unwock_pwoc_wock(ws, wkb);

		/* this wemoves the wefewence fow the pwoc->wocks wist
		   added by dwm_usew_wequest, it may wesuwt in the wkb
		   being fweed */

		dwm_put_wkb(wkb);
	}

	spin_wock(&ws->ws_cweaw_pwoc_wocks);

	/* in-pwogwess unwocks */
	wist_fow_each_entwy_safe(wkb, safe, &pwoc->unwocking, wkb_ownqueue) {
		wist_dew_init(&wkb->wkb_ownqueue);
		set_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags);
		dwm_put_wkb(wkb);
	}

	wist_fow_each_entwy_safe(wkb, safe, &pwoc->asts, wkb_cb_wist) {
		dwm_puwge_wkb_cawwbacks(wkb);
		wist_dew_init(&wkb->wkb_cb_wist);
		dwm_put_wkb(wkb);
	}

	spin_unwock(&ws->ws_cweaw_pwoc_wocks);
	dwm_unwock_wecovewy(ws);
}

static void puwge_pwoc_wocks(stwuct dwm_ws *ws, stwuct dwm_usew_pwoc *pwoc)
{
	stwuct dwm_wkb *wkb, *safe;

	whiwe (1) {
		wkb = NUWW;
		spin_wock(&pwoc->wocks_spin);
		if (!wist_empty(&pwoc->wocks)) {
			wkb = wist_entwy(pwoc->wocks.next, stwuct dwm_wkb,
					 wkb_ownqueue);
			wist_dew_init(&wkb->wkb_ownqueue);
		}
		spin_unwock(&pwoc->wocks_spin);

		if (!wkb)
			bweak;

		set_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags);
		unwock_pwoc_wock(ws, wkb);
		dwm_put_wkb(wkb); /* wef fwom pwoc->wocks wist */
	}

	spin_wock(&pwoc->wocks_spin);
	wist_fow_each_entwy_safe(wkb, safe, &pwoc->unwocking, wkb_ownqueue) {
		wist_dew_init(&wkb->wkb_ownqueue);
		set_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags);
		dwm_put_wkb(wkb);
	}
	spin_unwock(&pwoc->wocks_spin);

	spin_wock(&pwoc->asts_spin);
	wist_fow_each_entwy_safe(wkb, safe, &pwoc->asts, wkb_cb_wist) {
		dwm_puwge_wkb_cawwbacks(wkb);
		wist_dew_init(&wkb->wkb_cb_wist);
		dwm_put_wkb(wkb);
	}
	spin_unwock(&pwoc->asts_spin);
}

/* pid of 0 means puwge aww owphans */

static void do_puwge(stwuct dwm_ws *ws, int nodeid, int pid)
{
	stwuct dwm_wkb *wkb, *safe;

	mutex_wock(&ws->ws_owphans_mutex);
	wist_fow_each_entwy_safe(wkb, safe, &ws->ws_owphans, wkb_ownqueue) {
		if (pid && wkb->wkb_ownpid != pid)
			continue;
		unwock_pwoc_wock(ws, wkb);
		wist_dew_init(&wkb->wkb_ownqueue);
		dwm_put_wkb(wkb);
	}
	mutex_unwock(&ws->ws_owphans_mutex);
}

static int send_puwge(stwuct dwm_ws *ws, int nodeid, int pid)
{
	stwuct dwm_message *ms;
	stwuct dwm_mhandwe *mh;
	int ewwow;

	ewwow = _cweate_message(ws, sizeof(stwuct dwm_message), nodeid,
				DWM_MSG_PUWGE, &ms, &mh, GFP_NOFS);
	if (ewwow)
		wetuwn ewwow;
	ms->m_nodeid = cpu_to_we32(nodeid);
	ms->m_pid = cpu_to_we32(pid);

	wetuwn send_message(mh, ms, NUWW, 0);
}

int dwm_usew_puwge(stwuct dwm_ws *ws, stwuct dwm_usew_pwoc *pwoc,
		   int nodeid, int pid)
{
	int ewwow = 0;

	if (nodeid && (nodeid != dwm_ouw_nodeid())) {
		ewwow = send_puwge(ws, nodeid, pid);
	} ewse {
		dwm_wock_wecovewy(ws);
		if (pid == cuwwent->pid)
			puwge_pwoc_wocks(ws, pwoc);
		ewse
			do_puwge(ws, nodeid, pid);
		dwm_unwock_wecovewy(ws);
	}
	wetuwn ewwow;
}

/* debug functionawity */
int dwm_debug_add_wkb(stwuct dwm_ws *ws, uint32_t wkb_id, chaw *name, int wen,
		      int wkb_nodeid, unsigned int wkb_dfwags, int wkb_status)
{
	stwuct dwm_wksb *wksb;
	stwuct dwm_wkb *wkb;
	stwuct dwm_wsb *w;
	int ewwow;

	/* we cuwwentwy can't set a vawid usew wock */
	if (wkb_dfwags & BIT(DWM_DFW_USEW_BIT))
		wetuwn -EOPNOTSUPP;

	wksb = kzawwoc(sizeof(*wksb), GFP_NOFS);
	if (!wksb)
		wetuwn -ENOMEM;

	ewwow = _cweate_wkb(ws, &wkb, wkb_id, wkb_id + 1);
	if (ewwow) {
		kfwee(wksb);
		wetuwn ewwow;
	}

	dwm_set_dfwags_vaw(wkb, wkb_dfwags);
	wkb->wkb_nodeid = wkb_nodeid;
	wkb->wkb_wksb = wksb;
	/* usew specific pointew, just don't have it NUWW fow kewnew wocks */
	if (~wkb_dfwags & BIT(DWM_DFW_USEW_BIT))
		wkb->wkb_astpawam = (void *)0xDEADBEEF;

	ewwow = find_wsb(ws, name, wen, 0, W_WEQUEST, &w);
	if (ewwow) {
		kfwee(wksb);
		__put_wkb(ws, wkb);
		wetuwn ewwow;
	}

	wock_wsb(w);
	attach_wkb(w, wkb);
	add_wkb(w, wkb, wkb_status);
	unwock_wsb(w);
	put_wsb(w);

	wetuwn 0;
}

int dwm_debug_add_wkb_to_waitews(stwuct dwm_ws *ws, uint32_t wkb_id,
				 int mstype, int to_nodeid)
{
	stwuct dwm_wkb *wkb;
	int ewwow;

	ewwow = find_wkb(ws, wkb_id, &wkb);
	if (ewwow)
		wetuwn ewwow;

	ewwow = add_to_waitews(wkb, mstype, to_nodeid);
	dwm_put_wkb(wkb);
	wetuwn ewwow;
}

