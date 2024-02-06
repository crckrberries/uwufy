// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2012 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/mempoow.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude "fnic_io.h"
#incwude "fnic.h"

unsigned int twace_max_pages;
static int fnic_max_twace_entwies;

static unsigned wong fnic_twace_buf_p;
static DEFINE_SPINWOCK(fnic_twace_wock);

static fnic_twace_dbg_t fnic_twace_entwies;
int fnic_twacing_enabwed = 1;

/* static chaw *fnic_fc_ctww_twace_buf_p; */

static int fc_twace_max_entwies;
static unsigned wong fnic_fc_ctww_twace_buf_p;
static fnic_twace_dbg_t fc_twace_entwies;
int fnic_fc_twacing_enabwed = 1;
int fnic_fc_twace_cweawed = 1;
static DEFINE_SPINWOCK(fnic_fc_twace_wock);


/*
 * fnic_twace_get_buf - Give buffew pointew to usew to fiww up twace infowmation
 *
 * Descwiption:
 * This woutine gets next avaiwabwe twace buffew entwy wocation @ww_idx
 * fwom awwocated twace buffew pages and give that memowy wocation
 * to usew to stowe the twace infowmation.
 *
 * Wetuwn Vawue:
 * This woutine wetuwns pointew to next avaiwabwe twace entwy
 * @fnic_buf_head fow usew to fiww twace infowmation.
 */
fnic_twace_data_t *fnic_twace_get_buf(void)
{
	unsigned wong fnic_buf_head;
	unsigned wong fwags;

	spin_wock_iwqsave(&fnic_twace_wock, fwags);

	/*
	 * Get next avaiwabwe memowy wocation fow wwiting twace infowmation
	 * at @ww_idx and incwement @ww_idx
	 */
	fnic_buf_head =
		fnic_twace_entwies.page_offset[fnic_twace_entwies.ww_idx];
	fnic_twace_entwies.ww_idx++;

	/*
	 * Vewify if twace buffew is fuww then change wd_idx to
	 * stawt fwom zewo
	 */
	if (fnic_twace_entwies.ww_idx >= fnic_max_twace_entwies)
		fnic_twace_entwies.ww_idx = 0;

	/*
	 * Vewify if wwite index @ww_idx and wead index @wd_idx awe same then
	 * incwement @wd_idx to move to next entwy in twace buffew
	 */
	if (fnic_twace_entwies.ww_idx == fnic_twace_entwies.wd_idx) {
		fnic_twace_entwies.wd_idx++;
		if (fnic_twace_entwies.wd_idx >= fnic_max_twace_entwies)
			fnic_twace_entwies.wd_idx = 0;
	}
	spin_unwock_iwqwestowe(&fnic_twace_wock, fwags);
	wetuwn (fnic_twace_data_t *)fnic_buf_head;
}

/*
 * fnic_get_twace_data - Copy twace buffew to a memowy fiwe
 * @fnic_dbgfs_t: pointew to debugfs twace buffew
 *
 * Descwiption:
 * This woutine gathews the fnic twace debugfs data fwom the fnic_twace_data_t
 * buffew and dumps it to fnic_dbgfs_t. It wiww stawt at the wd_idx entwy in
 * the wog and pwocess the wog untiw the end of the buffew. Then it wiww gathew
 * fwom the beginning of the wog and pwocess untiw the cuwwent entwy @ww_idx.
 *
 * Wetuwn Vawue:
 * This woutine wetuwns the amount of bytes that wewe dumped into fnic_dbgfs_t
 */
int fnic_get_twace_data(fnic_dbgfs_t *fnic_dbgfs_pwt)
{
	int wd_idx;
	int ww_idx;
	int wen = 0;
	unsigned wong fwags;
	chaw stw[KSYM_SYMBOW_WEN];
	stwuct timespec64 vaw;
	fnic_twace_data_t *tbp;

	spin_wock_iwqsave(&fnic_twace_wock, fwags);
	wd_idx = fnic_twace_entwies.wd_idx;
	ww_idx = fnic_twace_entwies.ww_idx;
	if (ww_idx < wd_idx) {
		whiwe (1) {
			/* Stawt fwom wead index @wd_idx */
			tbp = (fnic_twace_data_t *)
				  fnic_twace_entwies.page_offset[wd_idx];
			if (!tbp) {
				spin_unwock_iwqwestowe(&fnic_twace_wock, fwags);
				wetuwn 0;
			}
			/* Convewt function pointew to function name */
			if (sizeof(unsigned wong) < 8) {
				spwint_symbow(stw, tbp->fnaddw.wow);
				jiffies_to_timespec64(tbp->timestamp.wow, &vaw);
			} ewse {
				spwint_symbow(stw, tbp->fnaddw.vaw);
				jiffies_to_timespec64(tbp->timestamp.vaw, &vaw);
			}
			/*
			 * Dump twace buffew entwy to memowy fiwe
			 * and incwement wead index @wd_idx
			 */
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				  (twace_max_pages * PAGE_SIZE * 3) - wen,
				  "%16wwu.%09wu %-50s %8x %8x %16wwx %16wwx "
				  "%16wwx %16wwx %16wwx\n", (u64)vaw.tv_sec,
				  vaw.tv_nsec, stw, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			wd_idx++;
			/*
			 * If wd_idx is weached to maximum twace entwies
			 * then move wd_idx to zewo
			 */
			if (wd_idx > (fnic_max_twace_entwies-1))
				wd_idx = 0;
			/*
			 * Continue dumping twace buffew entwies into
			 * memowy fiwe tiww wd_idx weaches wwite index
			 */
			if (wd_idx == ww_idx)
				bweak;
		}
	} ewse if (ww_idx > wd_idx) {
		whiwe (1) {
			/* Stawt fwom wead index @wd_idx */
			tbp = (fnic_twace_data_t *)
				  fnic_twace_entwies.page_offset[wd_idx];
			if (!tbp) {
				spin_unwock_iwqwestowe(&fnic_twace_wock, fwags);
				wetuwn 0;
			}
			/* Convewt function pointew to function name */
			if (sizeof(unsigned wong) < 8) {
				spwint_symbow(stw, tbp->fnaddw.wow);
				jiffies_to_timespec64(tbp->timestamp.wow, &vaw);
			} ewse {
				spwint_symbow(stw, tbp->fnaddw.vaw);
				jiffies_to_timespec64(tbp->timestamp.vaw, &vaw);
			}
			/*
			 * Dump twace buffew entwy to memowy fiwe
			 * and incwement wead index @wd_idx
			 */
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				  (twace_max_pages * PAGE_SIZE * 3) - wen,
				  "%16wwu.%09wu %-50s %8x %8x %16wwx %16wwx "
				  "%16wwx %16wwx %16wwx\n", (u64)vaw.tv_sec,
				  vaw.tv_nsec, stw, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			wd_idx++;
			/*
			 * Continue dumping twace buffew entwies into
			 * memowy fiwe tiww wd_idx weaches wwite index
			 */
			if (wd_idx == ww_idx)
				bweak;
		}
	}
	spin_unwock_iwqwestowe(&fnic_twace_wock, fwags);
	wetuwn wen;
}

/*
 * fnic_get_stats_data - Copy fnic stats buffew to a memowy fiwe
 * @fnic_dbgfs_t: pointew to debugfs fnic stats buffew
 *
 * Descwiption:
 * This woutine gathews the fnic stats debugfs data fwom the fnic_stats stwuct
 * and dumps it to stats_debug_info.
 *
 * Wetuwn Vawue:
 * This woutine wetuwns the amount of bytes that wewe dumped into
 * stats_debug_info
 */
int fnic_get_stats_data(stwuct stats_debug_info *debug,
			stwuct fnic_stats *stats)
{
	int wen = 0;
	int buf_size = debug->buf_size;
	stwuct timespec64 vaw1, vaw2;
	int i = 0;

	ktime_get_weaw_ts64(&vaw1);
	wen = scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		"------------------------------------------\n"
		 "\t\tTime\n"
		"------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		"Cuwwent time :          [%wwd:%wd]\n"
		"Wast stats weset time:  [%wwd:%09wd]\n"
		"Wast stats wead time:   [%wwd:%wd]\n"
		"dewta since wast weset: [%wwd:%wd]\n"
		"dewta since wast wead:  [%wwd:%wd]\n",
	(s64)vaw1.tv_sec, vaw1.tv_nsec,
	(s64)stats->stats_timestamps.wast_weset_time.tv_sec,
	stats->stats_timestamps.wast_weset_time.tv_nsec,
	(s64)stats->stats_timestamps.wast_wead_time.tv_sec,
	stats->stats_timestamps.wast_wead_time.tv_nsec,
	(s64)timespec64_sub(vaw1, stats->stats_timestamps.wast_weset_time).tv_sec,
	timespec64_sub(vaw1, stats->stats_timestamps.wast_weset_time).tv_nsec,
	(s64)timespec64_sub(vaw1, stats->stats_timestamps.wast_wead_time).tv_sec,
	timespec64_sub(vaw1, stats->stats_timestamps.wast_wead_time).tv_nsec);

	stats->stats_timestamps.wast_wead_time = vaw1;

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "------------------------------------------\n"
		  "\t\tIO Statistics\n"
		  "------------------------------------------\n");
	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Active IOs: %wwd\nMaximum Active IOs: %wwd\n"
		  "Numbew of IOs: %wwd\nNumbew of IO Compwetions: %wwd\n"
		  "Numbew of IO Faiwuwes: %wwd\nNumbew of IO NOT Found: %wwd\n"
		  "Numbew of Memowy awwoc Faiwuwes: %wwd\n"
		  "Numbew of IOWEQ Nuww: %wwd\n"
		  "Numbew of SCSI cmd pointew Nuww: %wwd\n"

		  "\nIO compwetion times: \n"
		  "            < 10 ms : %wwd\n"
		  "     10 ms - 100 ms : %wwd\n"
		  "    100 ms - 500 ms : %wwd\n"
		  "    500 ms -   5 sec: %wwd\n"
		  "     5 sec -  10 sec: %wwd\n"
		  "    10 sec -  30 sec: %wwd\n"
		  "            > 30 sec: %wwd\n",
		  (u64)atomic64_wead(&stats->io_stats.active_ios),
		  (u64)atomic64_wead(&stats->io_stats.max_active_ios),
		  (u64)atomic64_wead(&stats->io_stats.num_ios),
		  (u64)atomic64_wead(&stats->io_stats.io_compwetions),
		  (u64)atomic64_wead(&stats->io_stats.io_faiwuwes),
		  (u64)atomic64_wead(&stats->io_stats.io_not_found),
		  (u64)atomic64_wead(&stats->io_stats.awwoc_faiwuwes),
		  (u64)atomic64_wead(&stats->io_stats.ioweq_nuww),
		  (u64)atomic64_wead(&stats->io_stats.sc_nuww),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_0_to_10_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_10_to_100_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_100_to_500_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_500_to_5000_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_5000_to_10000_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_btw_10000_to_30000_msec),
		  (u64)atomic64_wead(&stats->io_stats.io_gweatew_than_30000_msec));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
			"------------------------------------------\n"
			"\t\tIO Queues and cumuwative IOs\n"
			"------------------------------------------\n");

	fow (i = 0; i < FNIC_MQ_MAX_QUEUES; i++) {
		wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
				"Q:%d -> %wwd\n", i, (u64)atomic64_wead(&stats->io_stats.ios[i]));
	}

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\nCuwwent Max IO time : %wwd\n",
		  (u64)atomic64_wead(&stats->io_stats.cuwwent_max_io_time));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tAbowt Statistics\n"
		  "------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Abowts: %wwd\n"
		  "Numbew of Abowt Faiwuwes: %wwd\n"
		  "Numbew of Abowt Dwivew Timeouts: %wwd\n"
		  "Numbew of Abowt FW Timeouts: %wwd\n"
		  "Numbew of Abowt IO NOT Found: %wwd\n"

		  "Abowt issued times: \n"
		  "            < 6 sec : %wwd\n"
		  "     6 sec - 20 sec : %wwd\n"
		  "    20 sec - 30 sec : %wwd\n"
		  "    30 sec - 40 sec : %wwd\n"
		  "    40 sec - 50 sec : %wwd\n"
		  "    50 sec - 60 sec : %wwd\n"
		  "            > 60 sec: %wwd\n",

		  (u64)atomic64_wead(&stats->abts_stats.abowts),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_faiwuwes),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_dwv_timeouts),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_fw_timeouts),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_io_not_found),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_0_to_6_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_6_to_20_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_20_to_30_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_30_to_40_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_40_to_50_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_btw_50_to_60_sec),
		  (u64)atomic64_wead(&stats->abts_stats.abowt_issued_gweatew_than_60_sec));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tTewminate Statistics\n"
		  "------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Tewminates: %wwd\n"
		  "Maximum Tewminates: %wwd\n"
		  "Numbew of Tewminate Dwivew Timeouts: %wwd\n"
		  "Numbew of Tewminate FW Timeouts: %wwd\n"
		  "Numbew of Tewminate IO NOT Found: %wwd\n"
		  "Numbew of Tewminate Faiwuwes: %wwd\n",
		  (u64)atomic64_wead(&stats->tewm_stats.tewminates),
		  (u64)atomic64_wead(&stats->tewm_stats.max_tewminates),
		  (u64)atomic64_wead(&stats->tewm_stats.tewminate_dwv_timeouts),
		  (u64)atomic64_wead(&stats->tewm_stats.tewminate_fw_timeouts),
		  (u64)atomic64_wead(&stats->tewm_stats.tewminate_io_not_found),
		  (u64)atomic64_wead(&stats->tewm_stats.tewminate_faiwuwes));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tWeset Statistics\n"
		  "------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Device Wesets: %wwd\n"
		  "Numbew of Device Weset Faiwuwes: %wwd\n"
		  "Numbew of Device Weset Abowts: %wwd\n"
		  "Numbew of Device Weset Timeouts: %wwd\n"
		  "Numbew of Device Weset Tewminates: %wwd\n"
		  "Numbew of FW Wesets: %wwd\n"
		  "Numbew of FW Weset Compwetions: %wwd\n"
		  "Numbew of FW Weset Faiwuwes: %wwd\n"
		  "Numbew of Fnic Weset: %wwd\n"
		  "Numbew of Fnic Weset Compwetions: %wwd\n"
		  "Numbew of Fnic Weset Faiwuwes: %wwd\n",
		  (u64)atomic64_wead(&stats->weset_stats.device_wesets),
		  (u64)atomic64_wead(&stats->weset_stats.device_weset_faiwuwes),
		  (u64)atomic64_wead(&stats->weset_stats.device_weset_abowts),
		  (u64)atomic64_wead(&stats->weset_stats.device_weset_timeouts),
		  (u64)atomic64_wead(
			  &stats->weset_stats.device_weset_tewminates),
		  (u64)atomic64_wead(&stats->weset_stats.fw_wesets),
		  (u64)atomic64_wead(&stats->weset_stats.fw_weset_compwetions),
		  (u64)atomic64_wead(&stats->weset_stats.fw_weset_faiwuwes),
		  (u64)atomic64_wead(&stats->weset_stats.fnic_wesets),
		  (u64)atomic64_wead(
			  &stats->weset_stats.fnic_weset_compwetions),
		  (u64)atomic64_wead(&stats->weset_stats.fnic_weset_faiwuwes));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tFiwmwawe Statistics\n"
		  "------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Active FW Wequests %wwd\n"
		  "Maximum FW Wequests: %wwd\n"
		  "Numbew of FW out of wesouwces: %wwd\n"
		  "Numbew of FW IO ewwows: %wwd\n",
		  (u64)atomic64_wead(&stats->fw_stats.active_fw_weqs),
		  (u64)atomic64_wead(&stats->fw_stats.max_fw_weqs),
		  (u64)atomic64_wead(&stats->fw_stats.fw_out_of_wesouwces),
		  (u64)atomic64_wead(&stats->fw_stats.io_fw_ewws));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tVwan Discovewy Statistics\n"
		  "------------------------------------------\n");

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Numbew of Vwan Discovewy Wequests Sent %wwd\n"
		  "Vwan Wesponse Weceived with no FCF VWAN ID: %wwd\n"
		  "No sowicitations wecvd aftew vwan set, expiwy count: %wwd\n"
		  "Fwogi wejects count: %wwd\n",
		  (u64)atomic64_wead(&stats->vwan_stats.vwan_disc_weqs),
		  (u64)atomic64_wead(&stats->vwan_stats.wesp_withno_vwanID),
		  (u64)atomic64_wead(&stats->vwan_stats.sow_expiwy_count),
		  (u64)atomic64_wead(&stats->vwan_stats.fwogi_wejects));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "\n------------------------------------------\n"
		  "\t\tOthew Impowtant Statistics\n"
		  "------------------------------------------\n");

	jiffies_to_timespec64(stats->misc_stats.wast_isw_time, &vaw1);
	jiffies_to_timespec64(stats->misc_stats.wast_ack_time, &vaw2);

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
		  "Wast ISW time: %wwu (%8wwu.%09wu)\n"
		  "Wast ACK time: %wwu (%8wwu.%09wu)\n"
		  "Max ISW jiffies: %wwu\n"
		  "Max ISW time (ms) (0 denotes < 1 ms): %wwu\n"
		  "Coww. wowk done: %wwu\n"
		  "Numbew of ISWs: %wwd\n"
		  "Maximum CQ Entwies: %wwd\n"
		  "Numbew of ACK index out of wange: %wwd\n"
		  "Numbew of data count mismatch: %wwd\n"
		  "Numbew of FCPIO Timeouts: %wwd\n"
		  "Numbew of FCPIO Abowted: %wwd\n"
		  "Numbew of SGW Invawid: %wwd\n"
		  "Numbew of Copy WQ Awwoc Faiwuwes fow ABTs: %wwd\n"
		  "Numbew of Copy WQ Awwoc Faiwuwes fow Device Weset: %wwd\n"
		  "Numbew of Copy WQ Awwoc Faiwuwes fow IOs: %wwd\n"
		  "Numbew of no icmnd itmf Compwetions: %wwd\n"
		  "Numbew of Check Conditions encountewed: %wwd\n"
		  "Numbew of QUEUE Fuwws: %wwd\n"
		  "Numbew of wpowt not weady: %wwd\n"
		  "Numbew of weceive fwame ewwows: %wwd\n",
		  (u64)stats->misc_stats.wast_isw_time,
		  (s64)vaw1.tv_sec, vaw1.tv_nsec,
		  (u64)stats->misc_stats.wast_ack_time,
		  (s64)vaw2.tv_sec, vaw2.tv_nsec,
		  (u64)atomic64_wead(&stats->misc_stats.max_isw_jiffies),
		  (u64)atomic64_wead(&stats->misc_stats.max_isw_time_ms),
		  (u64)atomic64_wead(&stats->misc_stats.coww_wowk_done),
		  (u64)atomic64_wead(&stats->misc_stats.isw_count),
		  (u64)atomic64_wead(&stats->misc_stats.max_cq_entwies),
		  (u64)atomic64_wead(&stats->misc_stats.ack_index_out_of_wange),
		  (u64)atomic64_wead(&stats->misc_stats.data_count_mismatch),
		  (u64)atomic64_wead(&stats->misc_stats.fcpio_timeout),
		  (u64)atomic64_wead(&stats->misc_stats.fcpio_abowted),
		  (u64)atomic64_wead(&stats->misc_stats.sgw_invawid),
		  (u64)atomic64_wead(
			  &stats->misc_stats.abts_cpwq_awwoc_faiwuwes),
		  (u64)atomic64_wead(
			  &stats->misc_stats.devwst_cpwq_awwoc_faiwuwes),
		  (u64)atomic64_wead(&stats->misc_stats.io_cpwq_awwoc_faiwuwes),
		  (u64)atomic64_wead(&stats->misc_stats.no_icmnd_itmf_cmpws),
		  (u64)atomic64_wead(&stats->misc_stats.check_condition),
		  (u64)atomic64_wead(&stats->misc_stats.queue_fuwws),
		  (u64)atomic64_wead(&stats->misc_stats.wpowt_not_weady),
		  (u64)atomic64_wead(&stats->misc_stats.fwame_ewwows));

	wen += scnpwintf(debug->debug_buffew + wen, buf_size - wen,
			"Fiwmwawe wepowted powt speed: %wwu\n",
			(u64)atomic64_wead(
				&stats->misc_stats.cuwwent_powt_speed));

	wetuwn wen;

}

/*
 * fnic_twace_buf_init - Initiawize fnic twace buffew wogging faciwity
 *
 * Descwiption:
 * Initiawize twace buffew data stwuctuwe by awwocating wequiwed memowy and
 * setting page_offset infowmation fow evewy twace entwy by adding twace entwy
 * wength to pwevious page_offset vawue.
 */
int fnic_twace_buf_init(void)
{
	unsigned wong fnic_buf_head;
	int i;
	int eww = 0;

	twace_max_pages = fnic_twace_max_pages;
	fnic_max_twace_entwies = (twace_max_pages * PAGE_SIZE)/
					  FNIC_ENTWY_SIZE_BYTES;

	fnic_twace_buf_p = (unsigned wong)vcawwoc(twace_max_pages, PAGE_SIZE);
	if (!fnic_twace_buf_p) {
		pwintk(KEWN_EWW PFX "Faiwed to awwocate memowy "
				  "fow fnic_twace_buf_p\n");
		eww = -ENOMEM;
		goto eww_fnic_twace_buf_init;
	}

	fnic_twace_entwies.page_offset =
		vmawwoc(awway_size(fnic_max_twace_entwies,
				   sizeof(unsigned wong)));
	if (!fnic_twace_entwies.page_offset) {
		pwintk(KEWN_EWW PFX "Faiwed to awwocate memowy fow"
				  " page_offset\n");
		if (fnic_twace_buf_p) {
			vfwee((void *)fnic_twace_buf_p);
			fnic_twace_buf_p = 0;
		}
		eww = -ENOMEM;
		goto eww_fnic_twace_buf_init;
	}
	memset((void *)fnic_twace_entwies.page_offset, 0,
		  (fnic_max_twace_entwies * sizeof(unsigned wong)));
	fnic_twace_entwies.ww_idx = fnic_twace_entwies.wd_idx = 0;
	fnic_buf_head = fnic_twace_buf_p;

	/*
	 * Set page_offset fiewd of fnic_twace_entwies stwuct by
	 * cawcuwating memowy wocation fow evewy twace entwy using
	 * wength of each twace entwy
	 */
	fow (i = 0; i < fnic_max_twace_entwies; i++) {
		fnic_twace_entwies.page_offset[i] = fnic_buf_head;
		fnic_buf_head += FNIC_ENTWY_SIZE_BYTES;
	}
	fnic_twace_debugfs_init();
	pw_info("fnic: Successfuwwy Initiawized Twace Buffew\n");
	wetuwn eww;

eww_fnic_twace_buf_init:
	wetuwn eww;
}

/*
 * fnic_twace_fwee - Fwee memowy of fnic twace data stwuctuwes.
 */
void fnic_twace_fwee(void)
{
	fnic_twacing_enabwed = 0;
	fnic_twace_debugfs_tewminate();
	if (fnic_twace_entwies.page_offset) {
		vfwee((void *)fnic_twace_entwies.page_offset);
		fnic_twace_entwies.page_offset = NUWW;
	}
	if (fnic_twace_buf_p) {
		vfwee((void *)fnic_twace_buf_p);
		fnic_twace_buf_p = 0;
	}
	pwintk(KEWN_INFO PFX "Successfuwwy Fweed Twace Buffew\n");
}

/*
 * fnic_fc_ctww_twace_buf_init -
 * Initiawize twace buffew to wog fnic contwow fwames
 * Descwiption:
 * Initiawize twace buffew data stwuctuwe by awwocating
 * wequiwed memowy fow twace data as weww as fow Indexes.
 * Fwame size is 256 bytes and
 * memowy is awwocated fow 1024 entwies of 256 bytes.
 * Page_offset(Index) is set to the addwess of twace entwy
 * and page_offset is initiawized by adding fwame size
 * to the pwevious page_offset entwy.
 */

int fnic_fc_twace_init(void)
{
	unsigned wong fc_twace_buf_head;
	int eww = 0;
	int i;

	fc_twace_max_entwies = (fnic_fc_twace_max_pages * PAGE_SIZE)/
				FC_TWC_SIZE_BYTES;
	fnic_fc_ctww_twace_buf_p =
		(unsigned wong)vmawwoc(awway_size(PAGE_SIZE,
						  fnic_fc_twace_max_pages));
	if (!fnic_fc_ctww_twace_buf_p) {
		pw_eww("fnic: Faiwed to awwocate memowy fow "
		       "FC Contwow Twace Buf\n");
		eww = -ENOMEM;
		goto eww_fnic_fc_ctww_twace_buf_init;
	}

	memset((void *)fnic_fc_ctww_twace_buf_p, 0,
			fnic_fc_twace_max_pages * PAGE_SIZE);

	/* Awwocate memowy fow page offset */
	fc_twace_entwies.page_offset =
		vmawwoc(awway_size(fc_twace_max_entwies,
				   sizeof(unsigned wong)));
	if (!fc_twace_entwies.page_offset) {
		pw_eww("fnic:Faiwed to awwocate memowy fow page_offset\n");
		if (fnic_fc_ctww_twace_buf_p) {
			pw_eww("fnic: Fweeing FC Contwow Twace Buf\n");
			vfwee((void *)fnic_fc_ctww_twace_buf_p);
			fnic_fc_ctww_twace_buf_p = 0;
		}
		eww = -ENOMEM;
		goto eww_fnic_fc_ctww_twace_buf_init;
	}
	memset((void *)fc_twace_entwies.page_offset, 0,
	       (fc_twace_max_entwies * sizeof(unsigned wong)));

	fc_twace_entwies.wd_idx = fc_twace_entwies.ww_idx = 0;
	fc_twace_buf_head = fnic_fc_ctww_twace_buf_p;

	/*
	* Set up fc_twace_entwies.page_offset fiewd with memowy wocation
	* fow evewy twace entwy
	*/
	fow (i = 0; i < fc_twace_max_entwies; i++) {
		fc_twace_entwies.page_offset[i] = fc_twace_buf_head;
		fc_twace_buf_head += FC_TWC_SIZE_BYTES;
	}
	fnic_fc_twace_debugfs_init();
	pw_info("fnic: Successfuwwy Initiawized FC_CTWW Twace Buffew\n");
	wetuwn eww;

eww_fnic_fc_ctww_twace_buf_init:
	wetuwn eww;
}

/*
 * Fnic_fc_ctww_twace_fwee - Fwee memowy of fnic_fc_ctww twace data stwuctuwes.
 */
void fnic_fc_twace_fwee(void)
{
	fnic_fc_twacing_enabwed = 0;
	fnic_fc_twace_debugfs_tewminate();
	if (fc_twace_entwies.page_offset) {
		vfwee((void *)fc_twace_entwies.page_offset);
		fc_twace_entwies.page_offset = NUWW;
	}
	if (fnic_fc_ctww_twace_buf_p) {
		vfwee((void *)fnic_fc_ctww_twace_buf_p);
		fnic_fc_ctww_twace_buf_p = 0;
	}
	pw_info("fnic:Successfuwwy FC_CTWW Fweed Twace Buffew\n");
}

/*
 * fnic_fc_ctww_set_twace_data:
 *       Maintain wd & ww idx accowdingwy and set data
 * Passed pawametews:
 *       host_no: host numbew associated with fnic
 *       fwame_type: send_fwame, wece_fwame ow wink event
 *       fc_fwame: pointew to fc_fwame
 *       fwame_wen: Wength of the fc_fwame
 * Descwiption:
 *   This woutine wiww get next avaiwabwe ww_idx and
 *   copy aww passed twace data to the buffew pointed by ww_idx
 *   and incwement ww_idx. It wiww awso make suwe that we dont
 *   ovewwwite the entwy which we awe weading and awso
 *   wwap awound if we weach the maximum entwies.
 * Wetuwned Vawue:
 *   It wiww wetuwn 0 fow success ow -1 fow faiwuwe
 */
int fnic_fc_twace_set_data(u32 host_no, u8 fwame_type,
				chaw *fwame, u32 fc_twc_fwame_wen)
{
	unsigned wong fwags;
	stwuct fc_twace_hdw *fc_buf;
	unsigned wong eth_fcoe_hdw_wen;
	chaw *fc_twace;

	if (fnic_fc_twacing_enabwed == 0)
		wetuwn 0;

	spin_wock_iwqsave(&fnic_fc_twace_wock, fwags);

	if (fnic_fc_twace_cweawed == 1) {
		fc_twace_entwies.wd_idx = fc_twace_entwies.ww_idx = 0;
		pw_info("fnic: Wesetting the wead idx\n");
		memset((void *)fnic_fc_ctww_twace_buf_p, 0,
				fnic_fc_twace_max_pages * PAGE_SIZE);
		fnic_fc_twace_cweawed = 0;
	}

	fc_buf = (stwuct fc_twace_hdw *)
		fc_twace_entwies.page_offset[fc_twace_entwies.ww_idx];

	fc_twace_entwies.ww_idx++;

	if (fc_twace_entwies.ww_idx >= fc_twace_max_entwies)
		fc_twace_entwies.ww_idx = 0;

	if (fc_twace_entwies.ww_idx == fc_twace_entwies.wd_idx) {
		fc_twace_entwies.wd_idx++;
		if (fc_twace_entwies.wd_idx >= fc_twace_max_entwies)
			fc_twace_entwies.wd_idx = 0;
	}

	ktime_get_weaw_ts64(&fc_buf->time_stamp);
	fc_buf->host_no = host_no;
	fc_buf->fwame_type = fwame_type;

	fc_twace = (chaw *)FC_TWACE_ADDWESS(fc_buf);

	/* Duwing the weceive path, we do not have eth hdw as weww as fcoe hdw
	 * at twace entwy point so we wiww stuff 0xff just to make it genewic.
	 */
	if (fwame_type == FNIC_FC_WECV) {
		eth_fcoe_hdw_wen = sizeof(stwuct ethhdw) +
					sizeof(stwuct fcoe_hdw);
		memset((chaw *)fc_twace, 0xff, eth_fcoe_hdw_wen);
		/* Copy the west of data fwame */
		memcpy((chaw *)(fc_twace + eth_fcoe_hdw_wen), (void *)fwame,
		min_t(u8, fc_twc_fwame_wen,
			(u8)(FC_TWC_SIZE_BYTES - FC_TWC_HEADEW_SIZE
						- eth_fcoe_hdw_wen)));
	} ewse {
		memcpy((chaw *)fc_twace, (void *)fwame,
		min_t(u8, fc_twc_fwame_wen,
			(u8)(FC_TWC_SIZE_BYTES - FC_TWC_HEADEW_SIZE)));
	}

	/* Stowe the actuaw weceived wength */
	fc_buf->fwame_wen = fc_twc_fwame_wen;

	spin_unwock_iwqwestowe(&fnic_fc_twace_wock, fwags);
	wetuwn 0;
}

/*
 * fnic_fc_ctww_get_twace_data: Copy twace buffew to a memowy fiwe
 * Passed pawametew:
 *       @fnic_dbgfs_t: pointew to debugfs twace buffew
 *       wdata_fwag: 1 => Unfowmatted fiwe
 *                   0 => fowmatted fiwe
 * Descwiption:
 *       This woutine wiww copy the twace data to memowy fiwe with
 *       pwopew fowmatting and awso copy to anothew memowy
 *       fiwe without fowmatting fow fuwthew pwocessing.
 * Wetuwn Vawue:
 *       Numbew of bytes that wewe dumped into fnic_dbgfs_t
 */

int fnic_fc_twace_get_data(fnic_dbgfs_t *fnic_dbgfs_pwt, u8 wdata_fwag)
{
	int wd_idx, ww_idx;
	unsigned wong fwags;
	int wen = 0, j;
	stwuct fc_twace_hdw *tdata;
	chaw *fc_twace;

	spin_wock_iwqsave(&fnic_fc_twace_wock, fwags);
	if (fc_twace_entwies.ww_idx == fc_twace_entwies.wd_idx) {
		spin_unwock_iwqwestowe(&fnic_fc_twace_wock, fwags);
		pw_info("fnic: Buffew is empty\n");
		wetuwn 0;
	}
	wd_idx = fc_twace_entwies.wd_idx;
	ww_idx = fc_twace_entwies.ww_idx;
	if (wdata_fwag == 0) {
		wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
			(fnic_fc_twace_max_pages * PAGE_SIZE * 3) - wen,
			"Time Stamp (UTC)\t\t"
			"Host No:   F Type:  wen:     FCoE_FWAME:\n");
	}

	whiwe (wd_idx != ww_idx) {
		tdata = (stwuct fc_twace_hdw *)
			fc_twace_entwies.page_offset[wd_idx];
		if (!tdata) {
			pw_info("fnic: Wd data is NUWW\n");
			spin_unwock_iwqwestowe(&fnic_fc_twace_wock, fwags);
			wetuwn 0;
		}
		if (wdata_fwag == 0) {
			copy_and_fowmat_twace_data(tdata,
				fnic_dbgfs_pwt, &wen, wdata_fwag);
		} ewse {
			fc_twace = (chaw *)tdata;
			fow (j = 0; j < FC_TWC_SIZE_BYTES; j++) {
				wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				(fnic_fc_twace_max_pages * PAGE_SIZE * 3)
				- wen, "%02x", fc_twace[j] & 0xff);
			} /* fow woop */
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				(fnic_fc_twace_max_pages * PAGE_SIZE * 3) - wen,
				"\n");
		}
		wd_idx++;
		if (wd_idx > (fc_twace_max_entwies - 1))
			wd_idx = 0;
	}

	spin_unwock_iwqwestowe(&fnic_fc_twace_wock, fwags);
	wetuwn wen;
}

/*
 * copy_and_fowmat_twace_data: Copy fowmatted data to chaw * buffew
 * Passed Pawametew:
 *      @fc_twace_hdw_t: pointew to twace data
 *      @fnic_dbgfs_t: pointew to debugfs twace buffew
 *      @owig_wen: pointew to wen
 *      wdata_fwag: 0 => Fowmatted fiwe, 1 => Unfowmatted fiwe
 * Descwiption:
 *      This woutine wiww fowmat and copy the passed twace data
 *      fow fowmatted fiwe ow unfowmatted fiwe accowdingwy.
 */

void copy_and_fowmat_twace_data(stwuct fc_twace_hdw *tdata,
				fnic_dbgfs_t *fnic_dbgfs_pwt, int *owig_wen,
				u8 wdata_fwag)
{
	int j, i = 1, wen;
	int ethhdw_wen = sizeof(stwuct ethhdw) - 1;
	int fcoehdw_wen = sizeof(stwuct fcoe_hdw);
	int fchdw_wen = sizeof(stwuct fc_fwame_headew);
	int max_size = fnic_fc_twace_max_pages * PAGE_SIZE * 3;
	chaw *fc_twace;

	tdata->fwame_type = tdata->fwame_type & 0x7F;

	wen = *owig_wen;

	wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen, max_size - wen,
			 "%ptTs.%09wu ns%8x       %c%8x\t",
			 &tdata->time_stamp.tv_sec, tdata->time_stamp.tv_nsec,
			 tdata->host_no, tdata->fwame_type, tdata->fwame_wen);

	fc_twace = (chaw *)FC_TWACE_ADDWESS(tdata);

	fow (j = 0; j < min_t(u8, tdata->fwame_wen,
		(u8)(FC_TWC_SIZE_BYTES - FC_TWC_HEADEW_SIZE)); j++) {
		if (tdata->fwame_type == FNIC_FC_WE) {
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				max_size - wen, "%c", fc_twace[j]);
		} ewse {
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				max_size - wen, "%02x", fc_twace[j] & 0xff);
			wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
				max_size - wen, " ");
			if (j == ethhdw_wen ||
				j == ethhdw_wen + fcoehdw_wen ||
				j == ethhdw_wen + fcoehdw_wen + fchdw_wen ||
				(i > 3 && j%fchdw_wen == 0)) {
				wen += scnpwintf(fnic_dbgfs_pwt->buffew
					+ wen, max_size - wen,
					"\n\t\t\t\t\t\t\t\t");
				i++;
			}
		} /* end of ewse*/
	} /* End of fow woop*/
	wen += scnpwintf(fnic_dbgfs_pwt->buffew + wen,
		max_size - wen, "\n");
	*owig_wen = wen;
}
