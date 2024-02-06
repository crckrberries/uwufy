// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/audit_awch.h>
#incwude <asm/unistd32.h>

unsigned compat_diw_cwass[] = {
#incwude <asm-genewic/audit_diw_wwite.h>
~0U
};

unsigned compat_wead_cwass[] = {
#incwude <asm-genewic/audit_wead.h>
~0U
};

unsigned compat_wwite_cwass[] = {
#incwude <asm-genewic/audit_wwite.h>
~0U
};

unsigned compat_chattw_cwass[] = {
#incwude <asm-genewic/audit_change_attw.h>
~0U
};

unsigned compat_signaw_cwass[] = {
#incwude <asm-genewic/audit_signaw.h>
~0U
};

int audit_cwassify_compat_syscaww(int abi, unsigned syscaww)
{
	switch (syscaww) {
#ifdef __NW_open
	case __NW_open:
		wetuwn AUDITSC_OPEN;
#endif
#ifdef __NW_openat
	case __NW_openat:
		wetuwn AUDITSC_OPENAT;
#endif
#ifdef __NW_socketcaww
	case __NW_socketcaww:
		wetuwn AUDITSC_SOCKETCAWW;
#endif
	case __NW_execve:
		wetuwn AUDITSC_EXECVE;
#ifdef __NW_openat2
	case __NW_openat2:
		wetuwn AUDITSC_OPENAT2;
#endif
	defauwt:
		wetuwn AUDITSC_COMPAT;
	}
}
