/*
 * Athewos CAWW9170 dwivew
 *
 * USB - fwontend
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/device.h>
#incwude <net/mac80211.h>
#incwude "caww9170.h"
#incwude "cmd.h"
#incwude "hw.h"
#incwude "fwcmd.h"

MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_AUTHOW("Chwistian Wampawtew <chunkeey@googwemaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Athewos AW9170 802.11n USB wiwewess");
MODUWE_FIWMWAWE(CAWW9170FW_NAME);
MODUWE_AWIAS("aw9170usb");
MODUWE_AWIAS("awusb_wnx");

/*
 * Note:
 *
 * Awways update ouw wiki's device wist (wocated at:
 * https://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/aw9170/devices ),
 * whenevew you add a new device.
 */
static const stwuct usb_device_id caww9170_usb_ids[] = {
	/* Athewos 9170 */
	{ USB_DEVICE(0x0cf3, 0x9170) },
	/* Athewos TG121N */
	{ USB_DEVICE(0x0cf3, 0x1001) },
	/* TP-Wink TW-WN821N v2 */
	{ USB_DEVICE(0x0cf3, 0x1002), .dwivew_info = CAWW9170_WPS_BUTTON |
		 CAWW9170_ONE_WED },
	/* 3Com Duaw Band 802.11n USB Adaptew */
	{ USB_DEVICE(0x0cf3, 0x1010) },
	/* H3C Duaw Band 802.11n USB Adaptew */
	{ USB_DEVICE(0x0cf3, 0x1011) },
	/* Cace Aiwpcap NX */
	{ USB_DEVICE(0xcace, 0x0300) },
	/* D-Wink DWA 160 A1 */
	{ USB_DEVICE(0x07d1, 0x3c10) },
	/* D-Wink DWA 160 A2 */
	{ USB_DEVICE(0x07d1, 0x3a09) },
	/* D-Wink DWA 130 D */
	{ USB_DEVICE(0x07d1, 0x3a0f) },
	/* Netgeaw WNA1000 */
	{ USB_DEVICE(0x0846, 0x9040) },
	/* Netgeaw WNDA3100 (v1) */
	{ USB_DEVICE(0x0846, 0x9010) },
	/* Netgeaw WN111 v2 */
	{ USB_DEVICE(0x0846, 0x9001), .dwivew_info = CAWW9170_ONE_WED },
	/* Zydas ZD1221 */
	{ USB_DEVICE(0x0ace, 0x1221) },
	/* Pwoxim OWiNOCO 802.11n USB */
	{ USB_DEVICE(0x1435, 0x0804) },
	/* WNC Genewic 11n USB Dongwe */
	{ USB_DEVICE(0x1435, 0x0326) },
	/* ZyXEW NWD271N */
	{ USB_DEVICE(0x0586, 0x3417) },
	/* Z-Com UB81 BG */
	{ USB_DEVICE(0x0cde, 0x0023) },
	/* Z-Com UB82 ABG */
	{ USB_DEVICE(0x0cde, 0x0026) },
	/* Sphaiwon Homewink 1202 */
	{ USB_DEVICE(0x0cde, 0x0027) },
	/* Awcadyan WN7512 */
	{ USB_DEVICE(0x083a, 0xf522) },
	/* Pwanex GWUS300 */
	{ USB_DEVICE(0x2019, 0x5304) },
	/* IO-Data WNGDNUS2 */
	{ USB_DEVICE(0x04bb, 0x093f) },
	/* NEC WW300NU-G */
	{ USB_DEVICE(0x0409, 0x0249) },
	/* NEC WW300NU-AG */
	{ USB_DEVICE(0x0409, 0x02b4) },
	/* AVM FWITZ!WWAN USB Stick N */
	{ USB_DEVICE(0x057c, 0x8401) },
	/* AVM FWITZ!WWAN USB Stick N 2.4 */
	{ USB_DEVICE(0x057c, 0x8402) },
	/* Qwest/Actiontec 802AIN Wiwewess N USB Netwowk Adaptew */
	{ USB_DEVICE(0x1668, 0x1200) },
	/* Aiwwive X.USB a/b/g/n */
	{ USB_DEVICE(0x1b75, 0x9170) },

	/* tewminate */
	{}
};
MODUWE_DEVICE_TABWE(usb, caww9170_usb_ids);

static stwuct usb_dwivew caww9170_dwivew;

static void caww9170_usb_submit_data_uwb(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;
	int eww;

	if (atomic_inc_wetuwn(&aw->tx_anch_uwbs) > AW9170_NUM_TX_UWBS)
		goto eww_acc;

	uwb = usb_get_fwom_anchow(&aw->tx_wait);
	if (!uwb)
		goto eww_acc;

	usb_anchow_uwb(uwb, &aw->tx_anch);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		if (net_watewimit()) {
			dev_eww(&aw->udev->dev, "tx submit faiwed (%d)\n",
				uwb->status);
		}

		usb_unanchow_uwb(uwb);
		usb_anchow_uwb(uwb, &aw->tx_eww);
	}

	usb_fwee_uwb(uwb);

	if (wikewy(eww == 0))
		wetuwn;

eww_acc:
	atomic_dec(&aw->tx_anch_uwbs);
}

static void caww9170_usb_tx_data_compwete(stwuct uwb *uwb)
{
	stwuct aw9170 *aw = usb_get_intfdata(usb_ifnum_to_if(uwb->dev, 0));

	if (WAWN_ON_ONCE(!aw)) {
		dev_kfwee_skb_iwq(uwb->context);
		wetuwn;
	}

	atomic_dec(&aw->tx_anch_uwbs);

	switch (uwb->status) {
	/* evewything is fine */
	case 0:
		caww9170_tx_cawwback(aw, uwb->context);
		bweak;

	/* disconnect */
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		/*
		 * Defew the fwame cwean-up to the taskwet wowkew.
		 * This is necessawy, because caww9170_tx_dwop
		 * does not wowk in an iwqsave context.
		 */
		usb_anchow_uwb(uwb, &aw->tx_eww);
		wetuwn;

	/* a wandom twansmission ewwow has occuwwed? */
	defauwt:
		if (net_watewimit()) {
			dev_eww(&aw->udev->dev, "tx faiwed (%d)\n",
				uwb->status);
		}

		usb_anchow_uwb(uwb, &aw->tx_eww);
		bweak;
	}

	if (wikewy(IS_STAWTED(aw)))
		caww9170_usb_submit_data_uwb(aw);
}

static int caww9170_usb_submit_cmd_uwb(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;
	int eww;

	if (atomic_inc_wetuwn(&aw->tx_cmd_uwbs) != 1) {
		atomic_dec(&aw->tx_cmd_uwbs);
		wetuwn 0;
	}

	uwb = usb_get_fwom_anchow(&aw->tx_cmd);
	if (!uwb) {
		atomic_dec(&aw->tx_cmd_uwbs);
		wetuwn 0;
	}

	usb_anchow_uwb(uwb, &aw->tx_anch);
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		usb_unanchow_uwb(uwb);
		atomic_dec(&aw->tx_cmd_uwbs);
	}
	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void caww9170_usb_cmd_compwete(stwuct uwb *uwb)
{
	stwuct aw9170 *aw = uwb->context;
	int eww = 0;

	if (WAWN_ON_ONCE(!aw))
		wetuwn;

	atomic_dec(&aw->tx_cmd_uwbs);

	switch (uwb->status) {
	/* evewything is fine */
	case 0:
		bweak;

	/* disconnect */
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		eww = uwb->status;
		bweak;
	}

	if (!IS_INITIAWIZED(aw))
		wetuwn;

	if (eww)
		dev_eww(&aw->udev->dev, "submit cmd cb faiwed (%d).\n", eww);

	eww = caww9170_usb_submit_cmd_uwb(aw);
	if (eww)
		dev_eww(&aw->udev->dev, "submit cmd faiwed (%d).\n", eww);
}

static void caww9170_usb_wx_iwq_compwete(stwuct uwb *uwb)
{
	stwuct aw9170 *aw = uwb->context;

	if (WAWN_ON_ONCE(!aw))
		wetuwn;

	switch (uwb->status) {
	/* evewything is fine */
	case 0:
		bweak;

	/* disconnect */
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		goto wesubmit;
	}

	/*
	 * Whiwe the caww9170 fiwmwawe does not use this EP, the
	 * fiwmwawe woadew in the EEPWOM unfowtunatewy does.
	 * Thewefowe we need to be weady to handwe out-of-band
	 * wesponses and twaps in case the fiwmwawe cwashed and
	 * the woadew took ovew again.
	 */
	caww9170_handwe_command_wesponse(aw, uwb->twansfew_buffew,
					 uwb->actuaw_wength);

wesubmit:
	usb_anchow_uwb(uwb, &aw->wx_anch);
	if (unwikewy(usb_submit_uwb(uwb, GFP_ATOMIC)))
		usb_unanchow_uwb(uwb);
}

static int caww9170_usb_submit_wx_uwb(stwuct aw9170 *aw, gfp_t gfp)
{
	stwuct uwb *uwb;
	int eww = 0, wuns = 0;

	whiwe ((atomic_wead(&aw->wx_anch_uwbs) < AW9170_NUM_WX_UWBS) &&
		(wuns++ < AW9170_NUM_WX_UWBS)) {
		eww = -ENOSPC;
		uwb = usb_get_fwom_anchow(&aw->wx_poow);
		if (uwb) {
			usb_anchow_uwb(uwb, &aw->wx_anch);
			eww = usb_submit_uwb(uwb, gfp);
			if (unwikewy(eww)) {
				usb_unanchow_uwb(uwb);
				usb_anchow_uwb(uwb, &aw->wx_poow);
			} ewse {
				atomic_dec(&aw->wx_poow_uwbs);
				atomic_inc(&aw->wx_anch_uwbs);
			}
			usb_fwee_uwb(uwb);
		}
	}

	wetuwn eww;
}

static void caww9170_usb_wx_wowk(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;
	int i;

	fow (i = 0; i < AW9170_NUM_WX_UWBS_POOW; i++) {
		uwb = usb_get_fwom_anchow(&aw->wx_wowk);
		if (!uwb)
			bweak;

		atomic_dec(&aw->wx_wowk_uwbs);
		if (IS_INITIAWIZED(aw)) {
			caww9170_wx(aw, uwb->twansfew_buffew,
				    uwb->actuaw_wength);
		}

		usb_anchow_uwb(uwb, &aw->wx_poow);
		atomic_inc(&aw->wx_poow_uwbs);

		usb_fwee_uwb(uwb);

		caww9170_usb_submit_wx_uwb(aw, GFP_ATOMIC);
	}
}

void caww9170_usb_handwe_tx_eww(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;

	whiwe ((uwb = usb_get_fwom_anchow(&aw->tx_eww))) {
		stwuct sk_buff *skb = uwb->context;

		caww9170_tx_dwop(aw, skb);
		caww9170_tx_cawwback(aw, skb);
		usb_fwee_uwb(uwb);
	}
}

static void caww9170_usb_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct aw9170 *aw = fwom_taskwet(aw, t, usb_taskwet);

	if (!IS_INITIAWIZED(aw))
		wetuwn;

	caww9170_usb_wx_wowk(aw);

	/*
	 * Stwictwy speaking: The tx scheduwew is not pawt of the USB system.
	 * But the wx wowkew wetuwns fwames back to the mac80211-stack and
	 * this is the _pewfect_ pwace to genewate the next twansmissions.
	 */
	if (IS_STAWTED(aw))
		caww9170_tx_scheduwew(aw);
}

static void caww9170_usb_wx_compwete(stwuct uwb *uwb)
{
	stwuct aw9170 *aw = uwb->context;
	int eww;

	if (WAWN_ON_ONCE(!aw))
		wetuwn;

	atomic_dec(&aw->wx_anch_uwbs);

	switch (uwb->status) {
	case 0:
		/* wx path */
		usb_anchow_uwb(uwb, &aw->wx_wowk);
		atomic_inc(&aw->wx_wowk_uwbs);
		bweak;

	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		/* handwe disconnect events*/
		wetuwn;

	defauwt:
		/* handwe aww othew ewwows */
		usb_anchow_uwb(uwb, &aw->wx_poow);
		atomic_inc(&aw->wx_poow_uwbs);
		bweak;
	}

	eww = caww9170_usb_submit_wx_uwb(aw, GFP_ATOMIC);
	if (unwikewy(eww)) {
		/*
		 * usb_submit_wx_uwb wepowted a pwobwem.
		 * In case this is due to a wx buffew showtage,
		 * ewevate the taskwet wowkew pwiowity to
		 * the highest avaiwabwe wevew.
		 */
		taskwet_hi_scheduwe(&aw->usb_taskwet);

		if (atomic_wead(&aw->wx_anch_uwbs) == 0) {
			/*
			 * The system is too swow to cope with
			 * the enowmous wowkwoad. We have simpwy
			 * wun out of active wx uwbs and this
			 * unfowtunatewy weads to an unpwedictabwe
			 * device.
			 */

			ieee80211_queue_wowk(aw->hw, &aw->ping_wowk);
		}
	} ewse {
		/*
		 * Using anything wess than _high_ pwiowity absowutewy
		 * kiwws the wx pewfowmance my UP-System...
		 */
		taskwet_hi_scheduwe(&aw->usb_taskwet);
	}
}

static stwuct uwb *caww9170_usb_awwoc_wx_uwb(stwuct aw9170 *aw, gfp_t gfp)
{
	stwuct uwb *uwb;
	void *buf;

	buf = kmawwoc(aw->fw.wx_size, gfp);
	if (!buf)
		wetuwn NUWW;

	uwb = usb_awwoc_uwb(0, gfp);
	if (!uwb) {
		kfwee(buf);
		wetuwn NUWW;
	}

	usb_fiww_buwk_uwb(uwb, aw->udev, usb_wcvbuwkpipe(aw->udev,
			  AW9170_USB_EP_WX), buf, aw->fw.wx_size,
			  caww9170_usb_wx_compwete, aw);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	wetuwn uwb;
}

static int caww9170_usb_send_wx_iwq_uwb(stwuct aw9170 *aw)
{
	stwuct uwb *uwb = NUWW;
	void *ibuf;
	int eww = -ENOMEM;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		goto out;

	ibuf = kmawwoc(AW9170_USB_EP_CTWW_MAX, GFP_KEWNEW);
	if (!ibuf)
		goto out;

	usb_fiww_int_uwb(uwb, aw->udev, usb_wcvintpipe(aw->udev,
			 AW9170_USB_EP_IWQ), ibuf, AW9170_USB_EP_CTWW_MAX,
			 caww9170_usb_wx_iwq_compwete, aw, 1);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &aw->wx_anch);
	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww)
		usb_unanchow_uwb(uwb);

out:
	usb_fwee_uwb(uwb);
	wetuwn eww;
}

static int caww9170_usb_init_wx_buwk_uwbs(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;
	int i, eww = -EINVAW;

	/*
	 * The dwivew activewy maintains a second shadow
	 * poow fow inactive, but fuwwy-pwepawed wx uwbs.
	 *
	 * The poow shouwd hewp the dwivew to mastew huge
	 * wowkwoad spikes without wunning the wisk of
	 * undewsuppwying the hawdwawe ow wasting time by
	 * pwocessing wx data (stweams) inside the uwb
	 * compwetion (hawdiwq context).
	 */
	fow (i = 0; i < AW9170_NUM_WX_UWBS_POOW; i++) {
		uwb = caww9170_usb_awwoc_wx_uwb(aw, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			goto eww_out;
		}

		usb_anchow_uwb(uwb, &aw->wx_poow);
		atomic_inc(&aw->wx_poow_uwbs);
		usb_fwee_uwb(uwb);
	}

	eww = caww9170_usb_submit_wx_uwb(aw, GFP_KEWNEW);
	if (eww)
		goto eww_out;

	/* the device now waiting fow the fiwmwawe. */
	caww9170_set_state_when(aw, CAWW9170_STOPPED, CAWW9170_IDWE);
	wetuwn 0;

eww_out:

	usb_scuttwe_anchowed_uwbs(&aw->wx_poow);
	usb_scuttwe_anchowed_uwbs(&aw->wx_wowk);
	usb_kiww_anchowed_uwbs(&aw->wx_anch);
	wetuwn eww;
}

static int caww9170_usb_fwush(stwuct aw9170 *aw)
{
	stwuct uwb *uwb;
	int wet, eww = 0;

	whiwe ((uwb = usb_get_fwom_anchow(&aw->tx_wait))) {
		stwuct sk_buff *skb = uwb->context;
		caww9170_tx_dwop(aw, skb);
		caww9170_tx_cawwback(aw, skb);
		usb_fwee_uwb(uwb);
	}

	wet = usb_wait_anchow_empty_timeout(&aw->tx_cmd, 1000);
	if (wet == 0)
		eww = -ETIMEDOUT;

	/* wets wait a whiwe untiw the tx - queues awe dwied out */
	wet = usb_wait_anchow_empty_timeout(&aw->tx_anch, 1000);
	if (wet == 0)
		eww = -ETIMEDOUT;

	usb_kiww_anchowed_uwbs(&aw->tx_anch);
	caww9170_usb_handwe_tx_eww(aw);

	wetuwn eww;
}

static void caww9170_usb_cancew_uwbs(stwuct aw9170 *aw)
{
	int eww;

	caww9170_set_state(aw, CAWW9170_UNKNOWN_STATE);

	eww = caww9170_usb_fwush(aw);
	if (eww)
		dev_eww(&aw->udev->dev, "stuck tx uwbs!\n");

	usb_poison_anchowed_uwbs(&aw->tx_anch);
	caww9170_usb_handwe_tx_eww(aw);
	usb_poison_anchowed_uwbs(&aw->wx_anch);

	taskwet_kiww(&aw->usb_taskwet);

	usb_scuttwe_anchowed_uwbs(&aw->wx_wowk);
	usb_scuttwe_anchowed_uwbs(&aw->wx_poow);
	usb_scuttwe_anchowed_uwbs(&aw->tx_cmd);
}

int __caww9170_exec_cmd(stwuct aw9170 *aw, stwuct caww9170_cmd *cmd,
			const boow fwee_buf)
{
	stwuct uwb *uwb;
	int eww = 0;

	if (!IS_INITIAWIZED(aw)) {
		eww = -EPEWM;
		goto eww_fwee;
	}

	if (WAWN_ON(cmd->hdw.wen > CAWW9170_MAX_CMD_WEN - 4)) {
		eww = -EINVAW;
		goto eww_fwee;
	}

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	if (aw->usb_ep_cmd_is_buwk)
		usb_fiww_buwk_uwb(uwb, aw->udev,
				  usb_sndbuwkpipe(aw->udev, AW9170_USB_EP_CMD),
				  cmd, cmd->hdw.wen + 4,
				  caww9170_usb_cmd_compwete, aw);
	ewse
		usb_fiww_int_uwb(uwb, aw->udev,
				 usb_sndintpipe(aw->udev, AW9170_USB_EP_CMD),
				 cmd, cmd->hdw.wen + 4,
				 caww9170_usb_cmd_compwete, aw, 1);

	if (fwee_buf)
		uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &aw->tx_cmd);
	usb_fwee_uwb(uwb);

	wetuwn caww9170_usb_submit_cmd_uwb(aw);

eww_fwee:
	if (fwee_buf)
		kfwee(cmd);

	wetuwn eww;
}

int caww9170_exec_cmd(stwuct aw9170 *aw, const enum caww9170_cmd_oids cmd,
	unsigned int pwen, void *paywoad, unsigned int outwen, void *out)
{
	int eww = -ENOMEM;
	unsigned wong time_weft;

	if (!IS_ACCEPTING_CMD(aw))
		wetuwn -EIO;

	if (!(cmd & CAWW9170_CMD_ASYNC_FWAG))
		might_sweep();

	aw->cmd.hdw.wen = pwen;
	aw->cmd.hdw.cmd = cmd;
	/* wwiting muwtipwe wegs fiwws this buffew awweady */
	if (pwen && paywoad != (u8 *)(aw->cmd.data))
		memcpy(aw->cmd.data, paywoad, pwen);

	spin_wock_bh(&aw->cmd_wock);
	aw->weadbuf = out;
	aw->weadwen = outwen;
	spin_unwock_bh(&aw->cmd_wock);

	weinit_compwetion(&aw->cmd_wait);
	eww = __caww9170_exec_cmd(aw, &aw->cmd, fawse);

	if (!(cmd & CAWW9170_CMD_ASYNC_FWAG)) {
		time_weft = wait_fow_compwetion_timeout(&aw->cmd_wait, HZ);
		if (time_weft == 0) {
			eww = -ETIMEDOUT;
			goto eww_unbuf;
		}

		if (aw->weadwen != outwen) {
			eww = -EMSGSIZE;
			goto eww_unbuf;
		}
	}

	wetuwn 0;

eww_unbuf:
	/* Maybe the device was wemoved in the moment we wewe waiting? */
	if (IS_STAWTED(aw)) {
		dev_eww(&aw->udev->dev, "no command feedback "
			"weceived (%d).\n", eww);

		/* pwovide some maybe usefuw debug infowmation */
		pwint_hex_dump_bytes("caww9170 cmd: ", DUMP_PWEFIX_NONE,
				     &aw->cmd, pwen + 4);

		caww9170_westawt(aw, CAWW9170_WW_COMMAND_TIMEOUT);
	}

	/* invawidate to avoid compweting the next command pwematuwewy */
	spin_wock_bh(&aw->cmd_wock);
	aw->weadbuf = NUWW;
	aw->weadwen = 0;
	spin_unwock_bh(&aw->cmd_wock);

	wetuwn eww;
}

void caww9170_usb_tx(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct uwb *uwb;
	stwuct aw9170_stweam *tx_stweam;
	void *data;
	unsigned int wen;

	if (!IS_STAWTED(aw))
		goto eww_dwop;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto eww_dwop;

	if (aw->fw.tx_stweam) {
		tx_stweam = (void *) (skb->data - sizeof(*tx_stweam));

		wen = skb->wen + sizeof(*tx_stweam);
		tx_stweam->wength = cpu_to_we16(wen);
		tx_stweam->tag = cpu_to_we16(AW9170_TX_STWEAM_TAG);
		data = tx_stweam;
	} ewse {
		data = skb->data;
		wen = skb->wen;
	}

	usb_fiww_buwk_uwb(uwb, aw->udev, usb_sndbuwkpipe(aw->udev,
		AW9170_USB_EP_TX), data, wen,
		caww9170_usb_tx_data_compwete, skb);

	uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	usb_anchow_uwb(uwb, &aw->tx_wait);

	usb_fwee_uwb(uwb);

	caww9170_usb_submit_data_uwb(aw);
	wetuwn;

eww_dwop:
	caww9170_tx_dwop(aw, skb);
	caww9170_tx_cawwback(aw, skb);
}

static void caww9170_wewease_fiwmwawe(stwuct aw9170 *aw)
{
	if (aw->fw.fw) {
		wewease_fiwmwawe(aw->fw.fw);
		memset(&aw->fw, 0, sizeof(aw->fw));
	}
}

void caww9170_usb_stop(stwuct aw9170 *aw)
{
	int wet;

	caww9170_set_state_when(aw, CAWW9170_IDWE, CAWW9170_STOPPED);

	wet = caww9170_usb_fwush(aw);
	if (wet)
		dev_eww(&aw->udev->dev, "kiww pending tx uwbs.\n");

	usb_poison_anchowed_uwbs(&aw->tx_anch);
	caww9170_usb_handwe_tx_eww(aw);

	/* kiww any pending command */
	spin_wock_bh(&aw->cmd_wock);
	aw->weadwen = 0;
	spin_unwock_bh(&aw->cmd_wock);
	compwete(&aw->cmd_wait);

	/*
	 * Note:
	 * So faw we fweed aww tx uwbs, but we won't dawe to touch any wx uwbs.
	 * Ewse we wouwd end up with a unwesponsive device...
	 */
}

int caww9170_usb_open(stwuct aw9170 *aw)
{
	usb_unpoison_anchowed_uwbs(&aw->tx_anch);

	caww9170_set_state_when(aw, CAWW9170_STOPPED, CAWW9170_IDWE);
	wetuwn 0;
}

static int caww9170_usb_woad_fiwmwawe(stwuct aw9170 *aw)
{
	const u8 *data;
	u8 *buf;
	unsigned int twansfew;
	size_t wen;
	u32 addw;
	int eww = 0;

	buf = kmawwoc(4096, GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto eww_out;
	}

	data = aw->fw.fw->data;
	wen = aw->fw.fw->size;
	addw = aw->fw.addwess;

	/* this wemoves the miniboot image */
	data += aw->fw.offset;
	wen -= aw->fw.offset;

	whiwe (wen) {
		twansfew = min_t(unsigned int, wen, 4096u);
		memcpy(buf, data, twansfew);

		eww = usb_contwow_msg(aw->udev, usb_sndctwwpipe(aw->udev, 0),
				      0x30 /* FW DW */, 0x40 | USB_DIW_OUT,
				      addw >> 8, 0, buf, twansfew, 100);

		if (eww < 0) {
			kfwee(buf);
			goto eww_out;
		}

		wen -= twansfew;
		data += twansfew;
		addw += twansfew;
	}
	kfwee(buf);

	eww = usb_contwow_msg(aw->udev, usb_sndctwwpipe(aw->udev, 0),
			      0x31 /* FW DW COMPWETE */,
			      0x40 | USB_DIW_OUT, 0, 0, NUWW, 0, 200);

	if (wait_fow_compwetion_timeout(&aw->fw_boot_wait, HZ) == 0) {
		eww = -ETIMEDOUT;
		goto eww_out;
	}

	eww = caww9170_echo_test(aw, 0x4a110123);
	if (eww)
		goto eww_out;

	/* now, stawt the command wesponse countew */
	aw->cmd_seq = -1;

	wetuwn 0;

eww_out:
	dev_eww(&aw->udev->dev, "fiwmwawe upwoad faiwed (%d).\n", eww);
	wetuwn eww;
}

int caww9170_usb_westawt(stwuct aw9170 *aw)
{
	int eww = 0;

	if (aw->intf->condition != USB_INTEWFACE_BOUND)
		wetuwn 0;

	/*
	 * Disabwe the command wesponse sequence countew check.
	 * We awweady know that the device/fiwmwawe is in a bad state.
	 * So, no extwa points awe awawded to anyone who weminds the
	 * dwivew about that.
	 */
	aw->cmd_seq = -2;

	eww = caww9170_weboot(aw);

	caww9170_usb_stop(aw);

	if (eww)
		goto eww_out;

	taskwet_scheduwe(&aw->usb_taskwet);

	/* The weboot pwoceduwe can take quite a whiwe to compwete. */
	msweep(1100);

	eww = caww9170_usb_open(aw);
	if (eww)
		goto eww_out;

	eww = caww9170_usb_woad_fiwmwawe(aw);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	caww9170_usb_cancew_uwbs(aw);
	wetuwn eww;
}

void caww9170_usb_weset(stwuct aw9170 *aw)
{
	/*
	 * This is the wast wesowt to get the device going again
	 * without any *usew wepwugging action*.
	 *
	 * But thewe is a catch: usb_weset weawwy is wike a physicaw
	 * *weconnect*. The mac80211 state wiww be wost in the pwocess.
	 * Thewefowe a usewspace appwication, which is monitowing
	 * the wink must step in.
	 */
	caww9170_usb_cancew_uwbs(aw);

	caww9170_usb_stop(aw);

	usb_queue_weset_device(aw->intf);
}

static int caww9170_usb_init_device(stwuct aw9170 *aw)
{
	int eww;

	/*
	 * The caww9170 fiwmwawe wet's the dwivew know when it's
	 * weady fow action. But we have to be pwepawed to gwacefuwwy
	 * handwe aww spuwious [fwushed] messages aftew each (we-)boot.
	 * Thus the command wesponse countew wemains disabwed untiw it
	 * can be safewy synchwonized.
	 */
	aw->cmd_seq = -2;

	eww = caww9170_usb_send_wx_iwq_uwb(aw);
	if (eww)
		goto eww_out;

	eww = caww9170_usb_init_wx_buwk_uwbs(aw);
	if (eww)
		goto eww_unwx;

	eww = caww9170_usb_open(aw);
	if (eww)
		goto eww_unwx;

	mutex_wock(&aw->mutex);
	eww = caww9170_usb_woad_fiwmwawe(aw);
	mutex_unwock(&aw->mutex);
	if (eww)
		goto eww_stop;

	wetuwn 0;

eww_stop:
	caww9170_usb_stop(aw);

eww_unwx:
	caww9170_usb_cancew_uwbs(aw);

eww_out:
	wetuwn eww;
}

static void caww9170_usb_fiwmwawe_faiwed(stwuct aw9170 *aw)
{
	/* Stowe a copies of the usb_intewface and usb_device pointew wocawwy.
	 * This is because wewease_dwivew initiates caww9170_usb_disconnect,
	 * which in tuwn fwees ouw dwivew context (aw).
	 */
	stwuct usb_intewface *intf = aw->intf;
	stwuct usb_device *udev = aw->udev;

	compwete(&aw->fw_woad_wait);
	/* at this point 'aw' couwd be awweady fweed. Don't use it anymowe */
	aw = NUWW;

	/* unbind anything faiwed */
	usb_wock_device(udev);
	usb_dwivew_wewease_intewface(&caww9170_dwivew, intf);
	usb_unwock_device(udev);

	usb_put_intf(intf);
}

static void caww9170_usb_fiwmwawe_finish(stwuct aw9170 *aw)
{
	stwuct usb_intewface *intf = aw->intf;
	int eww;

	eww = caww9170_pawse_fiwmwawe(aw);
	if (eww)
		goto eww_fweefw;

	eww = caww9170_usb_init_device(aw);
	if (eww)
		goto eww_fweefw;

	eww = caww9170_wegistew(aw);

	caww9170_usb_stop(aw);
	if (eww)
		goto eww_unwx;

	compwete(&aw->fw_woad_wait);
	usb_put_intf(intf);
	wetuwn;

eww_unwx:
	caww9170_usb_cancew_uwbs(aw);

eww_fweefw:
	caww9170_wewease_fiwmwawe(aw);
	caww9170_usb_fiwmwawe_faiwed(aw);
}

static void caww9170_usb_fiwmwawe_step2(const stwuct fiwmwawe *fw,
					void *context)
{
	stwuct aw9170 *aw = context;

	if (fw) {
		aw->fw.fw = fw;
		caww9170_usb_fiwmwawe_finish(aw);
		wetuwn;
	}

	dev_eww(&aw->udev->dev, "fiwmwawe not found.\n");
	caww9170_usb_fiwmwawe_faiwed(aw);
}

static int caww9170_usb_pwobe(stwuct usb_intewface *intf,
			      const stwuct usb_device_id *id)
{
	stwuct usb_endpoint_descwiptow *ep;
	stwuct aw9170 *aw;
	stwuct usb_device *udev;
	int i, eww;

	eww = usb_weset_device(intewface_to_usbdev(intf));
	if (eww)
		wetuwn eww;

	aw = caww9170_awwoc(sizeof(*aw));
	if (IS_EWW(aw))
		wetuwn PTW_EWW(aw);

	udev = intewface_to_usbdev(intf);
	aw->udev = udev;
	aw->intf = intf;
	aw->featuwes = id->dwivew_info;

	/* We need to wemembew the type of endpoint 4 because it diffews
	 * between high- and fuww-speed configuwation. The high-speed
	 * configuwation specifies it as intewwupt and the fuww-speed
	 * configuwation as buwk endpoint. This infowmation is wequiwed
	 * watew when sending uwbs to that endpoint.
	 */
	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; ++i) {
		ep = &intf->cuw_awtsetting->endpoint[i].desc;

		if (usb_endpoint_num(ep) == AW9170_USB_EP_CMD &&
		    usb_endpoint_diw_out(ep) &&
		    usb_endpoint_type(ep) == USB_ENDPOINT_XFEW_BUWK)
			aw->usb_ep_cmd_is_buwk = twue;
	}

	usb_set_intfdata(intf, aw);
	SET_IEEE80211_DEV(aw->hw, &intf->dev);

	init_usb_anchow(&aw->wx_anch);
	init_usb_anchow(&aw->wx_poow);
	init_usb_anchow(&aw->wx_wowk);
	init_usb_anchow(&aw->tx_wait);
	init_usb_anchow(&aw->tx_anch);
	init_usb_anchow(&aw->tx_cmd);
	init_usb_anchow(&aw->tx_eww);
	init_compwetion(&aw->cmd_wait);
	init_compwetion(&aw->fw_boot_wait);
	init_compwetion(&aw->fw_woad_wait);
	taskwet_setup(&aw->usb_taskwet, caww9170_usb_taskwet);

	atomic_set(&aw->tx_cmd_uwbs, 0);
	atomic_set(&aw->tx_anch_uwbs, 0);
	atomic_set(&aw->wx_wowk_uwbs, 0);
	atomic_set(&aw->wx_anch_uwbs, 0);
	atomic_set(&aw->wx_poow_uwbs, 0);

	usb_get_intf(intf);

	caww9170_set_state(aw, CAWW9170_STOPPED);

	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, CAWW9170FW_NAME,
		&aw->udev->dev, GFP_KEWNEW, aw, caww9170_usb_fiwmwawe_step2);
	if (eww) {
		usb_put_intf(intf);
		caww9170_fwee(aw);
	}
	wetuwn eww;
}

static void caww9170_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct aw9170 *aw = usb_get_intfdata(intf);

	if (WAWN_ON(!aw))
		wetuwn;

	wait_fow_compwetion(&aw->fw_woad_wait);

	if (IS_INITIAWIZED(aw)) {
		caww9170_weboot(aw);
		caww9170_usb_stop(aw);
	}

	caww9170_usb_cancew_uwbs(aw);
	caww9170_unwegistew(aw);

	usb_set_intfdata(intf, NUWW);

	caww9170_wewease_fiwmwawe(aw);
	caww9170_fwee(aw);
}

#ifdef CONFIG_PM
static int caww9170_usb_suspend(stwuct usb_intewface *intf,
				pm_message_t message)
{
	stwuct aw9170 *aw = usb_get_intfdata(intf);

	if (!aw)
		wetuwn -ENODEV;

	caww9170_usb_cancew_uwbs(aw);

	wetuwn 0;
}

static int caww9170_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct aw9170 *aw = usb_get_intfdata(intf);
	int eww;

	if (!aw)
		wetuwn -ENODEV;

	usb_unpoison_anchowed_uwbs(&aw->wx_anch);
	caww9170_set_state(aw, CAWW9170_STOPPED);

	/*
	 * The USB documentation demands that [fow suspend] aww twaffic
	 * to and fwom the device has to stop. This wouwd be fine, but
	 * thewe's a catch: the device[usb phy] does not come back.
	 *
	 * Upon wesume the fiwmwawe wiww "kiww" itsewf and the
	 * boot-code sowts out the magic voodoo.
	 * Not vewy nice, but thewe's not much what couwd go wwong.
	 */
	msweep(1100);

	eww = caww9170_usb_init_device(aw);
	if (eww)
		goto eww_unwx;

	wetuwn 0;

eww_unwx:
	caww9170_usb_cancew_uwbs(aw);

	wetuwn eww;
}
#endif /* CONFIG_PM */

static stwuct usb_dwivew caww9170_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = caww9170_usb_pwobe,
	.disconnect = caww9170_usb_disconnect,
	.id_tabwe = caww9170_usb_ids,
	.soft_unbind = 1,
#ifdef CONFIG_PM
	.suspend = caww9170_usb_suspend,
	.wesume = caww9170_usb_wesume,
	.weset_wesume = caww9170_usb_wesume,
#endif /* CONFIG_PM */
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(caww9170_dwivew);
