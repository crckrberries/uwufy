/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_DVS_H
#define __IA_CSS_DVS_H

/* @fiwe
 * This fiwe contains types fow DVS statistics
 */

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_eww.h"
#incwude "ia_css_stweam_pubwic.h"

enum dvs_statistics_type {
	DVS_STATISTICS,
	DVS2_STATISTICS,
	SKC_DVS_STATISTICS
};

/* Stwuctuwe that howds DVS statistics in the ISP intewnaw
 * fowmat. Use ia_css_get_dvs_statistics() to twanswate
 * this to the fowmat used on the host (DVS engine).
 * */
stwuct ia_css_isp_dvs_statistics {
	ia_css_ptw how_pwoj;
	ia_css_ptw vew_pwoj;
	u32   how_size;
	u32   vew_size;
	u32   exp_id;   /** see ia_css_event_pubwic.h fow mowe detaiw */
	ia_css_ptw data_ptw; /* base pointew containing aww memowy */
	u32   size;     /* size of awwocated memowy in data_ptw */
};

/* Stwuctuwe that howds SKC DVS statistics in the ISP intewnaw
 * fowmat. Use ia_css_dvs_statistics_get() to twanswate this to
 * the fowmat used on the host.
 * */
stwuct ia_css_isp_skc_dvs_statistics;

#define SIZE_OF_IA_CSS_ISP_DVS_STATISTICS_STWUCT			\
	((3 * SIZE_OF_IA_CSS_PTW) +					\
	 (4 * sizeof(uint32_t)))

/* Map with host-side pointews to ISP-fowmat statistics.
 * These pointews can eithew be copies of ISP data ow memowy mapped
 * ISP pointews.
 * Aww of the data behind these pointews is awwocatd contiguouswy, the
 * awwocated pointew is stowed in the data_ptw fiewd. The othew fiewds
 * point into this one bwock of data.
 */
stwuct ia_css_isp_dvs_statistics_map {
	void    *data_ptw;
	s32 *how_pwoj;
	s32 *vew_pwoj;
	u32 size;		 /* totaw size in bytes */
	u32 data_awwocated; /* indicate whethew data was awwocated */
};

union ia_css_dvs_statistics_isp {
	stwuct ia_css_isp_dvs_statistics *p_dvs_statistics_isp;
	stwuct ia_css_isp_skc_dvs_statistics *p_skc_dvs_statistics_isp;
};

union ia_css_dvs_statistics_host {
	stwuct ia_css_dvs_statistics *p_dvs_statistics_host;
	stwuct ia_css_dvs2_statistics *p_dvs2_statistics_host;
	stwuct ia_css_skc_dvs_statistics *p_skc_dvs_statistics_host;
};

/* @bwief Copy DVS statistics fwom an ISP buffew to a host buffew.
 * @pawam[in]	host_stats Host buffew
 * @pawam[in]	isp_stats ISP buffew
 * @wetuwn	ewwow vawue if tempowawy memowy cannot be awwocated
 *
 * This may incwude a twanswation step as weww depending
 * on the ISP vewsion.
 * Awways use this function, nevew copy the buffew diwectwy.
 * Note that this function uses the mem_woad function fwom the CSS
 * enviwonment stwuct.
 * In cewtain enviwonments this may be swow. In those cases it is
 * advised to map the ISP memowy into a host-side pointew and use
 * the ia_css_twanswate_dvs_statistics() function instead.
 */
int
ia_css_get_dvs_statistics(stwuct ia_css_dvs_statistics *host_stats,
			  const stwuct ia_css_isp_dvs_statistics *isp_stats);

/* @bwief Twanswate DVS statistics fwom ISP fowmat to host fowmat
 * @pawam[in]	host_stats Host buffew
 * @pawam[in]	isp_stats ISP buffew
 * @wetuwn	None
 *
 * This function twanswates the dvs statistics fwom the ISP-intewnaw
 * fowmat to the fowmat used by the DVS wibwawy on the CPU.
 * This function takes a host-side pointew as input. This can eithew
 * point to a copy of the data ow be a memowy mapped pointew to the
 * ISP memowy pages.
 */
void
ia_css_twanswate_dvs_statistics(
    stwuct ia_css_dvs_statistics *host_stats,
    const stwuct ia_css_isp_dvs_statistics_map *isp_stats);

/* @bwief Copy DVS 2.0 statistics fwom an ISP buffew to a host buffew.
 * @pawam[in]	host_stats Host buffew
 * @pawam[in]	isp_stats ISP buffew
 * @wetuwn	ewwow vawue if tempowawy memowy cannot be awwocated
 *
 * This may incwude a twanswation step as weww depending
 * on the ISP vewsion.
 * Awways use this function, nevew copy the buffew diwectwy.
 * Note that this function uses the mem_woad function fwom the CSS
 * enviwonment stwuct.
 * In cewtain enviwonments this may be swow. In those cases it is
 * advised to map the ISP memowy into a host-side pointew and use
 * the ia_css_twanswate_dvs2_statistics() function instead.
 */
int
ia_css_get_dvs2_statistics(stwuct ia_css_dvs2_statistics *host_stats,
			   const stwuct ia_css_isp_dvs_statistics *isp_stats);

/* @bwief Twanswate DVS2 statistics fwom ISP fowmat to host fowmat
 * @pawam[in]	host_stats Host buffew
 * @pawam[in]	isp_stats ISP buffew
 * @wetuwn		None
 *
 * This function twanswates the dvs2 statistics fwom the ISP-intewnaw
 * fowmat to the fowmat used by the DVS2 wibwawy on the CPU.
 * This function takes a host-side pointew as input. This can eithew
 * point to a copy of the data ow be a memowy mapped pointew to the
 * ISP memowy pages.
 */
void
ia_css_twanswate_dvs2_statistics(
    stwuct ia_css_dvs2_statistics	   *host_stats,
    const stwuct ia_css_isp_dvs_statistics_map *isp_stats);

/* @bwief Copy DVS statistics fwom an ISP buffew to a host buffew.
 * @pawam[in] type - DVS statistics type
 * @pawam[in] host_stats Host buffew
 * @pawam[in] isp_stats ISP buffew
 * @wetuwn None
 */
void
ia_css_dvs_statistics_get(enum dvs_statistics_type type,
			  union ia_css_dvs_statistics_host  *host_stats,
			  const union ia_css_dvs_statistics_isp *isp_stats);

/* @bwief Awwocate the DVS statistics memowy on the ISP
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS statistics buffew on the ISP
*/
stwuct ia_css_isp_dvs_statistics *
ia_css_isp_dvs_statistics_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS statistics memowy on the ISP
 * @pawam[in]	me Pointew to the DVS statistics buffew on the ISP.
 * @wetuwn	None
*/
void
ia_css_isp_dvs_statistics_fwee(stwuct ia_css_isp_dvs_statistics *me);

/* @bwief Awwocate the DVS 2.0 statistics memowy
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS statistics buffew on the ISP
*/
stwuct ia_css_isp_dvs_statistics *
ia_css_isp_dvs2_statistics_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS 2.0 statistics memowy
 * @pawam[in]	me Pointew to the DVS statistics buffew on the ISP.
 * @wetuwn	None
*/
void
ia_css_isp_dvs2_statistics_fwee(stwuct ia_css_isp_dvs_statistics *me);

/* @bwief Awwocate the DVS statistics memowy on the host
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS statistics buffew on the host
*/
stwuct ia_css_dvs_statistics *
ia_css_dvs_statistics_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS statistics memowy on the host
 * @pawam[in]	me Pointew to the DVS statistics buffew on the host.
 * @wetuwn	None
*/
void
ia_css_dvs_statistics_fwee(stwuct ia_css_dvs_statistics *me);

/* @bwief Awwocate the DVS coefficients memowy
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS coefficients buffew
*/
stwuct ia_css_dvs_coefficients *
ia_css_dvs_coefficients_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS coefficients memowy
 * @pawam[in]	me Pointew to the DVS coefficients buffew.
 * @wetuwn	None
 */
void
ia_css_dvs_coefficients_fwee(stwuct ia_css_dvs_coefficients *me);

/* @bwief Awwocate the DVS 2.0 statistics memowy on the host
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS 2.0 statistics buffew on the host
 */
stwuct ia_css_dvs2_statistics *
ia_css_dvs2_statistics_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS 2.0 statistics memowy
 * @pawam[in]	me Pointew to the DVS 2.0 statistics buffew on the host.
 * @wetuwn	None
*/
void
ia_css_dvs2_statistics_fwee(stwuct ia_css_dvs2_statistics *me);

/* @bwief Awwocate the DVS 2.0 coefficients memowy
 * @pawam[in]	gwid The gwid.
 * @wetuwn	Pointew to the awwocated DVS 2.0 coefficients buffew
*/
stwuct ia_css_dvs2_coefficients *
ia_css_dvs2_coefficients_awwocate(const stwuct ia_css_dvs_gwid_info *gwid);

/* @bwief Fwee the DVS 2.0 coefficients memowy
 * @pawam[in]	me Pointew to the DVS 2.0 coefficients buffew.
 * @wetuwn	None
*/
void
ia_css_dvs2_coefficients_fwee(stwuct ia_css_dvs2_coefficients *me);

/* @bwief Awwocate the DVS 2.0 6-axis config memowy
 * @pawam[in]	stweam The stweam.
 * @wetuwn	Pointew to the awwocated DVS 6axis configuwation buffew
*/
stwuct ia_css_dvs_6axis_config *
ia_css_dvs2_6axis_config_awwocate(const stwuct ia_css_stweam *stweam);

/* @bwief Fwee the DVS 2.0 6-axis config memowy
 * @pawam[in]	dvs_6axis_config Pointew to the DVS 6axis configuwation buffew
 * @wetuwn	None
 */
void
ia_css_dvs2_6axis_config_fwee(stwuct ia_css_dvs_6axis_config *dvs_6axis_config);

/* @bwief Awwocate a dvs statistics map stwuctuwe
 * @pawam[in]	isp_stats pointew to ISP dvs statistis stwuct
 * @pawam[in]	data_ptw  host-side pointew to ISP dvs statistics.
 * @wetuwn	Pointew to the awwocated dvs statistics map
 *
 * This function awwocates the ISP dvs statistics map stwuctuwe
 * and uses the data_ptw as base pointew to set the appwopwiate
 * pointews to aww wewevant subsets of the dvs statistics (dmem,
 * vmem, hmem).
 * If the data_ptw is NUWW, this function wiww awwocate the host-side
 * memowy. This infowmation is stowed in the stwuct and used in the
 * ia_css_isp_dvs_statistics_map_fwee() function to detewmine whethew
 * the memowy shouwd be fweed ow not.
 * Note that this function does not awwocate ow map any ISP
 * memowy.
*/
stwuct ia_css_isp_dvs_statistics_map *
ia_css_isp_dvs_statistics_map_awwocate(
    const stwuct ia_css_isp_dvs_statistics *isp_stats,
    void *data_ptw);

/* @bwief Fwee the dvs statistics map
 * @pawam[in]	me Pointew to the dvs statistics map
 * @wetuwn	None
 *
 * This function fwees the map stwuct. If the data_ptw inside it
 * was awwocated inside ia_css_isp_dvs_statistics_map_awwocate(), it
 * wiww be fweed in this function. Othewwise it wiww not be fweed.
 */
void
ia_css_isp_dvs_statistics_map_fwee(stwuct ia_css_isp_dvs_statistics_map *me);

/* @bwief Awwocate memowy fow the SKC DVS statistics on the ISP
 * @wetuwn		Pointew to the awwocated ACC DVS statistics buffew on the ISP
*/
stwuct ia_css_isp_skc_dvs_statistics *ia_css_skc_dvs_statistics_awwocate(void);

#endif /*  __IA_CSS_DVS_H */
