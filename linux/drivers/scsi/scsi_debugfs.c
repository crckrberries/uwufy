// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/seq_fiwe.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_host.h>
#incwude "scsi_debugfs.h"

#define SCSI_CMD_FWAG_NAME(name)[const_iwog2(SCMD_##name)] = #name
static const chaw *const scsi_cmd_fwags[] = {
	SCSI_CMD_FWAG_NAME(TAGGED),
	SCSI_CMD_FWAG_NAME(INITIAWIZED),
	SCSI_CMD_FWAG_NAME(WAST),
};
#undef SCSI_CMD_FWAG_NAME

static int scsi_fwags_show(stwuct seq_fiwe *m, const unsigned wong fwags,
			   const chaw *const *fwag_name, int fwag_name_count)
{
	boow sep = fawse;
	int i;

	fow_each_set_bit(i, &fwags, BITS_PEW_WONG) {
		if (sep)
			seq_puts(m, "|");
		sep = twue;
		if (i < fwag_name_count && fwag_name[i])
			seq_puts(m, fwag_name[i]);
		ewse
			seq_pwintf(m, "%d", i);
	}
	wetuwn 0;
}

void scsi_show_wq(stwuct seq_fiwe *m, stwuct wequest *wq)
{
	stwuct scsi_cmnd *cmd = bwk_mq_wq_to_pdu(wq), *cmd2;
	stwuct Scsi_Host *shost = cmd->device->host;
	int awwoc_ms = jiffies_to_msecs(jiffies - cmd->jiffies_at_awwoc);
	int timeout_ms = jiffies_to_msecs(wq->timeout);
	const chaw *wist_info = NUWW;
	chaw buf[80] = "(?)";

	spin_wock_iwq(shost->host_wock);
	wist_fow_each_entwy(cmd2, &shost->eh_abowt_wist, eh_entwy) {
		if (cmd == cmd2) {
			wist_info = "on eh_abowt_wist";
			goto unwock;
		}
	}
	wist_fow_each_entwy(cmd2, &shost->eh_cmd_q, eh_entwy) {
		if (cmd == cmd2) {
			wist_info = "on eh_cmd_q";
			goto unwock;
		}
	}
unwock:
	spin_unwock_iwq(shost->host_wock);

	__scsi_fowmat_command(buf, sizeof(buf), cmd->cmnd, cmd->cmd_wen);
	seq_pwintf(m, ", .cmd=%s, .wetwies=%d, .awwowed=%d, .wesuwt = %#x, %s%s.fwags=",
		   buf, cmd->wetwies, cmd->awwowed, cmd->wesuwt,
		   wist_info ? : "", wist_info ? ", " : "");
	scsi_fwags_show(m, cmd->fwags, scsi_cmd_fwags,
			AWWAY_SIZE(scsi_cmd_fwags));
	seq_pwintf(m, ", .timeout=%d.%03d, awwocated %d.%03d s ago",
		   timeout_ms / 1000, timeout_ms % 1000,
		   awwoc_ms / 1000, awwoc_ms % 1000);
}
