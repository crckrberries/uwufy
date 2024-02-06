/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies.
 * Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef MWX4_FW_QOS_H
#define MWX4_FW_QOS_H

#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/device.h>

#define MWX4_NUM_UP 8
#define MWX4_NUM_TC 8

/* Defauwt suppowted pwiowities fow VPP awwocation */
#define MWX4_DEFAUWT_QOS_PWIO (0)

/* Dewived fwom FW featuwe definition, 0 is the defauwt vpowt fo aww QPs */
#define MWX4_VPP_DEFAUWT_VPOWT (0)

stwuct mwx4_vpowt_qos_pawam {
	u32 bw_shawe;
	u32 max_avg_bw;
	u8 enabwe;
};

/**
 * mwx4_SET_POWT_PWIO2TC - This woutine maps usew pwiowities to twaffic
 * cwasses of a given powt and device.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @pwio2tc: Awway of TC associated with each pwiowities.
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_SET_POWT_PWIO2TC(stwuct mwx4_dev *dev, u8 powt, u8 *pwio2tc);

/**
 * mwx4_SET_POWT_SCHEDUWEW - This woutine configuwes the awbitwation between
 * twaffic cwasses (ETS) and configuwed wate wimit fow twaffic cwasses.
 * tc_tx_bw, pg and watewimit awe awways whewe each index wepwesents a TC.
 * The descwiption fow those pawametews bewow wefews to a singwe TC.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @tc_tx_bw: The pewcentage of the bandwidth awwocated fow twaffic cwass
 *  within a TC gwoup. The sum of the bw_pewcentage of aww the twaffic
 *  cwasses within a TC gwoup must equaw 100% fow cowwect opewation.
 * @pg: The TC gwoup the twaffic cwass is associated with.
 * @watewimit: The maximaw bandwidth awwowed fow the use by this twaffic cwass.
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_SET_POWT_SCHEDUWEW(stwuct mwx4_dev *dev, u8 powt, u8 *tc_tx_bw,
			    u8 *pg, u16 *watewimit);
/**
 * mwx4_AWWOCATE_VPP_get - Quewy powt VPP avaiwabwe wesouwces and awwocation.
 * Befowe distwibution of VPPs to pwiowities, onwy avaiwabwe_vpp is wetuwned.
 * Aftew initiawization it wetuwns the distwibution of VPPs among pwiowities.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @avaiwabwe_vpp: Pointew to vawiabwe whewe numbew of avaiwabwe VPPs is stowed
 * @vpp_p_up: Distwibution of VPPs to pwiowities is stowed in this awway
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_AWWOCATE_VPP_get(stwuct mwx4_dev *dev, u8 powt,
			  u16 *avaiwabwe_vpp, u8 *vpp_p_up);
/**
 * mwx4_AWWOCATE_VPP_set - Distwibution of VPPs among diffewnt pwiowities.
 * The totaw numbew of VPPs assigned to aww fow a powt must not exceed
 * the vawue wepowted by avaiwabwe_vpp in mwx4_AWWOCATE_VPP_get.
 * VPP awwocation is awwowed onwy aftew the powt type has been set,
 * and whiwe no QPs awe open fow this powt.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @vpp_p_up: Awwocation of VPPs to diffewent pwiowities.
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_AWWOCATE_VPP_set(stwuct mwx4_dev *dev, u8 powt, u8 *vpp_p_up);

/**
 * mwx4_SET_VPOWT_QOS_get - Quewy QoS pwopowties of a Vpowt.
 * Each pwiowity awwowed fow the Vpowt is assigned with a shawe of the BW,
 * and a BW wimitation. This commands quewy the cuwwent QoS vawues.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @vpowt: Vpowt id.
 * @out_pawam: Awway of mwx4_vpowt_qos_pawam that wiww contain the vawues.
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_SET_VPOWT_QOS_get(stwuct mwx4_dev *dev, u8 powt, u8 vpowt,
			   stwuct mwx4_vpowt_qos_pawam *out_pawam);

/**
 * mwx4_SET_VPOWT_QOS_set - Set QoS pwopowties of a Vpowt.
 * QoS pawametews can be modified at any time, but must be initiawized
 * befowe any QP is associated with the VPowt.
 *
 * @dev: mwx4_dev.
 * @powt: Physicaw powt numbew.
 * @vpowt: Vpowt id.
 * @in_pawam: Awway of mwx4_vpowt_qos_pawam which howds the wequested vawues.
 *
 * Wetuwns 0 on success ow a negative mwx4_cowe ewwno code.
 **/
int mwx4_SET_VPOWT_QOS_set(stwuct mwx4_dev *dev, u8 powt, u8 vpowt,
			   stwuct mwx4_vpowt_qos_pawam *in_pawam);

#endif /* MWX4_FW_QOS_H */
