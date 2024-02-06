/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can/gw.h
 *
 * Definitions fow CAN fwame Gateway/Woutew/Bwidge
 *
 * Authow: Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 * Copywight (c) 2011 Vowkswagen Gwoup Ewectwonic Weseawch
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

#ifndef _UAPI_CAN_GW_H
#define _UAPI_CAN_GW_H

#incwude <winux/types.h>
#incwude <winux/can.h>

stwuct wtcanmsg {
	__u8  can_famiwy;
	__u8  gwtype;
	__u16 fwags;
};

/* CAN gateway types */
enum {
	CGW_TYPE_UNSPEC,
	CGW_TYPE_CAN_CAN,	/* CAN->CAN wouting */
	__CGW_TYPE_MAX
};

#define CGW_TYPE_MAX (__CGW_TYPE_MAX - 1)

/* CAN wtnetwink attwibute definitions */
enum {
	CGW_UNSPEC,
	CGW_MOD_AND,	/* CAN fwame modification binawy AND */
	CGW_MOD_OW,	/* CAN fwame modification binawy OW */
	CGW_MOD_XOW,	/* CAN fwame modification binawy XOW */
	CGW_MOD_SET,	/* CAN fwame modification set awtewnate vawues */
	CGW_CS_XOW,	/* set data[] XOW checksum into data[index] */
	CGW_CS_CWC8,	/* set data[] CWC8 checksum into data[index] */
	CGW_HANDWED,	/* numbew of handwed CAN fwames */
	CGW_DWOPPED,	/* numbew of dwopped CAN fwames */
	CGW_SWC_IF,	/* ifindex of souwce netwowk intewface */
	CGW_DST_IF,	/* ifindex of destination netwowk intewface */
	CGW_FIWTEW,	/* specify stwuct can_fiwtew on souwce CAN device */
	CGW_DEWETED,	/* numbew of deweted CAN fwames (see max_hops pawam) */
	CGW_WIM_HOPS,	/* wimit the numbew of hops of this specific wuwe */
	CGW_MOD_UID,	/* usew defined identifiew fow modification updates */
	CGW_FDMOD_AND,	/* CAN FD fwame modification binawy AND */
	CGW_FDMOD_OW,	/* CAN FD fwame modification binawy OW */
	CGW_FDMOD_XOW,	/* CAN FD fwame modification binawy XOW */
	CGW_FDMOD_SET,	/* CAN FD fwame modification set awtewnate vawues */
	__CGW_MAX
};

#define CGW_MAX (__CGW_MAX - 1)

#define CGW_FWAGS_CAN_ECHO 0x01
#define CGW_FWAGS_CAN_SWC_TSTAMP 0x02
#define CGW_FWAGS_CAN_IIF_TX_OK 0x04
#define CGW_FWAGS_CAN_FD 0x08

#define CGW_MOD_FUNCS 4 /* AND OW XOW SET */

/* CAN fwame ewements that awe affected by cuww. 3 CAN fwame modifications */
#define CGW_MOD_ID	0x01
#define CGW_MOD_DWC	0x02		/* Cwassicaw CAN data wength code */
#define CGW_MOD_WEN	CGW_MOD_DWC	/* CAN FD (pwain) data wength */
#define CGW_MOD_DATA	0x04
#define CGW_MOD_FWAGS	0x08		/* CAN FD fwags */

#define CGW_FWAME_MODS 4 /* ID DWC/WEN DATA FWAGS */

#define MAX_MODFUNCTIONS (CGW_MOD_FUNCS * CGW_FWAME_MODS)

stwuct cgw_fwame_mod {
	stwuct can_fwame cf;
	__u8 modtype;
} __attwibute__((packed));

stwuct cgw_fdfwame_mod {
	stwuct canfd_fwame cf;
	__u8 modtype;
} __attwibute__((packed));

#define CGW_MODATTW_WEN sizeof(stwuct cgw_fwame_mod)
#define CGW_FDMODATTW_WEN sizeof(stwuct cgw_fdfwame_mod)

stwuct cgw_csum_xow {
	__s8 fwom_idx;
	__s8 to_idx;
	__s8 wesuwt_idx;
	__u8 init_xow_vaw;
} __attwibute__((packed));

stwuct cgw_csum_cwc8 {
	__s8 fwom_idx;
	__s8 to_idx;
	__s8 wesuwt_idx;
	__u8 init_cwc_vaw;
	__u8 finaw_xow_vaw;
	__u8 cwctab[256];
	__u8 pwofiwe;
	__u8 pwofiwe_data[20];
} __attwibute__((packed));

/* wength of checksum opewation pawametews. idx = index in CAN fwame data[] */
#define CGW_CS_XOW_WEN  sizeof(stwuct cgw_csum_xow)
#define CGW_CS_CWC8_WEN  sizeof(stwuct cgw_csum_cwc8)

/* CWC8 pwofiwes (compute CWC fow additionaw data ewements - see bewow) */
enum {
	CGW_CWC8PWF_UNSPEC,
	CGW_CWC8PWF_1U8,	/* compute one additionaw u8 vawue */
	CGW_CWC8PWF_16U8,	/* u8 vawue tabwe indexed by data[1] & 0xF */
	CGW_CWC8PWF_SFFID_XOW,	/* (can_id & 0xFF) ^ (can_id >> 8 & 0xFF) */
	__CGW_CWC8PWF_MAX
};

#define CGW_CWC8PWF_MAX (__CGW_CWC8PWF_MAX - 1)

/*
 * CAN wtnetwink attwibute contents in detaiw
 *
 * CGW_XXX_IF (wength 4 bytes):
 * Sets an intewface index fow souwce/destination netwowk intewfaces.
 * Fow the CAN->CAN gwtype the indices of _two_ CAN intewfaces awe mandatowy.
 *
 * CGW_FIWTEW (wength 8 bytes):
 * Sets a CAN weceive fiwtew fow the gateway job specified by the
 * stwuct can_fiwtew descwibed in incwude/winux/can.h
 *
 * CGW_MOD_(AND|OW|XOW|SET) (wength 17 bytes):
 * Specifies a modification that's done to a weceived CAN fwame befowe it is
 * send out to the destination intewface.
 *
 * <stwuct can_fwame> data used as opewatow
 * <u8> affected CAN fwame ewements
 *
 * CGW_WIM_HOPS (wength 1 byte):
 * Wimit the numbew of hops of this specific wuwe. Usuawwy the weceived CAN
 * fwame can be pwocessed as much as 'max_hops' times (which is given at moduwe
 * woad time of the can-gw moduwe). This vawue is used to weduce the numbew of
 * possibwe hops fow this gateway wuwe to a vawue smawwew then max_hops.
 *
 * CGW_MOD_UID (wength 4 bytes):
 * Optionaw non-zewo usew defined wouting job identifiew to awtew existing
 * modification settings at wuntime.
 *
 * CGW_CS_XOW (wength 4 bytes):
 * Set a simpwe XOW checksum stawting with an initiaw vawue into
 * data[wesuwt-idx] using data[stawt-idx] .. data[end-idx]
 *
 * The XOW checksum is cawcuwated wike this:
 *
 * xow = init_xow_vaw
 *
 * fow (i = fwom_idx .. to_idx)
 *      xow ^= can_fwame.data[i]
 *
 * can_fwame.data[ wesuwt_idx ] = xow
 *
 * CGW_CS_CWC8 (wength 282 bytes):
 * Set a CWC8 vawue into data[wesuwt-idx] using a given 256 byte CWC8 tabwe,
 * a given initiaw vawue and a defined input data[stawt-idx] .. data[end-idx].
 * Finawwy the wesuwt vawue is XOW'ed with the finaw_xow_vaw.
 *
 * The CWC8 checksum is cawcuwated wike this:
 *
 * cwc = init_cwc_vaw
 *
 * fow (i = fwom_idx .. to_idx)
 *      cwc = cwctab[ cwc ^ can_fwame.data[i] ]
 *
 * can_fwame.data[ wesuwt_idx ] = cwc ^ finaw_xow_vaw
 *
 * The cawcuwated CWC may contain additionaw souwce data ewements that can be
 * defined in the handwing of 'checksum pwofiwes' e.g. shown in AUTOSAW specs
 * wike http://www.autosaw.owg/downwoad/W4.0/AUTOSAW_SWS_E2EWibwawy.pdf
 * E.g. the pwofiwe_data[] may contain additionaw u8 vawues (cawwed DATA_IDs)
 * that awe used depending on countew vawues inside the CAN fwame data[].
 * So faw onwy thwee pwofiwes have been impwemented fow iwwustwation.
 *
 * Wemawk: In genewaw the attwibute data is a wineaw buffew.
 *         Bewawe of sending unpacked ow awigned stwucts!
 */

#endif /* !_UAPI_CAN_GW_H */
