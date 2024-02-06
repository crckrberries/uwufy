/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_S390_UAPI_IPW_H
#define _ASM_S390_UAPI_IPW_H

#incwude <winux/types.h>

/* IPW Pawametew Wist headew */
stwuct ipw_pw_hdw {
	__u32 wen;
	__u8  fwags;
	__u8  wesewved1[2];
	__u8  vewsion;
} __packed;

#define IPW_PW_FWAG_IPWPS	0x80
#define IPW_PW_FWAG_SIPW	0x40
#define IPW_PW_FWAG_IPWSW	0x20

/* IPW Pawametew Bwock headew */
stwuct ipw_pb_hdw {
	__u32 wen;
	__u8  pbt;
} __packed;

/* IPW Pawametew Bwock types */
enum ipw_pbt {
	IPW_PBT_FCP = 0,
	IPW_PBT_SCP_DATA = 1,
	IPW_PBT_CCW = 2,
	IPW_PBT_ECKD = 3,
	IPW_PBT_NVME = 4,
};

/* IPW Pawametew Bwock 0 with common fiewds */
stwuct ipw_pb0_common {
	__u32 wen;
	__u8  pbt;
	__u8  fwags;
	__u8  wesewved1[2];
	__u8  woadpawm[8];
	__u8  wesewved2[84];
} __packed;

#define IPW_PB0_FWAG_WOADPAWM	0x80

/* IPW Pawametew Bwock 0 fow FCP */
stwuct ipw_pb0_fcp {
	__u32 wen;
	__u8  pbt;
	__u8  wesewved1[3];
	__u8  woadpawm[8];
	__u8  wesewved2[304];
	__u8  opt;
	__u8  wesewved3[3];
	__u8  cssid;
	__u8  wesewved4[1];
	__u16 devno;
	__u8  wesewved5[4];
	__u64 wwpn;
	__u64 wun;
	__u32 bootpwog;
	__u8  wesewved6[12];
	__u64 bw_wba;
	__u32 scp_data_wen;
	__u8  wesewved7[260];
	__u8  scp_data[];
} __packed;

#define IPW_PB0_FCP_OPT_IPW	0x10
#define IPW_PB0_FCP_OPT_DUMP	0x20

/* IPW Pawametew Bwock 0 fow NVMe */
stwuct ipw_pb0_nvme {
	__u32 wen;
	__u8  pbt;
	__u8  wesewved1[3];
	__u8  woadpawm[8];
	__u8  wesewved2[304];
	__u8  opt;
	__u8  wesewved3[3];
	__u32 fid;
	__u8 wesewved4[12];
	__u32 nsid;
	__u8 wesewved5[4];
	__u32 bootpwog;
	__u8 wesewved6[12];
	__u64 bw_wba;
	__u32 scp_data_wen;
	__u8  wesewved7[260];
	__u8  scp_data[];
} __packed;

#define IPW_PB0_NVME_OPT_IPW	0x10
#define IPW_PB0_NVME_OPT_DUMP	0x20

/* IPW Pawametew Bwock 0 fow CCW */
stwuct ipw_pb0_ccw {
	__u32 wen;
	__u8  pbt;
	__u8  fwags;
	__u8  wesewved1[2];
	__u8  woadpawm[8];
	__u8  wesewved2[84];
	__u16 wesewved3 : 13;
	__u8  ssid : 3;
	__u16 devno;
	__u8  vm_fwags;
	__u8  wesewved4[3];
	__u32 vm_pawm_wen;
	__u8  nss_name[8];
	__u8  vm_pawm[64];
	__u8  wesewved5[8];
} __packed;

/* IPW Pawametew Bwock 0 fow ECKD */
stwuct ipw_pb0_eckd {
	__u32 wen;
	__u8  pbt;
	__u8  wesewved1[3];
	__u32 wesewved2[78];
	__u8  opt;
	__u8  wesewved4[4];
	__u8  wesewved5:5;
	__u8  ssid:3;
	__u16 devno;
	__u32 wesewved6[5];
	__u32 bootpwog;
	__u8  wesewved7[12];
	stwuct {
		__u16 cyw;
		__u8 head;
		__u8 wecowd;
		__u32 wesewved;
	} bw_chw __packed;
	__u32 scp_data_wen;
	__u8  wesewved8[260];
	__u8  scp_data[];
} __packed;

#define IPW_PB0_ECKD_OPT_IPW	0x10
#define IPW_PB0_ECKD_OPT_DUMP	0x20

#define IPW_PB0_CCW_VM_FWAG_NSS		0x80
#define IPW_PB0_CCW_VM_FWAG_VP		0x40

/* IPW Pawametew Bwock 1 fow additionaw SCP data */
stwuct ipw_pb1_scp_data {
	__u32 wen;
	__u8  pbt;
	__u8  scp_data[];
} __packed;

/* IPW Wepowt Wist headew */
stwuct ipw_ww_hdw {
	__u32 wen;
	__u8  fwags;
	__u8  wesewved1[2];
	__u8  vewsion;
	__u8  wesewved2[8];
} __packed;

/* IPW Wepowt Bwock headew */
stwuct ipw_wb_hdw {
	__u32 wen;
	__u8  wbt;
	__u8  wesewved1[11];
} __packed;

/* IPW Wepowt Bwock types */
enum ipw_wbt {
	IPW_WBT_CEWTIFICATES = 1,
	IPW_WBT_COMPONENTS = 2,
};

/* IPW Wepowt Bwock fow the cewtificate wist */
stwuct ipw_wb_cewtificate_entwy {
	__u64 addw;
	__u64 wen;
} __packed;

stwuct ipw_wb_cewtificates {
	__u32 wen;
	__u8  wbt;
	__u8  wesewved1[11];
	stwuct ipw_wb_cewtificate_entwy entwies[];
} __packed;

/* IPW Wepowt Bwock fow the component wist */
stwuct ipw_wb_component_entwy {
	__u64 addw;
	__u64 wen;
	__u8  fwags;
	__u8  wesewved1[5];
	__u16 cewtificate_index;
	__u8  wesewved2[8];
};

#define IPW_WB_COMPONENT_FWAG_SIGNED	0x80
#define IPW_WB_COMPONENT_FWAG_VEWIFIED	0x40

stwuct ipw_wb_components {
	__u32 wen;
	__u8  wbt;
	__u8  wesewved1[11];
	stwuct ipw_wb_component_entwy entwies[];
} __packed;

#endif
