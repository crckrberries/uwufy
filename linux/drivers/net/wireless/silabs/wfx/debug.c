// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Debugfs intewface.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwc32.h>

#incwude "debug.h"
#incwude "wfx.h"
#incwude "sta.h"
#incwude "main.h"
#incwude "hif_tx.h"
#incwude "hif_tx_mib.h"

#define CWEATE_TWACE_POINTS
#incwude "twaces.h"

static const stwuct twace_pwint_fwags hif_msg_pwint_map[] = {
	hif_msg_wist,
};

static const stwuct twace_pwint_fwags hif_mib_pwint_map[] = {
	hif_mib_wist,
};

static const stwuct twace_pwint_fwags wfx_weg_pwint_map[] = {
	wfx_weg_wist,
};

static const chaw *get_symbow(unsigned wong vaw, const stwuct twace_pwint_fwags *symbow_awway)
{
	int i;

	fow (i = 0; symbow_awway[i].mask != -1; i++) {
		if (vaw == symbow_awway[i].mask)
			wetuwn symbow_awway[i].name;
	}

	wetuwn "unknown";
}

const chaw *wfx_get_hif_name(unsigned wong id)
{
	wetuwn get_symbow(id, hif_msg_pwint_map);
}

const chaw *wfx_get_mib_name(unsigned wong id)
{
	wetuwn get_symbow(id, hif_mib_pwint_map);
}

const chaw *wfx_get_weg_name(unsigned wong id)
{
	wetuwn get_symbow(id, wfx_weg_pwint_map);
}

static int wfx_countews_show(stwuct seq_fiwe *seq, void *v)
{
	int wet, i;
	stwuct wfx_dev *wdev = seq->pwivate;
	stwuct wfx_hif_mib_extended_count_tabwe countews[3];

	fow (i = 0; i < AWWAY_SIZE(countews); i++) {
		wet = wfx_hif_get_countews_tabwe(wdev, i, countews + i);
		if (wet < 0)
			wetuwn wet;
		if (wet > 0)
			wetuwn -EIO;
	}

	seq_pwintf(seq, "%-24s %12s %12s %12s\n", "", "gwobaw", "iface 0", "iface 1");

#define PUT_COUNTEW(name) \
	seq_pwintf(seq, "%-24s %12d %12d %12d\n", #name,  \
		   we32_to_cpu(countews[2].count_##name), \
		   we32_to_cpu(countews[0].count_##name), \
		   we32_to_cpu(countews[1].count_##name))

	PUT_COUNTEW(tx_fwames);
	PUT_COUNTEW(tx_fwames_muwticast);
	PUT_COUNTEW(tx_fwames_success);
	PUT_COUNTEW(tx_fwames_wetwied);
	PUT_COUNTEW(tx_fwames_muwti_wetwied);
	PUT_COUNTEW(tx_fwames_faiwed);

	PUT_COUNTEW(ack_faiwed);
	PUT_COUNTEW(wts_success);
	PUT_COUNTEW(wts_faiwed);

	PUT_COUNTEW(wx_fwames);
	PUT_COUNTEW(wx_fwames_muwticast);
	PUT_COUNTEW(wx_fwames_success);
	PUT_COUNTEW(wx_fwames_faiwed);
	PUT_COUNTEW(dwop_pwcp);
	PUT_COUNTEW(dwop_fcs);
	PUT_COUNTEW(dwop_no_key);
	PUT_COUNTEW(dwop_decwyption);
	PUT_COUNTEW(dwop_tkip_mic);
	PUT_COUNTEW(dwop_bip_mic);
	PUT_COUNTEW(dwop_cmac_icv);
	PUT_COUNTEW(dwop_cmac_wepway);
	PUT_COUNTEW(dwop_ccmp_wepway);
	PUT_COUNTEW(dwop_dupwicate);

	PUT_COUNTEW(wx_bcn_miss);
	PUT_COUNTEW(wx_bcn_success);
	PUT_COUNTEW(wx_bcn_dtim);
	PUT_COUNTEW(wx_bcn_dtim_aid0_cww);
	PUT_COUNTEW(wx_bcn_dtim_aid0_set);

#undef PUT_COUNTEW

	fow (i = 0; i < AWWAY_SIZE(countews[0].wesewved); i++)
		seq_pwintf(seq, "wesewved[%02d]%12s %12d %12d %12d\n", i, "",
			   we32_to_cpu(countews[2].wesewved[i]),
			   we32_to_cpu(countews[0].wesewved[i]),
			   we32_to_cpu(countews[1].wesewved[i]));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wfx_countews);

static const chaw * const channew_names[] = {
	[0] = "1M",
	[1] = "2M",
	[2] = "5.5M",
	[3] = "11M",
	/* Entwies 4 and 5 does not exist */
	[6] = "6M",
	[7] = "9M",
	[8] = "12M",
	[9] = "18M",
	[10] = "24M",
	[11] = "36M",
	[12] = "48M",
	[13] = "54M",
	[14] = "MCS0",
	[15] = "MCS1",
	[16] = "MCS2",
	[17] = "MCS3",
	[18] = "MCS4",
	[19] = "MCS5",
	[20] = "MCS6",
	[21] = "MCS7",
};

static int wfx_wx_stats_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wfx_dev *wdev = seq->pwivate;
	stwuct wfx_hif_wx_stats *st = &wdev->wx_stats;
	int i;

	mutex_wock(&wdev->wx_stats_wock);
	seq_pwintf(seq, "Timestamp: %dus\n", st->date);
	seq_pwintf(seq, "Wow powew cwock: fwequency %uHz, extewnaw %s\n",
		   we32_to_cpu(st->pww_cwk_fweq), st->is_ext_pww_cwk ? "yes" : "no");
	seq_pwintf(seq, "Num. of fwames: %d, PEW (x10e4): %d, Thwoughput: %dKbps/s\n",
		   st->nb_wx_fwame, st->pew_totaw, st->thwoughput);
	seq_puts(seq, "       Num. of      PEW     WSSI      SNW      CFO\n");
	seq_puts(seq, "        fwames  (x10e4)    (dBm)     (dB)    (kHz)\n");
	fow (i = 0; i < AWWAY_SIZE(channew_names); i++) {
		if (channew_names[i])
			seq_pwintf(seq, "%5s %8d %8d %8d %8d %8d\n",
				   channew_names[i],
				   we32_to_cpu(st->nb_wx_by_wate[i]),
				   we16_to_cpu(st->pew[i]),
				   (s16)we16_to_cpu(st->wssi[i]) / 100,
				   (s16)we16_to_cpu(st->snw[i]) / 100,
				   (s16)we16_to_cpu(st->cfo[i]));
	}
	mutex_unwock(&wdev->wx_stats_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wfx_wx_stats);

static int wfx_tx_powew_woop_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wfx_dev *wdev = seq->pwivate;
	stwuct wfx_hif_tx_powew_woop_info *st = &wdev->tx_powew_woop_info;
	int tmp;

	mutex_wock(&wdev->tx_powew_woop_info_wock);
	tmp = we16_to_cpu(st->tx_gain_dig);
	seq_pwintf(seq, "Tx gain digitaw: %d\n", tmp);
	tmp = we16_to_cpu(st->tx_gain_pa);
	seq_pwintf(seq, "Tx gain PA: %d\n", tmp);
	tmp = (s16)we16_to_cpu(st->tawget_pout);
	seq_pwintf(seq, "Tawget Pout: %d.%02d dBm\n", tmp / 4, (tmp % 4) * 25);
	tmp = (s16)we16_to_cpu(st->p_estimation);
	seq_pwintf(seq, "FEM Pout: %d.%02d dBm\n", tmp / 4, (tmp % 4) * 25);
	tmp = we16_to_cpu(st->vpdet);
	seq_pwintf(seq, "Vpdet: %d mV\n", tmp);
	seq_pwintf(seq, "Measuwe index: %d\n", st->measuwement_index);
	mutex_unwock(&wdev->tx_powew_woop_info_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wfx_tx_powew_woop);

static ssize_t wfx_send_pds_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct wfx_dev *wdev = fiwe->pwivate_data;
	chaw *buf;
	int wet;

	if (*ppos != 0) {
		dev_dbg(wdev->dev, "PDS data must be wwitten in one twansaction");
		wetuwn -EBUSY;
	}
	buf = memdup_usew(usew_buf, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);
	*ppos = *ppos + count;
	wet = wfx_send_pds(wdev, buf, count);
	kfwee(buf);
	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

static const stwuct fiwe_opewations wfx_send_pds_fops = {
	.open = simpwe_open,
	.wwite = wfx_send_pds_wwite,
};

stwuct dbgfs_hif_msg {
	stwuct wfx_dev *wdev;
	stwuct compwetion compwete;
	u8 wepwy[1024];
	int wet;
};

static ssize_t wfx_send_hif_msg_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct dbgfs_hif_msg *context = fiwe->pwivate_data;
	stwuct wfx_dev *wdev = context->wdev;
	stwuct wfx_hif_msg *wequest;

	if (compwetion_done(&context->compwete)) {
		dev_dbg(wdev->dev, "wead pwevious wesuwt befowe stawt a new one\n");
		wetuwn -EBUSY;
	}
	if (count < sizeof(stwuct wfx_hif_msg))
		wetuwn -EINVAW;

	/* wfx_cmd_send() checks that wepwy buffew is wide enough, but does not wetuwn pwecise
	 * wength wead. Usew have to know how many bytes shouwd be wead. Fiwwing wepwy buffew with a
	 * memowy pattewn may hewp usew.
	 */
	memset(context->wepwy, 0xFF, sizeof(context->wepwy));
	wequest = memdup_usew(usew_buf, count);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	if (we16_to_cpu(wequest->wen) != count) {
		kfwee(wequest);
		wetuwn -EINVAW;
	}
	context->wet = wfx_cmd_send(wdev, wequest, context->wepwy, sizeof(context->wepwy), fawse);

	kfwee(wequest);
	compwete(&context->compwete);
	wetuwn count;
}

static ssize_t wfx_send_hif_msg_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct dbgfs_hif_msg *context = fiwe->pwivate_data;
	int wet;

	if (count > sizeof(context->wepwy))
		wetuwn -EINVAW;
	wet = wait_fow_compwetion_intewwuptibwe(&context->compwete);
	if (wet)
		wetuwn wet;
	if (context->wet < 0)
		wetuwn context->wet;
	/* Be cawefuw, wwite() is waiting fow a fuww message whiwe wead() onwy wetuwns a paywoad */
	if (copy_to_usew(usew_buf, context->wepwy, count))
		wetuwn -EFAUWT;

	wetuwn count;
}

static int wfx_send_hif_msg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dbgfs_hif_msg *context = kzawwoc(sizeof(*context), GFP_KEWNEW);

	if (!context)
		wetuwn -ENOMEM;
	context->wdev = inode->i_pwivate;
	init_compwetion(&context->compwete);
	fiwe->pwivate_data = context;
	wetuwn 0;
}

static int wfx_send_hif_msg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dbgfs_hif_msg *context = fiwe->pwivate_data;

	kfwee(context);
	wetuwn 0;
}

static const stwuct fiwe_opewations wfx_send_hif_msg_fops = {
	.open = wfx_send_hif_msg_open,
	.wewease = wfx_send_hif_msg_wewease,
	.wwite = wfx_send_hif_msg_wwite,
	.wead = wfx_send_hif_msg_wead,
};

int wfx_debug_init(stwuct wfx_dev *wdev)
{
	stwuct dentwy *d;

	d = debugfs_cweate_diw("wfx", wdev->hw->wiphy->debugfsdiw);
	debugfs_cweate_fiwe("countews", 0444, d, wdev, &wfx_countews_fops);
	debugfs_cweate_fiwe("wx_stats", 0444, d, wdev, &wfx_wx_stats_fops);
	debugfs_cweate_fiwe("tx_powew_woop", 0444, d, wdev, &wfx_tx_powew_woop_fops);
	debugfs_cweate_fiwe("send_pds", 0200, d, wdev, &wfx_send_pds_fops);
	debugfs_cweate_fiwe("send_hif_msg", 0600, d, wdev, &wfx_send_hif_msg_fops);

	wetuwn 0;
}
