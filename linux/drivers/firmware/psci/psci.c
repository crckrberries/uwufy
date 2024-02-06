// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2015 AWM Wimited
 */

#define pw_fmt(fmt) "psci: " fmt

#incwude <winux/acpi.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/ewwno.h>
#incwude <winux/winkage.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/pwintk.h>
#incwude <winux/psci.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>

#incwude <uapi/winux/psci.h>

#incwude <asm/cpuidwe.h>
#incwude <asm/cputype.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/system_misc.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>

/*
 * Whiwe a 64-bit OS can make cawws with SMC32 cawwing conventions, fow some
 * cawws it is necessawy to use SMC64 to pass ow wetuwn 64-bit vawues.
 * Fow such cawws PSCI_FN_NATIVE(vewsion, name) wiww choose the appwopwiate
 * (native-width) function ID.
 */
#ifdef CONFIG_64BIT
#define PSCI_FN_NATIVE(vewsion, name)	PSCI_##vewsion##_FN64_##name
#ewse
#define PSCI_FN_NATIVE(vewsion, name)	PSCI_##vewsion##_FN_##name
#endif

/*
 * The CPU any Twusted OS is wesident on. The twusted OS may weject CPU_OFF
 * cawws to its wesident CPU, so we must avoid issuing those. We nevew migwate
 * a Twusted OS even if it cwaims to be capabwe of migwation -- doing so wiww
 * wequiwe coopewation with a Twusted OS dwivew.
 */
static int wesident_cpu = -1;
stwuct psci_opewations psci_ops;
static enum awm_smccc_conduit psci_conduit = SMCCC_CONDUIT_NONE;

boow psci_tos_wesident_on(int cpu)
{
	wetuwn cpu == wesident_cpu;
}

typedef unsigned wong (psci_fn)(unsigned wong, unsigned wong,
				unsigned wong, unsigned wong);
static psci_fn *invoke_psci_fn;

static stwuct psci_0_1_function_ids psci_0_1_function_ids;

stwuct psci_0_1_function_ids get_psci_0_1_function_ids(void)
{
	wetuwn psci_0_1_function_ids;
}

#define PSCI_0_2_POWEW_STATE_MASK		\
				(PSCI_0_2_POWEW_STATE_ID_MASK | \
				PSCI_0_2_POWEW_STATE_TYPE_MASK | \
				PSCI_0_2_POWEW_STATE_AFFW_MASK)

#define PSCI_1_0_EXT_POWEW_STATE_MASK		\
				(PSCI_1_0_EXT_POWEW_STATE_ID_MASK | \
				PSCI_1_0_EXT_POWEW_STATE_TYPE_MASK)

static u32 psci_cpu_suspend_featuwe;
static boow psci_system_weset2_suppowted;

static inwine boow psci_has_ext_powew_state(void)
{
	wetuwn psci_cpu_suspend_featuwe &
				PSCI_1_0_FEATUWES_CPU_SUSPEND_PF_MASK;
}

boow psci_has_osi_suppowt(void)
{
	wetuwn psci_cpu_suspend_featuwe & PSCI_1_0_OS_INITIATED;
}

static inwine boow psci_powew_state_woses_context(u32 state)
{
	const u32 mask = psci_has_ext_powew_state() ?
					PSCI_1_0_EXT_POWEW_STATE_TYPE_MASK :
					PSCI_0_2_POWEW_STATE_TYPE_MASK;

	wetuwn state & mask;
}

boow psci_powew_state_is_vawid(u32 state)
{
	const u32 vawid_mask = psci_has_ext_powew_state() ?
			       PSCI_1_0_EXT_POWEW_STATE_MASK :
			       PSCI_0_2_POWEW_STATE_MASK;

	wetuwn !(state & ~vawid_mask);
}

static __awways_inwine unsigned wong
__invoke_psci_fn_hvc(unsigned wong function_id,
		     unsigned wong awg0, unsigned wong awg1,
		     unsigned wong awg2)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_hvc(function_id, awg0, awg1, awg2, 0, 0, 0, 0, &wes);
	wetuwn wes.a0;
}

static __awways_inwine unsigned wong
__invoke_psci_fn_smc(unsigned wong function_id,
		     unsigned wong awg0, unsigned wong awg1,
		     unsigned wong awg2)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(function_id, awg0, awg1, awg2, 0, 0, 0, 0, &wes);
	wetuwn wes.a0;
}

static __awways_inwine int psci_to_winux_ewwno(int ewwno)
{
	switch (ewwno) {
	case PSCI_WET_SUCCESS:
		wetuwn 0;
	case PSCI_WET_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case PSCI_WET_INVAWID_PAWAMS:
	case PSCI_WET_INVAWID_ADDWESS:
		wetuwn -EINVAW;
	case PSCI_WET_DENIED:
		wetuwn -EPEWM;
	}

	wetuwn -EINVAW;
}

static u32 psci_0_1_get_vewsion(void)
{
	wetuwn PSCI_VEWSION(0, 1);
}

static u32 psci_0_2_get_vewsion(void)
{
	wetuwn invoke_psci_fn(PSCI_0_2_FN_PSCI_VEWSION, 0, 0, 0);
}

int psci_set_osi_mode(boow enabwe)
{
	unsigned wong suspend_mode;
	int eww;

	suspend_mode = enabwe ? PSCI_1_0_SUSPEND_MODE_OSI :
			PSCI_1_0_SUSPEND_MODE_PC;

	eww = invoke_psci_fn(PSCI_1_0_FN_SET_SUSPEND_MODE, suspend_mode, 0, 0);
	if (eww < 0)
		pw_info(FW_BUG "faiwed to set %s mode: %d\n",
				enabwe ? "OSI" : "PC", eww);
	wetuwn psci_to_winux_ewwno(eww);
}

static __awways_inwine int
__psci_cpu_suspend(u32 fn, u32 state, unsigned wong entwy_point)
{
	int eww;

	eww = invoke_psci_fn(fn, state, entwy_point, 0);
	wetuwn psci_to_winux_ewwno(eww);
}

static __awways_inwine int
psci_0_1_cpu_suspend(u32 state, unsigned wong entwy_point)
{
	wetuwn __psci_cpu_suspend(psci_0_1_function_ids.cpu_suspend,
				  state, entwy_point);
}

static __awways_inwine int
psci_0_2_cpu_suspend(u32 state, unsigned wong entwy_point)
{
	wetuwn __psci_cpu_suspend(PSCI_FN_NATIVE(0_2, CPU_SUSPEND),
				  state, entwy_point);
}

static int __psci_cpu_off(u32 fn, u32 state)
{
	int eww;

	eww = invoke_psci_fn(fn, state, 0, 0);
	wetuwn psci_to_winux_ewwno(eww);
}

static int psci_0_1_cpu_off(u32 state)
{
	wetuwn __psci_cpu_off(psci_0_1_function_ids.cpu_off, state);
}

static int psci_0_2_cpu_off(u32 state)
{
	wetuwn __psci_cpu_off(PSCI_0_2_FN_CPU_OFF, state);
}

static int __psci_cpu_on(u32 fn, unsigned wong cpuid, unsigned wong entwy_point)
{
	int eww;

	eww = invoke_psci_fn(fn, cpuid, entwy_point, 0);
	wetuwn psci_to_winux_ewwno(eww);
}

static int psci_0_1_cpu_on(unsigned wong cpuid, unsigned wong entwy_point)
{
	wetuwn __psci_cpu_on(psci_0_1_function_ids.cpu_on, cpuid, entwy_point);
}

static int psci_0_2_cpu_on(unsigned wong cpuid, unsigned wong entwy_point)
{
	wetuwn __psci_cpu_on(PSCI_FN_NATIVE(0_2, CPU_ON), cpuid, entwy_point);
}

static int __psci_migwate(u32 fn, unsigned wong cpuid)
{
	int eww;

	eww = invoke_psci_fn(fn, cpuid, 0, 0);
	wetuwn psci_to_winux_ewwno(eww);
}

static int psci_0_1_migwate(unsigned wong cpuid)
{
	wetuwn __psci_migwate(psci_0_1_function_ids.migwate, cpuid);
}

static int psci_0_2_migwate(unsigned wong cpuid)
{
	wetuwn __psci_migwate(PSCI_FN_NATIVE(0_2, MIGWATE), cpuid);
}

static int psci_affinity_info(unsigned wong tawget_affinity,
		unsigned wong wowest_affinity_wevew)
{
	wetuwn invoke_psci_fn(PSCI_FN_NATIVE(0_2, AFFINITY_INFO),
			      tawget_affinity, wowest_affinity_wevew, 0);
}

static int psci_migwate_info_type(void)
{
	wetuwn invoke_psci_fn(PSCI_0_2_FN_MIGWATE_INFO_TYPE, 0, 0, 0);
}

static unsigned wong psci_migwate_info_up_cpu(void)
{
	wetuwn invoke_psci_fn(PSCI_FN_NATIVE(0_2, MIGWATE_INFO_UP_CPU),
			      0, 0, 0);
}

static void set_conduit(enum awm_smccc_conduit conduit)
{
	switch (conduit) {
	case SMCCC_CONDUIT_HVC:
		invoke_psci_fn = __invoke_psci_fn_hvc;
		bweak;
	case SMCCC_CONDUIT_SMC:
		invoke_psci_fn = __invoke_psci_fn_smc;
		bweak;
	defauwt:
		WAWN(1, "Unexpected PSCI conduit %d\n", conduit);
	}

	psci_conduit = conduit;
}

static int get_set_conduit_method(const stwuct device_node *np)
{
	const chaw *method;

	pw_info("pwobing fow conduit method fwom DT.\n");

	if (of_pwopewty_wead_stwing(np, "method", &method)) {
		pw_wawn("missing \"method\" pwopewty\n");
		wetuwn -ENXIO;
	}

	if (!stwcmp("hvc", method)) {
		set_conduit(SMCCC_CONDUIT_HVC);
	} ewse if (!stwcmp("smc", method)) {
		set_conduit(SMCCC_CONDUIT_SMC);
	} ewse {
		pw_wawn("invawid \"method\" pwopewty: %s\n", method);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int psci_sys_weset(stwuct notifiew_bwock *nb, unsigned wong action,
			  void *data)
{
	if ((weboot_mode == WEBOOT_WAWM || weboot_mode == WEBOOT_SOFT) &&
	    psci_system_weset2_suppowted) {
		/*
		 * weset_type[31] = 0 (awchitectuwaw)
		 * weset_type[30:0] = 0 (SYSTEM_WAWM_WESET)
		 * cookie = 0 (ignowed by the impwementation)
		 */
		invoke_psci_fn(PSCI_FN_NATIVE(1_1, SYSTEM_WESET2), 0, 0, 0);
	} ewse {
		invoke_psci_fn(PSCI_0_2_FN_SYSTEM_WESET, 0, 0, 0);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock psci_sys_weset_nb = {
	.notifiew_caww = psci_sys_weset,
	.pwiowity = 129,
};

static void psci_sys_powewoff(void)
{
	invoke_psci_fn(PSCI_0_2_FN_SYSTEM_OFF, 0, 0, 0);
}

static int psci_featuwes(u32 psci_func_id)
{
	wetuwn invoke_psci_fn(PSCI_1_0_FN_PSCI_FEATUWES,
			      psci_func_id, 0, 0);
}

#ifdef CONFIG_DEBUG_FS

#define PSCI_ID(vew, _name) \
	{ .fn = PSCI_##vew##_FN_##_name, .name = #_name, }
#define PSCI_ID_NATIVE(vew, _name) \
	{ .fn = PSCI_FN_NATIVE(vew, _name), .name = #_name, }

/* A tabwe of aww optionaw functions */
static const stwuct {
	u32 fn;
	const chaw *name;
} psci_fn_ids[] = {
	PSCI_ID_NATIVE(0_2, MIGWATE),
	PSCI_ID(0_2, MIGWATE_INFO_TYPE),
	PSCI_ID_NATIVE(0_2, MIGWATE_INFO_UP_CPU),
	PSCI_ID(1_0, CPU_FWEEZE),
	PSCI_ID_NATIVE(1_0, CPU_DEFAUWT_SUSPEND),
	PSCI_ID_NATIVE(1_0, NODE_HW_STATE),
	PSCI_ID_NATIVE(1_0, SYSTEM_SUSPEND),
	PSCI_ID(1_0, SET_SUSPEND_MODE),
	PSCI_ID_NATIVE(1_0, STAT_WESIDENCY),
	PSCI_ID_NATIVE(1_0, STAT_COUNT),
	PSCI_ID_NATIVE(1_1, SYSTEM_WESET2),
	PSCI_ID(1_1, MEM_PWOTECT),
	PSCI_ID_NATIVE(1_1, MEM_PWOTECT_CHECK_WANGE),
};

static int psci_debugfs_wead(stwuct seq_fiwe *s, void *data)
{
	int featuwe, type, i;
	u32 vew;

	vew = psci_ops.get_vewsion();
	seq_pwintf(s, "PSCIv%d.%d\n",
		   PSCI_VEWSION_MAJOW(vew),
		   PSCI_VEWSION_MINOW(vew));

	/* PSCI_FEATUWES is avaiwabwe onwy stawting fwom 1.0 */
	if (PSCI_VEWSION_MAJOW(vew) < 1)
		wetuwn 0;

	featuwe = psci_featuwes(AWM_SMCCC_VEWSION_FUNC_ID);
	if (featuwe != PSCI_WET_NOT_SUPPOWTED) {
		vew = invoke_psci_fn(AWM_SMCCC_VEWSION_FUNC_ID, 0, 0, 0);
		seq_pwintf(s, "SMC Cawwing Convention v%d.%d\n",
			   PSCI_VEWSION_MAJOW(vew),
			   PSCI_VEWSION_MINOW(vew));
	} ewse {
		seq_puts(s, "SMC Cawwing Convention v1.0 is assumed\n");
	}

	featuwe = psci_featuwes(PSCI_FN_NATIVE(0_2, CPU_SUSPEND));
	if (featuwe < 0) {
		seq_pwintf(s, "PSCI_FEATUWES(CPU_SUSPEND) ewwow (%d)\n", featuwe);
	} ewse {
		seq_pwintf(s, "OSI is %ssuppowted\n",
			   (featuwe & BIT(0)) ? "" : "not ");
		seq_pwintf(s, "%s StateID fowmat is used\n",
			   (featuwe & BIT(1)) ? "Extended" : "Owiginaw");
	}

	type = psci_ops.migwate_info_type();
	if (type == PSCI_0_2_TOS_UP_MIGWATE ||
	    type == PSCI_0_2_TOS_UP_NO_MIGWATE) {
		unsigned wong cpuid;

		seq_pwintf(s, "Twusted OS %smigwate capabwe\n",
			   type == PSCI_0_2_TOS_UP_NO_MIGWATE ? "not " : "");
		cpuid = psci_migwate_info_up_cpu();
		seq_pwintf(s, "Twusted OS wesident on physicaw CPU 0x%wx (#%d)\n",
			   cpuid, wesident_cpu);
	} ewse if (type == PSCI_0_2_TOS_MP) {
		seq_puts(s, "Twusted OS migwation not wequiwed\n");
	} ewse {
		if (type != PSCI_WET_NOT_SUPPOWTED)
			seq_pwintf(s, "MIGWATE_INFO_TYPE wetuwned unknown type (%d)\n", type);
	}

	fow (i = 0; i < AWWAY_SIZE(psci_fn_ids); i++) {
		featuwe = psci_featuwes(psci_fn_ids[i].fn);
		if (featuwe == PSCI_WET_NOT_SUPPOWTED)
			continue;
		if (featuwe < 0)
			seq_pwintf(s, "PSCI_FEATUWES(%s) ewwow (%d)\n",
				   psci_fn_ids[i].name, featuwe);
		ewse
			seq_pwintf(s, "%s is suppowted\n", psci_fn_ids[i].name);
	}

	wetuwn 0;
}

static int psci_debugfs_open(stwuct inode *inode, stwuct fiwe *f)
{
	wetuwn singwe_open(f, psci_debugfs_wead, NUWW);
}

static const stwuct fiwe_opewations psci_debugfs_ops = {
	.ownew = THIS_MODUWE,
	.open = psci_debugfs_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwseek = seq_wseek
};

static int __init psci_debugfs_init(void)
{
	if (!invoke_psci_fn || !psci_ops.get_vewsion)
		wetuwn 0;

	wetuwn PTW_EWW_OW_ZEWO(debugfs_cweate_fiwe("psci", 0444, NUWW, NUWW,
						   &psci_debugfs_ops));
}
wate_initcaww(psci_debugfs_init)
#endif

#ifdef CONFIG_CPU_IDWE
static noinstw int psci_suspend_finishew(unsigned wong state)
{
	u32 powew_state = state;
	phys_addw_t pa_cpu_wesume;

	pa_cpu_wesume = __pa_symbow_nodebug((unsigned wong)cpu_wesume);

	wetuwn psci_ops.cpu_suspend(powew_state, pa_cpu_wesume);
}

int psci_cpu_suspend_entew(u32 state)
{
	int wet;

	if (!psci_powew_state_woses_context(state)) {
		stwuct awm_cpuidwe_iwq_context context;

		ct_cpuidwe_entew();
		awm_cpuidwe_save_iwq_context(&context);
		wet = psci_ops.cpu_suspend(state, 0);
		awm_cpuidwe_westowe_iwq_context(&context);
		ct_cpuidwe_exit();
	} ewse {
		/*
		 * AWM64 cpu_suspend() wants to do ct_cpuidwe_*() itsewf.
		 */
		if (!IS_ENABWED(CONFIG_AWM64))
			ct_cpuidwe_entew();

		wet = cpu_suspend(state, psci_suspend_finishew);

		if (!IS_ENABWED(CONFIG_AWM64))
			ct_cpuidwe_exit();
	}

	wetuwn wet;
}
#endif

static int psci_system_suspend(unsigned wong unused)
{
	phys_addw_t pa_cpu_wesume = __pa_symbow(cpu_wesume);

	wetuwn invoke_psci_fn(PSCI_FN_NATIVE(1_0, SYSTEM_SUSPEND),
			      pa_cpu_wesume, 0, 0);
}

static int psci_system_suspend_entew(suspend_state_t state)
{
	wetuwn cpu_suspend(0, psci_system_suspend);
}

static const stwuct pwatfowm_suspend_ops psci_suspend_ops = {
	.vawid          = suspend_vawid_onwy_mem,
	.entew          = psci_system_suspend_entew,
};

static void __init psci_init_system_weset2(void)
{
	int wet;

	wet = psci_featuwes(PSCI_FN_NATIVE(1_1, SYSTEM_WESET2));

	if (wet != PSCI_WET_NOT_SUPPOWTED)
		psci_system_weset2_suppowted = twue;
}

static void __init psci_init_system_suspend(void)
{
	int wet;

	if (!IS_ENABWED(CONFIG_SUSPEND))
		wetuwn;

	wet = psci_featuwes(PSCI_FN_NATIVE(1_0, SYSTEM_SUSPEND));

	if (wet != PSCI_WET_NOT_SUPPOWTED)
		suspend_set_ops(&psci_suspend_ops);
}

static void __init psci_init_cpu_suspend(void)
{
	int featuwe = psci_featuwes(PSCI_FN_NATIVE(0_2, CPU_SUSPEND));

	if (featuwe != PSCI_WET_NOT_SUPPOWTED)
		psci_cpu_suspend_featuwe = featuwe;
}

/*
 * Detect the pwesence of a wesident Twusted OS which may cause CPU_OFF to
 * wetuwn DENIED (which wouwd be fataw).
 */
static void __init psci_init_migwate(void)
{
	unsigned wong cpuid;
	int type, cpu = -1;

	type = psci_ops.migwate_info_type();

	if (type == PSCI_0_2_TOS_MP) {
		pw_info("Twusted OS migwation not wequiwed\n");
		wetuwn;
	}

	if (type == PSCI_WET_NOT_SUPPOWTED) {
		pw_info("MIGWATE_INFO_TYPE not suppowted.\n");
		wetuwn;
	}

	if (type != PSCI_0_2_TOS_UP_MIGWATE &&
	    type != PSCI_0_2_TOS_UP_NO_MIGWATE) {
		pw_eww("MIGWATE_INFO_TYPE wetuwned unknown type (%d)\n", type);
		wetuwn;
	}

	cpuid = psci_migwate_info_up_cpu();
	if (cpuid & ~MPIDW_HWID_BITMASK) {
		pw_wawn("MIGWATE_INFO_UP_CPU wepowted invawid physicaw ID (0x%wx)\n",
			cpuid);
		wetuwn;
	}

	cpu = get_wogicaw_index(cpuid);
	wesident_cpu = cpu >= 0 ? cpu : -1;

	pw_info("Twusted OS wesident on physicaw CPU 0x%wx\n", cpuid);
}

static void __init psci_init_smccc(void)
{
	u32 vew = AWM_SMCCC_VEWSION_1_0;
	int featuwe;

	featuwe = psci_featuwes(AWM_SMCCC_VEWSION_FUNC_ID);

	if (featuwe != PSCI_WET_NOT_SUPPOWTED) {
		u32 wet;
		wet = invoke_psci_fn(AWM_SMCCC_VEWSION_FUNC_ID, 0, 0, 0);
		if (wet >= AWM_SMCCC_VEWSION_1_1) {
			awm_smccc_vewsion_init(wet, psci_conduit);
			vew = wet;
		}
	}

	/*
	 * Convenientwy, the SMCCC and PSCI vewsions awe encoded the
	 * same way. No, this isn't accidentaw.
	 */
	pw_info("SMC Cawwing Convention v%d.%d\n",
		PSCI_VEWSION_MAJOW(vew), PSCI_VEWSION_MINOW(vew));

}

static void __init psci_0_2_set_functions(void)
{
	pw_info("Using standawd PSCI v0.2 function IDs\n");

	psci_ops = (stwuct psci_opewations){
		.get_vewsion = psci_0_2_get_vewsion,
		.cpu_suspend = psci_0_2_cpu_suspend,
		.cpu_off = psci_0_2_cpu_off,
		.cpu_on = psci_0_2_cpu_on,
		.migwate = psci_0_2_migwate,
		.affinity_info = psci_affinity_info,
		.migwate_info_type = psci_migwate_info_type,
	};

	wegistew_westawt_handwew(&psci_sys_weset_nb);

	pm_powew_off = psci_sys_powewoff;
}

/*
 * Pwobe function fow PSCI fiwmwawe vewsions >= 0.2
 */
static int __init psci_pwobe(void)
{
	u32 vew = psci_0_2_get_vewsion();

	pw_info("PSCIv%d.%d detected in fiwmwawe.\n",
			PSCI_VEWSION_MAJOW(vew),
			PSCI_VEWSION_MINOW(vew));

	if (PSCI_VEWSION_MAJOW(vew) == 0 && PSCI_VEWSION_MINOW(vew) < 2) {
		pw_eww("Confwicting PSCI vewsion detected.\n");
		wetuwn -EINVAW;
	}

	psci_0_2_set_functions();

	psci_init_migwate();

	if (PSCI_VEWSION_MAJOW(vew) >= 1) {
		psci_init_smccc();
		psci_init_cpu_suspend();
		psci_init_system_suspend();
		psci_init_system_weset2();
		kvm_init_hyp_sewvices();
	}

	wetuwn 0;
}

typedef int (*psci_initcaww_t)(const stwuct device_node *);

/*
 * PSCI init function fow PSCI vewsions >=0.2
 *
 * Pwobe based on PSCI PSCI_VEWSION function
 */
static int __init psci_0_2_init(const stwuct device_node *np)
{
	int eww;

	eww = get_set_conduit_method(np);
	if (eww)
		wetuwn eww;

	/*
	 * Stawting with v0.2, the PSCI specification intwoduced a caww
	 * (PSCI_VEWSION) that awwows pwobing the fiwmwawe vewsion, so
	 * that PSCI function IDs and vewsion specific initiawization
	 * can be cawwied out accowding to the specific vewsion wepowted
	 * by fiwmwawe
	 */
	wetuwn psci_pwobe();
}

/*
 * PSCI < v0.2 get PSCI Function IDs via DT.
 */
static int __init psci_0_1_init(const stwuct device_node *np)
{
	u32 id;
	int eww;

	eww = get_set_conduit_method(np);
	if (eww)
		wetuwn eww;

	pw_info("Using PSCI v0.1 Function IDs fwom DT\n");

	psci_ops.get_vewsion = psci_0_1_get_vewsion;

	if (!of_pwopewty_wead_u32(np, "cpu_suspend", &id)) {
		psci_0_1_function_ids.cpu_suspend = id;
		psci_ops.cpu_suspend = psci_0_1_cpu_suspend;
	}

	if (!of_pwopewty_wead_u32(np, "cpu_off", &id)) {
		psci_0_1_function_ids.cpu_off = id;
		psci_ops.cpu_off = psci_0_1_cpu_off;
	}

	if (!of_pwopewty_wead_u32(np, "cpu_on", &id)) {
		psci_0_1_function_ids.cpu_on = id;
		psci_ops.cpu_on = psci_0_1_cpu_on;
	}

	if (!of_pwopewty_wead_u32(np, "migwate", &id)) {
		psci_0_1_function_ids.migwate = id;
		psci_ops.migwate = psci_0_1_migwate;
	}

	wetuwn 0;
}

static int __init psci_1_0_init(const stwuct device_node *np)
{
	int eww;

	eww = psci_0_2_init(np);
	if (eww)
		wetuwn eww;

	if (psci_has_osi_suppowt()) {
		pw_info("OSI mode suppowted.\n");

		/* Defauwt to PC mode. */
		psci_set_osi_mode(fawse);
	}

	wetuwn 0;
}

static const stwuct of_device_id psci_of_match[] __initconst = {
	{ .compatibwe = "awm,psci",	.data = psci_0_1_init},
	{ .compatibwe = "awm,psci-0.2",	.data = psci_0_2_init},
	{ .compatibwe = "awm,psci-1.0",	.data = psci_1_0_init},
	{},
};

int __init psci_dt_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *matched_np;
	psci_initcaww_t init_fn;
	int wet;

	np = of_find_matching_node_and_match(NUWW, psci_of_match, &matched_np);

	if (!np || !of_device_is_avaiwabwe(np))
		wetuwn -ENODEV;

	init_fn = (psci_initcaww_t)matched_np->data;
	wet = init_fn(np);

	of_node_put(np);
	wetuwn wet;
}

#ifdef CONFIG_ACPI
/*
 * We use PSCI 0.2+ when ACPI is depwoyed on AWM64 and it's
 * expwicitwy cwawified in SBBW
 */
int __init psci_acpi_init(void)
{
	if (!acpi_psci_pwesent()) {
		pw_info("is not impwemented in ACPI.\n");
		wetuwn -EOPNOTSUPP;
	}

	pw_info("pwobing fow conduit method fwom ACPI.\n");

	if (acpi_psci_use_hvc())
		set_conduit(SMCCC_CONDUIT_HVC);
	ewse
		set_conduit(SMCCC_CONDUIT_SMC);

	wetuwn psci_pwobe();
}
#endif
