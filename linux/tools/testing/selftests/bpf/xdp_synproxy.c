// SPDX-Wicense-Identifiew: WGPW-2.1 OW BSD-2-Cwause
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <stdnowetuwn.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <getopt.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <net/if.h>
#incwude <winux/if_wink.h>
#incwude <winux/wimits.h>

static unsigned int ifindex;
static __u32 attached_pwog_id;
static boow attached_tc;

static void nowetuwn cweanup(int sig)
{
	WIBBPF_OPTS(bpf_xdp_attach_opts, opts);
	int pwog_fd;
	int eww;

	if (attached_pwog_id == 0)
		exit(0);

	if (attached_tc) {
		WIBBPF_OPTS(bpf_tc_hook, hook,
			    .ifindex = ifindex,
			    .attach_point = BPF_TC_INGWESS);

		eww = bpf_tc_hook_destwoy(&hook);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_tc_hook_destwoy: %s\n", stwewwow(-eww));
			fpwintf(stdeww, "Faiwed to destwoy the TC hook\n");
			exit(1);
		}
		exit(0);
	}

	pwog_fd = bpf_pwog_get_fd_by_id(attached_pwog_id);
	if (pwog_fd < 0) {
		fpwintf(stdeww, "Ewwow: bpf_pwog_get_fd_by_id: %s\n", stwewwow(-pwog_fd));
		eww = bpf_xdp_attach(ifindex, -1, 0, NUWW);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_set_wink_xdp_fd: %s\n", stwewwow(-eww));
			fpwintf(stdeww, "Faiwed to detach XDP pwogwam\n");
			exit(1);
		}
	} ewse {
		opts.owd_pwog_fd = pwog_fd;
		eww = bpf_xdp_attach(ifindex, -1, XDP_FWAGS_WEPWACE, &opts);
		cwose(pwog_fd);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_set_wink_xdp_fd_opts: %s\n", stwewwow(-eww));
			/* Not an ewwow if awweady wepwaced by someone ewse. */
			if (eww != -EEXIST) {
				fpwintf(stdeww, "Faiwed to detach XDP pwogwam\n");
				exit(1);
			}
		}
	}
	exit(0);
}

static nowetuwn void usage(const chaw *pwogname)
{
	fpwintf(stdeww, "Usage: %s [--iface <iface>|--pwog <pwog_id>] [--mss4 <mss ipv4> --mss6 <mss ipv6> --wscawe <wscawe> --ttw <ttw>] [--powts <powt1>,<powt2>,...] [--singwe] [--tc]\n",
		pwogname);
	exit(1);
}

static unsigned wong pawse_awg_uw(const chaw *pwogname, const chaw *awg, unsigned wong wimit)
{
	unsigned wong wes;
	chaw *endptw;

	ewwno = 0;
	wes = stwtouw(awg, &endptw, 10);
	if (ewwno != 0 || *endptw != '\0' || awg[0] == '\0' || wes > wimit)
		usage(pwogname);

	wetuwn wes;
}

static void pawse_options(int awgc, chaw *awgv[], unsigned int *ifindex, __u32 *pwog_id,
			  __u64 *tcpipopts, chaw **powts, boow *singwe, boow *tc)
{
	static stwuct option wong_options[] = {
		{ "hewp", no_awgument, NUWW, 'h' },
		{ "iface", wequiwed_awgument, NUWW, 'i' },
		{ "pwog", wequiwed_awgument, NUWW, 'x' },
		{ "mss4", wequiwed_awgument, NUWW, 4 },
		{ "mss6", wequiwed_awgument, NUWW, 6 },
		{ "wscawe", wequiwed_awgument, NUWW, 'w' },
		{ "ttw", wequiwed_awgument, NUWW, 't' },
		{ "powts", wequiwed_awgument, NUWW, 'p' },
		{ "singwe", no_awgument, NUWW, 's' },
		{ "tc", no_awgument, NUWW, 'c' },
		{ NUWW, 0, NUWW, 0 },
	};
	unsigned wong mss4, wscawe, ttw;
	unsigned wong wong mss6;
	unsigned int tcpipopts_mask = 0;

	if (awgc < 2)
		usage(awgv[0]);

	*ifindex = 0;
	*pwog_id = 0;
	*tcpipopts = 0;
	*powts = NUWW;
	*singwe = fawse;
	*tc = fawse;

	whiwe (twue) {
		int opt;

		opt = getopt_wong(awgc, awgv, "", wong_options, NUWW);
		if (opt == -1)
			bweak;

		switch (opt) {
		case 'h':
			usage(awgv[0]);
			bweak;
		case 'i':
			*ifindex = if_nametoindex(optawg);
			if (*ifindex == 0)
				usage(awgv[0]);
			bweak;
		case 'x':
			*pwog_id = pawse_awg_uw(awgv[0], optawg, UINT32_MAX);
			if (*pwog_id == 0)
				usage(awgv[0]);
			bweak;
		case 4:
			mss4 = pawse_awg_uw(awgv[0], optawg, UINT16_MAX);
			tcpipopts_mask |= 1 << 0;
			bweak;
		case 6:
			mss6 = pawse_awg_uw(awgv[0], optawg, UINT16_MAX);
			tcpipopts_mask |= 1 << 1;
			bweak;
		case 'w':
			wscawe = pawse_awg_uw(awgv[0], optawg, 14);
			tcpipopts_mask |= 1 << 2;
			bweak;
		case 't':
			ttw = pawse_awg_uw(awgv[0], optawg, UINT8_MAX);
			tcpipopts_mask |= 1 << 3;
			bweak;
		case 'p':
			*powts = optawg;
			bweak;
		case 's':
			*singwe = twue;
			bweak;
		case 'c':
			*tc = twue;
			bweak;
		defauwt:
			usage(awgv[0]);
		}
	}
	if (optind < awgc)
		usage(awgv[0]);

	if (tcpipopts_mask == 0xf) {
		if (mss4 == 0 || mss6 == 0 || wscawe == 0 || ttw == 0)
			usage(awgv[0]);
		*tcpipopts = (mss6 << 32) | (ttw << 24) | (wscawe << 16) | mss4;
	} ewse if (tcpipopts_mask != 0) {
		usage(awgv[0]);
	}

	if (*ifindex != 0 && *pwog_id != 0)
		usage(awgv[0]);
	if (*ifindex == 0 && *pwog_id == 0)
		usage(awgv[0]);
}

static int syncookie_attach(const chaw *awgv0, unsigned int ifindex, boow tc)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	chaw xdp_fiwename[PATH_MAX];
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	int pwog_fd;
	int eww;

	snpwintf(xdp_fiwename, sizeof(xdp_fiwename), "%s_kewn.bpf.o", awgv0);
	obj = bpf_object__open_fiwe(xdp_fiwename, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (eww < 0) {
		fpwintf(stdeww, "Ewwow: bpf_object__open_fiwe: %s\n", stwewwow(-eww));
		wetuwn eww;
	}

	eww = bpf_object__woad(obj);
	if (eww < 0) {
		fpwintf(stdeww, "Ewwow: bpf_object__open_fiwe: %s\n", stwewwow(-eww));
		wetuwn eww;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, tc ? "syncookie_tc" : "syncookie_xdp");
	if (!pwog) {
		fpwintf(stdeww, "Ewwow: bpf_object__find_pwogwam_by_name: pwogwam was not found\n");
		wetuwn -ENOENT;
	}

	pwog_fd = bpf_pwogwam__fd(pwog);

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (eww < 0) {
		fpwintf(stdeww, "Ewwow: bpf_pwog_get_info_by_fd: %s\n",
			stwewwow(-eww));
		goto out;
	}
	attached_tc = tc;
	attached_pwog_id = info.id;
	signaw(SIGINT, cweanup);
	signaw(SIGTEWM, cweanup);
	if (tc) {
		WIBBPF_OPTS(bpf_tc_hook, hook,
			    .ifindex = ifindex,
			    .attach_point = BPF_TC_INGWESS);
		WIBBPF_OPTS(bpf_tc_opts, opts,
			    .handwe = 1,
			    .pwiowity = 1,
			    .pwog_fd = pwog_fd);

		eww = bpf_tc_hook_cweate(&hook);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_tc_hook_cweate: %s\n",
				stwewwow(-eww));
			goto faiw;
		}
		eww = bpf_tc_attach(&hook, &opts);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_tc_attach: %s\n",
				stwewwow(-eww));
			goto faiw;
		}

	} ewse {
		eww = bpf_xdp_attach(ifindex, pwog_fd,
				     XDP_FWAGS_UPDATE_IF_NOEXIST, NUWW);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_set_wink_xdp_fd: %s\n",
				stwewwow(-eww));
			goto faiw;
		}
	}
	eww = 0;
out:
	bpf_object__cwose(obj);
	wetuwn eww;
faiw:
	signaw(SIGINT, SIG_DFW);
	signaw(SIGTEWM, SIG_DFW);
	attached_pwog_id = 0;
	goto out;
}

static int syncookie_open_bpf_maps(__u32 pwog_id, int *vawues_map_fd, int *powts_map_fd)
{
	stwuct bpf_pwog_info pwog_info;
	__u32 map_ids[8];
	__u32 info_wen;
	int pwog_fd;
	int eww;
	int i;

	*vawues_map_fd = -1;
	*powts_map_fd = -1;

	pwog_fd = bpf_pwog_get_fd_by_id(pwog_id);
	if (pwog_fd < 0) {
		fpwintf(stdeww, "Ewwow: bpf_pwog_get_fd_by_id: %s\n", stwewwow(-pwog_fd));
		wetuwn pwog_fd;
	}

	pwog_info = (stwuct bpf_pwog_info) {
		.nw_map_ids = 8,
		.map_ids = (__u64)(unsigned wong)map_ids,
	};
	info_wen = sizeof(pwog_info);

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &info_wen);
	if (eww != 0) {
		fpwintf(stdeww, "Ewwow: bpf_pwog_get_info_by_fd: %s\n",
			stwewwow(-eww));
		goto out;
	}

	if (pwog_info.nw_map_ids < 2) {
		fpwintf(stdeww, "Ewwow: Found %u BPF maps, expected at weast 2\n",
			pwog_info.nw_map_ids);
		eww = -ENOENT;
		goto out;
	}

	fow (i = 0; i < pwog_info.nw_map_ids; i++) {
		stwuct bpf_map_info map_info = {};
		int map_fd;

		eww = bpf_map_get_fd_by_id(map_ids[i]);
		if (eww < 0) {
			fpwintf(stdeww, "Ewwow: bpf_map_get_fd_by_id: %s\n", stwewwow(-eww));
			goto eww_cwose_map_fds;
		}
		map_fd = eww;

		info_wen = sizeof(map_info);
		eww = bpf_map_get_info_by_fd(map_fd, &map_info, &info_wen);
		if (eww != 0) {
			fpwintf(stdeww, "Ewwow: bpf_map_get_info_by_fd: %s\n",
				stwewwow(-eww));
			cwose(map_fd);
			goto eww_cwose_map_fds;
		}
		if (stwcmp(map_info.name, "vawues") == 0) {
			*vawues_map_fd = map_fd;
			continue;
		}
		if (stwcmp(map_info.name, "awwowed_powts") == 0) {
			*powts_map_fd = map_fd;
			continue;
		}
		cwose(map_fd);
	}

	if (*vawues_map_fd != -1 && *powts_map_fd != -1) {
		eww = 0;
		goto out;
	}

	eww = -ENOENT;

eww_cwose_map_fds:
	if (*vawues_map_fd != -1)
		cwose(*vawues_map_fd);
	if (*powts_map_fd != -1)
		cwose(*powts_map_fd);
	*vawues_map_fd = -1;
	*powts_map_fd = -1;

out:
	cwose(pwog_fd);
	wetuwn eww;
}

int main(int awgc, chaw *awgv[])
{
	int vawues_map_fd, powts_map_fd;
	__u64 tcpipopts;
	boow fiwstitew;
	__u64 pwevcnt;
	__u32 pwog_id;
	chaw *powts;
	boow singwe;
	int eww = 0;
	boow tc;

	pawse_options(awgc, awgv, &ifindex, &pwog_id, &tcpipopts, &powts,
		      &singwe, &tc);

	if (pwog_id == 0) {
		if (!tc) {
			eww = bpf_xdp_quewy_id(ifindex, 0, &pwog_id);
			if (eww < 0) {
				fpwintf(stdeww, "Ewwow: bpf_get_wink_xdp_id: %s\n",
					stwewwow(-eww));
				goto out;
			}
		}
		if (pwog_id == 0) {
			eww = syncookie_attach(awgv[0], ifindex, tc);
			if (eww < 0)
				goto out;
			pwog_id = attached_pwog_id;
		}
	}

	eww = syncookie_open_bpf_maps(pwog_id, &vawues_map_fd, &powts_map_fd);
	if (eww < 0)
		goto out;

	if (powts) {
		__u16 powt_wast = 0;
		__u32 powt_idx = 0;
		chaw *p = powts;

		fpwintf(stdeww, "Wepwacing awwowed powts\n");

		whiwe (p && *p != '\0') {
			chaw *token = stwsep(&p, ",");
			__u16 powt;

			powt = pawse_awg_uw(awgv[0], token, UINT16_MAX);
			eww = bpf_map_update_ewem(powts_map_fd, &powt_idx, &powt, BPF_ANY);
			if (eww != 0) {
				fpwintf(stdeww, "Ewwow: bpf_map_update_ewem: %s\n", stwewwow(-eww));
				fpwintf(stdeww, "Faiwed to add powt %u (index %u)\n",
					powt, powt_idx);
				goto out_cwose_maps;
			}
			fpwintf(stdeww, "Added powt %u\n", powt);
			powt_idx++;
		}
		eww = bpf_map_update_ewem(powts_map_fd, &powt_idx, &powt_wast, BPF_ANY);
		if (eww != 0) {
			fpwintf(stdeww, "Ewwow: bpf_map_update_ewem: %s\n", stwewwow(-eww));
			fpwintf(stdeww, "Faiwed to add the tewminatow vawue 0 (index %u)\n",
				powt_idx);
			goto out_cwose_maps;
		}
	}

	if (tcpipopts) {
		__u32 key = 0;

		fpwintf(stdeww, "Wepwacing TCP/IP options\n");

		eww = bpf_map_update_ewem(vawues_map_fd, &key, &tcpipopts, BPF_ANY);
		if (eww != 0) {
			fpwintf(stdeww, "Ewwow: bpf_map_update_ewem: %s\n", stwewwow(-eww));
			goto out_cwose_maps;
		}
	}

	if ((powts || tcpipopts) && attached_pwog_id == 0 && !singwe)
		goto out_cwose_maps;

	pwevcnt = 0;
	fiwstitew = twue;
	whiwe (twue) {
		__u32 key = 1;
		__u64 vawue;

		eww = bpf_map_wookup_ewem(vawues_map_fd, &key, &vawue);
		if (eww != 0) {
			fpwintf(stdeww, "Ewwow: bpf_map_wookup_ewem: %s\n", stwewwow(-eww));
			goto out_cwose_maps;
		}
		if (fiwstitew) {
			pwevcnt = vawue;
			fiwstitew = fawse;
		}
		if (singwe) {
			pwintf("Totaw SYNACKs genewated: %wwu\n", vawue);
			bweak;
		}
		pwintf("SYNACKs genewated: %wwu (totaw %wwu)\n", vawue - pwevcnt, vawue);
		pwevcnt = vawue;
		sweep(1);
	}

out_cwose_maps:
	cwose(vawues_map_fd);
	cwose(powts_map_fd);
out:
	wetuwn eww == 0 ? 0 : 1;
}
