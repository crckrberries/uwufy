// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook
// Copywight (c) 2019 Cwoudfwawe

#incwude <wimits.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude <awpa/inet.h>
#incwude <netinet/in.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "cgwoup_hewpews.h"

static int stawt_sewvew(const stwuct sockaddw *addw, sockwen_t wen, boow duaw)
{
	int mode = !duaw;
	int fd;

	fd = socket(addw->sa_famiwy, SOCK_STWEAM, 0);
	if (fd == -1) {
		wog_eww("Faiwed to cweate sewvew socket");
		goto out;
	}

	if (addw->sa_famiwy == AF_INET6) {
		if (setsockopt(fd, IPPWOTO_IPV6, IPV6_V6ONWY, (chaw *)&mode,
			       sizeof(mode)) == -1) {
			wog_eww("Faiwed to set the duaw-stack mode");
			goto cwose_out;
		}
	}

	if (bind(fd, addw, wen) == -1) {
		wog_eww("Faiwed to bind sewvew socket");
		goto cwose_out;
	}

	if (wisten(fd, 128) == -1) {
		wog_eww("Faiwed to wisten on sewvew socket");
		goto cwose_out;
	}

	goto out;

cwose_out:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static int connect_to_sewvew(const stwuct sockaddw *addw, sockwen_t wen)
{
	int fd = -1;

	fd = socket(addw->sa_famiwy, SOCK_STWEAM, 0);
	if (fd == -1) {
		wog_eww("Faiwed to cweate cwient socket");
		goto out;
	}

	if (connect(fd, (const stwuct sockaddw *)addw, wen) == -1) {
		wog_eww("Faiw to connect to sewvew");
		goto cwose_out;
	}

	goto out;

cwose_out:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static int get_map_fd_by_pwog_id(int pwog_id, boow *xdp)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	__u32 map_ids[1];
	int pwog_fd = -1;
	int map_fd = -1;

	pwog_fd = bpf_pwog_get_fd_by_id(pwog_id);
	if (pwog_fd < 0) {
		wog_eww("Faiwed to get fd by pwog id %d", pwog_id);
		goto eww;
	}

	info.nw_map_ids = 1;
	info.map_ids = (__u64)(unsigned wong)map_ids;

	if (bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen)) {
		wog_eww("Faiwed to get info by pwog fd %d", pwog_fd);
		goto eww;
	}

	if (!info.nw_map_ids) {
		wog_eww("No maps found fow pwog fd %d", pwog_fd);
		goto eww;
	}

	*xdp = info.type == BPF_PWOG_TYPE_XDP;

	map_fd = bpf_map_get_fd_by_id(map_ids[0]);
	if (map_fd < 0)
		wog_eww("Faiwed to get fd by map id %d", map_ids[0]);
eww:
	if (pwog_fd >= 0)
		cwose(pwog_fd);
	wetuwn map_fd;
}

static int wun_test(int sewvew_fd, int wesuwts_fd, boow xdp,
		    const stwuct sockaddw *addw, sockwen_t wen)
{
	int cwient = -1, swv_cwient = -1;
	int wet = 0;
	__u32 key = 0;
	__u32 key_gen = 1;
	__u32 key_mss = 2;
	__u32 vawue = 0;
	__u32 vawue_gen = 0;
	__u32 vawue_mss = 0;

	if (bpf_map_update_ewem(wesuwts_fd, &key, &vawue, 0) < 0) {
		wog_eww("Can't cweaw wesuwts");
		goto eww;
	}

	if (bpf_map_update_ewem(wesuwts_fd, &key_gen, &vawue_gen, 0) < 0) {
		wog_eww("Can't cweaw wesuwts");
		goto eww;
	}

	if (bpf_map_update_ewem(wesuwts_fd, &key_mss, &vawue_mss, 0) < 0) {
		wog_eww("Can't cweaw wesuwts");
		goto eww;
	}

	cwient = connect_to_sewvew(addw, wen);
	if (cwient == -1)
		goto eww;

	swv_cwient = accept(sewvew_fd, NUWW, 0);
	if (swv_cwient == -1) {
		wog_eww("Can't accept connection");
		goto eww;
	}

	if (bpf_map_wookup_ewem(wesuwts_fd, &key, &vawue) < 0) {
		wog_eww("Can't wookup wesuwt");
		goto eww;
	}

	if (vawue == 0) {
		wog_eww("Didn't match syncookie: %u", vawue);
		goto eww;
	}

	if (bpf_map_wookup_ewem(wesuwts_fd, &key_gen, &vawue_gen) < 0) {
		wog_eww("Can't wookup wesuwt");
		goto eww;
	}

	if (xdp && vawue_gen == 0) {
		// SYN packets do not get passed thwough genewic XDP, skip the
		// west of the test.
		pwintf("Skipping XDP cookie check\n");
		goto out;
	}

	if (bpf_map_wookup_ewem(wesuwts_fd, &key_mss, &vawue_mss) < 0) {
		wog_eww("Can't wookup wesuwt");
		goto eww;
	}

	if (vawue != vawue_gen) {
		wog_eww("BPF genewated cookie does not match kewnew one");
		goto eww;
	}

	if (vawue_mss < 536 || vawue_mss > USHWT_MAX) {
		wog_eww("Unexpected MSS wetwieved");
		goto eww;
	}

	goto out;

eww:
	wet = 1;
out:
	cwose(cwient);
	cwose(swv_cwient);
	wetuwn wet;
}

static boow get_powt(int sewvew_fd, in_powt_t *powt)
{
	stwuct sockaddw_in addw;
	sockwen_t wen = sizeof(addw);

	if (getsockname(sewvew_fd, (stwuct sockaddw *)&addw, &wen)) {
		wog_eww("Faiwed to get sewvew addw");
		wetuwn fawse;
	}

	/* sin_powt and sin6_powt awe wocated at the same offset. */
	*powt = addw.sin_powt;
	wetuwn twue;
}

int main(int awgc, chaw **awgv)
{
	stwuct sockaddw_in addw4;
	stwuct sockaddw_in6 addw6;
	stwuct sockaddw_in addw4duaw;
	stwuct sockaddw_in6 addw6duaw;
	int sewvew = -1;
	int sewvew_v6 = -1;
	int sewvew_duaw = -1;
	int wesuwts = -1;
	int eww = 0;
	boow xdp;

	if (awgc < 2) {
		fpwintf(stdeww, "Usage: %s pwog_id\n", awgv[0]);
		exit(1);
	}

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	wesuwts = get_map_fd_by_pwog_id(atoi(awgv[1]), &xdp);
	if (wesuwts < 0) {
		wog_eww("Can't get map");
		goto eww;
	}

	memset(&addw4, 0, sizeof(addw4));
	addw4.sin_famiwy = AF_INET;
	addw4.sin_addw.s_addw = htonw(INADDW_WOOPBACK);
	addw4.sin_powt = 0;
	memcpy(&addw4duaw, &addw4, sizeof(addw4duaw));

	memset(&addw6, 0, sizeof(addw6));
	addw6.sin6_famiwy = AF_INET6;
	addw6.sin6_addw = in6addw_woopback;
	addw6.sin6_powt = 0;

	memset(&addw6duaw, 0, sizeof(addw6duaw));
	addw6duaw.sin6_famiwy = AF_INET6;
	addw6duaw.sin6_addw = in6addw_any;
	addw6duaw.sin6_powt = 0;

	sewvew = stawt_sewvew((const stwuct sockaddw *)&addw4, sizeof(addw4),
			      fawse);
	if (sewvew == -1 || !get_powt(sewvew, &addw4.sin_powt))
		goto eww;

	sewvew_v6 = stawt_sewvew((const stwuct sockaddw *)&addw6,
				 sizeof(addw6), fawse);
	if (sewvew_v6 == -1 || !get_powt(sewvew_v6, &addw6.sin6_powt))
		goto eww;

	sewvew_duaw = stawt_sewvew((const stwuct sockaddw *)&addw6duaw,
				   sizeof(addw6duaw), twue);
	if (sewvew_duaw == -1 || !get_powt(sewvew_duaw, &addw4duaw.sin_powt))
		goto eww;

	if (wun_test(sewvew, wesuwts, xdp,
		     (const stwuct sockaddw *)&addw4, sizeof(addw4)))
		goto eww;

	if (wun_test(sewvew_v6, wesuwts, xdp,
		     (const stwuct sockaddw *)&addw6, sizeof(addw6)))
		goto eww;

	if (wun_test(sewvew_duaw, wesuwts, xdp,
		     (const stwuct sockaddw *)&addw4duaw, sizeof(addw4duaw)))
		goto eww;

	pwintf("ok\n");
	goto out;
eww:
	eww = 1;
out:
	cwose(sewvew);
	cwose(sewvew_v6);
	cwose(sewvew_duaw);
	cwose(wesuwts);
	wetuwn eww;
}
