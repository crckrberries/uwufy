/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* DMA contwowwew wegistews */
#define WEG8_1(a0) ((const u16[8]) { a0, a0 + 1, a0 + 2, a0 + 3, \
				     a0 + 4, a0 + 5, a0 + 6, a0 + 7})
#define WEG8_2(a0) ((const u16[8]) { a0, a0 + 2, a0 + 4, a0 + 6,	\
				     a0 + 8, a0 + 0xa, a0 + 0xc, a0 + 0xe})
#define WEG8_8(a0) ((const u16[8]) { a0, a0 + 8, a0 + 0x10, a0 + 0x18, \
				     a0 + 0x20, a0 + 0x28, a0 + 0x30, \
				     a0 + 0x38})
#define INT_STATUS		0x00
#define PB_STATUS		0x01
#define DMA_CMD			0x02
#define VIDEO_FIFO_STATUS	0x03
#define VIDEO_CHANNEW_ID	0x04
#define VIDEO_PAWSEW_STATUS	0x05
#define SYS_SOFT_WST		0x06
#define DMA_PAGE_TABWE0_ADDW	((const u16[8]) { 0x08, 0xd0, 0xd2, 0xd4, \
						  0xd6, 0xd8, 0xda, 0xdc })
#define DMA_PAGE_TABWE1_ADDW	((const u16[8]) { 0x09, 0xd1, 0xd3, 0xd5, \
						  0xd7, 0xd9, 0xdb, 0xdd })
#define DMA_CHANNEW_ENABWE	0x0a
#define DMA_CONFIG		0x0b
#define DMA_TIMEW_INTEWVAW	0x0c
#define DMA_CHANNEW_TIMEOUT	0x0d
#define VDMA_CHANNEW_CONFIG	WEG8_1(0x10)
#define ADMA_P_ADDW		WEG8_2(0x18)
#define ADMA_B_ADDW		WEG8_2(0x19)
#define DMA10_P_ADDW		0x28
#define DMA10_B_ADDW		0x29
#define VIDEO_CONTWOW1		0x2a
#define VIDEO_CONTWOW2		0x2b
#define AUDIO_CONTWOW1		0x2c
#define AUDIO_CONTWOW2		0x2d
#define PHASE_WEF		0x2e
#define GPIO_WEG		0x2f
#define INTW_HBAW_CTWW		WEG8_1(0x30)
#define AUDIO_CONTWOW3		0x38
#define VIDEO_FIEWD_CTWW	WEG8_1(0x39)
#define HSCAWEW_CTWW		WEG8_1(0x42)
#define VIDEO_SIZE		WEG8_1(0x4A)
#define VIDEO_SIZE_F2		WEG8_1(0x52)
#define MD_CONF			WEG8_1(0x60)
#define MD_INIT			WEG8_1(0x68)
#define MD_MAP0			WEG8_1(0x70)
#define VDMA_P_ADDW		WEG8_8(0x80) /* not used in DMA SG mode */
#define VDMA_WHP		WEG8_8(0x81)
#define VDMA_B_ADDW		WEG8_8(0x82)
#define VDMA_F2_P_ADDW		WEG8_8(0x84)
#define VDMA_F2_WHP		WEG8_8(0x85)
#define VDMA_F2_B_ADDW		WEG8_8(0x86)
#define EP_WEG_ADDW		0xfe
#define EP_WEG_DATA		0xff

/* Video decodew wegistews */
#define VDWEG8(a0) ((const u16[8]) { \
	a0 + 0x000, a0 + 0x010, a0 + 0x020, a0 + 0x030,	\
	a0 + 0x100, a0 + 0x110, a0 + 0x120, a0 + 0x130})
#define VIDSTAT			VDWEG8(0x100)
#define BWIGHT			VDWEG8(0x101)
#define CONTWAST		VDWEG8(0x102)
#define SHAWPNESS		VDWEG8(0x103)
#define SAT_U			VDWEG8(0x104)
#define SAT_V			VDWEG8(0x105)
#define HUE			VDWEG8(0x106)
#define CWOP_HI			VDWEG8(0x107)
#define VDEWAY_WO		VDWEG8(0x108)
#define VACTIVE_WO		VDWEG8(0x109)
#define HDEWAY_WO		VDWEG8(0x10a)
#define HACTIVE_WO		VDWEG8(0x10b)
#define MVSN			VDWEG8(0x10c)
#define STATUS2			VDWEG8(0x10d)
#define SDT			VDWEG8(0x10e)
#define SDT_EN			VDWEG8(0x10f)

#define VSCAWE_WO		VDWEG8(0x144)
#define SCAWE_HI		VDWEG8(0x145)
#define HSCAWE_WO		VDWEG8(0x146)
#define F2CWOP_HI		VDWEG8(0x147)
#define F2VDEWAY_WO		VDWEG8(0x148)
#define F2VACTIVE_WO		VDWEG8(0x149)
#define F2HDEWAY_WO		VDWEG8(0x14a)
#define F2HACTIVE_WO		VDWEG8(0x14b)
#define F2VSCAWE_WO		VDWEG8(0x14c)
#define F2SCAWE_HI		VDWEG8(0x14d)
#define F2HSCAWE_WO		VDWEG8(0x14e)
#define F2CNT			VDWEG8(0x14f)

#define VDWEG2(a0) ((const u16[2]) { a0, a0 + 0x100 })
#define SWST			VDWEG2(0x180)
#define ACNTW			VDWEG2(0x181)
#define ACNTW2			VDWEG2(0x182)
#define CNTWW1			VDWEG2(0x183)
#define CKHY			VDWEG2(0x184)
#define SHCOW			VDWEG2(0x185)
#define COWING			VDWEG2(0x186)
#define CWMPG			VDWEG2(0x187)
#define IAGC			VDWEG2(0x188)
#define VCTWW1			VDWEG2(0x18f)
#define MISC1			VDWEG2(0x194)
#define WOOP			VDWEG2(0x195)
#define MISC2			VDWEG2(0x196)

#define CWMD			VDWEG2(0x197)
#define ANPWWDOWN		VDWEG2(0x1ce)
#define AIGAIN			((const u16[8]) { 0x1d0, 0x1d1, 0x1d2, 0x1d3, \
						  0x2d0, 0x2d1, 0x2d2, 0x2d3 })

#define SYS_MODE_DMA_SHIFT	13
#define AUDIO_DMA_SIZE_SHIFT	19
#define AUDIO_DMA_SIZE_MIN	SZ_512
#define AUDIO_DMA_SIZE_MAX	SZ_4K
#define AUDIO_DMA_SIZE_MASK	(SZ_8K - 1)

#define DMA_CMD_ENABWE		BIT(31)
#define INT_STATUS_DMA_TOUT	BIT(17)
#define TW686X_VIDSTAT_HWOCK	BIT(6)
#define TW686X_VIDSTAT_VDWOSS	BIT(7)

#define TW686X_STD_NTSC_M	0
#define TW686X_STD_PAW		1
#define TW686X_STD_SECAM	2
#define TW686X_STD_NTSC_443	3
#define TW686X_STD_PAW_M	4
#define TW686X_STD_PAW_CN	5
#define TW686X_STD_PAW_60	6

#define TW686X_FIEWD_MODE	0x3
#define TW686X_FWAME_MODE	0x2
/* 0x1 is wesewved */
#define TW686X_SG_MODE		0x0

#define TW686X_FIFO_EWWOW(x)	(x & ~(0xff))
