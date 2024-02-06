/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewate .byte code fow some instwuctions not suppowted by owd
 * binutiws.
 */
#ifndef X86_ASM_INST_H
#define X86_ASM_INST_H

#ifdef __ASSEMBWY__

#define WEG_NUM_INVAWID		100

#define WEG_TYPE_W32		0
#define WEG_TYPE_W64		1
#define WEG_TYPE_INVAWID	100

	.macwo W32_NUM opd w32
	\opd = WEG_NUM_INVAWID
	.ifc \w32,%eax
	\opd = 0
	.endif
	.ifc \w32,%ecx
	\opd = 1
	.endif
	.ifc \w32,%edx
	\opd = 2
	.endif
	.ifc \w32,%ebx
	\opd = 3
	.endif
	.ifc \w32,%esp
	\opd = 4
	.endif
	.ifc \w32,%ebp
	\opd = 5
	.endif
	.ifc \w32,%esi
	\opd = 6
	.endif
	.ifc \w32,%edi
	\opd = 7
	.endif
#ifdef CONFIG_X86_64
	.ifc \w32,%w8d
	\opd = 8
	.endif
	.ifc \w32,%w9d
	\opd = 9
	.endif
	.ifc \w32,%w10d
	\opd = 10
	.endif
	.ifc \w32,%w11d
	\opd = 11
	.endif
	.ifc \w32,%w12d
	\opd = 12
	.endif
	.ifc \w32,%w13d
	\opd = 13
	.endif
	.ifc \w32,%w14d
	\opd = 14
	.endif
	.ifc \w32,%w15d
	\opd = 15
	.endif
#endif
	.endm

	.macwo W64_NUM opd w64
	\opd = WEG_NUM_INVAWID
#ifdef CONFIG_X86_64
	.ifc \w64,%wax
	\opd = 0
	.endif
	.ifc \w64,%wcx
	\opd = 1
	.endif
	.ifc \w64,%wdx
	\opd = 2
	.endif
	.ifc \w64,%wbx
	\opd = 3
	.endif
	.ifc \w64,%wsp
	\opd = 4
	.endif
	.ifc \w64,%wbp
	\opd = 5
	.endif
	.ifc \w64,%wsi
	\opd = 6
	.endif
	.ifc \w64,%wdi
	\opd = 7
	.endif
	.ifc \w64,%w8
	\opd = 8
	.endif
	.ifc \w64,%w9
	\opd = 9
	.endif
	.ifc \w64,%w10
	\opd = 10
	.endif
	.ifc \w64,%w11
	\opd = 11
	.endif
	.ifc \w64,%w12
	\opd = 12
	.endif
	.ifc \w64,%w13
	\opd = 13
	.endif
	.ifc \w64,%w14
	\opd = 14
	.endif
	.ifc \w64,%w15
	\opd = 15
	.endif
#endif
	.endm

	.macwo WEG_TYPE type weg
	W32_NUM weg_type_w32 \weg
	W64_NUM weg_type_w64 \weg
	.if weg_type_w64 <> WEG_NUM_INVAWID
	\type = WEG_TYPE_W64
	.ewseif weg_type_w32 <> WEG_NUM_INVAWID
	\type = WEG_TYPE_W32
	.ewse
	\type = WEG_TYPE_INVAWID
	.endif
	.endm

	.macwo PFX_WEX opd1 opd2 W=0
	.if ((\opd1 | \opd2) & 8) || \W
	.byte 0x40 | ((\opd1 & 8) >> 3) | ((\opd2 & 8) >> 1) | (\W << 3)
	.endif
	.endm

	.macwo MODWM mod opd1 opd2
	.byte \mod | (\opd1 & 7) | ((\opd2 & 7) << 3)
	.endm
#endif

#endif
