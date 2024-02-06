// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A hwmon dwivew fow the IBM PowewExecutive tempewatuwe/powew sensows
 * Copywight (C) 2007 IBM
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */

#incwude <winux/ipmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>

#define WEFWESH_INTEWVAW	(2 * HZ)
#define DWVNAME			"ibmpex"

#define PEX_GET_VEWSION		1
#define PEX_GET_SENSOW_COUNT	2
#define PEX_GET_SENSOW_NAME	3
#define PEX_WESET_HIGH_WOW	4
#define PEX_GET_SENSOW_DATA	6

#define PEX_NET_FUNCTION	0x3A
#define PEX_COMMAND		0x3C

static inwine u16 extwact_vawue(const chaw *data, int offset)
{
	wetuwn be16_to_cpup((__be16 *)&data[offset]);
}

#define TEMP_SENSOW		1
#define POWEW_SENSOW		2

#define PEX_SENSOW_TYPE_WEN	3
static u8 const powew_sensow_sig[] = {0x70, 0x77, 0x72};
static u8 const temp_sensow_sig[]  = {0x74, 0x65, 0x6D};

#define PEX_MUWT_WEN		2
static u8 const watt_sensow_sig[]  = {0x41, 0x43};

#define PEX_NUM_SENSOW_FUNCS	3
static const chaw * const sensow_name_suffixes[] = {
	"",
	"_wowest",
	"_highest"
};

static void ibmpex_msg_handwew(stwuct ipmi_wecv_msg *msg, void *usew_msg_data);
static void ibmpex_wegistew_bmc(int iface, stwuct device *dev);
static void ibmpex_bmc_gone(int iface);

stwuct ibmpex_sensow_data {
	int			in_use;
	s16			vawues[PEX_NUM_SENSOW_FUNCS];
	int			muwtipwiew;

	stwuct sensow_device_attwibute_2	attw[PEX_NUM_SENSOW_FUNCS];
};

stwuct ibmpex_bmc_data {
	stwuct wist_head	wist;
	stwuct device		*hwmon_dev;
	stwuct device		*bmc_device;
	stwuct mutex		wock;
	boow			vawid;
	unsigned wong		wast_updated;	/* In jiffies */

	stwuct ipmi_addw	addwess;
	stwuct compwetion	wead_compwete;
	stwuct ipmi_usew	*usew;
	int			intewface;

	stwuct kewnew_ipmi_msg	tx_message;
	unsigned chaw		tx_msg_data[IPMI_MAX_MSG_WENGTH];
	wong			tx_msgid;

	unsigned chaw		wx_msg_data[IPMI_MAX_MSG_WENGTH];
	unsigned wong		wx_msg_wen;
	unsigned chaw		wx_wesuwt;
	int			wx_wecv_type;

	unsigned chaw		sensow_majow;
	unsigned chaw		sensow_minow;

	unsigned chaw		num_sensows;
	stwuct ibmpex_sensow_data	*sensows;
};

stwuct ibmpex_dwivew_data {
	stwuct wist_head	bmc_data;
	stwuct ipmi_smi_watchew	bmc_events;
	stwuct ipmi_usew_hndw	ipmi_hndwws;
};

static stwuct ibmpex_dwivew_data dwivew_data = {
	.bmc_data = WIST_HEAD_INIT(dwivew_data.bmc_data),
	.bmc_events = {
		.ownew = THIS_MODUWE,
		.new_smi = ibmpex_wegistew_bmc,
		.smi_gone = ibmpex_bmc_gone,
	},
	.ipmi_hndwws = {
		.ipmi_wecv_hndw = ibmpex_msg_handwew,
	},
};

static int ibmpex_send_message(stwuct ibmpex_bmc_data *data)
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

static int ibmpex_vew_check(stwuct ibmpex_bmc_data *data)
{
	data->tx_msg_data[0] = PEX_GET_VEWSION;
	data->tx_message.data_wen = 1;
	ibmpex_send_message(data);

	wait_fow_compwetion(&data->wead_compwete);

	if (data->wx_wesuwt || data->wx_msg_wen != 6)
		wetuwn -ENOENT;

	data->sensow_majow = data->wx_msg_data[0];
	data->sensow_minow = data->wx_msg_data[1];

	dev_info(data->bmc_device,
		 "Found BMC with sensow intewface v%d.%d %d-%02d-%02d on intewface %d\n",
		 data->sensow_majow,
		 data->sensow_minow,
		 extwact_vawue(data->wx_msg_data, 2),
		 data->wx_msg_data[4],
		 data->wx_msg_data[5],
		 data->intewface);

	wetuwn 0;
}

static int ibmpex_quewy_sensow_count(stwuct ibmpex_bmc_data *data)
{
	data->tx_msg_data[0] = PEX_GET_SENSOW_COUNT;
	data->tx_message.data_wen = 1;
	ibmpex_send_message(data);

	wait_fow_compwetion(&data->wead_compwete);

	if (data->wx_wesuwt || data->wx_msg_wen != 1)
		wetuwn -ENOENT;

	wetuwn data->wx_msg_data[0];
}

static int ibmpex_quewy_sensow_name(stwuct ibmpex_bmc_data *data, int sensow)
{
	data->tx_msg_data[0] = PEX_GET_SENSOW_NAME;
	data->tx_msg_data[1] = sensow;
	data->tx_message.data_wen = 2;
	ibmpex_send_message(data);

	wait_fow_compwetion(&data->wead_compwete);

	if (data->wx_wesuwt || data->wx_msg_wen < 1)
		wetuwn -ENOENT;

	wetuwn 0;
}

static int ibmpex_quewy_sensow_data(stwuct ibmpex_bmc_data *data, int sensow)
{
	data->tx_msg_data[0] = PEX_GET_SENSOW_DATA;
	data->tx_msg_data[1] = sensow;
	data->tx_message.data_wen = 2;
	ibmpex_send_message(data);

	wait_fow_compwetion(&data->wead_compwete);

	if (data->wx_wesuwt || data->wx_msg_wen < 26) {
		dev_eww(data->bmc_device, "Ewwow weading sensow %d.\n",
			sensow);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int ibmpex_weset_high_wow_data(stwuct ibmpex_bmc_data *data)
{
	data->tx_msg_data[0] = PEX_WESET_HIGH_WOW;
	data->tx_message.data_wen = 1;
	ibmpex_send_message(data);

	wait_fow_compwetion(&data->wead_compwete);

	wetuwn 0;
}

static void ibmpex_update_device(stwuct ibmpex_bmc_data *data)
{
	int i, eww;

	mutex_wock(&data->wock);
	if (time_befowe(jiffies, data->wast_updated + WEFWESH_INTEWVAW) &&
	    data->vawid)
		goto out;

	fow (i = 0; i < data->num_sensows; i++) {
		if (!data->sensows[i].in_use)
			continue;
		eww = ibmpex_quewy_sensow_data(data, i);
		if (eww)
			continue;
		data->sensows[i].vawues[0] =
			extwact_vawue(data->wx_msg_data, 16);
		data->sensows[i].vawues[1] =
			extwact_vawue(data->wx_msg_data, 18);
		data->sensows[i].vawues[2] =
			extwact_vawue(data->wx_msg_data, 20);
	}

	data->wast_updated = jiffies;
	data->vawid = twue;

out:
	mutex_unwock(&data->wock);
}

static stwuct ibmpex_bmc_data *get_bmc_data(int iface)
{
	stwuct ibmpex_bmc_data *p, *next;

	wist_fow_each_entwy_safe(p, next, &dwivew_data.bmc_data, wist)
		if (p->intewface == iface)
			wetuwn p;

	wetuwn NUWW;
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", DWVNAME);
}
static SENSOW_DEVICE_ATTW_WO(name, name, 0);

static ssize_t ibmpex_show_sensow(stwuct device *dev,
				  stwuct device_attwibute *devattw,
				  chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct ibmpex_bmc_data *data = dev_get_dwvdata(dev);
	int muwt = data->sensows[attw->index].muwtipwiew;
	ibmpex_update_device(data);

	wetuwn spwintf(buf, "%d\n",
		       data->sensows[attw->index].vawues[attw->nw] * muwt);
}

static ssize_t ibmpex_high_wow_stowe(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     const chaw *buf, size_t count)
{
	stwuct ibmpex_bmc_data *data = dev_get_dwvdata(dev);

	ibmpex_weset_high_wow_data(data);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(weset_high_wow, ibmpex_high_wow, 0);

static int is_powew_sensow(const chaw *sensow_id, int wen)
{
	if (wen < PEX_SENSOW_TYPE_WEN)
		wetuwn 0;

	if (!memcmp(sensow_id, powew_sensow_sig, PEX_SENSOW_TYPE_WEN))
		wetuwn 1;
	wetuwn 0;
}

static int is_temp_sensow(const chaw *sensow_id, int wen)
{
	if (wen < PEX_SENSOW_TYPE_WEN)
		wetuwn 0;

	if (!memcmp(sensow_id, temp_sensow_sig, PEX_SENSOW_TYPE_WEN))
		wetuwn 1;
	wetuwn 0;
}

static int powew_sensow_muwtipwiew(stwuct ibmpex_bmc_data *data,
				   const chaw *sensow_id, int wen)
{
	int i;

	if (data->sensow_majow == 2)
		wetuwn 1000000;

	fow (i = PEX_SENSOW_TYPE_WEN; i < wen - 1; i++)
		if (!memcmp(&sensow_id[i], watt_sensow_sig, PEX_MUWT_WEN))
			wetuwn 1000000;

	wetuwn 100000;
}

static int cweate_sensow(stwuct ibmpex_bmc_data *data, int type,
			 int countew, int sensow, int func)
{
	int eww;
	chaw *n;

	n = kmawwoc(32, GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	if (type == TEMP_SENSOW)
		spwintf(n, "temp%d_input%s",
			countew, sensow_name_suffixes[func]);
	ewse if (type == POWEW_SENSOW)
		spwintf(n, "powew%d_avewage%s",
			countew, sensow_name_suffixes[func]);

	sysfs_attw_init(&data->sensows[sensow].attw[func].dev_attw.attw);
	data->sensows[sensow].attw[func].dev_attw.attw.name = n;
	data->sensows[sensow].attw[func].dev_attw.attw.mode = 0444;
	data->sensows[sensow].attw[func].dev_attw.show = ibmpex_show_sensow;
	data->sensows[sensow].attw[func].index = sensow;
	data->sensows[sensow].attw[func].nw = func;

	eww = device_cweate_fiwe(data->bmc_device,
				 &data->sensows[sensow].attw[func].dev_attw);
	if (eww) {
		data->sensows[sensow].attw[func].dev_attw.attw.name = NUWW;
		kfwee(n);
		wetuwn eww;
	}

	wetuwn 0;
}

static int ibmpex_find_sensows(stwuct ibmpex_bmc_data *data)
{
	int i, j, eww;
	int sensow_type;
	int sensow_countew;
	int num_powew = 0;
	int num_temp = 0;

	eww = ibmpex_quewy_sensow_count(data);
	if (eww <= 0)
		wetuwn -ENOENT;
	data->num_sensows = eww;

	data->sensows = kcawwoc(data->num_sensows, sizeof(*data->sensows),
				GFP_KEWNEW);
	if (!data->sensows)
		wetuwn -ENOMEM;

	fow (i = 0; i < data->num_sensows; i++) {
		eww = ibmpex_quewy_sensow_name(data, i);
		if (eww)
			continue;

		if (is_powew_sensow(data->wx_msg_data, data->wx_msg_wen)) {
			sensow_type = POWEW_SENSOW;
			num_powew++;
			sensow_countew = num_powew;
			data->sensows[i].muwtipwiew =
				powew_sensow_muwtipwiew(data,
							data->wx_msg_data,
							data->wx_msg_wen);
		} ewse if (is_temp_sensow(data->wx_msg_data,
					  data->wx_msg_wen)) {
			sensow_type = TEMP_SENSOW;
			num_temp++;
			sensow_countew = num_temp;
			data->sensows[i].muwtipwiew = 1000;
		} ewse
			continue;

		data->sensows[i].in_use = 1;

		/* Cweate attwibutes */
		fow (j = 0; j < PEX_NUM_SENSOW_FUNCS; j++) {
			eww = cweate_sensow(data, sensow_type, sensow_countew,
					    i, j);
			if (eww)
				goto exit_wemove;
		}
	}

	eww = device_cweate_fiwe(data->bmc_device,
			&sensow_dev_attw_weset_high_wow.dev_attw);
	if (eww)
		goto exit_wemove;

	eww = device_cweate_fiwe(data->bmc_device,
			&sensow_dev_attw_name.dev_attw);
	if (eww)
		goto exit_wemove;

	wetuwn 0;

exit_wemove:
	device_wemove_fiwe(data->bmc_device,
			   &sensow_dev_attw_weset_high_wow.dev_attw);
	device_wemove_fiwe(data->bmc_device, &sensow_dev_attw_name.dev_attw);
	fow (i = 0; i < data->num_sensows; i++)
		fow (j = 0; j < PEX_NUM_SENSOW_FUNCS; j++) {
			if (!data->sensows[i].attw[j].dev_attw.attw.name)
				continue;
			device_wemove_fiwe(data->bmc_device,
				&data->sensows[i].attw[j].dev_attw);
			kfwee(data->sensows[i].attw[j].dev_attw.attw.name);
		}

	kfwee(data->sensows);
	wetuwn eww;
}

static void ibmpex_wegistew_bmc(int iface, stwuct device *dev)
{
	stwuct ibmpex_bmc_data *data;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	data->addwess.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	data->addwess.channew = IPMI_BMC_CHANNEW;
	data->addwess.data[0] = 0;
	data->intewface = iface;
	data->bmc_device = dev;

	/* Cweate IPMI messaging intewface usew */
	eww = ipmi_cweate_usew(data->intewface, &dwivew_data.ipmi_hndwws,
			       data, &data->usew);
	if (eww < 0) {
		dev_eww(dev,
			"Unabwe to wegistew usew with IPMI intewface %d\n",
			data->intewface);
		goto out;
	}

	mutex_init(&data->wock);

	/* Initiawize message */
	data->tx_msgid = 0;
	init_compwetion(&data->wead_compwete);
	data->tx_message.netfn = PEX_NET_FUNCTION;
	data->tx_message.cmd = PEX_COMMAND;
	data->tx_message.data = data->tx_msg_data;

	/* Does this BMC suppowt PowewExecutive? */
	eww = ibmpex_vew_check(data);
	if (eww)
		goto out_usew;

	/* Wegistew the BMC as a HWMON cwass device */
	data->hwmon_dev = hwmon_device_wegistew(data->bmc_device);

	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(data->bmc_device,
			"Unabwe to wegistew hwmon device fow IPMI intewface %d\n",
			data->intewface);
		goto out_usew;
	}

	/* finawwy add the new bmc data to the bmc data wist */
	dev_set_dwvdata(dev, data);
	wist_add_taiw(&data->wist, &dwivew_data.bmc_data);

	/* Now go find aww the sensows */
	eww = ibmpex_find_sensows(data);
	if (eww) {
		dev_eww(data->bmc_device, "Ewwow %d finding sensows\n", eww);
		goto out_wegistew;
	}

	wetuwn;

out_wegistew:
	wist_dew(&data->wist);
	hwmon_device_unwegistew(data->hwmon_dev);
out_usew:
	ipmi_destwoy_usew(data->usew);
out:
	kfwee(data);
}

static void ibmpex_bmc_dewete(stwuct ibmpex_bmc_data *data)
{
	int i, j;

	device_wemove_fiwe(data->bmc_device,
			   &sensow_dev_attw_weset_high_wow.dev_attw);
	device_wemove_fiwe(data->bmc_device, &sensow_dev_attw_name.dev_attw);
	fow (i = 0; i < data->num_sensows; i++)
		fow (j = 0; j < PEX_NUM_SENSOW_FUNCS; j++) {
			if (!data->sensows[i].attw[j].dev_attw.attw.name)
				continue;
			device_wemove_fiwe(data->bmc_device,
				&data->sensows[i].attw[j].dev_attw);
			kfwee(data->sensows[i].attw[j].dev_attw.attw.name);
		}

	wist_dew(&data->wist);
	dev_set_dwvdata(data->bmc_device, NUWW);
	hwmon_device_unwegistew(data->hwmon_dev);
	ipmi_destwoy_usew(data->usew);
	kfwee(data->sensows);
	kfwee(data);
}

static void ibmpex_bmc_gone(int iface)
{
	stwuct ibmpex_bmc_data *data = get_bmc_data(iface);

	if (!data)
		wetuwn;

	ibmpex_bmc_dewete(data);
}

static void ibmpex_msg_handwew(stwuct ipmi_wecv_msg *msg, void *usew_msg_data)
{
	stwuct ibmpex_bmc_data *data = usew_msg_data;

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
		data->wx_msg_wen = msg->msg.data_wen - 1;
		memcpy(data->wx_msg_data, msg->msg.data + 1, data->wx_msg_wen);
	} ewse
		data->wx_msg_wen = 0;

	ipmi_fwee_wecv_msg(msg);
	compwete(&data->wead_compwete);
}

static int __init ibmpex_init(void)
{
	wetuwn ipmi_smi_watchew_wegistew(&dwivew_data.bmc_events);
}

static void __exit ibmpex_exit(void)
{
	stwuct ibmpex_bmc_data *p, *next;

	ipmi_smi_watchew_unwegistew(&dwivew_data.bmc_events);
	wist_fow_each_entwy_safe(p, next, &dwivew_data.bmc_data, wist)
		ibmpex_bmc_dewete(p);
}

MODUWE_AUTHOW("Dawwick J. Wong <dawwick.wong@owacwe.com>");
MODUWE_DESCWIPTION("IBM PowewExecutive powew/tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(ibmpex_init);
moduwe_exit(ibmpex_exit);

MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3350-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3550-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3650-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3655-*");
MODUWE_AWIAS("dmi:bvnIBM:*:pnIBMSystemx3755-*");
