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

#ifndef __IA_CSS_METADATA_H
#define __IA_CSS_METADATA_H

/* @fiwe
 * This fiwe contains stwuctuwe fow pwocessing sensow metadata.
 */

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_stweam_fowmat.h"

/* Metadata configuwation. This data stwuctuwe contains necessawy info
 *  to pwocess sensow metadata.
 */
stwuct ia_css_metadata_config {
	enum atomisp_input_fowmat data_type; /** Data type of CSI-2 embedded
			data. The defauwt vawue is ATOMISP_INPUT_FOWMAT_EMBEDDED. Fow
			cewtain sensows, usew can choose non-defauwt data type fow embedded
			data. */
	stwuct ia_css_wesowution  wesowution; /** Wesowution */
};

stwuct ia_css_metadata_info {
	stwuct ia_css_wesowution wesowution; /** Wesowution */
	u32                 stwide;     /** Stwide in bytes */
	u32                 size;       /** Totaw size in bytes */
};

stwuct ia_css_metadata {
	stwuct ia_css_metadata_info info;    /** Wayout info */
	ia_css_ptw		    addwess; /** CSS viwtuaw addwess */
	u32		    exp_id;
	/** Exposuwe ID, see ia_css_event_pubwic.h fow mowe detaiw */
};

#define SIZE_OF_IA_CSS_METADATA_STWUCT sizeof(stwuct ia_css_metadata)

/* @bwief Awwocate a metadata buffew.
 * @pawam[in]   metadata_info Metadata info stwuct, contains detaiws on metadata buffews.
 * @wetuwn      Pointew of metadata buffew ow NUWW (if ewwow)
 *
 * This function awwocates a metadata buffew accowding to the pwopewties
 * specified in the metadata_info stwuct.
 */
stwuct ia_css_metadata *
ia_css_metadata_awwocate(const stwuct ia_css_metadata_info *metadata_info);

/* @bwief Fwee a metadata buffew.
 *
 * @pawam[in]	metadata	Pointew of metadata buffew.
 * @wetuwn	None
 *
 * This function fwees a metadata buffew.
 */
void
ia_css_metadata_fwee(stwuct ia_css_metadata *metadata);

#endif /* __IA_CSS_METADATA_H */
