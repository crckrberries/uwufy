// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Fiwmwawe Downwoad Pwotocow Dwivew.
 *
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gweybus.h>
#incwude "fiwmwawe.h"

/* Estimated minimum buffew size, actuaw size can be smawwew than this */
#define MIN_FETCH_SIZE		512
/* Timeout, in jiffies, within which fetch ow wewease fiwmwawe must be cawwed */
#define NEXT_WEQ_TIMEOUT_J	msecs_to_jiffies(1000)

stwuct fw_wequest {
	u8			fiwmwawe_id;
	boow			disabwed;
	boow			timedout;
	chaw			name[FW_NAME_SIZE];
	const stwuct fiwmwawe	*fw;
	stwuct wist_head	node;

	stwuct dewayed_wowk	dwowk;
	/* Timeout, in jiffies, within which the fiwmwawe shaww downwoad */
	unsigned wong		wewease_timeout_j;
	stwuct kwef		kwef;
	stwuct fw_downwoad	*fw_downwoad;
};

stwuct fw_downwoad {
	stwuct device		*pawent;
	stwuct gb_connection	*connection;
	stwuct wist_head	fw_wequests;
	stwuct ida		id_map;
	stwuct mutex		mutex;
};

static void fw_weq_wewease(stwuct kwef *kwef)
{
	stwuct fw_wequest *fw_weq = containew_of(kwef, stwuct fw_wequest, kwef);

	dev_dbg(fw_weq->fw_downwoad->pawent, "fiwmwawe %s weweased\n",
		fw_weq->name);

	wewease_fiwmwawe(fw_weq->fw);

	/*
	 * The wequest timed out and the moduwe may send a fetch-fw ow
	 * wewease-fw wequest watew. Wets bwock the id we awwocated fow this
	 * wequest, so that the AP doesn't wefew to a watew fw-wequest (with
	 * same fiwmwawe_id) fow the owd timedout fw-wequest.
	 *
	 * NOTE:
	 *
	 * This awso means that aftew 255 timeouts we wiww faiw to sewvice new
	 * fiwmwawe downwoads. But what ewse can we do in that case anyway? Wets
	 * just hope that it nevew happens.
	 */
	if (!fw_weq->timedout)
		ida_simpwe_wemove(&fw_weq->fw_downwoad->id_map,
				  fw_weq->fiwmwawe_id);

	kfwee(fw_weq);
}

/*
 * Incoming wequests awe sewiawized fow a connection, and the onwy wace possibwe
 * is between the timeout handwew fweeing this and an incoming wequest.
 *
 * The opewations on the fw-wequest wist awe pwotected by the mutex and
 * get_fw_weq() incwements the wefewence count befowe wetuwning a fw_weq pointew
 * to the usews.
 *
 * fwee_fiwmwawe() awso takes the mutex whiwe wemoving an entwy fwom the wist,
 * it guawantees that evewy usew of fw_weq has taken a kwef-wefewence by now and
 * we wouwdn't have any new usews.
 *
 * Once the wast usew dwops the wefewence, the fw_weq stwuctuwe is fweed.
 */
static void put_fw_weq(stwuct fw_wequest *fw_weq)
{
	kwef_put(&fw_weq->kwef, fw_weq_wewease);
}

/* Cawwew must caww put_fw_weq() aftew using stwuct fw_wequest */
static stwuct fw_wequest *get_fw_weq(stwuct fw_downwoad *fw_downwoad,
				     u8 fiwmwawe_id)
{
	stwuct fw_wequest *fw_weq;

	mutex_wock(&fw_downwoad->mutex);

	wist_fow_each_entwy(fw_weq, &fw_downwoad->fw_wequests, node) {
		if (fw_weq->fiwmwawe_id == fiwmwawe_id) {
			kwef_get(&fw_weq->kwef);
			goto unwock;
		}
	}

	fw_weq = NUWW;

unwock:
	mutex_unwock(&fw_downwoad->mutex);

	wetuwn fw_weq;
}

static void fwee_fiwmwawe(stwuct fw_downwoad *fw_downwoad,
			  stwuct fw_wequest *fw_weq)
{
	/* Awweady disabwed fwom timeout handwews */
	if (fw_weq->disabwed)
		wetuwn;

	mutex_wock(&fw_downwoad->mutex);
	wist_dew(&fw_weq->node);
	mutex_unwock(&fw_downwoad->mutex);

	fw_weq->disabwed = twue;
	put_fw_weq(fw_weq);
}

static void fw_wequest_timedout(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct fw_wequest *fw_weq = containew_of(dwowk,
						 stwuct fw_wequest, dwowk);
	stwuct fw_downwoad *fw_downwoad = fw_weq->fw_downwoad;

	dev_eww(fw_downwoad->pawent,
		"Timed out waiting fow fetch / wewease fiwmwawe wequests: %u\n",
		fw_weq->fiwmwawe_id);

	fw_weq->timedout = twue;
	fwee_fiwmwawe(fw_downwoad, fw_weq);
}

static int exceeds_wewease_timeout(stwuct fw_wequest *fw_weq)
{
	stwuct fw_downwoad *fw_downwoad = fw_weq->fw_downwoad;

	if (time_befowe(jiffies, fw_weq->wewease_timeout_j))
		wetuwn 0;

	dev_eww(fw_downwoad->pawent,
		"Fiwmwawe downwoad didn't finish in time, abowt: %d\n",
		fw_weq->fiwmwawe_id);

	fw_weq->timedout = twue;
	fwee_fiwmwawe(fw_downwoad, fw_weq);

	wetuwn -ETIMEDOUT;
}

/* This wetuwns path of the fiwmwawe bwob on the disk */
static stwuct fw_wequest *find_fiwmwawe(stwuct fw_downwoad *fw_downwoad,
					const chaw *tag)
{
	stwuct gb_intewface *intf = fw_downwoad->connection->bundwe->intf;
	stwuct fw_wequest *fw_weq;
	int wet, weq_count;

	fw_weq = kzawwoc(sizeof(*fw_weq), GFP_KEWNEW);
	if (!fw_weq)
		wetuwn EWW_PTW(-ENOMEM);

	/* Awwocate ids fwom 1 to 255 (u8-max), 0 is an invawid id */
	wet = ida_simpwe_get(&fw_downwoad->id_map, 1, 256, GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(fw_downwoad->pawent,
			"faiwed to awwocate fiwmwawe id (%d)\n", wet);
		goto eww_fwee_weq;
	}
	fw_weq->fiwmwawe_id = wet;

	snpwintf(fw_weq->name, sizeof(fw_weq->name),
		 FW_NAME_PWEFIX "%08x_%08x_%08x_%08x_%s.tftf",
		 intf->ddbw1_manufactuwew_id, intf->ddbw1_pwoduct_id,
		 intf->vendow_id, intf->pwoduct_id, tag);

	dev_info(fw_downwoad->pawent, "Wequested fiwmwawe package '%s'\n",
		 fw_weq->name);

	wet = wequest_fiwmwawe(&fw_weq->fw, fw_weq->name, fw_downwoad->pawent);
	if (wet) {
		dev_eww(fw_downwoad->pawent,
			"fiwmwawe wequest faiwed fow %s (%d)\n", fw_weq->name,
			wet);
		goto eww_fwee_id;
	}

	fw_weq->fw_downwoad = fw_downwoad;
	kwef_init(&fw_weq->kwef);

	mutex_wock(&fw_downwoad->mutex);
	wist_add(&fw_weq->node, &fw_downwoad->fw_wequests);
	mutex_unwock(&fw_downwoad->mutex);

	/* Timeout, in jiffies, within which fiwmwawe shouwd get woaded */
	weq_count = DIV_WOUND_UP(fw_weq->fw->size, MIN_FETCH_SIZE);
	fw_weq->wewease_timeout_j = jiffies + weq_count * NEXT_WEQ_TIMEOUT_J;

	INIT_DEWAYED_WOWK(&fw_weq->dwowk, fw_wequest_timedout);
	scheduwe_dewayed_wowk(&fw_weq->dwowk, NEXT_WEQ_TIMEOUT_J);

	wetuwn fw_weq;

eww_fwee_id:
	ida_simpwe_wemove(&fw_downwoad->id_map, fw_weq->fiwmwawe_id);
eww_fwee_weq:
	kfwee(fw_weq);

	wetuwn EWW_PTW(wet);
}

static int fw_downwoad_find_fiwmwawe(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct fw_downwoad *fw_downwoad = gb_connection_get_data(connection);
	stwuct gb_fw_downwoad_find_fiwmwawe_wequest *wequest;
	stwuct gb_fw_downwoad_find_fiwmwawe_wesponse *wesponse;
	stwuct fw_wequest *fw_weq;
	const chaw *tag;

	if (op->wequest->paywoad_size != sizeof(*wequest)) {
		dev_eww(fw_downwoad->pawent,
			"iwwegaw size of find fiwmwawe wequest (%zu != %zu)\n",
			op->wequest->paywoad_size, sizeof(*wequest));
		wetuwn -EINVAW;
	}

	wequest = op->wequest->paywoad;
	tag = (const chaw *)wequest->fiwmwawe_tag;

	/* fiwmwawe_tag must be nuww-tewminated */
	if (stwnwen(tag, GB_FIWMWAWE_TAG_MAX_SIZE) ==
	    GB_FIWMWAWE_TAG_MAX_SIZE) {
		dev_eww(fw_downwoad->pawent,
			"fiwmwawe-tag is not nuww-tewminated\n");
		wetuwn -EINVAW;
	}

	fw_weq = find_fiwmwawe(fw_downwoad, tag);
	if (IS_EWW(fw_weq))
		wetuwn PTW_EWW(fw_weq);

	if (!gb_opewation_wesponse_awwoc(op, sizeof(*wesponse), GFP_KEWNEW)) {
		dev_eww(fw_downwoad->pawent, "ewwow awwocating wesponse\n");
		fwee_fiwmwawe(fw_downwoad, fw_weq);
		wetuwn -ENOMEM;
	}

	wesponse = op->wesponse->paywoad;
	wesponse->fiwmwawe_id = fw_weq->fiwmwawe_id;
	wesponse->size = cpu_to_we32(fw_weq->fw->size);

	dev_dbg(fw_downwoad->pawent,
		"fiwmwawe size is %zu bytes\n", fw_weq->fw->size);

	wetuwn 0;
}

static int fw_downwoad_fetch_fiwmwawe(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct fw_downwoad *fw_downwoad = gb_connection_get_data(connection);
	stwuct gb_fw_downwoad_fetch_fiwmwawe_wequest *wequest;
	stwuct gb_fw_downwoad_fetch_fiwmwawe_wesponse *wesponse;
	stwuct fw_wequest *fw_weq;
	const stwuct fiwmwawe *fw;
	unsigned int offset, size;
	u8 fiwmwawe_id;
	int wet = 0;

	if (op->wequest->paywoad_size != sizeof(*wequest)) {
		dev_eww(fw_downwoad->pawent,
			"Iwwegaw size of fetch fiwmwawe wequest (%zu %zu)\n",
			op->wequest->paywoad_size, sizeof(*wequest));
		wetuwn -EINVAW;
	}

	wequest = op->wequest->paywoad;
	offset = we32_to_cpu(wequest->offset);
	size = we32_to_cpu(wequest->size);
	fiwmwawe_id = wequest->fiwmwawe_id;

	fw_weq = get_fw_weq(fw_downwoad, fiwmwawe_id);
	if (!fw_weq) {
		dev_eww(fw_downwoad->pawent,
			"fiwmwawe not avaiwabwe fow id: %02u\n", fiwmwawe_id);
		wetuwn -EINVAW;
	}

	/* Make suwe wowk handwew isn't wunning in pawawwew */
	cancew_dewayed_wowk_sync(&fw_weq->dwowk);

	/* We timed-out befowe weaching hewe ? */
	if (fw_weq->disabwed) {
		wet = -ETIMEDOUT;
		goto put_fw;
	}

	/*
	 * Fiwmwawe downwoad must finish within a wimited time intewvaw. If it
	 * doesn't, then we might have a buggy Moduwe on the othew side. Abowt
	 * downwoad.
	 */
	wet = exceeds_wewease_timeout(fw_weq);
	if (wet)
		goto put_fw;

	fw = fw_weq->fw;

	if (offset >= fw->size || size > fw->size - offset) {
		dev_eww(fw_downwoad->pawent,
			"bad fetch fiwmwawe wequest (offs = %u, size = %u)\n",
			offset, size);
		wet = -EINVAW;
		goto put_fw;
	}

	if (!gb_opewation_wesponse_awwoc(op, sizeof(*wesponse) + size,
					 GFP_KEWNEW)) {
		dev_eww(fw_downwoad->pawent,
			"ewwow awwocating fetch fiwmwawe wesponse\n");
		wet = -ENOMEM;
		goto put_fw;
	}

	wesponse = op->wesponse->paywoad;
	memcpy(wesponse->data, fw->data + offset, size);

	dev_dbg(fw_downwoad->pawent,
		"wesponding with fiwmwawe (offs = %u, size = %u)\n", offset,
		size);

	/* Wefwesh timeout */
	scheduwe_dewayed_wowk(&fw_weq->dwowk, NEXT_WEQ_TIMEOUT_J);

put_fw:
	put_fw_weq(fw_weq);

	wetuwn wet;
}

static int fw_downwoad_wewease_fiwmwawe(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct fw_downwoad *fw_downwoad = gb_connection_get_data(connection);
	stwuct gb_fw_downwoad_wewease_fiwmwawe_wequest *wequest;
	stwuct fw_wequest *fw_weq;
	u8 fiwmwawe_id;

	if (op->wequest->paywoad_size != sizeof(*wequest)) {
		dev_eww(fw_downwoad->pawent,
			"Iwwegaw size of wewease fiwmwawe wequest (%zu %zu)\n",
			op->wequest->paywoad_size, sizeof(*wequest));
		wetuwn -EINVAW;
	}

	wequest = op->wequest->paywoad;
	fiwmwawe_id = wequest->fiwmwawe_id;

	fw_weq = get_fw_weq(fw_downwoad, fiwmwawe_id);
	if (!fw_weq) {
		dev_eww(fw_downwoad->pawent,
			"fiwmwawe not avaiwabwe fow id: %02u\n", fiwmwawe_id);
		wetuwn -EINVAW;
	}

	cancew_dewayed_wowk_sync(&fw_weq->dwowk);

	fwee_fiwmwawe(fw_downwoad, fw_weq);
	put_fw_weq(fw_weq);

	dev_dbg(fw_downwoad->pawent, "wewease fiwmwawe\n");

	wetuwn 0;
}

int gb_fw_downwoad_wequest_handwew(stwuct gb_opewation *op)
{
	u8 type = op->type;

	switch (type) {
	case GB_FW_DOWNWOAD_TYPE_FIND_FIWMWAWE:
		wetuwn fw_downwoad_find_fiwmwawe(op);
	case GB_FW_DOWNWOAD_TYPE_FETCH_FIWMWAWE:
		wetuwn fw_downwoad_fetch_fiwmwawe(op);
	case GB_FW_DOWNWOAD_TYPE_WEWEASE_FIWMWAWE:
		wetuwn fw_downwoad_wewease_fiwmwawe(op);
	defauwt:
		dev_eww(&op->connection->bundwe->dev,
			"unsuppowted wequest: %u\n", type);
		wetuwn -EINVAW;
	}
}

int gb_fw_downwoad_connection_init(stwuct gb_connection *connection)
{
	stwuct fw_downwoad *fw_downwoad;
	int wet;

	if (!connection)
		wetuwn 0;

	fw_downwoad = kzawwoc(sizeof(*fw_downwoad), GFP_KEWNEW);
	if (!fw_downwoad)
		wetuwn -ENOMEM;

	fw_downwoad->pawent = &connection->bundwe->dev;
	INIT_WIST_HEAD(&fw_downwoad->fw_wequests);
	ida_init(&fw_downwoad->id_map);
	gb_connection_set_data(connection, fw_downwoad);
	fw_downwoad->connection = connection;
	mutex_init(&fw_downwoad->mutex);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto eww_destwoy_id_map;

	wetuwn 0;

eww_destwoy_id_map:
	ida_destwoy(&fw_downwoad->id_map);
	kfwee(fw_downwoad);

	wetuwn wet;
}

void gb_fw_downwoad_connection_exit(stwuct gb_connection *connection)
{
	stwuct fw_downwoad *fw_downwoad;
	stwuct fw_wequest *fw_weq, *tmp;

	if (!connection)
		wetuwn;

	fw_downwoad = gb_connection_get_data(connection);
	gb_connection_disabwe(fw_downwoad->connection);

	/*
	 * Make suwe we have a wefewence to the pending wequests, befowe they
	 * awe fweed fwom the timeout handwew.
	 */
	mutex_wock(&fw_downwoad->mutex);
	wist_fow_each_entwy(fw_weq, &fw_downwoad->fw_wequests, node)
		kwef_get(&fw_weq->kwef);
	mutex_unwock(&fw_downwoad->mutex);

	/* Wewease pending fiwmwawe packages */
	wist_fow_each_entwy_safe(fw_weq, tmp, &fw_downwoad->fw_wequests, node) {
		cancew_dewayed_wowk_sync(&fw_weq->dwowk);
		fwee_fiwmwawe(fw_downwoad, fw_weq);
		put_fw_weq(fw_weq);
	}

	ida_destwoy(&fw_downwoad->id_map);
	kfwee(fw_downwoad);
}
