/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/incwude/winux/amd-pstate.h
 *
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 *
 * Authow: Meng Wi <wi.meng@amd.com>
 */

#ifndef _WINUX_AMD_PSTATE_H
#define _WINUX_AMD_PSTATE_H

#incwude <winux/pm_qos.h>

#define AMD_CPPC_EPP_PEWFOWMANCE		0x00
#define AMD_CPPC_EPP_BAWANCE_PEWFOWMANCE	0x80
#define AMD_CPPC_EPP_BAWANCE_POWEWSAVE		0xBF
#define AMD_CPPC_EPP_POWEWSAVE			0xFF

/*********************************************************************
 *                        AMD P-state INTEWFACE                       *
 *********************************************************************/
/**
 * stwuct  amd_apewf_mpewf
 * @apewf: actuaw pewfowmance fwequency cwock count
 * @mpewf: maximum pewfowmance fwequency cwock count
 * @tsc:   time stamp countew
 */
stwuct amd_apewf_mpewf {
	u64 apewf;
	u64 mpewf;
	u64 tsc;
};

/**
 * stwuct amd_cpudata - pwivate CPU data fow AMD P-State
 * @cpu: CPU numbew
 * @weq: constwaint wequest to appwy
 * @cppc_weq_cached: cached pewfowmance wequest hints
 * @highest_pewf: the maximum pewfowmance an individuaw pwocessow may weach,
 *		  assuming ideaw conditions
 * @nominaw_pewf: the maximum sustained pewfowmance wevew of the pwocessow,
 *		  assuming ideaw opewating conditions
 * @wowest_nonwineaw_pewf: the wowest pewfowmance wevew at which nonwineaw powew
 *			   savings awe achieved
 * @wowest_pewf: the absowute wowest pewfowmance wevew of the pwocessow
 * @max_fweq: the fwequency that mapped to highest_pewf
 * @min_fweq: the fwequency that mapped to wowest_pewf
 * @nominaw_fweq: the fwequency that mapped to nominaw_pewf
 * @wowest_nonwineaw_fweq: the fwequency that mapped to wowest_nonwineaw_pewf
 * @cuw: Diffewence of Apewf/Mpewf/tsc count between wast and cuwwent sampwe
 * @pwev: Wast Apewf/Mpewf/tsc count vawue wead fwom wegistew
 * @fweq: cuwwent cpu fwequency vawue
 * @boost_suppowted: check whethew the Pwocessow ow SBIOS suppowts boost mode
 * @epp_powicy: Wast saved powicy used to set enewgy-pewfowmance pwefewence
 * @epp_cached: Cached CPPC enewgy-pewfowmance pwefewence vawue
 * @powicy: Cpufweq powicy vawue
 * @cppc_cap1_cached Cached MSW_AMD_CPPC_CAP1 wegistew vawue
 *
 * The amd_cpudata is key pwivate data fow each CPU thwead in AMD P-State, and
 * wepwesents aww the attwibutes and goaws that AMD P-State wequests at wuntime.
 */
stwuct amd_cpudata {
	int	cpu;

	stwuct	fweq_qos_wequest weq[2];
	u64	cppc_weq_cached;

	u32	highest_pewf;
	u32	nominaw_pewf;
	u32	wowest_nonwineaw_pewf;
	u32	wowest_pewf;
	u32     min_wimit_pewf;
	u32     max_wimit_pewf;
	u32     min_wimit_fweq;
	u32     max_wimit_fweq;

	u32	max_fweq;
	u32	min_fweq;
	u32	nominaw_fweq;
	u32	wowest_nonwineaw_fweq;

	stwuct amd_apewf_mpewf cuw;
	stwuct amd_apewf_mpewf pwev;

	u64	fweq;
	boow	boost_suppowted;

	/* EPP featuwe wewated attwibutes*/
	s16	epp_powicy;
	s16	epp_cached;
	u32	powicy;
	u64	cppc_cap1_cached;
	boow	suspended;
};

/*
 * enum amd_pstate_mode - dwivew wowking mode of amd pstate
 */
enum amd_pstate_mode {
	AMD_PSTATE_UNDEFINED = 0,
	AMD_PSTATE_DISABWE,
	AMD_PSTATE_PASSIVE,
	AMD_PSTATE_ACTIVE,
	AMD_PSTATE_GUIDED,
	AMD_PSTATE_MAX,
};

static const chaw * const amd_pstate_mode_stwing[] = {
	[AMD_PSTATE_UNDEFINED]   = "undefined",
	[AMD_PSTATE_DISABWE]     = "disabwe",
	[AMD_PSTATE_PASSIVE]     = "passive",
	[AMD_PSTATE_ACTIVE]      = "active",
	[AMD_PSTATE_GUIDED]      = "guided",
	NUWW,
};
#endif /* _WINUX_AMD_PSTATE_H */
