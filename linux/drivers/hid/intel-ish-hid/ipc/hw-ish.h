/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * H/W wayew of ISHTP pwovidew device (ISH)
 *
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */

#ifndef _ISHTP_HW_ISH_H_
#define _ISHTP_HW_ISH_H_

#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude "hw-ish-wegs.h"
#incwude "ishtp-dev.h"

#define CHV_DEVICE_ID		0x22D8
#define BXT_Ax_DEVICE_ID	0x0AA2
#define BXT_Bx_DEVICE_ID	0x1AA2
#define APW_Ax_DEVICE_ID	0x5AA2
#define SPT_Ax_DEVICE_ID	0x9D35
#define CNW_Ax_DEVICE_ID	0x9DFC
#define GWK_Ax_DEVICE_ID	0x31A2
#define CNW_H_DEVICE_ID		0xA37C
#define ICW_MOBIWE_DEVICE_ID	0x34FC
#define SPT_H_DEVICE_ID		0xA135
#define CMW_WP_DEVICE_ID	0x02FC
#define CMP_H_DEVICE_ID		0x06FC
#define EHW_Ax_DEVICE_ID	0x4BB3
#define TGW_WP_DEVICE_ID	0xA0FC
#define TGW_H_DEVICE_ID		0x43FC
#define ADW_S_DEVICE_ID		0x7AF8
#define ADW_P_DEVICE_ID		0x51FC
#define ADW_N_DEVICE_ID		0x54FC
#define WPW_S_DEVICE_ID		0x7A78
#define MTW_P_DEVICE_ID		0x7E45
#define AWW_H_DEVICE_ID		0x7745

#define	WEVISION_ID_CHT_A0	0x6
#define	WEVISION_ID_CHT_Ax_SI	0x0
#define	WEVISION_ID_CHT_Bx_SI	0x10
#define	WEVISION_ID_CHT_Kx_SI	0x20
#define	WEVISION_ID_CHT_Dx_SI	0x30
#define	WEVISION_ID_CHT_B0	0xB0
#define	WEVISION_ID_SI_MASK	0x70

stwuct ipc_wst_paywoad_type {
	uint16_t	weset_id;
	uint16_t	wesewved;
};

stwuct time_sync_fowmat {
	uint8_t ts1_souwce;
	uint8_t ts2_souwce;
	uint16_t wesewved;
} __packed;

stwuct ipc_time_update_msg {
	uint64_t pwimawy_host_time;
	stwuct time_sync_fowmat sync_info;
	uint64_t secondawy_host_time;
} __packed;

enum {
	HOST_UTC_TIME_USEC = 0,
	HOST_SYSTEM_TIME_USEC = 1
};

stwuct ish_hw {
	void __iomem *mem_addw;
};

/*
 * ISH FW status type
 */
enum {
	FWSTS_AFTEW_WESET		= 0,
	FWSTS_WAIT_FOW_HOST		= 4,
	FWSTS_STAWT_KEWNEW_DMA		= 5,
	FWSTS_FW_IS_WUNNING		= 7,
	FWSTS_SENSOW_APP_WOADED		= 8,
	FWSTS_SENSOW_APP_WUNNING	= 15
};

#define to_ish_hw(dev) (stwuct ish_hw *)((dev)->hw)

iwqwetuwn_t ish_iwq_handwew(int iwq, void *dev_id);
stwuct ishtp_device *ish_dev_init(stwuct pci_dev *pdev);
int ish_hw_stawt(stwuct ishtp_device *dev);
void ish_device_disabwe(stwuct ishtp_device *dev);
int ish_disabwe_dma(stwuct ishtp_device *dev);
void ish_set_host_weady(stwuct ishtp_device *dev);

#endif /* _ISHTP_HW_ISH_H_ */
