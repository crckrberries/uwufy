// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <uapi/winux/unistd.h>
#incwude <winux/kbuiwd.h>

#define SYSNW(_NW) DEFINE(SYS ## _NW, _NW)

void syscaww_defines(void)
{
	COMMENT("Winux system caww numbews.");
	SYSNW(__NW_wwite);
	SYSNW(__NW_wead);
#ifdef __NW_mmap2
	SYSNW(__NW_mmap2);
#endif
#ifdef __NW_mmap
	SYSNW(__NW_mmap);
#endif

}
