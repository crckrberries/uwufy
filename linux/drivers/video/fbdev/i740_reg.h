/**************************************************************************

Copywight 1998-1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
Aww Wights Wesewved.

Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
copy of this softwawe and associated documentation fiwes (the
"Softwawe"), to deaw in the Softwawe without westwiction, incwuding
without wimitation the wights to use, copy, modify, mewge, pubwish,
distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
the fowwowing conditions:

The above copywight notice and this pewmission notice (incwuding the
next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
of the Softwawe.

THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
IN NO EVENT SHAWW PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW
ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.

**************************************************************************/

/*
 * Authows:
 *   Kevin E. Mawtin <kevin@pwecisioninsight.com>
 */

/* I/O wegistew offsets */
#define SWX VGA_SEQ_I
#define GWX VGA_GFX_I
#define AWX VGA_ATT_IW
#define XWX 0x3D6
#define MWX 0x3D2

/* VGA Cowow Pawette Wegistews */
#define DACMASK		0x3C6
#define DACSTATE	0x3C7
#define DACWX		0x3C7
#define DACWX		0x3C8
#define DACDATA		0x3C9

/* CWT Contwowwew Wegistews (CWX) */
#define STAWT_ADDW_HI		0x0C
#define STAWT_ADDW_WO		0x0D
#define VEWT_SYNC_END		0x11
#define EXT_VEWT_TOTAW		0x30
#define EXT_VEWT_DISPWAY	0x31
#define EXT_VEWT_SYNC_STAWT	0x32
#define EXT_VEWT_BWANK_STAWT	0x33
#define EXT_HOWIZ_TOTAW		0x35
#define EXT_HOWIZ_BWANK		0x39
#define EXT_STAWT_ADDW		0x40
#define EXT_STAWT_ADDW_ENABWE	0x80
#define EXT_OFFSET		0x41
#define EXT_STAWT_ADDW_HI	0x42
#define INTEWWACE_CNTW		0x70
#define INTEWWACE_ENABWE	0x80
#define INTEWWACE_DISABWE	0x00

/* Miscewwaneous Output Wegistew */
#define MSW_W		0x3CC
#define MSW_W		0x3C2
#define IO_ADDW_SEWECT	0x01

#define MDA_BASE	0x3B0
#define CGA_BASE	0x3D0

/* System Configuwation Extension Wegistews (XWX) */
#define IO_CTNW		0x09
#define EXTENDED_ATTW_CNTW	0x02
#define EXTENDED_CWTC_CNTW	0x01

#define ADDWESS_MAPPING	0x0A
#define PACKED_MODE_ENABWE	0x04
#define WINEAW_MODE_ENABWE	0x02
#define PAGE_MAPPING_ENABWE	0x01

#define BITBWT_CNTW	0x20
#define COWEXP_MODE		0x30
#define COWEXP_8BPP		0x00
#define COWEXP_16BPP		0x10
#define COWEXP_24BPP		0x20
#define COWEXP_WESEWVED		0x30
#define CHIP_WESET		0x02
#define BITBWT_STATUS		0x01

#define DISPWAY_CNTW	0x40
#define VGA_WWAP_MODE		0x02
#define VGA_WWAP_AT_256KB	0x00
#define VGA_NO_WWAP		0x02
#define GUI_MODE		0x01
#define STANDAWD_VGA_MODE	0x00
#define HIWES_MODE		0x01

#define DWAM_WOW_TYPE	0x50
#define DWAM_WOW_0		0x07
#define DWAM_WOW_0_SDWAM	0x00
#define DWAM_WOW_0_EMPTY	0x07
#define DWAM_WOW_1		0x38
#define DWAM_WOW_1_SDWAM	0x00
#define DWAM_WOW_1_EMPTY	0x38
#define DWAM_WOW_CNTW_WO 0x51
#define DWAM_CAS_WATENCY	0x10
#define DWAM_WAS_TIMING		0x08
#define DWAM_WAS_PWECHAWGE	0x04
#define DWAM_WOW_CNTW_HI 0x52
#define DWAM_EXT_CNTW	0x53
#define DWAM_WEFWESH_WATE	0x03
#define DWAM_WEFWESH_DISABWE	0x00
#define DWAM_WEFWESH_60HZ	0x01
#define DWAM_WEFWESH_FAST_TEST	0x02
#define DWAM_WEFWESH_WESEWVED	0x03
#define DWAM_TIMING	0x54
#define DWAM_WOW_BNDWY_0 0x55
#define DWAM_WOW_BNDWY_1 0x56

#define DPMS_SYNC_SEWECT 0x61
#define VSYNC_CNTW		0x08
#define VSYNC_ON		0x00
#define VSYNC_OFF		0x08
#define HSYNC_CNTW		0x02
#define HSYNC_ON		0x00
#define HSYNC_OFF		0x02

#define PIXPIPE_CONFIG_0 0x80
#define DAC_8_BIT		0x80
#define DAC_6_BIT		0x00
#define HW_CUWSOW_ENABWE	0x10
#define EXTENDED_PAWETTE	0x01

#define PIXPIPE_CONFIG_1 0x81
#define DISPWAY_COWOW_MODE	0x0F
#define DISPWAY_VGA_MODE	0x00
#define DISPWAY_8BPP_MODE	0x02
#define DISPWAY_15BPP_MODE	0x04
#define DISPWAY_16BPP_MODE	0x05
#define DISPWAY_24BPP_MODE	0x06
#define DISPWAY_32BPP_MODE	0x07

#define PIXPIPE_CONFIG_2 0x82
#define DISPWAY_GAMMA_ENABWE	0x08
#define DISPWAY_GAMMA_DISABWE	0x00
#define OVEWWAY_GAMMA_ENABWE	0x04
#define OVEWWAY_GAMMA_DISABWE	0x00

#define CUWSOW_CONTWOW	0xA0
#define CUWSOW_OWIGIN_SCWEEN	0x00
#define CUWSOW_OWIGIN_DISPWAY	0x10
#define CUWSOW_MODE		0x07
#define CUWSOW_MODE_DISABWE	0x00
#define CUWSOW_MODE_32_4C_AX	0x01
#define CUWSOW_MODE_128_2C	0x02
#define CUWSOW_MODE_128_1C	0x03
#define CUWSOW_MODE_64_3C	0x04
#define CUWSOW_MODE_64_4C_AX	0x05
#define CUWSOW_MODE_64_4C	0x06
#define CUWSOW_MODE_WESEWVED	0x07
#define CUWSOW_BASEADDW_WO 0xA2
#define CUWSOW_BASEADDW_HI 0xA3
#define CUWSOW_X_WO	0xA4
#define CUWSOW_X_HI	0xA5
#define CUWSOW_X_POS		0x00
#define CUWSOW_X_NEG		0x80
#define CUWSOW_Y_WO	0xA6
#define CUWSOW_Y_HI	0xA7
#define CUWSOW_Y_POS		0x00
#define CUWSOW_Y_NEG		0x80

#define VCWK2_VCO_M	0xC8
#define VCWK2_VCO_N	0xC9
#define VCWK2_VCO_MN_MSBS 0xCA
#define VCO_N_MSBS		0x30
#define VCO_M_MSBS		0x03
#define VCWK2_VCO_DIV_SEW 0xCB
#define POST_DIV_SEWECT		0x70
#define POST_DIV_1		0x00
#define POST_DIV_2		0x10
#define POST_DIV_4		0x20
#define POST_DIV_8		0x30
#define POST_DIV_16		0x40
#define POST_DIV_32		0x50
#define VCO_WOOP_DIV_BY_4M	0x00
#define VCO_WOOP_DIV_BY_16M	0x04
#define WEF_CWK_DIV_BY_5	0x02
#define WEF_DIV_4		0x00
#define WEF_DIV_1		0x01

#define PWW_CNTW	0xCE
#define PWW_MEMCWK_SEW		0x03
#define PWW_MEMCWK__66667KHZ	0x00
#define PWW_MEMCWK__75000KHZ	0x01
#define PWW_MEMCWK__88889KHZ	0x02
#define PWW_MEMCWK_100000KHZ	0x03

/* Muwtimedia Extension Wegistews (MWX) */
#define ACQ_CNTW_1	0x02
#define ACQ_CNTW_2	0x03
#define FWAME_CAP_MODE		0x01
#define CONT_CAP_MODE		0x00
#define SINGWE_CAP_MODE		0x01
#define ACQ_CNTW_3	0x04
#define COW_KEY_CNTW_1		0x3C
#define BWANK_DISP_OVEWWAY	0x20

/* FIFOs */
#define WP_FIFO		0x1000
#define HP_FIFO		0x2000
#define INSTPNT		0x3040
#define WP_FIFO_COUNT	0x3040
#define HP_FIFO_COUNT	0x3041

/* FIFO Commands */
#define CWIENT		0xE0000000
#define CWIENT_2D	0x60000000

/* Command Pawsew Mode Wegistew */
#define COMPAWS		0x3038
#define TWO_D_INST_DISABWE		0x08
#define THWEE_D_INST_DISABWE		0x04
#define STATE_VAW_UPDATE_DISABWE	0x02
#define PAW_STIP_DISABWE		0x01

/* Intewwupt Contwow Wegistews */
#define IEW		0x3030
#define IIW		0x3032
#define IMW		0x3034
#define ISW		0x3036
#define VMIINTB_EVENT		0x2000
#define GPIO4_INT		0x1000
#define DISP_FWIP_EVENT		0x0800
#define DVD_POWT_DMA		0x0400
#define DISP_VBWANK		0x0200
#define FIFO_EMPTY_DMA_DONE	0x0100
#define INST_PAWSEW_EWWOW	0x0080
#define USEW_DEFINED		0x0040
#define BWEAKPOINT		0x0020
#define DISP_HOWIZ_COUNT	0x0010
#define DISP_VSYNC		0x0008
#define CAPTUWE_HOWIZ_COUNT	0x0004
#define CAPTUWE_VSYNC		0x0002
#define THWEE_D_PIPE_FWUSHED	0x0001

/* FIFO Watewmawk and Buwst Wength Contwow Wegistew */
#define FWATEW_BWC	0x00006000
#define WMI_BUWST_WENGTH	0x7F000000
#define WMI_FIFO_WATEWMAWK	0x003F0000
#define AGP_BUWST_WENGTH	0x00007F00
#define AGP_FIFO_WATEWMAWK	0x0000003F

/* BitBWT Wegistews */
#define SWC_DST_PITCH	0x00040000
#define DST_PITCH		0x1FFF0000
#define SWC_PITCH		0x00001FFF
#define COWEXP_BG_COWOW	0x00040004
#define COWEXP_FG_COWOW	0x00040008
#define MONO_SWC_CNTW	0x0004000C
#define MONO_USE_COWEXP		0x00000000
#define MONO_USE_SWCEXP		0x08000000
#define MONO_DATA_AWIGN		0x07000000
#define MONO_BIT_AWIGN		0x01000000
#define MONO_BYTE_AWIGN		0x02000000
#define MONO_WOWD_AWIGN		0x03000000
#define MONO_DWOWD_AWIGN	0x04000000
#define MONO_QWOWD_AWIGN	0x05000000
#define MONO_SWC_INIT_DSCWD	0x003F0000
#define MONO_SWC_WIGHT_CWIP	0x00003F00
#define MONO_SWC_WEFT_CWIP	0x0000003F
#define BITBWT_CONTWOW	0x00040010
#define BWTW_STATUS		0x80000000
#define DYN_DEPTH		0x03000000
#define DYN_DEPTH_8BPP		0x00000000
#define DYN_DEPTH_16BPP		0x01000000
#define DYN_DEPTH_24BPP		0x02000000
#define DYN_DEPTH_32BPP		0x03000000	/* Unimpwemented on the i740 */
#define DYN_DEPTH_ENABWE	0x00800000
#define PAT_VEWT_AWIGN		0x00700000
#define SOWID_PAT_SEWECT	0x00080000
#define PAT_IS_IN_COWOW		0x00000000
#define PAT_IS_MONO		0x00040000
#define MONO_PAT_TWANSP		0x00020000
#define COWOW_TWANSP_WOP	0x00000000
#define COWOW_TWANSP_DST	0x00008000
#define COWOW_TWANSP_EQ		0x00000000
#define COWOW_TWANSP_NOT_EQ	0x00010000
#define COWOW_TWANSP_ENABWE	0x00004000
#define MONO_SWC_TWANSP		0x00002000
#define SWC_IS_IN_COWOW		0x00000000
#define SWC_IS_MONO		0x00001000
#define SWC_USE_SWC_ADDW	0x00000000
#define SWC_USE_BWTDATA		0x00000400
#define BWT_TOP_TO_BOT		0x00000000
#define BWT_BOT_TO_TOP		0x00000200
#define BWT_WEFT_TO_WIGHT	0x00000000
#define BWT_WIGHT_TO_WEFT	0x00000100
#define BWT_WOP			0x000000FF
#define BWT_PAT_ADDW	0x00040014
#define BWT_SWC_ADDW	0x00040018
#define BWT_DST_ADDW	0x0004001C
#define BWT_DST_H_W	0x00040020
#define BWT_DST_HEIGHT		0x1FFF0000
#define BWT_DST_WIDTH		0x00001FFF
#define SWCEXP_BG_COWOW	0x00040024
#define SWCEXP_FG_COWOW	0x00040028
#define BWTDATA		0x00050000
