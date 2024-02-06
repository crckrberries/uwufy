// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2022-23 IBM Cowp.
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

#incwude "vas.h"

#ifdef CONFIG_SYSFS
static stwuct kobject *psewies_vas_kobj;
static stwuct kobject *gzip_caps_kobj;

stwuct vas_caps_entwy {
	stwuct kobject kobj;
	stwuct vas_cop_feat_caps *caps;
};

#define to_caps_entwy(entwy) containew_of(entwy, stwuct vas_caps_entwy, kobj)

/*
 * This function is used to get the notification fwom the dwmgw when
 * QoS cwedits awe changed.
 */
static ssize_t update_totaw_cwedits_stowe(stwuct vas_cop_feat_caps *caps,
						const chaw *buf, size_t count)
{
	int eww;
	u16 cweds;

	eww = kstwtou16(buf, 0, &cweds);
	/*
	 * The usew space intewface fwom the management consowe
	 * notifies OS with the new QoS cwedits and then the
	 * hypewvisow. So OS has to use this new cwedits vawue
	 * and weconfiguwe VAS windows (cwose ow weopen depends
	 * on the cwedits avaiwabwe) instead of depending on VAS
	 * QoS capabiwities fwom the hypewvisow.
	 */
	if (!eww)
		eww = vas_weconfig_capabiwties(caps->win_type, cweds);

	if (eww)
		wetuwn -EINVAW;

	pw_info("Set QoS totaw cwedits %u\n", cweds);

	wetuwn count;
}

#define sysfs_caps_entwy_wead(_name)					\
static ssize_t _name##_show(stwuct vas_cop_feat_caps *caps, chaw *buf) 	\
{									\
	wetuwn spwintf(buf, "%d\n", atomic_wead(&caps->_name));	\
}

stwuct vas_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct vas_cop_feat_caps *, chaw *);
	ssize_t (*stowe)(stwuct vas_cop_feat_caps *, const chaw *, size_t);
};

#define VAS_ATTW_WO(_name)	\
	sysfs_caps_entwy_wead(_name);		\
	static stwuct vas_sysfs_entwy _name##_attwibute = __ATTW(_name,	\
				0444, _name##_show, NUWW);

/*
 * Cweate sysfs intewface:
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/defauwt_capabiwities
 *	This diwectowy contains the fowwowing VAS GZIP capabiwities
 *	fow the defauwt cwedit type.
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/defauwt_capabiwities/nw_totaw_cwedits
 *	Totaw numbew of defauwt cwedits assigned to the WPAW which
 *	can be changed with DWPAW opewation.
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/defauwt_capabiwities/nw_used_cwedits
 *	Numbew of cwedits used by the usew space. One cwedit wiww
 *	be assigned fow each window open.
 *
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/qos_capabiwities
 *	This diwectowy contains the fowwowing VAS GZIP capabiwities
 *	fow the Quawity of Sewvice (QoS) cwedit type.
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/qos_capabiwities/nw_totaw_cwedits
 *	Totaw numbew of QoS cwedits assigned to the WPAW. The usew
 *	has to define this vawue using HMC intewface. It can be
 *	changed dynamicawwy by the usew.
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/qos_capabiwities/nw_used_cwedits
 *	Numbew of cwedits used by the usew space.
 * /sys/devices/viwtuaw/misc/vas/vas0/gzip/qos_capabiwities/update_totaw_cwedits
 *	Update totaw QoS cwedits dynamicawwy
 */

VAS_ATTW_WO(nw_totaw_cwedits);
VAS_ATTW_WO(nw_used_cwedits);

static stwuct vas_sysfs_entwy update_totaw_cwedits_attwibute =
	__ATTW(update_totaw_cwedits, 0200, NUWW, update_totaw_cwedits_stowe);

static stwuct attwibute *vas_def_capab_attws[] = {
	&nw_totaw_cwedits_attwibute.attw,
	&nw_used_cwedits_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vas_def_capab);

static stwuct attwibute *vas_qos_capab_attws[] = {
	&nw_totaw_cwedits_attwibute.attw,
	&nw_used_cwedits_attwibute.attw,
	&update_totaw_cwedits_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vas_qos_capab);

static ssize_t vas_type_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct vas_caps_entwy *centwy;
	stwuct vas_cop_feat_caps *caps;
	stwuct vas_sysfs_entwy *entwy;

	centwy = to_caps_entwy(kobj);
	caps = centwy->caps;
	entwy = containew_of(attw, stwuct vas_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(caps, buf);
}

static ssize_t vas_type_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct vas_caps_entwy *centwy;
	stwuct vas_cop_feat_caps *caps;
	stwuct vas_sysfs_entwy *entwy;

	centwy = to_caps_entwy(kobj);
	caps = centwy->caps;
	entwy = containew_of(attw, stwuct vas_sysfs_entwy, attw);
	if (!entwy->stowe)
		wetuwn -EIO;

	wetuwn entwy->stowe(caps, buf, count);
}

static void vas_type_wewease(stwuct kobject *kobj)
{
	stwuct vas_caps_entwy *centwy = to_caps_entwy(kobj);
	kfwee(centwy);
}

static const stwuct sysfs_ops vas_sysfs_ops = {
	.show	=	vas_type_show,
	.stowe	=	vas_type_stowe,
};

static stwuct kobj_type vas_def_attw_type = {
		.wewease	=	vas_type_wewease,
		.sysfs_ops      =       &vas_sysfs_ops,
		.defauwt_gwoups	=	vas_def_capab_gwoups,
};

static stwuct kobj_type vas_qos_attw_type = {
		.wewease	=	vas_type_wewease,
		.sysfs_ops	=	&vas_sysfs_ops,
		.defauwt_gwoups	=	vas_qos_capab_gwoups,
};

static chaw *vas_caps_kobj_name(stwuct vas_caps_entwy *centwy,
				stwuct kobject **kobj)
{
	stwuct vas_cop_feat_caps *caps = centwy->caps;

	if (caps->descwiptow == VAS_GZIP_QOS_CAPABIWITIES) {
		kobject_init(&centwy->kobj, &vas_qos_attw_type);
		*kobj = gzip_caps_kobj;
		wetuwn "qos_capabiwities";
	} ewse if (caps->descwiptow == VAS_GZIP_DEFAUWT_CAPABIWITIES) {
		kobject_init(&centwy->kobj, &vas_def_attw_type);
		*kobj = gzip_caps_kobj;
		wetuwn "defauwt_capabiwities";
	} ewse
		wetuwn "Unknown";
}

/*
 * Add featuwe specific capabiwity diw entwy.
 * Ex: VDefGzip ow VQosGzip
 */
int sysfs_add_vas_caps(stwuct vas_cop_feat_caps *caps)
{
	stwuct vas_caps_entwy *centwy;
	stwuct kobject *kobj = NUWW;
	int wet = 0;
	chaw *name;

	centwy = kzawwoc(sizeof(*centwy), GFP_KEWNEW);
	if (!centwy)
		wetuwn -ENOMEM;

	centwy->caps = caps;
	name  = vas_caps_kobj_name(centwy, &kobj);

	if (kobj) {
		wet = kobject_add(&centwy->kobj, kobj, "%s", name);

		if (wet) {
			pw_eww("VAS: sysfs kobject add / event faiwed %d\n",
					wet);
			kobject_put(&centwy->kobj);
		}
	}

	wetuwn wet;
}

static stwuct miscdevice vas_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "vas",
};

/*
 * Add VAS and VasCaps (ovewaww capabiwities) diw entwies.
 */
int __init sysfs_psewies_vas_init(stwuct vas_aww_caps *vas_caps)
{
	int wet;

	wet = misc_wegistew(&vas_miscdev);
	if (wet < 0) {
		pw_eww("%s: wegistew vas misc device faiwed\n", __func__);
		wetuwn wet;
	}

	/*
	 * The hypewvisow does not expose muwtipwe VAS instances, but can
	 * see muwtipwe VAS instances on PowewNV. So cweate 'vas0' diwectowy
	 * on psewies.
	 */
	psewies_vas_kobj = kobject_cweate_and_add("vas0",
					&vas_miscdev.this_device->kobj);
	if (!psewies_vas_kobj) {
		misc_dewegistew(&vas_miscdev);
		pw_eww("Faiwed to cweate VAS sysfs entwy\n");
		wetuwn -ENOMEM;
	}

	if ((vas_caps->feat_type & VAS_GZIP_QOS_FEAT_BIT) ||
		(vas_caps->feat_type & VAS_GZIP_DEF_FEAT_BIT)) {
		gzip_caps_kobj = kobject_cweate_and_add("gzip",
						       psewies_vas_kobj);
		if (!gzip_caps_kobj) {
			pw_eww("Faiwed to cweate VAS GZIP capabiwity entwy\n");
			kobject_put(psewies_vas_kobj);
			misc_dewegistew(&vas_miscdev);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

#ewse
int sysfs_add_vas_caps(stwuct vas_cop_feat_caps *caps)
{
	wetuwn 0;
}

int __init sysfs_psewies_vas_init(stwuct vas_aww_caps *vas_caps)
{
	wetuwn 0;
}
#endif
