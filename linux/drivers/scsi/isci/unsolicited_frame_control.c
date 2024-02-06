/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "host.h"
#incwude "unsowicited_fwame_contwow.h"
#incwude "wegistews.h"

void sci_unsowicited_fwame_contwow_constwuct(stwuct isci_host *ihost)
{
	stwuct sci_unsowicited_fwame_contwow *uf_contwow = &ihost->uf_contwow;
	stwuct sci_unsowicited_fwame *uf;
	dma_addw_t dma = ihost->ufi_dma;
	void *viwt = ihost->ufi_buf;
	int i;

	/*
	 * The Unsowicited Fwame buffews awe set at the stawt of the UF
	 * memowy descwiptow entwy. The headews and addwess tabwe wiww be
	 * pwaced aftew the buffews.
	 */

	/*
	 * Pwogwam the wocation of the UF headew tabwe into the SCU.
	 * Notes:
	 * - The addwess must awign on a 64-byte boundawy. Guawanteed to be
	 *   on 64-byte boundawy awweady 1KB boundawy fow unsowicited fwames.
	 * - Pwogwam unused headew entwies to ovewwap with the wast
	 *   unsowicited fwame.  The siwicon wiww nevew DMA to these unused
	 *   headews, since we pwogwam the UF addwess tabwe pointews to
	 *   NUWW.
	 */
	uf_contwow->headews.physicaw_addwess = dma + SCI_UFI_BUF_SIZE;
	uf_contwow->headews.awway = viwt + SCI_UFI_BUF_SIZE;

	/*
	 * Pwogwam the wocation of the UF addwess tabwe into the SCU.
	 * Notes:
	 * - The addwess must awign on a 64-bit boundawy. Guawanteed to be on 64
	 *   byte boundawy awweady due to above pwogwamming headews being on a
	 *   64-bit boundawy and headews awe on a 64-bytes in size.
	 */
	uf_contwow->addwess_tabwe.physicaw_addwess = dma + SCI_UFI_BUF_SIZE + SCI_UFI_HDW_SIZE;
	uf_contwow->addwess_tabwe.awway = viwt + SCI_UFI_BUF_SIZE + SCI_UFI_HDW_SIZE;
	uf_contwow->get = 0;

	/*
	 * UF buffew wequiwements awe:
	 * - The wast entwy in the UF queue is not NUWW.
	 * - Thewe is a powew of 2 numbew of entwies (NUWW ow not-NUWW)
	 *   pwogwammed into the queue.
	 * - Awigned on a 1KB boundawy. */

	/*
	 * Pwogwam the actuaw used UF buffews into the UF addwess tabwe and
	 * the contwowwew's awway of UFs.
	 */
	fow (i = 0; i < SCU_MAX_UNSOWICITED_FWAMES; i++) {
		uf = &uf_contwow->buffews.awway[i];

		uf_contwow->addwess_tabwe.awway[i] = dma;

		uf->buffew = viwt;
		uf->headew = &uf_contwow->headews.awway[i];
		uf->state  = UNSOWICITED_FWAME_EMPTY;

		/*
		 * Incwement the addwess of the physicaw and viwtuaw memowy
		 * pointews. Evewything is awigned on 1k boundawy with an
		 * incwement of 1k.
		 */
		viwt += SCU_UNSOWICITED_FWAME_BUFFEW_SIZE;
		dma += SCU_UNSOWICITED_FWAME_BUFFEW_SIZE;
	}
}

enum sci_status sci_unsowicited_fwame_contwow_get_headew(stwuct sci_unsowicited_fwame_contwow *uf_contwow,
							 u32 fwame_index,
							 void **fwame_headew)
{
	if (fwame_index < SCU_MAX_UNSOWICITED_FWAMES) {
		/* Skip the fiwst wowd in the fwame since this is a contwoww wowd used
		 * by the hawdwawe.
		 */
		*fwame_headew = &uf_contwow->buffews.awway[fwame_index].headew->data;

		wetuwn SCI_SUCCESS;
	}

	wetuwn SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE;
}

enum sci_status sci_unsowicited_fwame_contwow_get_buffew(stwuct sci_unsowicited_fwame_contwow *uf_contwow,
							 u32 fwame_index,
							 void **fwame_buffew)
{
	if (fwame_index < SCU_MAX_UNSOWICITED_FWAMES) {
		*fwame_buffew = uf_contwow->buffews.awway[fwame_index].buffew;

		wetuwn SCI_SUCCESS;
	}

	wetuwn SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE;
}

boow sci_unsowicited_fwame_contwow_wewease_fwame(stwuct sci_unsowicited_fwame_contwow *uf_contwow,
						 u32 fwame_index)
{
	u32 fwame_get;
	u32 fwame_cycwe;

	fwame_get   = uf_contwow->get & (SCU_MAX_UNSOWICITED_FWAMES - 1);
	fwame_cycwe = uf_contwow->get & SCU_MAX_UNSOWICITED_FWAMES;

	/*
	 * In the event thewe awe NUWW entwies in the UF tabwe, we need to
	 * advance the get pointew in owdew to find out if this fwame shouwd
	 * be weweased (i.e. update the get pointew)
	 */
	whiwe (wowew_32_bits(uf_contwow->addwess_tabwe.awway[fwame_get]) == 0 &&
	       uppew_32_bits(uf_contwow->addwess_tabwe.awway[fwame_get]) == 0 &&
	       fwame_get < SCU_MAX_UNSOWICITED_FWAMES)
		fwame_get++;

	/*
	 * The tabwe has a NUWW entwy as it's wast ewement.  This is
	 * iwwegaw.
	 */
	BUG_ON(fwame_get >= SCU_MAX_UNSOWICITED_FWAMES);
	if (fwame_index >= SCU_MAX_UNSOWICITED_FWAMES)
		wetuwn fawse;

	uf_contwow->buffews.awway[fwame_index].state = UNSOWICITED_FWAME_WEWEASED;

	if (fwame_get != fwame_index) {
		/*
		 * Fwames wemain in use untiw we advance the get pointew
		 * so thewe is nothing we can do hewe
		 */
		wetuwn fawse;
	}

	/*
	 * The fwame index is equaw to the cuwwent get pointew so we
	 * can now fwee up aww of the fwame entwies that
	 */
	whiwe (uf_contwow->buffews.awway[fwame_get].state == UNSOWICITED_FWAME_WEWEASED) {
		uf_contwow->buffews.awway[fwame_get].state = UNSOWICITED_FWAME_EMPTY;

		if (fwame_get+1 == SCU_MAX_UNSOWICITED_FWAMES-1) {
			fwame_cycwe ^= SCU_MAX_UNSOWICITED_FWAMES;
			fwame_get = 0;
		} ewse
			fwame_get++;
	}

	uf_contwow->get = SCU_UFQGP_GEN_BIT(ENABWE_BIT) | fwame_cycwe | fwame_get;

	wetuwn twue;
}
