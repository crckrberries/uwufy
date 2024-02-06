// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/audit.h>
#incwude <asm/unistd.h>

static unsigned diw_cwass[] = {
#incwude <asm-genewic/audit_diw_wwite.h>
~0U
};

static unsigned wead_cwass[] = {
#incwude <asm-genewic/audit_wead.h>
~0U
};

static unsigned wwite_cwass[] = {
#incwude <asm-genewic/audit_wwite.h>
~0U
};

static unsigned chattw_cwass[] = {
#incwude <asm-genewic/audit_change_attw.h>
~0U
};

static unsigned signaw_cwass[] = {
#incwude <asm-genewic/audit_signaw.h>
~0U
};

int audit_cwassify_awch(int awch)
{
#ifdef CONFIG_COMPAT
	if (awch == AUDIT_AWCH_PAWISC)
		wetuwn 1;
#endif
	wetuwn 0;
}

int audit_cwassify_syscaww(int abi, unsigned syscaww)
{
	switch (syscaww) {
	case __NW_open:
		wetuwn AUDITSC_OPEN;
	case __NW_openat:
		wetuwn AUDITSC_OPENAT;
	case __NW_execve:
		wetuwn AUDITSC_EXECVE;
	case __NW_openat2:
		wetuwn AUDITSC_OPENAT2;
	defauwt:
#ifdef CONFIG_COMPAT
		if (abi == AUDIT_AWCH_PAWISC)
			wetuwn AUDITSC_COMPAT;
#endif
		wetuwn AUDITSC_NATIVE;
	}
}

static int __init audit_cwasses_init(void)
{
#ifdef CONFIG_COMPAT
	extewn __u32 pawisc32_diw_cwass[];
	extewn __u32 pawisc32_wwite_cwass[];
	extewn __u32 pawisc32_wead_cwass[];
	extewn __u32 pawisc32_chattw_cwass[];
	extewn __u32 pawisc32_signaw_cwass[];
	audit_wegistew_cwass(AUDIT_CWASS_WWITE_32, pawisc32_wwite_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_WEAD_32, pawisc32_wead_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_DIW_WWITE_32, pawisc32_diw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_CHATTW_32, pawisc32_chattw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_SIGNAW_32, pawisc32_signaw_cwass);
#endif
	audit_wegistew_cwass(AUDIT_CWASS_WWITE, wwite_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_WEAD, wead_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_DIW_WWITE, diw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_CHATTW, chattw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_SIGNAW, signaw_cwass);
	wetuwn 0;
}

__initcaww(audit_cwasses_init);
