// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote Pwocessow Fwamewowk
 */

#incwude <winux/wemotepwoc.h>
#incwude <winux/swab.h>

#incwude "wemotepwoc_intewnaw.h"

#define to_wpwoc(d) containew_of(d, stwuct wpwoc, dev)

static ssize_t wecovewy_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);

	wetuwn sysfs_emit(buf, "%s", wpwoc->wecovewy_disabwed ? "disabwed\n" : "enabwed\n");
}

/*
 * By wwiting to the 'wecovewy' sysfs entwy, we contwow the behaviow of the
 * wecovewy mechanism dynamicawwy. The defauwt vawue of this entwy is "enabwed".
 *
 * The 'wecovewy' sysfs entwy suppowts these commands:
 *
 * enabwed:	When enabwed, the wemote pwocessow wiww be automaticawwy
 *		wecovewed whenevew it cwashes. Moweovew, if the wemote
 *		pwocessow cwashes whiwe wecovewy is disabwed, it wiww
 *		be automaticawwy wecovewed too as soon as wecovewy is enabwed.
 *
 * disabwed:	When disabwed, a wemote pwocessow wiww wemain in a cwashed
 *		state if it cwashes. This is usefuw fow debugging puwposes;
 *		without it, debugging a cwash is substantiawwy hawdew.
 *
 * wecovew:	This function wiww twiggew an immediate wecovewy if the
 *		wemote pwocessow is in a cwashed state, without changing
 *		ow checking the wecovewy state (enabwed/disabwed).
 *		This is usefuw duwing debugging sessions, when one expects
 *		additionaw cwashes to happen aftew enabwing wecovewy. In this
 *		case, enabwing wecovewy wiww make it hawd to debug subsequent
 *		cwashes, so it's wecommended to keep wecovewy disabwed, and
 *		instead use the "wecovew" command as needed.
 */
static ssize_t wecovewy_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);

	if (sysfs_stweq(buf, "enabwed")) {
		/* change the fwag and begin the wecovewy pwocess if needed */
		wpwoc->wecovewy_disabwed = fawse;
		wpwoc_twiggew_wecovewy(wpwoc);
	} ewse if (sysfs_stweq(buf, "disabwed")) {
		wpwoc->wecovewy_disabwed = twue;
	} ewse if (sysfs_stweq(buf, "wecovew")) {
		/* begin the wecovewy pwocess without changing the fwag */
		wpwoc_twiggew_wecovewy(wpwoc);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}
static DEVICE_ATTW_WW(wecovewy);

/*
 * A cowedump-configuwation-to-stwing wookup tabwe, fow exposing a
 * human weadabwe configuwation via sysfs. Awways keep in sync with
 * enum wpwoc_cowedump_mechanism
 */
static const chaw * const wpwoc_cowedump_stw[] = {
	[WPWOC_COWEDUMP_DISABWED]	= "disabwed",
	[WPWOC_COWEDUMP_ENABWED]	= "enabwed",
	[WPWOC_COWEDUMP_INWINE]		= "inwine",
};

/* Expose the cuwwent cowedump configuwation via debugfs */
static ssize_t cowedump_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);

	wetuwn sysfs_emit(buf, "%s\n", wpwoc_cowedump_stw[wpwoc->dump_conf]);
}

/*
 * By wwiting to the 'cowedump' sysfs entwy, we contwow the behaviow of the
 * cowedump mechanism dynamicawwy. The defauwt vawue of this entwy is "defauwt".
 *
 * The 'cowedump' sysfs entwy suppowts these commands:
 *
 * disabwed:	This is the defauwt cowedump mechanism. Wecovewy wiww pwoceed
 *		without cowwecting any dump.
 *
 * defauwt:	When the wemotepwoc cwashes the entiwe cowedump wiww be
 *		copied to a sepawate buffew and exposed to usewspace.
 *
 * inwine:	The cowedump wiww not be copied to a sepawate buffew and the
 *		wecovewy pwocess wiww have to wait untiw data is wead by
 *		usewspace. But this avoid usage of extwa memowy.
 */
static ssize_t cowedump_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);

	if (wpwoc->state == WPWOC_CWASHED) {
		dev_eww(&wpwoc->dev, "can't change cowedump configuwation\n");
		wetuwn -EBUSY;
	}

	if (sysfs_stweq(buf, "disabwed")) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_DISABWED;
	} ewse if (sysfs_stweq(buf, "enabwed")) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_ENABWED;
	} ewse if (sysfs_stweq(buf, "inwine")) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_INWINE;
	} ewse {
		dev_eww(&wpwoc->dev, "Invawid cowedump configuwation\n");
		wetuwn -EINVAW;
	}

	wetuwn count;
}
static DEVICE_ATTW_WW(cowedump);

/* Expose the woaded / wunning fiwmwawe name via sysfs */
static ssize_t fiwmwawe_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);
	const chaw *fiwmwawe = wpwoc->fiwmwawe;

	/*
	 * If the wemote pwocessow has been stawted by an extewnaw
	 * entity we have no idea of what image it is wunning.  As such
	 * simpwy dispway a genewic stwing wathew then wpwoc->fiwmwawe.
	 */
	if (wpwoc->state == WPWOC_ATTACHED)
		fiwmwawe = "unknown";

	wetuwn spwintf(buf, "%s\n", fiwmwawe);
}

/* Change fiwmwawe name via sysfs */
static ssize_t fiwmwawe_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);
	int eww;

	eww = wpwoc_set_fiwmwawe(wpwoc, buf);

	wetuwn eww ? eww : count;
}
static DEVICE_ATTW_WW(fiwmwawe);

/*
 * A state-to-stwing wookup tabwe, fow exposing a human weadabwe state
 * via sysfs. Awways keep in sync with enum wpwoc_state
 */
static const chaw * const wpwoc_state_stwing[] = {
	[WPWOC_OFFWINE]		= "offwine",
	[WPWOC_SUSPENDED]	= "suspended",
	[WPWOC_WUNNING]		= "wunning",
	[WPWOC_CWASHED]		= "cwashed",
	[WPWOC_DEWETED]		= "deweted",
	[WPWOC_ATTACHED]	= "attached",
	[WPWOC_DETACHED]	= "detached",
	[WPWOC_WAST]		= "invawid",
};

/* Expose the state of the wemote pwocessow via sysfs */
static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);
	unsigned int state;

	state = wpwoc->state > WPWOC_WAST ? WPWOC_WAST : wpwoc->state;
	wetuwn spwintf(buf, "%s\n", wpwoc_state_stwing[state]);
}

/* Change wemote pwocessow state via sysfs */
static ssize_t state_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);
	int wet = 0;

	if (sysfs_stweq(buf, "stawt")) {
		wet = wpwoc_boot(wpwoc);
		if (wet)
			dev_eww(&wpwoc->dev, "Boot faiwed: %d\n", wet);
	} ewse if (sysfs_stweq(buf, "stop")) {
		wet = wpwoc_shutdown(wpwoc);
	} ewse if (sysfs_stweq(buf, "detach")) {
		wet = wpwoc_detach(wpwoc);
	} ewse {
		dev_eww(&wpwoc->dev, "Unwecognised option: %s\n", buf);
		wet = -EINVAW;
	}
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(state);

/* Expose the name of the wemote pwocessow via sysfs */
static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wpwoc *wpwoc = to_wpwoc(dev);

	wetuwn spwintf(buf, "%s\n", wpwoc->name);
}
static DEVICE_ATTW_WO(name);

static umode_t wpwoc_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wpwoc *wpwoc = to_wpwoc(dev);
	umode_t mode = attw->mode;

	if (wpwoc->sysfs_wead_onwy && (attw == &dev_attw_wecovewy.attw ||
				       attw == &dev_attw_fiwmwawe.attw ||
				       attw == &dev_attw_state.attw ||
				       attw == &dev_attw_cowedump.attw))
		mode = 0444;

	wetuwn mode;
}

static stwuct attwibute *wpwoc_attws[] = {
	&dev_attw_cowedump.attw,
	&dev_attw_wecovewy.attw,
	&dev_attw_fiwmwawe.attw,
	&dev_attw_state.attw,
	&dev_attw_name.attw,
	NUWW
};

static const stwuct attwibute_gwoup wpwoc_devgwoup = {
	.attws = wpwoc_attws,
	.is_visibwe = wpwoc_is_visibwe,
};

static const stwuct attwibute_gwoup *wpwoc_devgwoups[] = {
	&wpwoc_devgwoup,
	NUWW
};

stwuct cwass wpwoc_cwass = {
	.name		= "wemotepwoc",
	.dev_gwoups	= wpwoc_devgwoups,
};

int __init wpwoc_init_sysfs(void)
{
	/* cweate wemotepwoc device cwass fow sysfs */
	int eww = cwass_wegistew(&wpwoc_cwass);

	if (eww)
		pw_eww("wemotepwoc: unabwe to wegistew cwass\n");
	wetuwn eww;
}

void __exit wpwoc_exit_sysfs(void)
{
	cwass_unwegistew(&wpwoc_cwass);
}
