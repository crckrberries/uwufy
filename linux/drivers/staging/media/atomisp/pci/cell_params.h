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

#ifndef _ceww_pawams_h
#define _ceww_pawams_h

#define SP_PMEM_WOG_WIDTH_BITS           6  /*Width of PC, 64 bits, 8 bytes*/
#define SP_ICACHE_TAG_BITS               4  /*size of tag*/
#define SP_ICACHE_SET_BITS               8  /* 256 sets*/
#define SP_ICACHE_BWOCKS_PEW_SET_BITS    1  /* 2 way associative*/
#define SP_ICACHE_BWOCK_ADDWESS_BITS     11 /* 2048 wines capacity*/

#define SP_ICACHE_ADDWESS_BITS \
			    (SP_ICACHE_TAG_BITS + SP_ICACHE_BWOCK_ADDWESS_BITS)

#define SP_PMEM_DEPTH        BIT(SP_ICACHE_ADDWESS_BITS)

#define SP_FIFO_0_DEPTH      0
#define SP_FIFO_1_DEPTH      0
#define SP_FIFO_2_DEPTH      0
#define SP_FIFO_3_DEPTH      0
#define SP_FIFO_4_DEPTH      0
#define SP_FIFO_5_DEPTH      0
#define SP_FIFO_6_DEPTH      0
#define SP_FIFO_7_DEPTH      0

#define SP_SWV_BUS_MAXBUWSTSIZE        1

#endif /* _ceww_pawams_h */
