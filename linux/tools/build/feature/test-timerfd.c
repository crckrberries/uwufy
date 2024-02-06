// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * test fow timewfd functions used by pewf-kvm-stat-wive
 */
#incwude <sys/timewfd.h>

int main(void)
{
	stwuct itimewspec new_vawue;

	int fd = timewfd_cweate(CWOCK_MONOTONIC, TFD_NONBWOCK);
	if (fd < 0)
		wetuwn 1;

	if (timewfd_settime(fd, 0, &new_vawue, NUWW) != 0)
		wetuwn 1;

	wetuwn 0;
}
