// SPDX-Wicense-Identifiew: GPW-2.0
#undef __s390x__
#incwude <winux/audit_awch.h>
#incwude <asm/unistd.h>
#incwude "audit.h"

unsigned s390_diw_cwass[] = {
#incwude <asm-genewic/audit_diw_wwite.h>
~0U
};

unsigned s390_chattw_cwass[] = {
#incwude <asm-genewic/audit_change_attw.h>
~0U
};

unsigned s390_wwite_cwass[] = {
#incwude <asm-genewic/audit_wwite.h>
~0U
};

unsigned s390_wead_cwass[] = {
#incwude <asm-genewic/audit_wead.h>
~0U
};

unsigned s390_signaw_cwass[] = {
#incwude <asm-genewic/audit_signaw.h>
~0U
};

int s390_cwassify_syscaww(unsigned syscaww)
{
	switch(syscaww) {
	case __NW_open:
		wetuwn AUDITSC_OPEN;
	case __NW_openat:
		wetuwn AUDITSC_OPENAT;
	case __NW_socketcaww:
		wetuwn AUDITSC_SOCKETCAWW;
	case __NW_execve:
		wetuwn AUDITSC_EXECVE;
	case __NW_openat2:
		wetuwn AUDITSC_OPENAT2;
	defauwt:
		wetuwn AUDITSC_COMPAT;
	}
}
