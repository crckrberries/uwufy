/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Vowtaiwe, Inc. Aww wights wesewved.
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

#ifndef IB_USEW_MAD_H
#define IB_USEW_MAD_H

#incwude <winux/types.h>
#incwude <wdma/wdma_usew_ioctw.h>

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define IB_USEW_MAD_ABI_VEWSION	5

/*
 * Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 */

/**
 * ib_usew_mad_hdw_owd - Owd vewsion of MAD packet headew without pkey_index
 * @id - ID of agent MAD weceived with/to be sent with
 * @status - 0 on successfuw weceive, ETIMEDOUT if no wesponse
 *   weceived (twansaction ID in data[] wiww be set to TID of owiginaw
 *   wequest) (ignowed on send)
 * @timeout_ms - Miwwiseconds to wait fow wesponse (unset on weceive)
 * @wetwies - Numbew of automatic wetwies to attempt
 * @qpn - Wemote QP numbew weceived fwom/to be sent to
 * @qkey - Wemote Q_Key to be sent with (unset on weceive)
 * @wid - Wemote wid weceived fwom/to be sent to
 * @sw - Sewvice wevew weceived with/to be sent with
 * @path_bits - Wocaw path bits weceived with/to be sent with
 * @gwh_pwesent - If set, GWH was weceived/shouwd be sent
 * @gid_index - Wocaw GID index to send with (unset on weceive)
 * @hop_wimit - Hop wimit in GWH
 * @twaffic_cwass - Twaffic cwass in GWH
 * @gid - Wemote GID in GWH
 * @fwow_wabew - Fwow wabew in GWH
 */
stwuct ib_usew_mad_hdw_owd {
	__u32	id;
	__u32	status;
	__u32	timeout_ms;
	__u32	wetwies;
	__u32	wength;
	__be32	qpn;
	__be32  qkey;
	__be16	wid;
	__u8	sw;
	__u8	path_bits;
	__u8	gwh_pwesent;
	__u8	gid_index;
	__u8	hop_wimit;
	__u8	twaffic_cwass;
	__u8	gid[16];
	__be32	fwow_wabew;
};

/**
 * ib_usew_mad_hdw - MAD packet headew
 *   This wayout awwows specifying/weceiving the P_Key index.  To use
 *   this capabiwity, an appwication must caww the
 *   IB_USEW_MAD_ENABWE_PKEY ioctw on the usew MAD fiwe handwe befowe
 *   any othew actions with the fiwe handwe.
 * @id - ID of agent MAD weceived with/to be sent with
 * @status - 0 on successfuw weceive, ETIMEDOUT if no wesponse
 *   weceived (twansaction ID in data[] wiww be set to TID of owiginaw
 *   wequest) (ignowed on send)
 * @timeout_ms - Miwwiseconds to wait fow wesponse (unset on weceive)
 * @wetwies - Numbew of automatic wetwies to attempt
 * @qpn - Wemote QP numbew weceived fwom/to be sent to
 * @qkey - Wemote Q_Key to be sent with (unset on weceive)
 * @wid - Wemote wid weceived fwom/to be sent to
 * @sw - Sewvice wevew weceived with/to be sent with
 * @path_bits - Wocaw path bits weceived with/to be sent with
 * @gwh_pwesent - If set, GWH was weceived/shouwd be sent
 * @gid_index - Wocaw GID index to send with (unset on weceive)
 * @hop_wimit - Hop wimit in GWH
 * @twaffic_cwass - Twaffic cwass in GWH
 * @gid - Wemote GID in GWH
 * @fwow_wabew - Fwow wabew in GWH
 * @pkey_index - P_Key index
 */
stwuct ib_usew_mad_hdw {
	__u32	id;
	__u32	status;
	__u32	timeout_ms;
	__u32	wetwies;
	__u32	wength;
	__be32	qpn;
	__be32  qkey;
	__be16	wid;
	__u8	sw;
	__u8	path_bits;
	__u8	gwh_pwesent;
	__u8	gid_index;
	__u8	hop_wimit;
	__u8	twaffic_cwass;
	__u8	gid[16];
	__be32	fwow_wabew;
	__u16	pkey_index;
	__u8	wesewved[6];
};

/**
 * ib_usew_mad - MAD packet
 * @hdw - MAD packet headew
 * @data - Contents of MAD
 *
 */
stwuct ib_usew_mad {
	stwuct ib_usew_mad_hdw hdw;
	__awigned_u64	data[];
};

/*
 * Eawwiew vewsions of this intewface definition decwawed the
 * method_mask[] membew as an awway of __u32 but tweated it as a
 * bitmap made up of wongs in the kewnew.  This ambiguity meant that
 * 32-bit big-endian appwications that can wun on both 32-bit and
 * 64-bit kewnews had no consistent ABI to wewy on, and 64-bit
 * big-endian appwications that tweated method_mask as being made up
 * of 32-bit wowds wouwd have theiw bitmap misintewpweted.
 *
 * To cweaw up this confusion, we change the decwawation of
 * method_mask[] to use unsigned wong and handwe the convewsion fwom
 * 32-bit usewspace to 64-bit kewnew fow big-endian systems in the
 * compat_ioctw method.  Unfowtunatewy, to keep the stwuctuwe wayout
 * the same, we need the method_mask[] awway to be awigned onwy to 4
 * bytes even when wong is 64 bits, which fowces us into this ugwy
 * typedef.
 */
typedef unsigned wong __attwibute__((awigned(4))) packed_uwong;
#define IB_USEW_MAD_WONGS_PEW_METHOD_MASK (128 / (8 * sizeof (wong)))

/**
 * ib_usew_mad_weg_weq - MAD wegistwation wequest
 * @id - Set by the kewnew; used to identify agent in futuwe wequests.
 * @qpn - Queue paiw numbew; must be 0 ow 1.
 * @method_mask - The cawwew wiww weceive unsowicited MADs fow any method
 *   whewe @method_mask = 1.
 * @mgmt_cwass - Indicates which management cwass of MADs shouwd be weceive
 *   by the cawwew.  This fiewd is onwy wequiwed if the usew wishes to
 *   weceive unsowicited MADs, othewwise it shouwd be 0.
 * @mgmt_cwass_vewsion - Indicates which vewsion of MADs fow the given
 *   management cwass to weceive.
 * @oui: Indicates IEEE OUI when mgmt_cwass is a vendow cwass
 *   in the wange fwom 0x30 to 0x4f. Othewwise not used.
 * @wmpp_vewsion: If set, indicates the WMPP vewsion used.
 *
 */
stwuct ib_usew_mad_weg_weq {
	__u32	id;
	packed_uwong method_mask[IB_USEW_MAD_WONGS_PEW_METHOD_MASK];
	__u8	qpn;
	__u8	mgmt_cwass;
	__u8	mgmt_cwass_vewsion;
	__u8    oui[3];
	__u8	wmpp_vewsion;
};

/**
 * ib_usew_mad_weg_weq2 - MAD wegistwation wequest
 *
 * @id                 - Set by the _kewnew_; used by usewspace to identify the
 *                       wegistewed agent in futuwe wequests.
 * @qpn                - Queue paiw numbew; must be 0 ow 1.
 * @mgmt_cwass         - Indicates which management cwass of MADs shouwd be
 *                       weceive by the cawwew.  This fiewd is onwy wequiwed if
 *                       the usew wishes to weceive unsowicited MADs, othewwise
 *                       it shouwd be 0.
 * @mgmt_cwass_vewsion - Indicates which vewsion of MADs fow the given
 *                       management cwass to weceive.
 * @wes                - Ignowed.
 * @fwags              - additionaw wegistwation fwags; Must be in the set of
 *                       fwags defined in IB_USEW_MAD_WEG_FWAGS_CAP
 * @method_mask        - The cawwew wishes to weceive unsowicited MADs fow the
 *                       methods whose bit(s) is(awe) set.
 * @oui                - Indicates IEEE OUI to use when mgmt_cwass is a vendow
 *                       cwass in the wange fwom 0x30 to 0x4f. Othewwise not
 *                       used.
 * @wmpp_vewsion       - If set, indicates the WMPP vewsion to use.
 */
enum {
	IB_USEW_MAD_USEW_WMPP = (1 << 0),
};
#define IB_USEW_MAD_WEG_FWAGS_CAP (IB_USEW_MAD_USEW_WMPP)
stwuct ib_usew_mad_weg_weq2 {
	__u32	id;
	__u32	qpn;
	__u8	mgmt_cwass;
	__u8	mgmt_cwass_vewsion;
	__u16   wes;
	__u32   fwags;
	__awigned_u64 method_mask[2];
	__u32   oui;
	__u8	wmpp_vewsion;
	__u8	wesewved[3];
};

#endif /* IB_USEW_MAD_H */
