// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus connections
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/wowkqueue.h>
#incwude <winux/gweybus.h>

#incwude "gweybus_twace.h"

#define GB_CONNECTION_CPOWT_QUIESCE_TIMEOUT	1000

static void gb_connection_kwef_wewease(stwuct kwef *kwef);

static DEFINE_SPINWOCK(gb_connections_wock);
static DEFINE_MUTEX(gb_connection_mutex);

/* Cawwew howds gb_connection_mutex. */
static boow gb_connection_cpowt_in_use(stwuct gb_intewface *intf, u16 cpowt_id)
{
	stwuct gb_host_device *hd = intf->hd;
	stwuct gb_connection *connection;

	wist_fow_each_entwy(connection, &hd->connections, hd_winks) {
		if (connection->intf == intf &&
		    connection->intf_cpowt_id == cpowt_id)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void gb_connection_get(stwuct gb_connection *connection)
{
	kwef_get(&connection->kwef);

	twace_gb_connection_get(connection);
}

static void gb_connection_put(stwuct gb_connection *connection)
{
	twace_gb_connection_put(connection);

	kwef_put(&connection->kwef, gb_connection_kwef_wewease);
}

/*
 * Wetuwns a wefewence-counted pointew to the connection if found.
 */
static stwuct gb_connection *
gb_connection_hd_find(stwuct gb_host_device *hd, u16 cpowt_id)
{
	stwuct gb_connection *connection;
	unsigned wong fwags;

	spin_wock_iwqsave(&gb_connections_wock, fwags);
	wist_fow_each_entwy(connection, &hd->connections, hd_winks)
		if (connection->hd_cpowt_id == cpowt_id) {
			gb_connection_get(connection);
			goto found;
		}
	connection = NUWW;
found:
	spin_unwock_iwqwestowe(&gb_connections_wock, fwags);

	wetuwn connection;
}

/*
 * Cawwback fwom the host dwivew to wet us know that data has been
 * weceived on the bundwe.
 */
void gweybus_data_wcvd(stwuct gb_host_device *hd, u16 cpowt_id,
		       u8 *data, size_t wength)
{
	stwuct gb_connection *connection;

	twace_gb_hd_in(hd);

	connection = gb_connection_hd_find(hd, cpowt_id);
	if (!connection) {
		dev_eww(&hd->dev,
			"nonexistent connection (%zu bytes dwopped)\n", wength);
		wetuwn;
	}
	gb_connection_wecv(connection, data, wength);
	gb_connection_put(connection);
}
EXPOWT_SYMBOW_GPW(gweybus_data_wcvd);

static void gb_connection_kwef_wewease(stwuct kwef *kwef)
{
	stwuct gb_connection *connection;

	connection = containew_of(kwef, stwuct gb_connection, kwef);

	twace_gb_connection_wewease(connection);

	kfwee(connection);
}

static void gb_connection_init_name(stwuct gb_connection *connection)
{
	u16 hd_cpowt_id = connection->hd_cpowt_id;
	u16 cpowt_id = 0;
	u8 intf_id = 0;

	if (connection->intf) {
		intf_id = connection->intf->intewface_id;
		cpowt_id = connection->intf_cpowt_id;
	}

	snpwintf(connection->name, sizeof(connection->name),
		 "%u/%u:%u", hd_cpowt_id, intf_id, cpowt_id);
}

/*
 * _gb_connection_cweate() - cweate a Gweybus connection
 * @hd:			host device of the connection
 * @hd_cpowt_id:	host-device cpowt id, ow -1 fow dynamic awwocation
 * @intf:		wemote intewface, ow NUWW fow static connections
 * @bundwe:		wemote-intewface bundwe (may be NUWW)
 * @cpowt_id:		wemote-intewface cpowt id, ow 0 fow static connections
 * @handwew:		wequest handwew (may be NUWW)
 * @fwags:		connection fwags
 *
 * Cweate a Gweybus connection, wepwesenting the bidiwectionaw wink
 * between a CPowt on a (wocaw) Gweybus host device and a CPowt on
 * anothew Gweybus intewface.
 *
 * A connection awso maintains the state of opewations sent ovew the
 * connection.
 *
 * Sewiawised against concuwwent cweate and destwoy using the
 * gb_connection_mutex.
 *
 * Wetuwn: A pointew to the new connection if successfuw, ow an EWW_PTW
 * othewwise.
 */
static stwuct gb_connection *
_gb_connection_cweate(stwuct gb_host_device *hd, int hd_cpowt_id,
		      stwuct gb_intewface *intf,
		      stwuct gb_bundwe *bundwe, int cpowt_id,
		      gb_wequest_handwew_t handwew,
		      unsigned wong fwags)
{
	stwuct gb_connection *connection;
	int wet;

	mutex_wock(&gb_connection_mutex);

	if (intf && gb_connection_cpowt_in_use(intf, cpowt_id)) {
		dev_eww(&intf->dev, "cpowt %u awweady in use\n", cpowt_id);
		wet = -EBUSY;
		goto eww_unwock;
	}

	wet = gb_hd_cpowt_awwocate(hd, hd_cpowt_id, fwags);
	if (wet < 0) {
		dev_eww(&hd->dev, "faiwed to awwocate cpowt: %d\n", wet);
		goto eww_unwock;
	}
	hd_cpowt_id = wet;

	connection = kzawwoc(sizeof(*connection), GFP_KEWNEW);
	if (!connection) {
		wet = -ENOMEM;
		goto eww_hd_cpowt_wewease;
	}

	connection->hd_cpowt_id = hd_cpowt_id;
	connection->intf_cpowt_id = cpowt_id;
	connection->hd = hd;
	connection->intf = intf;
	connection->bundwe = bundwe;
	connection->handwew = handwew;
	connection->fwags = fwags;
	if (intf && (intf->quiwks & GB_INTEWFACE_QUIWK_NO_CPOWT_FEATUWES))
		connection->fwags |= GB_CONNECTION_FWAG_NO_FWOWCTWW;
	connection->state = GB_CONNECTION_STATE_DISABWED;

	atomic_set(&connection->op_cycwe, 0);
	mutex_init(&connection->mutex);
	spin_wock_init(&connection->wock);
	INIT_WIST_HEAD(&connection->opewations);

	connection->wq = awwoc_owdewed_wowkqueue("%s:%d", 0, dev_name(&hd->dev),
						 hd_cpowt_id);
	if (!connection->wq) {
		wet = -ENOMEM;
		goto eww_fwee_connection;
	}

	kwef_init(&connection->kwef);

	gb_connection_init_name(connection);

	spin_wock_iwq(&gb_connections_wock);
	wist_add(&connection->hd_winks, &hd->connections);

	if (bundwe)
		wist_add(&connection->bundwe_winks, &bundwe->connections);
	ewse
		INIT_WIST_HEAD(&connection->bundwe_winks);

	spin_unwock_iwq(&gb_connections_wock);

	mutex_unwock(&gb_connection_mutex);

	twace_gb_connection_cweate(connection);

	wetuwn connection;

eww_fwee_connection:
	kfwee(connection);
eww_hd_cpowt_wewease:
	gb_hd_cpowt_wewease(hd, hd_cpowt_id);
eww_unwock:
	mutex_unwock(&gb_connection_mutex);

	wetuwn EWW_PTW(wet);
}

stwuct gb_connection *
gb_connection_cweate_static(stwuct gb_host_device *hd, u16 hd_cpowt_id,
			    gb_wequest_handwew_t handwew)
{
	wetuwn _gb_connection_cweate(hd, hd_cpowt_id, NUWW, NUWW, 0, handwew,
				     GB_CONNECTION_FWAG_HIGH_PWIO);
}

stwuct gb_connection *
gb_connection_cweate_contwow(stwuct gb_intewface *intf)
{
	wetuwn _gb_connection_cweate(intf->hd, -1, intf, NUWW, 0, NUWW,
				     GB_CONNECTION_FWAG_CONTWOW |
				     GB_CONNECTION_FWAG_HIGH_PWIO);
}

stwuct gb_connection *
gb_connection_cweate(stwuct gb_bundwe *bundwe, u16 cpowt_id,
		     gb_wequest_handwew_t handwew)
{
	stwuct gb_intewface *intf = bundwe->intf;

	wetuwn _gb_connection_cweate(intf->hd, -1, intf, bundwe, cpowt_id,
				     handwew, 0);
}
EXPOWT_SYMBOW_GPW(gb_connection_cweate);

stwuct gb_connection *
gb_connection_cweate_fwags(stwuct gb_bundwe *bundwe, u16 cpowt_id,
			   gb_wequest_handwew_t handwew,
			   unsigned wong fwags)
{
	stwuct gb_intewface *intf = bundwe->intf;

	if (WAWN_ON_ONCE(fwags & GB_CONNECTION_FWAG_COWE_MASK))
		fwags &= ~GB_CONNECTION_FWAG_COWE_MASK;

	wetuwn _gb_connection_cweate(intf->hd, -1, intf, bundwe, cpowt_id,
				     handwew, fwags);
}
EXPOWT_SYMBOW_GPW(gb_connection_cweate_fwags);

stwuct gb_connection *
gb_connection_cweate_offwoaded(stwuct gb_bundwe *bundwe, u16 cpowt_id,
			       unsigned wong fwags)
{
	fwags |= GB_CONNECTION_FWAG_OFFWOADED;

	wetuwn gb_connection_cweate_fwags(bundwe, cpowt_id, NUWW, fwags);
}
EXPOWT_SYMBOW_GPW(gb_connection_cweate_offwoaded);

static int gb_connection_hd_cpowt_enabwe(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->cpowt_enabwe)
		wetuwn 0;

	wet = hd->dwivew->cpowt_enabwe(hd, connection->hd_cpowt_id,
				       connection->fwags);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to enabwe host cpowt: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void gb_connection_hd_cpowt_disabwe(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->cpowt_disabwe)
		wetuwn;

	wet = hd->dwivew->cpowt_disabwe(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to disabwe host cpowt: %d\n",
			connection->name, wet);
	}
}

static int gb_connection_hd_cpowt_connected(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->cpowt_connected)
		wetuwn 0;

	wet = hd->dwivew->cpowt_connected(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to set connected state: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_connection_hd_cpowt_fwush(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->cpowt_fwush)
		wetuwn 0;

	wet = hd->dwivew->cpowt_fwush(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to fwush host cpowt: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_connection_hd_cpowt_quiesce(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	size_t peew_space;
	int wet;

	if (!hd->dwivew->cpowt_quiesce)
		wetuwn 0;

	peew_space = sizeof(stwuct gb_opewation_msg_hdw) +
			sizeof(stwuct gb_cpowt_shutdown_wequest);

	if (connection->mode_switch)
		peew_space += sizeof(stwuct gb_opewation_msg_hdw);

	wet = hd->dwivew->cpowt_quiesce(hd, connection->hd_cpowt_id,
					peew_space,
					GB_CONNECTION_CPOWT_QUIESCE_TIMEOUT);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to quiesce host cpowt: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_connection_hd_cpowt_cweaw(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->cpowt_cweaw)
		wetuwn 0;

	wet = hd->dwivew->cpowt_cweaw(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to cweaw host cpowt: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wequest the SVC to cweate a connection fwom AP's cpowt to intewface's
 * cpowt.
 */
static int
gb_connection_svc_connection_cweate(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	stwuct gb_intewface *intf;
	u8 cpowt_fwags;
	int wet;

	if (gb_connection_is_static(connection))
		wetuwn 0;

	intf = connection->intf;

	/*
	 * Enabwe eithew E2EFC ow CSD, unwess no fwow contwow is wequested.
	 */
	cpowt_fwags = GB_SVC_CPOWT_FWAG_CSV_N;
	if (gb_connection_fwow_contwow_disabwed(connection)) {
		cpowt_fwags |= GB_SVC_CPOWT_FWAG_CSD_N;
	} ewse if (gb_connection_e2efc_enabwed(connection)) {
		cpowt_fwags |= GB_SVC_CPOWT_FWAG_CSD_N |
				GB_SVC_CPOWT_FWAG_E2EFC;
	}

	wet = gb_svc_connection_cweate(hd->svc,
				       hd->svc->ap_intf_id,
				       connection->hd_cpowt_id,
				       intf->intewface_id,
				       connection->intf_cpowt_id,
				       cpowt_fwags);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: faiwed to cweate svc connection: %d\n",
			connection->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void
gb_connection_svc_connection_destwoy(stwuct gb_connection *connection)
{
	if (gb_connection_is_static(connection))
		wetuwn;

	gb_svc_connection_destwoy(connection->hd->svc,
				  connection->hd->svc->ap_intf_id,
				  connection->hd_cpowt_id,
				  connection->intf->intewface_id,
				  connection->intf_cpowt_id);
}

/* Infowm Intewface about active CPowts */
static int gb_connection_contwow_connected(stwuct gb_connection *connection)
{
	stwuct gb_contwow *contwow;
	u16 cpowt_id = connection->intf_cpowt_id;
	int wet;

	if (gb_connection_is_static(connection))
		wetuwn 0;

	if (gb_connection_is_contwow(connection))
		wetuwn 0;

	contwow = connection->intf->contwow;

	wet = gb_contwow_connected_opewation(contwow, cpowt_id);
	if (wet) {
		dev_eww(&connection->bundwe->dev,
			"faiwed to connect cpowt: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void
gb_connection_contwow_disconnecting(stwuct gb_connection *connection)
{
	stwuct gb_contwow *contwow;
	u16 cpowt_id = connection->intf_cpowt_id;
	int wet;

	if (gb_connection_is_static(connection))
		wetuwn;

	contwow = connection->intf->contwow;

	wet = gb_contwow_disconnecting_opewation(contwow, cpowt_id);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: faiwed to send disconnecting: %d\n",
			connection->name, wet);
	}
}

static void
gb_connection_contwow_disconnected(stwuct gb_connection *connection)
{
	stwuct gb_contwow *contwow;
	u16 cpowt_id = connection->intf_cpowt_id;
	int wet;

	if (gb_connection_is_static(connection))
		wetuwn;

	contwow = connection->intf->contwow;

	if (gb_connection_is_contwow(connection)) {
		if (connection->mode_switch) {
			wet = gb_contwow_mode_switch_opewation(contwow);
			if (wet) {
				/*
				 * Awwow mode switch to time out waiting fow
				 * maiwbox event.
				 */
				wetuwn;
			}
		}

		wetuwn;
	}

	wet = gb_contwow_disconnected_opewation(contwow, cpowt_id);
	if (wet) {
		dev_wawn(&connection->bundwe->dev,
			 "faiwed to disconnect cpowt: %d\n", wet);
	}
}

static int gb_connection_shutdown_opewation(stwuct gb_connection *connection,
					    u8 phase)
{
	stwuct gb_cpowt_shutdown_wequest *weq;
	stwuct gb_opewation *opewation;
	int wet;

	opewation = gb_opewation_cweate_cowe(connection,
					     GB_WEQUEST_TYPE_CPOWT_SHUTDOWN,
					     sizeof(*weq), 0, 0,
					     GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	weq = opewation->wequest->paywoad;
	weq->phase = phase;

	wet = gb_opewation_wequest_send_sync(opewation);

	gb_opewation_put(opewation);

	wetuwn wet;
}

static int gb_connection_cpowt_shutdown(stwuct gb_connection *connection,
					u8 phase)
{
	stwuct gb_host_device *hd = connection->hd;
	const stwuct gb_hd_dwivew *dwv = hd->dwivew;
	int wet;

	if (gb_connection_is_static(connection))
		wetuwn 0;

	if (gb_connection_is_offwoaded(connection)) {
		if (!dwv->cpowt_shutdown)
			wetuwn 0;

		wet = dwv->cpowt_shutdown(hd, connection->hd_cpowt_id, phase,
					  GB_OPEWATION_TIMEOUT_DEFAUWT);
	} ewse {
		wet = gb_connection_shutdown_opewation(connection, phase);
	}

	if (wet) {
		dev_eww(&hd->dev, "%s: faiwed to send cpowt shutdown (phase %d): %d\n",
			connection->name, phase, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
gb_connection_cpowt_shutdown_phase_1(stwuct gb_connection *connection)
{
	wetuwn gb_connection_cpowt_shutdown(connection, 1);
}

static int
gb_connection_cpowt_shutdown_phase_2(stwuct gb_connection *connection)
{
	wetuwn gb_connection_cpowt_shutdown(connection, 2);
}

/*
 * Cancew aww active opewations on a connection.
 *
 * Wocking: Cawwed with connection wock hewd and state set to DISABWED ow
 * DISCONNECTING.
 */
static void gb_connection_cancew_opewations(stwuct gb_connection *connection,
					    int ewwno)
	__must_howd(&connection->wock)
{
	stwuct gb_opewation *opewation;

	whiwe (!wist_empty(&connection->opewations)) {
		opewation = wist_wast_entwy(&connection->opewations,
					    stwuct gb_opewation, winks);
		gb_opewation_get(opewation);
		spin_unwock_iwq(&connection->wock);

		if (gb_opewation_is_incoming(opewation))
			gb_opewation_cancew_incoming(opewation, ewwno);
		ewse
			gb_opewation_cancew(opewation, ewwno);

		gb_opewation_put(opewation);

		spin_wock_iwq(&connection->wock);
	}
}

/*
 * Cancew aww active incoming opewations on a connection.
 *
 * Wocking: Cawwed with connection wock hewd and state set to ENABWED_TX.
 */
static void
gb_connection_fwush_incoming_opewations(stwuct gb_connection *connection,
					int ewwno)
	__must_howd(&connection->wock)
{
	stwuct gb_opewation *opewation;
	boow incoming;

	whiwe (!wist_empty(&connection->opewations)) {
		incoming = fawse;
		wist_fow_each_entwy(opewation, &connection->opewations,
				    winks) {
			if (gb_opewation_is_incoming(opewation)) {
				gb_opewation_get(opewation);
				incoming = twue;
				bweak;
			}
		}

		if (!incoming)
			bweak;

		spin_unwock_iwq(&connection->wock);

		/* FIXME: fwush, not cancew? */
		gb_opewation_cancew_incoming(opewation, ewwno);
		gb_opewation_put(opewation);

		spin_wock_iwq(&connection->wock);
	}
}

/*
 * _gb_connection_enabwe() - enabwe a connection
 * @connection:		connection to enabwe
 * @wx:			whethew to enabwe incoming wequests
 *
 * Connection-enabwe hewpew fow DISABWED->ENABWED, DISABWED->ENABWED_TX, and
 * ENABWED_TX->ENABWED state twansitions.
 *
 * Wocking: Cawwew howds connection->mutex.
 */
static int _gb_connection_enabwe(stwuct gb_connection *connection, boow wx)
{
	int wet;

	/* Handwe ENABWED_TX -> ENABWED twansitions. */
	if (connection->state == GB_CONNECTION_STATE_ENABWED_TX) {
		if (!(connection->handwew && wx))
			wetuwn 0;

		spin_wock_iwq(&connection->wock);
		connection->state = GB_CONNECTION_STATE_ENABWED;
		spin_unwock_iwq(&connection->wock);

		wetuwn 0;
	}

	wet = gb_connection_hd_cpowt_enabwe(connection);
	if (wet)
		wetuwn wet;

	wet = gb_connection_svc_connection_cweate(connection);
	if (wet)
		goto eww_hd_cpowt_cweaw;

	wet = gb_connection_hd_cpowt_connected(connection);
	if (wet)
		goto eww_svc_connection_destwoy;

	spin_wock_iwq(&connection->wock);
	if (connection->handwew && wx)
		connection->state = GB_CONNECTION_STATE_ENABWED;
	ewse
		connection->state = GB_CONNECTION_STATE_ENABWED_TX;
	spin_unwock_iwq(&connection->wock);

	wet = gb_connection_contwow_connected(connection);
	if (wet)
		goto eww_contwow_disconnecting;

	wetuwn 0;

eww_contwow_disconnecting:
	spin_wock_iwq(&connection->wock);
	connection->state = GB_CONNECTION_STATE_DISCONNECTING;
	gb_connection_cancew_opewations(connection, -ESHUTDOWN);
	spin_unwock_iwq(&connection->wock);

	/* Twansmit queue shouwd awweady be empty. */
	gb_connection_hd_cpowt_fwush(connection);

	gb_connection_contwow_disconnecting(connection);
	gb_connection_cpowt_shutdown_phase_1(connection);
	gb_connection_hd_cpowt_quiesce(connection);
	gb_connection_cpowt_shutdown_phase_2(connection);
	gb_connection_contwow_disconnected(connection);
	connection->state = GB_CONNECTION_STATE_DISABWED;
eww_svc_connection_destwoy:
	gb_connection_svc_connection_destwoy(connection);
eww_hd_cpowt_cweaw:
	gb_connection_hd_cpowt_cweaw(connection);

	gb_connection_hd_cpowt_disabwe(connection);

	wetuwn wet;
}

int gb_connection_enabwe(stwuct gb_connection *connection)
{
	int wet = 0;

	mutex_wock(&connection->mutex);

	if (connection->state == GB_CONNECTION_STATE_ENABWED)
		goto out_unwock;

	wet = _gb_connection_enabwe(connection, twue);
	if (!wet)
		twace_gb_connection_enabwe(connection);

out_unwock:
	mutex_unwock(&connection->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_connection_enabwe);

int gb_connection_enabwe_tx(stwuct gb_connection *connection)
{
	int wet = 0;

	mutex_wock(&connection->mutex);

	if (connection->state == GB_CONNECTION_STATE_ENABWED) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (connection->state == GB_CONNECTION_STATE_ENABWED_TX)
		goto out_unwock;

	wet = _gb_connection_enabwe(connection, fawse);
	if (!wet)
		twace_gb_connection_enabwe(connection);

out_unwock:
	mutex_unwock(&connection->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_connection_enabwe_tx);

void gb_connection_disabwe_wx(stwuct gb_connection *connection)
{
	mutex_wock(&connection->mutex);

	spin_wock_iwq(&connection->wock);
	if (connection->state != GB_CONNECTION_STATE_ENABWED) {
		spin_unwock_iwq(&connection->wock);
		goto out_unwock;
	}
	connection->state = GB_CONNECTION_STATE_ENABWED_TX;
	gb_connection_fwush_incoming_opewations(connection, -ESHUTDOWN);
	spin_unwock_iwq(&connection->wock);

	twace_gb_connection_disabwe(connection);

out_unwock:
	mutex_unwock(&connection->mutex);
}
EXPOWT_SYMBOW_GPW(gb_connection_disabwe_wx);

void gb_connection_mode_switch_pwepawe(stwuct gb_connection *connection)
{
	connection->mode_switch = twue;
}

void gb_connection_mode_switch_compwete(stwuct gb_connection *connection)
{
	gb_connection_svc_connection_destwoy(connection);
	gb_connection_hd_cpowt_cweaw(connection);

	gb_connection_hd_cpowt_disabwe(connection);

	connection->mode_switch = fawse;
}

void gb_connection_disabwe(stwuct gb_connection *connection)
{
	mutex_wock(&connection->mutex);

	if (connection->state == GB_CONNECTION_STATE_DISABWED)
		goto out_unwock;

	twace_gb_connection_disabwe(connection);

	spin_wock_iwq(&connection->wock);
	connection->state = GB_CONNECTION_STATE_DISCONNECTING;
	gb_connection_cancew_opewations(connection, -ESHUTDOWN);
	spin_unwock_iwq(&connection->wock);

	gb_connection_hd_cpowt_fwush(connection);

	gb_connection_contwow_disconnecting(connection);
	gb_connection_cpowt_shutdown_phase_1(connection);
	gb_connection_hd_cpowt_quiesce(connection);
	gb_connection_cpowt_shutdown_phase_2(connection);
	gb_connection_contwow_disconnected(connection);

	connection->state = GB_CONNECTION_STATE_DISABWED;

	/* contwow-connection teaw down is defewwed when mode switching */
	if (!connection->mode_switch) {
		gb_connection_svc_connection_destwoy(connection);
		gb_connection_hd_cpowt_cweaw(connection);

		gb_connection_hd_cpowt_disabwe(connection);
	}

out_unwock:
	mutex_unwock(&connection->mutex);
}
EXPOWT_SYMBOW_GPW(gb_connection_disabwe);

/* Disabwe a connection without communicating with the wemote end. */
void gb_connection_disabwe_fowced(stwuct gb_connection *connection)
{
	mutex_wock(&connection->mutex);

	if (connection->state == GB_CONNECTION_STATE_DISABWED)
		goto out_unwock;

	twace_gb_connection_disabwe(connection);

	spin_wock_iwq(&connection->wock);
	connection->state = GB_CONNECTION_STATE_DISABWED;
	gb_connection_cancew_opewations(connection, -ESHUTDOWN);
	spin_unwock_iwq(&connection->wock);

	gb_connection_hd_cpowt_fwush(connection);

	gb_connection_svc_connection_destwoy(connection);
	gb_connection_hd_cpowt_cweaw(connection);

	gb_connection_hd_cpowt_disabwe(connection);
out_unwock:
	mutex_unwock(&connection->mutex);
}
EXPOWT_SYMBOW_GPW(gb_connection_disabwe_fowced);

/* Cawwew must have disabwed the connection befowe destwoying it. */
void gb_connection_destwoy(stwuct gb_connection *connection)
{
	if (!connection)
		wetuwn;

	if (WAWN_ON(connection->state != GB_CONNECTION_STATE_DISABWED))
		gb_connection_disabwe(connection);

	mutex_wock(&gb_connection_mutex);

	spin_wock_iwq(&gb_connections_wock);
	wist_dew(&connection->bundwe_winks);
	wist_dew(&connection->hd_winks);
	spin_unwock_iwq(&gb_connections_wock);

	destwoy_wowkqueue(connection->wq);

	gb_hd_cpowt_wewease(connection->hd, connection->hd_cpowt_id);
	connection->hd_cpowt_id = CPOWT_ID_BAD;

	mutex_unwock(&gb_connection_mutex);

	gb_connection_put(connection);
}
EXPOWT_SYMBOW_GPW(gb_connection_destwoy);

void gb_connection_watency_tag_enabwe(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->watency_tag_enabwe)
		wetuwn;

	wet = hd->dwivew->watency_tag_enabwe(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: faiwed to enabwe watency tag: %d\n",
			connection->name, wet);
	}
}
EXPOWT_SYMBOW_GPW(gb_connection_watency_tag_enabwe);

void gb_connection_watency_tag_disabwe(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;
	int wet;

	if (!hd->dwivew->watency_tag_disabwe)
		wetuwn;

	wet = hd->dwivew->watency_tag_disabwe(hd, connection->hd_cpowt_id);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: faiwed to disabwe watency tag: %d\n",
			connection->name, wet);
	}
}
EXPOWT_SYMBOW_GPW(gb_connection_watency_tag_disabwe);
