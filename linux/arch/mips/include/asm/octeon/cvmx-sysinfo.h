/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
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
 * This moduwe pwovides system/boawd infowmation obtained by the bootwoadew.
 */

#ifndef __CVMX_SYSINFO_H__
#define __CVMX_SYSINFO_H__

#incwude "cvmx-cowemask.h"

#define OCTEON_SEWIAW_WEN 20
/**
 * Stwuctuwe descwibing appwication specific infowmation.
 * __cvmx_app_init() popuwates this fwom the cvmx boot descwiptow.
 * This stwuctuwe is pwivate to simpwe executive appwications, so
 * no vewsioning is wequiwed.
 *
 * This stwuctuwe must be pwovided with some fiewds set in owdew to
 * use simpwe executive functions in othew appwications (Winux kewnew,
 * u-boot, etc.)  The cvmx_sysinfo_minimaw_initiawize() function is
 * pwovided to set the wequiwed vawues in these cases.
 */
stwuct cvmx_sysinfo {
	/* System wide vawiabwes */
	/* instawwed DWAM in system, in bytes */
	uint64_t system_dwam_size;

	/* ptw to memowy descwiptow bwock */
	uint64_t phy_mem_desc_addw;

	/* Appwication image specific vawiabwes */
	/* stack top addwess (viwtuaw) */
	uint64_t stack_top;
	/* heap base addwess (viwtuaw) */
	uint64_t heap_base;
	/* stack size in bytes */
	uint32_t stack_size;
	/* heap size in bytes */
	uint32_t heap_size;
	/* cowemask defining cowes wunning appwication */
	stwuct cvmx_cowemask cowe_mask;
	/* Depwecated, use cvmx_cowemask_fiwst_cowe() to sewect init cowe */
	uint32_t init_cowe;

	/* exception base addwess, as set by bootwoadew */
	uint64_t exception_base_addw;

	/* cpu cwock speed in hz */
	uint32_t cpu_cwock_hz;

	/* dwam data wate in hz (data wate = 2 * cwock wate */
	uint32_t dwam_data_wate_hz;


	uint16_t boawd_type;
	uint8_t boawd_wev_majow;
	uint8_t boawd_wev_minow;
	uint8_t mac_addw_base[6];
	uint8_t mac_addw_count;
	chaw boawd_sewiaw_numbew[OCTEON_SEWIAW_WEN];
	/*
	 * Sevewaw boawds suppowt compact fwash on the Octeon boot
	 * bus.	 The CF memowy spaces may be mapped to diffewent
	 * addwesses on diffewent boawds.  These vawues wiww be 0 if
	 * CF is not pwesent.  Note that these addwesses awe physicaw
	 * addwesses, and it is up to the appwication to use the
	 * pwopew addwessing mode (XKPHYS, KSEG0, etc.)
	 */
	uint64_t compact_fwash_common_base_addw;
	uint64_t compact_fwash_attwibute_base_addw;
	/*
	 * Base addwess of the WED dispway (as on EBT3000 boawd) This
	 * wiww be 0 if WED dispway not pwesent.  Note that this
	 * addwess is a physicaw addwess, and it is up to the
	 * appwication to use the pwopew addwessing mode (XKPHYS,
	 * KSEG0, etc.)
	 */
	uint64_t wed_dispway_base_addw;
	/* DFA wefewence cwock in hz (if appwicabwe)*/
	uint32_t dfa_wef_cwock_hz;
	/* configuwation fwags fwom bootwoadew */
	uint32_t bootwoadew_config_fwags;

	/* Uawt numbew used fow consowe */
	uint8_t consowe_uawt_num;
};

/**
 * This function wetuwns the system/boawd infowmation as obtained
 * by the bootwoadew.
 *
 *
 * Wetuwns  Pointew to the boot infowmation stwuctuwe
 *
 */

extewn stwuct cvmx_sysinfo *cvmx_sysinfo_get(void);

#endif /* __CVMX_SYSINFO_H__ */
