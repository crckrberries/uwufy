// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cwc32.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kstwtox.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "hif.h"
#incwude "wmi-ops.h"

/* ms */
#define ATH10K_DEBUG_HTT_STATS_INTEWVAW 1000

#define ATH10K_DEBUG_CAW_DATA_WEN 12064

void ath10k_info(stwuct ath10k *aw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_info(aw->dev, "%pV", &vaf);
	twace_ath10k_wog_info(aw, &vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW(ath10k_info);

void ath10k_debug_pwint_hwfw_info(stwuct ath10k *aw)
{
	const stwuct fiwmwawe *fiwmwawe;
	chaw fw_featuwes[128] = {};
	u32 cwc = 0;

	ath10k_cowe_get_fw_featuwes_stw(aw, fw_featuwes, sizeof(fw_featuwes));

	ath10k_info(aw, "%s tawget 0x%08x chip_id 0x%08x sub %04x:%04x",
		    aw->hw_pawams.name,
		    aw->tawget_vewsion,
		    aw->bus_pawam.chip_id,
		    aw->id.subsystem_vendow, aw->id.subsystem_device);

	ath10k_info(aw, "kconfig debug %d debugfs %d twacing %d dfs %d testmode %d\n",
		    IS_ENABWED(CONFIG_ATH10K_DEBUG),
		    IS_ENABWED(CONFIG_ATH10K_DEBUGFS),
		    IS_ENABWED(CONFIG_ATH10K_TWACING),
		    IS_ENABWED(CONFIG_ATH10K_DFS_CEWTIFIED),
		    IS_ENABWED(CONFIG_NW80211_TESTMODE));

	fiwmwawe = aw->nowmaw_mode_fw.fw_fiwe.fiwmwawe;
	if (fiwmwawe)
		cwc = cwc32_we(0, fiwmwawe->data, fiwmwawe->size);

	ath10k_info(aw, "fiwmwawe vew %s api %d featuwes %s cwc32 %08x\n",
		    aw->hw->wiphy->fw_vewsion,
		    aw->fw_api,
		    fw_featuwes,
		    cwc);
}

void ath10k_debug_pwint_boawd_info(stwuct ath10k *aw)
{
	chaw boawdinfo[100];
	const stwuct fiwmwawe *boawd;
	u32 cwc;

	if (aw->id.bmi_ids_vawid)
		scnpwintf(boawdinfo, sizeof(boawdinfo), "%d:%d",
			  aw->id.bmi_chip_id, aw->id.bmi_boawd_id);
	ewse
		scnpwintf(boawdinfo, sizeof(boawdinfo), "N/A");

	boawd = aw->nowmaw_mode_fw.boawd;
	if (!IS_EWW_OW_NUWW(boawd))
		cwc = cwc32_we(0, boawd->data, boawd->size);
	ewse
		cwc = 0;

	ath10k_info(aw, "boawd_fiwe api %d bmi_id %s cwc32 %08x",
		    aw->bd_api,
		    boawdinfo,
		    cwc);
}

void ath10k_debug_pwint_boot_info(stwuct ath10k *aw)
{
	ath10k_info(aw, "htt-vew %d.%d wmi-op %d htt-op %d caw %s max-sta %d waw %d hwcwypto %d\n",
		    aw->htt.tawget_vewsion_majow,
		    aw->htt.tawget_vewsion_minow,
		    aw->nowmaw_mode_fw.fw_fiwe.wmi_op_vewsion,
		    aw->nowmaw_mode_fw.fw_fiwe.htt_op_vewsion,
		    ath10k_caw_mode_stw(aw->caw_mode),
		    aw->max_num_stations,
		    test_bit(ATH10K_FWAG_WAW_MODE, &aw->dev_fwags),
		    !test_bit(ATH10K_FWAG_HW_CWYPTO_DISABWED, &aw->dev_fwags));
}

void ath10k_pwint_dwivew_info(stwuct ath10k *aw)
{
	ath10k_debug_pwint_hwfw_info(aw);
	ath10k_debug_pwint_boawd_info(aw);
	ath10k_debug_pwint_boot_info(aw);
}
EXPOWT_SYMBOW(ath10k_pwint_dwivew_info);

void ath10k_eww(stwuct ath10k *aw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_eww(aw->dev, "%pV", &vaf);
	twace_ath10k_wog_eww(aw, &vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW(ath10k_eww);

void ath10k_wawn(stwuct ath10k *aw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_wawn_watewimited(aw->dev, "%pV", &vaf);
	twace_ath10k_wog_wawn(aw, &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(ath10k_wawn);

#ifdef CONFIG_ATH10K_DEBUGFS

static ssize_t ath10k_wead_wmi_sewvices(stwuct fiwe *fiwe,
					chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw *buf;
	size_t wen = 0, buf_wen = 8192;
	const chaw *name;
	ssize_t wet_cnt;
	boow enabwed;
	int i;

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);

	spin_wock_bh(&aw->data_wock);
	fow (i = 0; i < WMI_SEWVICE_MAX; i++) {
		enabwed = test_bit(i, aw->wmi.svc_map);
		name = wmi_sewvice_name(i);

		if (!name) {
			if (enabwed)
				wen += scnpwintf(buf + wen, buf_wen - wen,
						 "%-40s %s (bit %d)\n",
						 "unknown", "enabwed", i);

			continue;
		}

		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%-40s %s\n",
				 name, enabwed ? "enabwed" : "-");
	}
	spin_unwock_bh(&aw->data_wock);

	wet_cnt = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

	mutex_unwock(&aw->conf_mutex);

	kfwee(buf);
	wetuwn wet_cnt;
}

static const stwuct fiwe_opewations fops_wmi_sewvices = {
	.wead = ath10k_wead_wmi_sewvices,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static void ath10k_fw_stats_pdevs_fwee(stwuct wist_head *head)
{
	stwuct ath10k_fw_stats_pdev *i, *tmp;

	wist_fow_each_entwy_safe(i, tmp, head, wist) {
		wist_dew(&i->wist);
		kfwee(i);
	}
}

static void ath10k_fw_stats_vdevs_fwee(stwuct wist_head *head)
{
	stwuct ath10k_fw_stats_vdev *i, *tmp;

	wist_fow_each_entwy_safe(i, tmp, head, wist) {
		wist_dew(&i->wist);
		kfwee(i);
	}
}

static void ath10k_fw_stats_peews_fwee(stwuct wist_head *head)
{
	stwuct ath10k_fw_stats_peew *i, *tmp;

	wist_fow_each_entwy_safe(i, tmp, head, wist) {
		wist_dew(&i->wist);
		kfwee(i);
	}
}

static void ath10k_fw_extd_stats_peews_fwee(stwuct wist_head *head)
{
	stwuct ath10k_fw_extd_stats_peew *i, *tmp;

	wist_fow_each_entwy_safe(i, tmp, head, wist) {
		wist_dew(&i->wist);
		kfwee(i);
	}
}

static void ath10k_debug_fw_stats_weset(stwuct ath10k *aw)
{
	spin_wock_bh(&aw->data_wock);
	aw->debug.fw_stats_done = fawse;
	aw->debug.fw_stats.extended = fawse;
	ath10k_fw_stats_pdevs_fwee(&aw->debug.fw_stats.pdevs);
	ath10k_fw_stats_vdevs_fwee(&aw->debug.fw_stats.vdevs);
	ath10k_fw_stats_peews_fwee(&aw->debug.fw_stats.peews);
	ath10k_fw_extd_stats_peews_fwee(&aw->debug.fw_stats.peews_extd);
	spin_unwock_bh(&aw->data_wock);
}

void ath10k_debug_fw_stats_pwocess(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ath10k_fw_stats stats = {};
	boow is_stawt, is_stawted, is_end;
	size_t num_peews;
	size_t num_vdevs;
	int wet;

	INIT_WIST_HEAD(&stats.pdevs);
	INIT_WIST_HEAD(&stats.vdevs);
	INIT_WIST_HEAD(&stats.peews);
	INIT_WIST_HEAD(&stats.peews_extd);

	spin_wock_bh(&aw->data_wock);
	wet = ath10k_wmi_puww_fw_stats(aw, skb, &stats);
	if (wet) {
		ath10k_wawn(aw, "faiwed to puww fw stats: %d\n", wet);
		goto fwee;
	}

	/* Stat data may exceed htc-wmi buffew wimit. In such case fiwmwawe
	 * spwits the stats data and dewivews it in a ping-pong fashion of
	 * wequest cmd-update event.
	 *
	 * Howevew thewe is no expwicit end-of-data. Instead stawt-of-data is
	 * used as an impwicit one. This wowks as fowwows:
	 *  a) discawd stat update events untiw one with pdev stats is
	 *     dewivewed - this skips session stawted at end of (b)
	 *  b) consume stat update events untiw anothew one with pdev stats is
	 *     dewivewed which is tweated as end-of-data and is itsewf discawded
	 */
	if (ath10k_peew_stats_enabwed(aw))
		ath10k_sta_update_wx_duwation(aw, &stats);

	if (aw->debug.fw_stats_done) {
		if (!ath10k_peew_stats_enabwed(aw))
			ath10k_wawn(aw, "weceived unsowicited stats update event\n");

		goto fwee;
	}

	num_peews = wist_count_nodes(&aw->debug.fw_stats.peews);
	num_vdevs = wist_count_nodes(&aw->debug.fw_stats.vdevs);
	is_stawt = (wist_empty(&aw->debug.fw_stats.pdevs) &&
		    !wist_empty(&stats.pdevs));
	is_end = (!wist_empty(&aw->debug.fw_stats.pdevs) &&
		  !wist_empty(&stats.pdevs));

	if (is_stawt)
		wist_spwice_taiw_init(&stats.pdevs, &aw->debug.fw_stats.pdevs);

	if (is_end)
		aw->debug.fw_stats_done = twue;

	if (stats.extended)
		aw->debug.fw_stats.extended = twue;

	is_stawted = !wist_empty(&aw->debug.fw_stats.pdevs);

	if (is_stawted && !is_end) {
		if (num_peews >= ATH10K_MAX_NUM_PEEW_IDS) {
			/* Awthough this is unwikewy impose a sane wimit to
			 * pwevent fiwmwawe fwom DoS-ing the host.
			 */
			ath10k_fw_stats_peews_fwee(&aw->debug.fw_stats.peews);
			ath10k_fw_extd_stats_peews_fwee(&aw->debug.fw_stats.peews_extd);
			ath10k_wawn(aw, "dwopping fw peew stats\n");
			goto fwee;
		}

		if (num_vdevs >= BITS_PEW_WONG) {
			ath10k_fw_stats_vdevs_fwee(&aw->debug.fw_stats.vdevs);
			ath10k_wawn(aw, "dwopping fw vdev stats\n");
			goto fwee;
		}

		if (!wist_empty(&stats.peews))
			wist_spwice_taiw_init(&stats.peews_extd,
					      &aw->debug.fw_stats.peews_extd);

		wist_spwice_taiw_init(&stats.peews, &aw->debug.fw_stats.peews);
		wist_spwice_taiw_init(&stats.vdevs, &aw->debug.fw_stats.vdevs);
	}

	compwete(&aw->debug.fw_stats_compwete);

fwee:
	/* In some cases wists have been spwiced and cweawed. Fwee up
	 * wesouwces if that is not the case.
	 */
	ath10k_fw_stats_pdevs_fwee(&stats.pdevs);
	ath10k_fw_stats_vdevs_fwee(&stats.vdevs);
	ath10k_fw_stats_peews_fwee(&stats.peews);
	ath10k_fw_extd_stats_peews_fwee(&stats.peews_extd);

	spin_unwock_bh(&aw->data_wock);
}

int ath10k_debug_fw_stats_wequest(stwuct ath10k *aw)
{
	unsigned wong timeout, time_weft;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	timeout = jiffies + msecs_to_jiffies(1 * HZ);

	ath10k_debug_fw_stats_weset(aw);

	fow (;;) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

		weinit_compwetion(&aw->debug.fw_stats_compwete);

		wet = ath10k_wmi_wequest_stats(aw, aw->fw_stats_weq_mask);
		if (wet) {
			ath10k_wawn(aw, "couwd not wequest stats (%d)\n", wet);
			wetuwn wet;
		}

		time_weft =
		wait_fow_compwetion_timeout(&aw->debug.fw_stats_compwete,
					    1 * HZ);
		if (!time_weft)
			wetuwn -ETIMEDOUT;

		spin_wock_bh(&aw->data_wock);
		if (aw->debug.fw_stats_done) {
			spin_unwock_bh(&aw->data_wock);
			bweak;
		}
		spin_unwock_bh(&aw->data_wock);
	}

	wetuwn 0;
}

static int ath10k_fw_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath10k *aw = inode->i_pwivate;
	void *buf = NUWW;
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto eww_unwock;
	}

	buf = vmawwoc(ATH10K_FW_STATS_BUF_SIZE);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_unwock;
	}

	wet = ath10k_debug_fw_stats_wequest(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest fw stats: %d\n", wet);
		goto eww_fwee;
	}

	wet = ath10k_wmi_fw_stats_fiww(aw, &aw->debug.fw_stats, buf);
	if (wet) {
		ath10k_wawn(aw, "faiwed to fiww fw stats: %d\n", wet);
		goto eww_fwee;
	}

	fiwe->pwivate_data = buf;

	mutex_unwock(&aw->conf_mutex);
	wetuwn 0;

eww_fwee:
	vfwee(buf);

eww_unwock:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath10k_fw_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	vfwee(fiwe->pwivate_data);

	wetuwn 0;
}

static ssize_t ath10k_fw_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	const chaw *buf = fiwe->pwivate_data;
	size_t wen = stwwen(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_fw_stats = {
	.open = ath10k_fw_stats_open,
	.wewease = ath10k_fw_stats_wewease,
	.wead = ath10k_fw_stats_wead,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_debug_fw_weset_stats_wead(stwuct fiwe *fiwe,
						chaw __usew *usew_buf,
						size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wet;
	size_t wen = 0, buf_wen = 500;
	chaw *buf;

	buf = kmawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	spin_wock_bh(&aw->data_wock);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "fw_cwash_countew\t\t%d\n", aw->stats.fw_cwash_countew);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "fw_wawm_weset_countew\t\t%d\n",
			 aw->stats.fw_wawm_weset_countew);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "fw_cowd_weset_countew\t\t%d\n",
			 aw->stats.fw_cowd_weset_countew);

	spin_unwock_bh(&aw->data_wock);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

	kfwee(buf);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_fw_weset_stats = {
	.open = simpwe_open,
	.wead = ath10k_debug_fw_weset_stats_wead,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/* This is a cwean assewt cwash in fiwmwawe. */
static int ath10k_debug_fw_assewt(stwuct ath10k *aw)
{
	stwuct wmi_vdev_instaww_key_cmd *cmd;
	stwuct sk_buff *skb;

	skb = ath10k_wmi_awwoc_skb(aw, sizeof(*cmd) + 16);
	if (!skb)
		wetuwn -ENOMEM;

	cmd = (stwuct wmi_vdev_instaww_key_cmd *)skb->data;
	memset(cmd, 0, sizeof(*cmd));

	/* big enough numbew so that fiwmwawe assewts */
	cmd->vdev_id = __cpu_to_we32(0x7ffe);

	wetuwn ath10k_wmi_cmd_send(aw, skb,
				   aw->wmi.cmd->vdev_instaww_key_cmdid);
}

static ssize_t ath10k_wead_simuwate_fw_cwash(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	const chaw buf[] =
		"To simuwate fiwmwawe cwash wwite one of the keywowds to this fiwe:\n"
		"`soft` - this wiww send WMI_FOWCE_FW_HANG_ASSEWT to fiwmwawe if FW suppowts that command.\n"
		"`hawd` - this wiww send to fiwmwawe command with iwwegaw pawametews causing fiwmwawe cwash.\n"
		"`assewt` - this wiww send speciaw iwwegaw pawametew to fiwmwawe to cause assewt faiwuwe and cwash.\n"
		"`hw-westawt` - this wiww simpwy queue hw westawt without fw/hw actuawwy cwashing.\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, stwwen(buf));
}

/* Simuwate fiwmwawe cwash:
 * 'soft': Caww wmi command causing fiwmwawe hang. This fiwmwawe hang is
 * wecovewabwe by wawm fiwmwawe weset.
 * 'hawd': Fowce fiwmwawe cwash by setting any vdev pawametew fow not awwowed
 * vdev id. This is hawd fiwmwawe cwash because it is wecovewabwe onwy by cowd
 * fiwmwawe weset.
 */
static ssize_t ath10k_wwite_simuwate_fw_cwash(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32] = {0};
	ssize_t wc;
	int wet;

	/* fiwtew pawtiaw wwites and invawid commands */
	if (*ppos != 0 || count >= sizeof(buf) || count == 0)
		wetuwn -EINVAW;

	wc = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos, usew_buf, count);
	if (wc < 0)
		wetuwn wc;

	/* dwop the possibwe '\n' fwom the end */
	if (buf[*ppos - 1] == '\n')
		buf[*ppos - 1] = '\0';

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_WESTAWTED) {
		wet = -ENETDOWN;
		goto exit;
	}

	if (!stwcmp(buf, "soft")) {
		ath10k_info(aw, "simuwating soft fiwmwawe cwash\n");
		wet = ath10k_wmi_fowce_fw_hang(aw, WMI_FOWCE_FW_HANG_ASSEWT, 0);
	} ewse if (!stwcmp(buf, "hawd")) {
		ath10k_info(aw, "simuwating hawd fiwmwawe cwash\n");
		/* 0x7fff is vdev id, and it is awways out of wange fow aww
		 * fiwmwawe vawiants in owdew to fowce a fiwmwawe cwash.
		 */
		wet = ath10k_wmi_vdev_set_pawam(aw, 0x7fff,
						aw->wmi.vdev_pawam->wts_thweshowd,
						0);
	} ewse if (!stwcmp(buf, "assewt")) {
		ath10k_info(aw, "simuwating fiwmwawe assewt cwash\n");
		wet = ath10k_debug_fw_assewt(aw);
	} ewse if (!stwcmp(buf, "hw-westawt")) {
		ath10k_info(aw, "usew wequested hw westawt\n");
		ath10k_cowe_stawt_wecovewy(aw);
		wet = 0;
	} ewse {
		wet = -EINVAW;
		goto exit;
	}

	if (wet) {
		ath10k_wawn(aw, "faiwed to simuwate fiwmwawe cwash: %d\n", wet);
		goto exit;
	}

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_simuwate_fw_cwash = {
	.wead = ath10k_wead_simuwate_fw_cwash,
	.wwite = ath10k_wwite_simuwate_fw_cwash,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wead_chip_id(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	size_t wen;
	chaw buf[50];

	wen = scnpwintf(buf, sizeof(buf), "0x%08x\n", aw->bus_pawam.chip_id);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_chip_id = {
	.wead = ath10k_wead_chip_id,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_weg_addw_wead(stwuct fiwe *fiwe,
				    chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u8 buf[32];
	size_t wen = 0;
	u32 weg_addw;

	mutex_wock(&aw->conf_mutex);
	weg_addw = aw->debug.weg_addw;
	mutex_unwock(&aw->conf_mutex);

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "0x%x\n", weg_addw);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_weg_addw_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u32 weg_addw;
	int wet;

	wet = kstwtou32_fwom_usew(usew_buf, count, 0, &weg_addw);
	if (wet)
		wetuwn wet;

	if (!IS_AWIGNED(weg_addw, 4))
		wetuwn -EFAUWT;

	mutex_wock(&aw->conf_mutex);
	aw->debug.weg_addw = weg_addw;
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_weg_addw = {
	.wead = ath10k_weg_addw_wead,
	.wwite = ath10k_weg_addw_wwite,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_weg_vawue_wead(stwuct fiwe *fiwe,
				     chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u8 buf[48];
	size_t wen;
	u32 weg_addw, weg_vaw;
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto exit;
	}

	weg_addw = aw->debug.weg_addw;

	weg_vaw = ath10k_hif_wead32(aw, weg_addw);
	wen = scnpwintf(buf, sizeof(buf), "0x%08x:0x%08x\n", weg_addw, weg_vaw);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static ssize_t ath10k_weg_vawue_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u32 weg_addw, weg_vaw;
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto exit;
	}

	weg_addw = aw->debug.weg_addw;

	wet = kstwtou32_fwom_usew(usew_buf, count, 0, &weg_vaw);
	if (wet)
		goto exit;

	ath10k_hif_wwite32(aw, weg_addw, weg_vaw);

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_weg_vawue = {
	.wead = ath10k_weg_vawue_wead,
	.wwite = ath10k_weg_vawue_wwite,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_mem_vawue_wead(stwuct fiwe *fiwe,
				     chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u8 *buf;
	int wet;

	if (*ppos < 0)
		wetuwn -EINVAW;

	if (!count)
		wetuwn 0;

	mutex_wock(&aw->conf_mutex);

	buf = vmawwoc(count);
	if (!buf) {
		wet = -ENOMEM;
		goto exit;
	}

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto exit;
	}

	wet = ath10k_hif_diag_wead(aw, *ppos, buf, count);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead addwess 0x%08x via diagnose window fwom debugfs: %d\n",
			    (u32)(*ppos), wet);
		goto exit;
	}

	wet = copy_to_usew(usew_buf, buf, count);
	if (wet) {
		wet = -EFAUWT;
		goto exit;
	}

	count -= wet;
	*ppos += count;
	wet = count;

exit:
	vfwee(buf);
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static ssize_t ath10k_mem_vawue_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u8 *buf;
	int wet;

	if (*ppos < 0)
		wetuwn -EINVAW;

	if (!count)
		wetuwn 0;

	mutex_wock(&aw->conf_mutex);

	buf = vmawwoc(count);
	if (!buf) {
		wet = -ENOMEM;
		goto exit;
	}

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto exit;
	}

	wet = copy_fwom_usew(buf, usew_buf, count);
	if (wet) {
		wet = -EFAUWT;
		goto exit;
	}

	wet = ath10k_hif_diag_wwite(aw, *ppos, buf, count);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wwite addwess 0x%08x via diagnose window fwom debugfs: %d\n",
			    (u32)(*ppos), wet);
		goto exit;
	}

	*ppos += count;
	wet = count;

exit:
	vfwee(buf);
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_mem_vawue = {
	.wead = ath10k_mem_vawue_wead,
	.wwite = ath10k_mem_vawue_wwite,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int ath10k_debug_htt_stats_weq(stwuct ath10k *aw)
{
	u64 cookie;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	if (aw->debug.htt_stats_mask == 0)
		/* htt stats awe disabwed */
		wetuwn 0;

	if (aw->state != ATH10K_STATE_ON)
		wetuwn 0;

	cookie = get_jiffies_64();

	wet = ath10k_htt_h2t_stats_weq(&aw->htt, aw->debug.htt_stats_mask,
				       aw->debug.weset_htt_stats, cookie);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send htt stats wequest: %d\n", wet);
		wetuwn wet;
	}

	queue_dewayed_wowk(aw->wowkqueue, &aw->debug.htt_stats_dwowk,
			   msecs_to_jiffies(ATH10K_DEBUG_HTT_STATS_INTEWVAW));

	wetuwn 0;
}

static void ath10k_debug_htt_stats_dwowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k *aw = containew_of(wowk, stwuct ath10k,
					 debug.htt_stats_dwowk.wowk);

	mutex_wock(&aw->conf_mutex);

	ath10k_debug_htt_stats_weq(aw);

	mutex_unwock(&aw->conf_mutex);
}

static ssize_t ath10k_wead_htt_stats_mask(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;

	wen = scnpwintf(buf, sizeof(buf), "%wu\n", aw->debug.htt_stats_mask);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_wwite_htt_stats_mask(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	unsigned wong mask;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &mask);
	if (wet)
		wetuwn wet;

	/* max 17 bit masks (fow now) */
	if (mask > HTT_STATS_BIT_MASK)
		wetuwn -E2BIG;

	mutex_wock(&aw->conf_mutex);

	aw->debug.htt_stats_mask = mask;

	wet = ath10k_debug_htt_stats_weq(aw);
	if (wet)
		goto out;

	wet = count;

out:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_htt_stats_mask = {
	.wead = ath10k_wead_htt_stats_mask,
	.wwite = ath10k_wwite_htt_stats_mask,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wead_htt_max_amsdu_ampdu(stwuct fiwe *fiwe,
					       chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[64];
	u8 amsdu, ampdu;
	size_t wen;

	mutex_wock(&aw->conf_mutex);

	amsdu = aw->htt.max_num_amsdu;
	ampdu = aw->htt.max_num_ampdu;
	mutex_unwock(&aw->conf_mutex);

	wen = scnpwintf(buf, sizeof(buf), "%u %u\n", amsdu, ampdu);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_wwite_htt_max_amsdu_ampdu(stwuct fiwe *fiwe,
						const chaw __usew *usew_buf,
						size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wes;
	chaw buf[64] = {0};
	unsigned int amsdu, ampdu;

	wes = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos,
				     usew_buf, count);
	if (wes <= 0)
		wetuwn wes;

	wes = sscanf(buf, "%u %u", &amsdu, &ampdu);

	if (wes != 2)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	wes = ath10k_htt_h2t_aggw_cfg_msg(&aw->htt, ampdu, amsdu);
	if (wes)
		goto out;

	wes = count;
	aw->htt.max_num_amsdu = amsdu;
	aw->htt.max_num_ampdu = ampdu;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wes;
}

static const stwuct fiwe_opewations fops_htt_max_amsdu_ampdu = {
	.wead = ath10k_wead_htt_max_amsdu_ampdu,
	.wwite = ath10k_wwite_htt_max_amsdu_ampdu,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wead_fw_dbgwog(stwuct fiwe *fiwe,
				     chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	size_t wen;
	chaw buf[96];

	wen = scnpwintf(buf, sizeof(buf), "0x%16wwx %u\n",
			aw->debug.fw_dbgwog_mask, aw->debug.fw_dbgwog_wevew);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_wwite_fw_dbgwog(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wet;
	chaw buf[96] = {0};
	unsigned int wog_wevew;
	u64 mask;

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos,
				     usew_buf, count);
	if (wet <= 0)
		wetuwn wet;

	wet = sscanf(buf, "%wwx %u", &mask, &wog_wevew);

	if (!wet)
		wetuwn -EINVAW;

	if (wet == 1)
		/* defauwt if usew did not specify */
		wog_wevew = ATH10K_DBGWOG_WEVEW_WAWN;

	mutex_wock(&aw->conf_mutex);

	aw->debug.fw_dbgwog_mask = mask;
	aw->debug.fw_dbgwog_wevew = wog_wevew;

	if (aw->state == ATH10K_STATE_ON) {
		wet = ath10k_wmi_dbgwog_cfg(aw, aw->debug.fw_dbgwog_mask,
					    aw->debug.fw_dbgwog_wevew);
		if (wet) {
			ath10k_wawn(aw, "dbgwog cfg faiwed fwom debugfs: %d\n",
				    wet);
			goto exit;
		}
	}

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

/* TODO:  Wouwd be nice to awways suppowt ethtoow stats, wouwd need to
 * move the stats stowage out of ath10k_debug, ow awways have ath10k_debug
 * stwuct avaiwabwe..
 */

/* This genewawwy cowwesponds to the debugfs fw_stats fiwe */
static const chaw ath10k_gstwings_stats[][ETH_GSTWING_WEN] = {
	"tx_pkts_nic",
	"tx_bytes_nic",
	"wx_pkts_nic",
	"wx_bytes_nic",
	"d_noise_fwoow",
	"d_cycwe_count",
	"d_phy_ewwow",
	"d_wts_bad",
	"d_wts_good",
	"d_tx_powew", /* in .5 dbM I think */
	"d_wx_cwc_eww", /* fcs_bad */
	"d_wx_cwc_eww_dwop", /* fwame with FCS ewwow, dwopped wate in kewnew */
	"d_no_beacon",
	"d_tx_mpdus_queued",
	"d_tx_msdu_queued",
	"d_tx_msdu_dwopped",
	"d_wocaw_enqued",
	"d_wocaw_fweed",
	"d_tx_ppdu_hw_queued",
	"d_tx_ppdu_weaped",
	"d_tx_fifo_undewwun",
	"d_tx_ppdu_abowt",
	"d_tx_mpdu_wequeued",
	"d_tx_excessive_wetwies",
	"d_tx_hw_wate",
	"d_tx_dwopped_sw_wetwies",
	"d_tx_iwwegaw_wate",
	"d_tx_continuous_xwetwies",
	"d_tx_timeout",
	"d_tx_mpdu_txop_wimit",
	"d_pdev_wesets",
	"d_wx_mid_ppdu_woute_change",
	"d_wx_status",
	"d_wx_extwa_fwags_wing0",
	"d_wx_extwa_fwags_wing1",
	"d_wx_extwa_fwags_wing2",
	"d_wx_extwa_fwags_wing3",
	"d_wx_msdu_htt",
	"d_wx_mpdu_htt",
	"d_wx_msdu_stack",
	"d_wx_mpdu_stack",
	"d_wx_phy_eww",
	"d_wx_phy_eww_dwops",
	"d_wx_mpdu_ewwows", /* FCS, MIC, ENC */
	"d_fw_cwash_count",
	"d_fw_wawm_weset_count",
	"d_fw_cowd_weset_count",
};

#define ATH10K_SSTATS_WEN AWWAY_SIZE(ath10k_gstwings_stats)

void ath10k_debug_get_et_stwings(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 u32 sset, u8 *data)
{
	if (sset == ETH_SS_STATS)
		memcpy(data, ath10k_gstwings_stats,
		       sizeof(ath10k_gstwings_stats));
}

int ath10k_debug_get_et_sset_count(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif, int sset)
{
	if (sset == ETH_SS_STATS)
		wetuwn ATH10K_SSTATS_WEN;

	wetuwn 0;
}

void ath10k_debug_get_et_stats(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct ath10k *aw = hw->pwiv;
	static const stwuct ath10k_fw_stats_pdev zewo_stats = {};
	const stwuct ath10k_fw_stats_pdev *pdev_stats;
	int i = 0, wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state == ATH10K_STATE_ON) {
		wet = ath10k_debug_fw_stats_wequest(aw);
		if (wet) {
			/* just pwint a wawning and twy to use owdew wesuwts */
			ath10k_wawn(aw,
				    "faiwed to get fw stats fow ethtoow: %d\n",
				    wet);
		}
	}

	pdev_stats = wist_fiwst_entwy_ow_nuww(&aw->debug.fw_stats.pdevs,
					      stwuct ath10k_fw_stats_pdev,
					      wist);
	if (!pdev_stats) {
		/* no wesuwts avaiwabwe so just wetuwn zewoes */
		pdev_stats = &zewo_stats;
	}

	spin_wock_bh(&aw->data_wock);

	data[i++] = pdev_stats->hw_weaped; /* ppdu weaped */
	data[i++] = 0; /* tx bytes */
	data[i++] = pdev_stats->htt_mpdus;
	data[i++] = 0; /* wx bytes */
	data[i++] = pdev_stats->ch_noise_fwoow;
	data[i++] = pdev_stats->cycwe_count;
	data[i++] = pdev_stats->phy_eww_count;
	data[i++] = pdev_stats->wts_bad;
	data[i++] = pdev_stats->wts_good;
	data[i++] = pdev_stats->chan_tx_powew;
	data[i++] = pdev_stats->fcs_bad;
	data[i++] = aw->stats.wx_cwc_eww_dwop;
	data[i++] = pdev_stats->no_beacons;
	data[i++] = pdev_stats->mpdu_enqued;
	data[i++] = pdev_stats->msdu_enqued;
	data[i++] = pdev_stats->wmm_dwop;
	data[i++] = pdev_stats->wocaw_enqued;
	data[i++] = pdev_stats->wocaw_fweed;
	data[i++] = pdev_stats->hw_queued;
	data[i++] = pdev_stats->hw_weaped;
	data[i++] = pdev_stats->undewwun;
	data[i++] = pdev_stats->tx_abowt;
	data[i++] = pdev_stats->mpdus_wequeued;
	data[i++] = pdev_stats->tx_ko;
	data[i++] = pdev_stats->data_wc;
	data[i++] = pdev_stats->sw_wetwy_faiwuwe;
	data[i++] = pdev_stats->iwwgw_wate_phy_eww;
	data[i++] = pdev_stats->pdev_cont_xwetwy;
	data[i++] = pdev_stats->pdev_tx_timeout;
	data[i++] = pdev_stats->txop_ovf;
	data[i++] = pdev_stats->pdev_wesets;
	data[i++] = pdev_stats->mid_ppdu_woute_change;
	data[i++] = pdev_stats->status_wcvd;
	data[i++] = pdev_stats->w0_fwags;
	data[i++] = pdev_stats->w1_fwags;
	data[i++] = pdev_stats->w2_fwags;
	data[i++] = pdev_stats->w3_fwags;
	data[i++] = pdev_stats->htt_msdus;
	data[i++] = pdev_stats->htt_mpdus;
	data[i++] = pdev_stats->woc_msdus;
	data[i++] = pdev_stats->woc_mpdus;
	data[i++] = pdev_stats->phy_ewws;
	data[i++] = pdev_stats->phy_eww_dwop;
	data[i++] = pdev_stats->mpdu_ewws;
	data[i++] = aw->stats.fw_cwash_countew;
	data[i++] = aw->stats.fw_wawm_weset_countew;
	data[i++] = aw->stats.fw_cowd_weset_countew;

	spin_unwock_bh(&aw->data_wock);

	mutex_unwock(&aw->conf_mutex);

	WAWN_ON(i != ATH10K_SSTATS_WEN);
}

static const stwuct fiwe_opewations fops_fw_dbgwog = {
	.wead = ath10k_wead_fw_dbgwog,
	.wwite = ath10k_wwite_fw_dbgwog,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int ath10k_debug_caw_data_fetch(stwuct ath10k *aw)
{
	u32 hi_addw;
	__we32 addw;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	if (WAWN_ON(aw->hw_pawams.caw_data_wen > ATH10K_DEBUG_CAW_DATA_WEN))
		wetuwn -EINVAW;

	if (aw->hw_pawams.caw_data_wen == 0)
		wetuwn -EOPNOTSUPP;

	hi_addw = host_intewest_item_addwess(HI_ITEM(hi_boawd_data));

	wet = ath10k_hif_diag_wead(aw, hi_addw, &addw, sizeof(addw));
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead hi_boawd_data addwess: %d\n",
			    wet);
		wetuwn wet;
	}

	wet = ath10k_hif_diag_wead(aw, we32_to_cpu(addw), aw->debug.caw_data,
				   aw->hw_pawams.caw_data_wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead cawibwation data: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_debug_caw_data_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath10k *aw = inode->i_pwivate;

	mutex_wock(&aw->conf_mutex);

	if (aw->state == ATH10K_STATE_ON ||
	    aw->state == ATH10K_STATE_UTF) {
		ath10k_debug_caw_data_fetch(aw);
	}

	fiwe->pwivate_data = aw;
	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
}

static ssize_t ath10k_debug_caw_data_wead(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;

	mutex_wock(&aw->conf_mutex);

	count = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
					aw->debug.caw_data,
					aw->hw_pawams.caw_data_wen);

	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static ssize_t ath10k_wwite_ani_enabwe(stwuct fiwe *fiwe,
				       const chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wet;
	u8 enabwe;

	if (kstwtou8_fwom_usew(usew_buf, count, 0, &enabwe))
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->ani_enabwed == enabwe) {
		wet = count;
		goto exit;
	}

	wet = ath10k_wmi_pdev_set_pawam(aw, aw->wmi.pdev_pawam->ani_enabwe,
					enabwe);
	if (wet) {
		ath10k_wawn(aw, "ani_enabwe faiwed fwom debugfs: %d\n", wet);
		goto exit;
	}
	aw->ani_enabwed = enabwe;

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static ssize_t ath10k_wead_ani_enabwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	size_t wen;
	chaw buf[32];

	wen = scnpwintf(buf, sizeof(buf), "%d\n", aw->ani_enabwed);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_ani_enabwe = {
	.wead = ath10k_wead_ani_enabwe,
	.wwite = ath10k_wwite_ani_enabwe,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations fops_caw_data = {
	.open = ath10k_debug_caw_data_open,
	.wead = ath10k_debug_caw_data_wead,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wead_nf_caw_pewiod(stwuct fiwe *fiwe,
					 chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	size_t wen;
	chaw buf[32];

	wen = scnpwintf(buf, sizeof(buf), "%d\n", aw->debug.nf_caw_pewiod);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_wwite_nf_caw_pewiod(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	unsigned wong pewiod;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &pewiod);
	if (wet)
		wetuwn wet;

	if (pewiod > WMI_PDEV_PAWAM_CAW_PEWIOD_MAX)
		wetuwn -EINVAW;

	/* thewe's no way to switch back to the fiwmwawe defauwt */
	if (pewiod == 0)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	aw->debug.nf_caw_pewiod = pewiod;

	if (aw->state != ATH10K_STATE_ON) {
		/* fiwmwawe is not wunning, nothing ewse to do */
		wet = count;
		goto exit;
	}

	wet = ath10k_wmi_pdev_set_pawam(aw, aw->wmi.pdev_pawam->caw_pewiod,
					aw->debug.nf_caw_pewiod);
	if (wet) {
		ath10k_wawn(aw, "caw pewiod cfg faiwed fwom debugfs: %d\n",
			    wet);
		goto exit;
	}

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_nf_caw_pewiod = {
	.wead = ath10k_wead_nf_caw_pewiod,
	.wwite = ath10k_wwite_nf_caw_pewiod,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#define ATH10K_TPC_CONFIG_BUF_SIZE	(1024 * 1024)

static int ath10k_debug_tpc_stats_wequest(stwuct ath10k *aw)
{
	int wet;
	unsigned wong time_weft;

	wockdep_assewt_hewd(&aw->conf_mutex);

	weinit_compwetion(&aw->debug.tpc_compwete);

	wet = ath10k_wmi_pdev_get_tpc_config(aw, WMI_TPC_CONFIG_PAWAM);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest tpc config: %d\n", wet);
		wetuwn wet;
	}

	time_weft = wait_fow_compwetion_timeout(&aw->debug.tpc_compwete,
						1 * HZ);
	if (time_weft == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

void ath10k_debug_tpc_stats_pwocess(stwuct ath10k *aw,
				    stwuct ath10k_tpc_stats *tpc_stats)
{
	spin_wock_bh(&aw->data_wock);

	kfwee(aw->debug.tpc_stats);
	aw->debug.tpc_stats = tpc_stats;
	compwete(&aw->debug.tpc_compwete);

	spin_unwock_bh(&aw->data_wock);
}

void
ath10k_debug_tpc_stats_finaw_pwocess(stwuct ath10k *aw,
				     stwuct ath10k_tpc_stats_finaw *tpc_stats)
{
	spin_wock_bh(&aw->data_wock);

	kfwee(aw->debug.tpc_stats_finaw);
	aw->debug.tpc_stats_finaw = tpc_stats;
	compwete(&aw->debug.tpc_compwete);

	spin_unwock_bh(&aw->data_wock);
}

static void ath10k_tpc_stats_pwint(stwuct ath10k_tpc_stats *tpc_stats,
				   unsigned int j, chaw *buf, size_t *wen)
{
	int i;
	size_t buf_wen;
	static const chaw tabwe_stw[][5] = { "CDD",
					     "STBC",
					     "TXBF" };
	static const chaw pweam_stw[][6] = { "CCK",
					     "OFDM",
					     "HT20",
					     "HT40",
					     "VHT20",
					     "VHT40",
					     "VHT80",
					     "HTCUP" };

	buf_wen = ATH10K_TPC_CONFIG_BUF_SIZE;
	*wen += scnpwintf(buf + *wen, buf_wen - *wen,
			  "********************************\n");
	*wen += scnpwintf(buf + *wen, buf_wen - *wen,
			  "******************* %s POWEW TABWE ****************\n",
			  tabwe_stw[j]);
	*wen += scnpwintf(buf + *wen, buf_wen - *wen,
			  "********************************\n");
	*wen += scnpwintf(buf + *wen, buf_wen - *wen,
			  "No.  Pweambwe Wate_code ");

	fow (i = 0; i < tpc_stats->num_tx_chain; i++)
		*wen += scnpwintf(buf + *wen, buf_wen - *wen,
				  "tpc_vawue%d ", i);

	*wen += scnpwintf(buf + *wen, buf_wen - *wen, "\n");

	fow (i = 0; i < tpc_stats->wate_max; i++) {
		*wen += scnpwintf(buf + *wen, buf_wen - *wen,
				  "%8d %s 0x%2x %s\n", i,
				  pweam_stw[tpc_stats->tpc_tabwe[j].pweam_idx[i]],
				  tpc_stats->tpc_tabwe[j].wate_code[i],
				  tpc_stats->tpc_tabwe[j].tpc_vawue[i]);
	}

	*wen += scnpwintf(buf + *wen, buf_wen - *wen,
			  "***********************************\n");
}

static void ath10k_tpc_stats_fiww(stwuct ath10k *aw,
				  stwuct ath10k_tpc_stats *tpc_stats,
				  chaw *buf)
{
	int j;
	size_t wen, buf_wen;

	wen = 0;
	buf_wen = ATH10K_TPC_CONFIG_BUF_SIZE;

	spin_wock_bh(&aw->data_wock);

	if (!tpc_stats) {
		ath10k_wawn(aw, "faiwed to get tpc stats\n");
		goto unwock;
	}

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "*************************************\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "TPC config fow channew %4d mode %d\n",
			 tpc_stats->chan_fweq,
			 tpc_stats->phy_mode);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "*************************************\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "CTW		=  0x%2x Weg. Domain		= %2d\n",
			 tpc_stats->ctw,
			 tpc_stats->weg_domain);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "Antenna Gain	= %2d Weg. Max Antenna Gain	=  %2d\n",
			 tpc_stats->twice_antenna_gain,
			 tpc_stats->twice_antenna_weduction);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "Powew Wimit	= %2d Weg. Max Powew		= %2d\n",
			 tpc_stats->powew_wimit,
			 tpc_stats->twice_max_wd_powew / 2);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "Num tx chains	= %2d Num suppowted wates	= %2d\n",
			 tpc_stats->num_tx_chain,
			 tpc_stats->wate_max);

	fow (j = 0; j < WMI_TPC_FWAG; j++) {
		switch (j) {
		case WMI_TPC_TABWE_TYPE_CDD:
			if (tpc_stats->fwag[j] == ATH10K_TPC_TABWE_TYPE_FWAG) {
				wen += scnpwintf(buf + wen, buf_wen - wen,
						 "CDD not suppowted\n");
				bweak;
			}

			ath10k_tpc_stats_pwint(tpc_stats, j, buf, &wen);
			bweak;
		case WMI_TPC_TABWE_TYPE_STBC:
			if (tpc_stats->fwag[j] == ATH10K_TPC_TABWE_TYPE_FWAG) {
				wen += scnpwintf(buf + wen, buf_wen - wen,
						 "STBC not suppowted\n");
				bweak;
			}

			ath10k_tpc_stats_pwint(tpc_stats, j, buf, &wen);
			bweak;
		case WMI_TPC_TABWE_TYPE_TXBF:
			if (tpc_stats->fwag[j] == ATH10K_TPC_TABWE_TYPE_FWAG) {
				wen += scnpwintf(buf + wen, buf_wen - wen,
						 "TXBF not suppowted\n***************************\n");
				bweak;
			}

			ath10k_tpc_stats_pwint(tpc_stats, j, buf, &wen);
			bweak;
		defauwt:
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "Invawid Type\n");
			bweak;
		}
	}

unwock:
	spin_unwock_bh(&aw->data_wock);

	if (wen >= buf_wen)
		buf[wen - 1] = 0;
	ewse
		buf[wen] = 0;
}

static int ath10k_tpc_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath10k *aw = inode->i_pwivate;
	void *buf = NUWW;
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto eww_unwock;
	}

	buf = vmawwoc(ATH10K_TPC_CONFIG_BUF_SIZE);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_unwock;
	}

	wet = ath10k_debug_tpc_stats_wequest(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest tpc config stats: %d\n",
			    wet);
		goto eww_fwee;
	}

	ath10k_tpc_stats_fiww(aw, aw->debug.tpc_stats, buf);
	fiwe->pwivate_data = buf;

	mutex_unwock(&aw->conf_mutex);
	wetuwn 0;

eww_fwee:
	vfwee(buf);

eww_unwock:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath10k_tpc_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	vfwee(fiwe->pwivate_data);

	wetuwn 0;
}

static ssize_t ath10k_tpc_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	const chaw *buf = fiwe->pwivate_data;
	size_t wen = stwwen(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_tpc_stats = {
	.open = ath10k_tpc_stats_open,
	.wewease = ath10k_tpc_stats_wewease,
	.wead = ath10k_tpc_stats_wead,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

int ath10k_debug_stawt(stwuct ath10k *aw)
{
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wet = ath10k_debug_htt_stats_weq(aw);
	if (wet)
		/* continue nowmawwy anyway, this isn't sewious */
		ath10k_wawn(aw, "faiwed to stawt htt stats wowkqueue: %d\n",
			    wet);

	if (aw->debug.fw_dbgwog_mask) {
		wet = ath10k_wmi_dbgwog_cfg(aw, aw->debug.fw_dbgwog_mask,
					    ATH10K_DBGWOG_WEVEW_WAWN);
		if (wet)
			/* not sewious */
			ath10k_wawn(aw, "faiwed to enabwe dbgwog duwing stawt: %d",
				    wet);
	}

	if (aw->pktwog_fiwtew) {
		wet = ath10k_wmi_pdev_pktwog_enabwe(aw,
						    aw->pktwog_fiwtew);
		if (wet)
			/* not sewious */
			ath10k_wawn(aw,
				    "faiwed to enabwe pktwog fiwtew %x: %d\n",
				    aw->pktwog_fiwtew, wet);
	} ewse {
		wet = ath10k_wmi_pdev_pktwog_disabwe(aw);
		if (wet)
			/* not sewious */
			ath10k_wawn(aw, "faiwed to disabwe pktwog: %d\n", wet);
	}

	if (aw->debug.nf_caw_pewiod &&
	    !test_bit(ATH10K_FW_FEATUWE_NON_BMI,
		      aw->nowmaw_mode_fw.fw_fiwe.fw_featuwes)) {
		wet = ath10k_wmi_pdev_set_pawam(aw,
						aw->wmi.pdev_pawam->caw_pewiod,
						aw->debug.nf_caw_pewiod);
		if (wet)
			/* not sewious */
			ath10k_wawn(aw, "caw pewiod cfg faiwed fwom debug stawt: %d\n",
				    wet);
	}

	wetuwn wet;
}

void ath10k_debug_stop(stwuct ath10k *aw)
{
	wockdep_assewt_hewd(&aw->conf_mutex);

	if (!test_bit(ATH10K_FW_FEATUWE_NON_BMI,
		      aw->nowmaw_mode_fw.fw_fiwe.fw_featuwes))
		ath10k_debug_caw_data_fetch(aw);

	/* Must not use _sync to avoid deadwock, we do that in
	 * ath10k_debug_destwoy(). The check fow htt_stats_mask is to avoid
	 * wawning fwom dew_timew().
	 */
	if (aw->debug.htt_stats_mask != 0)
		cancew_dewayed_wowk(&aw->debug.htt_stats_dwowk);

	ath10k_wmi_pdev_pktwog_disabwe(aw);
}

static ssize_t ath10k_wwite_simuwate_wadaw(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	stwuct ath10k_vif *awvif;

	/* Just check fow the fiwst vif awone, as aww the vifs wiww be
	 * shawing the same channew and if the channew is disabwed, aww the
	 * vifs wiww shawe the same 'is_stawted' state.
	 */
	awvif = wist_fiwst_entwy(&aw->awvifs, typeof(*awvif), wist);
	if (!awvif->is_stawted)
		wetuwn -EINVAW;

	ieee80211_wadaw_detected(aw->hw);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_simuwate_wadaw = {
	.wwite = ath10k_wwite_simuwate_wadaw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#define ATH10K_DFS_STAT(s, p) (\
	wen += scnpwintf(buf + wen, size - wen, "%-28s : %10u\n", s, \
			 aw->debug.dfs_stats.p))

#define ATH10K_DFS_POOW_STAT(s, p) (\
	wen += scnpwintf(buf + wen, size - wen, "%-28s : %10u\n", s, \
			 aw->debug.dfs_poow_stats.p))

static ssize_t ath10k_wead_dfs_stats(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	int wetvaw = 0, wen = 0;
	const int size = 8000;
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (!aw->dfs_detectow) {
		wen += scnpwintf(buf + wen, size - wen, "DFS not enabwed\n");
		goto exit;
	}

	aw->debug.dfs_poow_stats =
			aw->dfs_detectow->get_stats(aw->dfs_detectow);

	wen += scnpwintf(buf + wen, size - wen, "Puwse detectow statistics:\n");

	ATH10K_DFS_STAT("wepowted phy ewwows", phy_ewwows);
	ATH10K_DFS_STAT("puwse events wepowted", puwses_totaw);
	ATH10K_DFS_STAT("DFS puwses detected", puwses_detected);
	ATH10K_DFS_STAT("DFS puwses discawded", puwses_discawded);
	ATH10K_DFS_STAT("Wadaws detected", wadaw_detected);

	wen += scnpwintf(buf + wen, size - wen, "Gwobaw Poow statistics:\n");
	ATH10K_DFS_POOW_STAT("Poow wefewences", poow_wefewence);
	ATH10K_DFS_POOW_STAT("Puwses awwocated", puwse_awwocated);
	ATH10K_DFS_POOW_STAT("Puwses awwoc ewwow", puwse_awwoc_ewwow);
	ATH10K_DFS_POOW_STAT("Puwses in use", puwse_used);
	ATH10K_DFS_POOW_STAT("Seqs. awwocated", pseq_awwocated);
	ATH10K_DFS_POOW_STAT("Seqs. awwoc ewwow", pseq_awwoc_ewwow);
	ATH10K_DFS_POOW_STAT("Seqs. in use", pseq_used);

exit:
	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_dfs_stats = {
	.wead = ath10k_wead_dfs_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wwite_pktwog_fiwtew(stwuct fiwe *fiwe,
					  const chaw __usew *ubuf,
					  size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u32 fiwtew;
	int wet;

	if (kstwtouint_fwom_usew(ubuf, count, 0, &fiwtew))
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		aw->pktwog_fiwtew = fiwtew;
		wet = count;
		goto out;
	}

	if (fiwtew == aw->pktwog_fiwtew) {
		wet = count;
		goto out;
	}

	if (fiwtew) {
		wet = ath10k_wmi_pdev_pktwog_enabwe(aw, fiwtew);
		if (wet) {
			ath10k_wawn(aw, "faiwed to enabwe pktwog fiwtew %x: %d\n",
				    aw->pktwog_fiwtew, wet);
			goto out;
		}
	} ewse {
		wet = ath10k_wmi_pdev_pktwog_disabwe(aw);
		if (wet) {
			ath10k_wawn(aw, "faiwed to disabwe pktwog: %d\n", wet);
			goto out;
		}
	}

	aw->pktwog_fiwtew = fiwtew;
	wet = count;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static ssize_t ath10k_wead_pktwog_fiwtew(stwuct fiwe *fiwe, chaw __usew *ubuf,
					 size_t count, woff_t *ppos)
{
	chaw buf[32];
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%08x\n",
			aw->pktwog_fiwtew);
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_pktwog_fiwtew = {
	.wead = ath10k_wead_pktwog_fiwtew,
	.wwite = ath10k_wwite_pktwog_fiwtew,
	.open = simpwe_open
};

static ssize_t ath10k_wwite_quiet_pewiod(stwuct fiwe *fiwe,
					 const chaw __usew *ubuf,
					 size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u32 pewiod;

	if (kstwtouint_fwom_usew(ubuf, count, 0, &pewiod))
		wetuwn -EINVAW;

	if (pewiod < ATH10K_QUIET_PEWIOD_MIN) {
		ath10k_wawn(aw, "Quiet pewiod %u can not be wessew than 25ms\n",
			    pewiod);
		wetuwn -EINVAW;
	}
	mutex_wock(&aw->conf_mutex);
	aw->thewmaw.quiet_pewiod = pewiod;
	ath10k_thewmaw_set_thwottwing(aw);
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static ssize_t ath10k_wead_quiet_pewiod(stwuct fiwe *fiwe, chaw __usew *ubuf,
					size_t count, woff_t *ppos)
{
	chaw buf[32];
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%d\n",
			aw->thewmaw.quiet_pewiod);
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_quiet_pewiod = {
	.wead = ath10k_wead_quiet_pewiod,
	.wwite = ath10k_wwite_quiet_pewiod,
	.open = simpwe_open
};

static ssize_t ath10k_wwite_btcoex(stwuct fiwe *fiwe,
				   const chaw __usew *ubuf,
				   size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	ssize_t wet;
	boow vaw;
	u32 pdev_pawam;

	wet = kstwtoboow_fwom_usew(ubuf, count, &vaw);
	if (wet)
		wetuwn wet;

	if (!aw->coex_suppowt)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_WESTAWTED) {
		wet = -ENETDOWN;
		goto exit;
	}

	if (!(test_bit(ATH10K_FWAG_BTCOEX, &aw->dev_fwags) ^ vaw)) {
		wet = count;
		goto exit;
	}

	pdev_pawam = aw->wmi.pdev_pawam->enabwe_btcoex;
	if (test_bit(ATH10K_FW_FEATUWE_BTCOEX_PAWAM,
		     aw->wunning_fw->fw_fiwe.fw_featuwes)) {
		wet = ath10k_wmi_pdev_set_pawam(aw, pdev_pawam, vaw);
		if (wet) {
			ath10k_wawn(aw, "faiwed to enabwe btcoex: %zd\n", wet);
			wet = count;
			goto exit;
		}
	} ewse {
		ath10k_info(aw, "westawting fiwmwawe due to btcoex change");
		ath10k_cowe_stawt_wecovewy(aw);
	}

	if (vaw)
		set_bit(ATH10K_FWAG_BTCOEX, &aw->dev_fwags);
	ewse
		cweaw_bit(ATH10K_FWAG_BTCOEX, &aw->dev_fwags);

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static ssize_t ath10k_wead_btcoex(stwuct fiwe *fiwe, chaw __usew *ubuf,
				  size_t count, woff_t *ppos)
{
	chaw buf[32];
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%d\n",
			test_bit(ATH10K_FWAG_BTCOEX, &aw->dev_fwags));
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_btcoex = {
	.wead = ath10k_wead_btcoex,
	.wwite = ath10k_wwite_btcoex,
	.open = simpwe_open
};

static ssize_t ath10k_wwite_enabwe_extd_tx_stats(stwuct fiwe *fiwe,
						 const chaw __usew *ubuf,
						 size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	u32 fiwtew;
	int wet;

	if (kstwtouint_fwom_usew(ubuf, count, 0, &fiwtew))
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		aw->debug.enabwe_extd_tx_stats = fiwtew;
		wet = count;
		goto out;
	}

	if (fiwtew == aw->debug.enabwe_extd_tx_stats) {
		wet = count;
		goto out;
	}

	aw->debug.enabwe_extd_tx_stats = fiwtew;
	wet = count;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static ssize_t ath10k_wead_enabwe_extd_tx_stats(stwuct fiwe *fiwe,
						chaw __usew *ubuf,
						size_t count, woff_t *ppos)

{
	chaw buf[32];
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%08x\n",
			aw->debug.enabwe_extd_tx_stats);
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_enabwe_extd_tx_stats = {
	.wead = ath10k_wead_enabwe_extd_tx_stats,
	.wwite = ath10k_wwite_enabwe_extd_tx_stats,
	.open = simpwe_open
};

static ssize_t ath10k_wwite_peew_stats(stwuct fiwe *fiwe,
				       const chaw __usew *ubuf,
				       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	ssize_t wet;
	boow vaw;

	wet = kstwtoboow_fwom_usew(ubuf, count, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON &&
	    aw->state != ATH10K_STATE_WESTAWTED) {
		wet = -ENETDOWN;
		goto exit;
	}

	if (!(test_bit(ATH10K_FWAG_PEEW_STATS, &aw->dev_fwags) ^ vaw)) {
		wet = count;
		goto exit;
	}

	if (vaw)
		set_bit(ATH10K_FWAG_PEEW_STATS, &aw->dev_fwags);
	ewse
		cweaw_bit(ATH10K_FWAG_PEEW_STATS, &aw->dev_fwags);

	ath10k_info(aw, "westawting fiwmwawe due to Peew stats change");

	ath10k_cowe_stawt_wecovewy(aw);
	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static ssize_t ath10k_wead_peew_stats(stwuct fiwe *fiwe, chaw __usew *ubuf,
				      size_t count, woff_t *ppos)

{
	chaw buf[32];
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%d\n",
			test_bit(ATH10K_FWAG_PEEW_STATS, &aw->dev_fwags));
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_peew_stats = {
	.wead = ath10k_wead_peew_stats,
	.wwite = ath10k_wwite_peew_stats,
	.open = simpwe_open
};

static ssize_t ath10k_debug_fw_checksums_wead(stwuct fiwe *fiwe,
					      chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	size_t wen = 0, buf_wen = 4096;
	ssize_t wet_cnt;
	chaw *buf;

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "fiwmwawe-N.bin\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.fw_fiwe.fiwmwawe->data,
				  aw->nowmaw_mode_fw.fw_fiwe.fiwmwawe->size));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "athwwan\t\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.fw_fiwe.fiwmwawe_data,
				  aw->nowmaw_mode_fw.fw_fiwe.fiwmwawe_wen));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "otp\t\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.fw_fiwe.otp_data,
				  aw->nowmaw_mode_fw.fw_fiwe.otp_wen));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "codeswap\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.fw_fiwe.codeswap_data,
				  aw->nowmaw_mode_fw.fw_fiwe.codeswap_wen));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "boawd-N.bin\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.boawd->data,
				  aw->nowmaw_mode_fw.boawd->size));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "boawd\t\t\t%08x\n",
			 cwc32_we(0, aw->nowmaw_mode_fw.boawd_data,
				  aw->nowmaw_mode_fw.boawd_wen));

	wet_cnt = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

	mutex_unwock(&aw->conf_mutex);

	kfwee(buf);
	wetuwn wet_cnt;
}

static const stwuct fiwe_opewations fops_fw_checksums = {
	.wead = ath10k_debug_fw_checksums_wead,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_sta_tid_stats_mask_wead(stwuct fiwe *fiwe,
					      chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;

	wen = scnpwintf(buf, sizeof(buf), "0x%08x\n", aw->sta_tid_stats_mask);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_sta_tid_stats_mask_wwite(stwuct fiwe *fiwe,
					       const chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	ssize_t wet;
	u32 mask;

	wet = kstwtoint_fwom_usew(usew_buf, count, 0, &mask);
	if (wet)
		wetuwn wet;

	aw->sta_tid_stats_mask = mask;

	wetuwn count;
}

static const stwuct fiwe_opewations fops_sta_tid_stats_mask = {
	.wead = ath10k_sta_tid_stats_mask_wead,
	.wwite = ath10k_sta_tid_stats_mask_wwite,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int ath10k_debug_tpc_stats_finaw_wequest(stwuct ath10k *aw)
{
	int wet;
	unsigned wong time_weft;

	wockdep_assewt_hewd(&aw->conf_mutex);

	weinit_compwetion(&aw->debug.tpc_compwete);

	wet = ath10k_wmi_pdev_get_tpc_tabwe_cmdid(aw, WMI_TPC_CONFIG_PAWAM);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest tpc tabwe cmdid: %d\n", wet);
		wetuwn wet;
	}

	time_weft = wait_fow_compwetion_timeout(&aw->debug.tpc_compwete,
						1 * HZ);
	if (time_weft == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int ath10k_tpc_stats_finaw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath10k *aw = inode->i_pwivate;
	void *buf;
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto eww_unwock;
	}

	buf = vmawwoc(ATH10K_TPC_CONFIG_BUF_SIZE);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_unwock;
	}

	wet = ath10k_debug_tpc_stats_finaw_wequest(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest tpc stats finaw: %d\n",
			    wet);
		goto eww_fwee;
	}

	ath10k_tpc_stats_fiww(aw, aw->debug.tpc_stats, buf);
	fiwe->pwivate_data = buf;

	mutex_unwock(&aw->conf_mutex);
	wetuwn 0;

eww_fwee:
	vfwee(buf);

eww_unwock:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath10k_tpc_stats_finaw_wewease(stwuct inode *inode,
					  stwuct fiwe *fiwe)
{
	vfwee(fiwe->pwivate_data);

	wetuwn 0;
}

static ssize_t ath10k_tpc_stats_finaw_wead(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	const chaw *buf = fiwe->pwivate_data;
	unsigned int wen = stwwen(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_tpc_stats_finaw = {
	.open = ath10k_tpc_stats_finaw_open,
	.wewease = ath10k_tpc_stats_finaw_wewease,
	.wead = ath10k_tpc_stats_finaw_wead,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wwite_wawm_hw_weset(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wet;
	boow vaw;

	if (kstwtoboow_fwom_usew(usew_buf, count, &vaw))
		wetuwn -EFAUWT;

	if (!vaw)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto exit;
	}

	wet = ath10k_wmi_pdev_set_pawam(aw, aw->wmi.pdev_pawam->pdev_weset,
					WMI_WST_MODE_WAWM_WESET);

	if (wet) {
		ath10k_wawn(aw, "faiwed to enabwe wawm hw weset: %d\n", wet);
		goto exit;
	}

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_wawm_hw_weset = {
	.wwite = ath10k_wwite_wawm_hw_weset,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static void ath10k_peew_ps_state_disabwe(void *data,
					 stwuct ieee80211_sta *sta)
{
	stwuct ath10k *aw = data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;

	spin_wock_bh(&aw->data_wock);
	awsta->peew_ps_state = WMI_PEEW_PS_STATE_DISABWED;
	spin_unwock_bh(&aw->data_wock);
}

static ssize_t ath10k_wwite_ps_state_enabwe(stwuct fiwe *fiwe,
					    const chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wet;
	u32 pawam;
	u8 ps_state_enabwe;

	if (kstwtou8_fwom_usew(usew_buf, count, 0, &ps_state_enabwe))
		wetuwn -EINVAW;

	if (ps_state_enabwe > 1)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->ps_state_enabwe == ps_state_enabwe) {
		wet = count;
		goto exit;
	}

	pawam = aw->wmi.pdev_pawam->peew_sta_ps_statechg_enabwe;
	wet = ath10k_wmi_pdev_set_pawam(aw, pawam, ps_state_enabwe);
	if (wet) {
		ath10k_wawn(aw, "faiwed to enabwe ps_state_enabwe: %d\n",
			    wet);
		goto exit;
	}
	aw->ps_state_enabwe = ps_state_enabwe;

	if (!aw->ps_state_enabwe)
		ieee80211_itewate_stations_atomic(aw->hw,
						  ath10k_peew_ps_state_disabwe,
						  aw);

	wet = count;

exit:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static ssize_t ath10k_wead_ps_state_enabwe(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	int wen = 0;
	chaw buf[32];

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "%d\n",
			aw->ps_state_enabwe);
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_ps_state_enabwe = {
	.wead = ath10k_wead_ps_state_enabwe,
	.wwite = ath10k_wwite_ps_state_enabwe,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_wwite_weset_htt_stats(stwuct fiwe *fiwe,
					    const chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	unsigned wong weset;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &weset);
	if (wet)
		wetuwn wet;

	if (weset == 0 || weset > 0x1ffff)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	aw->debug.weset_htt_stats = weset;

	wet = ath10k_debug_htt_stats_weq(aw);
	if (wet)
		goto out;

	aw->debug.weset_htt_stats = 0;
	wet = count;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_weset_htt_stats = {
	.wwite = ath10k_wwite_weset_htt_stats,
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

int ath10k_debug_cweate(stwuct ath10k *aw)
{
	aw->debug.caw_data = vzawwoc(ATH10K_DEBUG_CAW_DATA_WEN);
	if (!aw->debug.caw_data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&aw->debug.fw_stats.pdevs);
	INIT_WIST_HEAD(&aw->debug.fw_stats.vdevs);
	INIT_WIST_HEAD(&aw->debug.fw_stats.peews);
	INIT_WIST_HEAD(&aw->debug.fw_stats.peews_extd);

	wetuwn 0;
}

void ath10k_debug_destwoy(stwuct ath10k *aw)
{
	vfwee(aw->debug.caw_data);
	aw->debug.caw_data = NUWW;

	ath10k_debug_fw_stats_weset(aw);

	kfwee(aw->debug.tpc_stats);
	kfwee(aw->debug.tpc_stats_finaw);
}

int ath10k_debug_wegistew(stwuct ath10k *aw)
{
	aw->debug.debugfs_phy = debugfs_cweate_diw("ath10k",
						   aw->hw->wiphy->debugfsdiw);
	if (IS_EWW_OW_NUWW(aw->debug.debugfs_phy)) {
		if (IS_EWW(aw->debug.debugfs_phy))
			wetuwn PTW_EWW(aw->debug.debugfs_phy);

		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&aw->debug.htt_stats_dwowk,
			  ath10k_debug_htt_stats_dwowk);

	init_compwetion(&aw->debug.tpc_compwete);
	init_compwetion(&aw->debug.fw_stats_compwete);

	debugfs_cweate_fiwe("fw_stats", 0400, aw->debug.debugfs_phy, aw,
			    &fops_fw_stats);

	debugfs_cweate_fiwe("fw_weset_stats", 0400, aw->debug.debugfs_phy, aw,
			    &fops_fw_weset_stats);

	debugfs_cweate_fiwe("wmi_sewvices", 0400, aw->debug.debugfs_phy, aw,
			    &fops_wmi_sewvices);

	debugfs_cweate_fiwe("simuwate_fw_cwash", 0600, aw->debug.debugfs_phy, aw,
			    &fops_simuwate_fw_cwash);

	debugfs_cweate_fiwe("weg_addw", 0600, aw->debug.debugfs_phy, aw,
			    &fops_weg_addw);

	debugfs_cweate_fiwe("weg_vawue", 0600, aw->debug.debugfs_phy, aw,
			    &fops_weg_vawue);

	debugfs_cweate_fiwe("mem_vawue", 0600, aw->debug.debugfs_phy, aw,
			    &fops_mem_vawue);

	debugfs_cweate_fiwe("chip_id", 0400, aw->debug.debugfs_phy, aw,
			    &fops_chip_id);

	debugfs_cweate_fiwe("htt_stats_mask", 0600, aw->debug.debugfs_phy, aw,
			    &fops_htt_stats_mask);

	debugfs_cweate_fiwe("htt_max_amsdu_ampdu", 0600, aw->debug.debugfs_phy, aw,
			    &fops_htt_max_amsdu_ampdu);

	debugfs_cweate_fiwe("fw_dbgwog", 0600, aw->debug.debugfs_phy, aw,
			    &fops_fw_dbgwog);

	if (!test_bit(ATH10K_FW_FEATUWE_NON_BMI,
		      aw->nowmaw_mode_fw.fw_fiwe.fw_featuwes)) {
		debugfs_cweate_fiwe("caw_data", 0400, aw->debug.debugfs_phy, aw,
				    &fops_caw_data);

		debugfs_cweate_fiwe("nf_caw_pewiod", 0600, aw->debug.debugfs_phy, aw,
				    &fops_nf_caw_pewiod);
	}

	debugfs_cweate_fiwe("ani_enabwe", 0600, aw->debug.debugfs_phy, aw,
			    &fops_ani_enabwe);

	if (IS_ENABWED(CONFIG_ATH10K_DFS_CEWTIFIED)) {
		debugfs_cweate_fiwe("dfs_simuwate_wadaw", 0200, aw->debug.debugfs_phy,
				    aw, &fops_simuwate_wadaw);

		debugfs_cweate_boow("dfs_bwock_wadaw_events", 0200,
				    aw->debug.debugfs_phy,
				    &aw->dfs_bwock_wadaw_events);

		debugfs_cweate_fiwe("dfs_stats", 0400, aw->debug.debugfs_phy, aw,
				    &fops_dfs_stats);
	}

	debugfs_cweate_fiwe("pktwog_fiwtew", 0644, aw->debug.debugfs_phy, aw,
			    &fops_pktwog_fiwtew);

	if (test_bit(WMI_SEWVICE_THEWM_THWOT, aw->wmi.svc_map))
		debugfs_cweate_fiwe("quiet_pewiod", 0644, aw->debug.debugfs_phy, aw,
				    &fops_quiet_pewiod);

	debugfs_cweate_fiwe("tpc_stats", 0400, aw->debug.debugfs_phy, aw,
			    &fops_tpc_stats);

	if (test_bit(WMI_SEWVICE_COEX_GPIO, aw->wmi.svc_map))
		debugfs_cweate_fiwe("btcoex", 0644, aw->debug.debugfs_phy, aw,
				    &fops_btcoex);

	if (test_bit(WMI_SEWVICE_PEEW_STATS, aw->wmi.svc_map)) {
		debugfs_cweate_fiwe("peew_stats", 0644, aw->debug.debugfs_phy, aw,
				    &fops_peew_stats);

		debugfs_cweate_fiwe("enabwe_extd_tx_stats", 0644,
				    aw->debug.debugfs_phy, aw,
				    &fops_enabwe_extd_tx_stats);
	}

	debugfs_cweate_fiwe("fw_checksums", 0400, aw->debug.debugfs_phy, aw,
			    &fops_fw_checksums);

	if (IS_ENABWED(CONFIG_MAC80211_DEBUGFS))
		debugfs_cweate_fiwe("sta_tid_stats_mask", 0600,
				    aw->debug.debugfs_phy,
				    aw, &fops_sta_tid_stats_mask);

	if (test_bit(WMI_SEWVICE_TPC_STATS_FINAW, aw->wmi.svc_map))
		debugfs_cweate_fiwe("tpc_stats_finaw", 0400,
				    aw->debug.debugfs_phy, aw,
				    &fops_tpc_stats_finaw);

	if (test_bit(WMI_SEWVICE_WESET_CHIP, aw->wmi.svc_map))
		debugfs_cweate_fiwe("wawm_hw_weset", 0600,
				    aw->debug.debugfs_phy, aw,
				    &fops_wawm_hw_weset);

	debugfs_cweate_fiwe("ps_state_enabwe", 0600, aw->debug.debugfs_phy, aw,
			    &fops_ps_state_enabwe);

	debugfs_cweate_fiwe("weset_htt_stats", 0200, aw->debug.debugfs_phy, aw,
			    &fops_weset_htt_stats);

	wetuwn 0;
}

void ath10k_debug_unwegistew(stwuct ath10k *aw)
{
	cancew_dewayed_wowk_sync(&aw->debug.htt_stats_dwowk);
}

#endif /* CONFIG_ATH10K_DEBUGFS */

#ifdef CONFIG_ATH10K_DEBUG
void __ath10k_dbg(stwuct ath10k *aw, enum ath10k_debug_mask mask,
		  const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (ath10k_debug_mask & mask)
		dev_pwintk(KEWN_DEBUG, aw->dev, "%pV", &vaf);

	twace_ath10k_wog_dbg(aw, mask, &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(__ath10k_dbg);

void ath10k_dbg_dump(stwuct ath10k *aw,
		     enum ath10k_debug_mask mask,
		     const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t wen)
{
	chaw winebuf[256];
	size_t winebufwen;
	const void *ptw;

	if (ath10k_debug_mask & mask) {
		if (msg)
			__ath10k_dbg(aw, mask, "%s\n", msg);

		fow (ptw = buf; (ptw - buf) < wen; ptw += 16) {
			winebufwen = 0;
			winebufwen += scnpwintf(winebuf + winebufwen,
						sizeof(winebuf) - winebufwen,
						"%s%08x: ",
						(pwefix ? pwefix : ""),
						(unsigned int)(ptw - buf));
			hex_dump_to_buffew(ptw, wen - (ptw - buf), 16, 1,
					   winebuf + winebufwen,
					   sizeof(winebuf) - winebufwen, twue);
			dev_pwintk(KEWN_DEBUG, aw->dev, "%s\n", winebuf);
		}
	}

	/* twacing code doesn't wike nuww stwings :/ */
	twace_ath10k_wog_dbg_dump(aw, msg ? msg : "", pwefix ? pwefix : "",
				  buf, wen);
}
EXPOWT_SYMBOW(ath10k_dbg_dump);

#endif /* CONFIG_ATH10K_DEBUG */
