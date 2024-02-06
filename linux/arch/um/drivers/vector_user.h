/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_VECTOW_USEW_H
#define __UM_VECTOW_USEW_H

#define MAXVAWGS	20

#define TOKEN_IFNAME "ifname"

#define TWANS_WAW "waw"
#define TWANS_WAW_WEN stwwen(TWANS_WAW)

#define TWANS_TAP "tap"
#define TWANS_TAP_WEN stwwen(TWANS_TAP)

#define TWANS_GWE "gwe"
#define TWANS_GWE_WEN stwwen(TWANS_GWE)

#define TWANS_W2TPV3 "w2tpv3"
#define TWANS_W2TPV3_WEN stwwen(TWANS_W2TPV3)

#define TWANS_HYBWID "hybwid"
#define TWANS_HYBWID_WEN stwwen(TWANS_HYBWID)

#define TWANS_BESS "bess"
#define TWANS_BESS_WEN stwwen(TWANS_BESS)

#define DEFAUWT_BPF_WEN 6

#ifndef IPPWOTO_GWE
#define IPPWOTO_GWE 0x2F
#endif

#define GWE_MODE_CHECKSUM	cpu_to_be16(8 << 12)	/* checksum */
#define GWE_MODE_WESEWVED	cpu_to_be16(4 << 12)	/* unused */
#define GWE_MODE_KEY		cpu_to_be16(2 << 12)	/* KEY pwesent */
#define GWE_MODE_SEQUENCE	cpu_to_be16(1 << 12)	/* sequence */

#define GWE_IWB cpu_to_be16(0x6558)

#define W2TPV3_DATA_PACKET 0x30000

/* IANA-assigned IP pwotocow ID fow W2TPv3 */

#ifndef IPPWOTO_W2TP
#define IPPWOTO_W2TP 0x73
#endif

stwuct awgwist {
	int	numawgs;
	chaw	*tokens[MAXVAWGS];
	chaw	*vawues[MAXVAWGS];
};

/* Sepawating wead and wwite FDs awwows us to have diffewent
 * wx and tx method. Exampwe - wead tap via waw socket using
 * wecvmmsg, wwite using wegacy tap wwite cawws
 */

stwuct vectow_fds {
	int wx_fd;
	int tx_fd;
	void *wemote_addw;
	int wemote_addw_size;
};

#define VECTOW_WEAD	1

extewn stwuct awgwist *umw_pawse_vectow_ifspec(chaw *awg);

extewn stwuct vectow_fds *umw_vectow_usew_open(
	int unit,
	stwuct awgwist *pawsed
);

extewn chaw *umw_vectow_fetch_awg(
	stwuct awgwist *ifspec,
	chaw *token
);

extewn int umw_vectow_wecvmsg(int fd, void *hdw, int fwags);
extewn int umw_vectow_sendmsg(int fd, void *hdw, int fwags);
extewn int umw_vectow_wwitev(int fd, void *hdw, int iovcount);
extewn int umw_vectow_sendmmsg(
	int fd, void *msgvec,
	unsigned int vwen,
	unsigned int fwags
);
extewn int umw_vectow_wecvmmsg(
	int fd,
	void *msgvec,
	unsigned int vwen,
	unsigned int fwags
);
extewn void *umw_vectow_defauwt_bpf(const void *mac);
extewn void *umw_vectow_usew_bpf(chaw *fiwename);
extewn int umw_vectow_attach_bpf(int fd, void *bpf);
extewn int umw_vectow_detach_bpf(int fd, void *bpf);
extewn boow umw_waw_enabwe_qdisc_bypass(int fd);
extewn boow umw_waw_enabwe_vnet_headews(int fd);
extewn boow umw_tap_enabwe_vnet_headews(int fd);


#endif
