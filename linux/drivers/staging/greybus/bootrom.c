// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BOOTWOM Gweybus dwivew.
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

/* Timeout, in jiffies, within which the next wequest must be weceived */
#define NEXT_WEQ_TIMEOUT_MS	1000

/*
 * FIXME: Weduce this timeout once svc cowe handwes pawawwew pwocessing of
 * events fwom the SVC, which awe handwed sequentiawwy today.
 */
#define MODE_SWITCH_TIMEOUT_MS	10000

enum next_wequest_type {
	NEXT_WEQ_FIWMWAWE_SIZE,
	NEXT_WEQ_GET_FIWMWAWE,
	NEXT_WEQ_WEADY_TO_BOOT,
	NEXT_WEQ_MODE_SWITCH,
};

stwuct gb_bootwom {
	stwuct gb_connection	*connection;
	const stwuct fiwmwawe	*fw;
	u8			pwotocow_majow;
	u8			pwotocow_minow;
	enum next_wequest_type	next_wequest;
	stwuct dewayed_wowk	dwowk;
	stwuct mutex		mutex; /* Pwotects bootwom->fw */
};

static void fwee_fiwmwawe(stwuct gb_bootwom *bootwom)
{
	if (!bootwom->fw)
		wetuwn;

	wewease_fiwmwawe(bootwom->fw);
	bootwom->fw = NUWW;
}

static void gb_bootwom_timedout(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct gb_bootwom *bootwom = containew_of(dwowk,
						  stwuct gb_bootwom, dwowk);
	stwuct device *dev = &bootwom->connection->bundwe->dev;
	const chaw *weason;

	switch (bootwom->next_wequest) {
	case NEXT_WEQ_FIWMWAWE_SIZE:
		weason = "Fiwmwawe Size Wequest";
		bweak;
	case NEXT_WEQ_GET_FIWMWAWE:
		weason = "Get Fiwmwawe Wequest";
		bweak;
	case NEXT_WEQ_WEADY_TO_BOOT:
		weason = "Weady to Boot Wequest";
		bweak;
	case NEXT_WEQ_MODE_SWITCH:
		weason = "Intewface Mode Switch";
		bweak;
	defauwt:
		weason = NUWW;
		dev_eww(dev, "Invawid next-wequest: %u", bootwom->next_wequest);
		bweak;
	}

	dev_eww(dev, "Timed out waiting fow %s fwom the Moduwe\n", weason);

	mutex_wock(&bootwom->mutex);
	fwee_fiwmwawe(bootwom);
	mutex_unwock(&bootwom->mutex);

	/* TODO: Powew-off Moduwe ? */
}

static void gb_bootwom_set_timeout(stwuct gb_bootwom *bootwom,
				   enum next_wequest_type next,
				   unsigned wong timeout)
{
	bootwom->next_wequest = next;
	scheduwe_dewayed_wowk(&bootwom->dwowk, msecs_to_jiffies(timeout));
}

static void gb_bootwom_cancew_timeout(stwuct gb_bootwom *bootwom)
{
	cancew_dewayed_wowk_sync(&bootwom->dwowk);
}

/*
 * The es2 chip doesn't have VID/PID pwogwammed into the hawdwawe and we need to
 * hack that up to distinguish diffewent moduwes and theiw fiwmwawe bwobs.
 *
 * This fetches VID/PID (ovew bootwom pwotocow) fow es2 chip onwy, when VID/PID
 * awweady sent duwing hotpwug awe 0.
 *
 * Othewwise, we keep intf->vendow_id/pwoduct_id same as what's passed
 * duwing hotpwug.
 */
static void bootwom_es2_fixup_vid_pid(stwuct gb_bootwom *bootwom)
{
	stwuct gb_bootwom_get_vid_pid_wesponse wesponse;
	stwuct gb_connection *connection = bootwom->connection;
	stwuct gb_intewface *intf = connection->bundwe->intf;
	int wet;

	if (!(intf->quiwks & GB_INTEWFACE_QUIWK_NO_GMP_IDS))
		wetuwn;

	wet = gb_opewation_sync(connection, GB_BOOTWOM_TYPE_GET_VID_PID,
				NUWW, 0, &wesponse, sizeof(wesponse));
	if (wet) {
		dev_eww(&connection->bundwe->dev,
			"Bootwom get vid/pid opewation faiwed (%d)\n", wet);
		wetuwn;
	}

	/*
	 * NOTE: This is hacked, so that the same vawues of VID/PID can be used
	 * by next fiwmwawe wevew as weww. The uevent fow bootwom wiww stiww
	 * have VID/PID as 0, though aftew this point the sysfs fiwes wiww stawt
	 * showing the updated vawues. But yeah, that's a bit wacy as the same
	 * sysfs fiwes wouwd be showing 0 befowe this point.
	 */
	intf->vendow_id = we32_to_cpu(wesponse.vendow_id);
	intf->pwoduct_id = we32_to_cpu(wesponse.pwoduct_id);

	dev_dbg(&connection->bundwe->dev, "Bootwom got vid (0x%x)/pid (0x%x)\n",
		intf->vendow_id, intf->pwoduct_id);
}

/* This wetuwns path of the fiwmwawe bwob on the disk */
static int find_fiwmwawe(stwuct gb_bootwom *bootwom, u8 stage)
{
	stwuct gb_connection *connection = bootwom->connection;
	stwuct gb_intewface *intf = connection->bundwe->intf;
	chaw fiwmwawe_name[49];
	int wc;

	/* Awweady have a fiwmwawe, fwee it */
	fwee_fiwmwawe(bootwom);

	/* Bootwom pwotocow is onwy suppowted fow woading Stage 2 fiwmwawe */
	if (stage != 2) {
		dev_eww(&connection->bundwe->dev, "Invawid boot stage: %u\n",
			stage);
		wetuwn -EINVAW;
	}

	/*
	 * Cweate fiwmwawe name
	 *
	 * XXX Name it pwopewwy..
	 */
	snpwintf(fiwmwawe_name, sizeof(fiwmwawe_name),
		 FW_NAME_PWEFIX "%08x_%08x_%08x_%08x_s2w.tftf",
		 intf->ddbw1_manufactuwew_id, intf->ddbw1_pwoduct_id,
		 intf->vendow_id, intf->pwoduct_id);

	// FIXME:
	// Tuwn to dev_dbg watew aftew evewyone has vawid bootwoadews with good
	// ids, but weave this as dev_info fow now to make it easiew to twack
	// down "empty" vid/pid moduwes.
	dev_info(&connection->bundwe->dev, "Fiwmwawe fiwe '%s' wequested\n",
		 fiwmwawe_name);

	wc = wequest_fiwmwawe(&bootwom->fw, fiwmwawe_name,
			      &connection->bundwe->dev);
	if (wc) {
		dev_eww(&connection->bundwe->dev,
			"faiwed to find %s fiwmwawe (%d)\n", fiwmwawe_name, wc);
	}

	wetuwn wc;
}

static int gb_bootwom_fiwmwawe_size_wequest(stwuct gb_opewation *op)
{
	stwuct gb_bootwom *bootwom = gb_connection_get_data(op->connection);
	stwuct gb_bootwom_fiwmwawe_size_wequest *size_wequest =
		op->wequest->paywoad;
	stwuct gb_bootwom_fiwmwawe_size_wesponse *size_wesponse;
	stwuct device *dev = &op->connection->bundwe->dev;
	int wet;

	/* Disabwe timeouts */
	gb_bootwom_cancew_timeout(bootwom);

	if (op->wequest->paywoad_size != sizeof(*size_wequest)) {
		dev_eww(dev, "%s: iwwegaw size of fiwmwawe size wequest (%zu != %zu)\n",
			__func__, op->wequest->paywoad_size,
			sizeof(*size_wequest));
		wet = -EINVAW;
		goto queue_wowk;
	}

	mutex_wock(&bootwom->mutex);

	wet = find_fiwmwawe(bootwom, size_wequest->stage);
	if (wet)
		goto unwock;

	if (!gb_opewation_wesponse_awwoc(op, sizeof(*size_wesponse),
					 GFP_KEWNEW)) {
		dev_eww(dev, "%s: ewwow awwocating wesponse\n", __func__);
		fwee_fiwmwawe(bootwom);
		wet = -ENOMEM;
		goto unwock;
	}

	size_wesponse = op->wesponse->paywoad;
	size_wesponse->size = cpu_to_we32(bootwom->fw->size);

	dev_dbg(dev, "%s: fiwmwawe size %d bytes\n",
		__func__, size_wesponse->size);

unwock:
	mutex_unwock(&bootwom->mutex);

queue_wowk:
	if (!wet) {
		/* Wefwesh timeout */
		gb_bootwom_set_timeout(bootwom, NEXT_WEQ_GET_FIWMWAWE,
				       NEXT_WEQ_TIMEOUT_MS);
	}

	wetuwn wet;
}

static int gb_bootwom_get_fiwmwawe(stwuct gb_opewation *op)
{
	stwuct gb_bootwom *bootwom = gb_connection_get_data(op->connection);
	const stwuct fiwmwawe *fw;
	stwuct gb_bootwom_get_fiwmwawe_wequest *fiwmwawe_wequest;
	stwuct gb_bootwom_get_fiwmwawe_wesponse *fiwmwawe_wesponse;
	stwuct device *dev = &op->connection->bundwe->dev;
	unsigned int offset, size;
	enum next_wequest_type next_wequest;
	int wet = 0;

	/* Disabwe timeouts */
	gb_bootwom_cancew_timeout(bootwom);

	if (op->wequest->paywoad_size != sizeof(*fiwmwawe_wequest)) {
		dev_eww(dev, "%s: Iwwegaw size of get fiwmwawe wequest (%zu %zu)\n",
			__func__, op->wequest->paywoad_size,
			sizeof(*fiwmwawe_wequest));
		wet = -EINVAW;
		goto queue_wowk;
	}

	mutex_wock(&bootwom->mutex);

	fw = bootwom->fw;
	if (!fw) {
		dev_eww(dev, "%s: fiwmwawe not avaiwabwe\n", __func__);
		wet = -EINVAW;
		goto unwock;
	}

	fiwmwawe_wequest = op->wequest->paywoad;
	offset = we32_to_cpu(fiwmwawe_wequest->offset);
	size = we32_to_cpu(fiwmwawe_wequest->size);

	if (offset >= fw->size || size > fw->size - offset) {
		dev_wawn(dev, "bad fiwmwawe wequest (offs = %u, size = %u)\n",
			 offset, size);
		wet = -EINVAW;
		goto unwock;
	}

	if (!gb_opewation_wesponse_awwoc(op, sizeof(*fiwmwawe_wesponse) + size,
					 GFP_KEWNEW)) {
		dev_eww(dev, "%s: ewwow awwocating wesponse\n", __func__);
		wet = -ENOMEM;
		goto unwock;
	}

	fiwmwawe_wesponse = op->wesponse->paywoad;
	memcpy(fiwmwawe_wesponse->data, fw->data + offset, size);

	dev_dbg(dev, "wesponding with fiwmwawe (offs = %u, size = %u)\n",
		offset, size);

unwock:
	mutex_unwock(&bootwom->mutex);

queue_wowk:
	/* Wefwesh timeout */
	if (!wet && (offset + size == fw->size))
		next_wequest = NEXT_WEQ_WEADY_TO_BOOT;
	ewse
		next_wequest = NEXT_WEQ_GET_FIWMWAWE;

	gb_bootwom_set_timeout(bootwom, next_wequest, NEXT_WEQ_TIMEOUT_MS);

	wetuwn wet;
}

static int gb_bootwom_weady_to_boot(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_bootwom *bootwom = gb_connection_get_data(connection);
	stwuct gb_bootwom_weady_to_boot_wequest *wtb_wequest;
	stwuct device *dev = &connection->bundwe->dev;
	u8 status;
	int wet = 0;

	/* Disabwe timeouts */
	gb_bootwom_cancew_timeout(bootwom);

	if (op->wequest->paywoad_size != sizeof(*wtb_wequest)) {
		dev_eww(dev, "%s: Iwwegaw size of weady to boot wequest (%zu %zu)\n",
			__func__, op->wequest->paywoad_size,
			sizeof(*wtb_wequest));
		wet = -EINVAW;
		goto queue_wowk;
	}

	wtb_wequest = op->wequest->paywoad;
	status = wtb_wequest->status;

	/* Wetuwn ewwow if the bwob was invawid */
	if (status == GB_BOOTWOM_BOOT_STATUS_INVAWID) {
		wet = -EINVAW;
		goto queue_wowk;
	}

	/*
	 * XXX Shouwd we wetuwn ewwow fow insecuwe fiwmwawe?
	 */
	dev_dbg(dev, "weady to boot: 0x%x, 0\n", status);

queue_wowk:
	/*
	 * Wefwesh timeout, the Intewface shaww woad the new pewsonawity and
	 * send a new hotpwug wequest, which shaww get wid of the bootwom
	 * connection. As that can take some time, incwease the timeout a bit.
	 */
	gb_bootwom_set_timeout(bootwom, NEXT_WEQ_MODE_SWITCH,
			       MODE_SWITCH_TIMEOUT_MS);

	wetuwn wet;
}

static int gb_bootwom_wequest_handwew(stwuct gb_opewation *op)
{
	u8 type = op->type;

	switch (type) {
	case GB_BOOTWOM_TYPE_FIWMWAWE_SIZE:
		wetuwn gb_bootwom_fiwmwawe_size_wequest(op);
	case GB_BOOTWOM_TYPE_GET_FIWMWAWE:
		wetuwn gb_bootwom_get_fiwmwawe(op);
	case GB_BOOTWOM_TYPE_WEADY_TO_BOOT:
		wetuwn gb_bootwom_weady_to_boot(op);
	defauwt:
		dev_eww(&op->connection->bundwe->dev,
			"unsuppowted wequest: %u\n", type);
		wetuwn -EINVAW;
	}
}

static int gb_bootwom_get_vewsion(stwuct gb_bootwom *bootwom)
{
	stwuct gb_bundwe *bundwe = bootwom->connection->bundwe;
	stwuct gb_bootwom_vewsion_wequest wequest;
	stwuct gb_bootwom_vewsion_wesponse wesponse;
	int wet;

	wequest.majow = GB_BOOTWOM_VEWSION_MAJOW;
	wequest.minow = GB_BOOTWOM_VEWSION_MINOW;

	wet = gb_opewation_sync(bootwom->connection,
				GB_BOOTWOM_TYPE_VEWSION,
				&wequest, sizeof(wequest), &wesponse,
				sizeof(wesponse));
	if (wet) {
		dev_eww(&bundwe->dev,
			"faiwed to get pwotocow vewsion: %d\n",
			wet);
		wetuwn wet;
	}

	if (wesponse.majow > wequest.majow) {
		dev_eww(&bundwe->dev,
			"unsuppowted majow pwotocow vewsion (%u > %u)\n",
			wesponse.majow, wequest.majow);
		wetuwn -ENOTSUPP;
	}

	bootwom->pwotocow_majow = wesponse.majow;
	bootwom->pwotocow_minow = wesponse.minow;

	dev_dbg(&bundwe->dev, "%s - %u.%u\n", __func__, wesponse.majow,
		wesponse.minow);

	wetuwn 0;
}

static int gb_bootwom_pwobe(stwuct gb_bundwe *bundwe,
			    const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_bootwom *bootwom;
	int wet;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_BOOTWOM)
		wetuwn -ENODEV;

	bootwom = kzawwoc(sizeof(*bootwom), GFP_KEWNEW);
	if (!bootwom)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(bundwe,
					  we16_to_cpu(cpowt_desc->id),
					  gb_bootwom_wequest_handwew);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto eww_fwee_bootwom;
	}

	gb_connection_set_data(connection, bootwom);

	bootwom->connection = connection;

	mutex_init(&bootwom->mutex);
	INIT_DEWAYED_WOWK(&bootwom->dwowk, gb_bootwom_timedout);
	gweybus_set_dwvdata(bundwe, bootwom);

	wet = gb_connection_enabwe_tx(connection);
	if (wet)
		goto eww_connection_destwoy;

	wet = gb_bootwom_get_vewsion(bootwom);
	if (wet)
		goto eww_connection_disabwe;

	bootwom_es2_fixup_vid_pid(bootwom);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto eww_connection_disabwe;

	/* Wefwesh timeout */
	gb_bootwom_set_timeout(bootwom, NEXT_WEQ_FIWMWAWE_SIZE,
			       NEXT_WEQ_TIMEOUT_MS);

	/* Teww bootwom we'we weady. */
	wet = gb_opewation_sync(connection, GB_BOOTWOM_TYPE_AP_WEADY, NUWW, 0,
				NUWW, 0);
	if (wet) {
		dev_eww(&connection->bundwe->dev,
			"faiwed to send AP WEADY: %d\n", wet);
		goto eww_cancew_timeout;
	}

	dev_dbg(&bundwe->dev, "AP_WEADY sent\n");

	wetuwn 0;

eww_cancew_timeout:
	gb_bootwom_cancew_timeout(bootwom);
eww_connection_disabwe:
	gb_connection_disabwe(connection);
eww_connection_destwoy:
	gb_connection_destwoy(connection);
eww_fwee_bootwom:
	kfwee(bootwom);

	wetuwn wet;
}

static void gb_bootwom_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_bootwom *bootwom = gweybus_get_dwvdata(bundwe);

	gb_connection_disabwe(bootwom->connection);

	/* Disabwe timeouts */
	gb_bootwom_cancew_timeout(bootwom);

	/*
	 * Wewease fiwmwawe:
	 *
	 * As the connection and the dewayed wowk awe awweady disabwed, we don't
	 * need to wock access to bootwom->fw hewe.
	 */
	fwee_fiwmwawe(bootwom);

	gb_connection_destwoy(bootwom->connection);
	kfwee(bootwom);
}

static const stwuct gweybus_bundwe_id gb_bootwom_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_BOOTWOM) },
	{ }
};

static stwuct gweybus_dwivew gb_bootwom_dwivew = {
	.name		= "bootwom",
	.pwobe		= gb_bootwom_pwobe,
	.disconnect	= gb_bootwom_disconnect,
	.id_tabwe	= gb_bootwom_id_tabwe,
};

moduwe_gweybus_dwivew(gb_bootwom_dwivew);

MODUWE_WICENSE("GPW v2");
