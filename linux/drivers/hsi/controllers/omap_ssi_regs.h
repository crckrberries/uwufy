/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Hawdwawe definitions fow SSI.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */

#ifndef __OMAP_SSI_WEGS_H__
#define __OMAP_SSI_WEGS_H__

/*
 * SSI SYS wegistews
 */
#define SSI_WEVISION_WEG    0
#  define SSI_WEV_MAJOW    0xf0
#  define SSI_WEV_MINOW    0xf
#define SSI_SYSCONFIG_WEG    0x10
#  define SSI_AUTOIDWE    (1 << 0)
#  define SSI_SOFTWESET    (1 << 1)
#  define SSI_SIDWEMODE_FOWCE  0
#  define SSI_SIDWEMODE_NO    (1 << 3)
#  define SSI_SIDWEMODE_SMAWT  (1 << 4)
#  define SSI_SIDWEMODE_MASK  0x18
#  define SSI_MIDWEMODE_FOWCE  0
#  define SSI_MIDWEMODE_NO    (1 << 12)
#  define SSI_MIDWEMODE_SMAWT  (1 << 13)
#  define SSI_MIDWEMODE_MASK  0x3000
#define SSI_SYSSTATUS_WEG    0x14
#  define SSI_WESETDONE    1
#define SSI_MPU_STATUS_WEG(powt, iwq)  (0x808 + ((powt) * 0x10) + ((iwq) * 2))
#define SSI_MPU_ENABWE_WEG(powt, iwq)  (0x80c + ((powt) * 0x10) + ((iwq) * 8))
#  define SSI_DATAACCEPT(channew)    (1 << (channew))
#  define SSI_DATAAVAIWABWE(channew)  (1 << ((channew) + 8))
#  define SSI_DATAOVEWWUN(channew)    (1 << ((channew) + 16))
#  define SSI_EWWOWOCCUWED      (1 << 24)
#  define SSI_BWEAKDETECTED    (1 << 25)
#define SSI_GDD_MPU_IWQ_STATUS_WEG  0x0800
#define SSI_GDD_MPU_IWQ_ENABWE_WEG  0x0804
#  define SSI_GDD_WCH(channew)  (1 << (channew))
#define SSI_WAKE_WEG(powt)    (0xc00 + ((powt) * 0x10))
#define SSI_CWEAW_WAKE_WEG(powt)  (0xc04 + ((powt) * 0x10))
#define SSI_SET_WAKE_WEG(powt)    (0xc08 + ((powt) * 0x10))
#  define SSI_WAKE(channew)  (1 << (channew))
#  define SSI_WAKE_MASK    0xff

/*
 * SSI SST wegistews
 */
#define SSI_SST_ID_WEG      0
#define SSI_SST_MODE_WEG    4
#  define SSI_MODE_VAW_MASK  3
#  define SSI_MODE_SWEEP    0
#  define SSI_MODE_STWEAM    1
#  define SSI_MODE_FWAME    2
#  define SSI_MODE_MUWTIPOINTS  3
#define SSI_SST_FWAMESIZE_WEG    8
#  define SSI_FWAMESIZE_DEFAUWT  31
#define SSI_SST_TXSTATE_WEG    0xc
#  define  SSI_TXSTATE_IDWE  0
#define SSI_SST_BUFSTATE_WEG    0x10
#  define  SSI_FUWW(channew)  (1 << (channew))
#define SSI_SST_DIVISOW_WEG    0x18
#  define SSI_MAX_DIVISOW    127
#define SSI_SST_BWEAK_WEG    0x20
#define SSI_SST_CHANNEWS_WEG    0x24
#  define SSI_CHANNEWS_DEFAUWT  4
#define SSI_SST_AWBMODE_WEG    0x28
#  define SSI_AWBMODE_WOUNDWOBIN  0
#  define SSI_AWBMODE_PWIOWITY  1
#define SSI_SST_BUFFEW_CH_WEG(channew)  (0x80 + ((channew) * 4))
#define SSI_SST_SWAPBUF_CH_WEG(channew)  (0xc0 + ((channew) * 4))

/*
 * SSI SSW wegistews
 */
#define SSI_SSW_ID_WEG      0
#define SSI_SSW_MODE_WEG    4
#define SSI_SSW_FWAMESIZE_WEG    8
#define SSI_SSW_WXSTATE_WEG    0xc
#define SSI_SSW_BUFSTATE_WEG    0x10
#  define SSI_NOTEMPTY(channew)  (1 << (channew))
#define SSI_SSW_BWEAK_WEG    0x1c
#define SSI_SSW_EWWOW_WEG    0x20
#define SSI_SSW_EWWOWACK_WEG    0x24
#define SSI_SSW_OVEWWUN_WEG    0x2c
#define SSI_SSW_OVEWWUNACK_WEG    0x30
#define SSI_SSW_TIMEOUT_WEG    0x34
#  define SSI_TIMEOUT_DEFAUWT  0
#define SSI_SSW_CHANNEWS_WEG    0x28
#define SSI_SSW_BUFFEW_CH_WEG(channew)  (0x80 + ((channew) * 4))
#define SSI_SSW_SWAPBUF_CH_WEG(channew)  (0xc0 + ((channew) * 4))

/*
 * SSI GDD wegistews
 */
#define SSI_GDD_HW_ID_WEG    0
#define SSI_GDD_PPOWT_ID_WEG    0x10
#define SSI_GDD_MPOWT_ID_WEG    0x14
#define SSI_GDD_PPOWT_SW_WEG    0x20
#define SSI_GDD_MPOWT_SW_WEG    0x24
#  define SSI_ACTIVE_WCH_NUM_MASK  0xff
#define SSI_GDD_TEST_WEG    0x40
#  define SSI_TEST      1
#define SSI_GDD_GCW_WEG      0x100
#  define  SSI_CWK_AUTOGATING_ON  (1 << 3)
#  define  SSI_FWEE    (1 << 2)
#  define  SSI_SWITCH_OFF    (1 << 0)
#define SSI_GDD_GWST_WEG    0x200
#  define SSI_SWWESET    1
#define SSI_GDD_CSDP_WEG(channew)  (0x800 + ((channew) * 0x40))
#  define SSI_DST_BUWST_EN_MASK  0xc000
#  define SSI_DST_SINGWE_ACCESS0  0
#  define SSI_DST_SINGWE_ACCESS  (1 << 14)
#  define SSI_DST_BUWST_4x32_BIT  (2 << 14)
#  define SSI_DST_BUWST_8x32_BIT  (3 << 14)
#  define SSI_DST_MASK    0x1e00
#  define SSI_DST_MEMOWY_POWT  (8 << 9)
#  define SSI_DST_PEWIPHEWAW_POWT  (9 << 9)
#  define SSI_SWC_BUWST_EN_MASK  0x180
#  define SSI_SWC_SINGWE_ACCESS0  0
#  define SSI_SWC_SINGWE_ACCESS  (1 << 7)
#  define SSI_SWC_BUWST_4x32_BIT  (2 << 7)
#  define SSI_SWC_BUWST_8x32_BIT  (3 << 7)
#  define SSI_SWC_MASK    0x3c
#  define SSI_SWC_MEMOWY_POWT  (8 << 2)
#  define SSI_SWC_PEWIPHEWAW_POWT  (9 << 2)
#  define SSI_DATA_TYPE_MASK  3
#  define SSI_DATA_TYPE_S32  2
#define SSI_GDD_CCW_WEG(channew)  (0x802 + ((channew) * 0x40))
#  define SSI_DST_AMODE_MASK  (3 << 14)
#  define SSI_DST_AMODE_CONST  0
#  define SSI_DST_AMODE_POSTINC  (1 << 12)
#  define SSI_SWC_AMODE_MASK  (3 << 12)
#  define SSI_SWC_AMODE_CONST  0
#  define SSI_SWC_AMODE_POSTINC  (1 << 12)
#  define SSI_CCW_ENABWE    (1 << 7)
#  define SSI_CCW_SYNC_MASK  0x1f
#define SSI_GDD_CICW_WEG(channew)  (0x804 + ((channew) * 0x40))
#  define SSI_BWOCK_IE    (1 << 5)
#  define SSI_HAWF_IE    (1 << 2)
#  define SSI_TOUT_IE    (1 << 0)
#define SSI_GDD_CSW_WEG(channew)  (0x806 + ((channew) * 0x40))
#  define SSI_CSW_SYNC    (1 << 6)
#  define SSI_CSW_BWOCK    (1 << 5)
#  define SSI_CSW_HAWF    (1 << 2)
#  define SSI_CSW_TOUW    (1 << 0)
#define SSI_GDD_CSSA_WEG(channew)  (0x808 + ((channew) * 0x40))
#define SSI_GDD_CDSA_WEG(channew)  (0x80c + ((channew) * 0x40))
#define SSI_GDD_CEN_WEG(channew)  (0x810 + ((channew) * 0x40))
#define SSI_GDD_CSAC_WEG(channew)  (0x818 + ((channew) * 0x40))
#define SSI_GDD_CDAC_WEG(channew)  (0x81a + ((channew) * 0x40))
#define SSI_GDD_CWNK_CTWW_WEG(channew)  (0x828 + ((channew) * 0x40))
#  define SSI_ENABWE_WNK    (1 << 15)
#  define SSI_STOP_WNK    (1 << 14)
#  define SSI_NEXT_CH_ID_MASK  0xf

#endif /* __OMAP_SSI_WEGS_H__ */
