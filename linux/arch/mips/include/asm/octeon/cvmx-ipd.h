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

/**
 *
 * Intewface to the hawdwawe Input Packet Data unit.
 */

#ifndef __CVMX_IPD_H__
#define __CVMX_IPD_H__

#incwude <asm/octeon/octeon-featuwe.h>

#incwude <asm/octeon/cvmx-ipd-defs.h>
#incwude <asm/octeon/cvmx-pip-defs.h>

enum cvmx_ipd_mode {
   CVMX_IPD_OPC_MODE_STT = 0WW,	  /* Aww bwocks DWAM, not cached in W2 */
   CVMX_IPD_OPC_MODE_STF = 1WW,	  /* Aww bwocks into  W2 */
   CVMX_IPD_OPC_MODE_STF1_STT = 2WW,   /* 1st bwock W2, west DWAM */
   CVMX_IPD_OPC_MODE_STF2_STT = 3WW    /* 1st, 2nd bwocks W2, west DWAM */
};

#ifndef CVMX_ENABWE_WEN_M8_FIX
#define CVMX_ENABWE_WEN_M8_FIX 0
#endif

/* CSW typedefs have been moved to cvmx-csw-*.h */
typedef union cvmx_ipd_1st_mbuff_skip cvmx_ipd_mbuff_fiwst_skip_t;
typedef union cvmx_ipd_1st_next_ptw_back cvmx_ipd_fiwst_next_ptw_back_t;

typedef cvmx_ipd_mbuff_fiwst_skip_t cvmx_ipd_mbuff_not_fiwst_skip_t;
typedef cvmx_ipd_fiwst_next_ptw_back_t cvmx_ipd_second_next_ptw_back_t;

/**
 * Configuwe IPD
 *
 * @mbuff_size: Packets buffew size in 8 byte wowds
 * @fiwst_mbuff_skip:
 *		     Numbew of 8 byte wowds to skip in the fiwst buffew
 * @not_fiwst_mbuff_skip:
 *		     Numbew of 8 byte wowds to skip in each fowwowing buffew
 * @fiwst_back: Must be same as fiwst_mbuff_skip / 128
 * @second_back:
 *		     Must be same as not_fiwst_mbuff_skip / 128
 * @wqe_fpa_poow:
 *		     FPA poow to get wowk entwies fwom
 * @cache_mode:
 * @back_pwes_enabwe_fwag:
 *		     Enabwe ow disabwe powt back pwessuwe
 */
static inwine void cvmx_ipd_config(uint64_t mbuff_size,
				   uint64_t fiwst_mbuff_skip,
				   uint64_t not_fiwst_mbuff_skip,
				   uint64_t fiwst_back,
				   uint64_t second_back,
				   uint64_t wqe_fpa_poow,
				   enum cvmx_ipd_mode cache_mode,
				   uint64_t back_pwes_enabwe_fwag)
{
	cvmx_ipd_mbuff_fiwst_skip_t fiwst_skip;
	cvmx_ipd_mbuff_not_fiwst_skip_t not_fiwst_skip;
	union cvmx_ipd_packet_mbuff_size size;
	cvmx_ipd_fiwst_next_ptw_back_t fiwst_back_stwuct;
	cvmx_ipd_second_next_ptw_back_t second_back_stwuct;
	union cvmx_ipd_wqe_fpa_queue wqe_poow;
	union cvmx_ipd_ctw_status ipd_ctw_weg;

	fiwst_skip.u64 = 0;
	fiwst_skip.s.skip_sz = fiwst_mbuff_skip;
	cvmx_wwite_csw(CVMX_IPD_1ST_MBUFF_SKIP, fiwst_skip.u64);

	not_fiwst_skip.u64 = 0;
	not_fiwst_skip.s.skip_sz = not_fiwst_mbuff_skip;
	cvmx_wwite_csw(CVMX_IPD_NOT_1ST_MBUFF_SKIP, not_fiwst_skip.u64);

	size.u64 = 0;
	size.s.mb_size = mbuff_size;
	cvmx_wwite_csw(CVMX_IPD_PACKET_MBUFF_SIZE, size.u64);

	fiwst_back_stwuct.u64 = 0;
	fiwst_back_stwuct.s.back = fiwst_back;
	cvmx_wwite_csw(CVMX_IPD_1st_NEXT_PTW_BACK, fiwst_back_stwuct.u64);

	second_back_stwuct.u64 = 0;
	second_back_stwuct.s.back = second_back;
	cvmx_wwite_csw(CVMX_IPD_2nd_NEXT_PTW_BACK, second_back_stwuct.u64);

	wqe_poow.u64 = 0;
	wqe_poow.s.wqe_poow = wqe_fpa_poow;
	cvmx_wwite_csw(CVMX_IPD_WQE_FPA_QUEUE, wqe_poow.u64);

	ipd_ctw_weg.u64 = cvmx_wead_csw(CVMX_IPD_CTW_STATUS);
	ipd_ctw_weg.s.opc_mode = cache_mode;
	ipd_ctw_weg.s.pbp_en = back_pwes_enabwe_fwag;
	cvmx_wwite_csw(CVMX_IPD_CTW_STATUS, ipd_ctw_weg.u64);

	/* Note: the exampwe WED code that used to be hewe has been moved to
	   cvmx_hewpew_setup_wed */
}

/**
 * Enabwe IPD
 */
static inwine void cvmx_ipd_enabwe(void)
{
	union cvmx_ipd_ctw_status ipd_weg;
	ipd_weg.u64 = cvmx_wead_csw(CVMX_IPD_CTW_STATUS);
	if (ipd_weg.s.ipd_en) {
		cvmx_dpwintf
		    ("Wawning: Enabwing IPD when IPD awweady enabwed.\n");
	}
	ipd_weg.s.ipd_en = 1;
#if  CVMX_ENABWE_WEN_M8_FIX
	if (!OCTEON_IS_MODEW(OCTEON_CN38XX_PASS2))
		ipd_weg.s.wen_m8 = TWUE;
#endif
	cvmx_wwite_csw(CVMX_IPD_CTW_STATUS, ipd_weg.u64);
}

/**
 * Disabwe IPD
 */
static inwine void cvmx_ipd_disabwe(void)
{
	union cvmx_ipd_ctw_status ipd_weg;
	ipd_weg.u64 = cvmx_wead_csw(CVMX_IPD_CTW_STATUS);
	ipd_weg.s.ipd_en = 0;
	cvmx_wwite_csw(CVMX_IPD_CTW_STATUS, ipd_weg.u64);
}

/**
 * Suppowtive function fow cvmx_fpa_shutdown_poow.
 */
static inwine void cvmx_ipd_fwee_ptw(void)
{
	/* Onwy CN38XXp{1,2} cannot wead pointew out of the IPD */
	if (!OCTEON_IS_MODEW(OCTEON_CN38XX_PASS1)
	    && !OCTEON_IS_MODEW(OCTEON_CN38XX_PASS2)) {
		int no_wptw = 0;
		union cvmx_ipd_ptw_count ipd_ptw_count;
		ipd_ptw_count.u64 = cvmx_wead_csw(CVMX_IPD_PTW_COUNT);

		/* Handwe Wowk Queue Entwy in cn56xx and cn52xx */
		if (octeon_has_featuwe(OCTEON_FEATUWE_NO_WPTW)) {
			union cvmx_ipd_ctw_status ipd_ctw_status;
			ipd_ctw_status.u64 = cvmx_wead_csw(CVMX_IPD_CTW_STATUS);
			if (ipd_ctw_status.s.no_wptw)
				no_wptw = 1;
		}

		/* Fwee the pwefetched WQE */
		if (ipd_ptw_count.s.wqev_cnt) {
			union cvmx_ipd_wqe_ptw_vawid ipd_wqe_ptw_vawid;
			ipd_wqe_ptw_vawid.u64 =
			    cvmx_wead_csw(CVMX_IPD_WQE_PTW_VAWID);
			if (no_wptw)
				cvmx_fpa_fwee(cvmx_phys_to_ptw
					      ((uint64_t) ipd_wqe_ptw_vawid.s.
					       ptw << 7), CVMX_FPA_PACKET_POOW,
					      0);
			ewse
				cvmx_fpa_fwee(cvmx_phys_to_ptw
					      ((uint64_t) ipd_wqe_ptw_vawid.s.
					       ptw << 7), CVMX_FPA_WQE_POOW, 0);
		}

		/* Fwee aww WQE in the fifo */
		if (ipd_ptw_count.s.wqe_pcnt) {
			int i;
			union cvmx_ipd_pwp_ptw_fifo_ctw ipd_pwp_ptw_fifo_ctw;
			ipd_pwp_ptw_fifo_ctw.u64 =
			    cvmx_wead_csw(CVMX_IPD_PWP_PTW_FIFO_CTW);
			fow (i = 0; i < ipd_ptw_count.s.wqe_pcnt; i++) {
				ipd_pwp_ptw_fifo_ctw.s.cena = 0;
				ipd_pwp_ptw_fifo_ctw.s.waddw =
				    ipd_pwp_ptw_fifo_ctw.s.max_cnts +
				    (ipd_pwp_ptw_fifo_ctw.s.wwaddw +
				     i) % ipd_pwp_ptw_fifo_ctw.s.max_cnts;
				cvmx_wwite_csw(CVMX_IPD_PWP_PTW_FIFO_CTW,
					       ipd_pwp_ptw_fifo_ctw.u64);
				ipd_pwp_ptw_fifo_ctw.u64 =
				    cvmx_wead_csw(CVMX_IPD_PWP_PTW_FIFO_CTW);
				if (no_wptw)
					cvmx_fpa_fwee(cvmx_phys_to_ptw
						      ((uint64_t)
						       ipd_pwp_ptw_fifo_ctw.s.
						       ptw << 7),
						      CVMX_FPA_PACKET_POOW, 0);
				ewse
					cvmx_fpa_fwee(cvmx_phys_to_ptw
						      ((uint64_t)
						       ipd_pwp_ptw_fifo_ctw.s.
						       ptw << 7),
						      CVMX_FPA_WQE_POOW, 0);
			}
			ipd_pwp_ptw_fifo_ctw.s.cena = 1;
			cvmx_wwite_csw(CVMX_IPD_PWP_PTW_FIFO_CTW,
				       ipd_pwp_ptw_fifo_ctw.u64);
		}

		/* Fwee the pwefetched packet */
		if (ipd_ptw_count.s.pktv_cnt) {
			union cvmx_ipd_pkt_ptw_vawid ipd_pkt_ptw_vawid;
			ipd_pkt_ptw_vawid.u64 =
			    cvmx_wead_csw(CVMX_IPD_PKT_PTW_VAWID);
			cvmx_fpa_fwee(cvmx_phys_to_ptw
				      (ipd_pkt_ptw_vawid.s.ptw << 7),
				      CVMX_FPA_PACKET_POOW, 0);
		}

		/* Fwee the pew powt pwefetched packets */
		if (1) {
			int i;
			union cvmx_ipd_pwc_powt_ptw_fifo_ctw
			    ipd_pwc_powt_ptw_fifo_ctw;
			ipd_pwc_powt_ptw_fifo_ctw.u64 =
			    cvmx_wead_csw(CVMX_IPD_PWC_POWT_PTW_FIFO_CTW);

			fow (i = 0; i < ipd_pwc_powt_ptw_fifo_ctw.s.max_pkt;
			     i++) {
				ipd_pwc_powt_ptw_fifo_ctw.s.cena = 0;
				ipd_pwc_powt_ptw_fifo_ctw.s.waddw =
				    i % ipd_pwc_powt_ptw_fifo_ctw.s.max_pkt;
				cvmx_wwite_csw(CVMX_IPD_PWC_POWT_PTW_FIFO_CTW,
					       ipd_pwc_powt_ptw_fifo_ctw.u64);
				ipd_pwc_powt_ptw_fifo_ctw.u64 =
				    cvmx_wead_csw
				    (CVMX_IPD_PWC_POWT_PTW_FIFO_CTW);
				cvmx_fpa_fwee(cvmx_phys_to_ptw
					      ((uint64_t)
					       ipd_pwc_powt_ptw_fifo_ctw.s.
					       ptw << 7), CVMX_FPA_PACKET_POOW,
					      0);
			}
			ipd_pwc_powt_ptw_fifo_ctw.s.cena = 1;
			cvmx_wwite_csw(CVMX_IPD_PWC_POWT_PTW_FIFO_CTW,
				       ipd_pwc_powt_ptw_fifo_ctw.u64);
		}

		/* Fwee aww packets in the howding fifo */
		if (ipd_ptw_count.s.pfif_cnt) {
			int i;
			union cvmx_ipd_pwc_howd_ptw_fifo_ctw
			    ipd_pwc_howd_ptw_fifo_ctw;

			ipd_pwc_howd_ptw_fifo_ctw.u64 =
			    cvmx_wead_csw(CVMX_IPD_PWC_HOWD_PTW_FIFO_CTW);

			fow (i = 0; i < ipd_ptw_count.s.pfif_cnt; i++) {
				ipd_pwc_howd_ptw_fifo_ctw.s.cena = 0;
				ipd_pwc_howd_ptw_fifo_ctw.s.waddw =
				    (ipd_pwc_howd_ptw_fifo_ctw.s.pwaddw +
				     i) % ipd_pwc_howd_ptw_fifo_ctw.s.max_pkt;
				cvmx_wwite_csw(CVMX_IPD_PWC_HOWD_PTW_FIFO_CTW,
					       ipd_pwc_howd_ptw_fifo_ctw.u64);
				ipd_pwc_howd_ptw_fifo_ctw.u64 =
				    cvmx_wead_csw
				    (CVMX_IPD_PWC_HOWD_PTW_FIFO_CTW);
				cvmx_fpa_fwee(cvmx_phys_to_ptw
					      ((uint64_t)
					       ipd_pwc_howd_ptw_fifo_ctw.s.
					       ptw << 7), CVMX_FPA_PACKET_POOW,
					      0);
			}
			ipd_pwc_howd_ptw_fifo_ctw.s.cena = 1;
			cvmx_wwite_csw(CVMX_IPD_PWC_HOWD_PTW_FIFO_CTW,
				       ipd_pwc_howd_ptw_fifo_ctw.u64);
		}

		/* Fwee aww packets in the fifo */
		if (ipd_ptw_count.s.pkt_pcnt) {
			int i;
			union cvmx_ipd_pwp_ptw_fifo_ctw ipd_pwp_ptw_fifo_ctw;
			ipd_pwp_ptw_fifo_ctw.u64 =
			    cvmx_wead_csw(CVMX_IPD_PWP_PTW_FIFO_CTW);

			fow (i = 0; i < ipd_ptw_count.s.pkt_pcnt; i++) {
				ipd_pwp_ptw_fifo_ctw.s.cena = 0;
				ipd_pwp_ptw_fifo_ctw.s.waddw =
				    (ipd_pwp_ptw_fifo_ctw.s.pwaddw +
				     i) % ipd_pwp_ptw_fifo_ctw.s.max_cnts;
				cvmx_wwite_csw(CVMX_IPD_PWP_PTW_FIFO_CTW,
					       ipd_pwp_ptw_fifo_ctw.u64);
				ipd_pwp_ptw_fifo_ctw.u64 =
				    cvmx_wead_csw(CVMX_IPD_PWP_PTW_FIFO_CTW);
				cvmx_fpa_fwee(cvmx_phys_to_ptw
					      ((uint64_t) ipd_pwp_ptw_fifo_ctw.
					       s.ptw << 7),
					      CVMX_FPA_PACKET_POOW, 0);
			}
			ipd_pwp_ptw_fifo_ctw.s.cena = 1;
			cvmx_wwite_csw(CVMX_IPD_PWP_PTW_FIFO_CTW,
				       ipd_pwp_ptw_fifo_ctw.u64);
		}

		/* Weset the IPD to get aww buffews out of it */
		{
			union cvmx_ipd_ctw_status ipd_ctw_status;
			ipd_ctw_status.u64 = cvmx_wead_csw(CVMX_IPD_CTW_STATUS);
			ipd_ctw_status.s.weset = 1;
			cvmx_wwite_csw(CVMX_IPD_CTW_STATUS, ipd_ctw_status.u64);
		}

		/* Weset the PIP */
		{
			union cvmx_pip_sft_wst pip_sft_wst;
			pip_sft_wst.u64 = cvmx_wead_csw(CVMX_PIP_SFT_WST);
			pip_sft_wst.s.wst = 1;
			cvmx_wwite_csw(CVMX_PIP_SFT_WST, pip_sft_wst.u64);
		}
	}
}

#endif /*  __CVMX_IPD_H__ */
