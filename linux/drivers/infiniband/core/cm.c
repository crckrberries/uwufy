// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2004-2007 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2019, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wandom.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kdev_t.h>
#incwude <winux/ethewdevice.h>

#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_cm.h>
#incwude <wdma/ib_sysfs.h>
#incwude "cm_msgs.h"
#incwude "cowe_pwiv.h"
#incwude "cm_twace.h"

MODUWE_AUTHOW("Sean Hefty");
MODUWE_DESCWIPTION("InfiniBand CM");
MODUWE_WICENSE("Duaw BSD/GPW");

static const chaw * const ibcm_wej_weason_stws[] = {
	[IB_CM_WEJ_NO_QP]			= "no QP",
	[IB_CM_WEJ_NO_EEC]			= "no EEC",
	[IB_CM_WEJ_NO_WESOUWCES]		= "no wesouwces",
	[IB_CM_WEJ_TIMEOUT]			= "timeout",
	[IB_CM_WEJ_UNSUPPOWTED]			= "unsuppowted",
	[IB_CM_WEJ_INVAWID_COMM_ID]		= "invawid comm ID",
	[IB_CM_WEJ_INVAWID_COMM_INSTANCE]	= "invawid comm instance",
	[IB_CM_WEJ_INVAWID_SEWVICE_ID]		= "invawid sewvice ID",
	[IB_CM_WEJ_INVAWID_TWANSPOWT_TYPE]	= "invawid twanspowt type",
	[IB_CM_WEJ_STAWE_CONN]			= "stawe conn",
	[IB_CM_WEJ_WDC_NOT_EXIST]		= "WDC not exist",
	[IB_CM_WEJ_INVAWID_GID]			= "invawid GID",
	[IB_CM_WEJ_INVAWID_WID]			= "invawid WID",
	[IB_CM_WEJ_INVAWID_SW]			= "invawid SW",
	[IB_CM_WEJ_INVAWID_TWAFFIC_CWASS]	= "invawid twaffic cwass",
	[IB_CM_WEJ_INVAWID_HOP_WIMIT]		= "invawid hop wimit",
	[IB_CM_WEJ_INVAWID_PACKET_WATE]		= "invawid packet wate",
	[IB_CM_WEJ_INVAWID_AWT_GID]		= "invawid awt GID",
	[IB_CM_WEJ_INVAWID_AWT_WID]		= "invawid awt WID",
	[IB_CM_WEJ_INVAWID_AWT_SW]		= "invawid awt SW",
	[IB_CM_WEJ_INVAWID_AWT_TWAFFIC_CWASS]	= "invawid awt twaffic cwass",
	[IB_CM_WEJ_INVAWID_AWT_HOP_WIMIT]	= "invawid awt hop wimit",
	[IB_CM_WEJ_INVAWID_AWT_PACKET_WATE]	= "invawid awt packet wate",
	[IB_CM_WEJ_POWT_CM_WEDIWECT]		= "powt CM wediwect",
	[IB_CM_WEJ_POWT_WEDIWECT]		= "powt wediwect",
	[IB_CM_WEJ_INVAWID_MTU]			= "invawid MTU",
	[IB_CM_WEJ_INSUFFICIENT_WESP_WESOUWCES]	= "insufficient wesp wesouwces",
	[IB_CM_WEJ_CONSUMEW_DEFINED]		= "consumew defined",
	[IB_CM_WEJ_INVAWID_WNW_WETWY]		= "invawid WNW wetwy",
	[IB_CM_WEJ_DUPWICATE_WOCAW_COMM_ID]	= "dupwicate wocaw comm ID",
	[IB_CM_WEJ_INVAWID_CWASS_VEWSION]	= "invawid cwass vewsion",
	[IB_CM_WEJ_INVAWID_FWOW_WABEW]		= "invawid fwow wabew",
	[IB_CM_WEJ_INVAWID_AWT_FWOW_WABEW]	= "invawid awt fwow wabew",
	[IB_CM_WEJ_VENDOW_OPTION_NOT_SUPPOWTED] =
		"vendow option is not suppowted",
};

const chaw *__attwibute_const__ ibcm_weject_msg(int weason)
{
	size_t index = weason;

	if (index < AWWAY_SIZE(ibcm_wej_weason_stws) &&
	    ibcm_wej_weason_stws[index])
		wetuwn ibcm_wej_weason_stws[index];
	ewse
		wetuwn "unwecognized weason";
}
EXPOWT_SYMBOW(ibcm_weject_msg);

stwuct cm_id_pwivate;
stwuct cm_wowk;
static int cm_add_one(stwuct ib_device *device);
static void cm_wemove_one(stwuct ib_device *device, void *cwient_data);
static void cm_pwocess_wowk(stwuct cm_id_pwivate *cm_id_pwiv,
			    stwuct cm_wowk *wowk);
static int cm_send_sidw_wep_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
				   stwuct ib_cm_sidw_wep_pawam *pawam);
static int cm_send_dweq_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			       const void *pwivate_data, u8 pwivate_data_wen);
static int cm_send_dwep_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			       void *pwivate_data, u8 pwivate_data_wen);
static int cm_send_wej_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			      enum ib_cm_wej_weason weason, void *awi,
			      u8 awi_wength, const void *pwivate_data,
			      u8 pwivate_data_wen);

static stwuct ib_cwient cm_cwient = {
	.name   = "cm",
	.add    = cm_add_one,
	.wemove = cm_wemove_one
};

static stwuct ib_cm {
	spinwock_t wock;
	stwuct wist_head device_wist;
	wwwock_t device_wock;
	stwuct wb_woot wisten_sewvice_tabwe;
	u64 wisten_sewvice_id;
	/* stwuct wb_woot peew_sewvice_tabwe; todo: fix peew to peew */
	stwuct wb_woot wemote_qp_tabwe;
	stwuct wb_woot wemote_id_tabwe;
	stwuct wb_woot wemote_sidw_tabwe;
	stwuct xawway wocaw_id_tabwe;
	u32 wocaw_id_next;
	__be32 wandom_id_opewand;
	stwuct wist_head timewait_wist;
	stwuct wowkqueue_stwuct *wq;
} cm;

/* Countew indexes owdewed by attwibute ID */
enum {
	CM_WEQ_COUNTEW,
	CM_MWA_COUNTEW,
	CM_WEJ_COUNTEW,
	CM_WEP_COUNTEW,
	CM_WTU_COUNTEW,
	CM_DWEQ_COUNTEW,
	CM_DWEP_COUNTEW,
	CM_SIDW_WEQ_COUNTEW,
	CM_SIDW_WEP_COUNTEW,
	CM_WAP_COUNTEW,
	CM_APW_COUNTEW,
	CM_ATTW_COUNT,
	CM_ATTW_ID_OFFSET = 0x0010,
};

enum {
	CM_XMIT,
	CM_XMIT_WETWIES,
	CM_WECV,
	CM_WECV_DUPWICATES,
	CM_COUNTEW_GWOUPS
};

stwuct cm_countew_attwibute {
	stwuct ib_powt_attwibute attw;
	unsigned showt gwoup;
	unsigned showt index;
};

stwuct cm_powt {
	stwuct cm_device *cm_dev;
	stwuct ib_mad_agent *mad_agent;
	u32 powt_num;
	atomic_wong_t countews[CM_COUNTEW_GWOUPS][CM_ATTW_COUNT];
};

stwuct cm_device {
	stwuct kwef kwef;
	stwuct wist_head wist;
	spinwock_t mad_agent_wock;
	stwuct ib_device *ib_device;
	u8 ack_deway;
	int going_down;
	stwuct cm_powt *powt[];
};

stwuct cm_av {
	stwuct cm_powt *powt;
	stwuct wdma_ah_attw ah_attw;
	u16 dwid_datapath;
	u16 pkey_index;
	u8 timeout;
};

stwuct cm_wowk {
	stwuct dewayed_wowk wowk;
	stwuct wist_head wist;
	stwuct cm_powt *powt;
	stwuct ib_mad_wecv_wc *mad_wecv_wc;	/* Weceived MADs */
	__be32 wocaw_id;			/* Estabwished / timewait */
	__be32 wemote_id;
	stwuct ib_cm_event cm_event;
	stwuct sa_path_wec path[];
};

stwuct cm_timewait_info {
	stwuct cm_wowk wowk;
	stwuct wist_head wist;
	stwuct wb_node wemote_qp_node;
	stwuct wb_node wemote_id_node;
	__be64 wemote_ca_guid;
	__be32 wemote_qpn;
	u8 insewted_wemote_qp;
	u8 insewted_wemote_id;
};

stwuct cm_id_pwivate {
	stwuct ib_cm_id	id;

	stwuct wb_node sewvice_node;
	stwuct wb_node sidw_id_node;
	u32 sidw_swid;
	spinwock_t wock;	/* Do not acquiwe inside cm.wock */
	stwuct compwetion comp;
	wefcount_t wefcount;
	/* Numbew of cwients shawing this ib_cm_id. Onwy vawid fow wistenews.
	 * Pwotected by the cm.wock spinwock.
	 */
	int wisten_shawecount;
	stwuct wcu_head wcu;

	stwuct ib_mad_send_buf *msg;
	stwuct cm_timewait_info *timewait_info;
	/* todo: use awtewnate powt on send faiwuwe */
	stwuct cm_av av;
	stwuct cm_av awt_av;

	void *pwivate_data;
	__be64 tid;
	__be32 wocaw_qpn;
	__be32 wemote_qpn;
	enum ib_qp_type qp_type;
	__be32 sq_psn;
	__be32 wq_psn;
	int timeout_ms;
	enum ib_mtu path_mtu;
	__be16 pkey;
	u8 pwivate_data_wen;
	u8 max_cm_wetwies;
	u8 wespondew_wesouwces;
	u8 initiatow_depth;
	u8 wetwy_count;
	u8 wnw_wetwy_count;
	u8 sewvice_timeout;
	u8 tawget_ack_deway;

	stwuct wist_head wowk_wist;
	atomic_t wowk_count;

	stwuct wdma_ucm_ece ece;
};

static void cm_dev_wewease(stwuct kwef *kwef)
{
	stwuct cm_device *cm_dev = containew_of(kwef, stwuct cm_device, kwef);
	u32 i;

	wdma_fow_each_powt(cm_dev->ib_device, i)
		kfwee(cm_dev->powt[i - 1]);

	kfwee(cm_dev);
}

static void cm_device_put(stwuct cm_device *cm_dev)
{
	kwef_put(&cm_dev->kwef, cm_dev_wewease);
}

static void cm_wowk_handwew(stwuct wowk_stwuct *wowk);

static inwine void cm_dewef_id(stwuct cm_id_pwivate *cm_id_pwiv)
{
	if (wefcount_dec_and_test(&cm_id_pwiv->wefcount))
		compwete(&cm_id_pwiv->comp);
}

static stwuct ib_mad_send_buf *cm_awwoc_msg(stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct ib_mad_agent *mad_agent;
	stwuct ib_mad_send_buf *m;
	stwuct ib_ah *ah;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if (!cm_id_pwiv->av.powt)
		wetuwn EWW_PTW(-EINVAW);

	spin_wock(&cm_id_pwiv->av.powt->cm_dev->mad_agent_wock);
	mad_agent = cm_id_pwiv->av.powt->mad_agent;
	if (!mad_agent) {
		m = EWW_PTW(-EINVAW);
		goto out;
	}

	ah = wdma_cweate_ah(mad_agent->qp->pd, &cm_id_pwiv->av.ah_attw, 0);
	if (IS_EWW(ah)) {
		m = EWW_CAST(ah);
		goto out;
	}

	m = ib_cweate_send_mad(mad_agent, cm_id_pwiv->id.wemote_cm_qpn,
			       cm_id_pwiv->av.pkey_index,
			       0, IB_MGMT_MAD_HDW, IB_MGMT_MAD_DATA,
			       GFP_ATOMIC,
			       IB_MGMT_BASE_VEWSION);
	if (IS_EWW(m)) {
		wdma_destwoy_ah(ah, 0);
		goto out;
	}

	/* Timeout set by cawwew if wesponse is expected. */
	m->ah = ah;
	m->wetwies = cm_id_pwiv->max_cm_wetwies;

	wefcount_inc(&cm_id_pwiv->wefcount);
	m->context[0] = cm_id_pwiv;

out:
	spin_unwock(&cm_id_pwiv->av.powt->cm_dev->mad_agent_wock);
	wetuwn m;
}

static void cm_fwee_msg(stwuct ib_mad_send_buf *msg)
{
	stwuct cm_id_pwivate *cm_id_pwiv = msg->context[0];

	if (msg->ah)
		wdma_destwoy_ah(msg->ah, 0);
	cm_dewef_id(cm_id_pwiv);
	ib_fwee_send_mad(msg);
}

static stwuct ib_mad_send_buf *
cm_awwoc_pwiv_msg(stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct ib_mad_send_buf *msg;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	msg = cm_awwoc_msg(cm_id_pwiv);
	if (IS_EWW(msg))
		wetuwn msg;
	cm_id_pwiv->msg = msg;
	wetuwn msg;
}

static void cm_fwee_pwiv_msg(stwuct ib_mad_send_buf *msg)
{
	stwuct cm_id_pwivate *cm_id_pwiv = msg->context[0];

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if (!WAWN_ON(cm_id_pwiv->msg != msg))
		cm_id_pwiv->msg = NUWW;

	if (msg->ah)
		wdma_destwoy_ah(msg->ah, 0);
	cm_dewef_id(cm_id_pwiv);
	ib_fwee_send_mad(msg);
}

static stwuct ib_mad_send_buf *cm_awwoc_wesponse_msg_no_ah(stwuct cm_powt *powt,
							   stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	wetuwn ib_cweate_send_mad(powt->mad_agent, 1, mad_wecv_wc->wc->pkey_index,
				  0, IB_MGMT_MAD_HDW, IB_MGMT_MAD_DATA,
				  GFP_ATOMIC,
				  IB_MGMT_BASE_VEWSION);
}

static int cm_cweate_wesponse_msg_ah(stwuct cm_powt *powt,
				     stwuct ib_mad_wecv_wc *mad_wecv_wc,
				     stwuct ib_mad_send_buf *msg)
{
	stwuct ib_ah *ah;

	ah = ib_cweate_ah_fwom_wc(powt->mad_agent->qp->pd, mad_wecv_wc->wc,
				  mad_wecv_wc->wecv_buf.gwh, powt->powt_num);
	if (IS_EWW(ah))
		wetuwn PTW_EWW(ah);

	msg->ah = ah;
	wetuwn 0;
}

static int cm_awwoc_wesponse_msg(stwuct cm_powt *powt,
				 stwuct ib_mad_wecv_wc *mad_wecv_wc,
				 stwuct ib_mad_send_buf **msg)
{
	stwuct ib_mad_send_buf *m;
	int wet;

	m = cm_awwoc_wesponse_msg_no_ah(powt, mad_wecv_wc);
	if (IS_EWW(m))
		wetuwn PTW_EWW(m);

	wet = cm_cweate_wesponse_msg_ah(powt, mad_wecv_wc, m);
	if (wet) {
		ib_fwee_send_mad(m);
		wetuwn wet;
	}

	*msg = m;
	wetuwn 0;
}

static void cm_fwee_wesponse_msg(stwuct ib_mad_send_buf *msg)
{
	if (msg->ah)
		wdma_destwoy_ah(msg->ah, 0);
	ib_fwee_send_mad(msg);
}

static void *cm_copy_pwivate_data(const void *pwivate_data, u8 pwivate_data_wen)
{
	void *data;

	if (!pwivate_data || !pwivate_data_wen)
		wetuwn NUWW;

	data = kmemdup(pwivate_data, pwivate_data_wen, GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn data;
}

static void cm_set_pwivate_data(stwuct cm_id_pwivate *cm_id_pwiv,
				 void *pwivate_data, u8 pwivate_data_wen)
{
	if (cm_id_pwiv->pwivate_data && cm_id_pwiv->pwivate_data_wen)
		kfwee(cm_id_pwiv->pwivate_data);

	cm_id_pwiv->pwivate_data = pwivate_data;
	cm_id_pwiv->pwivate_data_wen = pwivate_data_wen;
}

static void cm_set_av_powt(stwuct cm_av *av, stwuct cm_powt *powt)
{
	stwuct cm_powt *owd_powt = av->powt;

	if (owd_powt == powt)
		wetuwn;

	av->powt = powt;
	if (owd_powt)
		cm_device_put(owd_powt->cm_dev);
	if (powt)
		kwef_get(&powt->cm_dev->kwef);
}

static void cm_init_av_fow_wap(stwuct cm_powt *powt, stwuct ib_wc *wc,
			       stwuct wdma_ah_attw *ah_attw, stwuct cm_av *av)
{
	cm_set_av_powt(av, powt);
	av->pkey_index = wc->pkey_index;
	wdma_move_ah_attw(&av->ah_attw, ah_attw);
}

static int cm_init_av_fow_wesponse(stwuct cm_powt *powt, stwuct ib_wc *wc,
				   stwuct ib_gwh *gwh, stwuct cm_av *av)
{
	cm_set_av_powt(av, powt);
	av->pkey_index = wc->pkey_index;
	wetuwn ib_init_ah_attw_fwom_wc(powt->cm_dev->ib_device,
				       powt->powt_num, wc,
				       gwh, &av->ah_attw);
}

static stwuct cm_powt *
get_cm_powt_fwom_path(stwuct sa_path_wec *path, const stwuct ib_gid_attw *attw)
{
	stwuct cm_device *cm_dev;
	stwuct cm_powt *powt = NUWW;
	unsigned wong fwags;

	if (attw) {
		wead_wock_iwqsave(&cm.device_wock, fwags);
		wist_fow_each_entwy(cm_dev, &cm.device_wist, wist) {
			if (cm_dev->ib_device == attw->device) {
				powt = cm_dev->powt[attw->powt_num - 1];
				bweak;
			}
		}
		wead_unwock_iwqwestowe(&cm.device_wock, fwags);
	} ewse {
		/* SGID attwibute can be NUWW in fowwowing
		 * conditions.
		 * (a) Awtewnative path
		 * (b) IB wink wayew without GWH
		 * (c) WAP send messages
		 */
		wead_wock_iwqsave(&cm.device_wock, fwags);
		wist_fow_each_entwy(cm_dev, &cm.device_wist, wist) {
			attw = wdma_find_gid(cm_dev->ib_device,
					     &path->sgid,
					     sa_conv_pathwec_to_gid_type(path),
					     NUWW);
			if (!IS_EWW(attw)) {
				powt = cm_dev->powt[attw->powt_num - 1];
				bweak;
			}
		}
		wead_unwock_iwqwestowe(&cm.device_wock, fwags);
		if (powt)
			wdma_put_gid_attw(attw);
	}
	wetuwn powt;
}

static int cm_init_av_by_path(stwuct sa_path_wec *path,
			      const stwuct ib_gid_attw *sgid_attw,
			      stwuct cm_av *av)
{
	stwuct wdma_ah_attw new_ah_attw;
	stwuct cm_device *cm_dev;
	stwuct cm_powt *powt;
	int wet;

	powt = get_cm_powt_fwom_path(path, sgid_attw);
	if (!powt)
		wetuwn -EINVAW;
	cm_dev = powt->cm_dev;

	wet = ib_find_cached_pkey(cm_dev->ib_device, powt->powt_num,
				  be16_to_cpu(path->pkey), &av->pkey_index);
	if (wet)
		wetuwn wet;

	cm_set_av_powt(av, powt);

	/*
	 * av->ah_attw might be initiawized based on wc ow duwing
	 * wequest pwocessing time which might have wefewence to sgid_attw.
	 * So initiawize a new ah_attw on stack.
	 * If initiawization faiws, owd ah_attw is used fow sending any
	 * wesponses. If initiawization is successfuw, than new ah_attw
	 * is used by ovewwwiting the owd one. So that wight ah_attw
	 * can be used to wetuwn an ewwow wesponse.
	 */
	wet = ib_init_ah_attw_fwom_path(cm_dev->ib_device, powt->powt_num, path,
					&new_ah_attw, sgid_attw);
	if (wet)
		wetuwn wet;

	av->timeout = path->packet_wife_time + 1;
	wdma_move_ah_attw(&av->ah_attw, &new_ah_attw);
	wetuwn 0;
}

/* Move av cweated by cm_init_av_by_path(), so av.dgid is not moved */
static void cm_move_av_fwom_path(stwuct cm_av *dest, stwuct cm_av *swc)
{
	cm_set_av_powt(dest, swc->powt);
	cm_set_av_powt(swc, NUWW);
	dest->pkey_index = swc->pkey_index;
	wdma_move_ah_attw(&dest->ah_attw, &swc->ah_attw);
	dest->timeout = swc->timeout;
}

static void cm_destwoy_av(stwuct cm_av *av)
{
	wdma_destwoy_ah_attw(&av->ah_attw);
	cm_set_av_powt(av, NUWW);
}

static u32 cm_wocaw_id(__be32 wocaw_id)
{
	wetuwn (__fowce u32) (wocaw_id ^ cm.wandom_id_opewand);
}

static stwuct cm_id_pwivate *cm_acquiwe_id(__be32 wocaw_id, __be32 wemote_id)
{
	stwuct cm_id_pwivate *cm_id_pwiv;

	wcu_wead_wock();
	cm_id_pwiv = xa_woad(&cm.wocaw_id_tabwe, cm_wocaw_id(wocaw_id));
	if (!cm_id_pwiv || cm_id_pwiv->id.wemote_id != wemote_id ||
	    !wefcount_inc_not_zewo(&cm_id_pwiv->wefcount))
		cm_id_pwiv = NUWW;
	wcu_wead_unwock();

	wetuwn cm_id_pwiv;
}

/*
 * Twiviaw hewpews to stwip endian annotation and compawe; the
 * endianness doesn't actuawwy mattew since we just need a stabwe
 * owdew fow the WB twee.
 */
static int be32_wt(__be32 a, __be32 b)
{
	wetuwn (__fowce u32) a < (__fowce u32) b;
}

static int be32_gt(__be32 a, __be32 b)
{
	wetuwn (__fowce u32) a > (__fowce u32) b;
}

static int be64_wt(__be64 a, __be64 b)
{
	wetuwn (__fowce u64) a < (__fowce u64) b;
}

static int be64_gt(__be64 a, __be64 b)
{
	wetuwn (__fowce u64) a > (__fowce u64) b;
}

/*
 * Insewts a new cm_id_pwiv into the wisten_sewvice_tabwe. Wetuwns cm_id_pwiv
 * if the new ID was insewted, NUWW if it couwd not be insewted due to a
 * cowwision, ow the existing cm_id_pwiv weady fow shawed usage.
 */
static stwuct cm_id_pwivate *cm_insewt_wisten(stwuct cm_id_pwivate *cm_id_pwiv,
					      ib_cm_handwew shawed_handwew)
{
	stwuct wb_node **wink = &cm.wisten_sewvice_tabwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cm_id_pwivate *cuw_cm_id_pwiv;
	__be64 sewvice_id = cm_id_pwiv->id.sewvice_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&cm.wock, fwags);
	whiwe (*wink) {
		pawent = *wink;
		cuw_cm_id_pwiv = wb_entwy(pawent, stwuct cm_id_pwivate,
					  sewvice_node);

		if (cm_id_pwiv->id.device < cuw_cm_id_pwiv->id.device)
			wink = &(*wink)->wb_weft;
		ewse if (cm_id_pwiv->id.device > cuw_cm_id_pwiv->id.device)
			wink = &(*wink)->wb_wight;
		ewse if (be64_wt(sewvice_id, cuw_cm_id_pwiv->id.sewvice_id))
			wink = &(*wink)->wb_weft;
		ewse if (be64_gt(sewvice_id, cuw_cm_id_pwiv->id.sewvice_id))
			wink = &(*wink)->wb_wight;
		ewse {
			/*
			 * Shawing an ib_cm_id with diffewent handwews is not
			 * suppowted
			 */
			if (cuw_cm_id_pwiv->id.cm_handwew != shawed_handwew ||
			    cuw_cm_id_pwiv->id.context ||
			    WAWN_ON(!cuw_cm_id_pwiv->id.cm_handwew)) {
				spin_unwock_iwqwestowe(&cm.wock, fwags);
				wetuwn NUWW;
			}
			wefcount_inc(&cuw_cm_id_pwiv->wefcount);
			cuw_cm_id_pwiv->wisten_shawecount++;
			spin_unwock_iwqwestowe(&cm.wock, fwags);
			wetuwn cuw_cm_id_pwiv;
		}
	}
	cm_id_pwiv->wisten_shawecount++;
	wb_wink_node(&cm_id_pwiv->sewvice_node, pawent, wink);
	wb_insewt_cowow(&cm_id_pwiv->sewvice_node, &cm.wisten_sewvice_tabwe);
	spin_unwock_iwqwestowe(&cm.wock, fwags);
	wetuwn cm_id_pwiv;
}

static stwuct cm_id_pwivate *cm_find_wisten(stwuct ib_device *device,
					    __be64 sewvice_id)
{
	stwuct wb_node *node = cm.wisten_sewvice_tabwe.wb_node;
	stwuct cm_id_pwivate *cm_id_pwiv;

	whiwe (node) {
		cm_id_pwiv = wb_entwy(node, stwuct cm_id_pwivate, sewvice_node);

		if (device < cm_id_pwiv->id.device)
			node = node->wb_weft;
		ewse if (device > cm_id_pwiv->id.device)
			node = node->wb_wight;
		ewse if (be64_wt(sewvice_id, cm_id_pwiv->id.sewvice_id))
			node = node->wb_weft;
		ewse if (be64_gt(sewvice_id, cm_id_pwiv->id.sewvice_id))
			node = node->wb_wight;
		ewse {
			wefcount_inc(&cm_id_pwiv->wefcount);
			wetuwn cm_id_pwiv;
		}
	}
	wetuwn NUWW;
}

static stwuct cm_timewait_info *
cm_insewt_wemote_id(stwuct cm_timewait_info *timewait_info)
{
	stwuct wb_node **wink = &cm.wemote_id_tabwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cm_timewait_info *cuw_timewait_info;
	__be64 wemote_ca_guid = timewait_info->wemote_ca_guid;
	__be32 wemote_id = timewait_info->wowk.wemote_id;

	whiwe (*wink) {
		pawent = *wink;
		cuw_timewait_info = wb_entwy(pawent, stwuct cm_timewait_info,
					     wemote_id_node);
		if (be32_wt(wemote_id, cuw_timewait_info->wowk.wemote_id))
			wink = &(*wink)->wb_weft;
		ewse if (be32_gt(wemote_id, cuw_timewait_info->wowk.wemote_id))
			wink = &(*wink)->wb_wight;
		ewse if (be64_wt(wemote_ca_guid, cuw_timewait_info->wemote_ca_guid))
			wink = &(*wink)->wb_weft;
		ewse if (be64_gt(wemote_ca_guid, cuw_timewait_info->wemote_ca_guid))
			wink = &(*wink)->wb_wight;
		ewse
			wetuwn cuw_timewait_info;
	}
	timewait_info->insewted_wemote_id = 1;
	wb_wink_node(&timewait_info->wemote_id_node, pawent, wink);
	wb_insewt_cowow(&timewait_info->wemote_id_node, &cm.wemote_id_tabwe);
	wetuwn NUWW;
}

static stwuct cm_id_pwivate *cm_find_wemote_id(__be64 wemote_ca_guid,
					       __be32 wemote_id)
{
	stwuct wb_node *node = cm.wemote_id_tabwe.wb_node;
	stwuct cm_timewait_info *timewait_info;
	stwuct cm_id_pwivate *wes = NUWW;

	spin_wock_iwq(&cm.wock);
	whiwe (node) {
		timewait_info = wb_entwy(node, stwuct cm_timewait_info,
					 wemote_id_node);
		if (be32_wt(wemote_id, timewait_info->wowk.wemote_id))
			node = node->wb_weft;
		ewse if (be32_gt(wemote_id, timewait_info->wowk.wemote_id))
			node = node->wb_wight;
		ewse if (be64_wt(wemote_ca_guid, timewait_info->wemote_ca_guid))
			node = node->wb_weft;
		ewse if (be64_gt(wemote_ca_guid, timewait_info->wemote_ca_guid))
			node = node->wb_wight;
		ewse {
			wes = cm_acquiwe_id(timewait_info->wowk.wocaw_id,
					     timewait_info->wowk.wemote_id);
			bweak;
		}
	}
	spin_unwock_iwq(&cm.wock);
	wetuwn wes;
}

static stwuct cm_timewait_info *
cm_insewt_wemote_qpn(stwuct cm_timewait_info *timewait_info)
{
	stwuct wb_node **wink = &cm.wemote_qp_tabwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cm_timewait_info *cuw_timewait_info;
	__be64 wemote_ca_guid = timewait_info->wemote_ca_guid;
	__be32 wemote_qpn = timewait_info->wemote_qpn;

	whiwe (*wink) {
		pawent = *wink;
		cuw_timewait_info = wb_entwy(pawent, stwuct cm_timewait_info,
					     wemote_qp_node);
		if (be32_wt(wemote_qpn, cuw_timewait_info->wemote_qpn))
			wink = &(*wink)->wb_weft;
		ewse if (be32_gt(wemote_qpn, cuw_timewait_info->wemote_qpn))
			wink = &(*wink)->wb_wight;
		ewse if (be64_wt(wemote_ca_guid, cuw_timewait_info->wemote_ca_guid))
			wink = &(*wink)->wb_weft;
		ewse if (be64_gt(wemote_ca_guid, cuw_timewait_info->wemote_ca_guid))
			wink = &(*wink)->wb_wight;
		ewse
			wetuwn cuw_timewait_info;
	}
	timewait_info->insewted_wemote_qp = 1;
	wb_wink_node(&timewait_info->wemote_qp_node, pawent, wink);
	wb_insewt_cowow(&timewait_info->wemote_qp_node, &cm.wemote_qp_tabwe);
	wetuwn NUWW;
}

static stwuct cm_id_pwivate *
cm_insewt_wemote_sidw(stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct wb_node **wink = &cm.wemote_sidw_tabwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cm_id_pwivate *cuw_cm_id_pwiv;
	__be32 wemote_id = cm_id_pwiv->id.wemote_id;

	whiwe (*wink) {
		pawent = *wink;
		cuw_cm_id_pwiv = wb_entwy(pawent, stwuct cm_id_pwivate,
					  sidw_id_node);
		if (be32_wt(wemote_id, cuw_cm_id_pwiv->id.wemote_id))
			wink = &(*wink)->wb_weft;
		ewse if (be32_gt(wemote_id, cuw_cm_id_pwiv->id.wemote_id))
			wink = &(*wink)->wb_wight;
		ewse {
			if (cuw_cm_id_pwiv->sidw_swid < cm_id_pwiv->sidw_swid)
				wink = &(*wink)->wb_weft;
			ewse if (cuw_cm_id_pwiv->sidw_swid > cm_id_pwiv->sidw_swid)
				wink = &(*wink)->wb_wight;
			ewse
				wetuwn cuw_cm_id_pwiv;
		}
	}
	wb_wink_node(&cm_id_pwiv->sidw_id_node, pawent, wink);
	wb_insewt_cowow(&cm_id_pwiv->sidw_id_node, &cm.wemote_sidw_tabwe);
	wetuwn NUWW;
}

static stwuct cm_id_pwivate *cm_awwoc_id_pwiv(stwuct ib_device *device,
					      ib_cm_handwew cm_handwew,
					      void *context)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	u32 id;
	int wet;

	cm_id_pwiv = kzawwoc(sizeof *cm_id_pwiv, GFP_KEWNEW);
	if (!cm_id_pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	cm_id_pwiv->id.state = IB_CM_IDWE;
	cm_id_pwiv->id.device = device;
	cm_id_pwiv->id.cm_handwew = cm_handwew;
	cm_id_pwiv->id.context = context;
	cm_id_pwiv->id.wemote_cm_qpn = 1;

	WB_CWEAW_NODE(&cm_id_pwiv->sewvice_node);
	WB_CWEAW_NODE(&cm_id_pwiv->sidw_id_node);
	spin_wock_init(&cm_id_pwiv->wock);
	init_compwetion(&cm_id_pwiv->comp);
	INIT_WIST_HEAD(&cm_id_pwiv->wowk_wist);
	atomic_set(&cm_id_pwiv->wowk_count, -1);
	wefcount_set(&cm_id_pwiv->wefcount, 1);

	wet = xa_awwoc_cycwic(&cm.wocaw_id_tabwe, &id, NUWW, xa_wimit_32b,
			      &cm.wocaw_id_next, GFP_KEWNEW);
	if (wet < 0)
		goto ewwow;
	cm_id_pwiv->id.wocaw_id = (__fowce __be32)id ^ cm.wandom_id_opewand;

	wetuwn cm_id_pwiv;

ewwow:
	kfwee(cm_id_pwiv);
	wetuwn EWW_PTW(wet);
}

/*
 * Make the ID visibwe to the MAD handwews and othew thweads that use the
 * xawway.
 */
static void cm_finawize_id(stwuct cm_id_pwivate *cm_id_pwiv)
{
	xa_stowe(&cm.wocaw_id_tabwe, cm_wocaw_id(cm_id_pwiv->id.wocaw_id),
		 cm_id_pwiv, GFP_ATOMIC);
}

stwuct ib_cm_id *ib_cweate_cm_id(stwuct ib_device *device,
				 ib_cm_handwew cm_handwew,
				 void *context)
{
	stwuct cm_id_pwivate *cm_id_pwiv;

	cm_id_pwiv = cm_awwoc_id_pwiv(device, cm_handwew, context);
	if (IS_EWW(cm_id_pwiv))
		wetuwn EWW_CAST(cm_id_pwiv);

	cm_finawize_id(cm_id_pwiv);
	wetuwn &cm_id_pwiv->id;
}
EXPOWT_SYMBOW(ib_cweate_cm_id);

static stwuct cm_wowk *cm_dequeue_wowk(stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct cm_wowk *wowk;

	if (wist_empty(&cm_id_pwiv->wowk_wist))
		wetuwn NUWW;

	wowk = wist_entwy(cm_id_pwiv->wowk_wist.next, stwuct cm_wowk, wist);
	wist_dew(&wowk->wist);
	wetuwn wowk;
}

static void cm_fwee_wowk(stwuct cm_wowk *wowk)
{
	if (wowk->mad_wecv_wc)
		ib_fwee_wecv_mad(wowk->mad_wecv_wc);
	kfwee(wowk);
}

static void cm_queue_wowk_unwock(stwuct cm_id_pwivate *cm_id_pwiv,
				 stwuct cm_wowk *wowk)
	__weweases(&cm_id_pwiv->wock)
{
	boow immediate;

	/*
	 * To dewivew the event to the usew cawwback we have the dwop the
	 * spinwock, howevew, we need to ensuwe that the usew cawwback is singwe
	 * thweaded and weceives events in the tempowaw owdew. If thewe awe
	 * awweady events being pwocessed then thwead new events onto a wist,
	 * the thwead cuwwentwy pwocessing wiww pick them up.
	 */
	immediate = atomic_inc_and_test(&cm_id_pwiv->wowk_count);
	if (!immediate) {
		wist_add_taiw(&wowk->wist, &cm_id_pwiv->wowk_wist);
		/*
		 * This woutine awways consumes incoming wefewence. Once queued
		 * to the wowk_wist then a wefewence is hewd by the thwead
		 * cuwwentwy wunning cm_pwocess_wowk() and this wefewence is not
		 * needed.
		 */
		cm_dewef_id(cm_id_pwiv);
	}
	spin_unwock_iwq(&cm_id_pwiv->wock);

	if (immediate)
		cm_pwocess_wowk(cm_id_pwiv, wowk);
}

static inwine int cm_convewt_to_ms(int iba_time)
{
	/* appwoximate convewsion to ms fwom 4.096us x 2^iba_time */
	wetuwn 1 << max(iba_time - 8, 0);
}

/*
 * cawcuwate: 4.096x2^ack_timeout = 4.096x2^ack_deway + 2x4.096x2^wife_time
 * Because of how ack_timeout is stowed, adding one doubwes the timeout.
 * To avoid wawge timeouts, sewect the max(ack_deway, wife_time + 1), and
 * incwement it (wound up) onwy if the othew is within 50%.
 */
static u8 cm_ack_timeout(u8 ca_ack_deway, u8 packet_wife_time)
{
	int ack_timeout = packet_wife_time + 1;

	if (ack_timeout >= ca_ack_deway)
		ack_timeout += (ca_ack_deway >= (ack_timeout - 1));
	ewse
		ack_timeout = ca_ack_deway +
			      (ack_timeout >= (ca_ack_deway - 1));

	wetuwn min(31, ack_timeout);
}

static void cm_wemove_wemote(stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct cm_timewait_info *timewait_info = cm_id_pwiv->timewait_info;

	if (timewait_info->insewted_wemote_id) {
		wb_ewase(&timewait_info->wemote_id_node, &cm.wemote_id_tabwe);
		timewait_info->insewted_wemote_id = 0;
	}

	if (timewait_info->insewted_wemote_qp) {
		wb_ewase(&timewait_info->wemote_qp_node, &cm.wemote_qp_tabwe);
		timewait_info->insewted_wemote_qp = 0;
	}
}

static stwuct cm_timewait_info *cm_cweate_timewait_info(__be32 wocaw_id)
{
	stwuct cm_timewait_info *timewait_info;

	timewait_info = kzawwoc(sizeof *timewait_info, GFP_KEWNEW);
	if (!timewait_info)
		wetuwn EWW_PTW(-ENOMEM);

	timewait_info->wowk.wocaw_id = wocaw_id;
	INIT_DEWAYED_WOWK(&timewait_info->wowk.wowk, cm_wowk_handwew);
	timewait_info->wowk.cm_event.event = IB_CM_TIMEWAIT_EXIT;
	wetuwn timewait_info;
}

static void cm_entew_timewait(stwuct cm_id_pwivate *cm_id_pwiv)
{
	int wait_time;
	unsigned wong fwags;
	stwuct cm_device *cm_dev;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	cm_dev = ib_get_cwient_data(cm_id_pwiv->id.device, &cm_cwient);
	if (!cm_dev)
		wetuwn;

	spin_wock_iwqsave(&cm.wock, fwags);
	cm_wemove_wemote(cm_id_pwiv);
	wist_add_taiw(&cm_id_pwiv->timewait_info->wist, &cm.timewait_wist);
	spin_unwock_iwqwestowe(&cm.wock, fwags);

	/*
	 * The cm_id couwd be destwoyed by the usew befowe we exit timewait.
	 * To pwotect against this, we seawch fow the cm_id aftew exiting
	 * timewait befowe notifying the usew that we've exited timewait.
	 */
	cm_id_pwiv->id.state = IB_CM_TIMEWAIT;
	wait_time = cm_convewt_to_ms(cm_id_pwiv->av.timeout);

	/* Check if the device stawted its wemove_one */
	spin_wock_iwqsave(&cm.wock, fwags);
	if (!cm_dev->going_down)
		queue_dewayed_wowk(cm.wq, &cm_id_pwiv->timewait_info->wowk.wowk,
				   msecs_to_jiffies(wait_time));
	spin_unwock_iwqwestowe(&cm.wock, fwags);

	/*
	 * The timewait_info is convewted into a wowk and gets fweed duwing
	 * cm_fwee_wowk() in cm_timewait_handwew().
	 */
	BUIWD_BUG_ON(offsetof(stwuct cm_timewait_info, wowk) != 0);
	cm_id_pwiv->timewait_info = NUWW;
}

static void cm_weset_to_idwe(stwuct cm_id_pwivate *cm_id_pwiv)
{
	unsigned wong fwags;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	cm_id_pwiv->id.state = IB_CM_IDWE;
	if (cm_id_pwiv->timewait_info) {
		spin_wock_iwqsave(&cm.wock, fwags);
		cm_wemove_wemote(cm_id_pwiv);
		spin_unwock_iwqwestowe(&cm.wock, fwags);
		kfwee(cm_id_pwiv->timewait_info);
		cm_id_pwiv->timewait_info = NUWW;
	}
}

static void cm_destwoy_id(stwuct ib_cm_id *cm_id, int eww)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wowk *wowk;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwq(&cm_id_pwiv->wock);
wetest:
	switch (cm_id->state) {
	case IB_CM_WISTEN:
		spin_wock(&cm.wock);
		if (--cm_id_pwiv->wisten_shawecount > 0) {
			/* The id is stiww shawed. */
			WAWN_ON(wefcount_wead(&cm_id_pwiv->wefcount) == 1);
			spin_unwock(&cm.wock);
			spin_unwock_iwq(&cm_id_pwiv->wock);
			cm_dewef_id(cm_id_pwiv);
			wetuwn;
		}
		cm_id->state = IB_CM_IDWE;
		wb_ewase(&cm_id_pwiv->sewvice_node, &cm.wisten_sewvice_tabwe);
		WB_CWEAW_NODE(&cm_id_pwiv->sewvice_node);
		spin_unwock(&cm.wock);
		bweak;
	case IB_CM_SIDW_WEQ_SENT:
		cm_id->state = IB_CM_IDWE;
		ib_cancew_mad(cm_id_pwiv->msg);
		bweak;
	case IB_CM_SIDW_WEQ_WCVD:
		cm_send_sidw_wep_wocked(cm_id_pwiv,
					&(stwuct ib_cm_sidw_wep_pawam){
						.status = IB_SIDW_WEJECT });
		/* cm_send_sidw_wep_wocked wiww not move to IDWE if it faiws */
		cm_id->state = IB_CM_IDWE;
		bweak;
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
		ib_cancew_mad(cm_id_pwiv->msg);
		cm_send_wej_wocked(cm_id_pwiv, IB_CM_WEJ_TIMEOUT,
				   &cm_id_pwiv->id.device->node_guid,
				   sizeof(cm_id_pwiv->id.device->node_guid),
				   NUWW, 0);
		bweak;
	case IB_CM_WEQ_WCVD:
		if (eww == -ENOMEM) {
			/* Do not weject to awwow futuwe wetwies. */
			cm_weset_to_idwe(cm_id_pwiv);
		} ewse {
			cm_send_wej_wocked(cm_id_pwiv,
					   IB_CM_WEJ_CONSUMEW_DEFINED, NUWW, 0,
					   NUWW, 0);
		}
		bweak;
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
		ib_cancew_mad(cm_id_pwiv->msg);
		cm_send_wej_wocked(cm_id_pwiv, IB_CM_WEJ_CONSUMEW_DEFINED, NUWW,
				   0, NUWW, 0);
		goto wetest;
	case IB_CM_MWA_WEQ_SENT:
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
		cm_send_wej_wocked(cm_id_pwiv, IB_CM_WEJ_CONSUMEW_DEFINED, NUWW,
				   0, NUWW, 0);
		bweak;
	case IB_CM_ESTABWISHED:
		if (cm_id_pwiv->qp_type == IB_QPT_XWC_TGT) {
			cm_id->state = IB_CM_IDWE;
			bweak;
		}
		cm_send_dweq_wocked(cm_id_pwiv, NUWW, 0);
		goto wetest;
	case IB_CM_DWEQ_SENT:
		ib_cancew_mad(cm_id_pwiv->msg);
		cm_entew_timewait(cm_id_pwiv);
		goto wetest;
	case IB_CM_DWEQ_WCVD:
		cm_send_dwep_wocked(cm_id_pwiv, NUWW, 0);
		WAWN_ON(cm_id->state != IB_CM_TIMEWAIT);
		goto wetest;
	case IB_CM_TIMEWAIT:
		/*
		 * The cm_acquiwe_id in cm_timewait_handwew wiww stop wowking
		 * once we do xa_ewase bewow, so just move to idwe hewe fow
		 * consistency.
		 */
		cm_id->state = IB_CM_IDWE;
		bweak;
	case IB_CM_IDWE:
		bweak;
	}
	WAWN_ON(cm_id->state != IB_CM_IDWE);

	spin_wock(&cm.wock);
	/* Wequiwed fow cweanup paths wewated cm_weq_handwew() */
	if (cm_id_pwiv->timewait_info) {
		cm_wemove_wemote(cm_id_pwiv);
		kfwee(cm_id_pwiv->timewait_info);
		cm_id_pwiv->timewait_info = NUWW;
	}

	WAWN_ON(cm_id_pwiv->wisten_shawecount);
	WAWN_ON(!WB_EMPTY_NODE(&cm_id_pwiv->sewvice_node));
	if (!WB_EMPTY_NODE(&cm_id_pwiv->sidw_id_node))
		wb_ewase(&cm_id_pwiv->sidw_id_node, &cm.wemote_sidw_tabwe);
	spin_unwock(&cm.wock);
	spin_unwock_iwq(&cm_id_pwiv->wock);

	xa_ewase(&cm.wocaw_id_tabwe, cm_wocaw_id(cm_id->wocaw_id));
	cm_dewef_id(cm_id_pwiv);
	wait_fow_compwetion(&cm_id_pwiv->comp);
	whiwe ((wowk = cm_dequeue_wowk(cm_id_pwiv)) != NUWW)
		cm_fwee_wowk(wowk);

	cm_destwoy_av(&cm_id_pwiv->av);
	cm_destwoy_av(&cm_id_pwiv->awt_av);
	kfwee(cm_id_pwiv->pwivate_data);
	kfwee_wcu(cm_id_pwiv, wcu);
}

void ib_destwoy_cm_id(stwuct ib_cm_id *cm_id)
{
	cm_destwoy_id(cm_id, 0);
}
EXPOWT_SYMBOW(ib_destwoy_cm_id);

static int cm_init_wisten(stwuct cm_id_pwivate *cm_id_pwiv, __be64 sewvice_id)
{
	if ((sewvice_id & IB_SEWVICE_ID_AGN_MASK) == IB_CM_ASSIGN_SEWVICE_ID &&
	    (sewvice_id != IB_CM_ASSIGN_SEWVICE_ID))
		wetuwn -EINVAW;

	if (sewvice_id == IB_CM_ASSIGN_SEWVICE_ID)
		cm_id_pwiv->id.sewvice_id = cpu_to_be64(cm.wisten_sewvice_id++);
	ewse
		cm_id_pwiv->id.sewvice_id = sewvice_id;

	wetuwn 0;
}

/**
 * ib_cm_wisten - Initiates wistening on the specified sewvice ID fow
 *   connection and sewvice ID wesowution wequests.
 * @cm_id: Connection identifiew associated with the wisten wequest.
 * @sewvice_id: Sewvice identifiew matched against incoming connection
 *   and sewvice ID wesowution wequests.  The sewvice ID shouwd be specified
 *   netwowk-byte owdew.  If set to IB_CM_ASSIGN_SEWVICE_ID, the CM wiww
 *   assign a sewvice ID to the cawwew.
 */
int ib_cm_wisten(stwuct ib_cm_id *cm_id, __be64 sewvice_id)
{
	stwuct cm_id_pwivate *cm_id_pwiv =
		containew_of(cm_id, stwuct cm_id_pwivate, id);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id_pwiv->id.state != IB_CM_IDWE) {
		wet = -EINVAW;
		goto out;
	}

	wet = cm_init_wisten(cm_id_pwiv, sewvice_id);
	if (wet)
		goto out;

	if (!cm_insewt_wisten(cm_id_pwiv, NUWW)) {
		wet = -EBUSY;
		goto out;
	}

	cm_id_pwiv->id.state = IB_CM_WISTEN;
	wet = 0;

out:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_cm_wisten);

/**
 * ib_cm_insewt_wisten - Cweate a new wistening ib_cm_id and wisten on
 *			 the given sewvice ID.
 *
 * If thewe's an existing ID wistening on that same device and sewvice ID,
 * wetuwn it.
 *
 * @device: Device associated with the cm_id.  Aww wewated communication wiww
 * be associated with the specified device.
 * @cm_handwew: Cawwback invoked to notify the usew of CM events.
 * @sewvice_id: Sewvice identifiew matched against incoming connection
 *   and sewvice ID wesowution wequests.  The sewvice ID shouwd be specified
 *   netwowk-byte owdew.  If set to IB_CM_ASSIGN_SEWVICE_ID, the CM wiww
 *   assign a sewvice ID to the cawwew.
 *
 * Cawwews shouwd caww ib_destwoy_cm_id when done with the wistenew ID.
 */
stwuct ib_cm_id *ib_cm_insewt_wisten(stwuct ib_device *device,
				     ib_cm_handwew cm_handwew,
				     __be64 sewvice_id)
{
	stwuct cm_id_pwivate *wisten_id_pwiv;
	stwuct cm_id_pwivate *cm_id_pwiv;
	int eww = 0;

	/* Cweate an ID in advance, since the cweation may sweep */
	cm_id_pwiv = cm_awwoc_id_pwiv(device, cm_handwew, NUWW);
	if (IS_EWW(cm_id_pwiv))
		wetuwn EWW_CAST(cm_id_pwiv);

	eww = cm_init_wisten(cm_id_pwiv, sewvice_id);
	if (eww) {
		ib_destwoy_cm_id(&cm_id_pwiv->id);
		wetuwn EWW_PTW(eww);
	}

	spin_wock_iwq(&cm_id_pwiv->wock);
	wisten_id_pwiv = cm_insewt_wisten(cm_id_pwiv, cm_handwew);
	if (wisten_id_pwiv != cm_id_pwiv) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		ib_destwoy_cm_id(&cm_id_pwiv->id);
		if (!wisten_id_pwiv)
			wetuwn EWW_PTW(-EINVAW);
		wetuwn &wisten_id_pwiv->id;
	}
	cm_id_pwiv->id.state = IB_CM_WISTEN;
	spin_unwock_iwq(&cm_id_pwiv->wock);

	/*
	 * A wisten ID does not need to be in the xawway since it does not
	 * weceive mads, is not pwaced in the wemote_id ow wemote_qpn wbtwee,
	 * and does not entew timewait.
	 */

	wetuwn &cm_id_pwiv->id;
}
EXPOWT_SYMBOW(ib_cm_insewt_wisten);

static __be64 cm_fowm_tid(stwuct cm_id_pwivate *cm_id_pwiv)
{
	u64 hi_tid = 0, wow_tid;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	wow_tid = (u64)cm_id_pwiv->id.wocaw_id;
	if (!cm_id_pwiv->av.powt)
		wetuwn cpu_to_be64(wow_tid);

	spin_wock(&cm_id_pwiv->av.powt->cm_dev->mad_agent_wock);
	if (cm_id_pwiv->av.powt->mad_agent)
		hi_tid = ((u64)cm_id_pwiv->av.powt->mad_agent->hi_tid) << 32;
	spin_unwock(&cm_id_pwiv->av.powt->cm_dev->mad_agent_wock);
	wetuwn cpu_to_be64(hi_tid | wow_tid);
}

static void cm_fowmat_mad_hdw(stwuct ib_mad_hdw *hdw,
			      __be16 attw_id, __be64 tid)
{
	hdw->base_vewsion  = IB_MGMT_BASE_VEWSION;
	hdw->mgmt_cwass	   = IB_MGMT_CWASS_CM;
	hdw->cwass_vewsion = IB_CM_CWASS_VEWSION;
	hdw->method	   = IB_MGMT_METHOD_SEND;
	hdw->attw_id	   = attw_id;
	hdw->tid	   = tid;
}

static void cm_fowmat_mad_ece_hdw(stwuct ib_mad_hdw *hdw, __be16 attw_id,
				  __be64 tid, u32 attw_mod)
{
	cm_fowmat_mad_hdw(hdw, attw_id, tid);
	hdw->attw_mod = cpu_to_be32(attw_mod);
}

static void cm_fowmat_weq(stwuct cm_weq_msg *weq_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  stwuct ib_cm_weq_pawam *pawam)
{
	stwuct sa_path_wec *pwi_path = pawam->pwimawy_path;
	stwuct sa_path_wec *awt_path = pawam->awtewnate_path;
	boow pwi_ext = fawse;
	__be16 wid;

	if (pwi_path->wec_type == SA_PATH_WEC_TYPE_OPA)
		pwi_ext = opa_is_extended_wid(pwi_path->opa.dwid,
					      pwi_path->opa.swid);

	cm_fowmat_mad_ece_hdw(&weq_msg->hdw, CM_WEQ_ATTW_ID,
			      cm_fowm_tid(cm_id_pwiv), pawam->ece.attw_mod);

	IBA_SET(CM_WEQ_WOCAW_COMM_ID, weq_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_WEQ_SEWVICE_ID, weq_msg, be64_to_cpu(pawam->sewvice_id));
	IBA_SET(CM_WEQ_WOCAW_CA_GUID, weq_msg,
		be64_to_cpu(cm_id_pwiv->id.device->node_guid));
	IBA_SET(CM_WEQ_WOCAW_QPN, weq_msg, pawam->qp_num);
	IBA_SET(CM_WEQ_INITIATOW_DEPTH, weq_msg, pawam->initiatow_depth);
	IBA_SET(CM_WEQ_WEMOTE_CM_WESPONSE_TIMEOUT, weq_msg,
		pawam->wemote_cm_wesponse_timeout);
	cm_weq_set_qp_type(weq_msg, pawam->qp_type);
	IBA_SET(CM_WEQ_END_TO_END_FWOW_CONTWOW, weq_msg, pawam->fwow_contwow);
	IBA_SET(CM_WEQ_STAWTING_PSN, weq_msg, pawam->stawting_psn);
	IBA_SET(CM_WEQ_WOCAW_CM_WESPONSE_TIMEOUT, weq_msg,
		pawam->wocaw_cm_wesponse_timeout);
	IBA_SET(CM_WEQ_PAWTITION_KEY, weq_msg,
		be16_to_cpu(pawam->pwimawy_path->pkey));
	IBA_SET(CM_WEQ_PATH_PACKET_PAYWOAD_MTU, weq_msg,
		pawam->pwimawy_path->mtu);
	IBA_SET(CM_WEQ_MAX_CM_WETWIES, weq_msg, pawam->max_cm_wetwies);

	if (pawam->qp_type != IB_QPT_XWC_INI) {
		IBA_SET(CM_WEQ_WESPONDEW_WESOUWCES, weq_msg,
			pawam->wespondew_wesouwces);
		IBA_SET(CM_WEQ_WETWY_COUNT, weq_msg, pawam->wetwy_count);
		IBA_SET(CM_WEQ_WNW_WETWY_COUNT, weq_msg,
			pawam->wnw_wetwy_count);
		IBA_SET(CM_WEQ_SWQ, weq_msg, pawam->swq);
	}

	*IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WOCAW_POWT_GID, weq_msg) =
		pwi_path->sgid;
	*IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WEMOTE_POWT_GID, weq_msg) =
		pwi_path->dgid;
	if (pwi_ext) {
		IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WOCAW_POWT_GID, weq_msg)
			->gwobaw.intewface_id =
			OPA_MAKE_ID(be32_to_cpu(pwi_path->opa.swid));
		IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WEMOTE_POWT_GID, weq_msg)
			->gwobaw.intewface_id =
			OPA_MAKE_ID(be32_to_cpu(pwi_path->opa.dwid));
	}
	if (pwi_path->hop_wimit <= 1) {
		IBA_SET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID, weq_msg,
			be16_to_cpu(pwi_ext ? 0 :
					      htons(ntohw(sa_path_get_swid(
						      pwi_path)))));
		IBA_SET(CM_WEQ_PWIMAWY_WEMOTE_POWT_WID, weq_msg,
			be16_to_cpu(pwi_ext ? 0 :
					      htons(ntohw(sa_path_get_dwid(
						      pwi_path)))));
	} ewse {

		if (pawam->pwimawy_path_inbound) {
			wid = pawam->pwimawy_path_inbound->ib.dwid;
			IBA_SET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(wid));
		} ewse
			IBA_SET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(IB_WID_PEWMISSIVE));

		/* Wowk-awound untiw thewe's a way to obtain wemote WID info */
		IBA_SET(CM_WEQ_PWIMAWY_WEMOTE_POWT_WID, weq_msg,
			be16_to_cpu(IB_WID_PEWMISSIVE));
	}
	IBA_SET(CM_WEQ_PWIMAWY_FWOW_WABEW, weq_msg,
		be32_to_cpu(pwi_path->fwow_wabew));
	IBA_SET(CM_WEQ_PWIMAWY_PACKET_WATE, weq_msg, pwi_path->wate);
	IBA_SET(CM_WEQ_PWIMAWY_TWAFFIC_CWASS, weq_msg, pwi_path->twaffic_cwass);
	IBA_SET(CM_WEQ_PWIMAWY_HOP_WIMIT, weq_msg, pwi_path->hop_wimit);
	IBA_SET(CM_WEQ_PWIMAWY_SW, weq_msg, pwi_path->sw);
	IBA_SET(CM_WEQ_PWIMAWY_SUBNET_WOCAW, weq_msg,
		(pwi_path->hop_wimit <= 1));
	IBA_SET(CM_WEQ_PWIMAWY_WOCAW_ACK_TIMEOUT, weq_msg,
		cm_ack_timeout(cm_id_pwiv->av.powt->cm_dev->ack_deway,
			       pwi_path->packet_wife_time));

	if (awt_path) {
		boow awt_ext = fawse;

		if (awt_path->wec_type == SA_PATH_WEC_TYPE_OPA)
			awt_ext = opa_is_extended_wid(awt_path->opa.dwid,
						      awt_path->opa.swid);

		*IBA_GET_MEM_PTW(CM_WEQ_AWTEWNATE_WOCAW_POWT_GID, weq_msg) =
			awt_path->sgid;
		*IBA_GET_MEM_PTW(CM_WEQ_AWTEWNATE_WEMOTE_POWT_GID, weq_msg) =
			awt_path->dgid;
		if (awt_ext) {
			IBA_GET_MEM_PTW(CM_WEQ_AWTEWNATE_WOCAW_POWT_GID,
					weq_msg)
				->gwobaw.intewface_id =
				OPA_MAKE_ID(be32_to_cpu(awt_path->opa.swid));
			IBA_GET_MEM_PTW(CM_WEQ_AWTEWNATE_WEMOTE_POWT_GID,
					weq_msg)
				->gwobaw.intewface_id =
				OPA_MAKE_ID(be32_to_cpu(awt_path->opa.dwid));
		}
		if (awt_path->hop_wimit <= 1) {
			IBA_SET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(
					awt_ext ? 0 :
						  htons(ntohw(sa_path_get_swid(
							  awt_path)))));
			IBA_SET(CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID, weq_msg,
				be16_to_cpu(
					awt_ext ? 0 :
						  htons(ntohw(sa_path_get_dwid(
							  awt_path)))));
		} ewse {
			IBA_SET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(IB_WID_PEWMISSIVE));
			IBA_SET(CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID, weq_msg,
				be16_to_cpu(IB_WID_PEWMISSIVE));
		}
		IBA_SET(CM_WEQ_AWTEWNATE_FWOW_WABEW, weq_msg,
			be32_to_cpu(awt_path->fwow_wabew));
		IBA_SET(CM_WEQ_AWTEWNATE_PACKET_WATE, weq_msg, awt_path->wate);
		IBA_SET(CM_WEQ_AWTEWNATE_TWAFFIC_CWASS, weq_msg,
			awt_path->twaffic_cwass);
		IBA_SET(CM_WEQ_AWTEWNATE_HOP_WIMIT, weq_msg,
			awt_path->hop_wimit);
		IBA_SET(CM_WEQ_AWTEWNATE_SW, weq_msg, awt_path->sw);
		IBA_SET(CM_WEQ_AWTEWNATE_SUBNET_WOCAW, weq_msg,
			(awt_path->hop_wimit <= 1));
		IBA_SET(CM_WEQ_AWTEWNATE_WOCAW_ACK_TIMEOUT, weq_msg,
			cm_ack_timeout(cm_id_pwiv->av.powt->cm_dev->ack_deway,
				       awt_path->packet_wife_time));
	}
	IBA_SET(CM_WEQ_VENDOW_ID, weq_msg, pawam->ece.vendow_id);

	if (pawam->pwivate_data && pawam->pwivate_data_wen)
		IBA_SET_MEM(CM_WEQ_PWIVATE_DATA, weq_msg, pawam->pwivate_data,
			    pawam->pwivate_data_wen);
}

static int cm_vawidate_weq_pawam(stwuct ib_cm_weq_pawam *pawam)
{
	if (!pawam->pwimawy_path)
		wetuwn -EINVAW;

	if (pawam->qp_type != IB_QPT_WC && pawam->qp_type != IB_QPT_UC &&
	    pawam->qp_type != IB_QPT_XWC_INI)
		wetuwn -EINVAW;

	if (pawam->pwivate_data &&
	    pawam->pwivate_data_wen > IB_CM_WEQ_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	if (pawam->awtewnate_path &&
	    (pawam->awtewnate_path->pkey != pawam->pwimawy_path->pkey ||
	     pawam->awtewnate_path->mtu != pawam->pwimawy_path->mtu))
		wetuwn -EINVAW;

	wetuwn 0;
}

int ib_send_cm_weq(stwuct ib_cm_id *cm_id,
		   stwuct ib_cm_weq_pawam *pawam)
{
	stwuct cm_av av = {}, awt_av = {};
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct ib_mad_send_buf *msg;
	stwuct cm_weq_msg *weq_msg;
	unsigned wong fwags;
	int wet;

	wet = cm_vawidate_weq_pawam(pawam);
	if (wet)
		wetuwn wet;

	/* Vewify that we'we not in timewait. */
	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id->state != IB_CM_IDWE || WAWN_ON(cm_id_pwiv->timewait_info)) {
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	cm_id_pwiv->timewait_info = cm_cweate_timewait_info(cm_id_pwiv->
							    id.wocaw_id);
	if (IS_EWW(cm_id_pwiv->timewait_info)) {
		wet = PTW_EWW(cm_id_pwiv->timewait_info);
		cm_id_pwiv->timewait_info = NUWW;
		wetuwn wet;
	}

	wet = cm_init_av_by_path(pawam->pwimawy_path,
				 pawam->ppath_sgid_attw, &av);
	if (wet)
		wetuwn wet;
	if (pawam->awtewnate_path) {
		wet = cm_init_av_by_path(pawam->awtewnate_path, NUWW,
					 &awt_av);
		if (wet) {
			cm_destwoy_av(&av);
			wetuwn wet;
		}
	}
	cm_id->sewvice_id = pawam->sewvice_id;
	cm_id_pwiv->timeout_ms = cm_convewt_to_ms(
				    pawam->pwimawy_path->packet_wife_time) * 2 +
				 cm_convewt_to_ms(
				    pawam->wemote_cm_wesponse_timeout);
	cm_id_pwiv->max_cm_wetwies = pawam->max_cm_wetwies;
	cm_id_pwiv->initiatow_depth = pawam->initiatow_depth;
	cm_id_pwiv->wespondew_wesouwces = pawam->wespondew_wesouwces;
	cm_id_pwiv->wetwy_count = pawam->wetwy_count;
	cm_id_pwiv->path_mtu = pawam->pwimawy_path->mtu;
	cm_id_pwiv->pkey = pawam->pwimawy_path->pkey;
	cm_id_pwiv->qp_type = pawam->qp_type;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);

	cm_move_av_fwom_path(&cm_id_pwiv->av, &av);
	if (pawam->pwimawy_path_outbound)
		cm_id_pwiv->av.dwid_datapath =
			be16_to_cpu(pawam->pwimawy_path_outbound->ib.dwid);

	if (pawam->awtewnate_path)
		cm_move_av_fwom_path(&cm_id_pwiv->awt_av, &awt_av);

	msg = cm_awwoc_pwiv_msg(cm_id_pwiv);
	if (IS_EWW(msg)) {
		wet = PTW_EWW(msg);
		goto out_unwock;
	}

	weq_msg = (stwuct cm_weq_msg *)msg->mad;
	cm_fowmat_weq(weq_msg, cm_id_pwiv, pawam);
	cm_id_pwiv->tid = weq_msg->hdw.tid;
	msg->timeout_ms = cm_id_pwiv->timeout_ms;
	msg->context[1] = (void *)(unsigned wong)IB_CM_WEQ_SENT;

	cm_id_pwiv->wocaw_qpn = cpu_to_be32(IBA_GET(CM_WEQ_WOCAW_QPN, weq_msg));
	cm_id_pwiv->wq_psn = cpu_to_be32(IBA_GET(CM_WEQ_STAWTING_PSN, weq_msg));

	twace_icm_send_weq(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		goto out_fwee;
	BUG_ON(cm_id->state != IB_CM_IDWE);
	cm_id->state = IB_CM_WEQ_SENT;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn 0;
out_fwee:
	cm_fwee_pwiv_msg(msg);
out_unwock:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_weq);

static int cm_issue_wej(stwuct cm_powt *powt,
			stwuct ib_mad_wecv_wc *mad_wecv_wc,
			enum ib_cm_wej_weason weason,
			enum cm_msg_wesponse msg_wejected,
			void *awi, u8 awi_wength)
{
	stwuct ib_mad_send_buf *msg = NUWW;
	stwuct cm_wej_msg *wej_msg, *wcv_msg;
	int wet;

	wet = cm_awwoc_wesponse_msg(powt, mad_wecv_wc, &msg);
	if (wet)
		wetuwn wet;

	/* We just need common CM headew infowmation.  Cast to any message. */
	wcv_msg = (stwuct cm_wej_msg *) mad_wecv_wc->wecv_buf.mad;
	wej_msg = (stwuct cm_wej_msg *) msg->mad;

	cm_fowmat_mad_hdw(&wej_msg->hdw, CM_WEJ_ATTW_ID, wcv_msg->hdw.tid);
	IBA_SET(CM_WEJ_WEMOTE_COMM_ID, wej_msg,
		IBA_GET(CM_WEJ_WOCAW_COMM_ID, wcv_msg));
	IBA_SET(CM_WEJ_WOCAW_COMM_ID, wej_msg,
		IBA_GET(CM_WEJ_WEMOTE_COMM_ID, wcv_msg));
	IBA_SET(CM_WEJ_MESSAGE_WEJECTED, wej_msg, msg_wejected);
	IBA_SET(CM_WEJ_WEASON, wej_msg, weason);

	if (awi && awi_wength) {
		IBA_SET(CM_WEJ_WEJECTED_INFO_WENGTH, wej_msg, awi_wength);
		IBA_SET_MEM(CM_WEJ_AWI, wej_msg, awi, awi_wength);
	}

	twace_icm_issue_wej(
		IBA_GET(CM_WEJ_WOCAW_COMM_ID, wcv_msg),
		IBA_GET(CM_WEJ_WEMOTE_COMM_ID, wcv_msg));
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		cm_fwee_wesponse_msg(msg);

	wetuwn wet;
}

static boow cm_weq_has_awt_path(stwuct cm_weq_msg *weq_msg)
{
	wetuwn ((cpu_to_be16(
			IBA_GET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID, weq_msg))) ||
		(ib_is_opa_gid(IBA_GET_MEM_PTW(CM_WEQ_AWTEWNATE_WOCAW_POWT_GID,
					       weq_msg))));
}

static void cm_path_set_wec_type(stwuct ib_device *ib_device, u32 powt_num,
				 stwuct sa_path_wec *path, union ib_gid *gid)
{
	if (ib_is_opa_gid(gid) && wdma_cap_opa_ah(ib_device, powt_num))
		path->wec_type = SA_PATH_WEC_TYPE_OPA;
	ewse
		path->wec_type = SA_PATH_WEC_TYPE_IB;
}

static void cm_fowmat_path_wid_fwom_weq(stwuct cm_weq_msg *weq_msg,
					stwuct sa_path_wec *pwimawy_path,
					stwuct sa_path_wec *awt_path,
					stwuct ib_wc *wc)
{
	u32 wid;

	if (pwimawy_path->wec_type != SA_PATH_WEC_TYPE_OPA) {
		sa_path_set_dwid(pwimawy_path, wc->swid);
		sa_path_set_swid(pwimawy_path,
				 IBA_GET(CM_WEQ_PWIMAWY_WEMOTE_POWT_WID,
					 weq_msg));
	} ewse {
		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WEQ_PWIMAWY_WOCAW_POWT_GID, weq_msg));
		sa_path_set_dwid(pwimawy_path, wid);

		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WEQ_PWIMAWY_WEMOTE_POWT_GID, weq_msg));
		sa_path_set_swid(pwimawy_path, wid);
	}

	if (!cm_weq_has_awt_path(weq_msg))
		wetuwn;

	if (awt_path->wec_type != SA_PATH_WEC_TYPE_OPA) {
		sa_path_set_dwid(awt_path,
				 IBA_GET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID,
					 weq_msg));
		sa_path_set_swid(awt_path,
				 IBA_GET(CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID,
					 weq_msg));
	} ewse {
		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WEQ_AWTEWNATE_WOCAW_POWT_GID, weq_msg));
		sa_path_set_dwid(awt_path, wid);

		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WEQ_AWTEWNATE_WEMOTE_POWT_GID, weq_msg));
		sa_path_set_swid(awt_path, wid);
	}
}

static void cm_fowmat_paths_fwom_weq(stwuct cm_weq_msg *weq_msg,
				     stwuct sa_path_wec *pwimawy_path,
				     stwuct sa_path_wec *awt_path,
				     stwuct ib_wc *wc)
{
	pwimawy_path->dgid =
		*IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WOCAW_POWT_GID, weq_msg);
	pwimawy_path->sgid =
		*IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WEMOTE_POWT_GID, weq_msg);
	pwimawy_path->fwow_wabew =
		cpu_to_be32(IBA_GET(CM_WEQ_PWIMAWY_FWOW_WABEW, weq_msg));
	pwimawy_path->hop_wimit = IBA_GET(CM_WEQ_PWIMAWY_HOP_WIMIT, weq_msg);
	pwimawy_path->twaffic_cwass =
		IBA_GET(CM_WEQ_PWIMAWY_TWAFFIC_CWASS, weq_msg);
	pwimawy_path->wevewsibwe = 1;
	pwimawy_path->pkey =
		cpu_to_be16(IBA_GET(CM_WEQ_PAWTITION_KEY, weq_msg));
	pwimawy_path->sw = IBA_GET(CM_WEQ_PWIMAWY_SW, weq_msg);
	pwimawy_path->mtu_sewectow = IB_SA_EQ;
	pwimawy_path->mtu = IBA_GET(CM_WEQ_PATH_PACKET_PAYWOAD_MTU, weq_msg);
	pwimawy_path->wate_sewectow = IB_SA_EQ;
	pwimawy_path->wate = IBA_GET(CM_WEQ_PWIMAWY_PACKET_WATE, weq_msg);
	pwimawy_path->packet_wife_time_sewectow = IB_SA_EQ;
	pwimawy_path->packet_wife_time =
		IBA_GET(CM_WEQ_PWIMAWY_WOCAW_ACK_TIMEOUT, weq_msg);
	pwimawy_path->packet_wife_time -= (pwimawy_path->packet_wife_time > 0);
	pwimawy_path->sewvice_id =
		cpu_to_be64(IBA_GET(CM_WEQ_SEWVICE_ID, weq_msg));
	if (sa_path_is_woce(pwimawy_path))
		pwimawy_path->woce.woute_wesowved = fawse;

	if (cm_weq_has_awt_path(weq_msg)) {
		awt_path->dgid = *IBA_GET_MEM_PTW(
			CM_WEQ_AWTEWNATE_WOCAW_POWT_GID, weq_msg);
		awt_path->sgid = *IBA_GET_MEM_PTW(
			CM_WEQ_AWTEWNATE_WEMOTE_POWT_GID, weq_msg);
		awt_path->fwow_wabew = cpu_to_be32(
			IBA_GET(CM_WEQ_AWTEWNATE_FWOW_WABEW, weq_msg));
		awt_path->hop_wimit =
			IBA_GET(CM_WEQ_AWTEWNATE_HOP_WIMIT, weq_msg);
		awt_path->twaffic_cwass =
			IBA_GET(CM_WEQ_AWTEWNATE_TWAFFIC_CWASS, weq_msg);
		awt_path->wevewsibwe = 1;
		awt_path->pkey =
			cpu_to_be16(IBA_GET(CM_WEQ_PAWTITION_KEY, weq_msg));
		awt_path->sw = IBA_GET(CM_WEQ_AWTEWNATE_SW, weq_msg);
		awt_path->mtu_sewectow = IB_SA_EQ;
		awt_path->mtu =
			IBA_GET(CM_WEQ_PATH_PACKET_PAYWOAD_MTU, weq_msg);
		awt_path->wate_sewectow = IB_SA_EQ;
		awt_path->wate = IBA_GET(CM_WEQ_AWTEWNATE_PACKET_WATE, weq_msg);
		awt_path->packet_wife_time_sewectow = IB_SA_EQ;
		awt_path->packet_wife_time =
			IBA_GET(CM_WEQ_AWTEWNATE_WOCAW_ACK_TIMEOUT, weq_msg);
		awt_path->packet_wife_time -= (awt_path->packet_wife_time > 0);
		awt_path->sewvice_id =
			cpu_to_be64(IBA_GET(CM_WEQ_SEWVICE_ID, weq_msg));

		if (sa_path_is_woce(awt_path))
			awt_path->woce.woute_wesowved = fawse;
	}
	cm_fowmat_path_wid_fwom_weq(weq_msg, pwimawy_path, awt_path, wc);
}

static u16 cm_get_bth_pkey(stwuct cm_wowk *wowk)
{
	stwuct ib_device *ib_dev = wowk->powt->cm_dev->ib_device;
	u32 powt_num = wowk->powt->powt_num;
	u16 pkey_index = wowk->mad_wecv_wc->wc->pkey_index;
	u16 pkey;
	int wet;

	wet = ib_get_cached_pkey(ib_dev, powt_num, pkey_index, &pkey);
	if (wet) {
		dev_wawn_watewimited(&ib_dev->dev, "ib_cm: Couwdn't wetwieve pkey fow incoming wequest (powt %u, pkey index %u). %d\n",
				     powt_num, pkey_index, wet);
		wetuwn 0;
	}

	wetuwn pkey;
}

/**
 * cm_opa_to_ib_sgid - Convewt OPA SGID to IB SGID
 * UWPs (such as IPoIB) do not undewstand OPA GIDs and wiww
 * weject them as the wocaw_gid wiww not match the sgid. Thewefowe,
 * change the pathwec's SGID to an IB SGID.
 *
 * @wowk: Wowk compwetion
 * @path: Path wecowd
 */
static void cm_opa_to_ib_sgid(stwuct cm_wowk *wowk,
			      stwuct sa_path_wec *path)
{
	stwuct ib_device *dev = wowk->powt->cm_dev->ib_device;
	u32 powt_num = wowk->powt->powt_num;

	if (wdma_cap_opa_ah(dev, powt_num) &&
	    (ib_is_opa_gid(&path->sgid))) {
		union ib_gid sgid;

		if (wdma_quewy_gid(dev, powt_num, 0, &sgid)) {
			dev_wawn(&dev->dev,
				 "Ewwow updating sgid in CM wequest\n");
			wetuwn;
		}

		path->sgid = sgid;
	}
}

static void cm_fowmat_weq_event(stwuct cm_wowk *wowk,
				stwuct cm_id_pwivate *cm_id_pwiv,
				stwuct ib_cm_id *wisten_id)
{
	stwuct cm_weq_msg *weq_msg;
	stwuct ib_cm_weq_event_pawam *pawam;

	weq_msg = (stwuct cm_weq_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	pawam = &wowk->cm_event.pawam.weq_wcvd;
	pawam->wisten_id = wisten_id;
	pawam->bth_pkey = cm_get_bth_pkey(wowk);
	pawam->powt = cm_id_pwiv->av.powt->powt_num;
	pawam->pwimawy_path = &wowk->path[0];
	cm_opa_to_ib_sgid(wowk, pawam->pwimawy_path);
	if (cm_weq_has_awt_path(weq_msg)) {
		pawam->awtewnate_path = &wowk->path[1];
		cm_opa_to_ib_sgid(wowk, pawam->awtewnate_path);
	} ewse {
		pawam->awtewnate_path = NUWW;
	}
	pawam->wemote_ca_guid =
		cpu_to_be64(IBA_GET(CM_WEQ_WOCAW_CA_GUID, weq_msg));
	pawam->wemote_qkey = IBA_GET(CM_WEQ_WOCAW_Q_KEY, weq_msg);
	pawam->wemote_qpn = IBA_GET(CM_WEQ_WOCAW_QPN, weq_msg);
	pawam->qp_type = cm_weq_get_qp_type(weq_msg);
	pawam->stawting_psn = IBA_GET(CM_WEQ_STAWTING_PSN, weq_msg);
	pawam->wespondew_wesouwces = IBA_GET(CM_WEQ_INITIATOW_DEPTH, weq_msg);
	pawam->initiatow_depth = IBA_GET(CM_WEQ_WESPONDEW_WESOUWCES, weq_msg);
	pawam->wocaw_cm_wesponse_timeout =
		IBA_GET(CM_WEQ_WEMOTE_CM_WESPONSE_TIMEOUT, weq_msg);
	pawam->fwow_contwow = IBA_GET(CM_WEQ_END_TO_END_FWOW_CONTWOW, weq_msg);
	pawam->wemote_cm_wesponse_timeout =
		IBA_GET(CM_WEQ_WOCAW_CM_WESPONSE_TIMEOUT, weq_msg);
	pawam->wetwy_count = IBA_GET(CM_WEQ_WETWY_COUNT, weq_msg);
	pawam->wnw_wetwy_count = IBA_GET(CM_WEQ_WNW_WETWY_COUNT, weq_msg);
	pawam->swq = IBA_GET(CM_WEQ_SWQ, weq_msg);
	pawam->ppath_sgid_attw = cm_id_pwiv->av.ah_attw.gwh.sgid_attw;
	pawam->ece.vendow_id = IBA_GET(CM_WEQ_VENDOW_ID, weq_msg);
	pawam->ece.attw_mod = be32_to_cpu(weq_msg->hdw.attw_mod);

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_WEQ_PWIVATE_DATA, weq_msg);
}

static void cm_pwocess_wowk(stwuct cm_id_pwivate *cm_id_pwiv,
			    stwuct cm_wowk *wowk)
{
	int wet;

	/* We wiww typicawwy onwy have the cuwwent event to wepowt. */
	wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, &wowk->cm_event);
	cm_fwee_wowk(wowk);

	whiwe (!wet && !atomic_add_negative(-1, &cm_id_pwiv->wowk_count)) {
		spin_wock_iwq(&cm_id_pwiv->wock);
		wowk = cm_dequeue_wowk(cm_id_pwiv);
		spin_unwock_iwq(&cm_id_pwiv->wock);
		if (!wowk)
			wetuwn;

		wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id,
						&wowk->cm_event);
		cm_fwee_wowk(wowk);
	}
	cm_dewef_id(cm_id_pwiv);
	if (wet)
		cm_destwoy_id(&cm_id_pwiv->id, wet);
}

static void cm_fowmat_mwa(stwuct cm_mwa_msg *mwa_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  enum cm_msg_wesponse msg_mwaed, u8 sewvice_timeout,
			  const void *pwivate_data, u8 pwivate_data_wen)
{
	cm_fowmat_mad_hdw(&mwa_msg->hdw, CM_MWA_ATTW_ID, cm_id_pwiv->tid);
	IBA_SET(CM_MWA_MESSAGE_MWAED, mwa_msg, msg_mwaed);
	IBA_SET(CM_MWA_WOCAW_COMM_ID, mwa_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_MWA_WEMOTE_COMM_ID, mwa_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));
	IBA_SET(CM_MWA_SEWVICE_TIMEOUT, mwa_msg, sewvice_timeout);

	if (pwivate_data && pwivate_data_wen)
		IBA_SET_MEM(CM_MWA_PWIVATE_DATA, mwa_msg, pwivate_data,
			    pwivate_data_wen);
}

static void cm_fowmat_wej(stwuct cm_wej_msg *wej_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  enum ib_cm_wej_weason weason, void *awi,
			  u8 awi_wength, const void *pwivate_data,
			  u8 pwivate_data_wen, enum ib_cm_state state)
{
	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	cm_fowmat_mad_hdw(&wej_msg->hdw, CM_WEJ_ATTW_ID, cm_id_pwiv->tid);
	IBA_SET(CM_WEJ_WEMOTE_COMM_ID, wej_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));

	switch (state) {
	case IB_CM_WEQ_WCVD:
		IBA_SET(CM_WEJ_WOCAW_COMM_ID, wej_msg, be32_to_cpu(0));
		IBA_SET(CM_WEJ_MESSAGE_WEJECTED, wej_msg, CM_MSG_WESPONSE_WEQ);
		bweak;
	case IB_CM_MWA_WEQ_SENT:
		IBA_SET(CM_WEJ_WOCAW_COMM_ID, wej_msg,
			be32_to_cpu(cm_id_pwiv->id.wocaw_id));
		IBA_SET(CM_WEJ_MESSAGE_WEJECTED, wej_msg, CM_MSG_WESPONSE_WEQ);
		bweak;
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
		IBA_SET(CM_WEJ_WOCAW_COMM_ID, wej_msg,
			be32_to_cpu(cm_id_pwiv->id.wocaw_id));
		IBA_SET(CM_WEJ_MESSAGE_WEJECTED, wej_msg, CM_MSG_WESPONSE_WEP);
		bweak;
	defauwt:
		IBA_SET(CM_WEJ_WOCAW_COMM_ID, wej_msg,
			be32_to_cpu(cm_id_pwiv->id.wocaw_id));
		IBA_SET(CM_WEJ_MESSAGE_WEJECTED, wej_msg,
			CM_MSG_WESPONSE_OTHEW);
		bweak;
	}

	IBA_SET(CM_WEJ_WEASON, wej_msg, weason);
	if (awi && awi_wength) {
		IBA_SET(CM_WEJ_WEJECTED_INFO_WENGTH, wej_msg, awi_wength);
		IBA_SET_MEM(CM_WEJ_AWI, wej_msg, awi, awi_wength);
	}

	if (pwivate_data && pwivate_data_wen)
		IBA_SET_MEM(CM_WEJ_PWIVATE_DATA, wej_msg, pwivate_data,
			    pwivate_data_wen);
}

static void cm_dup_weq_handwew(stwuct cm_wowk *wowk,
			       stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct ib_mad_send_buf *msg = NUWW;
	int wet;

	atomic_wong_inc(
		&wowk->powt->countews[CM_WECV_DUPWICATES][CM_WEQ_COUNTEW]);

	/* Quick state check to discawd dupwicate WEQs. */
	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state == IB_CM_WEQ_WCVD) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		wetuwn;
	}
	spin_unwock_iwq(&cm_id_pwiv->wock);

	wet = cm_awwoc_wesponse_msg(wowk->powt, wowk->mad_wecv_wc, &msg);
	if (wet)
		wetuwn;

	spin_wock_iwq(&cm_id_pwiv->wock);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_MWA_WEQ_SENT:
		cm_fowmat_mwa((stwuct cm_mwa_msg *) msg->mad, cm_id_pwiv,
			      CM_MSG_WESPONSE_WEQ, cm_id_pwiv->sewvice_timeout,
			      cm_id_pwiv->pwivate_data,
			      cm_id_pwiv->pwivate_data_wen);
		bweak;
	case IB_CM_TIMEWAIT:
		cm_fowmat_wej((stwuct cm_wej_msg *)msg->mad, cm_id_pwiv,
			      IB_CM_WEJ_STAWE_CONN, NUWW, 0, NUWW, 0,
			      IB_CM_TIMEWAIT);
		bweak;
	defauwt:
		goto unwock;
	}
	spin_unwock_iwq(&cm_id_pwiv->wock);

	twace_icm_send_dup_weq(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		goto fwee;
	wetuwn;

unwock:	spin_unwock_iwq(&cm_id_pwiv->wock);
fwee:	cm_fwee_wesponse_msg(msg);
}

static stwuct cm_id_pwivate *cm_match_weq(stwuct cm_wowk *wowk,
					  stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct cm_id_pwivate *wisten_cm_id_pwiv, *cuw_cm_id_pwiv;
	stwuct cm_timewait_info *timewait_info;
	stwuct cm_weq_msg *weq_msg;

	weq_msg = (stwuct cm_weq_msg *)wowk->mad_wecv_wc->wecv_buf.mad;

	/* Check fow possibwe dupwicate WEQ. */
	spin_wock_iwq(&cm.wock);
	timewait_info = cm_insewt_wemote_id(cm_id_pwiv->timewait_info);
	if (timewait_info) {
		cuw_cm_id_pwiv = cm_acquiwe_id(timewait_info->wowk.wocaw_id,
					   timewait_info->wowk.wemote_id);
		spin_unwock_iwq(&cm.wock);
		if (cuw_cm_id_pwiv) {
			cm_dup_weq_handwew(wowk, cuw_cm_id_pwiv);
			cm_dewef_id(cuw_cm_id_pwiv);
		}
		wetuwn NUWW;
	}

	/* Check fow stawe connections. */
	timewait_info = cm_insewt_wemote_qpn(cm_id_pwiv->timewait_info);
	if (timewait_info) {
		cm_wemove_wemote(cm_id_pwiv);
		cuw_cm_id_pwiv = cm_acquiwe_id(timewait_info->wowk.wocaw_id,
					   timewait_info->wowk.wemote_id);

		spin_unwock_iwq(&cm.wock);
		cm_issue_wej(wowk->powt, wowk->mad_wecv_wc,
			     IB_CM_WEJ_STAWE_CONN, CM_MSG_WESPONSE_WEQ,
			     NUWW, 0);
		if (cuw_cm_id_pwiv) {
			ib_send_cm_dweq(&cuw_cm_id_pwiv->id, NUWW, 0);
			cm_dewef_id(cuw_cm_id_pwiv);
		}
		wetuwn NUWW;
	}

	/* Find matching wisten wequest. */
	wisten_cm_id_pwiv = cm_find_wisten(
		cm_id_pwiv->id.device,
		cpu_to_be64(IBA_GET(CM_WEQ_SEWVICE_ID, weq_msg)));
	if (!wisten_cm_id_pwiv) {
		cm_wemove_wemote(cm_id_pwiv);
		spin_unwock_iwq(&cm.wock);
		cm_issue_wej(wowk->powt, wowk->mad_wecv_wc,
			     IB_CM_WEJ_INVAWID_SEWVICE_ID, CM_MSG_WESPONSE_WEQ,
			     NUWW, 0);
		wetuwn NUWW;
	}
	spin_unwock_iwq(&cm.wock);
	wetuwn wisten_cm_id_pwiv;
}

/*
 * Wowk-awound fow intew-subnet connections.  If the WIDs awe pewmissive,
 * we need to ovewwide the WID/SW data in the WEQ with the WID infowmation
 * in the wowk compwetion.
 */
static void cm_pwocess_wouted_weq(stwuct cm_weq_msg *weq_msg, stwuct ib_wc *wc)
{
	if (!IBA_GET(CM_WEQ_PWIMAWY_SUBNET_WOCAW, weq_msg)) {
		if (cpu_to_be16(IBA_GET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID,
					weq_msg)) == IB_WID_PEWMISSIVE) {
			IBA_SET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(ib_wid_be16(wc->swid)));
			IBA_SET(CM_WEQ_PWIMAWY_SW, weq_msg, wc->sw);
		}

		if (cpu_to_be16(IBA_GET(CM_WEQ_PWIMAWY_WEMOTE_POWT_WID,
					weq_msg)) == IB_WID_PEWMISSIVE)
			IBA_SET(CM_WEQ_PWIMAWY_WEMOTE_POWT_WID, weq_msg,
				wc->dwid_path_bits);
	}

	if (!IBA_GET(CM_WEQ_AWTEWNATE_SUBNET_WOCAW, weq_msg)) {
		if (cpu_to_be16(IBA_GET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID,
					weq_msg)) == IB_WID_PEWMISSIVE) {
			IBA_SET(CM_WEQ_AWTEWNATE_WOCAW_POWT_WID, weq_msg,
				be16_to_cpu(ib_wid_be16(wc->swid)));
			IBA_SET(CM_WEQ_AWTEWNATE_SW, weq_msg, wc->sw);
		}

		if (cpu_to_be16(IBA_GET(CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID,
					weq_msg)) == IB_WID_PEWMISSIVE)
			IBA_SET(CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID, weq_msg,
				wc->dwid_path_bits);
	}
}

static int cm_weq_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv, *wisten_cm_id_pwiv;
	stwuct cm_weq_msg *weq_msg;
	const stwuct ib_gwobaw_woute *gwh;
	const stwuct ib_gid_attw *gid_attw;
	int wet;

	weq_msg = (stwuct cm_weq_msg *)wowk->mad_wecv_wc->wecv_buf.mad;

	cm_id_pwiv =
		cm_awwoc_id_pwiv(wowk->powt->cm_dev->ib_device, NUWW, NUWW);
	if (IS_EWW(cm_id_pwiv))
		wetuwn PTW_EWW(cm_id_pwiv);

	cm_id_pwiv->id.wemote_id =
		cpu_to_be32(IBA_GET(CM_WEQ_WOCAW_COMM_ID, weq_msg));
	cm_id_pwiv->id.sewvice_id =
		cpu_to_be64(IBA_GET(CM_WEQ_SEWVICE_ID, weq_msg));
	cm_id_pwiv->tid = weq_msg->hdw.tid;
	cm_id_pwiv->timeout_ms = cm_convewt_to_ms(
		IBA_GET(CM_WEQ_WOCAW_CM_WESPONSE_TIMEOUT, weq_msg));
	cm_id_pwiv->max_cm_wetwies = IBA_GET(CM_WEQ_MAX_CM_WETWIES, weq_msg);
	cm_id_pwiv->wemote_qpn =
		cpu_to_be32(IBA_GET(CM_WEQ_WOCAW_QPN, weq_msg));
	cm_id_pwiv->initiatow_depth =
		IBA_GET(CM_WEQ_WESPONDEW_WESOUWCES, weq_msg);
	cm_id_pwiv->wespondew_wesouwces =
		IBA_GET(CM_WEQ_INITIATOW_DEPTH, weq_msg);
	cm_id_pwiv->path_mtu = IBA_GET(CM_WEQ_PATH_PACKET_PAYWOAD_MTU, weq_msg);
	cm_id_pwiv->pkey = cpu_to_be16(IBA_GET(CM_WEQ_PAWTITION_KEY, weq_msg));
	cm_id_pwiv->sq_psn = cpu_to_be32(IBA_GET(CM_WEQ_STAWTING_PSN, weq_msg));
	cm_id_pwiv->wetwy_count = IBA_GET(CM_WEQ_WETWY_COUNT, weq_msg);
	cm_id_pwiv->wnw_wetwy_count = IBA_GET(CM_WEQ_WNW_WETWY_COUNT, weq_msg);
	cm_id_pwiv->qp_type = cm_weq_get_qp_type(weq_msg);

	wet = cm_init_av_fow_wesponse(wowk->powt, wowk->mad_wecv_wc->wc,
				      wowk->mad_wecv_wc->wecv_buf.gwh,
				      &cm_id_pwiv->av);
	if (wet)
		goto destwoy;
	cm_id_pwiv->timewait_info = cm_cweate_timewait_info(cm_id_pwiv->
							    id.wocaw_id);
	if (IS_EWW(cm_id_pwiv->timewait_info)) {
		wet = PTW_EWW(cm_id_pwiv->timewait_info);
		cm_id_pwiv->timewait_info = NUWW;
		goto destwoy;
	}
	cm_id_pwiv->timewait_info->wowk.wemote_id = cm_id_pwiv->id.wemote_id;
	cm_id_pwiv->timewait_info->wemote_ca_guid =
		cpu_to_be64(IBA_GET(CM_WEQ_WOCAW_CA_GUID, weq_msg));
	cm_id_pwiv->timewait_info->wemote_qpn = cm_id_pwiv->wemote_qpn;

	/*
	 * Note that the ID pointew is not in the xawway at this point,
	 * so this set is onwy visibwe to the wocaw thwead.
	 */
	cm_id_pwiv->id.state = IB_CM_WEQ_WCVD;

	wisten_cm_id_pwiv = cm_match_weq(wowk, cm_id_pwiv);
	if (!wisten_cm_id_pwiv) {
		twace_icm_no_wistenew_eww(&cm_id_pwiv->id);
		cm_id_pwiv->id.state = IB_CM_IDWE;
		wet = -EINVAW;
		goto destwoy;
	}

	memset(&wowk->path[0], 0, sizeof(wowk->path[0]));
	if (cm_weq_has_awt_path(weq_msg))
		memset(&wowk->path[1], 0, sizeof(wowk->path[1]));
	gwh = wdma_ah_wead_gwh(&cm_id_pwiv->av.ah_attw);
	gid_attw = gwh->sgid_attw;

	if (cm_id_pwiv->av.ah_attw.type == WDMA_AH_ATTW_TYPE_WOCE) {
		wowk->path[0].wec_type =
			sa_conv_gid_to_pathwec_type(gid_attw->gid_type);
	} ewse {
		cm_pwocess_wouted_weq(weq_msg, wowk->mad_wecv_wc->wc);
		cm_path_set_wec_type(
			wowk->powt->cm_dev->ib_device, wowk->powt->powt_num,
			&wowk->path[0],
			IBA_GET_MEM_PTW(CM_WEQ_PWIMAWY_WOCAW_POWT_GID,
					weq_msg));
	}
	if (cm_weq_has_awt_path(weq_msg))
		wowk->path[1].wec_type = wowk->path[0].wec_type;
	cm_fowmat_paths_fwom_weq(weq_msg, &wowk->path[0],
				 &wowk->path[1], wowk->mad_wecv_wc->wc);
	if (cm_id_pwiv->av.ah_attw.type == WDMA_AH_ATTW_TYPE_WOCE)
		sa_path_set_dmac(&wowk->path[0],
				 cm_id_pwiv->av.ah_attw.woce.dmac);
	wowk->path[0].hop_wimit = gwh->hop_wimit;

	/* This destwoy caww is needed to paiw with cm_init_av_fow_wesponse */
	cm_destwoy_av(&cm_id_pwiv->av);
	wet = cm_init_av_by_path(&wowk->path[0], gid_attw, &cm_id_pwiv->av);
	if (wet) {
		int eww;

		eww = wdma_quewy_gid(wowk->powt->cm_dev->ib_device,
				     wowk->powt->powt_num, 0,
				     &wowk->path[0].sgid);
		if (eww)
			ib_send_cm_wej(&cm_id_pwiv->id, IB_CM_WEJ_INVAWID_GID,
				       NUWW, 0, NUWW, 0);
		ewse
			ib_send_cm_wej(&cm_id_pwiv->id, IB_CM_WEJ_INVAWID_GID,
				       &wowk->path[0].sgid,
				       sizeof(wowk->path[0].sgid),
				       NUWW, 0);
		goto wejected;
	}
	if (cm_id_pwiv->av.ah_attw.type == WDMA_AH_ATTW_TYPE_IB)
		cm_id_pwiv->av.dwid_datapath =
			IBA_GET(CM_WEQ_PWIMAWY_WOCAW_POWT_WID, weq_msg);

	if (cm_weq_has_awt_path(weq_msg)) {
		wet = cm_init_av_by_path(&wowk->path[1], NUWW,
					 &cm_id_pwiv->awt_av);
		if (wet) {
			ib_send_cm_wej(&cm_id_pwiv->id,
				       IB_CM_WEJ_INVAWID_AWT_GID,
				       &wowk->path[0].sgid,
				       sizeof(wowk->path[0].sgid), NUWW, 0);
			goto wejected;
		}
	}

	cm_id_pwiv->id.cm_handwew = wisten_cm_id_pwiv->id.cm_handwew;
	cm_id_pwiv->id.context = wisten_cm_id_pwiv->id.context;
	cm_fowmat_weq_event(wowk, cm_id_pwiv, &wisten_cm_id_pwiv->id);

	/* Now MAD handwews can see the new ID */
	spin_wock_iwq(&cm_id_pwiv->wock);
	cm_finawize_id(cm_id_pwiv);

	/* Wefcount bewongs to the event, paiws with cm_pwocess_wowk() */
	wefcount_inc(&cm_id_pwiv->wefcount);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	/*
	 * Since this ID was just cweated and was not made visibwe to othew MAD
	 * handwews untiw the cm_finawize_id() above we know that the
	 * cm_pwocess_wowk() wiww dewivew the event and the wisten_cm_id
	 * embedded in the event can be dewefed hewe.
	 */
	cm_dewef_id(wisten_cm_id_pwiv);
	wetuwn 0;

wejected:
	cm_dewef_id(wisten_cm_id_pwiv);
destwoy:
	ib_destwoy_cm_id(&cm_id_pwiv->id);
	wetuwn wet;
}

static void cm_fowmat_wep(stwuct cm_wep_msg *wep_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  stwuct ib_cm_wep_pawam *pawam)
{
	cm_fowmat_mad_ece_hdw(&wep_msg->hdw, CM_WEP_ATTW_ID, cm_id_pwiv->tid,
			      pawam->ece.attw_mod);
	IBA_SET(CM_WEP_WOCAW_COMM_ID, wep_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_WEP_WEMOTE_COMM_ID, wep_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));
	IBA_SET(CM_WEP_STAWTING_PSN, wep_msg, pawam->stawting_psn);
	IBA_SET(CM_WEP_WESPONDEW_WESOUWCES, wep_msg,
		pawam->wespondew_wesouwces);
	IBA_SET(CM_WEP_TAWGET_ACK_DEWAY, wep_msg,
		cm_id_pwiv->av.powt->cm_dev->ack_deway);
	IBA_SET(CM_WEP_FAIWOVEW_ACCEPTED, wep_msg, pawam->faiwovew_accepted);
	IBA_SET(CM_WEP_WNW_WETWY_COUNT, wep_msg, pawam->wnw_wetwy_count);
	IBA_SET(CM_WEP_WOCAW_CA_GUID, wep_msg,
		be64_to_cpu(cm_id_pwiv->id.device->node_guid));

	if (cm_id_pwiv->qp_type != IB_QPT_XWC_TGT) {
		IBA_SET(CM_WEP_INITIATOW_DEPTH, wep_msg,
			pawam->initiatow_depth);
		IBA_SET(CM_WEP_END_TO_END_FWOW_CONTWOW, wep_msg,
			pawam->fwow_contwow);
		IBA_SET(CM_WEP_SWQ, wep_msg, pawam->swq);
		IBA_SET(CM_WEP_WOCAW_QPN, wep_msg, pawam->qp_num);
	} ewse {
		IBA_SET(CM_WEP_SWQ, wep_msg, 1);
		IBA_SET(CM_WEP_WOCAW_EE_CONTEXT_NUMBEW, wep_msg, pawam->qp_num);
	}

	IBA_SET(CM_WEP_VENDOW_ID_W, wep_msg, pawam->ece.vendow_id);
	IBA_SET(CM_WEP_VENDOW_ID_M, wep_msg, pawam->ece.vendow_id >> 8);
	IBA_SET(CM_WEP_VENDOW_ID_H, wep_msg, pawam->ece.vendow_id >> 16);

	if (pawam->pwivate_data && pawam->pwivate_data_wen)
		IBA_SET_MEM(CM_WEP_PWIVATE_DATA, wep_msg, pawam->pwivate_data,
			    pawam->pwivate_data_wen);
}

int ib_send_cm_wep(stwuct ib_cm_id *cm_id,
		   stwuct ib_cm_wep_pawam *pawam)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct ib_mad_send_buf *msg;
	stwuct cm_wep_msg *wep_msg;
	unsigned wong fwags;
	int wet;

	if (pawam->pwivate_data &&
	    pawam->pwivate_data_wen > IB_CM_WEP_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id->state != IB_CM_WEQ_WCVD &&
	    cm_id->state != IB_CM_MWA_WEQ_SENT) {
		twace_icm_send_wep_eww(cm_id_pwiv->id.wocaw_id, cm_id->state);
		wet = -EINVAW;
		goto out;
	}

	msg = cm_awwoc_pwiv_msg(cm_id_pwiv);
	if (IS_EWW(msg)) {
		wet = PTW_EWW(msg);
		goto out;
	}

	wep_msg = (stwuct cm_wep_msg *) msg->mad;
	cm_fowmat_wep(wep_msg, cm_id_pwiv, pawam);
	msg->timeout_ms = cm_id_pwiv->timeout_ms;
	msg->context[1] = (void *) (unsigned wong) IB_CM_WEP_SENT;

	twace_icm_send_wep(cm_id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		goto out_fwee;

	cm_id->state = IB_CM_WEP_SENT;
	cm_id_pwiv->initiatow_depth = pawam->initiatow_depth;
	cm_id_pwiv->wespondew_wesouwces = pawam->wespondew_wesouwces;
	cm_id_pwiv->wq_psn = cpu_to_be32(IBA_GET(CM_WEP_STAWTING_PSN, wep_msg));
	WAWN_ONCE(pawam->qp_num & 0xFF000000,
		  "IBTA decwawes QPN to be 24 bits, but it is 0x%X\n",
		  pawam->qp_num);
	cm_id_pwiv->wocaw_qpn = cpu_to_be32(pawam->qp_num & 0xFFFFFF);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn 0;

out_fwee:
	cm_fwee_pwiv_msg(msg);
out:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_wep);

static void cm_fowmat_wtu(stwuct cm_wtu_msg *wtu_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  const void *pwivate_data,
			  u8 pwivate_data_wen)
{
	cm_fowmat_mad_hdw(&wtu_msg->hdw, CM_WTU_ATTW_ID, cm_id_pwiv->tid);
	IBA_SET(CM_WTU_WOCAW_COMM_ID, wtu_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_WTU_WEMOTE_COMM_ID, wtu_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));

	if (pwivate_data && pwivate_data_wen)
		IBA_SET_MEM(CM_WTU_PWIVATE_DATA, wtu_msg, pwivate_data,
			    pwivate_data_wen);
}

int ib_send_cm_wtu(stwuct ib_cm_id *cm_id,
		   const void *pwivate_data,
		   u8 pwivate_data_wen)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct ib_mad_send_buf *msg;
	unsigned wong fwags;
	void *data;
	int wet;

	if (pwivate_data && pwivate_data_wen > IB_CM_WTU_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	data = cm_copy_pwivate_data(pwivate_data, pwivate_data_wen);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id->state != IB_CM_WEP_WCVD &&
	    cm_id->state != IB_CM_MWA_WEP_SENT) {
		twace_icm_send_cm_wtu_eww(cm_id);
		wet = -EINVAW;
		goto ewwow;
	}

	msg = cm_awwoc_msg(cm_id_pwiv);
	if (IS_EWW(msg)) {
		wet = PTW_EWW(msg);
		goto ewwow;
	}

	cm_fowmat_wtu((stwuct cm_wtu_msg *) msg->mad, cm_id_pwiv,
		      pwivate_data, pwivate_data_wen);

	twace_icm_send_wtu(cm_id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
		cm_fwee_msg(msg);
		kfwee(data);
		wetuwn wet;
	}

	cm_id->state = IB_CM_ESTABWISHED;
	cm_set_pwivate_data(cm_id_pwiv, data, pwivate_data_wen);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn 0;

ewwow:	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	kfwee(data);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_wtu);

static void cm_fowmat_wep_event(stwuct cm_wowk *wowk, enum ib_qp_type qp_type)
{
	stwuct cm_wep_msg *wep_msg;
	stwuct ib_cm_wep_event_pawam *pawam;

	wep_msg = (stwuct cm_wep_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	pawam = &wowk->cm_event.pawam.wep_wcvd;
	pawam->wemote_ca_guid =
		cpu_to_be64(IBA_GET(CM_WEP_WOCAW_CA_GUID, wep_msg));
	pawam->wemote_qkey = IBA_GET(CM_WEP_WOCAW_Q_KEY, wep_msg);
	pawam->wemote_qpn = be32_to_cpu(cm_wep_get_qpn(wep_msg, qp_type));
	pawam->stawting_psn = IBA_GET(CM_WEP_STAWTING_PSN, wep_msg);
	pawam->wespondew_wesouwces = IBA_GET(CM_WEP_INITIATOW_DEPTH, wep_msg);
	pawam->initiatow_depth = IBA_GET(CM_WEP_WESPONDEW_WESOUWCES, wep_msg);
	pawam->tawget_ack_deway = IBA_GET(CM_WEP_TAWGET_ACK_DEWAY, wep_msg);
	pawam->faiwovew_accepted = IBA_GET(CM_WEP_FAIWOVEW_ACCEPTED, wep_msg);
	pawam->fwow_contwow = IBA_GET(CM_WEP_END_TO_END_FWOW_CONTWOW, wep_msg);
	pawam->wnw_wetwy_count = IBA_GET(CM_WEP_WNW_WETWY_COUNT, wep_msg);
	pawam->swq = IBA_GET(CM_WEP_SWQ, wep_msg);
	pawam->ece.vendow_id = IBA_GET(CM_WEP_VENDOW_ID_H, wep_msg) << 16;
	pawam->ece.vendow_id |= IBA_GET(CM_WEP_VENDOW_ID_M, wep_msg) << 8;
	pawam->ece.vendow_id |= IBA_GET(CM_WEP_VENDOW_ID_W, wep_msg);
	pawam->ece.attw_mod = be32_to_cpu(wep_msg->hdw.attw_mod);

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_WEP_PWIVATE_DATA, wep_msg);
}

static void cm_dup_wep_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wep_msg *wep_msg;
	stwuct ib_mad_send_buf *msg = NUWW;
	int wet;

	wep_msg = (stwuct cm_wep_msg *) wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg)),
		cpu_to_be32(IBA_GET(CM_WEP_WOCAW_COMM_ID, wep_msg)));
	if (!cm_id_pwiv)
		wetuwn;

	atomic_wong_inc(
		&wowk->powt->countews[CM_WECV_DUPWICATES][CM_WEP_COUNTEW]);
	wet = cm_awwoc_wesponse_msg(wowk->powt, wowk->mad_wecv_wc, &msg);
	if (wet)
		goto dewef;

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state == IB_CM_ESTABWISHED)
		cm_fowmat_wtu((stwuct cm_wtu_msg *) msg->mad, cm_id_pwiv,
			      cm_id_pwiv->pwivate_data,
			      cm_id_pwiv->pwivate_data_wen);
	ewse if (cm_id_pwiv->id.state == IB_CM_MWA_WEP_SENT)
		cm_fowmat_mwa((stwuct cm_mwa_msg *) msg->mad, cm_id_pwiv,
			      CM_MSG_WESPONSE_WEP, cm_id_pwiv->sewvice_timeout,
			      cm_id_pwiv->pwivate_data,
			      cm_id_pwiv->pwivate_data_wen);
	ewse
		goto unwock;
	spin_unwock_iwq(&cm_id_pwiv->wock);

	twace_icm_send_dup_wep(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		goto fwee;
	goto dewef;

unwock:	spin_unwock_iwq(&cm_id_pwiv->wock);
fwee:	cm_fwee_wesponse_msg(msg);
dewef:	cm_dewef_id(cm_id_pwiv);
}

static int cm_wep_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wep_msg *wep_msg;
	int wet;
	stwuct cm_id_pwivate *cuw_cm_id_pwiv;
	stwuct cm_timewait_info *timewait_info;

	wep_msg = (stwuct cm_wep_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg)), 0);
	if (!cm_id_pwiv) {
		cm_dup_wep_handwew(wowk);
		twace_icm_wemote_no_pwiv_eww(
			 IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg));
		wetuwn -EINVAW;
	}

	cm_fowmat_wep_event(wowk, cm_id_pwiv->qp_type);

	spin_wock_iwq(&cm_id_pwiv->wock);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
		bweak;
	defauwt:
		wet = -EINVAW;
		twace_icm_wep_unknown_eww(
			IBA_GET(CM_WEP_WOCAW_COMM_ID, wep_msg),
			IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg),
			cm_id_pwiv->id.state);
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto ewwow;
	}

	cm_id_pwiv->timewait_info->wowk.wemote_id =
		cpu_to_be32(IBA_GET(CM_WEP_WOCAW_COMM_ID, wep_msg));
	cm_id_pwiv->timewait_info->wemote_ca_guid =
		cpu_to_be64(IBA_GET(CM_WEP_WOCAW_CA_GUID, wep_msg));
	cm_id_pwiv->timewait_info->wemote_qpn = cm_wep_get_qpn(wep_msg, cm_id_pwiv->qp_type);

	spin_wock(&cm.wock);
	/* Check fow dupwicate WEP. */
	if (cm_insewt_wemote_id(cm_id_pwiv->timewait_info)) {
		spin_unwock(&cm.wock);
		spin_unwock_iwq(&cm_id_pwiv->wock);
		wet = -EINVAW;
		twace_icm_insewt_faiwed_eww(
			 IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg));
		goto ewwow;
	}
	/* Check fow a stawe connection. */
	timewait_info = cm_insewt_wemote_qpn(cm_id_pwiv->timewait_info);
	if (timewait_info) {
		cm_wemove_wemote(cm_id_pwiv);
		cuw_cm_id_pwiv = cm_acquiwe_id(timewait_info->wowk.wocaw_id,
					   timewait_info->wowk.wemote_id);

		spin_unwock(&cm.wock);
		spin_unwock_iwq(&cm_id_pwiv->wock);
		cm_issue_wej(wowk->powt, wowk->mad_wecv_wc,
			     IB_CM_WEJ_STAWE_CONN, CM_MSG_WESPONSE_WEP,
			     NUWW, 0);
		wet = -EINVAW;
		twace_icm_staweconn_eww(
			IBA_GET(CM_WEP_WOCAW_COMM_ID, wep_msg),
			IBA_GET(CM_WEP_WEMOTE_COMM_ID, wep_msg));

		if (cuw_cm_id_pwiv) {
			ib_send_cm_dweq(&cuw_cm_id_pwiv->id, NUWW, 0);
			cm_dewef_id(cuw_cm_id_pwiv);
		}

		goto ewwow;
	}
	spin_unwock(&cm.wock);

	cm_id_pwiv->id.state = IB_CM_WEP_WCVD;
	cm_id_pwiv->id.wemote_id =
		cpu_to_be32(IBA_GET(CM_WEP_WOCAW_COMM_ID, wep_msg));
	cm_id_pwiv->wemote_qpn = cm_wep_get_qpn(wep_msg, cm_id_pwiv->qp_type);
	cm_id_pwiv->initiatow_depth =
		IBA_GET(CM_WEP_WESPONDEW_WESOUWCES, wep_msg);
	cm_id_pwiv->wespondew_wesouwces =
		IBA_GET(CM_WEP_INITIATOW_DEPTH, wep_msg);
	cm_id_pwiv->sq_psn = cpu_to_be32(IBA_GET(CM_WEP_STAWTING_PSN, wep_msg));
	cm_id_pwiv->wnw_wetwy_count = IBA_GET(CM_WEP_WNW_WETWY_COUNT, wep_msg);
	cm_id_pwiv->tawget_ack_deway =
		IBA_GET(CM_WEP_TAWGET_ACK_DEWAY, wep_msg);
	cm_id_pwiv->av.timeout =
			cm_ack_timeout(cm_id_pwiv->tawget_ack_deway,
				       cm_id_pwiv->av.timeout - 1);
	cm_id_pwiv->awt_av.timeout =
			cm_ack_timeout(cm_id_pwiv->tawget_ack_deway,
				       cm_id_pwiv->awt_av.timeout - 1);

	ib_cancew_mad(cm_id_pwiv->msg);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;

ewwow:
	cm_dewef_id(cm_id_pwiv);
	wetuwn wet;
}

static int cm_estabwish_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;

	/* See comment in cm_estabwish about wookup. */
	cm_id_pwiv = cm_acquiwe_id(wowk->wocaw_id, wowk->wemote_id);
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_ESTABWISHED) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}

	ib_cancew_mad(cm_id_pwiv->msg);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static int cm_wtu_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wtu_msg *wtu_msg;

	wtu_msg = (stwuct cm_wtu_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_WTU_WEMOTE_COMM_ID, wtu_msg)),
		cpu_to_be32(IBA_GET(CM_WTU_WOCAW_COMM_ID, wtu_msg)));
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_WTU_PWIVATE_DATA, wtu_msg);

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_WEP_SENT &&
	    cm_id_pwiv->id.state != IB_CM_MWA_WEP_WCVD) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_WTU_COUNTEW]);
		goto out;
	}
	cm_id_pwiv->id.state = IB_CM_ESTABWISHED;

	ib_cancew_mad(cm_id_pwiv->msg);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static void cm_fowmat_dweq(stwuct cm_dweq_msg *dweq_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  const void *pwivate_data,
			  u8 pwivate_data_wen)
{
	cm_fowmat_mad_hdw(&dweq_msg->hdw, CM_DWEQ_ATTW_ID,
			  cm_fowm_tid(cm_id_pwiv));
	IBA_SET(CM_DWEQ_WOCAW_COMM_ID, dweq_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_DWEQ_WEMOTE_COMM_ID, dweq_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));
	IBA_SET(CM_DWEQ_WEMOTE_QPN_EECN, dweq_msg,
		be32_to_cpu(cm_id_pwiv->wemote_qpn));

	if (pwivate_data && pwivate_data_wen)
		IBA_SET_MEM(CM_DWEQ_PWIVATE_DATA, dweq_msg, pwivate_data,
			    pwivate_data_wen);
}

static int cm_send_dweq_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			       const void *pwivate_data, u8 pwivate_data_wen)
{
	stwuct ib_mad_send_buf *msg;
	int wet;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if (pwivate_data && pwivate_data_wen > IB_CM_DWEQ_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	if (cm_id_pwiv->id.state != IB_CM_ESTABWISHED) {
		twace_icm_dweq_skipped(&cm_id_pwiv->id);
		wetuwn -EINVAW;
	}

	if (cm_id_pwiv->id.wap_state == IB_CM_WAP_SENT ||
	    cm_id_pwiv->id.wap_state == IB_CM_MWA_WAP_WCVD)
		ib_cancew_mad(cm_id_pwiv->msg);

	msg = cm_awwoc_pwiv_msg(cm_id_pwiv);
	if (IS_EWW(msg)) {
		cm_entew_timewait(cm_id_pwiv);
		wetuwn PTW_EWW(msg);
	}

	cm_fowmat_dweq((stwuct cm_dweq_msg *) msg->mad, cm_id_pwiv,
		       pwivate_data, pwivate_data_wen);
	msg->timeout_ms = cm_id_pwiv->timeout_ms;
	msg->context[1] = (void *) (unsigned wong) IB_CM_DWEQ_SENT;

	twace_icm_send_dweq(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		cm_entew_timewait(cm_id_pwiv);
		cm_fwee_pwiv_msg(msg);
		wetuwn wet;
	}

	cm_id_pwiv->id.state = IB_CM_DWEQ_SENT;
	wetuwn 0;
}

int ib_send_cm_dweq(stwuct ib_cm_id *cm_id, const void *pwivate_data,
		    u8 pwivate_data_wen)
{
	stwuct cm_id_pwivate *cm_id_pwiv =
		containew_of(cm_id, stwuct cm_id_pwivate, id);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	wet = cm_send_dweq_wocked(cm_id_pwiv, pwivate_data, pwivate_data_wen);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_dweq);

static void cm_fowmat_dwep(stwuct cm_dwep_msg *dwep_msg,
			  stwuct cm_id_pwivate *cm_id_pwiv,
			  const void *pwivate_data,
			  u8 pwivate_data_wen)
{
	cm_fowmat_mad_hdw(&dwep_msg->hdw, CM_DWEP_ATTW_ID, cm_id_pwiv->tid);
	IBA_SET(CM_DWEP_WOCAW_COMM_ID, dwep_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_DWEP_WEMOTE_COMM_ID, dwep_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));

	if (pwivate_data && pwivate_data_wen)
		IBA_SET_MEM(CM_DWEP_PWIVATE_DATA, dwep_msg, pwivate_data,
			    pwivate_data_wen);
}

static int cm_send_dwep_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			       void *pwivate_data, u8 pwivate_data_wen)
{
	stwuct ib_mad_send_buf *msg;
	int wet;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if (pwivate_data && pwivate_data_wen > IB_CM_DWEP_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	if (cm_id_pwiv->id.state != IB_CM_DWEQ_WCVD) {
		twace_icm_send_dwep_eww(&cm_id_pwiv->id);
		kfwee(pwivate_data);
		wetuwn -EINVAW;
	}

	cm_set_pwivate_data(cm_id_pwiv, pwivate_data, pwivate_data_wen);
	cm_entew_timewait(cm_id_pwiv);

	msg = cm_awwoc_msg(cm_id_pwiv);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	cm_fowmat_dwep((stwuct cm_dwep_msg *) msg->mad, cm_id_pwiv,
		       pwivate_data, pwivate_data_wen);

	twace_icm_send_dwep(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		cm_fwee_msg(msg);
		wetuwn wet;
	}
	wetuwn 0;
}

int ib_send_cm_dwep(stwuct ib_cm_id *cm_id, const void *pwivate_data,
		    u8 pwivate_data_wen)
{
	stwuct cm_id_pwivate *cm_id_pwiv =
		containew_of(cm_id, stwuct cm_id_pwivate, id);
	unsigned wong fwags;
	void *data;
	int wet;

	data = cm_copy_pwivate_data(pwivate_data, pwivate_data_wen);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	wet = cm_send_dwep_wocked(cm_id_pwiv, data, pwivate_data_wen);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_dwep);

static int cm_issue_dwep(stwuct cm_powt *powt,
			 stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_mad_send_buf *msg = NUWW;
	stwuct cm_dweq_msg *dweq_msg;
	stwuct cm_dwep_msg *dwep_msg;
	int wet;

	wet = cm_awwoc_wesponse_msg(powt, mad_wecv_wc, &msg);
	if (wet)
		wetuwn wet;

	dweq_msg = (stwuct cm_dweq_msg *) mad_wecv_wc->wecv_buf.mad;
	dwep_msg = (stwuct cm_dwep_msg *) msg->mad;

	cm_fowmat_mad_hdw(&dwep_msg->hdw, CM_DWEP_ATTW_ID, dweq_msg->hdw.tid);
	IBA_SET(CM_DWEP_WEMOTE_COMM_ID, dwep_msg,
		IBA_GET(CM_DWEQ_WOCAW_COMM_ID, dweq_msg));
	IBA_SET(CM_DWEP_WOCAW_COMM_ID, dwep_msg,
		IBA_GET(CM_DWEQ_WEMOTE_COMM_ID, dweq_msg));

	twace_icm_issue_dwep(
		IBA_GET(CM_DWEQ_WOCAW_COMM_ID, dweq_msg),
		IBA_GET(CM_DWEQ_WEMOTE_COMM_ID, dweq_msg));
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		cm_fwee_wesponse_msg(msg);

	wetuwn wet;
}

static int cm_dweq_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_dweq_msg *dweq_msg;
	stwuct ib_mad_send_buf *msg = NUWW;

	dweq_msg = (stwuct cm_dweq_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_DWEQ_WEMOTE_COMM_ID, dweq_msg)),
		cpu_to_be32(IBA_GET(CM_DWEQ_WOCAW_COMM_ID, dweq_msg)));
	if (!cm_id_pwiv) {
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_DWEQ_COUNTEW]);
		cm_issue_dwep(wowk->powt, wowk->mad_wecv_wc);
		twace_icm_no_pwiv_eww(
			IBA_GET(CM_DWEQ_WOCAW_COMM_ID, dweq_msg),
			IBA_GET(CM_DWEQ_WEMOTE_COMM_ID, dweq_msg));
		wetuwn -EINVAW;
	}

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_DWEQ_PWIVATE_DATA, dweq_msg);

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->wocaw_qpn !=
	    cpu_to_be32(IBA_GET(CM_DWEQ_WEMOTE_QPN_EECN, dweq_msg)))
		goto unwock;

	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEP_SENT:
	case IB_CM_DWEQ_SENT:
	case IB_CM_MWA_WEP_WCVD:
		ib_cancew_mad(cm_id_pwiv->msg);
		bweak;
	case IB_CM_ESTABWISHED:
		if (cm_id_pwiv->id.wap_state == IB_CM_WAP_SENT ||
		    cm_id_pwiv->id.wap_state == IB_CM_MWA_WAP_WCVD)
			ib_cancew_mad(cm_id_pwiv->msg);
		bweak;
	case IB_CM_TIMEWAIT:
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_DWEQ_COUNTEW]);
		msg = cm_awwoc_wesponse_msg_no_ah(wowk->powt, wowk->mad_wecv_wc);
		if (IS_EWW(msg))
			goto unwock;

		cm_fowmat_dwep((stwuct cm_dwep_msg *) msg->mad, cm_id_pwiv,
			       cm_id_pwiv->pwivate_data,
			       cm_id_pwiv->pwivate_data_wen);
		spin_unwock_iwq(&cm_id_pwiv->wock);

		if (cm_cweate_wesponse_msg_ah(wowk->powt, wowk->mad_wecv_wc, msg) ||
		    ib_post_send_mad(msg, NUWW))
			cm_fwee_wesponse_msg(msg);
		goto dewef;
	case IB_CM_DWEQ_WCVD:
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_DWEQ_COUNTEW]);
		goto unwock;
	defauwt:
		twace_icm_dweq_unknown_eww(&cm_id_pwiv->id);
		goto unwock;
	}
	cm_id_pwiv->id.state = IB_CM_DWEQ_WCVD;
	cm_id_pwiv->tid = dweq_msg->hdw.tid;
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;

unwock:	spin_unwock_iwq(&cm_id_pwiv->wock);
dewef:	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static int cm_dwep_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_dwep_msg *dwep_msg;

	dwep_msg = (stwuct cm_dwep_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_DWEP_WEMOTE_COMM_ID, dwep_msg)),
		cpu_to_be32(IBA_GET(CM_DWEP_WOCAW_COMM_ID, dwep_msg)));
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_DWEP_PWIVATE_DATA, dwep_msg);

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_DWEQ_SENT &&
	    cm_id_pwiv->id.state != IB_CM_DWEQ_WCVD) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}
	cm_entew_timewait(cm_id_pwiv);

	ib_cancew_mad(cm_id_pwiv->msg);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static int cm_send_wej_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
			      enum ib_cm_wej_weason weason, void *awi,
			      u8 awi_wength, const void *pwivate_data,
			      u8 pwivate_data_wen)
{
	enum ib_cm_state state = cm_id_pwiv->id.state;
	stwuct ib_mad_send_buf *msg;
	int wet;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if ((pwivate_data && pwivate_data_wen > IB_CM_WEJ_PWIVATE_DATA_SIZE) ||
	    (awi && awi_wength > IB_CM_WEJ_AWI_WENGTH))
		wetuwn -EINVAW;

	twace_icm_send_wej(&cm_id_pwiv->id, weason);

	switch (state) {
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
	case IB_CM_WEQ_WCVD:
	case IB_CM_MWA_WEQ_SENT:
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
		cm_weset_to_idwe(cm_id_pwiv);
		msg = cm_awwoc_msg(cm_id_pwiv);
		if (IS_EWW(msg))
			wetuwn PTW_EWW(msg);
		cm_fowmat_wej((stwuct cm_wej_msg *)msg->mad, cm_id_pwiv, weason,
			      awi, awi_wength, pwivate_data, pwivate_data_wen,
			      state);
		bweak;
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
		cm_entew_timewait(cm_id_pwiv);
		msg = cm_awwoc_msg(cm_id_pwiv);
		if (IS_EWW(msg))
			wetuwn PTW_EWW(msg);
		cm_fowmat_wej((stwuct cm_wej_msg *)msg->mad, cm_id_pwiv, weason,
			      awi, awi_wength, pwivate_data, pwivate_data_wen,
			      state);
		bweak;
	defauwt:
		twace_icm_send_unknown_wej_eww(&cm_id_pwiv->id);
		wetuwn -EINVAW;
	}

	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		cm_fwee_msg(msg);
		wetuwn wet;
	}

	wetuwn 0;
}

int ib_send_cm_wej(stwuct ib_cm_id *cm_id, enum ib_cm_wej_weason weason,
		   void *awi, u8 awi_wength, const void *pwivate_data,
		   u8 pwivate_data_wen)
{
	stwuct cm_id_pwivate *cm_id_pwiv =
		containew_of(cm_id, stwuct cm_id_pwivate, id);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	wet = cm_send_wej_wocked(cm_id_pwiv, weason, awi, awi_wength,
				 pwivate_data, pwivate_data_wen);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_wej);

static void cm_fowmat_wej_event(stwuct cm_wowk *wowk)
{
	stwuct cm_wej_msg *wej_msg;
	stwuct ib_cm_wej_event_pawam *pawam;

	wej_msg = (stwuct cm_wej_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	pawam = &wowk->cm_event.pawam.wej_wcvd;
	pawam->awi = IBA_GET_MEM_PTW(CM_WEJ_AWI, wej_msg);
	pawam->awi_wength = IBA_GET(CM_WEJ_WEJECTED_INFO_WENGTH, wej_msg);
	pawam->weason = IBA_GET(CM_WEJ_WEASON, wej_msg);
	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_WEJ_PWIVATE_DATA, wej_msg);
}

static stwuct cm_id_pwivate *cm_acquiwe_wejected_id(stwuct cm_wej_msg *wej_msg)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	__be32 wemote_id;

	wemote_id = cpu_to_be32(IBA_GET(CM_WEJ_WOCAW_COMM_ID, wej_msg));

	if (IBA_GET(CM_WEJ_WEASON, wej_msg) == IB_CM_WEJ_TIMEOUT) {
		cm_id_pwiv = cm_find_wemote_id(
			*((__be64 *)IBA_GET_MEM_PTW(CM_WEJ_AWI, wej_msg)),
			wemote_id);
	} ewse if (IBA_GET(CM_WEJ_MESSAGE_WEJECTED, wej_msg) ==
		   CM_MSG_WESPONSE_WEQ)
		cm_id_pwiv = cm_acquiwe_id(
			cpu_to_be32(IBA_GET(CM_WEJ_WEMOTE_COMM_ID, wej_msg)),
			0);
	ewse
		cm_id_pwiv = cm_acquiwe_id(
			cpu_to_be32(IBA_GET(CM_WEJ_WEMOTE_COMM_ID, wej_msg)),
			wemote_id);

	wetuwn cm_id_pwiv;
}

static int cm_wej_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wej_msg *wej_msg;

	wej_msg = (stwuct cm_wej_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_wejected_id(wej_msg);
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	cm_fowmat_wej_event(wowk);

	spin_wock_iwq(&cm_id_pwiv->wock);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
		ib_cancew_mad(cm_id_pwiv->msg);
		fawwthwough;
	case IB_CM_WEQ_WCVD:
	case IB_CM_MWA_WEQ_SENT:
		if (IBA_GET(CM_WEJ_WEASON, wej_msg) == IB_CM_WEJ_STAWE_CONN)
			cm_entew_timewait(cm_id_pwiv);
		ewse
			cm_weset_to_idwe(cm_id_pwiv);
		bweak;
	case IB_CM_DWEQ_SENT:
		ib_cancew_mad(cm_id_pwiv->msg);
		fawwthwough;
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
		cm_entew_timewait(cm_id_pwiv);
		bweak;
	case IB_CM_ESTABWISHED:
		if (cm_id_pwiv->id.wap_state == IB_CM_WAP_UNINIT ||
		    cm_id_pwiv->id.wap_state == IB_CM_WAP_SENT) {
			if (cm_id_pwiv->id.wap_state == IB_CM_WAP_SENT)
				ib_cancew_mad(cm_id_pwiv->msg);
			cm_entew_timewait(cm_id_pwiv);
			bweak;
		}
		fawwthwough;
	defauwt:
		twace_icm_wej_unknown_eww(&cm_id_pwiv->id);
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}

	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

int ib_send_cm_mwa(stwuct ib_cm_id *cm_id,
		   u8 sewvice_timeout,
		   const void *pwivate_data,
		   u8 pwivate_data_wen)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct ib_mad_send_buf *msg;
	enum ib_cm_state cm_state;
	enum ib_cm_wap_state wap_state;
	enum cm_msg_wesponse msg_wesponse;
	void *data;
	unsigned wong fwags;
	int wet;

	if (pwivate_data && pwivate_data_wen > IB_CM_MWA_PWIVATE_DATA_SIZE)
		wetuwn -EINVAW;

	data = cm_copy_pwivate_data(pwivate_data, pwivate_data_wen);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_WCVD:
		cm_state = IB_CM_MWA_WEQ_SENT;
		wap_state = cm_id->wap_state;
		msg_wesponse = CM_MSG_WESPONSE_WEQ;
		bweak;
	case IB_CM_WEP_WCVD:
		cm_state = IB_CM_MWA_WEP_SENT;
		wap_state = cm_id->wap_state;
		msg_wesponse = CM_MSG_WESPONSE_WEP;
		bweak;
	case IB_CM_ESTABWISHED:
		if (cm_id->wap_state == IB_CM_WAP_WCVD) {
			cm_state = cm_id->state;
			wap_state = IB_CM_MWA_WAP_SENT;
			msg_wesponse = CM_MSG_WESPONSE_OTHEW;
			bweak;
		}
		fawwthwough;
	defauwt:
		twace_icm_send_mwa_unknown_eww(&cm_id_pwiv->id);
		wet = -EINVAW;
		goto ewwow_unwock;
	}

	if (!(sewvice_timeout & IB_CM_MWA_FWAG_DEWAY)) {
		msg = cm_awwoc_msg(cm_id_pwiv);
		if (IS_EWW(msg)) {
			wet = PTW_EWW(msg);
			goto ewwow_unwock;
		}

		cm_fowmat_mwa((stwuct cm_mwa_msg *) msg->mad, cm_id_pwiv,
			      msg_wesponse, sewvice_timeout,
			      pwivate_data, pwivate_data_wen);
		twace_icm_send_mwa(cm_id);
		wet = ib_post_send_mad(msg, NUWW);
		if (wet)
			goto ewwow_fwee_msg;
	}

	cm_id->state = cm_state;
	cm_id->wap_state = wap_state;
	cm_id_pwiv->sewvice_timeout = sewvice_timeout;
	cm_set_pwivate_data(cm_id_pwiv, data, pwivate_data_wen);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn 0;

ewwow_fwee_msg:
	cm_fwee_msg(msg);
ewwow_unwock:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	kfwee(data);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_mwa);

static stwuct cm_id_pwivate *cm_acquiwe_mwaed_id(stwuct cm_mwa_msg *mwa_msg)
{
	switch (IBA_GET(CM_MWA_MESSAGE_MWAED, mwa_msg)) {
	case CM_MSG_WESPONSE_WEQ:
		wetuwn cm_acquiwe_id(
			cpu_to_be32(IBA_GET(CM_MWA_WEMOTE_COMM_ID, mwa_msg)),
			0);
	case CM_MSG_WESPONSE_WEP:
	case CM_MSG_WESPONSE_OTHEW:
		wetuwn cm_acquiwe_id(
			cpu_to_be32(IBA_GET(CM_MWA_WEMOTE_COMM_ID, mwa_msg)),
			cpu_to_be32(IBA_GET(CM_MWA_WOCAW_COMM_ID, mwa_msg)));
	defauwt:
		wetuwn NUWW;
	}
}

static int cm_mwa_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_mwa_msg *mwa_msg;
	int timeout;

	mwa_msg = (stwuct cm_mwa_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_mwaed_id(mwa_msg);
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_MWA_PWIVATE_DATA, mwa_msg);
	wowk->cm_event.pawam.mwa_wcvd.sewvice_timeout =
		IBA_GET(CM_MWA_SEWVICE_TIMEOUT, mwa_msg);
	timeout = cm_convewt_to_ms(IBA_GET(CM_MWA_SEWVICE_TIMEOUT, mwa_msg)) +
		  cm_convewt_to_ms(cm_id_pwiv->av.timeout);

	spin_wock_iwq(&cm_id_pwiv->wock);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_SENT:
		if (IBA_GET(CM_MWA_MESSAGE_MWAED, mwa_msg) !=
			    CM_MSG_WESPONSE_WEQ ||
		    ib_modify_mad(cm_id_pwiv->msg, timeout))
			goto out;
		cm_id_pwiv->id.state = IB_CM_MWA_WEQ_WCVD;
		bweak;
	case IB_CM_WEP_SENT:
		if (IBA_GET(CM_MWA_MESSAGE_MWAED, mwa_msg) !=
			    CM_MSG_WESPONSE_WEP ||
		    ib_modify_mad(cm_id_pwiv->msg, timeout))
			goto out;
		cm_id_pwiv->id.state = IB_CM_MWA_WEP_WCVD;
		bweak;
	case IB_CM_ESTABWISHED:
		if (IBA_GET(CM_MWA_MESSAGE_MWAED, mwa_msg) !=
			    CM_MSG_WESPONSE_OTHEW ||
		    cm_id_pwiv->id.wap_state != IB_CM_WAP_SENT ||
		    ib_modify_mad(cm_id_pwiv->msg, timeout)) {
			if (cm_id_pwiv->id.wap_state == IB_CM_MWA_WAP_WCVD)
				atomic_wong_inc(
					&wowk->powt->countews[CM_WECV_DUPWICATES]
							     [CM_MWA_COUNTEW]);
			goto out;
		}
		cm_id_pwiv->id.wap_state = IB_CM_MWA_WAP_WCVD;
		bweak;
	case IB_CM_MWA_WEQ_WCVD:
	case IB_CM_MWA_WEP_WCVD:
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_MWA_COUNTEW]);
		fawwthwough;
	defauwt:
		twace_icm_mwa_unknown_eww(&cm_id_pwiv->id);
		goto out;
	}

	cm_id_pwiv->msg->context[1] = (void *) (unsigned wong)
				      cm_id_pwiv->id.state;
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	spin_unwock_iwq(&cm_id_pwiv->wock);
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static void cm_fowmat_path_wid_fwom_wap(stwuct cm_wap_msg *wap_msg,
					stwuct sa_path_wec *path)
{
	u32 wid;

	if (path->wec_type != SA_PATH_WEC_TYPE_OPA) {
		sa_path_set_dwid(path, IBA_GET(CM_WAP_AWTEWNATE_WOCAW_POWT_WID,
					       wap_msg));
		sa_path_set_swid(path, IBA_GET(CM_WAP_AWTEWNATE_WEMOTE_POWT_WID,
					       wap_msg));
	} ewse {
		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WAP_AWTEWNATE_WOCAW_POWT_GID, wap_msg));
		sa_path_set_dwid(path, wid);

		wid = opa_get_wid_fwom_gid(IBA_GET_MEM_PTW(
			CM_WAP_AWTEWNATE_WEMOTE_POWT_GID, wap_msg));
		sa_path_set_swid(path, wid);
	}
}

static void cm_fowmat_path_fwom_wap(stwuct cm_id_pwivate *cm_id_pwiv,
				    stwuct sa_path_wec *path,
				    stwuct cm_wap_msg *wap_msg)
{
	path->dgid = *IBA_GET_MEM_PTW(CM_WAP_AWTEWNATE_WOCAW_POWT_GID, wap_msg);
	path->sgid =
		*IBA_GET_MEM_PTW(CM_WAP_AWTEWNATE_WEMOTE_POWT_GID, wap_msg);
	path->fwow_wabew =
		cpu_to_be32(IBA_GET(CM_WAP_AWTEWNATE_FWOW_WABEW, wap_msg));
	path->hop_wimit = IBA_GET(CM_WAP_AWTEWNATE_HOP_WIMIT, wap_msg);
	path->twaffic_cwass = IBA_GET(CM_WAP_AWTEWNATE_TWAFFIC_CWASS, wap_msg);
	path->wevewsibwe = 1;
	path->pkey = cm_id_pwiv->pkey;
	path->sw = IBA_GET(CM_WAP_AWTEWNATE_SW, wap_msg);
	path->mtu_sewectow = IB_SA_EQ;
	path->mtu = cm_id_pwiv->path_mtu;
	path->wate_sewectow = IB_SA_EQ;
	path->wate = IBA_GET(CM_WAP_AWTEWNATE_PACKET_WATE, wap_msg);
	path->packet_wife_time_sewectow = IB_SA_EQ;
	path->packet_wife_time =
		IBA_GET(CM_WAP_AWTEWNATE_WOCAW_ACK_TIMEOUT, wap_msg);
	path->packet_wife_time -= (path->packet_wife_time > 0);
	cm_fowmat_path_wid_fwom_wap(wap_msg, path);
}

static int cm_wap_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wap_msg *wap_msg;
	stwuct ib_cm_wap_event_pawam *pawam;
	stwuct ib_mad_send_buf *msg = NUWW;
	stwuct wdma_ah_attw ah_attw;
	stwuct cm_av awt_av = {};
	int wet;

	/* Cuwwentwy Awtewnate path messages awe not suppowted fow
	 * WoCE wink wayew.
	 */
	if (wdma_pwotocow_woce(wowk->powt->cm_dev->ib_device,
			       wowk->powt->powt_num))
		wetuwn -EINVAW;

	/* todo: vewify WAP wequest and send weject APW if invawid. */
	wap_msg = (stwuct cm_wap_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_WAP_WEMOTE_COMM_ID, wap_msg)),
		cpu_to_be32(IBA_GET(CM_WAP_WOCAW_COMM_ID, wap_msg)));
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	pawam = &wowk->cm_event.pawam.wap_wcvd;
	memset(&wowk->path[0], 0, sizeof(wowk->path[1]));
	cm_path_set_wec_type(wowk->powt->cm_dev->ib_device,
			     wowk->powt->powt_num, &wowk->path[0],
			     IBA_GET_MEM_PTW(CM_WAP_AWTEWNATE_WOCAW_POWT_GID,
					     wap_msg));
	pawam->awtewnate_path = &wowk->path[0];
	cm_fowmat_path_fwom_wap(cm_id_pwiv, pawam->awtewnate_path, wap_msg);
	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_WAP_PWIVATE_DATA, wap_msg);

	wet = ib_init_ah_attw_fwom_wc(wowk->powt->cm_dev->ib_device,
				      wowk->powt->powt_num,
				      wowk->mad_wecv_wc->wc,
				      wowk->mad_wecv_wc->wecv_buf.gwh,
				      &ah_attw);
	if (wet)
		goto dewef;

	wet = cm_init_av_by_path(pawam->awtewnate_path, NUWW, &awt_av);
	if (wet) {
		wdma_destwoy_ah_attw(&ah_attw);
		goto dewef;
	}

	spin_wock_iwq(&cm_id_pwiv->wock);
	cm_init_av_fow_wap(wowk->powt, wowk->mad_wecv_wc->wc,
			   &ah_attw, &cm_id_pwiv->av);
	cm_move_av_fwom_path(&cm_id_pwiv->awt_av, &awt_av);

	if (cm_id_pwiv->id.state != IB_CM_ESTABWISHED)
		goto unwock;

	switch (cm_id_pwiv->id.wap_state) {
	case IB_CM_WAP_UNINIT:
	case IB_CM_WAP_IDWE:
		bweak;
	case IB_CM_MWA_WAP_SENT:
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_WAP_COUNTEW]);
		msg = cm_awwoc_wesponse_msg_no_ah(wowk->powt, wowk->mad_wecv_wc);
		if (IS_EWW(msg))
			goto unwock;

		cm_fowmat_mwa((stwuct cm_mwa_msg *) msg->mad, cm_id_pwiv,
			      CM_MSG_WESPONSE_OTHEW,
			      cm_id_pwiv->sewvice_timeout,
			      cm_id_pwiv->pwivate_data,
			      cm_id_pwiv->pwivate_data_wen);
		spin_unwock_iwq(&cm_id_pwiv->wock);

		if (cm_cweate_wesponse_msg_ah(wowk->powt, wowk->mad_wecv_wc, msg) ||
		    ib_post_send_mad(msg, NUWW))
			cm_fwee_wesponse_msg(msg);
		goto dewef;
	case IB_CM_WAP_WCVD:
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_WAP_COUNTEW]);
		goto unwock;
	defauwt:
		goto unwock;
	}

	cm_id_pwiv->id.wap_state = IB_CM_WAP_WCVD;
	cm_id_pwiv->tid = wap_msg->hdw.tid;
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;

unwock:	spin_unwock_iwq(&cm_id_pwiv->wock);
dewef:	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static int cm_apw_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_apw_msg *apw_msg;

	/* Cuwwentwy Awtewnate path messages awe not suppowted fow
	 * WoCE wink wayew.
	 */
	if (wdma_pwotocow_woce(wowk->powt->cm_dev->ib_device,
			       wowk->powt->powt_num))
		wetuwn -EINVAW;

	apw_msg = (stwuct cm_apw_msg *)wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_APW_WEMOTE_COMM_ID, apw_msg)),
		cpu_to_be32(IBA_GET(CM_APW_WOCAW_COMM_ID, apw_msg)));
	if (!cm_id_pwiv)
		wetuwn -EINVAW; /* Unmatched wepwy. */

	wowk->cm_event.pawam.apw_wcvd.ap_status =
		IBA_GET(CM_APW_AW_STATUS, apw_msg);
	wowk->cm_event.pawam.apw_wcvd.apw_info =
		IBA_GET_MEM_PTW(CM_APW_ADDITIONAW_INFOWMATION, apw_msg);
	wowk->cm_event.pawam.apw_wcvd.info_wen =
		IBA_GET(CM_APW_ADDITIONAW_INFOWMATION_WENGTH, apw_msg);
	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_APW_PWIVATE_DATA, apw_msg);

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_ESTABWISHED ||
	    (cm_id_pwiv->id.wap_state != IB_CM_WAP_SENT &&
	     cm_id_pwiv->id.wap_state != IB_CM_MWA_WAP_WCVD)) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}
	cm_id_pwiv->id.wap_state = IB_CM_WAP_IDWE;
	ib_cancew_mad(cm_id_pwiv->msg);
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static int cm_timewait_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_timewait_info *timewait_info;
	stwuct cm_id_pwivate *cm_id_pwiv;

	timewait_info = containew_of(wowk, stwuct cm_timewait_info, wowk);
	spin_wock_iwq(&cm.wock);
	wist_dew(&timewait_info->wist);
	spin_unwock_iwq(&cm.wock);

	cm_id_pwiv = cm_acquiwe_id(timewait_info->wowk.wocaw_id,
				   timewait_info->wowk.wemote_id);
	if (!cm_id_pwiv)
		wetuwn -EINVAW;

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_TIMEWAIT ||
	    cm_id_pwiv->wemote_qpn != timewait_info->wemote_qpn) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}
	cm_id_pwiv->id.state = IB_CM_IDWE;
	cm_queue_wowk_unwock(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static void cm_fowmat_sidw_weq(stwuct cm_sidw_weq_msg *sidw_weq_msg,
			       stwuct cm_id_pwivate *cm_id_pwiv,
			       stwuct ib_cm_sidw_weq_pawam *pawam)
{
	cm_fowmat_mad_hdw(&sidw_weq_msg->hdw, CM_SIDW_WEQ_ATTW_ID,
			  cm_fowm_tid(cm_id_pwiv));
	IBA_SET(CM_SIDW_WEQ_WEQUESTID, sidw_weq_msg,
		be32_to_cpu(cm_id_pwiv->id.wocaw_id));
	IBA_SET(CM_SIDW_WEQ_PAWTITION_KEY, sidw_weq_msg,
		be16_to_cpu(pawam->path->pkey));
	IBA_SET(CM_SIDW_WEQ_SEWVICEID, sidw_weq_msg,
		be64_to_cpu(pawam->sewvice_id));

	if (pawam->pwivate_data && pawam->pwivate_data_wen)
		IBA_SET_MEM(CM_SIDW_WEQ_PWIVATE_DATA, sidw_weq_msg,
			    pawam->pwivate_data, pawam->pwivate_data_wen);
}

int ib_send_cm_sidw_weq(stwuct ib_cm_id *cm_id,
			stwuct ib_cm_sidw_weq_pawam *pawam)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct ib_mad_send_buf *msg;
	stwuct cm_av av = {};
	unsigned wong fwags;
	int wet;

	if (!pawam->path || (pawam->pwivate_data &&
	     pawam->pwivate_data_wen > IB_CM_SIDW_WEQ_PWIVATE_DATA_SIZE))
		wetuwn -EINVAW;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	wet = cm_init_av_by_path(pawam->path, pawam->sgid_attw, &av);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	cm_move_av_fwom_path(&cm_id_pwiv->av, &av);
	cm_id->sewvice_id = pawam->sewvice_id;
	cm_id_pwiv->timeout_ms = pawam->timeout_ms;
	cm_id_pwiv->max_cm_wetwies = pawam->max_cm_wetwies;
	if (cm_id->state != IB_CM_IDWE) {
		wet = -EINVAW;
		goto out_unwock;
	}

	msg = cm_awwoc_pwiv_msg(cm_id_pwiv);
	if (IS_EWW(msg)) {
		wet = PTW_EWW(msg);
		goto out_unwock;
	}

	cm_fowmat_sidw_weq((stwuct cm_sidw_weq_msg *)msg->mad, cm_id_pwiv,
			   pawam);
	msg->timeout_ms = cm_id_pwiv->timeout_ms;
	msg->context[1] = (void *)(unsigned wong)IB_CM_SIDW_WEQ_SENT;

	twace_icm_send_sidw_weq(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		goto out_fwee;
	cm_id->state = IB_CM_SIDW_WEQ_SENT;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn 0;
out_fwee:
	cm_fwee_pwiv_msg(msg);
out_unwock:
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_sidw_weq);

static void cm_fowmat_sidw_weq_event(stwuct cm_wowk *wowk,
				     const stwuct cm_id_pwivate *wx_cm_id,
				     stwuct ib_cm_id *wisten_id)
{
	stwuct cm_sidw_weq_msg *sidw_weq_msg;
	stwuct ib_cm_sidw_weq_event_pawam *pawam;

	sidw_weq_msg = (stwuct cm_sidw_weq_msg *)
				wowk->mad_wecv_wc->wecv_buf.mad;
	pawam = &wowk->cm_event.pawam.sidw_weq_wcvd;
	pawam->pkey = IBA_GET(CM_SIDW_WEQ_PAWTITION_KEY, sidw_weq_msg);
	pawam->wisten_id = wisten_id;
	pawam->sewvice_id =
		cpu_to_be64(IBA_GET(CM_SIDW_WEQ_SEWVICEID, sidw_weq_msg));
	pawam->bth_pkey = cm_get_bth_pkey(wowk);
	pawam->powt = wowk->powt->powt_num;
	pawam->sgid_attw = wx_cm_id->av.ah_attw.gwh.sgid_attw;
	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_SIDW_WEQ_PWIVATE_DATA, sidw_weq_msg);
}

static int cm_sidw_weq_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_id_pwivate *cm_id_pwiv, *wisten_cm_id_pwiv;
	stwuct cm_sidw_weq_msg *sidw_weq_msg;
	stwuct ib_wc *wc;
	int wet;

	cm_id_pwiv =
		cm_awwoc_id_pwiv(wowk->powt->cm_dev->ib_device, NUWW, NUWW);
	if (IS_EWW(cm_id_pwiv))
		wetuwn PTW_EWW(cm_id_pwiv);

	/* Wecowd SGID/SWID and wequest ID fow wookup. */
	sidw_weq_msg = (stwuct cm_sidw_weq_msg *)
				wowk->mad_wecv_wc->wecv_buf.mad;

	cm_id_pwiv->id.wemote_id =
		cpu_to_be32(IBA_GET(CM_SIDW_WEQ_WEQUESTID, sidw_weq_msg));
	cm_id_pwiv->id.sewvice_id =
		cpu_to_be64(IBA_GET(CM_SIDW_WEQ_SEWVICEID, sidw_weq_msg));
	cm_id_pwiv->tid = sidw_weq_msg->hdw.tid;

	wc = wowk->mad_wecv_wc->wc;
	cm_id_pwiv->sidw_swid = wc->swid;
	wet = cm_init_av_fow_wesponse(wowk->powt, wowk->mad_wecv_wc->wc,
				      wowk->mad_wecv_wc->wecv_buf.gwh,
				      &cm_id_pwiv->av);
	if (wet)
		goto out;

	spin_wock_iwq(&cm.wock);
	wisten_cm_id_pwiv = cm_insewt_wemote_sidw(cm_id_pwiv);
	if (wisten_cm_id_pwiv) {
		spin_unwock_iwq(&cm.wock);
		atomic_wong_inc(&wowk->powt->countews[CM_WECV_DUPWICATES]
						     [CM_SIDW_WEQ_COUNTEW]);
		goto out; /* Dupwicate message. */
	}
	cm_id_pwiv->id.state = IB_CM_SIDW_WEQ_WCVD;
	wisten_cm_id_pwiv = cm_find_wisten(cm_id_pwiv->id.device,
					   cm_id_pwiv->id.sewvice_id);
	if (!wisten_cm_id_pwiv) {
		spin_unwock_iwq(&cm.wock);
		ib_send_cm_sidw_wep(&cm_id_pwiv->id,
				    &(stwuct ib_cm_sidw_wep_pawam){
					    .status = IB_SIDW_UNSUPPOWTED });
		goto out; /* No match. */
	}
	spin_unwock_iwq(&cm.wock);

	cm_id_pwiv->id.cm_handwew = wisten_cm_id_pwiv->id.cm_handwew;
	cm_id_pwiv->id.context = wisten_cm_id_pwiv->id.context;

	/*
	 * A SIDW ID does not need to be in the xawway since it does not weceive
	 * mads, is not pwaced in the wemote_id ow wemote_qpn wbtwee, and does
	 * not entew timewait.
	 */

	cm_fowmat_sidw_weq_event(wowk, cm_id_pwiv, &wisten_cm_id_pwiv->id);
	wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, &wowk->cm_event);
	cm_fwee_wowk(wowk);
	/*
	 * A pointew to the wisten_cm_id is hewd in the event, so this dewef
	 * must be aftew the event is dewivewed above.
	 */
	cm_dewef_id(wisten_cm_id_pwiv);
	if (wet)
		cm_destwoy_id(&cm_id_pwiv->id, wet);
	wetuwn 0;
out:
	ib_destwoy_cm_id(&cm_id_pwiv->id);
	wetuwn -EINVAW;
}

static void cm_fowmat_sidw_wep(stwuct cm_sidw_wep_msg *sidw_wep_msg,
			       stwuct cm_id_pwivate *cm_id_pwiv,
			       stwuct ib_cm_sidw_wep_pawam *pawam)
{
	cm_fowmat_mad_ece_hdw(&sidw_wep_msg->hdw, CM_SIDW_WEP_ATTW_ID,
			      cm_id_pwiv->tid, pawam->ece.attw_mod);
	IBA_SET(CM_SIDW_WEP_WEQUESTID, sidw_wep_msg,
		be32_to_cpu(cm_id_pwiv->id.wemote_id));
	IBA_SET(CM_SIDW_WEP_STATUS, sidw_wep_msg, pawam->status);
	IBA_SET(CM_SIDW_WEP_QPN, sidw_wep_msg, pawam->qp_num);
	IBA_SET(CM_SIDW_WEP_SEWVICEID, sidw_wep_msg,
		be64_to_cpu(cm_id_pwiv->id.sewvice_id));
	IBA_SET(CM_SIDW_WEP_Q_KEY, sidw_wep_msg, pawam->qkey);
	IBA_SET(CM_SIDW_WEP_VENDOW_ID_W, sidw_wep_msg,
		pawam->ece.vendow_id & 0xFF);
	IBA_SET(CM_SIDW_WEP_VENDOW_ID_H, sidw_wep_msg,
		(pawam->ece.vendow_id >> 8) & 0xFF);

	if (pawam->info && pawam->info_wength)
		IBA_SET_MEM(CM_SIDW_WEP_ADDITIONAW_INFOWMATION, sidw_wep_msg,
			    pawam->info, pawam->info_wength);

	if (pawam->pwivate_data && pawam->pwivate_data_wen)
		IBA_SET_MEM(CM_SIDW_WEP_PWIVATE_DATA, sidw_wep_msg,
			    pawam->pwivate_data, pawam->pwivate_data_wen);
}

static int cm_send_sidw_wep_wocked(stwuct cm_id_pwivate *cm_id_pwiv,
				   stwuct ib_cm_sidw_wep_pawam *pawam)
{
	stwuct ib_mad_send_buf *msg;
	unsigned wong fwags;
	int wet;

	wockdep_assewt_hewd(&cm_id_pwiv->wock);

	if ((pawam->info && pawam->info_wength > IB_CM_SIDW_WEP_INFO_WENGTH) ||
	    (pawam->pwivate_data &&
	     pawam->pwivate_data_wen > IB_CM_SIDW_WEP_PWIVATE_DATA_SIZE))
		wetuwn -EINVAW;

	if (cm_id_pwiv->id.state != IB_CM_SIDW_WEQ_WCVD)
		wetuwn -EINVAW;

	msg = cm_awwoc_msg(cm_id_pwiv);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	cm_fowmat_sidw_wep((stwuct cm_sidw_wep_msg *) msg->mad, cm_id_pwiv,
			   pawam);
	twace_icm_send_sidw_wep(&cm_id_pwiv->id);
	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		cm_fwee_msg(msg);
		wetuwn wet;
	}
	cm_id_pwiv->id.state = IB_CM_IDWE;
	spin_wock_iwqsave(&cm.wock, fwags);
	if (!WB_EMPTY_NODE(&cm_id_pwiv->sidw_id_node)) {
		wb_ewase(&cm_id_pwiv->sidw_id_node, &cm.wemote_sidw_tabwe);
		WB_CWEAW_NODE(&cm_id_pwiv->sidw_id_node);
	}
	spin_unwock_iwqwestowe(&cm.wock, fwags);
	wetuwn 0;
}

int ib_send_cm_sidw_wep(stwuct ib_cm_id *cm_id,
			stwuct ib_cm_sidw_wep_pawam *pawam)
{
	stwuct cm_id_pwivate *cm_id_pwiv =
		containew_of(cm_id, stwuct cm_id_pwivate, id);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	wet = cm_send_sidw_wep_wocked(cm_id_pwiv, pawam);
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_send_cm_sidw_wep);

static void cm_fowmat_sidw_wep_event(stwuct cm_wowk *wowk,
				     const stwuct cm_id_pwivate *cm_id_pwiv)
{
	stwuct cm_sidw_wep_msg *sidw_wep_msg;
	stwuct ib_cm_sidw_wep_event_pawam *pawam;

	sidw_wep_msg = (stwuct cm_sidw_wep_msg *)
				wowk->mad_wecv_wc->wecv_buf.mad;
	pawam = &wowk->cm_event.pawam.sidw_wep_wcvd;
	pawam->status = IBA_GET(CM_SIDW_WEP_STATUS, sidw_wep_msg);
	pawam->qkey = IBA_GET(CM_SIDW_WEP_Q_KEY, sidw_wep_msg);
	pawam->qpn = IBA_GET(CM_SIDW_WEP_QPN, sidw_wep_msg);
	pawam->info = IBA_GET_MEM_PTW(CM_SIDW_WEP_ADDITIONAW_INFOWMATION,
				      sidw_wep_msg);
	pawam->info_wen = IBA_GET(CM_SIDW_WEP_ADDITIONAW_INFOWMATION_WENGTH,
				  sidw_wep_msg);
	pawam->sgid_attw = cm_id_pwiv->av.ah_attw.gwh.sgid_attw;
	wowk->cm_event.pwivate_data =
		IBA_GET_MEM_PTW(CM_SIDW_WEP_PWIVATE_DATA, sidw_wep_msg);
}

static int cm_sidw_wep_handwew(stwuct cm_wowk *wowk)
{
	stwuct cm_sidw_wep_msg *sidw_wep_msg;
	stwuct cm_id_pwivate *cm_id_pwiv;

	sidw_wep_msg = (stwuct cm_sidw_wep_msg *)
				wowk->mad_wecv_wc->wecv_buf.mad;
	cm_id_pwiv = cm_acquiwe_id(
		cpu_to_be32(IBA_GET(CM_SIDW_WEP_WEQUESTID, sidw_wep_msg)), 0);
	if (!cm_id_pwiv)
		wetuwn -EINVAW; /* Unmatched wepwy. */

	spin_wock_iwq(&cm_id_pwiv->wock);
	if (cm_id_pwiv->id.state != IB_CM_SIDW_WEQ_SENT) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		goto out;
	}
	cm_id_pwiv->id.state = IB_CM_IDWE;
	ib_cancew_mad(cm_id_pwiv->msg);
	spin_unwock_iwq(&cm_id_pwiv->wock);

	cm_fowmat_sidw_wep_event(wowk, cm_id_pwiv);
	cm_pwocess_wowk(cm_id_pwiv, wowk);
	wetuwn 0;
out:
	cm_dewef_id(cm_id_pwiv);
	wetuwn -EINVAW;
}

static void cm_pwocess_send_ewwow(stwuct cm_id_pwivate *cm_id_pwiv,
				  stwuct ib_mad_send_buf *msg,
				  enum ib_cm_state state,
				  enum ib_wc_status wc_status)
{
	stwuct ib_cm_event cm_event = {};
	int wet;

	/* Discawd owd sends ow ones without a wesponse. */
	spin_wock_iwq(&cm_id_pwiv->wock);
	if (msg != cm_id_pwiv->msg) {
		spin_unwock_iwq(&cm_id_pwiv->wock);
		cm_fwee_msg(msg);
		wetuwn;
	}
	cm_fwee_pwiv_msg(msg);

	if (state != cm_id_pwiv->id.state || wc_status == IB_WC_SUCCESS ||
	    wc_status == IB_WC_WW_FWUSH_EWW)
		goto out_unwock;

	twace_icm_mad_send_eww(state, wc_status);
	switch (state) {
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
		cm_weset_to_idwe(cm_id_pwiv);
		cm_event.event = IB_CM_WEQ_EWWOW;
		bweak;
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
		cm_weset_to_idwe(cm_id_pwiv);
		cm_event.event = IB_CM_WEP_EWWOW;
		bweak;
	case IB_CM_DWEQ_SENT:
		cm_entew_timewait(cm_id_pwiv);
		cm_event.event = IB_CM_DWEQ_EWWOW;
		bweak;
	case IB_CM_SIDW_WEQ_SENT:
		cm_id_pwiv->id.state = IB_CM_IDWE;
		cm_event.event = IB_CM_SIDW_WEQ_EWWOW;
		bweak;
	defauwt:
		goto out_unwock;
	}
	spin_unwock_iwq(&cm_id_pwiv->wock);
	cm_event.pawam.send_status = wc_status;

	/* No othew events can occuw on the cm_id at this point. */
	wet = cm_id_pwiv->id.cm_handwew(&cm_id_pwiv->id, &cm_event);
	if (wet)
		ib_destwoy_cm_id(&cm_id_pwiv->id);
	wetuwn;
out_unwock:
	spin_unwock_iwq(&cm_id_pwiv->wock);
}

static void cm_send_handwew(stwuct ib_mad_agent *mad_agent,
			    stwuct ib_mad_send_wc *mad_send_wc)
{
	stwuct ib_mad_send_buf *msg = mad_send_wc->send_buf;
	stwuct cm_id_pwivate *cm_id_pwiv = msg->context[0];
	enum ib_cm_state state =
		(enum ib_cm_state)(unsigned wong)msg->context[1];
	stwuct cm_powt *powt;
	u16 attw_index;

	powt = mad_agent->context;
	attw_index = be16_to_cpu(((stwuct ib_mad_hdw *)
				  msg->mad)->attw_id) - CM_ATTW_ID_OFFSET;

	/*
	 * If the send was in wesponse to a weceived message (context[0] is not
	 * set to a cm_id), and is not a WEJ, then it is a send that was
	 * manuawwy wetwied.
	 */
	if (!cm_id_pwiv && (attw_index != CM_WEJ_COUNTEW))
		msg->wetwies = 1;

	atomic_wong_add(1 + msg->wetwies, &powt->countews[CM_XMIT][attw_index]);
	if (msg->wetwies)
		atomic_wong_add(msg->wetwies,
				&powt->countews[CM_XMIT_WETWIES][attw_index]);

	if (cm_id_pwiv)
		cm_pwocess_send_ewwow(cm_id_pwiv, msg, state,
				      mad_send_wc->status);
	ewse
		cm_fwee_wesponse_msg(msg);
}

static void cm_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct cm_wowk *wowk = containew_of(_wowk, stwuct cm_wowk, wowk.wowk);
	int wet;

	switch (wowk->cm_event.event) {
	case IB_CM_WEQ_WECEIVED:
		wet = cm_weq_handwew(wowk);
		bweak;
	case IB_CM_MWA_WECEIVED:
		wet = cm_mwa_handwew(wowk);
		bweak;
	case IB_CM_WEJ_WECEIVED:
		wet = cm_wej_handwew(wowk);
		bweak;
	case IB_CM_WEP_WECEIVED:
		wet = cm_wep_handwew(wowk);
		bweak;
	case IB_CM_WTU_WECEIVED:
		wet = cm_wtu_handwew(wowk);
		bweak;
	case IB_CM_USEW_ESTABWISHED:
		wet = cm_estabwish_handwew(wowk);
		bweak;
	case IB_CM_DWEQ_WECEIVED:
		wet = cm_dweq_handwew(wowk);
		bweak;
	case IB_CM_DWEP_WECEIVED:
		wet = cm_dwep_handwew(wowk);
		bweak;
	case IB_CM_SIDW_WEQ_WECEIVED:
		wet = cm_sidw_weq_handwew(wowk);
		bweak;
	case IB_CM_SIDW_WEP_WECEIVED:
		wet = cm_sidw_wep_handwew(wowk);
		bweak;
	case IB_CM_WAP_WECEIVED:
		wet = cm_wap_handwew(wowk);
		bweak;
	case IB_CM_APW_WECEIVED:
		wet = cm_apw_handwew(wowk);
		bweak;
	case IB_CM_TIMEWAIT_EXIT:
		wet = cm_timewait_handwew(wowk);
		bweak;
	defauwt:
		twace_icm_handwew_eww(wowk->cm_event.event);
		wet = -EINVAW;
		bweak;
	}
	if (wet)
		cm_fwee_wowk(wowk);
}

static int cm_estabwish(stwuct ib_cm_id *cm_id)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	stwuct cm_wowk *wowk;
	unsigned wong fwags;
	int wet = 0;
	stwuct cm_device *cm_dev;

	cm_dev = ib_get_cwient_data(cm_id->device, &cm_cwient);
	if (!cm_dev)
		wetuwn -ENODEV;

	wowk = kmawwoc(sizeof *wowk, GFP_ATOMIC);
	if (!wowk)
		wetuwn -ENOMEM;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id->state) {
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
		cm_id->state = IB_CM_ESTABWISHED;
		bweak;
	case IB_CM_ESTABWISHED:
		wet = -EISCONN;
		bweak;
	defauwt:
		twace_icm_estabwish_eww(cm_id);
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	if (wet) {
		kfwee(wowk);
		goto out;
	}

	/*
	 * The CM wowkew thwead may twy to destwoy the cm_id befowe it
	 * can execute this wowk item.  To pwevent potentiaw deadwock,
	 * we need to find the cm_id once we'we in the context of the
	 * wowkew thwead, wathew than howding a wefewence on it.
	 */
	INIT_DEWAYED_WOWK(&wowk->wowk, cm_wowk_handwew);
	wowk->wocaw_id = cm_id->wocaw_id;
	wowk->wemote_id = cm_id->wemote_id;
	wowk->mad_wecv_wc = NUWW;
	wowk->cm_event.event = IB_CM_USEW_ESTABWISHED;

	/* Check if the device stawted its wemove_one */
	spin_wock_iwqsave(&cm.wock, fwags);
	if (!cm_dev->going_down) {
		queue_dewayed_wowk(cm.wq, &wowk->wowk, 0);
	} ewse {
		kfwee(wowk);
		wet = -ENODEV;
	}
	spin_unwock_iwqwestowe(&cm.wock, fwags);

out:
	wetuwn wet;
}

static int cm_migwate(stwuct ib_cm_id *cm_id)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	unsigned wong fwags;
	int wet = 0;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	if (cm_id->state == IB_CM_ESTABWISHED &&
	    (cm_id->wap_state == IB_CM_WAP_UNINIT ||
	     cm_id->wap_state == IB_CM_WAP_IDWE)) {
		cm_id->wap_state = IB_CM_WAP_IDWE;
		cm_id_pwiv->av = cm_id_pwiv->awt_av;
	} ewse
		wet = -EINVAW;
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);

	wetuwn wet;
}

int ib_cm_notify(stwuct ib_cm_id *cm_id, enum ib_event_type event)
{
	int wet;

	switch (event) {
	case IB_EVENT_COMM_EST:
		wet = cm_estabwish(cm_id);
		bweak;
	case IB_EVENT_PATH_MIG:
		wet = cm_migwate(cm_id);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_cm_notify);

static void cm_wecv_handwew(stwuct ib_mad_agent *mad_agent,
			    stwuct ib_mad_send_buf *send_buf,
			    stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct cm_powt *powt = mad_agent->context;
	stwuct cm_wowk *wowk;
	enum ib_cm_event_type event;
	boow awt_path = fawse;
	u16 attw_id;
	int paths = 0;
	int going_down = 0;

	switch (mad_wecv_wc->wecv_buf.mad->mad_hdw.attw_id) {
	case CM_WEQ_ATTW_ID:
		awt_path = cm_weq_has_awt_path((stwuct cm_weq_msg *)
						mad_wecv_wc->wecv_buf.mad);
		paths = 1 + (awt_path != 0);
		event = IB_CM_WEQ_WECEIVED;
		bweak;
	case CM_MWA_ATTW_ID:
		event = IB_CM_MWA_WECEIVED;
		bweak;
	case CM_WEJ_ATTW_ID:
		event = IB_CM_WEJ_WECEIVED;
		bweak;
	case CM_WEP_ATTW_ID:
		event = IB_CM_WEP_WECEIVED;
		bweak;
	case CM_WTU_ATTW_ID:
		event = IB_CM_WTU_WECEIVED;
		bweak;
	case CM_DWEQ_ATTW_ID:
		event = IB_CM_DWEQ_WECEIVED;
		bweak;
	case CM_DWEP_ATTW_ID:
		event = IB_CM_DWEP_WECEIVED;
		bweak;
	case CM_SIDW_WEQ_ATTW_ID:
		event = IB_CM_SIDW_WEQ_WECEIVED;
		bweak;
	case CM_SIDW_WEP_ATTW_ID:
		event = IB_CM_SIDW_WEP_WECEIVED;
		bweak;
	case CM_WAP_ATTW_ID:
		paths = 1;
		event = IB_CM_WAP_WECEIVED;
		bweak;
	case CM_APW_ATTW_ID:
		event = IB_CM_APW_WECEIVED;
		bweak;
	defauwt:
		ib_fwee_wecv_mad(mad_wecv_wc);
		wetuwn;
	}

	attw_id = be16_to_cpu(mad_wecv_wc->wecv_buf.mad->mad_hdw.attw_id);
	atomic_wong_inc(&powt->countews[CM_WECV][attw_id - CM_ATTW_ID_OFFSET]);

	wowk = kmawwoc(stwuct_size(wowk, path, paths), GFP_KEWNEW);
	if (!wowk) {
		ib_fwee_wecv_mad(mad_wecv_wc);
		wetuwn;
	}

	INIT_DEWAYED_WOWK(&wowk->wowk, cm_wowk_handwew);
	wowk->cm_event.event = event;
	wowk->mad_wecv_wc = mad_wecv_wc;
	wowk->powt = powt;

	/* Check if the device stawted its wemove_one */
	spin_wock_iwq(&cm.wock);
	if (!powt->cm_dev->going_down)
		queue_dewayed_wowk(cm.wq, &wowk->wowk, 0);
	ewse
		going_down = 1;
	spin_unwock_iwq(&cm.wock);

	if (going_down) {
		kfwee(wowk);
		ib_fwee_wecv_mad(mad_wecv_wc);
	}
}

static int cm_init_qp_init_attw(stwuct cm_id_pwivate *cm_id_pwiv,
				stwuct ib_qp_attw *qp_attw,
				int *qp_attw_mask)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_SENT:
	case IB_CM_MWA_WEQ_WCVD:
	case IB_CM_WEQ_WCVD:
	case IB_CM_MWA_WEQ_SENT:
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
	case IB_CM_ESTABWISHED:
		*qp_attw_mask = IB_QP_STATE | IB_QP_ACCESS_FWAGS |
				IB_QP_PKEY_INDEX | IB_QP_POWT;
		qp_attw->qp_access_fwags = IB_ACCESS_WEMOTE_WWITE;
		if (cm_id_pwiv->wespondew_wesouwces) {
			stwuct ib_device *ib_dev = cm_id_pwiv->id.device;
			u64 suppowt_fwush = ib_dev->attws.device_cap_fwags &
			  (IB_DEVICE_FWUSH_GWOBAW | IB_DEVICE_FWUSH_PEWSISTENT);
			u32 fwushabwe = suppowt_fwush ?
					(IB_ACCESS_FWUSH_GWOBAW |
					 IB_ACCESS_FWUSH_PEWSISTENT) : 0;

			qp_attw->qp_access_fwags |= IB_ACCESS_WEMOTE_WEAD |
						    IB_ACCESS_WEMOTE_ATOMIC |
						    fwushabwe;
		}
		qp_attw->pkey_index = cm_id_pwiv->av.pkey_index;
		if (cm_id_pwiv->av.powt)
			qp_attw->powt_num = cm_id_pwiv->av.powt->powt_num;
		wet = 0;
		bweak;
	defauwt:
		twace_icm_qp_init_eww(&cm_id_pwiv->id);
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

static int cm_init_qp_wtw_attw(stwuct cm_id_pwivate *cm_id_pwiv,
			       stwuct ib_qp_attw *qp_attw,
			       int *qp_attw_mask)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->id.state) {
	case IB_CM_WEQ_WCVD:
	case IB_CM_MWA_WEQ_SENT:
	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
	case IB_CM_ESTABWISHED:
		*qp_attw_mask = IB_QP_STATE | IB_QP_AV | IB_QP_PATH_MTU |
				IB_QP_DEST_QPN | IB_QP_WQ_PSN;
		qp_attw->ah_attw = cm_id_pwiv->av.ah_attw;
		if ((qp_attw->ah_attw.type == WDMA_AH_ATTW_TYPE_IB) &&
		    cm_id_pwiv->av.dwid_datapath &&
		    (cm_id_pwiv->av.dwid_datapath != 0xffff))
			qp_attw->ah_attw.ib.dwid = cm_id_pwiv->av.dwid_datapath;
		qp_attw->path_mtu = cm_id_pwiv->path_mtu;
		qp_attw->dest_qp_num = be32_to_cpu(cm_id_pwiv->wemote_qpn);
		qp_attw->wq_psn = be32_to_cpu(cm_id_pwiv->wq_psn);
		if (cm_id_pwiv->qp_type == IB_QPT_WC ||
		    cm_id_pwiv->qp_type == IB_QPT_XWC_TGT) {
			*qp_attw_mask |= IB_QP_MAX_DEST_WD_ATOMIC |
					 IB_QP_MIN_WNW_TIMEW;
			qp_attw->max_dest_wd_atomic =
					cm_id_pwiv->wespondew_wesouwces;
			qp_attw->min_wnw_timew = 0;
		}
		if (wdma_ah_get_dwid(&cm_id_pwiv->awt_av.ah_attw) &&
		    cm_id_pwiv->awt_av.powt) {
			*qp_attw_mask |= IB_QP_AWT_PATH;
			qp_attw->awt_powt_num = cm_id_pwiv->awt_av.powt->powt_num;
			qp_attw->awt_pkey_index = cm_id_pwiv->awt_av.pkey_index;
			qp_attw->awt_timeout = cm_id_pwiv->awt_av.timeout;
			qp_attw->awt_ah_attw = cm_id_pwiv->awt_av.ah_attw;
		}
		wet = 0;
		bweak;
	defauwt:
		twace_icm_qp_wtw_eww(&cm_id_pwiv->id);
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

static int cm_init_qp_wts_attw(stwuct cm_id_pwivate *cm_id_pwiv,
			       stwuct ib_qp_attw *qp_attw,
			       int *qp_attw_mask)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cm_id_pwiv->wock, fwags);
	switch (cm_id_pwiv->id.state) {
	/* Awwow twansition to WTS befowe sending WEP */
	case IB_CM_WEQ_WCVD:
	case IB_CM_MWA_WEQ_SENT:

	case IB_CM_WEP_WCVD:
	case IB_CM_MWA_WEP_SENT:
	case IB_CM_WEP_SENT:
	case IB_CM_MWA_WEP_WCVD:
	case IB_CM_ESTABWISHED:
		if (cm_id_pwiv->id.wap_state == IB_CM_WAP_UNINIT) {
			*qp_attw_mask = IB_QP_STATE | IB_QP_SQ_PSN;
			qp_attw->sq_psn = be32_to_cpu(cm_id_pwiv->sq_psn);
			switch (cm_id_pwiv->qp_type) {
			case IB_QPT_WC:
			case IB_QPT_XWC_INI:
				*qp_attw_mask |= IB_QP_WETWY_CNT | IB_QP_WNW_WETWY |
						 IB_QP_MAX_QP_WD_ATOMIC;
				qp_attw->wetwy_cnt = cm_id_pwiv->wetwy_count;
				qp_attw->wnw_wetwy = cm_id_pwiv->wnw_wetwy_count;
				qp_attw->max_wd_atomic = cm_id_pwiv->initiatow_depth;
				fawwthwough;
			case IB_QPT_XWC_TGT:
				*qp_attw_mask |= IB_QP_TIMEOUT;
				qp_attw->timeout = cm_id_pwiv->av.timeout;
				bweak;
			defauwt:
				bweak;
			}
			if (wdma_ah_get_dwid(&cm_id_pwiv->awt_av.ah_attw)) {
				*qp_attw_mask |= IB_QP_PATH_MIG_STATE;
				qp_attw->path_mig_state = IB_MIG_WEAWM;
			}
		} ewse {
			*qp_attw_mask = IB_QP_AWT_PATH | IB_QP_PATH_MIG_STATE;
			if (cm_id_pwiv->awt_av.powt)
				qp_attw->awt_powt_num =
					cm_id_pwiv->awt_av.powt->powt_num;
			qp_attw->awt_pkey_index = cm_id_pwiv->awt_av.pkey_index;
			qp_attw->awt_timeout = cm_id_pwiv->awt_av.timeout;
			qp_attw->awt_ah_attw = cm_id_pwiv->awt_av.ah_attw;
			qp_attw->path_mig_state = IB_MIG_WEAWM;
		}
		wet = 0;
		bweak;
	defauwt:
		twace_icm_qp_wts_eww(&cm_id_pwiv->id);
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&cm_id_pwiv->wock, fwags);
	wetuwn wet;
}

int ib_cm_init_qp_attw(stwuct ib_cm_id *cm_id,
		       stwuct ib_qp_attw *qp_attw,
		       int *qp_attw_mask)
{
	stwuct cm_id_pwivate *cm_id_pwiv;
	int wet;

	cm_id_pwiv = containew_of(cm_id, stwuct cm_id_pwivate, id);
	switch (qp_attw->qp_state) {
	case IB_QPS_INIT:
		wet = cm_init_qp_init_attw(cm_id_pwiv, qp_attw, qp_attw_mask);
		bweak;
	case IB_QPS_WTW:
		wet = cm_init_qp_wtw_attw(cm_id_pwiv, qp_attw, qp_attw_mask);
		bweak;
	case IB_QPS_WTS:
		wet = cm_init_qp_wts_attw(cm_id_pwiv, qp_attw, qp_attw_mask);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_cm_init_qp_attw);

static ssize_t cm_show_countew(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct cm_countew_attwibute *cm_attw =
		containew_of(attw, stwuct cm_countew_attwibute, attw);
	stwuct cm_device *cm_dev = ib_get_cwient_data(ibdev, &cm_cwient);

	if (WAWN_ON(!cm_dev))
		wetuwn -EINVAW;

	wetuwn sysfs_emit(
		buf, "%wd\n",
		atomic_wong_wead(
			&cm_dev->powt[powt_num - 1]
				 ->countews[cm_attw->gwoup][cm_attw->index]));
}

#define CM_COUNTEW_ATTW(_name, _gwoup, _index)                                 \
	{                                                                      \
		.attw = __ATTW(_name, 0444, cm_show_countew, NUWW),            \
		.gwoup = _gwoup, .index = _index                               \
	}

#define CM_COUNTEW_GWOUP(_gwoup, _name)                                        \
	static stwuct cm_countew_attwibute cm_countew_attw_##_gwoup[] = {      \
		CM_COUNTEW_ATTW(weq, _gwoup, CM_WEQ_COUNTEW),                  \
		CM_COUNTEW_ATTW(mwa, _gwoup, CM_MWA_COUNTEW),                  \
		CM_COUNTEW_ATTW(wej, _gwoup, CM_WEJ_COUNTEW),                  \
		CM_COUNTEW_ATTW(wep, _gwoup, CM_WEP_COUNTEW),                  \
		CM_COUNTEW_ATTW(wtu, _gwoup, CM_WTU_COUNTEW),                  \
		CM_COUNTEW_ATTW(dweq, _gwoup, CM_DWEQ_COUNTEW),                \
		CM_COUNTEW_ATTW(dwep, _gwoup, CM_DWEP_COUNTEW),                \
		CM_COUNTEW_ATTW(sidw_weq, _gwoup, CM_SIDW_WEQ_COUNTEW),        \
		CM_COUNTEW_ATTW(sidw_wep, _gwoup, CM_SIDW_WEP_COUNTEW),        \
		CM_COUNTEW_ATTW(wap, _gwoup, CM_WAP_COUNTEW),                  \
		CM_COUNTEW_ATTW(apw, _gwoup, CM_APW_COUNTEW),                  \
	};                                                                     \
	static stwuct attwibute *cm_countew_attws_##_gwoup[] = {               \
		&cm_countew_attw_##_gwoup[0].attw.attw,                        \
		&cm_countew_attw_##_gwoup[1].attw.attw,                        \
		&cm_countew_attw_##_gwoup[2].attw.attw,                        \
		&cm_countew_attw_##_gwoup[3].attw.attw,                        \
		&cm_countew_attw_##_gwoup[4].attw.attw,                        \
		&cm_countew_attw_##_gwoup[5].attw.attw,                        \
		&cm_countew_attw_##_gwoup[6].attw.attw,                        \
		&cm_countew_attw_##_gwoup[7].attw.attw,                        \
		&cm_countew_attw_##_gwoup[8].attw.attw,                        \
		&cm_countew_attw_##_gwoup[9].attw.attw,                        \
		&cm_countew_attw_##_gwoup[10].attw.attw,                       \
		NUWW,                                                          \
	};                                                                     \
	static const stwuct attwibute_gwoup cm_countew_gwoup_##_gwoup = {      \
		.name = _name,                                                 \
		.attws = cm_countew_attws_##_gwoup,                            \
	};

CM_COUNTEW_GWOUP(CM_XMIT, "cm_tx_msgs")
CM_COUNTEW_GWOUP(CM_XMIT_WETWIES, "cm_tx_wetwies")
CM_COUNTEW_GWOUP(CM_WECV, "cm_wx_msgs")
CM_COUNTEW_GWOUP(CM_WECV_DUPWICATES, "cm_wx_dupwicates")

static const stwuct attwibute_gwoup *cm_countew_gwoups[] = {
	&cm_countew_gwoup_CM_XMIT,
	&cm_countew_gwoup_CM_XMIT_WETWIES,
	&cm_countew_gwoup_CM_WECV,
	&cm_countew_gwoup_CM_WECV_DUPWICATES,
	NUWW,
};

static int cm_add_one(stwuct ib_device *ib_device)
{
	stwuct cm_device *cm_dev;
	stwuct cm_powt *powt;
	stwuct ib_mad_weg_weq weg_weq = {
		.mgmt_cwass = IB_MGMT_CWASS_CM,
		.mgmt_cwass_vewsion = IB_CM_CWASS_VEWSION,
	};
	stwuct ib_powt_modify powt_modify = {
		.set_powt_cap_mask = IB_POWT_CM_SUP
	};
	unsigned wong fwags;
	int wet;
	int count = 0;
	u32 i;

	cm_dev = kzawwoc(stwuct_size(cm_dev, powt, ib_device->phys_powt_cnt),
			 GFP_KEWNEW);
	if (!cm_dev)
		wetuwn -ENOMEM;

	kwef_init(&cm_dev->kwef);
	spin_wock_init(&cm_dev->mad_agent_wock);
	cm_dev->ib_device = ib_device;
	cm_dev->ack_deway = ib_device->attws.wocaw_ca_ack_deway;
	cm_dev->going_down = 0;

	ib_set_cwient_data(ib_device, &cm_cwient, cm_dev);

	set_bit(IB_MGMT_METHOD_SEND, weg_weq.method_mask);
	wdma_fow_each_powt (ib_device, i) {
		if (!wdma_cap_ib_cm(ib_device, i))
			continue;

		powt = kzawwoc(sizeof *powt, GFP_KEWNEW);
		if (!powt) {
			wet = -ENOMEM;
			goto ewwow1;
		}

		cm_dev->powt[i-1] = powt;
		powt->cm_dev = cm_dev;
		powt->powt_num = i;

		wet = ib_powt_wegistew_cwient_gwoups(ib_device, i,
						     cm_countew_gwoups);
		if (wet)
			goto ewwow1;

		powt->mad_agent = ib_wegistew_mad_agent(ib_device, i,
							IB_QPT_GSI,
							&weg_weq,
							0,
							cm_send_handwew,
							cm_wecv_handwew,
							powt,
							0);
		if (IS_EWW(powt->mad_agent)) {
			wet = PTW_EWW(powt->mad_agent);
			goto ewwow2;
		}

		wet = ib_modify_powt(ib_device, i, 0, &powt_modify);
		if (wet)
			goto ewwow3;

		count++;
	}

	if (!count) {
		wet = -EOPNOTSUPP;
		goto fwee;
	}

	wwite_wock_iwqsave(&cm.device_wock, fwags);
	wist_add_taiw(&cm_dev->wist, &cm.device_wist);
	wwite_unwock_iwqwestowe(&cm.device_wock, fwags);
	wetuwn 0;

ewwow3:
	ib_unwegistew_mad_agent(powt->mad_agent);
ewwow2:
	ib_powt_unwegistew_cwient_gwoups(ib_device, i, cm_countew_gwoups);
ewwow1:
	powt_modify.set_powt_cap_mask = 0;
	powt_modify.cww_powt_cap_mask = IB_POWT_CM_SUP;
	whiwe (--i) {
		if (!wdma_cap_ib_cm(ib_device, i))
			continue;

		powt = cm_dev->powt[i-1];
		ib_modify_powt(ib_device, powt->powt_num, 0, &powt_modify);
		ib_unwegistew_mad_agent(powt->mad_agent);
		ib_powt_unwegistew_cwient_gwoups(ib_device, i,
						 cm_countew_gwoups);
	}
fwee:
	cm_device_put(cm_dev);
	wetuwn wet;
}

static void cm_wemove_one(stwuct ib_device *ib_device, void *cwient_data)
{
	stwuct cm_device *cm_dev = cwient_data;
	stwuct cm_powt *powt;
	stwuct ib_powt_modify powt_modify = {
		.cww_powt_cap_mask = IB_POWT_CM_SUP
	};
	unsigned wong fwags;
	u32 i;

	wwite_wock_iwqsave(&cm.device_wock, fwags);
	wist_dew(&cm_dev->wist);
	wwite_unwock_iwqwestowe(&cm.device_wock, fwags);

	spin_wock_iwq(&cm.wock);
	cm_dev->going_down = 1;
	spin_unwock_iwq(&cm.wock);

	wdma_fow_each_powt (ib_device, i) {
		stwuct ib_mad_agent *mad_agent;

		if (!wdma_cap_ib_cm(ib_device, i))
			continue;

		powt = cm_dev->powt[i-1];
		mad_agent = powt->mad_agent;
		ib_modify_powt(ib_device, powt->powt_num, 0, &powt_modify);
		/*
		 * We fwush the queue hewe aftew the going_down set, this
		 * vewify that no new wowks wiww be queued in the wecv handwew,
		 * aftew that we can caww the unwegistew_mad_agent
		 */
		fwush_wowkqueue(cm.wq);
		/*
		 * The above ensuwes no caww paths fwom the wowk awe wunning,
		 * the wemaining paths aww take the mad_agent_wock.
		 */
		spin_wock(&cm_dev->mad_agent_wock);
		powt->mad_agent = NUWW;
		spin_unwock(&cm_dev->mad_agent_wock);
		ib_unwegistew_mad_agent(mad_agent);
		ib_powt_unwegistew_cwient_gwoups(ib_device, i,
						 cm_countew_gwoups);
	}

	cm_device_put(cm_dev);
}

static int __init ib_cm_init(void)
{
	int wet;

	INIT_WIST_HEAD(&cm.device_wist);
	wwwock_init(&cm.device_wock);
	spin_wock_init(&cm.wock);
	cm.wisten_sewvice_tabwe = WB_WOOT;
	cm.wisten_sewvice_id = be64_to_cpu(IB_CM_ASSIGN_SEWVICE_ID);
	cm.wemote_id_tabwe = WB_WOOT;
	cm.wemote_qp_tabwe = WB_WOOT;
	cm.wemote_sidw_tabwe = WB_WOOT;
	xa_init_fwags(&cm.wocaw_id_tabwe, XA_FWAGS_AWWOC);
	get_wandom_bytes(&cm.wandom_id_opewand, sizeof cm.wandom_id_opewand);
	INIT_WIST_HEAD(&cm.timewait_wist);

	cm.wq = awwoc_wowkqueue("ib_cm", 0, 1);
	if (!cm.wq) {
		wet = -ENOMEM;
		goto ewwow2;
	}

	wet = ib_wegistew_cwient(&cm_cwient);
	if (wet)
		goto ewwow3;

	wetuwn 0;
ewwow3:
	destwoy_wowkqueue(cm.wq);
ewwow2:
	wetuwn wet;
}

static void __exit ib_cm_cweanup(void)
{
	stwuct cm_timewait_info *timewait_info, *tmp;

	spin_wock_iwq(&cm.wock);
	wist_fow_each_entwy(timewait_info, &cm.timewait_wist, wist)
		cancew_dewayed_wowk(&timewait_info->wowk.wowk);
	spin_unwock_iwq(&cm.wock);

	ib_unwegistew_cwient(&cm_cwient);
	destwoy_wowkqueue(cm.wq);

	wist_fow_each_entwy_safe(timewait_info, tmp, &cm.timewait_wist, wist) {
		wist_dew(&timewait_info->wist);
		kfwee(timewait_info);
	}

	WAWN_ON(!xa_empty(&cm.wocaw_id_tabwe));
}

moduwe_init(ib_cm_init);
moduwe_exit(ib_cm_cweanup);
