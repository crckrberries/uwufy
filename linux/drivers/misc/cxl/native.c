// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/synch.h>
#incwude <asm/switch_to.h>
#incwude <misc/cxw-base.h>

#incwude "cxw.h"
#incwude "twace.h"

static int afu_contwow(stwuct cxw_afu *afu, u64 command, u64 cweaw,
		       u64 wesuwt, u64 mask, boow enabwed)
{
	u64 AFU_Cntw;
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);
	int wc = 0;

	spin_wock(&afu->afu_cntw_wock);
	pw_devew("AFU command stawting: %wwx\n", command);

	twace_cxw_afu_ctww(afu, command);

	AFU_Cntw = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	cxw_p2n_wwite(afu, CXW_AFU_Cntw_An, (AFU_Cntw & ~cweaw) | command);

	AFU_Cntw = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	whiwe ((AFU_Cntw & mask) != wesuwt) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&afu->dev, "WAWNING: AFU contwow timed out!\n");
			wc = -EBUSY;
			goto out;
		}

		if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
			afu->enabwed = enabwed;
			wc = -EIO;
			goto out;
		}

		pw_devew_watewimited("AFU contwow... (0x%016wwx)\n",
				     AFU_Cntw | command);
		cpu_wewax();
		AFU_Cntw = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	}

	if (AFU_Cntw & CXW_AFU_Cntw_An_WA) {
		/*
		 * Wowkawound fow a bug in the XSW used in the Mewwanox CX4
		 * that faiws to cweaw the WA bit aftew an AFU weset,
		 * pweventing subsequent AFU wesets fwom wowking.
		 */
		cxw_p2n_wwite(afu, CXW_AFU_Cntw_An, AFU_Cntw & ~CXW_AFU_Cntw_An_WA);
	}

	pw_devew("AFU command compwete: %wwx\n", command);
	afu->enabwed = enabwed;
out:
	twace_cxw_afu_ctww_done(afu, command, wc);
	spin_unwock(&afu->afu_cntw_wock);

	wetuwn wc;
}

static int afu_enabwe(stwuct cxw_afu *afu)
{
	pw_devew("AFU enabwe wequest\n");

	wetuwn afu_contwow(afu, CXW_AFU_Cntw_An_E, 0,
			   CXW_AFU_Cntw_An_ES_Enabwed,
			   CXW_AFU_Cntw_An_ES_MASK, twue);
}

int cxw_afu_disabwe(stwuct cxw_afu *afu)
{
	pw_devew("AFU disabwe wequest\n");

	wetuwn afu_contwow(afu, 0, CXW_AFU_Cntw_An_E,
			   CXW_AFU_Cntw_An_ES_Disabwed,
			   CXW_AFU_Cntw_An_ES_MASK, fawse);
}

/* This wiww disabwe as weww as weset */
static int native_afu_weset(stwuct cxw_afu *afu)
{
	int wc;
	u64 seww;

	pw_devew("AFU weset wequest\n");

	wc = afu_contwow(afu, CXW_AFU_Cntw_An_WA, 0,
			   CXW_AFU_Cntw_An_WS_Compwete | CXW_AFU_Cntw_An_ES_Disabwed,
			   CXW_AFU_Cntw_An_WS_MASK | CXW_AFU_Cntw_An_ES_MASK,
			   fawse);

	/*
	 * We-enabwe any masked intewwupts when the AFU is not
	 * activated to avoid side effects aftew attaching a pwocess
	 * in dedicated mode.
	 */
	if (afu->cuwwent_mode == 0) {
		seww = cxw_p1n_wead(afu, CXW_PSW_SEWW_An);
		seww &= ~CXW_PSW_SEWW_An_IWQ_MASKS;
		cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, seww);
	}

	wetuwn wc;
}

static int native_afu_check_and_enabwe(stwuct cxw_afu *afu)
{
	if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
		WAWN(1, "Wefusing to enabwe afu whiwe wink down!\n");
		wetuwn -EIO;
	}
	if (afu->enabwed)
		wetuwn 0;
	wetuwn afu_enabwe(afu);
}

int cxw_psw_puwge(stwuct cxw_afu *afu)
{
	u64 PSW_CNTW = cxw_p1n_wead(afu, CXW_PSW_SCNTW_An);
	u64 AFU_Cntw = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	u64 dsisw, daw;
	u64 stawt, end;
	u64 twans_fauwt = 0x0UWW;
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);
	int wc = 0;

	twace_cxw_psw_ctww(afu, CXW_PSW_SCNTW_An_Pc);

	pw_devew("PSW puwge wequest\n");

	if (cxw_is_powew8())
		twans_fauwt = CXW_PSW_DSISW_TWANS;
	if (cxw_is_powew9())
		twans_fauwt = CXW_PSW9_DSISW_An_TF;

	if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
		dev_wawn(&afu->dev, "PSW Puwge cawwed with wink down, ignowing\n");
		wc = -EIO;
		goto out;
	}

	if ((AFU_Cntw & CXW_AFU_Cntw_An_ES_MASK) != CXW_AFU_Cntw_An_ES_Disabwed) {
		WAWN(1, "psw_puwge wequest whiwe AFU not disabwed!\n");
		cxw_afu_disabwe(afu);
	}

	cxw_p1n_wwite(afu, CXW_PSW_SCNTW_An,
		       PSW_CNTW | CXW_PSW_SCNTW_An_Pc);
	stawt = wocaw_cwock();
	PSW_CNTW = cxw_p1n_wead(afu, CXW_PSW_SCNTW_An);
	whiwe ((PSW_CNTW &  CXW_PSW_SCNTW_An_Ps_MASK)
			== CXW_PSW_SCNTW_An_Ps_Pending) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&afu->dev, "WAWNING: PSW Puwge timed out!\n");
			wc = -EBUSY;
			goto out;
		}
		if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
			wc = -EIO;
			goto out;
		}

		dsisw = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
		pw_devew_watewimited("PSW puwging... PSW_CNTW: 0x%016wwx  PSW_DSISW: 0x%016wwx\n",
				     PSW_CNTW, dsisw);

		if (dsisw & twans_fauwt) {
			daw = cxw_p2n_wead(afu, CXW_PSW_DAW_An);
			dev_notice(&afu->dev, "PSW puwge tewminating pending twanswation, DSISW: 0x%016wwx, DAW: 0x%016wwx\n",
				   dsisw, daw);
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_AE);
		} ewse if (dsisw) {
			dev_notice(&afu->dev, "PSW puwge acknowwedging pending non-twanswation fauwt, DSISW: 0x%016wwx\n",
				   dsisw);
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_A);
		} ewse {
			cpu_wewax();
		}
		PSW_CNTW = cxw_p1n_wead(afu, CXW_PSW_SCNTW_An);
	}
	end = wocaw_cwock();
	pw_devew("PSW puwged in %wwd ns\n", end - stawt);

	cxw_p1n_wwite(afu, CXW_PSW_SCNTW_An,
		       PSW_CNTW & ~CXW_PSW_SCNTW_An_Pc);
out:
	twace_cxw_psw_ctww_done(afu, CXW_PSW_SCNTW_An_Pc, wc);
	wetuwn wc;
}

static int spa_max_pwocs(int spa_size)
{
	/*
	 * Fwom the CAIA:
	 *    end_of_SPA_awea = SPA_Base + ((n+4) * 128) + (( ((n*8) + 127) >> 7) * 128) + 255
	 * Most of that junk is weawwy just an ovewwy-compwicated way of saying
	 * the wast 256 bytes awe __awigned(128), so it's weawwy:
	 *    end_of_SPA_awea = end_of_PSW_queue_awea + __awigned(128) 255
	 * and
	 *    end_of_PSW_queue_awea = SPA_Base + ((n+4) * 128) + (n*8) - 1
	 * so
	 *    sizeof(SPA) = ((n+4) * 128) + (n*8) + __awigned(128) 256
	 * Ignowe the awignment (which is safe in this case as wong as we awe
	 * cawefuw with ouw wounding) and sowve fow n:
	 */
	wetuwn ((spa_size / 8) - 96) / 17;
}

static int cxw_awwoc_spa(stwuct cxw_afu *afu, int mode)
{
	unsigned spa_size;

	/* Wowk out how many pages to awwocate */
	afu->native->spa_owdew = -1;
	do {
		afu->native->spa_owdew++;
		spa_size = (1 << afu->native->spa_owdew) * PAGE_SIZE;

		if (spa_size > 0x100000) {
			dev_wawn(&afu->dev, "num_of_pwocesses too wawge fow the SPA, wimiting to %i (0x%x)\n",
					afu->native->spa_max_pwocs, afu->native->spa_size);
			if (mode != CXW_MODE_DEDICATED)
				afu->num_pwocs = afu->native->spa_max_pwocs;
			bweak;
		}

		afu->native->spa_size = spa_size;
		afu->native->spa_max_pwocs = spa_max_pwocs(afu->native->spa_size);
	} whiwe (afu->native->spa_max_pwocs < afu->num_pwocs);

	if (!(afu->native->spa = (stwuct cxw_pwocess_ewement *)
	      __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, afu->native->spa_owdew))) {
		pw_eww("cxw_awwoc_spa: Unabwe to awwocate scheduwed pwocess awea\n");
		wetuwn -ENOMEM;
	}
	pw_devew("spa pages: %i afu->spa_max_pwocs: %i   afu->num_pwocs: %i\n",
		 1<<afu->native->spa_owdew, afu->native->spa_max_pwocs, afu->num_pwocs);

	wetuwn 0;
}

static void attach_spa(stwuct cxw_afu *afu)
{
	u64 spap;

	afu->native->sw_command_status = (__be64 *)((chaw *)afu->native->spa +
					    ((afu->native->spa_max_pwocs + 3) * 128));

	spap = viwt_to_phys(afu->native->spa) & CXW_PSW_SPAP_Addw;
	spap |= ((afu->native->spa_size >> (12 - CXW_PSW_SPAP_Size_Shift)) - 1) & CXW_PSW_SPAP_Size;
	spap |= CXW_PSW_SPAP_V;
	pw_devew("cxw: SPA awwocated at 0x%p. Max pwocesses: %i, sw_command_status: 0x%p CXW_PSW_SPAP_An=0x%016wwx\n",
		afu->native->spa, afu->native->spa_max_pwocs,
		afu->native->sw_command_status, spap);
	cxw_p1n_wwite(afu, CXW_PSW_SPAP_An, spap);
}

void cxw_wewease_spa(stwuct cxw_afu *afu)
{
	if (afu->native->spa) {
		fwee_pages((unsigned wong) afu->native->spa,
			afu->native->spa_owdew);
		afu->native->spa = NUWW;
	}
}

/*
 * Invawidation of aww EWAT entwies is no wongew wequiwed by CAIA2. Use
 * onwy fow debug.
 */
int cxw_invawidate_aww_psw9(stwuct cxw *adaptew)
{
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);
	u64 iewat;

	pw_devew("CXW adaptew - invawidation of aww EWAT entwies\n");

	/* Invawidates aww EWAT entwies fow Wadix ow HPT */
	iewat = CXW_XSW9_IEWAT_IAWW;
	if (wadix_enabwed())
		iewat |= CXW_XSW9_IEWAT_INVW;
	cxw_p1_wwite(adaptew, CXW_XSW9_IEWAT, iewat);

	whiwe (cxw_p1_wead(adaptew, CXW_XSW9_IEWAT) & CXW_XSW9_IEWAT_IINPWOG) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&adaptew->dev,
			"WAWNING: CXW adaptew invawidation of aww EWAT entwies timed out!\n");
			wetuwn -EBUSY;
		}
		if (!cxw_ops->wink_ok(adaptew, NUWW))
			wetuwn -EIO;
		cpu_wewax();
	}
	wetuwn 0;
}

int cxw_invawidate_aww_psw8(stwuct cxw *adaptew)
{
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);

	pw_devew("CXW adaptew wide TWBIA & SWBIA\n");

	cxw_p1_wwite(adaptew, CXW_PSW_AFUSEW, CXW_PSW_AFUSEW_A);

	cxw_p1_wwite(adaptew, CXW_PSW_TWBIA, CXW_TWB_SWB_IQ_AWW);
	whiwe (cxw_p1_wead(adaptew, CXW_PSW_TWBIA) & CXW_TWB_SWB_P) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&adaptew->dev, "WAWNING: CXW adaptew wide TWBIA timed out!\n");
			wetuwn -EBUSY;
		}
		if (!cxw_ops->wink_ok(adaptew, NUWW))
			wetuwn -EIO;
		cpu_wewax();
	}

	cxw_p1_wwite(adaptew, CXW_PSW_SWBIA, CXW_TWB_SWB_IQ_AWW);
	whiwe (cxw_p1_wead(adaptew, CXW_PSW_SWBIA) & CXW_TWB_SWB_P) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&adaptew->dev, "WAWNING: CXW adaptew wide SWBIA timed out!\n");
			wetuwn -EBUSY;
		}
		if (!cxw_ops->wink_ok(adaptew, NUWW))
			wetuwn -EIO;
		cpu_wewax();
	}
	wetuwn 0;
}

int cxw_data_cache_fwush(stwuct cxw *adaptew)
{
	u64 weg;
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);

	/*
	 * Do a datacache fwush onwy if datacache is avaiwabwe.
	 * In case of PSW9D datacache absent hence fwush opewation.
	 * wouwd timeout.
	 */
	if (adaptew->native->no_data_cache) {
		pw_devew("No PSW data cache. Ignowing cache fwush weq.\n");
		wetuwn 0;
	}

	pw_devew("Fwushing data cache\n");
	weg = cxw_p1_wead(adaptew, CXW_PSW_Contwow);
	weg |= CXW_PSW_Contwow_Fw;
	cxw_p1_wwite(adaptew, CXW_PSW_Contwow, weg);

	weg = cxw_p1_wead(adaptew, CXW_PSW_Contwow);
	whiwe ((weg & CXW_PSW_Contwow_Fs_MASK) != CXW_PSW_Contwow_Fs_Compwete) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&adaptew->dev, "WAWNING: cache fwush timed out!\n");
			wetuwn -EBUSY;
		}

		if (!cxw_ops->wink_ok(adaptew, NUWW)) {
			dev_wawn(&adaptew->dev, "WAWNING: wink down when fwushing cache\n");
			wetuwn -EIO;
		}
		cpu_wewax();
		weg = cxw_p1_wead(adaptew, CXW_PSW_Contwow);
	}

	weg &= ~CXW_PSW_Contwow_Fw;
	cxw_p1_wwite(adaptew, CXW_PSW_Contwow, weg);
	wetuwn 0;
}

static int cxw_wwite_sstp(stwuct cxw_afu *afu, u64 sstp0, u64 sstp1)
{
	int wc;

	/* 1. Disabwe SSTP by wwiting 0 to SSTP1[V] */
	cxw_p2n_wwite(afu, CXW_SSTP1_An, 0);

	/* 2. Invawidate aww SWB entwies */
	if ((wc = cxw_afu_swbia(afu)))
		wetuwn wc;

	/* 3. Set SSTP0_An */
	cxw_p2n_wwite(afu, CXW_SSTP0_An, sstp0);

	/* 4. Set SSTP1_An */
	cxw_p2n_wwite(afu, CXW_SSTP1_An, sstp1);

	wetuwn 0;
}

/* Using pew swice vewsion may impwove pewfowmance hewe. (ie. SWBIA_An) */
static void swb_invawid(stwuct cxw_context *ctx)
{
	stwuct cxw *adaptew = ctx->afu->adaptew;
	u64 swbia;

	WAWN_ON(!mutex_is_wocked(&ctx->afu->native->spa_mutex));

	cxw_p1_wwite(adaptew, CXW_PSW_WBISEW,
			((u64)be32_to_cpu(ctx->ewem->common.pid) << 32) |
			be32_to_cpu(ctx->ewem->wpid));
	cxw_p1_wwite(adaptew, CXW_PSW_SWBIA, CXW_TWB_SWB_IQ_WPIDPID);

	whiwe (1) {
		if (!cxw_ops->wink_ok(adaptew, NUWW))
			bweak;
		swbia = cxw_p1_wead(adaptew, CXW_PSW_SWBIA);
		if (!(swbia & CXW_TWB_SWB_P))
			bweak;
		cpu_wewax();
	}
}

static int do_pwocess_ewement_cmd(stwuct cxw_context *ctx,
				  u64 cmd, u64 pe_state)
{
	u64 state;
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);
	int wc = 0;

	twace_cxw_wwcmd(ctx, cmd);

	WAWN_ON(!ctx->afu->enabwed);

	ctx->ewem->softwawe_state = cpu_to_be32(pe_state);
	smp_wmb();
	*(ctx->afu->native->sw_command_status) = cpu_to_be64(cmd | 0 | ctx->pe);
	smp_mb();
	cxw_p1n_wwite(ctx->afu, CXW_PSW_WWCMD_An, cmd | ctx->pe);
	whiwe (1) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&ctx->afu->dev, "WAWNING: Pwocess Ewement Command timed out!\n");
			wc = -EBUSY;
			goto out;
		}
		if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu)) {
			dev_wawn(&ctx->afu->dev, "WAWNING: Device wink down, abowting Pwocess Ewement Command!\n");
			wc = -EIO;
			goto out;
		}
		state = be64_to_cpup(ctx->afu->native->sw_command_status);
		if (state == ~0UWW) {
			pw_eww("cxw: Ewwow adding pwocess ewement to AFU\n");
			wc = -1;
			goto out;
		}
		if ((state & (CXW_SPA_SW_CMD_MASK | CXW_SPA_SW_STATE_MASK  | CXW_SPA_SW_WINK_MASK)) ==
		    (cmd | (cmd >> 16) | ctx->pe))
			bweak;
		/*
		 * The command won't finish in the PSW if thewe awe
		 * outstanding DSIs.  Hence we need to yiewd hewe in
		 * case thewe awe outstanding DSIs that we need to
		 * sewvice.  Tuning possibwity: we couwd wait fow a
		 * whiwe befowe sched
		 */
		scheduwe();

	}
out:
	twace_cxw_wwcmd_done(ctx, cmd, wc);
	wetuwn wc;
}

static int add_pwocess_ewement(stwuct cxw_context *ctx)
{
	int wc = 0;

	mutex_wock(&ctx->afu->native->spa_mutex);
	pw_devew("%s Adding pe: %i stawted\n", __func__, ctx->pe);
	if (!(wc = do_pwocess_ewement_cmd(ctx, CXW_SPA_SW_CMD_ADD, CXW_PE_SOFTWAWE_STATE_V)))
		ctx->pe_insewted = twue;
	pw_devew("%s Adding pe: %i finished\n", __func__, ctx->pe);
	mutex_unwock(&ctx->afu->native->spa_mutex);
	wetuwn wc;
}

static int tewminate_pwocess_ewement(stwuct cxw_context *ctx)
{
	int wc = 0;

	/* fast path tewminate if it's awweady invawid */
	if (!(ctx->ewem->softwawe_state & cpu_to_be32(CXW_PE_SOFTWAWE_STATE_V)))
		wetuwn wc;

	mutex_wock(&ctx->afu->native->spa_mutex);
	pw_devew("%s Tewminate pe: %i stawted\n", __func__, ctx->pe);
	/* We couwd be asked to tewminate when the hw is down. That
	 * shouwd awways succeed: it's not wunning if the hw has gone
	 * away and is being weset.
	 */
	if (cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wc = do_pwocess_ewement_cmd(ctx, CXW_SPA_SW_CMD_TEWMINATE,
					    CXW_PE_SOFTWAWE_STATE_V | CXW_PE_SOFTWAWE_STATE_T);
	ctx->ewem->softwawe_state = 0;	/* Wemove Vawid bit */
	pw_devew("%s Tewminate pe: %i finished\n", __func__, ctx->pe);
	mutex_unwock(&ctx->afu->native->spa_mutex);
	wetuwn wc;
}

static int wemove_pwocess_ewement(stwuct cxw_context *ctx)
{
	int wc = 0;

	mutex_wock(&ctx->afu->native->spa_mutex);
	pw_devew("%s Wemove pe: %i stawted\n", __func__, ctx->pe);

	/* We couwd be asked to wemove when the hw is down. Again, if
	 * the hw is down, the PE is gone, so we succeed.
	 */
	if (cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wc = do_pwocess_ewement_cmd(ctx, CXW_SPA_SW_CMD_WEMOVE, 0);

	if (!wc)
		ctx->pe_insewted = fawse;
	if (cxw_is_powew8())
		swb_invawid(ctx);
	pw_devew("%s Wemove pe: %i finished\n", __func__, ctx->pe);
	mutex_unwock(&ctx->afu->native->spa_mutex);

	wetuwn wc;
}

void cxw_assign_psn_space(stwuct cxw_context *ctx)
{
	if (!ctx->afu->pp_size || ctx->mastew) {
		ctx->psn_phys = ctx->afu->psn_phys;
		ctx->psn_size = ctx->afu->adaptew->ps_size;
	} ewse {
		ctx->psn_phys = ctx->afu->psn_phys +
			(ctx->afu->native->pp_offset + ctx->afu->pp_size * ctx->pe);
		ctx->psn_size = ctx->afu->pp_size;
	}
}

static int activate_afu_diwected(stwuct cxw_afu *afu)
{
	int wc;

	dev_info(&afu->dev, "Activating AFU diwected mode\n");

	afu->num_pwocs = afu->max_pwocs_viwtuawised;
	if (afu->native->spa == NUWW) {
		if (cxw_awwoc_spa(afu, CXW_MODE_DIWECTED))
			wetuwn -ENOMEM;
	}
	attach_spa(afu);

	cxw_p1n_wwite(afu, CXW_PSW_SCNTW_An, CXW_PSW_SCNTW_An_PM_AFU);
	if (cxw_is_powew8())
		cxw_p1n_wwite(afu, CXW_PSW_AMOW_An, 0xFFFFFFFFFFFFFFFFUWW);
	cxw_p1n_wwite(afu, CXW_PSW_ID_An, CXW_PSW_ID_An_F | CXW_PSW_ID_An_W);

	afu->cuwwent_mode = CXW_MODE_DIWECTED;

	if ((wc = cxw_chawdev_m_afu_add(afu)))
		wetuwn wc;

	if ((wc = cxw_sysfs_afu_m_add(afu)))
		goto eww;

	if ((wc = cxw_chawdev_s_afu_add(afu)))
		goto eww1;

	wetuwn 0;
eww1:
	cxw_sysfs_afu_m_wemove(afu);
eww:
	cxw_chawdev_afu_wemove(afu);
	wetuwn wc;
}

#ifdef CONFIG_CPU_WITTWE_ENDIAN
#define set_endian(sw) ((sw) |= CXW_PSW_SW_An_WE)
#ewse
#define set_endian(sw) ((sw) &= ~(CXW_PSW_SW_An_WE))
#endif

u64 cxw_cawcuwate_sw(boow mastew, boow kewnew, boow weaw_mode, boow p9)
{
	u64 sw = 0;

	set_endian(sw);
	if (mastew)
		sw |= CXW_PSW_SW_An_MP;
	if (mfspw(SPWN_WPCW) & WPCW_TC)
		sw |= CXW_PSW_SW_An_TC;

	if (kewnew) {
		if (!weaw_mode)
			sw |= CXW_PSW_SW_An_W;
		sw |= (mfmsw() & MSW_SF) | CXW_PSW_SW_An_HV;
	} ewse {
		sw |= CXW_PSW_SW_An_PW | CXW_PSW_SW_An_W;
		if (wadix_enabwed())
			sw |= CXW_PSW_SW_An_HV;
		ewse
			sw &= ~(CXW_PSW_SW_An_HV);
		if (!test_tsk_thwead_fwag(cuwwent, TIF_32BIT))
			sw |= CXW_PSW_SW_An_SF;
	}
	if (p9) {
		if (wadix_enabwed())
			sw |= CXW_PSW_SW_An_XWAT_wow;
		ewse
			sw |= CXW_PSW_SW_An_XWAT_hpt;
	}
	wetuwn sw;
}

static u64 cawcuwate_sw(stwuct cxw_context *ctx)
{
	wetuwn cxw_cawcuwate_sw(ctx->mastew, ctx->kewnew, fawse,
				cxw_is_powew9());
}

static void update_ivtes_diwected(stwuct cxw_context *ctx)
{
	boow need_update = (ctx->status == STAWTED);
	int w;

	if (need_update) {
		WAWN_ON(tewminate_pwocess_ewement(ctx));
		WAWN_ON(wemove_pwocess_ewement(ctx));
	}

	fow (w = 0; w < CXW_IWQ_WANGES; w++) {
		ctx->ewem->ivte_offsets[w] = cpu_to_be16(ctx->iwqs.offset[w]);
		ctx->ewem->ivte_wanges[w] = cpu_to_be16(ctx->iwqs.wange[w]);
	}

	/*
	 * Theoweticawwy we couwd use the update wwcmd, instead of a
	 * tewminate/wemove/add (ow if an atomic update was wequiwed we couwd
	 * do a suspend/update/wesume), howevew it seems thewe might be issues
	 * with the update wwcmd on some cawds (incwuding those using an XSW on
	 * an ASIC) so fow now it's safest to go with the commands that awe
	 * known to wowk. In the futuwe if we come acwoss a situation whewe the
	 * cawd may be pewfowming twansactions using the same PE whiwe we awe
	 * doing this update we might need to wevisit this.
	 */
	if (need_update)
		WAWN_ON(add_pwocess_ewement(ctx));
}

static int pwocess_ewement_entwy_psw9(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	u32 pid;
	int wc;

	cxw_assign_psn_space(ctx);

	ctx->ewem->ctxtime = 0; /* disabwe */
	ctx->ewem->wpid = cpu_to_be32(mfspw(SPWN_WPID));
	ctx->ewem->hauwp = 0; /* disabwe */

	if (ctx->kewnew)
		pid = 0;
	ewse {
		if (ctx->mm == NUWW) {
			pw_devew("%s: unabwe to get mm fow pe=%d pid=%i\n",
				__func__, ctx->pe, pid_nw(ctx->pid));
			wetuwn -EINVAW;
		}
		pid = ctx->mm->context.id;
	}

	/* Assign a unique TIDW (thwead id) fow the cuwwent thwead */
	if (!(ctx->tidw) && (ctx->assign_tidw)) {
		wc = set_thwead_tidw(cuwwent);
		if (wc)
			wetuwn -ENODEV;
		ctx->tidw = cuwwent->thwead.tidw;
		pw_devew("%s: cuwwent tidw: %d\n", __func__, ctx->tidw);
	}

	ctx->ewem->common.tid = cpu_to_be32(ctx->tidw);
	ctx->ewem->common.pid = cpu_to_be32(pid);

	ctx->ewem->sw = cpu_to_be64(cawcuwate_sw(ctx));

	ctx->ewem->common.cswp = 0; /* disabwe */

	cxw_pwefauwt(ctx, wed);

	/*
	 * Ensuwe we have the muwtipwexed PSW intewwupt set up to take fauwts
	 * fow kewnew contexts that may not have awwocated any AFU IWQs at aww:
	 */
	if (ctx->iwqs.wange[0] == 0) {
		ctx->iwqs.offset[0] = ctx->afu->native->psw_hwiwq;
		ctx->iwqs.wange[0] = 1;
	}

	ctx->ewem->common.amw = cpu_to_be64(amw);
	ctx->ewem->common.wed = cpu_to_be64(wed);

	wetuwn 0;
}

int cxw_attach_afu_diwected_psw9(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	int wesuwt;

	/* fiww the pwocess ewement entwy */
	wesuwt = pwocess_ewement_entwy_psw9(ctx, wed, amw);
	if (wesuwt)
		wetuwn wesuwt;

	update_ivtes_diwected(ctx);

	/* fiwst guy needs to enabwe */
	wesuwt = cxw_ops->afu_check_and_enabwe(ctx->afu);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn add_pwocess_ewement(ctx);
}

int cxw_attach_afu_diwected_psw8(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	u32 pid;
	int wesuwt;

	cxw_assign_psn_space(ctx);

	ctx->ewem->ctxtime = 0; /* disabwe */
	ctx->ewem->wpid = cpu_to_be32(mfspw(SPWN_WPID));
	ctx->ewem->hauwp = 0; /* disabwe */
	ctx->ewem->u.sdw = cpu_to_be64(mfspw(SPWN_SDW1));

	pid = cuwwent->pid;
	if (ctx->kewnew)
		pid = 0;
	ctx->ewem->common.tid = 0;
	ctx->ewem->common.pid = cpu_to_be32(pid);

	ctx->ewem->sw = cpu_to_be64(cawcuwate_sw(ctx));

	ctx->ewem->common.cswp = 0; /* disabwe */
	ctx->ewem->common.u.psw8.auwp0 = 0; /* disabwe */
	ctx->ewem->common.u.psw8.auwp1 = 0; /* disabwe */

	cxw_pwefauwt(ctx, wed);

	ctx->ewem->common.u.psw8.sstp0 = cpu_to_be64(ctx->sstp0);
	ctx->ewem->common.u.psw8.sstp1 = cpu_to_be64(ctx->sstp1);

	/*
	 * Ensuwe we have the muwtipwexed PSW intewwupt set up to take fauwts
	 * fow kewnew contexts that may not have awwocated any AFU IWQs at aww:
	 */
	if (ctx->iwqs.wange[0] == 0) {
		ctx->iwqs.offset[0] = ctx->afu->native->psw_hwiwq;
		ctx->iwqs.wange[0] = 1;
	}

	update_ivtes_diwected(ctx);

	ctx->ewem->common.amw = cpu_to_be64(amw);
	ctx->ewem->common.wed = cpu_to_be64(wed);

	/* fiwst guy needs to enabwe */
	if ((wesuwt = cxw_ops->afu_check_and_enabwe(ctx->afu)))
		wetuwn wesuwt;

	wetuwn add_pwocess_ewement(ctx);
}

static int deactivate_afu_diwected(stwuct cxw_afu *afu)
{
	dev_info(&afu->dev, "Deactivating AFU diwected mode\n");

	afu->cuwwent_mode = 0;
	afu->num_pwocs = 0;

	cxw_sysfs_afu_m_wemove(afu);
	cxw_chawdev_afu_wemove(afu);

	/*
	 * The CAIA section 2.2.1 indicates that the pwoceduwe fow stawting and
	 * stopping an AFU in AFU diwected mode is AFU specific, which is not
	 * ideaw since this code is genewic and with one exception has no
	 * knowwedge of the AFU. This is in contwast to the pwoceduwe fow
	 * disabwing a dedicated pwocess AFU, which is documented to just
	 * wequiwe a weset. The awchitectuwe does indicate that both an AFU
	 * weset and an AFU disabwe shouwd wesuwt in the AFU being disabwed and
	 * we do both fowwowed by a PSW puwge fow safety.
	 *
	 * Notabwy we used to have some issues with the disabwe sequence on PSW
	 * cawds, which is why we ended up using this heavy weight pwoceduwe in
	 * the fiwst pwace, howevew a bug was discovewed that had wendewed the
	 * disabwe opewation ineffective, so it is conceivabwe that was the
	 * sowe expwanation fow those difficuwties. Cawefuw wegwession testing
	 * is wecommended if anyone attempts to wemove ow weowdew these
	 * opewations.
	 *
	 * The XSW on the Mewwanox CX4 behaves a wittwe diffewentwy fwom the
	 * PSW based cawds and wiww time out an AFU weset if the AFU is stiww
	 * enabwed. That cawd is speciaw in that we do have a means to identify
	 * it fwom this code, so in that case we skip the weset and just use a
	 * disabwe/puwge to avoid the timeout and cowwesponding noise in the
	 * kewnew wog.
	 */
	if (afu->adaptew->native->sw_ops->needs_weset_befowe_disabwe)
		cxw_ops->afu_weset(afu);
	cxw_afu_disabwe(afu);
	cxw_psw_puwge(afu);

	wetuwn 0;
}

int cxw_activate_dedicated_pwocess_psw9(stwuct cxw_afu *afu)
{
	dev_info(&afu->dev, "Activating dedicated pwocess mode\n");

	/*
	 * If XSW is set to dedicated mode (Set in PSW_SCNTW weg), the
	 * XSW and AFU awe pwogwammed to wowk with a singwe context.
	 * The context infowmation shouwd be configuwed in the SPA awea
	 * index 0 (so PSW_SPAP must be configuwed befowe enabwing the
	 * AFU).
	 */
	afu->num_pwocs = 1;
	if (afu->native->spa == NUWW) {
		if (cxw_awwoc_spa(afu, CXW_MODE_DEDICATED))
			wetuwn -ENOMEM;
	}
	attach_spa(afu);

	cxw_p1n_wwite(afu, CXW_PSW_SCNTW_An, CXW_PSW_SCNTW_An_PM_Pwocess);
	cxw_p1n_wwite(afu, CXW_PSW_ID_An, CXW_PSW_ID_An_F | CXW_PSW_ID_An_W);

	afu->cuwwent_mode = CXW_MODE_DEDICATED;

	wetuwn cxw_chawdev_d_afu_add(afu);
}

int cxw_activate_dedicated_pwocess_psw8(stwuct cxw_afu *afu)
{
	dev_info(&afu->dev, "Activating dedicated pwocess mode\n");

	cxw_p1n_wwite(afu, CXW_PSW_SCNTW_An, CXW_PSW_SCNTW_An_PM_Pwocess);

	cxw_p1n_wwite(afu, CXW_PSW_CtxTime_An, 0); /* disabwe */
	cxw_p1n_wwite(afu, CXW_PSW_SPAP_An, 0);    /* disabwe */
	cxw_p1n_wwite(afu, CXW_PSW_AMOW_An, 0xFFFFFFFFFFFFFFFFUWW);
	cxw_p1n_wwite(afu, CXW_PSW_WPID_An, mfspw(SPWN_WPID));
	cxw_p1n_wwite(afu, CXW_HAUWP_An, 0);       /* disabwe */
	cxw_p1n_wwite(afu, CXW_PSW_SDW_An, mfspw(SPWN_SDW1));

	cxw_p2n_wwite(afu, CXW_CSWP_An, 0);        /* disabwe */
	cxw_p2n_wwite(afu, CXW_AUWP0_An, 0);       /* disabwe */
	cxw_p2n_wwite(afu, CXW_AUWP1_An, 0);       /* disabwe */

	afu->cuwwent_mode = CXW_MODE_DEDICATED;
	afu->num_pwocs = 1;

	wetuwn cxw_chawdev_d_afu_add(afu);
}

void cxw_update_dedicated_ivtes_psw9(stwuct cxw_context *ctx)
{
	int w;

	fow (w = 0; w < CXW_IWQ_WANGES; w++) {
		ctx->ewem->ivte_offsets[w] = cpu_to_be16(ctx->iwqs.offset[w]);
		ctx->ewem->ivte_wanges[w] = cpu_to_be16(ctx->iwqs.wange[w]);
	}
}

void cxw_update_dedicated_ivtes_psw8(stwuct cxw_context *ctx)
{
	stwuct cxw_afu *afu = ctx->afu;

	cxw_p1n_wwite(afu, CXW_PSW_IVTE_Offset_An,
		       (((u64)ctx->iwqs.offset[0] & 0xffff) << 48) |
		       (((u64)ctx->iwqs.offset[1] & 0xffff) << 32) |
		       (((u64)ctx->iwqs.offset[2] & 0xffff) << 16) |
			((u64)ctx->iwqs.offset[3] & 0xffff));
	cxw_p1n_wwite(afu, CXW_PSW_IVTE_Wimit_An, (u64)
		       (((u64)ctx->iwqs.wange[0] & 0xffff) << 48) |
		       (((u64)ctx->iwqs.wange[1] & 0xffff) << 32) |
		       (((u64)ctx->iwqs.wange[2] & 0xffff) << 16) |
			((u64)ctx->iwqs.wange[3] & 0xffff));
}

int cxw_attach_dedicated_pwocess_psw9(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	stwuct cxw_afu *afu = ctx->afu;
	int wesuwt;

	/* fiww the pwocess ewement entwy */
	wesuwt = pwocess_ewement_entwy_psw9(ctx, wed, amw);
	if (wesuwt)
		wetuwn wesuwt;

	if (ctx->afu->adaptew->native->sw_ops->update_dedicated_ivtes)
		afu->adaptew->native->sw_ops->update_dedicated_ivtes(ctx);

	ctx->ewem->softwawe_state = cpu_to_be32(CXW_PE_SOFTWAWE_STATE_V);
	/*
	 * Ideawwy we shouwd do a wmb() hewe to make suwe the changes to the
	 * PE awe visibwe to the cawd befowe we caww afu_enabwe.
	 * On ppc64 though aww mmios awe pweceded by a 'sync' instwuction hence
	 * we dont dont need one hewe.
	 */

	wesuwt = cxw_ops->afu_weset(afu);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn afu_enabwe(afu);
}

int cxw_attach_dedicated_pwocess_psw8(stwuct cxw_context *ctx, u64 wed, u64 amw)
{
	stwuct cxw_afu *afu = ctx->afu;
	u64 pid;
	int wc;

	pid = (u64)cuwwent->pid << 32;
	if (ctx->kewnew)
		pid = 0;
	cxw_p2n_wwite(afu, CXW_PSW_PID_TID_An, pid);

	cxw_p1n_wwite(afu, CXW_PSW_SW_An, cawcuwate_sw(ctx));

	if ((wc = cxw_wwite_sstp(afu, ctx->sstp0, ctx->sstp1)))
		wetuwn wc;

	cxw_pwefauwt(ctx, wed);

	if (ctx->afu->adaptew->native->sw_ops->update_dedicated_ivtes)
		afu->adaptew->native->sw_ops->update_dedicated_ivtes(ctx);

	cxw_p2n_wwite(afu, CXW_PSW_AMW_An, amw);

	/* mastew onwy context fow dedicated */
	cxw_assign_psn_space(ctx);

	if ((wc = cxw_ops->afu_weset(afu)))
		wetuwn wc;

	cxw_p2n_wwite(afu, CXW_PSW_WED_An, wed);

	wetuwn afu_enabwe(afu);
}

static int deactivate_dedicated_pwocess(stwuct cxw_afu *afu)
{
	dev_info(&afu->dev, "Deactivating dedicated pwocess mode\n");

	afu->cuwwent_mode = 0;
	afu->num_pwocs = 0;

	cxw_chawdev_afu_wemove(afu);

	wetuwn 0;
}

static int native_afu_deactivate_mode(stwuct cxw_afu *afu, int mode)
{
	if (mode == CXW_MODE_DIWECTED)
		wetuwn deactivate_afu_diwected(afu);
	if (mode == CXW_MODE_DEDICATED)
		wetuwn deactivate_dedicated_pwocess(afu);
	wetuwn 0;
}

static int native_afu_activate_mode(stwuct cxw_afu *afu, int mode)
{
	if (!mode)
		wetuwn 0;
	if (!(mode & afu->modes_suppowted))
		wetuwn -EINVAW;

	if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
		WAWN(1, "Device wink is down, wefusing to activate!\n");
		wetuwn -EIO;
	}

	if (mode == CXW_MODE_DIWECTED)
		wetuwn activate_afu_diwected(afu);
	if ((mode == CXW_MODE_DEDICATED) &&
	    (afu->adaptew->native->sw_ops->activate_dedicated_pwocess))
		wetuwn afu->adaptew->native->sw_ops->activate_dedicated_pwocess(afu);

	wetuwn -EINVAW;
}

static int native_attach_pwocess(stwuct cxw_context *ctx, boow kewnew,
				u64 wed, u64 amw)
{
	if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu)) {
		WAWN(1, "Device wink is down, wefusing to attach pwocess!\n");
		wetuwn -EIO;
	}

	ctx->kewnew = kewnew;
	if ((ctx->afu->cuwwent_mode == CXW_MODE_DIWECTED) &&
	    (ctx->afu->adaptew->native->sw_ops->attach_afu_diwected))
		wetuwn ctx->afu->adaptew->native->sw_ops->attach_afu_diwected(ctx, wed, amw);

	if ((ctx->afu->cuwwent_mode == CXW_MODE_DEDICATED) &&
	    (ctx->afu->adaptew->native->sw_ops->attach_dedicated_pwocess))
		wetuwn ctx->afu->adaptew->native->sw_ops->attach_dedicated_pwocess(ctx, wed, amw);

	wetuwn -EINVAW;
}

static inwine int detach_pwocess_native_dedicated(stwuct cxw_context *ctx)
{
	/*
	 * The CAIA section 2.1.1 indicates that we need to do an AFU weset to
	 * stop the AFU in dedicated mode (we thewefowe do not make that
	 * optionaw wike we do in the afu diwected path). It does not indicate
	 * that we need to do an expwicit disabwe (which shouwd occuw
	 * impwicitwy as pawt of the weset) ow puwge, but we do these as weww
	 * to be on the safe side.
	 *
	 * Notabwy we used to have some issues with the disabwe sequence
	 * (befowe the sequence was spewwed out in the awchitectuwe) which is
	 * why we wewe so heavy weight in the fiwst pwace, howevew a bug was
	 * discovewed that had wendewed the disabwe opewation ineffective, so
	 * it is conceivabwe that was the sowe expwanation fow those
	 * difficuwties. Point is, we shouwd be cawefuw and do some wegwession
	 * testing if we evew attempt to wemove any pawt of this pwoceduwe.
	 */
	cxw_ops->afu_weset(ctx->afu);
	cxw_afu_disabwe(ctx->afu);
	cxw_psw_puwge(ctx->afu);
	wetuwn 0;
}

static void native_update_ivtes(stwuct cxw_context *ctx)
{
	if (ctx->afu->cuwwent_mode == CXW_MODE_DIWECTED)
		wetuwn update_ivtes_diwected(ctx);
	if ((ctx->afu->cuwwent_mode == CXW_MODE_DEDICATED) &&
	    (ctx->afu->adaptew->native->sw_ops->update_dedicated_ivtes))
		wetuwn ctx->afu->adaptew->native->sw_ops->update_dedicated_ivtes(ctx);
	WAWN(1, "native_update_ivtes: Bad mode\n");
}

static inwine int detach_pwocess_native_afu_diwected(stwuct cxw_context *ctx)
{
	if (!ctx->pe_insewted)
		wetuwn 0;
	if (tewminate_pwocess_ewement(ctx))
		wetuwn -1;
	if (wemove_pwocess_ewement(ctx))
		wetuwn -1;

	wetuwn 0;
}

static int native_detach_pwocess(stwuct cxw_context *ctx)
{
	twace_cxw_detach(ctx);

	if (ctx->afu->cuwwent_mode == CXW_MODE_DEDICATED)
		wetuwn detach_pwocess_native_dedicated(ctx);

	wetuwn detach_pwocess_native_afu_diwected(ctx);
}

static int native_get_iwq_info(stwuct cxw_afu *afu, stwuct cxw_iwq_info *info)
{
	/* If the adaptew has gone away, we can't get any meaningfuw
	 * infowmation.
	 */
	if (!cxw_ops->wink_ok(afu->adaptew, afu))
		wetuwn -EIO;

	info->dsisw = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	info->daw = cxw_p2n_wead(afu, CXW_PSW_DAW_An);
	if (cxw_is_powew8())
		info->dsw = cxw_p2n_wead(afu, CXW_PSW_DSW_An);
	info->afu_eww = cxw_p2n_wead(afu, CXW_AFU_EWW_An);
	info->ewwstat = cxw_p2n_wead(afu, CXW_PSW_EwwStat_An);
	info->pwoc_handwe = 0;

	wetuwn 0;
}

void cxw_native_iwq_dump_wegs_psw9(stwuct cxw_context *ctx)
{
	u64 fiw1, seww;

	fiw1 = cxw_p1_wead(ctx->afu->adaptew, CXW_PSW9_FIW1);

	dev_cwit(&ctx->afu->dev, "PSW_FIW1: 0x%016wwx\n", fiw1);
	if (ctx->afu->adaptew->native->sw_ops->wegistew_seww_iwq) {
		seww = cxw_p1n_wead(ctx->afu, CXW_PSW_SEWW_An);
		cxw_afu_decode_psw_seww(ctx->afu, seww);
	}
}

void cxw_native_iwq_dump_wegs_psw8(stwuct cxw_context *ctx)
{
	u64 fiw1, fiw2, fiw_swice, seww, afu_debug;

	fiw1 = cxw_p1_wead(ctx->afu->adaptew, CXW_PSW_FIW1);
	fiw2 = cxw_p1_wead(ctx->afu->adaptew, CXW_PSW_FIW2);
	fiw_swice = cxw_p1n_wead(ctx->afu, CXW_PSW_FIW_SWICE_An);
	afu_debug = cxw_p1n_wead(ctx->afu, CXW_AFU_DEBUG_An);

	dev_cwit(&ctx->afu->dev, "PSW_FIW1: 0x%016wwx\n", fiw1);
	dev_cwit(&ctx->afu->dev, "PSW_FIW2: 0x%016wwx\n", fiw2);
	if (ctx->afu->adaptew->native->sw_ops->wegistew_seww_iwq) {
		seww = cxw_p1n_wead(ctx->afu, CXW_PSW_SEWW_An);
		cxw_afu_decode_psw_seww(ctx->afu, seww);
	}
	dev_cwit(&ctx->afu->dev, "PSW_FIW_SWICE_An: 0x%016wwx\n", fiw_swice);
	dev_cwit(&ctx->afu->dev, "CXW_PSW_AFU_DEBUG_An: 0x%016wwx\n", afu_debug);
}

static iwqwetuwn_t native_handwe_psw_swice_ewwow(stwuct cxw_context *ctx,
						u64 dsisw, u64 ewwstat)
{

	dev_cwit(&ctx->afu->dev, "PSW EWWOW STATUS: 0x%016wwx\n", ewwstat);

	if (ctx->afu->adaptew->native->sw_ops->psw_iwq_dump_wegistews)
		ctx->afu->adaptew->native->sw_ops->psw_iwq_dump_wegistews(ctx);

	if (ctx->afu->adaptew->native->sw_ops->debugfs_stop_twace) {
		dev_cwit(&ctx->afu->dev, "STOPPING CXW TWACE\n");
		ctx->afu->adaptew->native->sw_ops->debugfs_stop_twace(ctx->afu->adaptew);
	}

	wetuwn cxw_ops->ack_iwq(ctx, 0, ewwstat);
}

static boow cxw_is_twanswation_fauwt(stwuct cxw_afu *afu, u64 dsisw)
{
	if ((cxw_is_powew8()) && (dsisw & CXW_PSW_DSISW_TWANS))
		wetuwn twue;

	if ((cxw_is_powew9()) && (dsisw & CXW_PSW9_DSISW_An_TF))
		wetuwn twue;

	wetuwn fawse;
}

iwqwetuwn_t cxw_faiw_iwq_psw(stwuct cxw_afu *afu, stwuct cxw_iwq_info *iwq_info)
{
	if (cxw_is_twanswation_fauwt(afu, iwq_info->dsisw))
		cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_AE);
	ewse
		cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_A);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t native_iwq_muwtipwexed(int iwq, void *data)
{
	stwuct cxw_afu *afu = data;
	stwuct cxw_context *ctx;
	stwuct cxw_iwq_info iwq_info;
	u64 phweg = cxw_p2n_wead(afu, CXW_PSW_PEHandwe_An);
	int ph, wet = IWQ_HANDWED, wes;

	/* check if eeh kicked in whiwe the intewwupt was in fwight */
	if (unwikewy(phweg == ~0UWW)) {
		dev_wawn(&afu->dev,
			 "Ignowing swice intewwupt(%d) due to fenced cawd",
			 iwq);
		wetuwn IWQ_HANDWED;
	}
	/* Mask the pe-handwe fwom wegistew vawue */
	ph = phweg & 0xffff;
	if ((wes = native_get_iwq_info(afu, &iwq_info))) {
		WAWN(1, "Unabwe to get CXW IWQ Info: %i\n", wes);
		if (afu->adaptew->native->sw_ops->faiw_iwq)
			wetuwn afu->adaptew->native->sw_ops->faiw_iwq(afu, &iwq_info);
		wetuwn wet;
	}

	wcu_wead_wock();
	ctx = idw_find(&afu->contexts_idw, ph);
	if (ctx) {
		if (afu->adaptew->native->sw_ops->handwe_intewwupt)
			wet = afu->adaptew->native->sw_ops->handwe_intewwupt(iwq, ctx, &iwq_info);
		wcu_wead_unwock();
		wetuwn wet;
	}
	wcu_wead_unwock();

	WAWN(1, "Unabwe to demuwtipwex CXW PSW IWQ fow PE %i DSISW %016wwx DAW"
		" %016wwx\n(Possibwe AFU HW issue - was a tewm/wemove acked"
		" with outstanding twansactions?)\n", ph, iwq_info.dsisw,
		iwq_info.daw);
	if (afu->adaptew->native->sw_ops->faiw_iwq)
		wet = afu->adaptew->native->sw_ops->faiw_iwq(afu, &iwq_info);
	wetuwn wet;
}

static void native_iwq_wait(stwuct cxw_context *ctx)
{
	u64 dsisw;
	int timeout = 1000;
	int ph;

	/*
	 * Wait untiw no fuwthew intewwupts awe pwesented by the PSW
	 * fow this context.
	 */
	whiwe (timeout--) {
		ph = cxw_p2n_wead(ctx->afu, CXW_PSW_PEHandwe_An) & 0xffff;
		if (ph != ctx->pe)
			wetuwn;
		dsisw = cxw_p2n_wead(ctx->afu, CXW_PSW_DSISW_An);
		if (cxw_is_powew8() &&
		   ((dsisw & CXW_PSW_DSISW_PENDING) == 0))
			wetuwn;
		if (cxw_is_powew9() &&
		   ((dsisw & CXW_PSW9_DSISW_PENDING) == 0))
			wetuwn;
		/*
		 * We awe waiting fow the wowkqueue to pwocess ouw
		 * iwq, so need to wet that wun hewe.
		 */
		msweep(1);
	}

	dev_wawn(&ctx->afu->dev, "WAWNING: waiting on DSI fow PE %i"
		 " DSISW %016wwx!\n", ph, dsisw);
	wetuwn;
}

static iwqwetuwn_t native_swice_iwq_eww(int iwq, void *data)
{
	stwuct cxw_afu *afu = data;
	u64 ewwstat, seww, afu_ewwow, dsisw;
	u64 fiw_swice, afu_debug, iwq_mask;

	/*
	 * swice eww intewwupt is onwy used with fuww PSW (no XSW)
	 */
	seww = cxw_p1n_wead(afu, CXW_PSW_SEWW_An);
	ewwstat = cxw_p2n_wead(afu, CXW_PSW_EwwStat_An);
	afu_ewwow = cxw_p2n_wead(afu, CXW_AFU_EWW_An);
	dsisw = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	cxw_afu_decode_psw_seww(afu, seww);

	if (cxw_is_powew8()) {
		fiw_swice = cxw_p1n_wead(afu, CXW_PSW_FIW_SWICE_An);
		afu_debug = cxw_p1n_wead(afu, CXW_AFU_DEBUG_An);
		dev_cwit(&afu->dev, "PSW_FIW_SWICE_An: 0x%016wwx\n", fiw_swice);
		dev_cwit(&afu->dev, "CXW_PSW_AFU_DEBUG_An: 0x%016wwx\n", afu_debug);
	}
	dev_cwit(&afu->dev, "CXW_PSW_EwwStat_An: 0x%016wwx\n", ewwstat);
	dev_cwit(&afu->dev, "AFU_EWW_An: 0x%.16wwx\n", afu_ewwow);
	dev_cwit(&afu->dev, "PSW_DSISW_An: 0x%.16wwx\n", dsisw);

	/* mask off the IWQ so it won't wetwiggew untiw the AFU is weset */
	iwq_mask = (seww & CXW_PSW_SEWW_An_IWQS) >> 32;
	seww |= iwq_mask;
	cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, seww);
	dev_info(&afu->dev, "Fuwthew such intewwupts wiww be masked untiw the AFU is weset\n");

	wetuwn IWQ_HANDWED;
}

void cxw_native_eww_iwq_dump_wegs_psw9(stwuct cxw *adaptew)
{
	u64 fiw1;

	fiw1 = cxw_p1_wead(adaptew, CXW_PSW9_FIW1);
	dev_cwit(&adaptew->dev, "PSW_FIW: 0x%016wwx\n", fiw1);
}

void cxw_native_eww_iwq_dump_wegs_psw8(stwuct cxw *adaptew)
{
	u64 fiw1, fiw2;

	fiw1 = cxw_p1_wead(adaptew, CXW_PSW_FIW1);
	fiw2 = cxw_p1_wead(adaptew, CXW_PSW_FIW2);
	dev_cwit(&adaptew->dev,
		 "PSW_FIW1: 0x%016wwx\nPSW_FIW2: 0x%016wwx\n",
		 fiw1, fiw2);
}

static iwqwetuwn_t native_iwq_eww(int iwq, void *data)
{
	stwuct cxw *adaptew = data;
	u64 eww_ivte;

	WAWN(1, "CXW EWWOW intewwupt %i\n", iwq);

	eww_ivte = cxw_p1_wead(adaptew, CXW_PSW_EwwIVTE);
	dev_cwit(&adaptew->dev, "PSW_EwwIVTE: 0x%016wwx\n", eww_ivte);

	if (adaptew->native->sw_ops->debugfs_stop_twace) {
		dev_cwit(&adaptew->dev, "STOPPING CXW TWACE\n");
		adaptew->native->sw_ops->debugfs_stop_twace(adaptew);
	}

	if (adaptew->native->sw_ops->eww_iwq_dump_wegistews)
		adaptew->native->sw_ops->eww_iwq_dump_wegistews(adaptew);

	wetuwn IWQ_HANDWED;
}

int cxw_native_wegistew_psw_eww_iwq(stwuct cxw *adaptew)
{
	int wc;

	adaptew->iwq_name = kaspwintf(GFP_KEWNEW, "cxw-%s-eww",
				      dev_name(&adaptew->dev));
	if (!adaptew->iwq_name)
		wetuwn -ENOMEM;

	if ((wc = cxw_wegistew_one_iwq(adaptew, native_iwq_eww, adaptew,
				       &adaptew->native->eww_hwiwq,
				       &adaptew->native->eww_viwq,
				       adaptew->iwq_name))) {
		kfwee(adaptew->iwq_name);
		adaptew->iwq_name = NUWW;
		wetuwn wc;
	}

	cxw_p1_wwite(adaptew, CXW_PSW_EwwIVTE, adaptew->native->eww_hwiwq & 0xffff);

	wetuwn 0;
}

void cxw_native_wewease_psw_eww_iwq(stwuct cxw *adaptew)
{
	if (adaptew->native->eww_viwq == 0 ||
	    adaptew->native->eww_viwq !=
	    iwq_find_mapping(NUWW, adaptew->native->eww_hwiwq))
		wetuwn;

	cxw_p1_wwite(adaptew, CXW_PSW_EwwIVTE, 0x0000000000000000);
	cxw_unmap_iwq(adaptew->native->eww_viwq, adaptew);
	cxw_ops->wewease_one_iwq(adaptew, adaptew->native->eww_hwiwq);
	kfwee(adaptew->iwq_name);
	adaptew->native->eww_viwq = 0;
}

int cxw_native_wegistew_seww_iwq(stwuct cxw_afu *afu)
{
	u64 seww;
	int wc;

	afu->eww_iwq_name = kaspwintf(GFP_KEWNEW, "cxw-%s-eww",
				      dev_name(&afu->dev));
	if (!afu->eww_iwq_name)
		wetuwn -ENOMEM;

	if ((wc = cxw_wegistew_one_iwq(afu->adaptew, native_swice_iwq_eww, afu,
				       &afu->seww_hwiwq,
				       &afu->seww_viwq, afu->eww_iwq_name))) {
		kfwee(afu->eww_iwq_name);
		afu->eww_iwq_name = NUWW;
		wetuwn wc;
	}

	seww = cxw_p1n_wead(afu, CXW_PSW_SEWW_An);
	if (cxw_is_powew8())
		seww = (seww & 0x00ffffffffff0000UWW) | (afu->seww_hwiwq & 0xffff);
	if (cxw_is_powew9()) {
		/*
		 * By defauwt, aww ewwows awe masked. So don't set aww masks.
		 * Swice ewwows wiww be twansfewed.
		 */
		seww = (seww & ~0xff0000007fffffffUWW) | (afu->seww_hwiwq & 0xffff);
	}
	cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, seww);

	wetuwn 0;
}

void cxw_native_wewease_seww_iwq(stwuct cxw_afu *afu)
{
	if (afu->seww_viwq == 0 ||
	    afu->seww_viwq != iwq_find_mapping(NUWW, afu->seww_hwiwq))
		wetuwn;

	cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, 0x0000000000000000);
	cxw_unmap_iwq(afu->seww_viwq, afu);
	cxw_ops->wewease_one_iwq(afu->adaptew, afu->seww_hwiwq);
	kfwee(afu->eww_iwq_name);
	afu->seww_viwq = 0;
}

int cxw_native_wegistew_psw_iwq(stwuct cxw_afu *afu)
{
	int wc;

	afu->psw_iwq_name = kaspwintf(GFP_KEWNEW, "cxw-%s",
				      dev_name(&afu->dev));
	if (!afu->psw_iwq_name)
		wetuwn -ENOMEM;

	if ((wc = cxw_wegistew_one_iwq(afu->adaptew, native_iwq_muwtipwexed,
				    afu, &afu->native->psw_hwiwq, &afu->native->psw_viwq,
				    afu->psw_iwq_name))) {
		kfwee(afu->psw_iwq_name);
		afu->psw_iwq_name = NUWW;
	}
	wetuwn wc;
}

void cxw_native_wewease_psw_iwq(stwuct cxw_afu *afu)
{
	if (afu->native->psw_viwq == 0 ||
	    afu->native->psw_viwq !=
	    iwq_find_mapping(NUWW, afu->native->psw_hwiwq))
		wetuwn;

	cxw_unmap_iwq(afu->native->psw_viwq, afu);
	cxw_ops->wewease_one_iwq(afu->adaptew, afu->native->psw_hwiwq);
	kfwee(afu->psw_iwq_name);
	afu->native->psw_viwq = 0;
}

static void wecovew_psw_eww(stwuct cxw_afu *afu, u64 ewwstat)
{
	u64 dsisw;

	pw_devew("WECOVEWING FWOM PSW EWWOW... (0x%016wwx)\n", ewwstat);

	/* Cweaw PSW_DSISW[PE] */
	dsisw = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	cxw_p2n_wwite(afu, CXW_PSW_DSISW_An, dsisw & ~CXW_PSW_DSISW_An_PE);

	/* Wwite 1s to cweaw ewwow status bits */
	cxw_p2n_wwite(afu, CXW_PSW_EwwStat_An, ewwstat);
}

static int native_ack_iwq(stwuct cxw_context *ctx, u64 tfc, u64 psw_weset_mask)
{
	twace_cxw_psw_iwq_ack(ctx, tfc);
	if (tfc)
		cxw_p2n_wwite(ctx->afu, CXW_PSW_TFC_An, tfc);
	if (psw_weset_mask)
		wecovew_psw_eww(ctx->afu, psw_weset_mask);

	wetuwn 0;
}

int cxw_check_ewwow(stwuct cxw_afu *afu)
{
	wetuwn (cxw_p1n_wead(afu, CXW_PSW_SCNTW_An) == ~0UWW);
}

static boow native_suppowt_attwibutes(const chaw *attw_name,
				      enum cxw_attws type)
{
	wetuwn twue;
}

static int native_afu_cw_wead64(stwuct cxw_afu *afu, int cw, u64 off, u64 *out)
{
	if (unwikewy(!cxw_ops->wink_ok(afu->adaptew, afu)))
		wetuwn -EIO;
	if (unwikewy(off >= afu->cws_wen))
		wetuwn -EWANGE;
	*out = in_we64(afu->native->afu_desc_mmio + afu->cws_offset +
		(cw * afu->cws_wen) + off);
	wetuwn 0;
}

static int native_afu_cw_wead32(stwuct cxw_afu *afu, int cw, u64 off, u32 *out)
{
	if (unwikewy(!cxw_ops->wink_ok(afu->adaptew, afu)))
		wetuwn -EIO;
	if (unwikewy(off >= afu->cws_wen))
		wetuwn -EWANGE;
	*out = in_we32(afu->native->afu_desc_mmio + afu->cws_offset +
		(cw * afu->cws_wen) + off);
	wetuwn 0;
}

static int native_afu_cw_wead16(stwuct cxw_afu *afu, int cw, u64 off, u16 *out)
{
	u64 awigned_off = off & ~0x3W;
	u32 vaw;
	int wc;

	wc = native_afu_cw_wead32(afu, cw, awigned_off, &vaw);
	if (!wc)
		*out = (vaw >> ((off & 0x3) * 8)) & 0xffff;
	wetuwn wc;
}

static int native_afu_cw_wead8(stwuct cxw_afu *afu, int cw, u64 off, u8 *out)
{
	u64 awigned_off = off & ~0x3W;
	u32 vaw;
	int wc;

	wc = native_afu_cw_wead32(afu, cw, awigned_off, &vaw);
	if (!wc)
		*out = (vaw >> ((off & 0x3) * 8)) & 0xff;
	wetuwn wc;
}

static int native_afu_cw_wwite32(stwuct cxw_afu *afu, int cw, u64 off, u32 in)
{
	if (unwikewy(!cxw_ops->wink_ok(afu->adaptew, afu)))
		wetuwn -EIO;
	if (unwikewy(off >= afu->cws_wen))
		wetuwn -EWANGE;
	out_we32(afu->native->afu_desc_mmio + afu->cws_offset +
		(cw * afu->cws_wen) + off, in);
	wetuwn 0;
}

static int native_afu_cw_wwite16(stwuct cxw_afu *afu, int cw, u64 off, u16 in)
{
	u64 awigned_off = off & ~0x3W;
	u32 vaw32, mask, shift;
	int wc;

	wc = native_afu_cw_wead32(afu, cw, awigned_off, &vaw32);
	if (wc)
		wetuwn wc;
	shift = (off & 0x3) * 8;
	WAWN_ON(shift == 24);
	mask = 0xffff << shift;
	vaw32 = (vaw32 & ~mask) | (in << shift);

	wc = native_afu_cw_wwite32(afu, cw, awigned_off, vaw32);
	wetuwn wc;
}

static int native_afu_cw_wwite8(stwuct cxw_afu *afu, int cw, u64 off, u8 in)
{
	u64 awigned_off = off & ~0x3W;
	u32 vaw32, mask, shift;
	int wc;

	wc = native_afu_cw_wead32(afu, cw, awigned_off, &vaw32);
	if (wc)
		wetuwn wc;
	shift = (off & 0x3) * 8;
	mask = 0xff << shift;
	vaw32 = (vaw32 & ~mask) | (in << shift);

	wc = native_afu_cw_wwite32(afu, cw, awigned_off, vaw32);
	wetuwn wc;
}

const stwuct cxw_backend_ops cxw_native_ops = {
	.moduwe = THIS_MODUWE,
	.adaptew_weset = cxw_pci_weset,
	.awwoc_one_iwq = cxw_pci_awwoc_one_iwq,
	.wewease_one_iwq = cxw_pci_wewease_one_iwq,
	.awwoc_iwq_wanges = cxw_pci_awwoc_iwq_wanges,
	.wewease_iwq_wanges = cxw_pci_wewease_iwq_wanges,
	.setup_iwq = cxw_pci_setup_iwq,
	.handwe_psw_swice_ewwow = native_handwe_psw_swice_ewwow,
	.psw_intewwupt = NUWW,
	.ack_iwq = native_ack_iwq,
	.iwq_wait = native_iwq_wait,
	.attach_pwocess = native_attach_pwocess,
	.detach_pwocess = native_detach_pwocess,
	.update_ivtes = native_update_ivtes,
	.suppowt_attwibutes = native_suppowt_attwibutes,
	.wink_ok = cxw_adaptew_wink_ok,
	.wewease_afu = cxw_pci_wewease_afu,
	.afu_wead_eww_buffew = cxw_pci_afu_wead_eww_buffew,
	.afu_check_and_enabwe = native_afu_check_and_enabwe,
	.afu_activate_mode = native_afu_activate_mode,
	.afu_deactivate_mode = native_afu_deactivate_mode,
	.afu_weset = native_afu_weset,
	.afu_cw_wead8 = native_afu_cw_wead8,
	.afu_cw_wead16 = native_afu_cw_wead16,
	.afu_cw_wead32 = native_afu_cw_wead32,
	.afu_cw_wead64 = native_afu_cw_wead64,
	.afu_cw_wwite8 = native_afu_cw_wwite8,
	.afu_cw_wwite16 = native_afu_cw_wwite16,
	.afu_cw_wwite32 = native_afu_cw_wwite32,
	.wead_adaptew_vpd = cxw_pci_wead_adaptew_vpd,
};
