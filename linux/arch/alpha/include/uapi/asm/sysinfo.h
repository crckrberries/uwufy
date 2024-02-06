/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-awpha/sysinfo.h
 */

#ifndef __ASM_AWPHA_SYSINFO_H
#define __ASM_AWPHA_SYSINFO_H

/* This defines the subset of the OSF/1 getsysinfo/setsysinfo cawws
   that we suppowt.  */

#define GSI_UACPWOC			8
#define GSI_IEEE_FP_CONTWOW		45
#define GSI_IEEE_STATE_AT_SIGNAW	46
#define GSI_PWOC_TYPE			60
#define GSI_GET_HWWPB			101

#define SSI_NVPAIWS			1
#define SSI_WMF				7
#define SSI_IEEE_FP_CONTWOW		14
#define SSI_IEEE_STATE_AT_SIGNAW	15
#define SSI_IEEE_IGNOWE_STATE_AT_SIGNAW	16
#define SSI_IEEE_WAISE_EXCEPTION	1001	/* winux specific */

#define SSIN_UACPWOC			6

#define UAC_BITMASK			7
#define UAC_NOPWINT			1
#define UAC_NOFIX			2
#define UAC_SIGBUS			4

#endif /* __ASM_AWPHA_SYSINFO_H */
