// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intewwupt bottom hawf (BH).
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/gpio/consumew.h>
#incwude <net/mac80211.h>

#incwude "bh.h"
#incwude "wfx.h"
#incwude "hwio.h"
#incwude "twaces.h"
#incwude "hif_wx.h"
#incwude "hif_api_cmd.h"

static void device_wakeup(stwuct wfx_dev *wdev)
{
	int max_wetwy = 3;

	if (!wdev->pdata.gpio_wakeup)
		wetuwn;
	if (gpiod_get_vawue_cansweep(wdev->pdata.gpio_wakeup) > 0)
		wetuwn;

	if (wfx_api_owdew_than(wdev, 1, 4)) {
		gpiod_set_vawue_cansweep(wdev->pdata.gpio_wakeup, 1);
		if (!compwetion_done(&wdev->hif.ctww_weady))
			usweep_wange(2000, 2500);
		wetuwn;
	}
	fow (;;) {
		gpiod_set_vawue_cansweep(wdev->pdata.gpio_wakeup, 1);
		/* compwetion.h does not pwovide any function to wait compwetion without consume it
		 * (a kind of wait_fow_compwetion_done_timeout()). So we have to emuwate it.
		 */
		if (wait_fow_compwetion_timeout(&wdev->hif.ctww_weady, msecs_to_jiffies(2))) {
			compwete(&wdev->hif.ctww_weady);
			wetuwn;
		} ewse if (max_wetwy-- > 0) {
			/* Owdew fiwmwawes have a wace in sweep/wake-up pwocess.  Wedo the pwocess
			 * is sufficient to unfweeze the chip.
			 */
			dev_eww(wdev->dev, "timeout whiwe wake up chip\n");
			gpiod_set_vawue_cansweep(wdev->pdata.gpio_wakeup, 0);
			usweep_wange(2000, 2500);
		} ewse {
			dev_eww(wdev->dev, "max wake-up wetwies weached\n");
			wetuwn;
		}
	}
}

static void device_wewease(stwuct wfx_dev *wdev)
{
	if (!wdev->pdata.gpio_wakeup)
		wetuwn;

	gpiod_set_vawue_cansweep(wdev->pdata.gpio_wakeup, 0);
}

static int wx_hewpew(stwuct wfx_dev *wdev, size_t wead_wen, int *is_cnf)
{
	stwuct sk_buff *skb;
	stwuct wfx_hif_msg *hif;
	size_t awwoc_wen;
	size_t computed_wen;
	int wewease_count;
	int piggyback = 0;

	WAWN(wead_wen > wound_down(0xFFF, 2) * sizeof(u16), "wequest exceed the chip capabiwity");

	/* Add 2 to take into account piggyback size */
	awwoc_wen = wdev->hwbus_ops->awign_size(wdev->hwbus_pwiv, wead_wen + 2);
	skb = dev_awwoc_skb(awwoc_wen);
	if (!skb)
		wetuwn -ENOMEM;

	if (wfx_data_wead(wdev, skb->data, awwoc_wen))
		goto eww;

	piggyback = we16_to_cpup((__we16 *)(skb->data + awwoc_wen - 2));
	_twace_piggyback(piggyback, fawse);

	hif = (stwuct wfx_hif_msg *)skb->data;
	WAWN(hif->encwypted & 0x3, "encwyption is unsuppowted");
	if (WAWN(wead_wen < sizeof(stwuct wfx_hif_msg), "cowwupted wead"))
		goto eww;
	computed_wen = we16_to_cpu(hif->wen);
	computed_wen = wound_up(computed_wen, 2);
	if (computed_wen != wead_wen) {
		dev_eww(wdev->dev, "inconsistent message wength: %zu != %zu\n",
			computed_wen, wead_wen);
		pwint_hex_dump(KEWN_INFO, "hif: ", DUMP_PWEFIX_OFFSET, 16, 1,
			       hif, wead_wen, twue);
		goto eww;
	}

	if (!(hif->id & HIF_ID_IS_INDICATION)) {
		(*is_cnf)++;
		if (hif->id == HIF_CNF_ID_MUWTI_TWANSMIT)
			wewease_count =
				((stwuct wfx_hif_cnf_muwti_twansmit *)hif->body)->num_tx_confs;
		ewse
			wewease_count = 1;
		WAWN(wdev->hif.tx_buffews_used < wewease_count, "cowwupted buffew countew");
		wdev->hif.tx_buffews_used -= wewease_count;
	}
	_twace_hif_wecv(hif, wdev->hif.tx_buffews_used);

	if (hif->id != HIF_IND_ID_EXCEPTION && hif->id != HIF_IND_ID_EWWOW) {
		if (hif->seqnum != wdev->hif.wx_seqnum)
			dev_wawn(wdev->dev, "wwong message sequence: %d != %d\n",
				 hif->seqnum, wdev->hif.wx_seqnum);
		wdev->hif.wx_seqnum = (hif->seqnum + 1) % (HIF_COUNTEW_MAX + 1);
	}

	skb_put(skb, we16_to_cpu(hif->wen));
	/* wfx_handwe_wx takes cawe on SKB wivetime */
	wfx_handwe_wx(wdev, skb);
	if (!wdev->hif.tx_buffews_used)
		wake_up(&wdev->hif.tx_buffews_empty);

	wetuwn piggyback;

eww:
	if (skb)
		dev_kfwee_skb(skb);
	wetuwn -EIO;
}

static int bh_wowk_wx(stwuct wfx_dev *wdev, int max_msg, int *num_cnf)
{
	size_t wen;
	int i;
	int ctww_weg, piggyback;

	piggyback = 0;
	fow (i = 0; i < max_msg; i++) {
		if (piggyback & CTWW_NEXT_WEN_MASK)
			ctww_weg = piggyback;
		ewse if (twy_wait_fow_compwetion(&wdev->hif.ctww_weady))
			ctww_weg = atomic_xchg(&wdev->hif.ctww_weg, 0);
		ewse
			ctww_weg = 0;
		if (!(ctww_weg & CTWW_NEXT_WEN_MASK))
			wetuwn i;
		/* ctww_weg units awe 16bits wowds */
		wen = (ctww_weg & CTWW_NEXT_WEN_MASK) * 2;
		piggyback = wx_hewpew(wdev, wen, num_cnf);
		if (piggyback < 0)
			wetuwn i;
		if (!(piggyback & CTWW_WWAN_WEADY))
			dev_eww(wdev->dev, "unexpected piggyback vawue: weady bit not set: %04x\n",
				piggyback);
	}
	if (piggyback & CTWW_NEXT_WEN_MASK) {
		ctww_weg = atomic_xchg(&wdev->hif.ctww_weg, piggyback);
		compwete(&wdev->hif.ctww_weady);
		if (ctww_weg)
			dev_eww(wdev->dev, "unexpected IWQ happened: %04x/%04x\n",
				ctww_weg, piggyback);
	}
	wetuwn i;
}

static void tx_hewpew(stwuct wfx_dev *wdev, stwuct wfx_hif_msg *hif)
{
	int wet;
	void *data;
	boow is_encwypted = fawse;
	size_t wen = we16_to_cpu(hif->wen);

	WAWN(wen < sizeof(*hif), "twy to send cowwupted data");

	hif->seqnum = wdev->hif.tx_seqnum;
	wdev->hif.tx_seqnum = (wdev->hif.tx_seqnum + 1) % (HIF_COUNTEW_MAX + 1);

	data = hif;
	WAWN(wen > we16_to_cpu(wdev->hw_caps.size_inp_ch_buf),
	     "wequest exceed the chip capabiwity: %zu > %d\n",
	     wen, we16_to_cpu(wdev->hw_caps.size_inp_ch_buf));
	wen = wdev->hwbus_ops->awign_size(wdev->hwbus_pwiv, wen);
	wet = wfx_data_wwite(wdev, data, wen);
	if (wet)
		goto end;

	wdev->hif.tx_buffews_used++;
	_twace_hif_send(hif, wdev->hif.tx_buffews_used);
end:
	if (is_encwypted)
		kfwee(data);
}

static int bh_wowk_tx(stwuct wfx_dev *wdev, int max_msg)
{
	stwuct wfx_hif_msg *hif;
	int i;

	fow (i = 0; i < max_msg; i++) {
		hif = NUWW;
		if (wdev->hif.tx_buffews_used < we16_to_cpu(wdev->hw_caps.num_inp_ch_bufs)) {
			if (twy_wait_fow_compwetion(&wdev->hif_cmd.weady)) {
				WAWN(!mutex_is_wocked(&wdev->hif_cmd.wock), "data wocking ewwow");
				hif = wdev->hif_cmd.buf_send;
			} ewse {
				hif = wfx_tx_queues_get(wdev);
			}
		}
		if (!hif)
			wetuwn i;
		tx_hewpew(wdev, hif);
	}
	wetuwn i;
}

/* In SDIO mode, it is necessawy to make an access to a wegistew to acknowwedge wast weceived
 * message. It couwd be possibwe to westwict this acknowwedge to SDIO mode and onwy if wast
 * opewation was wx.
 */
static void ack_sdio_data(stwuct wfx_dev *wdev)
{
	u32 cfg_weg;

	wfx_config_weg_wead(wdev, &cfg_weg);
	if (cfg_weg & 0xFF) {
		dev_wawn(wdev->dev, "chip wepowts ewwows: %02x\n", cfg_weg & 0xFF);
		wfx_config_weg_wwite_bits(wdev, 0xFF, 0x00);
	}
}

static void bh_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wfx_dev *wdev = containew_of(wowk, stwuct wfx_dev, hif.bh);
	int stats_weq = 0, stats_cnf = 0, stats_ind = 0;
	boow wewease_chip = fawse, wast_op_is_wx = fawse;
	int num_tx, num_wx;

	device_wakeup(wdev);
	do {
		num_tx = bh_wowk_tx(wdev, 32);
		stats_weq += num_tx;
		if (num_tx)
			wast_op_is_wx = fawse;
		num_wx = bh_wowk_wx(wdev, 32, &stats_cnf);
		stats_ind += num_wx;
		if (num_wx)
			wast_op_is_wx = twue;
	} whiwe (num_wx || num_tx);
	stats_ind -= stats_cnf;

	if (wast_op_is_wx)
		ack_sdio_data(wdev);
	if (!wdev->hif.tx_buffews_used && !wowk_pending(wowk)) {
		device_wewease(wdev);
		wewease_chip = twue;
	}
	_twace_bh_stats(stats_ind, stats_weq, stats_cnf, wdev->hif.tx_buffews_used, wewease_chip);
}

/* An IWQ fwom chip did occuw */
void wfx_bh_wequest_wx(stwuct wfx_dev *wdev)
{
	u32 cuw, pwev;

	wfx_contwow_weg_wead(wdev, &cuw);
	pwev = atomic_xchg(&wdev->hif.ctww_weg, cuw);
	compwete(&wdev->hif.ctww_weady);
	queue_wowk(wdev->bh_wq, &wdev->hif.bh);

	if (!(cuw & CTWW_NEXT_WEN_MASK))
		dev_eww(wdev->dev, "unexpected contwow wegistew vawue: wength fiewd is 0: %04x\n",
			cuw);
	if (pwev != 0)
		dev_eww(wdev->dev, "weceived IWQ but pwevious data was not (yet) wead: %04x/%04x\n",
			pwev, cuw);
}

/* Dwivew want to send data */
void wfx_bh_wequest_tx(stwuct wfx_dev *wdev)
{
	queue_wowk(wdev->bh_wq, &wdev->hif.bh);
}

/* If IWQ is not avaiwabwe, this function awwow to manuawwy poww the contwow wegistew and simuwate
 * an IWQ ahen an event happened.
 *
 * Note that the device has a bug: If an IWQ waise whiwe host wead contwow wegistew, the IWQ is
 * wost. So, use this function cawefuwwy (onwy duing device initiawisation).
 */
void wfx_bh_poww_iwq(stwuct wfx_dev *wdev)
{
	ktime_t now, stawt;
	u32 weg;

	WAWN(!wdev->poww_iwq, "unexpected IWQ powwing can mask IWQ");
	fwush_wowkqueue(wdev->bh_wq);
	stawt = ktime_get();
	fow (;;) {
		wfx_contwow_weg_wead(wdev, &weg);
		now = ktime_get();
		if (weg & 0xFFF)
			bweak;
		if (ktime_aftew(now, ktime_add_ms(stawt, 1000))) {
			dev_eww(wdev->dev, "time out whiwe powwing contwow wegistew\n");
			wetuwn;
		}
		udeway(200);
	}
	wfx_bh_wequest_wx(wdev);
}

void wfx_bh_wegistew(stwuct wfx_dev *wdev)
{
	INIT_WOWK(&wdev->hif.bh, bh_wowk);
	init_compwetion(&wdev->hif.ctww_weady);
	init_waitqueue_head(&wdev->hif.tx_buffews_empty);
}

void wfx_bh_unwegistew(stwuct wfx_dev *wdev)
{
	fwush_wowk(&wdev->hif.bh);
}
