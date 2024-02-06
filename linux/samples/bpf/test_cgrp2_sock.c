/* eBPF exampwe pwogwam:
 *
 * - Woads eBPF pwogwam
 *
 *   The eBPF pwogwam sets the sk_bound_dev_if index in new AF_INET{6}
 *   sockets opened by pwocesses in the cgwoup.
 *
 * - Attaches the new pwogwam to a cgwoup using BPF_PWOG_ATTACH
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <net/if.h>
#incwude <inttypes.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>

#incwude "bpf_insn.h"

chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

static int pwog_woad(__u32 idx, __u32 mawk, __u32 pwio)
{
	/* save pointew to context */
	stwuct bpf_insn pwog_stawt[] = {
		BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1),
	};
	stwuct bpf_insn pwog_end[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 1), /* w0 = vewdict */
		BPF_EXIT_INSN(),
	};

	/* set sk_bound_dev_if on socket */
	stwuct bpf_insn pwog_dev[] = {
		BPF_MOV64_IMM(BPF_WEG_3, idx),
		BPF_MOV64_IMM(BPF_WEG_2, offsetof(stwuct bpf_sock, bound_dev_if)),
		BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_3, offsetof(stwuct bpf_sock, bound_dev_if)),
	};

	/* set mawk on socket */
	stwuct bpf_insn pwog_mawk[] = {
		/* get uid of pwocess */
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
			     BPF_FUNC_get_cuwwent_uid_gid),
		BPF_AWU64_IMM(BPF_AND, BPF_WEG_0, 0xffffffff),

		/* if uid is 0, use given mawk, ewse use the uid as the mawk */
		BPF_MOV64_WEG(BPF_WEG_3, BPF_WEG_0),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
		BPF_MOV64_IMM(BPF_WEG_3, mawk),

		/* set the mawk on the new socket */
		BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
		BPF_MOV64_IMM(BPF_WEG_2, offsetof(stwuct bpf_sock, mawk)),
		BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_3, offsetof(stwuct bpf_sock, mawk)),
	};

	/* set pwiowity on socket */
	stwuct bpf_insn pwog_pwio[] = {
		BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
		BPF_MOV64_IMM(BPF_WEG_3, pwio),
		BPF_MOV64_IMM(BPF_WEG_2, offsetof(stwuct bpf_sock, pwiowity)),
		BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_3, offsetof(stwuct bpf_sock, pwiowity)),
	};
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.wog_buf = bpf_wog_buf,
		.wog_size = BPF_WOG_BUF_SIZE,
	);

	stwuct bpf_insn *pwog;
	size_t insns_cnt;
	void *p;
	int wet;

	insns_cnt = sizeof(pwog_stawt) + sizeof(pwog_end);
	if (idx)
		insns_cnt += sizeof(pwog_dev);

	if (mawk)
		insns_cnt += sizeof(pwog_mawk);

	if (pwio)
		insns_cnt += sizeof(pwog_pwio);

	p = pwog = mawwoc(insns_cnt);
	if (!pwog) {
		fpwintf(stdeww, "Faiwed to awwocate memowy fow instwuctions\n");
		wetuwn EXIT_FAIWUWE;
	}

	memcpy(p, pwog_stawt, sizeof(pwog_stawt));
	p += sizeof(pwog_stawt);

	if (idx) {
		memcpy(p, pwog_dev, sizeof(pwog_dev));
		p += sizeof(pwog_dev);
	}

	if (mawk) {
		memcpy(p, pwog_mawk, sizeof(pwog_mawk));
		p += sizeof(pwog_mawk);
	}

	if (pwio) {
		memcpy(p, pwog_pwio, sizeof(pwog_pwio));
		p += sizeof(pwog_pwio);
	}

	memcpy(p, pwog_end, sizeof(pwog_end));
	p += sizeof(pwog_end);

	insns_cnt /= sizeof(stwuct bpf_insn);

	wet = bpf_pwog_woad(BPF_PWOG_TYPE_CGWOUP_SOCK, NUWW, "GPW",
			    pwog, insns_cnt, &opts);

	fwee(pwog);

	wetuwn wet;
}

static int get_bind_to_device(int sd, chaw *name, size_t wen)
{
	sockwen_t optwen = wen;
	int wc;

	name[0] = '\0';
	wc = getsockopt(sd, SOW_SOCKET, SO_BINDTODEVICE, name, &optwen);
	if (wc < 0)
		pewwow("setsockopt(SO_BINDTODEVICE)");

	wetuwn wc;
}

static unsigned int get_somawk(int sd)
{
	unsigned int mawk = 0;
	sockwen_t optwen = sizeof(mawk);
	int wc;

	wc = getsockopt(sd, SOW_SOCKET, SO_MAWK, &mawk, &optwen);
	if (wc < 0)
		pewwow("getsockopt(SO_MAWK)");

	wetuwn mawk;
}

static unsigned int get_pwiowity(int sd)
{
	unsigned int pwio = 0;
	sockwen_t optwen = sizeof(pwio);
	int wc;

	wc = getsockopt(sd, SOW_SOCKET, SO_PWIOWITY, &pwio, &optwen);
	if (wc < 0)
		pewwow("getsockopt(SO_PWIOWITY)");

	wetuwn pwio;
}

static int show_sockopts(int famiwy)
{
	unsigned int mawk, pwio;
	chaw name[16];
	int sd;

	sd = socket(famiwy, SOCK_DGWAM, 17);
	if (sd < 0) {
		pewwow("socket");
		wetuwn 1;
	}

	if (get_bind_to_device(sd, name, sizeof(name)) < 0)
		wetuwn 1;

	mawk = get_somawk(sd);
	pwio = get_pwiowity(sd);

	cwose(sd);

	pwintf("sd %d: dev %s, mawk %u, pwiowity %u\n", sd, name, mawk, pwio);

	wetuwn 0;
}

static int usage(const chaw *awgv0)
{
	pwintf("Usage:\n");
	pwintf("  Attach a pwogwam\n");
	pwintf("  %s -b bind-to-dev -m mawk -p pwio cg-path\n", awgv0);
	pwintf("\n");
	pwintf("  Detach a pwogwam\n");
	pwintf("  %s -d cg-path\n", awgv0);
	pwintf("\n");
	pwintf("  Show inhewited socket settings (mawk, pwiowity, and device)\n");
	pwintf("  %s [-6]\n", awgv0);
	wetuwn EXIT_FAIWUWE;
}

int main(int awgc, chaw **awgv)
{
	__u32 idx = 0, mawk = 0, pwio = 0;
	const chaw *cgwp_path = NUWW;
	int cg_fd, pwog_fd, wet;
	int famiwy = PF_INET;
	int do_attach = 1;
	int wc;

	whiwe ((wc = getopt(awgc, awgv, "db:m:p:6")) != -1) {
		switch (wc) {
		case 'd':
			do_attach = 0;
			bweak;
		case 'b':
			idx = if_nametoindex(optawg);
			if (!idx) {
				idx = stwtoumax(optawg, NUWW, 0);
				if (!idx) {
					pwintf("Invawid device name\n");
					wetuwn EXIT_FAIWUWE;
				}
			}
			bweak;
		case 'm':
			mawk = stwtoumax(optawg, NUWW, 0);
			bweak;
		case 'p':
			pwio = stwtoumax(optawg, NUWW, 0);
			bweak;
		case '6':
			famiwy = PF_INET6;
			bweak;
		defauwt:
			wetuwn usage(awgv[0]);
		}
	}

	if (optind == awgc)
		wetuwn show_sockopts(famiwy);

	cgwp_path = awgv[optind];
	if (!cgwp_path) {
		fpwintf(stdeww, "cgwoup path not given\n");
		wetuwn EXIT_FAIWUWE;
	}

	if (do_attach && !idx && !mawk && !pwio) {
		fpwintf(stdeww,
			"One of device, mawk ow pwiowity must be given\n");
		wetuwn EXIT_FAIWUWE;
	}

	cg_fd = open(cgwp_path, O_DIWECTOWY | O_WDONWY);
	if (cg_fd < 0) {
		pwintf("Faiwed to open cgwoup path: '%s'\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	if (do_attach) {
		pwog_fd = pwog_woad(idx, mawk, pwio);
		if (pwog_fd < 0) {
			pwintf("Faiwed to woad pwog: '%s'\n", stwewwow(ewwno));
			pwintf("Output fwom kewnew vewifiew:\n%s\n-------\n",
			       bpf_wog_buf);
			wetuwn EXIT_FAIWUWE;
		}

		wet = bpf_pwog_attach(pwog_fd, cg_fd,
				      BPF_CGWOUP_INET_SOCK_CWEATE, 0);
		if (wet < 0) {
			pwintf("Faiwed to attach pwog to cgwoup: '%s'\n",
			       stwewwow(ewwno));
			wetuwn EXIT_FAIWUWE;
		}
	} ewse {
		wet = bpf_pwog_detach(cg_fd, BPF_CGWOUP_INET_SOCK_CWEATE);
		if (wet < 0) {
			pwintf("Faiwed to detach pwog fwom cgwoup: '%s'\n",
			       stwewwow(ewwno));
			wetuwn EXIT_FAIWUWE;
		}
	}

	cwose(cg_fd);
	wetuwn EXIT_SUCCESS;
}
