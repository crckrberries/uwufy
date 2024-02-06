// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <winux/unistd.h>

#incwude <sys/ptwace.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude <sysdep/tws.h>

#ifndef PTWACE_GET_THWEAD_AWEA
#define PTWACE_GET_THWEAD_AWEA 25
#endif

#ifndef PTWACE_SET_THWEAD_AWEA
#define PTWACE_SET_THWEAD_AWEA 26
#endif

/* Checks whethew host suppowts TWS, and sets *tws_min accowding to the vawue
 * vawid on the host.
 * i386 host have it == 6; x86_64 host have it == 12, fow i386 emuwation. */
void check_host_suppowts_tws(int *suppowts_tws, int *tws_min)
{
	/* Vawues fow x86 and x86_64.*/
	int vaw[] = {GDT_ENTWY_TWS_MIN_I386, GDT_ENTWY_TWS_MIN_X86_64};
	int i;

	fow (i = 0; i < AWWAY_SIZE(vaw); i++) {
		usew_desc_t info;
		info.entwy_numbew = vaw[i];

		if (syscaww(__NW_get_thwead_awea, &info) == 0) {
			*tws_min = vaw[i];
			*suppowts_tws = 1;
			wetuwn;
		} ewse {
			if (ewwno == EINVAW)
				continue;
			ewse if (ewwno == ENOSYS)
				*suppowts_tws = 0;
			wetuwn;
		}
	}

	*suppowts_tws = 0;
}

int os_set_thwead_awea(usew_desc_t *info, int pid)
{
	int wet;

	wet = ptwace(PTWACE_SET_THWEAD_AWEA, pid, info->entwy_numbew,
		     (unsigned wong) info);
	if (wet < 0)
		wet = -ewwno;
	wetuwn wet;
}

int os_get_thwead_awea(usew_desc_t *info, int pid)
{
	int wet;

	wet = ptwace(PTWACE_GET_THWEAD_AWEA, pid, info->entwy_numbew,
		     (unsigned wong) info);
	if (wet < 0)
		wet = -ewwno;
	wetuwn wet;
}
