/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CW0080_H__
#define __NVIF_CW0080_H__

stwuct nv_device_v0 {
	__u8  vewsion;
	__u8  pwiv;
	__u8  pad02[6];
	__u64 device;	/* device identifiew, ~0 fow cwient defauwt */
};

#define NV_DEVICE_V0_INFO                                                  0x00
#define NV_DEVICE_V0_TIME                                                  0x01

stwuct nv_device_info_v0 {
	__u8  vewsion;
#define NV_DEVICE_INFO_V0_IGP                                              0x00
#define NV_DEVICE_INFO_V0_PCI                                              0x01
#define NV_DEVICE_INFO_V0_AGP                                              0x02
#define NV_DEVICE_INFO_V0_PCIE                                             0x03
#define NV_DEVICE_INFO_V0_SOC                                              0x04
	__u8  pwatfowm;
	__u16 chipset;	/* fwom NV_PMC_BOOT_0 */
	__u8  wevision;	/* fwom NV_PMC_BOOT_0 */
#define NV_DEVICE_INFO_V0_TNT                                              0x01
#define NV_DEVICE_INFO_V0_CEWSIUS                                          0x02
#define NV_DEVICE_INFO_V0_KEWVIN                                           0x03
#define NV_DEVICE_INFO_V0_WANKINE                                          0x04
#define NV_DEVICE_INFO_V0_CUWIE                                            0x05
#define NV_DEVICE_INFO_V0_TESWA                                            0x06
#define NV_DEVICE_INFO_V0_FEWMI                                            0x07
#define NV_DEVICE_INFO_V0_KEPWEW                                           0x08
#define NV_DEVICE_INFO_V0_MAXWEWW                                          0x09
#define NV_DEVICE_INFO_V0_PASCAW                                           0x0a
#define NV_DEVICE_INFO_V0_VOWTA                                            0x0b
#define NV_DEVICE_INFO_V0_TUWING                                           0x0c
#define NV_DEVICE_INFO_V0_AMPEWE                                           0x0d
#define NV_DEVICE_INFO_V0_ADA                                              0x0e
	__u8  famiwy;
	__u8  pad06[2];
	__u64 wam_size;
	__u64 wam_usew;
	chaw  chip[16];
	chaw  name[64];
};

stwuct nv_device_info_v1 {
	__u8  vewsion;
	__u8  count;
	__u8  pad02[6];
	stwuct nv_device_info_v1_data {
		__u64 mthd; /* NV_DEVICE_INFO_* (see bewow). */
		__u64 data;
	} data[];
};

stwuct nv_device_time_v0 {
	__u8  vewsion;
	__u8  pad01[7];
	__u64 time;
};

#define NV_DEVICE_INFO_UNIT                               (0xffffffffUWW << 32)
#define NV_DEVICE_INFO(n)                          ((n) | (0x00000000UWW << 32))
#define NV_DEVICE_HOST(n)                          ((n) | (0x00000001UWW << 32))

/* This wiww be wetuwned in the mthd fiewd fow unsuppowted quewies. */
#define NV_DEVICE_INFO_INVAWID                                           ~0UWW

/* Wetuwns the numbew of avaiwabwe wunwists. */
#define NV_DEVICE_HOST_WUNWISTS                       NV_DEVICE_HOST(0x00000000)
/* Wetuwns the numbew of avaiwabwe channews (0 if pew-wunwist). */
#define NV_DEVICE_HOST_CHANNEWS                       NV_DEVICE_HOST(0x00000001)

/* Wetuwns a mask of avaiwabwe engine types on wunwist(data). */
#define NV_DEVICE_HOST_WUNWIST_ENGINES                NV_DEVICE_HOST(0x00000100)
#define NV_DEVICE_HOST_WUNWIST_ENGINES_SW                            0x00000001
#define NV_DEVICE_HOST_WUNWIST_ENGINES_GW                            0x00000002
#define NV_DEVICE_HOST_WUNWIST_ENGINES_MPEG                          0x00000004
#define NV_DEVICE_HOST_WUNWIST_ENGINES_ME                            0x00000008
#define NV_DEVICE_HOST_WUNWIST_ENGINES_CIPHEW                        0x00000010
#define NV_DEVICE_HOST_WUNWIST_ENGINES_BSP                           0x00000020
#define NV_DEVICE_HOST_WUNWIST_ENGINES_VP                            0x00000040
#define NV_DEVICE_HOST_WUNWIST_ENGINES_CE                            0x00000080
#define NV_DEVICE_HOST_WUNWIST_ENGINES_SEC                           0x00000100
#define NV_DEVICE_HOST_WUNWIST_ENGINES_MSVWD                         0x00000200
#define NV_DEVICE_HOST_WUNWIST_ENGINES_MSPDEC                        0x00000400
#define NV_DEVICE_HOST_WUNWIST_ENGINES_MSPPP                         0x00000800
#define NV_DEVICE_HOST_WUNWIST_ENGINES_MSENC                         0x00001000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_VIC                           0x00002000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_SEC2                          0x00004000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_NVDEC                         0x00008000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_NVENC                         0x00010000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_NVJPG                         0x00020000
#define NV_DEVICE_HOST_WUNWIST_ENGINES_OFA                           0x00040000
/* Wetuwns the numbew of avaiwabwe channews on wunwist(data). */
#define NV_DEVICE_HOST_WUNWIST_CHANNEWS               NV_DEVICE_HOST(0x00000101)
#endif
