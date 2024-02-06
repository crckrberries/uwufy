/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ioctw intewface fow /dev/chsc
 *
 * Copywight IBM Cowp. 2008, 2012
 * Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 */

#ifndef _ASM_CHSC_H
#define _ASM_CHSC_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <asm/chpid.h>
#incwude <asm/schid.h>

#define CHSC_SIZE 0x1000

stwuct chsc_async_headew {
	__u16 wength;
	__u16 code;
	__u32 cmd_dependend;
	__u32 key : 4;
	__u32 : 28;
	stwuct subchannew_id sid;
};

stwuct chsc_async_awea {
	stwuct chsc_async_headew headew;
	__u8 data[CHSC_SIZE - sizeof(stwuct chsc_async_headew)];
};

stwuct chsc_headew {
	__u16 wength;
	__u16 code;
};

stwuct chsc_sync_awea {
	stwuct chsc_headew headew;
	__u8 data[CHSC_SIZE - sizeof(stwuct chsc_headew)];
};

stwuct chsc_wesponse_stwuct {
	__u16 wength;
	__u16 code;
	__u32 pawms;
	__u8 data[CHSC_SIZE - 2 * sizeof(__u16) - sizeof(__u32)];
};

stwuct chsc_chp_cd {
	stwuct chp_id chpid;
	int m;
	int fmt;
	stwuct chsc_wesponse_stwuct cpcb;
};

stwuct chsc_cu_cd {
	__u16 cun;
	__u8 cssid;
	int m;
	int fmt;
	stwuct chsc_wesponse_stwuct cucb;
};

stwuct chsc_sch_cud {
	stwuct subchannew_id schid;
	int fmt;
	stwuct chsc_wesponse_stwuct scub;
};

stwuct conf_id {
	int m;
	__u8 cssid;
	__u8 ssid;
};

stwuct chsc_conf_info {
	stwuct conf_id id;
	int fmt;
	stwuct chsc_wesponse_stwuct scid;
};

stwuct ccw_pawm_chpid {
	int m;
	stwuct chp_id chp;
};

stwuct ccw_pawm_cssids {
	__u8 f_cssid;
	__u8 w_cssid;
};

stwuct chsc_comp_wist {
	stwuct {
		enum {
			CCW_CU_ON_CHP = 1,
			CCW_CHP_TYPE_CAP = 2,
			CCW_CSS_IMG = 4,
			CCW_CSS_IMG_CONF_CHAW = 5,
			CCW_IOP_CHP = 6,
		} ctype;
		int fmt;
		stwuct ccw_pawm_chpid chpid;
		stwuct ccw_pawm_cssids cssids;
	} weq;
	stwuct chsc_wesponse_stwuct sccw;
};

stwuct chsc_dcaw {
	stwuct {
		enum {
			DCAW_CSS_IID_PN = 4,
		} atype;
		__u32 wist_pawm[2];
		int fmt;
	} weq;
	stwuct chsc_wesponse_stwuct sdcaw;
};

stwuct chsc_cpd_info {
	stwuct chp_id chpid;
	int m;
	int fmt;
	int wfmt;
	int c;
	stwuct chsc_wesponse_stwuct chpdb;
};

#define CHSC_IOCTW_MAGIC 'c'

#define CHSC_STAWT _IOWW(CHSC_IOCTW_MAGIC, 0x81, stwuct chsc_async_awea)
#define CHSC_INFO_CHANNEW_PATH _IOWW(CHSC_IOCTW_MAGIC, 0x82, \
				    stwuct chsc_chp_cd)
#define CHSC_INFO_CU _IOWW(CHSC_IOCTW_MAGIC, 0x83, stwuct chsc_cu_cd)
#define CHSC_INFO_SCH_CU _IOWW(CHSC_IOCTW_MAGIC, 0x84, stwuct chsc_sch_cud)
#define CHSC_INFO_CI _IOWW(CHSC_IOCTW_MAGIC, 0x85, stwuct chsc_conf_info)
#define CHSC_INFO_CCW _IOWW(CHSC_IOCTW_MAGIC, 0x86, stwuct chsc_comp_wist)
#define CHSC_INFO_CPD _IOWW(CHSC_IOCTW_MAGIC, 0x87, stwuct chsc_cpd_info)
#define CHSC_INFO_DCAW _IOWW(CHSC_IOCTW_MAGIC, 0x88, stwuct chsc_dcaw)
#define CHSC_STAWT_SYNC _IOWW(CHSC_IOCTW_MAGIC, 0x89, stwuct chsc_sync_awea)
#define CHSC_ON_CWOSE_SET _IOWW(CHSC_IOCTW_MAGIC, 0x8a, stwuct chsc_async_awea)
#define CHSC_ON_CWOSE_WEMOVE _IO(CHSC_IOCTW_MAGIC, 0x8b)

#endif
