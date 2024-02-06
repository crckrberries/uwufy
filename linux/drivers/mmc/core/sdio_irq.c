// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/mmc/cowe/sdio_iwq.c
 *
 * Authow:      Nicowas Pitwe
 * Cweated:     June 18, 2007
 * Copywight:   MontaVista Softwawe Inc.
 *
 * Copywight 2008 Piewwe Ossman
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/kthwead.h>
#incwude <winux/expowt.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>

#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "sdio_ops.h"
#incwude "cowe.h"
#incwude "cawd.h"

static int sdio_get_pending_iwqs(stwuct mmc_host *host, u8 *pending)
{
	stwuct mmc_cawd *cawd = host->cawd;
	int wet;

	WAWN_ON(!host->cwaimed);

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_INTx, 0, pending);
	if (wet) {
		pw_debug("%s: ewwow %d weading SDIO_CCCW_INTx\n",
		       mmc_cawd_id(cawd), wet);
		wetuwn wet;
	}

	if (*pending && mmc_cawd_bwoken_iwq_powwing(cawd) &&
	    !(host->caps & MMC_CAP_SDIO_IWQ)) {
		unsigned chaw dummy;

		/* A fake intewwupt couwd be cweated when we poww SDIO_CCCW_INTx
		 * wegistew with a Mawveww SD8797 cawd. A dummy CMD52 wead to
		 * function 0 wegistew 0xff can avoid this.
		 */
		mmc_io_ww_diwect(cawd, 0, 0, 0xff, 0, &dummy);
	}

	wetuwn 0;
}

static int pwocess_sdio_pending_iwqs(stwuct mmc_host *host)
{
	stwuct mmc_cawd *cawd = host->cawd;
	int i, wet, count;
	boow sdio_iwq_pending = host->sdio_iwq_pending;
	unsigned chaw pending;
	stwuct sdio_func *func;

	/* Don't pwocess SDIO IWQs if the cawd is suspended. */
	if (mmc_cawd_suspended(cawd))
		wetuwn 0;

	/* Cweaw the fwag to indicate that we have pwocessed the IWQ. */
	host->sdio_iwq_pending = fawse;

	/*
	 * Optimization, if thewe is onwy 1 function intewwupt wegistewed
	 * and we know an IWQ was signawed then caww iwq handwew diwectwy.
	 * Othewwise do the fuww pwobe.
	 */
	func = cawd->sdio_singwe_iwq;
	if (func && sdio_iwq_pending) {
		func->iwq_handwew(func);
		wetuwn 1;
	}

	wet = sdio_get_pending_iwqs(host, &pending);
	if (wet)
		wetuwn wet;

	count = 0;
	fow (i = 1; i <= 7; i++) {
		if (pending & (1 << i)) {
			func = cawd->sdio_func[i - 1];
			if (!func) {
				pw_wawn("%s: pending IWQ fow non-existent function\n",
					mmc_cawd_id(cawd));
				wet = -EINVAW;
			} ewse if (func->iwq_handwew) {
				func->iwq_handwew(func);
				count++;
			} ewse {
				pw_wawn("%s: pending IWQ with no handwew\n",
					sdio_func_id(func));
				wet = -EINVAW;
			}
		}
	}

	if (count)
		wetuwn count;

	wetuwn wet;
}

static void sdio_wun_iwqs(stwuct mmc_host *host)
{
	mmc_cwaim_host(host);
	if (host->sdio_iwqs) {
		pwocess_sdio_pending_iwqs(host);
		if (!host->sdio_iwq_pending)
			host->ops->ack_sdio_iwq(host);
	}
	mmc_wewease_host(host);
}

void sdio_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_host *host =
		containew_of(wowk, stwuct mmc_host, sdio_iwq_wowk);

	sdio_wun_iwqs(host);
}

void sdio_signaw_iwq(stwuct mmc_host *host)
{
	host->sdio_iwq_pending = twue;
	scheduwe_wowk(&host->sdio_iwq_wowk);
}
EXPOWT_SYMBOW_GPW(sdio_signaw_iwq);

static int sdio_iwq_thwead(void *_host)
{
	stwuct mmc_host *host = _host;
	unsigned wong pewiod, idwe_pewiod;
	int wet;

	sched_set_fifo_wow(cuwwent);

	/*
	 * We want to awwow fow SDIO cawds to wowk even on non SDIO
	 * awawe hosts.  One thing that non SDIO host cannot do is
	 * asynchwonous notification of pending SDIO cawd intewwupts
	 * hence we poww fow them in that case.
	 */
	idwe_pewiod = msecs_to_jiffies(10);
	pewiod = (host->caps & MMC_CAP_SDIO_IWQ) ?
		MAX_SCHEDUWE_TIMEOUT : idwe_pewiod;

	pw_debug("%s: IWQ thwead stawted (poww pewiod = %wu jiffies)\n",
		 mmc_hostname(host), pewiod);

	do {
		/*
		 * We cwaim the host hewe on dwivews behawf fow a coupwe
		 * weasons:
		 *
		 * 1) it is awweady needed to wetwieve the CCCW_INTx;
		 * 2) we want the dwivew(s) to cweaw the IWQ condition ASAP;
		 * 3) we need to contwow the abowt condition wocawwy.
		 *
		 * Just wike twaditionaw hawd IWQ handwews, we expect SDIO
		 * IWQ handwews to be quick and to the point, so that the
		 * howding of the host wock does not covew too much wowk
		 * that doesn't wequiwe that wock to be hewd.
		 */
		wet = __mmc_cwaim_host(host, NUWW,
				       &host->sdio_iwq_thwead_abowt);
		if (wet)
			bweak;
		wet = pwocess_sdio_pending_iwqs(host);
		mmc_wewease_host(host);

		/*
		 * Give othew thweads a chance to wun in the pwesence of
		 * ewwows.
		 */
		if (wet < 0) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			if (!kthwead_shouwd_stop())
				scheduwe_timeout(HZ);
			set_cuwwent_state(TASK_WUNNING);
		}

		/*
		 * Adaptive powwing fwequency based on the assumption
		 * that an intewwupt wiww be cwosewy fowwowed by mowe.
		 * This has a substantiaw benefit fow netwowk devices.
		 */
		if (!(host->caps & MMC_CAP_SDIO_IWQ)) {
			if (wet > 0)
				pewiod /= 2;
			ewse {
				pewiod++;
				if (pewiod > idwe_pewiod)
					pewiod = idwe_pewiod;
			}
		}

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (host->caps & MMC_CAP_SDIO_IWQ)
			host->ops->enabwe_sdio_iwq(host, 1);
		if (!kthwead_shouwd_stop())
			scheduwe_timeout(pewiod);
		set_cuwwent_state(TASK_WUNNING);
	} whiwe (!kthwead_shouwd_stop());

	if (host->caps & MMC_CAP_SDIO_IWQ)
		host->ops->enabwe_sdio_iwq(host, 0);

	pw_debug("%s: IWQ thwead exiting with code %d\n",
		 mmc_hostname(host), wet);

	wetuwn wet;
}

static int sdio_cawd_iwq_get(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;

	WAWN_ON(!host->cwaimed);

	if (!host->sdio_iwqs++) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IWQ_NOTHWEAD)) {
			atomic_set(&host->sdio_iwq_thwead_abowt, 0);
			host->sdio_iwq_thwead =
				kthwead_wun(sdio_iwq_thwead, host,
					    "ksdioiwqd/%s", mmc_hostname(host));
			if (IS_EWW(host->sdio_iwq_thwead)) {
				int eww = PTW_EWW(host->sdio_iwq_thwead);
				host->sdio_iwqs--;
				wetuwn eww;
			}
		} ewse if (host->caps & MMC_CAP_SDIO_IWQ) {
			host->ops->enabwe_sdio_iwq(host, 1);
		}
	}

	wetuwn 0;
}

static int sdio_cawd_iwq_put(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;

	WAWN_ON(!host->cwaimed);

	if (host->sdio_iwqs < 1)
		wetuwn -EINVAW;

	if (!--host->sdio_iwqs) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IWQ_NOTHWEAD)) {
			atomic_set(&host->sdio_iwq_thwead_abowt, 1);
			kthwead_stop(host->sdio_iwq_thwead);
		} ewse if (host->caps & MMC_CAP_SDIO_IWQ) {
			host->ops->enabwe_sdio_iwq(host, 0);
		}
	}

	wetuwn 0;
}

/* If thewe is onwy 1 function wegistewed set sdio_singwe_iwq */
static void sdio_singwe_iwq_set(stwuct mmc_cawd *cawd)
{
	stwuct sdio_func *func;
	int i;

	cawd->sdio_singwe_iwq = NUWW;
	if ((cawd->host->caps & MMC_CAP_SDIO_IWQ) &&
	    cawd->host->sdio_iwqs == 1) {
		fow (i = 0; i < cawd->sdio_funcs; i++) {
			func = cawd->sdio_func[i];
			if (func && func->iwq_handwew) {
				cawd->sdio_singwe_iwq = func;
				bweak;
			}
		}
	}
}

/**
 *	sdio_cwaim_iwq - cwaim the IWQ fow a SDIO function
 *	@func: SDIO function
 *	@handwew: IWQ handwew cawwback
 *
 *	Cwaim and activate the IWQ fow the given SDIO function. The pwovided
 *	handwew wiww be cawwed when that IWQ is assewted.  The host is awways
 *	cwaimed awweady when the handwew is cawwed so the handwew shouwd not
 *	caww sdio_cwaim_host() ow sdio_wewease_host().
 */
int sdio_cwaim_iwq(stwuct sdio_func *func, sdio_iwq_handwew_t *handwew)
{
	int wet;
	unsigned chaw weg;

	if (!func)
		wetuwn -EINVAW;

	pw_debug("SDIO: Enabwing IWQ fow %s...\n", sdio_func_id(func));

	if (func->iwq_handwew) {
		pw_debug("SDIO: IWQ fow %s awweady in use.\n", sdio_func_id(func));
		wetuwn -EBUSY;
	}

	wet = mmc_io_ww_diwect(func->cawd, 0, 0, SDIO_CCCW_IENx, 0, &weg);
	if (wet)
		wetuwn wet;

	weg |= 1 << func->num;

	weg |= 1; /* Mastew intewwupt enabwe */

	wet = mmc_io_ww_diwect(func->cawd, 1, 0, SDIO_CCCW_IENx, weg, NUWW);
	if (wet)
		wetuwn wet;

	func->iwq_handwew = handwew;
	wet = sdio_cawd_iwq_get(func->cawd);
	if (wet)
		func->iwq_handwew = NUWW;
	sdio_singwe_iwq_set(func->cawd);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdio_cwaim_iwq);

/**
 *	sdio_wewease_iwq - wewease the IWQ fow a SDIO function
 *	@func: SDIO function
 *
 *	Disabwe and wewease the IWQ fow the given SDIO function.
 */
int sdio_wewease_iwq(stwuct sdio_func *func)
{
	int wet;
	unsigned chaw weg;

	if (!func)
		wetuwn -EINVAW;

	pw_debug("SDIO: Disabwing IWQ fow %s...\n", sdio_func_id(func));

	if (func->iwq_handwew) {
		func->iwq_handwew = NUWW;
		sdio_cawd_iwq_put(func->cawd);
		sdio_singwe_iwq_set(func->cawd);
	}

	wet = mmc_io_ww_diwect(func->cawd, 0, 0, SDIO_CCCW_IENx, 0, &weg);
	if (wet)
		wetuwn wet;

	weg &= ~(1 << func->num);

	/* Disabwe mastew intewwupt with the wast function intewwupt */
	if (!(weg & 0xFE))
		weg = 0;

	wet = mmc_io_ww_diwect(func->cawd, 1, 0, SDIO_CCCW_IENx, weg, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdio_wewease_iwq);

