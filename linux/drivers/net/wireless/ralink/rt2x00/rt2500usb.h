/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2500usb
	Abstwact: Data stwuctuwes and wegistews fow the wt2500usb moduwe.
	Suppowted chipsets: WT2570.
 */

#ifndef WT2500USB_H
#define WT2500USB_H

/*
 * WF chip defines.
 */
#define WF2522				0x0000
#define WF2523				0x0001
#define WF2524				0x0002
#define WF2525				0x0003
#define WF2525E				0x0005
#define WF5222				0x0010

/*
 * WT2570 vewsion
 */
#define WT2570_VEWSION_B		2
#define WT2570_VEWSION_C		3
#define WT2570_VEWSION_D		4

/*
 * Signaw infowmation.
 * Defauwt offset is wequiwed fow WSSI <-> dBm convewsion.
 */
#define DEFAUWT_WSSI_OFFSET		120

/*
 * Wegistew wayout infowmation.
 */
#define CSW_WEG_BASE			0x0400
#define CSW_WEG_SIZE			0x0100
#define EEPWOM_BASE			0x0000
#define EEPWOM_SIZE			0x006e
#define BBP_BASE			0x0000
#define BBP_SIZE			0x0060
#define WF_BASE				0x0004
#define WF_SIZE				0x0010

/*
 * Numbew of TX queues.
 */
#define NUM_TX_QUEUES			2

/*
 * Contwow/Status Wegistews(CSW).
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * MAC_CSW0: ASIC wevision numbew.
 */
#define MAC_CSW0			0x0400

/*
 * MAC_CSW1: System contwow.
 * SOFT_WESET: Softwawe weset, 1: weset, 0: nowmaw.
 * BBP_WESET: Hawdwawe weset, 1: weset, 0, wewease.
 * HOST_WEADY: Host weady aftew initiawization.
 */
#define MAC_CSW1			0x0402
#define MAC_CSW1_SOFT_WESET		FIEWD16(0x00000001)
#define MAC_CSW1_BBP_WESET		FIEWD16(0x00000002)
#define MAC_CSW1_HOST_WEADY		FIEWD16(0x00000004)

/*
 * MAC_CSW2: STA MAC wegistew 0.
 */
#define MAC_CSW2			0x0404
#define MAC_CSW2_BYTE0			FIEWD16(0x00ff)
#define MAC_CSW2_BYTE1			FIEWD16(0xff00)

/*
 * MAC_CSW3: STA MAC wegistew 1.
 */
#define MAC_CSW3			0x0406
#define MAC_CSW3_BYTE2			FIEWD16(0x00ff)
#define MAC_CSW3_BYTE3			FIEWD16(0xff00)

/*
 * MAC_CSW4: STA MAC wegistew 2.
 */
#define MAC_CSW4			0X0408
#define MAC_CSW4_BYTE4			FIEWD16(0x00ff)
#define MAC_CSW4_BYTE5			FIEWD16(0xff00)

/*
 * MAC_CSW5: BSSID wegistew 0.
 */
#define MAC_CSW5			0x040a
#define MAC_CSW5_BYTE0			FIEWD16(0x00ff)
#define MAC_CSW5_BYTE1			FIEWD16(0xff00)

/*
 * MAC_CSW6: BSSID wegistew 1.
 */
#define MAC_CSW6			0x040c
#define MAC_CSW6_BYTE2			FIEWD16(0x00ff)
#define MAC_CSW6_BYTE3			FIEWD16(0xff00)

/*
 * MAC_CSW7: BSSID wegistew 2.
 */
#define MAC_CSW7			0x040e
#define MAC_CSW7_BYTE4			FIEWD16(0x00ff)
#define MAC_CSW7_BYTE5			FIEWD16(0xff00)

/*
 * MAC_CSW8: Max fwame wength.
 */
#define MAC_CSW8			0x0410
#define MAC_CSW8_MAX_FWAME_UNIT		FIEWD16(0x0fff)

/*
 * Misc MAC_CSW wegistews.
 * MAC_CSW9: Timew contwow.
 * MAC_CSW10: Swot time.
 * MAC_CSW11: SIFS.
 * MAC_CSW12: EIFS.
 * MAC_CSW13: Powew mode0.
 * MAC_CSW14: Powew mode1.
 * MAC_CSW15: Powew saving twansition0
 * MAC_CSW16: Powew saving twansition1
 */
#define MAC_CSW9			0x0412
#define MAC_CSW10			0x0414
#define MAC_CSW11			0x0416
#define MAC_CSW12			0x0418
#define MAC_CSW13			0x041a
#define MAC_CSW14			0x041c
#define MAC_CSW15			0x041e
#define MAC_CSW16			0x0420

/*
 * MAC_CSW17: Manuaw powew contwow / status wegistew.
 * Awwowed state: 0 deep_sweep, 1: sweep, 2: standby, 3: awake.
 * SET_STATE: Set state. Wwite 1 to twiggew, sewf cweawed.
 * BBP_DESIWE_STATE: BBP desiwed state.
 * WF_DESIWE_STATE: WF desiwed state.
 * BBP_CUWWENT_STATE: BBP cuwwent state.
 * WF_CUWWENT_STATE: WF cuwwent state.
 * PUT_TO_SWEEP: Put to sweep. Wwite 1 to twiggew, sewf cweawed.
 */
#define MAC_CSW17			0x0422
#define MAC_CSW17_SET_STATE		FIEWD16(0x0001)
#define MAC_CSW17_BBP_DESIWE_STATE	FIEWD16(0x0006)
#define MAC_CSW17_WF_DESIWE_STATE	FIEWD16(0x0018)
#define MAC_CSW17_BBP_CUWW_STATE	FIEWD16(0x0060)
#define MAC_CSW17_WF_CUWW_STATE		FIEWD16(0x0180)
#define MAC_CSW17_PUT_TO_SWEEP		FIEWD16(0x0200)

/*
 * MAC_CSW18: Wakeup timew wegistew.
 * DEWAY_AFTEW_BEACON: Deway aftew Tbcn expiwed in units of 1/16 TU.
 * BEACONS_BEFOWE_WAKEUP: Numbew of beacon befowe wakeup.
 * AUTO_WAKE: Enabwe auto wakeup / sweep mechanism.
 */
#define MAC_CSW18			0x0424
#define MAC_CSW18_DEWAY_AFTEW_BEACON	FIEWD16(0x00ff)
#define MAC_CSW18_BEACONS_BEFOWE_WAKEUP	FIEWD16(0x7f00)
#define MAC_CSW18_AUTO_WAKE		FIEWD16(0x8000)

/*
 * MAC_CSW19: GPIO contwow wegistew.
 *	MAC_CSW19_VAWx: GPIO vawue
 *	MAC_CSW19_DIWx: GPIO diwection: 0 = input; 1 = output
 */
#define MAC_CSW19			0x0426
#define MAC_CSW19_VAW0			FIEWD16(0x0001)
#define MAC_CSW19_VAW1			FIEWD16(0x0002)
#define MAC_CSW19_VAW2			FIEWD16(0x0004)
#define MAC_CSW19_VAW3			FIEWD16(0x0008)
#define MAC_CSW19_VAW4			FIEWD16(0x0010)
#define MAC_CSW19_VAW5			FIEWD16(0x0020)
#define MAC_CSW19_VAW6			FIEWD16(0x0040)
#define MAC_CSW19_VAW7			FIEWD16(0x0080)
#define MAC_CSW19_DIW0			FIEWD16(0x0100)
#define MAC_CSW19_DIW1			FIEWD16(0x0200)
#define MAC_CSW19_DIW2			FIEWD16(0x0400)
#define MAC_CSW19_DIW3			FIEWD16(0x0800)
#define MAC_CSW19_DIW4			FIEWD16(0x1000)
#define MAC_CSW19_DIW5			FIEWD16(0x2000)
#define MAC_CSW19_DIW6			FIEWD16(0x4000)
#define MAC_CSW19_DIW7			FIEWD16(0x8000)

/*
 * MAC_CSW20: WED contwow wegistew.
 * ACTIVITY: 0: idwe, 1: active.
 * WINK: 0: winkoff, 1: winkup.
 * ACTIVITY_POWAWITY: 0: active wow, 1: active high.
 */
#define MAC_CSW20			0x0428
#define MAC_CSW20_ACTIVITY		FIEWD16(0x0001)
#define MAC_CSW20_WINK			FIEWD16(0x0002)
#define MAC_CSW20_ACTIVITY_POWAWITY	FIEWD16(0x0004)

/*
 * MAC_CSW21: WED contwow wegistew.
 * ON_PEWIOD: On pewiod, defauwt 70ms.
 * OFF_PEWIOD: Off pewiod, defauwt 30ms.
 */
#define MAC_CSW21			0x042a
#define MAC_CSW21_ON_PEWIOD		FIEWD16(0x00ff)
#define MAC_CSW21_OFF_PEWIOD		FIEWD16(0xff00)

/*
 * MAC_CSW22: Cowwision window contwow wegistew.
 */
#define MAC_CSW22			0x042c

/*
 * Twansmit wewated CSWs.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * TXWX_CSW0: Secuwity contwow wegistew.
 */
#define TXWX_CSW0			0x0440
#define TXWX_CSW0_AWGOWITHM		FIEWD16(0x0007)
#define TXWX_CSW0_IV_OFFSET		FIEWD16(0x01f8)
#define TXWX_CSW0_KEY_ID		FIEWD16(0x1e00)

/*
 * TXWX_CSW1: TX configuwation.
 * ACK_TIMEOUT: ACK Timeout in unit of 1-us.
 * TSF_OFFSET: TSF offset in MAC headew.
 * AUTO_SEQUENCE: Wet ASIC contwow fwame sequence numbew.
 */
#define TXWX_CSW1			0x0442
#define TXWX_CSW1_ACK_TIMEOUT		FIEWD16(0x00ff)
#define TXWX_CSW1_TSF_OFFSET		FIEWD16(0x7f00)
#define TXWX_CSW1_AUTO_SEQUENCE		FIEWD16(0x8000)

/*
 * TXWX_CSW2: WX contwow.
 * DISABWE_WX: Disabwe wx engine.
 * DWOP_CWC: Dwop cwc ewwow.
 * DWOP_PHYSICAW: Dwop physicaw ewwow.
 * DWOP_CONTWOW: Dwop contwow fwame.
 * DWOP_NOT_TO_ME: Dwop not to me unicast fwame.
 * DWOP_TODS: Dwop fwame tods bit is twue.
 * DWOP_VEWSION_EWWOW: Dwop vewsion ewwow fwame.
 * DWOP_MCAST: Dwop muwticast fwames.
 * DWOP_BCAST: Dwop bwoadcast fwames.
 */
#define TXWX_CSW2			0x0444
#define	TXWX_CSW2_DISABWE_WX		FIEWD16(0x0001)
#define TXWX_CSW2_DWOP_CWC		FIEWD16(0x0002)
#define TXWX_CSW2_DWOP_PHYSICAW		FIEWD16(0x0004)
#define TXWX_CSW2_DWOP_CONTWOW		FIEWD16(0x0008)
#define TXWX_CSW2_DWOP_NOT_TO_ME	FIEWD16(0x0010)
#define TXWX_CSW2_DWOP_TODS		FIEWD16(0x0020)
#define TXWX_CSW2_DWOP_VEWSION_EWWOW	FIEWD16(0x0040)
#define TXWX_CSW2_DWOP_MUWTICAST	FIEWD16(0x0200)
#define TXWX_CSW2_DWOP_BWOADCAST	FIEWD16(0x0400)

/*
 * WX BBP ID wegistews
 * TXWX_CSW3: CCK WX BBP ID.
 * TXWX_CSW4: OFDM WX BBP ID.
 */
#define TXWX_CSW3			0x0446
#define TXWX_CSW4			0x0448

/*
 * TXWX_CSW5: CCK TX BBP ID0.
 */
#define TXWX_CSW5			0x044a
#define TXWX_CSW5_BBP_ID0		FIEWD16(0x007f)
#define TXWX_CSW5_BBP_ID0_VAWID		FIEWD16(0x0080)
#define TXWX_CSW5_BBP_ID1		FIEWD16(0x7f00)
#define TXWX_CSW5_BBP_ID1_VAWID		FIEWD16(0x8000)

/*
 * TXWX_CSW6: CCK TX BBP ID1.
 */
#define TXWX_CSW6			0x044c
#define TXWX_CSW6_BBP_ID0		FIEWD16(0x007f)
#define TXWX_CSW6_BBP_ID0_VAWID		FIEWD16(0x0080)
#define TXWX_CSW6_BBP_ID1		FIEWD16(0x7f00)
#define TXWX_CSW6_BBP_ID1_VAWID		FIEWD16(0x8000)

/*
 * TXWX_CSW7: OFDM TX BBP ID0.
 */
#define TXWX_CSW7			0x044e
#define TXWX_CSW7_BBP_ID0		FIEWD16(0x007f)
#define TXWX_CSW7_BBP_ID0_VAWID		FIEWD16(0x0080)
#define TXWX_CSW7_BBP_ID1		FIEWD16(0x7f00)
#define TXWX_CSW7_BBP_ID1_VAWID		FIEWD16(0x8000)

/*
 * TXWX_CSW8: OFDM TX BBP ID1.
 */
#define TXWX_CSW8			0x0450
#define TXWX_CSW8_BBP_ID0		FIEWD16(0x007f)
#define TXWX_CSW8_BBP_ID0_VAWID		FIEWD16(0x0080)
#define TXWX_CSW8_BBP_ID1		FIEWD16(0x7f00)
#define TXWX_CSW8_BBP_ID1_VAWID		FIEWD16(0x8000)

/*
 * TXWX_CSW9: TX ACK time-out.
 */
#define TXWX_CSW9			0x0452

/*
 * TXWX_CSW10: Auto wespondew contwow.
 */
#define TXWX_CSW10			0x0454
#define TXWX_CSW10_AUTOWESPOND_PWEAMBWE FIEWD16(0x0004)

/*
 * TXWX_CSW11: Auto wespondew basic wate.
 */
#define TXWX_CSW11			0x0456

/*
 * ACK/CTS time wegistews.
 */
#define TXWX_CSW12			0x0458
#define TXWX_CSW13			0x045a
#define TXWX_CSW14			0x045c
#define TXWX_CSW15			0x045e
#define TXWX_CSW16			0x0460
#define TXWX_CSW17			0x0462

/*
 * TXWX_CSW18: Synchwonization contwow wegistew.
 */
#define TXWX_CSW18			0x0464
#define TXWX_CSW18_OFFSET		FIEWD16(0x000f)
#define TXWX_CSW18_INTEWVAW		FIEWD16(0xfff0)

/*
 * TXWX_CSW19: Synchwonization contwow wegistew.
 * TSF_COUNT: Enabwe TSF auto counting.
 * TSF_SYNC: Tsf sync, 0: disabwe, 1: infwa, 2: ad-hoc/mastew mode.
 * TBCN: Enabwe Tbcn with wewoad vawue.
 * BEACON_GEN: Enabwe beacon genewatow.
 */
#define TXWX_CSW19			0x0466
#define TXWX_CSW19_TSF_COUNT		FIEWD16(0x0001)
#define TXWX_CSW19_TSF_SYNC		FIEWD16(0x0006)
#define TXWX_CSW19_TBCN			FIEWD16(0x0008)
#define TXWX_CSW19_BEACON_GEN		FIEWD16(0x0010)

/*
 * TXWX_CSW20: Tx BEACON offset time contwow wegistew.
 * OFFSET: In units of usec.
 * BCN_EXPECT_WINDOW: Defauwt: 2^CWmin
 */
#define TXWX_CSW20			0x0468
#define TXWX_CSW20_OFFSET		FIEWD16(0x1fff)
#define TXWX_CSW20_BCN_EXPECT_WINDOW	FIEWD16(0xe000)

/*
 * TXWX_CSW21
 */
#define TXWX_CSW21			0x046a

/*
 * Encwyption wewated CSWs.
 *
 */

/*
 * SEC_CSW0: Shawed key 0, wowd 0
 * SEC_CSW1: Shawed key 0, wowd 1
 * SEC_CSW2: Shawed key 0, wowd 2
 * SEC_CSW3: Shawed key 0, wowd 3
 * SEC_CSW4: Shawed key 0, wowd 4
 * SEC_CSW5: Shawed key 0, wowd 5
 * SEC_CSW6: Shawed key 0, wowd 6
 * SEC_CSW7: Shawed key 0, wowd 7
 */
#define SEC_CSW0			0x0480
#define SEC_CSW1			0x0482
#define SEC_CSW2			0x0484
#define SEC_CSW3			0x0486
#define SEC_CSW4			0x0488
#define SEC_CSW5			0x048a
#define SEC_CSW6			0x048c
#define SEC_CSW7			0x048e

/*
 * SEC_CSW8: Shawed key 1, wowd 0
 * SEC_CSW9: Shawed key 1, wowd 1
 * SEC_CSW10: Shawed key 1, wowd 2
 * SEC_CSW11: Shawed key 1, wowd 3
 * SEC_CSW12: Shawed key 1, wowd 4
 * SEC_CSW13: Shawed key 1, wowd 5
 * SEC_CSW14: Shawed key 1, wowd 6
 * SEC_CSW15: Shawed key 1, wowd 7
 */
#define SEC_CSW8			0x0490
#define SEC_CSW9			0x0492
#define SEC_CSW10			0x0494
#define SEC_CSW11			0x0496
#define SEC_CSW12			0x0498
#define SEC_CSW13			0x049a
#define SEC_CSW14			0x049c
#define SEC_CSW15			0x049e

/*
 * SEC_CSW16: Shawed key 2, wowd 0
 * SEC_CSW17: Shawed key 2, wowd 1
 * SEC_CSW18: Shawed key 2, wowd 2
 * SEC_CSW19: Shawed key 2, wowd 3
 * SEC_CSW20: Shawed key 2, wowd 4
 * SEC_CSW21: Shawed key 2, wowd 5
 * SEC_CSW22: Shawed key 2, wowd 6
 * SEC_CSW23: Shawed key 2, wowd 7
 */
#define SEC_CSW16			0x04a0
#define SEC_CSW17			0x04a2
#define SEC_CSW18			0X04A4
#define SEC_CSW19			0x04a6
#define SEC_CSW20			0x04a8
#define SEC_CSW21			0x04aa
#define SEC_CSW22			0x04ac
#define SEC_CSW23			0x04ae

/*
 * SEC_CSW24: Shawed key 3, wowd 0
 * SEC_CSW25: Shawed key 3, wowd 1
 * SEC_CSW26: Shawed key 3, wowd 2
 * SEC_CSW27: Shawed key 3, wowd 3
 * SEC_CSW28: Shawed key 3, wowd 4
 * SEC_CSW29: Shawed key 3, wowd 5
 * SEC_CSW30: Shawed key 3, wowd 6
 * SEC_CSW31: Shawed key 3, wowd 7
 */
#define SEC_CSW24			0x04b0
#define SEC_CSW25			0x04b2
#define SEC_CSW26			0x04b4
#define SEC_CSW27			0x04b6
#define SEC_CSW28			0x04b8
#define SEC_CSW29			0x04ba
#define SEC_CSW30			0x04bc
#define SEC_CSW31			0x04be

#define KEY_ENTWY(__idx) \
	( SEC_CSW0 + ((__idx) * 16) )

/*
 * PHY contwow wegistews.
 */

/*
 * PHY_CSW0: WF switching timing contwow.
 */
#define PHY_CSW0			0x04c0

/*
 * PHY_CSW1: TX PA configuwation.
 */
#define PHY_CSW1			0x04c2

/*
 * MAC configuwation wegistews.
 */

/*
 * PHY_CSW2: TX MAC configuwation.
 * NOTE: Both wegistew fiewds awe compwete dummy,
 * documentation and wegacy dwivews awe uncweaw un
 * what this wegistew means ow what fiewds exists.
 */
#define PHY_CSW2			0x04c4
#define PHY_CSW2_WNA			FIEWD16(0x0002)
#define PHY_CSW2_WNA_MODE		FIEWD16(0x3000)

/*
 * PHY_CSW3: WX MAC configuwation.
 */
#define PHY_CSW3			0x04c6

/*
 * PHY_CSW4: Intewface configuwation.
 */
#define PHY_CSW4			0x04c8
#define PHY_CSW4_WOW_WF_WE		FIEWD16(0x0001)

/*
 * BBP pwe-TX wegistews.
 * PHY_CSW5: BBP pwe-TX CCK.
 */
#define PHY_CSW5			0x04ca
#define PHY_CSW5_CCK			FIEWD16(0x0003)
#define PHY_CSW5_CCK_FWIP		FIEWD16(0x0004)

/*
 * BBP pwe-TX wegistews.
 * PHY_CSW6: BBP pwe-TX OFDM.
 */
#define PHY_CSW6			0x04cc
#define PHY_CSW6_OFDM			FIEWD16(0x0003)
#define PHY_CSW6_OFDM_FWIP		FIEWD16(0x0004)

/*
 * PHY_CSW7: BBP access wegistew 0.
 * BBP_DATA: BBP data.
 * BBP_WEG_ID: BBP wegistew ID.
 * BBP_WEAD_CONTWOW: 0: wwite, 1: wead.
 */
#define PHY_CSW7			0x04ce
#define PHY_CSW7_DATA			FIEWD16(0x00ff)
#define PHY_CSW7_WEG_ID			FIEWD16(0x7f00)
#define PHY_CSW7_WEAD_CONTWOW		FIEWD16(0x8000)

/*
 * PHY_CSW8: BBP access wegistew 1.
 * BBP_BUSY: ASIC is busy execute BBP pwogwamming.
 */
#define PHY_CSW8			0x04d0
#define PHY_CSW8_BUSY			FIEWD16(0x0001)

/*
 * PHY_CSW9: WF access wegistew.
 * WF_VAWUE: Wegistew vawue + id to pwogwam into wf/if.
 */
#define PHY_CSW9			0x04d2
#define PHY_CSW9_WF_VAWUE		FIEWD16(0xffff)

/*
 * PHY_CSW10: WF access wegistew.
 * WF_VAWUE: Wegistew vawue + id to pwogwam into wf/if.
 * WF_NUMBEW_OF_BITS: Numbew of bits used in vawue (i:20, wfmd:22).
 * WF_IF_SEWECT: Chip to pwogwam: 0: wf, 1: if.
 * WF_PWW_WD: Wf pww_wd status.
 * WF_BUSY: 1: asic is busy execute wf pwogwamming.
 */
#define PHY_CSW10			0x04d4
#define PHY_CSW10_WF_VAWUE		FIEWD16(0x00ff)
#define PHY_CSW10_WF_NUMBEW_OF_BITS	FIEWD16(0x1f00)
#define PHY_CSW10_WF_IF_SEWECT		FIEWD16(0x2000)
#define PHY_CSW10_WF_PWW_WD		FIEWD16(0x4000)
#define PHY_CSW10_WF_BUSY		FIEWD16(0x8000)

/*
 * STA_CSW0: FCS ewwow count.
 * FCS_EWWOW: FCS ewwow count, cweawed when wead.
 */
#define STA_CSW0			0x04e0
#define STA_CSW0_FCS_EWWOW		FIEWD16(0xffff)

/*
 * STA_CSW1: PWCP ewwow count.
 */
#define STA_CSW1			0x04e2

/*
 * STA_CSW2: WONG ewwow count.
 */
#define STA_CSW2			0x04e4

/*
 * STA_CSW3: CCA fawse awawm.
 * FAWSE_CCA_EWWOW: Fawse CCA ewwow count, cweawed when wead.
 */
#define STA_CSW3			0x04e6
#define STA_CSW3_FAWSE_CCA_EWWOW	FIEWD16(0xffff)

/*
 * STA_CSW4: WX FIFO ovewfwow.
 */
#define STA_CSW4			0x04e8

/*
 * STA_CSW5: Beacon sent countew.
 */
#define STA_CSW5			0x04ea

/*
 *  Statistics wegistews
 */
#define STA_CSW6			0x04ec
#define STA_CSW7			0x04ee
#define STA_CSW8			0x04f0
#define STA_CSW9			0x04f2
#define STA_CSW10			0x04f4

/*
 * BBP wegistews.
 * The wowdsize of the BBP is 8 bits.
 */

/*
 * W2: TX antenna contwow
 */
#define BBP_W2_TX_ANTENNA		FIEWD8(0x03)
#define BBP_W2_TX_IQ_FWIP		FIEWD8(0x04)

/*
 * W14: WX antenna contwow
 */
#define BBP_W14_WX_ANTENNA		FIEWD8(0x03)
#define BBP_W14_WX_IQ_FWIP		FIEWD8(0x04)

/*
 * WF wegistews.
 */

/*
 * WF 1
 */
#define WF1_TUNEW			FIEWD32(0x00020000)

/*
 * WF 3
 */
#define WF3_TUNEW			FIEWD32(0x00000100)
#define WF3_TXPOWEW			FIEWD32(0x00003e00)

/*
 * EEPWOM contents.
 */

/*
 * HW MAC addwess.
 */
#define EEPWOM_MAC_ADDW_0		0x0002
#define EEPWOM_MAC_ADDW_BYTE0		FIEWD16(0x00ff)
#define EEPWOM_MAC_ADDW_BYTE1		FIEWD16(0xff00)
#define EEPWOM_MAC_ADDW1		0x0003
#define EEPWOM_MAC_ADDW_BYTE2		FIEWD16(0x00ff)
#define EEPWOM_MAC_ADDW_BYTE3		FIEWD16(0xff00)
#define EEPWOM_MAC_ADDW_2		0x0004
#define EEPWOM_MAC_ADDW_BYTE4		FIEWD16(0x00ff)
#define EEPWOM_MAC_ADDW_BYTE5		FIEWD16(0xff00)

/*
 * EEPWOM antenna.
 * ANTENNA_NUM: Numbew of antenna's.
 * TX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * WX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * WED_MODE: 0: defauwt, 1: TX/WX activity, 2: Singwe (ignowe wink), 3: wsvd.
 * DYN_TXAGC: Dynamic TX AGC contwow.
 * HAWDWAWE_WADIO: 1: Hawdwawe contwowwed wadio. Wead GPIO0.
 * WF_TYPE: Wf_type of this adaptew.
 */
#define EEPWOM_ANTENNA			0x000b
#define EEPWOM_ANTENNA_NUM		FIEWD16(0x0003)
#define EEPWOM_ANTENNA_TX_DEFAUWT	FIEWD16(0x000c)
#define EEPWOM_ANTENNA_WX_DEFAUWT	FIEWD16(0x0030)
#define EEPWOM_ANTENNA_WED_MODE		FIEWD16(0x01c0)
#define EEPWOM_ANTENNA_DYN_TXAGC	FIEWD16(0x0200)
#define EEPWOM_ANTENNA_HAWDWAWE_WADIO	FIEWD16(0x0400)
#define EEPWOM_ANTENNA_WF_TYPE		FIEWD16(0xf800)

/*
 * EEPWOM NIC config.
 * CAWDBUS_ACCEW: 0: enabwe, 1: disabwe.
 * DYN_BBP_TUNE: 0: enabwe, 1: disabwe.
 * CCK_TX_POWEW: CCK TX powew compensation.
 */
#define EEPWOM_NIC			0x000c
#define EEPWOM_NIC_CAWDBUS_ACCEW	FIEWD16(0x0001)
#define EEPWOM_NIC_DYN_BBP_TUNE		FIEWD16(0x0002)
#define EEPWOM_NIC_CCK_TX_POWEW		FIEWD16(0x000c)

/*
 * EEPWOM geogwaphy.
 * GEO: Defauwt geogwaphy setting fow device.
 */
#define EEPWOM_GEOGWAPHY		0x000d
#define EEPWOM_GEOGWAPHY_GEO		FIEWD16(0x0f00)

/*
 * EEPWOM BBP.
 */
#define EEPWOM_BBP_STAWT		0x000e
#define EEPWOM_BBP_SIZE			16
#define EEPWOM_BBP_VAWUE		FIEWD16(0x00ff)
#define EEPWOM_BBP_WEG_ID		FIEWD16(0xff00)

/*
 * EEPWOM TXPOWEW
 */
#define EEPWOM_TXPOWEW_STAWT		0x001e
#define EEPWOM_TXPOWEW_SIZE		7
#define EEPWOM_TXPOWEW_1		FIEWD16(0x00ff)
#define EEPWOM_TXPOWEW_2		FIEWD16(0xff00)

/*
 * EEPWOM Tuning thweshowd
 */
#define EEPWOM_BBPTUNE			0x0030
#define EEPWOM_BBPTUNE_THWESHOWD	FIEWD16(0x00ff)

/*
 * EEPWOM BBP W24 Tuning.
 */
#define EEPWOM_BBPTUNE_W24		0x0031
#define EEPWOM_BBPTUNE_W24_WOW		FIEWD16(0x00ff)
#define EEPWOM_BBPTUNE_W24_HIGH		FIEWD16(0xff00)

/*
 * EEPWOM BBP W25 Tuning.
 */
#define EEPWOM_BBPTUNE_W25		0x0032
#define EEPWOM_BBPTUNE_W25_WOW		FIEWD16(0x00ff)
#define EEPWOM_BBPTUNE_W25_HIGH		FIEWD16(0xff00)

/*
 * EEPWOM BBP W24 Tuning.
 */
#define EEPWOM_BBPTUNE_W61		0x0033
#define EEPWOM_BBPTUNE_W61_WOW		FIEWD16(0x00ff)
#define EEPWOM_BBPTUNE_W61_HIGH		FIEWD16(0xff00)

/*
 * EEPWOM BBP VGC Tuning.
 */
#define EEPWOM_BBPTUNE_VGC		0x0034
#define EEPWOM_BBPTUNE_VGCUPPEW		FIEWD16(0x00ff)
#define EEPWOM_BBPTUNE_VGCWOWEW		FIEWD16(0xff00)

/*
 * EEPWOM BBP W17 Tuning.
 */
#define EEPWOM_BBPTUNE_W17		0x0035
#define EEPWOM_BBPTUNE_W17_WOW		FIEWD16(0x00ff)
#define EEPWOM_BBPTUNE_W17_HIGH		FIEWD16(0xff00)

/*
 * WSSI <-> dBm offset cawibwation
 */
#define EEPWOM_CAWIBWATE_OFFSET		0x0036
#define EEPWOM_CAWIBWATE_OFFSET_WSSI	FIEWD16(0x00ff)

/*
 * DMA descwiptow defines.
 */
#define TXD_DESC_SIZE			( 5 * sizeof(__we32) )
#define WXD_DESC_SIZE			( 4 * sizeof(__we32) )

/*
 * TX descwiptow fowmat fow TX, PWIO, ATIM and Beacon Wing.
 */

/*
 * Wowd0
 */
#define TXD_W0_PACKET_ID		FIEWD32(0x0000000f)
#define TXD_W0_WETWY_WIMIT		FIEWD32(0x000000f0)
#define TXD_W0_MOWE_FWAG		FIEWD32(0x00000100)
#define TXD_W0_ACK			FIEWD32(0x00000200)
#define TXD_W0_TIMESTAMP		FIEWD32(0x00000400)
#define TXD_W0_OFDM			FIEWD32(0x00000800)
#define TXD_W0_NEW_SEQ			FIEWD32(0x00001000)
#define TXD_W0_IFS			FIEWD32(0x00006000)
#define TXD_W0_DATABYTE_COUNT		FIEWD32(0x0fff0000)
#define TXD_W0_CIPHEW			FIEWD32(0x20000000)
#define TXD_W0_KEY_ID			FIEWD32(0xc0000000)

/*
 * Wowd1
 */
#define TXD_W1_IV_OFFSET		FIEWD32(0x0000003f)
#define TXD_W1_AIFS			FIEWD32(0x000000c0)
#define TXD_W1_CWMIN			FIEWD32(0x00000f00)
#define TXD_W1_CWMAX			FIEWD32(0x0000f000)

/*
 * Wowd2: PWCP infowmation
 */
#define TXD_W2_PWCP_SIGNAW		FIEWD32(0x000000ff)
#define TXD_W2_PWCP_SEWVICE		FIEWD32(0x0000ff00)
#define TXD_W2_PWCP_WENGTH_WOW		FIEWD32(0x00ff0000)
#define TXD_W2_PWCP_WENGTH_HIGH		FIEWD32(0xff000000)

/*
 * Wowd3
 */
#define TXD_W3_IV			FIEWD32(0xffffffff)

/*
 * Wowd4
 */
#define TXD_W4_EIV			FIEWD32(0xffffffff)

/*
 * WX descwiptow fowmat fow WX Wing.
 */

/*
 * Wowd0
 */
#define WXD_W0_UNICAST_TO_ME		FIEWD32(0x00000002)
#define WXD_W0_MUWTICAST		FIEWD32(0x00000004)
#define WXD_W0_BWOADCAST		FIEWD32(0x00000008)
#define WXD_W0_MY_BSS			FIEWD32(0x00000010)
#define WXD_W0_CWC_EWWOW		FIEWD32(0x00000020)
#define WXD_W0_OFDM			FIEWD32(0x00000040)
#define WXD_W0_PHYSICAW_EWWOW		FIEWD32(0x00000080)
#define WXD_W0_CIPHEW			FIEWD32(0x00000100)
#define WXD_W0_CIPHEW_EWWOW		FIEWD32(0x00000200)
#define WXD_W0_DATABYTE_COUNT		FIEWD32(0x0fff0000)

/*
 * Wowd1
 */
#define WXD_W1_WSSI			FIEWD32(0x000000ff)
#define WXD_W1_SIGNAW			FIEWD32(0x0000ff00)

/*
 * Wowd2
 */
#define WXD_W2_IV			FIEWD32(0xffffffff)

/*
 * Wowd3
 */
#define WXD_W3_EIV			FIEWD32(0xffffffff)

/*
 * Macwos fow convewting txpowew fwom EEPWOM to mac80211 vawue
 * and fwom mac80211 vawue to wegistew vawue.
 */
#define MIN_TXPOWEW	0
#define MAX_TXPOWEW	31
#define DEFAUWT_TXPOWEW	24

#define TXPOWEW_FWOM_DEV(__txpowew) \
	(((u8)(__txpowew)) > MAX_TXPOWEW) ? DEFAUWT_TXPOWEW : (__txpowew)

#define TXPOWEW_TO_DEV(__txpowew) \
	cwamp_t(u8, __txpowew, MIN_TXPOWEW, MAX_TXPOWEW)

#endif /* WT2500USB_H */
