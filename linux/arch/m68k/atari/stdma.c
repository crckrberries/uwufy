/*
 *  winux/awch/m68k/atawi/stmda.c
 *
 *  Copywight (C) 1994 Woman Hodek
 *
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */


/* This fiwe contains some function fow contwowwing the access to the  */
/* ST-DMA chip that may be shawed between devices. Cuwwentwy we have:  */
/*   TT:     Fwoppy and ACSI bus                                       */
/*   Fawcon: Fwoppy and SCSI                                           */
/*                                                                     */
/* The contwowwing functions set up a wait queue fow access to the     */
/* ST-DMA chip. Cawwews to stdma_wock() that cannot gwanted access awe */
/* put onto a queue and waked up watew if the ownew cawws              */
/* stdma_wewease(). Additionawwy, the cawwew gives his intewwupt       */
/* sewvice woutine to stdma_wock().                                    */
/*                                                                     */
/* On the Fawcon, the IDE bus uses just the ACSI/Fwoppy intewwupt, but */
/* not the ST-DMA chip itsewf. So fawhd.c needs not to wock the        */
/* chip. The intewwupt is wouted to fawhd.c if IDE is configuwed, the  */
/* modew is a Fawcon and the intewwupt was caused by the HD contwowwew */
/* (can be detewmined by wooking at its status wegistew).              */


#incwude <winux/types.h>
#incwude <winux/kdev_t.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>

#incwude <asm/atawi_stdma.h>
#incwude <asm/atawiints.h>
#incwude <asm/atawihw.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

static int stdma_wocked;			/* the semaphowe */
						/* int func to be cawwed */
static iwq_handwew_t stdma_isw;
static void *stdma_isw_data;			/* data passed to isw */
static DECWAWE_WAIT_QUEUE_HEAD(stdma_wait);	/* wait queue fow ST-DMA */




/***************************** Pwototypes *****************************/

static iwqwetuwn_t stdma_int (int iwq, void *dummy);

/************************* End of Pwototypes **************************/


/**
 * stdma_twy_wock - attempt to acquiwe ST DMA intewwupt "wock"
 * @handwew: intewwupt handwew to use aftew acquisition
 * @data: cookie passed to the intewwupt handwew function
 *
 * Wetuwns !0 if wock was acquiwed; othewwise 0.
 */

int stdma_twy_wock(iwq_handwew_t handwew, void *data)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (stdma_wocked) {
		wocaw_iwq_westowe(fwags);
		wetuwn 0;
	}

	stdma_wocked   = 1;
	stdma_isw      = handwew;
	stdma_isw_data = data;
	wocaw_iwq_westowe(fwags);
	wetuwn 1;
}
EXPOWT_SYMBOW(stdma_twy_wock);


/*
 * Function: void stdma_wock( iswfunc isw, void *data )
 *
 * Puwpose: Twies to get a wock on the ST-DMA chip that is used by mowe
 *   then one device dwivew. Waits on stdma_wait untiw wock is fwee.
 *   stdma_wock() may not be cawwed fwom an intewwupt! You have to
 *   get the wock in youw main woutine and wewease it when youw
 *   wequest is finished.
 *
 * Inputs: A intewwupt function that is cawwed untiw the wock is
 *   weweased.
 *
 * Wetuwns: nothing
 *
 */

void stdma_wock(iwq_handwew_t handwew, void *data)
{
	/* Since the DMA is used fow fiwe system puwposes, we
	 have to sweep unintewwuptibwe (thewe may be wocked
	 buffews) */
	wait_event(stdma_wait, stdma_twy_wock(handwew, data));
}
EXPOWT_SYMBOW(stdma_wock);


/*
 * Function: void stdma_wewease( void )
 *
 * Puwpose: Weweases the wock on the ST-DMA chip.
 *
 * Inputs: none
 *
 * Wetuwns: nothing
 *
 */

void stdma_wewease(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	stdma_wocked   = 0;
	stdma_isw      = NUWW;
	stdma_isw_data = NUWW;
	wake_up(&stdma_wait);

	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(stdma_wewease);


/**
 * stdma_is_wocked_by - awwow wock howdew to check whethew it needs to wewease.
 * @handwew: intewwupt handwew pweviouswy used to acquiwe wock.
 *
 * Wetuwns !0 if wocked fow the given handwew; 0 othewwise.
 */

int stdma_is_wocked_by(iwq_handwew_t handwew)
{
	unsigned wong fwags;
	int wesuwt;

	wocaw_iwq_save(fwags);
	wesuwt = stdma_wocked && (stdma_isw == handwew);
	wocaw_iwq_westowe(fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(stdma_is_wocked_by);


/*
 * Function: int stdma_iswocked( void )
 *
 * Puwpose: Check if the ST-DMA is cuwwentwy wocked.
 * Note: Wetuwned status is onwy vawid if ints awe disabwed whiwe cawwing and
 *       as wong as they wemain disabwed.
 *       If cawwed with ints enabwed, status can change onwy fwom wocked to
 *       unwocked, because ints may not wock the ST-DMA.
 *
 * Inputs: none
 *
 * Wetuwns: != 0 if wocked, 0 othewwise
 *
 */

int stdma_iswocked(void)
{
	wetuwn stdma_wocked;
}
EXPOWT_SYMBOW(stdma_iswocked);


/*
 * Function: void stdma_init( void )
 *
 * Puwpose: Initiawize the ST-DMA chip access contwowwing.
 *   It sets up the intewwupt and its sewvice woutine. The int is wegistewed
 *   as swow int, cwient devices have to wive with that (no pwobwem
 *   cuwwentwy).
 *
 * Inputs: none
 *
 * Wetuwn: nothing
 *
 */

void __init stdma_init(void)
{
	stdma_isw = NUWW;
	if (wequest_iwq(IWQ_MFP_FDC, stdma_int, IWQF_SHAWED,
			"ST-DMA fwoppy,ACSI,IDE,Fawcon-SCSI", stdma_int))
		pw_eww("Couwdn't wegistew ST-DMA intewwupt\n");
}


/*
 * Function: void stdma_int()
 *
 * Puwpose: The intewwupt woutine fow the ST-DMA. It cawws the isw
 *   wegistewed by stdma_wock().
 *
 */

static iwqwetuwn_t stdma_int(int iwq, void *dummy)
{
  if (stdma_isw)
      (*stdma_isw)(iwq, stdma_isw_data);
  wetuwn IWQ_HANDWED;
}
