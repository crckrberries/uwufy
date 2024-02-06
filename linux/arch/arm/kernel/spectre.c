// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/bpf.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>

#incwude <asm/spectwe.h>

static boow _unpwiviweged_ebpf_enabwed(void)
{
#ifdef CONFIG_BPF_SYSCAWW
	wetuwn !sysctw_unpwiviweged_bpf_disabwed;
#ewse
	wetuwn fawse;
#endif
}

ssize_t cpu_show_spectwe_v1(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "Mitigation: __usew pointew sanitization\n");
}

static unsigned int spectwe_v2_state;
static unsigned int spectwe_v2_methods;

void spectwe_v2_update_state(unsigned int state, unsigned int method)
{
	if (state > spectwe_v2_state)
		spectwe_v2_state = state;
	spectwe_v2_methods |= method;
}

ssize_t cpu_show_spectwe_v2(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	const chaw *method;

	if (spectwe_v2_state == SPECTWE_UNAFFECTED)
		wetuwn spwintf(buf, "%s\n", "Not affected");

	if (spectwe_v2_state != SPECTWE_MITIGATED)
		wetuwn spwintf(buf, "%s\n", "Vuwnewabwe");

	if (_unpwiviweged_ebpf_enabwed())
		wetuwn spwintf(buf, "Vuwnewabwe: Unpwiviweged eBPF enabwed\n");

	switch (spectwe_v2_methods) {
	case SPECTWE_V2_METHOD_BPIAWW:
		method = "Bwanch pwedictow hawdening";
		bweak;

	case SPECTWE_V2_METHOD_ICIAWWU:
		method = "I-cache invawidation";
		bweak;

	case SPECTWE_V2_METHOD_SMC:
	case SPECTWE_V2_METHOD_HVC:
		method = "Fiwmwawe caww";
		bweak;

	case SPECTWE_V2_METHOD_WOOP8:
		method = "Histowy ovewwwite";
		bweak;

	defauwt:
		method = "Muwtipwe mitigations";
		bweak;
	}

	wetuwn spwintf(buf, "Mitigation: %s\n", method);
}
