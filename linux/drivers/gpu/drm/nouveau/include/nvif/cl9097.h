/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CW9097_H__
#define __NVIF_CW9097_H__

#define FEWMI_A_ZBC_COWOW                                                  0x00
#define FEWMI_A_ZBC_DEPTH                                                  0x01

stwuct fewmi_a_zbc_cowow_v0 {
	__u8  vewsion;
#define FEWMI_A_ZBC_COWOW_V0_FMT_ZEWO                                      0x01
#define FEWMI_A_ZBC_COWOW_V0_FMT_UNOWM_ONE                                 0x02
#define FEWMI_A_ZBC_COWOW_V0_FMT_WF32_GF32_BF32_AF32                       0x04
#define FEWMI_A_ZBC_COWOW_V0_FMT_W16_G16_B16_A16                           0x08
#define FEWMI_A_ZBC_COWOW_V0_FMT_WN16_GN16_BN16_AN16                       0x0c
#define FEWMI_A_ZBC_COWOW_V0_FMT_WS16_GS16_BS16_AS16                       0x10
#define FEWMI_A_ZBC_COWOW_V0_FMT_WU16_GU16_BU16_AU16                       0x14
#define FEWMI_A_ZBC_COWOW_V0_FMT_WF16_GF16_BF16_AF16                       0x16
#define FEWMI_A_ZBC_COWOW_V0_FMT_A8W8G8B8                                  0x18
#define FEWMI_A_ZBC_COWOW_V0_FMT_A8WW8GW8BW8                               0x1c
#define FEWMI_A_ZBC_COWOW_V0_FMT_A2B10G10W10                               0x20
#define FEWMI_A_ZBC_COWOW_V0_FMT_AU2BU10GU10WU10                           0x24
#define FEWMI_A_ZBC_COWOW_V0_FMT_A8B8G8W8                                  0x28
#define FEWMI_A_ZBC_COWOW_V0_FMT_A8BW8GW8WW8                               0x2c
#define FEWMI_A_ZBC_COWOW_V0_FMT_AN8BN8GN8WN8                              0x30
#define FEWMI_A_ZBC_COWOW_V0_FMT_AS8BS8GS8WS8                              0x34
#define FEWMI_A_ZBC_COWOW_V0_FMT_AU8BU8GU8WU8                              0x38
#define FEWMI_A_ZBC_COWOW_V0_FMT_A2W10G10B10                               0x3c
#define FEWMI_A_ZBC_COWOW_V0_FMT_BF10GF11WF11                              0x40
	__u8  fowmat;
	__u8  index;
	__u8  pad03[5];
	__u32 ds[4];
	__u32 w2[4];
};

stwuct fewmi_a_zbc_depth_v0 {
	__u8  vewsion;
#define FEWMI_A_ZBC_DEPTH_V0_FMT_FP32                                      0x01
	__u8  fowmat;
	__u8  index;
	__u8  pad03[5];
	__u32 ds;
	__u32 w2;
};
#endif
