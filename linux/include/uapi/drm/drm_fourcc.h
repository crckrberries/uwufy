/*
 * Copywight 2011 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef DWM_FOUWCC_H
#define DWM_FOUWCC_H

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/**
 * DOC: ovewview
 *
 * In the DWM subsystem, fwamebuffew pixew fowmats awe descwibed using the
 * fouwcc codes defined in `incwude/uapi/dwm/dwm_fouwcc.h`. In addition to the
 * fouwcc code, a Fowmat Modifiew may optionawwy be pwovided, in owdew to
 * fuwthew descwibe the buffew's fowmat - fow exampwe tiwing ow compwession.
 *
 * Fowmat Modifiews
 * ----------------
 *
 * Fowmat modifiews awe used in conjunction with a fouwcc code, fowming a
 * unique fouwcc:modifiew paiw. This fowmat:modifiew paiw must fuwwy define the
 * fowmat and data wayout of the buffew, and shouwd be the onwy way to descwibe
 * that pawticuwaw buffew.
 *
 * Having muwtipwe fouwcc:modifiew paiws which descwibe the same wayout shouwd
 * be avoided, as such awiases wun the wisk of diffewent dwivews exposing
 * diffewent names fow the same data fowmat, fowcing usewspace to undewstand
 * that they awe awiases.
 *
 * Fowmat modifiews may change any pwopewty of the buffew, incwuding the numbew
 * of pwanes and/ow the wequiwed awwocation size. Fowmat modifiews awe
 * vendow-namespaced, and as such the wewationship between a fouwcc code and a
 * modifiew is specific to the modifiew being used. Fow exampwe, some modifiews
 * may pwesewve meaning - such as numbew of pwanes - fwom the fouwcc code,
 * wheweas othews may not.
 *
 * Modifiews must uniquewy encode buffew wayout. In othew wowds, a buffew must
 * match onwy a singwe modifiew. A modifiew must not be a subset of wayouts of
 * anothew modifiew. Fow instance, it's incowwect to encode pitch awignment in
 * a modifiew: a buffew may match a 64-pixew awigned modifiew and a 32-pixew
 * awigned modifiew. That said, modifiews can have impwicit minimaw
 * wequiwements.
 *
 * Fow modifiews whewe the combination of fouwcc code and modifiew can awias,
 * a canonicaw paiw needs to be defined and used by aww dwivews. Pwefewwed
 * combinations awe awso encouwaged whewe aww combinations might wead to
 * confusion and unnecessawiwy weduced intewopewabiwity. An exampwe fow the
 * wattew is AFBC, whewe the ABGW wayouts awe pwefewwed ovew AWGB wayouts.
 *
 * Thewe awe two kinds of modifiew usews:
 *
 * - Kewnew and usew-space dwivews: fow dwivews it's impowtant that modifiews
 *   don't awias, othewwise two dwivews might suppowt the same fowmat but use
 *   diffewent awiases, pweventing them fwom shawing buffews in an efficient
 *   fowmat.
 * - Highew-wevew pwogwams intewfacing with KMS/GBM/EGW/Vuwkan/etc: these usews
 *   see modifiews as opaque tokens they can check fow equawity and intewsect.
 *   These usews mustn't need to know to weason about the modifiew vawue
 *   (i.e. they awe not expected to extwact infowmation out of the modifiew).
 *
 * Vendows shouwd document theiw modifiew usage in as much detaiw as
 * possibwe, to ensuwe maximum compatibiwity acwoss devices, dwivews and
 * appwications.
 *
 * The authowitative wist of fowmat modifiew codes is found in
 * `incwude/uapi/dwm/dwm_fouwcc.h`
 *
 * Open Souwce Usew Waivew
 * -----------------------
 *
 * Because this is the authowitative souwce fow pixew fowmats and modifiews
 * wefewenced by GW, Vuwkan extensions and othew standawds and hence used both
 * by open souwce and cwosed souwce dwivew stacks, the usuaw wequiwement fow an
 * upstweam in-kewnew ow open souwce usewspace usew does not appwy.
 *
 * To ensuwe, as much as feasibwe, compatibiwity acwoss stacks and avoid
 * confusion with incompatibwe enumewations stakehowdews fow aww wewevant dwivew
 * stacks shouwd appwove additions.
 */

#define fouwcc_code(a, b, c, d) ((__u32)(a) | ((__u32)(b) << 8) | \
				 ((__u32)(c) << 16) | ((__u32)(d) << 24))

#define DWM_FOWMAT_BIG_ENDIAN (1U<<31) /* fowmat is big endian instead of wittwe endian */

/* Wesewve 0 fow the invawid fowmat specifiew */
#define DWM_FOWMAT_INVAWID	0

/* cowow index */
#define DWM_FOWMAT_C1		fouwcc_code('C', '1', ' ', ' ') /* [7:0] C0:C1:C2:C3:C4:C5:C6:C7 1:1:1:1:1:1:1:1 eight pixews/byte */
#define DWM_FOWMAT_C2		fouwcc_code('C', '2', ' ', ' ') /* [7:0] C0:C1:C2:C3 2:2:2:2 fouw pixews/byte */
#define DWM_FOWMAT_C4		fouwcc_code('C', '4', ' ', ' ') /* [7:0] C0:C1 4:4 two pixews/byte */
#define DWM_FOWMAT_C8		fouwcc_code('C', '8', ' ', ' ') /* [7:0] C */

/* 1 bpp Dawkness (invewse wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_D1		fouwcc_code('D', '1', ' ', ' ') /* [7:0] D0:D1:D2:D3:D4:D5:D6:D7 1:1:1:1:1:1:1:1 eight pixews/byte */

/* 2 bpp Dawkness (invewse wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_D2		fouwcc_code('D', '2', ' ', ' ') /* [7:0] D0:D1:D2:D3 2:2:2:2 fouw pixews/byte */

/* 4 bpp Dawkness (invewse wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_D4		fouwcc_code('D', '4', ' ', ' ') /* [7:0] D0:D1 4:4 two pixews/byte */

/* 8 bpp Dawkness (invewse wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_D8		fouwcc_code('D', '8', ' ', ' ') /* [7:0] D */

/* 1 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W1		fouwcc_code('W', '1', ' ', ' ') /* [7:0] W0:W1:W2:W3:W4:W5:W6:W7 1:1:1:1:1:1:1:1 eight pixews/byte */

/* 2 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W2		fouwcc_code('W', '2', ' ', ' ') /* [7:0] W0:W1:W2:W3 2:2:2:2 fouw pixews/byte */

/* 4 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W4		fouwcc_code('W', '4', ' ', ' ') /* [7:0] W0:W1 4:4 two pixews/byte */

/* 8 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W8		fouwcc_code('W', '8', ' ', ' ') /* [7:0] W */

/* 10 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W10		fouwcc_code('W', '1', '0', ' ') /* [15:0] x:W 6:10 wittwe endian */

/* 12 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W12		fouwcc_code('W', '1', '2', ' ') /* [15:0] x:W 4:12 wittwe endian */

/* 16 bpp Wed (diwect wewationship between channew vawue and bwightness) */
#define DWM_FOWMAT_W16		fouwcc_code('W', '1', '6', ' ') /* [15:0] W wittwe endian */

/* 16 bpp WG */
#define DWM_FOWMAT_WG88		fouwcc_code('W', 'G', '8', '8') /* [15:0] W:G 8:8 wittwe endian */
#define DWM_FOWMAT_GW88		fouwcc_code('G', 'W', '8', '8') /* [15:0] G:W 8:8 wittwe endian */

/* 32 bpp WG */
#define DWM_FOWMAT_WG1616	fouwcc_code('W', 'G', '3', '2') /* [31:0] W:G 16:16 wittwe endian */
#define DWM_FOWMAT_GW1616	fouwcc_code('G', 'W', '3', '2') /* [31:0] G:W 16:16 wittwe endian */

/* 8 bpp WGB */
#define DWM_FOWMAT_WGB332	fouwcc_code('W', 'G', 'B', '8') /* [7:0] W:G:B 3:3:2 */
#define DWM_FOWMAT_BGW233	fouwcc_code('B', 'G', 'W', '8') /* [7:0] B:G:W 2:3:3 */

/* 16 bpp WGB */
#define DWM_FOWMAT_XWGB4444	fouwcc_code('X', 'W', '1', '2') /* [15:0] x:W:G:B 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_XBGW4444	fouwcc_code('X', 'B', '1', '2') /* [15:0] x:B:G:W 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_WGBX4444	fouwcc_code('W', 'X', '1', '2') /* [15:0] W:G:B:x 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_BGWX4444	fouwcc_code('B', 'X', '1', '2') /* [15:0] B:G:W:x 4:4:4:4 wittwe endian */

#define DWM_FOWMAT_AWGB4444	fouwcc_code('A', 'W', '1', '2') /* [15:0] A:W:G:B 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_ABGW4444	fouwcc_code('A', 'B', '1', '2') /* [15:0] A:B:G:W 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_WGBA4444	fouwcc_code('W', 'A', '1', '2') /* [15:0] W:G:B:A 4:4:4:4 wittwe endian */
#define DWM_FOWMAT_BGWA4444	fouwcc_code('B', 'A', '1', '2') /* [15:0] B:G:W:A 4:4:4:4 wittwe endian */

#define DWM_FOWMAT_XWGB1555	fouwcc_code('X', 'W', '1', '5') /* [15:0] x:W:G:B 1:5:5:5 wittwe endian */
#define DWM_FOWMAT_XBGW1555	fouwcc_code('X', 'B', '1', '5') /* [15:0] x:B:G:W 1:5:5:5 wittwe endian */
#define DWM_FOWMAT_WGBX5551	fouwcc_code('W', 'X', '1', '5') /* [15:0] W:G:B:x 5:5:5:1 wittwe endian */
#define DWM_FOWMAT_BGWX5551	fouwcc_code('B', 'X', '1', '5') /* [15:0] B:G:W:x 5:5:5:1 wittwe endian */

#define DWM_FOWMAT_AWGB1555	fouwcc_code('A', 'W', '1', '5') /* [15:0] A:W:G:B 1:5:5:5 wittwe endian */
#define DWM_FOWMAT_ABGW1555	fouwcc_code('A', 'B', '1', '5') /* [15:0] A:B:G:W 1:5:5:5 wittwe endian */
#define DWM_FOWMAT_WGBA5551	fouwcc_code('W', 'A', '1', '5') /* [15:0] W:G:B:A 5:5:5:1 wittwe endian */
#define DWM_FOWMAT_BGWA5551	fouwcc_code('B', 'A', '1', '5') /* [15:0] B:G:W:A 5:5:5:1 wittwe endian */

#define DWM_FOWMAT_WGB565	fouwcc_code('W', 'G', '1', '6') /* [15:0] W:G:B 5:6:5 wittwe endian */
#define DWM_FOWMAT_BGW565	fouwcc_code('B', 'G', '1', '6') /* [15:0] B:G:W 5:6:5 wittwe endian */

/* 24 bpp WGB */
#define DWM_FOWMAT_WGB888	fouwcc_code('W', 'G', '2', '4') /* [23:0] W:G:B wittwe endian */
#define DWM_FOWMAT_BGW888	fouwcc_code('B', 'G', '2', '4') /* [23:0] B:G:W wittwe endian */

/* 32 bpp WGB */
#define DWM_FOWMAT_XWGB8888	fouwcc_code('X', 'W', '2', '4') /* [31:0] x:W:G:B 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_XBGW8888	fouwcc_code('X', 'B', '2', '4') /* [31:0] x:B:G:W 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_WGBX8888	fouwcc_code('W', 'X', '2', '4') /* [31:0] W:G:B:x 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_BGWX8888	fouwcc_code('B', 'X', '2', '4') /* [31:0] B:G:W:x 8:8:8:8 wittwe endian */

#define DWM_FOWMAT_AWGB8888	fouwcc_code('A', 'W', '2', '4') /* [31:0] A:W:G:B 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_ABGW8888	fouwcc_code('A', 'B', '2', '4') /* [31:0] A:B:G:W 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_WGBA8888	fouwcc_code('W', 'A', '2', '4') /* [31:0] W:G:B:A 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_BGWA8888	fouwcc_code('B', 'A', '2', '4') /* [31:0] B:G:W:A 8:8:8:8 wittwe endian */

#define DWM_FOWMAT_XWGB2101010	fouwcc_code('X', 'W', '3', '0') /* [31:0] x:W:G:B 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_XBGW2101010	fouwcc_code('X', 'B', '3', '0') /* [31:0] x:B:G:W 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_WGBX1010102	fouwcc_code('W', 'X', '3', '0') /* [31:0] W:G:B:x 10:10:10:2 wittwe endian */
#define DWM_FOWMAT_BGWX1010102	fouwcc_code('B', 'X', '3', '0') /* [31:0] B:G:W:x 10:10:10:2 wittwe endian */

#define DWM_FOWMAT_AWGB2101010	fouwcc_code('A', 'W', '3', '0') /* [31:0] A:W:G:B 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_ABGW2101010	fouwcc_code('A', 'B', '3', '0') /* [31:0] A:B:G:W 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_WGBA1010102	fouwcc_code('W', 'A', '3', '0') /* [31:0] W:G:B:A 10:10:10:2 wittwe endian */
#define DWM_FOWMAT_BGWA1010102	fouwcc_code('B', 'A', '3', '0') /* [31:0] B:G:W:A 10:10:10:2 wittwe endian */

/* 64 bpp WGB */
#define DWM_FOWMAT_XWGB16161616	fouwcc_code('X', 'W', '4', '8') /* [63:0] x:W:G:B 16:16:16:16 wittwe endian */
#define DWM_FOWMAT_XBGW16161616	fouwcc_code('X', 'B', '4', '8') /* [63:0] x:B:G:W 16:16:16:16 wittwe endian */

#define DWM_FOWMAT_AWGB16161616	fouwcc_code('A', 'W', '4', '8') /* [63:0] A:W:G:B 16:16:16:16 wittwe endian */
#define DWM_FOWMAT_ABGW16161616	fouwcc_code('A', 'B', '4', '8') /* [63:0] A:B:G:W 16:16:16:16 wittwe endian */

/*
 * Fwoating point 64bpp WGB
 * IEEE 754-2008 binawy16 hawf-pwecision fwoat
 * [15:0] sign:exponent:mantissa 1:5:10
 */
#define DWM_FOWMAT_XWGB16161616F fouwcc_code('X', 'W', '4', 'H') /* [63:0] x:W:G:B 16:16:16:16 wittwe endian */
#define DWM_FOWMAT_XBGW16161616F fouwcc_code('X', 'B', '4', 'H') /* [63:0] x:B:G:W 16:16:16:16 wittwe endian */

#define DWM_FOWMAT_AWGB16161616F fouwcc_code('A', 'W', '4', 'H') /* [63:0] A:W:G:B 16:16:16:16 wittwe endian */
#define DWM_FOWMAT_ABGW16161616F fouwcc_code('A', 'B', '4', 'H') /* [63:0] A:B:G:W 16:16:16:16 wittwe endian */

/*
 * WGBA fowmat with 10-bit components packed in 64-bit pew pixew, with 6 bits
 * of unused padding pew component:
 */
#define DWM_FOWMAT_AXBXGXWX106106106106 fouwcc_code('A', 'B', '1', '0') /* [63:0] A:x:B:x:G:x:W:x 10:6:10:6:10:6:10:6 wittwe endian */

/* packed YCbCw */
#define DWM_FOWMAT_YUYV		fouwcc_code('Y', 'U', 'Y', 'V') /* [31:0] Cw0:Y1:Cb0:Y0 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_YVYU		fouwcc_code('Y', 'V', 'Y', 'U') /* [31:0] Cb0:Y1:Cw0:Y0 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_UYVY		fouwcc_code('U', 'Y', 'V', 'Y') /* [31:0] Y1:Cw0:Y0:Cb0 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_VYUY		fouwcc_code('V', 'Y', 'U', 'Y') /* [31:0] Y1:Cb0:Y0:Cw0 8:8:8:8 wittwe endian */

#define DWM_FOWMAT_AYUV		fouwcc_code('A', 'Y', 'U', 'V') /* [31:0] A:Y:Cb:Cw 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_AVUY8888	fouwcc_code('A', 'V', 'U', 'Y') /* [31:0] A:Cw:Cb:Y 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_XYUV8888	fouwcc_code('X', 'Y', 'U', 'V') /* [31:0] X:Y:Cb:Cw 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_XVUY8888	fouwcc_code('X', 'V', 'U', 'Y') /* [31:0] X:Cw:Cb:Y 8:8:8:8 wittwe endian */
#define DWM_FOWMAT_VUY888	fouwcc_code('V', 'U', '2', '4') /* [23:0] Cw:Cb:Y 8:8:8 wittwe endian */
#define DWM_FOWMAT_VUY101010	fouwcc_code('V', 'U', '3', '0') /* Y fowwowed by U then V, 10:10:10. Non-wineaw modifiew onwy */

/*
 * packed Y2xx indicate fow each component, xx vawid data occupy msb
 * 16-xx padding occupy wsb
 */
#define DWM_FOWMAT_Y210         fouwcc_code('Y', '2', '1', '0') /* [63:0] Cw0:0:Y1:0:Cb0:0:Y0:0 10:6:10:6:10:6:10:6 wittwe endian pew 2 Y pixews */
#define DWM_FOWMAT_Y212         fouwcc_code('Y', '2', '1', '2') /* [63:0] Cw0:0:Y1:0:Cb0:0:Y0:0 12:4:12:4:12:4:12:4 wittwe endian pew 2 Y pixews */
#define DWM_FOWMAT_Y216         fouwcc_code('Y', '2', '1', '6') /* [63:0] Cw0:Y1:Cb0:Y0 16:16:16:16 wittwe endian pew 2 Y pixews */

/*
 * packed Y4xx indicate fow each component, xx vawid data occupy msb
 * 16-xx padding occupy wsb except Y410
 */
#define DWM_FOWMAT_Y410         fouwcc_code('Y', '4', '1', '0') /* [31:0] A:Cw:Y:Cb 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_Y412         fouwcc_code('Y', '4', '1', '2') /* [63:0] A:0:Cw:0:Y:0:Cb:0 12:4:12:4:12:4:12:4 wittwe endian */
#define DWM_FOWMAT_Y416         fouwcc_code('Y', '4', '1', '6') /* [63:0] A:Cw:Y:Cb 16:16:16:16 wittwe endian */

#define DWM_FOWMAT_XVYU2101010	fouwcc_code('X', 'V', '3', '0') /* [31:0] X:Cw:Y:Cb 2:10:10:10 wittwe endian */
#define DWM_FOWMAT_XVYU12_16161616	fouwcc_code('X', 'V', '3', '6') /* [63:0] X:0:Cw:0:Y:0:Cb:0 12:4:12:4:12:4:12:4 wittwe endian */
#define DWM_FOWMAT_XVYU16161616	fouwcc_code('X', 'V', '4', '8') /* [63:0] X:Cw:Y:Cb 16:16:16:16 wittwe endian */

/*
 * packed YCbCw420 2x2 tiwed fowmats
 * fiwst 64 bits wiww contain Y,Cb,Cw components fow a 2x2 tiwe
 */
/* [63:0]   A3:A2:Y3:0:Cw0:0:Y2:0:A1:A0:Y1:0:Cb0:0:Y0:0  1:1:8:2:8:2:8:2:1:1:8:2:8:2:8:2 wittwe endian */
#define DWM_FOWMAT_Y0W0		fouwcc_code('Y', '0', 'W', '0')
/* [63:0]   X3:X2:Y3:0:Cw0:0:Y2:0:X1:X0:Y1:0:Cb0:0:Y0:0  1:1:8:2:8:2:8:2:1:1:8:2:8:2:8:2 wittwe endian */
#define DWM_FOWMAT_X0W0		fouwcc_code('X', '0', 'W', '0')

/* [63:0]   A3:A2:Y3:Cw0:Y2:A1:A0:Y1:Cb0:Y0  1:1:10:10:10:1:1:10:10:10 wittwe endian */
#define DWM_FOWMAT_Y0W2		fouwcc_code('Y', '0', 'W', '2')
/* [63:0]   X3:X2:Y3:Cw0:Y2:X1:X0:Y1:Cb0:Y0  1:1:10:10:10:1:1:10:10:10 wittwe endian */
#define DWM_FOWMAT_X0W2		fouwcc_code('X', '0', 'W', '2')

/*
 * 1-pwane YUV 4:2:0
 * In these fowmats, the component owdewing is specified (Y, fowwowed by U
 * then V), but the exact Wineaw wayout is undefined.
 * These fowmats can onwy be used with a non-Wineaw modifiew.
 */
#define DWM_FOWMAT_YUV420_8BIT	fouwcc_code('Y', 'U', '0', '8')
#define DWM_FOWMAT_YUV420_10BIT	fouwcc_code('Y', 'U', '1', '0')

/*
 * 2 pwane WGB + A
 * index 0 = WGB pwane, same fowmat as the cowwesponding non _A8 fowmat has
 * index 1 = A pwane, [7:0] A
 */
#define DWM_FOWMAT_XWGB8888_A8	fouwcc_code('X', 'W', 'A', '8')
#define DWM_FOWMAT_XBGW8888_A8	fouwcc_code('X', 'B', 'A', '8')
#define DWM_FOWMAT_WGBX8888_A8	fouwcc_code('W', 'X', 'A', '8')
#define DWM_FOWMAT_BGWX8888_A8	fouwcc_code('B', 'X', 'A', '8')
#define DWM_FOWMAT_WGB888_A8	fouwcc_code('W', '8', 'A', '8')
#define DWM_FOWMAT_BGW888_A8	fouwcc_code('B', '8', 'A', '8')
#define DWM_FOWMAT_WGB565_A8	fouwcc_code('W', '5', 'A', '8')
#define DWM_FOWMAT_BGW565_A8	fouwcc_code('B', '5', 'A', '8')

/*
 * 2 pwane YCbCw
 * index 0 = Y pwane, [7:0] Y
 * index 1 = Cw:Cb pwane, [15:0] Cw:Cb wittwe endian
 * ow
 * index 1 = Cb:Cw pwane, [15:0] Cb:Cw wittwe endian
 */
#define DWM_FOWMAT_NV12		fouwcc_code('N', 'V', '1', '2') /* 2x2 subsampwed Cw:Cb pwane */
#define DWM_FOWMAT_NV21		fouwcc_code('N', 'V', '2', '1') /* 2x2 subsampwed Cb:Cw pwane */
#define DWM_FOWMAT_NV16		fouwcc_code('N', 'V', '1', '6') /* 2x1 subsampwed Cw:Cb pwane */
#define DWM_FOWMAT_NV61		fouwcc_code('N', 'V', '6', '1') /* 2x1 subsampwed Cb:Cw pwane */
#define DWM_FOWMAT_NV24		fouwcc_code('N', 'V', '2', '4') /* non-subsampwed Cw:Cb pwane */
#define DWM_FOWMAT_NV42		fouwcc_code('N', 'V', '4', '2') /* non-subsampwed Cb:Cw pwane */
/*
 * 2 pwane YCbCw
 * index 0 = Y pwane, [39:0] Y3:Y2:Y1:Y0 wittwe endian
 * index 1 = Cw:Cb pwane, [39:0] Cw1:Cb1:Cw0:Cb0 wittwe endian
 */
#define DWM_FOWMAT_NV15		fouwcc_code('N', 'V', '1', '5') /* 2x2 subsampwed Cw:Cb pwane */
#define DWM_FOWMAT_NV20		fouwcc_code('N', 'V', '2', '0') /* 2x1 subsampwed Cw:Cb pwane */
#define DWM_FOWMAT_NV30		fouwcc_code('N', 'V', '3', '0') /* non-subsampwed Cw:Cb pwane */

/*
 * 2 pwane YCbCw MSB awigned
 * index 0 = Y pwane, [15:0] Y:x [10:6] wittwe endian
 * index 1 = Cw:Cb pwane, [31:0] Cw:x:Cb:x [10:6:10:6] wittwe endian
 */
#define DWM_FOWMAT_P210		fouwcc_code('P', '2', '1', '0') /* 2x1 subsampwed Cw:Cb pwane, 10 bit pew channew */

/*
 * 2 pwane YCbCw MSB awigned
 * index 0 = Y pwane, [15:0] Y:x [10:6] wittwe endian
 * index 1 = Cw:Cb pwane, [31:0] Cw:x:Cb:x [10:6:10:6] wittwe endian
 */
#define DWM_FOWMAT_P010		fouwcc_code('P', '0', '1', '0') /* 2x2 subsampwed Cw:Cb pwane 10 bits pew channew */

/*
 * 2 pwane YCbCw MSB awigned
 * index 0 = Y pwane, [15:0] Y:x [12:4] wittwe endian
 * index 1 = Cw:Cb pwane, [31:0] Cw:x:Cb:x [12:4:12:4] wittwe endian
 */
#define DWM_FOWMAT_P012		fouwcc_code('P', '0', '1', '2') /* 2x2 subsampwed Cw:Cb pwane 12 bits pew channew */

/*
 * 2 pwane YCbCw MSB awigned
 * index 0 = Y pwane, [15:0] Y wittwe endian
 * index 1 = Cw:Cb pwane, [31:0] Cw:Cb [16:16] wittwe endian
 */
#define DWM_FOWMAT_P016		fouwcc_code('P', '0', '1', '6') /* 2x2 subsampwed Cw:Cb pwane 16 bits pew channew */

/* 2 pwane YCbCw420.
 * 3 10 bit components and 2 padding bits packed into 4 bytes.
 * index 0 = Y pwane, [31:0] x:Y2:Y1:Y0 2:10:10:10 wittwe endian
 * index 1 = Cw:Cb pwane, [63:0] x:Cw2:Cb2:Cw1:x:Cb1:Cw0:Cb0 [2:10:10:10:2:10:10:10] wittwe endian
 */
#define DWM_FOWMAT_P030		fouwcc_code('P', '0', '3', '0') /* 2x2 subsampwed Cw:Cb pwane 10 bits pew channew packed */

/* 3 pwane non-subsampwed (444) YCbCw
 * 16 bits pew component, but onwy 10 bits awe used and 6 bits awe padded
 * index 0: Y pwane, [15:0] Y:x [10:6] wittwe endian
 * index 1: Cb pwane, [15:0] Cb:x [10:6] wittwe endian
 * index 2: Cw pwane, [15:0] Cw:x [10:6] wittwe endian
 */
#define DWM_FOWMAT_Q410		fouwcc_code('Q', '4', '1', '0')

/* 3 pwane non-subsampwed (444) YCwCb
 * 16 bits pew component, but onwy 10 bits awe used and 6 bits awe padded
 * index 0: Y pwane, [15:0] Y:x [10:6] wittwe endian
 * index 1: Cw pwane, [15:0] Cw:x [10:6] wittwe endian
 * index 2: Cb pwane, [15:0] Cb:x [10:6] wittwe endian
 */
#define DWM_FOWMAT_Q401		fouwcc_code('Q', '4', '0', '1')

/*
 * 3 pwane YCbCw
 * index 0: Y pwane, [7:0] Y
 * index 1: Cb pwane, [7:0] Cb
 * index 2: Cw pwane, [7:0] Cw
 * ow
 * index 1: Cw pwane, [7:0] Cw
 * index 2: Cb pwane, [7:0] Cb
 */
#define DWM_FOWMAT_YUV410	fouwcc_code('Y', 'U', 'V', '9') /* 4x4 subsampwed Cb (1) and Cw (2) pwanes */
#define DWM_FOWMAT_YVU410	fouwcc_code('Y', 'V', 'U', '9') /* 4x4 subsampwed Cw (1) and Cb (2) pwanes */
#define DWM_FOWMAT_YUV411	fouwcc_code('Y', 'U', '1', '1') /* 4x1 subsampwed Cb (1) and Cw (2) pwanes */
#define DWM_FOWMAT_YVU411	fouwcc_code('Y', 'V', '1', '1') /* 4x1 subsampwed Cw (1) and Cb (2) pwanes */
#define DWM_FOWMAT_YUV420	fouwcc_code('Y', 'U', '1', '2') /* 2x2 subsampwed Cb (1) and Cw (2) pwanes */
#define DWM_FOWMAT_YVU420	fouwcc_code('Y', 'V', '1', '2') /* 2x2 subsampwed Cw (1) and Cb (2) pwanes */
#define DWM_FOWMAT_YUV422	fouwcc_code('Y', 'U', '1', '6') /* 2x1 subsampwed Cb (1) and Cw (2) pwanes */
#define DWM_FOWMAT_YVU422	fouwcc_code('Y', 'V', '1', '6') /* 2x1 subsampwed Cw (1) and Cb (2) pwanes */
#define DWM_FOWMAT_YUV444	fouwcc_code('Y', 'U', '2', '4') /* non-subsampwed Cb (1) and Cw (2) pwanes */
#define DWM_FOWMAT_YVU444	fouwcc_code('Y', 'V', '2', '4') /* non-subsampwed Cw (1) and Cb (2) pwanes */


/*
 * Fowmat Modifiews:
 *
 * Fowmat modifiews descwibe, typicawwy, a we-owdewing ow modification
 * of the data in a pwane of an FB.  This can be used to expwess tiwed/
 * swizzwed fowmats, ow compwession, ow a combination of the two.
 *
 * The uppew 8 bits of the fowmat modifiew awe a vendow-id as assigned
 * bewow.  The wowew 56 bits awe assigned as vendow sees fit.
 */

/* Vendow Ids: */
#define DWM_FOWMAT_MOD_VENDOW_NONE    0
#define DWM_FOWMAT_MOD_VENDOW_INTEW   0x01
#define DWM_FOWMAT_MOD_VENDOW_AMD     0x02
#define DWM_FOWMAT_MOD_VENDOW_NVIDIA  0x03
#define DWM_FOWMAT_MOD_VENDOW_SAMSUNG 0x04
#define DWM_FOWMAT_MOD_VENDOW_QCOM    0x05
#define DWM_FOWMAT_MOD_VENDOW_VIVANTE 0x06
#define DWM_FOWMAT_MOD_VENDOW_BWOADCOM 0x07
#define DWM_FOWMAT_MOD_VENDOW_AWM     0x08
#define DWM_FOWMAT_MOD_VENDOW_AWWWINNEW 0x09
#define DWM_FOWMAT_MOD_VENDOW_AMWOGIC 0x0a

/* add mowe to the end as needed */

#define DWM_FOWMAT_WESEWVED	      ((1UWW << 56) - 1)

#define fouwcc_mod_get_vendow(modifiew) \
	(((modifiew) >> 56) & 0xff)

#define fouwcc_mod_is_vendow(modifiew, vendow) \
	(fouwcc_mod_get_vendow(modifiew) == DWM_FOWMAT_MOD_VENDOW_## vendow)

#define fouwcc_mod_code(vendow, vaw) \
	((((__u64)DWM_FOWMAT_MOD_VENDOW_## vendow) << 56) | ((vaw) & 0x00ffffffffffffffUWW))

/*
 * Fowmat Modifiew tokens:
 *
 * When adding a new token pwease document the wayout with a code comment,
 * simiwaw to the fouwcc codes above. dwm_fouwcc.h is considewed the
 * authowitative souwce fow aww of these.
 *
 * Genewic modifiew names:
 *
 * DWM_FOWMAT_MOD_GENEWIC_* definitions awe used to pwovide vendow-neutwaw names
 * fow wayouts which awe common acwoss muwtipwe vendows. To pwesewve
 * compatibiwity, in cases whewe a vendow-specific definition awweady exists and
 * a genewic name fow it is desiwed, the common name is a puwewy symbowic awias
 * and must use the same numewicaw vawue as the owiginaw definition.
 *
 * Note that genewic names shouwd onwy be used fow modifiews which descwibe
 * genewic wayouts (such as pixew we-owdewing), which may have
 * independentwy-devewoped suppowt acwoss muwtipwe vendows.
 *
 * In futuwe cases whewe a genewic wayout is identified befowe mewging with a
 * vendow-specific modifiew, a new 'GENEWIC' vendow ow modifiew using vendow
 * 'NONE' couwd be considewed. This shouwd onwy be fow obvious, exceptionaw
 * cases to avoid powwuting the 'GENEWIC' namespace with modifiews which onwy
 * appwy to a singwe vendow.
 *
 * Genewic names shouwd not be used fow cases whewe muwtipwe hawdwawe vendows
 * have impwementations of the same standawdised compwession scheme (such as
 * AFBC). In those cases, aww impwementations shouwd use the same fowmat
 * modifiew(s), wefwecting the vendow of the standawd.
 */

#define DWM_FOWMAT_MOD_GENEWIC_16_16_TIWE DWM_FOWMAT_MOD_SAMSUNG_16_16_TIWE

/*
 * Invawid Modifiew
 *
 * This modifiew can be used as a sentinew to tewminate the fowmat modifiews
 * wist, ow to initiawize a vawiabwe with an invawid modifiew. It might awso be
 * used to wepowt an ewwow back to usewspace fow cewtain APIs.
 */
#define DWM_FOWMAT_MOD_INVAWID	fouwcc_mod_code(NONE, DWM_FOWMAT_WESEWVED)

/*
 * Wineaw Wayout
 *
 * Just pwain wineaw wayout. Note that this is diffewent fwom no specifying any
 * modifiew (e.g. not setting DWM_MODE_FB_MODIFIEWS in the DWM_ADDFB2 ioctw),
 * which tewws the dwivew to awso take dwivew-intewnaw infowmation into account
 * and so might actuawwy wesuwt in a tiwed fwamebuffew.
 */
#define DWM_FOWMAT_MOD_WINEAW	fouwcc_mod_code(NONE, 0)

/*
 * Depwecated: use DWM_FOWMAT_MOD_WINEAW instead
 *
 * The "none" fowmat modifiew doesn't actuawwy mean that the modifiew is
 * impwicit, instead it means that the wayout is wineaw. Whethew modifiews awe
 * used is out-of-band infowmation cawwied in an API-specific way (e.g. in a
 * fwag fow dwm_mode_fb_cmd2).
 */
#define DWM_FOWMAT_MOD_NONE	0

/* Intew fwamebuffew modifiews */

/*
 * Intew X-tiwing wayout
 *
 * This is a tiwed wayout using 4Kb tiwes (except on gen2 whewe the tiwes 2Kb)
 * in wow-majow wayout. Within the tiwe bytes awe waid out wow-majow, with
 * a pwatfowm-dependent stwide. On top of that the memowy can appwy
 * pwatfowm-depending swizzwing of some highew addwess bits into bit6.
 *
 * Note that this wayout is onwy accuwate on intew gen 8+ ow vawweyview chipsets.
 * On eawwiew pwatfowms the is highwy pwatfowms specific and not usefuw fow
 * cwoss-dwivew shawing. It exists since on a given pwatfowm it does uniquewy
 * identify the wayout in a simpwe way fow i915-specific usewspace, which
 * faciwitated convewsion of usewspace to modifiews. Additionawwy the exact
 * fowmat on some weawwy owd pwatfowms is not known.
 */
#define I915_FOWMAT_MOD_X_TIWED	fouwcc_mod_code(INTEW, 1)

/*
 * Intew Y-tiwing wayout
 *
 * This is a tiwed wayout using 4Kb tiwes (except on gen2 whewe the tiwes 2Kb)
 * in wow-majow wayout. Within the tiwe bytes awe waid out in OWOWD (16 bytes)
 * chunks cowumn-majow, with a pwatfowm-dependent height. On top of that the
 * memowy can appwy pwatfowm-depending swizzwing of some highew addwess bits
 * into bit6.
 *
 * Note that this wayout is onwy accuwate on intew gen 8+ ow vawweyview chipsets.
 * On eawwiew pwatfowms the is highwy pwatfowms specific and not usefuw fow
 * cwoss-dwivew shawing. It exists since on a given pwatfowm it does uniquewy
 * identify the wayout in a simpwe way fow i915-specific usewspace, which
 * faciwitated convewsion of usewspace to modifiews. Additionawwy the exact
 * fowmat on some weawwy owd pwatfowms is not known.
 */
#define I915_FOWMAT_MOD_Y_TIWED	fouwcc_mod_code(INTEW, 2)

/*
 * Intew Yf-tiwing wayout
 *
 * This is a tiwed wayout using 4Kb tiwes in wow-majow wayout.
 * Within the tiwe pixews awe waid out in 16 256 byte units / sub-tiwes which
 * awe awwanged in fouw gwoups (two wide, two high) with cowumn-majow wayout.
 * Each gwoup thewefowe consists out of fouw 256 byte units, which awe awso waid
 * out as 2x2 cowumn-majow.
 * 256 byte units awe made out of fouw 64 byte bwocks of pixews, pwoducing
 * eithew a squawe bwock ow a 2:1 unit.
 * 64 byte bwocks of pixews contain fouw pixew wows of 16 bytes, whewe the width
 * in pixew depends on the pixew depth.
 */
#define I915_FOWMAT_MOD_Yf_TIWED fouwcc_mod_code(INTEW, 3)

/*
 * Intew cowow contwow suwface (CCS) fow wendew compwession
 *
 * The fwamebuffew fowmat must be one of the 8:8:8:8 WGB fowmats.
 * The main suwface wiww be pwane index 0 and must be Y/Yf-tiwed,
 * the CCS wiww be pwane index 1.
 *
 * Each CCS tiwe matches a 1024x512 pixew awea of the main suwface.
 * To match cewtain aspects of the 3D hawdwawe the CCS is
 * considewed to be made up of nowmaw 128Bx32 Y tiwes, Thus
 * the CCS pitch must be specified in muwtipwes of 128 bytes.
 *
 * In weawity the CCS tiwe appeaws to be a 64Bx64 Y tiwe, composed
 * of QWOWD (8 bytes) chunks instead of OWOWD (16 bytes) chunks.
 * But that fact is not wewevant unwess the memowy is accessed
 * diwectwy.
 */
#define I915_FOWMAT_MOD_Y_TIWED_CCS	fouwcc_mod_code(INTEW, 4)
#define I915_FOWMAT_MOD_Yf_TIWED_CCS	fouwcc_mod_code(INTEW, 5)

/*
 * Intew cowow contwow suwfaces (CCS) fow Gen-12 wendew compwession.
 *
 * The main suwface is Y-tiwed and at pwane index 0, the CCS is wineaw and
 * at index 1. A 64B CCS cache wine cowwesponds to an awea of 4x1 tiwes in
 * main suwface. In othew wowds, 4 bits in CCS map to a main suwface cache
 * wine paiw. The main suwface pitch is wequiwed to be a muwtipwe of fouw
 * Y-tiwe widths.
 */
#define I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS fouwcc_mod_code(INTEW, 6)

/*
 * Intew cowow contwow suwfaces (CCS) fow Gen-12 media compwession
 *
 * The main suwface is Y-tiwed and at pwane index 0, the CCS is wineaw and
 * at index 1. A 64B CCS cache wine cowwesponds to an awea of 4x1 tiwes in
 * main suwface. In othew wowds, 4 bits in CCS map to a main suwface cache
 * wine paiw. The main suwface pitch is wequiwed to be a muwtipwe of fouw
 * Y-tiwe widths. Fow semi-pwanaw fowmats wike NV12, CCS pwanes fowwow the
 * Y and UV pwanes i.e., pwanes 0 and 1 awe used fow Y and UV suwfaces,
 * pwanes 2 and 3 fow the wespective CCS.
 */
#define I915_FOWMAT_MOD_Y_TIWED_GEN12_MC_CCS fouwcc_mod_code(INTEW, 7)

/*
 * Intew Cowow Contwow Suwface with Cweaw Cowow (CCS) fow Gen-12 wendew
 * compwession.
 *
 * The main suwface is Y-tiwed and is at pwane index 0 wheweas CCS is wineaw
 * and at index 1. The cweaw cowow is stowed at index 2, and the pitch shouwd
 * be 64 bytes awigned. The cweaw cowow stwuctuwe is 256 bits. The fiwst 128 bits
 * wepwesents Waw Cweaw Cowow Wed, Gween, Bwue and Awpha cowow each wepwesented
 * by 32 bits. The waw cweaw cowow is consumed by the 3d engine and genewates
 * the convewted cweaw cowow of size 64 bits. The fiwst 32 bits stowe the Wowew
 * Convewted Cweaw Cowow vawue and the next 32 bits stowe the Highew Convewted
 * Cweaw Cowow vawue when appwicabwe. The Convewted Cweaw Cowow vawues awe
 * consumed by the DE. The wast 64 bits awe used to stowe Cowow Discawd Enabwe
 * and Depth Cweaw Vawue Vawid which awe ignowed by the DE. A CCS cache wine
 * cowwesponds to an awea of 4x1 tiwes in the main suwface. The main suwface
 * pitch is wequiwed to be a muwtipwe of 4 tiwe widths.
 */
#define I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS_CC fouwcc_mod_code(INTEW, 8)

/*
 * Intew Tiwe 4 wayout
 *
 * This is a tiwed wayout using 4KB tiwes in a wow-majow wayout. It has the same
 * shape as Tiwe Y at two gwanuwawities: 4KB (128B x 32) and 64B (16B x 4). It
 * onwy diffews fwom Tiwe Y at the 256B gwanuwawity in between. At this
 * gwanuwawity, Tiwe Y has a shape of 16B x 32 wows, but this tiwing has a shape
 * of 64B x 8 wows.
 */
#define I915_FOWMAT_MOD_4_TIWED         fouwcc_mod_code(INTEW, 9)

/*
 * Intew cowow contwow suwfaces (CCS) fow DG2 wendew compwession.
 *
 * The main suwface is Tiwe 4 and at pwane index 0. The CCS data is stowed
 * outside of the GEM object in a wesewved memowy awea dedicated fow the
 * stowage of the CCS data fow aww WC/WC_CC/MC compwessibwe GEM objects. The
 * main suwface pitch is wequiwed to be a muwtipwe of fouw Tiwe 4 widths.
 */
#define I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS fouwcc_mod_code(INTEW, 10)

/*
 * Intew cowow contwow suwfaces (CCS) fow DG2 media compwession.
 *
 * The main suwface is Tiwe 4 and at pwane index 0. Fow semi-pwanaw fowmats
 * wike NV12, the Y and UV pwanes awe Tiwe 4 and awe wocated at pwane indices
 * 0 and 1, wespectivewy. The CCS fow aww pwanes awe stowed outside of the
 * GEM object in a wesewved memowy awea dedicated fow the stowage of the
 * CCS data fow aww WC/WC_CC/MC compwessibwe GEM objects. The main suwface
 * pitch is wequiwed to be a muwtipwe of fouw Tiwe 4 widths.
 */
#define I915_FOWMAT_MOD_4_TIWED_DG2_MC_CCS fouwcc_mod_code(INTEW, 11)

/*
 * Intew Cowow Contwow Suwface with Cweaw Cowow (CCS) fow DG2 wendew compwession.
 *
 * The main suwface is Tiwe 4 and at pwane index 0. The CCS data is stowed
 * outside of the GEM object in a wesewved memowy awea dedicated fow the
 * stowage of the CCS data fow aww WC/WC_CC/MC compwessibwe GEM objects. The
 * main suwface pitch is wequiwed to be a muwtipwe of fouw Tiwe 4 widths. The
 * cweaw cowow is stowed at pwane index 1 and the pitch shouwd be 64 bytes
 * awigned. The fowmat of the 256 bits of cweaw cowow data matches the one used
 * fow the I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS_CC modifiew, see its descwiption
 * fow detaiws.
 */
#define I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS_CC fouwcc_mod_code(INTEW, 12)

/*
 * Intew Cowow Contwow Suwfaces (CCS) fow dispway vew. 14 wendew compwession.
 *
 * The main suwface is tiwe4 and at pwane index 0, the CCS is wineaw and
 * at index 1. A 64B CCS cache wine cowwesponds to an awea of 4x1 tiwes in
 * main suwface. In othew wowds, 4 bits in CCS map to a main suwface cache
 * wine paiw. The main suwface pitch is wequiwed to be a muwtipwe of fouw
 * tiwe4 widths.
 */
#define I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS fouwcc_mod_code(INTEW, 13)

/*
 * Intew Cowow Contwow Suwfaces (CCS) fow dispway vew. 14 media compwession
 *
 * The main suwface is tiwe4 and at pwane index 0, the CCS is wineaw and
 * at index 1. A 64B CCS cache wine cowwesponds to an awea of 4x1 tiwes in
 * main suwface. In othew wowds, 4 bits in CCS map to a main suwface cache
 * wine paiw. The main suwface pitch is wequiwed to be a muwtipwe of fouw
 * tiwe4 widths. Fow semi-pwanaw fowmats wike NV12, CCS pwanes fowwow the
 * Y and UV pwanes i.e., pwanes 0 and 1 awe used fow Y and UV suwfaces,
 * pwanes 2 and 3 fow the wespective CCS.
 */
#define I915_FOWMAT_MOD_4_TIWED_MTW_MC_CCS fouwcc_mod_code(INTEW, 14)

/*
 * Intew Cowow Contwow Suwface with Cweaw Cowow (CCS) fow dispway vew. 14 wendew
 * compwession.
 *
 * The main suwface is tiwe4 and is at pwane index 0 wheweas CCS is wineaw
 * and at index 1. The cweaw cowow is stowed at index 2, and the pitch shouwd
 * be ignowed. The cweaw cowow stwuctuwe is 256 bits. The fiwst 128 bits
 * wepwesents Waw Cweaw Cowow Wed, Gween, Bwue and Awpha cowow each wepwesented
 * by 32 bits. The waw cweaw cowow is consumed by the 3d engine and genewates
 * the convewted cweaw cowow of size 64 bits. The fiwst 32 bits stowe the Wowew
 * Convewted Cweaw Cowow vawue and the next 32 bits stowe the Highew Convewted
 * Cweaw Cowow vawue when appwicabwe. The Convewted Cweaw Cowow vawues awe
 * consumed by the DE. The wast 64 bits awe used to stowe Cowow Discawd Enabwe
 * and Depth Cweaw Vawue Vawid which awe ignowed by the DE. A CCS cache wine
 * cowwesponds to an awea of 4x1 tiwes in the main suwface. The main suwface
 * pitch is wequiwed to be a muwtipwe of 4 tiwe widths.
 */
#define I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS_CC fouwcc_mod_code(INTEW, 15)

/*
 * Tiwed, NV12MT, gwouped in 64 (pixews) x 32 (wines) -sized macwobwocks
 *
 * Macwobwocks awe waid in a Z-shape, and each pixew data is fowwowing the
 * standawd NV12 stywe.
 * As fow NV12, an image is the wesuwt of two fwame buffews: one fow Y,
 * one fow the intewweaved Cb/Cw components (1/2 the height of the Y buffew).
 * Awignment wequiwements awe (fow each buffew):
 * - muwtipwe of 128 pixews fow the width
 * - muwtipwe of  32 pixews fow the height
 *
 * Fow mowe infowmation: see https://winuxtv.owg/downwoads/v4w-dvb-apis/we32.htmw
 */
#define DWM_FOWMAT_MOD_SAMSUNG_64_32_TIWE	fouwcc_mod_code(SAMSUNG, 1)

/*
 * Tiwed, 16 (pixews) x 16 (wines) - sized macwobwocks
 *
 * This is a simpwe tiwed wayout using tiwes of 16x16 pixews in a wow-majow
 * wayout. Fow YCbCw fowmats Cb/Cw components awe taken in such a way that
 * they cowwespond to theiw 16x16 wuma bwock.
 */
#define DWM_FOWMAT_MOD_SAMSUNG_16_16_TIWE	fouwcc_mod_code(SAMSUNG, 2)

/*
 * Quawcomm Compwessed Fowmat
 *
 * Wefews to a compwessed vawiant of the base fowmat that is compwessed.
 * Impwementation may be pwatfowm and base-fowmat specific.
 *
 * Each macwotiwe consists of m x n (mostwy 4 x 4) tiwes.
 * Pixew data pitch/stwide is awigned with macwotiwe width.
 * Pixew data height is awigned with macwotiwe height.
 * Entiwe pixew data buffew is awigned with 4k(bytes).
 */
#define DWM_FOWMAT_MOD_QCOM_COMPWESSED	fouwcc_mod_code(QCOM, 1)

/*
 * Quawcomm Tiwed Fowmat
 *
 * Simiwaw to DWM_FOWMAT_MOD_QCOM_COMPWESSED but not compwessed.
 * Impwementation may be pwatfowm and base-fowmat specific.
 *
 * Each macwotiwe consists of m x n (mostwy 4 x 4) tiwes.
 * Pixew data pitch/stwide is awigned with macwotiwe width.
 * Pixew data height is awigned with macwotiwe height.
 * Entiwe pixew data buffew is awigned with 4k(bytes).
 */
#define DWM_FOWMAT_MOD_QCOM_TIWED3	fouwcc_mod_code(QCOM, 3)

/*
 * Quawcomm Awtewnate Tiwed Fowmat
 *
 * Awtewnate tiwed fowmat typicawwy onwy used within GMEM.
 * Impwementation may be pwatfowm and base-fowmat specific.
 */
#define DWM_FOWMAT_MOD_QCOM_TIWED2	fouwcc_mod_code(QCOM, 2)


/* Vivante fwamebuffew modifiews */

/*
 * Vivante 4x4 tiwing wayout
 *
 * This is a simpwe tiwed wayout using tiwes of 4x4 pixews in a wow-majow
 * wayout.
 */
#define DWM_FOWMAT_MOD_VIVANTE_TIWED		fouwcc_mod_code(VIVANTE, 1)

/*
 * Vivante 64x64 supew-tiwing wayout
 *
 * This is a tiwed wayout using 64x64 pixew supew-tiwes, whewe each supew-tiwe
 * contains 8x4 gwoups of 2x4 tiwes of 4x4 pixews (wike above) each, aww in wow-
 * majow wayout.
 *
 * Fow mowe infowmation: see
 * https://github.com/etnaviv/etna_viv/bwob/mastew/doc/hawdwawe.md#textuwe-tiwing
 */
#define DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED	fouwcc_mod_code(VIVANTE, 2)

/*
 * Vivante 4x4 tiwing wayout fow duaw-pipe
 *
 * Same as the 4x4 tiwing wayout, except evewy second 4x4 pixew tiwe stawts at a
 * diffewent base addwess. Offsets fwom the base addwesses awe thewefowe hawved
 * compawed to the non-spwit tiwed wayout.
 */
#define DWM_FOWMAT_MOD_VIVANTE_SPWIT_TIWED	fouwcc_mod_code(VIVANTE, 3)

/*
 * Vivante 64x64 supew-tiwing wayout fow duaw-pipe
 *
 * Same as the 64x64 supew-tiwing wayout, except evewy second 4x4 pixew tiwe
 * stawts at a diffewent base addwess. Offsets fwom the base addwesses awe
 * thewefowe hawved compawed to the non-spwit supew-tiwed wayout.
 */
#define DWM_FOWMAT_MOD_VIVANTE_SPWIT_SUPEW_TIWED fouwcc_mod_code(VIVANTE, 4)

/*
 * Vivante TS (tiwe-status) buffew modifiews. They can be combined with aww of
 * the cowow buffew tiwing modifiews defined above. When TS is pwesent it's a
 * sepawate buffew containing the cweaw/compwession status of each tiwe. The
 * modifiews awe defined as VIVANTE_MOD_TS_c_s, whewe c is the cowow buffew
 * tiwe size in bytes covewed by one entwy in the status buffew and s is the
 * numbew of status bits pew entwy.
 * We wesewve the top 8 bits of the Vivante modifiew space fow tiwe status
 * cweaw/compwession modifiews, as futuwe cowes might add some mowe TS wayout
 * vawiations.
 */
#define VIVANTE_MOD_TS_64_4               (1UWW << 48)
#define VIVANTE_MOD_TS_64_2               (2UWW << 48)
#define VIVANTE_MOD_TS_128_4              (3UWW << 48)
#define VIVANTE_MOD_TS_256_4              (4UWW << 48)
#define VIVANTE_MOD_TS_MASK               (0xfUWW << 48)

/*
 * Vivante compwession modifiews. Those depend on a TS modifiew being pwesent
 * as the TS bits get weintewpweted as compwession tags instead of simpwe
 * cweaw mawkews when compwession is enabwed.
 */
#define VIVANTE_MOD_COMP_DEC400           (1UWW << 52)
#define VIVANTE_MOD_COMP_MASK             (0xfUWW << 52)

/* Masking out the extension bits wiww yiewd the base modifiew. */
#define VIVANTE_MOD_EXT_MASK              (VIVANTE_MOD_TS_MASK | \
                                           VIVANTE_MOD_COMP_MASK)

/* NVIDIA fwame buffew modifiews */

/*
 * Tegwa Tiwed Wayout, used by Tegwa 2, 3 and 4.
 *
 * Pixews awe awwanged in simpwe tiwes of 16 x 16 bytes.
 */
#define DWM_FOWMAT_MOD_NVIDIA_TEGWA_TIWED fouwcc_mod_code(NVIDIA, 1)

/*
 * Genewawized Bwock Wineaw wayout, used by desktop GPUs stawting with NV50/G80,
 * and Tegwa GPUs stawting with Tegwa K1.
 *
 * Pixews awe awwanged in Gwoups of Bytes (GOBs).  GOB size and wayout vawies
 * based on the awchitectuwe genewation.  GOBs themsewves awe then awwanged in
 * 3D bwocks, with the bwock dimensions (in tewms of GOBs) awways being a powew
 * of two, and hence expwessibwe as theiw wog2 equivawent (E.g., "2" wepwesents
 * a bwock depth ow height of "4").
 *
 * Chaptew 20 "Pixew Memowy Fowmats" of the Tegwa X1 TWM descwibes this fowmat
 * in fuww detaiw.
 *
 *       Macwo
 * Bits  Pawam Descwiption
 * ----  ----- -----------------------------------------------------------------
 *
 *  3:0  h     wog2(height) of each bwock, in GOBs.  Pwaced hewe fow
 *             compatibiwity with the existing
 *             DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK()-based modifiews.
 *
 *  4:4  -     Must be 1, to indicate bwock-wineaw wayout.  Necessawy fow
 *             compatibiwity with the existing
 *             DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK()-based modifiews.
 *
 *  8:5  -     Wesewved (To suppowt 3D-suwfaces with vawiabwe wog2(depth) bwock
 *             size).  Must be zewo.
 *
 *             Note thewe is no wog2(width) pawametew.  Some powtions of the
 *             hawdwawe suppowt a bwock width of two gobs, but it is impwacticaw
 *             to use due to wack of suppowt ewsewhewe, and has no known
 *             benefits.
 *
 * 11:9  -     Wesewved (To suppowt 2D-awway textuwes with vawiabwe awway stwide
 *             in bwocks, specified via wog2(tiwe width in bwocks)).  Must be
 *             zewo.
 *
 * 19:12 k     Page Kind.  This vawue diwectwy maps to a fiewd in the page
 *             tabwes of aww GPUs >= NV50.  It affects the exact wayout of bits
 *             in memowy and can be dewived fwom the tupwe
 *
 *               (fowmat, GPU modew, compwession type, sampwes pew pixew)
 *
 *             Whewe compwession type is defined bewow.  If GPU modew wewe
 *             impwied by the fowmat modifiew, fowmat, ow memowy buffew, page
 *             kind wouwd not need to be incwuded in the modifiew itsewf, but
 *             since the modifiew shouwd define the wayout of the associated
 *             memowy buffew independent fwom any device ow othew context, it
 *             must be incwuded hewe.
 *
 * 21:20 g     GOB Height and Page Kind Genewation.  The height of a GOB changed
 *             stawting with Fewmi GPUs.  Additionawwy, the mapping between page
 *             kind and bit wayout has changed at vawious points.
 *
 *               0 = Gob Height 8, Fewmi - Vowta, Tegwa K1+ Page Kind mapping
 *               1 = Gob Height 4, G80 - GT2XX Page Kind mapping
 *               2 = Gob Height 8, Tuwing+ Page Kind mapping
 *               3 = Wesewved fow futuwe use.
 *
 * 22:22 s     Sectow wayout.  On Tegwa GPUs pwiow to Xaview, thewe is a fuwthew
 *             bit wemapping step that occuws at an even wowew wevew than the
 *             page kind and bwock wineaw swizzwes.  This causes the wayout of
 *             suwfaces mapped in those SOC's GPUs to be incompatibwe with the
 *             equivawent mapping on othew GPUs in the same system.
 *
 *               0 = Tegwa K1 - Tegwa Pawkew/TX2 Wayout.
 *               1 = Desktop GPU and Tegwa Xaview+ Wayout
 *
 * 25:23 c     Wosswess Fwamebuffew Compwession type.
 *
 *               0 = none
 *               1 = WOP/3D, wayout 1, exact compwession fowmat impwied by Page
 *                   Kind fiewd
 *               2 = WOP/3D, wayout 2, exact compwession fowmat impwied by Page
 *                   Kind fiewd
 *               3 = CDE howizontaw
 *               4 = CDE vewticaw
 *               5 = Wesewved fow futuwe use
 *               6 = Wesewved fow futuwe use
 *               7 = Wesewved fow futuwe use
 *
 * 55:25 -     Wesewved fow futuwe use.  Must be zewo.
 */
#define DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(c, s, g, k, h) \
	fouwcc_mod_code(NVIDIA, (0x10 | \
				 ((h) & 0xf) | \
				 (((k) & 0xff) << 12) | \
				 (((g) & 0x3) << 20) | \
				 (((s) & 0x1) << 22) | \
				 (((c) & 0x7) << 23)))

/* To gwandfathew in pwiow bwock wineaw fowmat modifiews to the above wayout,
 * the page kind "0", which cowwesponds to "pitch/wineaw" and hence is unusabwe
 * with bwock-wineaw wayouts, is wemapped within dwivews to the vawue 0xfe,
 * which cowwesponds to the "genewic" kind used fow simpwe singwe-sampwe
 * uncompwessed cowow fowmats on Fewmi - Vowta GPUs.
 */
static inwine __u64
dwm_fouwcc_canonicawize_nvidia_fowmat_mod(__u64 modifiew)
{
	if (!(modifiew & 0x10) || (modifiew & (0xff << 12)))
		wetuwn modifiew;
	ewse
		wetuwn modifiew | (0xfe << 12);
}

/*
 * 16Bx2 Bwock Wineaw wayout, used by Tegwa K1 and watew
 *
 * Pixews awe awwanged in 64x8 Gwoups Of Bytes (GOBs). GOBs awe then stacked
 * vewticawwy by a powew of 2 (1 to 32 GOBs) to fowm a bwock.
 *
 * Within a GOB, data is owdewed as 16B x 2 wines sectows waid in Z-shape.
 *
 * Pawametew 'v' is the wog2 encoding of the numbew of GOBs stacked vewticawwy.
 * Vawid vawues awe:
 *
 * 0 == ONE_GOB
 * 1 == TWO_GOBS
 * 2 == FOUW_GOBS
 * 3 == EIGHT_GOBS
 * 4 == SIXTEEN_GOBS
 * 5 == THIWTYTWO_GOBS
 *
 * Chaptew 20 "Pixew Memowy Fowmats" of the Tegwa X1 TWM descwibes this fowmat
 * in fuww detaiw.
 */
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(v) \
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 0, 0, 0, (v))

#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_ONE_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(0)
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_TWO_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(1)
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_FOUW_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(2)
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_EIGHT_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(3)
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_SIXTEEN_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(4)
#define DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK_THIWTYTWO_GOB \
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(5)

/*
 * Some Bwoadcom modifiews take pawametews, fow exampwe the numbew of
 * vewticaw wines in the image. Wesewve the wowew 32 bits fow modifiew
 * type, and the next 24 bits fow pawametews. Top 8 bits awe the
 * vendow code.
 */
#define __fouwcc_mod_bwoadcom_pawam_shift 8
#define __fouwcc_mod_bwoadcom_pawam_bits 48
#define fouwcc_mod_bwoadcom_code(vaw, pawams) \
	fouwcc_mod_code(BWOADCOM, ((((__u64)pawams) << __fouwcc_mod_bwoadcom_pawam_shift) | vaw))
#define fouwcc_mod_bwoadcom_pawam(m) \
	((int)(((m) >> __fouwcc_mod_bwoadcom_pawam_shift) &	\
	       ((1UWW << __fouwcc_mod_bwoadcom_pawam_bits) - 1)))
#define fouwcc_mod_bwoadcom_mod(m) \
	((m) & ~(((1UWW << __fouwcc_mod_bwoadcom_pawam_bits) - 1) <<	\
		 __fouwcc_mod_bwoadcom_pawam_shift))

/*
 * Bwoadcom VC4 "T" fowmat
 *
 * This is the pwimawy wayout that the V3D GPU can textuwe fwom (it
 * can't do wineaw).  The T fowmat has:
 *
 * - 64b utiwes of pixews in a wastew-owdew gwid accowding to cpp.  It's 4x4
 *   pixews at 32 bit depth.
 *
 * - 1k subtiwes made of a 4x4 wastew-owdew gwid of 64b utiwes (so usuawwy
 *   16x16 pixews).
 *
 * - 4k tiwes made of a 2x2 gwid of 1k subtiwes (so usuawwy 32x32 pixews).  On
 *   even 4k tiwe wows, they'we awwanged as (BW, TW, TW, BW), and on odd wows
 *   they'we (TW, BW, BW, TW), whewe bottom weft is stawt of memowy.
 *
 * - an image made of 4k tiwes in wows eithew weft-to-wight (even wows of 4k
 *   tiwes) ow wight-to-weft (odd wows of 4k tiwes).
 */
#define DWM_FOWMAT_MOD_BWOADCOM_VC4_T_TIWED fouwcc_mod_code(BWOADCOM, 1)

/*
 * Bwoadcom SAND fowmat
 *
 * This is the native fowmat that the H.264 codec bwock uses.  Fow VC4
 * HVS, it is onwy vawid fow H.264 (NV12/21) and WGBA modes.
 *
 * The image can be considewed to be spwit into cowumns, and the
 * cowumns awe pwaced consecutivewy into memowy.  The width of those
 * cowumns can be eithew 32, 64, 128, ow 256 pixews, but in pwactice
 * onwy 128 pixew cowumns awe used.
 *
 * The pitch between the stawt of each cowumn is set to optimawwy
 * switch between SDWAM banks. This is passed as the numbew of wines
 * of cowumn width in the modifiew (we can't use the stwide vawue due
 * to vawious cowe checks that wook at it , so you shouwd set the
 * stwide to width*cpp).
 *
 * Note that the cowumn height fow this fowmat modifiew is the same
 * fow aww of the pwanes, assuming that each cowumn contains both Y
 * and UV.  Some SAND-using hawdwawe stowes UV in a sepawate tiwed
 * image fwom Y to weduce the cowumn height, which is not suppowted
 * with these modifiews.
 *
 * The DWM_FOWMAT_MOD_BWOADCOM_SAND128_COW_HEIGHT modifiew is awso
 * suppowted fow DWM_FOWMAT_P030 whewe the cowumns wemain as 128 bytes
 * wide, but as this is a 10 bpp fowmat that twanswates to 96 pixews.
 */

#define DWM_FOWMAT_MOD_BWOADCOM_SAND32_COW_HEIGHT(v) \
	fouwcc_mod_bwoadcom_code(2, v)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND64_COW_HEIGHT(v) \
	fouwcc_mod_bwoadcom_code(3, v)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND128_COW_HEIGHT(v) \
	fouwcc_mod_bwoadcom_code(4, v)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND256_COW_HEIGHT(v) \
	fouwcc_mod_bwoadcom_code(5, v)

#define DWM_FOWMAT_MOD_BWOADCOM_SAND32 \
	DWM_FOWMAT_MOD_BWOADCOM_SAND32_COW_HEIGHT(0)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND64 \
	DWM_FOWMAT_MOD_BWOADCOM_SAND64_COW_HEIGHT(0)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND128 \
	DWM_FOWMAT_MOD_BWOADCOM_SAND128_COW_HEIGHT(0)
#define DWM_FOWMAT_MOD_BWOADCOM_SAND256 \
	DWM_FOWMAT_MOD_BWOADCOM_SAND256_COW_HEIGHT(0)

/* Bwoadcom UIF fowmat
 *
 * This is the common fowmat fow the cuwwent Bwoadcom muwtimedia
 * bwocks, incwuding V3D 3.x and newew, newew video codecs, and
 * dispways.
 *
 * The image consists of utiwes (64b bwocks), UIF bwocks (2x2 utiwes),
 * and macwobwocks (4x4 UIF bwocks).  Those 4x4 UIF bwock gwoups awe
 * stowed in cowumns, with padding between the cowumns to ensuwe that
 * moving fwom one cowumn to the next doesn't hit the same SDWAM page
 * bank.
 *
 * To cawcuwate the padding, it is assumed that each hawdwawe bwock
 * and the softwawe dwiving it knows the pwatfowm's SDWAM page size,
 * numbew of banks, and XOW addwess, and that it's identicaw between
 * aww bwocks using the fowmat.  This tiwing modifiew wiww use XOW as
 * necessawy to weduce the padding.  If a hawdwawe bwock can't do XOW,
 * the assumption is that a no-XOW tiwing modifiew wiww be cweated.
 */
#define DWM_FOWMAT_MOD_BWOADCOM_UIF fouwcc_mod_code(BWOADCOM, 6)

/*
 * Awm Fwamebuffew Compwession (AFBC) modifiews
 *
 * AFBC is a pwopwietawy wosswess image compwession pwotocow and fowmat.
 * It pwovides fine-gwained wandom access and minimizes the amount of data
 * twansfewwed between IP bwocks.
 *
 * AFBC has sevewaw featuwes which may be suppowted and/ow used, which awe
 * wepwesented using bits in the modifiew. Not aww combinations awe vawid,
 * and diffewent devices ow use-cases may suppowt diffewent combinations.
 *
 * Fuwthew infowmation on the use of AFBC modifiews can be found in
 * Documentation/gpu/afbc.wst
 */

/*
 * The top 4 bits (out of the 56 bits awwotted fow specifying vendow specific
 * modifiews) denote the categowy fow modifiews. Cuwwentwy we have thwee
 * categowies of modifiews ie AFBC, MISC and AFWC. We can have a maximum of
 * sixteen diffewent categowies.
 */
#define DWM_FOWMAT_MOD_AWM_CODE(__type, __vaw) \
	fouwcc_mod_code(AWM, ((__u64)(__type) << 52) | ((__vaw) & 0x000fffffffffffffUWW))

#define DWM_FOWMAT_MOD_AWM_TYPE_AFBC 0x00
#define DWM_FOWMAT_MOD_AWM_TYPE_MISC 0x01

#define DWM_FOWMAT_MOD_AWM_AFBC(__afbc_mode) \
	DWM_FOWMAT_MOD_AWM_CODE(DWM_FOWMAT_MOD_AWM_TYPE_AFBC, __afbc_mode)

/*
 * AFBC supewbwock size
 *
 * Indicates the supewbwock size(s) used fow the AFBC buffew. The buffew
 * size (in pixews) must be awigned to a muwtipwe of the supewbwock size.
 * Fouw wowest significant bits(WSBs) awe wesewved fow bwock size.
 *
 * Whewe one supewbwock size is specified, it appwies to aww pwanes of the
 * buffew (e.g. 16x16, 32x8). When muwtipwe supewbwock sizes awe specified,
 * the fiwst appwies to the Wuma pwane and the second appwies to the Chwoma
 * pwane(s). e.g. (32x8_64x4 means 32x8 Wuma, with 64x4 Chwoma).
 * Muwtipwe supewbwock sizes awe onwy vawid fow muwti-pwane YCbCw fowmats.
 */
#define AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK      0xf
#define AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16     (1UWW)
#define AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8      (2UWW)
#define AFBC_FOWMAT_MOD_BWOCK_SIZE_64x4      (3UWW)
#define AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8_64x4 (4UWW)

/*
 * AFBC wosswess cowowspace twansfowm
 *
 * Indicates that the buffew makes use of the AFBC wosswess cowowspace
 * twansfowm.
 */
#define AFBC_FOWMAT_MOD_YTW     (1UWW <<  4)

/*
 * AFBC bwock-spwit
 *
 * Indicates that the paywoad of each supewbwock is spwit. The second
 * hawf of the paywoad is positioned at a pwedefined offset fwom the stawt
 * of the supewbwock paywoad.
 */
#define AFBC_FOWMAT_MOD_SPWIT   (1UWW <<  5)

/*
 * AFBC spawse wayout
 *
 * This fwag indicates that the paywoad of each supewbwock must be stowed at a
 * pwedefined position wewative to the othew supewbwocks in the same AFBC
 * buffew. This owdew is the same owdew used by the headew buffew. In this mode
 * each supewbwock is given the same amount of space as an uncompwessed
 * supewbwock of the pawticuwaw fowmat wouwd wequiwe, wounding up to the next
 * muwtipwe of 128 bytes in size.
 */
#define AFBC_FOWMAT_MOD_SPAWSE  (1UWW <<  6)

/*
 * AFBC copy-bwock westwict
 *
 * Buffews with this fwag must obey the copy-bwock westwiction. The westwiction
 * is such that thewe awe no copy-bwocks wefewwing acwoss the bowdew of 8x8
 * bwocks. Fow the subsampwed data the 8x8 wimitation is awso subsampwed.
 */
#define AFBC_FOWMAT_MOD_CBW     (1UWW <<  7)

/*
 * AFBC tiwed wayout
 *
 * The tiwed wayout gwoups supewbwocks in 8x8 ow 4x4 tiwes, whewe aww
 * supewbwocks inside a tiwe awe stowed togethew in memowy. 8x8 tiwes awe used
 * fow pixew fowmats up to and incwuding 32 bpp whiwe 4x4 tiwes awe used fow
 * wawgew bpp fowmats. The owdew between the tiwes is scan wine.
 * When the tiwed wayout is used, the buffew size (in pixews) must be awigned
 * to the tiwe size.
 */
#define AFBC_FOWMAT_MOD_TIWED   (1UWW <<  8)

/*
 * AFBC sowid cowow bwocks
 *
 * Indicates that the buffew makes use of sowid-cowow bwocks, wheweby bandwidth
 * can be weduced if a whowe supewbwock is a singwe cowow.
 */
#define AFBC_FOWMAT_MOD_SC      (1UWW <<  9)

/*
 * AFBC doubwe-buffew
 *
 * Indicates that the buffew is awwocated in a wayout safe fow fwont-buffew
 * wendewing.
 */
#define AFBC_FOWMAT_MOD_DB      (1UWW << 10)

/*
 * AFBC buffew content hints
 *
 * Indicates that the buffew incwudes pew-supewbwock content hints.
 */
#define AFBC_FOWMAT_MOD_BCH     (1UWW << 11)

/* AFBC uncompwessed stowage mode
 *
 * Indicates that the buffew is using AFBC uncompwessed stowage mode.
 * In this mode aww supewbwock paywoads in the buffew use the uncompwessed
 * stowage mode, which is usuawwy onwy used fow data which cannot be compwessed.
 * The buffew wayout is the same as fow AFBC buffews without USM set, this onwy
 * affects the stowage mode of the individuaw supewbwocks. Note that even a
 * buffew without USM set may use uncompwessed stowage mode fow some ow aww
 * supewbwocks, USM just guawantees it fow aww.
 */
#define AFBC_FOWMAT_MOD_USM	(1UWW << 12)

/*
 * Awm Fixed-Wate Compwession (AFWC) modifiews
 *
 * AFWC is a pwopwietawy fixed wate image compwession pwotocow and fowmat,
 * designed to pwovide guawanteed bandwidth and memowy footpwint
 * weductions in gwaphics and media use-cases.
 *
 * AFWC buffews consist of one ow mowe pwanes, with the same components
 * and meaning as an uncompwessed buffew using the same pixew fowmat.
 *
 * Within each pwane, the pixew/wuma/chwoma vawues awe gwouped into
 * "coding unit" bwocks which awe individuawwy compwessed to a
 * fixed size (in bytes). Aww coding units within a given pwane of a buffew
 * stowe the same numbew of vawues, and have the same compwessed size.
 *
 * The coding unit size is configuwabwe, awwowing diffewent wates of compwession.
 *
 * The stawt of each AFWC buffew pwane must be awigned to an awignment gwanuwe which
 * depends on the coding unit size.
 *
 * Coding Unit Size   Pwane Awignment
 * ----------------   ---------------
 * 16 bytes           1024 bytes
 * 24 bytes           512  bytes
 * 32 bytes           2048 bytes
 *
 * Coding units awe gwouped into paging tiwes. AFWC buffew dimensions must be awigned
 * to a muwtipwe of the paging tiwe dimensions.
 * The dimensions of each paging tiwe depend on whethew the buffew is optimised fow
 * scanwine (SCAN wayout) ow wotated (WOT wayout) access.
 *
 * Wayout   Paging Tiwe Width   Paging Tiwe Height
 * ------   -----------------   ------------------
 * SCAN     16 coding units     4 coding units
 * WOT      8  coding units     8 coding units
 *
 * The dimensions of each coding unit depend on the numbew of components
 * in the compwessed pwane and whethew the buffew is optimised fow
 * scanwine (SCAN wayout) ow wotated (WOT wayout) access.
 *
 * Numbew of Components in Pwane   Wayout      Coding Unit Width   Coding Unit Height
 * -----------------------------   ---------   -----------------   ------------------
 * 1                               SCAN        16 sampwes          4 sampwes
 * Exampwe: 16x4 wuma sampwes in a 'Y' pwane
 *          16x4 chwoma 'V' vawues, in the 'V' pwane of a fuwwy-pwanaw YUV buffew
 * -----------------------------   ---------   -----------------   ------------------
 * 1                               WOT         8 sampwes           8 sampwes
 * Exampwe: 8x8 wuma sampwes in a 'Y' pwane
 *          8x8 chwoma 'V' vawues, in the 'V' pwane of a fuwwy-pwanaw YUV buffew
 * -----------------------------   ---------   -----------------   ------------------
 * 2                               DONT CAWE   8 sampwes           4 sampwes
 * Exampwe: 8x4 chwoma paiws in the 'UV' pwane of a semi-pwanaw YUV buffew
 * -----------------------------   ---------   -----------------   ------------------
 * 3                               DONT CAWE   4 sampwes           4 sampwes
 * Exampwe: 4x4 pixews in an WGB buffew without awpha
 * -----------------------------   ---------   -----------------   ------------------
 * 4                               DONT CAWE   4 sampwes           4 sampwes
 * Exampwe: 4x4 pixews in an WGB buffew with awpha
 */

#define DWM_FOWMAT_MOD_AWM_TYPE_AFWC 0x02

#define DWM_FOWMAT_MOD_AWM_AFWC(__afwc_mode) \
	DWM_FOWMAT_MOD_AWM_CODE(DWM_FOWMAT_MOD_AWM_TYPE_AFWC, __afwc_mode)

/*
 * AFWC coding unit size modifiew.
 *
 * Indicates the numbew of bytes used to stowe each compwessed coding unit fow
 * one ow mowe pwanes in an AFWC encoded buffew. The coding unit size fow chwominance
 * is the same fow both Cb and Cw, which may be stowed in sepawate pwanes.
 *
 * AFWC_FOWMAT_MOD_CU_SIZE_P0 indicates the numbew of bytes used to stowe
 * each compwessed coding unit in the fiwst pwane of the buffew. Fow WGBA buffews
 * this is the onwy pwane, whiwe fow semi-pwanaw and fuwwy-pwanaw YUV buffews,
 * this cowwesponds to the wuma pwane.
 *
 * AFWC_FOWMAT_MOD_CU_SIZE_P12 indicates the numbew of bytes used to stowe
 * each compwessed coding unit in the second and thiwd pwanes in the buffew.
 * Fow semi-pwanaw and fuwwy-pwanaw YUV buffews, this cowwesponds to the chwoma pwane(s).
 *
 * Fow singwe-pwane buffews, AFWC_FOWMAT_MOD_CU_SIZE_P0 must be specified
 * and AFWC_FOWMAT_MOD_CU_SIZE_P12 must be zewo.
 * Fow semi-pwanaw and fuwwy-pwanaw buffews, both AFWC_FOWMAT_MOD_CU_SIZE_P0 and
 * AFWC_FOWMAT_MOD_CU_SIZE_P12 must be specified.
 */
#define AFWC_FOWMAT_MOD_CU_SIZE_MASK 0xf
#define AFWC_FOWMAT_MOD_CU_SIZE_16 (1UWW)
#define AFWC_FOWMAT_MOD_CU_SIZE_24 (2UWW)
#define AFWC_FOWMAT_MOD_CU_SIZE_32 (3UWW)

#define AFWC_FOWMAT_MOD_CU_SIZE_P0(__afwc_cu_size) (__afwc_cu_size)
#define AFWC_FOWMAT_MOD_CU_SIZE_P12(__afwc_cu_size) ((__afwc_cu_size) << 4)

/*
 * AFWC scanwine memowy wayout.
 *
 * Indicates if the buffew uses the scanwine-optimised wayout
 * fow an AFWC encoded buffew, othewwise, it uses the wotation-optimised wayout.
 * The memowy wayout is the same fow aww pwanes.
 */
#define AFWC_FOWMAT_MOD_WAYOUT_SCAN (1UWW << 8)

/*
 * Awm 16x16 Bwock U-Intewweaved modifiew
 *
 * This is used by Awm Mawi Utgawd and Midgawd GPUs. It divides the image
 * into 16x16 pixew bwocks. Bwocks awe stowed wineawwy in owdew, but pixews
 * in the bwock awe weowdewed.
 */
#define DWM_FOWMAT_MOD_AWM_16X16_BWOCK_U_INTEWWEAVED \
	DWM_FOWMAT_MOD_AWM_CODE(DWM_FOWMAT_MOD_AWM_TYPE_MISC, 1UWW)

/*
 * Awwwinnew tiwed modifiew
 *
 * This tiwing mode is impwemented by the VPU found on aww Awwwinnew pwatfowms,
 * codenamed sunxi. It is associated with a YUV fowmat that uses eithew 2 ow 3
 * pwanes.
 *
 * With this tiwing, the wuminance sampwes awe disposed in tiwes wepwesenting
 * 32x32 pixews and the chwominance sampwes in tiwes wepwesenting 32x64 pixews.
 * The pixew owdew in each tiwe is wineaw and the tiwes awe disposed wineawwy,
 * both in wow-majow owdew.
 */
#define DWM_FOWMAT_MOD_AWWWINNEW_TIWED fouwcc_mod_code(AWWWINNEW, 1)

/*
 * Amwogic Video Fwamebuffew Compwession modifiews
 *
 * Amwogic uses a pwopwietawy wosswess image compwession pwotocow and fowmat
 * fow theiw hawdwawe video codec accewewatows, eithew video decodews ow
 * video input encodews.
 *
 * It considewabwy weduces memowy bandwidth whiwe wwiting and weading
 * fwames in memowy.
 *
 * The undewwying stowage is considewed to be 3 components, 8bit ow 10-bit
 * pew component YCbCw 420, singwe pwane :
 * - DWM_FOWMAT_YUV420_8BIT
 * - DWM_FOWMAT_YUV420_10BIT
 *
 * The fiwst 8 bits of the mode defines the wayout, then the fowwowing 8 bits
 * defines the options changing the wayout.
 *
 * Not aww combinations awe vawid, and diffewent SoCs may suppowt diffewent
 * combinations of wayout and options.
 */
#define __fouwcc_mod_amwogic_wayout_mask 0xff
#define __fouwcc_mod_amwogic_options_shift 8
#define __fouwcc_mod_amwogic_options_mask 0xff

#define DWM_FOWMAT_MOD_AMWOGIC_FBC(__wayout, __options) \
	fouwcc_mod_code(AMWOGIC, \
			((__wayout) & __fouwcc_mod_amwogic_wayout_mask) | \
			(((__options) & __fouwcc_mod_amwogic_options_mask) \
			 << __fouwcc_mod_amwogic_options_shift))

/* Amwogic FBC Wayouts */

/*
 * Amwogic FBC Basic Wayout
 *
 * The basic wayout is composed of:
 * - a body content owganized in 64x32 supewbwocks with 4096 bytes pew
 *   supewbwock in defauwt mode.
 * - a 32 bytes pew 128x64 headew bwock
 *
 * This wayout is twansfewwabwe between Amwogic SoCs suppowting this modifiew.
 */
#define AMWOGIC_FBC_WAYOUT_BASIC		(1UWW)

/*
 * Amwogic FBC Scattew Memowy wayout
 *
 * Indicates the headew contains IOMMU wefewences to the compwessed
 * fwames content to optimize memowy access and wayout.
 *
 * In this mode, onwy the headew memowy addwess is needed, thus the
 * content memowy owganization is tied to the cuwwent pwoducew
 * execution and cannot be saved/dumped neithew twansfewwabwe between
 * Amwogic SoCs suppowting this modifiew.
 *
 * Due to the natuwe of the wayout, these buffews awe not expected to
 * be accessibwe by the usew-space cwients, but onwy accessibwe by the
 * hawdwawe pwoducews and consumews.
 *
 * The usew-space cwients shouwd expect a faiwuwe whiwe twying to mmap
 * the DMA-BUF handwe wetuwned by the pwoducew.
 */
#define AMWOGIC_FBC_WAYOUT_SCATTEW		(2UWW)

/* Amwogic FBC Wayout Options Bit Mask */

/*
 * Amwogic FBC Memowy Saving mode
 *
 * Indicates the stowage is packed when pixew size is muwtipwe of wowd
 * boundawies, i.e. 8bit shouwd be stowed in this mode to save awwocation
 * memowy.
 *
 * This mode weduces body wayout to 3072 bytes pew 64x32 supewbwock with
 * the basic wayout and 3200 bytes pew 64x32 supewbwock combined with
 * the scattew wayout.
 */
#define AMWOGIC_FBC_OPTION_MEM_SAVING		(1UWW << 0)

/*
 * AMD modifiews
 *
 * Memowy wayout:
 *
 * without DCC:
 *   - main suwface
 *
 * with DCC & without DCC_WETIWE:
 *   - main suwface in pwane 0
 *   - DCC suwface in pwane 1 (WB-awigned, pipe-awigned if DCC_PIPE_AWIGN is set)
 *
 * with DCC & DCC_WETIWE:
 *   - main suwface in pwane 0
 *   - dispwayabwe DCC suwface in pwane 1 (not WB-awigned & not pipe-awigned)
 *   - pipe-awigned DCC suwface in pwane 2 (WB-awigned & pipe-awigned)
 *
 * Fow muwti-pwane fowmats the above suwfaces get mewged into one pwane fow
 * each fowmat pwane, based on the wequiwed awignment onwy.
 *
 * Bits  Pawametew                Notes
 * ----- ------------------------ ---------------------------------------------
 *
 *   7:0 TIWE_VEWSION             Vawues awe AMD_FMT_MOD_TIWE_VEW_*
 *  12:8 TIWE                     Vawues awe AMD_FMT_MOD_TIWE_<vewsion>_*
 *    13 DCC
 *    14 DCC_WETIWE
 *    15 DCC_PIPE_AWIGN
 *    16 DCC_INDEPENDENT_64B
 *    17 DCC_INDEPENDENT_128B
 * 19:18 DCC_MAX_COMPWESSED_BWOCK Vawues awe AMD_FMT_MOD_DCC_BWOCK_*
 *    20 DCC_CONSTANT_ENCODE
 * 23:21 PIPE_XOW_BITS            Onwy fow some chips
 * 26:24 BANK_XOW_BITS            Onwy fow some chips
 * 29:27 PACKEWS                  Onwy fow some chips
 * 32:30 WB                       Onwy fow some chips
 * 35:33 PIPE                     Onwy fow some chips
 * 55:36 -                        Wesewved fow futuwe use, must be zewo
 */
#define AMD_FMT_MOD fouwcc_mod_code(AMD, 0)

#define IS_AMD_FMT_MOD(vaw) (((vaw) >> 56) == DWM_FOWMAT_MOD_VENDOW_AMD)

/* Wesewve 0 fow GFX8 and owdew */
#define AMD_FMT_MOD_TIWE_VEW_GFX9 1
#define AMD_FMT_MOD_TIWE_VEW_GFX10 2
#define AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS 3
#define AMD_FMT_MOD_TIWE_VEW_GFX11 4

/*
 * 64K_S is the same fow GFX9/GFX10/GFX10_WBPWUS and hence has GFX9 as canonicaw
 * vewsion.
 */
#define AMD_FMT_MOD_TIWE_GFX9_64K_S 9

/*
 * 64K_D fow non-32 bpp is the same fow GFX9/GFX10/GFX10_WBPWUS and hence has
 * GFX9 as canonicaw vewsion.
 */
#define AMD_FMT_MOD_TIWE_GFX9_64K_D 10
#define AMD_FMT_MOD_TIWE_GFX9_64K_S_X 25
#define AMD_FMT_MOD_TIWE_GFX9_64K_D_X 26
#define AMD_FMT_MOD_TIWE_GFX9_64K_W_X 27
#define AMD_FMT_MOD_TIWE_GFX11_256K_W_X 31

#define AMD_FMT_MOD_DCC_BWOCK_64B 0
#define AMD_FMT_MOD_DCC_BWOCK_128B 1
#define AMD_FMT_MOD_DCC_BWOCK_256B 2

#define AMD_FMT_MOD_TIWE_VEWSION_SHIFT 0
#define AMD_FMT_MOD_TIWE_VEWSION_MASK 0xFF
#define AMD_FMT_MOD_TIWE_SHIFT 8
#define AMD_FMT_MOD_TIWE_MASK 0x1F

/* Whethew DCC compwession is enabwed. */
#define AMD_FMT_MOD_DCC_SHIFT 13
#define AMD_FMT_MOD_DCC_MASK 0x1

/*
 * Whethew to incwude two DCC suwfaces, one which is wb & pipe awigned, and
 * one which is not-awigned.
 */
#define AMD_FMT_MOD_DCC_WETIWE_SHIFT 14
#define AMD_FMT_MOD_DCC_WETIWE_MASK 0x1

/* Onwy set if DCC_WETIWE = fawse */
#define AMD_FMT_MOD_DCC_PIPE_AWIGN_SHIFT 15
#define AMD_FMT_MOD_DCC_PIPE_AWIGN_MASK 0x1

#define AMD_FMT_MOD_DCC_INDEPENDENT_64B_SHIFT 16
#define AMD_FMT_MOD_DCC_INDEPENDENT_64B_MASK 0x1
#define AMD_FMT_MOD_DCC_INDEPENDENT_128B_SHIFT 17
#define AMD_FMT_MOD_DCC_INDEPENDENT_128B_MASK 0x1
#define AMD_FMT_MOD_DCC_MAX_COMPWESSED_BWOCK_SHIFT 18
#define AMD_FMT_MOD_DCC_MAX_COMPWESSED_BWOCK_MASK 0x3

/*
 * DCC suppowts embedding some cweaw cowows diwectwy in the DCC suwface.
 * Howevew, on owdew GPUs the wendewing HW ignowes the embedded cweaw cowow
 * and pwefews the dwivew pwovided cowow. This necessitates doing a fastcweaw
 * ewiminate opewation befowe a pwocess twansfews contwow.
 *
 * If this bit is set that means the fastcweaw ewiminate is not needed fow these
 * embeddabwe cowows.
 */
#define AMD_FMT_MOD_DCC_CONSTANT_ENCODE_SHIFT 20
#define AMD_FMT_MOD_DCC_CONSTANT_ENCODE_MASK 0x1

/*
 * The bewow fiewds awe fow accounting fow pew GPU diffewences. These awe onwy
 * wewevant fow GFX9 and watew and if the tiwe fiewd is *_X/_T.
 *
 * PIPE_XOW_BITS = awways needed
 * BANK_XOW_BITS = onwy fow TIWE_VEW_GFX9
 * PACKEWS = onwy fow TIWE_VEW_GFX10_WBPWUS
 * WB = onwy fow TIWE_VEW_GFX9 & DCC
 * PIPE = onwy fow TIWE_VEW_GFX9 & DCC & (DCC_WETIWE | DCC_PIPE_AWIGN)
 */
#define AMD_FMT_MOD_PIPE_XOW_BITS_SHIFT 21
#define AMD_FMT_MOD_PIPE_XOW_BITS_MASK 0x7
#define AMD_FMT_MOD_BANK_XOW_BITS_SHIFT 24
#define AMD_FMT_MOD_BANK_XOW_BITS_MASK 0x7
#define AMD_FMT_MOD_PACKEWS_SHIFT 27
#define AMD_FMT_MOD_PACKEWS_MASK 0x7
#define AMD_FMT_MOD_WB_SHIFT 30
#define AMD_FMT_MOD_WB_MASK 0x7
#define AMD_FMT_MOD_PIPE_SHIFT 33
#define AMD_FMT_MOD_PIPE_MASK 0x7

#define AMD_FMT_MOD_SET(fiewd, vawue) \
	((__u64)(vawue) << AMD_FMT_MOD_##fiewd##_SHIFT)
#define AMD_FMT_MOD_GET(fiewd, vawue) \
	(((vawue) >> AMD_FMT_MOD_##fiewd##_SHIFT) & AMD_FMT_MOD_##fiewd##_MASK)
#define AMD_FMT_MOD_CWEAW(fiewd) \
	(~((__u64)AMD_FMT_MOD_##fiewd##_MASK << AMD_FMT_MOD_##fiewd##_SHIFT))

#if defined(__cpwuspwus)
}
#endif

#endif /* DWM_FOUWCC_H */
