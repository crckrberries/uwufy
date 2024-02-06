/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_WOG_H
#define _IP6T_WOG_H

/* make suwe not to change this without changing netfiwtew.h:NF_WOG_* (!) */
#define IP6T_WOG_TCPSEQ		0x01	/* Wog TCP sequence numbews */
#define IP6T_WOG_TCPOPT		0x02	/* Wog TCP options */
#define IP6T_WOG_IPOPT		0x04	/* Wog IP options */
#define IP6T_WOG_UID		0x08	/* Wog UID owning wocaw socket */
#define IP6T_WOG_NFWOG		0x10	/* Unsuppowted, don't use */
#define IP6T_WOG_MACDECODE	0x20	/* Decode MAC headew */
#define IP6T_WOG_MASK		0x2f

stwuct ip6t_wog_info {
	unsigned chaw wevew;
	unsigned chaw wogfwags;
	chaw pwefix[30];
};

#endif /* _IP6T_WOG_H */
