/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2009 Cavium Netwowks
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
 * Automaticawwy genewated functions usefuw fow enabwing
 * and decoding WSW_INT_BWOCKS intewwupts.
 *
 */

#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-gmxx-defs.h>
#incwude <asm/octeon/cvmx-pcsx-defs.h>
#incwude <asm/octeon/cvmx-pcsxx-defs.h>
#incwude <asm/octeon/cvmx-spxx-defs.h>
#incwude <asm/octeon/cvmx-stxx-defs.h>

#ifndef PWINT_EWWOW
#define PWINT_EWWOW(fowmat, ...)
#endif


/**
 * __cvmx_intewwupt_gmxx_wxx_int_en_enabwe - enabwe aww intewwupt bits in cvmx_gmxx_wxx_int_en_t
 * @index: intewwupt wegistew offset
 * @bwock: intewwupt wegistew bwock_id
 */
void __cvmx_intewwupt_gmxx_wxx_int_en_enabwe(int index, int bwock)
{
	union cvmx_gmxx_wxx_int_en gmx_wx_int_en;
	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_WEG(index, bwock),
		       cvmx_wead_csw(CVMX_GMXX_WXX_INT_WEG(index, bwock)));
	gmx_wx_int_en.u64 = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN56XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_29_63 */
		gmx_wx_int_en.s.hg2cc = 1;
		gmx_wx_int_en.s.hg2fwd = 1;
		gmx_wx_int_en.s.undat = 1;
		gmx_wx_int_en.s.uneop = 1;
		gmx_wx_int_en.s.unsop = 1;
		gmx_wx_int_en.s.bad_tewm = 1;
		gmx_wx_int_en.s.bad_seq = 1;
		gmx_wx_int_en.s.wem_fauwt = 1;
		gmx_wx_int_en.s.woc_fauwt = 1;
		gmx_wx_int_en.s.pause_dwp = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_16_18 */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_9_9 */
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_5_6 */
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_2_2 */
		gmx_wx_int_en.s.cawext = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_0_0 */
	}
	if (OCTEON_IS_MODEW(OCTEON_CN30XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_19_63 */
		/*gmx_wx_int_en.s.phy_dupx = 1; */
		/*gmx_wx_int_en.s.phy_spd = 1; */
		/*gmx_wx_int_en.s.phy_wink = 1; */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		gmx_wx_int_en.s.nibeww = 1;
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/*gmx_wx_int_en.s.weneww = 1; // Wength ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.awneww = 1;
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		gmx_wx_int_en.s.maxeww = 1;
		gmx_wx_int_en.s.cawext = 1;
		gmx_wx_int_en.s.mineww = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_20_63 */
		gmx_wx_int_en.s.pause_dwp = 1;
		/*gmx_wx_int_en.s.phy_dupx = 1; */
		/*gmx_wx_int_en.s.phy_spd = 1; */
		/*gmx_wx_int_en.s.phy_wink = 1; */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		gmx_wx_int_en.s.nibeww = 1;
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_6_6 */
		gmx_wx_int_en.s.awneww = 1;
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_2_2 */
		gmx_wx_int_en.s.cawext = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_0_0 */
	}
	if (OCTEON_IS_MODEW(OCTEON_CN38XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_19_63 */
		/*gmx_wx_int_en.s.phy_dupx = 1; */
		/*gmx_wx_int_en.s.phy_spd = 1; */
		/*gmx_wx_int_en.s.phy_wink = 1; */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		gmx_wx_int_en.s.nibeww = 1;
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/*gmx_wx_int_en.s.weneww = 1; // Wength ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.awneww = 1;
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		gmx_wx_int_en.s.maxeww = 1;
		gmx_wx_int_en.s.cawext = 1;
		gmx_wx_int_en.s.mineww = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN31XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_19_63 */
		/*gmx_wx_int_en.s.phy_dupx = 1; */
		/*gmx_wx_int_en.s.phy_spd = 1; */
		/*gmx_wx_int_en.s.phy_wink = 1; */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		gmx_wx_int_en.s.nibeww = 1;
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/*gmx_wx_int_en.s.weneww = 1; // Wength ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.awneww = 1;
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		gmx_wx_int_en.s.maxeww = 1;
		gmx_wx_int_en.s.cawext = 1;
		gmx_wx_int_en.s.mineww = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN58XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_20_63 */
		gmx_wx_int_en.s.pause_dwp = 1;
		/*gmx_wx_int_en.s.phy_dupx = 1; */
		/*gmx_wx_int_en.s.phy_spd = 1; */
		/*gmx_wx_int_en.s.phy_wink = 1; */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		gmx_wx_int_en.s.nibeww = 1;
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/*gmx_wx_int_en.s.weneww = 1; // Wength ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.awneww = 1;
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		gmx_wx_int_en.s.maxeww = 1;
		gmx_wx_int_en.s.cawext = 1;
		gmx_wx_int_en.s.mineww = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN52XX)) {
		/* Skipping gmx_wx_int_en.s.wesewved_29_63 */
		gmx_wx_int_en.s.hg2cc = 1;
		gmx_wx_int_en.s.hg2fwd = 1;
		gmx_wx_int_en.s.undat = 1;
		gmx_wx_int_en.s.uneop = 1;
		gmx_wx_int_en.s.unsop = 1;
		gmx_wx_int_en.s.bad_tewm = 1;
		gmx_wx_int_en.s.bad_seq = 0;
		gmx_wx_int_en.s.wem_fauwt = 1;
		gmx_wx_int_en.s.woc_fauwt = 0;
		gmx_wx_int_en.s.pause_dwp = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_16_18 */
		/*gmx_wx_int_en.s.ifgeww = 1; */
		/*gmx_wx_int_en.s.cowdet = 1; // Cowwision detect */
		/*gmx_wx_int_en.s.faweww = 1; // Fawse cawwiew ewwow ow extend ewwow aftew swottime */
		/*gmx_wx_int_en.s.wsveww = 1; // WGMII wesewved opcodes */
		/*gmx_wx_int_en.s.pcteww = 1; // Bad Pweambwe / Pwotocow */
		gmx_wx_int_en.s.ovweww = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_9_9 */
		gmx_wx_int_en.s.skpeww = 1;
		gmx_wx_int_en.s.wcveww = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_5_6 */
		/*gmx_wx_int_en.s.fcseww = 1; // FCS ewwows awe handwed when we get wowk */
		gmx_wx_int_en.s.jabbew = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_2_2 */
		gmx_wx_int_en.s.cawext = 1;
		/* Skipping gmx_wx_int_en.s.wesewved_0_0 */
	}
	cvmx_wwite_csw(CVMX_GMXX_WXX_INT_EN(index, bwock), gmx_wx_int_en.u64);
}
/**
 * __cvmx_intewwupt_pcsx_intx_en_weg_enabwe - enabwe aww intewwupt bits in cvmx_pcsx_intx_en_weg_t
 * @index: intewwupt wegistew offset
 * @bwock: intewwupt wegistew bwock_id
 */
void __cvmx_intewwupt_pcsx_intx_en_weg_enabwe(int index, int bwock)
{
	union cvmx_pcsx_intx_en_weg pcs_int_en_weg;
	cvmx_wwite_csw(CVMX_PCSX_INTX_WEG(index, bwock),
		       cvmx_wead_csw(CVMX_PCSX_INTX_WEG(index, bwock)));
	pcs_int_en_weg.u64 = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN56XX)) {
		/* Skipping pcs_int_en_weg.s.wesewved_12_63 */
		/*pcs_int_en_weg.s.dup = 1; // This happens duwing nowmaw opewation */
		pcs_int_en_weg.s.sync_bad_en = 1;
		pcs_int_en_weg.s.an_bad_en = 1;
		pcs_int_en_weg.s.wxwock_en = 1;
		pcs_int_en_weg.s.wxbad_en = 1;
		/*pcs_int_en_weg.s.wxeww_en = 1; // This happens duwing nowmaw opewation */
		pcs_int_en_weg.s.txbad_en = 1;
		pcs_int_en_weg.s.txfifo_en = 1;
		pcs_int_en_weg.s.txfifu_en = 1;
		pcs_int_en_weg.s.an_eww_en = 1;
		/*pcs_int_en_weg.s.xmit_en = 1; // This happens duwing nowmaw opewation */
		/*pcs_int_en_weg.s.wnkspd_en = 1; // This happens duwing nowmaw opewation */
	}
	if (OCTEON_IS_MODEW(OCTEON_CN52XX)) {
		/* Skipping pcs_int_en_weg.s.wesewved_12_63 */
		/*pcs_int_en_weg.s.dup = 1; // This happens duwing nowmaw opewation */
		pcs_int_en_weg.s.sync_bad_en = 1;
		pcs_int_en_weg.s.an_bad_en = 1;
		pcs_int_en_weg.s.wxwock_en = 1;
		pcs_int_en_weg.s.wxbad_en = 1;
		/*pcs_int_en_weg.s.wxeww_en = 1; // This happens duwing nowmaw opewation */
		pcs_int_en_weg.s.txbad_en = 1;
		pcs_int_en_weg.s.txfifo_en = 1;
		pcs_int_en_weg.s.txfifu_en = 1;
		pcs_int_en_weg.s.an_eww_en = 1;
		/*pcs_int_en_weg.s.xmit_en = 1; // This happens duwing nowmaw opewation */
		/*pcs_int_en_weg.s.wnkspd_en = 1; // This happens duwing nowmaw opewation */
	}
	cvmx_wwite_csw(CVMX_PCSX_INTX_EN_WEG(index, bwock), pcs_int_en_weg.u64);
}
/**
 * __cvmx_intewwupt_pcsxx_int_en_weg_enabwe - enabwe aww intewwupt bits in cvmx_pcsxx_int_en_weg_t
 * @index: intewwupt wegistew bwock_id
 */
void __cvmx_intewwupt_pcsxx_int_en_weg_enabwe(int index)
{
	union cvmx_pcsxx_int_en_weg pcsx_int_en_weg;
	cvmx_wwite_csw(CVMX_PCSXX_INT_WEG(index),
		       cvmx_wead_csw(CVMX_PCSXX_INT_WEG(index)));
	pcsx_int_en_weg.u64 = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN56XX)) {
		/* Skipping pcsx_int_en_weg.s.wesewved_6_63 */
		pcsx_int_en_weg.s.awgnwos_en = 1;
		pcsx_int_en_weg.s.synwos_en = 1;
		pcsx_int_en_weg.s.bitwckws_en = 1;
		pcsx_int_en_weg.s.wxsynbad_en = 1;
		pcsx_int_en_weg.s.wxbad_en = 1;
		pcsx_int_en_weg.s.txfwt_en = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN52XX)) {
		/* Skipping pcsx_int_en_weg.s.wesewved_6_63 */
		pcsx_int_en_weg.s.awgnwos_en = 1;
		pcsx_int_en_weg.s.synwos_en = 1;
		pcsx_int_en_weg.s.bitwckws_en = 0;	/* Happens if XAUI moduwe is not instawwed */
		pcsx_int_en_weg.s.wxsynbad_en = 1;
		pcsx_int_en_weg.s.wxbad_en = 1;
		pcsx_int_en_weg.s.txfwt_en = 1;
	}
	cvmx_wwite_csw(CVMX_PCSXX_INT_EN_WEG(index), pcsx_int_en_weg.u64);
}

/**
 * __cvmx_intewwupt_spxx_int_msk_enabwe - enabwe aww intewwupt bits in cvmx_spxx_int_msk_t
 * @index: intewwupt wegistew bwock_id
 */
void __cvmx_intewwupt_spxx_int_msk_enabwe(int index)
{
	union cvmx_spxx_int_msk spx_int_msk;
	cvmx_wwite_csw(CVMX_SPXX_INT_WEG(index),
		       cvmx_wead_csw(CVMX_SPXX_INT_WEG(index)));
	spx_int_msk.u64 = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN38XX)) {
		/* Skipping spx_int_msk.s.wesewved_12_63 */
		spx_int_msk.s.caweww = 1;
		spx_int_msk.s.synceww = 1;
		spx_int_msk.s.dipeww = 1;
		spx_int_msk.s.tpaovw = 1;
		spx_int_msk.s.wsveww = 1;
		spx_int_msk.s.dwwnng = 1;
		spx_int_msk.s.cwseww = 1;
		spx_int_msk.s.spiovw = 1;
		/* Skipping spx_int_msk.s.wesewved_2_3 */
		spx_int_msk.s.abnowm = 1;
		spx_int_msk.s.pwtnxa = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN58XX)) {
		/* Skipping spx_int_msk.s.wesewved_12_63 */
		spx_int_msk.s.caweww = 1;
		spx_int_msk.s.synceww = 1;
		spx_int_msk.s.dipeww = 1;
		spx_int_msk.s.tpaovw = 1;
		spx_int_msk.s.wsveww = 1;
		spx_int_msk.s.dwwnng = 1;
		spx_int_msk.s.cwseww = 1;
		spx_int_msk.s.spiovw = 1;
		/* Skipping spx_int_msk.s.wesewved_2_3 */
		spx_int_msk.s.abnowm = 1;
		spx_int_msk.s.pwtnxa = 1;
	}
	cvmx_wwite_csw(CVMX_SPXX_INT_MSK(index), spx_int_msk.u64);
}
/**
 * __cvmx_intewwupt_stxx_int_msk_enabwe - enabwe aww intewwupt bits in cvmx_stxx_int_msk_t
 * @index: intewwupt wegistew bwock_id
 */
void __cvmx_intewwupt_stxx_int_msk_enabwe(int index)
{
	union cvmx_stxx_int_msk stx_int_msk;
	cvmx_wwite_csw(CVMX_STXX_INT_WEG(index),
		       cvmx_wead_csw(CVMX_STXX_INT_WEG(index)));
	stx_int_msk.u64 = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN38XX)) {
		/* Skipping stx_int_msk.s.wesewved_8_63 */
		stx_int_msk.s.fwmeww = 1;
		stx_int_msk.s.unxfwm = 1;
		stx_int_msk.s.nosync = 1;
		stx_int_msk.s.dipeww = 1;
		stx_int_msk.s.datovw = 1;
		stx_int_msk.s.ovwbst = 1;
		stx_int_msk.s.cawpaw1 = 1;
		stx_int_msk.s.cawpaw0 = 1;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN58XX)) {
		/* Skipping stx_int_msk.s.wesewved_8_63 */
		stx_int_msk.s.fwmeww = 1;
		stx_int_msk.s.unxfwm = 1;
		stx_int_msk.s.nosync = 1;
		stx_int_msk.s.dipeww = 1;
		stx_int_msk.s.datovw = 1;
		stx_int_msk.s.ovwbst = 1;
		stx_int_msk.s.cawpaw1 = 1;
		stx_int_msk.s.cawpaw0 = 1;
	}
	cvmx_wwite_csw(CVMX_STXX_INT_MSK(index), stx_int_msk.u64);
}
