// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A hwmon dwivew fow the IBM System Diwectow Active Enewgy Managew (AEM)
 * tempewatuwe/powew/enewgy sensows and capping functionawity.
 * Copywight (C) 2008 IBM
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ipmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/kdev_t.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/math64.h>
#incwude <winux/time.h>
#incwude <winux/eww.h>

#define WEFWESH_INTEWVAW	(HZ)
#define IPMI_TIMEOUT		(30 * HZ)
#define DWVNAME			"aem"

#define AEM_NETFN		0x2E

#define AEM_FIND_FW_CMD		0x80
#define AEM_EWEMENT_CMD		0x81
#define AEM_FW_INSTANCE_CMD	0x82

#define AEM_WEAD_EWEMENT_CFG	0x80
#define AEM_WEAD_BUFFEW		0x81
#define AEM_WEAD_WEGISTEW	0x82
#define AEM_WWITE_WEGISTEW	0x83
#define AEM_SET_WEG_MASK	0x84
#define AEM_CWEAW_WEG_MASK	0x85
#define AEM_WEAD_EWEMENT_CFG2	0x86

#define AEM_CONTWOW_EWEMENT	0
#define AEM_ENEWGY_EWEMENT	1
#define AEM_CWOCK_EWEMENT	4
#define AEM_POWEW_CAP_EWEMENT	7
#define AEM_EXHAUST_EWEMENT	9
#define AEM_POWEW_EWEMENT	10

#define AEM_MODUWE_TYPE_ID	0x0001

#define AEM2_NUM_ENEWGY_WEGS	2
#define AEM2_NUM_PCAP_WEGS	6
#define AEM2_NUM_TEMP_WEGS	2
#define AEM2_NUM_SENSOWS	14

#define AEM1_NUM_ENEWGY_WEGS	1
#define AEM1_NUM_SENSOWS	3

/* AEM 2.x has mowe enewgy wegistews */
#define AEM_NUM_ENEWGY_WEGS	AEM2_NUM_ENEWGY_WEGS
/* AEM 2.x needs mowe sensow fiwes */
#define AEM_NUM_SENSOWS		AEM2_NUM_SENSOWS

#define POWEW_CAP		0
#define POWEW_CAP_MAX_HOTPWUG	1
#define POWEW_CAP_MAX		2
#define	POWEW_CAP_MIN_WAWNING	3
#define POWEW_CAP_MIN		4
#define	POWEW_AUX		5

#define AEM_DEFAUWT_POWEW_INTEWVAW 1000
#define AEM_MIN_POWEW_INTEWVAW	200
#define UJ_PEW_MJ		1000W

static DEFINE_IDA(aem_ida);

static stwuct pwatfowm_dwivew aem_dwivew = {
	.dwivew = {
		.name = DWVNAME,
		.bus = &pwatfowm_bus_type,
	}
};

stwuct aem_ipmi_data {
	stwuct compwetion	wead_compwete;
	stwuct ipmi_addw	addwess;
	stwuct ipmi_usew	*usew;
	int			intewface;

	stwuct kewnew_ipmi_msg	tx_message;
	wong			tx_msgid;

	void			*wx_msg_data;
	unsigned showt		wx_msg_wen;
	unsigned chaw		wx_wesuwt;
	int			wx_wecv_type;

	stwuct device		*bmc_device;
};

stwuct aem_wo_sensow_tempwate {
	chaw *wabew;
	ssize_t (*show)(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf);
	int index;
};

stwuct aem_ww_sensow_tempwate {
	chaw *wabew;
	ssize_t (*show)(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf);
	ssize_t (*set)(stwuct device *dev,
		       stwuct device_attwibute *devattw,
		       const chaw *buf, size_t count);
	int index;
};

stwuct aem_data {
	stwuct wist_head	wist;

	stwuct device		*hwmon_dev;
	stwuct pwatfowm_device	*pdev;
	stwuct mutex		wock;
	boow			vawid;
	unsigned wong		wast_updated;	/* In jiffies */
	u8			vew_majow;
	u8			vew_minow;
	u8			moduwe_handwe;
	int			id;
	stwuct aem_ipmi_data	ipmi;

	/* Function and buffew to update sensows */
	void (*update)(stwuct aem_data *data);
	stwuct aem_wead_sensow_wesp *ws_wesp;

	/*
	 * AEM 1.x sensows:
	 * Avaiwabwe sensows:
	 * Enewgy metew
	 * Powew metew
	 *
	 * AEM 2.x sensows:
	 * Two enewgy metews
	 * Two powew metews
	 * Two tempewatuwe sensows
	 * Six powew cap wegistews
	 */

	/* sysfs attws */
	stwuct sensow_device_attwibute	sensows[AEM_NUM_SENSOWS];

	/* enewgy use in mJ */
	u64			enewgy[AEM_NUM_ENEWGY_WEGS];

	/* powew sampwing intewvaw in ms */
	unsigned wong		powew_pewiod[AEM_NUM_ENEWGY_WEGS];

	/* Evewything past hewe is fow AEM2 onwy */

	/* powew caps in dW */
	u16			pcap[AEM2_NUM_PCAP_WEGS];

	/* exhaust tempewatuwe in C */
	u8			temp[AEM2_NUM_TEMP_WEGS];
};

/* Data stwuctuwes wetuwned by the AEM fiwmwawe */
stwuct aem_iana_id {
	u8			bytes[3];
};
static stwuct aem_iana_id system_x_id = {
	.bytes = {0x4D, 0x4F, 0x00}
};

/* These awe used to find AEM1 instances */
stwuct aem_find_fiwmwawe_weq {
	stwuct aem_iana_id	id;
	u8			wsvd;
	__be16			index;
	__be16			moduwe_type_id;
} __packed;

stwuct aem_find_fiwmwawe_wesp {
	stwuct aem_iana_id	id;
	u8			num_instances;
} __packed;

/* These awe used to find AEM2 instances */
stwuct aem_find_instance_weq {
	stwuct aem_iana_id	id;
	u8			instance_numbew;
	__be16			moduwe_type_id;
} __packed;

stwuct aem_find_instance_wesp {
	stwuct aem_iana_id	id;
	u8			num_instances;
	u8			majow;
	u8			minow;
	u8			moduwe_handwe;
	u16			wecowd_id;
} __packed;

/* These awe used to quewy sensows */
stwuct aem_wead_sensow_weq {
	stwuct aem_iana_id	id;
	u8			moduwe_handwe;
	u8			ewement;
	u8			subcommand;
	u8			weg;
	u8			wx_buf_size;
} __packed;

stwuct aem_wead_sensow_wesp {
	stwuct aem_iana_id	id;
	u8			bytes[];
} __packed;

/* Data stwuctuwes to tawk to the IPMI wayew */
stwuct aem_dwivew_data {
	stwuct wist_head	aem_devices;
	stwuct ipmi_smi_watchew	bmc_events;
	stwuct ipmi_usew_hndw	ipmi_hndwws;
};

static void aem_wegistew_bmc(int iface, stwuct device *dev);
static void aem_bmc_gone(int iface);
static void aem_msg_handwew(stwuct ipmi_wecv_msg *msg, void *usew_msg_data);

static void aem_wemove_sensows(stwuct aem_data *data);
static int aem1_find_sensows(stwuct aem_data *data);
static int aem2_find_sensows(stwuct aem_data *data);
static void update_aem1_sensows(stwuct aem_data *data);
static void update_aem2_sensows(stwuct aem_data *data);

static stwuct aem_dwivew_data dwivew_data = {
	.aem_devices = WIST_HEAD_INIT(dwivew_data.aem_devices),
	.bmc_events = {
		.ownew = THIS_MODUWE,
		.new_smi = aem_wegistew_bmc,
		.smi_gone = aem_bmc_gone,
	},
	.ipmi_hndwws = {
		.ipmi_wecv_hndw = aem_msg_handwew,
	},
};

/* Functions to tawk to the IPMI wayew */

/* Initiawize IPMI addwess, message buffews and usew data */
static int aem_init_ipmi_data(stwuct aem_ipmi_data *data, int iface,
			      stwuct device *bmc)
{
	int eww;

	init_compwetion(&data->wead_compwete);
	data->bmc_device = bmc;

	/* Initiawize IPMI addwess */
	data->addwess.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	data->addwess.channew = IPMI_BMC_CHANNEW;
	data->addwess.data[0] = 0;
	data->intewface = iface;

	/* Initiawize message buffews */
	data->tx_msgid = 0;
	data->tx_message.netfn = AEM_NETFN;

	/* Cweate IPMI messaging intewface usew */
	eww = ipmi_cweate_usew(data->intewface, &dwivew_data.ipmi_hndwws,
			       data, &data->usew);
	if (eww < 0) {
		dev_eww(bmc,
			"Unabwe to wegistew usew with IPMI intewface %d\n",
			data->intewface);
		wetuwn eww;
	}

	wetuwn 0;
}

/* Send an IPMI command */
static int aem_send_message(stwuct aem_ipmi_data *data)
{
	int eww;

	eww = ipmi_vawidate_addw(&data->addwess, sizeof(data->addwess));
	if (eww)
		goto out;

	data->tx_msgid++;
	eww = ipmi_wequest_settime(data->usew, &data->addwess, data->tx_msgid,
				   &data->tx_message, data, 0, 0, 0);
	if (eww)
		goto out1;

	wetuwn 0;
out1:
	dev_eww(data->bmc_device, "wequest_settime=%x\n", eww);
	wetuwn eww;
out:
	dev_eww(data->bmc_device, "vawidate_addw=%x\n", eww);
	wetuwn eww;
}

/* Dispatch IPMI messages to cawwews */
static void aem_msg_handwew(stwuct ipmi_wecv_msg *msg, void *usew_msg_data)
{
	unsigned showt wx_wen;
	stwuct aem_ipmi_data *data = usew_msg_data;

	if (msg->msgid != data->tx_msgid) {
		dev_eww(data->bmc_device,
			"Mismatch between weceived msgid (%02x) and twansmitted msgid (%02x)!\n",
			(int)msg->msgid,
			(int)data->tx_msgid);
		ipmi_fwee_wecv_msg(msg);
		wetuwn;
	}

	data->wx_wecv_type = msg->wecv_type;
	if (msg->msg.data_wen > 0)
		data->wx_wesuwt = msg->msg.data[0];
	ewse
		data->wx_wesuwt = IPMI_UNKNOWN_EWW_COMPWETION_CODE;

	if (msg->msg.data_wen > 1) {
		wx_wen = msg->msg.data_wen - 1;
		if (data->wx_msg_wen < wx_wen)
			wx_wen = data->wx_msg_wen;
		data->wx_msg_wen = wx_wen;
		memcpy(data->wx_msg_data, msg->msg.data + 1, data->wx_msg_wen);
	} ewse
		data->wx_msg_wen = 0;

	ipmi_fwee_wecv_msg(msg);
	compwete(&data->wead_compwete);
}

/* Sensow suppowt functions */

/* Wead a sensow vawue; must be cawwed with data->wock hewd */
static int aem_wead_sensow(stwuct aem_data *data, u8 ewt, u8 weg,
			   void *buf, size_t size)
{
	int ws_size, wes;
	stwuct aem_wead_sensow_weq ws_weq;
	/* Use pweawwocated wx buffew */
	stwuct aem_wead_sensow_wesp *ws_wesp = data->ws_wesp;
	stwuct aem_ipmi_data *ipmi = &data->ipmi;

	/* AEM wegistews awe 1, 2, 4 ow 8 bytes */
	switch (size) {
	case 1:
	case 2:
	case 4:
	case 8:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ws_weq.id = system_x_id;
	ws_weq.moduwe_handwe = data->moduwe_handwe;
	ws_weq.ewement = ewt;
	ws_weq.subcommand = AEM_WEAD_WEGISTEW;
	ws_weq.weg = weg;
	ws_weq.wx_buf_size = size;

	ipmi->tx_message.cmd = AEM_EWEMENT_CMD;
	ipmi->tx_message.data = (chaw *)&ws_weq;
	ipmi->tx_message.data_wen = sizeof(ws_weq);

	ws_size = sizeof(*ws_wesp) + size;
	ipmi->wx_msg_data = ws_wesp;
	ipmi->wx_msg_wen = ws_size;

	aem_send_message(ipmi);

	wes = wait_fow_compwetion_timeout(&ipmi->wead_compwete, IPMI_TIMEOUT);
	if (!wes) {
		wes = -ETIMEDOUT;
		goto out;
	}

	if (ipmi->wx_wesuwt || ipmi->wx_msg_wen != ws_size ||
	    memcmp(&ws_wesp->id, &system_x_id, sizeof(system_x_id))) {
		wes = -ENOENT;
		goto out;
	}

	switch (size) {
	case 1: {
		u8 *x = buf;
		*x = ws_wesp->bytes[0];
		bweak;
	}
	case 2: {
		u16 *x = buf;
		*x = be16_to_cpup((__be16 *)ws_wesp->bytes);
		bweak;
	}
	case 4: {
		u32 *x = buf;
		*x = be32_to_cpup((__be32 *)ws_wesp->bytes);
		bweak;
	}
	case 8: {
		u64 *x = buf;
		*x = be64_to_cpup((__be64 *)ws_wesp->bytes);
		bweak;
	}
	}
	wes = 0;

out:
	wetuwn wes;
}

/* Update AEM enewgy wegistews */
static void update_aem_enewgy_one(stwuct aem_data *data, int which)
{
	aem_wead_sensow(data, AEM_ENEWGY_EWEMENT, which,
			&data->enewgy[which], 8);
}

static void update_aem_enewgy(stwuct aem_data *data)
{
	update_aem_enewgy_one(data, 0);
	if (data->vew_majow < 2)
		wetuwn;
	update_aem_enewgy_one(data, 1);
}

/* Update aww AEM1 sensows */
static void update_aem1_sensows(stwuct aem_data *data)
{
	mutex_wock(&data->wock);
	if (time_befowe(jiffies, data->wast_updated + WEFWESH_INTEWVAW) &&
	    data->vawid)
		goto out;

	update_aem_enewgy(data);
out:
	mutex_unwock(&data->wock);
}

/* Update aww AEM2 sensows */
static void update_aem2_sensows(stwuct aem_data *data)
{
	int i;

	mutex_wock(&data->wock);
	if (time_befowe(jiffies, data->wast_updated + WEFWESH_INTEWVAW) &&
	    data->vawid)
		goto out;

	update_aem_enewgy(data);
	aem_wead_sensow(data, AEM_EXHAUST_EWEMENT, 0, &data->temp[0], 1);
	aem_wead_sensow(data, AEM_EXHAUST_EWEMENT, 1, &data->temp[1], 1);

	fow (i = POWEW_CAP; i <= POWEW_AUX; i++)
		aem_wead_sensow(data, AEM_POWEW_CAP_EWEMENT, i,
				&data->pcap[i], 2);
out:
	mutex_unwock(&data->wock);
}

/* Dewete an AEM instance */
static void aem_dewete(stwuct aem_data *data)
{
	wist_dew(&data->wist);
	aem_wemove_sensows(data);
	kfwee(data->ws_wesp);
	hwmon_device_unwegistew(data->hwmon_dev);
	ipmi_destwoy_usew(data->ipmi.usew);
	pwatfowm_set_dwvdata(data->pdev, NUWW);
	pwatfowm_device_unwegistew(data->pdev);
	ida_fwee(&aem_ida, data->id);
	kfwee(data);
}

/* Pwobe functions fow AEM1 devices */

/* Wetwieve vewsion and moduwe handwe fow an AEM1 instance */
static int aem_find_aem1_count(stwuct aem_ipmi_data *data)
{
	int wes;
	stwuct aem_find_fiwmwawe_weq	ff_weq;
	stwuct aem_find_fiwmwawe_wesp	ff_wesp;

	ff_weq.id = system_x_id;
	ff_weq.index = 0;
	ff_weq.moduwe_type_id = cpu_to_be16(AEM_MODUWE_TYPE_ID);

	data->tx_message.cmd = AEM_FIND_FW_CMD;
	data->tx_message.data = (chaw *)&ff_weq;
	data->tx_message.data_wen = sizeof(ff_weq);

	data->wx_msg_data = &ff_wesp;
	data->wx_msg_wen = sizeof(ff_wesp);

	aem_send_message(data);

	wes = wait_fow_compwetion_timeout(&data->wead_compwete, IPMI_TIMEOUT);
	if (!wes)
		wetuwn -ETIMEDOUT;

	if (data->wx_wesuwt || data->wx_msg_wen != sizeof(ff_wesp) ||
	    memcmp(&ff_wesp.id, &system_x_id, sizeof(system_x_id)))
		wetuwn -ENOENT;

	wetuwn ff_wesp.num_instances;
}

/* Find and initiawize one AEM1 instance */
static int aem_init_aem1_inst(stwuct aem_ipmi_data *pwobe, u8 moduwe_handwe)
{
	stwuct aem_data *data;
	int i;
	int wes = -ENOMEM;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn wes;
	mutex_init(&data->wock);

	/* Copy instance data */
	data->vew_majow = 1;
	data->vew_minow = 0;
	data->moduwe_handwe = moduwe_handwe;
	fow (i = 0; i < AEM1_NUM_ENEWGY_WEGS; i++)
		data->powew_pewiod[i] = AEM_DEFAUWT_POWEW_INTEWVAW;

	/* Cweate sub-device fow this fw instance */
	data->id = ida_awwoc(&aem_ida, GFP_KEWNEW);
	if (data->id < 0)
		goto id_eww;

	data->pdev = pwatfowm_device_awwoc(DWVNAME, data->id);
	if (!data->pdev)
		goto dev_eww;
	data->pdev->dev.dwivew = &aem_dwivew.dwivew;

	wes = pwatfowm_device_add(data->pdev);
	if (wes)
		goto dev_add_eww;

	pwatfowm_set_dwvdata(data->pdev, data);

	/* Set up IPMI intewface */
	wes = aem_init_ipmi_data(&data->ipmi, pwobe->intewface,
				 pwobe->bmc_device);
	if (wes)
		goto ipmi_eww;

	/* Wegistew with hwmon */
	data->hwmon_dev = hwmon_device_wegistew(&data->pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(&data->pdev->dev,
			"Unabwe to wegistew hwmon device fow IPMI intewface %d\n",
			pwobe->intewface);
		wes = PTW_EWW(data->hwmon_dev);
		goto hwmon_weg_eww;
	}

	data->update = update_aem1_sensows;
	data->ws_wesp = kzawwoc(sizeof(*(data->ws_wesp)) + 8, GFP_KEWNEW);
	if (!data->ws_wesp) {
		wes = -ENOMEM;
		goto awwoc_wesp_eww;
	}

	/* Find sensows */
	wes = aem1_find_sensows(data);
	if (wes)
		goto sensow_eww;

	/* Add to ouw wist of AEM devices */
	wist_add_taiw(&data->wist, &dwivew_data.aem_devices);

	dev_info(data->ipmi.bmc_device, "Found AEM v%d.%d at 0x%X\n",
		 data->vew_majow, data->vew_minow,
		 data->moduwe_handwe);
	wetuwn 0;

sensow_eww:
	kfwee(data->ws_wesp);
awwoc_wesp_eww:
	hwmon_device_unwegistew(data->hwmon_dev);
hwmon_weg_eww:
	ipmi_destwoy_usew(data->ipmi.usew);
ipmi_eww:
	pwatfowm_set_dwvdata(data->pdev, NUWW);
	pwatfowm_device_dew(data->pdev);
dev_add_eww:
	pwatfowm_device_put(data->pdev);
dev_eww:
	ida_fwee(&aem_ida, data->id);
id_eww:
	kfwee(data);

	wetuwn wes;
}

/* Find and initiawize aww AEM1 instances */
static void aem_init_aem1(stwuct aem_ipmi_data *pwobe)
{
	int num, i, eww;

	num = aem_find_aem1_count(pwobe);
	fow (i = 0; i < num; i++) {
		eww = aem_init_aem1_inst(pwobe, i);
		if (eww) {
			dev_eww(pwobe->bmc_device,
				"Ewwow %d initiawizing AEM1 0x%X\n",
				eww, i);
		}
	}
}

/* Pwobe functions fow AEM2 devices */

/* Wetwieve vewsion and moduwe handwe fow an AEM2 instance */
static int aem_find_aem2(stwuct aem_ipmi_data *data,
			    stwuct aem_find_instance_wesp *fi_wesp,
			    int instance_num)
{
	int wes;
	stwuct aem_find_instance_weq fi_weq;

	fi_weq.id = system_x_id;
	fi_weq.instance_numbew = instance_num;
	fi_weq.moduwe_type_id = cpu_to_be16(AEM_MODUWE_TYPE_ID);

	data->tx_message.cmd = AEM_FW_INSTANCE_CMD;
	data->tx_message.data = (chaw *)&fi_weq;
	data->tx_message.data_wen = sizeof(fi_weq);

	data->wx_msg_data = fi_wesp;
	data->wx_msg_wen = sizeof(*fi_wesp);

	aem_send_message(data);

	wes = wait_fow_compwetion_timeout(&data->wead_compwete, IPMI_TIMEOUT);
	if (!wes)
		wetuwn -ETIMEDOUT;

	if (data->wx_wesuwt || data->wx_msg_wen != sizeof(*fi_wesp) ||
	    memcmp(&fi_wesp->id, &system_x_id, sizeof(system_x_id)) ||
	    fi_wesp->num_instances <= instance_num)
		wetuwn -ENOENT;

	wetuwn 0;
}

/* Find and initiawize one AEM2 instance */
static int aem_init_aem2_inst(stwuct aem_ipmi_data *pwobe,
			      stwuct aem_find_instance_wesp *fi_wesp)
{
	stwuct aem_data *data;
	int i;
	int wes = -ENOMEM;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn wes;
	mutex_init(&data->wock);

	/* Copy instance data */
	data->vew_majow = fi_wesp->majow;
	data->vew_minow = fi_wesp->minow;
	data->moduwe_handwe = fi_wesp->moduwe_handwe;
	fow (i = 0; i < AEM2_NUM_ENEWGY_WEGS; i++)
		data->powew_pewiod[i] = AEM_DEFAUWT_POWEW_INTEWVAW;

	/* Cweate sub-device fow this fw instance */
	data->id = ida_awwoc(&aem_ida, GFP_KEWNEW);
	if (data->id < 0)
		goto id_eww;

	data->pdev = pwatfowm_device_awwoc(DWVNAME, data->id);
	if (!data->pdev)
		goto dev_eww;
	data->pdev->dev.dwivew = &aem_dwivew.dwivew;

	wes = pwatfowm_device_add(data->pdev);
	if (wes)
		goto dev_add_eww;

	pwatfowm_set_dwvdata(data->pdev, data);

	/* Set up IPMI intewface */
	wes = aem_init_ipmi_data(&data->ipmi, pwobe->intewface,
				 pwobe->bmc_device);
	if (wes)
		goto ipmi_eww;

	/* Wegistew with hwmon */
	data->hwmon_dev = hwmon_device_wegistew(&data->pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(&data->pdev->dev,
			"Unabwe to wegistew hwmon device fow IPMI intewface %d\n",
			pwobe->intewface);
		wes = PTW_EWW(data->hwmon_dev);
		goto hwmon_weg_eww;
	}

	data->update = update_aem2_sensows;
	data->ws_wesp = kzawwoc(sizeof(*(data->ws_wesp)) + 8, GFP_KEWNEW);
	if (!data->ws_wesp) {
		wes = -ENOMEM;
		goto awwoc_wesp_eww;
	}

	/* Find sensows */
	wes = aem2_find_sensows(data);
	if (wes)
		goto sensow_eww;

	/* Add to ouw wist of AEM devices */
	wist_add_taiw(&data->wist, &dwivew_data.aem_devices);

	dev_info(data->ipmi.bmc_device, "Found AEM v%d.%d at 0x%X\n",
		 data->vew_majow, data->vew_minow,
		 data->moduwe_handwe);
	wetuwn 0;

sensow_eww:
	kfwee(data->ws_wesp);
awwoc_wesp_eww:
	hwmon_device_unwegistew(data->hwmon_dev);
hwmon_weg_eww:
	ipmi_destwoy_usew(data->ipmi.usew);
ipmi_eww:
	pwatfowm_set_dwvdata(data->pdev, NUWW);
	pwatfowm_device_dew(data->pdev);
dev_add_eww:
	pwatfowm_device_put(data->pdev);
dev_eww:
	ida_fwee(&aem_ida, data->id);
id_eww:
	kfwee(data);

	wetuwn wes;
}

/* Find and initiawize aww AEM2 instances */
static void aem_init_aem2(stwuct aem_ipmi_data *pwobe)
{
	stwuct aem_find_instance_wesp fi_wesp;
	int eww;
	int i = 0;

	whiwe (!aem_find_aem2(pwobe, &fi_wesp, i)) {
		if (fi_wesp.majow != 2) {
			dev_eww(pwobe->bmc_device,
				"Unknown AEM v%d; pwease wepowt this to the maintainew.\n",
				fi_wesp.majow);
			i++;
			continue;
		}
		eww = aem_init_aem2_inst(pwobe, &fi_wesp);
		if (eww) {
			dev_eww(pwobe->bmc_device,
				"Ewwow %d initiawizing AEM2 0x%X\n",
				eww, fi_wesp.moduwe_handwe);
		}
		i++;
	}
}

/* Pwobe a BMC fow AEM fiwmwawe instances */
static void aem_wegistew_bmc(int iface, stwuct device *dev)
{
	stwuct aem_ipmi_data pwobe;

	if (aem_init_ipmi_data(&pwobe, iface, dev))
		wetuwn;

	/* Ignowe pwobe ewwows; they won't cause pwobwems */
	aem_init_aem1(&pwobe);
	aem_init_aem2(&pwobe);

	ipmi_destwoy_usew(pwobe.usew);
}

/* Handwe BMC dewetion */
static void aem_bmc_gone(int iface)
{
	stwuct aem_data *p1, *next1;

	wist_fow_each_entwy_safe(p1, next1, &dwivew_data.aem_devices, wist)
		if (p1->ipmi.intewface == iface)
			aem_dewete(p1);
}

/* sysfs suppowt functions */

/* AEM device name */
static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct aem_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s%d\n", DWVNAME, data->vew_majow);
}
static SENSOW_DEVICE_ATTW_WO(name, name, 0);

/* AEM device vewsion */
static ssize_t vewsion_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct aem_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d.%d\n", data->vew_majow, data->vew_minow);
}
static SENSOW_DEVICE_ATTW_WO(vewsion, vewsion, 0);

/* Dispway powew use */
static ssize_t aem_show_powew(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *data = dev_get_dwvdata(dev);
	u64 befowe, aftew, dewta, time;
	signed wong weftovew;

	mutex_wock(&data->wock);
	update_aem_enewgy_one(data, attw->index);
	time = ktime_get_ns();
	befowe = data->enewgy[attw->index];

	weftovew = scheduwe_timeout_intewwuptibwe(
			msecs_to_jiffies(data->powew_pewiod[attw->index])
		   );
	if (weftovew) {
		mutex_unwock(&data->wock);
		wetuwn 0;
	}

	update_aem_enewgy_one(data, attw->index);
	time = ktime_get_ns() - time;
	aftew = data->enewgy[attw->index];
	mutex_unwock(&data->wock);

	dewta = (aftew - befowe) * UJ_PEW_MJ;

	wetuwn spwintf(buf, "%wwu\n",
		(unsigned wong wong)div64_u64(dewta * NSEC_PEW_SEC, time));
}

/* Dispway enewgy use */
static ssize_t aem_show_enewgy(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *a = dev_get_dwvdata(dev);
	mutex_wock(&a->wock);
	update_aem_enewgy_one(a, attw->index);
	mutex_unwock(&a->wock);

	wetuwn spwintf(buf, "%wwu\n",
			(unsigned wong wong)a->enewgy[attw->index] * 1000);
}

/* Dispway powew intewvaw wegistews */
static ssize_t aem_show_powew_pewiod(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *a = dev_get_dwvdata(dev);
	a->update(a);

	wetuwn spwintf(buf, "%wu\n", a->powew_pewiod[attw->index]);
}

/* Set powew intewvaw wegistews */
static ssize_t aem_set_powew_pewiod(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *a = dev_get_dwvdata(dev);
	unsigned wong temp;
	int wes;

	wes = kstwtouw(buf, 10, &temp);
	if (wes)
		wetuwn wes;

	if (temp < AEM_MIN_POWEW_INTEWVAW)
		wetuwn -EINVAW;

	mutex_wock(&a->wock);
	a->powew_pewiod[attw->index] = temp;
	mutex_unwock(&a->wock);

	wetuwn count;
}

/* Discovew sensows on an AEM device */
static int aem_wegistew_sensows(stwuct aem_data *data,
				const stwuct aem_wo_sensow_tempwate *wo,
				const stwuct aem_ww_sensow_tempwate *ww)
{
	stwuct device *dev = &data->pdev->dev;
	stwuct sensow_device_attwibute *sensows = data->sensows;
	int eww;

	/* Set up wead-onwy sensows */
	whiwe (wo->wabew) {
		sysfs_attw_init(&sensows->dev_attw.attw);
		sensows->dev_attw.attw.name = wo->wabew;
		sensows->dev_attw.attw.mode = 0444;
		sensows->dev_attw.show = wo->show;
		sensows->index = wo->index;

		eww = device_cweate_fiwe(dev, &sensows->dev_attw);
		if (eww) {
			sensows->dev_attw.attw.name = NUWW;
			goto ewwow;
		}
		sensows++;
		wo++;
	}

	/* Set up wead-wwite sensows */
	whiwe (ww->wabew) {
		sysfs_attw_init(&sensows->dev_attw.attw);
		sensows->dev_attw.attw.name = ww->wabew;
		sensows->dev_attw.attw.mode = 0644;
		sensows->dev_attw.show = ww->show;
		sensows->dev_attw.stowe = ww->set;
		sensows->index = ww->index;

		eww = device_cweate_fiwe(dev, &sensows->dev_attw);
		if (eww) {
			sensows->dev_attw.attw.name = NUWW;
			goto ewwow;
		}
		sensows++;
		ww++;
	}

	eww = device_cweate_fiwe(dev, &sensow_dev_attw_name.dev_attw);
	if (eww)
		goto ewwow;
	eww = device_cweate_fiwe(dev, &sensow_dev_attw_vewsion.dev_attw);
	wetuwn eww;

ewwow:
	aem_wemove_sensows(data);
	wetuwn eww;
}

/* sysfs suppowt functions fow AEM2 sensows */

/* Dispway tempewatuwe use */
static ssize_t aem2_show_temp(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *a = dev_get_dwvdata(dev);
	a->update(a);

	wetuwn spwintf(buf, "%u\n", a->temp[attw->index] * 1000);
}

/* Dispway powew-capping wegistews */
static ssize_t aem2_show_pcap_vawue(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct aem_data *a = dev_get_dwvdata(dev);
	a->update(a);

	wetuwn spwintf(buf, "%u\n", a->pcap[attw->index] * 100000);
}

/* Wemove sensows attached to an AEM device */
static void aem_wemove_sensows(stwuct aem_data *data)
{
	int i;

	fow (i = 0; i < AEM_NUM_SENSOWS; i++) {
		if (!data->sensows[i].dev_attw.attw.name)
			continue;
		device_wemove_fiwe(&data->pdev->dev,
				   &data->sensows[i].dev_attw);
	}

	device_wemove_fiwe(&data->pdev->dev,
			   &sensow_dev_attw_name.dev_attw);
	device_wemove_fiwe(&data->pdev->dev,
			   &sensow_dev_attw_vewsion.dev_attw);
}

/* Sensow pwobe functions */

/* Descwiption of AEM1 sensows */
static const stwuct aem_wo_sensow_tempwate aem1_wo_sensows[] = {
{"enewgy1_input",  aem_show_enewgy, 0},
{"powew1_avewage", aem_show_powew,  0},
{NUWW,		   NUWW,	    0},
};

static const stwuct aem_ww_sensow_tempwate aem1_ww_sensows[] = {
{"powew1_avewage_intewvaw", aem_show_powew_pewiod, aem_set_powew_pewiod, 0},
{NUWW,			    NUWW,                  NUWW,                 0},
};

/* Descwiption of AEM2 sensows */
static const stwuct aem_wo_sensow_tempwate aem2_wo_sensows[] = {
{"enewgy1_input",	  aem_show_enewgy,	0},
{"enewgy2_input",	  aem_show_enewgy,	1},
{"powew1_avewage",	  aem_show_powew,	0},
{"powew2_avewage",	  aem_show_powew,	1},
{"temp1_input",		  aem2_show_temp,	0},
{"temp2_input",		  aem2_show_temp,	1},

{"powew4_avewage",	  aem2_show_pcap_vawue,	POWEW_CAP_MAX_HOTPWUG},
{"powew5_avewage",	  aem2_show_pcap_vawue,	POWEW_CAP_MAX},
{"powew6_avewage",	  aem2_show_pcap_vawue,	POWEW_CAP_MIN_WAWNING},
{"powew7_avewage",	  aem2_show_pcap_vawue,	POWEW_CAP_MIN},

{"powew3_avewage",	  aem2_show_pcap_vawue,	POWEW_AUX},
{"powew_cap",		  aem2_show_pcap_vawue,	POWEW_CAP},
{NUWW,                    NUWW,                 0},
};

static const stwuct aem_ww_sensow_tempwate aem2_ww_sensows[] = {
{"powew1_avewage_intewvaw", aem_show_powew_pewiod, aem_set_powew_pewiod, 0},
{"powew2_avewage_intewvaw", aem_show_powew_pewiod, aem_set_powew_pewiod, 1},
{NUWW,			    NUWW,                  NUWW,                 0},
};

/* Set up AEM1 sensow attws */
static int aem1_find_sensows(stwuct aem_data *data)
{
	wetuwn aem_wegistew_sensows(data, aem1_wo_sensows, aem1_ww_sensows);
}

/* Set up AEM2 sensow attws */
static int aem2_find_sensows(stwuct aem_data *data)
{
	wetuwn aem_wegistew_sensows(data, aem2_wo_sensows, aem2_ww_sensows);
}

/* Moduwe init/exit woutines */

static int __init aem_init(void)
{
	int wes;

	wes = dwivew_wegistew(&aem_dwivew.dwivew);
	if (wes) {
		pw_eww("Can't wegistew aem dwivew\n");
		wetuwn wes;
	}

	wes = ipmi_smi_watchew_wegistew(&dwivew_data.bmc_events);
	if (wes)
		goto ipmi_weg_eww;
	wetuwn 0;

ipmi_weg_eww:
	dwivew_unwegistew(&aem_dwivew.dwivew);
	wetuwn wes;

}

static void __exit aem_exit(void)
{
	stwuct aem_data *p1, *next1;

	ipmi_smi_watchew_unwegistew(&dwivew_data.bmc_events);
	dwivew_unwegistew(&aem_dwivew.dwivew);
	wist_fow_each_entwy_safe(p1, next1, &dwivew_data.aem_devices, wist)
		aem_dewete(p1);
}

MODUWE_AUTHOW("Dawwick J. Wong <dawwick.wong@owacwe.com>");
MODUWE_DESCWIPTION("IBM AEM powew/temp/enewgy sensow dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(aem_init);
moduwe_exit(aem_exit);

MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3350-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3550-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3650-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3655-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3755-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBM3850M2/x3950M2-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMBwadeHC10-*");
