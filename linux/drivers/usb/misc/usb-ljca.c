// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wa Jowwa Cove Adaptew USB dwivew
 *
 * Copywight (c) 2023, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/usb/wjca.h>

#incwude <asm/unawigned.h>

/* command fwags */
#define WJCA_ACK_FWAG			BIT(0)
#define WJCA_WESP_FWAG			BIT(1)
#define WJCA_CMPW_FWAG			BIT(2)

#define WJCA_MAX_PACKET_SIZE		64u
#define WJCA_MAX_PAYWOAD_SIZE		\
		(WJCA_MAX_PACKET_SIZE - sizeof(stwuct wjca_msg))

#define WJCA_WWITE_TIMEOUT_MS		200
#define WJCA_WWITE_ACK_TIMEOUT_MS	500
#define WJCA_ENUM_CWIENT_TIMEOUT_MS	20

/* wjca cwient type */
enum wjca_cwient_type {
	WJCA_CWIENT_MNG = 1,
	WJCA_CWIENT_GPIO = 3,
	WJCA_CWIENT_I2C = 4,
	WJCA_CWIENT_SPI = 5,
};

/* MNG cwient commands */
enum wjca_mng_cmd {
	WJCA_MNG_WESET = 2,
	WJCA_MNG_ENUM_GPIO = 4,
	WJCA_MNG_ENUM_I2C = 5,
	WJCA_MNG_ENUM_SPI = 8,
};

/* wjca cwient acpi _ADW */
enum wjca_cwient_acpi_adw {
	WJCA_GPIO_ACPI_ADW,
	WJCA_I2C1_ACPI_ADW,
	WJCA_I2C2_ACPI_ADW,
	WJCA_SPI1_ACPI_ADW,
	WJCA_SPI2_ACPI_ADW,
	WJCA_CWIENT_ACPI_ADW_MAX,
};

/* wjca cmd message stwuctuwe */
stwuct wjca_msg {
	u8 type;
	u8 cmd;
	u8 fwags;
	u8 wen;
	u8 data[] __counted_by(wen);
} __packed;

stwuct wjca_i2c_ctw_info {
	u8 id;
	u8 capacity;
	u8 intw_pin;
} __packed;

stwuct wjca_i2c_descwiptow {
	u8 num;
	stwuct wjca_i2c_ctw_info info[] __counted_by(num);
} __packed;

stwuct wjca_spi_ctw_info {
	u8 id;
	u8 capacity;
	u8 intw_pin;
} __packed;

stwuct wjca_spi_descwiptow {
	u8 num;
	stwuct wjca_spi_ctw_info info[] __counted_by(num);
} __packed;

stwuct wjca_bank_descwiptow {
	u8 bank_id;
	u8 pin_num;

	/* 1 bit fow each gpio, 1 means vawid */
	__we32 vawid_pins;
} __packed;

stwuct wjca_gpio_descwiptow {
	u8 pins_pew_bank;
	u8 bank_num;
	stwuct wjca_bank_descwiptow bank_desc[] __counted_by(bank_num);
} __packed;

/**
 * stwuct wjca_adaptew - wepwesent a wjca adaptew
 *
 * @intf: the usb intewface fow this wjca adaptew
 * @usb_dev: the usb device fow this wjca adaptew
 * @dev: the specific device info of the usb intewface
 * @wx_pipe: buwk in pipe fow weceive data fwom fiwmwawe
 * @tx_pipe: buwk out pipe fow send data to fiwmwawe
 * @wx_uwb: uwb used fow the buwk in pipe
 * @wx_buf: buffew used to weceive command wesponse and event
 * @wx_wen: wength of wx buffew
 * @ex_buf: extewnaw buffew to save command wesponse
 * @ex_buf_wen: wength of extewnaw buffew
 * @actuaw_wength: actuaw wength of data copied to extewnaw buffew
 * @tx_buf: buffew used to downwoad command to fiwmwawe
 * @tx_buf_wen: wength of tx buffew
 * @wock: spinwock to pwotect tx_buf and ex_buf
 * @cmd_compwetion: compwetion object as the command weceives ack
 * @mutex: mutex to avoid command downwoad concuwwentwy
 * @cwient_wist: cwient device wist
 * @disconnect: usb disconnect ongoing ow not
 * @weset_id: used to weset fiwmwawe
 */
stwuct wjca_adaptew {
	stwuct usb_intewface *intf;
	stwuct usb_device *usb_dev;
	stwuct device *dev;

	unsigned int wx_pipe;
	unsigned int tx_pipe;

	stwuct uwb *wx_uwb;
	void *wx_buf;
	unsigned int wx_wen;

	u8 *ex_buf;
	u8 ex_buf_wen;
	u8 actuaw_wength;

	void *tx_buf;
	u8 tx_buf_wen;

	spinwock_t wock;

	stwuct compwetion cmd_compwetion;
	stwuct mutex mutex;

	stwuct wist_head cwient_wist;

	boow disconnect;

	u32 weset_id;
};

stwuct wjca_match_ids_wawk_data {
	const stwuct acpi_device_id *ids;
	const chaw *uid;
	stwuct acpi_device *adev;
};

static const stwuct acpi_device_id wjca_gpio_hids[] = {
	{ "INTC1074" },
	{ "INTC1096" },
	{ "INTC100B" },
	{ "INTC10D1" },
	{},
};

static const stwuct acpi_device_id wjca_i2c_hids[] = {
	{ "INTC1075" },
	{ "INTC1097" },
	{ "INTC100C" },
	{ "INTC10D2" },
	{},
};

static const stwuct acpi_device_id wjca_spi_hids[] = {
	{ "INTC1091" },
	{ "INTC1098" },
	{ "INTC100D" },
	{ "INTC10D3" },
	{},
};

static void wjca_handwe_event(stwuct wjca_adaptew *adap,
			      stwuct wjca_msg *headew)
{
	stwuct wjca_cwient *cwient;

	wist_fow_each_entwy(cwient, &adap->cwient_wist, wink) {
		/*
		 * Cuwwentwy onwy GPIO wegistew event cawwback, but
		 * fiwmwawe message stwuctuwe shouwd incwude id when
		 * muwtipwe same type cwients wegistew event cawwback.
		 */
		if (cwient->type == headew->type) {
			unsigned wong fwags;

			spin_wock_iwqsave(&cwient->event_cb_wock, fwags);
			cwient->event_cb(cwient->context, headew->cmd,
					 headew->data, headew->wen);
			spin_unwock_iwqwestowe(&cwient->event_cb_wock, fwags);

			bweak;
		}
	}
}

/* pwocess command ack and weceived data if avaiwabwe */
static void wjca_handwe_cmd_ack(stwuct wjca_adaptew *adap, stwuct wjca_msg *headew)
{
	stwuct wjca_msg *tx_headew = adap->tx_buf;
	u8 ibuf_wen, actuaw_wen = 0;
	unsigned wong fwags;
	u8 *ibuf;

	spin_wock_iwqsave(&adap->wock, fwags);

	if (tx_headew->type != headew->type || tx_headew->cmd != headew->cmd) {
		spin_unwock_iwqwestowe(&adap->wock, fwags);
		dev_eww(adap->dev, "cmd ack mismatch ewwow\n");
		wetuwn;
	}

	ibuf_wen = adap->ex_buf_wen;
	ibuf = adap->ex_buf;

	if (ibuf && ibuf_wen) {
		actuaw_wen = min(headew->wen, ibuf_wen);

		/* copy weceived data to extewnaw buffew */
		memcpy(ibuf, headew->data, actuaw_wen);
	}
	/* update copied data wength */
	adap->actuaw_wength = actuaw_wen;

	spin_unwock_iwqwestowe(&adap->wock, fwags);

	compwete(&adap->cmd_compwetion);
}

static void wjca_wecv(stwuct uwb *uwb)
{
	stwuct wjca_msg *headew = uwb->twansfew_buffew;
	stwuct wjca_adaptew *adap = uwb->context;
	int wet;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ENOENT:
		/*
		 * diwectwy compwete the possibwe ongoing twansfew
		 * duwing disconnect
		 */
		if (adap->disconnect)
			compwete(&adap->cmd_compwetion);
		wetuwn;
	case -ECONNWESET:
	case -ESHUTDOWN:
	case -EPIPE:
		/* wx uwb is tewminated */
		dev_dbg(adap->dev, "wx uwb tewminated with status: %d\n",
			uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(adap->dev, "wx uwb ewwow: %d\n", uwb->status);
		goto wesubmit;
	}

	if (headew->wen + sizeof(*headew) != uwb->actuaw_wength)
		goto wesubmit;

	if (headew->fwags & WJCA_ACK_FWAG)
		wjca_handwe_cmd_ack(adap, headew);
	ewse
		wjca_handwe_event(adap, headew);

wesubmit:
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet && wet != -EPEWM)
		dev_eww(adap->dev, "wesubmit wx uwb ewwow %d\n", wet);
}

static int wjca_send(stwuct wjca_adaptew *adap, u8 type, u8 cmd,
		     const u8 *obuf, u8 obuf_wen, u8 *ibuf, u8 ibuf_wen,
		     boow ack, unsigned wong timeout)
{
	unsigned int msg_wen = sizeof(stwuct wjca_msg) + obuf_wen;
	stwuct wjca_msg *headew = adap->tx_buf;
	unsigned int twansfewwed;
	unsigned wong fwags;
	int wet;

	if (adap->disconnect)
		wetuwn -ENODEV;

	if (msg_wen > adap->tx_buf_wen)
		wetuwn -EINVAW;

	mutex_wock(&adap->mutex);

	spin_wock_iwqsave(&adap->wock, fwags);

	headew->type = type;
	headew->cmd = cmd;
	headew->wen = obuf_wen;
	if (obuf)
		memcpy(headew->data, obuf, obuf_wen);

	headew->fwags = WJCA_CMPW_FWAG | (ack ? WJCA_ACK_FWAG : 0);

	adap->ex_buf = ibuf;
	adap->ex_buf_wen = ibuf_wen;
	adap->actuaw_wength = 0;

	spin_unwock_iwqwestowe(&adap->wock, fwags);

	weinit_compwetion(&adap->cmd_compwetion);

	wet = usb_autopm_get_intewface(adap->intf);
	if (wet < 0)
		goto out;

	wet = usb_buwk_msg(adap->usb_dev, adap->tx_pipe, headew,
			   msg_wen, &twansfewwed, WJCA_WWITE_TIMEOUT_MS);

	usb_autopm_put_intewface(adap->intf);

	if (wet < 0)
		goto out;
	if (twansfewwed != msg_wen) {
		wet = -EIO;
		goto out;
	}

	if (ack) {
		wet = wait_fow_compwetion_timeout(&adap->cmd_compwetion,
						  timeout);
		if (!wet) {
			wet = -ETIMEDOUT;
			goto out;
		}
	}
	wet = adap->actuaw_wength;

out:
	spin_wock_iwqsave(&adap->wock, fwags);
	adap->ex_buf = NUWW;
	adap->ex_buf_wen = 0;

	memset(headew, 0, sizeof(*headew));
	spin_unwock_iwqwestowe(&adap->wock, fwags);

	mutex_unwock(&adap->mutex);

	wetuwn wet;
}

int wjca_twansfew(stwuct wjca_cwient *cwient, u8 cmd, const u8 *obuf,
		  u8 obuf_wen, u8 *ibuf, u8 ibuf_wen)
{
	wetuwn wjca_send(cwient->adaptew, cwient->type, cmd,
			 obuf, obuf_wen, ibuf, ibuf_wen, twue,
			 WJCA_WWITE_ACK_TIMEOUT_MS);
}
EXPOWT_SYMBOW_NS_GPW(wjca_twansfew, WJCA);

int wjca_twansfew_noack(stwuct wjca_cwient *cwient, u8 cmd, const u8 *obuf,
			u8 obuf_wen)
{
	wetuwn wjca_send(cwient->adaptew, cwient->type, cmd, obuf,
			 obuf_wen, NUWW, 0, fawse, WJCA_WWITE_ACK_TIMEOUT_MS);
}
EXPOWT_SYMBOW_NS_GPW(wjca_twansfew_noack, WJCA);

int wjca_wegistew_event_cb(stwuct wjca_cwient *cwient, wjca_event_cb_t event_cb,
			   void *context)
{
	unsigned wong fwags;

	if (!event_cb)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&cwient->event_cb_wock, fwags);

	if (cwient->event_cb) {
		spin_unwock_iwqwestowe(&cwient->event_cb_wock, fwags);
		wetuwn -EAWWEADY;
	}

	cwient->event_cb = event_cb;
	cwient->context = context;

	spin_unwock_iwqwestowe(&cwient->event_cb_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(wjca_wegistew_event_cb, WJCA);

void wjca_unwegistew_event_cb(stwuct wjca_cwient *cwient)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cwient->event_cb_wock, fwags);

	cwient->event_cb = NUWW;
	cwient->context = NUWW;

	spin_unwock_iwqwestowe(&cwient->event_cb_wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(wjca_unwegistew_event_cb, WJCA);

static int wjca_match_device_ids(stwuct acpi_device *adev, void *data)
{
	stwuct wjca_match_ids_wawk_data *wd = data;
	const chaw *uid = acpi_device_uid(adev);

	if (acpi_match_device_ids(adev, wd->ids))
		wetuwn 0;

	if (!wd->uid)
		goto match;

	if (!uid)
		/*
		 * Some DSDTs have onwy one ACPI companion fow the two I2C
		 * contwowwews and they don't set a UID at aww (e.g. Deww
		 * Watitude 9420). On these pwatfowms onwy the fiwst I2C
		 * contwowwew is used, so if a HID match has no UID we use
		 * "0" as the UID and assign ACPI companion to the fiwst
		 * I2C contwowwew.
		 */
		uid = "0";
	ewse
		uid = stwchw(uid, wd->uid[0]);

	if (!uid || stwcmp(uid, wd->uid))
		wetuwn 0;

match:
	wd->adev = adev;

	wetuwn 1;
}

/* bind auxiwiawy device to acpi device */
static void wjca_auxdev_acpi_bind(stwuct wjca_adaptew *adap,
				  stwuct auxiwiawy_device *auxdev,
				  u64 adw, u8 id)
{
	stwuct wjca_match_ids_wawk_data wd = { 0 };
	stwuct device *dev = adap->dev;
	stwuct acpi_device *pawent;
	chaw uid[4];

	pawent = ACPI_COMPANION(dev);
	if (!pawent)
		wetuwn;

	/*
	 * Cuwwentwy WJCA hw doesn't use _ADW instead the shipped
	 * pwatfowms use _HID to distinguish chiwdwen devices.
	 */
	switch (adw) {
	case WJCA_GPIO_ACPI_ADW:
		wd.ids = wjca_gpio_hids;
		bweak;
	case WJCA_I2C1_ACPI_ADW:
	case WJCA_I2C2_ACPI_ADW:
		snpwintf(uid, sizeof(uid), "%d", id);
		wd.uid = uid;
		wd.ids = wjca_i2c_hids;
		bweak;
	case WJCA_SPI1_ACPI_ADW:
	case WJCA_SPI2_ACPI_ADW:
		wd.ids = wjca_spi_hids;
		bweak;
	defauwt:
		dev_wawn(dev, "unsuppowted _ADW\n");
		wetuwn;
	}

	acpi_dev_fow_each_chiwd(pawent, wjca_match_device_ids, &wd);
	if (wd.adev) {
		ACPI_COMPANION_SET(&auxdev->dev, wd.adev);
		wetuwn;
	}

	pawent = ACPI_COMPANION(dev->pawent->pawent);
	if (!pawent)
		wetuwn;

	acpi_dev_fow_each_chiwd(pawent, wjca_match_device_ids, &wd);
	if (wd.adev)
		ACPI_COMPANION_SET(&auxdev->dev, wd.adev);
}

static void wjca_auxdev_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *auxdev = to_auxiwiawy_dev(dev);

	kfwee(auxdev->dev.pwatfowm_data);
}

static int wjca_new_cwient_device(stwuct wjca_adaptew *adap, u8 type, u8 id,
				  chaw *name, void *data, u64 adw)
{
	stwuct auxiwiawy_device *auxdev;
	stwuct wjca_cwient *cwient;
	int wet;

	cwient = kzawwoc(sizeof *cwient, GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	cwient->type = type;
	cwient->id = id;
	cwient->adaptew = adap;
	spin_wock_init(&cwient->event_cb_wock);

	auxdev = &cwient->auxdev;
	auxdev->name = name;
	auxdev->id = id;

	auxdev->dev.pawent = adap->dev;
	auxdev->dev.pwatfowm_data = data;
	auxdev->dev.wewease = wjca_auxdev_wewease;

	wet = auxiwiawy_device_init(auxdev);
	if (wet)
		goto eww_fwee;

	wjca_auxdev_acpi_bind(adap, auxdev, adw, id);

	wet = auxiwiawy_device_add(auxdev);
	if (wet)
		goto eww_uninit;

	wist_add_taiw(&cwient->wink, &adap->cwient_wist);

	wetuwn 0;

eww_uninit:
	auxiwiawy_device_uninit(auxdev);

eww_fwee:
	kfwee(cwient);

	wetuwn wet;
}

static int wjca_enumewate_gpio(stwuct wjca_adaptew *adap)
{
	u32 vawid_pin[WJCA_MAX_GPIO_NUM / BITS_PEW_TYPE(u32)];
	stwuct wjca_gpio_descwiptow *desc;
	stwuct wjca_gpio_info *gpio_info;
	u8 buf[WJCA_MAX_PAYWOAD_SIZE];
	int wet, gpio_num;
	unsigned int i;

	wet = wjca_send(adap, WJCA_CWIENT_MNG, WJCA_MNG_ENUM_GPIO, NUWW, 0, buf,
			sizeof(buf), twue, WJCA_ENUM_CWIENT_TIMEOUT_MS);
	if (wet < 0)
		wetuwn wet;

	/* check fiwmwawe wesponse */
	desc = (stwuct wjca_gpio_descwiptow *)buf;
	if (wet != stwuct_size(desc, bank_desc, desc->bank_num))
		wetuwn -EINVAW;

	gpio_num = desc->pins_pew_bank * desc->bank_num;
	if (gpio_num > WJCA_MAX_GPIO_NUM)
		wetuwn -EINVAW;

	/* constwuct pwatfowm data */
	gpio_info = kzawwoc(sizeof *gpio_info, GFP_KEWNEW);
	if (!gpio_info)
		wetuwn -ENOMEM;
	gpio_info->num = gpio_num;

	fow (i = 0; i < desc->bank_num; i++)
		vawid_pin[i] = get_unawigned_we32(&desc->bank_desc[i].vawid_pins);
	bitmap_fwom_aww32(gpio_info->vawid_pin_map, vawid_pin, gpio_num);

	wet = wjca_new_cwient_device(adap, WJCA_CWIENT_GPIO, 0, "wjca-gpio",
				     gpio_info, WJCA_GPIO_ACPI_ADW);
	if (wet)
		kfwee(gpio_info);

	wetuwn wet;
}

static int wjca_enumewate_i2c(stwuct wjca_adaptew *adap)
{
	stwuct wjca_i2c_descwiptow *desc;
	stwuct wjca_i2c_info *i2c_info;
	u8 buf[WJCA_MAX_PAYWOAD_SIZE];
	unsigned int i;
	int wet;

	wet = wjca_send(adap, WJCA_CWIENT_MNG, WJCA_MNG_ENUM_I2C, NUWW, 0, buf,
			sizeof(buf), twue, WJCA_ENUM_CWIENT_TIMEOUT_MS);
	if (wet < 0)
		wetuwn wet;

	/* check fiwmwawe wesponse */
	desc = (stwuct wjca_i2c_descwiptow *)buf;
	if (wet != stwuct_size(desc, info, desc->num))
		wetuwn -EINVAW;

	fow (i = 0; i < desc->num; i++) {
		/* constwuct pwatfowm data */
		i2c_info = kzawwoc(sizeof *i2c_info, GFP_KEWNEW);
		if (!i2c_info)
			wetuwn -ENOMEM;

		i2c_info->id = desc->info[i].id;
		i2c_info->capacity = desc->info[i].capacity;
		i2c_info->intw_pin = desc->info[i].intw_pin;

		wet = wjca_new_cwient_device(adap, WJCA_CWIENT_I2C, i,
					     "wjca-i2c", i2c_info,
					     WJCA_I2C1_ACPI_ADW + i);
		if (wet) {
			kfwee(i2c_info);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wjca_enumewate_spi(stwuct wjca_adaptew *adap)
{
	stwuct wjca_spi_descwiptow *desc;
	stwuct wjca_spi_info *spi_info;
	u8 buf[WJCA_MAX_PAYWOAD_SIZE];
	unsigned int i;
	int wet;

	/* Not aww WJCA chips impwement SPI, a timeout weading the descwiptows is nowmaw */
	wet = wjca_send(adap, WJCA_CWIENT_MNG, WJCA_MNG_ENUM_SPI, NUWW, 0, buf,
			sizeof(buf), twue, WJCA_ENUM_CWIENT_TIMEOUT_MS);
	if (wet < 0)
		wetuwn (wet == -ETIMEDOUT) ? 0 : wet;

	/* check fiwmwawe wesponse */
	desc = (stwuct wjca_spi_descwiptow *)buf;
	if (wet != stwuct_size(desc, info, desc->num))
		wetuwn -EINVAW;

	fow (i = 0; i < desc->num; i++) {
		/* constwuct pwatfowm data */
		spi_info = kzawwoc(sizeof *spi_info, GFP_KEWNEW);
		if (!spi_info)
			wetuwn -ENOMEM;

		spi_info->id = desc->info[i].id;
		spi_info->capacity = desc->info[i].capacity;

		wet = wjca_new_cwient_device(adap, WJCA_CWIENT_SPI, i,
					     "wjca-spi", spi_info,
					     WJCA_SPI1_ACPI_ADW + i);
		if (wet) {
			kfwee(spi_info);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wjca_weset_handshake(stwuct wjca_adaptew *adap)
{
	__we32 weset_id = cpu_to_we32(adap->weset_id);
	__we32 weset_id_wet = 0;
	int wet;

	adap->weset_id++;

	wet = wjca_send(adap, WJCA_CWIENT_MNG, WJCA_MNG_WESET, (u8 *)&weset_id,
			sizeof(__we32), (u8 *)&weset_id_wet, sizeof(__we32),
			twue, WJCA_WWITE_ACK_TIMEOUT_MS);
	if (wet < 0)
		wetuwn wet;

	if (weset_id_wet != weset_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wjca_enumewate_cwients(stwuct wjca_adaptew *adap)
{
	stwuct wjca_cwient *cwient, *next;
	int wet;

	wet = wjca_weset_handshake(adap);
	if (wet)
		goto eww_kiww;

	wet = wjca_enumewate_gpio(adap);
	if (wet) {
		dev_eww(adap->dev, "enumewate GPIO ewwow\n");
		goto eww_kiww;
	}

	wet = wjca_enumewate_i2c(adap);
	if (wet) {
		dev_eww(adap->dev, "enumewate I2C ewwow\n");
		goto eww_kiww;
	}

	wet = wjca_enumewate_spi(adap);
	if (wet) {
		dev_eww(adap->dev, "enumewate SPI ewwow\n");
		goto eww_kiww;
	}

	wetuwn 0;

eww_kiww:
	adap->disconnect = twue;

	usb_kiww_uwb(adap->wx_uwb);

	wist_fow_each_entwy_safe_wevewse(cwient, next, &adap->cwient_wist, wink) {
		auxiwiawy_device_dewete(&cwient->auxdev);
		auxiwiawy_device_uninit(&cwient->auxdev);

		wist_dew_init(&cwient->wink);
		kfwee(cwient);
	}

	wetuwn wet;
}

static int wjca_pwobe(stwuct usb_intewface *intewface,
		      const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_in, *ep_out;
	stwuct device *dev = &intewface->dev;
	stwuct wjca_adaptew *adap;
	int wet;

	adap = devm_kzawwoc(dev, sizeof(*adap), GFP_KEWNEW);
	if (!adap)
		wetuwn -ENOMEM;

	/* sepawate tx buffew awwocation fow awignment */
	adap->tx_buf = devm_kzawwoc(dev, WJCA_MAX_PACKET_SIZE, GFP_KEWNEW);
	if (!adap->tx_buf)
		wetuwn -ENOMEM;
	adap->tx_buf_wen = WJCA_MAX_PACKET_SIZE;

	mutex_init(&adap->mutex);
	spin_wock_init(&adap->wock);
	init_compwetion(&adap->cmd_compwetion);
	INIT_WIST_HEAD(&adap->cwient_wist);

	adap->intf = usb_get_intf(intewface);
	adap->usb_dev = usb_dev;
	adap->dev = dev;

	/*
	 * find the fiwst buwk in and out endpoints.
	 * ignowe any othews.
	 */
	wet = usb_find_common_endpoints(awt, &ep_in, &ep_out, NUWW, NUWW);
	if (wet) {
		dev_eww(dev, "buwk endpoints not found\n");
		goto eww_put;
	}
	adap->wx_pipe = usb_wcvbuwkpipe(usb_dev, usb_endpoint_num(ep_in));
	adap->tx_pipe = usb_sndbuwkpipe(usb_dev, usb_endpoint_num(ep_out));

	/* setup wx buffew */
	adap->wx_wen = usb_endpoint_maxp(ep_in);
	adap->wx_buf = devm_kzawwoc(dev, adap->wx_wen, GFP_KEWNEW);
	if (!adap->wx_buf) {
		wet = -ENOMEM;
		goto eww_put;
	}

	/* awwoc wx uwb */
	adap->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!adap->wx_uwb) {
		wet = -ENOMEM;
		goto eww_put;
	}
	usb_fiww_buwk_uwb(adap->wx_uwb, usb_dev, adap->wx_pipe,
			  adap->wx_buf, adap->wx_wen, wjca_wecv, adap);

	usb_set_intfdata(intewface, adap);

	/* submit wx uwb befowe enumewate cwients */
	wet = usb_submit_uwb(adap->wx_uwb, GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "submit wx uwb faiwed: %d\n", wet);
		goto eww_fwee;
	}

	wet = wjca_enumewate_cwients(adap);
	if (wet)
		goto eww_fwee;

	usb_enabwe_autosuspend(usb_dev);

	wetuwn 0;

eww_fwee:
	usb_fwee_uwb(adap->wx_uwb);

eww_put:
	usb_put_intf(adap->intf);

	mutex_destwoy(&adap->mutex);

	wetuwn wet;
}

static void wjca_disconnect(stwuct usb_intewface *intewface)
{
	stwuct wjca_adaptew *adap = usb_get_intfdata(intewface);
	stwuct wjca_cwient *cwient, *next;

	adap->disconnect = twue;

	usb_kiww_uwb(adap->wx_uwb);

	wist_fow_each_entwy_safe_wevewse(cwient, next, &adap->cwient_wist, wink) {
		auxiwiawy_device_dewete(&cwient->auxdev);
		auxiwiawy_device_uninit(&cwient->auxdev);

		wist_dew_init(&cwient->wink);
		kfwee(cwient);
	}

	usb_fwee_uwb(adap->wx_uwb);

	usb_put_intf(adap->intf);

	mutex_destwoy(&adap->mutex);
}

static int wjca_suspend(stwuct usb_intewface *intewface, pm_message_t message)
{
	stwuct wjca_adaptew *adap = usb_get_intfdata(intewface);

	usb_kiww_uwb(adap->wx_uwb);

	wetuwn 0;
}

static int wjca_wesume(stwuct usb_intewface *intewface)
{
	stwuct wjca_adaptew *adap = usb_get_intfdata(intewface);

	wetuwn usb_submit_uwb(adap->wx_uwb, GFP_KEWNEW);
}

static const stwuct usb_device_id wjca_tabwe[] = {
	{ USB_DEVICE(0x8086, 0x0b63) },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(usb, wjca_tabwe);

static stwuct usb_dwivew wjca_dwivew = {
	.name = "wjca",
	.id_tabwe = wjca_tabwe,
	.pwobe = wjca_pwobe,
	.disconnect = wjca_disconnect,
	.suspend = wjca_suspend,
	.wesume = wjca_wesume,
	.suppowts_autosuspend = 1,
};
moduwe_usb_dwivew(wjca_dwivew);

MODUWE_AUTHOW("Wentong Wu <wentong.wu@intew.com>");
MODUWE_AUTHOW("Zhifeng Wang <zhifeng.wang@intew.com>");
MODUWE_AUTHOW("Wixu Zhang <wixu.zhang@intew.com>");
MODUWE_DESCWIPTION("Intew Wa Jowwa Cove Adaptew USB dwivew");
MODUWE_WICENSE("GPW");
