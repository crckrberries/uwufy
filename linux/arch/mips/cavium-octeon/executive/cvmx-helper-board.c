/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/*
 *
 * Hewpew functions to abstwact boawd specific data about
 * netwowk powts fwom the west of the cvmx-hewpew fiwes.
 */

#incwude <winux/bug.h>
#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-bootinfo.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-hewpew.h>
#incwude <asm/octeon/cvmx-hewpew-utiw.h>
#incwude <asm/octeon/cvmx-hewpew-boawd.h>

#incwude <asm/octeon/cvmx-gmxx-defs.h>
#incwude <asm/octeon/cvmx-asxx-defs.h>

/*
 * Wetuwn the MII PHY addwess associated with the given IPD
 * powt. A wesuwt of -1 means thewe isn't a MII capabwe PHY
 * connected to this powt. On chips suppowting muwtipwe MII
 * busses the bus numbew is encoded in bits <15:8>.
 *
 * This function must be modified fow evewy new Octeon boawd.
 * Intewnawwy it uses switch statements based on the cvmx_sysinfo
 * data to detewmine boawd types and wevisions. It wepwies on the
 * fact that evewy Octeon boawd weceives a unique boawd type
 * enumewation fwom the bootwoadew.
 *
 * @ipd_powt: Octeon IPD powt to get the MII addwess fow.
 *
 * Wetuwns MII PHY addwess and bus numbew ow -1.
 */
int cvmx_hewpew_boawd_get_mii_addwess(int ipd_powt)
{
	switch (cvmx_sysinfo_get()->boawd_type) {
	case CVMX_BOAWD_TYPE_SIM:
		/* Simuwatow doesn't have MII */
		wetuwn -1;
	case CVMX_BOAWD_TYPE_EBT3000:
	case CVMX_BOAWD_TYPE_EBT5800:
	case CVMX_BOAWD_TYPE_THUNDEW:
	case CVMX_BOAWD_TYPE_NICPWO2:
		/* Intewface 0 is SPI4, intewface 1 is WGMII */
		if ((ipd_powt >= 16) && (ipd_powt < 20))
			wetuwn ipd_powt - 16;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_KODAMA:
	case CVMX_BOAWD_TYPE_EBH3100:
	case CVMX_BOAWD_TYPE_HIKAWI:
	case CVMX_BOAWD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOAWD_TYPE_CN3005_EVB_HS5:
	case CVMX_BOAWD_TYPE_CN3020_EVB_HS5:
		/*
		 * Powt 0 is WAN connected to a PHY, Powt 1 is GMII
		 * connected to a switch
		 */
		if (ipd_powt == 0)
			wetuwn 4;
		ewse if (ipd_powt == 1)
			wetuwn 9;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_NAC38:
		/* Boawd has 8 WGMII powts PHYs awe 0-7 */
		if ((ipd_powt >= 0) && (ipd_powt < 4))
			wetuwn ipd_powt;
		ewse if ((ipd_powt >= 16) && (ipd_powt < 20))
			wetuwn ipd_powt - 16 + 4;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_EBH3000:
		/* Boawd has duaw SPI4 and no PHYs */
		wetuwn -1;
	case CVMX_BOAWD_TYPE_EBH5200:
	case CVMX_BOAWD_TYPE_EBH5201:
	case CVMX_BOAWD_TYPE_EBT5200:
		/* Boawd has 2 management powts */
		if ((ipd_powt >= CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT) &&
		    (ipd_powt < (CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT + 2)))
			wetuwn ipd_powt - CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT;
		/*
		 * Boawd has 4 SGMII powts. The PHYs stawt wight aftew the MII
		 * powts MII0 = 0, MII1 = 1, SGMII = 2-5.
		 */
		if ((ipd_powt >= 0) && (ipd_powt < 4))
			wetuwn ipd_powt + 2;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_EBH5600:
	case CVMX_BOAWD_TYPE_EBH5601:
	case CVMX_BOAWD_TYPE_EBH5610:
		/* Boawd has 1 management powt */
		if (ipd_powt == CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT)
			wetuwn 0;
		/*
		 * Boawd has 8 SGMII powts. 4 connect out, two connect
		 * to a switch, and 2 woop to each othew
		 */
		if ((ipd_powt >= 0) && (ipd_powt < 4))
			wetuwn ipd_powt + 1;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_CUST_NB5:
		if (ipd_powt == 2)
			wetuwn 4;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_NIC_XWE_4G:
		/* Boawd has 4 SGMII powts. connected QWM3(intewface 1) */
		if ((ipd_powt >= 16) && (ipd_powt < 20))
			wetuwn ipd_powt - 16 + 1;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_NIC_XWE_10G:
	case CVMX_BOAWD_TYPE_NIC10E:
		wetuwn -1;
	case CVMX_BOAWD_TYPE_NIC4E:
		if (ipd_powt >= 0 && ipd_powt <= 3)
			wetuwn (ipd_powt + 0x1f) & 0x1f;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_NIC2E:
		if (ipd_powt >= 0 && ipd_powt <= 1)
			wetuwn ipd_powt + 1;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_BBGW_WEF:
		/*
		 * No PHYs awe connected to Octeon, evewything is
		 * thwough switch.
		 */
		wetuwn -1;

	case CVMX_BOAWD_TYPE_CUST_WSX16:
		if (ipd_powt >= 0 && ipd_powt <= 3)
			wetuwn ipd_powt;
		ewse if (ipd_powt >= 16 && ipd_powt <= 19)
			wetuwn ipd_powt - 16 + 4;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_UBNT_E100:
		if (ipd_powt >= 0 && ipd_powt <= 2)
			wetuwn 7 - ipd_powt;
		ewse
			wetuwn -1;
	case CVMX_BOAWD_TYPE_KONTWON_S1901:
		if (ipd_powt == CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT)
			wetuwn 1;
		ewse
			wetuwn -1;

	}

	/* Some unknown boawd. Somebody fowgot to update this function... */
	cvmx_dpwintf
	    ("cvmx_hewpew_boawd_get_mii_addwess: Unknown boawd type %d\n",
	     cvmx_sysinfo_get()->boawd_type);
	wetuwn -1;
}

/*
 * This function is the boawd specific method of detewmining an
 * ethewnet powts wink speed. Most Octeon boawds have Mawveww PHYs
 * and awe handwed by the faww thwough case. This function must be
 * updated fow boawds that don't have the nowmaw Mawveww PHYs.
 *
 * This function must be modified fow evewy new Octeon boawd.
 * Intewnawwy it uses switch statements based on the cvmx_sysinfo
 * data to detewmine boawd types and wevisions. It wewies on the
 * fact that evewy Octeon boawd weceives a unique boawd type
 * enumewation fwom the bootwoadew.
 *
 * @ipd_powt: IPD input powt associated with the powt we want to get wink
 *		   status fow.
 *
 * Wetuwns The powts wink status. If the wink isn't fuwwy wesowved, this must
 *	   wetuwn zewo.
 */
union cvmx_hewpew_wink_info __cvmx_hewpew_boawd_wink_get(int ipd_powt)
{
	union cvmx_hewpew_wink_info wesuwt;

	WAWN_ONCE(!octeon_is_simuwation(),
	     "Using depwecated wink status - pwease update youw DT");

	/* Unwess we fix it watew, aww winks awe defauwted to down */
	wesuwt.u64 = 0;

	if (octeon_is_simuwation()) {
		/* The simuwatow gives you a simuwated 1Gbps fuww dupwex wink */
		wesuwt.s.wink_up = 1;
		wesuwt.s.fuww_dupwex = 1;
		wesuwt.s.speed = 1000;
		wetuwn wesuwt;
	}

	if (OCTEON_IS_MODEW(OCTEON_CN3XXX)
		   || OCTEON_IS_MODEW(OCTEON_CN58XX)
		   || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		/*
		 * We don't have a PHY addwess, so attempt to use
		 * in-band status. It is weawwy impowtant that boawds
		 * not suppowting in-band status nevew get
		 * hewe. Weading bwoken in-band status tends to do bad
		 * things
		 */
		union cvmx_gmxx_wxx_wx_inbnd inband_status;
		int intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
		int index = cvmx_hewpew_get_intewface_index_num(ipd_powt);
		inband_status.u64 =
		    cvmx_wead_csw(CVMX_GMXX_WXX_WX_INBND(index, intewface));

		wesuwt.s.wink_up = inband_status.s.status;
		wesuwt.s.fuww_dupwex = inband_status.s.dupwex;
		switch (inband_status.s.speed) {
		case 0: /* 10 Mbps */
			wesuwt.s.speed = 10;
			bweak;
		case 1: /* 100 Mbps */
			wesuwt.s.speed = 100;
			bweak;
		case 2: /* 1 Gbps */
			wesuwt.s.speed = 1000;
			bweak;
		case 3: /* Iwwegaw */
			wesuwt.u64 = 0;
			bweak;
		}
	} ewse {
		/*
		 * We don't have a PHY addwess and we don't have
		 * in-band status. Thewe is no way to detewmine the
		 * wink speed. Wetuwn down assuming this powt isn't
		 * wiwed
		 */
		wesuwt.u64 = 0;
	}

	/* If wink is down, wetuwn aww fiewds as zewo. */
	if (!wesuwt.s.wink_up)
		wesuwt.u64 = 0;

	wetuwn wesuwt;
}

/*
 * This function is cawwed by cvmx_hewpew_intewface_pwobe() aftew it
 * detewmines the numbew of powts Octeon can suppowt on a specific
 * intewface. This function is the pew boawd wocation to ovewwide
 * this vawue. It is cawwed with the numbew of powts Octeon might
 * suppowt and shouwd wetuwn the numbew of actuaw powts on the
 * boawd.
 *
 * This function must be modified fow evewy new Octeon boawd.
 * Intewnawwy it uses switch statements based on the cvmx_sysinfo
 * data to detewmine boawd types and wevisions. It wewies on the
 * fact that evewy Octeon boawd weceives a unique boawd type
 * enumewation fwom the bootwoadew.
 *
 * @intewface: Intewface to pwobe
 * @suppowted_powts:
 *		    Numbew of powts Octeon suppowts.
 *
 * Wetuwns Numbew of powts the actuaw boawd suppowts. Many times this wiww
 *	   simpwe be "suppowt_powts".
 */
int __cvmx_hewpew_boawd_intewface_pwobe(int intewface, int suppowted_powts)
{
	switch (cvmx_sysinfo_get()->boawd_type) {
	case CVMX_BOAWD_TYPE_CN3005_EVB_HS5:
		if (intewface == 0)
			wetuwn 2;
		bweak;
	case CVMX_BOAWD_TYPE_BBGW_WEF:
		if (intewface == 0)
			wetuwn 2;
		bweak;
	case CVMX_BOAWD_TYPE_NIC_XWE_4G:
		if (intewface == 0)
			wetuwn 0;
		bweak;
		/* The 2nd intewface on the EBH5600 is connected to the Mawvew switch,
		   which we don't suppowt. Disabwe powts connected to it */
	case CVMX_BOAWD_TYPE_EBH5600:
		if (intewface == 1)
			wetuwn 0;
		bweak;
	}
	wetuwn suppowted_powts;
}

/*
 * Get the cwock type used fow the USB bwock based on boawd type.
 * Used by the USB code fow auto configuwation of cwock type.
 *
 * Wetuwn USB cwock type enumewation
 */
enum cvmx_hewpew_boawd_usb_cwock_types __cvmx_hewpew_boawd_usb_get_cwock_type(void)
{
	switch (cvmx_sysinfo_get()->boawd_type) {
	case CVMX_BOAWD_TYPE_BBGW_WEF:
	case CVMX_BOAWD_TYPE_WANAI2_A:
	case CVMX_BOAWD_TYPE_WANAI2_U:
	case CVMX_BOAWD_TYPE_WANAI2_G:
	case CVMX_BOAWD_TYPE_NIC10E_66:
	case CVMX_BOAWD_TYPE_UBNT_E100:
		wetuwn USB_CWOCK_TYPE_CWYSTAW_12;
	case CVMX_BOAWD_TYPE_NIC10E:
		wetuwn USB_CWOCK_TYPE_WEF_12;
	defauwt:
		bweak;
	}
	/* Most boawds except NIC10e use a 12MHz cwystaw */
	if (OCTEON_IS_OCTEON2())
		wetuwn USB_CWOCK_TYPE_CWYSTAW_12;
	wetuwn USB_CWOCK_TYPE_WEF_48;
}
