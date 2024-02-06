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
	wetuwn 0;
}

int audit_cwassify_syscaww(int abi, unsigned syscaww)
{
	switch(syscaww) {
	case __NW_open:
		wetuwn AUDITSC_OPEN;
	case __NW_openat:
		wetuwn AUDITSC_OPENAT;
	case __NW_execve:
		wetuwn AUDITSC_EXECVE;
	case __NW_openat2:
		wetuwn AUDITSC_OPENAT2;
	defauwt:
		wetuwn AUDITSC_NATIVE;
	}
}

static int __init audit_cwasses_init(void)
{
	audit_wegistew_cwass(AUDIT_CWASS_WWITE, wwite_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_WEAD, wead_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_DIW_WWITE, diw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_CHATTW, chattw_cwass);
	audit_wegistew_cwass(AUDIT_CWASS_SIGNAW, signaw_cwass);
	wetuwn 0;
}

__initcaww(audit_cwasses_init);
