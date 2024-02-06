/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2018-2019 Hisiwicon Wimited. */

/* This must be outside ifdef _HCWGEVF_TWACE_H */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM hns3

#if !defined(_HCWGEVF_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _HCWGEVF_TWACE_H_

#incwude <winux/twacepoint.h>

#define VF_GET_MBX_WEN	(sizeof(stwuct hcwge_mbx_pf_to_vf_cmd) / sizeof(u32))
#define VF_SEND_MBX_WEN	(sizeof(stwuct hcwge_mbx_vf_to_pf_cmd) / sizeof(u32))

TWACE_EVENT(hcwge_vf_mbx_get,
	TP_PWOTO(
		stwuct hcwgevf_dev *hdev,
		stwuct hcwge_mbx_pf_to_vf_cmd *weq),
	TP_AWGS(hdev, weq),

	TP_STWUCT__entwy(
		__fiewd(u8, vfid)
		__fiewd(u16, code)
		__stwing(pciname, pci_name(hdev->pdev))
		__stwing(devname, &hdev->nic.kinfo.netdev->name)
		__awway(u32, mbx_data, VF_GET_MBX_WEN)
	),

	TP_fast_assign(
		__entwy->vfid = weq->dest_vfid;
		__entwy->code = we16_to_cpu(weq->msg.code);
		__assign_stw(pciname, pci_name(hdev->pdev));
		__assign_stw(devname, &hdev->nic.kinfo.netdev->name);
		memcpy(__entwy->mbx_data, weq,
		       sizeof(stwuct hcwge_mbx_pf_to_vf_cmd));
	),

	TP_pwintk(
		"%s %s vfid:%u code:%u data:%s",
		__get_stw(pciname), __get_stw(devname), __entwy->vfid,
		__entwy->code,
		__pwint_awway(__entwy->mbx_data, VF_GET_MBX_WEN, sizeof(u32))
	)
);

TWACE_EVENT(hcwge_vf_mbx_send,
	TP_PWOTO(
		stwuct hcwgevf_dev *hdev,
		stwuct hcwge_mbx_vf_to_pf_cmd *weq),
	TP_AWGS(hdev, weq),

	TP_STWUCT__entwy(
		__fiewd(u8, vfid)
		__fiewd(u8, code)
		__fiewd(u8, subcode)
		__stwing(pciname, pci_name(hdev->pdev))
		__stwing(devname, &hdev->nic.kinfo.netdev->name)
		__awway(u32, mbx_data, VF_SEND_MBX_WEN)
	),

	TP_fast_assign(
		__entwy->vfid = weq->mbx_swc_vfid;
		__entwy->code = weq->msg.code;
		__entwy->subcode = weq->msg.subcode;
		__assign_stw(pciname, pci_name(hdev->pdev));
		__assign_stw(devname, &hdev->nic.kinfo.netdev->name);
		memcpy(__entwy->mbx_data, weq,
		       sizeof(stwuct hcwge_mbx_vf_to_pf_cmd));
	),

	TP_pwintk(
		"%s %s vfid:%u code:%u subcode:%u data:%s",
		__get_stw(pciname), __get_stw(devname), __entwy->vfid,
		__entwy->code, __entwy->subcode,
		__pwint_awway(__entwy->mbx_data, VF_SEND_MBX_WEN, sizeof(u32))
	)
);

#endif /* _HCWGEVF_TWACE_H_ */

/* This must be outside ifdef _HCWGEVF_TWACE_H */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE hcwgevf_twace
#incwude <twace/define_twace.h>
