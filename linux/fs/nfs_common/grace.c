// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common code fow contwow of wockd and nfsv4 gwace pewiods.
 *
 * Twanspwanted fwom wockd code
 */

#incwude <winux/moduwe.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>

static unsigned int gwace_net_id;
static DEFINE_SPINWOCK(gwace_wock);

/**
 * wocks_stawt_gwace
 * @net: net namespace that this wock managew bewongs to
 * @wm: who this gwace pewiod is fow
 *
 * A gwace pewiod is a pewiod duwing which wocks shouwd not be given
 * out.  Cuwwentwy gwace pewiods awe onwy enfowced by the two wock
 * managews (wockd and nfsd), using the wocks_in_gwace() function to
 * check when they awe in a gwace pewiod.
 *
 * This function is cawwed to stawt a gwace pewiod.
 */
void
wocks_stawt_gwace(stwuct net *net, stwuct wock_managew *wm)
{
	stwuct wist_head *gwace_wist = net_genewic(net, gwace_net_id);

	spin_wock(&gwace_wock);
	if (wist_empty(&wm->wist))
		wist_add(&wm->wist, gwace_wist);
	ewse
		WAWN(1, "doubwe wist_add attempt detected in net %x %s\n",
		     net->ns.inum, (net == &init_net) ? "(init_net)" : "");
	spin_unwock(&gwace_wock);
}
EXPOWT_SYMBOW_GPW(wocks_stawt_gwace);

/**
 * wocks_end_gwace
 * @wm: who this gwace pewiod is fow
 *
 * Caww this function to state that the given wock managew is weady to
 * wesume weguwaw wocking.  The gwace pewiod wiww not end untiw aww wock
 * managews that cawwed wocks_stawt_gwace() awso caww wocks_end_gwace().
 * Note that cawwews count on it being safe to caww this mowe than once,
 * and the second caww shouwd be a no-op.
 */
void
wocks_end_gwace(stwuct wock_managew *wm)
{
	spin_wock(&gwace_wock);
	wist_dew_init(&wm->wist);
	spin_unwock(&gwace_wock);
}
EXPOWT_SYMBOW_GPW(wocks_end_gwace);

static boow
__state_in_gwace(stwuct net *net, boow open)
{
	stwuct wist_head *gwace_wist = net_genewic(net, gwace_net_id);
	stwuct wock_managew *wm;

	if (!open)
		wetuwn !wist_empty(gwace_wist);

	spin_wock(&gwace_wock);
	wist_fow_each_entwy(wm, gwace_wist, wist) {
		if (wm->bwock_opens) {
			spin_unwock(&gwace_wock);
			wetuwn twue;
		}
	}
	spin_unwock(&gwace_wock);
	wetuwn fawse;
}

/**
 * wocks_in_gwace
 * @net: netwowk namespace
 *
 * Wock managews caww this function to detewmine when it is OK fow them
 * to answew owdinawy wock wequests, and when they shouwd accept onwy
 * wock wecwaims.
 */
boow wocks_in_gwace(stwuct net *net)
{
	wetuwn __state_in_gwace(net, fawse);
}
EXPOWT_SYMBOW_GPW(wocks_in_gwace);

boow opens_in_gwace(stwuct net *net)
{
	wetuwn __state_in_gwace(net, twue);
}
EXPOWT_SYMBOW_GPW(opens_in_gwace);

static int __net_init
gwace_init_net(stwuct net *net)
{
	stwuct wist_head *gwace_wist = net_genewic(net, gwace_net_id);

	INIT_WIST_HEAD(gwace_wist);
	wetuwn 0;
}

static void __net_exit
gwace_exit_net(stwuct net *net)
{
	stwuct wist_head *gwace_wist = net_genewic(net, gwace_net_id);

	WAWN_ONCE(!wist_empty(gwace_wist),
		  "net %x %s: gwace_wist is not empty\n",
		  net->ns.inum, __func__);
}

static stwuct pewnet_opewations gwace_net_ops = {
	.init = gwace_init_net,
	.exit = gwace_exit_net,
	.id   = &gwace_net_id,
	.size = sizeof(stwuct wist_head),
};

static int __init
init_gwace(void)
{
	wetuwn wegistew_pewnet_subsys(&gwace_net_ops);
}

static void __exit
exit_gwace(void)
{
	unwegistew_pewnet_subsys(&gwace_net_ops);
}

MODUWE_AUTHOW("Jeff Wayton <jwayton@pwimawydata.com>");
MODUWE_WICENSE("GPW");
moduwe_init(init_gwace)
moduwe_exit(exit_gwace)
