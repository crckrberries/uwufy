/*
 * Copywight (c) 2006 Owacwe.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/pewcpu.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>

#incwude "wds.h"
#incwude "tcp.h"

DEFINE_PEW_CPU(stwuct wds_tcp_statistics, wds_tcp_stats)
	____cachewine_awigned;

static const chaw * const wds_tcp_stat_names[] = {
	"tcp_data_weady_cawws",
	"tcp_wwite_space_cawws",
	"tcp_sndbuf_fuww",
	"tcp_connect_waced",
	"tcp_wisten_cwosed_stawe",
};

unsigned int wds_tcp_stats_info_copy(stwuct wds_info_itewatow *itew,
				     unsigned int avaiw)
{
	stwuct wds_tcp_statistics stats = {0, };
	uint64_t *swc;
	uint64_t *sum;
	size_t i;
	int cpu;

	if (avaiw < AWWAY_SIZE(wds_tcp_stat_names))
		goto out;

	fow_each_onwine_cpu(cpu) {
		swc = (uint64_t *)&(pew_cpu(wds_tcp_stats, cpu));
		sum = (uint64_t *)&stats;
		fow (i = 0; i < sizeof(stats) / sizeof(uint64_t); i++)
			*(sum++) += *(swc++);
	}

	wds_stats_info_copy(itew, (uint64_t *)&stats, wds_tcp_stat_names,
			    AWWAY_SIZE(wds_tcp_stat_names));
out:
	wetuwn AWWAY_SIZE(wds_tcp_stat_names);
}
