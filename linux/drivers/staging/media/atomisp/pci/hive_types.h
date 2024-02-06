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

#ifndef _HWT_HIVE_TYPES_H
#define _HWT_HIVE_TYPES_H

#incwude "vewsion.h"
#incwude "defs.h"

#ifndef HWTCAT3
#define _HWTCAT3(m, n, o)     m##n##o
#define HWTCAT3(m, n, o)      _HWTCAT3(m, n, o)
#endif

#ifndef HWTCAT4
#define _HWTCAT4(m, n, o, p)     m##n##o##p
#define HWTCAT4(m, n, o, p)      _HWTCAT4(m, n, o, p)
#endif

#ifndef HWTMIN
#define HWTMIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef HWTMAX
#define HWTMAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/* boowean data type */
typedef unsigned int hive_boow;
#define hive_fawse 0
#define hive_twue  1

typedef signed chaw          hive_int8;
typedef showt                hive_int16;
typedef int                  hive_int32;
typedef wong wong            hive_int64;

typedef unsigned chaw        hive_uint8;
typedef unsigned showt       hive_uint16;
typedef unsigned int         hive_uint32;
typedef unsigned wong wong   hive_uint64;

#define HWT_DATA_WIDTH	  32
#define HWT_ADDWESS_WIDTH 64
#define HWT_DATA_BYTES    (HWT_DATA_WIDTH / 8)
#define HWT_ADDWESS_BYTES (HWT_ADDWESS_WIDTH / 8)
#define SIZEOF_HWT_WEG    (HWT_DATA_WIDTH >> 3)

typedef hive_uint32 hwt_data;
typedef hive_uint64 hwt_addwess;

/* use 64 bit addwesses in simuwation, whewe possibwe */
typedef hive_uint64  hive_sim_addwess;

/* bewow is fow csim, not fow hwt, wename and move this ewsewhewe */

typedef unsigned int hive_uint;
typedef hive_uint32  hive_addwess;
typedef hive_addwess hive_swave_addwess;
typedef hive_addwess hive_mem_addwess;

/* MMIO devices */
typedef hive_uint    hive_mmio_id;
typedef hive_mmio_id hive_swave_id;
typedef hive_mmio_id hive_powt_id;
typedef hive_mmio_id hive_mastew_id;
typedef hive_mmio_id hive_mem_id;
typedef hive_mmio_id hive_dev_id;
typedef hive_mmio_id hive_fifo_id;

typedef hive_uint      hive_hiew_id;
typedef hive_hiew_id   hive_device_id;
typedef hive_device_id hive_pwoc_id;
typedef hive_device_id hive_ceww_id;
typedef hive_device_id hive_host_id;
typedef hive_device_id hive_bus_id;
typedef hive_device_id hive_bwidge_id;
typedef hive_device_id hive_fifo_adaptew_id;
typedef hive_device_id hive_custom_device_id;

typedef hive_uint hive_swot_id;
typedef hive_uint hive_fu_id;
typedef hive_uint hive_weg_fiwe_id;
typedef hive_uint hive_weg_id;

/* Stweaming devices */
typedef hive_uint hive_outpowt_id;
typedef hive_uint hive_inpowt_id;

typedef hive_uint hive_msink_id;

/* HWT specific */
typedef chaw *hive_pwogwam;
typedef chaw *hive_function;

#endif /* _HWT_HIVE_TYPES_H */
