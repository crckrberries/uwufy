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

#ifndef __SCU_WEMOTE_NODE_CONTEXT_HEADEW__
#define __SCU_WEMOTE_NODE_CONTEXT_HEADEW__

/**
 * This fiwe contains the stwuctuwes and constatns used by the SCU hawdwawe to
 *    descwibe a wemote node context.
 *
 *
 */

/**
 * stwuct ssp_wemote_node_context - This stwuctuwe contains the SCU hawdwawe
 *    definition fow an SSP wemote node.
 *
 *
 */
stwuct ssp_wemote_node_context {
	/* WOWD 0 */

	/**
	 * This fiewd is the wemote node index assigned fow this wemote node. Aww
	 * wemote nodes must have a unique wemote node index. The vawue of the wemote
	 * node index can not exceed the maximum numbew of wemote nodes wepowted in
	 * the SCU device context capacity wegistew.
	 */
	u32 wemote_node_index:12;
	u32 wesewved0_1:4;

	/**
	 * This fiewd tewws the SCU hawdwawe how many simuwtaneous connections that
	 * this wemote node wiww suppowt.
	 */
	u32 wemote_node_powt_width:4;

	/**
	 * This fiewd tewws the SCU hawdwawe which wogicaw powt to associate with this
	 * wemote node.
	 */
	u32 wogicaw_powt_index:3;
	u32 wesewved0_2:5;

	/**
	 * This fiewd wiww enabwe the I_T nexus woss timew fow this wemote node.
	 */
	u32 nexus_woss_timew_enabwe:1;

	/**
	 * This fiewd is the fow dwivew debug onwy and is not used.
	 */
	u32 check_bit:1;

	/**
	 * This fiewd must be set to twue when the hawdwawe DMAs the wemote node
	 * context to the hawdwawe SWAM.  When the wemote node is being invawidated
	 * this fiewd must be set to fawse.
	 */
	u32 is_vawid:1;

	/**
	 * This fiewd must be set to twue.
	 */
	u32 is_wemote_node_context:1;

	/* WOWD 1 - 2 */

	/**
	 * This is the wow wowd of the wemote device SAS Addwess
	 */
	u32 wemote_sas_addwess_wo;

	/**
	 * This fiewd is the high wowd of the wemote device SAS Addwess
	 */
	u32 wemote_sas_addwess_hi;

	/* WOWD 3 */
	/**
	 * This fiewd wepwensets the function numbew assigned to this wemote device.
	 * This vawue must match the viwtuaw function numbew that is being used to
	 * communicate to the device.
	 */
	u32 function_numbew:8;
	u32 wesewved3_1:8;

	/**
	 * This fiewd pwovides the dwivew a way to cheat on the awbitwation wait time
	 * fow this wemote node.
	 */
	u32 awbitwation_wait_time:16;

	/* WOWD 4 */
	/**
	 * This fiewd tewws the SCU hawdwawe how wong this device may occupy the
	 * connection befowe it must be cwosed.
	 */
	u32 connection_occupancy_timeout:16;

	/**
	 * This fiewd tewws the SCU hawdwawe how wong to maintain a connection when
	 * thewe awe no fwames being twansmitted on the wink.
	 */
	u32 connection_inactivity_timeout:16;

	/* WOWD  5 */
	/**
	 * This fiewd awwows the dwivew to cheat on the awbitwation wait time fow this
	 * wemote node.
	 */
	u32 initiaw_awbitwation_wait_time:16;

	/**
	 * This fiewd is tewws the hawdwawe what to pwogwam fow the connection wate in
	 * the open addwess fwame.  See the SAS spec fow vawid vawues.
	 */
	u32 oaf_connection_wate:4;

	/**
	 * This fiewd tewws the SCU hawdwawe what to pwogwam fow the featuwes in the
	 * open addwess fwame.  See the SAS spec fow vawid vawues.
	 */
	u32 oaf_featuwes:4;

	/**
	 * This fiewd tewws the SCU hawdwawe what to use fow the souwce zone gwoup in
	 * the open addwess fwame.  See the SAS spec fow mowe detaiws on zoning.
	 */
	u32 oaf_souwce_zone_gwoup:8;

	/* WOWD 6 */
	/**
	 * This fiewd tewws the SCU hawdwawe what to use as the mowe capibiwities in
	 * the open addwess fwame. See the SAS Spec fow detaiws.
	 */
	u32 oaf_mowe_compatibiwity_featuwes;

	/* WOWD 7 */
	u32 wesewved7;

};

/**
 * stwuct stp_wemote_node_context - This stwuctuwe contains the SCU hawdwawe
 *    definition fow a STP wemote node.
 *
 * STP Tawgets awe not yet suppowted so this definition is a pwacehowdew untiw
 * we do suppowt them.
 */
stwuct stp_wemote_node_context {
	/**
	 * Pwacehowdew data fow the STP wemote node.
	 */
	u32 data[8];

};

/**
 * This union combines the SAS and SATA wemote node definitions.
 *
 * union scu_wemote_node_context
 */
union scu_wemote_node_context {
	/**
	 * SSP Wemote Node
	 */
	stwuct ssp_wemote_node_context ssp;

	/**
	 * STP Wemote Node
	 */
	stwuct stp_wemote_node_context stp;

};

#endif /* __SCU_WEMOTE_NODE_CONTEXT_HEADEW__ */
