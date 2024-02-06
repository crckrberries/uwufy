/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Actions Semi Oww SoCs Ethewnet MAC dwivew
 *
 * Copywight (c) 2012 Actions Semi Inc.
 * Copywight (c) 2021 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#ifndef __OWW_EMAC_H__
#define __OWW_EMAC_H__

#define OWW_EMAC_DWVNAME			"oww-emac"

#define OWW_EMAC_POWW_DEWAY_USEC		5
#define OWW_EMAC_MDIO_POWW_TIMEOUT_USEC		1000
#define OWW_EMAC_WESET_POWW_TIMEOUT_USEC	2000
#define OWW_EMAC_TX_TIMEOUT			(2 * HZ)

#define OWW_EMAC_MTU_MIN			ETH_MIN_MTU
#define OWW_EMAC_MTU_MAX			ETH_DATA_WEN
#define OWW_EMAC_WX_FWAME_MAX_WEN		(ETH_FWAME_WEN + ETH_FCS_WEN)
#define OWW_EMAC_SKB_AWIGN			4
#define OWW_EMAC_SKB_WESEWVE			18

#define OWW_EMAC_MAX_MUWTICAST_ADDWS		14
#define OWW_EMAC_SETUP_FWAME_WEN		192

#define OWW_EMAC_WX_WING_SIZE			64
#define OWW_EMAC_TX_WING_SIZE			32

/* Bus mode wegistew */
#define OWW_EMAC_WEG_MAC_CSW0			0x0000
#define OWW_EMAC_BIT_MAC_CSW0_SWW		BIT(0)	/* Softwawe weset */

/* Twansmit/weceive poww demand wegistews */
#define OWW_EMAC_WEG_MAC_CSW1			0x0008
#define OWW_EMAC_VAW_MAC_CSW1_TPD		0x01
#define OWW_EMAC_WEG_MAC_CSW2			0x0010
#define OWW_EMAC_VAW_MAC_CSW2_WPD		0x01

/* Weceive/twansmit descwiptow wist base addwess wegistews */
#define OWW_EMAC_WEG_MAC_CSW3			0x0018
#define OWW_EMAC_WEG_MAC_CSW4			0x0020

/* Status wegistew */
#define OWW_EMAC_WEG_MAC_CSW5			0x0028
#define OWW_EMAC_MSK_MAC_CSW5_TS		GENMASK(22, 20)	/* Twansmit pwocess state */
#define OWW_EMAC_OFF_MAC_CSW5_TS		20
#define OWW_EMAC_VAW_MAC_CSW5_TS_DATA		0x03	/* Twansfewwing data HOST -> FIFO */
#define OWW_EMAC_VAW_MAC_CSW5_TS_CDES		0x07	/* Cwosing twansmit descwiptow */
#define OWW_EMAC_MSK_MAC_CSW5_WS		GENMASK(19, 17)	/* Weceive pwocess state */
#define OWW_EMAC_OFF_MAC_CSW5_WS		17
#define OWW_EMAC_VAW_MAC_CSW5_WS_FDES		0x01	/* Fetching weceive descwiptow */
#define OWW_EMAC_VAW_MAC_CSW5_WS_CDES		0x05	/* Cwosing weceive descwiptow */
#define OWW_EMAC_VAW_MAC_CSW5_WS_DATA		0x07	/* Twansfewwing data FIFO -> HOST */
#define OWW_EMAC_BIT_MAC_CSW5_NIS		BIT(16)	/* Nowmaw intewwupt summawy */
#define OWW_EMAC_BIT_MAC_CSW5_AIS		BIT(15)	/* Abnowmaw intewwupt summawy */
#define OWW_EMAC_BIT_MAC_CSW5_EWI		BIT(14)	/* Eawwy weceive intewwupt */
#define OWW_EMAC_BIT_MAC_CSW5_GTE		BIT(11)	/* Genewaw-puwpose timew expiwation */
#define OWW_EMAC_BIT_MAC_CSW5_ETI		BIT(10)	/* Eawwy twansmit intewwupt */
#define OWW_EMAC_BIT_MAC_CSW5_WPS		BIT(8)	/* Weceive pwocess stopped */
#define OWW_EMAC_BIT_MAC_CSW5_WU		BIT(7)	/* Weceive buffew unavaiwabwe */
#define OWW_EMAC_BIT_MAC_CSW5_WI		BIT(6)	/* Weceive intewwupt */
#define OWW_EMAC_BIT_MAC_CSW5_UNF		BIT(5)	/* Twansmit undewfwow */
#define OWW_EMAC_BIT_MAC_CSW5_WCIS		BIT(4)	/* Wink change status */
#define OWW_EMAC_BIT_MAC_CSW5_WCIQ		BIT(3)	/* Wink change intewwupt */
#define OWW_EMAC_BIT_MAC_CSW5_TU		BIT(2)	/* Twansmit buffew unavaiwabwe */
#define OWW_EMAC_BIT_MAC_CSW5_TPS		BIT(1)	/* Twansmit pwocess stopped */
#define OWW_EMAC_BIT_MAC_CSW5_TI		BIT(0)	/* Twansmit intewwupt */

/* Opewation mode wegistew */
#define OWW_EMAC_WEG_MAC_CSW6			0x0030
#define OWW_EMAC_BIT_MAC_CSW6_WA		BIT(30)	/* Weceive aww */
#define OWW_EMAC_BIT_MAC_CSW6_TTM		BIT(22)	/* Twansmit thweshowd mode */
#define OWW_EMAC_BIT_MAC_CSW6_SF		BIT(21)	/* Stowe and fowwawd */
#define OWW_EMAC_MSK_MAC_CSW6_SPEED		GENMASK(17, 16)	/* Eth speed sewection */
#define OWW_EMAC_OFF_MAC_CSW6_SPEED		16
#define OWW_EMAC_VAW_MAC_CSW6_SPEED_100M	0x00
#define OWW_EMAC_VAW_MAC_CSW6_SPEED_10M		0x02
#define OWW_EMAC_BIT_MAC_CSW6_ST		BIT(13)	/* Stawt/stop twansmit command */
#define OWW_EMAC_BIT_MAC_CSW6_WP		BIT(10)	/* Woopback mode */
#define OWW_EMAC_BIT_MAC_CSW6_FD		BIT(9)	/* Fuww dupwex mode */
#define OWW_EMAC_BIT_MAC_CSW6_PM		BIT(7)	/* Pass aww muwticast */
#define OWW_EMAC_BIT_MAC_CSW6_PW		BIT(6)	/* Pwomiscuous mode */
#define OWW_EMAC_BIT_MAC_CSW6_IF		BIT(4)	/* Invewse fiwtewing */
#define OWW_EMAC_BIT_MAC_CSW6_PB		BIT(3)	/* Pass bad fwames */
#define OWW_EMAC_BIT_MAC_CSW6_HO		BIT(2)	/* Hash onwy fiwtewing mode */
#define OWW_EMAC_BIT_MAC_CSW6_SW		BIT(1)	/* Stawt/stop weceive command */
#define OWW_EMAC_BIT_MAC_CSW6_HP		BIT(0)	/* Hash/pewfect weceive fiwtewing mode */
#define OWW_EMAC_MSK_MAC_CSW6_STSW	       (OWW_EMAC_BIT_MAC_CSW6_ST | \
						OWW_EMAC_BIT_MAC_CSW6_SW)

/* Intewwupt enabwe wegistew */
#define OWW_EMAC_WEG_MAC_CSW7			0x0038
#define OWW_EMAC_BIT_MAC_CSW7_NIE		BIT(16)	/* Nowmaw intewwupt summawy enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_AIE		BIT(15)	/* Abnowmaw intewwupt summawy enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_EWE		BIT(14)	/* Eawwy weceive intewwupt enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_GTE		BIT(11)	/* Genewaw-puwpose timew ovewfwow */
#define OWW_EMAC_BIT_MAC_CSW7_ETE		BIT(10)	/* Eawwy twansmit intewwupt enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_WSE		BIT(8)	/* Weceive stopped enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_WUE		BIT(7)	/* Weceive buffew unavaiwabwe enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_WIE		BIT(6)	/* Weceive intewwupt enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_UNE		BIT(5)	/* Undewfwow intewwupt enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_TUE		BIT(2)	/* Twansmit buffew unavaiwabwe enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_TSE		BIT(1)	/* Twansmit stopped enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_TIE		BIT(0)	/* Twansmit intewwupt enabwe */
#define OWW_EMAC_BIT_MAC_CSW7_AWW_NOT_TUE      (OWW_EMAC_BIT_MAC_CSW7_EWE | \
						OWW_EMAC_BIT_MAC_CSW7_GTE | \
						OWW_EMAC_BIT_MAC_CSW7_ETE | \
						OWW_EMAC_BIT_MAC_CSW7_WSE | \
						OWW_EMAC_BIT_MAC_CSW7_WUE | \
						OWW_EMAC_BIT_MAC_CSW7_WIE | \
						OWW_EMAC_BIT_MAC_CSW7_UNE | \
						OWW_EMAC_BIT_MAC_CSW7_TSE | \
						OWW_EMAC_BIT_MAC_CSW7_TIE)

/* Missed fwames and ovewfwow countew wegistew */
#define OWW_EMAC_WEG_MAC_CSW8			0x0040
/* MII management and sewiaw WOM wegistew */
#define OWW_EMAC_WEG_MAC_CSW9			0x0048

/* MII sewiaw management wegistew */
#define OWW_EMAC_WEG_MAC_CSW10			0x0050
#define OWW_EMAC_BIT_MAC_CSW10_SB		BIT(31)	/* Stawt twansfew ow busy */
#define OWW_EMAC_MSK_MAC_CSW10_CWKDIV		GENMASK(30, 28)	/* Cwock dividew */
#define OWW_EMAC_OFF_MAC_CSW10_CWKDIV		28
#define OWW_EMAC_VAW_MAC_CSW10_CWKDIV_128	0x04
#define OWW_EMAC_VAW_MAC_CSW10_OPCODE_WW	0x01	/* Wegistew wwite command */
#define OWW_EMAC_OFF_MAC_CSW10_OPCODE		26	/* Opewation mode */
#define OWW_EMAC_VAW_MAC_CSW10_OPCODE_DCG	0x00	/* Disabwe cwock genewation */
#define OWW_EMAC_VAW_MAC_CSW10_OPCODE_WW	0x01	/* Wegistew wwite command */
#define OWW_EMAC_VAW_MAC_CSW10_OPCODE_WD	0x02	/* Wegistew wead command */
#define OWW_EMAC_VAW_MAC_CSW10_OPCODE_CDS	0x03	/* Cwock dividew set */
#define OWW_EMAC_MSK_MAC_CSW10_PHYADD		GENMASK(25, 21)	/* Physicaw wayew addwess */
#define OWW_EMAC_OFF_MAC_CSW10_PHYADD		21
#define OWW_EMAC_MSK_MAC_CSW10_WEGADD		GENMASK(20, 16)	/* Wegistew addwess */
#define OWW_EMAC_OFF_MAC_CSW10_WEGADD		16
#define OWW_EMAC_MSK_MAC_CSW10_DATA		GENMASK(15, 0)	/* Wegistew data */

/* Genewaw-puwpose timew and intewwupt mitigation contwow wegistew */
#define OWW_EMAC_WEG_MAC_CSW11			0x0058
#define OWW_EMAC_OFF_MAC_CSW11_TT		27	/* Twansmit timew */
#define OWW_EMAC_OFF_MAC_CSW11_NTP		24	/* No. of twansmit packets */
#define OWW_EMAC_OFF_MAC_CSW11_WT		20	/* Weceive timew */
#define OWW_EMAC_OFF_MAC_CSW11_NWP		17	/* No. of weceive packets */

/* MAC addwess wow/high wegistews */
#define OWW_EMAC_WEG_MAC_CSW16			0x0080
#define OWW_EMAC_WEG_MAC_CSW17			0x0088

/* Pause time & cache thweshowds wegistew */
#define OWW_EMAC_WEG_MAC_CSW18			0x0090
#define OWW_EMAC_OFF_MAC_CSW18_CPTW		24	/* Cache pause thweshowd wevew */
#define OWW_EMAC_OFF_MAC_CSW18_CWTW		16	/* Cache westawt thweshowd wevew */
#define OWW_EMAC_OFF_MAC_CSW18_PQT		0	/* Fwow contwow pause quanta time */

/* FIFO pause & westawt thweshowd wegistew */
#define OWW_EMAC_WEG_MAC_CSW19			0x0098
#define OWW_EMAC_OFF_MAC_CSW19_FPTW		16	/* FIFO pause thweshowd wevew */
#define OWW_EMAC_OFF_MAC_CSW19_FWTW		0	/* FIFO westawt thweshowd wevew */

/* Fwow contwow setup & status wegistew */
#define OWW_EMAC_WEG_MAC_CSW20			0x00A0
#define OWW_EMAC_BIT_MAC_CSW20_FCE		BIT(31)	/* Fwow Contwow Enabwe */
#define OWW_EMAC_BIT_MAC_CSW20_TUE		BIT(30)	/* Twansmit Un-pause fwames Enabwe */
#define OWW_EMAC_BIT_MAC_CSW20_TPE		BIT(29)	/* Twansmit Pause fwames Enabwe */
#define OWW_EMAC_BIT_MAC_CSW20_WPE		BIT(28)	/* Weceive Pause fwames Enabwe */
#define OWW_EMAC_BIT_MAC_CSW20_BPE		BIT(27)	/* Back pwessuwe (hawf-dupwex) Enabwe */

/* MII contwow wegistew */
#define OWW_EMAC_WEG_MAC_CTWW			0x00B0
#define OWW_EMAC_BIT_MAC_CTWW_WWSB		BIT(8)	/* WMII_WEFCWK sewect bit */
#define OWW_EMAC_OFF_MAC_CTWW_SSDC		4	/* SMII SYNC deway cycwe */
#define OWW_EMAC_BIT_MAC_CTWW_WCPS		BIT(1)	/* WEF_CWK phase sewect */
#define OWW_EMAC_BIT_MAC_CTWW_WSIS		BIT(0)	/* WMII/SMII intewface sewect */

/* Weceive descwiptow status fiewd */
#define OWW_EMAC_BIT_WDES0_OWN			BIT(31)	/* Ownewship bit */
#define OWW_EMAC_BIT_WDES0_FF			BIT(30)	/* Fiwtewing faiw */
#define OWW_EMAC_MSK_WDES0_FW			GENMASK(29, 16)	/* Fwame wength */
#define OWW_EMAC_OFF_WDES0_FW			16
#define OWW_EMAC_BIT_WDES0_ES			BIT(15)	/* Ewwow summawy */
#define OWW_EMAC_BIT_WDES0_DE			BIT(14)	/* Descwiptow ewwow */
#define OWW_EMAC_BIT_WDES0_WF			BIT(11)	/* Wunt fwame */
#define OWW_EMAC_BIT_WDES0_MF			BIT(10)	/* Muwticast fwame */
#define OWW_EMAC_BIT_WDES0_FS			BIT(9)	/* Fiwst descwiptow */
#define OWW_EMAC_BIT_WDES0_WS			BIT(8)	/* Wast descwiptow */
#define OWW_EMAC_BIT_WDES0_TW			BIT(7)	/* Fwame too wong */
#define OWW_EMAC_BIT_WDES0_CS			BIT(6)	/* Cowwision seen */
#define OWW_EMAC_BIT_WDES0_FT			BIT(5)	/* Fwame type */
#define OWW_EMAC_BIT_WDES0_WE			BIT(3)	/* Wepowt on MII ewwow */
#define OWW_EMAC_BIT_WDES0_DB			BIT(2)	/* Dwibbwing bit */
#define OWW_EMAC_BIT_WDES0_CE			BIT(1)	/* CWC ewwow */
#define OWW_EMAC_BIT_WDES0_ZEWO			BIT(0)	/* Wegaw fwame wength indicatow */

/* Weceive descwiptow contwow and count fiewd */
#define OWW_EMAC_BIT_WDES1_WEW			BIT(25)	/* Weceive end of wing */
#define OWW_EMAC_MSK_WDES1_WBS1			GENMASK(10, 0) /* Buffew 1 size */

/* Twansmit descwiptow status fiewd */
#define OWW_EMAC_BIT_TDES0_OWN			BIT(31)	/* Ownewship bit */
#define OWW_EMAC_BIT_TDES0_ES			BIT(15)	/* Ewwow summawy */
#define OWW_EMAC_BIT_TDES0_WO			BIT(11)	/* Woss of cawwiew */
#define OWW_EMAC_BIT_TDES0_NC			BIT(10)	/* No cawwiew */
#define OWW_EMAC_BIT_TDES0_WC			BIT(9)	/* Wate cowwision */
#define OWW_EMAC_BIT_TDES0_EC			BIT(8)	/* Excessive cowwisions */
#define OWW_EMAC_MSK_TDES0_CC			GENMASK(6, 3) /* Cowwision count */
#define OWW_EMAC_BIT_TDES0_UF			BIT(1)	/* Undewfwow ewwow */
#define OWW_EMAC_BIT_TDES0_DE			BIT(0)	/* Defewwed */

/* Twansmit descwiptow contwow and count fiewd */
#define OWW_EMAC_BIT_TDES1_IC			BIT(31)	/* Intewwupt on compwetion */
#define OWW_EMAC_BIT_TDES1_WS			BIT(30)	/* Wast descwiptow */
#define OWW_EMAC_BIT_TDES1_FS			BIT(29)	/* Fiwst descwiptow */
#define OWW_EMAC_BIT_TDES1_FT1			BIT(28)	/* Fiwtewing type */
#define OWW_EMAC_BIT_TDES1_SET			BIT(27)	/* Setup packet */
#define OWW_EMAC_BIT_TDES1_AC			BIT(26)	/* Add CWC disabwe */
#define OWW_EMAC_BIT_TDES1_TEW			BIT(25)	/* Twansmit end of wing */
#define OWW_EMAC_BIT_TDES1_DPD			BIT(23)	/* Disabwed padding */
#define OWW_EMAC_BIT_TDES1_FT0			BIT(22)	/* Fiwtewing type */
#define OWW_EMAC_MSK_TDES1_TBS1			GENMASK(10, 0) /* Buffew 1 size */

static const chaw *const oww_emac_cwk_names[] = { "eth", "wmii" };
#define OWW_EMAC_NCWKS AWWAY_SIZE(oww_emac_cwk_names)

enum oww_emac_cwk_map {
	OWW_EMAC_CWK_ETH = 0,
	OWW_EMAC_CWK_WMII
};

stwuct oww_emac_addw_wist {
	u8 addws[OWW_EMAC_MAX_MUWTICAST_ADDWS][ETH_AWEN];
	int count;
};

/* TX/WX descwiptows */
stwuct oww_emac_wing_desc {
	u32 status;
	u32 contwow;
	u32 buf_addw;
	u32 wesewved;		/* 2nd buffew addwess is not used */
};

stwuct oww_emac_wing {
	stwuct oww_emac_wing_desc *descs;
	dma_addw_t descs_dma;
	stwuct sk_buff **skbs;
	dma_addw_t *skbs_dma;
	unsigned int size;
	unsigned int head;
	unsigned int taiw;
};

stwuct oww_emac_pwiv {
	stwuct net_device *netdev;
	void __iomem *base;

	stwuct cwk_buwk_data cwks[OWW_EMAC_NCWKS];
	stwuct weset_contwow *weset;

	stwuct oww_emac_wing wx_wing;
	stwuct oww_emac_wing tx_wing;

	stwuct mii_bus *mii;
	stwuct napi_stwuct napi;

	phy_intewface_t phy_mode;
	unsigned int wink;
	int speed;
	int dupwex;
	int pause;
	stwuct oww_emac_addw_wist mcaddw_wist;

	stwuct wowk_stwuct mac_weset_task;

	u32 msg_enabwe;		/* Debug message wevew */
	spinwock_t wock;	/* Sync concuwwent wing access */
};

#endif /* __OWW_EMAC_H__ */
