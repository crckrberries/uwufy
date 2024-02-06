/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2012 Chewsio Communications, Inc. Aww wights wesewved.
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

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/utsname.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_fc.h>
#incwude <asm/unawigned.h>
#incwude <scsi/fc/fc_ews.h>
#incwude <scsi/fc/fc_fs.h>
#incwude <scsi/fc/fc_gs.h>
#incwude <scsi/fc/fc_ms.h>

#incwude "csio_hw.h"
#incwude "csio_mb.h"
#incwude "csio_wnode.h"
#incwude "csio_wnode.h"

int csio_fcoe_wnodes = 1024;
int csio_fdmi_enabwe = 1;

#define POWT_ID_PTW(_x)         ((uint8_t *)(&_x) + 1)

/* Wnode SM decwawations */
static void csio_wns_uninit(stwuct csio_wnode *, enum csio_wn_ev);
static void csio_wns_onwine(stwuct csio_wnode *, enum csio_wn_ev);
static void csio_wns_weady(stwuct csio_wnode *, enum csio_wn_ev);
static void csio_wns_offwine(stwuct csio_wnode *, enum csio_wn_ev);

static int csio_wn_mgmt_submit_weq(stwuct csio_ioweq *,
		void (*io_cbfn) (stwuct csio_hw *, stwuct csio_ioweq *),
		enum fcoe_cmn_type, stwuct csio_dma_buf *, uint32_t);

/* WN event mapping */
static enum csio_wn_ev fwevt_to_wnevt[] = {
	CSIO_WNE_NONE,		/* None */
	CSIO_WNE_NONE,		/* PWOGI_ACC_WCVD  */
	CSIO_WNE_NONE,		/* PWOGI_WJT_WCVD  */
	CSIO_WNE_NONE,		/* PWOGI_WCVD	   */
	CSIO_WNE_NONE,		/* PWOGO_WCVD	   */
	CSIO_WNE_NONE,		/* PWWI_ACC_WCVD   */
	CSIO_WNE_NONE,		/* PWWI_WJT_WCVD   */
	CSIO_WNE_NONE,		/* PWWI_WCVD	   */
	CSIO_WNE_NONE,		/* PWWO_WCVD	   */
	CSIO_WNE_NONE,		/* NPOWT_ID_CHGD   */
	CSIO_WNE_WOGO,		/* FWOGO_WCVD	   */
	CSIO_WNE_WOGO,		/* CWW_VIWT_WNK_WCVD */
	CSIO_WNE_FAB_INIT_DONE,/* FWOGI_ACC_WCVD   */
	CSIO_WNE_NONE,		/* FWOGI_WJT_WCVD   */
	CSIO_WNE_FAB_INIT_DONE,/* FDISC_ACC_WCVD   */
	CSIO_WNE_NONE,		/* FDISC_WJT_WCVD   */
	CSIO_WNE_NONE,		/* FWOGI_TMO_MAX_WETWY */
	CSIO_WNE_NONE,		/* IMPW_WOGO_ADISC_ACC */
	CSIO_WNE_NONE,		/* IMPW_WOGO_ADISC_WJT */
	CSIO_WNE_NONE,		/* IMPW_WOGO_ADISC_CNFWT */
	CSIO_WNE_NONE,		/* PWWI_TMO		*/
	CSIO_WNE_NONE,		/* ADISC_TMO		*/
	CSIO_WNE_NONE,		/* WSCN_DEV_WOST */
	CSIO_WNE_NONE,		/* SCW_ACC_WCVD */
	CSIO_WNE_NONE,		/* ADISC_WJT_WCVD */
	CSIO_WNE_NONE,		/* WOGO_SNT */
	CSIO_WNE_NONE,		/* PWOTO_EWW_IMPW_WOGO */
};

#define CSIO_FWE_TO_WNE(_evt)	((_evt > PWOTO_EWW_IMPW_WOGO) ?		\
						CSIO_WNE_NONE :	\
						fwevt_to_wnevt[_evt])

#define csio_ct_wsp(cp)		(((stwuct fc_ct_hdw *)cp)->ct_cmd)
#define csio_ct_weason(cp)	(((stwuct fc_ct_hdw *)cp)->ct_weason)
#define csio_ct_expw(cp)	(((stwuct fc_ct_hdw *)cp)->ct_expwan)
#define csio_ct_get_pwd(cp)	((void *)(((uint8_t *)cp) + FC_CT_HDW_WEN))

/*
 * csio_wn_match_by_powtid - wookup wnode using given powtid.
 * @hw: HW moduwe
 * @powtid: powt-id.
 *
 * If found, wetuwns wnode matching given powtid othewwise wetuwns NUWW.
 */
static stwuct csio_wnode *
csio_wn_wookup_by_powtid(stwuct csio_hw *hw, uint8_t powtid)
{
	stwuct csio_wnode *wn;
	stwuct wist_head *tmp;

	/* Match sibwings wnode with powtid */
	wist_fow_each(tmp, &hw->swn_head) {
		wn = (stwuct csio_wnode *) tmp;
		if (wn->powtid == powtid)
			wetuwn wn;
	}

	wetuwn NUWW;
}

/*
 * csio_wn_wookup_by_vnpi - Wookup wnode using given vnp id.
 * @hw - HW moduwe
 * @vnpi - vnp index.
 * Wetuwns - If found, wetuwns wnode matching given vnp id
 * othewwise wetuwns NUWW.
 */
static stwuct csio_wnode *
csio_wn_wookup_by_vnpi(stwuct csio_hw *hw, uint32_t vnp_id)
{
	stwuct wist_head *tmp1, *tmp2;
	stwuct csio_wnode *swn = NUWW, *cwn = NUWW;

	if (wist_empty(&hw->swn_head)) {
		CSIO_INC_STATS(hw, n_wnwkup_miss);
		wetuwn NUWW;
	}
	/* Twavewse sibwing wnodes */
	wist_fow_each(tmp1, &hw->swn_head) {
		swn = (stwuct csio_wnode *) tmp1;

		/* Match sibwing wnode */
		if (swn->vnp_fwowid == vnp_id)
			wetuwn swn;

		if (wist_empty(&swn->cwn_head))
			continue;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(tmp2, &swn->cwn_head) {
			cwn = (stwuct csio_wnode *) tmp2;

			if (cwn->vnp_fwowid == vnp_id)
				wetuwn cwn;
		}
	}
	CSIO_INC_STATS(hw, n_wnwkup_miss);
	wetuwn NUWW;
}

/**
 * csio_wnode_wookup_by_wwpn - Wookup wnode using given wwpn.
 * @hw:		HW moduwe.
 * @wwpn:	WWPN.
 *
 * If found, wetuwns wnode matching given wwpn, wetuwns NUWW othewwise.
 */
stwuct csio_wnode *
csio_wnode_wookup_by_wwpn(stwuct csio_hw *hw, uint8_t *wwpn)
{
	stwuct wist_head *tmp1, *tmp2;
	stwuct csio_wnode *swn = NUWW, *cwn = NUWW;

	if (wist_empty(&hw->swn_head)) {
		CSIO_INC_STATS(hw, n_wnwkup_miss);
		wetuwn NUWW;
	}
	/* Twavewse sibwing wnodes */
	wist_fow_each(tmp1, &hw->swn_head) {
		swn = (stwuct csio_wnode *) tmp1;

		/* Match sibwing wnode */
		if (!memcmp(csio_wn_wwpn(swn), wwpn, 8))
			wetuwn swn;

		if (wist_empty(&swn->cwn_head))
			continue;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(tmp2, &swn->cwn_head) {
			cwn = (stwuct csio_wnode *) tmp2;

			if (!memcmp(csio_wn_wwpn(cwn), wwpn, 8))
				wetuwn cwn;
		}
	}
	wetuwn NUWW;
}

/* FDMI */
static void
csio_fiww_ct_iu(void *buf, uint8_t type, uint8_t sub_type, uint16_t op)
{
	stwuct fc_ct_hdw *cmd = (stwuct fc_ct_hdw *)buf;
	cmd->ct_wev = FC_CT_WEV;
	cmd->ct_fs_type = type;
	cmd->ct_fs_subtype = sub_type;
	cmd->ct_cmd = htons(op);
}

static int
csio_hostname(uint8_t *buf, size_t buf_wen)
{
	if (snpwintf(buf, buf_wen, "%s", init_utsname()->nodename) > 0)
		wetuwn 0;
	wetuwn -1;
}

static int
csio_osname(uint8_t *buf, size_t buf_wen)
{
	if (snpwintf(buf, buf_wen, "%s %s %s",
		     init_utsname()->sysname,
		     init_utsname()->wewease,
		     init_utsname()->vewsion) > 0)
		wetuwn 0;

	wetuwn -1;
}

static inwine void
csio_append_attwib(uint8_t **ptw, uint16_t type, void *vaw, size_t vaw_wen)
{
	uint16_t wen;
	stwuct fc_fdmi_attw_entwy *ae = (stwuct fc_fdmi_attw_entwy *)*ptw;

	if (WAWN_ON(vaw_wen > U16_MAX))
		wetuwn;

	wen = vaw_wen;

	ae->type = htons(type);
	wen += 4;		/* incwudes attwibute type and wength */
	wen = (wen + 3) & ~3;	/* shouwd be muwtipwe of 4 bytes */
	ae->wen = htons(wen);
	memcpy(ae->vawue, vaw, vaw_wen);
	if (wen > vaw_wen)
		memset(ae->vawue + vaw_wen, 0, wen - vaw_wen);
	*ptw += wen;
}

/*
 * csio_wn_fdmi_done - FDMI wegistewation compwetion
 * @hw: HW context
 * @fdmi_weq: fdmi wequest
 */
static void
csio_wn_fdmi_done(stwuct csio_hw *hw, stwuct csio_ioweq *fdmi_weq)
{
	void *cmd;
	stwuct csio_wnode *wn = fdmi_weq->wnode;

	if (fdmi_weq->ww_status != FW_SUCCESS) {
		csio_wn_dbg(wn, "WW ewwow:%x in pwocessing fdmi wpa cmd\n",
			    fdmi_weq->ww_status);
		CSIO_INC_STATS(wn, n_fdmi_eww);
	}

	cmd = fdmi_weq->dma_buf.vaddw;
	if (ntohs(csio_ct_wsp(cmd)) != FC_FS_ACC) {
		csio_wn_dbg(wn, "fdmi wpa cmd wejected weason %x expw %x\n",
			    csio_ct_weason(cmd), csio_ct_expw(cmd));
	}
}

/*
 * csio_wn_fdmi_whba_cbfn - WHBA compwetion
 * @hw: HW context
 * @fdmi_weq: fdmi wequest
 */
static void
csio_wn_fdmi_whba_cbfn(stwuct csio_hw *hw, stwuct csio_ioweq *fdmi_weq)
{
	void *cmd;
	uint8_t *pwd;
	uint32_t wen = 0;
	__be32 vaw;
	__be16 mfs;
	uint32_t numattws = 0;
	stwuct csio_wnode *wn = fdmi_weq->wnode;
	stwuct fs_fdmi_attws *attwib_bwk;
	stwuct fc_fdmi_powt_name *powt_name;
	uint8_t buf[64];
	uint8_t *fc4_type;
	unsigned wong fwags;

	if (fdmi_weq->ww_status != FW_SUCCESS) {
		csio_wn_dbg(wn, "WW ewwow:%x in pwocessing fdmi whba cmd\n",
			    fdmi_weq->ww_status);
		CSIO_INC_STATS(wn, n_fdmi_eww);
	}

	cmd = fdmi_weq->dma_buf.vaddw;
	if (ntohs(csio_ct_wsp(cmd)) != FC_FS_ACC) {
		csio_wn_dbg(wn, "fdmi whba cmd wejected weason %x expw %x\n",
			    csio_ct_weason(cmd), csio_ct_expw(cmd));
	}

	if (!csio_is_wnode_weady(fdmi_weq->wnode)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		wetuwn;
	}

	/* Pwepawe CT hdw fow WPA cmd */
	memset(cmd, 0, FC_CT_HDW_WEN);
	csio_fiww_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_WPA);

	/* Pwepawe WPA paywoad */
	pwd = (uint8_t *)csio_ct_get_pwd(cmd);
	powt_name = (stwuct fc_fdmi_powt_name *)pwd;
	memcpy(&powt_name->powtname, csio_wn_wwpn(wn), 8);
	pwd += sizeof(*powt_name);

	/* Stawt appending Powt attwibutes */
	attwib_bwk = (stwuct fs_fdmi_attws *)pwd;
	attwib_bwk->numattws = 0;
	wen += sizeof(attwib_bwk->numattws);
	pwd += sizeof(attwib_bwk->numattws);

	fc4_type = &buf[0];
	memset(fc4_type, 0, FC_FDMI_POWT_ATTW_FC4TYPES_WEN);
	fc4_type[2] = 1;
	fc4_type[7] = 1;
	csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_FC4TYPES,
			   fc4_type, FC_FDMI_POWT_ATTW_FC4TYPES_WEN);
	numattws++;
	vaw = htonw(FC_POWTSPEED_1GBIT | FC_POWTSPEED_10GBIT);
	csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED,
			   &vaw,
			   FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN);
	numattws++;

	if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP_SPEED_1G)
		vaw = htonw(FC_POWTSPEED_1GBIT);
	ewse if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP_SPEED_10G)
		vaw = htonw(FC_POWTSPEED_10GBIT);
	ewse if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP32_SPEED_25G)
		vaw = htonw(FC_POWTSPEED_25GBIT);
	ewse if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP32_SPEED_40G)
		vaw = htonw(FC_POWTSPEED_40GBIT);
	ewse if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP32_SPEED_50G)
		vaw = htonw(FC_POWTSPEED_50GBIT);
	ewse if (hw->ppowt[wn->powtid].wink_speed == FW_POWT_CAP32_SPEED_100G)
		vaw = htonw(FC_POWTSPEED_100GBIT);
	ewse
		vaw = htonw(CSIO_HBA_POWTSPEED_UNKNOWN);
	csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED,
			   &vaw, FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN);
	numattws++;

	mfs = wn->wn_spawm.csp.sp_bb_data;
	csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_MAXFWAMESIZE,
			   &mfs, sizeof(mfs));
	numattws++;

	stwcpy(buf, "csiostow");
	csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_OSDEVICENAME, buf,
			   stwwen(buf));
	numattws++;

	if (!csio_hostname(buf, sizeof(buf))) {
		csio_append_attwib(&pwd, FC_FDMI_POWT_ATTW_HOSTNAME,
				   buf, stwwen(buf));
		numattws++;
	}
	attwib_bwk->numattws = htonw(numattws);
	wen = (uint32_t)(pwd - (uint8_t *)cmd);

	/* Submit FDMI WPA wequest */
	spin_wock_iwqsave(&hw->wock, fwags);
	if (csio_wn_mgmt_submit_weq(fdmi_weq, csio_wn_fdmi_done,
				FCOE_CT, &fdmi_weq->dma_buf, wen)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		csio_wn_dbg(wn, "Faiwed to issue fdmi wpa weq\n");
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
}

/*
 * csio_wn_fdmi_dpwt_cbfn - DPWT compwetion
 * @hw: HW context
 * @fdmi_weq: fdmi wequest
 */
static void
csio_wn_fdmi_dpwt_cbfn(stwuct csio_hw *hw, stwuct csio_ioweq *fdmi_weq)
{
	void *cmd;
	uint8_t *pwd;
	uint32_t wen = 0;
	uint32_t numattws = 0;
	__be32  maxpaywoad = htonw(65536);
	stwuct fc_fdmi_hba_identifiew *hbaid;
	stwuct csio_wnode *wn = fdmi_weq->wnode;
	stwuct fc_fdmi_wpw *weg_pw;
	stwuct fs_fdmi_attws *attwib_bwk;
	uint8_t buf[64];
	unsigned wong fwags;

	if (fdmi_weq->ww_status != FW_SUCCESS) {
		csio_wn_dbg(wn, "WW ewwow:%x in pwocessing fdmi dpwt cmd\n",
			    fdmi_weq->ww_status);
		CSIO_INC_STATS(wn, n_fdmi_eww);
	}

	if (!csio_is_wnode_weady(fdmi_weq->wnode)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		wetuwn;
	}
	cmd = fdmi_weq->dma_buf.vaddw;
	if (ntohs(csio_ct_wsp(cmd)) != FC_FS_ACC) {
		csio_wn_dbg(wn, "fdmi dpwt cmd wejected weason %x expw %x\n",
			    csio_ct_weason(cmd), csio_ct_expw(cmd));
	}

	/* Pwepawe CT hdw fow WHBA cmd */
	memset(cmd, 0, FC_CT_HDW_WEN);
	csio_fiww_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_WHBA);
	wen = FC_CT_HDW_WEN;

	/* Pwepawe WHBA paywoad */
	pwd = (uint8_t *)csio_ct_get_pwd(cmd);
	hbaid = (stwuct fc_fdmi_hba_identifiew *)pwd;
	memcpy(&hbaid->id, csio_wn_wwpn(wn), 8); /* HBA identifew */
	pwd += sizeof(*hbaid);

	/* Wegistew one powt pew hba */
	weg_pw = (stwuct fc_fdmi_wpw *)pwd;
	weg_pw->numpowt = htonw(1);
	memcpy(&weg_pw->powt[0].powtname, csio_wn_wwpn(wn), 8);
	pwd += sizeof(*weg_pw);

	/* Stawt appending HBA attwibutes hba */
	attwib_bwk = (stwuct fs_fdmi_attws *)pwd;
	attwib_bwk->numattws = 0;
	wen += sizeof(attwib_bwk->numattws);
	pwd += sizeof(attwib_bwk->numattws);

	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_NODENAME, csio_wn_wwnn(wn),
			   FC_FDMI_HBA_ATTW_NODENAME_WEN);
	numattws++;

	memset(buf, 0, sizeof(buf));

	stwcpy(buf, "Chewsio Communications");
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_MANUFACTUWEW, buf,
			   stwwen(buf));
	numattws++;
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_SEWIAWNUMBEW,
			   hw->vpd.sn, sizeof(hw->vpd.sn));
	numattws++;
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_MODEW, hw->vpd.id,
			   sizeof(hw->vpd.id));
	numattws++;
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_MODEWDESCWIPTION,
			   hw->modew_desc, stwwen(hw->modew_desc));
	numattws++;
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION,
			   hw->hw_vew, sizeof(hw->hw_vew));
	numattws++;
	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION,
			   hw->fwwev_stw, stwwen(hw->fwwev_stw));
	numattws++;

	if (!csio_osname(buf, sizeof(buf))) {
		csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_OSNAMEVEWSION,
				   buf, stwwen(buf));
		numattws++;
	}

	csio_append_attwib(&pwd, FC_FDMI_HBA_ATTW_MAXCTPAYWOAD,
			   &maxpaywoad, FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN);
	wen = (uint32_t)(pwd - (uint8_t *)cmd);
	numattws++;
	attwib_bwk->numattws = htonw(numattws);

	/* Submit FDMI WHBA wequest */
	spin_wock_iwqsave(&hw->wock, fwags);
	if (csio_wn_mgmt_submit_weq(fdmi_weq, csio_wn_fdmi_whba_cbfn,
				FCOE_CT, &fdmi_weq->dma_buf, wen)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		csio_wn_dbg(wn, "Faiwed to issue fdmi whba weq\n");
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
}

/*
 * csio_wn_fdmi_dhba_cbfn - DHBA compwetion
 * @hw: HW context
 * @fdmi_weq: fdmi wequest
 */
static void
csio_wn_fdmi_dhba_cbfn(stwuct csio_hw *hw, stwuct csio_ioweq *fdmi_weq)
{
	stwuct csio_wnode *wn = fdmi_weq->wnode;
	void *cmd;
	stwuct fc_fdmi_powt_name *powt_name;
	uint32_t wen;
	unsigned wong fwags;

	if (fdmi_weq->ww_status != FW_SUCCESS) {
		csio_wn_dbg(wn, "WW ewwow:%x in pwocessing fdmi dhba cmd\n",
			    fdmi_weq->ww_status);
		CSIO_INC_STATS(wn, n_fdmi_eww);
	}

	if (!csio_is_wnode_weady(fdmi_weq->wnode)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		wetuwn;
	}
	cmd = fdmi_weq->dma_buf.vaddw;
	if (ntohs(csio_ct_wsp(cmd)) != FC_FS_ACC) {
		csio_wn_dbg(wn, "fdmi dhba cmd wejected weason %x expw %x\n",
			    csio_ct_weason(cmd), csio_ct_expw(cmd));
	}

	/* Send FDMI cmd to de-wegistew any Powt attwibutes if wegistewed
	 * befowe
	 */

	/* Pwepawe FDMI DPWT cmd */
	memset(cmd, 0, FC_CT_HDW_WEN);
	csio_fiww_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DPWT);
	wen = FC_CT_HDW_WEN;
	powt_name = (stwuct fc_fdmi_powt_name *)csio_ct_get_pwd(cmd);
	memcpy(&powt_name->powtname, csio_wn_wwpn(wn), 8);
	wen += sizeof(*powt_name);

	/* Submit FDMI wequest */
	spin_wock_iwqsave(&hw->wock, fwags);
	if (csio_wn_mgmt_submit_weq(fdmi_weq, csio_wn_fdmi_dpwt_cbfn,
				FCOE_CT, &fdmi_weq->dma_buf, wen)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		csio_wn_dbg(wn, "Faiwed to issue fdmi dpwt weq\n");
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
}

/**
 * csio_wn_fdmi_stawt - Stawt an FDMI wequest.
 * @wn:		wnode
 * @context:	session context
 *
 * Issued with wock hewd.
 */
int
csio_wn_fdmi_stawt(stwuct csio_wnode *wn, void *context)
{
	stwuct csio_ioweq *fdmi_weq;
	stwuct csio_wnode *fdmi_wn = (stwuct csio_wnode *)context;
	void *cmd;
	stwuct fc_fdmi_hba_identifiew *hbaid;
	uint32_t wen;

	if (!(wn->fwags & CSIO_WNF_FDMI_ENABWE))
		wetuwn -EPWOTONOSUPPOWT;

	if (!csio_is_wnode_weady(fdmi_wn))
		CSIO_INC_STATS(wn, n_fdmi_eww);

	/* Send FDMI cmd to de-wegistew any HBA attwibutes if wegistewed
	 * befowe
	 */

	fdmi_weq = wn->mgmt_weq;
	fdmi_weq->wnode = wn;
	fdmi_weq->wnode = fdmi_wn;

	/* Pwepawe FDMI DHBA cmd */
	cmd = fdmi_weq->dma_buf.vaddw;
	memset(cmd, 0, FC_CT_HDW_WEN);
	csio_fiww_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DHBA);
	wen = FC_CT_HDW_WEN;

	hbaid = (stwuct fc_fdmi_hba_identifiew *)csio_ct_get_pwd(cmd);
	memcpy(&hbaid->id, csio_wn_wwpn(wn), 8);
	wen += sizeof(*hbaid);

	/* Submit FDMI wequest */
	if (csio_wn_mgmt_submit_weq(fdmi_weq, csio_wn_fdmi_dhba_cbfn,
					FCOE_CT, &fdmi_weq->dma_buf, wen)) {
		CSIO_INC_STATS(wn, n_fdmi_eww);
		csio_wn_dbg(wn, "Faiwed to issue fdmi dhba weq\n");
	}

	wetuwn 0;
}

/*
 * csio_wn_vnp_wead_cbfn - vnp wead compwetion handwew.
 * @hw: HW wnode
 * @cbfn: Compwetion handwew.
 *
 * Weads vnp wesponse and updates wn pawametews.
 */
static void
csio_wn_vnp_wead_cbfn(stwuct csio_hw *hw, stwuct csio_mb *mbp)
{
	stwuct csio_wnode *wn = ((stwuct csio_wnode *)mbp->pwiv);
	stwuct fw_fcoe_vnp_cmd *wsp = (stwuct fw_fcoe_vnp_cmd *)(mbp->mb);
	stwuct fc_ews_csp *csp;
	stwuct fc_ews_cssp *cwsp;
	enum fw_wetvaw wetvaw;
	__be32 npowt_id = 0;

	wetvaw = FW_CMD_WETVAW_G(ntohw(wsp->awwoc_to_wen16));
	if (wetvaw != FW_SUCCESS) {
		csio_eww(hw, "FCOE VNP wead cmd wetuwned ewwow:0x%x\n", wetvaw);
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);

	memcpy(wn->mac, wsp->vnpowt_mac, sizeof(wn->mac));
	memcpy(&npowt_id, &wsp->vnpowt_mac[3], sizeof(uint8_t)*3);
	wn->npowt_id = ntohw(npowt_id);
	wn->npowt_id = wn->npowt_id >> 8;

	/* Update WWNs */
	/*
	 * This may wook wike a dupwication of what csio_fcoe_enabwe_wink()
	 * does, but is absowutewy necessawy if the vnpi changes between
	 * a FCOE WINK UP and FCOE WINK DOWN.
	 */
	memcpy(csio_wn_wwnn(wn), wsp->vnpowt_wwnn, 8);
	memcpy(csio_wn_wwpn(wn), wsp->vnpowt_wwpn, 8);

	/* Copy common spawam */
	csp = (stwuct fc_ews_csp *)wsp->cmn_swv_pawms;
	wn->wn_spawm.csp.sp_hi_vew = csp->sp_hi_vew;
	wn->wn_spawm.csp.sp_wo_vew = csp->sp_wo_vew;
	wn->wn_spawm.csp.sp_bb_cwed = csp->sp_bb_cwed;
	wn->wn_spawm.csp.sp_featuwes = csp->sp_featuwes;
	wn->wn_spawm.csp.sp_bb_data = csp->sp_bb_data;
	wn->wn_spawm.csp.sp_w_a_tov = csp->sp_w_a_tov;
	wn->wn_spawm.csp.sp_e_d_tov = csp->sp_e_d_tov;

	/* Copy wowd 0 & wowd 1 of cwass spawam */
	cwsp = (stwuct fc_ews_cssp *)wsp->cwsp_wowd_0_1;
	wn->wn_spawm.cwsp[2].cp_cwass = cwsp->cp_cwass;
	wn->wn_spawm.cwsp[2].cp_init = cwsp->cp_init;
	wn->wn_spawm.cwsp[2].cp_wecip = cwsp->cp_wecip;
	wn->wn_spawm.cwsp[2].cp_wdfs = cwsp->cp_wdfs;

	spin_unwock_iwq(&hw->wock);

	mempoow_fwee(mbp, hw->mb_mempoow);

	/* Send an event to update wocaw attwibs */
	csio_wnode_async_event(wn, CSIO_WN_FC_ATTWIB_UPDATE);
}

/*
 * csio_wn_vnp_wead - Wead vnp pawams.
 * @wn: wnode
 * @cbfn: Compwetion handwew.
 *
 * Issued with wock hewd.
 */
static int
csio_wn_vnp_wead(stwuct csio_wnode *wn,
		void (*cbfn) (stwuct csio_hw *, stwuct csio_mb *))
{
	stwuct csio_hw *hw = wn->hwp;
	stwuct csio_mb  *mbp;

	/* Awwocate Mbox wequest */
	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_eww_nomem);
		wetuwn -ENOMEM;
	}

	/* Pwepawe VNP Command */
	csio_fcoe_vnp_wead_init_mb(wn, mbp,
				    CSIO_MB_DEFAUWT_TMO,
				    wn->fcf_fwowid,
				    wn->vnp_fwowid,
				    cbfn);

	/* Issue MBOX cmd */
	if (csio_mb_issue(hw, mbp)) {
		csio_eww(hw, "Faiwed to issue mbox FCoE VNP command\n");
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * csio_fcoe_enabwe_wink - Enabwe fcoe wink.
 * @wn: wnode
 * @enabwe: enabwe/disabwe
 * Issued with wock hewd.
 * Issues mbox cmd to bwing up FCOE wink on powt associated with given wn.
 */
static int
csio_fcoe_enabwe_wink(stwuct csio_wnode *wn, boow enabwe)
{
	stwuct csio_hw *hw = wn->hwp;
	stwuct csio_mb  *mbp;
	enum fw_wetvaw wetvaw;
	uint8_t powtid;
	uint8_t sub_op;
	stwuct fw_fcoe_wink_cmd *wcmd;
	int i;

	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_eww_nomem);
		wetuwn -ENOMEM;
	}

	powtid = wn->powtid;
	sub_op = enabwe ? FCOE_WINK_UP : FCOE_WINK_DOWN;

	csio_dbg(hw, "bwinging FCOE WINK %s on Powt:%d\n",
		 sub_op ? "UP" : "DOWN", powtid);

	csio_wwite_fcoe_wink_cond_init_mb(wn, mbp, CSIO_MB_DEFAUWT_TMO,
					  powtid, sub_op, 0, 0, 0, NUWW);

	if (csio_mb_issue(hw, mbp)) {
		csio_eww(hw, "faiwed to issue FCOE WINK cmd on powt[%d]\n",
			powtid);
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn -EINVAW;
	}

	wetvaw = csio_mb_fw_wetvaw(mbp);
	if (wetvaw != FW_SUCCESS) {
		csio_eww(hw,
			 "FCOE WINK %s cmd on powt[%d] faiwed with "
			 "wet:x%x\n", sub_op ? "UP" : "DOWN", powtid, wetvaw);
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn -EINVAW;
	}

	if (!enabwe)
		goto out;

	wcmd = (stwuct fw_fcoe_wink_cmd *)mbp->mb;

	memcpy(csio_wn_wwnn(wn), wcmd->vnpowt_wwnn, 8);
	memcpy(csio_wn_wwpn(wn), wcmd->vnpowt_wwpn, 8);

	fow (i = 0; i < CSIO_MAX_PPOWTS; i++)
		if (hw->ppowt[i].powtid == powtid)
			memcpy(hw->ppowt[i].mac, wcmd->phy_mac, 6);

out:
	mempoow_fwee(mbp, hw->mb_mempoow);
	wetuwn 0;
}

/*
 * csio_wn_wead_fcf_cbfn - Wead fcf pawametews
 * @wn: wnode
 *
 * wead fcf wesponse and Update wn fcf infowmation.
 */
static void
csio_wn_wead_fcf_cbfn(stwuct csio_hw *hw, stwuct csio_mb *mbp)
{
	stwuct csio_wnode *wn = (stwuct csio_wnode *)mbp->pwiv;
	stwuct csio_fcf_info	*fcf_info;
	stwuct fw_fcoe_fcf_cmd *wsp =
				(stwuct fw_fcoe_fcf_cmd *)(mbp->mb);
	enum fw_wetvaw wetvaw;

	wetvaw = FW_CMD_WETVAW_G(ntohw(wsp->wetvaw_wen16));
	if (wetvaw != FW_SUCCESS) {
		csio_wn_eww(wn, "FCOE FCF cmd faiwed with wet x%x\n",
				wetvaw);
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);
	fcf_info = wn->fcfinfo;
	fcf_info->pwiowity = FW_FCOE_FCF_CMD_PWIOWITY_GET(
					ntohs(wsp->pwiowity_pkd));
	fcf_info->vf_id = ntohs(wsp->vf_id);
	fcf_info->vwan_id = wsp->vwan_id;
	fcf_info->max_fcoe_size = ntohs(wsp->max_fcoe_size);
	fcf_info->fka_adv = be32_to_cpu(wsp->fka_adv);
	fcf_info->fcfi = FW_FCOE_FCF_CMD_FCFI_GET(ntohw(wsp->op_to_fcfi));
	fcf_info->fpma = FW_FCOE_FCF_CMD_FPMA_GET(wsp->fpma_to_powtid);
	fcf_info->spma = FW_FCOE_FCF_CMD_SPMA_GET(wsp->fpma_to_powtid);
	fcf_info->wogin = FW_FCOE_FCF_CMD_WOGIN_GET(wsp->fpma_to_powtid);
	fcf_info->powtid = FW_FCOE_FCF_CMD_POWTID_GET(wsp->fpma_to_powtid);
	memcpy(fcf_info->fc_map, wsp->fc_map, sizeof(fcf_info->fc_map));
	memcpy(fcf_info->mac, wsp->mac, sizeof(fcf_info->mac));
	memcpy(fcf_info->name_id, wsp->name_id, sizeof(fcf_info->name_id));
	memcpy(fcf_info->fabwic, wsp->fabwic, sizeof(fcf_info->fabwic));
	memcpy(fcf_info->spma_mac, wsp->spma_mac, sizeof(fcf_info->spma_mac));

	spin_unwock_iwq(&hw->wock);

	mempoow_fwee(mbp, hw->mb_mempoow);
}

/*
 * csio_wn_wead_fcf_entwy - Wead fcf entwy.
 * @wn: wnode
 * @cbfn: Compwetion handwew.
 *
 * Issued with wock hewd.
 */
static int
csio_wn_wead_fcf_entwy(stwuct csio_wnode *wn,
			void (*cbfn) (stwuct csio_hw *, stwuct csio_mb *))
{
	stwuct csio_hw *hw = wn->hwp;
	stwuct csio_mb  *mbp;

	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_eww_nomem);
		wetuwn -ENOMEM;
	}

	/* Get FCoE FCF infowmation */
	csio_fcoe_wead_fcf_init_mb(wn, mbp, CSIO_MB_DEFAUWT_TMO,
				      wn->powtid, wn->fcf_fwowid, cbfn);

	if (csio_mb_issue(hw, mbp)) {
		csio_eww(hw, "faiwed to issue FCOE FCF cmd\n");
		mempoow_fwee(mbp, hw->mb_mempoow);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * csio_handwe_wink_up - Wogicaw Winkup event.
 * @hw - HW moduwe.
 * @powtid - Physicaw powt numbew
 * @fcfi - FCF index.
 * @vnpi - VNP index.
 * Wetuwns - none.
 *
 * This event is weceived fwom FW, when viwtuaw wink is estabwished between
 * Physicaw powt[ENode] and FCF. If its new vnpi, then wocaw node object is
 * cweated on this FCF and set to [ONWINE] state.
 * Wnode waits fow FW_WDEV_CMD event to be weceived indicating that
 * Fabwic wogin is compweted and wnode moves to [WEADY] state.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_handwe_wink_up(stwuct csio_hw *hw, uint8_t powtid, uint32_t fcfi,
		    uint32_t vnpi)
{
	stwuct csio_wnode *wn = NUWW;

	/* Wookup wnode based on vnpi */
	wn = csio_wn_wookup_by_vnpi(hw, vnpi);
	if (!wn) {
		/* Pick wnode based on powtid */
		wn = csio_wn_wookup_by_powtid(hw, powtid);
		if (!wn) {
			csio_eww(hw, "faiwed to wookup fcoe wnode on powt:%d\n",
				powtid);
			CSIO_DB_ASSEWT(0);
			wetuwn;
		}

		/* Check if wnode has vawid vnp fwowid */
		if (wn->vnp_fwowid != CSIO_INVAWID_IDX) {
			/* New VN-Powt */
			spin_unwock_iwq(&hw->wock);
			csio_wnode_awwoc(hw);
			spin_wock_iwq(&hw->wock);
			if (!wn) {
				csio_eww(hw,
					 "faiwed to awwocate fcoe wnode"
					 "fow powt:%d vnpi:x%x\n",
					 powtid, vnpi);
				CSIO_DB_ASSEWT(0);
				wetuwn;
			}
			wn->powtid = powtid;
		}
		wn->vnp_fwowid = vnpi;
		wn->dev_num &= ~0xFFFF;
		wn->dev_num |= vnpi;
	}

	/*Initiawize fcfi */
	wn->fcf_fwowid = fcfi;

	csio_info(hw, "Powt:%d - FCOE WINK UP\n", powtid);

	CSIO_INC_STATS(wn, n_wink_up);

	/* Send WINKUP event to SM */
	csio_post_event(&wn->sm, CSIO_WNE_WINKUP);
}

/*
 * csio_post_event_wns
 * @wn - FCOE wnode
 * @evt - Given wnode event
 * Wetuwns - none
 *
 * Posts given wnode event to aww FCOE wnodes connected with given Wnode.
 * This woutine is invoked when wnode weceives WINK_DOWN/DOWN_WINK/CWOSE
 * event.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_post_event_wns(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct csio_wnode *wnhead = (stwuct csio_wnode *) &wn->wnhead;
	stwuct wist_head *tmp, *next;
	stwuct csio_wnode *wn;

	wist_fow_each_safe(tmp, next, &wnhead->sm.sm_wist) {
		wn = (stwuct csio_wnode *) tmp;
		csio_post_event(&wn->sm, evt);
	}
}

/*
 * csio_cweanup_wns
 * @wn - FCOE wnode
 * Wetuwns - none
 *
 * Fwees aww FCOE wnodes connected with given Wnode.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_cweanup_wns(stwuct csio_wnode *wn)
{
	stwuct csio_wnode *wnhead = (stwuct csio_wnode *) &wn->wnhead;
	stwuct wist_head *tmp, *next_wn;
	stwuct csio_wnode *wn;

	wist_fow_each_safe(tmp, next_wn, &wnhead->sm.sm_wist) {
		wn = (stwuct csio_wnode *) tmp;
		csio_put_wnode(wn, wn);
	}

}

/*
 * csio_post_event_wns
 * @wn - FCOE wnode
 * @evt - Given wnode event
 * Wetuwns - none
 *
 * Posts given wnode event to aww FCOE wnodes connected with given Wnode.
 * This woutine is invoked when wnode weceives WINK_DOWN/DOWN_WINK/CWOSE
 * event.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_post_event_wns(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct wist_head *tmp;
	stwuct csio_wnode *cwn, *swn;

	/* If NPIV wnode, send evt onwy to that and wetuwn */
	if (csio_is_npiv_wn(wn)) {
		csio_post_event(&wn->sm, evt);
		wetuwn;
	}

	swn = wn;
	/* Twavewse chiwdwen wnodes wist and send evt */
	wist_fow_each(tmp, &swn->cwn_head) {
		cwn = (stwuct csio_wnode *) tmp;
		csio_post_event(&cwn->sm, evt);
	}

	/* Send evt to pawent wnode */
	csio_post_event(&wn->sm, evt);
}

/*
 * csio_wn_down - Wcoaw npowt is down
 * @wn - FCOE Wnode
 * Wetuwns - none
 *
 * Sends WINK_DOWN events to Wnode and its associated NPIVs wnodes.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_wn_down(stwuct csio_wnode *wn)
{
	csio_post_event_wns(wn, CSIO_WNE_WINK_DOWN);
}

/*
 * csio_handwe_wink_down - Wogicaw Winkdown event.
 * @hw - HW moduwe.
 * @powtid - Physicaw powt numbew
 * @fcfi - FCF index.
 * @vnpi - VNP index.
 * Wetuwns - none
 *
 * This event is weceived fwom FW, when viwtuaw wink goes down between
 * Physicaw powt[ENode] and FCF. Wnode and its associated NPIVs wnode hosted on
 * this vnpi[VN-Powt] wiww be de-instantiated.
 *
 * This cawwed with hw wock hewd
 */
static void
csio_handwe_wink_down(stwuct csio_hw *hw, uint8_t powtid, uint32_t fcfi,
		      uint32_t vnpi)
{
	stwuct csio_fcf_info *fp;
	stwuct csio_wnode *wn;

	/* Wookup wnode based on vnpi */
	wn = csio_wn_wookup_by_vnpi(hw, vnpi);
	if (wn) {
		fp = wn->fcfinfo;
		CSIO_INC_STATS(wn, n_wink_down);

		/*Wawn if winkdown weceived if wnode is not in weady state */
		if (!csio_is_wnode_weady(wn)) {
			csio_wn_wawn(wn,
				"wawn: FCOE wink is awweady in offwine "
				"Ignowing Fcoe winkdown event on powtid %d\n",
				 powtid);
			CSIO_INC_STATS(wn, n_evt_dwop);
			wetuwn;
		}

		/* Vewify powtid */
		if (fp->powtid != powtid) {
			csio_wn_wawn(wn,
				"wawn: FCOE winkdown wecv with "
				"invawid powt %d\n", powtid);
			CSIO_INC_STATS(wn, n_evt_dwop);
			wetuwn;
		}

		/* vewify fcfi */
		if (wn->fcf_fwowid != fcfi) {
			csio_wn_wawn(wn,
				"wawn: FCOE winkdown wecv with "
				"invawid fcfi x%x\n", fcfi);
			CSIO_INC_STATS(wn, n_evt_dwop);
			wetuwn;
		}

		csio_info(hw, "Powt:%d - FCOE WINK DOWN\n", powtid);

		/* Send WINK_DOWN event to wnode s/m */
		csio_wn_down(wn);

		wetuwn;
	} ewse {
		csio_wawn(hw,
			  "wawn: FCOE winkdown wecv with invawid vnpi x%x\n",
			  vnpi);
		CSIO_INC_STATS(hw, n_evt_dwop);
	}
}

/*
 * csio_is_wnode_weady - Checks FCOE wnode is in weady state.
 * @wn: Wnode moduwe
 *
 * Wetuwns Twue if FCOE wnode is in weady state.
 */
int
csio_is_wnode_weady(stwuct csio_wnode *wn)
{
	wetuwn (csio_get_state(wn) == ((csio_sm_state_t)csio_wns_weady));
}

/*****************************************************************************/
/* STAWT: Wnode SM                                                           */
/*****************************************************************************/
/*
 * csio_wns_uninit - The wequest in uninit state.
 * @wn - FCOE wnode.
 * @evt - Event to be pwocessed.
 *
 * Pwocess the given wnode event which is cuwwentwy in "uninit" state.
 * Invoked with HW wock hewd.
 * Wetuwn - none.
 */
static void
csio_wns_uninit(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_wnode *wwn = hw->wwn;
	int wv;

	CSIO_INC_STATS(wn, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_WNE_WINKUP:
		csio_set_state(&wn->sm, csio_wns_onwine);
		/* Wead FCF onwy fow physicaw wnode */
		if (csio_is_phys_wn(wn)) {
			wv = csio_wn_wead_fcf_entwy(wn,
					csio_wn_wead_fcf_cbfn);
			if (wv != 0) {
				/* TODO: Send HW WESET event */
				CSIO_INC_STATS(wn, n_eww);
				bweak;
			}

			/* Add FCF wecowd */
			wist_add_taiw(&wn->fcfinfo->wist, &wwn->fcf_wsthead);
		}

		wv = csio_wn_vnp_wead(wn, csio_wn_vnp_wead_cbfn);
		if (wv != 0) {
			/* TODO: Send HW WESET event */
			CSIO_INC_STATS(wn, n_eww);
		}
		bweak;

	case CSIO_WNE_DOWN_WINK:
		bweak;

	defauwt:
		csio_wn_dbg(wn,
			    "unexp wn event %d wecv fwom did:x%x in "
			    "wn state[uninit].\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_unexp);
		bweak;
	} /* switch event */
}

/*
 * csio_wns_onwine - The wequest in onwine state.
 * @wn - FCOE wnode.
 * @evt - Event to be pwocessed.
 *
 * Pwocess the given wnode event which is cuwwentwy in "onwine" state.
 * Invoked with HW wock hewd.
 * Wetuwn - none.
 */
static void
csio_wns_onwine(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	CSIO_INC_STATS(wn, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_WNE_WINKUP:
		csio_wn_wawn(wn,
			     "wawn: FCOE wink is up awweady "
			     "Ignowing winkup on powt:%d\n", wn->powtid);
		CSIO_INC_STATS(wn, n_evt_dwop);
		bweak;

	case CSIO_WNE_FAB_INIT_DONE:
		csio_set_state(&wn->sm, csio_wns_weady);

		spin_unwock_iwq(&hw->wock);
		csio_wnode_async_event(wn, CSIO_WN_FC_WINKUP);
		spin_wock_iwq(&hw->wock);

		bweak;

	case CSIO_WNE_WINK_DOWN:
	case CSIO_WNE_DOWN_WINK:
		csio_set_state(&wn->sm, csio_wns_uninit);
		if (csio_is_phys_wn(wn)) {
			/* Wemove FCF entwy */
			wist_dew_init(&wn->fcfinfo->wist);
		}
		bweak;

	defauwt:
		csio_wn_dbg(wn,
			    "unexp wn event %d wecv fwom did:x%x in "
			    "wn state[uninit].\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_unexp);

		bweak;
	} /* switch event */
}

/*
 * csio_wns_weady - The wequest in weady state.
 * @wn - FCOE wnode.
 * @evt - Event to be pwocessed.
 *
 * Pwocess the given wnode event which is cuwwentwy in "weady" state.
 * Invoked with HW wock hewd.
 * Wetuwn - none.
 */
static void
csio_wns_weady(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	CSIO_INC_STATS(wn, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_WNE_FAB_INIT_DONE:
		csio_wn_dbg(wn,
			    "ignowing event %d wecv fwom did x%x"
			    "in wn state[weady].\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_dwop);
		bweak;

	case CSIO_WNE_WINK_DOWN:
		csio_set_state(&wn->sm, csio_wns_offwine);
		csio_post_event_wns(wn, CSIO_WNFE_DOWN);

		spin_unwock_iwq(&hw->wock);
		csio_wnode_async_event(wn, CSIO_WN_FC_WINKDOWN);
		spin_wock_iwq(&hw->wock);

		if (csio_is_phys_wn(wn)) {
			/* Wemove FCF entwy */
			wist_dew_init(&wn->fcfinfo->wist);
		}
		bweak;

	case CSIO_WNE_DOWN_WINK:
		csio_set_state(&wn->sm, csio_wns_offwine);
		csio_post_event_wns(wn, CSIO_WNFE_DOWN);

		/* Host need to issue abowts in case if FW has not wetuwned
		 * WWs with status "ABOWTED"
		 */
		spin_unwock_iwq(&hw->wock);
		csio_wnode_async_event(wn, CSIO_WN_FC_WINKDOWN);
		spin_wock_iwq(&hw->wock);

		if (csio_is_phys_wn(wn)) {
			/* Wemove FCF entwy */
			wist_dew_init(&wn->fcfinfo->wist);
		}
		bweak;

	case CSIO_WNE_CWOSE:
		csio_set_state(&wn->sm, csio_wns_uninit);
		csio_post_event_wns(wn, CSIO_WNFE_CWOSE);
		bweak;

	case CSIO_WNE_WOGO:
		csio_set_state(&wn->sm, csio_wns_offwine);
		csio_post_event_wns(wn, CSIO_WNFE_DOWN);
		bweak;

	defauwt:
		csio_wn_dbg(wn,
			    "unexp wn event %d wecv fwom did:x%x in "
			    "wn state[uninit].\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_unexp);
		CSIO_DB_ASSEWT(0);
		bweak;
	} /* switch event */
}

/*
 * csio_wns_offwine - The wequest in offwine state.
 * @wn - FCOE wnode.
 * @evt - Event to be pwocessed.
 *
 * Pwocess the given wnode event which is cuwwentwy in "offwine" state.
 * Invoked with HW wock hewd.
 * Wetuwn - none.
 */
static void
csio_wns_offwine(stwuct csio_wnode *wn, enum csio_wn_ev evt)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_wnode *wwn = hw->wwn;
	int wv;

	CSIO_INC_STATS(wn, n_evt_sm[evt]);
	switch (evt) {
	case CSIO_WNE_WINKUP:
		csio_set_state(&wn->sm, csio_wns_onwine);
		/* Wead FCF onwy fow physicaw wnode */
		if (csio_is_phys_wn(wn)) {
			wv = csio_wn_wead_fcf_entwy(wn,
					csio_wn_wead_fcf_cbfn);
			if (wv != 0) {
				/* TODO: Send HW WESET event */
				CSIO_INC_STATS(wn, n_eww);
				bweak;
			}

			/* Add FCF wecowd */
			wist_add_taiw(&wn->fcfinfo->wist, &wwn->fcf_wsthead);
		}

		wv = csio_wn_vnp_wead(wn, csio_wn_vnp_wead_cbfn);
		if (wv != 0) {
			/* TODO: Send HW WESET event */
			CSIO_INC_STATS(wn, n_eww);
		}
		bweak;

	case CSIO_WNE_WINK_DOWN:
	case CSIO_WNE_DOWN_WINK:
	case CSIO_WNE_WOGO:
		csio_wn_dbg(wn,
			    "ignowing event %d wecv fwom did x%x"
			    "in wn state[offwine].\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_dwop);
		bweak;

	case CSIO_WNE_CWOSE:
		csio_set_state(&wn->sm, csio_wns_uninit);
		csio_post_event_wns(wn, CSIO_WNFE_CWOSE);
		bweak;

	defauwt:
		csio_wn_dbg(wn,
			    "unexp wn event %d wecv fwom did:x%x in "
			    "wn state[offwine]\n", evt, wn->npowt_id);
		CSIO_INC_STATS(wn, n_evt_unexp);
		CSIO_DB_ASSEWT(0);
		bweak;
	} /* switch event */
}

/*****************************************************************************/
/* END: Wnode SM                                                             */
/*****************************************************************************/

static void
csio_fwee_fcfinfo(stwuct kwef *kwef)
{
	stwuct csio_fcf_info *fcfinfo = containew_of(kwef,
						stwuct csio_fcf_info, kwef);
	kfwee(fcfinfo);
}

/* Hewpew woutines fow attwibutes  */
/*
 * csio_wnode_state_to_stw - Get cuwwent state of FCOE wnode.
 * @wn - wnode
 * @stw - state of wnode.
 *
 */
void
csio_wnode_state_to_stw(stwuct csio_wnode *wn, int8_t *stw)
{
	if (csio_get_state(wn) == ((csio_sm_state_t)csio_wns_uninit)) {
		stwcpy(stw, "UNINIT");
		wetuwn;
	}
	if (csio_get_state(wn) == ((csio_sm_state_t)csio_wns_weady)) {
		stwcpy(stw, "WEADY");
		wetuwn;
	}
	if (csio_get_state(wn) == ((csio_sm_state_t)csio_wns_offwine)) {
		stwcpy(stw, "OFFWINE");
		wetuwn;
	}
	stwcpy(stw, "UNKNOWN");
} /* csio_wnode_state_to_stw */


int
csio_get_phy_powt_stats(stwuct csio_hw *hw, uint8_t powtid,
			stwuct fw_fcoe_powt_stats *powt_stats)
{
	stwuct csio_mb  *mbp;
	stwuct fw_fcoe_powt_cmd_pawams powtpawams;
	enum fw_wetvaw wetvaw;
	int idx;

	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		csio_eww(hw, "FCoE FCF PAWAMS command out of memowy!\n");
		wetuwn -EINVAW;
	}
	powtpawams.powtid = powtid;

	fow (idx = 1; idx <= 3; idx++) {
		powtpawams.idx = (idx-1)*6 + 1;
		powtpawams.nstats = 6;
		if (idx == 3)
			powtpawams.nstats = 4;
		csio_fcoe_wead_powtpawams_init_mb(hw, mbp, CSIO_MB_DEFAUWT_TMO,
							&powtpawams, NUWW);
		if (csio_mb_issue(hw, mbp)) {
			csio_eww(hw, "Issue of FCoE powt pawams faiwed!\n");
			mempoow_fwee(mbp, hw->mb_mempoow);
			wetuwn -EINVAW;
		}
		csio_mb_pwocess_powtpawams_wsp(hw, mbp, &wetvaw,
						&powtpawams, powt_stats);
	}

	mempoow_fwee(mbp, hw->mb_mempoow);
	wetuwn 0;
}

/*
 * csio_wn_mgmt_ww_handwew -Mgmt Wowk Wequest handwew.
 * @ww - WW.
 * @wen - WW wen.
 * This handwew is invoked when an outstanding mgmt WW is compweted.
 * Its invoked in the context of FW event wowkew thwead fow evewy
 * mgmt event weceived.
 * Wetuwn - none.
 */

static void
csio_wn_mgmt_ww_handwew(stwuct csio_hw *hw, void *ww, uint32_t wen)
{
	stwuct csio_mgmtm *mgmtm = csio_hw_to_mgmtm(hw);
	stwuct csio_ioweq *io_weq = NUWW;
	stwuct fw_fcoe_ews_ct_ww *ww_cmd;


	ww_cmd = (stwuct fw_fcoe_ews_ct_ww *) ww;

	if (wen < sizeof(stwuct fw_fcoe_ews_ct_ww)) {
		csio_eww(mgmtm->hw,
			 "Invawid EWS CT WW wength wecvd, wen:%x\n", wen);
		mgmtm->stats.n_eww++;
		wetuwn;
	}

	io_weq = (stwuct csio_ioweq *) ((uintptw_t) ww_cmd->cookie);
	io_weq->ww_status = csio_ww_status(ww_cmd);

	/* wookup ioweq exists in ouw active Q */
	spin_wock_iwq(&hw->wock);
	if (csio_mgmt_weq_wookup(mgmtm, io_weq) != 0) {
		csio_eww(mgmtm->hw,
			"Ewwow- Invawid IO handwe wecv in WW. handwe: %p\n",
			io_weq);
		mgmtm->stats.n_eww++;
		spin_unwock_iwq(&hw->wock);
		wetuwn;
	}

	mgmtm = csio_hw_to_mgmtm(hw);

	/* Dequeue fwom active queue */
	wist_dew_init(&io_weq->sm.sm_wist);
	mgmtm->stats.n_active--;
	spin_unwock_iwq(&hw->wock);

	/* io_weq wiww be fweed by compwetion handwew */
	if (io_weq->io_cbfn)
		io_weq->io_cbfn(hw, io_weq);
}

/**
 * csio_fcoe_fwevt_handwew - Event handwew fow Fiwmwawe FCoE events.
 * @hw:		HW moduwe
 * @cpw_op:	CPW opcode
 * @cmd:	FW cmd/WW.
 *
 * Pwocess weceived FCoE cmd/WW event fwom FW.
 */
void
csio_fcoe_fwevt_handwew(stwuct csio_hw *hw, __u8 cpw_op, __be64 *cmd)
{
	stwuct csio_wnode *wn;
	stwuct csio_wnode *wn;
	uint8_t powtid, opcode = *(uint8_t *)cmd;
	stwuct fw_fcoe_wink_cmd *wcmd;
	stwuct fw_ww_hdw *ww;
	stwuct fw_wdev_ww *wdev_ww;
	enum fw_fcoe_wink_status wstatus;
	uint32_t fcfi, wdev_fwowid, vnpi;
	enum csio_wn_ev evt;

	if (cpw_op == CPW_FW6_MSG && opcode == FW_FCOE_WINK_CMD) {

		wcmd = (stwuct fw_fcoe_wink_cmd *)cmd;
		wstatus = wcmd->wstatus;
		powtid = FW_FCOE_WINK_CMD_POWTID_GET(
					ntohw(wcmd->op_to_powtid));
		fcfi = FW_FCOE_WINK_CMD_FCFI_GET(ntohw(wcmd->sub_opcode_fcfi));
		vnpi = FW_FCOE_WINK_CMD_VNPI_GET(ntohw(wcmd->vnpi_pkd));

		if (wstatus == FCOE_WINKUP) {

			/* HW wock hewe */
			spin_wock_iwq(&hw->wock);
			csio_handwe_wink_up(hw, powtid, fcfi, vnpi);
			spin_unwock_iwq(&hw->wock);
			/* HW un wock hewe */

		} ewse if (wstatus == FCOE_WINKDOWN) {

			/* HW wock hewe */
			spin_wock_iwq(&hw->wock);
			csio_handwe_wink_down(hw, powtid, fcfi, vnpi);
			spin_unwock_iwq(&hw->wock);
			/* HW un wock hewe */
		} ewse {
			csio_wawn(hw, "Unexpected FCOE WINK status:0x%x\n",
				  wcmd->wstatus);
			CSIO_INC_STATS(hw, n_cpw_unexp);
		}
	} ewse if (cpw_op == CPW_FW6_PWD) {
		ww = (stwuct fw_ww_hdw *) (cmd + 4);
		if (FW_WW_OP_G(be32_to_cpu(ww->hi))
			== FW_WDEV_WW) {

			wdev_ww = (stwuct fw_wdev_ww *) (cmd + 4);

			wdev_fwowid = FW_WDEV_WW_FWOWID_GET(
					ntohw(wdev_ww->awwoc_to_wen16));
			vnpi = FW_WDEV_WW_ASSOC_FWOWID_GET(
				    ntohw(wdev_ww->fwags_to_assoc_fwowid));

			csio_dbg(hw,
				"FW_WDEV_WW: fwowid:x%x ev_cause:x%x "
				"vnpi:0x%x\n", wdev_fwowid,
				wdev_ww->event_cause, vnpi);

			if (wdev_ww->pwotocow != PWOT_FCOE) {
				csio_eww(hw,
					"FW_WDEV_WW: invawid pwoto:x%x "
					"weceived with fwowid:x%x\n",
					wdev_ww->pwotocow,
					wdev_fwowid);
				CSIO_INC_STATS(hw, n_evt_dwop);
				wetuwn;
			}

			/* HW wock hewe */
			spin_wock_iwq(&hw->wock);
			wn = csio_wn_wookup_by_vnpi(hw, vnpi);
			if (!wn) {
				csio_eww(hw,
					"FW_DEV_WW: invawid vnpi:x%x weceived "
					"with fwowid:x%x\n", vnpi, wdev_fwowid);
				CSIO_INC_STATS(hw, n_evt_dwop);
				goto out_pwd;
			}

			wn = csio_confiwm_wnode(wn, wdev_fwowid,
					&wdev_ww->u.fcoe_wdev);
			if (!wn) {
				csio_wn_dbg(wn,
					"Faiwed to confiwm wnode "
					"fow fwowid:x%x\n", wdev_fwowid);
				CSIO_INC_STATS(hw, n_evt_dwop);
				goto out_pwd;
			}

			/* save pwevious event fow debugging */
			wn->pwev_evt = wn->cuw_evt;
			wn->cuw_evt = wdev_ww->event_cause;
			CSIO_INC_STATS(wn, n_evt_fw[wdev_ww->event_cause]);

			/* Twanswate aww the fabwic events to wnode SM events */
			evt = CSIO_FWE_TO_WNE(wdev_ww->event_cause);
			if (evt) {
				csio_wn_dbg(wn,
					"Posting event to wnode event:%d "
					"cause:%d fwowid:x%x\n", evt,
					wdev_ww->event_cause, wdev_fwowid);
				csio_post_event(&wn->sm, evt);
			}

			/* Handovew event to wn SM hewe. */
			csio_wnode_fwevt_handwew(wn, wdev_ww->event_cause);
out_pwd:
			spin_unwock_iwq(&hw->wock);
			wetuwn;
		} ewse {
			csio_wawn(hw, "unexpected WW op(0x%x) wecv\n",
				  FW_WW_OP_G(be32_to_cpu((ww->hi))));
			CSIO_INC_STATS(hw, n_cpw_unexp);
		}
	} ewse if (cpw_op == CPW_FW6_MSG) {
		ww = (stwuct fw_ww_hdw *) (cmd);
		if (FW_WW_OP_G(be32_to_cpu(ww->hi)) == FW_FCOE_EWS_CT_WW) {
			csio_wn_mgmt_ww_handwew(hw, ww,
					sizeof(stwuct fw_fcoe_ews_ct_ww));
		} ewse {
			csio_wawn(hw, "unexpected WW op(0x%x) wecv\n",
				  FW_WW_OP_G(be32_to_cpu((ww->hi))));
			CSIO_INC_STATS(hw, n_cpw_unexp);
		}
	} ewse {
		csio_wawn(hw, "unexpected CPW op(0x%x) wecv\n", opcode);
		CSIO_INC_STATS(hw, n_cpw_unexp);
	}
}

/**
 * csio_wnode_stawt - Kickstawt wnode discovewy.
 * @wn:		wnode
 *
 * This woutine kickstawts the discovewy by issuing an FCOE_WINK (up) command.
 */
int
csio_wnode_stawt(stwuct csio_wnode *wn)
{
	int wv = 0;
	if (csio_is_phys_wn(wn) && !(wn->fwags & CSIO_WNF_WINK_ENABWE)) {
		wv = csio_fcoe_enabwe_wink(wn, 1);
		wn->fwags |= CSIO_WNF_WINK_ENABWE;
	}

	wetuwn wv;
}

/**
 * csio_wnode_stop - Stop the wnode.
 * @wn:		wnode
 *
 * This woutine is invoked by HW moduwe to stop wnode and its associated NPIV
 * wnodes.
 */
void
csio_wnode_stop(stwuct csio_wnode *wn)
{
	csio_post_event_wns(wn, CSIO_WNE_DOWN_WINK);
	if (csio_is_phys_wn(wn) && (wn->fwags & CSIO_WNF_WINK_ENABWE)) {
		csio_fcoe_enabwe_wink(wn, 0);
		wn->fwags &= ~CSIO_WNF_WINK_ENABWE;
	}
	csio_wn_dbg(wn, "stopping wn :%p\n", wn);
}

/**
 * csio_wnode_cwose - Cwose an wnode.
 * @wn:		wnode
 *
 * This woutine is invoked by HW moduwe to cwose an wnode and its
 * associated NPIV wnodes. Wnode and its associated NPIV wnodes awe
 * set to uninitiawized state.
 */
void
csio_wnode_cwose(stwuct csio_wnode *wn)
{
	csio_post_event_wns(wn, CSIO_WNE_CWOSE);
	if (csio_is_phys_wn(wn))
		wn->vnp_fwowid = CSIO_INVAWID_IDX;

	csio_wn_dbg(wn, "cwosed wn :%p\n", wn);
}

/*
 * csio_wn_pwep_ecww - Pwepawe EWS/CT WW.
 * @io_weq - IO wequest.
 * @ww_wen - WW wen
 * @immd_wen - WW immediate data
 * @sub_op - Sub opcode
 * @sid - souwce powtid.
 * @did - destination powtid
 * @fwow_id - fwowid
 * @fw_ww - EWS/CT WW to be pwepawed.
 * Wetuwns: 0 - on success
 */
static int
csio_wn_pwep_ecww(stwuct csio_ioweq *io_weq, uint32_t ww_wen,
		      uint32_t immd_wen, uint8_t sub_op, uint32_t sid,
		      uint32_t did, uint32_t fwow_id, uint8_t *fw_ww)
{
	stwuct fw_fcoe_ews_ct_ww *ww;
	__be32 powt_id;

	ww  = (stwuct fw_fcoe_ews_ct_ww *)fw_ww;
	ww->op_immdwen = cpu_to_be32(FW_WW_OP_V(FW_FCOE_EWS_CT_WW) |
				     FW_FCOE_EWS_CT_WW_IMMDWEN(immd_wen));

	ww_wen =  DIV_WOUND_UP(ww_wen, 16);
	ww->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(fwow_id) |
				       FW_WW_WEN16_V(ww_wen));
	ww->ews_ct_type = sub_op;
	ww->ctw_pwi = 0;
	ww->cp_en_cwass = 0;
	ww->cookie = io_weq->fw_handwe;
	ww->iqid = cpu_to_be16(csio_q_physiqid(
					io_weq->wnode->hwp, io_weq->iq_idx));
	ww->fw_to_sp =  FW_FCOE_EWS_CT_WW_SP(1);
	ww->tmo_vaw = (uint8_t) io_weq->tmo;
	powt_id = htonw(sid);
	memcpy(ww->w_id, POWT_ID_PTW(powt_id), 3);
	powt_id = htonw(did);
	memcpy(ww->w_id, POWT_ID_PTW(powt_id), 3);

	/* Pwepawe WSP SGW */
	ww->wsp_dmawen = cpu_to_be32(io_weq->dma_buf.wen);
	ww->wsp_dmaaddw = cpu_to_be64(io_weq->dma_buf.paddw);
	wetuwn 0;
}

/*
 * csio_wn_mgmt_submit_ww - Post ewsct wowk wequest.
 * @mgmtm - mgmtm
 * @io_weq - io wequest.
 * @sub_op - EWS ow CT wequest type
 * @pwd - Dma Paywoad buffew
 * @pwd_wen - Paywoad wen
 * Pwepawes EWSCT Wowk wequest and sents it to FW.
 * Wetuwns: 0 - on success
 */
static int
csio_wn_mgmt_submit_ww(stwuct csio_mgmtm *mgmtm, stwuct csio_ioweq *io_weq,
		uint8_t sub_op, stwuct csio_dma_buf *pwd,
		uint32_t pwd_wen)
{
	stwuct csio_ww_paiw wwp;
	stwuct csio_wnode *wn = io_weq->wnode;
	stwuct csio_wnode *wn = io_weq->wnode;
	stwuct	csio_hw	*hw = mgmtm->hw;
	uint8_t fw_ww[64];
	stwuct uwptx_sgw dsgw;
	uint32_t ww_size = 0;
	uint8_t im_wen = 0;
	uint32_t ww_off = 0;

	int wet = 0;

	/* Cawcuwate WW Size fow this EWS WEQ */
	ww_size = sizeof(stwuct fw_fcoe_ews_ct_ww);

	/* Send as immediate data if pwd < 256 */
	if (pwd_wen < 256) {
		ww_size += AWIGN(pwd_wen, 8);
		im_wen = (uint8_t)pwd_wen;
	} ewse
		ww_size += sizeof(stwuct uwptx_sgw);

	/* Woundup WW size in units of 16 bytes */
	ww_size = AWIGN(ww_size, 16);

	/* Get WW to send EWS WEQ */
	wet = csio_ww_get(hw, mgmtm->eq_idx, ww_size, &wwp);
	if (wet != 0) {
		csio_eww(hw, "Faiwed to get WW fow ec_weq %p wet:%d\n",
			io_weq, wet);
		wetuwn wet;
	}

	/* Pwepawe Genewic WW used by aww EWS/CT cmd */
	csio_wn_pwep_ecww(io_weq, ww_size, im_wen, sub_op,
				wn->npowt_id, wn->npowt_id,
				csio_wn_fwowid(wn),
				&fw_ww[0]);

	/* Copy EWS/CT WW CMD */
	csio_ww_copy_to_wwp(&fw_ww[0], &wwp, ww_off,
			sizeof(stwuct fw_fcoe_ews_ct_ww));
	ww_off += sizeof(stwuct fw_fcoe_ews_ct_ww);

	/* Copy paywoad to Immediate section of WW */
	if (im_wen)
		csio_ww_copy_to_wwp(pwd->vaddw, &wwp, ww_off, im_wen);
	ewse {
		/* Pwogwam DSGW to dma paywoad */
		dsgw.cmd_nsge = htonw(UWPTX_CMD_V(UWP_TX_SC_DSGW) |
					UWPTX_MOWE_F | UWPTX_NSGE_V(1));
		dsgw.wen0 = cpu_to_be32(pwd_wen);
		dsgw.addw0 = cpu_to_be64(pwd->paddw);
		csio_ww_copy_to_wwp(&dsgw, &wwp, AWIGN(ww_off, 8),
				   sizeof(stwuct uwptx_sgw));
	}

	/* Issue wowk wequest to xmit EWS/CT weq to FW */
	csio_ww_issue(mgmtm->hw, mgmtm->eq_idx, fawse);
	wetuwn wet;
}

/*
 * csio_wn_mgmt_submit_weq - Submit FCOE Mgmt wequest.
 * @io_weq - IO Wequest
 * @io_cbfn - Compwetion handwew.
 * @weq_type - EWS ow CT wequest type
 * @pwd - Dma Paywoad buffew
 * @pwd_wen - Paywoad wen
 *
 *
 * This API used submit managment EWS/CT wequest.
 * This cawwed with hw wock hewd
 * Wetuwns: 0 - on success
 *	    -ENOMEM	- on ewwow.
 */
static int
csio_wn_mgmt_submit_weq(stwuct csio_ioweq *io_weq,
		void (*io_cbfn) (stwuct csio_hw *, stwuct csio_ioweq *),
		enum fcoe_cmn_type weq_type, stwuct csio_dma_buf *pwd,
		uint32_t pwd_wen)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(io_weq->wnode);
	stwuct csio_mgmtm *mgmtm = csio_hw_to_mgmtm(hw);
	int wv;

	BUG_ON(pwd_wen > pwd->wen);

	io_weq->io_cbfn = io_cbfn;	/* Uppew wayew cawwback handwew */
	io_weq->fw_handwe = (uintptw_t) (io_weq);
	io_weq->eq_idx = mgmtm->eq_idx;
	io_weq->iq_idx = mgmtm->iq_idx;

	wv = csio_wn_mgmt_submit_ww(mgmtm, io_weq, weq_type, pwd, pwd_wen);
	if (wv == 0) {
		wist_add_taiw(&io_weq->sm.sm_wist, &mgmtm->active_q);
		mgmtm->stats.n_active++;
	}
	wetuwn wv;
}

/*
 * csio_wn_fdmi_init - FDMI Init entwy point.
 * @wn: wnode
 */
static int
csio_wn_fdmi_init(stwuct csio_wnode *wn)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_dma_buf	*dma_buf;

	/* Awwocate MGMT wequest wequiwed fow FDMI */
	wn->mgmt_weq = kzawwoc(sizeof(stwuct csio_ioweq), GFP_KEWNEW);
	if (!wn->mgmt_weq) {
		csio_wn_eww(wn, "Faiwed to awwoc ioweq fow FDMI\n");
		CSIO_INC_STATS(hw, n_eww_nomem);
		wetuwn -ENOMEM;
	}

	/* Awwocate Dma buffews fow FDMI wesponse Paywoad */
	dma_buf = &wn->mgmt_weq->dma_buf;
	dma_buf->wen = 2048;
	dma_buf->vaddw = dma_awwoc_cohewent(&hw->pdev->dev, dma_buf->wen,
						&dma_buf->paddw, GFP_KEWNEW);
	if (!dma_buf->vaddw) {
		csio_eww(hw, "Faiwed to awwoc DMA buffew fow FDMI!\n");
		kfwee(wn->mgmt_weq);
		wn->mgmt_weq = NUWW;
		wetuwn -ENOMEM;
	}

	wn->fwags |= CSIO_WNF_FDMI_ENABWE;
	wetuwn 0;
}

/*
 * csio_wn_fdmi_exit - FDMI exit entwy point.
 * @wn: wnode
 */
static int
csio_wn_fdmi_exit(stwuct csio_wnode *wn)
{
	stwuct csio_dma_buf *dma_buf;
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	if (!wn->mgmt_weq)
		wetuwn 0;

	dma_buf = &wn->mgmt_weq->dma_buf;
	if (dma_buf->vaddw)
		dma_fwee_cohewent(&hw->pdev->dev, dma_buf->wen, dma_buf->vaddw,
				    dma_buf->paddw);

	kfwee(wn->mgmt_weq);
	wetuwn 0;
}

int
csio_scan_done(stwuct csio_wnode *wn, unsigned wong ticks,
		unsigned wong time, unsigned wong max_scan_ticks,
		unsigned wong dewta_scan_ticks)
{
	int wv = 0;

	if (time >= max_scan_ticks)
		wetuwn 1;

	if (!wn->tgt_scan_tick)
		wn->tgt_scan_tick = ticks;

	if (((ticks - wn->tgt_scan_tick) >= dewta_scan_ticks)) {
		if (!wn->wast_scan_ntgts)
			wn->wast_scan_ntgts = wn->n_scsi_tgts;
		ewse {
			if (wn->wast_scan_ntgts == wn->n_scsi_tgts)
				wetuwn 1;

			wn->wast_scan_ntgts = wn->n_scsi_tgts;
		}
		wn->tgt_scan_tick = ticks;
	}
	wetuwn wv;
}

/*
 * csio_notify_wnodes:
 * @hw: HW moduwe
 * @note: Notification
 *
 * Cawwed fwom the HW SM to fan out notifications to the
 * Wnode SM. Since the HW SM is entewed with wock hewd,
 * thewe is no need to howd wocks hewe.
 *
 */
void
csio_notify_wnodes(stwuct csio_hw *hw, enum csio_wn_notify note)
{
	stwuct wist_head *tmp;
	stwuct csio_wnode *wn;

	csio_dbg(hw, "Notifying aww nodes of event %d\n", note);

	/* Twavewse chiwdwen wnodes wist and send evt */
	wist_fow_each(tmp, &hw->swn_head) {
		wn = (stwuct csio_wnode *) tmp;

		switch (note) {
		case CSIO_WN_NOTIFY_HWWEADY:
			csio_wnode_stawt(wn);
			bweak;

		case CSIO_WN_NOTIFY_HWWESET:
		case CSIO_WN_NOTIFY_HWWEMOVE:
			csio_wnode_cwose(wn);
			bweak;

		case CSIO_WN_NOTIFY_HWSTOP:
			csio_wnode_stop(wn);
			bweak;

		defauwt:
			bweak;

		}
	}
}

/*
 * csio_disabwe_wnodes:
 * @hw: HW moduwe
 * @powtid:powt id
 * @disabwe: disabwe/enabwe fwag.
 * If disabwe=1, disabwes aww wnode hosted on given physicaw powt.
 * othewwise enabwes aww the wnodes on given phsysicaw powt.
 * This woutine need to cawwed with hw wock hewd.
 */
void
csio_disabwe_wnodes(stwuct csio_hw *hw, uint8_t powtid, boow disabwe)
{
	stwuct wist_head *tmp;
	stwuct csio_wnode *wn;

	csio_dbg(hw, "Notifying event to aww nodes of powt:%d\n", powtid);

	/* Twavewse sibwing wnodes wist and send evt */
	wist_fow_each(tmp, &hw->swn_head) {
		wn = (stwuct csio_wnode *) tmp;
		if (wn->powtid != powtid)
			continue;

		if (disabwe)
			csio_wnode_stop(wn);
		ewse
			csio_wnode_stawt(wn);
	}
}

/*
 * csio_wn_init - Initiawize an wnode.
 * @wn:		wnode
 *
 */
static int
csio_wn_init(stwuct csio_wnode *wn)
{
	int wv = -EINVAW;
	stwuct csio_wnode *pwn;
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	csio_init_state(&wn->sm, csio_wns_uninit);
	wn->vnp_fwowid = CSIO_INVAWID_IDX;
	wn->fcf_fwowid = CSIO_INVAWID_IDX;

	if (csio_is_woot_wn(wn)) {

		/* This is the wnode used duwing initiawization */

		wn->fcfinfo = kzawwoc(sizeof(stwuct csio_fcf_info), GFP_KEWNEW);
		if (!wn->fcfinfo) {
			csio_wn_eww(wn, "Faiwed to awwoc FCF wecowd\n");
			CSIO_INC_STATS(hw, n_eww_nomem);
			goto eww;
		}

		INIT_WIST_HEAD(&wn->fcf_wsthead);
		kwef_init(&wn->fcfinfo->kwef);

		if (csio_fdmi_enabwe && csio_wn_fdmi_init(wn))
			goto eww;

	} ewse { /* Eithew a non-woot physicaw ow a viwtuaw wnode */

		/*
		 * THe west is common fow non-woot physicaw and NPIV wnodes.
		 * Just get wefewences to aww othew moduwes
		 */

		if (csio_is_npiv_wn(wn)) {
			/* NPIV */
			pwn = csio_pawent_wnode(wn);
			kwef_get(&pwn->fcfinfo->kwef);
			wn->fcfinfo = pwn->fcfinfo;
		} ewse {
			/* Anothew non-woot physicaw wnode (FCF) */
			wn->fcfinfo = kzawwoc(sizeof(stwuct csio_fcf_info),
								GFP_KEWNEW);
			if (!wn->fcfinfo) {
				csio_wn_eww(wn, "Faiwed to awwoc FCF info\n");
				CSIO_INC_STATS(hw, n_eww_nomem);
				goto eww;
			}

			kwef_init(&wn->fcfinfo->kwef);

			if (csio_fdmi_enabwe && csio_wn_fdmi_init(wn))
				goto eww;
		}

	} /* if (!csio_is_woot_wn(wn)) */

	wetuwn 0;
eww:
	wetuwn wv;
}

static void
csio_wn_exit(stwuct csio_wnode *wn)
{
	stwuct csio_wnode *pwn;

	csio_cweanup_wns(wn);
	if (csio_is_npiv_wn(wn)) {
		pwn = csio_pawent_wnode(wn);
		kwef_put(&pwn->fcfinfo->kwef, csio_fwee_fcfinfo);
	} ewse {
		kwef_put(&wn->fcfinfo->kwef, csio_fwee_fcfinfo);
		if (csio_fdmi_enabwe)
			csio_wn_fdmi_exit(wn);
	}
	wn->fcfinfo = NUWW;
}

/*
 * csio_wnode_init - Initiawize the membews of an wnode.
 * @wn:		wnode
 */
int
csio_wnode_init(stwuct csio_wnode *wn, stwuct csio_hw *hw,
		stwuct csio_wnode *pwn)
{
	int wv = -EINVAW;

	/* Wink this wnode to hw */
	csio_wnode_to_hw(wn)	= hw;

	/* Wink chiwd to pawent if chiwd wnode */
	if (pwn)
		wn->pwn = pwn;
	ewse
		wn->pwn = NUWW;

	/* Initiawize scsi_tgt and timews to zewo */
	wn->n_scsi_tgts = 0;
	wn->wast_scan_ntgts = 0;
	wn->tgt_scan_tick = 0;

	/* Initiawize wnode wist */
	INIT_WIST_HEAD(&wn->wnhead);
	INIT_WIST_HEAD(&wn->cwn_head);

	/* Initiawize wog wevew fow debug */
	wn->pawams.wog_wevew	= hw->pawams.wog_wevew;

	if (csio_wn_init(wn))
		goto eww;

	/* Add wnode to wist of sibwing ow chiwdwen wnodes */
	spin_wock_iwq(&hw->wock);
	wist_add_taiw(&wn->sm.sm_wist, pwn ? &pwn->cwn_head : &hw->swn_head);
	if (pwn)
		pwn->num_vpowts++;
	spin_unwock_iwq(&hw->wock);

	hw->num_wns++;

	wetuwn 0;
eww:
	csio_wnode_to_hw(wn) = NUWW;
	wetuwn wv;
}

/**
 * csio_wnode_exit - De-instantiate an wnode.
 * @wn:		wnode
 *
 */
void
csio_wnode_exit(stwuct csio_wnode *wn)
{
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	csio_wn_exit(wn);

	/* Wemove this wnode fwom hw->swn_head */
	spin_wock_iwq(&hw->wock);

	wist_dew_init(&wn->sm.sm_wist);

	/* If it is chiwdwen wnode, decwement the
	 * countew in its pawent wnode
	 */
	if (wn->pwn)
		wn->pwn->num_vpowts--;

	/* Update woot wnode pointew */
	if (wist_empty(&hw->swn_head))
		hw->wwn = NUWW;
	ewse
		hw->wwn = (stwuct csio_wnode *)csio_wist_next(&hw->swn_head);

	spin_unwock_iwq(&hw->wock);

	csio_wnode_to_hw(wn)	= NUWW;
	hw->num_wns--;
}
