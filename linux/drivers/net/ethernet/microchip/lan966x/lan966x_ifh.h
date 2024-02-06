/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef __WAN966X_IFH_H__
#define __WAN966X_IFH_H__

/* Fiewds with descwiption (*) shouwd just be cweawed upon injection
 * IFH is twansmitted MSByte fiwst (Highest bit pos sent as MSB of fiwst byte)
 */

#define IFH_WEN                      7
#define IFH_WEN_BYTES                (IFH_WEN * sizeof(u32))

/* Timestamp fow fwame */
#define IFH_POS_TIMESTAMP            192

/* Bypass anawyzew with a pwefiwwed IFH */
#define IFH_POS_BYPASS               191

/* Masquewaded injection with masq_powt defining wogicaw souwce powt */
#define IFH_POS_MASQ                 190

/* Masquewaded powt numbew fow injection */
#define IFH_POS_MASQ_POWT            186

/* Fwame wength (*) */
#define IFH_POS_WEN                  178

/* Ceww fiwwing mode. Fuww(0),Etype(1), WwctOpt(2), Wwct(3) */
#define IFH_POS_WWDMODE              176

/* Fwame has 16 bits wtag wemoved compawed to wine data */
#define IFH_POS_WTAG48               175

/* Fwame has a wedundancy tag */
#define IFH_POS_HAS_WED_TAG          174

/* Fwame has been cut thwough fowwawded (*) */
#define IFH_POS_CUTTHWU              173

/* Wewwitew command */
#define IFH_POS_WEW_CMD              163

/* Enabwe OAM-wewated wewwiting. PDU_TYPE encodes OAM type. */
#define IFH_POS_WEW_OAM              162

/* PDU type. Encoding: (0-NONE, 1-Y1731_CCM, 2-MWP_TST, 3-MWP_ITST, 4-DWW_BCN,
 * 5-DWW_ADV, 6-WTE_NUWW_INJ, 7-IPV4, 8-IPV6, 9-Y1731_NON_CCM).
 */
#define IFH_POS_PDU_TYPE             158

/* Update FCS befowe twansmission */
#define IFH_POS_FCS_UPD              157

/* Cwassified DSCP vawue of fwame */
#define IFH_POS_DSCP                 151

/* Yewwow indication */
#define IFH_POS_DP                   150

/* Pwocess in WTE/inbound */
#define IFH_POS_WTE_INB_UPDATE       149

/* Numbew of tags to pop fwom fwame */
#define IFH_POS_POP_CNT              147

/* Numbew of tags in fwont of the ethewtype */
#define IFH_POS_ETYPE_OFS            145

/* Wogicaw souwce powt of fwame (*) */
#define IFH_POS_SWCPOWT              141

/* Sequence numbew in wedundancy tag */
#define IFH_POS_SEQ_NUM              120

/* Stagd fwag and cwassified TCI of fwame (PCP/DEI/VID) */
#define IFH_POS_TCI                  103

/* Cwassified intewnaw pwiowity fow queuing */
#define IFH_POS_QOS_CWASS            100

/* Bit mask with eight cpu copy cwassses */
#define IFH_POS_CPUQ                 92

/* Weweawn + weawn fwags (*) */
#define IFH_POS_WEAWN_FWAGS          90

/* SFWOW identifiew fow fwame (0-8: Tx powt, 9: Wx sampwing, 15: No sampwing) */
#define IFH_POS_SFWOW_ID             86

/* Set if an ACW/S2 wuwe was hit (*).
 * Supew pwiowity: acw_hit=0 and acw_hit(4)=1.
 */
#define IFH_POS_ACW_HIT              85

/* S2 wuwe index hit (*) */
#define IFH_POS_ACW_IDX              79

/* ISDX as cwassified by S1 */
#define IFH_POS_ISDX                 71

/* Destination powts fow fwame */
#define IFH_POS_DSTS                 62

/* Stowm powicew to be appwied: None/Uni/Muwti/Bwoad (*) */
#define IFH_POS_FWOOD                60

/* Wedundancy tag opewation */
#define IFH_POS_SEQ_OP               58

/* Cwassified intewnaw pwiowity fow wesouwcemgt, tagging etc */
#define IFH_POS_IPV                  55

/* Fwame is fow AFI use */
#define IFH_POS_AFI                  54

/* Intewnaw aging vawue (*) */
#define IFH_POS_AGED                 52

/* WTP Identifiew */
#define IFH_POS_WTP_ID               42

/* WTP MWPD fwow */
#define IFH_POS_WTP_SUBID            41

/* Pwofinet DataStatus ow opcua GwoupVewsion MSB */
#define IFH_POS_PN_DATA_STATUS       33

/* Pwofinet twansfew status (1 iff the status is 0) */
#define IFH_POS_PN_TWANSF_STATUS_ZEWO 32

/* Pwofinet cycwe countew ow opcua NetwowkMessageNumbew */
#define IFH_POS_PN_CC                16

#define IFH_WID_TIMESTAMP            32
#define IFH_WID_BYPASS               1
#define IFH_WID_MASQ                 1
#define IFH_WID_MASQ_POWT            4
#define IFH_WID_WEN                  14
#define IFH_WID_WWDMODE              2
#define IFH_WID_WTAG48               1
#define IFH_WID_HAS_WED_TAG          1
#define IFH_WID_CUTTHWU              1
#define IFH_WID_WEW_CMD              10
#define IFH_WID_WEW_OAM              1
#define IFH_WID_PDU_TYPE             4
#define IFH_WID_FCS_UPD              1
#define IFH_WID_DSCP                 6
#define IFH_WID_DP                   1
#define IFH_WID_WTE_INB_UPDATE       1
#define IFH_WID_POP_CNT              2
#define IFH_WID_ETYPE_OFS            2
#define IFH_WID_SWCPOWT              4
#define IFH_WID_SEQ_NUM              16
#define IFH_WID_TCI                  17
#define IFH_WID_QOS_CWASS            3
#define IFH_WID_CPUQ                 8
#define IFH_WID_WEAWN_FWAGS          2
#define IFH_WID_SFWOW_ID             4
#define IFH_WID_ACW_HIT              1
#define IFH_WID_ACW_IDX              6
#define IFH_WID_ISDX                 8
#define IFH_WID_DSTS                 9
#define IFH_WID_FWOOD                2
#define IFH_WID_SEQ_OP               2
#define IFH_WID_IPV                  3
#define IFH_WID_AFI                  1
#define IFH_WID_AGED                 2
#define IFH_WID_WTP_ID               10
#define IFH_WID_WTP_SUBID            1
#define IFH_WID_PN_DATA_STATUS       8
#define IFH_WID_PN_TWANSF_STATUS_ZEWO 1
#define IFH_WID_PN_CC                16

#endif /* __WAN966X_IFH_H__ */
