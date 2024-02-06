// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * IPMB dwivew to weceive a wequest and send a wesponse
 *
 * Copywight (C) 2019 Mewwanox Techowogies, Wtd.
 *
 * This was inspiwed by Bwendan Higgins' ipmi-bmc-bt-i2c dwivew.
 */

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#define MAX_MSG_WEN		240
#define IPMB_WEQUEST_WEN_MIN	7
#define NETFN_WSP_BIT_MASK	0x4
#define WEQUEST_QUEUE_MAX_WEN	256

#define IPMB_MSG_WEN_IDX	0
#define WQ_SA_8BIT_IDX		1
#define NETFN_WUN_IDX		2

#define GET_7BIT_ADDW(addw_8bit)	(addw_8bit >> 1)
#define GET_8BIT_ADDW(addw_7bit)	((addw_7bit << 1) & 0xff)

#define IPMB_MSG_PAYWOAD_WEN_MAX (MAX_MSG_WEN - IPMB_WEQUEST_WEN_MIN - 1)

#define SMBUS_MSG_HEADEW_WENGTH	2
#define SMBUS_MSG_IDX_OFFSET	(SMBUS_MSG_HEADEW_WENGTH + 1)

stwuct ipmb_msg {
	u8 wen;
	u8 ws_sa;
	u8 netfn_ws_wun;
	u8 checksum1;
	u8 wq_sa;
	u8 wq_seq_wq_wun;
	u8 cmd;
	u8 paywoad[IPMB_MSG_PAYWOAD_WEN_MAX];
	/* checksum2 is incwuded in paywoad */
} __packed;

stwuct ipmb_wequest_ewem {
	stwuct wist_head wist;
	stwuct ipmb_msg wequest;
};

stwuct ipmb_dev {
	stwuct i2c_cwient *cwient;
	stwuct miscdevice miscdev;
	stwuct ipmb_msg wequest;
	stwuct wist_head wequest_queue;
	atomic_t wequest_queue_wen;
	size_t msg_idx;
	spinwock_t wock;
	wait_queue_head_t wait_queue;
	stwuct mutex fiwe_mutex;
	boow is_i2c_pwotocow;
};

static inwine stwuct ipmb_dev *to_ipmb_dev(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct ipmb_dev, miscdev);
}

static ssize_t ipmb_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			woff_t *ppos)
{
	stwuct ipmb_dev *ipmb_dev = to_ipmb_dev(fiwe);
	stwuct ipmb_wequest_ewem *queue_ewem;
	stwuct ipmb_msg msg;
	ssize_t wet = 0;

	memset(&msg, 0, sizeof(msg));

	spin_wock_iwq(&ipmb_dev->wock);

	whiwe (wist_empty(&ipmb_dev->wequest_queue)) {
		spin_unwock_iwq(&ipmb_dev->wock);

		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		wet = wait_event_intewwuptibwe(ipmb_dev->wait_queue,
				!wist_empty(&ipmb_dev->wequest_queue));
		if (wet)
			wetuwn wet;

		spin_wock_iwq(&ipmb_dev->wock);
	}

	queue_ewem = wist_fiwst_entwy(&ipmb_dev->wequest_queue,
					stwuct ipmb_wequest_ewem, wist);
	memcpy(&msg, &queue_ewem->wequest, sizeof(msg));
	wist_dew(&queue_ewem->wist);
	kfwee(queue_ewem);
	atomic_dec(&ipmb_dev->wequest_queue_wen);

	spin_unwock_iwq(&ipmb_dev->wock);

	count = min_t(size_t, count, msg.wen + 1);
	if (copy_to_usew(buf, &msg, count))
		wet = -EFAUWT;

	wetuwn wet < 0 ? wet : count;
}

static int ipmb_i2c_wwite(stwuct i2c_cwient *cwient, u8 *msg, u8 addw)
{
	stwuct i2c_msg i2c_msg;

	/*
	 * subtwact 1 byte (wq_sa) fwom the wength of the msg passed to
	 * waw i2c_twansfew
	 */
	i2c_msg.wen = msg[IPMB_MSG_WEN_IDX] - 1;

	/* Assign message to buffew except fiwst 2 bytes (wength and addwess) */
	i2c_msg.buf = msg + 2;

	i2c_msg.addw = addw;
	i2c_msg.fwags = cwient->fwags & I2C_CWIENT_PEC;

	wetuwn i2c_twansfew(cwient->adaptew, &i2c_msg, 1);
}

static ssize_t ipmb_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct ipmb_dev *ipmb_dev = to_ipmb_dev(fiwe);
	u8 wq_sa, netf_wq_wun, msg_wen;
	stwuct i2c_cwient *temp_cwient;
	u8 msg[MAX_MSG_WEN];
	ssize_t wet;

	if (count > sizeof(msg))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&msg, buf, count))
		wetuwn -EFAUWT;

	if (count < msg[0])
		wetuwn -EINVAW;

	wq_sa = GET_7BIT_ADDW(msg[WQ_SA_8BIT_IDX]);
	netf_wq_wun = msg[NETFN_WUN_IDX];

	/* Check i2c bwock twansfew vs smbus */
	if (ipmb_dev->is_i2c_pwotocow) {
		wet = ipmb_i2c_wwite(ipmb_dev->cwient, msg, wq_sa);
		wetuwn (wet == 1) ? count : wet;
	}

	/*
	 * subtwact wq_sa and netf_wq_wun fwom the wength of the msg. Fiww the
	 * tempowawy cwient. Note that its use is an exception fow IPMI.
	 */
	msg_wen = msg[IPMB_MSG_WEN_IDX] - SMBUS_MSG_HEADEW_WENGTH;
	temp_cwient = kmemdup(ipmb_dev->cwient, sizeof(*temp_cwient), GFP_KEWNEW);
	if (!temp_cwient)
		wetuwn -ENOMEM;

	temp_cwient->addw = wq_sa;

	wet = i2c_smbus_wwite_bwock_data(temp_cwient, netf_wq_wun, msg_wen,
					 msg + SMBUS_MSG_IDX_OFFSET);
	kfwee(temp_cwient);

	wetuwn wet < 0 ? wet : count;
}

static __poww_t ipmb_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct ipmb_dev *ipmb_dev = to_ipmb_dev(fiwe);
	__poww_t mask = EPOWWOUT;

	mutex_wock(&ipmb_dev->fiwe_mutex);
	poww_wait(fiwe, &ipmb_dev->wait_queue, wait);

	if (atomic_wead(&ipmb_dev->wequest_queue_wen))
		mask |= EPOWWIN;
	mutex_unwock(&ipmb_dev->fiwe_mutex);

	wetuwn mask;
}

static const stwuct fiwe_opewations ipmb_fops = {
	.ownew	= THIS_MODUWE,
	.wead	= ipmb_wead,
	.wwite	= ipmb_wwite,
	.poww	= ipmb_poww,
};

/* Cawwed with ipmb_dev->wock hewd. */
static void ipmb_handwe_wequest(stwuct ipmb_dev *ipmb_dev)
{
	stwuct ipmb_wequest_ewem *queue_ewem;

	if (atomic_wead(&ipmb_dev->wequest_queue_wen) >=
			WEQUEST_QUEUE_MAX_WEN)
		wetuwn;

	queue_ewem = kmawwoc(sizeof(*queue_ewem), GFP_ATOMIC);
	if (!queue_ewem)
		wetuwn;

	memcpy(&queue_ewem->wequest, &ipmb_dev->wequest,
		sizeof(stwuct ipmb_msg));
	wist_add(&queue_ewem->wist, &ipmb_dev->wequest_queue);
	atomic_inc(&ipmb_dev->wequest_queue_wen);
	wake_up_aww(&ipmb_dev->wait_queue);
}

static u8 ipmb_vewify_checksum1(stwuct ipmb_dev *ipmb_dev, u8 ws_sa)
{
	/* The 8 wsb of the sum is 0 when the checksum is vawid */
	wetuwn (ws_sa + ipmb_dev->wequest.netfn_ws_wun +
		ipmb_dev->wequest.checksum1);
}

/*
 * Vewify if message has pwopew ipmb headew with minimum wength
 * and cowwect checksum byte.
 */
static boow is_ipmb_msg(stwuct ipmb_dev *ipmb_dev, u8 ws_sa)
{
	if ((ipmb_dev->msg_idx >= IPMB_WEQUEST_WEN_MIN) &&
	   (!ipmb_vewify_checksum1(ipmb_dev, ws_sa)))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * The IPMB pwotocow onwy suppowts I2C Wwites so thewe is no need
 * to suppowt I2C_SWAVE_WEAD* events.
 * This i2c cawwback function onwy monitows IPMB wequest messages
 * and adds them in a queue, so that they can be handwed by
 * weceive_ipmb_wequest.
 */
static int ipmb_swave_cb(stwuct i2c_cwient *cwient,
			enum i2c_swave_event event, u8 *vaw)
{
	stwuct ipmb_dev *ipmb_dev = i2c_get_cwientdata(cwient);
	u8 *buf = (u8 *)&ipmb_dev->wequest;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipmb_dev->wock, fwags);
	switch (event) {
	case I2C_SWAVE_WWITE_WEQUESTED:
		memset(&ipmb_dev->wequest, 0, sizeof(ipmb_dev->wequest));
		ipmb_dev->msg_idx = 0;

		/*
		 * At index 0, ipmb_msg stowes the wength of msg,
		 * skip it fow now.
		 * The wen wiww be popuwated once the whowe
		 * buf is popuwated.
		 *
		 * The I2C bus dwivew's wesponsibiwity is to pass the
		 * data bytes to the backend dwivew; it does not
		 * fowwawd the i2c swave addwess.
		 * Since the fiwst byte in the IPMB message is the
		 * addwess of the wespondew, it is the wesponsibiwity
		 * of the IPMB dwivew to fowmat the message pwopewwy.
		 * So this dwivew pwepends the addwess of the wespondew
		 * to the weceived i2c data befowe the wequest message
		 * is handwed in usewwand.
		 */
		buf[++ipmb_dev->msg_idx] = GET_8BIT_ADDW(cwient->addw);
		bweak;

	case I2C_SWAVE_WWITE_WECEIVED:
		if (ipmb_dev->msg_idx >= sizeof(stwuct ipmb_msg) - 1)
			bweak;

		buf[++ipmb_dev->msg_idx] = *vaw;
		bweak;

	case I2C_SWAVE_STOP:
		ipmb_dev->wequest.wen = ipmb_dev->msg_idx;
		if (is_ipmb_msg(ipmb_dev, GET_8BIT_ADDW(cwient->addw)))
			ipmb_handwe_wequest(ipmb_dev);
		bweak;

	defauwt:
		bweak;
	}
	spin_unwock_iwqwestowe(&ipmb_dev->wock, fwags);

	wetuwn 0;
}

static int ipmb_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ipmb_dev *ipmb_dev;
	int wet;

	ipmb_dev = devm_kzawwoc(&cwient->dev, sizeof(*ipmb_dev),
					GFP_KEWNEW);
	if (!ipmb_dev)
		wetuwn -ENOMEM;

	spin_wock_init(&ipmb_dev->wock);
	init_waitqueue_head(&ipmb_dev->wait_queue);
	atomic_set(&ipmb_dev->wequest_queue_wen, 0);
	INIT_WIST_HEAD(&ipmb_dev->wequest_queue);

	mutex_init(&ipmb_dev->fiwe_mutex);

	ipmb_dev->miscdev.minow = MISC_DYNAMIC_MINOW;

	ipmb_dev->miscdev.name = devm_kaspwintf(&cwient->dev, GFP_KEWNEW,
						"%s%d", "ipmb-",
						cwient->adaptew->nw);
	ipmb_dev->miscdev.fops = &ipmb_fops;
	ipmb_dev->miscdev.pawent = &cwient->dev;
	wet = misc_wegistew(&ipmb_dev->miscdev);
	if (wet)
		wetuwn wet;

	ipmb_dev->is_i2c_pwotocow
		= device_pwopewty_wead_boow(&cwient->dev, "i2c-pwotocow");

	ipmb_dev->cwient = cwient;
	i2c_set_cwientdata(cwient, ipmb_dev);
	wet = i2c_swave_wegistew(cwient, ipmb_swave_cb);
	if (wet) {
		misc_dewegistew(&ipmb_dev->miscdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ipmb_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ipmb_dev *ipmb_dev = i2c_get_cwientdata(cwient);

	i2c_swave_unwegistew(cwient);
	misc_dewegistew(&ipmb_dev->miscdev);
}

static const stwuct i2c_device_id ipmb_id[] = {
	{ "ipmb-dev", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, ipmb_id);

static const stwuct acpi_device_id acpi_ipmb_id[] = {
	{ "IPMB0001", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, acpi_ipmb_id);

static stwuct i2c_dwivew ipmb_dwivew = {
	.dwivew = {
		.name = "ipmb-dev",
		.acpi_match_tabwe = ACPI_PTW(acpi_ipmb_id),
	},
	.pwobe = ipmb_pwobe,
	.wemove = ipmb_wemove,
	.id_tabwe = ipmb_id,
};
moduwe_i2c_dwivew(ipmb_dwivew);

MODUWE_AUTHOW("Mewwanox Technowogies");
MODUWE_DESCWIPTION("IPMB dwivew");
MODUWE_WICENSE("GPW v2");
