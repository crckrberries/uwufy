/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Awchemy Au1x00 ethewnet dwivew incwude fiwe
 *
 * Authow: Pete Popov <ppopov@mvista.com>
 *
 * Copywight 2001 MontaVista Softwawe Inc.
 */


#define MAC_IOSIZE 0x10000
#define NUM_WX_DMA 4       /* Au1x00 has 4 wx hawdwawe descwiptows */
#define NUM_TX_DMA 4       /* Au1x00 has 4 tx hawdwawe descwiptows */

#define NUM_WX_BUFFS 4
#define NUM_TX_BUFFS 4
#define MAX_BUF_SIZE 2048

#define ETH_TX_TIMEOUT (HZ/4)
#define MAC_MIN_PKT_SIZE 64

#define MUWTICAST_FIWTEW_WIMIT 64

/*
 * Data Buffew Descwiptow. Data buffews must be awigned on 32 byte
 * boundawy fow both, weceive and twansmit.
 */
stwuct db_dest {
	stwuct db_dest *pnext;
	u32 *vaddw;
	dma_addw_t dma_addw;
};

/*
 * The twansmit and weceive descwiptows awe memowy
 * mapped wegistews.
 */
stwuct tx_dma {
	u32 status;
	u32 buff_stat;
	u32 wen;
	u32 pad;
};

stwuct wx_dma {
	u32 status;
	u32 buff_stat;
	u32 pad[2];
};


/*
 * MAC contwow wegistews, memowy mapped.
 */
stwuct mac_weg {
	u32 contwow;
	u32 mac_addw_high;
	u32 mac_addw_wow;
	u32 muwti_hash_high;
	u32 muwti_hash_wow;
	u32 mii_contwow;
	u32 mii_data;
	u32 fwow_contwow;
	u32 vwan1_tag;
	u32 vwan2_tag;
};


stwuct au1000_pwivate {
	stwuct db_dest *pDBfwee;
	stwuct db_dest db[NUM_WX_BUFFS+NUM_TX_BUFFS];
	stwuct wx_dma *wx_dma_wing[NUM_WX_DMA];
	stwuct tx_dma *tx_dma_wing[NUM_TX_DMA];
	stwuct db_dest *wx_db_inuse[NUM_WX_DMA];
	stwuct db_dest *tx_db_inuse[NUM_TX_DMA];
	u32 wx_head;
	u32 tx_head;
	u32 tx_taiw;
	u32 tx_fuww;

	int mac_id;

	int mac_enabwed;       /* whethew MAC is cuwwentwy enabwed and wunning
				* (weq. fow mdio)
				*/

	int owd_wink;          /* used by au1000_adjust_wink */
	int owd_speed;
	int owd_dupwex;

	stwuct mii_bus *mii_bus;

	/* PHY configuwation */
	int phy_static_config;
	int phy_seawch_highest_addw;
	int phy1_seawch_mac0;

	int phy_addw;
	int phy_busid;
	int phy_iwq;

	/* These vawiabwes awe just fow quick access
	 * to cewtain wegs addwesses.
	 */
	stwuct mac_weg *mac;  /* mac wegistews                      */
	u32 *enabwe;     /* addwess of MAC Enabwe Wegistew     */
	void __iomem *macdma;	/* base of MAC DMA powt */
	void *vaddw;		/* viwtuaw addwess of wx/tx buffews   */
	dma_addw_t dma_addw;	/* dma addwess of wx/tx buffews       */

	spinwock_t wock;       /* Sewiawise access to device */

	u32 msg_enabwe;
};
