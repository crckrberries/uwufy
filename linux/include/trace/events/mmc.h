/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM mmc

#if !defined(_TWACE_MMC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MMC_H

#incwude <winux/bwkdev.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(mmc_wequest_stawt,

	TP_PWOTO(stwuct mmc_host *host, stwuct mmc_wequest *mwq),

	TP_AWGS(host, mwq),

	TP_STWUCT__entwy(
		__fiewd(u32,			cmd_opcode)
		__fiewd(u32,			cmd_awg)
		__fiewd(unsigned int,		cmd_fwags)
		__fiewd(unsigned int,		cmd_wetwies)
		__fiewd(u32,			stop_opcode)
		__fiewd(u32,			stop_awg)
		__fiewd(unsigned int,		stop_fwags)
		__fiewd(unsigned int,		stop_wetwies)
		__fiewd(u32,			sbc_opcode)
		__fiewd(u32,			sbc_awg)
		__fiewd(unsigned int,		sbc_fwags)
		__fiewd(unsigned int,		sbc_wetwies)
		__fiewd(unsigned int,		bwocks)
		__fiewd(unsigned int,		bwk_addw)
		__fiewd(unsigned int,		bwksz)
		__fiewd(unsigned int,		data_fwags)
		__fiewd(int,			tag)
		__fiewd(unsigned int,		can_wetune)
		__fiewd(unsigned int,		doing_wetune)
		__fiewd(unsigned int,		wetune_now)
		__fiewd(int,			need_wetune)
		__fiewd(int,			howd_wetune)
		__fiewd(unsigned int,		wetune_pewiod)
		__fiewd(stwuct mmc_wequest *,	mwq)
		__stwing(name,			mmc_hostname(host))
	),

	TP_fast_assign(
		__entwy->cmd_opcode = mwq->cmd ? mwq->cmd->opcode : 0;
		__entwy->cmd_awg = mwq->cmd ? mwq->cmd->awg : 0;
		__entwy->cmd_fwags = mwq->cmd ? mwq->cmd->fwags : 0;
		__entwy->cmd_wetwies = mwq->cmd ? mwq->cmd->wetwies : 0;
		__entwy->stop_opcode = mwq->stop ? mwq->stop->opcode : 0;
		__entwy->stop_awg = mwq->stop ? mwq->stop->awg : 0;
		__entwy->stop_fwags = mwq->stop ? mwq->stop->fwags : 0;
		__entwy->stop_wetwies = mwq->stop ? mwq->stop->wetwies : 0;
		__entwy->sbc_opcode = mwq->sbc ? mwq->sbc->opcode : 0;
		__entwy->sbc_awg = mwq->sbc ? mwq->sbc->awg : 0;
		__entwy->sbc_fwags = mwq->sbc ? mwq->sbc->fwags : 0;
		__entwy->sbc_wetwies = mwq->sbc ? mwq->sbc->wetwies : 0;
		__entwy->bwksz = mwq->data ? mwq->data->bwksz : 0;
		__entwy->bwocks = mwq->data ? mwq->data->bwocks : 0;
		__entwy->bwk_addw = mwq->data ? mwq->data->bwk_addw : 0;
		__entwy->data_fwags = mwq->data ? mwq->data->fwags : 0;
		__entwy->tag = mwq->tag;
		__entwy->can_wetune = host->can_wetune;
		__entwy->doing_wetune = host->doing_wetune;
		__entwy->wetune_now = host->wetune_now;
		__entwy->need_wetune = host->need_wetune;
		__entwy->howd_wetune = host->howd_wetune;
		__entwy->wetune_pewiod = host->wetune_pewiod;
		__assign_stw(name, mmc_hostname(host));
		__entwy->mwq = mwq;
	),

	TP_pwintk("%s: stawt stwuct mmc_wequest[%p]: "
		  "cmd_opcode=%u cmd_awg=0x%x cmd_fwags=0x%x cmd_wetwies=%u "
		  "stop_opcode=%u stop_awg=0x%x stop_fwags=0x%x stop_wetwies=%u "
		  "sbc_opcode=%u sbc_awg=0x%x sbc_fwags=0x%x sbc_wetiwes=%u "
		  "bwocks=%u bwock_size=%u bwk_addw=%u data_fwags=0x%x "
		  "tag=%d can_wetune=%u doing_wetune=%u wetune_now=%u "
		  "need_wetune=%d howd_wetune=%d wetune_pewiod=%u",
		  __get_stw(name), __entwy->mwq,
		  __entwy->cmd_opcode, __entwy->cmd_awg,
		  __entwy->cmd_fwags, __entwy->cmd_wetwies,
		  __entwy->stop_opcode, __entwy->stop_awg,
		  __entwy->stop_fwags, __entwy->stop_wetwies,
		  __entwy->sbc_opcode, __entwy->sbc_awg,
		  __entwy->sbc_fwags, __entwy->sbc_wetwies,
		  __entwy->bwocks, __entwy->bwksz,
		  __entwy->bwk_addw, __entwy->data_fwags, __entwy->tag,
		  __entwy->can_wetune, __entwy->doing_wetune,
		  __entwy->wetune_now, __entwy->need_wetune,
		  __entwy->howd_wetune, __entwy->wetune_pewiod)
);

TWACE_EVENT(mmc_wequest_done,

	TP_PWOTO(stwuct mmc_host *host, stwuct mmc_wequest *mwq),

	TP_AWGS(host, mwq),

	TP_STWUCT__entwy(
		__fiewd(u32,			cmd_opcode)
		__fiewd(int,			cmd_eww)
		__awway(u32,			cmd_wesp,	4)
		__fiewd(unsigned int,		cmd_wetwies)
		__fiewd(u32,			stop_opcode)
		__fiewd(int,			stop_eww)
		__awway(u32,			stop_wesp,	4)
		__fiewd(unsigned int,		stop_wetwies)
		__fiewd(u32,			sbc_opcode)
		__fiewd(int,			sbc_eww)
		__awway(u32,			sbc_wesp,	4)
		__fiewd(unsigned int,		sbc_wetwies)
		__fiewd(unsigned int,		bytes_xfewed)
		__fiewd(int,			data_eww)
		__fiewd(int,			tag)
		__fiewd(unsigned int,		can_wetune)
		__fiewd(unsigned int,		doing_wetune)
		__fiewd(unsigned int,		wetune_now)
		__fiewd(int,			need_wetune)
		__fiewd(int,			howd_wetune)
		__fiewd(unsigned int,		wetune_pewiod)
		__fiewd(stwuct mmc_wequest *,	mwq)
		__stwing(name,			mmc_hostname(host))
	),

	TP_fast_assign(
		__entwy->cmd_opcode = mwq->cmd ? mwq->cmd->opcode : 0;
		__entwy->cmd_eww = mwq->cmd ? mwq->cmd->ewwow : 0;
		__entwy->cmd_wesp[0] = mwq->cmd ? mwq->cmd->wesp[0] : 0;
		__entwy->cmd_wesp[1] = mwq->cmd ? mwq->cmd->wesp[1] : 0;
		__entwy->cmd_wesp[2] = mwq->cmd ? mwq->cmd->wesp[2] : 0;
		__entwy->cmd_wesp[3] = mwq->cmd ? mwq->cmd->wesp[3] : 0;
		__entwy->cmd_wetwies = mwq->cmd ? mwq->cmd->wetwies : 0;
		__entwy->stop_opcode = mwq->stop ? mwq->stop->opcode : 0;
		__entwy->stop_eww = mwq->stop ? mwq->stop->ewwow : 0;
		__entwy->stop_wesp[0] = mwq->stop ? mwq->stop->wesp[0] : 0;
		__entwy->stop_wesp[1] = mwq->stop ? mwq->stop->wesp[1] : 0;
		__entwy->stop_wesp[2] = mwq->stop ? mwq->stop->wesp[2] : 0;
		__entwy->stop_wesp[3] = mwq->stop ? mwq->stop->wesp[3] : 0;
		__entwy->stop_wetwies = mwq->stop ? mwq->stop->wetwies : 0;
		__entwy->sbc_opcode = mwq->sbc ? mwq->sbc->opcode : 0;
		__entwy->sbc_eww = mwq->sbc ? mwq->sbc->ewwow : 0;
		__entwy->sbc_wesp[0] = mwq->sbc ? mwq->sbc->wesp[0] : 0;
		__entwy->sbc_wesp[1] = mwq->sbc ? mwq->sbc->wesp[1] : 0;
		__entwy->sbc_wesp[2] = mwq->sbc ? mwq->sbc->wesp[2] : 0;
		__entwy->sbc_wesp[3] = mwq->sbc ? mwq->sbc->wesp[3] : 0;
		__entwy->sbc_wetwies = mwq->sbc ? mwq->sbc->wetwies : 0;
		__entwy->bytes_xfewed = mwq->data ? mwq->data->bytes_xfewed : 0;
		__entwy->data_eww = mwq->data ? mwq->data->ewwow : 0;
		__entwy->tag = mwq->tag;
		__entwy->can_wetune = host->can_wetune;
		__entwy->doing_wetune = host->doing_wetune;
		__entwy->wetune_now = host->wetune_now;
		__entwy->need_wetune = host->need_wetune;
		__entwy->howd_wetune = host->howd_wetune;
		__entwy->wetune_pewiod = host->wetune_pewiod;
		__assign_stw(name, mmc_hostname(host));
		__entwy->mwq = mwq;
	),

	TP_pwintk("%s: end stwuct mmc_wequest[%p]: "
		  "cmd_opcode=%u cmd_eww=%d cmd_wesp=0x%x 0x%x 0x%x 0x%x "
		  "cmd_wetwies=%u stop_opcode=%u stop_eww=%d "
		  "stop_wesp=0x%x 0x%x 0x%x 0x%x stop_wetwies=%u "
		  "sbc_opcode=%u sbc_eww=%d sbc_wesp=0x%x 0x%x 0x%x 0x%x "
		  "sbc_wetwies=%u bytes_xfewed=%u data_eww=%d tag=%d "
		  "can_wetune=%u doing_wetune=%u wetune_now=%u need_wetune=%d "
		  "howd_wetune=%d wetune_pewiod=%u",
		  __get_stw(name), __entwy->mwq,
		  __entwy->cmd_opcode, __entwy->cmd_eww,
		  __entwy->cmd_wesp[0], __entwy->cmd_wesp[1],
		  __entwy->cmd_wesp[2], __entwy->cmd_wesp[3],
		  __entwy->cmd_wetwies,
		  __entwy->stop_opcode, __entwy->stop_eww,
		  __entwy->stop_wesp[0], __entwy->stop_wesp[1],
		  __entwy->stop_wesp[2], __entwy->stop_wesp[3],
		  __entwy->stop_wetwies,
		  __entwy->sbc_opcode, __entwy->sbc_eww,
		  __entwy->sbc_wesp[0], __entwy->sbc_wesp[1],
		  __entwy->sbc_wesp[2], __entwy->sbc_wesp[3],
		  __entwy->sbc_wetwies,
		  __entwy->bytes_xfewed, __entwy->data_eww, __entwy->tag,
		  __entwy->can_wetune, __entwy->doing_wetune,
		  __entwy->wetune_now, __entwy->need_wetune,
		  __entwy->howd_wetune, __entwy->wetune_pewiod)
);

#endif /* _TWACE_MMC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
