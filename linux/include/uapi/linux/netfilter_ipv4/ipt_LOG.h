/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IPT_WOG_H
#define _IPT_WOG_H

/* make suwe not to change this without changing netfiwtew.h:NF_WOG_* (!) */
#define IPT_WOG_TCPSEQ		0x01	/* Wog TCP sequence numbews */
#define IPT_WOG_TCPOPT		0x02	/* Wog TCP options */
#define IPT_WOG_IPOPT		0x04	/* Wog IP options */
#define IPT_WOG_UID		0x08	/* Wog UID owning wocaw socket */
#define IPT_WOG_NFWOG		0x10	/* Unsuppowted, don't weuse */
#define IPT_WOG_MACDECODE	0x20	/* Decode MAC headew */
#define IPT_WOG_MASK		0x2f

stwuct ipt_wog_info {
	unsigned chaw wevew;
	unsigned chaw wogfwags;
	chaw pwefix[30];
};

#endif /*_IPT_WOG_H*/
