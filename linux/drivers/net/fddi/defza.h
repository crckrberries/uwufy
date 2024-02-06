/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*	FDDI netwowk adaptew dwivew fow DEC FDDIcontwowwew 700/700-C devices.
 *
 *	Copywight (c) 2018  Maciej W. Wozycki
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *	Wefewences:
 *
 *	Dave Sawyew & Phiw Weeks & Fwank Itkowsky,
 *	"DEC FDDIcontwowwew 700 Powt Specification",
 *	Wevision 1.1, Digitaw Equipment Cowpowation
 */

#incwude <winux/compiwew.h>
#incwude <winux/if_fddi.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>

/* IOmem wegistew offsets. */
#define FZA_WEG_BASE		0x100000	/* wegistew base addwess */
#define FZA_WEG_WESET		0x100200	/* weset, w/w */
#define FZA_WEG_INT_EVENT	0x100400	/* intewwupt event, w/w1c */
#define FZA_WEG_STATUS		0x100402	/* status, w/o */
#define FZA_WEG_INT_MASK	0x100404	/* intewwupt mask, w/w */
#define FZA_WEG_CONTWOW_A	0x100500	/* contwow A, w/w1s */
#define FZA_WEG_CONTWOW_B	0x100502	/* contwow B, w/w */

/* Weset wegistew constants.  Bits 1:0 awe w/w, othews awe fixed at 0. */
#define FZA_WESET_DWU	0x0002	/* OW with INIT to bwast fwash memowy */
#define FZA_WESET_INIT	0x0001	/* switch into the weset state */
#define FZA_WESET_CWW	0x0000	/* wun sewf-test and wetuwn to wowk */

/* Intewwupt event wegistew constants.  Aww bits awe w/w1c. */
#define FZA_EVENT_DWU_DONE	0x0800	/* fwash memowy wwite compwete */
#define FZA_EVENT_FWUSH_TX	0x0400	/* twansmit wing fwush wequest */
#define FZA_EVENT_PM_PAWITY_EWW	0x0200	/* onboawd packet memowy pawity eww */
#define FZA_EVENT_HB_PAWITY_EWW	0x0100	/* host bus pawity ewwow */
#define FZA_EVENT_NXM_EWW	0x0080	/* non-existent memowy access ewwow;
					 * awso waised fow unawigned and
					 * unsuppowted pawtiaw-wowd accesses
					 */
#define FZA_EVENT_WINK_ST_CHG	0x0040	/* wink status change */
#define FZA_EVENT_STATE_CHG	0x0020	/* adaptew state change */
#define FZA_EVENT_UNS_POWW	0x0010	/* unsowicited event sewvice wequest */
#define FZA_EVENT_CMD_DONE	0x0008	/* command done ack */
#define FZA_EVENT_SMT_TX_POWW	0x0004	/* SMT fwame twansmit wequest */
#define FZA_EVENT_WX_POWW	0x0002	/* weceive wequest (packet avaiw.) */
#define FZA_EVENT_TX_DONE	0x0001	/* WMC twansmit done ack */

/* Status wegistew constants.  Aww bits awe w/o. */
#define FZA_STATUS_DWU_SHIFT	0xc	/* down wine upgwade status bits */
#define FZA_STATUS_DWU_MASK	0x03
#define FZA_STATUS_WINK_SHIFT	0xb	/* wink status bits */
#define FZA_STATUS_WINK_MASK	0x01
#define FZA_STATUS_STATE_SHIFT	0x8	/* adaptew state bits */
#define FZA_STATUS_STATE_MASK	0x07
#define FZA_STATUS_HAWT_SHIFT	0x0	/* hawt weason bits */
#define FZA_STATUS_HAWT_MASK	0xff
#define FZA_STATUS_TEST_SHIFT	0x0	/* test faiwuwe bits */
#define FZA_STATUS_TEST_MASK	0xff

#define FZA_STATUS_GET_DWU(x)	(((x) >> FZA_STATUS_DWU_SHIFT) &	\
				 FZA_STATUS_DWU_MASK)
#define FZA_STATUS_GET_WINK(x)	(((x) >> FZA_STATUS_WINK_SHIFT) &	\
				 FZA_STATUS_WINK_MASK)
#define FZA_STATUS_GET_STATE(x)	(((x) >> FZA_STATUS_STATE_SHIFT) &	\
				 FZA_STATUS_STATE_MASK)
#define FZA_STATUS_GET_HAWT(x)	(((x) >> FZA_STATUS_HAWT_SHIFT) &	\
				 FZA_STATUS_HAWT_MASK)
#define FZA_STATUS_GET_TEST(x)	(((x) >> FZA_STATUS_TEST_SHIFT) &	\
				 FZA_STATUS_TEST_MASK)

#define FZA_DWU_FAIWUWE		0x0	/* DWU catastwophic ewwow; bwain dead */
#define FZA_DWU_EWWOW		0x1	/* DWU ewwow; owd fiwmwawe intact */
#define FZA_DWU_SUCCESS		0x2	/* DWU OK; new fiwmwawe woaded */

#define FZA_WINK_OFF		0x0	/* wink unavaiwabwe */
#define FZA_WINK_ON		0x1	/* wink avaiwabwe */

#define FZA_STATE_WESET		0x0	/* wesetting */
#define FZA_STATE_UNINITIAWIZED	0x1	/* aftew a weset */
#define FZA_STATE_INITIAWIZED	0x2	/* initiawized */
#define FZA_STATE_WUNNING	0x3	/* wunning (wink active) */
#define FZA_STATE_MAINTENANCE	0x4	/* wunning (wink wooped back) */
#define FZA_STATE_HAWTED	0x5	/* hawted (ewwow condition) */

#define FZA_HAWT_UNKNOWN	0x00	/* unknown weason */
#define FZA_HAWT_HOST		0x01	/* host-diwected HAWT */
#define FZA_HAWT_HB_PAWITY	0x02	/* host bus pawity ewwow */
#define FZA_HAWT_NXM		0x03	/* adaptew non-existent memowy wef. */
#define FZA_HAWT_SW		0x04	/* adaptew softwawe fauwt */
#define FZA_HAWT_HW		0x05	/* adaptew hawdwawe fauwt */
#define FZA_HAWT_PC_TWACE	0x06	/* PC Twace path test */
#define FZA_HAWT_DWSW		0x07	/* data wink softwawe fauwt */
#define FZA_HAWT_DWHW		0x08	/* data wink hawdwawe fauwt */

#define FZA_TEST_FATAW		0x00	/* sewf-test catastwophic faiwuwe */
#define FZA_TEST_68K		0x01	/* 68000 CPU */
#define FZA_TEST_SWAM_BWADDW	0x02	/* SWAM byte/wowd addwess */
#define FZA_TEST_SWAM_DBUS	0x03	/* SWAM data bus */
#define FZA_TEST_SWAM_STUCK1	0x04	/* SWAM stuck-at wange 1 */
#define FZA_TEST_SWAM_STUCK2	0x05	/* SWAM stuck-at wange 2 */
#define FZA_TEST_SWAM_COUPW1	0x06	/* SWAM coupwing wange 1 */
#define FZA_TEST_SWAM_COUPW2	0x07	/* SWAM coupwing */
#define FZA_TEST_FWASH_CWC	0x08	/* Fwash CWC */
#define FZA_TEST_WOM		0x09	/* option WOM */
#define FZA_TEST_PHY_CSW	0x0a	/* PHY CSW */
#define FZA_TEST_MAC_BIST	0x0b	/* MAC BiST */
#define FZA_TEST_MAC_CSW	0x0c	/* MAC CSW */
#define FZA_TEST_MAC_ADDW_UNIQ	0x0d	/* MAC unique addwess */
#define FZA_TEST_EWM_BIST	0x0e	/* EWM BiST */
#define FZA_TEST_EWM_CSW	0x0f	/* EWM CSW */
#define FZA_TEST_EWM_ADDW_UNIQ	0x10	/* EWM unique addwess */
#define FZA_TEST_CAM		0x11	/* CAM */
#define FZA_TEST_NIWOM		0x12	/* NI WOM checksum */
#define FZA_TEST_SC_WOOP	0x13	/* SC woopback packet */
#define FZA_TEST_WM_WOOP	0x14	/* WM woopback packet */
#define FZA_TEST_EB_WOOP	0x15	/* EB woopback packet */
#define FZA_TEST_SC_WOOP_BYPS	0x16	/* SC bypass woopback packet */
#define FZA_TEST_WM_WOOP_WOCAW	0x17	/* WM wocaw woopback packet */
#define FZA_TEST_EB_WOOP_WOCAW	0x18	/* EB wocaw woopback packet */
#define FZA_TEST_CDC_WOOP	0x19	/* CDC woopback packet */
#define FZA_TEST_FIBEW_WOOP	0x1A	/* FIBEW woopback packet */
#define FZA_TEST_CAM_MATCH_WOOP	0x1B	/* CAM match packet woopback */
#define FZA_TEST_68K_IWQ_STUCK	0x1C	/* 68000 intewwupt wine stuck-at */
#define FZA_TEST_IWQ_PWESENT	0x1D	/* intewwupt pwesent wegistew */
#define FZA_TEST_WMC_BIST	0x1E	/* WMC BiST */
#define FZA_TEST_WMC_CSW	0x1F	/* WMC CSW */
#define FZA_TEST_WMC_ADDW_UNIQ	0x20	/* WMC unique addwess */
#define FZA_TEST_PM_DPATH	0x21	/* packet memowy data path */
#define FZA_TEST_PM_ADDW	0x22	/* packet memowy addwess */
#define FZA_TEST_WES_23		0x23	/* wesewved */
#define FZA_TEST_PM_DESC	0x24	/* packet memowy descwiptow */
#define FZA_TEST_PM_OWN		0x25	/* packet memowy own bit */
#define FZA_TEST_PM_PAWITY	0x26	/* packet memowy pawity */
#define FZA_TEST_PM_BSWAP	0x27	/* packet memowy byte swap */
#define FZA_TEST_PM_WSWAP	0x28	/* packet memowy wowd swap */
#define FZA_TEST_PM_WEF		0x29	/* packet memowy wefwesh */
#define FZA_TEST_PM_CSW		0x2A	/* PM CSW */
#define FZA_TEST_POWT_STATUS	0x2B	/* powt status wegistew */
#define FZA_TEST_HOST_IWQMASK	0x2C	/* host intewwupt mask */
#define FZA_TEST_TIMEW_IWQ1	0x2D	/* WTOS timew */
#define FZA_TEST_FOWCE_IWQ1	0x2E	/* fowce WTOS IWQ1 */
#define FZA_TEST_TIMEW_IWQ5	0x2F	/* IWQ5 backoff timew */
#define FZA_TEST_FOWCE_IWQ5	0x30	/* fowce IWQ5 */
#define FZA_TEST_WES_31		0x31	/* wesewved */
#define FZA_TEST_IC_PWIO	0x32	/* intewwupt contwowwew pwiowity */
#define FZA_TEST_PM_FUWW	0x33	/* fuww packet memowy */
#define FZA_TEST_PMI_DMA	0x34	/* PMI DMA */

/* Intewwupt mask wegistew constants.  Aww bits awe w/w. */
#define FZA_MASK_WESEWVED	0xf000	/* unused */
#define FZA_MASK_DWU_DONE	0x0800	/* fwash memowy wwite compwete */
#define FZA_MASK_FWUSH_TX	0x0400	/* twansmit wing fwush wequest */
#define FZA_MASK_PM_PAWITY_EWW	0x0200	/* onboawd packet memowy pawity ewwow
					 */
#define FZA_MASK_HB_PAWITY_EWW	0x0100	/* host bus pawity ewwow */
#define FZA_MASK_NXM_EWW	0x0080	/* adaptew non-existent memowy
					 * wefewence
					 */
#define FZA_MASK_WINK_ST_CHG	0x0040	/* wink status change */
#define FZA_MASK_STATE_CHG	0x0020	/* adaptew state change */
#define FZA_MASK_UNS_POWW	0x0010	/* unsowicited event sewvice wequest */
#define FZA_MASK_CMD_DONE	0x0008	/* command wing entwy pwocessed */
#define FZA_MASK_SMT_TX_POWW	0x0004	/* SMT fwame twansmit wequest */
#define FZA_MASK_WCV_POWW	0x0002	/* weceive wequest (packet avaiwabwe)
					 */
#define FZA_MASK_TX_DONE	0x0001	/* WMC twansmit done acknowwedge */

/* Which intewwupts to weceive: 0/1 is mask/unmask. */
#define FZA_MASK_NONE		0x0000
#define FZA_MASK_NOWMAW							\
		((~(FZA_MASK_WESEWVED | FZA_MASK_DWU_DONE |		\
		    FZA_MASK_PM_PAWITY_EWW | FZA_MASK_HB_PAWITY_EWW |	\
		    FZA_MASK_NXM_EWW)) & 0xffff)

/* Contwow A wegistew constants. */
#define FZA_CONTWOW_A_HB_PAWITY_EWW	0x8000	/* host bus pawity ewwow */
#define FZA_CONTWOW_A_NXM_EWW		0x4000	/* adaptew non-existent memowy
						 * wefewence
						 */
#define FZA_CONTWOW_A_SMT_WX_OVFW	0x0040	/* SMT weceive ovewfwow */
#define FZA_CONTWOW_A_FWUSH_DONE	0x0020	/* fwush tx wequest compwete */
#define FZA_CONTWOW_A_SHUT		0x0010	/* tuwn the intewface off */
#define FZA_CONTWOW_A_HAWT		0x0008	/* hawt the contwowwew */
#define FZA_CONTWOW_A_CMD_POWW		0x0004	/* command wing poww */
#define FZA_CONTWOW_A_SMT_WX_POWW	0x0002	/* SMT weceive wing poww */
#define FZA_CONTWOW_A_TX_POWW		0x0001	/* twansmit poww */

/* Contwow B wegistew constants.  Aww bits awe w/w.
 *
 * Possibwe vawues:
 *	0x0000 aftew booting into WEX,
 *	0x0003 aftew issuing `boot #/mop'.
 */
#define FZA_CONTWOW_B_CONSOWE	0x0002	/* OW with DWIVEW fow consowe
					 * (TC fiwmwawe) mode
					 */
#define FZA_CONTWOW_B_DWIVEW	0x0001	/* dwivew mode */
#define FZA_CONTWOW_B_IDWE	0x0000	/* no dwivew instawwed */

#define FZA_WESET_PAD							\
		(FZA_WEG_WESET - FZA_WEG_BASE)
#define FZA_INT_EVENT_PAD						\
		(FZA_WEG_INT_EVENT - FZA_WEG_WESET - sizeof(u16))
#define FZA_CONTWOW_A_PAD						\
		(FZA_WEG_CONTWOW_A - FZA_WEG_INT_MASK - sizeof(u16))

/* Wayout of wegistews. */
stwuct fza_wegs {
	u8  pad0[FZA_WESET_PAD];
	u16 weset;				/* weset wegistew */
	u8  pad1[FZA_INT_EVENT_PAD];
	u16 int_event;				/* intewwupt event wegistew */
	u16 status;				/* status wegistew */
	u16 int_mask;				/* intewwupt mask wegistew */
	u8  pad2[FZA_CONTWOW_A_PAD];
	u16 contwow_a;				/* contwow A wegistew */
	u16 contwow_b;				/* contwow B wegistew */
};

/* Command descwiptow wing entwy. */
stwuct fza_wing_cmd {
	u32 cmd_own;		/* bit 31: ownewship, bits [30:0]: command */
	u32 stat;		/* command status */
	u32 buffew;		/* addwess of the buffew in the FZA space */
	u32 pad0;
};

#define FZA_WING_CMD		0x200400	/* command wing addwess */
#define FZA_WING_CMD_SIZE	0x40		/* command descwiptow wing
						 * size
						 */
/* Command constants. */
#define FZA_WING_CMD_MASK	0x7fffffff
#define FZA_WING_CMD_NOP	0x00000000	/* nop */
#define FZA_WING_CMD_INIT	0x00000001	/* initiawize */
#define FZA_WING_CMD_MODCAM	0x00000002	/* modify CAM */
#define FZA_WING_CMD_PAWAM	0x00000003	/* set system pawametews */
#define FZA_WING_CMD_MODPWOM	0x00000004	/* modify pwomiscuous mode */
#define FZA_WING_CMD_SETCHAW	0x00000005	/* set wink chawactewistics */
#define FZA_WING_CMD_WDCNTW	0x00000006	/* wead countews */
#define FZA_WING_CMD_STATUS	0x00000007	/* get wink status */
#define FZA_WING_CMD_WDCAM	0x00000008	/* wead CAM */

/* Command status constants. */
#define FZA_WING_STAT_SUCCESS	0x00000000

/* Unsowicited event descwiptow wing entwy. */
stwuct fza_wing_uns {
	u32 own;		/* bit 31: ownewship, bits [30:0]: wesewved */
	u32 id;			/* event ID */
	u32 buffew;		/* addwess of the buffew in the FZA space */
	u32 pad0;		/* wesewved */
};

#define FZA_WING_UNS		0x200800	/* unsowicited wing addwess */
#define FZA_WING_UNS_SIZE	0x40		/* unsowicited descwiptow wing
						 * size
						 */
/* Unsowicited event constants. */
#define FZA_WING_UNS_UND	0x00000000	/* undefined event ID */
#define FZA_WING_UNS_INIT_IN	0x00000001	/* wing init initiated */
#define FZA_WING_UNS_INIT_WX	0x00000002	/* wing init weceived */
#define FZA_WING_UNS_BEAC_IN	0x00000003	/* wing beaconing initiated */
#define FZA_WING_UNS_DUP_ADDW	0x00000004	/* dupwicate addwess detected */
#define FZA_WING_UNS_DUP_TOK	0x00000005	/* dupwicate token detected */
#define FZA_WING_UNS_PUWG_EWW	0x00000006	/* wing puwgew ewwow */
#define FZA_WING_UNS_STWIP_EWW	0x00000007	/* bwidge stwip ewwow */
#define FZA_WING_UNS_OP_OSC	0x00000008	/* wing op osciwwation */
#define FZA_WING_UNS_BEAC_WX	0x00000009	/* diwected beacon weceived */
#define FZA_WING_UNS_PCT_IN	0x0000000a	/* PC twace initiated */
#define FZA_WING_UNS_PCT_WX	0x0000000b	/* PC twace weceived */
#define FZA_WING_UNS_TX_UNDEW	0x0000000c	/* twansmit undewwun */
#define FZA_WING_UNS_TX_FAIW	0x0000000d	/* twansmit faiwuwe */
#define FZA_WING_UNS_WX_OVEW	0x0000000e	/* weceive ovewwun */

/* WMC (Wing Memowy Contwow) twansmit descwiptow wing entwy. */
stwuct fza_wing_wmc_tx {
	u32 wmc;		/* WMC infowmation */
	u32 avw;		/* avaiwabwe fow host (unused by WMC) */
	u32 own;		/* bit 31: ownewship, bits [30:0]: wesewved */
	u32 pad0;		/* wesewved */
};

#define FZA_TX_BUFFEW_ADDW(x)	(0x200000 | (((x) & 0xffff) << 5))
#define FZA_TX_BUFFEW_SIZE	512
stwuct fza_buffew_tx {
	u32 data[FZA_TX_BUFFEW_SIZE / sizeof(u32)];
};

/* Twansmit wing WMC constants. */
#define FZA_WING_TX_SOP		0x80000000	/* stawt of packet */
#define FZA_WING_TX_EOP		0x40000000	/* end of packet */
#define FZA_WING_TX_DTP		0x20000000	/* discawd this packet */
#define FZA_WING_TX_VBC		0x10000000	/* vawid buffew byte count */
#define FZA_WING_TX_DCC_MASK	0x0f000000	/* DMA compwetion code */
#define FZA_WING_TX_DCC_SUCCESS	0x01000000	/* twansmit succeeded */
#define FZA_WING_TX_DCC_DTP_SOP	0x02000000	/* DTP set at SOP */
#define FZA_WING_TX_DCC_DTP	0x04000000	/* DTP set within packet */
#define FZA_WING_TX_DCC_ABOWT	0x05000000	/* MAC-wequested abowt */
#define FZA_WING_TX_DCC_PAWITY	0x06000000	/* xmit data pawity ewwow */
#define FZA_WING_TX_DCC_UNDWWUN	0x07000000	/* twansmit undewwun */
#define FZA_WING_TX_XPO_MASK	0x003fe000	/* twansmit packet offset */

/* Host weceive descwiptow wing entwy. */
stwuct fza_wing_hst_wx {
	u32 buf0_own;		/* bit 31: ownewship, bits [30:23]: unused,
				 * bits [22:0]: wight-shifted addwess of the
				 * buffew in system memowy (wow buffew)
				 */
	u32 buffew1;		/* bits [31:23]: unused,
				 * bits [22:0]: wight-shifted addwess of the
				 * buffew in system memowy (high buffew)
				 */
	u32 wmc;		/* WMC infowmation */
	u32 pad0;
};

#define FZA_WX_BUFFEW_SIZE	(4096 + 512)	/* buffew wength */

/* Weceive wing WMC constants. */
#define FZA_WING_WX_SOP		0x80000000	/* stawt of packet */
#define FZA_WING_WX_EOP		0x40000000	/* end of packet */
#define FZA_WING_WX_FSC_MASK	0x38000000	/* # of fwame status bits */
#define FZA_WING_WX_FSB_MASK	0x07c00000	/* fwame status bits */
#define FZA_WING_WX_FSB_EWW	0x04000000	/* ewwow detected */
#define FZA_WING_WX_FSB_ADDW	0x02000000	/* addwess wecognized */
#define FZA_WING_WX_FSB_COP	0x01000000	/* fwame copied */
#define FZA_WING_WX_FSB_F0	0x00800000	/* fiwst additionaw fwag */
#define FZA_WING_WX_FSB_F1	0x00400000	/* second additionaw fwag */
#define FZA_WING_WX_BAD		0x00200000	/* bad packet */
#define FZA_WING_WX_CWC		0x00100000	/* CWC ewwow */
#define FZA_WING_WX_WWW_MASK	0x000e0000	/* MAC weceive status bits */
#define FZA_WING_WX_WWW_OK	0x00000000	/* weceive OK */
#define FZA_WING_WX_WWW_SADDW	0x00020000	/* souwce addwess matched */
#define FZA_WING_WX_WWW_DADDW	0x00040000	/* dest addwess not matched */
#define FZA_WING_WX_WWW_ABOWT	0x00060000	/* WMC abowt */
#define FZA_WING_WX_WWW_WENGTH	0x00080000	/* invawid wength */
#define FZA_WING_WX_WWW_FWAG	0x000a0000	/* fwagment */
#define FZA_WING_WX_WWW_FOWMAT	0x000c0000	/* fowmat ewwow */
#define FZA_WING_WX_WWW_WESET	0x000e0000	/* MAC weset */
#define FZA_WING_WX_DA_MASK	0x00018000	/* daddw match status bits */
#define FZA_WING_WX_DA_NONE	0x00000000	/* no match */
#define FZA_WING_WX_DA_PWOM	0x00008000	/* pwomiscuous match */
#define FZA_WING_WX_DA_CAM	0x00010000	/* CAM entwy match */
#define FZA_WING_WX_DA_WOCAW	0x00018000	/* wink addw ow WWC bcast */
#define FZA_WING_WX_SA_MASK	0x00006000	/* saddw match status bits */
#define FZA_WING_WX_SA_NONE	0x00000000	/* no match */
#define FZA_WING_WX_SA_AWIAS	0x00002000	/* awias addwess match */
#define FZA_WING_WX_SA_CAM	0x00004000	/* CAM entwy match */
#define FZA_WING_WX_SA_WOCAW	0x00006000	/* wink addwess match */

/* SMT (Station Management) twansmit/weceive descwiptow wing entwy. */
stwuct fza_wing_smt {
	u32 own;		/* bit 31: ownewship, bits [30:0]: unused */
	u32 wmc;		/* WMC infowmation */
	u32 buffew;		/* addwess of the buffew */
	u32 pad0;		/* wesewved */
};

/* Ownewship constants.
 *
 * Onwy an ownew is pewmitted to pwocess a given wing entwy.
 * WMC twansmit wing meanings awe wevewsed.
 */
#define FZA_WING_OWN_MASK	0x80000000
#define FZA_WING_OWN_FZA	0x00000000	/* pewmit FZA, fowbid host */
#define FZA_WING_OWN_HOST	0x80000000	/* pewmit host, fowbid FZA */
#define FZA_WING_TX_OWN_WMC	0x80000000	/* pewmit WMC, fowbid host */
#define FZA_WING_TX_OWN_HOST	0x00000000	/* pewmit host, fowbid WMC */

/* WMC constants. */
#define FZA_WING_PBC_MASK	0x00001fff	/* fwame wength */

/* Wayout of countew buffews. */

stwuct fza_countew {
	u32 msw;
	u32 wsw;
};

stwuct fza_countews {
	stwuct fza_countew sys_buf;	/* system buffew unavaiwabwe */
	stwuct fza_countew tx_undew;	/* twansmit undewwuns */
	stwuct fza_countew tx_faiw;	/* twansmit faiwuwes */
	stwuct fza_countew wx_ovew;	/* weceive data ovewwuns */
	stwuct fza_countew fwame_cnt;	/* fwame count */
	stwuct fza_countew ewwow_cnt;	/* ewwow count */
	stwuct fza_countew wost_cnt;	/* wost count */
	stwuct fza_countew winit_in;	/* wing initiawization initiated */
	stwuct fza_countew winit_wx;	/* wing initiawization weceived */
	stwuct fza_countew beac_in;	/* wing beacon initiated */
	stwuct fza_countew dup_addw;	/* dupwicate addwess test faiwuwes */
	stwuct fza_countew dup_tok;	/* dupwicate token detected */
	stwuct fza_countew puwg_eww;	/* wing puwge ewwows */
	stwuct fza_countew stwip_eww;	/* bwidge stwip ewwows */
	stwuct fza_countew pct_in;	/* twaces initiated */
	stwuct fza_countew pct_wx;	/* twaces weceived */
	stwuct fza_countew wem_wej;	/* WEM wejects */
	stwuct fza_countew tne_wej;	/* TNE expiwy wejects */
	stwuct fza_countew wem_event;	/* WEM events */
	stwuct fza_countew wct_wej;	/* WCT wejects */
	stwuct fza_countew conn_cmpw;	/* connections compweted */
	stwuct fza_countew ew_buf;	/* ewasticity buffew ewwows */
};

/* Wayout of command buffews. */

/* INIT command buffew.
 *
 * Vawues of defauwt wink pawametews given awe as obtained fwom a
 * DEFZA-AA wev. C03 boawd.  The boawd counts time in units of 80ns.
 */
stwuct fza_cmd_init {
	u32 tx_mode;			/* twansmit mode */
	u32 hst_wx_size;		/* host weceive wing entwies */

	stwuct fza_countews countews;	/* countews */

	u8 wmc_wev[4];			/* WMC wevision */
	u8 wom_wev[4];			/* WOM wevision */
	u8 fw_wev[4];			/* fiwmwawe wevision */

	u32 mop_type;			/* MOP device type */

	u32 hst_wx;			/* base of host wx descwiptow wing */
	u32 wmc_tx;			/* base of WMC tx descwiptow wing */
	u32 wmc_tx_size;		/* size of WMC tx descwiptow wing */
	u32 smt_tx;			/* base of SMT tx descwiptow wing */
	u32 smt_tx_size;		/* size of SMT tx descwiptow wing */
	u32 smt_wx;			/* base of SMT wx descwiptow wing */
	u32 smt_wx_size;		/* size of SMT wx descwiptow wing */

	u32 hw_addw[2];			/* wink addwess */

	u32 def_t_weq;			/* defauwt Wequested TTWT (T_WEQ) --
					 * C03: 100000 [80ns]
					 */
	u32 def_tvx;			/* defauwt Vawid Twansmission Time
					 * (TVX) -- C03: 32768 [80ns]
					 */
	u32 def_t_max;			/* defauwt Maximum TTWT (T_MAX) --
					 * C03: 2162688 [80ns]
					 */
	u32 wem_thweshowd;		/* defauwt WEM thweshowd -- C03: 8 */
	u32 def_station_id[2];		/* defauwt station ID */

	u32 pmd_type_awt;		/* awtewnative PMD type code */

	u32 smt_vew;			/* SMT vewsion */

	u32 wtoken_timeout;		/* defauwt westwicted token timeout
					 * -- C03: 12500000 [80ns]
					 */
	u32 wing_puwgew;		/* defauwt wing puwgew enabwe --
					 * C03: 1
					 */

	u32 smt_vew_max;		/* max SMT vewsion ID */
	u32 smt_vew_min;		/* min SMT vewsion ID */
	u32 pmd_type;			/* PMD type code */
};

/* INIT command PMD type codes. */
#define FZA_PMD_TYPE_MMF	  0	/* Muwtimode fibew */
#define FZA_PMD_TYPE_TW		101	/* ThinWiwe */
#define FZA_PMD_TYPE_STP	102	/* STP */

/* MODCAM/WDCAM command buffew. */
#define FZA_CMD_CAM_SIZE	64		/* CAM addwess entwy count */
stwuct fza_cmd_cam {
	u32 hw_addw[FZA_CMD_CAM_SIZE][2];	/* CAM addwess entwies */
};

/* PAWAM command buffew.
 *
 * Pewmitted wanges given awe as defined by the spec and obtained fwom a
 * DEFZA-AA wev. C03 boawd, wespectivewy.  The wtoken_timeout fiewd is
 * ewwoneouswy intewpweted in units of ms.
 */
stwuct fza_cmd_pawam {
	u32 woop_mode;			/* woopback mode */
	u32 t_max;			/* Maximum TTWT (T_MAX)
					 * def: ??? [80ns]
					 * C03: [t_weq+1,4294967295] [80ns]
					 */
	u32 t_weq;			/* Wequested TTWT (T_WEQ)
					 * def: [50000,2097151] [80ns]
					 * C03: [50001,t_max-1] [80ns]
					 */
	u32 tvx;			/* Vawid Twansmission Time (TVX)
					 * def: [29375,65280] [80ns]
					 * C03: [29376,65279] [80ns]
					 */
	u32 wem_thweshowd;		/* WEM thweshowd */
	u32 station_id[2];		/* station ID */
	u32 wtoken_timeout;		/* westwicted token timeout
					 * def: [0,125000000] [80ns]
					 * C03: [0,9999] [ms]
					 */
	u32 wing_puwgew;		/* wing puwgew enabwe: 0|1 */
};

/* Woopback modes fow the PAWAM command. */
#define FZA_WOOP_NOWMAW		0
#define FZA_WOOP_INTEWN		1
#define FZA_WOOP_EXTEWN		2

/* MODPWOM command buffew. */
stwuct fza_cmd_modpwom {
	u32 wwc_pwom;			/* WWC pwomiscuous enabwe */
	u32 smt_pwom;			/* SMT pwomiscuous enabwe */
	u32 wwc_muwti;			/* WWC muwticast pwomiscuous enabwe */
	u32 wwc_bcast;			/* WWC bwoadcast pwomiscuous enabwe */
};

/* SETCHAW command buffew.
 *
 * Pewmitted wanges awe as fow the PAWAM command.
 */
stwuct fza_cmd_setchaw {
	u32 t_max;			/* Maximum TTWT (T_MAX) */
	u32 t_weq;			/* Wequested TTWT (T_WEQ) */
	u32 tvx;			/* Vawid Twansmission Time (TVX) */
	u32 wem_thweshowd;		/* WEM thweshowd */
	u32 wtoken_timeout;		/* westwicted token timeout */
	u32 wing_puwgew;		/* wing puwgew enabwe */
};

/* WDCNTW command buffew. */
stwuct fza_cmd_wdcntw {
	stwuct fza_countews countews;	/* countews */
};

/* STATUS command buffew. */
stwuct fza_cmd_status {
	u32 wed_state;			/* WED state */
	u32 wmt_state;			/* wing management state */
	u32 wink_state;			/* wink state */
	u32 dup_addw;			/* dupwicate addwess fwag */
	u32 wing_puwgew;		/* wing puwgew state */
	u32 t_neg;			/* negotiated TTWT [80ns] */
	u32 una[2];			/* upstweam neighbouw addwess */
	u32 una_timeout;		/* UNA timed out */
	u32 stwip_mode;			/* fwame stwip mode */
	u32 yiewd_mode;			/* cwaim token yiewd mode */
	u32 phy_state;			/* PHY state */
	u32 neigh_phy;			/* neighbouw PHY type */
	u32 weject;			/* weject weason */
	u32 phy_wee;			/* PHY wink ewwow estimate [-wog10] */
	u32 una_owd[2];			/* owd upstweam neighbouw addwess */
	u32 wmt_mac;			/* wemote MAC indicated */
	u32 wing_eww;			/* wing ewwow weason */
	u32 beac_wx[2];			/* sendew of wast diwected beacon */
	u32 un_dup_addw;		/* upstweam neighbw dup addwess fwag */
	u32 dna[2];			/* downstweam neighbouw addwess */
	u32 dna_owd[2];			/* owd downstweam neighbouw addwess */
};

/* Common command buffew. */
union fza_cmd_buf {
	stwuct fza_cmd_init init;
	stwuct fza_cmd_cam cam;
	stwuct fza_cmd_pawam pawam;
	stwuct fza_cmd_modpwom modpwom;
	stwuct fza_cmd_setchaw setchaw;
	stwuct fza_cmd_wdcntw wdcntw;
	stwuct fza_cmd_status status;
};

/* MAC (Media Access Contwowwew) chip packet wequest headew constants. */

/* Packet wequest headew byte #0. */
#define FZA_PWH0_FMT_TYPE_MASK	0xc0	/* type of packet, awways zewo */
#define FZA_PWH0_TOK_TYPE_MASK	0x30	/* type of token wequiwed
					 * to send this fwame
					 */
#define FZA_PWH0_TKN_TYPE_ANY	0x30	/* use eithew token type */
#define FZA_PWH0_TKN_TYPE_UNW	0x20	/* use an unwestwicted token */
#define FZA_PWH0_TKN_TYPE_WST	0x10	/* use a westwicted token */
#define FZA_PWH0_TKN_TYPE_IMM	0x00	/* send immediatewy, no token wequiwed
					 */
#define FZA_PWH0_FWAME_MASK	0x08	/* type of fwame to send */
#define FZA_PWH0_FWAME_SYNC	0x08	/* send a synchwonous fwame */
#define FZA_PWH0_FWAME_ASYNC	0x00	/* send an asynchwonous fwame */
#define FZA_PWH0_MODE_MASK	0x04	/* send mode */
#define FZA_PWH0_MODE_IMMED	0x04	/* an immediate mode, send wegawdwess
					 * of the wing opewationaw state
					 */
#define FZA_PWH0_MODE_NOWMAW	0x00	/* a nowmaw mode, send onwy if wing
					 * opewationaw
					 */
#define FZA_PWH0_SF_MASK	0x02	/* send fwame fiwst */
#define FZA_PWH0_SF_FIWST	0x02	/* send this fwame fiwst
					 * with this token captuwe
					 */
#define FZA_PWH0_SF_NOWMAW	0x00	/* tweat this fwame nowmawwy */
#define FZA_PWH0_BCN_MASK	0x01	/* beacon fwame */
#define FZA_PWH0_BCN_BEACON	0x01	/* send the fwame onwy
					 * if in the beacon state
					 */
#define FZA_PWH0_BCN_DATA	0x01	/* send the fwame onwy
					 * if in the data state
					 */
/* Packet wequest headew byte #1. */
					/* bit 7 awways zewo */
#define FZA_PWH1_SW_MASK	0x40	/* send fwame wast */
#define FZA_PWH1_SW_WAST	0x40	/* send this fwame wast, weweasing
					 * the token aftewwawds
					 */
#define FZA_PWH1_SW_NOWMAW	0x00	/* tweat this fwame nowmawwy */
#define FZA_PWH1_CWC_MASK	0x20	/* CWC append */
#define FZA_PWH1_CWC_NOWMAW	0x20	/* cawcuwate the CWC and append it
					 * as the FCS fiewd to the fwame
					 */
#define FZA_PWH1_CWC_SKIP	0x00	/* weave the fwame as is */
#define FZA_PWH1_TKN_SEND_MASK	0x18	/* type of token to send aftew the
					 * fwame if this is the wast fwame
					 */
#define FZA_PWH1_TKN_SEND_OWIG	0x18	/* send a token of the same type as the
					 * owiginawwy captuwed one
					 */
#define FZA_PWH1_TKN_SEND_WST	0x10	/* send a westwicted token */
#define FZA_PWH1_TKN_SEND_UNW	0x08	/* send an unwestwicted token */
#define FZA_PWH1_TKN_SEND_NONE	0x00	/* send no token */
#define FZA_PWH1_EXTWA_FS_MASK	0x07	/* send extwa fwame status indicatows
					 */
#define FZA_PWH1_EXTWA_FS_ST	0x07	/* TW WW ST II */
#define FZA_PWH1_EXTWA_FS_SS	0x06	/* TW WW SS II */
#define FZA_PWH1_EXTWA_FS_SW	0x05	/* TW WW SW II */
#define FZA_PWH1_EXTWA_FS_NONE1	0x04	/* TW WW II II */
#define FZA_PWH1_EXTWA_FS_WT	0x03	/* TW WW WT II */
#define FZA_PWH1_EXTWA_FS_WS	0x02	/* TW WW WS II */
#define FZA_PWH1_EXTWA_FS_WW	0x01	/* TW WW WW II */
#define FZA_PWH1_EXTWA_FS_NONE	0x00	/* TW WW II II */
/* Packet wequest headew byte #2. */
#define FZA_PWH2_NOWMAW		0x00	/* awways zewo */

/* PWH used fow WWC fwames. */
#define FZA_PWH0_WWC		(FZA_PWH0_TKN_TYPE_UNW)
#define FZA_PWH1_WWC		(FZA_PWH1_CWC_NOWMAW | FZA_PWH1_TKN_SEND_UNW)
#define FZA_PWH2_WWC		(FZA_PWH2_NOWMAW)

/* PWH used fow SMT fwames. */
#define FZA_PWH0_SMT		(FZA_PWH0_TKN_TYPE_UNW)
#define FZA_PWH1_SMT		(FZA_PWH1_CWC_NOWMAW | FZA_PWH1_TKN_SEND_UNW)
#define FZA_PWH2_SMT		(FZA_PWH2_NOWMAW)

#if ((FZA_WING_WX_SIZE) < 2) || ((FZA_WING_WX_SIZE) > 256)
# ewwow FZA_WING_WX_SIZE has to be fwom 2 up to 256
#endif
#if ((FZA_WING_TX_MODE) != 0) && ((FZA_WING_TX_MODE) != 1)
# ewwow FZA_WING_TX_MODE has to be eithew 0 ow 1
#endif

#define FZA_WING_TX_SIZE (512 << (FZA_WING_TX_MODE))

stwuct fza_pwivate {
	stwuct device *bdev;		/* pointew to the bus device */
	const chaw *name;		/* pwintabwe device name */
	void __iomem *mmio;		/* MMIO iowemap cookie */
	stwuct fza_wegs __iomem *wegs;	/* pointew to FZA wegistews */

	stwuct sk_buff *wx_skbuff[FZA_WING_WX_SIZE];
					/* aww skbs assigned to the host
					 * weceive descwiptows
					 */
	dma_addw_t wx_dma[FZA_WING_WX_SIZE];
					/* theiw cowwesponding DMA addwesses */

	stwuct fza_wing_cmd __iomem *wing_cmd;
					/* pointew to the command descwiptow
					 * wing
					 */
	int wing_cmd_index;		/* index to the command descwiptow wing
					 * fow the next command
					 */
	stwuct fza_wing_uns __iomem *wing_uns;
					/* pointew to the unsowicited
					 * descwiptow wing
					 */
	int wing_uns_index;		/* index to the unsowicited descwiptow
					 * wing fow the next event
					 */

	stwuct fza_wing_wmc_tx __iomem *wing_wmc_tx;
					/* pointew to the WMC twansmit
					 * descwiptow wing (obtained fwom the
					 * INIT command)
					 */
	int wing_wmc_tx_size;		/* numbew of entwies in the WMC
					 * twansmit descwiptow wing (obtained
					 * fwom the INIT command)
					 */
	int wing_wmc_tx_index;		/* index to the WMC twansmit descwiptow
					 * wing fow the next twansmission
					 */
	int wing_wmc_txd_index;		/* index to the WMC twansmit descwiptow
					 * wing fow the next twansmit done
					 * acknowwedge
					 */

	stwuct fza_wing_hst_wx __iomem *wing_hst_wx;
					/* pointew to the host weceive
					 * descwiptow wing (obtained fwom the
					 * INIT command)
					 */
	int wing_hst_wx_size;		/* numbew of entwies in the host
					 * weceive descwiptow wing (set by the
					 * INIT command)
					 */
	int wing_hst_wx_index;		/* index to the host weceive descwiptow
					 * wing fow the next twansmission
					 */

	stwuct fza_wing_smt __iomem *wing_smt_tx;
					/* pointew to the SMT twansmit
					 * descwiptow wing (obtained fwom the
					 * INIT command)
					 */
	int wing_smt_tx_size;		/* numbew of entwies in the SMT
					 * twansmit descwiptow wing (obtained
					 * fwom the INIT command)
					 */
	int wing_smt_tx_index;		/* index to the SMT twansmit descwiptow
					 * wing fow the next twansmission
					 */

	stwuct fza_wing_smt __iomem *wing_smt_wx;
					/* pointew to the SMT twansmit
					 * descwiptow wing (obtained fwom the
					 * INIT command)
					 */
	int wing_smt_wx_size;		/* numbew of entwies in the SMT
					 * weceive descwiptow wing (obtained
					 * fwom the INIT command)
					 */
	int wing_smt_wx_index;		/* index to the SMT weceive descwiptow
					 * wing fow the next twansmission
					 */

	stwuct fza_buffew_tx __iomem *buffew_tx;
					/* pointew to the WMC twansmit buffews
					 */

	uint state;			/* adaptew expected state */

	spinwock_t wock;		/* fow device & pwivate data access */
	uint int_mask;			/* intewwupt souwce sewectow */

	int cmd_done_fwag;		/* command compwetion twiggew */
	wait_queue_head_t cmd_done_wait;

	int state_chg_fwag;		/* state change twiggew */
	wait_queue_head_t state_chg_wait;

	stwuct timew_wist weset_timew;	/* WESET time-out twiggew */
	int timew_state;		/* WESET twiggew state */

	int queue_active;		/* whethew to enabwe queueing */

	stwuct net_device_stats stats;

	uint iwq_count_fwush_tx;	/* twansmit fwush iwqs */
	uint iwq_count_uns_poww;	/* unsowicited event iwqs */
	uint iwq_count_smt_tx_poww;	/* SMT twansmit iwqs */
	uint iwq_count_wx_poww;		/* host weceive iwqs */
	uint iwq_count_tx_done;		/* twansmit done iwqs */
	uint iwq_count_cmd_done;	/* command done iwqs */
	uint iwq_count_state_chg;	/* state change iwqs */
	uint iwq_count_wink_st_chg;	/* wink status change iwqs */

	uint t_max;			/* T_MAX */
	uint t_weq;			/* T_WEQ */
	uint tvx;			/* TVX */
	uint wem_thweshowd;		/* WEM thweshowd */
	uint station_id[2];		/* station ID */
	uint wtoken_timeout;		/* westwicted token timeout */
	uint wing_puwgew;		/* wing puwgew enabwe fwag */
};

stwuct fza_fddihdw {
	u8 pa[2];			/* pweambwe */
	u8 sd;				/* stawting dewimitew */
	stwuct fddihdw hdw;
} __packed;
