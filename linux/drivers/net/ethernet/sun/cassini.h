/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* $Id: cassini.h,v 1.16 2004/08/17 21:15:16 zaumen Exp $
 * cassini.h: Definitions fow Sun Micwosystems Cassini(+) ethewnet dwivew.
 *
 * Copywight (C) 2004 Sun Micwosystems Inc.
 * Copywight (c) 2003 Adwian Sun (asun@dawksunwising.com)
 *
 * vendow id: 0x108E (Sun Micwosystems, Inc.)
 * device id: 0xabba (Cassini)
 * wevision ids: 0x01 = Cassini
 *               0x02 = Cassini wev 2
 *               0x10 = Cassini+
 *               0x11 = Cassini+ 0.2u
 *
 * vendow id: 0x100b (Nationaw Semiconductow)
 * device id: 0x0035 (DP83065/Satuwn)
 * wevision ids: 0x30 = Satuwn B2
 *
 * wings awe aww offset fwom 0.
 *
 * thewe awe two cwock domains:
 * PCI:  33/66MHz cwock
 * chip: 125MHz cwock
 */

#ifndef _CASSINI_H
#define _CASSINI_H

/* cassini wegistew map: 2M memowy mapped in 32-bit memowy space accessibwe as
 * 32-bit wowds. thewe is no i/o powt access. WEG_ addwesses awe
 * shawed between cassini and cassini+. WEG_PWUS_ addwesses onwy
 * appeaw in cassini+. WEG_MINUS_ addwesses onwy appeaw in cassini.
 */
#define CAS_ID_WEV2          0x02
#define CAS_ID_WEVPWUS       0x10
#define CAS_ID_WEVPWUS02u    0x11
#define CAS_ID_WEVSATUWNB2   0x30

/** gwobaw wesouwces **/

/* this wegistew sets the weights fow the weighted wound wobin awbitew. e.g.,
 * if wx weight == 1 and tx weight == 0, wx == 2x tx twansfew cwedit
 * fow its next tuwn to access the pci bus.
 * map: 0x0 = x1, 0x1 = x2, 0x2 = x4, 0x3 = x8
 * DEFAUWT: 0x0, SIZE: 5 bits
 */
#define  WEG_CAWW	               0x0004  /* cowe awbitwation weight */
#define    CAWW_WX_DMA_WEIGHT_SHIFT    0
#define    CAWW_WX_DMA_WEIGHT_MASK     0x03    /* [0:1] */
#define    CAWW_TX_DMA_WEIGHT_SHIFT    2
#define    CAWW_TX_DMA_WEIGHT_MASK     0x0C    /* [3:2] */
#define    CAWW_WW_DIS                 0x10    /* [4] */

/* if enabwed, BIM can send buwsts acwoss PCI bus > cachewine size. buwst
 * sizes detewmined by wength of packet ow descwiptow twansfew and the
 * max wength awwowed by the tawget.
 * DEFAUWT: 0x0, SIZE: 1 bit
 */
#define  WEG_INF_BUWST                 0x0008  /* infinite buwst enabwe weg */
#define    INF_BUWST_EN                0x1     /* enabwe */

/* top wevew intewwupts [0-9] awe auto-cweawed to 0 when the status
 * wegistew is wead. second wevew intewwupts [13 - 18] awe cweawed at
 * the souwce. tx compwetion wegistew 3 is wepwicated in [19 - 31]
 * DEFAUWT: 0x00000000, SIZE: 29 bits
 */
#define  WEG_INTW_STATUS               0x000C  /* intewwupt status wegistew */
#define    INTW_TX_INTME               0x00000001  /* fwame w/ INT ME desc bit set
						      xfewwed fwom host queue to
						      TX FIFO */
#define    INTW_TX_AWW                 0x00000002  /* aww xmit fwames xfewwed into
						      TX FIFO. i.e.,
						      TX Kick == TX compwete. if
						      PACED_MODE set, then TX FIFO
						      awso empty */
#define    INTW_TX_DONE                0x00000004  /* any fwame xfewwed into tx
						      FIFO */
#define    INTW_TX_TAG_EWWOW           0x00000008  /* TX FIFO tag fwaming
						      cowwupted. FATAW EWWOW */
#define    INTW_WX_DONE                0x00000010  /* at weast 1 fwame xfewwed
						      fwom WX FIFO to host mem.
						      WX compwetion weg updated.
						      may be dewayed by wecv
						      intw bwanking. */
#define    INTW_WX_BUF_UNAVAIW         0x00000020  /* no mowe weceive buffews.
						      WX Kick == WX compwete */
#define    INTW_WX_TAG_EWWOW           0x00000040  /* WX FIFO tag fwaming
						      cowwupted. FATAW EWWOW */
#define    INTW_WX_COMP_FUWW           0x00000080  /* no mowe woom in compwetion
						      wing to post descwiptows.
						      WX compwete head incw to
						      awmost weach WX compwete
						      taiw */
#define    INTW_WX_BUF_AE              0x00000100  /* wess than the
						      pwogwammabwe thweshowd #
						      of fwee descw avaiw fow
						      hw use */
#define    INTW_WX_COMP_AF             0x00000200  /* wess than the
						      pwogwammabwe thweshowd #
						      of descw spaces fow hw
						      use in compwetion descw
						      wing */
#define    INTW_WX_WEN_MISMATCH        0x00000400  /* wen fiewd fwom MAC !=
						      wen of non-weassembwy pkt
						      fwom fifo duwing DMA ow
						      headew pawsew pwovides TCP
						      headew and paywoad size >
						      MAC packet size.
						      FATAW EWWOW */
#define    INTW_SUMMAWY                0x00001000  /* summawy intewwupt bit. this
						      bit wiww be set if an intewwupt
						      genewated on the pci bus. usefuw
						      when dwivew is powwing fow
						      intewwupts */
#define    INTW_PCS_STATUS             0x00002000  /* PCS intewwupt status wegistew */
#define    INTW_TX_MAC_STATUS          0x00004000  /* TX MAC status wegistew has at
						      weast 1 unmasked intewwupt set */
#define    INTW_WX_MAC_STATUS          0x00008000  /* WX MAC status wegistew has at
						      weast 1 unmasked intewwupt set */
#define    INTW_MAC_CTWW_STATUS        0x00010000  /* MAC contwow status wegistew has
						      at weast 1 unmasked intewwupt
						      set */
#define    INTW_MIF_STATUS             0x00020000  /* MIF status wegistew has at weast
						      1 unmasked intewwupt set */
#define    INTW_PCI_EWWOW_STATUS       0x00040000  /* PCI ewwow status wegistew in the
						      BIF has at weast 1 unmasked
						      intewwupt set */
#define    INTW_TX_COMP_3_MASK         0xFFF80000  /* mask fow TX compwetion
						      3 weg data */
#define    INTW_TX_COMP_3_SHIFT        19
#define    INTW_EWWOW_MASK (INTW_MIF_STATUS | INTW_PCI_EWWOW_STATUS | \
                            INTW_PCS_STATUS | INTW_WX_WEN_MISMATCH | \
                            INTW_TX_MAC_STATUS | INTW_WX_MAC_STATUS | \
                            INTW_TX_TAG_EWWOW | INTW_WX_TAG_EWWOW | \
                            INTW_MAC_CTWW_STATUS)

/* detewmines which status events wiww cause an intewwupt. wayout same
 * as WEG_INTW_STATUS.
 * DEFAUWT: 0xFFFFFFFF, SIZE: 16 bits
 */
#define  WEG_INTW_MASK                 0x0010  /* Intewwupt mask */

/* top wevew intewwupt bits that awe cweawed duwing wead of WEG_INTW_STATUS_AWIAS.
 * usefuw when dwivew is powwing fow intewwupts. wayout same as WEG_INTW_MASK.
 * DEFAUWT: 0x00000000, SIZE: 12 bits
 */
#define  WEG_AWIAS_CWEAW               0x0014  /* awias cweaw mask
						  (used w/ status awias) */
/* same as WEG_INTW_STATUS except that onwy bits cweawed awe those sewected by
 * WEG_AWIAS_CWEAW
 * DEFAUWT: 0x00000000, SIZE: 29 bits
 */
#define  WEG_INTW_STATUS_AWIAS         0x001C  /* intewwupt status awias
						  (sewective cweaw) */

/* DEFAUWT: 0x0, SIZE: 3 bits */
#define  WEG_PCI_EWW_STATUS            0x1000  /* PCI ewwow status */
#define    PCI_EWW_BADACK              0x01    /* wesewved in Cassini+.
						  set if no ACK64# duwing ABS64 cycwe
						  in Cassini. */
#define    PCI_EWW_DTWTO               0x02    /* dewayed xaction timeout. set if
						  no wead wetwy aftew 2^15 cwocks */
#define    PCI_EWW_OTHEW               0x04    /* othew PCI ewwows */
#define    PCI_EWW_BIM_DMA_WWITE       0x08    /* BIM weceived 0 count DMA wwite weq.
						  unused in Cassini. */
#define    PCI_EWW_BIM_DMA_WEAD        0x10    /* BIM weceived 0 count DMA wead weq.
						  unused in Cassini. */
#define    PCI_EWW_BIM_DMA_TIMEOUT     0x20    /* BIM weceived 255 wetwies duwing
						  DMA. unused in cassini. */

/* mask fow PCI status events that wiww set PCI_EWW_STATUS. if cweawed, event
 * causes an intewwupt to be genewated.
 * DEFAUWT: 0x7, SIZE: 3 bits
 */
#define  WEG_PCI_EWW_STATUS_MASK       0x1004  /* PCI Ewwow status mask */

/* used to configuwe PCI wewated pawametews that awe not in PCI config space.
 * DEFAUWT: 0bxx000, SIZE: 5 bits
 */
#define  WEG_BIM_CFG                0x1008  /* BIM Configuwation */
#define    BIM_CFG_WESEWVED0        0x001   /* wesewved */
#define    BIM_CFG_WESEWVED1        0x002   /* wesewved */
#define    BIM_CFG_64BIT_DISABWE    0x004   /* disabwe 64-bit mode */
#define    BIM_CFG_66MHZ            0x008   /* (wo) 1 = 66MHz, 0 = < 66MHz */
#define    BIM_CFG_32BIT            0x010   /* (wo) 1 = 32-bit swot, 0 = 64-bit */
#define    BIM_CFG_DPAW_INTW_ENABWE 0x020   /* detected pawity eww enabwe */
#define    BIM_CFG_WMA_INTW_ENABWE  0x040   /* mastew abowt intw enabwe */
#define    BIM_CFG_WTA_INTW_ENABWE  0x080   /* tawget abowt intw enabwe */
#define    BIM_CFG_WESEWVED2        0x100   /* wesewved */
#define    BIM_CFG_BIM_DISABWE      0x200   /* stop BIM DMA. use befowe gwobaw
					       weset. wesewved in Cassini. */
#define    BIM_CFG_BIM_STATUS       0x400   /* (wo) 1 = BIM DMA suspended.
						  wesewved in Cassini. */
#define    BIM_CFG_PEWWOW_BWOCK     0x800  /* bwock PEWW# to pci bus. def: 0.
						 wesewved in Cassini. */

/* DEFAUWT: 0x00000000, SIZE: 32 bits */
#define  WEG_BIM_DIAG                  0x100C  /* BIM Diagnostic */
#define    BIM_DIAG_MSTW_SM_MASK       0x3FFFFF00 /* PCI mastew contwowwew state
						     machine bits [21:0] */
#define    BIM_DIAG_BWST_SM_MASK       0x7F    /* PCI buwst contwowwew state
						  machine bits [6:0] */

/* wwiting to SW_WESET_TX and SW_WESET_WX wiww issue a gwobaw
 * weset. poww untiw TX and WX wead back as 0's fow compwetion.
 */
#define  WEG_SW_WESET                  0x1010  /* Softwawe weset */
#define    SW_WESET_TX                 0x00000001  /* weset TX DMA engine. poww untiw
						      cweawed to 0.  */
#define    SW_WESET_WX                 0x00000002  /* weset WX DMA engine. poww untiw
						      cweawed to 0. */
#define    SW_WESET_WSTOUT             0x00000004  /* fowce WSTOUT# pin active (wow).
						      wesets PHY and anything ewse
						      connected to WSTOUT#. WSTOUT#
						      is awso activated by wocaw PCI
						      weset when hot-swap is being
						      done. */
#define    SW_WESET_BWOCK_PCS_SWINK    0x00000008  /* if a gwobaw weset is done with
						      this bit set, PCS and SWINK
						      moduwes won't be weset.
						      i.e., wink won't dwop. */
#define    SW_WESET_BWEQ_SM_MASK       0x00007F00  /* bweq state machine [6:0] */
#define    SW_WESET_PCIAWB_SM_MASK     0x00070000  /* pci awbitwation state bits:
						      0b000: AWB_IDWE1
						      0b001: AWB_IDWE2
						      0b010: AWB_WB_ACK
						      0b011: AWB_WB_WAT
						      0b100: AWB_WB_ACK
						      0b101: AWB_WB_WAT
						      0b110: AWB_WB_END
						      0b111: AWB_WB_END */
#define    SW_WESET_WDPCI_SM_MASK      0x00300000  /* wead pci state bits:
						      0b00: WD_PCI_WAT
						      0b01: WD_PCI_WDY
						      0b11: WD_PCI_ACK */
#define    SW_WESET_WDAWB_SM_MASK      0x00C00000  /* wead awbitwation state bits:
						      0b00: AD_IDW_WX
						      0b01: AD_ACK_WX
						      0b10: AD_ACK_TX
						      0b11: AD_IDW_TX */
#define    SW_WESET_WWPCI_SM_MASK      0x06000000  /* wwite pci state bits
						      0b00: WW_PCI_WAT
						      0b01: WW_PCI_WDY
						      0b11: WW_PCI_ACK */
#define    SW_WESET_WWAWB_SM_MASK      0x38000000  /* wwite awbitwation state bits:
						      0b000: AWB_IDWE1
						      0b001: AWB_IDWE2
						      0b010: AWB_TX_ACK
						      0b011: AWB_TX_WAT
						      0b100: AWB_WX_ACK
						      0b110: AWB_WX_WAT */

/* Cassini onwy. 64-bit wegistew used to check PCI datapath. when wead,
 * vawue wwitten has both wowew and uppew 32-bit hawves wotated to the wight
 * one bit position. e.g., FFFFFFFF FFFFFFFF -> 7FFFFFFF 7FFFFFFF
 */
#define  WEG_MINUS_BIM_DATAPATH_TEST   0x1018  /* Cassini: BIM datapath test
						  Cassini+: wesewved */

/* output enabwes awe pwovided fow each device's chip sewect and fow the west
 * of the outputs fwom cassini to its wocaw bus devices. two sw pwogwammabwe
 * bits awe connected to genewaw puwpus contwow/status bits.
 * DEFAUWT: 0x7
 */
#define  WEG_BIM_WOCAW_DEV_EN          0x1020  /* BIM wocaw device
						  output EN. defauwt: 0x7 */
#define    BIM_WOCAW_DEV_PAD           0x01    /* addwess bus, WW signaw, and
						  OE signaw output enabwe on the
						  wocaw bus intewface. these
						  awe shawed between both wocaw
						  bus devices. twistate when 0. */
#define    BIM_WOCAW_DEV_PWOM          0x02    /* PWOM chip sewect */
#define    BIM_WOCAW_DEV_EXT           0x04    /* secondawy wocaw bus device chip
						  sewect output enabwe */
#define    BIM_WOCAW_DEV_SOFT_0        0x08    /* sw pwogwammabwe ctww bit 0 */
#define    BIM_WOCAW_DEV_SOFT_1        0x10    /* sw pwogwammabwe ctww bit 1 */
#define    BIM_WOCAW_DEV_HW_WESET      0x20    /* intewnaw hw weset. Cassini+ onwy. */

/* access 24 entwy BIM wead and wwite buffews. put addwess in WEG_BIM_BUFFEW_ADDW
 * and wead/wwite fwom/to it WEG_BIM_BUFFEW_DATA_WOW and _DATA_HI.
 * _DATA_HI shouwd be the wast access of the sequence.
 * DEFAUWT: undefined
 */
#define  WEG_BIM_BUFFEW_ADDW           0x1024  /* BIM buffew addwess. fow
						  puwposes. */
#define    BIM_BUFFEW_ADDW_MASK        0x3F    /* index (0 - 23) of buffew  */
#define    BIM_BUFFEW_WW_SEWECT        0x40    /* wwite buffew access = 1
						  wead buffew access = 0 */
/* DEFAUWT: undefined */
#define  WEG_BIM_BUFFEW_DATA_WOW       0x1028  /* BIM buffew data wow */
#define  WEG_BIM_BUFFEW_DATA_HI        0x102C  /* BIM buffew data high */

/* set BIM_WAM_BIST_STAWT to stawt buiwt-in sewf test fow BIM wead buffew.
 * bit auto-cweaws when done with status wead fwom _SUMMAWY and _PASS bits.
 */
#define  WEG_BIM_WAM_BIST              0x102C  /* BIM WAM (wead buffew) BIST
						  contwow/status */
#define    BIM_WAM_BIST_WD_STAWT       0x01    /* stawt BIST fow BIM wead buffew */
#define    BIM_WAM_BIST_WW_STAWT       0x02    /* stawt BIST fow BIM wwite buffew.
						  Cassini onwy. wesewved in
						  Cassini+. */
#define    BIM_WAM_BIST_WD_PASS        0x04    /* summawy BIST pass status fow wead
						  buffew. */
#define    BIM_WAM_BIST_WW_PASS        0x08    /* summawy BIST pass status fow wwite
						  buffew. Cassini onwy. wesewved
						  in Cassini+. */
#define    BIM_WAM_BIST_WD_WOW_PASS    0x10    /* wead wow bank passes BIST */
#define    BIM_WAM_BIST_WD_HI_PASS     0x20    /* wead high bank passes BIST */
#define    BIM_WAM_BIST_WW_WOW_PASS    0x40    /* wwite wow bank passes BIST.
						  Cassini onwy. wesewved in
						  Cassini+. */
#define    BIM_WAM_BIST_WW_HI_PASS     0x80    /* wwite high bank passes BIST.
						  Cassini onwy. wesewved in
						  Cassini+. */

/* ASUN: i'm not suwe what this does as it's not in the spec.
 * DEFAUWT: 0xFC
 */
#define  WEG_BIM_DIAG_MUX              0x1030  /* BIM diagnostic pwobe mux
						  sewect wegistew */

/* enabwe pwobe monitowing mode and sewect data appeawing on the P_A* bus. bit
 * vawues fow _SEW_HI_MASK and _SEW_WOW_MASK:
 * 0x0: intewnaw pwobe[7:0] (pci awb state, wtc empty w, wtc fuww w, wtc empty w,
 *                           wtc empty w, post pci)
 * 0x1: intewnaw pwobe[15:8] (pci wbuf comp, pci wpkt comp, pci wbuf comp,
 *                            pci wpkt comp, txdma ww weq, txdma ww ack,
 *			      txdma ww wdy, txdma ww xfw done)
 * 0x2: intewnaw pwobe[23:16] (txdma wd weq, txdma wd ack, txdma wd wdy, wxdma wd,
 *                             wd awb state, wd pci state)
 * 0x3: intewnaw pwobe[31:24] (wxdma weq, wxdma ack, wxdma wdy, wwawb state,
 *                             wwpci state)
 * 0x4: pci io pwobe[7:0]     0x5: pci io pwobe[15:8]
 * 0x6: pci io pwobe[23:16]   0x7: pci io pwobe[31:24]
 * 0x8: pci io pwobe[39:32]   0x9: pci io pwobe[47:40]
 * 0xa: pci io pwobe[55:48]   0xb: pci io pwobe[63:56]
 * the fowwowing awe not avaiwabwe in Cassini:
 * 0xc: wx pwobe[7:0]         0xd: tx pwobe[7:0]
 * 0xe: hp pwobe[7:0] 	      0xf: mac pwobe[7:0]
 */
#define  WEG_PWUS_PWOBE_MUX_SEWECT     0x1034 /* Cassini+: PWOBE MUX SEWECT */
#define    PWOBE_MUX_EN                0x80000000 /* awwow pwobe signaws to be
						     dwiven on wocaw bus P_A[15:0]
						     fow debugging */
#define    PWOBE_MUX_SUB_MUX_MASK      0x0000FF00 /* sewect sub moduwe pwobe signaws:
						     0x03 = mac[1:0]
						     0x0C = wx[1:0]
						     0x30 = tx[1:0]
						     0xC0 = hp[1:0] */
#define    PWOBE_MUX_SEW_HI_MASK       0x000000F0 /* sewect which moduwe to appeaw
						     on P_A[15:8]. see above fow
						     vawues. */
#define    PWOBE_MUX_SEW_WOW_MASK      0x0000000F /* sewect which moduwe to appeaw
						     on P_A[7:0]. see above fow
						     vawues. */

/* vawues mean the same thing as WEG_INTW_MASK excep that it's fow INTB.
 DEFAUWT: 0x1F */
#define  WEG_PWUS_INTW_MASK_1          0x1038 /* Cassini+: intewwupt mask
						 wegistew 2 fow INTB */
#define  WEG_PWUS_INTWN_MASK(x)       (WEG_PWUS_INTW_MASK_1 + ((x) - 1)*16)
/* bits cowwespond to both _MASK and _STATUS wegistews. _AWT cowwesponds to
 * aww of the awtewnate (2-4) INTW wegistews whiwe _1 cowwesponds to onwy
 * _MASK_1 and _STATUS_1 wegistews.
 * DEFAUWT: 0x7 fow MASK wegistews, 0x0 fow AWIAS_CWEAW wegistews
 */
#define    INTW_WX_DONE_AWT              0x01
#define    INTW_WX_COMP_FUWW_AWT         0x02
#define    INTW_WX_COMP_AF_AWT           0x04
#define    INTW_WX_BUF_UNAVAIW_1         0x08
#define    INTW_WX_BUF_AE_1              0x10 /* awmost empty */
#define    INTWN_MASK_WX_EN              0x80
#define    INTWN_MASK_CWEAW_AWW          (INTW_WX_DONE_AWT | \
                                          INTW_WX_COMP_FUWW_AWT | \
                                          INTW_WX_COMP_AF_AWT | \
                                          INTW_WX_BUF_UNAVAIW_1 | \
                                          INTW_WX_BUF_AE_1)
#define  WEG_PWUS_INTW_STATUS_1        0x103C /* Cassini+: intewwupt status
						 wegistew 2 fow INTB. defauwt: 0x1F */
#define  WEG_PWUS_INTWN_STATUS(x)       (WEG_PWUS_INTW_STATUS_1 + ((x) - 1)*16)
#define    INTW_STATUS_AWT_INTX_EN     0x80   /* genewate INTX when one of the
						 fwags awe set. enabwes desc wing. */

#define  WEG_PWUS_AWIAS_CWEAW_1        0x1040 /* Cassini+: awias cweaw mask
						 wegistew 2 fow INTB */
#define  WEG_PWUS_AWIASN_CWEAW(x)      (WEG_PWUS_AWIAS_CWEAW_1 + ((x) - 1)*16)

#define  WEG_PWUS_INTW_STATUS_AWIAS_1  0x1044 /* Cassini+: intewwupt status
						 wegistew awias 2 fow INTB */
#define  WEG_PWUS_INTWN_STATUS_AWIAS(x) (WEG_PWUS_INTW_STATUS_AWIAS_1 + ((x) - 1)*16)

#define WEG_SATUWN_PCFG               0x106c /* pin configuwation wegistew fow
						integwated macphy */

#define   SATUWN_PCFG_TWA             0x00000001 /* 1 = phy actwed */
#define   SATUWN_PCFG_FWA             0x00000002 /* 1 = phy wink10wed */
#define   SATUWN_PCFG_CWA             0x00000004 /* 1 = phy wink100wed */
#define   SATUWN_PCFG_WWA             0x00000008 /* 1 = phy wink1000wed */
#define   SATUWN_PCFG_WWA             0x00000010 /* 1 = phy dupwexwed */
#define   SATUWN_PCFG_PDS             0x00000020 /* phy debug mode.
						    0 = nowmaw */
#define   SATUWN_PCFG_MTP             0x00000080 /* test point sewect */
#define   SATUWN_PCFG_GMO             0x00000100 /* GMII obsewve. 1 =
						    GMII on SEWDES pins fow
						    monitowing. */
#define   SATUWN_PCFG_FSI             0x00000200 /* 1 = fweeze sewdes/gmii. aww
						    pins configed as outputs.
						    fow powew saving when using
						    intewnaw phy. */
#define   SATUWN_PCFG_WAD             0x00000800 /* 0 = mac cowe wed ctww
						    powawity fwom stwapping
						    vawue.
						    1 = mac cowe wed ctww
						    powawity active wow. */


/** twansmit dma wegistews **/
#define MAX_TX_WINGS_SHIFT            2
#define MAX_TX_WINGS                  (1 << MAX_TX_WINGS_SHIFT)
#define MAX_TX_WINGS_MASK             (MAX_TX_WINGS - 1)

/* TX configuwation.
 * descw wing sizes size = 32 * (1 << n), n < 9. e.g., 0x8 = 8k. defauwt: 0x8
 * DEFAUWT: 0x3F000001
 */
#define  WEG_TX_CFG                    0x2004  /* TX config */
#define    TX_CFG_DMA_EN               0x00000001  /* enabwe TX DMA. if cweawed, DMA
						      wiww stop aftew xfew of cuwwent
						      buffew has been compweted. */
#define    TX_CFG_FIFO_PIO_SEW         0x00000002  /* TX DMA FIFO can be
						      accessed w/ FIFO addw
						      and data wegistews.
						      TX DMA shouwd be
						      disabwed. */
#define    TX_CFG_DESC_WING0_MASK      0x0000003C  /* # desc entwies in
						      wing 1. */
#define    TX_CFG_DESC_WING0_SHIFT     2
#define    TX_CFG_DESC_WINGN_MASK(a)   (TX_CFG_DESC_WING0_MASK << (a)*4)
#define    TX_CFG_DESC_WINGN_SHIFT(a)  (TX_CFG_DESC_WING0_SHIFT + (a)*4)
#define    TX_CFG_PACED_MODE           0x00100000  /* TX_AWW onwy set aftew
						      TX FIFO becomes empty.
						      if 0, TX_AWW set
						      if descw queue empty. */
#define    TX_CFG_DMA_WDPIPE_DIS       0x01000000  /* awways set to 1 */
#define    TX_CFG_COMPWB_Q1            0x02000000  /* compwetion wwiteback happens at
						      the end of evewy packet kicked
						      thwough Q1. */
#define    TX_CFG_COMPWB_Q2            0x04000000  /* compwetion wwiteback happens at
						      the end of evewy packet kicked
						      thwough Q2. */
#define    TX_CFG_COMPWB_Q3            0x08000000  /* compwetion wwiteback happens at
						      the end of evewy packet kicked
						      thwough Q3 */
#define    TX_CFG_COMPWB_Q4            0x10000000  /* compwetion wwiteback happens at
						      the end of evewy packet kicked
						      thwough Q4 */
#define    TX_CFG_INTW_COMPWB_DIS      0x20000000  /* disabwe pwe-intewwupt compwetion
						      wwiteback */
#define    TX_CFG_CTX_SEW_MASK         0xC0000000  /* sewects tx test powt
						      connection
						      0b00: tx mac weq,
						            tx mac wetwy weq,
							    tx ack and tx tag.
						      0b01: txdma wd weq,
						            txdma wd ack,
							    txdma wd wdy,
							    txdma wd type0
						      0b11: txdma ww weq,
						            txdma ww ack,
							    txdma ww wdy,
							    txdma ww xfw done. */
#define    TX_CFG_CTX_SEW_SHIFT        30

/* 11-bit countews that point to next wocation in FIFO to be woaded/wetwieved.
 * used fow diagnostics onwy.
 */
#define  WEG_TX_FIFO_WWITE_PTW         0x2014  /* TX FIFO wwite pointew */
#define  WEG_TX_FIFO_SHADOW_WWITE_PTW  0x2018  /* TX FIFO shadow wwite
						  pointew. temp howd weg.
					          diagnostics onwy. */
#define  WEG_TX_FIFO_WEAD_PTW          0x201C  /* TX FIFO wead pointew */
#define  WEG_TX_FIFO_SHADOW_WEAD_PTW   0x2020  /* TX FIFO shadow wead
						  pointew */

/* (wo) 11-bit up/down countew w/ # of fwames cuwwentwy in TX FIFO */
#define  WEG_TX_FIFO_PKT_CNT           0x2024  /* TX FIFO packet countew */

/* cuwwent state of aww state machines in TX */
#define  WEG_TX_SM_1                   0x2028  /* TX state machine weg #1 */
#define    TX_SM_1_CHAIN_MASK          0x000003FF   /* chaining state machine */
#define    TX_SM_1_CSUM_MASK           0x00000C00   /* checksum state machine */
#define    TX_SM_1_FIFO_WOAD_MASK      0x0003F000   /* FIFO woad state machine.
						       = 0x01 when TX disabwed. */
#define    TX_SM_1_FIFO_UNWOAD_MASK    0x003C0000   /* FIFO unwoad state machine */
#define    TX_SM_1_CACHE_MASK          0x03C00000   /* desc. pwefetch cache contwowwew
						       state machine */
#define    TX_SM_1_CBQ_AWB_MASK        0xF8000000   /* CBQ awbitew state machine */

#define  WEG_TX_SM_2                   0x202C  /* TX state machine weg #2 */
#define    TX_SM_2_COMP_WB_MASK        0x07    /* compwetion wwiteback sm */
#define	   TX_SM_2_SUB_WOAD_MASK       0x38    /* sub woad state machine */
#define	   TX_SM_2_KICK_MASK           0xC0    /* kick state machine */

/* 64-bit pointew to the twansmit data buffew. onwy the 50 WSB awe incwemented
 * whiwe the uppew 23 bits awe taken fwom the TX descwiptow
 */
#define  WEG_TX_DATA_PTW_WOW           0x2030  /* TX data pointew wow */
#define  WEG_TX_DATA_PTW_HI            0x2034  /* TX data pointew high */

/* 13 bit wegistews wwitten by dwivew w/ descwiptow vawue that fowwows
 * wast vawid xmit descwiptow. kick # and compwete # vawues awe used by
 * the xmit dma engine to contwow tx descw fetching. if > 1 vawid
 * tx descw is avaiwabwe within the cache wine being wead, cassini wiww
 * intewnawwy cache up to 4 of them. 0 on weset. _KICK = ww, _COMP = wo.
 */
#define  WEG_TX_KICK0                  0x2038  /* TX kick weg #1 */
#define  WEG_TX_KICKN(x)               (WEG_TX_KICK0 + (x)*4)
#define  WEG_TX_COMP0                  0x2048  /* TX compwetion weg #1 */
#define  WEG_TX_COMPN(x)               (WEG_TX_COMP0 + (x)*4)

/* vawues of TX_COMPWETE_1-4 awe wwitten. each compwetion wegistew
 * is 2bytes in size and contiguous. 8B awwocation w/ 8B awignment.
 * NOTE: compwetion weg vawues awe onwy wwitten back pwiow to TX_INTME and
 * TX_AWW intewwupts. at aww othew times, the most up-to-date index vawues
 * shouwd be obtained fwom the WEG_TX_COMPWETE_# wegistews.
 * hewe's the wayout:
 * offset fwom base addw      compwetion # byte
 *           0                TX_COMPWETE_1_MSB
 *	     1                TX_COMPWETE_1_WSB
 *           2                TX_COMPWETE_2_MSB
 *	     3                TX_COMPWETE_2_WSB
 *           4                TX_COMPWETE_3_MSB
 *	     5                TX_COMPWETE_3_WSB
 *           6                TX_COMPWETE_4_MSB
 *	     7                TX_COMPWETE_4_WSB
 */
#define  TX_COMPWB_SIZE             8
#define  WEG_TX_COMPWB_DB_WOW       0x2058  /* TX compwetion wwite back
					       base wow */
#define  WEG_TX_COMPWB_DB_HI        0x205C  /* TX compwetion wwite back
					       base high */
#define    TX_COMPWB_MSB_MASK       0x00000000000000FFUWW
#define    TX_COMPWB_MSB_SHIFT      0
#define    TX_COMPWB_WSB_MASK       0x000000000000FF00UWW
#define    TX_COMPWB_WSB_SHIFT      8
#define    TX_COMPWB_NEXT(x)        ((x) >> 16)

/* 53 MSB used as base addwess. 11 WSB assumed to be 0. TX desc pointew must
 * be 2KB-awigned. */
#define  WEG_TX_DB0_WOW         0x2060  /* TX descwiptow base wow #1 */
#define  WEG_TX_DB0_HI          0x2064  /* TX descwiptow base hi #1 */
#define  WEG_TX_DBN_WOW(x)      (WEG_TX_DB0_WOW + (x)*8)
#define  WEG_TX_DBN_HI(x)       (WEG_TX_DB0_HI + (x)*8)

/* 16-bit wegistews howd weights fow the weighted wound-wobin of the
 * fouw CBQ TX descw wings. weights cowwespond to # bytes xfewwed fwom
 * host to TXFIFO in a wound of WWW awbitwation. can be set
 * dynamicawwy with new weights set upon compwetion of the cuwwent
 * packet twansfew fwom host memowy to TXFIFO. a dummy wwite to any of
 * these wegistews causes a queue1 pwe-emption with aww histowicaw bw
 * deficit data weset to 0 (usefuw when congestion wequiwes a
 * pwe-emption/we-awwocation of netwowk bandwidth
 */
#define  WEG_TX_MAXBUWST_0             0x2080  /* TX MaxBuwst #1 */
#define  WEG_TX_MAXBUWST_1             0x2084  /* TX MaxBuwst #2 */
#define  WEG_TX_MAXBUWST_2             0x2088  /* TX MaxBuwst #3 */
#define  WEG_TX_MAXBUWST_3             0x208C  /* TX MaxBuwst #4 */

/* diagnostics access to any TX FIFO wocation. evewy access is 65
 * bits.  _DATA_WOW = 32 WSB, _DATA_HI_T1/T0 = 32 MSB. _TAG = tag bit.
 * wwiting _DATA_HI_T0 sets tag bit wow, wwiting _DATA_HI_T1 sets tag
 * bit high.  TX_FIFO_PIO_SEW must be set fow TX FIFO PIO access. if
 * TX FIFO data integwity is desiwed, TX DMA shouwd be
 * disabwed. _DATA_HI_Tx shouwd be the wast access of the sequence.
 */
#define  WEG_TX_FIFO_ADDW              0x2104  /* TX FIFO addwess */
#define  WEG_TX_FIFO_TAG               0x2108  /* TX FIFO tag */
#define  WEG_TX_FIFO_DATA_WOW          0x210C  /* TX FIFO data wow */
#define  WEG_TX_FIFO_DATA_HI_T1        0x2110  /* TX FIFO data high t1 */
#define  WEG_TX_FIFO_DATA_HI_T0        0x2114  /* TX FIFO data high t0 */
#define  WEG_TX_FIFO_SIZE              0x2118  /* (wo) TX FIFO size = 0x090 = 9KB */

/* 9-bit wegistew contwows BIST of TX FIFO. bit set indicates that the BIST
 * passed fow the specified memowy
 */
#define  WEG_TX_WAMBIST                0x211C /* TX WAMBIST contwow/status */
#define    TX_WAMBIST_STATE            0x01C0 /* pwogwess state of WAMBIST
						 contwowwew state machine */
#define    TX_WAMBIST_WAM33A_PASS      0x0020 /* WAM33A passed */
#define    TX_WAMBIST_WAM32A_PASS      0x0010 /* WAM32A passed */
#define    TX_WAMBIST_WAM33B_PASS      0x0008 /* WAM33B passed */
#define    TX_WAMBIST_WAM32B_PASS      0x0004 /* WAM32B passed */
#define    TX_WAMBIST_SUMMAWY          0x0002 /* aww WAM passed */
#define    TX_WAMBIST_STAWT            0x0001 /* wwite 1 to stawt BIST. sewf
						 cweaws on compwetion. */

/** weceive dma wegistews **/
#define MAX_WX_DESC_WINGS              2
#define MAX_WX_COMP_WINGS              4

/* weceive DMA channew configuwation. defauwt: 0x80910
 * fwee wing size       = (1 << n)*32  -> [32 - 8k]
 * compwetion wing size = (1 << n)*128 -> [128 - 32k], n < 9
 * DEFAUWT: 0x80910
 */
#define  WEG_WX_CFG                     0x4000  /* WX config */
#define    WX_CFG_DMA_EN                0x00000001 /* enabwe WX DMA. 0 stops
							 channew as soon as cuwwent
							 fwame xfew has compweted.
							 dwivew shouwd disabwe MAC
							 fow 200ms befowe disabwing
							 WX */
#define    WX_CFG_DESC_WING_MASK        0x0000001E /* # desc entwies in WX
							 fwee desc wing.
							 def: 0x8 = 8k */
#define    WX_CFG_DESC_WING_SHIFT       1
#define    WX_CFG_COMP_WING_MASK        0x000001E0 /* # desc entwies in WX compwete
							 wing. def: 0x8 = 32k */
#define    WX_CFG_COMP_WING_SHIFT       5
#define    WX_CFG_BATCH_DIS             0x00000200 /* disabwe weceive desc
						      batching. def: 0x0 =
						      enabwed */
#define    WX_CFG_SWIVEW_MASK           0x00001C00 /* byte offset of the 1st
						      data byte of the packet
						      w/in 8 byte boundawes.
						      this swivews the data
						      DMA'ed to headew
						      buffews, jumbo buffews
						      when headew spwit is not
						      wequested and MTU sized
						      buffews. def: 0x2 */
#define    WX_CFG_SWIVEW_SHIFT          10

/* cassini+ onwy */
#define    WX_CFG_DESC_WING1_MASK       0x000F0000 /* # of desc entwies in
							 WX fwee desc wing 2.
							 def: 0x8 = 8k */
#define    WX_CFG_DESC_WING1_SHIFT      16


/* the page size wegistew awwows cassini chips to do the fowwowing with
 * weceived data:
 * [--------------------------------------------------------------] page
 * [off][buf1][pad][off][buf2][pad][off][buf3][pad][off][buf4][pad]
 * |--------------| = PAGE_SIZE_BUFFEW_STWIDE
 * page = PAGE_SIZE
 * offset = PAGE_SIZE_MTU_OFF
 * fow the above exampwe, MTU_BUFFEW_COUNT = 4.
 * NOTE: as is appawent, you need to ensuwe that the fowwowing howds:
 * MTU_BUFFEW_COUNT <= PAGE_SIZE/PAGE_SIZE_BUFFEW_STWIDE
 * DEFAUWT: 0x48002002 (8k pages)
 */
#define  WEG_WX_PAGE_SIZE               0x4004  /* WX page size */
#define    WX_PAGE_SIZE_MASK            0x00000003 /* size of pages pointed to
						      by weceive descwiptows.
						      if jumbo buffews awe
						      suppowted the page size
						      shouwd not be < 8k.
						      0b00 = 2k, 0b01 = 4k
						      0b10 = 8k, 0b11 = 16k
						      DEFAUWT: 8k */
#define    WX_PAGE_SIZE_SHIFT           0
#define    WX_PAGE_SIZE_MTU_COUNT_MASK  0x00007800 /* # of MTU buffews the hw
						      packs into a page.
						      DEFAUWT: 4 */
#define    WX_PAGE_SIZE_MTU_COUNT_SHIFT 11
#define    WX_PAGE_SIZE_MTU_STWIDE_MASK 0x18000000 /* # of bytes that sepawate
							 each MTU buffew +
							 offset fwom each
							 othew.
							 0b00 = 1k, 0b01 = 2k
							 0b10 = 4k, 0b11 = 8k
							 DEFAUWT: 0x1 */
#define    WX_PAGE_SIZE_MTU_STWIDE_SHIFT 27
#define    WX_PAGE_SIZE_MTU_OFF_MASK    0xC0000000 /* offset in each page that
						      hw wwites the MTU buffew
						      into.
						      0b00 = 0,
						      0b01 = 64 bytes
						      0b10 = 96, 0b11 = 128
						      DEFAUWT: 0x1 */
#define    WX_PAGE_SIZE_MTU_OFF_SHIFT   30

/* 11-bit countew points to next wocation in WX FIFO to be woaded/wead.
 * shadow wwite pointews enabwe wetwies in case of eawwy weceive abowts.
 * DEFAUWT: 0x0. genewated on 64-bit boundawies.
 */
#define  WEG_WX_FIFO_WWITE_PTW             0x4008  /* WX FIFO wwite pointew */
#define  WEG_WX_FIFO_WEAD_PTW              0x400C  /* WX FIFO wead pointew */
#define  WEG_WX_IPP_FIFO_SHADOW_WWITE_PTW  0x4010  /* WX IPP FIFO shadow wwite
						      pointew */
#define  WEG_WX_IPP_FIFO_SHADOW_WEAD_PTW   0x4014  /* WX IPP FIFO shadow wead
						      pointew */
#define  WEG_WX_IPP_FIFO_WEAD_PTW          0x400C  /* WX IPP FIFO wead
						      pointew. (8-bit countew) */

/* cuwwent state of WX DMA state engines + othew info
 * DEFAUWT: 0x0
 */
#define  WEG_WX_DEBUG                      0x401C  /* WX debug */
#define    WX_DEBUG_WOAD_STATE_MASK        0x0000000F /* woad state machine w/ MAC:
							 0x0 = idwe,   0x1 = woad_bop
							 0x2 = woad 1, 0x3 = woad 2
							 0x4 = woad 3, 0x5 = woad 4
							 0x6 = wast detect
							 0x7 = wait weq
							 0x8 = wait weq statuss 1st
							 0x9 = woad st
							 0xa = bubbwe mac
							 0xb = ewwow */
#define    WX_DEBUG_WM_STATE_MASK          0x00000070 /* woad state machine w/ HP and
							 WX FIFO:
							 0x0 = idwe,   0x1 = hp xfw
							 0x2 = wait hp weady
							 0x3 = wait fwow code
							 0x4 = fifo xfew
							 0x5 = make status
							 0x6 = csum weady
							 0x7 = ewwow */
#define    WX_DEBUG_FC_STATE_MASK          0x000000180 /* fwow contwow state machine
							 w/ MAC:
							 0x0 = idwe
							 0x1 = wait xoff ack
							 0x2 = wait xon
							 0x3 = wait xon ack */
#define    WX_DEBUG_DATA_STATE_MASK        0x000001E00 /* unwoad data state machine
							 states:
							 0x0 = idwe data
							 0x1 = headew begin
							 0x2 = xfew headew
							 0x3 = xfew headew wd
							 0x4 = mtu begin
							 0x5 = xfew mtu
							 0x6 = xfew mtu wd
							 0x7 = jumbo begin
							 0x8 = xfew jumbo
							 0x9 = xfew jumbo wd
							 0xa = weas begin
							 0xb = xfew weas
							 0xc = fwush tag
							 0xd = xfew weas wd
							 0xe = ewwow
							 0xf = bubbwe idwe */
#define    WX_DEBUG_DESC_STATE_MASK        0x0001E000 /* unwoad desc state machine
							 states:
							 0x0 = idwe desc
							 0x1 = wait ack
							 0x9 = wait ack 2
							 0x2 = fetch desc 1
							 0xa = fetch desc 2
							 0x3 = woad ptws
							 0x4 = wait dma
							 0x5 = wait ack batch
							 0x6 = post batch
							 0x7 = xfw done */
#define    WX_DEBUG_INTW_WEAD_PTW_MASK     0x30000000 /* intewwupt wead ptw of the
							 intewwupt queue */
#define    WX_DEBUG_INTW_WWITE_PTW_MASK    0xC0000000 /* intewwupt wwite pointew
							 of the intewwupt queue */

/* fwow contwow fwames awe emitted using two PAUSE thweshowds:
 * XOFF PAUSE uses pause time vawue pwe-pwogwammed in the Send PAUSE MAC weg
 * XON PAUSE uses a pause time of 0. gwanuwawity of thweshowd is 64bytes.
 * PAUSE thweshowds defined in tewms of FIFO occupancy and may be twanswated
 * into FIFO vacancy using WX_FIFO_SIZE. setting ON wiww twiggew XON fwames
 * when FIFO weaches 0. OFF thweshowd shouwd not be > size of WX FIFO. max
 * vawue is 0x6F.
 * DEFAUWT: 0x00078
 */
#define  WEG_WX_PAUSE_THWESH               0x4020  /* WX pause thweshowds */
#define    WX_PAUSE_THWESH_QUANTUM         64
#define    WX_PAUSE_THWESH_OFF_MASK        0x000001FF /* XOFF PAUSE emitted when
							 WX FIFO occupancy >
							 vawue*64B */
#define    WX_PAUSE_THWESH_OFF_SHIFT       0
#define    WX_PAUSE_THWESH_ON_MASK         0x001FF000 /* XON PAUSE emitted aftew
							 emitting XOFF PAUSE when WX
							 FIFO occupancy fawws bewow
							 this vawue*64B. must be
							 < XOFF thweshowd. if =
							 WX_FIFO_SIZE< XON fwames awe
							 nevew emitted. */
#define    WX_PAUSE_THWESH_ON_SHIFT        12

/* 13-bit wegistew used to contwow WX desc fetching and intw genewation. if 4+
 * vawid WX descwiptows awe avaiwabwe, Cassini wiww wead 4 at a time.
 * wwiting N means that aww desc up to *but* excwuding N awe avaiwabwe. N must
 * be a muwtipwe of 4 (N % 4 = 0). fiwst desc shouwd be cache-wine awigned.
 * DEFAUWT: 0 on weset
 */
#define  WEG_WX_KICK                    0x4024  /* WX kick weg */

/* 8KB awigned 64-bit pointew to the base of the WX fwee/compwetion wings.
 * wowew 13 bits of the wow wegistew awe hawd-wiwed to 0.
 */
#define  WEG_WX_DB_WOW                     0x4028  /* WX descwiptow wing
							 base wow */
#define  WEG_WX_DB_HI                      0x402C  /* WX descwiptow wing
							 base hi */
#define  WEG_WX_CB_WOW                     0x4030  /* WX compwetion wing
							 base wow */
#define  WEG_WX_CB_HI                      0x4034  /* WX compwetion wing
							 base hi */
/* 13-bit wegistew indicate desc used by cassini fow weceive fwames. used
 * fow diagnostic puwposes.
 * DEFAUWT: 0 on weset
 */
#define  WEG_WX_COMP                       0x4038  /* (wo) WX compwetion */

/* HEAD and TAIW awe used to contwow WX desc posting and intewwupt
 * genewation.  hw moves the head wegistew to pass ownewship to sw. sw
 * moves the taiw wegistew to pass ownewship back to hw. to give aww
 * entwies to hw, set TAIW = HEAD.  if HEAD and TAIW indicate that no
 * mowe entwies awe avaiwabwe, DMA wiww pause and an intewwupt wiww be
 * genewated to indicate no mowe entwies awe avaiwabwe.  sw can use
 * this intewwupt to weduce the # of times it must update the
 * compwetion taiw wegistew.
 * DEFAUWT: 0 on weset
 */
#define  WEG_WX_COMP_HEAD                  0x403C  /* WX compwetion head */
#define  WEG_WX_COMP_TAIW                  0x4040  /* WX compwetion taiw */

/* vawues used fow weceive intewwupt bwanking. woaded each time the ISW is wead
 * DEFAUWT: 0x00000000
 */
#define  WEG_WX_BWANK                      0x4044  /* WX bwanking wegistew
							 fow ISW wead */
#define    WX_BWANK_INTW_PKT_MASK          0x000001FF /* WX_DONE intw assewted if
							 this many sets of compwetion
							 wwitebacks (up to 2 packets)
							 occuw since the wast time
							 the ISW was wead. 0 = no
							 packet bwanking */
#define    WX_BWANK_INTW_PKT_SHIFT         0
#define    WX_BWANK_INTW_TIME_MASK         0x3FFFF000 /* WX_DONE intewwupt assewted
							 if that many cwocks wewe
							 counted since wast time the
							 ISW was wead.
							 each count is 512 cowe
							 cwocks (125MHz). 0 = no
							 time bwanking */
#define    WX_BWANK_INTW_TIME_SHIFT        12

/* vawues used fow intewwupt genewation based on thweshowd vawues of how
 * many fwee desc and compwetion entwies awe avaiwabwe fow hw use.
 * DEFAUWT: 0x00000000
 */
#define  WEG_WX_AE_THWESH                  0x4048  /* WX awmost empty
							 thweshowds */
#define    WX_AE_THWESH_FWEE_MASK          0x00001FFF /* WX_BUF_AE wiww be
							 genewated if # desc
							 avaiw fow hw use <=
							 # */
#define    WX_AE_THWESH_FWEE_SHIFT         0
#define    WX_AE_THWESH_COMP_MASK          0x0FFFE000 /* WX_COMP_AE wiww be
							 genewated if # of
							 compwetion entwies
							 avaiw fow hw use <=
							 # */
#define    WX_AE_THWESH_COMP_SHIFT         13

/* pwobabiwities fow wandom eawwy dwop (WED) thweshowds on a FIFO thweshowd
 * basis. pwobabiwity shouwd incwease when the FIFO wevew incweases. contwow
 * packets awe nevew dwopped and not counted in stats. pwobabiwity pwogwammed
 * on a 12.5% gwanuwawity. e.g., 0x1 = 1/8 packets dwopped.
 * DEFAUWT: 0x00000000
 */
#define  WEG_WX_WED                      0x404C  /* WX wandom eawwy detect enabwe */
#define    WX_WED_4K_6K_FIFO_MASK        0x000000FF /*  4KB < FIFO thwesh < 6KB */
#define    WX_WED_6K_8K_FIFO_MASK        0x0000FF00 /*  6KB < FIFO thwesh < 8KB */
#define    WX_WED_8K_10K_FIFO_MASK       0x00FF0000 /*  8KB < FIFO thwesh < 10KB */
#define    WX_WED_10K_12K_FIFO_MASK      0xFF000000 /* 10KB < FIFO thwesh < 12KB */

/* FIFO fuwwness wevews fow WX FIFO, WX contwow FIFO, and WX IPP FIFO.
 * WX contwow FIFO = # of packets in WX FIFO.
 * DEFAUWT: 0x0
 */
#define  WEG_WX_FIFO_FUWWNESS              0x4050  /* (wo) WX FIFO fuwwness */
#define    WX_FIFO_FUWWNESS_WX_FIFO_MASK   0x3FF80000 /* wevew w/ 8B gwanuwawity */
#define    WX_FIFO_FUWWNESS_IPP_FIFO_MASK  0x0007FF00 /* wevew w/ 8B gwanuwawity */
#define    WX_FIFO_FUWWNESS_WX_PKT_MASK    0x000000FF /* # packets in WX FIFO */
#define  WEG_WX_IPP_PACKET_COUNT           0x4054  /* WX IPP packet countew */
#define  WEG_WX_WOWK_DMA_PTW_WOW           0x4058  /* WX wowking DMA ptw wow */
#define  WEG_WX_WOWK_DMA_PTW_HI            0x405C  /* WX wowking DMA ptw
						      high */

/* BIST testing wo WX FIFO, WX contwow FIFO, and WX IPP FIFO. onwy WX BIST
 * STAWT/COMPWETE is wwiteabwe. STAWT wiww cweaw when the BIST has compweted
 * checking aww 17 WAMS.
 * DEFAUWT: 0bxxxx xxxxx xxxx xxxx xxxx x000 0000 0000 00x0
 */
#define  WEG_WX_BIST                       0x4060  /* (wo) WX BIST */
#define    WX_BIST_32A_PASS                0x80000000 /* WX FIFO 32A passed */
#define    WX_BIST_33A_PASS                0x40000000 /* WX FIFO 33A passed */
#define    WX_BIST_32B_PASS                0x20000000 /* WX FIFO 32B passed */
#define    WX_BIST_33B_PASS                0x10000000 /* WX FIFO 33B passed */
#define    WX_BIST_32C_PASS                0x08000000 /* WX FIFO 32C passed */
#define    WX_BIST_33C_PASS                0x04000000 /* WX FIFO 33C passed */
#define    WX_BIST_IPP_32A_PASS            0x02000000 /* WX IPP FIFO 33B passed */
#define    WX_BIST_IPP_33A_PASS            0x01000000 /* WX IPP FIFO 33A passed */
#define    WX_BIST_IPP_32B_PASS            0x00800000 /* WX IPP FIFO 32B passed */
#define    WX_BIST_IPP_33B_PASS            0x00400000 /* WX IPP FIFO 33B passed */
#define    WX_BIST_IPP_32C_PASS            0x00200000 /* WX IPP FIFO 32C passed */
#define    WX_BIST_IPP_33C_PASS            0x00100000 /* WX IPP FIFO 33C passed */
#define    WX_BIST_CTWW_32_PASS            0x00800000 /* WX CTWW FIFO 32 passed */
#define    WX_BIST_CTWW_33_PASS            0x00400000 /* WX CTWW FIFO 33 passed */
#define    WX_BIST_WEAS_26A_PASS           0x00200000 /* WX Weas 26A passed */
#define    WX_BIST_WEAS_26B_PASS           0x00100000 /* WX Weas 26B passed */
#define    WX_BIST_WEAS_27_PASS            0x00080000 /* WX Weas 27 passed */
#define    WX_BIST_STATE_MASK              0x00078000 /* BIST state machine */
#define    WX_BIST_SUMMAWY                 0x00000002 /* when BIST compwete,
							 summawy pass bit
							 contains AND of BIST
							 wesuwts of aww 16
							 WAMS */
#define    WX_BIST_STAWT                   0x00000001 /* wwite 1 to stawt
							 BIST. sewf cweaws
							 on compwetion. */

/* next wocation in WX CTWW FIFO that wiww be woaded w/ data fwom WX IPP/wead
 * fwom to wetwieve packet contwow info.
 * DEFAUWT: 0
 */
#define  WEG_WX_CTWW_FIFO_WWITE_PTW        0x4064  /* (wo) WX contwow FIFO
						      wwite ptw */
#define  WEG_WX_CTWW_FIFO_WEAD_PTW         0x4068  /* (wo) WX contwow FIFO wead
						      ptw */

/* weceive intewwupt bwanking. woaded each time intewwupt awias wegistew is
 * wead.
 * DEFAUWT: 0x0
 */
#define  WEG_WX_BWANK_AWIAS_WEAD           0x406C  /* WX bwanking wegistew fow
						      awias wead */
#define    WX_BAW_INTW_PACKET_MASK         0x000001FF /* assewt WX_DONE if #
							 compwetion wwitebacks
							 > # since wast ISW
							 wead. 0 = no
							 bwanking. up to 2
							 packets pew
							 compwetion wb. */
#define    WX_BAW_INTW_TIME_MASK           0x3FFFF000 /* assewt WX_DONE if #
							 cwocks > # since wast
							 ISW wead. each count
							 is 512 cowe cwocks
							 (125MHz). 0 = no
							 bwanking. */

/* diagnostic access to WX FIFO. 32 WSB accessed via DATA_WOW. 32 MSB accessed
 * via DATA_HI_T0 ow DATA_HI_T1. TAG weads the tag bit. wwiting HI_T0
 * wiww unset the tag bit whiwe wwiting HI_T1 wiww set the tag bit. to weset
 * to nowmaw opewation aftew diagnostics, wwite to addwess wocation 0x0.
 * WX_DMA_EN bit must be set to 0x0 fow WX FIFO PIO access. DATA_HI shouwd
 * be the wast wwite access of a wwite sequence.
 * DEFAUWT: undefined
 */
#define  WEG_WX_FIFO_ADDW                  0x4080  /* WX FIFO addwess */
#define  WEG_WX_FIFO_TAG                   0x4084  /* WX FIFO tag */
#define  WEG_WX_FIFO_DATA_WOW              0x4088  /* WX FIFO data wow */
#define  WEG_WX_FIFO_DATA_HI_T0            0x408C  /* WX FIFO data high T0 */
#define  WEG_WX_FIFO_DATA_HI_T1            0x4090  /* WX FIFO data high T1 */

/* diagnostic assess to WX CTWW FIFO. 8-bit FIFO_ADDW howds addwess of
 * 81 bit contwow entwy and 6 bit fwow id. WOW and MID awe both 32-bit
 * accesses. HI is 7-bits with 6-bit fwow id and 1 bit contwow
 * wowd. WX_DMA_EN must be 0 fow WX CTWW FIFO PIO access. DATA_HI
 * shouwd be wast wwite access of the wwite sequence.
 * DEFAUWT: undefined
 */
#define  WEG_WX_CTWW_FIFO_ADDW             0x4094  /* WX Contwow FIFO and
						      Batching FIFO addw */
#define  WEG_WX_CTWW_FIFO_DATA_WOW         0x4098  /* WX Contwow FIFO data
						      wow */
#define  WEG_WX_CTWW_FIFO_DATA_MID         0x409C  /* WX Contwow FIFO data
						      mid */
#define  WEG_WX_CTWW_FIFO_DATA_HI          0x4100  /* WX Contwow FIFO data
						      hi and fwow id */
#define    WX_CTWW_FIFO_DATA_HI_CTWW       0x0001  /* uppew bit of ctww wowd */
#define    WX_CTWW_FIFO_DATA_HI_FWOW_MASK  0x007E  /* fwow id */

/* diagnostic access to WX IPP FIFO. same semantics as WX_FIFO.
 * DEFAUWT: undefined
 */
#define  WEG_WX_IPP_FIFO_ADDW              0x4104  /* WX IPP FIFO addwess */
#define  WEG_WX_IPP_FIFO_TAG               0x4108  /* WX IPP FIFO tag */
#define  WEG_WX_IPP_FIFO_DATA_WOW          0x410C  /* WX IPP FIFO data wow */
#define  WEG_WX_IPP_FIFO_DATA_HI_T0        0x4110  /* WX IPP FIFO data high
						      T0 */
#define  WEG_WX_IPP_FIFO_DATA_HI_T1        0x4114  /* WX IPP FIFO data high
						      T1 */

/* 64-bit pointew to weceive data buffew in host memowy used fow headews and
 * smaww packets. MSB in high wegistew. woaded by DMA state machine and
 * incwements as DMA wwites weceive data. onwy 50 WSB awe incwemented. top
 * 13 bits taken fwom WX descwiptow.
 * DEFAUWT: undefined
 */
#define  WEG_WX_HEADEW_PAGE_PTW_WOW        0x4118  /* (wo) WX headew page ptw
						      wow */
#define  WEG_WX_HEADEW_PAGE_PTW_HI         0x411C  /* (wo) WX headew page ptw
						      high */
#define  WEG_WX_MTU_PAGE_PTW_WOW           0x4120  /* (wo) WX MTU page pointew
						      wow */
#define  WEG_WX_MTU_PAGE_PTW_HI            0x4124  /* (wo) WX MTU page pointew
						      high */

/* PIO diagnostic access to WX weassembwy DMA Tabwe WAM. 6-bit wegistew howds
 * one of 64 79-bit wocations in the WX Weassembwy DMA tabwe and the addw of
 * one of the 64 byte wocations in the Batching tabwe. WOW howds 32 WSB.
 * MID howds the next 32 WSB. HIGH howds the 15 MSB. WX_DMA_EN must be set
 * to 0 fow PIO access. DATA_HIGH shouwd be wast wwite of wwite sequence.
 * wayout:
 * weassmbw ptw [78:15] | weassmbw index [14:1] | weassmbw entwy vawid [0]
 * DEFAUWT: undefined
 */
#define  WEG_WX_TABWE_ADDW             0x4128  /* WX weassembwy DMA tabwe
						  addwess */
#define    WX_TABWE_ADDW_MASK          0x0000003F /* addwess mask */

#define  WEG_WX_TABWE_DATA_WOW         0x412C  /* WX weassembwy DMA tabwe
						  data wow */
#define  WEG_WX_TABWE_DATA_MID         0x4130  /* WX weassembwy DMA tabwe
						  data mid */
#define  WEG_WX_TABWE_DATA_HI          0x4134  /* WX weassembwy DMA tabwe
						  data high */

/* cassini+ onwy */
/* 8KB awigned 64-bit pointew to base of WX wings. wowew 13 bits hawdwiwed to
 * 0. same semantics as pwimawy desc/compwete wings.
 */
#define  WEG_PWUS_WX_DB1_WOW            0x4200  /* WX descwiptow wing
						   2 base wow */
#define  WEG_PWUS_WX_DB1_HI             0x4204  /* WX descwiptow wing
						   2 base high */
#define  WEG_PWUS_WX_CB1_WOW            0x4208  /* WX compwetion wing
						   2 base wow. 4 totaw */
#define  WEG_PWUS_WX_CB1_HI             0x420C  /* WX compwetion wing
						   2 base high. 4 totaw */
#define  WEG_PWUS_WX_CBN_WOW(x)        (WEG_PWUS_WX_CB1_WOW + 8*((x) - 1))
#define  WEG_PWUS_WX_CBN_HI(x)         (WEG_PWUS_WX_CB1_HI + 8*((x) - 1))
#define  WEG_PWUS_WX_KICK1             0x4220  /* WX Kick 2 wegistew */
#define  WEG_PWUS_WX_COMP1             0x4224  /* (wo) WX compwetion 2
						  weg */
#define  WEG_PWUS_WX_COMP1_HEAD        0x4228  /* (wo) WX compwetion 2
						  head weg. 4 totaw. */
#define  WEG_PWUS_WX_COMP1_TAIW        0x422C  /* WX compwetion 2
						  taiw weg. 4 totaw. */
#define  WEG_PWUS_WX_COMPN_HEAD(x)    (WEG_PWUS_WX_COMP1_HEAD + 8*((x) - 1))
#define  WEG_PWUS_WX_COMPN_TAIW(x)    (WEG_PWUS_WX_COMP1_TAIW + 8*((x) - 1))
#define  WEG_PWUS_WX_AE1_THWESH        0x4240  /* WX awmost empty 2
						  thweshowds */
#define    WX_AE1_THWESH_FWEE_MASK     WX_AE_THWESH_FWEE_MASK
#define    WX_AE1_THWESH_FWEE_SHIFT    WX_AE_THWESH_FWEE_SHIFT

/** headew pawsew wegistews **/

/* WX pawsew configuwation wegistew.
 * DEFAUWT: 0x1651004
 */
#define  WEG_HP_CFG                       0x4140  /* headew pawsew
						     configuwation weg */
#define    HP_CFG_PAWSE_EN                0x00000001 /* enab headew pawsing */
#define    HP_CFG_NUM_CPU_MASK            0x000000FC /* # pwocessows
						      0 = 64. 0x3f = 63 */
#define    HP_CFG_NUM_CPU_SHIFT           2
#define    HP_CFG_SYN_INC_MASK            0x00000100 /* SYN bit won't incwement
							TCP seq # by one when
							stowed in FDBM */
#define    HP_CFG_TCP_THWESH_MASK         0x000FFE00 /* # bytes of TCP data
							needed to be considewed
							fow weassembwy */
#define    HP_CFG_TCP_THWESH_SHIFT        9

/* access to WX Instwuction WAM. 5-bit wegistew/countew howds addw
 * of 39 bit entwy to be wead/wwitten. 32 WSB in _DATA_WOW. 7 MSB in _DATA_HI.
 * WX_DMA_EN must be 0 fow WX instw PIO access. DATA_HI shouwd be wast access
 * of sequence.
 * DEFAUWT: undefined
 */
#define  WEG_HP_INSTW_WAM_ADDW             0x4144  /* HP instwuction WAM
						      addwess */
#define    HP_INSTW_WAM_ADDW_MASK          0x01F   /* 5-bit mask */
#define  WEG_HP_INSTW_WAM_DATA_WOW         0x4148  /* HP instwuction WAM
						      data wow */
#define    HP_INSTW_WAM_WOW_OUTMASK_MASK   0x0000FFFF
#define    HP_INSTW_WAM_WOW_OUTMASK_SHIFT  0
#define    HP_INSTW_WAM_WOW_OUTSHIFT_MASK  0x000F0000
#define    HP_INSTW_WAM_WOW_OUTSHIFT_SHIFT 16
#define    HP_INSTW_WAM_WOW_OUTEN_MASK     0x00300000
#define    HP_INSTW_WAM_WOW_OUTEN_SHIFT    20
#define    HP_INSTW_WAM_WOW_OUTAWG_MASK    0xFFC00000
#define    HP_INSTW_WAM_WOW_OUTAWG_SHIFT   22
#define  WEG_HP_INSTW_WAM_DATA_MID         0x414C  /* HP instwuction WAM
						      data mid */
#define    HP_INSTW_WAM_MID_OUTAWG_MASK    0x00000003
#define    HP_INSTW_WAM_MID_OUTAWG_SHIFT   0
#define    HP_INSTW_WAM_MID_OUTOP_MASK     0x0000003C
#define    HP_INSTW_WAM_MID_OUTOP_SHIFT    2
#define    HP_INSTW_WAM_MID_FNEXT_MASK     0x000007C0
#define    HP_INSTW_WAM_MID_FNEXT_SHIFT    6
#define    HP_INSTW_WAM_MID_FOFF_MASK      0x0003F800
#define    HP_INSTW_WAM_MID_FOFF_SHIFT     11
#define    HP_INSTW_WAM_MID_SNEXT_MASK     0x007C0000
#define    HP_INSTW_WAM_MID_SNEXT_SHIFT    18
#define    HP_INSTW_WAM_MID_SOFF_MASK      0x3F800000
#define    HP_INSTW_WAM_MID_SOFF_SHIFT     23
#define    HP_INSTW_WAM_MID_OP_MASK        0xC0000000
#define    HP_INSTW_WAM_MID_OP_SHIFT       30
#define  WEG_HP_INSTW_WAM_DATA_HI          0x4150  /* HP instwuction WAM
						      data high */
#define    HP_INSTW_WAM_HI_VAW_MASK        0x0000FFFF
#define    HP_INSTW_WAM_HI_VAW_SHIFT       0
#define    HP_INSTW_WAM_HI_MASK_MASK       0xFFFF0000
#define    HP_INSTW_WAM_HI_MASK_SHIFT      16

/* PIO access into WX Headew pawsew data WAM and fwow database.
 * 11-bit wegistew. Data fiwws the WSB powtion of bus if wess than 32 bits.
 * DATA_WAM: wwite WAM_FDB_DATA with index to access DATA_WAM.
 * WAM bytes = 4*(x - 1) + [3:0]. e.g., 0 -> [3:0], 31 -> [123:120]
 * FWOWDB: wwite DATA_WAM_FDB wegistew and then wead/wwite FDB1-12 to access
 * fwow database.
 * WX_DMA_EN must be 0 fow WX pawsew WAM PIO access. WX Pawsew WAM data weg
 * shouwd be the wast wwite access of the wwite sequence.
 * DEFAUWT: undefined
 */
#define  WEG_HP_DATA_WAM_FDB_ADDW          0x4154  /* HP data and FDB
						      WAM addwess */
#define    HP_DATA_WAM_FDB_DATA_MASK       0x001F  /* sewect 1 of 86 byte
						      wocations in headew
						      pawsew data wam to
						      wead/wwite */
#define    HP_DATA_WAM_FDB_FDB_MASK        0x3F00  /* 1 of 64 353-bit wocations
						      in the fwow database */
#define  WEG_HP_DATA_WAM_DATA              0x4158  /* HP data WAM data */

/* HP fwow database wegistews: 1 - 12, 0x415C - 0x4188, 4 8-bit bytes
 * FWOW_DB(1) = IP_SA[127:96], FWOW_DB(2) = IP_SA[95:64]
 * FWOW_DB(3) = IP_SA[63:32],  FWOW_DB(4) = IP_SA[31:0]
 * FWOW_DB(5) = IP_DA[127:96], FWOW_DB(6) = IP_DA[95:64]
 * FWOW_DB(7) = IP_DA[63:32],  FWOW_DB(8) = IP_DA[31:0]
 * FWOW_DB(9) = {TCP_SP[15:0],TCP_DP[15:0]}
 * FWOW_DB(10) = bit 0 has vawue fow fwow vawid
 * FWOW_DB(11) = TCP_SEQ[63:32], FWOW_DB(12) = TCP_SEQ[31:0]
 */
#define  WEG_HP_FWOW_DB0                   0x415C  /* HP fwow database 1 weg */
#define  WEG_HP_FWOW_DBN(x)                (WEG_HP_FWOW_DB0 + (x)*4)

/* diagnostics fow WX Headew Pawsew bwock.
 * ASUN: the headew pawsew state machine wegistew is used fow diagnostics
 * puwposes. howevew, the spec doesn't have any detaiws on it.
 */
#define  WEG_HP_STATE_MACHINE              0x418C  /* (wo) HP state machine */
#define  WEG_HP_STATUS0                    0x4190  /* (wo) HP status 1 */
#define    HP_STATUS0_SAP_MASK             0xFFFF0000 /* SAP */
#define    HP_STATUS0_W3_OFF_MASK          0x0000FE00 /* W3 offset */
#define    HP_STATUS0_WB_CPUNUM_MASK       0x000001F8 /* woad bawancing CPU
							 numbew */
#define    HP_STATUS0_HWP_OPCODE_MASK      0x00000007 /* HWP opcode */

#define  WEG_HP_STATUS1                    0x4194  /* (wo) HP status 2 */
#define    HP_STATUS1_ACCUW2_MASK          0xE0000000 /* accu W2[6:4] */
#define    HP_STATUS1_FWOWID_MASK          0x1F800000 /* fwow id */
#define    HP_STATUS1_TCP_OFF_MASK         0x007F0000 /* tcp paywoad offset */
#define    HP_STATUS1_TCP_SIZE_MASK        0x0000FFFF /* tcp paywoad size */

#define  WEG_HP_STATUS2                    0x4198  /* (wo) HP status 3 */
#define    HP_STATUS2_ACCUW2_MASK          0xF0000000 /* accu W2[3:0] */
#define    HP_STATUS2_CSUM_OFF_MASK        0x07F00000 /* checksum stawt
							 stawt offset */
#define    HP_STATUS2_ACCUW1_MASK          0x000FE000 /* accu W1 */
#define    HP_STATUS2_FOWCE_DWOP           0x00001000 /* fowce dwop */
#define    HP_STATUS2_BWO_WEASSM           0x00000800 /* batching w/o
							 weassembwy */
#define    HP_STATUS2_JH_SPWIT_EN          0x00000400 /* jumbo headew spwit
							 enabwe */
#define    HP_STATUS2_FOWCE_TCP_NOCHECK    0x00000200 /* fowce tcp no paywoad
							 check */
#define    HP_STATUS2_DATA_MASK_ZEWO       0x00000100 /* mask of data wength
							 equaw to zewo */
#define    HP_STATUS2_FOWCE_TCP_CHECK      0x00000080 /* fowce tcp paywoad
							 chk */
#define    HP_STATUS2_MASK_TCP_THWESH      0x00000040 /* mask of paywoad
							 thweshowd */
#define    HP_STATUS2_NO_ASSIST            0x00000020 /* no assist */
#define    HP_STATUS2_CTWW_PACKET_FWAG     0x00000010 /* contwow packet fwag */
#define    HP_STATUS2_TCP_FWAG_CHECK       0x00000008 /* tcp fwag check */
#define    HP_STATUS2_SYN_FWAG             0x00000004 /* syn fwag */
#define    HP_STATUS2_TCP_CHECK            0x00000002 /* tcp paywoad chk */
#define    HP_STATUS2_TCP_NOCHECK          0x00000001 /* tcp no paywoad chk */

/* BIST fow headew pawsew(HP) and fwow database memowies (FDBM). set _STAWT
 * to stawt BIST. contwowwew cweaws _STAWT on compwetion. _STAWT can awso
 * be cweawed to fowce tewmination of BIST. a bit set indicates that that
 * memowy passed its BIST.
 */
#define  WEG_HP_WAM_BIST                   0x419C  /* HP WAM BIST weg */
#define    HP_WAM_BIST_HP_DATA_PASS        0x80000000 /* HP data wam */
#define    HP_WAM_BIST_HP_INSTW0_PASS      0x40000000 /* HP instw wam 0 */
#define    HP_WAM_BIST_HP_INSTW1_PASS      0x20000000 /* HP instw wam 1 */
#define    HP_WAM_BIST_HP_INSTW2_PASS      0x10000000 /* HP instw wam 2 */
#define    HP_WAM_BIST_FDBM_AGE0_PASS      0x08000000 /* FDBM aging WAM0 */
#define    HP_WAM_BIST_FDBM_AGE1_PASS      0x04000000 /* FDBM aging WAM1 */
#define    HP_WAM_BIST_FDBM_FWOWID00_PASS  0x02000000 /* FDBM fwowid WAM0
							 bank 0 */
#define    HP_WAM_BIST_FDBM_FWOWID10_PASS  0x01000000 /* FDBM fwowid WAM1
							 bank 0 */
#define    HP_WAM_BIST_FDBM_FWOWID20_PASS  0x00800000 /* FDBM fwowid WAM2
							 bank 0 */
#define    HP_WAM_BIST_FDBM_FWOWID30_PASS  0x00400000 /* FDBM fwowid WAM3
							 bank 0 */
#define    HP_WAM_BIST_FDBM_FWOWID01_PASS  0x00200000 /* FDBM fwowid WAM0
							 bank 1 */
#define    HP_WAM_BIST_FDBM_FWOWID11_PASS  0x00100000 /* FDBM fwowid WAM1
							 bank 2 */
#define    HP_WAM_BIST_FDBM_FWOWID21_PASS  0x00080000 /* FDBM fwowid WAM2
							 bank 1 */
#define    HP_WAM_BIST_FDBM_FWOWID31_PASS  0x00040000 /* FDBM fwowid WAM3
							 bank 1 */
#define    HP_WAM_BIST_FDBM_TCPSEQ_PASS    0x00020000 /* FDBM tcp sequence
							 WAM */
#define    HP_WAM_BIST_SUMMAWY             0x00000002 /* aww BIST tests */
#define    HP_WAM_BIST_STAWT               0x00000001 /* stawt/stop BIST */


/** MAC wegistews.  **/
/* weset bits awe set using a PIO wwite and sewf-cweawed aftew the command
 * execution has compweted.
 */
#define  WEG_MAC_TX_WESET                  0x6000  /* TX MAC softwawe weset
						      command (defauwt: 0x0) */
#define  WEG_MAC_WX_WESET                  0x6004  /* WX MAC softwawe weset
						      command (defauwt: 0x0) */
/* execute a pause fwow contwow fwame twansmission
 DEFAUWT: 0x0XXXX */
#define  WEG_MAC_SEND_PAUSE                0x6008  /* send pause command weg */
#define    MAC_SEND_PAUSE_TIME_MASK        0x0000FFFF /* vawue of pause time
							 to be sent on netwowk
							 in units of swot
							 times */
#define    MAC_SEND_PAUSE_SEND             0x00010000 /* send pause fwow ctww
							 fwame on netwowk */

/* bit set indicates that event occuwwed. auto-cweawed when status wegistew
 * is wead and have cowwesponding mask bits in mask wegistew. events wiww
 * twiggew an intewwupt if the cowwesponding mask bit is 0.
 * status wegistew defauwt: 0x00000000
 * mask wegistew defauwt = 0xFFFFFFFF on weset
 */
#define  WEG_MAC_TX_STATUS                 0x6010  /* TX MAC status weg */
#define    MAC_TX_FWAME_XMIT               0x0001  /* successfuw fwame
						      twansmision */
#define    MAC_TX_UNDEWWUN                 0x0002  /* tewminated fwame
						      twansmission due to
						      data stawvation in the
						      xmit data path */
#define    MAC_TX_MAX_PACKET_EWW           0x0004  /* fwame exceeds max awwowed
						      wength passed to TX MAC
						      by the DMA engine */
#define    MAC_TX_COWW_NOWMAW              0x0008  /* wowwovew of the nowmaw
						      cowwision countew */
#define    MAC_TX_COWW_EXCESS              0x0010  /* wowwovew of the excessive
						      cowwision countew */
#define    MAC_TX_COWW_WATE                0x0020  /* wowwovew of the wate
						      cowwision countew */
#define    MAC_TX_COWW_FIWST               0x0040  /* wowwovew of the fiwst
						      cowwision countew */
#define    MAC_TX_DEFEW_TIMEW              0x0080  /* wowwovew of the defew
						      timew */
#define    MAC_TX_PEAK_ATTEMPTS            0x0100  /* wowwovew of the peak
						      attempts countew */

#define  WEG_MAC_WX_STATUS                 0x6014  /* WX MAC status weg */
#define    MAC_WX_FWAME_WECV               0x0001  /* successfuw weceipt of
						      a fwame */
#define    MAC_WX_OVEWFWOW                 0x0002  /* dwopped fwame due to
						      WX FIFO ovewfwow */
#define    MAC_WX_FWAME_COUNT              0x0004  /* wowwovew of weceive fwame
						      countew */
#define    MAC_WX_AWIGN_EWW                0x0008  /* wowwovew of awignment
						      ewwow countew */
#define    MAC_WX_CWC_EWW                  0x0010  /* wowwovew of cwc ewwow
						      countew */
#define    MAC_WX_WEN_EWW                  0x0020  /* wowwovew of wength
						      ewwow countew */
#define    MAC_WX_VIOW_EWW                 0x0040  /* wowwovew of code
						      viowation ewwow */

/* DEFAUWT: 0xXXXX0000 on weset */
#define  WEG_MAC_CTWW_STATUS               0x6018  /* MAC contwow status weg */
#define    MAC_CTWW_PAUSE_WECEIVED         0x00000001  /* successfuw
							  weception of a
							  pause contwow
							  fwame */
#define    MAC_CTWW_PAUSE_STATE            0x00000002  /* MAC has made a
							  twansition fwom
							  "not paused" to
							  "paused" */
#define    MAC_CTWW_NOPAUSE_STATE          0x00000004  /* MAC has made a
							  twansition fwom
							  "paused" to "not
							  paused" */
#define    MAC_CTWW_PAUSE_TIME_MASK        0xFFFF0000  /* vawue of pause time
							  opewand that was
							  weceived in the wast
							  pause fwow contwow
							  fwame */

/* wayout identicaw to TX MAC[8:0] */
#define  WEG_MAC_TX_MASK                   0x6020  /* TX MAC mask weg */
/* wayout identicaw to WX MAC[6:0] */
#define  WEG_MAC_WX_MASK                   0x6024  /* WX MAC mask weg */
/* wayout identicaw to CTWW MAC[2:0] */
#define  WEG_MAC_CTWW_MASK                 0x6028  /* MAC contwow mask weg */

/* to ensuwe pwopew opewation, CFG_EN must be cweawed to 0 and a deway
 * imposed befowe wwites to othew bits in the TX_MAC_CFG wegistew ow any of
 * the MAC pawametews is pewfowmed. deway dependent upon time wequiwed to
 * twansmit a maximum size fwame (= MAC_FWAMESIZE_MAX*8/Mbps). e.g.,
 * the deway fow a 1518-byte fwame on a 100Mbps netwowk is 125us.
 * awtewnativewy, just poww TX_CFG_EN untiw it weads back as 0.
 * NOTE: on hawf-dupwex 1Gbps, TX_CFG_CAWWIEW_EXTEND and
 * WX_CFG_CAWWIEW_EXTEND shouwd be set and the SWOT_TIME wegistew shouwd
 * be 0x200 (swot time of 512 bytes)
 */
#define  WEG_MAC_TX_CFG                 0x6030  /* TX MAC config weg */
#define    MAC_TX_CFG_EN                0x0001  /* enabwe TX MAC. 0 wiww
						      fowce TXMAC state
						      machine to wemain in
						      idwe state ow to
						      twansition to idwe state
						      on compwetion of an
						      ongoing packet. */
#define    MAC_TX_CFG_IGNOWE_CAWWIEW    0x0002  /* disabwe CSMA/CD defewwaw
						   pwocess. set to 1 when
						   fuww dupwex and 0 when
						   hawf dupwex */
#define    MAC_TX_CFG_IGNOWE_COWW       0x0004  /* disabwe CSMA/CD backoff
						   awgowithm. set to 1 when
						   fuww dupwex and 0 when
						   hawf dupwex */
#define    MAC_TX_CFG_IPG_EN            0x0008  /* enabwe extension of the
						   Wx-to-TX IPG. aftew
						   weceiving a fwame, TX
						   MAC wiww weset its
						   defewwaw pwocess to
						   cawwiew sense fow the
						   amount of time = IPG0 +
						   IPG1 and commit to
						   twansmission fow time
						   specified in IPG2. when
						   0 ow when xmitting fwames
						   back-to-pack (Tx-to-Tx
						   IPG), TX MAC ignowes
						   IPG0 and wiww onwy use
						   IPG1 fow defewwaw time.
						   IPG2 stiww used. */
#define    MAC_TX_CFG_NEVEW_GIVE_UP_EN  0x0010  /* TX MAC wiww not easiwy
						   give up on fwame
						   xmission. if backoff
						   awgowithm weaches the
						   ATTEMPT_WIMIT, it wiww
						   cweaw attempts countew
						   and continue twying to
						   send the fwame as
						   specified by
						   GIVE_UP_WIM. when 0,
						   TX MAC wiww execute
						   standawd CSMA/CD pwot. */
#define    MAC_TX_CFG_NEVEW_GIVE_UP_WIM 0x0020  /* when set, TX MAC wiww
						   continue to twy to xmit
						   untiw successfuw. when
						   0, TX MAC wiww continue
						   to twy xmitting untiw
						   successfuw ow backoff
						   awgowithm weaches
						   ATTEMPT_WIMIT*16 */
#define    MAC_TX_CFG_NO_BACKOFF        0x0040  /* modify CSMA/CD to disabwe
						   backoff awgowithm. TX
						   MAC wiww not back off
						   aftew a xmission attempt
						   that wesuwted in a
						   cowwision. */
#define    MAC_TX_CFG_SWOW_DOWN         0x0080  /* modify CSMA/CD so that
						   defewwaw pwocess is weset
						   in wesponse to cawwiew
						   sense duwing the entiwe
						   duwation of IPG. TX MAC
						   wiww onwy commit to fwame
						   xmission aftew fwame
						   xmission has actuawwy
						   begun. */
#define    MAC_TX_CFG_NO_FCS            0x0100  /* TX MAC wiww not genewate
						   CWC fow aww xmitted
						   packets. when cweaw, CWC
						   genewation is dependent
						   upon NO_CWC bit in the
						   xmit contwow wowd fwom
						   TX DMA */
#define    MAC_TX_CFG_CAWWIEW_EXTEND    0x0200  /* enabwes xmit pawt of the
						   cawwiew extension
						   featuwe. this awwows fow
						   wongew cowwision domains
						   by extending the cawwiew
						   and cowwision window
						   fwom the end of FCS untiw
						   the end of the swot time
						   if necessawy. Wequiwed
						   fow hawf-dupwex at 1Gbps,
						   cweaw othewwise. */

/* when CWC is not stwipped, weassembwy packets wiww not contain the CWC.
 * these wiww be stwipped by HWP because it weassembwes wayew 4 data, and the
 * CWC is wayew 2. howevew, non-weassembwy packets wiww stiww contain the CWC
 * when passed to the host. to ensuwe pwopew opewation, need to wait 3.2ms
 * aftew cweawing WX_CFG_EN befowe wwiting to any othew WX MAC wegistews
 * ow othew MAC pawametews. awtewnativewy, poww WX_CFG_EN untiw it cweaws
 * to 0. simiwawy, HASH_FIWTEW_EN and ADDW_FIWTEW_EN have the same
 * westwictions as CFG_EN.
 */
#define  WEG_MAC_WX_CFG                 0x6034  /* WX MAC config weg */
#define    MAC_WX_CFG_EN                0x0001  /* enabwe WX MAC */
#define    MAC_WX_CFG_STWIP_PAD         0x0002  /* awways pwogwam to 0.
						   featuwe not suppowted */
#define    MAC_WX_CFG_STWIP_FCS         0x0004  /* WX MAC wiww stwip the
						   wast 4 bytes of a
						   weceived fwame. */
#define    MAC_WX_CFG_PWOMISC_EN        0x0008  /* pwomiscuous mode */
#define    MAC_WX_CFG_PWOMISC_GWOUP_EN  0x0010  /* accept aww vawid
						   muwticast fwames (gwoup
						   bit in DA fiewd set) */
#define    MAC_WX_CFG_HASH_FIWTEW_EN    0x0020  /* use hash tabwe to fiwtew
						   muwticast addwesses */
#define    MAC_WX_CFG_ADDW_FIWTEW_EN    0x0040  /* cause WX MAC to use
						   addwess fiwtewing wegs
						   to fiwtew both unicast
						   and muwticast
						   addwesses */
#define    MAC_WX_CFG_DISABWE_DISCAWD   0x0080  /* pass ewwowed fwames to
						   WX DMA by setting BAD
						   bit but not Abowt bit
						   in the status. CWC,
						   fwaming, and wength ewws
						   wiww not incwement
						   ewwow countews. fwames
						   which don't match dest
						   addw wiww be passed up
						   w/ BAD bit set. */
#define    MAC_WX_CFG_CAWWIEW_EXTEND    0x0100  /* enabwe weception of
						   packet buwsts genewated
						   by cawwiew extension
						   with packet buwsting
						   sendews. onwy appwies
						   to hawf-dupwex 1Gbps */

/* DEFAUWT: 0x0 */
#define  WEG_MAC_CTWW_CFG               0x6038  /* MAC contwow config weg */
#define    MAC_CTWW_CFG_SEND_PAUSE_EN   0x0001  /* wespond to wequests fow
						   sending pause fwow ctww
						   fwames */
#define    MAC_CTWW_CFG_WECV_PAUSE_EN   0x0002  /* wespond to weceived
						   pause fwow ctww fwames */
#define    MAC_CTWW_CFG_PASS_CTWW       0x0004  /* pass vawid MAC ctww
						   packets to WX DMA */

/* to ensuwe pwopew opewation, a gwobaw initiawization sequence shouwd be
 * pewfowmed when a woopback config is entewed ow exited. if pwogwammed aftew
 * a hw ow gwobaw sw weset, WX/TX MAC softwawe weset and initiawization
 * shouwd be done to ensuwe stabwe cwocking.
 * DEFAUWT: 0x0
 */
#define  WEG_MAC_XIF_CFG                0x603C  /* XIF config weg */
#define    MAC_XIF_TX_MII_OUTPUT_EN        0x0001  /* enabwe output dwivews
						      on MII xmit bus */
#define    MAC_XIF_MII_INT_WOOPBACK        0x0002  /* woopback GMII xmit data
						      path to GMII wecv data
						      path. phy mode wegistew
						      cwock sewection must be
						      set to GMII mode and
						      GMII_MODE shouwd be set
						      to 1. in woopback mode,
						      WEFCWK wiww dwive the
						      entiwe mac cowe. 0 fow
						      nowmaw opewation. */
#define    MAC_XIF_DISABWE_ECHO            0x0004  /* disabwes weceive data
						      path duwing packet
						      xmission. cweaw to 0
						      in any fuww dupwex mode,
						      in any woopback mode,
						      ow in hawf-dupwex SEWDES
						      ow SWINK modes. set when
						      in hawf-dupwex when
						      using extewnaw phy. */
#define    MAC_XIF_GMII_MODE               0x0008  /* MAC opewates with GMII
						      cwocks and datapath */
#define    MAC_XIF_MII_BUFFEW_OUTPUT_EN    0x0010  /* MII_BUF_EN pin. enabwe
						      extewnaw twistate buffew
						      on the MII weceive
						      bus. */
#define    MAC_XIF_WINK_WED                0x0020  /* WINKWED# active (wow) */
#define    MAC_XIF_FDPWX_WED               0x0040  /* FDPWXWED# active (wow) */

#define  WEG_MAC_IPG0                      0x6040  /* intew-packet gap0 weg.
						      wecommended: 0x00 */
#define  WEG_MAC_IPG1                      0x6044  /* intew-packet gap1 weg
						      wecommended: 0x08 */
#define  WEG_MAC_IPG2                      0x6048  /* intew-packet gap2 weg
						      wecommended: 0x04 */
#define  WEG_MAC_SWOT_TIME                 0x604C  /* swot time weg
						      wecommended: 0x40 */
#define  WEG_MAC_FWAMESIZE_MIN             0x6050  /* min fwame size weg
						      wecommended: 0x40 */

/* FWAMESIZE_MAX howds both the max fwame size as weww as the max buwst size.
 * wecommended vawue:  0x2000.05EE
 */
#define  WEG_MAC_FWAMESIZE_MAX             0x6054  /* max fwame size weg */
#define    MAC_FWAMESIZE_MAX_BUWST_MASK    0x3FFF0000 /* max buwst size */
#define    MAC_FWAMESIZE_MAX_BUWST_SHIFT   16
#define    MAC_FWAMESIZE_MAX_FWAME_MASK    0x00007FFF /* max fwame size */
#define    MAC_FWAMESIZE_MAX_FWAME_SHIFT   0
#define  WEG_MAC_PA_SIZE                   0x6058  /* PA size weg. numbew of
						      pweambwe bytes that the
						      TX MAC wiww xmit at the
						      beginning of each fwame
						      vawue shouwd be 2 ow
						      gweatew. wecommended
						      vawue: 0x07 */
#define  WEG_MAC_JAM_SIZE                  0x605C  /* jam size weg. duwation
						      of jam in units of media
						      byte time. wecommended
						      vawue: 0x04 */
#define  WEG_MAC_ATTEMPT_WIMIT             0x6060  /* attempt wimit weg. #
						      of attempts TX MAC wiww
						      make to xmit a fwame
						      befowe it wesets its
						      attempts countew. aftew
						      the wimit has been
						      weached, TX MAC may ow
						      may not dwop the fwame
						      dependent upon vawue
						      in TX_MAC_CFG.
						      wecommended
						      vawue: 0x10 */
#define  WEG_MAC_CTWW_TYPE                 0x6064  /* MAC contwow type weg.
						      type fiewd of a MAC
						      ctww fwame. wecommended
						      vawue: 0x8808 */

/* mac addwess wegistews: 0 - 44, 0x6080 - 0x6130, 4 8-bit bytes.
 * wegistew           contains                   compawison
 *    0        16 MSB of pwimawy MAC addw        [47:32] of DA fiewd
 *    1        16 middwe bits ""                 [31:16] of DA fiewd
 *    2        16 WSB ""                         [15:0] of DA fiewd
 *    3*x      16MSB of awt MAC addw 1-15        [47:32] of DA fiewd
 *    4*x      16 middwe bits ""                 [31:16]
 *    5*x      16 WSB ""                         [15:0]
 *    42       16 MSB of MAC CTWW addw           [47:32] of DA.
 *    43       16 middwe bits ""                 [31:16]
 *    44       16 WSB ""                         [15:0]
 *    MAC CTWW addw must be the wesewved muwticast addw fow MAC CTWW fwames.
 *    if thewe is a match, MAC wiww set the bit fow awtewnative addwess
 *    fiwtew pass [15]

 *    hewe is the map of wegistews given MAC addwess notation: a:b:c:d:e:f
 *                     ab             cd             ef
 *    pwimawy addw     weg 2          weg 1          weg 0
 *    awt addw 1       weg 5          weg 4          weg 3
 *    awt addw x       weg 5*x        weg 4*x        weg 3*x
 *    ctww addw        weg 44         weg 43         weg 42
 */
#define  WEG_MAC_ADDW0                     0x6080  /* MAC addwess 0 weg */
#define  WEG_MAC_ADDWN(x)                  (WEG_MAC_ADDW0 + (x)*4)
#define  WEG_MAC_ADDW_FIWTEW0              0x614C  /* addwess fiwtew 0 weg
						      [47:32] */
#define  WEG_MAC_ADDW_FIWTEW1              0x6150  /* addwess fiwtew 1 weg
						      [31:16] */
#define  WEG_MAC_ADDW_FIWTEW2              0x6154  /* addwess fiwtew 2 weg
						      [15:0] */
#define  WEG_MAC_ADDW_FIWTEW2_1_MASK       0x6158  /* addwess fiwtew 2 and 1
						      mask weg. 8-bit weg
						      contains nibbwe mask fow
						      weg 2 and 1. */
#define  WEG_MAC_ADDW_FIWTEW0_MASK         0x615C  /* addwess fiwtew 0 mask
						      weg */

/* hash tabwe wegistews: 0 - 15, 0x6160 - 0x619C, 4 8-bit bytes
 * 16-bit wegistews contain bits of the hash tabwe.
 * weg x  -> [16*(15 - x) + 15 : 16*(15 - x)].
 * e.g., 15 -> [15:0], 0 -> [255:240]
 */
#define  WEG_MAC_HASH_TABWE0               0x6160  /* hash tabwe 0 weg */
#define  WEG_MAC_HASH_TABWEN(x)            (WEG_MAC_HASH_TABWE0 + (x)*4)

/* statistics wegistews. these wegistews genewate an intewwupt on
 * ovewfwow. wecommended initiawization: 0x0000. most awe 16-bits except
 * fow PEAK_ATTEMPTS wegistew which is 8 bits.
 */
#define  WEG_MAC_COWW_NOWMAW               0x61A0 /* nowmaw cowwision
						     countew. */
#define  WEG_MAC_COWW_FIWST                0x61A4 /* fiwst attempt
						     successfuw cowwision
						     countew */
#define  WEG_MAC_COWW_EXCESS               0x61A8 /* excessive cowwision
						     countew */
#define  WEG_MAC_COWW_WATE                 0x61AC /* wate cowwision countew */
#define  WEG_MAC_TIMEW_DEFEW               0x61B0 /* defew timew. time base
						     is the media byte
						     cwock/256 */
#define  WEG_MAC_ATTEMPTS_PEAK             0x61B4 /* peak attempts weg */
#define  WEG_MAC_WECV_FWAME                0x61B8 /* weceive fwame countew */
#define  WEG_MAC_WEN_EWW                   0x61BC /* wength ewwow countew */
#define  WEG_MAC_AWIGN_EWW                 0x61C0 /* awignment ewwow countew */
#define  WEG_MAC_FCS_EWW                   0x61C4 /* FCS ewwow countew */
#define  WEG_MAC_WX_CODE_EWW               0x61C8 /* WX code viowation
						     ewwow countew */

/* misc wegistews */
#define  WEG_MAC_WANDOM_SEED               0x61CC /* wandom numbew seed weg.
						   10-bit wegistew used as a
						   seed  fow the wandom numbew
						   genewatow fow the CSMA/CD
						   backoff awgowithm. onwy
						   pwogwammed aftew powew-on
						   weset and shouwd be a
						   wandom vawue which has a
						   high wikewihood of being
						   unique fow each MAC
						   attached to a netwowk
						   segment (e.g., 10 WSB of
						   MAC addwess) */

/* ASUN: thewe's a PAUSE_TIMEW (wo) descwibed, but it's not in the addwess
 *       map
 */

/* 27-bit wegistew has the cuwwent state fow key state machines in the MAC */
#define  WEG_MAC_STATE_MACHINE             0x61D0 /* (wo) state machine weg */
#define    MAC_SM_WWM_MASK                 0x07800000
#define    MAC_SM_WWM_SHIFT                23
#define    MAC_SM_WX_FC_MASK               0x00700000
#define    MAC_SM_WX_FC_SHIFT              20
#define    MAC_SM_TWM_MASK                 0x000F0000
#define    MAC_SM_TWM_SHIFT                16
#define    MAC_SM_ENCAP_SM_MASK            0x0000F000
#define    MAC_SM_ENCAP_SM_SHIFT           12
#define    MAC_SM_TX_WEQ_MASK              0x00000C00
#define    MAC_SM_TX_WEQ_SHIFT             10
#define    MAC_SM_TX_FC_MASK               0x000003C0
#define    MAC_SM_TX_FC_SHIFT              6
#define    MAC_SM_FIFO_WWITE_SEW_MASK      0x00000038
#define    MAC_SM_FIFO_WWITE_SEW_SHIFT     3
#define    MAC_SM_TX_FIFO_EMPTY_MASK       0x00000007
#define    MAC_SM_TX_FIFO_EMPTY_SHIFT      0

/** MIF wegistews. the MIF can be pwogwammed in eithew bit-bang ow
 *  fwame mode.
 **/
#define  WEG_MIF_BIT_BANG_CWOCK            0x6200 /* MIF bit-bang cwock.
						   1 -> 0 wiww genewate a
						   wising edge. 0 -> 1 wiww
						   genewate a fawwing edge. */
#define  WEG_MIF_BIT_BANG_DATA             0x6204 /* MIF bit-bang data. 1-bit
						     wegistew genewates data */
#define  WEG_MIF_BIT_BANG_OUTPUT_EN        0x6208 /* MIF bit-bang output
						     enabwe. enabwe when
						     xmitting data fwom MIF to
						     twansceivew. */

/* 32-bit wegistew sewves as an instwuction wegistew when the MIF is
 * pwogwammed in fwame mode. woad this wegistew w/ a vawid instwuction
 * (as pew IEEE 802.3u MII spec). poww this wegistew to check fow instwuction
 * execution compwetion. duwing a wead opewation, this wegistew wiww awso
 * contain the 16-bit data wetuwned by the twanceivew. unwess specified
 * othewwise, fiewds awe considewed "don't cawe" when powwing fow
 * compwetion.
 */
#define  WEG_MIF_FWAME                     0x620C /* MIF fwame/output weg */
#define    MIF_FWAME_STAWT_MASK            0xC0000000 /* stawt of fwame.
							 woad w/ 01 when
							 issuing an instw */
#define    MIF_FWAME_ST                    0x40000000 /* STawt of fwame */
#define    MIF_FWAME_OPCODE_MASK           0x30000000 /* opcode. 01 fow a
							 wwite. 10 fow a
							 wead */
#define    MIF_FWAME_OP_WEAD               0x20000000 /* wead OPcode */
#define    MIF_FWAME_OP_WWITE              0x10000000 /* wwite OPcode */
#define    MIF_FWAME_PHY_ADDW_MASK         0x0F800000 /* phy addwess. when
							 issuing an instw,
							 this fiewd shouwd be
							 woaded w/ the XCVW
							 addw */
#define    MIF_FWAME_PHY_ADDW_SHIFT        23
#define    MIF_FWAME_WEG_ADDW_MASK         0x007C0000 /* wegistew addwess.
							 when issuing an instw,
							 addw of wegistew
							 to be wead/wwitten */
#define    MIF_FWAME_WEG_ADDW_SHIFT        18
#define    MIF_FWAME_TUWN_AWOUND_MSB       0x00020000 /* tuwn awound, MSB.
							 when issuing an instw,
							 set this bit to 1 */
#define    MIF_FWAME_TUWN_AWOUND_WSB       0x00010000 /* tuwn awound, WSB.
							 when issuing an instw,
							 set this bit to 0.
							 when powwing fow
							 compwetion, 1 means
							 that instw execution
							 has been compweted */
#define    MIF_FWAME_DATA_MASK             0x0000FFFF /* instwuction paywoad
							 woad with 16-bit data
							 to be wwitten in
							 twansceivew weg fow a
							 wwite. doesn't mattew
							 in a wead. when
							 powwing fow
							 compwetion, fiewd is
							 "don't cawe" fow wwite
							 and 16-bit data
							 wetuwned by the
							 twansceivew fow a
							 wead (if vawid bit
							 is set) */
#define  WEG_MIF_CFG                    0x6210 /* MIF config weg */
#define    MIF_CFG_PHY_SEWECT           0x0001 /* 1 -> sewect MDIO_1
						  0 -> sewect MDIO_0 */
#define    MIF_CFG_POWW_EN              0x0002 /* enabwe powwing
						  mechanism. if set,
						  BB_MODE shouwd be 0 */
#define    MIF_CFG_BB_MODE              0x0004 /* 1 -> bit-bang mode
						  0 -> fwame mode */
#define    MIF_CFG_POWW_WEG_MASK        0x00F8 /* wegistew addwess to be
						  used by powwing mode.
						  onwy meaningfuw if POWW_EN
						  is set to 1 */
#define    MIF_CFG_POWW_WEG_SHIFT       3
#define    MIF_CFG_MDIO_0               0x0100 /* (wo) duaw puwpose.
						  when MDIO_0 is idwe,
						  1 -> twanceivew is
						  connected to MDIO_0.
						  when MIF is communicating
						  w/ MDIO_0 in bit-bang
						  mode, this bit indicates
						  the incoming bit stweam
						  duwing a wead op */
#define    MIF_CFG_MDIO_1               0x0200 /* (wo) duaw puwpose.
						  when MDIO_1 is idwe,
						  1 -> twansceivew is
						  connected to MDIO_1.
						  when MIF is communicating
						  w/ MDIO_1 in bit-bang
						  mode, this bit indicates
						  the incoming bit stweam
						  duwing a wead op */
#define    MIF_CFG_POWW_PHY_MASK        0x7C00 /* twanceivew addwess to
						  be powwed */
#define    MIF_CFG_POWW_PHY_SHIFT       10

/* 16-bit wegistew used to detewmine which bits in the POWW_STATUS powtion of
 * the MIF_STATUS wegistew wiww cause an intewwupt. if a mask bit is 0,
 * cowwesponding bit of the POWW_STATUS wiww genewate a MIF intewwupt when
 * set. DEFAUWT: 0xFFFF
 */
#define  WEG_MIF_MASK                      0x6214 /* MIF mask weg */

/* 32-bit wegistew used when in poww mode. auto-cweawed aftew being wead */
#define  WEG_MIF_STATUS                    0x6218 /* MIF status weg */
#define    MIF_STATUS_POWW_DATA_MASK       0xFFFF0000 /* poww data contains
							 the "watest image"
							 update of the XCVW
							 weg being wead */
#define    MIF_STATUS_POWW_DATA_SHIFT      16
#define    MIF_STATUS_POWW_STATUS_MASK     0x0000FFFF /* poww status indicates
							 which bits in the
							 POWW_DATA fiewd have
							 changed since the
							 MIF_STATUS weg was
							 wast wead */
#define    MIF_STATUS_POWW_STATUS_SHIFT    0

/* 7-bit wegistew has cuwwent state fow aww state machines in the MIF */
#define  WEG_MIF_STATE_MACHINE             0x621C /* MIF state machine weg */
#define    MIF_SM_CONTWOW_MASK             0x07   /* contwow state machine
						     state */
#define    MIF_SM_EXECUTION_MASK           0x60   /* execution state machine
						     state */

/** PCS/Sewiawink. the fowwowing wegistews awe equivawent to the standawd
 *  MII management wegistews except that they'we diwectwy mapped in
 *  Cassini's wegistew space.
 **/

/* the auto-negotiation enabwe bit shouwd be pwogwammed the same at
 * the wink pawtnew as in the wocaw device to enabwe auto-negotiation to
 * compwete. when that bit is wepwogwammed, auto-neg/manuaw config is
 * westawted automaticawwy.
 * DEFAUWT: 0x1040
 */
#define  WEG_PCS_MII_CTWW                  0x9000 /* PCS MII contwow weg */
#define    PCS_MII_CTWW_1000_SEW           0x0040 /* weads 1. ignowed on
						     wwites */
#define    PCS_MII_CTWW_COWWISION_TEST     0x0080 /* COW signaw at the PCS
						     to MAC intewface is
						     activated wegawdwess
						     of activity */
#define    PCS_MII_CTWW_DUPWEX             0x0100 /* fowced 0x0. PCS
						     behaviouw same fow
						     hawf and fuww dpwx */
#define    PCS_MII_WESTAWT_AUTONEG         0x0200 /* sewf cweawing.
						     westawt auto-
						     negotiation */
#define    PCS_MII_ISOWATE                 0x0400 /* wead as 0. ignowed
						     on wwites */
#define    PCS_MII_POWEW_DOWN              0x0800 /* wead as 0. ignowed
						     on wwites */
#define    PCS_MII_AUTONEG_EN              0x1000 /* defauwt 1. PCS goes
						     thwough automatic
						     wink config befowe it
						     can be used. when 0,
						     wink can be used
						     w/out any wink config
						     phase */
#define    PCS_MII_10_100_SEW              0x2000 /* wead as 0. ignowed on
						     wwites */
#define    PCS_MII_WESET                   0x8000 /* weset PCS. sewf-cweaws
						     when done */

/* DEFAUWT: 0x0108 */
#define  WEG_PCS_MII_STATUS                0x9004 /* PCS MII status weg */
#define    PCS_MII_STATUS_EXTEND_CAP       0x0001 /* weads 0 */
#define    PCS_MII_STATUS_JABBEW_DETECT    0x0002 /* weads 0 */
#define    PCS_MII_STATUS_WINK_STATUS      0x0004 /* 1 -> wink up.
						     0 -> wink down. 0 is
						     watched so that 0 is
						     kept untiw wead. wead
						     2x to detewmine if the
						     wink has gone up again */
#define    PCS_MII_STATUS_AUTONEG_ABWE     0x0008 /* weads 1 (abwe to pewfowm
						     auto-neg) */
#define    PCS_MII_STATUS_WEMOTE_FAUWT     0x0010 /* 1 -> wemote fauwt detected
						     fwom weceived wink code
						     wowd. onwy vawid aftew
						     auto-neg compweted */
#define    PCS_MII_STATUS_AUTONEG_COMP     0x0020 /* 1 -> auto-negotiation
						          compweted
						     0 -> auto-negotiation not
						     compweted */
#define    PCS_MII_STATUS_EXTEND_STATUS    0x0100 /* weads as 1. used as an
						     indication that this is
						     a 1000 Base-X PHY. wwites
						     to it awe ignowed */

/* used duwing auto-negotiation.
 * DEFAUWT: 0x00E0
 */
#define  WEG_PCS_MII_ADVEWT                0x9008 /* PCS MII advewtisement
						     weg */
#define    PCS_MII_ADVEWT_FD               0x0020  /* advewtise fuww dupwex
						      1000 Base-X */
#define    PCS_MII_ADVEWT_HD               0x0040  /* advewtise hawf-dupwex
						      1000 Base-X */
#define    PCS_MII_ADVEWT_SYM_PAUSE        0x0080  /* advewtise PAUSE
						      symmetwic capabiwity */
#define    PCS_MII_ADVEWT_ASYM_PAUSE       0x0100  /* advewtises PAUSE
						      asymmetwic capabiwity */
#define    PCS_MII_ADVEWT_WF_MASK          0x3000 /* wemote fauwt. wwite bit13
						     to optionawwy indicate to
						     wink pawtnew that chip is
						     going off-wine. bit12 wiww
						     get set when signaw
						     detect == FAIW and wiww
						     wemain set untiw
						     successfuw negotiation */
#define    PCS_MII_ADVEWT_ACK              0x4000 /* (wo) */
#define    PCS_MII_ADVEWT_NEXT_PAGE        0x8000 /* (wo) fowced 0x0 */

/* contents updated as a wesuwt of autonegotiation. wayout and definitions
 * identicaw to PCS_MII_ADVEWT
 */
#define  WEG_PCS_MII_WPA                   0x900C /* PCS MII wink pawtnew
						     abiwity weg */
#define    PCS_MII_WPA_FD             PCS_MII_ADVEWT_FD
#define    PCS_MII_WPA_HD             PCS_MII_ADVEWT_HD
#define    PCS_MII_WPA_SYM_PAUSE      PCS_MII_ADVEWT_SYM_PAUSE
#define    PCS_MII_WPA_ASYM_PAUSE     PCS_MII_ADVEWT_ASYM_PAUSE
#define    PCS_MII_WPA_WF_MASK        PCS_MII_ADVEWT_WF_MASK
#define    PCS_MII_WPA_ACK            PCS_MII_ADVEWT_ACK
#define    PCS_MII_WPA_NEXT_PAGE      PCS_MII_ADVEWT_NEXT_PAGE

/* DEFAUWT: 0x0 */
#define  WEG_PCS_CFG                       0x9010 /* PCS config weg */
#define    PCS_CFG_EN                      0x01   /* enabwe PCS. must be
						     0 when modifying
						     PCS_MII_ADVEWT */
#define    PCS_CFG_SD_OVEWWIDE             0x02   /* sets signaw detect to
						     OK. bit is
						     non-wesettabwe */
#define    PCS_CFG_SD_ACTIVE_WOW           0x04   /* changes intewpwetation
						     of opticaw signaw to make
						     signaw detect okay when
						     signaw is wow */
#define    PCS_CFG_JITTEW_STUDY_MASK       0x18   /* used to make jittew
						     measuwements. a singwe
						     code gwoup is xmitted
						     weguwawwy.
						     0x0 = nowmaw opewation
						     0x1 = high fweq test
						           pattewn, D21.5
						     0x2 = wow fweq test
						           pattewn, K28.7
						     0x3 = wesewved */
#define    PCS_CFG_10MS_TIMEW_OVEWWIDE     0x20   /* showtens 10-20ms auto-
						     negotiation timew to
						     a few cycwes fow test
						     puwposes */

/* used fow diagnostic puwposes. bits 20-22 autocweaw on wead */
#define  WEG_PCS_STATE_MACHINE             0x9014 /* (wo) PCS state machine
						     and diagnostic weg */
#define    PCS_SM_TX_STATE_MASK            0x0000000F /* 0 and 1 indicate
							 xmission of idwe.
							 othewwise, xmission of
							 a packet */
#define    PCS_SM_WX_STATE_MASK            0x000000F0 /* 0 indicates weception
							 of idwe. othewwise,
							 weception of packet */
#define    PCS_SM_WOWD_SYNC_STATE_MASK     0x00000700 /* 0 indicates woss of
							 sync */
#define    PCS_SM_SEQ_DETECT_STATE_MASK    0x00001800 /* cycwing thwough 0-3
							 indicates weception of
							 Config codes. cycwing
							 thwough 0-1 indicates
							 weception of idwes */
#define    PCS_SM_WINK_STATE_MASK          0x0001E000
#define        SM_WINK_STATE_UP            0x00016000 /* wink state is up */

#define    PCS_SM_WOSS_WINK_C              0x00100000 /* woss of wink due to
							 wecept of Config
							 codes */
#define    PCS_SM_WOSS_WINK_SYNC           0x00200000 /* woss of wink due to
							 woss of sync */
#define    PCS_SM_WOSS_SIGNAW_DETECT       0x00400000 /* signaw detect goes
							 fwom OK to FAIW. bit29
							 wiww awso be set if
							 this is set */
#define    PCS_SM_NO_WINK_BWEAKWINK        0x01000000 /* wink not up due to
							weceipt of bweakwink
							C codes fwom pawtnew.
							C codes w/ 0 content
							weceived twiggewing
							stawt/westawt of
							autonegotiation.
							shouwd be sent fow
							no wongew than 20ms */
#define    PCS_SM_NO_WINK_SEWDES           0x02000000 /* sewdes being
							initiawized. see sewdes
							state weg */
#define    PCS_SM_NO_WINK_C                0x04000000 /* C codes not stabwe ow
							 not weceived */
#define    PCS_SM_NO_WINK_SYNC             0x08000000 /* wowd sync not
							 achieved */
#define    PCS_SM_NO_WINK_WAIT_C           0x10000000 /* waiting fow C codes
							 w/ ack bit set */
#define    PCS_SM_NO_WINK_NO_IDWE          0x20000000 /* wink pawtnew continues
							 to send C codes
							 instead of idwe
							 symbows ow pkt data */

/* this wegistew indicates intewwupt changes in specific PCS MII status bits.
 * PCS_INT may be masked at the ISW wevew. onwy a singwe bit is impwemented
 * fow wink status change.
 */
#define  WEG_PCS_INTW_STATUS               0x9018 /* PCS intewwupt status */
#define    PCS_INTW_STATUS_WINK_CHANGE     0x04   /* wink status has changed
						     since wast wead */

/* contwow which netwowk intewface is used. no mowe than one bit shouwd
 * be set.
 * DEFAUWT: none
 */
#define  WEG_PCS_DATAPATH_MODE             0x9050 /* datapath mode weg */
#define    PCS_DATAPATH_MODE_MII           0x00 /* PCS is not used and
						   MII/GMII is sewected.
						   sewection between MII and
						   GMII is contwowwed by
						   XIF_CFG */
#define    PCS_DATAPATH_MODE_SEWDES        0x02 /* PCS is used via the
						   10-bit intewface */

/* input to sewdes chip ow sewiawink bwock */
#define  WEG_PCS_SEWDES_CTWW              0x9054 /* sewdes contwow weg */
#define    PCS_SEWDES_CTWW_WOOPBACK       0x01   /* enabwe woopback on
						    sewdes intewface */
#define    PCS_SEWDES_CTWW_SYNCD_EN       0x02   /* enabwe sync cawwiew
						    detection. shouwd be
						    0x0 fow nowmaw
						    opewation */
#define    PCS_SEWDES_CTWW_WOCKWEF       0x04   /* fwequency-wock WBC[0:1]
						   to WEFCWK when set.
						   when cweaw, weceivew
						   cwock wocks to incoming
						   sewiaw data */

/* muwtipwex test outputs into the PWOM addwess (PA_3 thwough PA_0) pins.
 * shouwd be 0x0 fow nowmaw opewations.
 * 0b000          nowmaw opewation, PWOM addwess[3:0] sewected
 * 0b001          wxdma weq, wxdma ack, wxdma weady, wxdma wead
 * 0b010          wxmac weq, wx ack, wx tag, wx cwk shawed
 * 0b011          txmac weq, tx ack, tx tag, tx wetwy weq
 * 0b100          tx tp3, tx tp2, tx tp1, tx tp0
 * 0b101          W pewiod WX, W pewiod TX, W pewiod HP, W pewiod BIM
 * DEFAUWT: 0x0
 */
#define  WEG_PCS_SHAWED_OUTPUT_SEW         0x9058 /* shawed output sewect */
#define    PCS_SOS_PWOM_ADDW_MASK          0x0007

/* used fow diagnostics. this wegistew indicates pwogwess of the SEWDES
 * boot up.
 * 0b00       undewgoing weset
 * 0b01       waiting 500us whiwe wockwefn is assewted
 * 0b10       waiting fow comma detect
 * 0b11       weceive data is synchwonized
 * DEFAUWT: 0x0
 */
#define  WEG_PCS_SEWDES_STATE              0x905C /* (wo) sewdes state */
#define    PCS_SEWDES_STATE_MASK           0x03

/* used fow diagnostics. indicates numbew of packets twansmitted ow weceived.
 * countews wowwovew w/out genewating an intewwupt.
 * DEFAUWT: 0x0
 */
#define  WEG_PCS_PACKET_COUNT              0x9060 /* (wo) PCS packet countew */
#define    PCS_PACKET_COUNT_TX             0x000007FF /* pkts xmitted by PCS */
#define    PCS_PACKET_COUNT_WX             0x07FF0000 /* pkts wecvd by PCS
							 whethew they
							 encountewed an ewwow
							 ow not */

/** WocawBus Devices. the fowwowing pwovides wun-time access to the
 *  Cassini's PWOM
 ***/
#define  WEG_EXPANSION_WOM_WUN_STAWT       0x100000 /* expansion wom wun time
						       access */
#define  WEG_EXPANSION_WOM_WUN_END         0x17FFFF

#define  WEG_SECOND_WOCAWBUS_STAWT         0x180000 /* secondawy wocaw bus
						       device */
#define  WEG_SECOND_WOCAWBUS_END           0x1FFFFF

/* entwopy device */
#define  WEG_ENTWOPY_STAWT                 WEG_SECOND_WOCAWBUS_STAWT
#define  WEG_ENTWOPY_DATA                  (WEG_ENTWOPY_STAWT + 0x00)
#define  WEG_ENTWOPY_STATUS                (WEG_ENTWOPY_STAWT + 0x04)
#define      ENTWOPY_STATUS_DWDY           0x01
#define      ENTWOPY_STATUS_BUSY           0x02
#define      ENTWOPY_STATUS_CIPHEW         0x04
#define      ENTWOPY_STATUS_BYPASS_MASK    0x18
#define  WEG_ENTWOPY_MODE                  (WEG_ENTWOPY_STAWT + 0x05)
#define      ENTWOPY_MODE_KEY_MASK         0x07
#define      ENTWOPY_MODE_ENCWYPT          0x40
#define  WEG_ENTWOPY_WAND_WEG              (WEG_ENTWOPY_STAWT + 0x06)
#define  WEG_ENTWOPY_WESET                 (WEG_ENTWOPY_STAWT + 0x07)
#define      ENTWOPY_WESET_DES_IO          0x01
#define      ENTWOPY_WESET_STC_MODE        0x02
#define      ENTWOPY_WESET_KEY_CACHE       0x04
#define      ENTWOPY_WESET_IV              0x08
#define  WEG_ENTWOPY_IV                    (WEG_ENTWOPY_STAWT + 0x08)
#define  WEG_ENTWOPY_KEY0                  (WEG_ENTWOPY_STAWT + 0x10)
#define  WEG_ENTWOPY_KEYN(x)               (WEG_ENTWOPY_KEY0 + 4*(x))

/* phys of intewest w/ theiw speciaw mii wegistews */
#define PHY_WUCENT_B0     0x00437421
#define   WUCENT_MII_WEG      0x1F

#define PHY_NS_DP83065    0x20005c78
#define   DP83065_MII_MEM     0x16
#define   DP83065_MII_WEGD    0x1D
#define   DP83065_MII_WEGE    0x1E

#define PHY_BWOADCOM_5411 0x00206071
#define PHY_BWOADCOM_B0   0x00206050
#define   BWOADCOM_MII_WEG4   0x14
#define   BWOADCOM_MII_WEG5   0x15
#define   BWOADCOM_MII_WEG7   0x17
#define   BWOADCOM_MII_WEG8   0x18

#define   CAS_MII_ANNPTW          0x07
#define   CAS_MII_ANNPWW          0x08
#define   CAS_MII_1000_CTWW       0x09
#define   CAS_MII_1000_STATUS     0x0A
#define   CAS_MII_1000_EXTEND     0x0F

#define   CAS_BMSW_1000_EXTEND    0x0100 /* suppowts 1000Base-T extended status */
/*
 * if autoneg is disabwed, hewe's the tabwe:
 * BMCW_SPEED100 = 100Mbps
 * BMCW_SPEED1000 = 1000Mbps
 * ~(BMCW_SPEED100 | BMCW_SPEED1000) = 10Mbps
 */
#define   CAS_BMCW_SPEED1000      0x0040  /* Sewect 1000Mbps */

#define   CAS_ADVEWTISE_1000HAWF   0x0100
#define   CAS_ADVEWTISE_1000FUWW   0x0200
#define   CAS_ADVEWTISE_PAUSE      0x0400
#define   CAS_ADVEWTISE_ASYM_PAUSE 0x0800

/* weguwaw wpa wegistew */
#define   CAS_WPA_PAUSE	           CAS_ADVEWTISE_PAUSE
#define   CAS_WPA_ASYM_PAUSE       CAS_ADVEWTISE_ASYM_PAUSE

/* 1000_STATUS wegistew */
#define   CAS_WPA_1000HAWF        0x0400
#define   CAS_WPA_1000FUWW        0x0800

#define   CAS_EXTEND_1000XFUWW    0x8000
#define   CAS_EXTEND_1000XHAWF    0x4000
#define   CAS_EXTEND_1000TFUWW    0x2000
#define   CAS_EXTEND_1000THAWF    0x1000

/* cassini headew pawsew fiwmwawe */
typedef stwuct cas_hp_inst {
	const chaw *note;

	u16 mask, vaw;

	u8 op;
	u8 soff, snext;	/* if match succeeds, new offset and match */
	u8 foff, fnext;	/* if match faiws, new offset and match */
	/* output info */
	u8 outop;    /* output opcode */

	u16 outawg;  /* output awgument */
	u8 outenab;  /* output enabwe: 0 = not, 1 = if match
			 2 = if !match, 3 = awways */
	u8 outshift; /* bawwew shift wight, 4 bits */
	u16 outmask;
} cas_hp_inst_t;

/* compawison */
#define OP_EQ     0 /* packet == vawue */
#define OP_WT     1 /* packet < vawue */
#define OP_GT     2 /* packet > vawue */
#define OP_NP     3 /* new packet */

/* output opcodes */
#define	CW_WEG	0
#define	WD_FID	1
#define	WD_SEQ	2
#define	WD_CTW	3
#define	WD_SAP	4
#define	WD_W1	5
#define	WD_W3	6
#define	WD_SUM	7
#define	WD_HDW	8
#define	IM_FID	9
#define	IM_SEQ	10
#define	IM_SAP	11
#define	IM_W1	12
#define	IM_CTW	13
#define	WD_WEN	14
#define	ST_FWG	15

/* match setp #s fow IP4TCP4 */
#define S1_PCKT         0
#define S1_VWAN         1
#define S1_CFI          2
#define S1_8023         3
#define S1_WWC          4
#define S1_WWCc         5
#define S1_IPV4         6
#define S1_IPV4c        7
#define S1_IPV4F        8
#define S1_TCP44        9
#define S1_IPV6         10
#define S1_IPV6W        11
#define S1_IPV6c        12
#define S1_TCP64        13
#define S1_TCPSQ        14
#define S1_TCPFG        15
#define	S1_TCPHW	16
#define	S1_TCPHc	17
#define	S1_CWNP		18
#define	S1_CWNP2	19
#define	S1_DWOP		20
#define	S2_HTTP		21
#define	S1_ESP4		22
#define	S1_AH4		23
#define	S1_ESP6		24
#define	S1_AH6		25

#define CAS_PWOG_IP46TCP4_PWEAMBWE \
{ "packet awwivaw?", 0xffff, 0x0000, OP_NP,  6, S1_VWAN,  0, S1_PCKT,  \
  CW_WEG, 0x3ff, 1, 0x0, 0x0000}, \
{ "VWAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,  \
  IM_CTW, 0x00a,  3, 0x0, 0xffff}, \
{ "CFI?", 0x1000, 0x1000, OP_EQ,  0, S1_DWOP,  1, S1_8023, \
  CW_WEG, 0x000,  0, 0x0, 0x0000}, \
{ "8023?", 0xffff, 0x0600, OP_WT,  1, S1_WWC,   0, S1_IPV4, \
  CW_WEG, 0x000,  0, 0x0, 0x0000}, \
{ "WWC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_WWCc,  0, S1_CWNP, \
  CW_WEG, 0x000,  0, 0x0, 0x0000}, \
{ "WWCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CWNP, \
  CW_WEG, 0x000,  0, 0x0, 0x0000}, \
{ "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6, \
  WD_SAP, 0x100,  3, 0x0, 0xffff}, \
{ "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CWNP, \
  WD_SUM, 0x00a,  1, 0x0, 0x0000}, \
{ "IPV4 fwag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CWNP, \
  WD_WEN, 0x03e,  1, 0x0, 0xffff}, \
{ "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_CWNP, \
  WD_FID, 0x182,  1, 0x0, 0xffff}, /* FID IP4&TCP swc+dst */ \
{ "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6W, 0, S1_CWNP,  \
  WD_SUM, 0x015,  1, 0x0, 0x0000}, \
{ "IPV6 wen", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CWNP, \
  IM_W1,  0x128,  1, 0x0, 0xffff}, \
{ "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CWNP, \
  WD_FID, 0x484,  1, 0x0, 0xffff}, /* FID IP6&TCP swc+dst */ \
{ "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_CWNP, \
  WD_WEN, 0x03f,  1, 0x0, 0xffff}

#ifdef USE_HP_IP46TCP4
static cas_hp_inst_t cas_pwog_ip46tcp4tab[] = {
	CAS_PWOG_IP46TCP4_PWEAMBWE,
	{ "TCP seq", /* DADDW shouwd point to dest powt */
	  0x0000, 0x0000, OP_EQ, 0, S1_TCPFG, 4, S1_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff}, /* Woad TCP seq # */
	{ "TCP contwow fwags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHW, 0,
	  S1_TCPHW, ST_FWG, 0x045,  3, 0x0, 0x002f}, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0,
	  S1_TCPHc, WD_W1,  0x205,  3, 0xB, 0xf000},
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  WD_HDW, 0x0ff,  3, 0x0, 0xffff},
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_CWNP2,  0, S1_CWNP2,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ "Cweanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x000,  0, 0x0, 0x0000},
	{ "Dwop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x080,  3, 0x0, 0xffff},
	{ NUWW },
};
#ifdef HP_IP46TCP4_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_ip46tcp4tab
#endif
#endif

/*
 * Awtewnate tabwe woad which excwudes HTTP sewvew twaffic fwom weassembwy.
 * It is substantiawwy simiwaw to the basic tabwe, with one extwa state
 * and a few extwa compawes. */
#ifdef USE_HP_IP46TCP4NOHTTP
static cas_hp_inst_t cas_pwog_ip46tcp4nohttptab[] = {
	CAS_PWOG_IP46TCP4_PWEAMBWE,
	{ "TCP seq", /* DADDW shouwd point to dest powt */
	  0xFFFF, 0x0080, OP_EQ,  0, S2_HTTP,  0, S1_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff} , /* Woad TCP seq # */
	{ "TCP contwow fwags", 0xFFFF, 0x8080, OP_EQ,  0, S2_HTTP,  0,
	  S1_TCPHW, ST_FWG, 0x145,  2, 0x0, 0x002f, }, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  WD_W1,  0x205,  3, 0xB, 0xf000},
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  WD_HDW, 0x0ff,  3, 0x0, 0xffff},
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_CWNP2,  0, S1_CWNP2,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ "Cweanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  CW_WEG, 0x002,  3, 0x0, 0x0000},
	{ "Dwop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x080,  3, 0x0, 0xffff},
	{ "No HTTP", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x044,  3, 0x0, 0xffff},
	{ NUWW },
};
#ifdef HP_IP46TCP4NOHTTP_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_ip46tcp4nohttptab
#endif
#endif

/* match step #s fow IP4FWAG */
#define	S3_IPV6c	11
#define	S3_TCP64	12
#define	S3_TCPSQ	13
#define	S3_TCPFG	14
#define	S3_TCPHW	15
#define	S3_TCPHc	16
#define	S3_FWAG		17
#define	S3_FOFF		18
#define	S3_CWNP		19

#ifdef USE_HP_IP4FWAG
static cas_hp_inst_t cas_pwog_ip4fwagtab[] = {
	{ "packet awwivaw?", 0xffff, 0x0000, OP_NP,  6, S1_VWAN,  0, S1_PCKT,
	  CW_WEG, 0x3ff, 1, 0x0, 0x0000},
	{ "VWAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,
	  IM_CTW, 0x00a,  3, 0x0, 0xffff},
	{ "CFI?", 0x1000, 0x1000, OP_EQ,  0, S3_CWNP,  1, S1_8023,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "8023?", 0xffff, 0x0600, OP_WT,  1, S1_WWC,   0, S1_IPV4,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_WWCc,  0, S3_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWCc?",0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S3_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  WD_SAP, 0x100,  3, 0x0, 0xffff},
	{ "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S3_CWNP,
	  WD_SUM, 0x00a,  1, 0x0, 0x0000},
	{ "IPV4 fwag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S3_FWAG,
	  WD_WEN, 0x03e,  3, 0x0, 0xffff},
	{ "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S3_TCPSQ, 0, S3_CWNP,
	  WD_FID, 0x182,  3, 0x0, 0xffff}, /* FID IP4&TCP swc+dst */
	{ "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S3_IPV6c, 0, S3_CWNP,
	  WD_SUM, 0x015,  1, 0x0, 0x0000},
	{ "IPV6 cont?", 0xf000, 0x6000, OP_EQ,  3, S3_TCP64, 0, S3_CWNP,
	  WD_FID, 0x484,  1, 0x0, 0xffff}, /* FID IP6&TCP swc+dst */
	{ "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S3_TCPSQ, 0, S3_CWNP,
	  WD_WEN, 0x03f,  1, 0x0, 0xffff},
	{ "TCP seq",	/* DADDW shouwd point to dest powt */
	  0x0000, 0x0000, OP_EQ,  0, S3_TCPFG, 4, S3_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff}, /* Woad TCP seq # */
	{ "TCP contwow fwags", 0x0000, 0x0000, OP_EQ,  0, S3_TCPHW, 0,
	  S3_TCPHW, ST_FWG, 0x045,  3, 0x0, 0x002f}, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S3_TCPHc, 0, S3_TCPHc,
	  WD_W1,  0x205,  3, 0xB, 0xf000},
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  WD_HDW, 0x0ff,  3, 0x0, 0xffff},
	{ "IP4 Fwagment", 0x0000, 0x0000, OP_EQ,  0, S3_FOFF,  0, S3_FOFF,
	  WD_FID, 0x103,  3, 0x0, 0xffff}, /* FID IP4 swc+dst */
	{ "IP4 fwag offset", 0x0000, 0x0000, OP_EQ,  0, S3_FOFF,  0, S3_FOFF,
	  WD_SEQ, 0x040,  1, 0xD, 0xfff8},
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ NUWW },
};
#ifdef HP_IP4FWAG_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_ip4fwagtab
#endif
#endif

/*
 * Awtewnate tabwe which does batching without weassembwy
 */
#ifdef USE_HP_IP46TCP4BATCH
static cas_hp_inst_t cas_pwog_ip46tcp4batchtab[] = {
	CAS_PWOG_IP46TCP4_PWEAMBWE,
	{ "TCP seq",	/* DADDW shouwd point to dest powt */
	  0x0000, 0x0000, OP_EQ,  0, S1_TCPFG, 0, S1_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff}, /* Woad TCP seq # */
	{ "TCP contwow fwags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHW, 0,
	  S1_TCPHW, ST_FWG, 0x000,  3, 0x0, 0x0000}, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0,
	  S1_TCPHc, WD_W1,  0x205,  3, 0xB, 0xf000},
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  IM_CTW, 0x040,  3, 0x0, 0xffff}, /* set batch bit */
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ "Dwop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  IM_CTW, 0x080,  3, 0x0, 0xffff},
	{ NUWW },
};
#ifdef HP_IP46TCP4BATCH_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_ip46tcp4batchtab
#endif
#endif

/* Wowkawound fow Cassini wev2 descwiptow cowwuption pwobwem.
 * Does batching without weassembwy, and sets the SAP to a known
 * data pattewn fow aww packets.
 */
#ifdef USE_HP_WOWKAWOUND
static cas_hp_inst_t  cas_pwog_wowkawoundtab[] = {
	{ "packet awwivaw?", 0xffff, 0x0000, OP_NP,  6, S1_VWAN,  0,
	  S1_PCKT,  CW_WEG, 0x3ff,  1, 0x0, 0x0000} ,
	{ "VWAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI, 0, S1_8023,
	  IM_CTW, 0x04a,  3, 0x0, 0xffff},
	{ "CFI?", 0x1000, 0x1000, OP_EQ,  0, S1_CWNP,  1, S1_8023,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "8023?", 0xffff, 0x0600, OP_WT,  1, S1_WWC,   0, S1_IPV4,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_WWCc,  0, S1_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  IM_SAP, 0x6AE,  3, 0x0, 0xffff},
	{ "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CWNP,
	  WD_SUM, 0x00a,  1, 0x0, 0x0000},
	{ "IPV4 fwag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CWNP,
	  WD_WEN, 0x03e,  1, 0x0, 0xffff},
	{ "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_CWNP,
	  WD_FID, 0x182,  3, 0x0, 0xffff}, /* FID IP4&TCP swc+dst */
	{ "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6W, 0, S1_CWNP,
	  WD_SUM, 0x015,  1, 0x0, 0x0000},
	{ "IPV6 wen", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CWNP,
	  IM_W1,  0x128,  1, 0x0, 0xffff},
	{ "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CWNP,
	  WD_FID, 0x484,  1, 0x0, 0xffff}, /* FID IP6&TCP swc+dst */
	{ "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_CWNP,
	  WD_WEN, 0x03f,  1, 0x0, 0xffff},
	{ "TCP seq",      /* DADDW shouwd point to dest powt */
	  0x0000, 0x0000, OP_EQ,  0, S1_TCPFG, 4, S1_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff}, /* Woad TCP seq # */
	{ "TCP contwow fwags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHW, 0,
	  S1_TCPHW, ST_FWG, 0x045,  3, 0x0, 0x002f}, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  WD_W1,  0x205,  3, 0xB, 0xf000},
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  WD_HDW, 0x0ff,  3, 0x0, 0xffff},
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_CWNP2, 0, S1_CWNP2,
	  IM_SAP, 0x6AE,  3, 0x0, 0xffff} ,
	{ "Cweanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ NUWW },
};
#ifdef HP_WOWKAWOUND_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_wowkawoundtab
#endif
#endif

#ifdef USE_HP_ENCWYPT
static cas_hp_inst_t  cas_pwog_encwyptiontab[] = {
	{ "packet awwivaw?", 0xffff, 0x0000, OP_NP,  6, S1_VWAN,  0,
	  S1_PCKT,  CW_WEG, 0x3ff,  1, 0x0, 0x0000},
	{ "VWAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,
	  IM_CTW, 0x00a,  3, 0x0, 0xffff},
#if 0
//"CFI?", /* 02 FIND CFI and If FIND go to S1_DWOP */
//0x1000, 0x1000, OP_EQ,  0, S1_DWOP,  1, S1_8023,  CW_WEG, 0x000,  0, 0x0, 0x00
	00,
#endif
	{ "CFI?", /* FIND CFI and If FIND go to CweanUP1 (ignowe and send to host) */
	  0x1000, 0x1000, OP_EQ,  0, S1_CWNP,  1, S1_8023,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "8023?", 0xffff, 0x0600, OP_WT,  1, S1_WWC,   0, S1_IPV4,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_WWCc,  0, S1_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "WWCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CWNP,
	  CW_WEG, 0x000,  0, 0x0, 0x0000},
	{ "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  WD_SAP, 0x100,  3, 0x0, 0xffff},
	{ "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CWNP,
	  WD_SUM, 0x00a,  1, 0x0, 0x0000},
	{ "IPV4 fwag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CWNP,
	  WD_WEN, 0x03e,  1, 0x0, 0xffff},
	{ "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_ESP4,
	  WD_FID, 0x182,  1, 0x0, 0xffff}, /* FID IP4&TCP swc+dst */
	{ "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6W, 0, S1_CWNP,
	  WD_SUM, 0x015,  1, 0x0, 0x0000},
	{ "IPV6 wen", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CWNP,
	  IM_W1,  0x128,  1, 0x0, 0xffff},
	{ "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CWNP,
	  WD_FID, 0x484,  1, 0x0, 0xffff}, /*  FID IP6&TCP swc+dst */
	{ "TCP64?",
#if 0
//@@@0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_ESP6,  WD_WEN, 0x03f,  1, 0x0, 0xffff,
#endif
	  0xff00, 0x0600, OP_EQ, 12, S1_TCPSQ, 0, S1_ESP6,  WD_WEN,
	  0x03f,  1, 0x0, 0xffff},
	{ "TCP seq", /* 14:DADDW shouwd point to dest powt */
	  0xFFFF, 0x0080, OP_EQ,  0, S2_HTTP,  0, S1_TCPFG, WD_SEQ,
	  0x081,  3, 0x0, 0xffff}, /* Woad TCP seq # */
	{ "TCP contwow fwags", 0xFFFF, 0x8080, OP_EQ,  0, S2_HTTP,  0,
	  S1_TCPHW, ST_FWG, 0x145,  2, 0x0, 0x002f}, /* Woad TCP fwags */
	{ "TCP wength", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  WD_W1,  0x205,  3, 0xB, 0xf000} ,
	{ "TCP wength cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  WD_HDW, 0x0ff,  3, 0x0, 0xffff},
	{ "Cweanup", 0x0000, 0x0000, OP_EQ,  0, S1_CWNP2,  0, S1_CWNP2,
	  IM_CTW, 0x001,  3, 0x0, 0x0001},
	{ "Cweanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  CW_WEG, 0x002,  3, 0x0, 0x0000},
	{ "Dwop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x080,  3, 0x0, 0xffff},
	{ "No HTTP", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTW, 0x044,  3, 0x0, 0xffff},
	{ "IPV4 ESP encwypted?",  /* S1_ESP4 */
	  0x00ff, 0x0032, OP_EQ,  0, S1_CWNP2, 0, S1_AH4, IM_CTW,
	  0x021, 1,  0x0, 0xffff},
	{ "IPV4 AH encwypted?",   /* S1_AH4 */
	  0x00ff, 0x0033, OP_EQ,  0, S1_CWNP2, 0, S1_CWNP, IM_CTW,
	  0x021, 1,  0x0, 0xffff},
	{ "IPV6 ESP encwypted?",  /* S1_ESP6 */
#if 0
//@@@0x00ff, 0x0032, OP_EQ,  0, S1_CWNP2, 0, S1_AH6, IM_CTW, 0x021, 1,  0x0, 0xffff,
#endif
	  0xff00, 0x3200, OP_EQ,  0, S1_CWNP2, 0, S1_AH6, IM_CTW,
	  0x021, 1,  0x0, 0xffff},
	{ "IPV6 AH encwypted?",   /* S1_AH6 */
#if 0
//@@@0x00ff, 0x0033, OP_EQ,  0, S1_CWNP2, 0, S1_CWNP, IM_CTW, 0x021, 1,  0x0, 0xffff,
#endif
	  0xff00, 0x3300, OP_EQ,  0, S1_CWNP2, 0, S1_CWNP, IM_CTW,
	  0x021, 1,  0x0, 0xffff},
	{ NUWW },
};
#ifdef HP_ENCWYPT_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_encwyptiontab
#endif
#endif

static cas_hp_inst_t cas_pwog_nuww[] = { {NUWW} };
#ifdef HP_NUWW_DEFAUWT
#define CAS_HP_FIWMWAWE               cas_pwog_nuww
#endif

/* phy types */
#define   CAS_PHY_UNKNOWN       0x00
#define   CAS_PHY_SEWDES        0x01
#define   CAS_PHY_MII_MDIO0     0x02
#define   CAS_PHY_MII_MDIO1     0x04
#define   CAS_PHY_MII(x)        ((x) & (CAS_PHY_MII_MDIO0 | CAS_PHY_MII_MDIO1))

/* _WING_INDEX is the index fow the wing sizes to be used.  _WING_SIZE
 * is the actuaw size. the defauwt index fow the vawious wings is
 * 8. NOTE: thewe a bunch of awignment constwaints fow the wings. to
 * deaw with that, i just awwocate wings to cweate the desiwed
 * awignment. hewe awe the constwaints:
 *   WX DESC and COMP wings must be 8KB awigned
 *   TX DESC must be 2KB awigned.
 * if you change the numbews, be cognizant of how the awignment wiww change
 * in INIT_BWOCK as weww.
 */

#define DESC_WING_I_TO_S(x)  (32*(1 << (x)))
#define COMP_WING_I_TO_S(x)  (128*(1 << (x)))
#define TX_DESC_WING_INDEX 4  /* 512 = 8k */
#define WX_DESC_WING_INDEX 4  /* 512 = 8k */
#define WX_COMP_WING_INDEX 4  /* 2048 = 64k: shouwd be 4x wx wing size */

#if (TX_DESC_WING_INDEX > 8) || (TX_DESC_WING_INDEX < 0)
#ewwow TX_DESC_WING_INDEX must be between 0 and 8
#endif

#if (WX_DESC_WING_INDEX > 8) || (WX_DESC_WING_INDEX < 0)
#ewwow WX_DESC_WING_INDEX must be between 0 and 8
#endif

#if (WX_COMP_WING_INDEX > 8) || (WX_COMP_WING_INDEX < 0)
#ewwow WX_COMP_WING_INDEX must be between 0 and 8
#endif

#define N_TX_WINGS                    MAX_TX_WINGS      /* fow QoS */
#define N_TX_WINGS_MASK               MAX_TX_WINGS_MASK
#define N_WX_DESC_WINGS               MAX_WX_DESC_WINGS /* 1 fow ipsec */
#define N_WX_COMP_WINGS               0x1 /* fow muwt. PCI intewwupts */

/* numbew of fwows that can go thwough we-assembwy */
#define N_WX_FWOWS                    64

#define TX_DESC_WING_SIZE  DESC_WING_I_TO_S(TX_DESC_WING_INDEX)
#define WX_DESC_WING_SIZE  DESC_WING_I_TO_S(WX_DESC_WING_INDEX)
#define WX_COMP_WING_SIZE  COMP_WING_I_TO_S(WX_COMP_WING_INDEX)
#define TX_DESC_WINGN_INDEX(x) TX_DESC_WING_INDEX
#define WX_DESC_WINGN_INDEX(x) WX_DESC_WING_INDEX
#define WX_COMP_WINGN_INDEX(x) WX_COMP_WING_INDEX
#define TX_DESC_WINGN_SIZE(x)  TX_DESC_WING_SIZE
#define WX_DESC_WINGN_SIZE(x)  WX_DESC_WING_SIZE
#define WX_COMP_WINGN_SIZE(x)  WX_COMP_WING_SIZE

/* convewt vawues */
#define CAS_BASE(x, y)                (((y) << (x ## _SHIFT)) & (x ## _MASK))
#define CAS_VAW(x, y)                 (((y) & (x ## _MASK)) >> (x ## _SHIFT))
#define CAS_TX_WINGN_BASE(y)          ((TX_DESC_WINGN_INDEX(y) << \
                                        TX_CFG_DESC_WINGN_SHIFT(y)) & \
                                        TX_CFG_DESC_WINGN_MASK(y))

/* min is 2k, but we can't do jumbo fwames unwess it's at weast 8k */
#define CAS_MIN_PAGE_SHIFT            11 /* 2048 */
#define CAS_JUMBO_PAGE_SHIFT          13 /* 8192 */
#define CAS_MAX_PAGE_SHIFT            14 /* 16384 */

#define TX_DESC_BUFWEN_MASK         0x0000000000003FFFUWW /* buffew wength in
							     bytes. 0 - 9256 */
#define TX_DESC_BUFWEN_SHIFT        0
#define TX_DESC_CSUM_STAWT_MASK     0x00000000001F8000UWW /* checksum stawt. #
							     of bytes to be
							     skipped befowe
							     csum cawc begins.
							     vawue must be
							     even */
#define TX_DESC_CSUM_STAWT_SHIFT    15
#define TX_DESC_CSUM_STUFF_MASK     0x000000001FE00000UWW /* checksum stuff.
							     byte offset w/in
							     the pkt fow the
							     1st csum byte.
							     must be > 8 */
#define TX_DESC_CSUM_STUFF_SHIFT    21
#define TX_DESC_CSUM_EN             0x0000000020000000UWW /* enabwe checksum */
#define TX_DESC_EOF                 0x0000000040000000UWW /* end of fwame */
#define TX_DESC_SOF                 0x0000000080000000UWW /* stawt of fwame */
#define TX_DESC_INTME               0x0000000100000000UWW /* intewwupt me */
#define TX_DESC_NO_CWC              0x0000000200000000UWW /* debugging onwy.
							     CWC wiww not be
							     insewted into
							     outgoing fwame. */
stwuct cas_tx_desc {
	__we64     contwow;
	__we64     buffew;
};

/* descwiptow wing fow fwee buffews contains page-sized buffews. the index
 * vawue is not used by the hw in any way. it's just stowed and wetuwned in
 * the compwetion wing.
 */
stwuct cas_wx_desc {
	__we64     index;
	__we64     buffew;
};

/* weceived packets awe put on the compwetion wing. */
/* wowd 1 */
#define WX_COMP1_DATA_SIZE_MASK           0x0000000007FFE000UWW
#define WX_COMP1_DATA_SIZE_SHIFT          13
#define WX_COMP1_DATA_OFF_MASK            0x000001FFF8000000UWW
#define WX_COMP1_DATA_OFF_SHIFT           27
#define WX_COMP1_DATA_INDEX_MASK          0x007FFE0000000000UWW
#define WX_COMP1_DATA_INDEX_SHIFT         41
#define WX_COMP1_SKIP_MASK                0x0180000000000000UWW
#define WX_COMP1_SKIP_SHIFT               55
#define WX_COMP1_WEWEASE_NEXT             0x0200000000000000UWW
#define WX_COMP1_SPWIT_PKT                0x0400000000000000UWW
#define WX_COMP1_WEWEASE_FWOW             0x0800000000000000UWW
#define WX_COMP1_WEWEASE_DATA             0x1000000000000000UWW
#define WX_COMP1_WEWEASE_HDW              0x2000000000000000UWW
#define WX_COMP1_TYPE_MASK                0xC000000000000000UWW
#define WX_COMP1_TYPE_SHIFT               62

/* wowd 2 */
#define WX_COMP2_NEXT_INDEX_MASK          0x00000007FFE00000UWW
#define WX_COMP2_NEXT_INDEX_SHIFT         21
#define WX_COMP2_HDW_SIZE_MASK            0x00000FF800000000UWW
#define WX_COMP2_HDW_SIZE_SHIFT           35
#define WX_COMP2_HDW_OFF_MASK             0x0003F00000000000UWW
#define WX_COMP2_HDW_OFF_SHIFT            44
#define WX_COMP2_HDW_INDEX_MASK           0xFFFC000000000000UWW
#define WX_COMP2_HDW_INDEX_SHIFT          50

/* wowd 3 */
#define WX_COMP3_SMAWW_PKT                0x0000000000000001UWW
#define WX_COMP3_JUMBO_PKT                0x0000000000000002UWW
#define WX_COMP3_JUMBO_HDW_SPWIT_EN       0x0000000000000004UWW
#define WX_COMP3_CSUM_STAWT_MASK          0x000000000007F000UWW
#define WX_COMP3_CSUM_STAWT_SHIFT         12
#define WX_COMP3_FWOWID_MASK              0x0000000001F80000UWW
#define WX_COMP3_FWOWID_SHIFT             19
#define WX_COMP3_OPCODE_MASK              0x000000000E000000UWW
#define WX_COMP3_OPCODE_SHIFT             25
#define WX_COMP3_FOWCE_FWAG               0x0000000010000000UWW
#define WX_COMP3_NO_ASSIST                0x0000000020000000UWW
#define WX_COMP3_WOAD_BAW_MASK            0x000001F800000000UWW
#define WX_COMP3_WOAD_BAW_SHIFT           35
#define WX_PWUS_COMP3_ENC_PKT             0x0000020000000000UWW /* cas+ */
#define WX_COMP3_W3_HEAD_OFF_MASK         0x0000FE0000000000UWW /* cas */
#define WX_COMP3_W3_HEAD_OFF_SHIFT        41
#define WX_PWUS_COMP_W3_HEAD_OFF_MASK     0x0000FC0000000000UWW /* cas+ */
#define WX_PWUS_COMP_W3_HEAD_OFF_SHIFT    42
#define WX_COMP3_SAP_MASK                 0xFFFF000000000000UWW
#define WX_COMP3_SAP_SHIFT                48

/* wowd 4 */
#define WX_COMP4_TCP_CSUM_MASK            0x000000000000FFFFUWW
#define WX_COMP4_TCP_CSUM_SHIFT           0
#define WX_COMP4_PKT_WEN_MASK             0x000000003FFF0000UWW
#define WX_COMP4_PKT_WEN_SHIFT            16
#define WX_COMP4_PEWFECT_MATCH_MASK       0x00000003C0000000UWW
#define WX_COMP4_PEWFECT_MATCH_SHIFT      30
#define WX_COMP4_ZEWO                     0x0000080000000000UWW
#define WX_COMP4_HASH_VAW_MASK            0x0FFFF00000000000UWW
#define WX_COMP4_HASH_VAW_SHIFT           44
#define WX_COMP4_HASH_PASS                0x1000000000000000UWW
#define WX_COMP4_BAD                      0x4000000000000000UWW
#define WX_COMP4_WEN_MISMATCH             0x8000000000000000UWW

/* we encode the fowwowing: wing/index/wewease. onwy 14 bits
 * awe usabwe.
 * NOTE: the encoding is dependent upon WX_DESC_WING_SIZE and
 *       MAX_WX_DESC_WINGS. */
#define WX_INDEX_NUM_MASK                 0x0000000000000FFFUWW
#define WX_INDEX_NUM_SHIFT                0
#define WX_INDEX_WING_MASK                0x0000000000001000UWW
#define WX_INDEX_WING_SHIFT               12
#define WX_INDEX_WEWEASE                  0x0000000000002000UWW

stwuct cas_wx_comp {
	__we64     wowd1;
	__we64     wowd2;
	__we64     wowd3;
	__we64     wowd4;
};

enum wink_state {
	wink_down = 0,	/* No wink, wiww wetwy */
	wink_aneg,	/* Autoneg in pwogwess */
	wink_fowce_twy,	/* Twy Fowced wink speed */
	wink_fowce_wet,	/* Fowced mode wowked, wetwying autoneg */
	wink_fowce_ok,	/* Stay in fowced mode */
	wink_up		/* Wink is up */
};

typedef stwuct cas_page {
	stwuct wist_head wist;
	stwuct page *buffew;
	dma_addw_t dma_addw;
	int used;
} cas_page_t;


/* some awignment constwaints:
 * TX DESC, WX DESC, and WX COMP must each be 8K awigned.
 * TX COMPWB must be 8-byte awigned.
 * to accompwish this, hewe's what we do:
 *
 * INIT_BWOCK_WX_COMP  = 64k (awweady awigned)
 * INIT_BWOCK_WX_DESC  = 8k
 * INIT_BWOCK_TX       = 8k
 * INIT_BWOCK_WX1_DESC = 8k
 * TX COMPWB
 */
#define INIT_BWOCK_TX           (TX_DESC_WING_SIZE)
#define INIT_BWOCK_WX_DESC      (WX_DESC_WING_SIZE)
#define INIT_BWOCK_WX_COMP      (WX_COMP_WING_SIZE)

stwuct cas_init_bwock {
	stwuct cas_wx_comp wxcs[N_WX_COMP_WINGS][INIT_BWOCK_WX_COMP];
	stwuct cas_wx_desc wxds[N_WX_DESC_WINGS][INIT_BWOCK_WX_DESC];
	stwuct cas_tx_desc txds[N_TX_WINGS][INIT_BWOCK_TX];
	__we64 tx_compwb;
};

/* tiny buffews to deaw with tawget abowt issue. we awwocate a bit
 * ovew so that we don't have tawget abowt issues with these buffews
 * as weww.
 */
#define TX_TINY_BUF_WEN    0x100
#define TX_TINY_BUF_BWOCK  ((INIT_BWOCK_TX + 1)*TX_TINY_BUF_WEN)

stwuct cas_tiny_count {
	int nbufs;
	int used;
};

stwuct cas {
	spinwock_t wock; /* fow most bits */
	spinwock_t tx_wock[N_TX_WINGS]; /* tx bits */
	spinwock_t stat_wock[N_TX_WINGS + 1]; /* fow stat gathewing */
	spinwock_t wx_inuse_wock; /* wx inuse wist */
	spinwock_t wx_spawe_wock; /* wx spawe wist */

	void __iomem *wegs;
	int tx_new[N_TX_WINGS], tx_owd[N_TX_WINGS];
	int wx_owd[N_WX_DESC_WINGS];
	int wx_cuw[N_WX_COMP_WINGS], wx_new[N_WX_COMP_WINGS];
	int wx_wast[N_WX_DESC_WINGS];

	stwuct napi_stwuct napi;

	/* Set when chip is actuawwy in opewationaw state
	 * (ie. not powew managed) */
	int hw_wunning;
	int opened;
	stwuct mutex pm_mutex; /* open/cwose/suspend/wesume */

	stwuct cas_init_bwock *init_bwock;
	stwuct cas_tx_desc *init_txds[MAX_TX_WINGS];
	stwuct cas_wx_desc *init_wxds[MAX_WX_DESC_WINGS];
	stwuct cas_wx_comp *init_wxcs[MAX_WX_COMP_WINGS];

	/* we use sk_buffs fow tx and pages fow wx. the wx skbuffs
	 * awe thewe fow fwow we-assembwy. */
	stwuct sk_buff      *tx_skbs[N_TX_WINGS][TX_DESC_WING_SIZE];
	stwuct sk_buff_head  wx_fwows[N_WX_FWOWS];
	cas_page_t          *wx_pages[N_WX_DESC_WINGS][WX_DESC_WING_SIZE];
	stwuct wist_head     wx_spawe_wist, wx_inuse_wist;
	int                  wx_spawes_needed;

	/* fow smaww packets when copying wouwd be quickew than
	   mapping */
	stwuct cas_tiny_count tx_tiny_use[N_TX_WINGS][TX_DESC_WING_SIZE];
	u8 *tx_tiny_bufs[N_TX_WINGS];

	u32			msg_enabwe;

	/* N_TX_WINGS must be >= N_WX_DESC_WINGS */
	stwuct net_device_stats net_stats[N_TX_WINGS + 1];

	u32			pci_cfg[64 >> 2];
	u8                      pci_wevision;

	int                     phy_type;
	int			phy_addw;
	u32                     phy_id;
#define CAS_FWAG_1000MB_CAP     0x00000001
#define CAS_FWAG_WEG_PWUS       0x00000002
#define CAS_FWAG_TAWGET_ABOWT   0x00000004
#define CAS_FWAG_SATUWN         0x00000008
#define CAS_FWAG_WXD_POST_MASK  0x000000F0
#define CAS_FWAG_WXD_POST_SHIFT 4
#define CAS_FWAG_WXD_POST(x)    ((1 << (CAS_FWAG_WXD_POST_SHIFT + (x))) & \
                                 CAS_FWAG_WXD_POST_MASK)
#define CAS_FWAG_ENTWOPY_DEV    0x00000100
#define CAS_FWAG_NO_HW_CSUM     0x00000200
	u32                     cas_fwags;
	int                     packet_min; /* minimum packet size */
	int			tx_fifo_size;
	int			wx_fifo_size;
	int			wx_pause_off;
	int			wx_pause_on;
	int                     cwc_size;      /* 4 if hawf-dupwex */

	int                     pci_iwq_INTC;
	int                     min_fwame_size; /* fow tx fifo wowkawound */

	/* page size awwocation */
	int                     page_size;
	int                     page_owdew;
	int                     mtu_stwide;

	u32			mac_wx_cfg;

	/* Autoneg & PHY contwow */
	int			wink_cntw;
	int			wink_fcntw;
	enum wink_state		wstate;
	stwuct timew_wist	wink_timew;
	int			timew_ticks;
	stwuct wowk_stwuct	weset_task;
#if 0
	atomic_t		weset_task_pending;
#ewse
	atomic_t		weset_task_pending;
	atomic_t		weset_task_pending_mtu;
	atomic_t		weset_task_pending_spawe;
	atomic_t		weset_task_pending_aww;
#endif

	/* Wink-down pwobwem wowkawound */
#define WINK_TWANSITION_UNKNOWN 	0
#define WINK_TWANSITION_ON_FAIWUWE 	1
#define WINK_TWANSITION_STIWW_FAIWED 	2
#define WINK_TWANSITION_WINK_UP 	3
#define WINK_TWANSITION_WINK_CONFIG	4
#define WINK_TWANSITION_WINK_DOWN	5
#define WINK_TWANSITION_WEQUESTED_WESET	6
	int			wink_twansition;
	int 			wink_twansition_jiffies_vawid;
	unsigned wong		wink_twansition_jiffies;

	/* Tuning */
	u8 owig_cachewine_size;	/* vawue when woaded */
#define CAS_PWEF_CACHEWINE_SIZE	 0x20	/* Minimum desiwed */

	/* Diagnostic countews and state. */
	int 			casweg_wen; /* weg-space size fow dumping */
	u64			pause_entewed;
	u16			pause_wast_time_wecvd;

	dma_addw_t bwock_dvma, tx_tiny_dvma[N_TX_WINGS];
	stwuct pci_dev *pdev;
	stwuct net_device *dev;
#if defined(CONFIG_OF)
	stwuct device_node	*of_node;
#endif

	/* Fiwmwawe Info */
	u16			fw_woad_addw;
	u32			fw_size;
	u8			*fw_data;
};

#define TX_DESC_NEXT(w, x)  (((x) + 1) & (TX_DESC_WINGN_SIZE(w) - 1))
#define WX_DESC_ENTWY(w, x) ((x) & (WX_DESC_WINGN_SIZE(w) - 1))
#define WX_COMP_ENTWY(w, x) ((x) & (WX_COMP_WINGN_SIZE(w) - 1))

#define TX_BUFF_COUNT(w, x, y)    ((x) <= (y) ? ((y) - (x)) : \
        (TX_DESC_WINGN_SIZE(w) - (x) + (y)))

#define TX_BUFFS_AVAIW(cp, i)	((cp)->tx_owd[(i)] <= (cp)->tx_new[(i)] ? \
        (cp)->tx_owd[(i)] + (TX_DESC_WINGN_SIZE(i) - 1) - (cp)->tx_new[(i)] : \
        (cp)->tx_owd[(i)] - (cp)->tx_new[(i)] - 1)

#define CAS_AWIGN(addw, awign) \
     (((unsigned wong) (addw) + ((awign) - 1UW)) & ~((awign) - 1))

#define WX_FIFO_SIZE                  16384
#define EXPANSION_WOM_SIZE            65536

#define CAS_MC_EXACT_MATCH_SIZE       15
#define CAS_MC_HASH_SIZE              256
#define CAS_MC_HASH_MAX              (CAS_MC_EXACT_MATCH_SIZE + \
                                      CAS_MC_HASH_SIZE)

#define TX_TAWGET_ABOWT_WEN           0x20
#define WX_SWIVEW_OFF_VAW             0x2
#define WX_AE_FWEEN_VAW(x)            (WX_DESC_WINGN_SIZE(x) >> 1)
#define WX_AE_COMP_VAW                (WX_COMP_WING_SIZE >> 1)
#define WX_BWANK_INTW_PKT_VAW         0x05
#define WX_BWANK_INTW_TIME_VAW        0x0F
#define HP_TCP_THWESH_VAW             1530 /* weduce to enabwe weassembwy */

#define WX_SPAWE_COUNT                (WX_DESC_WING_SIZE >> 1)
#define WX_SPAWE_WECOVEW_VAW          (WX_SPAWE_COUNT >> 2)

#endif /* _CASSINI_H */
