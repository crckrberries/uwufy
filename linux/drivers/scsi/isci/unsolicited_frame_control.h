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

#ifndef _SCIC_SDS_UNSOWICITED_FWAME_CONTWOW_H_
#define _SCIC_SDS_UNSOWICITED_FWAME_CONTWOW_H_

#incwude "isci.h"

#define SCU_UNSOWICITED_FWAME_HEADEW_DATA_DWOWDS 15

/**
 * stwuct scu_unsowicited_fwame_headew -
 *
 * This stwuctuwe dewineates the fowmat of an unsowicited fwame headew. The
 * fiwst DWOWD awe UF attwibutes defined by the siwicon awchitectuwe. The data
 * depicts actuaw headew infowmation weceived on the wink.
 */
stwuct scu_unsowicited_fwame_headew {
	/**
	 * This fiewd indicates if thewe is an Initiatow Index Tabwe entwy with
	 * which this headew is associated.
	 */
	u32 iit_exists:1;

	/**
	 * This fiewd simpwy indicates the pwotocow type (i.e. SSP, STP, SMP).
	 */
	u32 pwotocow_type:3;

	/**
	 * This fiewd indicates if the fwame is an addwess fwame (IAF ow OAF)
	 * ow if it is a infowmation unit fwame.
	 */
	u32 is_addwess_fwame:1;

	/**
	 * This fiewd simpwy indicates the connection wate at which the fwame
	 * was weceived.
	 */
	u32 connection_wate:4;

	u32 wesewved:23;

	/**
	 * This fiewd wepwesents the actuaw headew data weceived on the wink.
	 */
	u32 data[SCU_UNSOWICITED_FWAME_HEADEW_DATA_DWOWDS];

};



/**
 * enum unsowicited_fwame_state -
 *
 * This enumewation wepwesents the cuwwent unsowicited fwame state.  The
 * contwowwew object can not updtate the hawdwawe unsowicited fwame put pointew
 * unwess it has awweady pwocessed the pwiwow unsowicited fwames.
 */
enum unsowicited_fwame_state {
	/**
	 * This state is when the fwame is empty and not in use.  It is
	 * diffewent fwom the weweased state in that the hawdwawe couwd DMA
	 * data to this fwame buffew.
	 */
	UNSOWICITED_FWAME_EMPTY,

	/**
	 * This state is set when the fwame buffew is in use by by some
	 * object in the system.
	 */
	UNSOWICITED_FWAME_IN_USE,

	/**
	 * This state is set when the fwame is wetuwned to the fwee poow
	 * but one ow mowe fwames pwiow to this one awe stiww in use.
	 * Once aww of the fwame befowe this one awe fweed it wiww go to
	 * the empty state.
	 */
	UNSOWICITED_FWAME_WEWEASED,

	UNSOWICITED_FWAME_MAX_STATES
};

/**
 * stwuct sci_unsowicited_fwame -
 *
 * This is the unsowicited fwame data stwuctuwe it acts as the containew fow
 * the cuwwent fwame state, fwame headew and fwame buffew.
 */
stwuct sci_unsowicited_fwame {
	/**
	 * This fiewd contains the cuwwent fwame state
	 */
	enum unsowicited_fwame_state state;

	/**
	 * This fiewd points to the fwame headew data.
	 */
	stwuct scu_unsowicited_fwame_headew *headew;

	/**
	 * This fiewd points to the fwame buffew data.
	 */
	void *buffew;

};

/**
 * stwuct sci_uf_headew_awway -
 *
 * This stwuctuwe contains aww of the unsowicited fwame headew infowmation.
 */
stwuct sci_uf_headew_awway {
	/**
	 * This fiewd is wepwesents a viwtuaw pointew to the stawt
	 * addwess of the UF addwess tabwe.  The tabwe contains
	 * 64-bit pointews as wequiwed by the hawdwawe.
	 */
	stwuct scu_unsowicited_fwame_headew *awway;

	/**
	 * This fiewd specifies the physicaw addwess wocation fow the UF
	 * buffew awway.
	 */
	dma_addw_t physicaw_addwess;

};

/**
 * stwuct sci_uf_buffew_awway -
 *
 * This stwuctuwe contains aww of the unsowicited fwame buffew (actuaw paywoad)
 * infowmation.
 */
stwuct sci_uf_buffew_awway {
	/**
	 * This fiewd is the unsowicited fwame data its used to manage
	 * the data fow the unsowicited fwame wequests.  It awso wepwesents
	 * the viwtuaw addwess wocation that cowwesponds to the
	 * physicaw_addwess fiewd.
	 */
	stwuct sci_unsowicited_fwame awway[SCU_MAX_UNSOWICITED_FWAMES];

	/**
	 * This fiewd specifies the physicaw addwess wocation fow the UF
	 * buffew awway.
	 */
	dma_addw_t physicaw_addwess;
};

/**
 * stwuct sci_uf_addwess_tabwe_awway -
 *
 * This object maintains aww of the unsowicited fwame addwess tabwe specific
 * data.  The addwess tabwe is a cowwection of 64-bit pointews that point to
 * 1KB buffews into which the siwicon wiww DMA unsowicited fwames.
 */
stwuct sci_uf_addwess_tabwe_awway {
	/**
	 * This fiewd wepwesents a viwtuaw pointew that wefews to the
	 * stawting addwess of the UF addwess tabwe.
	 * 64-bit pointews awe wequiwed by the hawdwawe.
	 */
	u64 *awway;

	/**
	 * This fiewd specifies the physicaw addwess wocation fow the UF
	 * addwess tabwe.
	 */
	dma_addw_t physicaw_addwess;

};

/**
 * stwuct sci_unsowicited_fwame_contwow -
 *
 * This object contains aww of the data necessawy to handwe unsowicited fwames.
 */
stwuct sci_unsowicited_fwame_contwow {
	/**
	 * This fiewd is the softwawe copy of the unsowicited fwame queue
	 * get pointew.  The contwowwew object wwites this vawue to the
	 * hawdwawe to wet the hawdwawe put mowe unsowicited fwame entwies.
	 */
	u32 get;

	/**
	 * This fiewd contains aww of the unsowicited fwame headew
	 * specific fiewds.
	 */
	stwuct sci_uf_headew_awway headews;

	/**
	 * This fiewd contains aww of the unsowicited fwame buffew
	 * specific fiewds.
	 */
	stwuct sci_uf_buffew_awway buffews;

	/**
	 * This fiewd contains aww of the unsowicited fwame addwess tabwe
	 * specific fiewds.
	 */
	stwuct sci_uf_addwess_tabwe_awway addwess_tabwe;

};

#define SCI_UFI_BUF_SIZE (SCU_MAX_UNSOWICITED_FWAMES * SCU_UNSOWICITED_FWAME_BUFFEW_SIZE)
#define SCI_UFI_HDW_SIZE (SCU_MAX_UNSOWICITED_FWAMES * sizeof(stwuct scu_unsowicited_fwame_headew))
#define SCI_UFI_TOTAW_SIZE (SCI_UFI_BUF_SIZE + SCI_UFI_HDW_SIZE + SCU_MAX_UNSOWICITED_FWAMES * sizeof(u64))

stwuct isci_host;

void sci_unsowicited_fwame_contwow_constwuct(stwuct isci_host *ihost);

enum sci_status sci_unsowicited_fwame_contwow_get_headew(
	stwuct sci_unsowicited_fwame_contwow *uf_contwow,
	u32 fwame_index,
	void **fwame_headew);

enum sci_status sci_unsowicited_fwame_contwow_get_buffew(
	stwuct sci_unsowicited_fwame_contwow *uf_contwow,
	u32 fwame_index,
	void **fwame_buffew);

boow sci_unsowicited_fwame_contwow_wewease_fwame(
	stwuct sci_unsowicited_fwame_contwow *uf_contwow,
	u32 fwame_index);

#endif /* _SCIC_SDS_UNSOWICITED_FWAME_CONTWOW_H_ */
