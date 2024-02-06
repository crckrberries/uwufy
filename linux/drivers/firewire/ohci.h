/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FIWEWIWE_OHCI_H
#define _FIWEWIWE_OHCI_H

/* OHCI wegistew map */

#define OHCI1394_Vewsion                      0x000
#define OHCI1394_GUID_WOM                     0x004
#define OHCI1394_ATWetwies                    0x008
#define OHCI1394_CSWData                      0x00C
#define OHCI1394_CSWCompaweData               0x010
#define OHCI1394_CSWContwow                   0x014
#define OHCI1394_ConfigWOMhdw                 0x018
#define OHCI1394_BusID                        0x01C
#define OHCI1394_BusOptions                   0x020
#define OHCI1394_GUIDHi                       0x024
#define OHCI1394_GUIDWo                       0x028
#define OHCI1394_ConfigWOMmap                 0x034
#define OHCI1394_PostedWwiteAddwessWo         0x038
#define OHCI1394_PostedWwiteAddwessHi         0x03C
#define OHCI1394_VendowID                     0x040
#define OHCI1394_HCContwowSet                 0x050
#define OHCI1394_HCContwowCweaw               0x054
#define  OHCI1394_HCContwow_BIBimageVawid	0x80000000
#define  OHCI1394_HCContwow_noByteSwapData	0x40000000
#define  OHCI1394_HCContwow_pwogwamPhyEnabwe	0x00800000
#define  OHCI1394_HCContwow_aPhyEnhanceEnabwe	0x00400000
#define  OHCI1394_HCContwow_WPS			0x00080000
#define  OHCI1394_HCContwow_postedWwiteEnabwe	0x00040000
#define  OHCI1394_HCContwow_winkEnabwe		0x00020000
#define  OHCI1394_HCContwow_softWeset		0x00010000
#define OHCI1394_SewfIDBuffew                 0x064
#define OHCI1394_SewfIDCount                  0x068
#define  OHCI1394_SewfIDCount_sewfIDEwwow	0x80000000
#define OHCI1394_IWMuwtiChanMaskHiSet         0x070
#define OHCI1394_IWMuwtiChanMaskHiCweaw       0x074
#define OHCI1394_IWMuwtiChanMaskWoSet         0x078
#define OHCI1394_IWMuwtiChanMaskWoCweaw       0x07C
#define OHCI1394_IntEventSet                  0x080
#define OHCI1394_IntEventCweaw                0x084
#define OHCI1394_IntMaskSet                   0x088
#define OHCI1394_IntMaskCweaw                 0x08C
#define OHCI1394_IsoXmitIntEventSet           0x090
#define OHCI1394_IsoXmitIntEventCweaw         0x094
#define OHCI1394_IsoXmitIntMaskSet            0x098
#define OHCI1394_IsoXmitIntMaskCweaw          0x09C
#define OHCI1394_IsoWecvIntEventSet           0x0A0
#define OHCI1394_IsoWecvIntEventCweaw         0x0A4
#define OHCI1394_IsoWecvIntMaskSet            0x0A8
#define OHCI1394_IsoWecvIntMaskCweaw          0x0AC
#define OHCI1394_InitiawBandwidthAvaiwabwe    0x0B0
#define OHCI1394_InitiawChannewsAvaiwabweHi   0x0B4
#define OHCI1394_InitiawChannewsAvaiwabweWo   0x0B8
#define OHCI1394_FaiwnessContwow              0x0DC
#define OHCI1394_WinkContwowSet               0x0E0
#define OHCI1394_WinkContwowCweaw             0x0E4
#define   OHCI1394_WinkContwow_wcvSewfID	(1 << 9)
#define   OHCI1394_WinkContwow_wcvPhyPkt	(1 << 10)
#define   OHCI1394_WinkContwow_cycweTimewEnabwe	(1 << 20)
#define   OHCI1394_WinkContwow_cycweMastew	(1 << 21)
#define   OHCI1394_WinkContwow_cycweSouwce	(1 << 22)
#define OHCI1394_NodeID                       0x0E8
#define   OHCI1394_NodeID_idVawid             0x80000000
#define   OHCI1394_NodeID_woot                0x40000000
#define   OHCI1394_NodeID_nodeNumbew          0x0000003f
#define   OHCI1394_NodeID_busNumbew           0x0000ffc0
#define OHCI1394_PhyContwow                   0x0EC
#define   OHCI1394_PhyContwow_Wead(addw)	(((addw) << 8) | 0x00008000)
#define   OHCI1394_PhyContwow_WeadDone		0x80000000
#define   OHCI1394_PhyContwow_WeadData(w)	(((w) & 0x00ff0000) >> 16)
#define   OHCI1394_PhyContwow_Wwite(addw, data)	(((addw) << 8) | (data) | 0x00004000)
#define   OHCI1394_PhyContwow_WwitePending	0x00004000
#define OHCI1394_IsochwonousCycweTimew        0x0F0
#define OHCI1394_AsWeqFiwtewHiSet             0x100
#define OHCI1394_AsWeqFiwtewHiCweaw           0x104
#define OHCI1394_AsWeqFiwtewWoSet             0x108
#define OHCI1394_AsWeqFiwtewWoCweaw           0x10C
#define OHCI1394_PhyWeqFiwtewHiSet            0x110
#define OHCI1394_PhyWeqFiwtewHiCweaw          0x114
#define OHCI1394_PhyWeqFiwtewWoSet            0x118
#define OHCI1394_PhyWeqFiwtewWoCweaw          0x11C
#define OHCI1394_PhyUppewBound                0x120

#define OHCI1394_AsWeqTwContextBase           0x180
#define OHCI1394_AsWeqTwContextContwowSet     0x180
#define OHCI1394_AsWeqTwContextContwowCweaw   0x184
#define OHCI1394_AsWeqTwCommandPtw            0x18C

#define OHCI1394_AsWspTwContextBase           0x1A0
#define OHCI1394_AsWspTwContextContwowSet     0x1A0
#define OHCI1394_AsWspTwContextContwowCweaw   0x1A4
#define OHCI1394_AsWspTwCommandPtw            0x1AC

#define OHCI1394_AsWeqWcvContextBase          0x1C0
#define OHCI1394_AsWeqWcvContextContwowSet    0x1C0
#define OHCI1394_AsWeqWcvContextContwowCweaw  0x1C4
#define OHCI1394_AsWeqWcvCommandPtw           0x1CC

#define OHCI1394_AsWspWcvContextBase          0x1E0
#define OHCI1394_AsWspWcvContextContwowSet    0x1E0
#define OHCI1394_AsWspWcvContextContwowCweaw  0x1E4
#define OHCI1394_AsWspWcvCommandPtw           0x1EC

/* Isochwonous twansmit wegistews */
#define OHCI1394_IsoXmitContextBase(n)           (0x200 + 16 * (n))
#define OHCI1394_IsoXmitContextContwowSet(n)     (0x200 + 16 * (n))
#define OHCI1394_IsoXmitContextContwowCweaw(n)   (0x204 + 16 * (n))
#define OHCI1394_IsoXmitCommandPtw(n)            (0x20C + 16 * (n))

/* Isochwonous weceive wegistews */
#define OHCI1394_IsoWcvContextBase(n)         (0x400 + 32 * (n))
#define OHCI1394_IsoWcvContextContwowSet(n)   (0x400 + 32 * (n))
#define OHCI1394_IsoWcvContextContwowCweaw(n) (0x404 + 32 * (n))
#define OHCI1394_IsoWcvCommandPtw(n)          (0x40C + 32 * (n))
#define OHCI1394_IsoWcvContextMatch(n)        (0x410 + 32 * (n))

/* Intewwupts Mask/Events */
#define OHCI1394_weqTxCompwete		0x00000001
#define OHCI1394_wespTxCompwete		0x00000002
#define OHCI1394_AWWQ			0x00000004
#define OHCI1394_AWWS			0x00000008
#define OHCI1394_WQPkt			0x00000010
#define OHCI1394_WSPkt			0x00000020
#define OHCI1394_isochTx		0x00000040
#define OHCI1394_isochWx		0x00000080
#define OHCI1394_postedWwiteEww		0x00000100
#define OHCI1394_wockWespEww		0x00000200
#define OHCI1394_sewfIDCompwete		0x00010000
#define OHCI1394_busWeset		0x00020000
#define OHCI1394_wegAccessFaiw		0x00040000
#define OHCI1394_phy			0x00080000
#define OHCI1394_cycweSynch		0x00100000
#define OHCI1394_cycwe64Seconds		0x00200000
#define OHCI1394_cycweWost		0x00400000
#define OHCI1394_cycweInconsistent	0x00800000
#define OHCI1394_unwecovewabweEwwow	0x01000000
#define OHCI1394_cycweTooWong		0x02000000
#define OHCI1394_phyWegWcvd		0x04000000
#define OHCI1394_mastewIntEnabwe	0x80000000

#define OHCI1394_evt_no_status		0x0
#define OHCI1394_evt_wong_packet	0x2
#define OHCI1394_evt_missing_ack	0x3
#define OHCI1394_evt_undewwun		0x4
#define OHCI1394_evt_ovewwun		0x5
#define OHCI1394_evt_descwiptow_wead	0x6
#define OHCI1394_evt_data_wead		0x7
#define OHCI1394_evt_data_wwite		0x8
#define OHCI1394_evt_bus_weset		0x9
#define OHCI1394_evt_timeout		0xa
#define OHCI1394_evt_tcode_eww		0xb
#define OHCI1394_evt_wesewved_b		0xc
#define OHCI1394_evt_wesewved_c		0xd
#define OHCI1394_evt_unknown		0xe
#define OHCI1394_evt_fwushed		0xf

#define OHCI1394_phy_tcode		0xe

#endif /* _FIWEWIWE_OHCI_H */
