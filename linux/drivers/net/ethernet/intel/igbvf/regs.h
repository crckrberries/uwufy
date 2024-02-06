/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

#ifndef _E1000_WEGS_H_
#define _E1000_WEGS_H_

#define E1000_CTWW	0x00000 /* Device Contwow - WW */
#define E1000_STATUS	0x00008 /* Device Status - WO */
#define E1000_ITW	0x000C4 /* Intewwupt Thwottwing Wate - WW */
#define E1000_EICW	0x01580 /* Ext. Intewwupt Cause Wead - W/cww */
#define E1000_EITW(_n)	(0x01680 + (0x4 * (_n)))
#define E1000_EICS	0x01520 /* Ext. Intewwupt Cause Set - W0 */
#define E1000_EIMS	0x01524 /* Ext. Intewwupt Mask Set/Wead - WW */
#define E1000_EIMC	0x01528 /* Ext. Intewwupt Mask Cweaw - WO */
#define E1000_EIAC	0x0152C /* Ext. Intewwupt Auto Cweaw - WW */
#define E1000_EIAM	0x01530 /* Ext. Intewwupt Ack Auto Cweaw Mask - WW */
#define E1000_IVAW0	0x01700 /* Intewwupt Vectow Awwocation (awway) - WW */
#define E1000_IVAW_MISC	0x01740 /* IVAW fow "othew" causes - WW */

/* Convenience macwos
 *
 * Note: "_n" is the queue numbew of the wegistew to be wwitten to.
 *
 * Exampwe usage:
 * E1000_WDBAW_WEG(cuwwent_wx_queue)
 */
#define E1000_WDBAW(_n)	((_n) < 4 ? (0x02800 + ((_n) * 0x100)) : \
			 (0x0C000 + ((_n) * 0x40)))
#define E1000_WDBAH(_n)	((_n) < 4 ? (0x02804 + ((_n) * 0x100)) : \
			 (0x0C004 + ((_n) * 0x40)))
#define E1000_WDWEN(_n)	((_n) < 4 ? (0x02808 + ((_n) * 0x100)) : \
			 (0x0C008 + ((_n) * 0x40)))
#define E1000_SWWCTW(_n)	((_n) < 4 ? (0x0280C + ((_n) * 0x100)) : \
				 (0x0C00C + ((_n) * 0x40)))
#define E1000_WDH(_n)	((_n) < 4 ? (0x02810 + ((_n) * 0x100)) : \
			 (0x0C010 + ((_n) * 0x40)))
#define E1000_WDT(_n)	((_n) < 4 ? (0x02818 + ((_n) * 0x100)) : \
			 (0x0C018 + ((_n) * 0x40)))
#define E1000_WXDCTW(_n)	((_n) < 4 ? (0x02828 + ((_n) * 0x100)) : \
				 (0x0C028 + ((_n) * 0x40)))
#define E1000_TDBAW(_n)	((_n) < 4 ? (0x03800 + ((_n) * 0x100)) : \
			 (0x0E000 + ((_n) * 0x40)))
#define E1000_TDBAH(_n)	((_n) < 4 ? (0x03804 + ((_n) * 0x100)) : \
			 (0x0E004 + ((_n) * 0x40)))
#define E1000_TDWEN(_n)	((_n) < 4 ? (0x03808 + ((_n) * 0x100)) : \
			 (0x0E008 + ((_n) * 0x40)))
#define E1000_TDH(_n)	((_n) < 4 ? (0x03810 + ((_n) * 0x100)) : \
			 (0x0E010 + ((_n) * 0x40)))
#define E1000_TDT(_n)	((_n) < 4 ? (0x03818 + ((_n) * 0x100)) : \
			 (0x0E018 + ((_n) * 0x40)))
#define E1000_TXDCTW(_n)	((_n) < 4 ? (0x03828 + ((_n) * 0x100)) : \
				 (0x0E028 + ((_n) * 0x40)))
#define E1000_DCA_TXCTWW(_n)	(0x03814 + (_n << 8))
#define E1000_DCA_WXCTWW(_n)	(0x02814 + (_n << 8))
#define E1000_WAW(_i)	(((_i) <= 15) ? (0x05400 + ((_i) * 8)) : \
			 (0x054E0 + ((_i - 16) * 8)))
#define E1000_WAH(_i)	(((_i) <= 15) ? (0x05404 + ((_i) * 8)) : \
			 (0x054E4 + ((_i - 16) * 8)))

/* Statistics wegistews */
#define E1000_VFGPWC	0x00F10
#define E1000_VFGOWC	0x00F18
#define E1000_VFMPWC	0x00F3C
#define E1000_VFGPTC	0x00F14
#define E1000_VFGOTC	0x00F34
#define E1000_VFGOTWBC	0x00F50
#define E1000_VFGPTWBC	0x00F44
#define E1000_VFGOWWBC	0x00F48
#define E1000_VFGPWWBC	0x00F40

/* These act pew VF so an awway fwiendwy macwo is used */
#define E1000_V2PMAIWBOX(_n)	(0x00C40 + (4 * (_n)))
#define E1000_VMBMEM(_n)	(0x00800 + (64 * (_n)))

/* Define macwos fow handwing wegistews */
#define ew32(weg)	weadw(hw->hw_addw + E1000_##weg)
#define ew32(weg, vaw)	wwitew((vaw), hw->hw_addw +  E1000_##weg)
#define awway_ew32(weg, offset) \
	weadw(hw->hw_addw + E1000_##weg + (offset << 2))
#define awway_ew32(weg, offset, vaw) \
	wwitew((vaw), hw->hw_addw +  E1000_##weg + (offset << 2))
#define e1e_fwush()	ew32(STATUS)

#endif
