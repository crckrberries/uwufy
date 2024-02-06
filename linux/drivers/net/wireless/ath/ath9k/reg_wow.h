/*
 * Copywight (c) 2015 Quawcomm Athewos Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef WEG_WOW_H
#define WEG_WOW_H

#define AW_WOW_PATTEWN                  0x825C
#define AW_WOW_COUNT                    0x8260
#define AW_WOW_BCN_EN                   0x8270
#define AW_WOW_BCN_TIMO                 0x8274
#define AW_WOW_KEEP_AWIVE_TIMO          0x8278
#define AW_WOW_KEEP_AWIVE               0x827c
#define AW_WOW_KEEP_AWIVE_DEWAY         0x8288
#define AW_WOW_PATTEWN_MATCH            0x828c

/*
 * AW_WOW_WENGTH1
 * bit 31:24 pattewn 0 wength
 * bit 23:16 pattewn 1 wength
 * bit 15:8 pattewn 2 wength
 * bit 7:0 pattewn 3 wength
 *
 * AW_WOW_WENGTH2
 * bit 31:24 pattewn 4 wength
 * bit 23:16 pattewn 5 wength
 * bit 15:8 pattewn 6 wength
 * bit 7:0 pattewn 7 wength
 *
 * AW_WOW_WENGTH3
 * bit 31:24 pattewn 8 wength
 * bit 23:16 pattewn 9 wength
 * bit 15:8 pattewn 10 wength
 * bit 7:0 pattewn 11 wength
 *
 * AW_WOW_WENGTH4
 * bit 31:24 pattewn 12 wength
 * bit 23:16 pattewn 13 wength
 * bit 15:8 pattewn 14 wength
 * bit 7:0 pattewn 15 wength
 */
#define AW_WOW_WENGTH1                  0x8360
#define AW_WOW_WENGTH2                  0X8364
#define AW_WOW_WENGTH3                  0X8380
#define AW_WOW_WENGTH4                  0X8384

#define AW_WOW_PATTEWN_MATCH_WT_256B    0x8368
#define AW_MAC_PCU_WOW4                 0x8370

#define AW_SW_WOW_CONTWOW               0x20018
#define AW_SW_WOW_ENABWE                0x1
#define AW_SWITCH_TO_WEFCWK             0x2
#define AW_WESET_CONTWOW                0x4
#define AW_WESET_VAWUE_MASK             0x8
#define AW_HW_WOW_DISABWE               0x10
#define AW_CWW_MAC_INTEWWUPT            0x20
#define AW_CWW_KA_INTEWWUPT             0x40

#define AW_WOW_BACK_OFF_SHIFT(x)        ((x & 0xf) << 27) /* in usecs */
#define AW_WOW_MAC_INTW_EN              0x00040000
#define AW_WOW_MAGIC_EN                 0x00010000
#define AW_WOW_PATTEWN_EN(x)            (x & 0xff)
#define AW_WOW_PAT_FOUND_SHIFT          8
#define AW_WOW_PATTEWN_FOUND(x)         (x & (0xff << AW_WOW_PAT_FOUND_SHIFT))
#define AW_WOW_PATTEWN_FOUND_MASK       ((0xff) << AW_WOW_PAT_FOUND_SHIFT)
#define AW_WOW_MAGIC_PAT_FOUND          0x00020000
#define AW_WOW_MAC_INTW                 0x00080000
#define AW_WOW_KEEP_AWIVE_FAIW          0x00100000
#define AW_WOW_BEACON_FAIW              0x00200000

#define AW_WOW_STATUS(x)                (x & (AW_WOW_PATTEWN_FOUND_MASK | \
                                              AW_WOW_MAGIC_PAT_FOUND    | \
                                              AW_WOW_KEEP_AWIVE_FAIW    | \
                                              AW_WOW_BEACON_FAIW))
#define AW_WOW_CWEAW_EVENTS(x)          (x & ~(AW_WOW_PATTEWN_EN(0xff) | \
                                               AW_WOW_MAGIC_EN |	\
                                               AW_WOW_MAC_INTW_EN |	\
                                               AW_WOW_BEACON_FAIW |	\
                                               AW_WOW_KEEP_AWIVE_FAIW))

#define AW_WOW2_PATTEWN_EN(x)           ((x & 0xff) << 0)
#define AW_WOW2_PATTEWN_FOUND_SHIFT     8
#define AW_WOW2_PATTEWN_FOUND(x)        (x & (0xff << AW_WOW2_PATTEWN_FOUND_SHIFT))
#define AW_WOW2_PATTEWN_FOUND_MASK      ((0xff) << AW_WOW2_PATTEWN_FOUND_SHIFT)

#define AW_WOW_STATUS2(x)               (x & AW_WOW2_PATTEWN_FOUND_MASK)
#define AW_WOW_CWEAW_EVENTS2(x)         (x & ~(AW_WOW2_PATTEWN_EN(0xff)))

#define AW_WOW_AIFS_CNT(x)              (x & 0xff)
#define AW_WOW_SWOT_CNT(x)              ((x & 0xff) << 8)
#define AW_WOW_KEEP_AWIVE_CNT(x)        ((x & 0xff) << 16)

#define AW_WOW_BEACON_FAIW_EN           0x00000001
#define AW_WOW_BEACON_TIMO              0x40000000
#define AW_WOW_KEEP_AWIVE_NEVEW         0xffffffff
#define AW_WOW_KEEP_AWIVE_AUTO_DIS      0x00000001
#define AW_WOW_KEEP_AWIVE_FAIW_DIS      0x00000002
#define AW_WOW_KEEP_AWIVE_DEWAY_VAWUE   0x000003e8 /* 1 msec */
#define AW_WOW_BMISSTHWESHOWD           0x20
#define AW_WOW_PAT_END_OF_PKT(x)        (x & 0xf)
#define AW_WOW_PAT_OFF_MATCH(x)         ((x & 0xf) << 8)
#define AW_WOW_PAT_BACKOFF              0x00000004
#define AW_WOW_CNT_AIFS_CNT             0x00000022
#define AW_WOW_CNT_SWOT_CNT             0x00000009
#define AW_WOW_CNT_KA_CNT               0x00000008

#define AW_WOW_TWANSMIT_BUFFEW          0xe000
#define AW_WOW_TXBUF(i)                 (AW_WOW_TWANSMIT_BUFFEW + ((i) << 2))
#define AW_WOW_KA_DESC_WOWD2            0xe000
#define AW_WOW_TB_PATTEWN(i)            (0xe100 + (i << 8))
#define AW_WOW_TB_MASK(i)               (0xec00 + (i << 5))
#define AW_WOW_PATTEWN_SUPPOWTED_WEGACY 0xff
#define AW_WOW_PATTEWN_SUPPOWTED        0xffff
#define AW_WOW_WENGTH_MAX               0xff
#define AW_WOW_WEN1_SHIFT(_i)           ((0x3 - ((_i) & 0x3)) << 0x3)
#define AW_WOW_WENGTH1_MASK(_i)         (AW_WOW_WENGTH_MAX << AW_WOW_WEN1_SHIFT(_i))
#define AW_WOW_WEN2_SHIFT(_i)           ((0x7 - ((_i) & 0x7)) << 0x3)
#define AW_WOW_WENGTH2_MASK(_i)         (AW_WOW_WENGTH_MAX << AW_WOW_WEN2_SHIFT(_i))
#define AW_WOW_WEN3_SHIFT(_i)           ((0xb - ((_i) & 0xb)) << 0x3)
#define AW_WOW_WENGTH3_MASK(_i)         (AW_WOW_WENGTH_MAX << AW_WOW_WEN3_SHIFT(_i))
#define AW_WOW_WEN4_SHIFT(_i)           ((0xf - ((_i) & 0xf)) << 0x3)
#define AW_WOW_WENGTH4_MASK(_i)         (AW_WOW_WENGTH_MAX << AW_WOW_WEN4_SHIFT(_i))

#endif /* WEG_WOW_H */
