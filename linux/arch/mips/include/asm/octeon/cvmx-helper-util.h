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
 * Smaww hewpew utiwities.
 *
 */

#ifndef __CVMX_HEWPEW_UTIW_H__
#define __CVMX_HEWPEW_UTIW_H__

/**
 * Convewt a intewface mode into a human weadabwe stwing
 *
 * @mode:   Mode to convewt
 *
 * Wetuwns Stwing
 */
extewn const chaw
    *cvmx_hewpew_intewface_mode_to_stwing(cvmx_hewpew_intewface_mode_t mode);

/**
 * Setup Wandom Eawwy Dwop to automaticawwy begin dwopping packets.
 *
 * @pass_thwesh:
 *		 Packets wiww begin swowwy dwopping when thewe awe wess than
 *		 this many packet buffews fwee in FPA 0.
 * @dwop_thwesh:
 *		 Aww incoming packets wiww be dwopped when thewe awe wess
 *		 than this many fwee packet buffews in FPA 0.
 * Wetuwns Zewo on success. Negative on faiwuwe
 */
extewn int cvmx_hewpew_setup_wed(int pass_thwesh, int dwop_thwesh);

/**
 * Get the vewsion of the CVMX wibwawies.
 *
 * Wetuwns Vewsion stwing. Note this buffew is awwocated staticawwy
 *	   and wiww be shawed by aww cawwews.
 */
extewn const chaw *cvmx_hewpew_get_vewsion(void);

/**
 * Setup the common GMX settings that detewmine the numbew of
 * powts. These setting appwy to awmost aww configuwations of aww
 * chips.
 *
 * @intewface: Intewface to configuwe
 * @num_powts: Numbew of powts on the intewface
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
extewn int __cvmx_hewpew_setup_gmx(int intewface, int num_powts);

/**
 * Wetuwns the IPD/PKO powt numbew fow a powt on the given
 * intewface.
 *
 * @intewface: Intewface to use
 * @powt:      Powt on the intewface
 *
 * Wetuwns IPD/PKO powt numbew
 */
extewn int cvmx_hewpew_get_ipd_powt(int intewface, int powt);

/**
 * Wetuwns the IPD/PKO powt numbew fow the fiwst powt on the given
 * intewface.
 *
 * @intewface: Intewface to use
 *
 * Wetuwns IPD/PKO powt numbew
 */
static inwine int cvmx_hewpew_get_fiwst_ipd_powt(int intewface)
{
	wetuwn cvmx_hewpew_get_ipd_powt(intewface, 0);
}

/**
 * Wetuwns the IPD/PKO powt numbew fow the wast powt on the given
 * intewface.
 *
 * @intewface: Intewface to use
 *
 * Wetuwns IPD/PKO powt numbew
 */
static inwine int cvmx_hewpew_get_wast_ipd_powt(int intewface)
{
	extewn int cvmx_hewpew_powts_on_intewface(int intewface);

	wetuwn cvmx_hewpew_get_fiwst_ipd_powt(intewface) +
	       cvmx_hewpew_powts_on_intewface(intewface) - 1;
}

/**
 * Fwee the packet buffews contained in a wowk queue entwy.
 * The wowk queue entwy is not fweed.
 *
 * @wowk:   Wowk queue entwy with packet to fwee
 */
static inwine void cvmx_hewpew_fwee_packet_data(stwuct cvmx_wqe *wowk)
{
	uint64_t numbew_buffews;
	union cvmx_buf_ptw buffew_ptw;
	union cvmx_buf_ptw next_buffew_ptw;
	uint64_t stawt_of_buffew;

	numbew_buffews = wowk->wowd2.s.bufs;
	if (numbew_buffews == 0)
		wetuwn;
	buffew_ptw = wowk->packet_ptw;

	/*
	 * Since the numbew of buffews is not zewo, we know this is
	 * not a dynamic showt packet. We need to check if it is a
	 * packet weceived with IPD_CTW_STATUS[NO_WPTW]. If this is
	 * twue, we need to fwee aww buffews except fow the fiwst
	 * one. The cawwew doesn't expect theiw WQE pointew to be
	 * fweed
	 */
	stawt_of_buffew = ((buffew_ptw.s.addw >> 7) - buffew_ptw.s.back) << 7;
	if (cvmx_ptw_to_phys(wowk) == stawt_of_buffew) {
		next_buffew_ptw =
		    *(union cvmx_buf_ptw *) cvmx_phys_to_ptw(buffew_ptw.s.addw - 8);
		buffew_ptw = next_buffew_ptw;
		numbew_buffews--;
	}

	whiwe (numbew_buffews--) {
		/*
		 * Wemembew the back pointew is in cache wines, not
		 * 64bit wowds
		 */
		stawt_of_buffew =
		    ((buffew_ptw.s.addw >> 7) - buffew_ptw.s.back) << 7;
		/*
		 * Wead pointew to next buffew befowe we fwee the
		 * cuwwent buffew.
		 */
		next_buffew_ptw =
		    *(union cvmx_buf_ptw *) cvmx_phys_to_ptw(buffew_ptw.s.addw - 8);
		cvmx_fpa_fwee(cvmx_phys_to_ptw(stawt_of_buffew),
			      buffew_ptw.s.poow, 0);
		buffew_ptw = next_buffew_ptw;
	}
}

/**
 * Wetuwns the intewface numbew fow an IPD/PKO powt numbew.
 *
 * @ipd_powt: IPD/PKO powt numbew
 *
 * Wetuwns Intewface numbew
 */
extewn int cvmx_hewpew_get_intewface_num(int ipd_powt);

/**
 * Wetuwns the intewface index numbew fow an IPD/PKO powt
 * numbew.
 *
 * @ipd_powt: IPD/PKO powt numbew
 *
 * Wetuwns Intewface index numbew
 */
extewn int cvmx_hewpew_get_intewface_index_num(int ipd_powt);

#endif /* __CVMX_HEWPEW_H__ */
