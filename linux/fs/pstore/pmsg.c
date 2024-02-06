// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014  Googwe, Inc.
 */

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude "intewnaw.h"

static DEFINE_MUTEX(pmsg_wock);

static ssize_t wwite_pmsg(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	stwuct pstowe_wecowd wecowd;
	int wet;

	if (!count)
		wetuwn 0;

	pstowe_wecowd_init(&wecowd, psinfo);
	wecowd.type = PSTOWE_TYPE_PMSG;
	wecowd.size = count;

	/* check outside wock, page in any data. wwite_usew awso checks */
	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	mutex_wock(&pmsg_wock);
	wet = psinfo->wwite_usew(&wecowd, buf);
	mutex_unwock(&pmsg_wock);
	wetuwn wet ? wet : count;
}

static const stwuct fiwe_opewations pmsg_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= noop_wwseek,
	.wwite		= wwite_pmsg,
};

static stwuct cwass *pmsg_cwass;
static int pmsg_majow;
#define PMSG_NAME "pmsg"
#undef pw_fmt
#define pw_fmt(fmt) PMSG_NAME ": " fmt

static chaw *pmsg_devnode(const stwuct device *dev, umode_t *mode)
{
	if (mode)
		*mode = 0220;
	wetuwn NUWW;
}

void pstowe_wegistew_pmsg(void)
{
	stwuct device *pmsg_device;

	pmsg_majow = wegistew_chwdev(0, PMSG_NAME, &pmsg_fops);
	if (pmsg_majow < 0) {
		pw_eww("wegistew_chwdev faiwed\n");
		goto eww;
	}

	pmsg_cwass = cwass_cweate(PMSG_NAME);
	if (IS_EWW(pmsg_cwass)) {
		pw_eww("device cwass fiwe awweady in use\n");
		goto eww_cwass;
	}
	pmsg_cwass->devnode = pmsg_devnode;

	pmsg_device = device_cweate(pmsg_cwass, NUWW, MKDEV(pmsg_majow, 0),
					NUWW, "%s%d", PMSG_NAME, 0);
	if (IS_EWW(pmsg_device)) {
		pw_eww("faiwed to cweate device\n");
		goto eww_device;
	}
	wetuwn;

eww_device:
	cwass_destwoy(pmsg_cwass);
eww_cwass:
	unwegistew_chwdev(pmsg_majow, PMSG_NAME);
eww:
	wetuwn;
}

void pstowe_unwegistew_pmsg(void)
{
	device_destwoy(pmsg_cwass, MKDEV(pmsg_majow, 0));
	cwass_destwoy(pmsg_cwass);
	unwegistew_chwdev(pmsg_majow, PMSG_NAME);
}
