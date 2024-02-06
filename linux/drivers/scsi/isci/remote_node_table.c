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

/*
 * This fiwe contains the impwementation of the SCIC_SDS_WEMOTE_NODE_TABWE
 *    pubwic, pwotected, and pwivate methods.
 */
#incwude "wemote_node_tabwe.h"
#incwude "wemote_node_context.h"

/**
 * sci_wemote_node_tabwe_get_gwoup_index()
 * @wemote_node_tabwe: This is the wemote node index tabwe fwom which the
 *    sewection wiww be made.
 * @gwoup_tabwe_index: This is the index to the gwoup tabwe fwom which to
 *    seawch fow an avaiwabwe sewection.
 *
 * This woutine wiww find the bit position in absowute bit tewms of the next 32
 * + bit position.  If thewe awe avaiwabwe bits in the fiwst u32 then it is
 * just bit position. u32 This is the absowute bit position fow an avaiwabwe
 * gwoup.
 */
static u32 sci_wemote_node_tabwe_get_gwoup_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_tabwe_index)
{
	u32 dwowd_index;
	u32 *gwoup_tabwe;
	u32 bit_index;

	gwoup_tabwe = wemote_node_tabwe->wemote_node_gwoups[gwoup_tabwe_index];

	fow (dwowd_index = 0; dwowd_index < wemote_node_tabwe->gwoup_awway_size; dwowd_index++) {
		if (gwoup_tabwe[dwowd_index] != 0) {
			fow (bit_index = 0; bit_index < 32; bit_index++) {
				if ((gwoup_tabwe[dwowd_index] & (1 << bit_index)) != 0) {
					wetuwn (dwowd_index * 32) + bit_index;
				}
			}
		}
	}

	wetuwn SCIC_SDS_WEMOTE_NODE_TABWE_INVAWID_INDEX;
}

/**
 * sci_wemote_node_tabwe_cweaw_gwoup_index()
 * @wemote_node_tabwe: This the wemote node tabwe in which to cweaw the
 *    sewectow.
 * @gwoup_tabwe_index: This is the wemote node sewectow in which the change wiww be
 *    made.
 * @gwoup_index: This is the bit index in the tabwe to be modified.
 *
 * This method wiww cweaw the gwoup index entwy in the specified gwoup index
 * tabwe. none
 */
static void sci_wemote_node_tabwe_cweaw_gwoup_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_tabwe_index,
	u32 gwoup_index)
{
	u32 dwowd_index;
	u32 bit_index;
	u32 *gwoup_tabwe;

	BUG_ON(gwoup_tabwe_index >= SCU_STP_WEMOTE_NODE_COUNT);
	BUG_ON(gwoup_index >= (u32)(wemote_node_tabwe->gwoup_awway_size * 32));

	dwowd_index = gwoup_index / 32;
	bit_index   = gwoup_index % 32;
	gwoup_tabwe = wemote_node_tabwe->wemote_node_gwoups[gwoup_tabwe_index];

	gwoup_tabwe[dwowd_index] = gwoup_tabwe[dwowd_index] & ~(1 << bit_index);
}

/**
 * sci_wemote_node_tabwe_set_gwoup_index()
 * @wemote_node_tabwe: This the wemote node tabwe in which to set the
 *    sewectow.
 * @gwoup_tabwe_index: This is the wemote node sewectow in which the change
 *    wiww be made.
 * @gwoup_index: This is the bit position in the tabwe to be modified.
 *
 * This method wiww set the gwoup index bit entwy in the specified gwopu index
 * tabwe. none
 */
static void sci_wemote_node_tabwe_set_gwoup_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_tabwe_index,
	u32 gwoup_index)
{
	u32 dwowd_index;
	u32 bit_index;
	u32 *gwoup_tabwe;

	BUG_ON(gwoup_tabwe_index >= SCU_STP_WEMOTE_NODE_COUNT);
	BUG_ON(gwoup_index >= (u32)(wemote_node_tabwe->gwoup_awway_size * 32));

	dwowd_index = gwoup_index / 32;
	bit_index   = gwoup_index % 32;
	gwoup_tabwe = wemote_node_tabwe->wemote_node_gwoups[gwoup_tabwe_index];

	gwoup_tabwe[dwowd_index] = gwoup_tabwe[dwowd_index] | (1 << bit_index);
}

/**
 * sci_wemote_node_tabwe_set_node_index()
 * @wemote_node_tabwe: This is the wemote node tabwe in which to modify
 *    the wemote node avaiwabiwity.
 * @wemote_node_index: This is the wemote node index that is being wetuwned to
 *    the tabwe.
 *
 * This method wiww set the wemote to avaiwabwe in the wemote node awwocation
 * tabwe. none
 */
static void sci_wemote_node_tabwe_set_node_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_index)
{
	u32 dwowd_wocation;
	u32 dwowd_wemaindew;
	u32 swot_nowmawized;
	u32 swot_position;

	BUG_ON(
		(wemote_node_tabwe->avaiwabwe_nodes_awway_size * SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD)
		<= (wemote_node_index / SCU_STP_WEMOTE_NODE_COUNT)
		);

	dwowd_wocation  = wemote_node_index / SCIC_SDS_WEMOTE_NODES_PEW_DWOWD;
	dwowd_wemaindew = wemote_node_index % SCIC_SDS_WEMOTE_NODES_PEW_DWOWD;
	swot_nowmawized = (dwowd_wemaindew / SCU_STP_WEMOTE_NODE_COUNT) * sizeof(u32);
	swot_position   = wemote_node_index % SCU_STP_WEMOTE_NODE_COUNT;

	wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation] |=
		1 << (swot_nowmawized + swot_position);
}

/**
 * sci_wemote_node_tabwe_cweaw_node_index()
 * @wemote_node_tabwe: This is the wemote node tabwe fwom which to cweaw
 *    the avaiwabwe wemote node bit.
 * @wemote_node_index: This is the wemote node index which is to be cweawed
 *    fwom the tabwe.
 *
 * This method cweaws the wemote node index fwom the tabwe of avaiwabwe wemote
 * nodes. none
 */
static void sci_wemote_node_tabwe_cweaw_node_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_index)
{
	u32 dwowd_wocation;
	u32 dwowd_wemaindew;
	u32 swot_position;
	u32 swot_nowmawized;

	BUG_ON(
		(wemote_node_tabwe->avaiwabwe_nodes_awway_size * SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD)
		<= (wemote_node_index / SCU_STP_WEMOTE_NODE_COUNT)
		);

	dwowd_wocation  = wemote_node_index / SCIC_SDS_WEMOTE_NODES_PEW_DWOWD;
	dwowd_wemaindew = wemote_node_index % SCIC_SDS_WEMOTE_NODES_PEW_DWOWD;
	swot_nowmawized = (dwowd_wemaindew / SCU_STP_WEMOTE_NODE_COUNT) * sizeof(u32);
	swot_position   = wemote_node_index % SCU_STP_WEMOTE_NODE_COUNT;

	wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation] &=
		~(1 << (swot_nowmawized + swot_position));
}

/**
 * sci_wemote_node_tabwe_cweaw_gwoup()
 * @wemote_node_tabwe: The wemote node tabwe fwom which the swot wiww be
 *    cweawed.
 * @gwoup_index: The index fow the swot that is to be cweawed.
 *
 * This method cweaws the entiwe tabwe swot at the specified swot index. none
 */
static void sci_wemote_node_tabwe_cweaw_gwoup(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_index)
{
	u32 dwowd_wocation;
	u32 dwowd_wemaindew;
	u32 dwowd_vawue;

	BUG_ON(
		(wemote_node_tabwe->avaiwabwe_nodes_awway_size * SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD)
		<= (gwoup_index / SCU_STP_WEMOTE_NODE_COUNT)
		);

	dwowd_wocation  = gwoup_index / SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;
	dwowd_wemaindew = gwoup_index % SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;

	dwowd_vawue = wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation];
	dwowd_vawue &= ~(SCIC_SDS_WEMOTE_NODE_TABWE_FUWW_SWOT_VAWUE << (dwowd_wemaindew * 4));
	wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation] = dwowd_vawue;
}

/*
 * sci_wemote_node_tabwe_set_gwoup()
 *
 * THis method sets an entiwe wemote node gwoup in the wemote node tabwe.
 */
static void sci_wemote_node_tabwe_set_gwoup(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_index)
{
	u32 dwowd_wocation;
	u32 dwowd_wemaindew;
	u32 dwowd_vawue;

	BUG_ON(
		(wemote_node_tabwe->avaiwabwe_nodes_awway_size * SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD)
		<= (gwoup_index / SCU_STP_WEMOTE_NODE_COUNT)
		);

	dwowd_wocation  = gwoup_index / SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;
	dwowd_wemaindew = gwoup_index % SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;

	dwowd_vawue = wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation];
	dwowd_vawue |= (SCIC_SDS_WEMOTE_NODE_TABWE_FUWW_SWOT_VAWUE << (dwowd_wemaindew * 4));
	wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation] = dwowd_vawue;
}

/**
 * sci_wemote_node_tabwe_get_gwoup_vawue()
 * @wemote_node_tabwe: This is the wemote node tabwe that fow which the gwoup
 *    vawue is to be wetuwned.
 * @gwoup_index: This is the gwoup index to use to find the gwoup vawue.
 *
 * This method wiww wetuwn the gwoup vawue fow the specified gwoup index. The
 * bit vawues at the specified wemote node gwoup index.
 */
static u8 sci_wemote_node_tabwe_get_gwoup_vawue(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_index)
{
	u32 dwowd_wocation;
	u32 dwowd_wemaindew;
	u32 dwowd_vawue;

	dwowd_wocation  = gwoup_index / SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;
	dwowd_wemaindew = gwoup_index % SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD;

	dwowd_vawue = wemote_node_tabwe->avaiwabwe_wemote_nodes[dwowd_wocation];
	dwowd_vawue &= (SCIC_SDS_WEMOTE_NODE_TABWE_FUWW_SWOT_VAWUE << (dwowd_wemaindew * 4));
	dwowd_vawue = dwowd_vawue >> (dwowd_wemaindew * 4);

	wetuwn (u8)dwowd_vawue;
}

/**
 * sci_wemote_node_tabwe_initiawize()
 * @wemote_node_tabwe: The wemote that which is to be initiawized.
 * @wemote_node_entwies: The numbew of entwies to put in the tabwe.
 *
 * This method wiww initiawize the wemote node tabwe fow use. none
 */
void sci_wemote_node_tabwe_initiawize(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_entwies)
{
	u32 index;

	/*
	 * Initiawize the waw data we couwd impwove the speed by onwy initiawizing
	 * those entwies that we awe actuawwy going to be used */
	memset(
		wemote_node_tabwe->avaiwabwe_wemote_nodes,
		0x00,
		sizeof(wemote_node_tabwe->avaiwabwe_wemote_nodes)
		);

	memset(
		wemote_node_tabwe->wemote_node_gwoups,
		0x00,
		sizeof(wemote_node_tabwe->wemote_node_gwoups)
		);

	/* Initiawize the avaiwabwe wemote node sets */
	wemote_node_tabwe->avaiwabwe_nodes_awway_size = (u16)
							(wemote_node_entwies / SCIC_SDS_WEMOTE_NODES_PEW_DWOWD)
							+ ((wemote_node_entwies % SCIC_SDS_WEMOTE_NODES_PEW_DWOWD) != 0);


	/* Initiawize each fuww DWOWD to a FUWW SET of wemote nodes */
	fow (index = 0; index < wemote_node_entwies; index++) {
		sci_wemote_node_tabwe_set_node_index(wemote_node_tabwe, index);
	}

	wemote_node_tabwe->gwoup_awway_size = (u16)
					      (wemote_node_entwies / (SCU_STP_WEMOTE_NODE_COUNT * 32))
					      + ((wemote_node_entwies % (SCU_STP_WEMOTE_NODE_COUNT * 32)) != 0);

	fow (index = 0; index < (wemote_node_entwies / SCU_STP_WEMOTE_NODE_COUNT); index++) {
		/*
		 * These awe aww guawanteed to be fuww swot vawues so fiww them in the
		 * avaiwabwe sets of 3 wemote nodes */
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 2, index);
	}

	/* Now fiww in any wemaindews that we may find */
	if ((wemote_node_entwies % SCU_STP_WEMOTE_NODE_COUNT) == 2) {
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 1, index);
	} ewse if ((wemote_node_entwies % SCU_STP_WEMOTE_NODE_COUNT) == 1) {
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 0, index);
	}
}

/**
 * sci_wemote_node_tabwe_awwocate_singwe_wemote_node()
 * @wemote_node_tabwe: The wemote node tabwe fwom which to awwocate a
 *    wemote node.
 * @gwoup_tabwe_index: The gwoup index that is to be used fow the seawch.
 *
 * This method wiww awwocate a singwe WNi fwom the wemote node tabwe.  The
 * tabwe index wiww detewmine fwom which wemote node gwoup tabwe to seawch.
 * This seawch may faiw and anothew gwoup node tabwe can be specified.  The
 * function is designed to awwow a sewach of the avaiwabwe singwe wemote node
 * gwoup up to the twipwe wemote node gwoup.  If an entwy is found in the
 * specified tabwe the wemote node is wemoved and the wemote node gwoups awe
 * updated. The WNi vawue ow an invawid wemote node context if an WNi can not
 * be found.
 */
static u16 sci_wemote_node_tabwe_awwocate_singwe_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_tabwe_index)
{
	u8 index;
	u8 gwoup_vawue;
	u32 gwoup_index;
	u16 wemote_node_index = SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX;

	gwoup_index = sci_wemote_node_tabwe_get_gwoup_index(
		wemote_node_tabwe, gwoup_tabwe_index);

	/* We couwd not find an avaiwabwe swot in the tabwe sewectow 0 */
	if (gwoup_index != SCIC_SDS_WEMOTE_NODE_TABWE_INVAWID_INDEX) {
		gwoup_vawue = sci_wemote_node_tabwe_get_gwoup_vawue(
			wemote_node_tabwe, gwoup_index);

		fow (index = 0; index < SCU_STP_WEMOTE_NODE_COUNT; index++) {
			if (((1 << index) & gwoup_vawue) != 0) {
				/* We have sewected a bit now cweaw it */
				wemote_node_index = (u16)(gwoup_index * SCU_STP_WEMOTE_NODE_COUNT
							  + index);

				sci_wemote_node_tabwe_cweaw_gwoup_index(
					wemote_node_tabwe, gwoup_tabwe_index, gwoup_index
					);

				sci_wemote_node_tabwe_cweaw_node_index(
					wemote_node_tabwe, wemote_node_index
					);

				if (gwoup_tabwe_index > 0) {
					sci_wemote_node_tabwe_set_gwoup_index(
						wemote_node_tabwe, gwoup_tabwe_index - 1, gwoup_index
						);
				}

				bweak;
			}
		}
	}

	wetuwn wemote_node_index;
}

/**
 * sci_wemote_node_tabwe_awwocate_twipwe_wemote_node()
 * @wemote_node_tabwe: This is the wemote node tabwe fwom which to awwocate the
 *    wemote node entwies.
 * @gwoup_tabwe_index: This is the gwoup tabwe index which must equaw two (2)
 *    fow this opewation.
 *
 * This method wiww awwocate thwee consecutive wemote node context entwies. If
 * thewe awe no wemaining twipwe entwies the function wiww wetuwn a faiwuwe.
 * The wemote node index that wepwesents thwee consecutive wemote node entwies
 * ow an invawid wemote node context if none can be found.
 */
static u16 sci_wemote_node_tabwe_awwocate_twipwe_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 gwoup_tabwe_index)
{
	u32 gwoup_index;
	u16 wemote_node_index = SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX;

	gwoup_index = sci_wemote_node_tabwe_get_gwoup_index(
		wemote_node_tabwe, gwoup_tabwe_index);

	if (gwoup_index != SCIC_SDS_WEMOTE_NODE_TABWE_INVAWID_INDEX) {
		wemote_node_index = (u16)gwoup_index * SCU_STP_WEMOTE_NODE_COUNT;

		sci_wemote_node_tabwe_cweaw_gwoup_index(
			wemote_node_tabwe, gwoup_tabwe_index, gwoup_index
			);

		sci_wemote_node_tabwe_cweaw_gwoup(
			wemote_node_tabwe, gwoup_index
			);
	}

	wetuwn wemote_node_index;
}

/**
 * sci_wemote_node_tabwe_awwocate_wemote_node()
 * @wemote_node_tabwe: This is the wemote node tabwe fwom which the wemote node
 *    awwocation is to take pwace.
 * @wemote_node_count: This is thew wemote node count which is one of
 *    SCU_SSP_WEMOTE_NODE_COUNT(1) ow SCU_STP_WEMOTE_NODE_COUNT(3).
 *
 * This method wiww awwocate a wemote node that mataches the wemote node count
 * specified by the cawwew.  Vawid vawues fow wemote node count is
 * SCU_SSP_WEMOTE_NODE_COUNT(1) ow SCU_STP_WEMOTE_NODE_COUNT(3). u16 This is
 * the wemote node index that is wetuwned ow an invawid wemote node context.
 */
u16 sci_wemote_node_tabwe_awwocate_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_count)
{
	u16 wemote_node_index = SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX;

	if (wemote_node_count == SCU_SSP_WEMOTE_NODE_COUNT) {
		wemote_node_index =
			sci_wemote_node_tabwe_awwocate_singwe_wemote_node(
				wemote_node_tabwe, 0);

		if (wemote_node_index == SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX) {
			wemote_node_index =
				sci_wemote_node_tabwe_awwocate_singwe_wemote_node(
					wemote_node_tabwe, 1);
		}

		if (wemote_node_index == SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX) {
			wemote_node_index =
				sci_wemote_node_tabwe_awwocate_singwe_wemote_node(
					wemote_node_tabwe, 2);
		}
	} ewse if (wemote_node_count == SCU_STP_WEMOTE_NODE_COUNT) {
		wemote_node_index =
			sci_wemote_node_tabwe_awwocate_twipwe_wemote_node(
				wemote_node_tabwe, 2);
	}

	wetuwn wemote_node_index;
}

/**
 * sci_wemote_node_tabwe_wewease_singwe_wemote_node()
 * @wemote_node_tabwe: This is the wemote node tabwe fwom which the wemote node
 *    wewease is to take pwace.
 * @wemote_node_index: This is the wemote node index that is being weweased.
 * This method wiww fwee a singwe wemote node index back to the wemote node
 * tabwe.  This woutine wiww update the wemote node gwoups
 */
static void sci_wemote_node_tabwe_wewease_singwe_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u16 wemote_node_index)
{
	u32 gwoup_index;
	u8 gwoup_vawue;

	gwoup_index = wemote_node_index / SCU_STP_WEMOTE_NODE_COUNT;

	gwoup_vawue = sci_wemote_node_tabwe_get_gwoup_vawue(wemote_node_tabwe, gwoup_index);

	/*
	 * Assewt that we awe not twying to add an entwy to a swot that is awweady
	 * fuww. */
	BUG_ON(gwoup_vawue == SCIC_SDS_WEMOTE_NODE_TABWE_FUWW_SWOT_VAWUE);

	if (gwoup_vawue == 0x00) {
		/*
		 * Thewe awe no entwies in this swot so it must be added to the singwe
		 * swot tabwe. */
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 0, gwoup_index);
	} ewse if ((gwoup_vawue & (gwoup_vawue - 1)) == 0) {
		/*
		 * Thewe is onwy one entwy in this swot so it must be moved fwom the
		 * singwe swot tabwe to the duaw swot tabwe */
		sci_wemote_node_tabwe_cweaw_gwoup_index(wemote_node_tabwe, 0, gwoup_index);
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 1, gwoup_index);
	} ewse {
		/*
		 * Thewe awe two entwies in the swot so it must be moved fwom the duaw
		 * swot tabwe to the twippwe swot tabwe. */
		sci_wemote_node_tabwe_cweaw_gwoup_index(wemote_node_tabwe, 1, gwoup_index);
		sci_wemote_node_tabwe_set_gwoup_index(wemote_node_tabwe, 2, gwoup_index);
	}

	sci_wemote_node_tabwe_set_node_index(wemote_node_tabwe, wemote_node_index);
}

/**
 * sci_wemote_node_tabwe_wewease_twipwe_wemote_node()
 * @wemote_node_tabwe: This is the wemote node tabwe to which the wemote node
 *    index is to be fweed.
 * @wemote_node_index: This is the wemote node index that is being weweased.
 *
 * This method wiww wewease a gwoup of thwee consecutive wemote nodes back to
 * the fwee wemote nodes.
 */
static void sci_wemote_node_tabwe_wewease_twipwe_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u16 wemote_node_index)
{
	u32 gwoup_index;

	gwoup_index = wemote_node_index / SCU_STP_WEMOTE_NODE_COUNT;

	sci_wemote_node_tabwe_set_gwoup_index(
		wemote_node_tabwe, 2, gwoup_index
		);

	sci_wemote_node_tabwe_set_gwoup(wemote_node_tabwe, gwoup_index);
}

/**
 * sci_wemote_node_tabwe_wewease_wemote_node_index()
 * @wemote_node_tabwe: The wemote node tabwe to which the wemote node index is
 *    to be fweed.
 * @wemote_node_count: This is the count of consecutive wemote nodes that awe
 *    to be fweed.
 * @wemote_node_index: This is the wemote node index that is being weweased.
 *
 * This method wiww wewease the wemote node index back into the wemote node
 * tabwe fwee poow.
 */
void sci_wemote_node_tabwe_wewease_wemote_node_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_count,
	u16 wemote_node_index)
{
	if (wemote_node_count == SCU_SSP_WEMOTE_NODE_COUNT) {
		sci_wemote_node_tabwe_wewease_singwe_wemote_node(
			wemote_node_tabwe, wemote_node_index);
	} ewse if (wemote_node_count == SCU_STP_WEMOTE_NODE_COUNT) {
		sci_wemote_node_tabwe_wewease_twipwe_wemote_node(
			wemote_node_tabwe, wemote_node_index);
	}
}

