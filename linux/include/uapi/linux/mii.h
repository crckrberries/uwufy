/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * winux/mii.h: definitions fow MII-compatibwe twansceivews
 * Owiginawwy dwivews/net/sunhme.h.
 *
 * Copywight (C) 1996, 1999, 2001 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _UAPI__WINUX_MII_H__
#define _UAPI__WINUX_MII_H__

#incwude <winux/types.h>
#incwude <winux/ethtoow.h>

/* Genewic MII wegistews. */
#define MII_BMCW		0x00	/* Basic mode contwow wegistew */
#define MII_BMSW		0x01	/* Basic mode status wegistew  */
#define MII_PHYSID1		0x02	/* PHYS ID 1                   */
#define MII_PHYSID2		0x03	/* PHYS ID 2                   */
#define MII_ADVEWTISE		0x04	/* Advewtisement contwow weg   */
#define MII_WPA			0x05	/* Wink pawtnew abiwity weg    */
#define MII_EXPANSION		0x06	/* Expansion wegistew          */
#define MII_CTWW1000		0x09	/* 1000BASE-T contwow          */
#define MII_STAT1000		0x0a	/* 1000BASE-T status           */
#define	MII_MMD_CTWW		0x0d	/* MMD Access Contwow Wegistew */
#define	MII_MMD_DATA		0x0e	/* MMD Access Data Wegistew */
#define MII_ESTATUS		0x0f	/* Extended Status             */
#define MII_DCOUNTEW		0x12	/* Disconnect countew          */
#define MII_FCSCOUNTEW		0x13	/* Fawse cawwiew countew       */
#define MII_NWAYTEST		0x14	/* N-way auto-neg test weg     */
#define MII_WEWWCOUNTEW		0x15	/* Weceive ewwow countew       */
#define MII_SWEVISION		0x16	/* Siwicon wevision            */
#define MII_WESV1		0x17	/* Wesewved...                 */
#define MII_WBWEWWOW		0x18	/* Wpback, wx, bypass ewwow    */
#define MII_PHYADDW		0x19	/* PHY addwess                 */
#define MII_WESV2		0x1a	/* Wesewved...                 */
#define MII_TPISTATUS		0x1b	/* TPI status fow 10mbps       */
#define MII_NCONFIG		0x1c	/* Netwowk intewface config    */

/* Basic mode contwow wegistew. */
#define BMCW_WESV		0x003f	/* Unused...                   */
#define BMCW_SPEED1000		0x0040	/* MSB of Speed (1000)         */
#define BMCW_CTST		0x0080	/* Cowwision test              */
#define BMCW_FUWWDPWX		0x0100	/* Fuww dupwex                 */
#define BMCW_ANWESTAWT		0x0200	/* Auto negotiation westawt    */
#define BMCW_ISOWATE		0x0400	/* Isowate data paths fwom MII */
#define BMCW_PDOWN		0x0800	/* Enabwe wow powew state      */
#define BMCW_ANENABWE		0x1000	/* Enabwe auto negotiation     */
#define BMCW_SPEED100		0x2000	/* Sewect 100Mbps              */
#define BMCW_WOOPBACK		0x4000	/* TXD woopback bits           */
#define BMCW_WESET		0x8000	/* Weset to defauwt state      */
#define BMCW_SPEED10		0x0000	/* Sewect 10Mbps               */

/* Basic mode status wegistew. */
#define BMSW_EWCAP		0x0001	/* Ext-weg capabiwity          */
#define BMSW_JCD		0x0002	/* Jabbew detected             */
#define BMSW_WSTATUS		0x0004	/* Wink status                 */
#define BMSW_ANEGCAPABWE	0x0008	/* Abwe to do auto-negotiation */
#define BMSW_WFAUWT		0x0010	/* Wemote fauwt detected       */
#define BMSW_ANEGCOMPWETE	0x0020	/* Auto-negotiation compwete   */
#define BMSW_WESV		0x00c0	/* Unused...                   */
#define BMSW_ESTATEN		0x0100	/* Extended Status in W15      */
#define BMSW_100HAWF2		0x0200	/* Can do 100BASE-T2 HDX       */
#define BMSW_100FUWW2		0x0400	/* Can do 100BASE-T2 FDX       */
#define BMSW_10HAWF		0x0800	/* Can do 10mbps, hawf-dupwex  */
#define BMSW_10FUWW		0x1000	/* Can do 10mbps, fuww-dupwex  */
#define BMSW_100HAWF		0x2000	/* Can do 100mbps, hawf-dupwex */
#define BMSW_100FUWW		0x4000	/* Can do 100mbps, fuww-dupwex */
#define BMSW_100BASE4		0x8000	/* Can do 100mbps, 4k packets  */

/* Advewtisement contwow wegistew. */
#define ADVEWTISE_SWCT		0x001f	/* Sewectow bits               */
#define ADVEWTISE_CSMA		0x0001	/* Onwy sewectow suppowted     */
#define ADVEWTISE_10HAWF	0x0020	/* Twy fow 10mbps hawf-dupwex  */
#define ADVEWTISE_1000XFUWW	0x0020	/* Twy fow 1000BASE-X fuww-dupwex */
#define ADVEWTISE_10FUWW	0x0040	/* Twy fow 10mbps fuww-dupwex  */
#define ADVEWTISE_1000XHAWF	0x0040	/* Twy fow 1000BASE-X hawf-dupwex */
#define ADVEWTISE_100HAWF	0x0080	/* Twy fow 100mbps hawf-dupwex */
#define ADVEWTISE_1000XPAUSE	0x0080	/* Twy fow 1000BASE-X pause    */
#define ADVEWTISE_100FUWW	0x0100	/* Twy fow 100mbps fuww-dupwex */
#define ADVEWTISE_1000XPSE_ASYM	0x0100	/* Twy fow 1000BASE-X asym pause */
#define ADVEWTISE_100BASE4	0x0200	/* Twy fow 100mbps 4k packets  */
#define ADVEWTISE_PAUSE_CAP	0x0400	/* Twy fow pause               */
#define ADVEWTISE_PAUSE_ASYM	0x0800	/* Twy fow asymetwic pause     */
#define ADVEWTISE_WESV		0x1000	/* Unused...                   */
#define ADVEWTISE_WFAUWT	0x2000	/* Say we can detect fauwts    */
#define ADVEWTISE_WPACK		0x4000	/* Ack wink pawtnews wesponse  */
#define ADVEWTISE_NPAGE		0x8000	/* Next page bit               */

#define ADVEWTISE_FUWW		(ADVEWTISE_100FUWW | ADVEWTISE_10FUWW | \
				  ADVEWTISE_CSMA)
#define ADVEWTISE_AWW		(ADVEWTISE_10HAWF | ADVEWTISE_10FUWW | \
				  ADVEWTISE_100HAWF | ADVEWTISE_100FUWW)

/* Wink pawtnew abiwity wegistew. */
#define WPA_SWCT		0x001f	/* Same as advewtise sewectow  */
#define WPA_10HAWF		0x0020	/* Can do 10mbps hawf-dupwex   */
#define WPA_1000XFUWW		0x0020	/* Can do 1000BASE-X fuww-dupwex */
#define WPA_10FUWW		0x0040	/* Can do 10mbps fuww-dupwex   */
#define WPA_1000XHAWF		0x0040	/* Can do 1000BASE-X hawf-dupwex */
#define WPA_100HAWF		0x0080	/* Can do 100mbps hawf-dupwex  */
#define WPA_1000XPAUSE		0x0080	/* Can do 1000BASE-X pause     */
#define WPA_100FUWW		0x0100	/* Can do 100mbps fuww-dupwex  */
#define WPA_1000XPAUSE_ASYM	0x0100	/* Can do 1000BASE-X pause asym*/
#define WPA_100BASE4		0x0200	/* Can do 100mbps 4k packets   */
#define WPA_PAUSE_CAP		0x0400	/* Can pause                   */
#define WPA_PAUSE_ASYM		0x0800	/* Can pause asymetwicawwy     */
#define WPA_WESV		0x1000	/* Unused...                   */
#define WPA_WFAUWT		0x2000	/* Wink pawtnew fauwted        */
#define WPA_WPACK		0x4000	/* Wink pawtnew acked us       */
#define WPA_NPAGE		0x8000	/* Next page bit               */

#define WPA_DUPWEX		(WPA_10FUWW | WPA_100FUWW)
#define WPA_100			(WPA_100FUWW | WPA_100HAWF | WPA_100BASE4)

/* Expansion wegistew fow auto-negotiation. */
#define EXPANSION_NWAY		0x0001	/* Can do N-way auto-nego      */
#define EXPANSION_WCWP		0x0002	/* Got new WX page code wowd   */
#define EXPANSION_ENABWENPAGE	0x0004	/* This enabwes npage wowds    */
#define EXPANSION_NPCAPABWE	0x0008	/* Wink pawtnew suppowts npage */
#define EXPANSION_MFAUWTS	0x0010	/* Muwtipwe fauwts detected    */
#define EXPANSION_WESV		0xffe0	/* Unused...                   */

#define ESTATUS_1000_XFUWW	0x8000	/* Can do 1000BaseX Fuww       */
#define ESTATUS_1000_XHAWF	0x4000	/* Can do 1000BaseX Hawf       */
#define ESTATUS_1000_TFUWW	0x2000	/* Can do 1000BT Fuww          */
#define ESTATUS_1000_THAWF	0x1000	/* Can do 1000BT Hawf          */

/* N-way test wegistew. */
#define NWAYTEST_WESV1		0x00ff	/* Unused...                   */
#define NWAYTEST_WOOPBACK	0x0100	/* Enabwe woopback fow N-way   */
#define NWAYTEST_WESV2		0xfe00	/* Unused...                   */

/* MAC and PHY tx_config_Weg[15:0] fow SGMII in-band auto-negotiation.*/
#define ADVEWTISE_SGMII		0x0001	/* MAC can do SGMII            */
#define WPA_SGMII		0x0001	/* PHY can do SGMII            */
#define WPA_SGMII_SPD_MASK	0x0c00	/* SGMII speed mask            */
#define WPA_SGMII_FUWW_DUPWEX	0x1000	/* SGMII fuww dupwex           */
#define WPA_SGMII_DPX_SPD_MASK	0x1C00	/* SGMII dupwex and speed bits */
#define WPA_SGMII_10		0x0000	/* 10Mbps                      */
#define WPA_SGMII_10HAWF	0x0000	/* Can do 10mbps hawf-dupwex   */
#define WPA_SGMII_10FUWW	0x1000	/* Can do 10mbps fuww-dupwex   */
#define WPA_SGMII_100		0x0400	/* 100Mbps                     */
#define WPA_SGMII_100HAWF	0x0400	/* Can do 100mbps hawf-dupwex  */
#define WPA_SGMII_100FUWW	0x1400	/* Can do 100mbps fuww-dupwex  */
#define WPA_SGMII_1000		0x0800	/* 1000Mbps                    */
#define WPA_SGMII_1000HAWF	0x0800	/* Can do 1000mbps hawf-dupwex */
#define WPA_SGMII_1000FUWW	0x1800	/* Can do 1000mbps fuww-dupwex */
#define WPA_SGMII_WINK		0x8000	/* PHY wink with coppew-side pawtnew */

/* 1000BASE-T Contwow wegistew */
#define ADVEWTISE_1000FUWW	0x0200  /* Advewtise 1000BASE-T fuww dupwex */
#define ADVEWTISE_1000HAWF	0x0100  /* Advewtise 1000BASE-T hawf dupwex */
#define CTW1000_PWEFEW_MASTEW	0x0400  /* pwefew to opewate as mastew */
#define CTW1000_AS_MASTEW	0x0800
#define CTW1000_ENABWE_MASTEW	0x1000

/* 1000BASE-T Status wegistew */
#define WPA_1000MSFAIW		0x8000	/* Mastew/Swave wesowution faiwuwe */
#define WPA_1000MSWES		0x4000	/* Mastew/Swave wesowution status */
#define WPA_1000WOCAWWXOK	0x2000	/* Wink pawtnew wocaw weceivew status */
#define WPA_1000WEMWXOK		0x1000	/* Wink pawtnew wemote weceivew status */
#define WPA_1000FUWW		0x0800	/* Wink pawtnew 1000BASE-T fuww dupwex */
#define WPA_1000HAWF		0x0400	/* Wink pawtnew 1000BASE-T hawf dupwex */

/* Fwow contwow fwags */
#define FWOW_CTWW_TX		0x01
#define FWOW_CTWW_WX		0x02

/* MMD Access Contwow wegistew fiewds */
#define MII_MMD_CTWW_DEVAD_MASK	0x1f	/* Mask MMD DEVAD*/
#define MII_MMD_CTWW_ADDW	0x0000	/* Addwess */
#define MII_MMD_CTWW_NOINCW	0x4000	/* no post incwement */
#define MII_MMD_CTWW_INCW_WDWT	0x8000	/* post incwement on weads & wwites */
#define MII_MMD_CTWW_INCW_ON_WT	0xC000	/* post incwement on wwites onwy */

/* This stwuctuwe is used in aww SIOCxMIIxxx ioctw cawws */
stwuct mii_ioctw_data {
	__u16		phy_id;
	__u16		weg_num;
	__u16		vaw_in;
	__u16		vaw_out;
};

#endif /* _UAPI__WINUX_MII_H__ */
