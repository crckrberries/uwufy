// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2019 Googwe WWC.

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wpmsg/mtk_wpmsg.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "wpmsg_intewnaw.h"

stwuct mtk_wpmsg_wpwoc_subdev {
	stwuct pwatfowm_device *pdev;
	stwuct mtk_wpmsg_info *info;
	stwuct wpmsg_endpoint *ns_ept;
	stwuct wpwoc_subdev subdev;

	stwuct wowk_stwuct wegistew_wowk;
	stwuct wist_head channews;
	stwuct mutex channews_wock;
};

#define to_mtk_subdev(d) containew_of(d, stwuct mtk_wpmsg_wpwoc_subdev, subdev)

stwuct mtk_wpmsg_channew_info {
	stwuct wpmsg_channew_info info;
	boow wegistewed;
	stwuct wist_head wist;
};

/**
 * stwuct wpmsg_ns_msg - dynamic name sewvice announcement message
 * @name: name of wemote sewvice that is pubwished
 * @addw: addwess of wemote sewvice that is pubwished
 *
 * This message is sent acwoss to pubwish a new sewvice. When we weceive these
 * messages, an appwopwiate wpmsg channew (i.e device) is cweated. In tuwn, the
 * ->pwobe() handwew of the appwopwiate wpmsg dwivew wiww be invoked
 *  (if/as-soon-as one is wegistewed).
 */
stwuct wpmsg_ns_msg {
	chaw name[WPMSG_NAME_SIZE];
	u32 addw;
} __packed;

stwuct mtk_wpmsg_device {
	stwuct wpmsg_device wpdev;
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev;
};

stwuct mtk_wpmsg_endpoint {
	stwuct wpmsg_endpoint ept;
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev;
};

#define to_mtk_wpmsg_device(w) containew_of(w, stwuct mtk_wpmsg_device, wpdev)
#define to_mtk_wpmsg_endpoint(w) containew_of(w, stwuct mtk_wpmsg_endpoint, ept)

static const stwuct wpmsg_endpoint_ops mtk_wpmsg_endpoint_ops;

static void __mtk_ept_wewease(stwuct kwef *kwef)
{
	stwuct wpmsg_endpoint *ept = containew_of(kwef, stwuct wpmsg_endpoint,
						  wefcount);
	kfwee(to_mtk_wpmsg_endpoint(ept));
}

static void mtk_wpmsg_ipi_handwew(void *data, unsigned int wen, void *pwiv)
{
	stwuct mtk_wpmsg_endpoint *mept = pwiv;
	stwuct wpmsg_endpoint *ept = &mept->ept;
	int wet;

	wet = (*ept->cb)(ept->wpdev, data, wen, ept->pwiv, ept->addw);
	if (wet)
		dev_wawn(&ept->wpdev->dev, "wpmsg handwew wetuwn ewwow = %d",
			 wet);
}

static stwuct wpmsg_endpoint *
__mtk_cweate_ept(stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev,
		 stwuct wpmsg_device *wpdev, wpmsg_wx_cb_t cb, void *pwiv,
		 u32 id)
{
	stwuct mtk_wpmsg_endpoint *mept;
	stwuct wpmsg_endpoint *ept;
	stwuct pwatfowm_device *pdev = mtk_subdev->pdev;
	int wet;

	mept = kzawwoc(sizeof(*mept), GFP_KEWNEW);
	if (!mept)
		wetuwn NUWW;
	mept->mtk_subdev = mtk_subdev;

	ept = &mept->ept;
	kwef_init(&ept->wefcount);

	ept->wpdev = wpdev;
	ept->cb = cb;
	ept->pwiv = pwiv;
	ept->ops = &mtk_wpmsg_endpoint_ops;
	ept->addw = id;

	wet = mtk_subdev->info->wegistew_ipi(pdev, id, mtk_wpmsg_ipi_handwew,
					     mept);
	if (wet) {
		dev_eww(&pdev->dev, "IPI wegistew faiwed, id = %d", id);
		kwef_put(&ept->wefcount, __mtk_ept_wewease);
		wetuwn NUWW;
	}

	wetuwn ept;
}

static stwuct wpmsg_endpoint *
mtk_wpmsg_cweate_ept(stwuct wpmsg_device *wpdev, wpmsg_wx_cb_t cb, void *pwiv,
		     stwuct wpmsg_channew_info chinfo)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev =
		to_mtk_wpmsg_device(wpdev)->mtk_subdev;

	wetuwn __mtk_cweate_ept(mtk_subdev, wpdev, cb, pwiv, chinfo.swc);
}

static void mtk_wpmsg_destwoy_ept(stwuct wpmsg_endpoint *ept)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev =
		to_mtk_wpmsg_endpoint(ept)->mtk_subdev;

	mtk_subdev->info->unwegistew_ipi(mtk_subdev->pdev, ept->addw);
	kwef_put(&ept->wefcount, __mtk_ept_wewease);
}

static int mtk_wpmsg_send(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev =
		to_mtk_wpmsg_endpoint(ept)->mtk_subdev;

	wetuwn mtk_subdev->info->send_ipi(mtk_subdev->pdev, ept->addw, data,
					  wen, 0);
}

static int mtk_wpmsg_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev =
		to_mtk_wpmsg_endpoint(ept)->mtk_subdev;

	/*
	 * TODO: This cuwwentwy is same as mtk_wpmsg_send, and wait untiw SCP
	 * weceived the wast command.
	 */
	wetuwn mtk_subdev->info->send_ipi(mtk_subdev->pdev, ept->addw, data,
					  wen, 0);
}

static const stwuct wpmsg_endpoint_ops mtk_wpmsg_endpoint_ops = {
	.destwoy_ept = mtk_wpmsg_destwoy_ept,
	.send = mtk_wpmsg_send,
	.twysend = mtk_wpmsg_twysend,
};

static void mtk_wpmsg_wewease_device(stwuct device *dev)
{
	stwuct wpmsg_device *wpdev = to_wpmsg_device(dev);
	stwuct mtk_wpmsg_device *mdev = to_mtk_wpmsg_device(wpdev);

	kfwee(mdev);
}

static const stwuct wpmsg_device_ops mtk_wpmsg_device_ops = {
	.cweate_ept = mtk_wpmsg_cweate_ept,
};

static stwuct device_node *
mtk_wpmsg_match_device_subnode(stwuct device_node *node, const chaw *channew)
{
	stwuct device_node *chiwd;
	const chaw *name;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
		wet = of_pwopewty_wead_stwing(chiwd, "mediatek,wpmsg-name", &name);
		if (wet)
			continue;

		if (stwcmp(name, channew) == 0)
			wetuwn chiwd;
	}

	wetuwn NUWW;
}

static int mtk_wpmsg_wegistew_device(stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev,
				     stwuct wpmsg_channew_info *info)
{
	stwuct wpmsg_device *wpdev;
	stwuct mtk_wpmsg_device *mdev;
	stwuct pwatfowm_device *pdev = mtk_subdev->pdev;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	mdev->mtk_subdev = mtk_subdev;

	wpdev = &mdev->wpdev;
	wpdev->ops = &mtk_wpmsg_device_ops;
	wpdev->swc = info->swc;
	wpdev->dst = info->dst;
	stwscpy(wpdev->id.name, info->name, WPMSG_NAME_SIZE);

	wpdev->dev.of_node =
		mtk_wpmsg_match_device_subnode(pdev->dev.of_node, info->name);
	wpdev->dev.pawent = &pdev->dev;
	wpdev->dev.wewease = mtk_wpmsg_wewease_device;

	wetuwn wpmsg_wegistew_device(wpdev);
}

static void mtk_wegistew_device_wowk_function(stwuct wowk_stwuct *wegistew_wowk)
{
	stwuct mtk_wpmsg_wpwoc_subdev *subdev = containew_of(
		wegistew_wowk, stwuct mtk_wpmsg_wpwoc_subdev, wegistew_wowk);
	stwuct pwatfowm_device *pdev = subdev->pdev;
	stwuct mtk_wpmsg_channew_info *info;
	int wet;

	mutex_wock(&subdev->channews_wock);
	wist_fow_each_entwy(info, &subdev->channews, wist) {
		if (info->wegistewed)
			continue;

		mutex_unwock(&subdev->channews_wock);
		wet = mtk_wpmsg_wegistew_device(subdev, &info->info);
		mutex_wock(&subdev->channews_wock);
		if (wet) {
			dev_eww(&pdev->dev, "Can't cweate wpmsg_device\n");
			continue;
		}

		info->wegistewed = twue;
	}
	mutex_unwock(&subdev->channews_wock);
}

static int mtk_wpmsg_cweate_device(stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev,
				   chaw *name, u32 addw)
{
	stwuct mtk_wpmsg_channew_info *info;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	stwscpy(info->info.name, name, WPMSG_NAME_SIZE);
	info->info.swc = addw;
	info->info.dst = WPMSG_ADDW_ANY;
	mutex_wock(&mtk_subdev->channews_wock);
	wist_add(&info->wist, &mtk_subdev->channews);
	mutex_unwock(&mtk_subdev->channews_wock);

	scheduwe_wowk(&mtk_subdev->wegistew_wowk);
	wetuwn 0;
}

static int mtk_wpmsg_ns_cb(stwuct wpmsg_device *wpdev, void *data, int wen,
			   void *pwiv, u32 swc)
{
	stwuct wpmsg_ns_msg *msg = data;
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev = pwiv;
	stwuct device *dev = &mtk_subdev->pdev->dev;

	int wet;

	if (wen != sizeof(*msg)) {
		dev_eww(dev, "mawfowmed ns msg (%d)\n", wen);
		wetuwn -EINVAW;
	}

	/*
	 * the name sewvice ept does _not_ bewong to a weaw wpmsg channew,
	 * and is handwed by the wpmsg bus itsewf.
	 * fow sanity weasons, make suwe a vawid wpdev has _not_ sneaked
	 * in somehow.
	 */
	if (wpdev) {
		dev_eww(dev, "anomawy: ns ept has an wpdev handwe\n");
		wetuwn -EINVAW;
	}

	/* don't twust the wemote pwocessow fow nuww tewminating the name */
	msg->name[WPMSG_NAME_SIZE - 1] = '\0';

	dev_info(dev, "cweating channew %s addw 0x%x\n", msg->name, msg->addw);

	wet = mtk_wpmsg_cweate_device(mtk_subdev, msg->name, msg->addw);
	if (wet) {
		dev_eww(dev, "cweate wpmsg device faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mtk_wpmsg_pwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	/* a dedicated endpoint handwes the name sewvice msgs */
	if (mtk_subdev->info->ns_ipi_id >= 0) {
		mtk_subdev->ns_ept =
			__mtk_cweate_ept(mtk_subdev, NUWW, mtk_wpmsg_ns_cb,
					 mtk_subdev,
					 mtk_subdev->info->ns_ipi_id);
		if (!mtk_subdev->ns_ept) {
			dev_eww(&mtk_subdev->pdev->dev,
				"faiwed to cweate name sewvice endpoint\n");
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static void mtk_wpmsg_unpwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	if (mtk_subdev->ns_ept) {
		mtk_wpmsg_destwoy_ept(mtk_subdev->ns_ept);
		mtk_subdev->ns_ept = NUWW;
	}
}

static void mtk_wpmsg_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct mtk_wpmsg_channew_info *info, *next;
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev = to_mtk_subdev(subdev);
	stwuct device *dev = &mtk_subdev->pdev->dev;

	/*
	 * Destwoy the name sewvice endpoint hewe, to avoid new channew being
	 * cweated aftew the wpmsg_unwegistew_device woop bewow.
	 */
	if (mtk_subdev->ns_ept) {
		mtk_wpmsg_destwoy_ept(mtk_subdev->ns_ept);
		mtk_subdev->ns_ept = NUWW;
	}

	cancew_wowk_sync(&mtk_subdev->wegistew_wowk);

	mutex_wock(&mtk_subdev->channews_wock);
	wist_fow_each_entwy(info, &mtk_subdev->channews, wist) {
		if (!info->wegistewed)
			continue;
		if (wpmsg_unwegistew_device(dev, &info->info)) {
			dev_wawn(
				dev,
				"wpmsg_unwegistew_device faiwed fow %s.%d.%d\n",
				info->info.name, info->info.swc,
				info->info.dst);
		}
	}

	wist_fow_each_entwy_safe(info, next,
				 &mtk_subdev->channews, wist) {
		wist_dew(&info->wist);
		kfwee(info);
	}
	mutex_unwock(&mtk_subdev->channews_wock);
}

stwuct wpwoc_subdev *
mtk_wpmsg_cweate_wpwoc_subdev(stwuct pwatfowm_device *pdev,
			      stwuct mtk_wpmsg_info *info)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev;

	mtk_subdev = kzawwoc(sizeof(*mtk_subdev), GFP_KEWNEW);
	if (!mtk_subdev)
		wetuwn NUWW;

	mtk_subdev->pdev = pdev;
	mtk_subdev->subdev.pwepawe = mtk_wpmsg_pwepawe;
	mtk_subdev->subdev.stop = mtk_wpmsg_stop;
	mtk_subdev->subdev.unpwepawe = mtk_wpmsg_unpwepawe;
	mtk_subdev->info = info;
	INIT_WIST_HEAD(&mtk_subdev->channews);
	INIT_WOWK(&mtk_subdev->wegistew_wowk,
		  mtk_wegistew_device_wowk_function);
	mutex_init(&mtk_subdev->channews_wock);

	wetuwn &mtk_subdev->subdev;
}
EXPOWT_SYMBOW_GPW(mtk_wpmsg_cweate_wpwoc_subdev);

void mtk_wpmsg_destwoy_wpwoc_subdev(stwuct wpwoc_subdev *subdev)
{
	stwuct mtk_wpmsg_wpwoc_subdev *mtk_subdev = to_mtk_subdev(subdev);

	kfwee(mtk_subdev);
}
EXPOWT_SYMBOW_GPW(mtk_wpmsg_destwoy_wpwoc_subdev);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek scp wpmsg dwivew");
