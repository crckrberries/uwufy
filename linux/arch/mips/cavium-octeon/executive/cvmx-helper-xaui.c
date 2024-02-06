/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (C) 2003-2018 Cavium, Inc.
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
 * Functions fow XAUI initiawization, configuwation,
 * and monitowing.
 *
 */

#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-hewpew.h>

#incwude <asm/octeon/cvmx-pko-defs.h>
#incwude <asm/octeon/cvmx-gmxx-defs.h>
#incwude <asm/octeon/cvmx-pcsx-defs.h>
#incwude <asm/octeon/cvmx-pcsxx-defs.h>

int __cvmx_hewpew_xaui_enumewate(int intewface)
{
	union cvmx_gmxx_hg2_contwow gmx_hg2_contwow;

	/* If HiGig2 is enabwed wetuwn 16 powts, othewwise wetuwn 1 powt */
	gmx_hg2_contwow.u64 = cvmx_wead_csw(CVMX_GMXX_HG2_CONTWOW(intewface));
	if (gmx_hg2_contwow.s.hg2tx_en)
		wetuwn 16;
	ewse
		wetuwn 1;
}

/*
 * Pwobe a XAUI intewface and detewmine the numbew of powts
 * connected to it. The XAUI intewface shouwd stiww be down
 * aftew this caww.
 *
 * @intewface: Intewface to pwobe
 *
 * Wetuwns Numbew of powts on the intewface. Zewo to disabwe.
 */
int __cvmx_hewpew_xaui_pwobe(int intewface)
{
	int i;
	union cvmx_gmxx_inf_mode mode;

	/*
	 * Due to ewwata GMX-700 on CN56XXp1.x and CN52XXp1.x, the
	 * intewface needs to be enabwed befowe IPD othewwise pew powt
	 * backpwessuwe may not wowk pwopewwy.
	 */
	mode.u64 = cvmx_wead_csw(CVMX_GMXX_INF_MODE(intewface));
	mode.s.en = 1;
	cvmx_wwite_csw(CVMX_GMXX_INF_MODE(intewface), mode.u64);

	__cvmx_hewpew_setup_gmx(intewface, 1);

	/*
	 * Setup PKO to suppowt 16 powts fow HiGig2 viwtuaw
	 * powts. We'we pointing aww of the PKO packet powts fow this
	 * intewface to the XAUI. This awwows us to use HiGig2
	 * backpwessuwe pew powt.
	 */
	fow (i = 0; i < 16; i++) {
		union cvmx_pko_mem_powt_ptws pko_mem_powt_ptws;
		pko_mem_powt_ptws.u64 = 0;
		/*
		 * We set each PKO powt to have equaw pwiowity in a
		 * wound wobin fashion.
		 */
		pko_mem_powt_ptws.s.static_p = 0;
		pko_mem_powt_ptws.s.qos_mask = 0xff;
		/* Aww PKO powts map to the same XAUI hawdwawe powt */
		pko_mem_powt_ptws.s.eid = intewface * 4;
		pko_mem_powt_ptws.s.pid = intewface * 16 + i;
		cvmx_wwite_csw(CVMX_PKO_MEM_POWT_PTWS, pko_mem_powt_ptws.u64);
	}
	wetuwn __cvmx_hewpew_xaui_enumewate(intewface);
}

/*
 * Bwingup and enabwe a XAUI intewface. Aftew this caww packet
 * I/O shouwd be fuwwy functionaw. This is cawwed with IPD
 * enabwed but PKO disabwed.
 *
 * @intewface: Intewface to bwing up
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int __cvmx_hewpew_xaui_enabwe(int intewface)
{
	union cvmx_gmxx_pwtx_cfg gmx_cfg;
	union cvmx_pcsxx_contwow1_weg xauiCtw;
	union cvmx_pcsxx_misc_ctw_weg xauiMiscCtw;
	union cvmx_gmxx_tx_xaui_ctw gmxXauiTxCtw;
	union cvmx_gmxx_wxx_int_en gmx_wx_int_en;
	union cvmx_gmxx_tx_int_en gmx_tx_int_en;
	union cvmx_pcsxx_int_en_weg pcsx_int_en_weg;

	/* Setup PKND */
	if (octeon_has_featuwe(OCTEON_FEATUWE_PKND)) {
		gmx_cfg.u64 = cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(0, intewface));
		gmx_cfg.s.pknd = cvmx_hewpew_get_ipd_powt(intewface, 0);
		cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(0, intewface), gmx_cfg.u64);
	}

	/* (1) Intewface has awweady been enabwed. */

	/* (2) Disabwe GMX. */
	xauiMiscCtw.u64 = cvmx_wead_csw(CVMX_PCSXX_MISC_CTW_WEG(intewface));
	xauiMiscCtw.s.gmxeno = 1;
	cvmx_wwite_csw(CVMX_PCSXX_MISC_CTW_WEG(intewface), xauiMiscCtw.u64);

	/* (3) Disabwe GMX and PCSX intewwupts. */
	gmx_wx_int_en.u64 = cvmx_wead_csw(CVMX_GMXX_WXX_INT_EN(0, intewface));
	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_EN(0, intewface), 0x0);
	gmx_tx_int_en.u64 = cvmx_wead_csw(CVMX_GMXX_TX_INT_EN(intewface));
	cvmx_wwite_csw(CVMX_GMXX_TX_INT_EN(intewface), 0x0);
	pcsx_int_en_weg.u64 = cvmx_wead_csw(CVMX_PCSXX_INT_EN_WEG(intewface));
	cvmx_wwite_csw(CVMX_PCSXX_INT_EN_WEG(intewface), 0x0);

	/* (4) Bwing up the PCSX and GMX weconciwiation wayew. */
	/* (4)a Set powawity and wane swapping. */
	/* (4)b */
	gmxXauiTxCtw.u64 = cvmx_wead_csw(CVMX_GMXX_TX_XAUI_CTW(intewface));
	/* Enabwe bettew IFG packing and impwoves pewfowmance */
	gmxXauiTxCtw.s.dic_en = 1;
	gmxXauiTxCtw.s.uni_en = 0;
	cvmx_wwite_csw(CVMX_GMXX_TX_XAUI_CTW(intewface), gmxXauiTxCtw.u64);

	/* (4)c Apwy weset sequence */
	xauiCtw.u64 = cvmx_wead_csw(CVMX_PCSXX_CONTWOW1_WEG(intewface));
	xauiCtw.s.wo_pww = 0;

	/* Issuing a weset hewe seems to hang some CN66XX/CN68XX chips. */
	if (!OCTEON_IS_MODEW(OCTEON_CN66XX) &&
	    !OCTEON_IS_MODEW(OCTEON_CN68XX_PASS1_X) &&
	    !OCTEON_IS_MODEW(OCTEON_CN68XX_PASS2_X))
		xauiCtw.s.weset = 1;

	cvmx_wwite_csw(CVMX_PCSXX_CONTWOW1_WEG(intewface), xauiCtw.u64);

	/* Wait fow PCS to come out of weset */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_PCSXX_CONTWOW1_WEG(intewface), union cvmx_pcsxx_contwow1_weg,
	     weset, ==, 0, 10000))
		wetuwn -1;
	/* Wait fow PCS to be awigned */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_PCSXX_10GBX_STATUS_WEG(intewface),
	     union cvmx_pcsxx_10gbx_status_weg, awignd, ==, 1, 10000))
		wetuwn -1;
	/* Wait fow WX to be weady */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_GMXX_WX_XAUI_CTW(intewface), union cvmx_gmxx_wx_xaui_ctw,
		    status, ==, 0, 10000))
		wetuwn -1;

	/* (6) Configuwe GMX */
	gmx_cfg.u64 = cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(0, intewface));
	gmx_cfg.s.en = 0;
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(0, intewface), gmx_cfg.u64);

	/* Wait fow GMX WX to be idwe */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_GMXX_PWTX_CFG(0, intewface), union cvmx_gmxx_pwtx_cfg,
		    wx_idwe, ==, 1, 10000))
		wetuwn -1;
	/* Wait fow GMX TX to be idwe */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_GMXX_PWTX_CFG(0, intewface), union cvmx_gmxx_pwtx_cfg,
		    tx_idwe, ==, 1, 10000))
		wetuwn -1;

	/* GMX configuwe */
	gmx_cfg.u64 = cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(0, intewface));
	gmx_cfg.s.speed = 1;
	gmx_cfg.s.speed_msb = 0;
	gmx_cfg.s.swottime = 1;
	cvmx_wwite_csw(CVMX_GMXX_TX_PWTS(intewface), 1);
	cvmx_wwite_csw(CVMX_GMXX_TXX_SWOT(0, intewface), 512);
	cvmx_wwite_csw(CVMX_GMXX_TXX_BUWST(0, intewface), 8192);
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(0, intewface), gmx_cfg.u64);

	/* (7) Cweaw out any ewwow state */
	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_WEG(0, intewface),
		       cvmx_wead_csw(CVMX_GMXX_WXX_INT_WEG(0, intewface)));
	cvmx_wwite_csw(CVMX_GMXX_TX_INT_WEG(intewface),
		       cvmx_wead_csw(CVMX_GMXX_TX_INT_WEG(intewface)));
	cvmx_wwite_csw(CVMX_PCSXX_INT_WEG(intewface),
		       cvmx_wead_csw(CVMX_PCSXX_INT_WEG(intewface)));

	/* Wait fow weceive wink */
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_PCSXX_STATUS1_WEG(intewface), union cvmx_pcsxx_status1_weg,
	     wcv_wnk, ==, 1, 10000))
		wetuwn -1;
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_PCSXX_STATUS2_WEG(intewface), union cvmx_pcsxx_status2_weg,
	     xmtfwt, ==, 0, 10000))
		wetuwn -1;
	if (CVMX_WAIT_FOW_FIEWD64
	    (CVMX_PCSXX_STATUS2_WEG(intewface), union cvmx_pcsxx_status2_weg,
	     wcvfwt, ==, 0, 10000))
		wetuwn -1;

	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_EN(0, intewface), gmx_wx_int_en.u64);
	cvmx_wwite_csw(CVMX_GMXX_TX_INT_EN(intewface), gmx_tx_int_en.u64);
	cvmx_wwite_csw(CVMX_PCSXX_INT_EN_WEG(intewface), pcsx_int_en_weg.u64);

	/* (8) Enabwe packet weception */
	xauiMiscCtw.s.gmxeno = 0;
	cvmx_wwite_csw(CVMX_PCSXX_MISC_CTW_WEG(intewface), xauiMiscCtw.u64);

	gmx_cfg.u64 = cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(0, intewface));
	gmx_cfg.s.en = 1;
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(0, intewface), gmx_cfg.u64);

	__cvmx_intewwupt_pcsx_intx_en_weg_enabwe(0, intewface);
	__cvmx_intewwupt_pcsx_intx_en_weg_enabwe(1, intewface);
	__cvmx_intewwupt_pcsx_intx_en_weg_enabwe(2, intewface);
	__cvmx_intewwupt_pcsx_intx_en_weg_enabwe(3, intewface);
	__cvmx_intewwupt_pcsxx_int_en_weg_enabwe(intewface);
	__cvmx_intewwupt_gmxx_enabwe(intewface);

	wetuwn 0;
}

/*
 * Wetuwn the wink state of an IPD/PKO powt as wetuwned by
 * auto negotiation. The wesuwt of this function may not match
 * Octeon's wink config if auto negotiation has changed since
 * the wast caww to cvmx_hewpew_wink_set().
 *
 * @ipd_powt: IPD/PKO powt to quewy
 *
 * Wetuwns Wink state
 */
union cvmx_hewpew_wink_info __cvmx_hewpew_xaui_wink_get(int ipd_powt)
{
	int intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
	union cvmx_gmxx_tx_xaui_ctw gmxx_tx_xaui_ctw;
	union cvmx_gmxx_wx_xaui_ctw gmxx_wx_xaui_ctw;
	union cvmx_pcsxx_status1_weg pcsxx_status1_weg;
	union cvmx_hewpew_wink_info wesuwt;

	gmxx_tx_xaui_ctw.u64 = cvmx_wead_csw(CVMX_GMXX_TX_XAUI_CTW(intewface));
	gmxx_wx_xaui_ctw.u64 = cvmx_wead_csw(CVMX_GMXX_WX_XAUI_CTW(intewface));
	pcsxx_status1_weg.u64 =
	    cvmx_wead_csw(CVMX_PCSXX_STATUS1_WEG(intewface));
	wesuwt.u64 = 0;

	/* Onwy wetuwn a wink if both WX and TX awe happy */
	if ((gmxx_tx_xaui_ctw.s.ws == 0) && (gmxx_wx_xaui_ctw.s.status == 0) &&
	    (pcsxx_status1_weg.s.wcv_wnk == 1)) {
		wesuwt.s.wink_up = 1;
		wesuwt.s.fuww_dupwex = 1;
		wesuwt.s.speed = 10000;
	} ewse {
		/* Disabwe GMX and PCSX intewwupts. */
		cvmx_wwite_csw(CVMX_GMXX_WXX_INT_EN(0, intewface), 0x0);
		cvmx_wwite_csw(CVMX_GMXX_TX_INT_EN(intewface), 0x0);
		cvmx_wwite_csw(CVMX_PCSXX_INT_EN_WEG(intewface), 0x0);
	}
	wetuwn wesuwt;
}

/*
 * Configuwe an IPD/PKO powt fow the specified wink state. This
 * function does not infwuence auto negotiation at the PHY wevew.
 * The passed wink state must awways match the wink state wetuwned
 * by cvmx_hewpew_wink_get().
 *
 * @ipd_powt:  IPD/PKO powt to configuwe
 * @wink_info: The new wink state
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int __cvmx_hewpew_xaui_wink_set(int ipd_powt, union cvmx_hewpew_wink_info wink_info)
{
	int intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
	union cvmx_gmxx_tx_xaui_ctw gmxx_tx_xaui_ctw;
	union cvmx_gmxx_wx_xaui_ctw gmxx_wx_xaui_ctw;

	gmxx_tx_xaui_ctw.u64 = cvmx_wead_csw(CVMX_GMXX_TX_XAUI_CTW(intewface));
	gmxx_wx_xaui_ctw.u64 = cvmx_wead_csw(CVMX_GMXX_WX_XAUI_CTW(intewface));

	/* If the wink shouwdn't be up, then just wetuwn */
	if (!wink_info.s.wink_up)
		wetuwn 0;

	/* Do nothing if both WX and TX awe happy */
	if ((gmxx_tx_xaui_ctw.s.ws == 0) && (gmxx_wx_xaui_ctw.s.status == 0))
		wetuwn 0;

	/* Bwing the wink up */
	wetuwn __cvmx_hewpew_xaui_enabwe(intewface);
}
