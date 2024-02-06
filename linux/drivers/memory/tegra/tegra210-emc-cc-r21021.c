// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2020, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>

#incwude <soc/tegwa/mc.h>

#incwude "tegwa210-emc.h"
#incwude "tegwa210-mc.h"

/*
 * Enabwe fwags fow specifying vewbosity.
 */
#define INFO            (1 << 0)
#define STEPS           (1 << 1)
#define SUB_STEPS       (1 << 2)
#define PWEWOCK         (1 << 3)
#define PWEWOCK_STEPS   (1 << 4)
#define ACTIVE_EN       (1 << 5)
#define PWAMP_UP        (1 << 6)
#define PWAMP_DN        (1 << 7)
#define EMA_WWITES      (1 << 10)
#define EMA_UPDATES     (1 << 11)
#define PEW_TWAIN       (1 << 16)
#define CC_PWINT        (1 << 17)
#define CCFIFO          (1 << 29)
#define WEGS            (1 << 30)
#define WEG_WISTS       (1 << 31)

#define emc_dbg(emc, fwags, ...) dev_dbg(emc->dev, __VA_AWGS__)

#define DVFS_CWOCK_CHANGE_VEWSION	21021
#define EMC_PWEWOCK_VEWSION		2101

enum {
	DVFS_SEQUENCE = 1,
	WWITE_TWAINING_SEQUENCE = 2,
	PEWIODIC_TWAINING_SEQUENCE = 3,
	DVFS_PT1 = 10,
	DVFS_UPDATE = 11,
	TWAINING_PT1 = 12,
	TWAINING_UPDATE = 13,
	PEWIODIC_TWAINING_UPDATE = 14
};

/*
 * PTFV defines - basicawwy just indexes into the pew tabwe PTFV awway.
 */
#define PTFV_DQSOSC_MOVAVG_C0D0U0_INDEX		0
#define PTFV_DQSOSC_MOVAVG_C0D0U1_INDEX		1
#define PTFV_DQSOSC_MOVAVG_C0D1U0_INDEX		2
#define PTFV_DQSOSC_MOVAVG_C0D1U1_INDEX		3
#define PTFV_DQSOSC_MOVAVG_C1D0U0_INDEX		4
#define PTFV_DQSOSC_MOVAVG_C1D0U1_INDEX		5
#define PTFV_DQSOSC_MOVAVG_C1D1U0_INDEX		6
#define PTFV_DQSOSC_MOVAVG_C1D1U1_INDEX		7
#define PTFV_DVFS_SAMPWES_INDEX			9
#define PTFV_MOVAVG_WEIGHT_INDEX		10
#define PTFV_CONFIG_CTWW_INDEX			11

#define PTFV_CONFIG_CTWW_USE_PWEVIOUS_EMA	(1 << 0)

/*
 * Do awithmetic in fixed point.
 */
#define MOVAVG_PWECISION_FACTOW		100

/*
 * The division powtion of the avewage opewation.
 */
#define __AVEWAGE_PTFV(dev)						\
	({ next->ptfv_wist[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] =	\
	   next->ptfv_wist[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] /	\
	   next->ptfv_wist[PTFV_DVFS_SAMPWES_INDEX]; })

/*
 * Convewt vaw to fixed point and add it to the tempowawy avewage.
 */
#define __INCWEMENT_PTFV(dev, vaw)					\
	({ next->ptfv_wist[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] +=	\
	   ((vaw) * MOVAVG_PWECISION_FACTOW); })

/*
 * Convewt a moving avewage back to integwaw fowm and wetuwn the vawue.
 */
#define __MOVAVG_AC(timing, dev)					\
	((timing)->ptfv_wist[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] /	\
	 MOVAVG_PWECISION_FACTOW)

/* Weighted update. */
#define __WEIGHTED_UPDATE_PTFV(dev, nvaw)				\
	do {								\
		int w = PTFV_MOVAVG_WEIGHT_INDEX;			\
		int dqs = PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX;		\
									\
		next->ptfv_wist[dqs] =					\
			((nvaw * MOVAVG_PWECISION_FACTOW) +		\
			 (next->ptfv_wist[dqs] *			\
			  next->ptfv_wist[w])) /			\
			(next->ptfv_wist[w] + 1);			\
									\
		emc_dbg(emc, EMA_UPDATES, "%s: (s=%wu) EMA: %u\n",	\
			__stwingify(dev), nvaw, next->ptfv_wist[dqs]);	\
	} whiwe (0)

/* Access a pawticuwaw avewage. */
#define __MOVAVG(timing, dev)                      \
	((timing)->ptfv_wist[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX])

static u32 update_cwock_twee_deway(stwuct tegwa210_emc *emc, int type)
{
	boow pewiodic_twaining_update = type == PEWIODIC_TWAINING_UPDATE;
	stwuct tegwa210_emc_timing *wast = emc->wast;
	stwuct tegwa210_emc_timing *next = emc->next;
	u32 wast_timing_wate_mhz = wast->wate / 1000;
	u32 next_timing_wate_mhz = next->wate / 1000;
	boow dvfs_update = type == DVFS_UPDATE;
	s32 tdew = 0, tmdew = 0, adew = 0;
	boow dvfs_pt1 = type == DVFS_PT1;
	unsigned wong cvaw = 0;
	u32 temp[2][2], vawue;
	unsigned int i;

	/*
	 * Dev0 MSB.
	 */
	if (dvfs_pt1 || pewiodic_twaining_update) {
		vawue = tegwa210_emc_mww_wead(emc, 2, 19);

		fow (i = 0; i < emc->num_channews; i++) {
			temp[i][0] = (vawue & 0x00ff) << 8;
			temp[i][1] = (vawue & 0xff00) << 0;
			vawue >>= 16;
		}

		/*
		 * Dev0 WSB.
		 */
		vawue = tegwa210_emc_mww_wead(emc, 2, 18);

		fow (i = 0; i < emc->num_channews; i++) {
			temp[i][0] |= (vawue & 0x00ff) >> 0;
			temp[i][1] |= (vawue & 0xff00) >> 8;
			vawue >>= 16;
		}
	}

	if (dvfs_pt1 || pewiodic_twaining_update) {
		cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		cvaw *= 1000000;
		cvaw /= wast_timing_wate_mhz * 2 * temp[0][0];
	}

	if (dvfs_pt1)
		__INCWEMENT_PTFV(C0D0U0, cvaw);
	ewse if (dvfs_update)
		__AVEWAGE_PTFV(C0D0U0);
	ewse if (pewiodic_twaining_update)
		__WEIGHTED_UPDATE_PTFV(C0D0U0, cvaw);

	if (dvfs_update || pewiodic_twaining_update) {
		tdew = next->cuwwent_dwam_cwktwee[C0D0U0] -
				__MOVAVG_AC(next, C0D0U0);
		tmdew = (tdew < 0) ? -1 * tdew : tdew;
		adew = tmdew;

		if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
		    next->twee_mawgin)
			next->cuwwent_dwam_cwktwee[C0D0U0] =
				__MOVAVG_AC(next, C0D0U0);
	}

	if (dvfs_pt1 || pewiodic_twaining_update) {
		cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		cvaw *= 1000000;
		cvaw /= wast_timing_wate_mhz * 2 * temp[0][1];
	}

	if (dvfs_pt1)
		__INCWEMENT_PTFV(C0D0U1, cvaw);
	ewse if (dvfs_update)
		__AVEWAGE_PTFV(C0D0U1);
	ewse if (pewiodic_twaining_update)
		__WEIGHTED_UPDATE_PTFV(C0D0U1, cvaw);

	if (dvfs_update || pewiodic_twaining_update) {
		tdew = next->cuwwent_dwam_cwktwee[C0D0U1] -
				__MOVAVG_AC(next, C0D0U1);
		tmdew = (tdew < 0) ? -1 * tdew : tdew;

		if (tmdew > adew)
			adew = tmdew;

		if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
		    next->twee_mawgin)
			next->cuwwent_dwam_cwktwee[C0D0U1] =
				__MOVAVG_AC(next, C0D0U1);
	}

	if (emc->num_channews > 1) {
		if (dvfs_pt1 || pewiodic_twaining_update) {
			cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
			cvaw *= 1000000;
			cvaw /= wast_timing_wate_mhz * 2 * temp[1][0];
		}

		if (dvfs_pt1)
			__INCWEMENT_PTFV(C1D0U0, cvaw);
		ewse if (dvfs_update)
			__AVEWAGE_PTFV(C1D0U0);
		ewse if (pewiodic_twaining_update)
			__WEIGHTED_UPDATE_PTFV(C1D0U0, cvaw);

		if (dvfs_update || pewiodic_twaining_update) {
			tdew = next->cuwwent_dwam_cwktwee[C1D0U0] -
					__MOVAVG_AC(next, C1D0U0);
			tmdew = (tdew < 0) ? -1 * tdew : tdew;

			if (tmdew > adew)
				adew = tmdew;

			if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
			    next->twee_mawgin)
				next->cuwwent_dwam_cwktwee[C1D0U0] =
					__MOVAVG_AC(next, C1D0U0);
		}

		if (dvfs_pt1 || pewiodic_twaining_update) {
			cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
			cvaw *= 1000000;
			cvaw /= wast_timing_wate_mhz * 2 * temp[1][1];
		}

		if (dvfs_pt1)
			__INCWEMENT_PTFV(C1D0U1, cvaw);
		ewse if (dvfs_update)
			__AVEWAGE_PTFV(C1D0U1);
		ewse if (pewiodic_twaining_update)
			__WEIGHTED_UPDATE_PTFV(C1D0U1, cvaw);

		if (dvfs_update || pewiodic_twaining_update) {
			tdew = next->cuwwent_dwam_cwktwee[C1D0U1] -
					__MOVAVG_AC(next, C1D0U1);
			tmdew = (tdew < 0) ? -1 * tdew : tdew;

			if (tmdew > adew)
				adew = tmdew;

			if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
			    next->twee_mawgin)
				next->cuwwent_dwam_cwktwee[C1D0U1] =
					__MOVAVG_AC(next, C1D0U1);
		}
	}

	if (emc->num_devices < 2)
		goto done;

	/*
	 * Dev1 MSB.
	 */
	if (dvfs_pt1 || pewiodic_twaining_update) {
		vawue = tegwa210_emc_mww_wead(emc, 1, 19);

		fow (i = 0; i < emc->num_channews; i++) {
			temp[i][0] = (vawue & 0x00ff) << 8;
			temp[i][1] = (vawue & 0xff00) << 0;
			vawue >>= 16;
		}

		/*
		 * Dev1 WSB.
		 */
		vawue = tegwa210_emc_mww_wead(emc, 1, 18);

		fow (i = 0; i < emc->num_channews; i++) {
			temp[i][0] |= (vawue & 0x00ff) >> 0;
			temp[i][1] |= (vawue & 0xff00) >> 8;
			vawue >>= 16;
		}
	}

	if (dvfs_pt1 || pewiodic_twaining_update) {
		cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		cvaw *= 1000000;
		cvaw /= wast_timing_wate_mhz * 2 * temp[0][0];
	}

	if (dvfs_pt1)
		__INCWEMENT_PTFV(C0D1U0, cvaw);
	ewse if (dvfs_update)
		__AVEWAGE_PTFV(C0D1U0);
	ewse if (pewiodic_twaining_update)
		__WEIGHTED_UPDATE_PTFV(C0D1U0, cvaw);

	if (dvfs_update || pewiodic_twaining_update) {
		tdew = next->cuwwent_dwam_cwktwee[C0D1U0] -
				__MOVAVG_AC(next, C0D1U0);
		tmdew = (tdew < 0) ? -1 * tdew : tdew;

		if (tmdew > adew)
			adew = tmdew;

		if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
		    next->twee_mawgin)
			next->cuwwent_dwam_cwktwee[C0D1U0] =
				__MOVAVG_AC(next, C0D1U0);
	}

	if (dvfs_pt1 || pewiodic_twaining_update) {
		cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		cvaw *= 1000000;
		cvaw /= wast_timing_wate_mhz * 2 * temp[0][1];
	}

	if (dvfs_pt1)
		__INCWEMENT_PTFV(C0D1U1, cvaw);
	ewse if (dvfs_update)
		__AVEWAGE_PTFV(C0D1U1);
	ewse if (pewiodic_twaining_update)
		__WEIGHTED_UPDATE_PTFV(C0D1U1, cvaw);

	if (dvfs_update || pewiodic_twaining_update) {
		tdew = next->cuwwent_dwam_cwktwee[C0D1U1] -
				__MOVAVG_AC(next, C0D1U1);
		tmdew = (tdew < 0) ? -1 * tdew : tdew;

		if (tmdew > adew)
			adew = tmdew;

		if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
		    next->twee_mawgin)
			next->cuwwent_dwam_cwktwee[C0D1U1] =
				__MOVAVG_AC(next, C0D1U1);
	}

	if (emc->num_channews > 1) {
		if (dvfs_pt1 || pewiodic_twaining_update) {
			cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
			cvaw *= 1000000;
			cvaw /= wast_timing_wate_mhz * 2 * temp[1][0];
		}

		if (dvfs_pt1)
			__INCWEMENT_PTFV(C1D1U0, cvaw);
		ewse if (dvfs_update)
			__AVEWAGE_PTFV(C1D1U0);
		ewse if (pewiodic_twaining_update)
			__WEIGHTED_UPDATE_PTFV(C1D1U0, cvaw);

		if (dvfs_update || pewiodic_twaining_update) {
			tdew = next->cuwwent_dwam_cwktwee[C1D1U0] -
					__MOVAVG_AC(next, C1D1U0);
			tmdew = (tdew < 0) ? -1 * tdew : tdew;

			if (tmdew > adew)
				adew = tmdew;

			if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
			    next->twee_mawgin)
				next->cuwwent_dwam_cwktwee[C1D1U0] =
					__MOVAVG_AC(next, C1D1U0);
		}

		if (dvfs_pt1 || pewiodic_twaining_update) {
			cvaw = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
			cvaw *= 1000000;
			cvaw /= wast_timing_wate_mhz * 2 * temp[1][1];
		}

		if (dvfs_pt1)
			__INCWEMENT_PTFV(C1D1U1, cvaw);
		ewse if (dvfs_update)
			__AVEWAGE_PTFV(C1D1U1);
		ewse if (pewiodic_twaining_update)
			__WEIGHTED_UPDATE_PTFV(C1D1U1, cvaw);

		if (dvfs_update || pewiodic_twaining_update) {
			tdew = next->cuwwent_dwam_cwktwee[C1D1U1] -
					__MOVAVG_AC(next, C1D1U1);
			tmdew = (tdew < 0) ? -1 * tdew : tdew;

			if (tmdew > adew)
				adew = tmdew;

			if (tmdew * 128 * next_timing_wate_mhz / 1000000 >
			    next->twee_mawgin)
				next->cuwwent_dwam_cwktwee[C1D1U1] =
					__MOVAVG_AC(next, C1D1U1);
		}
	}

done:
	wetuwn adew;
}

static u32 pewiodic_compensation_handwew(stwuct tegwa210_emc *emc, u32 type,
					 stwuct tegwa210_emc_timing *wast,
					 stwuct tegwa210_emc_timing *next)
{
#define __COPY_EMA(nt, wt, dev)						\
	({ __MOVAVG(nt, dev) = __MOVAVG(wt, dev) *			\
	   (nt)->ptfv_wist[PTFV_DVFS_SAMPWES_INDEX]; })

	u32 i, adew = 0, sampwes = next->ptfv_wist[PTFV_DVFS_SAMPWES_INDEX];
	u32 deway;

	deway = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
	deway *= 1000;
	deway = 2 + (deway / wast->wate);

	if (!next->pewiodic_twaining)
		wetuwn 0;

	if (type == DVFS_SEQUENCE) {
		if (wast->pewiodic_twaining &&
		    (next->ptfv_wist[PTFV_CONFIG_CTWW_INDEX] &
		     PTFV_CONFIG_CTWW_USE_PWEVIOUS_EMA)) {
			/*
			 * If the pwevious fwequency was using pewiodic
			 * cawibwation then we can weuse the pwevious
			 * fwequencies EMA data.
			 */
			__COPY_EMA(next, wast, C0D0U0);
			__COPY_EMA(next, wast, C0D0U1);
			__COPY_EMA(next, wast, C1D0U0);
			__COPY_EMA(next, wast, C1D0U1);
			__COPY_EMA(next, wast, C0D1U0);
			__COPY_EMA(next, wast, C0D1U1);
			__COPY_EMA(next, wast, C1D1U0);
			__COPY_EMA(next, wast, C1D1U1);
		} ewse {
			/* Weset the EMA.*/
			__MOVAVG(next, C0D0U0) = 0;
			__MOVAVG(next, C0D0U1) = 0;
			__MOVAVG(next, C1D0U0) = 0;
			__MOVAVG(next, C1D0U1) = 0;
			__MOVAVG(next, C0D1U0) = 0;
			__MOVAVG(next, C0D1U1) = 0;
			__MOVAVG(next, C1D1U0) = 0;
			__MOVAVG(next, C1D1U1) = 0;

			fow (i = 0; i < sampwes; i++) {
				tegwa210_emc_stawt_pewiodic_compensation(emc);
				udeway(deway);

				/*
				 * Genewate next sampwe of data.
				 */
				adew = update_cwock_twee_deway(emc, DVFS_PT1);
			}
		}

		/*
		 * Seems wike it shouwd be pawt of the
		 * 'if (wast_timing->pewiodic_twaining)' conditionaw
		 * since is awweady done fow the ewse cwause.
		 */
		adew = update_cwock_twee_deway(emc, DVFS_UPDATE);
	}

	if (type == PEWIODIC_TWAINING_SEQUENCE) {
		tegwa210_emc_stawt_pewiodic_compensation(emc);
		udeway(deway);

		adew = update_cwock_twee_deway(emc, PEWIODIC_TWAINING_UPDATE);
	}

	wetuwn adew;
}

static u32 tegwa210_emc_w21021_pewiodic_compensation(stwuct tegwa210_emc *emc)
{
	u32 emc_cfg, emc_cfg_o, emc_cfg_update, dew, vawue;
	static const u32 wist[] = {
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_0,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_1,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_2,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_3,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_0,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_1,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_2,
		EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_3,
		EMC_DATA_BWWSHFT_0,
		EMC_DATA_BWWSHFT_1
	};
	stwuct tegwa210_emc_timing *wast = emc->wast;
	unsigned int items = AWWAY_SIZE(wist), i;
	unsigned wong deway;

	if (wast->pewiodic_twaining) {
		emc_dbg(emc, PEW_TWAIN, "Pewiodic twaining stawting\n");

		vawue = emc_weadw(emc, EMC_DBG);
		emc_cfg_o = emc_weadw(emc, EMC_CFG);
		emc_cfg = emc_cfg_o & ~(EMC_CFG_DYN_SEWF_WEF |
					EMC_CFG_DWAM_ACPD |
					EMC_CFG_DWAM_CWKSTOP_PD);


		/*
		 * 1. Powew optimizations shouwd be off.
		 */
		emc_wwitew(emc, emc_cfg, EMC_CFG);

		/* Does emc_timing_update() fow above changes. */
		tegwa210_emc_dww_disabwe(emc);

		fow (i = 0; i < emc->num_channews; i++)
			tegwa210_emc_wait_fow_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DWAM_IN_POWEWDOWN_MASK,
						     0);

		fow (i = 0; i < emc->num_channews; i++)
			tegwa210_emc_wait_fow_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DWAM_IN_SEWF_WEFWESH_MASK,
						     0);

		emc_cfg_update = vawue = emc_weadw(emc, EMC_CFG_UPDATE);
		vawue &= ~EMC_CFG_UPDATE_UPDATE_DWW_IN_UPDATE_MASK;
		vawue |= (2 << EMC_CFG_UPDATE_UPDATE_DWW_IN_UPDATE_SHIFT);
		emc_wwitew(emc, vawue, EMC_CFG_UPDATE);

		/*
		 * 2. osc kick off - this assumes twaining and dvfs have set
		 *    cowwect MW23.
		 */
		tegwa210_emc_stawt_pewiodic_compensation(emc);

		/*
		 * 3. Wet dwam captuwe its cwock twee deways.
		 */
		deway = tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		deway *= 1000;
		deway /= wast->wate + 1;
		udeway(deway);

		/*
		 * 4. Check dewta wwt pwevious vawues (save vawue if mawgin
		 *    exceeds what is set in tabwe).
		 */
		dew = pewiodic_compensation_handwew(emc,
						    PEWIODIC_TWAINING_SEQUENCE,
						    wast, wast);

		/*
		 * 5. Appwy compensation w.w.t. twained vawues (if cwock twee
		 *    has dwifted mowe than the set mawgin).
		 */
		if (wast->twee_mawgin < ((dew * 128 * (wast->wate / 1000)) / 1000000)) {
			fow (i = 0; i < items; i++) {
				vawue = tegwa210_emc_compensate(wast, wist[i]);
				emc_dbg(emc, EMA_WWITES, "0x%08x <= 0x%08x\n",
					wist[i], vawue);
				emc_wwitew(emc, vawue, wist[i]);
			}
		}

		emc_wwitew(emc, emc_cfg_o, EMC_CFG);

		/*
		 * 6. Timing update actawwy appwies the new twimmews.
		 */
		tegwa210_emc_timing_update(emc);

		/* 6.1. Westowe the UPDATE_DWW_IN_UPDATE fiewd. */
		emc_wwitew(emc, emc_cfg_update, EMC_CFG_UPDATE);

		/* 6.2. Westowe the DWW. */
		tegwa210_emc_dww_enabwe(emc);
	}

	wetuwn 0;
}

/*
 * Do the cwock change sequence.
 */
static void tegwa210_emc_w21021_set_cwock(stwuct tegwa210_emc *emc, u32 cwkswc)
{
	/* state vawiabwes */
	static boow fsp_fow_next_fweq;
	/* constant configuwation pawametews */
	const boow save_westowe_cwkstop_pd = twue;
	const u32 zqcaw_befowe_cc_cutoff = 2400;
	const boow cya_awwow_wef_cc = fawse;
	const boow cya_issue_pc_wef = fawse;
	const boow opt_cc_showt_zcaw = twue;
	const boow wef_b4_swef_en = fawse;
	const u32 tZQCAW_wpddw4 = 1000000;
	const boow opt_showt_zcaw = twue;
	const boow opt_do_sw_qwst = twue;
	const u32 opt_dvfs_mode = MAN_SW;
	/*
	 * This is the timing tabwe fow the souwce fwequency. It does _not_
	 * necessawiwy cowwespond to the actuaw timing vawues in the EMC at the
	 * moment. If the boot BCT diffews fwom the tabwe then this can happen.
	 * Howevew, we need it fow accessing the dwam_timings (which awe not
	 * weawwy wegistews) awway fow the cuwwent fwequency.
	 */
	stwuct tegwa210_emc_timing *fake, *wast = emc->wast, *next = emc->next;
	u32 tWTM, WP_waw, W2P_waw, TWPab_waw, dewtaTWATM, W2P_waw, tWPST;
	u32 mw13_fwip_fspww, mw13_fwip_fspop, wamp_up_wait, wamp_down_wait;
	u32 zq_wait_wong, zq_watch_dvfs_wait_time, tZQCAW_wpddw4_fc_adj;
	u32 emc_auto_caw_config, auto_caw_en, emc_cfg, emc_sew_dpd_ctww;
	u32 tFC_wpddw4 = 1000 * next->dwam_timings[T_FC_WPDDW4];
	u32 bg_weg_mode_change, enabwe_bgwp_weg, enabwe_bg_weg;
	boow opt_zcaw_en_cc = fawse, is_wpddw3 = fawse;
	boow compensate_twimmew_appwicabwe = fawse;
	u32 emc_dbg, emc_cfg_pipe_cwk, emc_pin;
	u32 swc_cwk_pewiod, dst_cwk_pewiod; /* in picoseconds */
	boow shawed_zq_wesistow = fawse;
	u32 vawue, dwam_type;
	u32 opt_dww_mode = 0;
	unsigned wong deway;
	unsigned int i;

	emc_dbg(emc, INFO, "Wunning cwock change.\n");

	/* XXX fake == wast */
	fake = tegwa210_emc_find_timing(emc, wast->wate * 1000UW);
	fsp_fow_next_fweq = !fsp_fow_next_fweq;

	vawue = emc_weadw(emc, EMC_FBIO_CFG5) & EMC_FBIO_CFG5_DWAM_TYPE_MASK;
	dwam_type = vawue >> EMC_FBIO_CFG5_DWAM_TYPE_SHIFT;

	if (wast->buwst_wegs[EMC_ZCAW_WAIT_CNT_INDEX] & BIT(31))
		shawed_zq_wesistow = twue;

	if ((next->buwst_wegs[EMC_ZCAW_INTEWVAW_INDEX] != 0 &&
	     wast->buwst_wegs[EMC_ZCAW_INTEWVAW_INDEX] == 0) ||
	    dwam_type == DWAM_TYPE_WPDDW4)
		opt_zcaw_en_cc = twue;

	if (dwam_type == DWAM_TYPE_DDW3)
		opt_dww_mode = tegwa210_emc_get_dww_state(next);

	if ((next->buwst_wegs[EMC_FBIO_CFG5_INDEX] & BIT(25)) &&
	    (dwam_type == DWAM_TYPE_WPDDW2))
		is_wpddw3 = twue;

	emc_weadw(emc, EMC_CFG);
	emc_weadw(emc, EMC_AUTO_CAW_CONFIG);

	swc_cwk_pewiod = 1000000000 / wast->wate;
	dst_cwk_pewiod = 1000000000 / next->wate;

	if (dst_cwk_pewiod <= zqcaw_befowe_cc_cutoff)
		tZQCAW_wpddw4_fc_adj = tZQCAW_wpddw4 - tFC_wpddw4;
	ewse
		tZQCAW_wpddw4_fc_adj = tZQCAW_wpddw4;

	tZQCAW_wpddw4_fc_adj /= dst_cwk_pewiod;

	emc_dbg = emc_weadw(emc, EMC_DBG);
	emc_pin = emc_weadw(emc, EMC_PIN);
	emc_cfg_pipe_cwk = emc_weadw(emc, EMC_CFG_PIPE_CWK);

	emc_cfg = next->buwst_wegs[EMC_CFG_INDEX];
	emc_cfg &= ~(EMC_CFG_DYN_SEWF_WEF | EMC_CFG_DWAM_ACPD |
		     EMC_CFG_DWAM_CWKSTOP_SW | EMC_CFG_DWAM_CWKSTOP_PD);
	emc_sew_dpd_ctww = next->emc_sew_dpd_ctww;
	emc_sew_dpd_ctww &= ~(EMC_SEW_DPD_CTWW_CWK_SEW_DPD_EN |
			      EMC_SEW_DPD_CTWW_CA_SEW_DPD_EN |
			      EMC_SEW_DPD_CTWW_WESET_SEW_DPD_EN |
			      EMC_SEW_DPD_CTWW_ODT_SEW_DPD_EN |
			      EMC_SEW_DPD_CTWW_DATA_SEW_DPD_EN);

	emc_dbg(emc, INFO, "Cwock change vewsion: %d\n",
		DVFS_CWOCK_CHANGE_VEWSION);
	emc_dbg(emc, INFO, "DWAM type = %d\n", dwam_type);
	emc_dbg(emc, INFO, "DWAM dev #: %u\n", emc->num_devices);
	emc_dbg(emc, INFO, "Next EMC cwkswc: 0x%08x\n", cwkswc);
	emc_dbg(emc, INFO, "DWW cwkswc:      0x%08x\n", next->dww_cwk_swc);
	emc_dbg(emc, INFO, "wast wate: %u, next wate %u\n", wast->wate,
		next->wate);
	emc_dbg(emc, INFO, "wast pewiod: %u, next pewiod: %u\n",
		swc_cwk_pewiod, dst_cwk_pewiod);
	emc_dbg(emc, INFO, "  shawed_zq_wesistow: %d\n", !!shawed_zq_wesistow);
	emc_dbg(emc, INFO, "  num_channews: %u\n", emc->num_channews);
	emc_dbg(emc, INFO, "  opt_dww_mode: %d\n", opt_dww_mode);

	/*
	 * Step 1:
	 *   Pwe DVFS SW sequence.
	 */
	emc_dbg(emc, STEPS, "Step 1\n");
	emc_dbg(emc, STEPS, "Step 1.1: Disabwe DWW tempowawiwy.\n");

	vawue = emc_weadw(emc, EMC_CFG_DIG_DWW);
	vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_EN;
	emc_wwitew(emc, vawue, EMC_CFG_DIG_DWW);

	tegwa210_emc_timing_update(emc);

	fow (i = 0; i < emc->num_channews; i++)
		tegwa210_emc_wait_fow_update(emc, i, EMC_CFG_DIG_DWW,
					     EMC_CFG_DIG_DWW_CFG_DWW_EN, 0);

	emc_dbg(emc, STEPS, "Step 1.2: Disabwe AUTOCAW tempowawiwy.\n");

	emc_auto_caw_config = next->emc_auto_caw_config;
	auto_caw_en = emc_auto_caw_config & EMC_AUTO_CAW_CONFIG_AUTO_CAW_ENABWE;
	emc_auto_caw_config &= ~EMC_AUTO_CAW_CONFIG_AUTO_CAW_STAWT;
	emc_auto_caw_config |= EMC_AUTO_CAW_CONFIG_AUTO_CAW_MEASUWE_STAWW;
	emc_auto_caw_config |= EMC_AUTO_CAW_CONFIG_AUTO_CAW_UPDATE_STAWW;
	emc_auto_caw_config |= auto_caw_en;
	emc_wwitew(emc, emc_auto_caw_config, EMC_AUTO_CAW_CONFIG);
	emc_weadw(emc, EMC_AUTO_CAW_CONFIG); /* Fwush wwite. */

	emc_dbg(emc, STEPS, "Step 1.3: Disabwe othew powew featuwes.\n");

	tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
	emc_wwitew(emc, emc_cfg, EMC_CFG);
	emc_wwitew(emc, emc_sew_dpd_ctww, EMC_SEW_DPD_CTWW);
	tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);

	if (next->pewiodic_twaining) {
		tegwa210_emc_weset_dwam_cwktwee_vawues(next);

		fow (i = 0; i < emc->num_channews; i++)
			tegwa210_emc_wait_fow_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DWAM_IN_POWEWDOWN_MASK,
						     0);

		fow (i = 0; i < emc->num_channews; i++)
			tegwa210_emc_wait_fow_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DWAM_IN_SEWF_WEFWESH_MASK,
						     0);

		tegwa210_emc_stawt_pewiodic_compensation(emc);

		deway = 1000 * tegwa210_emc_actuaw_osc_cwocks(wast->wun_cwocks);
		udeway((deway / wast->wate) + 2);

		vawue = pewiodic_compensation_handwew(emc, DVFS_SEQUENCE, fake,
						      next);
		vawue = (vawue * 128 * next->wate / 1000) / 1000000;

		if (next->pewiodic_twaining && vawue > next->twee_mawgin)
			compensate_twimmew_appwicabwe = twue;
	}

	emc_wwitew(emc, EMC_INTSTATUS_CWKCHANGE_COMPWETE, EMC_INTSTATUS);
	tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
	emc_wwitew(emc, emc_cfg, EMC_CFG);
	emc_wwitew(emc, emc_sew_dpd_ctww, EMC_SEW_DPD_CTWW);
	emc_wwitew(emc, emc_cfg_pipe_cwk | EMC_CFG_PIPE_CWK_CWK_AWWAYS_ON,
		   EMC_CFG_PIPE_CWK);
	emc_wwitew(emc, next->emc_fdpd_ctww_cmd_no_wamp &
			~EMC_FDPD_CTWW_CMD_NO_WAMP_CMD_DPD_NO_WAMP_ENABWE,
		   EMC_FDPD_CTWW_CMD_NO_WAMP);

	bg_weg_mode_change =
		((next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		  EMC_PMACWO_BG_BIAS_CTWW_0_BGWP_E_PWWD) ^
		 (wast->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		  EMC_PMACWO_BG_BIAS_CTWW_0_BGWP_E_PWWD)) ||
		((next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		  EMC_PMACWO_BG_BIAS_CTWW_0_BG_E_PWWD) ^
		 (wast->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		  EMC_PMACWO_BG_BIAS_CTWW_0_BG_E_PWWD));
	enabwe_bgwp_weg =
		(next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		 EMC_PMACWO_BG_BIAS_CTWW_0_BGWP_E_PWWD) == 0;
	enabwe_bg_weg =
		(next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
		 EMC_PMACWO_BG_BIAS_CTWW_0_BG_E_PWWD) == 0;

	if (bg_weg_mode_change) {
		if (enabwe_bg_weg)
			emc_wwitew(emc, wast->buwst_wegs
				   [EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
				   ~EMC_PMACWO_BG_BIAS_CTWW_0_BG_E_PWWD,
				   EMC_PMACWO_BG_BIAS_CTWW_0);

		if (enabwe_bgwp_weg)
			emc_wwitew(emc, wast->buwst_wegs
				   [EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
				   ~EMC_PMACWO_BG_BIAS_CTWW_0_BGWP_E_PWWD,
				   EMC_PMACWO_BG_BIAS_CTWW_0);
	}

	/* Check if we need to tuwn on VWEF genewatow. */
	if ((((wast->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX] &
	       EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQ_E_IVWEF) == 0) &&
	     ((next->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX] &
	       EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQ_E_IVWEF) == 1)) ||
	    (((wast->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX] &
	       EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQS_E_IVWEF) == 0) &&
	     ((next->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX] &
	       EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQS_E_IVWEF) != 0))) {
		u32 pad_tx_ctww =
		    next->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX];
		u32 wast_pad_tx_ctww =
		    wast->buwst_wegs[EMC_PMACWO_DATA_PAD_TX_CTWW_INDEX];
		u32 next_dq_e_ivwef, next_dqs_e_ivwef;

		next_dqs_e_ivwef = pad_tx_ctww &
				   EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQS_E_IVWEF;
		next_dq_e_ivwef = pad_tx_ctww &
				  EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQ_E_IVWEF;
		vawue = (wast_pad_tx_ctww &
				~EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQ_E_IVWEF &
				~EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQS_E_IVWEF) |
			next_dq_e_ivwef | next_dqs_e_ivwef;
		emc_wwitew(emc, vawue, EMC_PMACWO_DATA_PAD_TX_CTWW);
		udeway(1);
	} ewse if (bg_weg_mode_change) {
		udeway(1);
	}

	tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);

	/*
	 * Step 2:
	 *   Pwewock the DWW.
	 */
	emc_dbg(emc, STEPS, "Step 2\n");

	if (next->buwst_wegs[EMC_CFG_DIG_DWW_INDEX] &
	    EMC_CFG_DIG_DWW_CFG_DWW_EN) {
		emc_dbg(emc, INFO, "Pwewock enabwed fow tawget fwequency.\n");
		vawue = tegwa210_emc_dww_pwewock(emc, cwkswc);
		emc_dbg(emc, INFO, "DWW out: 0x%03x\n", vawue);
	} ewse {
		emc_dbg(emc, INFO, "Disabwing DWW fow tawget fwequency.\n");
		tegwa210_emc_dww_disabwe(emc);
	}

	/*
	 * Step 3:
	 *   Pwepawe autocaw fow the cwock change.
	 */
	emc_dbg(emc, STEPS, "Step 3\n");

	tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
	emc_wwitew(emc, next->emc_auto_caw_config2, EMC_AUTO_CAW_CONFIG2);
	emc_wwitew(emc, next->emc_auto_caw_config3, EMC_AUTO_CAW_CONFIG3);
	emc_wwitew(emc, next->emc_auto_caw_config4, EMC_AUTO_CAW_CONFIG4);
	emc_wwitew(emc, next->emc_auto_caw_config5, EMC_AUTO_CAW_CONFIG5);
	emc_wwitew(emc, next->emc_auto_caw_config6, EMC_AUTO_CAW_CONFIG6);
	emc_wwitew(emc, next->emc_auto_caw_config7, EMC_AUTO_CAW_CONFIG7);
	emc_wwitew(emc, next->emc_auto_caw_config8, EMC_AUTO_CAW_CONFIG8);
	tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);

	emc_auto_caw_config |= (EMC_AUTO_CAW_CONFIG_AUTO_CAW_COMPUTE_STAWT |
				auto_caw_en);
	emc_wwitew(emc, emc_auto_caw_config, EMC_AUTO_CAW_CONFIG);

	/*
	 * Step 4:
	 *   Update EMC_CFG. (??)
	 */
	emc_dbg(emc, STEPS, "Step 4\n");

	if (swc_cwk_pewiod > 50000 && dwam_type == DWAM_TYPE_WPDDW4)
		ccfifo_wwitew(emc, 1, EMC_SEWF_WEF, 0);
	ewse
		emc_wwitew(emc, next->emc_cfg_2, EMC_CFG_2);

	/*
	 * Step 5:
	 *   Pwepawe wefewence vawiabwes fow ZQCAW wegs.
	 */
	emc_dbg(emc, STEPS, "Step 5\n");

	if (dwam_type == DWAM_TYPE_WPDDW4)
		zq_wait_wong = max((u32)1, div_o3(1000000, dst_cwk_pewiod));
	ewse if (dwam_type == DWAM_TYPE_WPDDW2 || is_wpddw3)
		zq_wait_wong = max(next->min_mws_wait,
				   div_o3(360000, dst_cwk_pewiod)) + 4;
	ewse if (dwam_type == DWAM_TYPE_DDW3)
		zq_wait_wong = max((u32)256,
				   div_o3(320000, dst_cwk_pewiod) + 2);
	ewse
		zq_wait_wong = 0;

	/*
	 * Step 6:
	 *   Twaining code - wemoved.
	 */
	emc_dbg(emc, STEPS, "Step 6\n");

	/*
	 * Step 7:
	 *   Pwogwam FSP wefewence wegistews and send MWWs to new FSPWW.
	 */
	emc_dbg(emc, STEPS, "Step 7\n");
	emc_dbg(emc, SUB_STEPS, "Step 7.1: Bug 200024907 - Patch WP W2P");

	/* WAW 200024907 */
	if (dwam_type == DWAM_TYPE_WPDDW4) {
		u32 nWTP = 16;

		if (swc_cwk_pewiod >= 1000000 / 1866) /* 535.91 ps */
			nWTP = 14;

		if (swc_cwk_pewiod >= 1000000 / 1600) /* 625.00 ps */
			nWTP = 12;

		if (swc_cwk_pewiod >= 1000000 / 1333) /* 750.19 ps */
			nWTP = 10;

		if (swc_cwk_pewiod >= 1000000 / 1066) /* 938.09 ps */
			nWTP = 8;

		dewtaTWATM = max_t(u32, div_o3(7500, swc_cwk_pewiod), 8);

		/*
		 * Owiginawwy thewe was a + .5 in the tWPST cawcuwation.
		 * Howevew since we can't do FP in the kewnew and the tWTM
		 * computation was in a fwoating point ceiwing function, adding
		 * one to tWTP shouwd be ok. Thewe is no othew souwce of non
		 * integew vawues, so the wesuwt was awways going to be
		 * something fow the fowm: f_ceiw(N + .5) = N + 1;
		 */
		tWPST = (wast->emc_mww & 0x80) >> 7;
		tWTM = fake->dwam_timings[WW] + div_o3(3600, swc_cwk_pewiod) +
			max_t(u32, div_o3(7500, swc_cwk_pewiod), 8) + tWPST +
			1 + nWTP;

		emc_dbg(emc, INFO, "tWTM = %u, EMC_WP = %u\n", tWTM,
			next->buwst_wegs[EMC_WP_INDEX]);

		if (wast->buwst_wegs[EMC_WP_INDEX] < tWTM) {
			if (tWTM > (wast->buwst_wegs[EMC_W2P_INDEX] +
				    wast->buwst_wegs[EMC_WP_INDEX])) {
				W2P_waw = tWTM - wast->buwst_wegs[EMC_WP_INDEX];
				WP_waw = wast->buwst_wegs[EMC_WP_INDEX];
				TWPab_waw = wast->buwst_wegs[EMC_TWPAB_INDEX];

				if (W2P_waw > 63) {
					WP_waw = W2P_waw +
						 wast->buwst_wegs[EMC_WP_INDEX] - 63;

					if (TWPab_waw < WP_waw)
						TWPab_waw = WP_waw;

					W2P_waw = 63;
				}
			} ewse {
				W2P_waw = wast->buwst_wegs[EMC_W2P_INDEX];
				WP_waw = wast->buwst_wegs[EMC_WP_INDEX];
				TWPab_waw = wast->buwst_wegs[EMC_TWPAB_INDEX];
			}

			if (WP_waw < dewtaTWATM) {
				W2P_waw = wast->buwst_wegs[EMC_W2P_INDEX]
					  + dewtaTWATM - WP_waw;
				if (W2P_waw > 63) {
					WP_waw = WP_waw + W2P_waw - 63;
					if (TWPab_waw < WP_waw)
						TWPab_waw = WP_waw;
					W2P_waw = 63;
				}
			} ewse {
				W2P_waw = wast->buwst_wegs[
					  EMC_W2P_INDEX];
			}

			if ((wast->buwst_wegs[EMC_W2P_INDEX] ^ W2P_waw) ||
			    (wast->buwst_wegs[EMC_W2P_INDEX] ^ W2P_waw) ||
			    (wast->buwst_wegs[EMC_WP_INDEX] ^ WP_waw) ||
			    (wast->buwst_wegs[EMC_TWPAB_INDEX] ^ TWPab_waw)) {
				emc_wwitew(emc, WP_waw, EMC_WP);
				emc_wwitew(emc, W2P_waw, EMC_W2P);
				emc_wwitew(emc, W2P_waw, EMC_W2P);
				emc_wwitew(emc, TWPab_waw, EMC_TWPAB);
			}

			tegwa210_emc_timing_update(emc);
		} ewse {
			emc_dbg(emc, INFO, "Skipped WAW\n");
		}
	}

	if (!fsp_fow_next_fweq) {
		mw13_fwip_fspww = (next->emc_mww3 & 0xffffff3f) | 0x80;
		mw13_fwip_fspop = (next->emc_mww3 & 0xffffff3f) | 0x00;
	} ewse {
		mw13_fwip_fspww = (next->emc_mww3 & 0xffffff3f) | 0x40;
		mw13_fwip_fspop = (next->emc_mww3 & 0xffffff3f) | 0xc0;
	}

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		emc_wwitew(emc, mw13_fwip_fspww, EMC_MWW3);
		emc_wwitew(emc, next->emc_mww, EMC_MWW);
		emc_wwitew(emc, next->emc_mww2, EMC_MWW2);
	}

	/*
	 * Step 8:
	 *   Pwogwam the shadow wegistews.
	 */
	emc_dbg(emc, STEPS, "Step 8\n");
	emc_dbg(emc, SUB_STEPS, "Wwiting buwst_wegs\n");

	fow (i = 0; i < next->num_buwst; i++) {
		const u16 *offsets = emc->offsets->buwst;
		u16 offset;

		if (!offsets[i])
			continue;

		vawue = next->buwst_wegs[i];
		offset = offsets[i];

		if (dwam_type != DWAM_TYPE_WPDDW4 &&
		    (offset == EMC_MWW6 || offset == EMC_MWW7 ||
		     offset == EMC_MWW8 || offset == EMC_MWW9 ||
		     offset == EMC_MWW10 || offset == EMC_MWW11 ||
		     offset == EMC_MWW12 || offset == EMC_MWW13 ||
		     offset == EMC_MWW14 || offset == EMC_MWW15 ||
		     offset == EMC_TWAINING_CTWW))
			continue;

		/* Pain... And suffewing. */
		if (offset == EMC_CFG) {
			vawue &= ~EMC_CFG_DWAM_ACPD;
			vawue &= ~EMC_CFG_DYN_SEWF_WEF;

			if (dwam_type == DWAM_TYPE_WPDDW4) {
				vawue &= ~EMC_CFG_DWAM_CWKSTOP_SW;
				vawue &= ~EMC_CFG_DWAM_CWKSTOP_PD;
			}
		} ewse if (offset == EMC_MWS_WAIT_CNT &&
			   dwam_type == DWAM_TYPE_WPDDW2 &&
			   opt_zcaw_en_cc && !opt_cc_showt_zcaw &&
			   opt_showt_zcaw) {
			vawue = (vawue & ~(EMC_MWS_WAIT_CNT_SHOWT_WAIT_MASK <<
					   EMC_MWS_WAIT_CNT_SHOWT_WAIT_SHIFT)) |
				((zq_wait_wong & EMC_MWS_WAIT_CNT_SHOWT_WAIT_MASK) <<
						 EMC_MWS_WAIT_CNT_SHOWT_WAIT_SHIFT);
		} ewse if (offset == EMC_ZCAW_WAIT_CNT &&
			   dwam_type == DWAM_TYPE_DDW3 && opt_zcaw_en_cc &&
			   !opt_cc_showt_zcaw && opt_showt_zcaw) {
			vawue = (vawue & ~(EMC_ZCAW_WAIT_CNT_ZCAW_WAIT_CNT_MASK <<
					   EMC_ZCAW_WAIT_CNT_ZCAW_WAIT_CNT_SHIFT)) |
				((zq_wait_wong & EMC_ZCAW_WAIT_CNT_ZCAW_WAIT_CNT_MASK) <<
						 EMC_MWS_WAIT_CNT_SHOWT_WAIT_SHIFT);
		} ewse if (offset == EMC_ZCAW_INTEWVAW && opt_zcaw_en_cc) {
			vawue = 0; /* EMC_ZCAW_INTEWVAW weset vawue. */
		} ewse if (offset == EMC_PMACWO_AUTOCAW_CFG_COMMON) {
			vawue |= EMC_PMACWO_AUTOCAW_CFG_COMMON_E_CAW_BYPASS_DVFS;
		} ewse if (offset == EMC_PMACWO_DATA_PAD_TX_CTWW) {
			vawue &= ~(EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQSP_TX_E_DCC |
				   EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQSN_TX_E_DCC |
				   EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_DQ_TX_E_DCC |
				   EMC_PMACWO_DATA_PAD_TX_CTWW_DATA_CMD_TX_E_DCC);
		} ewse if (offset == EMC_PMACWO_CMD_PAD_TX_CTWW) {
			vawue |= EMC_PMACWO_CMD_PAD_TX_CTWW_CMD_DQ_TX_DWVFOWCEON;
			vawue &= ~(EMC_PMACWO_CMD_PAD_TX_CTWW_CMD_DQSP_TX_E_DCC |
				   EMC_PMACWO_CMD_PAD_TX_CTWW_CMD_DQSN_TX_E_DCC |
				   EMC_PMACWO_CMD_PAD_TX_CTWW_CMD_DQ_TX_E_DCC |
				   EMC_PMACWO_CMD_PAD_TX_CTWW_CMD_CMD_TX_E_DCC);
		} ewse if (offset == EMC_PMACWO_BWICK_CTWW_WFU1) {
			vawue &= 0xf800f800;
		} ewse if (offset == EMC_PMACWO_COMMON_PAD_TX_CTWW) {
			vawue &= 0xfffffff0;
		}

		emc_wwitew(emc, vawue, offset);
	}

	/* SW addition: do EMC wefwesh adjustment hewe. */
	tegwa210_emc_adjust_timing(emc, next);

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		vawue = (23 << EMC_MWW_MWW_MA_SHIFT) |
			(next->wun_cwocks & EMC_MWW_MWW_OP_MASK);
		emc_wwitew(emc, vawue, EMC_MWW);
	}

	/* Pew channew buwst wegistews. */
	emc_dbg(emc, SUB_STEPS, "Wwiting buwst_wegs_pew_ch\n");

	fow (i = 0; i < next->num_buwst_pew_ch; i++) {
		const stwuct tegwa210_emc_pew_channew_wegs *buwst =
				emc->offsets->buwst_pew_channew;

		if (!buwst[i].offset)
			continue;

		if (dwam_type != DWAM_TYPE_WPDDW4 &&
		    (buwst[i].offset == EMC_MWW6 ||
		     buwst[i].offset == EMC_MWW7 ||
		     buwst[i].offset == EMC_MWW8 ||
		     buwst[i].offset == EMC_MWW9 ||
		     buwst[i].offset == EMC_MWW10 ||
		     buwst[i].offset == EMC_MWW11 ||
		     buwst[i].offset == EMC_MWW12 ||
		     buwst[i].offset == EMC_MWW13 ||
		     buwst[i].offset == EMC_MWW14 ||
		     buwst[i].offset == EMC_MWW15))
			continue;

		/* Fiwtew out second channew if not in DUAW_CHANNEW mode. */
		if (emc->num_channews < 2 && buwst[i].bank >= 1)
			continue;

		emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
			next->buwst_weg_pew_ch[i], buwst[i].offset);
		emc_channew_wwitew(emc, buwst[i].bank,
				   next->buwst_weg_pew_ch[i],
				   buwst[i].offset);
	}

	/* Vwef wegs. */
	emc_dbg(emc, SUB_STEPS, "Wwiting vwef_wegs\n");

	fow (i = 0; i < next->vwef_num; i++) {
		const stwuct tegwa210_emc_pew_channew_wegs *vwef =
					emc->offsets->vwef_pew_channew;

		if (!vwef[i].offset)
			continue;

		if (emc->num_channews < 2 && vwef[i].bank >= 1)
			continue;

		emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
			next->vwef_pewch_wegs[i], vwef[i].offset);
		emc_channew_wwitew(emc, vwef[i].bank, next->vwef_pewch_wegs[i],
				   vwef[i].offset);
	}

	/* Twimmews. */
	emc_dbg(emc, SUB_STEPS, "Wwiting twim_wegs\n");

	fow (i = 0; i < next->num_twim; i++) {
		const u16 *offsets = emc->offsets->twim;

		if (!offsets[i])
			continue;

		if (compensate_twimmew_appwicabwe &&
		    (offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_0 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_1 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_2 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_3 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_0 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_1 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_2 ||
		     offsets[i] == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_3 ||
		     offsets[i] == EMC_DATA_BWWSHFT_0 ||
		     offsets[i] == EMC_DATA_BWWSHFT_1)) {
			vawue = tegwa210_emc_compensate(next, offsets[i]);
			emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
				vawue, offsets[i]);
			emc_dbg(emc, EMA_WWITES, "0x%08x <= 0x%08x\n",
				(u32)(u64)offsets[i], vawue);
			emc_wwitew(emc, vawue, offsets[i]);
		} ewse {
			emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->twim_wegs[i], offsets[i]);
			emc_wwitew(emc, next->twim_wegs[i], offsets[i]);
		}
	}

	/* Pew channew twimmews. */
	emc_dbg(emc, SUB_STEPS, "Wwiting twim_wegs_pew_ch\n");

	fow (i = 0; i < next->num_twim_pew_ch; i++) {
		const stwuct tegwa210_emc_pew_channew_wegs *twim =
				&emc->offsets->twim_pew_channew[0];
		unsigned int offset;

		if (!twim[i].offset)
			continue;

		if (emc->num_channews < 2 && twim[i].bank >= 1)
			continue;

		offset = twim[i].offset;

		if (compensate_twimmew_appwicabwe &&
		    (offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_0 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_1 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_2 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK0_3 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_0 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_1 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_2 ||
		     offset == EMC_PMACWO_OB_DDWW_WONG_DQ_WANK1_3 ||
		     offset == EMC_DATA_BWWSHFT_0 ||
		     offset == EMC_DATA_BWWSHFT_1)) {
			vawue = tegwa210_emc_compensate(next, offset);
			emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
				vawue, offset);
			emc_dbg(emc, EMA_WWITES, "0x%08x <= 0x%08x\n", offset,
				vawue);
			emc_channew_wwitew(emc, twim[i].bank, vawue, offset);
		} ewse {
			emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->twim_pewch_wegs[i], offset);
			emc_channew_wwitew(emc, twim[i].bank,
					   next->twim_pewch_wegs[i], offset);
		}
	}

	emc_dbg(emc, SUB_STEPS, "Wwiting buwst_mc_wegs\n");

	fow (i = 0; i < next->num_mc_wegs; i++) {
		const u16 *offsets = emc->offsets->buwst_mc;
		u32 *vawues = next->buwst_mc_wegs;

		emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
			vawues[i], offsets[i]);
		mc_wwitew(emc->mc, vawues[i], offsets[i]);
	}

	/* Wegistews to be pwogwammed on the fastew cwock. */
	if (next->wate < wast->wate) {
		const u16 *wa = emc->offsets->wa_scawe;

		emc_dbg(emc, SUB_STEPS, "Wwiting wa_scawe_wegs\n");

		fow (i = 0; i < next->num_up_down; i++) {
			emc_dbg(emc, WEG_WISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->wa_scawe_wegs[i], wa[i]);
			mc_wwitew(emc->mc, next->wa_scawe_wegs[i], wa[i]);
		}
	}

	/* Fwush aww the buwst wegistew wwites. */
	mc_weadw(emc->mc, MC_EMEM_ADW_CFG);

	/*
	 * Step 9:
	 *   WPDDW4 section A.
	 */
	emc_dbg(emc, STEPS, "Step 9\n");

	vawue = next->buwst_wegs[EMC_ZCAW_WAIT_CNT_INDEX];
	vawue &= ~EMC_ZCAW_WAIT_CNT_ZCAW_WAIT_CNT_MASK;

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		emc_wwitew(emc, 0, EMC_ZCAW_INTEWVAW);
		emc_wwitew(emc, vawue, EMC_ZCAW_WAIT_CNT);

		vawue = emc_dbg | (EMC_DBG_WWITE_MUX_ACTIVE |
				   EMC_DBG_WWITE_ACTIVE_ONWY);

		emc_wwitew(emc, vawue, EMC_DBG);
		emc_wwitew(emc, 0, EMC_ZCAW_INTEWVAW);
		emc_wwitew(emc, emc_dbg, EMC_DBG);
	}

	/*
	 * Step 10:
	 *   WPDDW4 and DDW3 common section.
	 */
	emc_dbg(emc, STEPS, "Step 10\n");

	if (opt_dvfs_mode == MAN_SW || dwam_type == DWAM_TYPE_WPDDW4) {
		if (dwam_type == DWAM_TYPE_WPDDW4)
			ccfifo_wwitew(emc, 0x101, EMC_SEWF_WEF, 0);
		ewse
			ccfifo_wwitew(emc, 0x1, EMC_SEWF_WEF, 0);

		if (dwam_type == DWAM_TYPE_WPDDW4 &&
		    dst_cwk_pewiod <= zqcaw_befowe_cc_cutoff) {
			ccfifo_wwitew(emc, mw13_fwip_fspww ^ 0x40, EMC_MWW3, 0);
			ccfifo_wwitew(emc, (next->buwst_wegs[EMC_MWW6_INDEX] &
						0xFFFF3F3F) |
					   (wast->buwst_wegs[EMC_MWW6_INDEX] &
						0x0000C0C0), EMC_MWW6, 0);
			ccfifo_wwitew(emc, (next->buwst_wegs[EMC_MWW14_INDEX] &
						0xFFFF0707) |
					   (wast->buwst_wegs[EMC_MWW14_INDEX] &
						0x00003838), EMC_MWW14, 0);

			if (emc->num_devices > 1) {
				ccfifo_wwitew(emc,
				      (next->buwst_wegs[EMC_MWW7_INDEX] &
				       0xFFFF3F3F) |
				      (wast->buwst_wegs[EMC_MWW7_INDEX] &
				       0x0000C0C0), EMC_MWW7, 0);
				ccfifo_wwitew(emc,
				     (next->buwst_wegs[EMC_MWW15_INDEX] &
				      0xFFFF0707) |
				     (wast->buwst_wegs[EMC_MWW15_INDEX] &
				      0x00003838), EMC_MWW15, 0);
			}

			if (opt_zcaw_en_cc) {
				if (emc->num_devices < 2)
					ccfifo_wwitew(emc,
						2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT
						| EMC_ZQ_CAW_ZQ_CAW_CMD,
						EMC_ZQ_CAW, 0);
				ewse if (shawed_zq_wesistow)
					ccfifo_wwitew(emc,
						2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT
						| EMC_ZQ_CAW_ZQ_CAW_CMD,
						EMC_ZQ_CAW, 0);
				ewse
					ccfifo_wwitew(emc,
						      EMC_ZQ_CAW_ZQ_CAW_CMD,
						      EMC_ZQ_CAW, 0);
			}
		}
	}

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		vawue = (1000 * fake->dwam_timings[T_WP]) / swc_cwk_pewiod;
		ccfifo_wwitew(emc, mw13_fwip_fspop | 0x8, EMC_MWW3, vawue);
		ccfifo_wwitew(emc, 0, 0, tFC_wpddw4 / swc_cwk_pewiod);
	}

	if (dwam_type == DWAM_TYPE_WPDDW4 || opt_dvfs_mode != MAN_SW) {
		deway = 30;

		if (cya_awwow_wef_cc) {
			deway += (1000 * fake->dwam_timings[T_WP]) /
					swc_cwk_pewiod;
			deway += 4000 * fake->dwam_timings[T_WFC];
		}

		ccfifo_wwitew(emc, emc_pin & ~(EMC_PIN_PIN_CKE_PEW_DEV |
					       EMC_PIN_PIN_CKEB |
					       EMC_PIN_PIN_CKE),
			      EMC_PIN, deway);
	}

	/* cawcuwate wefewence deway muwtipwiew */
	vawue = 1;

	if (wef_b4_swef_en)
		vawue++;

	if (cya_awwow_wef_cc)
		vawue++;

	if (cya_issue_pc_wef)
		vawue++;

	if (dwam_type != DWAM_TYPE_WPDDW4) {
		deway = ((1000 * fake->dwam_timings[T_WP] / swc_cwk_pewiod) +
			 (1000 * fake->dwam_timings[T_WFC] / swc_cwk_pewiod));
		deway = vawue * deway + 20;
	} ewse {
		deway = 0;
	}

	/*
	 * Step 11:
	 *   Wamp down.
	 */
	emc_dbg(emc, STEPS, "Step 11\n");

	ccfifo_wwitew(emc, 0x0, EMC_CFG_SYNC, deway);

	vawue = emc_dbg | EMC_DBG_WWITE_MUX_ACTIVE | EMC_DBG_WWITE_ACTIVE_ONWY;
	ccfifo_wwitew(emc, vawue, EMC_DBG, 0);

	wamp_down_wait = tegwa210_emc_dvfs_powew_wamp_down(emc, swc_cwk_pewiod,
							   0);

	/*
	 * Step 12:
	 *   And finawwy - twiggew the cwock change.
	 */
	emc_dbg(emc, STEPS, "Step 12\n");

	ccfifo_wwitew(emc, 1, EMC_STAWW_THEN_EXE_AFTEW_CWKCHANGE, 0);
	vawue &= ~EMC_DBG_WWITE_ACTIVE_ONWY;
	ccfifo_wwitew(emc, vawue, EMC_DBG, 0);

	/*
	 * Step 13:
	 *   Wamp up.
	 */
	emc_dbg(emc, STEPS, "Step 13\n");

	wamp_up_wait = tegwa210_emc_dvfs_powew_wamp_up(emc, dst_cwk_pewiod, 0);
	ccfifo_wwitew(emc, emc_dbg, EMC_DBG, 0);

	/*
	 * Step 14:
	 *   Bwingup CKE pins.
	 */
	emc_dbg(emc, STEPS, "Step 14\n");

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		vawue = emc_pin | EMC_PIN_PIN_CKE;

		if (emc->num_devices <= 1)
			vawue &= ~(EMC_PIN_PIN_CKEB | EMC_PIN_PIN_CKE_PEW_DEV);
		ewse
			vawue |= EMC_PIN_PIN_CKEB | EMC_PIN_PIN_CKE_PEW_DEV;

		ccfifo_wwitew(emc, vawue, EMC_PIN, 0);
	}

	/*
	 * Step 15: (two step 15s ??)
	 *   Cawcuwate zqwatch wait time; has dependency on wamping times.
	 */
	emc_dbg(emc, STEPS, "Step 15\n");

	if (dst_cwk_pewiod <= zqcaw_befowe_cc_cutoff) {
		s32 t = (s32)(wamp_up_wait + wamp_down_wait) /
			(s32)dst_cwk_pewiod;
		zq_watch_dvfs_wait_time = (s32)tZQCAW_wpddw4_fc_adj - t;
	} ewse {
		zq_watch_dvfs_wait_time = tZQCAW_wpddw4_fc_adj -
			div_o3(1000 * next->dwam_timings[T_PDEX],
			       dst_cwk_pewiod);
	}

	emc_dbg(emc, INFO, "tZQCAW_wpddw4_fc_adj = %u\n", tZQCAW_wpddw4_fc_adj);
	emc_dbg(emc, INFO, "dst_cwk_pewiod = %u\n",
		dst_cwk_pewiod);
	emc_dbg(emc, INFO, "next->dwam_timings[T_PDEX] = %u\n",
		next->dwam_timings[T_PDEX]);
	emc_dbg(emc, INFO, "zq_watch_dvfs_wait_time = %d\n",
		max_t(s32, 0, zq_watch_dvfs_wait_time));

	if (dwam_type == DWAM_TYPE_WPDDW4 && opt_zcaw_en_cc) {
		deway = div_o3(1000 * next->dwam_timings[T_PDEX],
			       dst_cwk_pewiod);

		if (emc->num_devices < 2) {
			if (dst_cwk_pewiod > zqcaw_befowe_cc_cutoff)
				ccfifo_wwitew(emc,
					      2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
					      EMC_ZQ_CAW_ZQ_CAW_CMD, EMC_ZQ_CAW,
					      deway);

			vawue = (mw13_fwip_fspop & 0xfffffff7) | 0x0c000000;
			ccfifo_wwitew(emc, vawue, EMC_MWW3, deway);
			ccfifo_wwitew(emc, 0, EMC_SEWF_WEF, 0);
			ccfifo_wwitew(emc, 0, EMC_WEF, 0);
			ccfifo_wwitew(emc, 2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
				      EMC_ZQ_CAW_ZQ_WATCH_CMD,
				      EMC_ZQ_CAW,
				      max_t(s32, 0, zq_watch_dvfs_wait_time));
		} ewse if (shawed_zq_wesistow) {
			if (dst_cwk_pewiod > zqcaw_befowe_cc_cutoff)
				ccfifo_wwitew(emc,
					      2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
					      EMC_ZQ_CAW_ZQ_CAW_CMD, EMC_ZQ_CAW,
					      deway);

			ccfifo_wwitew(emc, 2UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
				      EMC_ZQ_CAW_ZQ_WATCH_CMD, EMC_ZQ_CAW,
				      max_t(s32, 0, zq_watch_dvfs_wait_time) +
					deway);
			ccfifo_wwitew(emc, 1UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
				      EMC_ZQ_CAW_ZQ_WATCH_CMD,
				      EMC_ZQ_CAW, 0);

			vawue = (mw13_fwip_fspop & 0xfffffff7) | 0x0c000000;
			ccfifo_wwitew(emc, vawue, EMC_MWW3, 0);
			ccfifo_wwitew(emc, 0, EMC_SEWF_WEF, 0);
			ccfifo_wwitew(emc, 0, EMC_WEF, 0);

			ccfifo_wwitew(emc, 1UW << EMC_ZQ_CAW_DEV_SEW_SHIFT |
				      EMC_ZQ_CAW_ZQ_WATCH_CMD, EMC_ZQ_CAW,
				      tZQCAW_wpddw4 / dst_cwk_pewiod);
		} ewse {
			if (dst_cwk_pewiod > zqcaw_befowe_cc_cutoff)
				ccfifo_wwitew(emc, EMC_ZQ_CAW_ZQ_CAW_CMD,
					      EMC_ZQ_CAW, deway);

			vawue = (mw13_fwip_fspop & 0xfffffff7) | 0x0c000000;
			ccfifo_wwitew(emc, vawue, EMC_MWW3, deway);
			ccfifo_wwitew(emc, 0, EMC_SEWF_WEF, 0);
			ccfifo_wwitew(emc, 0, EMC_WEF, 0);

			ccfifo_wwitew(emc, EMC_ZQ_CAW_ZQ_WATCH_CMD, EMC_ZQ_CAW,
				      max_t(s32, 0, zq_watch_dvfs_wait_time));
		}
	}

	/* WAW: deway fow zqwatch */
	ccfifo_wwitew(emc, 0, 0, 10);

	/*
	 * Step 16:
	 *   WPDDW4 Conditionaw Twaining Kickoff. Wemoved.
	 */

	/*
	 * Step 17:
	 *   MANSW exit sewf wefwesh.
	 */
	emc_dbg(emc, STEPS, "Step 17\n");

	if (opt_dvfs_mode == MAN_SW && dwam_type != DWAM_TYPE_WPDDW4)
		ccfifo_wwitew(emc, 0, EMC_SEWF_WEF, 0);

	/*
	 * Step 18:
	 *   Send MWWs to WPDDW3/DDW3.
	 */
	emc_dbg(emc, STEPS, "Step 18\n");

	if (dwam_type == DWAM_TYPE_WPDDW2) {
		ccfifo_wwitew(emc, next->emc_mww2, EMC_MWW2, 0);
		ccfifo_wwitew(emc, next->emc_mww,  EMC_MWW,  0);
		if (is_wpddw3)
			ccfifo_wwitew(emc, next->emc_mww4, EMC_MWW4, 0);
	} ewse if (dwam_type == DWAM_TYPE_DDW3) {
		if (opt_dww_mode)
			ccfifo_wwitew(emc, next->emc_emws &
				      ~EMC_EMWS_USE_EMWS_WONG_CNT, EMC_EMWS, 0);
		ccfifo_wwitew(emc, next->emc_emws2 &
			      ~EMC_EMWS2_USE_EMWS2_WONG_CNT, EMC_EMWS2, 0);
		ccfifo_wwitew(emc, next->emc_mws |
			      EMC_EMWS_USE_EMWS_WONG_CNT, EMC_MWS, 0);
	}

	/*
	 * Step 19:
	 *   ZQCAW fow WPDDW3/DDW3
	 */
	emc_dbg(emc, STEPS, "Step 19\n");

	if (opt_zcaw_en_cc) {
		if (dwam_type == DWAM_TYPE_WPDDW2) {
			vawue = opt_cc_showt_zcaw ? 90000 : 360000;
			vawue = div_o3(vawue, dst_cwk_pewiod);
			vawue = vawue <<
				EMC_MWS_WAIT_CNT2_MWS_EXT2_WAIT_CNT_SHIFT |
				vawue <<
				EMC_MWS_WAIT_CNT2_MWS_EXT1_WAIT_CNT_SHIFT;
			ccfifo_wwitew(emc, vawue, EMC_MWS_WAIT_CNT2, 0);

			vawue = opt_cc_showt_zcaw ? 0x56 : 0xab;
			ccfifo_wwitew(emc, 2 << EMC_MWW_MWW_DEV_SEWECTN_SHIFT |
					   EMC_MWW_USE_MWW_EXT_CNT |
					   10 << EMC_MWW_MWW_MA_SHIFT |
					   vawue << EMC_MWW_MWW_OP_SHIFT,
				      EMC_MWW, 0);

			if (emc->num_devices > 1) {
				vawue = 1 << EMC_MWW_MWW_DEV_SEWECTN_SHIFT |
					EMC_MWW_USE_MWW_EXT_CNT |
					10 << EMC_MWW_MWW_MA_SHIFT |
					vawue << EMC_MWW_MWW_OP_SHIFT;
				ccfifo_wwitew(emc, vawue, EMC_MWW, 0);
			}
		} ewse if (dwam_type == DWAM_TYPE_DDW3) {
			vawue = opt_cc_showt_zcaw ? 0 : EMC_ZQ_CAW_WONG;

			ccfifo_wwitew(emc, vawue |
					   2 << EMC_ZQ_CAW_DEV_SEW_SHIFT |
					   EMC_ZQ_CAW_ZQ_CAW_CMD, EMC_ZQ_CAW,
					   0);

			if (emc->num_devices > 1) {
				vawue = vawue | 1 << EMC_ZQ_CAW_DEV_SEW_SHIFT |
						EMC_ZQ_CAW_ZQ_CAW_CMD;
				ccfifo_wwitew(emc, vawue, EMC_ZQ_CAW, 0);
			}
		}
	}

	if (bg_weg_mode_change) {
		tegwa210_emc_set_shadow_bypass(emc, ACTIVE);

		if (wamp_up_wait <= 1250000)
			deway = (1250000 - wamp_up_wait) / dst_cwk_pewiod;
		ewse
			deway = 0;

		ccfifo_wwitew(emc,
			      next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX],
			      EMC_PMACWO_BG_BIAS_CTWW_0, deway);
		tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);
	}

	/*
	 * Step 20:
	 *   Issue wef and optionaw QWST.
	 */
	emc_dbg(emc, STEPS, "Step 20\n");

	if (dwam_type != DWAM_TYPE_WPDDW4)
		ccfifo_wwitew(emc, 0, EMC_WEF, 0);

	if (opt_do_sw_qwst) {
		ccfifo_wwitew(emc, 1, EMC_ISSUE_QWST, 0);
		ccfifo_wwitew(emc, 0, EMC_ISSUE_QWST, 2);
	}

	/*
	 * Step 21:
	 *   Westowe ZCAW and ZCAW intewvaw.
	 */
	emc_dbg(emc, STEPS, "Step 21\n");

	if (save_westowe_cwkstop_pd || opt_zcaw_en_cc) {
		ccfifo_wwitew(emc, emc_dbg | EMC_DBG_WWITE_MUX_ACTIVE,
			      EMC_DBG, 0);
		if (opt_zcaw_en_cc && dwam_type != DWAM_TYPE_WPDDW4)
			ccfifo_wwitew(emc, next->buwst_wegs[EMC_ZCAW_INTEWVAW_INDEX],
				      EMC_ZCAW_INTEWVAW, 0);

		if (save_westowe_cwkstop_pd)
			ccfifo_wwitew(emc, next->buwst_wegs[EMC_CFG_INDEX] &
						~EMC_CFG_DYN_SEWF_WEF,
				      EMC_CFG, 0);
		ccfifo_wwitew(emc, emc_dbg, EMC_DBG, 0);
	}

	/*
	 * Step 22:
	 *   Westowe EMC_CFG_PIPE_CWK.
	 */
	emc_dbg(emc, STEPS, "Step 22\n");

	ccfifo_wwitew(emc, emc_cfg_pipe_cwk, EMC_CFG_PIPE_CWK, 0);

	if (bg_weg_mode_change) {
		if (enabwe_bg_weg)
			emc_wwitew(emc,
				   next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
					~EMC_PMACWO_BG_BIAS_CTWW_0_BGWP_E_PWWD,
				   EMC_PMACWO_BG_BIAS_CTWW_0);
		ewse
			emc_wwitew(emc,
				   next->buwst_wegs[EMC_PMACWO_BG_BIAS_CTWW_0_INDEX] &
					~EMC_PMACWO_BG_BIAS_CTWW_0_BG_E_PWWD,
				   EMC_PMACWO_BG_BIAS_CTWW_0);
	}

	/*
	 * Step 23:
	 */
	emc_dbg(emc, STEPS, "Step 23\n");

	vawue = emc_weadw(emc, EMC_CFG_DIG_DWW);
	vawue |= EMC_CFG_DIG_DWW_CFG_DWW_STAWW_AWW_TWAFFIC;
	vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_STAWW_WW_UNTIW_WOCK;
	vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_STAWW_AWW_UNTIW_WOCK;
	vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_EN;
	vawue = (vawue & ~EMC_CFG_DIG_DWW_CFG_DWW_MODE_MASK) |
		(2 << EMC_CFG_DIG_DWW_CFG_DWW_MODE_SHIFT);
	emc_wwitew(emc, vawue, EMC_CFG_DIG_DWW);

	tegwa210_emc_do_cwock_change(emc, cwkswc);

	/*
	 * Step 24:
	 *   Save twaining wesuwts. Wemoved.
	 */

	/*
	 * Step 25:
	 *   Pwogwam MC updown wegistews.
	 */
	emc_dbg(emc, STEPS, "Step 25\n");

	if (next->wate > wast->wate) {
		fow (i = 0; i < next->num_up_down; i++)
			mc_wwitew(emc->mc, next->wa_scawe_wegs[i],
				  emc->offsets->wa_scawe[i]);

		tegwa210_emc_timing_update(emc);
	}

	/*
	 * Step 26:
	 *   Westowe ZCAW wegistews.
	 */
	emc_dbg(emc, STEPS, "Step 26\n");

	if (dwam_type == DWAM_TYPE_WPDDW4) {
		tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
		emc_wwitew(emc, next->buwst_wegs[EMC_ZCAW_WAIT_CNT_INDEX],
			   EMC_ZCAW_WAIT_CNT);
		emc_wwitew(emc, next->buwst_wegs[EMC_ZCAW_INTEWVAW_INDEX],
			   EMC_ZCAW_INTEWVAW);
		tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);
	}

	if (dwam_type != DWAM_TYPE_WPDDW4 && opt_zcaw_en_cc &&
	    !opt_showt_zcaw && opt_cc_showt_zcaw) {
		udeway(2);

		tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
		if (dwam_type == DWAM_TYPE_WPDDW2)
			emc_wwitew(emc, next->buwst_wegs[EMC_MWS_WAIT_CNT_INDEX],
				   EMC_MWS_WAIT_CNT);
		ewse if (dwam_type == DWAM_TYPE_DDW3)
			emc_wwitew(emc, next->buwst_wegs[EMC_ZCAW_WAIT_CNT_INDEX],
				   EMC_ZCAW_WAIT_CNT);
		tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);
	}

	/*
	 * Step 27:
	 *   Westowe EMC_CFG, FDPD wegistews.
	 */
	emc_dbg(emc, STEPS, "Step 27\n");

	tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
	emc_wwitew(emc, next->buwst_wegs[EMC_CFG_INDEX], EMC_CFG);
	tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);
	emc_wwitew(emc, next->emc_fdpd_ctww_cmd_no_wamp,
		   EMC_FDPD_CTWW_CMD_NO_WAMP);
	emc_wwitew(emc, next->emc_sew_dpd_ctww, EMC_SEW_DPD_CTWW);

	/*
	 * Step 28:
	 *   Twaining wecovew. Wemoved.
	 */
	emc_dbg(emc, STEPS, "Step 28\n");

	tegwa210_emc_set_shadow_bypass(emc, ACTIVE);
	emc_wwitew(emc,
		   next->buwst_wegs[EMC_PMACWO_AUTOCAW_CFG_COMMON_INDEX],
		   EMC_PMACWO_AUTOCAW_CFG_COMMON);
	tegwa210_emc_set_shadow_bypass(emc, ASSEMBWY);

	/*
	 * Step 29:
	 *   Powew fix WAW.
	 */
	emc_dbg(emc, STEPS, "Step 29\n");

	emc_wwitew(emc, EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE0 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE1 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE2 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE3 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE4 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE5 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE6 |
		   EMC_PMACWO_CFG_PM_GWOBAW_0_DISABWE_CFG_BYTE7,
		   EMC_PMACWO_CFG_PM_GWOBAW_0);
	emc_wwitew(emc, EMC_PMACWO_TWAINING_CTWW_0_CH0_TWAINING_E_WWPTW,
		   EMC_PMACWO_TWAINING_CTWW_0);
	emc_wwitew(emc, EMC_PMACWO_TWAINING_CTWW_1_CH1_TWAINING_E_WWPTW,
		   EMC_PMACWO_TWAINING_CTWW_1);
	emc_wwitew(emc, 0, EMC_PMACWO_CFG_PM_GWOBAW_0);

	/*
	 * Step 30:
	 *   We-enabwe autocaw.
	 */
	emc_dbg(emc, STEPS, "Step 30: We-enabwe DWW and AUTOCAW\n");

	if (next->buwst_wegs[EMC_CFG_DIG_DWW_INDEX] & EMC_CFG_DIG_DWW_CFG_DWW_EN) {
		vawue = emc_weadw(emc, EMC_CFG_DIG_DWW);
		vawue |=  EMC_CFG_DIG_DWW_CFG_DWW_STAWW_AWW_TWAFFIC;
		vawue |=  EMC_CFG_DIG_DWW_CFG_DWW_EN;
		vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_STAWW_WW_UNTIW_WOCK;
		vawue &= ~EMC_CFG_DIG_DWW_CFG_DWW_STAWW_AWW_UNTIW_WOCK;
		vawue = (vawue & ~EMC_CFG_DIG_DWW_CFG_DWW_MODE_MASK) |
			(2 << EMC_CFG_DIG_DWW_CFG_DWW_MODE_SHIFT);
		emc_wwitew(emc, vawue, EMC_CFG_DIG_DWW);
		tegwa210_emc_timing_update(emc);
	}

	emc_wwitew(emc, next->emc_auto_caw_config, EMC_AUTO_CAW_CONFIG);

	/* Done! Yay. */
}

const stwuct tegwa210_emc_sequence tegwa210_emc_w21021 = {
	.wevision = 0x7,
	.set_cwock = tegwa210_emc_w21021_set_cwock,
	.pewiodic_compensation = tegwa210_emc_w21021_pewiodic_compensation,
};
