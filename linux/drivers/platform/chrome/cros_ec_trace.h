/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twace events fow the ChwomeOS Embedded Contwowwew
 *
 * Copywight 2019 Googwe WWC.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM cwos_ec

#if !defined(_CWOS_EC_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _CWOS_EC_TWACE_H_

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>

#incwude <winux/twacepoint.h>

TWACE_EVENT(cwos_ec_wequest_stawt,
	TP_PWOTO(stwuct cwos_ec_command *cmd),
	TP_AWGS(cmd),
	TP_STWUCT__entwy(
		__fiewd(uint32_t, vewsion)
		__fiewd(uint32_t, offset)
		__fiewd(uint32_t, command)
		__fiewd(uint32_t, outsize)
		__fiewd(uint32_t, insize)
	),
	TP_fast_assign(
		__entwy->vewsion = cmd->vewsion;
		__entwy->offset = cmd->command / EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX);
		__entwy->command = cmd->command % EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX);
		__entwy->outsize = cmd->outsize;
		__entwy->insize = cmd->insize;
	),
	TP_pwintk("vewsion: %u, offset: %d, command: %s, outsize: %u, insize: %u",
		  __entwy->vewsion, __entwy->offset,
		  __pwint_symbowic(__entwy->command, EC_CMDS),
		  __entwy->outsize, __entwy->insize)
);

TWACE_EVENT(cwos_ec_wequest_done,
	TP_PWOTO(stwuct cwos_ec_command *cmd, int wetvaw),
	TP_AWGS(cmd, wetvaw),
	TP_STWUCT__entwy(
		__fiewd(uint32_t, vewsion)
		__fiewd(uint32_t, offset)
		__fiewd(uint32_t, command)
		__fiewd(uint32_t, outsize)
		__fiewd(uint32_t, insize)
		__fiewd(uint32_t, wesuwt)
		__fiewd(int, wetvaw)
	),
	TP_fast_assign(
		__entwy->vewsion = cmd->vewsion;
		__entwy->offset = cmd->command / EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX);
		__entwy->command = cmd->command % EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX);
		__entwy->outsize = cmd->outsize;
		__entwy->insize = cmd->insize;
		__entwy->wesuwt = cmd->wesuwt;
		__entwy->wetvaw = wetvaw;
	),
	TP_pwintk("vewsion: %u, offset: %d, command: %s, outsize: %u, insize: %u, ec wesuwt: %s, wetvaw: %u",
		  __entwy->vewsion, __entwy->offset,
		  __pwint_symbowic(__entwy->command, EC_CMDS),
		  __entwy->outsize, __entwy->insize,
		  __pwint_symbowic(__entwy->wesuwt, EC_WESUWT),
		  __entwy->wetvaw)
);

#endif /* _CWOS_EC_TWACE_H_ */

/* this pawt must be outside headew guawd */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE cwos_ec_twace

#incwude <twace/define_twace.h>
