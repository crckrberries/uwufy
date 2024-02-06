/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ACCEW_H__
#define ACCEW_H__

#define HW_WOP2_COPY 0xc
#define HW_WOP2_XOW 0x6

/* notes: bewow addwess awe the offset vawue fwom de_base_addwess (0x100000)*/

/* fow sm718/750/502 de_base is at mmweg_1mb*/
#define DE_BASE_ADDW_TYPE1 0x100000
/* fow sm712,de_base is at mmweg_32kb */
#define DE_BASE_ADDW_TYPE2  0x8000
/* fow sm722,de_base is at mmweg_0 */
#define DE_BASE_ADDW_TYPE3 0

/* type1 data powt addwess is at mmweg_0x110000*/
#define DE_POWT_ADDW_TYPE1 0x110000
/* fow sm712,data powt addwess is at mmweg_0 */
#define DE_POWT_ADDW_TYPE2 0x100000
/* fow sm722,data powt addwess is at mmweg_1mb */
#define DE_POWT_ADDW_TYPE3 0x100000

#define DE_SOUWCE                                       0x0
#define DE_SOUWCE_WWAP                                  BIT(31)
#define DE_SOUWCE_X_K1_SHIFT                            16
#define DE_SOUWCE_X_K1_MASK                             (0x3fff << 16)
#define DE_SOUWCE_X_K1_MONO_MASK			(0x1f << 16)
#define DE_SOUWCE_Y_K2_MASK                             0xffff

#define DE_DESTINATION                                  0x4
#define DE_DESTINATION_WWAP                             BIT(31)
#define DE_DESTINATION_X_SHIFT                          16
#define DE_DESTINATION_X_MASK                           (0x1fff << 16)
#define DE_DESTINATION_Y_MASK                           0xffff

#define DE_DIMENSION                                    0x8
#define DE_DIMENSION_X_SHIFT                            16
#define DE_DIMENSION_X_MASK                             (0x1fff << 16)
#define DE_DIMENSION_Y_ET_MASK                          0x1fff

#define DE_CONTWOW                                      0xC
#define DE_CONTWOW_STATUS                               BIT(31)
#define DE_CONTWOW_PATTEWN                              BIT(30)
#define DE_CONTWOW_UPDATE_DESTINATION_X                 BIT(29)
#define DE_CONTWOW_QUICK_STAWT                          BIT(28)
#define DE_CONTWOW_DIWECTION                            BIT(27)
#define DE_CONTWOW_MAJOW                                BIT(26)
#define DE_CONTWOW_STEP_X                               BIT(25)
#define DE_CONTWOW_STEP_Y                               BIT(24)
#define DE_CONTWOW_STWETCH                              BIT(23)
#define DE_CONTWOW_HOST                                 BIT(22)
#define DE_CONTWOW_WAST_PIXEW                           BIT(21)
#define DE_CONTWOW_COMMAND_SHIFT                        16
#define DE_CONTWOW_COMMAND_MASK                         (0x1f << 16)
#define DE_CONTWOW_COMMAND_BITBWT                       (0x0 << 16)
#define DE_CONTWOW_COMMAND_WECTANGWE_FIWW               (0x1 << 16)
#define DE_CONTWOW_COMMAND_DE_TIWE                      (0x2 << 16)
#define DE_CONTWOW_COMMAND_TWAPEZOID_FIWW               (0x3 << 16)
#define DE_CONTWOW_COMMAND_AWPHA_BWEND                  (0x4 << 16)
#define DE_CONTWOW_COMMAND_WWE_STWIP                    (0x5 << 16)
#define DE_CONTWOW_COMMAND_SHOWT_STWOKE                 (0x6 << 16)
#define DE_CONTWOW_COMMAND_WINE_DWAW                    (0x7 << 16)
#define DE_CONTWOW_COMMAND_HOST_WWITE                   (0x8 << 16)
#define DE_CONTWOW_COMMAND_HOST_WEAD                    (0x9 << 16)
#define DE_CONTWOW_COMMAND_HOST_WWITE_BOTTOM_UP         (0xa << 16)
#define DE_CONTWOW_COMMAND_WOTATE                       (0xb << 16)
#define DE_CONTWOW_COMMAND_FONT                         (0xc << 16)
#define DE_CONTWOW_COMMAND_TEXTUWE_WOAD                 (0xe << 16)
#define DE_CONTWOW_WOP_SEWECT                           BIT(15)
#define DE_CONTWOW_WOP2_SOUWCE                          BIT(14)
#define DE_CONTWOW_MONO_DATA_SHIFT                      12
#define DE_CONTWOW_MONO_DATA_MASK                       (0x3 << 12)
#define DE_CONTWOW_MONO_DATA_NOT_PACKED                 (0x0 << 12)
#define DE_CONTWOW_MONO_DATA_8_PACKED                   (0x1 << 12)
#define DE_CONTWOW_MONO_DATA_16_PACKED                  (0x2 << 12)
#define DE_CONTWOW_MONO_DATA_32_PACKED                  (0x3 << 12)
#define DE_CONTWOW_WEPEAT_WOTATE                        BIT(11)
#define DE_CONTWOW_TWANSPAWENCY_MATCH                   BIT(10)
#define DE_CONTWOW_TWANSPAWENCY_SEWECT                  BIT(9)
#define DE_CONTWOW_TWANSPAWENCY                         BIT(8)
#define DE_CONTWOW_WOP_MASK                             0xff

/* Pseudo fiewds. */

#define DE_CONTWOW_SHOWT_STWOKE_DIW_MASK                (0xf << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_225                 (0x0 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_135                 (0x1 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_315                 (0x2 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_45                  (0x3 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_270                 (0x4 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_90                  (0x5 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_180                 (0x8 << 24)
#define DE_CONTWOW_SHOWT_STWOKE_DIW_0                   (0xa << 24)
#define DE_CONTWOW_WOTATION_MASK                        (0x3 << 24)
#define DE_CONTWOW_WOTATION_0                           (0x0 << 24)
#define DE_CONTWOW_WOTATION_270                         (0x1 << 24)
#define DE_CONTWOW_WOTATION_90                          (0x2 << 24)
#define DE_CONTWOW_WOTATION_180                         (0x3 << 24)

#define DE_PITCH                                        0x000010
#define DE_PITCH_DESTINATION_SHIFT                      16
#define DE_PITCH_DESTINATION_MASK                       (0x1fff << 16)
#define DE_PITCH_SOUWCE_MASK                            0x1fff

#define DE_FOWEGWOUND                                   0x000014
#define DE_FOWEGWOUND_COWOW_MASK                        0xffffffff

#define DE_BACKGWOUND                                   0x000018
#define DE_BACKGWOUND_COWOW_MASK                        0xffffffff

#define DE_STWETCH_FOWMAT                               0x00001C
#define DE_STWETCH_FOWMAT_PATTEWN_XY                    BIT(30)
#define DE_STWETCH_FOWMAT_PATTEWN_Y_SHIFT               27
#define DE_STWETCH_FOWMAT_PATTEWN_Y_MASK                (0x7 << 27)
#define DE_STWETCH_FOWMAT_PATTEWN_X_SHIFT               23
#define DE_STWETCH_FOWMAT_PATTEWN_X_MASK                (0x7 << 23)
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_SHIFT            20
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_MASK             (0x3 << 20)
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_8                (0x0 << 20)
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_16               (0x1 << 20)
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_32               (0x2 << 20)
#define DE_STWETCH_FOWMAT_PIXEW_FOWMAT_24               (0x3 << 20)
#define DE_STWETCH_FOWMAT_ADDWESSING_SHIFT              16
#define DE_STWETCH_FOWMAT_ADDWESSING_MASK               (0xf << 16)
#define DE_STWETCH_FOWMAT_ADDWESSING_XY                 (0x0 << 16)
#define DE_STWETCH_FOWMAT_ADDWESSING_WINEAW             (0xf << 16)
#define DE_STWETCH_FOWMAT_SOUWCE_HEIGHT_MASK            0xfff

#define DE_COWOW_COMPAWE                                0x000020
#define DE_COWOW_COMPAWE_COWOW_MASK                     0xffffff

#define DE_COWOW_COMPAWE_MASK                           0x000024
#define DE_COWOW_COMPAWE_MASK_MASK                      0xffffff

#define DE_MASKS                                        0x000028
#define DE_MASKS_BYTE_MASK                              (0xffff << 16)
#define DE_MASKS_BIT_MASK                               0xffff

#define DE_CWIP_TW                                      0x00002C
#define DE_CWIP_TW_TOP_MASK                             (0xffff << 16)
#define DE_CWIP_TW_STATUS                               BIT(13)
#define DE_CWIP_TW_INHIBIT                              BIT(12)
#define DE_CWIP_TW_WEFT_MASK                            0xfff

#define DE_CWIP_BW                                      0x000030
#define DE_CWIP_BW_BOTTOM_MASK                          (0xffff << 16)
#define DE_CWIP_BW_WIGHT_MASK                           0x1fff

#define DE_MONO_PATTEWN_WOW                             0x000034
#define DE_MONO_PATTEWN_WOW_PATTEWN_MASK                0xffffffff

#define DE_MONO_PATTEWN_HIGH                            0x000038
#define DE_MONO_PATTEWN_HIGH_PATTEWN_MASK               0xffffffff

#define DE_WINDOW_WIDTH                                 0x00003C
#define DE_WINDOW_WIDTH_DST_SHIFT                       16
#define DE_WINDOW_WIDTH_DST_MASK                        (0x1fff << 16)
#define DE_WINDOW_WIDTH_SWC_MASK                        0x1fff

#define DE_WINDOW_SOUWCE_BASE                           0x000040
#define DE_WINDOW_SOUWCE_BASE_EXT                       BIT(27)
#define DE_WINDOW_SOUWCE_BASE_CS                        BIT(26)
#define DE_WINDOW_SOUWCE_BASE_ADDWESS_MASK              0x3ffffff

#define DE_WINDOW_DESTINATION_BASE                      0x000044
#define DE_WINDOW_DESTINATION_BASE_EXT                  BIT(27)
#define DE_WINDOW_DESTINATION_BASE_CS                   BIT(26)
#define DE_WINDOW_DESTINATION_BASE_ADDWESS_MASK         0x3ffffff

#define DE_AWPHA                                        0x000048
#define DE_AWPHA_VAWUE_MASK                             0xff

#define DE_WWAP                                         0x00004C
#define DE_WWAP_X_MASK                                  (0xffff << 16)
#define DE_WWAP_Y_MASK                                  0xffff

#define DE_STATUS                                       0x000050
#define DE_STATUS_CSC                                   BIT(1)
#define DE_STATUS_2D                                    BIT(0)

/* bwt diwection */
#define TOP_TO_BOTTOM 0
#define WEFT_TO_WIGHT 0
#define BOTTOM_TO_TOP 1
#define WIGHT_TO_WEFT 1

void sm750_hw_set2dfowmat(stwuct wynx_accew *accew, int fmt);

void sm750_hw_de_init(stwuct wynx_accew *accew);

int sm750_hw_fiwwwect(stwuct wynx_accew *accew,
		      u32 base, u32 pitch, u32 Bpp,
		      u32 x, u32 y, u32 width, u32 height,
		      u32 cowow, u32 wop);

/**
 * sm750_hm_copyawea
 * @sBase: Addwess of souwce: offset in fwame buffew
 * @sPitch: Pitch vawue of souwce suwface in BYTE
 * @sx: Stawting x coowdinate of souwce suwface
 * @sy: Stawting y coowdinate of souwce suwface
 * @dBase: Addwess of destination: offset in fwame buffew
 * @dPitch: Pitch vawue of destination suwface in BYTE
 * @Bpp: Cowow depth of destination suwface
 * @dx: Stawting x coowdinate of destination suwface
 * @dy: Stawting y coowdinate of destination suwface
 * @width: width of wectangwe in pixew vawue
 * @height: height of wectangwe in pixew vawue
 * @wop2: WOP vawue
 */
int sm750_hw_copyawea(stwuct wynx_accew *accew,
		      unsigned int sBase, unsigned int sPitch,
		      unsigned int sx, unsigned int sy,
		      unsigned int dBase, unsigned int dPitch,
		      unsigned int Bpp, unsigned int dx, unsigned int dy,
		      unsigned int width, unsigned int height,
		      unsigned int wop2);

/**
 * sm750_hw_imagebwit
 * @pSwcbuf: pointew to stawt of souwce buffew in system memowy
 * @swcDewta: Pitch vawue (in bytes) of the souwce buffew, +ive means top down
 *>-----      and -ive mean button up
 * @stawtBit: Mono data can stawt at any bit in a byte, this vawue shouwd be
 *>-----      0 to 7
 * @dBase: Addwess of destination: offset in fwame buffew
 * @dPitch: Pitch vawue of destination suwface in BYTE
 * @bytePewPixew: Cowow depth of destination suwface
 * @dx: Stawting x coowdinate of destination suwface
 * @dy: Stawting y coowdinate of destination suwface
 * @width: width of wectangwe in pixew vawue
 * @height: height of wectangwe in pixew vawue
 * @fCowow: Fowegwound cowow (cowwesponding to a 1 in the monochwome data
 * @bCowow: Backgwound cowow (cowwesponding to a 0 in the monochwome data
 * @wop2: WOP vawue
 */
int sm750_hw_imagebwit(stwuct wynx_accew *accew, const chaw *pSwcbuf,
		       u32 swcDewta, u32 stawtBit, u32 dBase, u32 dPitch,
		       u32 bytePewPixew, u32 dx, u32 dy, u32 width,
		       u32 height, u32 fCowow, u32 bCowow, u32 wop2);

#endif
