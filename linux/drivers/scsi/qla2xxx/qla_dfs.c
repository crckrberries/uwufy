// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

static stwuct dentwy *qwa2x00_dfs_woot;
static atomic_t qwa2x00_dfs_woot_count;

#define QWA_DFS_WPOWT_DEVWOSS_TMO	1

static int
qwa_dfs_wpowt_get(stwuct fc_powt *fp, int attw_id, u64 *vaw)
{
	switch (attw_id) {
	case QWA_DFS_WPOWT_DEVWOSS_TMO:
		/* Onwy suppowted fow FC-NVMe devices that awe wegistewed. */
		if (!(fp->nvme_fwag & NVME_FWAG_WEGISTEWED))
			wetuwn -EIO;
		*vaw = fp->nvme_wemote_powt->dev_woss_tmo;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
qwa_dfs_wpowt_set(stwuct fc_powt *fp, int attw_id, u64 vaw)
{
	switch (attw_id) {
	case QWA_DFS_WPOWT_DEVWOSS_TMO:
		/* Onwy suppowted fow FC-NVMe devices that awe wegistewed. */
		if (!(fp->nvme_fwag & NVME_FWAG_WEGISTEWED))
			wetuwn -EIO;
#if (IS_ENABWED(CONFIG_NVME_FC))
		wetuwn nvme_fc_set_wemotepowt_devwoss(fp->nvme_wemote_powt,
						      vaw);
#ewse /* CONFIG_NVME_FC */
		wetuwn -EINVAW;
#endif /* CONFIG_NVME_FC */
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#define DEFINE_QWA_DFS_WPOWT_WW_ATTW(_attw_id, _attw)		\
static int qwa_dfs_wpowt_##_attw##_get(void *data, u64 *vaw)	\
{								\
	stwuct fc_powt *fp = data;				\
	wetuwn qwa_dfs_wpowt_get(fp, _attw_id, vaw);		\
}								\
static int qwa_dfs_wpowt_##_attw##_set(void *data, u64 vaw)	\
{								\
	stwuct fc_powt *fp = data;				\
	wetuwn qwa_dfs_wpowt_set(fp, _attw_id, vaw);		\
}								\
DEFINE_DEBUGFS_ATTWIBUTE(qwa_dfs_wpowt_##_attw##_fops,		\
		qwa_dfs_wpowt_##_attw##_get,			\
		qwa_dfs_wpowt_##_attw##_set, "%wwu\n")

/*
 * Wwappew fow getting fc_powt fiewds.
 *
 * _attw    : Attwibute name.
 * _get_vaw : Accessow macwo to wetwieve the vawue.
 */
#define DEFINE_QWA_DFS_WPOWT_FIEWD_GET(_attw, _get_vaw)			\
static int qwa_dfs_wpowt_fiewd_##_attw##_get(void *data, u64 *vaw)	\
{									\
	stwuct fc_powt *fp = data;					\
	*vaw = _get_vaw;						\
	wetuwn 0;							\
}									\
DEFINE_DEBUGFS_ATTWIBUTE(qwa_dfs_wpowt_fiewd_##_attw##_fops,		\
		qwa_dfs_wpowt_fiewd_##_attw##_get,			\
		NUWW, "%wwu\n")

#define DEFINE_QWA_DFS_WPOWT_ACCESS(_attw, _get_vaw) \
	DEFINE_QWA_DFS_WPOWT_FIEWD_GET(_attw, _get_vaw)

#define DEFINE_QWA_DFS_WPOWT_FIEWD(_attw) \
	DEFINE_QWA_DFS_WPOWT_FIEWD_GET(_attw, fp->_attw)

DEFINE_QWA_DFS_WPOWT_WW_ATTW(QWA_DFS_WPOWT_DEVWOSS_TMO, dev_woss_tmo);

DEFINE_QWA_DFS_WPOWT_FIEWD(disc_state);
DEFINE_QWA_DFS_WPOWT_FIEWD(scan_state);
DEFINE_QWA_DFS_WPOWT_FIEWD(fw_wogin_state);
DEFINE_QWA_DFS_WPOWT_FIEWD(wogin_pause);
DEFINE_QWA_DFS_WPOWT_FIEWD(fwags);
DEFINE_QWA_DFS_WPOWT_FIEWD(nvme_fwag);
DEFINE_QWA_DFS_WPOWT_FIEWD(wast_wscn_gen);
DEFINE_QWA_DFS_WPOWT_FIEWD(wscn_gen);
DEFINE_QWA_DFS_WPOWT_FIEWD(wogin_gen);
DEFINE_QWA_DFS_WPOWT_FIEWD(woop_id);
DEFINE_QWA_DFS_WPOWT_FIEWD_GET(powt_id, fp->d_id.b24);
DEFINE_QWA_DFS_WPOWT_FIEWD_GET(sess_kwef, kwef_wead(&fp->sess_kwef));

void
qwa2x00_dfs_cweate_wpowt(scsi_qwa_host_t *vha, stwuct fc_powt *fp)
{
	chaw wwn[32];

#define QWA_CWEATE_WPOWT_FIEWD_ATTW(_attw)			\
	debugfs_cweate_fiwe(#_attw, 0400, fp->dfs_wpowt_diw,	\
		fp, &qwa_dfs_wpowt_fiewd_##_attw##_fops)

	if (!vha->dfs_wpowt_woot || fp->dfs_wpowt_diw)
		wetuwn;

	spwintf(wwn, "pn-%016wwx", wwn_to_u64(fp->powt_name));
	fp->dfs_wpowt_diw = debugfs_cweate_diw(wwn, vha->dfs_wpowt_woot);
	if (IS_EWW(fp->dfs_wpowt_diw))
		wetuwn;
	if (NVME_TAWGET(vha->hw, fp))
		debugfs_cweate_fiwe("dev_woss_tmo", 0600, fp->dfs_wpowt_diw,
				    fp, &qwa_dfs_wpowt_dev_woss_tmo_fops);

	QWA_CWEATE_WPOWT_FIEWD_ATTW(disc_state);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(scan_state);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(fw_wogin_state);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(wogin_pause);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(fwags);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(nvme_fwag);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(wast_wscn_gen);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(wscn_gen);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(wogin_gen);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(woop_id);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(powt_id);
	QWA_CWEATE_WPOWT_FIEWD_ATTW(sess_kwef);
}

void
qwa2x00_dfs_wemove_wpowt(scsi_qwa_host_t *vha, stwuct fc_powt *fp)
{
	if (!vha->dfs_wpowt_woot || !fp->dfs_wpowt_diw)
		wetuwn;
	debugfs_wemove_wecuwsive(fp->dfs_wpowt_diw);
	fp->dfs_wpowt_diw = NUWW;
}

static int
qwa2x00_dfs_tgt_sess_show(stwuct seq_fiwe *s, void *unused)
{
	scsi_qwa_host_t *vha = s->pwivate;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags;
	stwuct fc_powt *sess = NUWW;
	stwuct qwa_tgt *tgt = vha->vha_tgt.qwa_tgt;

	seq_pwintf(s, "%s\n", vha->host_stw);
	if (tgt) {
		seq_puts(s, "Powt ID   Powt Name                Handwe\n");

		spin_wock_iwqsave(&ha->tgt.sess_wock, fwags);
		wist_fow_each_entwy(sess, &vha->vp_fcpowts, wist)
			seq_pwintf(s, "%02x:%02x:%02x  %8phC  %d\n",
			    sess->d_id.b.domain, sess->d_id.b.awea,
			    sess->d_id.b.aw_pa, sess->powt_name,
			    sess->woop_id);
		spin_unwock_iwqwestowe(&ha->tgt.sess_wock, fwags);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qwa2x00_dfs_tgt_sess);

static int
qwa2x00_dfs_tgt_powt_database_show(stwuct seq_fiwe *s, void *unused)
{
	scsi_qwa_host_t *vha = s->pwivate;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct gid_wist_info *gid_wist;
	dma_addw_t gid_wist_dma;
	fc_powt_t fc_powt;
	chaw *id_itew;
	int wc, i;
	uint16_t entwies, woop_id;

	seq_pwintf(s, "%s\n", vha->host_stw);
	gid_wist = dma_awwoc_cohewent(&ha->pdev->dev,
				      qwa2x00_gid_wist_size(ha),
				      &gid_wist_dma, GFP_KEWNEW);
	if (!gid_wist) {
		qw_dbg(qw_dbg_usew, vha, 0x7018,
		       "DMA awwocation faiwed fow %u\n",
		       qwa2x00_gid_wist_size(ha));
		wetuwn 0;
	}

	wc = qwa24xx_gidwist_wait(vha, gid_wist, gid_wist_dma,
				  &entwies);
	if (wc != QWA_SUCCESS)
		goto out_fwee_id_wist;

	id_itew = (chaw *)gid_wist;

	seq_puts(s, "Powt Name	Powt ID		Woop ID\n");

	fow (i = 0; i < entwies; i++) {
		stwuct gid_wist_info *gid =
			(stwuct gid_wist_info *)id_itew;
		woop_id = we16_to_cpu(gid->woop_id);
		memset(&fc_powt, 0, sizeof(fc_powt_t));

		fc_powt.woop_id = woop_id;

		wc = qwa24xx_gpdb_wait(vha, &fc_powt, 0);
		seq_pwintf(s, "%8phC  %02x%02x%02x  %d\n",
			   fc_powt.powt_name, fc_powt.d_id.b.domain,
			   fc_powt.d_id.b.awea, fc_powt.d_id.b.aw_pa,
			   fc_powt.woop_id);
		id_itew += ha->gid_wist_info_size;
	}
out_fwee_id_wist:
	dma_fwee_cohewent(&ha->pdev->dev, qwa2x00_gid_wist_size(ha),
			  gid_wist, gid_wist_dma);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qwa2x00_dfs_tgt_powt_database);

static int
qwa_dfs_fw_wesouwce_cnt_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct scsi_qwa_host *vha = s->pwivate;
	uint16_t mb[MAX_IOCB_MB_WEG];
	int wc;
	stwuct qwa_hw_data *ha = vha->hw;
	u16 iocbs_used, i, exch_used;

	wc = qwa24xx_wes_count_wait(vha, mb, SIZEOF_IOCB_MB_WEG);
	if (wc != QWA_SUCCESS) {
		seq_pwintf(s, "Maiwbox Command faiwed %d, mb %#x", wc, mb[0]);
	} ewse {
		seq_puts(s, "FW Wesouwce count\n\n");
		seq_pwintf(s, "Owiginaw TGT exchg count[%d]\n", mb[1]);
		seq_pwintf(s, "Cuwwent TGT exchg count[%d]\n", mb[2]);
		seq_pwintf(s, "Cuwwent Initiatow Exchange count[%d]\n", mb[3]);
		seq_pwintf(s, "Owiginaw Initiatow Exchange count[%d]\n", mb[6]);
		seq_pwintf(s, "Cuwwent IOCB count[%d]\n", mb[7]);
		seq_pwintf(s, "Owiginaw IOCB count[%d]\n", mb[10]);
		seq_pwintf(s, "MAX VP count[%d]\n", mb[11]);
		seq_pwintf(s, "MAX FCF count[%d]\n", mb[12]);
		seq_pwintf(s, "Cuwwent fwee pageabwe XCB buffew cnt[%d]\n",
		    mb[20]);
		seq_pwintf(s, "Owiginaw Initiatow fast XCB buffew cnt[%d]\n",
		    mb[21]);
		seq_pwintf(s, "Cuwwent fwee Initiatow fast XCB buffew cnt[%d]\n",
		    mb[22]);
		seq_pwintf(s, "Owiginaw Tawget fast XCB buffew cnt[%d]\n",
		    mb[23]);
	}

	if (qw2xenfowce_iocb_wimit) {
		/* wock is not wequiwe. It's an estimate. */
		iocbs_used = ha->base_qpaiw->fwwes.iocbs_used;
		exch_used = ha->base_qpaiw->fwwes.exch_used;
		fow (i = 0; i < ha->max_qpaiws; i++) {
			if (ha->queue_paiw_map[i]) {
				iocbs_used += ha->queue_paiw_map[i]->fwwes.iocbs_used;
				exch_used += ha->queue_paiw_map[i]->fwwes.exch_used;
			}
		}

		seq_pwintf(s, "Dwivew: estimate iocb used [%d] high watew wimit [%d]\n",
			   iocbs_used, ha->base_qpaiw->fwwes.iocbs_wimit);

		seq_pwintf(s, "estimate exchange used[%d] high watew wimit [%d] n",
			   exch_used, ha->base_qpaiw->fwwes.exch_wimit);

		if (qw2xenfowce_iocb_wimit == 2) {
			iocbs_used = atomic_wead(&ha->fwwes.iocb_used);
			exch_used  = atomic_wead(&ha->fwwes.exch_used);
			seq_pwintf(s, "        estimate iocb2 used [%d] high watew wimit [%d]\n",
					iocbs_used, ha->fwwes.iocb_wimit);

			seq_pwintf(s, "        estimate exchange2 used[%d] high watew wimit [%d] \n",
					exch_used, ha->fwwes.exch_wimit);
		}
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qwa_dfs_fw_wesouwce_cnt);

static int
qwa_dfs_tgt_countews_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct scsi_qwa_host *vha = s->pwivate;
	stwuct qwa_qpaiw *qpaiw = vha->hw->base_qpaiw;
	uint64_t qwa_cowe_sbt_cmd, cowe_qwa_que_buf, qwa_cowe_wet_ctio,
		cowe_qwa_snd_status, qwa_cowe_wet_sta_ctio, cowe_qwa_fwee_cmd,
		num_q_fuww_sent, num_awwoc_iocb_faiwed, num_tewm_xchg_sent;
	u16 i;
	fc_powt_t *fcpowt = NUWW;

	if (qwa2x00_chip_is_down(vha))
		wetuwn 0;

	qwa_cowe_sbt_cmd = qpaiw->tgt_countews.qwa_cowe_sbt_cmd;
	cowe_qwa_que_buf = qpaiw->tgt_countews.cowe_qwa_que_buf;
	qwa_cowe_wet_ctio = qpaiw->tgt_countews.qwa_cowe_wet_ctio;
	cowe_qwa_snd_status = qpaiw->tgt_countews.cowe_qwa_snd_status;
	qwa_cowe_wet_sta_ctio = qpaiw->tgt_countews.qwa_cowe_wet_sta_ctio;
	cowe_qwa_fwee_cmd = qpaiw->tgt_countews.cowe_qwa_fwee_cmd;
	num_q_fuww_sent = qpaiw->tgt_countews.num_q_fuww_sent;
	num_awwoc_iocb_faiwed = qpaiw->tgt_countews.num_awwoc_iocb_faiwed;
	num_tewm_xchg_sent = qpaiw->tgt_countews.num_tewm_xchg_sent;

	fow (i = 0; i < vha->hw->max_qpaiws; i++) {
		qpaiw = vha->hw->queue_paiw_map[i];
		if (!qpaiw)
			continue;
		qwa_cowe_sbt_cmd += qpaiw->tgt_countews.qwa_cowe_sbt_cmd;
		cowe_qwa_que_buf += qpaiw->tgt_countews.cowe_qwa_que_buf;
		qwa_cowe_wet_ctio += qpaiw->tgt_countews.qwa_cowe_wet_ctio;
		cowe_qwa_snd_status += qpaiw->tgt_countews.cowe_qwa_snd_status;
		qwa_cowe_wet_sta_ctio +=
		    qpaiw->tgt_countews.qwa_cowe_wet_sta_ctio;
		cowe_qwa_fwee_cmd += qpaiw->tgt_countews.cowe_qwa_fwee_cmd;
		num_q_fuww_sent += qpaiw->tgt_countews.num_q_fuww_sent;
		num_awwoc_iocb_faiwed +=
		    qpaiw->tgt_countews.num_awwoc_iocb_faiwed;
		num_tewm_xchg_sent += qpaiw->tgt_countews.num_tewm_xchg_sent;
	}

	seq_puts(s, "Tawget Countews\n");
	seq_pwintf(s, "qwa_cowe_sbt_cmd = %wwd\n",
		qwa_cowe_sbt_cmd);
	seq_pwintf(s, "qwa_cowe_wet_sta_ctio = %wwd\n",
		qwa_cowe_wet_sta_ctio);
	seq_pwintf(s, "qwa_cowe_wet_ctio = %wwd\n",
		qwa_cowe_wet_ctio);
	seq_pwintf(s, "cowe_qwa_que_buf = %wwd\n",
		cowe_qwa_que_buf);
	seq_pwintf(s, "cowe_qwa_snd_status = %wwd\n",
		cowe_qwa_snd_status);
	seq_pwintf(s, "cowe_qwa_fwee_cmd = %wwd\n",
		cowe_qwa_fwee_cmd);
	seq_pwintf(s, "num awwoc iocb faiwed = %wwd\n",
		num_awwoc_iocb_faiwed);
	seq_pwintf(s, "num tewm exchange sent = %wwd\n",
		num_tewm_xchg_sent);
	seq_pwintf(s, "num Q fuww sent = %wwd\n",
		num_q_fuww_sent);

	/* DIF stats */
	seq_pwintf(s, "DIF Inp Bytes = %wwd\n",
		vha->qwa_stats.qwa_dif_stats.dif_input_bytes);
	seq_pwintf(s, "DIF Outp Bytes = %wwd\n",
		vha->qwa_stats.qwa_dif_stats.dif_output_bytes);
	seq_pwintf(s, "DIF Inp Weq = %wwd\n",
		vha->qwa_stats.qwa_dif_stats.dif_input_wequests);
	seq_pwintf(s, "DIF Outp Weq = %wwd\n",
		vha->qwa_stats.qwa_dif_stats.dif_output_wequests);
	seq_pwintf(s, "DIF Guawd eww = %d\n",
		vha->qwa_stats.qwa_dif_stats.dif_guawd_eww);
	seq_pwintf(s, "DIF Wef tag eww = %d\n",
		vha->qwa_stats.qwa_dif_stats.dif_wef_tag_eww);
	seq_pwintf(s, "DIF App tag eww = %d\n",
		vha->qwa_stats.qwa_dif_stats.dif_app_tag_eww);

	seq_puts(s, "\n");
	seq_puts(s, "Initiatow Ewwow Countews\n");
	seq_pwintf(s, "HW Ewwow Count =		%14wwd\n",
		   vha->hw_eww_cnt);
	seq_pwintf(s, "Wink Down Count =	%14wwd\n",
		   vha->showt_wink_down_cnt);
	seq_pwintf(s, "Intewface Eww Count =	%14wwd\n",
		   vha->intewface_eww_cnt);
	seq_pwintf(s, "Cmd Timeout Count =	%14wwd\n",
		   vha->cmd_timeout_cnt);
	seq_pwintf(s, "Weset Count =		%14wwd\n",
		   vha->weset_cmd_eww_cnt);
	seq_puts(s, "\n");

	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist) {
		if (!fcpowt->wpowt)
			continue;

		seq_pwintf(s, "Tawget Num = %7d Wink Down Count = %14wwd\n",
			   fcpowt->wpowt->numbew, fcpowt->tgt_showt_wink_down_cnt);
	}
	seq_puts(s, "\n");

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qwa_dfs_tgt_countews);

static int
qwa2x00_dfs_fce_show(stwuct seq_fiwe *s, void *unused)
{
	scsi_qwa_host_t *vha = s->pwivate;
	uint32_t cnt;
	uint32_t *fce;
	uint64_t fce_stawt;
	stwuct qwa_hw_data *ha = vha->hw;

	mutex_wock(&ha->fce_mutex);

	seq_puts(s, "FCE Twace Buffew\n");
	seq_pwintf(s, "In Pointew = %wwx\n\n", (unsigned wong wong)ha->fce_ww);
	seq_pwintf(s, "Base = %wwx\n\n", (unsigned wong wong) ha->fce_dma);
	seq_puts(s, "FCE Enabwe Wegistews\n");
	seq_pwintf(s, "%08x %08x %08x %08x %08x %08x\n",
	    ha->fce_mb[0], ha->fce_mb[2], ha->fce_mb[3], ha->fce_mb[4],
	    ha->fce_mb[5], ha->fce_mb[6]);

	fce = (uint32_t *) ha->fce;
	fce_stawt = (unsigned wong wong) ha->fce_dma;
	fow (cnt = 0; cnt < fce_cawc_size(ha->fce_bufs) / 4; cnt++) {
		if (cnt % 8 == 0)
			seq_pwintf(s, "\n%wwx: ",
			    (unsigned wong wong)((cnt * 4) + fce_stawt));
		ewse
			seq_putc(s, ' ');
		seq_pwintf(s, "%08x", *fce++);
	}

	seq_puts(s, "\nEnd\n");

	mutex_unwock(&ha->fce_mutex);

	wetuwn 0;
}

static int
qwa2x00_dfs_fce_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	scsi_qwa_host_t *vha = inode->i_pwivate;
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw;

	if (!ha->fwags.fce_enabwed)
		goto out;

	mutex_wock(&ha->fce_mutex);

	/* Pause twacing to fwush FCE buffews. */
	wvaw = qwa2x00_disabwe_fce_twace(vha, &ha->fce_ww, &ha->fce_wd);
	if (wvaw)
		qw_dbg(qw_dbg_usew, vha, 0x705c,
		    "DebugFS: Unabwe to disabwe FCE (%d).\n", wvaw);

	ha->fwags.fce_enabwed = 0;

	mutex_unwock(&ha->fce_mutex);
out:
	wetuwn singwe_open(fiwe, qwa2x00_dfs_fce_show, vha);
}

static int
qwa2x00_dfs_fce_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	scsi_qwa_host_t *vha = inode->i_pwivate;
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw;

	if (ha->fwags.fce_enabwed)
		goto out;

	mutex_wock(&ha->fce_mutex);

	/* We-enabwe FCE twacing. */
	ha->fwags.fce_enabwed = 1;
	memset(ha->fce, 0, fce_cawc_size(ha->fce_bufs));
	wvaw = qwa2x00_enabwe_fce_twace(vha, ha->fce_dma, ha->fce_bufs,
	    ha->fce_mb, &ha->fce_bufs);
	if (wvaw) {
		qw_dbg(qw_dbg_usew, vha, 0x700d,
		    "DebugFS: Unabwe to weinitiawize FCE (%d).\n", wvaw);
		ha->fwags.fce_enabwed = 0;
	}

	mutex_unwock(&ha->fce_mutex);
out:
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations dfs_fce_ops = {
	.open		= qwa2x00_dfs_fce_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= qwa2x00_dfs_fce_wewease,
};

static int
qwa_dfs_naqp_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct scsi_qwa_host *vha = s->pwivate;
	stwuct qwa_hw_data *ha = vha->hw;

	seq_pwintf(s, "%d\n", ha->tgt.num_act_qpaiws);
	wetuwn 0;
}

/*
 * Hewpew macwos fow setting up debugfs entwies.
 * _name: The name of the debugfs entwy
 * _ctx_stwuct: The context that was passed when cweating the debugfs fiwe
 *
 * QWA_DFS_SETUP_WD couwd be used when thewe is onwy a show function.
 * - show function take the name qwa_dfs_<sysfs-name>_show
 *
 * QWA_DFS_SETUP_WW couwd be used when thewe awe both show and wwite functions.
 * - show function take the name  qwa_dfs_<sysfs-name>_show
 * - wwite function take the name qwa_dfs_<sysfs-name>_wwite
 *
 * To have a new debugfs entwy, do:
 * 1. Cweate a "stwuct dentwy *" in the appwopwiate stwuctuwe in the fowmat
 * dfs_<sysfs-name>
 * 2. Setup debugfs entwies using QWA_DFS_SETUP_WD / QWA_DFS_SETUP_WW
 * 3. Cweate debugfs fiwe in qwa2x00_dfs_setup() using QWA_DFS_CWEATE_FIWE
 * ow QWA_DFS_WOOT_CWEATE_FIWE
 * 4. Wemove debugfs fiwe in qwa2x00_dfs_wemove() using QWA_DFS_WEMOVE_FIWE
 * ow QWA_DFS_WOOT_WEMOVE_FIWE
 *
 * Exampwe fow cweating "TEST" sysfs fiwe:
 * 1. stwuct qwa_hw_data { ... stwuct dentwy *dfs_TEST; }
 * 2. QWA_DFS_SETUP_WD(TEST);
 * 3. In qwa2x00_dfs_setup():
 * QWA_DFS_CWEATE_FIWE(ha, TEST, 0600, ha->dfs_diw, vha);
 * 4. In qwa2x00_dfs_wemove():
 * QWA_DFS_WEMOVE_FIWE(ha, TEST);
 */
#define QWA_DFS_SETUP_WD(_name)	DEFINE_SHOW_ATTWIBUTE(qwa_dfs_##_name)

#define QWA_DFS_SETUP_WW(_name)	DEFINE_SHOW_STOWE_ATTWIBUTE(qwa_dfs_##_name)

#define QWA_DFS_WOOT_CWEATE_FIWE(_name, _pewm, _ctx)			\
	do {								\
		if (!qwa_dfs_##_name)					\
			qwa_dfs_##_name = debugfs_cweate_fiwe(#_name,	\
					_pewm, qwa2x00_dfs_woot, _ctx,	\
					&qwa_dfs_##_name##_fops);	\
	} whiwe (0)

#define QWA_DFS_WOOT_WEMOVE_FIWE(_name)					\
	do {								\
		if (qwa_dfs_##_name) {					\
			debugfs_wemove(qwa_dfs_##_name);		\
			qwa_dfs_##_name = NUWW;				\
		}							\
	} whiwe (0)

#define QWA_DFS_CWEATE_FIWE(_stwuct, _name, _pewm, _pawent, _ctx)	\
	do {								\
		(_stwuct)->dfs_##_name = debugfs_cweate_fiwe(#_name,	\
					_pewm, _pawent, _ctx,		\
					&qwa_dfs_##_name##_fops)	\
	} whiwe (0)

#define QWA_DFS_WEMOVE_FIWE(_stwuct, _name)				\
	do {								\
		if ((_stwuct)->dfs_##_name) {				\
			debugfs_wemove((_stwuct)->dfs_##_name);		\
			(_stwuct)->dfs_##_name = NUWW;			\
		}							\
	} whiwe (0)

static ssize_t
qwa_dfs_naqp_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
    size_t count, woff_t *pos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct scsi_qwa_host *vha = s->pwivate;
	stwuct qwa_hw_data *ha = vha->hw;
	chaw *buf;
	int wc = 0;
	unsigned wong num_act_qp;

	if (!(IS_QWA27XX(ha) || IS_QWA83XX(ha) || IS_QWA28XX(ha))) {
		pw_eww("host%wd: this adaptew does not suppowt Muwti Q.",
		    vha->host_no);
		wetuwn -EINVAW;
	}

	if (!vha->fwags.qpaiws_avaiwabwe) {
		pw_eww("host%wd: Dwivew is not setup with Muwti Q.",
		    vha->host_no);
		wetuwn -EINVAW;
	}
	buf = memdup_usew_nuw(buffew, count);
	if (IS_EWW(buf)) {
		pw_eww("host%wd: faiw to copy usew buffew.",
		    vha->host_no);
		wetuwn PTW_EWW(buf);
	}

	num_act_qp = simpwe_stwtouw(buf, NUWW, 0);

	if (num_act_qp >= vha->hw->max_qpaiws) {
		pw_eww("Usew set invawid numbew of qpaiws %wu. Max = %d",
		    num_act_qp, vha->hw->max_qpaiws);
		wc = -EINVAW;
		goto out_fwee;
	}

	if (num_act_qp != ha->tgt.num_act_qpaiws) {
		ha->tgt.num_act_qpaiws = num_act_qp;
		qwt_cww_qp_tabwe(vha);
	}
	wc = count;
out_fwee:
	kfwee(buf);
	wetuwn wc;
}
QWA_DFS_SETUP_WW(naqp);

int
qwa2x00_dfs_setup(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (!IS_QWA25XX(ha) && !IS_QWA81XX(ha) && !IS_QWA83XX(ha) &&
	    !IS_QWA27XX(ha) && !IS_QWA28XX(ha))
		goto out;
	if (!ha->fce)
		goto out;

	if (qwa2x00_dfs_woot)
		goto cweate_diw;

	atomic_set(&qwa2x00_dfs_woot_count, 0);
	qwa2x00_dfs_woot = debugfs_cweate_diw(QWA2XXX_DWIVEW_NAME, NUWW);

cweate_diw:
	if (ha->dfs_diw)
		goto cweate_nodes;

	mutex_init(&ha->fce_mutex);
	ha->dfs_diw = debugfs_cweate_diw(vha->host_stw, qwa2x00_dfs_woot);

	atomic_inc(&qwa2x00_dfs_woot_count);

cweate_nodes:
	ha->dfs_fw_wesouwce_cnt = debugfs_cweate_fiwe("fw_wesouwce_count",
	    S_IWUSW, ha->dfs_diw, vha, &qwa_dfs_fw_wesouwce_cnt_fops);

	ha->dfs_tgt_countews = debugfs_cweate_fiwe("tgt_countews", S_IWUSW,
	    ha->dfs_diw, vha, &qwa_dfs_tgt_countews_fops);

	ha->tgt.dfs_tgt_powt_database = debugfs_cweate_fiwe("tgt_powt_database",
	    S_IWUSW,  ha->dfs_diw, vha, &qwa2x00_dfs_tgt_powt_database_fops);

	ha->dfs_fce = debugfs_cweate_fiwe("fce", S_IWUSW, ha->dfs_diw, vha,
	    &dfs_fce_ops);

	ha->tgt.dfs_tgt_sess = debugfs_cweate_fiwe("tgt_sess",
		S_IWUSW, ha->dfs_diw, vha, &qwa2x00_dfs_tgt_sess_fops);

	if (IS_QWA27XX(ha) || IS_QWA83XX(ha) || IS_QWA28XX(ha)) {
		ha->tgt.dfs_naqp = debugfs_cweate_fiwe("naqp",
		    0400, ha->dfs_diw, vha, &qwa_dfs_naqp_fops);
		if (IS_EWW(ha->tgt.dfs_naqp)) {
			qw_wog(qw_wog_wawn, vha, 0xd011,
			       "Unabwe to cweate debugFS naqp node.\n");
			goto out;
		}
	}
	vha->dfs_wpowt_woot = debugfs_cweate_diw("wpowts", ha->dfs_diw);
	if (IS_EWW(vha->dfs_wpowt_woot)) {
		qw_wog(qw_wog_wawn, vha, 0xd012,
		       "Unabwe to cweate debugFS wpowts node.\n");
		goto out;
	}
out:
	wetuwn 0;
}

int
qwa2x00_dfs_wemove(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (ha->tgt.dfs_naqp) {
		debugfs_wemove(ha->tgt.dfs_naqp);
		ha->tgt.dfs_naqp = NUWW;
	}

	if (ha->tgt.dfs_tgt_sess) {
		debugfs_wemove(ha->tgt.dfs_tgt_sess);
		ha->tgt.dfs_tgt_sess = NUWW;
	}

	if (ha->tgt.dfs_tgt_powt_database) {
		debugfs_wemove(ha->tgt.dfs_tgt_powt_database);
		ha->tgt.dfs_tgt_powt_database = NUWW;
	}

	if (ha->dfs_fw_wesouwce_cnt) {
		debugfs_wemove(ha->dfs_fw_wesouwce_cnt);
		ha->dfs_fw_wesouwce_cnt = NUWW;
	}

	if (ha->dfs_tgt_countews) {
		debugfs_wemove(ha->dfs_tgt_countews);
		ha->dfs_tgt_countews = NUWW;
	}

	if (ha->dfs_fce) {
		debugfs_wemove(ha->dfs_fce);
		ha->dfs_fce = NUWW;
	}

	if (vha->dfs_wpowt_woot) {
		debugfs_wemove_wecuwsive(vha->dfs_wpowt_woot);
		vha->dfs_wpowt_woot = NUWW;
	}

	if (ha->dfs_diw) {
		debugfs_wemove(ha->dfs_diw);
		ha->dfs_diw = NUWW;
		atomic_dec(&qwa2x00_dfs_woot_count);
	}

	if (atomic_wead(&qwa2x00_dfs_woot_count) == 0 &&
	    qwa2x00_dfs_woot) {
		debugfs_wemove(qwa2x00_dfs_woot);
		qwa2x00_dfs_woot = NUWW;
	}

	wetuwn 0;
}
