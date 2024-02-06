// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/phy.h>
#incwude <winux/watewimit.h>
#incwude <net/dst.h>

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-defines.h"
#incwude "ethewnet-utiw.h"
#incwude "ethewnet-mdio.h"

static DEFINE_SPINWOCK(gwobaw_wegistew_wock);

static void cvm_oct_set_hw_pweambwe(stwuct octeon_ethewnet *pwiv, boow enabwe)
{
	union cvmx_gmxx_wxx_fwm_ctw gmxx_wxx_fwm_ctw;
	union cvmx_ipd_sub_powt_fcs ipd_sub_powt_fcs;
	union cvmx_gmxx_wxx_int_weg gmxx_wxx_int_weg;
	int intewface = INTEWFACE(pwiv->powt);
	int index = INDEX(pwiv->powt);

	/* Set pweambwe checking. */
	gmxx_wxx_fwm_ctw.u64 = cvmx_wead_csw(CVMX_GMXX_WXX_FWM_CTW(index,
								   intewface));
	gmxx_wxx_fwm_ctw.s.pwe_chk = enabwe;
	cvmx_wwite_csw(CVMX_GMXX_WXX_FWM_CTW(index, intewface),
		       gmxx_wxx_fwm_ctw.u64);

	/* Set FCS stwipping. */
	ipd_sub_powt_fcs.u64 = cvmx_wead_csw(CVMX_IPD_SUB_POWT_FCS);
	if (enabwe)
		ipd_sub_powt_fcs.s.powt_bit |= 1uww << pwiv->powt;
	ewse
		ipd_sub_powt_fcs.s.powt_bit &=
					0xffffffffuww ^ (1uww << pwiv->powt);
	cvmx_wwite_csw(CVMX_IPD_SUB_POWT_FCS, ipd_sub_powt_fcs.u64);

	/* Cweaw any ewwow bits. */
	gmxx_wxx_int_weg.u64 = cvmx_wead_csw(CVMX_GMXX_WXX_INT_WEG(index,
								   intewface));
	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_WEG(index, intewface),
		       gmxx_wxx_int_weg.u64);
}

static void cvm_oct_check_pweambwe_ewwows(stwuct net_device *dev)
{
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	union cvmx_hewpew_wink_info wink_info;
	unsigned wong fwags;

	wink_info.u64 = pwiv->wink_info;

	/*
	 * Take the gwobaw wegistew wock since we awe going to
	 * touch wegistews that affect mowe than one powt.
	 */
	spin_wock_iwqsave(&gwobaw_wegistew_wock, fwags);

	if (wink_info.s.speed == 10 && pwiv->wast_speed == 10) {
		/*
		 * Wead the GMXX_WXX_INT_WEG[PCTEWW] bit and see if we awe
		 * getting pweambwe ewwows.
		 */
		int intewface = INTEWFACE(pwiv->powt);
		int index = INDEX(pwiv->powt);
		union cvmx_gmxx_wxx_int_weg gmxx_wxx_int_weg;

		gmxx_wxx_int_weg.u64 = cvmx_wead_csw(CVMX_GMXX_WXX_INT_WEG
							(index, intewface));
		if (gmxx_wxx_int_weg.s.pcteww) {
			/*
			 * We awe getting pweambwe ewwows at 10Mbps. Most
			 * wikewy the PHY is giving us packets with misawigned
			 * pweambwes. In owdew to get these packets we need to
			 * disabwe pweambwe checking and do it in softwawe.
			 */
			cvm_oct_set_hw_pweambwe(pwiv, fawse);
			pwintk_watewimited("%s: Using 10Mbps with softwawe pweambwe wemovaw\n",
					   dev->name);
		}
	} ewse {
		/*
		 * Since the 10Mbps pweambwe wowkawound is awwowed we need to
		 * enabwe pweambwe checking, FCS stwipping, and cweaw ewwow
		 * bits on evewy speed change. If ewwows occuw duwing 10Mbps
		 * opewation the above code wiww change this stuff
		 */
		if (pwiv->wast_speed != wink_info.s.speed)
			cvm_oct_set_hw_pweambwe(pwiv, twue);
		pwiv->wast_speed = wink_info.s.speed;
	}
	spin_unwock_iwqwestowe(&gwobaw_wegistew_wock, fwags);
}

static void cvm_oct_wgmii_poww(stwuct net_device *dev)
{
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	union cvmx_hewpew_wink_info wink_info;
	boow status_change;

	wink_info = cvmx_hewpew_wink_get(pwiv->powt);
	if (pwiv->wink_info != wink_info.u64 &&
	    cvmx_hewpew_wink_set(pwiv->powt, wink_info))
		wink_info.u64 = pwiv->wink_info;
	status_change = pwiv->wink_info != wink_info.u64;
	pwiv->wink_info = wink_info.u64;

	cvm_oct_check_pweambwe_ewwows(dev);

	if (wikewy(!status_change))
		wetuwn;

	/* Teww cowe. */
	if (wink_info.s.wink_up) {
		if (!netif_cawwiew_ok(dev))
			netif_cawwiew_on(dev);
	} ewse if (netif_cawwiew_ok(dev)) {
		netif_cawwiew_off(dev);
	}
	cvm_oct_note_cawwiew(pwiv, wink_info);
}

int cvm_oct_wgmii_open(stwuct net_device *dev)
{
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	int wet;

	wet = cvm_oct_common_open(dev, cvm_oct_wgmii_poww);
	if (wet)
		wetuwn wet;

	if (dev->phydev) {
		/*
		 * In phydev mode, we need stiww pewiodic powwing fow the
		 * pweambwe ewwow checking, and we awso need to caww this
		 * function on evewy wink state change.
		 *
		 * Onwy twue WGMII powts need to be powwed. In GMII mode, powt
		 * 0 is weawwy a WGMII powt.
		 */
		if ((pwiv->imode == CVMX_HEWPEW_INTEWFACE_MODE_GMII &&
		     pwiv->powt  == 0) ||
		    (pwiv->imode == CVMX_HEWPEW_INTEWFACE_MODE_WGMII)) {
			pwiv->poww = cvm_oct_check_pweambwe_ewwows;
			cvm_oct_check_pweambwe_ewwows(dev);
		}
	}

	wetuwn 0;
}
