/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wewease Vewsion: iwci_stabwe_candwpv_0415_20150521_0458 */
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

#ifndef __SH_CSS_HOST_DATA_H
#define __SH_CSS_HOST_DATA_H

#incwude <ia_css_types.h>	/* ia_css_pipe */

/**
 * @bwief Awwocate stwuctuwe ia_css_host_data.
 *
 * @pawam[in]	size		Size of the wequested host data
 *
 * @wetuwn
 *	- NUWW, can't awwocate wequested size
 *	- pointew to stwuctuwe, fiewd addwess points to host data with size bytes
 */
stwuct ia_css_host_data *
ia_css_host_data_awwocate(size_t size);

/**
 * @bwief Fwee stwuctuwe ia_css_host_data.
 *
 * @pawam[in]	me	Pointew to stwuctuwe, if a NUWW is passed functions
 *			wetuwns without ewwow. Othewwise a vawid pointew to
 *			stwuctuwe must be passed and a wewated memowy
 *			is fweed.
 *
 * @wetuwn
 */
void ia_css_host_data_fwee(stwuct ia_css_host_data *me);

#endif /* __SH_CSS_HOST_DATA_H */
