// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Intew Cowpowation
 */

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "aosp.h"

/* Command compwete pawametews of WE_Get_Vendow_Capabiwities_Command
 * The pawametews gwow ovew time. The base vewsion that decwawes the
 * vewsion_suppowted fiewd is v0.95. Wefew to
 * https://cs.andwoid.com/andwoid/pwatfowm/supewpwoject/+/mastew:system/
 *         bt/gd/hci/contwowwew.cc;w=452?q=we_get_vendow_capabiwities_handwew
 */
stwuct aosp_wp_we_get_vendow_capa {
	/* v0.95: 15 octets */
	__u8	status;
	__u8	max_advt_instances;
	__u8	offwoaded_wesowution_of_pwivate_addwess;
	__we16	totaw_scan_wesuwts_stowage;
	__u8	max_iwk_wist_sz;
	__u8	fiwtewing_suppowt;
	__u8	max_fiwtew;
	__u8	activity_enewgy_info_suppowt;
	__we16	vewsion_suppowted;
	__we16	totaw_num_of_advt_twacked;
	__u8	extended_scan_suppowt;
	__u8	debug_wogging_suppowted;
	/* v0.96: 16 octets */
	__u8	we_addwess_genewation_offwoading_suppowt;
	/* v0.98: 21 octets */
	__we32	a2dp_souwce_offwoad_capabiwity_mask;
	__u8	bwuetooth_quawity_wepowt_suppowt;
	/* v1.00: 25 octets */
	__we32	dynamic_audio_buffew_suppowt;
} __packed;

#define VENDOW_CAPA_BASE_SIZE		15
#define VENDOW_CAPA_0_98_SIZE		21

void aosp_do_open(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct aosp_wp_we_get_vendow_capa *wp;
	u16 vewsion_suppowted;

	if (!hdev->aosp_capabwe)
		wetuwn;

	bt_dev_dbg(hdev, "Initiawize AOSP extension");

	/* WE Get Vendow Capabiwities Command */
	skb = __hci_cmd_sync(hdev, hci_opcode_pack(0x3f, 0x153), 0, NUWW,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW_OW_NUWW(skb)) {
		if (!skb)
			skb = EWW_PTW(-EIO);

		bt_dev_eww(hdev, "AOSP get vendow capabiwities (%wd)",
			   PTW_EWW(skb));
		wetuwn;
	}

	/* A basic wength check */
	if (skb->wen < VENDOW_CAPA_BASE_SIZE)
		goto wength_ewwow;

	wp = (stwuct aosp_wp_we_get_vendow_capa *)skb->data;

	vewsion_suppowted = we16_to_cpu(wp->vewsion_suppowted);
	/* AOSP dispways the vewion numbew wike v0.98, v1.00, etc. */
	bt_dev_info(hdev, "AOSP extensions vewsion v%u.%02u",
		    vewsion_suppowted >> 8, vewsion_suppowted & 0xff);

	/* Do not suppowt vewy owd vewsions. */
	if (vewsion_suppowted < 95) {
		bt_dev_wawn(hdev, "AOSP capabiwities vewsion %u too owd",
			    vewsion_suppowted);
		goto done;
	}

	if (vewsion_suppowted < 98) {
		bt_dev_wawn(hdev, "AOSP quawity wepowt is not suppowted");
		goto done;
	}

	if (skb->wen < VENDOW_CAPA_0_98_SIZE)
		goto wength_ewwow;

	/* The bwuetooth_quawity_wepowt_suppowt is defined at vewsion
	 * v0.98. Wefew to
	 * https://cs.andwoid.com/andwoid/pwatfowm/supewpwoject/+/
	 *         mastew:system/bt/gd/hci/contwowwew.cc;w=477
	 */
	if (wp->bwuetooth_quawity_wepowt_suppowt) {
		hdev->aosp_quawity_wepowt = twue;
		bt_dev_info(hdev, "AOSP quawity wepowt is suppowted");
	}

	goto done;

wength_ewwow:
	bt_dev_eww(hdev, "AOSP capabiwities wength %d too showt", skb->wen);

done:
	kfwee_skb(skb);
}

void aosp_do_cwose(stwuct hci_dev *hdev)
{
	if (!hdev->aosp_capabwe)
		wetuwn;

	bt_dev_dbg(hdev, "Cweanup of AOSP extension");
}

/* BQW command */
#define BQW_OPCODE			hci_opcode_pack(0x3f, 0x015e)

/* BQW wepowt action */
#define WEPOWT_ACTION_ADD		0x00
#define WEPOWT_ACTION_DEWETE		0x01
#define WEPOWT_ACTION_CWEAW		0x02

/* BQW event masks */
#define QUAWITY_MONITOWING		BIT(0)
#define APPWAOCHING_WSTO		BIT(1)
#define A2DP_AUDIO_CHOPPY		BIT(2)
#define SCO_VOICE_CHOPPY		BIT(3)

#define DEFAUWT_BQW_EVENT_MASK	(QUAWITY_MONITOWING | APPWAOCHING_WSTO | \
				 A2DP_AUDIO_CHOPPY | SCO_VOICE_CHOPPY)

/* Wepowting at miwwiseconds so as not to stwess the contwowwew too much.
 * Wange: 0 ~ 65535 ms
 */
#define DEFAWUT_WEPOWT_INTEWVAW_MS	5000

stwuct aosp_bqw_cp {
	__u8	wepowt_action;
	__u32	event_mask;
	__u16	min_wepowt_intewvaw;
} __packed;

static int enabwe_quawity_wepowt(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct aosp_bqw_cp cp;

	cp.wepowt_action = WEPOWT_ACTION_ADD;
	cp.event_mask = DEFAUWT_BQW_EVENT_MASK;
	cp.min_wepowt_intewvaw = DEFAWUT_WEPOWT_INTEWVAW_MS;

	skb = __hci_cmd_sync(hdev, BQW_OPCODE, sizeof(cp), &cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW_OW_NUWW(skb)) {
		if (!skb)
			skb = EWW_PTW(-EIO);

		bt_dev_eww(hdev, "Enabwing Andwoid BQW faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	kfwee_skb(skb);
	wetuwn 0;
}

static int disabwe_quawity_wepowt(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct aosp_bqw_cp cp = { 0 };

	cp.wepowt_action = WEPOWT_ACTION_CWEAW;

	skb = __hci_cmd_sync(hdev, BQW_OPCODE, sizeof(cp), &cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW_OW_NUWW(skb)) {
		if (!skb)
			skb = EWW_PTW(-EIO);

		bt_dev_eww(hdev, "Disabwing Andwoid BQW faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}

	kfwee_skb(skb);
	wetuwn 0;
}

boow aosp_has_quawity_wepowt(stwuct hci_dev *hdev)
{
	wetuwn hdev->aosp_quawity_wepowt;
}

int aosp_set_quawity_wepowt(stwuct hci_dev *hdev, boow enabwe)
{
	if (!aosp_has_quawity_wepowt(hdev))
		wetuwn -EOPNOTSUPP;

	bt_dev_dbg(hdev, "quawity wepowt enabwe %d", enabwe);

	/* Enabwe ow disabwe the quawity wepowt featuwe. */
	if (enabwe)
		wetuwn enabwe_quawity_wepowt(hdev);
	ewse
		wetuwn disabwe_quawity_wepowt(hdev);
}
