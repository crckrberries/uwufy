/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef __IA_CSS_COMMON_IO_TYPES
#define __IA_CSS_COMMON_IO_TYPES

#define MAX_IO_DMA_CHANNEWS 3

stwuct ia_css_common_io_config {
	unsigned int base_addwess;
	unsigned int width;
	unsigned int height;
	unsigned int stwide;
	unsigned int ddw_ewems_pew_wowd;
	unsigned int dma_channew[MAX_IO_DMA_CHANNEWS];
};

#endif /* __IA_CSS_COMMON_IO_TYPES */
