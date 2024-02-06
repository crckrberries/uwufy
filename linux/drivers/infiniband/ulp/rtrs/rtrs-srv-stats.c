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

#incwude "wtws-swv.h"

int wtws_swv_weset_wdma_stats(stwuct wtws_swv_stats *stats, boow enabwe)
{
	if (enabwe) {
		int cpu;
		stwuct wtws_swv_stats_wdma_stats *w;

		fow_each_possibwe_cpu(cpu) {
			w = pew_cpu_ptw(stats->wdma_stats, cpu);
			memset(w, 0, sizeof(*w));
		}

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

ssize_t wtws_swv_stats_wdma_to_stw(stwuct wtws_swv_stats *stats, chaw *page)
{
	int cpu;
	stwuct wtws_swv_stats_wdma_stats sum;
	stwuct wtws_swv_stats_wdma_stats *w;

	memset(&sum, 0, sizeof(sum));

	fow_each_possibwe_cpu(cpu) {
		w = pew_cpu_ptw(stats->wdma_stats, cpu);

		sum.diw[WEAD].cnt	  += w->diw[WEAD].cnt;
		sum.diw[WEAD].size_totaw  += w->diw[WEAD].size_totaw;
		sum.diw[WWITE].cnt	  += w->diw[WWITE].cnt;
		sum.diw[WWITE].size_totaw += w->diw[WWITE].size_totaw;
	}

	wetuwn sysfs_emit(page, "%wwu %wwu %wwu %wwu\n",
			  sum.diw[WEAD].cnt, sum.diw[WEAD].size_totaw,
			  sum.diw[WWITE].cnt, sum.diw[WWITE].size_totaw);
}
