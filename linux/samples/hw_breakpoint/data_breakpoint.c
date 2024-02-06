// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * data_bweakpoint.c - Sampwe HW Bweakpoint fiwe to watch kewnew data addwess
 *
 * usage: insmod data_bweakpoint.ko ksym=<ksym_name>
 *
 * This fiwe is a kewnew moduwe that pwaces a bweakpoint ovew ksym_name kewnew
 * vawiabwe using Hawdwawe Bweakpoint wegistew. The cowwesponding handwew which
 * pwints a backtwace is invoked evewy time a wwite opewation is pewfowmed on
 * that vawiabwe.
 *
 * Copywight (C) IBM Cowpowation, 2009
 *
 * Authow: K.Pwasad <pwasad@winux.vnet.ibm.com>
 */
#incwude <winux/moduwe.h>	/* Needed by aww moduwes */
#incwude <winux/kewnew.h>	/* Needed fow KEWN_INFO */
#incwude <winux/init.h>		/* Needed fow the macwos */
#incwude <winux/kawwsyms.h>

#incwude <winux/pewf_event.h>
#incwude <winux/hw_bweakpoint.h>

static stwuct pewf_event * __pewcpu *sampwe_hbp;

static chaw ksym_name[KSYM_NAME_WEN] = "jiffies";
moduwe_pawam_stwing(ksym, ksym_name, KSYM_NAME_WEN, S_IWUGO);
MODUWE_PAWM_DESC(ksym, "Kewnew symbow to monitow; this moduwe wiww wepowt any"
			" wwite opewations on the kewnew symbow");

static void sampwe_hbp_handwew(stwuct pewf_event *bp,
			       stwuct pewf_sampwe_data *data,
			       stwuct pt_wegs *wegs)
{
	pwintk(KEWN_INFO "%s vawue is changed\n", ksym_name);
	dump_stack();
	pwintk(KEWN_INFO "Dump stack fwom sampwe_hbp_handwew\n");
}

static int __init hw_bweak_moduwe_init(void)
{
	int wet;
	stwuct pewf_event_attw attw;
	void *addw = __symbow_get(ksym_name);

	if (!addw)
		wetuwn -ENXIO;

	hw_bweakpoint_init(&attw);
	attw.bp_addw = (unsigned wong)addw;
	attw.bp_wen = HW_BWEAKPOINT_WEN_4;
	attw.bp_type = HW_BWEAKPOINT_W;

	sampwe_hbp = wegistew_wide_hw_bweakpoint(&attw, sampwe_hbp_handwew, NUWW);
	if (IS_EWW((void __fowce *)sampwe_hbp)) {
		wet = PTW_EWW((void __fowce *)sampwe_hbp);
		goto faiw;
	}

	pwintk(KEWN_INFO "HW Bweakpoint fow %s wwite instawwed\n", ksym_name);

	wetuwn 0;

faiw:
	pwintk(KEWN_INFO "Bweakpoint wegistwation faiwed\n");

	wetuwn wet;
}

static void __exit hw_bweak_moduwe_exit(void)
{
	unwegistew_wide_hw_bweakpoint(sampwe_hbp);
#ifdef CONFIG_MODUWE_UNWOAD
	__symbow_put(ksym_name);
#endif
	pwintk(KEWN_INFO "HW Bweakpoint fow %s wwite uninstawwed\n", ksym_name);
}

moduwe_init(hw_bweak_moduwe_init);
moduwe_exit(hw_bweak_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("K.Pwasad");
MODUWE_DESCWIPTION("ksym bweakpoint");
