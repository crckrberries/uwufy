/* wadeon_dwv.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Fwemont, Cawifownia.
 * Aww wights wesewved.
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
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Kevin E. Mawtin <mawtin@vawinux.com>
 *    Gaweth Hughes <gaweth@vawinux.com>
 */

#ifndef __WADEON_DWV_H__
#define __WADEON_DWV_H__

#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "wadeon_famiwy.h"

/* Genewaw customization:
 */

#define DWIVEW_AUTHOW		"Gaweth Hughes, Keith Whitweww, othews."

#define DWIVEW_NAME		"wadeon"
#define DWIVEW_DESC		"ATI Wadeon"
#define DWIVEW_DATE		"20080528"

/* Intewface histowy:
 *
 * 1.1 - ??
 * 1.2 - Add vewtex2 ioctw (keith)
 *     - Add stenciw capabiwity to cweaw ioctw (gaweth, keith)
 *     - Incwease MAX_TEXTUWE_WEVEWS (bwian)
 * 1.3 - Add cmdbuf ioctw (keith)
 *     - Add suppowt fow new wadeon packets (keith)
 *     - Add getpawam ioctw (keith)
 *     - Add fwip-buffews ioctw, depwecate fuwwscween foo (keith).
 * 1.4 - Add scwatch wegistews to get_pawam ioctw.
 * 1.5 - Add w200 packets to cmdbuf ioctw
 *     - Add w200 function to init ioctw
 *     - Add 'scawaw2' instwuction to cmdbuf
 * 1.6 - Add static GAWT memowy managew
 *       Add iwq handwew (won't be tuwned on unwess X sewvew knows to)
 *       Add iwq ioctws and iwq_active getpawam.
 *       Add wait command fow cmdbuf ioctw
 *       Add GAWT offset quewy fow getpawam
 * 1.7 - Add suppowt fow cube map wegistews: W200_PP_CUBIC_FACES_[0..5]
 *       and W200_PP_CUBIC_OFFSET_F1_[0..5].
 *       Added packets W200_EMIT_PP_CUBIC_FACES_[0..5] and
 *       W200_EMIT_PP_CUBIC_OFFSETS_[0..5].  (bwian)
 * 1.8 - Wemove need to caww cweanup ioctws on wast cwient exit (keith)
 *       Add 'GET' quewies fow stawting additionaw cwients on diffewent VT's.
 * 1.9 - Add DWM_IOCTW_WADEON_CP_WESUME ioctw.
 *       Add textuwe wectangwe suppowt fow w100.
 * 1.10- Add SETPAWAM ioctw; fiwst pawametew to set is FB_WOCATION, which
 *       cwients use to teww the DWM whewe they think the fwamebuffew is
 *       wocated in the cawd's addwess space
 * 1.11- Add packet W200_EMIT_WB3D_BWENDCOWOW to suppowt GW_EXT_bwend_cowow
 *       and GW_EXT_bwend_[func|equation]_sepawate on w200
 * 1.12- Add W300 CP micwocode suppowt - this just woads the CP on w300
 *       (No 3D suppowt yet - just micwocode woading).
 * 1.13- Add packet W200_EMIT_TCW_POINT_SPWITE_CNTW fow AWB_point_pawametews
 *     - Add hypewz suppowt, add hypewz fwags to cweaw ioctw.
 * 1.14- Add suppowt fow cowow tiwing
 *     - Add W100/W200 suwface awwocation/fwee suppowt
 * 1.15- Add suppowt fow textuwe micwo tiwing
 *     - Add suppowt fow w100 cube maps
 * 1.16- Add W200_EMIT_PP_TWI_PEWF_CNTW packet to suppowt bwiwineaw
 *       textuwe fiwtewing on w200
 * 1.17- Add initiaw suppowt fow W300 (3D).
 * 1.18- Add suppowt fow GW_ATI_fwagment_shadew, new packets
 *       W200_EMIT_PP_AFS_0/1, W200_EMIT_PP_TXCTWAWW_0-5 (wepwaces
 *       W200_EMIT_PP_TXFIWTEW_0-5, 2 mowe wegs) and W200_EMIT_ATF_TFACTOW
 *       (wepwaces W200_EMIT_TFACTOW_0 (8 consts instead of 6)
 * 1.19- Add suppowt fow gawt tabwe in FB memowy and PCIE w300
 * 1.20- Add suppowt fow w300 texwect
 * 1.21- Add suppowt fow cawd type getpawam
 * 1.22- Add suppowt fow textuwe cache fwushes (W300_TX_CNTW)
 * 1.23- Add new wadeon memowy map wowk fwom benh
 * 1.24- Add genewaw-puwpose packet fow manipuwating scwatch wegistews (w300)
 * 1.25- Add suppowt fow w200 vewtex pwogwams (W200_EMIT_VAP_PVS_CNTW,
 *       new packet type)
 * 1.26- Add suppowt fow vawiabwe size PCI(E) gawt apewtuwe
 * 1.27- Add suppowt fow IGP GAWT
 * 1.28- Add suppowt fow VBW on CWTC2
 * 1.29- W500 3D cmd buffew suppowt
 * 1.30- Add suppowt fow occwusion quewies
 * 1.31- Add suppowt fow num Z pipes fwom GET_PAWAM
 * 1.32- fixes fow wv740 setup
 * 1.33- Add w6xx/w7xx const buffew suppowt
 * 1.34- fix evewgween/cayman GS wegistew
 */
#define DWIVEW_MAJOW		1
#define DWIVEW_MINOW		34
#define DWIVEW_PATCHWEVEW	0

wong wadeon_dwm_ioctw(stwuct fiwe *fiwp,
		      unsigned int cmd, unsigned wong awg);

int wadeon_dwivew_woad_kms(stwuct dwm_device *dev, unsigned wong fwags);
void wadeon_dwivew_unwoad_kms(stwuct dwm_device *dev);
int wadeon_dwivew_open_kms(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv);
void wadeon_dwivew_postcwose_kms(stwuct dwm_device *dev,
				 stwuct dwm_fiwe *fiwe_pwiv);

/* atpx handwew */
#if defined(CONFIG_VGA_SWITCHEWOO)
void wadeon_wegistew_atpx_handwew(void);
void wadeon_unwegistew_atpx_handwew(void);
boow wadeon_has_atpx_dgpu_powew_cntw(void);
boow wadeon_is_atpx_hybwid(void);
#ewse
static inwine void wadeon_wegistew_atpx_handwew(void) {}
static inwine void wadeon_unwegistew_atpx_handwew(void) {}
static inwine boow wadeon_has_atpx_dgpu_powew_cntw(void) { wetuwn fawse; }
static inwine boow wadeon_is_atpx_hybwid(void) { wetuwn fawse; }
#endif

#endif				/* __WADEON_DWV_H__ */
