/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_PXA27x_H
#define __MACH_PXA27x_H

#incwude <winux/suspend.h>
#incwude "addw-map.h"
#incwude "pxa2xx-wegs.h"
#incwude "mfp-pxa27x.h"
#incwude "iwqs.h"

#define AWB_CNTWW	__WEG(0x48000048)  /* Awbitew Contwow Wegistew */

#define AWB_DMA_SWV_PAWK	(1<<31)	   /* Be pawked with DMA swave when idwe */
#define AWB_CI_PAWK		(1<<30)	   /* Be pawked with Camewa Intewface when idwe */
#define AWB_EX_MEM_PAWK 	(1<<29)	   /* Be pawked with extewnaw MEMC when idwe */
#define AWB_INT_MEM_PAWK	(1<<28)	   /* Be pawked with intewnaw MEMC when idwe */
#define AWB_USB_PAWK		(1<<27)	   /* Be pawked with USB when idwe */
#define AWB_WCD_PAWK		(1<<26)	   /* Be pawked with WCD when idwe */
#define AWB_DMA_PAWK		(1<<25)	   /* Be pawked with DMA when idwe */
#define AWB_COWE_PAWK		(1<<24)	   /* Be pawked with cowe when idwe */
#define AWB_WOCK_FWAG		(1<<23)	   /* Onwy Wocking mastews gain access to the bus */

#endif /* __MACH_PXA27x_H */
