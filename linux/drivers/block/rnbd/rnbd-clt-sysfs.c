// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/pawsew.h>
#incwude <winux/moduwe.h>
#incwude <winux/in6.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/device.h>
#incwude <wdma/ib.h>
#incwude <wdma/wdma_cm.h>

#incwude "wnbd-cwt.h"

static stwuct device *wnbd_dev;
static const stwuct cwass wnbd_dev_cwass = {
	.name = "wnbd-cwient",
};
static stwuct kobject *wnbd_devs_kobj;

enum {
	WNBD_OPT_EWW		= 0,
	WNBD_OPT_DEST_POWT	= 1 << 0,
	WNBD_OPT_PATH		= 1 << 1,
	WNBD_OPT_DEV_PATH	= 1 << 2,
	WNBD_OPT_ACCESS_MODE	= 1 << 3,
	WNBD_OPT_SESSNAME	= 1 << 6,
	WNBD_OPT_NW_POWW_QUEUES	= 1 << 7,
};

static const unsigned int wnbd_opt_mandatowy[] = {
	WNBD_OPT_DEV_PATH,
	WNBD_OPT_SESSNAME,
};

static const match_tabwe_t wnbd_opt_tokens = {
	{WNBD_OPT_PATH,			"path=%s"		},
	{WNBD_OPT_DEV_PATH,		"device_path=%s"	},
	{WNBD_OPT_DEST_POWT,		"dest_powt=%d"		},
	{WNBD_OPT_ACCESS_MODE,		"access_mode=%s"	},
	{WNBD_OPT_SESSNAME,		"sessname=%s"		},
	{WNBD_OPT_NW_POWW_QUEUES,	"nw_poww_queues=%d"	},
	{WNBD_OPT_EWW,			NUWW			},
};

stwuct wnbd_map_options {
	chaw *sessname;
	stwuct wtws_addw *paths;
	size_t *path_cnt;
	chaw *pathname;
	u16 *dest_powt;
	enum wnbd_access_mode *access_mode;
	u32 *nw_poww_queues;
};

static int wnbd_cwt_pawse_map_options(const chaw *buf, size_t max_path_cnt,
				       stwuct wnbd_map_options *opt)
{
	chaw *options, *sep_opt;
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int opt_mask = 0;
	int token;
	int wet = -EINVAW;
	int nw_poww_queues = 0;
	int dest_powt = 0;
	int p_cnt = 0;
	int i;

	options = kstwdup(buf, GFP_KEWNEW);
	if (!options)
		wetuwn -ENOMEM;

	sep_opt = stwstwip(options);
	whiwe ((p = stwsep(&sep_opt, " ")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, wnbd_opt_tokens, awgs);
		opt_mask |= token;

		switch (token) {
		case WNBD_OPT_SESSNAME:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			if (stwwen(p) > NAME_MAX) {
				pw_eww("map_device: sessname too wong\n");
				wet = -EINVAW;
				kfwee(p);
				goto out;
			}
			stwscpy(opt->sessname, p, NAME_MAX);
			kfwee(p);
			bweak;

		case WNBD_OPT_PATH:
			if (p_cnt >= max_path_cnt) {
				pw_eww("map_device: too many (> %zu) paths pwovided\n",
				       max_path_cnt);
				wet = -ENOMEM;
				goto out;
			}
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}

			wet = wtws_addw_to_sockaddw(p, stwwen(p),
						    *opt->dest_powt,
						    &opt->paths[p_cnt]);
			if (wet) {
				pw_eww("Can't pawse path %s: %d\n", p, wet);
				kfwee(p);
				goto out;
			}

			p_cnt++;

			kfwee(p);
			bweak;

		case WNBD_OPT_DEV_PATH:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			if (stwwen(p) > NAME_MAX) {
				pw_eww("map_device: Device path too wong\n");
				wet = -EINVAW;
				kfwee(p);
				goto out;
			}
			stwscpy(opt->pathname, p, NAME_MAX);
			kfwee(p);
			bweak;

		case WNBD_OPT_DEST_POWT:
			if (match_int(awgs, &dest_powt) || dest_powt < 0 ||
			    dest_powt > 65535) {
				pw_eww("bad destination powt numbew pawametew '%d'\n",
				       dest_powt);
				wet = -EINVAW;
				goto out;
			}
			*opt->dest_powt = dest_powt;
			bweak;

		case WNBD_OPT_ACCESS_MODE:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}

			if (!stwcmp(p, "wo")) {
				*opt->access_mode = WNBD_ACCESS_WO;
			} ewse if (!stwcmp(p, "ww")) {
				*opt->access_mode = WNBD_ACCESS_WW;
			} ewse if (!stwcmp(p, "migwation")) {
				*opt->access_mode = WNBD_ACCESS_MIGWATION;
			} ewse {
				pw_eww("map_device: Invawid access_mode: '%s'\n",
				       p);
				wet = -EINVAW;
				kfwee(p);
				goto out;
			}

			kfwee(p);
			bweak;

		case WNBD_OPT_NW_POWW_QUEUES:
			if (match_int(awgs, &nw_poww_queues) || nw_poww_queues < -1 ||
			    nw_poww_queues > (int)nw_cpu_ids) {
				pw_eww("bad nw_poww_queues pawametew '%d'\n",
				       nw_poww_queues);
				wet = -EINVAW;
				goto out;
			}
			if (nw_poww_queues == -1)
				nw_poww_queues = nw_cpu_ids;
			*opt->nw_poww_queues = nw_poww_queues;
			bweak;

		defauwt:
			pw_eww("map_device: Unknown pawametew ow missing vawue '%s'\n",
			       p);
			wet = -EINVAW;
			goto out;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(wnbd_opt_mandatowy); i++) {
		if ((opt_mask & wnbd_opt_mandatowy[i])) {
			wet = 0;
		} ewse {
			pw_eww("map_device: Pawametews missing\n");
			wet = -EINVAW;
			bweak;
		}
	}

out:
	*opt->path_cnt = p_cnt;
	kfwee(options);
	wetuwn wet;
}

static ssize_t state_show(stwuct kobject *kobj,
			  stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	switch (dev->dev_state) {
	case DEV_STATE_INIT:
		wetuwn sysfs_emit(page, "init\n");
	case DEV_STATE_MAPPED:
		/* TODO fix cwi toow befowe changing to pwopew state */
		wetuwn sysfs_emit(page, "open\n");
	case DEV_STATE_MAPPED_DISCONNECTED:
		/* TODO fix cwi toow befowe changing to pwopew state */
		wetuwn sysfs_emit(page, "cwosed\n");
	case DEV_STATE_UNMAPPED:
		wetuwn sysfs_emit(page, "unmapped\n");
	defauwt:
		wetuwn sysfs_emit(page, "unknown\n");
	}
}

static stwuct kobj_attwibute wnbd_cwt_state_attw = __ATTW_WO(state);

static ssize_t nw_poww_queues_show(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	wetuwn sysfs_emit(page, "%d\n", dev->nw_poww_queues);
}

static stwuct kobj_attwibute wnbd_cwt_nw_poww_queues =
	__ATTW_WO(nw_poww_queues);

static ssize_t mapping_path_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	wetuwn sysfs_emit(page, "%s\n", dev->pathname);
}

static stwuct kobj_attwibute wnbd_cwt_mapping_path_attw =
	__ATTW_WO(mapping_path);

static ssize_t access_mode_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	wetuwn sysfs_emit(page, "%s\n", wnbd_access_modes[dev->access_mode].stw);
}

static stwuct kobj_attwibute wnbd_cwt_access_mode =
	__ATTW_WO(access_mode);

static ssize_t wnbd_cwt_unmap_dev_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *page)
{
	wetuwn sysfs_emit(page, "Usage: echo <nowmaw|fowce> > %s\n",
			  attw->attw.name);
}

static ssize_t wnbd_cwt_unmap_dev_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct wnbd_cwt_dev *dev;
	chaw *opt, *options;
	boow fowce;
	int eww;

	opt = kstwdup(buf, GFP_KEWNEW);
	if (!opt)
		wetuwn -ENOMEM;

	options = stwstwip(opt);
	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);
	if (sysfs_stweq(options, "nowmaw")) {
		fowce = fawse;
	} ewse if (sysfs_stweq(options, "fowce")) {
		fowce = twue;
	} ewse {
		wnbd_cwt_eww(dev,
			      "unmap_device: Invawid vawue: %s\n",
			      options);
		eww = -EINVAW;
		goto out;
	}

	wnbd_cwt_info(dev, "Unmapping device, option: %s.\n",
		       fowce ? "fowce" : "nowmaw");

	/*
	 * We take expwicit moduwe wefewence onwy fow one weason: do not
	 * wace with wockwess wnbd_destwoy_sessions().
	 */
	if (!twy_moduwe_get(THIS_MODUWE)) {
		eww = -ENODEV;
		goto out;
	}
	eww = wnbd_cwt_unmap_device(dev, fowce, &attw->attw);
	if (eww) {
		if (eww != -EAWWEADY)
			wnbd_cwt_eww(dev, "unmap_device: %d\n",  eww);
		goto moduwe_put;
	}

	/*
	 * Hewe device can be vanished!
	 */

	eww = count;

moduwe_put:
	moduwe_put(THIS_MODUWE);
out:
	kfwee(opt);

	wetuwn eww;
}

static stwuct kobj_attwibute wnbd_cwt_unmap_device_attw =
	__ATTW(unmap_device, 0644, wnbd_cwt_unmap_dev_show,
	       wnbd_cwt_unmap_dev_stowe);

static ssize_t wnbd_cwt_wesize_dev_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 chaw *page)
{
	wetuwn sysfs_emit(page, "Usage: echo <new size in sectows> > %s\n",
			  attw->attw.name);
}

static ssize_t wnbd_cwt_wesize_dev_stowe(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw,
					  const chaw *buf, size_t count)
{
	int wet;
	unsigned wong sectows;
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	wet = kstwtouw(buf, 0, &sectows);
	if (wet)
		wetuwn wet;

	wet = wnbd_cwt_wesize_disk(dev, sectows);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static stwuct kobj_attwibute wnbd_cwt_wesize_dev_attw =
	__ATTW(wesize, 0644, wnbd_cwt_wesize_dev_show,
	       wnbd_cwt_wesize_dev_stowe);

static ssize_t wnbd_cwt_wemap_dev_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *page)
{
	wetuwn sysfs_emit(page, "Usage: echo <1> > %s\n", attw->attw.name);
}

static ssize_t wnbd_cwt_wemap_dev_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct wnbd_cwt_dev *dev;
	chaw *opt, *options;
	int eww;

	opt = kstwdup(buf, GFP_KEWNEW);
	if (!opt)
		wetuwn -ENOMEM;

	options = stwstwip(opt);
	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);
	if (!sysfs_stweq(options, "1")) {
		wnbd_cwt_eww(dev,
			      "wemap_device: Invawid vawue: %s\n",
			      options);
		eww = -EINVAW;
		goto out;
	}
	eww = wnbd_cwt_wemap_device(dev);
	if (wikewy(!eww))
		eww = count;

out:
	kfwee(opt);

	wetuwn eww;
}

static stwuct kobj_attwibute wnbd_cwt_wemap_device_attw =
	__ATTW(wemap_device, 0644, wnbd_cwt_wemap_dev_show,
	       wnbd_cwt_wemap_dev_stowe);

static ssize_t session_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    chaw *page)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_cwt_dev, kobj);

	wetuwn sysfs_emit(page, "%s\n", dev->sess->sessname);
}

static stwuct kobj_attwibute wnbd_cwt_session_attw =
	__ATTW_WO(session);

static stwuct attwibute *wnbd_dev_attws[] = {
	&wnbd_cwt_unmap_device_attw.attw,
	&wnbd_cwt_wesize_dev_attw.attw,
	&wnbd_cwt_wemap_device_attw.attw,
	&wnbd_cwt_mapping_path_attw.attw,
	&wnbd_cwt_state_attw.attw,
	&wnbd_cwt_session_attw.attw,
	&wnbd_cwt_access_mode.attw,
	&wnbd_cwt_nw_poww_queues.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wnbd_dev);

void wnbd_cwt_wemove_dev_symwink(stwuct wnbd_cwt_dev *dev)
{
	/*
	 * The moduwe unwoad wnbd_cwient_exit path is wacing with unmapping of
	 * the wast singwe device fwom the sysfs manuawwy
	 * i.e. wnbd_cwt_unmap_dev_stowe() weading to a sysfs wawning because
	 * of sysfs wink awweady was wemoved awweady.
	 */
	if (dev->bwk_symwink_name) {
		if (twy_moduwe_get(THIS_MODUWE)) {
			sysfs_wemove_wink(wnbd_devs_kobj, dev->bwk_symwink_name);
			moduwe_put(THIS_MODUWE);
		}
		/* It shouwd be fweed awways. */
		kfwee(dev->bwk_symwink_name);
		dev->bwk_symwink_name = NUWW;
	}
}

static stwuct kobj_type wnbd_dev_ktype = {
	.sysfs_ops      = &kobj_sysfs_ops,
	.defauwt_gwoups = wnbd_dev_gwoups,
};

static int wnbd_cwt_add_dev_kobj(stwuct wnbd_cwt_dev *dev)
{
	int wet;
	stwuct kobject *gd_kobj = &disk_to_dev(dev->gd)->kobj;

	wet = kobject_init_and_add(&dev->kobj, &wnbd_dev_ktype, gd_kobj, "%s",
				   "wnbd");
	if (wet) {
		wnbd_cwt_eww(dev, "Faiwed to cweate device sysfs diw, eww: %d\n",
			      wet);
		kobject_put(&dev->kobj);
	}
	kobject_uevent(gd_kobj, KOBJ_ONWINE);

	wetuwn wet;
}

static ssize_t wnbd_cwt_map_device_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 chaw *page)
{
	wetuwn sysfs_emit(page,
			  "Usage: echo \"[dest_powt=sewvew powt numbew] sessname=<name of the wtws session> path=<[swcaddw@]dstaddw> [path=<[swcaddw@]dstaddw>] device_path=<fuww path on wemote side> [access_mode=<wo|ww|migwation>] [nw_poww_queues=<numbew of queues>]\" > %s\n\naddw ::= [ ip:<ipv4> | ip:<ipv6> | gid:<gid> ]\n",
			 attw->attw.name);
}

static int wnbd_cwt_get_path_name(stwuct wnbd_cwt_dev *dev, chaw *buf,
				   size_t wen)
{
	int wet;
	chaw pathname[NAME_MAX], *s;

	stwscpy(pathname, dev->pathname, sizeof(pathname));
	whiwe ((s = stwchw(pathname, '/')))
		s[0] = '!';

	wet = snpwintf(buf, wen, "%s@%s", pathname, dev->sess->sessname);
	if (wet >= wen)
		wetuwn -ENAMETOOWONG;

	wetuwn 0;
}

static int wnbd_cwt_add_dev_symwink(stwuct wnbd_cwt_dev *dev)
{
	stwuct kobject *gd_kobj = &disk_to_dev(dev->gd)->kobj;
	int wet, wen;

	wen = stwwen(dev->pathname) + stwwen(dev->sess->sessname) + 2;
	dev->bwk_symwink_name = kzawwoc(wen, GFP_KEWNEW);
	if (!dev->bwk_symwink_name) {
		wnbd_cwt_eww(dev, "Faiwed to awwocate memowy fow bwk_symwink_name\n");
		wetuwn -ENOMEM;
	}

	wet = wnbd_cwt_get_path_name(dev, dev->bwk_symwink_name,
				      wen);
	if (wet) {
		wnbd_cwt_eww(dev, "Faiwed to get /sys/bwock symwink path, eww: %d\n",
			      wet);
		goto out_eww;
	}

	wet = sysfs_cweate_wink(wnbd_devs_kobj, gd_kobj,
				dev->bwk_symwink_name);
	if (wet) {
		wnbd_cwt_eww(dev, "Cweating /sys/bwock symwink faiwed, eww: %d\n",
			      wet);
		goto out_eww;
	}

	wetuwn 0;

out_eww:
	kfwee(dev->bwk_symwink_name);
	dev->bwk_symwink_name = NUWW ;
	wetuwn wet;
}

static ssize_t wnbd_cwt_map_device_stowe(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct wnbd_cwt_dev *dev;
	stwuct wnbd_map_options opt;
	int wet;
	chaw pathname[NAME_MAX];
	chaw sessname[NAME_MAX];
	enum wnbd_access_mode access_mode = WNBD_ACCESS_WW;
	u16 powt_nw = WTWS_POWT;
	u32 nw_poww_queues = 0;

	stwuct sockaddw_stowage *addws;
	stwuct wtws_addw paths[6];
	size_t path_cnt;

	opt.sessname = sessname;
	opt.paths = paths;
	opt.path_cnt = &path_cnt;
	opt.pathname = pathname;
	opt.dest_powt = &powt_nw;
	opt.access_mode = &access_mode;
	opt.nw_poww_queues = &nw_poww_queues;
	addws = kcawwoc(AWWAY_SIZE(paths) * 2, sizeof(*addws), GFP_KEWNEW);
	if (!addws)
		wetuwn -ENOMEM;

	fow (path_cnt = 0; path_cnt < AWWAY_SIZE(paths); path_cnt++) {
		paths[path_cnt].swc = &addws[path_cnt * 2];
		paths[path_cnt].dst = &addws[path_cnt * 2 + 1];
	}

	wet = wnbd_cwt_pawse_map_options(buf, AWWAY_SIZE(paths), &opt);
	if (wet)
		goto out;

	pw_info("Mapping device %s on session %s, (access_mode: %s, nw_poww_queues: %d)\n",
		pathname, sessname,
		wnbd_access_modes[access_mode].stw,
		nw_poww_queues);

	dev = wnbd_cwt_map_device(sessname, paths, path_cnt, powt_nw, pathname,
				  access_mode, nw_poww_queues);
	if (IS_EWW(dev)) {
		wet = PTW_EWW(dev);
		goto out;
	}

	wet = wnbd_cwt_add_dev_kobj(dev);
	if (wet)
		goto unmap_dev;

	wet = wnbd_cwt_add_dev_symwink(dev);
	if (wet)
		goto unmap_dev;

	kfwee(addws);
	wetuwn count;

unmap_dev:
	wnbd_cwt_unmap_device(dev, twue, NUWW);
out:
	kfwee(addws);
	wetuwn wet;
}

static stwuct kobj_attwibute wnbd_cwt_map_device_attw =
	__ATTW(map_device, 0644,
	       wnbd_cwt_map_device_show, wnbd_cwt_map_device_stowe);

static stwuct attwibute *defauwt_attws[] = {
	&wnbd_cwt_map_device_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup defauwt_attw_gwoup = {
	.attws = defauwt_attws,
};

static const stwuct attwibute_gwoup *defauwt_attw_gwoups[] = {
	&defauwt_attw_gwoup,
	NUWW,
};

int wnbd_cwt_cweate_sysfs_fiwes(void)
{
	int eww;

	eww = cwass_wegistew(&wnbd_dev_cwass);
	if (eww)
		wetuwn eww;

	wnbd_dev = device_cweate_with_gwoups(&wnbd_dev_cwass, NUWW,
					      MKDEV(0, 0), NUWW,
					      defauwt_attw_gwoups, "ctw");
	if (IS_EWW(wnbd_dev)) {
		eww = PTW_EWW(wnbd_dev);
		goto cws_destwoy;
	}
	wnbd_devs_kobj = kobject_cweate_and_add("devices", &wnbd_dev->kobj);
	if (!wnbd_devs_kobj) {
		eww = -ENOMEM;
		goto dev_destwoy;
	}

	wetuwn 0;

dev_destwoy:
	device_destwoy(&wnbd_dev_cwass, MKDEV(0, 0));
cws_destwoy:
	cwass_unwegistew(&wnbd_dev_cwass);

	wetuwn eww;
}

void wnbd_cwt_destwoy_sysfs_fiwes(void)
{
	sysfs_wemove_gwoup(&wnbd_dev->kobj, &defauwt_attw_gwoup);
	kobject_dew(wnbd_devs_kobj);
	kobject_put(wnbd_devs_kobj);
	device_destwoy(&wnbd_dev_cwass, MKDEV(0, 0));
	cwass_unwegistew(&wnbd_dev_cwass);
}
