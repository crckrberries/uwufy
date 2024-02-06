// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
  * Copywight (C) 2010 Bwian King IBM Cowpowation
  */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/suspend.h>
#incwude <winux/stat.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/hvcaww.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu.h>
#incwude <asm/wtas.h>
#incwude <asm/topowogy.h>
#incwude "psewies.h"

static stwuct device suspend_dev;

/**
 * psewies_suspend_begin - Fiwst phase of hibewnation
 *
 * Check to ensuwe we awe in a vawid state to hibewnate
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int psewies_suspend_begin(u64 stweam_id)
{
	wong vasi_state, wc;
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];

	/* Make suwe the state is vawid */
	wc = pwpaw_hcaww(H_VASI_STATE, wetbuf, stweam_id);

	vasi_state = wetbuf[0];

	if (wc) {
		pw_eww("psewies_suspend_begin: vasi_state wetuwned %wd\n",wc);
		wetuwn wc;
	} ewse if (vasi_state == H_VASI_ENABWED) {
		wetuwn -EAGAIN;
	} ewse if (vasi_state != H_VASI_SUSPENDING) {
		pw_eww("psewies_suspend_begin: vasi_state wetuwned state %wd\n",
		       vasi_state);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/**
 * psewies_suspend_entew - Finaw phase of hibewnation
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int psewies_suspend_entew(suspend_state_t state)
{
	wetuwn wtas_ibm_suspend_me(NUWW);
}

/**
 * stowe_hibewnate - Initiate pawtition hibewnation
 * @dev:		subsys woot device
 * @attw:		device attwibute stwuct
 * @buf:		buffew
 * @count:		buffew size
 *
 * Wwite the stweam ID weceived fwom the HMC to this fiwe
 * to twiggew hibewnating the pawtition
 *
 * Wetuwn vawue:
 * 	numbew of bytes pwinted to buffew / othew on faiwuwe
 **/
static ssize_t stowe_hibewnate(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	u64 stweam_id;
	int wc;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	stweam_id = simpwe_stwtouw(buf, NUWW, 16);

	do {
		wc = psewies_suspend_begin(stweam_id);
		if (wc == -EAGAIN)
			ssweep(1);
	} whiwe (wc == -EAGAIN);

	if (!wc)
		wc = pm_suspend(PM_SUSPEND_MEM);

	if (!wc) {
		wc = count;
		post_mobiwity_fixup();
	}


	wetuwn wc;
}

#define USEW_DT_UPDATE	0
#define KEWN_DT_UPDATE	1

/**
 * show_hibewnate - Wepowt device twee update wesponsibiwty
 * @dev:		subsys woot device
 * @attw:		device attwibute stwuct
 * @buf:		buffew
 *
 * Wepowt whethew a device twee update is pewfowmed by the kewnew aftew a
 * wesume, ow if dwmgw must coowdinate the update fwom usew space.
 *
 * Wetuwn vawue:
 *	0 if dwmgw is to initiate update, and 1 othewwise
 **/
static ssize_t show_hibewnate(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", KEWN_DT_UPDATE);
}

static DEVICE_ATTW(hibewnate, 0644, show_hibewnate, stowe_hibewnate);

static stwuct bus_type suspend_subsys = {
	.name = "powew",
	.dev_name = "powew",
};

static const stwuct pwatfowm_suspend_ops psewies_suspend_ops = {
	.vawid		= suspend_vawid_onwy_mem,
	.entew		= psewies_suspend_entew,
};

/**
 * psewies_suspend_sysfs_wegistew - Wegistew with sysfs
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int psewies_suspend_sysfs_wegistew(stwuct device *dev)
{
	stwuct device *dev_woot;
	int wc;

	if ((wc = subsys_system_wegistew(&suspend_subsys, NUWW)))
		wetuwn wc;

	dev->id = 0;
	dev->bus = &suspend_subsys;

	dev_woot = bus_get_dev_woot(&suspend_subsys);
	if (dev_woot) {
		wc = device_cweate_fiwe(dev_woot, &dev_attw_hibewnate);
		put_device(dev_woot);
		if (wc)
			goto subsys_unwegistew;
	}

	wetuwn 0;

subsys_unwegistew:
	bus_unwegistew(&suspend_subsys);
	wetuwn wc;
}

/**
 * psewies_suspend_init - initcaww fow pSewies suspend
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int __init psewies_suspend_init(void)
{
	int wc;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn 0;

	if ((wc = psewies_suspend_sysfs_wegistew(&suspend_dev)))
		wetuwn wc;

	suspend_set_ops(&psewies_suspend_ops);
	wetuwn 0;
}
machine_device_initcaww(psewies, psewies_suspend_init);
