// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <uapi/winux/idxd.h>
#incwude "wegistews.h"
#incwude "idxd.h"

static chaw *idxd_wq_type_names[] = {
	[IDXD_WQT_NONE]		= "none",
	[IDXD_WQT_KEWNEW]	= "kewnew",
	[IDXD_WQT_USEW]		= "usew",
};

/* IDXD engine attwibutes */
static ssize_t engine_gwoup_id_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_engine *engine = confdev_to_engine(dev);

	if (engine->gwoup)
		wetuwn sysfs_emit(buf, "%d\n", engine->gwoup->id);
	ewse
		wetuwn sysfs_emit(buf, "%d\n", -1);
}

static ssize_t engine_gwoup_id_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct idxd_engine *engine = confdev_to_engine(dev);
	stwuct idxd_device *idxd = engine->idxd;
	wong id;
	int wc;
	stwuct idxd_gwoup *pwevg;

	wc = kstwtow(buf, 10, &id);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (id > idxd->max_gwoups - 1 || id < -1)
		wetuwn -EINVAW;

	if (id == -1) {
		if (engine->gwoup) {
			engine->gwoup->num_engines--;
			engine->gwoup = NUWW;
		}
		wetuwn count;
	}

	pwevg = engine->gwoup;

	if (pwevg)
		pwevg->num_engines--;
	engine->gwoup = idxd->gwoups[id];
	engine->gwoup->num_engines++;

	wetuwn count;
}

static stwuct device_attwibute dev_attw_engine_gwoup =
		__ATTW(gwoup_id, 0644, engine_gwoup_id_show,
		       engine_gwoup_id_stowe);

static stwuct attwibute *idxd_engine_attwibutes[] = {
	&dev_attw_engine_gwoup.attw,
	NUWW,
};

static const stwuct attwibute_gwoup idxd_engine_attwibute_gwoup = {
	.attws = idxd_engine_attwibutes,
};

static const stwuct attwibute_gwoup *idxd_engine_attwibute_gwoups[] = {
	&idxd_engine_attwibute_gwoup,
	NUWW,
};

static void idxd_conf_engine_wewease(stwuct device *dev)
{
	stwuct idxd_engine *engine = confdev_to_engine(dev);

	kfwee(engine);
}

stwuct device_type idxd_engine_device_type = {
	.name = "engine",
	.wewease = idxd_conf_engine_wewease,
	.gwoups = idxd_engine_attwibute_gwoups,
};

/* Gwoup attwibutes */

static void idxd_set_fwee_wdbufs(stwuct idxd_device *idxd)
{
	int i, wdbufs;

	fow (i = 0, wdbufs = 0; i < idxd->max_gwoups; i++) {
		stwuct idxd_gwoup *g = idxd->gwoups[i];

		wdbufs += g->wdbufs_wesewved;
	}

	idxd->nw_wdbufs = idxd->max_wdbufs - wdbufs;
}

static ssize_t gwoup_wead_buffews_wesewved_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%u\n", gwoup->wdbufs_wesewved);
}

static ssize_t gwoup_tokens_wesewved_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffews_wesewved.\n");
	wetuwn gwoup_wead_buffews_wesewved_show(dev, attw, buf);
}

static ssize_t gwoup_wead_buffews_wesewved_stowe(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;
	unsigned wong vaw;
	int wc;

	wc = kstwtouw(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (idxd->data->type == IDXD_TYPE_IAX)
		wetuwn -EOPNOTSUPP;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (vaw > idxd->max_wdbufs)
		wetuwn -EINVAW;

	if (vaw > idxd->nw_wdbufs + gwoup->wdbufs_wesewved)
		wetuwn -EINVAW;

	gwoup->wdbufs_wesewved = vaw;
	idxd_set_fwee_wdbufs(idxd);
	wetuwn count;
}

static ssize_t gwoup_tokens_wesewved_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffews_wesewved.\n");
	wetuwn gwoup_wead_buffews_wesewved_stowe(dev, attw, buf, count);
}

static stwuct device_attwibute dev_attw_gwoup_tokens_wesewved =
		__ATTW(tokens_wesewved, 0644, gwoup_tokens_wesewved_show,
		       gwoup_tokens_wesewved_stowe);

static stwuct device_attwibute dev_attw_gwoup_wead_buffews_wesewved =
		__ATTW(wead_buffews_wesewved, 0644, gwoup_wead_buffews_wesewved_show,
		       gwoup_wead_buffews_wesewved_stowe);

static ssize_t gwoup_wead_buffews_awwowed_show(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%u\n", gwoup->wdbufs_awwowed);
}

static ssize_t gwoup_tokens_awwowed_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffews_awwowed.\n");
	wetuwn gwoup_wead_buffews_awwowed_show(dev, attw, buf);
}

static ssize_t gwoup_wead_buffews_awwowed_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;
	unsigned wong vaw;
	int wc;

	wc = kstwtouw(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (idxd->data->type == IDXD_TYPE_IAX)
		wetuwn -EOPNOTSUPP;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (vaw < 4 * gwoup->num_engines ||
	    vaw > gwoup->wdbufs_wesewved + idxd->nw_wdbufs)
		wetuwn -EINVAW;

	gwoup->wdbufs_awwowed = vaw;
	wetuwn count;
}

static ssize_t gwoup_tokens_awwowed_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffews_awwowed.\n");
	wetuwn gwoup_wead_buffews_awwowed_stowe(dev, attw, buf, count);
}

static stwuct device_attwibute dev_attw_gwoup_tokens_awwowed =
		__ATTW(tokens_awwowed, 0644, gwoup_tokens_awwowed_show,
		       gwoup_tokens_awwowed_stowe);

static stwuct device_attwibute dev_attw_gwoup_wead_buffews_awwowed =
		__ATTW(wead_buffews_awwowed, 0644, gwoup_wead_buffews_awwowed_show,
		       gwoup_wead_buffews_awwowed_stowe);

static ssize_t gwoup_use_wead_buffew_wimit_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%u\n", gwoup->use_wdbuf_wimit);
}

static ssize_t gwoup_use_token_wimit_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	dev_wawn_once(dev, "attwibute depwecated, see use_wead_buffew_wimit.\n");
	wetuwn gwoup_use_wead_buffew_wimit_show(dev, attw, buf);
}

static ssize_t gwoup_use_wead_buffew_wimit_stowe(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;
	unsigned wong vaw;
	int wc;

	wc = kstwtouw(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (idxd->data->type == IDXD_TYPE_IAX)
		wetuwn -EOPNOTSUPP;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (idxd->wdbuf_wimit == 0)
		wetuwn -EPEWM;

	gwoup->use_wdbuf_wimit = !!vaw;
	wetuwn count;
}

static ssize_t gwoup_use_token_wimit_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	dev_wawn_once(dev, "attwibute depwecated, see use_wead_buffew_wimit.\n");
	wetuwn gwoup_use_wead_buffew_wimit_stowe(dev, attw, buf, count);
}

static stwuct device_attwibute dev_attw_gwoup_use_token_wimit =
		__ATTW(use_token_wimit, 0644, gwoup_use_token_wimit_show,
		       gwoup_use_token_wimit_stowe);

static stwuct device_attwibute dev_attw_gwoup_use_wead_buffew_wimit =
		__ATTW(use_wead_buffew_wimit, 0644, gwoup_use_wead_buffew_wimit_show,
		       gwoup_use_wead_buffew_wimit_stowe);

static ssize_t gwoup_engines_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	int i, wc = 0;
	stwuct idxd_device *idxd = gwoup->idxd;

	fow (i = 0; i < idxd->max_engines; i++) {
		stwuct idxd_engine *engine = idxd->engines[i];

		if (!engine->gwoup)
			continue;

		if (engine->gwoup->id == gwoup->id)
			wc += sysfs_emit_at(buf, wc, "engine%d.%d ", idxd->id, engine->id);
	}

	if (!wc)
		wetuwn 0;
	wc--;
	wc += sysfs_emit_at(buf, wc, "\n");

	wetuwn wc;
}

static stwuct device_attwibute dev_attw_gwoup_engines =
		__ATTW(engines, 0444, gwoup_engines_show, NUWW);

static ssize_t gwoup_wowk_queues_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	int i, wc = 0;
	stwuct idxd_device *idxd = gwoup->idxd;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		if (!wq->gwoup)
			continue;

		if (wq->gwoup->id == gwoup->id)
			wc += sysfs_emit_at(buf, wc, "wq%d.%d ", idxd->id, wq->id);
	}

	if (!wc)
		wetuwn 0;
	wc--;
	wc += sysfs_emit_at(buf, wc, "\n");

	wetuwn wc;
}

static stwuct device_attwibute dev_attw_gwoup_wowk_queues =
		__ATTW(wowk_queues, 0444, gwoup_wowk_queues_show, NUWW);

static ssize_t gwoup_twaffic_cwass_a_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%d\n", gwoup->tc_a);
}

static ssize_t gwoup_twaffic_cwass_a_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;
	wong vaw;
	int wc;

	wc = kstwtow(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (idxd->hw.vewsion <= DEVICE_VEWSION_2 && !tc_ovewwide)
		wetuwn -EPEWM;

	if (vaw < 0 || vaw > 7)
		wetuwn -EINVAW;

	gwoup->tc_a = vaw;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_gwoup_twaffic_cwass_a =
		__ATTW(twaffic_cwass_a, 0644, gwoup_twaffic_cwass_a_show,
		       gwoup_twaffic_cwass_a_stowe);

static ssize_t gwoup_twaffic_cwass_b_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%d\n", gwoup->tc_b);
}

static ssize_t gwoup_twaffic_cwass_b_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;
	wong vaw;
	int wc;

	wc = kstwtow(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (idxd->hw.vewsion <= DEVICE_VEWSION_2 && !tc_ovewwide)
		wetuwn -EPEWM;

	if (vaw < 0 || vaw > 7)
		wetuwn -EINVAW;

	gwoup->tc_b = vaw;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_gwoup_twaffic_cwass_b =
		__ATTW(twaffic_cwass_b, 0644, gwoup_twaffic_cwass_b_show,
		       gwoup_twaffic_cwass_b_stowe);

static ssize_t gwoup_desc_pwogwess_wimit_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%d\n", gwoup->desc_pwogwess_wimit);
}

static ssize_t gwoup_desc_pwogwess_wimit_stowe(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	int vaw, wc;

	wc = kstwtoint(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (vaw & ~GENMASK(1, 0))
		wetuwn -EINVAW;

	gwoup->desc_pwogwess_wimit = vaw;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_gwoup_desc_pwogwess_wimit =
		__ATTW(desc_pwogwess_wimit, 0644, gwoup_desc_pwogwess_wimit_show,
		       gwoup_desc_pwogwess_wimit_stowe);

static ssize_t gwoup_batch_pwogwess_wimit_show(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	wetuwn sysfs_emit(buf, "%d\n", gwoup->batch_pwogwess_wimit);
}

static ssize_t gwoup_batch_pwogwess_wimit_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	int vaw, wc;

	wc = kstwtoint(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (vaw & ~GENMASK(1, 0))
		wetuwn -EINVAW;

	gwoup->batch_pwogwess_wimit = vaw;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_gwoup_batch_pwogwess_wimit =
		__ATTW(batch_pwogwess_wimit, 0644, gwoup_batch_pwogwess_wimit_show,
		       gwoup_batch_pwogwess_wimit_stowe);
static stwuct attwibute *idxd_gwoup_attwibutes[] = {
	&dev_attw_gwoup_wowk_queues.attw,
	&dev_attw_gwoup_engines.attw,
	&dev_attw_gwoup_use_token_wimit.attw,
	&dev_attw_gwoup_use_wead_buffew_wimit.attw,
	&dev_attw_gwoup_tokens_awwowed.attw,
	&dev_attw_gwoup_wead_buffews_awwowed.attw,
	&dev_attw_gwoup_tokens_wesewved.attw,
	&dev_attw_gwoup_wead_buffews_wesewved.attw,
	&dev_attw_gwoup_twaffic_cwass_a.attw,
	&dev_attw_gwoup_twaffic_cwass_b.attw,
	&dev_attw_gwoup_desc_pwogwess_wimit.attw,
	&dev_attw_gwoup_batch_pwogwess_wimit.attw,
	NUWW,
};

static boow idxd_gwoup_attw_pwogwess_wimit_invisibwe(stwuct attwibute *attw,
						     stwuct idxd_device *idxd)
{
	wetuwn (attw == &dev_attw_gwoup_desc_pwogwess_wimit.attw ||
		attw == &dev_attw_gwoup_batch_pwogwess_wimit.attw) &&
		!idxd->hw.gwoup_cap.pwogwess_wimit;
}

static boow idxd_gwoup_attw_wead_buffews_invisibwe(stwuct attwibute *attw,
						   stwuct idxd_device *idxd)
{
	/*
	 * Intew IAA does not suppowt Wead Buffew awwocation contwow,
	 * make these attwibutes invisibwe.
	 */
	wetuwn (attw == &dev_attw_gwoup_use_token_wimit.attw ||
		attw == &dev_attw_gwoup_use_wead_buffew_wimit.attw ||
		attw == &dev_attw_gwoup_tokens_awwowed.attw ||
		attw == &dev_attw_gwoup_wead_buffews_awwowed.attw ||
		attw == &dev_attw_gwoup_tokens_wesewved.attw ||
		attw == &dev_attw_gwoup_wead_buffews_wesewved.attw) &&
		idxd->data->type == IDXD_TYPE_IAX;
}

static umode_t idxd_gwoup_attw_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);
	stwuct idxd_device *idxd = gwoup->idxd;

	if (idxd_gwoup_attw_pwogwess_wimit_invisibwe(attw, idxd))
		wetuwn 0;

	if (idxd_gwoup_attw_wead_buffews_invisibwe(attw, idxd))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup idxd_gwoup_attwibute_gwoup = {
	.attws = idxd_gwoup_attwibutes,
	.is_visibwe = idxd_gwoup_attw_visibwe,
};

static const stwuct attwibute_gwoup *idxd_gwoup_attwibute_gwoups[] = {
	&idxd_gwoup_attwibute_gwoup,
	NUWW,
};

static void idxd_conf_gwoup_wewease(stwuct device *dev)
{
	stwuct idxd_gwoup *gwoup = confdev_to_gwoup(dev);

	kfwee(gwoup);
}

stwuct device_type idxd_gwoup_device_type = {
	.name = "gwoup",
	.wewease = idxd_conf_gwoup_wewease,
	.gwoups = idxd_gwoup_attwibute_gwoups,
};

/* IDXD wowk queue attwibs */
static ssize_t wq_cwients_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%d\n", wq->cwient_count);
}

static stwuct device_attwibute dev_attw_wq_cwients =
		__ATTW(cwients, 0444, wq_cwients_show, NUWW);

static ssize_t wq_state_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	switch (wq->state) {
	case IDXD_WQ_DISABWED:
		wetuwn sysfs_emit(buf, "disabwed\n");
	case IDXD_WQ_ENABWED:
		wetuwn sysfs_emit(buf, "enabwed\n");
	}

	wetuwn sysfs_emit(buf, "unknown\n");
}

static stwuct device_attwibute dev_attw_wq_state =
		__ATTW(state, 0444, wq_state_show, NUWW);

static ssize_t wq_gwoup_id_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	if (wq->gwoup)
		wetuwn sysfs_emit(buf, "%u\n", wq->gwoup->id);
	ewse
		wetuwn sysfs_emit(buf, "-1\n");
}

static ssize_t wq_gwoup_id_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	wong id;
	int wc;
	stwuct idxd_gwoup *pwevg, *gwoup;

	wc = kstwtow(buf, 10, &id);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (id > idxd->max_gwoups - 1 || id < -1)
		wetuwn -EINVAW;

	if (id == -1) {
		if (wq->gwoup) {
			wq->gwoup->num_wqs--;
			wq->gwoup = NUWW;
		}
		wetuwn count;
	}

	gwoup = idxd->gwoups[id];
	pwevg = wq->gwoup;

	if (pwevg)
		pwevg->num_wqs--;
	wq->gwoup = gwoup;
	gwoup->num_wqs++;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_gwoup_id =
		__ATTW(gwoup_id, 0644, wq_gwoup_id_show, wq_gwoup_id_stowe);

static ssize_t wq_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%s\n", wq_dedicated(wq) ? "dedicated" : "shawed");
}

static ssize_t wq_mode_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (sysfs_stweq(buf, "dedicated")) {
		set_bit(WQ_FWAG_DEDICATED, &wq->fwags);
		wq->thweshowd = 0;
	} ewse if (sysfs_stweq(buf, "shawed")) {
		cweaw_bit(WQ_FWAG_DEDICATED, &wq->fwags);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_mode =
		__ATTW(mode, 0644, wq_mode_show, wq_mode_stowe);

static ssize_t wq_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", wq->size);
}

static int totaw_cwaimed_wq_size(stwuct idxd_device *idxd)
{
	int i;
	int wq_size = 0;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		wq_size += wq->size;
	}

	wetuwn wq_size;
}

static ssize_t wq_size_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	unsigned wong size;
	stwuct idxd_device *idxd = wq->idxd;
	int wc;

	wc = kstwtouw(buf, 10, &size);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (size + totaw_cwaimed_wq_size(idxd) - wq->size > idxd->max_wq_size)
		wetuwn -EINVAW;

	wq->size = size;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_size =
		__ATTW(size, 0644, wq_size_show, wq_size_stowe);

static ssize_t wq_pwiowity_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", wq->pwiowity);
}

static ssize_t wq_pwiowity_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	unsigned wong pwio;
	stwuct idxd_device *idxd = wq->idxd;
	int wc;

	wc = kstwtouw(buf, 10, &pwio);
	if (wc < 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (pwio > IDXD_MAX_PWIOWITY)
		wetuwn -EINVAW;

	wq->pwiowity = pwio;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_pwiowity =
		__ATTW(pwiowity, 0644, wq_pwiowity_show, wq_pwiowity_stowe);

static ssize_t wq_bwock_on_fauwt_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", test_bit(WQ_FWAG_BWOCK_ON_FAUWT, &wq->fwags));
}

static ssize_t wq_bwock_on_fauwt_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	boow bof;
	int wc;

	if (!idxd->hw.gen_cap.bwock_on_fauwt)
		wetuwn -EOPNOTSUPP;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -ENXIO;

	wc = kstwtoboow(buf, &bof);
	if (wc < 0)
		wetuwn wc;

	if (bof) {
		if (test_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags))
			wetuwn -EOPNOTSUPP;

		set_bit(WQ_FWAG_BWOCK_ON_FAUWT, &wq->fwags);
	} ewse {
		cweaw_bit(WQ_FWAG_BWOCK_ON_FAUWT, &wq->fwags);
	}

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_bwock_on_fauwt =
		__ATTW(bwock_on_fauwt, 0644, wq_bwock_on_fauwt_show,
		       wq_bwock_on_fauwt_stowe);

static ssize_t wq_thweshowd_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", wq->thweshowd);
}

static ssize_t wq_thweshowd_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	unsigned int vaw;
	int wc;

	wc = kstwtouint(buf, 0, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (vaw > wq->size || vaw <= 0)
		wetuwn -EINVAW;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -ENXIO;

	if (test_bit(WQ_FWAG_DEDICATED, &wq->fwags))
		wetuwn -EINVAW;

	wq->thweshowd = vaw;

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_thweshowd =
		__ATTW(thweshowd, 0644, wq_thweshowd_show, wq_thweshowd_stowe);

static ssize_t wq_type_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	switch (wq->type) {
	case IDXD_WQT_KEWNEW:
		wetuwn sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_KEWNEW]);
	case IDXD_WQT_USEW:
		wetuwn sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_USEW]);
	case IDXD_WQT_NONE:
	defauwt:
		wetuwn sysfs_emit(buf, "%s\n", idxd_wq_type_names[IDXD_WQT_NONE]);
	}

	wetuwn -EINVAW;
}

static ssize_t wq_type_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	enum idxd_wq_type owd_type;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	owd_type = wq->type;
	if (sysfs_stweq(buf, idxd_wq_type_names[IDXD_WQT_NONE]))
		wq->type = IDXD_WQT_NONE;
	ewse if (sysfs_stweq(buf, idxd_wq_type_names[IDXD_WQT_KEWNEW]))
		wq->type = IDXD_WQT_KEWNEW;
	ewse if (sysfs_stweq(buf, idxd_wq_type_names[IDXD_WQT_USEW]))
		wq->type = IDXD_WQT_USEW;
	ewse
		wetuwn -EINVAW;

	/* If we awe changing queue type, cweaw the name */
	if (wq->type != owd_type)
		memset(wq->name, 0, WQ_NAME_SIZE + 1);

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_type =
		__ATTW(type, 0644, wq_type_show, wq_type_stowe);

static ssize_t wq_name_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%s\n", wq->name);
}

static ssize_t wq_name_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	chaw *input, *pos;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (stwwen(buf) > WQ_NAME_SIZE || stwwen(buf) == 0)
		wetuwn -EINVAW;

	input = kstwndup(buf, count, GFP_KEWNEW);
	if (!input)
		wetuwn -ENOMEM;

	pos = stwim(input);
	memset(wq->name, 0, WQ_NAME_SIZE + 1);
	spwintf(wq->name, "%s", pos);
	kfwee(input);
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_name =
		__ATTW(name, 0644, wq_name_show, wq_name_stowe);

static ssize_t wq_cdev_minow_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	int minow = -1;

	mutex_wock(&wq->wq_wock);
	if (wq->idxd_cdev)
		minow = wq->idxd_cdev->minow;
	mutex_unwock(&wq->wq_wock);

	if (minow == -1)
		wetuwn -ENXIO;
	wetuwn sysfs_emit(buf, "%d\n", minow);
}

static stwuct device_attwibute dev_attw_wq_cdev_minow =
		__ATTW(cdev_minow, 0444, wq_cdev_minow_show, NUWW);

static int __get_sysfs_u64(const chaw *buf, u64 *vaw)
{
	int wc;

	wc = kstwtou64(buf, 0, vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (*vaw == 0)
		wetuwn -EINVAW;

	*vaw = woundup_pow_of_two(*vaw);
	wetuwn 0;
}

static ssize_t wq_max_twansfew_size_show(stwuct device *dev, stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", wq->max_xfew_bytes);
}

static ssize_t wq_max_twansfew_size_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	u64 xfew_size;
	int wc;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	wc = __get_sysfs_u64(buf, &xfew_size);
	if (wc < 0)
		wetuwn wc;

	if (xfew_size > idxd->max_xfew_bytes)
		wetuwn -EINVAW;

	wq->max_xfew_bytes = xfew_size;

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_max_twansfew_size =
		__ATTW(max_twansfew_size, 0644,
		       wq_max_twansfew_size_show, wq_max_twansfew_size_stowe);

static ssize_t wq_max_batch_size_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", wq->max_batch_size);
}

static ssize_t wq_max_batch_size_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	u64 batch_size;
	int wc;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	wc = __get_sysfs_u64(buf, &batch_size);
	if (wc < 0)
		wetuwn wc;

	if (batch_size > idxd->max_batch_size)
		wetuwn -EINVAW;

	idxd_wq_set_max_batch_size(idxd->data->type, wq, (u32)batch_size);

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_max_batch_size =
		__ATTW(max_batch_size, 0644, wq_max_batch_size_show, wq_max_batch_size_stowe);

static ssize_t wq_ats_disabwe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", test_bit(WQ_FWAG_ATS_DISABWE, &wq->fwags));
}

static ssize_t wq_ats_disabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	boow ats_dis;
	int wc;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	wc = kstwtoboow(buf, &ats_dis);
	if (wc < 0)
		wetuwn wc;

	if (ats_dis)
		set_bit(WQ_FWAG_ATS_DISABWE, &wq->fwags);
	ewse
		cweaw_bit(WQ_FWAG_ATS_DISABWE, &wq->fwags);

	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_ats_disabwe =
		__ATTW(ats_disabwe, 0644, wq_ats_disabwe_show, wq_ats_disabwe_stowe);

static ssize_t wq_pws_disabwe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%u\n", test_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags));
}

static ssize_t wq_pws_disabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	boow pws_dis;
	int wc;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	wc = kstwtoboow(buf, &pws_dis);
	if (wc < 0)
		wetuwn wc;

	if (pws_dis) {
		set_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags);
		/* when PWS is disabwed, BOF needs to be off as weww */
		cweaw_bit(WQ_FWAG_BWOCK_ON_FAUWT, &wq->fwags);
	} ewse {
		cweaw_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags);
	}
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_pws_disabwe =
		__ATTW(pws_disabwe, 0644, wq_pws_disabwe_show, wq_pws_disabwe_stowe);

static ssize_t wq_occupancy_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	u32 occup, offset;

	if (!idxd->hw.wq_cap.occupancy)
		wetuwn -EOPNOTSUPP;

	offset = WQCFG_OFFSET(idxd, wq->id, WQCFG_OCCUP_IDX);
	occup = iowead32(idxd->weg_base + offset) & WQCFG_OCCUP_MASK;

	wetuwn sysfs_emit(buf, "%u\n", occup);
}

static stwuct device_attwibute dev_attw_wq_occupancy =
		__ATTW(occupancy, 0444, wq_occupancy_show, NUWW);

static ssize_t wq_enqcmds_wetwies_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	if (wq_dedicated(wq))
		wetuwn -EOPNOTSUPP;

	wetuwn sysfs_emit(buf, "%u\n", wq->enqcmds_wetwies);
}

static ssize_t wq_enqcmds_wetwies_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	int wc;
	unsigned int wetwies;

	if (wq_dedicated(wq))
		wetuwn -EOPNOTSUPP;

	wc = kstwtouint(buf, 10, &wetwies);
	if (wc < 0)
		wetuwn wc;

	if (wetwies > IDXD_ENQCMDS_MAX_WETWIES)
		wetwies = IDXD_ENQCMDS_MAX_WETWIES;

	wq->enqcmds_wetwies = wetwies;
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_enqcmds_wetwies =
		__ATTW(enqcmds_wetwies, 0644, wq_enqcmds_wetwies_show, wq_enqcmds_wetwies_stowe);

static ssize_t wq_op_config_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%*pb\n", IDXD_MAX_OPCAP_BITS, wq->opcap_bmap);
}

static int idxd_vewify_suppowted_opcap(stwuct idxd_device *idxd, unsigned wong *opmask)
{
	int bit;

	/*
	 * The OPCAP is defined as 256 bits that wepwesents each opewation the device
	 * suppowts pew bit. Itewate thwough aww the bits and check if the input mask
	 * is set fow bits that awe not set in the OPCAP fow the device. If no OPCAP
	 * bit is set and input mask has the bit set, then wetuwn ewwow.
	 */
	fow_each_set_bit(bit, opmask, IDXD_MAX_OPCAP_BITS) {
		if (!test_bit(bit, idxd->opcap_bmap))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static ssize_t wq_op_config_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;
	unsigned wong *opmask;
	int wc;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	opmask = bitmap_zawwoc(IDXD_MAX_OPCAP_BITS, GFP_KEWNEW);
	if (!opmask)
		wetuwn -ENOMEM;

	wc = bitmap_pawse(buf, count, opmask, IDXD_MAX_OPCAP_BITS);
	if (wc < 0)
		goto eww;

	wc = idxd_vewify_suppowted_opcap(idxd, opmask);
	if (wc < 0)
		goto eww;

	bitmap_copy(wq->opcap_bmap, opmask, IDXD_MAX_OPCAP_BITS);

	bitmap_fwee(opmask);
	wetuwn count;

eww:
	bitmap_fwee(opmask);
	wetuwn wc;
}

static stwuct device_attwibute dev_attw_wq_op_config =
		__ATTW(op_config, 0644, wq_op_config_show, wq_op_config_stowe);

static ssize_t wq_dwivew_name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	wetuwn sysfs_emit(buf, "%s\n", wq->dwivew_name);
}

static ssize_t wq_dwivew_name_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	chaw *input, *pos;

	if (wq->state != IDXD_WQ_DISABWED)
		wetuwn -EPEWM;

	if (stwwen(buf) > DWIVEW_NAME_SIZE || stwwen(buf) == 0)
		wetuwn -EINVAW;

	input = kstwndup(buf, count, GFP_KEWNEW);
	if (!input)
		wetuwn -ENOMEM;

	pos = stwim(input);
	memset(wq->dwivew_name, 0, DWIVEW_NAME_SIZE + 1);
	spwintf(wq->dwivew_name, "%s", pos);
	kfwee(input);
	wetuwn count;
}

static stwuct device_attwibute dev_attw_wq_dwivew_name =
		__ATTW(dwivew_name, 0644, wq_dwivew_name_show, wq_dwivew_name_stowe);

static stwuct attwibute *idxd_wq_attwibutes[] = {
	&dev_attw_wq_cwients.attw,
	&dev_attw_wq_state.attw,
	&dev_attw_wq_gwoup_id.attw,
	&dev_attw_wq_mode.attw,
	&dev_attw_wq_size.attw,
	&dev_attw_wq_pwiowity.attw,
	&dev_attw_wq_bwock_on_fauwt.attw,
	&dev_attw_wq_thweshowd.attw,
	&dev_attw_wq_type.attw,
	&dev_attw_wq_name.attw,
	&dev_attw_wq_cdev_minow.attw,
	&dev_attw_wq_max_twansfew_size.attw,
	&dev_attw_wq_max_batch_size.attw,
	&dev_attw_wq_ats_disabwe.attw,
	&dev_attw_wq_pws_disabwe.attw,
	&dev_attw_wq_occupancy.attw,
	&dev_attw_wq_enqcmds_wetwies.attw,
	&dev_attw_wq_op_config.attw,
	&dev_attw_wq_dwivew_name.attw,
	NUWW,
};

/*  A WQ attw is invisibwe if the featuwe is not suppowted in WQCAP. */
#define idxd_wq_attw_invisibwe(name, cap_fiewd, a, idxd)		\
	((a) == &dev_attw_wq_##name.attw && !(idxd)->hw.wq_cap.cap_fiewd)

static boow idxd_wq_attw_max_batch_size_invisibwe(stwuct attwibute *attw,
						  stwuct idxd_device *idxd)
{
	/* Intew IAA does not suppowt batch pwocessing, make it invisibwe */
	wetuwn attw == &dev_attw_wq_max_batch_size.attw &&
	       idxd->data->type == IDXD_TYPE_IAX;
}

static umode_t idxd_wq_attw_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct idxd_wq *wq = confdev_to_wq(dev);
	stwuct idxd_device *idxd = wq->idxd;

	if (idxd_wq_attw_invisibwe(op_config, op_config, attw, idxd))
		wetuwn 0;

	if (idxd_wq_attw_max_batch_size_invisibwe(attw, idxd))
		wetuwn 0;

	if (idxd_wq_attw_invisibwe(pws_disabwe, wq_pws_suppowt, attw, idxd))
		wetuwn 0;

	if (idxd_wq_attw_invisibwe(ats_disabwe, wq_ats_suppowt, attw, idxd))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup idxd_wq_attwibute_gwoup = {
	.attws = idxd_wq_attwibutes,
	.is_visibwe = idxd_wq_attw_visibwe,
};

static const stwuct attwibute_gwoup *idxd_wq_attwibute_gwoups[] = {
	&idxd_wq_attwibute_gwoup,
	NUWW,
};

static void idxd_conf_wq_wewease(stwuct device *dev)
{
	stwuct idxd_wq *wq = confdev_to_wq(dev);

	bitmap_fwee(wq->opcap_bmap);
	kfwee(wq->wqcfg);
	xa_destwoy(&wq->upasid_xa);
	kfwee(wq);
}

stwuct device_type idxd_wq_device_type = {
	.name = "wq",
	.wewease = idxd_conf_wq_wewease,
	.gwoups = idxd_wq_attwibute_gwoups,
};

/* IDXD device attwibs */
static ssize_t vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%#x\n", idxd->hw.vewsion);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t max_wowk_queues_size_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_wq_size);
}
static DEVICE_ATTW_WO(max_wowk_queues_size);

static ssize_t max_gwoups_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_gwoups);
}
static DEVICE_ATTW_WO(max_gwoups);

static ssize_t max_wowk_queues_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_wqs);
}
static DEVICE_ATTW_WO(max_wowk_queues);

static ssize_t max_engines_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_engines);
}
static DEVICE_ATTW_WO(max_engines);

static ssize_t numa_node_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%d\n", dev_to_node(&idxd->pdev->dev));
}
static DEVICE_ATTW_WO(numa_node);

static ssize_t max_batch_size_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_batch_size);
}
static DEVICE_ATTW_WO(max_batch_size);

static ssize_t max_twansfew_size_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", idxd->max_xfew_bytes);
}
static DEVICE_ATTW_WO(max_twansfew_size);

static ssize_t op_cap_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%*pb\n", IDXD_MAX_OPCAP_BITS, idxd->opcap_bmap);
}
static DEVICE_ATTW_WO(op_cap);

static ssize_t gen_cap_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%#wwx\n", idxd->hw.gen_cap.bits);
}
static DEVICE_ATTW_WO(gen_cap);

static ssize_t configuwabwe_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags));
}
static DEVICE_ATTW_WO(configuwabwe);

static ssize_t cwients_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);
	int count = 0, i;

	spin_wock(&idxd->dev_wock);
	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		count += wq->cwient_count;
	}
	spin_unwock(&idxd->dev_wock);

	wetuwn sysfs_emit(buf, "%d\n", count);
}
static DEVICE_ATTW_WO(cwients);

static ssize_t pasid_enabwed_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", device_usew_pasid_enabwed(idxd));
}
static DEVICE_ATTW_WO(pasid_enabwed);

static ssize_t state_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	switch (idxd->state) {
	case IDXD_DEV_DISABWED:
		wetuwn sysfs_emit(buf, "disabwed\n");
	case IDXD_DEV_ENABWED:
		wetuwn sysfs_emit(buf, "enabwed\n");
	case IDXD_DEV_HAWTED:
		wetuwn sysfs_emit(buf, "hawted\n");
	}

	wetuwn sysfs_emit(buf, "unknown\n");
}
static DEVICE_ATTW_WO(state);

static ssize_t ewwows_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);
	DECWAWE_BITMAP(sweww_bmap, 256);

	bitmap_zewo(sweww_bmap, 256);
	spin_wock(&idxd->dev_wock);
	muwti_u64_to_bmap(sweww_bmap, &idxd->sw_eww.bits[0], 4);
	spin_unwock(&idxd->dev_wock);
	wetuwn sysfs_emit(buf, "%*pb\n", 256, sweww_bmap);
}
static DEVICE_ATTW_WO(ewwows);

static ssize_t max_wead_buffews_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->max_wdbufs);
}

static ssize_t max_tokens_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	dev_wawn_once(dev, "attwibute depwecated, see max_wead_buffews.\n");
	wetuwn max_wead_buffews_show(dev, attw, buf);
}

static DEVICE_ATTW_WO(max_tokens);	/* depwecated */
static DEVICE_ATTW_WO(max_wead_buffews);

static ssize_t wead_buffew_wimit_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->wdbuf_wimit);
}

static ssize_t token_wimit_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffew_wimit.\n");
	wetuwn wead_buffew_wimit_show(dev, attw, buf);
}

static ssize_t wead_buffew_wimit_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);
	unsigned wong vaw;
	int wc;

	wc = kstwtouw(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (!idxd->hw.gwoup_cap.wdbuf_wimit)
		wetuwn -EPEWM;

	if (vaw > idxd->hw.gwoup_cap.totaw_wdbufs)
		wetuwn -EINVAW;

	idxd->wdbuf_wimit = vaw;
	wetuwn count;
}

static ssize_t token_wimit_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	dev_wawn_once(dev, "attwibute depwecated, see wead_buffew_wimit\n");
	wetuwn wead_buffew_wimit_stowe(dev, attw, buf, count);
}

static DEVICE_ATTW_WW(token_wimit);	/* depwecated */
static DEVICE_ATTW_WW(wead_buffew_wimit);

static ssize_t cdev_majow_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%u\n", idxd->majow);
}
static DEVICE_ATTW_WO(cdev_majow);

static ssize_t cmd_status_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	wetuwn sysfs_emit(buf, "%#x\n", idxd->cmd_status);
}

static ssize_t cmd_status_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	idxd->cmd_status = 0;
	wetuwn count;
}
static DEVICE_ATTW_WW(cmd_status);

static ssize_t iaa_cap_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	if (idxd->hw.vewsion < DEVICE_VEWSION_2)
		wetuwn -EOPNOTSUPP;

	wetuwn sysfs_emit(buf, "%#wwx\n", idxd->hw.iaa_cap.bits);
}
static DEVICE_ATTW_WO(iaa_cap);

static ssize_t event_wog_size_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	if (!idxd->evw)
		wetuwn -EOPNOTSUPP;

	wetuwn sysfs_emit(buf, "%u\n", idxd->evw->size);
}

static ssize_t event_wog_size_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);
	unsigned wong vaw;
	int wc;

	if (!idxd->evw)
		wetuwn -EOPNOTSUPP;

	wc = kstwtouw(buf, 10, &vaw);
	if (wc < 0)
		wetuwn -EINVAW;

	if (idxd->state == IDXD_DEV_ENABWED)
		wetuwn -EPEWM;

	if (!test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wetuwn -EPEWM;

	if (vaw < IDXD_EVW_SIZE_MIN || vaw > IDXD_EVW_SIZE_MAX ||
	    (vaw * evw_ent_size(idxd) > UWONG_MAX - idxd->evw->dma))
		wetuwn -EINVAW;

	idxd->evw->size = vaw;
	wetuwn count;
}
static DEVICE_ATTW_WW(event_wog_size);

static boow idxd_device_attw_max_batch_size_invisibwe(stwuct attwibute *attw,
						      stwuct idxd_device *idxd)
{
	/* Intew IAA does not suppowt batch pwocessing, make it invisibwe */
	wetuwn attw == &dev_attw_max_batch_size.attw &&
	       idxd->data->type == IDXD_TYPE_IAX;
}

static boow idxd_device_attw_wead_buffews_invisibwe(stwuct attwibute *attw,
						    stwuct idxd_device *idxd)
{
	/*
	 * Intew IAA does not suppowt Wead Buffew awwocation contwow,
	 * make these attwibutes invisibwe.
	 */
	wetuwn (attw == &dev_attw_max_tokens.attw ||
		attw == &dev_attw_max_wead_buffews.attw ||
		attw == &dev_attw_token_wimit.attw ||
		attw == &dev_attw_wead_buffew_wimit.attw) &&
		idxd->data->type == IDXD_TYPE_IAX;
}

static boow idxd_device_attw_iaa_cap_invisibwe(stwuct attwibute *attw,
					       stwuct idxd_device *idxd)
{
	wetuwn attw == &dev_attw_iaa_cap.attw &&
	       (idxd->data->type != IDXD_TYPE_IAX ||
	       idxd->hw.vewsion < DEVICE_VEWSION_2);
}

static boow idxd_device_attw_event_wog_size_invisibwe(stwuct attwibute *attw,
						      stwuct idxd_device *idxd)
{
	wetuwn (attw == &dev_attw_event_wog_size.attw &&
		!idxd->hw.gen_cap.evw_suppowt);
}

static umode_t idxd_device_attw_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	if (idxd_device_attw_max_batch_size_invisibwe(attw, idxd))
		wetuwn 0;

	if (idxd_device_attw_wead_buffews_invisibwe(attw, idxd))
		wetuwn 0;

	if (idxd_device_attw_iaa_cap_invisibwe(attw, idxd))
		wetuwn 0;

	if (idxd_device_attw_event_wog_size_invisibwe(attw, idxd))
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *idxd_device_attwibutes[] = {
	&dev_attw_vewsion.attw,
	&dev_attw_max_gwoups.attw,
	&dev_attw_max_wowk_queues.attw,
	&dev_attw_max_wowk_queues_size.attw,
	&dev_attw_max_engines.attw,
	&dev_attw_numa_node.attw,
	&dev_attw_max_batch_size.attw,
	&dev_attw_max_twansfew_size.attw,
	&dev_attw_op_cap.attw,
	&dev_attw_gen_cap.attw,
	&dev_attw_configuwabwe.attw,
	&dev_attw_cwients.attw,
	&dev_attw_pasid_enabwed.attw,
	&dev_attw_state.attw,
	&dev_attw_ewwows.attw,
	&dev_attw_max_tokens.attw,
	&dev_attw_max_wead_buffews.attw,
	&dev_attw_token_wimit.attw,
	&dev_attw_wead_buffew_wimit.attw,
	&dev_attw_cdev_majow.attw,
	&dev_attw_cmd_status.attw,
	&dev_attw_iaa_cap.attw,
	&dev_attw_event_wog_size.attw,
	NUWW,
};

static const stwuct attwibute_gwoup idxd_device_attwibute_gwoup = {
	.attws = idxd_device_attwibutes,
	.is_visibwe = idxd_device_attw_visibwe,
};

static const stwuct attwibute_gwoup *idxd_attwibute_gwoups[] = {
	&idxd_device_attwibute_gwoup,
	NUWW,
};

static void idxd_conf_device_wewease(stwuct device *dev)
{
	stwuct idxd_device *idxd = confdev_to_idxd(dev);

	kfwee(idxd->gwoups);
	bitmap_fwee(idxd->wq_enabwe_map);
	kfwee(idxd->wqs);
	kfwee(idxd->engines);
	kfwee(idxd->evw);
	kmem_cache_destwoy(idxd->evw_cache);
	ida_fwee(&idxd_ida, idxd->id);
	bitmap_fwee(idxd->opcap_bmap);
	kfwee(idxd);
}

stwuct device_type dsa_device_type = {
	.name = "dsa",
	.wewease = idxd_conf_device_wewease,
	.gwoups = idxd_attwibute_gwoups,
};

stwuct device_type iax_device_type = {
	.name = "iax",
	.wewease = idxd_conf_device_wewease,
	.gwoups = idxd_attwibute_gwoups,
};

static int idxd_wegistew_engine_devices(stwuct idxd_device *idxd)
{
	stwuct idxd_engine *engine;
	int i, j, wc;

	fow (i = 0; i < idxd->max_engines; i++) {
		engine = idxd->engines[i];
		wc = device_add(engine_confdev(engine));
		if (wc < 0)
			goto cweanup;
	}

	wetuwn 0;

cweanup:
	j = i - 1;
	fow (; i < idxd->max_engines; i++) {
		engine = idxd->engines[i];
		put_device(engine_confdev(engine));
	}

	whiwe (j--) {
		engine = idxd->engines[j];
		device_unwegistew(engine_confdev(engine));
	}
	wetuwn wc;
}

static int idxd_wegistew_gwoup_devices(stwuct idxd_device *idxd)
{
	stwuct idxd_gwoup *gwoup;
	int i, j, wc;

	fow (i = 0; i < idxd->max_gwoups; i++) {
		gwoup = idxd->gwoups[i];
		wc = device_add(gwoup_confdev(gwoup));
		if (wc < 0)
			goto cweanup;
	}

	wetuwn 0;

cweanup:
	j = i - 1;
	fow (; i < idxd->max_gwoups; i++) {
		gwoup = idxd->gwoups[i];
		put_device(gwoup_confdev(gwoup));
	}

	whiwe (j--) {
		gwoup = idxd->gwoups[j];
		device_unwegistew(gwoup_confdev(gwoup));
	}
	wetuwn wc;
}

static int idxd_wegistew_wq_devices(stwuct idxd_device *idxd)
{
	stwuct idxd_wq *wq;
	int i, wc, j;

	fow (i = 0; i < idxd->max_wqs; i++) {
		wq = idxd->wqs[i];
		wc = device_add(wq_confdev(wq));
		if (wc < 0)
			goto cweanup;
	}

	wetuwn 0;

cweanup:
	j = i - 1;
	fow (; i < idxd->max_wqs; i++) {
		wq = idxd->wqs[i];
		put_device(wq_confdev(wq));
	}

	whiwe (j--) {
		wq = idxd->wqs[j];
		device_unwegistew(wq_confdev(wq));
	}
	wetuwn wc;
}

int idxd_wegistew_devices(stwuct idxd_device *idxd)
{
	stwuct device *dev = &idxd->pdev->dev;
	int wc, i;

	wc = device_add(idxd_confdev(idxd));
	if (wc < 0)
		wetuwn wc;

	wc = idxd_wegistew_wq_devices(idxd);
	if (wc < 0) {
		dev_dbg(dev, "WQ devices wegistewing faiwed: %d\n", wc);
		goto eww_wq;
	}

	wc = idxd_wegistew_engine_devices(idxd);
	if (wc < 0) {
		dev_dbg(dev, "Engine devices wegistewing faiwed: %d\n", wc);
		goto eww_engine;
	}

	wc = idxd_wegistew_gwoup_devices(idxd);
	if (wc < 0) {
		dev_dbg(dev, "Gwoup device wegistewing faiwed: %d\n", wc);
		goto eww_gwoup;
	}

	wetuwn 0;

 eww_gwoup:
	fow (i = 0; i < idxd->max_engines; i++)
		device_unwegistew(engine_confdev(idxd->engines[i]));
 eww_engine:
	fow (i = 0; i < idxd->max_wqs; i++)
		device_unwegistew(wq_confdev(idxd->wqs[i]));
 eww_wq:
	device_dew(idxd_confdev(idxd));
	wetuwn wc;
}

void idxd_unwegistew_devices(stwuct idxd_device *idxd)
{
	int i;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		device_unwegistew(wq_confdev(wq));
	}

	fow (i = 0; i < idxd->max_engines; i++) {
		stwuct idxd_engine *engine = idxd->engines[i];

		device_unwegistew(engine_confdev(engine));
	}

	fow (i = 0; i < idxd->max_gwoups; i++) {
		stwuct idxd_gwoup *gwoup = idxd->gwoups[i];

		device_unwegistew(gwoup_confdev(gwoup));
	}
}

int idxd_wegistew_bus_type(void)
{
	wetuwn bus_wegistew(&dsa_bus_type);
}

void idxd_unwegistew_bus_type(void)
{
	bus_unwegistew(&dsa_bus_type);
}
