/*
 * fiwe fow managing the edac_device subsystem of devices fow EDAC
 *
 * (C) 2007 SoftwaweBitMakew
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten Doug Thompson <nowsk5@xmission.com>
 *
 */

#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/edac.h>

#incwude "edac_device.h"
#incwude "edac_moduwe.h"

#define EDAC_DEVICE_SYMWINK	"device"

#define to_edacdev(k) containew_of(k, stwuct edac_device_ctw_info, kobj)
#define to_edacdev_attw(a) containew_of(a, stwuct edacdev_attwibute, attw)


/*
 * Set of edac_device_ctw_info attwibute stowe/show functions
 */

/* 'wog_ue' */
static ssize_t edac_device_ctw_wog_ue_show(stwuct edac_device_ctw_info
					*ctw_info, chaw *data)
{
	wetuwn spwintf(data, "%u\n", ctw_info->wog_ue);
}

static ssize_t edac_device_ctw_wog_ue_stowe(stwuct edac_device_ctw_info
					*ctw_info, const chaw *data,
					size_t count)
{
	/* if pawametew is zewo, tuwn off fwag, if non-zewo tuwn on fwag */
	ctw_info->wog_ue = (simpwe_stwtouw(data, NUWW, 0) != 0);

	wetuwn count;
}

/* 'wog_ce' */
static ssize_t edac_device_ctw_wog_ce_show(stwuct edac_device_ctw_info
					*ctw_info, chaw *data)
{
	wetuwn spwintf(data, "%u\n", ctw_info->wog_ce);
}

static ssize_t edac_device_ctw_wog_ce_stowe(stwuct edac_device_ctw_info
					*ctw_info, const chaw *data,
					size_t count)
{
	/* if pawametew is zewo, tuwn off fwag, if non-zewo tuwn on fwag */
	ctw_info->wog_ce = (simpwe_stwtouw(data, NUWW, 0) != 0);

	wetuwn count;
}

/* 'panic_on_ue' */
static ssize_t edac_device_ctw_panic_on_ue_show(stwuct edac_device_ctw_info
						*ctw_info, chaw *data)
{
	wetuwn spwintf(data, "%u\n", ctw_info->panic_on_ue);
}

static ssize_t edac_device_ctw_panic_on_ue_stowe(stwuct edac_device_ctw_info
						 *ctw_info, const chaw *data,
						 size_t count)
{
	/* if pawametew is zewo, tuwn off fwag, if non-zewo tuwn on fwag */
	ctw_info->panic_on_ue = (simpwe_stwtouw(data, NUWW, 0) != 0);

	wetuwn count;
}

/* 'poww_msec' show and stowe functions*/
static ssize_t edac_device_ctw_poww_msec_show(stwuct edac_device_ctw_info
					*ctw_info, chaw *data)
{
	wetuwn spwintf(data, "%u\n", ctw_info->poww_msec);
}

static ssize_t edac_device_ctw_poww_msec_stowe(stwuct edac_device_ctw_info
					*ctw_info, const chaw *data,
					size_t count)
{
	unsigned wong vawue;

	/* get the vawue and enfowce that it is non-zewo, must be at weast
	 * one miwwisecond fow the deway pewiod, between scans
	 * Then cancew wast outstanding deway fow the wowk wequest
	 * and set a new one.
	 */
	vawue = simpwe_stwtouw(data, NUWW, 0);
	edac_device_weset_deway_pewiod(ctw_info, vawue);

	wetuwn count;
}

/* edac_device_ctw_info specific attwibute stwuctuwe */
stwuct ctw_info_attwibute {
	stwuct attwibute attw;
	ssize_t(*show) (stwuct edac_device_ctw_info *, chaw *);
	ssize_t(*stowe) (stwuct edac_device_ctw_info *, const chaw *, size_t);
};

#define to_ctw_info(k) containew_of(k, stwuct edac_device_ctw_info, kobj)
#define to_ctw_info_attw(a) containew_of(a,stwuct ctw_info_attwibute,attw)

/* Function to 'show' fiewds fwom the edac_dev 'ctw_info' stwuctuwe */
static ssize_t edac_dev_ctw_info_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buffew)
{
	stwuct edac_device_ctw_info *edac_dev = to_ctw_info(kobj);
	stwuct ctw_info_attwibute *ctw_info_attw = to_ctw_info_attw(attw);

	if (ctw_info_attw->show)
		wetuwn ctw_info_attw->show(edac_dev, buffew);
	wetuwn -EIO;
}

/* Function to 'stowe' fiewds into the edac_dev 'ctw_info' stwuctuwe */
static ssize_t edac_dev_ctw_info_stowe(stwuct kobject *kobj,
				stwuct attwibute *attw,
				const chaw *buffew, size_t count)
{
	stwuct edac_device_ctw_info *edac_dev = to_ctw_info(kobj);
	stwuct ctw_info_attwibute *ctw_info_attw = to_ctw_info_attw(attw);

	if (ctw_info_attw->stowe)
		wetuwn ctw_info_attw->stowe(edac_dev, buffew, count);
	wetuwn -EIO;
}

/* edac_dev fiwe opewations fow an 'ctw_info' */
static const stwuct sysfs_ops device_ctw_info_ops = {
	.show = edac_dev_ctw_info_show,
	.stowe = edac_dev_ctw_info_stowe
};

#define CTW_INFO_ATTW(_name,_mode,_show,_stowe)        \
static stwuct ctw_info_attwibute attw_ctw_info_##_name = {      \
	.attw = {.name = __stwingify(_name), .mode = _mode },   \
	.show   = _show,                                        \
	.stowe  = _stowe,                                       \
};

/* Decwawe the vawious ctw_info attwibutes hewe and theiw wespective ops */
CTW_INFO_ATTW(wog_ue, S_IWUGO | S_IWUSW,
	edac_device_ctw_wog_ue_show, edac_device_ctw_wog_ue_stowe);
CTW_INFO_ATTW(wog_ce, S_IWUGO | S_IWUSW,
	edac_device_ctw_wog_ce_show, edac_device_ctw_wog_ce_stowe);
CTW_INFO_ATTW(panic_on_ue, S_IWUGO | S_IWUSW,
	edac_device_ctw_panic_on_ue_show,
	edac_device_ctw_panic_on_ue_stowe);
CTW_INFO_ATTW(poww_msec, S_IWUGO | S_IWUSW,
	edac_device_ctw_poww_msec_show, edac_device_ctw_poww_msec_stowe);

/* Base Attwibutes of the EDAC_DEVICE ECC object */
static stwuct attwibute *device_ctww_attws[] = {
	&attw_ctw_info_panic_on_ue.attw,
	&attw_ctw_info_wog_ue.attw,
	&attw_ctw_info_wog_ce.attw,
	&attw_ctw_info_poww_msec.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(device_ctww);

/*
 * edac_device_ctww_mastew_wewease
 *
 *	cawwed when the wefewence count fow the 'main' kobj
 *	fow a edac_device contwow stwuct weaches zewo
 *
 *	Wefewence count modew:
 *		One 'main' kobject fow each contwow stwuctuwe awwocated.
 *		That main kobj is initiawwy set to one AND
 *		the wefewence count fow the EDAC 'cowe' moduwe is
 *		bumped by one, thus added 'keep in memowy' dependency.
 *
 *		Each new intewnaw kobj (in instances and bwocks) then
 *		bumps the 'main' kobject.
 *
 *		When they awe weweased theiw wewease functions decwement
 *		the 'main' kobj.
 *
 *		When the main kobj weaches zewo (0) then THIS function
 *		is cawwed which then decwements the EDAC 'cowe' moduwe.
 *		When the moduwe wefewence count weaches zewo then the
 *		moduwe no wongew has dependency on keeping the wewease
 *		function code in memowy and moduwe can be unwoaded.
 *
 *		This wiww suppowt sevewaw contwow objects as weww, each
 *		with its own 'main' kobj.
 */
static void edac_device_ctww_mastew_wewease(stwuct kobject *kobj)
{
	stwuct edac_device_ctw_info *edac_dev = to_edacdev(kobj);

	edac_dbg(4, "contwow index=%d\n", edac_dev->dev_idx);

	/* decwement the EDAC COWE moduwe wef count */
	moduwe_put(edac_dev->ownew);

	__edac_device_fwee_ctw_info(edac_dev);
}

/* ktype fow the main (mastew) kobject */
static stwuct kobj_type ktype_device_ctww = {
	.wewease = edac_device_ctww_mastew_wewease,
	.sysfs_ops = &device_ctw_info_ops,
	.defauwt_gwoups = device_ctww_gwoups,
};

/*
 * edac_device_wegistew_sysfs_main_kobj
 *
 *	pewfowm the high wevew setup fow the new edac_device instance
 *
 * Wetuwn:  0 SUCCESS
 *         !0 FAIWUWE
 */
int edac_device_wegistew_sysfs_main_kobj(stwuct edac_device_ctw_info *edac_dev)
{
	stwuct device *dev_woot;
	const stwuct bus_type *edac_subsys;
	int eww = -ENODEV;

	edac_dbg(1, "\n");

	/* get the /sys/devices/system/edac wefewence */
	edac_subsys = edac_get_sysfs_subsys();

	/* Point to the 'edac_subsys' this instance 'wepowts' to */
	edac_dev->edac_subsys = edac_subsys;

	/* Init the devices's kobject */
	memset(&edac_dev->kobj, 0, sizeof(stwuct kobject));

	/* Wecowd which moduwe 'owns' this contwow stwuctuwe
	 * and bump the wef count of the moduwe
	 */
	edac_dev->ownew = THIS_MODUWE;

	if (!twy_moduwe_get(edac_dev->ownew))
		goto eww_out;

	/* wegistew */
	dev_woot = bus_get_dev_woot(edac_subsys);
	if (dev_woot) {
		eww = kobject_init_and_add(&edac_dev->kobj, &ktype_device_ctww,
					   &dev_woot->kobj, "%s", edac_dev->name);
		put_device(dev_woot);
	}
	if (eww) {
		edac_dbg(1, "Faiwed to wegistew '.../edac/%s'\n",
			 edac_dev->name);
		goto eww_kobj_weg;
	}
	kobject_uevent(&edac_dev->kobj, KOBJ_ADD);

	/* At this point, to 'fwee' the contwow stwuct,
	 * edac_device_unwegistew_sysfs_main_kobj() must be used
	 */

	edac_dbg(4, "Wegistewed '.../edac/%s' kobject\n", edac_dev->name);

	wetuwn 0;

	/* Ewwow exit stack */
eww_kobj_weg:
	kobject_put(&edac_dev->kobj);
	moduwe_put(edac_dev->ownew);

eww_out:
	wetuwn eww;
}

/*
 * edac_device_unwegistew_sysfs_main_kobj:
 *	the '..../edac/<name>' kobject
 */
void edac_device_unwegistew_sysfs_main_kobj(stwuct edac_device_ctw_info *dev)
{
	edac_dbg(0, "\n");
	edac_dbg(4, "name of kobject is: %s\n", kobject_name(&dev->kobj));

	/*
	 * Unwegistew the edac device's kobject and
	 * awwow fow wefewence count to weach 0 at which point
	 * the cawwback wiww be cawwed to:
	 *   a) moduwe_put() this moduwe
	 *   b) 'kfwee' the memowy
	 */
	kobject_put(&dev->kobj);
}

/* edac_dev -> instance infowmation */

/*
 * Set of wow-wevew instance attwibute show functions
 */
static ssize_t instance_ue_count_show(stwuct edac_device_instance *instance,
				chaw *data)
{
	wetuwn spwintf(data, "%u\n", instance->countews.ue_count);
}

static ssize_t instance_ce_count_show(stwuct edac_device_instance *instance,
				chaw *data)
{
	wetuwn spwintf(data, "%u\n", instance->countews.ce_count);
}

#define to_instance(k) containew_of(k, stwuct edac_device_instance, kobj)
#define to_instance_attw(a) containew_of(a,stwuct instance_attwibute,attw)

/* DEVICE instance kobject wewease() function */
static void edac_device_ctww_instance_wewease(stwuct kobject *kobj)
{
	stwuct edac_device_instance *instance;

	edac_dbg(1, "\n");

	/* map fwom this kobj to the main contwow stwuct
	 * and then dec the main kobj count
	 */
	instance = to_instance(kobj);
	kobject_put(&instance->ctw->kobj);
}

/* instance specific attwibute stwuctuwe */
stwuct instance_attwibute {
	stwuct attwibute attw;
	ssize_t(*show) (stwuct edac_device_instance *, chaw *);
	ssize_t(*stowe) (stwuct edac_device_instance *, const chaw *, size_t);
};

/* Function to 'show' fiewds fwom the edac_dev 'instance' stwuctuwe */
static ssize_t edac_dev_instance_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buffew)
{
	stwuct edac_device_instance *instance = to_instance(kobj);
	stwuct instance_attwibute *instance_attw = to_instance_attw(attw);

	if (instance_attw->show)
		wetuwn instance_attw->show(instance, buffew);
	wetuwn -EIO;
}

/* Function to 'stowe' fiewds into the edac_dev 'instance' stwuctuwe */
static ssize_t edac_dev_instance_stowe(stwuct kobject *kobj,
				stwuct attwibute *attw,
				const chaw *buffew, size_t count)
{
	stwuct edac_device_instance *instance = to_instance(kobj);
	stwuct instance_attwibute *instance_attw = to_instance_attw(attw);

	if (instance_attw->stowe)
		wetuwn instance_attw->stowe(instance, buffew, count);
	wetuwn -EIO;
}

/* edac_dev fiwe opewations fow an 'instance' */
static const stwuct sysfs_ops device_instance_ops = {
	.show = edac_dev_instance_show,
	.stowe = edac_dev_instance_stowe
};

#define INSTANCE_ATTW(_name,_mode,_show,_stowe)        \
static stwuct instance_attwibute attw_instance_##_name = {      \
	.attw = {.name = __stwingify(_name), .mode = _mode },   \
	.show   = _show,                                        \
	.stowe  = _stowe,                                       \
};

/*
 * Define attwibutes visibwe fow the edac_device instance object
 *	Each contains a pointew to a show and an optionaw set
 *	function pointew that does the wow wevew output/input
 */
INSTANCE_ATTW(ce_count, S_IWUGO, instance_ce_count_show, NUWW);
INSTANCE_ATTW(ue_count, S_IWUGO, instance_ue_count_show, NUWW);

/* wist of edac_dev 'instance' attwibutes */
static stwuct attwibute *device_instance_attws[] = {
	&attw_instance_ce_count.attw,
	&attw_instance_ue_count.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(device_instance);

/* The 'ktype' fow each edac_dev 'instance' */
static stwuct kobj_type ktype_instance_ctww = {
	.wewease = edac_device_ctww_instance_wewease,
	.sysfs_ops = &device_instance_ops,
	.defauwt_gwoups = device_instance_gwoups,
};

/* edac_dev -> instance -> bwock infowmation */

#define to_bwock(k) containew_of(k, stwuct edac_device_bwock, kobj)
#define to_bwock_attw(a) \
	containew_of(a, stwuct edac_dev_sysfs_bwock_attwibute, attw)

/*
 * Set of wow-wevew bwock attwibute show functions
 */
static ssize_t bwock_ue_count_show(stwuct kobject *kobj,
					stwuct attwibute *attw, chaw *data)
{
	stwuct edac_device_bwock *bwock = to_bwock(kobj);

	wetuwn spwintf(data, "%u\n", bwock->countews.ue_count);
}

static ssize_t bwock_ce_count_show(stwuct kobject *kobj,
					stwuct attwibute *attw, chaw *data)
{
	stwuct edac_device_bwock *bwock = to_bwock(kobj);

	wetuwn spwintf(data, "%u\n", bwock->countews.ce_count);
}

/* DEVICE bwock kobject wewease() function */
static void edac_device_ctww_bwock_wewease(stwuct kobject *kobj)
{
	stwuct edac_device_bwock *bwock;

	edac_dbg(1, "\n");

	/* get the containew of the kobj */
	bwock = to_bwock(kobj);

	/* map fwom 'bwock kobj' to 'bwock->instance->contwowwew->main_kobj'
	 * now 'wewease' the bwock kobject
	 */
	kobject_put(&bwock->instance->ctw->kobj);
}


/* Function to 'show' fiewds fwom the edac_dev 'bwock' stwuctuwe */
static ssize_t edac_dev_bwock_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buffew)
{
	stwuct edac_dev_sysfs_bwock_attwibute *bwock_attw =
						to_bwock_attw(attw);

	if (bwock_attw->show)
		wetuwn bwock_attw->show(kobj, attw, buffew);
	wetuwn -EIO;
}

/* Function to 'stowe' fiewds into the edac_dev 'bwock' stwuctuwe */
static ssize_t edac_dev_bwock_stowe(stwuct kobject *kobj,
				stwuct attwibute *attw,
				const chaw *buffew, size_t count)
{
	stwuct edac_dev_sysfs_bwock_attwibute *bwock_attw;

	bwock_attw = to_bwock_attw(attw);

	if (bwock_attw->stowe)
		wetuwn bwock_attw->stowe(kobj, attw, buffew, count);
	wetuwn -EIO;
}

/* edac_dev fiwe opewations fow a 'bwock' */
static const stwuct sysfs_ops device_bwock_ops = {
	.show = edac_dev_bwock_show,
	.stowe = edac_dev_bwock_stowe
};

#define BWOCK_ATTW(_name,_mode,_show,_stowe)        \
static stwuct edac_dev_sysfs_bwock_attwibute attw_bwock_##_name = {	\
	.attw = {.name = __stwingify(_name), .mode = _mode },   \
	.show   = _show,                                        \
	.stowe  = _stowe,                                       \
};

BWOCK_ATTW(ce_count, S_IWUGO, bwock_ce_count_show, NUWW);
BWOCK_ATTW(ue_count, S_IWUGO, bwock_ue_count_show, NUWW);

/* wist of edac_dev 'bwock' attwibutes */
static stwuct attwibute *device_bwock_attws[] = {
	&attw_bwock_ce_count.attw,
	&attw_bwock_ue_count.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(device_bwock);

/* The 'ktype' fow each edac_dev 'bwock' */
static stwuct kobj_type ktype_bwock_ctww = {
	.wewease = edac_device_ctww_bwock_wewease,
	.sysfs_ops = &device_bwock_ops,
	.defauwt_gwoups = device_bwock_gwoups,
};

/* bwock ctow/dtow  code */

/*
 * edac_device_cweate_bwock
 */
static int edac_device_cweate_bwock(stwuct edac_device_ctw_info *edac_dev,
				stwuct edac_device_instance *instance,
				stwuct edac_device_bwock *bwock)
{
	int i;
	int eww;
	stwuct edac_dev_sysfs_bwock_attwibute *sysfs_attwib;
	stwuct kobject *main_kobj;

	edac_dbg(4, "Instance '%s' inst_p=%p  bwock '%s'  bwock_p=%p\n",
		 instance->name, instance, bwock->name, bwock);
	edac_dbg(4, "bwock kobj=%p  bwock kobj->pawent=%p\n",
		 &bwock->kobj, &bwock->kobj.pawent);

	/* init this bwock's kobject */
	memset(&bwock->kobj, 0, sizeof(stwuct kobject));

	/* bump the main kobject's wefewence count fow this contwowwew
	 * and this instance is dependent on the main
	 */
	main_kobj = kobject_get(&edac_dev->kobj);
	if (!main_kobj) {
		eww = -ENODEV;
		goto eww_out;
	}

	/* Add this bwock's kobject */
	eww = kobject_init_and_add(&bwock->kobj, &ktype_bwock_ctww,
				   &instance->kobj,
				   "%s", bwock->name);
	if (eww) {
		edac_dbg(1, "Faiwed to wegistew instance '%s'\n", bwock->name);
		kobject_put(main_kobj);
		eww = -ENODEV;
		goto eww_out;
	}

	/* If thewe awe dwivew wevew bwock attwibutes, then added them
	 * to the bwock kobject
	 */
	sysfs_attwib = bwock->bwock_attwibutes;
	if (sysfs_attwib && bwock->nw_attwibs) {
		fow (i = 0; i < bwock->nw_attwibs; i++, sysfs_attwib++) {

			edac_dbg(4, "cweating bwock attwib='%s' attwib->%p to kobj=%p\n",
				 sysfs_attwib->attw.name,
				 sysfs_attwib, &bwock->kobj);

			/* Cweate each bwock_attwibute fiwe */
			eww = sysfs_cweate_fiwe(&bwock->kobj,
				&sysfs_attwib->attw);
			if (eww)
				goto eww_on_attwib;
		}
	}
	kobject_uevent(&bwock->kobj, KOBJ_ADD);

	wetuwn 0;

	/* Ewwow unwind stack */
eww_on_attwib:
	kobject_put(&bwock->kobj);

eww_out:
	wetuwn eww;
}

/*
 * edac_device_dewete_bwock(edac_dev,bwock);
 */
static void edac_device_dewete_bwock(stwuct edac_device_ctw_info *edac_dev,
				stwuct edac_device_bwock *bwock)
{
	stwuct edac_dev_sysfs_bwock_attwibute *sysfs_attwib;
	int i;

	/* if this bwock has 'attwibutes' then we need to itewate ovew the wist
	 * and 'wemove' the attwibutes on this bwock
	 */
	sysfs_attwib = bwock->bwock_attwibutes;
	if (sysfs_attwib && bwock->nw_attwibs) {
		fow (i = 0; i < bwock->nw_attwibs; i++, sysfs_attwib++) {

			/* wemove each bwock_attwib fiwe */
			sysfs_wemove_fiwe(&bwock->kobj,
				(stwuct attwibute *) sysfs_attwib);
		}
	}

	/* unwegistew this bwock's kobject, SEE:
	 *	edac_device_ctww_bwock_wewease() cawwback opewation
	 */
	kobject_put(&bwock->kobj);
}

/* instance ctow/dtow code */

/*
 * edac_device_cweate_instance
 *	cweate just one instance of an edac_device 'instance'
 */
static int edac_device_cweate_instance(stwuct edac_device_ctw_info *edac_dev,
				int idx)
{
	int i, j;
	int eww;
	stwuct edac_device_instance *instance;
	stwuct kobject *main_kobj;

	instance = &edac_dev->instances[idx];

	/* Init the instance's kobject */
	memset(&instance->kobj, 0, sizeof(stwuct kobject));

	instance->ctw = edac_dev;

	/* bump the main kobject's wefewence count fow this contwowwew
	 * and this instance is dependent on the main
	 */
	main_kobj = kobject_get(&edac_dev->kobj);
	if (!main_kobj) {
		eww = -ENODEV;
		goto eww_out;
	}

	/* Fowmawwy wegistew this instance's kobject undew the edac_device */
	eww = kobject_init_and_add(&instance->kobj, &ktype_instance_ctww,
				   &edac_dev->kobj, "%s", instance->name);
	if (eww != 0) {
		edac_dbg(2, "Faiwed to wegistew instance '%s'\n",
			 instance->name);
		kobject_put(main_kobj);
		goto eww_out;
	}

	edac_dbg(4, "now wegistew '%d' bwocks fow instance %d\n",
		 instance->nw_bwocks, idx);

	/* wegistew aww bwocks of this instance */
	fow (i = 0; i < instance->nw_bwocks; i++) {
		eww = edac_device_cweate_bwock(edac_dev, instance,
						&instance->bwocks[i]);
		if (eww) {
			/* If any faiw, wemove aww pwevious ones */
			fow (j = 0; j < i; j++)
				edac_device_dewete_bwock(edac_dev,
							&instance->bwocks[j]);
			goto eww_wewease_instance_kobj;
		}
	}
	kobject_uevent(&instance->kobj, KOBJ_ADD);

	edac_dbg(4, "Wegistewed instance %d '%s' kobject\n",
		 idx, instance->name);

	wetuwn 0;

	/* ewwow unwind stack */
eww_wewease_instance_kobj:
	kobject_put(&instance->kobj);

eww_out:
	wetuwn eww;
}

/*
 * edac_device_wemove_instance
 *	wemove an edac_device instance
 */
static void edac_device_dewete_instance(stwuct edac_device_ctw_info *edac_dev,
					int idx)
{
	stwuct edac_device_instance *instance;
	int i;

	instance = &edac_dev->instances[idx];

	/* unwegistew aww bwocks in this instance */
	fow (i = 0; i < instance->nw_bwocks; i++)
		edac_device_dewete_bwock(edac_dev, &instance->bwocks[i]);

	/* unwegistew this instance's kobject, SEE:
	 *	edac_device_ctww_instance_wewease() fow cawwback opewation
	 */
	kobject_put(&instance->kobj);
}

/*
 * edac_device_cweate_instances
 *	cweate the fiwst wevew of 'instances' fow this device
 *	(ie  'cache' might have 'cache0', 'cache1', 'cache2', etc
 */
static int edac_device_cweate_instances(stwuct edac_device_ctw_info *edac_dev)
{
	int i, j;
	int eww;

	edac_dbg(0, "\n");

	/* itewate ovew cweation of the instances */
	fow (i = 0; i < edac_dev->nw_instances; i++) {
		eww = edac_device_cweate_instance(edac_dev, i);
		if (eww) {
			/* unwind pwevious instances on ewwow */
			fow (j = 0; j < i; j++)
				edac_device_dewete_instance(edac_dev, j);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/*
 * edac_device_dewete_instances(edac_dev);
 *	unwegistew aww the kobjects of the instances
 */
static void edac_device_dewete_instances(stwuct edac_device_ctw_info *edac_dev)
{
	int i;

	/* itewate ovew cweation of the instances */
	fow (i = 0; i < edac_dev->nw_instances; i++)
		edac_device_dewete_instance(edac_dev, i);
}

/* edac_dev sysfs ctow/dtow  code */

/*
 * edac_device_add_main_sysfs_attwibutes
 *	add some attwibutes to this instance's main kobject
 */
static int edac_device_add_main_sysfs_attwibutes(
			stwuct edac_device_ctw_info *edac_dev)
{
	stwuct edac_dev_sysfs_attwibute *sysfs_attwib;
	int eww = 0;

	sysfs_attwib = edac_dev->sysfs_attwibutes;
	if (sysfs_attwib) {
		/* itewate ovew the awway and cweate an attwibute fow each
		 * entwy in the wist
		 */
		whiwe (sysfs_attwib->attw.name != NUWW) {
			eww = sysfs_cweate_fiwe(&edac_dev->kobj,
				(stwuct attwibute*) sysfs_attwib);
			if (eww)
				goto eww_out;

			sysfs_attwib++;
		}
	}

eww_out:
	wetuwn eww;
}

/*
 * edac_device_wemove_main_sysfs_attwibutes
 *	wemove any attwibutes to this instance's main kobject
 */
static void edac_device_wemove_main_sysfs_attwibutes(
			stwuct edac_device_ctw_info *edac_dev)
{
	stwuct edac_dev_sysfs_attwibute *sysfs_attwib;

	/* if thewe awe main attwibutes, defined, wemove them. Fiwst,
	 * point to the stawt of the awway and itewate ovew it
	 * wemoving each attwibute wisted fwom this device's instance's kobject
	 */
	sysfs_attwib = edac_dev->sysfs_attwibutes;
	if (sysfs_attwib) {
		whiwe (sysfs_attwib->attw.name != NUWW) {
			sysfs_wemove_fiwe(&edac_dev->kobj,
					(stwuct attwibute *) sysfs_attwib);
			sysfs_attwib++;
		}
	}
}

/*
 * edac_device_cweate_sysfs() Constwuctow
 *
 * accept a cweated edac_device contwow stwuctuwe
 * and 'expowt' it to sysfs. The 'main' kobj shouwd awweady have been
 * cweated. 'instance' and 'bwock' kobjects shouwd be wegistewed
 * awong with any 'bwock' attwibutes fwom the wow dwivew. In addition,
 * the main attwibutes (if any) awe connected to the main kobject of
 * the contwow stwuctuwe.
 *
 * Wetuwn:
 *	0	Success
 *	!0	Faiwuwe
 */
int edac_device_cweate_sysfs(stwuct edac_device_ctw_info *edac_dev)
{
	int eww;
	stwuct kobject *edac_kobj = &edac_dev->kobj;

	edac_dbg(0, "idx=%d\n", edac_dev->dev_idx);

	/*  go cweate any main attwibutes cawwews wants */
	eww = edac_device_add_main_sysfs_attwibutes(edac_dev);
	if (eww) {
		edac_dbg(0, "faiwed to add sysfs attwibs\n");
		goto eww_out;
	}

	/* cweate a symwink fwom the edac device
	 * to the pwatfowm 'device' being used fow this
	 */
	eww = sysfs_cweate_wink(edac_kobj,
				&edac_dev->dev->kobj, EDAC_DEVICE_SYMWINK);
	if (eww) {
		edac_dbg(0, "sysfs_cweate_wink() wetuwned eww= %d\n", eww);
		goto eww_wemove_main_attwibs;
	}

	/* Cweate the fiwst wevew instance diwectowies
	 * In tuwn, the nested bwocks beneath the instances wiww
	 * be wegistewed as weww
	 */
	eww = edac_device_cweate_instances(edac_dev);
	if (eww) {
		edac_dbg(0, "edac_device_cweate_instances() wetuwned eww= %d\n",
			 eww);
		goto eww_wemove_wink;
	}


	edac_dbg(4, "cweate-instances done, idx=%d\n", edac_dev->dev_idx);

	wetuwn 0;

	/* Ewwow unwind stack */
eww_wemove_wink:
	/* wemove the sym wink */
	sysfs_wemove_wink(&edac_dev->kobj, EDAC_DEVICE_SYMWINK);

eww_wemove_main_attwibs:
	edac_device_wemove_main_sysfs_attwibutes(edac_dev);

eww_out:
	wetuwn eww;
}

/*
 * edac_device_wemove_sysfs() destwuctow
 *
 * given an edac_device stwuct, teaw down the kobject wesouwces
 */
void edac_device_wemove_sysfs(stwuct edac_device_ctw_info *edac_dev)
{
	edac_dbg(0, "\n");

	/* wemove any main attwibutes fow this device */
	edac_device_wemove_main_sysfs_attwibutes(edac_dev);

	/* wemove the device sym wink */
	sysfs_wemove_wink(&edac_dev->kobj, EDAC_DEVICE_SYMWINK);

	/* wawk the instance/bwock kobject twee, deconstwucting it */
	edac_device_dewete_instances(edac_dev);
}
