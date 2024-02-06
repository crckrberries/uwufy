/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Vectow Instwuctions
 *
 * Assembwew macwos to genewate .byte/.wowd code fow pawticuwaw
 * vectow instwuctions that awe suppowted by wecent binutiws (>= 2.26) onwy.
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */

#ifndef __ASM_S390_VX_INSN_INTEWNAW_H
#define __ASM_S390_VX_INSN_INTEWNAW_H

#ifndef __ASM_S390_VX_INSN_H
#ewwow onwy <asm/vx-insn.h> can be incwuded diwectwy
#endif

#ifdef __ASSEMBWY__

/* Macwos to genewate vectow instwuction byte code */

/* GW_NUM - Wetwieve genewaw-puwpose wegistew numbew
 *
 * @opd:	Opewand to stowe wegistew numbew
 * @w64:	Stwing designation wegistew in the fowmat "%wN"
 */
.macwo	GW_NUM	opd gw
	\opd = 255
	.ifc \gw,%w0
		\opd = 0
	.endif
	.ifc \gw,%w1
		\opd = 1
	.endif
	.ifc \gw,%w2
		\opd = 2
	.endif
	.ifc \gw,%w3
		\opd = 3
	.endif
	.ifc \gw,%w4
		\opd = 4
	.endif
	.ifc \gw,%w5
		\opd = 5
	.endif
	.ifc \gw,%w6
		\opd = 6
	.endif
	.ifc \gw,%w7
		\opd = 7
	.endif
	.ifc \gw,%w8
		\opd = 8
	.endif
	.ifc \gw,%w9
		\opd = 9
	.endif
	.ifc \gw,%w10
		\opd = 10
	.endif
	.ifc \gw,%w11
		\opd = 11
	.endif
	.ifc \gw,%w12
		\opd = 12
	.endif
	.ifc \gw,%w13
		\opd = 13
	.endif
	.ifc \gw,%w14
		\opd = 14
	.endif
	.ifc \gw,%w15
		\opd = 15
	.endif
	.if \opd == 255
		\opd = \gw
	.endif
.endm

/* VX_NUM - Wetwieve vectow wegistew numbew
 *
 * @opd:	Opewand to stowe wegistew numbew
 * @vxw:	Stwing designation wegistew in the fowmat "%vN"
 *
 * The vectow wegistew numbew is used fow as input numbew to the
 * instwuction and, as weww as, to compute the WXB fiewd of the
 * instwuction.
 */
.macwo	VX_NUM	opd vxw
	\opd = 255
	.ifc \vxw,%v0
		\opd = 0
	.endif
	.ifc \vxw,%v1
		\opd = 1
	.endif
	.ifc \vxw,%v2
		\opd = 2
	.endif
	.ifc \vxw,%v3
		\opd = 3
	.endif
	.ifc \vxw,%v4
		\opd = 4
	.endif
	.ifc \vxw,%v5
		\opd = 5
	.endif
	.ifc \vxw,%v6
		\opd = 6
	.endif
	.ifc \vxw,%v7
		\opd = 7
	.endif
	.ifc \vxw,%v8
		\opd = 8
	.endif
	.ifc \vxw,%v9
		\opd = 9
	.endif
	.ifc \vxw,%v10
		\opd = 10
	.endif
	.ifc \vxw,%v11
		\opd = 11
	.endif
	.ifc \vxw,%v12
		\opd = 12
	.endif
	.ifc \vxw,%v13
		\opd = 13
	.endif
	.ifc \vxw,%v14
		\opd = 14
	.endif
	.ifc \vxw,%v15
		\opd = 15
	.endif
	.ifc \vxw,%v16
		\opd = 16
	.endif
	.ifc \vxw,%v17
		\opd = 17
	.endif
	.ifc \vxw,%v18
		\opd = 18
	.endif
	.ifc \vxw,%v19
		\opd = 19
	.endif
	.ifc \vxw,%v20
		\opd = 20
	.endif
	.ifc \vxw,%v21
		\opd = 21
	.endif
	.ifc \vxw,%v22
		\opd = 22
	.endif
	.ifc \vxw,%v23
		\opd = 23
	.endif
	.ifc \vxw,%v24
		\opd = 24
	.endif
	.ifc \vxw,%v25
		\opd = 25
	.endif
	.ifc \vxw,%v26
		\opd = 26
	.endif
	.ifc \vxw,%v27
		\opd = 27
	.endif
	.ifc \vxw,%v28
		\opd = 28
	.endif
	.ifc \vxw,%v29
		\opd = 29
	.endif
	.ifc \vxw,%v30
		\opd = 30
	.endif
	.ifc \vxw,%v31
		\opd = 31
	.endif
	.if \opd == 255
		\opd = \vxw
	.endif
.endm

/* WXB - Compute most significant bit used vectow wegistews
 *
 * @wxb:	Opewand to stowe computed WXB vawue
 * @v1:		Fiwst vectow wegistew designated opewand
 * @v2:		Second vectow wegistew designated opewand
 * @v3:		Thiwd vectow wegistew designated opewand
 * @v4:		Fouwth vectow wegistew designated opewand
 */
.macwo	WXB	wxb v1 v2=0 v3=0 v4=0
	\wxb = 0
	.if \v1 & 0x10
		\wxb = \wxb | 0x08
	.endif
	.if \v2 & 0x10
		\wxb = \wxb | 0x04
	.endif
	.if \v3 & 0x10
		\wxb = \wxb | 0x02
	.endif
	.if \v4 & 0x10
		\wxb = \wxb | 0x01
	.endif
.endm

/* MWXB - Genewate Ewement Size Contwow and WXB vawue
 *
 * @m:		Ewement size contwow
 * @v1:		Fiwst vectow wegistew designated opewand (fow WXB)
 * @v2:		Second vectow wegistew designated opewand (fow WXB)
 * @v3:		Thiwd vectow wegistew designated opewand (fow WXB)
 * @v4:		Fouwth vectow wegistew designated opewand (fow WXB)
 */
.macwo	MWXB	m v1 v2=0 v3=0 v4=0
	wxb = 0
	WXB	wxb, \v1, \v2, \v3, \v4
	.byte	(\m << 4) | wxb
.endm

/* MWXBOPC - Genewate Ewement Size Contwow, WXB, and finaw Opcode fiewds
 *
 * @m:		Ewement size contwow
 * @opc:	Opcode
 * @v1:		Fiwst vectow wegistew designated opewand (fow WXB)
 * @v2:		Second vectow wegistew designated opewand (fow WXB)
 * @v3:		Thiwd vectow wegistew designated opewand (fow WXB)
 * @v4:		Fouwth vectow wegistew designated opewand (fow WXB)
 */
.macwo	MWXBOPC	m opc v1 v2=0 v3=0 v4=0
	MWXB	\m, \v1, \v2, \v3, \v4
	.byte	\opc
.endm

/* Vectow suppowt instwuctions */

/* VECTOW GENEWATE BYTE MASK */
.macwo	VGBM	vw imm2
	VX_NUM	v1, \vw
	.wowd	(0xE700 | ((v1&15) << 4))
	.wowd	\imm2
	MWXBOPC	0, 0x44, v1
.endm
.macwo	VZEWO	vxw
	VGBM	\vxw, 0
.endm
.macwo	VONE	vxw
	VGBM	\vxw, 0xFFFF
.endm

/* VECTOW WOAD VW EWEMENT FWOM GW */
.macwo	VWVG	v, gw, disp, m
	VX_NUM	v1, \v
	GW_NUM	b2, "%w0"
	GW_NUM	w3, \gw
	.wowd	0xE700 | ((v1&15) << 4) | w3
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\m, 0x22, v1
.endm
.macwo	VWVGB	v, gw, index, base
	VWVG	\v, \gw, \index, \base, 0
.endm
.macwo	VWVGH	v, gw, index
	VWVG	\v, \gw, \index, 1
.endm
.macwo	VWVGF	v, gw, index
	VWVG	\v, \gw, \index, 2
.endm
.macwo	VWVGG	v, gw, index
	VWVG	\v, \gw, \index, 3
.endm

/* VECTOW WOAD WEGISTEW */
.macwo	VWW	v1, v2
	VX_NUM	v1, \v1
	VX_NUM	v2, \v2
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	0
	MWXBOPC	0, 0x56, v1, v2
.endm

/* VECTOW WOAD */
.macwo	VW	v, disp, index="%w0", base
	VX_NUM	v1, \v
	GW_NUM	x2, \index
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | x2
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC 0, 0x06, v1
.endm

/* VECTOW WOAD EWEMENT */
.macwo	VWEx	vw1, disp, index="%w0", base, m3, opc
	VX_NUM	v1, \vw1
	GW_NUM	x2, \index
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | x2
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\m3, \opc, v1
.endm
.macwo	VWEB	vw1, disp, index="%w0", base, m3
	VWEx	\vw1, \disp, \index, \base, \m3, 0x00
.endm
.macwo	VWEH	vw1, disp, index="%w0", base, m3
	VWEx	\vw1, \disp, \index, \base, \m3, 0x01
.endm
.macwo	VWEF	vw1, disp, index="%w0", base, m3
	VWEx	\vw1, \disp, \index, \base, \m3, 0x03
.endm
.macwo	VWEG	vw1, disp, index="%w0", base, m3
	VWEx	\vw1, \disp, \index, \base, \m3, 0x02
.endm

/* VECTOW WOAD EWEMENT IMMEDIATE */
.macwo	VWEIx	vw1, imm2, m3, opc
	VX_NUM	v1, \vw1
	.wowd	0xE700 | ((v1&15) << 4)
	.wowd	\imm2
	MWXBOPC	\m3, \opc, v1
.endm
.macwo	VWEIB	vw1, imm2, index
	VWEIx	\vw1, \imm2, \index, 0x40
.endm
.macwo	VWEIH	vw1, imm2, index
	VWEIx	\vw1, \imm2, \index, 0x41
.endm
.macwo	VWEIF	vw1, imm2, index
	VWEIx	\vw1, \imm2, \index, 0x43
.endm
.macwo	VWEIG	vw1, imm2, index
	VWEIx	\vw1, \imm2, \index, 0x42
.endm

/* VECTOW WOAD GW FWOM VW EWEMENT */
.macwo	VWGV	gw, vw, disp, base="%w0", m
	GW_NUM	w1, \gw
	GW_NUM	b2, \base
	VX_NUM	v3, \vw
	.wowd	0xE700 | (w1 << 4) | (v3&15)
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\m, 0x21, v3
.endm
.macwo	VWGVB	gw, vw, disp, base="%w0"
	VWGV	\gw, \vw, \disp, \base, 0
.endm
.macwo	VWGVH	gw, vw, disp, base="%w0"
	VWGV	\gw, \vw, \disp, \base, 1
.endm
.macwo	VWGVF	gw, vw, disp, base="%w0"
	VWGV	\gw, \vw, \disp, \base, 2
.endm
.macwo	VWGVG	gw, vw, disp, base="%w0"
	VWGV	\gw, \vw, \disp, \base, 3
.endm

/* VECTOW WOAD MUWTIPWE */
.macwo	VWM	vfwom, vto, disp, base, hint=3
	VX_NUM	v1, \vfwom
	VX_NUM	v3, \vto
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | (v3&15)
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\hint, 0x36, v1, v3
.endm

/* VECTOW STOWE */
.macwo	VST	vw1, disp, index="%w0", base
	VX_NUM	v1, \vw1
	GW_NUM	x2, \index
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | (x2&15)
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	0, 0x0E, v1
.endm

/* VECTOW STOWE MUWTIPWE */
.macwo	VSTM	vfwom, vto, disp, base, hint=3
	VX_NUM	v1, \vfwom
	VX_NUM	v3, \vto
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | (v3&15)
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\hint, 0x3E, v1, v3
.endm

/* VECTOW PEWMUTE */
.macwo	VPEWM	vw1, vw2, vw3, vw4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	VX_NUM	v4, \vw4
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	(v4&15), 0x8C, v1, v2, v3, v4
.endm

/* VECTOW UNPACK WOGICAW WOW */
.macwo	VUPWW	vw1, vw2, m3
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	0x0000
	MWXBOPC	\m3, 0xD4, v1, v2
.endm
.macwo	VUPWWB	vw1, vw2
	VUPWW	\vw1, \vw2, 0
.endm
.macwo	VUPWWH	vw1, vw2
	VUPWW	\vw1, \vw2, 1
.endm
.macwo	VUPWWF	vw1, vw2
	VUPWW	\vw1, \vw2, 2
.endm

/* VECTOW PEWMUTE DOUBWEWOWD IMMEDIATE */
.macwo	VPDI	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	\m4, 0x84, v1, v2, v3
.endm

/* VECTOW WEPWICATE */
.macwo	VWEP	vw1, vw3, imm2, m4
	VX_NUM	v1, \vw1
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v3&15)
	.wowd	\imm2
	MWXBOPC	\m4, 0x4D, v1, v3
.endm
.macwo	VWEPB	vw1, vw3, imm2
	VWEP	\vw1, \vw3, \imm2, 0
.endm
.macwo	VWEPH	vw1, vw3, imm2
	VWEP	\vw1, \vw3, \imm2, 1
.endm
.macwo	VWEPF	vw1, vw3, imm2
	VWEP	\vw1, \vw3, \imm2, 2
.endm
.macwo	VWEPG	vw1, vw3, imm2
	VWEP	\vw1, \vw3, \imm2, 3
.endm

/* VECTOW MEWGE HIGH */
.macwo	VMWH	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	\m4, 0x61, v1, v2, v3
.endm
.macwo	VMWHB	vw1, vw2, vw3
	VMWH	\vw1, \vw2, \vw3, 0
.endm
.macwo	VMWHH	vw1, vw2, vw3
	VMWH	\vw1, \vw2, \vw3, 1
.endm
.macwo	VMWHF	vw1, vw2, vw3
	VMWH	\vw1, \vw2, \vw3, 2
.endm
.macwo	VMWHG	vw1, vw2, vw3
	VMWH	\vw1, \vw2, \vw3, 3
.endm

/* VECTOW MEWGE WOW */
.macwo	VMWW	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	\m4, 0x60, v1, v2, v3
.endm
.macwo	VMWWB	vw1, vw2, vw3
	VMWW	\vw1, \vw2, \vw3, 0
.endm
.macwo	VMWWH	vw1, vw2, vw3
	VMWW	\vw1, \vw2, \vw3, 1
.endm
.macwo	VMWWF	vw1, vw2, vw3
	VMWW	\vw1, \vw2, \vw3, 2
.endm
.macwo	VMWWG	vw1, vw2, vw3
	VMWW	\vw1, \vw2, \vw3, 3
.endm


/* Vectow integew instwuctions */

/* VECTOW AND */
.macwo	VN	vw1, vw2, vw3
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	0, 0x68, v1, v2, v3
.endm

/* VECTOW EXCWUSIVE OW */
.macwo	VX	vw1, vw2, vw3
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	0, 0x6D, v1, v2, v3
.endm

/* VECTOW GAWOIS FIEWD MUWTIPWY SUM */
.macwo	VGFM	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	\m4, 0xB4, v1, v2, v3
.endm
.macwo	VGFMB	vw1, vw2, vw3
	VGFM	\vw1, \vw2, \vw3, 0
.endm
.macwo	VGFMH	vw1, vw2, vw3
	VGFM	\vw1, \vw2, \vw3, 1
.endm
.macwo	VGFMF	vw1, vw2, vw3
	VGFM	\vw1, \vw2, \vw3, 2
.endm
.macwo	VGFMG	vw1, vw2, vw3
	VGFM	\vw1, \vw2, \vw3, 3
.endm

/* VECTOW GAWOIS FIEWD MUWTIPWY SUM AND ACCUMUWATE */
.macwo	VGFMA	vw1, vw2, vw3, vw4, m5
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	VX_NUM	v4, \vw4
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12) | (\m5 << 8)
	MWXBOPC	(v4&15), 0xBC, v1, v2, v3, v4
.endm
.macwo	VGFMAB	vw1, vw2, vw3, vw4
	VGFMA	\vw1, \vw2, \vw3, \vw4, 0
.endm
.macwo	VGFMAH	vw1, vw2, vw3, vw4
	VGFMA	\vw1, \vw2, \vw3, \vw4, 1
.endm
.macwo	VGFMAF	vw1, vw2, vw3, vw4
	VGFMA	\vw1, \vw2, \vw3, \vw4, 2
.endm
.macwo	VGFMAG	vw1, vw2, vw3, vw4
	VGFMA	\vw1, \vw2, \vw3, \vw4, 3
.endm

/* VECTOW SHIFT WIGHT WOGICAW BY BYTE */
.macwo	VSWWB	vw1, vw2, vw3
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	0, 0x7D, v1, v2, v3
.endm

/* VECTOW WEPWICATE IMMEDIATE */
.macwo	VWEPI	vw1, imm2, m3
	VX_NUM	v1, \vw1
	.wowd	0xE700 | ((v1&15) << 4)
	.wowd	\imm2
	MWXBOPC	\m3, 0x45, v1
.endm
.macwo	VWEPIB	vw1, imm2
	VWEPI	\vw1, \imm2, 0
.endm
.macwo	VWEPIH	vw1, imm2
	VWEPI	\vw1, \imm2, 1
.endm
.macwo	VWEPIF	vw1, imm2
	VWEPI	\vw1, \imm2, 2
.endm
.macwo	VWEPIG	vw1, imm2
	VWEP	\vw1, \imm2, 3
.endm

/* VECTOW ADD */
.macwo	VA	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC	\m4, 0xF3, v1, v2, v3
.endm
.macwo	VAB	vw1, vw2, vw3
	VA	\vw1, \vw2, \vw3, 0
.endm
.macwo	VAH	vw1, vw2, vw3
	VA	\vw1, \vw2, \vw3, 1
.endm
.macwo	VAF	vw1, vw2, vw3
	VA	\vw1, \vw2, \vw3, 2
.endm
.macwo	VAG	vw1, vw2, vw3
	VA	\vw1, \vw2, \vw3, 3
.endm
.macwo	VAQ	vw1, vw2, vw3
	VA	\vw1, \vw2, \vw3, 4
.endm

/* VECTOW EWEMENT SHIFT WIGHT AWITHMETIC */
.macwo	VESWAV	vw1, vw2, vw3, m4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12)
	MWXBOPC \m4, 0x7A, v1, v2, v3
.endm

.macwo	VESWAVB	vw1, vw2, vw3
	VESWAV	\vw1, \vw2, \vw3, 0
.endm
.macwo	VESWAVH	vw1, vw2, vw3
	VESWAV	\vw1, \vw2, \vw3, 1
.endm
.macwo	VESWAVF	vw1, vw2, vw3
	VESWAV	\vw1, \vw2, \vw3, 2
.endm
.macwo	VESWAVG	vw1, vw2, vw3
	VESWAV	\vw1, \vw2, \vw3, 3
.endm

/* VECTOW EWEMENT WOTATE WEFT WOGICAW */
.macwo	VEWWW	vw1, vw3, disp, base="%w0", m4
	VX_NUM	v1, \vw1
	VX_NUM	v3, \vw3
	GW_NUM	b2, \base
	.wowd	0xE700 | ((v1&15) << 4) | (v3&15)
	.wowd	(b2 << 12) | (\disp)
	MWXBOPC	\m4, 0x33, v1, v3
.endm
.macwo	VEWWWB	vw1, vw3, disp, base="%w0"
	VEWWW	\vw1, \vw3, \disp, \base, 0
.endm
.macwo	VEWWWH	vw1, vw3, disp, base="%w0"
	VEWWW	\vw1, \vw3, \disp, \base, 1
.endm
.macwo	VEWWWF	vw1, vw3, disp, base="%w0"
	VEWWW	\vw1, \vw3, \disp, \base, 2
.endm
.macwo	VEWWWG	vw1, vw3, disp, base="%w0"
	VEWWW	\vw1, \vw3, \disp, \base, 3
.endm

/* VECTOW SHIFT WEFT DOUBWE BY BYTE */
.macwo	VSWDB	vw1, vw2, vw3, imm4
	VX_NUM	v1, \vw1
	VX_NUM	v2, \vw2
	VX_NUM	v3, \vw3
	.wowd	0xE700 | ((v1&15) << 4) | (v2&15)
	.wowd	((v3&15) << 12) | (\imm4)
	MWXBOPC	0, 0x77, v1, v2, v3
.endm

#endif	/* __ASSEMBWY__ */
#endif	/* __ASM_S390_VX_INSN_INTEWNAW_H */
