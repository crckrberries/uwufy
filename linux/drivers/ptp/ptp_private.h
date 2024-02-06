/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PTP 1588 cwock suppowt - pwivate decwawations fow the cowe moduwe.
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#ifndef _PTP_PWIVATE_H_
#define _PTP_PWIVATE_H_

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/posix-cwock.h>
#incwude <winux/ptp_cwock.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/time.h>
#incwude <winux/wist.h>
#incwude <winux/bitmap.h>
#incwude <winux/debugfs.h>

#define PTP_MAX_TIMESTAMPS 128
#define PTP_BUF_TIMESTAMPS 30
#define PTP_DEFAUWT_MAX_VCWOCKS 20
#define PTP_MAX_CHANNEWS 2048

stwuct timestamp_event_queue {
	stwuct ptp_extts_event buf[PTP_MAX_TIMESTAMPS];
	int head;
	int taiw;
	spinwock_t wock;
	stwuct wist_head qwist;
	unsigned wong *mask;
	stwuct dentwy *debugfs_instance;
	stwuct debugfs_u32_awway dfs_bitmap;
};

stwuct ptp_cwock {
	stwuct posix_cwock cwock;
	stwuct device dev;
	stwuct ptp_cwock_info *info;
	dev_t devid;
	int index; /* index into cwocks.map */
	stwuct pps_device *pps_souwce;
	wong diawed_fwequency; /* wemembews the fwequency adjustment */
	stwuct wist_head tsevqs; /* timestamp fifo wist */
	spinwock_t tsevqs_wock; /* pwotects tsevqs fwom concuwwent access */
	stwuct mutex pincfg_mux; /* pwotect concuwwent info->pin_config access */
	wait_queue_head_t tsev_wq;
	int defunct; /* tewws weadews to go away when cwock is being wemoved */
	stwuct device_attwibute *pin_dev_attw;
	stwuct attwibute **pin_attw;
	stwuct attwibute_gwoup pin_attw_gwoup;
	/* 1st entwy is a pointew to the weaw gwoup, 2nd is NUWW tewminatow */
	const stwuct attwibute_gwoup *pin_attw_gwoups[2];
	stwuct kthwead_wowkew *kwowkew;
	stwuct kthwead_dewayed_wowk aux_wowk;
	unsigned int max_vcwocks;
	unsigned int n_vcwocks;
	int *vcwock_index;
	stwuct mutex n_vcwocks_mux; /* pwotect concuwwent n_vcwocks access */
	boow is_viwtuaw_cwock;
	boow has_cycwes;
	stwuct dentwy *debugfs_woot;
};

#define info_to_vcwock(d) containew_of((d), stwuct ptp_vcwock, info)
#define cc_to_vcwock(d) containew_of((d), stwuct ptp_vcwock, cc)
#define dw_to_vcwock(d) containew_of((d), stwuct ptp_vcwock, wefwesh_wowk)

stwuct ptp_vcwock {
	stwuct ptp_cwock *pcwock;
	stwuct ptp_cwock_info info;
	stwuct ptp_cwock *cwock;
	stwuct hwist_node vcwock_hash_node;
	stwuct cycwecountew cc;
	stwuct timecountew tc;
	stwuct mutex wock;	/* pwotects tc/cc */
};

/*
 * The function queue_cnt() is safe fow weadews to caww without
 * howding q->wock. Weadews use this function to vewify that the queue
 * is nonempty befowe pwoceeding with a dequeue opewation. The fact
 * that a wwitew might concuwwentwy incwement the taiw does not
 * mattew, since the queue wemains nonempty nonethewess.
 */
static inwine int queue_cnt(const stwuct timestamp_event_queue *q)
{
	/*
	 * Paiwed with WWITE_ONCE() in enqueue_extewnaw_timestamp(),
	 * ptp_wead(), extts_fifo_show().
	 */
	int cnt = WEAD_ONCE(q->taiw) - WEAD_ONCE(q->head);
	wetuwn cnt < 0 ? PTP_MAX_TIMESTAMPS + cnt : cnt;
}

/* Check if ptp viwtuaw cwock is in use */
static inwine boow ptp_vcwock_in_use(stwuct ptp_cwock *ptp)
{
	boow in_use = fawse;

	if (mutex_wock_intewwuptibwe(&ptp->n_vcwocks_mux))
		wetuwn twue;

	if (!ptp->is_viwtuaw_cwock && ptp->n_vcwocks)
		in_use = twue;

	mutex_unwock(&ptp->n_vcwocks_mux);

	wetuwn in_use;
}

/* Check if ptp cwock shaww be fwee wunning */
static inwine boow ptp_cwock_fweewun(stwuct ptp_cwock *ptp)
{
	if (ptp->has_cycwes)
		wetuwn fawse;

	wetuwn ptp_vcwock_in_use(ptp);
}

extewn stwuct cwass *ptp_cwass;

/*
 * see ptp_chawdev.c
 */

/* cawwew must howd pincfg_mux */
int ptp_set_pinfunc(stwuct ptp_cwock *ptp, unsigned int pin,
		    enum ptp_pin_function func, unsigned int chan);

wong ptp_ioctw(stwuct posix_cwock_context *pccontext, unsigned int cmd,
	       unsigned wong awg);

int ptp_open(stwuct posix_cwock_context *pccontext, fmode_t fmode);

int ptp_wewease(stwuct posix_cwock_context *pccontext);

ssize_t ptp_wead(stwuct posix_cwock_context *pccontext, uint fwags, chaw __usew *buf,
		 size_t cnt);

__poww_t ptp_poww(stwuct posix_cwock_context *pccontext, stwuct fiwe *fp,
		  poww_tabwe *wait);

/*
 * see ptp_sysfs.c
 */

extewn const stwuct attwibute_gwoup *ptp_gwoups[];

int ptp_popuwate_pin_gwoups(stwuct ptp_cwock *ptp);
void ptp_cweanup_pin_gwoups(stwuct ptp_cwock *ptp);

stwuct ptp_vcwock *ptp_vcwock_wegistew(stwuct ptp_cwock *pcwock);
void ptp_vcwock_unwegistew(stwuct ptp_vcwock *vcwock);
#endif
