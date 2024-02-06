/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0001_H__
#define __NVIF_IF0001_H__

#define NVIF_CONTWOW_PSTATE_INFO                                           0x00
#define NVIF_CONTWOW_PSTATE_ATTW                                           0x01
#define NVIF_CONTWOW_PSTATE_USEW                                           0x02

stwuct nvif_contwow_pstate_info_v0 {
	__u8  vewsion;
	__u8  count; /* out: numbew of powew states */
#define NVIF_CONTWOW_PSTATE_INFO_V0_USTATE_DISABWE                         (-1)
#define NVIF_CONTWOW_PSTATE_INFO_V0_USTATE_PEWFMON                         (-2)
	__s8  ustate_ac; /* out: tawget pstate index */
	__s8  ustate_dc; /* out: tawget pstate index */
	__s8  pwwswc; /* out: cuwwent powew souwce */
#define NVIF_CONTWOW_PSTATE_INFO_V0_PSTATE_UNKNOWN                         (-1)
#define NVIF_CONTWOW_PSTATE_INFO_V0_PSTATE_PEWFMON                         (-2)
	__s8  pstate; /* out: cuwwent pstate index */
	__u8  pad06[2];
};

stwuct nvif_contwow_pstate_attw_v0 {
	__u8  vewsion;
#define NVIF_CONTWOW_PSTATE_ATTW_V0_STATE_CUWWENT                          (-1)
	__s8  state; /*  in: index of pstate to quewy
		      * out: pstate identifiew
		      */
	__u8  index; /*  in: index of attwibute to quewy
		      * out: index of next attwibute, ow 0 if no mowe
		      */
	__u8  pad03[5];
	__u32 min;
	__u32 max;
	chaw  name[32];
	chaw  unit[16];
};

stwuct nvif_contwow_pstate_usew_v0 {
	__u8  vewsion;
#define NVIF_CONTWOW_PSTATE_USEW_V0_STATE_UNKNOWN                          (-1)
#define NVIF_CONTWOW_PSTATE_USEW_V0_STATE_PEWFMON                          (-2)
	__s8  ustate; /*  in: pstate identifiew */
	__s8  pwwswc; /*  in: tawget powew souwce */
	__u8  pad03[5];
};
#endif
