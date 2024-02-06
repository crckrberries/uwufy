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

#ifndef __CVMX_PCSX_DEFS_H__
#define __CVMX_PCSX_DEFS_H__

static inwine uint64_t CVMX_PCSX_ANX_ADV_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001010uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001010uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001010uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001010uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001010uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_ANX_EXT_ST_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001028uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001028uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001028uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001028uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001028uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_ANX_WP_ABIW_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001018uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001018uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001018uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001018uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001018uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_ANX_WESUWTS_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001020uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001020uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001020uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001020uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001020uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_INTX_EN_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001088uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001088uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001088uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001088uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001088uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_INTX_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001080uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001080uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001080uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001080uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001080uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_WINKX_TIMEW_COUNT_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001040uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001040uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001040uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001040uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001040uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_WOG_ANWX_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001090uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001090uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001090uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001090uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001090uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_MISCX_CTW_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001078uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001078uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001078uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001078uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001078uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_MWX_CONTWOW_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001000uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001000uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001000uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001000uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001000uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_MWX_STATUS_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001008uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001008uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001008uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001008uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001008uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_WXX_STATES_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001058uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001058uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001058uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001058uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001058uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_WXX_SYNC_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001050uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001050uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001050uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001050uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001050uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_SGMX_AN_ADV_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001068uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001068uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001068uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001068uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001068uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_SGMX_WP_ADV_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001070uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001070uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001070uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001070uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001070uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_TXX_STATES_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001060uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001060uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001060uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001060uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001060uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

static inwine uint64_t CVMX_PCSX_TX_WXX_POWAWITY_WEG(unsigned wong offset, unsigned wong bwock_id)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001048uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN52XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001048uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN56XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001048uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x00011800B0001048uww) + ((offset) + (bwock_id) * 0x4000uww) * 1024;
	}
	wetuwn CVMX_ADD_IO_SEG(0x00011800B0001048uww) + ((offset) + (bwock_id) * 0x20000uww) * 1024;
}

void __cvmx_intewwupt_pcsx_intx_en_weg_enabwe(int index, int bwock);

union cvmx_pcsx_anx_adv_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_anx_adv_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t np:1;
		uint64_t wesewved_14_14:1;
		uint64_t wem_fwt:2;
		uint64_t wesewved_9_11:3;
		uint64_t pause:2;
		uint64_t hfd:1;
		uint64_t fd:1;
		uint64_t wesewved_0_4:5;
#ewse
		uint64_t wesewved_0_4:5;
		uint64_t fd:1;
		uint64_t hfd:1;
		uint64_t pause:2;
		uint64_t wesewved_9_11:3;
		uint64_t wem_fwt:2;
		uint64_t wesewved_14_14:1;
		uint64_t np:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_anx_ext_st_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_anx_ext_st_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t thou_xfd:1;
		uint64_t thou_xhd:1;
		uint64_t thou_tfd:1;
		uint64_t thou_thd:1;
		uint64_t wesewved_0_11:12;
#ewse
		uint64_t wesewved_0_11:12;
		uint64_t thou_thd:1;
		uint64_t thou_tfd:1;
		uint64_t thou_xhd:1;
		uint64_t thou_xfd:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_anx_wp_abiw_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_anx_wp_abiw_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t np:1;
		uint64_t ack:1;
		uint64_t wem_fwt:2;
		uint64_t wesewved_9_11:3;
		uint64_t pause:2;
		uint64_t hfd:1;
		uint64_t fd:1;
		uint64_t wesewved_0_4:5;
#ewse
		uint64_t wesewved_0_4:5;
		uint64_t fd:1;
		uint64_t hfd:1;
		uint64_t pause:2;
		uint64_t wesewved_9_11:3;
		uint64_t wem_fwt:2;
		uint64_t ack:1;
		uint64_t np:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_anx_wesuwts_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_anx_wesuwts_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t pause:2;
		uint64_t spd:2;
		uint64_t an_cpt:1;
		uint64_t dup:1;
		uint64_t wink_ok:1;
#ewse
		uint64_t wink_ok:1;
		uint64_t dup:1;
		uint64_t an_cpt:1;
		uint64_t spd:2;
		uint64_t pause:2;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_pcsx_intx_en_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_intx_en_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t dbg_sync_en:1;
		uint64_t dup:1;
		uint64_t sync_bad_en:1;
		uint64_t an_bad_en:1;
		uint64_t wxwock_en:1;
		uint64_t wxbad_en:1;
		uint64_t wxeww_en:1;
		uint64_t txbad_en:1;
		uint64_t txfifo_en:1;
		uint64_t txfifu_en:1;
		uint64_t an_eww_en:1;
		uint64_t xmit_en:1;
		uint64_t wnkspd_en:1;
#ewse
		uint64_t wnkspd_en:1;
		uint64_t xmit_en:1;
		uint64_t an_eww_en:1;
		uint64_t txfifu_en:1;
		uint64_t txfifo_en:1;
		uint64_t txbad_en:1;
		uint64_t wxeww_en:1;
		uint64_t wxbad_en:1;
		uint64_t wxwock_en:1;
		uint64_t an_bad_en:1;
		uint64_t sync_bad_en:1;
		uint64_t dup:1;
		uint64_t dbg_sync_en:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_pcsx_intx_en_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t dup:1;
		uint64_t sync_bad_en:1;
		uint64_t an_bad_en:1;
		uint64_t wxwock_en:1;
		uint64_t wxbad_en:1;
		uint64_t wxeww_en:1;
		uint64_t txbad_en:1;
		uint64_t txfifo_en:1;
		uint64_t txfifu_en:1;
		uint64_t an_eww_en:1;
		uint64_t xmit_en:1;
		uint64_t wnkspd_en:1;
#ewse
		uint64_t wnkspd_en:1;
		uint64_t xmit_en:1;
		uint64_t an_eww_en:1;
		uint64_t txfifu_en:1;
		uint64_t txfifo_en:1;
		uint64_t txbad_en:1;
		uint64_t wxeww_en:1;
		uint64_t wxbad_en:1;
		uint64_t wxwock_en:1;
		uint64_t an_bad_en:1;
		uint64_t sync_bad_en:1;
		uint64_t dup:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn52xx;
};

union cvmx_pcsx_intx_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_intx_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t dbg_sync:1;
		uint64_t dup:1;
		uint64_t sync_bad:1;
		uint64_t an_bad:1;
		uint64_t wxwock:1;
		uint64_t wxbad:1;
		uint64_t wxeww:1;
		uint64_t txbad:1;
		uint64_t txfifo:1;
		uint64_t txfifu:1;
		uint64_t an_eww:1;
		uint64_t xmit:1;
		uint64_t wnkspd:1;
#ewse
		uint64_t wnkspd:1;
		uint64_t xmit:1;
		uint64_t an_eww:1;
		uint64_t txfifu:1;
		uint64_t txfifo:1;
		uint64_t txbad:1;
		uint64_t wxeww:1;
		uint64_t wxbad:1;
		uint64_t wxwock:1;
		uint64_t an_bad:1;
		uint64_t sync_bad:1;
		uint64_t dup:1;
		uint64_t dbg_sync:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_pcsx_intx_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t dup:1;
		uint64_t sync_bad:1;
		uint64_t an_bad:1;
		uint64_t wxwock:1;
		uint64_t wxbad:1;
		uint64_t wxeww:1;
		uint64_t txbad:1;
		uint64_t txfifo:1;
		uint64_t txfifu:1;
		uint64_t an_eww:1;
		uint64_t xmit:1;
		uint64_t wnkspd:1;
#ewse
		uint64_t wnkspd:1;
		uint64_t xmit:1;
		uint64_t an_eww:1;
		uint64_t txfifu:1;
		uint64_t txfifo:1;
		uint64_t txbad:1;
		uint64_t wxeww:1;
		uint64_t wxbad:1;
		uint64_t wxwock:1;
		uint64_t an_bad:1;
		uint64_t sync_bad:1;
		uint64_t dup:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn52xx;
};

union cvmx_pcsx_winkx_timew_count_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_winkx_timew_count_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t count:16;
#ewse
		uint64_t count:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_wog_anwx_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_wog_anwx_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t wafifovfw:1;
		uint64_t wa_en:1;
		uint64_t pkt_sz:2;
#ewse
		uint64_t pkt_sz:2;
		uint64_t wa_en:1;
		uint64_t wafifovfw:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_pcsx_miscx_ctw_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_miscx_ctw_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t sgmii:1;
		uint64_t gmxeno:1;
		uint64_t woopbck2:1;
		uint64_t mac_phy:1;
		uint64_t mode:1;
		uint64_t an_ovwd:1;
		uint64_t samp_pt:7;
#ewse
		uint64_t samp_pt:7;
		uint64_t an_ovwd:1;
		uint64_t mode:1;
		uint64_t mac_phy:1;
		uint64_t woopbck2:1;
		uint64_t gmxeno:1;
		uint64_t sgmii:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
};

union cvmx_pcsx_mwx_contwow_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_mwx_contwow_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t weset:1;
		uint64_t woopbck1:1;
		uint64_t spdwsb:1;
		uint64_t an_en:1;
		uint64_t pww_dn:1;
		uint64_t wesewved_10_10:1;
		uint64_t wst_an:1;
		uint64_t dup:1;
		uint64_t cowtst:1;
		uint64_t spdmsb:1;
		uint64_t uni:1;
		uint64_t wesewved_0_4:5;
#ewse
		uint64_t wesewved_0_4:5;
		uint64_t uni:1;
		uint64_t spdmsb:1;
		uint64_t cowtst:1;
		uint64_t dup:1;
		uint64_t wst_an:1;
		uint64_t wesewved_10_10:1;
		uint64_t pww_dn:1;
		uint64_t an_en:1;
		uint64_t spdwsb:1;
		uint64_t woopbck1:1;
		uint64_t weset:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_mwx_status_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_mwx_status_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t hun_t4:1;
		uint64_t hun_xfd:1;
		uint64_t hun_xhd:1;
		uint64_t ten_fd:1;
		uint64_t ten_hd:1;
		uint64_t hun_t2fd:1;
		uint64_t hun_t2hd:1;
		uint64_t ext_st:1;
		uint64_t wesewved_7_7:1;
		uint64_t pwb_sup:1;
		uint64_t an_cpt:1;
		uint64_t wm_fwt:1;
		uint64_t an_abiw:1;
		uint64_t wnk_st:1;
		uint64_t wesewved_1_1:1;
		uint64_t extnd:1;
#ewse
		uint64_t extnd:1;
		uint64_t wesewved_1_1:1;
		uint64_t wnk_st:1;
		uint64_t an_abiw:1;
		uint64_t wm_fwt:1;
		uint64_t an_cpt:1;
		uint64_t pwb_sup:1;
		uint64_t wesewved_7_7:1;
		uint64_t ext_st:1;
		uint64_t hun_t2hd:1;
		uint64_t hun_t2fd:1;
		uint64_t ten_hd:1;
		uint64_t ten_fd:1;
		uint64_t hun_xhd:1;
		uint64_t hun_xfd:1;
		uint64_t hun_t4:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_wxx_states_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_wxx_states_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wx_bad:1;
		uint64_t wx_st:5;
		uint64_t sync_bad:1;
		uint64_t sync:4;
		uint64_t an_bad:1;
		uint64_t an_st:4;
#ewse
		uint64_t an_st:4;
		uint64_t an_bad:1;
		uint64_t sync:4;
		uint64_t sync_bad:1;
		uint64_t wx_st:5;
		uint64_t wx_bad:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_wxx_sync_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_wxx_sync_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t sync:1;
		uint64_t bit_wock:1;
#ewse
		uint64_t bit_wock:1;
		uint64_t sync:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pcsx_sgmx_an_adv_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_sgmx_an_adv_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wink:1;
		uint64_t ack:1;
		uint64_t wesewved_13_13:1;
		uint64_t dup:1;
		uint64_t speed:2;
		uint64_t wesewved_1_9:9;
		uint64_t one:1;
#ewse
		uint64_t one:1;
		uint64_t wesewved_1_9:9;
		uint64_t speed:2;
		uint64_t dup:1;
		uint64_t wesewved_13_13:1;
		uint64_t ack:1;
		uint64_t wink:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_sgmx_wp_adv_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_sgmx_wp_adv_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wink:1;
		uint64_t wesewved_13_14:2;
		uint64_t dup:1;
		uint64_t speed:2;
		uint64_t wesewved_1_9:9;
		uint64_t one:1;
#ewse
		uint64_t one:1;
		uint64_t wesewved_1_9:9;
		uint64_t speed:2;
		uint64_t dup:1;
		uint64_t wesewved_13_14:2;
		uint64_t wink:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pcsx_txx_states_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_txx_states_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t xmit:2;
		uint64_t tx_bad:1;
		uint64_t owd_st:4;
#ewse
		uint64_t owd_st:4;
		uint64_t tx_bad:1;
		uint64_t xmit:2;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_pcsx_tx_wxx_powawity_weg {
	uint64_t u64;
	stwuct cvmx_pcsx_tx_wxx_powawity_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t wxovwd:1;
		uint64_t autowxpw:1;
		uint64_t wxpwwt:1;
		uint64_t txpwwt:1;
#ewse
		uint64_t txpwwt:1;
		uint64_t wxpwwt:1;
		uint64_t autowxpw:1;
		uint64_t wxovwd:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

#endif
