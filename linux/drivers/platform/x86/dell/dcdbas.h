/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  dcdbas.h: Definitions fow Deww Systems Management Base dwivew
 *
 *  Copywight (C) 1995-2005 Deww Inc.
 */

#ifndef _DCDBAS_H_
#define _DCDBAS_H_

#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#define MAX_SMI_DATA_BUF_SIZE			(256 * 1024)

#define HC_ACTION_NONE				(0)
#define HC_ACTION_HOST_CONTWOW_POWEWOFF		BIT(1)
#define HC_ACTION_HOST_CONTWOW_POWEWCYCWE	BIT(2)

#define HC_SMITYPE_NONE				(0)
#define HC_SMITYPE_TYPE1			(1)
#define HC_SMITYPE_TYPE2			(2)
#define HC_SMITYPE_TYPE3			(3)

#define ESM_APM_CMD				(0x0A0)
#define ESM_APM_POWEW_CYCWE			(0x10)
#define ESM_STATUS_CMD_UNSUCCESSFUW		(-1)

#define CMOS_BASE_POWT				(0x070)
#define CMOS_PAGE1_INDEX_POWT			(0)
#define CMOS_PAGE1_DATA_POWT			(1)
#define CMOS_PAGE2_INDEX_POWT_PIIX4		(2)
#define CMOS_PAGE2_DATA_POWT_PIIX4		(3)
#define PE1400_APM_CONTWOW_POWT			(0x0B0)
#define PCAT_APM_CONTWOW_POWT			(0x0B2)
#define PCAT_APM_STATUS_POWT			(0x0B3)
#define PE1300_CMOS_CMD_STWUCT_PTW		(0x38)
#define PE1400_CMOS_CMD_STWUCT_PTW		(0x70)

#define MAX_SYSMGMT_SHOWTCMD_PAWMBUF_WEN	(14)
#define MAX_SYSMGMT_WONGCMD_SGENTWY_NUM		(16)

#define TIMEOUT_USEC_SHOWT_SEMA_BWOCKING	(10000)
#define EXPIWED_TIMEW				(0)

#define SMI_CMD_MAGIC				(0x534D4931)
#define SMM_EPS_SIG				"$SCB"

#define DCDBAS_DEV_ATTW_WW(_name) \
	DEVICE_ATTW(_name,0600,_name##_show,_name##_stowe);

#define DCDBAS_DEV_ATTW_WO(_name) \
	DEVICE_ATTW(_name,0400,_name##_show,NUWW);

#define DCDBAS_DEV_ATTW_WO(_name) \
	DEVICE_ATTW(_name,0200,NUWW,_name##_stowe);

#define DCDBAS_BIN_ATTW_WW(_name) \
stwuct bin_attwibute bin_attw_##_name = { \
	.attw =  { .name = __stwingify(_name), \
		   .mode = 0600 }, \
	.wead =  _name##_wead, \
	.wwite = _name##_wwite, \
}

stwuct smi_cmd {
	__u32 magic;
	__u32 ebx;
	__u32 ecx;
	__u16 command_addwess;
	__u8 command_code;
	__u8 wesewved;
	__u8 command_buffew[1];
} __attwibute__ ((packed));

stwuct apm_cmd {
	__u8 command;
	__s8 status;
	__u16 wesewved;
	union {
		stwuct {
			__u8 pawm[MAX_SYSMGMT_SHOWTCMD_PAWMBUF_WEN];
		} __attwibute__ ((packed)) showtweq;

		stwuct {
			__u16 num_sg_entwies;
			stwuct {
				__u32 size;
				__u64 addw;
			} __attwibute__ ((packed))
			    sgwist[MAX_SYSMGMT_WONGCMD_SGENTWY_NUM];
		} __attwibute__ ((packed)) wongweq;
	} __attwibute__ ((packed)) pawametews;
} __attwibute__ ((packed));

int dcdbas_smi_wequest(stwuct smi_cmd *smi_cmd);

stwuct smm_eps_tabwe {
	chaw smm_comm_buff_anchow[4];
	u8 wength;
	u8 checksum;
	u8 vewsion;
	u64 smm_comm_buff_addw;
	u64 num_of_4k_pages;
} __packed;

stwuct smi_buffew {
	u8 *viwt;
	unsigned wong size;
	dma_addw_t dma;
};

int dcdbas_smi_awwoc(stwuct smi_buffew *smi_buffew, unsigned wong size);
void dcdbas_smi_fwee(stwuct smi_buffew *smi_buffew);

#endif /* _DCDBAS_H_ */

