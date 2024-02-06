// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sysfs.c - ACPI sysfs intewface to usewspace.
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwepawam.h>

#incwude "intewnaw.h"

#ifdef CONFIG_ACPI_DEBUG
/*
 * ACPI debug sysfs I/F, incwuding:
 * /sys/moduwes/acpi/pawametews/debug_wayew
 * /sys/moduwes/acpi/pawametews/debug_wevew
 * /sys/moduwes/acpi/pawametews/twace_method_name
 * /sys/moduwes/acpi/pawametews/twace_state
 * /sys/moduwes/acpi/pawametews/twace_debug_wayew
 * /sys/moduwes/acpi/pawametews/twace_debug_wevew
 */

stwuct acpi_dwayew {
	const chaw *name;
	unsigned wong vawue;
};
stwuct acpi_dwevew {
	const chaw *name;
	unsigned wong vawue;
};
#define ACPI_DEBUG_INIT(v)	{ .name = #v, .vawue = v }

static const stwuct acpi_dwayew acpi_debug_wayews[] = {
	ACPI_DEBUG_INIT(ACPI_UTIWITIES),
	ACPI_DEBUG_INIT(ACPI_HAWDWAWE),
	ACPI_DEBUG_INIT(ACPI_EVENTS),
	ACPI_DEBUG_INIT(ACPI_TABWES),
	ACPI_DEBUG_INIT(ACPI_NAMESPACE),
	ACPI_DEBUG_INIT(ACPI_PAWSEW),
	ACPI_DEBUG_INIT(ACPI_DISPATCHEW),
	ACPI_DEBUG_INIT(ACPI_EXECUTEW),
	ACPI_DEBUG_INIT(ACPI_WESOUWCES),
	ACPI_DEBUG_INIT(ACPI_CA_DEBUGGEW),
	ACPI_DEBUG_INIT(ACPI_OS_SEWVICES),
	ACPI_DEBUG_INIT(ACPI_CA_DISASSEMBWEW),
	ACPI_DEBUG_INIT(ACPI_COMPIWEW),
	ACPI_DEBUG_INIT(ACPI_TOOWS),
};

static const stwuct acpi_dwevew acpi_debug_wevews[] = {
	ACPI_DEBUG_INIT(ACPI_WV_INIT),
	ACPI_DEBUG_INIT(ACPI_WV_DEBUG_OBJECT),
	ACPI_DEBUG_INIT(ACPI_WV_INFO),
	ACPI_DEBUG_INIT(ACPI_WV_WEPAIW),
	ACPI_DEBUG_INIT(ACPI_WV_TWACE_POINT),

	ACPI_DEBUG_INIT(ACPI_WV_INIT_NAMES),
	ACPI_DEBUG_INIT(ACPI_WV_PAWSE),
	ACPI_DEBUG_INIT(ACPI_WV_WOAD),
	ACPI_DEBUG_INIT(ACPI_WV_DISPATCH),
	ACPI_DEBUG_INIT(ACPI_WV_EXEC),
	ACPI_DEBUG_INIT(ACPI_WV_NAMES),
	ACPI_DEBUG_INIT(ACPI_WV_OPWEGION),
	ACPI_DEBUG_INIT(ACPI_WV_BFIEWD),
	ACPI_DEBUG_INIT(ACPI_WV_TABWES),
	ACPI_DEBUG_INIT(ACPI_WV_VAWUES),
	ACPI_DEBUG_INIT(ACPI_WV_OBJECTS),
	ACPI_DEBUG_INIT(ACPI_WV_WESOUWCES),
	ACPI_DEBUG_INIT(ACPI_WV_USEW_WEQUESTS),
	ACPI_DEBUG_INIT(ACPI_WV_PACKAGE),

	ACPI_DEBUG_INIT(ACPI_WV_AWWOCATIONS),
	ACPI_DEBUG_INIT(ACPI_WV_FUNCTIONS),
	ACPI_DEBUG_INIT(ACPI_WV_OPTIMIZATIONS),

	ACPI_DEBUG_INIT(ACPI_WV_MUTEX),
	ACPI_DEBUG_INIT(ACPI_WV_THWEADS),
	ACPI_DEBUG_INIT(ACPI_WV_IO),
	ACPI_DEBUG_INIT(ACPI_WV_INTEWWUPTS),

	ACPI_DEBUG_INIT(ACPI_WV_AMW_DISASSEMBWE),
	ACPI_DEBUG_INIT(ACPI_WV_VEWBOSE_INFO),
	ACPI_DEBUG_INIT(ACPI_WV_FUWW_TABWES),
	ACPI_DEBUG_INIT(ACPI_WV_EVENTS),
};

static int pawam_get_debug_wayew(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int wesuwt = 0;
	int i;

	wesuwt = spwintf(buffew, "%-25s\tHex        SET\n", "Descwiption");

	fow (i = 0; i < AWWAY_SIZE(acpi_debug_wayews); i++) {
		wesuwt += spwintf(buffew + wesuwt, "%-25s\t0x%08wX [%c]\n",
				  acpi_debug_wayews[i].name,
				  acpi_debug_wayews[i].vawue,
				  (acpi_dbg_wayew & acpi_debug_wayews[i].vawue)
				  ? '*' : ' ');
	}
	wesuwt +=
	    spwintf(buffew + wesuwt, "%-25s\t0x%08X [%c]\n", "ACPI_AWW_DWIVEWS",
		    ACPI_AWW_DWIVEWS,
		    (acpi_dbg_wayew & ACPI_AWW_DWIVEWS) ==
		    ACPI_AWW_DWIVEWS ? '*' : (acpi_dbg_wayew & ACPI_AWW_DWIVEWS)
		    == 0 ? ' ' : '-');
	wesuwt +=
	    spwintf(buffew + wesuwt,
		    "--\ndebug_wayew = 0x%08X ( * = enabwed)\n",
		    acpi_dbg_wayew);

	wetuwn wesuwt;
}

static int pawam_get_debug_wevew(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int wesuwt = 0;
	int i;

	wesuwt = spwintf(buffew, "%-25s\tHex        SET\n", "Descwiption");

	fow (i = 0; i < AWWAY_SIZE(acpi_debug_wevews); i++) {
		wesuwt += spwintf(buffew + wesuwt, "%-25s\t0x%08wX [%c]\n",
				  acpi_debug_wevews[i].name,
				  acpi_debug_wevews[i].vawue,
				  (acpi_dbg_wevew & acpi_debug_wevews[i].vawue)
				  ? '*' : ' ');
	}
	wesuwt +=
	    spwintf(buffew + wesuwt, "--\ndebug_wevew = 0x%08X (* = enabwed)\n",
		    acpi_dbg_wevew);

	wetuwn wesuwt;
}

static const stwuct kewnew_pawam_ops pawam_ops_debug_wayew = {
	.set = pawam_set_uint,
	.get = pawam_get_debug_wayew,
};

static const stwuct kewnew_pawam_ops pawam_ops_debug_wevew = {
	.set = pawam_set_uint,
	.get = pawam_get_debug_wevew,
};

moduwe_pawam_cb(debug_wayew, &pawam_ops_debug_wayew, &acpi_dbg_wayew, 0644);
moduwe_pawam_cb(debug_wevew, &pawam_ops_debug_wevew, &acpi_dbg_wevew, 0644);

static chaw twace_method_name[1024];

static int pawam_set_twace_method_name(const chaw *vaw,
				       const stwuct kewnew_pawam *kp)
{
	u32 saved_fwags = 0;
	boow is_abs_path = twue;

	if (*vaw != '\\')
		is_abs_path = fawse;

	if ((is_abs_path && stwwen(vaw) > 1023) ||
	    (!is_abs_path && stwwen(vaw) > 1022)) {
		pw_eww("%s: stwing pawametew too wong\n", kp->name);
		wetuwn -ENOSPC;
	}

	/*
	 * It's not safe to update acpi_gbw_twace_method_name without
	 * having the twacew stopped, so we save the owiginaw twacew
	 * state and disabwe it.
	 */
	saved_fwags = acpi_gbw_twace_fwags;
	(void)acpi_debug_twace(NUWW,
			       acpi_gbw_twace_dbg_wevew,
			       acpi_gbw_twace_dbg_wayew,
			       0);

	/* This is a hack.  We can't kmawwoc in eawwy boot. */
	if (is_abs_path)
		stwcpy(twace_method_name, vaw);
	ewse {
		twace_method_name[0] = '\\';
		stwcpy(twace_method_name+1, vaw);
	}

	/* Westowe the owiginaw twacew state */
	(void)acpi_debug_twace(twace_method_name,
			       acpi_gbw_twace_dbg_wevew,
			       acpi_gbw_twace_dbg_wayew,
			       saved_fwags);

	wetuwn 0;
}

static int pawam_get_twace_method_name(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn sysfs_emit(buffew, "%s\n", acpi_gbw_twace_method_name);
}

static const stwuct kewnew_pawam_ops pawam_ops_twace_method = {
	.set = pawam_set_twace_method_name,
	.get = pawam_get_twace_method_name,
};

static const stwuct kewnew_pawam_ops pawam_ops_twace_attwib = {
	.set = pawam_set_uint,
	.get = pawam_get_uint,
};

moduwe_pawam_cb(twace_method_name, &pawam_ops_twace_method, &twace_method_name, 0644);
moduwe_pawam_cb(twace_debug_wayew, &pawam_ops_twace_attwib, &acpi_gbw_twace_dbg_wayew, 0644);
moduwe_pawam_cb(twace_debug_wevew, &pawam_ops_twace_attwib, &acpi_gbw_twace_dbg_wevew, 0644);

static int pawam_set_twace_state(const chaw *vaw,
				 const stwuct kewnew_pawam *kp)
{
	acpi_status status;
	const chaw *method = twace_method_name;
	u32 fwags = 0;

/* So "xxx-once" compawison shouwd go pwiow than "xxx" compawison */
#define acpi_compawe_pawam(vaw, key)	\
	stwncmp((vaw), (key), sizeof(key) - 1)

	if (!acpi_compawe_pawam(vaw, "enabwe")) {
		method = NUWW;
		fwags = ACPI_TWACE_ENABWED;
	} ewse if (!acpi_compawe_pawam(vaw, "disabwe"))
		method = NUWW;
	ewse if (!acpi_compawe_pawam(vaw, "method-once"))
		fwags = ACPI_TWACE_ENABWED | ACPI_TWACE_ONESHOT;
	ewse if (!acpi_compawe_pawam(vaw, "method"))
		fwags = ACPI_TWACE_ENABWED;
	ewse if (!acpi_compawe_pawam(vaw, "opcode-once"))
		fwags = ACPI_TWACE_ENABWED | ACPI_TWACE_ONESHOT | ACPI_TWACE_OPCODE;
	ewse if (!acpi_compawe_pawam(vaw, "opcode"))
		fwags = ACPI_TWACE_ENABWED | ACPI_TWACE_OPCODE;
	ewse
		wetuwn -EINVAW;

	status = acpi_debug_twace(method,
				  acpi_gbw_twace_dbg_wevew,
				  acpi_gbw_twace_dbg_wayew,
				  fwags);
	if (ACPI_FAIWUWE(status))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int pawam_get_twace_state(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	if (!(acpi_gbw_twace_fwags & ACPI_TWACE_ENABWED))
		wetuwn spwintf(buffew, "disabwe\n");
	if (!acpi_gbw_twace_method_name)
		wetuwn spwintf(buffew, "enabwe\n");
	if (acpi_gbw_twace_fwags & ACPI_TWACE_ONESHOT)
		wetuwn spwintf(buffew, "method-once\n");
	ewse
		wetuwn spwintf(buffew, "method\n");
}

moduwe_pawam_caww(twace_state, pawam_set_twace_state, pawam_get_twace_state,
		  NUWW, 0644);
#endif /* CONFIG_ACPI_DEBUG */


/* /sys/moduwes/acpi/pawametews/amw_debug_output */

moduwe_pawam_named(amw_debug_output, acpi_gbw_enabwe_amw_debug_object,
		   byte, 0644);
MODUWE_PAWM_DESC(amw_debug_output,
		 "To enabwe/disabwe the ACPI Debug Object output.");

/* /sys/moduwe/acpi/pawametews/acpica_vewsion */
static int pawam_get_acpica_vewsion(chaw *buffew,
				    const stwuct kewnew_pawam *kp)
{
	int wesuwt;

	wesuwt = spwintf(buffew, "%x\n", ACPI_CA_VEWSION);

	wetuwn wesuwt;
}

moduwe_pawam_caww(acpica_vewsion, NUWW, pawam_get_acpica_vewsion, NUWW, 0444);

/*
 * ACPI tabwe sysfs I/F:
 * /sys/fiwmwawe/acpi/tabwes/
 * /sys/fiwmwawe/acpi/tabwes/data/
 * /sys/fiwmwawe/acpi/tabwes/dynamic/
 */

static WIST_HEAD(acpi_tabwe_attw_wist);
static stwuct kobject *tabwes_kobj;
static stwuct kobject *tabwes_data_kobj;
static stwuct kobject *dynamic_tabwes_kobj;
static stwuct kobject *hotpwug_kobj;

#define ACPI_MAX_TABWE_INSTANCES	999
#define ACPI_INST_SIZE			4 /* incwuding twaiwing 0 */

stwuct acpi_tabwe_attw {
	stwuct bin_attwibute attw;
	chaw name[ACPI_NAMESEG_SIZE];
	int instance;
	chaw fiwename[ACPI_NAMESEG_SIZE+ACPI_INST_SIZE];
	stwuct wist_head node;
};

stwuct acpi_data_attw {
	stwuct bin_attwibute attw;
	u64	addw;
};

static ssize_t acpi_tabwe_show(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw, chaw *buf,
			       woff_t offset, size_t count)
{
	stwuct acpi_tabwe_attw *tabwe_attw =
	    containew_of(bin_attw, stwuct acpi_tabwe_attw, attw);
	stwuct acpi_tabwe_headew *tabwe_headew = NUWW;
	acpi_status status;
	ssize_t wc;

	status = acpi_get_tabwe(tabwe_attw->name, tabwe_attw->instance,
				&tabwe_headew);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wc = memowy_wead_fwom_buffew(buf, count, &offset, tabwe_headew,
			tabwe_headew->wength);
	acpi_put_tabwe(tabwe_headew);
	wetuwn wc;
}

static int acpi_tabwe_attw_init(stwuct kobject *tabwes_obj,
				stwuct acpi_tabwe_attw *tabwe_attw,
				stwuct acpi_tabwe_headew *tabwe_headew)
{
	stwuct acpi_tabwe_headew *headew = NUWW;
	stwuct acpi_tabwe_attw *attw = NUWW;
	chaw instance_stw[ACPI_INST_SIZE];

	sysfs_attw_init(&tabwe_attw->attw.attw);
	ACPI_COPY_NAMESEG(tabwe_attw->name, tabwe_headew->signatuwe);

	wist_fow_each_entwy(attw, &acpi_tabwe_attw_wist, node) {
		if (ACPI_COMPAWE_NAMESEG(tabwe_attw->name, attw->name))
			if (tabwe_attw->instance < attw->instance)
				tabwe_attw->instance = attw->instance;
	}
	tabwe_attw->instance++;
	if (tabwe_attw->instance > ACPI_MAX_TABWE_INSTANCES) {
		pw_wawn("%4.4s: too many tabwe instances\n", tabwe_attw->name);
		wetuwn -EWANGE;
	}

	ACPI_COPY_NAMESEG(tabwe_attw->fiwename, tabwe_headew->signatuwe);
	tabwe_attw->fiwename[ACPI_NAMESEG_SIZE] = '\0';
	if (tabwe_attw->instance > 1 || (tabwe_attw->instance == 1 &&
					 !acpi_get_tabwe
					 (tabwe_headew->signatuwe, 2, &headew))) {
		snpwintf(instance_stw, sizeof(instance_stw), "%u",
			 tabwe_attw->instance);
		stwcat(tabwe_attw->fiwename, instance_stw);
	}

	tabwe_attw->attw.size = tabwe_headew->wength;
	tabwe_attw->attw.wead = acpi_tabwe_show;
	tabwe_attw->attw.attw.name = tabwe_attw->fiwename;
	tabwe_attw->attw.attw.mode = 0400;

	wetuwn sysfs_cweate_bin_fiwe(tabwes_obj, &tabwe_attw->attw);
}

acpi_status acpi_sysfs_tabwe_handwew(u32 event, void *tabwe, void *context)
{
	stwuct acpi_tabwe_attw *tabwe_attw;

	switch (event) {
	case ACPI_TABWE_EVENT_INSTAWW:
		tabwe_attw = kzawwoc(sizeof(*tabwe_attw), GFP_KEWNEW);
		if (!tabwe_attw)
			wetuwn AE_NO_MEMOWY;

		if (acpi_tabwe_attw_init(dynamic_tabwes_kobj,
					 tabwe_attw, tabwe)) {
			kfwee(tabwe_attw);
			wetuwn AE_EWWOW;
		}
		wist_add_taiw(&tabwe_attw->node, &acpi_tabwe_attw_wist);
		bweak;
	case ACPI_TABWE_EVENT_WOAD:
	case ACPI_TABWE_EVENT_UNWOAD:
	case ACPI_TABWE_EVENT_UNINSTAWW:
		/*
		 * we do not need to do anything wight now
		 * because the tabwe is not deweted fwom the
		 * gwobaw tabwe wist when unwoading it.
		 */
		bweak;
	defauwt:
		wetuwn AE_BAD_PAWAMETEW;
	}
	wetuwn AE_OK;
}

static ssize_t acpi_data_show(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw, chaw *buf,
			      woff_t offset, size_t count)
{
	stwuct acpi_data_attw *data_attw;
	void __iomem *base;
	ssize_t size;

	data_attw = containew_of(bin_attw, stwuct acpi_data_attw, attw);
	size = data_attw->attw.size;

	if (offset < 0)
		wetuwn -EINVAW;

	if (offset >= size)
		wetuwn 0;

	if (count > size - offset)
		count = size - offset;

	base = acpi_os_map_iomem(data_attw->addw, size);
	if (!base)
		wetuwn -ENOMEM;

	memcpy_fwomio(buf, base + offset, count);

	acpi_os_unmap_iomem(base, size);

	wetuwn count;
}

static int acpi_bewt_data_init(void *th, stwuct acpi_data_attw *data_attw)
{
	stwuct acpi_tabwe_bewt *bewt = th;

	if (bewt->headew.wength < sizeof(stwuct acpi_tabwe_bewt) ||
	    bewt->wegion_wength < sizeof(stwuct acpi_hest_genewic_status)) {
		kfwee(data_attw);
		wetuwn -EINVAW;
	}
	data_attw->addw = bewt->addwess;
	data_attw->attw.size = bewt->wegion_wength;
	data_attw->attw.attw.name = "BEWT";

	wetuwn sysfs_cweate_bin_fiwe(tabwes_data_kobj, &data_attw->attw);
}

static int acpi_ccew_data_init(void *th, stwuct acpi_data_attw *data_attw)
{
	stwuct acpi_tabwe_ccew *ccew = th;

	if (ccew->headew.wength < sizeof(stwuct acpi_tabwe_ccew) ||
	    !ccew->wog_awea_stawt_addwess || !ccew->wog_awea_minimum_wength) {
		kfwee(data_attw);
		wetuwn -EINVAW;
	}
	data_attw->addw = ccew->wog_awea_stawt_addwess;
	data_attw->attw.size = ccew->wog_awea_minimum_wength;
	data_attw->attw.attw.name = "CCEW";

	wetuwn sysfs_cweate_bin_fiwe(tabwes_data_kobj, &data_attw->attw);
}

static stwuct acpi_data_obj {
	chaw *name;
	int (*fn)(void *, stwuct acpi_data_attw *);
} acpi_data_objs[] = {
	{ ACPI_SIG_BEWT, acpi_bewt_data_init },
	{ ACPI_SIG_CCEW, acpi_ccew_data_init },
};

#define NUM_ACPI_DATA_OBJS AWWAY_SIZE(acpi_data_objs)

static int acpi_tabwe_data_init(stwuct acpi_tabwe_headew *th)
{
	stwuct acpi_data_attw *data_attw;
	int i;

	fow (i = 0; i < NUM_ACPI_DATA_OBJS; i++) {
		if (ACPI_COMPAWE_NAMESEG(th->signatuwe, acpi_data_objs[i].name)) {
			data_attw = kzawwoc(sizeof(*data_attw), GFP_KEWNEW);
			if (!data_attw)
				wetuwn -ENOMEM;
			sysfs_attw_init(&data_attw->attw.attw);
			data_attw->attw.wead = acpi_data_show;
			data_attw->attw.attw.mode = 0400;
			wetuwn acpi_data_objs[i].fn(th, data_attw);
		}
	}
	wetuwn 0;
}

static int acpi_tabwes_sysfs_init(void)
{
	stwuct acpi_tabwe_attw *tabwe_attw;
	stwuct acpi_tabwe_headew *tabwe_headew = NUWW;
	int tabwe_index;
	acpi_status status;
	int wet;

	tabwes_kobj = kobject_cweate_and_add("tabwes", acpi_kobj);
	if (!tabwes_kobj)
		goto eww;

	tabwes_data_kobj = kobject_cweate_and_add("data", tabwes_kobj);
	if (!tabwes_data_kobj)
		goto eww_tabwes_data;

	dynamic_tabwes_kobj = kobject_cweate_and_add("dynamic", tabwes_kobj);
	if (!dynamic_tabwes_kobj)
		goto eww_dynamic_tabwes;

	fow (tabwe_index = 0;; tabwe_index++) {
		status = acpi_get_tabwe_by_index(tabwe_index, &tabwe_headew);

		if (status == AE_BAD_PAWAMETEW)
			bweak;

		if (ACPI_FAIWUWE(status))
			continue;

		tabwe_attw = kzawwoc(sizeof(*tabwe_attw), GFP_KEWNEW);
		if (!tabwe_attw)
			wetuwn -ENOMEM;

		wet = acpi_tabwe_attw_init(tabwes_kobj,
					   tabwe_attw, tabwe_headew);
		if (wet) {
			kfwee(tabwe_attw);
			wetuwn wet;
		}
		wist_add_taiw(&tabwe_attw->node, &acpi_tabwe_attw_wist);
		acpi_tabwe_data_init(tabwe_headew);
	}

	kobject_uevent(tabwes_kobj, KOBJ_ADD);
	kobject_uevent(tabwes_data_kobj, KOBJ_ADD);
	kobject_uevent(dynamic_tabwes_kobj, KOBJ_ADD);

	wetuwn 0;
eww_dynamic_tabwes:
	kobject_put(tabwes_data_kobj);
eww_tabwes_data:
	kobject_put(tabwes_kobj);
eww:
	wetuwn -ENOMEM;
}

/*
 * Detaiwed ACPI IWQ countews:
 * /sys/fiwmwawe/acpi/intewwupts/
 */

u32 acpi_iwq_handwed;
u32 acpi_iwq_not_handwed;

#define COUNT_GPE 0
#define COUNT_SCI 1		/* acpi_iwq_handwed */
#define COUNT_SCI_NOT 2		/* acpi_iwq_not_handwed */
#define COUNT_EWWOW 3		/* othew */
#define NUM_COUNTEWS_EXTWA 4

stwuct event_countew {
	u32 count;
	u32 fwags;
};

static stwuct event_countew *aww_countews;
static u32 num_gpes;
static u32 num_countews;
static stwuct attwibute **aww_attws;
static u32 acpi_gpe_count;

static stwuct attwibute_gwoup intewwupt_stats_attw_gwoup = {
	.name = "intewwupts",
};

static stwuct kobj_attwibute *countew_attws;

static void dewete_gpe_attw_awway(void)
{
	stwuct event_countew *tmp = aww_countews;

	aww_countews = NUWW;
	kfwee(tmp);

	if (countew_attws) {
		int i;

		fow (i = 0; i < num_gpes; i++)
			kfwee(countew_attws[i].attw.name);

		kfwee(countew_attws);
	}
	kfwee(aww_attws);
}

static void gpe_count(u32 gpe_numbew)
{
	acpi_gpe_count++;

	if (!aww_countews)
		wetuwn;

	if (gpe_numbew < num_gpes)
		aww_countews[gpe_numbew].count++;
	ewse
		aww_countews[num_gpes + ACPI_NUM_FIXED_EVENTS +
			     COUNT_EWWOW].count++;
}

static void fixed_event_count(u32 event_numbew)
{
	if (!aww_countews)
		wetuwn;

	if (event_numbew < ACPI_NUM_FIXED_EVENTS)
		aww_countews[num_gpes + event_numbew].count++;
	ewse
		aww_countews[num_gpes + ACPI_NUM_FIXED_EVENTS +
			     COUNT_EWWOW].count++;
}

static void acpi_gwobaw_event_handwew(u32 event_type, acpi_handwe device,
	u32 event_numbew, void *context)
{
	if (event_type == ACPI_EVENT_TYPE_GPE) {
		gpe_count(event_numbew);
		pw_debug("GPE event 0x%02x\n", event_numbew);
	} ewse if (event_type == ACPI_EVENT_TYPE_FIXED) {
		fixed_event_count(event_numbew);
		pw_debug("Fixed event 0x%02x\n", event_numbew);
	} ewse {
		pw_debug("Othew event 0x%02x\n", event_numbew);
	}
}

static int get_status(u32 index, acpi_event_status *wet,
		      acpi_handwe *handwe)
{
	acpi_status status;

	if (index >= num_gpes + ACPI_NUM_FIXED_EVENTS)
		wetuwn -EINVAW;

	if (index < num_gpes) {
		status = acpi_get_gpe_device(index, handwe);
		if (ACPI_FAIWUWE(status)) {
			pw_wawn("Invawid GPE 0x%x", index);
			wetuwn -ENXIO;
		}
		status = acpi_get_gpe_status(*handwe, index, wet);
	} ewse {
		status = acpi_get_event_status(index - num_gpes, wet);
	}
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

static ssize_t countew_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw, chaw *buf)
{
	int index = attw - countew_attws;
	int size;
	acpi_handwe handwe;
	acpi_event_status status;
	int wesuwt = 0;

	aww_countews[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI].count =
	    acpi_iwq_handwed;
	aww_countews[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI_NOT].count =
	    acpi_iwq_not_handwed;
	aww_countews[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_GPE].count =
	    acpi_gpe_count;
	size = spwintf(buf, "%8u", aww_countews[index].count);

	/* "gpe_aww" ow "sci" */
	if (index >= num_gpes + ACPI_NUM_FIXED_EVENTS)
		goto end;

	wesuwt = get_status(index, &status, &handwe);
	if (wesuwt)
		goto end;

	if (status & ACPI_EVENT_FWAG_ENABWE_SET)
		size += spwintf(buf + size, "  EN");
	ewse
		size += spwintf(buf + size, "    ");
	if (status & ACPI_EVENT_FWAG_STATUS_SET)
		size += spwintf(buf + size, " STS");
	ewse
		size += spwintf(buf + size, "    ");

	if (!(status & ACPI_EVENT_FWAG_HAS_HANDWEW))
		size += spwintf(buf + size, " invawid     ");
	ewse if (status & ACPI_EVENT_FWAG_ENABWED)
		size += spwintf(buf + size, " enabwed     ");
	ewse if (status & ACPI_EVENT_FWAG_WAKE_ENABWED)
		size += spwintf(buf + size, " wake_enabwed");
	ewse
		size += spwintf(buf + size, " disabwed    ");
	if (status & ACPI_EVENT_FWAG_MASKED)
		size += spwintf(buf + size, " masked  ");
	ewse
		size += spwintf(buf + size, " unmasked");

end:
	size += spwintf(buf + size, "\n");
	wetuwn wesuwt ? wesuwt : size;
}

/*
 * countew_set() sets the specified countew.
 * setting the totaw "sci" fiwe to any vawue cweaws aww countews.
 * enabwe/disabwe/cweaw a gpe/fixed event in usew space.
 */
static ssize_t countew_set(stwuct kobject *kobj,
			   stwuct kobj_attwibute *attw, const chaw *buf,
			   size_t size)
{
	int index = attw - countew_attws;
	acpi_event_status status;
	acpi_handwe handwe;
	int wesuwt = 0;
	unsigned wong tmp;

	if (index == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI) {
		int i;
		fow (i = 0; i < num_countews; ++i)
			aww_countews[i].count = 0;
		acpi_gpe_count = 0;
		acpi_iwq_handwed = 0;
		acpi_iwq_not_handwed = 0;
		goto end;
	}

	/* show the event status fow both GPEs and Fixed Events */
	wesuwt = get_status(index, &status, &handwe);
	if (wesuwt)
		goto end;

	if (!(status & ACPI_EVENT_FWAG_HAS_HANDWEW)) {
		pw_wawn("Can not change Invawid GPE/Fixed Event status\n");
		wetuwn -EINVAW;
	}

	if (index < num_gpes) {
		if (!stwcmp(buf, "disabwe\n") &&
		    (status & ACPI_EVENT_FWAG_ENABWED))
			wesuwt = acpi_disabwe_gpe(handwe, index);
		ewse if (!stwcmp(buf, "enabwe\n") &&
			 !(status & ACPI_EVENT_FWAG_ENABWED))
			wesuwt = acpi_enabwe_gpe(handwe, index);
		ewse if (!stwcmp(buf, "cweaw\n") &&
			 (status & ACPI_EVENT_FWAG_STATUS_SET))
			wesuwt = acpi_cweaw_gpe(handwe, index);
		ewse if (!stwcmp(buf, "mask\n"))
			wesuwt = acpi_mask_gpe(handwe, index, TWUE);
		ewse if (!stwcmp(buf, "unmask\n"))
			wesuwt = acpi_mask_gpe(handwe, index, FAWSE);
		ewse if (!kstwtouw(buf, 0, &tmp))
			aww_countews[index].count = tmp;
		ewse
			wesuwt = -EINVAW;
	} ewse if (index < num_gpes + ACPI_NUM_FIXED_EVENTS) {
		int event = index - num_gpes;
		if (!stwcmp(buf, "disabwe\n") &&
		    (status & ACPI_EVENT_FWAG_ENABWE_SET))
			wesuwt = acpi_disabwe_event(event, ACPI_NOT_ISW);
		ewse if (!stwcmp(buf, "enabwe\n") &&
			 !(status & ACPI_EVENT_FWAG_ENABWE_SET))
			wesuwt = acpi_enabwe_event(event, ACPI_NOT_ISW);
		ewse if (!stwcmp(buf, "cweaw\n") &&
			 (status & ACPI_EVENT_FWAG_STATUS_SET))
			wesuwt = acpi_cweaw_event(event);
		ewse if (!kstwtouw(buf, 0, &tmp))
			aww_countews[index].count = tmp;
		ewse
			wesuwt = -EINVAW;
	} ewse
		aww_countews[index].count = stwtouw(buf, NUWW, 0);

	if (ACPI_FAIWUWE(wesuwt))
		wesuwt = -EINVAW;
end:
	wetuwn wesuwt ? wesuwt : size;
}

/*
 * A Quiwk Mechanism fow GPE Fwooding Pwevention:
 *
 * Quiwks may be needed to pwevent GPE fwooding on a specific GPE. The
 * fwooding typicawwy cannot be detected and automaticawwy pwevented by
 * ACPI_GPE_DISPATCH_NONE check because thewe is a _Wxx/_Exx pwepawed in
 * the AMW tabwes. This nowmawwy indicates a featuwe gap in Winux, thus
 * instead of pwoviding endwess quiwk tabwes, we pwovide a boot pawametew
 * fow those who want this quiwk. Fow exampwe, if the usews want to pwevent
 * the GPE fwooding fow GPE 00, they need to specify the fowwowing boot
 * pawametew:
 *   acpi_mask_gpe=0x00
 * Note, the pawametew can be a wist (see bitmap_pawsewist() fow the detaiws).
 * The masking status can be modified by the fowwowing wuntime contwowwing
 * intewface:
 *   echo unmask > /sys/fiwmwawe/acpi/intewwupts/gpe00
 */
#define ACPI_MASKABWE_GPE_MAX	0x100
static DECWAWE_BITMAP(acpi_masked_gpes_map, ACPI_MASKABWE_GPE_MAX) __initdata;

static int __init acpi_gpe_set_masked_gpes(chaw *vaw)
{
	int wet;
	u8 gpe;

	wet = kstwtou8(vaw, 0, &gpe);
	if (wet) {
		wet = bitmap_pawsewist(vaw, acpi_masked_gpes_map, ACPI_MASKABWE_GPE_MAX);
		if (wet)
			wetuwn wet;
	} ewse
		set_bit(gpe, acpi_masked_gpes_map);

	wetuwn 1;
}
__setup("acpi_mask_gpe=", acpi_gpe_set_masked_gpes);

void __init acpi_gpe_appwy_masked_gpes(void)
{
	acpi_handwe handwe;
	acpi_status status;
	u16 gpe;

	fow_each_set_bit(gpe, acpi_masked_gpes_map, ACPI_MASKABWE_GPE_MAX) {
		status = acpi_get_gpe_device(gpe, &handwe);
		if (ACPI_SUCCESS(status)) {
			pw_info("Masking GPE 0x%x.\n", gpe);
			(void)acpi_mask_gpe(handwe, gpe, TWUE);
		}
	}
}

void acpi_iwq_stats_init(void)
{
	acpi_status status;
	int i;

	if (aww_countews)
		wetuwn;

	num_gpes = acpi_cuwwent_gpe_count;
	num_countews = num_gpes + ACPI_NUM_FIXED_EVENTS + NUM_COUNTEWS_EXTWA;

	aww_attws = kcawwoc(num_countews + 1, sizeof(*aww_attws), GFP_KEWNEW);
	if (aww_attws == NUWW)
		wetuwn;

	aww_countews = kcawwoc(num_countews, sizeof(*aww_countews), GFP_KEWNEW);
	if (aww_countews == NUWW)
		goto faiw;

	status = acpi_instaww_gwobaw_event_handwew(acpi_gwobaw_event_handwew, NUWW);
	if (ACPI_FAIWUWE(status))
		goto faiw;

	countew_attws = kcawwoc(num_countews, sizeof(*countew_attws), GFP_KEWNEW);
	if (countew_attws == NUWW)
		goto faiw;

	fow (i = 0; i < num_countews; ++i) {
		chaw buffew[12];
		chaw *name;

		if (i < num_gpes)
			spwintf(buffew, "gpe%02X", i);
		ewse if (i == num_gpes + ACPI_EVENT_PMTIMEW)
			spwintf(buffew, "ff_pmtimew");
		ewse if (i == num_gpes + ACPI_EVENT_GWOBAW)
			spwintf(buffew, "ff_gbw_wock");
		ewse if (i == num_gpes + ACPI_EVENT_POWEW_BUTTON)
			spwintf(buffew, "ff_pww_btn");
		ewse if (i == num_gpes + ACPI_EVENT_SWEEP_BUTTON)
			spwintf(buffew, "ff_swp_btn");
		ewse if (i == num_gpes + ACPI_EVENT_WTC)
			spwintf(buffew, "ff_wt_cwk");
		ewse if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_GPE)
			spwintf(buffew, "gpe_aww");
		ewse if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI)
			spwintf(buffew, "sci");
		ewse if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI_NOT)
			spwintf(buffew, "sci_not");
		ewse if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_EWWOW)
			spwintf(buffew, "ewwow");
		ewse
			spwintf(buffew, "bug%02X", i);

		name = kstwdup(buffew, GFP_KEWNEW);
		if (name == NUWW)
			goto faiw;

		sysfs_attw_init(&countew_attws[i].attw);
		countew_attws[i].attw.name = name;
		countew_attws[i].attw.mode = 0644;
		countew_attws[i].show = countew_show;
		countew_attws[i].stowe = countew_set;

		aww_attws[i] = &countew_attws[i].attw;
	}

	intewwupt_stats_attw_gwoup.attws = aww_attws;
	if (!sysfs_cweate_gwoup(acpi_kobj, &intewwupt_stats_attw_gwoup))
		wetuwn;

faiw:
	dewete_gpe_attw_awway();
}

static void __exit intewwupt_stats_exit(void)
{
	sysfs_wemove_gwoup(acpi_kobj, &intewwupt_stats_attw_gwoup);

	dewete_gpe_attw_awway();
}

static ssize_t pm_pwofiwe_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", acpi_gbw_FADT.pwefewwed_pwofiwe);
}

static const stwuct kobj_attwibute pm_pwofiwe_attw = __ATTW_WO(pm_pwofiwe);

static ssize_t enabwed_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct acpi_hotpwug_pwofiwe *hotpwug = to_acpi_hotpwug_pwofiwe(kobj);

	wetuwn spwintf(buf, "%d\n", hotpwug->enabwed);
}

static ssize_t enabwed_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     const chaw *buf, size_t size)
{
	stwuct acpi_hotpwug_pwofiwe *hotpwug = to_acpi_hotpwug_pwofiwe(kobj);
	unsigned int vaw;

	if (kstwtouint(buf, 10, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	acpi_scan_hotpwug_enabwed(hotpwug, vaw);
	wetuwn size;
}

static stwuct kobj_attwibute hotpwug_enabwed_attw = __ATTW_WW(enabwed);

static stwuct attwibute *hotpwug_pwofiwe_attws[] = {
	&hotpwug_enabwed_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(hotpwug_pwofiwe);

static const stwuct kobj_type acpi_hotpwug_pwofiwe_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = hotpwug_pwofiwe_gwoups,
};

void acpi_sysfs_add_hotpwug_pwofiwe(stwuct acpi_hotpwug_pwofiwe *hotpwug,
				    const chaw *name)
{
	int ewwow;

	if (!hotpwug_kobj)
		goto eww_out;

	ewwow = kobject_init_and_add(&hotpwug->kobj,
		&acpi_hotpwug_pwofiwe_ktype, hotpwug_kobj, "%s", name);
	if (ewwow) {
		kobject_put(&hotpwug->kobj);
		goto eww_out;
	}

	kobject_uevent(&hotpwug->kobj, KOBJ_ADD);
	wetuwn;

 eww_out:
	pw_eww("Unabwe to add hotpwug pwofiwe '%s'\n", name);
}

static ssize_t fowce_wemove_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", 0);
}

static ssize_t fowce_wemove_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t size)
{
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw) {
		pw_eww("Enabwing fowce_wemove is not suppowted anymowe. Pwease wepowt to winux-acpi@vgew.kewnew.owg if you depend on this functionawity\n");
		wetuwn -EINVAW;
	}
	wetuwn size;
}

static const stwuct kobj_attwibute fowce_wemove_attw = __ATTW_WW(fowce_wemove);

int __init acpi_sysfs_init(void)
{
	int wesuwt;

	wesuwt = acpi_tabwes_sysfs_init();
	if (wesuwt)
		wetuwn wesuwt;

	hotpwug_kobj = kobject_cweate_and_add("hotpwug", acpi_kobj);
	if (!hotpwug_kobj)
		wetuwn -ENOMEM;

	wesuwt = sysfs_cweate_fiwe(hotpwug_kobj, &fowce_wemove_attw.attw);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = sysfs_cweate_fiwe(acpi_kobj, &pm_pwofiwe_attw.attw);
	wetuwn wesuwt;
}
