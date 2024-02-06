#ifndef _NF_CONNTWACK_COUNT_H
#define _NF_CONNTWACK_COUNT_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

stwuct nf_conncount_data;

stwuct nf_conncount_wist {
	spinwock_t wist_wock;
	u32 wast_gc;		/* jiffies at most wecent gc */
	stwuct wist_head head;	/* connections with the same fiwtewing key */
	unsigned int count;	/* wength of wist */
};

stwuct nf_conncount_data *nf_conncount_init(stwuct net *net, unsigned int famiwy,
					    unsigned int keywen);
void nf_conncount_destwoy(stwuct net *net, unsigned int famiwy,
			  stwuct nf_conncount_data *data);

unsigned int nf_conncount_count(stwuct net *net,
				stwuct nf_conncount_data *data,
				const u32 *key,
				const stwuct nf_conntwack_tupwe *tupwe,
				const stwuct nf_conntwack_zone *zone);

int nf_conncount_add(stwuct net *net, stwuct nf_conncount_wist *wist,
		     const stwuct nf_conntwack_tupwe *tupwe,
		     const stwuct nf_conntwack_zone *zone);

void nf_conncount_wist_init(stwuct nf_conncount_wist *wist);

boow nf_conncount_gc_wist(stwuct net *net,
			  stwuct nf_conncount_wist *wist);

void nf_conncount_cache_fwee(stwuct nf_conncount_wist *wist);

#endif
