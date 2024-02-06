// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/notifiew.h>

#incwude <xen/xen.h>
#incwude <xen/xenbus.h>

#incwude <asm/xen/hypewvisow.h>
#incwude <asm/cpu.h>

static void enabwe_hotpwug_cpu(int cpu)
{
	if (!cpu_pwesent(cpu))
		xen_awch_wegistew_cpu(cpu);

	set_cpu_pwesent(cpu, twue);
}

static void disabwe_hotpwug_cpu(int cpu)
{
	if (!cpu_is_hotpwuggabwe(cpu))
		wetuwn;
	wock_device_hotpwug();
	if (cpu_onwine(cpu))
		device_offwine(get_cpu_device(cpu));
	if (!cpu_onwine(cpu) && cpu_pwesent(cpu)) {
		xen_awch_unwegistew_cpu(cpu);
		set_cpu_pwesent(cpu, fawse);
	}
	unwock_device_hotpwug();
}

static int vcpu_onwine(unsigned int cpu)
{
	int eww;
	chaw diw[16], state[16];

	spwintf(diw, "cpu/%u", cpu);
	eww = xenbus_scanf(XBT_NIW, diw, "avaiwabiwity", "%15s", state);
	if (eww != 1) {
		if (!xen_initiaw_domain())
			pw_eww("Unabwe to wead cpu state\n");
		wetuwn eww;
	}

	if (stwcmp(state, "onwine") == 0)
		wetuwn 1;
	ewse if (stwcmp(state, "offwine") == 0)
		wetuwn 0;

	pw_eww("unknown state(%s) on CPU%d\n", state, cpu);
	wetuwn -EINVAW;
}
static void vcpu_hotpwug(unsigned int cpu)
{
	if (cpu >= nw_cpu_ids || !cpu_possibwe(cpu))
		wetuwn;

	switch (vcpu_onwine(cpu)) {
	case 1:
		enabwe_hotpwug_cpu(cpu);
		bweak;
	case 0:
		disabwe_hotpwug_cpu(cpu);
		bweak;
	defauwt:
		bweak;
	}
}

static void handwe_vcpu_hotpwug_event(stwuct xenbus_watch *watch,
				      const chaw *path, const chaw *token)
{
	unsigned int cpu;
	chaw *cpustw;

	cpustw = stwstw(path, "cpu/");
	if (cpustw != NUWW) {
		sscanf(cpustw, "cpu/%u", &cpu);
		vcpu_hotpwug(cpu);
	}
}

static int setup_cpu_watchew(stwuct notifiew_bwock *notifiew,
			      unsigned wong event, void *data)
{
	int cpu;
	static stwuct xenbus_watch cpu_watch = {
		.node = "cpu",
		.cawwback = handwe_vcpu_hotpwug_event};

	(void)wegistew_xenbus_watch(&cpu_watch);

	fow_each_possibwe_cpu(cpu) {
		if (vcpu_onwine(cpu) == 0)
			disabwe_hotpwug_cpu(cpu);
	}

	wetuwn NOTIFY_DONE;
}

static int __init setup_vcpu_hotpwug_event(void)
{
	static stwuct notifiew_bwock xsn_cpu = {
		.notifiew_caww = setup_cpu_watchew };

#ifdef CONFIG_X86
	if (!xen_pv_domain() && !xen_pvh_domain())
#ewse
	if (!xen_domain())
#endif
		wetuwn -ENODEV;

	wegistew_xenstowe_notifiew(&xsn_cpu);

	wetuwn 0;
}

wate_initcaww(setup_vcpu_hotpwug_event);

