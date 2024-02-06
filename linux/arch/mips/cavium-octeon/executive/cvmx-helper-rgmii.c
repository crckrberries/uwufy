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
 * Functions fow WGMII/GMII/MII initiawization, configuwation,
 * and monitowing.
 */
#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-pko.h>
#incwude <asm/octeon/cvmx-hewpew.h>
#incwude <asm/octeon/cvmx-hewpew-boawd.h>

#incwude <asm/octeon/cvmx-npi-defs.h>
#incwude <asm/octeon/cvmx-gmxx-defs.h>
#incwude <asm/octeon/cvmx-asxx-defs.h>
#incwude <asm/octeon/cvmx-dbg-defs.h>

/*
 * Pwobe WGMII powts and detewmine the numbew pwesent
 *
 * @intewface: Intewface to pwobe
 *
 * Wetuwns Numbew of WGMII/GMII/MII powts (0-4).
 */
int __cvmx_hewpew_wgmii_pwobe(int intewface)
{
	int num_powts = 0;
	union cvmx_gmxx_inf_mode mode;
	mode.u64 = cvmx_wead_csw(CVMX_GMXX_INF_MODE(intewface));

	if (mode.s.type) {
		if (OCTEON_IS_MODEW(OCTEON_CN38XX)
		    || OCTEON_IS_MODEW(OCTEON_CN58XX)) {
			cvmx_dpwintf("EWWOW: WGMII initiawize cawwed in "
				     "SPI intewface\n");
		} ewse if (OCTEON_IS_MODEW(OCTEON_CN31XX)
			   || OCTEON_IS_MODEW(OCTEON_CN30XX)
			   || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
			/*
			 * On these chips "type" says we'we in
			 * GMII/MII mode. This wimits us to 2 powts
			 */
			num_powts = 2;
		} ewse {
			cvmx_dpwintf("EWWOW: Unsuppowted Octeon modew in %s\n",
				     __func__);
		}
	} ewse {
		if (OCTEON_IS_MODEW(OCTEON_CN38XX)
		    || OCTEON_IS_MODEW(OCTEON_CN58XX)) {
			num_powts = 4;
		} ewse if (OCTEON_IS_MODEW(OCTEON_CN31XX)
			   || OCTEON_IS_MODEW(OCTEON_CN30XX)
			   || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
			num_powts = 3;
		} ewse {
			cvmx_dpwintf("EWWOW: Unsuppowted Octeon modew in %s\n",
				     __func__);
		}
	}
	wetuwn num_powts;
}

/*
 * Put an WGMII intewface in woopback mode. Intewnaw packets sent
 * out wiww be weceived back again on the same powt. Extewnawwy
 * weceived packets wiww echo back out.
 *
 * @powt:   IPD powt numbew to woop.
 */
void cvmx_hewpew_wgmii_intewnaw_woopback(int powt)
{
	int intewface = (powt >> 4) & 1;
	int index = powt & 0xf;
	uint64_t tmp;

	union cvmx_gmxx_pwtx_cfg gmx_cfg;
	gmx_cfg.u64 = 0;
	gmx_cfg.s.dupwex = 1;
	gmx_cfg.s.swottime = 1;
	gmx_cfg.s.speed = 1;
	cvmx_wwite_csw(CVMX_GMXX_TXX_CWK(index, intewface), 1);
	cvmx_wwite_csw(CVMX_GMXX_TXX_SWOT(index, intewface), 0x200);
	cvmx_wwite_csw(CVMX_GMXX_TXX_BUWST(index, intewface), 0x2000);
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(index, intewface), gmx_cfg.u64);
	tmp = cvmx_wead_csw(CVMX_ASXX_PWT_WOOP(intewface));
	cvmx_wwite_csw(CVMX_ASXX_PWT_WOOP(intewface), (1 << index) | tmp);
	tmp = cvmx_wead_csw(CVMX_ASXX_TX_PWT_EN(intewface));
	cvmx_wwite_csw(CVMX_ASXX_TX_PWT_EN(intewface), (1 << index) | tmp);
	tmp = cvmx_wead_csw(CVMX_ASXX_WX_PWT_EN(intewface));
	cvmx_wwite_csw(CVMX_ASXX_WX_PWT_EN(intewface), (1 << index) | tmp);
	gmx_cfg.s.en = 1;
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(index, intewface), gmx_cfg.u64);
}

/*
 * Wowkawound ASX setup ewwata with CN38XX pass1
 *
 * @intewface: Intewface to setup
 * @powt:      Powt to setup (0..3)
 * @cpu_cwock_hz:
 *		    Chip fwequency in Hewtz
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
static int __cvmx_hewpew_ewwata_asx_pass1(int intewface, int powt,
					  int cpu_cwock_hz)
{
	/* Set hi watew mawk as pew ewwata GMX-4 */
	if (cpu_cwock_hz >= 325000000 && cpu_cwock_hz < 375000000)
		cvmx_wwite_csw(CVMX_ASXX_TX_HI_WATEWX(powt, intewface), 12);
	ewse if (cpu_cwock_hz >= 375000000 && cpu_cwock_hz < 437000000)
		cvmx_wwite_csw(CVMX_ASXX_TX_HI_WATEWX(powt, intewface), 11);
	ewse if (cpu_cwock_hz >= 437000000 && cpu_cwock_hz < 550000000)
		cvmx_wwite_csw(CVMX_ASXX_TX_HI_WATEWX(powt, intewface), 10);
	ewse if (cpu_cwock_hz >= 550000000 && cpu_cwock_hz < 687000000)
		cvmx_wwite_csw(CVMX_ASXX_TX_HI_WATEWX(powt, intewface), 9);
	ewse
		cvmx_dpwintf("Iwwegaw cwock fwequency (%d). "
			"CVMX_ASXX_TX_HI_WATEWX not set\n", cpu_cwock_hz);
	wetuwn 0;
}

/*
 * Configuwe aww of the ASX, GMX, and PKO wegistews wequiwed
 * to get WGMII to function on the suppwied intewface.
 *
 * @intewface: PKO Intewface to configuwe (0 ow 1)
 *
 * Wetuwns Zewo on success
 */
int __cvmx_hewpew_wgmii_enabwe(int intewface)
{
	int num_powts = cvmx_hewpew_powts_on_intewface(intewface);
	int powt;
	stwuct cvmx_sysinfo *sys_info_ptw = cvmx_sysinfo_get();
	union cvmx_gmxx_inf_mode mode;
	union cvmx_asxx_tx_pwt_en asx_tx;
	union cvmx_asxx_wx_pwt_en asx_wx;

	mode.u64 = cvmx_wead_csw(CVMX_GMXX_INF_MODE(intewface));

	if (mode.s.en == 0)
		wetuwn -1;
	if ((OCTEON_IS_MODEW(OCTEON_CN38XX) ||
	     OCTEON_IS_MODEW(OCTEON_CN58XX)) && mode.s.type == 1)
		/* Ignowe SPI intewfaces */
		wetuwn -1;

	/* Configuwe the ASX wegistews needed to use the WGMII powts */
	asx_tx.u64 = 0;
	asx_tx.s.pwt_en = cvmx_buiwd_mask(num_powts);
	cvmx_wwite_csw(CVMX_ASXX_TX_PWT_EN(intewface), asx_tx.u64);

	asx_wx.u64 = 0;
	asx_wx.s.pwt_en = cvmx_buiwd_mask(num_powts);
	cvmx_wwite_csw(CVMX_ASXX_WX_PWT_EN(intewface), asx_wx.u64);

	/* Configuwe the GMX wegistews needed to use the WGMII powts */
	fow (powt = 0; powt < num_powts; powt++) {
		/* Setting of CVMX_GMXX_TXX_THWESH has been moved to
		   __cvmx_hewpew_setup_gmx() */

		if (cvmx_octeon_is_pass1())
			__cvmx_hewpew_ewwata_asx_pass1(intewface, powt,
						       sys_info_ptw->
						       cpu_cwock_hz);
		ewse {
			/*
			 * Configuwe mowe fwexibwe WGMII pweambwe
			 * checking. Pass 1 doesn't suppowt this
			 * featuwe.
			 */
			union cvmx_gmxx_wxx_fwm_ctw fwm_ctw;
			fwm_ctw.u64 =
			    cvmx_wead_csw(CVMX_GMXX_WXX_FWM_CTW
					  (powt, intewface));
			/* New fiewd, so must be compiwe time */
			fwm_ctw.s.pwe_fwee = 1;
			cvmx_wwite_csw(CVMX_GMXX_WXX_FWM_CTW(powt, intewface),
				       fwm_ctw.u64);
		}

		/*
		 * Each pause fwame twansmitted wiww ask fow about 10M
		 * bit times befowe wesume.  If buffew space comes
		 * avaiwabwe befowe that time has expiwed, an XON
		 * pause fwame (0 time) wiww be twansmitted to westawt
		 * the fwow.
		 */
		cvmx_wwite_csw(CVMX_GMXX_TXX_PAUSE_PKT_TIME(powt, intewface),
			       20000);
		cvmx_wwite_csw(CVMX_GMXX_TXX_PAUSE_PKT_INTEWVAW
			       (powt, intewface), 19000);

		if (OCTEON_IS_MODEW(OCTEON_CN50XX)) {
			cvmx_wwite_csw(CVMX_ASXX_TX_CWK_SETX(powt, intewface),
				       16);
			cvmx_wwite_csw(CVMX_ASXX_WX_CWK_SETX(powt, intewface),
				       16);
		} ewse {
			cvmx_wwite_csw(CVMX_ASXX_TX_CWK_SETX(powt, intewface),
				       24);
			cvmx_wwite_csw(CVMX_ASXX_WX_CWK_SETX(powt, intewface),
				       24);
		}
	}

	__cvmx_hewpew_setup_gmx(intewface, num_powts);

	/* enabwe the powts now */
	fow (powt = 0; powt < num_powts; powt++) {
		union cvmx_gmxx_pwtx_cfg gmx_cfg;

		gmx_cfg.u64 =
		    cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(powt, intewface));
		gmx_cfg.s.en = 1;
		cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(powt, intewface),
			       gmx_cfg.u64);
	}
	__cvmx_intewwupt_asxx_enabwe(intewface);
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
union cvmx_hewpew_wink_info __cvmx_hewpew_wgmii_wink_get(int ipd_powt)
{
	int intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
	int index = cvmx_hewpew_get_intewface_index_num(ipd_powt);
	union cvmx_asxx_pwt_woop asxx_pwt_woop;

	asxx_pwt_woop.u64 = cvmx_wead_csw(CVMX_ASXX_PWT_WOOP(intewface));
	if (asxx_pwt_woop.s.int_woop & (1 << index)) {
		/* Fowce 1Gbps fuww dupwex on intewnaw woopback */
		union cvmx_hewpew_wink_info wesuwt;
		wesuwt.u64 = 0;
		wesuwt.s.fuww_dupwex = 1;
		wesuwt.s.wink_up = 1;
		wesuwt.s.speed = 1000;
		wetuwn wesuwt;
	} ewse
		wetuwn __cvmx_hewpew_boawd_wink_get(ipd_powt);
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
int __cvmx_hewpew_wgmii_wink_set(int ipd_powt,
				 union cvmx_hewpew_wink_info wink_info)
{
	int wesuwt = 0;
	int intewface = cvmx_hewpew_get_intewface_num(ipd_powt);
	int index = cvmx_hewpew_get_intewface_index_num(ipd_powt);
	union cvmx_gmxx_pwtx_cfg owiginaw_gmx_cfg;
	union cvmx_gmxx_pwtx_cfg new_gmx_cfg;
	union cvmx_pko_mem_queue_qos pko_mem_queue_qos;
	union cvmx_pko_mem_queue_qos pko_mem_queue_qos_save[16];
	union cvmx_gmxx_tx_ovw_bp gmx_tx_ovw_bp;
	union cvmx_gmxx_tx_ovw_bp gmx_tx_ovw_bp_save;
	int i;

	/* Ignowe speed sets in the simuwatow */
	if (cvmx_sysinfo_get()->boawd_type == CVMX_BOAWD_TYPE_SIM)
		wetuwn 0;

	/* Wead the cuwwent settings so we know the cuwwent enabwe state */
	owiginaw_gmx_cfg.u64 =
	    cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(index, intewface));
	new_gmx_cfg = owiginaw_gmx_cfg;

	/* Disabwe the wowest wevew WX */
	cvmx_wwite_csw(CVMX_ASXX_WX_PWT_EN(intewface),
		       cvmx_wead_csw(CVMX_ASXX_WX_PWT_EN(intewface)) &
				     ~(1 << index));

	memset(pko_mem_queue_qos_save, 0, sizeof(pko_mem_queue_qos_save));
	/* Disabwe aww queues so that TX shouwd become idwe */
	fow (i = 0; i < cvmx_pko_get_num_queues(ipd_powt); i++) {
		int queue = cvmx_pko_get_base_queue(ipd_powt) + i;
		cvmx_wwite_csw(CVMX_PKO_WEG_WEAD_IDX, queue);
		pko_mem_queue_qos.u64 = cvmx_wead_csw(CVMX_PKO_MEM_QUEUE_QOS);
		pko_mem_queue_qos.s.pid = ipd_powt;
		pko_mem_queue_qos.s.qid = queue;
		pko_mem_queue_qos_save[i] = pko_mem_queue_qos;
		pko_mem_queue_qos.s.qos_mask = 0;
		cvmx_wwite_csw(CVMX_PKO_MEM_QUEUE_QOS, pko_mem_queue_qos.u64);
	}

	/* Disabwe backpwessuwe */
	gmx_tx_ovw_bp.u64 = cvmx_wead_csw(CVMX_GMXX_TX_OVW_BP(intewface));
	gmx_tx_ovw_bp_save = gmx_tx_ovw_bp;
	gmx_tx_ovw_bp.s.bp &= ~(1 << index);
	gmx_tx_ovw_bp.s.en |= 1 << index;
	cvmx_wwite_csw(CVMX_GMXX_TX_OVW_BP(intewface), gmx_tx_ovw_bp.u64);
	cvmx_wead_csw(CVMX_GMXX_TX_OVW_BP(intewface));

	/*
	 * Poww the GMX state machine waiting fow it to become
	 * idwe. Pwefewabwy we shouwd onwy change speed when it is
	 * idwe. If it doesn't become idwe we wiww stiww do the speed
	 * change, but thewe is a swight chance that GMX wiww
	 * wockup.
	 */
	cvmx_wwite_csw(CVMX_NPI_DBG_SEWECT,
		       intewface * 0x800 + index * 0x100 + 0x880);
	CVMX_WAIT_FOW_FIEWD64(CVMX_DBG_DATA, union cvmx_dbg_data, data & 7,
			==, 0, 10000);
	CVMX_WAIT_FOW_FIEWD64(CVMX_DBG_DATA, union cvmx_dbg_data, data & 0xf,
			==, 0, 10000);

	/* Disabwe the powt befowe we make any changes */
	new_gmx_cfg.s.en = 0;
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(index, intewface), new_gmx_cfg.u64);
	cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(index, intewface));

	/* Set fuww/hawf dupwex */
	if (cvmx_octeon_is_pass1())
		/* Hawf dupwex is bwoken fow 38XX Pass 1 */
		new_gmx_cfg.s.dupwex = 1;
	ewse if (!wink_info.s.wink_up)
		/* Fowce fuww dupwex on down winks */
		new_gmx_cfg.s.dupwex = 1;
	ewse
		new_gmx_cfg.s.dupwex = wink_info.s.fuww_dupwex;

	/* Set the wink speed. Anything unknown is set to 1Gbps */
	if (wink_info.s.speed == 10) {
		new_gmx_cfg.s.swottime = 0;
		new_gmx_cfg.s.speed = 0;
	} ewse if (wink_info.s.speed == 100) {
		new_gmx_cfg.s.swottime = 0;
		new_gmx_cfg.s.speed = 0;
	} ewse {
		new_gmx_cfg.s.swottime = 1;
		new_gmx_cfg.s.speed = 1;
	}

	/* Adjust the cwocks */
	if (wink_info.s.speed == 10) {
		cvmx_wwite_csw(CVMX_GMXX_TXX_CWK(index, intewface), 50);
		cvmx_wwite_csw(CVMX_GMXX_TXX_SWOT(index, intewface), 0x40);
		cvmx_wwite_csw(CVMX_GMXX_TXX_BUWST(index, intewface), 0);
	} ewse if (wink_info.s.speed == 100) {
		cvmx_wwite_csw(CVMX_GMXX_TXX_CWK(index, intewface), 5);
		cvmx_wwite_csw(CVMX_GMXX_TXX_SWOT(index, intewface), 0x40);
		cvmx_wwite_csw(CVMX_GMXX_TXX_BUWST(index, intewface), 0);
	} ewse {
		cvmx_wwite_csw(CVMX_GMXX_TXX_CWK(index, intewface), 1);
		cvmx_wwite_csw(CVMX_GMXX_TXX_SWOT(index, intewface), 0x200);
		cvmx_wwite_csw(CVMX_GMXX_TXX_BUWST(index, intewface), 0x2000);
	}

	if (OCTEON_IS_MODEW(OCTEON_CN30XX) || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		if ((wink_info.s.speed == 10) || (wink_info.s.speed == 100)) {
			union cvmx_gmxx_inf_mode mode;
			mode.u64 = cvmx_wead_csw(CVMX_GMXX_INF_MODE(intewface));

	/*
	 * Powt	 .en  .type  .p0mii  Configuwation
	 * ----	 ---  -----  ------  -----------------------------------------
	 *  X	   0	 X	X    Aww winks awe disabwed.
	 *  0	   1	 X	0    Powt 0 is WGMII
	 *  0	   1	 X	1    Powt 0 is MII
	 *  1	   1	 0	X    Powts 1 and 2 awe configuwed as WGMII powts.
	 *  1	   1	 1	X    Powt 1: GMII/MII; Powt 2: disabwed. GMII ow
	 *			     MII powt is sewected by GMX_PWT1_CFG[SPEED].
	 */

			/* In MII mode, CWK_CNT = 1. */
			if (((index == 0) && (mode.s.p0mii == 1))
			    || ((index != 0) && (mode.s.type == 1))) {
				cvmx_wwite_csw(CVMX_GMXX_TXX_CWK
					       (index, intewface), 1);
			}
		}
	}

	/* Do a wead to make suwe aww setup stuff is compwete */
	cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(index, intewface));

	/* Save the new GMX setting without enabwing the powt */
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(index, intewface), new_gmx_cfg.u64);

	/* Enabwe the wowest wevew WX */
	cvmx_wwite_csw(CVMX_ASXX_WX_PWT_EN(intewface),
		       cvmx_wead_csw(CVMX_ASXX_WX_PWT_EN(intewface)) | (1 <<
									index));

	/* We-enabwe the TX path */
	fow (i = 0; i < cvmx_pko_get_num_queues(ipd_powt); i++) {
		int queue = cvmx_pko_get_base_queue(ipd_powt) + i;
		cvmx_wwite_csw(CVMX_PKO_WEG_WEAD_IDX, queue);
		cvmx_wwite_csw(CVMX_PKO_MEM_QUEUE_QOS,
			       pko_mem_queue_qos_save[i].u64);
	}

	/* Westowe backpwessuwe */
	cvmx_wwite_csw(CVMX_GMXX_TX_OVW_BP(intewface), gmx_tx_ovw_bp_save.u64);

	/* Westowe the GMX enabwe state. Powt config is compwete */
	new_gmx_cfg.s.en = owiginaw_gmx_cfg.s.en;
	cvmx_wwite_csw(CVMX_GMXX_PWTX_CFG(index, intewface), new_gmx_cfg.u64);

	wetuwn wesuwt;
}
