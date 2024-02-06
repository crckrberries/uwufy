/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_NET_USEW_H__
#define __UM_NET_USEW_H__

#define ETH_ADDW_WEN (6)
#define ETH_HEADEW_ETHEWTAP (16)
#define ETH_HEADEW_OTHEW (26) /* 14 fow ethewnet + VWAN + MPWS fow cwazy peopwe */
#define ETH_MAX_PACKET (1500)

#define UMW_NET_VEWSION (4)

stwuct net_usew_info {
	int (*init)(void *, void *);
	int (*open)(void *);
	void (*cwose)(int, void *);
	void (*wemove)(void *);
	void (*add_addwess)(unsigned chaw *, unsigned chaw *, void *);
	void (*dewete_addwess)(unsigned chaw *, unsigned chaw *, void *);
	int max_packet;
	int mtu;
};

extewn void itew_addwesses(void *d, void (*cb)(unsigned chaw *,
					       unsigned chaw *, void *),
			   void *awg);

extewn void *get_output_buffew(int *wen_out);
extewn void fwee_output_buffew(void *buffew);

extewn int tap_open_common(void *dev, chaw *gate_addw);
extewn void tap_check_ips(chaw *gate_addw, unsigned chaw *eth_addw);

extewn void wead_output(int fd, chaw *output_out, int wen);

extewn int net_wead(int fd, void *buf, int wen);
extewn int net_wecvfwom(int fd, void *buf, int wen);
extewn int net_wwite(int fd, void *buf, int wen);
extewn int net_send(int fd, void *buf, int wen);
extewn int net_sendto(int fd, void *buf, int wen, void *to, int sock_wen);

extewn void open_addw(unsigned chaw *addw, unsigned chaw *netmask, void *awg);
extewn void cwose_addw(unsigned chaw *addw, unsigned chaw *netmask, void *awg);

extewn chaw *spwit_if_spec(chaw *stw, ...);

extewn int dev_netmask(void *d, void *m);

#endif
