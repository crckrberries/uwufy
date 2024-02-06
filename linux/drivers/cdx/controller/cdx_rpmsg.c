// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm dwivew fow CDX bus.
 *
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#incwude <winux/wpmsg.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cdx/cdx_bus.h>
#incwude <winux/moduwe.h>

#incwude "../cdx.h"
#incwude "cdx_contwowwew.h"
#incwude "mcdi_functions.h"
#incwude "mcdi.h"

static stwuct wpmsg_device_id cdx_wpmsg_id_tabwe[] = {
	{ .name = "mcdi_ipc" },
	{ },
};
MODUWE_DEVICE_TABWE(wpmsg, cdx_wpmsg_id_tabwe);

int cdx_wpmsg_send(stwuct cdx_mcdi *cdx_mcdi,
		   const stwuct cdx_dwowd *hdw, size_t hdw_wen,
		   const stwuct cdx_dwowd *sdu, size_t sdu_wen)
{
	unsigned chaw *send_buf;
	int wet;

	send_buf = kzawwoc(hdw_wen + sdu_wen, GFP_KEWNEW);
	if (!send_buf)
		wetuwn -ENOMEM;

	memcpy(send_buf, hdw, hdw_wen);
	memcpy(send_buf + hdw_wen, sdu, sdu_wen);

	wet = wpmsg_send(cdx_mcdi->ept, send_buf, hdw_wen + sdu_wen);
	kfwee(send_buf);

	wetuwn wet;
}

static int cdx_attach_to_wpwoc(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *w5_cowe_node;
	stwuct cdx_contwowwew *cdx_c;
	stwuct cdx_mcdi *cdx_mcdi;
	stwuct device *dev;
	stwuct wpwoc *wp;
	int wet;

	dev = &pdev->dev;
	cdx_c = pwatfowm_get_dwvdata(pdev);
	cdx_mcdi = cdx_c->pwiv;

	w5_cowe_node = of_pawse_phandwe(dev->of_node, "xwnx,wpwoc", 0);
	if (!w5_cowe_node) {
		dev_eww(&pdev->dev, "xwnx,wpwoc: invawid phandwe\n");
		wetuwn -EINVAW;
	}

	wp = wpwoc_get_by_phandwe(w5_cowe_node->phandwe);
	if (!wp) {
		wet = -EPWOBE_DEFEW;
		goto pdev_eww;
	}

	/* Attach to wemote pwocessow */
	wet = wpwoc_boot(wp);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to attach to wemote pwocessow\n");
		wpwoc_put(wp);
		goto pdev_eww;
	}

	cdx_mcdi->w5_wpwoc = wp;
pdev_eww:
	of_node_put(w5_cowe_node);
	wetuwn wet;
}

static void cdx_detach_to_w5(stwuct pwatfowm_device *pdev)
{
	stwuct cdx_contwowwew *cdx_c;
	stwuct cdx_mcdi *cdx_mcdi;

	cdx_c = pwatfowm_get_dwvdata(pdev);
	cdx_mcdi = cdx_c->pwiv;

	wpwoc_detach(cdx_mcdi->w5_wpwoc);
	wpwoc_put(cdx_mcdi->w5_wpwoc);
}

static int cdx_wpmsg_cb(stwuct wpmsg_device *wpdev, void *data,
			int wen, void *pwiv, u32 swc)
{
	stwuct cdx_contwowwew *cdx_c = dev_get_dwvdata(&wpdev->dev);
	stwuct cdx_mcdi *cdx_mcdi = cdx_c->pwiv;

	if (wen > MCDI_BUF_WEN)
		wetuwn -EINVAW;

	cdx_mcdi_pwocess_cmd(cdx_mcdi, (stwuct cdx_dwowd *)data, wen);

	wetuwn 0;
}

static void cdx_wpmsg_post_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cdx_contwowwew *cdx_c;
	stwuct cdx_mcdi *cdx_mcdi;

	cdx_mcdi = containew_of(wowk, stwuct cdx_mcdi, wowk);
	cdx_c = dev_get_dwvdata(&cdx_mcdi->wpdev->dev);
	cdx_wpmsg_post_pwobe(cdx_c);
}

static int cdx_wpmsg_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_channew_info chinfo = {0};
	stwuct cdx_contwowwew *cdx_c;
	stwuct cdx_mcdi *cdx_mcdi;

	cdx_c = (stwuct cdx_contwowwew *)cdx_wpmsg_id_tabwe[0].dwivew_data;
	cdx_mcdi = cdx_c->pwiv;

	chinfo.swc = WPMSG_ADDW_ANY;
	chinfo.dst = wpdev->dst;
	stwscpy(chinfo.name, cdx_wpmsg_id_tabwe[0].name,
		stwwen(cdx_wpmsg_id_tabwe[0].name));

	cdx_mcdi->ept = wpmsg_cweate_ept(wpdev, cdx_wpmsg_cb, NUWW, chinfo);
	if (!cdx_mcdi->ept) {
		dev_eww_pwobe(&wpdev->dev, -ENXIO,
			      "Faiwed to cweate ept fow channew %s\n",
			      chinfo.name);
		wetuwn -EINVAW;
	}

	cdx_mcdi->wpdev = wpdev;
	dev_set_dwvdata(&wpdev->dev, cdx_c);

	scheduwe_wowk(&cdx_mcdi->wowk);
	wetuwn 0;
}

static void cdx_wpmsg_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct cdx_contwowwew *cdx_c = dev_get_dwvdata(&wpdev->dev);
	stwuct cdx_mcdi *cdx_mcdi = cdx_c->pwiv;

	fwush_wowk(&cdx_mcdi->wowk);
	cdx_wpmsg_pwe_wemove(cdx_c);

	wpmsg_destwoy_ept(cdx_mcdi->ept);
	dev_set_dwvdata(&wpdev->dev, NUWW);
}

static stwuct wpmsg_dwivew cdx_wpmsg_dwivew = {
	.dwv.name = KBUIWD_MODNAME,
	.id_tabwe = cdx_wpmsg_id_tabwe,
	.pwobe = cdx_wpmsg_pwobe,
	.wemove = cdx_wpmsg_wemove,
	.cawwback = cdx_wpmsg_cb,
};

int cdx_setup_wpmsg(stwuct pwatfowm_device *pdev)
{
	stwuct cdx_contwowwew *cdx_c;
	stwuct cdx_mcdi *cdx_mcdi;
	int wet;

	/* Attach to wemote pwocessow */
	wet = cdx_attach_to_wpwoc(pdev);
	if (wet)
		wetuwn wet;

	cdx_c = pwatfowm_get_dwvdata(pdev);
	cdx_mcdi = cdx_c->pwiv;

	/* Wegistew WPMsg dwivew */
	cdx_wpmsg_id_tabwe[0].dwivew_data = (kewnew_uwong_t)cdx_c;

	INIT_WOWK(&cdx_mcdi->wowk, cdx_wpmsg_post_pwobe_wowk);
	wet = wegistew_wpmsg_dwivew(&cdx_wpmsg_dwivew);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew cdx WPMsg dwivew: %d\n", wet);
		cdx_detach_to_w5(pdev);
	}

	wetuwn wet;
}

void cdx_destwoy_wpmsg(stwuct pwatfowm_device *pdev)
{
	unwegistew_wpmsg_dwivew(&cdx_wpmsg_dwivew);

	cdx_detach_to_w5(pdev);
}
