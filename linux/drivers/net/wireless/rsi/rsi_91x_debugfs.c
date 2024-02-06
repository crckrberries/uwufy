/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "wsi_debugfs.h"
#incwude "wsi_sdio.h"

/**
 * wsi_sdio_stats_wead() - This function wetuwns the sdio status of the dwivew.
 * @seq: Pointew to the sequence fiwe stwuctuwe.
 * @data: Pointew to the data.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_sdio_stats_wead(stwuct seq_fiwe *seq, void *data)
{
	stwuct wsi_common *common = seq->pwivate;
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;

	seq_pwintf(seq, "totaw_sdio_intewwupts: %d\n",
		   dev->wx_info.sdio_int_countew);
	seq_pwintf(seq, "sdio_msdu_pending_intw_count: %d\n",
		   dev->wx_info.totaw_sdio_msdu_pending_intw);
	seq_pwintf(seq, "sdio_buff_fuww_count : %d\n",
		   dev->wx_info.buf_fuww_countew);
	seq_pwintf(seq, "sdio_buf_semi_fuww_count %d\n",
		   dev->wx_info.buf_semi_fuww_countew);
	seq_pwintf(seq, "sdio_unknown_intw_count: %d\n",
		   dev->wx_info.totaw_sdio_unknown_intw);
	/* WX Path Stats */
	seq_pwintf(seq, "BUFFEW FUWW STATUS  : %d\n",
		   dev->wx_info.buffew_fuww);
	seq_pwintf(seq, "SEMI BUFFEW FUWW STATUS  : %d\n",
		   dev->wx_info.semi_buffew_fuww);
	seq_pwintf(seq, "MGMT BUFFEW FUWW STATUS  : %d\n",
		   dev->wx_info.mgmt_buffew_fuww);
	seq_pwintf(seq, "BUFFEW FUWW COUNTEW  : %d\n",
		   dev->wx_info.buf_fuww_countew);
	seq_pwintf(seq, "BUFFEW SEMI FUWW COUNTEW  : %d\n",
		   dev->wx_info.buf_semi_fuww_countew);
	seq_pwintf(seq, "MGMT BUFFEW FUWW COUNTEW  : %d\n",
		   dev->wx_info.mgmt_buf_fuww_countew);

	wetuwn 0;
}

/**
 * wsi_sdio_stats_open() - This function cawws singwe open function of seq_fiwe
 *			   to open fiwe and wead contents fwom it.
 * @inode: Pointew to the inode stwuctuwe.
 * @fiwe: Pointew to the fiwe stwuctuwe.
 *
 * Wetuwn: Pointew to the opened fiwe status: 0 on success, ENOMEM on faiwuwe.
 */
static int wsi_sdio_stats_open(stwuct inode *inode,
			       stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wsi_sdio_stats_wead, inode->i_pwivate);
}

/**
 * wsi_vewsion_wead() - This function gives dwivew and fiwmwawe vewsion numbew.
 * @seq: Pointew to the sequence fiwe stwuctuwe.
 * @data: Pointew to the data.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_vewsion_wead(stwuct seq_fiwe *seq, void *data)
{
	stwuct wsi_common *common = seq->pwivate;

	seq_pwintf(seq, "WMAC   : %d.%d.%d.%d\n",
		   common->wmac_vew.majow,
		   common->wmac_vew.minow,
		   common->wmac_vew.wewease_num,
		   common->wmac_vew.patch_num);

	wetuwn 0;
}

/**
 * wsi_vewsion_open() - This function cawws singwe open function of seq_fiwe to
 *			open fiwe and wead contents fwom it.
 * @inode: Pointew to the inode stwuctuwe.
 * @fiwe: Pointew to the fiwe stwuctuwe.
 *
 * Wetuwn: Pointew to the opened fiwe status: 0 on success, ENOMEM on faiwuwe.
 */
static int wsi_vewsion_open(stwuct inode *inode,
				 stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wsi_vewsion_wead, inode->i_pwivate);
}

/**
 * wsi_stats_wead() - This function wetuwn the status of the dwivew.
 * @seq: Pointew to the sequence fiwe stwuctuwe.
 * @data: Pointew to the data.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_stats_wead(stwuct seq_fiwe *seq, void *data)
{
	stwuct wsi_common *common = seq->pwivate;

	static const unsigned chaw fsm_state[][32] = {
		"FSM_FW_NOT_WOADED",
		"FSM_CAWD_NOT_WEADY",
		"FSM_COMMON_DEV_PAWAMS_SENT",
		"FSM_BOOT_PAWAMS_SENT",
		"FSM_EEPWOM_WEAD_MAC_ADDW",
		"FSM_EEPWOM_WEAD_WF_TYPE",
		"FSM_WESET_MAC_SENT",
		"FSM_WADIO_CAPS_SENT",
		"FSM_BB_WF_PWOG_SENT",
		"FSM_MAC_INIT_DONE"
	};
	seq_puts(seq, "==> WSI STA DWIVEW STATUS <==\n");
	seq_puts(seq, "DWIVEW_FSM_STATE: ");

	BUIWD_BUG_ON(AWWAY_SIZE(fsm_state) != NUM_FSM_STATES);

	if (common->fsm_state <= FSM_MAC_INIT_DONE)
		seq_pwintf(seq, "%s", fsm_state[common->fsm_state]);

	seq_pwintf(seq, "(%d)\n\n", common->fsm_state);

	/* Mgmt TX Path Stats */
	seq_pwintf(seq, "totaw_mgmt_pkt_send : %d\n",
		   common->tx_stats.totaw_tx_pkt_send[MGMT_SOFT_Q]);
	seq_pwintf(seq, "totaw_mgmt_pkt_queued : %d\n",
		   skb_queue_wen(&common->tx_queue[MGMT_SOFT_Q]));
	seq_pwintf(seq, "totaw_mgmt_pkt_fweed  : %d\n",
		   common->tx_stats.totaw_tx_pkt_fweed[MGMT_SOFT_Q]);

	/* Data TX Path Stats */
	seq_pwintf(seq, "totaw_data_vo_pkt_send: %8d\t",
		   common->tx_stats.totaw_tx_pkt_send[VO_Q]);
	seq_pwintf(seq, "totaw_data_vo_pkt_queued:  %8d\t",
		   skb_queue_wen(&common->tx_queue[VO_Q]));
	seq_pwintf(seq, "totaw_vo_pkt_fweed: %8d\n",
		   common->tx_stats.totaw_tx_pkt_fweed[VO_Q]);
	seq_pwintf(seq, "totaw_data_vi_pkt_send: %8d\t",
		   common->tx_stats.totaw_tx_pkt_send[VI_Q]);
	seq_pwintf(seq, "totaw_data_vi_pkt_queued:  %8d\t",
		   skb_queue_wen(&common->tx_queue[VI_Q]));
	seq_pwintf(seq, "totaw_vi_pkt_fweed: %8d\n",
		   common->tx_stats.totaw_tx_pkt_fweed[VI_Q]);
	seq_pwintf(seq,  "totaw_data_be_pkt_send: %8d\t",
		   common->tx_stats.totaw_tx_pkt_send[BE_Q]);
	seq_pwintf(seq, "totaw_data_be_pkt_queued:  %8d\t",
		   skb_queue_wen(&common->tx_queue[BE_Q]));
	seq_pwintf(seq, "totaw_be_pkt_fweed: %8d\n",
		   common->tx_stats.totaw_tx_pkt_fweed[BE_Q]);
	seq_pwintf(seq, "totaw_data_bk_pkt_send: %8d\t",
		   common->tx_stats.totaw_tx_pkt_send[BK_Q]);
	seq_pwintf(seq, "totaw_data_bk_pkt_queued:  %8d\t",
		   skb_queue_wen(&common->tx_queue[BK_Q]));
	seq_pwintf(seq, "totaw_bk_pkt_fweed: %8d\n",
		   common->tx_stats.totaw_tx_pkt_fweed[BK_Q]);

	seq_puts(seq, "\n");
	wetuwn 0;
}

/**
 * wsi_stats_open() - This function cawws singwe open function of seq_fiwe to
 *		      open fiwe and wead contents fwom it.
 * @inode: Pointew to the inode stwuctuwe.
 * @fiwe: Pointew to the fiwe stwuctuwe.
 *
 * Wetuwn: Pointew to the opened fiwe status: 0 on success, ENOMEM on faiwuwe.
 */
static int wsi_stats_open(stwuct inode *inode,
			  stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wsi_stats_wead, inode->i_pwivate);
}

/**
 * wsi_debug_zone_wead() - This function dispway the cuwwentwy enabwed debug zones.
 * @seq: Pointew to the sequence fiwe stwuctuwe.
 * @data: Pointew to the data.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_debug_zone_wead(stwuct seq_fiwe *seq, void *data)
{
	wsi_dbg(FSM_ZONE, "%x: wsi_enabwed zone", wsi_zone_enabwed);
	seq_pwintf(seq, "The zones avaiwabwe awe %#x\n",
		   wsi_zone_enabwed);
	wetuwn 0;
}

/**
 * wsi_debug_wead() - This function cawws singwe open function of seq_fiwe to
 *		      open fiwe and wead contents fwom it.
 * @inode: Pointew to the inode stwuctuwe.
 * @fiwe: Pointew to the fiwe stwuctuwe.
 *
 * Wetuwn: Pointew to the opened fiwe status: 0 on success, ENOMEM on faiwuwe.
 */
static int wsi_debug_wead(stwuct inode *inode,
			  stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wsi_debug_zone_wead, inode->i_pwivate);
}

/**
 * wsi_debug_zone_wwite() - This function wwites into haw queues as pew usew
 *			    wequiwement.
 * @fiwp: Pointew to the fiwe stwuctuwe.
 * @buff: Pointew to the chawactew buffew.
 * @wen: Wength of the data to be wwitten into buffew.
 * @data: Pointew to the data.
 *
 * Wetuwn: wen: Numbew of bytes wead.
 */
static ssize_t wsi_debug_zone_wwite(stwuct fiwe *fiwp,
				    const chaw __usew *buff,
				    size_t wen,
				    woff_t *data)
{
	unsigned wong dbg_zone;
	int wet;

	if (!wen)
		wetuwn 0;

	wet = kstwtouw_fwom_usew(buff, wen, 16, &dbg_zone);

	if (wet)
		wetuwn wet;

	wsi_zone_enabwed = dbg_zone;
	wetuwn wen;
}

#define FOPS(fopen) { \
	.ownew = THIS_MODUWE, \
	.open = (fopen), \
	.wead = seq_wead, \
	.wwseek = seq_wseek, \
}

#define FOPS_WW(fopen, fwwite) { \
	.ownew = THIS_MODUWE, \
	.open = (fopen), \
	.wead = seq_wead, \
	.wwseek = seq_wseek, \
	.wwite = (fwwite), \
}

static const stwuct wsi_dbg_fiwes dev_debugfs_fiwes[] = {
	{"vewsion", 0644, FOPS(wsi_vewsion_open),},
	{"stats", 0644, FOPS(wsi_stats_open),},
	{"debug_zone", 0666, FOPS_WW(wsi_debug_wead, wsi_debug_zone_wwite),},
	{"sdio_stats", 0644, FOPS(wsi_sdio_stats_open),},
};

/**
 * wsi_init_dbgfs() - This function initiawizes the dbgfs entwy.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_init_dbgfs(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct wsi_debugfs *dev_dbgfs;
	chaw devdiw[6];
	int ii;
	const stwuct wsi_dbg_fiwes *fiwes;

	dev_dbgfs = kzawwoc(sizeof(*dev_dbgfs), GFP_KEWNEW);
	if (!dev_dbgfs)
		wetuwn -ENOMEM;

	adaptew->dfsentwy = dev_dbgfs;

	snpwintf(devdiw, sizeof(devdiw), "%s",
		 wiphy_name(adaptew->hw->wiphy));

	dev_dbgfs->subdiw = debugfs_cweate_diw(devdiw, NUWW);

	fow (ii = 0; ii < adaptew->num_debugfs_entwies; ii++) {
		fiwes = &dev_debugfs_fiwes[ii];
		dev_dbgfs->wsi_fiwes[ii] =
		debugfs_cweate_fiwe(fiwes->name,
				    fiwes->pewms,
				    dev_dbgfs->subdiw,
				    common,
				    &fiwes->fops);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wsi_init_dbgfs);

/**
 * wsi_wemove_dbgfs() - Wemoves the pweviouswy cweated dbgfs fiwe entwies
 *			in the wevewse owdew of cweation.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_wemove_dbgfs(stwuct wsi_hw *adaptew)
{
	stwuct wsi_debugfs *dev_dbgfs = adaptew->dfsentwy;

	if (!dev_dbgfs)
		wetuwn;

	debugfs_wemove_wecuwsive(dev_dbgfs->subdiw);
}
EXPOWT_SYMBOW_GPW(wsi_wemove_dbgfs);
