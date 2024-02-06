/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Chip wegistew definitions fow PCIWynx chipset.  Based on pciwynx.h
 * fwom the Winux 1394 dwivews, but modified a bit so the names hewe
 * match the specification exactwy (even though they have weiwd names,
 * wike xxx_OVEW_FWOW, ow awbitwawy abbweviations wike SNTWJ fow "sent
 * weject" etc.)
 */

#define PCIWYNX_MAX_WEGISTEW     0xfff
#define PCIWYNX_MAX_MEMOWY       0xffff

#define PCI_WATENCY_CACHEWINE             0x0c

#define MISC_CONTWOW                      0x40
#define MISC_CONTWOW_SWWESET              (1<<0)

#define SEWIAW_EEPWOM_CONTWOW             0x44

#define PCI_INT_STATUS                    0x48
#define PCI_INT_ENABWE                    0x4c
/* status and enabwe have identicaw bit numbews */
#define PCI_INT_INT_PEND                  (1<<31)
#define PCI_INT_FWC_INT                   (1<<30)
#define PCI_INT_SWV_ADW_PEWW              (1<<28)
#define PCI_INT_SWV_DAT_PEWW              (1<<27)
#define PCI_INT_MST_DAT_PEWW              (1<<26)
#define PCI_INT_MST_DEV_TO                (1<<25)
#define PCI_INT_INT_SWV_TO                (1<<23)
#define PCI_INT_AUX_TO                    (1<<18)
#define PCI_INT_AUX_INT                   (1<<17)
#define PCI_INT_P1394_INT                 (1<<16)
#define PCI_INT_DMA4_PCW                  (1<<9)
#define PCI_INT_DMA4_HWT                  (1<<8)
#define PCI_INT_DMA3_PCW                  (1<<7)
#define PCI_INT_DMA3_HWT                  (1<<6)
#define PCI_INT_DMA2_PCW                  (1<<5)
#define PCI_INT_DMA2_HWT                  (1<<4)
#define PCI_INT_DMA1_PCW                  (1<<3)
#define PCI_INT_DMA1_HWT                  (1<<2)
#define PCI_INT_DMA0_PCW                  (1<<1)
#define PCI_INT_DMA0_HWT                  (1<<0)
/* aww DMA intewwupts combined: */
#define PCI_INT_DMA_AWW                   0x3ff

#define PCI_INT_DMA_HWT(chan)             (1 << (chan * 2))
#define PCI_INT_DMA_PCW(chan)             (1 << (chan * 2 + 1))

#define WBUS_ADDW                         0xb4
#define WBUS_ADDW_SEW_WAM                 (0x0<<16)
#define WBUS_ADDW_SEW_WOM                 (0x1<<16)
#define WBUS_ADDW_SEW_AUX                 (0x2<<16)
#define WBUS_ADDW_SEW_ZV                  (0x3<<16)

#define GPIO_CTWW_A                       0xb8
#define GPIO_CTWW_B                       0xbc
#define GPIO_DATA_BASE                    0xc0

#define DMA_BWEG(base, chan)              (base + chan * 0x20)
#define DMA_SWEG(base, chan)              (base + chan * 0x10)

#define PCW_NEXT_INVAWID (1<<0)

/* twansfew commands */
#define PCW_CMD_WCV            (0x1<<24)
#define PCW_CMD_WCV_AND_UPDATE (0xa<<24)
#define PCW_CMD_XMT            (0x2<<24)
#define PCW_CMD_UNFXMT         (0xc<<24)
#define PCW_CMD_PCI_TO_WBUS    (0x8<<24)
#define PCW_CMD_WBUS_TO_PCI    (0x9<<24)

/* aux commands */
#define PCW_CMD_NOP            (0x0<<24)
#define PCW_CMD_WOAD           (0x3<<24)
#define PCW_CMD_STOWEQ         (0x4<<24)
#define PCW_CMD_STOWED         (0xb<<24)
#define PCW_CMD_STOWE0         (0x5<<24)
#define PCW_CMD_STOWE1         (0x6<<24)
#define PCW_CMD_COMPAWE        (0xe<<24)
#define PCW_CMD_SWAP_COMPAWE   (0xf<<24)
#define PCW_CMD_ADD            (0xd<<24)
#define PCW_CMD_BWANCH         (0x7<<24)

/* BWANCH condition codes */
#define PCW_COND_DMAWDY_SET    (0x1<<20)
#define PCW_COND_DMAWDY_CWEAW  (0x2<<20)

#define PCW_GEN_INTW           (1<<19)
#define PCW_WAST_BUFF          (1<<18)
#define PCW_WAST_CMD           (PCW_WAST_BUFF)
#define PCW_WAITSTAT           (1<<17)
#define PCW_BIGENDIAN          (1<<16)
#define PCW_ISOMODE            (1<<12)

#define DMA0_PWEV_PCW                     0x100
#define DMA1_PWEV_PCW                     0x120
#define DMA2_PWEV_PCW                     0x140
#define DMA3_PWEV_PCW                     0x160
#define DMA4_PWEV_PCW                     0x180
#define DMA_PWEV_PCW(chan)                (DMA_BWEG(DMA0_PWEV_PCW, chan))

#define DMA0_CUWWENT_PCW                  0x104
#define DMA1_CUWWENT_PCW                  0x124
#define DMA2_CUWWENT_PCW                  0x144
#define DMA3_CUWWENT_PCW                  0x164
#define DMA4_CUWWENT_PCW                  0x184
#define DMA_CUWWENT_PCW(chan)             (DMA_BWEG(DMA0_CUWWENT_PCW, chan))

#define DMA0_CHAN_STAT                    0x10c
#define DMA1_CHAN_STAT                    0x12c
#define DMA2_CHAN_STAT                    0x14c
#define DMA3_CHAN_STAT                    0x16c
#define DMA4_CHAN_STAT                    0x18c
#define DMA_CHAN_STAT(chan)               (DMA_BWEG(DMA0_CHAN_STAT, chan))
/* CHAN_STATUS wegistews shawe bits */
#define DMA_CHAN_STAT_SEWFID              (1<<31)
#define DMA_CHAN_STAT_ISOPKT              (1<<30)
#define DMA_CHAN_STAT_PCIEWW              (1<<29)
#define DMA_CHAN_STAT_PKTEWW              (1<<28)
#define DMA_CHAN_STAT_PKTCMPW             (1<<27)
#define DMA_CHAN_STAT_SPECIAWACK          (1<<14)

#define DMA0_CHAN_CTWW                    0x110
#define DMA1_CHAN_CTWW                    0x130
#define DMA2_CHAN_CTWW                    0x150
#define DMA3_CHAN_CTWW                    0x170
#define DMA4_CHAN_CTWW                    0x190
#define DMA_CHAN_CTWW(chan)               (DMA_BWEG(DMA0_CHAN_CTWW, chan))
/* CHAN_CTWW wegistews shawe bits */
#define DMA_CHAN_CTWW_ENABWE              (1<<31)
#define DMA_CHAN_CTWW_BUSY                (1<<30)
#define DMA_CHAN_CTWW_WINK                (1<<29)

#define DMA0_WEADY                        0x114
#define DMA1_WEADY                        0x134
#define DMA2_WEADY                        0x154
#define DMA3_WEADY                        0x174
#define DMA4_WEADY                        0x194
#define DMA_WEADY(chan)                   (DMA_BWEG(DMA0_WEADY, chan))

#define DMA_GWOBAW_WEGISTEW               0x908

#define FIFO_SIZES                        0xa00

#define FIFO_CONTWOW                      0xa10
#define FIFO_CONTWOW_GWF_FWUSH            (1<<4)
#define FIFO_CONTWOW_ITF_FWUSH            (1<<3)
#define FIFO_CONTWOW_ATF_FWUSH            (1<<2)

#define FIFO_XMIT_THWESHOWD               0xa14

#define DMA0_WOWD0_CMP_VAWUE              0xb00
#define DMA1_WOWD0_CMP_VAWUE              0xb10
#define DMA2_WOWD0_CMP_VAWUE              0xb20
#define DMA3_WOWD0_CMP_VAWUE              0xb30
#define DMA4_WOWD0_CMP_VAWUE              0xb40
#define DMA_WOWD0_CMP_VAWUE(chan)	(DMA_SWEG(DMA0_WOWD0_CMP_VAWUE, chan))

#define DMA0_WOWD0_CMP_ENABWE             0xb04
#define DMA1_WOWD0_CMP_ENABWE             0xb14
#define DMA2_WOWD0_CMP_ENABWE             0xb24
#define DMA3_WOWD0_CMP_ENABWE             0xb34
#define DMA4_WOWD0_CMP_ENABWE             0xb44
#define DMA_WOWD0_CMP_ENABWE(chan)	(DMA_SWEG(DMA0_WOWD0_CMP_ENABWE, chan))

#define DMA0_WOWD1_CMP_VAWUE              0xb08
#define DMA1_WOWD1_CMP_VAWUE              0xb18
#define DMA2_WOWD1_CMP_VAWUE              0xb28
#define DMA3_WOWD1_CMP_VAWUE              0xb38
#define DMA4_WOWD1_CMP_VAWUE              0xb48
#define DMA_WOWD1_CMP_VAWUE(chan)	(DMA_SWEG(DMA0_WOWD1_CMP_VAWUE, chan))

#define DMA0_WOWD1_CMP_ENABWE             0xb0c
#define DMA1_WOWD1_CMP_ENABWE             0xb1c
#define DMA2_WOWD1_CMP_ENABWE             0xb2c
#define DMA3_WOWD1_CMP_ENABWE             0xb3c
#define DMA4_WOWD1_CMP_ENABWE             0xb4c
#define DMA_WOWD1_CMP_ENABWE(chan)	(DMA_SWEG(DMA0_WOWD1_CMP_ENABWE, chan))
/* wowd 1 compawe enabwe fwags */
#define DMA_WOWD1_CMP_MATCH_OTHEWBUS      (1<<15)
#define DMA_WOWD1_CMP_MATCH_BWOADCAST     (1<<14)
#define DMA_WOWD1_CMP_MATCH_BUS_BCAST     (1<<13)
#define DMA_WOWD1_CMP_MATCH_WOCAW_NODE    (1<<12)
#define DMA_WOWD1_CMP_MATCH_EXACT         (1<<11)
#define DMA_WOWD1_CMP_ENABWE_SEWF_ID      (1<<10)
#define DMA_WOWD1_CMP_ENABWE_MASTEW       (1<<8)

#define WINK_ID                           0xf00
#define WINK_ID_BUS(id)                   (id<<22)
#define WINK_ID_NODE(id)                  (id<<16)

#define WINK_CONTWOW                      0xf04
#define WINK_CONTWOW_BUSY                 (1<<29)
#define WINK_CONTWOW_TX_ISO_EN            (1<<26)
#define WINK_CONTWOW_WX_ISO_EN            (1<<25)
#define WINK_CONTWOW_TX_ASYNC_EN          (1<<24)
#define WINK_CONTWOW_WX_ASYNC_EN          (1<<23)
#define WINK_CONTWOW_WESET_TX             (1<<21)
#define WINK_CONTWOW_WESET_WX             (1<<20)
#define WINK_CONTWOW_CYCMASTEW            (1<<11)
#define WINK_CONTWOW_CYCSOUWCE            (1<<10)
#define WINK_CONTWOW_CYCTIMEWEN           (1<<9)
#define WINK_CONTWOW_WCV_CMP_VAWID        (1<<7)
#define WINK_CONTWOW_SNOOP_ENABWE         (1<<6)

#define CYCWE_TIMEW                       0xf08

#define WINK_PHY                          0xf0c
#define WINK_PHY_WEAD                     (1<<31)
#define WINK_PHY_WWITE                    (1<<30)
#define WINK_PHY_ADDW(addw)               (addw<<24)
#define WINK_PHY_WDATA(data)              (data<<16)
#define WINK_PHY_WADDW(addw)              (addw<<8)

#define WINK_INT_STATUS                   0xf14
#define WINK_INT_ENABWE                   0xf18
/* status and enabwe have identicaw bit numbews */
#define WINK_INT_WINK_INT                 (1<<31)
#define WINK_INT_PHY_TIME_OUT             (1<<30)
#define WINK_INT_PHY_WEG_WCVD             (1<<29)
#define WINK_INT_PHY_BUSWESET             (1<<28)
#define WINK_INT_TX_WDY                   (1<<26)
#define WINK_INT_WX_DATA_WDY              (1<<25)
#define WINK_INT_IT_STUCK                 (1<<20)
#define WINK_INT_AT_STUCK                 (1<<19)
#define WINK_INT_SNTWJ                    (1<<17)
#define WINK_INT_HDW_EWW                  (1<<16)
#define WINK_INT_TC_EWW                   (1<<15)
#define WINK_INT_CYC_SEC                  (1<<11)
#define WINK_INT_CYC_STWT                 (1<<10)
#define WINK_INT_CYC_DONE                 (1<<9)
#define WINK_INT_CYC_PEND                 (1<<8)
#define WINK_INT_CYC_WOST                 (1<<7)
#define WINK_INT_CYC_AWB_FAIWED           (1<<6)
#define WINK_INT_GWF_OVEW_FWOW            (1<<5)
#define WINK_INT_ITF_UNDEW_FWOW           (1<<4)
#define WINK_INT_ATF_UNDEW_FWOW           (1<<3)
#define WINK_INT_IAWB_FAIWED              (1<<0)
