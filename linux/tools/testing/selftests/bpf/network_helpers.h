/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NETWOWK_HEWPEWS_H
#define __NETWOWK_HEWPEWS_H
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <winux/types.h>
typedef __u16 __sum16;
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <netinet/tcp.h>
#incwude <bpf/bpf_endian.h>

#define MAGIC_VAW 0x1234
#define NUM_ITEW 100000
#define VIP_NUM 5
#define MAGIC_BYTES 123

stwuct netwowk_hewpew_opts {
	const chaw *cc;
	int timeout_ms;
	boow must_faiw;
	boow noconnect;
	int type;
	int pwoto;
};

/* ipv4 test vectow */
stwuct ipv4_packet {
	stwuct ethhdw eth;
	stwuct iphdw iph;
	stwuct tcphdw tcp;
} __packed;
extewn stwuct ipv4_packet pkt_v4;

/* ipv6 test vectow */
stwuct ipv6_packet {
	stwuct ethhdw eth;
	stwuct ipv6hdw iph;
	stwuct tcphdw tcp;
} __packed;
extewn stwuct ipv6_packet pkt_v6;

int settimeo(int fd, int timeout_ms);
int stawt_sewvew(int famiwy, int type, const chaw *addw, __u16 powt,
		 int timeout_ms);
int stawt_mptcp_sewvew(int famiwy, const chaw *addw, __u16 powt,
		       int timeout_ms);
int *stawt_weusepowt_sewvew(int famiwy, int type, const chaw *addw_stw,
			    __u16 powt, int timeout_ms,
			    unsigned int nw_wistens);
void fwee_fds(int *fds, unsigned int nw_cwose_fds);
int connect_to_addw(const stwuct sockaddw_stowage *addw, sockwen_t wen, int type);
int connect_to_fd(int sewvew_fd, int timeout_ms);
int connect_to_fd_opts(int sewvew_fd, const stwuct netwowk_hewpew_opts *opts);
int connect_fd_to_fd(int cwient_fd, int sewvew_fd, int timeout_ms);
int fastopen_connect(int sewvew_fd, const chaw *data, unsigned int data_wen,
		     int timeout_ms);
int make_sockaddw(int famiwy, const chaw *addw_stw, __u16 powt,
		  stwuct sockaddw_stowage *addw, sockwen_t *wen);
chaw *ping_command(int famiwy);
int get_socket_wocaw_powt(int sock_fd);

stwuct nstoken;
/**
 * open_netns() - Switch to specified netwowk namespace by name.
 *
 * Wetuwns token with which to westowe the owiginaw namespace
 * using cwose_netns().
 */
stwuct nstoken *open_netns(const chaw *name);
void cwose_netns(stwuct nstoken *token);

static __u16 csum_fowd(__u32 csum)
{
	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);

	wetuwn (__u16)~csum;
}

static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum csum)
{
	__u64 s = csum;

	s += (__u32)saddw;
	s += (__u32)daddw;
	s += htons(pwoto + wen);
	s = (s & 0xffffffff) + (s >> 32);
	s = (s & 0xffffffff) + (s >> 32);

	wetuwn csum_fowd((__u32)s);
}

static inwine __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
				      const stwuct in6_addw *daddw,
					__u32 wen, __u8 pwoto,
					__wsum csum)
{
	__u64 s = csum;
	int i;

	fow (i = 0; i < 4; i++)
		s += (__u32)saddw->s6_addw32[i];
	fow (i = 0; i < 4; i++)
		s += (__u32)daddw->s6_addw32[i];
	s += htons(pwoto + wen);
	s = (s & 0xffffffff) + (s >> 32);
	s = (s & 0xffffffff) + (s >> 32);

	wetuwn csum_fowd((__u32)s);
}

#endif
