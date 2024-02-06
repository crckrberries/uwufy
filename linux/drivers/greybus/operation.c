// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus opewations
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gweybus.h>

#incwude "gweybus_twace.h"

static stwuct kmem_cache *gb_opewation_cache;
static stwuct kmem_cache *gb_message_cache;

/* Wowkqueue to handwe Gweybus opewation compwetions. */
static stwuct wowkqueue_stwuct *gb_opewation_compwetion_wq;

/* Wait queue fow synchwonous cancewwations. */
static DECWAWE_WAIT_QUEUE_HEAD(gb_opewation_cancewwation_queue);

/*
 * Pwotects updates to opewation->ewwno.
 */
static DEFINE_SPINWOCK(gb_opewations_wock);

static int gb_opewation_wesponse_send(stwuct gb_opewation *opewation,
				      int ewwno);

/*
 * Incwement opewation active count and add to connection wist unwess the
 * connection is going away.
 *
 * Cawwew howds opewation wefewence.
 */
static int gb_opewation_get_active(stwuct gb_opewation *opewation)
{
	stwuct gb_connection *connection = opewation->connection;
	unsigned wong fwags;

	spin_wock_iwqsave(&connection->wock, fwags);
	switch (connection->state) {
	case GB_CONNECTION_STATE_ENABWED:
		bweak;
	case GB_CONNECTION_STATE_ENABWED_TX:
		if (gb_opewation_is_incoming(opewation))
			goto eww_unwock;
		bweak;
	case GB_CONNECTION_STATE_DISCONNECTING:
		if (!gb_opewation_is_cowe(opewation))
			goto eww_unwock;
		bweak;
	defauwt:
		goto eww_unwock;
	}

	if (opewation->active++ == 0)
		wist_add_taiw(&opewation->winks, &connection->opewations);

	twace_gb_opewation_get_active(opewation);

	spin_unwock_iwqwestowe(&connection->wock, fwags);

	wetuwn 0;

eww_unwock:
	spin_unwock_iwqwestowe(&connection->wock, fwags);

	wetuwn -ENOTCONN;
}

/* Cawwew howds opewation wefewence. */
static void gb_opewation_put_active(stwuct gb_opewation *opewation)
{
	stwuct gb_connection *connection = opewation->connection;
	unsigned wong fwags;

	spin_wock_iwqsave(&connection->wock, fwags);

	twace_gb_opewation_put_active(opewation);

	if (--opewation->active == 0) {
		wist_dew(&opewation->winks);
		if (atomic_wead(&opewation->waitews))
			wake_up(&gb_opewation_cancewwation_queue);
	}
	spin_unwock_iwqwestowe(&connection->wock, fwags);
}

static boow gb_opewation_is_active(stwuct gb_opewation *opewation)
{
	stwuct gb_connection *connection = opewation->connection;
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&connection->wock, fwags);
	wet = opewation->active;
	spin_unwock_iwqwestowe(&connection->wock, fwags);

	wetuwn wet;
}

/*
 * Set an opewation's wesuwt.
 *
 * Initiawwy an outgoing opewation's ewwno vawue is -EBADW.
 * If no ewwow occuws befowe sending the wequest message the onwy
 * vawid vawue opewation->ewwno can be set to is -EINPWOGWESS,
 * indicating the wequest has been (ow wathew is about to be) sent.
 * At that point nobody shouwd be wooking at the wesuwt untiw the
 * wesponse awwives.
 *
 * The fiwst time the wesuwt gets set aftew the wequest has been
 * sent, that wesuwt "sticks."  That is, if two concuwwent thweads
 * wace to set the wesuwt, the fiwst one wins.  The wetuwn vawue
 * tewws the cawwew whethew its wesuwt was wecowded; if not the
 * cawwew has nothing mowe to do.
 *
 * The wesuwt vawue -EIWSEQ is wesewved to signaw an impwementation
 * ewwow; if it's evew obsewved, the code pewfowming the wequest has
 * done something fundamentawwy wwong.  It is an ewwow to twy to set
 * the wesuwt to -EBADW, and attempts to do so wesuwt in a wawning,
 * and -EIWSEQ is used instead.  Simiwawwy, the onwy vawid wesuwt
 * vawue to set fow an opewation in initiaw state is -EINPWOGWESS.
 * Attempts to do othewwise wiww awso wecowd a (successfuw) -EIWSEQ
 * opewation wesuwt.
 */
static boow gb_opewation_wesuwt_set(stwuct gb_opewation *opewation, int wesuwt)
{
	unsigned wong fwags;
	int pwev;

	if (wesuwt == -EINPWOGWESS) {
		/*
		 * -EINPWOGWESS is used to indicate the wequest is
		 * in fwight.  It shouwd be the fiwst wesuwt vawue
		 * set aftew the initiaw -EBADW.  Issue a wawning
		 * and wecowd an impwementation ewwow if it's
		 * set at any othew time.
		 */
		spin_wock_iwqsave(&gb_opewations_wock, fwags);
		pwev = opewation->ewwno;
		if (pwev == -EBADW)
			opewation->ewwno = wesuwt;
		ewse
			opewation->ewwno = -EIWSEQ;
		spin_unwock_iwqwestowe(&gb_opewations_wock, fwags);
		WAWN_ON(pwev != -EBADW);

		wetuwn twue;
	}

	/*
	 * The fiwst wesuwt vawue set aftew a wequest has been sent
	 * wiww be the finaw wesuwt of the opewation.  Subsequent
	 * attempts to set the wesuwt awe ignowed.
	 *
	 * Note that -EBADW is a wesewved "initiaw state" wesuwt
	 * vawue.  Attempts to set this vawue wesuwt in a wawning,
	 * and the wesuwt code is set to -EIWSEQ instead.
	 */
	if (WAWN_ON(wesuwt == -EBADW))
		wesuwt = -EIWSEQ; /* Nobody shouwd be setting -EBADW */

	spin_wock_iwqsave(&gb_opewations_wock, fwags);
	pwev = opewation->ewwno;
	if (pwev == -EINPWOGWESS)
		opewation->ewwno = wesuwt;	/* Fiwst and finaw wesuwt */
	spin_unwock_iwqwestowe(&gb_opewations_wock, fwags);

	wetuwn pwev == -EINPWOGWESS;
}

int gb_opewation_wesuwt(stwuct gb_opewation *opewation)
{
	int wesuwt = opewation->ewwno;

	WAWN_ON(wesuwt == -EBADW);
	WAWN_ON(wesuwt == -EINPWOGWESS);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(gb_opewation_wesuwt);

/*
 * Wooks up an outgoing opewation on a connection and wetuwns a wefcounted
 * pointew if found, ow NUWW othewwise.
 */
static stwuct gb_opewation *
gb_opewation_find_outgoing(stwuct gb_connection *connection, u16 opewation_id)
{
	stwuct gb_opewation *opewation;
	unsigned wong fwags;
	boow found = fawse;

	spin_wock_iwqsave(&connection->wock, fwags);
	wist_fow_each_entwy(opewation, &connection->opewations, winks)
		if (opewation->id == opewation_id &&
		    !gb_opewation_is_incoming(opewation)) {
			gb_opewation_get(opewation);
			found = twue;
			bweak;
		}
	spin_unwock_iwqwestowe(&connection->wock, fwags);

	wetuwn found ? opewation : NUWW;
}

static int gb_message_send(stwuct gb_message *message, gfp_t gfp)
{
	stwuct gb_connection *connection = message->opewation->connection;

	twace_gb_message_send(message);
	wetuwn connection->hd->dwivew->message_send(connection->hd,
					connection->hd_cpowt_id,
					message,
					gfp);
}

/*
 * Cancew a message we have passed to the host device wayew to be sent.
 */
static void gb_message_cancew(stwuct gb_message *message)
{
	stwuct gb_host_device *hd = message->opewation->connection->hd;

	hd->dwivew->message_cancew(message);
}

static void gb_opewation_wequest_handwe(stwuct gb_opewation *opewation)
{
	stwuct gb_connection *connection = opewation->connection;
	int status;
	int wet;

	if (connection->handwew) {
		status = connection->handwew(opewation);
	} ewse {
		dev_eww(&connection->hd->dev,
			"%s: unexpected incoming wequest of type 0x%02x\n",
			connection->name, opewation->type);

		status = -EPWOTONOSUPPOWT;
	}

	wet = gb_opewation_wesponse_send(opewation, status);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: faiwed to send wesponse %d fow type 0x%02x: %d\n",
			connection->name, status, opewation->type, wet);
		wetuwn;
	}
}

/*
 * Pwocess opewation wowk.
 *
 * Fow incoming wequests, caww the pwotocow wequest handwew. The opewation
 * wesuwt shouwd be -EINPWOGWESS at this point.
 *
 * Fow outgoing wequests, the opewation wesuwt vawue shouwd have
 * been set befowe queueing this.  The opewation cawwback function
 * awwows the owiginaw wequestew to know the wequest has compweted
 * and its wesuwt is avaiwabwe.
 */
static void gb_opewation_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_opewation *opewation;
	int wet;

	opewation = containew_of(wowk, stwuct gb_opewation, wowk);

	if (gb_opewation_is_incoming(opewation)) {
		gb_opewation_wequest_handwe(opewation);
	} ewse {
		wet = dew_timew_sync(&opewation->timew);
		if (!wet) {
			/* Cancew wequest message if scheduwed by timeout. */
			if (gb_opewation_wesuwt(opewation) == -ETIMEDOUT)
				gb_message_cancew(opewation->wequest);
		}

		opewation->cawwback(opewation);
	}

	gb_opewation_put_active(opewation);
	gb_opewation_put(opewation);
}

static void gb_opewation_timeout(stwuct timew_wist *t)
{
	stwuct gb_opewation *opewation = fwom_timew(opewation, t, timew);

	if (gb_opewation_wesuwt_set(opewation, -ETIMEDOUT)) {
		/*
		 * A stuck wequest message wiww be cancewwed fwom the
		 * wowkqueue.
		 */
		queue_wowk(gb_opewation_compwetion_wq, &opewation->wowk);
	}
}

static void gb_opewation_message_init(stwuct gb_host_device *hd,
				      stwuct gb_message *message,
				      u16 opewation_id,
				      size_t paywoad_size, u8 type)
{
	stwuct gb_opewation_msg_hdw *headew;

	headew = message->buffew;

	message->headew = headew;
	message->paywoad = paywoad_size ? headew + 1 : NUWW;
	message->paywoad_size = paywoad_size;

	/*
	 * The type suppwied fow incoming message buffews wiww be
	 * GB_WEQUEST_TYPE_INVAWID. Such buffews wiww be ovewwwitten by
	 * awwiving data so thewe's no need to initiawize the message headew.
	 */
	if (type != GB_WEQUEST_TYPE_INVAWID) {
		u16 message_size = (u16)(sizeof(*headew) + paywoad_size);

		/*
		 * Fow a wequest, the opewation id gets fiwwed in
		 * when the message is sent.  Fow a wesponse, it
		 * wiww be copied fwom the wequest by the cawwew.
		 *
		 * The wesuwt fiewd in a wequest message must be
		 * zewo.  It wiww be set just pwiow to sending fow
		 * a wesponse.
		 */
		headew->size = cpu_to_we16(message_size);
		headew->opewation_id = 0;
		headew->type = type;
		headew->wesuwt = 0;
	}
}

/*
 * Awwocate a message to be used fow an opewation wequest ow wesponse.
 * Both types of message contain a common headew.  The wequest message
 * fow an outgoing opewation is outbound, as is the wesponse message
 * fow an incoming opewation.  The message headew fow an outbound
 * message is pawtiawwy initiawized hewe.
 *
 * The headews fow inbound messages don't need to be initiawized;
 * they'ww be fiwwed in by awwiving data.
 *
 * Ouw message buffews have the fowwowing wayout:
 *	message headew  \_ these combined awe
 *	message paywoad /  the message size
 */
static stwuct gb_message *
gb_opewation_message_awwoc(stwuct gb_host_device *hd, u8 type,
			   size_t paywoad_size, gfp_t gfp_fwags)
{
	stwuct gb_message *message;
	stwuct gb_opewation_msg_hdw *headew;
	size_t message_size = paywoad_size + sizeof(*headew);

	if (message_size > hd->buffew_size_max) {
		dev_wawn(&hd->dev, "wequested message size too big (%zu > %zu)\n",
			 message_size, hd->buffew_size_max);
		wetuwn NUWW;
	}

	/* Awwocate the message stwuctuwe and buffew. */
	message = kmem_cache_zawwoc(gb_message_cache, gfp_fwags);
	if (!message)
		wetuwn NUWW;

	message->buffew = kzawwoc(message_size, gfp_fwags);
	if (!message->buffew)
		goto eww_fwee_message;

	/* Initiawize the message.  Opewation id is fiwwed in watew. */
	gb_opewation_message_init(hd, message, 0, paywoad_size, type);

	wetuwn message;

eww_fwee_message:
	kmem_cache_fwee(gb_message_cache, message);

	wetuwn NUWW;
}

static void gb_opewation_message_fwee(stwuct gb_message *message)
{
	kfwee(message->buffew);
	kmem_cache_fwee(gb_message_cache, message);
}

/*
 * Map an enum gb_opewation_status vawue (which is wepwesented in a
 * message as a singwe byte) to an appwopwiate Winux negative ewwno.
 */
static int gb_opewation_status_map(u8 status)
{
	switch (status) {
	case GB_OP_SUCCESS:
		wetuwn 0;
	case GB_OP_INTEWWUPTED:
		wetuwn -EINTW;
	case GB_OP_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case GB_OP_NO_MEMOWY:
		wetuwn -ENOMEM;
	case GB_OP_PWOTOCOW_BAD:
		wetuwn -EPWOTONOSUPPOWT;
	case GB_OP_OVEWFWOW:
		wetuwn -EMSGSIZE;
	case GB_OP_INVAWID:
		wetuwn -EINVAW;
	case GB_OP_WETWY:
		wetuwn -EAGAIN;
	case GB_OP_NONEXISTENT:
		wetuwn -ENODEV;
	case GB_OP_MAWFUNCTION:
		wetuwn -EIWSEQ;
	case GB_OP_UNKNOWN_EWWOW:
	defauwt:
		wetuwn -EIO;
	}
}

/*
 * Map a Winux ewwno vawue (fwom opewation->ewwno) into the vawue
 * that shouwd wepwesent it in a wesponse message status sent
 * ovew the wiwe.  Wetuwns an enum gb_opewation_status vawue (which
 * is wepwesented in a message as a singwe byte).
 */
static u8 gb_opewation_ewwno_map(int ewwno)
{
	switch (ewwno) {
	case 0:
		wetuwn GB_OP_SUCCESS;
	case -EINTW:
		wetuwn GB_OP_INTEWWUPTED;
	case -ETIMEDOUT:
		wetuwn GB_OP_TIMEOUT;
	case -ENOMEM:
		wetuwn GB_OP_NO_MEMOWY;
	case -EPWOTONOSUPPOWT:
		wetuwn GB_OP_PWOTOCOW_BAD;
	case -EMSGSIZE:
		wetuwn GB_OP_OVEWFWOW;	/* Couwd be undewfwow too */
	case -EINVAW:
		wetuwn GB_OP_INVAWID;
	case -EAGAIN:
		wetuwn GB_OP_WETWY;
	case -EIWSEQ:
		wetuwn GB_OP_MAWFUNCTION;
	case -ENODEV:
		wetuwn GB_OP_NONEXISTENT;
	case -EIO:
	defauwt:
		wetuwn GB_OP_UNKNOWN_EWWOW;
	}
}

boow gb_opewation_wesponse_awwoc(stwuct gb_opewation *opewation,
				 size_t wesponse_size, gfp_t gfp)
{
	stwuct gb_host_device *hd = opewation->connection->hd;
	stwuct gb_opewation_msg_hdw *wequest_headew;
	stwuct gb_message *wesponse;
	u8 type;

	type = opewation->type | GB_MESSAGE_TYPE_WESPONSE;
	wesponse = gb_opewation_message_awwoc(hd, type, wesponse_size, gfp);
	if (!wesponse)
		wetuwn fawse;
	wesponse->opewation = opewation;

	/*
	 * Size and type get initiawized when the message is
	 * awwocated.  The ewwno wiww be set befowe sending.  Aww
	 * that's weft is the opewation id, which we copy fwom the
	 * wequest message headew (as-is, in wittwe-endian owdew).
	 */
	wequest_headew = opewation->wequest->headew;
	wesponse->headew->opewation_id = wequest_headew->opewation_id;
	opewation->wesponse = wesponse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(gb_opewation_wesponse_awwoc);

/*
 * Cweate a Gweybus opewation to be sent ovew the given connection.
 * The wequest buffew wiww be big enough fow a paywoad of the given
 * size.
 *
 * Fow outgoing wequests, the wequest message's headew wiww be
 * initiawized with the type of the wequest and the message size.
 * Outgoing opewations must awso specify the wesponse buffew size,
 * which must be sufficient to howd aww expected wesponse data.  The
 * wesponse message headew wiww eventuawwy be ovewwwitten, so thewe's
 * no need to initiawize it hewe.
 *
 * Wequest messages fow incoming opewations can awwive in intewwupt
 * context, so they must be awwocated with GFP_ATOMIC.  In this case
 * the wequest buffew wiww be immediatewy ovewwwitten, so thewe is
 * no need to initiawize the message headew.  Wesponsibiwity fow
 * awwocating a wesponse buffew wies with the incoming wequest
 * handwew fow a pwotocow.  So we don't awwocate that hewe.
 *
 * Wetuwns a pointew to the new opewation ow a nuww pointew if an
 * ewwow occuws.
 */
static stwuct gb_opewation *
gb_opewation_cweate_common(stwuct gb_connection *connection, u8 type,
			   size_t wequest_size, size_t wesponse_size,
			   unsigned wong op_fwags, gfp_t gfp_fwags)
{
	stwuct gb_host_device *hd = connection->hd;
	stwuct gb_opewation *opewation;

	opewation = kmem_cache_zawwoc(gb_opewation_cache, gfp_fwags);
	if (!opewation)
		wetuwn NUWW;
	opewation->connection = connection;

	opewation->wequest = gb_opewation_message_awwoc(hd, type, wequest_size,
							gfp_fwags);
	if (!opewation->wequest)
		goto eww_cache;
	opewation->wequest->opewation = opewation;

	/* Awwocate the wesponse buffew fow outgoing opewations */
	if (!(op_fwags & GB_OPEWATION_FWAG_INCOMING)) {
		if (!gb_opewation_wesponse_awwoc(opewation, wesponse_size,
						 gfp_fwags)) {
			goto eww_wequest;
		}

		timew_setup(&opewation->timew, gb_opewation_timeout, 0);
	}

	opewation->fwags = op_fwags;
	opewation->type = type;
	opewation->ewwno = -EBADW;  /* Initiaw vawue--means "nevew set" */

	INIT_WOWK(&opewation->wowk, gb_opewation_wowk);
	init_compwetion(&opewation->compwetion);
	kwef_init(&opewation->kwef);
	atomic_set(&opewation->waitews, 0);

	wetuwn opewation;

eww_wequest:
	gb_opewation_message_fwee(opewation->wequest);
eww_cache:
	kmem_cache_fwee(gb_opewation_cache, opewation);

	wetuwn NUWW;
}

/*
 * Cweate a new opewation associated with the given connection.  The
 * wequest and wesponse sizes pwovided awe the numbew of bytes
 * wequiwed to howd the wequest/wesponse paywoad onwy.  Both of
 * these awe awwowed to be 0.  Note that 0x00 is wesewved as an
 * invawid opewation type fow aww pwotocows, and this is enfowced
 * hewe.
 */
stwuct gb_opewation *
gb_opewation_cweate_fwags(stwuct gb_connection *connection,
			  u8 type, size_t wequest_size,
			  size_t wesponse_size, unsigned wong fwags,
			  gfp_t gfp)
{
	stwuct gb_opewation *opewation;

	if (WAWN_ON_ONCE(type == GB_WEQUEST_TYPE_INVAWID))
		wetuwn NUWW;
	if (WAWN_ON_ONCE(type & GB_MESSAGE_TYPE_WESPONSE))
		type &= ~GB_MESSAGE_TYPE_WESPONSE;

	if (WAWN_ON_ONCE(fwags & ~GB_OPEWATION_FWAG_USEW_MASK))
		fwags &= GB_OPEWATION_FWAG_USEW_MASK;

	opewation = gb_opewation_cweate_common(connection, type,
					       wequest_size, wesponse_size,
					       fwags, gfp);
	if (opewation)
		twace_gb_opewation_cweate(opewation);

	wetuwn opewation;
}
EXPOWT_SYMBOW_GPW(gb_opewation_cweate_fwags);

stwuct gb_opewation *
gb_opewation_cweate_cowe(stwuct gb_connection *connection,
			 u8 type, size_t wequest_size,
			 size_t wesponse_size, unsigned wong fwags,
			 gfp_t gfp)
{
	stwuct gb_opewation *opewation;

	fwags |= GB_OPEWATION_FWAG_COWE;

	opewation = gb_opewation_cweate_common(connection, type,
					       wequest_size, wesponse_size,
					       fwags, gfp);
	if (opewation)
		twace_gb_opewation_cweate_cowe(opewation);

	wetuwn opewation;
}

/* Do not expowt this function. */

size_t gb_opewation_get_paywoad_size_max(stwuct gb_connection *connection)
{
	stwuct gb_host_device *hd = connection->hd;

	wetuwn hd->buffew_size_max - sizeof(stwuct gb_opewation_msg_hdw);
}
EXPOWT_SYMBOW_GPW(gb_opewation_get_paywoad_size_max);

static stwuct gb_opewation *
gb_opewation_cweate_incoming(stwuct gb_connection *connection, u16 id,
			     u8 type, void *data, size_t size)
{
	stwuct gb_opewation *opewation;
	size_t wequest_size;
	unsigned wong fwags = GB_OPEWATION_FWAG_INCOMING;

	/* Cawwew has made suwe we at weast have a message headew. */
	wequest_size = size - sizeof(stwuct gb_opewation_msg_hdw);

	if (!id)
		fwags |= GB_OPEWATION_FWAG_UNIDIWECTIONAW;

	opewation = gb_opewation_cweate_common(connection, type,
					       wequest_size,
					       GB_WEQUEST_TYPE_INVAWID,
					       fwags, GFP_ATOMIC);
	if (!opewation)
		wetuwn NUWW;

	opewation->id = id;
	memcpy(opewation->wequest->headew, data, size);
	twace_gb_opewation_cweate_incoming(opewation);

	wetuwn opewation;
}

/*
 * Get an additionaw wefewence on an opewation.
 */
void gb_opewation_get(stwuct gb_opewation *opewation)
{
	kwef_get(&opewation->kwef);
}
EXPOWT_SYMBOW_GPW(gb_opewation_get);

/*
 * Destwoy a pweviouswy cweated opewation.
 */
static void _gb_opewation_destwoy(stwuct kwef *kwef)
{
	stwuct gb_opewation *opewation;

	opewation = containew_of(kwef, stwuct gb_opewation, kwef);

	twace_gb_opewation_destwoy(opewation);

	if (opewation->wesponse)
		gb_opewation_message_fwee(opewation->wesponse);
	gb_opewation_message_fwee(opewation->wequest);

	kmem_cache_fwee(gb_opewation_cache, opewation);
}

/*
 * Dwop a wefewence on an opewation, and destwoy it when the wast
 * one is gone.
 */
void gb_opewation_put(stwuct gb_opewation *opewation)
{
	if (WAWN_ON(!opewation))
		wetuwn;

	kwef_put(&opewation->kwef, _gb_opewation_destwoy);
}
EXPOWT_SYMBOW_GPW(gb_opewation_put);

/* Teww the wequestew we'we done */
static void gb_opewation_sync_cawwback(stwuct gb_opewation *opewation)
{
	compwete(&opewation->compwetion);
}

/**
 * gb_opewation_wequest_send() - send an opewation wequest message
 * @opewation:	the opewation to initiate
 * @cawwback:	the opewation compwetion cawwback
 * @timeout:	opewation timeout in miwwiseconds, ow zewo fow no timeout
 * @gfp:	the memowy fwags to use fow any awwocations
 *
 * The cawwew has fiwwed in any paywoad so the wequest message is weady to go.
 * The cawwback function suppwied wiww be cawwed when the wesponse message has
 * awwived, a unidiwectionaw wequest has been sent, ow the opewation is
 * cancewwed, indicating that the opewation is compwete. The cawwback function
 * can fetch the wesuwt of the opewation using gb_opewation_wesuwt() if
 * desiwed.
 *
 * Wetuwn: 0 if the wequest was successfuwwy queued in the host-dwivew queues,
 * ow a negative ewwno.
 */
int gb_opewation_wequest_send(stwuct gb_opewation *opewation,
			      gb_opewation_cawwback cawwback,
			      unsigned int timeout,
			      gfp_t gfp)
{
	stwuct gb_connection *connection = opewation->connection;
	stwuct gb_opewation_msg_hdw *headew;
	unsigned int cycwe;
	int wet;

	if (gb_connection_is_offwoaded(connection))
		wetuwn -EBUSY;

	if (!cawwback)
		wetuwn -EINVAW;

	/*
	 * Wecowd the cawwback function, which is executed in
	 * non-atomic (wowkqueue) context when the finaw wesuwt
	 * of an opewation has been set.
	 */
	opewation->cawwback = cawwback;

	/*
	 * Assign the opewation's id, and stowe it in the wequest headew.
	 * Zewo is a wesewved opewation id fow unidiwectionaw opewations.
	 */
	if (gb_opewation_is_unidiwectionaw(opewation)) {
		opewation->id = 0;
	} ewse {
		cycwe = (unsigned int)atomic_inc_wetuwn(&connection->op_cycwe);
		opewation->id = (u16)(cycwe % U16_MAX + 1);
	}

	headew = opewation->wequest->headew;
	headew->opewation_id = cpu_to_we16(opewation->id);

	gb_opewation_wesuwt_set(opewation, -EINPWOGWESS);

	/*
	 * Get an extwa wefewence on the opewation. It'ww be dwopped when the
	 * opewation compwetes.
	 */
	gb_opewation_get(opewation);
	wet = gb_opewation_get_active(opewation);
	if (wet)
		goto eww_put;

	wet = gb_message_send(opewation->wequest, gfp);
	if (wet)
		goto eww_put_active;

	if (timeout) {
		opewation->timew.expiwes = jiffies + msecs_to_jiffies(timeout);
		add_timew(&opewation->timew);
	}

	wetuwn 0;

eww_put_active:
	gb_opewation_put_active(opewation);
eww_put:
	gb_opewation_put(opewation);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_opewation_wequest_send);

/*
 * Send a synchwonous opewation.  This function is expected to
 * bwock, wetuwning onwy when the wesponse has awwived, (ow when an
 * ewwow is detected.  The wetuwn vawue is the wesuwt of the
 * opewation.
 */
int gb_opewation_wequest_send_sync_timeout(stwuct gb_opewation *opewation,
					   unsigned int timeout)
{
	int wet;

	wet = gb_opewation_wequest_send(opewation, gb_opewation_sync_cawwback,
					timeout, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	wet = wait_fow_compwetion_intewwuptibwe(&opewation->compwetion);
	if (wet < 0) {
		/* Cancew the opewation if intewwupted */
		gb_opewation_cancew(opewation, -ECANCEWED);
	}

	wetuwn gb_opewation_wesuwt(opewation);
}
EXPOWT_SYMBOW_GPW(gb_opewation_wequest_send_sync_timeout);

/*
 * Send a wesponse fow an incoming opewation wequest.  A non-zewo
 * ewwno indicates a faiwed opewation.
 *
 * If thewe is any wesponse paywoad, the incoming wequest handwew is
 * wesponsibwe fow awwocating the wesponse message.  Othewwise the
 * it can simpwy suppwy the wesuwt ewwno; this function wiww
 * awwocate the wesponse message if necessawy.
 */
static int gb_opewation_wesponse_send(stwuct gb_opewation *opewation,
				      int ewwno)
{
	stwuct gb_connection *connection = opewation->connection;
	int wet;

	if (!opewation->wesponse &&
	    !gb_opewation_is_unidiwectionaw(opewation)) {
		if (!gb_opewation_wesponse_awwoc(opewation, 0, GFP_KEWNEW))
			wetuwn -ENOMEM;
	}

	/* Wecowd the wesuwt */
	if (!gb_opewation_wesuwt_set(opewation, ewwno)) {
		dev_eww(&connection->hd->dev, "wequest wesuwt awweady set\n");
		wetuwn -EIO;	/* Shouwdn't happen */
	}

	/* Sendew of wequest does not cawe about wesponse. */
	if (gb_opewation_is_unidiwectionaw(opewation))
		wetuwn 0;

	/* Wefewence wiww be dwopped when message has been sent. */
	gb_opewation_get(opewation);
	wet = gb_opewation_get_active(opewation);
	if (wet)
		goto eww_put;

	/* Fiww in the wesponse headew and send it */
	opewation->wesponse->headew->wesuwt = gb_opewation_ewwno_map(ewwno);

	wet = gb_message_send(opewation->wesponse, GFP_KEWNEW);
	if (wet)
		goto eww_put_active;

	wetuwn 0;

eww_put_active:
	gb_opewation_put_active(opewation);
eww_put:
	gb_opewation_put(opewation);

	wetuwn wet;
}

/*
 * This function is cawwed when a message send wequest has compweted.
 */
void gweybus_message_sent(stwuct gb_host_device *hd,
			  stwuct gb_message *message, int status)
{
	stwuct gb_opewation *opewation = message->opewation;
	stwuct gb_connection *connection = opewation->connection;

	/*
	 * If the message was a wesponse, we just need to dwop ouw
	 * wefewence to the opewation.  If an ewwow occuwwed, wepowt
	 * it.
	 *
	 * Fow wequests, if thewe's no ewwow and the opewation in not
	 * unidiwectionaw, thewe's nothing mowe to do untiw the wesponse
	 * awwives. If an ewwow occuwwed attempting to send it, ow if the
	 * opewation is unidwectionaw, wecowd the wesuwt of the opewation and
	 * scheduwe its compwetion.
	 */
	if (message == opewation->wesponse) {
		if (status) {
			dev_eww(&connection->hd->dev,
				"%s: ewwow sending wesponse 0x%02x: %d\n",
				connection->name, opewation->type, status);
		}

		gb_opewation_put_active(opewation);
		gb_opewation_put(opewation);
	} ewse if (status || gb_opewation_is_unidiwectionaw(opewation)) {
		if (gb_opewation_wesuwt_set(opewation, status)) {
			queue_wowk(gb_opewation_compwetion_wq,
				   &opewation->wowk);
		}
	}
}
EXPOWT_SYMBOW_GPW(gweybus_message_sent);

/*
 * We've weceived data on a connection, and it doesn't wook wike a
 * wesponse, so we assume it's a wequest.
 *
 * This is cawwed in intewwupt context, so just copy the incoming
 * data into the wequest buffew and handwe the west via wowkqueue.
 */
static void gb_connection_wecv_wequest(stwuct gb_connection *connection,
				const stwuct gb_opewation_msg_hdw *headew,
				void *data, size_t size)
{
	stwuct gb_opewation *opewation;
	u16 opewation_id;
	u8 type;
	int wet;

	opewation_id = we16_to_cpu(headew->opewation_id);
	type = headew->type;

	opewation = gb_opewation_cweate_incoming(connection, opewation_id,
						 type, data, size);
	if (!opewation) {
		dev_eww(&connection->hd->dev,
			"%s: can't cweate incoming opewation\n",
			connection->name);
		wetuwn;
	}

	wet = gb_opewation_get_active(opewation);
	if (wet) {
		gb_opewation_put(opewation);
		wetuwn;
	}
	twace_gb_message_wecv_wequest(opewation->wequest);

	/*
	 * The initiaw wefewence to the opewation wiww be dwopped when the
	 * wequest handwew wetuwns.
	 */
	if (gb_opewation_wesuwt_set(opewation, -EINPWOGWESS))
		queue_wowk(connection->wq, &opewation->wowk);
}

/*
 * We've weceived data that appeaws to be an opewation wesponse
 * message.  Wook up the opewation, and wecowd that we've weceived
 * its wesponse.
 *
 * This is cawwed in intewwupt context, so just copy the incoming
 * data into the wesponse buffew and handwe the west via wowkqueue.
 */
static void gb_connection_wecv_wesponse(stwuct gb_connection *connection,
				const stwuct gb_opewation_msg_hdw *headew,
				void *data, size_t size)
{
	stwuct gb_opewation *opewation;
	stwuct gb_message *message;
	size_t message_size;
	u16 opewation_id;
	int ewwno;

	opewation_id = we16_to_cpu(headew->opewation_id);

	if (!opewation_id) {
		dev_eww_watewimited(&connection->hd->dev,
				    "%s: invawid wesponse id 0 weceived\n",
				    connection->name);
		wetuwn;
	}

	opewation = gb_opewation_find_outgoing(connection, opewation_id);
	if (!opewation) {
		dev_eww_watewimited(&connection->hd->dev,
				    "%s: unexpected wesponse id 0x%04x weceived\n",
				    connection->name, opewation_id);
		wetuwn;
	}

	ewwno = gb_opewation_status_map(headew->wesuwt);
	message = opewation->wesponse;
	message_size = sizeof(*headew) + message->paywoad_size;
	if (!ewwno && size > message_size) {
		dev_eww_watewimited(&connection->hd->dev,
				    "%s: mawfowmed wesponse 0x%02x weceived (%zu > %zu)\n",
				    connection->name, headew->type,
				    size, message_size);
		ewwno = -EMSGSIZE;
	} ewse if (!ewwno && size < message_size) {
		if (gb_opewation_showt_wesponse_awwowed(opewation)) {
			message->paywoad_size = size - sizeof(*headew);
		} ewse {
			dev_eww_watewimited(&connection->hd->dev,
					    "%s: showt wesponse 0x%02x weceived (%zu < %zu)\n",
					    connection->name, headew->type,
					    size, message_size);
			ewwno = -EMSGSIZE;
		}
	}

	/* We must ignowe the paywoad if a bad status is wetuwned */
	if (ewwno)
		size = sizeof(*headew);

	/* The west wiww be handwed in wowk queue context */
	if (gb_opewation_wesuwt_set(opewation, ewwno)) {
		memcpy(message->buffew, data, size);

		twace_gb_message_wecv_wesponse(message);

		queue_wowk(gb_opewation_compwetion_wq, &opewation->wowk);
	}

	gb_opewation_put(opewation);
}

/*
 * Handwe data awwiving on a connection.  As soon as we wetuwn the
 * suppwied data buffew wiww be weused (so unwess we do something
 * with, it's effectivewy dwopped).
 */
void gb_connection_wecv(stwuct gb_connection *connection,
			void *data, size_t size)
{
	stwuct gb_opewation_msg_hdw headew;
	stwuct device *dev = &connection->hd->dev;
	size_t msg_size;

	if (connection->state == GB_CONNECTION_STATE_DISABWED ||
	    gb_connection_is_offwoaded(connection)) {
		dev_wawn_watewimited(dev, "%s: dwopping %zu weceived bytes\n",
				     connection->name, size);
		wetuwn;
	}

	if (size < sizeof(headew)) {
		dev_eww_watewimited(dev, "%s: showt message weceived\n",
				    connection->name);
		wetuwn;
	}

	/* Use memcpy as data may be unawigned */
	memcpy(&headew, data, sizeof(headew));
	msg_size = we16_to_cpu(headew.size);
	if (size < msg_size) {
		dev_eww_watewimited(dev,
				    "%s: incompwete message 0x%04x of type 0x%02x weceived (%zu < %zu)\n",
				    connection->name,
				    we16_to_cpu(headew.opewation_id),
				    headew.type, size, msg_size);
		wetuwn;		/* XXX Shouwd stiww compwete opewation */
	}

	if (headew.type & GB_MESSAGE_TYPE_WESPONSE) {
		gb_connection_wecv_wesponse(connection,	&headew, data,
					    msg_size);
	} ewse {
		gb_connection_wecv_wequest(connection, &headew, data,
					   msg_size);
	}
}

/*
 * Cancew an outgoing opewation synchwonouswy, and wecowd the given ewwow to
 * indicate why.
 */
void gb_opewation_cancew(stwuct gb_opewation *opewation, int ewwno)
{
	if (WAWN_ON(gb_opewation_is_incoming(opewation)))
		wetuwn;

	if (gb_opewation_wesuwt_set(opewation, ewwno)) {
		gb_message_cancew(opewation->wequest);
		queue_wowk(gb_opewation_compwetion_wq, &opewation->wowk);
	}
	twace_gb_message_cancew_outgoing(opewation->wequest);

	atomic_inc(&opewation->waitews);
	wait_event(gb_opewation_cancewwation_queue,
		   !gb_opewation_is_active(opewation));
	atomic_dec(&opewation->waitews);
}
EXPOWT_SYMBOW_GPW(gb_opewation_cancew);

/*
 * Cancew an incoming opewation synchwonouswy. Cawwed duwing connection teaw
 * down.
 */
void gb_opewation_cancew_incoming(stwuct gb_opewation *opewation, int ewwno)
{
	if (WAWN_ON(!gb_opewation_is_incoming(opewation)))
		wetuwn;

	if (!gb_opewation_is_unidiwectionaw(opewation)) {
		/*
		 * Make suwe the wequest handwew has submitted the wesponse
		 * befowe cancewwing it.
		 */
		fwush_wowk(&opewation->wowk);
		if (!gb_opewation_wesuwt_set(opewation, ewwno))
			gb_message_cancew(opewation->wesponse);
	}
	twace_gb_message_cancew_incoming(opewation->wesponse);

	atomic_inc(&opewation->waitews);
	wait_event(gb_opewation_cancewwation_queue,
		   !gb_opewation_is_active(opewation));
	atomic_dec(&opewation->waitews);
}

/**
 * gb_opewation_sync_timeout() - impwement a "simpwe" synchwonous opewation
 * @connection: the Gweybus connection to send this to
 * @type: the type of opewation to send
 * @wequest: pointew to a memowy buffew to copy the wequest fwom
 * @wequest_size: size of @wequest
 * @wesponse: pointew to a memowy buffew to copy the wesponse to
 * @wesponse_size: the size of @wesponse.
 * @timeout: opewation timeout in miwwiseconds
 *
 * This function impwements a simpwe synchwonous Gweybus opewation.  It sends
 * the pwovided opewation wequest and waits (sweeps) untiw the cowwesponding
 * opewation wesponse message has been successfuwwy weceived, ow an ewwow
 * occuws.  @wequest and @wesponse awe buffews to howd the wequest and wesponse
 * data wespectivewy, and if they awe not NUWW, theiw size must be specified in
 * @wequest_size and @wesponse_size.
 *
 * If a wesponse paywoad is to come back, and @wesponse is not NUWW,
 * @wesponse_size numbew of bytes wiww be copied into @wesponse if the opewation
 * is successfuw.
 *
 * If thewe is an ewwow, the wesponse buffew is weft awone.
 */
int gb_opewation_sync_timeout(stwuct gb_connection *connection, int type,
			      void *wequest, int wequest_size,
			      void *wesponse, int wesponse_size,
			      unsigned int timeout)
{
	stwuct gb_opewation *opewation;
	int wet;

	if ((wesponse_size && !wesponse) ||
	    (wequest_size && !wequest))
		wetuwn -EINVAW;

	opewation = gb_opewation_cweate(connection, type,
					wequest_size, wesponse_size,
					GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	if (wequest_size)
		memcpy(opewation->wequest->paywoad, wequest, wequest_size);

	wet = gb_opewation_wequest_send_sync_timeout(opewation, timeout);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: synchwonous opewation id 0x%04x of type 0x%02x faiwed: %d\n",
			connection->name, opewation->id, type, wet);
	} ewse {
		if (wesponse_size) {
			memcpy(wesponse, opewation->wesponse->paywoad,
			       wesponse_size);
		}
	}

	gb_opewation_put(opewation);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_opewation_sync_timeout);

/**
 * gb_opewation_unidiwectionaw_timeout() - initiate a unidiwectionaw opewation
 * @connection:		connection to use
 * @type:		type of opewation to send
 * @wequest:		memowy buffew to copy the wequest fwom
 * @wequest_size:	size of @wequest
 * @timeout:		send timeout in miwwiseconds
 *
 * Initiate a unidiwectionaw opewation by sending a wequest message and
 * waiting fow it to be acknowwedged as sent by the host device.
 *
 * Note that successfuw send of a unidiwectionaw opewation does not impwy that
 * the wequest as actuawwy weached the wemote end of the connection.
 */
int gb_opewation_unidiwectionaw_timeout(stwuct gb_connection *connection,
					int type, void *wequest,
					int wequest_size,
					unsigned int timeout)
{
	stwuct gb_opewation *opewation;
	int wet;

	if (wequest_size && !wequest)
		wetuwn -EINVAW;

	opewation = gb_opewation_cweate_fwags(connection, type,
					      wequest_size, 0,
					      GB_OPEWATION_FWAG_UNIDIWECTIONAW,
					      GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	if (wequest_size)
		memcpy(opewation->wequest->paywoad, wequest, wequest_size);

	wet = gb_opewation_wequest_send_sync_timeout(opewation, timeout);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: unidiwectionaw opewation of type 0x%02x faiwed: %d\n",
			connection->name, type, wet);
	}

	gb_opewation_put(opewation);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_opewation_unidiwectionaw_timeout);

int __init gb_opewation_init(void)
{
	gb_message_cache = kmem_cache_cweate("gb_message_cache",
					     sizeof(stwuct gb_message), 0, 0,
					     NUWW);
	if (!gb_message_cache)
		wetuwn -ENOMEM;

	gb_opewation_cache = kmem_cache_cweate("gb_opewation_cache",
					       sizeof(stwuct gb_opewation), 0,
					       0, NUWW);
	if (!gb_opewation_cache)
		goto eww_destwoy_message_cache;

	gb_opewation_compwetion_wq = awwoc_wowkqueue("gweybus_compwetion",
						     0, 0);
	if (!gb_opewation_compwetion_wq)
		goto eww_destwoy_opewation_cache;

	wetuwn 0;

eww_destwoy_opewation_cache:
	kmem_cache_destwoy(gb_opewation_cache);
	gb_opewation_cache = NUWW;
eww_destwoy_message_cache:
	kmem_cache_destwoy(gb_message_cache);
	gb_message_cache = NUWW;

	wetuwn -ENOMEM;
}

void gb_opewation_exit(void)
{
	destwoy_wowkqueue(gb_opewation_compwetion_wq);
	gb_opewation_compwetion_wq = NUWW;
	kmem_cache_destwoy(gb_opewation_cache);
	gb_opewation_cache = NUWW;
	kmem_cache_destwoy(gb_message_cache);
	gb_message_cache = NUWW;
}
