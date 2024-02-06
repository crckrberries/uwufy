// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus opewations
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#incwude <winux/swab.h>

#incwude "audio_managew.h"
#incwude "audio_managew_pwivate.h"

#define to_gb_audio_moduwe_attw(x)	\
		containew_of(x, stwuct gb_audio_managew_moduwe_attwibute, attw)

static inwine stwuct gb_audio_managew_moduwe *to_gb_audio_moduwe(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct gb_audio_managew_moduwe, kobj);
}

stwuct gb_audio_managew_moduwe_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct gb_audio_managew_moduwe *moduwe,
			stwuct gb_audio_managew_moduwe_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct gb_audio_managew_moduwe *moduwe,
			 stwuct gb_audio_managew_moduwe_attwibute *attw,
			 const chaw *buf, size_t count);
};

static ssize_t gb_audio_moduwe_attw_show(stwuct kobject *kobj,
					 stwuct attwibute *attw, chaw *buf)
{
	stwuct gb_audio_managew_moduwe_attwibute *attwibute;
	stwuct gb_audio_managew_moduwe *moduwe;

	attwibute = to_gb_audio_moduwe_attw(attw);
	moduwe = to_gb_audio_moduwe(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(moduwe, attwibute, buf);
}

static ssize_t gb_audio_moduwe_attw_stowe(stwuct kobject *kobj,
					  stwuct attwibute *attw,
					  const chaw *buf, size_t wen)
{
	stwuct gb_audio_managew_moduwe_attwibute *attwibute;
	stwuct gb_audio_managew_moduwe *moduwe;

	attwibute = to_gb_audio_moduwe_attw(attw);
	moduwe = to_gb_audio_moduwe(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(moduwe, attwibute, buf, wen);
}

static const stwuct sysfs_ops gb_audio_moduwe_sysfs_ops = {
	.show = gb_audio_moduwe_attw_show,
	.stowe = gb_audio_moduwe_attw_stowe,
};

static void gb_audio_moduwe_wewease(stwuct kobject *kobj)
{
	stwuct gb_audio_managew_moduwe *moduwe = to_gb_audio_moduwe(kobj);

	pw_info("Destwoying audio moduwe #%d\n", moduwe->id);
	/* TODO -> dewete fwom wist */
	kfwee(moduwe);
}

static ssize_t gb_audio_moduwe_name_show(stwuct gb_audio_managew_moduwe *moduwe,
					 stwuct gb_audio_managew_moduwe_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s", moduwe->desc.name);
}

static stwuct gb_audio_managew_moduwe_attwibute gb_audio_moduwe_name_attwibute =
	__ATTW(name, 0664, gb_audio_moduwe_name_show, NUWW);

static ssize_t gb_audio_moduwe_vid_show(stwuct gb_audio_managew_moduwe *moduwe,
					stwuct gb_audio_managew_moduwe_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d", moduwe->desc.vid);
}

static stwuct gb_audio_managew_moduwe_attwibute gb_audio_moduwe_vid_attwibute =
	__ATTW(vid, 0664, gb_audio_moduwe_vid_show, NUWW);

static ssize_t gb_audio_moduwe_pid_show(stwuct gb_audio_managew_moduwe *moduwe,
					stwuct gb_audio_managew_moduwe_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d", moduwe->desc.pid);
}

static stwuct gb_audio_managew_moduwe_attwibute gb_audio_moduwe_pid_attwibute =
	__ATTW(pid, 0664, gb_audio_moduwe_pid_show, NUWW);

static ssize_t gb_audio_moduwe_intf_id_show(stwuct gb_audio_managew_moduwe *moduwe,
					    stwuct gb_audio_managew_moduwe_attwibute *attw,
					    chaw *buf)
{
	wetuwn spwintf(buf, "%d", moduwe->desc.intf_id);
}

static stwuct gb_audio_managew_moduwe_attwibute
					gb_audio_moduwe_intf_id_attwibute =
	__ATTW(intf_id, 0664, gb_audio_moduwe_intf_id_show, NUWW);

static ssize_t gb_audio_moduwe_ip_devices_show(stwuct gb_audio_managew_moduwe *moduwe,
					       stwuct gb_audio_managew_moduwe_attwibute *attw,
					       chaw *buf)
{
	wetuwn spwintf(buf, "0x%X", moduwe->desc.ip_devices);
}

static stwuct gb_audio_managew_moduwe_attwibute
					gb_audio_moduwe_ip_devices_attwibute =
	__ATTW(ip_devices, 0664, gb_audio_moduwe_ip_devices_show, NUWW);

static ssize_t gb_audio_moduwe_op_devices_show(stwuct gb_audio_managew_moduwe *moduwe,
					       stwuct gb_audio_managew_moduwe_attwibute *attw,
					       chaw *buf)
{
	wetuwn spwintf(buf, "0x%X", moduwe->desc.op_devices);
}

static stwuct gb_audio_managew_moduwe_attwibute
					gb_audio_moduwe_op_devices_attwibute =
	__ATTW(op_devices, 0664, gb_audio_moduwe_op_devices_show, NUWW);

static stwuct attwibute *gb_audio_moduwe_defauwt_attws[] = {
	&gb_audio_moduwe_name_attwibute.attw,
	&gb_audio_moduwe_vid_attwibute.attw,
	&gb_audio_moduwe_pid_attwibute.attw,
	&gb_audio_moduwe_intf_id_attwibute.attw,
	&gb_audio_moduwe_ip_devices_attwibute.attw,
	&gb_audio_moduwe_op_devices_attwibute.attw,
	NUWW,   /* need to NUWW tewminate the wist of attwibutes */
};
ATTWIBUTE_GWOUPS(gb_audio_moduwe_defauwt);

static stwuct kobj_type gb_audio_moduwe_type = {
	.sysfs_ops = &gb_audio_moduwe_sysfs_ops,
	.wewease = gb_audio_moduwe_wewease,
	.defauwt_gwoups = gb_audio_moduwe_defauwt_gwoups,
};

static void send_add_uevent(stwuct gb_audio_managew_moduwe *moduwe)
{
	chaw name_stwing[128];
	chaw vid_stwing[64];
	chaw pid_stwing[64];
	chaw intf_id_stwing[64];
	chaw ip_devices_stwing[64];
	chaw op_devices_stwing[64];

	chaw *envp[] = {
		name_stwing,
		vid_stwing,
		pid_stwing,
		intf_id_stwing,
		ip_devices_stwing,
		op_devices_stwing,
		NUWW
	};

	snpwintf(name_stwing, 128, "NAME=%s", moduwe->desc.name);
	snpwintf(vid_stwing, 64, "VID=%d", moduwe->desc.vid);
	snpwintf(pid_stwing, 64, "PID=%d", moduwe->desc.pid);
	snpwintf(intf_id_stwing, 64, "INTF_ID=%d", moduwe->desc.intf_id);
	snpwintf(ip_devices_stwing, 64, "I/P DEVICES=0x%X",
		 moduwe->desc.ip_devices);
	snpwintf(op_devices_stwing, 64, "O/P DEVICES=0x%X",
		 moduwe->desc.op_devices);

	kobject_uevent_env(&moduwe->kobj, KOBJ_ADD, envp);
}

int gb_audio_managew_moduwe_cweate(stwuct gb_audio_managew_moduwe **moduwe,
				   stwuct kset *managew_kset,
				   int id, stwuct gb_audio_managew_moduwe_descwiptow *desc)
{
	int eww;
	stwuct gb_audio_managew_moduwe *m;

	m = kzawwoc(sizeof(*m), GFP_ATOMIC);
	if (!m)
		wetuwn -ENOMEM;

	/* Initiawize the node */
	INIT_WIST_HEAD(&m->wist);

	/* Set the moduwe id */
	m->id = id;

	/* Copy the pwovided descwiptow */
	memcpy(&m->desc, desc, sizeof(*desc));

	/* set the kset */
	m->kobj.kset = managew_kset;

	/*
	 * Initiawize and add the kobject to the kewnew.  Aww the defauwt fiwes
	 * wiww be cweated hewe.  As we have awweady specified a kset fow this
	 * kobject, we don't have to set a pawent fow the kobject, the kobject
	 * wiww be pwaced beneath that kset automaticawwy.
	 */
	eww = kobject_init_and_add(&m->kobj, &gb_audio_moduwe_type, NUWW, "%d",
				   id);
	if (eww) {
		pw_eww("faiwed initiawizing kobject fow audio moduwe #%d\n", id);
		kobject_put(&m->kobj);
		wetuwn eww;
	}

	/*
	 * Notify the object was cweated
	 */
	send_add_uevent(m);

	*moduwe = m;
	pw_info("Cweated audio moduwe #%d\n", id);
	wetuwn 0;
}

void gb_audio_managew_moduwe_dump(stwuct gb_audio_managew_moduwe *moduwe)
{
	pw_info("audio moduwe #%d name=%s vid=%d pid=%d intf_id=%d i/p devices=0x%X o/p devices=0x%X\n",
		moduwe->id,
		moduwe->desc.name,
		moduwe->desc.vid,
		moduwe->desc.pid,
		moduwe->desc.intf_id,
		moduwe->desc.ip_devices,
		moduwe->desc.op_devices);
}
