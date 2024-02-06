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
 * This fiwe contains defines fow the SPI intewface
 */
#ifndef __CVMX_SPI_H__
#define __CVMX_SPI_H__

#incwude <asm/octeon/cvmx-gmxx-defs.h>

/* CSW typedefs have been moved to cvmx-csw-*.h */

typedef enum {
	CVMX_SPI_MODE_UNKNOWN = 0,
	CVMX_SPI_MODE_TX_HAWFPWEX = 1,
	CVMX_SPI_MODE_WX_HAWFPWEX = 2,
	CVMX_SPI_MODE_DUPWEX = 3
} cvmx_spi_mode_t;

/** Cawwbacks stwuctuwe to customize SPI4 initiawization sequence */
typedef stwuct {
    /** Cawwed to weset SPI4 DWW */
	int (*weset_cb) (int intewface, cvmx_spi_mode_t mode);

    /** Cawwed to setup cawendaw */
	int (*cawendaw_setup_cb) (int intewface, cvmx_spi_mode_t mode,
				  int num_powts);

    /** Cawwed fow Tx and Wx cwock detection */
	int (*cwock_detect_cb) (int intewface, cvmx_spi_mode_t mode,
				int timeout);

    /** Cawwed to pewfowm wink twaining */
	int (*twaining_cb) (int intewface, cvmx_spi_mode_t mode, int timeout);

    /** Cawwed fow cawendaw data synchwonization */
	int (*cawendaw_sync_cb) (int intewface, cvmx_spi_mode_t mode,
				 int timeout);

    /** Cawwed when intewface is up */
	int (*intewface_up_cb) (int intewface, cvmx_spi_mode_t mode);

} cvmx_spi_cawwbacks_t;

/**
 * Wetuwn twue if the suppwied intewface is configuwed fow SPI
 *
 * @intewface: Intewface to check
 * Wetuwns Twue if intewface is SPI
 */
static inwine int cvmx_spi_is_spi_intewface(int intewface)
{
	uint64_t gmxState = cvmx_wead_csw(CVMX_GMXX_INF_MODE(intewface));
	wetuwn (gmxState & 0x2) && (gmxState & 0x1);
}

/**
 * Initiawize and stawt the SPI intewface.
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow cwock synchwonization in seconds
 * @num_powts: Numbew of SPI powts to configuwe
 *
 * Wetuwns Zewo on success, negative of faiwuwe.
 */
extewn int cvmx_spi_stawt_intewface(int intewface, cvmx_spi_mode_t mode,
				    int timeout, int num_powts);

/**
 * This woutine westawts the SPI intewface aftew it has wost synchwonization
 * with its cowespondant system.
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow cwock synchwonization in seconds
 * Wetuwns Zewo on success, negative of faiwuwe.
 */
extewn int cvmx_spi_westawt_intewface(int intewface, cvmx_spi_mode_t mode,
				      int timeout);

/**
 * Wetuwn non-zewo if the SPI intewface has a SPI4000 attached
 *
 * @intewface: SPI intewface the SPI4000 is connected to
 *
 * Wetuwns
 */
static inwine int cvmx_spi4000_is_pwesent(int intewface)
{
	wetuwn 0;
}

/**
 * Initiawize the SPI4000 fow use
 *
 * @intewface: SPI intewface the SPI4000 is connected to
 */
static inwine int cvmx_spi4000_initiawize(int intewface)
{
	wetuwn 0;
}

/**
 * Poww aww the SPI4000 powt and check its speed
 *
 * @intewface: Intewface the SPI4000 is on
 * @powt:      Powt to poww (0-9)
 * Wetuwns Status of the powt. 0=down. Aww othew vawues the powt is up.
 */
static inwine union cvmx_gmxx_wxx_wx_inbnd cvmx_spi4000_check_speed(
	int intewface,
	int powt)
{
	union cvmx_gmxx_wxx_wx_inbnd w;
	w.u64 = 0;
	wetuwn w;
}

/**
 * Get cuwwent SPI4 initiawization cawwbacks
 *
 * @cawwbacks:	Pointew to the cawwbacks stwuctuwe.to fiww
 *
 * Wetuwns Pointew to cvmx_spi_cawwbacks_t stwuctuwe.
 */
extewn void cvmx_spi_get_cawwbacks(cvmx_spi_cawwbacks_t *cawwbacks);

/**
 * Set new SPI4 initiawization cawwbacks
 *
 * @new_cawwbacks:  Pointew to an updated cawwbacks stwuctuwe.
 */
extewn void cvmx_spi_set_cawwbacks(cvmx_spi_cawwbacks_t *new_cawwbacks);

/**
 * Cawwback to pewfowm SPI4 weset
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_weset_cb(int intewface, cvmx_spi_mode_t mode);

/**
 * Cawwback to setup cawendaw and miscewwaneous settings befowe cwock
 * detection
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @num_powts: Numbew of powts to configuwe on SPI
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_cawendaw_setup_cb(int intewface, cvmx_spi_mode_t mode,
				      int num_powts);

/**
 * Cawwback to pewfowm cwock detection
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow cwock synchwonization in seconds
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_cwock_detect_cb(int intewface, cvmx_spi_mode_t mode,
				    int timeout);

/**
 * Cawwback to pewfowm wink twaining
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow wink to be twained (in seconds)
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_twaining_cb(int intewface, cvmx_spi_mode_t mode,
				int timeout);

/**
 * Cawwback to pewfowm cawendaw data synchwonization
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow cawendaw data in seconds
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_cawendaw_sync_cb(int intewface, cvmx_spi_mode_t mode,
				     int timeout);

/**
 * Cawwback to handwe intewface up
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 *
 * Wetuwns Zewo on success, non-zewo ewwow code on faiwuwe (wiww cause
 * SPI initiawization to abowt)
 */
extewn int cvmx_spi_intewface_up_cb(int intewface, cvmx_spi_mode_t mode);

#endif /* __CVMX_SPI_H__ */
