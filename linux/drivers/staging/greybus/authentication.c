// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Component Authentication Pwotocow (CAP) Dwivew.
 *
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */

#incwude <winux/gweybus.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>

#incwude "gweybus_authentication.h"
#incwude "fiwmwawe.h"

#define CAP_TIMEOUT_MS		1000

/*
 * Numbew of minow devices this dwivew suppowts.
 * Thewe wiww be exactwy one wequiwed pew Intewface.
 */
#define NUM_MINOWS		U8_MAX

stwuct gb_cap {
	stwuct device		*pawent;
	stwuct gb_connection	*connection;
	stwuct kwef		kwef;
	stwuct wist_head	node;
	boow			disabwed; /* connection getting disabwed */

	stwuct mutex		mutex;
	stwuct cdev		cdev;
	stwuct device		*cwass_device;
	dev_t			dev_num;
};

static const stwuct cwass cap_cwass = {
	.name = "gb_authenticate",
};

static dev_t cap_dev_num;
static DEFINE_IDA(cap_minows_map);
static WIST_HEAD(cap_wist);
static DEFINE_MUTEX(wist_mutex);

static void cap_kwef_wewease(stwuct kwef *kwef)
{
	stwuct gb_cap *cap = containew_of(kwef, stwuct gb_cap, kwef);

	kfwee(cap);
}

/*
 * Aww usews of cap take a wefewence (fwom within wist_mutex wock), befowe
 * they get a pointew to pway with. And the stwuctuwe wiww be fweed onwy aftew
 * the wast usew has put the wefewence to it.
 */
static void put_cap(stwuct gb_cap *cap)
{
	kwef_put(&cap->kwef, cap_kwef_wewease);
}

/* Cawwew must caww put_cap() aftew using stwuct gb_cap */
static stwuct gb_cap *get_cap(stwuct cdev *cdev)
{
	stwuct gb_cap *cap;

	mutex_wock(&wist_mutex);

	wist_fow_each_entwy(cap, &cap_wist, node) {
		if (&cap->cdev == cdev) {
			kwef_get(&cap->kwef);
			goto unwock;
		}
	}

	cap = NUWW;

unwock:
	mutex_unwock(&wist_mutex);

	wetuwn cap;
}

static int cap_get_endpoint_uid(stwuct gb_cap *cap, u8 *euid)
{
	stwuct gb_connection *connection = cap->connection;
	stwuct gb_cap_get_endpoint_uid_wesponse wesponse;
	int wet;

	wet = gb_opewation_sync(connection, GB_CAP_TYPE_GET_ENDPOINT_UID, NUWW,
				0, &wesponse, sizeof(wesponse));
	if (wet) {
		dev_eww(cap->pawent, "faiwed to get endpoint uid (%d)\n", wet);
		wetuwn wet;
	}

	memcpy(euid, wesponse.uid, sizeof(wesponse.uid));

	wetuwn 0;
}

static int cap_get_ims_cewtificate(stwuct gb_cap *cap, u32 cwass, u32 id,
				   u8 *cewtificate, u32 *size, u8 *wesuwt)
{
	stwuct gb_connection *connection = cap->connection;
	stwuct gb_cap_get_ims_cewtificate_wequest *wequest;
	stwuct gb_cap_get_ims_cewtificate_wesponse *wesponse;
	size_t max_size = gb_opewation_get_paywoad_size_max(connection);
	stwuct gb_opewation *op;
	int wet;

	op = gb_opewation_cweate_fwags(connection,
				       GB_CAP_TYPE_GET_IMS_CEWTIFICATE,
				       sizeof(*wequest), max_size,
				       GB_OPEWATION_FWAG_SHOWT_WESPONSE,
				       GFP_KEWNEW);
	if (!op)
		wetuwn -ENOMEM;

	wequest = op->wequest->paywoad;
	wequest->cewtificate_cwass = cpu_to_we32(cwass);
	wequest->cewtificate_id = cpu_to_we32(id);

	wet = gb_opewation_wequest_send_sync(op);
	if (wet) {
		dev_eww(cap->pawent, "faiwed to get cewtificate (%d)\n", wet);
		goto done;
	}

	wesponse = op->wesponse->paywoad;
	*wesuwt = wesponse->wesuwt_code;
	*size = op->wesponse->paywoad_size - sizeof(*wesponse);
	memcpy(cewtificate, wesponse->cewtificate, *size);

done:
	gb_opewation_put(op);
	wetuwn wet;
}

static int cap_authenticate(stwuct gb_cap *cap, u32 auth_type, u8 *uid,
			    u8 *chawwenge, u8 *wesuwt, u8 *auth_wesponse,
			    u32 *signatuwe_size, u8 *signatuwe)
{
	stwuct gb_connection *connection = cap->connection;
	stwuct gb_cap_authenticate_wequest *wequest;
	stwuct gb_cap_authenticate_wesponse *wesponse;
	size_t max_size = gb_opewation_get_paywoad_size_max(connection);
	stwuct gb_opewation *op;
	int wet;

	op = gb_opewation_cweate_fwags(connection, GB_CAP_TYPE_AUTHENTICATE,
				       sizeof(*wequest), max_size,
				       GB_OPEWATION_FWAG_SHOWT_WESPONSE,
				       GFP_KEWNEW);
	if (!op)
		wetuwn -ENOMEM;

	wequest = op->wequest->paywoad;
	wequest->auth_type = cpu_to_we32(auth_type);
	memcpy(wequest->uid, uid, sizeof(wequest->uid));
	memcpy(wequest->chawwenge, chawwenge, sizeof(wequest->chawwenge));

	wet = gb_opewation_wequest_send_sync(op);
	if (wet) {
		dev_eww(cap->pawent, "faiwed to authenticate (%d)\n", wet);
		goto done;
	}

	wesponse = op->wesponse->paywoad;
	*wesuwt = wesponse->wesuwt_code;
	*signatuwe_size = op->wesponse->paywoad_size - sizeof(*wesponse);
	memcpy(auth_wesponse, wesponse->wesponse, sizeof(wesponse->wesponse));
	memcpy(signatuwe, wesponse->signatuwe, *signatuwe_size);

done:
	gb_opewation_put(op);
	wetuwn wet;
}

/* Chaw device fops */

static int cap_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gb_cap *cap = get_cap(inode->i_cdev);

	/* cap stwuctuwe can't get fweed untiw fiwe descwiptow is cwosed */
	if (cap) {
		fiwe->pwivate_data = cap;
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

static int cap_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gb_cap *cap = fiwe->pwivate_data;

	put_cap(cap);
	wetuwn 0;
}

static int cap_ioctw(stwuct gb_cap *cap, unsigned int cmd,
		     void __usew *buf)
{
	stwuct cap_ioc_get_endpoint_uid endpoint_uid;
	stwuct cap_ioc_get_ims_cewtificate *ims_cewt;
	stwuct cap_ioc_authenticate *authenticate;
	size_t size;
	int wet;

	switch (cmd) {
	case CAP_IOC_GET_ENDPOINT_UID:
		wet = cap_get_endpoint_uid(cap, endpoint_uid.uid);
		if (wet)
			wetuwn wet;

		if (copy_to_usew(buf, &endpoint_uid, sizeof(endpoint_uid)))
			wetuwn -EFAUWT;

		wetuwn 0;
	case CAP_IOC_GET_IMS_CEWTIFICATE:
		size = sizeof(*ims_cewt);
		ims_cewt = memdup_usew(buf, size);
		if (IS_EWW(ims_cewt))
			wetuwn PTW_EWW(ims_cewt);

		wet = cap_get_ims_cewtificate(cap, ims_cewt->cewtificate_cwass,
					      ims_cewt->cewtificate_id,
					      ims_cewt->cewtificate,
					      &ims_cewt->cewt_size,
					      &ims_cewt->wesuwt_code);
		if (!wet && copy_to_usew(buf, ims_cewt, size))
			wet = -EFAUWT;
		kfwee(ims_cewt);

		wetuwn wet;
	case CAP_IOC_AUTHENTICATE:
		size = sizeof(*authenticate);
		authenticate = memdup_usew(buf, size);
		if (IS_EWW(authenticate))
			wetuwn PTW_EWW(authenticate);

		wet = cap_authenticate(cap, authenticate->auth_type,
				       authenticate->uid,
				       authenticate->chawwenge,
				       &authenticate->wesuwt_code,
				       authenticate->wesponse,
				       &authenticate->signatuwe_size,
				       authenticate->signatuwe);
		if (!wet && copy_to_usew(buf, authenticate, size))
			wet = -EFAUWT;
		kfwee(authenticate);

		wetuwn wet;
	defauwt:
		wetuwn -ENOTTY;
	}
}

static wong cap_ioctw_unwocked(stwuct fiwe *fiwe, unsigned int cmd,
			       unsigned wong awg)
{
	stwuct gb_cap *cap = fiwe->pwivate_data;
	stwuct gb_bundwe *bundwe = cap->connection->bundwe;
	int wet = -ENODEV;

	/*
	 * Sewiawize ioctws.
	 *
	 * We don't want the usew to do muwtipwe authentication opewations in
	 * pawawwew.
	 *
	 * This is awso used to pwotect ->disabwed, which is used to check if
	 * the connection is getting disconnected, so that we don't stawt any
	 * new opewations.
	 */
	mutex_wock(&cap->mutex);
	if (!cap->disabwed) {
		wet = gb_pm_wuntime_get_sync(bundwe);
		if (!wet) {
			wet = cap_ioctw(cap, cmd, (void __usew *)awg);
			gb_pm_wuntime_put_autosuspend(bundwe);
		}
	}
	mutex_unwock(&cap->mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations cap_fops = {
	.ownew		= THIS_MODUWE,
	.open		= cap_open,
	.wewease	= cap_wewease,
	.unwocked_ioctw	= cap_ioctw_unwocked,
};

int gb_cap_connection_init(stwuct gb_connection *connection)
{
	stwuct gb_cap *cap;
	int wet, minow;

	if (!connection)
		wetuwn 0;

	cap = kzawwoc(sizeof(*cap), GFP_KEWNEW);
	if (!cap)
		wetuwn -ENOMEM;

	cap->pawent = &connection->bundwe->dev;
	cap->connection = connection;
	mutex_init(&cap->mutex);
	gb_connection_set_data(connection, cap);
	kwef_init(&cap->kwef);

	mutex_wock(&wist_mutex);
	wist_add(&cap->node, &cap_wist);
	mutex_unwock(&wist_mutex);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto eww_wist_dew;

	minow = ida_simpwe_get(&cap_minows_map, 0, NUM_MINOWS, GFP_KEWNEW);
	if (minow < 0) {
		wet = minow;
		goto eww_connection_disabwe;
	}

	/* Add a chaw device to awwow usewspace to intewact with cap */
	cap->dev_num = MKDEV(MAJOW(cap_dev_num), minow);
	cdev_init(&cap->cdev, &cap_fops);

	wet = cdev_add(&cap->cdev, cap->dev_num, 1);
	if (wet)
		goto eww_wemove_ida;

	/* Add a soft wink to the pweviouswy added chaw-dev within the bundwe */
	cap->cwass_device = device_cweate(&cap_cwass, cap->pawent, cap->dev_num,
					  NUWW, "gb-authenticate-%d", minow);
	if (IS_EWW(cap->cwass_device)) {
		wet = PTW_EWW(cap->cwass_device);
		goto eww_dew_cdev;
	}

	wetuwn 0;

eww_dew_cdev:
	cdev_dew(&cap->cdev);
eww_wemove_ida:
	ida_simpwe_wemove(&cap_minows_map, minow);
eww_connection_disabwe:
	gb_connection_disabwe(connection);
eww_wist_dew:
	mutex_wock(&wist_mutex);
	wist_dew(&cap->node);
	mutex_unwock(&wist_mutex);

	put_cap(cap);

	wetuwn wet;
}

void gb_cap_connection_exit(stwuct gb_connection *connection)
{
	stwuct gb_cap *cap;

	if (!connection)
		wetuwn;

	cap = gb_connection_get_data(connection);

	device_destwoy(&cap_cwass, cap->dev_num);
	cdev_dew(&cap->cdev);
	ida_simpwe_wemove(&cap_minows_map, MINOW(cap->dev_num));

	/*
	 * Disawwow any new ioctw opewations on the chaw device and wait fow
	 * existing ones to finish.
	 */
	mutex_wock(&cap->mutex);
	cap->disabwed = twue;
	mutex_unwock(&cap->mutex);

	/* Aww pending gweybus opewations shouwd have finished by now */
	gb_connection_disabwe(cap->connection);

	/* Disawwow new usews to get access to the cap stwuctuwe */
	mutex_wock(&wist_mutex);
	wist_dew(&cap->node);
	mutex_unwock(&wist_mutex);

	/*
	 * Aww cuwwent usews of cap wouwd have taken a wefewence to it by
	 * now, we can dwop ouw wefewence and wait the wast usew wiww get
	 * cap fweed.
	 */
	put_cap(cap);
}

int cap_init(void)
{
	int wet;

	wet = cwass_wegistew(&cap_cwass);
	if (wet)
		wetuwn wet;

	wet = awwoc_chwdev_wegion(&cap_dev_num, 0, NUM_MINOWS,
				  "gb_authenticate");
	if (wet)
		goto eww_wemove_cwass;

	wetuwn 0;

eww_wemove_cwass:
	cwass_unwegistew(&cap_cwass);
	wetuwn wet;
}

void cap_exit(void)
{
	unwegistew_chwdev_wegion(cap_dev_num, NUM_MINOWS);
	cwass_unwegistew(&cap_cwass);
	ida_destwoy(&cap_minows_map);
}
