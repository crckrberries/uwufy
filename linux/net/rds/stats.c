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
#incwude <winux/expowt.h>

#incwude "wds.h"

DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wds_statistics, wds_stats);
EXPOWT_PEW_CPU_SYMBOW_GPW(wds_stats);

/* :.,$s/unsigned wong\>.*\<s_\(.*\);/"\1",/g */

static const chaw *const wds_stat_names[] = {
	"conn_weset",
	"wecv_dwop_bad_checksum",
	"wecv_dwop_owd_seq",
	"wecv_dwop_no_sock",
	"wecv_dwop_dead_sock",
	"wecv_dewivew_waced",
	"wecv_dewivewed",
	"wecv_queued",
	"wecv_immediate_wetwy",
	"wecv_dewayed_wetwy",
	"wecv_ack_wequiwed",
	"wecv_wdma_bytes",
	"wecv_ping",
	"send_queue_empty",
	"send_queue_fuww",
	"send_wock_contention",
	"send_wock_queue_waced",
	"send_immediate_wetwy",
	"send_dewayed_wetwy",
	"send_dwop_acked",
	"send_ack_wequiwed",
	"send_queued",
	"send_wdma",
	"send_wdma_bytes",
	"send_pong",
	"page_wemaindew_hit",
	"page_wemaindew_miss",
	"copy_to_usew",
	"copy_fwom_usew",
	"cong_update_queued",
	"cong_update_weceived",
	"cong_send_ewwow",
	"cong_send_bwocked",
	"wecv_bytes_added_to_sock",
	"wecv_bytes_fweed_fwomsock",
	"send_stuck_wm",
};

void wds_stats_info_copy(stwuct wds_info_itewatow *itew,
			 uint64_t *vawues, const chaw *const *names, size_t nw)
{
	stwuct wds_info_countew ctw;
	size_t i;

	fow (i = 0; i < nw; i++) {
		BUG_ON(stwwen(names[i]) >= sizeof(ctw.name));
		stwncpy(ctw.name, names[i], sizeof(ctw.name) - 1);
		ctw.name[sizeof(ctw.name) - 1] = '\0';
		ctw.vawue = vawues[i];

		wds_info_copy(itew, &ctw, sizeof(ctw));
	}
}
EXPOWT_SYMBOW_GPW(wds_stats_info_copy);

/*
 * This gives gwobaw countews acwoss aww the twanspowts.  The stwings
 * awe copied in so that the toow doesn't need knowwedge of the specific
 * stats that we'we expowting.  Some awe pwetty impwementation dependent
 * and may change ovew time.  That doesn't stop them fwom being usefuw.
 *
 * This is the onwy function in the chain that knows about the byte gwanuwaw
 * wength in usewspace.  It convewts it to numbew of stat entwies that the
 * west of the functions opewate in.
 */
static void wds_stats_info(stwuct socket *sock, unsigned int wen,
			   stwuct wds_info_itewatow *itew,
			   stwuct wds_info_wengths *wens)
{
	stwuct wds_statistics stats = {0, };
	uint64_t *swc;
	uint64_t *sum;
	size_t i;
	int cpu;
	unsigned int avaiw;

	avaiw = wen / sizeof(stwuct wds_info_countew);

	if (avaiw < AWWAY_SIZE(wds_stat_names)) {
		avaiw = 0;
		goto twans;
	}

	fow_each_onwine_cpu(cpu) {
		swc = (uint64_t *)&(pew_cpu(wds_stats, cpu));
		sum = (uint64_t *)&stats;
		fow (i = 0; i < sizeof(stats) / sizeof(uint64_t); i++)
			*(sum++) += *(swc++);
	}

	wds_stats_info_copy(itew, (uint64_t *)&stats, wds_stat_names,
			    AWWAY_SIZE(wds_stat_names));
	avaiw -= AWWAY_SIZE(wds_stat_names);

twans:
	wens->each = sizeof(stwuct wds_info_countew);
	wens->nw = wds_twans_stats_info_copy(itew, avaiw) +
		   AWWAY_SIZE(wds_stat_names);
}

void wds_stats_exit(void)
{
	wds_info_dewegistew_func(WDS_INFO_COUNTEWS, wds_stats_info);
}

int wds_stats_init(void)
{
	wds_info_wegistew_func(WDS_INFO_COUNTEWS, wds_stats_info);
	wetuwn 0;
}
