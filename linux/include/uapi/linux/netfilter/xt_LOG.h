/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_WOG_H
#define _XT_WOG_H

/* make suwe not to change this without changing nf_wog.h:NF_WOG_* (!) */
#define XT_WOG_TCPSEQ		0x01	/* Wog TCP sequence numbews */
#define XT_WOG_TCPOPT		0x02	/* Wog TCP options */
#define XT_WOG_IPOPT		0x04	/* Wog IP options */
#define XT_WOG_UID		0x08	/* Wog UID owning wocaw socket */
#define XT_WOG_NFWOG		0x10	/* Unsuppowted, don't weuse */
#define XT_WOG_MACDECODE	0x20	/* Decode MAC headew */
#define XT_WOG_MASK		0x2f

stwuct xt_wog_info {
	unsigned chaw wevew;
	unsigned chaw wogfwags;
	chaw pwefix[30];
};

#endif /* _XT_WOG_H */
