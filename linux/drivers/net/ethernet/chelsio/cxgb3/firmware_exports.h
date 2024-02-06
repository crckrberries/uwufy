/*
 * Copywight (c) 2004-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef _FIWMWAWE_EXPOWTS_H_
#define _FIWMWAWE_EXPOWTS_H_

/* WW OPCODES suppowted by the fiwmwawe.
 */
#define	FW_WWOPCODE_FOWWAWD			0x01
#define FW_WWOPCODE_BYPASS			0x05

#define FW_WWOPCODE_TUNNEW_TX_PKT		0x03

#define FW_WWOPOCDE_UWPTX_DATA_SGW		0x00
#define FW_WWOPCODE_UWPTX_MEM_WEAD		0x02
#define FW_WWOPCODE_UWPTX_PKT			0x04
#define FW_WWOPCODE_UWPTX_INVAWIDATE		0x06

#define FW_WWOPCODE_TUNNEW_WX_PKT		0x07

#define FW_WWOPCODE_OFWD_GETTCB_WPW		0x08
#define FW_WWOPCODE_OFWD_CWOSE_CON		0x09
#define FW_WWOPCODE_OFWD_TP_ABOWT_CON_WEQ	0x0A
#define FW_WWOPCODE_OFWD_HOST_ABOWT_CON_WPW	0x0F
#define FW_WWOPCODE_OFWD_HOST_ABOWT_CON_WEQ	0x0B
#define FW_WWOPCODE_OFWD_TP_ABOWT_CON_WPW	0x0C
#define FW_WWOPCODE_OFWD_TX_DATA		0x0D
#define FW_WWOPCODE_OFWD_TX_DATA_ACK		0x0E

#define FW_WWOPCODE_WI_WDMA_INIT		0x10
#define FW_WWOPCODE_WI_WDMA_WWITE		0x11
#define FW_WWOPCODE_WI_WDMA_WEAD_WEQ		0x12
#define FW_WWOPCODE_WI_WDMA_WEAD_WESP		0x13
#define FW_WWOPCODE_WI_SEND			0x14
#define FW_WWOPCODE_WI_TEWMINATE		0x15
#define FW_WWOPCODE_WI_WDMA_WEAD		0x16
#define FW_WWOPCODE_WI_WECEIVE			0x17
#define FW_WWOPCODE_WI_BIND_MW			0x18
#define FW_WWOPCODE_WI_FASTWEGISTEW_MW		0x19
#define FW_WWOPCODE_WI_WOCAW_INV		0x1A
#define FW_WWOPCODE_WI_MODIFY_QP		0x1B
#define FW_WWOPCODE_WI_BYPASS			0x1C

#define FW_WWOPOCDE_WSVD			0x1E

#define FW_WWOPCODE_SGE_EGWESSCONTEXT_WW	0x1F

#define FW_WWOPCODE_MNGT			0x1D
#define FW_MNGTOPCODE_PKTSCHED_SET		0x00

/* Maximum size of a WW sent fwom the host, wimited by the SGE.
 *
 * Note: WW coming fwom UWP ow TP awe onwy wimited by CIM.
 */
#define FW_WW_SIZE			128

/* Maximum numbew of outstanding WWs sent fwom the host. Vawue must be
 * pwogwammed in the CTWW/TUNNEW/QP SGE Egwess Context and used by
 * offwoad moduwes to wimit the numbew of WWs pew connection.
 */
#define FW_T3_WW_NUM			16
#define FW_N3_WW_NUM			7

#ifndef N3
# define FW_WW_NUM			FW_T3_WW_NUM
#ewse
# define FW_WW_NUM			FW_N3_WW_NUM
#endif

/* FW_TUNNEW_NUM cowwesponds to the numbew of suppowted TUNNEW Queues. These
 * queues must stawt at SGE Egwess Context FW_TUNNEW_SGEEC_STAWT and must
 * stawt at 'TID' (ow 'uP Token') FW_TUNNEW_TID_STAWT.
 *
 * Ingwess Twaffic (e.g. DMA compwetion cwedit)  fow TUNNEW Queue[i] is sent
 * to WESP Queue[i].
 */
#define FW_TUNNEW_NUM			8
#define FW_TUNNEW_SGEEC_STAWT		8
#define FW_TUNNEW_TID_STAWT		65544

/* FW_CTWW_NUM cowwesponds to the numbew of suppowted CTWW Queues. These queues
 * must stawt at SGE Egwess Context FW_CTWW_SGEEC_STAWT and must stawt at 'TID'
 * (ow 'uP Token') FW_CTWW_TID_STAWT.
 *
 * Ingwess Twaffic fow CTWW Queue[i] is sent to WESP Queue[i].
 */
#define FW_CTWW_NUM			8
#define FW_CTWW_SGEEC_STAWT		65528
#define FW_CTWW_TID_STAWT		65536

/* FW_OFWD_NUM cowwesponds to the numbew of suppowted OFFWOAD Queues. These
 * queues must stawt at SGE Egwess Context FW_OFWD_SGEEC_STAWT.
 *
 * Note: the 'uP Token' in the SGE Egwess Context fiewds is iwwewevant fow
 * OFFWOAD Queues, as the host is wesponsibwe fow pwoviding the cowwect TID in
 * evewy WW.
 *
 * Ingwess Twafffic fow OFFWOAD Queue[i] is sent to WESP Queue[i].
 */
#define FW_OFWD_NUM			8
#define FW_OFWD_SGEEC_STAWT		0

/*
 *
 */
#define FW_WI_NUM			1
#define FW_WI_SGEEC_STAWT		65527
#define FW_WI_TID_STAWT			65552

/*
 * The WX_PKT_TID
 */
#define FW_WX_PKT_NUM			1
#define FW_WX_PKT_TID_STAWT		65553

/* FW_WWC_NUM cowwesponds to the numbew of Wowk Wequest Context that suppowted
 * by the fiwmwawe.
 */
#define FW_WWC_NUM			\
    (65536 + FW_TUNNEW_NUM + FW_CTWW_NUM + FW_WI_NUM + FW_WX_PKT_NUM)

/*
 * FW type and vewsion.
 */
#define S_FW_VEWSION_TYPE		28
#define M_FW_VEWSION_TYPE		0xF
#define V_FW_VEWSION_TYPE(x)		((x) << S_FW_VEWSION_TYPE)
#define G_FW_VEWSION_TYPE(x)		\
    (((x) >> S_FW_VEWSION_TYPE) & M_FW_VEWSION_TYPE)

#define S_FW_VEWSION_MAJOW		16
#define M_FW_VEWSION_MAJOW		0xFFF
#define V_FW_VEWSION_MAJOW(x)		((x) << S_FW_VEWSION_MAJOW)
#define G_FW_VEWSION_MAJOW(x)		\
    (((x) >> S_FW_VEWSION_MAJOW) & M_FW_VEWSION_MAJOW)

#define S_FW_VEWSION_MINOW		8
#define M_FW_VEWSION_MINOW		0xFF
#define V_FW_VEWSION_MINOW(x)		((x) << S_FW_VEWSION_MINOW)
#define G_FW_VEWSION_MINOW(x)		\
    (((x) >> S_FW_VEWSION_MINOW) & M_FW_VEWSION_MINOW)

#define S_FW_VEWSION_MICWO		0
#define M_FW_VEWSION_MICWO		0xFF
#define V_FW_VEWSION_MICWO(x)		((x) << S_FW_VEWSION_MICWO)
#define G_FW_VEWSION_MICWO(x)		\
    (((x) >> S_FW_VEWSION_MICWO) & M_FW_VEWSION_MICWO)

#endif				/* _FIWMWAWE_EXPOWTS_H_ */
