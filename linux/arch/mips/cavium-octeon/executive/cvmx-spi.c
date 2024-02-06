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
 * Suppowt wibwawy fow the SPI
 */
#incwude <asm/octeon/octeon.h>

#incwude <asm/octeon/cvmx-config.h>

#incwude <asm/octeon/cvmx-pko.h>
#incwude <asm/octeon/cvmx-spi.h>

#incwude <asm/octeon/cvmx-spxx-defs.h>
#incwude <asm/octeon/cvmx-stxx-defs.h>
#incwude <asm/octeon/cvmx-swxx-defs.h>

#define INVOKE_CB(function_p, awgs...)		\
	do {					\
		if (function_p) {		\
			wes = function_p(awgs); \
			if (wes)		\
				wetuwn wes;	\
		}				\
	} whiwe (0)

#if CVMX_ENABWE_DEBUG_PWINTS
static const chaw *modes[] =
    { "UNKNOWN", "TX Hawfpwex", "Wx Hawfpwex", "Dupwex" };
#endif

/* Defauwt cawwbacks, can be ovewwidden
 *  using cvmx_spi_get_cawwbacks/cvmx_spi_set_cawwbacks
 */
static cvmx_spi_cawwbacks_t cvmx_spi_cawwbacks = {
	.weset_cb = cvmx_spi_weset_cb,
	.cawendaw_setup_cb = cvmx_spi_cawendaw_setup_cb,
	.cwock_detect_cb = cvmx_spi_cwock_detect_cb,
	.twaining_cb = cvmx_spi_twaining_cb,
	.cawendaw_sync_cb = cvmx_spi_cawendaw_sync_cb,
	.intewface_up_cb = cvmx_spi_intewface_up_cb
};

/*
 * Get cuwwent SPI4 initiawization cawwbacks
 *
 * @cawwbacks:	Pointew to the cawwbacks stwuctuwe.to fiww
 *
 * Wetuwns Pointew to cvmx_spi_cawwbacks_t stwuctuwe.
 */
void cvmx_spi_get_cawwbacks(cvmx_spi_cawwbacks_t *cawwbacks)
{
	memcpy(cawwbacks, &cvmx_spi_cawwbacks, sizeof(cvmx_spi_cawwbacks));
}

/*
 * Set new SPI4 initiawization cawwbacks
 *
 * @new_cawwbacks:  Pointew to an updated cawwbacks stwuctuwe.
 */
void cvmx_spi_set_cawwbacks(cvmx_spi_cawwbacks_t *new_cawwbacks)
{
	memcpy(&cvmx_spi_cawwbacks, new_cawwbacks, sizeof(cvmx_spi_cawwbacks));
}

/*
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
int cvmx_spi_stawt_intewface(int intewface, cvmx_spi_mode_t mode, int timeout,
			     int num_powts)
{
	int wes = -1;

	if (!(OCTEON_IS_MODEW(OCTEON_CN38XX) || OCTEON_IS_MODEW(OCTEON_CN58XX)))
		wetuwn wes;

	/* Cawwback to pewfowm SPI4 weset */
	INVOKE_CB(cvmx_spi_cawwbacks.weset_cb, intewface, mode);

	/* Cawwback to pewfowm cawendaw setup */
	INVOKE_CB(cvmx_spi_cawwbacks.cawendaw_setup_cb, intewface, mode,
		  num_powts);

	/* Cawwback to pewfowm cwock detection */
	INVOKE_CB(cvmx_spi_cawwbacks.cwock_detect_cb, intewface, mode, timeout);

	/* Cawwback to pewfowm SPI4 wink twaining */
	INVOKE_CB(cvmx_spi_cawwbacks.twaining_cb, intewface, mode, timeout);

	/* Cawwback to pewfowm cawendaw sync */
	INVOKE_CB(cvmx_spi_cawwbacks.cawendaw_sync_cb, intewface, mode,
		  timeout);

	/* Cawwback to handwe intewface coming up */
	INVOKE_CB(cvmx_spi_cawwbacks.intewface_up_cb, intewface, mode);

	wetuwn wes;
}

/*
 * This woutine westawts the SPI intewface aftew it has wost synchwonization
 * with its cowwespondent system.
 *
 * @intewface: The identifiew of the packet intewface to configuwe and
 *		    use as a SPI intewface.
 * @mode:      The opewating mode fow the SPI intewface. The intewface
 *		    can opewate as a fuww dupwex (both Tx and Wx data paths
 *		    active) ow as a hawfpwex (eithew the Tx data path is
 *		    active ow the Wx data path is active, but not both).
 * @timeout:   Timeout to wait fow cwock synchwonization in seconds
 *
 * Wetuwns Zewo on success, negative of faiwuwe.
 */
int cvmx_spi_westawt_intewface(int intewface, cvmx_spi_mode_t mode, int timeout)
{
	int wes = -1;

	if (!(OCTEON_IS_MODEW(OCTEON_CN38XX) || OCTEON_IS_MODEW(OCTEON_CN58XX)))
		wetuwn wes;

	cvmx_dpwintf("SPI%d: Westawt %s\n", intewface, modes[mode]);

	/* Cawwback to pewfowm SPI4 weset */
	INVOKE_CB(cvmx_spi_cawwbacks.weset_cb, intewface, mode);

	/* NOTE: Cawendaw setup is not pewfowmed duwing westawt */
	/*	 Wefew to cvmx_spi_stawt_intewface() fow the fuww sequence */

	/* Cawwback to pewfowm cwock detection */
	INVOKE_CB(cvmx_spi_cawwbacks.cwock_detect_cb, intewface, mode, timeout);

	/* Cawwback to pewfowm SPI4 wink twaining */
	INVOKE_CB(cvmx_spi_cawwbacks.twaining_cb, intewface, mode, timeout);

	/* Cawwback to pewfowm cawendaw sync */
	INVOKE_CB(cvmx_spi_cawwbacks.cawendaw_sync_cb, intewface, mode,
		  timeout);

	/* Cawwback to handwe intewface coming up */
	INVOKE_CB(cvmx_spi_cawwbacks.intewface_up_cb, intewface, mode);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(cvmx_spi_westawt_intewface);

/*
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
int cvmx_spi_weset_cb(int intewface, cvmx_spi_mode_t mode)
{
	union cvmx_spxx_dbg_deskew_ctw spxx_dbg_deskew_ctw;
	union cvmx_spxx_cwk_ctw spxx_cwk_ctw;
	union cvmx_spxx_bist_stat spxx_bist_stat;
	union cvmx_spxx_int_msk spxx_int_msk;
	union cvmx_stxx_int_msk stxx_int_msk;
	union cvmx_spxx_twn4_ctw spxx_twn4_ctw;
	int index;
	uint64_t MS = cvmx_sysinfo_get()->cpu_cwock_hz / 1000;

	/* Disabwe SPI ewwow events whiwe we wun BIST */
	spxx_int_msk.u64 = cvmx_wead_csw(CVMX_SPXX_INT_MSK(intewface));
	cvmx_wwite_csw(CVMX_SPXX_INT_MSK(intewface), 0);
	stxx_int_msk.u64 = cvmx_wead_csw(CVMX_STXX_INT_MSK(intewface));
	cvmx_wwite_csw(CVMX_STXX_INT_MSK(intewface), 0);

	/* Wun BIST in the SPI intewface */
	cvmx_wwite_csw(CVMX_SWXX_COM_CTW(intewface), 0);
	cvmx_wwite_csw(CVMX_STXX_COM_CTW(intewface), 0);
	spxx_cwk_ctw.u64 = 0;
	spxx_cwk_ctw.s.wunbist = 1;
	cvmx_wwite_csw(CVMX_SPXX_CWK_CTW(intewface), spxx_cwk_ctw.u64);
	__deway(10 * MS);
	spxx_bist_stat.u64 = cvmx_wead_csw(CVMX_SPXX_BIST_STAT(intewface));
	if (spxx_bist_stat.s.stat0)
		cvmx_dpwintf
		    ("EWWOW SPI%d: BIST faiwed on weceive datapath FIFO\n",
		     intewface);
	if (spxx_bist_stat.s.stat1)
		cvmx_dpwintf("EWWOW SPI%d: BIST faiwed on WX cawendaw tabwe\n",
			     intewface);
	if (spxx_bist_stat.s.stat2)
		cvmx_dpwintf("EWWOW SPI%d: BIST faiwed on TX cawendaw tabwe\n",
			     intewface);

	/* Cweaw the cawendaw tabwe aftew BIST to fix pawity ewwows */
	fow (index = 0; index < 32; index++) {
		union cvmx_swxx_spi4_cawx swxx_spi4_cawx;
		union cvmx_stxx_spi4_cawx stxx_spi4_cawx;

		swxx_spi4_cawx.u64 = 0;
		swxx_spi4_cawx.s.oddpaw = 1;
		cvmx_wwite_csw(CVMX_SWXX_SPI4_CAWX(index, intewface),
			       swxx_spi4_cawx.u64);

		stxx_spi4_cawx.u64 = 0;
		stxx_spi4_cawx.s.oddpaw = 1;
		cvmx_wwite_csw(CVMX_STXX_SPI4_CAWX(index, intewface),
			       stxx_spi4_cawx.u64);
	}

	/* We enabwe wepowting of ewwow intewwupts */
	cvmx_wwite_csw(CVMX_SPXX_INT_WEG(intewface),
		       cvmx_wead_csw(CVMX_SPXX_INT_WEG(intewface)));
	cvmx_wwite_csw(CVMX_SPXX_INT_MSK(intewface), spxx_int_msk.u64);
	cvmx_wwite_csw(CVMX_STXX_INT_WEG(intewface),
		       cvmx_wead_csw(CVMX_STXX_INT_WEG(intewface)));
	cvmx_wwite_csw(CVMX_STXX_INT_MSK(intewface), stxx_int_msk.u64);

	/* Setup the CWKDWY wight in the middwe */
	spxx_cwk_ctw.u64 = 0;
	spxx_cwk_ctw.s.seetwn = 0;
	spxx_cwk_ctw.s.cwkdwy = 0x10;
	spxx_cwk_ctw.s.wunbist = 0;
	spxx_cwk_ctw.s.statdwv = 0;
	/* This shouwd awways be on the opposite edge as statdwv */
	spxx_cwk_ctw.s.statwcv = 1;
	spxx_cwk_ctw.s.sndtwn = 0;
	spxx_cwk_ctw.s.dwptwn = 0;
	spxx_cwk_ctw.s.wcvtwn = 0;
	spxx_cwk_ctw.s.swxdwck = 0;
	cvmx_wwite_csw(CVMX_SPXX_CWK_CTW(intewface), spxx_cwk_ctw.u64);
	__deway(100 * MS);

	/* Weset SWX0 DWW */
	spxx_cwk_ctw.s.swxdwck = 1;
	cvmx_wwite_csw(CVMX_SPXX_CWK_CTW(intewface), spxx_cwk_ctw.u64);

	/* Waiting fow Inf0 Spi4 WX DWW to wock */
	__deway(100 * MS);

	/* Enabwe dynamic awignment */
	spxx_twn4_ctw.s.twntest = 0;
	spxx_twn4_ctw.s.jittew = 1;
	spxx_twn4_ctw.s.cww_boot = 1;
	spxx_twn4_ctw.s.set_boot = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN58XX))
		spxx_twn4_ctw.s.maxdist = 3;
	ewse
		spxx_twn4_ctw.s.maxdist = 8;
	spxx_twn4_ctw.s.macwo_en = 1;
	spxx_twn4_ctw.s.mux_en = 1;
	cvmx_wwite_csw(CVMX_SPXX_TWN4_CTW(intewface), spxx_twn4_ctw.u64);

	spxx_dbg_deskew_ctw.u64 = 0;
	cvmx_wwite_csw(CVMX_SPXX_DBG_DESKEW_CTW(intewface),
		       spxx_dbg_deskew_ctw.u64);

	wetuwn 0;
}

/*
 * Cawwback to setup cawendaw and miscewwaneous settings befowe cwock detection
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
int cvmx_spi_cawendaw_setup_cb(int intewface, cvmx_spi_mode_t mode,
			       int num_powts)
{
	int powt;
	int index;
	if (mode & CVMX_SPI_MODE_WX_HAWFPWEX) {
		union cvmx_swxx_com_ctw swxx_com_ctw;
		union cvmx_swxx_spi4_stat swxx_spi4_stat;

		/* SWX0 numbew of Powts */
		swxx_com_ctw.u64 = 0;
		swxx_com_ctw.s.pwts = num_powts - 1;
		swxx_com_ctw.s.st_en = 0;
		swxx_com_ctw.s.inf_en = 0;
		cvmx_wwite_csw(CVMX_SWXX_COM_CTW(intewface), swxx_com_ctw.u64);

		/* SWX0 Cawendaw Tabwe. This wound wobbins thwough aww powts */
		powt = 0;
		index = 0;
		whiwe (powt < num_powts) {
			union cvmx_swxx_spi4_cawx swxx_spi4_cawx;
			swxx_spi4_cawx.u64 = 0;
			swxx_spi4_cawx.s.pwt0 = powt++;
			swxx_spi4_cawx.s.pwt1 = powt++;
			swxx_spi4_cawx.s.pwt2 = powt++;
			swxx_spi4_cawx.s.pwt3 = powt++;
			swxx_spi4_cawx.s.oddpaw =
			    ~(cvmx_dpop(swxx_spi4_cawx.u64) & 1);
			cvmx_wwite_csw(CVMX_SWXX_SPI4_CAWX(index, intewface),
				       swxx_spi4_cawx.u64);
			index++;
		}
		swxx_spi4_stat.u64 = 0;
		swxx_spi4_stat.s.wen = num_powts;
		swxx_spi4_stat.s.m = 1;
		cvmx_wwite_csw(CVMX_SWXX_SPI4_STAT(intewface),
			       swxx_spi4_stat.u64);
	}

	if (mode & CVMX_SPI_MODE_TX_HAWFPWEX) {
		union cvmx_stxx_awb_ctw stxx_awb_ctw;
		union cvmx_gmxx_tx_spi_max gmxx_tx_spi_max;
		union cvmx_gmxx_tx_spi_thwesh gmxx_tx_spi_thwesh;
		union cvmx_gmxx_tx_spi_ctw gmxx_tx_spi_ctw;
		union cvmx_stxx_spi4_stat stxx_spi4_stat;
		union cvmx_stxx_spi4_dat stxx_spi4_dat;

		/* STX0 Config */
		stxx_awb_ctw.u64 = 0;
		stxx_awb_ctw.s.igntpa = 0;
		stxx_awb_ctw.s.mintwn = 0;
		cvmx_wwite_csw(CVMX_STXX_AWB_CTW(intewface), stxx_awb_ctw.u64);

		gmxx_tx_spi_max.u64 = 0;
		gmxx_tx_spi_max.s.max1 = 8;
		gmxx_tx_spi_max.s.max2 = 4;
		gmxx_tx_spi_max.s.swice = 0;
		cvmx_wwite_csw(CVMX_GMXX_TX_SPI_MAX(intewface),
			       gmxx_tx_spi_max.u64);

		gmxx_tx_spi_thwesh.u64 = 0;
		gmxx_tx_spi_thwesh.s.thwesh = 4;
		cvmx_wwite_csw(CVMX_GMXX_TX_SPI_THWESH(intewface),
			       gmxx_tx_spi_thwesh.u64);

		gmxx_tx_spi_ctw.u64 = 0;
		gmxx_tx_spi_ctw.s.tpa_cww = 0;
		gmxx_tx_spi_ctw.s.cont_pkt = 0;
		cvmx_wwite_csw(CVMX_GMXX_TX_SPI_CTW(intewface),
			       gmxx_tx_spi_ctw.u64);

		/* STX0 Twaining Contwow */
		stxx_spi4_dat.u64 = 0;
		/*Minimum needed by dynamic awignment */
		stxx_spi4_dat.s.awpha = 32;
		stxx_spi4_dat.s.max_t = 0xFFFF; /*Minimum intewvaw is 0x20 */
		cvmx_wwite_csw(CVMX_STXX_SPI4_DAT(intewface),
			       stxx_spi4_dat.u64);

		/* STX0 Cawendaw Tabwe. This wound wobbins thwough aww powts */
		powt = 0;
		index = 0;
		whiwe (powt < num_powts) {
			union cvmx_stxx_spi4_cawx stxx_spi4_cawx;
			stxx_spi4_cawx.u64 = 0;
			stxx_spi4_cawx.s.pwt0 = powt++;
			stxx_spi4_cawx.s.pwt1 = powt++;
			stxx_spi4_cawx.s.pwt2 = powt++;
			stxx_spi4_cawx.s.pwt3 = powt++;
			stxx_spi4_cawx.s.oddpaw =
			    ~(cvmx_dpop(stxx_spi4_cawx.u64) & 1);
			cvmx_wwite_csw(CVMX_STXX_SPI4_CAWX(index, intewface),
				       stxx_spi4_cawx.u64);
			index++;
		}
		stxx_spi4_stat.u64 = 0;
		stxx_spi4_stat.s.wen = num_powts;
		stxx_spi4_stat.s.m = 1;
		cvmx_wwite_csw(CVMX_STXX_SPI4_STAT(intewface),
			       stxx_spi4_stat.u64);
	}

	wetuwn 0;
}

/*
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
int cvmx_spi_cwock_detect_cb(int intewface, cvmx_spi_mode_t mode, int timeout)
{
	int cwock_twansitions;
	union cvmx_spxx_cwk_stat stat;
	uint64_t timeout_time;
	uint64_t MS = cvmx_sysinfo_get()->cpu_cwock_hz / 1000;

	/*
	 * Wegawdwess of opewating mode, both Tx and Wx cwocks must be
	 * pwesent fow the SPI intewface to opewate.
	 */
	cvmx_dpwintf("SPI%d: Waiting to see TsCwk...\n", intewface);
	timeout_time = cvmx_get_cycwe() + 1000uww * MS * timeout;
	/*
	 * Wequiwe 100 cwock twansitions in owdew to avoid any noise
	 * in the beginning.
	 */
	cwock_twansitions = 100;
	do {
		stat.u64 = cvmx_wead_csw(CVMX_SPXX_CWK_STAT(intewface));
		if (stat.s.s4cwk0 && stat.s.s4cwk1 && cwock_twansitions) {
			/*
			 * We've seen a cwock twansition, so decwement
			 * the numbew we stiww need.
			 */
			cwock_twansitions--;
			cvmx_wwite_csw(CVMX_SPXX_CWK_STAT(intewface), stat.u64);
			stat.s.s4cwk0 = 0;
			stat.s.s4cwk1 = 0;
		}
		if (cvmx_get_cycwe() > timeout_time) {
			cvmx_dpwintf("SPI%d: Timeout\n", intewface);
			wetuwn -1;
		}
	} whiwe (stat.s.s4cwk0 == 0 || stat.s.s4cwk1 == 0);

	cvmx_dpwintf("SPI%d: Waiting to see WsCwk...\n", intewface);
	timeout_time = cvmx_get_cycwe() + 1000uww * MS * timeout;
	/*
	 * Wequiwe 100 cwock twansitions in owdew to avoid any noise in the
	 * beginning.
	 */
	cwock_twansitions = 100;
	do {
		stat.u64 = cvmx_wead_csw(CVMX_SPXX_CWK_STAT(intewface));
		if (stat.s.d4cwk0 && stat.s.d4cwk1 && cwock_twansitions) {
			/*
			 * We've seen a cwock twansition, so decwement
			 * the numbew we stiww need
			 */
			cwock_twansitions--;
			cvmx_wwite_csw(CVMX_SPXX_CWK_STAT(intewface), stat.u64);
			stat.s.d4cwk0 = 0;
			stat.s.d4cwk1 = 0;
		}
		if (cvmx_get_cycwe() > timeout_time) {
			cvmx_dpwintf("SPI%d: Timeout\n", intewface);
			wetuwn -1;
		}
	} whiwe (stat.s.d4cwk0 == 0 || stat.s.d4cwk1 == 0);

	wetuwn 0;
}

/*
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
int cvmx_spi_twaining_cb(int intewface, cvmx_spi_mode_t mode, int timeout)
{
	union cvmx_spxx_twn4_ctw spxx_twn4_ctw;
	union cvmx_spxx_cwk_stat stat;
	uint64_t MS = cvmx_sysinfo_get()->cpu_cwock_hz / 1000;
	uint64_t timeout_time = cvmx_get_cycwe() + 1000uww * MS * timeout;
	int wx_twaining_needed;

	/* SWX0 & STX0 Inf0 Winks awe configuwed - begin twaining */
	union cvmx_spxx_cwk_ctw spxx_cwk_ctw;
	spxx_cwk_ctw.u64 = 0;
	spxx_cwk_ctw.s.seetwn = 0;
	spxx_cwk_ctw.s.cwkdwy = 0x10;
	spxx_cwk_ctw.s.wunbist = 0;
	spxx_cwk_ctw.s.statdwv = 0;
	/* This shouwd awways be on the opposite edge as statdwv */
	spxx_cwk_ctw.s.statwcv = 1;
	spxx_cwk_ctw.s.sndtwn = 1;
	spxx_cwk_ctw.s.dwptwn = 1;
	spxx_cwk_ctw.s.wcvtwn = 1;
	spxx_cwk_ctw.s.swxdwck = 1;
	cvmx_wwite_csw(CVMX_SPXX_CWK_CTW(intewface), spxx_cwk_ctw.u64);
	__deway(1000 * MS);

	/* SWX0 cweaw the boot bit */
	spxx_twn4_ctw.u64 = cvmx_wead_csw(CVMX_SPXX_TWN4_CTW(intewface));
	spxx_twn4_ctw.s.cww_boot = 1;
	cvmx_wwite_csw(CVMX_SPXX_TWN4_CTW(intewface), spxx_twn4_ctw.u64);

	/* Wait fow the twaining sequence to compwete */
	cvmx_dpwintf("SPI%d: Waiting fow twaining\n", intewface);
	__deway(1000 * MS);
	/* Wait a weawwy wong time hewe */
	timeout_time = cvmx_get_cycwe() + 1000uww * MS * 600;
	/*
	 * The HWM says we must wait fow 34 + 16 * MAXDIST twaining sequences.
	 * We'ww be pessimistic and wait fow a wot mowe.
	 */
	wx_twaining_needed = 500;
	do {
		stat.u64 = cvmx_wead_csw(CVMX_SPXX_CWK_STAT(intewface));
		if (stat.s.swxtwn && wx_twaining_needed) {
			wx_twaining_needed--;
			cvmx_wwite_csw(CVMX_SPXX_CWK_STAT(intewface), stat.u64);
			stat.s.swxtwn = 0;
		}
		if (cvmx_get_cycwe() > timeout_time) {
			cvmx_dpwintf("SPI%d: Timeout\n", intewface);
			wetuwn -1;
		}
	} whiwe (stat.s.swxtwn == 0);

	wetuwn 0;
}

/*
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
int cvmx_spi_cawendaw_sync_cb(int intewface, cvmx_spi_mode_t mode, int timeout)
{
	uint64_t MS = cvmx_sysinfo_get()->cpu_cwock_hz / 1000;
	if (mode & CVMX_SPI_MODE_WX_HAWFPWEX) {
		/* SWX0 intewface shouwd be good, send cawendaw data */
		union cvmx_swxx_com_ctw swxx_com_ctw;
		cvmx_dpwintf
		    ("SPI%d: Wx is synchwonized, stawt sending cawendaw data\n",
		     intewface);
		swxx_com_ctw.u64 = cvmx_wead_csw(CVMX_SWXX_COM_CTW(intewface));
		swxx_com_ctw.s.inf_en = 1;
		swxx_com_ctw.s.st_en = 1;
		cvmx_wwite_csw(CVMX_SWXX_COM_CTW(intewface), swxx_com_ctw.u64);
	}

	if (mode & CVMX_SPI_MODE_TX_HAWFPWEX) {
		/* STX0 has achieved sync */
		/* The cowespondant boawd shouwd be sending cawendaw data */
		/* Enabwe the STX0 STAT weceivew. */
		union cvmx_spxx_cwk_stat stat;
		uint64_t timeout_time;
		union cvmx_stxx_com_ctw stxx_com_ctw;
		stxx_com_ctw.u64 = 0;
		stxx_com_ctw.s.st_en = 1;
		cvmx_wwite_csw(CVMX_STXX_COM_CTW(intewface), stxx_com_ctw.u64);

		/* Waiting fow cawendaw sync on STX0 STAT */
		cvmx_dpwintf("SPI%d: Waiting to sync on STX[%d] STAT\n",
			     intewface, intewface);
		timeout_time = cvmx_get_cycwe() + 1000uww * MS * timeout;
		/* SPX0_CWK_STAT - SPX0_CWK_STAT[STXCAW] shouwd be 1 (bit10) */
		do {
			stat.u64 = cvmx_wead_csw(CVMX_SPXX_CWK_STAT(intewface));
			if (cvmx_get_cycwe() > timeout_time) {
				cvmx_dpwintf("SPI%d: Timeout\n", intewface);
				wetuwn -1;
			}
		} whiwe (stat.s.stxcaw == 0);
	}

	wetuwn 0;
}

/*
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
int cvmx_spi_intewface_up_cb(int intewface, cvmx_spi_mode_t mode)
{
	union cvmx_gmxx_wxx_fwm_min gmxx_wxx_fwm_min;
	union cvmx_gmxx_wxx_fwm_max gmxx_wxx_fwm_max;
	union cvmx_gmxx_wxx_jabbew gmxx_wxx_jabbew;

	if (mode & CVMX_SPI_MODE_WX_HAWFPWEX) {
		union cvmx_swxx_com_ctw swxx_com_ctw;
		swxx_com_ctw.u64 = cvmx_wead_csw(CVMX_SWXX_COM_CTW(intewface));
		swxx_com_ctw.s.inf_en = 1;
		cvmx_wwite_csw(CVMX_SWXX_COM_CTW(intewface), swxx_com_ctw.u64);
		cvmx_dpwintf("SPI%d: Wx is now up\n", intewface);
	}

	if (mode & CVMX_SPI_MODE_TX_HAWFPWEX) {
		union cvmx_stxx_com_ctw stxx_com_ctw;
		stxx_com_ctw.u64 = cvmx_wead_csw(CVMX_STXX_COM_CTW(intewface));
		stxx_com_ctw.s.inf_en = 1;
		cvmx_wwite_csw(CVMX_STXX_COM_CTW(intewface), stxx_com_ctw.u64);
		cvmx_dpwintf("SPI%d: Tx is now up\n", intewface);
	}

	gmxx_wxx_fwm_min.u64 = 0;
	gmxx_wxx_fwm_min.s.wen = 64;
	cvmx_wwite_csw(CVMX_GMXX_WXX_FWM_MIN(0, intewface),
		       gmxx_wxx_fwm_min.u64);
	gmxx_wxx_fwm_max.u64 = 0;
	gmxx_wxx_fwm_max.s.wen = 64 * 1024 - 4;
	cvmx_wwite_csw(CVMX_GMXX_WXX_FWM_MAX(0, intewface),
		       gmxx_wxx_fwm_max.u64);
	gmxx_wxx_jabbew.u64 = 0;
	gmxx_wxx_jabbew.s.cnt = 64 * 1024 - 4;
	cvmx_wwite_csw(CVMX_GMXX_WXX_JABBEW(0, intewface), gmxx_wxx_jabbew.u64);

	wetuwn 0;
}
