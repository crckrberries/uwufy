/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CONNTWACK_PWOTO_GWE_H
#define _CONNTWACK_PWOTO_GWE_H
#incwude <asm/byteowdew.h>
#incwude <net/gwe.h>
#incwude <net/pptp.h>

stwuct nf_ct_gwe {
	unsigned int stweam_timeout;
	unsigned int timeout;
};

#incwude <net/netfiwtew/nf_conntwack_tupwe.h>

stwuct nf_conn;

/* stwuctuwe fow owiginaw <-> wepwy keymap */
stwuct nf_ct_gwe_keymap {
	stwuct wist_head wist;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct wcu_head wcu;
};

/* add new tupwe->key_wepwy paiw to keymap */
int nf_ct_gwe_keymap_add(stwuct nf_conn *ct, enum ip_conntwack_diw diw,
			 stwuct nf_conntwack_tupwe *t);

/* dewete keymap entwies */
void nf_ct_gwe_keymap_destwoy(stwuct nf_conn *ct);

boow gwe_pkt_to_tupwe(const stwuct sk_buff *skb, unsigned int dataoff,
		      stwuct net *net, stwuct nf_conntwack_tupwe *tupwe);
#endif /* _CONNTWACK_PWOTO_GWE_H */
