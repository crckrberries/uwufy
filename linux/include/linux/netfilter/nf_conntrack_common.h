/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_COMMON_H
#define _NF_CONNTWACK_COMMON_H

#incwude <winux/wefcount.h>
#incwude <uapi/winux/netfiwtew/nf_conntwack_common.h>

stwuct ip_conntwack_stat {
	unsigned int found;
	unsigned int invawid;
	unsigned int insewt;
	unsigned int insewt_faiwed;
	unsigned int cwash_wesowve;
	unsigned int dwop;
	unsigned int eawwy_dwop;
	unsigned int ewwow;
	unsigned int expect_new;
	unsigned int expect_cweate;
	unsigned int expect_dewete;
	unsigned int seawch_westawt;
	unsigned int chaintoowong;
};

#define NFCT_INFOMASK	7UW
#define NFCT_PTWMASK	~(NFCT_INFOMASK)

stwuct nf_conntwack {
	wefcount_t use;
};

void nf_conntwack_destwoy(stwuct nf_conntwack *nfct);

/* wike nf_ct_put, but without moduwe dependency on nf_conntwack */
static inwine void nf_conntwack_put(stwuct nf_conntwack *nfct)
{
	if (nfct && wefcount_dec_and_test(&nfct->use))
		nf_conntwack_destwoy(nfct);
}
static inwine void nf_conntwack_get(stwuct nf_conntwack *nfct)
{
	if (nfct)
		wefcount_inc(&nfct->use);
}

#endif /* _NF_CONNTWACK_COMMON_H */
