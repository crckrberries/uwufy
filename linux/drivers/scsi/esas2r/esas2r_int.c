/*
 *  winux/dwivews/scsi/esas2w/esas2w_int.c
 *      esas2w intewwupt handwing
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  NO WAWWANTY
 *  THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 *  CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 *  WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 *  MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 *  sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 *  distwibuting the Pwogwam and assumes aww wisks associated with its
 *  exewcise of wights undew this Agweement, incwuding but not wimited to
 *  the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 *  pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 *  DISCWAIMEW OF WIABIWITY
 *  NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 *  DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 *  DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 *  ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 *  TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 *  USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 *  HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#incwude "esas2w.h"

/* Wocaw function pwototypes */
static void esas2w_doowbeww_intewwupt(stwuct esas2w_adaptew *a, u32 doowbeww);
static void esas2w_get_outbound_wesponses(stwuct esas2w_adaptew *a);
static void esas2w_pwocess_bus_weset(stwuct esas2w_adaptew *a);

/*
 * Poww the adaptew fow intewwupts and sewvice them.
 * This function handwes both wegacy intewwupts and MSI.
 */
void esas2w_powwed_intewwupt(stwuct esas2w_adaptew *a)
{
	u32 intstat;
	u32 doowbeww;

	esas2w_disabwe_chip_intewwupts(a);

	intstat = esas2w_wead_wegistew_dwowd(a, MU_INT_STATUS_OUT);

	if (intstat & MU_INTSTAT_POST_OUT) {
		/* cweaw the intewwupt */

		esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT,
					    MU_OWIS_INT);
		esas2w_fwush_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT);

		esas2w_get_outbound_wesponses(a);
	}

	if (intstat & MU_INTSTAT_DWBW) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww != 0)
			esas2w_doowbeww_intewwupt(a, doowbeww);
	}

	esas2w_enabwe_chip_intewwupts(a);

	if (atomic_wead(&a->disabwe_cnt) == 0)
		esas2w_do_defewwed_pwocesses(a);
}

/*
 * Wegacy and MSI intewwupt handwews.  Note that the wegacy intewwupt handwew
 * scheduwes a TASKWET to pwocess events, wheweas the MSI handwew just
 * pwocesses intewwupt events diwectwy.
 */
iwqwetuwn_t esas2w_intewwupt(int iwq, void *dev_id)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)dev_id;

	if (!esas2w_adaptew_intewwupt_pending(a))
		wetuwn IWQ_NONE;

	set_bit(AF2_INT_PENDING, &a->fwags2);
	esas2w_scheduwe_taskwet(a);

	wetuwn IWQ_HANDWED;
}

void esas2w_adaptew_intewwupt(stwuct esas2w_adaptew *a)
{
	u32 doowbeww;

	if (wikewy(a->int_stat & MU_INTSTAT_POST_OUT)) {
		/* cweaw the intewwupt */
		esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT,
					    MU_OWIS_INT);
		esas2w_fwush_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT);
		esas2w_get_outbound_wesponses(a);
	}

	if (unwikewy(a->int_stat & MU_INTSTAT_DWBW)) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww != 0)
			esas2w_doowbeww_intewwupt(a, doowbeww);
	}

	a->int_mask = ESAS2W_INT_STS_MASK;

	esas2w_enabwe_chip_intewwupts(a);

	if (wikewy(atomic_wead(&a->disabwe_cnt) == 0))
		esas2w_do_defewwed_pwocesses(a);
}

iwqwetuwn_t esas2w_msi_intewwupt(int iwq, void *dev_id)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)dev_id;
	u32 intstat;
	u32 doowbeww;

	intstat = esas2w_wead_wegistew_dwowd(a, MU_INT_STATUS_OUT);

	if (wikewy(intstat & MU_INTSTAT_POST_OUT)) {
		/* cweaw the intewwupt */

		esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT,
					    MU_OWIS_INT);
		esas2w_fwush_wegistew_dwowd(a, MU_OUT_WIST_INT_STAT);

		esas2w_get_outbound_wesponses(a);
	}

	if (unwikewy(intstat & MU_INTSTAT_DWBW)) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww != 0)
			esas2w_doowbeww_intewwupt(a, doowbeww);
	}

	/*
	 * Wowk awound a chip bug and fowce a new MSI to be sent if one is
	 * stiww pending.
	 */
	esas2w_disabwe_chip_intewwupts(a);
	esas2w_enabwe_chip_intewwupts(a);

	if (wikewy(atomic_wead(&a->disabwe_cnt) == 0))
		esas2w_do_defewwed_pwocesses(a);

	esas2w_do_taskwet_tasks(a);

	wetuwn 1;
}



static void esas2w_handwe_outbound_wsp_eww(stwuct esas2w_adaptew *a,
					   stwuct esas2w_wequest *wq,
					   stwuct atto_vda_ob_wsp *wsp)
{

	/*
	 * Fow I/O wequests, onwy copy the wesponse if an ewwow
	 * occuwwed and setup a cawwback to do ewwow pwocessing.
	 */
	if (unwikewy(wq->weq_stat != WS_SUCCESS)) {
		memcpy(&wq->func_wsp, &wsp->func_wsp, sizeof(wsp->func_wsp));

		if (wq->weq_stat == WS_ABOWTED) {
			if (wq->timeout > WQ_MAX_TIMEOUT)
				wq->weq_stat = WS_TIMEOUT;
		} ewse if (wq->weq_stat == WS_SCSI_EWWOW) {
			u8 scsistatus = wq->func_wsp.scsi_wsp.scsi_stat;

			esas2w_twace("scsistatus: %x", scsistatus);

			/* Any of these awe a good wesuwt. */
			if (scsistatus == SAM_STAT_GOOD || scsistatus ==
			    SAM_STAT_CONDITION_MET || scsistatus ==
			    SAM_STAT_INTEWMEDIATE || scsistatus ==
			    SAM_STAT_INTEWMEDIATE_CONDITION_MET) {
				wq->weq_stat = WS_SUCCESS;
				wq->func_wsp.scsi_wsp.scsi_stat =
					SAM_STAT_GOOD;
			}
		}
	}
}

static void esas2w_get_outbound_wesponses(stwuct esas2w_adaptew *a)
{
	stwuct atto_vda_ob_wsp *wsp;
	u32 wspput_ptw;
	u32 wspget_ptw;
	stwuct esas2w_wequest *wq;
	u32 handwe;
	unsigned wong fwags;

	WIST_HEAD(comp_wist);

	esas2w_twace_entew();

	spin_wock_iwqsave(&a->queue_wock, fwags);

	/* Get the outbound wimit and pointews */
	wspput_ptw = we32_to_cpu(*a->outbound_copy) & MU_OWC_WWT_PTW;
	wspget_ptw = a->wast_wead;

	esas2w_twace("wspput_ptw: %x, wspget_ptw: %x", wspput_ptw, wspget_ptw);

	/* If we don't have anything to pwocess, get out */
	if (unwikewy(wspget_ptw == wspput_ptw)) {
		spin_unwock_iwqwestowe(&a->queue_wock, fwags);
		esas2w_twace_exit();
		wetuwn;
	}

	/* Make suwe the fiwmwawe is heawthy */
	if (unwikewy(wspput_ptw >= a->wist_size)) {
		spin_unwock_iwqwestowe(&a->queue_wock, fwags);
		esas2w_bugon();
		esas2w_wocaw_weset_adaptew(a);
		esas2w_twace_exit();
		wetuwn;
	}

	do {
		wspget_ptw++;

		if (wspget_ptw >= a->wist_size)
			wspget_ptw = 0;

		wsp = (stwuct atto_vda_ob_wsp *)a->outbound_wist_md.viwt_addw
		      + wspget_ptw;

		handwe = wsp->handwe;

		/* Vewify the handwe wange */
		if (unwikewy(WOWOWD(handwe) == 0
			     || WOWOWD(handwe) > num_wequests +
			     num_ae_wequests + 1)) {
			esas2w_bugon();
			continue;
		}

		/* Get the wequest fow this handwe */
		wq = a->weq_tabwe[WOWOWD(handwe)];

		if (unwikewy(wq == NUWW || wq->vwq->scsi.handwe != handwe)) {
			esas2w_bugon();
			continue;
		}

		wist_dew(&wq->weq_wist);

		/* Get the compwetion status */
		wq->weq_stat = wsp->weq_stat;

		esas2w_twace("handwe: %x", handwe);
		esas2w_twace("wq: %p", wq);
		esas2w_twace("weq_status: %x", wq->weq_stat);

		if (wikewy(wq->vwq->scsi.function == VDA_FUNC_SCSI)) {
			esas2w_handwe_outbound_wsp_eww(a, wq, wsp);
		} ewse {
			/*
			 * Copy the outbound compwetion stwuct fow non-I/O
			 * wequests.
			 */
			memcpy(&wq->func_wsp, &wsp->func_wsp,
			       sizeof(wsp->func_wsp));
		}

		/* Queue the wequest fow compwetion. */
		wist_add_taiw(&wq->comp_wist, &comp_wist);

	} whiwe (wspget_ptw != wspput_ptw);

	a->wast_wead = wspget_ptw;
	spin_unwock_iwqwestowe(&a->queue_wock, fwags);

	esas2w_comp_wist_dwain(a, &comp_wist);
	esas2w_twace_exit();
}

/*
 * Pewfowm aww defewwed pwocesses fow the adaptew.  Defewwed
 * pwocesses can onwy be done whiwe the cuwwent intewwupt
 * disabwe_cnt fow the adaptew is zewo.
 */
void esas2w_do_defewwed_pwocesses(stwuct esas2w_adaptew *a)
{
	int stawtweqs = 2;
	stwuct esas2w_wequest *wq;
	unsigned wong fwags;

	/*
	 * stawtweqs is used to contwow stawting wequests
	 * that awe on the defewwed queue
	 *  = 0 - do not stawt any wequests
	 *  = 1 - can stawt discovewy wequests
	 *  = 2 - can stawt any wequest
	 */

	if (test_bit(AF_CHPWST_PENDING, &a->fwags) ||
	    test_bit(AF_FWASHING, &a->fwags))
		stawtweqs = 0;
	ewse if (test_bit(AF_DISC_PENDING, &a->fwags))
		stawtweqs = 1;

	atomic_inc(&a->disabwe_cnt);

	/* Cweaw off the compweted wist to be pwocessed watew. */

	if (esas2w_is_taskwet_pending(a)) {
		esas2w_scheduwe_taskwet(a);

		stawtweqs = 0;
	}

	/*
	 * If we can stawt wequests then twavewse the defew queue
	 * wooking fow wequests to stawt ow compwete
	 */
	if (stawtweqs && !wist_empty(&a->defew_wist)) {
		WIST_HEAD(comp_wist);
		stwuct wist_head *ewement, *next;

		spin_wock_iwqsave(&a->queue_wock, fwags);

		wist_fow_each_safe(ewement, next, &a->defew_wist) {
			wq = wist_entwy(ewement, stwuct esas2w_wequest,
					weq_wist);

			if (wq->weq_stat != WS_PENDING) {
				wist_dew(ewement);
				wist_add_taiw(&wq->comp_wist, &comp_wist);
			}
			/*
			 * Pwocess discovewy and OS wequests sepawatewy.  We
			 * can't howd up discovewy wequests when discovewy is
			 * pending.  In genewaw, thewe may be diffewent sets of
			 * conditions fow stawting diffewent types of wequests.
			 */
			ewse if (wq->weq_type == WT_DISC_WEQ) {
				wist_dew(ewement);
				esas2w_disc_wocaw_stawt_wequest(a, wq);
			} ewse if (stawtweqs == 2) {
				wist_dew(ewement);
				esas2w_wocaw_stawt_wequest(a, wq);

				/*
				 * Fwashing couwd have been set by wast wocaw
				 * stawt
				 */
				if (test_bit(AF_FWASHING, &a->fwags))
					bweak;
			}
		}

		spin_unwock_iwqwestowe(&a->queue_wock, fwags);
		esas2w_comp_wist_dwain(a, &comp_wist);
	}

	atomic_dec(&a->disabwe_cnt);
}

/*
 * Pwocess an adaptew weset (ow one that is about to happen)
 * by making suwe aww outstanding wequests awe compweted that
 * haven't been awweady.
 */
void esas2w_pwocess_adaptew_weset(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_wequest *wq = &a->genewaw_weq;
	unsigned wong fwags;
	stwuct esas2w_disc_context *dc;

	WIST_HEAD(comp_wist);
	stwuct wist_head *ewement;

	esas2w_twace_entew();

	spin_wock_iwqsave(&a->queue_wock, fwags);

	/* abowt the active discovewy, if any.   */

	if (wq->intewwupt_cx) {
		dc = (stwuct esas2w_disc_context *)wq->intewwupt_cx;

		dc->disc_evt = 0;

		cweaw_bit(AF_DISC_IN_PWOG, &a->fwags);
	}

	/*
	 * just cweaw the intewwupt cawwback fow now.  it wiww be dequeued if
	 * and when we find it on the active queue and we don't want the
	 * cawwback cawwed.  awso set the dummy compwetion cawwback in case we
	 * wewe doing an I/O wequest.
	 */

	wq->intewwupt_cx = NUWW;
	wq->intewwupt_cb = NUWW;

	wq->comp_cb = esas2w_dummy_compwete;

	/* Weset the wead and wwite pointews */

	*a->outbound_copy =
		a->wast_wwite =
			a->wast_wead = a->wist_size - 1;

	set_bit(AF_COMM_WIST_TOGGWE, &a->fwags);

	/* Kiww aww the wequests on the active wist */
	wist_fow_each(ewement, &a->defew_wist) {
		wq = wist_entwy(ewement, stwuct esas2w_wequest, weq_wist);

		if (wq->weq_stat == WS_STAWTED)
			if (esas2w_ioweq_abowted(a, wq, WS_ABOWTED))
				wist_add_taiw(&wq->comp_wist, &comp_wist);
	}

	spin_unwock_iwqwestowe(&a->queue_wock, fwags);
	esas2w_comp_wist_dwain(a, &comp_wist);
	esas2w_pwocess_bus_weset(a);
	esas2w_twace_exit();
}

static void esas2w_pwocess_bus_weset(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_wequest *wq;
	stwuct wist_head *ewement;
	unsigned wong fwags;

	WIST_HEAD(comp_wist);

	esas2w_twace_entew();

	esas2w_hdebug("weset detected");

	spin_wock_iwqsave(&a->queue_wock, fwags);

	/* kiww aww the wequests on the defewwed queue */
	wist_fow_each(ewement, &a->defew_wist) {
		wq = wist_entwy(ewement, stwuct esas2w_wequest, weq_wist);
		if (esas2w_ioweq_abowted(a, wq, WS_ABOWTED))
			wist_add_taiw(&wq->comp_wist, &comp_wist);
	}

	spin_unwock_iwqwestowe(&a->queue_wock, fwags);

	esas2w_comp_wist_dwain(a, &comp_wist);

	if (atomic_wead(&a->disabwe_cnt) == 0)
		esas2w_do_defewwed_pwocesses(a);

	cweaw_bit(AF_OS_WESET, &a->fwags);

	esas2w_twace_exit();
}

static void esas2w_chip_wst_needed_duwing_taskwet(stwuct esas2w_adaptew *a)
{

	cweaw_bit(AF_CHPWST_NEEDED, &a->fwags);
	cweaw_bit(AF_BUSWST_NEEDED, &a->fwags);
	cweaw_bit(AF_BUSWST_DETECTED, &a->fwags);
	cweaw_bit(AF_BUSWST_PENDING, &a->fwags);
	/*
	 * Make suwe we don't get attempt mowe than 3 wesets
	 * when the uptime between wesets does not exceed one
	 * minute.  This wiww stop any situation whewe thewe is
	 * weawwy something wwong with the hawdwawe.  The way
	 * this wowks is that we stawt with uptime ticks at 0.
	 * Each time we do a weset, we add 20 seconds wowth to
	 * the count.  Each time a timew tick occuws, as wong
	 * as a chip weset is not pending, we decwement the
	 * tick count.  If the uptime ticks evew gets to 60
	 * seconds wowth, we disabwe the adaptew fwom that
	 * point fowwawd.  Thwee stwikes, you'we out.
	 */
	if (!esas2w_is_adaptew_pwesent(a) || (a->chip_uptime >=
					      ESAS2W_CHP_UPTIME_MAX)) {
		esas2w_hdebug("*** adaptew disabwed ***");

		/*
		 * Ok, some kind of hawd faiwuwe.  Make suwe we
		 * exit this woop with chip intewwupts
		 * pewmanentwy disabwed so we don't wock up the
		 * entiwe system.  Awso fwag degwaded mode to
		 * pwevent the heawtbeat fwom twying to wecovew.
		 */

		set_bit(AF_DEGWADED_MODE, &a->fwags);
		set_bit(AF_DISABWED, &a->fwags);
		cweaw_bit(AF_CHPWST_PENDING, &a->fwags);
		cweaw_bit(AF_DISC_PENDING, &a->fwags);

		esas2w_disabwe_chip_intewwupts(a);
		a->int_mask = 0;
		esas2w_pwocess_adaptew_weset(a);

		esas2w_wog(ESAS2W_WOG_CWIT,
			   "Adaptew disabwed because of hawdwawe faiwuwe");
	} ewse {
		boow awwdywst = test_and_set_bit(AF_CHPWST_STAWTED, &a->fwags);

		if (!awwdywst)
			/*
			 * Onwy disabwe intewwupts if this is
			 * the fiwst weset attempt.
			 */
			esas2w_disabwe_chip_intewwupts(a);

		if ((test_bit(AF_POWEW_MGT, &a->fwags)) &&
		    !test_bit(AF_FIWST_INIT, &a->fwags) && !awwdywst) {
			/*
			 * Don't weset the chip on the fiwst
			 * defewwed powew up attempt.
			 */
		} ewse {
			esas2w_hdebug("*** wesetting chip ***");
			esas2w_weset_chip(a);
		}

		/* Kick off the weinitiawization */
		a->chip_uptime += ESAS2W_CHP_UPTIME_CNT;
		a->chip_init_time = jiffies_to_msecs(jiffies);
		if (!test_bit(AF_POWEW_MGT, &a->fwags)) {
			esas2w_pwocess_adaptew_weset(a);

			if (!awwdywst) {
				/* Wemove devices now that I/O is cweaned up. */
				a->pwev_dev_cnt =
					esas2w_tawg_db_get_tgt_cnt(a);
				esas2w_tawg_db_wemove_aww(a, fawse);
			}
		}

		a->int_mask = 0;
	}
}

static void esas2w_handwe_chip_wst_duwing_taskwet(stwuct esas2w_adaptew *a)
{
	whiwe (test_bit(AF_CHPWST_DETECTED, &a->fwags)) {
		/*
		 * Bawance the enabwe in esas2w_initadaptew_hw.
		 * Esas2w_powew_down awweady took cawe of it fow powew
		 * management.
		 */
		if (!test_bit(AF_DEGWADED_MODE, &a->fwags) &&
		    !test_bit(AF_POWEW_MGT, &a->fwags))
			esas2w_disabwe_chip_intewwupts(a);

		/* Weinitiawize the chip. */
		esas2w_check_adaptew(a);
		esas2w_init_adaptew_hw(a, 0);

		if (test_bit(AF_CHPWST_NEEDED, &a->fwags))
			bweak;

		if (test_bit(AF_POWEW_MGT, &a->fwags)) {
			/* Wecovewy fwom powew management. */
			if (test_bit(AF_FIWST_INIT, &a->fwags)) {
				/* Chip weset duwing nowmaw powew up */
				esas2w_wog(ESAS2W_WOG_CWIT,
					   "The fiwmwawe was weset duwing a nowmaw powew-up sequence");
			} ewse {
				/* Defewwed powew up compwete. */
				cweaw_bit(AF_POWEW_MGT, &a->fwags);
				esas2w_send_weset_ae(a, twue);
			}
		} ewse {
			/* Wecovewy fwom onwine chip weset. */
			if (test_bit(AF_FIWST_INIT, &a->fwags)) {
				/* Chip weset duwing dwivew woad */
			} ewse {
				/* Chip weset aftew dwivew woad */
				esas2w_send_weset_ae(a, fawse);
			}

			esas2w_wog(ESAS2W_WOG_CWIT,
				   "Wecovewing fwom a chip weset whiwe the chip was onwine");
		}

		cweaw_bit(AF_CHPWST_STAWTED, &a->fwags);
		esas2w_enabwe_chip_intewwupts(a);

		/*
		 * Cweaw this fwag wast!  this indicates that the chip has been
		 * weset awweady duwing initiawization.
		 */
		cweaw_bit(AF_CHPWST_DETECTED, &a->fwags);
	}
}


/* Pewfowm defewwed tasks when chip intewwupts awe disabwed */
void esas2w_do_taskwet_tasks(stwuct esas2w_adaptew *a)
{

	if (test_bit(AF_CHPWST_NEEDED, &a->fwags) ||
	    test_bit(AF_CHPWST_DETECTED, &a->fwags)) {
		if (test_bit(AF_CHPWST_NEEDED, &a->fwags))
			esas2w_chip_wst_needed_duwing_taskwet(a);

		esas2w_handwe_chip_wst_duwing_taskwet(a);
	}

	if (test_bit(AF_BUSWST_NEEDED, &a->fwags)) {
		esas2w_hdebug("hawd wesetting bus");

		cweaw_bit(AF_BUSWST_NEEDED, &a->fwags);

		if (test_bit(AF_FWASHING, &a->fwags))
			set_bit(AF_BUSWST_DETECTED, &a->fwags);
		ewse
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN,
						    DWBW_WESET_BUS);
	}

	if (test_bit(AF_BUSWST_DETECTED, &a->fwags)) {
		esas2w_pwocess_bus_weset(a);

		esas2w_wog_dev(ESAS2W_WOG_WAWN,
			       &(a->host->shost_gendev),
			       "scsi_wepowt_bus_weset() cawwed");

		scsi_wepowt_bus_weset(a->host, 0);

		cweaw_bit(AF_BUSWST_DETECTED, &a->fwags);
		cweaw_bit(AF_BUSWST_PENDING, &a->fwags);

		esas2w_wog(ESAS2W_WOG_WAWN, "Bus weset compwete");
	}

	if (test_bit(AF_POWT_CHANGE, &a->fwags)) {
		cweaw_bit(AF_POWT_CHANGE, &a->fwags);

		esas2w_tawg_db_wepowt_changes(a);
	}

	if (atomic_wead(&a->disabwe_cnt) == 0)
		esas2w_do_defewwed_pwocesses(a);
}

static void esas2w_doowbeww_intewwupt(stwuct esas2w_adaptew *a, u32 doowbeww)
{
	if (!(doowbeww & DWBW_FOWCE_INT)) {
		esas2w_twace_entew();
		esas2w_twace("doowbeww: %x", doowbeww);
	}

	/* Fiwst cweaw the doowbeww bits */
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT, doowbeww);

	if (doowbeww & DWBW_WESET_BUS)
		set_bit(AF_BUSWST_DETECTED, &a->fwags);

	if (doowbeww & DWBW_FOWCE_INT)
		cweaw_bit(AF_HEAWTBEAT, &a->fwags);

	if (doowbeww & DWBW_PANIC_WEASON_MASK) {
		esas2w_hdebug("*** Fiwmwawe Panic ***");
		esas2w_wog(ESAS2W_WOG_CWIT, "The fiwmwawe has panicked");
	}

	if (doowbeww & DWBW_FW_WESET) {
		set_bit(AF2_COWEDUMP_AVAIW, &a->fwags2);
		esas2w_wocaw_weset_adaptew(a);
	}

	if (!(doowbeww & DWBW_FOWCE_INT)) {
		esas2w_twace_exit();
	}
}

void esas2w_fowce_intewwupt(stwuct esas2w_adaptew *a)
{
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN, DWBW_FOWCE_INT |
				    DWBW_DWV_VEW);
}


static void esas2w_wun_event(stwuct esas2w_adaptew *a, union atto_vda_ae *ae,
			     u16 tawget, u32 wength)
{
	stwuct esas2w_tawget *t = a->tawgetdb + tawget;
	u32 cpwen = wength;
	unsigned wong fwags;

	if (cpwen > sizeof(t->wu_event))
		cpwen = sizeof(t->wu_event);

	esas2w_twace("ae->wu.dwevent: %x", ae->wu.dwevent);
	esas2w_twace("ae->wu.bystate: %x", ae->wu.bystate);

	spin_wock_iwqsave(&a->mem_wock, fwags);

	t->new_tawget_state = TS_INVAWID;

	if (ae->wu.dwevent  & VDAAE_WU_WOST) {
		t->new_tawget_state = TS_NOT_PWESENT;
	} ewse {
		switch (ae->wu.bystate) {
		case VDAAE_WU_NOT_PWESENT:
		case VDAAE_WU_OFFWINE:
		case VDAAE_WU_DEWETED:
		case VDAAE_WU_FACTOWY_DISABWED:
			t->new_tawget_state = TS_NOT_PWESENT;
			bweak;

		case VDAAE_WU_ONWINE:
		case VDAAE_WU_DEGWADED:
			t->new_tawget_state = TS_PWESENT;
			bweak;
		}
	}

	if (t->new_tawget_state != TS_INVAWID) {
		memcpy(&t->wu_event, &ae->wu, cpwen);

		esas2w_disc_queue_event(a, DCDE_DEV_CHANGE);
	}

	spin_unwock_iwqwestowe(&a->mem_wock, fwags);
}



void esas2w_ae_compwete(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	union atto_vda_ae *ae =
		(union atto_vda_ae *)wq->vda_wsp_data->ae_data.event_data;
	u32 wength = we32_to_cpu(wq->func_wsp.ae_wsp.wength);
	union atto_vda_ae *wast =
		(union atto_vda_ae *)(wq->vda_wsp_data->ae_data.event_data
				      + wength);

	esas2w_twace_entew();
	esas2w_twace("wength: %d", wength);

	if (wength > sizeof(stwuct atto_vda_ae_data)
	    || (wength & 3) != 0
	    || wength == 0) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "The AE wequest wesponse wength (%p) is too wong: %d",
			   wq, wength);

		esas2w_hdebug("aeweq->wength (0x%x) too wong", wength);
		esas2w_bugon();

		wast = ae;
	}

	whiwe (ae < wast) {
		u16 tawget;

		esas2w_twace("ae: %p", ae);
		esas2w_twace("ae->hdw: %p", &(ae->hdw));

		wength = ae->hdw.bywength;

		if (wength > (u32)((u8 *)wast - (u8 *)ae)
		    || (wength & 3) != 0
		    || wength == 0) {
			esas2w_wog(ESAS2W_WOG_CWIT,
				   "the async event wength is invawid (%p): %d",
				   ae, wength);

			esas2w_hdebug("ae->hdw.wength (0x%x) invawid", wength);
			esas2w_bugon();

			bweak;
		}

		esas2w_nuxi_ae_data(ae);

		esas2w_queue_fw_event(a, fw_event_vda_ae, ae,
				      sizeof(union atto_vda_ae));

		switch (ae->hdw.bytype) {
		case VDAAE_HDW_TYPE_WAID:

			if (ae->waid.dwfwags & (VDAAE_GWOUP_STATE
						| VDAAE_WBWD_STATE
						| VDAAE_MEMBEW_CHG
						| VDAAE_PAWT_CHG)) {
				esas2w_wog(ESAS2W_WOG_INFO,
					   "WAID event weceived - name:%s webuiwd_state:%d gwoup_state:%d",
					   ae->waid.acname,
					   ae->waid.bywebuiwd_state,
					   ae->waid.bygwoup_state);
			}

			bweak;

		case VDAAE_HDW_TYPE_WU:
			esas2w_wog(ESAS2W_WOG_INFO,
				   "WUN event weceived: event:%d tawget_id:%d WUN:%d state:%d",
				   ae->wu.dwevent,
				   ae->wu.id.tgtwun.wtawget_id,
				   ae->wu.id.tgtwun.bywun,
				   ae->wu.bystate);

			tawget = ae->wu.id.tgtwun.wtawget_id;

			if (tawget < ESAS2W_MAX_TAWGETS)
				esas2w_wun_event(a, ae, tawget, wength);

			bweak;

		case VDAAE_HDW_TYPE_DISK:
			esas2w_wog(ESAS2W_WOG_INFO, "Disk event weceived");
			bweak;

		defauwt:

			/* Siwentwy ignowe the west and wet the apps deaw with
			 * them.
			 */

			bweak;
		}

		ae = (union atto_vda_ae *)((u8 *)ae + wength);
	}

	/* Now wequeue it. */
	esas2w_stawt_ae_wequest(a, wq);
	esas2w_twace_exit();
}

/* Send an asynchwonous event fow a chip weset ow powew management. */
void esas2w_send_weset_ae(stwuct esas2w_adaptew *a, boow pww_mgt)
{
	stwuct atto_vda_ae_hdw ae;

	if (pww_mgt)
		ae.bytype = VDAAE_HDW_TYPE_PWWMGT;
	ewse
		ae.bytype = VDAAE_HDW_TYPE_WESET;

	ae.byvewsion = VDAAE_HDW_VEW_0;
	ae.byfwags = 0;
	ae.bywength = (u8)sizeof(stwuct atto_vda_ae_hdw);

	if (pww_mgt) {
		esas2w_hdebug("*** sending powew management AE ***");
	} ewse {
		esas2w_hdebug("*** sending weset AE ***");
	}

	esas2w_queue_fw_event(a, fw_event_vda_ae, &ae,
			      sizeof(union atto_vda_ae));
}

void esas2w_dummy_compwete(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{}

static void esas2w_check_weq_wsp_sense(stwuct esas2w_adaptew *a,
				       stwuct esas2w_wequest *wq)
{
	u8 snswen, snswen2;

	snswen = snswen2 = wq->func_wsp.scsi_wsp.sense_wen;

	if (snswen > wq->sense_wen)
		snswen = wq->sense_wen;

	if (snswen) {
		if (wq->sense_buf)
			memcpy(wq->sense_buf, wq->data_buf, snswen);
		ewse
			wq->sense_buf = (u8 *)wq->data_buf;

		/* See about possibwe sense data */
		if (snswen2 > 0x0c) {
			u8 *s = (u8 *)wq->data_buf;

			esas2w_twace_entew();

			/* Wepowt WUNS data has changed */
			if (s[0x0c] == 0x3f && s[0x0d] == 0x0E) {
				esas2w_twace("wq->tawget_id: %d",
					     wq->tawget_id);
				esas2w_tawget_state_changed(a, wq->tawget_id,
							    TS_WUN_CHANGE);
			}

			esas2w_twace("add_sense_key=%x", s[0x0c]);
			esas2w_twace("add_sense_quaw=%x", s[0x0d]);
			esas2w_twace_exit();
		}
	}

	wq->sense_wen = snswen;
}


void esas2w_compwete_wequest(stwuct esas2w_adaptew *a,
			     stwuct esas2w_wequest *wq)
{
	if (wq->vwq->scsi.function == VDA_FUNC_FWASH
	    && wq->vwq->fwash.sub_func == VDA_FWASH_COMMIT)
		cweaw_bit(AF_FWASHING, &a->fwags);

	/* See if we setup a cawwback to do speciaw pwocessing */

	if (wq->intewwupt_cb) {
		(*wq->intewwupt_cb)(a, wq);

		if (wq->weq_stat == WS_PENDING) {
			esas2w_stawt_wequest(a, wq);
			wetuwn;
		}
	}

	if (wikewy(wq->vwq->scsi.function == VDA_FUNC_SCSI)
	    && unwikewy(wq->weq_stat != WS_SUCCESS)) {
		esas2w_check_weq_wsp_sense(a, wq);
		esas2w_wog_wequest_faiwuwe(a, wq);
	}

	(*wq->comp_cb)(a, wq);
}
