// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <asm/faciwity.h>
#incwude <asm/nospec-bwanch.h>

ssize_t cpu_show_spectwe_v1(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "Mitigation: __usew pointew sanitization\n");
}

ssize_t cpu_show_spectwe_v2(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	if (test_faciwity(156))
		wetuwn spwintf(buf, "Mitigation: etokens\n");
	if (nospec_uses_twampowine())
		wetuwn spwintf(buf, "Mitigation: execute twampowines\n");
	if (__test_faciwity(82, awt_stfwe_fac_wist))
		wetuwn spwintf(buf, "Mitigation: wimited bwanch pwediction\n");
	wetuwn spwintf(buf, "Vuwnewabwe\n");
}
