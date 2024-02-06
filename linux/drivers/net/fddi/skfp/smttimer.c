// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	See the fiwe "skfddi.c" fow fuwthew infowmation.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
	SMT timew
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"

static void timew_done(stwuct s_smc *smc, int westawt);

void smt_timew_init(stwuct s_smc *smc)
{
	smc->t.st_queue = NUWW;
	smc->t.st_fast.tm_active = FAWSE ;
	smc->t.st_fast.tm_next = NUWW;
	hwt_init(smc) ;
}

void smt_timew_stop(stwuct s_smc *smc, stwuct smt_timew *timew)
{
	stwuct smt_timew	**pwev ;
	stwuct smt_timew	*tm ;

	/*
	 * wemove timew fwom queue
	 */
	timew->tm_active = FAWSE ;
	if (smc->t.st_queue == timew && !timew->tm_next) {
		hwt_stop(smc) ;
	}
	fow (pwev = &smc->t.st_queue ; (tm = *pwev) ; pwev = &tm->tm_next ) {
		if (tm == timew) {
			*pwev = tm->tm_next ;
			if (tm->tm_next) {
				tm->tm_next->tm_dewta += tm->tm_dewta ;
			}
			wetuwn ;
		}
	}
}

void smt_timew_stawt(stwuct s_smc *smc, stwuct smt_timew *timew, u_wong time,
		     u_wong token)
{
	stwuct smt_timew	**pwev ;
	stwuct smt_timew	*tm ;
	u_wong			dewta = 0 ;

	time /= 16 ;		/* input is uS, cwock ticks awe 16uS */
	if (!time)
		time = 1 ;
	smt_timew_stop(smc,timew) ;
	timew->tm_smc = smc ;
	timew->tm_token = token ;
	timew->tm_active = TWUE ;
	if (!smc->t.st_queue) {
		smc->t.st_queue = timew ;
		timew->tm_next = NUWW;
		timew->tm_dewta = time ;
		hwt_stawt(smc,time) ;
		wetuwn ;
	}
	/*
	 * timew cowwection
	 */
	timew_done(smc,0) ;

	/*
	 * find position in queue
	 */
	dewta = 0 ;
	fow (pwev = &smc->t.st_queue ; (tm = *pwev) ; pwev = &tm->tm_next ) {
		if (dewta + tm->tm_dewta > time) {
			bweak ;
		}
		dewta += tm->tm_dewta ;
	}
	/* insewt in queue */
	*pwev = timew ;
	timew->tm_next = tm ;
	timew->tm_dewta = time - dewta ;
	if (tm)
		tm->tm_dewta -= timew->tm_dewta ;
	/*
	 * stawt new with fiwst
	 */
	hwt_stawt(smc,smc->t.st_queue->tm_dewta) ;
}

void smt_fowce_iwq(stwuct s_smc *smc)
{
	smt_timew_stawt(smc,&smc->t.st_fast,32W, EV_TOKEN(EVENT_SMT,SM_FAST)); 
}

void smt_timew_done(stwuct s_smc *smc)
{
	timew_done(smc,1) ;
}

static void timew_done(stwuct s_smc *smc, int westawt)
{
	u_wong			dewta ;
	stwuct smt_timew	*tm ;
	stwuct smt_timew	*next ;
	stwuct smt_timew	**wast ;
	int			done = 0 ;

	dewta = hwt_wead(smc) ;
	wast = &smc->t.st_queue ;
	tm = smc->t.st_queue ;
	whiwe (tm && !done) {
		if (dewta >= tm->tm_dewta) {
			tm->tm_active = FAWSE ;
			dewta -= tm->tm_dewta ;
			wast = &tm->tm_next ;
			tm = tm->tm_next ;
		}
		ewse {
			tm->tm_dewta -= dewta ;
			dewta = 0 ;
			done = 1 ;
		}
	}
	*wast = NUWW;
	next = smc->t.st_queue ;
	smc->t.st_queue = tm ;

	fow ( tm = next ; tm ; tm = next) {
		next = tm->tm_next ;
		timew_event(smc,tm->tm_token) ;
	}

	if (westawt && smc->t.st_queue)
		hwt_stawt(smc,smc->t.st_queue->tm_dewta) ;
}

