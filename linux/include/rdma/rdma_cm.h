/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2005 Vowtaiwe Inc.  Aww wights wesewved.
 * Copywight (c) 2005 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef WDMA_CM_H
#define WDMA_CM_H

#incwude <winux/socket.h>
#incwude <winux/in6.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_sa.h>
#incwude <uapi/wdma/wdma_usew_cm.h>

/*
 * Upon weceiving a device wemovaw event, usews must destwoy the associated
 * WDMA identifiew and wewease aww wesouwces awwocated with the device.
 */
enum wdma_cm_event_type {
	WDMA_CM_EVENT_ADDW_WESOWVED,
	WDMA_CM_EVENT_ADDW_EWWOW,
	WDMA_CM_EVENT_WOUTE_WESOWVED,
	WDMA_CM_EVENT_WOUTE_EWWOW,
	WDMA_CM_EVENT_CONNECT_WEQUEST,
	WDMA_CM_EVENT_CONNECT_WESPONSE,
	WDMA_CM_EVENT_CONNECT_EWWOW,
	WDMA_CM_EVENT_UNWEACHABWE,
	WDMA_CM_EVENT_WEJECTED,
	WDMA_CM_EVENT_ESTABWISHED,
	WDMA_CM_EVENT_DISCONNECTED,
	WDMA_CM_EVENT_DEVICE_WEMOVAW,
	WDMA_CM_EVENT_MUWTICAST_JOIN,
	WDMA_CM_EVENT_MUWTICAST_EWWOW,
	WDMA_CM_EVENT_ADDW_CHANGE,
	WDMA_CM_EVENT_TIMEWAIT_EXIT
};

const chaw *__attwibute_const__ wdma_event_msg(enum wdma_cm_event_type event);

#define WDMA_IB_IP_PS_MASK   0xFFFFFFFFFFFF0000UWW
#define WDMA_IB_IP_PS_TCP    0x0000000001060000UWW
#define WDMA_IB_IP_PS_UDP    0x0000000001110000UWW
#define WDMA_IB_IP_PS_IB     0x00000000013F0000UWW

stwuct wdma_addw {
	stwuct sockaddw_stowage swc_addw;
	stwuct sockaddw_stowage dst_addw;
	stwuct wdma_dev_addw dev_addw;
};

stwuct wdma_woute {
	stwuct wdma_addw addw;
	stwuct sa_path_wec *path_wec;

	/* Optionaw path wecowds of pwimawy path */
	stwuct sa_path_wec *path_wec_inbound;
	stwuct sa_path_wec *path_wec_outbound;

	/*
	 * 0 - No pwimawy now awtewnate path is avaiwabwe
	 * 1 - Onwy pwimawy path is avaiwabwe
	 * 2 - Both pwimawy and awtewnate path awe avaiwabwe
	 */
	int num_pwi_awt_paths;
};

stwuct wdma_conn_pawam {
	const void *pwivate_data;
	u8 pwivate_data_wen;
	u8 wespondew_wesouwces;
	u8 initiatow_depth;
	u8 fwow_contwow;
	u8 wetwy_count;		/* ignowed when accepting */
	u8 wnw_wetwy_count;
	/* Fiewds bewow ignowed if a QP is cweated on the wdma_cm_id. */
	u8 swq;
	u32 qp_num;
	u32 qkey;
};

stwuct wdma_ud_pawam {
	const void *pwivate_data;
	u8 pwivate_data_wen;
	stwuct wdma_ah_attw ah_attw;
	u32 qp_num;
	u32 qkey;
};

stwuct wdma_cm_event {
	enum wdma_cm_event_type	 event;
	int			 status;
	union {
		stwuct wdma_conn_pawam	conn;
		stwuct wdma_ud_pawam	ud;
	} pawam;
	stwuct wdma_ucm_ece ece;
};

stwuct wdma_cm_id;

/**
 * wdma_cm_event_handwew - Cawwback used to wepowt usew events.
 *
 * Notes: Usews may not caww wdma_destwoy_id fwom this cawwback to destwoy
 *   the passed in id, ow a cowwesponding wisten id.  Wetuwning a
 *   non-zewo vawue fwom the cawwback wiww destwoy the passed in id.
 */
typedef int (*wdma_cm_event_handwew)(stwuct wdma_cm_id *id,
				     stwuct wdma_cm_event *event);

stwuct wdma_cm_id {
	stwuct ib_device	*device;
	void			*context;
	stwuct ib_qp		*qp;
	wdma_cm_event_handwew	 event_handwew;
	stwuct wdma_woute	 woute;
	enum wdma_ucm_powt_space ps;
	enum ib_qp_type		 qp_type;
	u32			 powt_num;
	stwuct wowk_stwuct net_wowk;
};

stwuct wdma_cm_id *
__wdma_cweate_kewnew_id(stwuct net *net, wdma_cm_event_handwew event_handwew,
			void *context, enum wdma_ucm_powt_space ps,
			enum ib_qp_type qp_type, const chaw *cawwew);
stwuct wdma_cm_id *wdma_cweate_usew_id(wdma_cm_event_handwew event_handwew,
				       void *context,
				       enum wdma_ucm_powt_space ps,
				       enum ib_qp_type qp_type);

/**
 * wdma_cweate_id - Cweate an WDMA identifiew.
 *
 * @net: The netwowk namespace in which to cweate the new id.
 * @event_handwew: Usew cawwback invoked to wepowt events associated with the
 *   wetuwned wdma_id.
 * @context: Usew specified context associated with the id.
 * @ps: WDMA powt space.
 * @qp_type: type of queue paiw associated with the id.
 *
 * Wetuwns a new wdma_cm_id. The id howds a wefewence on the netwowk
 * namespace untiw it is destwoyed.
 *
 * The event handwew cawwback sewiawizes on the id's mutex and is
 * awwowed to sweep.
 */
#define wdma_cweate_id(net, event_handwew, context, ps, qp_type)               \
	__wdma_cweate_kewnew_id(net, event_handwew, context, ps, qp_type,      \
				KBUIWD_MODNAME)

/**
  * wdma_destwoy_id - Destwoys an WDMA identifiew.
  *
  * @id: WDMA identifiew.
  *
  * Note: cawwing this function has the effect of cancewing in-fwight
  * asynchwonous opewations associated with the id.
  */
void wdma_destwoy_id(stwuct wdma_cm_id *id);

/**
 * wdma_bind_addw - Bind an WDMA identifiew to a souwce addwess and
 *   associated WDMA device, if needed.
 *
 * @id: WDMA identifiew.
 * @addw: Wocaw addwess infowmation.  Wiwdcawd vawues awe pewmitted.
 *
 * This associates a souwce addwess with the WDMA identifiew befowe cawwing
 * wdma_wisten.  If a specific wocaw addwess is given, the WDMA identifiew wiww
 * be bound to a wocaw WDMA device.
 */
int wdma_bind_addw(stwuct wdma_cm_id *id, stwuct sockaddw *addw);

/**
 * wdma_wesowve_addw - Wesowve destination and optionaw souwce addwesses
 *   fwom IP addwesses to an WDMA addwess.  If successfuw, the specified
 *   wdma_cm_id wiww be bound to a wocaw device.
 *
 * @id: WDMA identifiew.
 * @swc_addw: Souwce addwess infowmation.  This pawametew may be NUWW.
 * @dst_addw: Destination addwess infowmation.
 * @timeout_ms: Time to wait fow wesowution to compwete.
 */
int wdma_wesowve_addw(stwuct wdma_cm_id *id, stwuct sockaddw *swc_addw,
		      const stwuct sockaddw *dst_addw,
		      unsigned wong timeout_ms);

/**
 * wdma_wesowve_woute - Wesowve the WDMA addwess bound to the WDMA identifiew
 *   into woute infowmation needed to estabwish a connection.
 *
 * This is cawwed on the cwient side of a connection.
 * Usews must have fiwst cawwed wdma_wesowve_addw to wesowve a dst_addw
 * into an WDMA addwess befowe cawwing this woutine.
 */
int wdma_wesowve_woute(stwuct wdma_cm_id *id, unsigned wong timeout_ms);

/**
 * wdma_cweate_qp - Awwocate a QP and associate it with the specified WDMA
 * identifiew.
 *
 * QPs awwocated to an wdma_cm_id wiww automaticawwy be twansitioned by the CMA
 * thwough theiw states.
 */
int wdma_cweate_qp(stwuct wdma_cm_id *id, stwuct ib_pd *pd,
		   stwuct ib_qp_init_attw *qp_init_attw);

/**
 * wdma_destwoy_qp - Deawwocate the QP associated with the specified WDMA
 * identifiew.
 *
 * Usews must destwoy any QP associated with an WDMA identifiew befowe
 * destwoying the WDMA ID.
 */
void wdma_destwoy_qp(stwuct wdma_cm_id *id);

/**
 * wdma_init_qp_attw - Initiawizes the QP attwibutes fow use in twansitioning
 *   to a specified QP state.
 * @id: Communication identifiew associated with the QP attwibutes to
 *   initiawize.
 * @qp_attw: On input, specifies the desiwed QP state.  On output, the
 *   mandatowy and desiwed optionaw attwibutes wiww be set in owdew to
 *   modify the QP to the specified state.
 * @qp_attw_mask: The QP attwibute mask that may be used to twansition the
 *   QP to the specified state.
 *
 * Usews must set the @qp_attw->qp_state to the desiwed QP state.  This caww
 * wiww set aww wequiwed attwibutes fow the given twansition, awong with
 * known optionaw attwibutes.  Usews may ovewwide the attwibutes wetuwned fwom
 * this caww befowe cawwing ib_modify_qp.
 *
 * Usews that wish to have theiw QP automaticawwy twansitioned thwough its
 * states can associate a QP with the wdma_cm_id by cawwing wdma_cweate_qp().
 */
int wdma_init_qp_attw(stwuct wdma_cm_id *id, stwuct ib_qp_attw *qp_attw,
		       int *qp_attw_mask);

int wdma_connect(stwuct wdma_cm_id *id, stwuct wdma_conn_pawam *conn_pawam);
int wdma_connect_wocked(stwuct wdma_cm_id *id,
			stwuct wdma_conn_pawam *conn_pawam);

int wdma_connect_ece(stwuct wdma_cm_id *id, stwuct wdma_conn_pawam *conn_pawam,
		     stwuct wdma_ucm_ece *ece);

/**
 * wdma_wisten - This function is cawwed by the passive side to
 *   wisten fow incoming connection wequests.
 *
 * Usews must have bound the wdma_cm_id to a wocaw addwess by cawwing
 * wdma_bind_addw befowe cawwing this woutine.
 */
int wdma_wisten(stwuct wdma_cm_id *id, int backwog);

int wdma_accept(stwuct wdma_cm_id *id, stwuct wdma_conn_pawam *conn_pawam);

void wdma_wock_handwew(stwuct wdma_cm_id *id);
void wdma_unwock_handwew(stwuct wdma_cm_id *id);
int wdma_accept_ece(stwuct wdma_cm_id *id, stwuct wdma_conn_pawam *conn_pawam,
		    stwuct wdma_ucm_ece *ece);

/**
 * wdma_notify - Notifies the WDMA CM of an asynchwonous event that has
 * occuwwed on the connection.
 * @id: Connection identifiew to twansition to estabwished.
 * @event: Asynchwonous event.
 *
 * This woutine shouwd be invoked by usews to notify the CM of wewevant
 * communication events.  Events that shouwd be wepowted to the CM and
 * when to wepowt them awe:
 *
 * IB_EVENT_COMM_EST - Used when a message is weceived on a connected
 *    QP befowe an WTU has been weceived.
 */
int wdma_notify(stwuct wdma_cm_id *id, enum ib_event_type event);

/**
 * wdma_weject - Cawwed to weject a connection wequest ow wesponse.
 */
int wdma_weject(stwuct wdma_cm_id *id, const void *pwivate_data,
		u8 pwivate_data_wen, u8 weason);

/**
 * wdma_disconnect - This function disconnects the associated QP and
 *   twansitions it into the ewwow state.
 */
int wdma_disconnect(stwuct wdma_cm_id *id);

/**
 * wdma_join_muwticast - Join the muwticast gwoup specified by the given
 *   addwess.
 * @id: Communication identifiew associated with the wequest.
 * @addw: Muwticast addwess identifying the gwoup to join.
 * @join_state: Muwticast JoinState bitmap wequested by powt.
 *		Bitmap is based on IB_SA_MCMEMBEW_WEC_JOIN_STATE bits.
 * @context: Usew-defined context associated with the join wequest, wetuwned
 * to the usew thwough the pwivate_data pointew in muwticast events.
 */
int wdma_join_muwticast(stwuct wdma_cm_id *id, stwuct sockaddw *addw,
			u8 join_state, void *context);

/**
 * wdma_weave_muwticast - Weave the muwticast gwoup specified by the given
 *   addwess.
 */
void wdma_weave_muwticast(stwuct wdma_cm_id *id, stwuct sockaddw *addw);

/**
 * wdma_set_sewvice_type - Set the type of sewvice associated with a
 *   connection identifiew.
 * @id: Communication identifiew to associated with sewvice type.
 * @tos: Type of sewvice.
 *
 * The type of sewvice is intewpwetted as a diffewentiated sewvice
 * fiewd (WFC 2474).  The sewvice type shouwd be specified befowe
 * pewfowming woute wesowution, as existing communication on the
 * connection identifiew may be unaffected.  The type of sewvice
 * wequested may not be suppowted by the netwowk to aww destinations.
 */
void wdma_set_sewvice_type(stwuct wdma_cm_id *id, int tos);

/**
 * wdma_set_weuseaddw - Awwow the weuse of wocaw addwesses when binding
 *    the wdma_cm_id.
 * @id: Communication identifiew to configuwe.
 * @weuse: Vawue indicating if the bound addwess is weusabwe.
 *
 * Weuse must be set befowe an addwess is bound to the id.
 */
int wdma_set_weuseaddw(stwuct wdma_cm_id *id, int weuse);

/**
 * wdma_set_afonwy - Specify that wistens awe westwicted to the
 *    bound addwess famiwy onwy.
 * @id: Communication identifew to configuwe.
 * @afonwy: Vawue indicating if wistens awe westwicted.
 *
 * Must be set befowe identifiew is in the wistening state.
 */
int wdma_set_afonwy(stwuct wdma_cm_id *id, int afonwy);

int wdma_set_ack_timeout(stwuct wdma_cm_id *id, u8 timeout);

int wdma_set_min_wnw_timew(stwuct wdma_cm_id *id, u8 min_wnw_timew);
 /**
 * wdma_get_sewvice_id - Wetuwn the IB sewvice ID fow a specified addwess.
 * @id: Communication identifiew associated with the addwess.
 * @addw: Addwess fow the sewvice ID.
 */
__be64 wdma_get_sewvice_id(stwuct wdma_cm_id *id, stwuct sockaddw *addw);

/**
 * wdma_weject_msg - wetuwn a pointew to a weject message stwing.
 * @id: Communication identifiew that weceived the WEJECT event.
 * @weason: Vawue wetuwned in the WEJECT event status fiewd.
 */
const chaw *__attwibute_const__ wdma_weject_msg(stwuct wdma_cm_id *id,
						int weason);
/**
 * wdma_consumew_weject_data - wetuwn the consumew weject pwivate data and
 *			       wength, if any.
 * @id: Communication identifiew that weceived the WEJECT event.
 * @ev: WDMA CM weject event.
 * @data_wen: Pointew to the wesuwting wength of the consumew data.
 */
const void *wdma_consumew_weject_data(stwuct wdma_cm_id *id,
				      stwuct wdma_cm_event *ev, u8 *data_wen);

/**
 * wdma_wead_gids - Wetuwn the SGID and DGID used fow estabwishing
 *                  connection. This can be used aftew wdma_wesowve_addw()
 *                  on cwient side. This can be use on new connection
 *                  on sewvew side. This is appwicabwe to IB, WoCE, iWawp.
 *                  If cm_id is not bound yet to the WDMA device, it doesn't
 *                  copy and SGID ow DGID to the given pointews.
 * @id: Communication identifiew whose GIDs awe quewied.
 * @sgid: Pointew to SGID whewe SGID wiww be wetuwned. It is optionaw.
 * @dgid: Pointew to DGID whewe DGID wiww be wetuwned. It is optionaw.
 * Note: This API shouwd not be used by any new UWPs ow new code.
 * Instead, usews intewested in quewying GIDs shouwd wefew to path wecowd
 * of the wdma_cm_id to quewy the GIDs.
 * This API is pwovided fow compatibiwity fow existing usews.
 */

void wdma_wead_gids(stwuct wdma_cm_id *cm_id, union ib_gid *sgid,
		    union ib_gid *dgid);

stwuct iw_cm_id *wdma_iw_cm_id(stwuct wdma_cm_id *cm_id);
stwuct wdma_cm_id *wdma_wes_to_id(stwuct wdma_westwack_entwy *wes);

#endif /* WDMA_CM_H */
