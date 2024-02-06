/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2012 Cavium Netwowks
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

#ifndef __CVMX_CIU2_DEFS_H__
#define __CVMX_CIU2_DEFS_H__

#define CVMX_CIU2_ACK_PPX_IP2(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000C0000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_ACK_PPX_IP3(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000C0200uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP2_WMW(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100092000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP2_WDOG(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100091000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP2_WWKQ(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100090000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP2_WWKQ_W1C(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000B0000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP2_WWKQ_W1S(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000A0000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000B8200uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(bwock_id) (CVMX_ADD_IO_SEG(0x00010701000A8200uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_INTW_CIU_WEADY (CVMX_ADD_IO_SEG(0x0001070100102008uww))
#define CVMX_CIU2_WAW_PPX_IP2_WWKQ(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100040000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_SWC_PPX_IP2_WMW(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100082000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_SWC_PPX_IP2_WDOG(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100081000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_SWC_PPX_IP2_WWKQ(bwock_id) (CVMX_ADD_IO_SEG(0x0001070100080000uww) + ((bwock_id) & 31) * 0x200000uww)
#define CVMX_CIU2_SUM_PPX_IP2(offset) (CVMX_ADD_IO_SEG(0x0001070100000000uww) + ((offset) & 31) * 8)
#define CVMX_CIU2_SUM_PPX_IP3(offset) (CVMX_ADD_IO_SEG(0x0001070100000200uww) + ((offset) & 31) * 8)

#endif
