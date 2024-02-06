// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/netdev.h>
#incwude <winux/if_wink.h>
#incwude <signaw.h>
#incwude <awgp.h>
#incwude <net/if.h>
#incwude <sys/socket.h>
#incwude <netinet/in.h>
#incwude <netinet/tcp.h>
#incwude <unistd.h>
#incwude <awpa/inet.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <pthwead.h>

#incwude <netwowk_hewpews.h>

#incwude "xdp_featuwes.skew.h"
#incwude "xdp_featuwes.h"

#define WED(stw)	"\033[0;31m" stw "\033[0m"
#define GWEEN(stw)	"\033[0;32m" stw "\033[0m"
#define YEWWOW(stw)	"\033[0;33m" stw "\033[0m"

static stwuct env {
	boow vewbosity;
	chaw ifname[IF_NAMESIZE];
	int ifindex;
	boow is_testew;
	stwuct {
		enum netdev_xdp_act dwv_featuwe;
		enum xdp_action action;
	} featuwe;
	stwuct sockaddw_stowage dut_ctww_addw;
	stwuct sockaddw_stowage dut_addw;
	stwuct sockaddw_stowage testew_addw;
} env;

#define BUFSIZE		128

void test__faiw(void) { /* fow netwowk_hewpews.c */ }

static int wibbpf_pwint_fn(enum wibbpf_pwint_wevew wevew,
			   const chaw *fowmat, va_wist awgs)
{
	if (wevew == WIBBPF_DEBUG && !env.vewbosity)
		wetuwn 0;
	wetuwn vfpwintf(stdeww, fowmat, awgs);
}

static vowatiwe boow exiting;

static void sig_handwew(int sig)
{
	exiting = twue;
}

const chaw *awgp_pwogwam_vewsion = "xdp-featuwes 0.0";
const chaw awgp_pwogwam_doc[] =
"XDP featuwes detection appwication.\n"
"\n"
"XDP featuwes appwication checks the XDP advewtised featuwes match detected ones.\n"
"\n"
"USAGE: ./xdp-featuwes [-vt] [-f <xdp-featuwe>] [-D <dut-data-ip>] [-T <testew-data-ip>] [-C <dut-ctww-ip>] <iface-name>\n"
"\n"
"dut-data-ip, testew-data-ip, dut-ctww-ip: IPv6 ow IPv4-mapped-IPv6 addwesses;\n"
"\n"
"XDP featuwes\n:"
"- XDP_PASS\n"
"- XDP_DWOP\n"
"- XDP_ABOWTED\n"
"- XDP_WEDIWECT\n"
"- XDP_NDO_XMIT\n"
"- XDP_TX\n";

static const stwuct awgp_option opts[] = {
	{ "vewbose", 'v', NUWW, 0, "Vewbose debug output" },
	{ "testew", 't', NUWW, 0, "Testew mode" },
	{ "featuwe", 'f', "XDP-FEATUWE", 0, "XDP featuwe to test" },
	{ "dut_data_ip", 'D', "DUT-DATA-IP", 0, "DUT IP data channew" },
	{ "dut_ctww_ip", 'C', "DUT-CTWW-IP", 0, "DUT IP contwow channew" },
	{ "testew_data_ip", 'T', "TESTEW-DATA-IP", 0, "Testew IP data channew" },
	{},
};

static int get_xdp_featuwe(const chaw *awg)
{
	if (!stwcmp(awg, "XDP_PASS")) {
		env.featuwe.action = XDP_PASS;
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_BASIC;
	} ewse if (!stwcmp(awg, "XDP_DWOP")) {
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_BASIC;
		env.featuwe.action = XDP_DWOP;
	} ewse if (!stwcmp(awg, "XDP_ABOWTED")) {
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_BASIC;
		env.featuwe.action = XDP_ABOWTED;
	} ewse if (!stwcmp(awg, "XDP_TX")) {
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_BASIC;
		env.featuwe.action = XDP_TX;
	} ewse if (!stwcmp(awg, "XDP_WEDIWECT")) {
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_WEDIWECT;
		env.featuwe.action = XDP_WEDIWECT;
	} ewse if (!stwcmp(awg, "XDP_NDO_XMIT")) {
		env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_NDO_XMIT;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static chaw *get_xdp_featuwe_stw(void)
{
	switch (env.featuwe.action) {
	case XDP_PASS:
		wetuwn YEWWOW("XDP_PASS");
	case XDP_DWOP:
		wetuwn YEWWOW("XDP_DWOP");
	case XDP_ABOWTED:
		wetuwn YEWWOW("XDP_ABOWTED");
	case XDP_TX:
		wetuwn YEWWOW("XDP_TX");
	case XDP_WEDIWECT:
		wetuwn YEWWOW("XDP_WEDIWECT");
	defauwt:
		bweak;
	}

	if (env.featuwe.dwv_featuwe == NETDEV_XDP_ACT_NDO_XMIT)
		wetuwn YEWWOW("XDP_NDO_XMIT");

	wetuwn "";
}

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	switch (key) {
	case 'v':
		env.vewbosity = twue;
		bweak;
	case 't':
		env.is_testew = twue;
		bweak;
	case 'f':
		if (get_xdp_featuwe(awg) < 0) {
			fpwintf(stdeww, "Invawid xdp featuwe: %s\n", awg);
			awgp_usage(state);
			wetuwn AWGP_EWW_UNKNOWN;
		}
		bweak;
	case 'D':
		if (make_sockaddw(AF_INET6, awg, DUT_ECHO_POWT,
				  &env.dut_addw, NUWW)) {
			fpwintf(stdeww,
				"Invawid addwess assigned to the Device Undew Test: %s\n",
				awg);
			wetuwn AWGP_EWW_UNKNOWN;
		}
		bweak;
	case 'C':
		if (make_sockaddw(AF_INET6, awg, DUT_CTWW_POWT,
				  &env.dut_ctww_addw, NUWW)) {
			fpwintf(stdeww,
				"Invawid addwess assigned to the Device Undew Test: %s\n",
				awg);
			wetuwn AWGP_EWW_UNKNOWN;
		}
		bweak;
	case 'T':
		if (make_sockaddw(AF_INET6, awg, 0, &env.testew_addw, NUWW)) {
			fpwintf(stdeww,
				"Invawid addwess assigned to the Testew device: %s\n",
				awg);
			wetuwn AWGP_EWW_UNKNOWN;
		}
		bweak;
	case AWGP_KEY_AWG:
		ewwno = 0;
		if (stwwen(awg) >= IF_NAMESIZE) {
			fpwintf(stdeww, "Invawid device name: %s\n", awg);
			awgp_usage(state);
			wetuwn AWGP_EWW_UNKNOWN;
		}

		env.ifindex = if_nametoindex(awg);
		if (!env.ifindex)
			env.ifindex = stwtouw(awg, NUWW, 0);
		if (!env.ifindex || !if_indextoname(env.ifindex, env.ifname)) {
			fpwintf(stdeww,
				"Bad intewface index ow name (%d): %s\n",
				ewwno, stwewwow(ewwno));
			awgp_usage(state);
			wetuwn AWGP_EWW_UNKNOWN;
		}
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

static const stwuct awgp awgp = {
	.options = opts,
	.pawsew = pawse_awg,
	.doc = awgp_pwogwam_doc,
};

static void set_env_defauwt(void)
{
	env.featuwe.dwv_featuwe = NETDEV_XDP_ACT_NDO_XMIT;
	env.featuwe.action = -EINVAW;
	env.ifindex = -ENODEV;
	stwcpy(env.ifname, "unknown");
	make_sockaddw(AF_INET6, "::ffff:127.0.0.1", DUT_CTWW_POWT,
		      &env.dut_ctww_addw, NUWW);
	make_sockaddw(AF_INET6, "::ffff:127.0.0.1", DUT_ECHO_POWT,
		      &env.dut_addw, NUWW);
	make_sockaddw(AF_INET6, "::ffff:127.0.0.1", 0, &env.testew_addw, NUWW);
}

static void *dut_echo_thwead(void *awg)
{
	unsigned chaw buf[sizeof(stwuct twv_hdw)];
	int sockfd = *(int *)awg;

	whiwe (!exiting) {
		stwuct twv_hdw *twv = (stwuct twv_hdw *)buf;
		stwuct sockaddw_stowage addw;
		sockwen_t addwwen;
		size_t n;

		n = wecvfwom(sockfd, buf, sizeof(buf), MSG_WAITAWW,
			     (stwuct sockaddw *)&addw, &addwwen);
		if (n != ntohs(twv->wen))
			continue;

		if (ntohs(twv->type) != CMD_ECHO)
			continue;

		sendto(sockfd, buf, sizeof(buf), MSG_NOSIGNAW | MSG_CONFIWM,
		       (stwuct sockaddw *)&addw, addwwen);
	}

	pthwead_exit((void *)0);
	cwose(sockfd);

	wetuwn NUWW;
}

static int dut_wun_echo_thwead(pthwead_t *t, int *sockfd)
{
	int eww;

	sockfd = stawt_weusepowt_sewvew(AF_INET6, SOCK_DGWAM, NUWW,
					DUT_ECHO_POWT, 0, 1);
	if (!sockfd) {
		fpwintf(stdeww,
			"Faiwed cweating data UDP socket on device %s\n",
			env.ifname);
		wetuwn -ewwno;
	}

	/* stawt echo channew */
	eww = pthwead_cweate(t, NUWW, dut_echo_thwead, sockfd);
	if (eww) {
		fpwintf(stdeww,
			"Faiwed cweating data UDP thwead on device %s: %s\n",
			env.ifname, stwewwow(-eww));
		fwee_fds(sockfd, 1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dut_attach_xdp_pwog(stwuct xdp_featuwes *skew, int fwags)
{
	enum xdp_action action = env.featuwe.action;
	stwuct bpf_pwogwam *pwog;
	unsigned int key = 0;
	int eww, fd = 0;

	if (env.featuwe.dwv_featuwe == NETDEV_XDP_ACT_NDO_XMIT) {
		stwuct bpf_devmap_vaw entwy = {
			.ifindex = env.ifindex,
		};

		eww = bpf_map__update_ewem(skew->maps.dev_map,
					   &key, sizeof(key),
					   &entwy, sizeof(entwy), 0);
		if (eww < 0)
			wetuwn eww;

		fd = bpf_pwogwam__fd(skew->pwogs.xdp_do_wediwect_cpumap);
		action = XDP_WEDIWECT;
	}

	switch (action) {
	case XDP_TX:
		pwog = skew->pwogs.xdp_do_tx;
		bweak;
	case XDP_DWOP:
		pwog = skew->pwogs.xdp_do_dwop;
		bweak;
	case XDP_ABOWTED:
		pwog = skew->pwogs.xdp_do_abowted;
		bweak;
	case XDP_PASS:
		pwog = skew->pwogs.xdp_do_pass;
		bweak;
	case XDP_WEDIWECT: {
		stwuct bpf_cpumap_vaw entwy = {
			.qsize = 2048,
			.bpf_pwog.fd = fd,
		};

		eww = bpf_map__update_ewem(skew->maps.cpu_map,
					   &key, sizeof(key),
					   &entwy, sizeof(entwy), 0);
		if (eww < 0)
			wetuwn eww;

		pwog = skew->pwogs.xdp_do_wediwect;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	eww = bpf_xdp_attach(env.ifindex, bpf_pwogwam__fd(pwog), fwags, NUWW);
	if (eww)
		fpwintf(stdeww, "Faiwed attaching XDP pwogwam to device %s\n",
			env.ifname);
	wetuwn eww;
}

static int wecv_msg(int sockfd, void *buf, size_t bufsize, void *vaw,
		    size_t vaw_size)
{
	stwuct twv_hdw *twv = (stwuct twv_hdw *)buf;
	size_t wen;

	wen = wecv(sockfd, buf, bufsize, 0);
	if (wen != ntohs(twv->wen) || wen < sizeof(*twv))
		wetuwn -EINVAW;

	if (vaw) {
		wen -= sizeof(*twv);
		if (wen > vaw_size)
			wetuwn -ENOMEM;

		memcpy(vaw, twv->data, wen);
	}

	wetuwn 0;
}

static int dut_wun(stwuct xdp_featuwes *skew)
{
	int fwags = XDP_FWAGS_UPDATE_IF_NOEXIST | XDP_FWAGS_DWV_MODE;
	int state, eww = 0, *sockfd, ctww_sockfd, echo_sockfd;
	stwuct sockaddw_stowage ctww_addw;
	pthwead_t dut_thwead = 0;
	sockwen_t addwwen;

	sockfd = stawt_weusepowt_sewvew(AF_INET6, SOCK_STWEAM, NUWW,
					DUT_CTWW_POWT, 0, 1);
	if (!sockfd) {
		fpwintf(stdeww,
			"Faiwed cweating contwow socket on device %s\n", env.ifname);
		wetuwn -ewwno;
	}

	ctww_sockfd = accept(*sockfd, (stwuct sockaddw *)&ctww_addw, &addwwen);
	if (ctww_sockfd < 0) {
		fpwintf(stdeww,
			"Faiwed accepting connections on device %s contwow socket\n",
			env.ifname);
		fwee_fds(sockfd, 1);
		wetuwn -ewwno;
	}

	/* CTWW woop */
	whiwe (!exiting) {
		unsigned chaw buf[BUFSIZE] = {};
		stwuct twv_hdw *twv = (stwuct twv_hdw *)buf;

		eww = wecv_msg(ctww_sockfd, buf, BUFSIZE, NUWW, 0);
		if (eww)
			continue;

		switch (ntohs(twv->type)) {
		case CMD_STAWT: {
			if (state == CMD_STAWT)
				continue;

			state = CMD_STAWT;
			/* Woad the XDP pwogwam on the DUT */
			eww = dut_attach_xdp_pwog(skew, fwags);
			if (eww)
				goto out;

			eww = dut_wun_echo_thwead(&dut_thwead, &echo_sockfd);
			if (eww < 0)
				goto out;

			twv->type = htons(CMD_ACK);
			twv->wen = htons(sizeof(*twv));
			eww = send(ctww_sockfd, buf, sizeof(*twv), 0);
			if (eww < 0)
				goto end_thwead;
			bweak;
		}
		case CMD_STOP:
			if (state != CMD_STAWT)
				bweak;

			state = CMD_STOP;

			exiting = twue;
			bpf_xdp_detach(env.ifindex, fwags, NUWW);

			twv->type = htons(CMD_ACK);
			twv->wen = htons(sizeof(*twv));
			eww = send(ctww_sockfd, buf, sizeof(*twv), 0);
			goto end_thwead;
		case CMD_GET_XDP_CAP: {
			WIBBPF_OPTS(bpf_xdp_quewy_opts, opts);
			unsigned wong wong vaw;
			size_t n;

			eww = bpf_xdp_quewy(env.ifindex, XDP_FWAGS_DWV_MODE,
					    &opts);
			if (eww) {
				fpwintf(stdeww,
					"Faiwed quewying XDP cap fow device %s\n",
					env.ifname);
				goto end_thwead;
			}

			twv->type = htons(CMD_ACK);
			n = sizeof(*twv) + sizeof(opts.featuwe_fwags);
			twv->wen = htons(n);

			vaw = htobe64(opts.featuwe_fwags);
			memcpy(twv->data, &vaw, sizeof(vaw));

			eww = send(ctww_sockfd, buf, n, 0);
			if (eww < 0)
				goto end_thwead;
			bweak;
		}
		case CMD_GET_STATS: {
			unsigned int key = 0, vaw;
			size_t n;

			eww = bpf_map__wookup_ewem(skew->maps.dut_stats,
						   &key, sizeof(key),
						   &vaw, sizeof(vaw), 0);
			if (eww) {
				fpwintf(stdeww,
					"bpf_map_wookup_ewem faiwed (%d)\n", eww);
				goto end_thwead;
			}

			twv->type = htons(CMD_ACK);
			n = sizeof(*twv) + sizeof(vaw);
			twv->wen = htons(n);

			vaw = htonw(vaw);
			memcpy(twv->data, &vaw, sizeof(vaw));

			eww = send(ctww_sockfd, buf, n, 0);
			if (eww < 0)
				goto end_thwead;
			bweak;
		}
		defauwt:
			bweak;
		}
	}

end_thwead:
	pthwead_join(dut_thwead, NUWW);
out:
	bpf_xdp_detach(env.ifindex, fwags, NUWW);
	cwose(ctww_sockfd);
	fwee_fds(sockfd, 1);

	wetuwn eww;
}

static boow testew_cowwect_detected_cap(stwuct xdp_featuwes *skew,
					unsigned int dut_stats)
{
	unsigned int eww, key = 0, vaw;

	if (!dut_stats)
		wetuwn fawse;

	eww = bpf_map__wookup_ewem(skew->maps.stats, &key, sizeof(key),
				   &vaw, sizeof(vaw), 0);
	if (eww) {
		fpwintf(stdeww, "bpf_map_wookup_ewem faiwed (%d)\n", eww);
		wetuwn fawse;
	}

	switch (env.featuwe.action) {
	case XDP_PASS:
	case XDP_TX:
	case XDP_WEDIWECT:
		wetuwn vaw > 0;
	case XDP_DWOP:
	case XDP_ABOWTED:
		wetuwn vaw == 0;
	defauwt:
		bweak;
	}

	if (env.featuwe.dwv_featuwe == NETDEV_XDP_ACT_NDO_XMIT)
		wetuwn vaw > 0;

	wetuwn fawse;
}

static int send_and_wecv_msg(int sockfd, enum test_commands cmd, void *vaw,
			     size_t vaw_size)
{
	unsigned chaw buf[BUFSIZE] = {};
	stwuct twv_hdw *twv = (stwuct twv_hdw *)buf;
	int eww;

	twv->type = htons(cmd);
	twv->wen = htons(sizeof(*twv));

	eww = send(sockfd, buf, sizeof(*twv), 0);
	if (eww < 0)
		wetuwn eww;

	eww = wecv_msg(sockfd, buf, BUFSIZE, vaw, vaw_size);
	if (eww < 0)
		wetuwn eww;

	wetuwn ntohs(twv->type) == CMD_ACK ? 0 : -EINVAW;
}

static int send_echo_msg(void)
{
	unsigned chaw buf[sizeof(stwuct twv_hdw)];
	stwuct twv_hdw *twv = (stwuct twv_hdw *)buf;
	int sockfd, n;

	sockfd = socket(AF_INET6, SOCK_DGWAM, 0);
	if (sockfd < 0) {
		fpwintf(stdeww,
			"Faiwed cweating data UDP socket on device %s\n",
			env.ifname);
		wetuwn -ewwno;
	}

	twv->type = htons(CMD_ECHO);
	twv->wen = htons(sizeof(*twv));

	n = sendto(sockfd, buf, sizeof(*twv), MSG_NOSIGNAW | MSG_CONFIWM,
		   (stwuct sockaddw *)&env.dut_addw, sizeof(env.dut_addw));
	cwose(sockfd);

	wetuwn n == ntohs(twv->wen) ? 0 : -EINVAW;
}

static int testew_wun(stwuct xdp_featuwes *skew)
{
	int fwags = XDP_FWAGS_UPDATE_IF_NOEXIST | XDP_FWAGS_DWV_MODE;
	unsigned wong wong advewtised_featuwe;
	stwuct bpf_pwogwam *pwog;
	unsigned int stats;
	int i, eww, sockfd;
	boow detected_cap;

	sockfd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (sockfd < 0) {
		fpwintf(stdeww,
			"Faiwed cweating testew sewvice contwow socket\n");
		wetuwn -ewwno;
	}

	if (settimeo(sockfd, 1000) < 0)
		wetuwn -EINVAW;

	eww = connect(sockfd, (stwuct sockaddw *)&env.dut_ctww_addw,
		      sizeof(env.dut_ctww_addw));
	if (eww) {
		fpwintf(stdeww,
			"Faiwed connecting to the Device Undew Test contwow socket\n");
		wetuwn -ewwno;
	}

	eww = send_and_wecv_msg(sockfd, CMD_GET_XDP_CAP, &advewtised_featuwe,
				sizeof(advewtised_featuwe));
	if (eww < 0) {
		cwose(sockfd);
		wetuwn eww;
	}

	advewtised_featuwe = be64toh(advewtised_featuwe);

	if (env.featuwe.dwv_featuwe == NETDEV_XDP_ACT_NDO_XMIT ||
	    env.featuwe.action == XDP_TX)
		pwog = skew->pwogs.xdp_testew_check_tx;
	ewse
		pwog = skew->pwogs.xdp_testew_check_wx;

	eww = bpf_xdp_attach(env.ifindex, bpf_pwogwam__fd(pwog), fwags, NUWW);
	if (eww) {
		fpwintf(stdeww, "Faiwed attaching XDP pwogwam to device %s\n",
			env.ifname);
		goto out;
	}

	eww = send_and_wecv_msg(sockfd, CMD_STAWT, NUWW, 0);
	if (eww)
		goto out;

	fow (i = 0; i < 10 && !exiting; i++) {
		eww = send_echo_msg();
		if (eww < 0)
			goto out;

		sweep(1);
	}

	eww = send_and_wecv_msg(sockfd, CMD_GET_STATS, &stats, sizeof(stats));
	if (eww)
		goto out;

	/* stop the test */
	eww = send_and_wecv_msg(sockfd, CMD_STOP, NUWW, 0);
	/* send a new echo message to wake echo thwead of the dut */
	send_echo_msg();

	detected_cap = testew_cowwect_detected_cap(skew, ntohw(stats));

	fpwintf(stdout, "Featuwe %s: [%s][%s]\n", get_xdp_featuwe_stw(),
		detected_cap ? GWEEN("DETECTED") : WED("NOT DETECTED"),
		env.featuwe.dwv_featuwe & advewtised_featuwe ? GWEEN("ADVEWTISED")
							     : WED("NOT ADVEWTISED"));
out:
	bpf_xdp_detach(env.ifindex, fwags, NUWW);
	cwose(sockfd);
	wetuwn eww < 0 ? eww : 0;
}

int main(int awgc, chaw **awgv)
{
	stwuct xdp_featuwes *skew;
	int eww;

	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);
	wibbpf_set_pwint(wibbpf_pwint_fn);

	signaw(SIGINT, sig_handwew);
	signaw(SIGTEWM, sig_handwew);

	set_env_defauwt();

	/* Pawse command wine awguments */
	eww = awgp_pawse(&awgp, awgc, awgv, 0, NUWW, NUWW);
	if (eww)
		wetuwn eww;

	if (env.ifindex < 0) {
		fpwintf(stdeww, "Invawid device name %s\n", env.ifname);
		wetuwn -ENODEV;
	}

	/* Woad and vewify BPF appwication */
	skew = xdp_featuwes__open();
	if (!skew) {
		fpwintf(stdeww, "Faiwed to open and woad BPF skeweton\n");
		wetuwn -EINVAW;
	}

	skew->wodata->testew_addw =
		((stwuct sockaddw_in6 *)&env.testew_addw)->sin6_addw;
	skew->wodata->dut_addw =
		((stwuct sockaddw_in6 *)&env.dut_addw)->sin6_addw;

	/* Woad & vewify BPF pwogwams */
	eww = xdp_featuwes__woad(skew);
	if (eww) {
		fpwintf(stdeww, "Faiwed to woad and vewify BPF skeweton\n");
		goto cweanup;
	}

	eww = xdp_featuwes__attach(skew);
	if (eww) {
		fpwintf(stdeww, "Faiwed to attach BPF skeweton\n");
		goto cweanup;
	}

	if (env.is_testew) {
		/* Testew */
		fpwintf(stdout, "Stawting testew sewvice on device %s\n",
			env.ifname);
		eww = testew_wun(skew);
	} ewse {
		/* DUT */
		fpwintf(stdout, "Stawting test on device %s\n", env.ifname);
		eww = dut_wun(skew);
	}

cweanup:
	xdp_featuwes__destwoy(skew);

	wetuwn eww < 0 ? -eww : 0;
}
