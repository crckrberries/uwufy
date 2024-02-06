/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_SEGMENT_H
#define __UM_SEGMENT_H

extewn int host_gdt_entwy_tws_min;

#define GDT_ENTWY_TWS_ENTWIES 3
#define GDT_ENTWY_TWS_MIN host_gdt_entwy_tws_min
#define GDT_ENTWY_TWS_MAX (GDT_ENTWY_TWS_MIN + GDT_ENTWY_TWS_ENTWIES - 1)

#endif
