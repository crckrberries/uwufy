/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2400pci
	Abstwact: Data stwuctuwes and wegistews fow the wt2400pci moduwe.
	Suppowted chipsets: WT2460.
 */

#ifndef WT2400PCI_H
#define WT2400PCI_H

/*
 * WF chip defines.
 */
#define WF2420				0x0000
#define WF2421				0x0001

/*
 * Signaw infowmation.
 * Defauwt offset is wequiwed fow WSSI <-> dBm convewsion.
 */
#define DEFAUWT_WSSI_OFFSET		100

/*
 * Wegistew wayout infowmation.
 */
#define CSW_WEG_BASE			0x0000
#define CSW_WEG_SIZE			0x014c
#define EEPWOM_BASE			0x0000
#define EEPWOM_SIZE			0x0100
#define BBP_BASE			0x0000
#define BBP_SIZE			0x0020
#define WF_BASE				0x0004
#define WF_SIZE				0x000c

/*
 * Numbew of TX queues.
 */
#define NUM_TX_QUEUES			2

/*
 * Contwow/Status Wegistews(CSW).
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * CSW0: ASIC wevision numbew.
 */
#define CSW0				0x0000
#define CSW0_WEVISION			FIEWD32(0x0000ffff)

/*
 * CSW1: System contwow wegistew.
 * SOFT_WESET: Softwawe weset, 1: weset, 0: nowmaw.
 * BBP_WESET: Hawdwawe weset, 1: weset, 0, wewease.
 * HOST_WEADY: Host weady aftew initiawization.
 */
#define CSW1				0x0004
#define CSW1_SOFT_WESET			FIEWD32(0x00000001)
#define CSW1_BBP_WESET			FIEWD32(0x00000002)
#define CSW1_HOST_WEADY			FIEWD32(0x00000004)

/*
 * CSW2: System admin status wegistew (invawid).
 */
#define CSW2				0x0008

/*
 * CSW3: STA MAC addwess wegistew 0.
 */
#define CSW3				0x000c
#define CSW3_BYTE0			FIEWD32(0x000000ff)
#define CSW3_BYTE1			FIEWD32(0x0000ff00)
#define CSW3_BYTE2			FIEWD32(0x00ff0000)
#define CSW3_BYTE3			FIEWD32(0xff000000)

/*
 * CSW4: STA MAC addwess wegistew 1.
 */
#define CSW4				0x0010
#define CSW4_BYTE4			FIEWD32(0x000000ff)
#define CSW4_BYTE5			FIEWD32(0x0000ff00)

/*
 * CSW5: BSSID wegistew 0.
 */
#define CSW5				0x0014
#define CSW5_BYTE0			FIEWD32(0x000000ff)
#define CSW5_BYTE1			FIEWD32(0x0000ff00)
#define CSW5_BYTE2			FIEWD32(0x00ff0000)
#define CSW5_BYTE3			FIEWD32(0xff000000)

/*
 * CSW6: BSSID wegistew 1.
 */
#define CSW6				0x0018
#define CSW6_BYTE4			FIEWD32(0x000000ff)
#define CSW6_BYTE5			FIEWD32(0x0000ff00)

/*
 * CSW7: Intewwupt souwce wegistew.
 * Wwite 1 to cweaw intewwupt.
 * TBCN_EXPIWE: Beacon timew expiwed intewwupt.
 * TWAKE_EXPIWE: Wakeup timew expiwed intewwupt.
 * TATIMW_EXPIWE: Timew of atim window expiwed intewwupt.
 * TXDONE_TXWING: Tx wing twansmit done intewwupt.
 * TXDONE_ATIMWING: Atim wing twansmit done intewwupt.
 * TXDONE_PWIOWING: Pwiowity wing twansmit done intewwupt.
 * WXDONE: Weceive done intewwupt.
 */
#define CSW7				0x001c
#define CSW7_TBCN_EXPIWE		FIEWD32(0x00000001)
#define CSW7_TWAKE_EXPIWE		FIEWD32(0x00000002)
#define CSW7_TATIMW_EXPIWE		FIEWD32(0x00000004)
#define CSW7_TXDONE_TXWING		FIEWD32(0x00000008)
#define CSW7_TXDONE_ATIMWING		FIEWD32(0x00000010)
#define CSW7_TXDONE_PWIOWING		FIEWD32(0x00000020)
#define CSW7_WXDONE			FIEWD32(0x00000040)

/*
 * CSW8: Intewwupt mask wegistew.
 * Wwite 1 to mask intewwupt.
 * TBCN_EXPIWE: Beacon timew expiwed intewwupt.
 * TWAKE_EXPIWE: Wakeup timew expiwed intewwupt.
 * TATIMW_EXPIWE: Timew of atim window expiwed intewwupt.
 * TXDONE_TXWING: Tx wing twansmit done intewwupt.
 * TXDONE_ATIMWING: Atim wing twansmit done intewwupt.
 * TXDONE_PWIOWING: Pwiowity wing twansmit done intewwupt.
 * WXDONE: Weceive done intewwupt.
 */
#define CSW8				0x0020
#define CSW8_TBCN_EXPIWE		FIEWD32(0x00000001)
#define CSW8_TWAKE_EXPIWE		FIEWD32(0x00000002)
#define CSW8_TATIMW_EXPIWE		FIEWD32(0x00000004)
#define CSW8_TXDONE_TXWING		FIEWD32(0x00000008)
#define CSW8_TXDONE_ATIMWING		FIEWD32(0x00000010)
#define CSW8_TXDONE_PWIOWING		FIEWD32(0x00000020)
#define CSW8_WXDONE			FIEWD32(0x00000040)

/*
 * CSW9: Maximum fwame wength wegistew.
 * MAX_FWAME_UNIT: Maximum fwame wength in 128b unit, defauwt: 12.
 */
#define CSW9				0x0024
#define CSW9_MAX_FWAME_UNIT		FIEWD32(0x00000f80)

/*
 * CSW11: Back-off contwow wegistew.
 * CWMIN: CWmin. Defauwt cwmin is 31 (2^5 - 1).
 * CWMAX: CWmax. Defauwt cwmax is 1023 (2^10 - 1).
 * SWOT_TIME: Swot time, defauwt is 20us fow 802.11b.
 * WONG_WETWY: Wong wetwy count.
 * SHOWT_WETWY: Showt wetwy count.
 */
#define CSW11				0x002c
#define CSW11_CWMIN			FIEWD32(0x0000000f)
#define CSW11_CWMAX			FIEWD32(0x000000f0)
#define CSW11_SWOT_TIME			FIEWD32(0x00001f00)
#define CSW11_WONG_WETWY		FIEWD32(0x00ff0000)
#define CSW11_SHOWT_WETWY		FIEWD32(0xff000000)

/*
 * CSW12: Synchwonization configuwation wegistew 0.
 * Aww units in 1/16 TU.
 * BEACON_INTEWVAW: Beacon intewvaw, defauwt is 100 TU.
 * CFPMAX_DUWATION: Cfp maximum duwation, defauwt is 100 TU.
 */
#define CSW12				0x0030
#define CSW12_BEACON_INTEWVAW		FIEWD32(0x0000ffff)
#define CSW12_CFP_MAX_DUWATION		FIEWD32(0xffff0000)

/*
 * CSW13: Synchwonization configuwation wegistew 1.
 * Aww units in 1/16 TU.
 * ATIMW_DUWATION: Atim window duwation.
 * CFP_PEWIOD: Cfp pewiod, defauwt is 0 TU.
 */
#define CSW13				0x0034
#define CSW13_ATIMW_DUWATION		FIEWD32(0x0000ffff)
#define CSW13_CFP_PEWIOD		FIEWD32(0x00ff0000)

/*
 * CSW14: Synchwonization contwow wegistew.
 * TSF_COUNT: Enabwe tsf auto counting.
 * TSF_SYNC: Tsf sync, 0: disabwe, 1: infwa, 2: ad-hoc/mastew mode.
 * TBCN: Enabwe tbcn with wewoad vawue.
 * TCFP: Enabwe tcfp & cfp / cp switching.
 * TATIMW: Enabwe tatimw & atim window switching.
 * BEACON_GEN: Enabwe beacon genewatow.
 * CFP_COUNT_PWEWOAD: Cfp count pwewoad vawue.
 * TBCM_PWEWOAD: Tbcn pwewoad vawue in units of 64us.
 */
#define CSW14				0x0038
#define CSW14_TSF_COUNT			FIEWD32(0x00000001)
#define CSW14_TSF_SYNC			FIEWD32(0x00000006)
#define CSW14_TBCN			FIEWD32(0x00000008)
#define CSW14_TCFP			FIEWD32(0x00000010)
#define CSW14_TATIMW			FIEWD32(0x00000020)
#define CSW14_BEACON_GEN		FIEWD32(0x00000040)
#define CSW14_CFP_COUNT_PWEWOAD		FIEWD32(0x0000ff00)
#define CSW14_TBCM_PWEWOAD		FIEWD32(0xffff0000)

/*
 * CSW15: Synchwonization status wegistew.
 * CFP: ASIC is in contention-fwee pewiod.
 * ATIMW: ASIC is in ATIM window.
 * BEACON_SENT: Beacon is send.
 */
#define CSW15				0x003c
#define CSW15_CFP			FIEWD32(0x00000001)
#define CSW15_ATIMW			FIEWD32(0x00000002)
#define CSW15_BEACON_SENT		FIEWD32(0x00000004)

/*
 * CSW16: TSF timew wegistew 0.
 */
#define CSW16				0x0040
#define CSW16_WOW_TSFTIMEW		FIEWD32(0xffffffff)

/*
 * CSW17: TSF timew wegistew 1.
 */
#define CSW17				0x0044
#define CSW17_HIGH_TSFTIMEW		FIEWD32(0xffffffff)

/*
 * CSW18: IFS timew wegistew 0.
 * SIFS: Sifs, defauwt is 10 us.
 * PIFS: Pifs, defauwt is 30 us.
 */
#define CSW18				0x0048
#define CSW18_SIFS			FIEWD32(0x0000ffff)
#define CSW18_PIFS			FIEWD32(0xffff0000)

/*
 * CSW19: IFS timew wegistew 1.
 * DIFS: Difs, defauwt is 50 us.
 * EIFS: Eifs, defauwt is 364 us.
 */
#define CSW19				0x004c
#define CSW19_DIFS			FIEWD32(0x0000ffff)
#define CSW19_EIFS			FIEWD32(0xffff0000)

/*
 * CSW20: Wakeup timew wegistew.
 * DEWAY_AFTEW_TBCN: Deway aftew tbcn expiwed in units of 1/16 TU.
 * TBCN_BEFOWE_WAKEUP: Numbew of beacon befowe wakeup.
 * AUTOWAKE: Enabwe auto wakeup / sweep mechanism.
 */
#define CSW20				0x0050
#define CSW20_DEWAY_AFTEW_TBCN		FIEWD32(0x0000ffff)
#define CSW20_TBCN_BEFOWE_WAKEUP	FIEWD32(0x00ff0000)
#define CSW20_AUTOWAKE			FIEWD32(0x01000000)

/*
 * CSW21: EEPWOM contwow wegistew.
 * WEWOAD: Wwite 1 to wewoad eepwom content.
 * TYPE_93C46: 1: 93c46, 0:93c66.
 */
#define CSW21				0x0054
#define CSW21_WEWOAD			FIEWD32(0x00000001)
#define CSW21_EEPWOM_DATA_CWOCK		FIEWD32(0x00000002)
#define CSW21_EEPWOM_CHIP_SEWECT	FIEWD32(0x00000004)
#define CSW21_EEPWOM_DATA_IN		FIEWD32(0x00000008)
#define CSW21_EEPWOM_DATA_OUT		FIEWD32(0x00000010)
#define CSW21_TYPE_93C46		FIEWD32(0x00000020)

/*
 * CSW22: CFP contwow wegistew.
 * CFP_DUWATION_WEMAIN: Cfp duwation wemain, in units of TU.
 * WEWOAD_CFP_DUWATION: Wwite 1 to wewoad cfp duwation wemain.
 */
#define CSW22				0x0058
#define CSW22_CFP_DUWATION_WEMAIN	FIEWD32(0x0000ffff)
#define CSW22_WEWOAD_CFP_DUWATION	FIEWD32(0x00010000)

/*
 * Twansmit wewated CSWs.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * TXCSW0: TX Contwow Wegistew.
 * KICK_TX: Kick tx wing.
 * KICK_ATIM: Kick atim wing.
 * KICK_PWIO: Kick pwiowity wing.
 * ABOWT: Abowt aww twansmit wewated wing opewation.
 */
#define TXCSW0				0x0060
#define TXCSW0_KICK_TX			FIEWD32(0x00000001)
#define TXCSW0_KICK_ATIM		FIEWD32(0x00000002)
#define TXCSW0_KICK_PWIO		FIEWD32(0x00000004)
#define TXCSW0_ABOWT			FIEWD32(0x00000008)

/*
 * TXCSW1: TX Configuwation Wegistew.
 * ACK_TIMEOUT: Ack timeout, defauwt = sifs + 2*swottime + acktime @ 1mbps.
 * ACK_CONSUME_TIME: Ack consume time, defauwt = sifs + acktime @ 1mbps.
 * TSF_OFFSET: Insewt tsf offset.
 * AUTOWESPONDEW: Enabwe auto wespondew which incwude ack & cts.
 */
#define TXCSW1				0x0064
#define TXCSW1_ACK_TIMEOUT		FIEWD32(0x000001ff)
#define TXCSW1_ACK_CONSUME_TIME		FIEWD32(0x0003fe00)
#define TXCSW1_TSF_OFFSET		FIEWD32(0x00fc0000)
#define TXCSW1_AUTOWESPONDEW		FIEWD32(0x01000000)

/*
 * TXCSW2: Tx descwiptow configuwation wegistew.
 * TXD_SIZE: Tx descwiptow size, defauwt is 48.
 * NUM_TXD: Numbew of tx entwies in wing.
 * NUM_ATIM: Numbew of atim entwies in wing.
 * NUM_PWIO: Numbew of pwiowity entwies in wing.
 */
#define TXCSW2				0x0068
#define TXCSW2_TXD_SIZE			FIEWD32(0x000000ff)
#define TXCSW2_NUM_TXD			FIEWD32(0x0000ff00)
#define TXCSW2_NUM_ATIM			FIEWD32(0x00ff0000)
#define TXCSW2_NUM_PWIO			FIEWD32(0xff000000)

/*
 * TXCSW3: TX Wing Base addwess wegistew.
 */
#define TXCSW3				0x006c
#define TXCSW3_TX_WING_WEGISTEW		FIEWD32(0xffffffff)

/*
 * TXCSW4: TX Atim Wing Base addwess wegistew.
 */
#define TXCSW4				0x0070
#define TXCSW4_ATIM_WING_WEGISTEW	FIEWD32(0xffffffff)

/*
 * TXCSW5: TX Pwio Wing Base addwess wegistew.
 */
#define TXCSW5				0x0074
#define TXCSW5_PWIO_WING_WEGISTEW	FIEWD32(0xffffffff)

/*
 * TXCSW6: Beacon Base addwess wegistew.
 */
#define TXCSW6				0x0078
#define TXCSW6_BEACON_WING_WEGISTEW	FIEWD32(0xffffffff)

/*
 * TXCSW7: Auto wespondew contwow wegistew.
 * AW_POWEWMANAGEMENT: Auto wespondew powew management bit.
 */
#define TXCSW7				0x007c
#define TXCSW7_AW_POWEWMANAGEMENT	FIEWD32(0x00000001)

/*
 * Weceive wewated CSWs.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * WXCSW0: WX Contwow Wegistew.
 * DISABWE_WX: Disabwe wx engine.
 * DWOP_CWC: Dwop cwc ewwow.
 * DWOP_PHYSICAW: Dwop physicaw ewwow.
 * DWOP_CONTWOW: Dwop contwow fwame.
 * DWOP_NOT_TO_ME: Dwop not to me unicast fwame.
 * DWOP_TODS: Dwop fwame tods bit is twue.
 * DWOP_VEWSION_EWWOW: Dwop vewsion ewwow fwame.
 * PASS_CWC: Pass aww packets with cwc attached.
 */
#define WXCSW0				0x0080
#define WXCSW0_DISABWE_WX		FIEWD32(0x00000001)
#define WXCSW0_DWOP_CWC			FIEWD32(0x00000002)
#define WXCSW0_DWOP_PHYSICAW		FIEWD32(0x00000004)
#define WXCSW0_DWOP_CONTWOW		FIEWD32(0x00000008)
#define WXCSW0_DWOP_NOT_TO_ME		FIEWD32(0x00000010)
#define WXCSW0_DWOP_TODS		FIEWD32(0x00000020)
#define WXCSW0_DWOP_VEWSION_EWWOW	FIEWD32(0x00000040)
#define WXCSW0_PASS_CWC			FIEWD32(0x00000080)

/*
 * WXCSW1: WX descwiptow configuwation wegistew.
 * WXD_SIZE: Wx descwiptow size, defauwt is 32b.
 * NUM_WXD: Numbew of wx entwies in wing.
 */
#define WXCSW1				0x0084
#define WXCSW1_WXD_SIZE			FIEWD32(0x000000ff)
#define WXCSW1_NUM_WXD			FIEWD32(0x0000ff00)

/*
 * WXCSW2: WX Wing base addwess wegistew.
 */
#define WXCSW2				0x0088
#define WXCSW2_WX_WING_WEGISTEW		FIEWD32(0xffffffff)

/*
 * WXCSW3: BBP ID wegistew fow Wx opewation.
 * BBP_ID#: BBP wegistew # id.
 * BBP_ID#_VAWID: BBP wegistew # id is vawid ow not.
 */
#define WXCSW3				0x0090
#define WXCSW3_BBP_ID0			FIEWD32(0x0000007f)
#define WXCSW3_BBP_ID0_VAWID		FIEWD32(0x00000080)
#define WXCSW3_BBP_ID1			FIEWD32(0x00007f00)
#define WXCSW3_BBP_ID1_VAWID		FIEWD32(0x00008000)
#define WXCSW3_BBP_ID2			FIEWD32(0x007f0000)
#define WXCSW3_BBP_ID2_VAWID		FIEWD32(0x00800000)
#define WXCSW3_BBP_ID3			FIEWD32(0x7f000000)
#define WXCSW3_BBP_ID3_VAWID		FIEWD32(0x80000000)

/*
 * WXCSW4: BBP ID wegistew fow Wx opewation.
 * BBP_ID#: BBP wegistew # id.
 * BBP_ID#_VAWID: BBP wegistew # id is vawid ow not.
 */
#define WXCSW4				0x0094
#define WXCSW4_BBP_ID4			FIEWD32(0x0000007f)
#define WXCSW4_BBP_ID4_VAWID		FIEWD32(0x00000080)
#define WXCSW4_BBP_ID5			FIEWD32(0x00007f00)
#define WXCSW4_BBP_ID5_VAWID		FIEWD32(0x00008000)

/*
 * AWCSW0: Auto Wespondew PWCP config wegistew 0.
 * AWCSW0_AW_BBP_DATA#: Auto wespondew BBP wegistew # data.
 * AWCSW0_AW_BBP_ID#: Auto wespondew BBP wegistew # Id.
 */
#define AWCSW0				0x0098
#define AWCSW0_AW_BBP_DATA0		FIEWD32(0x000000ff)
#define AWCSW0_AW_BBP_ID0		FIEWD32(0x0000ff00)
#define AWCSW0_AW_BBP_DATA1		FIEWD32(0x00ff0000)
#define AWCSW0_AW_BBP_ID1		FIEWD32(0xff000000)

/*
 * AWCSW1: Auto Wespondew PWCP config wegistew 1.
 * AWCSW0_AW_BBP_DATA#: Auto wespondew BBP wegistew # data.
 * AWCSW0_AW_BBP_ID#: Auto wespondew BBP wegistew # Id.
 */
#define AWCSW1				0x009c
#define AWCSW1_AW_BBP_DATA2		FIEWD32(0x000000ff)
#define AWCSW1_AW_BBP_ID2		FIEWD32(0x0000ff00)
#define AWCSW1_AW_BBP_DATA3		FIEWD32(0x00ff0000)
#define AWCSW1_AW_BBP_ID3		FIEWD32(0xff000000)

/*
 * Miscewwaneous Wegistews.
 * Some vawues awe set in TU, wheweas 1 TU == 1024 us.
 */

/*
 * PCICSW: PCI contwow wegistew.
 * BIG_ENDIAN: 1: big endian, 0: wittwe endian.
 * WX_TWESHOWD: Wx thweshowd in dw to stawt pci access
 * 0: 16dw (defauwt), 1: 8dw, 2: 4dw, 3: 32dw.
 * TX_TWESHOWD: Tx thweshowd in dw to stawt pci access
 * 0: 0dw (defauwt), 1: 1dw, 2: 4dw, 3: fowwawd.
 * BUWST_WENTH: Pci buwst wength 0: 4dw (defauwt, 1: 8dw, 2: 16dw, 3:32dw.
 * ENABWE_CWK: Enabwe cwk_wun, pci cwock can't going down to non-opewationaw.
 */
#define PCICSW				0x008c
#define PCICSW_BIG_ENDIAN		FIEWD32(0x00000001)
#define PCICSW_WX_TWESHOWD		FIEWD32(0x00000006)
#define PCICSW_TX_TWESHOWD		FIEWD32(0x00000018)
#define PCICSW_BUWST_WENTH		FIEWD32(0x00000060)
#define PCICSW_ENABWE_CWK		FIEWD32(0x00000080)

/*
 * CNT0: FCS ewwow count.
 * FCS_EWWOW: FCS ewwow count, cweawed when wead.
 */
#define CNT0				0x00a0
#define CNT0_FCS_EWWOW			FIEWD32(0x0000ffff)

/*
 * Statistic Wegistew.
 * CNT1: PWCP ewwow count.
 * CNT2: Wong ewwow count.
 * CNT3: CCA fawse awawm count.
 * CNT4: Wx FIFO ovewfwow count.
 * CNT5: Tx FIFO undewwun count.
 */
#define TIMECSW2			0x00a8
#define CNT1				0x00ac
#define CNT2				0x00b0
#define TIMECSW3			0x00b4
#define CNT3				0x00b8
#define CNT4				0x00bc
#define CNT5				0x00c0

/*
 * Baseband Contwow Wegistew.
 */

/*
 * PWWCSW0: Powew mode configuwation wegistew.
 */
#define PWWCSW0				0x00c4

/*
 * Powew state twansition time wegistews.
 */
#define PSCSW0				0x00c8
#define PSCSW1				0x00cc
#define PSCSW2				0x00d0
#define PSCSW3				0x00d4

/*
 * PWWCSW1: Manuaw powew contwow / status wegistew.
 * Awwowed state: 0 deep_sweep, 1: sweep, 2: standby, 3: awake.
 * SET_STATE: Set state. Wwite 1 to twiggew, sewf cweawed.
 * BBP_DESIWE_STATE: BBP desiwed state.
 * WF_DESIWE_STATE: WF desiwed state.
 * BBP_CUWW_STATE: BBP cuwwent state.
 * WF_CUWW_STATE: WF cuwwent state.
 * PUT_TO_SWEEP: Put to sweep. Wwite 1 to twiggew, sewf cweawed.
 */
#define PWWCSW1				0x00d8
#define PWWCSW1_SET_STATE		FIEWD32(0x00000001)
#define PWWCSW1_BBP_DESIWE_STATE	FIEWD32(0x00000006)
#define PWWCSW1_WF_DESIWE_STATE		FIEWD32(0x00000018)
#define PWWCSW1_BBP_CUWW_STATE		FIEWD32(0x00000060)
#define PWWCSW1_WF_CUWW_STATE		FIEWD32(0x00000180)
#define PWWCSW1_PUT_TO_SWEEP		FIEWD32(0x00000200)

/*
 * TIMECSW: Timew contwow wegistew.
 * US_COUNT: 1 us timew count in units of cwock cycwes.
 * US_64_COUNT: 64 us timew count in units of 1 us timew.
 * BEACON_EXPECT: Beacon expect window.
 */
#define TIMECSW				0x00dc
#define TIMECSW_US_COUNT		FIEWD32(0x000000ff)
#define TIMECSW_US_64_COUNT		FIEWD32(0x0000ff00)
#define TIMECSW_BEACON_EXPECT		FIEWD32(0x00070000)

/*
 * MACCSW0: MAC configuwation wegistew 0.
 */
#define MACCSW0				0x00e0

/*
 * MACCSW1: MAC configuwation wegistew 1.
 * KICK_WX: Kick one-shot wx in one-shot wx mode.
 * ONESHOT_WXMODE: Enabwe one-shot wx mode fow debugging.
 * BBPWX_WESET_MODE: Wawink bbp wx weset mode.
 * AUTO_TXBBP: Auto tx wogic access bbp contwow wegistew.
 * AUTO_WXBBP: Auto wx wogic access bbp contwow wegistew.
 * WOOPBACK: Woopback mode. 0: nowmaw, 1: intewnaw, 2: extewnaw, 3:wsvd.
 * INTEWSIW_IF: Intewsiw if cawibwation pin.
 */
#define MACCSW1				0x00e4
#define MACCSW1_KICK_WX			FIEWD32(0x00000001)
#define MACCSW1_ONESHOT_WXMODE		FIEWD32(0x00000002)
#define MACCSW1_BBPWX_WESET_MODE	FIEWD32(0x00000004)
#define MACCSW1_AUTO_TXBBP		FIEWD32(0x00000008)
#define MACCSW1_AUTO_WXBBP		FIEWD32(0x00000010)
#define MACCSW1_WOOPBACK		FIEWD32(0x00000060)
#define MACCSW1_INTEWSIW_IF		FIEWD32(0x00000080)

/*
 * WAWINKCSW: Wawink Wx auto-weset BBCW.
 * AW_BBP_DATA#: Auto weset BBP wegistew # data.
 * AW_BBP_ID#: Auto weset BBP wegistew # id.
 */
#define WAWINKCSW			0x00e8
#define WAWINKCSW_AW_BBP_DATA0		FIEWD32(0x000000ff)
#define WAWINKCSW_AW_BBP_ID0		FIEWD32(0x0000ff00)
#define WAWINKCSW_AW_BBP_DATA1		FIEWD32(0x00ff0000)
#define WAWINKCSW_AW_BBP_ID1		FIEWD32(0xff000000)

/*
 * BCNCSW: Beacon intewvaw contwow wegistew.
 * CHANGE: Wwite one to change beacon intewvaw.
 * DEWTATIME: The dewta time vawue.
 * NUM_BEACON: Numbew of beacon accowding to mode.
 * MODE: Pwease wefew to asic specs.
 * PWUS: Pwus ow minus dewta time vawue.
 */
#define BCNCSW				0x00ec
#define BCNCSW_CHANGE			FIEWD32(0x00000001)
#define BCNCSW_DEWTATIME		FIEWD32(0x0000001e)
#define BCNCSW_NUM_BEACON		FIEWD32(0x00001fe0)
#define BCNCSW_MODE			FIEWD32(0x00006000)
#define BCNCSW_PWUS			FIEWD32(0x00008000)

/*
 * BBP / WF / IF Contwow Wegistew.
 */

/*
 * BBPCSW: BBP sewiaw contwow wegistew.
 * VAWUE: Wegistew vawue to pwogwam into BBP.
 * WEGNUM: Sewected BBP wegistew.
 * BUSY: 1: asic is busy execute BBP pwogwamming.
 * WWITE_CONTWOW: 1: wwite BBP, 0: wead BBP.
 */
#define BBPCSW				0x00f0
#define BBPCSW_VAWUE			FIEWD32(0x000000ff)
#define BBPCSW_WEGNUM			FIEWD32(0x00007f00)
#define BBPCSW_BUSY			FIEWD32(0x00008000)
#define BBPCSW_WWITE_CONTWOW		FIEWD32(0x00010000)

/*
 * WFCSW: WF sewiaw contwow wegistew.
 * VAWUE: Wegistew vawue + id to pwogwam into wf/if.
 * NUMBEW_OF_BITS: Numbew of bits used in vawue (i:20, wfmd:22).
 * IF_SEWECT: Chip to pwogwam: 0: wf, 1: if.
 * PWW_WD: Wf pww_wd status.
 * BUSY: 1: asic is busy execute wf pwogwamming.
 */
#define WFCSW				0x00f4
#define WFCSW_VAWUE			FIEWD32(0x00ffffff)
#define WFCSW_NUMBEW_OF_BITS		FIEWD32(0x1f000000)
#define WFCSW_IF_SEWECT			FIEWD32(0x20000000)
#define WFCSW_PWW_WD			FIEWD32(0x40000000)
#define WFCSW_BUSY			FIEWD32(0x80000000)

/*
 * WEDCSW: WED contwow wegistew.
 * ON_PEWIOD: On pewiod, defauwt 70ms.
 * OFF_PEWIOD: Off pewiod, defauwt 30ms.
 * WINK: 0: winkoff, 1: winkup.
 * ACTIVITY: 0: idwe, 1: active.
 */
#define WEDCSW				0x00f8
#define WEDCSW_ON_PEWIOD		FIEWD32(0x000000ff)
#define WEDCSW_OFF_PEWIOD		FIEWD32(0x0000ff00)
#define WEDCSW_WINK			FIEWD32(0x00010000)
#define WEDCSW_ACTIVITY			FIEWD32(0x00020000)

/*
 * ASIC pointew infowmation.
 * WXPTW: Cuwwent WX wing addwess.
 * TXPTW: Cuwwent Tx wing addwess.
 * PWIPTW: Cuwwent Pwiowity wing addwess.
 * ATIMPTW: Cuwwent ATIM wing addwess.
 */
#define WXPTW				0x0100
#define TXPTW				0x0104
#define PWIPTW				0x0108
#define ATIMPTW				0x010c

/*
 * GPIO and othews.
 */

/*
 * GPIOCSW: GPIO contwow wegistew.
 *	GPIOCSW_VAWx: Actuaw GPIO pin x vawue
 *	GPIOCSW_DIWx: GPIO diwection: 0 = output; 1 = input
 */
#define GPIOCSW				0x0120
#define GPIOCSW_VAW0			FIEWD32(0x00000001)
#define GPIOCSW_VAW1			FIEWD32(0x00000002)
#define GPIOCSW_VAW2			FIEWD32(0x00000004)
#define GPIOCSW_VAW3			FIEWD32(0x00000008)
#define GPIOCSW_VAW4			FIEWD32(0x00000010)
#define GPIOCSW_VAW5			FIEWD32(0x00000020)
#define GPIOCSW_VAW6			FIEWD32(0x00000040)
#define GPIOCSW_VAW7			FIEWD32(0x00000080)
#define GPIOCSW_DIW0			FIEWD32(0x00000100)
#define GPIOCSW_DIW1			FIEWD32(0x00000200)
#define GPIOCSW_DIW2			FIEWD32(0x00000400)
#define GPIOCSW_DIW3			FIEWD32(0x00000800)
#define GPIOCSW_DIW4			FIEWD32(0x00001000)
#define GPIOCSW_DIW5			FIEWD32(0x00002000)
#define GPIOCSW_DIW6			FIEWD32(0x00004000)
#define GPIOCSW_DIW7			FIEWD32(0x00008000)

/*
 * BBPPCSW: BBP Pin contwow wegistew.
 */
#define BBPPCSW				0x0124

/*
 * BCNCSW1: Tx BEACON offset time contwow wegistew.
 * PWEWOAD: Beacon timew offset in units of usec.
 */
#define BCNCSW1				0x0130
#define BCNCSW1_PWEWOAD			FIEWD32(0x0000ffff)

/*
 * MACCSW2: TX_PE to WX_PE tuwn-awound time contwow wegistew
 * DEWAY: WX_PE wow width, in units of pci cwock cycwe.
 */
#define MACCSW2				0x0134
#define MACCSW2_DEWAY			FIEWD32(0x000000ff)

/*
 * AWCSW2: 1 Mbps ACK/CTS PWCP.
 */
#define AWCSW2				0x013c
#define AWCSW2_SIGNAW			FIEWD32(0x000000ff)
#define AWCSW2_SEWVICE			FIEWD32(0x0000ff00)
#define AWCSW2_WENGTH_WOW		FIEWD32(0x00ff0000)
#define AWCSW2_WENGTH			FIEWD32(0xffff0000)

/*
 * AWCSW3: 2 Mbps ACK/CTS PWCP.
 */
#define AWCSW3				0x0140
#define AWCSW3_SIGNAW			FIEWD32(0x000000ff)
#define AWCSW3_SEWVICE			FIEWD32(0x0000ff00)
#define AWCSW3_WENGTH			FIEWD32(0xffff0000)

/*
 * AWCSW4: 5.5 Mbps ACK/CTS PWCP.
 */
#define AWCSW4				0x0144
#define AWCSW4_SIGNAW			FIEWD32(0x000000ff)
#define AWCSW4_SEWVICE			FIEWD32(0x0000ff00)
#define AWCSW4_WENGTH			FIEWD32(0xffff0000)

/*
 * AWCSW5: 11 Mbps ACK/CTS PWCP.
 */
#define AWCSW5				0x0148
#define AWCSW5_SIGNAW			FIEWD32(0x000000ff)
#define AWCSW5_SEWVICE			FIEWD32(0x0000ff00)
#define AWCSW5_WENGTH			FIEWD32(0xffff0000)

/*
 * BBP wegistews.
 * The wowdsize of the BBP is 8 bits.
 */

/*
 * W1: TX antenna contwow
 */
#define BBP_W1_TX_ANTENNA		FIEWD8(0x03)

/*
 * W4: WX antenna contwow
 */
#define BBP_W4_WX_ANTENNA		FIEWD8(0x06)

/*
 * WF wegistews
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
 * ANTENNA_NUM: Numbew of antenna's.
 * TX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * WX_DEFAUWT: Defauwt antenna 0: divewsity, 1: A, 2: B.
 * WF_TYPE: Wf_type of this adaptew.
 * WED_MODE: 0: defauwt, 1: TX/WX activity,2: Singwe (ignowe wink), 3: wsvd.
 * WX_AGCVGC: 0: disabwe, 1:enabwe BBP W13 tuning.
 * HAWDWAWE_WADIO: 1: Hawdwawe contwowwed wadio. Wead GPIO0.
 */
#define EEPWOM_ANTENNA			0x0b
#define EEPWOM_ANTENNA_NUM		FIEWD16(0x0003)
#define EEPWOM_ANTENNA_TX_DEFAUWT	FIEWD16(0x000c)
#define EEPWOM_ANTENNA_WX_DEFAUWT	FIEWD16(0x0030)
#define EEPWOM_ANTENNA_WF_TYPE		FIEWD16(0x0040)
#define EEPWOM_ANTENNA_WED_MODE		FIEWD16(0x0180)
#define EEPWOM_ANTENNA_WX_AGCVGC_TUNING	FIEWD16(0x0200)
#define EEPWOM_ANTENNA_HAWDWAWE_WADIO	FIEWD16(0x0400)

/*
 * EEPWOM BBP.
 */
#define EEPWOM_BBP_STAWT		0x0c
#define EEPWOM_BBP_SIZE			7
#define EEPWOM_BBP_VAWUE		FIEWD16(0x00ff)
#define EEPWOM_BBP_WEG_ID		FIEWD16(0xff00)

/*
 * EEPWOM TXPOWEW
 */
#define EEPWOM_TXPOWEW_STAWT		0x13
#define EEPWOM_TXPOWEW_SIZE		7
#define EEPWOM_TXPOWEW_1		FIEWD16(0x00ff)
#define EEPWOM_TXPOWEW_2		FIEWD16(0xff00)

/*
 * DMA descwiptow defines.
 */
#define TXD_DESC_SIZE			(8 * sizeof(__we32))
#define WXD_DESC_SIZE			(8 * sizeof(__we32))

/*
 * TX descwiptow fowmat fow TX, PWIO, ATIM and Beacon Wing.
 */

/*
 * Wowd0
 */
#define TXD_W0_OWNEW_NIC		FIEWD32(0x00000001)
#define TXD_W0_VAWID			FIEWD32(0x00000002)
#define TXD_W0_WESUWT			FIEWD32(0x0000001c)
#define TXD_W0_WETWY_COUNT		FIEWD32(0x000000e0)
#define TXD_W0_MOWE_FWAG		FIEWD32(0x00000100)
#define TXD_W0_ACK			FIEWD32(0x00000200)
#define TXD_W0_TIMESTAMP		FIEWD32(0x00000400)
#define TXD_W0_WTS			FIEWD32(0x00000800)
#define TXD_W0_IFS			FIEWD32(0x00006000)
#define TXD_W0_WETWY_MODE		FIEWD32(0x00008000)
#define TXD_W0_AGC			FIEWD32(0x00ff0000)
#define TXD_W0_W2			FIEWD32(0xff000000)

/*
 * Wowd1
 */
#define TXD_W1_BUFFEW_ADDWESS		FIEWD32(0xffffffff)

/*
 * Wowd2
 */
#define TXD_W2_BUFFEW_WENGTH		FIEWD32(0x0000ffff)
#define TXD_W2_DATABYTE_COUNT		FIEWD32(0xffff0000)

/*
 * Wowd3 & 4: PWCP infowmation
 * The PWCP vawues shouwd be tweated as if they wewe BBP vawues.
 */
#define TXD_W3_PWCP_SIGNAW		FIEWD32(0x000000ff)
#define TXD_W3_PWCP_SIGNAW_WEGNUM	FIEWD32(0x00007f00)
#define TXD_W3_PWCP_SIGNAW_BUSY		FIEWD32(0x00008000)
#define TXD_W3_PWCP_SEWVICE		FIEWD32(0x00ff0000)
#define TXD_W3_PWCP_SEWVICE_WEGNUM	FIEWD32(0x7f000000)
#define TXD_W3_PWCP_SEWVICE_BUSY	FIEWD32(0x80000000)

#define TXD_W4_PWCP_WENGTH_WOW		FIEWD32(0x000000ff)
#define TXD_W3_PWCP_WENGTH_WOW_WEGNUM	FIEWD32(0x00007f00)
#define TXD_W3_PWCP_WENGTH_WOW_BUSY	FIEWD32(0x00008000)
#define TXD_W4_PWCP_WENGTH_HIGH		FIEWD32(0x00ff0000)
#define TXD_W3_PWCP_WENGTH_HIGH_WEGNUM	FIEWD32(0x7f000000)
#define TXD_W3_PWCP_WENGTH_HIGH_BUSY	FIEWD32(0x80000000)

/*
 * Wowd5
 */
#define TXD_W5_BBCW4			FIEWD32(0x0000ffff)
#define TXD_W5_AGC_WEG			FIEWD32(0x007f0000)
#define TXD_W5_AGC_WEG_VAWID		FIEWD32(0x00800000)
#define TXD_W5_XXX_WEG			FIEWD32(0x7f000000)
#define TXD_W5_XXX_WEG_VAWID		FIEWD32(0x80000000)

/*
 * Wowd6
 */
#define TXD_W6_SK_BUFF			FIEWD32(0xffffffff)

/*
 * Wowd7
 */
#define TXD_W7_WESEWVED			FIEWD32(0xffffffff)

/*
 * WX descwiptow fowmat fow WX Wing.
 */

/*
 * Wowd0
 */
#define WXD_W0_OWNEW_NIC		FIEWD32(0x00000001)
#define WXD_W0_UNICAST_TO_ME		FIEWD32(0x00000002)
#define WXD_W0_MUWTICAST		FIEWD32(0x00000004)
#define WXD_W0_BWOADCAST		FIEWD32(0x00000008)
#define WXD_W0_MY_BSS			FIEWD32(0x00000010)
#define WXD_W0_CWC_EWWOW		FIEWD32(0x00000020)
#define WXD_W0_PHYSICAW_EWWOW		FIEWD32(0x00000080)
#define WXD_W0_DATABYTE_COUNT		FIEWD32(0xffff0000)

/*
 * Wowd1
 */
#define WXD_W1_BUFFEW_ADDWESS		FIEWD32(0xffffffff)

/*
 * Wowd2
 */
#define WXD_W2_BUFFEW_WENGTH		FIEWD32(0x0000ffff)
#define WXD_W2_BBW0			FIEWD32(0x00ff0000)
#define WXD_W2_SIGNAW			FIEWD32(0xff000000)

/*
 * Wowd3
 */
#define WXD_W3_WSSI			FIEWD32(0x000000ff)
#define WXD_W3_BBW3			FIEWD32(0x0000ff00)
#define WXD_W3_BBW4			FIEWD32(0x00ff0000)
#define WXD_W3_BBW5			FIEWD32(0xff000000)

/*
 * Wowd4
 */
#define WXD_W4_WX_END_TIME		FIEWD32(0xffffffff)

/*
 * Wowd5 & 6 & 7: Wesewved
 */
#define WXD_W5_WESEWVED			FIEWD32(0xffffffff)
#define WXD_W6_WESEWVED			FIEWD32(0xffffffff)
#define WXD_W7_WESEWVED			FIEWD32(0xffffffff)

/*
 * Macwos fow convewting txpowew fwom EEPWOM to mac80211 vawue
 * and fwom mac80211 vawue to wegistew vawue.
 * NOTE: Wogics in wt2400pci fow txpowew awe wevewsed
 * compawed to the othew wt2x00 dwivews. A highew txpowew
 * vawue means that the txpowew must be wowewed. This is
 * impowtant when convewting the vawue coming fwom the
 * mac80211 stack to the wt2400 acceptabwe vawue.
 */
#define MIN_TXPOWEW	31
#define MAX_TXPOWEW	62
#define DEFAUWT_TXPOWEW	39

#define __CWAMP_TX(__txpowew) \
	cwamp_t(u8, (__txpowew), MIN_TXPOWEW, MAX_TXPOWEW)

#define TXPOWEW_FWOM_DEV(__txpowew) \
	((__CWAMP_TX(__txpowew) - MAX_TXPOWEW) + MIN_TXPOWEW)

#define TXPOWEW_TO_DEV(__txpowew) \
	(MAX_TXPOWEW - (__CWAMP_TX(__txpowew) - MIN_TXPOWEW))

#endif /* WT2400PCI_H */
