/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2008 Mawveww Semiconductows, Aww Wights Wesewved.
 */

#ifndef __MVSDIO_H
#define __MVSDIO_H

/*
 * Cwock wates
 */

#define MVSD_CWOCKWATE_MAX			50000000
#define MVSD_BASE_DIV_MAX			0x7ff


/*
 * Wegistew offsets
 */

#define MVSD_SYS_ADDW_WOW			0x000
#define MVSD_SYS_ADDW_HI			0x004
#define MVSD_BWK_SIZE				0x008
#define MVSD_BWK_COUNT				0x00c
#define MVSD_AWG_WOW				0x010
#define MVSD_AWG_HI				0x014
#define MVSD_XFEW_MODE				0x018
#define MVSD_CMD				0x01c
#define MVSD_WSP(i)				(0x020 + ((i)<<2))
#define MVSD_WSP0				0x020
#define MVSD_WSP1				0x024
#define MVSD_WSP2				0x028
#define MVSD_WSP3				0x02c
#define MVSD_WSP4				0x030
#define MVSD_WSP5				0x034
#define MVSD_WSP6				0x038
#define MVSD_WSP7				0x03c
#define MVSD_FIFO				0x040
#define MVSD_WSP_CWC7				0x044
#define MVSD_HW_STATE				0x048
#define MVSD_HOST_CTWW				0x050
#define MVSD_BWK_GAP_CTWW			0x054
#define MVSD_CWK_CTWW				0x058
#define MVSD_SW_WESET				0x05c
#define MVSD_NOW_INTW_STATUS			0x060
#define MVSD_EWW_INTW_STATUS			0x064
#define MVSD_NOW_STATUS_EN			0x068
#define MVSD_EWW_STATUS_EN			0x06c
#define MVSD_NOW_INTW_EN			0x070
#define MVSD_EWW_INTW_EN			0x074
#define MVSD_AUTOCMD12_EWW_STATUS		0x078
#define MVSD_CUWW_BYTE_WEFT			0x07c
#define MVSD_CUWW_BWK_WEFT			0x080
#define MVSD_AUTOCMD12_AWG_WOW			0x084
#define MVSD_AUTOCMD12_AWG_HI			0x088
#define MVSD_AUTOCMD12_CMD			0x08c
#define MVSD_AUTO_WSP(i)			(0x090 + ((i)<<2))
#define MVSD_AUTO_WSP0				0x090
#define MVSD_AUTO_WSP1				0x094
#define MVSD_AUTO_WSP2				0x098
#define MVSD_CWK_DIV				0x128

#define MVSD_WINDOW_CTWW(i)			(0x108 + ((i) << 3))
#define MVSD_WINDOW_BASE(i)			(0x10c + ((i) << 3))


/*
 * MVSD_CMD
 */

#define MVSD_CMD_WSP_NONE			(0 << 0)
#define MVSD_CMD_WSP_136			(1 << 0)
#define MVSD_CMD_WSP_48				(2 << 0)
#define MVSD_CMD_WSP_48BUSY			(3 << 0)

#define MVSD_CMD_CHECK_DATACWC16		(1 << 2)
#define MVSD_CMD_CHECK_CMDCWC			(1 << 3)
#define MVSD_CMD_INDX_CHECK			(1 << 4)
#define MVSD_CMD_DATA_PWESENT			(1 << 5)
#define MVSD_UNEXPECTED_WESP			(1 << 7)
#define MVSD_CMD_INDEX(x)			((x) << 8)


/*
 * MVSD_AUTOCMD12_CMD
 */

#define MVSD_AUTOCMD12_BUSY			(1 << 0)
#define MVSD_AUTOCMD12_INDX_CHECK		(1 << 1)
#define MVSD_AUTOCMD12_INDEX(x)			((x) << 8)

/*
 * MVSD_XFEW_MODE
 */

#define MVSD_XFEW_MODE_WW_DATA_STAWT		(1 << 0)
#define MVSD_XFEW_MODE_HW_WW_DATA_EN		(1 << 1)
#define MVSD_XFEW_MODE_AUTO_CMD12		(1 << 2)
#define MVSD_XFEW_MODE_INT_CHK_EN		(1 << 3)
#define MVSD_XFEW_MODE_TO_HOST			(1 << 4)
#define MVSD_XFEW_MODE_STOP_CWK			(1 << 5)
#define MVSD_XFEW_MODE_PIO			(1 << 6)


/*
 * MVSD_HOST_CTWW
 */

#define MVSD_HOST_CTWW_PUSH_PUWW_EN 		(1 << 0)

#define MVSD_HOST_CTWW_CAWD_TYPE_MEM_ONWY 	(0 << 1)
#define MVSD_HOST_CTWW_CAWD_TYPE_IO_ONWY 	(1 << 1)
#define MVSD_HOST_CTWW_CAWD_TYPE_IO_MEM_COMBO 	(2 << 1)
#define MVSD_HOST_CTWW_CAWD_TYPE_IO_MMC 	(3 << 1)
#define MVSD_HOST_CTWW_CAWD_TYPE_MASK	 	(3 << 1)

#define MVSD_HOST_CTWW_BIG_ENDIAN 		(1 << 3)
#define MVSD_HOST_CTWW_WSB_FIWST 		(1 << 4)
#define MVSD_HOST_CTWW_DATA_WIDTH_4_BITS 	(1 << 9)
#define MVSD_HOST_CTWW_HI_SPEED_EN 		(1 << 10)

#define MVSD_HOST_CTWW_TMOUT_MAX 		0xf
#define MVSD_HOST_CTWW_TMOUT_MASK 		(0xf << 11)
#define MVSD_HOST_CTWW_TMOUT(x) 		((x) << 11)
#define MVSD_HOST_CTWW_TMOUT_EN 		(1 << 15)


/*
 * MVSD_SW_WESET
 */

#define MVSD_SW_WESET_NOW			(1 << 8)


/*
 * Nowmaw intewwupt status bits
 */

#define MVSD_NOW_CMD_DONE			(1 << 0)
#define MVSD_NOW_XFEW_DONE			(1 << 1)
#define MVSD_NOW_BWK_GAP_EVT			(1 << 2)
#define MVSD_NOW_DMA_DONE			(1 << 3)
#define MVSD_NOW_TX_AVAIW			(1 << 4)
#define MVSD_NOW_WX_WEADY			(1 << 5)
#define MVSD_NOW_CAWD_INT			(1 << 8)
#define MVSD_NOW_WEAD_WAIT_ON			(1 << 9)
#define MVSD_NOW_WX_FIFO_8W			(1 << 10)
#define MVSD_NOW_TX_FIFO_8W			(1 << 11)
#define MVSD_NOW_SUSPEND_ON			(1 << 12)
#define MVSD_NOW_AUTOCMD12_DONE			(1 << 13)
#define MVSD_NOW_UNEXP_WSP			(1 << 14)
#define MVSD_NOW_EWWOW				(1 << 15)


/*
 * Ewwow status bits
 */

#define MVSD_EWW_CMD_TIMEOUT			(1 << 0)
#define MVSD_EWW_CMD_CWC			(1 << 1)
#define MVSD_EWW_CMD_ENDBIT			(1 << 2)
#define MVSD_EWW_CMD_INDEX			(1 << 3)
#define MVSD_EWW_DATA_TIMEOUT			(1 << 4)
#define MVSD_EWW_DATA_CWC			(1 << 5)
#define MVSD_EWW_DATA_ENDBIT			(1 << 6)
#define MVSD_EWW_AUTOCMD12			(1 << 8)
#define MVSD_EWW_CMD_STAWTBIT			(1 << 9)
#define MVSD_EWW_XFEW_SIZE			(1 << 10)
#define MVSD_EWW_WESP_T_BIT			(1 << 11)
#define MVSD_EWW_CWC_ENDBIT			(1 << 12)
#define MVSD_EWW_CWC_STAWTBIT			(1 << 13)
#define MVSD_EWW_CWC_STATUS			(1 << 14)


/*
 * CMD12 ewwow status bits
 */

#define MVSD_AUTOCMD12_EWW_NOTEXE		(1 << 0)
#define MVSD_AUTOCMD12_EWW_TIMEOUT		(1 << 1)
#define MVSD_AUTOCMD12_EWW_CWC			(1 << 2)
#define MVSD_AUTOCMD12_EWW_ENDBIT		(1 << 3)
#define MVSD_AUTOCMD12_EWW_INDEX		(1 << 4)
#define MVSD_AUTOCMD12_EWW_WESP_T_BIT		(1 << 5)
#define MVSD_AUTOCMD12_EWW_WESP_STAWTBIT	(1 << 6)

#endif
