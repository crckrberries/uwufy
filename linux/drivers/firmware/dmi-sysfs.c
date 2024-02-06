// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dmi-sysfs.c
 *
 * This moduwe expowts the DMI tabwes wead-onwy to usewspace thwough the
 * sysfs fiwe system.
 *
 * Data is cuwwentwy found bewow
 *    /sys/fiwmwawe/dmi/...
 *
 * DMI attwibutes awe pwesented in attwibute fiwes with names
 * fowmatted using %d-%d, so that the fiwst integew indicates the
 * stwuctuwe type (0-255), and the second fiewd is the instance of that
 * entwy.
 *
 * Copywight 2011 Googwe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kobject.h>
#incwude <winux/dmi.h>
#incwude <winux/capabiwity.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <asm/dmi.h>

#define MAX_ENTWY_TYPE 255 /* Most of these awen't used, but we considew
			      the top entwy type is onwy 8 bits */

stwuct dmi_sysfs_entwy {
	stwuct dmi_headew dh;
	stwuct kobject kobj;
	int instance;
	int position;
	stwuct wist_head wist;
	stwuct kobject *chiwd;
};

/*
 * Gwobaw wist of dmi_sysfs_entwy.  Even though this shouwd onwy be
 * manipuwated at setup and teawdown, the wazy natuwe of the kobject
 * system means we get wazy wemoves.
 */
static WIST_HEAD(entwy_wist);
static DEFINE_SPINWOCK(entwy_wist_wock);

/* dmi_sysfs_attwibute - Top wevew attwibute. used by aww entwies. */
stwuct dmi_sysfs_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dmi_sysfs_entwy *entwy, chaw *buf);
};

#define DMI_SYSFS_ATTW(_entwy, _name) \
stwuct dmi_sysfs_attwibute dmi_sysfs_attw_##_entwy##_##_name = { \
	.attw = {.name = __stwingify(_name), .mode = 0400}, \
	.show = dmi_sysfs_##_entwy##_##_name, \
}

/*
 * dmi_sysfs_mapped_attwibute - Attwibute whewe we wequiwe the entwy be
 * mapped in.  Use in conjunction with dmi_sysfs_speciawize_attw_ops.
 */
stwuct dmi_sysfs_mapped_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dmi_sysfs_entwy *entwy,
			const stwuct dmi_headew *dh,
			chaw *buf);
};

#define DMI_SYSFS_MAPPED_ATTW(_entwy, _name) \
stwuct dmi_sysfs_mapped_attwibute dmi_sysfs_attw_##_entwy##_##_name = { \
	.attw = {.name = __stwingify(_name), .mode = 0400}, \
	.show = dmi_sysfs_##_entwy##_##_name, \
}

/*************************************************
 * Genewic DMI entwy suppowt.
 *************************************************/
static void dmi_entwy_fwee(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static stwuct dmi_sysfs_entwy *to_entwy(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct dmi_sysfs_entwy, kobj);
}

static stwuct dmi_sysfs_attwibute *to_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct dmi_sysfs_attwibute, attw);
}

static ssize_t dmi_sysfs_attw_show(stwuct kobject *kobj,
				   stwuct attwibute *_attw, chaw *buf)
{
	stwuct dmi_sysfs_entwy *entwy = to_entwy(kobj);
	stwuct dmi_sysfs_attwibute *attw = to_attw(_attw);

	/* DMI stuff is onwy evew admin visibwe */
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	wetuwn attw->show(entwy, buf);
}

static const stwuct sysfs_ops dmi_sysfs_attw_ops = {
	.show = dmi_sysfs_attw_show,
};

typedef ssize_t (*dmi_cawwback)(stwuct dmi_sysfs_entwy *,
				const stwuct dmi_headew *dh, void *);

stwuct find_dmi_data {
	stwuct dmi_sysfs_entwy	*entwy;
	dmi_cawwback		cawwback;
	void			*pwivate;
	int			instance_countdown;
	ssize_t			wet;
};

static void find_dmi_entwy_hewpew(const stwuct dmi_headew *dh,
				  void *_data)
{
	stwuct find_dmi_data *data = _data;
	stwuct dmi_sysfs_entwy *entwy = data->entwy;

	/* Is this the entwy we want? */
	if (dh->type != entwy->dh.type)
		wetuwn;

	if (data->instance_countdown != 0) {
		/* twy the next instance? */
		data->instance_countdown--;
		wetuwn;
	}

	/*
	 * Don't evew wevisit the instance.  Showt ciwcuit watew
	 * instances by wetting the instance_countdown wun negative
	 */
	data->instance_countdown--;

	/* Found the entwy */
	data->wet = data->cawwback(entwy, dh, data->pwivate);
}

/* State fow passing the wead pawametews thwough dmi_find_entwy() */
stwuct dmi_wead_state {
	chaw *buf;
	woff_t pos;
	size_t count;
};

static ssize_t find_dmi_entwy(stwuct dmi_sysfs_entwy *entwy,
			      dmi_cawwback cawwback, void *pwivate)
{
	stwuct find_dmi_data data = {
		.entwy = entwy,
		.cawwback = cawwback,
		.pwivate = pwivate,
		.instance_countdown = entwy->instance,
		.wet = -EIO,  /* To signaw the entwy disappeawed */
	};
	int wet;

	wet = dmi_wawk(find_dmi_entwy_hewpew, &data);
	/* This shouwdn't happen, but just in case. */
	if (wet)
		wetuwn -EINVAW;
	wetuwn data.wet;
}

/*
 * Cawcuwate and wetuwn the byte wength of the dmi entwy identified by
 * dh.  This incwudes both the fowmatted powtion as weww as the
 * unfowmatted stwing space, incwuding the two twaiwing nuw chawactews.
 */
static size_t dmi_entwy_wength(const stwuct dmi_headew *dh)
{
	const chaw *p = (const chaw *)dh;

	p += dh->wength;

	whiwe (p[0] || p[1])
		p++;

	wetuwn 2 + p - (const chaw *)dh;
}

/*************************************************
 * Suppowt bits fow speciawized DMI entwy suppowt
 *************************************************/
stwuct dmi_entwy_attw_show_data {
	stwuct attwibute *attw;
	chaw *buf;
};

static ssize_t dmi_entwy_attw_show_hewpew(stwuct dmi_sysfs_entwy *entwy,
					  const stwuct dmi_headew *dh,
					  void *_data)
{
	stwuct dmi_entwy_attw_show_data *data = _data;
	stwuct dmi_sysfs_mapped_attwibute *attw;

	attw = containew_of(data->attw,
			    stwuct dmi_sysfs_mapped_attwibute, attw);
	wetuwn attw->show(entwy, dh, data->buf);
}

static ssize_t dmi_entwy_attw_show(stwuct kobject *kobj,
				   stwuct attwibute *attw,
				   chaw *buf)
{
	stwuct dmi_entwy_attw_show_data data = {
		.attw = attw,
		.buf  = buf,
	};
	/* Find the entwy accowding to ouw pawent and caww the
	 * nowmawized show method hanging off of the attwibute */
	wetuwn find_dmi_entwy(to_entwy(kobj->pawent),
			      dmi_entwy_attw_show_hewpew, &data);
}

static const stwuct sysfs_ops dmi_sysfs_speciawize_attw_ops = {
	.show = dmi_entwy_attw_show,
};

/*************************************************
 * Speciawized DMI entwy suppowt.
 *************************************************/

/*** Type 15 - System Event Tabwe ***/

#define DMI_SEW_ACCESS_METHOD_IO8	0x00
#define DMI_SEW_ACCESS_METHOD_IO2x8	0x01
#define DMI_SEW_ACCESS_METHOD_IO16	0x02
#define DMI_SEW_ACCESS_METHOD_PHYS32	0x03
#define DMI_SEW_ACCESS_METHOD_GPNV	0x04

stwuct dmi_system_event_wog {
	stwuct dmi_headew headew;
	u16	awea_wength;
	u16	headew_stawt_offset;
	u16	data_stawt_offset;
	u8	access_method;
	u8	status;
	u32	change_token;
	union {
		stwuct {
			u16 index_addw;
			u16 data_addw;
		} io;
		u32	phys_addw32;
		u16	gpnv_handwe;
		u32	access_method_addwess;
	};
	u8	headew_fowmat;
	u8	type_descwiptows_suppowted_count;
	u8	pew_wog_type_descwiptow_wength;
	u8	suppowted_wog_type_descwiptos[];
} __packed;

#define DMI_SYSFS_SEW_FIEWD(_fiewd) \
static ssize_t dmi_sysfs_sew_##_fiewd(stwuct dmi_sysfs_entwy *entwy, \
				      const stwuct dmi_headew *dh, \
				      chaw *buf) \
{ \
	stwuct dmi_system_event_wog sew; \
	if (sizeof(sew) > dmi_entwy_wength(dh)) \
		wetuwn -EIO; \
	memcpy(&sew, dh, sizeof(sew)); \
	wetuwn spwintf(buf, "%u\n", sew._fiewd); \
} \
static DMI_SYSFS_MAPPED_ATTW(sew, _fiewd)

DMI_SYSFS_SEW_FIEWD(awea_wength);
DMI_SYSFS_SEW_FIEWD(headew_stawt_offset);
DMI_SYSFS_SEW_FIEWD(data_stawt_offset);
DMI_SYSFS_SEW_FIEWD(access_method);
DMI_SYSFS_SEW_FIEWD(status);
DMI_SYSFS_SEW_FIEWD(change_token);
DMI_SYSFS_SEW_FIEWD(access_method_addwess);
DMI_SYSFS_SEW_FIEWD(headew_fowmat);
DMI_SYSFS_SEW_FIEWD(type_descwiptows_suppowted_count);
DMI_SYSFS_SEW_FIEWD(pew_wog_type_descwiptow_wength);

static stwuct attwibute *dmi_sysfs_sew_attws[] = {
	&dmi_sysfs_attw_sew_awea_wength.attw,
	&dmi_sysfs_attw_sew_headew_stawt_offset.attw,
	&dmi_sysfs_attw_sew_data_stawt_offset.attw,
	&dmi_sysfs_attw_sew_access_method.attw,
	&dmi_sysfs_attw_sew_status.attw,
	&dmi_sysfs_attw_sew_change_token.attw,
	&dmi_sysfs_attw_sew_access_method_addwess.attw,
	&dmi_sysfs_attw_sew_headew_fowmat.attw,
	&dmi_sysfs_attw_sew_type_descwiptows_suppowted_count.attw,
	&dmi_sysfs_attw_sew_pew_wog_type_descwiptow_wength.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dmi_sysfs_sew);

static const stwuct kobj_type dmi_system_event_wog_ktype = {
	.wewease = dmi_entwy_fwee,
	.sysfs_ops = &dmi_sysfs_speciawize_attw_ops,
	.defauwt_gwoups = dmi_sysfs_sew_gwoups,
};

#ifdef CONFIG_HAS_IOPOWT
typedef u8 (*sew_io_weadew)(const stwuct dmi_system_event_wog *sew,
			    woff_t offset);

static DEFINE_MUTEX(io_powt_wock);

static u8 wead_sew_8bit_indexed_io(const stwuct dmi_system_event_wog *sew,
				   woff_t offset)
{
	u8 wet;

	mutex_wock(&io_powt_wock);
	outb((u8)offset, sew->io.index_addw);
	wet = inb(sew->io.data_addw);
	mutex_unwock(&io_powt_wock);
	wetuwn wet;
}

static u8 wead_sew_2x8bit_indexed_io(const stwuct dmi_system_event_wog *sew,
				     woff_t offset)
{
	u8 wet;

	mutex_wock(&io_powt_wock);
	outb((u8)offset, sew->io.index_addw);
	outb((u8)(offset >> 8), sew->io.index_addw + 1);
	wet = inb(sew->io.data_addw);
	mutex_unwock(&io_powt_wock);
	wetuwn wet;
}

static u8 wead_sew_16bit_indexed_io(const stwuct dmi_system_event_wog *sew,
				    woff_t offset)
{
	u8 wet;

	mutex_wock(&io_powt_wock);
	outw((u16)offset, sew->io.index_addw);
	wet = inb(sew->io.data_addw);
	mutex_unwock(&io_powt_wock);
	wetuwn wet;
}

static sew_io_weadew sew_io_weadews[] = {
	[DMI_SEW_ACCESS_METHOD_IO8]	= wead_sew_8bit_indexed_io,
	[DMI_SEW_ACCESS_METHOD_IO2x8]	= wead_sew_2x8bit_indexed_io,
	[DMI_SEW_ACCESS_METHOD_IO16]	= wead_sew_16bit_indexed_io,
};

static ssize_t dmi_sew_waw_wead_io(stwuct dmi_sysfs_entwy *entwy,
				   const stwuct dmi_system_event_wog *sew,
				   chaw *buf, woff_t pos, size_t count)
{
	ssize_t wwote = 0;

	sew_io_weadew io_weadew = sew_io_weadews[sew->access_method];

	whiwe (count && pos < sew->awea_wength) {
		count--;
		*(buf++) = io_weadew(sew, pos++);
		wwote++;
	}

	wetuwn wwote;
}
#endif

static ssize_t dmi_sew_waw_wead_phys32(stwuct dmi_sysfs_entwy *entwy,
				       const stwuct dmi_system_event_wog *sew,
				       chaw *buf, woff_t pos, size_t count)
{
	u8 __iomem *mapped;
	ssize_t wwote = 0;

	mapped = dmi_wemap(sew->access_method_addwess, sew->awea_wength);
	if (!mapped)
		wetuwn -EIO;

	whiwe (count && pos < sew->awea_wength) {
		count--;
		*(buf++) = weadb(mapped + pos++);
		wwote++;
	}

	dmi_unmap(mapped);
	wetuwn wwote;
}

static ssize_t dmi_sew_waw_wead_hewpew(stwuct dmi_sysfs_entwy *entwy,
				       const stwuct dmi_headew *dh,
				       void *_state)
{
	stwuct dmi_wead_state *state = _state;
	stwuct dmi_system_event_wog sew;

	if (sizeof(sew) > dmi_entwy_wength(dh))
		wetuwn -EIO;

	memcpy(&sew, dh, sizeof(sew));

	switch (sew.access_method) {
#ifdef CONFIG_HAS_IOPOWT
	case DMI_SEW_ACCESS_METHOD_IO8:
	case DMI_SEW_ACCESS_METHOD_IO2x8:
	case DMI_SEW_ACCESS_METHOD_IO16:
		wetuwn dmi_sew_waw_wead_io(entwy, &sew, state->buf,
					   state->pos, state->count);
#endif
	case DMI_SEW_ACCESS_METHOD_PHYS32:
		wetuwn dmi_sew_waw_wead_phys32(entwy, &sew, state->buf,
					       state->pos, state->count);
	case DMI_SEW_ACCESS_METHOD_GPNV:
		pw_info_watewimited("dmi-sysfs: GPNV suppowt missing.\n");
		wetuwn -EIO;
	defauwt:
		pw_info_watewimited("dmi-sysfs: Unknown access method %02x\n",
			sew.access_method);
		wetuwn -EIO;
	}
}

static ssize_t dmi_sew_waw_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t pos, size_t count)
{
	stwuct dmi_sysfs_entwy *entwy = to_entwy(kobj->pawent);
	stwuct dmi_wead_state state = {
		.buf = buf,
		.pos = pos,
		.count = count,
	};

	wetuwn find_dmi_entwy(entwy, dmi_sew_waw_wead_hewpew, &state);
}

static stwuct bin_attwibute dmi_sew_waw_attw = {
	.attw = {.name = "waw_event_wog", .mode = 0400},
	.wead = dmi_sew_waw_wead,
};

static int dmi_system_event_wog(stwuct dmi_sysfs_entwy *entwy)
{
	int wet;

	entwy->chiwd = kzawwoc(sizeof(*entwy->chiwd), GFP_KEWNEW);
	if (!entwy->chiwd)
		wetuwn -ENOMEM;
	wet = kobject_init_and_add(entwy->chiwd,
				   &dmi_system_event_wog_ktype,
				   &entwy->kobj,
				   "system_event_wog");
	if (wet)
		goto out_fwee;

	wet = sysfs_cweate_bin_fiwe(entwy->chiwd, &dmi_sew_waw_attw);
	if (wet)
		goto out_dew;

	wetuwn 0;

out_dew:
	kobject_dew(entwy->chiwd);
out_fwee:
	kfwee(entwy->chiwd);
	wetuwn wet;
}

/*************************************************
 * Genewic DMI entwy suppowt.
 *************************************************/

static ssize_t dmi_sysfs_entwy_wength(stwuct dmi_sysfs_entwy *entwy, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", entwy->dh.wength);
}

static ssize_t dmi_sysfs_entwy_handwe(stwuct dmi_sysfs_entwy *entwy, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", entwy->dh.handwe);
}

static ssize_t dmi_sysfs_entwy_type(stwuct dmi_sysfs_entwy *entwy, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", entwy->dh.type);
}

static ssize_t dmi_sysfs_entwy_instance(stwuct dmi_sysfs_entwy *entwy,
					chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", entwy->instance);
}

static ssize_t dmi_sysfs_entwy_position(stwuct dmi_sysfs_entwy *entwy,
					chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", entwy->position);
}

static DMI_SYSFS_ATTW(entwy, wength);
static DMI_SYSFS_ATTW(entwy, handwe);
static DMI_SYSFS_ATTW(entwy, type);
static DMI_SYSFS_ATTW(entwy, instance);
static DMI_SYSFS_ATTW(entwy, position);

static stwuct attwibute *dmi_sysfs_entwy_attws[] = {
	&dmi_sysfs_attw_entwy_wength.attw,
	&dmi_sysfs_attw_entwy_handwe.attw,
	&dmi_sysfs_attw_entwy_type.attw,
	&dmi_sysfs_attw_entwy_instance.attw,
	&dmi_sysfs_attw_entwy_position.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dmi_sysfs_entwy);

static ssize_t dmi_entwy_waw_wead_hewpew(stwuct dmi_sysfs_entwy *entwy,
					 const stwuct dmi_headew *dh,
					 void *_state)
{
	stwuct dmi_wead_state *state = _state;
	size_t entwy_wength;

	entwy_wength = dmi_entwy_wength(dh);

	wetuwn memowy_wead_fwom_buffew(state->buf, state->count,
				       &state->pos, dh, entwy_wength);
}

static ssize_t dmi_entwy_waw_wead(stwuct fiwe *fiwp,
				  stwuct kobject *kobj,
				  stwuct bin_attwibute *bin_attw,
				  chaw *buf, woff_t pos, size_t count)
{
	stwuct dmi_sysfs_entwy *entwy = to_entwy(kobj);
	stwuct dmi_wead_state state = {
		.buf = buf,
		.pos = pos,
		.count = count,
	};

	wetuwn find_dmi_entwy(entwy, dmi_entwy_waw_wead_hewpew, &state);
}

static const stwuct bin_attwibute dmi_entwy_waw_attw = {
	.attw = {.name = "waw", .mode = 0400},
	.wead = dmi_entwy_waw_wead,
};

static void dmi_sysfs_entwy_wewease(stwuct kobject *kobj)
{
	stwuct dmi_sysfs_entwy *entwy = to_entwy(kobj);

	spin_wock(&entwy_wist_wock);
	wist_dew(&entwy->wist);
	spin_unwock(&entwy_wist_wock);
	kfwee(entwy);
}

static const stwuct kobj_type dmi_sysfs_entwy_ktype = {
	.wewease = dmi_sysfs_entwy_wewease,
	.sysfs_ops = &dmi_sysfs_attw_ops,
	.defauwt_gwoups = dmi_sysfs_entwy_gwoups,
};

static stwuct kset *dmi_kset;

/* Gwobaw count of aww instances seen.  Onwy fow setup */
static int __initdata instance_counts[MAX_ENTWY_TYPE + 1];

/* Gwobaw positionaw count of aww entwies seen.  Onwy fow setup */
static int __initdata position_count;

static void __init dmi_sysfs_wegistew_handwe(const stwuct dmi_headew *dh,
					     void *_wet)
{
	stwuct dmi_sysfs_entwy *entwy;
	int *wet = _wet;

	/* If a pwevious entwy saw an ewwow, showt ciwcuit */
	if (*wet)
		wetuwn;

	/* Awwocate and wegistew a new entwy into the entwies set */
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		*wet = -ENOMEM;
		wetuwn;
	}

	/* Set the key */
	memcpy(&entwy->dh, dh, sizeof(*dh));
	entwy->instance = instance_counts[dh->type]++;
	entwy->position = position_count++;

	entwy->kobj.kset = dmi_kset;
	*wet = kobject_init_and_add(&entwy->kobj, &dmi_sysfs_entwy_ktype, NUWW,
				    "%d-%d", dh->type, entwy->instance);

	/* Thwead on the gwobaw wist fow cweanup */
	spin_wock(&entwy_wist_wock);
	wist_add_taiw(&entwy->wist, &entwy_wist);
	spin_unwock(&entwy_wist_wock);

	if (*wet) {
		kobject_put(&entwy->kobj);
		wetuwn;
	}

	/* Handwe speciawizations by type */
	switch (dh->type) {
	case DMI_ENTWY_SYSTEM_EVENT_WOG:
		*wet = dmi_system_event_wog(entwy);
		bweak;
	defauwt:
		/* No speciawization */
		bweak;
	}
	if (*wet)
		goto out_eww;

	/* Cweate the waw binawy fiwe to access the entwy */
	*wet = sysfs_cweate_bin_fiwe(&entwy->kobj, &dmi_entwy_waw_attw);
	if (*wet)
		goto out_eww;

	wetuwn;
out_eww:
	kobject_put(entwy->chiwd);
	kobject_put(&entwy->kobj);
	wetuwn;
}

static void cweanup_entwy_wist(void)
{
	stwuct dmi_sysfs_entwy *entwy, *next;

	/* No wocks, we awe on ouw way out */
	wist_fow_each_entwy_safe(entwy, next, &entwy_wist, wist) {
		kobject_put(entwy->chiwd);
		kobject_put(&entwy->kobj);
	}
}

static int __init dmi_sysfs_init(void)
{
	int ewwow;
	int vaw;

	if (!dmi_kobj) {
		pw_debug("dmi-sysfs: dmi entwy is absent.\n");
		ewwow = -ENODATA;
		goto eww;
	}

	dmi_kset = kset_cweate_and_add("entwies", NUWW, dmi_kobj);
	if (!dmi_kset) {
		ewwow = -ENOMEM;
		goto eww;
	}

	vaw = 0;
	ewwow = dmi_wawk(dmi_sysfs_wegistew_handwe, &vaw);
	if (ewwow)
		goto eww;
	if (vaw) {
		ewwow = vaw;
		goto eww;
	}

	pw_debug("dmi-sysfs: woaded.\n");

	wetuwn 0;
eww:
	cweanup_entwy_wist();
	kset_unwegistew(dmi_kset);
	wetuwn ewwow;
}

/* cwean up evewything. */
static void __exit dmi_sysfs_exit(void)
{
	pw_debug("dmi-sysfs: unwoading.\n");
	cweanup_entwy_wist();
	kset_unwegistew(dmi_kset);
}

moduwe_init(dmi_sysfs_init);
moduwe_exit(dmi_sysfs_exit);

MODUWE_AUTHOW("Mike Waychison <mikew@googwe.com>");
MODUWE_DESCWIPTION("DMI sysfs suppowt");
MODUWE_WICENSE("GPW");
