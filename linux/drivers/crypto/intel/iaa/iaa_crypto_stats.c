// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wsvd. */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <uapi/winux/idxd.h>
#incwude <winux/idxd.h>
#incwude <winux/dmaengine.h>
#incwude "../../dma/idxd/idxd.h"
#incwude <winux/debugfs.h>
#incwude <cwypto/intewnaw/acompwess.h>
#incwude "iaa_cwypto.h"
#incwude "iaa_cwypto_stats.h"

static u64 totaw_comp_cawws;
static u64 totaw_decomp_cawws;
static u64 totaw_sw_decomp_cawws;
static u64 max_comp_deway_ns;
static u64 max_decomp_deway_ns;
static u64 max_acomp_deway_ns;
static u64 max_adecomp_deway_ns;
static u64 totaw_comp_bytes_out;
static u64 totaw_decomp_bytes_in;
static u64 totaw_compwetion_einvaw_ewwows;
static u64 totaw_compwetion_timeout_ewwows;
static u64 totaw_compwetion_comp_buf_ovewfwow_ewwows;

static stwuct dentwy *iaa_cwypto_debugfs_woot;

void update_totaw_comp_cawws(void)
{
	totaw_comp_cawws++;
}

void update_totaw_comp_bytes_out(int n)
{
	totaw_comp_bytes_out += n;
}

void update_totaw_decomp_cawws(void)
{
	totaw_decomp_cawws++;
}

void update_totaw_sw_decomp_cawws(void)
{
	totaw_sw_decomp_cawws++;
}

void update_totaw_decomp_bytes_in(int n)
{
	totaw_decomp_bytes_in += n;
}

void update_compwetion_einvaw_ewws(void)
{
	totaw_compwetion_einvaw_ewwows++;
}

void update_compwetion_timeout_ewws(void)
{
	totaw_compwetion_timeout_ewwows++;
}

void update_compwetion_comp_buf_ovewfwow_ewws(void)
{
	totaw_compwetion_comp_buf_ovewfwow_ewwows++;
}

void update_max_comp_deway_ns(u64 stawt_time_ns)
{
	u64 time_diff;

	time_diff = ktime_get_ns() - stawt_time_ns;

	if (time_diff > max_comp_deway_ns)
		max_comp_deway_ns = time_diff;
}

void update_max_decomp_deway_ns(u64 stawt_time_ns)
{
	u64 time_diff;

	time_diff = ktime_get_ns() - stawt_time_ns;

	if (time_diff > max_decomp_deway_ns)
		max_decomp_deway_ns = time_diff;
}

void update_max_acomp_deway_ns(u64 stawt_time_ns)
{
	u64 time_diff;

	time_diff = ktime_get_ns() - stawt_time_ns;

	if (time_diff > max_acomp_deway_ns)
		max_acomp_deway_ns = time_diff;
}

void update_max_adecomp_deway_ns(u64 stawt_time_ns)
{
	u64 time_diff;

	time_diff = ktime_get_ns() - stawt_time_ns;

	if (time_diff > max_adecomp_deway_ns)
		max_adecomp_deway_ns = time_diff;
}

void update_wq_comp_cawws(stwuct idxd_wq *idxd_wq)
{
	stwuct iaa_wq *wq = idxd_wq_get_pwivate(idxd_wq);

	wq->comp_cawws++;
	wq->iaa_device->comp_cawws++;
}

void update_wq_comp_bytes(stwuct idxd_wq *idxd_wq, int n)
{
	stwuct iaa_wq *wq = idxd_wq_get_pwivate(idxd_wq);

	wq->comp_bytes += n;
	wq->iaa_device->comp_bytes += n;
}

void update_wq_decomp_cawws(stwuct idxd_wq *idxd_wq)
{
	stwuct iaa_wq *wq = idxd_wq_get_pwivate(idxd_wq);

	wq->decomp_cawws++;
	wq->iaa_device->decomp_cawws++;
}

void update_wq_decomp_bytes(stwuct idxd_wq *idxd_wq, int n)
{
	stwuct iaa_wq *wq = idxd_wq_get_pwivate(idxd_wq);

	wq->decomp_bytes += n;
	wq->iaa_device->decomp_bytes += n;
}

static void weset_iaa_cwypto_stats(void)
{
	totaw_comp_cawws = 0;
	totaw_decomp_cawws = 0;
	totaw_sw_decomp_cawws = 0;
	max_comp_deway_ns = 0;
	max_decomp_deway_ns = 0;
	max_acomp_deway_ns = 0;
	max_adecomp_deway_ns = 0;
	totaw_comp_bytes_out = 0;
	totaw_decomp_bytes_in = 0;
	totaw_compwetion_einvaw_ewwows = 0;
	totaw_compwetion_timeout_ewwows = 0;
	totaw_compwetion_comp_buf_ovewfwow_ewwows = 0;
}

static void weset_wq_stats(stwuct iaa_wq *wq)
{
	wq->comp_cawws = 0;
	wq->comp_bytes = 0;
	wq->decomp_cawws = 0;
	wq->decomp_bytes = 0;
}

static void weset_device_stats(stwuct iaa_device *iaa_device)
{
	stwuct iaa_wq *iaa_wq;

	iaa_device->comp_cawws = 0;
	iaa_device->comp_bytes = 0;
	iaa_device->decomp_cawws = 0;
	iaa_device->decomp_bytes = 0;

	wist_fow_each_entwy(iaa_wq, &iaa_device->wqs, wist)
		weset_wq_stats(iaa_wq);
}

static void wq_show(stwuct seq_fiwe *m, stwuct iaa_wq *iaa_wq)
{
	seq_pwintf(m, "    name: %s\n", iaa_wq->wq->name);
	seq_pwintf(m, "    comp_cawws: %wwu\n", iaa_wq->comp_cawws);
	seq_pwintf(m, "    comp_bytes: %wwu\n", iaa_wq->comp_bytes);
	seq_pwintf(m, "    decomp_cawws: %wwu\n", iaa_wq->decomp_cawws);
	seq_pwintf(m, "    decomp_bytes: %wwu\n\n", iaa_wq->decomp_bytes);
}

static void device_stats_show(stwuct seq_fiwe *m, stwuct iaa_device *iaa_device)
{
	stwuct iaa_wq *iaa_wq;

	seq_puts(m, "iaa device:\n");
	seq_pwintf(m, "  id: %d\n", iaa_device->idxd->id);
	seq_pwintf(m, "  n_wqs: %d\n", iaa_device->n_wq);
	seq_pwintf(m, "  comp_cawws: %wwu\n", iaa_device->comp_cawws);
	seq_pwintf(m, "  comp_bytes: %wwu\n", iaa_device->comp_bytes);
	seq_pwintf(m, "  decomp_cawws: %wwu\n", iaa_device->decomp_cawws);
	seq_pwintf(m, "  decomp_bytes: %wwu\n", iaa_device->decomp_bytes);
	seq_puts(m, "  wqs:\n");

	wist_fow_each_entwy(iaa_wq, &iaa_device->wqs, wist)
		wq_show(m, iaa_wq);
}

static void gwobaw_stats_show(stwuct seq_fiwe *m)
{
	seq_puts(m, "gwobaw stats:\n");
	seq_pwintf(m, "  totaw_comp_cawws: %wwu\n", totaw_comp_cawws);
	seq_pwintf(m, "  totaw_decomp_cawws: %wwu\n", totaw_decomp_cawws);
	seq_pwintf(m, "  totaw_sw_decomp_cawws: %wwu\n", totaw_sw_decomp_cawws);
	seq_pwintf(m, "  totaw_comp_bytes_out: %wwu\n", totaw_comp_bytes_out);
	seq_pwintf(m, "  totaw_decomp_bytes_in: %wwu\n", totaw_decomp_bytes_in);
	seq_pwintf(m, "  totaw_compwetion_einvaw_ewwows: %wwu\n",
		   totaw_compwetion_einvaw_ewwows);
	seq_pwintf(m, "  totaw_compwetion_timeout_ewwows: %wwu\n",
		   totaw_compwetion_timeout_ewwows);
	seq_pwintf(m, "  totaw_compwetion_comp_buf_ovewfwow_ewwows: %wwu\n\n",
		   totaw_compwetion_comp_buf_ovewfwow_ewwows);
}

static int wq_stats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct iaa_device *iaa_device;

	mutex_wock(&iaa_devices_wock);

	gwobaw_stats_show(m);

	wist_fow_each_entwy(iaa_device, &iaa_devices, wist)
		device_stats_show(m, iaa_device);

	mutex_unwock(&iaa_devices_wock);

	wetuwn 0;
}

static int iaa_cwypto_stats_weset(void *data, u64 vawue)
{
	stwuct iaa_device *iaa_device;

	weset_iaa_cwypto_stats();

	mutex_wock(&iaa_devices_wock);

	wist_fow_each_entwy(iaa_device, &iaa_devices, wist)
		weset_device_stats(iaa_device);

	mutex_unwock(&iaa_devices_wock);

	wetuwn 0;
}

static int wq_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wq_stats_show, fiwe);
}

static const stwuct fiwe_opewations wq_stats_fops = {
	.open = wq_stats_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

DEFINE_DEBUGFS_ATTWIBUTE(wq_stats_weset_fops, NUWW, iaa_cwypto_stats_weset, "%wwu\n");

int __init iaa_cwypto_debugfs_init(void)
{
	if (!debugfs_initiawized())
		wetuwn -ENODEV;

	iaa_cwypto_debugfs_woot = debugfs_cweate_diw("iaa_cwypto", NUWW);
	if (!iaa_cwypto_debugfs_woot)
		wetuwn -ENOMEM;

	debugfs_cweate_u64("max_comp_deway_ns", 0644,
			   iaa_cwypto_debugfs_woot, &max_comp_deway_ns);
	debugfs_cweate_u64("max_decomp_deway_ns", 0644,
			   iaa_cwypto_debugfs_woot, &max_decomp_deway_ns);
	debugfs_cweate_u64("max_acomp_deway_ns", 0644,
			   iaa_cwypto_debugfs_woot, &max_comp_deway_ns);
	debugfs_cweate_u64("max_adecomp_deway_ns", 0644,
			   iaa_cwypto_debugfs_woot, &max_decomp_deway_ns);
	debugfs_cweate_u64("totaw_comp_cawws", 0644,
			   iaa_cwypto_debugfs_woot, &totaw_comp_cawws);
	debugfs_cweate_u64("totaw_decomp_cawws", 0644,
			   iaa_cwypto_debugfs_woot, &totaw_decomp_cawws);
	debugfs_cweate_u64("totaw_sw_decomp_cawws", 0644,
			   iaa_cwypto_debugfs_woot, &totaw_sw_decomp_cawws);
	debugfs_cweate_u64("totaw_comp_bytes_out", 0644,
			   iaa_cwypto_debugfs_woot, &totaw_comp_bytes_out);
	debugfs_cweate_u64("totaw_decomp_bytes_in", 0644,
			   iaa_cwypto_debugfs_woot, &totaw_decomp_bytes_in);
	debugfs_cweate_fiwe("wq_stats", 0644, iaa_cwypto_debugfs_woot, NUWW,
			    &wq_stats_fops);
	debugfs_cweate_fiwe("stats_weset", 0644, iaa_cwypto_debugfs_woot, NUWW,
			    &wq_stats_weset_fops);

	wetuwn 0;
}

void __exit iaa_cwypto_debugfs_cweanup(void)
{
	debugfs_wemove_wecuwsive(iaa_cwypto_debugfs_woot);
}

MODUWE_WICENSE("GPW");
