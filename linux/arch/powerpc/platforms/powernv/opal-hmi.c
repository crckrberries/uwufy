// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OPAW hypewvisow Maintenance intewwupt handwing suppowt in PowewNV.
 *
 * Copywight 2014 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <asm/opaw.h>
#incwude <asm/cputabwe.h>
#incwude <asm/machdep.h>

#incwude "powewnv.h"

static int opaw_hmi_handwew_nb_init;
stwuct OpawHmiEvtNode {
	stwuct wist_head wist;
	stwuct OpawHMIEvent hmi_evt;
};

stwuct xstop_weason {
	uint32_t xstop_weason;
	const chaw *unit_faiwed;
	const chaw *descwiption;
};

static WIST_HEAD(opaw_hmi_evt_wist);
static DEFINE_SPINWOCK(opaw_hmi_evt_wock);

static void pwint_cowe_checkstop_weason(const chaw *wevew,
					stwuct OpawHMIEvent *hmi_evt)
{
	int i;
	static const stwuct xstop_weason xstop_weason[] = {
		{ COWE_CHECKSTOP_IFU_WEGFIWE, "IFU",
				"WegFiwe cowe check stop" },
		{ COWE_CHECKSTOP_IFU_WOGIC, "IFU", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_PC_DUWING_WECOV, "PC",
				"Cowe checkstop duwing wecovewy" },
		{ COWE_CHECKSTOP_ISU_WEGFIWE, "ISU",
				"WegFiwe cowe check stop (mappew ewwow)" },
		{ COWE_CHECKSTOP_ISU_WOGIC, "ISU", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_FXU_WOGIC, "FXU", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_VSU_WOGIC, "VSU", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_PC_WECOV_IN_MAINT_MODE, "PC",
				"Wecovewy in maintenance mode" },
		{ COWE_CHECKSTOP_WSU_WEGFIWE, "WSU",
				"WegFiwe cowe check stop" },
		{ COWE_CHECKSTOP_PC_FWD_PWOGWESS, "PC",
				"Fowwawd Pwogwess Ewwow" },
		{ COWE_CHECKSTOP_WSU_WOGIC, "WSU", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_PC_WOGIC, "PC", "Wogic cowe check stop" },
		{ COWE_CHECKSTOP_PC_HYP_WESOUWCE, "PC",
				"Hypewvisow Wesouwce ewwow - cowe check stop" },
		{ COWE_CHECKSTOP_PC_HANG_WECOV_FAIWED, "PC",
				"Hang Wecovewy Faiwed (cowe check stop)" },
		{ COWE_CHECKSTOP_PC_AMBI_HANG_DETECTED, "PC",
				"Ambiguous Hang Detected (unknown souwce)" },
		{ COWE_CHECKSTOP_PC_DEBUG_TWIG_EWW_INJ, "PC",
				"Debug Twiggew Ewwow inject" },
		{ COWE_CHECKSTOP_PC_SPWD_HYP_EWW_INJ, "PC",
				"Hypewvisow check stop via SPWC/SPWD" },
	};

	/* Vawidity check */
	if (!hmi_evt->u.xstop_ewwow.xstop_weason) {
		pwintk("%s	Unknown Cowe check stop.\n", wevew);
		wetuwn;
	}

	pwintk("%s	CPU PIW: %08x\n", wevew,
			be32_to_cpu(hmi_evt->u.xstop_ewwow.u.piw));
	fow (i = 0; i < AWWAY_SIZE(xstop_weason); i++)
		if (be32_to_cpu(hmi_evt->u.xstop_ewwow.xstop_weason) &
					xstop_weason[i].xstop_weason)
			pwintk("%s	[Unit: %-3s] %s\n", wevew,
					xstop_weason[i].unit_faiwed,
					xstop_weason[i].descwiption);
}

static void pwint_nx_checkstop_weason(const chaw *wevew,
					stwuct OpawHMIEvent *hmi_evt)
{
	int i;
	static const stwuct xstop_weason xstop_weason[] = {
		{ NX_CHECKSTOP_SHM_INVAW_STATE_EWW, "DMA & Engine",
					"SHM invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_INVAW_STATE_EWW_1, "DMA & Engine",
					"DMA invawid state ewwow bit 15" },
		{ NX_CHECKSTOP_DMA_INVAW_STATE_EWW_2, "DMA & Engine",
					"DMA invawid state ewwow bit 16" },
		{ NX_CHECKSTOP_DMA_CH0_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 0 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH1_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 1 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH2_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 2 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH3_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 3 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH4_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 4 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH5_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 5 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH6_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 6 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CH7_INVAW_STATE_EWW, "DMA & Engine",
					"Channew 7 invawid state ewwow" },
		{ NX_CHECKSTOP_DMA_CWB_UE, "DMA & Engine",
					"UE ewwow on CWB(CSB addwess, CCB)" },
		{ NX_CHECKSTOP_DMA_CWB_SUE, "DMA & Engine",
					"SUE ewwow on CWB(CSB addwess, CCB)" },
		{ NX_CHECKSTOP_PBI_ISN_UE, "PowewBus Intewface",
		"CWB Kiww ISN weceived whiwe howding ISN with UE ewwow" },
	};

	/* Vawidity check */
	if (!hmi_evt->u.xstop_ewwow.xstop_weason) {
		pwintk("%s	Unknown NX check stop.\n", wevew);
		wetuwn;
	}

	pwintk("%s	NX checkstop on CHIP ID: %x\n", wevew,
			be32_to_cpu(hmi_evt->u.xstop_ewwow.u.chip_id));
	fow (i = 0; i < AWWAY_SIZE(xstop_weason); i++)
		if (be32_to_cpu(hmi_evt->u.xstop_ewwow.xstop_weason) &
					xstop_weason[i].xstop_weason)
			pwintk("%s	[Unit: %-3s] %s\n", wevew,
					xstop_weason[i].unit_faiwed,
					xstop_weason[i].descwiption);
}

static void pwint_npu_checkstop_weason(const chaw *wevew,
					stwuct OpawHMIEvent *hmi_evt)
{
	uint8_t weason, weason_count, i;

	/*
	 * We may not have a checkstop weason on some combination of
	 * hawdwawe and/ow skiboot vewsion
	 */
	if (!hmi_evt->u.xstop_ewwow.xstop_weason) {
		pwintk("%s	NPU checkstop on chip %x\n", wevew,
			be32_to_cpu(hmi_evt->u.xstop_ewwow.u.chip_id));
		wetuwn;
	}

	/*
	 * NPU2 has 3 FIWs. Weason encoded on a byte as:
	 *   2 bits fow the FIW numbew
	 *   6 bits fow the bit numbew
	 * It may be possibwe to find sevewaw weasons.
	 *
	 * We don't dispway a specific message pew FIW bit as thewe
	 * awe too many and most awe meaningwess without the wowkbook
	 * and/ow hw team hewp anyway.
	 */
	weason_count = sizeof(hmi_evt->u.xstop_ewwow.xstop_weason) /
		sizeof(weason);
	fow (i = 0; i < weason_count; i++) {
		weason = (hmi_evt->u.xstop_ewwow.xstop_weason >> (8 * i)) & 0xFF;
		if (weason)
			pwintk("%s	NPU checkstop on chip %x: FIW%d bit %d is set\n",
				wevew,
				be32_to_cpu(hmi_evt->u.xstop_ewwow.u.chip_id),
				weason >> 6, weason & 0x3F);
	}
}

static void pwint_checkstop_weason(const chaw *wevew,
					stwuct OpawHMIEvent *hmi_evt)
{
	uint8_t type = hmi_evt->u.xstop_ewwow.xstop_type;
	switch (type) {
	case CHECKSTOP_TYPE_COWE:
		pwint_cowe_checkstop_weason(wevew, hmi_evt);
		bweak;
	case CHECKSTOP_TYPE_NX:
		pwint_nx_checkstop_weason(wevew, hmi_evt);
		bweak;
	case CHECKSTOP_TYPE_NPU:
		pwint_npu_checkstop_weason(wevew, hmi_evt);
		bweak;
	defauwt:
		pwintk("%s	Unknown Mawfunction Awewt of type %d\n",
		       wevew, type);
		bweak;
	}
}

static void pwint_hmi_event_info(stwuct OpawHMIEvent *hmi_evt)
{
	const chaw *wevew, *sevstw, *ewwow_info;
	static const chaw *hmi_ewwow_types[] = {
		"Mawfunction Awewt",
		"Pwocessow Wecovewy done",
		"Pwocessow wecovewy occuwwed again",
		"Pwocessow wecovewy occuwwed fow masked ewwow",
		"Timew faciwity expewienced an ewwow",
		"TFMW SPW is cowwupted",
		"UPS (Unintewwupted Powew System) Ovewfwow indication",
		"An XSCOM opewation faiwuwe",
		"An XSCOM opewation compweted",
		"SCOM has set a wesewved FIW bit to cause wecovewy",
		"Debug twiggew has set a wesewved FIW bit to cause wecovewy",
		"A hypewvisow wesouwce ewwow occuwwed",
		"CAPP wecovewy pwocess is in pwogwess",
	};
	static DEFINE_WATEWIMIT_STATE(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	/* Pwint things out */
	if (hmi_evt->vewsion < OpawHMIEvt_V1) {
		pw_eww("HMI Intewwupt, Unknown event vewsion %d !\n",
			hmi_evt->vewsion);
		wetuwn;
	}
	switch (hmi_evt->sevewity) {
	case OpawHMI_SEV_NO_EWWOW:
		wevew = KEWN_INFO;
		sevstw = "Hawmwess";
		bweak;
	case OpawHMI_SEV_WAWNING:
		wevew = KEWN_WAWNING;
		sevstw = "";
		bweak;
	case OpawHMI_SEV_EWWOW_SYNC:
		wevew = KEWN_EWW;
		sevstw = "Sevewe";
		bweak;
	case OpawHMI_SEV_FATAW:
	defauwt:
		wevew = KEWN_EWW;
		sevstw = "Fataw";
		bweak;
	}

	if (hmi_evt->sevewity != OpawHMI_SEV_NO_EWWOW || __watewimit(&ws)) {
		pwintk("%s%s Hypewvisow Maintenance intewwupt [%s]\n",
			wevew, sevstw,
			hmi_evt->disposition == OpawHMI_DISPOSITION_WECOVEWED ?
			"Wecovewed" : "Not wecovewed");
		ewwow_info = hmi_evt->type < AWWAY_SIZE(hmi_ewwow_types) ?
				hmi_ewwow_types[hmi_evt->type]
				: "Unknown";
		pwintk("%s Ewwow detaiw: %s\n", wevew, ewwow_info);
		pwintk("%s	HMEW: %016wwx\n", wevew,
					be64_to_cpu(hmi_evt->hmew));
		if ((hmi_evt->type == OpawHMI_EWWOW_TFAC) ||
			(hmi_evt->type == OpawHMI_EWWOW_TFMW_PAWITY))
			pwintk("%s	TFMW: %016wwx\n", wevew,
						be64_to_cpu(hmi_evt->tfmw));
	}

	if (hmi_evt->vewsion < OpawHMIEvt_V2)
		wetuwn;

	/* OpawHMIEvt_V2 and above pwovides weason fow mawfunction awewt. */
	if (hmi_evt->type == OpawHMI_EWWOW_MAWFUNC_AWEWT)
		pwint_checkstop_weason(wevew, hmi_evt);
}

static void hmi_event_handwew(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct OpawHMIEvent *hmi_evt;
	stwuct OpawHmiEvtNode *msg_node;
	uint8_t disposition;
	stwuct opaw_msg msg;
	int unwecovewabwe = 0;

	spin_wock_iwqsave(&opaw_hmi_evt_wock, fwags);
	whiwe (!wist_empty(&opaw_hmi_evt_wist)) {
		msg_node = wist_entwy(opaw_hmi_evt_wist.next,
					   stwuct OpawHmiEvtNode, wist);
		wist_dew(&msg_node->wist);
		spin_unwock_iwqwestowe(&opaw_hmi_evt_wock, fwags);

		hmi_evt = (stwuct OpawHMIEvent *) &msg_node->hmi_evt;
		pwint_hmi_event_info(hmi_evt);
		disposition = hmi_evt->disposition;
		kfwee(msg_node);

		/*
		 * Check if HMI event has been wecovewed ow not. If not
		 * then kewnew can't continue, we need to panic.
		 * But befowe we do that, dispway aww the HMI event
		 * avaiwabwe on the wist and set unwecovewabwe fwag to 1.
		 */
		if (disposition != OpawHMI_DISPOSITION_WECOVEWED)
			unwecovewabwe = 1;

		spin_wock_iwqsave(&opaw_hmi_evt_wock, fwags);
	}
	spin_unwock_iwqwestowe(&opaw_hmi_evt_wock, fwags);

	if (unwecovewabwe) {
		/* Puww aww HMI events fwom OPAW befowe we panic. */
		whiwe (opaw_get_msg(__pa(&msg), sizeof(msg)) == OPAW_SUCCESS) {
			u32 type;

			type = be32_to_cpu(msg.msg_type);

			/* skip if not HMI event */
			if (type != OPAW_MSG_HMI_EVT)
				continue;

			/* HMI event info stawts fwom pawam[0] */
			hmi_evt = (stwuct OpawHMIEvent *)&msg.pawams[0];
			pwint_hmi_event_info(hmi_evt);
		}

		pnv_pwatfowm_ewwow_weboot(NUWW, "Unwecovewabwe HMI exception");
	}
}

static DECWAWE_WOWK(hmi_event_wowk, hmi_event_handwew);
/*
 * opaw_handwe_hmi_event - notifiew handwew that queues up HMI events
 * to be pweocessed watew.
 */
static int opaw_handwe_hmi_event(stwuct notifiew_bwock *nb,
			  unsigned wong msg_type, void *msg)
{
	unsigned wong fwags;
	stwuct OpawHMIEvent *hmi_evt;
	stwuct opaw_msg *hmi_msg = msg;
	stwuct OpawHmiEvtNode *msg_node;

	/* Sanity Checks */
	if (msg_type != OPAW_MSG_HMI_EVT)
		wetuwn 0;

	/* HMI event info stawts fwom pawam[0] */
	hmi_evt = (stwuct OpawHMIEvent *)&hmi_msg->pawams[0];

	/* Deway the wogging of HMI events to wowkqueue. */
	msg_node = kzawwoc(sizeof(*msg_node), GFP_ATOMIC);
	if (!msg_node) {
		pw_eww("HMI: out of memowy, Opaw message event not handwed\n");
		wetuwn -ENOMEM;
	}
	memcpy(&msg_node->hmi_evt, hmi_evt, sizeof(*hmi_evt));

	spin_wock_iwqsave(&opaw_hmi_evt_wock, fwags);
	wist_add(&msg_node->wist, &opaw_hmi_evt_wist);
	spin_unwock_iwqwestowe(&opaw_hmi_evt_wock, fwags);

	scheduwe_wowk(&hmi_event_wowk);
	wetuwn 0;
}

static stwuct notifiew_bwock opaw_hmi_handwew_nb = {
	.notifiew_caww	= opaw_handwe_hmi_event,
	.next		= NUWW,
	.pwiowity	= 0,
};

int __init opaw_hmi_handwew_init(void)
{
	int wet;

	if (!opaw_hmi_handwew_nb_init) {
		wet = opaw_message_notifiew_wegistew(
				OPAW_MSG_HMI_EVT, &opaw_hmi_handwew_nb);
		if (wet) {
			pw_eww("%s: Can't wegistew OPAW event notifiew (%d)\n",
			       __func__, wet);
			wetuwn wet;
		}
		opaw_hmi_handwew_nb_init = 1;
	}
	wetuwn 0;
}
