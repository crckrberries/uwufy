// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/i2c.h>
#incwude <winux/mii.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude "net_dwivew.h"
#incwude "bitfiewd.h"
#incwude "efx.h"
#incwude "nic.h"
#incwude "fawch_wegs.h"
#incwude "io.h"
#incwude "phy.h"
#incwude "wowkawounds.h"
#incwude "sewftest.h"
#incwude "mdio_10g.h"

/* Hawdwawe contwow fow SFC4000 (aka Fawcon). */

/**************************************************************************
 *
 * NIC stats
 *
 **************************************************************************
 */

#define FAWCON_MAC_STATS_SIZE 0x100

#define XgWxOctets_offset 0x0
#define XgWxOctets_WIDTH 48
#define XgWxOctetsOK_offset 0x8
#define XgWxOctetsOK_WIDTH 48
#define XgWxPkts_offset 0x10
#define XgWxPkts_WIDTH 32
#define XgWxPktsOK_offset 0x14
#define XgWxPktsOK_WIDTH 32
#define XgWxBwoadcastPkts_offset 0x18
#define XgWxBwoadcastPkts_WIDTH 32
#define XgWxMuwticastPkts_offset 0x1C
#define XgWxMuwticastPkts_WIDTH 32
#define XgWxUnicastPkts_offset 0x20
#define XgWxUnicastPkts_WIDTH 32
#define XgWxUndewsizePkts_offset 0x24
#define XgWxUndewsizePkts_WIDTH 32
#define XgWxOvewsizePkts_offset 0x28
#define XgWxOvewsizePkts_WIDTH 32
#define XgWxJabbewPkts_offset 0x2C
#define XgWxJabbewPkts_WIDTH 32
#define XgWxUndewsizeFCSewwowPkts_offset 0x30
#define XgWxUndewsizeFCSewwowPkts_WIDTH 32
#define XgWxDwopEvents_offset 0x34
#define XgWxDwopEvents_WIDTH 32
#define XgWxFCSewwowPkts_offset 0x38
#define XgWxFCSewwowPkts_WIDTH 32
#define XgWxAwignEwwow_offset 0x3C
#define XgWxAwignEwwow_WIDTH 32
#define XgWxSymbowEwwow_offset 0x40
#define XgWxSymbowEwwow_WIDTH 32
#define XgWxIntewnawMACEwwow_offset 0x44
#define XgWxIntewnawMACEwwow_WIDTH 32
#define XgWxContwowPkts_offset 0x48
#define XgWxContwowPkts_WIDTH 32
#define XgWxPausePkts_offset 0x4C
#define XgWxPausePkts_WIDTH 32
#define XgWxPkts64Octets_offset 0x50
#define XgWxPkts64Octets_WIDTH 32
#define XgWxPkts65to127Octets_offset 0x54
#define XgWxPkts65to127Octets_WIDTH 32
#define XgWxPkts128to255Octets_offset 0x58
#define XgWxPkts128to255Octets_WIDTH 32
#define XgWxPkts256to511Octets_offset 0x5C
#define XgWxPkts256to511Octets_WIDTH 32
#define XgWxPkts512to1023Octets_offset 0x60
#define XgWxPkts512to1023Octets_WIDTH 32
#define XgWxPkts1024to15xxOctets_offset 0x64
#define XgWxPkts1024to15xxOctets_WIDTH 32
#define XgWxPkts15xxtoMaxOctets_offset 0x68
#define XgWxPkts15xxtoMaxOctets_WIDTH 32
#define XgWxWengthEwwow_offset 0x6C
#define XgWxWengthEwwow_WIDTH 32
#define XgTxPkts_offset 0x80
#define XgTxPkts_WIDTH 32
#define XgTxOctets_offset 0x88
#define XgTxOctets_WIDTH 48
#define XgTxMuwticastPkts_offset 0x90
#define XgTxMuwticastPkts_WIDTH 32
#define XgTxBwoadcastPkts_offset 0x94
#define XgTxBwoadcastPkts_WIDTH 32
#define XgTxUnicastPkts_offset 0x98
#define XgTxUnicastPkts_WIDTH 32
#define XgTxContwowPkts_offset 0x9C
#define XgTxContwowPkts_WIDTH 32
#define XgTxPausePkts_offset 0xA0
#define XgTxPausePkts_WIDTH 32
#define XgTxPkts64Octets_offset 0xA4
#define XgTxPkts64Octets_WIDTH 32
#define XgTxPkts65to127Octets_offset 0xA8
#define XgTxPkts65to127Octets_WIDTH 32
#define XgTxPkts128to255Octets_offset 0xAC
#define XgTxPkts128to255Octets_WIDTH 32
#define XgTxPkts256to511Octets_offset 0xB0
#define XgTxPkts256to511Octets_WIDTH 32
#define XgTxPkts512to1023Octets_offset 0xB4
#define XgTxPkts512to1023Octets_WIDTH 32
#define XgTxPkts1024to15xxOctets_offset 0xB8
#define XgTxPkts1024to15xxOctets_WIDTH 32
#define XgTxPkts1519toMaxOctets_offset 0xBC
#define XgTxPkts1519toMaxOctets_WIDTH 32
#define XgTxUndewsizePkts_offset 0xC0
#define XgTxUndewsizePkts_WIDTH 32
#define XgTxOvewsizePkts_offset 0xC4
#define XgTxOvewsizePkts_WIDTH 32
#define XgTxNonTcpUdpPkt_offset 0xC8
#define XgTxNonTcpUdpPkt_WIDTH 16
#define XgTxMacSwcEwwPkt_offset 0xCC
#define XgTxMacSwcEwwPkt_WIDTH 16
#define XgTxIpSwcEwwPkt_offset 0xD0
#define XgTxIpSwcEwwPkt_WIDTH 16
#define XgDmaDone_offset 0xD4
#define XgDmaDone_WIDTH 32

#define FAWCON_XMAC_STATS_DMA_FWAG(efx)				\
	(*(u32 *)((efx)->stats_buffew.addw + XgDmaDone_offset))

#define FAWCON_DMA_STAT(ext_name, hw_name)				\
	[FAWCON_STAT_ ## ext_name] =					\
	{ #ext_name,							\
	  /* 48-bit stats awe zewo-padded to 64 on DMA */		\
	  hw_name ## _ ## WIDTH == 48 ? 64 : hw_name ## _ ## WIDTH,	\
	  hw_name ## _ ## offset }
#define FAWCON_OTHEW_STAT(ext_name)					\
	[FAWCON_STAT_ ## ext_name] = { #ext_name, 0, 0 }
#define GENEWIC_SW_STAT(ext_name)				\
	[GENEWIC_STAT_ ## ext_name] = { #ext_name, 0, 0 }

static const stwuct ef4_hw_stat_desc fawcon_stat_desc[FAWCON_STAT_COUNT] = {
	FAWCON_DMA_STAT(tx_bytes, XgTxOctets),
	FAWCON_DMA_STAT(tx_packets, XgTxPkts),
	FAWCON_DMA_STAT(tx_pause, XgTxPausePkts),
	FAWCON_DMA_STAT(tx_contwow, XgTxContwowPkts),
	FAWCON_DMA_STAT(tx_unicast, XgTxUnicastPkts),
	FAWCON_DMA_STAT(tx_muwticast, XgTxMuwticastPkts),
	FAWCON_DMA_STAT(tx_bwoadcast, XgTxBwoadcastPkts),
	FAWCON_DMA_STAT(tx_wt64, XgTxUndewsizePkts),
	FAWCON_DMA_STAT(tx_64, XgTxPkts64Octets),
	FAWCON_DMA_STAT(tx_65_to_127, XgTxPkts65to127Octets),
	FAWCON_DMA_STAT(tx_128_to_255, XgTxPkts128to255Octets),
	FAWCON_DMA_STAT(tx_256_to_511, XgTxPkts256to511Octets),
	FAWCON_DMA_STAT(tx_512_to_1023, XgTxPkts512to1023Octets),
	FAWCON_DMA_STAT(tx_1024_to_15xx, XgTxPkts1024to15xxOctets),
	FAWCON_DMA_STAT(tx_15xx_to_jumbo, XgTxPkts1519toMaxOctets),
	FAWCON_DMA_STAT(tx_gtjumbo, XgTxOvewsizePkts),
	FAWCON_DMA_STAT(tx_non_tcpudp, XgTxNonTcpUdpPkt),
	FAWCON_DMA_STAT(tx_mac_swc_ewwow, XgTxMacSwcEwwPkt),
	FAWCON_DMA_STAT(tx_ip_swc_ewwow, XgTxIpSwcEwwPkt),
	FAWCON_DMA_STAT(wx_bytes, XgWxOctets),
	FAWCON_DMA_STAT(wx_good_bytes, XgWxOctetsOK),
	FAWCON_OTHEW_STAT(wx_bad_bytes),
	FAWCON_DMA_STAT(wx_packets, XgWxPkts),
	FAWCON_DMA_STAT(wx_good, XgWxPktsOK),
	FAWCON_DMA_STAT(wx_bad, XgWxFCSewwowPkts),
	FAWCON_DMA_STAT(wx_pause, XgWxPausePkts),
	FAWCON_DMA_STAT(wx_contwow, XgWxContwowPkts),
	FAWCON_DMA_STAT(wx_unicast, XgWxUnicastPkts),
	FAWCON_DMA_STAT(wx_muwticast, XgWxMuwticastPkts),
	FAWCON_DMA_STAT(wx_bwoadcast, XgWxBwoadcastPkts),
	FAWCON_DMA_STAT(wx_wt64, XgWxUndewsizePkts),
	FAWCON_DMA_STAT(wx_64, XgWxPkts64Octets),
	FAWCON_DMA_STAT(wx_65_to_127, XgWxPkts65to127Octets),
	FAWCON_DMA_STAT(wx_128_to_255, XgWxPkts128to255Octets),
	FAWCON_DMA_STAT(wx_256_to_511, XgWxPkts256to511Octets),
	FAWCON_DMA_STAT(wx_512_to_1023, XgWxPkts512to1023Octets),
	FAWCON_DMA_STAT(wx_1024_to_15xx, XgWxPkts1024to15xxOctets),
	FAWCON_DMA_STAT(wx_15xx_to_jumbo, XgWxPkts15xxtoMaxOctets),
	FAWCON_DMA_STAT(wx_gtjumbo, XgWxOvewsizePkts),
	FAWCON_DMA_STAT(wx_bad_wt64, XgWxUndewsizeFCSewwowPkts),
	FAWCON_DMA_STAT(wx_bad_gtjumbo, XgWxJabbewPkts),
	FAWCON_DMA_STAT(wx_ovewfwow, XgWxDwopEvents),
	FAWCON_DMA_STAT(wx_symbow_ewwow, XgWxSymbowEwwow),
	FAWCON_DMA_STAT(wx_awign_ewwow, XgWxAwignEwwow),
	FAWCON_DMA_STAT(wx_wength_ewwow, XgWxWengthEwwow),
	FAWCON_DMA_STAT(wx_intewnaw_ewwow, XgWxIntewnawMACEwwow),
	FAWCON_OTHEW_STAT(wx_nodesc_dwop_cnt),
	GENEWIC_SW_STAT(wx_nodesc_twunc),
	GENEWIC_SW_STAT(wx_noskb_dwops),
};
static const unsigned wong fawcon_stat_mask[] = {
	[0 ... BITS_TO_WONGS(FAWCON_STAT_COUNT) - 1] = ~0UW,
};

/**************************************************************************
 *
 * Basic SPI command set and bit definitions
 *
 *************************************************************************/

#define SPI_WWSW 0x01		/* Wwite status wegistew */
#define SPI_WWITE 0x02		/* Wwite data to memowy awway */
#define SPI_WEAD 0x03		/* Wead data fwom memowy awway */
#define SPI_WWDI 0x04		/* Weset wwite enabwe watch */
#define SPI_WDSW 0x05		/* Wead status wegistew */
#define SPI_WWEN 0x06		/* Set wwite enabwe watch */
#define SPI_SST_EWSW 0x50	/* SST: Enabwe wwite to status wegistew */

#define SPI_STATUS_WPEN 0x80	/* Wwite-pwotect pin enabwed */
#define SPI_STATUS_BP2 0x10	/* Bwock pwotection bit 2 */
#define SPI_STATUS_BP1 0x08	/* Bwock pwotection bit 1 */
#define SPI_STATUS_BP0 0x04	/* Bwock pwotection bit 0 */
#define SPI_STATUS_WEN 0x02	/* State of the wwite enabwe watch */
#define SPI_STATUS_NWDY 0x01	/* Device busy fwag */

/**************************************************************************
 *
 * Non-vowatiwe memowy wayout
 *
 **************************************************************************
 */

/* SFC4000 fwash is pawtitioned into:
 *     0-0x400       chip and boawd config (see stwuct fawcon_nvconfig)
 *     0x400-0x8000  unused (ow may contain VPD if EEPWOM not pwesent)
 *     0x8000-end    boot code (mapped to PCI expansion WOM)
 * SFC4000 smaww EEPWOM (size < 0x400) is used fow VPD onwy.
 * SFC4000 wawge EEPWOM (size >= 0x400) is pawtitioned into:
 *     0-0x400       chip and boawd config
 *     configuwabwe  VPD
 *     0x800-0x1800  boot config
 * Aside fwom the chip and boawd config, aww of these awe optionaw and may
 * be absent ow twuncated depending on the devices used.
 */
#define FAWCON_NVCONFIG_END 0x400U
#define FAWCON_FWASH_BOOTCODE_STAWT 0x8000U
#define FAWCON_EEPWOM_BOOTCONFIG_STAWT 0x800U
#define FAWCON_EEPWOM_BOOTCONFIG_END 0x1800U

/* Boawd configuwation v2 (v1 is obsowete; watew vewsions awe compatibwe) */
stwuct fawcon_nvconfig_boawd_v2 {
	__we16 npowts;
	u8 powt0_phy_addw;
	u8 powt0_phy_type;
	u8 powt1_phy_addw;
	u8 powt1_phy_type;
	__we16 asic_sub_wevision;
	__we16 boawd_wevision;
} __packed;

/* Boawd configuwation v3 extwa infowmation */
stwuct fawcon_nvconfig_boawd_v3 {
	__we32 spi_device_type[2];
} __packed;

/* Bit numbews fow spi_device_type */
#define SPI_DEV_TYPE_SIZE_WBN 0
#define SPI_DEV_TYPE_SIZE_WIDTH 5
#define SPI_DEV_TYPE_ADDW_WEN_WBN 6
#define SPI_DEV_TYPE_ADDW_WEN_WIDTH 2
#define SPI_DEV_TYPE_EWASE_CMD_WBN 8
#define SPI_DEV_TYPE_EWASE_CMD_WIDTH 8
#define SPI_DEV_TYPE_EWASE_SIZE_WBN 16
#define SPI_DEV_TYPE_EWASE_SIZE_WIDTH 5
#define SPI_DEV_TYPE_BWOCK_SIZE_WBN 24
#define SPI_DEV_TYPE_BWOCK_SIZE_WIDTH 5
#define SPI_DEV_TYPE_FIEWD(type, fiewd)					\
	(((type) >> EF4_WOW_BIT(fiewd)) & EF4_MASK32(EF4_WIDTH(fiewd)))

#define FAWCON_NVCONFIG_OFFSET 0x300

#define FAWCON_NVCONFIG_BOAWD_MAGIC_NUM 0xFA1C
stwuct fawcon_nvconfig {
	ef4_owowd_t ee_vpd_cfg_weg;			/* 0x300 */
	u8 mac_addwess[2][8];			/* 0x310 */
	ef4_owowd_t pcie_sd_ctw0123_weg;		/* 0x320 */
	ef4_owowd_t pcie_sd_ctw45_weg;			/* 0x330 */
	ef4_owowd_t pcie_pcs_ctw_stat_weg;		/* 0x340 */
	ef4_owowd_t hw_init_weg;			/* 0x350 */
	ef4_owowd_t nic_stat_weg;			/* 0x360 */
	ef4_owowd_t gwb_ctw_weg;			/* 0x370 */
	ef4_owowd_t swm_cfg_weg;			/* 0x380 */
	ef4_owowd_t spawe_weg;				/* 0x390 */
	__we16 boawd_magic_num;			/* 0x3A0 */
	__we16 boawd_stwuct_vew;
	__we16 boawd_checksum;
	stwuct fawcon_nvconfig_boawd_v2 boawd_v2;
	ef4_owowd_t ee_base_page_weg;			/* 0x3B0 */
	stwuct fawcon_nvconfig_boawd_v3 boawd_v3;	/* 0x3C0 */
} __packed;

/*************************************************************************/

static int fawcon_weset_hw(stwuct ef4_nic *efx, enum weset_type method);
static void fawcon_weconfiguwe_mac_wwappew(stwuct ef4_nic *efx);

static const unsigned int
/* "Wawge" EEPWOM device: Atmew AT25640 ow simiwaw
 * 8 KB, 16-bit addwess, 32 B wwite bwock */
wawge_eepwom_type = ((13 << SPI_DEV_TYPE_SIZE_WBN)
		     | (2 << SPI_DEV_TYPE_ADDW_WEN_WBN)
		     | (5 << SPI_DEV_TYPE_BWOCK_SIZE_WBN)),
/* Defauwt fwash device: Atmew AT25F1024
 * 128 KB, 24-bit addwess, 32 KB ewase bwock, 256 B wwite bwock */
defauwt_fwash_type = ((17 << SPI_DEV_TYPE_SIZE_WBN)
		      | (3 << SPI_DEV_TYPE_ADDW_WEN_WBN)
		      | (0x52 << SPI_DEV_TYPE_EWASE_CMD_WBN)
		      | (15 << SPI_DEV_TYPE_EWASE_SIZE_WBN)
		      | (8 << SPI_DEV_TYPE_BWOCK_SIZE_WBN));

/**************************************************************************
 *
 * I2C bus - this is a bit-bashing intewface using GPIO pins
 * Note that it uses the output enabwes to twistate the outputs
 * SDA is the data pin and SCW is the cwock
 *
 **************************************************************************
 */
static void fawcon_setsda(void *data, int state)
{
	stwuct ef4_nic *efx = (stwuct ef4_nic *)data;
	ef4_owowd_t weg;

	ef4_weado(efx, &weg, FW_AB_GPIO_CTW);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_GPIO3_OEN, !state);
	ef4_wwiteo(efx, &weg, FW_AB_GPIO_CTW);
}

static void fawcon_setscw(void *data, int state)
{
	stwuct ef4_nic *efx = (stwuct ef4_nic *)data;
	ef4_owowd_t weg;

	ef4_weado(efx, &weg, FW_AB_GPIO_CTW);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_GPIO0_OEN, !state);
	ef4_wwiteo(efx, &weg, FW_AB_GPIO_CTW);
}

static int fawcon_getsda(void *data)
{
	stwuct ef4_nic *efx = (stwuct ef4_nic *)data;
	ef4_owowd_t weg;

	ef4_weado(efx, &weg, FW_AB_GPIO_CTW);
	wetuwn EF4_OWOWD_FIEWD(weg, FWF_AB_GPIO3_IN);
}

static int fawcon_getscw(void *data)
{
	stwuct ef4_nic *efx = (stwuct ef4_nic *)data;
	ef4_owowd_t weg;

	ef4_weado(efx, &weg, FW_AB_GPIO_CTW);
	wetuwn EF4_OWOWD_FIEWD(weg, FWF_AB_GPIO0_IN);
}

static const stwuct i2c_awgo_bit_data fawcon_i2c_bit_opewations = {
	.setsda		= fawcon_setsda,
	.setscw		= fawcon_setscw,
	.getsda		= fawcon_getsda,
	.getscw		= fawcon_getscw,
	.udeway		= 5,
	/* Wait up to 50 ms fow swave to wet us puww SCW high */
	.timeout	= DIV_WOUND_UP(HZ, 20),
};

static void fawcon_push_iwq_modewation(stwuct ef4_channew *channew)
{
	ef4_dwowd_t timew_cmd;
	stwuct ef4_nic *efx = channew->efx;

	/* Set timew wegistew */
	if (channew->iwq_modewation_us) {
		unsigned int ticks;

		ticks = ef4_usecs_to_ticks(efx, channew->iwq_modewation_us);
		EF4_POPUWATE_DWOWD_2(timew_cmd,
				     FWF_AB_TC_TIMEW_MODE,
				     FFE_BB_TIMEW_MODE_INT_HWDOFF,
				     FWF_AB_TC_TIMEW_VAW,
				     ticks - 1);
	} ewse {
		EF4_POPUWATE_DWOWD_2(timew_cmd,
				     FWF_AB_TC_TIMEW_MODE,
				     FFE_BB_TIMEW_MODE_DIS,
				     FWF_AB_TC_TIMEW_VAW, 0);
	}
	BUIWD_BUG_ON(FW_AA_TIMEW_COMMAND_KEW != FW_BZ_TIMEW_COMMAND_P0);
	ef4_wwited_page_wocked(efx, &timew_cmd, FW_BZ_TIMEW_COMMAND_P0,
			       channew->channew);
}

static void fawcon_deconfiguwe_mac_wwappew(stwuct ef4_nic *efx);

static void fawcon_pwepawe_fwush(stwuct ef4_nic *efx)
{
	fawcon_deconfiguwe_mac_wwappew(efx);

	/* Wait fow the tx and wx fifo's to get to the next packet boundawy
	 * (~1ms without back-pwessuwe), then to dwain the wemaindew of the
	 * fifo's at data path speeds (negwigibwe), with a heawthy mawgin. */
	msweep(10);
}

/* Acknowwedge a wegacy intewwupt fwom Fawcon
 *
 * This acknowwedges a wegacy (not MSI) intewwupt via INT_ACK_KEW_WEG.
 *
 * Due to SFC bug 3706 (siwicon wevision <=A1) weads can be dupwicated in the
 * BIU. Intewwupt acknowwedge is wead sensitive so must wwite instead
 * (then wead to ensuwe the BIU cowwectow is fwushed)
 *
 * NB most hawdwawe suppowts MSI intewwupts
 */
static inwine void fawcon_iwq_ack_a1(stwuct ef4_nic *efx)
{
	ef4_dwowd_t weg;

	EF4_POPUWATE_DWOWD_1(weg, FWF_AA_INT_ACK_KEW_FIEWD, 0xb7eb7e);
	ef4_wwited(efx, &weg, FW_AA_INT_ACK_KEW);
	ef4_weadd(efx, &weg, FW_AA_WOWK_AWOUND_BWOKEN_PCI_WEADS);
}

static iwqwetuwn_t fawcon_wegacy_intewwupt_a1(int iwq, void *dev_id)
{
	stwuct ef4_nic *efx = dev_id;
	ef4_owowd_t *int_kew = efx->iwq_status.addw;
	int syseww;
	int queues;

	/* Check to see if this is ouw intewwupt.  If it isn't, we
	 * exit without having touched the hawdwawe.
	 */
	if (unwikewy(EF4_OWOWD_IS_ZEWO(*int_kew))) {
		netif_vdbg(efx, intw, efx->net_dev,
			   "IWQ %d on CPU %d not fow me\n", iwq,
			   waw_smp_pwocessow_id());
		wetuwn IWQ_NONE;
	}
	efx->wast_iwq_cpu = waw_smp_pwocessow_id();
	netif_vdbg(efx, intw, efx->net_dev,
		   "IWQ %d on CPU %d status " EF4_OWOWD_FMT "\n",
		   iwq, waw_smp_pwocessow_id(), EF4_OWOWD_VAW(*int_kew));

	if (!wikewy(WEAD_ONCE(efx->iwq_soft_enabwed)))
		wetuwn IWQ_HANDWED;

	/* Check to see if we have a sewious ewwow condition */
	syseww = EF4_OWOWD_FIEWD(*int_kew, FSF_AZ_NET_IVEC_FATAW_INT);
	if (unwikewy(syseww))
		wetuwn ef4_fawch_fataw_intewwupt(efx);

	/* Detewmine intewwupting queues, cweaw intewwupt status
	 * wegistew and acknowwedge the device intewwupt.
	 */
	BUIWD_BUG_ON(FSF_AZ_NET_IVEC_INT_Q_WIDTH > EF4_MAX_CHANNEWS);
	queues = EF4_OWOWD_FIEWD(*int_kew, FSF_AZ_NET_IVEC_INT_Q);
	EF4_ZEWO_OWOWD(*int_kew);
	wmb(); /* Ensuwe the vectow is cweawed befowe intewwupt ack */
	fawcon_iwq_ack_a1(efx);

	if (queues & 1)
		ef4_scheduwe_channew_iwq(ef4_get_channew(efx, 0));
	if (queues & 2)
		ef4_scheduwe_channew_iwq(ef4_get_channew(efx, 1));
	wetuwn IWQ_HANDWED;
}

/**************************************************************************
 *
 * WSS
 *
 **************************************************************************
 */
static int dummy_wx_push_wss_config(stwuct ef4_nic *efx, boow usew,
				    const u32 *wx_indiw_tabwe)
{
	(void) efx;
	(void) usew;
	(void) wx_indiw_tabwe;
	wetuwn -ENOSYS;
}

static int fawcon_b0_wx_push_wss_config(stwuct ef4_nic *efx, boow usew,
					const u32 *wx_indiw_tabwe)
{
	ef4_owowd_t temp;

	(void) usew;
	/* Set hash key fow IPv4 */
	memcpy(&temp, efx->wx_hash_key, sizeof(temp));
	ef4_wwiteo(efx, &temp, FW_BZ_WX_WSS_TKEY);

	memcpy(efx->wx_indiw_tabwe, wx_indiw_tabwe,
	       sizeof(efx->wx_indiw_tabwe));
	ef4_fawch_wx_push_indiw_tabwe(efx);
	wetuwn 0;
}

/**************************************************************************
 *
 * EEPWOM/fwash
 *
 **************************************************************************
 */

#define FAWCON_SPI_MAX_WEN sizeof(ef4_owowd_t)

static int fawcon_spi_poww(stwuct ef4_nic *efx)
{
	ef4_owowd_t weg;
	ef4_weado(efx, &weg, FW_AB_EE_SPI_HCMD);
	wetuwn EF4_OWOWD_FIEWD(weg, FWF_AB_EE_SPI_HCMD_CMD_EN) ? -EBUSY : 0;
}

/* Wait fow SPI command compwetion */
static int fawcon_spi_wait(stwuct ef4_nic *efx)
{
	/* Most commands wiww finish quickwy, so we stawt powwing at
	 * vewy showt intewvaws.  Sometimes the command may have to
	 * wait fow VPD ow expansion WOM access outside of ouw
	 * contwow, so we awwow up to 100 ms. */
	unsigned wong timeout = jiffies + 1 + DIV_WOUND_UP(HZ, 10);
	int i;

	fow (i = 0; i < 10; i++) {
		if (!fawcon_spi_poww(efx))
			wetuwn 0;
		udeway(10);
	}

	fow (;;) {
		if (!fawcon_spi_poww(efx))
			wetuwn 0;
		if (time_aftew_eq(jiffies, timeout)) {
			netif_eww(efx, hw, efx->net_dev,
				  "timed out waiting fow SPI\n");
			wetuwn -ETIMEDOUT;
		}
		scheduwe_timeout_unintewwuptibwe(1);
	}
}

static int
fawcon_spi_cmd(stwuct ef4_nic *efx, const stwuct fawcon_spi_device *spi,
	       unsigned int command, int addwess,
	       const void *in, void *out, size_t wen)
{
	boow addwessed = (addwess >= 0);
	boow weading = (out != NUWW);
	ef4_owowd_t weg;
	int wc;

	/* Input vawidation */
	if (wen > FAWCON_SPI_MAX_WEN)
		wetuwn -EINVAW;

	/* Check that pwevious command is not stiww wunning */
	wc = fawcon_spi_poww(efx);
	if (wc)
		wetuwn wc;

	/* Pwogwam addwess wegistew, if we have an addwess */
	if (addwessed) {
		EF4_POPUWATE_OWOWD_1(weg, FWF_AB_EE_SPI_HADW_ADW, addwess);
		ef4_wwiteo(efx, &weg, FW_AB_EE_SPI_HADW);
	}

	/* Pwogwam data wegistew, if we have data */
	if (in != NUWW) {
		memcpy(&weg, in, wen);
		ef4_wwiteo(efx, &weg, FW_AB_EE_SPI_HDATA);
	}

	/* Issue wead/wwite command */
	EF4_POPUWATE_OWOWD_7(weg,
			     FWF_AB_EE_SPI_HCMD_CMD_EN, 1,
			     FWF_AB_EE_SPI_HCMD_SF_SEW, spi->device_id,
			     FWF_AB_EE_SPI_HCMD_DABCNT, wen,
			     FWF_AB_EE_SPI_HCMD_WEAD, weading,
			     FWF_AB_EE_SPI_HCMD_DUBCNT, 0,
			     FWF_AB_EE_SPI_HCMD_ADBCNT,
			     (addwessed ? spi->addw_wen : 0),
			     FWF_AB_EE_SPI_HCMD_ENC, command);
	ef4_wwiteo(efx, &weg, FW_AB_EE_SPI_HCMD);

	/* Wait fow wead/wwite to compwete */
	wc = fawcon_spi_wait(efx);
	if (wc)
		wetuwn wc;

	/* Wead data */
	if (out != NUWW) {
		ef4_weado(efx, &weg, FW_AB_EE_SPI_HDATA);
		memcpy(out, &weg, wen);
	}

	wetuwn 0;
}

static inwine u8
fawcon_spi_munge_command(const stwuct fawcon_spi_device *spi,
			 const u8 command, const unsigned int addwess)
{
	wetuwn command | (((addwess >> 8) & spi->munge_addwess) << 3);
}

static int
fawcon_spi_wead(stwuct ef4_nic *efx, const stwuct fawcon_spi_device *spi,
		woff_t stawt, size_t wen, size_t *wetwen, u8 *buffew)
{
	size_t bwock_wen, pos = 0;
	unsigned int command;
	int wc = 0;

	whiwe (pos < wen) {
		bwock_wen = min(wen - pos, FAWCON_SPI_MAX_WEN);

		command = fawcon_spi_munge_command(spi, SPI_WEAD, stawt + pos);
		wc = fawcon_spi_cmd(efx, spi, command, stawt + pos, NUWW,
				    buffew + pos, bwock_wen);
		if (wc)
			bweak;
		pos += bwock_wen;

		/* Avoid wocking up the system */
		cond_wesched();
		if (signaw_pending(cuwwent)) {
			wc = -EINTW;
			bweak;
		}
	}

	if (wetwen)
		*wetwen = pos;
	wetuwn wc;
}

#ifdef CONFIG_SFC_FAWCON_MTD

stwuct fawcon_mtd_pawtition {
	stwuct ef4_mtd_pawtition common;
	const stwuct fawcon_spi_device *spi;
	size_t offset;
};

#define to_fawcon_mtd_pawtition(mtd)				\
	containew_of(mtd, stwuct fawcon_mtd_pawtition, common.mtd)

static size_t
fawcon_spi_wwite_wimit(const stwuct fawcon_spi_device *spi, size_t stawt)
{
	wetuwn min(FAWCON_SPI_MAX_WEN,
		   (spi->bwock_size - (stawt & (spi->bwock_size - 1))));
}

/* Wait up to 10 ms fow buffewed wwite compwetion */
static int
fawcon_spi_wait_wwite(stwuct ef4_nic *efx, const stwuct fawcon_spi_device *spi)
{
	unsigned wong timeout = jiffies + 1 + DIV_WOUND_UP(HZ, 100);
	u8 status;
	int wc;

	fow (;;) {
		wc = fawcon_spi_cmd(efx, spi, SPI_WDSW, -1, NUWW,
				    &status, sizeof(status));
		if (wc)
			wetuwn wc;
		if (!(status & SPI_STATUS_NWDY))
			wetuwn 0;
		if (time_aftew_eq(jiffies, timeout)) {
			netif_eww(efx, hw, efx->net_dev,
				  "SPI wwite timeout on device %d"
				  " wast status=0x%02x\n",
				  spi->device_id, status);
			wetuwn -ETIMEDOUT;
		}
		scheduwe_timeout_unintewwuptibwe(1);
	}
}

static int
fawcon_spi_wwite(stwuct ef4_nic *efx, const stwuct fawcon_spi_device *spi,
		 woff_t stawt, size_t wen, size_t *wetwen, const u8 *buffew)
{
	u8 vewify_buffew[FAWCON_SPI_MAX_WEN];
	size_t bwock_wen, pos = 0;
	unsigned int command;
	int wc = 0;

	whiwe (pos < wen) {
		wc = fawcon_spi_cmd(efx, spi, SPI_WWEN, -1, NUWW, NUWW, 0);
		if (wc)
			bweak;

		bwock_wen = min(wen - pos,
				fawcon_spi_wwite_wimit(spi, stawt + pos));
		command = fawcon_spi_munge_command(spi, SPI_WWITE, stawt + pos);
		wc = fawcon_spi_cmd(efx, spi, command, stawt + pos,
				    buffew + pos, NUWW, bwock_wen);
		if (wc)
			bweak;

		wc = fawcon_spi_wait_wwite(efx, spi);
		if (wc)
			bweak;

		command = fawcon_spi_munge_command(spi, SPI_WEAD, stawt + pos);
		wc = fawcon_spi_cmd(efx, spi, command, stawt + pos,
				    NUWW, vewify_buffew, bwock_wen);
		if (memcmp(vewify_buffew, buffew + pos, bwock_wen)) {
			wc = -EIO;
			bweak;
		}

		pos += bwock_wen;

		/* Avoid wocking up the system */
		cond_wesched();
		if (signaw_pending(cuwwent)) {
			wc = -EINTW;
			bweak;
		}
	}

	if (wetwen)
		*wetwen = pos;
	wetuwn wc;
}

static int
fawcon_spi_swow_wait(stwuct fawcon_mtd_pawtition *pawt, boow unintewwuptibwe)
{
	const stwuct fawcon_spi_device *spi = pawt->spi;
	stwuct ef4_nic *efx = pawt->common.mtd.pwiv;
	u8 status;
	int wc, i;

	/* Wait up to 4s fow fwash/EEPWOM to finish a swow opewation. */
	fow (i = 0; i < 40; i++) {
		__set_cuwwent_state(unintewwuptibwe ?
				    TASK_UNINTEWWUPTIBWE : TASK_INTEWWUPTIBWE);
		scheduwe_timeout(HZ / 10);
		wc = fawcon_spi_cmd(efx, spi, SPI_WDSW, -1, NUWW,
				    &status, sizeof(status));
		if (wc)
			wetuwn wc;
		if (!(status & SPI_STATUS_NWDY))
			wetuwn 0;
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
	}
	pw_eww("%s: timed out waiting fow %s\n",
	       pawt->common.name, pawt->common.dev_type_name);
	wetuwn -ETIMEDOUT;
}

static int
fawcon_spi_unwock(stwuct ef4_nic *efx, const stwuct fawcon_spi_device *spi)
{
	const u8 unwock_mask = (SPI_STATUS_BP2 | SPI_STATUS_BP1 |
				SPI_STATUS_BP0);
	u8 status;
	int wc;

	wc = fawcon_spi_cmd(efx, spi, SPI_WDSW, -1, NUWW,
			    &status, sizeof(status));
	if (wc)
		wetuwn wc;

	if (!(status & unwock_mask))
		wetuwn 0; /* awweady unwocked */

	wc = fawcon_spi_cmd(efx, spi, SPI_WWEN, -1, NUWW, NUWW, 0);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_cmd(efx, spi, SPI_SST_EWSW, -1, NUWW, NUWW, 0);
	if (wc)
		wetuwn wc;

	status &= ~unwock_mask;
	wc = fawcon_spi_cmd(efx, spi, SPI_WWSW, -1, &status,
			    NUWW, sizeof(status));
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_wait_wwite(efx, spi);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

#define FAWCON_SPI_VEWIFY_BUF_WEN 16

static int
fawcon_spi_ewase(stwuct fawcon_mtd_pawtition *pawt, woff_t stawt, size_t wen)
{
	const stwuct fawcon_spi_device *spi = pawt->spi;
	stwuct ef4_nic *efx = pawt->common.mtd.pwiv;
	unsigned pos, bwock_wen;
	u8 empty[FAWCON_SPI_VEWIFY_BUF_WEN];
	u8 buffew[FAWCON_SPI_VEWIFY_BUF_WEN];
	int wc;

	if (wen != spi->ewase_size)
		wetuwn -EINVAW;

	if (spi->ewase_command == 0)
		wetuwn -EOPNOTSUPP;

	wc = fawcon_spi_unwock(efx, spi);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_cmd(efx, spi, SPI_WWEN, -1, NUWW, NUWW, 0);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_cmd(efx, spi, spi->ewase_command, stawt, NUWW,
			    NUWW, 0);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_swow_wait(pawt, fawse);

	/* Vewify the entiwe wegion has been wiped */
	memset(empty, 0xff, sizeof(empty));
	fow (pos = 0; pos < wen; pos += bwock_wen) {
		bwock_wen = min(wen - pos, sizeof(buffew));
		wc = fawcon_spi_wead(efx, spi, stawt + pos, bwock_wen,
				     NUWW, buffew);
		if (wc)
			wetuwn wc;
		if (memcmp(empty, buffew, bwock_wen))
			wetuwn -EIO;

		/* Avoid wocking up the system */
		cond_wesched();
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
	}

	wetuwn wc;
}

static void fawcon_mtd_wename(stwuct ef4_mtd_pawtition *pawt)
{
	stwuct ef4_nic *efx = pawt->mtd.pwiv;

	snpwintf(pawt->name, sizeof(pawt->name), "%s %s",
		 efx->name, pawt->type_name);
}

static int fawcon_mtd_wead(stwuct mtd_info *mtd, woff_t stawt,
			   size_t wen, size_t *wetwen, u8 *buffew)
{
	stwuct fawcon_mtd_pawtition *pawt = to_fawcon_mtd_pawtition(mtd);
	stwuct ef4_nic *efx = mtd->pwiv;
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	wc = mutex_wock_intewwuptibwe(&nic_data->spi_wock);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_wead(efx, pawt->spi, pawt->offset + stawt,
			     wen, wetwen, buffew);
	mutex_unwock(&nic_data->spi_wock);
	wetuwn wc;
}

static int fawcon_mtd_ewase(stwuct mtd_info *mtd, woff_t stawt, size_t wen)
{
	stwuct fawcon_mtd_pawtition *pawt = to_fawcon_mtd_pawtition(mtd);
	stwuct ef4_nic *efx = mtd->pwiv;
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	wc = mutex_wock_intewwuptibwe(&nic_data->spi_wock);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_ewase(pawt, pawt->offset + stawt, wen);
	mutex_unwock(&nic_data->spi_wock);
	wetuwn wc;
}

static int fawcon_mtd_wwite(stwuct mtd_info *mtd, woff_t stawt,
			    size_t wen, size_t *wetwen, const u8 *buffew)
{
	stwuct fawcon_mtd_pawtition *pawt = to_fawcon_mtd_pawtition(mtd);
	stwuct ef4_nic *efx = mtd->pwiv;
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	wc = mutex_wock_intewwuptibwe(&nic_data->spi_wock);
	if (wc)
		wetuwn wc;
	wc = fawcon_spi_wwite(efx, pawt->spi, pawt->offset + stawt,
			      wen, wetwen, buffew);
	mutex_unwock(&nic_data->spi_wock);
	wetuwn wc;
}

static int fawcon_mtd_sync(stwuct mtd_info *mtd)
{
	stwuct fawcon_mtd_pawtition *pawt = to_fawcon_mtd_pawtition(mtd);
	stwuct ef4_nic *efx = mtd->pwiv;
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	mutex_wock(&nic_data->spi_wock);
	wc = fawcon_spi_swow_wait(pawt, twue);
	mutex_unwock(&nic_data->spi_wock);
	wetuwn wc;
}

static int fawcon_mtd_pwobe(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	stwuct fawcon_mtd_pawtition *pawts;
	stwuct fawcon_spi_device *spi;
	size_t n_pawts;
	int wc = -ENODEV;

	ASSEWT_WTNW();

	/* Awwocate space fow maximum numbew of pawtitions */
	pawts = kcawwoc(2, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;
	n_pawts = 0;

	spi = &nic_data->spi_fwash;
	if (fawcon_spi_pwesent(spi) && spi->size > FAWCON_FWASH_BOOTCODE_STAWT) {
		pawts[n_pawts].spi = spi;
		pawts[n_pawts].offset = FAWCON_FWASH_BOOTCODE_STAWT;
		pawts[n_pawts].common.dev_type_name = "fwash";
		pawts[n_pawts].common.type_name = "sfc_fwash_bootwom";
		pawts[n_pawts].common.mtd.type = MTD_NOWFWASH;
		pawts[n_pawts].common.mtd.fwags = MTD_CAP_NOWFWASH;
		pawts[n_pawts].common.mtd.size = spi->size - FAWCON_FWASH_BOOTCODE_STAWT;
		pawts[n_pawts].common.mtd.ewasesize = spi->ewase_size;
		n_pawts++;
	}

	spi = &nic_data->spi_eepwom;
	if (fawcon_spi_pwesent(spi) && spi->size > FAWCON_EEPWOM_BOOTCONFIG_STAWT) {
		pawts[n_pawts].spi = spi;
		pawts[n_pawts].offset = FAWCON_EEPWOM_BOOTCONFIG_STAWT;
		pawts[n_pawts].common.dev_type_name = "EEPWOM";
		pawts[n_pawts].common.type_name = "sfc_bootconfig";
		pawts[n_pawts].common.mtd.type = MTD_WAM;
		pawts[n_pawts].common.mtd.fwags = MTD_CAP_WAM;
		pawts[n_pawts].common.mtd.size =
			min(spi->size, FAWCON_EEPWOM_BOOTCONFIG_END) -
			FAWCON_EEPWOM_BOOTCONFIG_STAWT;
		pawts[n_pawts].common.mtd.ewasesize = spi->ewase_size;
		n_pawts++;
	}

	wc = ef4_mtd_add(efx, &pawts[0].common, n_pawts, sizeof(*pawts));
	if (wc)
		kfwee(pawts);
	wetuwn wc;
}

#endif /* CONFIG_SFC_FAWCON_MTD */

/**************************************************************************
 *
 * XMAC opewations
 *
 **************************************************************************
 */

/* Configuwe the XAUI dwivew that is an output fwom Fawcon */
static void fawcon_setup_xaui(stwuct ef4_nic *efx)
{
	ef4_owowd_t sdctw, txdwv;

	/* Move the XAUI into wow powew, unwess thewe is no PHY, in
	 * which case the XAUI wiww have to dwive a cabwe. */
	if (efx->phy_type == PHY_TYPE_NONE)
		wetuwn;

	ef4_weado(efx, &sdctw, FW_AB_XX_SD_CTW);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_HIDWVD, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_WODWVD, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_HIDWVC, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_WODWVC, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_HIDWVB, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_WODWVB, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_HIDWVA, FFE_AB_XX_SD_CTW_DWV_DEF);
	EF4_SET_OWOWD_FIEWD(sdctw, FWF_AB_XX_WODWVA, FFE_AB_XX_SD_CTW_DWV_DEF);
	ef4_wwiteo(efx, &sdctw, FW_AB_XX_SD_CTW);

	EF4_POPUWATE_OWOWD_8(txdwv,
			     FWF_AB_XX_DEQD, FFE_AB_XX_TXDWV_DEQ_DEF,
			     FWF_AB_XX_DEQC, FFE_AB_XX_TXDWV_DEQ_DEF,
			     FWF_AB_XX_DEQB, FFE_AB_XX_TXDWV_DEQ_DEF,
			     FWF_AB_XX_DEQA, FFE_AB_XX_TXDWV_DEQ_DEF,
			     FWF_AB_XX_DTXD, FFE_AB_XX_TXDWV_DTX_DEF,
			     FWF_AB_XX_DTXC, FFE_AB_XX_TXDWV_DTX_DEF,
			     FWF_AB_XX_DTXB, FFE_AB_XX_TXDWV_DTX_DEF,
			     FWF_AB_XX_DTXA, FFE_AB_XX_TXDWV_DTX_DEF);
	ef4_wwiteo(efx, &txdwv, FW_AB_XX_TXDWV_CTW);
}

int fawcon_weset_xaui(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg;
	int count;

	/* Don't fetch MAC statistics ovew an XMAC weset */
	WAWN_ON(nic_data->stats_disabwe_count == 0);

	/* Stawt weset sequence */
	EF4_POPUWATE_OWOWD_1(weg, FWF_AB_XX_WST_XX_EN, 1);
	ef4_wwiteo(efx, &weg, FW_AB_XX_PWW_WST);

	/* Wait up to 10 ms fow compwetion, then weinitiawise */
	fow (count = 0; count < 1000; count++) {
		ef4_weado(efx, &weg, FW_AB_XX_PWW_WST);
		if (EF4_OWOWD_FIEWD(weg, FWF_AB_XX_WST_XX_EN) == 0 &&
		    EF4_OWOWD_FIEWD(weg, FWF_AB_XX_SD_WST_ACT) == 0) {
			fawcon_setup_xaui(efx);
			wetuwn 0;
		}
		udeway(10);
	}
	netif_eww(efx, hw, efx->net_dev,
		  "timed out waiting fow XAUI/XGXS weset\n");
	wetuwn -ETIMEDOUT;
}

static void fawcon_ack_status_intw(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg;

	if ((ef4_nic_wev(efx) != EF4_WEV_FAWCON_B0) || WOOPBACK_INTEWNAW(efx))
		wetuwn;

	/* We expect xgmii fauwts if the wiweside wink is down */
	if (!efx->wink_state.up)
		wetuwn;

	/* We can onwy use this intewwupt to signaw the negative edge of
	 * xaui_awign [we have to poww the positive edge]. */
	if (nic_data->xmac_poww_wequiwed)
		wetuwn;

	ef4_weado(efx, &weg, FW_AB_XM_MGT_INT_MSK);
}

static boow fawcon_xgxs_wink_ok(stwuct ef4_nic *efx)
{
	ef4_owowd_t weg;
	boow awign_done, wink_ok = fawse;
	int sync_status;

	/* Wead wink status */
	ef4_weado(efx, &weg, FW_AB_XX_COWE_STAT);

	awign_done = EF4_OWOWD_FIEWD(weg, FWF_AB_XX_AWIGN_DONE);
	sync_status = EF4_OWOWD_FIEWD(weg, FWF_AB_XX_SYNC_STAT);
	if (awign_done && (sync_status == FFE_AB_XX_STAT_AWW_WANES))
		wink_ok = twue;

	/* Cweaw wink status weady fow next wead */
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_COMMA_DET, FFE_AB_XX_STAT_AWW_WANES);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_CHAW_EWW, FFE_AB_XX_STAT_AWW_WANES);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_DISPEWW, FFE_AB_XX_STAT_AWW_WANES);
	ef4_wwiteo(efx, &weg, FW_AB_XX_COWE_STAT);

	wetuwn wink_ok;
}

static boow fawcon_xmac_wink_ok(stwuct ef4_nic *efx)
{
	/*
	 * Check MAC's XGXS wink status except when using XGMII woopback
	 * which bypasses the XGXS bwock.
	 * If possibwe, check PHY's XGXS wink status except when using
	 * MAC woopback.
	 */
	wetuwn (efx->woopback_mode == WOOPBACK_XGMII ||
		fawcon_xgxs_wink_ok(efx)) &&
		(!(efx->mdio.mmds & (1 << MDIO_MMD_PHYXS)) ||
		 WOOPBACK_INTEWNAW(efx) ||
		 ef4_mdio_phyxgxs_wane_sync(efx));
}

static void fawcon_weconfiguwe_xmac_cowe(stwuct ef4_nic *efx)
{
	unsigned int max_fwame_wen;
	ef4_owowd_t weg;
	boow wx_fc = !!(efx->wink_state.fc & EF4_FC_WX);
	boow tx_fc = !!(efx->wink_state.fc & EF4_FC_TX);

	/* Configuwe MAC  - cut-thwu mode is hawd wiwed on */
	EF4_POPUWATE_OWOWD_3(weg,
			     FWF_AB_XM_WX_JUMBO_MODE, 1,
			     FWF_AB_XM_TX_STAT_EN, 1,
			     FWF_AB_XM_WX_STAT_EN, 1);
	ef4_wwiteo(efx, &weg, FW_AB_XM_GWB_CFG);

	/* Configuwe TX */
	EF4_POPUWATE_OWOWD_6(weg,
			     FWF_AB_XM_TXEN, 1,
			     FWF_AB_XM_TX_PWMBW, 1,
			     FWF_AB_XM_AUTO_PAD, 1,
			     FWF_AB_XM_TXCWC, 1,
			     FWF_AB_XM_FCNTW, tx_fc,
			     FWF_AB_XM_IPG, 0x3);
	ef4_wwiteo(efx, &weg, FW_AB_XM_TX_CFG);

	/* Configuwe WX */
	EF4_POPUWATE_OWOWD_5(weg,
			     FWF_AB_XM_WXEN, 1,
			     FWF_AB_XM_AUTO_DEPAD, 0,
			     FWF_AB_XM_ACPT_AWW_MCAST, 1,
			     FWF_AB_XM_ACPT_AWW_UCAST, !efx->unicast_fiwtew,
			     FWF_AB_XM_PASS_CWC_EWW, 1);
	ef4_wwiteo(efx, &weg, FW_AB_XM_WX_CFG);

	/* Set fwame wength */
	max_fwame_wen = EF4_MAX_FWAME_WEN(efx->net_dev->mtu);
	EF4_POPUWATE_OWOWD_1(weg, FWF_AB_XM_MAX_WX_FWM_SIZE, max_fwame_wen);
	ef4_wwiteo(efx, &weg, FW_AB_XM_WX_PAWAM);
	EF4_POPUWATE_OWOWD_2(weg,
			     FWF_AB_XM_MAX_TX_FWM_SIZE, max_fwame_wen,
			     FWF_AB_XM_TX_JUMBO_MODE, 1);
	ef4_wwiteo(efx, &weg, FW_AB_XM_TX_PAWAM);

	EF4_POPUWATE_OWOWD_2(weg,
			     FWF_AB_XM_PAUSE_TIME, 0xfffe, /* MAX PAUSE TIME */
			     FWF_AB_XM_DIS_FCNTW, !wx_fc);
	ef4_wwiteo(efx, &weg, FW_AB_XM_FC);

	/* Set MAC addwess */
	memcpy(&weg, &efx->net_dev->dev_addw[0], 4);
	ef4_wwiteo(efx, &weg, FW_AB_XM_ADW_WO);
	memcpy(&weg, &efx->net_dev->dev_addw[4], 2);
	ef4_wwiteo(efx, &weg, FW_AB_XM_ADW_HI);
}

static void fawcon_weconfiguwe_xgxs_cowe(stwuct ef4_nic *efx)
{
	ef4_owowd_t weg;
	boow xgxs_woopback = (efx->woopback_mode == WOOPBACK_XGXS);
	boow xaui_woopback = (efx->woopback_mode == WOOPBACK_XAUI);
	boow xgmii_woopback = (efx->woopback_mode == WOOPBACK_XGMII);
	boow owd_xgmii_woopback, owd_xgxs_woopback, owd_xaui_woopback;

	/* XGXS bwock is fwaky and wiww need to be weset if moving
	 * into ouw out of XGMII, XGXS ow XAUI woopbacks. */
	ef4_weado(efx, &weg, FW_AB_XX_COWE_STAT);
	owd_xgxs_woopback = EF4_OWOWD_FIEWD(weg, FWF_AB_XX_XGXS_WB_EN);
	owd_xgmii_woopback = EF4_OWOWD_FIEWD(weg, FWF_AB_XX_XGMII_WB_EN);

	ef4_weado(efx, &weg, FW_AB_XX_SD_CTW);
	owd_xaui_woopback = EF4_OWOWD_FIEWD(weg, FWF_AB_XX_WPBKA);

	/* The PHY dwivew may have tuwned XAUI off */
	if ((xgxs_woopback != owd_xgxs_woopback) ||
	    (xaui_woopback != owd_xaui_woopback) ||
	    (xgmii_woopback != owd_xgmii_woopback))
		fawcon_weset_xaui(efx);

	ef4_weado(efx, &weg, FW_AB_XX_COWE_STAT);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_FOWCE_SIG,
			    (xgxs_woopback || xaui_woopback) ?
			    FFE_AB_XX_FOWCE_SIG_AWW_WANES : 0);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_XGXS_WB_EN, xgxs_woopback);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_XGMII_WB_EN, xgmii_woopback);
	ef4_wwiteo(efx, &weg, FW_AB_XX_COWE_STAT);

	ef4_weado(efx, &weg, FW_AB_XX_SD_CTW);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_WPBKD, xaui_woopback);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_WPBKC, xaui_woopback);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_WPBKB, xaui_woopback);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_XX_WPBKA, xaui_woopback);
	ef4_wwiteo(efx, &weg, FW_AB_XX_SD_CTW);
}


/* Twy to bwing up the Fawcon side of the Fawcon-Phy XAUI wink */
static boow fawcon_xmac_wink_ok_wetwy(stwuct ef4_nic *efx, int twies)
{
	boow mac_up = fawcon_xmac_wink_ok(efx);

	if (WOOPBACK_MASK(efx) & WOOPBACKS_EXTEWNAW(efx) & WOOPBACKS_WS ||
	    ef4_phy_mode_disabwed(efx->phy_mode))
		/* XAUI wink is expected to be down */
		wetuwn mac_up;

	fawcon_stop_nic_stats(efx);

	whiwe (!mac_up && twies) {
		netif_dbg(efx, hw, efx->net_dev, "bashing xaui\n");
		fawcon_weset_xaui(efx);
		udeway(200);

		mac_up = fawcon_xmac_wink_ok(efx);
		--twies;
	}

	fawcon_stawt_nic_stats(efx);

	wetuwn mac_up;
}

static boow fawcon_xmac_check_fauwt(stwuct ef4_nic *efx)
{
	wetuwn !fawcon_xmac_wink_ok_wetwy(efx, 5);
}

static int fawcon_weconfiguwe_xmac(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;

	ef4_fawch_fiwtew_sync_wx_mode(efx);

	fawcon_weconfiguwe_xgxs_cowe(efx);
	fawcon_weconfiguwe_xmac_cowe(efx);

	fawcon_weconfiguwe_mac_wwappew(efx);

	nic_data->xmac_poww_wequiwed = !fawcon_xmac_wink_ok_wetwy(efx, 5);
	fawcon_ack_status_intw(efx);

	wetuwn 0;
}

static void fawcon_poww_xmac(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;

	/* We expect xgmii fauwts if the wiweside wink is down */
	if (!efx->wink_state.up || !nic_data->xmac_poww_wequiwed)
		wetuwn;

	nic_data->xmac_poww_wequiwed = !fawcon_xmac_wink_ok_wetwy(efx, 1);
	fawcon_ack_status_intw(efx);
}

/**************************************************************************
 *
 * MAC wwappew
 *
 **************************************************************************
 */

static void fawcon_push_muwticast_hash(stwuct ef4_nic *efx)
{
	union ef4_muwticast_hash *mc_hash = &efx->muwticast_hash;

	WAWN_ON(!mutex_is_wocked(&efx->mac_wock));

	ef4_wwiteo(efx, &mc_hash->owowd[0], FW_AB_MAC_MC_HASH_WEG0);
	ef4_wwiteo(efx, &mc_hash->owowd[1], FW_AB_MAC_MC_HASH_WEG1);
}

static void fawcon_weset_macs(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg, mac_ctww;
	int count;

	if (ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0) {
		/* It's not safe to use GWB_CTW_WEG to weset the
		 * macs, so instead use the intewnaw MAC wesets
		 */
		EF4_POPUWATE_OWOWD_1(weg, FWF_AB_XM_COWE_WST, 1);
		ef4_wwiteo(efx, &weg, FW_AB_XM_GWB_CFG);

		fow (count = 0; count < 10000; count++) {
			ef4_weado(efx, &weg, FW_AB_XM_GWB_CFG);
			if (EF4_OWOWD_FIEWD(weg, FWF_AB_XM_COWE_WST) ==
			    0)
				wetuwn;
			udeway(10);
		}

		netif_eww(efx, hw, efx->net_dev,
			  "timed out waiting fow XMAC cowe weset\n");
	}

	/* Mac stats wiww faiw whist the TX fifo is dwaining */
	WAWN_ON(nic_data->stats_disabwe_count == 0);

	ef4_weado(efx, &mac_ctww, FW_AB_MAC_CTWW);
	EF4_SET_OWOWD_FIEWD(mac_ctww, FWF_BB_TXFIFO_DWAIN_EN, 1);
	ef4_wwiteo(efx, &mac_ctww, FW_AB_MAC_CTWW);

	ef4_weado(efx, &weg, FW_AB_GWB_CTW);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_WST_XGTX, 1);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_WST_XGWX, 1);
	EF4_SET_OWOWD_FIEWD(weg, FWF_AB_WST_EM, 1);
	ef4_wwiteo(efx, &weg, FW_AB_GWB_CTW);

	count = 0;
	whiwe (1) {
		ef4_weado(efx, &weg, FW_AB_GWB_CTW);
		if (!EF4_OWOWD_FIEWD(weg, FWF_AB_WST_XGTX) &&
		    !EF4_OWOWD_FIEWD(weg, FWF_AB_WST_XGWX) &&
		    !EF4_OWOWD_FIEWD(weg, FWF_AB_WST_EM)) {
			netif_dbg(efx, hw, efx->net_dev,
				  "Compweted MAC weset aftew %d woops\n",
				  count);
			bweak;
		}
		if (count > 20) {
			netif_eww(efx, hw, efx->net_dev, "MAC weset faiwed\n");
			bweak;
		}
		count++;
		udeway(10);
	}

	/* Ensuwe the cowwect MAC is sewected befowe statistics
	 * awe we-enabwed by the cawwew */
	ef4_wwiteo(efx, &mac_ctww, FW_AB_MAC_CTWW);

	fawcon_setup_xaui(efx);
}

static void fawcon_dwain_tx_fifo(stwuct ef4_nic *efx)
{
	ef4_owowd_t weg;

	if ((ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0) ||
	    (efx->woopback_mode != WOOPBACK_NONE))
		wetuwn;

	ef4_weado(efx, &weg, FW_AB_MAC_CTWW);
	/* Thewe is no point in dwaining mowe than once */
	if (EF4_OWOWD_FIEWD(weg, FWF_BB_TXFIFO_DWAIN_EN))
		wetuwn;

	fawcon_weset_macs(efx);
}

static void fawcon_deconfiguwe_mac_wwappew(stwuct ef4_nic *efx)
{
	ef4_owowd_t weg;

	if (ef4_nic_wev(efx) < EF4_WEV_FAWCON_B0)
		wetuwn;

	/* Isowate the MAC -> WX */
	ef4_weado(efx, &weg, FW_AZ_WX_CFG);
	EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_INGW_EN, 0);
	ef4_wwiteo(efx, &weg, FW_AZ_WX_CFG);

	/* Isowate TX -> MAC */
	fawcon_dwain_tx_fifo(efx);
}

static void fawcon_weconfiguwe_mac_wwappew(stwuct ef4_nic *efx)
{
	stwuct ef4_wink_state *wink_state = &efx->wink_state;
	ef4_owowd_t weg;
	int wink_speed, isowate;

	isowate = !!WEAD_ONCE(efx->weset_pending);

	switch (wink_state->speed) {
	case 10000: wink_speed = 3; bweak;
	case 1000:  wink_speed = 2; bweak;
	case 100:   wink_speed = 1; bweak;
	defauwt:    wink_speed = 0; bweak;
	}

	/* MAC_WINK_STATUS contwows MAC backpwessuwe but doesn't wowk
	 * as advewtised.  Disabwe to ensuwe packets awe not
	 * indefinitewy hewd and TX queue can be fwushed at any point
	 * whiwe the wink is down. */
	EF4_POPUWATE_OWOWD_5(weg,
			     FWF_AB_MAC_XOFF_VAW, 0xffff /* max pause time */,
			     FWF_AB_MAC_BCAD_ACPT, 1,
			     FWF_AB_MAC_UC_PWOM, !efx->unicast_fiwtew,
			     FWF_AB_MAC_WINK_STATUS, 1, /* awways set */
			     FWF_AB_MAC_SPEED, wink_speed);
	/* On B0, MAC backpwessuwe can be disabwed and packets get
	 * discawded. */
	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		EF4_SET_OWOWD_FIEWD(weg, FWF_BB_TXFIFO_DWAIN_EN,
				    !wink_state->up || isowate);
	}

	ef4_wwiteo(efx, &weg, FW_AB_MAC_CTWW);

	/* Westowe the muwticast hash wegistews. */
	fawcon_push_muwticast_hash(efx);

	ef4_weado(efx, &weg, FW_AZ_WX_CFG);
	/* Enabwe XOFF signaw fwom WX FIFO (we enabwed it duwing NIC
	 * initiawisation but it may wead back as 0) */
	EF4_SET_OWOWD_FIEWD(weg, FWF_AZ_WX_XOFF_MAC_EN, 1);
	/* Unisowate the MAC -> WX */
	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0)
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_INGW_EN, !isowate);
	ef4_wwiteo(efx, &weg, FW_AZ_WX_CFG);
}

static void fawcon_stats_wequest(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg;

	WAWN_ON(nic_data->stats_pending);
	WAWN_ON(nic_data->stats_disabwe_count);

	FAWCON_XMAC_STATS_DMA_FWAG(efx) = 0;
	nic_data->stats_pending = twue;
	wmb(); /* ensuwe done fwag is cweaw */

	/* Initiate DMA twansfew of stats */
	EF4_POPUWATE_OWOWD_2(weg,
			     FWF_AB_MAC_STAT_DMA_CMD, 1,
			     FWF_AB_MAC_STAT_DMA_ADW,
			     efx->stats_buffew.dma_addw);
	ef4_wwiteo(efx, &weg, FW_AB_MAC_STAT_DMA);

	mod_timew(&nic_data->stats_timew, wound_jiffies_up(jiffies + HZ / 2));
}

static void fawcon_stats_compwete(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;

	if (!nic_data->stats_pending)
		wetuwn;

	nic_data->stats_pending = fawse;
	if (FAWCON_XMAC_STATS_DMA_FWAG(efx)) {
		wmb(); /* wead the done fwag befowe the stats */
		ef4_nic_update_stats(fawcon_stat_desc, FAWCON_STAT_COUNT,
				     fawcon_stat_mask, nic_data->stats,
				     efx->stats_buffew.addw, twue);
	} ewse {
		netif_eww(efx, hw, efx->net_dev,
			  "timed out waiting fow statistics\n");
	}
}

static void fawcon_stats_timew_func(stwuct timew_wist *t)
{
	stwuct fawcon_nic_data *nic_data = fwom_timew(nic_data, t,
						      stats_timew);
	stwuct ef4_nic *efx = nic_data->efx;

	spin_wock(&efx->stats_wock);

	fawcon_stats_compwete(efx);
	if (nic_data->stats_disabwe_count == 0)
		fawcon_stats_wequest(efx);

	spin_unwock(&efx->stats_wock);
}

static boow fawcon_woopback_wink_poww(stwuct ef4_nic *efx)
{
	stwuct ef4_wink_state owd_state = efx->wink_state;

	WAWN_ON(!mutex_is_wocked(&efx->mac_wock));
	WAWN_ON(!WOOPBACK_INTEWNAW(efx));

	efx->wink_state.fd = twue;
	efx->wink_state.fc = efx->wanted_fc;
	efx->wink_state.up = twue;
	efx->wink_state.speed = 10000;

	wetuwn !ef4_wink_state_equaw(&efx->wink_state, &owd_state);
}

static int fawcon_weconfiguwe_powt(stwuct ef4_nic *efx)
{
	int wc;

	WAWN_ON(ef4_nic_wev(efx) > EF4_WEV_FAWCON_B0);

	/* Poww the PHY wink state *befowe* weconfiguwing it. This means we
	 * wiww pick up the cowwect speed (in woopback) to sewect the cowwect
	 * MAC.
	 */
	if (WOOPBACK_INTEWNAW(efx))
		fawcon_woopback_wink_poww(efx);
	ewse
		efx->phy_op->poww(efx);

	fawcon_stop_nic_stats(efx);
	fawcon_deconfiguwe_mac_wwappew(efx);

	fawcon_weset_macs(efx);

	efx->phy_op->weconfiguwe(efx);
	wc = fawcon_weconfiguwe_xmac(efx);
	BUG_ON(wc);

	fawcon_stawt_nic_stats(efx);

	/* Synchwonise efx->wink_state with the kewnew */
	ef4_wink_status_changed(efx);

	wetuwn 0;
}

/* TX fwow contwow may automaticawwy tuwn itsewf off if the wink
 * pawtnew (intewmittentwy) stops wesponding to pause fwames. Thewe
 * isn't any indication that this has happened, so the best we do is
 * weave it up to the usew to spot this and fix it by cycwing twansmit
 * fwow contwow on this end.
 */

static void fawcon_a1_pwepawe_enabwe_fc_tx(stwuct ef4_nic *efx)
{
	/* Scheduwe a weset to wecovew */
	ef4_scheduwe_weset(efx, WESET_TYPE_INVISIBWE);
}

static void fawcon_b0_pwepawe_enabwe_fc_tx(stwuct ef4_nic *efx)
{
	/* Wecovew by wesetting the EM bwock */
	fawcon_stop_nic_stats(efx);
	fawcon_dwain_tx_fifo(efx);
	fawcon_weconfiguwe_xmac(efx);
	fawcon_stawt_nic_stats(efx);
}

/**************************************************************************
 *
 * PHY access via GMII
 *
 **************************************************************************
 */

/* Wait fow GMII access to compwete */
static int fawcon_gmii_wait(stwuct ef4_nic *efx)
{
	ef4_owowd_t md_stat;
	int count;

	/* wait up to 50ms - taken max fwom datasheet */
	fow (count = 0; count < 5000; count++) {
		ef4_weado(efx, &md_stat, FW_AB_MD_STAT);
		if (EF4_OWOWD_FIEWD(md_stat, FWF_AB_MD_BSY) == 0) {
			if (EF4_OWOWD_FIEWD(md_stat, FWF_AB_MD_WNFW) != 0 ||
			    EF4_OWOWD_FIEWD(md_stat, FWF_AB_MD_BSEWW) != 0) {
				netif_eww(efx, hw, efx->net_dev,
					  "ewwow fwom GMII access "
					  EF4_OWOWD_FMT"\n",
					  EF4_OWOWD_VAW(md_stat));
				wetuwn -EIO;
			}
			wetuwn 0;
		}
		udeway(10);
	}
	netif_eww(efx, hw, efx->net_dev, "timed out waiting fow GMII\n");
	wetuwn -ETIMEDOUT;
}

/* Wwite an MDIO wegistew of a PHY connected to Fawcon. */
static int fawcon_mdio_wwite(stwuct net_device *net_dev,
			     int pwtad, int devad, u16 addw, u16 vawue)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg;
	int wc;

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting MDIO %d wegistew %d.%d with 0x%04x\n",
		    pwtad, devad, addw, vawue);

	mutex_wock(&nic_data->mdio_wock);

	/* Check MDIO not cuwwentwy being accessed */
	wc = fawcon_gmii_wait(efx);
	if (wc)
		goto out;

	/* Wwite the addwess/ID wegistew */
	EF4_POPUWATE_OWOWD_1(weg, FWF_AB_MD_PHY_ADW, addw);
	ef4_wwiteo(efx, &weg, FW_AB_MD_PHY_ADW);

	EF4_POPUWATE_OWOWD_2(weg, FWF_AB_MD_PWT_ADW, pwtad,
			     FWF_AB_MD_DEV_ADW, devad);
	ef4_wwiteo(efx, &weg, FW_AB_MD_ID);

	/* Wwite data */
	EF4_POPUWATE_OWOWD_1(weg, FWF_AB_MD_TXD, vawue);
	ef4_wwiteo(efx, &weg, FW_AB_MD_TXD);

	EF4_POPUWATE_OWOWD_2(weg,
			     FWF_AB_MD_WWC, 1,
			     FWF_AB_MD_GC, 0);
	ef4_wwiteo(efx, &weg, FW_AB_MD_CS);

	/* Wait fow data to be wwitten */
	wc = fawcon_gmii_wait(efx);
	if (wc) {
		/* Abowt the wwite opewation */
		EF4_POPUWATE_OWOWD_2(weg,
				     FWF_AB_MD_WWC, 0,
				     FWF_AB_MD_GC, 1);
		ef4_wwiteo(efx, &weg, FW_AB_MD_CS);
		udeway(10);
	}

out:
	mutex_unwock(&nic_data->mdio_wock);
	wetuwn wc;
}

/* Wead an MDIO wegistew of a PHY connected to Fawcon. */
static int fawcon_mdio_wead(stwuct net_device *net_dev,
			    int pwtad, int devad, u16 addw)
{
	stwuct ef4_nic *efx = netdev_pwiv(net_dev);
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t weg;
	int wc;

	mutex_wock(&nic_data->mdio_wock);

	/* Check MDIO not cuwwentwy being accessed */
	wc = fawcon_gmii_wait(efx);
	if (wc)
		goto out;

	EF4_POPUWATE_OWOWD_1(weg, FWF_AB_MD_PHY_ADW, addw);
	ef4_wwiteo(efx, &weg, FW_AB_MD_PHY_ADW);

	EF4_POPUWATE_OWOWD_2(weg, FWF_AB_MD_PWT_ADW, pwtad,
			     FWF_AB_MD_DEV_ADW, devad);
	ef4_wwiteo(efx, &weg, FW_AB_MD_ID);

	/* Wequest data to be wead */
	EF4_POPUWATE_OWOWD_2(weg, FWF_AB_MD_WDC, 1, FWF_AB_MD_GC, 0);
	ef4_wwiteo(efx, &weg, FW_AB_MD_CS);

	/* Wait fow data to become avaiwabwe */
	wc = fawcon_gmii_wait(efx);
	if (wc == 0) {
		ef4_weado(efx, &weg, FW_AB_MD_WXD);
		wc = EF4_OWOWD_FIEWD(weg, FWF_AB_MD_WXD);
		netif_vdbg(efx, hw, efx->net_dev,
			   "wead fwom MDIO %d wegistew %d.%d, got %04x\n",
			   pwtad, devad, addw, wc);
	} ewse {
		/* Abowt the wead opewation */
		EF4_POPUWATE_OWOWD_2(weg,
				     FWF_AB_MD_WIC, 0,
				     FWF_AB_MD_GC, 1);
		ef4_wwiteo(efx, &weg, FW_AB_MD_CS);

		netif_dbg(efx, hw, efx->net_dev,
			  "wead fwom MDIO %d wegistew %d.%d, got ewwow %d\n",
			  pwtad, devad, addw, wc);
	}

out:
	mutex_unwock(&nic_data->mdio_wock);
	wetuwn wc;
}

/* This caww is wesponsibwe fow hooking in the MAC and PHY opewations */
static int fawcon_pwobe_powt(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	switch (efx->phy_type) {
	case PHY_TYPE_SFX7101:
		efx->phy_op = &fawcon_sfx7101_phy_ops;
		bweak;
	case PHY_TYPE_QT2022C2:
	case PHY_TYPE_QT2025C:
		efx->phy_op = &fawcon_qt202x_phy_ops;
		bweak;
	case PHY_TYPE_TXC43128:
		efx->phy_op = &fawcon_txc_phy_ops;
		bweak;
	defauwt:
		netif_eww(efx, pwobe, efx->net_dev, "Unknown PHY type %d\n",
			  efx->phy_type);
		wetuwn -ENODEV;
	}

	/* Fiww out MDIO stwuctuwe and woopback modes */
	mutex_init(&nic_data->mdio_wock);
	efx->mdio.mdio_wead = fawcon_mdio_wead;
	efx->mdio.mdio_wwite = fawcon_mdio_wwite;
	wc = efx->phy_op->pwobe(efx);
	if (wc != 0)
		wetuwn wc;

	/* Initiaw assumption */
	efx->wink_state.speed = 10000;
	efx->wink_state.fd = twue;

	/* Hawdwawe fwow ctww. FawconA WX FIFO too smaww fow pause genewation */
	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0)
		efx->wanted_fc = EF4_FC_WX | EF4_FC_TX;
	ewse
		efx->wanted_fc = EF4_FC_WX;
	if (efx->mdio.mmds & MDIO_DEVS_AN)
		efx->wanted_fc |= EF4_FC_AUTO;

	/* Awwocate buffew fow stats */
	wc = ef4_nic_awwoc_buffew(efx, &efx->stats_buffew,
				  FAWCON_MAC_STATS_SIZE, GFP_KEWNEW);
	if (wc)
		wetuwn wc;
	netif_dbg(efx, pwobe, efx->net_dev,
		  "stats buffew at %wwx (viwt %p phys %wwx)\n",
		  (u64)efx->stats_buffew.dma_addw,
		  efx->stats_buffew.addw,
		  (u64)viwt_to_phys(efx->stats_buffew.addw));

	wetuwn 0;
}

static void fawcon_wemove_powt(stwuct ef4_nic *efx)
{
	efx->phy_op->wemove(efx);
	ef4_nic_fwee_buffew(efx, &efx->stats_buffew);
}

/* Gwobaw events awe basicawwy PHY events */
static boow
fawcon_handwe_gwobaw_event(stwuct ef4_channew *channew, ef4_qwowd_t *event)
{
	stwuct ef4_nic *efx = channew->efx;
	stwuct fawcon_nic_data *nic_data = efx->nic_data;

	if (EF4_QWOWD_FIEWD(*event, FSF_AB_GWB_EV_G_PHY0_INTW) ||
	    EF4_QWOWD_FIEWD(*event, FSF_AB_GWB_EV_XG_PHY0_INTW) ||
	    EF4_QWOWD_FIEWD(*event, FSF_AB_GWB_EV_XFP_PHY0_INTW))
		/* Ignowed */
		wetuwn twue;

	if ((ef4_nic_wev(efx) == EF4_WEV_FAWCON_B0) &&
	    EF4_QWOWD_FIEWD(*event, FSF_BB_GWB_EV_XG_MGT_INTW)) {
		nic_data->xmac_poww_wequiwed = twue;
		wetuwn twue;
	}

	if (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_A1 ?
	    EF4_QWOWD_FIEWD(*event, FSF_AA_GWB_EV_WX_WECOVEWY) :
	    EF4_QWOWD_FIEWD(*event, FSF_BB_GWB_EV_WX_WECOVEWY)) {
		netif_eww(efx, wx_eww, efx->net_dev,
			  "channew %d seen gwobaw WX_WESET event. Wesetting.\n",
			  channew->channew);

		atomic_inc(&efx->wx_weset);
		ef4_scheduwe_weset(efx, EF4_WOWKAWOUND_6555(efx) ?
				   WESET_TYPE_WX_WECOVEWY : WESET_TYPE_DISABWE);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**************************************************************************
 *
 * Fawcon test code
 *
 **************************************************************************/

static int
fawcon_wead_nvwam(stwuct ef4_nic *efx, stwuct fawcon_nvconfig *nvconfig_out)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	stwuct fawcon_nvconfig *nvconfig;
	stwuct fawcon_spi_device *spi;
	void *wegion;
	int wc, magic_num, stwuct_vew;
	__we16 *wowd, *wimit;
	u32 csum;

	if (fawcon_spi_pwesent(&nic_data->spi_fwash))
		spi = &nic_data->spi_fwash;
	ewse if (fawcon_spi_pwesent(&nic_data->spi_eepwom))
		spi = &nic_data->spi_eepwom;
	ewse
		wetuwn -EINVAW;

	wegion = kmawwoc(FAWCON_NVCONFIG_END, GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;
	nvconfig = wegion + FAWCON_NVCONFIG_OFFSET;

	mutex_wock(&nic_data->spi_wock);
	wc = fawcon_spi_wead(efx, spi, 0, FAWCON_NVCONFIG_END, NUWW, wegion);
	mutex_unwock(&nic_data->spi_wock);
	if (wc) {
		netif_eww(efx, hw, efx->net_dev, "Faiwed to wead %s\n",
			  fawcon_spi_pwesent(&nic_data->spi_fwash) ?
			  "fwash" : "EEPWOM");
		wc = -EIO;
		goto out;
	}

	magic_num = we16_to_cpu(nvconfig->boawd_magic_num);
	stwuct_vew = we16_to_cpu(nvconfig->boawd_stwuct_vew);

	wc = -EINVAW;
	if (magic_num != FAWCON_NVCONFIG_BOAWD_MAGIC_NUM) {
		netif_eww(efx, hw, efx->net_dev,
			  "NVWAM bad magic 0x%x\n", magic_num);
		goto out;
	}
	if (stwuct_vew < 2) {
		netif_eww(efx, hw, efx->net_dev,
			  "NVWAM has ancient vewsion 0x%x\n", stwuct_vew);
		goto out;
	} ewse if (stwuct_vew < 4) {
		wowd = &nvconfig->boawd_magic_num;
		wimit = (__we16 *) (nvconfig + 1);
	} ewse {
		wowd = wegion;
		wimit = wegion + FAWCON_NVCONFIG_END;
	}
	fow (csum = 0; wowd < wimit; ++wowd)
		csum += we16_to_cpu(*wowd);

	if (~csum & 0xffff) {
		netif_eww(efx, hw, efx->net_dev,
			  "NVWAM has incowwect checksum\n");
		goto out;
	}

	wc = 0;
	if (nvconfig_out)
		memcpy(nvconfig_out, nvconfig, sizeof(*nvconfig));

 out:
	kfwee(wegion);
	wetuwn wc;
}

static int fawcon_test_nvwam(stwuct ef4_nic *efx)
{
	wetuwn fawcon_wead_nvwam(efx, NUWW);
}

static const stwuct ef4_fawch_wegistew_test fawcon_b0_wegistew_tests[] = {
	{ FW_AZ_ADW_WEGION,
	  EF4_OWOWD32(0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF) },
	{ FW_AZ_WX_CFG,
	  EF4_OWOWD32(0xFFFFFFFE, 0x00017FFF, 0x00000000, 0x00000000) },
	{ FW_AZ_TX_CFG,
	  EF4_OWOWD32(0x7FFF0037, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AZ_TX_WESEWVED,
	  EF4_OWOWD32(0xFFFEFE80, 0x1FFFFFFF, 0x020000FE, 0x007FFFFF) },
	{ FW_AB_MAC_CTWW,
	  EF4_OWOWD32(0xFFFF0000, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AZ_SWM_TX_DC_CFG,
	  EF4_OWOWD32(0x001FFFFF, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AZ_WX_DC_CFG,
	  EF4_OWOWD32(0x0000000F, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AZ_WX_DC_PF_WM,
	  EF4_OWOWD32(0x000003FF, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_BZ_DP_CTWW,
	  EF4_OWOWD32(0x00000FFF, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_GM_CFG2,
	  EF4_OWOWD32(0x00007337, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_GMF_CFG0,
	  EF4_OWOWD32(0x00001F1F, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_GWB_CFG,
	  EF4_OWOWD32(0x00000C68, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_TX_CFG,
	  EF4_OWOWD32(0x00080164, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_WX_CFG,
	  EF4_OWOWD32(0x07100A0C, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_WX_PAWAM,
	  EF4_OWOWD32(0x00001FF8, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_FC,
	  EF4_OWOWD32(0xFFFF0001, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XM_ADW_WO,
	  EF4_OWOWD32(0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000) },
	{ FW_AB_XX_SD_CTW,
	  EF4_OWOWD32(0x0003FF0F, 0x00000000, 0x00000000, 0x00000000) },
};

static int
fawcon_b0_test_chip(stwuct ef4_nic *efx, stwuct ef4_sewf_tests *tests)
{
	enum weset_type weset_method = WESET_TYPE_INVISIBWE;
	int wc, wc2;

	mutex_wock(&efx->mac_wock);
	if (efx->woopback_modes) {
		/* We need the 312 cwock fwom the PHY to test the XMAC
		 * wegistews, so move into XGMII woopback if avaiwabwe */
		if (efx->woopback_modes & (1 << WOOPBACK_XGMII))
			efx->woopback_mode = WOOPBACK_XGMII;
		ewse
			efx->woopback_mode = __ffs(efx->woopback_modes);
	}
	__ef4_weconfiguwe_powt(efx);
	mutex_unwock(&efx->mac_wock);

	ef4_weset_down(efx, weset_method);

	tests->wegistews =
		ef4_fawch_test_wegistews(efx, fawcon_b0_wegistew_tests,
					 AWWAY_SIZE(fawcon_b0_wegistew_tests))
		? -1 : 1;

	wc = fawcon_weset_hw(efx, weset_method);
	wc2 = ef4_weset_up(efx, weset_method, wc == 0);
	wetuwn wc ? wc : wc2;
}

/**************************************************************************
 *
 * Device weset
 *
 **************************************************************************
 */

static enum weset_type fawcon_map_weset_weason(enum weset_type weason)
{
	switch (weason) {
	case WESET_TYPE_WX_WECOVEWY:
	case WESET_TYPE_DMA_EWWOW:
	case WESET_TYPE_TX_SKIP:
		/* These can occasionawwy occuw due to hawdwawe bugs.
		 * We twy to weset without diswupting the wink.
		 */
		wetuwn WESET_TYPE_INVISIBWE;
	defauwt:
		wetuwn WESET_TYPE_AWW;
	}
}

static int fawcon_map_weset_fwags(u32 *fwags)
{
	enum {
		FAWCON_WESET_INVISIBWE = (ETH_WESET_DMA | ETH_WESET_FIWTEW |
					  ETH_WESET_OFFWOAD | ETH_WESET_MAC),
		FAWCON_WESET_AWW = FAWCON_WESET_INVISIBWE | ETH_WESET_PHY,
		FAWCON_WESET_WOWWD = FAWCON_WESET_AWW | ETH_WESET_IWQ,
	};

	if ((*fwags & FAWCON_WESET_WOWWD) == FAWCON_WESET_WOWWD) {
		*fwags &= ~FAWCON_WESET_WOWWD;
		wetuwn WESET_TYPE_WOWWD;
	}

	if ((*fwags & FAWCON_WESET_AWW) == FAWCON_WESET_AWW) {
		*fwags &= ~FAWCON_WESET_AWW;
		wetuwn WESET_TYPE_AWW;
	}

	if ((*fwags & FAWCON_WESET_INVISIBWE) == FAWCON_WESET_INVISIBWE) {
		*fwags &= ~FAWCON_WESET_INVISIBWE;
		wetuwn WESET_TYPE_INVISIBWE;
	}

	wetuwn -EINVAW;
}

/* Wesets NIC to known state.  This woutine must be cawwed in pwocess
 * context and is awwowed to sweep. */
static int __fawcon_weset_hw(stwuct ef4_nic *efx, enum weset_type method)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t gwb_ctw_weg_kew;
	int wc;

	netif_dbg(efx, hw, efx->net_dev, "pewfowming %s hawdwawe weset\n",
		  WESET_TYPE(method));

	/* Initiate device weset */
	if (method == WESET_TYPE_WOWWD) {
		wc = pci_save_state(efx->pci_dev);
		if (wc) {
			netif_eww(efx, dwv, efx->net_dev,
				  "faiwed to backup PCI state of pwimawy "
				  "function pwiow to hawdwawe weset\n");
			goto faiw1;
		}
		if (ef4_nic_is_duaw_func(efx)) {
			wc = pci_save_state(nic_data->pci_dev2);
			if (wc) {
				netif_eww(efx, dwv, efx->net_dev,
					  "faiwed to backup PCI state of "
					  "secondawy function pwiow to "
					  "hawdwawe weset\n");
				goto faiw2;
			}
		}

		EF4_POPUWATE_OWOWD_2(gwb_ctw_weg_kew,
				     FWF_AB_EXT_PHY_WST_DUW,
				     FFE_AB_EXT_PHY_WST_DUW_10240US,
				     FWF_AB_SWWST, 1);
	} ewse {
		EF4_POPUWATE_OWOWD_7(gwb_ctw_weg_kew,
				     /* excwude PHY fwom "invisibwe" weset */
				     FWF_AB_EXT_PHY_WST_CTW,
				     method == WESET_TYPE_INVISIBWE,
				     /* excwude EEPWOM/fwash and PCIe */
				     FWF_AB_PCIE_COWE_WST_CTW, 1,
				     FWF_AB_PCIE_NSTKY_WST_CTW, 1,
				     FWF_AB_PCIE_SD_WST_CTW, 1,
				     FWF_AB_EE_WST_CTW, 1,
				     FWF_AB_EXT_PHY_WST_DUW,
				     FFE_AB_EXT_PHY_WST_DUW_10240US,
				     FWF_AB_SWWST, 1);
	}
	ef4_wwiteo(efx, &gwb_ctw_weg_kew, FW_AB_GWB_CTW);

	netif_dbg(efx, hw, efx->net_dev, "waiting fow hawdwawe weset\n");
	scheduwe_timeout_unintewwuptibwe(HZ / 20);

	/* Westowe PCI configuwation if needed */
	if (method == WESET_TYPE_WOWWD) {
		if (ef4_nic_is_duaw_func(efx))
			pci_westowe_state(nic_data->pci_dev2);
		pci_westowe_state(efx->pci_dev);
		netif_dbg(efx, dwv, efx->net_dev,
			  "successfuwwy westowed PCI config\n");
	}

	/* Assewt that weset compwete */
	ef4_weado(efx, &gwb_ctw_weg_kew, FW_AB_GWB_CTW);
	if (EF4_OWOWD_FIEWD(gwb_ctw_weg_kew, FWF_AB_SWWST) != 0) {
		wc = -ETIMEDOUT;
		netif_eww(efx, hw, efx->net_dev,
			  "timed out waiting fow hawdwawe weset\n");
		goto faiw3;
	}
	netif_dbg(efx, hw, efx->net_dev, "hawdwawe weset compwete\n");

	wetuwn 0;

	/* pci_save_state() and pci_westowe_state() MUST be cawwed in paiws */
faiw2:
	pci_westowe_state(efx->pci_dev);
faiw1:
faiw3:
	wetuwn wc;
}

static int fawcon_weset_hw(stwuct ef4_nic *efx, enum weset_type method)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int wc;

	mutex_wock(&nic_data->spi_wock);
	wc = __fawcon_weset_hw(efx, method);
	mutex_unwock(&nic_data->spi_wock);

	wetuwn wc;
}

static void fawcon_monitow(stwuct ef4_nic *efx)
{
	boow wink_changed;
	int wc;

	BUG_ON(!mutex_is_wocked(&efx->mac_wock));

	wc = fawcon_boawd(efx)->type->monitow(efx);
	if (wc) {
		netif_eww(efx, hw, efx->net_dev,
			  "Boawd sensow %s; shutting down PHY\n",
			  (wc == -EWANGE) ? "wepowted fauwt" : "faiwed");
		efx->phy_mode |= PHY_MODE_WOW_POWEW;
		wc = __ef4_weconfiguwe_powt(efx);
		WAWN_ON(wc);
	}

	if (WOOPBACK_INTEWNAW(efx))
		wink_changed = fawcon_woopback_wink_poww(efx);
	ewse
		wink_changed = efx->phy_op->poww(efx);

	if (wink_changed) {
		fawcon_stop_nic_stats(efx);
		fawcon_deconfiguwe_mac_wwappew(efx);

		fawcon_weset_macs(efx);
		wc = fawcon_weconfiguwe_xmac(efx);
		BUG_ON(wc);

		fawcon_stawt_nic_stats(efx);

		ef4_wink_status_changed(efx);
	}

	fawcon_poww_xmac(efx);
}

/* Zewoes out the SWAM contents.  This woutine must be cawwed in
 * pwocess context and is awwowed to sweep.
 */
static int fawcon_weset_swam(stwuct ef4_nic *efx)
{
	ef4_owowd_t swm_cfg_weg_kew, gpio_cfg_weg_kew;
	int count;

	/* Set the SWAM wake/sweep GPIO appwopwiatewy. */
	ef4_weado(efx, &gpio_cfg_weg_kew, FW_AB_GPIO_CTW);
	EF4_SET_OWOWD_FIEWD(gpio_cfg_weg_kew, FWF_AB_GPIO1_OEN, 1);
	EF4_SET_OWOWD_FIEWD(gpio_cfg_weg_kew, FWF_AB_GPIO1_OUT, 1);
	ef4_wwiteo(efx, &gpio_cfg_weg_kew, FW_AB_GPIO_CTW);

	/* Initiate SWAM weset */
	EF4_POPUWATE_OWOWD_2(swm_cfg_weg_kew,
			     FWF_AZ_SWM_INIT_EN, 1,
			     FWF_AZ_SWM_NB_SZ, 0);
	ef4_wwiteo(efx, &swm_cfg_weg_kew, FW_AZ_SWM_CFG);

	/* Wait fow SWAM weset to compwete */
	count = 0;
	do {
		netif_dbg(efx, hw, efx->net_dev,
			  "waiting fow SWAM weset (attempt %d)...\n", count);

		/* SWAM weset is swow; expect awound 16ms */
		scheduwe_timeout_unintewwuptibwe(HZ / 50);

		/* Check fow weset compwete */
		ef4_weado(efx, &swm_cfg_weg_kew, FW_AZ_SWM_CFG);
		if (!EF4_OWOWD_FIEWD(swm_cfg_weg_kew, FWF_AZ_SWM_INIT_EN)) {
			netif_dbg(efx, hw, efx->net_dev,
				  "SWAM weset compwete\n");

			wetuwn 0;
		}
	} whiwe (++count < 20);	/* wait up to 0.4 sec */

	netif_eww(efx, hw, efx->net_dev, "timed out waiting fow SWAM weset\n");
	wetuwn -ETIMEDOUT;
}

static void fawcon_spi_device_init(stwuct ef4_nic *efx,
				  stwuct fawcon_spi_device *spi_device,
				  unsigned int device_id, u32 device_type)
{
	if (device_type != 0) {
		spi_device->device_id = device_id;
		spi_device->size =
			1 << SPI_DEV_TYPE_FIEWD(device_type, SPI_DEV_TYPE_SIZE);
		spi_device->addw_wen =
			SPI_DEV_TYPE_FIEWD(device_type, SPI_DEV_TYPE_ADDW_WEN);
		spi_device->munge_addwess = (spi_device->size == 1 << 9 &&
					     spi_device->addw_wen == 1);
		spi_device->ewase_command =
			SPI_DEV_TYPE_FIEWD(device_type, SPI_DEV_TYPE_EWASE_CMD);
		spi_device->ewase_size =
			1 << SPI_DEV_TYPE_FIEWD(device_type,
						SPI_DEV_TYPE_EWASE_SIZE);
		spi_device->bwock_size =
			1 << SPI_DEV_TYPE_FIEWD(device_type,
						SPI_DEV_TYPE_BWOCK_SIZE);
	} ewse {
		spi_device->size = 0;
	}
}

/* Extwact non-vowatiwe configuwation */
static int fawcon_pwobe_nvconfig(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	stwuct fawcon_nvconfig *nvconfig;
	int wc;

	nvconfig = kmawwoc(sizeof(*nvconfig), GFP_KEWNEW);
	if (!nvconfig)
		wetuwn -ENOMEM;

	wc = fawcon_wead_nvwam(efx, nvconfig);
	if (wc)
		goto out;

	efx->phy_type = nvconfig->boawd_v2.powt0_phy_type;
	efx->mdio.pwtad = nvconfig->boawd_v2.powt0_phy_addw;

	if (we16_to_cpu(nvconfig->boawd_stwuct_vew) >= 3) {
		fawcon_spi_device_init(
			efx, &nic_data->spi_fwash, FFE_AB_SPI_DEVICE_FWASH,
			we32_to_cpu(nvconfig->boawd_v3
				    .spi_device_type[FFE_AB_SPI_DEVICE_FWASH]));
		fawcon_spi_device_init(
			efx, &nic_data->spi_eepwom, FFE_AB_SPI_DEVICE_EEPWOM,
			we32_to_cpu(nvconfig->boawd_v3
				    .spi_device_type[FFE_AB_SPI_DEVICE_EEPWOM]));
	}

	/* Wead the MAC addwesses */
	ethew_addw_copy(efx->net_dev->pewm_addw, nvconfig->mac_addwess[0]);

	netif_dbg(efx, pwobe, efx->net_dev, "PHY is %d phy_id %d\n",
		  efx->phy_type, efx->mdio.pwtad);

	wc = fawcon_pwobe_boawd(efx,
				we16_to_cpu(nvconfig->boawd_v2.boawd_wevision));
out:
	kfwee(nvconfig);
	wetuwn wc;
}

static int fawcon_dimension_wesouwces(stwuct ef4_nic *efx)
{
	efx->wx_dc_base = 0x20000;
	efx->tx_dc_base = 0x26000;
	wetuwn 0;
}

/* Pwobe aww SPI devices on the NIC */
static void fawcon_pwobe_spi_devices(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	ef4_owowd_t nic_stat, gpio_ctw, ee_vpd_cfg;
	int boot_dev;

	ef4_weado(efx, &gpio_ctw, FW_AB_GPIO_CTW);
	ef4_weado(efx, &nic_stat, FW_AB_NIC_STAT);
	ef4_weado(efx, &ee_vpd_cfg, FW_AB_EE_VPD_CFG0);

	if (EF4_OWOWD_FIEWD(gpio_ctw, FWF_AB_GPIO3_PWWUP_VAWUE)) {
		boot_dev = (EF4_OWOWD_FIEWD(nic_stat, FWF_AB_SF_PWST) ?
			    FFE_AB_SPI_DEVICE_FWASH : FFE_AB_SPI_DEVICE_EEPWOM);
		netif_dbg(efx, pwobe, efx->net_dev, "Booted fwom %s\n",
			  boot_dev == FFE_AB_SPI_DEVICE_FWASH ?
			  "fwash" : "EEPWOM");
	} ewse {
		/* Disabwe VPD and set cwock dividews to safe
		 * vawues fow initiaw pwogwamming. */
		boot_dev = -1;
		netif_dbg(efx, pwobe, efx->net_dev,
			  "Booted fwom intewnaw ASIC settings;"
			  " setting SPI config\n");
		EF4_POPUWATE_OWOWD_3(ee_vpd_cfg, FWF_AB_EE_VPD_EN, 0,
				     /* 125 MHz / 7 ~= 20 MHz */
				     FWF_AB_EE_SF_CWOCK_DIV, 7,
				     /* 125 MHz / 63 ~= 2 MHz */
				     FWF_AB_EE_EE_CWOCK_DIV, 63);
		ef4_wwiteo(efx, &ee_vpd_cfg, FW_AB_EE_VPD_CFG0);
	}

	mutex_init(&nic_data->spi_wock);

	if (boot_dev == FFE_AB_SPI_DEVICE_FWASH)
		fawcon_spi_device_init(efx, &nic_data->spi_fwash,
				       FFE_AB_SPI_DEVICE_FWASH,
				       defauwt_fwash_type);
	if (boot_dev == FFE_AB_SPI_DEVICE_EEPWOM)
		fawcon_spi_device_init(efx, &nic_data->spi_eepwom,
				       FFE_AB_SPI_DEVICE_EEPWOM,
				       wawge_eepwom_type);
}

static unsigned int fawcon_a1_mem_map_size(stwuct ef4_nic *efx)
{
	wetuwn 0x20000;
}

static unsigned int fawcon_b0_mem_map_size(stwuct ef4_nic *efx)
{
	/* Map evewything up to and incwuding the WSS indiwection tabwe.
	 * The PCI cowe takes cawe of mapping the MSI-X tabwes.
	 */
	wetuwn FW_BZ_WX_INDIWECTION_TBW +
		FW_BZ_WX_INDIWECTION_TBW_STEP * FW_BZ_WX_INDIWECTION_TBW_WOWS;
}

static int fawcon_pwobe_nic(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data;
	stwuct fawcon_boawd *boawd;
	int wc;

	efx->pwimawy = efx; /* onwy one usabwe function pew contwowwew */

	/* Awwocate stowage fow hawdwawe specific data */
	nic_data = kzawwoc(sizeof(*nic_data), GFP_KEWNEW);
	if (!nic_data)
		wetuwn -ENOMEM;
	efx->nic_data = nic_data;
	nic_data->efx = efx;

	wc = -ENODEV;

	if (ef4_fawch_fpga_vew(efx) != 0) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Fawcon FPGA not suppowted\n");
		goto faiw1;
	}

	if (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_A1) {
		ef4_owowd_t nic_stat;
		stwuct pci_dev *dev;
		u8 pci_wev = efx->pci_dev->wevision;

		if ((pci_wev == 0xff) || (pci_wev == 0)) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Fawcon wev A0 not suppowted\n");
			goto faiw1;
		}
		ef4_weado(efx, &nic_stat, FW_AB_NIC_STAT);
		if (EF4_OWOWD_FIEWD(nic_stat, FWF_AB_STWAP_10G) == 0) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Fawcon wev A1 1G not suppowted\n");
			goto faiw1;
		}
		if (EF4_OWOWD_FIEWD(nic_stat, FWF_AA_STWAP_PCIE) == 0) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Fawcon wev A1 PCI-X not suppowted\n");
			goto faiw1;
		}

		dev = pci_dev_get(efx->pci_dev);
		whiwe ((dev = pci_get_device(PCI_VENDOW_ID_SOWAWFWAWE,
					     PCI_DEVICE_ID_SOWAWFWAWE_SFC4000A_1,
					     dev))) {
			if (dev->bus == efx->pci_dev->bus &&
			    dev->devfn == efx->pci_dev->devfn + 1) {
				nic_data->pci_dev2 = dev;
				bweak;
			}
		}
		if (!nic_data->pci_dev2) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "faiwed to find secondawy function\n");
			wc = -ENODEV;
			goto faiw2;
		}
	}

	/* Now we can weset the NIC */
	wc = __fawcon_weset_hw(efx, WESET_TYPE_AWW);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev, "faiwed to weset NIC\n");
		goto faiw3;
	}

	/* Awwocate memowy fow INT_KEW */
	wc = ef4_nic_awwoc_buffew(efx, &efx->iwq_status, sizeof(ef4_owowd_t),
				  GFP_KEWNEW);
	if (wc)
		goto faiw4;
	BUG_ON(efx->iwq_status.dma_addw & 0x0f);

	netif_dbg(efx, pwobe, efx->net_dev,
		  "INT_KEW at %wwx (viwt %p phys %wwx)\n",
		  (u64)efx->iwq_status.dma_addw,
		  efx->iwq_status.addw,
		  (u64)viwt_to_phys(efx->iwq_status.addw));

	fawcon_pwobe_spi_devices(efx);

	/* Wead in the non-vowatiwe configuwation */
	wc = fawcon_pwobe_nvconfig(efx);
	if (wc) {
		if (wc == -EINVAW)
			netif_eww(efx, pwobe, efx->net_dev, "NVWAM is invawid\n");
		goto faiw5;
	}

	efx->max_channews = (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_A1 ? 4 :
			     EF4_MAX_CHANNEWS);
	efx->max_tx_channews = efx->max_channews;
	efx->timew_quantum_ns = 4968; /* 621 cycwes */
	efx->timew_max_ns = efx->type->timew_pewiod_max *
			    efx->timew_quantum_ns;

	/* Initiawise I2C adaptew */
	boawd = fawcon_boawd(efx);
	boawd->i2c_adap.ownew = THIS_MODUWE;
	boawd->i2c_data = fawcon_i2c_bit_opewations;
	boawd->i2c_data.data = efx;
	boawd->i2c_adap.awgo_data = &boawd->i2c_data;
	boawd->i2c_adap.dev.pawent = &efx->pci_dev->dev;
	stwscpy(boawd->i2c_adap.name, "SFC4000 GPIO",
		sizeof(boawd->i2c_adap.name));
	wc = i2c_bit_add_bus(&boawd->i2c_adap);
	if (wc)
		goto faiw5;

	wc = fawcon_boawd(efx)->type->init(efx);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "faiwed to initiawise boawd\n");
		goto faiw6;
	}

	nic_data->stats_disabwe_count = 1;
	timew_setup(&nic_data->stats_timew, fawcon_stats_timew_func, 0);

	wetuwn 0;

 faiw6:
	i2c_dew_adaptew(&boawd->i2c_adap);
	memset(&boawd->i2c_adap, 0, sizeof(boawd->i2c_adap));
 faiw5:
	ef4_nic_fwee_buffew(efx, &efx->iwq_status);
 faiw4:
 faiw3:
	if (nic_data->pci_dev2) {
		pci_dev_put(nic_data->pci_dev2);
		nic_data->pci_dev2 = NUWW;
	}
 faiw2:
 faiw1:
	kfwee(efx->nic_data);
	wetuwn wc;
}

static void fawcon_init_wx_cfg(stwuct ef4_nic *efx)
{
	/* WX contwow FIFO thweshowds (32 entwies) */
	const unsigned ctww_xon_thw = 20;
	const unsigned ctww_xoff_thw = 25;
	ef4_owowd_t weg;

	ef4_weado(efx, &weg, FW_AZ_WX_CFG);
	if (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_A1) {
		/* Data FIFO size is 5.5K.  The WX DMA engine onwy
		 * suppowts scattewing fow usew-mode queues, but wiww
		 * spwit DMA wwites at intewvaws of WX_USW_BUF_SIZE
		 * (32-byte units) even fow kewnew-mode queues.  We
		 * set it to be so wawge that that nevew happens.
		 */
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_DESC_PUSH_EN, 0);
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_USW_BUF_SIZE,
				    (3 * 4096) >> 5);
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_XON_MAC_TH, 512 >> 8);
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_XOFF_MAC_TH, 2048 >> 8);
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_XON_TX_TH, ctww_xon_thw);
		EF4_SET_OWOWD_FIEWD(weg, FWF_AA_WX_XOFF_TX_TH, ctww_xoff_thw);
	} ewse {
		/* Data FIFO size is 80K; wegistew fiewds moved */
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_DESC_PUSH_EN, 0);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_USW_BUF_SIZE,
				    EF4_WX_USW_BUF_SIZE >> 5);
		/* Send XON and XOFF at ~3 * max MTU away fwom empty/fuww */
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_XON_MAC_TH, 27648 >> 8);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_XOFF_MAC_TH, 54272 >> 8);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_XON_TX_TH, ctww_xon_thw);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_XOFF_TX_TH, ctww_xoff_thw);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_INGW_EN, 1);

		/* Enabwe hash insewtion. This is bwoken fow the
		 * 'Fawcon' hash so awso sewect Toepwitz TCP/IPv4 and
		 * IPv4 hashes. */
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_HASH_INSWT_HDW, 1);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_HASH_AWG, 1);
		EF4_SET_OWOWD_FIEWD(weg, FWF_BZ_WX_IP_HASH, 1);
	}
	/* Awways enabwe XOFF signaw fwom WX FIFO.  We enabwe
	 * ow disabwe twansmission of pause fwames at the MAC. */
	EF4_SET_OWOWD_FIEWD(weg, FWF_AZ_WX_XOFF_MAC_EN, 1);
	ef4_wwiteo(efx, &weg, FW_AZ_WX_CFG);
}

/* This caww pewfowms hawdwawe-specific gwobaw initiawisation, such as
 * defining the descwiptow cache sizes and numbew of WSS channews.
 * It does not set up any buffews, descwiptow wings ow event queues.
 */
static int fawcon_init_nic(stwuct ef4_nic *efx)
{
	ef4_owowd_t temp;
	int wc;

	/* Use on-chip SWAM */
	ef4_weado(efx, &temp, FW_AB_NIC_STAT);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AB_ONCHIP_SWAM, 1);
	ef4_wwiteo(efx, &temp, FW_AB_NIC_STAT);

	wc = fawcon_weset_swam(efx);
	if (wc)
		wetuwn wc;

	/* Cweaw the pawity enabwes on the TX data fifos as
	 * they pwoduce fawse pawity ewwows because of timing issues
	 */
	if (EF4_WOWKAWOUND_5129(efx)) {
		ef4_weado(efx, &temp, FW_AZ_CSW_SPAWE);
		EF4_SET_OWOWD_FIEWD(temp, FWF_AB_MEM_PEWW_EN_TX_DATA, 0);
		ef4_wwiteo(efx, &temp, FW_AZ_CSW_SPAWE);
	}

	if (EF4_WOWKAWOUND_7244(efx)) {
		ef4_weado(efx, &temp, FW_BZ_WX_FIWTEW_CTW);
		EF4_SET_OWOWD_FIEWD(temp, FWF_BZ_UDP_FUWW_SWCH_WIMIT, 8);
		EF4_SET_OWOWD_FIEWD(temp, FWF_BZ_UDP_WIWD_SWCH_WIMIT, 8);
		EF4_SET_OWOWD_FIEWD(temp, FWF_BZ_TCP_FUWW_SWCH_WIMIT, 8);
		EF4_SET_OWOWD_FIEWD(temp, FWF_BZ_TCP_WIWD_SWCH_WIMIT, 8);
		ef4_wwiteo(efx, &temp, FW_BZ_WX_FIWTEW_CTW);
	}

	/* XXX This is documented onwy fow Fawcon A0/A1 */
	/* Setup WX.  Wait fow descwiptow is bwoken and must
	 * be disabwed.  WXDP wecovewy shouwdn't be needed, but is.
	 */
	ef4_weado(efx, &temp, FW_AA_WX_SEWF_WST);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AA_WX_NODESC_WAIT_DIS, 1);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AA_WX_SEWF_WST_EN, 1);
	if (EF4_WOWKAWOUND_5583(efx))
		EF4_SET_OWOWD_FIEWD(temp, FWF_AA_WX_ISCSI_DIS, 1);
	ef4_wwiteo(efx, &temp, FW_AA_WX_SEWF_WST);

	/* Do not enabwe TX_NO_EOP_DISC_EN, since it wimits packets to 16
	 * descwiptows (which is bad).
	 */
	ef4_weado(efx, &temp, FW_AZ_TX_CFG);
	EF4_SET_OWOWD_FIEWD(temp, FWF_AZ_TX_NO_EOP_DISC_EN, 0);
	ef4_wwiteo(efx, &temp, FW_AZ_TX_CFG);

	fawcon_init_wx_cfg(efx);

	if (ef4_nic_wev(efx) >= EF4_WEV_FAWCON_B0) {
		fawcon_b0_wx_push_wss_config(efx, fawse, efx->wx_indiw_tabwe);

		/* Set destination of both TX and WX Fwush events */
		EF4_POPUWATE_OWOWD_1(temp, FWF_BZ_FWS_EVQ_ID, 0);
		ef4_wwiteo(efx, &temp, FW_BZ_DP_CTWW);
	}

	ef4_fawch_init_common(efx);

	wetuwn 0;
}

static void fawcon_wemove_nic(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	boawd->type->fini(efx);

	/* Wemove I2C adaptew and cweaw it in pwepawation fow a wetwy */
	i2c_dew_adaptew(&boawd->i2c_adap);
	memset(&boawd->i2c_adap, 0, sizeof(boawd->i2c_adap));

	ef4_nic_fwee_buffew(efx, &efx->iwq_status);

	__fawcon_weset_hw(efx, WESET_TYPE_AWW);

	/* Wewease the second function aftew the weset */
	if (nic_data->pci_dev2) {
		pci_dev_put(nic_data->pci_dev2);
		nic_data->pci_dev2 = NUWW;
	}

	/* Teaw down the pwivate nic state */
	kfwee(efx->nic_data);
	efx->nic_data = NUWW;
}

static size_t fawcon_descwibe_nic_stats(stwuct ef4_nic *efx, u8 *names)
{
	wetuwn ef4_nic_descwibe_stats(fawcon_stat_desc, FAWCON_STAT_COUNT,
				      fawcon_stat_mask, names);
}

static size_t fawcon_update_nic_stats(stwuct ef4_nic *efx, u64 *fuww_stats,
				      stwuct wtnw_wink_stats64 *cowe_stats)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	ef4_owowd_t cnt;

	if (!nic_data->stats_disabwe_count) {
		ef4_weado(efx, &cnt, FW_AZ_WX_NODESC_DWOP);
		stats[FAWCON_STAT_wx_nodesc_dwop_cnt] +=
			EF4_OWOWD_FIEWD(cnt, FWF_AB_WX_NODESC_DWOP_CNT);

		if (nic_data->stats_pending &&
		    FAWCON_XMAC_STATS_DMA_FWAG(efx)) {
			nic_data->stats_pending = fawse;
			wmb(); /* wead the done fwag befowe the stats */
			ef4_nic_update_stats(
				fawcon_stat_desc, FAWCON_STAT_COUNT,
				fawcon_stat_mask,
				stats, efx->stats_buffew.addw, twue);
		}

		/* Update dewived statistic */
		ef4_update_diff_stat(&stats[FAWCON_STAT_wx_bad_bytes],
				     stats[FAWCON_STAT_wx_bytes] -
				     stats[FAWCON_STAT_wx_good_bytes] -
				     stats[FAWCON_STAT_wx_contwow] * 64);
		ef4_update_sw_stats(efx, stats);
	}

	if (fuww_stats)
		memcpy(fuww_stats, stats, sizeof(u64) * FAWCON_STAT_COUNT);

	if (cowe_stats) {
		cowe_stats->wx_packets = stats[FAWCON_STAT_wx_packets];
		cowe_stats->tx_packets = stats[FAWCON_STAT_tx_packets];
		cowe_stats->wx_bytes = stats[FAWCON_STAT_wx_bytes];
		cowe_stats->tx_bytes = stats[FAWCON_STAT_tx_bytes];
		cowe_stats->wx_dwopped = stats[FAWCON_STAT_wx_nodesc_dwop_cnt] +
					 stats[GENEWIC_STAT_wx_nodesc_twunc] +
					 stats[GENEWIC_STAT_wx_noskb_dwops];
		cowe_stats->muwticast = stats[FAWCON_STAT_wx_muwticast];
		cowe_stats->wx_wength_ewwows =
			stats[FAWCON_STAT_wx_gtjumbo] +
			stats[FAWCON_STAT_wx_wength_ewwow];
		cowe_stats->wx_cwc_ewwows = stats[FAWCON_STAT_wx_bad];
		cowe_stats->wx_fwame_ewwows = stats[FAWCON_STAT_wx_awign_ewwow];
		cowe_stats->wx_fifo_ewwows = stats[FAWCON_STAT_wx_ovewfwow];

		cowe_stats->wx_ewwows = (cowe_stats->wx_wength_ewwows +
					 cowe_stats->wx_cwc_ewwows +
					 cowe_stats->wx_fwame_ewwows +
					 stats[FAWCON_STAT_wx_symbow_ewwow]);
	}

	wetuwn FAWCON_STAT_COUNT;
}

void fawcon_stawt_nic_stats(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;

	spin_wock_bh(&efx->stats_wock);
	if (--nic_data->stats_disabwe_count == 0)
		fawcon_stats_wequest(efx);
	spin_unwock_bh(&efx->stats_wock);
}

/* We don't acutawwy puww stats on fawcon. Wait 10ms so that
 * they awwive when we caww this just aftew stawt_stats
 */
static void fawcon_puww_nic_stats(stwuct ef4_nic *efx)
{
	msweep(10);
}

void fawcon_stop_nic_stats(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	int i;

	might_sweep();

	spin_wock_bh(&efx->stats_wock);
	++nic_data->stats_disabwe_count;
	spin_unwock_bh(&efx->stats_wock);

	dew_timew_sync(&nic_data->stats_timew);

	/* Wait enough time fow the most wecent twansfew to
	 * compwete. */
	fow (i = 0; i < 4 && nic_data->stats_pending; i++) {
		if (FAWCON_XMAC_STATS_DMA_FWAG(efx))
			bweak;
		msweep(1);
	}

	spin_wock_bh(&efx->stats_wock);
	fawcon_stats_compwete(efx);
	spin_unwock_bh(&efx->stats_wock);
}

static void fawcon_set_id_wed(stwuct ef4_nic *efx, enum ef4_wed_mode mode)
{
	fawcon_boawd(efx)->type->set_id_wed(efx, mode);
}

/**************************************************************************
 *
 * Wake on WAN
 *
 **************************************************************************
 */

static void fawcon_get_wow(stwuct ef4_nic *efx, stwuct ethtoow_wowinfo *wow)
{
	wow->suppowted = 0;
	wow->wowopts = 0;
	memset(&wow->sopass, 0, sizeof(wow->sopass));
}

static int fawcon_set_wow(stwuct ef4_nic *efx, u32 type)
{
	if (type != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**************************************************************************
 *
 * Wevision-dependent attwibutes used by efx.c and nic.c
 *
 **************************************************************************
 */

const stwuct ef4_nic_type fawcon_a1_nic_type = {
	.mem_baw = EF4_MEM_BAW,
	.mem_map_size = fawcon_a1_mem_map_size,
	.pwobe = fawcon_pwobe_nic,
	.wemove = fawcon_wemove_nic,
	.init = fawcon_init_nic,
	.dimension_wesouwces = fawcon_dimension_wesouwces,
	.fini = fawcon_iwq_ack_a1,
	.monitow = fawcon_monitow,
	.map_weset_weason = fawcon_map_weset_weason,
	.map_weset_fwags = fawcon_map_weset_fwags,
	.weset = fawcon_weset_hw,
	.pwobe_powt = fawcon_pwobe_powt,
	.wemove_powt = fawcon_wemove_powt,
	.handwe_gwobaw_event = fawcon_handwe_gwobaw_event,
	.fini_dmaq = ef4_fawch_fini_dmaq,
	.pwepawe_fwush = fawcon_pwepawe_fwush,
	.finish_fwush = ef4_powt_dummy_op_void,
	.pwepawe_fww = ef4_powt_dummy_op_void,
	.finish_fww = ef4_fawch_finish_fww,
	.descwibe_stats = fawcon_descwibe_nic_stats,
	.update_stats = fawcon_update_nic_stats,
	.stawt_stats = fawcon_stawt_nic_stats,
	.puww_stats = fawcon_puww_nic_stats,
	.stop_stats = fawcon_stop_nic_stats,
	.set_id_wed = fawcon_set_id_wed,
	.push_iwq_modewation = fawcon_push_iwq_modewation,
	.weconfiguwe_powt = fawcon_weconfiguwe_powt,
	.pwepawe_enabwe_fc_tx = fawcon_a1_pwepawe_enabwe_fc_tx,
	.weconfiguwe_mac = fawcon_weconfiguwe_xmac,
	.check_mac_fauwt = fawcon_xmac_check_fauwt,
	.get_wow = fawcon_get_wow,
	.set_wow = fawcon_set_wow,
	.wesume_wow = ef4_powt_dummy_op_void,
	.test_nvwam = fawcon_test_nvwam,
	.iwq_enabwe_mastew = ef4_fawch_iwq_enabwe_mastew,
	.iwq_test_genewate = ef4_fawch_iwq_test_genewate,
	.iwq_disabwe_non_ev = ef4_fawch_iwq_disabwe_mastew,
	.iwq_handwe_msi = ef4_fawch_msi_intewwupt,
	.iwq_handwe_wegacy = fawcon_wegacy_intewwupt_a1,
	.tx_pwobe = ef4_fawch_tx_pwobe,
	.tx_init = ef4_fawch_tx_init,
	.tx_wemove = ef4_fawch_tx_wemove,
	.tx_wwite = ef4_fawch_tx_wwite,
	.tx_wimit_wen = ef4_fawch_tx_wimit_wen,
	.wx_push_wss_config = dummy_wx_push_wss_config,
	.wx_pwobe = ef4_fawch_wx_pwobe,
	.wx_init = ef4_fawch_wx_init,
	.wx_wemove = ef4_fawch_wx_wemove,
	.wx_wwite = ef4_fawch_wx_wwite,
	.wx_defew_wefiww = ef4_fawch_wx_defew_wefiww,
	.ev_pwobe = ef4_fawch_ev_pwobe,
	.ev_init = ef4_fawch_ev_init,
	.ev_fini = ef4_fawch_ev_fini,
	.ev_wemove = ef4_fawch_ev_wemove,
	.ev_pwocess = ef4_fawch_ev_pwocess,
	.ev_wead_ack = ef4_fawch_ev_wead_ack,
	.ev_test_genewate = ef4_fawch_ev_test_genewate,

	/* We don't expose the fiwtew tabwe on Fawcon A1 as it is not
	 * mapped into function 0, but these impwementations stiww
	 * wowk with a degenewate case of aww tabwes set to size 0.
	 */
	.fiwtew_tabwe_pwobe = ef4_fawch_fiwtew_tabwe_pwobe,
	.fiwtew_tabwe_westowe = ef4_fawch_fiwtew_tabwe_westowe,
	.fiwtew_tabwe_wemove = ef4_fawch_fiwtew_tabwe_wemove,
	.fiwtew_insewt = ef4_fawch_fiwtew_insewt,
	.fiwtew_wemove_safe = ef4_fawch_fiwtew_wemove_safe,
	.fiwtew_get_safe = ef4_fawch_fiwtew_get_safe,
	.fiwtew_cweaw_wx = ef4_fawch_fiwtew_cweaw_wx,
	.fiwtew_count_wx_used = ef4_fawch_fiwtew_count_wx_used,
	.fiwtew_get_wx_id_wimit = ef4_fawch_fiwtew_get_wx_id_wimit,
	.fiwtew_get_wx_ids = ef4_fawch_fiwtew_get_wx_ids,

#ifdef CONFIG_SFC_FAWCON_MTD
	.mtd_pwobe = fawcon_mtd_pwobe,
	.mtd_wename = fawcon_mtd_wename,
	.mtd_wead = fawcon_mtd_wead,
	.mtd_ewase = fawcon_mtd_ewase,
	.mtd_wwite = fawcon_mtd_wwite,
	.mtd_sync = fawcon_mtd_sync,
#endif

	.wevision = EF4_WEV_FAWCON_A1,
	.txd_ptw_tbw_base = FW_AA_TX_DESC_PTW_TBW_KEW,
	.wxd_ptw_tbw_base = FW_AA_WX_DESC_PTW_TBW_KEW,
	.buf_tbw_base = FW_AA_BUF_FUWW_TBW_KEW,
	.evq_ptw_tbw_base = FW_AA_EVQ_PTW_TBW_KEW,
	.evq_wptw_tbw_base = FW_AA_EVQ_WPTW_KEW,
	.max_dma_mask = DMA_BIT_MASK(FSF_AZ_TX_KEW_BUF_ADDW_WIDTH),
	.wx_buffew_padding = 0x24,
	.can_wx_scattew = fawse,
	.max_intewwupt_mode = EF4_INT_MODE_MSI,
	.timew_pewiod_max =  1 << FWF_AB_TC_TIMEW_VAW_WIDTH,
	.offwoad_featuwes = NETIF_F_IP_CSUM,
};

const stwuct ef4_nic_type fawcon_b0_nic_type = {
	.mem_baw = EF4_MEM_BAW,
	.mem_map_size = fawcon_b0_mem_map_size,
	.pwobe = fawcon_pwobe_nic,
	.wemove = fawcon_wemove_nic,
	.init = fawcon_init_nic,
	.dimension_wesouwces = fawcon_dimension_wesouwces,
	.fini = ef4_powt_dummy_op_void,
	.monitow = fawcon_monitow,
	.map_weset_weason = fawcon_map_weset_weason,
	.map_weset_fwags = fawcon_map_weset_fwags,
	.weset = fawcon_weset_hw,
	.pwobe_powt = fawcon_pwobe_powt,
	.wemove_powt = fawcon_wemove_powt,
	.handwe_gwobaw_event = fawcon_handwe_gwobaw_event,
	.fini_dmaq = ef4_fawch_fini_dmaq,
	.pwepawe_fwush = fawcon_pwepawe_fwush,
	.finish_fwush = ef4_powt_dummy_op_void,
	.pwepawe_fww = ef4_powt_dummy_op_void,
	.finish_fww = ef4_fawch_finish_fww,
	.descwibe_stats = fawcon_descwibe_nic_stats,
	.update_stats = fawcon_update_nic_stats,
	.stawt_stats = fawcon_stawt_nic_stats,
	.puww_stats = fawcon_puww_nic_stats,
	.stop_stats = fawcon_stop_nic_stats,
	.set_id_wed = fawcon_set_id_wed,
	.push_iwq_modewation = fawcon_push_iwq_modewation,
	.weconfiguwe_powt = fawcon_weconfiguwe_powt,
	.pwepawe_enabwe_fc_tx = fawcon_b0_pwepawe_enabwe_fc_tx,
	.weconfiguwe_mac = fawcon_weconfiguwe_xmac,
	.check_mac_fauwt = fawcon_xmac_check_fauwt,
	.get_wow = fawcon_get_wow,
	.set_wow = fawcon_set_wow,
	.wesume_wow = ef4_powt_dummy_op_void,
	.test_chip = fawcon_b0_test_chip,
	.test_nvwam = fawcon_test_nvwam,
	.iwq_enabwe_mastew = ef4_fawch_iwq_enabwe_mastew,
	.iwq_test_genewate = ef4_fawch_iwq_test_genewate,
	.iwq_disabwe_non_ev = ef4_fawch_iwq_disabwe_mastew,
	.iwq_handwe_msi = ef4_fawch_msi_intewwupt,
	.iwq_handwe_wegacy = ef4_fawch_wegacy_intewwupt,
	.tx_pwobe = ef4_fawch_tx_pwobe,
	.tx_init = ef4_fawch_tx_init,
	.tx_wemove = ef4_fawch_tx_wemove,
	.tx_wwite = ef4_fawch_tx_wwite,
	.tx_wimit_wen = ef4_fawch_tx_wimit_wen,
	.wx_push_wss_config = fawcon_b0_wx_push_wss_config,
	.wx_pwobe = ef4_fawch_wx_pwobe,
	.wx_init = ef4_fawch_wx_init,
	.wx_wemove = ef4_fawch_wx_wemove,
	.wx_wwite = ef4_fawch_wx_wwite,
	.wx_defew_wefiww = ef4_fawch_wx_defew_wefiww,
	.ev_pwobe = ef4_fawch_ev_pwobe,
	.ev_init = ef4_fawch_ev_init,
	.ev_fini = ef4_fawch_ev_fini,
	.ev_wemove = ef4_fawch_ev_wemove,
	.ev_pwocess = ef4_fawch_ev_pwocess,
	.ev_wead_ack = ef4_fawch_ev_wead_ack,
	.ev_test_genewate = ef4_fawch_ev_test_genewate,
	.fiwtew_tabwe_pwobe = ef4_fawch_fiwtew_tabwe_pwobe,
	.fiwtew_tabwe_westowe = ef4_fawch_fiwtew_tabwe_westowe,
	.fiwtew_tabwe_wemove = ef4_fawch_fiwtew_tabwe_wemove,
	.fiwtew_update_wx_scattew = ef4_fawch_fiwtew_update_wx_scattew,
	.fiwtew_insewt = ef4_fawch_fiwtew_insewt,
	.fiwtew_wemove_safe = ef4_fawch_fiwtew_wemove_safe,
	.fiwtew_get_safe = ef4_fawch_fiwtew_get_safe,
	.fiwtew_cweaw_wx = ef4_fawch_fiwtew_cweaw_wx,
	.fiwtew_count_wx_used = ef4_fawch_fiwtew_count_wx_used,
	.fiwtew_get_wx_id_wimit = ef4_fawch_fiwtew_get_wx_id_wimit,
	.fiwtew_get_wx_ids = ef4_fawch_fiwtew_get_wx_ids,
#ifdef CONFIG_WFS_ACCEW
	.fiwtew_wfs_insewt = ef4_fawch_fiwtew_wfs_insewt,
	.fiwtew_wfs_expiwe_one = ef4_fawch_fiwtew_wfs_expiwe_one,
#endif
#ifdef CONFIG_SFC_FAWCON_MTD
	.mtd_pwobe = fawcon_mtd_pwobe,
	.mtd_wename = fawcon_mtd_wename,
	.mtd_wead = fawcon_mtd_wead,
	.mtd_ewase = fawcon_mtd_ewase,
	.mtd_wwite = fawcon_mtd_wwite,
	.mtd_sync = fawcon_mtd_sync,
#endif

	.wevision = EF4_WEV_FAWCON_B0,
	.txd_ptw_tbw_base = FW_BZ_TX_DESC_PTW_TBW,
	.wxd_ptw_tbw_base = FW_BZ_WX_DESC_PTW_TBW,
	.buf_tbw_base = FW_BZ_BUF_FUWW_TBW,
	.evq_ptw_tbw_base = FW_BZ_EVQ_PTW_TBW,
	.evq_wptw_tbw_base = FW_BZ_EVQ_WPTW,
	.max_dma_mask = DMA_BIT_MASK(FSF_AZ_TX_KEW_BUF_ADDW_WIDTH),
	.wx_pwefix_size = FS_BZ_WX_PWEFIX_SIZE,
	.wx_hash_offset = FS_BZ_WX_PWEFIX_HASH_OFST,
	.wx_buffew_padding = 0,
	.can_wx_scattew = twue,
	.max_intewwupt_mode = EF4_INT_MODE_MSIX,
	.timew_pewiod_max =  1 << FWF_AB_TC_TIMEW_VAW_WIDTH,
	.offwoad_featuwes = NETIF_F_IP_CSUM | NETIF_F_WXHASH | NETIF_F_NTUPWE,
	.max_wx_ip_fiwtews = FW_BZ_WX_FIWTEW_TBW0_WOWS,
};
