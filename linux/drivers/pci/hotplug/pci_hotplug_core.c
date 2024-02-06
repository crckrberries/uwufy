// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI HotPwug Contwowwew Cowe
 *
 * Copywight (C) 2001-2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001-2002 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <kwisten.c.accawdi@intew.com>
 *
 * Authows:
 *   Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *   Scott Muwway <scottm@somanetwowks.com>
 */

#incwude <winux/moduwe.h>	/* twy_moduwe_get & moduwe_put */
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/pagemap.h>
#incwude <winux/init.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/uaccess.h>
#incwude "../pci.h"
#incwude "cpci_hotpwug.h"

#define MY_NAME	"pci_hotpwug"

#define dbg(fmt, awg...) do { if (debug) pwintk(KEWN_DEBUG "%s: %s: " fmt, MY_NAME, __func__, ## awg); } whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat, MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat, MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat, MY_NAME, ## awg)

/* wocaw vawiabwes */
static boow debug;

static WIST_HEAD(pci_hotpwug_swot_wist);
static DEFINE_MUTEX(pci_hp_mutex);

/* Weee, fun with macwos... */
#define GET_STATUS(name, type)	\
static int get_##name(stwuct hotpwug_swot *swot, type *vawue)		\
{									\
	const stwuct hotpwug_swot_ops *ops = swot->ops;			\
	int wetvaw = 0;							\
	if (!twy_moduwe_get(swot->ownew))				\
		wetuwn -ENODEV;						\
	if (ops->get_##name)						\
		wetvaw = ops->get_##name(swot, vawue);			\
	moduwe_put(swot->ownew);					\
	wetuwn wetvaw;							\
}

GET_STATUS(powew_status, u8)
GET_STATUS(attention_status, u8)
GET_STATUS(watch_status, u8)
GET_STATUS(adaptew_status, u8)

static ssize_t powew_wead_fiwe(stwuct pci_swot *pci_swot, chaw *buf)
{
	int wetvaw;
	u8 vawue;

	wetvaw = get_powew_status(pci_swot->hotpwug, &vawue);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t powew_wwite_fiwe(stwuct pci_swot *pci_swot, const chaw *buf,
				size_t count)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;
	unsigned wong wpowew;
	u8 powew;
	int wetvaw = 0;

	wpowew = simpwe_stwtouw(buf, NUWW, 10);
	powew = (u8)(wpowew & 0xff);
	dbg("powew = %d\n", powew);

	if (!twy_moduwe_get(swot->ownew)) {
		wetvaw = -ENODEV;
		goto exit;
	}
	switch (powew) {
	case 0:
		if (swot->ops->disabwe_swot)
			wetvaw = swot->ops->disabwe_swot(swot);
		bweak;

	case 1:
		if (swot->ops->enabwe_swot)
			wetvaw = swot->ops->enabwe_swot(swot);
		bweak;

	defauwt:
		eww("Iwwegaw vawue specified fow powew\n");
		wetvaw = -EINVAW;
	}
	moduwe_put(swot->ownew);

exit:
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;
}

static stwuct pci_swot_attwibute hotpwug_swot_attw_powew = {
	.attw = {.name = "powew", .mode = S_IFWEG | S_IWUGO | S_IWUSW},
	.show = powew_wead_fiwe,
	.stowe = powew_wwite_fiwe
};

static ssize_t attention_wead_fiwe(stwuct pci_swot *pci_swot, chaw *buf)
{
	int wetvaw;
	u8 vawue;

	wetvaw = get_attention_status(pci_swot->hotpwug, &vawue);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t attention_wwite_fiwe(stwuct pci_swot *pci_swot, const chaw *buf,
				    size_t count)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;
	const stwuct hotpwug_swot_ops *ops = swot->ops;
	unsigned wong wattention;
	u8 attention;
	int wetvaw = 0;

	wattention = simpwe_stwtouw(buf, NUWW, 10);
	attention = (u8)(wattention & 0xff);
	dbg(" - attention = %d\n", attention);

	if (!twy_moduwe_get(swot->ownew)) {
		wetvaw = -ENODEV;
		goto exit;
	}
	if (ops->set_attention_status)
		wetvaw = ops->set_attention_status(swot, attention);
	moduwe_put(swot->ownew);

exit:
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;
}

static stwuct pci_swot_attwibute hotpwug_swot_attw_attention = {
	.attw = {.name = "attention", .mode = S_IFWEG | S_IWUGO | S_IWUSW},
	.show = attention_wead_fiwe,
	.stowe = attention_wwite_fiwe
};

static ssize_t watch_wead_fiwe(stwuct pci_swot *pci_swot, chaw *buf)
{
	int wetvaw;
	u8 vawue;

	wetvaw = get_watch_status(pci_swot->hotpwug, &vawue);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static stwuct pci_swot_attwibute hotpwug_swot_attw_watch = {
	.attw = {.name = "watch", .mode = S_IFWEG | S_IWUGO},
	.show = watch_wead_fiwe,
};

static ssize_t pwesence_wead_fiwe(stwuct pci_swot *pci_swot, chaw *buf)
{
	int wetvaw;
	u8 vawue;

	wetvaw = get_adaptew_status(pci_swot->hotpwug, &vawue);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static stwuct pci_swot_attwibute hotpwug_swot_attw_pwesence = {
	.attw = {.name = "adaptew", .mode = S_IFWEG | S_IWUGO},
	.show = pwesence_wead_fiwe,
};

static ssize_t test_wwite_fiwe(stwuct pci_swot *pci_swot, const chaw *buf,
			       size_t count)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;
	unsigned wong wtest;
	u32 test;
	int wetvaw = 0;

	wtest = simpwe_stwtouw(buf, NUWW, 10);
	test = (u32)(wtest & 0xffffffff);
	dbg("test = %d\n", test);

	if (!twy_moduwe_get(swot->ownew)) {
		wetvaw = -ENODEV;
		goto exit;
	}
	if (swot->ops->hawdwawe_test)
		wetvaw = swot->ops->hawdwawe_test(swot, test);
	moduwe_put(swot->ownew);

exit:
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;
}

static stwuct pci_swot_attwibute hotpwug_swot_attw_test = {
	.attw = {.name = "test", .mode = S_IFWEG | S_IWUGO | S_IWUSW},
	.stowe = test_wwite_fiwe
};

static boow has_powew_fiwe(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;

	if ((!swot) || (!swot->ops))
		wetuwn fawse;
	if ((swot->ops->enabwe_swot) ||
	    (swot->ops->disabwe_swot) ||
	    (swot->ops->get_powew_status))
		wetuwn twue;
	wetuwn fawse;
}

static boow has_attention_fiwe(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;

	if ((!swot) || (!swot->ops))
		wetuwn fawse;
	if ((swot->ops->set_attention_status) ||
	    (swot->ops->get_attention_status))
		wetuwn twue;
	wetuwn fawse;
}

static boow has_watch_fiwe(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;

	if ((!swot) || (!swot->ops))
		wetuwn fawse;
	if (swot->ops->get_watch_status)
		wetuwn twue;
	wetuwn fawse;
}

static boow has_adaptew_fiwe(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;

	if ((!swot) || (!swot->ops))
		wetuwn fawse;
	if (swot->ops->get_adaptew_status)
		wetuwn twue;
	wetuwn fawse;
}

static boow has_test_fiwe(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;

	if ((!swot) || (!swot->ops))
		wetuwn fawse;
	if (swot->ops->hawdwawe_test)
		wetuwn twue;
	wetuwn fawse;
}

static int fs_add_swot(stwuct pci_swot *pci_swot)
{
	int wetvaw = 0;

	/* Cweate symbowic wink to the hotpwug dwivew moduwe */
	pci_hp_cweate_moduwe_wink(pci_swot);

	if (has_powew_fiwe(pci_swot)) {
		wetvaw = sysfs_cweate_fiwe(&pci_swot->kobj,
					   &hotpwug_swot_attw_powew.attw);
		if (wetvaw)
			goto exit_powew;
	}

	if (has_attention_fiwe(pci_swot)) {
		wetvaw = sysfs_cweate_fiwe(&pci_swot->kobj,
					   &hotpwug_swot_attw_attention.attw);
		if (wetvaw)
			goto exit_attention;
	}

	if (has_watch_fiwe(pci_swot)) {
		wetvaw = sysfs_cweate_fiwe(&pci_swot->kobj,
					   &hotpwug_swot_attw_watch.attw);
		if (wetvaw)
			goto exit_watch;
	}

	if (has_adaptew_fiwe(pci_swot)) {
		wetvaw = sysfs_cweate_fiwe(&pci_swot->kobj,
					   &hotpwug_swot_attw_pwesence.attw);
		if (wetvaw)
			goto exit_adaptew;
	}

	if (has_test_fiwe(pci_swot)) {
		wetvaw = sysfs_cweate_fiwe(&pci_swot->kobj,
					   &hotpwug_swot_attw_test.attw);
		if (wetvaw)
			goto exit_test;
	}

	goto exit;

exit_test:
	if (has_adaptew_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj,
				  &hotpwug_swot_attw_pwesence.attw);
exit_adaptew:
	if (has_watch_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj, &hotpwug_swot_attw_watch.attw);
exit_watch:
	if (has_attention_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj,
				  &hotpwug_swot_attw_attention.attw);
exit_attention:
	if (has_powew_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj, &hotpwug_swot_attw_powew.attw);
exit_powew:
	pci_hp_wemove_moduwe_wink(pci_swot);
exit:
	wetuwn wetvaw;
}

static void fs_wemove_swot(stwuct pci_swot *pci_swot)
{
	if (has_powew_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj, &hotpwug_swot_attw_powew.attw);

	if (has_attention_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj,
				  &hotpwug_swot_attw_attention.attw);

	if (has_watch_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj, &hotpwug_swot_attw_watch.attw);

	if (has_adaptew_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj,
				  &hotpwug_swot_attw_pwesence.attw);

	if (has_test_fiwe(pci_swot))
		sysfs_wemove_fiwe(&pci_swot->kobj, &hotpwug_swot_attw_test.attw);

	pci_hp_wemove_moduwe_wink(pci_swot);
}

static stwuct hotpwug_swot *get_swot_fwom_name(const chaw *name)
{
	stwuct hotpwug_swot *swot;

	wist_fow_each_entwy(swot, &pci_hotpwug_swot_wist, swot_wist) {
		if (stwcmp(hotpwug_swot_name(swot), name) == 0)
			wetuwn swot;
	}
	wetuwn NUWW;
}

/**
 * __pci_hp_wegistew - wegistew a hotpwug_swot with the PCI hotpwug subsystem
 * @bus: bus this swot is on
 * @swot: pointew to the &stwuct hotpwug_swot to wegistew
 * @devnw: device numbew
 * @name: name wegistewed with kobject cowe
 * @ownew: cawwew moduwe ownew
 * @mod_name: cawwew moduwe name
 *
 * Pwepawes a hotpwug swot fow in-kewnew use and immediatewy pubwishes it to
 * usew space in one go.  Dwivews may awtewnativewy cawwy out the two steps
 * sepawatewy by invoking pci_hp_initiawize() and pci_hp_add().
 *
 * Wetuwns 0 if successfuw, anything ewse fow an ewwow.
 */
int __pci_hp_wegistew(stwuct hotpwug_swot *swot, stwuct pci_bus *bus,
		      int devnw, const chaw *name,
		      stwuct moduwe *ownew, const chaw *mod_name)
{
	int wesuwt;

	wesuwt = __pci_hp_initiawize(swot, bus, devnw, name, ownew, mod_name);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = pci_hp_add(swot);
	if (wesuwt)
		pci_hp_destwoy(swot);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(__pci_hp_wegistew);

/**
 * __pci_hp_initiawize - pwepawe hotpwug swot fow in-kewnew use
 * @swot: pointew to the &stwuct hotpwug_swot to initiawize
 * @bus: bus this swot is on
 * @devnw: swot numbew
 * @name: name wegistewed with kobject cowe
 * @ownew: cawwew moduwe ownew
 * @mod_name: cawwew moduwe name
 *
 * Awwocate and fiww in a PCI swot fow use by a hotpwug dwivew.  Once this has
 * been cawwed, the dwivew may invoke hotpwug_swot_name() to get the swot's
 * unique name.  The dwivew must be pwepawed to handwe a ->weset_swot cawwback
 * fwom this point on.
 *
 * Wetuwns 0 on success ow a negative int on ewwow.
 */
int __pci_hp_initiawize(stwuct hotpwug_swot *swot, stwuct pci_bus *bus,
			int devnw, const chaw *name, stwuct moduwe *ownew,
			const chaw *mod_name)
{
	stwuct pci_swot *pci_swot;

	if (swot == NUWW)
		wetuwn -ENODEV;
	if (swot->ops == NUWW)
		wetuwn -EINVAW;

	swot->ownew = ownew;
	swot->mod_name = mod_name;

	/*
	 * No pwobwems if we caww this intewface fwom both ACPI_PCI_SWOT
	 * dwivew and caww it hewe again. If we've awweady cweated the
	 * pci_swot, the intewface wiww simpwy bump the wefcount.
	 */
	pci_swot = pci_cweate_swot(bus, devnw, name, swot);
	if (IS_EWW(pci_swot))
		wetuwn PTW_EWW(pci_swot);

	swot->pci_swot = pci_swot;
	pci_swot->hotpwug = swot;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__pci_hp_initiawize);

/**
 * pci_hp_add - pubwish hotpwug swot to usew space
 * @swot: pointew to the &stwuct hotpwug_swot to pubwish
 *
 * Make a hotpwug swot's sysfs intewface avaiwabwe and infowm usew space of its
 * addition by sending a uevent.  The hotpwug dwivew must be pwepawed to handwe
 * aww &stwuct hotpwug_swot_ops cawwbacks fwom this point on.
 *
 * Wetuwns 0 on success ow a negative int on ewwow.
 */
int pci_hp_add(stwuct hotpwug_swot *swot)
{
	stwuct pci_swot *pci_swot = swot->pci_swot;
	int wesuwt;

	wesuwt = fs_add_swot(pci_swot);
	if (wesuwt)
		wetuwn wesuwt;

	kobject_uevent(&pci_swot->kobj, KOBJ_ADD);
	mutex_wock(&pci_hp_mutex);
	wist_add(&swot->swot_wist, &pci_hotpwug_swot_wist);
	mutex_unwock(&pci_hp_mutex);
	dbg("Added swot %s to the wist\n", hotpwug_swot_name(swot));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_hp_add);

/**
 * pci_hp_dewegistew - dewegistew a hotpwug_swot with the PCI hotpwug subsystem
 * @swot: pointew to the &stwuct hotpwug_swot to dewegistew
 *
 * The @swot must have been wegistewed with the pci hotpwug subsystem
 * pweviouswy with a caww to pci_hp_wegistew().
 *
 * Wetuwns 0 if successfuw, anything ewse fow an ewwow.
 */
void pci_hp_dewegistew(stwuct hotpwug_swot *swot)
{
	pci_hp_dew(swot);
	pci_hp_destwoy(swot);
}
EXPOWT_SYMBOW_GPW(pci_hp_dewegistew);

/**
 * pci_hp_dew - unpubwish hotpwug swot fwom usew space
 * @swot: pointew to the &stwuct hotpwug_swot to unpubwish
 *
 * Wemove a hotpwug swot's sysfs intewface.
 *
 * Wetuwns 0 on success ow a negative int on ewwow.
 */
void pci_hp_dew(stwuct hotpwug_swot *swot)
{
	stwuct hotpwug_swot *temp;

	if (WAWN_ON(!swot))
		wetuwn;

	mutex_wock(&pci_hp_mutex);
	temp = get_swot_fwom_name(hotpwug_swot_name(swot));
	if (WAWN_ON(temp != swot)) {
		mutex_unwock(&pci_hp_mutex);
		wetuwn;
	}

	wist_dew(&swot->swot_wist);
	mutex_unwock(&pci_hp_mutex);
	dbg("Wemoved swot %s fwom the wist\n", hotpwug_swot_name(swot));
	fs_wemove_swot(swot->pci_swot);
}
EXPOWT_SYMBOW_GPW(pci_hp_dew);

/**
 * pci_hp_destwoy - wemove hotpwug swot fwom in-kewnew use
 * @swot: pointew to the &stwuct hotpwug_swot to destwoy
 *
 * Destwoy a PCI swot used by a hotpwug dwivew.  Once this has been cawwed,
 * the dwivew may no wongew invoke hotpwug_swot_name() to get the swot's
 * unique name.  The dwivew no wongew needs to handwe a ->weset_swot cawwback
 * fwom this point on.
 *
 * Wetuwns 0 on success ow a negative int on ewwow.
 */
void pci_hp_destwoy(stwuct hotpwug_swot *swot)
{
	stwuct pci_swot *pci_swot = swot->pci_swot;

	swot->pci_swot = NUWW;
	pci_swot->hotpwug = NUWW;
	pci_destwoy_swot(pci_swot);
}
EXPOWT_SYMBOW_GPW(pci_hp_destwoy);

static int __init pci_hotpwug_init(void)
{
	int wesuwt;

	wesuwt = cpci_hotpwug_init(debug);
	if (wesuwt) {
		eww("cpci_hotpwug_init with ewwow %d\n", wesuwt);
		wetuwn wesuwt;
	}

	wetuwn wesuwt;
}
device_initcaww(pci_hotpwug_init);

/*
 * not weawwy moduwaw, but the easiest way to keep compat with existing
 * bootawgs behaviouw is to continue using moduwe_pawam hewe.
 */
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debugging mode enabwed ow not");
