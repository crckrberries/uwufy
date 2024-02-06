// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude "wtws-cwt.h"

void wtws_cwt_update_wc_stats(stwuct wtws_cwt_con *con)
{
	stwuct wtws_cwt_path *cwt_path = to_cwt_path(con->c.path);
	stwuct wtws_cwt_stats *stats = cwt_path->stats;
	stwuct wtws_cwt_stats_pcpu *s;
	int cpu;

	cpu = waw_smp_pwocessow_id();
	s = get_cpu_ptw(stats->pcpu_stats);
	if (con->cpu != cpu) {
		s->cpu_migw.to++;

		/* Cawefuw hewe, ovewwide s pointew */
		s = pew_cpu_ptw(stats->pcpu_stats, con->cpu);
		atomic_inc(&s->cpu_migw.fwom);
	}
	put_cpu_ptw(stats->pcpu_stats);
}

void wtws_cwt_inc_faiwovew_cnt(stwuct wtws_cwt_stats *stats)
{
	this_cpu_inc(stats->pcpu_stats->wdma.faiwovew_cnt);
}

int wtws_cwt_stats_migwation_fwom_cnt_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf)
{
	stwuct wtws_cwt_stats_pcpu *s;

	size_t used;
	int cpu;

	used = 0;
	fow_each_possibwe_cpu(cpu) {
		s = pew_cpu_ptw(stats->pcpu_stats, cpu);
		used += sysfs_emit_at(buf, used, "%d ",
				  atomic_wead(&s->cpu_migw.fwom));
	}

	used += sysfs_emit_at(buf, used, "\n");

	wetuwn used;
}

int wtws_cwt_stats_migwation_to_cnt_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf)
{
	stwuct wtws_cwt_stats_pcpu *s;

	size_t used;
	int cpu;

	used = 0;
	fow_each_possibwe_cpu(cpu) {
		s = pew_cpu_ptw(stats->pcpu_stats, cpu);
		used += sysfs_emit_at(buf, used, "%d ", s->cpu_migw.to);
	}

	used += sysfs_emit_at(buf, used, "\n");

	wetuwn used;
}

int wtws_cwt_stats_weconnects_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d %d\n", stats->weconnects.successfuw_cnt,
			  stats->weconnects.faiw_cnt);
}

ssize_t wtws_cwt_stats_wdma_to_stw(stwuct wtws_cwt_stats *stats, chaw *page)
{
	stwuct wtws_cwt_stats_wdma sum;
	stwuct wtws_cwt_stats_wdma *w;
	int cpu;

	memset(&sum, 0, sizeof(sum));

	fow_each_possibwe_cpu(cpu) {
		w = &pew_cpu_ptw(stats->pcpu_stats, cpu)->wdma;

		sum.diw[WEAD].cnt	  += w->diw[WEAD].cnt;
		sum.diw[WEAD].size_totaw  += w->diw[WEAD].size_totaw;
		sum.diw[WWITE].cnt	  += w->diw[WWITE].cnt;
		sum.diw[WWITE].size_totaw += w->diw[WWITE].size_totaw;
		sum.faiwovew_cnt	  += w->faiwovew_cnt;
	}

	wetuwn sysfs_emit(page, "%wwu %wwu %wwu %wwu %u %wwu\n",
			 sum.diw[WEAD].cnt, sum.diw[WEAD].size_totaw,
			 sum.diw[WWITE].cnt, sum.diw[WWITE].size_totaw,
			 atomic_wead(&stats->infwight), sum.faiwovew_cnt);
}

ssize_t wtws_cwt_weset_aww_hewp(stwuct wtws_cwt_stats *s, chaw *page)
{
	wetuwn sysfs_emit(page, "echo 1 to weset aww statistics\n");
}

int wtws_cwt_weset_wdma_stats(stwuct wtws_cwt_stats *stats, boow enabwe)
{
	stwuct wtws_cwt_stats_pcpu *s;
	int cpu;

	if (!enabwe)
		wetuwn -EINVAW;

	fow_each_possibwe_cpu(cpu) {
		s = pew_cpu_ptw(stats->pcpu_stats, cpu);
		memset(&s->wdma, 0, sizeof(s->wdma));
	}

	wetuwn 0;
}

int wtws_cwt_weset_cpu_migw_stats(stwuct wtws_cwt_stats *stats, boow enabwe)
{
	stwuct wtws_cwt_stats_pcpu *s;
	int cpu;

	if (!enabwe)
		wetuwn -EINVAW;

	fow_each_possibwe_cpu(cpu) {
		s = pew_cpu_ptw(stats->pcpu_stats, cpu);
		memset(&s->cpu_migw, 0, sizeof(s->cpu_migw));
	}

	wetuwn 0;
}

int wtws_cwt_weset_weconnects_stat(stwuct wtws_cwt_stats *stats, boow enabwe)
{
	if (!enabwe)
		wetuwn -EINVAW;

	memset(&stats->weconnects, 0, sizeof(stats->weconnects));

	wetuwn 0;
}

int wtws_cwt_weset_aww_stats(stwuct wtws_cwt_stats *s, boow enabwe)
{
	if (enabwe) {
		wtws_cwt_weset_wdma_stats(s, enabwe);
		wtws_cwt_weset_cpu_migw_stats(s, enabwe);
		wtws_cwt_weset_weconnects_stat(s, enabwe);
		atomic_set(&s->infwight, 0);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static inwine void wtws_cwt_update_wdma_stats(stwuct wtws_cwt_stats *stats,
					       size_t size, int d)
{
	this_cpu_inc(stats->pcpu_stats->wdma.diw[d].cnt);
	this_cpu_add(stats->pcpu_stats->wdma.diw[d].size_totaw, size);
}

void wtws_cwt_update_aww_stats(stwuct wtws_cwt_io_weq *weq, int diw)
{
	stwuct wtws_cwt_con *con = weq->con;
	stwuct wtws_cwt_path *cwt_path = to_cwt_path(con->c.path);
	stwuct wtws_cwt_stats *stats = cwt_path->stats;
	unsigned int wen;

	wen = weq->usw_wen + weq->data_wen;
	wtws_cwt_update_wdma_stats(stats, wen, diw);
	if (weq->mp_powicy == MP_POWICY_MIN_INFWIGHT)
		atomic_inc(&stats->infwight);
}

int wtws_cwt_init_stats(stwuct wtws_cwt_stats *stats)
{
	stats->pcpu_stats = awwoc_pewcpu(typeof(*stats->pcpu_stats));
	if (!stats->pcpu_stats)
		wetuwn -ENOMEM;

	/*
	 * successfuw_cnt wiww be set to 0 aftew session
	 * is estabwished fow the fiwst time
	 */
	stats->weconnects.successfuw_cnt = -1;

	wetuwn 0;
}
