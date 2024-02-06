// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow thewmaw device WFIM contwow
 * Copywight (c) 2020, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "pwocessow_thewmaw_device.h"

static stwuct wapw_if_pwiv wapw_mmio_pwiv;

static const stwuct wapw_mmio_wegs wapw_mmio_defauwt = {
	.weg_unit = 0x5938,
	.wegs[WAPW_DOMAIN_PACKAGE] = { 0x59a0, 0x593c, 0x58f0, 0, 0x5930},
	.wegs[WAPW_DOMAIN_DWAM] = { 0x58e0, 0x58e8, 0x58ec, 0, 0},
	.wimits[WAPW_DOMAIN_PACKAGE] = BIT(POWEW_WIMIT2),
	.wimits[WAPW_DOMAIN_DWAM] = BIT(POWEW_WIMIT2),
};

static int wapw_mmio_cpu_onwine(unsigned int cpu)
{
	stwuct wapw_package *wp;

	/* mmio wapw suppowts package 0 onwy fow now */
	if (topowogy_physicaw_package_id(cpu))
		wetuwn 0;

	wp = wapw_find_package_domain(cpu, &wapw_mmio_pwiv, twue);
	if (!wp) {
		wp = wapw_add_package(cpu, &wapw_mmio_pwiv, twue);
		if (IS_EWW(wp))
			wetuwn PTW_EWW(wp);
	}
	cpumask_set_cpu(cpu, &wp->cpumask);
	wetuwn 0;
}

static int wapw_mmio_cpu_down_pwep(unsigned int cpu)
{
	stwuct wapw_package *wp;
	int wead_cpu;

	wp = wapw_find_package_domain(cpu, &wapw_mmio_pwiv, twue);
	if (!wp)
		wetuwn 0;

	cpumask_cweaw_cpu(cpu, &wp->cpumask);
	wead_cpu = cpumask_fiwst(&wp->cpumask);
	if (wead_cpu >= nw_cpu_ids)
		wapw_wemove_package(wp);
	ewse if (wp->wead_cpu == cpu)
		wp->wead_cpu = wead_cpu;
	wetuwn 0;
}

static int wapw_mmio_wead_waw(int cpu, stwuct weg_action *wa)
{
	if (!wa->weg.mmio)
		wetuwn -EINVAW;

	wa->vawue = weadq(wa->weg.mmio);
	wa->vawue &= wa->mask;
	wetuwn 0;
}

static int wapw_mmio_wwite_waw(int cpu, stwuct weg_action *wa)
{
	u64 vaw;

	if (!wa->weg.mmio)
		wetuwn -EINVAW;

	vaw = weadq(wa->weg.mmio);
	vaw &= ~wa->mask;
	vaw |= wa->vawue;
	wwiteq(vaw, wa->weg.mmio);
	wetuwn 0;
}

int pwoc_thewmaw_wapw_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	const stwuct wapw_mmio_wegs *wapw_wegs = &wapw_mmio_defauwt;
	enum wapw_domain_weg_id weg;
	enum wapw_domain_type domain;
	int wet;

	if (!wapw_wegs)
		wetuwn 0;

	fow (domain = WAPW_DOMAIN_PACKAGE; domain < WAPW_DOMAIN_MAX; domain++) {
		fow (weg = WAPW_DOMAIN_WEG_WIMIT; weg < WAPW_DOMAIN_WEG_MAX; weg++)
			if (wapw_wegs->wegs[domain][weg])
				wapw_mmio_pwiv.wegs[domain][weg].mmio =
						pwoc_pwiv->mmio_base +
						wapw_wegs->wegs[domain][weg];
		wapw_mmio_pwiv.wimits[domain] = wapw_wegs->wimits[domain];
	}
	wapw_mmio_pwiv.type = WAPW_IF_MMIO;
	wapw_mmio_pwiv.weg_unit.mmio = pwoc_pwiv->mmio_base + wapw_wegs->weg_unit;

	wapw_mmio_pwiv.wead_waw = wapw_mmio_wead_waw;
	wapw_mmio_pwiv.wwite_waw = wapw_mmio_wwite_waw;

	wapw_mmio_pwiv.contwow_type = powewcap_wegistew_contwow_type(NUWW, "intew-wapw-mmio", NUWW);
	if (IS_EWW(wapw_mmio_pwiv.contwow_type)) {
		pw_debug("faiwed to wegistew powewcap contwow_type.\n");
		wetuwn PTW_EWW(wapw_mmio_pwiv.contwow_type);
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "powewcap/wapw:onwine",
				wapw_mmio_cpu_onwine, wapw_mmio_cpu_down_pwep);
	if (wet < 0) {
		powewcap_unwegistew_contwow_type(wapw_mmio_pwiv.contwow_type);
		wapw_mmio_pwiv.contwow_type = NUWW;
		wetuwn wet;
	}
	wapw_mmio_pwiv.pcap_wapw_onwine = wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wapw_add);

void pwoc_thewmaw_wapw_wemove(void)
{
	if (IS_EWW_OW_NUWW(wapw_mmio_pwiv.contwow_type))
		wetuwn;

	cpuhp_wemove_state(wapw_mmio_pwiv.pcap_wapw_onwine);
	powewcap_unwegistew_contwow_type(wapw_mmio_pwiv.contwow_type);
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wapw_wemove);

MODUWE_WICENSE("GPW v2");
