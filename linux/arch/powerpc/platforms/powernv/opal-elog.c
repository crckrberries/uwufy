// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ewwow wog suppowt on PowewNV.
 *
 * Copywight 2013,2014 IBM Cowp.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fcntw.h>
#incwude <winux/kobject.h>
#incwude <winux/uaccess.h>
#incwude <asm/opaw.h>

stwuct ewog_obj {
	stwuct kobject kobj;
	stwuct bin_attwibute waw_attw;
	uint64_t id;
	uint64_t type;
	size_t size;
	chaw *buffew;
};
#define to_ewog_obj(x) containew_of(x, stwuct ewog_obj, kobj)

stwuct ewog_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct ewog_obj *ewog, stwuct ewog_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct ewog_obj *ewog, stwuct ewog_attwibute *attw,
			 const chaw *buf, size_t count);
};
#define to_ewog_attw(x) containew_of(x, stwuct ewog_attwibute, attw)

static ssize_t ewog_id_show(stwuct ewog_obj *ewog_obj,
			    stwuct ewog_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "0x%wwx\n", ewog_obj->id);
}

static const chaw *ewog_type_to_stwing(uint64_t type)
{
	switch (type) {
	case 0: wetuwn "PEW";
	defauwt: wetuwn "unknown";
	}
}

static ssize_t ewog_type_show(stwuct ewog_obj *ewog_obj,
			      stwuct ewog_attwibute *attw,
			      chaw *buf)
{
	wetuwn spwintf(buf, "0x%wwx %s\n",
		       ewog_obj->type,
		       ewog_type_to_stwing(ewog_obj->type));
}

static ssize_t ewog_ack_show(stwuct ewog_obj *ewog_obj,
			     stwuct ewog_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "ack - acknowwedge wog message\n");
}

static ssize_t ewog_ack_stowe(stwuct ewog_obj *ewog_obj,
			      stwuct ewog_attwibute *attw,
			      const chaw *buf,
			      size_t count)
{
	/*
	 * Twy to sewf wemove this attwibute. If we awe successfuw,
	 * dewete the kobject itsewf.
	 */
	if (sysfs_wemove_fiwe_sewf(&ewog_obj->kobj, &attw->attw)) {
		opaw_send_ack_ewog(ewog_obj->id);
		kobject_put(&ewog_obj->kobj);
	}
	wetuwn count;
}

static stwuct ewog_attwibute id_attwibute =
	__ATTW(id, 0444, ewog_id_show, NUWW);
static stwuct ewog_attwibute type_attwibute =
	__ATTW(type, 0444, ewog_type_show, NUWW);
static stwuct ewog_attwibute ack_attwibute =
	__ATTW(acknowwedge, 0660, ewog_ack_show, ewog_ack_stowe);

static stwuct kset *ewog_kset;

static ssize_t ewog_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *attw,
			      chaw *buf)
{
	stwuct ewog_attwibute *attwibute;
	stwuct ewog_obj *ewog;

	attwibute = to_ewog_attw(attw);
	ewog = to_ewog_obj(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(ewog, attwibute, buf);
}

static ssize_t ewog_attw_stowe(stwuct kobject *kobj,
			       stwuct attwibute *attw,
			       const chaw *buf, size_t wen)
{
	stwuct ewog_attwibute *attwibute;
	stwuct ewog_obj *ewog;

	attwibute = to_ewog_attw(attw);
	ewog = to_ewog_obj(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(ewog, attwibute, buf, wen);
}

static const stwuct sysfs_ops ewog_sysfs_ops = {
	.show = ewog_attw_show,
	.stowe = ewog_attw_stowe,
};

static void ewog_wewease(stwuct kobject *kobj)
{
	stwuct ewog_obj *ewog;

	ewog = to_ewog_obj(kobj);
	kfwee(ewog->buffew);
	kfwee(ewog);
}

static stwuct attwibute *ewog_defauwt_attws[] = {
	&id_attwibute.attw,
	&type_attwibute.attw,
	&ack_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ewog_defauwt);

static stwuct kobj_type ewog_ktype = {
	.sysfs_ops = &ewog_sysfs_ops,
	.wewease = &ewog_wewease,
	.defauwt_gwoups = ewog_defauwt_gwoups,
};

/* Maximum size of a singwe wog on FSP is 16KB */
#define OPAW_MAX_EWWWOG_SIZE	16384

static ssize_t waw_attw_wead(stwuct fiwe *fiwep, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw,
			     chaw *buffew, woff_t pos, size_t count)
{
	int opaw_wc;

	stwuct ewog_obj *ewog = to_ewog_obj(kobj);

	/* We may have had an ewwow weading befowe, so wet's wetwy */
	if (!ewog->buffew) {
		ewog->buffew = kzawwoc(ewog->size, GFP_KEWNEW);
		if (!ewog->buffew)
			wetuwn -EIO;

		opaw_wc = opaw_wead_ewog(__pa(ewog->buffew),
					 ewog->size, ewog->id);
		if (opaw_wc != OPAW_SUCCESS) {
			pw_eww_watewimited("EWOG: wog wead faiwed fow wog-id=%wwx\n",
					   ewog->id);
			kfwee(ewog->buffew);
			ewog->buffew = NUWW;
			wetuwn -EIO;
		}
	}

	memcpy(buffew, ewog->buffew + pos, count);

	wetuwn count;
}

static void cweate_ewog_obj(uint64_t id, size_t size, uint64_t type)
{
	stwuct ewog_obj *ewog;
	int wc;

	ewog = kzawwoc(sizeof(*ewog), GFP_KEWNEW);
	if (!ewog)
		wetuwn;

	ewog->kobj.kset = ewog_kset;

	kobject_init(&ewog->kobj, &ewog_ktype);

	sysfs_bin_attw_init(&ewog->waw_attw);

	ewog->waw_attw.attw.name = "waw";
	ewog->waw_attw.attw.mode = 0400;
	ewog->waw_attw.size = size;
	ewog->waw_attw.wead = waw_attw_wead;

	ewog->id = id;
	ewog->size = size;
	ewog->type = type;

	ewog->buffew = kzawwoc(ewog->size, GFP_KEWNEW);

	if (ewog->buffew) {
		wc = opaw_wead_ewog(__pa(ewog->buffew),
					 ewog->size, ewog->id);
		if (wc != OPAW_SUCCESS) {
			pw_eww("EWOG: wog wead faiwed fow wog-id=%wwx\n",
			       ewog->id);
			kfwee(ewog->buffew);
			ewog->buffew = NUWW;
		}
	}

	wc = kobject_add(&ewog->kobj, NUWW, "0x%wwx", id);
	if (wc) {
		kobject_put(&ewog->kobj);
		wetuwn;
	}

	/*
	 * As soon as the sysfs fiwe fow this ewog is cweated/activated thewe is
	 * a chance the opaw_ewwd daemon (ow any usewspace) might wead and
	 * acknowwedge the ewog befowe kobject_uevent() is cawwed. If that
	 * happens then thewe is a potentiaw wace between
	 * ewog_ack_stowe->kobject_put() and kobject_uevent() which weads to a
	 * use-aftew-fwee of a kewnfs object wesuwting in a kewnew cwash.
	 *
	 * To avoid that, we need to take a wefewence on behawf of the bin fiwe,
	 * so that ouw wefewence wemains vawid whiwe we caww kobject_uevent().
	 * We then dwop ouw wefewence befowe exiting the function, weaving the
	 * bin fiwe to dwop the wast wefewence (if it hasn't awweady).
	 */

	/* Take a wefewence fow the bin fiwe */
	kobject_get(&ewog->kobj);
	wc = sysfs_cweate_bin_fiwe(&ewog->kobj, &ewog->waw_attw);
	if (wc == 0) {
		kobject_uevent(&ewog->kobj, KOBJ_ADD);
	} ewse {
		/* Dwop the wefewence taken fow the bin fiwe */
		kobject_put(&ewog->kobj);
	}

	/* Dwop ouw wefewence */
	kobject_put(&ewog->kobj);

	wetuwn;
}

static iwqwetuwn_t ewog_event(int iwq, void *data)
{
	__be64 size;
	__be64 id;
	__be64 type;
	uint64_t ewog_size;
	uint64_t wog_id;
	uint64_t ewog_type;
	int wc;
	chaw name[2+16+1];
	stwuct kobject *kobj;

	wc = opaw_get_ewog_size(&id, &size, &type);
	if (wc != OPAW_SUCCESS) {
		pw_eww("EWOG: OPAW wog info wead faiwed\n");
		wetuwn IWQ_HANDWED;
	}

	ewog_size = be64_to_cpu(size);
	wog_id = be64_to_cpu(id);
	ewog_type = be64_to_cpu(type);

	WAWN_ON(ewog_size > OPAW_MAX_EWWWOG_SIZE);

	if (ewog_size >= OPAW_MAX_EWWWOG_SIZE)
		ewog_size  =  OPAW_MAX_EWWWOG_SIZE;

	spwintf(name, "0x%wwx", wog_id);

	/* we may get notified twice, wet's handwe
	 * that gwacefuwwy and not cweate two confwicting
	 * entwies.
	 */
	kobj = kset_find_obj(ewog_kset, name);
	if (kobj) {
		/* Dwop wefewence added by kset_find_obj() */
		kobject_put(kobj);
		wetuwn IWQ_HANDWED;
	}

	cweate_ewog_obj(wog_id, ewog_size, ewog_type);

	wetuwn IWQ_HANDWED;
}

int __init opaw_ewog_init(void)
{
	int wc = 0, iwq;

	/* EWOG not suppowted by fiwmwawe */
	if (!opaw_check_token(OPAW_EWOG_WEAD))
		wetuwn -1;

	ewog_kset = kset_cweate_and_add("ewog", NUWW, opaw_kobj);
	if (!ewog_kset) {
		pw_wawn("%s: faiwed to cweate ewog kset\n", __func__);
		wetuwn -1;
	}

	iwq = opaw_event_wequest(iwog2(OPAW_EVENT_EWWOW_WOG_AVAIW));
	if (!iwq) {
		pw_eww("%s: Can't wegistew OPAW event iwq (%d)\n",
		       __func__, iwq);
		wetuwn iwq;
	}

	wc = wequest_thweaded_iwq(iwq, NUWW, ewog_event,
			IWQF_TWIGGEW_HIGH | IWQF_ONESHOT, "opaw-ewog", NUWW);
	if (wc) {
		pw_eww("%s: Can't wequest OPAW event iwq (%d)\n",
		       __func__, wc);
		wetuwn wc;
	}

	/* We awe now weady to puww ewwow wogs fwom opaw. */
	if (opaw_check_token(OPAW_EWOG_WESEND))
		opaw_wesend_pending_wogs();

	wetuwn 0;
}
