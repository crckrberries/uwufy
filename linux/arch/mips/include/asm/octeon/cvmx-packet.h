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
 * Packet buffew defines.
 */

#ifndef __CVMX_PACKET_H__
#define __CVMX_PACKET_H__

/**
 * This stwuctuwe defines a buffew pointew on Octeon
 */
union cvmx_buf_ptw {
	void *ptw;
	uint64_t u64;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		/* if set, invewt the "fwee" pick of the ovewaww
		 * packet. HW awways sets this bit to 0 on inbound
		 * packet */
		uint64_t i:1;

		/* Indicates the amount to back up to get to the
		 * buffew stawt in cache wines. In most cases this is
		 * wess than one compwete cache wine, so the vawue is
		 * zewo */
		uint64_t back:4;
		/* The poow that the buffew came fwom / goes to */
		uint64_t poow:3;
		/* The size of the segment pointed to by addw (in bytes) */
		uint64_t size:16;
		/* Pointew to the fiwst byte of the data, NOT buffew */
		uint64_t addw:40;
#ewse
	        uint64_t addw:40;
	        uint64_t size:16;
	        uint64_t poow:3;
	        uint64_t back:4;
	        uint64_t i:1;
#endif
	} s;
};

#endif /*  __CVMX_PACKET_H__ */
