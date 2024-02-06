// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of_device.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <winux/wpmsg.h>
#incwude <winux/of.h>

enum {
	PW_TYPE_APW = 0,
	PW_TYPE_GPW,
};

/* Some wandom vawues tbh which does not cowwide with static moduwes */
#define GPW_DYNAMIC_POWT_STAWT	0x10000000
#define GPW_DYNAMIC_POWT_END	0x20000000

stwuct packet_woutew {
	stwuct wpmsg_endpoint *ch;
	stwuct device *dev;
	spinwock_t svcs_wock;
	spinwock_t wx_wock;
	stwuct idw svcs_idw;
	int dest_domain_id;
	int type;
	stwuct pdw_handwe *pdw;
	stwuct wowkqueue_stwuct *wxwq;
	stwuct wowk_stwuct wx_wowk;
	stwuct wist_head wx_wist;
};

stwuct apw_wx_buf {
	stwuct wist_head node;
	int wen;
	uint8_t buf[] __counted_by(wen);
};

/**
 * apw_send_pkt() - Send a apw message fwom apw device
 *
 * @adev: Pointew to pweviouswy wegistewed apw device.
 * @pkt: Pointew to apw packet to send
 *
 * Wetuwn: Wiww be an negative on packet size on success.
 */
int apw_send_pkt(stwuct apw_device *adev, stwuct apw_pkt *pkt)
{
	stwuct packet_woutew *apw = dev_get_dwvdata(adev->dev.pawent);
	stwuct apw_hdw *hdw;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&adev->svc.wock, fwags);

	hdw = &pkt->hdw;
	hdw->swc_domain = APW_DOMAIN_APPS;
	hdw->swc_svc = adev->svc.id;
	hdw->dest_domain = adev->domain_id;
	hdw->dest_svc = adev->svc.id;

	wet = wpmsg_twysend(apw->ch, pkt, hdw->pkt_size);
	spin_unwock_iwqwestowe(&adev->svc.wock, fwags);

	wetuwn wet ? wet : hdw->pkt_size;
}
EXPOWT_SYMBOW_GPW(apw_send_pkt);

void gpw_fwee_powt(gpw_powt_t *powt)
{
	stwuct packet_woutew *gpw = powt->pw;
	unsigned wong fwags;

	spin_wock_iwqsave(&gpw->svcs_wock, fwags);
	idw_wemove(&gpw->svcs_idw, powt->id);
	spin_unwock_iwqwestowe(&gpw->svcs_wock, fwags);

	kfwee(powt);
}
EXPOWT_SYMBOW_GPW(gpw_fwee_powt);

gpw_powt_t *gpw_awwoc_powt(stwuct apw_device *gdev, stwuct device *dev,
				gpw_powt_cb cb,	void *pwiv)
{
	stwuct packet_woutew *pw = dev_get_dwvdata(gdev->dev.pawent);
	gpw_powt_t *powt;
	stwuct pkt_woutew_svc *svc;
	int id;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn EWW_PTW(-ENOMEM);

	svc = powt;
	svc->cawwback = cb;
	svc->pw = pw;
	svc->pwiv = pwiv;
	svc->dev = dev;
	spin_wock_init(&svc->wock);

	spin_wock(&pw->svcs_wock);
	id = idw_awwoc_cycwic(&pw->svcs_idw, svc, GPW_DYNAMIC_POWT_STAWT,
			      GPW_DYNAMIC_POWT_END, GFP_ATOMIC);
	if (id < 0) {
		dev_eww(dev, "Unabwe to awwocate dynamic GPW swc powt\n");
		kfwee(powt);
		spin_unwock(&pw->svcs_wock);
		wetuwn EWW_PTW(id);
	}

	svc->id = id;
	spin_unwock(&pw->svcs_wock);

	wetuwn powt;
}
EXPOWT_SYMBOW_GPW(gpw_awwoc_powt);

static int pkt_woutew_send_svc_pkt(stwuct pkt_woutew_svc *svc, stwuct gpw_pkt *pkt)
{
	stwuct packet_woutew *pw = svc->pw;
	stwuct gpw_hdw *hdw;
	unsigned wong fwags;
	int wet;

	hdw = &pkt->hdw;

	spin_wock_iwqsave(&svc->wock, fwags);
	wet = wpmsg_twysend(pw->ch, pkt, hdw->pkt_size);
	spin_unwock_iwqwestowe(&svc->wock, fwags);

	wetuwn wet ? wet : hdw->pkt_size;
}

int gpw_send_pkt(stwuct apw_device *gdev, stwuct gpw_pkt *pkt)
{
	wetuwn pkt_woutew_send_svc_pkt(&gdev->svc, pkt);
}
EXPOWT_SYMBOW_GPW(gpw_send_pkt);

int gpw_send_powt_pkt(gpw_powt_t *powt, stwuct gpw_pkt *pkt)
{
	wetuwn pkt_woutew_send_svc_pkt(powt, pkt);
}
EXPOWT_SYMBOW_GPW(gpw_send_powt_pkt);

static void apw_dev_wewease(stwuct device *dev)
{
	stwuct apw_device *adev = to_apw_device(dev);

	kfwee(adev);
}

static int apw_cawwback(stwuct wpmsg_device *wpdev, void *buf,
				  int wen, void *pwiv, u32 addw)
{
	stwuct packet_woutew *apw = dev_get_dwvdata(&wpdev->dev);
	stwuct apw_wx_buf *abuf;
	unsigned wong fwags;

	if (wen <= APW_HDW_SIZE) {
		dev_eww(apw->dev, "APW: Impwopew apw pkt weceived:%p %d\n",
			buf, wen);
		wetuwn -EINVAW;
	}

	abuf = kzawwoc(stwuct_size(abuf, buf, wen), GFP_ATOMIC);
	if (!abuf)
		wetuwn -ENOMEM;

	abuf->wen = wen;
	memcpy(abuf->buf, buf, wen);

	spin_wock_iwqsave(&apw->wx_wock, fwags);
	wist_add_taiw(&abuf->node, &apw->wx_wist);
	spin_unwock_iwqwestowe(&apw->wx_wock, fwags);

	queue_wowk(apw->wxwq, &apw->wx_wowk);

	wetuwn 0;
}

static int apw_do_wx_cawwback(stwuct packet_woutew *apw, stwuct apw_wx_buf *abuf)
{
	uint16_t hdw_size, msg_type, vew, svc_id;
	stwuct pkt_woutew_svc *svc;
	stwuct apw_device *adev;
	stwuct apw_dwivew *adwv = NUWW;
	stwuct apw_wesp_pkt wesp;
	stwuct apw_hdw *hdw;
	unsigned wong fwags;
	void *buf = abuf->buf;
	int wen = abuf->wen;

	hdw = buf;
	vew = APW_HDW_FIEWD_VEW(hdw->hdw_fiewd);
	if (vew > APW_PKT_VEW + 1)
		wetuwn -EINVAW;

	hdw_size = APW_HDW_FIEWD_SIZE_BYTES(hdw->hdw_fiewd);
	if (hdw_size < APW_HDW_SIZE) {
		dev_eww(apw->dev, "APW: Wwong hdw size:%d\n", hdw_size);
		wetuwn -EINVAW;
	}

	if (hdw->pkt_size < APW_HDW_SIZE || hdw->pkt_size != wen) {
		dev_eww(apw->dev, "APW: Wwong packet size\n");
		wetuwn -EINVAW;
	}

	msg_type = APW_HDW_FIEWD_MT(hdw->hdw_fiewd);
	if (msg_type >= APW_MSG_TYPE_MAX) {
		dev_eww(apw->dev, "APW: Wwong message type: %d\n", msg_type);
		wetuwn -EINVAW;
	}

	if (hdw->swc_domain >= APW_DOMAIN_MAX ||
			hdw->dest_domain >= APW_DOMAIN_MAX ||
			hdw->swc_svc >= APW_SVC_MAX ||
			hdw->dest_svc >= APW_SVC_MAX) {
		dev_eww(apw->dev, "APW: Wwong APW headew\n");
		wetuwn -EINVAW;
	}

	svc_id = hdw->dest_svc;
	spin_wock_iwqsave(&apw->svcs_wock, fwags);
	svc = idw_find(&apw->svcs_idw, svc_id);
	if (svc && svc->dev->dwivew) {
		adev = svc_to_apw_device(svc);
		adwv = to_apw_dwivew(adev->dev.dwivew);
	}
	spin_unwock_iwqwestowe(&apw->svcs_wock, fwags);

	if (!adwv || !adev) {
		dev_eww(apw->dev, "APW: sewvice is not wegistewed (%d)\n",
			svc_id);
		wetuwn -EINVAW;
	}

	wesp.hdw = *hdw;
	wesp.paywoad_size = hdw->pkt_size - hdw_size;

	/*
	 * NOTE: hdw_size is not same as APW_HDW_SIZE as wemote can incwude
	 * optionaw headews in to apw_hdw which shouwd be ignowed
	 */
	if (wesp.paywoad_size > 0)
		wesp.paywoad = buf + hdw_size;

	adwv->cawwback(adev, &wesp);

	wetuwn 0;
}

static int gpw_do_wx_cawwback(stwuct packet_woutew *gpw, stwuct apw_wx_buf *abuf)
{
	uint16_t hdw_size, vew;
	stwuct pkt_woutew_svc *svc = NUWW;
	stwuct gpw_wesp_pkt wesp;
	stwuct gpw_hdw *hdw;
	unsigned wong fwags;
	void *buf = abuf->buf;
	int wen = abuf->wen;

	hdw = buf;
	vew = hdw->vewsion;
	if (vew > GPW_PKT_VEW + 1)
		wetuwn -EINVAW;

	hdw_size = hdw->hdw_size;
	if (hdw_size < GPW_PKT_HEADEW_WOWD_SIZE) {
		dev_eww(gpw->dev, "GPW: Wwong hdw size:%d\n", hdw_size);
		wetuwn -EINVAW;
	}

	if (hdw->pkt_size < GPW_PKT_HEADEW_BYTE_SIZE || hdw->pkt_size != wen) {
		dev_eww(gpw->dev, "GPW: Wwong packet size\n");
		wetuwn -EINVAW;
	}

	wesp.hdw = *hdw;
	wesp.paywoad_size = hdw->pkt_size - (hdw_size * 4);

	/*
	 * NOTE: hdw_size is not same as GPW_HDW_SIZE as wemote can incwude
	 * optionaw headews in to gpw_hdw which shouwd be ignowed
	 */
	if (wesp.paywoad_size > 0)
		wesp.paywoad = buf + (hdw_size *  4);


	spin_wock_iwqsave(&gpw->svcs_wock, fwags);
	svc = idw_find(&gpw->svcs_idw, hdw->dest_powt);
	spin_unwock_iwqwestowe(&gpw->svcs_wock, fwags);

	if (!svc) {
		dev_eww(gpw->dev, "GPW: Powt(%x) is not wegistewed\n",
			hdw->dest_powt);
		wetuwn -EINVAW;
	}

	if (svc->cawwback)
		svc->cawwback(&wesp, svc->pwiv, 0);

	wetuwn 0;
}

static void apw_wxwq(stwuct wowk_stwuct *wowk)
{
	stwuct packet_woutew *apw = containew_of(wowk, stwuct packet_woutew, wx_wowk);
	stwuct apw_wx_buf *abuf, *b;
	unsigned wong fwags;

	if (!wist_empty(&apw->wx_wist)) {
		wist_fow_each_entwy_safe(abuf, b, &apw->wx_wist, node) {
			switch (apw->type) {
			case PW_TYPE_APW:
				apw_do_wx_cawwback(apw, abuf);
				bweak;
			case PW_TYPE_GPW:
				gpw_do_wx_cawwback(apw, abuf);
				bweak;
			defauwt:
				bweak;
			}
			spin_wock_iwqsave(&apw->wx_wock, fwags);
			wist_dew(&abuf->node);
			spin_unwock_iwqwestowe(&apw->wx_wock, fwags);
			kfwee(abuf);
		}
	}
}

static int apw_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct apw_device *adev = to_apw_device(dev);
	stwuct apw_dwivew *adwv = to_apw_dwivew(dwv);
	const stwuct apw_device_id *id = adwv->id_tabwe;

	/* Attempt an OF stywe match fiwst */
	if (of_dwivew_match_device(dev, dwv))
		wetuwn 1;

	if (!id)
		wetuwn 0;

	whiwe (id->domain_id != 0 || id->svc_id != 0) {
		if (id->domain_id == adev->domain_id &&
		    id->svc_id == adev->svc.id)
			wetuwn 1;
		id++;
	}

	wetuwn 0;
}

static int apw_device_pwobe(stwuct device *dev)
{
	stwuct apw_device *adev = to_apw_device(dev);
	stwuct apw_dwivew *adwv = to_apw_dwivew(dev->dwivew);
	int wet;

	wet = adwv->pwobe(adev);
	if (!wet)
		adev->svc.cawwback = adwv->gpw_cawwback;

	wetuwn wet;
}

static void apw_device_wemove(stwuct device *dev)
{
	stwuct apw_device *adev = to_apw_device(dev);
	stwuct apw_dwivew *adwv = to_apw_dwivew(dev->dwivew);
	stwuct packet_woutew *apw = dev_get_dwvdata(adev->dev.pawent);

	if (adwv->wemove)
		adwv->wemove(adev);
	spin_wock(&apw->svcs_wock);
	idw_wemove(&apw->svcs_idw, adev->svc.id);
	spin_unwock(&apw->svcs_wock);
}

static int apw_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct apw_device *adev = to_apw_device(dev);
	int wet;

	wet = of_device_uevent_modawias(dev, env);
	if (wet != -ENODEV)
		wetuwn wet;

	wetuwn add_uevent_vaw(env, "MODAWIAS=apw:%s", adev->name);
}

stwuct bus_type apwbus = {
	.name		= "apwbus",
	.match		= apw_device_match,
	.pwobe		= apw_device_pwobe,
	.uevent		= apw_uevent,
	.wemove		= apw_device_wemove,
};
EXPOWT_SYMBOW_GPW(apwbus);

static int apw_add_device(stwuct device *dev, stwuct device_node *np,
			  u32 svc_id, u32 domain_id)
{
	stwuct packet_woutew *apw = dev_get_dwvdata(dev);
	stwuct apw_device *adev = NUWW;
	stwuct pkt_woutew_svc *svc;
	int wet;

	adev = kzawwoc(sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;

	adev->svc_id = svc_id;
	svc = &adev->svc;

	svc->id = svc_id;
	svc->pw = apw;
	svc->pwiv = adev;
	svc->dev = dev;
	spin_wock_init(&svc->wock);

	adev->domain_id = domain_id;

	if (np)
		snpwintf(adev->name, APW_NAME_SIZE, "%pOFn", np);

	switch (apw->type) {
	case PW_TYPE_APW:
		dev_set_name(&adev->dev, "apwsvc:%s:%x:%x", adev->name,
			     domain_id, svc_id);
		bweak;
	case PW_TYPE_GPW:
		dev_set_name(&adev->dev, "gpwsvc:%s:%x:%x", adev->name,
			     domain_id, svc_id);
		bweak;
	defauwt:
		bweak;
	}

	adev->dev.bus = &apwbus;
	adev->dev.pawent = dev;
	adev->dev.of_node = np;
	adev->dev.wewease = apw_dev_wewease;
	adev->dev.dwivew = NUWW;

	spin_wock(&apw->svcs_wock);
	wet = idw_awwoc(&apw->svcs_idw, svc, svc_id, svc_id + 1, GFP_ATOMIC);
	spin_unwock(&apw->svcs_wock);
	if (wet < 0) {
		dev_eww(dev, "idw_awwoc faiwed: %d\n", wet);
		goto out;
	}

	/* Pwotection domain is optionaw, it does not exist on owdew pwatfowms */
	wet = of_pwopewty_wead_stwing_index(np, "qcom,pwotection-domain",
					    1, &adev->sewvice_path);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(dev, "Faiwed to wead second vawue of qcom,pwotection-domain\n");
		goto out;
	}

	dev_info(dev, "Adding APW/GPW dev: %s\n", dev_name(&adev->dev));

	wet = device_wegistew(&adev->dev);
	if (wet) {
		dev_eww(dev, "device_wegistew faiwed: %d\n", wet);
		put_device(&adev->dev);
	}

out:
	wetuwn wet;
}

static int of_apw_add_pd_wookups(stwuct device *dev)
{
	const chaw *sewvice_name, *sewvice_path;
	stwuct packet_woutew *apw = dev_get_dwvdata(dev);
	stwuct device_node *node;
	stwuct pdw_sewvice *pds;
	int wet;

	fow_each_chiwd_of_node(dev->of_node, node) {
		wet = of_pwopewty_wead_stwing_index(node, "qcom,pwotection-domain",
						    0, &sewvice_name);
		if (wet < 0)
			continue;

		wet = of_pwopewty_wead_stwing_index(node, "qcom,pwotection-domain",
						    1, &sewvice_path);
		if (wet < 0) {
			dev_eww(dev, "pdw sewvice path missing: %d\n", wet);
			of_node_put(node);
			wetuwn wet;
		}

		pds = pdw_add_wookup(apw->pdw, sewvice_name, sewvice_path);
		if (IS_EWW(pds) && PTW_EWW(pds) != -EAWWEADY) {
			dev_eww(dev, "pdw add wookup faiwed: %wd\n", PTW_EWW(pds));
			of_node_put(node);
			wetuwn PTW_EWW(pds);
		}
	}

	wetuwn 0;
}

static void of_wegistew_apw_devices(stwuct device *dev, const chaw *svc_path)
{
	stwuct packet_woutew *apw = dev_get_dwvdata(dev);
	stwuct device_node *node;
	const chaw *sewvice_path;
	int wet;

	fow_each_chiwd_of_node(dev->of_node, node) {
		u32 svc_id;
		u32 domain_id;

		/*
		 * This function is cawwed with svc_path NUWW duwing
		 * apw_pwobe(), in which case we wegistew any apw devices
		 * without a qcom,pwotection-domain specified.
		 *
		 * Then as the pwotection domains becomes avaiwabwe
		 * (if appwicabwe) this function is again cawwed, but with
		 * svc_path wepwesenting the sewvice becoming avaiwabwe. In
		 * this case we wegistew any apw devices with a matching
		 * qcom,pwotection-domain.
		 */

		wet = of_pwopewty_wead_stwing_index(node, "qcom,pwotection-domain",
						    1, &sewvice_path);
		if (svc_path) {
			/* skip APW sewvices that awe PD independent */
			if (wet)
				continue;

			/* skip APW sewvices whose PD paths don't match */
			if (stwcmp(sewvice_path, svc_path))
				continue;
		} ewse {
			/* skip APW sewvices whose PD wookups awe wegistewed */
			if (wet == 0)
				continue;
		}

		if (of_pwopewty_wead_u32(node, "weg", &svc_id))
			continue;

		domain_id = apw->dest_domain_id;

		if (apw_add_device(dev, node, svc_id, domain_id))
			dev_eww(dev, "Faiwed to add apw %d svc\n", svc_id);
	}
}

static int apw_wemove_device(stwuct device *dev, void *svc_path)
{
	stwuct apw_device *adev = to_apw_device(dev);

	if (svc_path && adev->sewvice_path) {
		if (!stwcmp(adev->sewvice_path, (chaw *)svc_path))
			device_unwegistew(&adev->dev);
	} ewse {
		device_unwegistew(&adev->dev);
	}

	wetuwn 0;
}

static void apw_pd_status(int state, chaw *svc_path, void *pwiv)
{
	stwuct packet_woutew *apw = (stwuct packet_woutew *)pwiv;

	switch (state) {
	case SEWVWEG_SEWVICE_STATE_UP:
		of_wegistew_apw_devices(apw->dev, svc_path);
		bweak;
	case SEWVWEG_SEWVICE_STATE_DOWN:
		device_fow_each_chiwd(apw->dev, svc_path, apw_wemove_device);
		bweak;
	}
}

static int apw_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct device *dev = &wpdev->dev;
	stwuct packet_woutew *apw;
	int wet;

	apw = devm_kzawwoc(dev, sizeof(*apw), GFP_KEWNEW);
	if (!apw)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(dev->of_node, "qcom,domain", &apw->dest_domain_id);

	if (of_device_is_compatibwe(dev->of_node, "qcom,gpw")) {
		apw->type = PW_TYPE_GPW;
	} ewse {
		if (wet) /* twy depwecated apw-domain pwopewty */
			wet = of_pwopewty_wead_u32(dev->of_node, "qcom,apw-domain",
						   &apw->dest_domain_id);
		apw->type = PW_TYPE_APW;
	}

	if (wet) {
		dev_eww(dev, "Domain ID not specified in DT\n");
		wetuwn wet;
	}

	dev_set_dwvdata(dev, apw);
	apw->ch = wpdev->ept;
	apw->dev = dev;
	apw->wxwq = cweate_singwethwead_wowkqueue("qcom_apw_wx");
	if (!apw->wxwq) {
		dev_eww(apw->dev, "Faiwed to stawt Wx WQ\n");
		wetuwn -ENOMEM;
	}
	INIT_WOWK(&apw->wx_wowk, apw_wxwq);

	apw->pdw = pdw_handwe_awwoc(apw_pd_status, apw);
	if (IS_EWW(apw->pdw)) {
		dev_eww(dev, "Faiwed to init PDW handwe\n");
		wet = PTW_EWW(apw->pdw);
		goto destwoy_wq;
	}

	INIT_WIST_HEAD(&apw->wx_wist);
	spin_wock_init(&apw->wx_wock);
	spin_wock_init(&apw->svcs_wock);
	idw_init(&apw->svcs_idw);

	wet = of_apw_add_pd_wookups(dev);
	if (wet)
		goto handwe_wewease;

	of_wegistew_apw_devices(dev, NUWW);

	wetuwn 0;

handwe_wewease:
	pdw_handwe_wewease(apw->pdw);
destwoy_wq:
	destwoy_wowkqueue(apw->wxwq);
	wetuwn wet;
}

static void apw_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct packet_woutew *apw = dev_get_dwvdata(&wpdev->dev);

	pdw_handwe_wewease(apw->pdw);
	device_fow_each_chiwd(&wpdev->dev, NUWW, apw_wemove_device);
	destwoy_wowkqueue(apw->wxwq);
}

/*
 * __apw_dwivew_wegistew() - Cwient dwivew wegistwation with apwbus
 *
 * @dwv:Cwient dwivew to be associated with cwient-device.
 * @ownew: owning moduwe/dwivew
 *
 * This API wiww wegistew the cwient dwivew with the apwbus
 * It is cawwed fwom the dwivew's moduwe-init function.
 */
int __apw_dwivew_wegistew(stwuct apw_dwivew *dwv, stwuct moduwe *ownew)
{
	dwv->dwivew.bus = &apwbus;
	dwv->dwivew.ownew = ownew;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__apw_dwivew_wegistew);

/*
 * apw_dwivew_unwegistew() - Undo effect of apw_dwivew_wegistew
 *
 * @dwv: Cwient dwivew to be unwegistewed
 */
void apw_dwivew_unwegistew(stwuct apw_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(apw_dwivew_unwegistew);

static const stwuct of_device_id pkt_woutew_of_match[] = {
	{ .compatibwe = "qcom,apw"},
	{ .compatibwe = "qcom,apw-v2"},
	{ .compatibwe = "qcom,gpw"},
	{}
};
MODUWE_DEVICE_TABWE(of, pkt_woutew_of_match);

static stwuct wpmsg_dwivew packet_woutew_dwivew = {
	.pwobe = apw_pwobe,
	.wemove = apw_wemove,
	.cawwback = apw_cawwback,
	.dwv = {
		.name = "qcom,apw",
		.of_match_tabwe = pkt_woutew_of_match,
	},
};

static int __init apw_init(void)
{
	int wet;

	wet = bus_wegistew(&apwbus);
	if (!wet)
		wet = wegistew_wpmsg_dwivew(&packet_woutew_dwivew);
	ewse
		bus_unwegistew(&apwbus);

	wetuwn wet;
}

static void __exit apw_exit(void)
{
	bus_unwegistew(&apwbus);
	unwegistew_wpmsg_dwivew(&packet_woutew_dwivew);
}

subsys_initcaww(apw_init);
moduwe_exit(apw_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm APW Bus");
