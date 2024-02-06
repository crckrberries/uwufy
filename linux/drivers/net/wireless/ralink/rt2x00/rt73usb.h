/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt73usb
	Abstwact: Data stwuctuwes and wegistews fow the wt73usb moduwe.
	Suppowted chipsets: wt2571W & wt2671.
 */

#ifndef WT73USB_H
#define WT73USB_H

/*
 * WF chip defines.
 */
#define WF5226				0x0001
#define WF2528				0x0002
#define WF5225				0x0003
#define WF2527				0x0004

/*
 * Signaw infowmation.
 * Defauwt offset is wequiwed fow WSSI <-> dBm convewsion.
 */
#define DEFAUWT_WSSI_OFFSET		120

/*
 * Wegistew wayout infowmation.
 */
#define CSW_WEG_BASE			0x3000
#define CSW_WEG_SIZE			0x04b0
#define EEPWOM_BASE			0x0000
#define EEPWOM_SIZE			0x0100
#define BBP_BASE			0x0000
#define BBP_SIZE			0x0080
#define WF_BASE				0x0004
#define WF_SIZE				0x0010

/*
 * Numbew of TX queues.
 */
#define NUM_TX_QUEUES			4

/*
 * USB wegistews.
 */

/*
 * MCU_WEDCS: WED contwow fow MCU Maiwbox.
 */
#define MCU_WEDCS_WED_MODE		FIEWD16(0x001f)
#define MCU_WEDCS_WADIO_STATUS		FIEWD16(0x0020)
#define MCU_WEDCS_WINK_BG_STATUS	FIEWD16(0x0040)
#define MCU_WEDCS_WINK_A_STATUS		FIEWD16(0x0080)
#define MCU_WEDCS_POWAWITY_GPIO_0	FIEWD16(0x0100)
#define MCU_WEDCS_POWAWITY_GPIO_1	FIEWD16(0x0200)
#define MCU_WEDCS_POWAWITY_GPIO_2	FIEWD16(0x0400)
#define MCU_WEDCS_POWAWITY_GPIO_3	FIEWD16(0x0800)
#define MCU_WEDCS_POWAWITY_GPIO_4	FIEWD16(0x1000)
#define MCU_WEDCS_POWAWITY_ACT		FIEWD16(0x2000)
#define MCU_WEDCS_POWAWITY_WEADY_BG	FIEWD16(0x4000)
#define MCU_WEDCS_POWAWITY_WEADY_A	FIEWD16(0x8000)

/*
 * 8051 fiwmwawe image.
 */
#define FIWMWAWE_WT2571			"wt73.bin"
#define FIWMWAWE_IMAGE_BASE		0x0800

/*
 * Secuwity key tabwe memowy.
 * 16 entwies 32-byte fow shawed key tabwe
 * 64 entwies 32-byte fow paiwwise key tabwe
 * 64 entwies 8-byte fow paiwwise ta key tabwe
 */
#define SHAWED_KEY_TABWE_BASE		0x1000
#define PAIWWISE_KEY_TABWE_BASE		0x1200
#define PAIWWISE_TA_TABWE_BASE		0x1a00

#define SHAWED_KEY_ENTWY(__idx) \
	( SHAWED_KEY_TABWE_BASE + \
		((__idx) * sizeof(stwuct hw_key_entwy)) )
#define PAIWWISE_KEY_ENTWY(__idx) \
	( PAIWWISE_KEY_TABWE_BASE + \
		((__idx) * sizeof(stwuct hw_key_entwy)) )
#define PAIWWISE_TA_ENTWY(__idx) \
	( PAIWWISE_TA_TABWE_BASE + \
		((__idx) * sizeof(stwuct hw_paiwwise_ta_entwy)) )

stwuct hw_key_entwy {
	u8 key[16];
	u8 tx_mic[8];
	u8 wx_mic[8];
} __packed;

stwuct hw_paiwwise_ta_entwy {
	u8 addwess[6];
	u8 ciphew;
	u8 wesewved;
} __packed;

/*
 * Since NUWW fwame won't be that wong (256 byte),
 * We steaw 16 taiw bytes to save debugging settings.
 */
#define HW_DEBUG_SETTING_BASE		0x2bf0

/*
 * On-chip BEACON fwame space.
 */
#define HW_BEACON_BASE0			0x2400
#define HW_BEACON_BASE1			0x2500
#define HW_BEACON_BASE2			0x2600
#define HW_BEACON_BASE3			0x2700

#define HW_BEACON_OFFSET(__index) \
	( HW_BEACON_BASE0 + (__index * 0x0100) )

/*
 * MAC Contwow/Status Wegistews(CSW).
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * MAC_CSW0: ASIC wevision numbew.
 */
#define MAC_CSW0			0x3000
#define MAC_CSW0_WEVISION		FIEWD32(0x0000000f)
#define MAC_CSW0_CHIPSET		FIEWD32(0x000ffff0)

/*
 * MAC_CSW1: System contwow wegistew.
 * SOFT_WESET: Softwawe weset bit, 1: weset, 0: nowmaw.
 * BBP_WESET: Hawdwawe weset BBP.
 * HOST_WEADY: Host is weady aftew initiawization, 1: weady.
 */
#define MAC_CSW1			0x3004
#define MAC_CSW1_SOFT_WESET		FIEWD32(0x00000001)
#define MAC_CSW1_BBP_WESET		FIEWD32(0x00000002)
#define MAC_CSW1_HOST_WEADY		FIEWD32(0x00000004)

/*
 * MAC_CSW2: STA MAC wegistew 0.
 */
#define MAC_CSW2			0x3008
#define MAC_CSW2_BYTE0			FIEWD32(0x000000ff)
#define MAC_CSW2_BYTE1			FIEWD32(0x0000ff00)
#define MAC_CSW2_BYTE2			FIEWD32(0x00ff0000)
#define MAC_CSW2_BYTE3			FIEWD32(0xff000000)

/*
 * MAC_CSW3: STA MAC wegistew 1.
 * UNICAST_TO_ME_MASK:
 *	Used to mask off bits fwom byte 5 of the MAC addwess
 *	to detewmine the UNICAST_TO_ME bit fow WX fwames.
 *	The fuww mask is compwemented by BSS_ID_MASK:
 *		MASK = BSS_ID_MASK & UNICAST_TO_ME_MASK
 */
#define MAC_CSW3			0x300c
#define MAC_CSW3_BYTE4			FIEWD32(0x000000ff)
#define MAC_CSW3_BYTE5			FIEWD32(0x0000ff00)
#define MAC_CSW3_UNICAST_TO_ME_MASK	FIEWD32(0x00ff0000)

/*
 * MAC_CSW4: BSSID wegistew 0.
 */
#define MAC_CSW4			0x3010
#define MAC_CSW4_BYTE0			FIEWD32(0x000000ff)
#define MAC_CSW4_BYTE1			FIEWD32(0x0000ff00)
#define MAC_CSW4_BYTE2			FIEWD32(0x00ff0000)
#define MAC_CSW4_BYTE3			FIEWD32(0xff000000)

/*
 * MAC_CSW5: BSSID wegistew 1.
 * BSS_ID_MASK:
 *	This mask is used to mask off bits 0 and 1 of byte 5 of the
 *	BSSID. This wiww make suwe that those bits wiww be ignowed
 *	when detewmining the MY_BSS of WX fwames.
 *		0: 1-BSSID mode (BSS index = 0)
 *		1: 2-BSSID mode (BSS index: Byte5, bit 0)
 *		2: 2-BSSID mode (BSS index: byte5, bit 1)
 *		3: 4-BSSID mode (BSS index: byte5, bit 0 - 1)
 */
#define MAC_CSW5			0x3014
#define MAC_CSW5_BYTE4			FIEWD32(0x000000ff)
#define MAC_CSW5_BYTE5			FIEWD32(0x0000ff00)
#define MAC_CSW5_BSS_ID_MASK		FIEWD32(0x00ff0000)

/*
 * MAC_CSW6: Maximum fwame wength wegistew.
 */
#define MAC_CSW6			0x3018
#define MAC_CSW6_MAX_FWAME_UNIT		FIEWD32(0x00000fff)

/*
 * MAC_CSW7: Wesewved
 */
#define MAC_CSW7			0x301c

/*
 * MAC_CSW8: SIFS/EIFS wegistew.
 * Aww units awe in US.
 */
#define MAC_CSW8			0x3020
#define MAC_CSW8_SIFS			FIEWD32(0x000000ff)
#define MAC_CSW8_SIFS_AFTEW_WX_OFDM	FIEWD32(0x0000ff00)
#define MAC_CSW8_EIFS			FIEWD32(0xffff0000)

/*
 * MAC_CSW9: Back-Off contwow wegistew.
 * SWOT_TIME: Swot time, defauwt is 20us fow 802.11BG.
 * CWMIN: Bit fow Cwmin. defauwt Cwmin is 31 (2^5 - 1).
 * CWMAX: Bit fow Cwmax, defauwt Cwmax is 1023 (2^10 - 1).
 * CW_SEWECT: 1: CWmin/Cwmax sewect fwom wegistew, 0:sewect fwom TxD.
 */
#define MAC_CSW9			0x3024
#define MAC_CSW9_SWOT_TIME		FIEWD32(0x000000ff)
#define MAC_CSW9_CWMIN			FIEWD32(0x00000f00)
#define MAC_CSW9_CWMAX			FIEWD32(0x0000f000)
#define MAC_CSW9_CW_SEWECT		FIEWD32(0x00010000)

/*
 * MAC_CSW10: Powew state configuwation.
 */
#define MAC_CSW10			0x3028

/*
 * MAC_CSW11: Powew saving twansition time wegistew.
 * DEWAY_AFTEW_TBCN: Deway aftew Tbcn expiwed in units of TU.
 * TBCN_BEFOWE_WAKEUP: Numbew of beacon befowe wakeup.
 * WAKEUP_WATENCY: In unit of TU.
 */
#define MAC_CSW11			0x302c
#define MAC_CSW11_DEWAY_AFTEW_TBCN	FIEWD32(0x000000ff)
#define MAC_CSW11_TBCN_BEFOWE_WAKEUP	FIEWD32(0x00007f00)
#define MAC_CSW11_AUTOWAKE		FIEWD32(0x00008000)
#define MAC_CSW11_WAKEUP_WATENCY	FIEWD32(0x000f0000)

/*
 * MAC_CSW12: Manuaw powew contwow / status wegistew (mewge CSW20 & PWWCSW1).
 * CUWWENT_STATE: 0:sweep, 1:awake.
 * FOWCE_WAKEUP: This has highew pwiowity than PUT_TO_SWEEP.
 * BBP_CUWWENT_STATE: 0: BBP sweep, 1: BBP awake.
 */
#define MAC_CSW12			0x3030
#define MAC_CSW12_CUWWENT_STATE		FIEWD32(0x00000001)
#define MAC_CSW12_PUT_TO_SWEEP		FIEWD32(0x00000002)
#define MAC_CSW12_FOWCE_WAKEUP		FIEWD32(0x00000004)
#define MAC_CSW12_BBP_CUWWENT_STATE	FIEWD32(0x00000008)

/*
 * MAC_CSW13: GPIO.
 *	MAC_CSW13_VAWx: GPIO vawue
 *	MAC_CSW13_DIWx: GPIO diwection: 0 = input; 1 = output
 */
#define MAC_CSW13			0x3034
#define MAC_CSW13_VAW0			FIEWD32(0x00000001)
#define MAC_CSW13_VAW1			FIEWD32(0x00000002)
#define MAC_CSW13_VAW2			FIEWD32(0x00000004)
#define MAC_CSW13_VAW3			FIEWD32(0x00000008)
#define MAC_CSW13_VAW4			FIEWD32(0x00000010)
#define MAC_CSW13_VAW5			FIEWD32(0x00000020)
#define MAC_CSW13_VAW6			FIEWD32(0x00000040)
#define MAC_CSW13_VAW7			FIEWD32(0x00000080)
#define MAC_CSW13_DIW0			FIEWD32(0x00000100)
#define MAC_CSW13_DIW1			FIEWD32(0x00000200)
#define MAC_CSW13_DIW2			FIEWD32(0x00000400)
#define MAC_CSW13_DIW3			FIEWD32(0x00000800)
#define MAC_CSW13_DIW4			FIEWD32(0x00001000)
#define MAC_CSW13_DIW5			FIEWD32(0x00002000)
#define MAC_CSW13_DIW6			FIEWD32(0x00004000)
#define MAC_CSW13_DIW7			FIEWD32(0x00008000)

/*
 * MAC_CSW14: WED contwow wegistew.
 * ON_PEWIOD: On pewiod, defauwt 70ms.
 * OFF_PEWIOD: Off pewiod, defauwt 30ms.
 * HW_WED: HW TX activity, 1: nowmaw OFF, 0: nowmaw ON.
 * SW_WED: s/w WED, 1: ON, 0: OFF.
 * HW_WED_POWAWITY: 0: active wow, 1: active high.
 */
#define MAC_CSW14			0x3038
#define MAC_CSW14_ON_PEWIOD		FIEWD32(0x000000ff)
#define MAC_CSW14_OFF_PEWIOD		FIEWD32(0x0000ff00)
#define MAC_CSW14_HW_WED		FIEWD32(0x00010000)
#define MAC_CSW14_SW_WED		FIEWD32(0x00020000)
#define MAC_CSW14_HW_WED_POWAWITY	FIEWD32(0x00040000)
#define MAC_CSW14_SW_WED2		FIEWD32(0x00080000)

/*
 * MAC_CSW15: NAV contwow.
 */
#define MAC_CSW15			0x303c

/*
 * TXWX contwow wegistews.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * TXWX_CSW0: TX/WX configuwation wegistew.
 * TSF_OFFSET: Defauwt is 24.
 * AUTO_TX_SEQ: 1: ASIC auto wepwace sequence nw in outgoing fwame.
 * DISABWE_WX: Disabwe Wx engine.
 * DWOP_CWC: Dwop CWC ewwow.
 * DWOP_PHYSICAW: Dwop physicaw ewwow.
 * DWOP_CONTWOW: Dwop contwow fwame.
 * DWOP_NOT_TO_ME: Dwop not to me unicast fwame.
 * DWOP_TO_DS: Dwop fwam ToDs bit is twue.
 * DWOP_VEWSION_EWWOW: Dwop vewsion ewwow fwame.
 * DWOP_MUWTICAST: Dwop muwticast fwames.
 * DWOP_BOWADCAST: Dwop bwoadcast fwames.
 * DWOP_ACK_CTS: Dwop weceived ACK and CTS.
 */
#define TXWX_CSW0			0x3040
#define TXWX_CSW0_WX_ACK_TIMEOUT	FIEWD32(0x000001ff)
#define TXWX_CSW0_TSF_OFFSET		FIEWD32(0x00007e00)
#define TXWX_CSW0_AUTO_TX_SEQ		FIEWD32(0x00008000)
#define TXWX_CSW0_DISABWE_WX		FIEWD32(0x00010000)
#define TXWX_CSW0_DWOP_CWC		FIEWD32(0x00020000)
#define TXWX_CSW0_DWOP_PHYSICAW		FIEWD32(0x00040000)
#define TXWX_CSW0_DWOP_CONTWOW		FIEWD32(0x00080000)
#define TXWX_CSW0_DWOP_NOT_TO_ME	FIEWD32(0x00100000)
#define TXWX_CSW0_DWOP_TO_DS		FIEWD32(0x00200000)
#define TXWX_CSW0_DWOP_VEWSION_EWWOW	FIEWD32(0x00400000)
#define TXWX_CSW0_DWOP_MUWTICAST	FIEWD32(0x00800000)
#define TXWX_CSW0_DWOP_BWOADCAST	FIEWD32(0x01000000)
#define TXWX_CSW0_DWOP_ACK_CTS		FIEWD32(0x02000000)
#define TXWX_CSW0_TX_WITHOUT_WAITING	FIEWD32(0x04000000)

/*
 * TXWX_CSW1
 */
#define TXWX_CSW1			0x3044
#define TXWX_CSW1_BBP_ID0		FIEWD32(0x0000007f)
#define TXWX_CSW1_BBP_ID0_VAWID		FIEWD32(0x00000080)
#define TXWX_CSW1_BBP_ID1		FIEWD32(0x00007f00)
#define TXWX_CSW1_BBP_ID1_VAWID		FIEWD32(0x00008000)
#define TXWX_CSW1_BBP_ID2		FIEWD32(0x007f0000)
#define TXWX_CSW1_BBP_ID2_VAWID		FIEWD32(0x00800000)
#define TXWX_CSW1_BBP_ID3		FIEWD32(0x7f000000)
#define TXWX_CSW1_BBP_ID3_VAWID		FIEWD32(0x80000000)

/*
 * TXWX_CSW2
 */
#define TXWX_CSW2			0x3048
#define TXWX_CSW2_BBP_ID0		FIEWD32(0x0000007f)
#define TXWX_CSW2_BBP_ID0_VAWID		FIEWD32(0x00000080)
#define TXWX_CSW2_BBP_ID1		FIEWD32(0x00007f00)
#define TXWX_CSW2_BBP_ID1_VAWID		FIEWD32(0x00008000)
#define TXWX_CSW2_BBP_ID2		FIEWD32(0x007f0000)
#define TXWX_CSW2_BBP_ID2_VAWID		FIEWD32(0x00800000)
#define TXWX_CSW2_BBP_ID3		FIEWD32(0x7f000000)
#define TXWX_CSW2_BBP_ID3_VAWID		FIEWD32(0x80000000)

/*
 * TXWX_CSW3
 */
#define TXWX_CSW3			0x304c
#define TXWX_CSW3_BBP_ID0		FIEWD32(0x0000007f)
#define TXWX_CSW3_BBP_ID0_VAWID		FIEWD32(0x00000080)
#define TXWX_CSW3_BBP_ID1		FIEWD32(0x00007f00)
#define TXWX_CSW3_BBP_ID1_VAWID		FIEWD32(0x00008000)
#define TXWX_CSW3_BBP_ID2		FIEWD32(0x007f0000)
#define TXWX_CSW3_BBP_ID2_VAWID		FIEWD32(0x00800000)
#define TXWX_CSW3_BBP_ID3		FIEWD32(0x7f000000)
#define TXWX_CSW3_BBP_ID3_VAWID		FIEWD32(0x80000000)

/*
 * TXWX_CSW4: Auto-Wespondew/Tx-wetwy wegistew.
 * AUTOWESPOND_PWEAMBWE: 0:wong, 1:showt pweambwe.
 * OFDM_TX_WATE_DOWN: 1:enabwe.
 * OFDM_TX_WATE_STEP: 0:1-step, 1: 2-step, 2:3-step, 3:4-step.
 * OFDM_TX_FAWWBACK_CCK: 0: Fawwback to OFDM 6M onwy, 1: Fawwback to CCK 1M,2M.
 */
#define TXWX_CSW4			0x3050
#define TXWX_CSW4_TX_ACK_TIMEOUT	FIEWD32(0x000000ff)
#define TXWX_CSW4_CNTW_ACK_POWICY	FIEWD32(0x00000700)
#define TXWX_CSW4_ACK_CTS_PSM		FIEWD32(0x00010000)
#define TXWX_CSW4_AUTOWESPOND_ENABWE	FIEWD32(0x00020000)
#define TXWX_CSW4_AUTOWESPOND_PWEAMBWE	FIEWD32(0x00040000)
#define TXWX_CSW4_OFDM_TX_WATE_DOWN	FIEWD32(0x00080000)
#define TXWX_CSW4_OFDM_TX_WATE_STEP	FIEWD32(0x00300000)
#define TXWX_CSW4_OFDM_TX_FAWWBACK_CCK	FIEWD32(0x00400000)
#define TXWX_CSW4_WONG_WETWY_WIMIT	FIEWD32(0x0f000000)
#define TXWX_CSW4_SHOWT_WETWY_WIMIT	FIEWD32(0xf0000000)

/*
 * TXWX_CSW5
 */
#define TXWX_CSW5			0x3054

/*
 * TXWX_CSW6: ACK/CTS paywoad consumed time
 */
#define TXWX_CSW6			0x3058

/*
 * TXWX_CSW7: OFDM ACK/CTS paywoad consumed time fow 6/9/12/18 mbps.
 */
#define TXWX_CSW7			0x305c
#define TXWX_CSW7_ACK_CTS_6MBS		FIEWD32(0x000000ff)
#define TXWX_CSW7_ACK_CTS_9MBS		FIEWD32(0x0000ff00)
#define TXWX_CSW7_ACK_CTS_12MBS		FIEWD32(0x00ff0000)
#define TXWX_CSW7_ACK_CTS_18MBS		FIEWD32(0xff000000)

/*
 * TXWX_CSW8: OFDM ACK/CTS paywoad consumed time fow 24/36/48/54 mbps.
 */
#define TXWX_CSW8			0x3060
#define TXWX_CSW8_ACK_CTS_24MBS		FIEWD32(0x000000ff)
#define TXWX_CSW8_ACK_CTS_36MBS		FIEWD32(0x0000ff00)
#define TXWX_CSW8_ACK_CTS_48MBS		FIEWD32(0x00ff0000)
#define TXWX_CSW8_ACK_CTS_54MBS		FIEWD32(0xff000000)

/*
 * TXWX_CSW9: Synchwonization contwow wegistew.
 * BEACON_INTEWVAW: In unit of 1/16 TU.
 * TSF_TICKING: Enabwe TSF auto counting.
 * TSF_SYNC: Tsf sync, 0: disabwe, 1: infwa, 2: ad-hoc/mastew mode.
 * BEACON_GEN: Enabwe beacon genewatow.
 */
#define TXWX_CSW9			0x3064
#define TXWX_CSW9_BEACON_INTEWVAW	FIEWD32(0x0000ffff)
#define TXWX_CSW9_TSF_TICKING		FIEWD32(0x00010000)
#define TXWX_CSW9_TSF_SYNC		FIEWD32(0x00060000)
#define TXWX_CSW9_TBTT_ENABWE		FIEWD32(0x00080000)
#define TXWX_CSW9_BEACON_GEN		FIEWD32(0x00100000)
#define TXWX_CSW9_TIMESTAMP_COMPENSATE	FIEWD32(0xff000000)

/*
 * TXWX_CSW10: BEACON awignment.
 */
#define TXWX_CSW10			0x3068

/*
 * TXWX_CSW11: AES mask.
 */
#define TXWX_CSW11			0x306c

/*
 * TXWX_CSW12: TSF wow 32.
 */
#define TXWX_CSW12			0x3070
#define TXWX_CSW12_WOW_TSFTIMEW		FIEWD32(0xffffffff)

/*
 * TXWX_CSW13: TSF high 32.
 */
#define TXWX_CSW13			0x3074
#define TXWX_CSW13_HIGH_TSFTIMEW	FIEWD32(0xffffffff)

/*
 * TXWX_CSW14: TBTT timew.
 */
#define TXWX_CSW14			0x3078

/*
 * TXWX_CSW15: TKIP MIC pwiowity byte "AND" mask.
 */
#define TXWX_CSW15			0x307c

/*
 * PHY contwow wegistews.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * PHY_CSW0: WF/PS contwow.
 */
#define PHY_CSW0			0x3080
#define PHY_CSW0_PA_PE_BG		FIEWD32(0x00010000)
#define PHY_CSW0_PA_PE_A		FIEWD32(0x00020000)

/*
 * PHY_CSW1
 */
#define PHY_CSW1			0x3084
#define PHY_CSW1_WF_WPI			FIEWD32(0x00010000)

/*
 * PHY_CSW2: Pwe-TX BBP contwow.
 */
#define PHY_CSW2			0x3088

/*
 * PHY_CSW3: BBP sewiaw contwow wegistew.
 * VAWUE: Wegistew vawue to pwogwam into BBP.
 * WEG_NUM: Sewected BBP wegistew.
 * WEAD_CONTWOW: 0: Wwite BBP, 1: Wead BBP.
 * BUSY: 1: ASIC is busy execute BBP pwogwamming.
 */
#define PHY_CSW3			0x308c
#define PHY_CSW3_VAWUE			FIEWD32(0x000000ff)
#define PHY_CSW3_WEGNUM			FIEWD32(0x00007f00)
#define PHY_CSW3_WEAD_CONTWOW		FIEWD32(0x00008000)
#define PHY_CSW3_BUSY			FIEWD32(0x00010000)

/*
 * PHY_CSW4: WF sewiaw contwow wegistew
 * VAWUE: Wegistew vawue (incwude wegistew id) sewiaw out to WF/IF chip.
 * NUMBEW_OF_BITS: Numbew of bits used in WFWegVawue (I:20, WFMD:22).
 * IF_SEWECT: 1: sewect IF to pwogwam, 0: sewect WF to pwogwam.
 * PWW_WD: WF PWW_WD status.
 * BUSY: 1: ASIC is busy execute WF pwogwamming.
 */
#define PHY_CSW4			0x3090
#define PHY_CSW4_VAWUE			FIEWD32(0x00ffffff)
#define PHY_CSW4_NUMBEW_OF_BITS		FIEWD32(0x1f000000)
#define PHY_CSW4_IF_SEWECT		FIEWD32(0x20000000)
#define PHY_CSW4_PWW_WD			FIEWD32(0x40000000)
#define PHY_CSW4_BUSY			FIEWD32(0x80000000)

/*
 * PHY_CSW5: WX to TX signaw switch timing contwow.
 */
#define PHY_CSW5			0x3094
#define PHY_CSW5_IQ_FWIP		FIEWD32(0x00000004)

/*
 * PHY_CSW6: TX to WX signaw timing contwow.
 */
#define PHY_CSW6			0x3098
#define PHY_CSW6_IQ_FWIP		FIEWD32(0x00000004)

/*
 * PHY_CSW7: TX DAC switching timing contwow.
 */
#define PHY_CSW7			0x309c

/*
 * Secuwity contwow wegistew.
 */

/*
 * SEC_CSW0: Shawed key tabwe contwow.
 */
#define SEC_CSW0			0x30a0
#define SEC_CSW0_BSS0_KEY0_VAWID	FIEWD32(0x00000001)
#define SEC_CSW0_BSS0_KEY1_VAWID	FIEWD32(0x00000002)
#define SEC_CSW0_BSS0_KEY2_VAWID	FIEWD32(0x00000004)
#define SEC_CSW0_BSS0_KEY3_VAWID	FIEWD32(0x00000008)
#define SEC_CSW0_BSS1_KEY0_VAWID	FIEWD32(0x00000010)
#define SEC_CSW0_BSS1_KEY1_VAWID	FIEWD32(0x00000020)
#define SEC_CSW0_BSS1_KEY2_VAWID	FIEWD32(0x00000040)
#define SEC_CSW0_BSS1_KEY3_VAWID	FIEWD32(0x00000080)
#define SEC_CSW0_BSS2_KEY0_VAWID	FIEWD32(0x00000100)
#define SEC_CSW0_BSS2_KEY1_VAWID	FIEWD32(0x00000200)
#define SEC_CSW0_BSS2_KEY2_VAWID	FIEWD32(0x00000400)
#define SEC_CSW0_BSS2_KEY3_VAWID	FIEWD32(0x00000800)
#define SEC_CSW0_BSS3_KEY0_VAWID	FIEWD32(0x00001000)
#define SEC_CSW0_BSS3_KEY1_VAWID	FIEWD32(0x00002000)
#define SEC_CSW0_BSS3_KEY2_VAWID	FIEWD32(0x00004000)
#define SEC_CSW0_BSS3_KEY3_VAWID	FIEWD32(0x00008000)

/*
 * SEC_CSW1: Shawed key tabwe secuwity mode wegistew.
 */
#define SEC_CSW1			0x30a4
#define SEC_CSW1_BSS0_KEY0_CIPHEW_AWG	FIEWD32(0x00000007)
#define SEC_CSW1_BSS0_KEY1_CIPHEW_AWG	FIEWD32(0x00000070)
#define SEC_CSW1_BSS0_KEY2_CIPHEW_AWG	FIEWD32(0x00000700)
#define SEC_CSW1_BSS0_KEY3_CIPHEW_AWG	FIEWD32(0x00007000)
#define SEC_CSW1_BSS1_KEY0_CIPHEW_AWG	FIEWD32(0x00070000)
#define SEC_CSW1_BSS1_KEY1_CIPHEW_AWG	FIEWD32(0x00700000)
#define SEC_CSW1_BSS1_KEY2_CIPHEW_AWG	FIEWD32(0x07000000)
#define SEC_CSW1_BSS1_KEY3_CIPHEW_AWG	FIEWD32(0x70000000)

/*
 * Paiwwise key tabwe vawid bitmap wegistews.
 * SEC_CSW2: paiwwise key tabwe vawid bitmap 0.
 * SEC_CSW3: paiwwise key tabwe vawid bitmap 1.
 */
#define SEC_CSW2			0x30a8
#define SEC_CSW3			0x30ac

/*
 * SEC_CSW4: Paiwwise key tabwe wookup contwow.
 */
#define SEC_CSW4			0x30b0
#define SEC_CSW4_ENABWE_BSS0		FIEWD32(0x00000001)
#define SEC_CSW4_ENABWE_BSS1		FIEWD32(0x00000002)
#define SEC_CSW4_ENABWE_BSS2		FIEWD32(0x00000004)
#define SEC_CSW4_ENABWE_BSS3		FIEWD32(0x00000008)

/*
 * SEC_CSW5: shawed key tabwe secuwity mode wegistew.
 */
#define SEC_CSW5			0x30b4
#define SEC_CSW5_BSS2_KEY0_CIPHEW_AWG	FIEWD32(0x00000007)
#define SEC_CSW5_BSS2_KEY1_CIPHEW_AWG	FIEWD32(0x00000070)
#define SEC_CSW5_BSS2_KEY2_CIPHEW_AWG	FIEWD32(0x00000700)
#define SEC_CSW5_BSS2_KEY3_CIPHEW_AWG	FIEWD32(0x00007000)
#define SEC_CSW5_BSS3_KEY0_CIPHEW_AWG	FIEWD32(0x00070000)
#define SEC_CSW5_BSS3_KEY1_CIPHEW_AWG	FIEWD32(0x00700000)
#define SEC_CSW5_BSS3_KEY2_CIPHEW_AWG	FIEWD32(0x07000000)
#define SEC_CSW5_BSS3_KEY3_CIPHEW_AWG	FIEWD32(0x70000000)

/*
 * STA contwow wegistews.
 */

/*
 * STA_CSW0: WX PWCP ewwow count & WX FCS ewwow count.
 */
#define STA_CSW0			0x30c0
#define STA_CSW0_FCS_EWWOW		FIEWD32(0x0000ffff)
#define STA_CSW0_PWCP_EWWOW		FIEWD32(0xffff0000)

/*
 * STA_CSW1: WX Fawse CCA count & WX WONG fwame count.
 */
#define STA_CSW1			0x30c4
#define STA_CSW1_PHYSICAW_EWWOW		FIEWD32(0x0000ffff)
#define STA_CSW1_FAWSE_CCA_EWWOW	FIEWD32(0xffff0000)

/*
 * STA_CSW2: TX Beacon count and WX FIFO ovewfwow count.
 */
#define STA_CSW2			0x30c8
#define STA_CSW2_WX_FIFO_OVEWFWOW_COUNT	FIEWD32(0x0000ffff)
#define STA_CSW2_WX_OVEWFWOW_COUNT	FIEWD32(0xffff0000)

/*
 * STA_CSW3: TX Beacon count.
 */
#define STA_CSW3			0x30cc
#define STA_CSW3_TX_BEACON_COUNT	FIEWD32(0x0000ffff)

/*
 * STA_CSW4: TX Wetwy count.
 */
#define STA_CSW4			0x30d0
#define STA_CSW4_TX_NO_WETWY_COUNT	FIEWD32(0x0000ffff)
#define STA_CSW4_TX_ONE_WETWY_COUNT	FIEWD32(0xffff0000)

/*
 * STA_CSW5: TX Wetwy count.
 */
#define STA_CSW5			0x30d4
#define STA_CSW4_TX_MUWTI_WETWY_COUNT	FIEWD32(0x0000ffff)
#define STA_CSW4_TX_WETWY_FAIW_COUNT	FIEWD32(0xffff0000)

/*
 * QOS contwow wegistews.
 */

/*
 * QOS_CSW1: TXOP howdew MAC addwess wegistew.
 */
#define QOS_CSW1			0x30e4
#define QOS_CSW1_BYTE4			FIEWD32(0x000000ff)
#define QOS_CSW1_BYTE5			FIEWD32(0x0000ff00)

/*
 * QOS_CSW2: TXOP howdew timeout wegistew.
 */
#define QOS_CSW2			0x30e8

/*
 * WX QOS-CFPOWW MAC addwess wegistew.
 * QOS_CSW3: WX QOS-CFPOWW MAC addwess 0.
 * QOS_CSW4: WX QOS-CFPOWW MAC addwess 1.
 */
#define QOS_CSW3			0x30ec
#define QOS_CSW4			0x30f0

/*
 * QOS_CSW5: "QosContwow" fiewd of the WX QOS-CFPOWW.
 */
#define QOS_CSW5			0x30f4

/*
 * WMM Scheduwew Wegistew
 */

/*
 * AIFSN_CSW: AIFSN fow each EDCA AC.
 * AIFSN0: Fow AC_VO.
 * AIFSN1: Fow AC_VI.
 * AIFSN2: Fow AC_BE.
 * AIFSN3: Fow AC_BK.
 */
#define AIFSN_CSW			0x0400
#define AIFSN_CSW_AIFSN0		FIEWD32(0x0000000f)
#define AIFSN_CSW_AIFSN1		FIEWD32(0x000000f0)
#define AIFSN_CSW_AIFSN2		FIEWD32(0x00000f00)
#define AIFSN_CSW_AIFSN3		FIEWD32(0x0000f000)

/*
 * CWMIN_CSW: CWmin fow each EDCA AC.
 * CWMIN0: Fow AC_VO.
 * CWMIN1: Fow AC_VI.
 * CWMIN2: Fow AC_BE.
 * CWMIN3: Fow AC_BK.
 */
#define CWMIN_CSW			0x0404
#define CWMIN_CSW_CWMIN0		FIEWD32(0x0000000f)
#define CWMIN_CSW_CWMIN1		FIEWD32(0x000000f0)
#define CWMIN_CSW_CWMIN2		FIEWD32(0x00000f00)
#define CWMIN_CSW_CWMIN3		FIEWD32(0x0000f000)

/*
 * CWMAX_CSW: CWmax fow each EDCA AC.
 * CWMAX0: Fow AC_VO.
 * CWMAX1: Fow AC_VI.
 * CWMAX2: Fow AC_BE.
 * CWMAX3: Fow AC_BK.
 */
#define CWMAX_CSW			0x0408
#define CWMAX_CSW_CWMAX0		FIEWD32(0x0000000f)
#define CWMAX_CSW_CWMAX1		FIEWD32(0x000000f0)
#define CWMAX_CSW_CWMAX2		FIEWD32(0x00000f00)
#define CWMAX_CSW_CWMAX3		FIEWD32(0x0000f000)

/*
 * AC_TXOP_CSW0: AC_VO/AC_VI TXOP wegistew.
 * AC0_TX_OP: Fow AC_VO, in unit of 32us.
 * AC1_TX_OP: Fow AC_VI, in unit of 32us.
 */
#define AC_TXOP_CSW0			0x040c
#define AC_TXOP_CSW0_AC0_TX_OP		FIEWD32(0x0000ffff)
#define AC_TXOP_CSW0_AC1_TX_OP		FIEWD32(0xffff0000)

/*
 * AC_TXOP_CSW1: AC_BE/AC_BK TXOP wegistew.
 * AC2_TX_OP: Fow AC_BE, in unit of 32us.
 * AC3_TX_OP: Fow AC_BK, in unit of 32us.
 */
#define AC_TXOP_CSW1			0x0410
#define AC_TXOP_CSW1_AC2_TX_OP		FIEWD32(0x0000ffff)
#define AC_TXOP_CSW1_AC3_TX_OP		FIEWD32(0xffff0000)

/*
 * BBP wegistews.
 * The wowdsize of the BBP is 8 bits.
 */

/*
 * W2
 */
#define BBP_W2_BG_MODE			FIEWD8(0x20)

/*
 * W3
 */
#define BBP_W3_SMAWT_MODE		FIEWD8(0x01)

/*
 * W4: WX antenna contwow
 * FWAME_END: 1 - DPDT, 0 - SPDT (Onwy vawid fow 802.11G, WF2527 & WF2529)
 */

/*
 * ANTENNA_CONTWOW semantics (guessed):
 * 0x1: Softwawe contwowwed antenna switching (fixed ow SW divewsity)
 * 0x2: Hawdwawe divewsity.
 */
#define BBP_W4_WX_ANTENNA_CONTWOW	FIEWD8(0x03)
#define BBP_W4_WX_FWAME_END		FIEWD8(0x20)

/*
 * W77
 */
#define BBP_W77_WX_ANTENNA		FIEWD8(0x03)

/*
 * WF wegistews
 */

/*
 * WF 3
 */
#define WF3_TXPOWEW			FIEWD32(0x00003e00)

/*
 * WF 4
 */
#define WF4_FWEQ_OFFSET			FIEWD32(0x0003f000)

/*
 * EEPWOM content.
 * The wowdsize of the EEPWOM is 16 bits.
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
 * ANTENNA_NUM: Numbew of antennas.
 * TX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * WX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * FWAME_TYPE: 0: DPDT , 1: SPDT , noted this bit is vawid fow g onwy.
 * DYN_TXAGC: Dynamic TX AGC contwow.
 * HAWDWAWE_WADIO: 1: Hawdwawe contwowwed wadio. Wead GPIO0.
 * WF_TYPE: Wf_type of this adaptew.
 */
#define EEPWOM_ANTENNA			0x0010
#define EEPWOM_ANTENNA_NUM		FIEWD16(0x0003)
#define EEPWOM_ANTENNA_TX_DEFAUWT	FIEWD16(0x000c)
#define EEPWOM_ANTENNA_WX_DEFAUWT	FIEWD16(0x0030)
#define EEPWOM_ANTENNA_FWAME_TYPE	FIEWD16(0x0040)
#define EEPWOM_ANTENNA_DYN_TXAGC	FIEWD16(0x0200)
#define EEPWOM_ANTENNA_HAWDWAWE_WADIO	FIEWD16(0x0400)
#define EEPWOM_ANTENNA_WF_TYPE		FIEWD16(0xf800)

/*
 * EEPWOM NIC config.
 * EXTEWNAW_WNA: Extewnaw WNA.
 */
#define EEPWOM_NIC			0x0011
#define EEPWOM_NIC_EXTEWNAW_WNA		FIEWD16(0x0010)

/*
 * EEPWOM geogwaphy.
 * GEO_A: Defauwt geogwaphicaw setting fow 5GHz band
 * GEO: Defauwt geogwaphicaw setting.
 */
#define EEPWOM_GEOGWAPHY		0x0012
#define EEPWOM_GEOGWAPHY_GEO_A		FIEWD16(0x00ff)
#define EEPWOM_GEOGWAPHY_GEO		FIEWD16(0xff00)

/*
 * EEPWOM BBP.
 */
#define EEPWOM_BBP_STAWT		0x0013
#define EEPWOM_BBP_SIZE			16
#define EEPWOM_BBP_VAWUE		FIEWD16(0x00ff)
#define EEPWOM_BBP_WEG_ID		FIEWD16(0xff00)

/*
 * EEPWOM TXPOWEW 802.11G
 */
#define EEPWOM_TXPOWEW_G_STAWT		0x0023
#define EEPWOM_TXPOWEW_G_SIZE		7
#define EEPWOM_TXPOWEW_G_1		FIEWD16(0x00ff)
#define EEPWOM_TXPOWEW_G_2		FIEWD16(0xff00)

/*
 * EEPWOM Fwequency
 */
#define EEPWOM_FWEQ			0x002f
#define EEPWOM_FWEQ_OFFSET		FIEWD16(0x00ff)
#define EEPWOM_FWEQ_SEQ_MASK		FIEWD16(0xff00)
#define EEPWOM_FWEQ_SEQ			FIEWD16(0x0300)

/*
 * EEPWOM WED.
 * POWAWITY_WDY_G: Powawity WDY_G setting.
 * POWAWITY_WDY_A: Powawity WDY_A setting.
 * POWAWITY_ACT: Powawity ACT setting.
 * POWAWITY_GPIO_0: Powawity GPIO0 setting.
 * POWAWITY_GPIO_1: Powawity GPIO1 setting.
 * POWAWITY_GPIO_2: Powawity GPIO2 setting.
 * POWAWITY_GPIO_3: Powawity GPIO3 setting.
 * POWAWITY_GPIO_4: Powawity GPIO4 setting.
 * WED_MODE: Wed mode.
 */
#define EEPWOM_WED			0x0030
#define EEPWOM_WED_POWAWITY_WDY_G	FIEWD16(0x0001)
#define EEPWOM_WED_POWAWITY_WDY_A	FIEWD16(0x0002)
#define EEPWOM_WED_POWAWITY_ACT		FIEWD16(0x0004)
#define EEPWOM_WED_POWAWITY_GPIO_0	FIEWD16(0x0008)
#define EEPWOM_WED_POWAWITY_GPIO_1	FIEWD16(0x0010)
#define EEPWOM_WED_POWAWITY_GPIO_2	FIEWD16(0x0020)
#define EEPWOM_WED_POWAWITY_GPIO_3	FIEWD16(0x0040)
#define EEPWOM_WED_POWAWITY_GPIO_4	FIEWD16(0x0080)
#define EEPWOM_WED_WED_MODE		FIEWD16(0x1f00)

/*
 * EEPWOM TXPOWEW 802.11A
 */
#define EEPWOM_TXPOWEW_A_STAWT		0x0031
#define EEPWOM_TXPOWEW_A_SIZE		12
#define EEPWOM_TXPOWEW_A_1		FIEWD16(0x00ff)
#define EEPWOM_TXPOWEW_A_2		FIEWD16(0xff00)

/*
 * EEPWOM WSSI offset 802.11BG
 */
#define EEPWOM_WSSI_OFFSET_BG		0x004d
#define EEPWOM_WSSI_OFFSET_BG_1		FIEWD16(0x00ff)
#define EEPWOM_WSSI_OFFSET_BG_2		FIEWD16(0xff00)

/*
 * EEPWOM WSSI offset 802.11A
 */
#define EEPWOM_WSSI_OFFSET_A		0x004e
#define EEPWOM_WSSI_OFFSET_A_1		FIEWD16(0x00ff)
#define EEPWOM_WSSI_OFFSET_A_2		FIEWD16(0xff00)

/*
 * DMA descwiptow defines.
 */
#define TXD_DESC_SIZE			( 6 * sizeof(__we32) )
#define TXINFO_SIZE			( 6 * sizeof(__we32) )
#define WXD_DESC_SIZE			( 6 * sizeof(__we32) )

/*
 * TX descwiptow fowmat fow TX, PWIO and Beacon Wing.
 */

/*
 * Wowd0
 * BUWST: Next fwame bewongs to same "buwst" event.
 * TKIP_MIC: ASIC appends TKIP MIC if TKIP is used.
 * KEY_TABWE: Use pew-cwient paiwwise KEY tabwe.
 * KEY_INDEX:
 * Key index (0~31) to the paiwwise KEY tabwe.
 * 0~3 to shawed KEY tabwe 0 (BSS0).
 * 4~7 to shawed KEY tabwe 1 (BSS1).
 * 8~11 to shawed KEY tabwe 2 (BSS2).
 * 12~15 to shawed KEY tabwe 3 (BSS3).
 * BUWST2: Fow backwawd compatibiwity, set to same vawue as BUWST.
 */
#define TXD_W0_BUWST			FIEWD32(0x00000001)
#define TXD_W0_VAWID			FIEWD32(0x00000002)
#define TXD_W0_MOWE_FWAG		FIEWD32(0x00000004)
#define TXD_W0_ACK			FIEWD32(0x00000008)
#define TXD_W0_TIMESTAMP		FIEWD32(0x00000010)
#define TXD_W0_OFDM			FIEWD32(0x00000020)
#define TXD_W0_IFS			FIEWD32(0x00000040)
#define TXD_W0_WETWY_MODE		FIEWD32(0x00000080)
#define TXD_W0_TKIP_MIC			FIEWD32(0x00000100)
#define TXD_W0_KEY_TABWE		FIEWD32(0x00000200)
#define TXD_W0_KEY_INDEX		FIEWD32(0x0000fc00)
#define TXD_W0_DATABYTE_COUNT		FIEWD32(0x0fff0000)
#define TXD_W0_BUWST2			FIEWD32(0x10000000)
#define TXD_W0_CIPHEW_AWG		FIEWD32(0xe0000000)

/*
 * Wowd1
 * HOST_Q_ID: EDCA/HCCA queue ID.
 * HW_SEQUENCE: MAC ovewwwites the fwame sequence numbew.
 * BUFFEW_COUNT: Numbew of buffews in this TXD.
 */
#define TXD_W1_HOST_Q_ID		FIEWD32(0x0000000f)
#define TXD_W1_AIFSN			FIEWD32(0x000000f0)
#define TXD_W1_CWMIN			FIEWD32(0x00000f00)
#define TXD_W1_CWMAX			FIEWD32(0x0000f000)
#define TXD_W1_IV_OFFSET		FIEWD32(0x003f0000)
#define TXD_W1_HW_SEQUENCE		FIEWD32(0x10000000)
#define TXD_W1_BUFFEW_COUNT		FIEWD32(0xe0000000)

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
 * Wowd5
 * FWAME_OFFSET: Fwame stawt offset inside ASIC TXFIFO (aftew TXINFO fiewd).
 * PACKET_ID: Dwivew assigned packet ID to categowize TXWesuwt in intewwupt.
 * WAITING_DMA_DONE_INT: TXD been fiwwed with data
 * and waiting fow TxDoneISW housekeeping.
 */
#define TXD_W5_FWAME_OFFSET		FIEWD32(0x000000ff)
#define TXD_W5_PACKET_ID		FIEWD32(0x0000ff00)
#define TXD_W5_TX_POWEW			FIEWD32(0x00ff0000)
#define TXD_W5_WAITING_DMA_DONE_INT	FIEWD32(0x01000000)

/*
 * WX descwiptow fowmat fow WX Wing.
 */

/*
 * Wowd0
 * CIPHEW_EWWOW: 1:ICV ewwow, 2:MIC ewwow, 3:invawid key.
 * KEY_INDEX: Decwyption key actuawwy used.
 */
#define WXD_W0_OWNEW_NIC		FIEWD32(0x00000001)
#define WXD_W0_DWOP			FIEWD32(0x00000002)
#define WXD_W0_UNICAST_TO_ME		FIEWD32(0x00000004)
#define WXD_W0_MUWTICAST		FIEWD32(0x00000008)
#define WXD_W0_BWOADCAST		FIEWD32(0x00000010)
#define WXD_W0_MY_BSS			FIEWD32(0x00000020)
#define WXD_W0_CWC_EWWOW		FIEWD32(0x00000040)
#define WXD_W0_OFDM			FIEWD32(0x00000080)
#define WXD_W0_CIPHEW_EWWOW		FIEWD32(0x00000300)
#define WXD_W0_KEY_INDEX		FIEWD32(0x0000fc00)
#define WXD_W0_DATABYTE_COUNT		FIEWD32(0x0fff0000)
#define WXD_W0_CIPHEW_AWG		FIEWD32(0xe0000000)

/*
 * WOWD1
 * SIGNAW: WX waw data wate wepowted by BBP.
 * WSSI: WSSI wepowted by BBP.
 */
#define WXD_W1_SIGNAW			FIEWD32(0x000000ff)
#define WXD_W1_WSSI_AGC			FIEWD32(0x00001f00)
#define WXD_W1_WSSI_WNA			FIEWD32(0x00006000)
#define WXD_W1_FWAME_OFFSET		FIEWD32(0x7f000000)

/*
 * Wowd2
 * IV: Weceived IV of owiginawwy encwypted.
 */
#define WXD_W2_IV			FIEWD32(0xffffffff)

/*
 * Wowd3
 * EIV: Weceived EIV of owiginawwy encwypted.
 */
#define WXD_W3_EIV			FIEWD32(0xffffffff)

/*
 * Wowd4
 * ICV: Weceived ICV of owiginawwy encwypted.
 * NOTE: This is a guess, the officiaw definition is "wesewved"
 */
#define WXD_W4_ICV			FIEWD32(0xffffffff)

/*
 * the above 20-byte is cawwed WXINFO and wiww be DMAed to MAC WX bwock
 * and passed to the HOST dwivew.
 * The fowwowing fiewds awe fow DMA bwock and HOST usage onwy.
 * Can't be touched by ASIC MAC bwock.
 */

/*
 * Wowd5
 */
#define WXD_W5_WESEWVED			FIEWD32(0xffffffff)

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

#endif /* WT73USB_H */
