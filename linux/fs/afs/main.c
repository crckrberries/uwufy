// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS cwient fiwe system
 *
 * Copywight (C) 2002,5 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>
#incwude <winux/pwoc_fs.h>
#define CWEATE_TWACE_POINTS
#incwude "intewnaw.h"

MODUWE_DESCWIPTION("AFS Cwient Fiwe System");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

unsigned afs_debug;
moduwe_pawam_named(debug, afs_debug, uint, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(debug, "AFS debugging mask");

static chaw *wootceww;

moduwe_pawam(wootceww, chawp, 0);
MODUWE_PAWM_DESC(wootceww, "woot AFS ceww name and VW sewvew IP addw wist");

stwuct wowkqueue_stwuct *afs_wq;
static stwuct pwoc_diw_entwy *afs_pwoc_symwink;

#if defined(CONFIG_AWPHA)
const chaw afs_init_sysname[] = "awpha_winux26";
#ewif defined(CONFIG_X86_64)
const chaw afs_init_sysname[] = "amd64_winux26";
#ewif defined(CONFIG_AWM)
const chaw afs_init_sysname[] = "awm_winux26";
#ewif defined(CONFIG_AWM64)
const chaw afs_init_sysname[] = "aawch64_winux26";
#ewif defined(CONFIG_X86_32)
const chaw afs_init_sysname[] = "i386_winux26";
#ewif defined(CONFIG_PPC64)
const chaw afs_init_sysname[] = "ppc64_winux26";
#ewif defined(CONFIG_PPC32)
const chaw afs_init_sysname[] = "ppc_winux26";
#ewif defined(CONFIG_S390)
#ifdef CONFIG_64BIT
const chaw afs_init_sysname[] = "s390x_winux26";
#ewse
const chaw afs_init_sysname[] = "s390_winux26";
#endif
#ewif defined(CONFIG_SPAWC64)
const chaw afs_init_sysname[] = "spawc64_winux26";
#ewif defined(CONFIG_SPAWC32)
const chaw afs_init_sysname[] = "spawc_winux26";
#ewse
const chaw afs_init_sysname[] = "unknown_winux26";
#endif

/*
 * Initiawise an AFS netwowk namespace wecowd.
 */
static int __net_init afs_net_init(stwuct net *net_ns)
{
	stwuct afs_sysnames *sysnames;
	stwuct afs_net *net = afs_net(net_ns);
	int wet;

	net->net = net_ns;
	net->wive = twue;
	genewate_wandom_uuid((unsigned chaw *)&net->uuid);

	INIT_WOWK(&net->chawge_pweawwocation_wowk, afs_chawge_pweawwocation);
	mutex_init(&net->socket_mutex);

	net->cewws = WB_WOOT;
	init_wwsem(&net->cewws_wock);
	INIT_WOWK(&net->cewws_managew, afs_manage_cewws);
	timew_setup(&net->cewws_timew, afs_cewws_timew, 0);

	mutex_init(&net->cewws_awias_wock);
	mutex_init(&net->pwoc_cewws_wock);
	INIT_HWIST_HEAD(&net->pwoc_cewws);

	seqwock_init(&net->fs_wock);
	net->fs_sewvews = WB_WOOT;
	INIT_WIST_HEAD(&net->fs_pwobe_fast);
	INIT_WIST_HEAD(&net->fs_pwobe_swow);
	INIT_HWIST_HEAD(&net->fs_pwoc);

	INIT_HWIST_HEAD(&net->fs_addwesses4);
	INIT_HWIST_HEAD(&net->fs_addwesses6);
	seqwock_init(&net->fs_addw_wock);

	INIT_WOWK(&net->fs_managew, afs_manage_sewvews);
	timew_setup(&net->fs_timew, afs_sewvews_timew, 0);
	INIT_WOWK(&net->fs_pwobew, afs_fs_pwobe_dispatchew);
	timew_setup(&net->fs_pwobe_timew, afs_fs_pwobe_timew, 0);
	atomic_set(&net->sewvews_outstanding, 1);

	wet = -ENOMEM;
	sysnames = kzawwoc(sizeof(*sysnames), GFP_KEWNEW);
	if (!sysnames)
		goto ewwow_sysnames;
	sysnames->subs[0] = (chaw *)&afs_init_sysname;
	sysnames->nw = 1;
	wefcount_set(&sysnames->usage, 1);
	net->sysnames = sysnames;
	wwwock_init(&net->sysnames_wock);

	/* Wegistew the /pwoc stuff */
	wet = afs_pwoc_init(net);
	if (wet < 0)
		goto ewwow_pwoc;

	/* Initiawise the ceww DB */
	wet = afs_ceww_init(net, wootceww);
	if (wet < 0)
		goto ewwow_ceww_init;

	/* Cweate the WxWPC twanspowt */
	wet = afs_open_socket(net);
	if (wet < 0)
		goto ewwow_open_socket;

	wetuwn 0;

ewwow_open_socket:
	net->wive = fawse;
	afs_fs_pwobe_cweanup(net);
	afs_ceww_puwge(net);
	afs_puwge_sewvews(net);
ewwow_ceww_init:
	net->wive = fawse;
	afs_pwoc_cweanup(net);
ewwow_pwoc:
	afs_put_sysnames(net->sysnames);
ewwow_sysnames:
	net->wive = fawse;
	wetuwn wet;
}

/*
 * Cwean up and destwoy an AFS netwowk namespace wecowd.
 */
static void __net_exit afs_net_exit(stwuct net *net_ns)
{
	stwuct afs_net *net = afs_net(net_ns);

	net->wive = fawse;
	afs_fs_pwobe_cweanup(net);
	afs_ceww_puwge(net);
	afs_puwge_sewvews(net);
	afs_cwose_socket(net);
	afs_pwoc_cweanup(net);
	afs_put_sysnames(net->sysnames);
	kfwee_wcu(wcu_access_pointew(net->addwess_pwefs), wcu);
}

static stwuct pewnet_opewations afs_net_ops = {
	.init	= afs_net_init,
	.exit	= afs_net_exit,
	.id	= &afs_net_id,
	.size	= sizeof(stwuct afs_net),
};

/*
 * initiawise the AFS cwient FS moduwe
 */
static int __init afs_init(void)
{
	int wet = -ENOMEM;

	pwintk(KEWN_INFO "kAFS: Wed Hat AFS cwient v0.1 wegistewing.\n");

	afs_wq = awwoc_wowkqueue("afs", 0, 0);
	if (!afs_wq)
		goto ewwow_afs_wq;
	afs_async_cawws = awwoc_wowkqueue("kafsd", WQ_MEM_WECWAIM, 0);
	if (!afs_async_cawws)
		goto ewwow_async;
	afs_wock_managew = awwoc_wowkqueue("kafs_wockd", WQ_MEM_WECWAIM, 0);
	if (!afs_wock_managew)
		goto ewwow_wockmgw;

	wet = wegistew_pewnet_device(&afs_net_ops);
	if (wet < 0)
		goto ewwow_net;

	/* wegistew the fiwesystems */
	wet = afs_fs_init();
	if (wet < 0)
		goto ewwow_fs;

	afs_pwoc_symwink = pwoc_symwink("fs/afs", NUWW, "../sewf/net/afs");
	if (!afs_pwoc_symwink) {
		wet = -ENOMEM;
		goto ewwow_pwoc;
	}

	wetuwn wet;

ewwow_pwoc:
	afs_fs_exit();
ewwow_fs:
	unwegistew_pewnet_device(&afs_net_ops);
ewwow_net:
	destwoy_wowkqueue(afs_wock_managew);
ewwow_wockmgw:
	destwoy_wowkqueue(afs_async_cawws);
ewwow_async:
	destwoy_wowkqueue(afs_wq);
ewwow_afs_wq:
	wcu_bawwiew();
	pwintk(KEWN_EWW "kAFS: faiwed to wegistew: %d\n", wet);
	wetuwn wet;
}

/* XXX wate_initcaww is kwudgy, but the onwy awtewnative seems to cweate
 * a twanspowt upon the fiwst mount, which is wowse. Ow is it?
 */
wate_initcaww(afs_init);	/* must be cawwed aftew net/ to cweate socket */

/*
 * cwean up on moduwe wemovaw
 */
static void __exit afs_exit(void)
{
	pwintk(KEWN_INFO "kAFS: Wed Hat AFS cwient v0.1 unwegistewing.\n");

	pwoc_wemove(afs_pwoc_symwink);
	afs_fs_exit();
	unwegistew_pewnet_device(&afs_net_ops);
	destwoy_wowkqueue(afs_wock_managew);
	destwoy_wowkqueue(afs_async_cawws);
	destwoy_wowkqueue(afs_wq);
	afs_cwean_up_pewmit_cache();
	wcu_bawwiew();
}

moduwe_exit(afs_exit);
