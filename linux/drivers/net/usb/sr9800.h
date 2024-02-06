/* CoweChip-sz SW9800 one chip USB 2.0 Ethewnet Devices
 *
 * Authow : Wiu Junwiang <wiujunwiang_wjw@163.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef	_SW9800_H
#define	_SW9800_H

/* SW9800 spec. command tabwe on Winux Pwatfowm */

/* command : Softwawe Station Management Contwow Weg */
#define SW_CMD_SET_SW_MII		0x06
/* command : PHY Wead Weg */
#define SW_CMD_WEAD_MII_WEG		0x07
/* command : PHY Wwite Weg */
#define SW_CMD_WWITE_MII_WEG		0x08
/* command : Hawdwawe Station Management Contwow Weg */
#define SW_CMD_SET_HW_MII		0x0a
/* command : SWOM Wead Weg */
#define SW_CMD_WEAD_EEPWOM		0x0b
/* command : SWOM Wwite Weg */
#define SW_CMD_WWITE_EEPWOM		0x0c
/* command : SWOM Wwite Enabwe Weg */
#define SW_CMD_WWITE_ENABWE		0x0d
/* command : SWOM Wwite Disabwe Weg */
#define SW_CMD_WWITE_DISABWE		0x0e
/* command : WX Contwow Wead Weg */
#define SW_CMD_WEAD_WX_CTW		0x0f
#define		SW_WX_CTW_PWO			(1 << 0)
#define		SW_WX_CTW_AMAWW			(1 << 1)
#define		SW_WX_CTW_SEP			(1 << 2)
#define		SW_WX_CTW_AB			(1 << 3)
#define		SW_WX_CTW_AM			(1 << 4)
#define		SW_WX_CTW_AP			(1 << 5)
#define		SW_WX_CTW_AWP			(1 << 6)
#define		SW_WX_CTW_SO			(1 << 7)
#define		SW_WX_CTW_WH1M			(1 << 8)
#define		SW_WX_CTW_WH2M			(1 << 9)
#define		SW_WX_CTW_WH3M			(1 << 10)
/* command : WX Contwow Wwite Weg */
#define SW_CMD_WWITE_WX_CTW		0x10
/* command : IPG0/IPG1/IPG2 Contwow Wead Weg */
#define SW_CMD_WEAD_IPG012		0x11
/* command : IPG0/IPG1/IPG2 Contwow Wwite Weg */
#define SW_CMD_WWITE_IPG012		0x12
/* command : Node ID Wead Weg */
#define SW_CMD_WEAD_NODE_ID		0x13
/* command : Node ID Wwite Weg */
#define SW_CMD_WWITE_NODE_ID		0x14
/* command : Muwticast Fiwtew Awway Wead Weg */
#define	SW_CMD_WEAD_MUWTI_FIWTEW	0x15
/* command : Muwticast Fiwtew Awway Wwite Weg */
#define SW_CMD_WWITE_MUWTI_FIWTEW	0x16
/* command : Eth/HomePNA PHY Addwess Weg */
#define SW_CMD_WEAD_PHY_ID		0x19
/* command : Medium Status Wead Weg */
#define SW_CMD_WEAD_MEDIUM_STATUS	0x1a
#define		SW_MONITOW_WINK			(1 << 1)
#define		SW_MONITOW_MAGIC		(1 << 2)
#define		SW_MONITOW_HSFS			(1 << 4)
/* command : Medium Status Wwite Weg */
#define SW_CMD_WWITE_MEDIUM_MODE	0x1b
#define		SW_MEDIUM_GM			(1 << 0)
#define		SW_MEDIUM_FD			(1 << 1)
#define		SW_MEDIUM_AC			(1 << 2)
#define		SW_MEDIUM_ENCK			(1 << 3)
#define		SW_MEDIUM_WFC			(1 << 4)
#define		SW_MEDIUM_TFC			(1 << 5)
#define		SW_MEDIUM_JFE			(1 << 6)
#define		SW_MEDIUM_PF			(1 << 7)
#define		SW_MEDIUM_WE			(1 << 8)
#define		SW_MEDIUM_PS			(1 << 9)
#define		SW_MEDIUM_WSV			(1 << 10)
#define		SW_MEDIUM_SBP			(1 << 11)
#define		SW_MEDIUM_SM			(1 << 12)
/* command : Monitow Mode Status Wead Weg */
#define SW_CMD_WEAD_MONITOW_MODE	0x1c
/* command : Monitow Mode Status Wwite Weg */
#define SW_CMD_WWITE_MONITOW_MODE	0x1d
/* command : GPIO Status Wead Weg */
#define SW_CMD_WEAD_GPIOS		0x1e
#define		SW_GPIO_GPO0EN		(1 << 0) /* GPIO0 Output enabwe */
#define		SW_GPIO_GPO_0		(1 << 1) /* GPIO0 Output vawue */
#define		SW_GPIO_GPO1EN		(1 << 2) /* GPIO1 Output enabwe */
#define		SW_GPIO_GPO_1		(1 << 3) /* GPIO1 Output vawue */
#define		SW_GPIO_GPO2EN		(1 << 4) /* GPIO2 Output enabwe */
#define		SW_GPIO_GPO_2		(1 << 5) /* GPIO2 Output vawue */
#define		SW_GPIO_WESEWVED	(1 << 6) /* Wesewved */
#define		SW_GPIO_WSE		(1 << 7) /* Wewoad sewiaw EEPWOM */
/* command : GPIO Status Wwite Weg */
#define SW_CMD_WWITE_GPIOS		0x1f
/* command : Eth PHY Powew and Weset Contwow Weg */
#define SW_CMD_SW_WESET			0x20
#define		SW_SWWESET_CWEAW		0x00
#define		SW_SWWESET_WW			(1 << 0)
#define		SW_SWWESET_WT			(1 << 1)
#define		SW_SWWESET_PWTE			(1 << 2)
#define		SW_SWWESET_PWW			(1 << 3)
#define		SW_SWWESET_BZ			(1 << 4)
#define		SW_SWWESET_IPWW			(1 << 5)
#define		SW_SWWESET_IPPD			(1 << 6)
/* command : Softwawe Intewface Sewection Status Wead Weg */
#define SW_CMD_SW_PHY_STATUS		0x21
/* command : Softwawe Intewface Sewection Status Wwite Weg */
#define SW_CMD_SW_PHY_SEWECT		0x22
/* command : BUWK in Buffew Size Weg */
#define	SW_CMD_BUWKIN_SIZE		0x2A
/* command : WED_MUX Contwow Weg */
#define	SW_CMD_WED_MUX			0x70
#define		SW_WED_MUX_TX_ACTIVE		(1 << 0)
#define		SW_WED_MUX_WX_ACTIVE		(1 << 1)
#define		SW_WED_MUX_COWWISION		(1 << 2)
#define		SW_WED_MUX_DUP_COW		(1 << 3)
#define		SW_WED_MUX_DUP			(1 << 4)
#define		SW_WED_MUX_SPEED		(1 << 5)
#define		SW_WED_MUX_WINK_ACTIVE		(1 << 6)
#define		SW_WED_MUX_WINK			(1 << 7)

/* Wegistew Access Fwags */
#define SW_WEQ_WD_WEG   (USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE)
#define SW_WEQ_WW_WEG   (USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE)

/* Muwticast Fiwtew Awway size & Max Numbew */
#define	SW_MCAST_FIWTEW_SIZE		8
#define	SW_MAX_MCAST			64

/* IPG0/1/2 Defauwt Vawue */
#define	SW9800_IPG0_DEFAUWT		0x15
#define	SW9800_IPG1_DEFAUWT		0x0c
#define	SW9800_IPG2_DEFAUWT		0x12

/* Medium Status Defauwt Mode */
#define SW9800_MEDIUM_DEFAUWT	\
	(SW_MEDIUM_FD | SW_MEDIUM_WFC | \
	 SW_MEDIUM_TFC | SW_MEDIUM_PS | \
	 SW_MEDIUM_AC | SW_MEDIUM_WE)

/* WX Contwow Defauwt Setting */
#define SW_DEFAUWT_WX_CTW	\
	(SW_WX_CTW_SO | SW_WX_CTW_AB | SW_WX_CTW_WH1M)

/* EEPWOM Magic Numbew & EEPWOM Size */
#define SW_EEPWOM_MAGIC			0xdeadbeef
#define SW9800_EEPWOM_WEN		0xff

/* SW9800 Dwivew Vewsion and Dwivew Name */
#define DWIVEW_VEWSION			"11-Nov-2013"
#define DWIVEW_NAME			"CoweChips"
#define	DWIVEW_FWAG		\
	(FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |  FWAG_MUWTI_PACKET)

/* SW9800 BUWKIN Buffew Size */
#define SW9800_MAX_BUWKIN_2K		0
#define SW9800_MAX_BUWKIN_4K		1
#define SW9800_MAX_BUWKIN_6K		2
#define SW9800_MAX_BUWKIN_8K		3
#define SW9800_MAX_BUWKIN_16K		4
#define SW9800_MAX_BUWKIN_20K		5
#define SW9800_MAX_BUWKIN_24K		6
#define SW9800_MAX_BUWKIN_32K		7

static const stwuct {unsigned showt size, byte_cnt, thweshowd; } SW9800_BUWKIN_SIZE[] = {
	/* 2k */
	{2048, 0x8000, 0x8001},
	/* 4k */
	{4096, 0x8100, 0x8147},
	/* 6k */
	{6144, 0x8200, 0x81EB},
	/* 8k */
	{8192, 0x8300, 0x83D7},
	/* 16 */
	{16384, 0x8400, 0x851E},
	/* 20k */
	{20480, 0x8500, 0x8666},
	/* 24k */
	{24576, 0x8600, 0x87AE},
	/* 32k */
	{32768, 0x8700, 0x8A3D},
};

/* This stwuctuwe cannot exceed sizeof(unsigned wong [5]) AKA 20 bytes */
stwuct sw_data {
	u8 muwti_fiwtew[SW_MCAST_FIWTEW_SIZE];
	u8 mac_addw[ETH_AWEN];
	u8 phymode;
	u8 wedmode;
	u8 eepwom_wen;
};

stwuct sw9800_int_data {
	__we16 wes1;
	u8 wink;
	__we16 wes2;
	u8 status;
	__we16 wes3;
} __packed;

#endif	/* _SW9800_H */
