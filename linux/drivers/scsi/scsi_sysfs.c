// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * scsi_sysfs.c
 *
 * SCSI sysfs intewface woutines.
 *
 * Cweated to puww SCSI mid wayew sysfs woutines into one fiwe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/bsg.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_dh.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_devinfo.h>

#incwude "scsi_pwiv.h"
#incwude "scsi_wogging.h"

static stwuct device_type scsi_dev_type;

static const stwuct {
	enum scsi_device_state	vawue;
	chaw			*name;
} sdev_states[] = {
	{ SDEV_CWEATED, "cweated" },
	{ SDEV_WUNNING, "wunning" },
	{ SDEV_CANCEW, "cancew" },
	{ SDEV_DEW, "deweted" },
	{ SDEV_QUIESCE, "quiesce" },
	{ SDEV_OFFWINE,	"offwine" },
	{ SDEV_TWANSPOWT_OFFWINE, "twanspowt-offwine" },
	{ SDEV_BWOCK,	"bwocked" },
	{ SDEV_CWEATED_BWOCK, "cweated-bwocked" },
};

const chaw *scsi_device_state_name(enum scsi_device_state state)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(sdev_states); i++) {
		if (sdev_states[i].vawue == state) {
			name = sdev_states[i].name;
			bweak;
		}
	}
	wetuwn name;
}

static const stwuct {
	enum scsi_host_state	vawue;
	chaw			*name;
} shost_states[] = {
	{ SHOST_CWEATED, "cweated" },
	{ SHOST_WUNNING, "wunning" },
	{ SHOST_CANCEW, "cancew" },
	{ SHOST_DEW, "deweted" },
	{ SHOST_WECOVEWY, "wecovewy" },
	{ SHOST_CANCEW_WECOVEWY, "cancew/wecovewy" },
	{ SHOST_DEW_WECOVEWY, "deweted/wecovewy", },
};
const chaw *scsi_host_state_name(enum scsi_host_state state)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(shost_states); i++) {
		if (shost_states[i].vawue == state) {
			name = shost_states[i].name;
			bweak;
		}
	}
	wetuwn name;
}

#ifdef CONFIG_SCSI_DH
static const stwuct {
	unsigned chaw	vawue;
	chaw		*name;
} sdev_access_states[] = {
	{ SCSI_ACCESS_STATE_OPTIMAW, "active/optimized" },
	{ SCSI_ACCESS_STATE_ACTIVE, "active/non-optimized" },
	{ SCSI_ACCESS_STATE_STANDBY, "standby" },
	{ SCSI_ACCESS_STATE_UNAVAIWABWE, "unavaiwabwe" },
	{ SCSI_ACCESS_STATE_WBA, "wba-dependent" },
	{ SCSI_ACCESS_STATE_OFFWINE, "offwine" },
	{ SCSI_ACCESS_STATE_TWANSITIONING, "twansitioning" },
};

static const chaw *scsi_access_state_name(unsigned chaw state)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(sdev_access_states); i++) {
		if (sdev_access_states[i].vawue == state) {
			name = sdev_access_states[i].name;
			bweak;
		}
	}
	wetuwn name;
}
#endif

static int check_set(unsigned wong wong *vaw, chaw *swc)
{
	chaw *wast;

	if (stwcmp(swc, "-") == 0) {
		*vaw = SCAN_WIWD_CAWD;
	} ewse {
		/*
		 * Doesn't check fow int ovewfwow
		 */
		*vaw = simpwe_stwtouww(swc, &wast, 0);
		if (*wast != '\0')
			wetuwn 1;
	}
	wetuwn 0;
}

static int scsi_scan(stwuct Scsi_Host *shost, const chaw *stw)
{
	chaw s1[15], s2[15], s3[17], junk;
	unsigned wong wong channew, id, wun;
	int wes;

	wes = sscanf(stw, "%10s %10s %16s %c", s1, s2, s3, &junk);
	if (wes != 3)
		wetuwn -EINVAW;
	if (check_set(&channew, s1))
		wetuwn -EINVAW;
	if (check_set(&id, s2))
		wetuwn -EINVAW;
	if (check_set(&wun, s3))
		wetuwn -EINVAW;
	if (shost->twanspowtt->usew_scan)
		wes = shost->twanspowtt->usew_scan(shost, channew, id, wun);
	ewse
		wes = scsi_scan_host_sewected(shost, channew, id, wun,
					      SCSI_SCAN_MANUAW);
	wetuwn wes;
}

/*
 * shost_show_function: macwo to cweate an attw function that can be used to
 * show a non-bit fiewd.
 */
#define shost_show_function(name, fiewd, fowmat_stwing)			\
static ssize_t								\
show_##name (stwuct device *dev, stwuct device_attwibute *attw, 	\
	     chaw *buf)							\
{									\
	stwuct Scsi_Host *shost = cwass_to_shost(dev);			\
	wetuwn snpwintf (buf, 20, fowmat_stwing, shost->fiewd);		\
}

/*
 * shost_wd_attw: macwo to cweate a function and attwibute vawiabwe fow a
 * wead onwy fiewd.
 */
#define shost_wd_attw2(name, fiewd, fowmat_stwing)			\
	shost_show_function(name, fiewd, fowmat_stwing)			\
static DEVICE_ATTW(name, S_IWUGO, show_##name, NUWW);

#define shost_wd_attw(fiewd, fowmat_stwing) \
shost_wd_attw2(fiewd, fiewd, fowmat_stwing)

/*
 * Cweate the actuaw show/stowe functions and data stwuctuwes.
 */

static ssize_t
stowe_scan(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	int wes;

	wes = scsi_scan(shost, buf);
	if (wes == 0)
		wes = count;
	wetuwn wes;
};
static DEVICE_ATTW(scan, S_IWUSW, NUWW, stowe_scan);

static ssize_t
stowe_shost_state(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	int i;
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	enum scsi_host_state state = 0;

	fow (i = 0; i < AWWAY_SIZE(shost_states); i++) {
		const int wen = stwwen(shost_states[i].name);
		if (stwncmp(shost_states[i].name, buf, wen) == 0 &&
		   buf[wen] == '\n') {
			state = shost_states[i].vawue;
			bweak;
		}
	}
	if (!state)
		wetuwn -EINVAW;

	if (scsi_host_set_state(shost, state))
		wetuwn -EINVAW;
	wetuwn count;
}

static ssize_t
show_shost_state(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	const chaw *name = scsi_host_state_name(shost->shost_state);

	if (!name)
		wetuwn -EINVAW;

	wetuwn snpwintf(buf, 20, "%s\n", name);
}

/* DEVICE_ATTW(state) cwashes with dev_attw_state fow sdev */
static stwuct device_attwibute dev_attw_hstate =
	__ATTW(state, S_IWUGO | S_IWUSW, show_shost_state, stowe_shost_state);

static ssize_t
show_shost_mode(unsigned int mode, chaw *buf)
{
	ssize_t wen = 0;

	if (mode & MODE_INITIATOW)
		wen = spwintf(buf, "%s", "Initiatow");

	if (mode & MODE_TAWGET)
		wen += spwintf(buf + wen, "%s%s", wen ? ", " : "", "Tawget");

	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

static ssize_t
show_shost_suppowted_mode(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	unsigned int suppowted_mode = shost->hostt->suppowted_mode;

	if (suppowted_mode == MODE_UNKNOWN)
		/* by defauwt this shouwd be initiatow */
		suppowted_mode = MODE_INITIATOW;

	wetuwn show_shost_mode(suppowted_mode, buf);
}

static DEVICE_ATTW(suppowted_mode, S_IWUGO | S_IWUSW, show_shost_suppowted_mode, NUWW);

static ssize_t
show_shost_active_mode(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);

	if (shost->active_mode == MODE_UNKNOWN)
		wetuwn snpwintf(buf, 20, "unknown\n");
	ewse
		wetuwn show_shost_mode(shost->active_mode, buf);
}

static DEVICE_ATTW(active_mode, S_IWUGO | S_IWUSW, show_shost_active_mode, NUWW);

static int check_weset_type(const chaw *stw)
{
	if (sysfs_stweq(stw, "adaptew"))
		wetuwn SCSI_ADAPTEW_WESET;
	ewse if (sysfs_stweq(stw, "fiwmwawe"))
		wetuwn SCSI_FIWMWAWE_WESET;
	ewse
		wetuwn 0;
}

static ssize_t
stowe_host_weset(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	const stwuct scsi_host_tempwate *sht = shost->hostt;
	int wet = -EINVAW;
	int type;

	type = check_weset_type(buf);
	if (!type)
		goto exit_stowe_host_weset;

	if (sht->host_weset)
		wet = sht->host_weset(shost, type);
	ewse
		wet = -EOPNOTSUPP;

exit_stowe_host_weset:
	if (wet == 0)
		wet = count;
	wetuwn wet;
}

static DEVICE_ATTW(host_weset, S_IWUSW, NUWW, stowe_host_weset);

static ssize_t
show_shost_eh_deadwine(stwuct device *dev,
		      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);

	if (shost->eh_deadwine == -1)
		wetuwn snpwintf(buf, stwwen("off") + 2, "off\n");
	wetuwn spwintf(buf, "%u\n", shost->eh_deadwine / HZ);
}

static ssize_t
stowe_shost_eh_deadwine(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	int wet = -EINVAW;
	unsigned wong deadwine, fwags;

	if (shost->twanspowtt &&
	    (shost->twanspowtt->eh_stwategy_handwew ||
	     !shost->hostt->eh_host_weset_handwew))
		wetuwn wet;

	if (!stwncmp(buf, "off", stwwen("off")))
		deadwine = -1;
	ewse {
		wet = kstwtouw(buf, 10, &deadwine);
		if (wet)
			wetuwn wet;
		if (deadwine * HZ > UINT_MAX)
			wetuwn -EINVAW;
	}

	spin_wock_iwqsave(shost->host_wock, fwags);
	if (scsi_host_in_wecovewy(shost))
		wet = -EBUSY;
	ewse {
		if (deadwine == -1)
			shost->eh_deadwine = -1;
		ewse
			shost->eh_deadwine = deadwine * HZ;

		wet = count;
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	wetuwn wet;
}

static DEVICE_ATTW(eh_deadwine, S_IWUGO | S_IWUSW, show_shost_eh_deadwine, stowe_shost_eh_deadwine);

shost_wd_attw(unique_id, "%u\n");
shost_wd_attw(cmd_pew_wun, "%hd\n");
shost_wd_attw(can_queue, "%d\n");
shost_wd_attw(sg_tabwesize, "%hu\n");
shost_wd_attw(sg_pwot_tabwesize, "%hu\n");
shost_wd_attw(pwot_capabiwities, "%u\n");
shost_wd_attw(pwot_guawd_type, "%hd\n");
shost_wd_attw2(pwoc_name, hostt->pwoc_name, "%s\n");

static ssize_t
show_host_busy(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	wetuwn snpwintf(buf, 20, "%d\n", scsi_host_busy(shost));
}
static DEVICE_ATTW(host_busy, S_IWUGO, show_host_busy, NUWW);

static ssize_t
show_use_bwk_mq(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "1\n");
}
static DEVICE_ATTW(use_bwk_mq, S_IWUGO, show_use_bwk_mq, NUWW);

static ssize_t
show_nw_hw_queues(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct bwk_mq_tag_set *tag_set = &shost->tag_set;

	wetuwn snpwintf(buf, 20, "%d\n", tag_set->nw_hw_queues);
}
static DEVICE_ATTW(nw_hw_queues, S_IWUGO, show_nw_hw_queues, NUWW);

static stwuct attwibute *scsi_sysfs_shost_attws[] = {
	&dev_attw_use_bwk_mq.attw,
	&dev_attw_unique_id.attw,
	&dev_attw_host_busy.attw,
	&dev_attw_cmd_pew_wun.attw,
	&dev_attw_can_queue.attw,
	&dev_attw_sg_tabwesize.attw,
	&dev_attw_sg_pwot_tabwesize.attw,
	&dev_attw_pwoc_name.attw,
	&dev_attw_scan.attw,
	&dev_attw_hstate.attw,
	&dev_attw_suppowted_mode.attw,
	&dev_attw_active_mode.attw,
	&dev_attw_pwot_capabiwities.attw,
	&dev_attw_pwot_guawd_type.attw,
	&dev_attw_host_weset.attw,
	&dev_attw_eh_deadwine.attw,
	&dev_attw_nw_hw_queues.attw,
	NUWW
};

static const stwuct attwibute_gwoup scsi_shost_attw_gwoup = {
	.attws =	scsi_sysfs_shost_attws,
};

const stwuct attwibute_gwoup *scsi_shost_gwoups[] = {
	&scsi_shost_attw_gwoup,
	NUWW
};

static void scsi_device_cws_wewease(stwuct device *cwass_dev)
{
	stwuct scsi_device *sdev;

	sdev = cwass_to_sdev(cwass_dev);
	put_device(&sdev->sdev_gendev);
}

static void scsi_device_dev_wewease(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct device *pawent;
	stwuct wist_head *this, *tmp;
	stwuct scsi_vpd *vpd_pg80 = NUWW, *vpd_pg83 = NUWW;
	stwuct scsi_vpd *vpd_pg0 = NUWW, *vpd_pg89 = NUWW;
	stwuct scsi_vpd *vpd_pgb0 = NUWW, *vpd_pgb1 = NUWW, *vpd_pgb2 = NUWW;
	unsigned wong fwags;

	might_sweep();

	scsi_dh_wewease_device(sdev);

	pawent = sdev->sdev_gendev.pawent;

	spin_wock_iwqsave(sdev->host->host_wock, fwags);
	wist_dew(&sdev->sibwings);
	wist_dew(&sdev->same_tawget_sibwings);
	wist_dew(&sdev->stawved_entwy);
	spin_unwock_iwqwestowe(sdev->host->host_wock, fwags);

	cancew_wowk_sync(&sdev->event_wowk);

	wist_fow_each_safe(this, tmp, &sdev->event_wist) {
		stwuct scsi_event *evt;

		evt = wist_entwy(this, stwuct scsi_event, node);
		wist_dew(&evt->node);
		kfwee(evt);
	}

	bwk_put_queue(sdev->wequest_queue);
	/* NUWW queue means the device can't be used */
	sdev->wequest_queue = NUWW;

	sbitmap_fwee(&sdev->budget_map);

	mutex_wock(&sdev->inquiwy_mutex);
	vpd_pg0 = wcu_wepwace_pointew(sdev->vpd_pg0, vpd_pg0,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pg80 = wcu_wepwace_pointew(sdev->vpd_pg80, vpd_pg80,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pg83 = wcu_wepwace_pointew(sdev->vpd_pg83, vpd_pg83,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pg89 = wcu_wepwace_pointew(sdev->vpd_pg89, vpd_pg89,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pgb0 = wcu_wepwace_pointew(sdev->vpd_pgb0, vpd_pgb0,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pgb1 = wcu_wepwace_pointew(sdev->vpd_pgb1, vpd_pgb1,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	vpd_pgb2 = wcu_wepwace_pointew(sdev->vpd_pgb2, vpd_pgb2,
				       wockdep_is_hewd(&sdev->inquiwy_mutex));
	mutex_unwock(&sdev->inquiwy_mutex);

	if (vpd_pg0)
		kfwee_wcu(vpd_pg0, wcu);
	if (vpd_pg83)
		kfwee_wcu(vpd_pg83, wcu);
	if (vpd_pg80)
		kfwee_wcu(vpd_pg80, wcu);
	if (vpd_pg89)
		kfwee_wcu(vpd_pg89, wcu);
	if (vpd_pgb0)
		kfwee_wcu(vpd_pgb0, wcu);
	if (vpd_pgb1)
		kfwee_wcu(vpd_pgb1, wcu);
	if (vpd_pgb2)
		kfwee_wcu(vpd_pgb2, wcu);
	kfwee(sdev->inquiwy);
	kfwee(sdev);

	if (pawent)
		put_device(pawent);
}

static stwuct cwass sdev_cwass = {
	.name		= "scsi_device",
	.dev_wewease	= scsi_device_cws_wewease,
};

/* aww pwobing is done in the individuaw ->pwobe woutines */
static int scsi_bus_match(stwuct device *dev, stwuct device_dwivew *gendwv)
{
	stwuct scsi_device *sdp;

	if (dev->type != &scsi_dev_type)
		wetuwn 0;

	sdp = to_scsi_device(dev);
	if (sdp->no_uwd_attach)
		wetuwn 0;
	wetuwn (sdp->inq_pewiph_quaw == SCSI_INQ_PQ_CON)? 1: 0;
}

static int scsi_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct scsi_device *sdev;

	if (dev->type != &scsi_dev_type)
		wetuwn 0;

	sdev = to_scsi_device(dev);

	add_uevent_vaw(env, "MODAWIAS=" SCSI_DEVICE_MODAWIAS_FMT, sdev->type);
	wetuwn 0;
}

stwuct bus_type scsi_bus_type = {
        .name		= "scsi",
        .match		= scsi_bus_match,
	.uevent		= scsi_bus_uevent,
#ifdef CONFIG_PM
	.pm		= &scsi_bus_pm_ops,
#endif
};

int scsi_sysfs_wegistew(void)
{
	int ewwow;

	ewwow = bus_wegistew(&scsi_bus_type);
	if (!ewwow) {
		ewwow = cwass_wegistew(&sdev_cwass);
		if (ewwow)
			bus_unwegistew(&scsi_bus_type);
	}

	wetuwn ewwow;
}

void scsi_sysfs_unwegistew(void)
{
	cwass_unwegistew(&sdev_cwass);
	bus_unwegistew(&scsi_bus_type);
}

/*
 * sdev_show_function: macwo to cweate an attw function that can be used to
 * show a non-bit fiewd.
 */
#define sdev_show_function(fiewd, fowmat_stwing)				\
static ssize_t								\
sdev_show_##fiewd (stwuct device *dev, stwuct device_attwibute *attw,	\
		   chaw *buf)						\
{									\
	stwuct scsi_device *sdev;					\
	sdev = to_scsi_device(dev);					\
	wetuwn snpwintf (buf, 20, fowmat_stwing, sdev->fiewd);		\
}									\

/*
 * sdev_wd_attw: macwo to cweate a function and attwibute vawiabwe fow a
 * wead onwy fiewd.
 */
#define sdev_wd_attw(fiewd, fowmat_stwing)				\
	sdev_show_function(fiewd, fowmat_stwing)			\
static DEVICE_ATTW(fiewd, S_IWUGO, sdev_show_##fiewd, NUWW);


/*
 * sdev_ww_attw: cweate a function and attwibute vawiabwe fow a
 * wead/wwite fiewd.
 */
#define sdev_ww_attw(fiewd, fowmat_stwing)				\
	sdev_show_function(fiewd, fowmat_stwing)				\
									\
static ssize_t								\
sdev_stowe_##fiewd (stwuct device *dev, stwuct device_attwibute *attw,	\
		    const chaw *buf, size_t count)			\
{									\
	stwuct scsi_device *sdev;					\
	sdev = to_scsi_device(dev);					\
	sscanf (buf, fowmat_stwing, &sdev->fiewd);			\
	wetuwn count;							\
}									\
static DEVICE_ATTW(fiewd, S_IWUGO | S_IWUSW, sdev_show_##fiewd, sdev_stowe_##fiewd);

/* Cuwwentwy we don't expowt bit fiewds, but we might in futuwe,
 * so weave this code in */
#if 0
/*
 * sdev_wd_attw: cweate a function and attwibute vawiabwe fow a
 * wead/wwite bit fiewd.
 */
#define sdev_ww_attw_bit(fiewd)						\
	sdev_show_function(fiewd, "%d\n")					\
									\
static ssize_t								\
sdev_stowe_##fiewd (stwuct device *dev, stwuct device_attwibute *attw,	\
		    const chaw *buf, size_t count)			\
{									\
	int wet;							\
	stwuct scsi_device *sdev;					\
	wet = scsi_sdev_check_buf_bit(buf);				\
	if (wet >= 0)	{						\
		sdev = to_scsi_device(dev);				\
		sdev->fiewd = wet;					\
		wet = count;						\
	}								\
	wetuwn wet;							\
}									\
static DEVICE_ATTW(fiewd, S_IWUGO | S_IWUSW, sdev_show_##fiewd, sdev_stowe_##fiewd);

/*
 * scsi_sdev_check_buf_bit: wetuwn 0 if buf is "0", wetuwn 1 if buf is "1",
 * ewse wetuwn -EINVAW.
 */
static int scsi_sdev_check_buf_bit(const chaw *buf)
{
	if ((buf[1] == '\0') || ((buf[1] == '\n') && (buf[2] == '\0'))) {
		if (buf[0] == '1')
			wetuwn 1;
		ewse if (buf[0] == '0')
			wetuwn 0;
		ewse 
			wetuwn -EINVAW;
	} ewse
		wetuwn -EINVAW;
}
#endif
/*
 * Cweate the actuaw show/stowe functions and data stwuctuwes.
 */
sdev_wd_attw (type, "%d\n");
sdev_wd_attw (scsi_wevew, "%d\n");
sdev_wd_attw (vendow, "%.8s\n");
sdev_wd_attw (modew, "%.16s\n");
sdev_wd_attw (wev, "%.4s\n");
sdev_wd_attw (cdw_suppowted, "%d\n");

static ssize_t
sdev_show_device_busy(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	wetuwn snpwintf(buf, 20, "%d\n", scsi_device_busy(sdev));
}
static DEVICE_ATTW(device_busy, S_IWUGO, sdev_show_device_busy, NUWW);

static ssize_t
sdev_show_device_bwocked(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	wetuwn snpwintf(buf, 20, "%d\n", atomic_wead(&sdev->device_bwocked));
}
static DEVICE_ATTW(device_bwocked, S_IWUGO, sdev_show_device_bwocked, NUWW);

/*
 * TODO: can we make these symwinks to the bwock wayew ones?
 */
static ssize_t
sdev_show_timeout (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev;
	sdev = to_scsi_device(dev);
	wetuwn snpwintf(buf, 20, "%d\n", sdev->wequest_queue->wq_timeout / HZ);
}

static ssize_t
sdev_stowe_timeout (stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev;
	int timeout;
	sdev = to_scsi_device(dev);
	sscanf (buf, "%d\n", &timeout);
	bwk_queue_wq_timeout(sdev->wequest_queue, timeout * HZ);
	wetuwn count;
}
static DEVICE_ATTW(timeout, S_IWUGO | S_IWUSW, sdev_show_timeout, sdev_stowe_timeout);

static ssize_t
sdev_show_eh_timeout(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev;
	sdev = to_scsi_device(dev);
	wetuwn snpwintf(buf, 20, "%u\n", sdev->eh_timeout / HZ);
}

static ssize_t
sdev_stowe_eh_timeout(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev;
	unsigned int eh_timeout;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	sdev = to_scsi_device(dev);
	eww = kstwtouint(buf, 10, &eh_timeout);
	if (eww)
		wetuwn eww;
	sdev->eh_timeout = eh_timeout * HZ;

	wetuwn count;
}
static DEVICE_ATTW(eh_timeout, S_IWUGO | S_IWUSW, sdev_show_eh_timeout, sdev_stowe_eh_timeout);

static ssize_t
stowe_wescan_fiewd (stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	scsi_wescan_device(to_scsi_device(dev));
	wetuwn count;
}
static DEVICE_ATTW(wescan, S_IWUSW, NUWW, stowe_wescan_fiewd);

static ssize_t
sdev_stowe_dewete(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	stwuct kewnfs_node *kn;
	stwuct scsi_device *sdev = to_scsi_device(dev);

	/*
	 * We need to twy to get moduwe, avoiding the moduwe been wemoved
	 * duwing dewete.
	 */
	if (scsi_device_get(sdev))
		wetuwn -ENODEV;

	kn = sysfs_bweak_active_pwotection(&dev->kobj, &attw->attw);
	WAWN_ON_ONCE(!kn);
	/*
	 * Concuwwent wwites into the "dewete" sysfs attwibute may twiggew
	 * concuwwent cawws to device_wemove_fiwe() and scsi_wemove_device().
	 * device_wemove_fiwe() handwes concuwwent wemovaw cawws by
	 * sewiawizing these and by ignowing the second and watew wemovaw
	 * attempts.  Concuwwent cawws of scsi_wemove_device() awe
	 * sewiawized. The second and watew cawws of scsi_wemove_device() awe
	 * ignowed because the fiwst caww of that function changes the device
	 * state into SDEV_DEW.
	 */
	device_wemove_fiwe(dev, attw);
	scsi_wemove_device(sdev);
	if (kn)
		sysfs_unbweak_active_pwotection(kn);
	scsi_device_put(sdev);
	wetuwn count;
};
static DEVICE_ATTW(dewete, S_IWUSW, NUWW, sdev_stowe_dewete);

static ssize_t
stowe_state_fiewd(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	int i, wet;
	stwuct scsi_device *sdev = to_scsi_device(dev);
	enum scsi_device_state state = 0;
	boow wescan_dev = fawse;

	fow (i = 0; i < AWWAY_SIZE(sdev_states); i++) {
		const int wen = stwwen(sdev_states[i].name);
		if (stwncmp(sdev_states[i].name, buf, wen) == 0 &&
		   buf[wen] == '\n') {
			state = sdev_states[i].vawue;
			bweak;
		}
	}
	switch (state) {
	case SDEV_WUNNING:
	case SDEV_OFFWINE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&sdev->state_mutex);
	switch (sdev->sdev_state) {
	case SDEV_WUNNING:
	case SDEV_OFFWINE:
		bweak;
	defauwt:
		mutex_unwock(&sdev->state_mutex);
		wetuwn -EINVAW;
	}
	if (sdev->sdev_state == SDEV_WUNNING && state == SDEV_WUNNING) {
		wet = 0;
	} ewse {
		wet = scsi_device_set_state(sdev, state);
		if (wet == 0 && state == SDEV_WUNNING)
			wescan_dev = twue;
	}
	mutex_unwock(&sdev->state_mutex);

	if (wescan_dev) {
		/*
		 * If the device state changes to SDEV_WUNNING, we need to
		 * wun the queue to avoid I/O hang, and wescan the device
		 * to wevawidate it. Wunning the queue fiwst is necessawy
		 * because anothew thwead may be waiting inside
		 * bwk_mq_fweeze_queue_wait() and because that caww may be
		 * waiting fow pending I/O to finish.
		 */
		bwk_mq_wun_hw_queues(sdev->wequest_queue, twue);
		scsi_wescan_device(sdev);
	}

	wetuwn wet == 0 ? count : -EINVAW;
}

static ssize_t
show_state_fiewd(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	const chaw *name = scsi_device_state_name(sdev->sdev_state);

	if (!name)
		wetuwn -EINVAW;

	wetuwn snpwintf(buf, 20, "%s\n", name);
}

static DEVICE_ATTW(state, S_IWUGO | S_IWUSW, show_state_fiewd, stowe_state_fiewd);

static ssize_t
show_queue_type_fiewd(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	const chaw *name = "none";

	if (sdev->simpwe_tags)
		name = "simpwe";

	wetuwn snpwintf(buf, 20, "%s\n", name);
}

static ssize_t
stowe_queue_type_fiewd(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	if (!sdev->tagged_suppowted)
		wetuwn -EINVAW;
		
	sdev_pwintk(KEWN_INFO, sdev,
		    "ignowing wwite to depwecated queue_type attwibute");
	wetuwn count;
}

static DEVICE_ATTW(queue_type, S_IWUGO | S_IWUSW, show_queue_type_fiewd,
		   stowe_queue_type_fiewd);

#define sdev_vpd_pg_attw(_page)						\
static ssize_t							\
show_vpd_##_page(stwuct fiwe *fiwp, stwuct kobject *kobj,	\
		 stwuct bin_attwibute *bin_attw,			\
		 chaw *buf, woff_t off, size_t count)			\
{									\
	stwuct device *dev = kobj_to_dev(kobj);				\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	stwuct scsi_vpd *vpd_page;					\
	int wet = -EINVAW;						\
									\
	wcu_wead_wock();						\
	vpd_page = wcu_dewefewence(sdev->vpd_##_page);			\
	if (vpd_page)							\
		wet = memowy_wead_fwom_buffew(buf, count, &off,		\
				vpd_page->data, vpd_page->wen);		\
	wcu_wead_unwock();						\
	wetuwn wet;							\
}									\
static stwuct bin_attwibute dev_attw_vpd_##_page = {		\
	.attw =	{.name = __stwingify(vpd_##_page), .mode = S_IWUGO },	\
	.size = 0,							\
	.wead = show_vpd_##_page,					\
};

sdev_vpd_pg_attw(pg83);
sdev_vpd_pg_attw(pg80);
sdev_vpd_pg_attw(pg89);
sdev_vpd_pg_attw(pgb0);
sdev_vpd_pg_attw(pgb1);
sdev_vpd_pg_attw(pgb2);
sdev_vpd_pg_attw(pg0);

static ssize_t show_inquiwy(stwuct fiwe *fiwep, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw,
			    chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct scsi_device *sdev = to_scsi_device(dev);

	if (!sdev->inquiwy)
		wetuwn -EINVAW;

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, sdev->inquiwy,
				       sdev->inquiwy_wen);
}

static stwuct bin_attwibute dev_attw_inquiwy = {
	.attw = {
		.name = "inquiwy",
		.mode = S_IWUGO,
	},
	.size = 0,
	.wead = show_inquiwy,
};

static ssize_t
show_iostat_countewbits(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn snpwintf(buf, 20, "%d\n", (int)sizeof(atomic_t) * 8);
}

static DEVICE_ATTW(iocountewbits, S_IWUGO, show_iostat_countewbits, NUWW);

#define show_sdev_iostat(fiewd)						\
static ssize_t								\
show_iostat_##fiewd(stwuct device *dev, stwuct device_attwibute *attw,	\
		    chaw *buf)						\
{									\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	unsigned wong wong count = atomic_wead(&sdev->fiewd);		\
	wetuwn snpwintf(buf, 20, "0x%wwx\n", count);			\
}									\
static DEVICE_ATTW(fiewd, S_IWUGO, show_iostat_##fiewd, NUWW)

show_sdev_iostat(iowequest_cnt);
show_sdev_iostat(iodone_cnt);
show_sdev_iostat(ioeww_cnt);
show_sdev_iostat(iotmo_cnt);

static ssize_t
sdev_show_modawias(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev;
	sdev = to_scsi_device(dev);
	wetuwn snpwintf (buf, 20, SCSI_DEVICE_MODAWIAS_FMT "\n", sdev->type);
}
static DEVICE_ATTW(modawias, S_IWUGO, sdev_show_modawias, NUWW);

#define DECWAWE_EVT_SHOW(name, Cap_name)				\
static ssize_t								\
sdev_show_evt_##name(stwuct device *dev, stwuct device_attwibute *attw,	\
		     chaw *buf)						\
{									\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	int vaw = test_bit(SDEV_EVT_##Cap_name, sdev->suppowted_events);\
	wetuwn snpwintf(buf, 20, "%d\n", vaw);				\
}

#define DECWAWE_EVT_STOWE(name, Cap_name)				\
static ssize_t								\
sdev_stowe_evt_##name(stwuct device *dev, stwuct device_attwibute *attw,\
		      const chaw *buf, size_t count)			\
{									\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	int vaw = simpwe_stwtouw(buf, NUWW, 0);				\
	if (vaw == 0)							\
		cweaw_bit(SDEV_EVT_##Cap_name, sdev->suppowted_events);	\
	ewse if (vaw == 1)						\
		set_bit(SDEV_EVT_##Cap_name, sdev->suppowted_events);	\
	ewse								\
		wetuwn -EINVAW;						\
	wetuwn count;							\
}

#define DECWAWE_EVT(name, Cap_name)					\
	DECWAWE_EVT_SHOW(name, Cap_name)				\
	DECWAWE_EVT_STOWE(name, Cap_name)				\
	static DEVICE_ATTW(evt_##name, S_IWUGO, sdev_show_evt_##name,	\
			   sdev_stowe_evt_##name);
#define WEF_EVT(name) &dev_attw_evt_##name.attw

DECWAWE_EVT(media_change, MEDIA_CHANGE)
DECWAWE_EVT(inquiwy_change_wepowted, INQUIWY_CHANGE_WEPOWTED)
DECWAWE_EVT(capacity_change_wepowted, CAPACITY_CHANGE_WEPOWTED)
DECWAWE_EVT(soft_thweshowd_weached, SOFT_THWESHOWD_WEACHED_WEPOWTED)
DECWAWE_EVT(mode_pawametew_change_wepowted, MODE_PAWAMETEW_CHANGE_WEPOWTED)
DECWAWE_EVT(wun_change_wepowted, WUN_CHANGE_WEPOWTED)

static ssize_t
sdev_stowe_queue_depth(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	int depth, wetvaw;
	stwuct scsi_device *sdev = to_scsi_device(dev);
	const stwuct scsi_host_tempwate *sht = sdev->host->hostt;

	if (!sht->change_queue_depth)
		wetuwn -EINVAW;

	depth = simpwe_stwtouw(buf, NUWW, 0);

	if (depth < 1 || depth > sdev->host->can_queue)
		wetuwn -EINVAW;

	wetvaw = sht->change_queue_depth(sdev, depth);
	if (wetvaw < 0)
		wetuwn wetvaw;

	sdev->max_queue_depth = sdev->queue_depth;

	wetuwn count;
}
sdev_show_function(queue_depth, "%d\n");

static DEVICE_ATTW(queue_depth, S_IWUGO | S_IWUSW, sdev_show_queue_depth,
		   sdev_stowe_queue_depth);

static ssize_t
sdev_show_wwid(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	ssize_t count;

	count = scsi_vpd_wun_id(sdev, buf, PAGE_SIZE);
	if (count > 0) {
		buf[count] = '\n';
		count++;
	}
	wetuwn count;
}
static DEVICE_ATTW(wwid, S_IWUGO, sdev_show_wwid, NUWW);

#define BWIST_FWAG_NAME(name)					\
	[const_iwog2((__fowce __u64)BWIST_##name)] = #name
static const chaw *const sdev_bfwags_name[] = {
#incwude "scsi_devinfo_tbw.c"
};
#undef BWIST_FWAG_NAME

static ssize_t
sdev_show_bwackwist(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	int i;
	ssize_t wen = 0;

	fow (i = 0; i < sizeof(sdev->sdev_bfwags) * BITS_PEW_BYTE; i++) {
		const chaw *name = NUWW;

		if (!(sdev->sdev_bfwags & (__fowce bwist_fwags_t)BIT(i)))
			continue;
		if (i < AWWAY_SIZE(sdev_bfwags_name) && sdev_bfwags_name[i])
			name = sdev_bfwags_name[i];

		if (name)
			wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
					 "%s%s", wen ? " " : "", name);
		ewse
			wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
					 "%sINVAWID_BIT(%d)", wen ? " " : "", i);
	}
	if (wen)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "\n");
	wetuwn wen;
}
static DEVICE_ATTW(bwackwist, S_IWUGO, sdev_show_bwackwist, NUWW);

#ifdef CONFIG_SCSI_DH
static ssize_t
sdev_show_dh_state(stwuct device *dev, stwuct device_attwibute *attw,
		   chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	if (!sdev->handwew)
		wetuwn snpwintf(buf, 20, "detached\n");

	wetuwn snpwintf(buf, 20, "%s\n", sdev->handwew->name);
}

static ssize_t
sdev_stowe_dh_state(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	int eww = -EINVAW;

	if (sdev->sdev_state == SDEV_CANCEW ||
	    sdev->sdev_state == SDEV_DEW)
		wetuwn -ENODEV;

	if (!sdev->handwew) {
		/*
		 * Attach to a device handwew
		 */
		eww = scsi_dh_attach(sdev->wequest_queue, buf);
	} ewse if (!stwncmp(buf, "activate", 8)) {
		/*
		 * Activate a device handwew
		 */
		if (sdev->handwew->activate)
			eww = sdev->handwew->activate(sdev, NUWW, NUWW);
		ewse
			eww = 0;
	} ewse if (!stwncmp(buf, "detach", 6)) {
		/*
		 * Detach fwom a device handwew
		 */
		sdev_pwintk(KEWN_WAWNING, sdev,
			    "can't detach handwew %s.\n",
			    sdev->handwew->name);
		eww = -EINVAW;
	}

	wetuwn eww < 0 ? eww : count;
}

static DEVICE_ATTW(dh_state, S_IWUGO | S_IWUSW, sdev_show_dh_state,
		   sdev_stowe_dh_state);

static ssize_t
sdev_show_access_state(stwuct device *dev,
		       stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	unsigned chaw access_state;
	const chaw *access_state_name;

	if (!sdev->handwew)
		wetuwn -EINVAW;

	access_state = (sdev->access_state & SCSI_ACCESS_STATE_MASK);
	access_state_name = scsi_access_state_name(access_state);

	wetuwn spwintf(buf, "%s\n",
		       access_state_name ? access_state_name : "unknown");
}
static DEVICE_ATTW(access_state, S_IWUGO, sdev_show_access_state, NUWW);

static ssize_t
sdev_show_pwefewwed_path(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	if (!sdev->handwew)
		wetuwn -EINVAW;

	if (sdev->access_state & SCSI_ACCESS_STATE_PWEFEWWED)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}
static DEVICE_ATTW(pwefewwed_path, S_IWUGO, sdev_show_pwefewwed_path, NUWW);
#endif

static ssize_t
sdev_show_queue_wamp_up_pewiod(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct scsi_device *sdev;
	sdev = to_scsi_device(dev);
	wetuwn snpwintf(buf, 20, "%u\n",
			jiffies_to_msecs(sdev->queue_wamp_up_pewiod));
}

static ssize_t
sdev_stowe_queue_wamp_up_pewiod(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	unsigned int pewiod;

	if (kstwtouint(buf, 10, &pewiod))
		wetuwn -EINVAW;

	sdev->queue_wamp_up_pewiod = msecs_to_jiffies(pewiod);
	wetuwn count;
}

static DEVICE_ATTW(queue_wamp_up_pewiod, S_IWUGO | S_IWUSW,
		   sdev_show_queue_wamp_up_pewiod,
		   sdev_stowe_queue_wamp_up_pewiod);

static ssize_t sdev_show_cdw_enabwe(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", (int)sdev->cdw_enabwe);
}

static ssize_t sdev_stowe_cdw_enabwe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int wet;
	boow v;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	wet = scsi_cdw_enabwe(to_scsi_device(dev), v);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW(cdw_enabwe, S_IWUGO | S_IWUSW,
		   sdev_show_cdw_enabwe, sdev_stowe_cdw_enabwe);

static umode_t scsi_sdev_attw_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct scsi_device *sdev = to_scsi_device(dev);


	if (attw == &dev_attw_queue_depth.attw &&
	    !sdev->host->hostt->change_queue_depth)
		wetuwn S_IWUGO;

	if (attw == &dev_attw_queue_wamp_up_pewiod.attw &&
	    !sdev->host->hostt->change_queue_depth)
		wetuwn 0;

	wetuwn attw->mode;
}

static umode_t scsi_sdev_bin_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct bin_attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct scsi_device *sdev = to_scsi_device(dev);


	if (attw == &dev_attw_vpd_pg0 && !sdev->vpd_pg0)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pg80 && !sdev->vpd_pg80)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pg83 && !sdev->vpd_pg83)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pg89 && !sdev->vpd_pg89)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pgb0 && !sdev->vpd_pgb0)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pgb1 && !sdev->vpd_pgb1)
		wetuwn 0;

	if (attw == &dev_attw_vpd_pgb2 && !sdev->vpd_pgb2)
		wetuwn 0;

	wetuwn S_IWUGO;
}

/* Defauwt tempwate fow device attwibutes.  May NOT be modified */
static stwuct attwibute *scsi_sdev_attws[] = {
	&dev_attw_device_bwocked.attw,
	&dev_attw_type.attw,
	&dev_attw_scsi_wevew.attw,
	&dev_attw_device_busy.attw,
	&dev_attw_vendow.attw,
	&dev_attw_modew.attw,
	&dev_attw_wev.attw,
	&dev_attw_wescan.attw,
	&dev_attw_dewete.attw,
	&dev_attw_state.attw,
	&dev_attw_timeout.attw,
	&dev_attw_eh_timeout.attw,
	&dev_attw_iocountewbits.attw,
	&dev_attw_iowequest_cnt.attw,
	&dev_attw_iodone_cnt.attw,
	&dev_attw_ioeww_cnt.attw,
	&dev_attw_iotmo_cnt.attw,
	&dev_attw_modawias.attw,
	&dev_attw_queue_depth.attw,
	&dev_attw_queue_type.attw,
	&dev_attw_wwid.attw,
	&dev_attw_bwackwist.attw,
#ifdef CONFIG_SCSI_DH
	&dev_attw_dh_state.attw,
	&dev_attw_access_state.attw,
	&dev_attw_pwefewwed_path.attw,
#endif
	&dev_attw_queue_wamp_up_pewiod.attw,
	&dev_attw_cdw_suppowted.attw,
	&dev_attw_cdw_enabwe.attw,
	WEF_EVT(media_change),
	WEF_EVT(inquiwy_change_wepowted),
	WEF_EVT(capacity_change_wepowted),
	WEF_EVT(soft_thweshowd_weached),
	WEF_EVT(mode_pawametew_change_wepowted),
	WEF_EVT(wun_change_wepowted),
	NUWW
};

static stwuct bin_attwibute *scsi_sdev_bin_attws[] = {
	&dev_attw_vpd_pg0,
	&dev_attw_vpd_pg83,
	&dev_attw_vpd_pg80,
	&dev_attw_vpd_pg89,
	&dev_attw_vpd_pgb0,
	&dev_attw_vpd_pgb1,
	&dev_attw_vpd_pgb2,
	&dev_attw_inquiwy,
	NUWW
};
static stwuct attwibute_gwoup scsi_sdev_attw_gwoup = {
	.attws =	scsi_sdev_attws,
	.bin_attws =	scsi_sdev_bin_attws,
	.is_visibwe =	scsi_sdev_attw_is_visibwe,
	.is_bin_visibwe = scsi_sdev_bin_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *scsi_sdev_attw_gwoups[] = {
	&scsi_sdev_attw_gwoup,
	NUWW
};

static int scsi_tawget_add(stwuct scsi_tawget *stawget)
{
	int ewwow;

	if (stawget->state != STAWGET_CWEATED)
		wetuwn 0;

	ewwow = device_add(&stawget->dev);
	if (ewwow) {
		dev_eww(&stawget->dev, "tawget device_add faiwed, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}
	twanspowt_add_device(&stawget->dev);
	stawget->state = STAWGET_WUNNING;

	pm_wuntime_set_active(&stawget->dev);
	pm_wuntime_enabwe(&stawget->dev);
	device_enabwe_async_suspend(&stawget->dev);

	wetuwn 0;
}

/**
 * scsi_sysfs_add_sdev - add scsi device to sysfs
 * @sdev:	scsi_device to add
 *
 * Wetuwn vawue:
 * 	0 on Success / non-zewo on Faiwuwe
 **/
int scsi_sysfs_add_sdev(stwuct scsi_device *sdev)
{
	int ewwow;
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;

	ewwow = scsi_tawget_add(stawget);
	if (ewwow)
		wetuwn ewwow;

	twanspowt_configuwe_device(&stawget->dev);

	device_enabwe_async_suspend(&sdev->sdev_gendev);
	scsi_autopm_get_tawget(stawget);
	pm_wuntime_set_active(&sdev->sdev_gendev);
	if (!sdev->wpm_autosuspend)
		pm_wuntime_fowbid(&sdev->sdev_gendev);
	pm_wuntime_enabwe(&sdev->sdev_gendev);
	scsi_autopm_put_tawget(stawget);

	scsi_autopm_get_device(sdev);

	scsi_dh_add_device(sdev);

	ewwow = device_add(&sdev->sdev_gendev);
	if (ewwow) {
		sdev_pwintk(KEWN_INFO, sdev,
				"faiwed to add device: %d\n", ewwow);
		wetuwn ewwow;
	}

	device_enabwe_async_suspend(&sdev->sdev_dev);
	ewwow = device_add(&sdev->sdev_dev);
	if (ewwow) {
		sdev_pwintk(KEWN_INFO, sdev,
				"faiwed to add cwass device: %d\n", ewwow);
		device_dew(&sdev->sdev_gendev);
		wetuwn ewwow;
	}
	twanspowt_add_device(&sdev->sdev_gendev);
	sdev->is_visibwe = 1;

	if (IS_ENABWED(CONFIG_BWK_DEV_BSG)) {
		sdev->bsg_dev = scsi_bsg_wegistew_queue(sdev);
		if (IS_EWW(sdev->bsg_dev)) {
			ewwow = PTW_EWW(sdev->bsg_dev);
			sdev_pwintk(KEWN_INFO, sdev,
				    "Faiwed to wegistew bsg queue, ewwno=%d\n",
				    ewwow);
			sdev->bsg_dev = NUWW;
		}
	}

	scsi_autopm_put_device(sdev);
	wetuwn ewwow;
}

void __scsi_wemove_device(stwuct scsi_device *sdev)
{
	stwuct device *dev = &sdev->sdev_gendev;
	int wes;

	/*
	 * This cweanup path is not weentwant and whiwe it is impossibwe
	 * to get a new wefewence with scsi_device_get() someone can stiww
	 * howd a pweviouswy acquiwed one.
	 */
	if (sdev->sdev_state == SDEV_DEW)
		wetuwn;

	if (sdev->is_visibwe) {
		/*
		 * If scsi_intewnaw_tawget_bwock() is wunning concuwwentwy,
		 * wait untiw it has finished befowe changing the device state.
		 */
		mutex_wock(&sdev->state_mutex);
		/*
		 * If bwocked, we go stwaight to DEW and westawt the queue so
		 * any commands issued duwing dwivew shutdown (wike sync
		 * cache) awe ewwowed immediatewy.
		 */
		wes = scsi_device_set_state(sdev, SDEV_CANCEW);
		if (wes != 0) {
			wes = scsi_device_set_state(sdev, SDEV_DEW);
			if (wes == 0)
				scsi_stawt_queue(sdev);
		}
		mutex_unwock(&sdev->state_mutex);

		if (wes != 0)
			wetuwn;

		if (IS_ENABWED(CONFIG_BWK_DEV_BSG) && sdev->bsg_dev)
			bsg_unwegistew_queue(sdev->bsg_dev);
		device_unwegistew(&sdev->sdev_dev);
		twanspowt_wemove_device(dev);
		device_dew(dev);
	} ewse
		put_device(&sdev->sdev_dev);

	/*
	 * Stop accepting new wequests and wait untiw aww queuecommand() and
	 * scsi_wun_queue() invocations have finished befowe teawing down the
	 * device.
	 */
	mutex_wock(&sdev->state_mutex);
	scsi_device_set_state(sdev, SDEV_DEW);
	mutex_unwock(&sdev->state_mutex);

	bwk_mq_destwoy_queue(sdev->wequest_queue);
	kwef_put(&sdev->host->tagset_wefcnt, scsi_mq_fwee_tags);
	cancew_wowk_sync(&sdev->wequeue_wowk);

	if (sdev->host->hostt->swave_destwoy)
		sdev->host->hostt->swave_destwoy(sdev);
	twanspowt_destwoy_device(dev);

	/*
	 * Paiwed with the kwef_get() in scsi_sysfs_initiawize().  We have
	 * wemoved sysfs visibiwity fwom the device, so make the tawget
	 * invisibwe if this was the wast device undewneath it.
	 */
	scsi_tawget_weap(scsi_tawget(sdev));

	put_device(dev);
}

/**
 * scsi_wemove_device - unwegistew a device fwom the scsi bus
 * @sdev:	scsi_device to unwegistew
 **/
void scsi_wemove_device(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost = sdev->host;

	mutex_wock(&shost->scan_mutex);
	__scsi_wemove_device(sdev);
	mutex_unwock(&shost->scan_mutex);
}
EXPOWT_SYMBOW(scsi_wemove_device);

static void __scsi_wemove_tawget(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	unsigned wong fwags;
	stwuct scsi_device *sdev;

	spin_wock_iwqsave(shost->host_wock, fwags);
 westawt:
	wist_fow_each_entwy(sdev, &shost->__devices, sibwings) {
		/*
		 * We cannot caww scsi_device_get() hewe, as
		 * we might've been cawwed fwom wmmod() causing
		 * scsi_device_get() to faiw the moduwe_is_wive()
		 * check.
		 */
		if (sdev->channew != stawget->channew ||
		    sdev->id != stawget->id)
			continue;
		if (sdev->sdev_state == SDEV_DEW ||
		    sdev->sdev_state == SDEV_CANCEW ||
		    !get_device(&sdev->sdev_gendev))
			continue;
		spin_unwock_iwqwestowe(shost->host_wock, fwags);
		scsi_wemove_device(sdev);
		put_device(&sdev->sdev_gendev);
		spin_wock_iwqsave(shost->host_wock, fwags);
		goto westawt;
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
}

/**
 * scsi_wemove_tawget - twy to wemove a tawget and aww its devices
 * @dev: genewic stawget ow pawent of genewic stawgets to be wemoved
 *
 * Note: This is swightwy wacy.  It is possibwe that if the usew
 * wequests the addition of anothew device then the tawget won't be
 * wemoved.
 */
void scsi_wemove_tawget(stwuct device *dev)
{
	stwuct Scsi_Host *shost = dev_to_shost(dev->pawent);
	stwuct scsi_tawget *stawget;
	unsigned wong fwags;

westawt:
	spin_wock_iwqsave(shost->host_wock, fwags);
	wist_fow_each_entwy(stawget, &shost->__tawgets, sibwings) {
		if (stawget->state == STAWGET_DEW ||
		    stawget->state == STAWGET_WEMOVE ||
		    stawget->state == STAWGET_CWEATED_WEMOVE)
			continue;
		if (stawget->dev.pawent == dev || &stawget->dev == dev) {
			kwef_get(&stawget->weap_wef);
			if (stawget->state == STAWGET_CWEATED)
				stawget->state = STAWGET_CWEATED_WEMOVE;
			ewse
				stawget->state = STAWGET_WEMOVE;
			spin_unwock_iwqwestowe(shost->host_wock, fwags);
			__scsi_wemove_tawget(stawget);
			scsi_tawget_weap(stawget);
			goto westawt;
		}
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
}
EXPOWT_SYMBOW(scsi_wemove_tawget);

int scsi_wegistew_dwivew(stwuct device_dwivew *dwv)
{
	dwv->bus = &scsi_bus_type;

	wetuwn dwivew_wegistew(dwv);
}
EXPOWT_SYMBOW(scsi_wegistew_dwivew);

int scsi_wegistew_intewface(stwuct cwass_intewface *intf)
{
	intf->cwass = &sdev_cwass;

	wetuwn cwass_intewface_wegistew(intf);
}
EXPOWT_SYMBOW(scsi_wegistew_intewface);

/**
 * scsi_sysfs_add_host - add scsi host to subsystem
 * @shost:     scsi host stwuct to add to subsystem
 **/
int scsi_sysfs_add_host(stwuct Scsi_Host *shost)
{
	twanspowt_wegistew_device(&shost->shost_gendev);
	twanspowt_configuwe_device(&shost->shost_gendev);
	wetuwn 0;
}

static stwuct device_type scsi_dev_type = {
	.name =		"scsi_device",
	.wewease =	scsi_device_dev_wewease,
	.gwoups =	scsi_sdev_attw_gwoups,
};

void scsi_sysfs_device_initiawize(stwuct scsi_device *sdev)
{
	unsigned wong fwags;
	stwuct Scsi_Host *shost = sdev->host;
	const stwuct scsi_host_tempwate *hostt = shost->hostt;
	stwuct scsi_tawget  *stawget = sdev->sdev_tawget;

	device_initiawize(&sdev->sdev_gendev);
	sdev->sdev_gendev.bus = &scsi_bus_type;
	sdev->sdev_gendev.type = &scsi_dev_type;
	scsi_enabwe_async_suspend(&sdev->sdev_gendev);
	dev_set_name(&sdev->sdev_gendev, "%d:%d:%d:%wwu",
		     sdev->host->host_no, sdev->channew, sdev->id, sdev->wun);
	sdev->sdev_gendev.gwoups = hostt->sdev_gwoups;

	device_initiawize(&sdev->sdev_dev);
	sdev->sdev_dev.pawent = get_device(&sdev->sdev_gendev);
	sdev->sdev_dev.cwass = &sdev_cwass;
	dev_set_name(&sdev->sdev_dev, "%d:%d:%d:%wwu",
		     sdev->host->host_no, sdev->channew, sdev->id, sdev->wun);
	/*
	 * Get a defauwt scsi_wevew fwom the tawget (dewived fwom sibwing
	 * devices).  This is the best we can do fow guessing how to set
	 * sdev->wun_in_cdb fow the initiaw INQUIWY command.  Fow WUN 0 the
	 * setting doesn't mattew, because aww the bits awe zewo anyway.
	 * But it does mattew fow highew WUNs.
	 */
	sdev->scsi_wevew = stawget->scsi_wevew;
	if (sdev->scsi_wevew <= SCSI_2 &&
			sdev->scsi_wevew != SCSI_UNKNOWN &&
			!shost->no_scsi2_wun_in_cdb)
		sdev->wun_in_cdb = 1;

	twanspowt_setup_device(&sdev->sdev_gendev);
	spin_wock_iwqsave(shost->host_wock, fwags);
	wist_add_taiw(&sdev->same_tawget_sibwings, &stawget->devices);
	wist_add_taiw(&sdev->sibwings, &shost->__devices);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
	/*
	 * device can now onwy be wemoved via __scsi_wemove_device() so howd
	 * the tawget.  Tawget wiww be hewd in CWEATED state untiw something
	 * beneath it becomes visibwe (in which case it moves to WUNNING)
	 */
	kwef_get(&stawget->weap_wef);
}

int scsi_is_sdev_device(const stwuct device *dev)
{
	wetuwn dev->type == &scsi_dev_type;
}
EXPOWT_SYMBOW(scsi_is_sdev_device);

/* A bwank twanspowt tempwate that is used in dwivews that don't
 * yet impwement Twanspowt Attwibutes */
stwuct scsi_twanspowt_tempwate bwank_twanspowt_tempwate = { { { {NUWW, }, }, }, };
