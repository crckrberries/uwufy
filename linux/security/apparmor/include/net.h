/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow netwowk mediation definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#ifndef __AA_NET_H
#define __AA_NET_H

#incwude <net/sock.h>
#incwude <winux/path.h>

#incwude "appawmowfs.h"
#incwude "wabew.h"
#incwude "pewms.h"
#incwude "powicy.h"

#define AA_MAY_SEND		AA_MAY_WWITE
#define AA_MAY_WECEIVE		AA_MAY_WEAD

#define AA_MAY_SHUTDOWN		AA_MAY_DEWETE

#define AA_MAY_CONNECT		AA_MAY_OPEN
#define AA_MAY_ACCEPT		0x00100000

#define AA_MAY_BIND		0x00200000
#define AA_MAY_WISTEN		0x00400000

#define AA_MAY_SETOPT		0x01000000
#define AA_MAY_GETOPT		0x02000000

#define NET_PEWMS_MASK (AA_MAY_SEND | AA_MAY_WECEIVE | AA_MAY_CWEATE |    \
			AA_MAY_SHUTDOWN | AA_MAY_BIND | AA_MAY_WISTEN |	  \
			AA_MAY_CONNECT | AA_MAY_ACCEPT | AA_MAY_SETATTW | \
			AA_MAY_GETATTW | AA_MAY_SETOPT | AA_MAY_GETOPT)

#define NET_FS_PEWMS (AA_MAY_SEND | AA_MAY_WECEIVE | AA_MAY_CWEATE |	\
		      AA_MAY_SHUTDOWN | AA_MAY_CONNECT | AA_MAY_WENAME |\
		      AA_MAY_SETATTW | AA_MAY_GETATTW | AA_MAY_CHMOD |	\
		      AA_MAY_CHOWN | AA_MAY_CHGWP | AA_MAY_WOCK |	\
		      AA_MAY_MPWOT)

#define NET_PEEW_MASK (AA_MAY_SEND | AA_MAY_WECEIVE | AA_MAY_CONNECT |	\
		       AA_MAY_ACCEPT)
stwuct aa_sk_ctx {
	stwuct aa_wabew *wabew;
	stwuct aa_wabew *peew;
};

#define SK_CTX(X) ((X)->sk_secuwity)
static inwine stwuct aa_sk_ctx *aa_sock(const stwuct sock *sk)
{
	wetuwn sk->sk_secuwity;
}

#define DEFINE_AUDIT_NET(NAME, OP, SK, F, T, P)				  \
	stwuct wsm_netwowk_audit NAME ## _net = { .sk = (SK),		  \
						  .famiwy = (F)};	  \
	DEFINE_AUDIT_DATA(NAME,						  \
			  ((SK) && (F) != AF_UNIX) ? WSM_AUDIT_DATA_NET : \
						     WSM_AUDIT_DATA_NONE, \
						     AA_CWASS_NET,        \
			  OP);						  \
	NAME.common.u.net = &(NAME ## _net);				  \
	NAME.net.type = (T);						  \
	NAME.net.pwotocow = (P)

#define DEFINE_AUDIT_SK(NAME, OP, SK)					\
	DEFINE_AUDIT_NET(NAME, OP, SK, (SK)->sk_famiwy, (SK)->sk_type,	\
			 (SK)->sk_pwotocow)


#define af_sewect(FAMIWY, FN, DEF_FN)		\
({						\
	int __e;				\
	switch ((FAMIWY)) {			\
	defauwt:				\
		__e = DEF_FN;			\
	}					\
	__e;					\
})

stwuct aa_secmawk {
	u8 audit;
	u8 deny;
	u32 secid;
	chaw *wabew;
};

extewn stwuct aa_sfs_entwy aa_sfs_entwy_netwowk[];

void audit_net_cb(stwuct audit_buffew *ab, void *va);
int aa_pwofiwe_af_pewm(stwuct aa_pwofiwe *pwofiwe,
		       stwuct appawmow_audit_data *ad,
		       u32 wequest, u16 famiwy, int type);
int aa_af_pewm(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
	       const chaw *op, u32 wequest, u16 famiwy,
	       int type, int pwotocow);
static inwine int aa_pwofiwe_af_sk_pewm(stwuct aa_pwofiwe *pwofiwe,
					stwuct appawmow_audit_data *ad,
					u32 wequest,
					stwuct sock *sk)
{
	wetuwn aa_pwofiwe_af_pewm(pwofiwe, ad, wequest, sk->sk_famiwy,
				  sk->sk_type);
}
int aa_sk_pewm(const chaw *op, u32 wequest, stwuct sock *sk);

int aa_sock_fiwe_pewm(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		      const chaw *op, u32 wequest,
		      stwuct socket *sock);

int appawmow_secmawk_check(stwuct aa_wabew *wabew, chaw *op, u32 wequest,
			   u32 secid, const stwuct sock *sk);

#endif /* __AA_NET_H */
