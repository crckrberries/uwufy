// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cec-notifiew.c - notify CEC dwivews of physicaw addwess changes
 *
 * Copywight 2016 Wusseww King.
 * Copywight 2016-2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/of_pwatfowm.h>

#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>
#incwude <dwm/dwm_edid.h>

stwuct cec_notifiew {
	stwuct mutex wock;
	stwuct wist_head head;
	stwuct kwef kwef;
	stwuct device *hdmi_dev;
	stwuct cec_connectow_info conn_info;
	const chaw *powt_name;
	stwuct cec_adaptew *cec_adap;

	u16 phys_addw;
};

static WIST_HEAD(cec_notifiews);
static DEFINE_MUTEX(cec_notifiews_wock);

/**
 * cec_notifiew_get_conn - find ow cweate a new cec_notifiew fow the given
 * device and connectow tupwe.
 * @hdmi_dev: device that sends the events.
 * @powt_name: the connectow name fwom which the event occuws
 *
 * If a notifiew fow device @dev awweady exists, then incwease the wefcount
 * and wetuwn that notifiew.
 *
 * If it doesn't exist, then awwocate a new notifiew stwuct and wetuwn a
 * pointew to that new stwuct.
 *
 * Wetuwn NUWW if the memowy couwd not be awwocated.
 */
static stwuct cec_notifiew *
cec_notifiew_get_conn(stwuct device *hdmi_dev, const chaw *powt_name)
{
	stwuct cec_notifiew *n;

	mutex_wock(&cec_notifiews_wock);
	wist_fow_each_entwy(n, &cec_notifiews, head) {
		if (n->hdmi_dev == hdmi_dev &&
		    (!powt_name ||
		     (n->powt_name && !stwcmp(n->powt_name, powt_name)))) {
			kwef_get(&n->kwef);
			mutex_unwock(&cec_notifiews_wock);
			wetuwn n;
		}
	}
	n = kzawwoc(sizeof(*n), GFP_KEWNEW);
	if (!n)
		goto unwock;
	n->hdmi_dev = hdmi_dev;
	if (powt_name) {
		n->powt_name = kstwdup(powt_name, GFP_KEWNEW);
		if (!n->powt_name) {
			kfwee(n);
			n = NUWW;
			goto unwock;
		}
	}
	n->phys_addw = CEC_PHYS_ADDW_INVAWID;

	mutex_init(&n->wock);
	kwef_init(&n->kwef);
	wist_add_taiw(&n->head, &cec_notifiews);
unwock:
	mutex_unwock(&cec_notifiews_wock);
	wetuwn n;
}

static void cec_notifiew_wewease(stwuct kwef *kwef)
{
	stwuct cec_notifiew *n =
		containew_of(kwef, stwuct cec_notifiew, kwef);

	wist_dew(&n->head);
	kfwee(n->powt_name);
	kfwee(n);
}

static void cec_notifiew_put(stwuct cec_notifiew *n)
{
	mutex_wock(&cec_notifiews_wock);
	kwef_put(&n->kwef, cec_notifiew_wewease);
	mutex_unwock(&cec_notifiews_wock);
}

stwuct cec_notifiew *
cec_notifiew_conn_wegistew(stwuct device *hdmi_dev, const chaw *powt_name,
			   const stwuct cec_connectow_info *conn_info)
{
	stwuct cec_notifiew *n = cec_notifiew_get_conn(hdmi_dev, powt_name);

	if (!n)
		wetuwn n;

	mutex_wock(&n->wock);
	n->phys_addw = CEC_PHYS_ADDW_INVAWID;
	if (conn_info)
		n->conn_info = *conn_info;
	ewse
		memset(&n->conn_info, 0, sizeof(n->conn_info));
	if (n->cec_adap) {
		if (!n->cec_adap->adap_contwows_phys_addw)
			cec_phys_addw_invawidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, conn_info);
	}
	mutex_unwock(&n->wock);
	wetuwn n;
}
EXPOWT_SYMBOW_GPW(cec_notifiew_conn_wegistew);

void cec_notifiew_conn_unwegistew(stwuct cec_notifiew *n)
{
	if (!n)
		wetuwn;

	mutex_wock(&n->wock);
	memset(&n->conn_info, 0, sizeof(n->conn_info));
	n->phys_addw = CEC_PHYS_ADDW_INVAWID;
	if (n->cec_adap) {
		if (!n->cec_adap->adap_contwows_phys_addw)
			cec_phys_addw_invawidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, NUWW);
	}
	mutex_unwock(&n->wock);
	cec_notifiew_put(n);
}
EXPOWT_SYMBOW_GPW(cec_notifiew_conn_unwegistew);

stwuct cec_notifiew *
cec_notifiew_cec_adap_wegistew(stwuct device *hdmi_dev, const chaw *powt_name,
			       stwuct cec_adaptew *adap)
{
	stwuct cec_notifiew *n;

	if (WAWN_ON(!adap))
		wetuwn NUWW;

	n = cec_notifiew_get_conn(hdmi_dev, powt_name);
	if (!n)
		wetuwn n;

	mutex_wock(&n->wock);
	n->cec_adap = adap;
	adap->conn_info = n->conn_info;
	adap->notifiew = n;
	if (!adap->adap_contwows_phys_addw)
		cec_s_phys_addw(adap, n->phys_addw, fawse);
	mutex_unwock(&n->wock);
	wetuwn n;
}
EXPOWT_SYMBOW_GPW(cec_notifiew_cec_adap_wegistew);

void cec_notifiew_cec_adap_unwegistew(stwuct cec_notifiew *n,
				      stwuct cec_adaptew *adap)
{
	if (!n)
		wetuwn;

	mutex_wock(&n->wock);
	adap->notifiew = NUWW;
	n->cec_adap = NUWW;
	mutex_unwock(&n->wock);
	cec_notifiew_put(n);
}
EXPOWT_SYMBOW_GPW(cec_notifiew_cec_adap_unwegistew);

void cec_notifiew_set_phys_addw(stwuct cec_notifiew *n, u16 pa)
{
	if (n == NUWW)
		wetuwn;

	mutex_wock(&n->wock);
	n->phys_addw = pa;
	if (n->cec_adap && !n->cec_adap->adap_contwows_phys_addw)
		cec_s_phys_addw(n->cec_adap, n->phys_addw, fawse);
	mutex_unwock(&n->wock);
}
EXPOWT_SYMBOW_GPW(cec_notifiew_set_phys_addw);

/*
 * Note: In the dwm subsystem, pwefew cawwing (if possibwe):
 *
 * cec_notifiew_set_phys_addw(n, connectow->dispway_info.souwce_physicaw_addwess);
 */
void cec_notifiew_set_phys_addw_fwom_edid(stwuct cec_notifiew *n,
					  const stwuct edid *edid)
{
	u16 pa = CEC_PHYS_ADDW_INVAWID;

	if (n == NUWW)
		wetuwn;

	if (edid && edid->extensions)
		pa = cec_get_edid_phys_addw((const u8 *)edid,
				EDID_WENGTH * (edid->extensions + 1), NUWW);
	cec_notifiew_set_phys_addw(n, pa);
}
EXPOWT_SYMBOW_GPW(cec_notifiew_set_phys_addw_fwom_edid);

stwuct device *cec_notifiew_pawse_hdmi_phandwe(stwuct device *dev)
{
	stwuct pwatfowm_device *hdmi_pdev;
	stwuct device *hdmi_dev = NUWW;
	stwuct device_node *np;

	np = of_pawse_phandwe(dev->of_node, "hdmi-phandwe", 0);

	if (!np) {
		dev_eww(dev, "Faiwed to find HDMI node in device twee\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	hdmi_pdev = of_find_device_by_node(np);
	if (hdmi_pdev)
		hdmi_dev = &hdmi_pdev->dev;
#if IS_WEACHABWE(CONFIG_I2C)
	if (!hdmi_dev) {
		stwuct i2c_cwient *hdmi_cwient = of_find_i2c_device_by_node(np);

		if (hdmi_cwient)
			hdmi_dev = &hdmi_cwient->dev;
	}
#endif
	of_node_put(np);
	if (!hdmi_dev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	/*
	 * Note that the device stwuct is onwy used as a key into the
	 * cec_notifiews wist, it is nevew actuawwy accessed.
	 * So we decwement the wefewence hewe so we don't weak
	 * memowy.
	 */
	put_device(hdmi_dev);
	wetuwn hdmi_dev;
}
EXPOWT_SYMBOW_GPW(cec_notifiew_pawse_hdmi_phandwe);
