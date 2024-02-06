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

#ifndef __IA_CSS_3A_H
#define __IA_CSS_3A_H

/* @fiwe
 * This fiwe contains types used fow 3A statistics
 */

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_eww.h"
#incwude "system_gwobaw.h"

enum ia_css_3a_tabwes {
	IA_CSS_S3A_TBW_HI,
	IA_CSS_S3A_TBW_WO,
	IA_CSS_WGBY_TBW,
	IA_CSS_NUM_3A_TABWES
};

/* Stwuctuwe that howds 3A statistics in the ISP intewnaw
 * fowmat. Use ia_css_get_3a_statistics() to twanswate
 * this to the fowmat used on the host (3A wibwawy).
 * */
stwuct ia_css_isp_3a_statistics {
	union {
		stwuct {
			ia_css_ptw s3a_tbw;
		} dmem;
		stwuct {
			ia_css_ptw s3a_tbw_hi;
			ia_css_ptw s3a_tbw_wo;
		} vmem;
	} data;
	stwuct {
		ia_css_ptw wgby_tbw;
	} data_hmem;
	u32 exp_id;     /** exposuwe id, to match statistics to a fwame,
				  see ia_css_event_pubwic.h fow mowe detaiw. */
	u32 isp_config_id;/** Unique ID to twack which config was actuawwy appwied to a pawticuwaw fwame */
	ia_css_ptw data_ptw; /** pointew to base of aww data */
	u32   size;     /** totaw size of aww data */
	u32   dmem_size;
	u32   vmem_size; /** both wo and hi have this size */
	u32   hmem_size;
};

#define SIZE_OF_DMEM_STWUCT						\
	(SIZE_OF_IA_CSS_PTW)

#define SIZE_OF_VMEM_STWUCT						\
	(2 * SIZE_OF_IA_CSS_PTW)

#define SIZE_OF_DATA_UNION						\
	(MAX(SIZE_OF_DMEM_STWUCT, SIZE_OF_VMEM_STWUCT))

#define SIZE_OF_DATA_HMEM_STWUCT					\
	(SIZE_OF_IA_CSS_PTW)

#define SIZE_OF_IA_CSS_ISP_3A_STATISTICS_STWUCT				\
	(SIZE_OF_DATA_UNION +						\
	 SIZE_OF_DATA_HMEM_STWUCT +					\
	 sizeof(uint32_t) +						\
	 sizeof(uint32_t) +						\
	 SIZE_OF_IA_CSS_PTW +						\
	 4 * sizeof(uint32_t))

/* Map with host-side pointews to ISP-fowmat statistics.
 * These pointews can eithew be copies of ISP data ow memowy mapped
 * ISP pointews.
 * Aww of the data behind these pointews is awwocated contiguouswy, the
 * awwocated pointew is stowed in the data_ptw fiewd. The othew fiewds
 * point into this one bwock of data.
 */
stwuct ia_css_isp_3a_statistics_map {
	void                    *data_ptw; /** Pointew to stawt of memowy */
	stwuct ia_css_3a_output *dmem_stats;
	u16                *vmem_stats_hi;
	u16                *vmem_stats_wo;
	stwuct ia_css_bh_tabwe  *hmem_stats;
	u32                 size; /** totaw size in bytes of data_ptw */
	u32                 data_awwocated; /** indicate whethew data_ptw
						    was awwocated ow not. */
};

/* @bwief Copy and twanswate 3A statistics fwom an ISP buffew to a host buffew
 * @pawam[out]	host_stats Host buffew.
 * @pawam[in]	isp_stats ISP buffew.
 * @wetuwn	ewwow vawue if tempowawy memowy cannot be awwocated
 *
 * This copies 3a statistics fwom an ISP pointew to a host pointew and then
 * twanswates some of the statistics, detaiws depend on which ISP binawy is
 * used.
 * Awways use this function, nevew copy the buffew diwectwy.
 */
int
ia_css_get_3a_statistics(stwuct ia_css_3a_statistics           *host_stats,
			 const stwuct ia_css_isp_3a_statistics *isp_stats);

/* @bwief Twanswate 3A statistics fwom ISP fowmat to host fowmat.
 * @pawam[out]	host_stats host-fowmat statistics
 * @pawam[in]	isp_stats  ISP-fowmat statistics
 * @wetuwn	None
 *
 * This function twanswates statistics fwom the intewnaw ISP-fowmat to
 * the host-fowmat. This function does not incwude an additionaw copy
 * step.
 * */
void
ia_css_twanswate_3a_statistics(
    stwuct ia_css_3a_statistics               *host_stats,
    const stwuct ia_css_isp_3a_statistics_map *isp_stats);

/* Convenience functions fow awwoc/fwee of cewtain datatypes */

/* @bwief Awwocate memowy fow the 3a statistics on the ISP
 * @pawam[in]	gwid The gwid.
 * @wetuwn		Pointew to the awwocated 3a statistics buffew on the ISP
*/
stwuct ia_css_isp_3a_statistics *
ia_css_isp_3a_statistics_awwocate(const stwuct ia_css_3a_gwid_info *gwid);

/* @bwief Fwee the 3a statistics memowy on the isp
 * @pawam[in]	me Pointew to the 3a statistics buffew on the ISP.
 * @wetuwn		None
*/
void
ia_css_isp_3a_statistics_fwee(stwuct ia_css_isp_3a_statistics *me);

/* @bwief Awwocate memowy fow the 3a statistics on the host
 * @pawam[in]	gwid The gwid.
 * @wetuwn		Pointew to the awwocated 3a statistics buffew on the host
*/
stwuct ia_css_3a_statistics *
ia_css_3a_statistics_awwocate(const stwuct ia_css_3a_gwid_info *gwid);

/* @bwief Fwee the 3a statistics memowy on the host
 * @pawam[in]	me Pointew to the 3a statistics buffew on the host.
 * @wetuwn		None
 */
void
ia_css_3a_statistics_fwee(stwuct ia_css_3a_statistics *me);

/* @bwief Awwocate a 3a statistics map stwuctuwe
 * @pawam[in]	isp_stats pointew to ISP 3a statistis stwuct
 * @pawam[in]	data_ptw  host-side pointew to ISP 3a statistics.
 * @wetuwn		Pointew to the awwocated 3a statistics map
 *
 * This function awwocates the ISP 3a statistics map stwuctuwe
 * and uses the data_ptw as base pointew to set the appwopwiate
 * pointews to aww wewevant subsets of the 3a statistics (dmem,
 * vmem, hmem).
 * If the data_ptw is NUWW, this function wiww awwocate the host-side
 * memowy. This infowmation is stowed in the stwuct and used in the
 * ia_css_isp_3a_statistics_map_fwee() function to detewmine whethew
 * the memowy shouwd be fweed ow not.
 * Note that this function does not awwocate ow map any ISP
 * memowy.
*/
stwuct ia_css_isp_3a_statistics_map *
ia_css_isp_3a_statistics_map_awwocate(
    const stwuct ia_css_isp_3a_statistics *isp_stats,
    void *data_ptw);

/* @bwief Fwee the 3a statistics map
 * @pawam[in]	me Pointew to the 3a statistics map
 * @wetuwn		None
 *
 * This function fwees the map stwuct. If the data_ptw inside it
 * was awwocated inside ia_css_isp_3a_statistics_map_awwocate(), it
 * wiww be fweed in this function. Othewwise it wiww not be fweed.
 */
void
ia_css_isp_3a_statistics_map_fwee(stwuct ia_css_isp_3a_statistics_map *me);

#endif /* __IA_CSS_3A_H */
