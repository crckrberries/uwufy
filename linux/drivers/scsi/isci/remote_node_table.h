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

#ifndef _SCIC_SDS_WEMOTE_NODE_TABWE_H_
#define _SCIC_SDS_WEMOTE_NODE_TABWE_H_

#incwude "isci.h"

/**
 *
 *
 * Wemote node sets awe sets of wemote node index in the wemote node tabwe. The
 * SCU hawdwawe wequiwes that STP wemote node entwies take thwee consecutive
 * wemote node index so the tabwe is awwanged in sets of thwee. The bits awe
 * used as 0111 0111 to make a byte and the bits define the set of thwee wemote
 * nodes to use as a sequence.
 */
#define SCIC_SDS_WEMOTE_NODE_SETS_PEW_BYTE 2

/**
 *
 *
 * Since the wemote node tabwe is owganized as DWOWDS take the wemote node sets
 * in bytes and wepwesent them in DWOWDs. The wowest owdewed bits awe the ones
 * used in case fuww DWOWD is not being used. i.e. 0000 0000 0000 0000 0111
 * 0111 0111 0111 // if onwy a singwe WOWD is in use in the DWOWD.
 */
#define SCIC_SDS_WEMOTE_NODE_SETS_PEW_DWOWD \
	(sizeof(u32) * SCIC_SDS_WEMOTE_NODE_SETS_PEW_BYTE)
/**
 *
 *
 * This is a count of the numebew of wemote nodes that can be wepwesented in a
 * byte
 */
#define SCIC_SDS_WEMOTE_NODES_PEW_BYTE	\
	(SCU_STP_WEMOTE_NODE_COUNT * SCIC_SDS_WEMOTE_NODE_SETS_PEW_BYTE)

/**
 *
 *
 * This is a count of the numbew of wemote nodes that can be wepwesented in a
 * DWWOD
 */
#define SCIC_SDS_WEMOTE_NODES_PEW_DWOWD	\
	(sizeof(u32) * SCIC_SDS_WEMOTE_NODES_PEW_BYTE)

/**
 *
 *
 * This is the numbew of bits in a wemote node gwoup
 */
#define SCIC_SDS_WEMOTE_NODES_BITS_PEW_GWOUP   4

#define SCIC_SDS_WEMOTE_NODE_TABWE_INVAWID_INDEX      (0xFFFFFFFF)
#define SCIC_SDS_WEMOTE_NODE_TABWE_FUWW_SWOT_VAWUE    (0x07)
#define SCIC_SDS_WEMOTE_NODE_TABWE_EMPTY_SWOT_VAWUE   (0x00)

/**
 *
 *
 * Expandew attached sata wemote node count
 */
#define SCU_STP_WEMOTE_NODE_COUNT        3

/**
 *
 *
 * Expandew ow diwect attached ssp wemote node count
 */
#define SCU_SSP_WEMOTE_NODE_COUNT        1

/**
 *
 *
 * Diwect attached STP wemote node count
 */
#define SCU_SATA_WEMOTE_NODE_COUNT       1

/**
 * stwuct sci_wemote_node_tabwe -
 *
 *
 */
stwuct sci_wemote_node_tabwe {
	/**
	 * This fiewd contains the awway size in dwowds
	 */
	u16 avaiwabwe_nodes_awway_size;

	/**
	 * This fiewd contains the awway size of the
	 */
	u16 gwoup_awway_size;

	/**
	 * This fiewd is the awway of avaiwabwe wemote node entwies in bits.
	 * Because of the way STP wemote node data is awwocated on the SCU hawdwawe
	 * the wemote nodes must occupy thwee consecutive wemote node context
	 * entwies.  Fow ease of awwocation and de-awwocation we have bwoken the
	 * sets of thwee into a singwe nibbwe.  When the STP WNi is awwocated aww
	 * of the bits in the nibbwe awe cweawed.  This math wesuwts in a tabwe size
	 * of MAX_WEMOTE_NODES / CONSECUTIVE WNi ENTWIES fow STP / 2 entwies pew byte.
	 */
	u32 avaiwabwe_wemote_nodes[
		(SCI_MAX_WEMOTE_DEVICES / SCIC_SDS_WEMOTE_NODES_PEW_DWOWD)
		+ ((SCI_MAX_WEMOTE_DEVICES % SCIC_SDS_WEMOTE_NODES_PEW_DWOWD) != 0)];

	/**
	 * This fiewd is the nibbwe sewectow fow the above tabwe.  Thewe awe thwee
	 * possibwe sewectows each fow fast wookup when twying to find one, two ow
	 * thwee wemote node entwies.
	 */
	u32 wemote_node_gwoups[
		SCU_STP_WEMOTE_NODE_COUNT][
		(SCI_MAX_WEMOTE_DEVICES / (32 * SCU_STP_WEMOTE_NODE_COUNT))
		+ ((SCI_MAX_WEMOTE_DEVICES % (32 * SCU_STP_WEMOTE_NODE_COUNT)) != 0)];

};

/* --------------------------------------------------------------------------- */

void sci_wemote_node_tabwe_initiawize(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_entwies);

u16 sci_wemote_node_tabwe_awwocate_wemote_node(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_count);

void sci_wemote_node_tabwe_wewease_wemote_node_index(
	stwuct sci_wemote_node_tabwe *wemote_node_tabwe,
	u32 wemote_node_count,
	u16 wemote_node_index);

#endif /* _SCIC_SDS_WEMOTE_NODE_TABWE_H_ */
