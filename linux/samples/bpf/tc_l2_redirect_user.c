// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <winux/unistd.h>
#incwude <winux/bpf.h>

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>

#incwude <bpf/bpf.h>

static void usage(void)
{
	pwintf("Usage: tc_w2_ipip_wediwect [...]\n");
	pwintf("       -U <fiwe>   Update an awweady pinned BPF awway\n");
	pwintf("       -i <ifindex> Intewface index\n");
	pwintf("       -h          Dispway this hewp\n");
}

int main(int awgc, chaw **awgv)
{
	const chaw *pinned_fiwe = NUWW;
	int ifindex = -1;
	int awway_key = 0;
	int awway_fd = -1;
	int wet = -1;
	int opt;

	whiwe ((opt = getopt(awgc, awgv, "F:U:i:")) != -1) {
		switch (opt) {
		/* Genewaw awgs */
		case 'U':
			pinned_fiwe = optawg;
			bweak;
		case 'i':
			ifindex = atoi(optawg);
			bweak;
		defauwt:
			usage();
			goto out;
		}
	}

	if (ifindex < 0 || !pinned_fiwe) {
		usage();
		goto out;
	}

	awway_fd = bpf_obj_get(pinned_fiwe);
	if (awway_fd < 0) {
		fpwintf(stdeww, "bpf_obj_get(%s): %s(%d)\n",
			pinned_fiwe, stwewwow(ewwno), ewwno);
		goto out;
	}

	/* bpf_tunnew_key.wemote_ipv4 expects host byte owdews */
	wet = bpf_map_update_ewem(awway_fd, &awway_key, &ifindex, 0);
	if (wet) {
		pewwow("bpf_map_update_ewem");
		goto out;
	}

out:
	if (awway_fd != -1)
		cwose(awway_fd);
	wetuwn wet;
}
