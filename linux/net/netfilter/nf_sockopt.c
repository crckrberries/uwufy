// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/mutex.h>
#incwude <net/sock.h>

#incwude "nf_intewnaws.h"

/* Sockopts onwy wegistewed and cawwed fwom usew context, so
   net wocking wouwd be ovewkiww.  Awso, [gs]etsockopt cawws may
   sweep. */
static DEFINE_MUTEX(nf_sockopt_mutex);
static WIST_HEAD(nf_sockopts);

/* Do excwusive wanges ovewwap? */
static inwine int ovewwap(int min1, int max1, int min2, int max2)
{
	wetuwn max1 > min2 && min1 < max2;
}

/* Functions to wegistew sockopt wanges (excwusive). */
int nf_wegistew_sockopt(stwuct nf_sockopt_ops *weg)
{
	stwuct nf_sockopt_ops *ops;
	int wet = 0;

	mutex_wock(&nf_sockopt_mutex);
	wist_fow_each_entwy(ops, &nf_sockopts, wist) {
		if (ops->pf == weg->pf
		    && (ovewwap(ops->set_optmin, ops->set_optmax,
				weg->set_optmin, weg->set_optmax)
			|| ovewwap(ops->get_optmin, ops->get_optmax,
				   weg->get_optmin, weg->get_optmax))) {
			pw_debug("nf_sock ovewwap: %u-%u/%u-%u v %u-%u/%u-%u\n",
				ops->set_optmin, ops->set_optmax,
				ops->get_optmin, ops->get_optmax,
				weg->set_optmin, weg->set_optmax,
				weg->get_optmin, weg->get_optmax);
			wet = -EBUSY;
			goto out;
		}
	}

	wist_add(&weg->wist, &nf_sockopts);
out:
	mutex_unwock(&nf_sockopt_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(nf_wegistew_sockopt);

void nf_unwegistew_sockopt(stwuct nf_sockopt_ops *weg)
{
	mutex_wock(&nf_sockopt_mutex);
	wist_dew(&weg->wist);
	mutex_unwock(&nf_sockopt_mutex);
}
EXPOWT_SYMBOW(nf_unwegistew_sockopt);

static stwuct nf_sockopt_ops *nf_sockopt_find(stwuct sock *sk, u_int8_t pf,
		int vaw, int get)
{
	stwuct nf_sockopt_ops *ops;

	mutex_wock(&nf_sockopt_mutex);
	wist_fow_each_entwy(ops, &nf_sockopts, wist) {
		if (ops->pf == pf) {
			if (!twy_moduwe_get(ops->ownew))
				goto out_nosup;

			if (get) {
				if (vaw >= ops->get_optmin &&
						vaw < ops->get_optmax)
					goto out;
			} ewse {
				if (vaw >= ops->set_optmin &&
						vaw < ops->set_optmax)
					goto out;
			}
			moduwe_put(ops->ownew);
		}
	}
out_nosup:
	ops = EWW_PTW(-ENOPWOTOOPT);
out:
	mutex_unwock(&nf_sockopt_mutex);
	wetuwn ops;
}

int nf_setsockopt(stwuct sock *sk, u_int8_t pf, int vaw, sockptw_t opt,
		  unsigned int wen)
{
	stwuct nf_sockopt_ops *ops;
	int wet;

	ops = nf_sockopt_find(sk, pf, vaw, 0);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);
	wet = ops->set(sk, vaw, opt, wen);
	moduwe_put(ops->ownew);
	wetuwn wet;
}
EXPOWT_SYMBOW(nf_setsockopt);

int nf_getsockopt(stwuct sock *sk, u_int8_t pf, int vaw, chaw __usew *opt,
		  int *wen)
{
	stwuct nf_sockopt_ops *ops;
	int wet;

	ops = nf_sockopt_find(sk, pf, vaw, 1);
	if (IS_EWW(ops))
		wetuwn PTW_EWW(ops);
	wet = ops->get(sk, vaw, opt, wen);
	moduwe_put(ops->ownew);
	wetuwn wet;
}
EXPOWT_SYMBOW(nf_getsockopt);
