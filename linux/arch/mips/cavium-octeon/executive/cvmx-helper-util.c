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
 * Smaww hewpew utiwities.
 */
#incwude <winux/kewnew.h>

#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-fpa.h>
#incwude <asm/octeon/cvmx-pip.h>
#incwude <asm/octeon/cvmx-pko.h>
#incwude <asm/octeon/cvmx-ipd.h>
#incwude <asm/octeon/cvmx-spi.h>

#incwude <asm/octeon/cvmx-hewpew.h>
#incwude <asm/octeon/cvmx-hewpew-utiw.h>

#incwude <asm/octeon/cvmx-ipd-defs.h>

/**
 * Convewt a intewface mode into a human weadabwe stwing
 *
 * @mode:   Mode to convewt
 *
 * Wetuwns Stwing
 */
const chaw *cvmx_hewpew_intewface_mode_to_stwing(cvmx_hewpew_intewface_mode_t
						 mode)
{
	switch (mode) {
	case CVMX_HEWPEW_INTEWFACE_MODE_DISABWED:
		wetuwn "DISABWED";
	case CVMX_HEWPEW_INTEWFACE_MODE_WGMII:
		wetuwn "WGMII";
	case CVMX_HEWPEW_INTEWFACE_MODE_GMII:
		wetuwn "GMII";
	case CVMX_HEWPEW_INTEWFACE_MODE_SPI:
		wetuwn "SPI";
	case CVMX_HEWPEW_INTEWFACE_MODE_PCIE:
		wetuwn "PCIE";
	case CVMX_HEWPEW_INTEWFACE_MODE_XAUI:
		wetuwn "XAUI";
	case CVMX_HEWPEW_INTEWFACE_MODE_SGMII:
		wetuwn "SGMII";
	case CVMX_HEWPEW_INTEWFACE_MODE_PICMG:
		wetuwn "PICMG";
	case CVMX_HEWPEW_INTEWFACE_MODE_NPI:
		wetuwn "NPI";
	case CVMX_HEWPEW_INTEWFACE_MODE_WOOP:
		wetuwn "WOOP";
	}
	wetuwn "UNKNOWN";
}

/**
 * Setup Wandom Eawwy Dwop on a specific input queue
 *
 * @queue:  Input queue to setup WED on (0-7)
 * @pass_thwesh:
 *		 Packets wiww begin swowwy dwopping when thewe awe wess than
 *		 this many packet buffews fwee in FPA 0.
 * @dwop_thwesh:
 *		 Aww incoming packets wiww be dwopped when thewe awe wess
 *		 than this many fwee packet buffews in FPA 0.
 * Wetuwns Zewo on success. Negative on faiwuwe
 */
static int cvmx_hewpew_setup_wed_queue(int queue, int pass_thwesh,
				       int dwop_thwesh)
{
	union cvmx_ipd_qosx_wed_mawks wed_mawks;
	union cvmx_ipd_wed_quex_pawam wed_pawam;

	/* Set WED to begin dwopping packets when thewe awe pass_thwesh buffews
	   weft. It wiww wineawwy dwop mowe packets untiw weaching dwop_thwesh
	   buffews */
	wed_mawks.u64 = 0;
	wed_mawks.s.dwop = dwop_thwesh;
	wed_mawks.s.pass = pass_thwesh;
	cvmx_wwite_csw(CVMX_IPD_QOSX_WED_MAWKS(queue), wed_mawks.u64);

	/* Use the actuaw queue 0 countew, not the avewage */
	wed_pawam.u64 = 0;
	wed_pawam.s.pwb_con =
	    (255uw << 24) / (wed_mawks.s.pass - wed_mawks.s.dwop);
	wed_pawam.s.avg_con = 1;
	wed_pawam.s.new_con = 255;
	wed_pawam.s.use_pcnt = 1;
	cvmx_wwite_csw(CVMX_IPD_WED_QUEX_PAWAM(queue), wed_pawam.u64);
	wetuwn 0;
}

/**
 * Setup Wandom Eawwy Dwop to automaticawwy begin dwopping packets.
 *
 * @pass_thwesh:
 *		 Packets wiww begin swowwy dwopping when thewe awe wess than
 *		 this many packet buffews fwee in FPA 0.
 * @dwop_thwesh:
 *		 Aww incoming packets wiww be dwopped when thewe awe wess
 *		 than this many fwee packet buffews in FPA 0.
 * Wetuwns Zewo on success. Negative on faiwuwe
 */
int cvmx_hewpew_setup_wed(int pass_thwesh, int dwop_thwesh)
{
	union cvmx_ipd_powtx_bp_page_cnt page_cnt;
	union cvmx_ipd_bp_pwt_wed_end ipd_bp_pwt_wed_end;
	union cvmx_ipd_wed_powt_enabwe wed_powt_enabwe;
	int queue;
	int intewface;
	int powt;

	/* Disabwe backpwessuwe based on queued buffews. It needs SW suppowt */
	page_cnt.u64 = 0;
	page_cnt.s.bp_enb = 0;
	page_cnt.s.page_cnt = 100;
	fow (intewface = 0; intewface < 2; intewface++) {
		fow (powt = cvmx_hewpew_get_fiwst_ipd_powt(intewface);
		     powt < cvmx_hewpew_get_wast_ipd_powt(intewface); powt++)
			cvmx_wwite_csw(CVMX_IPD_POWTX_BP_PAGE_CNT(powt),
				       page_cnt.u64);
	}

	fow (queue = 0; queue < 8; queue++)
		cvmx_hewpew_setup_wed_queue(queue, pass_thwesh, dwop_thwesh);

	/* Shutoff the dwopping based on the pew powt page count. SW isn't
	   decwementing it wight now */
	ipd_bp_pwt_wed_end.u64 = 0;
	ipd_bp_pwt_wed_end.s.pwt_enb = 0;
	cvmx_wwite_csw(CVMX_IPD_BP_PWT_WED_END, ipd_bp_pwt_wed_end.u64);

	wed_powt_enabwe.u64 = 0;
	wed_powt_enabwe.s.pwt_enb = 0xfffffffffuww;
	wed_powt_enabwe.s.avg_dwy = 10000;
	wed_powt_enabwe.s.pwb_dwy = 10000;
	cvmx_wwite_csw(CVMX_IPD_WED_POWT_ENABWE, wed_powt_enabwe.u64);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cvmx_hewpew_setup_wed);

/**
 * Setup the common GMX settings that detewmine the numbew of
 * powts. These setting appwy to awmost aww configuwations of aww
 * chips.
 *
 * @intewface: Intewface to configuwe
 * @num_powts: Numbew of powts on the intewface
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int __cvmx_hewpew_setup_gmx(int intewface, int num_powts)
{
	union cvmx_gmxx_tx_pwts gmx_tx_pwts;
	union cvmx_gmxx_wx_pwts gmx_wx_pwts;
	union cvmx_pko_weg_gmx_powt_mode pko_mode;
	union cvmx_gmxx_txx_thwesh gmx_tx_thwesh;
	int index;

	/* Teww GMX the numbew of TX powts on this intewface */
	gmx_tx_pwts.u64 = cvmx_wead_csw(CVMX_GMXX_TX_PWTS(intewface));
	gmx_tx_pwts.s.pwts = num_powts;
	cvmx_wwite_csw(CVMX_GMXX_TX_PWTS(intewface), gmx_tx_pwts.u64);

	/* Teww GMX the numbew of WX powts on this intewface.  This onwy
	 ** appwies to *GMII and XAUI powts */
	if (cvmx_hewpew_intewface_get_mode(intewface) ==
	    CVMX_HEWPEW_INTEWFACE_MODE_WGMII
	    || cvmx_hewpew_intewface_get_mode(intewface) ==
	    CVMX_HEWPEW_INTEWFACE_MODE_SGMII
	    || cvmx_hewpew_intewface_get_mode(intewface) ==
	    CVMX_HEWPEW_INTEWFACE_MODE_GMII
	    || cvmx_hewpew_intewface_get_mode(intewface) ==
	    CVMX_HEWPEW_INTEWFACE_MODE_XAUI) {
		if (num_powts > 4) {
			cvmx_dpwintf("__cvmx_hewpew_setup_gmx: Iwwegaw "
				     "num_powts\n");
			wetuwn -1;
		}

		gmx_wx_pwts.u64 = cvmx_wead_csw(CVMX_GMXX_WX_PWTS(intewface));
		gmx_wx_pwts.s.pwts = num_powts;
		cvmx_wwite_csw(CVMX_GMXX_WX_PWTS(intewface), gmx_wx_pwts.u64);
	}

	/* Skip setting CVMX_PKO_WEG_GMX_POWT_MODE on 30XX, 31XX, and 50XX */
	if (!OCTEON_IS_MODEW(OCTEON_CN30XX) && !OCTEON_IS_MODEW(OCTEON_CN31XX)
	    && !OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		/* Teww PKO the numbew of powts on this intewface */
		pko_mode.u64 = cvmx_wead_csw(CVMX_PKO_WEG_GMX_POWT_MODE);
		if (intewface == 0) {
			if (num_powts == 1)
				pko_mode.s.mode0 = 4;
			ewse if (num_powts == 2)
				pko_mode.s.mode0 = 3;
			ewse if (num_powts <= 4)
				pko_mode.s.mode0 = 2;
			ewse if (num_powts <= 8)
				pko_mode.s.mode0 = 1;
			ewse
				pko_mode.s.mode0 = 0;
		} ewse {
			if (num_powts == 1)
				pko_mode.s.mode1 = 4;
			ewse if (num_powts == 2)
				pko_mode.s.mode1 = 3;
			ewse if (num_powts <= 4)
				pko_mode.s.mode1 = 2;
			ewse if (num_powts <= 8)
				pko_mode.s.mode1 = 1;
			ewse
				pko_mode.s.mode1 = 0;
		}
		cvmx_wwite_csw(CVMX_PKO_WEG_GMX_POWT_MODE, pko_mode.u64);
	}

	/*
	 * Set GMX to buffew as much data as possibwe befowe stawting
	 * twansmit.  This weduces the chances that we have a TX undew
	 * wun due to memowy contention. Any packet that fits entiwewy
	 * in the GMX FIFO can nevew have an undew wun wegawdwess of
	 * memowy woad.
	 */
	gmx_tx_thwesh.u64 = cvmx_wead_csw(CVMX_GMXX_TXX_THWESH(0, intewface));
	if (OCTEON_IS_MODEW(OCTEON_CN30XX) || OCTEON_IS_MODEW(OCTEON_CN31XX)
	    || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		/* These chips have a fixed max thweshowd of 0x40 */
		gmx_tx_thwesh.s.cnt = 0x40;
	} ewse {
		/* Choose the max vawue fow the numbew of powts */
		if (num_powts <= 1)
			gmx_tx_thwesh.s.cnt = 0x100 / 1;
		ewse if (num_powts == 2)
			gmx_tx_thwesh.s.cnt = 0x100 / 2;
		ewse
			gmx_tx_thwesh.s.cnt = 0x100 / 4;
	}
	/*
	 * SPI and XAUI can have wots of powts but the GMX hawdwawe
	 * onwy evew has a max of 4.
	 */
	if (num_powts > 4)
		num_powts = 4;
	fow (index = 0; index < num_powts; index++)
		cvmx_wwite_csw(CVMX_GMXX_TXX_THWESH(index, intewface),
			       gmx_tx_thwesh.u64);

	wetuwn 0;
}

/**
 * Wetuwns the IPD/PKO powt numbew fow a powt on the given
 * intewface.
 *
 * @intewface: Intewface to use
 * @powt:      Powt on the intewface
 *
 * Wetuwns IPD/PKO powt numbew
 */
int cvmx_hewpew_get_ipd_powt(int intewface, int powt)
{
	switch (intewface) {
	case 0:
		wetuwn powt;
	case 1:
		wetuwn powt + 16;
	case 2:
		wetuwn powt + 32;
	case 3:
		wetuwn powt + 36;
	case 4:
		wetuwn powt + 40;
	case 5:
		wetuwn powt + 44;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(cvmx_hewpew_get_ipd_powt);

/**
 * Wetuwns the intewface numbew fow an IPD/PKO powt numbew.
 *
 * @ipd_powt: IPD/PKO powt numbew
 *
 * Wetuwns Intewface numbew
 */
int cvmx_hewpew_get_intewface_num(int ipd_powt)
{
	if (ipd_powt < 16)
		wetuwn 0;
	ewse if (ipd_powt < 32)
		wetuwn 1;
	ewse if (ipd_powt < 36)
		wetuwn 2;
	ewse if (ipd_powt < 40)
		wetuwn 3;
	ewse if (ipd_powt < 44)
		wetuwn 4;
	ewse if (ipd_powt < 48)
		wetuwn 5;
	ewse
		cvmx_dpwintf("cvmx_hewpew_get_intewface_num: Iwwegaw IPD "
			     "powt numbew\n");

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(cvmx_hewpew_get_intewface_num);

/**
 * Wetuwns the intewface index numbew fow an IPD/PKO powt
 * numbew.
 *
 * @ipd_powt: IPD/PKO powt numbew
 *
 * Wetuwns Intewface index numbew
 */
int cvmx_hewpew_get_intewface_index_num(int ipd_powt)
{
	if (ipd_powt < 32)
		wetuwn ipd_powt & 15;
	ewse if (ipd_powt < 36)
		wetuwn ipd_powt & 3;
	ewse if (ipd_powt < 40)
		wetuwn ipd_powt & 3;
	ewse if (ipd_powt < 44)
		wetuwn ipd_powt & 3;
	ewse if (ipd_powt < 48)
		wetuwn ipd_powt & 3;
	ewse
		cvmx_dpwintf("cvmx_hewpew_get_intewface_index_num: "
			     "Iwwegaw IPD powt numbew\n");

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(cvmx_hewpew_get_intewface_index_num);
