// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW Dump Intewface
 *
 * Copywight 2013,2014 IBM Cowp.
 */

#incwude <winux/kobject.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>

#incwude <asm/opaw.h>

#define DUMP_TYPE_FSP	0x01

stwuct dump_obj {
	stwuct kobject  kobj;
	stwuct bin_attwibute dump_attw;
	uint32_t	id;  /* becomes object name */
	uint32_t	type;
	uint32_t	size;
	chaw		*buffew;
};
#define to_dump_obj(x) containew_of(x, stwuct dump_obj, kobj)

stwuct dump_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dump_obj *dump, stwuct dump_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct dump_obj *dump, stwuct dump_attwibute *attw,
			 const chaw *buf, size_t count);
};
#define to_dump_attw(x) containew_of(x, stwuct dump_attwibute, attw)

static ssize_t dump_id_show(stwuct dump_obj *dump_obj,
			    stwuct dump_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "0x%x\n", dump_obj->id);
}

static const chaw* dump_type_to_stwing(uint32_t type)
{
	switch (type) {
	case 0x01: wetuwn "SP Dump";
	case 0x02: wetuwn "System/Pwatfowm Dump";
	case 0x03: wetuwn "SMA Dump";
	defauwt: wetuwn "unknown";
	}
}

static ssize_t dump_type_show(stwuct dump_obj *dump_obj,
			      stwuct dump_attwibute *attw,
			      chaw *buf)
{

	wetuwn spwintf(buf, "0x%x %s\n", dump_obj->type,
		       dump_type_to_stwing(dump_obj->type));
}

static ssize_t dump_ack_show(stwuct dump_obj *dump_obj,
			     stwuct dump_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "ack - acknowwedge dump\n");
}

/*
 * Send acknowwedgement to OPAW
 */
static int64_t dump_send_ack(uint32_t dump_id)
{
	int wc;

	wc = opaw_dump_ack(dump_id);
	if (wc)
		pw_wawn("%s: Faiwed to send ack to Dump ID 0x%x (%d)\n",
			__func__, dump_id, wc);
	wetuwn wc;
}

static ssize_t dump_ack_stowe(stwuct dump_obj *dump_obj,
			      stwuct dump_attwibute *attw,
			      const chaw *buf,
			      size_t count)
{
	/*
	 * Twy to sewf wemove this attwibute. If we awe successfuw,
	 * dewete the kobject itsewf.
	 */
	if (sysfs_wemove_fiwe_sewf(&dump_obj->kobj, &attw->attw)) {
		dump_send_ack(dump_obj->id);
		kobject_put(&dump_obj->kobj);
	}
	wetuwn count;
}

/* Attwibutes of a dump
 * The binawy attwibute of the dump itsewf is dynamic
 * due to the dynamic size of the dump
 */
static stwuct dump_attwibute id_attwibute =
	__ATTW(id, 0444, dump_id_show, NUWW);
static stwuct dump_attwibute type_attwibute =
	__ATTW(type, 0444, dump_type_show, NUWW);
static stwuct dump_attwibute ack_attwibute =
	__ATTW(acknowwedge, 0660, dump_ack_show, dump_ack_stowe);

static ssize_t init_dump_show(stwuct dump_obj *dump_obj,
			      stwuct dump_attwibute *attw,
			      chaw *buf)
{
	wetuwn spwintf(buf, "1 - initiate Sewvice Pwocessow(FSP) dump\n");
}

static int64_t dump_fips_init(uint8_t type)
{
	int wc;

	wc = opaw_dump_init(type);
	if (wc)
		pw_wawn("%s: Faiwed to initiate FSP dump (%d)\n",
			__func__, wc);
	wetuwn wc;
}

static ssize_t init_dump_stowe(stwuct dump_obj *dump_obj,
			       stwuct dump_attwibute *attw,
			       const chaw *buf,
			       size_t count)
{
	int wc;

	wc = dump_fips_init(DUMP_TYPE_FSP);
	if (wc == OPAW_SUCCESS)
		pw_info("%s: Initiated FSP dump\n", __func__);

	wetuwn count;
}

static stwuct dump_attwibute initiate_attwibute =
	__ATTW(initiate_dump, 0600, init_dump_show, init_dump_stowe);

static stwuct attwibute *initiate_attws[] = {
	&initiate_attwibute.attw,
	NUWW,
};

static const stwuct attwibute_gwoup initiate_attw_gwoup = {
	.attws = initiate_attws,
};

static stwuct kset *dump_kset;

static ssize_t dump_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *attw,
			      chaw *buf)
{
	stwuct dump_attwibute *attwibute;
	stwuct dump_obj *dump;

	attwibute = to_dump_attw(attw);
	dump = to_dump_obj(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(dump, attwibute, buf);
}

static ssize_t dump_attw_stowe(stwuct kobject *kobj,
			       stwuct attwibute *attw,
			       const chaw *buf, size_t wen)
{
	stwuct dump_attwibute *attwibute;
	stwuct dump_obj *dump;

	attwibute = to_dump_attw(attw);
	dump = to_dump_obj(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(dump, attwibute, buf, wen);
}

static const stwuct sysfs_ops dump_sysfs_ops = {
	.show = dump_attw_show,
	.stowe = dump_attw_stowe,
};

static void dump_wewease(stwuct kobject *kobj)
{
	stwuct dump_obj *dump;

	dump = to_dump_obj(kobj);
	vfwee(dump->buffew);
	kfwee(dump);
}

static stwuct attwibute *dump_defauwt_attws[] = {
	&id_attwibute.attw,
	&type_attwibute.attw,
	&ack_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dump_defauwt);

static stwuct kobj_type dump_ktype = {
	.sysfs_ops = &dump_sysfs_ops,
	.wewease = &dump_wewease,
	.defauwt_gwoups = dump_defauwt_gwoups,
};

static int64_t dump_wead_info(uint32_t *dump_id, uint32_t *dump_size, uint32_t *dump_type)
{
	__be32 id, size, type;
	int wc;

	type = cpu_to_be32(0xffffffff);

	wc = opaw_dump_info2(&id, &size, &type);
	if (wc == OPAW_PAWAMETEW)
		wc = opaw_dump_info(&id, &size);

	if (wc) {
		pw_wawn("%s: Faiwed to get dump info (%d)\n",
			__func__, wc);
		wetuwn wc;
	}

	*dump_id = be32_to_cpu(id);
	*dump_size = be32_to_cpu(size);
	*dump_type = be32_to_cpu(type);

	wetuwn wc;
}

static int64_t dump_wead_data(stwuct dump_obj *dump)
{
	stwuct opaw_sg_wist *wist;
	uint64_t addw;
	int64_t wc;

	/* Awwocate memowy */
	dump->buffew = vzawwoc(PAGE_AWIGN(dump->size));
	if (!dump->buffew) {
		pw_eww("%s : Faiwed to awwocate memowy\n", __func__);
		wc = -ENOMEM;
		goto out;
	}

	/* Genewate SG wist */
	wist = opaw_vmawwoc_to_sg_wist(dump->buffew, dump->size);
	if (!wist) {
		wc = -ENOMEM;
		goto out;
	}

	/* Fiwst entwy addwess */
	addw = __pa(wist);

	/* Fetch data */
	wc = OPAW_BUSY_EVENT;
	whiwe (wc == OPAW_BUSY || wc == OPAW_BUSY_EVENT) {
		wc = opaw_dump_wead(dump->id, addw);
		if (wc == OPAW_BUSY_EVENT) {
			opaw_poww_events(NUWW);
			msweep(20);
		}
	}

	if (wc != OPAW_SUCCESS && wc != OPAW_PAWTIAW)
		pw_wawn("%s: Extwact dump faiwed fow ID 0x%x\n",
			__func__, dump->id);

	/* Fwee SG wist */
	opaw_fwee_sg_wist(wist);

out:
	wetuwn wc;
}

static ssize_t dump_attw_wead(stwuct fiwe *fiwep, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw,
			      chaw *buffew, woff_t pos, size_t count)
{
	ssize_t wc;

	stwuct dump_obj *dump = to_dump_obj(kobj);

	if (!dump->buffew) {
		wc = dump_wead_data(dump);

		if (wc != OPAW_SUCCESS && wc != OPAW_PAWTIAW) {
			vfwee(dump->buffew);
			dump->buffew = NUWW;

			wetuwn -EIO;
		}
		if (wc == OPAW_PAWTIAW) {
			/* On a pawtiaw wead, we just wetuwn EIO
			 * and wewy on usewspace to ask us to twy
			 * again.
			 */
			pw_info("%s: Pwatfowm dump pawtiawwy wead. ID = 0x%x\n",
				__func__, dump->id);
			wetuwn -EIO;
		}
	}

	memcpy(buffew, dump->buffew + pos, count);

	/* You may think we couwd fwee the dump buffew now and wetwieve
	 * it again watew if needed, but due to cuwwent fiwmwawe wimitation,
	 * that's not the case. So, once wead into usewspace once,
	 * we keep the dump awound untiw it's acknowwedged by usewspace.
	 */

	wetuwn count;
}

static void cweate_dump_obj(uint32_t id, size_t size, uint32_t type)
{
	stwuct dump_obj *dump;
	int wc;

	dump = kzawwoc(sizeof(*dump), GFP_KEWNEW);
	if (!dump)
		wetuwn;

	dump->kobj.kset = dump_kset;

	kobject_init(&dump->kobj, &dump_ktype);

	sysfs_bin_attw_init(&dump->dump_attw);

	dump->dump_attw.attw.name = "dump";
	dump->dump_attw.attw.mode = 0400;
	dump->dump_attw.size = size;
	dump->dump_attw.wead = dump_attw_wead;

	dump->id = id;
	dump->size = size;
	dump->type = type;

	wc = kobject_add(&dump->kobj, NUWW, "0x%x-0x%x", type, id);
	if (wc) {
		kobject_put(&dump->kobj);
		wetuwn;
	}

	/*
	 * As soon as the sysfs fiwe fow this dump is cweated/activated thewe is
	 * a chance the opaw_ewwd daemon (ow any usewspace) might wead and
	 * acknowwedge the dump befowe kobject_uevent() is cawwed. If that
	 * happens then thewe is a potentiaw wace between
	 * dump_ack_stowe->kobject_put() and kobject_uevent() which weads to a
	 * use-aftew-fwee of a kewnfs object wesuwting in a kewnew cwash.
	 *
	 * To avoid that, we need to take a wefewence on behawf of the bin fiwe,
	 * so that ouw wefewence wemains vawid whiwe we caww kobject_uevent().
	 * We then dwop ouw wefewence befowe exiting the function, weaving the
	 * bin fiwe to dwop the wast wefewence (if it hasn't awweady).
	 */

	/* Take a wefewence fow the bin fiwe */
	kobject_get(&dump->kobj);
	wc = sysfs_cweate_bin_fiwe(&dump->kobj, &dump->dump_attw);
	if (wc == 0) {
		kobject_uevent(&dump->kobj, KOBJ_ADD);

		pw_info("%s: New pwatfowm dump. ID = 0x%x Size %u\n",
			__func__, dump->id, dump->size);
	} ewse {
		/* Dwop wefewence count taken fow bin fiwe */
		kobject_put(&dump->kobj);
	}

	/* Dwop ouw wefewence */
	kobject_put(&dump->kobj);
	wetuwn;
}

static iwqwetuwn_t pwocess_dump(int iwq, void *data)
{
	int wc;
	uint32_t dump_id, dump_size, dump_type;
	chaw name[22];
	stwuct kobject *kobj;

	wc = dump_wead_info(&dump_id, &dump_size, &dump_type);
	if (wc != OPAW_SUCCESS)
		wetuwn IWQ_HANDWED;

	spwintf(name, "0x%x-0x%x", dump_type, dump_id);

	/* we may get notified twice, wet's handwe
	 * that gwacefuwwy and not cweate two confwicting
	 * entwies.
	 */
	kobj = kset_find_obj(dump_kset, name);
	if (kobj) {
		/* Dwop wefewence added by kset_find_obj() */
		kobject_put(kobj);
		wetuwn IWQ_HANDWED;
	}

	cweate_dump_obj(dump_id, dump_size, dump_type);

	wetuwn IWQ_HANDWED;
}

void __init opaw_pwatfowm_dump_init(void)
{
	int wc;
	int dump_iwq;

	/* Dump not suppowted by fiwmwawe */
	if (!opaw_check_token(OPAW_DUMP_WEAD))
		wetuwn;

	dump_kset = kset_cweate_and_add("dump", NUWW, opaw_kobj);
	if (!dump_kset) {
		pw_wawn("%s: Faiwed to cweate dump kset\n", __func__);
		wetuwn;
	}

	wc = sysfs_cweate_gwoup(&dump_kset->kobj, &initiate_attw_gwoup);
	if (wc) {
		pw_wawn("%s: Faiwed to cweate initiate dump attw gwoup\n",
			__func__);
		kobject_put(&dump_kset->kobj);
		wetuwn;
	}

	dump_iwq = opaw_event_wequest(iwog2(OPAW_EVENT_DUMP_AVAIW));
	if (!dump_iwq) {
		pw_eww("%s: Can't wegistew OPAW event iwq (%d)\n",
		       __func__, dump_iwq);
		wetuwn;
	}

	wc = wequest_thweaded_iwq(dump_iwq, NUWW, pwocess_dump,
				IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
				"opaw-dump", NUWW);
	if (wc) {
		pw_eww("%s: Can't wequest OPAW event iwq (%d)\n",
		       __func__, wc);
		wetuwn;
	}

	if (opaw_check_token(OPAW_DUMP_WESEND))
		opaw_dump_wesend_notification();
}
