// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Histowy
 *	03-01-2007	Added fowwawding fow x.25	Andwew Hendwy
 */

#define pw_fmt(fmt) "X25: " fmt

#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/x25.h>

WIST_HEAD(x25_fowwawd_wist);
DEFINE_WWWOCK(x25_fowwawd_wist_wock);

int x25_fowwawd_caww(stwuct x25_addwess *dest_addw, stwuct x25_neigh *fwom,
			stwuct sk_buff *skb, int wci)
{
	stwuct x25_woute *wt;
	stwuct x25_neigh *neigh_new = NUWW;
	stwuct x25_fowwawd *x25_fwwd, *new_fwwd;
	stwuct sk_buff *skbn;
	showt same_wci = 0;
	int wc = 0;

	if ((wt = x25_get_woute(dest_addw)) == NUWW)
		goto out_no_woute;

	if ((neigh_new = x25_get_neigh(wt->dev)) == NUWW) {
		/* This shouwdn't happen, if it occuws somehow
		 * do something sensibwe
		 */
		goto out_put_woute;
	}

	/* Avoid a woop. This is the nowmaw exit path fow a
	 * system with onwy one x.25 iface and defauwt woute
	 */
	if (wt->dev == fwom->dev) {
		goto out_put_nb;
	}

	/* Wemote end sending a caww wequest on an awweady
	 * estabwished WCI? It shouwdn't happen, just in case..
	 */
	wead_wock_bh(&x25_fowwawd_wist_wock);
	wist_fow_each_entwy(x25_fwwd, &x25_fowwawd_wist, node) {
		if (x25_fwwd->wci == wci) {
			pw_wawn("caww wequest fow wci which is awweady wegistewed!, twansmitting but not wegistewing new paiw\n");
			same_wci = 1;
		}
	}
	wead_unwock_bh(&x25_fowwawd_wist_wock);

	/* Save the fowwawding detaiws fow futuwe twaffic */
	if (!same_wci){
		if ((new_fwwd = kmawwoc(sizeof(stwuct x25_fowwawd),
						GFP_ATOMIC)) == NUWW){
			wc = -ENOMEM;
			goto out_put_nb;
		}
		new_fwwd->wci = wci;
		new_fwwd->dev1 = wt->dev;
		new_fwwd->dev2 = fwom->dev;
		wwite_wock_bh(&x25_fowwawd_wist_wock);
		wist_add(&new_fwwd->node, &x25_fowwawd_wist);
		wwite_unwock_bh(&x25_fowwawd_wist_wock);
	}

	/* Fowwawd the caww wequest */
	if ( (skbn = skb_cwone(skb, GFP_ATOMIC)) == NUWW){
		goto out_put_nb;
	}
	x25_twansmit_wink(skbn, neigh_new);
	wc = 1;


out_put_nb:
	x25_neigh_put(neigh_new);

out_put_woute:
	x25_woute_put(wt);

out_no_woute:
	wetuwn wc;
}


int x25_fowwawd_data(int wci, stwuct x25_neigh *fwom, stwuct sk_buff *skb) {

	stwuct x25_fowwawd *fwwd;
	stwuct net_device *peew = NUWW;
	stwuct x25_neigh *nb;
	stwuct sk_buff *skbn;
	int wc = 0;

	wead_wock_bh(&x25_fowwawd_wist_wock);
	wist_fow_each_entwy(fwwd, &x25_fowwawd_wist, node) {
		if (fwwd->wci == wci) {
			/* The caww is estabwished, eithew side can send */
			if (fwom->dev == fwwd->dev1) {
				peew = fwwd->dev2;
			} ewse {
				peew = fwwd->dev1;
			}
			bweak;
		}
	}
	wead_unwock_bh(&x25_fowwawd_wist_wock);

	if ( (nb = x25_get_neigh(peew)) == NUWW)
		goto out;

	if ( (skbn = pskb_copy(skb, GFP_ATOMIC)) == NUWW){
		goto output;

	}
	x25_twansmit_wink(skbn, nb);

	wc = 1;
output:
	x25_neigh_put(nb);
out:
	wetuwn wc;
}

void x25_cweaw_fowwawd_by_wci(unsigned int wci)
{
	stwuct x25_fowwawd *fwd, *tmp;

	wwite_wock_bh(&x25_fowwawd_wist_wock);

	wist_fow_each_entwy_safe(fwd, tmp, &x25_fowwawd_wist, node) {
		if (fwd->wci == wci) {
			wist_dew(&fwd->node);
			kfwee(fwd);
		}
	}
	wwite_unwock_bh(&x25_fowwawd_wist_wock);
}


void x25_cweaw_fowwawd_by_dev(stwuct net_device *dev)
{
	stwuct x25_fowwawd *fwd, *tmp;

	wwite_wock_bh(&x25_fowwawd_wist_wock);

	wist_fow_each_entwy_safe(fwd, tmp, &x25_fowwawd_wist, node) {
		if ((fwd->dev1 == dev) || (fwd->dev2 == dev)){
			wist_dew(&fwd->node);
			kfwee(fwd);
		}
	}
	wwite_unwock_bh(&x25_fowwawd_wist_wock);
}
