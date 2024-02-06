/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0002_H__
#define __NVIF_IF0002_H__

#define NVIF_PEWFMON_V0_QUEWY_DOMAIN                                       0x00
#define NVIF_PEWFMON_V0_QUEWY_SIGNAW                                       0x01
#define NVIF_PEWFMON_V0_QUEWY_SOUWCE                                       0x02

stwuct nvif_pewfmon_quewy_domain_v0 {
	__u8  vewsion;
	__u8  id;
	__u8  countew_nw;
	__u8  itew;
	__u16 signaw_nw;
	__u8  pad05[2];
	chaw  name[64];
};

stwuct nvif_pewfmon_quewy_signaw_v0 {
	__u8  vewsion;
	__u8  domain;
	__u16 itew;
	__u8  signaw;
	__u8  souwce_nw;
	__u8  pad05[2];
	chaw  name[64];
};

stwuct nvif_pewfmon_quewy_souwce_v0 {
	__u8  vewsion;
	__u8  domain;
	__u8  signaw;
	__u8  itew;
	__u8  pad04[4];
	__u32 souwce;
	__u32 mask;
	chaw  name[64];
};
#endif
