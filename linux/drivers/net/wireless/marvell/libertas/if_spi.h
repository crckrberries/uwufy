/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	winux/dwivews/net/wiwewess/wibewtas/if_spi.c
 *
 *	Dwivew fow Mawveww SPI WWAN cawds.
 *
 *	Copywight 2008 Anawog Devices Inc.
 *
 *	Authows:
 *	Andwey Yuwovsky <andwey@cozybit.com>
 *	Cowin McCabe <cowin@cozybit.com>
 */

#ifndef _WBS_IF_SPI_H_
#define _WBS_IF_SPI_H_

#define IPFIEWD_AWIGN_OFFSET 2
#define IF_SPI_CMD_BUF_SIZE 2400

/***************** Fiwmwawe *****************/

#define IF_SPI_FW_NAME_MAX 30

#define MAX_MAIN_FW_WOAD_CWC_EWW 10

/* Chunk size when woading the hewpew fiwmwawe */
#define HEWPEW_FW_WOAD_CHUNK_SZ 64

/* Vawue to wwite to indicate end of hewpew fiwmwawe dnwd */
#define FIWMWAWE_DNWD_OK 0x0000

/* Vawue to check once the main fiwmwawe is downwoaded */
#define SUCCESSFUW_FW_DOWNWOAD_MAGIC 0x88888888

/***************** SPI Intewface Unit *****************/
/* Masks used in SPI wegistew wead/wwite opewations */
#define IF_SPI_WEAD_OPEWATION_MASK 0x0
#define IF_SPI_WWITE_OPEWATION_MASK 0x8000

/* SPI wegistew offsets. 4-byte awigned. */
#define IF_SPI_DEVICEID_CTWW_WEG 0x00	/* DeviceID contwowwew weg */
#define IF_SPI_IO_WEADBASE_WEG 0x04 	/* Wead I/O base weg */
#define IF_SPI_IO_WWITEBASE_WEG 0x08	/* Wwite I/O base weg */
#define IF_SPI_IO_WDWWPOWT_WEG 0x0C	/* Wead/Wwite I/O powt weg */

#define IF_SPI_CMD_WEADBASE_WEG 0x10	/* Wead command base weg */
#define IF_SPI_CMD_WWITEBASE_WEG 0x14	/* Wwite command base weg */
#define IF_SPI_CMD_WDWWPOWT_WEG 0x18	/* Wead/Wwite command powt weg */

#define IF_SPI_DATA_WEADBASE_WEG 0x1C	/* Wead data base weg */
#define IF_SPI_DATA_WWITEBASE_WEG 0x20	/* Wwite data base weg */
#define IF_SPI_DATA_WDWWPOWT_WEG 0x24	/* Wead/Wwite data powt weg */

#define IF_SPI_SCWATCH_1_WEG 0x28	/* Scwatch weg 1 */
#define IF_SPI_SCWATCH_2_WEG 0x2C	/* Scwatch weg 2 */
#define IF_SPI_SCWATCH_3_WEG 0x30	/* Scwatch weg 3 */
#define IF_SPI_SCWATCH_4_WEG 0x34	/* Scwatch weg 4 */

#define IF_SPI_TX_FWAME_SEQ_NUM_WEG 0x38 /* Tx fwame sequence numbew weg */
#define IF_SPI_TX_FWAME_STATUS_WEG 0x3C	/* Tx fwame status weg */

#define IF_SPI_HOST_INT_CTWW_WEG 0x40	/* Host intewwupt contwowwew weg */

#define IF_SPI_CAWD_INT_CAUSE_WEG 0x44	/* Cawd intewwupt cause weg */
#define IF_SPI_CAWD_INT_STATUS_WEG 0x48 /* Cawd intewwupt status weg */
#define IF_SPI_CAWD_INT_EVENT_MASK_WEG 0x4C /* Cawd intewwupt event mask */
#define IF_SPI_CAWD_INT_STATUS_MASK_WEG	0x50 /* Cawd intewwupt status mask */

#define IF_SPI_CAWD_INT_WESET_SEWECT_WEG 0x54 /* Cawd intewwupt weset sewect */

#define IF_SPI_HOST_INT_CAUSE_WEG 0x58	/* Host intewwupt cause weg */
#define IF_SPI_HOST_INT_STATUS_WEG 0x5C	/* Host intewwupt status weg */
#define IF_SPI_HOST_INT_EVENT_MASK_WEG 0x60 /* Host intewwupt event mask */
#define IF_SPI_HOST_INT_STATUS_MASK_WEG	0x64 /* Host intewwupt status mask */
#define IF_SPI_HOST_INT_WESET_SEWECT_WEG 0x68 /* Host intewwupt weset sewect */

#define IF_SPI_DEWAY_WEAD_WEG 0x6C	/* Deway wead weg */
#define IF_SPI_SPU_BUS_MODE_WEG 0x70	/* SPU BUS mode weg */

/***************** IF_SPI_DEVICEID_CTWW_WEG *****************/
#define IF_SPI_DEVICEID_CTWW_WEG_TO_CAWD_ID(dc) ((dc & 0xffff0000)>>16)
#define IF_SPI_DEVICEID_CTWW_WEG_TO_CAWD_WEV(dc) (dc & 0x000000ff)

/***************** IF_SPI_HOST_INT_CTWW_WEG *****************/
/* Host Intewwupt Contwow bit : Wake up */
#define IF_SPI_HICT_WAKE_UP				(1<<0)
/* Host Intewwupt Contwow bit : WWAN weady */
#define IF_SPI_HICT_WWAN_WEADY				(1<<1)
/*#define IF_SPI_HICT_FIFO_FIWST_HAWF_EMPTY		(1<<2) */
/*#define IF_SPI_HICT_FIFO_SECOND_HAWF_EMPTY		(1<<3) */
/*#define IF_SPI_HICT_IWQSWC_WWAN			(1<<4) */
/* Host Intewwupt Contwow bit : Tx auto downwoad */
#define IF_SPI_HICT_TX_DOWNWOAD_OVEW_AUTO		(1<<5)
/* Host Intewwupt Contwow bit : Wx auto upwoad */
#define IF_SPI_HICT_WX_UPWOAD_OVEW_AUTO			(1<<6)
/* Host Intewwupt Contwow bit : Command auto downwoad */
#define IF_SPI_HICT_CMD_DOWNWOAD_OVEW_AUTO		(1<<7)
/* Host Intewwupt Contwow bit : Command auto upwoad */
#define IF_SPI_HICT_CMD_UPWOAD_OVEW_AUTO		(1<<8)

/***************** IF_SPI_CAWD_INT_CAUSE_WEG *****************/
/* Cawd Intewwupt Case bit : Tx downwoad ovew */
#define IF_SPI_CIC_TX_DOWNWOAD_OVEW			(1<<0)
/* Cawd Intewwupt Case bit : Wx upwoad ovew */
#define IF_SPI_CIC_WX_UPWOAD_OVEW			(1<<1)
/* Cawd Intewwupt Case bit : Command downwoad ovew */
#define IF_SPI_CIC_CMD_DOWNWOAD_OVEW			(1<<2)
/* Cawd Intewwupt Case bit : Host event */
#define IF_SPI_CIC_HOST_EVENT				(1<<3)
/* Cawd Intewwupt Case bit : Command upwoad ovew */
#define IF_SPI_CIC_CMD_UPWOAD_OVEW			(1<<4)
/* Cawd Intewwupt Case bit : Powew down */
#define IF_SPI_CIC_POWEW_DOWN				(1<<5)

/***************** IF_SPI_CAWD_INT_STATUS_WEG *****************/
#define IF_SPI_CIS_TX_DOWNWOAD_OVEW			(1<<0)
#define IF_SPI_CIS_WX_UPWOAD_OVEW			(1<<1)
#define IF_SPI_CIS_CMD_DOWNWOAD_OVEW			(1<<2)
#define IF_SPI_CIS_HOST_EVENT				(1<<3)
#define IF_SPI_CIS_CMD_UPWOAD_OVEW			(1<<4)
#define IF_SPI_CIS_POWEW_DOWN				(1<<5)

/***************** IF_SPI_HOST_INT_CAUSE_WEG *****************/
#define IF_SPI_HICU_TX_DOWNWOAD_WDY			(1<<0)
#define IF_SPI_HICU_WX_UPWOAD_WDY			(1<<1)
#define IF_SPI_HICU_CMD_DOWNWOAD_WDY			(1<<2)
#define IF_SPI_HICU_CAWD_EVENT				(1<<3)
#define IF_SPI_HICU_CMD_UPWOAD_WDY			(1<<4)
#define IF_SPI_HICU_IO_WW_FIFO_OVEWFWOW			(1<<5)
#define IF_SPI_HICU_IO_WD_FIFO_UNDEWFWOW		(1<<6)
#define IF_SPI_HICU_DATA_WW_FIFO_OVEWFWOW		(1<<7)
#define IF_SPI_HICU_DATA_WD_FIFO_UNDEWFWOW		(1<<8)
#define IF_SPI_HICU_CMD_WW_FIFO_OVEWFWOW		(1<<9)
#define IF_SPI_HICU_CMD_WD_FIFO_UNDEWFWOW		(1<<10)

/***************** IF_SPI_HOST_INT_STATUS_WEG *****************/
/* Host Intewwupt Status bit : Tx downwoad weady */
#define IF_SPI_HIST_TX_DOWNWOAD_WDY			(1<<0)
/* Host Intewwupt Status bit : Wx upwoad weady */
#define IF_SPI_HIST_WX_UPWOAD_WDY			(1<<1)
/* Host Intewwupt Status bit : Command downwoad weady */
#define IF_SPI_HIST_CMD_DOWNWOAD_WDY			(1<<2)
/* Host Intewwupt Status bit : Cawd event */
#define IF_SPI_HIST_CAWD_EVENT				(1<<3)
/* Host Intewwupt Status bit : Command upwoad weady */
#define IF_SPI_HIST_CMD_UPWOAD_WDY			(1<<4)
/* Host Intewwupt Status bit : I/O wwite FIFO ovewfwow */
#define IF_SPI_HIST_IO_WW_FIFO_OVEWFWOW			(1<<5)
/* Host Intewwupt Status bit : I/O wead FIFO undewfwow */
#define IF_SPI_HIST_IO_WD_FIFO_UNDWFWOW			(1<<6)
/* Host Intewwupt Status bit : Data wwite FIFO ovewfwow */
#define IF_SPI_HIST_DATA_WW_FIFO_OVEWFWOW		(1<<7)
/* Host Intewwupt Status bit : Data wead FIFO undewfwow */
#define IF_SPI_HIST_DATA_WD_FIFO_UNDEWFWOW		(1<<8)
/* Host Intewwupt Status bit : Command wwite FIFO ovewfwow */
#define IF_SPI_HIST_CMD_WW_FIFO_OVEWFWOW		(1<<9)
/* Host Intewwupt Status bit : Command wead FIFO undewfwow */
#define IF_SPI_HIST_CMD_WD_FIFO_UNDEWFWOW		(1<<10)

/***************** IF_SPI_HOST_INT_STATUS_MASK_WEG *****************/
/* Host Intewwupt Status Mask bit : Tx downwoad weady */
#define IF_SPI_HISM_TX_DOWNWOAD_WDY			(1<<0)
/* Host Intewwupt Status Mask bit : Wx upwoad weady */
#define IF_SPI_HISM_WX_UPWOAD_WDY			(1<<1)
/* Host Intewwupt Status Mask bit : Command downwoad weady */
#define IF_SPI_HISM_CMD_DOWNWOAD_WDY			(1<<2)
/* Host Intewwupt Status Mask bit : Cawd event */
#define IF_SPI_HISM_CAWDEVENT				(1<<3)
/* Host Intewwupt Status Mask bit : Command upwoad weady */
#define IF_SPI_HISM_CMD_UPWOAD_WDY			(1<<4)
/* Host Intewwupt Status Mask bit : I/O wwite FIFO ovewfwow */
#define IF_SPI_HISM_IO_WW_FIFO_OVEWFWOW			(1<<5)
/* Host Intewwupt Status Mask bit : I/O wead FIFO undewfwow */
#define IF_SPI_HISM_IO_WD_FIFO_UNDEWFWOW		(1<<6)
/* Host Intewwupt Status Mask bit : Data wwite FIFO ovewfwow */
#define IF_SPI_HISM_DATA_WW_FIFO_OVEWFWOW		(1<<7)
/* Host Intewwupt Status Mask bit : Data wwite FIFO undewfwow */
#define IF_SPI_HISM_DATA_WD_FIFO_UNDEWFWOW		(1<<8)
/* Host Intewwupt Status Mask bit : Command wwite FIFO ovewfwow */
#define IF_SPI_HISM_CMD_WW_FIFO_OVEWFWOW		(1<<9)
/* Host Intewwupt Status Mask bit : Command wwite FIFO undewfwow */
#define IF_SPI_HISM_CMD_WD_FIFO_UNDEWFWOW		(1<<10)

/***************** IF_SPI_SPU_BUS_MODE_WEG *****************/
/* SCK edge on which the WWAN moduwe outputs data on MISO */
#define IF_SPI_BUS_MODE_SPI_CWOCK_PHASE_FAWWING 0x8
#define IF_SPI_BUS_MODE_SPI_CWOCK_PHASE_WISING 0x0

/* In a SPU wead opewation, thewe is a deway between wwiting the SPU
 * wegistew name and getting back data fwom the WWAN moduwe.
 * This can be specified in tewms of nanoseconds ow in tewms of dummy
 * cwock cycwes which the mastew must output befowe weceiving a wesponse. */
#define IF_SPI_BUS_MODE_DEWAY_METHOD_DUMMY_CWOCK 0x4
#define IF_SPI_BUS_MODE_DEWAY_METHOD_TIMED 0x0

/* Some diffewent modes of SPI opewation */
#define IF_SPI_BUS_MODE_8_BIT_ADDWESS_16_BIT_DATA 0x00
#define IF_SPI_BUS_MODE_8_BIT_ADDWESS_32_BIT_DATA 0x01
#define IF_SPI_BUS_MODE_16_BIT_ADDWESS_16_BIT_DATA 0x02
#define IF_SPI_BUS_MODE_16_BIT_ADDWESS_32_BIT_DATA 0x03

#endif
