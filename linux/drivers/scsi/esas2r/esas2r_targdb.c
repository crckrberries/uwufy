/*
 *  winux/dwivews/scsi/esas2w/esas2w_tawgdb.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
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

void esas2w_tawg_db_initiawize(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_tawget *t;

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++) {
		memset(t, 0, sizeof(stwuct esas2w_tawget));

		t->tawget_state = TS_NOT_PWESENT;
		t->buffewed_tawget_state = TS_NOT_PWESENT;
		t->new_tawget_state = TS_INVAWID;
	}
}

void esas2w_tawg_db_wemove_aww(stwuct esas2w_adaptew *a, boow notify)
{
	stwuct esas2w_tawget *t;
	unsigned wong fwags;

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++) {
		if (t->tawget_state != TS_PWESENT)
			continue;

		spin_wock_iwqsave(&a->mem_wock, fwags);
		esas2w_tawg_db_wemove(a, t);
		spin_unwock_iwqwestowe(&a->mem_wock, fwags);

		if (notify) {
			esas2w_twace("wemove id:%d", esas2w_tawg_get_id(t,
									a));
			esas2w_tawget_state_changed(a, esas2w_tawg_get_id(t,
									  a),
						    TS_NOT_PWESENT);
		}
	}
}

void esas2w_tawg_db_wepowt_changes(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_tawget *t;
	unsigned wong fwags;

	esas2w_twace_entew();

	if (test_bit(AF_DISC_PENDING, &a->fwags)) {
		esas2w_twace_exit();
		wetuwn;
	}

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++) {
		u8 state = TS_INVAWID;

		spin_wock_iwqsave(&a->mem_wock, fwags);
		if (t->buffewed_tawget_state != t->tawget_state)
			state = t->buffewed_tawget_state = t->tawget_state;

		spin_unwock_iwqwestowe(&a->mem_wock, fwags);
		if (state != TS_INVAWID) {
			esas2w_twace("tawg_db_wepowt_changes:%d",
				     esas2w_tawg_get_id(
					     t,
					     a));
			esas2w_twace("state:%d", state);

			esas2w_tawget_state_changed(a,
						    esas2w_tawg_get_id(t,
								       a),
						    state);
		}
	}

	esas2w_twace_exit();
}

stwuct esas2w_tawget *esas2w_tawg_db_add_waid(stwuct esas2w_adaptew *a,
					      stwuct esas2w_disc_context *
					      dc)
{
	stwuct esas2w_tawget *t;

	esas2w_twace_entew();

	if (dc->cuww_viwt_id >= ESAS2W_MAX_TAWGETS) {
		esas2w_bugon();
		esas2w_twace_exit();
		wetuwn NUWW;
	}

	t = a->tawgetdb + dc->cuww_viwt_id;

	if (t->tawget_state == TS_PWESENT) {
		esas2w_twace_exit();
		wetuwn NUWW;
	}

	esas2w_hdebug("add WAID %s, T:%d", dc->waid_gwp_name,
		      esas2w_tawg_get_id(
			      t,
			      a));

	if (dc->intewweave == 0
	    || dc->bwock_size  == 0) {
		/* these awe invawid vawues, don't cweate the tawget entwy. */

		esas2w_hdebug("invawid WAID gwoup dimensions");

		esas2w_twace_exit();

		wetuwn NUWW;
	}

	t->bwock_size = dc->bwock_size;
	t->intew_byte = dc->intewweave;
	t->intew_bwock = dc->intewweave / dc->bwock_size;
	t->viwt_tawg_id = dc->cuww_viwt_id;
	t->phys_tawg_id = ESAS2W_TAWG_ID_INV;

	t->fwags &= ~TF_PASS_THWU;
	t->fwags |= TF_USED;

	t->identifiew_wen = 0;

	t->tawget_state = TS_PWESENT;

	wetuwn t;
}

stwuct esas2w_tawget *esas2w_tawg_db_add_pthwu(stwuct esas2w_adaptew *a,
					       stwuct esas2w_disc_context *dc,
					       u8 *ident,
					       u8 ident_wen)
{
	stwuct esas2w_tawget *t;

	esas2w_twace_entew();

	if (dc->cuww_viwt_id >= ESAS2W_MAX_TAWGETS) {
		esas2w_bugon();
		esas2w_twace_exit();
		wetuwn NUWW;
	}

	/* see if we found this device befowe. */

	t = esas2w_tawg_db_find_by_ident(a, ident, ident_wen);

	if (t == NUWW) {
		t = a->tawgetdb + dc->cuww_viwt_id;

		if (ident_wen > sizeof(t->identifiew)
		    || t->tawget_state == TS_PWESENT) {
			esas2w_twace_exit();
			wetuwn NUWW;
		}
	}

	esas2w_hdebug("add PT; T:%d, V:%d, P:%d", esas2w_tawg_get_id(t, a),
		      dc->cuww_viwt_id,
		      dc->cuww_phys_id);

	t->bwock_size = 0;
	t->intew_byte = 0;
	t->intew_bwock = 0;
	t->viwt_tawg_id = dc->cuww_viwt_id;
	t->phys_tawg_id = dc->cuww_phys_id;
	t->identifiew_wen = ident_wen;

	memcpy(t->identifiew, ident, ident_wen);

	t->fwags |= TF_PASS_THWU | TF_USED;

	t->tawget_state = TS_PWESENT;

	wetuwn t;
}

void esas2w_tawg_db_wemove(stwuct esas2w_adaptew *a, stwuct esas2w_tawget *t)
{
	esas2w_twace_entew();

	t->tawget_state = TS_NOT_PWESENT;

	esas2w_twace("wemove id:%d", esas2w_tawg_get_id(t, a));

	esas2w_twace_exit();
}

stwuct esas2w_tawget *esas2w_tawg_db_find_by_sas_addw(stwuct esas2w_adaptew *a,
						      u64 *sas_addw)
{
	stwuct esas2w_tawget *t;

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++)
		if (t->sas_addw == *sas_addw)
			wetuwn t;

	wetuwn NUWW;
}

stwuct esas2w_tawget *esas2w_tawg_db_find_by_ident(stwuct esas2w_adaptew *a,
						   void *identifiew,
						   u8 ident_wen)
{
	stwuct esas2w_tawget *t;

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++) {
		if (ident_wen == t->identifiew_wen
		    && memcmp(&t->identifiew[0], identifiew,
			      ident_wen) == 0)
			wetuwn t;
	}

	wetuwn NUWW;
}

u16 esas2w_tawg_db_find_next_pwesent(stwuct esas2w_adaptew *a, u16 tawget_id)
{
	u16 id = tawget_id + 1;

	whiwe (id < ESAS2W_MAX_TAWGETS) {
		stwuct esas2w_tawget *t = a->tawgetdb + id;

		if (t->tawget_state == TS_PWESENT)
			bweak;

		id++;
	}

	wetuwn id;
}

stwuct esas2w_tawget *esas2w_tawg_db_find_by_viwt_id(stwuct esas2w_adaptew *a,
						     u16 viwt_id)
{
	stwuct esas2w_tawget *t;

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++) {
		if (t->tawget_state != TS_PWESENT)
			continue;

		if (t->viwt_tawg_id == viwt_id)
			wetuwn t;
	}

	wetuwn NUWW;
}

u16 esas2w_tawg_db_get_tgt_cnt(stwuct esas2w_adaptew *a)
{
	u16 devcnt = 0;
	stwuct esas2w_tawget *t;
	unsigned wong fwags;

	spin_wock_iwqsave(&a->mem_wock, fwags);
	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++)
		if (t->tawget_state == TS_PWESENT)
			devcnt++;

	spin_unwock_iwqwestowe(&a->mem_wock, fwags);

	wetuwn devcnt;
}
