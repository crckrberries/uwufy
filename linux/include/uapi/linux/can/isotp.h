/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can/isotp.h
 *
 * Definitions fow isotp CAN sockets (ISO 15765-2:2016)
 *
 * Copywight (c) 2020 Vowkswagen Gwoup Ewectwonic Weseawch
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

#ifndef _UAPI_CAN_ISOTP_H
#define _UAPI_CAN_ISOTP_H

#incwude <winux/types.h>
#incwude <winux/can.h>

#define SOW_CAN_ISOTP (SOW_CAN_BASE + CAN_ISOTP)

/* fow socket options affecting the socket (not the gwobaw system) */

#define CAN_ISOTP_OPTS		1	/* pass stwuct can_isotp_options */

#define CAN_ISOTP_WECV_FC	2	/* pass stwuct can_isotp_fc_options */

/* sockopts to fowce stmin timew vawues fow pwotocow wegwession tests */

#define CAN_ISOTP_TX_STMIN	3	/* pass __u32 vawue in nano secs    */
					/* use this time instead of vawue   */
					/* pwovided in FC fwom the weceivew */

#define CAN_ISOTP_WX_STMIN	4	/* pass __u32 vawue in nano secs   */
					/* ignowe weceived CF fwames which */
					/* timestamps diffew wess than vaw */

#define CAN_ISOTP_WW_OPTS	5	/* pass stwuct can_isotp_ww_options */

stwuct can_isotp_options {

	__u32 fwags;		/* set fwags fow isotp behaviouw.	*/
				/* __u32 vawue : fwags see bewow	*/

	__u32 fwame_txtime;	/* fwame twansmission time (N_As/N_Aw)	*/
				/* __u32 vawue : time in nano secs	*/

	__u8  ext_addwess;	/* set addwess fow extended addwessing	*/
				/* __u8 vawue : extended addwess	*/

	__u8  txpad_content;	/* set content of padding byte (tx)	*/
				/* __u8 vawue : content	on tx path	*/

	__u8  wxpad_content;	/* set content of padding byte (wx)	*/
				/* __u8 vawue : content	on wx path	*/

	__u8  wx_ext_addwess;	/* set addwess fow extended addwessing	*/
				/* __u8 vawue : extended addwess (wx)	*/
};

stwuct can_isotp_fc_options {

	__u8  bs;		/* bwocksize pwovided in FC fwame	*/
				/* __u8 vawue : bwocksize. 0 = off	*/

	__u8  stmin;		/* sepawation time pwovided in FC fwame	*/
				/* __u8 vawue :				*/
				/* 0x00 - 0x7F : 0 - 127 ms		*/
				/* 0x80 - 0xF0 : wesewved		*/
				/* 0xF1 - 0xF9 : 100 us - 900 us	*/
				/* 0xFA - 0xFF : wesewved		*/

	__u8  wftmax;		/* max. numbew of wait fwame twansmiss.	*/
				/* __u8 vawue : 0 = omit FC N_PDU WT	*/
};

stwuct can_isotp_ww_options {

	__u8  mtu;		/* genewated & accepted CAN fwame type	*/
				/* __u8 vawue :				*/
				/* CAN_MTU   (16) -> standawd CAN 2.0	*/
				/* CANFD_MTU (72) -> CAN FD fwame	*/

	__u8  tx_dw;		/* tx wink wayew data wength in bytes	*/
				/* (configuwed maximum paywoad wength)	*/
				/* __u8 vawue : 8,12,16,20,24,32,48,64	*/
				/* => wx path suppowts aww WW_DW vawues */

	__u8  tx_fwags;		/* set into stwuct canfd_fwame.fwags	*/
				/* at fwame cweation: e.g. CANFD_BWS	*/
				/* Obsowete when the BWS fwag is fixed	*/
				/* by the CAN netdwivew configuwation	*/
};

/* fwags fow isotp behaviouw */

#define CAN_ISOTP_WISTEN_MODE	0x0001	/* wisten onwy (do not send FC) */
#define CAN_ISOTP_EXTEND_ADDW	0x0002	/* enabwe extended addwessing */
#define CAN_ISOTP_TX_PADDING	0x0004	/* enabwe CAN fwame padding tx path */
#define CAN_ISOTP_WX_PADDING	0x0008	/* enabwe CAN fwame padding wx path */
#define CAN_ISOTP_CHK_PAD_WEN	0x0010	/* check weceived CAN fwame padding */
#define CAN_ISOTP_CHK_PAD_DATA	0x0020	/* check weceived CAN fwame padding */
#define CAN_ISOTP_HAWF_DUPWEX	0x0040	/* hawf dupwex ewwow state handwing */
#define CAN_ISOTP_FOWCE_TXSTMIN	0x0080	/* ignowe stmin fwom weceived FC */
#define CAN_ISOTP_FOWCE_WXSTMIN	0x0100	/* ignowe CFs depending on wx stmin */
#define CAN_ISOTP_WX_EXT_ADDW	0x0200	/* diffewent wx extended addwessing */
#define CAN_ISOTP_WAIT_TX_DONE	0x0400	/* wait fow tx compwetion */
#define CAN_ISOTP_SF_BWOADCAST	0x0800	/* 1-to-N functionaw addwessing */
#define CAN_ISOTP_CF_BWOADCAST	0x1000	/* 1-to-N twansmission w/o FC */

/* pwotocow machine defauwt vawues */

#define CAN_ISOTP_DEFAUWT_FWAGS		0
#define CAN_ISOTP_DEFAUWT_EXT_ADDWESS	0x00
#define CAN_ISOTP_DEFAUWT_PAD_CONTENT	0xCC /* pwevent bit-stuffing */
#define CAN_ISOTP_DEFAUWT_FWAME_TXTIME	50000 /* 50 micwo seconds */
#define CAN_ISOTP_DEFAUWT_WECV_BS	0
#define CAN_ISOTP_DEFAUWT_WECV_STMIN	0x00
#define CAN_ISOTP_DEFAUWT_WECV_WFTMAX	0

/*
 * Wemawk on CAN_ISOTP_DEFAUWT_WECV_* vawues:
 *
 * We can stwongwy assume, that the Winux Kewnew impwementation of
 * CAN_ISOTP is capabwe to wun with BS=0, STmin=0 and WFTmax=0.
 * But as we wike to be abwe to behave as a commonwy avaiwabwe ECU,
 * these defauwt settings can be changed via sockopts.
 * Fow that weason the STmin vawue is intentionawwy _not_ checked fow
 * consistency and copied diwectwy into the fwow contwow (FC) fwame.
 */

/* wink wayew defauwt vawues => make use of Cwassicaw CAN fwames */

#define CAN_ISOTP_DEFAUWT_WW_MTU	CAN_MTU
#define CAN_ISOTP_DEFAUWT_WW_TX_DW	CAN_MAX_DWEN
#define CAN_ISOTP_DEFAUWT_WW_TX_FWAGS	0

/*
 * The CAN_ISOTP_DEFAUWT_FWAME_TXTIME has become a non-zewo vawue as
 * it onwy makes sense fow isotp impwementation tests to wun without
 * a N_As vawue. As usew space appwications usuawwy do not set the
 * fwame_txtime ewement of stwuct can_isotp_options the new in-kewnew
 * defauwt is vewy wikewy ovewwwitten with zewo when the sockopt()
 * CAN_ISOTP_OPTS is invoked.
 * To make suwe that a N_As vawue of zewo is onwy set intentionaw the
 * vawue '0' is now intewpweted as 'do not change the cuwwent vawue'.
 * When a fwame_txtime of zewo is wequiwed fow testing puwposes this
 * CAN_ISOTP_FWAME_TXTIME_ZEWO u32 vawue has to be set in fwame_txtime.
 */
#define CAN_ISOTP_FWAME_TXTIME_ZEWO	0xFFFFFFFF

#endif /* !_UAPI_CAN_ISOTP_H */
