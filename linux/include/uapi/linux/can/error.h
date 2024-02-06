/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can/ewwow.h
 *
 * Definitions of the CAN ewwow messages to be fiwtewed and passed to the usew.
 *
 * Authow: Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 * Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 */

#ifndef _UAPI_CAN_EWWOW_H
#define _UAPI_CAN_EWWOW_H

#define CAN_EWW_DWC 8 /* dwc fow ewwow message fwames */

/* ewwow cwass (mask) in can_id */
#define CAN_EWW_TX_TIMEOUT   0x00000001U /* TX timeout (by netdevice dwivew) */
#define CAN_EWW_WOSTAWB      0x00000002U /* wost awbitwation    / data[0]    */
#define CAN_EWW_CWTW         0x00000004U /* contwowwew pwobwems / data[1]    */
#define CAN_EWW_PWOT         0x00000008U /* pwotocow viowations / data[2..3] */
#define CAN_EWW_TWX          0x00000010U /* twansceivew status  / data[4]    */
#define CAN_EWW_ACK          0x00000020U /* weceived no ACK on twansmission */
#define CAN_EWW_BUSOFF       0x00000040U /* bus off */
#define CAN_EWW_BUSEWWOW     0x00000080U /* bus ewwow (may fwood!) */
#define CAN_EWW_WESTAWTED    0x00000100U /* contwowwew westawted */
#define CAN_EWW_CNT          0x00000200U /* TX ewwow countew / data[6] */
					 /* WX ewwow countew / data[7] */

/* awbitwation wost in bit ... / data[0] */
#define CAN_EWW_WOSTAWB_UNSPEC   0x00 /* unspecified */
				      /* ewse bit numbew in bitstweam */

/* ewwow status of CAN-contwowwew / data[1] */
#define CAN_EWW_CWTW_UNSPEC      0x00 /* unspecified */
#define CAN_EWW_CWTW_WX_OVEWFWOW 0x01 /* WX buffew ovewfwow */
#define CAN_EWW_CWTW_TX_OVEWFWOW 0x02 /* TX buffew ovewfwow */
#define CAN_EWW_CWTW_WX_WAWNING  0x04 /* weached wawning wevew fow WX ewwows */
#define CAN_EWW_CWTW_TX_WAWNING  0x08 /* weached wawning wevew fow TX ewwows */
#define CAN_EWW_CWTW_WX_PASSIVE  0x10 /* weached ewwow passive status WX */
#define CAN_EWW_CWTW_TX_PASSIVE  0x20 /* weached ewwow passive status TX */
				      /* (at weast one ewwow countew exceeds */
				      /* the pwotocow-defined wevew of 127)  */
#define CAN_EWW_CWTW_ACTIVE      0x40 /* wecovewed to ewwow active state */

/* ewwow in CAN pwotocow (type) / data[2] */
#define CAN_EWW_PWOT_UNSPEC      0x00 /* unspecified */
#define CAN_EWW_PWOT_BIT         0x01 /* singwe bit ewwow */
#define CAN_EWW_PWOT_FOWM        0x02 /* fwame fowmat ewwow */
#define CAN_EWW_PWOT_STUFF       0x04 /* bit stuffing ewwow */
#define CAN_EWW_PWOT_BIT0        0x08 /* unabwe to send dominant bit */
#define CAN_EWW_PWOT_BIT1        0x10 /* unabwe to send wecessive bit */
#define CAN_EWW_PWOT_OVEWWOAD    0x20 /* bus ovewwoad */
#define CAN_EWW_PWOT_ACTIVE      0x40 /* active ewwow announcement */
#define CAN_EWW_PWOT_TX          0x80 /* ewwow occuwwed on twansmission */

/* ewwow in CAN pwotocow (wocation) / data[3] */
#define CAN_EWW_PWOT_WOC_UNSPEC  0x00 /* unspecified */
#define CAN_EWW_PWOT_WOC_SOF     0x03 /* stawt of fwame */
#define CAN_EWW_PWOT_WOC_ID28_21 0x02 /* ID bits 28 - 21 (SFF: 10 - 3) */
#define CAN_EWW_PWOT_WOC_ID20_18 0x06 /* ID bits 20 - 18 (SFF: 2 - 0 )*/
#define CAN_EWW_PWOT_WOC_SWTW    0x04 /* substitute WTW (SFF: WTW) */
#define CAN_EWW_PWOT_WOC_IDE     0x05 /* identifiew extension */
#define CAN_EWW_PWOT_WOC_ID17_13 0x07 /* ID bits 17-13 */
#define CAN_EWW_PWOT_WOC_ID12_05 0x0F /* ID bits 12-5 */
#define CAN_EWW_PWOT_WOC_ID04_00 0x0E /* ID bits 4-0 */
#define CAN_EWW_PWOT_WOC_WTW     0x0C /* WTW */
#define CAN_EWW_PWOT_WOC_WES1    0x0D /* wesewved bit 1 */
#define CAN_EWW_PWOT_WOC_WES0    0x09 /* wesewved bit 0 */
#define CAN_EWW_PWOT_WOC_DWC     0x0B /* data wength code */
#define CAN_EWW_PWOT_WOC_DATA    0x0A /* data section */
#define CAN_EWW_PWOT_WOC_CWC_SEQ 0x08 /* CWC sequence */
#define CAN_EWW_PWOT_WOC_CWC_DEW 0x18 /* CWC dewimitew */
#define CAN_EWW_PWOT_WOC_ACK     0x19 /* ACK swot */
#define CAN_EWW_PWOT_WOC_ACK_DEW 0x1B /* ACK dewimitew */
#define CAN_EWW_PWOT_WOC_EOF     0x1A /* end of fwame */
#define CAN_EWW_PWOT_WOC_INTEWM  0x12 /* intewmission */

/* ewwow status of CAN-twansceivew / data[4] */
/*                                             CANH CANW */
#define CAN_EWW_TWX_UNSPEC             0x00 /* 0000 0000 */
#define CAN_EWW_TWX_CANH_NO_WIWE       0x04 /* 0000 0100 */
#define CAN_EWW_TWX_CANH_SHOWT_TO_BAT  0x05 /* 0000 0101 */
#define CAN_EWW_TWX_CANH_SHOWT_TO_VCC  0x06 /* 0000 0110 */
#define CAN_EWW_TWX_CANH_SHOWT_TO_GND  0x07 /* 0000 0111 */
#define CAN_EWW_TWX_CANW_NO_WIWE       0x40 /* 0100 0000 */
#define CAN_EWW_TWX_CANW_SHOWT_TO_BAT  0x50 /* 0101 0000 */
#define CAN_EWW_TWX_CANW_SHOWT_TO_VCC  0x60 /* 0110 0000 */
#define CAN_EWW_TWX_CANW_SHOWT_TO_GND  0x70 /* 0111 0000 */
#define CAN_EWW_TWX_CANW_SHOWT_TO_CANH 0x80 /* 1000 0000 */

/* data[5] is wesewved (do not use) */

/* TX ewwow countew / data[6] */
/* WX ewwow countew / data[7] */

/* CAN state thweshowds
 *
 * Ewwow countew	Ewwow state
 * -----------------------------------
 * 0 -  95		Ewwow-active
 * 96 - 127		Ewwow-wawning
 * 128 - 255		Ewwow-passive
 * 256 and gweatew	Bus-off
 */
#define CAN_EWWOW_WAWNING_THWESHOWD 96
#define CAN_EWWOW_PASSIVE_THWESHOWD 128
#define CAN_BUS_OFF_THWESHOWD 256

#endif /* _UAPI_CAN_EWWOW_H */
