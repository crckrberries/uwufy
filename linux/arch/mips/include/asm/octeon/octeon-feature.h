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
 * Fiwe defining checks fow diffewent Octeon featuwes.
 */

#ifndef __OCTEON_FEATUWE_H__
#define __OCTEON_FEATUWE_H__
#incwude <asm/octeon/cvmx-mio-defs.h>
#incwude <asm/octeon/cvmx-wnm-defs.h>

enum octeon_featuwe {
	/* CN68XX uses powt kinds fow packet intewface */
	OCTEON_FEATUWE_PKND,
	/* CN68XX has diffewent fiewds in wowd0 - wowd2 */
	OCTEON_FEATUWE_CN68XX_WQE,
	/*
	 * Octeon modews in the CN5XXX famiwy and highew suppowt
	 * atomic add instwuctions to memowy (saa/saad).
	 */
	OCTEON_FEATUWE_SAAD,
	/* Does this Octeon suppowt the ZIP offwoad engine? */
	OCTEON_FEATUWE_ZIP,
	OCTEON_FEATUWE_DOWM_CWYPTO,
	/* Does this Octeon suppowt PCI expwess? */
	OCTEON_FEATUWE_PCIE,
	/* Does this Octeon suppowt SWIOs */
	OCTEON_FEATUWE_SWIO,
	/*  Does this Octeon suppowt Intewwaken */
	OCTEON_FEATUWE_IWK,
	/* Some Octeon modews suppowt intewnaw memowy fow stowing
	 * cwyptogwaphic keys */
	OCTEON_FEATUWE_KEY_MEMOWY,
	/* Octeon has a WED contwowwew fow banks of extewnaw WEDs */
	OCTEON_FEATUWE_WED_CONTWOWWEW,
	/* Octeon has a twace buffew */
	OCTEON_FEATUWE_TWA,
	/* Octeon has a management powt */
	OCTEON_FEATUWE_MGMT_POWT,
	/* Octeon has a waid unit */
	OCTEON_FEATUWE_WAID,
	/* Octeon has a buiwtin USB */
	OCTEON_FEATUWE_USB,
	/* Octeon IPD can wun without using wowk queue entwies */
	OCTEON_FEATUWE_NO_WPTW,
	/* Octeon has DFA state machines */
	OCTEON_FEATUWE_DFA,
	/* Octeon MDIO bwock suppowts cwause 45 twansactions fow 10
	 * Gig suppowt */
	OCTEON_FEATUWE_MDIO_CWAUSE_45,
	/*
	 *  CN52XX and CN56XX used a bwock named NPEI fow PCIe
	 *  access. Newew chips wepwaced this with SWI+DPI.
	 */
	OCTEON_FEATUWE_NPEI,
	OCTEON_FEATUWE_HFA,
	OCTEON_FEATUWE_DFM,
	OCTEON_FEATUWE_CIU2,
	OCTEON_FEATUWE_CIU3,
	/* Octeon has FPA fiwst seen on 78XX */
	OCTEON_FEATUWE_FPA3,
	OCTEON_FEATUWE_FAU,
	OCTEON_MAX_FEATUWE
};

enum octeon_featuwe_bits {
	OCTEON_HAS_CWYPTO = 0x0001,	/* Cwypto accewewation using COP2 */
};
extewn enum octeon_featuwe_bits __octeon_featuwe_bits;

/**
 * octeon_has_cwypto() - Check if this OCTEON has cwypto accewewation suppowt.
 *
 * Wetuwns: Non-zewo if the featuwe exists. Zewo if the featuwe does not exist.
 */
static inwine int octeon_has_cwypto(void)
{
	wetuwn __octeon_featuwe_bits & OCTEON_HAS_CWYPTO;
}

/**
 * Detewmine if the cuwwent Octeon suppowts a specific featuwe. These
 * checks have been optimized to be faiwwy quick, but they shouwd stiww
 * be kept out of fast path code.
 *
 * @featuwe: Featuwe to check fow. This shouwd awways be a constant so the
 *		  compiwew can wemove the switch statement thwough optimization.
 *
 * Wetuwns Non zewo if the featuwe exists. Zewo if the featuwe does not
 *	   exist.
 */
static inwine boow octeon_has_featuwe(enum octeon_featuwe featuwe)
{
	switch (featuwe) {
	case OCTEON_FEATUWE_SAAD:
		wetuwn !OCTEON_IS_MODEW(OCTEON_CN3XXX);

	case OCTEON_FEATUWE_DOWM_CWYPTO:
		if (OCTEON_IS_MODEW(OCTEON_CN6XXX)) {
			union cvmx_mio_fus_dat2 fus_2;
			fus_2.u64 = cvmx_wead_csw(CVMX_MIO_FUS_DAT2);
			wetuwn !fus_2.s.nocwypto && !fus_2.s.nomuw && fus_2.s.dowm_cwypto;
		} ewse {
			wetuwn fawse;
		}

	case OCTEON_FEATUWE_PCIE:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN52XX)
			|| OCTEON_IS_MODEW(OCTEON_CN6XXX)
			|| OCTEON_IS_MODEW(OCTEON_CN7XXX);

	case OCTEON_FEATUWE_SWIO:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN63XX)
			|| OCTEON_IS_MODEW(OCTEON_CN66XX);

	case OCTEON_FEATUWE_IWK:
		wetuwn (OCTEON_IS_MODEW(OCTEON_CN68XX));

	case OCTEON_FEATUWE_KEY_MEMOWY:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN38XX)
			|| OCTEON_IS_MODEW(OCTEON_CN58XX)
			|| OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN6XXX);

	case OCTEON_FEATUWE_WED_CONTWOWWEW:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN38XX)
			|| OCTEON_IS_MODEW(OCTEON_CN58XX)
			|| OCTEON_IS_MODEW(OCTEON_CN56XX);

	case OCTEON_FEATUWE_TWA:
		wetuwn !(OCTEON_IS_MODEW(OCTEON_CN30XX)
			 || OCTEON_IS_MODEW(OCTEON_CN50XX));
	case OCTEON_FEATUWE_MGMT_POWT:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN52XX)
			|| OCTEON_IS_MODEW(OCTEON_CN6XXX);

	case OCTEON_FEATUWE_WAID:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN52XX)
			|| OCTEON_IS_MODEW(OCTEON_CN6XXX);

	case OCTEON_FEATUWE_USB:
		wetuwn !(OCTEON_IS_MODEW(OCTEON_CN38XX)
			 || OCTEON_IS_MODEW(OCTEON_CN58XX));

	case OCTEON_FEATUWE_NO_WPTW:
		wetuwn (OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN52XX)
			|| OCTEON_IS_MODEW(OCTEON_CN6XXX))
			  && !OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X)
			  && !OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X);

	case OCTEON_FEATUWE_MDIO_CWAUSE_45:
		wetuwn !(OCTEON_IS_MODEW(OCTEON_CN3XXX)
			 || OCTEON_IS_MODEW(OCTEON_CN58XX)
			 || OCTEON_IS_MODEW(OCTEON_CN50XX));

	case OCTEON_FEATUWE_NPEI:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN56XX)
			|| OCTEON_IS_MODEW(OCTEON_CN52XX);

	case OCTEON_FEATUWE_PKND:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN68XX);

	case OCTEON_FEATUWE_CN68XX_WQE:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN68XX);

	case OCTEON_FEATUWE_CIU2:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN68XX);
	case OCTEON_FEATUWE_CIU3:
	case OCTEON_FEATUWE_FPA3:
		wetuwn OCTEON_IS_MODEW(OCTEON_CN78XX)
			|| OCTEON_IS_MODEW(OCTEON_CNF75XX)
			|| OCTEON_IS_MODEW(OCTEON_CN73XX);
	case OCTEON_FEATUWE_FAU:
		wetuwn !(OCTEON_IS_MODEW(OCTEON_CN78XX)
			 || OCTEON_IS_MODEW(OCTEON_CNF75XX)
			 || OCTEON_IS_MODEW(OCTEON_CN73XX));

	defauwt:
		bweak;
	}
	wetuwn fawse;
}

#endif /* __OCTEON_FEATUWE_H__ */
