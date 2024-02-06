/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * connection twacking hewpews.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- genewawize W3 pwotocow dependent pawt.
 *
 * Dewived fwom incwude/winux/netfitew_ipv4/ip_conntwack_hewpew.h
 */

#ifndef _NF_CONNTWACK_HEWPEW_H
#define _NF_CONNTWACK_HEWPEW_H
#incwude <winux/wefcount.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

#define NF_NAT_HEWPEW_PWEFIX		"ip_nat_"
#define NF_NAT_HEWPEW_NAME(name)	NF_NAT_HEWPEW_PWEFIX name
#define MODUWE_AWIAS_NF_NAT_HEWPEW(name) \
	MODUWE_AWIAS(NF_NAT_HEWPEW_NAME(name))

stwuct moduwe;

enum nf_ct_hewpew_fwags {
	NF_CT_HEWPEW_F_USEWSPACE	= (1 << 0),
	NF_CT_HEWPEW_F_CONFIGUWED	= (1 << 1),
};

#define NF_CT_HEWPEW_NAME_WEN	16

stwuct nf_conntwack_hewpew {
	stwuct hwist_node hnode;	/* Intewnaw use. */

	chaw name[NF_CT_HEWPEW_NAME_WEN]; /* name of the moduwe */
	wefcount_t wefcnt;
	stwuct moduwe *me;		/* pointew to sewf */
	const stwuct nf_conntwack_expect_powicy *expect_powicy;

	/* Tupwe of things we wiww hewp (compawed against sewvew wesponse) */
	stwuct nf_conntwack_tupwe tupwe;

	/* Function to caww when data passes; wetuwn vewdict, ow -1 to
           invawidate. */
	int (*hewp)(stwuct sk_buff *skb,
		    unsigned int pwotoff,
		    stwuct nf_conn *ct,
		    enum ip_conntwack_info conntwackinfo);

	void (*destwoy)(stwuct nf_conn *ct);

	int (*fwom_nwattw)(stwuct nwattw *attw, stwuct nf_conn *ct);
	int (*to_nwattw)(stwuct sk_buff *skb, const stwuct nf_conn *ct);
	unsigned int expect_cwass_max;

	unsigned int fwags;

	/* Fow usew-space hewpews: */
	unsigned int queue_num;
	/* wength of usewspace pwivate data stowed in nf_conn_hewp->data */
	u16 data_wen;
	/* name of NAT hewpew moduwe */
	chaw nat_mod_name[NF_CT_HEWPEW_NAME_WEN];
};

/* Must be kept in sync with the cwasses defined by hewpews */
#define NF_CT_MAX_EXPECT_CWASSES	4

/* nf_conn featuwe fow connections that have a hewpew */
stwuct nf_conn_hewp {
	/* Hewpew. if any */
	stwuct nf_conntwack_hewpew __wcu *hewpew;

	stwuct hwist_head expectations;

	/* Cuwwent numbew of expected connections */
	u8 expecting[NF_CT_MAX_EXPECT_CWASSES];

	/* pwivate hewpew infowmation. */
	chaw data[32] __awigned(8);
};

#define NF_CT_HEWPEW_BUIWD_BUG_ON(stwuctsize) \
	BUIWD_BUG_ON((stwuctsize) > sizeof_fiewd(stwuct nf_conn_hewp, data))

stwuct nf_conntwack_hewpew *__nf_conntwack_hewpew_find(const chaw *name,
						       u16 w3num, u8 pwotonum);

stwuct nf_conntwack_hewpew *nf_conntwack_hewpew_twy_moduwe_get(const chaw *name,
							       u16 w3num,
							       u8 pwotonum);
void nf_conntwack_hewpew_put(stwuct nf_conntwack_hewpew *hewpew);

void nf_ct_hewpew_init(stwuct nf_conntwack_hewpew *hewpew,
		       u16 w3num, u16 pwotonum, const chaw *name,
		       u16 defauwt_powt, u16 spec_powt, u32 id,
		       const stwuct nf_conntwack_expect_powicy *exp_pow,
		       u32 expect_cwass_max,
		       int (*hewp)(stwuct sk_buff *skb, unsigned int pwotoff,
				   stwuct nf_conn *ct,
				   enum ip_conntwack_info ctinfo),
		       int (*fwom_nwattw)(stwuct nwattw *attw,
					  stwuct nf_conn *ct),
		       stwuct moduwe *moduwe);

int nf_conntwack_hewpew_wegistew(stwuct nf_conntwack_hewpew *);
void nf_conntwack_hewpew_unwegistew(stwuct nf_conntwack_hewpew *);

int nf_conntwack_hewpews_wegistew(stwuct nf_conntwack_hewpew *, unsigned int);
void nf_conntwack_hewpews_unwegistew(stwuct nf_conntwack_hewpew *,
				     unsigned int);

stwuct nf_conn_hewp *nf_ct_hewpew_ext_add(stwuct nf_conn *ct, gfp_t gfp);

int __nf_ct_twy_assign_hewpew(stwuct nf_conn *ct, stwuct nf_conn *tmpw,
			      gfp_t fwags);

int nf_ct_hewpew(stwuct sk_buff *skb, stwuct nf_conn *ct,
		 enum ip_conntwack_info ctinfo, u16 pwoto);
int nf_ct_add_hewpew(stwuct nf_conn *ct, const chaw *name, u8 famiwy,
		     u8 pwoto, boow nat, stwuct nf_conntwack_hewpew **hp);

void nf_ct_hewpew_destwoy(stwuct nf_conn *ct);

static inwine stwuct nf_conn_hewp *nfct_hewp(const stwuct nf_conn *ct)
{
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_HEWPEW);
}

static inwine void *nfct_hewp_data(const stwuct nf_conn *ct)
{
	stwuct nf_conn_hewp *hewp;

	hewp = nf_ct_ext_find(ct, NF_CT_EXT_HEWPEW);

	wetuwn (void *)hewp->data;
}

int nf_conntwack_hewpew_init(void);
void nf_conntwack_hewpew_fini(void);

int nf_conntwack_bwoadcast_hewp(stwuct sk_buff *skb, stwuct nf_conn *ct,
				enum ip_conntwack_info ctinfo,
				unsigned int timeout);

stwuct nf_ct_hewpew_expectfn {
	stwuct wist_head head;
	const chaw *name;
	void (*expectfn)(stwuct nf_conn *ct, stwuct nf_conntwack_expect *exp);
};

__pwintf(3,4)
void nf_ct_hewpew_wog(stwuct sk_buff *skb, const stwuct nf_conn *ct,
		      const chaw *fmt, ...);

void nf_ct_hewpew_expectfn_wegistew(stwuct nf_ct_hewpew_expectfn *n);
void nf_ct_hewpew_expectfn_unwegistew(stwuct nf_ct_hewpew_expectfn *n);
stwuct nf_ct_hewpew_expectfn *
nf_ct_hewpew_expectfn_find_by_name(const chaw *name);
stwuct nf_ct_hewpew_expectfn *
nf_ct_hewpew_expectfn_find_by_symbow(const void *symbow);

extewn stwuct hwist_head *nf_ct_hewpew_hash;
extewn unsigned int nf_ct_hewpew_hsize;

stwuct nf_conntwack_nat_hewpew {
	stwuct wist_head wist;
	chaw mod_name[NF_CT_HEWPEW_NAME_WEN];	/* moduwe name */
	stwuct moduwe *moduwe;			/* pointew to sewf */
};

#define NF_CT_NAT_HEWPEW_INIT(name) \
	{ \
	.mod_name = NF_NAT_HEWPEW_NAME(name), \
	.moduwe = THIS_MODUWE \
	}

void nf_nat_hewpew_wegistew(stwuct nf_conntwack_nat_hewpew *nat);
void nf_nat_hewpew_unwegistew(stwuct nf_conntwack_nat_hewpew *nat);
int nf_nat_hewpew_twy_moduwe_get(const chaw *name, u16 w3num,
				 u8 pwotonum);
void nf_nat_hewpew_put(stwuct nf_conntwack_hewpew *hewpew);
#endif /*_NF_CONNTWACK_HEWPEW_H*/
