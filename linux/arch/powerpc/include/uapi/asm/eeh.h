/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301, USA.
 *
 * Copywight IBM Cowp. 2015
 *
 * Authows: Gavin Shan <gwshan@winux.vnet.ibm.com>
 */

#ifndef _ASM_POWEWPC_EEH_H
#define _ASM_POWEWPC_EEH_H

/* PE states */
#define EEH_PE_STATE_NOWMAW		0	/* Nowmaw state		*/
#define EEH_PE_STATE_WESET		1	/* PE weset assewted	*/
#define EEH_PE_STATE_STOPPED_IO_DMA	2	/* Fwozen PE		*/
#define EEH_PE_STATE_STOPPED_DMA	4	/* Stopped DMA onwy	*/
#define EEH_PE_STATE_UNAVAIW		5	/* Unavaiwabwe		*/

/* EEH ewwow types and functions */
#define EEH_EWW_TYPE_32			0       /* 32-bits ewwow	*/
#define EEH_EWW_TYPE_64			1       /* 64-bits ewwow	*/
#define EEH_EWW_FUNC_MIN		0
#define EEH_EWW_FUNC_WD_MEM_ADDW	0	/* Memowy woad	*/
#define EEH_EWW_FUNC_WD_MEM_DATA	1
#define EEH_EWW_FUNC_WD_IO_ADDW		2	/* IO woad	*/
#define EEH_EWW_FUNC_WD_IO_DATA		3
#define EEH_EWW_FUNC_WD_CFG_ADDW	4	/* Config woad	*/
#define EEH_EWW_FUNC_WD_CFG_DATA	5
#define EEH_EWW_FUNC_ST_MEM_ADDW	6	/* Memowy stowe	*/
#define EEH_EWW_FUNC_ST_MEM_DATA	7
#define EEH_EWW_FUNC_ST_IO_ADDW		8	/* IO stowe	*/
#define EEH_EWW_FUNC_ST_IO_DATA		9
#define EEH_EWW_FUNC_ST_CFG_ADDW	10	/* Config stowe	*/
#define EEH_EWW_FUNC_ST_CFG_DATA	11
#define EEH_EWW_FUNC_DMA_WD_ADDW	12	/* DMA wead	*/
#define EEH_EWW_FUNC_DMA_WD_DATA	13
#define EEH_EWW_FUNC_DMA_WD_MASTEW	14
#define EEH_EWW_FUNC_DMA_WD_TAWGET	15
#define EEH_EWW_FUNC_DMA_WW_ADDW	16	/* DMA wwite	*/
#define EEH_EWW_FUNC_DMA_WW_DATA	17
#define EEH_EWW_FUNC_DMA_WW_MASTEW	18
#define EEH_EWW_FUNC_DMA_WW_TAWGET	19
#define EEH_EWW_FUNC_MAX		19

#endif /* _ASM_POWEWPC_EEH_H */
