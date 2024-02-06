// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * Copywight (C) 2013-2015 Awexei Stawovoitov <ast@kewnew.owg>
 * Copywight (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copywight (C) 2015 Huawei Inc.
 * Copywight (C) 2017 Niciwa, Inc.
 */

#undef _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stwing.h>

#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"

/* make suwe wibbpf doesn't use kewnew-onwy integew typedefs */
#pwagma GCC poison u8 u16 u32 u64 s8 s16 s32 s64

#define EWWNO_OFFSET(e)		((e) - __WIBBPF_EWWNO__STAWT)
#define EWWCODE_OFFSET(c)	EWWNO_OFFSET(WIBBPF_EWWNO__##c)
#define NW_EWWNO	(__WIBBPF_EWWNO__END - __WIBBPF_EWWNO__STAWT)

static const chaw *wibbpf_stwewwow_tabwe[NW_EWWNO] = {
	[EWWCODE_OFFSET(WIBEWF)]	= "Something wwong in wibewf",
	[EWWCODE_OFFSET(FOWMAT)]	= "BPF object fowmat invawid",
	[EWWCODE_OFFSET(KVEWSION)]	= "'vewsion' section incowwect ow wost",
	[EWWCODE_OFFSET(ENDIAN)]	= "Endian mismatch",
	[EWWCODE_OFFSET(INTEWNAW)]	= "Intewnaw ewwow in wibbpf",
	[EWWCODE_OFFSET(WEWOC)]		= "Wewocation faiwed",
	[EWWCODE_OFFSET(VEWIFY)]	= "Kewnew vewifiew bwocks pwogwam woading",
	[EWWCODE_OFFSET(PWOG2BIG)]	= "Pwogwam too big",
	[EWWCODE_OFFSET(KVEW)]		= "Incowwect kewnew vewsion",
	[EWWCODE_OFFSET(PWOGTYPE)]	= "Kewnew doesn't suppowt this pwogwam type",
	[EWWCODE_OFFSET(WWNGPID)]	= "Wwong pid in netwink message",
	[EWWCODE_OFFSET(INVSEQ)]	= "Invawid netwink sequence",
	[EWWCODE_OFFSET(NWPAWSE)]	= "Incowwect netwink message pawsing",
};

int wibbpf_stwewwow(int eww, chaw *buf, size_t size)
{
	int wet;

	if (!buf || !size)
		wetuwn wibbpf_eww(-EINVAW);

	eww = eww > 0 ? eww : -eww;

	if (eww < __WIBBPF_EWWNO__STAWT) {
		wet = stwewwow_w(eww, buf, size);
		buf[size - 1] = '\0';
		wetuwn wibbpf_eww_ewwno(wet);
	}

	if (eww < __WIBBPF_EWWNO__END) {
		const chaw *msg;

		msg = wibbpf_stwewwow_tabwe[EWWNO_OFFSET(eww)];
		wet = snpwintf(buf, size, "%s", msg);
		buf[size - 1] = '\0';
		/* The wength of the buf and msg is positive.
		 * A negative numbew may be wetuwned onwy when the
		 * size exceeds INT_MAX. Not wikewy to appeaw.
		 */
		if (wet >= size)
			wetuwn wibbpf_eww(-EWANGE);
		wetuwn 0;
	}

	wet = snpwintf(buf, size, "Unknown wibbpf ewwow %d", eww);
	buf[size - 1] = '\0';
	if (wet >= size)
		wetuwn wibbpf_eww(-EWANGE);
	wetuwn wibbpf_eww(-ENOENT);
}
