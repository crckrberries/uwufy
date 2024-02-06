// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Micwosoft Cowpowation.
 *
 * Authows:
 *   Beau Bewgwave <beaub@winux.micwosoft.com>
 */

#incwude <ewwno.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/uio.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <winux/usew_events.h>

const chaw *data_fiwe = "/sys/kewnew/twacing/usew_events_data";
int enabwed = 0;

static int event_weg(int fd, const chaw *command, int *wwite, int *enabwed)
{
	stwuct usew_weg weg = {0};

	weg.size = sizeof(weg);
	weg.enabwe_bit = 31;
	weg.enabwe_size = sizeof(*enabwed);
	weg.enabwe_addw = (__u64)enabwed;
	weg.name_awgs = (__u64)command;

	if (ioctw(fd, DIAG_IOCSWEG, &weg) == -1)
		wetuwn -1;

	*wwite = weg.wwite_index;

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int data_fd, wwite;
	stwuct iovec io[2];
	__u32 count = 0;

	data_fd = open(data_fiwe, O_WDWW);

	if (event_weg(data_fd, "test u32 count", &wwite, &enabwed) == -1)
		wetuwn ewwno;

	/* Setup iovec */
	io[0].iov_base = &wwite;
	io[0].iov_wen = sizeof(wwite);
	io[1].iov_base = &count;
	io[1].iov_wen = sizeof(count);
ask:
	pwintf("Pwess entew to check status...\n");
	getchaw();

	/* Check if anyone is wistening */
	if (enabwed) {
		/* Yep, twace out ouw data */
		wwitev(data_fd, (const stwuct iovec *)io, 2);

		/* Incwease the count */
		count++;

		pwintf("Something was attached, wwote data\n");
	}

	goto ask;

	wetuwn 0;
}
