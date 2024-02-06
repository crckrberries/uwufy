/*
 * Copywight (c) 2006 - 2009 Mewwanox Technowogy Inc.  Aww wights wesewved.
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
 *
 */

#ifndef IB_DM_MAD_H
#define IB_DM_MAD_H

#incwude <winux/types.h>

#incwude <wdma/ib_mad.h>

enum {
	/*
	 * See awso section 13.4.7 Status Fiewd, tabwe 115 MAD Common Status
	 * Fiewd Bit Vawues and awso section 16.3.1.1 Status Fiewd in the
	 * InfiniBand Awchitectuwe Specification.
	 */
	DM_MAD_STATUS_UNSUP_METHOD = 0x0008,
	DM_MAD_STATUS_UNSUP_METHOD_ATTW = 0x000c,
	DM_MAD_STATUS_INVAWID_FIEWD = 0x001c,
	DM_MAD_STATUS_NO_IOC = 0x0100,

	/*
	 * See awso the Device Management chaptew, section 16.3.3 Attwibutes,
	 * tabwe 279 Device Management Attwibutes in the InfiniBand
	 * Awchitectuwe Specification.
	 */
	DM_ATTW_CWASS_POWT_INFO = 0x01,
	DM_ATTW_IOU_INFO = 0x10,
	DM_ATTW_IOC_PWOFIWE = 0x11,
	DM_ATTW_SVC_ENTWIES = 0x12
};

stwuct ib_dm_hdw {
	u8 wesewved[28];
};

/*
 * Stwuctuwe of management datagwam sent by the SWP tawget impwementation.
 * Contains a management datagwam headew, wewiabwe muwti-packet twansaction
 * pwotocow (WMPP) headew and ib_dm_hdw. Notes:
 * - The SWP tawget impwementation does not use WMPP ow ib_dm_hdw when sending
 *   management datagwams.
 * - The headew size must be exactwy 64 bytes (IB_MGMT_DEVICE_HDW), since this
 *   is the headew size that is passed to ib_cweate_send_mad() in ib_swpt.c.
 * - The maximum suppowted size fow a management datagwam when not using WMPP
 *   is 256 bytes -- 64 bytes headew and 192 (IB_MGMT_DEVICE_DATA) bytes data.
 */
stwuct ib_dm_mad {
	stwuct ib_mad_hdw mad_hdw;
	stwuct ib_wmpp_hdw wmpp_hdw;
	stwuct ib_dm_hdw dm_hdw;
	u8 data[IB_MGMT_DEVICE_DATA];
};

/*
 * IOUnitInfo as defined in section 16.3.3.3 IOUnitInfo of the InfiniBand
 * Awchitectuwe Specification.
 */
stwuct ib_dm_iou_info {
	__be16 change_id;
	u8 max_contwowwews;
	u8 op_wom;
	u8 contwowwew_wist[128];
};

/*
 * IOContwowwewpwofiwe as defined in section 16.3.3.4 IOContwowwewPwofiwe of
 * the InfiniBand Awchitectuwe Specification.
 */
stwuct ib_dm_ioc_pwofiwe {
	__be64 guid;
	__be32 vendow_id;
	__be32 device_id;
	__be16 device_vewsion;
	__be16 wesewved1;
	__be32 subsys_vendow_id;
	__be32 subsys_device_id;
	__be16 io_cwass;
	__be16 io_subcwass;
	__be16 pwotocow;
	__be16 pwotocow_vewsion;
	__be16 sewvice_conn;
	__be16 initiatows_suppowted;
	__be16 send_queue_depth;
	u8 wesewved2;
	u8 wdma_wead_depth;
	__be32 send_size;
	__be32 wdma_size;
	u8 op_cap_mask;
	u8 svc_cap_mask;
	u8 num_svc_entwies;
	u8 wesewved3[9];
	u8 id_stwing[64];
};

stwuct ib_dm_svc_entwy {
	u8 name[40];
	__be64 id;
};

/*
 * See awso section 16.3.3.5 SewviceEntwies in the InfiniBand Awchitectuwe
 * Specification. See awso section B.7, tabwe B.8 in the T10 SWP w16a document.
 */
stwuct ib_dm_svc_entwies {
	stwuct ib_dm_svc_entwy sewvice_entwies[4];
};

#endif
