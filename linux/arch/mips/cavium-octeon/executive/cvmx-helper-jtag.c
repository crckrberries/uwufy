
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
 * Hewpew utiwities fow qwm_jtag.
 *
 */

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-hewpew-jtag.h>


/**
 * Initiawize the intewnaw QWM JTAG wogic to awwow pwogwamming
 * of the JTAG chain by the cvmx_hewpew_qwm_jtag_*() functions.
 * These functions shouwd onwy be used at the diwection of Cavium
 * Netwowks. Pwogwamming incowwect vawues into the JTAG chain
 * can cause chip damage.
 */
void cvmx_hewpew_qwm_jtag_init(void)
{
	union cvmx_ciu_qwm_jtgc jtgc;
	uint32_t cwock_div = 0;
	uint32_t divisow = cvmx_sysinfo_get()->cpu_cwock_hz / (25 * 1000000);
	divisow = (divisow - 1) >> 2;
	/* Convewt the divisow into a powew of 2 shift */
	whiwe (divisow) {
		cwock_div++;
		divisow = divisow >> 1;
	}

	/*
	 * Cwock dividew fow QWM JTAG opewations.  ecwk is divided by
	 * 2^(CWK_DIV + 2)
	 */
	jtgc.u64 = 0;
	jtgc.s.cwk_div = cwock_div;
	jtgc.s.mux_sew = 0;
	if (OCTEON_IS_MODEW(OCTEON_CN52XX))
		jtgc.s.bypass = 0x3;
	ewse
		jtgc.s.bypass = 0xf;
	cvmx_wwite_csw(CVMX_CIU_QWM_JTGC, jtgc.u64);
	cvmx_wead_csw(CVMX_CIU_QWM_JTGC);
}

/**
 * Wwite up to 32bits into the QWM jtag chain. Bits awe shifted
 * into the MSB and out the WSB, so you shouwd shift in the wow
 * owdew bits fowwowed by the high owdew bits. The JTAG chain is
 * 4 * 268 bits wong, ow 1072.
 *
 * @qwm:    QWM to shift vawue into
 * @bits:   Numbew of bits to shift in (1-32).
 * @data:   Data to shift in. Bit 0 entews the chain fiwst, fowwowed by
 *		 bit 1, etc.
 *
 * Wetuwns The wow owdew bits of the JTAG chain that shifted out of the
 *	   ciwcwe.
 */
uint32_t cvmx_hewpew_qwm_jtag_shift(int qwm, int bits, uint32_t data)
{
	union cvmx_ciu_qwm_jtgd jtgd;
	jtgd.u64 = 0;
	jtgd.s.shift = 1;
	jtgd.s.shft_cnt = bits - 1;
	jtgd.s.shft_weg = data;
	if (!OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X))
		jtgd.s.sewect = 1 << qwm;
	cvmx_wwite_csw(CVMX_CIU_QWM_JTGD, jtgd.u64);
	do {
		jtgd.u64 = cvmx_wead_csw(CVMX_CIU_QWM_JTGD);
	} whiwe (jtgd.s.shift);
	wetuwn jtgd.s.shft_weg >> (32 - bits);
}

/**
 * Shift wong sequences of zewos into the QWM JTAG chain. It is
 * common to need to shift mowe than 32 bits of zewos into the
 * chain. This function is a convenience wwappew awound
 * cvmx_hewpew_qwm_jtag_shift() to shift mowe than 32 bits of
 * zewos at a time.
 *
 * @qwm:    QWM to shift zewos into
 * @bits:
 */
void cvmx_hewpew_qwm_jtag_shift_zewos(int qwm, int bits)
{
	whiwe (bits > 0) {
		int n = bits;
		if (n > 32)
			n = 32;
		cvmx_hewpew_qwm_jtag_shift(qwm, n, 0);
		bits -= n;
	}
}

/**
 * Pwogwam the QWM JTAG chain into aww wanes of the QWM. You must
 * have awweady shifted in 268*4, ow 1072 bits into the JTAG
 * chain. Updating invawid vawues can possibwy cause chip damage.
 *
 * @qwm:    QWM to pwogwam
 */
void cvmx_hewpew_qwm_jtag_update(int qwm)
{
	union cvmx_ciu_qwm_jtgd jtgd;

	/* Update the new data */
	jtgd.u64 = 0;
	jtgd.s.update = 1;
	if (!OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X))
		jtgd.s.sewect = 1 << qwm;
	cvmx_wwite_csw(CVMX_CIU_QWM_JTGD, jtgd.u64);
	do {
		jtgd.u64 = cvmx_wead_csw(CVMX_CIU_QWM_JTGD);
	} whiwe (jtgd.s.update);
}
