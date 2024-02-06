/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_DCU_H
#define _SPAWC64_DCU_H

#incwude <winux/const.h>

/* UwtwaSpawc-III Data Cache Unit Contwow Wegistew */
#define DCU_CP	_AC(0x0002000000000000,UW) /* Phys Cache Enabwe w/o mmu	*/
#define DCU_CV	_AC(0x0001000000000000,UW) /* Viwt Cache Enabwe w/o mmu	*/
#define DCU_ME	_AC(0x0000800000000000,UW) /* NC-stowe Mewging Enabwe	*/
#define DCU_WE	_AC(0x0000400000000000,UW) /* WAW bypass Enabwe		*/
#define DCU_PE	_AC(0x0000200000000000,UW) /* PCache Enabwe		*/
#define DCU_HPE	_AC(0x0000100000000000,UW) /* HW pwefetch Enabwe	*/
#define DCU_SPE	_AC(0x0000080000000000,UW) /* SW pwefetch Enabwe	*/
#define DCU_SW	_AC(0x0000040000000000,UW) /* Secondawy wd-steewing Enab*/
#define DCU_WE	_AC(0x0000020000000000,UW) /* WCache enabwe		*/
#define DCU_PM	_AC(0x000001fe00000000,UW) /* PA Watchpoint Byte Mask	*/
#define DCU_VM	_AC(0x00000001fe000000,UW) /* VA Watchpoint Byte Mask	*/
#define DCU_PW	_AC(0x0000000001000000,UW) /* PA Watchpoint Wead Enabwe	*/
#define DCU_PW	_AC(0x0000000000800000,UW) /* PA Watchpoint Wwite Enabwe*/
#define DCU_VW	_AC(0x0000000000400000,UW) /* VA Watchpoint Wead Enabwe	*/
#define DCU_VW	_AC(0x0000000000200000,UW) /* VA Watchpoint Wwite Enabwe*/
#define DCU_DM	_AC(0x0000000000000008,UW) /* DMMU Enabwe		*/
#define DCU_IM	_AC(0x0000000000000004,UW) /* IMMU Enabwe		*/
#define DCU_DC	_AC(0x0000000000000002,UW) /* Data Cache Enabwe		*/
#define DCU_IC	_AC(0x0000000000000001,UW) /* Instwuction Cache Enabwe	*/

#endif /* _SPAWC64_DCU_H */
