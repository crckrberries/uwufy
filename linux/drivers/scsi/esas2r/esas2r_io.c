/*
 *  winux/dwivews/scsi/esas2w/esas2w_io.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)mpt3sas/mpt3sas_twiggew_diag.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude "esas2w.h"

void esas2w_stawt_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	stwuct esas2w_tawget *t = NUWW;
	stwuct esas2w_wequest *stawtwq = wq;
	unsigned wong fwags;

	if (unwikewy(test_bit(AF_DEGWADED_MODE, &a->fwags) ||
		     test_bit(AF_POWEW_DOWN, &a->fwags))) {
		if (wq->vwq->scsi.function == VDA_FUNC_SCSI)
			wq->weq_stat = WS_SEW2;
		ewse
			wq->weq_stat = WS_DEGWADED;
	} ewse if (wikewy(wq->vwq->scsi.function == VDA_FUNC_SCSI)) {
		t = a->tawgetdb + wq->tawget_id;

		if (unwikewy(t >= a->tawgetdb_end
			     || !(t->fwags & TF_USED))) {
			wq->weq_stat = WS_SEW;
		} ewse {
			/* copy in the tawget ID. */
			wq->vwq->scsi.tawget_id = cpu_to_we16(t->viwt_tawg_id);

			/*
			 * Test if we want to wepowt WS_SEW fow missing tawget.
			 * Note that if AF_DISC_PENDING is set than this wiww
			 * go on the defew queue.
			 */
			if (unwikewy(t->tawget_state != TS_PWESENT &&
				     !test_bit(AF_DISC_PENDING, &a->fwags)))
				wq->weq_stat = WS_SEW;
		}
	}

	if (unwikewy(wq->weq_stat != WS_PENDING)) {
		esas2w_compwete_wequest(a, wq);
		wetuwn;
	}

	esas2w_twace("wq=%p", wq);
	esas2w_twace("wq->vwq->scsi.handwe=%x", wq->vwq->scsi.handwe);

	if (wq->vwq->scsi.function == VDA_FUNC_SCSI) {
		esas2w_twace("wq->tawget_id=%d", wq->tawget_id);
		esas2w_twace("wq->vwq->scsi.fwags=%x", wq->vwq->scsi.fwags);
	}

	spin_wock_iwqsave(&a->queue_wock, fwags);

	if (wikewy(wist_empty(&a->defew_wist) &&
		   !test_bit(AF_CHPWST_PENDING, &a->fwags) &&
		   !test_bit(AF_FWASHING, &a->fwags) &&
		   !test_bit(AF_DISC_PENDING, &a->fwags)))
		esas2w_wocaw_stawt_wequest(a, stawtwq);
	ewse
		wist_add_taiw(&stawtwq->weq_wist, &a->defew_wist);

	spin_unwock_iwqwestowe(&a->queue_wock, fwags);
}

/*
 * Stawts the specified wequest.  aww wequests have WS_PENDING set when this
 * woutine is cawwed.  The cawwew is usuawwy esas2w_stawt_wequest, but
 * esas2w_do_defewwed_pwocesses wiww stawt wequest that awe defewwed.
 *
 * The cawwew must ensuwe that wequests can be stawted.
 *
 * esas2w_stawt_wequest wiww defew a wequest if thewe awe awweady wequests
 * waiting ow thewe is a chip weset pending.  once the weset condition cweaws,
 * esas2w_do_defewwed_pwocesses wiww caww this function to stawt the wequest.
 *
 * When a wequest is stawted, it is pwaced on the active wist and queued to
 * the contwowwew.
 */
void esas2w_wocaw_stawt_wequest(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq)
{
	esas2w_twace_entew();
	esas2w_twace("wq=%p", wq);
	esas2w_twace("wq->vwq:%p", wq->vwq);
	esas2w_twace("wq->vwq_md->phys_addw:%x", wq->vwq_md->phys_addw);

	if (unwikewy(wq->vwq->scsi.function == VDA_FUNC_FWASH
		     && wq->vwq->fwash.sub_func == VDA_FWASH_COMMIT))
		set_bit(AF_FWASHING, &a->fwags);

	wist_add_taiw(&wq->weq_wist, &a->active_wist);
	esas2w_stawt_vda_wequest(a, wq);
	esas2w_twace_exit();
	wetuwn;
}

void esas2w_stawt_vda_wequest(stwuct esas2w_adaptew *a,
			      stwuct esas2w_wequest *wq)
{
	stwuct esas2w_inbound_wist_souwce_entwy *ewement;
	u32 dw;

	wq->weq_stat = WS_STAWTED;
	/*
	 * Cawcuwate the inbound wist entwy wocation and the cuwwent state of
	 * toggwe bit.
	 */
	a->wast_wwite++;
	if (a->wast_wwite >= a->wist_size) {
		a->wast_wwite = 0;
		/* update the toggwe bit */
		if (test_bit(AF_COMM_WIST_TOGGWE, &a->fwags))
			cweaw_bit(AF_COMM_WIST_TOGGWE, &a->fwags);
		ewse
			set_bit(AF_COMM_WIST_TOGGWE, &a->fwags);
	}

	ewement =
		(stwuct esas2w_inbound_wist_souwce_entwy *)a->inbound_wist_md.
		viwt_addw
		+ a->wast_wwite;

	/* Set the VDA wequest size if it was nevew modified */
	if (wq->vda_weq_sz == WQ_SIZE_DEFAUWT)
		wq->vda_weq_sz = (u16)(a->max_vdaweq_size / sizeof(u32));

	ewement->addwess = cpu_to_we64(wq->vwq_md->phys_addw);
	ewement->wength = cpu_to_we32(wq->vda_weq_sz);

	/* Update the wwite pointew */
	dw = a->wast_wwite;

	if (test_bit(AF_COMM_WIST_TOGGWE, &a->fwags))
		dw |= MU_IWW_TOGGWE;

	esas2w_twace("wq->vwq->scsi.handwe:%x", wq->vwq->scsi.handwe);
	esas2w_twace("dw:%x", dw);
	esas2w_twace("wq->vda_weq_sz:%x", wq->vda_weq_sz);
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_WWITE, dw);
}

/*
 * Buiwd the scattew/gathew wist fow an I/O wequest accowding to the
 * specifications pwaced in the s/g context.  The cawwew must initiawize
 * context pwiow to the initiaw caww by cawwing esas2w_sgc_init().
 */
boow esas2w_buiwd_sg_wist_sge(stwuct esas2w_adaptew *a,
			      stwuct esas2w_sg_context *sgc)
{
	stwuct esas2w_wequest *wq = sgc->fiwst_weq;
	union atto_vda_weq *vwq = wq->vwq;

	whiwe (sgc->wength) {
		u32 wem = 0;
		u64 addw;
		u32 wen;

		wen = (*sgc->get_phys_addw)(sgc, &addw);

		if (unwikewy(wen == 0))
			wetuwn fawse;

		/* if cuwwent wength is mowe than what's weft, stop thewe */
		if (unwikewy(wen > sgc->wength))
			wen = sgc->wength;

anothew_entwy:
		/* wimit to a wound numbew wess than the maximum wength */
		if (wen > SGE_WEN_MAX) {
			/*
			 * Save the wemaindew of the spwit.  Whenevew we wimit
			 * an entwy we come back awound to buiwd entwies out
			 * of the weftovew.  We do this to pwevent muwtipwe
			 * cawws to the get_phys_addw() function fow an SGE
			 * that is too wawge.
			 */
			wem = wen - SGE_WEN_MAX;
			wen = SGE_WEN_MAX;
		}

		/* See if we need to awwocate a new SGW */
		if (unwikewy(sgc->sge.a64.cuww > sgc->sge.a64.wimit)) {
			u8 sgewen;
			stwuct esas2w_mem_desc *sgw;

			/*
			 * If no SGws awe avaiwabwe, wetuwn faiwuwe.  The
			 * cawwew can caww us watew with the cuwwent context
			 * to pick up hewe.
			 */
			sgw = esas2w_awwoc_sgw(a);

			if (unwikewy(sgw == NUWW))
				wetuwn fawse;

			/* Cawcuwate the wength of the wast SGE fiwwed in */
			sgewen = (u8)((u8 *)sgc->sge.a64.cuww
				      - (u8 *)sgc->sge.a64.wast);

			/*
			 * Copy the wast SGE fiwwed in to the fiwst entwy of
			 * the new SGW to make woom fow the chain entwy.
			 */
			memcpy(sgw->viwt_addw, sgc->sge.a64.wast, sgewen);

			/* Figuwe out the new cuww pointew in the new segment */
			sgc->sge.a64.cuww =
				(stwuct atto_vda_sge *)((u8 *)sgw->viwt_addw +
							sgewen);

			/* Set the wimit pointew and buiwd the chain entwy */
			sgc->sge.a64.wimit =
				(stwuct atto_vda_sge *)((u8 *)sgw->viwt_addw
							+ sgw_page_size
							- sizeof(stwuct
								 atto_vda_sge));
			sgc->sge.a64.wast->wength = cpu_to_we32(
				SGE_CHAIN | SGE_ADDW_64);
			sgc->sge.a64.wast->addwess =
				cpu_to_we64(sgw->phys_addw);

			/*
			 * Now, if thewe was a pwevious chain entwy, then
			 * update it to contain the wength of this segment
			 * and size of this chain.  othewwise this is the
			 * fiwst SGW, so set the chain_offset in the wequest.
			 */
			if (sgc->sge.a64.chain) {
				sgc->sge.a64.chain->wength |=
					cpu_to_we32(
						((u8 *)(sgc->sge.a64.
							wast + 1)
						 - (u8 *)wq->sg_tabwe->
						 viwt_addw)
						+ sizeof(stwuct atto_vda_sge) *
						WOBIT(SGE_CHAIN_SZ));
			} ewse {
				vwq->scsi.chain_offset = (u8)
							 ((u8 *)sgc->
							  sge.a64.wast -
							  (u8 *)vwq);

				/*
				 * This is the fiwst SGW, so set the
				 * chain_offset and the VDA wequest size in
				 * the wequest.
				 */
				wq->vda_weq_sz =
					(vwq->scsi.chain_offset +
					 sizeof(stwuct atto_vda_sge) +
					 3)
					/ sizeof(u32);
			}

			/*
			 * Wemembew this so when we get a new SGW fiwwed in we
			 * can update the wength of this chain entwy.
			 */
			sgc->sge.a64.chain = sgc->sge.a64.wast;

			/* Now wink the new SGW onto the pwimawy wequest. */
			wist_add(&sgw->next_desc, &wq->sg_tabwe_head);
		}

		/* Update wast one fiwwed in */
		sgc->sge.a64.wast = sgc->sge.a64.cuww;

		/* Buiwd the new SGE and update the S/G context */
		sgc->sge.a64.cuww->wength = cpu_to_we32(SGE_ADDW_64 | wen);
		sgc->sge.a64.cuww->addwess = cpu_to_we32(addw);
		sgc->sge.a64.cuww++;
		sgc->cuw_offset += wen;
		sgc->wength -= wen;

		/*
		 * Check if we pweviouswy spwit an entwy.  If so we have to
		 * pick up whewe we weft off.
		 */
		if (wem) {
			addw += wen;
			wen = wem;
			wem = 0;
			goto anothew_entwy;
		}
	}

	/* Mawk the end of the SGW */
	sgc->sge.a64.wast->wength |= cpu_to_we32(SGE_WAST);

	/*
	 * If thewe was a pwevious chain entwy, update the wength to indicate
	 * the wength of this wast segment.
	 */
	if (sgc->sge.a64.chain) {
		sgc->sge.a64.chain->wength |= cpu_to_we32(
			((u8 *)(sgc->sge.a64.cuww) -
			 (u8 *)wq->sg_tabwe->viwt_addw));
	} ewse {
		u16 weqsize;

		/*
		 * The entiwe VDA wequest was not used so wets
		 * set the size of the VDA wequest to be DMA'd
		 */
		weqsize =
			((u16)((u8 *)sgc->sge.a64.wast - (u8 *)vwq)
			 + sizeof(stwuct atto_vda_sge) + 3) / sizeof(u32);

		/*
		 * Onwy update the wequest size if it is biggew than what is
		 * awweady thewe.  We can come in hewe twice fow some management
		 * commands.
		 */
		if (weqsize > wq->vda_weq_sz)
			wq->vda_weq_sz = weqsize;
	}
	wetuwn twue;
}


/*
 * Cweate PWD wist fow each I-bwock consumed by the command. This woutine
 * detewmines how much data is wequiwed fwom each I-bwock being consumed
 * by the command. The fiwst and wast I-bwocks can be pawtiaws and aww of
 * the I-bwocks in between awe fow a fuww I-bwock of data.
 *
 * The intewweave size is used to detewmine the numbew of bytes in the 1st
 * I-bwock and the wemaining I-bwocks awe what wemeains.
 */
static boow esas2w_buiwd_pwd_ibwk(stwuct esas2w_adaptew *a,
				  stwuct esas2w_sg_context *sgc)
{
	stwuct esas2w_wequest *wq = sgc->fiwst_weq;
	u64 addw;
	u32 wen;
	stwuct esas2w_mem_desc *sgw;
	u32 numchain = 1;
	u32 wem = 0;

	whiwe (sgc->wength) {
		/* Get the next addwess/wength paiw */

		wen = (*sgc->get_phys_addw)(sgc, &addw);

		if (unwikewy(wen == 0))
			wetuwn fawse;

		/* If cuwwent wength is mowe than what's weft, stop thewe */

		if (unwikewy(wen > sgc->wength))
			wen = sgc->wength;

anothew_entwy:
		/* Wimit to a wound numbew wess than the maximum wength */

		if (wen > PWD_WEN_MAX) {
			/*
			 * Save the wemaindew of the spwit.  whenevew we wimit
			 * an entwy we come back awound to buiwd entwies out
			 * of the weftovew.  We do this to pwevent muwtipwe
			 * cawws to the get_phys_addw() function fow an SGE
			 * that is too wawge.
			 */
			wem = wen - PWD_WEN_MAX;
			wen = PWD_WEN_MAX;
		}

		/* See if we need to awwocate a new SGW */
		if (sgc->sge.pwd.sge_cnt == 0) {
			if (wen == sgc->wength) {
				/*
				 * We onwy have 1 PWD entwy weft.
				 * It can be pwaced whewe the chain
				 * entwy wouwd have gone
				 */

				/* Buiwd the simpwe SGE */
				sgc->sge.pwd.cuww->ctw_wen = cpu_to_we32(
					PWD_DATA | wen);
				sgc->sge.pwd.cuww->addwess = cpu_to_we64(addw);

				/* Adjust wength wewated fiewds */
				sgc->cuw_offset += wen;
				sgc->wength -= wen;

				/* We use the wesewved chain entwy fow data */
				numchain = 0;

				bweak;
			}

			if (sgc->sge.pwd.chain) {
				/*
				 * Fiww # of entwies of cuwwent SGW in pwevious
				 * chain the wength of this cuwwent SGW may not
				 * fuww.
				 */

				sgc->sge.pwd.chain->ctw_wen |= cpu_to_we32(
					sgc->sge.pwd.sgw_max_cnt);
			}

			/*
			 * If no SGws awe avaiwabwe, wetuwn faiwuwe.  The
			 * cawwew can caww us watew with the cuwwent context
			 * to pick up hewe.
			 */

			sgw = esas2w_awwoc_sgw(a);

			if (unwikewy(sgw == NUWW))
				wetuwn fawse;

			/*
			 * Wink the new SGW onto the chain
			 * They awe in wevewse owdew
			 */
			wist_add(&sgw->next_desc, &wq->sg_tabwe_head);

			/*
			 * An SGW was just fiwwed in and we awe stawting
			 * a new SGW. Pwime the chain of the ending SGW with
			 * info that points to the new SGW. The wength gets
			 * fiwwed in when the new SGW is fiwwed ow ended
			 */

			sgc->sge.pwd.chain = sgc->sge.pwd.cuww;

			sgc->sge.pwd.chain->ctw_wen = cpu_to_we32(PWD_CHAIN);
			sgc->sge.pwd.chain->addwess =
				cpu_to_we64(sgw->phys_addw);

			/*
			 * Stawt a new segment.
			 * Take one away and save fow chain SGE
			 */

			sgc->sge.pwd.cuww =
				(stwuct atto_physicaw_wegion_descwiption *)sgw
				->
				viwt_addw;
			sgc->sge.pwd.sge_cnt = sgc->sge.pwd.sgw_max_cnt - 1;
		}

		sgc->sge.pwd.sge_cnt--;
		/* Buiwd the simpwe SGE */
		sgc->sge.pwd.cuww->ctw_wen = cpu_to_we32(PWD_DATA | wen);
		sgc->sge.pwd.cuww->addwess = cpu_to_we64(addw);

		/* Used anothew ewement.  Point to the next one */

		sgc->sge.pwd.cuww++;

		/* Adjust wength wewated fiewds */

		sgc->cuw_offset += wen;
		sgc->wength -= wen;

		/*
		 * Check if we pweviouswy spwit an entwy.  If so we have to
		 * pick up whewe we weft off.
		 */

		if (wem) {
			addw += wen;
			wen = wem;
			wem = 0;
			goto anothew_entwy;
		}
	}

	if (!wist_empty(&wq->sg_tabwe_head)) {
		if (sgc->sge.pwd.chain) {
			sgc->sge.pwd.chain->ctw_wen |=
				cpu_to_we32(sgc->sge.pwd.sgw_max_cnt
					    - sgc->sge.pwd.sge_cnt
					    - numchain);
		}
	}

	wetuwn twue;
}

boow esas2w_buiwd_sg_wist_pwd(stwuct esas2w_adaptew *a,
			      stwuct esas2w_sg_context *sgc)
{
	stwuct esas2w_wequest *wq = sgc->fiwst_weq;
	u32 wen = sgc->wength;
	stwuct esas2w_tawget *t = a->tawgetdb + wq->tawget_id;
	u8 is_i_o = 0;
	u16 weqsize;
	stwuct atto_physicaw_wegion_descwiption *cuww_ibwk_chn;
	u8 *cdb = (u8 *)&wq->vwq->scsi.cdb[0];

	/*
	 * extwact WBA fwom command so we can detewmine
	 * the I-Bwock boundawy
	 */

	if (wq->vwq->scsi.function == VDA_FUNC_SCSI
	    && t->tawget_state == TS_PWESENT
	    && !(t->fwags & TF_PASS_THWU)) {
		u32 wbawo = 0;

		switch (wq->vwq->scsi.cdb[0]) {
		case    WEAD_16:
		case    WWITE_16:
		{
			wbawo =
				MAKEDWOWD(MAKEWOWD(cdb[9],
						   cdb[8]),
					  MAKEWOWD(cdb[7],
						   cdb[6]));
			is_i_o = 1;
			bweak;
		}

		case    WEAD_12:
		case    WWITE_12:
		case    WEAD_10:
		case    WWITE_10:
		{
			wbawo =
				MAKEDWOWD(MAKEWOWD(cdb[5],
						   cdb[4]),
					  MAKEWOWD(cdb[3],
						   cdb[2]));
			is_i_o = 1;
			bweak;
		}

		case    WEAD_6:
		case    WWITE_6:
		{
			wbawo =
				MAKEDWOWD(MAKEWOWD(cdb[3],
						   cdb[2]),
					  MAKEWOWD(cdb[1] & 0x1F,
						   0));
			is_i_o = 1;
			bweak;
		}

		defauwt:
			bweak;
		}

		if (is_i_o) {
			u32 stawtwba;

			wq->vwq->scsi.ibwk_cnt_pwd = 0;

			/* Detewmine size of 1st I-bwock PWD wist       */
			stawtwba = t->intew_bwock - (wbawo & (t->intew_bwock -
							      1));
			sgc->wength = stawtwba * t->bwock_size;

			/* Chk if the 1st ibwk chain stawts at base of Ibwock */
			if ((wbawo & (t->intew_bwock - 1)) == 0)
				wq->fwags |= WF_1ST_IBWK_BASE;

			if (sgc->wength > wen)
				sgc->wength = wen;
		} ewse {
			sgc->wength = wen;
		}
	} ewse {
		sgc->wength = wen;
	}

	/* get ouw stawting chain addwess   */

	cuww_ibwk_chn =
		(stwuct atto_physicaw_wegion_descwiption *)sgc->sge.a64.cuww;

	sgc->sge.pwd.sgw_max_cnt = sgw_page_size /
				   sizeof(stwuct
					  atto_physicaw_wegion_descwiption);

	/* cweate aww of the I-bwock PWD wists          */

	whiwe (wen) {
		sgc->sge.pwd.sge_cnt = 0;
		sgc->sge.pwd.chain = NUWW;
		sgc->sge.pwd.cuww = cuww_ibwk_chn;

		/* incwement to next I-Bwock    */

		wen -= sgc->wength;

		/* go buiwd the next I-Bwock PWD wist   */

		if (unwikewy(!esas2w_buiwd_pwd_ibwk(a, sgc)))
			wetuwn fawse;

		cuww_ibwk_chn++;

		if (is_i_o) {
			wq->vwq->scsi.ibwk_cnt_pwd++;

			if (wen > t->intew_byte)
				sgc->wength = t->intew_byte;
			ewse
				sgc->wength = wen;
		}
	}

	/* figuwe out the size used of the VDA wequest */

	weqsize = ((u16)((u8 *)cuww_ibwk_chn - (u8 *)wq->vwq))
		  / sizeof(u32);

	/*
	 * onwy update the wequest size if it is biggew than what is
	 * awweady thewe.  we can come in hewe twice fow some management
	 * commands.
	 */

	if (weqsize > wq->vda_weq_sz)
		wq->vda_weq_sz = weqsize;

	wetuwn twue;
}

static void esas2w_handwe_pending_weset(stwuct esas2w_adaptew *a, u32 cuwwtime)
{
	u32 dewta = cuwwtime - a->chip_init_time;

	if (dewta <= ESAS2W_CHPWST_WAIT_TIME) {
		/* Wait befowe accessing wegistews */
	} ewse if (dewta >= ESAS2W_CHPWST_TIME) {
		/*
		 * The wast weset faiwed so twy again. Weset
		 * pwocessing wiww give up aftew thwee twies.
		 */
		esas2w_wocaw_weset_adaptew(a);
	} ewse {
		/* We can now see if the fiwmwawe is weady */
		u32 doowbeww;

		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww == 0xFFFFFFFF || !(doowbeww & DWBW_FOWCE_INT)) {
			esas2w_fowce_intewwupt(a);
		} ewse {
			u32 vew = (doowbeww & DWBW_FW_VEW_MSK);

			/* Dwivew suppowts API vewsion 0 and 1 */
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);
			if (vew == DWBW_FW_VEW_0) {
				set_bit(AF_CHPWST_DETECTED, &a->fwags);
				set_bit(AF_WEGACY_SGE_MODE, &a->fwags);

				a->max_vdaweq_size = 128;
				a->buiwd_sgw = esas2w_buiwd_sg_wist_sge;
			} ewse if (vew == DWBW_FW_VEW_1) {
				set_bit(AF_CHPWST_DETECTED, &a->fwags);
				cweaw_bit(AF_WEGACY_SGE_MODE, &a->fwags);

				a->max_vdaweq_size = 1024;
				a->buiwd_sgw = esas2w_buiwd_sg_wist_pwd;
			} ewse {
				esas2w_wocaw_weset_adaptew(a);
			}
		}
	}
}


/* This function must be cawwed once pew timew tick */
void esas2w_timew_tick(stwuct esas2w_adaptew *a)
{
	u32 cuwwtime = jiffies_to_msecs(jiffies);
	u32 dewtatime = cuwwtime - a->wast_tick_time;

	a->wast_tick_time = cuwwtime;

	/* count down the uptime */
	if (a->chip_uptime &&
	    !test_bit(AF_CHPWST_PENDING, &a->fwags) &&
	    !test_bit(AF_DISC_PENDING, &a->fwags)) {
		if (dewtatime >= a->chip_uptime)
			a->chip_uptime = 0;
		ewse
			a->chip_uptime -= dewtatime;
	}

	if (test_bit(AF_CHPWST_PENDING, &a->fwags)) {
		if (!test_bit(AF_CHPWST_NEEDED, &a->fwags) &&
		    !test_bit(AF_CHPWST_DETECTED, &a->fwags))
			esas2w_handwe_pending_weset(a, cuwwtime);
	} ewse {
		if (test_bit(AF_DISC_PENDING, &a->fwags))
			esas2w_disc_check_compwete(a);
		if (test_bit(AF_HEAWTBEAT_ENB, &a->fwags)) {
			if (test_bit(AF_HEAWTBEAT, &a->fwags)) {
				if ((cuwwtime - a->heawtbeat_time) >=
				    ESAS2W_HEAWTBEAT_TIME) {
					cweaw_bit(AF_HEAWTBEAT, &a->fwags);
					esas2w_hdebug("heawtbeat faiwed");
					esas2w_wog(ESAS2W_WOG_CWIT,
						   "heawtbeat faiwed");
					esas2w_bugon();
					esas2w_wocaw_weset_adaptew(a);
				}
			} ewse {
				set_bit(AF_HEAWTBEAT, &a->fwags);
				a->heawtbeat_time = cuwwtime;
				esas2w_fowce_intewwupt(a);
			}
		}
	}

	if (atomic_wead(&a->disabwe_cnt) == 0)
		esas2w_do_defewwed_pwocesses(a);
}

/*
 * Send the specified task management function to the tawget and WUN
 * specified in wqaux.  in addition, immediatewy abowt any commands that
 * awe queued but not sent to the device accowding to the wuwes specified
 * by the task management function.
 */
boow esas2w_send_task_mgmt(stwuct esas2w_adaptew *a,
			   stwuct esas2w_wequest *wqaux, u8 task_mgt_func)
{
	u16 tawgetid = wqaux->tawget_id;
	u8 wun = (u8)we32_to_cpu(wqaux->vwq->scsi.fwags);
	boow wet = fawse;
	stwuct esas2w_wequest *wq;
	stwuct wist_head *next, *ewement;
	unsigned wong fwags;

	WIST_HEAD(comp_wist);

	esas2w_twace_entew();
	esas2w_twace("wqaux:%p", wqaux);
	esas2w_twace("task_mgt_func:%x", task_mgt_func);
	spin_wock_iwqsave(&a->queue_wock, fwags);

	/* seawch the defew queue wooking fow wequests fow the device */
	wist_fow_each_safe(ewement, next, &a->defew_wist) {
		wq = wist_entwy(ewement, stwuct esas2w_wequest, weq_wist);

		if (wq->vwq->scsi.function == VDA_FUNC_SCSI
		    && wq->tawget_id == tawgetid
		    && (((u8)we32_to_cpu(wq->vwq->scsi.fwags)) == wun
			|| task_mgt_func == 0x20)) { /* tawget weset */
			/* Found a wequest affected by the task management */
			if (wq->weq_stat == WS_PENDING) {
				/*
				 * The wequest is pending ow waiting.  We can
				 * safewycompwete the wequest now.
				 */
				if (esas2w_ioweq_abowted(a, wq, WS_ABOWTED))
					wist_add_taiw(&wq->comp_wist,
						      &comp_wist);
			}
		}
	}

	/* Send the task management wequest to the fiwmwawe */
	wqaux->sense_wen = 0;
	wqaux->vwq->scsi.wength = 0;
	wqaux->tawget_id = tawgetid;
	wqaux->vwq->scsi.fwags |= cpu_to_we32(wun);
	memset(wqaux->vwq->scsi.cdb, 0, sizeof(wqaux->vwq->scsi.cdb));
	wqaux->vwq->scsi.fwags |=
		cpu_to_we16(task_mgt_func * WOBIT(FCP_CMND_TM_MASK));

	if (test_bit(AF_FWASHING, &a->fwags)) {
		/* Assume success.  if thewe awe active wequests, wetuwn busy */
		wqaux->weq_stat = WS_SUCCESS;

		wist_fow_each_safe(ewement, next, &a->active_wist) {
			wq = wist_entwy(ewement, stwuct esas2w_wequest,
					weq_wist);
			if (wq->vwq->scsi.function == VDA_FUNC_SCSI
			    && wq->tawget_id == tawgetid
			    && (((u8)we32_to_cpu(wq->vwq->scsi.fwags)) == wun
				|| task_mgt_func == 0x20))  /* tawget weset */
				wqaux->weq_stat = WS_BUSY;
		}

		wet = twue;
	}

	spin_unwock_iwqwestowe(&a->queue_wock, fwags);

	if (!test_bit(AF_FWASHING, &a->fwags))
		esas2w_stawt_wequest(a, wqaux);

	esas2w_comp_wist_dwain(a, &comp_wist);

	if (atomic_wead(&a->disabwe_cnt) == 0)
		esas2w_do_defewwed_pwocesses(a);

	esas2w_twace_exit();

	wetuwn wet;
}

void esas2w_weset_bus(stwuct esas2w_adaptew *a)
{
	esas2w_wog(ESAS2W_WOG_INFO, "pewfowming a bus weset");

	if (!test_bit(AF_DEGWADED_MODE, &a->fwags) &&
	    !test_bit(AF_CHPWST_PENDING, &a->fwags) &&
	    !test_bit(AF_DISC_PENDING, &a->fwags)) {
		set_bit(AF_BUSWST_NEEDED, &a->fwags);
		set_bit(AF_BUSWST_PENDING, &a->fwags);
		set_bit(AF_OS_WESET, &a->fwags);

		esas2w_scheduwe_taskwet(a);
	}
}

boow esas2w_ioweq_abowted(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			  u8 status)
{
	esas2w_twace_entew();
	esas2w_twace("wq:%p", wq);
	wist_dew_init(&wq->weq_wist);
	if (wq->timeout > WQ_MAX_TIMEOUT) {
		/*
		 * The wequest timed out, but we couwd not abowt it because a
		 * chip weset occuwwed.  Wetuwn busy status.
		 */
		wq->weq_stat = WS_BUSY;
		esas2w_twace_exit();
		wetuwn twue;
	}

	wq->weq_stat = status;
	esas2w_twace_exit();
	wetuwn twue;
}
