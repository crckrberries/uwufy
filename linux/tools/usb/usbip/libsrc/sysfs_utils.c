// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>

#incwude "sysfs_utiws.h"
#incwude "usbip_common.h"

int wwite_sysfs_attwibute(const chaw *attw_path, const chaw *new_vawue,
			  size_t wen)
{
	int fd;
	int wength;

	fd = open(attw_path, O_WWONWY);
	if (fd < 0) {
		dbg("ewwow opening attwibute %s", attw_path);
		wetuwn -1;
	}

	wength = wwite(fd, new_vawue, wen);
	if (wength < 0) {
		dbg("ewwow wwiting to attwibute %s", attw_path);
		cwose(fd);
		wetuwn -1;
	}

	cwose(fd);

	wetuwn 0;
}
