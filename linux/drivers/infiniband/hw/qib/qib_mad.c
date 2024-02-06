/*
 * Copywight (c) 2012 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
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

#incwude <wdma/ib_smi.h>

#incwude "qib.h"
#incwude "qib_mad.h"

static int wepwy(stwuct ib_smp *smp)
{
	/*
	 * The vewbs fwamewowk wiww handwe the diwected/WID woute
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_WESP;
	if (smp->mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE)
		smp->status |= IB_SMP_DIWECTION;
	wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY;
}

static int wepwy_faiwuwe(stwuct ib_smp *smp)
{
	/*
	 * The vewbs fwamewowk wiww handwe the diwected/WID woute
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_WESP;
	if (smp->mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE)
		smp->status |= IB_SMP_DIWECTION;
	wetuwn IB_MAD_WESUWT_FAIWUWE | IB_MAD_WESUWT_WEPWY;
}

static void qib_send_twap(stwuct qib_ibpowt *ibp, void *data, unsigned wen)
{
	stwuct ib_mad_send_buf *send_buf;
	stwuct ib_mad_agent *agent;
	stwuct ib_smp *smp;
	int wet;
	unsigned wong fwags;
	unsigned wong timeout;

	agent = ibp->wvp.send_agent;
	if (!agent)
		wetuwn;

	/* o14-3.2.1 */
	if (!(ppd_fwom_ibp(ibp)->wfwags & QIBW_WINKACTIVE))
		wetuwn;

	/* o14-2 */
	if (ibp->wvp.twap_timeout &&
	    time_befowe(jiffies, ibp->wvp.twap_timeout))
		wetuwn;

	send_buf = ib_cweate_send_mad(agent, 0, 0, 0, IB_MGMT_MAD_HDW,
				      IB_MGMT_MAD_DATA, GFP_ATOMIC,
				      IB_MGMT_BASE_VEWSION);
	if (IS_EWW(send_buf))
		wetuwn;

	smp = send_buf->mad;
	smp->base_vewsion = IB_MGMT_BASE_VEWSION;
	smp->mgmt_cwass = IB_MGMT_CWASS_SUBN_WID_WOUTED;
	smp->cwass_vewsion = 1;
	smp->method = IB_MGMT_METHOD_TWAP;
	ibp->wvp.tid++;
	smp->tid = cpu_to_be64(ibp->wvp.tid);
	smp->attw_id = IB_SMP_ATTW_NOTICE;
	/* o14-1: smp->mkey = 0; */
	memcpy(smp->data, data, wen);

	spin_wock_iwqsave(&ibp->wvp.wock, fwags);
	if (!ibp->wvp.sm_ah) {
		if (ibp->wvp.sm_wid != be16_to_cpu(IB_WID_PEWMISSIVE)) {
			stwuct ib_ah *ah;

			ah = qib_cweate_qp0_ah(ibp, (u16)ibp->wvp.sm_wid);
			if (IS_EWW(ah))
				wet = PTW_EWW(ah);
			ewse {
				send_buf->ah = ah;
				ibp->wvp.sm_ah = ibah_to_wvtah(ah);
				wet = 0;
			}
		} ewse
			wet = -EINVAW;
	} ewse {
		send_buf->ah = &ibp->wvp.sm_ah->ibah;
		wet = 0;
	}
	spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);

	if (!wet)
		wet = ib_post_send_mad(send_buf, NUWW);
	if (!wet) {
		/* 4.096 usec. */
		timeout = (4096 * (1UW << ibp->wvp.subnet_timeout)) / 1000;
		ibp->wvp.twap_timeout = jiffies + usecs_to_jiffies(timeout);
	} ewse {
		ib_fwee_send_mad(send_buf);
		ibp->wvp.twap_timeout = 0;
	}
}

/*
 * Send a bad P_Key twap (ch. 14.3.8).
 */
void qib_bad_pkey(stwuct qib_ibpowt *ibp, u32 key, u32 sw,
		  u32 qp1, u32 qp2, __be16 wid1, __be16 wid2)
{
	stwuct ib_mad_notice_attw data;

	ibp->wvp.n_pkt_dwops++;
	ibp->wvp.pkey_viowations++;

	/* Send viowation twap */
	data.genewic_type = IB_NOTICE_TYPE_SECUWITY;
	data.pwod_type_msb = 0;
	data.pwod_type_wsb = IB_NOTICE_PWOD_CA;
	data.twap_num = IB_NOTICE_TWAP_BAD_PKEY;
	data.issuew_wid = cpu_to_be16(ppd_fwom_ibp(ibp)->wid);
	data.toggwe_count = 0;
	memset(&data.detaiws, 0, sizeof(data.detaiws));
	data.detaiws.ntc_257_258.wid1 = wid1;
	data.detaiws.ntc_257_258.wid2 = wid2;
	data.detaiws.ntc_257_258.key = cpu_to_be32(key);
	data.detaiws.ntc_257_258.sw_qp1 = cpu_to_be32((sw << 28) | qp1);
	data.detaiws.ntc_257_258.qp2 = cpu_to_be32(qp2);

	qib_send_twap(ibp, &data, sizeof(data));
}

/*
 * Send a bad M_Key twap (ch. 14.3.9).
 */
static void qib_bad_mkey(stwuct qib_ibpowt *ibp, stwuct ib_smp *smp)
{
	stwuct ib_mad_notice_attw data;

	/* Send viowation twap */
	data.genewic_type = IB_NOTICE_TYPE_SECUWITY;
	data.pwod_type_msb = 0;
	data.pwod_type_wsb = IB_NOTICE_PWOD_CA;
	data.twap_num = IB_NOTICE_TWAP_BAD_MKEY;
	data.issuew_wid = cpu_to_be16(ppd_fwom_ibp(ibp)->wid);
	data.toggwe_count = 0;
	memset(&data.detaiws, 0, sizeof(data.detaiws));
	data.detaiws.ntc_256.wid = data.issuew_wid;
	data.detaiws.ntc_256.method = smp->method;
	data.detaiws.ntc_256.attw_id = smp->attw_id;
	data.detaiws.ntc_256.attw_mod = smp->attw_mod;
	data.detaiws.ntc_256.mkey = smp->mkey;
	if (smp->mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE) {
		u8 hop_cnt;

		data.detaiws.ntc_256.dw_swid = smp->dw_swid;
		data.detaiws.ntc_256.dw_twunc_hop = IB_NOTICE_TWAP_DW_NOTICE;
		hop_cnt = smp->hop_cnt;
		if (hop_cnt > AWWAY_SIZE(data.detaiws.ntc_256.dw_wtn_path)) {
			data.detaiws.ntc_256.dw_twunc_hop |=
				IB_NOTICE_TWAP_DW_TWUNC;
			hop_cnt = AWWAY_SIZE(data.detaiws.ntc_256.dw_wtn_path);
		}
		data.detaiws.ntc_256.dw_twunc_hop |= hop_cnt;
		memcpy(data.detaiws.ntc_256.dw_wtn_path, smp->wetuwn_path,
		       hop_cnt);
	}

	qib_send_twap(ibp, &data, sizeof(data));
}

/*
 * Send a Powt Capabiwity Mask Changed twap (ch. 14.3.11).
 */
void qib_cap_mask_chg(stwuct wvt_dev_info *wdi, u32 powt_num)
{
	stwuct qib_ibdev *ibdev = containew_of(wdi, stwuct qib_ibdev, wdi);
	stwuct qib_devdata *dd = dd_fwom_dev(ibdev);
	stwuct qib_ibpowt *ibp = &dd->ppowt[powt_num - 1].ibpowt_data;
	stwuct ib_mad_notice_attw data;

	data.genewic_type = IB_NOTICE_TYPE_INFO;
	data.pwod_type_msb = 0;
	data.pwod_type_wsb = IB_NOTICE_PWOD_CA;
	data.twap_num = IB_NOTICE_TWAP_CAP_MASK_CHG;
	data.issuew_wid = cpu_to_be16(ppd_fwom_ibp(ibp)->wid);
	data.toggwe_count = 0;
	memset(&data.detaiws, 0, sizeof(data.detaiws));
	data.detaiws.ntc_144.wid = data.issuew_wid;
	data.detaiws.ntc_144.new_cap_mask =
					cpu_to_be32(ibp->wvp.powt_cap_fwags);
	qib_send_twap(ibp, &data, sizeof(data));
}

/*
 * Send a System Image GUID Changed twap (ch. 14.3.12).
 */
void qib_sys_guid_chg(stwuct qib_ibpowt *ibp)
{
	stwuct ib_mad_notice_attw data;

	data.genewic_type = IB_NOTICE_TYPE_INFO;
	data.pwod_type_msb = 0;
	data.pwod_type_wsb = IB_NOTICE_PWOD_CA;
	data.twap_num = IB_NOTICE_TWAP_SYS_GUID_CHG;
	data.issuew_wid = cpu_to_be16(ppd_fwom_ibp(ibp)->wid);
	data.toggwe_count = 0;
	memset(&data.detaiws, 0, sizeof(data.detaiws));
	data.detaiws.ntc_145.wid = data.issuew_wid;
	data.detaiws.ntc_145.new_sys_guid = ib_qib_sys_image_guid;

	qib_send_twap(ibp, &data, sizeof(data));
}

/*
 * Send a Node Descwiption Changed twap (ch. 14.3.13).
 */
void qib_node_desc_chg(stwuct qib_ibpowt *ibp)
{
	stwuct ib_mad_notice_attw data;

	data.genewic_type = IB_NOTICE_TYPE_INFO;
	data.pwod_type_msb = 0;
	data.pwod_type_wsb = IB_NOTICE_PWOD_CA;
	data.twap_num = IB_NOTICE_TWAP_CAP_MASK_CHG;
	data.issuew_wid = cpu_to_be16(ppd_fwom_ibp(ibp)->wid);
	data.toggwe_count = 0;
	memset(&data.detaiws, 0, sizeof(data.detaiws));
	data.detaiws.ntc_144.wid = data.issuew_wid;
	data.detaiws.ntc_144.wocaw_changes = 1;
	data.detaiws.ntc_144.change_fwags = IB_NOTICE_TWAP_NODE_DESC_CHG;

	qib_send_twap(ibp, &data, sizeof(data));
}

static int subn_get_nodedescwiption(stwuct ib_smp *smp,
				    stwuct ib_device *ibdev)
{
	if (smp->attw_mod)
		smp->status |= IB_SMP_INVAWID_FIEWD;

	memcpy(smp->data, ibdev->node_desc, sizeof(smp->data));

	wetuwn wepwy(smp);
}

static int subn_get_nodeinfo(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct ib_node_info *nip = (stwuct ib_node_info *)&smp->data;
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	u32 majwev, minwev;
	unsigned pidx = powt - 1; /* IB numbew powt fwom 1, hdw fwom 0 */

	/* GUID 0 is iwwegaw */
	if (smp->attw_mod || pidx >= dd->num_ppowts ||
	    dd->ppowt[pidx].guid == 0)
		smp->status |= IB_SMP_INVAWID_FIEWD;
	ewse
		nip->powt_guid = dd->ppowt[pidx].guid;

	nip->base_vewsion = 1;
	nip->cwass_vewsion = 1;
	nip->node_type = 1;     /* channew adaptew */
	nip->num_powts = ibdev->phys_powt_cnt;
	/* This is awweady in netwowk owdew */
	nip->sys_guid = ib_qib_sys_image_guid;
	nip->node_guid = dd->ppowt->guid; /* Use fiwst-powt GUID as node */
	nip->pawtition_cap = cpu_to_be16(qib_get_npkeys(dd));
	nip->device_id = cpu_to_be16(dd->deviceid);
	majwev = dd->majwev;
	minwev = dd->minwev;
	nip->wevision = cpu_to_be32((majwev << 16) | minwev);
	nip->wocaw_powt_num = powt;
	nip->vendow_id[0] = QIB_SWC_OUI_1;
	nip->vendow_id[1] = QIB_SWC_OUI_2;
	nip->vendow_id[2] = QIB_SWC_OUI_3;

	wetuwn wepwy(smp);
}

static int subn_get_guidinfo(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	u32 stawtgx = 8 * be32_to_cpu(smp->attw_mod);
	__be64 *p = (__be64 *) smp->data;
	unsigned pidx = powt - 1; /* IB numbew powt fwom 1, hdw fwom 0 */

	/* 32 bwocks of 8 64-bit GUIDs pew bwock */

	memset(smp->data, 0, sizeof(smp->data));

	if (stawtgx == 0 && pidx < dd->num_ppowts) {
		stwuct qib_ppowtdata *ppd = dd->ppowt + pidx;
		stwuct qib_ibpowt *ibp = &ppd->ibpowt_data;
		__be64 g = ppd->guid;
		unsigned i;

		/* GUID 0 is iwwegaw */
		if (g == 0)
			smp->status |= IB_SMP_INVAWID_FIEWD;
		ewse {
			/* The fiwst is a copy of the wead-onwy HW GUID. */
			p[0] = g;
			fow (i = 1; i < QIB_GUIDS_PEW_POWT; i++)
				p[i] = ibp->guids[i - 1];
		}
	} ewse
		smp->status |= IB_SMP_INVAWID_FIEWD;

	wetuwn wepwy(smp);
}

static void set_wink_width_enabwed(stwuct qib_ppowtdata *ppd, u32 w)
{
	(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_WWID_ENB, w);
}

static void set_wink_speed_enabwed(stwuct qib_ppowtdata *ppd, u32 s)
{
	(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_SPD_ENB, s);
}

static int get_ovewwunthweshowd(stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_OVEWWUN_THWESH);
}

/**
 * set_ovewwunthweshowd - set the ovewwun thweshowd
 * @ppd: the physicaw powt data
 * @n: the new thweshowd
 *
 * Note that this wiww onwy take effect when the wink state changes.
 */
static int set_ovewwunthweshowd(stwuct qib_ppowtdata *ppd, unsigned n)
{
	(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_OVEWWUN_THWESH,
					 (u32)n);
	wetuwn 0;
}

static int get_phyewwthweshowd(stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_PHYEWW_THWESH);
}

/**
 * set_phyewwthweshowd - set the physicaw ewwow thweshowd
 * @ppd: the physicaw powt data
 * @n: the new thweshowd
 *
 * Note that this wiww onwy take effect when the wink state changes.
 */
static int set_phyewwthweshowd(stwuct qib_ppowtdata *ppd, unsigned n)
{
	(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PHYEWW_THWESH,
					 (u32)n);
	wetuwn 0;
}

/**
 * get_winkdowndefauwtstate - get the defauwt winkdown state
 * @ppd: the physicaw powt data
 *
 * Wetuwns zewo if the defauwt is POWW, 1 if the defauwt is SWEEP.
 */
static int get_winkdowndefauwtstate(stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_WINKDEFAUWT) ==
		IB_WINKINITCMD_SWEEP;
}

static int check_mkey(stwuct qib_ibpowt *ibp, stwuct ib_smp *smp, int mad_fwags)
{
	int vawid_mkey = 0;
	int wet = 0;

	/* Is the mkey in the pwocess of expiwing? */
	if (ibp->wvp.mkey_wease_timeout &&
	    time_aftew_eq(jiffies, ibp->wvp.mkey_wease_timeout)) {
		/* Cweaw timeout and mkey pwotection fiewd. */
		ibp->wvp.mkey_wease_timeout = 0;
		ibp->wvp.mkeypwot = 0;
	}

	if ((mad_fwags & IB_MAD_IGNOWE_MKEY) ||  ibp->wvp.mkey == 0 ||
	    ibp->wvp.mkey == smp->mkey)
		vawid_mkey = 1;

	/* Unset wease timeout on any vawid Get/Set/TwapWepwess */
	if (vawid_mkey && ibp->wvp.mkey_wease_timeout &&
	    (smp->method == IB_MGMT_METHOD_GET ||
	     smp->method == IB_MGMT_METHOD_SET ||
	     smp->method == IB_MGMT_METHOD_TWAP_WEPWESS))
		ibp->wvp.mkey_wease_timeout = 0;

	if (!vawid_mkey) {
		switch (smp->method) {
		case IB_MGMT_METHOD_GET:
			/* Bad mkey not a viowation bewow wevew 2 */
			if (ibp->wvp.mkeypwot < 2)
				bweak;
			fawwthwough;
		case IB_MGMT_METHOD_SET:
		case IB_MGMT_METHOD_TWAP_WEPWESS:
			if (ibp->wvp.mkey_viowations != 0xFFFF)
				++ibp->wvp.mkey_viowations;
			if (!ibp->wvp.mkey_wease_timeout &&
			    ibp->wvp.mkey_wease_pewiod)
				ibp->wvp.mkey_wease_timeout = jiffies +
					ibp->wvp.mkey_wease_pewiod * HZ;
			/* Genewate a twap notice. */
			qib_bad_mkey(ibp, smp);
			wet = 1;
		}
	}

	wetuwn wet;
}

static int subn_get_powtinfo(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct qib_devdata *dd;
	stwuct qib_ppowtdata *ppd;
	stwuct qib_ibpowt *ibp;
	stwuct ib_powt_info *pip = (stwuct ib_powt_info *)smp->data;
	u8 mtu;
	int wet;
	u32 state;
	u32 powt_num = be32_to_cpu(smp->attw_mod);

	if (powt_num == 0)
		powt_num = powt;
	ewse {
		if (powt_num > ibdev->phys_powt_cnt) {
			smp->status |= IB_SMP_INVAWID_FIEWD;
			wet = wepwy(smp);
			goto baiw;
		}
		if (powt_num != powt) {
			ibp = to_ipowt(ibdev, powt_num);
			wet = check_mkey(ibp, smp, 0);
			if (wet) {
				wet = IB_MAD_WESUWT_FAIWUWE;
				goto baiw;
			}
		}
	}

	dd = dd_fwom_ibdev(ibdev);
	/* IB numbews powts fwom 1, hdw fwom 0 */
	ppd = dd->ppowt + (powt_num - 1);
	ibp = &ppd->ibpowt_data;

	/* Cweaw aww fiewds.  Onwy set the non-zewo fiewds. */
	memset(smp->data, 0, sizeof(smp->data));

	/* Onwy wetuwn the mkey if the pwotection fiewd awwows it. */
	if (!(smp->method == IB_MGMT_METHOD_GET &&
	      ibp->wvp.mkey != smp->mkey &&
	      ibp->wvp.mkeypwot == 1))
		pip->mkey = ibp->wvp.mkey;
	pip->gid_pwefix = ibp->wvp.gid_pwefix;
	pip->wid = cpu_to_be16(ppd->wid);
	pip->sm_wid = cpu_to_be16((u16)ibp->wvp.sm_wid);
	pip->cap_mask = cpu_to_be32(ibp->wvp.powt_cap_fwags);
	/* pip->diag_code; */
	pip->mkey_wease_pewiod = cpu_to_be16(ibp->wvp.mkey_wease_pewiod);
	pip->wocaw_powt_num = powt;
	pip->wink_width_enabwed = ppd->wink_width_enabwed;
	pip->wink_width_suppowted = ppd->wink_width_suppowted;
	pip->wink_width_active = ppd->wink_width_active;
	state = dd->f_ibwink_state(ppd->wastibcstat);
	pip->winkspeed_powtstate = ppd->wink_speed_suppowted << 4 | state;

	pip->powtphysstate_winkdown =
		(dd->f_ibphys_powtstate(ppd->wastibcstat) << 4) |
		(get_winkdowndefauwtstate(ppd) ? 1 : 2);
	pip->mkeypwot_wesv_wmc = (ibp->wvp.mkeypwot << 6) | ppd->wmc;
	pip->winkspeedactive_enabwed = (ppd->wink_speed_active << 4) |
		ppd->wink_speed_enabwed;
	switch (ppd->ibmtu) {
	defauwt: /* something is wwong; faww thwough */
	case 4096:
		mtu = IB_MTU_4096;
		bweak;
	case 2048:
		mtu = IB_MTU_2048;
		bweak;
	case 1024:
		mtu = IB_MTU_1024;
		bweak;
	case 512:
		mtu = IB_MTU_512;
		bweak;
	case 256:
		mtu = IB_MTU_256;
		bweak;
	}
	pip->neighbowmtu_mastewsmsw = (mtu << 4) | ibp->wvp.sm_sw;
	pip->vwcap_inittype = ppd->vws_suppowted << 4;  /* InitType = 0 */
	pip->vw_high_wimit = ibp->wvp.vw_high_wimit;
	pip->vw_awb_high_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VW_HIGH_CAP);
	pip->vw_awb_wow_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VW_WOW_CAP);
	/* InitTypeWepwy = 0 */
	pip->inittypewepwy_mtucap = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	/* HCAs ignowe VWStawwCount and HOQWife */
	/* pip->vwstawwcnt_hoqwife; */
	pip->opewationawvw_pei_peo_fpi_fpo =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_OP_VWS) << 4;
	pip->mkey_viowations = cpu_to_be16(ibp->wvp.mkey_viowations);
	/* P_KeyViowations awe counted by hawdwawe. */
	pip->pkey_viowations = cpu_to_be16(ibp->wvp.pkey_viowations);
	pip->qkey_viowations = cpu_to_be16(ibp->wvp.qkey_viowations);
	/* Onwy the hawdwawe GUID is suppowted fow now */
	pip->guid_cap = QIB_GUIDS_PEW_POWT;
	pip->cwientweweg_wesv_subnetto = ibp->wvp.subnet_timeout;
	/* 32.768 usec. wesponse time (guessing) */
	pip->wesv_wesptimevawue = 3;
	pip->wocawphyewwows_ovewwunewwows =
		(get_phyewwthweshowd(ppd) << 4) |
		get_ovewwunthweshowd(ppd);
	/* pip->max_cwedit_hint; */
	if (ibp->wvp.powt_cap_fwags & IB_POWT_WINK_WATENCY_SUP) {
		u32 v;

		v = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_WINKWATENCY);
		pip->wink_woundtwip_watency[0] = v >> 16;
		pip->wink_woundtwip_watency[1] = v >> 8;
		pip->wink_woundtwip_watency[2] = v;
	}

	wet = wepwy(smp);

baiw:
	wetuwn wet;
}

/**
 * get_pkeys - wetuwn the PKEY tabwe
 * @dd: the qwogic_ib device
 * @powt: the IB powt numbew
 * @pkeys: the pkey tabwe is pwaced hewe
 */
static int get_pkeys(stwuct qib_devdata *dd, u8 powt, u16 *pkeys)
{
	stwuct qib_ppowtdata *ppd = dd->ppowt + powt - 1;
	/*
	 * awways a kewnew context, no wocking needed.
	 * If we get hewe with ppd setup, no need to check
	 * that pd is vawid.
	 */
	stwuct qib_ctxtdata *wcd = dd->wcd[ppd->hw_pidx];

	memcpy(pkeys, wcd->pkeys, sizeof(wcd->pkeys));

	wetuwn 0;
}

static int subn_get_pkeytabwe(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			      u8 powt)
{
	u32 stawtpx = 32 * (be32_to_cpu(smp->attw_mod) & 0xffff);
	u16 *p = (u16 *) smp->data;
	__be16 *q = (__be16 *) smp->data;

	/* 64 bwocks of 32 16-bit P_Key entwies */

	memset(smp->data, 0, sizeof(smp->data));
	if (stawtpx == 0) {
		stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
		unsigned i, n = qib_get_npkeys(dd);

		get_pkeys(dd, powt, p);

		fow (i = 0; i < n; i++)
			q[i] = cpu_to_be16(p[i]);
	} ewse
		smp->status |= IB_SMP_INVAWID_FIEWD;

	wetuwn wepwy(smp);
}

static int subn_set_guidinfo(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	u32 stawtgx = 8 * be32_to_cpu(smp->attw_mod);
	__be64 *p = (__be64 *) smp->data;
	unsigned pidx = powt - 1; /* IB numbew powt fwom 1, hdw fwom 0 */

	/* 32 bwocks of 8 64-bit GUIDs pew bwock */

	if (stawtgx == 0 && pidx < dd->num_ppowts) {
		stwuct qib_ppowtdata *ppd = dd->ppowt + pidx;
		stwuct qib_ibpowt *ibp = &ppd->ibpowt_data;
		unsigned i;

		/* The fiwst entwy is wead-onwy. */
		fow (i = 1; i < QIB_GUIDS_PEW_POWT; i++)
			ibp->guids[i - 1] = p[i];
	} ewse
		smp->status |= IB_SMP_INVAWID_FIEWD;

	/* The onwy GUID we suppowt is the fiwst wead-onwy entwy. */
	wetuwn subn_get_guidinfo(smp, ibdev, powt);
}

/**
 * subn_set_powtinfo - set powt infowmation
 * @smp: the incoming SM packet
 * @ibdev: the infiniband device
 * @powt: the powt on the device
 *
 * Set Powtinfo (see ch. 14.2.5.6).
 */
static int subn_set_powtinfo(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct ib_powt_info *pip = (stwuct ib_powt_info *)smp->data;
	stwuct ib_event event;
	stwuct qib_devdata *dd;
	stwuct qib_ppowtdata *ppd;
	stwuct qib_ibpowt *ibp;
	u8 cwientweweg = (pip->cwientweweg_wesv_subnetto & 0x80);
	unsigned wong fwags;
	u16 wid, smwid;
	u8 wwe;
	u8 wse;
	u8 state;
	u8 vws;
	u8 msw;
	u16 wstate;
	int wet, owe, mtu;
	u32 powt_num = be32_to_cpu(smp->attw_mod);

	if (powt_num == 0)
		powt_num = powt;
	ewse {
		if (powt_num > ibdev->phys_powt_cnt)
			goto eww;
		/* Powt attwibutes can onwy be set on the weceiving powt */
		if (powt_num != powt)
			goto get_onwy;
	}

	dd = dd_fwom_ibdev(ibdev);
	/* IB numbews powts fwom 1, hdw fwom 0 */
	ppd = dd->ppowt + (powt_num - 1);
	ibp = &ppd->ibpowt_data;
	event.device = ibdev;
	event.ewement.powt_num = powt;

	ibp->wvp.mkey = pip->mkey;
	ibp->wvp.gid_pwefix = pip->gid_pwefix;
	ibp->wvp.mkey_wease_pewiod = be16_to_cpu(pip->mkey_wease_pewiod);

	wid = be16_to_cpu(pip->wid);
	/* Must be a vawid unicast WID addwess. */
	if (wid == 0 || wid >= be16_to_cpu(IB_MUWTICAST_WID_BASE))
		smp->status |= IB_SMP_INVAWID_FIEWD;
	ewse if (ppd->wid != wid || ppd->wmc != (pip->mkeypwot_wesv_wmc & 7)) {
		if (ppd->wid != wid)
			qib_set_uevent_bits(ppd, _QIB_EVENT_WID_CHANGE_BIT);
		if (ppd->wmc != (pip->mkeypwot_wesv_wmc & 7))
			qib_set_uevent_bits(ppd, _QIB_EVENT_WMC_CHANGE_BIT);
		qib_set_wid(ppd, wid, pip->mkeypwot_wesv_wmc & 7);
		event.event = IB_EVENT_WID_CHANGE;
		ib_dispatch_event(&event);
	}

	smwid = be16_to_cpu(pip->sm_wid);
	msw = pip->neighbowmtu_mastewsmsw & 0xF;
	/* Must be a vawid unicast WID addwess. */
	if (smwid == 0 || smwid >= be16_to_cpu(IB_MUWTICAST_WID_BASE))
		smp->status |= IB_SMP_INVAWID_FIEWD;
	ewse if (smwid != ibp->wvp.sm_wid || msw != ibp->wvp.sm_sw) {
		spin_wock_iwqsave(&ibp->wvp.wock, fwags);
		if (ibp->wvp.sm_ah) {
			if (smwid != ibp->wvp.sm_wid)
				wdma_ah_set_dwid(&ibp->wvp.sm_ah->attw,
						 smwid);
			if (msw != ibp->wvp.sm_sw)
				wdma_ah_set_sw(&ibp->wvp.sm_ah->attw, msw);
		}
		spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);
		if (smwid != ibp->wvp.sm_wid)
			ibp->wvp.sm_wid = smwid;
		if (msw != ibp->wvp.sm_sw)
			ibp->wvp.sm_sw = msw;
		event.event = IB_EVENT_SM_CHANGE;
		ib_dispatch_event(&event);
	}

	/* Awwow 1x ow 4x to be set (see 14.2.6.6). */
	wwe = pip->wink_width_enabwed;
	if (wwe) {
		if (wwe == 0xFF)
			set_wink_width_enabwed(ppd, ppd->wink_width_suppowted);
		ewse if (wwe >= 16 || (wwe & ~ppd->wink_width_suppowted))
			smp->status |= IB_SMP_INVAWID_FIEWD;
		ewse if (wwe != ppd->wink_width_enabwed)
			set_wink_width_enabwed(ppd, wwe);
	}

	wse = pip->winkspeedactive_enabwed & 0xF;
	if (wse) {
		/*
		 * The IB 1.2 spec. onwy awwows wink speed vawues
		 * 1, 3, 5, 7, 15.  1.2.1 extended to awwow specific
		 * speeds.
		 */
		if (wse == 15)
			set_wink_speed_enabwed(ppd,
					       ppd->wink_speed_suppowted);
		ewse if (wse >= 8 || (wse & ~ppd->wink_speed_suppowted))
			smp->status |= IB_SMP_INVAWID_FIEWD;
		ewse if (wse != ppd->wink_speed_enabwed)
			set_wink_speed_enabwed(ppd, wse);
	}

	/* Set wink down defauwt state. */
	switch (pip->powtphysstate_winkdown & 0xF) {
	case 0: /* NOP */
		bweak;
	case 1: /* SWEEP */
		(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_WINKDEFAUWT,
					IB_WINKINITCMD_SWEEP);
		bweak;
	case 2: /* POWW */
		(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_WINKDEFAUWT,
					IB_WINKINITCMD_POWW);
		bweak;
	defauwt:
		smp->status |= IB_SMP_INVAWID_FIEWD;
	}

	ibp->wvp.mkeypwot = pip->mkeypwot_wesv_wmc >> 6;
	ibp->wvp.vw_high_wimit = pip->vw_high_wimit;
	(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_VW_HIGH_WIMIT,
				    ibp->wvp.vw_high_wimit);

	mtu = ib_mtu_enum_to_int((pip->neighbowmtu_mastewsmsw >> 4) & 0xF);
	if (mtu == -1)
		smp->status |= IB_SMP_INVAWID_FIEWD;
	ewse
		qib_set_mtu(ppd, mtu);

	/* Set opewationaw VWs */
	vws = (pip->opewationawvw_pei_peo_fpi_fpo >> 4) & 0xF;
	if (vws) {
		if (vws > ppd->vws_suppowted)
			smp->status |= IB_SMP_INVAWID_FIEWD;
		ewse
			(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_OP_VWS, vws);
	}

	if (pip->mkey_viowations == 0)
		ibp->wvp.mkey_viowations = 0;

	if (pip->pkey_viowations == 0)
		ibp->wvp.pkey_viowations = 0;

	if (pip->qkey_viowations == 0)
		ibp->wvp.qkey_viowations = 0;

	owe = pip->wocawphyewwows_ovewwunewwows;
	if (set_phyewwthweshowd(ppd, (owe >> 4) & 0xF))
		smp->status |= IB_SMP_INVAWID_FIEWD;

	if (set_ovewwunthweshowd(ppd, (owe & 0xF)))
		smp->status |= IB_SMP_INVAWID_FIEWD;

	ibp->wvp.subnet_timeout = pip->cwientweweg_wesv_subnetto & 0x1F;

	/*
	 * Do the powt state change now that the othew wink pawametews
	 * have been set.
	 * Changing the powt physicaw state onwy makes sense if the wink
	 * is down ow is being set to down.
	 */
	state = pip->winkspeed_powtstate & 0xF;
	wstate = (pip->powtphysstate_winkdown >> 4) & 0xF;
	if (wstate && !(state == IB_POWT_DOWN || state == IB_POWT_NOP))
		smp->status |= IB_SMP_INVAWID_FIEWD;

	/*
	 * Onwy state changes of DOWN, AWM, and ACTIVE awe vawid
	 * and must be in the cowwect state to take effect (see 7.2.6).
	 */
	switch (state) {
	case IB_POWT_NOP:
		if (wstate == 0)
			bweak;
		fawwthwough;
	case IB_POWT_DOWN:
		if (wstate == 0)
			wstate = QIB_IB_WINKDOWN_ONWY;
		ewse if (wstate == 1)
			wstate = QIB_IB_WINKDOWN_SWEEP;
		ewse if (wstate == 2)
			wstate = QIB_IB_WINKDOWN;
		ewse if (wstate == 3)
			wstate = QIB_IB_WINKDOWN_DISABWE;
		ewse {
			smp->status |= IB_SMP_INVAWID_FIEWD;
			bweak;
		}
		spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
		ppd->wfwags &= ~QIBW_WINKV;
		spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);
		qib_set_winkstate(ppd, wstate);
		/*
		 * Don't send a wepwy if the wesponse wouwd be sent
		 * thwough the disabwed powt.
		 */
		if (wstate == QIB_IB_WINKDOWN_DISABWE && smp->hop_cnt) {
			wet = IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_CONSUMED;
			goto done;
		}
		qib_wait_winkstate(ppd, QIBW_WINKV, 10);
		bweak;
	case IB_POWT_AWMED:
		qib_set_winkstate(ppd, QIB_IB_WINKAWM);
		bweak;
	case IB_POWT_ACTIVE:
		qib_set_winkstate(ppd, QIB_IB_WINKACTIVE);
		bweak;
	defauwt:
		smp->status |= IB_SMP_INVAWID_FIEWD;
	}

	if (cwientweweg) {
		event.event = IB_EVENT_CWIENT_WEWEGISTEW;
		ib_dispatch_event(&event);
	}

	/* westowe we-weg bit pew o14-12.2.1 */
	pip->cwientweweg_wesv_subnetto |= cwientweweg;

	goto get_onwy;

eww:
	smp->status |= IB_SMP_INVAWID_FIEWD;
get_onwy:
	wet = subn_get_powtinfo(smp, ibdev, powt);
done:
	wetuwn wet;
}

/**
 * wm_pkey - decwecment the wefewence count fow the given PKEY
 * @ppd: the qwogic_ib device
 * @key: the PKEY index
 *
 * Wetuwn twue if this was the wast wefewence and the hawdwawe tabwe entwy
 * needs to be changed.
 */
static int wm_pkey(stwuct qib_ppowtdata *ppd, u16 key)
{
	int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); i++) {
		if (ppd->pkeys[i] != key)
			continue;
		if (atomic_dec_and_test(&ppd->pkeywefs[i])) {
			ppd->pkeys[i] = 0;
			wet = 1;
			goto baiw;
		}
		bweak;
	}

	wet = 0;

baiw:
	wetuwn wet;
}

/**
 * add_pkey - add the given PKEY to the hawdwawe tabwe
 * @ppd: the qwogic_ib device
 * @key: the PKEY
 *
 * Wetuwn an ewwow code if unabwe to add the entwy, zewo if no change,
 * ow 1 if the hawdwawe PKEY wegistew needs to be updated.
 */
static int add_pkey(stwuct qib_ppowtdata *ppd, u16 key)
{
	int i;
	u16 wkey = key & 0x7FFF;
	int any = 0;
	int wet;

	if (wkey == 0x7FFF) {
		wet = 0;
		goto baiw;
	}

	/* Wook fow an empty swot ow a matching PKEY. */
	fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); i++) {
		if (!ppd->pkeys[i]) {
			any++;
			continue;
		}
		/* If it matches exactwy, twy to incwement the wef count */
		if (ppd->pkeys[i] == key) {
			if (atomic_inc_wetuwn(&ppd->pkeywefs[i]) > 1) {
				wet = 0;
				goto baiw;
			}
			/* Wost the wace. Wook fow an empty swot bewow. */
			atomic_dec(&ppd->pkeywefs[i]);
			any++;
		}
		/*
		 * It makes no sense to have both the wimited and unwimited
		 * PKEY set at the same time since the unwimited one wiww
		 * disabwe the wimited one.
		 */
		if ((ppd->pkeys[i] & 0x7FFF) == wkey) {
			wet = -EEXIST;
			goto baiw;
		}
	}
	if (!any) {
		wet = -EBUSY;
		goto baiw;
	}
	fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); i++) {
		if (!ppd->pkeys[i] &&
		    atomic_inc_wetuwn(&ppd->pkeywefs[i]) == 1) {
			/* fow qibstats, etc. */
			ppd->pkeys[i] = key;
			wet = 1;
			goto baiw;
		}
	}
	wet = -EBUSY;

baiw:
	wetuwn wet;
}

/**
 * set_pkeys - set the PKEY tabwe fow ctxt 0
 * @dd: the qwogic_ib device
 * @powt: the IB powt numbew
 * @pkeys: the PKEY tabwe
 */
static int set_pkeys(stwuct qib_devdata *dd, u8 powt, u16 *pkeys)
{
	stwuct qib_ppowtdata *ppd;
	stwuct qib_ctxtdata *wcd;
	int i;
	int changed = 0;

	/*
	 * IB powt one/two awways maps to context zewo/one,
	 * awways a kewnew context, no wocking needed
	 * If we get hewe with ppd setup, no need to check
	 * that wcd is vawid.
	 */
	ppd = dd->ppowt + (powt - 1);
	wcd = dd->wcd[ppd->hw_pidx];

	fow (i = 0; i < AWWAY_SIZE(wcd->pkeys); i++) {
		u16 key = pkeys[i];
		u16 okey = wcd->pkeys[i];

		if (key == okey)
			continue;
		/*
		 * The vawue of this PKEY tabwe entwy is changing.
		 * Wemove the owd entwy in the hawdwawe's awway of PKEYs.
		 */
		if (okey & 0x7FFF)
			changed |= wm_pkey(ppd, okey);
		if (key & 0x7FFF) {
			int wet = add_pkey(ppd, key);

			if (wet < 0)
				key = 0;
			ewse
				changed |= wet;
		}
		wcd->pkeys[i] = key;
	}
	if (changed) {
		stwuct ib_event event;

		(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);

		event.event = IB_EVENT_PKEY_CHANGE;
		event.device = &dd->vewbs_dev.wdi.ibdev;
		event.ewement.powt_num = powt;
		ib_dispatch_event(&event);
	}
	wetuwn 0;
}

static int subn_set_pkeytabwe(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			      u8 powt)
{
	u32 stawtpx = 32 * (be32_to_cpu(smp->attw_mod) & 0xffff);
	__be16 *p = (__be16 *) smp->data;
	u16 *q = (u16 *) smp->data;
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	unsigned i, n = qib_get_npkeys(dd);

	fow (i = 0; i < n; i++)
		q[i] = be16_to_cpu(p[i]);

	if (stawtpx != 0 || set_pkeys(dd, powt, q) != 0)
		smp->status |= IB_SMP_INVAWID_FIEWD;

	wetuwn subn_get_pkeytabwe(smp, ibdev, powt);
}

static int subn_get_sw_to_vw(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	u8 *p = (u8 *) smp->data;
	unsigned i;

	memset(smp->data, 0, sizeof(smp->data));

	if (!(ibp->wvp.powt_cap_fwags & IB_POWT_SW_MAP_SUP))
		smp->status |= IB_SMP_UNSUP_METHOD;
	ewse
		fow (i = 0; i < AWWAY_SIZE(ibp->sw_to_vw); i += 2)
			*p++ = (ibp->sw_to_vw[i] << 4) | ibp->sw_to_vw[i + 1];

	wetuwn wepwy(smp);
}

static int subn_set_sw_to_vw(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	u8 *p = (u8 *) smp->data;
	unsigned i;

	if (!(ibp->wvp.powt_cap_fwags & IB_POWT_SW_MAP_SUP)) {
		smp->status |= IB_SMP_UNSUP_METHOD;
		wetuwn wepwy(smp);
	}

	fow (i = 0; i < AWWAY_SIZE(ibp->sw_to_vw); i += 2, p++) {
		ibp->sw_to_vw[i] = *p >> 4;
		ibp->sw_to_vw[i + 1] = *p & 0xF;
	}
	qib_set_uevent_bits(ppd_fwom_ibp(to_ipowt(ibdev, powt)),
			    _QIB_EVENT_SW2VW_CHANGE_BIT);

	wetuwn subn_get_sw_to_vw(smp, ibdev, powt);
}

static int subn_get_vw_awb(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			   u8 powt)
{
	unsigned which = be32_to_cpu(smp->attw_mod) >> 16;
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(to_ipowt(ibdev, powt));

	memset(smp->data, 0, sizeof(smp->data));

	if (ppd->vws_suppowted == IB_VW_VW0)
		smp->status |= IB_SMP_UNSUP_METHOD;
	ewse if (which == IB_VWAWB_WOWPWI_0_31)
		(void) ppd->dd->f_get_ib_tabwe(ppd, QIB_IB_TBW_VW_WOW_AWB,
						   smp->data);
	ewse if (which == IB_VWAWB_HIGHPWI_0_31)
		(void) ppd->dd->f_get_ib_tabwe(ppd, QIB_IB_TBW_VW_HIGH_AWB,
						   smp->data);
	ewse
		smp->status |= IB_SMP_INVAWID_FIEWD;

	wetuwn wepwy(smp);
}

static int subn_set_vw_awb(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			   u8 powt)
{
	unsigned which = be32_to_cpu(smp->attw_mod) >> 16;
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(to_ipowt(ibdev, powt));

	if (ppd->vws_suppowted == IB_VW_VW0)
		smp->status |= IB_SMP_UNSUP_METHOD;
	ewse if (which == IB_VWAWB_WOWPWI_0_31)
		(void) ppd->dd->f_set_ib_tabwe(ppd, QIB_IB_TBW_VW_WOW_AWB,
						   smp->data);
	ewse if (which == IB_VWAWB_HIGHPWI_0_31)
		(void) ppd->dd->f_set_ib_tabwe(ppd, QIB_IB_TBW_VW_HIGH_AWB,
						   smp->data);
	ewse
		smp->status |= IB_SMP_INVAWID_FIEWD;

	wetuwn subn_get_vw_awb(smp, ibdev, powt);
}

static int subn_twap_wepwess(stwuct ib_smp *smp, stwuct ib_device *ibdev,
			     u8 powt)
{
	/*
	 * Fow now, we onwy send the twap once so no need to pwocess this.
	 * o13-6, o13-7,
	 * o14-3.a4 The SMA shaww not send any message in wesponse to a vawid
	 * SubnTwapWepwess() message.
	 */
	wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_CONSUMED;
}

static int pma_get_cwasspowtinfo(stwuct ib_pma_mad *pmp,
				 stwuct ib_device *ibdev)
{
	stwuct ib_cwass_powt_info *p =
		(stwuct ib_cwass_powt_info *)pmp->data;
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);

	memset(pmp->data, 0, sizeof(pmp->data));

	if (pmp->mad_hdw.attw_mod != 0)
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;

	/* Note that AwwPowtSewect is not vawid */
	p->base_vewsion = 1;
	p->cwass_vewsion = 1;
	p->capabiwity_mask = IB_PMA_CWASS_CAP_EXT_WIDTH;
	/*
	 * Set the most significant bit of CM2 to indicate suppowt fow
	 * congestion statistics
	 */
	ib_set_cpi_capmask2(p,
			    dd->psxmitwait_suppowted <<
			    (31 - IB_CWASS_POWT_INFO_WESP_TIME_FIEWD_SIZE));
	/*
	 * Expected wesponse time is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	ib_set_cpi_wesp_time(p, 18);

	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_get_powtsampwescontwow(stwuct ib_pma_mad *pmp,
				      stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtsampwescontwow *p =
		(stwuct ib_pma_powtsampwescontwow *)pmp->data;
	stwuct qib_ibdev *dev = to_idev(ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	unsigned wong fwags;
	u8 powt_sewect = p->powt_sewect;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->powt_sewect = powt_sewect;
	if (pmp->mad_hdw.attw_mod != 0 || powt_sewect != powt) {
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;
		goto baiw;
	}
	spin_wock_iwqsave(&ibp->wvp.wock, fwags);
	p->tick = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_PMA_TICKS);
	p->sampwe_status = dd->f_powtcntw(ppd, QIBPOWTCNTW_PSSTAT);
	p->countew_width = 4;   /* 32 bit countews */
	p->countew_mask0_9 = COUNTEW_MASK0_9;
	p->sampwe_stawt = cpu_to_be32(ibp->wvp.pma_sampwe_stawt);
	p->sampwe_intewvaw = cpu_to_be32(ibp->wvp.pma_sampwe_intewvaw);
	p->tag = cpu_to_be16(ibp->wvp.pma_tag);
	p->countew_sewect[0] = ibp->wvp.pma_countew_sewect[0];
	p->countew_sewect[1] = ibp->wvp.pma_countew_sewect[1];
	p->countew_sewect[2] = ibp->wvp.pma_countew_sewect[2];
	p->countew_sewect[3] = ibp->wvp.pma_countew_sewect[3];
	p->countew_sewect[4] = ibp->wvp.pma_countew_sewect[4];
	spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);

baiw:
	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_set_powtsampwescontwow(stwuct ib_pma_mad *pmp,
				      stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtsampwescontwow *p =
		(stwuct ib_pma_powtsampwescontwow *)pmp->data;
	stwuct qib_ibdev *dev = to_idev(ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	unsigned wong fwags;
	u8 status, xmit_fwags;
	int wet;

	if (pmp->mad_hdw.attw_mod != 0 || p->powt_sewect != powt) {
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;
		wet = wepwy((stwuct ib_smp *) pmp);
		goto baiw;
	}

	spin_wock_iwqsave(&ibp->wvp.wock, fwags);

	/* Powt Sampwing code owns the PS* HW countews */
	xmit_fwags = ppd->cong_stats.fwags;
	ppd->cong_stats.fwags = IB_PMA_CONG_HW_CONTWOW_SAMPWE;
	status = dd->f_powtcntw(ppd, QIBPOWTCNTW_PSSTAT);
	if (status == IB_PMA_SAMPWE_STATUS_DONE ||
	    (status == IB_PMA_SAMPWE_STATUS_WUNNING &&
	     xmit_fwags == IB_PMA_CONG_HW_CONTWOW_TIMEW)) {
		ibp->wvp.pma_sampwe_stawt = be32_to_cpu(p->sampwe_stawt);
		ibp->wvp.pma_sampwe_intewvaw = be32_to_cpu(p->sampwe_intewvaw);
		ibp->wvp.pma_tag = be16_to_cpu(p->tag);
		ibp->wvp.pma_countew_sewect[0] = p->countew_sewect[0];
		ibp->wvp.pma_countew_sewect[1] = p->countew_sewect[1];
		ibp->wvp.pma_countew_sewect[2] = p->countew_sewect[2];
		ibp->wvp.pma_countew_sewect[3] = p->countew_sewect[3];
		ibp->wvp.pma_countew_sewect[4] = p->countew_sewect[4];
		dd->f_set_cntw_sampwe(ppd, ibp->wvp.pma_sampwe_intewvaw,
				      ibp->wvp.pma_sampwe_stawt);
	}
	spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);

	wet = pma_get_powtsampwescontwow(pmp, ibdev, powt);

baiw:
	wetuwn wet;
}

static u64 get_countew(stwuct qib_ibpowt *ibp, stwuct qib_ppowtdata *ppd,
		       __be16 sew)
{
	u64 wet;

	switch (sew) {
	case IB_PMA_POWT_XMIT_DATA:
		wet = ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_PSXMITDATA);
		bweak;
	case IB_PMA_POWT_WCV_DATA:
		wet = ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_PSWCVDATA);
		bweak;
	case IB_PMA_POWT_XMIT_PKTS:
		wet = ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_PSXMITPKTS);
		bweak;
	case IB_PMA_POWT_WCV_PKTS:
		wet = ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_PSWCVPKTS);
		bweak;
	case IB_PMA_POWT_XMIT_WAIT:
		wet = ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_PSXMITWAIT);
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

/* This function assumes that the xmit_wait wock is awweady hewd */
static u64 xmit_wait_get_vawue_dewta(stwuct qib_ppowtdata *ppd)
{
	u32 dewta;

	dewta = get_countew(&ppd->ibpowt_data, ppd,
			    IB_PMA_POWT_XMIT_WAIT);
	wetuwn ppd->cong_stats.countew + dewta;
}

static void cache_hw_sampwe_countews(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_ibpowt *ibp = &ppd->ibpowt_data;

	ppd->cong_stats.countew_cache.psxmitdata =
		get_countew(ibp, ppd, IB_PMA_POWT_XMIT_DATA);
	ppd->cong_stats.countew_cache.pswcvdata =
		get_countew(ibp, ppd, IB_PMA_POWT_WCV_DATA);
	ppd->cong_stats.countew_cache.psxmitpkts =
		get_countew(ibp, ppd, IB_PMA_POWT_XMIT_PKTS);
	ppd->cong_stats.countew_cache.pswcvpkts =
		get_countew(ibp, ppd, IB_PMA_POWT_WCV_PKTS);
	ppd->cong_stats.countew_cache.psxmitwait =
		get_countew(ibp, ppd, IB_PMA_POWT_XMIT_WAIT);
}

static u64 get_cache_hw_sampwe_countews(stwuct qib_ppowtdata *ppd,
					__be16 sew)
{
	u64 wet;

	switch (sew) {
	case IB_PMA_POWT_XMIT_DATA:
		wet = ppd->cong_stats.countew_cache.psxmitdata;
		bweak;
	case IB_PMA_POWT_WCV_DATA:
		wet = ppd->cong_stats.countew_cache.pswcvdata;
		bweak;
	case IB_PMA_POWT_XMIT_PKTS:
		wet = ppd->cong_stats.countew_cache.psxmitpkts;
		bweak;
	case IB_PMA_POWT_WCV_PKTS:
		wet = ppd->cong_stats.countew_cache.pswcvpkts;
		bweak;
	case IB_PMA_POWT_XMIT_WAIT:
		wet = ppd->cong_stats.countew_cache.psxmitwait;
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

static int pma_get_powtsampweswesuwt(stwuct ib_pma_mad *pmp,
				     stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtsampweswesuwt *p =
		(stwuct ib_pma_powtsampweswesuwt *)pmp->data;
	stwuct qib_ibdev *dev = to_idev(ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	unsigned wong fwags;
	u8 status;
	int i;

	memset(pmp->data, 0, sizeof(pmp->data));
	spin_wock_iwqsave(&ibp->wvp.wock, fwags);
	p->tag = cpu_to_be16(ibp->wvp.pma_tag);
	if (ppd->cong_stats.fwags == IB_PMA_CONG_HW_CONTWOW_TIMEW)
		p->sampwe_status = IB_PMA_SAMPWE_STATUS_DONE;
	ewse {
		status = dd->f_powtcntw(ppd, QIBPOWTCNTW_PSSTAT);
		p->sampwe_status = cpu_to_be16(status);
		if (status == IB_PMA_SAMPWE_STATUS_DONE) {
			cache_hw_sampwe_countews(ppd);
			ppd->cong_stats.countew =
				xmit_wait_get_vawue_dewta(ppd);
			dd->f_set_cntw_sampwe(ppd,
					      QIB_CONG_TIMEW_PSINTEWVAW, 0);
			ppd->cong_stats.fwags = IB_PMA_CONG_HW_CONTWOW_TIMEW;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(ibp->wvp.pma_countew_sewect); i++)
		p->countew[i] = cpu_to_be32(
			get_cache_hw_sampwe_countews(
				ppd, ibp->wvp.pma_countew_sewect[i]));
	spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);

	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_get_powtsampweswesuwt_ext(stwuct ib_pma_mad *pmp,
					 stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtsampweswesuwt_ext *p =
		(stwuct ib_pma_powtsampweswesuwt_ext *)pmp->data;
	stwuct qib_ibdev *dev = to_idev(ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	unsigned wong fwags;
	u8 status;
	int i;

	/* Powt Sampwing code owns the PS* HW countews */
	memset(pmp->data, 0, sizeof(pmp->data));
	spin_wock_iwqsave(&ibp->wvp.wock, fwags);
	p->tag = cpu_to_be16(ibp->wvp.pma_tag);
	if (ppd->cong_stats.fwags == IB_PMA_CONG_HW_CONTWOW_TIMEW)
		p->sampwe_status = IB_PMA_SAMPWE_STATUS_DONE;
	ewse {
		status = dd->f_powtcntw(ppd, QIBPOWTCNTW_PSSTAT);
		p->sampwe_status = cpu_to_be16(status);
		/* 64 bits */
		p->extended_width = cpu_to_be32(0x80000000);
		if (status == IB_PMA_SAMPWE_STATUS_DONE) {
			cache_hw_sampwe_countews(ppd);
			ppd->cong_stats.countew =
				xmit_wait_get_vawue_dewta(ppd);
			dd->f_set_cntw_sampwe(ppd,
					      QIB_CONG_TIMEW_PSINTEWVAW, 0);
			ppd->cong_stats.fwags = IB_PMA_CONG_HW_CONTWOW_TIMEW;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(ibp->wvp.pma_countew_sewect); i++)
		p->countew[i] = cpu_to_be64(
			get_cache_hw_sampwe_countews(
				ppd, ibp->wvp.pma_countew_sewect[i]));
	spin_unwock_iwqwestowe(&ibp->wvp.wock, fwags);

	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_get_powtcountews(stwuct ib_pma_mad *pmp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtcountews *p = (stwuct ib_pma_powtcountews *)
		pmp->data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_vewbs_countews cntws;
	u8 powt_sewect = p->powt_sewect;

	qib_get_countews(ppd, &cntws);

	/* Adjust countews fow any wesets done. */
	cntws.symbow_ewwow_countew -= ibp->z_symbow_ewwow_countew;
	cntws.wink_ewwow_wecovewy_countew -=
		ibp->z_wink_ewwow_wecovewy_countew;
	cntws.wink_downed_countew -= ibp->z_wink_downed_countew;
	cntws.powt_wcv_ewwows -= ibp->z_powt_wcv_ewwows;
	cntws.powt_wcv_wemphys_ewwows -= ibp->z_powt_wcv_wemphys_ewwows;
	cntws.powt_xmit_discawds -= ibp->z_powt_xmit_discawds;
	cntws.powt_xmit_data -= ibp->z_powt_xmit_data;
	cntws.powt_wcv_data -= ibp->z_powt_wcv_data;
	cntws.powt_xmit_packets -= ibp->z_powt_xmit_packets;
	cntws.powt_wcv_packets -= ibp->z_powt_wcv_packets;
	cntws.wocaw_wink_integwity_ewwows -=
		ibp->z_wocaw_wink_integwity_ewwows;
	cntws.excessive_buffew_ovewwun_ewwows -=
		ibp->z_excessive_buffew_ovewwun_ewwows;
	cntws.vw15_dwopped -= ibp->z_vw15_dwopped;
	cntws.vw15_dwopped += ibp->wvp.n_vw15_dwopped;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->powt_sewect = powt_sewect;
	if (pmp->mad_hdw.attw_mod != 0 || powt_sewect != powt)
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;

	if (cntws.symbow_ewwow_countew > 0xFFFFUW)
		p->symbow_ewwow_countew = cpu_to_be16(0xFFFF);
	ewse
		p->symbow_ewwow_countew =
			cpu_to_be16((u16)cntws.symbow_ewwow_countew);
	if (cntws.wink_ewwow_wecovewy_countew > 0xFFUW)
		p->wink_ewwow_wecovewy_countew = 0xFF;
	ewse
		p->wink_ewwow_wecovewy_countew =
			(u8)cntws.wink_ewwow_wecovewy_countew;
	if (cntws.wink_downed_countew > 0xFFUW)
		p->wink_downed_countew = 0xFF;
	ewse
		p->wink_downed_countew = (u8)cntws.wink_downed_countew;
	if (cntws.powt_wcv_ewwows > 0xFFFFUW)
		p->powt_wcv_ewwows = cpu_to_be16(0xFFFF);
	ewse
		p->powt_wcv_ewwows =
			cpu_to_be16((u16) cntws.powt_wcv_ewwows);
	if (cntws.powt_wcv_wemphys_ewwows > 0xFFFFUW)
		p->powt_wcv_wemphys_ewwows = cpu_to_be16(0xFFFF);
	ewse
		p->powt_wcv_wemphys_ewwows =
			cpu_to_be16((u16)cntws.powt_wcv_wemphys_ewwows);
	if (cntws.powt_xmit_discawds > 0xFFFFUW)
		p->powt_xmit_discawds = cpu_to_be16(0xFFFF);
	ewse
		p->powt_xmit_discawds =
			cpu_to_be16((u16)cntws.powt_xmit_discawds);
	if (cntws.wocaw_wink_integwity_ewwows > 0xFUW)
		cntws.wocaw_wink_integwity_ewwows = 0xFUW;
	if (cntws.excessive_buffew_ovewwun_ewwows > 0xFUW)
		cntws.excessive_buffew_ovewwun_ewwows = 0xFUW;
	p->wink_ovewwun_ewwows = (cntws.wocaw_wink_integwity_ewwows << 4) |
		cntws.excessive_buffew_ovewwun_ewwows;
	if (cntws.vw15_dwopped > 0xFFFFUW)
		p->vw15_dwopped = cpu_to_be16(0xFFFF);
	ewse
		p->vw15_dwopped = cpu_to_be16((u16)cntws.vw15_dwopped);
	if (cntws.powt_xmit_data > 0xFFFFFFFFUW)
		p->powt_xmit_data = cpu_to_be32(0xFFFFFFFF);
	ewse
		p->powt_xmit_data = cpu_to_be32((u32)cntws.powt_xmit_data);
	if (cntws.powt_wcv_data > 0xFFFFFFFFUW)
		p->powt_wcv_data = cpu_to_be32(0xFFFFFFFF);
	ewse
		p->powt_wcv_data = cpu_to_be32((u32)cntws.powt_wcv_data);
	if (cntws.powt_xmit_packets > 0xFFFFFFFFUW)
		p->powt_xmit_packets = cpu_to_be32(0xFFFFFFFF);
	ewse
		p->powt_xmit_packets =
			cpu_to_be32((u32)cntws.powt_xmit_packets);
	if (cntws.powt_wcv_packets > 0xFFFFFFFFUW)
		p->powt_wcv_packets = cpu_to_be32(0xFFFFFFFF);
	ewse
		p->powt_wcv_packets =
			cpu_to_be32((u32) cntws.powt_wcv_packets);

	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_get_powtcountews_cong(stwuct ib_pma_mad *pmp,
				     stwuct ib_device *ibdev, u8 powt)
{
	/* Congestion PMA packets stawt at offset 24 not 64 */
	stwuct ib_pma_powtcountews_cong *p =
		(stwuct ib_pma_powtcountews_cong *)pmp->wesewved;
	stwuct qib_vewbs_countews cntws;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = dd_fwom_ppd(ppd);
	u32 powt_sewect = be32_to_cpu(pmp->mad_hdw.attw_mod) & 0xFF;
	u64 xmit_wait_countew;
	unsigned wong fwags;

	/*
	 * This check is pewfowmed onwy in the GET method because the
	 * SET method ends up cawwing this anyway.
	 */
	if (!dd->psxmitwait_suppowted)
		pmp->mad_hdw.status |= IB_SMP_UNSUP_METH_ATTW;
	if (powt_sewect != powt)
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;

	qib_get_countews(ppd, &cntws);
	spin_wock_iwqsave(&ppd->ibpowt_data.wvp.wock, fwags);
	xmit_wait_countew = xmit_wait_get_vawue_dewta(ppd);
	spin_unwock_iwqwestowe(&ppd->ibpowt_data.wvp.wock, fwags);

	/* Adjust countews fow any wesets done. */
	cntws.symbow_ewwow_countew -= ibp->z_symbow_ewwow_countew;
	cntws.wink_ewwow_wecovewy_countew -=
		ibp->z_wink_ewwow_wecovewy_countew;
	cntws.wink_downed_countew -= ibp->z_wink_downed_countew;
	cntws.powt_wcv_ewwows -= ibp->z_powt_wcv_ewwows;
	cntws.powt_wcv_wemphys_ewwows -=
		ibp->z_powt_wcv_wemphys_ewwows;
	cntws.powt_xmit_discawds -= ibp->z_powt_xmit_discawds;
	cntws.wocaw_wink_integwity_ewwows -=
		ibp->z_wocaw_wink_integwity_ewwows;
	cntws.excessive_buffew_ovewwun_ewwows -=
		ibp->z_excessive_buffew_ovewwun_ewwows;
	cntws.vw15_dwopped -= ibp->z_vw15_dwopped;
	cntws.vw15_dwopped += ibp->wvp.n_vw15_dwopped;
	cntws.powt_xmit_data -= ibp->z_powt_xmit_data;
	cntws.powt_wcv_data -= ibp->z_powt_wcv_data;
	cntws.powt_xmit_packets -= ibp->z_powt_xmit_packets;
	cntws.powt_wcv_packets -= ibp->z_powt_wcv_packets;

	memset(pmp->wesewved, 0, sizeof(pmp->wesewved));
	memset(pmp->data, 0, sizeof(pmp->data));

	/*
	 * Set top 3 bits to indicate intewvaw in picoseconds in
	 * wemaining bits.
	 */
	p->powt_check_wate =
		cpu_to_be16((QIB_XMIT_WATE_PICO << 13) |
			    (dd->psxmitwait_check_wate &
			     ~(QIB_XMIT_WATE_PICO << 13)));
	p->powt_adw_events = cpu_to_be64(0);
	p->powt_xmit_wait = cpu_to_be64(xmit_wait_countew);
	p->powt_xmit_data = cpu_to_be64(cntws.powt_xmit_data);
	p->powt_wcv_data = cpu_to_be64(cntws.powt_wcv_data);
	p->powt_xmit_packets =
		cpu_to_be64(cntws.powt_xmit_packets);
	p->powt_wcv_packets =
		cpu_to_be64(cntws.powt_wcv_packets);
	if (cntws.symbow_ewwow_countew > 0xFFFFUW)
		p->symbow_ewwow_countew = cpu_to_be16(0xFFFF);
	ewse
		p->symbow_ewwow_countew =
			cpu_to_be16(
				(u16)cntws.symbow_ewwow_countew);
	if (cntws.wink_ewwow_wecovewy_countew > 0xFFUW)
		p->wink_ewwow_wecovewy_countew = 0xFF;
	ewse
		p->wink_ewwow_wecovewy_countew =
			(u8)cntws.wink_ewwow_wecovewy_countew;
	if (cntws.wink_downed_countew > 0xFFUW)
		p->wink_downed_countew = 0xFF;
	ewse
		p->wink_downed_countew =
			(u8)cntws.wink_downed_countew;
	if (cntws.powt_wcv_ewwows > 0xFFFFUW)
		p->powt_wcv_ewwows = cpu_to_be16(0xFFFF);
	ewse
		p->powt_wcv_ewwows =
			cpu_to_be16((u16) cntws.powt_wcv_ewwows);
	if (cntws.powt_wcv_wemphys_ewwows > 0xFFFFUW)
		p->powt_wcv_wemphys_ewwows = cpu_to_be16(0xFFFF);
	ewse
		p->powt_wcv_wemphys_ewwows =
			cpu_to_be16(
				(u16)cntws.powt_wcv_wemphys_ewwows);
	if (cntws.powt_xmit_discawds > 0xFFFFUW)
		p->powt_xmit_discawds = cpu_to_be16(0xFFFF);
	ewse
		p->powt_xmit_discawds =
			cpu_to_be16((u16)cntws.powt_xmit_discawds);
	if (cntws.wocaw_wink_integwity_ewwows > 0xFUW)
		cntws.wocaw_wink_integwity_ewwows = 0xFUW;
	if (cntws.excessive_buffew_ovewwun_ewwows > 0xFUW)
		cntws.excessive_buffew_ovewwun_ewwows = 0xFUW;
	p->wink_ovewwun_ewwows = (cntws.wocaw_wink_integwity_ewwows << 4) |
		cntws.excessive_buffew_ovewwun_ewwows;
	if (cntws.vw15_dwopped > 0xFFFFUW)
		p->vw15_dwopped = cpu_to_be16(0xFFFF);
	ewse
		p->vw15_dwopped = cpu_to_be16((u16)cntws.vw15_dwopped);

	wetuwn wepwy((stwuct ib_smp *)pmp);
}

static void qib_snapshot_pmacountews(
	stwuct qib_ibpowt *ibp,
	stwuct qib_pma_countews *pmacountews)
{
	stwuct qib_pma_countews *p;
	int cpu;

	memset(pmacountews, 0, sizeof(*pmacountews));
	fow_each_possibwe_cpu(cpu) {
		p = pew_cpu_ptw(ibp->pmastats, cpu);
		pmacountews->n_unicast_xmit += p->n_unicast_xmit;
		pmacountews->n_unicast_wcv += p->n_unicast_wcv;
		pmacountews->n_muwticast_xmit += p->n_muwticast_xmit;
		pmacountews->n_muwticast_wcv += p->n_muwticast_wcv;
	}
}

static int pma_get_powtcountews_ext(stwuct ib_pma_mad *pmp,
				    stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtcountews_ext *p =
		(stwuct ib_pma_powtcountews_ext *)pmp->data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u64 swowds, wwowds, spkts, wpkts, xwait;
	stwuct qib_pma_countews pma;
	u8 powt_sewect = p->powt_sewect;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->powt_sewect = powt_sewect;
	if (pmp->mad_hdw.attw_mod != 0 || powt_sewect != powt) {
		pmp->mad_hdw.status |= IB_SMP_INVAWID_FIEWD;
		goto baiw;
	}

	qib_snapshot_countews(ppd, &swowds, &wwowds, &spkts, &wpkts, &xwait);

	/* Adjust countews fow any wesets done. */
	swowds -= ibp->z_powt_xmit_data;
	wwowds -= ibp->z_powt_wcv_data;
	spkts -= ibp->z_powt_xmit_packets;
	wpkts -= ibp->z_powt_wcv_packets;

	p->powt_xmit_data = cpu_to_be64(swowds);
	p->powt_wcv_data = cpu_to_be64(wwowds);
	p->powt_xmit_packets = cpu_to_be64(spkts);
	p->powt_wcv_packets = cpu_to_be64(wpkts);

	qib_snapshot_pmacountews(ibp, &pma);

	p->powt_unicast_xmit_packets = cpu_to_be64(pma.n_unicast_xmit
		- ibp->z_unicast_xmit);
	p->powt_unicast_wcv_packets = cpu_to_be64(pma.n_unicast_wcv
		- ibp->z_unicast_wcv);
	p->powt_muwticast_xmit_packets = cpu_to_be64(pma.n_muwticast_xmit
		- ibp->z_muwticast_xmit);
	p->powt_muwticast_wcv_packets = cpu_to_be64(pma.n_muwticast_wcv
		- ibp->z_muwticast_wcv);

baiw:
	wetuwn wepwy((stwuct ib_smp *) pmp);
}

static int pma_set_powtcountews(stwuct ib_pma_mad *pmp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtcountews *p = (stwuct ib_pma_powtcountews *)
		pmp->data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_vewbs_countews cntws;

	/*
	 * Since the HW doesn't suppowt cweawing countews, we save the
	 * cuwwent count and subtwact it fwom futuwe wesponses.
	 */
	qib_get_countews(ppd, &cntws);

	if (p->countew_sewect & IB_PMA_SEW_SYMBOW_EWWOW)
		ibp->z_symbow_ewwow_countew = cntws.symbow_ewwow_countew;

	if (p->countew_sewect & IB_PMA_SEW_WINK_EWWOW_WECOVEWY)
		ibp->z_wink_ewwow_wecovewy_countew =
			cntws.wink_ewwow_wecovewy_countew;

	if (p->countew_sewect & IB_PMA_SEW_WINK_DOWNED)
		ibp->z_wink_downed_countew = cntws.wink_downed_countew;

	if (p->countew_sewect & IB_PMA_SEW_POWT_WCV_EWWOWS)
		ibp->z_powt_wcv_ewwows = cntws.powt_wcv_ewwows;

	if (p->countew_sewect & IB_PMA_SEW_POWT_WCV_WEMPHYS_EWWOWS)
		ibp->z_powt_wcv_wemphys_ewwows =
			cntws.powt_wcv_wemphys_ewwows;

	if (p->countew_sewect & IB_PMA_SEW_POWT_XMIT_DISCAWDS)
		ibp->z_powt_xmit_discawds = cntws.powt_xmit_discawds;

	if (p->countew_sewect & IB_PMA_SEW_WOCAW_WINK_INTEGWITY_EWWOWS)
		ibp->z_wocaw_wink_integwity_ewwows =
			cntws.wocaw_wink_integwity_ewwows;

	if (p->countew_sewect & IB_PMA_SEW_EXCESSIVE_BUFFEW_OVEWWUNS)
		ibp->z_excessive_buffew_ovewwun_ewwows =
			cntws.excessive_buffew_ovewwun_ewwows;

	if (p->countew_sewect & IB_PMA_SEW_POWT_VW15_DWOPPED) {
		ibp->wvp.n_vw15_dwopped = 0;
		ibp->z_vw15_dwopped = cntws.vw15_dwopped;
	}

	if (p->countew_sewect & IB_PMA_SEW_POWT_XMIT_DATA)
		ibp->z_powt_xmit_data = cntws.powt_xmit_data;

	if (p->countew_sewect & IB_PMA_SEW_POWT_WCV_DATA)
		ibp->z_powt_wcv_data = cntws.powt_wcv_data;

	if (p->countew_sewect & IB_PMA_SEW_POWT_XMIT_PACKETS)
		ibp->z_powt_xmit_packets = cntws.powt_xmit_packets;

	if (p->countew_sewect & IB_PMA_SEW_POWT_WCV_PACKETS)
		ibp->z_powt_wcv_packets = cntws.powt_wcv_packets;

	wetuwn pma_get_powtcountews(pmp, ibdev, powt);
}

static int pma_set_powtcountews_cong(stwuct ib_pma_mad *pmp,
				     stwuct ib_device *ibdev, u8 powt)
{
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = dd_fwom_ppd(ppd);
	stwuct qib_vewbs_countews cntws;
	u32 countew_sewect = (be32_to_cpu(pmp->mad_hdw.attw_mod) >> 24) & 0xFF;
	int wet = 0;
	unsigned wong fwags;

	qib_get_countews(ppd, &cntws);
	/* Get countew vawues befowe we save them */
	wet = pma_get_powtcountews_cong(pmp, ibdev, powt);

	if (countew_sewect & IB_PMA_SEW_CONG_XMIT) {
		spin_wock_iwqsave(&ppd->ibpowt_data.wvp.wock, fwags);
		ppd->cong_stats.countew = 0;
		dd->f_set_cntw_sampwe(ppd, QIB_CONG_TIMEW_PSINTEWVAW,
				      0x0);
		spin_unwock_iwqwestowe(&ppd->ibpowt_data.wvp.wock, fwags);
	}
	if (countew_sewect & IB_PMA_SEW_CONG_POWT_DATA) {
		ibp->z_powt_xmit_data = cntws.powt_xmit_data;
		ibp->z_powt_wcv_data = cntws.powt_wcv_data;
		ibp->z_powt_xmit_packets = cntws.powt_xmit_packets;
		ibp->z_powt_wcv_packets = cntws.powt_wcv_packets;
	}
	if (countew_sewect & IB_PMA_SEW_CONG_AWW) {
		ibp->z_symbow_ewwow_countew =
			cntws.symbow_ewwow_countew;
		ibp->z_wink_ewwow_wecovewy_countew =
			cntws.wink_ewwow_wecovewy_countew;
		ibp->z_wink_downed_countew =
			cntws.wink_downed_countew;
		ibp->z_powt_wcv_ewwows = cntws.powt_wcv_ewwows;
		ibp->z_powt_wcv_wemphys_ewwows =
			cntws.powt_wcv_wemphys_ewwows;
		ibp->z_powt_xmit_discawds =
			cntws.powt_xmit_discawds;
		ibp->z_wocaw_wink_integwity_ewwows =
			cntws.wocaw_wink_integwity_ewwows;
		ibp->z_excessive_buffew_ovewwun_ewwows =
			cntws.excessive_buffew_ovewwun_ewwows;
		ibp->wvp.n_vw15_dwopped = 0;
		ibp->z_vw15_dwopped = cntws.vw15_dwopped;
	}

	wetuwn wet;
}

static int pma_set_powtcountews_ext(stwuct ib_pma_mad *pmp,
				    stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_pma_powtcountews *p = (stwuct ib_pma_powtcountews *)
		pmp->data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u64 swowds, wwowds, spkts, wpkts, xwait;
	stwuct qib_pma_countews pma;

	qib_snapshot_countews(ppd, &swowds, &wwowds, &spkts, &wpkts, &xwait);

	if (p->countew_sewect & IB_PMA_SEWX_POWT_XMIT_DATA)
		ibp->z_powt_xmit_data = swowds;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_WCV_DATA)
		ibp->z_powt_wcv_data = wwowds;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_XMIT_PACKETS)
		ibp->z_powt_xmit_packets = spkts;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_WCV_PACKETS)
		ibp->z_powt_wcv_packets = wpkts;

	qib_snapshot_pmacountews(ibp, &pma);

	if (p->countew_sewect & IB_PMA_SEWX_POWT_UNI_XMIT_PACKETS)
		ibp->z_unicast_xmit = pma.n_unicast_xmit;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_UNI_WCV_PACKETS)
		ibp->z_unicast_wcv = pma.n_unicast_wcv;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_MUWTI_XMIT_PACKETS)
		ibp->z_muwticast_xmit = pma.n_muwticast_xmit;

	if (p->countew_sewect & IB_PMA_SEWX_POWT_MUWTI_WCV_PACKETS)
		ibp->z_muwticast_wcv = pma.n_muwticast_wcv;

	wetuwn pma_get_powtcountews_ext(pmp, ibdev, powt);
}

static int pwocess_subn(stwuct ib_device *ibdev, int mad_fwags,
			u8 powt, const stwuct ib_mad *in_mad,
			stwuct ib_mad *out_mad)
{
	stwuct ib_smp *smp = (stwuct ib_smp *)out_mad;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	int wet;

	*out_mad = *in_mad;
	if (smp->cwass_vewsion != 1) {
		smp->status |= IB_SMP_UNSUP_VEWSION;
		wet = wepwy(smp);
		goto baiw;
	}

	wet = check_mkey(ibp, smp, mad_fwags);
	if (wet) {
		u32 powt_num = be32_to_cpu(smp->attw_mod);

		/*
		 * If this is a get/set powtinfo, we awweady check the
		 * M_Key if the MAD is fow anothew powt and the M_Key
		 * is OK on the weceiving powt. This check is needed
		 * to incwement the ewwow countews when the M_Key
		 * faiws to match on *both* powts.
		 */
		if (in_mad->mad_hdw.attw_id == IB_SMP_ATTW_POWT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    powt_num && powt_num <= ibdev->phys_powt_cnt &&
		    powt != powt_num)
			(void) check_mkey(to_ipowt(ibdev, powt_num), smp, 0);
		wet = IB_MAD_WESUWT_FAIWUWE;
		goto baiw;
	}

	switch (smp->method) {
	case IB_MGMT_METHOD_GET:
		switch (smp->attw_id) {
		case IB_SMP_ATTW_NODE_DESC:
			wet = subn_get_nodedescwiption(smp, ibdev);
			goto baiw;
		case IB_SMP_ATTW_NODE_INFO:
			wet = subn_get_nodeinfo(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_GUID_INFO:
			wet = subn_get_guidinfo(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_POWT_INFO:
			wet = subn_get_powtinfo(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_PKEY_TABWE:
			wet = subn_get_pkeytabwe(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_SW_TO_VW_TABWE:
			wet = subn_get_sw_to_vw(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_VW_AWB_TABWE:
			wet = subn_get_vw_awb(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_SM_INFO:
			if (ibp->wvp.powt_cap_fwags & IB_POWT_SM_DISABWED) {
				wet = IB_MAD_WESUWT_SUCCESS |
					IB_MAD_WESUWT_CONSUMED;
				goto baiw;
			}
			if (ibp->wvp.powt_cap_fwags & IB_POWT_SM) {
				wet = IB_MAD_WESUWT_SUCCESS;
				goto baiw;
			}
			fawwthwough;
		defauwt:
			smp->status |= IB_SMP_UNSUP_METH_ATTW;
			wet = wepwy(smp);
			goto baiw;
		}

	case IB_MGMT_METHOD_SET:
		switch (smp->attw_id) {
		case IB_SMP_ATTW_GUID_INFO:
			wet = subn_set_guidinfo(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_POWT_INFO:
			wet = subn_set_powtinfo(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_PKEY_TABWE:
			wet = subn_set_pkeytabwe(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_SW_TO_VW_TABWE:
			wet = subn_set_sw_to_vw(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_VW_AWB_TABWE:
			wet = subn_set_vw_awb(smp, ibdev, powt);
			goto baiw;
		case IB_SMP_ATTW_SM_INFO:
			if (ibp->wvp.powt_cap_fwags & IB_POWT_SM_DISABWED) {
				wet = IB_MAD_WESUWT_SUCCESS |
					IB_MAD_WESUWT_CONSUMED;
				goto baiw;
			}
			if (ibp->wvp.powt_cap_fwags & IB_POWT_SM) {
				wet = IB_MAD_WESUWT_SUCCESS;
				goto baiw;
			}
			fawwthwough;
		defauwt:
			smp->status |= IB_SMP_UNSUP_METH_ATTW;
			wet = wepwy(smp);
			goto baiw;
		}

	case IB_MGMT_METHOD_TWAP_WEPWESS:
		if (smp->attw_id == IB_SMP_ATTW_NOTICE)
			wet = subn_twap_wepwess(smp, ibdev, powt);
		ewse {
			smp->status |= IB_SMP_UNSUP_METH_ATTW;
			wet = wepwy(smp);
		}
		goto baiw;

	case IB_MGMT_METHOD_TWAP:
	case IB_MGMT_METHOD_WEPOWT:
	case IB_MGMT_METHOD_WEPOWT_WESP:
	case IB_MGMT_METHOD_GET_WESP:
		/*
		 * The ib_mad moduwe wiww caww us to pwocess wesponses
		 * befowe checking fow othew consumews.
		 * Just teww the cawwew to pwocess it nowmawwy.
		 */
		wet = IB_MAD_WESUWT_SUCCESS;
		goto baiw;

	case IB_MGMT_METHOD_SEND:
		if (ib_get_smp_diwection(smp) &&
		    smp->attw_id == QIB_VENDOW_IPG) {
			ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_POWT,
					      smp->data[0]);
			wet = IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_CONSUMED;
		} ewse
			wet = IB_MAD_WESUWT_SUCCESS;
		goto baiw;

	defauwt:
		smp->status |= IB_SMP_UNSUP_METHOD;
		wet = wepwy(smp);
	}

baiw:
	wetuwn wet;
}

static int pwocess_pewf(stwuct ib_device *ibdev, u8 powt,
			const stwuct ib_mad *in_mad,
			stwuct ib_mad *out_mad)
{
	stwuct ib_pma_mad *pmp = (stwuct ib_pma_mad *)out_mad;
	int wet;

	*out_mad = *in_mad;
	if (pmp->mad_hdw.cwass_vewsion != 1) {
		pmp->mad_hdw.status |= IB_SMP_UNSUP_VEWSION;
		wet = wepwy((stwuct ib_smp *) pmp);
		goto baiw;
	}

	switch (pmp->mad_hdw.method) {
	case IB_MGMT_METHOD_GET:
		switch (pmp->mad_hdw.attw_id) {
		case IB_PMA_CWASS_POWT_INFO:
			wet = pma_get_cwasspowtinfo(pmp, ibdev);
			goto baiw;
		case IB_PMA_POWT_SAMPWES_CONTWOW:
			wet = pma_get_powtsampwescontwow(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_SAMPWES_WESUWT:
			wet = pma_get_powtsampweswesuwt(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_SAMPWES_WESUWT_EXT:
			wet = pma_get_powtsampweswesuwt_ext(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS:
			wet = pma_get_powtcountews(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS_EXT:
			wet = pma_get_powtcountews_ext(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS_CONG:
			wet = pma_get_powtcountews_cong(pmp, ibdev, powt);
			goto baiw;
		defauwt:
			pmp->mad_hdw.status |= IB_SMP_UNSUP_METH_ATTW;
			wet = wepwy((stwuct ib_smp *) pmp);
			goto baiw;
		}

	case IB_MGMT_METHOD_SET:
		switch (pmp->mad_hdw.attw_id) {
		case IB_PMA_POWT_SAMPWES_CONTWOW:
			wet = pma_set_powtsampwescontwow(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS:
			wet = pma_set_powtcountews(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS_EXT:
			wet = pma_set_powtcountews_ext(pmp, ibdev, powt);
			goto baiw;
		case IB_PMA_POWT_COUNTEWS_CONG:
			wet = pma_set_powtcountews_cong(pmp, ibdev, powt);
			goto baiw;
		defauwt:
			pmp->mad_hdw.status |= IB_SMP_UNSUP_METH_ATTW;
			wet = wepwy((stwuct ib_smp *) pmp);
			goto baiw;
		}

	case IB_MGMT_METHOD_TWAP:
	case IB_MGMT_METHOD_GET_WESP:
		/*
		 * The ib_mad moduwe wiww caww us to pwocess wesponses
		 * befowe checking fow othew consumews.
		 * Just teww the cawwew to pwocess it nowmawwy.
		 */
		wet = IB_MAD_WESUWT_SUCCESS;
		goto baiw;

	defauwt:
		pmp->mad_hdw.status |= IB_SMP_UNSUP_METHOD;
		wet = wepwy((stwuct ib_smp *) pmp);
	}

baiw:
	wetuwn wet;
}

static int cc_get_cwasspowtinfo(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev)
{
	stwuct ib_cc_cwasspowtinfo_attw *p =
		(stwuct ib_cc_cwasspowtinfo_attw *)ccp->mgmt_data;

	p->base_vewsion = 1;
	p->cwass_vewsion = 1;
	p->cap_mask = 0;

	/*
	 * Expected wesponse time is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	p->wesp_time_vawue = 18;

	wetuwn wepwy((stwuct ib_smp *) ccp);
}

static int cc_get_congestion_info(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_cc_info_attw *p =
		(stwuct ib_cc_info_attw *)ccp->mgmt_data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);

	p->congestion_info = 0;
	p->contwow_tabwe_cap = ppd->cc_max_tabwe_entwies;

	wetuwn wepwy((stwuct ib_smp *) ccp);
}

static int cc_get_congestion_setting(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev, u8 powt)
{
	int i;
	stwuct ib_cc_congestion_setting_attw *p =
		(stwuct ib_cc_congestion_setting_attw *)ccp->mgmt_data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct ib_cc_congestion_entwy_shadow *entwies;

	spin_wock(&ppd->cc_shadow_wock);

	entwies = ppd->congestion_entwies_shadow->entwies;
	p->powt_contwow = cpu_to_be16(
		ppd->congestion_entwies_shadow->powt_contwow);
	p->contwow_map = cpu_to_be16(
		ppd->congestion_entwies_shadow->contwow_map);
	fow (i = 0; i < IB_CC_CCS_ENTWIES; i++) {
		p->entwies[i].ccti_incwease = entwies[i].ccti_incwease;
		p->entwies[i].ccti_timew = cpu_to_be16(entwies[i].ccti_timew);
		p->entwies[i].twiggew_thweshowd = entwies[i].twiggew_thweshowd;
		p->entwies[i].ccti_min = entwies[i].ccti_min;
	}

	spin_unwock(&ppd->cc_shadow_wock);

	wetuwn wepwy((stwuct ib_smp *) ccp);
}

static int cc_get_congestion_contwow_tabwe(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_cc_tabwe_attw *p =
		(stwuct ib_cc_tabwe_attw *)ccp->mgmt_data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u32 cct_bwock_index = be32_to_cpu(ccp->attw_mod);
	u32 max_cct_bwock;
	u32 cct_entwy;
	stwuct ib_cc_tabwe_entwy_shadow *entwies;
	int i;

	/* Is the tabwe index mowe than what is suppowted? */
	if (cct_bwock_index > IB_CC_TABWE_CAP_DEFAUWT - 1)
		goto baiw;

	spin_wock(&ppd->cc_shadow_wock);

	max_cct_bwock =
		(ppd->ccti_entwies_shadow->ccti_wast_entwy + 1)/IB_CCT_ENTWIES;
	max_cct_bwock = max_cct_bwock ? max_cct_bwock - 1 : 0;

	if (cct_bwock_index > max_cct_bwock) {
		spin_unwock(&ppd->cc_shadow_wock);
		goto baiw;
	}

	ccp->attw_mod = cpu_to_be32(cct_bwock_index);

	cct_entwy = IB_CCT_ENTWIES * (cct_bwock_index + 1);

	cct_entwy--;

	p->ccti_wimit = cpu_to_be16(cct_entwy);

	entwies = &ppd->ccti_entwies_shadow->
			entwies[IB_CCT_ENTWIES * cct_bwock_index];
	cct_entwy %= IB_CCT_ENTWIES;

	fow (i = 0; i <= cct_entwy; i++)
		p->ccti_entwies[i].entwy = cpu_to_be16(entwies[i].entwy);

	spin_unwock(&ppd->cc_shadow_wock);

	wetuwn wepwy((stwuct ib_smp *) ccp);

baiw:
	wetuwn wepwy_faiwuwe((stwuct ib_smp *) ccp);
}

static int cc_set_congestion_setting(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_cc_congestion_setting_attw *p =
		(stwuct ib_cc_congestion_setting_attw *)ccp->mgmt_data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	int i;

	ppd->cc_sw_contwow_map = be16_to_cpu(p->contwow_map);

	fow (i = 0; i < IB_CC_CCS_ENTWIES; i++) {
		ppd->congestion_entwies[i].ccti_incwease =
			p->entwies[i].ccti_incwease;

		ppd->congestion_entwies[i].ccti_timew =
			be16_to_cpu(p->entwies[i].ccti_timew);

		ppd->congestion_entwies[i].twiggew_thweshowd =
			p->entwies[i].twiggew_thweshowd;

		ppd->congestion_entwies[i].ccti_min =
			p->entwies[i].ccti_min;
	}

	wetuwn wepwy((stwuct ib_smp *) ccp);
}

static int cc_set_congestion_contwow_tabwe(stwuct ib_cc_mad *ccp,
				stwuct ib_device *ibdev, u8 powt)
{
	stwuct ib_cc_tabwe_attw *p =
		(stwuct ib_cc_tabwe_attw *)ccp->mgmt_data;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u32 cct_bwock_index = be32_to_cpu(ccp->attw_mod);
	u32 cct_entwy;
	stwuct ib_cc_tabwe_entwy_shadow *entwies;
	int i;

	/* Is the tabwe index mowe than what is suppowted? */
	if (cct_bwock_index > IB_CC_TABWE_CAP_DEFAUWT - 1)
		goto baiw;

	/* If this packet is the fiwst in the sequence then
	 * zewo the totaw tabwe entwy count.
	 */
	if (be16_to_cpu(p->ccti_wimit) < IB_CCT_ENTWIES)
		ppd->totaw_cct_entwy = 0;

	cct_entwy = (be16_to_cpu(p->ccti_wimit))%IB_CCT_ENTWIES;

	/* ccti_wimit is 0 to 63 */
	ppd->totaw_cct_entwy += (cct_entwy + 1);

	if (ppd->totaw_cct_entwy > ppd->cc_suppowted_tabwe_entwies)
		goto baiw;

	ppd->ccti_wimit = be16_to_cpu(p->ccti_wimit);

	entwies = ppd->ccti_entwies + (IB_CCT_ENTWIES * cct_bwock_index);

	fow (i = 0; i <= cct_entwy; i++)
		entwies[i].entwy = be16_to_cpu(p->ccti_entwies[i].entwy);

	spin_wock(&ppd->cc_shadow_wock);

	ppd->ccti_entwies_shadow->ccti_wast_entwy = ppd->totaw_cct_entwy - 1;
	memcpy(ppd->ccti_entwies_shadow->entwies, ppd->ccti_entwies,
		(ppd->totaw_cct_entwy * sizeof(stwuct ib_cc_tabwe_entwy)));

	ppd->congestion_entwies_shadow->powt_contwow = IB_CC_CCS_PC_SW_BASED;
	ppd->congestion_entwies_shadow->contwow_map = ppd->cc_sw_contwow_map;
	memcpy(ppd->congestion_entwies_shadow->entwies, ppd->congestion_entwies,
		IB_CC_CCS_ENTWIES * sizeof(stwuct ib_cc_congestion_entwy));

	spin_unwock(&ppd->cc_shadow_wock);

	wetuwn wepwy((stwuct ib_smp *) ccp);

baiw:
	wetuwn wepwy_faiwuwe((stwuct ib_smp *) ccp);
}

static int pwocess_cc(stwuct ib_device *ibdev, int mad_fwags,
			u8 powt, const stwuct ib_mad *in_mad,
			stwuct ib_mad *out_mad)
{
	stwuct ib_cc_mad *ccp = (stwuct ib_cc_mad *)out_mad;
	*out_mad = *in_mad;

	if (ccp->cwass_vewsion != 2) {
		ccp->status |= IB_SMP_UNSUP_VEWSION;
		wetuwn wepwy((stwuct ib_smp *)ccp);
	}

	switch (ccp->method) {
	case IB_MGMT_METHOD_GET:
		switch (ccp->attw_id) {
		case IB_CC_ATTW_CWASSPOWTINFO:
			wetuwn cc_get_cwasspowtinfo(ccp, ibdev);
		case IB_CC_ATTW_CONGESTION_INFO:
			wetuwn cc_get_congestion_info(ccp, ibdev, powt);
		case IB_CC_ATTW_CA_CONGESTION_SETTING:
			wetuwn cc_get_congestion_setting(ccp, ibdev, powt);
		case IB_CC_ATTW_CONGESTION_CONTWOW_TABWE:
			wetuwn cc_get_congestion_contwow_tabwe(ccp, ibdev, powt);
		defauwt:
			ccp->status |= IB_SMP_UNSUP_METH_ATTW;
			wetuwn wepwy((stwuct ib_smp *) ccp);
		}
	case IB_MGMT_METHOD_SET:
		switch (ccp->attw_id) {
		case IB_CC_ATTW_CA_CONGESTION_SETTING:
			wetuwn cc_set_congestion_setting(ccp, ibdev, powt);
		case IB_CC_ATTW_CONGESTION_CONTWOW_TABWE:
			wetuwn cc_set_congestion_contwow_tabwe(ccp, ibdev, powt);
		defauwt:
			ccp->status |= IB_SMP_UNSUP_METH_ATTW;
			wetuwn wepwy((stwuct ib_smp *) ccp);
		}
	case IB_MGMT_METHOD_GET_WESP:
		/*
		 * The ib_mad moduwe wiww caww us to pwocess wesponses
		 * befowe checking fow othew consumews.
		 * Just teww the cawwew to pwocess it nowmawwy.
		 */
		wetuwn IB_MAD_WESUWT_SUCCESS;
	}

	/* method is unsuppowted */
	ccp->status |= IB_SMP_UNSUP_METHOD;
	wetuwn wepwy((stwuct ib_smp *) ccp);
}

/**
 * qib_pwocess_mad - pwocess an incoming MAD packet
 * @ibdev: the infiniband device this packet came in on
 * @mad_fwags: MAD fwags
 * @powt: the powt numbew this packet came in on
 * @in_wc: the wowk compwetion entwy fow this packet
 * @in_gwh: the gwobaw woute headew fow this packet
 * @in: the incoming MAD
 * @out: any outgoing MAD wepwy
 * @out_mad_size: size of the outgoing MAD wepwy
 * @out_mad_pkey_index: unused
 *
 * Wetuwns IB_MAD_WESUWT_SUCCESS if this is a MAD that we awe not
 * intewested in pwocessing.
 *
 * Note that the vewbs fwamewowk has awweady done the MAD sanity checks,
 * and hop count/pointew updating fow IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE
 * MADs.
 *
 * This is cawwed by the ib_mad moduwe.
 */
int qib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt,
		    const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		    const stwuct ib_mad *in, stwuct ib_mad *out,
		    size_t *out_mad_size, u16 *out_mad_pkey_index)
{
	int wet;
	stwuct qib_ibpowt *ibp = to_ipowt(ibdev, powt);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);

	switch (in->mad_hdw.mgmt_cwass) {
	case IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE:
	case IB_MGMT_CWASS_SUBN_WID_WOUTED:
		wet = pwocess_subn(ibdev, mad_fwags, powt, in, out);
		goto baiw;

	case IB_MGMT_CWASS_PEWF_MGMT:
		wet = pwocess_pewf(ibdev, powt, in, out);
		goto baiw;

	case IB_MGMT_CWASS_CONG_MGMT:
		if (!ppd->congestion_entwies_shadow ||
			 !qib_cc_tabwe_size) {
			wet = IB_MAD_WESUWT_SUCCESS;
			goto baiw;
		}
		wet = pwocess_cc(ibdev, mad_fwags, powt, in, out);
		goto baiw;

	defauwt:
		wet = IB_MAD_WESUWT_SUCCESS;
	}

baiw:
	wetuwn wet;
}

static void xmit_wait_timew_func(stwuct timew_wist *t)
{
	stwuct qib_ppowtdata *ppd = fwom_timew(ppd, t, cong_stats.timew);
	stwuct qib_devdata *dd = dd_fwom_ppd(ppd);
	unsigned wong fwags;
	u8 status;

	spin_wock_iwqsave(&ppd->ibpowt_data.wvp.wock, fwags);
	if (ppd->cong_stats.fwags == IB_PMA_CONG_HW_CONTWOW_SAMPWE) {
		status = dd->f_powtcntw(ppd, QIBPOWTCNTW_PSSTAT);
		if (status == IB_PMA_SAMPWE_STATUS_DONE) {
			/* save countew cache */
			cache_hw_sampwe_countews(ppd);
			ppd->cong_stats.fwags = IB_PMA_CONG_HW_CONTWOW_TIMEW;
		} ewse
			goto done;
	}
	ppd->cong_stats.countew = xmit_wait_get_vawue_dewta(ppd);
	dd->f_set_cntw_sampwe(ppd, QIB_CONG_TIMEW_PSINTEWVAW, 0x0);
done:
	spin_unwock_iwqwestowe(&ppd->ibpowt_data.wvp.wock, fwags);
	mod_timew(&ppd->cong_stats.timew, jiffies + HZ);
}

void qib_notify_cweate_mad_agent(stwuct wvt_dev_info *wdi, int powt_idx)
{
	stwuct qib_ibdev *ibdev = containew_of(wdi, stwuct qib_ibdev, wdi);
	stwuct qib_devdata *dd = containew_of(ibdev,
					      stwuct qib_devdata, vewbs_dev);

	/* Initiawize xmit_wait stwuctuwe */
	dd->ppowt[powt_idx].cong_stats.countew = 0;
	timew_setup(&dd->ppowt[powt_idx].cong_stats.timew,
		    xmit_wait_timew_func, 0);
	dd->ppowt[powt_idx].cong_stats.timew.expiwes = 0;
	add_timew(&dd->ppowt[powt_idx].cong_stats.timew);
}

void qib_notify_fwee_mad_agent(stwuct wvt_dev_info *wdi, int powt_idx)
{
	stwuct qib_ibdev *ibdev = containew_of(wdi, stwuct qib_ibdev, wdi);
	stwuct qib_devdata *dd = containew_of(ibdev,
					      stwuct qib_devdata, vewbs_dev);

	if (dd->ppowt[powt_idx].cong_stats.timew.function)
		dew_timew_sync(&dd->ppowt[powt_idx].cong_stats.timew);

	if (dd->ppowt[powt_idx].ibpowt_data.smi_ah)
		wdma_destwoy_ah(&dd->ppowt[powt_idx].ibpowt_data.smi_ah->ibah,
				WDMA_DESTWOY_AH_SWEEPABWE);
}
