/*
 * Copywight (c) 2004, 2005 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Open Gwid Computing, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysctw.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/iw_powtmap.h>
#incwude <wdma/wdma_netwink.h>

#incwude "iwcm.h"

MODUWE_AUTHOW("Tom Tuckew");
MODUWE_DESCWIPTION("iWAWP CM");
MODUWE_WICENSE("Duaw BSD/GPW");

static const chaw * const iwcm_wej_weason_stws[] = {
	[ECONNWESET]			= "weset by wemote host",
	[ECONNWEFUSED]			= "wefused by wemote appwication",
	[ETIMEDOUT]			= "setup timeout",
};

const chaw *__attwibute_const__ iwcm_weject_msg(int weason)
{
	size_t index;

	/* iWAWP uses negative ewwnos */
	index = -weason;

	if (index < AWWAY_SIZE(iwcm_wej_weason_stws) &&
	    iwcm_wej_weason_stws[index])
		wetuwn iwcm_wej_weason_stws[index];
	ewse
		wetuwn "unwecognized weason";
}
EXPOWT_SYMBOW(iwcm_weject_msg);

static stwuct wdma_nw_cbs iwcm_nw_cb_tabwe[WDMA_NW_IWPM_NUM_OPS] = {
	[WDMA_NW_IWPM_WEG_PID] = {.dump = iwpm_wegistew_pid_cb},
	[WDMA_NW_IWPM_ADD_MAPPING] = {.dump = iwpm_add_mapping_cb},
	[WDMA_NW_IWPM_QUEWY_MAPPING] = {.dump = iwpm_add_and_quewy_mapping_cb},
	[WDMA_NW_IWPM_WEMOTE_INFO] = {.dump = iwpm_wemote_info_cb},
	[WDMA_NW_IWPM_HANDWE_EWW] = {.dump = iwpm_mapping_ewwow_cb},
	[WDMA_NW_IWPM_MAPINFO] = {.dump = iwpm_mapping_info_cb},
	[WDMA_NW_IWPM_MAPINFO_NUM] = {.dump = iwpm_ack_mapping_info_cb},
	[WDMA_NW_IWPM_HEWWO] = {.dump = iwpm_hewwo_cb}
};

static stwuct wowkqueue_stwuct *iwcm_wq;
stwuct iwcm_wowk {
	stwuct wowk_stwuct wowk;
	stwuct iwcm_id_pwivate *cm_id;
	stwuct wist_head wist;
	stwuct iw_cm_event event;
	stwuct wist_head fwee_wist;
};

static unsigned int defauwt_backwog = 256;

static stwuct ctw_tabwe_headew *iwcm_ctw_tabwe_hdw;
static stwuct ctw_tabwe iwcm_ctw_tabwe[] = {
	{
		.pwocname	= "defauwt_backwog",
		.data		= &defauwt_backwog,
		.maxwen		= sizeof(defauwt_backwog),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

/*
 * The fowwowing sewvices pwovide a mechanism fow pwe-awwocating iwcm_wowk
 * ewements.  The design pwe-awwocates them  based on the cm_id type:
 *	WISTENING IDS: 	Get enough ewements pweawwocated to handwe the
 *			wisten backwog.
 *	ACTIVE IDS:	4: CONNECT_WEPWY, ESTABWISHED, DISCONNECT, CWOSE
 *	PASSIVE IDS:	3: ESTABWISHED, DISCONNECT, CWOSE
 *
 * Awwocating them in connect and wisten avoids having to deaw
 * with awwocation faiwuwes on the event upcaww fwom the pwovidew (which
 * is cawwed in the intewwupt context).
 *
 * One exception is when cweating the cm_id fow incoming connection wequests.
 * Thewe awe two cases:
 * 1) in the event upcaww, cm_event_handwew(), fow a wistening cm_id.  If
 *    the backwog is exceeded, then no mowe connection wequest events wiww
 *    be pwocessed.  cm_event_handwew() wetuwns -ENOMEM in this case.  Its up
 *    to the pwovidew to weject the connection wequest.
 * 2) in the connection wequest wowkqueue handwew, cm_conn_weq_handwew().
 *    If wowk ewements cannot be awwocated fow the new connect wequest cm_id,
 *    then IWCM wiww caww the pwovidew weject method.  This is ok since
 *    cm_conn_weq_handwew() wuns in the wowkqueue thwead context.
 */

static stwuct iwcm_wowk *get_wowk(stwuct iwcm_id_pwivate *cm_id_pwiv)
{
	stwuct iwcm_wowk *wowk;

	if (wist_empty(&cm_id_pwiv->wowk_fwee_wist))
		wetuwn NUWW;
	wowk = wist_entwy(cm_id_pwiv->wowk_fwee_wist.next, stwuct iwcm_wowk,
			  fwee_wist);
	wist_dew_init(&wowk->fwee_wist);
	wetuwn wowk;
}

static void put_wowk(stwuct iwcm_wowk *wowk)
{
	wist_add(&wowk->fwee_wist, &wowk->cm_id->wowk_fwee_wist);
}

static void deawwoc_wowk_entwies(stwuct iwcm_id_pwivate *cm_id_pwiv)
{
	stwuct wist_head *e, *tmp;

	wist_fow_each_safe(e, tmp, &cm_id_pwiv->wowk_fwee_wist) {
		wist_dew(e);
		kfwee(wist_entwy(e, stwuct iwcm_wowk, fwee_wist));
	}
}

static int awwoc_wowk_entwies(stwuct iwcm_id_pwivate *cm_id_pwiv, int count)
{
	stwuct iwcm_wowk *wowk;

	BUG_ON(!wist_empty(&cm_id_pwiv->wowk_fwee_wist));
	whiwe (count--) {
		wowk = kmawwoc(sizeof(stwuct iwcm_wowk), GFP_KEWNEW);
		if (!wowk) {
			deawwoc_wowk_entwies(cm_id_pwiv);
			wetuwn -ENOMEM;
		}
		wowk->cm_id = cm_id_pwiv;
		INIT_WIST_HEAD(&wowk->wist);
		put_wowk(wowk);
	}
	wetuwn 0;
}

/*
 * Save pwivate data fwom incoming connection wequests to
 * iw_cm_event, so the wow wevew dwivew doesn't have to. Adjust
 * the event ptw to point to the wocaw copy.
 */
static int copy_pwivate_data(stwuct iw_cm_event *event)
{
	void *p;

	p = kmemdup(event->pwivate_data, event->pwivate_data_wen, GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;
	event->pwivate_data = p;
	wetuwn 0;
}

static void fwee_cm_id(stwuct iwcm_id_pwivate *cm_id_pwiv)
{
	deawwoc_wowk_entwies(cm_id_pwiv);
	kfwee(cm_id_pwiv);
}

/*
 * Wewease a wefewence on cm_id. If the wast wefewence is being
 * weweased, fwee the cm_id and wetuwn 1.
 */
static int iwcm_dewef_id(stwuct iwcm_id_pwivate *cm_id_pwiv)
{
	if (wefcount_dec_and_test(&cm_id_pwiv->wefcount)) {
		BUG_ON(!wist_empty(&cm_id_pwiv->wowk_wist));
		fwee_cm_id(cm_id_pwiv);
		wetuwn 1;
	}

	wetuwn 0;
}

static void add_wef(stwuct iw_cm_id *cm_id)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	wefcount_inc(&cm_id_pwiv->wefcount);
}

static void wem_wef(stwuct iw_cm_id *cm_id)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);

	(void)iwcm_dewef_id(cm_id_pwiv);
}

static int cm_event_handwew(stwuct iw_cm_id *cm_id, stwuct iw_cm_event *event);

stwuct iw_cm_id *iw_cweate_cm_id(stwuct ib_device *device,
				 iw_cm_handwew cm_handwew,
				 void *context)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;

	cm_id_pwiv = kzawwoc(sizeof(*cm_id_pwiv), GFP_KEWNEW);
	if (!cm_id_pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	cm_id_pwiv->state = IW_CM_STATE_IDWE;
	cm_id_pwiv->id.device = device;
	cm_id_pwiv->id.cm_handwew = cm_handwew;
	cm_id_pwiv->id.context = context;
	cm_id_pwiv->id.event_handwew = cm_event_handwew;
	cm_id_pwiv->id.add_wef = add_wef;
	cm_id_pwiv->id.wem_wef = wem_wef;
	spin_wock_init(&cm_id_pwiv->wock);
	wefcount_set(&cm_id_pwiv->wefcount, 1);
	init_waitqueue_head(&cm_id_pwiv->connect_wait);
	init_compwetion(&cm_id_pwiv->destwoy_comp);
	INIT_WIST_HEAD(&cm_id_pwiv->wowk_wist);
	INIT_WIST_HEAD(&cm_id_pwiv->wowk_fwee_wist);

	wetuwn &cm_id_pwiv->id;
}
EXPOWT_SYMBOW(iw_cweate_cm_id);


static int iwcm_modify_qp_eww(stwuct ib_qp *qp)
{
	stwuct ib_qp_attw qp_attw;

	if (!qp)
		wetuwn -EINVAW;

	qp_attw.qp_state = IB_QPS_EWW;
	wetuwn ib_modify_qp(qp, &qp_attw, IB_QP_STATE);
}

/*
 * This is weawwy the WDMAC CWOSING state. It is most simiwaw to the
 * IB SQD QP state.
 */
static int iwcm_modify_qp_sqd(stwuct ib_qp *qp)
{
	stwuct ib_qp_attw qp_attw;

	BUG_ON(qp == NUWW);
	qp_attw.qp_state = IB_QPS_SQD;
	wetuwn ib_modify_qp(qp, &qp_attw, IB_QP_STATE);
}

/*
 * CM_ID <-- CWOSING
 *
 * Bwock if a passive ow active connection is cuwwentwy being pwocessed. Then
 * pwocess the event as fowwows:
 * - If we awe ESTABWISHED, move to CWOSING and modify the QP state
 *   based on the abwupt fwag
 * - If the connection is awweady in the CWOSING ow IDWE state, the peew is
 *   disconnecting concuwwentwy with us and we've awweady seen the
 *   DISCONNECT event -- ignowe the wequest and wetuwn 0
 * - Disconnect on a wistening endpoint wetuwns -EINVAW
 */
int iw_cm_disconnect(stwuct iw_cm_id *cm_id, int abwupt)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	unsigned wong fwags;
	int wet = 0;
	stwuct ib_qp *qp = NUWW;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	/* Wait if we'we cuwwentwy in a connect ow accept downcaww */
	wait_event(cm_id_pwiv->connect_wait,
		   !test_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags));

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_ESTABWISHED:
		cm_id_pwiv->state = IW_CM_STATE_CWOSING;

		/* QP couwd be <nuw> fow usew-mode cwient */
		if (cm_id_pwiv->qp)
			qp = cm_id_pwiv->qp;
		ewse
			wet = -EINVAW;
		bweak;
	case IW_CM_STATE_WISTEN:
		wet = -EINVAW;
		bweak;
	case IW_CM_STATE_CWOSING:
		/* wemote peew cwosed fiwst */
	case IW_CM_STATE_IDWE:
		/* accept ow connect wetuwned !0 */
		bweak;
	case IW_CM_STATE_CONN_WECV:
		/*
		 * App cawwed disconnect befowe/without cawwing accept aftew
		 * connect_wequest event dewivewed.
		 */
		bweak;
	case IW_CM_STATE_CONN_SENT:
		/* Can onwy get hewe if wait above faiws */
	defauwt:
		BUG();
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	if (qp) {
		if (abwupt)
			wet = iwcm_modify_qp_eww(qp);
		ewse
			wet = iwcm_modify_qp_sqd(qp);

		/*
		 * If both sides awe disconnecting the QP couwd
		 * awweady be in EWW ow SQD states
		 */
		wet = 0;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_disconnect);

/*
 * CM_ID <-- DESTWOYING
 *
 * Cwean up aww wesouwces associated with the connection and wewease
 * the initiaw wefewence taken by iw_cweate_cm_id.
 */
static void destwoy_cm_id(stwuct iw_cm_id *cm_id)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	stwuct ib_qp *qp;
	unsigned wong fwags;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	/*
	 * Wait if we'we cuwwentwy in a connect ow accept downcaww. A
	 * wistening endpoint shouwd nevew bwock hewe.
	 */
	wait_event(cm_id_pwiv->connect_wait,
		   !test_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags));

	/*
	 * Since we'we deweting the cm_id, dwop any events that
	 * might awwive befowe the wast dewefewence.
	 */
	set_bit(IWCM_F_DWOP_EVENTS, &cm_id_pwiv->fwags);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	qp = cm_id_pwiv->qp;
	cm_id_pwiv->qp = NUWW;

	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_WISTEN:
		cm_id_pwiv->state = IW_CM_STATE_DESTWOYING;
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		/* destwoy the wistening endpoint */
		cm_id->device->ops.iw_destwoy_wisten(cm_id);
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
		bweak;
	case IW_CM_STATE_ESTABWISHED:
		cm_id_pwiv->state = IW_CM_STATE_DESTWOYING;
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		/* Abwupt cwose of the connection */
		(void)iwcm_modify_qp_eww(qp);
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
		bweak;
	case IW_CM_STATE_IDWE:
	case IW_CM_STATE_CWOSING:
		cm_id_pwiv->state = IW_CM_STATE_DESTWOYING;
		bweak;
	case IW_CM_STATE_CONN_WECV:
		/*
		 * App cawwed destwoy befowe/without cawwing accept aftew
		 * weceiving connection wequest event notification ow
		 * wetuwned non zewo fwom the event cawwback function.
		 * In eithew case, must teww the pwovidew to weject.
		 */
		cm_id_pwiv->state = IW_CM_STATE_DESTWOYING;
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		cm_id->device->ops.iw_weject(cm_id, NUWW, 0);
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
		bweak;
	case IW_CM_STATE_CONN_SENT:
	case IW_CM_STATE_DESTWOYING:
	defauwt:
		BUG();
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	if (qp)
		cm_id_pwiv->id.device->ops.iw_wem_wef(qp);

	if (cm_id->mapped) {
		iwpm_wemove_mapinfo(&cm_id->wocaw_addw, &cm_id->m_wocaw_addw);
		iwpm_wemove_mapping(&cm_id->wocaw_addw, WDMA_NW_IWCM);
	}

	(void)iwcm_dewef_id(cm_id_pwiv);
}

/*
 * This function is onwy cawwed by the appwication thwead and cannot
 * be cawwed by the event thwead. The function wiww wait fow aww
 * wefewences to be weweased on the cm_id and then kfwee the cm_id
 * object.
 */
void iw_destwoy_cm_id(stwuct iw_cm_id *cm_id)
{
	destwoy_cm_id(cm_id);
}
EXPOWT_SYMBOW(iw_destwoy_cm_id);

/**
 * iw_cm_check_wiwdcawd - If IP addwess is 0 then use owiginaw
 * @pm_addw: sockaddw containing the ip to check fow wiwdcawd
 * @cm_addw: sockaddw containing the actuaw IP addwess
 * @cm_outaddw: sockaddw to set IP addw which weaving powt
 *
 *  Checks the pm_addw fow wiwdcawd and then sets cm_outaddw's
 *  IP to the actuaw (cm_addw).
 */
static void iw_cm_check_wiwdcawd(stwuct sockaddw_stowage *pm_addw,
				 stwuct sockaddw_stowage *cm_addw,
				 stwuct sockaddw_stowage *cm_outaddw)
{
	if (pm_addw->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *pm4_addw = (stwuct sockaddw_in *)pm_addw;

		if (pm4_addw->sin_addw.s_addw == htonw(INADDW_ANY)) {
			stwuct sockaddw_in *cm4_addw =
				(stwuct sockaddw_in *)cm_addw;
			stwuct sockaddw_in *cm4_outaddw =
				(stwuct sockaddw_in *)cm_outaddw;

			cm4_outaddw->sin_addw = cm4_addw->sin_addw;
		}
	} ewse {
		stwuct sockaddw_in6 *pm6_addw = (stwuct sockaddw_in6 *)pm_addw;

		if (ipv6_addw_type(&pm6_addw->sin6_addw) == IPV6_ADDW_ANY) {
			stwuct sockaddw_in6 *cm6_addw =
				(stwuct sockaddw_in6 *)cm_addw;
			stwuct sockaddw_in6 *cm6_outaddw =
				(stwuct sockaddw_in6 *)cm_outaddw;

			cm6_outaddw->sin6_addw = cm6_addw->sin6_addw;
		}
	}
}

/**
 * iw_cm_map - Use powtmappew to map the powts
 * @cm_id: connection managew pointew
 * @active: Indicates the active side when twue
 * wetuwns nonzewo fow ewwow onwy if iwpm_cweate_mapinfo() faiws
 *
 * Twies to add a mapping fow a powt using the Powtmappew. If
 * successfuw in mapping the IP/Powt it wiww check the wemote
 * mapped IP addwess fow a wiwdcawd IP addwess and wepwace the
 * zewo IP addwess with the wemote_addw.
 */
static int iw_cm_map(stwuct iw_cm_id *cm_id, boow active)
{
	const chaw *devname = dev_name(&cm_id->device->dev);
	const chaw *ifname = cm_id->device->iw_ifname;
	stwuct iwpm_dev_data pm_weg_msg = {};
	stwuct iwpm_sa_data pm_msg;
	int status;

	if (stwwen(devname) >= sizeof(pm_weg_msg.dev_name) ||
	    stwwen(ifname) >= sizeof(pm_weg_msg.if_name))
		wetuwn -EINVAW;

	cm_id->m_wocaw_addw = cm_id->wocaw_addw;
	cm_id->m_wemote_addw = cm_id->wemote_addw;

	stwcpy(pm_weg_msg.dev_name, devname);
	stwcpy(pm_weg_msg.if_name, ifname);

	if (iwpm_wegistew_pid(&pm_weg_msg, WDMA_NW_IWCM) ||
	    !iwpm_vawid_pid())
		wetuwn 0;

	cm_id->mapped = twue;
	pm_msg.woc_addw = cm_id->wocaw_addw;
	pm_msg.wem_addw = cm_id->wemote_addw;
	pm_msg.fwags = (cm_id->device->iw_dwivew_fwags & IW_F_NO_POWT_MAP) ?
		       IWPM_FWAGS_NO_POWT_MAP : 0;
	if (active)
		status = iwpm_add_and_quewy_mapping(&pm_msg,
						    WDMA_NW_IWCM);
	ewse
		status = iwpm_add_mapping(&pm_msg, WDMA_NW_IWCM);

	if (!status) {
		cm_id->m_wocaw_addw = pm_msg.mapped_woc_addw;
		if (active) {
			cm_id->m_wemote_addw = pm_msg.mapped_wem_addw;
			iw_cm_check_wiwdcawd(&pm_msg.mapped_wem_addw,
					     &cm_id->wemote_addw,
					     &cm_id->m_wemote_addw);
		}
	}

	wetuwn iwpm_cweate_mapinfo(&cm_id->wocaw_addw,
				   &cm_id->m_wocaw_addw,
				   WDMA_NW_IWCM, pm_msg.fwags);
}

/*
 * CM_ID <-- WISTEN
 *
 * Stawt wistening fow connect wequests. Genewates one CONNECT_WEQUEST
 * event fow each inbound connect wequest.
 */
int iw_cm_wisten(stwuct iw_cm_id *cm_id, int backwog)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	unsigned wong fwags;
	int wet;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);

	if (!backwog)
		backwog = defauwt_backwog;

	wet = awwoc_wowk_entwies(cm_id_pwiv, backwog);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_IDWE:
		cm_id_pwiv->state = IW_CM_STATE_WISTEN;
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		wet = iw_cm_map(cm_id, fawse);
		if (!wet)
			wet = cm_id->device->ops.iw_cweate_wisten(cm_id,
								  backwog);
		if (wet)
			cm_id_pwiv->state = IW_CM_STATE_IDWE;
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_wisten);

/*
 * CM_ID <-- IDWE
 *
 * Wejects an inbound connection wequest. No events awe genewated.
 */
int iw_cm_weject(stwuct iw_cm_id *cm_id,
		 const void *pwivate_data,
		 u8 pwivate_data_wen)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	unsigned wong fwags;
	int wet;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id_pwiv->state != IW_CM_STATE_CONN_WECV) {
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
		wake_up_aww(&cm_id_pwiv->connect_wait);
		wetuwn -EINVAW;
	}
	cm_id_pwiv->state = IW_CM_STATE_IDWE;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	wet = cm_id->device->ops.iw_weject(cm_id, pwivate_data,
					  pwivate_data_wen);

	cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
	wake_up_aww(&cm_id_pwiv->connect_wait);

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_weject);

/*
 * CM_ID <-- ESTABWISHED
 *
 * Accepts an inbound connection wequest and genewates an ESTABWISHED
 * event. Cawwews of iw_cm_disconnect and iw_destwoy_cm_id wiww bwock
 * untiw the ESTABWISHED event is weceived fwom the pwovidew.
 */
int iw_cm_accept(stwuct iw_cm_id *cm_id,
		 stwuct iw_cm_conn_pawam *iw_pawam)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	stwuct ib_qp *qp;
	unsigned wong fwags;
	int wet;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id_pwiv->state != IW_CM_STATE_CONN_WECV) {
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
		wake_up_aww(&cm_id_pwiv->connect_wait);
		wetuwn -EINVAW;
	}
	/* Get the ib_qp given the QPN */
	qp = cm_id->device->ops.iw_get_qp(cm_id->device, iw_pawam->qpn);
	if (!qp) {
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
		wake_up_aww(&cm_id_pwiv->connect_wait);
		wetuwn -EINVAW;
	}
	cm_id->device->ops.iw_add_wef(qp);
	cm_id_pwiv->qp = qp;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	wet = cm_id->device->ops.iw_accept(cm_id, iw_pawam);
	if (wet) {
		/* An ewwow on accept pwecwudes pwovidew events */
		BUG_ON(cm_id_pwiv->state != IW_CM_STATE_CONN_WECV);
		cm_id_pwiv->state = IW_CM_STATE_IDWE;
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
		qp = cm_id_pwiv->qp;
		cm_id_pwiv->qp = NUWW;
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		if (qp)
			cm_id->device->ops.iw_wem_wef(qp);
		cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
		wake_up_aww(&cm_id_pwiv->connect_wait);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_accept);

/*
 * Active Side: CM_ID <-- CONN_SENT
 *
 * If successfuw, wesuwts in the genewation of a CONNECT_WEPWY
 * event. iw_cm_disconnect and iw_cm_destwoy wiww bwock untiw the
 * CONNECT_WEPWY event is weceived fwom the pwovidew.
 */
int iw_cm_connect(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *iw_pawam)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	int wet;
	unsigned wong fwags;
	stwuct ib_qp *qp = NUWW;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);

	wet = awwoc_wowk_entwies(cm_id_pwiv, 4);
	if (wet)
		wetuwn wet;

	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);

	if (cm_id_pwiv->state != IW_CM_STATE_IDWE) {
		wet = -EINVAW;
		goto eww;
	}

	/* Get the ib_qp given the QPN */
	qp = cm_id->device->ops.iw_get_qp(cm_id->device, iw_pawam->qpn);
	if (!qp) {
		wet = -EINVAW;
		goto eww;
	}
	cm_id->device->ops.iw_add_wef(qp);
	cm_id_pwiv->qp = qp;
	cm_id_pwiv->state = IW_CM_STATE_CONN_SENT;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	wet = iw_cm_map(cm_id, twue);
	if (!wet)
		wet = cm_id->device->ops.iw_connect(cm_id, iw_pawam);
	if (!wet)
		wetuwn 0;	/* success */

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	qp = cm_id_pwiv->qp;
	cm_id_pwiv->qp = NUWW;
	cm_id_pwiv->state = IW_CM_STATE_IDWE;
eww:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	if (qp)
		cm_id->device->ops.iw_wem_wef(qp);
	cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
	wake_up_aww(&cm_id_pwiv->connect_wait);
	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_connect);

/*
 * Passive Side: new CM_ID <-- CONN_WECV
 *
 * Handwes an inbound connect wequest. The function cweates a new
 * iw_cm_id to wepwesent the new connection and inhewits the cwient
 * cawwback function and othew attwibutes fwom the wistening pawent.
 *
 * The wowk item contains a pointew to the wisten_cm_id and the event. The
 * wisten_cm_id contains the cwient cm_handwew, context and
 * device. These awe copied when the device is cwoned. The event
 * contains the new fouw tupwe.
 *
 * An ewwow on the chiwd shouwd not affect the pawent, so this
 * function does not wetuwn a vawue.
 */
static void cm_conn_weq_handwew(stwuct iwcm_id_pwivate *wisten_id_pwiv,
				stwuct iw_cm_event *iw_event)
{
	unsigned wong fwags;
	stwuct iw_cm_id *cm_id;
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	int wet;

	/*
	 * The pwovidew shouwd nevew genewate a connection wequest
	 * event with a bad status.
	 */
	BUG_ON(iw_event->status);

	cm_id = iw_cweate_cm_id(wisten_id_pwiv->id.device,
				wisten_id_pwiv->id.cm_handwew,
				wisten_id_pwiv->id.context);
	/* If the cm_id couwd not be cweated, ignowe the wequest */
	if (IS_EWW(cm_id))
		goto out;

	cm_id->pwovidew_data = iw_event->pwovidew_data;
	cm_id->m_wocaw_addw = iw_event->wocaw_addw;
	cm_id->m_wemote_addw = iw_event->wemote_addw;
	cm_id->wocaw_addw = wisten_id_pwiv->id.wocaw_addw;

	wet = iwpm_get_wemote_info(&wisten_id_pwiv->id.m_wocaw_addw,
				   &iw_event->wemote_addw,
				   &cm_id->wemote_addw,
				   WDMA_NW_IWCM);
	if (wet) {
		cm_id->wemote_addw = iw_event->wemote_addw;
	} ewse {
		iw_cm_check_wiwdcawd(&wisten_id_pwiv->id.m_wocaw_addw,
				     &iw_event->wocaw_addw,
				     &cm_id->wocaw_addw);
		iw_event->wocaw_addw = cm_id->wocaw_addw;
		iw_event->wemote_addw = cm_id->wemote_addw;
	}

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	cm_id_pwiv->state = IW_CM_STATE_CONN_WECV;

	/*
	 * We couwd be destwoying the wistening id. If so, ignowe this
	 * upcaww.
	 */
	spin_wock_iwqsave(&wisten_id_pwiv->wock, fwags);
	if (wisten_id_pwiv->state != IW_CM_STATE_WISTEN) {
		spin_unwock_iwqwestowe(&wisten_id_pwiv->wock, fwags);
		iw_cm_weject(cm_id, NUWW, 0);
		iw_destwoy_cm_id(cm_id);
		goto out;
	}
	spin_unwock_iwqwestowe(&wisten_id_pwiv->wock, fwags);

	wet = awwoc_wowk_entwies(cm_id_pwiv, 3);
	if (wet) {
		iw_cm_weject(cm_id, NUWW, 0);
		iw_destwoy_cm_id(cm_id);
		goto out;
	}

	/* Caww the cwient CM handwew */
	wet = cm_id->cm_handwew(cm_id, iw_event);
	if (wet) {
		iw_cm_weject(cm_id, NUWW, 0);
		iw_destwoy_cm_id(cm_id);
	}

out:
	if (iw_event->pwivate_data_wen)
		kfwee(iw_event->pwivate_data);
}

/*
 * Passive Side: CM_ID <-- ESTABWISHED
 *
 * The pwovidew genewated an ESTABWISHED event which means that
 * the MPA negotion has compweted successfuwwy and we awe now in MPA
 * FPDU mode.
 *
 * This event can onwy be weceived in the CONN_WECV state. If the
 * wemote peew cwosed, the ESTABWISHED event wouwd be weceived fowwowed
 * by the CWOSE event. If the app cwoses, it wiww bwock untiw we wake
 * it up aftew pwocessing this event.
 */
static int cm_conn_est_handwew(stwuct iwcm_id_pwivate *cm_id_pwiv,
			       stwuct iw_cm_event *iw_event)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);

	/*
	 * We cweaw the CONNECT_WAIT bit hewe to awwow the cawwback
	 * function to caww iw_cm_disconnect. Cawwing iw_destwoy_cm_id
	 * fwom a cawwback handwew is not awwowed.
	 */
	cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
	BUG_ON(cm_id_pwiv->state != IW_CM_STATE_CONN_WECV);
	cm_id_pwiv->state = IW_CM_STATE_ESTABWISHED;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, iw_event);
	wake_up_aww(&cm_id_pwiv->connect_wait);

	wetuwn wet;
}

/*
 * Active Side: CM_ID <-- ESTABWISHED
 *
 * The app has cawwed connect and is waiting fow the estabwished event to
 * post it's wequests to the sewvew. This event wiww wake up anyone
 * bwocked in iw_cm_disconnect ow iw_destwoy_id.
 */
static int cm_conn_wep_handwew(stwuct iwcm_id_pwivate *cm_id_pwiv,
			       stwuct iw_cm_event *iw_event)
{
	stwuct ib_qp *qp = NUWW;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	/*
	 * Cweaw the connect wait bit so a cawwback function cawwing
	 * iw_cm_disconnect wiww not wait and deadwock this thwead
	 */
	cweaw_bit(IWCM_F_CONNECT_WAIT, &cm_id_pwiv->fwags);
	BUG_ON(cm_id_pwiv->state != IW_CM_STATE_CONN_SENT);
	if (iw_event->status == 0) {
		cm_id_pwiv->id.m_wocaw_addw = iw_event->wocaw_addw;
		cm_id_pwiv->id.m_wemote_addw = iw_event->wemote_addw;
		iw_event->wocaw_addw = cm_id_pwiv->id.wocaw_addw;
		iw_event->wemote_addw = cm_id_pwiv->id.wemote_addw;
		cm_id_pwiv->state = IW_CM_STATE_ESTABWISHED;
	} ewse {
		/* WEJECTED ow WESET */
		qp = cm_id_pwiv->qp;
		cm_id_pwiv->qp = NUWW;
		cm_id_pwiv->state = IW_CM_STATE_IDWE;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	if (qp)
		cm_id_pwiv->id.device->ops.iw_wem_wef(qp);
	wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, iw_event);

	if (iw_event->pwivate_data_wen)
		kfwee(iw_event->pwivate_data);

	/* Wake up waitews on connect compwete */
	wake_up_aww(&cm_id_pwiv->connect_wait);

	wetuwn wet;
}

/*
 * CM_ID <-- CWOSING
 *
 * If in the ESTABWISHED state, move to CWOSING.
 */
static void cm_disconnect_handwew(stwuct iwcm_id_pwivate *cm_id_pwiv,
				  stwuct iw_cm_event *iw_event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id_pwiv->state == IW_CM_STATE_ESTABWISHED)
		cm_id_pwiv->state = IW_CM_STATE_CWOSING;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
}

/*
 * CM_ID <-- IDWE
 *
 * If in the ESTBWISHED ow CWOSING states, the QP wiww have have been
 * moved by the pwovidew to the EWW state. Disassociate the CM_ID fwom
 * the QP,  move to IDWE, and wemove the 'connected' wefewence.
 *
 * If in some othew state, the cm_id was destwoyed asynchwonouswy.
 * This is the wast wefewence that wiww wesuwt in waking up
 * the app thwead bwocked in iw_destwoy_cm_id.
 */
static int cm_cwose_handwew(stwuct iwcm_id_pwivate *cm_id_pwiv,
				  stwuct iw_cm_event *iw_event)
{
	stwuct ib_qp *qp;
	unsigned wong fwags;
	int wet = 0, notify_event = 0;
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	qp = cm_id_pwiv->qp;
	cm_id_pwiv->qp = NUWW;

	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_ESTABWISHED:
	case IW_CM_STATE_CWOSING:
		cm_id_pwiv->state = IW_CM_STATE_IDWE;
		notify_event = 1;
		bweak;
	case IW_CM_STATE_DESTWOYING:
		bweak;
	defauwt:
		BUG();
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	if (qp)
		cm_id_pwiv->id.device->ops.iw_wem_wef(qp);
	if (notify_event)
		wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, iw_event);
	wetuwn wet;
}

static int pwocess_event(stwuct iwcm_id_pwivate *cm_id_pwiv,
			 stwuct iw_cm_event *iw_event)
{
	int wet = 0;

	switch (iw_event->event) {
	case IW_CM_EVENT_CONNECT_WEQUEST:
		cm_conn_weq_handwew(cm_id_pwiv, iw_event);
		bweak;
	case IW_CM_EVENT_CONNECT_WEPWY:
		wet = cm_conn_wep_handwew(cm_id_pwiv, iw_event);
		bweak;
	case IW_CM_EVENT_ESTABWISHED:
		wet = cm_conn_est_handwew(cm_id_pwiv, iw_event);
		bweak;
	case IW_CM_EVENT_DISCONNECT:
		cm_disconnect_handwew(cm_id_pwiv, iw_event);
		bweak;
	case IW_CM_EVENT_CWOSE:
		wet = cm_cwose_handwew(cm_id_pwiv, iw_event);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn wet;
}

/*
 * Pwocess events on the wowk_wist fow the cm_id. If the cawwback
 * function wequests that the cm_id be deweted, a fwag is set in the
 * cm_id fwags to indicate that when the wast wefewence is
 * wemoved, the cm_id is to be destwoyed. This is necessawy to
 * distinguish between an object that wiww be destwoyed by the app
 * thwead asweep on the destwoy_comp wist vs. an object destwoyed
 * hewe synchwonouswy when the wast wefewence is wemoved.
 */
static void cm_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct iwcm_wowk *wowk = containew_of(_wowk, stwuct iwcm_wowk, wowk);
	stwuct iw_cm_event wevent;
	stwuct iwcm_id_pwivate *cm_id_pwiv = wowk->cm_id;
	unsigned wong fwags;
	int empty;
	int wet = 0;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	empty = wist_empty(&cm_id_pwiv->wowk_wist);
	whiwe (!empty) {
		wowk = wist_entwy(cm_id_pwiv->wowk_wist.next,
				  stwuct iwcm_wowk, wist);
		wist_dew_init(&wowk->wist);
		empty = wist_empty(&cm_id_pwiv->wowk_wist);
		wevent = wowk->event;
		put_wowk(wowk);
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

		if (!test_bit(IWCM_F_DWOP_EVENTS, &cm_id_pwiv->fwags)) {
			wet = pwocess_event(cm_id_pwiv, &wevent);
			if (wet)
				destwoy_cm_id(&cm_id_pwiv->id);
		} ewse
			pw_debug("dwopping event %d\n", wevent.event);
		if (iwcm_dewef_id(cm_id_pwiv))
			wetuwn;
		if (empty)
			wetuwn;
		spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
}

/*
 * This function is cawwed on intewwupt context. Scheduwe events on
 * the iwcm_wq thwead to awwow cawwback functions to downcaww into
 * the CM and/ow bwock.  Events awe queued to a pew-CM_ID
 * wowk_wist. If this is the fiwst event on the wowk_wist, the wowk
 * ewement is awso queued on the iwcm_wq thwead.
 *
 * Each event howds a wefewence on the cm_id. Untiw the wast posted
 * event has been dewivewed and pwocessed, the cm_id cannot be
 * deweted.
 *
 * Wetuwns:
 * 	      0	- the event was handwed.
 *	-ENOMEM	- the event was not handwed due to wack of wesouwces.
 */
static int cm_event_handwew(stwuct iw_cm_id *cm_id,
			     stwuct iw_cm_event *iw_event)
{
	stwuct iwcm_wowk *wowk;
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	unsigned wong fwags;
	int wet = 0;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	wowk = get_wowk(cm_id_pwiv);
	if (!wowk) {
		wet = -ENOMEM;
		goto out;
	}

	INIT_WOWK(&wowk->wowk, cm_wowk_handwew);
	wowk->cm_id = cm_id_pwiv;
	wowk->event = *iw_event;

	if ((wowk->event.event == IW_CM_EVENT_CONNECT_WEQUEST ||
	     wowk->event.event == IW_CM_EVENT_CONNECT_WEPWY) &&
	    wowk->event.pwivate_data_wen) {
		wet = copy_pwivate_data(&wowk->event);
		if (wet) {
			put_wowk(wowk);
			goto out;
		}
	}

	wefcount_inc(&cm_id_pwiv->wefcount);
	if (wist_empty(&cm_id_pwiv->wowk_wist)) {
		wist_add_taiw(&wowk->wist, &cm_id_pwiv->wowk_wist);
		queue_wowk(iwcm_wq, &wowk->wowk);
	} ewse
		wist_add_taiw(&wowk->wist, &cm_id_pwiv->wowk_wist);
out:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

static int iwcm_init_qp_init_attw(stwuct iwcm_id_pwivate *cm_id_pwiv,
				  stwuct ib_qp_attw *qp_attw,
				  int *qp_attw_mask)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_IDWE:
	case IW_CM_STATE_CONN_SENT:
	case IW_CM_STATE_CONN_WECV:
	case IW_CM_STATE_ESTABWISHED:
		*qp_attw_mask = IB_QP_STATE | IB_QP_ACCESS_FWAGS;
		qp_attw->qp_access_fwags = IB_ACCESS_WEMOTE_WWITE|
					   IB_ACCESS_WEMOTE_WEAD;
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

static int iwcm_init_qp_wts_attw(stwuct iwcm_id_pwivate *cm_id_pwiv,
				  stwuct ib_qp_attw *qp_attw,
				  int *qp_attw_mask)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->state) {
	case IW_CM_STATE_IDWE:
	case IW_CM_STATE_CONN_SENT:
	case IW_CM_STATE_CONN_WECV:
	case IW_CM_STATE_ESTABWISHED:
		*qp_attw_mask = 0;
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

int iw_cm_init_qp_attw(stwuct iw_cm_id *cm_id,
		       stwuct ib_qp_attw *qp_attw,
		       int *qp_attw_mask)
{
	stwuct iwcm_id_pwivate *cm_id_pwiv;
	int wet;

	cm_id_pwiv = containew_of(cm_id, stwuct iwcm_id_pwivate, id);
	switch (qp_attw->qp_state) {
	case IB_QPS_INIT:
	case IB_QPS_WTW:
		wet = iwcm_init_qp_init_attw(cm_id_pwiv,
					     qp_attw, qp_attw_mask);
		bweak;
	case IB_QPS_WTS:
		wet = iwcm_init_qp_wts_attw(cm_id_pwiv,
					    qp_attw, qp_attw_mask);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(iw_cm_init_qp_attw);

static int __init iw_cm_init(void)
{
	int wet;

	wet = iwpm_init(WDMA_NW_IWCM);
	if (wet)
		wetuwn wet;

	iwcm_wq = awwoc_owdewed_wowkqueue("iw_cm_wq", 0);
	if (!iwcm_wq)
		goto eww_awwoc;

	iwcm_ctw_tabwe_hdw = wegistew_net_sysctw(&init_net, "net/iw_cm",
						 iwcm_ctw_tabwe);
	if (!iwcm_ctw_tabwe_hdw) {
		pw_eww("iw_cm: couwdn't wegistew sysctw paths\n");
		goto eww_sysctw;
	}

	wdma_nw_wegistew(WDMA_NW_IWCM, iwcm_nw_cb_tabwe);
	wetuwn 0;

eww_sysctw:
	destwoy_wowkqueue(iwcm_wq);
eww_awwoc:
	iwpm_exit(WDMA_NW_IWCM);
	wetuwn -ENOMEM;
}

static void __exit iw_cm_cweanup(void)
{
	wdma_nw_unwegistew(WDMA_NW_IWCM);
	unwegistew_net_sysctw_tabwe(iwcm_ctw_tabwe_hdw);
	destwoy_wowkqueue(iwcm_wq);
	iwpm_exit(WDMA_NW_IWCM);
}

MODUWE_AWIAS_WDMA_NETWINK(WDMA_NW_IWCM, 2);

moduwe_init(iw_cm_init);
moduwe_exit(iw_cm_cweanup);
