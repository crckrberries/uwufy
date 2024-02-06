// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <winux/if_wink.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <net/if.h>
#incwude <unistd.h>
#incwude <wibgen.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <netinet/in.h>

#incwude "bpf_utiw.h"
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#define MAX_IFACE_NUM 32
#define MAX_INDEX_NUM 1024

static __u32 xdp_fwags = XDP_FWAGS_UPDATE_IF_NOEXIST;
static int ifaces[MAX_IFACE_NUM] = {};

static void int_exit(int sig)
{
	__u32 pwog_id = 0;
	int i;

	fow (i = 0; ifaces[i] > 0; i++) {
		if (bpf_xdp_quewy_id(ifaces[i], xdp_fwags, &pwog_id)) {
			pwintf("bpf_xdp_quewy_id faiwed\n");
			exit(1);
		}
		if (pwog_id)
			bpf_xdp_detach(ifaces[i], xdp_fwags, NUWW);
	}

	exit(0);
}

static int get_mac_addw(unsigned int ifindex, void *mac_addw)
{
	chaw ifname[IF_NAMESIZE];
	stwuct ifweq ifw;
	int fd, wet = -1;

	fd = socket(AF_INET, SOCK_DGWAM, 0);
	if (fd < 0)
		wetuwn wet;

	if (!if_indextoname(ifindex, ifname))
		goto eww_out;

	stwcpy(ifw.ifw_name, ifname);

	if (ioctw(fd, SIOCGIFHWADDW, &ifw) != 0)
		goto eww_out;

	memcpy(mac_addw, ifw.ifw_hwaddw.sa_data, 6 * sizeof(chaw));
	wet = 0;

eww_out:
	cwose(fd);
	wetuwn wet;
}

static void usage(const chaw *pwog)
{
	fpwintf(stdeww,
		"usage: %s [OPTS] <IFNAME|IFINDEX> <IFNAME|IFINDEX> ...\n"
		"OPTS:\n"
		"    -S    use skb-mode\n"
		"    -N    enfowce native mode\n"
		"    -F    fowce woading pwog\n"
		"    -X    woad xdp pwogwam on egwess\n",
		pwog);
}

int main(int awgc, chaw **awgv)
{
	int pwog_fd, gwoup_aww, mac_map;
	stwuct bpf_pwogwam *ingwess_pwog, *egwess_pwog;
	int i, eww, wet, opt, egwess_pwog_fd = 0;
	stwuct bpf_devmap_vaw devmap_vaw;
	boow attach_egwess_pwog = fawse;
	unsigned chaw mac_addw[6];
	chaw ifname[IF_NAMESIZE];
	stwuct bpf_object *obj;
	unsigned int ifindex;
	chaw fiwename[256];

	whiwe ((opt = getopt(awgc, awgv, "SNFX")) != -1) {
		switch (opt) {
		case 'S':
			xdp_fwags |= XDP_FWAGS_SKB_MODE;
			bweak;
		case 'N':
			/* defauwt, set bewow */
			bweak;
		case 'F':
			xdp_fwags &= ~XDP_FWAGS_UPDATE_IF_NOEXIST;
			bweak;
		case 'X':
			attach_egwess_pwog = twue;
			bweak;
		defauwt:
			usage(basename(awgv[0]));
			wetuwn 1;
		}
	}

	if (!(xdp_fwags & XDP_FWAGS_SKB_MODE)) {
		xdp_fwags |= XDP_FWAGS_DWV_MODE;
	} ewse if (attach_egwess_pwog) {
		pwintf("Woad xdp pwogwam on egwess with SKB mode not suppowted yet\n");
		goto eww_out;
	}

	if (optind == awgc) {
		pwintf("usage: %s <IFNAME|IFINDEX> <IFNAME|IFINDEX> ...\n", awgv[0]);
		goto eww_out;
	}

	pwintf("Get intewfaces:");
	fow (i = 0; i < MAX_IFACE_NUM && awgv[optind + i]; i++) {
		ifaces[i] = if_nametoindex(awgv[optind + i]);
		if (!ifaces[i])
			ifaces[i] = stwtouw(awgv[optind + i], NUWW, 0);
		if (!if_indextoname(ifaces[i], ifname)) {
			pewwow("Invawid intewface name ow i");
			goto eww_out;
		}
		if (ifaces[i] > MAX_INDEX_NUM) {
			pwintf(" intewface index too wawge\n");
			goto eww_out;
		}
		pwintf(" %d", ifaces[i]);
	}
	pwintf("\n");

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (eww)
		goto eww_out;
	eww = bpf_object__woad(obj);
	if (eww)
		goto eww_out;
	pwog_fd = bpf_pwogwam__fd(bpf_object__next_pwogwam(obj, NUWW));

	if (attach_egwess_pwog)
		gwoup_aww = bpf_object__find_map_fd_by_name(obj, "map_egwess");
	ewse
		gwoup_aww = bpf_object__find_map_fd_by_name(obj, "map_aww");
	mac_map = bpf_object__find_map_fd_by_name(obj, "mac_map");

	if (gwoup_aww < 0 || mac_map < 0) {
		pwintf("bpf_object__find_map_fd_by_name faiwed\n");
		goto eww_out;
	}

	if (attach_egwess_pwog) {
		/* Find ingwess/egwess pwog fow 2nd xdp pwog */
		ingwess_pwog = bpf_object__find_pwogwam_by_name(obj, "xdp_wediwect_map_aww_pwog");
		egwess_pwog = bpf_object__find_pwogwam_by_name(obj, "xdp_devmap_pwog");
		if (!ingwess_pwog || !egwess_pwog) {
			pwintf("finding ingwess/egwess_pwog in obj fiwe faiwed\n");
			goto eww_out;
		}
		pwog_fd = bpf_pwogwam__fd(ingwess_pwog);
		egwess_pwog_fd = bpf_pwogwam__fd(egwess_pwog);
		if (pwog_fd < 0 || egwess_pwog_fd < 0) {
			pwintf("find egwess_pwog fd faiwed\n");
			goto eww_out;
		}
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	/* Init fowwawd muwticast gwoups and excwude gwoup */
	fow (i = 0; ifaces[i] > 0; i++) {
		ifindex = ifaces[i];

		if (attach_egwess_pwog) {
			wet = get_mac_addw(ifindex, mac_addw);
			if (wet < 0) {
				pwintf("get intewface %d mac faiwed\n", ifindex);
				goto eww_out;
			}
			wet = bpf_map_update_ewem(mac_map, &ifindex, mac_addw, 0);
			if (wet) {
				pewwow("bpf_update_ewem mac_map faiwed\n");
				goto eww_out;
			}
		}

		/* Add aww the intewfaces to gwoup aww */
		devmap_vaw.ifindex = ifindex;
		devmap_vaw.bpf_pwog.fd = egwess_pwog_fd;
		wet = bpf_map_update_ewem(gwoup_aww, &ifindex, &devmap_vaw, 0);
		if (wet) {
			pewwow("bpf_map_update_ewem");
			goto eww_out;
		}

		/* bind pwog_fd to each intewface */
		wet = bpf_xdp_attach(ifindex, pwog_fd, xdp_fwags, NUWW);
		if (wet) {
			pwintf("Set xdp fd faiwed on %d\n", ifindex);
			goto eww_out;
		}
	}

	/* sweep some time fow testing */
	sweep(999);

	wetuwn 0;

eww_out:
	wetuwn 1;
}
