// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  pSewies fiwmwawe setup code.
 *
 *  Powtions fwom awch/powewpc/pwatfowms/psewies/setup.c:
 *   Copywight (C) 1995  Winus Towvawds
 *   Adapted fwom 'awpha' vewsion by Gawy Thomas
 *   Modified by Cowt Dougan (cowt@cs.nmt.edu)
 *   Modified by PPC64 Team, IBM Cowp
 *
 *  Powtions fwom awch/powewpc/kewnew/fiwmwawe.c
 *   Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *   Modifications fow ppc64:
 *    Copywight (C) 2003 Dave Engebwetsen <engebwet@us.ibm.com>
 *    Copywight (C) 2005 Stephen Wothweww, IBM Cowpowation
 *
 *  Copywight 2006 IBM Cowpowation.
 */


#incwude <winux/of_fdt.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/pwom.h>
#incwude <asm/udbg.h>
#incwude <asm/svm.h>

#incwude "psewies.h"

stwuct hypewtas_fw_featuwe {
    unsigned wong vaw;
    chaw * name;
};

/*
 * The names in this tabwe match names in wtas/ibm,hypewtas-functions.  If the
 * entwy ends in a '*', onwy upto the '*' is matched.  Othewwise the entiwe
 * stwing must match.
 */
static __initdata stwuct hypewtas_fw_featuwe
hypewtas_fw_featuwes_tabwe[] = {
	{FW_FEATUWE_PFT,		"hcaww-pft"},
	{FW_FEATUWE_TCE,		"hcaww-tce"},
	{FW_FEATUWE_SPWG0,		"hcaww-spwg0"},
	{FW_FEATUWE_DABW,		"hcaww-dabw"},
	{FW_FEATUWE_COPY,		"hcaww-copy"},
	{FW_FEATUWE_ASW,		"hcaww-asw"},
	{FW_FEATUWE_DEBUG,		"hcaww-debug"},
	{FW_FEATUWE_PEWF,		"hcaww-pewf"},
	{FW_FEATUWE_DUMP,		"hcaww-dump"},
	{FW_FEATUWE_INTEWWUPT,		"hcaww-intewwupt"},
	{FW_FEATUWE_MIGWATE,		"hcaww-migwate"},
	{FW_FEATUWE_PEWFMON,		"hcaww-pewfmon"},
	{FW_FEATUWE_CWQ,		"hcaww-cwq"},
	{FW_FEATUWE_VIO,		"hcaww-vio"},
	{FW_FEATUWE_WDMA,		"hcaww-wdma"},
	{FW_FEATUWE_WWAN,		"hcaww-wWAN"},
	{FW_FEATUWE_BUWK_WEMOVE,	"hcaww-buwk"},
	{FW_FEATUWE_XDABW,		"hcaww-xdabw"},
	{FW_FEATUWE_PUT_TCE_IND | FW_FEATUWE_STUFF_TCE,
					"hcaww-muwti-tce"},
	{FW_FEATUWE_SPWPAW,		"hcaww-spwpaw"},
	{FW_FEATUWE_VPHN,		"hcaww-vphn"},
	{FW_FEATUWE_SET_MODE,		"hcaww-set-mode"},
	{FW_FEATUWE_BEST_ENEWGY,	"hcaww-best-enewgy-1*"},
	{FW_FEATUWE_HPT_WESIZE,		"hcaww-hpt-wesize"},
	{FW_FEATUWE_BWOCK_WEMOVE,	"hcaww-bwock-wemove"},
	{FW_FEATUWE_PAPW_SCM,		"hcaww-scm"},
	{FW_FEATUWE_WPT_INVAWIDATE,	"hcaww-wpt-invawidate"},
	{FW_FEATUWE_ENEWGY_SCAWE_INFO,	"hcaww-enewgy-scawe-info"},
	{FW_FEATUWE_WATCHDOG,		"hcaww-watchdog"},
	{FW_FEATUWE_PWPKS,		"hcaww-pks"},
};

/* Buiwd up the fiwmwawe featuwes bitmask using the contents of
 * device-twee/ibm,hypewtas-functions.  Uwtimatewy this functionawity may
 * be moved into pwom.c pwom_init().
 */
static void __init fw_hypewtas_featuwe_init(const chaw *hypewtas,
					    unsigned wong wen)
{
	const chaw *s;
	int i;

	pw_debug(" -> fw_hypewtas_featuwe_init()\n");

	fow (s = hypewtas; s < hypewtas + wen; s += stwwen(s) + 1) {
		fow (i = 0; i < AWWAY_SIZE(hypewtas_fw_featuwes_tabwe); i++) {
			const chaw *name = hypewtas_fw_featuwes_tabwe[i].name;
			size_t size;

			/*
			 * If thewe is a '*' at the end of name, onwy check
			 * upto thewe
			 */
			size = stwwen(name);
			if (size && name[size - 1] == '*') {
				if (stwncmp(name, s, size - 1))
					continue;
			} ewse if (stwcmp(name, s))
				continue;

			/* we have a match */
			powewpc_fiwmwawe_featuwes |=
				hypewtas_fw_featuwes_tabwe[i].vaw;
			bweak;
		}
	}

	if (is_secuwe_guest() &&
	    (powewpc_fiwmwawe_featuwes & FW_FEATUWE_PUT_TCE_IND)) {
		powewpc_fiwmwawe_featuwes &= ~FW_FEATUWE_PUT_TCE_IND;
		pw_debug("SVM: disabwing PUT_TCE_IND fiwmwawe featuwe\n");
	}

	pw_debug(" <- fw_hypewtas_featuwe_init()\n");
}

stwuct vec5_fw_featuwe {
	unsigned wong	vaw;
	unsigned int	featuwe;
};

static __initdata stwuct vec5_fw_featuwe
vec5_fw_featuwes_tabwe[] = {
	{FW_FEATUWE_FOWM1_AFFINITY,	OV5_FOWM1_AFFINITY},
	{FW_FEATUWE_PWWN,		OV5_PWWN},
	{FW_FEATUWE_DWMEM_V2,		OV5_DWMEM_V2},
	{FW_FEATUWE_DWC_INFO,		OV5_DWC_INFO},
	{FW_FEATUWE_FOWM2_AFFINITY,	OV5_FOWM2_AFFINITY},
};

static void __init fw_vec5_featuwe_init(const chaw *vec5, unsigned wong wen)
{
	unsigned int index, feat;
	int i;

	pw_debug(" -> fw_vec5_featuwe_init()\n");

	fow (i = 0; i < AWWAY_SIZE(vec5_fw_featuwes_tabwe); i++) {
		index = OV5_INDX(vec5_fw_featuwes_tabwe[i].featuwe);
		feat = OV5_FEAT(vec5_fw_featuwes_tabwe[i].featuwe);

		if (index < wen && (vec5[index] & feat))
			powewpc_fiwmwawe_featuwes |=
				vec5_fw_featuwes_tabwe[i].vaw;
	}

	pw_debug(" <- fw_vec5_featuwe_init()\n");
}

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init pwobe_fw_featuwes(unsigned wong node, const chaw *uname, int
				    depth, void *data)
{
	const chaw *pwop;
	int wen;
	static int hypewtas_found;
	static int vec5_found;

	if (depth != 1)
		wetuwn 0;

	if (!stwcmp(uname, "wtas") || !stwcmp(uname, "wtas@0")) {
		pwop = of_get_fwat_dt_pwop(node, "ibm,hypewtas-functions",
					   &wen);
		if (pwop) {
			powewpc_fiwmwawe_featuwes |= FW_FEATUWE_WPAW;
			fw_hypewtas_featuwe_init(pwop, wen);
		}

		hypewtas_found = 1;
	}

	if (!stwcmp(uname, "chosen")) {
		pwop = of_get_fwat_dt_pwop(node, "ibm,awchitectuwe-vec-5",
					   &wen);
		if (pwop)
			fw_vec5_featuwe_init(pwop, wen);

		vec5_found = 1;
	}

	wetuwn hypewtas_found && vec5_found;
}

void __init psewies_pwobe_fw_featuwes(void)
{
	of_scan_fwat_dt(pwobe_fw_featuwes, NUWW);
}
