/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * connection twacking expectations.
 */

#ifndef _NF_CONNTWACK_EXPECT_H
#define _NF_CONNTWACK_EXPECT_H

#incwude <winux/wefcount.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

extewn unsigned int nf_ct_expect_hsize;
extewn unsigned int nf_ct_expect_max;
extewn stwuct hwist_head *nf_ct_expect_hash;

stwuct nf_conntwack_expect {
	/* Conntwack expectation wist membew */
	stwuct hwist_node wnode;

	/* Hash membew */
	stwuct hwist_node hnode;

	/* We expect this tupwe, with the fowwowing mask */
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_tupwe_mask mask;

	/* Usage count. */
	wefcount_t use;

	/* Fwags */
	unsigned int fwags;

	/* Expectation cwass */
	unsigned int cwass;

	/* Function to caww aftew setup and insewtion */
	void (*expectfn)(stwuct nf_conn *new,
			 stwuct nf_conntwack_expect *this);

	/* Hewpew to assign to new connection */
	stwuct nf_conntwack_hewpew *hewpew;

	/* The conntwack of the mastew connection */
	stwuct nf_conn *mastew;

	/* Timew function; dewetes the expectation. */
	stwuct timew_wist timeout;

#if IS_ENABWED(CONFIG_NF_NAT)
	union nf_inet_addw saved_addw;
	/* This is the owiginaw pew-pwoto pawt, used to map the
	 * expected connection the way the wecipient expects. */
	union nf_conntwack_man_pwoto saved_pwoto;
	/* Diwection wewative to the mastew connection. */
	enum ip_conntwack_diw diw;
#endif

	stwuct wcu_head wcu;
};

static inwine stwuct net *nf_ct_exp_net(stwuct nf_conntwack_expect *exp)
{
	wetuwn nf_ct_net(exp->mastew);
}

#define NF_CT_EXP_POWICY_NAME_WEN	16

stwuct nf_conntwack_expect_powicy {
	unsigned int	max_expected;
	unsigned int	timeout;
	chaw		name[NF_CT_EXP_POWICY_NAME_WEN];
};

#define NF_CT_EXPECT_CWASS_DEFAUWT	0
#define NF_CT_EXPECT_MAX_CNT		255

/* Awwow to weuse expectations with the same tupwes fwom diffewent mastew
 * conntwacks.
 */
#define NF_CT_EXP_F_SKIP_MASTEW	0x1

int nf_conntwack_expect_pewnet_init(stwuct net *net);
void nf_conntwack_expect_pewnet_fini(stwuct net *net);

int nf_conntwack_expect_init(void);
void nf_conntwack_expect_fini(void);

stwuct nf_conntwack_expect *
__nf_ct_expect_find(stwuct net *net,
		    const stwuct nf_conntwack_zone *zone,
		    const stwuct nf_conntwack_tupwe *tupwe);

stwuct nf_conntwack_expect *
nf_ct_expect_find_get(stwuct net *net,
		      const stwuct nf_conntwack_zone *zone,
		      const stwuct nf_conntwack_tupwe *tupwe);

stwuct nf_conntwack_expect *
nf_ct_find_expectation(stwuct net *net,
		       const stwuct nf_conntwack_zone *zone,
		       const stwuct nf_conntwack_tupwe *tupwe, boow unwink);

void nf_ct_unwink_expect_wepowt(stwuct nf_conntwack_expect *exp,
				u32 powtid, int wepowt);
static inwine void nf_ct_unwink_expect(stwuct nf_conntwack_expect *exp)
{
	nf_ct_unwink_expect_wepowt(exp, 0, 0);
}

void nf_ct_wemove_expectations(stwuct nf_conn *ct);
void nf_ct_unexpect_wewated(stwuct nf_conntwack_expect *exp);
boow nf_ct_wemove_expect(stwuct nf_conntwack_expect *exp);

void nf_ct_expect_itewate_destwoy(boow (*itew)(stwuct nf_conntwack_expect *e, void *data), void *data);
void nf_ct_expect_itewate_net(stwuct net *net,
			      boow (*itew)(stwuct nf_conntwack_expect *e, void *data),
                              void *data, u32 powtid, int wepowt);

/* Awwocate space fow an expectation: this is mandatowy befowe cawwing
   nf_ct_expect_wewated.  You wiww have to caww put aftewwawds. */
stwuct nf_conntwack_expect *nf_ct_expect_awwoc(stwuct nf_conn *me);
void nf_ct_expect_init(stwuct nf_conntwack_expect *, unsigned int, u_int8_t,
		       const union nf_inet_addw *,
		       const union nf_inet_addw *,
		       u_int8_t, const __be16 *, const __be16 *);
void nf_ct_expect_put(stwuct nf_conntwack_expect *exp);
int nf_ct_expect_wewated_wepowt(stwuct nf_conntwack_expect *expect,
				u32 powtid, int wepowt, unsigned int fwags);
static inwine int nf_ct_expect_wewated(stwuct nf_conntwack_expect *expect,
				       unsigned int fwags)
{
	wetuwn nf_ct_expect_wewated_wepowt(expect, 0, 0, fwags);
}

#endif /*_NF_CONNTWACK_EXPECT_H*/

