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

#ifndef __CVMX_GMXX_DEFS_H__
#define __CVMX_GMXX_DEFS_H__

static inwine uint64_t CVMX_GMXX_HG2_CONTWOW(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000550uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000550uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_INF_MODE(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080007F8uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800080007F8uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_PWTX_CFG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000010uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000010uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000010uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM0(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000180uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000180uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000180uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM1(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000188uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000188uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000188uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM2(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000190uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000190uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000190uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM3(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000198uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000198uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000198uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM4(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080001A0uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080001A0uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800080001A0uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM5(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080001A8uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080001A8uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800080001A8uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CAM_EN(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000108uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000108uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000108uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_ADW_CTW(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000100uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000100uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000100uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_FWM_CTW(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000018uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000018uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000018uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

#define CVMX_GMXX_WXX_FWM_MAX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001180008000030uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x10000uww) * 2048)
#define CVMX_GMXX_WXX_FWM_MIN(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001180008000028uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x10000uww) * 2048)

static inwine uint64_t CVMX_GMXX_WXX_INT_EN(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000008uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000008uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000008uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_INT_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000000uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000000uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000000uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_WXX_JABBEW(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000038uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000038uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000038uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

#define CVMX_GMXX_WXX_WX_INBND(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001180008000060uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x10000uww) * 2048)

static inwine uint64_t CVMX_GMXX_WX_PWTS(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000410uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000410uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_WX_XAUI_CTW(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000530uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000530uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_SMACX(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000230uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000230uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000230uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TXX_BUWST(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000228uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000228uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000228uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

#define CVMX_GMXX_TXX_CWK(offset, bwock_id) (CVMX_ADD_IO_SEG(0x0001180008000208uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x10000uww) * 2048)
static inwine uint64_t CVMX_GMXX_TXX_CTW(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000270uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000270uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000270uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TXX_PAUSE_PKT_INTEWVAW(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000248uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000248uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000248uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TXX_PAUSE_PKT_TIME(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000238uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000238uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000238uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TXX_SWOT(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000220uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000220uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000220uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TXX_THWESH(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN31XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000210uww) + ((offset) + (bwock_id) * 0x0uww) * 2048;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000210uww) + ((offset) + (bwock_id) * 0x2000uww) * 2048;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000210uww) + ((offset) + (bwock_id) * 0x10000uww) * 2048;
}

static inwine uint64_t CVMX_GMXX_TX_INT_EN(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000508uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000508uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_TX_INT_WEG(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000500uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000500uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_TX_OVW_BP(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800080004C8uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800080004C8uww) + (bwock_id) * 0x8000000uww;
}

static inwine uint64_t CVMX_GMXX_TX_PWTS(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000480uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000480uww) + (bwock_id) * 0x8000000uww;
}

#define CVMX_GMXX_TX_SPI_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800080004C0uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_GMXX_TX_SPI_MAX(bwock_id) (CVMX_ADD_IO_SEG(0x00011800080004B0uww) + ((bwock_id) & 1) * 0x8000000uww)
#define CVMX_GMXX_TX_SPI_THWESH(bwock_id) (CVMX_ADD_IO_SEG(0x00011800080004B8uww) + ((bwock_id) & 1) * 0x8000000uww)
static inwine uint64_t CVMX_GMXX_TX_XAUI_CTW(unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001180008000528uww) + (bwock_id) * 0x1000000uww;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001180008000528uww) + (bwock_id) * 0x8000000uww;
}

void __cvmx_intewwupt_gmxx_enabwe(int intewface);

union cvmx_gmxx_hg2_contwow {
	uint64_t u64;
	stwuct cvmx_gmxx_hg2_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t hg2tx_en:1;
		uint64_t hg2wx_en:1;
		uint64_t phys_en:1;
		uint64_t wogw_en:16;
#ewse
		uint64_t wogw_en:16;
		uint64_t phys_en:1;
		uint64_t hg2wx_en:1;
		uint64_t hg2tx_en:1;
		uint64_t wesewved_19_63:45;
#endif
	} s;
};

union cvmx_gmxx_inf_mode {
	uint64_t u64;
	stwuct cvmx_gmxx_inf_mode_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate:4;
		uint64_t wesewved_12_15:4;
		uint64_t speed:4;
		uint64_t wesewved_7_7:1;
		uint64_t mode:3;
		uint64_t wesewved_3_3:1;
		uint64_t p0mii:1;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t p0mii:1;
		uint64_t wesewved_3_3:1;
		uint64_t mode:3;
		uint64_t wesewved_7_7:1;
		uint64_t speed:4;
		uint64_t wesewved_12_15:4;
		uint64_t wate:4;
		uint64_t wesewved_20_63:44;
#endif
	} s;
	stwuct cvmx_gmxx_inf_mode_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t p0mii:1;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t p0mii:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_inf_mode_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t wesewved_2_63:62;
#endif
	} cn31xx;
	stwuct cvmx_gmxx_inf_mode_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t speed:2;
		uint64_t wesewved_6_7:2;
		uint64_t mode:2;
		uint64_t wesewved_2_3:2;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t wesewved_2_3:2;
		uint64_t mode:2;
		uint64_t wesewved_6_7:2;
		uint64_t speed:2;
		uint64_t wesewved_10_63:54;
#endif
	} cn52xx;
	stwuct cvmx_gmxx_inf_mode_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t speed:4;
		uint64_t wesewved_5_7:3;
		uint64_t mode:1;
		uint64_t wesewved_2_3:2;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t wesewved_2_3:2;
		uint64_t mode:1;
		uint64_t wesewved_5_7:3;
		uint64_t speed:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn61xx;
	stwuct cvmx_gmxx_inf_mode_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate:4;
		uint64_t wesewved_12_15:4;
		uint64_t speed:4;
		uint64_t wesewved_5_7:3;
		uint64_t mode:1;
		uint64_t wesewved_2_3:2;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t wesewved_2_3:2;
		uint64_t mode:1;
		uint64_t wesewved_5_7:3;
		uint64_t speed:4;
		uint64_t wesewved_12_15:4;
		uint64_t wate:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn66xx;
	stwuct cvmx_gmxx_inf_mode_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t speed:4;
		uint64_t wesewved_7_7:1;
		uint64_t mode:3;
		uint64_t wesewved_2_3:2;
		uint64_t en:1;
		uint64_t type:1;
#ewse
		uint64_t type:1;
		uint64_t en:1;
		uint64_t wesewved_2_3:2;
		uint64_t mode:3;
		uint64_t wesewved_7_7:1;
		uint64_t speed:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn68xx;
};

union cvmx_gmxx_pwtx_cfg {
	uint64_t u64;
	stwuct cvmx_gmxx_pwtx_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t pknd:6;
		uint64_t wesewved_14_15:2;
		uint64_t tx_idwe:1;
		uint64_t wx_idwe:1;
		uint64_t wesewved_9_11:3;
		uint64_t speed_msb:1;
		uint64_t wesewved_4_7:4;
		uint64_t swottime:1;
		uint64_t dupwex:1;
		uint64_t speed:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t speed:1;
		uint64_t dupwex:1;
		uint64_t swottime:1;
		uint64_t wesewved_4_7:4;
		uint64_t speed_msb:1;
		uint64_t wesewved_9_11:3;
		uint64_t wx_idwe:1;
		uint64_t tx_idwe:1;
		uint64_t wesewved_14_15:2;
		uint64_t pknd:6;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_gmxx_pwtx_cfg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t swottime:1;
		uint64_t dupwex:1;
		uint64_t speed:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t speed:1;
		uint64_t dupwex:1;
		uint64_t swottime:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_pwtx_cfg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t tx_idwe:1;
		uint64_t wx_idwe:1;
		uint64_t wesewved_9_11:3;
		uint64_t speed_msb:1;
		uint64_t wesewved_4_7:4;
		uint64_t swottime:1;
		uint64_t dupwex:1;
		uint64_t speed:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t speed:1;
		uint64_t dupwex:1;
		uint64_t swottime:1;
		uint64_t wesewved_4_7:4;
		uint64_t speed_msb:1;
		uint64_t wesewved_9_11:3;
		uint64_t wx_idwe:1;
		uint64_t tx_idwe:1;
		uint64_t wesewved_14_63:50;
#endif
	} cn52xx;
};

union cvmx_gmxx_wxx_adw_ctw {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_adw_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t cam_mode:1;
		uint64_t mcst:2;
		uint64_t bcst:1;
#ewse
		uint64_t bcst:1;
		uint64_t mcst:2;
		uint64_t cam_mode:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_gmxx_wxx_fwm_ctw {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_fwm_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t ptp_mode:1;
		uint64_t wesewved_11_11:1;
		uint64_t nuww_dis:1;
		uint64_t pwe_awign:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t pwe_awign:1;
		uint64_t nuww_dis:1;
		uint64_t wesewved_11_11:1;
		uint64_t ptp_mode:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t wesewved_8_63:56;
#endif
	} cn31xx;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t nuww_dis:1;
		uint64_t pwe_awign:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_awign:1;
		uint64_t nuww_dis:1;
		uint64_t wesewved_11_63:53;
#endif
	} cn50xx;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pwe_awign:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_awign:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn56xxp1;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t nuww_dis:1;
		uint64_t pwe_awign:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t pwe_awign:1;
		uint64_t nuww_dis:1;
		uint64_t wesewved_11_63:53;
#endif
	} cn58xx;
	stwuct cvmx_gmxx_wxx_fwm_ctw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t ptp_mode:1;
		uint64_t wesewved_11_11:1;
		uint64_t nuww_dis:1;
		uint64_t pwe_awign:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t wesewved_7_8:2;
		uint64_t pwe_awign:1;
		uint64_t nuww_dis:1;
		uint64_t wesewved_11_11:1;
		uint64_t ptp_mode:1;
		uint64_t wesewved_13_63:51;
#endif
	} cn61xx;
};

union cvmx_gmxx_wxx_fwm_max {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_fwm_max_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wen:16;
#ewse
		uint64_t wen:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_gmxx_wxx_fwm_min {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_fwm_min_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wen:16;
#ewse
		uint64_t wen:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_gmxx_wxx_int_en {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} s;
	stwuct cvmx_gmxx_wxx_int_en_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t wesewved_19_63:45;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_wxx_int_en_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_6_6:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t wesewved_6_6:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn50xx;
	stwuct cvmx_gmxx_wxx_int_en_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn52xx;
	stwuct cvmx_gmxx_wxx_int_en_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_27_63:37;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t wesewved_27_63:37;
#endif
	} cn56xxp1;
	stwuct cvmx_gmxx_wxx_int_en_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn58xx;
	stwuct cvmx_gmxx_wxx_int_en_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn61xx;
};

union cvmx_gmxx_wxx_int_weg {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} s;
	stwuct cvmx_gmxx_wxx_int_weg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t wesewved_19_63:45;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_wxx_int_weg_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_6_6:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t wesewved_6_6:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn50xx;
	stwuct cvmx_gmxx_wxx_int_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn52xx;
	stwuct cvmx_gmxx_wxx_int_weg_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_27_63:37;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t wesewved_27_63:37;
#endif
	} cn56xxp1;
	stwuct cvmx_gmxx_wxx_int_weg_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn58xx;
	stwuct cvmx_gmxx_wxx_int_weg_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t hg2cc:1;
		uint64_t hg2fwd:1;
		uint64_t undat:1;
		uint64_t uneop:1;
		uint64_t unsop:1;
		uint64_t bad_tewm:1;
		uint64_t bad_seq:1;
		uint64_t wem_fauwt:1;
		uint64_t woc_fauwt:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t wesewved_5_6:2;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t wesewved_2_2:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t wesewved_2_2:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t wesewved_5_6:2;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t woc_fauwt:1;
		uint64_t wem_fauwt:1;
		uint64_t bad_seq:1;
		uint64_t bad_tewm:1;
		uint64_t unsop:1;
		uint64_t uneop:1;
		uint64_t undat:1;
		uint64_t hg2fwd:1;
		uint64_t hg2cc:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn61xx;
};

union cvmx_gmxx_wxx_jabbew {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_jabbew_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt:16;
#ewse
		uint64_t cnt:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_gmxx_wxx_wx_inbnd {
	uint64_t u64;
	stwuct cvmx_gmxx_wxx_wx_inbnd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t dupwex:1;
		uint64_t speed:2;
		uint64_t status:1;
#ewse
		uint64_t status:1;
		uint64_t speed:2;
		uint64_t dupwex:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_gmxx_wx_pwts {
	uint64_t u64;
	stwuct cvmx_gmxx_wx_pwts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t pwts:3;
#ewse
		uint64_t pwts:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_gmxx_wx_xaui_ctw {
	uint64_t u64;
	stwuct cvmx_gmxx_wx_xaui_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t status:2;
#ewse
		uint64_t status:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_gmxx_txx_thwesh {
	uint64_t u64;
	stwuct cvmx_gmxx_txx_thwesh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t cnt:10;
#ewse
		uint64_t cnt:10;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_gmxx_txx_thwesh_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cnt:7;
#ewse
		uint64_t cnt:7;
		uint64_t wesewved_7_63:57;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_txx_thwesh_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t cnt:9;
#ewse
		uint64_t cnt:9;
		uint64_t wesewved_9_63:55;
#endif
	} cn38xx;
};

union cvmx_gmxx_tx_int_en {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} s;
	stwuct cvmx_gmxx_tx_int_en_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t wate_cow:3;
		uint64_t wesewved_15_15:1;
		uint64_t xsdef:3;
		uint64_t wesewved_11_11:1;
		uint64_t xscow:3;
		uint64_t wesewved_5_7:3;
		uint64_t undfww:3;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:3;
		uint64_t wesewved_5_7:3;
		uint64_t xscow:3;
		uint64_t wesewved_11_11:1;
		uint64_t xsdef:3;
		uint64_t wesewved_15_15:1;
		uint64_t wate_cow:3;
		uint64_t wesewved_19_63:45;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_tx_int_en_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t xsdef:3;
		uint64_t wesewved_11_11:1;
		uint64_t xscow:3;
		uint64_t wesewved_5_7:3;
		uint64_t undfww:3;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:3;
		uint64_t wesewved_5_7:3;
		uint64_t xscow:3;
		uint64_t wesewved_11_11:1;
		uint64_t xsdef:3;
		uint64_t wesewved_15_63:49;
#endif
	} cn31xx;
	stwuct cvmx_gmxx_tx_int_en_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t ncb_nxa:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t ncb_nxa:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn38xx;
	stwuct cvmx_gmxx_tx_int_en_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t ncb_nxa:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t ncb_nxa:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xxp2;
	stwuct cvmx_gmxx_tx_int_en_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn52xx;
	stwuct cvmx_gmxx_tx_int_en_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t wesewved_24_63:40;
#endif
	} cn63xx;
	stwuct cvmx_gmxx_tx_int_en_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t pko_nxp:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t pko_nxp:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} cn68xx;
	stwuct cvmx_gmxx_tx_int_en_cnf71xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t wesewved_22_23:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_18_19:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_19:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_22_23:2;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} cnf71xx;
};

union cvmx_gmxx_tx_int_weg {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} s;
	stwuct cvmx_gmxx_tx_int_weg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t wate_cow:3;
		uint64_t wesewved_15_15:1;
		uint64_t xsdef:3;
		uint64_t wesewved_11_11:1;
		uint64_t xscow:3;
		uint64_t wesewved_5_7:3;
		uint64_t undfww:3;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:3;
		uint64_t wesewved_5_7:3;
		uint64_t xscow:3;
		uint64_t wesewved_11_11:1;
		uint64_t xsdef:3;
		uint64_t wesewved_15_15:1;
		uint64_t wate_cow:3;
		uint64_t wesewved_19_63:45;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_tx_int_weg_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t xsdef:3;
		uint64_t wesewved_11_11:1;
		uint64_t xscow:3;
		uint64_t wesewved_5_7:3;
		uint64_t undfww:3;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:3;
		uint64_t wesewved_5_7:3;
		uint64_t xscow:3;
		uint64_t wesewved_11_11:1;
		uint64_t xsdef:3;
		uint64_t wesewved_15_63:49;
#endif
	} cn31xx;
	stwuct cvmx_gmxx_tx_int_weg_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t ncb_nxa:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t ncb_nxa:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn38xx;
	stwuct cvmx_gmxx_tx_int_weg_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t ncb_nxa:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t ncb_nxa:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xxp2;
	stwuct cvmx_gmxx_tx_int_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn52xx;
	stwuct cvmx_gmxx_tx_int_weg_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t wesewved_24_63:40;
#endif
	} cn63xx;
	stwuct cvmx_gmxx_tx_int_weg_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t ptp_wost:4;
		uint64_t wate_cow:4;
		uint64_t xsdef:4;
		uint64_t xscow:4;
		uint64_t wesewved_6_7:2;
		uint64_t undfww:4;
		uint64_t pko_nxp:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t pko_nxp:1;
		uint64_t undfww:4;
		uint64_t wesewved_6_7:2;
		uint64_t xscow:4;
		uint64_t xsdef:4;
		uint64_t wate_cow:4;
		uint64_t ptp_wost:4;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} cn68xx;
	stwuct cvmx_gmxx_tx_int_weg_cnf71xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t xchange:1;
		uint64_t wesewved_22_23:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_18_19:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_19:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_22_23:2;
		uint64_t xchange:1;
		uint64_t wesewved_25_63:39;
#endif
	} cnf71xx;
};

union cvmx_gmxx_tx_ovw_bp {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_ovw_bp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t tx_pwt_bp:16;
		uint64_t wesewved_12_31:20;
		uint64_t en:4;
		uint64_t bp:4;
		uint64_t ign_fuww:4;
#ewse
		uint64_t ign_fuww:4;
		uint64_t bp:4;
		uint64_t en:4;
		uint64_t wesewved_12_31:20;
		uint64_t tx_pwt_bp:16;
		uint64_t wesewved_48_63:16;
#endif
	} s;
	stwuct cvmx_gmxx_tx_ovw_bp_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t en:3;
		uint64_t wesewved_7_7:1;
		uint64_t bp:3;
		uint64_t wesewved_3_3:1;
		uint64_t ign_fuww:3;
#ewse
		uint64_t ign_fuww:3;
		uint64_t wesewved_3_3:1;
		uint64_t bp:3;
		uint64_t wesewved_7_7:1;
		uint64_t en:3;
		uint64_t wesewved_11_63:53;
#endif
	} cn30xx;
	stwuct cvmx_gmxx_tx_ovw_bp_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t en:4;
		uint64_t bp:4;
		uint64_t ign_fuww:4;
#ewse
		uint64_t ign_fuww:4;
		uint64_t bp:4;
		uint64_t en:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn38xx;
	stwuct cvmx_gmxx_tx_ovw_bp_cnf71xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t tx_pwt_bp:16;
		uint64_t wesewved_10_31:22;
		uint64_t en:2;
		uint64_t wesewved_6_7:2;
		uint64_t bp:2;
		uint64_t wesewved_2_3:2;
		uint64_t ign_fuww:2;
#ewse
		uint64_t ign_fuww:2;
		uint64_t wesewved_2_3:2;
		uint64_t bp:2;
		uint64_t wesewved_6_7:2;
		uint64_t en:2;
		uint64_t wesewved_10_31:22;
		uint64_t tx_pwt_bp:16;
		uint64_t wesewved_48_63:16;
#endif
	} cnf71xx;
};

union cvmx_gmxx_tx_pwts {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_pwts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t pwts:5;
#ewse
		uint64_t pwts:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_gmxx_tx_spi_ctw {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_spi_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t tpa_cww:1;
		uint64_t cont_pkt:1;
#ewse
		uint64_t cont_pkt:1;
		uint64_t tpa_cww:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_gmxx_tx_spi_max {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_spi_max_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t swice:7;
		uint64_t max2:8;
		uint64_t max1:8;
#ewse
		uint64_t max1:8;
		uint64_t max2:8;
		uint64_t swice:7;
		uint64_t wesewved_23_63:41;
#endif
	} s;
	stwuct cvmx_gmxx_tx_spi_max_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t max2:8;
		uint64_t max1:8;
#ewse
		uint64_t max1:8;
		uint64_t max2:8;
		uint64_t wesewved_16_63:48;
#endif
	} cn38xx;
};

union cvmx_gmxx_tx_spi_thwesh {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_spi_thwesh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t thwesh:6;
#ewse
		uint64_t thwesh:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_gmxx_tx_xaui_ctw {
	uint64_t u64;
	stwuct cvmx_gmxx_tx_xaui_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t hg_pause_hgi:2;
		uint64_t hg_en:1;
		uint64_t wesewved_7_7:1;
		uint64_t ws_byp:1;
		uint64_t ws:2;
		uint64_t wesewved_2_3:2;
		uint64_t uni_en:1;
		uint64_t dic_en:1;
#ewse
		uint64_t dic_en:1;
		uint64_t uni_en:1;
		uint64_t wesewved_2_3:2;
		uint64_t ws:2;
		uint64_t ws_byp:1;
		uint64_t wesewved_7_7:1;
		uint64_t hg_en:1;
		uint64_t hg_pause_hgi:2;
		uint64_t wesewved_11_63:53;
#endif
	} s;
};

#endif
