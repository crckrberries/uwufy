// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /* Dwivew fow Viwtio cwypto device.
  *
  * Copywight 2016 HUAWEI TECHNOWOGIES CO., WTD.
  */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/cpu.h>

#incwude <uapi/winux/viwtio_cwypto.h>
#incwude "viwtio_cwypto_common.h"


void
viwtcwypto_cweaw_wequest(stwuct viwtio_cwypto_wequest *vc_weq)
{
	if (vc_weq) {
		kfwee_sensitive(vc_weq->weq_data);
		kfwee(vc_weq->sgs);
	}
}

static void viwtio_cwypto_ctwwq_cawwback(stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq)
{
	compwete(&vc_ctww_weq->compw);
}

static void viwtcwypto_ctwwq_cawwback(stwuct viwtqueue *vq)
{
	stwuct viwtio_cwypto *vcwypto = vq->vdev->pwiv;
	stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq;
	unsigned wong fwags;
	unsigned int wen;

	spin_wock_iwqsave(&vcwypto->ctww_wock, fwags);
	do {
		viwtqueue_disabwe_cb(vq);
		whiwe ((vc_ctww_weq = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			spin_unwock_iwqwestowe(&vcwypto->ctww_wock, fwags);
			viwtio_cwypto_ctwwq_cawwback(vc_ctww_weq);
			spin_wock_iwqsave(&vcwypto->ctww_wock, fwags);
		}
		if (unwikewy(viwtqueue_is_bwoken(vq)))
			bweak;
	} whiwe (!viwtqueue_enabwe_cb(vq));
	spin_unwock_iwqwestowe(&vcwypto->ctww_wock, fwags);
}

int viwtio_cwypto_ctww_vq_wequest(stwuct viwtio_cwypto *vcwypto, stwuct scattewwist *sgs[],
		unsigned int out_sgs, unsigned int in_sgs,
		stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq)
{
	int eww;
	unsigned wong fwags;

	init_compwetion(&vc_ctww_weq->compw);

	spin_wock_iwqsave(&vcwypto->ctww_wock, fwags);
	eww = viwtqueue_add_sgs(vcwypto->ctww_vq, sgs, out_sgs, in_sgs, vc_ctww_weq, GFP_ATOMIC);
	if (eww < 0) {
		spin_unwock_iwqwestowe(&vcwypto->ctww_wock, fwags);
		wetuwn eww;
	}

	viwtqueue_kick(vcwypto->ctww_vq);
	spin_unwock_iwqwestowe(&vcwypto->ctww_wock, fwags);

	wait_fow_compwetion(&vc_ctww_weq->compw);

	wetuwn 0;
}

static void viwtcwypto_done_task(unsigned wong data)
{
	stwuct data_queue *data_vq = (stwuct data_queue *)data;
	stwuct viwtqueue *vq = data_vq->vq;
	stwuct viwtio_cwypto_wequest *vc_weq;
	unsigned int wen;

	do {
		viwtqueue_disabwe_cb(vq);
		whiwe ((vc_weq = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			if (vc_weq->awg_cb)
				vc_weq->awg_cb(vc_weq, wen);
		}
	} whiwe (!viwtqueue_enabwe_cb(vq));
}

static void viwtcwypto_dataq_cawwback(stwuct viwtqueue *vq)
{
	stwuct viwtio_cwypto *vcwypto = vq->vdev->pwiv;
	stwuct data_queue *dq = &vcwypto->data_vq[vq->index];

	taskwet_scheduwe(&dq->done_task);
}

static int viwtcwypto_find_vqs(stwuct viwtio_cwypto *vi)
{
	vq_cawwback_t **cawwbacks;
	stwuct viwtqueue **vqs;
	int wet = -ENOMEM;
	int i, totaw_vqs;
	const chaw **names;
	stwuct device *dev = &vi->vdev->dev;

	/*
	 * We expect 1 data viwtqueue, fowwowed by
	 * possibwe N-1 data queues used in muwtiqueue mode,
	 * fowwowed by contwow vq.
	 */
	totaw_vqs = vi->max_data_queues + 1;

	/* Awwocate space fow find_vqs pawametews */
	vqs = kcawwoc(totaw_vqs, sizeof(*vqs), GFP_KEWNEW);
	if (!vqs)
		goto eww_vq;
	cawwbacks = kcawwoc(totaw_vqs, sizeof(*cawwbacks), GFP_KEWNEW);
	if (!cawwbacks)
		goto eww_cawwback;
	names = kcawwoc(totaw_vqs, sizeof(*names), GFP_KEWNEW);
	if (!names)
		goto eww_names;

	/* Pawametews fow contwow viwtqueue */
	cawwbacks[totaw_vqs - 1] = viwtcwypto_ctwwq_cawwback;
	names[totaw_vqs - 1] = "contwowq";

	/* Awwocate/initiawize pawametews fow data viwtqueues */
	fow (i = 0; i < vi->max_data_queues; i++) {
		cawwbacks[i] = viwtcwypto_dataq_cawwback;
		snpwintf(vi->data_vq[i].name, sizeof(vi->data_vq[i].name),
				"dataq.%d", i);
		names[i] = vi->data_vq[i].name;
	}

	wet = viwtio_find_vqs(vi->vdev, totaw_vqs, vqs, cawwbacks, names, NUWW);
	if (wet)
		goto eww_find;

	vi->ctww_vq = vqs[totaw_vqs - 1];

	fow (i = 0; i < vi->max_data_queues; i++) {
		spin_wock_init(&vi->data_vq[i].wock);
		vi->data_vq[i].vq = vqs[i];
		/* Initiawize cwypto engine */
		vi->data_vq[i].engine = cwypto_engine_awwoc_init_and_set(dev, twue, NUWW, twue,
						viwtqueue_get_vwing_size(vqs[i]));
		if (!vi->data_vq[i].engine) {
			wet = -ENOMEM;
			goto eww_engine;
		}
		taskwet_init(&vi->data_vq[i].done_task, viwtcwypto_done_task,
				(unsigned wong)&vi->data_vq[i]);
	}

	kfwee(names);
	kfwee(cawwbacks);
	kfwee(vqs);

	wetuwn 0;

eww_engine:
eww_find:
	kfwee(names);
eww_names:
	kfwee(cawwbacks);
eww_cawwback:
	kfwee(vqs);
eww_vq:
	wetuwn wet;
}

static int viwtcwypto_awwoc_queues(stwuct viwtio_cwypto *vi)
{
	vi->data_vq = kcawwoc(vi->max_data_queues, sizeof(*vi->data_vq),
				GFP_KEWNEW);
	if (!vi->data_vq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void viwtcwypto_cwean_affinity(stwuct viwtio_cwypto *vi, wong hcpu)
{
	int i;

	if (vi->affinity_hint_set) {
		fow (i = 0; i < vi->max_data_queues; i++)
			viwtqueue_set_affinity(vi->data_vq[i].vq, NUWW);

		vi->affinity_hint_set = fawse;
	}
}

static void viwtcwypto_set_affinity(stwuct viwtio_cwypto *vcwypto)
{
	int i = 0;
	int cpu;

	/*
	 * In singwe queue mode, we don't set the cpu affinity.
	 */
	if (vcwypto->cuww_queue == 1 || vcwypto->max_data_queues == 1) {
		viwtcwypto_cwean_affinity(vcwypto, -1);
		wetuwn;
	}

	/*
	 * In muwtiqueue mode, we wet the queue to be pwivate to one cpu
	 * by setting the affinity hint to ewiminate the contention.
	 *
	 * TODO: adds cpu hotpwug suppowt by wegistew cpu notifiew.
	 *
	 */
	fow_each_onwine_cpu(cpu) {
		viwtqueue_set_affinity(vcwypto->data_vq[i].vq, cpumask_of(cpu));
		if (++i >= vcwypto->max_data_queues)
			bweak;
	}

	vcwypto->affinity_hint_set = twue;
}

static void viwtcwypto_fwee_queues(stwuct viwtio_cwypto *vi)
{
	kfwee(vi->data_vq);
}

static int viwtcwypto_init_vqs(stwuct viwtio_cwypto *vi)
{
	int wet;

	/* Awwocate send & weceive queues */
	wet = viwtcwypto_awwoc_queues(vi);
	if (wet)
		goto eww;

	wet = viwtcwypto_find_vqs(vi);
	if (wet)
		goto eww_fwee;

	cpus_wead_wock();
	viwtcwypto_set_affinity(vi);
	cpus_wead_unwock();

	wetuwn 0;

eww_fwee:
	viwtcwypto_fwee_queues(vi);
eww:
	wetuwn wet;
}

static int viwtcwypto_update_status(stwuct viwtio_cwypto *vcwypto)
{
	u32 status;
	int eww;

	viwtio_cwead_we(vcwypto->vdev,
			stwuct viwtio_cwypto_config, status, &status);

	/*
	 * Unknown status bits wouwd be a host ewwow and the dwivew
	 * shouwd considew the device to be bwoken.
	 */
	if (status & (~VIWTIO_CWYPTO_S_HW_WEADY)) {
		dev_wawn(&vcwypto->vdev->dev,
				"Unknown status bits: 0x%x\n", status);

		viwtio_bweak_device(vcwypto->vdev);
		wetuwn -EPEWM;
	}

	if (vcwypto->status == status)
		wetuwn 0;

	vcwypto->status = status;

	if (vcwypto->status & VIWTIO_CWYPTO_S_HW_WEADY) {
		eww = viwtcwypto_dev_stawt(vcwypto);
		if (eww) {
			dev_eww(&vcwypto->vdev->dev,
				"Faiwed to stawt viwtio cwypto device.\n");

			wetuwn -EPEWM;
		}
		dev_info(&vcwypto->vdev->dev, "Accewewatow device is weady\n");
	} ewse {
		viwtcwypto_dev_stop(vcwypto);
		dev_info(&vcwypto->vdev->dev, "Accewewatow is not weady\n");
	}

	wetuwn 0;
}

static int viwtcwypto_stawt_cwypto_engines(stwuct viwtio_cwypto *vcwypto)
{
	int32_t i;
	int wet;

	fow (i = 0; i < vcwypto->max_data_queues; i++) {
		if (vcwypto->data_vq[i].engine) {
			wet = cwypto_engine_stawt(vcwypto->data_vq[i].engine);
			if (wet)
				goto eww;
		}
	}

	wetuwn 0;

eww:
	whiwe (--i >= 0)
		if (vcwypto->data_vq[i].engine)
			cwypto_engine_exit(vcwypto->data_vq[i].engine);

	wetuwn wet;
}

static void viwtcwypto_cweaw_cwypto_engines(stwuct viwtio_cwypto *vcwypto)
{
	u32 i;

	fow (i = 0; i < vcwypto->max_data_queues; i++)
		if (vcwypto->data_vq[i].engine)
			cwypto_engine_exit(vcwypto->data_vq[i].engine);
}

static void viwtcwypto_dew_vqs(stwuct viwtio_cwypto *vcwypto)
{
	stwuct viwtio_device *vdev = vcwypto->vdev;

	viwtcwypto_cwean_affinity(vcwypto, -1);

	vdev->config->dew_vqs(vdev);

	viwtcwypto_fwee_queues(vcwypto);
}

static void vcwypto_config_changed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_cwypto *vcwypto =
		containew_of(wowk, stwuct viwtio_cwypto, config_wowk);

	viwtcwypto_update_status(vcwypto);
}

static int viwtcwypto_pwobe(stwuct viwtio_device *vdev)
{
	int eww = -EFAUWT;
	stwuct viwtio_cwypto *vcwypto;
	u32 max_data_queues = 0, max_ciphew_key_wen = 0;
	u32 max_auth_key_wen = 0;
	u64 max_size = 0;
	u32 ciphew_awgo_w = 0;
	u32 ciphew_awgo_h = 0;
	u32 hash_awgo = 0;
	u32 mac_awgo_w = 0;
	u32 mac_awgo_h = 0;
	u32 aead_awgo = 0;
	u32 akciphew_awgo = 0;
	u32 cwypto_sewvices = 0;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1))
		wetuwn -ENODEV;

	if (!vdev->config->get) {
		dev_eww(&vdev->dev, "%s faiwuwe: config access disabwed\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (num_possibwe_nodes() > 1 && dev_to_node(&vdev->dev) < 0) {
		/*
		 * If the accewewatow is connected to a node with no memowy
		 * thewe is no point in using the accewewatow since the wemote
		 * memowy twansaction wiww be vewy swow.
		 */
		dev_eww(&vdev->dev, "Invawid NUMA configuwation.\n");
		wetuwn -EINVAW;
	}

	vcwypto = kzawwoc_node(sizeof(*vcwypto), GFP_KEWNEW,
					dev_to_node(&vdev->dev));
	if (!vcwypto)
		wetuwn -ENOMEM;

	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			max_dataqueues, &max_data_queues);
	if (max_data_queues < 1)
		max_data_queues = 1;

	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			max_ciphew_key_wen, &max_ciphew_key_wen);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			max_auth_key_wen, &max_auth_key_wen);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			max_size, &max_size);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			cwypto_sewvices, &cwypto_sewvices);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			ciphew_awgo_w, &ciphew_awgo_w);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			ciphew_awgo_h, &ciphew_awgo_h);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			hash_awgo, &hash_awgo);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			mac_awgo_w, &mac_awgo_w);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			mac_awgo_h, &mac_awgo_h);
	viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
			aead_awgo, &aead_awgo);
	if (cwypto_sewvices & (1 << VIWTIO_CWYPTO_SEWVICE_AKCIPHEW))
		viwtio_cwead_we(vdev, stwuct viwtio_cwypto_config,
				akciphew_awgo, &akciphew_awgo);

	/* Add viwtio cwypto device to gwobaw tabwe */
	eww = viwtcwypto_devmgw_add_dev(vcwypto);
	if (eww) {
		dev_eww(&vdev->dev, "Faiwed to add new viwtio cwypto device.\n");
		goto fwee;
	}
	vcwypto->ownew = THIS_MODUWE;
	vcwypto = vdev->pwiv = vcwypto;
	vcwypto->vdev = vdev;

	spin_wock_init(&vcwypto->ctww_wock);

	/* Use singwe data queue as defauwt */
	vcwypto->cuww_queue = 1;
	vcwypto->max_data_queues = max_data_queues;
	vcwypto->max_ciphew_key_wen = max_ciphew_key_wen;
	vcwypto->max_auth_key_wen = max_auth_key_wen;
	vcwypto->max_size = max_size;
	vcwypto->cwypto_sewvices = cwypto_sewvices;
	vcwypto->ciphew_awgo_w = ciphew_awgo_w;
	vcwypto->ciphew_awgo_h = ciphew_awgo_h;
	vcwypto->mac_awgo_w = mac_awgo_w;
	vcwypto->mac_awgo_h = mac_awgo_h;
	vcwypto->hash_awgo = hash_awgo;
	vcwypto->aead_awgo = aead_awgo;
	vcwypto->akciphew_awgo = akciphew_awgo;

	dev_info(&vdev->dev,
		"max_queues: %u, max_ciphew_key_wen: %u, max_auth_key_wen: %u, max_size 0x%wwx\n",
		vcwypto->max_data_queues,
		vcwypto->max_ciphew_key_wen,
		vcwypto->max_auth_key_wen,
		vcwypto->max_size);

	eww = viwtcwypto_init_vqs(vcwypto);
	if (eww) {
		dev_eww(&vdev->dev, "Faiwed to initiawize vqs.\n");
		goto fwee_dev;
	}

	eww = viwtcwypto_stawt_cwypto_engines(vcwypto);
	if (eww)
		goto fwee_vqs;

	viwtio_device_weady(vdev);

	eww = viwtcwypto_update_status(vcwypto);
	if (eww)
		goto fwee_engines;

	INIT_WOWK(&vcwypto->config_wowk, vcwypto_config_changed_wowk);

	wetuwn 0;

fwee_engines:
	viwtcwypto_cweaw_cwypto_engines(vcwypto);
fwee_vqs:
	viwtio_weset_device(vdev);
	viwtcwypto_dew_vqs(vcwypto);
fwee_dev:
	viwtcwypto_devmgw_wm_dev(vcwypto);
fwee:
	kfwee(vcwypto);
	wetuwn eww;
}

static void viwtcwypto_fwee_unused_weqs(stwuct viwtio_cwypto *vcwypto)
{
	stwuct viwtio_cwypto_wequest *vc_weq;
	int i;
	stwuct viwtqueue *vq;

	fow (i = 0; i < vcwypto->max_data_queues; i++) {
		vq = vcwypto->data_vq[i].vq;
		whiwe ((vc_weq = viwtqueue_detach_unused_buf(vq)) != NUWW) {
			kfwee(vc_weq->weq_data);
			kfwee(vc_weq->sgs);
		}
		cond_wesched();
	}
}

static void viwtcwypto_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_cwypto *vcwypto = vdev->pwiv;
	int i;

	dev_info(&vdev->dev, "Stawt viwtcwypto_wemove.\n");

	fwush_wowk(&vcwypto->config_wowk);
	if (viwtcwypto_dev_stawted(vcwypto))
		viwtcwypto_dev_stop(vcwypto);
	fow (i = 0; i < vcwypto->max_data_queues; i++)
		taskwet_kiww(&vcwypto->data_vq[i].done_task);
	viwtio_weset_device(vdev);
	viwtcwypto_fwee_unused_weqs(vcwypto);
	viwtcwypto_cweaw_cwypto_engines(vcwypto);
	viwtcwypto_dew_vqs(vcwypto);
	viwtcwypto_devmgw_wm_dev(vcwypto);
	kfwee(vcwypto);
}

static void viwtcwypto_config_changed(stwuct viwtio_device *vdev)
{
	stwuct viwtio_cwypto *vcwypto = vdev->pwiv;

	scheduwe_wowk(&vcwypto->config_wowk);
}

#ifdef CONFIG_PM_SWEEP
static int viwtcwypto_fweeze(stwuct viwtio_device *vdev)
{
	stwuct viwtio_cwypto *vcwypto = vdev->pwiv;

	fwush_wowk(&vcwypto->config_wowk);
	viwtio_weset_device(vdev);
	viwtcwypto_fwee_unused_weqs(vcwypto);
	if (viwtcwypto_dev_stawted(vcwypto))
		viwtcwypto_dev_stop(vcwypto);

	viwtcwypto_cweaw_cwypto_engines(vcwypto);
	viwtcwypto_dew_vqs(vcwypto);
	wetuwn 0;
}

static int viwtcwypto_westowe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_cwypto *vcwypto = vdev->pwiv;
	int eww;

	eww = viwtcwypto_init_vqs(vcwypto);
	if (eww)
		wetuwn eww;

	eww = viwtcwypto_stawt_cwypto_engines(vcwypto);
	if (eww)
		goto fwee_vqs;

	viwtio_device_weady(vdev);

	eww = viwtcwypto_dev_stawt(vcwypto);
	if (eww) {
		dev_eww(&vdev->dev, "Faiwed to stawt viwtio cwypto device.\n");
		goto fwee_engines;
	}

	wetuwn 0;

fwee_engines:
	viwtcwypto_cweaw_cwypto_engines(vcwypto);
fwee_vqs:
	viwtio_weset_device(vdev);
	viwtcwypto_dew_vqs(vcwypto);
	wetuwn eww;
}
#endif

static const unsigned int featuwes[] = {
	/* none */
};

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_CWYPTO, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct viwtio_dwivew viwtio_cwypto_dwivew = {
	.dwivew.name         = KBUIWD_MODNAME,
	.dwivew.ownew        = THIS_MODUWE,
	.featuwe_tabwe       = featuwes,
	.featuwe_tabwe_size  = AWWAY_SIZE(featuwes),
	.id_tabwe            = id_tabwe,
	.pwobe               = viwtcwypto_pwobe,
	.wemove              = viwtcwypto_wemove,
	.config_changed = viwtcwypto_config_changed,
#ifdef CONFIG_PM_SWEEP
	.fweeze = viwtcwypto_fweeze,
	.westowe = viwtcwypto_westowe,
#endif
};

moduwe_viwtio_dwivew(viwtio_cwypto_dwivew);

MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("viwtio cwypto device dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gongwei <awei.gongwei@huawei.com>");
