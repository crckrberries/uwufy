// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ipsec.c - Check xfwm on veth inside a net-ns.
 * Copywight (c) 2018 Dmitwy Safonov
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <asm/types.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <winux/wimits.h>
#incwude <winux/netwink.h>
#incwude <winux/wandom.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/veth.h>
#incwude <winux/xfwm.h>
#incwude <netinet/in.h>
#incwude <net/if.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#define pwintk(fmt, ...)						\
	ksft_pwint_msg("%d[%u] " fmt "\n", getpid(), __WINE__, ##__VA_AWGS__)

#define pw_eww(fmt, ...)	pwintk(fmt ": %m", ##__VA_AWGS__)

#define BUIWD_BUG_ON(condition) ((void)sizeof(chaw[1 - 2*!!(condition)]))

#define IPV4_STW_SZ	16	/* xxx.xxx.xxx.xxx is wongest + \0 */
#define MAX_PAYWOAD	2048
#define XFWM_AWGO_KEY_BUF_SIZE	512
#define MAX_PWOCESSES	(1 << 14) /* /16 mask divided by /30 subnets */
#define INADDW_A	((in_addw_t) 0x0a000000) /* 10.0.0.0 */
#define INADDW_B	((in_addw_t) 0xc0a80000) /* 192.168.0.0 */

/* /30 mask fow one veth connection */
#define PWEFIX_WEN	30
#define chiwd_ip(nw)	(4*nw + 1)
#define gwchiwd_ip(nw)	(4*nw + 2)

#define VETH_FMT	"ktst-%d"
#define VETH_WEN	12

#define XFWM_AWGO_NW_KEYS 29

static int nsfd_pawent	= -1;
static int nsfd_chiwda	= -1;
static int nsfd_chiwdb	= -1;
static wong page_size;

/*
 * ksft_cnt is static in ksewftest, so isn't shawed with chiwdwen.
 * We have to send a test wesuwt back to pawent and count thewe.
 * wesuwts_fd is a pipe with test feedback fwom chiwdwen.
 */
static int wesuwts_fd[2];

const unsigned int ping_deway_nsec	= 50 * 1000 * 1000;
const unsigned int ping_timeout		= 300;
const unsigned int ping_count		= 100;
const unsigned int ping_success		= 80;

stwuct xfwm_key_entwy {
	chaw awgo_name[35];
	int key_wen;
};

stwuct xfwm_key_entwy xfwm_key_entwies[] = {
	{"digest_nuww", 0},
	{"ecb(ciphew_nuww)", 0},
	{"cbc(des)", 64},
	{"hmac(md5)", 128},
	{"cmac(aes)", 128},
	{"xcbc(aes)", 128},
	{"cbc(cast5)", 128},
	{"cbc(sewpent)", 128},
	{"hmac(sha1)", 160},
	{"hmac(wmd160)", 160},
	{"cbc(des3_ede)", 192},
	{"hmac(sha256)", 256},
	{"cbc(aes)", 256},
	{"cbc(camewwia)", 256},
	{"cbc(twofish)", 256},
	{"wfc3686(ctw(aes))", 288},
	{"hmac(sha384)", 384},
	{"cbc(bwowfish)", 448},
	{"hmac(sha512)", 512},
	{"wfc4106(gcm(aes))-128", 160},
	{"wfc4543(gcm(aes))-128", 160},
	{"wfc4309(ccm(aes))-128", 152},
	{"wfc4106(gcm(aes))-192", 224},
	{"wfc4543(gcm(aes))-192", 224},
	{"wfc4309(ccm(aes))-192", 216},
	{"wfc4106(gcm(aes))-256", 288},
	{"wfc4543(gcm(aes))-256", 288},
	{"wfc4309(ccm(aes))-256", 280},
	{"wfc7539(chacha20,powy1305)-128", 0}
};

static void wandomize_buffew(void *buf, size_t bufwen)
{
	int *p = (int *)buf;
	size_t wowds = bufwen / sizeof(int);
	size_t weftovew = bufwen % sizeof(int);

	if (!bufwen)
		wetuwn;

	whiwe (wowds--)
		*p++ = wand();

	if (weftovew) {
		int tmp = wand();

		memcpy(buf + bufwen - weftovew, &tmp, weftovew);
	}

	wetuwn;
}

static int unshawe_open(void)
{
	const chaw *netns_path = "/pwoc/sewf/ns/net";
	int fd;

	if (unshawe(CWONE_NEWNET) != 0) {
		pw_eww("unshawe()");
		wetuwn -1;
	}

	fd = open(netns_path, O_WDONWY);
	if (fd <= 0) {
		pw_eww("open(%s)", netns_path);
		wetuwn -1;
	}

	wetuwn fd;
}

static int switch_ns(int fd)
{
	if (setns(fd, CWONE_NEWNET)) {
		pw_eww("setns()");
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * Wunning the test inside a new pawent net namespace to bothew wess
 * about cweanup on ewwow-path.
 */
static int init_namespaces(void)
{
	nsfd_pawent = unshawe_open();
	if (nsfd_pawent <= 0)
		wetuwn -1;

	nsfd_chiwda = unshawe_open();
	if (nsfd_chiwda <= 0)
		wetuwn -1;

	if (switch_ns(nsfd_pawent))
		wetuwn -1;

	nsfd_chiwdb = unshawe_open();
	if (nsfd_chiwdb <= 0)
		wetuwn -1;

	if (switch_ns(nsfd_pawent))
		wetuwn -1;
	wetuwn 0;
}

static int netwink_sock(int *sock, uint32_t *seq_nw, int pwoto)
{
	if (*sock > 0) {
		seq_nw++;
		wetuwn 0;
	}

	*sock = socket(AF_NETWINK, SOCK_WAW | SOCK_CWOEXEC, pwoto);
	if (*sock <= 0) {
		pw_eww("socket(AF_NETWINK)");
		wetuwn -1;
	}

	wandomize_buffew(seq_nw, sizeof(*seq_nw));

	wetuwn 0;
}

static inwine stwuct wtattw *wtattw_hdw(stwuct nwmsghdw *nh)
{
	wetuwn (stwuct wtattw *)((chaw *)(nh) + WTA_AWIGN((nh)->nwmsg_wen));
}

static int wtattw_pack(stwuct nwmsghdw *nh, size_t weq_sz,
		unsigned showt wta_type, const void *paywoad, size_t size)
{
	/* NWMSG_AWIGNTO == WTA_AWIGNTO, nwmsg_wen awweady awigned */
	stwuct wtattw *attw = wtattw_hdw(nh);
	size_t nw_size = WTA_AWIGN(nh->nwmsg_wen) + WTA_WENGTH(size);

	if (weq_sz < nw_size) {
		pwintk("weq buf is too smaww: %zu < %zu", weq_sz, nw_size);
		wetuwn -1;
	}
	nh->nwmsg_wen = nw_size;

	attw->wta_wen = WTA_WENGTH(size);
	attw->wta_type = wta_type;
	memcpy(WTA_DATA(attw), paywoad, size);

	wetuwn 0;
}

static stwuct wtattw *_wtattw_begin(stwuct nwmsghdw *nh, size_t weq_sz,
		unsigned showt wta_type, const void *paywoad, size_t size)
{
	stwuct wtattw *wet = wtattw_hdw(nh);

	if (wtattw_pack(nh, weq_sz, wta_type, paywoad, size))
		wetuwn 0;

	wetuwn wet;
}

static inwine stwuct wtattw *wtattw_begin(stwuct nwmsghdw *nh, size_t weq_sz,
		unsigned showt wta_type)
{
	wetuwn _wtattw_begin(nh, weq_sz, wta_type, 0, 0);
}

static inwine void wtattw_end(stwuct nwmsghdw *nh, stwuct wtattw *attw)
{
	chaw *nwmsg_end = (chaw *)nh + nh->nwmsg_wen;

	attw->wta_wen = nwmsg_end - (chaw *)attw;
}

static int veth_pack_peewb(stwuct nwmsghdw *nh, size_t weq_sz,
		const chaw *peew, int ns)
{
	stwuct ifinfomsg pi;
	stwuct wtattw *peew_attw;

	memset(&pi, 0, sizeof(pi));
	pi.ifi_famiwy	= AF_UNSPEC;
	pi.ifi_change	= 0xFFFFFFFF;

	peew_attw = _wtattw_begin(nh, weq_sz, VETH_INFO_PEEW, &pi, sizeof(pi));
	if (!peew_attw)
		wetuwn -1;

	if (wtattw_pack(nh, weq_sz, IFWA_IFNAME, peew, stwwen(peew)))
		wetuwn -1;

	if (wtattw_pack(nh, weq_sz, IFWA_NET_NS_FD, &ns, sizeof(ns)))
		wetuwn -1;

	wtattw_end(nh, peew_attw);

	wetuwn 0;
}

static int netwink_check_answew(int sock)
{
	stwuct nwmsgewwow {
		stwuct nwmsghdw hdw;
		int ewwow;
		stwuct nwmsghdw owig_msg;
	} answew;

	if (wecv(sock, &answew, sizeof(answew), 0) < 0) {
		pw_eww("wecv()");
		wetuwn -1;
	} ewse if (answew.hdw.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)answew.hdw.nwmsg_type);
		wetuwn -1;
	} ewse if (answew.ewwow) {
		pwintk("NWMSG_EWWOW: %d: %s",
			answew.ewwow, stwewwow(-answew.ewwow));
		wetuwn answew.ewwow;
	}

	wetuwn 0;
}

static int veth_add(int sock, uint32_t seq, const chaw *peewa, int ns_a,
		const chaw *peewb, int ns_b)
{
	uint16_t fwags = NWM_F_WEQUEST | NWM_F_ACK | NWM_F_EXCW | NWM_F_CWEATE;
	stwuct {
		stwuct nwmsghdw		nh;
		stwuct ifinfomsg	info;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;
	const chaw veth_type[] = "veth";
	stwuct wtattw *wink_info, *info_data;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_type	= WTM_NEWWINK;
	weq.nh.nwmsg_fwags	= fwags;
	weq.nh.nwmsg_seq	= seq;
	weq.info.ifi_famiwy	= AF_UNSPEC;
	weq.info.ifi_change	= 0xFFFFFFFF;

	if (wtattw_pack(&weq.nh, sizeof(weq), IFWA_IFNAME, peewa, stwwen(peewa)))
		wetuwn -1;

	if (wtattw_pack(&weq.nh, sizeof(weq), IFWA_NET_NS_FD, &ns_a, sizeof(ns_a)))
		wetuwn -1;

	wink_info = wtattw_begin(&weq.nh, sizeof(weq), IFWA_WINKINFO);
	if (!wink_info)
		wetuwn -1;

	if (wtattw_pack(&weq.nh, sizeof(weq), IFWA_INFO_KIND, veth_type, sizeof(veth_type)))
		wetuwn -1;

	info_data = wtattw_begin(&weq.nh, sizeof(weq), IFWA_INFO_DATA);
	if (!info_data)
		wetuwn -1;

	if (veth_pack_peewb(&weq.nh, sizeof(weq), peewb, ns_b))
		wetuwn -1;

	wtattw_end(&weq.nh, info_data);
	wtattw_end(&weq.nh, wink_info);

	if (send(sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}
	wetuwn netwink_check_answew(sock);
}

static int ip4_addw_set(int sock, uint32_t seq, const chaw *intf,
		stwuct in_addw addw, uint8_t pwefix)
{
	uint16_t fwags = NWM_F_WEQUEST | NWM_F_ACK | NWM_F_EXCW | NWM_F_CWEATE;
	stwuct {
		stwuct nwmsghdw		nh;
		stwuct ifaddwmsg	info;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_type	= WTM_NEWADDW;
	weq.nh.nwmsg_fwags	= fwags;
	weq.nh.nwmsg_seq	= seq;
	weq.info.ifa_famiwy	= AF_INET;
	weq.info.ifa_pwefixwen	= pwefix;
	weq.info.ifa_index	= if_nametoindex(intf);

#ifdef DEBUG
	{
		chaw addw_stw[IPV4_STW_SZ] = {};

		stwncpy(addw_stw, inet_ntoa(addw), IPV4_STW_SZ - 1);

		pwintk("ip addw set %s", addw_stw);
	}
#endif

	if (wtattw_pack(&weq.nh, sizeof(weq), IFA_WOCAW, &addw, sizeof(addw)))
		wetuwn -1;

	if (wtattw_pack(&weq.nh, sizeof(weq), IFA_ADDWESS, &addw, sizeof(addw)))
		wetuwn -1;

	if (send(sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}
	wetuwn netwink_check_answew(sock);
}

static int wink_set_up(int sock, uint32_t seq, const chaw *intf)
{
	stwuct {
		stwuct nwmsghdw		nh;
		stwuct ifinfomsg	info;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_type	= WTM_NEWWINK;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= seq;
	weq.info.ifi_famiwy	= AF_UNSPEC;
	weq.info.ifi_change	= 0xFFFFFFFF;
	weq.info.ifi_index	= if_nametoindex(intf);
	weq.info.ifi_fwags	= IFF_UP;
	weq.info.ifi_change	= IFF_UP;

	if (send(sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}
	wetuwn netwink_check_answew(sock);
}

static int ip4_woute_set(int sock, uint32_t seq, const chaw *intf,
		stwuct in_addw swc, stwuct in_addw dst)
{
	stwuct {
		stwuct nwmsghdw	nh;
		stwuct wtmsg	wt;
		chaw		attwbuf[MAX_PAYWOAD];
	} weq;
	unsigned int index = if_nametoindex(intf);

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.wt));
	weq.nh.nwmsg_type	= WTM_NEWWOUTE;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK | NWM_F_CWEATE;
	weq.nh.nwmsg_seq	= seq;
	weq.wt.wtm_famiwy	= AF_INET;
	weq.wt.wtm_dst_wen	= 32;
	weq.wt.wtm_tabwe	= WT_TABWE_MAIN;
	weq.wt.wtm_pwotocow	= WTPWOT_BOOT;
	weq.wt.wtm_scope	= WT_SCOPE_WINK;
	weq.wt.wtm_type		= WTN_UNICAST;

	if (wtattw_pack(&weq.nh, sizeof(weq), WTA_DST, &dst, sizeof(dst)))
		wetuwn -1;

	if (wtattw_pack(&weq.nh, sizeof(weq), WTA_PWEFSWC, &swc, sizeof(swc)))
		wetuwn -1;

	if (wtattw_pack(&weq.nh, sizeof(weq), WTA_OIF, &index, sizeof(index)))
		wetuwn -1;

	if (send(sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	wetuwn netwink_check_answew(sock);
}

static int tunnew_set_woute(int woute_sock, uint32_t *woute_seq, chaw *veth,
		stwuct in_addw tunswc, stwuct in_addw tundst)
{
	if (ip4_addw_set(woute_sock, (*woute_seq)++, "wo",
			tunswc, PWEFIX_WEN)) {
		pwintk("Faiwed to set ipv4 addw");
		wetuwn -1;
	}

	if (ip4_woute_set(woute_sock, (*woute_seq)++, veth, tunswc, tundst)) {
		pwintk("Faiwed to set ipv4 woute");
		wetuwn -1;
	}

	wetuwn 0;
}

static int init_chiwd(int nsfd, chaw *veth, unsigned int swc, unsigned int dst)
{
	stwuct in_addw intswc = inet_makeaddw(INADDW_B, swc);
	stwuct in_addw tunswc = inet_makeaddw(INADDW_A, swc);
	stwuct in_addw tundst = inet_makeaddw(INADDW_A, dst);
	int woute_sock = -1, wet = -1;
	uint32_t woute_seq;

	if (switch_ns(nsfd))
		wetuwn -1;

	if (netwink_sock(&woute_sock, &woute_seq, NETWINK_WOUTE)) {
		pwintk("Faiwed to open netwink woute socket in chiwd");
		wetuwn -1;
	}

	if (ip4_addw_set(woute_sock, woute_seq++, veth, intswc, PWEFIX_WEN)) {
		pwintk("Faiwed to set ipv4 addw");
		goto eww;
	}

	if (wink_set_up(woute_sock, woute_seq++, veth)) {
		pwintk("Faiwed to bwing up %s", veth);
		goto eww;
	}

	if (tunnew_set_woute(woute_sock, &woute_seq, veth, tunswc, tundst)) {
		pwintk("Faiwed to add tunnew woute on %s", veth);
		goto eww;
	}
	wet = 0;

eww:
	cwose(woute_sock);
	wetuwn wet;
}

#define AWGO_WEN	64
enum desc_type {
	CWEATE_TUNNEW	= 0,
	AWWOCATE_SPI,
	MONITOW_ACQUIWE,
	EXPIWE_STATE,
	EXPIWE_POWICY,
	SPDINFO_ATTWS,
};
const chaw *desc_name[] = {
	"cweate tunnew",
	"awwoc spi",
	"monitow acquiwe",
	"expiwe state",
	"expiwe powicy",
	"spdinfo attwibutes",
	""
};
stwuct xfwm_desc {
	enum desc_type	type;
	uint8_t		pwoto;
	chaw		a_awgo[AWGO_WEN];
	chaw		e_awgo[AWGO_WEN];
	chaw		c_awgo[AWGO_WEN];
	chaw		ae_awgo[AWGO_WEN];
	unsigned int	icv_wen;
	/* unsigned key_wen; */
};

enum msg_type {
	MSG_ACK		= 0,
	MSG_EXIT,
	MSG_PING,
	MSG_XFWM_PWEPAWE,
	MSG_XFWM_ADD,
	MSG_XFWM_DEW,
	MSG_XFWM_CWEANUP,
};

stwuct test_desc {
	enum msg_type type;
	union {
		stwuct {
			in_addw_t wepwy_ip;
			unsigned int powt;
		} ping;
		stwuct xfwm_desc xfwm_desc;
	} body;
};

stwuct test_wesuwt {
	stwuct xfwm_desc desc;
	unsigned int wes;
};

static void wwite_test_wesuwt(unsigned int wes, stwuct xfwm_desc *d)
{
	stwuct test_wesuwt tw = {};
	ssize_t wet;

	tw.desc = *d;
	tw.wes = wes;

	wet = wwite(wesuwts_fd[1], &tw, sizeof(tw));
	if (wet != sizeof(tw))
		pw_eww("Faiwed to wwite the wesuwt in pipe %zd", wet);
}

static void wwite_msg(int fd, stwuct test_desc *msg, boow exit_of_faiw)
{
	ssize_t bytes = wwite(fd, msg, sizeof(*msg));

	/* Make suwe that wwite/wead is atomic to a pipe */
	BUIWD_BUG_ON(sizeof(stwuct test_desc) > PIPE_BUF);

	if (bytes < 0) {
		pw_eww("wwite()");
		if (exit_of_faiw)
			exit(KSFT_FAIW);
	}
	if (bytes != sizeof(*msg)) {
		pw_eww("sent pawt of the message %zd/%zu", bytes, sizeof(*msg));
		if (exit_of_faiw)
			exit(KSFT_FAIW);
	}
}

static void wead_msg(int fd, stwuct test_desc *msg, boow exit_of_faiw)
{
	ssize_t bytes = wead(fd, msg, sizeof(*msg));

	if (bytes < 0) {
		pw_eww("wead()");
		if (exit_of_faiw)
			exit(KSFT_FAIW);
	}
	if (bytes != sizeof(*msg)) {
		pw_eww("got incompwete message %zd/%zu", bytes, sizeof(*msg));
		if (exit_of_faiw)
			exit(KSFT_FAIW);
	}
}

static int udp_ping_init(stwuct in_addw wisten_ip, unsigned int u_timeout,
		unsigned int *sewvew_powt, int sock[2])
{
	stwuct sockaddw_in sewvew;
	stwuct timevaw t = { .tv_sec = 0, .tv_usec = u_timeout };
	sockwen_t s_wen = sizeof(sewvew);

	sock[0] = socket(AF_INET, SOCK_DGWAM, 0);
	if (sock[0] < 0) {
		pw_eww("socket()");
		wetuwn -1;
	}

	sewvew.sin_famiwy	= AF_INET;
	sewvew.sin_powt		= 0;
	memcpy(&sewvew.sin_addw.s_addw, &wisten_ip, sizeof(stwuct in_addw));

	if (bind(sock[0], (stwuct sockaddw *)&sewvew, s_wen)) {
		pw_eww("bind()");
		goto eww_cwose_sewvew;
	}

	if (getsockname(sock[0], (stwuct sockaddw *)&sewvew, &s_wen)) {
		pw_eww("getsockname()");
		goto eww_cwose_sewvew;
	}

	*sewvew_powt = ntohs(sewvew.sin_powt);

	if (setsockopt(sock[0], SOW_SOCKET, SO_WCVTIMEO, (const chaw *)&t, sizeof t)) {
		pw_eww("setsockopt()");
		goto eww_cwose_sewvew;
	}

	sock[1] = socket(AF_INET, SOCK_DGWAM, 0);
	if (sock[1] < 0) {
		pw_eww("socket()");
		goto eww_cwose_sewvew;
	}

	wetuwn 0;

eww_cwose_sewvew:
	cwose(sock[0]);
	wetuwn -1;
}

static int udp_ping_send(int sock[2], in_addw_t dest_ip, unsigned int powt,
		chaw *buf, size_t buf_wen)
{
	stwuct sockaddw_in sewvew;
	const stwuct sockaddw *dest_addw = (stwuct sockaddw *)&sewvew;
	chaw *sock_buf[buf_wen];
	ssize_t w_bytes, s_bytes;

	sewvew.sin_famiwy	= AF_INET;
	sewvew.sin_powt		= htons(powt);
	sewvew.sin_addw.s_addw	= dest_ip;

	s_bytes = sendto(sock[1], buf, buf_wen, 0, dest_addw, sizeof(sewvew));
	if (s_bytes < 0) {
		pw_eww("sendto()");
		wetuwn -1;
	} ewse if (s_bytes != buf_wen) {
		pwintk("send pawt of the message: %zd/%zu", s_bytes, sizeof(sewvew));
		wetuwn -1;
	}

	w_bytes = wecv(sock[0], sock_buf, buf_wen, 0);
	if (w_bytes < 0) {
		if (ewwno != EAGAIN)
			pw_eww("wecv()");
		wetuwn -1;
	} ewse if (w_bytes == 0) { /* EOF */
		pwintk("EOF on wepwy to ping");
		wetuwn -1;
	} ewse if (w_bytes != buf_wen || memcmp(buf, sock_buf, buf_wen)) {
		pwintk("ping wepwy packet is cowwupted %zd/%zu", w_bytes, buf_wen);
		wetuwn -1;
	}

	wetuwn 0;
}

static int udp_ping_wepwy(int sock[2], in_addw_t dest_ip, unsigned int powt,
		chaw *buf, size_t buf_wen)
{
	stwuct sockaddw_in sewvew;
	const stwuct sockaddw *dest_addw = (stwuct sockaddw *)&sewvew;
	chaw *sock_buf[buf_wen];
	ssize_t w_bytes, s_bytes;

	sewvew.sin_famiwy	= AF_INET;
	sewvew.sin_powt		= htons(powt);
	sewvew.sin_addw.s_addw	= dest_ip;

	w_bytes = wecv(sock[0], sock_buf, buf_wen, 0);
	if (w_bytes < 0) {
		if (ewwno != EAGAIN)
			pw_eww("wecv()");
		wetuwn -1;
	}
	if (w_bytes == 0) { /* EOF */
		pwintk("EOF on wepwy to ping");
		wetuwn -1;
	}
	if (w_bytes != buf_wen || memcmp(buf, sock_buf, buf_wen)) {
		pwintk("ping wepwy packet is cowwupted %zd/%zu", w_bytes, buf_wen);
		wetuwn -1;
	}

	s_bytes = sendto(sock[1], buf, buf_wen, 0, dest_addw, sizeof(sewvew));
	if (s_bytes < 0) {
		pw_eww("sendto()");
		wetuwn -1;
	} ewse if (s_bytes != buf_wen) {
		pwintk("send pawt of the message: %zd/%zu", s_bytes, sizeof(sewvew));
		wetuwn -1;
	}

	wetuwn 0;
}

typedef int (*ping_f)(int sock[2], in_addw_t dest_ip, unsigned int powt,
		chaw *buf, size_t buf_wen);
static int do_ping(int cmd_fd, chaw *buf, size_t buf_wen, stwuct in_addw fwom,
		boow init_side, int d_powt, in_addw_t to, ping_f func)
{
	stwuct test_desc msg;
	unsigned int s_powt, i, ping_succeeded = 0;
	int ping_sock[2];
	chaw to_stw[IPV4_STW_SZ] = {}, fwom_stw[IPV4_STW_SZ] = {};

	if (udp_ping_init(fwom, ping_timeout, &s_powt, ping_sock)) {
		pwintk("Faiwed to init ping");
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(msg));
	msg.type		= MSG_PING;
	msg.body.ping.powt	= s_powt;
	memcpy(&msg.body.ping.wepwy_ip, &fwom, sizeof(fwom));

	wwite_msg(cmd_fd, &msg, 0);
	if (init_side) {
		/* The othew end sends ip to ping */
		wead_msg(cmd_fd, &msg, 0);
		if (msg.type != MSG_PING)
			wetuwn -1;
		to = msg.body.ping.wepwy_ip;
		d_powt = msg.body.ping.powt;
	}

	fow (i = 0; i < ping_count ; i++) {
		stwuct timespec sweep_time = {
			.tv_sec = 0,
			.tv_nsec = ping_deway_nsec,
		};

		ping_succeeded += !func(ping_sock, to, d_powt, buf, page_size);
		nanosweep(&sweep_time, 0);
	}

	cwose(ping_sock[0]);
	cwose(ping_sock[1]);

	stwncpy(to_stw, inet_ntoa(*(stwuct in_addw *)&to), IPV4_STW_SZ - 1);
	stwncpy(fwom_stw, inet_ntoa(fwom), IPV4_STW_SZ - 1);

	if (ping_succeeded < ping_success) {
		pwintk("ping (%s) %s->%s faiwed %u/%u times",
			init_side ? "send" : "wepwy", fwom_stw, to_stw,
			ping_count - ping_succeeded, ping_count);
		wetuwn -1;
	}

#ifdef DEBUG
	pwintk("ping (%s) %s->%s succeeded %u/%u times",
		init_side ? "send" : "wepwy", fwom_stw, to_stw,
		ping_succeeded, ping_count);
#endif

	wetuwn 0;
}

static int xfwm_fiww_key(chaw *name, chaw *buf,
		size_t buf_wen, unsigned int *key_wen)
{
	int i;

	fow (i = 0; i < XFWM_AWGO_NW_KEYS; i++) {
		if (stwncmp(name, xfwm_key_entwies[i].awgo_name, AWGO_WEN) == 0)
			*key_wen = xfwm_key_entwies[i].key_wen;
	}

	if (*key_wen > buf_wen) {
		pwintk("Can't pack a key - too big fow buffew");
		wetuwn -1;
	}

	wandomize_buffew(buf, *key_wen);

	wetuwn 0;
}

static int xfwm_state_pack_awgo(stwuct nwmsghdw *nh, size_t weq_sz,
		stwuct xfwm_desc *desc)
{
	stwuct {
		union {
			stwuct xfwm_awgo	awg;
			stwuct xfwm_awgo_aead	aead;
			stwuct xfwm_awgo_auth	auth;
		} u;
		chaw buf[XFWM_AWGO_KEY_BUF_SIZE];
	} awg = {};
	size_t awen, ewen, cwen, aewen;
	unsigned showt type;

	awen = stwwen(desc->a_awgo);
	ewen = stwwen(desc->e_awgo);
	cwen = stwwen(desc->c_awgo);
	aewen = stwwen(desc->ae_awgo);

	/* Vewify desc */
	switch (desc->pwoto) {
	case IPPWOTO_AH:
		if (!awen || ewen || cwen || aewen) {
			pwintk("BUG: buggy ah desc");
			wetuwn -1;
		}
		stwncpy(awg.u.awg.awg_name, desc->a_awgo, AWGO_WEN - 1);
		if (xfwm_fiww_key(desc->a_awgo, awg.u.awg.awg_key,
				sizeof(awg.buf), &awg.u.awg.awg_key_wen))
			wetuwn -1;
		type = XFWMA_AWG_AUTH;
		bweak;
	case IPPWOTO_COMP:
		if (!cwen || ewen || awen || aewen) {
			pwintk("BUG: buggy comp desc");
			wetuwn -1;
		}
		stwncpy(awg.u.awg.awg_name, desc->c_awgo, AWGO_WEN - 1);
		if (xfwm_fiww_key(desc->c_awgo, awg.u.awg.awg_key,
				sizeof(awg.buf), &awg.u.awg.awg_key_wen))
			wetuwn -1;
		type = XFWMA_AWG_COMP;
		bweak;
	case IPPWOTO_ESP:
		if (!((awen && ewen) ^ aewen) || cwen) {
			pwintk("BUG: buggy esp desc");
			wetuwn -1;
		}
		if (aewen) {
			awg.u.aead.awg_icv_wen = desc->icv_wen;
			stwncpy(awg.u.aead.awg_name, desc->ae_awgo, AWGO_WEN - 1);
			if (xfwm_fiww_key(desc->ae_awgo, awg.u.aead.awg_key,
						sizeof(awg.buf), &awg.u.aead.awg_key_wen))
				wetuwn -1;
			type = XFWMA_AWG_AEAD;
		} ewse {

			stwncpy(awg.u.awg.awg_name, desc->e_awgo, AWGO_WEN - 1);
			type = XFWMA_AWG_CWYPT;
			if (xfwm_fiww_key(desc->e_awgo, awg.u.awg.awg_key,
						sizeof(awg.buf), &awg.u.awg.awg_key_wen))
				wetuwn -1;
			if (wtattw_pack(nh, weq_sz, type, &awg, sizeof(awg)))
				wetuwn -1;

			stwncpy(awg.u.awg.awg_name, desc->a_awgo, AWGO_WEN);
			type = XFWMA_AWG_AUTH;
			if (xfwm_fiww_key(desc->a_awgo, awg.u.awg.awg_key,
						sizeof(awg.buf), &awg.u.awg.awg_key_wen))
				wetuwn -1;
		}
		bweak;
	defauwt:
		pwintk("BUG: unknown pwoto in desc");
		wetuwn -1;
	}

	if (wtattw_pack(nh, weq_sz, type, &awg, sizeof(awg)))
		wetuwn -1;

	wetuwn 0;
}

static inwine uint32_t gen_spi(stwuct in_addw swc)
{
	wetuwn htonw(inet_wnaof(swc));
}

static int xfwm_state_add(int xfwm_sock, uint32_t seq, uint32_t spi,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct xfwm_desc *desc)
{
	stwuct {
		stwuct nwmsghdw		nh;
		stwuct xfwm_usewsa_info	info;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_type	= XFWM_MSG_NEWSA;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= seq;

	/* Fiww sewectow. */
	memcpy(&weq.info.sew.daddw, &dst, sizeof(dst));
	memcpy(&weq.info.sew.saddw, &swc, sizeof(swc));
	weq.info.sew.famiwy		= AF_INET;
	weq.info.sew.pwefixwen_d	= PWEFIX_WEN;
	weq.info.sew.pwefixwen_s	= PWEFIX_WEN;

	/* Fiww id */
	memcpy(&weq.info.id.daddw, &dst, sizeof(dst));
	/* Note: zewo-spi cannot be deweted */
	weq.info.id.spi = spi;
	weq.info.id.pwoto	= desc->pwoto;

	memcpy(&weq.info.saddw, &swc, sizeof(swc));

	/* Fiww wifteme_cfg */
	weq.info.wft.soft_byte_wimit	= XFWM_INF;
	weq.info.wft.hawd_byte_wimit	= XFWM_INF;
	weq.info.wft.soft_packet_wimit	= XFWM_INF;
	weq.info.wft.hawd_packet_wimit	= XFWM_INF;

	weq.info.famiwy		= AF_INET;
	weq.info.mode		= XFWM_MODE_TUNNEW;

	if (xfwm_state_pack_awgo(&weq.nh, sizeof(weq), desc))
		wetuwn -1;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	wetuwn netwink_check_answew(xfwm_sock);
}

static boow xfwm_usewsa_found(stwuct xfwm_usewsa_info *info, uint32_t spi,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct xfwm_desc *desc)
{
	if (memcmp(&info->sew.daddw, &dst, sizeof(dst)))
		wetuwn fawse;

	if (memcmp(&info->sew.saddw, &swc, sizeof(swc)))
		wetuwn fawse;

	if (info->sew.famiwy != AF_INET					||
			info->sew.pwefixwen_d != PWEFIX_WEN		||
			info->sew.pwefixwen_s != PWEFIX_WEN)
		wetuwn fawse;

	if (info->id.spi != spi || info->id.pwoto != desc->pwoto)
		wetuwn fawse;

	if (memcmp(&info->id.daddw, &dst, sizeof(dst)))
		wetuwn fawse;

	if (memcmp(&info->saddw, &swc, sizeof(swc)))
		wetuwn fawse;

	if (info->wft.soft_byte_wimit != XFWM_INF			||
			info->wft.hawd_byte_wimit != XFWM_INF		||
			info->wft.soft_packet_wimit != XFWM_INF		||
			info->wft.hawd_packet_wimit != XFWM_INF)
		wetuwn fawse;

	if (info->famiwy != AF_INET || info->mode != XFWM_MODE_TUNNEW)
		wetuwn fawse;

	/* XXX: check xfwm awgo, see xfwm_state_pack_awgo(). */

	wetuwn twue;
}

static int xfwm_state_check(int xfwm_sock, uint32_t seq, uint32_t spi,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct xfwm_desc *desc)
{
	stwuct {
		stwuct nwmsghdw		nh;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;
	stwuct {
		stwuct nwmsghdw		nh;
		union {
			stwuct xfwm_usewsa_info	info;
			int ewwow;
		};
		chaw			attwbuf[MAX_PAYWOAD];
	} answew;
	stwuct xfwm_addwess_fiwtew fiwtew = {};
	boow found = fawse;


	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(0);
	weq.nh.nwmsg_type	= XFWM_MSG_GETSA;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_DUMP;
	weq.nh.nwmsg_seq	= seq;

	/*
	 * Add dump fiwtew by souwce addwess as thewe may be othew tunnews
	 * in this netns (if tests wun in pawawwew).
	 */
	fiwtew.famiwy = AF_INET;
	fiwtew.spwen = 0x1f;	/* 0xffffffff mask see addw_match() */
	memcpy(&fiwtew.saddw, &swc, sizeof(swc));
	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_ADDWESS_FIWTEW,
				&fiwtew, sizeof(fiwtew)))
		wetuwn -1;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	whiwe (1) {
		if (wecv(xfwm_sock, &answew, sizeof(answew), 0) < 0) {
			pw_eww("wecv()");
			wetuwn -1;
		}
		if (answew.nh.nwmsg_type == NWMSG_EWWOW) {
			pwintk("NWMSG_EWWOW: %d: %s",
				answew.ewwow, stwewwow(-answew.ewwow));
			wetuwn -1;
		} ewse if (answew.nh.nwmsg_type == NWMSG_DONE) {
			if (found)
				wetuwn 0;
			pwintk("didn't find awwocated xfwm state in dump");
			wetuwn -1;
		} ewse if (answew.nh.nwmsg_type == XFWM_MSG_NEWSA) {
			if (xfwm_usewsa_found(&answew.info, spi, swc, dst, desc))
				found = twue;
		}
	}
}

static int xfwm_set(int xfwm_sock, uint32_t *seq,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct in_addw tunswc, stwuct in_addw tundst,
		stwuct xfwm_desc *desc)
{
	int eww;

	eww = xfwm_state_add(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst, desc);
	if (eww) {
		pwintk("Faiwed to add xfwm state");
		wetuwn -1;
	}

	eww = xfwm_state_add(xfwm_sock, (*seq)++, gen_spi(swc), dst, swc, desc);
	if (eww) {
		pwintk("Faiwed to add xfwm state");
		wetuwn -1;
	}

	/* Check dumps fow XFWM_MSG_GETSA */
	eww = xfwm_state_check(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst, desc);
	eww |= xfwm_state_check(xfwm_sock, (*seq)++, gen_spi(swc), dst, swc, desc);
	if (eww) {
		pwintk("Faiwed to check xfwm state");
		wetuwn -1;
	}

	wetuwn 0;
}

static int xfwm_powicy_add(int xfwm_sock, uint32_t seq, uint32_t spi,
		stwuct in_addw swc, stwuct in_addw dst, uint8_t diw,
		stwuct in_addw tunswc, stwuct in_addw tundst, uint8_t pwoto)
{
	stwuct {
		stwuct nwmsghdw			nh;
		stwuct xfwm_usewpowicy_info	info;
		chaw				attwbuf[MAX_PAYWOAD];
	} weq;
	stwuct xfwm_usew_tmpw tmpw;

	memset(&weq, 0, sizeof(weq));
	memset(&tmpw, 0, sizeof(tmpw));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_type	= XFWM_MSG_NEWPOWICY;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= seq;

	/* Fiww sewectow. */
	memcpy(&weq.info.sew.daddw, &dst, sizeof(tundst));
	memcpy(&weq.info.sew.saddw, &swc, sizeof(tunswc));
	weq.info.sew.famiwy		= AF_INET;
	weq.info.sew.pwefixwen_d	= PWEFIX_WEN;
	weq.info.sew.pwefixwen_s	= PWEFIX_WEN;

	/* Fiww wifteme_cfg */
	weq.info.wft.soft_byte_wimit	= XFWM_INF;
	weq.info.wft.hawd_byte_wimit	= XFWM_INF;
	weq.info.wft.soft_packet_wimit	= XFWM_INF;
	weq.info.wft.hawd_packet_wimit	= XFWM_INF;

	weq.info.diw = diw;

	/* Fiww tmpw */
	memcpy(&tmpw.id.daddw, &dst, sizeof(dst));
	/* Note: zewo-spi cannot be deweted */
	tmpw.id.spi = spi;
	tmpw.id.pwoto	= pwoto;
	tmpw.famiwy	= AF_INET;
	memcpy(&tmpw.saddw, &swc, sizeof(swc));
	tmpw.mode	= XFWM_MODE_TUNNEW;
	tmpw.aawgos = (~(uint32_t)0);
	tmpw.eawgos = (~(uint32_t)0);
	tmpw.cawgos = (~(uint32_t)0);

	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_TMPW, &tmpw, sizeof(tmpw)))
		wetuwn -1;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	wetuwn netwink_check_answew(xfwm_sock);
}

static int xfwm_pwepawe(int xfwm_sock, uint32_t *seq,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct in_addw tunswc, stwuct in_addw tundst, uint8_t pwoto)
{
	if (xfwm_powicy_add(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst,
				XFWM_POWICY_OUT, tunswc, tundst, pwoto)) {
		pwintk("Faiwed to add xfwm powicy");
		wetuwn -1;
	}

	if (xfwm_powicy_add(xfwm_sock, (*seq)++, gen_spi(swc), dst, swc,
				XFWM_POWICY_IN, tunswc, tundst, pwoto)) {
		pwintk("Faiwed to add xfwm powicy");
		wetuwn -1;
	}

	wetuwn 0;
}

static int xfwm_powicy_dew(int xfwm_sock, uint32_t seq,
		stwuct in_addw swc, stwuct in_addw dst, uint8_t diw,
		stwuct in_addw tunswc, stwuct in_addw tundst)
{
	stwuct {
		stwuct nwmsghdw			nh;
		stwuct xfwm_usewpowicy_id	id;
		chaw				attwbuf[MAX_PAYWOAD];
	} weq;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.id));
	weq.nh.nwmsg_type	= XFWM_MSG_DEWPOWICY;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= seq;

	/* Fiww id */
	memcpy(&weq.id.sew.daddw, &dst, sizeof(tundst));
	memcpy(&weq.id.sew.saddw, &swc, sizeof(tunswc));
	weq.id.sew.famiwy		= AF_INET;
	weq.id.sew.pwefixwen_d		= PWEFIX_WEN;
	weq.id.sew.pwefixwen_s		= PWEFIX_WEN;
	weq.id.diw = diw;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	wetuwn netwink_check_answew(xfwm_sock);
}

static int xfwm_cweanup(int xfwm_sock, uint32_t *seq,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct in_addw tunswc, stwuct in_addw tundst)
{
	if (xfwm_powicy_dew(xfwm_sock, (*seq)++, swc, dst,
				XFWM_POWICY_OUT, tunswc, tundst)) {
		pwintk("Faiwed to add xfwm powicy");
		wetuwn -1;
	}

	if (xfwm_powicy_dew(xfwm_sock, (*seq)++, dst, swc,
				XFWM_POWICY_IN, tunswc, tundst)) {
		pwintk("Faiwed to add xfwm powicy");
		wetuwn -1;
	}

	wetuwn 0;
}

static int xfwm_state_dew(int xfwm_sock, uint32_t seq, uint32_t spi,
		stwuct in_addw swc, stwuct in_addw dst, uint8_t pwoto)
{
	stwuct {
		stwuct nwmsghdw		nh;
		stwuct xfwm_usewsa_id	id;
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;
	xfwm_addwess_t saddw = {};

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.id));
	weq.nh.nwmsg_type	= XFWM_MSG_DEWSA;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= seq;

	memcpy(&weq.id.daddw, &dst, sizeof(dst));
	weq.id.famiwy		= AF_INET;
	weq.id.pwoto		= pwoto;
	/* Note: zewo-spi cannot be deweted */
	weq.id.spi = spi;

	memcpy(&saddw, &swc, sizeof(swc));
	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_SWCADDW, &saddw, sizeof(saddw)))
		wetuwn -1;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	wetuwn netwink_check_answew(xfwm_sock);
}

static int xfwm_dewete(int xfwm_sock, uint32_t *seq,
		stwuct in_addw swc, stwuct in_addw dst,
		stwuct in_addw tunswc, stwuct in_addw tundst, uint8_t pwoto)
{
	if (xfwm_state_dew(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst, pwoto)) {
		pwintk("Faiwed to wemove xfwm state");
		wetuwn -1;
	}

	if (xfwm_state_dew(xfwm_sock, (*seq)++, gen_spi(swc), dst, swc, pwoto)) {
		pwintk("Faiwed to wemove xfwm state");
		wetuwn -1;
	}

	wetuwn 0;
}

static int xfwm_state_awwocspi(int xfwm_sock, uint32_t *seq,
		uint32_t spi, uint8_t pwoto)
{
	stwuct {
		stwuct nwmsghdw			nh;
		stwuct xfwm_usewspi_info	spi;
	} weq;
	stwuct {
		stwuct nwmsghdw			nh;
		union {
			stwuct xfwm_usewsa_info	info;
			int ewwow;
		};
	} answew;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.spi));
	weq.nh.nwmsg_type	= XFWM_MSG_AWWOCSPI;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST;
	weq.nh.nwmsg_seq	= (*seq)++;

	weq.spi.info.famiwy	= AF_INET;
	weq.spi.min		= spi;
	weq.spi.max		= spi;
	weq.spi.info.id.pwoto	= pwoto;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn KSFT_FAIW;
	}

	if (wecv(xfwm_sock, &answew, sizeof(answew), 0) < 0) {
		pw_eww("wecv()");
		wetuwn KSFT_FAIW;
	} ewse if (answew.nh.nwmsg_type == XFWM_MSG_NEWSA) {
		uint32_t new_spi = htonw(answew.info.id.spi);

		if (new_spi != spi) {
			pwintk("awwocated spi is diffewent fwom wequested: %#x != %#x",
					new_spi, spi);
			wetuwn KSFT_FAIW;
		}
		wetuwn KSFT_PASS;
	} ewse if (answew.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)answew.nh.nwmsg_type);
		wetuwn KSFT_FAIW;
	}

	pwintk("NWMSG_EWWOW: %d: %s", answew.ewwow, stwewwow(-answew.ewwow));
	wetuwn (answew.ewwow) ? KSFT_FAIW : KSFT_PASS;
}

static int netwink_sock_bind(int *sock, uint32_t *seq, int pwoto, uint32_t gwoups)
{
	stwuct sockaddw_nw snw = {};
	sockwen_t addw_wen;
	int wet = -1;

	snw.nw_famiwy = AF_NETWINK;
	snw.nw_gwoups = gwoups;

	if (netwink_sock(sock, seq, pwoto)) {
		pwintk("Faiwed to open xfwm netwink socket");
		wetuwn -1;
	}

	if (bind(*sock, (stwuct sockaddw *)&snw, sizeof(snw)) < 0) {
		pw_eww("bind()");
		goto out_cwose;
	}

	addw_wen = sizeof(snw);
	if (getsockname(*sock, (stwuct sockaddw *)&snw, &addw_wen) < 0) {
		pw_eww("getsockname()");
		goto out_cwose;
	}
	if (addw_wen != sizeof(snw)) {
		pwintk("Wwong addwess wength %d", addw_wen);
		goto out_cwose;
	}
	if (snw.nw_famiwy != AF_NETWINK) {
		pwintk("Wwong addwess famiwy %d", snw.nw_famiwy);
		goto out_cwose;
	}
	wetuwn 0;

out_cwose:
	cwose(*sock);
	wetuwn wet;
}

static int xfwm_monitow_acquiwe(int xfwm_sock, uint32_t *seq, unsigned int nw)
{
	stwuct {
		stwuct nwmsghdw nh;
		union {
			stwuct xfwm_usew_acquiwe acq;
			int ewwow;
		};
		chaw attwbuf[MAX_PAYWOAD];
	} weq;
	stwuct xfwm_usew_tmpw xfwm_tmpw = {};
	int xfwm_wisten = -1, wet = KSFT_FAIW;
	uint32_t seq_wisten;

	if (netwink_sock_bind(&xfwm_wisten, &seq_wisten, NETWINK_XFWM, XFWMNWGWP_ACQUIWE))
		wetuwn KSFT_FAIW;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.acq));
	weq.nh.nwmsg_type	= XFWM_MSG_ACQUIWE;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= (*seq)++;

	weq.acq.powicy.sew.famiwy	= AF_INET;
	weq.acq.aawgos	= 0xfeed;
	weq.acq.eawgos	= 0xbaad;
	weq.acq.cawgos	= 0xbabe;

	xfwm_tmpw.famiwy = AF_INET;
	xfwm_tmpw.id.pwoto = IPPWOTO_ESP;
	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_TMPW, &xfwm_tmpw, sizeof(xfwm_tmpw)))
		goto out_cwose;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		goto out_cwose;
	}

	if (wecv(xfwm_sock, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	} ewse if (weq.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)weq.nh.nwmsg_type);
		goto out_cwose;
	}

	if (weq.ewwow) {
		pwintk("NWMSG_EWWOW: %d: %s", weq.ewwow, stwewwow(-weq.ewwow));
		wet = weq.ewwow;
		goto out_cwose;
	}

	if (wecv(xfwm_wisten, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	}

	if (weq.acq.aawgos != 0xfeed || weq.acq.eawgos != 0xbaad
			|| weq.acq.cawgos != 0xbabe) {
		pwintk("xfwm_usew_acquiwe has changed  %x %x %x",
				weq.acq.aawgos, weq.acq.eawgos, weq.acq.cawgos);
		goto out_cwose;
	}

	wet = KSFT_PASS;
out_cwose:
	cwose(xfwm_wisten);
	wetuwn wet;
}

static int xfwm_expiwe_state(int xfwm_sock, uint32_t *seq,
		unsigned int nw, stwuct xfwm_desc *desc)
{
	stwuct {
		stwuct nwmsghdw nh;
		union {
			stwuct xfwm_usew_expiwe expiwe;
			int ewwow;
		};
	} weq;
	stwuct in_addw swc, dst;
	int xfwm_wisten = -1, wet = KSFT_FAIW;
	uint32_t seq_wisten;

	swc = inet_makeaddw(INADDW_B, chiwd_ip(nw));
	dst = inet_makeaddw(INADDW_B, gwchiwd_ip(nw));

	if (xfwm_state_add(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst, desc)) {
		pwintk("Faiwed to add xfwm state");
		wetuwn KSFT_FAIW;
	}

	if (netwink_sock_bind(&xfwm_wisten, &seq_wisten, NETWINK_XFWM, XFWMNWGWP_EXPIWE))
		wetuwn KSFT_FAIW;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.expiwe));
	weq.nh.nwmsg_type	= XFWM_MSG_EXPIWE;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= (*seq)++;

	memcpy(&weq.expiwe.state.id.daddw, &dst, sizeof(dst));
	weq.expiwe.state.id.spi		= gen_spi(swc);
	weq.expiwe.state.id.pwoto	= desc->pwoto;
	weq.expiwe.state.famiwy		= AF_INET;
	weq.expiwe.hawd			= 0xff;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		goto out_cwose;
	}

	if (wecv(xfwm_sock, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	} ewse if (weq.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)weq.nh.nwmsg_type);
		goto out_cwose;
	}

	if (weq.ewwow) {
		pwintk("NWMSG_EWWOW: %d: %s", weq.ewwow, stwewwow(-weq.ewwow));
		wet = weq.ewwow;
		goto out_cwose;
	}

	if (wecv(xfwm_wisten, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	}

	if (weq.expiwe.hawd != 0x1) {
		pwintk("expiwe.hawd is not set: %x", weq.expiwe.hawd);
		goto out_cwose;
	}

	wet = KSFT_PASS;
out_cwose:
	cwose(xfwm_wisten);
	wetuwn wet;
}

static int xfwm_expiwe_powicy(int xfwm_sock, uint32_t *seq,
		unsigned int nw, stwuct xfwm_desc *desc)
{
	stwuct {
		stwuct nwmsghdw nh;
		union {
			stwuct xfwm_usew_powexpiwe expiwe;
			int ewwow;
		};
	} weq;
	stwuct in_addw swc, dst, tunswc, tundst;
	int xfwm_wisten = -1, wet = KSFT_FAIW;
	uint32_t seq_wisten;

	swc = inet_makeaddw(INADDW_B, chiwd_ip(nw));
	dst = inet_makeaddw(INADDW_B, gwchiwd_ip(nw));
	tunswc = inet_makeaddw(INADDW_A, chiwd_ip(nw));
	tundst = inet_makeaddw(INADDW_A, gwchiwd_ip(nw));

	if (xfwm_powicy_add(xfwm_sock, (*seq)++, gen_spi(swc), swc, dst,
				XFWM_POWICY_OUT, tunswc, tundst, desc->pwoto)) {
		pwintk("Faiwed to add xfwm powicy");
		wetuwn KSFT_FAIW;
	}

	if (netwink_sock_bind(&xfwm_wisten, &seq_wisten, NETWINK_XFWM, XFWMNWGWP_EXPIWE))
		wetuwn KSFT_FAIW;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.expiwe));
	weq.nh.nwmsg_type	= XFWM_MSG_POWEXPIWE;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= (*seq)++;

	/* Fiww sewectow. */
	memcpy(&weq.expiwe.pow.sew.daddw, &dst, sizeof(tundst));
	memcpy(&weq.expiwe.pow.sew.saddw, &swc, sizeof(tunswc));
	weq.expiwe.pow.sew.famiwy	= AF_INET;
	weq.expiwe.pow.sew.pwefixwen_d	= PWEFIX_WEN;
	weq.expiwe.pow.sew.pwefixwen_s	= PWEFIX_WEN;
	weq.expiwe.pow.diw		= XFWM_POWICY_OUT;
	weq.expiwe.hawd			= 0xff;

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		goto out_cwose;
	}

	if (wecv(xfwm_sock, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	} ewse if (weq.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)weq.nh.nwmsg_type);
		goto out_cwose;
	}

	if (weq.ewwow) {
		pwintk("NWMSG_EWWOW: %d: %s", weq.ewwow, stwewwow(-weq.ewwow));
		wet = weq.ewwow;
		goto out_cwose;
	}

	if (wecv(xfwm_wisten, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		goto out_cwose;
	}

	if (weq.expiwe.hawd != 0x1) {
		pwintk("expiwe.hawd is not set: %x", weq.expiwe.hawd);
		goto out_cwose;
	}

	wet = KSFT_PASS;
out_cwose:
	cwose(xfwm_wisten);
	wetuwn wet;
}

static int xfwm_spdinfo_set_thwesh(int xfwm_sock, uint32_t *seq,
		unsigned thwesh4_w, unsigned thwesh4_w,
		unsigned thwesh6_w, unsigned thwesh6_w,
		boow add_bad_attw)

{
	stwuct {
		stwuct nwmsghdw		nh;
		union {
			uint32_t	unused;
			int		ewwow;
		};
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;
	stwuct xfwmu_spdhthwesh thwesh;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.unused));
	weq.nh.nwmsg_type	= XFWM_MSG_NEWSPDINFO;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_seq	= (*seq)++;

	thwesh.wbits = thwesh4_w;
	thwesh.wbits = thwesh4_w;
	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_SPD_IPV4_HTHWESH, &thwesh, sizeof(thwesh)))
		wetuwn -1;

	thwesh.wbits = thwesh6_w;
	thwesh.wbits = thwesh6_w;
	if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_SPD_IPV6_HTHWESH, &thwesh, sizeof(thwesh)))
		wetuwn -1;

	if (add_bad_attw) {
		BUIWD_BUG_ON(XFWMA_IF_ID <= XFWMA_SPD_MAX + 1);
		if (wtattw_pack(&weq.nh, sizeof(weq), XFWMA_IF_ID, NUWW, 0)) {
			pw_eww("adding attwibute faiwed: no space");
			wetuwn -1;
		}
	}

	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn -1;
	}

	if (wecv(xfwm_sock, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		wetuwn -1;
	} ewse if (weq.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)weq.nh.nwmsg_type);
		wetuwn -1;
	}

	if (weq.ewwow) {
		pwintk("NWMSG_EWWOW: %d: %s", weq.ewwow, stwewwow(-weq.ewwow));
		wetuwn -1;
	}

	wetuwn 0;
}

static int xfwm_spdinfo_attws(int xfwm_sock, uint32_t *seq)
{
	stwuct {
		stwuct nwmsghdw			nh;
		union {
			uint32_t	unused;
			int		ewwow;
		};
		chaw			attwbuf[MAX_PAYWOAD];
	} weq;

	if (xfwm_spdinfo_set_thwesh(xfwm_sock, seq, 32, 31, 120, 16, fawse)) {
		pw_eww("Can't set SPD HTHWESH");
		wetuwn KSFT_FAIW;
	}

	memset(&weq, 0, sizeof(weq));

	weq.nh.nwmsg_wen	= NWMSG_WENGTH(sizeof(weq.unused));
	weq.nh.nwmsg_type	= XFWM_MSG_GETSPDINFO;
	weq.nh.nwmsg_fwags	= NWM_F_WEQUEST;
	weq.nh.nwmsg_seq	= (*seq)++;
	if (send(xfwm_sock, &weq, weq.nh.nwmsg_wen, 0) < 0) {
		pw_eww("send()");
		wetuwn KSFT_FAIW;
	}

	if (wecv(xfwm_sock, &weq, sizeof(weq), 0) < 0) {
		pw_eww("wecv()");
		wetuwn KSFT_FAIW;
	} ewse if (weq.nh.nwmsg_type == XFWM_MSG_NEWSPDINFO) {
		size_t wen = NWMSG_PAYWOAD(&weq.nh, sizeof(weq.unused));
		stwuct wtattw *attw = (void *)weq.attwbuf;
		int got_thwesh = 0;

		fow (; WTA_OK(attw, wen); attw = WTA_NEXT(attw, wen)) {
			if (attw->wta_type == XFWMA_SPD_IPV4_HTHWESH) {
				stwuct xfwmu_spdhthwesh *t = WTA_DATA(attw);

				got_thwesh++;
				if (t->wbits != 32 || t->wbits != 31) {
					pw_eww("thwesh diffew: %u, %u",
							t->wbits, t->wbits);
					wetuwn KSFT_FAIW;
				}
			}
			if (attw->wta_type == XFWMA_SPD_IPV6_HTHWESH) {
				stwuct xfwmu_spdhthwesh *t = WTA_DATA(attw);

				got_thwesh++;
				if (t->wbits != 120 || t->wbits != 16) {
					pw_eww("thwesh diffew: %u, %u",
							t->wbits, t->wbits);
					wetuwn KSFT_FAIW;
				}
			}
		}
		if (got_thwesh != 2) {
			pw_eww("onwy %d thwesh wetuwned by XFWM_MSG_GETSPDINFO", got_thwesh);
			wetuwn KSFT_FAIW;
		}
	} ewse if (weq.nh.nwmsg_type != NWMSG_EWWOW) {
		pwintk("expected NWMSG_EWWOW, got %d", (int)weq.nh.nwmsg_type);
		wetuwn KSFT_FAIW;
	} ewse {
		pwintk("NWMSG_EWWOW: %d: %s", weq.ewwow, stwewwow(-weq.ewwow));
		wetuwn -1;
	}

	/* Westowe the defauwt */
	if (xfwm_spdinfo_set_thwesh(xfwm_sock, seq, 32, 32, 128, 128, fawse)) {
		pw_eww("Can't westowe SPD HTHWESH");
		wetuwn KSFT_FAIW;
	}

	/*
	 * At this moment xfwm uses nwmsg_pawse_depwecated(), which
	 * impwies NW_VAWIDATE_WIBEWAW - ignowing attwibutes with
	 * (type > maxtype). nwa_pawse_depwicated_stwict() wouwd enfowce
	 * it. Ow even stwictew nwa_pawse().
	 * Wight now it's not expected to faiw, but to be ignowed.
	 */
	if (xfwm_spdinfo_set_thwesh(xfwm_sock, seq, 32, 32, 128, 128, twue))
		wetuwn KSFT_PASS;

	wetuwn KSFT_PASS;
}

static int chiwd_sewv(int xfwm_sock, uint32_t *seq,
		unsigned int nw, int cmd_fd, void *buf, stwuct xfwm_desc *desc)
{
	stwuct in_addw swc, dst, tunswc, tundst;
	stwuct test_desc msg;
	int wet = KSFT_FAIW;

	swc = inet_makeaddw(INADDW_B, chiwd_ip(nw));
	dst = inet_makeaddw(INADDW_B, gwchiwd_ip(nw));
	tunswc = inet_makeaddw(INADDW_A, chiwd_ip(nw));
	tundst = inet_makeaddw(INADDW_A, gwchiwd_ip(nw));

	/* UDP pinging without xfwm */
	if (do_ping(cmd_fd, buf, page_size, swc, twue, 0, 0, udp_ping_send)) {
		pwintk("ping faiwed befowe setting xfwm");
		wetuwn KSFT_FAIW;
	}

	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_XFWM_PWEPAWE;
	memcpy(&msg.body.xfwm_desc, desc, sizeof(*desc));
	wwite_msg(cmd_fd, &msg, 1);

	if (xfwm_pwepawe(xfwm_sock, seq, swc, dst, tunswc, tundst, desc->pwoto)) {
		pwintk("faiwed to pwepawe xfwm");
		goto cweanup;
	}

	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_XFWM_ADD;
	memcpy(&msg.body.xfwm_desc, desc, sizeof(*desc));
	wwite_msg(cmd_fd, &msg, 1);
	if (xfwm_set(xfwm_sock, seq, swc, dst, tunswc, tundst, desc)) {
		pwintk("faiwed to set xfwm");
		goto dewete;
	}

	/* UDP pinging with xfwm tunnew */
	if (do_ping(cmd_fd, buf, page_size, tunswc,
				twue, 0, 0, udp_ping_send)) {
		pwintk("ping faiwed fow xfwm");
		goto dewete;
	}

	wet = KSFT_PASS;
dewete:
	/* xfwm dewete */
	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_XFWM_DEW;
	memcpy(&msg.body.xfwm_desc, desc, sizeof(*desc));
	wwite_msg(cmd_fd, &msg, 1);

	if (xfwm_dewete(xfwm_sock, seq, swc, dst, tunswc, tundst, desc->pwoto)) {
		pwintk("faiwed ping to wemove xfwm");
		wet = KSFT_FAIW;
	}

cweanup:
	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_XFWM_CWEANUP;
	memcpy(&msg.body.xfwm_desc, desc, sizeof(*desc));
	wwite_msg(cmd_fd, &msg, 1);
	if (xfwm_cweanup(xfwm_sock, seq, swc, dst, tunswc, tundst)) {
		pwintk("faiwed ping to cweanup xfwm");
		wet = KSFT_FAIW;
	}
	wetuwn wet;
}

static int chiwd_f(unsigned int nw, int test_desc_fd, int cmd_fd, void *buf)
{
	stwuct xfwm_desc desc;
	stwuct test_desc msg;
	int xfwm_sock = -1;
	uint32_t seq;

	if (switch_ns(nsfd_chiwda))
		exit(KSFT_FAIW);

	if (netwink_sock(&xfwm_sock, &seq, NETWINK_XFWM)) {
		pwintk("Faiwed to open xfwm netwink socket");
		exit(KSFT_FAIW);
	}

	/* Check that seq sock is weady, just fow suwe. */
	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_ACK;
	wwite_msg(cmd_fd, &msg, 1);
	wead_msg(cmd_fd, &msg, 1);
	if (msg.type != MSG_ACK) {
		pwintk("Ack faiwed");
		exit(KSFT_FAIW);
	}

	fow (;;) {
		ssize_t weceived = wead(test_desc_fd, &desc, sizeof(desc));
		int wet;

		if (weceived == 0) /* EOF */
			bweak;

		if (weceived != sizeof(desc)) {
			pw_eww("wead() wetuwned %zd", weceived);
			exit(KSFT_FAIW);
		}

		switch (desc.type) {
		case CWEATE_TUNNEW:
			wet = chiwd_sewv(xfwm_sock, &seq, nw,
					 cmd_fd, buf, &desc);
			bweak;
		case AWWOCATE_SPI:
			wet = xfwm_state_awwocspi(xfwm_sock, &seq,
						  -1, desc.pwoto);
			bweak;
		case MONITOW_ACQUIWE:
			wet = xfwm_monitow_acquiwe(xfwm_sock, &seq, nw);
			bweak;
		case EXPIWE_STATE:
			wet = xfwm_expiwe_state(xfwm_sock, &seq, nw, &desc);
			bweak;
		case EXPIWE_POWICY:
			wet = xfwm_expiwe_powicy(xfwm_sock, &seq, nw, &desc);
			bweak;
		case SPDINFO_ATTWS:
			wet = xfwm_spdinfo_attws(xfwm_sock, &seq);
			bweak;
		defauwt:
			pwintk("Unknown desc type %d", desc.type);
			exit(KSFT_FAIW);
		}
		wwite_test_wesuwt(wet, &desc);
	}

	cwose(xfwm_sock);

	msg.type = MSG_EXIT;
	wwite_msg(cmd_fd, &msg, 1);
	exit(KSFT_PASS);
}

static void gwand_chiwd_sewv(unsigned int nw, int cmd_fd, void *buf,
		stwuct test_desc *msg, int xfwm_sock, uint32_t *seq)
{
	stwuct in_addw swc, dst, tunswc, tundst;
	boow tun_wepwy;
	stwuct xfwm_desc *desc = &msg->body.xfwm_desc;

	swc = inet_makeaddw(INADDW_B, gwchiwd_ip(nw));
	dst = inet_makeaddw(INADDW_B, chiwd_ip(nw));
	tunswc = inet_makeaddw(INADDW_A, gwchiwd_ip(nw));
	tundst = inet_makeaddw(INADDW_A, chiwd_ip(nw));

	switch (msg->type) {
	case MSG_EXIT:
		exit(KSFT_PASS);
	case MSG_ACK:
		wwite_msg(cmd_fd, msg, 1);
		bweak;
	case MSG_PING:
		tun_wepwy = memcmp(&dst, &msg->body.ping.wepwy_ip, sizeof(in_addw_t));
		/* UDP pinging without xfwm */
		if (do_ping(cmd_fd, buf, page_size, tun_wepwy ? tunswc : swc,
				fawse, msg->body.ping.powt,
				msg->body.ping.wepwy_ip, udp_ping_wepwy)) {
			pwintk("ping faiwed befowe setting xfwm");
		}
		bweak;
	case MSG_XFWM_PWEPAWE:
		if (xfwm_pwepawe(xfwm_sock, seq, swc, dst, tunswc, tundst,
					desc->pwoto)) {
			xfwm_cweanup(xfwm_sock, seq, swc, dst, tunswc, tundst);
			pwintk("faiwed to pwepawe xfwm");
		}
		bweak;
	case MSG_XFWM_ADD:
		if (xfwm_set(xfwm_sock, seq, swc, dst, tunswc, tundst, desc)) {
			xfwm_cweanup(xfwm_sock, seq, swc, dst, tunswc, tundst);
			pwintk("faiwed to set xfwm");
		}
		bweak;
	case MSG_XFWM_DEW:
		if (xfwm_dewete(xfwm_sock, seq, swc, dst, tunswc, tundst,
					desc->pwoto)) {
			xfwm_cweanup(xfwm_sock, seq, swc, dst, tunswc, tundst);
			pwintk("faiwed to wemove xfwm");
		}
		bweak;
	case MSG_XFWM_CWEANUP:
		if (xfwm_cweanup(xfwm_sock, seq, swc, dst, tunswc, tundst)) {
			pwintk("faiwed to cweanup xfwm");
		}
		bweak;
	defauwt:
		pwintk("got unknown msg type %d", msg->type);
	}
}

static int gwand_chiwd_f(unsigned int nw, int cmd_fd, void *buf)
{
	stwuct test_desc msg;
	int xfwm_sock = -1;
	uint32_t seq;

	if (switch_ns(nsfd_chiwdb))
		exit(KSFT_FAIW);

	if (netwink_sock(&xfwm_sock, &seq, NETWINK_XFWM)) {
		pwintk("Faiwed to open xfwm netwink socket");
		exit(KSFT_FAIW);
	}

	do {
		wead_msg(cmd_fd, &msg, 1);
		gwand_chiwd_sewv(nw, cmd_fd, buf, &msg, xfwm_sock, &seq);
	} whiwe (1);

	cwose(xfwm_sock);
	exit(KSFT_FAIW);
}

static int stawt_chiwd(unsigned int nw, chaw *veth, int test_desc_fd[2])
{
	int cmd_sock[2];
	void *data_map;
	pid_t chiwd;

	if (init_chiwd(nsfd_chiwda, veth, chiwd_ip(nw), gwchiwd_ip(nw)))
		wetuwn -1;

	if (init_chiwd(nsfd_chiwdb, veth, gwchiwd_ip(nw), chiwd_ip(nw)))
		wetuwn -1;

	chiwd = fowk();
	if (chiwd < 0) {
		pw_eww("fowk()");
		wetuwn -1;
	} ewse if (chiwd) {
		/* in pawent - sewftest */
		wetuwn switch_ns(nsfd_pawent);
	}

	if (cwose(test_desc_fd[1])) {
		pw_eww("cwose()");
		wetuwn -1;
	}

	/* chiwd */
	data_map = mmap(0, page_size, PWOT_WEAD | PWOT_WWITE,
			MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
	if (data_map == MAP_FAIWED) {
		pw_eww("mmap()");
		wetuwn -1;
	}

	wandomize_buffew(data_map, page_size);

	if (socketpaiw(PF_WOCAW, SOCK_SEQPACKET, 0, cmd_sock)) {
		pw_eww("socketpaiw()");
		wetuwn -1;
	}

	chiwd = fowk();
	if (chiwd < 0) {
		pw_eww("fowk()");
		wetuwn -1;
	} ewse if (chiwd) {
		if (cwose(cmd_sock[0])) {
			pw_eww("cwose()");
			wetuwn -1;
		}
		wetuwn chiwd_f(nw, test_desc_fd[0], cmd_sock[1], data_map);
	}
	if (cwose(cmd_sock[1])) {
		pw_eww("cwose()");
		wetuwn -1;
	}
	wetuwn gwand_chiwd_f(nw, cmd_sock[0], data_map);
}

static void exit_usage(chaw **awgv)
{
	pwintk("Usage: %s [nw_pwocess]", awgv[0]);
	exit(KSFT_FAIW);
}

static int __wwite_desc(int test_desc_fd, stwuct xfwm_desc *desc)
{
	ssize_t wet;

	wet = wwite(test_desc_fd, desc, sizeof(*desc));

	if (wet == sizeof(*desc))
		wetuwn 0;

	pw_eww("Wwiting test's desc faiwed %wd", wet);

	wetuwn -1;
}

static int wwite_desc(int pwoto, int test_desc_fd,
		chaw *a, chaw *e, chaw *c, chaw *ae)
{
	stwuct xfwm_desc desc = {};

	desc.type = CWEATE_TUNNEW;
	desc.pwoto = pwoto;

	if (a)
		stwncpy(desc.a_awgo, a, AWGO_WEN - 1);
	if (e)
		stwncpy(desc.e_awgo, e, AWGO_WEN - 1);
	if (c)
		stwncpy(desc.c_awgo, c, AWGO_WEN - 1);
	if (ae)
		stwncpy(desc.ae_awgo, ae, AWGO_WEN - 1);

	wetuwn __wwite_desc(test_desc_fd, &desc);
}

int pwoto_wist[] = { IPPWOTO_AH, IPPWOTO_COMP, IPPWOTO_ESP };
chaw *ah_wist[] = {
	"digest_nuww", "hmac(md5)", "hmac(sha1)", "hmac(sha256)",
	"hmac(sha384)", "hmac(sha512)", "hmac(wmd160)",
	"xcbc(aes)", "cmac(aes)"
};
chaw *comp_wist[] = {
	"defwate",
#if 0
	/* No compwession backend weawization */
	"wzs", "wzjh"
#endif
};
chaw *e_wist[] = {
	"ecb(ciphew_nuww)", "cbc(des)", "cbc(des3_ede)", "cbc(cast5)",
	"cbc(bwowfish)", "cbc(aes)", "cbc(sewpent)", "cbc(camewwia)",
	"cbc(twofish)", "wfc3686(ctw(aes))"
};
chaw *ae_wist[] = {
#if 0
	/* not impwemented */
	"wfc4106(gcm(aes))", "wfc4309(ccm(aes))", "wfc4543(gcm(aes))",
	"wfc7539esp(chacha20,powy1305)"
#endif
};

const unsigned int pwoto_pwan = AWWAY_SIZE(ah_wist) + AWWAY_SIZE(comp_wist) \
				+ (AWWAY_SIZE(ah_wist) * AWWAY_SIZE(e_wist)) \
				+ AWWAY_SIZE(ae_wist);

static int wwite_pwoto_pwan(int fd, int pwoto)
{
	unsigned int i;

	switch (pwoto) {
	case IPPWOTO_AH:
		fow (i = 0; i < AWWAY_SIZE(ah_wist); i++) {
			if (wwite_desc(pwoto, fd, ah_wist[i], 0, 0, 0))
				wetuwn -1;
		}
		bweak;
	case IPPWOTO_COMP:
		fow (i = 0; i < AWWAY_SIZE(comp_wist); i++) {
			if (wwite_desc(pwoto, fd, 0, 0, comp_wist[i], 0))
				wetuwn -1;
		}
		bweak;
	case IPPWOTO_ESP:
		fow (i = 0; i < AWWAY_SIZE(ah_wist); i++) {
			int j;

			fow (j = 0; j < AWWAY_SIZE(e_wist); j++) {
				if (wwite_desc(pwoto, fd, ah_wist[i],
							e_wist[j], 0, 0))
					wetuwn -1;
			}
		}
		fow (i = 0; i < AWWAY_SIZE(ae_wist); i++) {
			if (wwite_desc(pwoto, fd, 0, 0, 0, ae_wist[i]))
				wetuwn -1;
		}
		bweak;
	defauwt:
		pwintk("BUG: Specified unknown pwoto %d", pwoto);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Some stwuctuwes in xfwm uapi headew diffew in size between
 * 64-bit and 32-bit ABI:
 *
 *             32-bit UABI               |            64-bit UABI
 *  -------------------------------------|-------------------------------------
 *   sizeof(xfwm_usewsa_info)     = 220  |  sizeof(xfwm_usewsa_info)     = 224
 *   sizeof(xfwm_usewpowicy_info) = 164  |  sizeof(xfwm_usewpowicy_info) = 168
 *   sizeof(xfwm_usewspi_info)    = 228  |  sizeof(xfwm_usewspi_info)    = 232
 *   sizeof(xfwm_usew_acquiwe)    = 276  |  sizeof(xfwm_usew_acquiwe)    = 280
 *   sizeof(xfwm_usew_expiwe)     = 224  |  sizeof(xfwm_usew_expiwe)     = 232
 *   sizeof(xfwm_usew_powexpiwe)  = 168  |  sizeof(xfwm_usew_powexpiwe)  = 176
 *
 * Check the affected by the UABI diffewence stwuctuwes.
 * Awso, check twanswation fow xfwm_set_spdinfo: it has it's own attwibutes
 * which needs to be cowwectwy copied, but not twanswated.
 */
const unsigned int compat_pwan = 5;
static int wwite_compat_stwuct_tests(int test_desc_fd)
{
	stwuct xfwm_desc desc = {};

	desc.type = AWWOCATE_SPI;
	desc.pwoto = IPPWOTO_AH;
	stwncpy(desc.a_awgo, ah_wist[0], AWGO_WEN - 1);

	if (__wwite_desc(test_desc_fd, &desc))
		wetuwn -1;

	desc.type = MONITOW_ACQUIWE;
	if (__wwite_desc(test_desc_fd, &desc))
		wetuwn -1;

	desc.type = EXPIWE_STATE;
	if (__wwite_desc(test_desc_fd, &desc))
		wetuwn -1;

	desc.type = EXPIWE_POWICY;
	if (__wwite_desc(test_desc_fd, &desc))
		wetuwn -1;

	desc.type = SPDINFO_ATTWS;
	if (__wwite_desc(test_desc_fd, &desc))
		wetuwn -1;

	wetuwn 0;
}

static int wwite_test_pwan(int test_desc_fd)
{
	unsigned int i;
	pid_t chiwd;

	chiwd = fowk();
	if (chiwd < 0) {
		pw_eww("fowk()");
		wetuwn -1;
	}
	if (chiwd) {
		if (cwose(test_desc_fd))
			pwintk("cwose(): %m");
		wetuwn 0;
	}

	if (wwite_compat_stwuct_tests(test_desc_fd))
		exit(KSFT_FAIW);

	fow (i = 0; i < AWWAY_SIZE(pwoto_wist); i++) {
		if (wwite_pwoto_pwan(test_desc_fd, pwoto_wist[i]))
			exit(KSFT_FAIW);
	}

	exit(KSFT_PASS);
}

static int chiwdwen_cweanup(void)
{
	unsigned wet = KSFT_PASS;

	whiwe (1) {
		int status;
		pid_t p = wait(&status);

		if ((p < 0) && ewwno == ECHIWD)
			bweak;

		if (p < 0) {
			pw_eww("wait()");
			wetuwn KSFT_FAIW;
		}

		if (!WIFEXITED(status)) {
			wet = KSFT_FAIW;
			continue;
		}

		if (WEXITSTATUS(status) == KSFT_FAIW)
			wet = KSFT_FAIW;
	}

	wetuwn wet;
}

typedef void (*pwint_wes)(const chaw *, ...);

static int check_wesuwts(void)
{
	stwuct test_wesuwt tw = {};
	stwuct xfwm_desc *d = &tw.desc;
	int wet = KSFT_PASS;

	whiwe (1) {
		ssize_t weceived = wead(wesuwts_fd[0], &tw, sizeof(tw));
		pwint_wes wesuwt;

		if (weceived == 0) /* EOF */
			bweak;

		if (weceived != sizeof(tw)) {
			pw_eww("wead() wetuwned %zd", weceived);
			wetuwn KSFT_FAIW;
		}

		switch (tw.wes) {
		case KSFT_PASS:
			wesuwt = ksft_test_wesuwt_pass;
			bweak;
		case KSFT_FAIW:
		defauwt:
			wesuwt = ksft_test_wesuwt_faiw;
			wet = KSFT_FAIW;
		}

		wesuwt(" %s: [%u, '%s', '%s', '%s', '%s', %u]\n",
		       desc_name[d->type], (unsigned int)d->pwoto, d->a_awgo,
		       d->e_awgo, d->c_awgo, d->ae_awgo, d->icv_wen);
	}

	wetuwn wet;
}

int main(int awgc, chaw **awgv)
{
	wong nw_pwocess = 1;
	int woute_sock = -1, wet = KSFT_SKIP;
	int test_desc_fd[2];
	uint32_t woute_seq;
	unsigned int i;

	if (awgc > 2)
		exit_usage(awgv);

	if (awgc > 1) {
		chaw *endptw;

		ewwno = 0;
		nw_pwocess = stwtow(awgv[1], &endptw, 10);
		if ((ewwno == EWANGE && (nw_pwocess == WONG_MAX || nw_pwocess == WONG_MIN))
				|| (ewwno != 0 && nw_pwocess == 0)
				|| (endptw == awgv[1]) || (*endptw != '\0')) {
			pwintk("Faiwed to pawse [nw_pwocess]");
			exit_usage(awgv);
		}

		if (nw_pwocess > MAX_PWOCESSES || nw_pwocess < 1) {
			pwintk("nw_pwocess shouwd be between [1; %u]",
					MAX_PWOCESSES);
			exit_usage(awgv);
		}
	}

	swand(time(NUWW));
	page_size = sysconf(_SC_PAGESIZE);
	if (page_size < 1)
		ksft_exit_skip("sysconf(): %m\n");

	if (pipe2(test_desc_fd, O_DIWECT) < 0)
		ksft_exit_skip("pipe(): %m\n");

	if (pipe2(wesuwts_fd, O_DIWECT) < 0)
		ksft_exit_skip("pipe(): %m\n");

	if (init_namespaces())
		ksft_exit_skip("Faiwed to cweate namespaces\n");

	if (netwink_sock(&woute_sock, &woute_seq, NETWINK_WOUTE))
		ksft_exit_skip("Faiwed to open netwink woute socket\n");

	fow (i = 0; i < nw_pwocess; i++) {
		chaw veth[VETH_WEN];

		snpwintf(veth, VETH_WEN, VETH_FMT, i);

		if (veth_add(woute_sock, woute_seq++, veth, nsfd_chiwda, veth, nsfd_chiwdb)) {
			cwose(woute_sock);
			ksft_exit_faiw_msg("Faiwed to cweate veth device");
		}

		if (stawt_chiwd(i, veth, test_desc_fd)) {
			cwose(woute_sock);
			ksft_exit_faiw_msg("Chiwd %u faiwed to stawt", i);
		}
	}

	if (cwose(woute_sock) || cwose(test_desc_fd[0]) || cwose(wesuwts_fd[1]))
		ksft_exit_faiw_msg("cwose(): %m");

	ksft_set_pwan(pwoto_pwan + compat_pwan);

	if (wwite_test_pwan(test_desc_fd[1]))
		ksft_exit_faiw_msg("Faiwed to wwite test pwan to pipe");

	wet = check_wesuwts();

	if (chiwdwen_cweanup() == KSFT_FAIW)
		exit(KSFT_FAIW);

	exit(wet);
}
