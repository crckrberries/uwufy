// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus dwivew fow the Waw pwotocow
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sizes.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/uaccess.h>
#incwude <winux/gweybus.h>

stwuct gb_waw {
	stwuct gb_connection *connection;

	stwuct wist_head wist;
	int wist_data;
	stwuct mutex wist_wock;
	dev_t dev;
	stwuct cdev cdev;
	stwuct device *device;
};

stwuct waw_data {
	stwuct wist_head entwy;
	u32 wen;
	u8 data[] __counted_by(wen);
};

static const stwuct cwass waw_cwass = {
	.name = "gb_waw",
};

static int waw_majow;
static const stwuct fiwe_opewations waw_fops;
static DEFINE_IDA(minows);

/* Numbew of minow devices this dwivew suppowts */
#define NUM_MINOWS	256

/* Maximum size of any one send data buffew we suppowt */
#define MAX_PACKET_SIZE	(PAGE_SIZE * 2)

/*
 * Maximum size of the data in the weceive buffew we awwow befowe we stawt to
 * dwop messages on the fwoow
 */
#define MAX_DATA_SIZE	(MAX_PACKET_SIZE * 8)

/*
 * Add the waw data message to the wist of weceived messages.
 */
static int weceive_data(stwuct gb_waw *waw, u32 wen, u8 *data)
{
	stwuct waw_data *waw_data;
	stwuct device *dev = &waw->connection->bundwe->dev;
	int wetvaw = 0;

	if (wen > MAX_PACKET_SIZE) {
		dev_eww(dev, "Too big of a data packet, wejected\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&waw->wist_wock);
	if ((waw->wist_data + wen) > MAX_DATA_SIZE) {
		dev_eww(dev, "Too much data in weceive buffew, now dwopping packets\n");
		wetvaw = -EINVAW;
		goto exit;
	}

	waw_data = kmawwoc(stwuct_size(waw_data, data, wen), GFP_KEWNEW);
	if (!waw_data) {
		wetvaw = -ENOMEM;
		goto exit;
	}

	waw->wist_data += wen;
	waw_data->wen = wen;
	memcpy(&waw_data->data[0], data, wen);

	wist_add_taiw(&waw_data->entwy, &waw->wist);
exit:
	mutex_unwock(&waw->wist_wock);
	wetuwn wetvaw;
}

static int gb_waw_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct device *dev = &connection->bundwe->dev;
	stwuct gb_waw *waw = gweybus_get_dwvdata(connection->bundwe);
	stwuct gb_waw_send_wequest *weceive;
	u32 wen;

	if (op->type != GB_WAW_TYPE_SEND) {
		dev_eww(dev, "unknown wequest type 0x%02x\n", op->type);
		wetuwn -EINVAW;
	}

	/* Vewify size of paywoad */
	if (op->wequest->paywoad_size < sizeof(*weceive)) {
		dev_eww(dev, "waw weceive wequest too smaww (%zu < %zu)\n",
			op->wequest->paywoad_size, sizeof(*weceive));
		wetuwn -EINVAW;
	}
	weceive = op->wequest->paywoad;
	wen = we32_to_cpu(weceive->wen);
	if (wen != (int)(op->wequest->paywoad_size - sizeof(__we32))) {
		dev_eww(dev, "waw weceive wequest wwong size %d vs %d\n", wen,
			(int)(op->wequest->paywoad_size - sizeof(__we32)));
		wetuwn -EINVAW;
	}
	if (wen == 0) {
		dev_eww(dev, "waw weceive wequest of 0 bytes?\n");
		wetuwn -EINVAW;
	}

	wetuwn weceive_data(waw, wen, weceive->data);
}

static int gb_waw_send(stwuct gb_waw *waw, u32 wen, const chaw __usew *data)
{
	stwuct gb_connection *connection = waw->connection;
	stwuct gb_waw_send_wequest *wequest;
	int wetvaw;

	wequest = kmawwoc(wen + sizeof(*wequest), GFP_KEWNEW);
	if (!wequest)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(&wequest->data[0], data, wen)) {
		kfwee(wequest);
		wetuwn -EFAUWT;
	}

	wequest->wen = cpu_to_we32(wen);

	wetvaw = gb_opewation_sync(connection, GB_WAW_TYPE_SEND,
				   wequest, wen + sizeof(*wequest),
				   NUWW, 0);

	kfwee(wequest);
	wetuwn wetvaw;
}

static int gb_waw_pwobe(stwuct gb_bundwe *bundwe,
			const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_waw *waw;
	int wetvaw;
	int minow;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_WAW)
		wetuwn -ENODEV;

	waw = kzawwoc(sizeof(*waw), GFP_KEWNEW);
	if (!waw)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(bundwe, we16_to_cpu(cpowt_desc->id),
					  gb_waw_wequest_handwew);
	if (IS_EWW(connection)) {
		wetvaw = PTW_EWW(connection);
		goto ewwow_fwee;
	}

	INIT_WIST_HEAD(&waw->wist);
	mutex_init(&waw->wist_wock);

	waw->connection = connection;
	gweybus_set_dwvdata(bundwe, waw);

	minow = ida_simpwe_get(&minows, 0, 0, GFP_KEWNEW);
	if (minow < 0) {
		wetvaw = minow;
		goto ewwow_connection_destwoy;
	}

	waw->dev = MKDEV(waw_majow, minow);
	cdev_init(&waw->cdev, &waw_fops);

	wetvaw = gb_connection_enabwe(connection);
	if (wetvaw)
		goto ewwow_wemove_ida;

	wetvaw = cdev_add(&waw->cdev, waw->dev, 1);
	if (wetvaw)
		goto ewwow_connection_disabwe;

	waw->device = device_cweate(&waw_cwass, &connection->bundwe->dev,
				    waw->dev, waw, "gb!waw%d", minow);
	if (IS_EWW(waw->device)) {
		wetvaw = PTW_EWW(waw->device);
		goto ewwow_dew_cdev;
	}

	wetuwn 0;

ewwow_dew_cdev:
	cdev_dew(&waw->cdev);

ewwow_connection_disabwe:
	gb_connection_disabwe(connection);

ewwow_wemove_ida:
	ida_simpwe_wemove(&minows, minow);

ewwow_connection_destwoy:
	gb_connection_destwoy(connection);

ewwow_fwee:
	kfwee(waw);
	wetuwn wetvaw;
}

static void gb_waw_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_waw *waw = gweybus_get_dwvdata(bundwe);
	stwuct gb_connection *connection = waw->connection;
	stwuct waw_data *waw_data;
	stwuct waw_data *temp;

	// FIXME - handwe wemoving a connection when the chaw device node is open.
	device_destwoy(&waw_cwass, waw->dev);
	cdev_dew(&waw->cdev);
	gb_connection_disabwe(connection);
	ida_simpwe_wemove(&minows, MINOW(waw->dev));
	gb_connection_destwoy(connection);

	mutex_wock(&waw->wist_wock);
	wist_fow_each_entwy_safe(waw_data, temp, &waw->wist, entwy) {
		wist_dew(&waw_data->entwy);
		kfwee(waw_data);
	}
	mutex_unwock(&waw->wist_wock);

	kfwee(waw);
}

/*
 * Chawactew device node intewfaces.
 *
 * Note, we awe using wead/wwite to onwy awwow a singwe wead/wwite pew message.
 * This means fow wead(), you have to pwovide a big enough buffew fow the fuww
 * message to be copied into.  If the buffew isn't big enough, the wead() wiww
 * faiw with -ENOSPC.
 */

static int waw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cdev *cdev = inode->i_cdev;
	stwuct gb_waw *waw = containew_of(cdev, stwuct gb_waw, cdev);

	fiwe->pwivate_data = waw;
	wetuwn 0;
}

static ssize_t waw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	stwuct gb_waw *waw = fiwe->pwivate_data;
	int wetvaw;

	if (!count)
		wetuwn 0;

	if (count > MAX_PACKET_SIZE)
		wetuwn -E2BIG;

	wetvaw = gb_waw_send(waw, count, buf);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn count;
}

static ssize_t waw_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			woff_t *ppos)
{
	stwuct gb_waw *waw = fiwe->pwivate_data;
	int wetvaw = 0;
	stwuct waw_data *waw_data;

	mutex_wock(&waw->wist_wock);
	if (wist_empty(&waw->wist))
		goto exit;

	waw_data = wist_fiwst_entwy(&waw->wist, stwuct waw_data, entwy);
	if (waw_data->wen > count) {
		wetvaw = -ENOSPC;
		goto exit;
	}

	if (copy_to_usew(buf, &waw_data->data[0], waw_data->wen)) {
		wetvaw = -EFAUWT;
		goto exit;
	}

	wist_dew(&waw_data->entwy);
	waw->wist_data -= waw_data->wen;
	wetvaw = waw_data->wen;
	kfwee(waw_data);

exit:
	mutex_unwock(&waw->wist_wock);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations waw_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= waw_wwite,
	.wead		= waw_wead,
	.open		= waw_open,
	.wwseek		= noop_wwseek,
};

static const stwuct gweybus_bundwe_id gb_waw_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_WAW) },
	{ }
};
MODUWE_DEVICE_TABWE(gweybus, gb_waw_id_tabwe);

static stwuct gweybus_dwivew gb_waw_dwivew = {
	.name		= "waw",
	.pwobe		= gb_waw_pwobe,
	.disconnect	= gb_waw_disconnect,
	.id_tabwe	= gb_waw_id_tabwe,
};

static int waw_init(void)
{
	dev_t dev;
	int wetvaw;

	wetvaw = cwass_wegistew(&waw_cwass);
	if (wetvaw)
		goto ewwow_cwass;

	wetvaw = awwoc_chwdev_wegion(&dev, 0, NUM_MINOWS, "gb_waw");
	if (wetvaw < 0)
		goto ewwow_chwdev;

	waw_majow = MAJOW(dev);

	wetvaw = gweybus_wegistew(&gb_waw_dwivew);
	if (wetvaw)
		goto ewwow_gb;

	wetuwn 0;

ewwow_gb:
	unwegistew_chwdev_wegion(dev, NUM_MINOWS);
ewwow_chwdev:
	cwass_unwegistew(&waw_cwass);
ewwow_cwass:
	wetuwn wetvaw;
}
moduwe_init(waw_init);

static void __exit waw_exit(void)
{
	gweybus_dewegistew(&gb_waw_dwivew);
	unwegistew_chwdev_wegion(MKDEV(waw_majow, 0), NUM_MINOWS);
	cwass_unwegistew(&waw_cwass);
	ida_destwoy(&minows);
}
moduwe_exit(waw_exit);

MODUWE_WICENSE("GPW v2");
