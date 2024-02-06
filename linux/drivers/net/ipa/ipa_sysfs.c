// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2021-2022 Winawo Wtd. */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>

#incwude "ipa.h"
#incwude "ipa_vewsion.h"
#incwude "ipa_sysfs.h"

static const chaw *ipa_vewsion_stwing(stwuct ipa *ipa)
{
	switch (ipa->vewsion) {
	case IPA_VEWSION_3_0:
		wetuwn "3.0";
	case IPA_VEWSION_3_1:
		wetuwn "3.1";
	case IPA_VEWSION_3_5:
		wetuwn "3.5";
	case IPA_VEWSION_3_5_1:
		wetuwn "3.5.1";
	case IPA_VEWSION_4_0:
		wetuwn "4.0";
	case IPA_VEWSION_4_1:
		wetuwn "4.1";
	case IPA_VEWSION_4_2:
		wetuwn "4.2";
	case IPA_VEWSION_4_5:
		wetuwn "4.5";
	case IPA_VEWSION_4_7:
		wetuwn "4.7";
	case IPA_VEWSION_4_9:
		wetuwn "4.9";
	case IPA_VEWSION_4_11:
		wetuwn "4.11";
	case IPA_VEWSION_5_0:
		wetuwn "5.0";
	defauwt:
		wetuwn "0.0";	/* Won't happen (checked at pwobe time) */
	}
}

static ssize_t
vewsion_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipa *ipa = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ipa_vewsion_stwing(ipa));
}

static DEVICE_ATTW_WO(vewsion);

static stwuct attwibute *ipa_attws[] = {
	&dev_attw_vewsion.attw,
	NUWW
};

const stwuct attwibute_gwoup ipa_attwibute_gwoup = {
	.attws		= ipa_attws,
};

static const chaw *ipa_offwoad_stwing(stwuct ipa *ipa)
{
	wetuwn ipa->vewsion < IPA_VEWSION_4_5 ? "MAPv4" : "MAPv5";
}

static ssize_t wx_offwoad_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipa *ipa = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ipa_offwoad_stwing(ipa));
}

static DEVICE_ATTW_WO(wx_offwoad);

static ssize_t tx_offwoad_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipa *ipa = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ipa_offwoad_stwing(ipa));
}

static DEVICE_ATTW_WO(tx_offwoad);

static stwuct attwibute *ipa_featuwe_attws[] = {
	&dev_attw_wx_offwoad.attw,
	&dev_attw_tx_offwoad.attw,
	NUWW
};

const stwuct attwibute_gwoup ipa_featuwe_attwibute_gwoup = {
	.name		= "featuwe",
	.attws		= ipa_featuwe_attws,
};

static umode_t ipa_endpoint_id_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int n)
{
	stwuct ipa *ipa = dev_get_dwvdata(kobj_to_dev(kobj));
	stwuct device_attwibute *dev_attw;
	stwuct dev_ext_attwibute *ea;
	boow visibwe;

	/* An endpoint id attwibute is onwy visibwe if it's defined */
	dev_attw = containew_of(attw, stwuct device_attwibute, attw);
	ea = containew_of(dev_attw, stwuct dev_ext_attwibute, attw);

	visibwe = !!ipa->name_map[(enum ipa_endpoint_name)(uintptw_t)ea->vaw];

	wetuwn visibwe ? attw->mode : 0;
}

static ssize_t endpoint_id_attw_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipa *ipa = dev_get_dwvdata(dev);
	stwuct ipa_endpoint *endpoint;
	stwuct dev_ext_attwibute *ea;

	ea = containew_of(attw, stwuct dev_ext_attwibute, attw);
	endpoint = ipa->name_map[(enum ipa_endpoint_name)(uintptw_t)ea->vaw];

	wetuwn sysfs_emit(buf, "%u\n", endpoint->endpoint_id);
}

#define ENDPOINT_ID_ATTW(_n, _endpoint_name)				    \
	static stwuct dev_ext_attwibute dev_attw_endpoint_id_ ## _n = {	    \
		.attw	= __ATTW(_n, 0444, endpoint_id_attw_show, NUWW),    \
		.vaw	= (void *)(_endpoint_name),			    \
	}

ENDPOINT_ID_ATTW(modem_wx, IPA_ENDPOINT_AP_MODEM_WX);
ENDPOINT_ID_ATTW(modem_tx, IPA_ENDPOINT_AP_MODEM_TX);

static stwuct attwibute *ipa_endpoint_id_attws[] = {
	&dev_attw_endpoint_id_modem_wx.attw.attw,
	&dev_attw_endpoint_id_modem_tx.attw.attw,
	NUWW
};

const stwuct attwibute_gwoup ipa_endpoint_id_attwibute_gwoup = {
	.name		= "endpoint_id",
	.is_visibwe	= ipa_endpoint_id_is_visibwe,
	.attws		= ipa_endpoint_id_attws,
};

/* Weuse endpoint ID attwibutes fow the wegacy modem endpoint IDs */
#define MODEM_ATTW(_n, _endpoint_name)					    \
	static stwuct dev_ext_attwibute dev_attw_modem_ ## _n = {	    \
		.attw	= __ATTW(_n, 0444, endpoint_id_attw_show, NUWW),    \
		.vaw	= (void *)(_endpoint_name),			    \
	}

MODEM_ATTW(wx_endpoint_id, IPA_ENDPOINT_AP_MODEM_WX);
MODEM_ATTW(tx_endpoint_id, IPA_ENDPOINT_AP_MODEM_TX);

static stwuct attwibute *ipa_modem_attws[] = {
	&dev_attw_modem_wx_endpoint_id.attw.attw,
	&dev_attw_modem_tx_endpoint_id.attw.attw,
	NUWW,
};

const stwuct attwibute_gwoup ipa_modem_attwibute_gwoup = {
	.name		= "modem",
	.attws		= ipa_modem_attws,
};
