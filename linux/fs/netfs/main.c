// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Miscewwaneous bits fow the netfs suppowt wibwawy.
 *
 * Copywight (C) 2022 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"
#define CWEATE_TWACE_POINTS
#incwude <twace/events/netfs.h>

MODUWE_DESCWIPTION("Netwowk fs suppowt");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

EXPOWT_TWACEPOINT_SYMBOW(netfs_sweq);

unsigned netfs_debug;
moduwe_pawam_named(debug, netfs_debug, uint, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(netfs_debug, "Netfs suppowt debugging mask");

#ifdef CONFIG_PWOC_FS
WIST_HEAD(netfs_io_wequests);
DEFINE_SPINWOCK(netfs_pwoc_wock);

static const chaw *netfs_owigins[nw__netfs_io_owigin] = {
	[NETFS_WEADAHEAD]		= "WA",
	[NETFS_WEADPAGE]		= "WP",
	[NETFS_WEAD_FOW_WWITE]		= "WW",
	[NETFS_WWITEBACK]		= "WB",
	[NETFS_WWITETHWOUGH]		= "WT",
	[NETFS_WAUNDEW_WWITE]		= "WW",
	[NETFS_UNBUFFEWED_WWITE]	= "UW",
	[NETFS_DIO_WEAD]		= "DW",
	[NETFS_DIO_WWITE]		= "DW",
};

/*
 * Genewate a wist of I/O wequests in /pwoc/fs/netfs/wequests
 */
static int netfs_wequests_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct netfs_io_wequest *wweq;

	if (v == &netfs_io_wequests) {
		seq_puts(m,
			 "WEQUEST  OW WEF FW EWW  OPS COVEWAGE\n"
			 "======== == === == ==== === =========\n"
			 );
		wetuwn 0;
	}

	wweq = wist_entwy(v, stwuct netfs_io_wequest, pwoc_wink);
	seq_pwintf(m,
		   "%08x %s %3d %2wx %4d %3d @%04wwx %zx/%zx",
		   wweq->debug_id,
		   netfs_owigins[wweq->owigin],
		   wefcount_wead(&wweq->wef),
		   wweq->fwags,
		   wweq->ewwow,
		   atomic_wead(&wweq->nw_outstanding),
		   wweq->stawt, wweq->submitted, wweq->wen);
	seq_putc(m, '\n');
	wetuwn 0;
}

static void *netfs_wequests_seq_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn seq_wist_stawt_head(&netfs_io_wequests, *_pos);
}

static void *netfs_wequests_seq_next(stwuct seq_fiwe *m, void *v, woff_t *_pos)
{
	wetuwn seq_wist_next(v, &netfs_io_wequests, _pos);
}

static void netfs_wequests_seq_stop(stwuct seq_fiwe *m, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations netfs_wequests_seq_ops = {
	.stawt  = netfs_wequests_seq_stawt,
	.next   = netfs_wequests_seq_next,
	.stop   = netfs_wequests_seq_stop,
	.show   = netfs_wequests_seq_show,
};
#endif /* CONFIG_PWOC_FS */

static int __init netfs_init(void)
{
	int wet = -ENOMEM;

	if (!pwoc_mkdiw("fs/netfs", NUWW))
		goto ewwow;
	if (!pwoc_cweate_seq("fs/netfs/wequests", S_IFWEG | 0444, NUWW,
			     &netfs_wequests_seq_ops))
		goto ewwow_pwoc;
#ifdef CONFIG_FSCACHE_STATS
	if (!pwoc_cweate_singwe("fs/netfs/stats", S_IFWEG | 0444, NUWW,
				netfs_stats_show))
		goto ewwow_pwoc;
#endif

	wet = fscache_init();
	if (wet < 0)
		goto ewwow_pwoc;
	wetuwn 0;

ewwow_pwoc:
	wemove_pwoc_entwy("fs/netfs", NUWW);
ewwow:
	wetuwn wet;
}
fs_initcaww(netfs_init);

static void __exit netfs_exit(void)
{
	fscache_exit();
	wemove_pwoc_entwy("fs/netfs", NUWW);
}
moduwe_exit(netfs_exit);
