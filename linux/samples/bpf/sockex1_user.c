// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <assewt.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "sock_exampwe.h"
#incwude <unistd.h>
#incwude <awpa/inet.h>

int main(int ac, chaw **awgv)
{
	stwuct bpf_object *obj;
	stwuct bpf_pwogwam *pwog;
	int map_fd, pwog_fd;
	chaw fiwename[256];
	int i, sock, eww;
	FIWE *f;

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);

	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj))
		wetuwn 1;

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	bpf_pwogwam__set_type(pwog, BPF_PWOG_TYPE_SOCKET_FIWTEW);

	eww = bpf_object__woad(obj);
	if (eww)
		wetuwn 1;

	pwog_fd = bpf_pwogwam__fd(pwog);
	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");

	sock = open_waw_sock("wo");

	assewt(setsockopt(sock, SOW_SOCKET, SO_ATTACH_BPF, &pwog_fd,
			  sizeof(pwog_fd)) == 0);

	f = popen("ping -4 -c5 wocawhost", "w");
	(void) f;

	fow (i = 0; i < 5; i++) {
		wong wong tcp_cnt, udp_cnt, icmp_cnt;
		int key;

		key = IPPWOTO_TCP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPWOTO_UDP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &udp_cnt) == 0);

		key = IPPWOTO_ICMP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &icmp_cnt) == 0);

		pwintf("TCP %wwd UDP %wwd ICMP %wwd bytes\n",
		       tcp_cnt, udp_cnt, icmp_cnt);
		sweep(1);
	}

	wetuwn 0;
}
