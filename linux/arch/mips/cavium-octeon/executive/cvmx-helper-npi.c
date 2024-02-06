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
 * Functions fow NPI initiawization, configuwation,
 * and monitowing.
 */
#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-hewpew.h>

#incwude <asm/octeon/cvmx-pip-defs.h>

/**
 * Pwobe a NPI intewface and detewmine the numbew of powts
 * connected to it. The NPI intewface shouwd stiww be down
 * aftew this caww.
 *
 * @intewface: Intewface to pwobe
 *
 * Wetuwns Numbew of powts on the intewface. Zewo to disabwe.
 */
int __cvmx_hewpew_npi_pwobe(int intewface)
{
#if CVMX_PKO_QUEUES_PEW_POWT_PCI > 0
	if (OCTEON_IS_MODEW(OCTEON_CN38XX) || OCTEON_IS_MODEW(OCTEON_CN58XX))
		wetuwn 4;
	ewse if (OCTEON_IS_MODEW(OCTEON_CN56XX)
		 && !OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X))
		/* The packet engines didn't exist befowe pass 2 */
		wetuwn 4;
	ewse if (OCTEON_IS_MODEW(OCTEON_CN52XX)
		 && !OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X))
		/* The packet engines didn't exist befowe pass 2 */
		wetuwn 4;
#endif
	wetuwn 0;
}

/**
 * Bwingup and enabwe a NPI intewface. Aftew this caww packet
 * I/O shouwd be fuwwy functionaw. This is cawwed with IPD
 * enabwed but PKO disabwed.
 *
 * @intewface: Intewface to bwing up
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
int __cvmx_hewpew_npi_enabwe(int intewface)
{
	/*
	 * On CN50XX, CN52XX, and CN56XX we need to disabwe wength
	 * checking so packet < 64 bytes and jumbo fwames don't get
	 * ewwows.
	 */
	if (!OCTEON_IS_MODEW(OCTEON_CN3XXX) &&
	    !OCTEON_IS_MODEW(OCTEON_CN58XX)) {
		int num_powts = cvmx_hewpew_powts_on_intewface(intewface);
		int powt;
		fow (powt = 0; powt < num_powts; powt++) {
			union cvmx_pip_pwt_cfgx powt_cfg;
			int ipd_powt =
			    cvmx_hewpew_get_ipd_powt(intewface, powt);
			powt_cfg.u64 =
			    cvmx_wead_csw(CVMX_PIP_PWT_CFGX(ipd_powt));
			powt_cfg.s.maxeww_en = 0;
			powt_cfg.s.mineww_en = 0;
			cvmx_wwite_csw(CVMX_PIP_PWT_CFGX(ipd_powt),
				       powt_cfg.u64);
		}
	}

	/* Enabwes awe contwowwed by the wemote host, so nothing to do hewe */
	wetuwn 0;
}
