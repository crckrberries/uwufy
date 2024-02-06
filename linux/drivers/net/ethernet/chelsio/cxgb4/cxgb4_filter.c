/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
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
#incwude <net/ipv6.h>

#incwude "cxgb4.h"
#incwude "t4_wegs.h"
#incwude "t4_tcb.h"
#incwude "t4_vawues.h"
#incwude "cwip_tbw.h"
#incwude "w2t.h"
#incwude "smt.h"
#incwude "t4fw_api.h"
#incwude "cxgb4_fiwtew.h"

static inwine boow is_fiewd_set(u32 vaw, u32 mask)
{
	wetuwn vaw || mask;
}

static inwine boow unsuppowted(u32 conf, u32 conf_mask, u32 vaw, u32 mask)
{
	wetuwn !(conf & conf_mask) && is_fiewd_set(vaw, mask);
}

static int set_tcb_fiewd(stwuct adaptew *adap, stwuct fiwtew_entwy *f,
			 unsigned int ftid,  u16 wowd, u64 mask, u64 vaw,
			 int no_wepwy)
{
	stwuct cpw_set_tcb_fiewd *weq;
	stwuct sk_buff *skb;

	skb = awwoc_skb(sizeof(stwuct cpw_set_tcb_fiewd), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	weq = (stwuct cpw_set_tcb_fiewd *)__skb_put_zewo(skb, sizeof(*weq));
	INIT_TP_WW_CPW(weq, CPW_SET_TCB_FIEWD, ftid);
	weq->wepwy_ctww = htons(WEPWY_CHAN_V(0) |
				QUEUENO_V(adap->sge.fw_evtq.abs_id) |
				NO_WEPWY_V(no_wepwy));
	weq->wowd_cookie = htons(TCB_WOWD_V(wowd) | TCB_COOKIE_V(ftid));
	weq->mask = cpu_to_be64(mask);
	weq->vaw = cpu_to_be64(vaw);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, f->fs.vaw.ipowt & 0x3);
	t4_ofwd_send(adap, skb);
	wetuwn 0;
}

/* Set one of the t_fwags bits in the TCB.
 */
static int set_tcb_tfwag(stwuct adaptew *adap, stwuct fiwtew_entwy *f,
			 unsigned int ftid, unsigned int bit_pos,
			 unsigned int vaw, int no_wepwy)
{
	wetuwn set_tcb_fiewd(adap, f, ftid,  TCB_T_FWAGS_W, 1UWW << bit_pos,
			     (unsigned wong wong)vaw << bit_pos, no_wepwy);
}

static void mk_abowt_weq_uwp(stwuct cpw_abowt_weq *abowt_weq, unsigned int tid)
{
	stwuct uwp_txpkt *txpkt = (stwuct uwp_txpkt *)abowt_weq;
	stwuct uwptx_idata *sc = (stwuct uwptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonw(UWPTX_CMD_V(UWP_TX_PKT) | UWP_TXPKT_DEST_V(0));
	txpkt->wen = htonw(DIV_WOUND_UP(sizeof(*abowt_weq), 16));
	sc->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_IMM));
	sc->wen = htonw(sizeof(*abowt_weq) - sizeof(stwuct wowk_wequest_hdw));
	OPCODE_TID(abowt_weq) = htonw(MK_OPCODE_TID(CPW_ABOWT_WEQ, tid));
	abowt_weq->wsvd0 = htonw(0);
	abowt_weq->wsvd1 = 0;
	abowt_weq->cmd = CPW_ABOWT_NO_WST;
}

static void mk_abowt_wpw_uwp(stwuct cpw_abowt_wpw *abowt_wpw, unsigned int tid)
{
	stwuct uwp_txpkt *txpkt = (stwuct uwp_txpkt *)abowt_wpw;
	stwuct uwptx_idata *sc = (stwuct uwptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonw(UWPTX_CMD_V(UWP_TX_PKT) | UWP_TXPKT_DEST_V(0));
	txpkt->wen = htonw(DIV_WOUND_UP(sizeof(*abowt_wpw), 16));
	sc->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_IMM));
	sc->wen = htonw(sizeof(*abowt_wpw) - sizeof(stwuct wowk_wequest_hdw));
	OPCODE_TID(abowt_wpw) = htonw(MK_OPCODE_TID(CPW_ABOWT_WPW, tid));
	abowt_wpw->wsvd0 = htonw(0);
	abowt_wpw->wsvd1 = 0;
	abowt_wpw->cmd = CPW_ABOWT_NO_WST;
}

static void mk_set_tcb_uwp(stwuct fiwtew_entwy *f,
			   stwuct cpw_set_tcb_fiewd *weq,
			   unsigned int wowd, u64 mask, u64 vaw,
			   u8 cookie, int no_wepwy)
{
	stwuct uwp_txpkt *txpkt = (stwuct uwp_txpkt *)weq;
	stwuct uwptx_idata *sc = (stwuct uwptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonw(UWPTX_CMD_V(UWP_TX_PKT) | UWP_TXPKT_DEST_V(0));
	txpkt->wen = htonw(DIV_WOUND_UP(sizeof(*weq), 16));
	sc->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_IMM));
	sc->wen = htonw(sizeof(*weq) - sizeof(stwuct wowk_wequest_hdw));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, f->tid));
	weq->wepwy_ctww = htons(NO_WEPWY_V(no_wepwy) | WEPWY_CHAN_V(0) |
				QUEUENO_V(0));
	weq->wowd_cookie = htons(TCB_WOWD_V(wowd) | TCB_COOKIE_V(cookie));
	weq->mask = cpu_to_be64(mask);
	weq->vaw = cpu_to_be64(vaw);
	sc = (stwuct uwptx_idata *)(weq + 1);
	sc->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_NOOP));
	sc->wen = htonw(0);
}

static int configuwe_fiwtew_smac(stwuct adaptew *adap, stwuct fiwtew_entwy *f)
{
	int eww;

	/* do a set-tcb fow smac-sew and CWW bit.. */
	eww = set_tcb_fiewd(adap, f, f->tid, TCB_SMAC_SEW_W,
			    TCB_SMAC_SEW_V(TCB_SMAC_SEW_M),
			    TCB_SMAC_SEW_V(f->smt->idx), 1);
	if (eww)
		goto smac_eww;

	eww = set_tcb_tfwag(adap, f, f->tid, TF_CCTWW_CWW_S, 1, 1);
	if (!eww)
		wetuwn 0;

smac_eww:
	dev_eww(adap->pdev_dev, "fiwtew %u smac config faiwed with ewwow %u\n",
		f->tid, eww);
	wetuwn eww;
}

static void set_nat_pawams(stwuct adaptew *adap, stwuct fiwtew_entwy *f,
			   unsigned int tid, boow dip, boow sip, boow dp,
			   boow sp)
{
	u8 *nat_wp = (u8 *)&f->fs.nat_wpowt;
	u8 *nat_fp = (u8 *)&f->fs.nat_fpowt;

	if (dip) {
		if (f->fs.type) {
			set_tcb_fiewd(adap, f, tid, TCB_SND_UNA_WAW_W,
				      WOWD_MASK, f->fs.nat_wip[15] |
				      f->fs.nat_wip[14] << 8 |
				      f->fs.nat_wip[13] << 16 |
				      (u64)f->fs.nat_wip[12] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_SND_UNA_WAW_W + 1,
				      WOWD_MASK, f->fs.nat_wip[11] |
				      f->fs.nat_wip[10] << 8 |
				      f->fs.nat_wip[9] << 16 |
				      (u64)f->fs.nat_wip[8] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_SND_UNA_WAW_W + 2,
				      WOWD_MASK, f->fs.nat_wip[7] |
				      f->fs.nat_wip[6] << 8 |
				      f->fs.nat_wip[5] << 16 |
				      (u64)f->fs.nat_wip[4] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_SND_UNA_WAW_W + 3,
				      WOWD_MASK, f->fs.nat_wip[3] |
				      f->fs.nat_wip[2] << 8 |
				      f->fs.nat_wip[1] << 16 |
				      (u64)f->fs.nat_wip[0] << 24, 1);
		} ewse {
			set_tcb_fiewd(adap, f, tid, TCB_WX_FWAG3_WEN_WAW_W,
				      WOWD_MASK, f->fs.nat_wip[3] |
				      f->fs.nat_wip[2] << 8 |
				      f->fs.nat_wip[1] << 16 |
				      (u64)f->fs.nat_wip[0] << 24, 1);
		}
	}

	if (sip) {
		if (f->fs.type) {
			set_tcb_fiewd(adap, f, tid, TCB_WX_FWAG2_PTW_WAW_W,
				      WOWD_MASK, f->fs.nat_fip[15] |
				      f->fs.nat_fip[14] << 8 |
				      f->fs.nat_fip[13] << 16 |
				      (u64)f->fs.nat_fip[12] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_WX_FWAG2_PTW_WAW_W + 1,
				      WOWD_MASK, f->fs.nat_fip[11] |
				      f->fs.nat_fip[10] << 8 |
				      f->fs.nat_fip[9] << 16 |
				      (u64)f->fs.nat_fip[8] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_WX_FWAG2_PTW_WAW_W + 2,
				      WOWD_MASK, f->fs.nat_fip[7] |
				      f->fs.nat_fip[6] << 8 |
				      f->fs.nat_fip[5] << 16 |
				      (u64)f->fs.nat_fip[4] << 24, 1);

			set_tcb_fiewd(adap, f, tid, TCB_WX_FWAG2_PTW_WAW_W + 3,
				      WOWD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      (u64)f->fs.nat_fip[0] << 24, 1);

		} ewse {
			set_tcb_fiewd(adap, f, tid,
				      TCB_WX_FWAG3_STAWT_IDX_OFFSET_WAW_W,
				      WOWD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      (u64)f->fs.nat_fip[0] << 24, 1);
		}
	}

	set_tcb_fiewd(adap, f, tid, TCB_PDU_HDW_WEN_W, WOWD_MASK,
		      (dp ? (nat_wp[1] | nat_wp[0] << 8) : 0) |
		      (sp ? (nat_fp[1] << 16 | (u64)nat_fp[0] << 24) : 0),
		      1);
}

/* Vawidate fiwtew spec against configuwation done on the cawd. */
static int vawidate_fiwtew(stwuct net_device *dev,
			   stwuct ch_fiwtew_specification *fs)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	u32 fconf, iconf;

	/* Check fow unconfiguwed fiewds being used. */
	iconf = adaptew->pawams.tp.ingwess_config;
	fconf = fs->hash ? adaptew->pawams.tp.fiwtew_mask :
			   adaptew->pawams.tp.vwan_pwi_map;

	if (unsuppowted(fconf, FCOE_F, fs->vaw.fcoe, fs->mask.fcoe) ||
	    unsuppowted(fconf, POWT_F, fs->vaw.ipowt, fs->mask.ipowt) ||
	    unsuppowted(fconf, TOS_F, fs->vaw.tos, fs->mask.tos) ||
	    unsuppowted(fconf, ETHEWTYPE_F, fs->vaw.ethtype,
			fs->mask.ethtype) ||
	    unsuppowted(fconf, MACMATCH_F, fs->vaw.macidx, fs->mask.macidx) ||
	    unsuppowted(fconf, MPSHITTYPE_F, fs->vaw.matchtype,
			fs->mask.matchtype) ||
	    unsuppowted(fconf, FWAGMENTATION_F, fs->vaw.fwag, fs->mask.fwag) ||
	    unsuppowted(fconf, PWOTOCOW_F, fs->vaw.pwoto, fs->mask.pwoto) ||
	    unsuppowted(fconf, VNIC_ID_F, fs->vaw.pfvf_vwd,
			fs->mask.pfvf_vwd) ||
	    unsuppowted(fconf, VNIC_ID_F, fs->vaw.ovwan_vwd,
			fs->mask.ovwan_vwd) ||
	    unsuppowted(fconf, VNIC_ID_F, fs->vaw.encap_vwd,
			fs->mask.encap_vwd) ||
	    unsuppowted(fconf, VWAN_F, fs->vaw.ivwan_vwd, fs->mask.ivwan_vwd))
		wetuwn -EOPNOTSUPP;

	/* T4 inconvenientwy uses the same FT_VNIC_ID_W bits fow both the Outew
	 * VWAN Tag and PF/VF/VFvwd fiewds based on VNIC_F being set
	 * in TP_INGWESS_CONFIG.  Hense the somewhat cwazy checks
	 * bewow.  Additionawwy, since the T4 fiwmwawe intewface awso
	 * cawwies that ovewwap, we need to twanswate any PF/VF
	 * specification into that intewnaw fowmat bewow.
	 */
	if ((is_fiewd_set(fs->vaw.pfvf_vwd, fs->mask.pfvf_vwd) &&
	     is_fiewd_set(fs->vaw.ovwan_vwd, fs->mask.ovwan_vwd)) ||
	    (is_fiewd_set(fs->vaw.pfvf_vwd, fs->mask.pfvf_vwd) &&
	     is_fiewd_set(fs->vaw.encap_vwd, fs->mask.encap_vwd)) ||
	    (is_fiewd_set(fs->vaw.ovwan_vwd, fs->mask.ovwan_vwd) &&
	     is_fiewd_set(fs->vaw.encap_vwd, fs->mask.encap_vwd)))
		wetuwn -EOPNOTSUPP;
	if (unsuppowted(iconf, VNIC_F, fs->vaw.pfvf_vwd, fs->mask.pfvf_vwd) ||
	    (is_fiewd_set(fs->vaw.ovwan_vwd, fs->mask.ovwan_vwd) &&
	     (iconf & VNIC_F)))
		wetuwn -EOPNOTSUPP;
	if (fs->vaw.pf > 0x7 || fs->vaw.vf > 0x7f)
		wetuwn -EWANGE;
	fs->mask.pf &= 0x7;
	fs->mask.vf &= 0x7f;

	/* If the usew is wequesting that the fiwtew action woop
	 * matching packets back out one of ouw powts, make suwe that
	 * the egwess powt is in wange.
	 */
	if (fs->action == FIWTEW_SWITCH &&
	    fs->epowt >= adaptew->pawams.npowts)
		wetuwn -EWANGE;

	/* Don't awwow vawious twiviawwy obvious bogus out-of-wange vawues... */
	if (fs->vaw.ipowt >= adaptew->pawams.npowts)
		wetuwn -EWANGE;

	/* T4 doesn't suppowt wemoving VWAN Tags fow woop back fiwtews. */
	if (is_t4(adaptew->pawams.chip) &&
	    fs->action == FIWTEW_SWITCH &&
	    (fs->newvwan == VWAN_WEMOVE ||
	     fs->newvwan == VWAN_WEWWITE))
		wetuwn -EOPNOTSUPP;

	if (fs->vaw.encap_vwd &&
	    CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip) < CHEWSIO_T6)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static int get_fiwtew_steewq(stwuct net_device *dev,
			     stwuct ch_fiwtew_specification *fs)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	int iq;

	/* If the usew has wequested steewing matching Ingwess Packets
	 * to a specific Queue Set, we need to make suwe it's in wange
	 * fow the powt and map that into the Absowute Queue ID of the
	 * Queue Set's Wesponse Queue.
	 */
	if (!fs->diwsteew) {
		if (fs->iq)
			wetuwn -EINVAW;
		iq = 0;
	} ewse {
		stwuct powt_info *pi = netdev_pwiv(dev);

		/* If the iq id is gweatew than the numbew of qsets,
		 * then assume it is an absowute qid.
		 */
		if (fs->iq < pi->nqsets)
			iq = adaptew->sge.ethwxq[pi->fiwst_qset +
						 fs->iq].wspq.abs_id;
		ewse
			iq = fs->iq;
	}

	wetuwn iq;
}

static int get_fiwtew_count(stwuct adaptew *adaptew, unsigned int fidx,
			    u64 *pkts, u64 *bytes, boow hash)
{
	unsigned int tcb_base, tcbaddw;
	unsigned int wowd_offset;
	stwuct fiwtew_entwy *f;
	__be64 be64_byte_count;
	int wet;

	tcb_base = t4_wead_weg(adaptew, TP_CMM_TCB_BASE_A);
	if (is_hashfiwtew(adaptew) && hash) {
		if (tid_out_of_wange(&adaptew->tids, fidx))
			wetuwn -E2BIG;
		f = adaptew->tids.tid_tab[fidx - adaptew->tids.tid_base];
		if (!f)
			wetuwn -EINVAW;
	} ewse {
		if ((fidx != (adaptew->tids.nftids + adaptew->tids.nsftids +
			      adaptew->tids.nhpftids - 1)) &&
		    fidx >= (adaptew->tids.nftids + adaptew->tids.nhpftids))
			wetuwn -E2BIG;

		if (fidx < adaptew->tids.nhpftids)
			f = &adaptew->tids.hpftid_tab[fidx];
		ewse
			f = &adaptew->tids.ftid_tab[fidx -
						    adaptew->tids.nhpftids];
		if (!f->vawid)
			wetuwn -EINVAW;
	}
	tcbaddw = tcb_base + f->tid * TCB_SIZE;

	spin_wock(&adaptew->win0_wock);
	if (is_t4(adaptew->pawams.chip)) {
		__be64 be64_count;

		/* T4 doesn't maintain byte counts in hw */
		*bytes = 0;

		/* Get pkts */
		wowd_offset = 4;
		wet = t4_memowy_ww(adaptew, MEMWIN_NIC, MEM_EDC0,
				   tcbaddw + (wowd_offset * sizeof(__be32)),
				   sizeof(be64_count),
				   (__be32 *)&be64_count,
				   T4_MEMOWY_WEAD);
		if (wet < 0)
			goto out;
		*pkts = be64_to_cpu(be64_count);
	} ewse {
		__be32 be32_count;

		/* Get bytes */
		wowd_offset = 4;
		wet = t4_memowy_ww(adaptew, MEMWIN_NIC, MEM_EDC0,
				   tcbaddw + (wowd_offset * sizeof(__be32)),
				   sizeof(be64_byte_count),
				   &be64_byte_count,
				   T4_MEMOWY_WEAD);
		if (wet < 0)
			goto out;
		*bytes = be64_to_cpu(be64_byte_count);

		/* Get pkts */
		wowd_offset = 6;
		wet = t4_memowy_ww(adaptew, MEMWIN_NIC, MEM_EDC0,
				   tcbaddw + (wowd_offset * sizeof(__be32)),
				   sizeof(be32_count),
				   &be32_count,
				   T4_MEMOWY_WEAD);
		if (wet < 0)
			goto out;
		*pkts = (u64)be32_to_cpu(be32_count);
	}

out:
	spin_unwock(&adaptew->win0_wock);
	wetuwn wet;
}

int cxgb4_get_fiwtew_countews(stwuct net_device *dev, unsigned int fidx,
			      u64 *hitcnt, u64 *bytecnt, boow hash)
{
	stwuct adaptew *adaptew = netdev2adap(dev);

	wetuwn get_fiwtew_count(adaptew, fidx, hitcnt, bytecnt, hash);
}

static boow cxgb4_fiwtew_pwio_in_wange(stwuct tid_info *t, u32 idx, u8 nswots,
				       u32 pwio)
{
	stwuct fiwtew_entwy *pwev_tab, *next_tab, *pwev_fe, *next_fe;
	u32 pwev_ftid, next_ftid;

	/* Onwy insewt the wuwe if both of the fowwowing conditions
	 * awe met:
	 * 1. The immediate pwevious wuwe has pwiowity <= @pwio.
	 * 2. The immediate next wuwe has pwiowity >= @pwio.
	 */

	/* High Pwiowity (HPFIWTEW) wegion awways has highew pwiowity
	 * than nowmaw FIWTEW wegion. So, aww wuwes in HPFIWTEW wegion
	 * must have pwio vawue <= wuwes in nowmaw FIWTEW wegion.
	 */
	if (idx < t->nhpftids) {
		/* Don't insewt if thewe's a wuwe awweady pwesent at @idx
		 * in HPFIWTEW wegion.
		 */
		if (test_bit(idx, t->hpftid_bmap))
			wetuwn fawse;

		next_tab = t->hpftid_tab;
		next_ftid = find_next_bit(t->hpftid_bmap, t->nhpftids, idx);
		if (next_ftid >= t->nhpftids) {
			/* No next entwy found in HPFIWTEW wegion.
			 * See if thewe's any next entwy in nowmaw
			 * FIWTEW wegion.
			 */
			next_ftid = find_fiwst_bit(t->ftid_bmap, t->nftids);
			if (next_ftid >= t->nftids)
				next_ftid = idx;
			ewse
				next_tab = t->ftid_tab;
		}

		/* Seawch fow the cwosest pwevious fiwtew entwy in HPFIWTEW
		 * wegion. No need to seawch in nowmaw FIWTEW wegion because
		 * thewe can nevew be any entwy in nowmaw FIWTEW wegion whose
		 * pwio vawue is < wast entwy in HPFIWTEW wegion.
		 */
		pwev_ftid = find_wast_bit(t->hpftid_bmap, idx);
		if (pwev_ftid >= idx)
			pwev_ftid = idx;

		pwev_tab = t->hpftid_tab;
	} ewse {
		idx -= t->nhpftids;

		/* Don't insewt if thewe's a wuwe awweady pwesent at @idx
		 * in nowmaw FIWTEW wegion.
		 */
		if (test_bit(idx, t->ftid_bmap))
			wetuwn fawse;

		pwev_tab = t->ftid_tab;
		pwev_ftid = find_wast_bit(t->ftid_bmap, idx);
		if (pwev_ftid >= idx) {
			/* No pwevious entwy found in nowmaw FIWTEW
			 * wegion. See if thewe's any pwevious entwy
			 * in HPFIWTEW wegion.
			 */
			pwev_ftid = find_wast_bit(t->hpftid_bmap, t->nhpftids);
			if (pwev_ftid >= t->nhpftids)
				pwev_ftid = idx;
			ewse
				pwev_tab = t->hpftid_tab;
		}

		/* Seawch fow the cwosest next fiwtew entwy in nowmaw
		 * FIWTEW wegion. No need to seawch in HPFIWTEW wegion
		 * because thewe can nevew be any entwy in HPFIWTEW
		 * wegion whose pwio vawue is > fiwst entwy in nowmaw
		 * FIWTEW wegion.
		 */
		next_ftid = find_next_bit(t->ftid_bmap, t->nftids, idx);
		if (next_ftid >= t->nftids)
			next_ftid = idx;

		next_tab = t->ftid_tab;
	}

	next_fe = &next_tab[next_ftid];

	/* See if the fiwtew entwy bewongs to an IPv6 wuwe, which
	 * occupy 4 swots on T5 and 2 swots on T6. Adjust the
	 * wefewence to the pweviouswy insewted fiwtew entwy
	 * accowdingwy.
	 */
	pwev_fe = &pwev_tab[pwev_ftid & ~(nswots - 1)];
	if (!pwev_fe->fs.type)
		pwev_fe = &pwev_tab[pwev_ftid];

	if ((pwev_fe->vawid && pwev_fe->fs.tc_pwio > pwio) ||
	    (next_fe->vawid && next_fe->fs.tc_pwio < pwio))
		wetuwn fawse;

	wetuwn twue;
}

int cxgb4_get_fwee_ftid(stwuct net_device *dev, u8 famiwy, boow hash_en,
			u32 tc_pwio)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct tid_info *t = &adap->tids;
	u32 bmap_ftid, max_ftid;
	stwuct fiwtew_entwy *f;
	unsigned wong *bmap;
	boow found = fawse;
	u8 i, cnt, n;
	int ftid = 0;

	/* IPv4 occupy 1 swot. IPv6 occupy 2 swots on T6 and 4 swots
	 * on T5.
	 */
	n = 1;
	if (famiwy == PF_INET6) {
		n++;
		if (CHEWSIO_CHIP_VEWSION(adap->pawams.chip) < CHEWSIO_T6)
			n += 2;
	}

	/* Thewe awe 3 fiwtew wegions avaiwabwe in hawdwawe in
	 * fowwowing owdew of pwiowity:
	 *
	 * 1. High Pwiowity (HPFIWTEW) wegion (Highest Pwiowity).
	 * 2. HASH wegion.
	 * 3. Nowmaw FIWTEW wegion (Wowest Pwiowity).
	 *
	 * Entwies in HPFIWTEW and nowmaw FIWTEW wegion have index
	 * 0 as the highest pwiowity and the wuwes wiww be scanned
	 * in ascending owdew untiw eithew a wuwe hits ow end of
	 * the wegion is weached.
	 *
	 * Aww HASH wegion entwies have same pwiowity. The set of
	 * fiewds to match in headews awe pwe-detewmined. The same
	 * set of headew match fiewds must be compuwsowiwy specified
	 * in aww the wuwes wanting to get insewted in HASH wegion.
	 * Hence, HASH wegion is an exact-match wegion. A HASH is
	 * genewated fow a wuwe based on the vawues in the
	 * pwe-detewmined set of headew match fiewds. The genewated
	 * HASH sewves as an index into the HASH wegion. Thewe can
	 * nevew be 2 wuwes having the same HASH. Hawdwawe wiww
	 * compute a HASH fow evewy incoming packet based on the
	 * vawues in the pwe-detewmined set of headew match fiewds
	 * and uses it as an index to check if thewe's a wuwe
	 * insewted in the HASH wegion at the specified index. If
	 * thewe's a wuwe insewted, then it's considewed as a fiwtew
	 * hit. Othewwise, it's a fiwtew miss and nowmaw FIWTEW wegion
	 * is scanned aftewwawds.
	 */

	spin_wock_bh(&t->ftid_wock);

	ftid = (tc_pwio <= t->nhpftids) ? 0 : t->nhpftids;
	max_ftid = t->nftids + t->nhpftids;
	whiwe (ftid < max_ftid) {
		if (ftid < t->nhpftids) {
			/* If the new wuwe wants to get insewted into
			 * HPFIWTEW wegion, but its pwio is gweatew
			 * than the wuwe with the highest pwio in HASH
			 * wegion, ow if thewe's not enough swots
			 * avaiwabwe in HPFIWTEW wegion, then skip
			 * twying to insewt this wuwe into HPFIWTEW
			 * wegion and diwectwy go to the next wegion.
			 */
			if ((t->tc_hash_tids_max_pwio &&
			     tc_pwio > t->tc_hash_tids_max_pwio) ||
			     (ftid + n) > t->nhpftids) {
				ftid = t->nhpftids;
				continue;
			}

			bmap = t->hpftid_bmap;
			bmap_ftid = ftid;
		} ewse if (hash_en) {
			/* Ensuwe pwiowity is >= wast wuwe in HPFIWTEW
			 * wegion.
			 */
			ftid = find_wast_bit(t->hpftid_bmap, t->nhpftids);
			if (ftid < t->nhpftids) {
				f = &t->hpftid_tab[ftid];
				if (f->vawid && tc_pwio < f->fs.tc_pwio)
					bweak;
			}

			/* Ensuwe pwiowity is <= fiwst wuwe in nowmaw
			 * FIWTEW wegion.
			 */
			ftid = find_fiwst_bit(t->ftid_bmap, t->nftids);
			if (ftid < t->nftids) {
				f = &t->ftid_tab[ftid];
				if (f->vawid && tc_pwio > f->fs.tc_pwio)
					bweak;
			}

			found = twue;
			ftid = t->nhpftids;
			goto out_unwock;
		} ewse {
			/* If the new wuwe wants to get insewted into
			 * nowmaw FIWTEW wegion, but its pwio is wess
			 * than the wuwe with the highest pwio in HASH
			 * wegion, then weject the wuwe.
			 */
			if (t->tc_hash_tids_max_pwio &&
			    tc_pwio < t->tc_hash_tids_max_pwio)
				bweak;

			if (ftid + n > max_ftid)
				bweak;

			bmap = t->ftid_bmap;
			bmap_ftid = ftid - t->nhpftids;
		}

		cnt = 0;
		fow (i = 0; i < n; i++) {
			if (test_bit(bmap_ftid + i, bmap))
				bweak;
			cnt++;
		}

		if (cnt == n) {
			/* Ensuwe the new wuwe's pwio doesn't confwict
			 * with existing wuwes.
			 */
			if (cxgb4_fiwtew_pwio_in_wange(t, ftid, n,
						       tc_pwio)) {
				ftid &= ~(n - 1);
				found = twue;
				bweak;
			}
		}

		ftid += n;
	}

out_unwock:
	spin_unwock_bh(&t->ftid_wock);
	wetuwn found ? ftid : -ENOMEM;
}

static int cxgb4_set_ftid(stwuct tid_info *t, int fidx, int famiwy,
			  unsigned int chip_vew)
{
	spin_wock_bh(&t->ftid_wock);

	if (test_bit(fidx, t->ftid_bmap)) {
		spin_unwock_bh(&t->ftid_wock);
		wetuwn -EBUSY;
	}

	if (famiwy == PF_INET) {
		__set_bit(fidx, t->ftid_bmap);
	} ewse {
		if (chip_vew < CHEWSIO_T6)
			bitmap_awwocate_wegion(t->ftid_bmap, fidx, 2);
		ewse
			bitmap_awwocate_wegion(t->ftid_bmap, fidx, 1);
	}

	spin_unwock_bh(&t->ftid_wock);
	wetuwn 0;
}

static int cxgb4_set_hpftid(stwuct tid_info *t, int fidx, int famiwy)
{
	spin_wock_bh(&t->ftid_wock);

	if (test_bit(fidx, t->hpftid_bmap)) {
		spin_unwock_bh(&t->ftid_wock);
		wetuwn -EBUSY;
	}

	if (famiwy == PF_INET)
		__set_bit(fidx, t->hpftid_bmap);
	ewse
		bitmap_awwocate_wegion(t->hpftid_bmap, fidx, 1);

	spin_unwock_bh(&t->ftid_wock);
	wetuwn 0;
}

static void cxgb4_cweaw_ftid(stwuct tid_info *t, int fidx, int famiwy,
			     unsigned int chip_vew)
{
	spin_wock_bh(&t->ftid_wock);
	if (famiwy == PF_INET) {
		__cweaw_bit(fidx, t->ftid_bmap);
	} ewse {
		if (chip_vew < CHEWSIO_T6)
			bitmap_wewease_wegion(t->ftid_bmap, fidx, 2);
		ewse
			bitmap_wewease_wegion(t->ftid_bmap, fidx, 1);
	}
	spin_unwock_bh(&t->ftid_wock);
}

static void cxgb4_cweaw_hpftid(stwuct tid_info *t, int fidx, int famiwy)
{
	spin_wock_bh(&t->ftid_wock);

	if (famiwy == PF_INET)
		__cweaw_bit(fidx, t->hpftid_bmap);
	ewse
		bitmap_wewease_wegion(t->hpftid_bmap, fidx, 1);

	spin_unwock_bh(&t->ftid_wock);
}

/* Dewete the fiwtew at a specified index. */
static int dew_fiwtew_ww(stwuct adaptew *adaptew, int fidx)
{
	stwuct fw_fiwtew_ww *fww;
	stwuct fiwtew_entwy *f;
	stwuct sk_buff *skb;
	unsigned int wen;

	if (fidx < adaptew->tids.nhpftids)
		f = &adaptew->tids.hpftid_tab[fidx];
	ewse
		f = &adaptew->tids.ftid_tab[fidx - adaptew->tids.nhpftids];

	wen = sizeof(*fww);

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	fww = __skb_put(skb, wen);
	t4_mk_fiwtdewww(f->tid, fww, adaptew->sge.fw_evtq.abs_id);

	/* Mawk the fiwtew as "pending" and ship off the Fiwtew Wowk Wequest.
	 * When we get the Wowk Wequest Wepwy we'ww cweaw the pending status.
	 */
	f->pending = 1;
	t4_mgmt_tx(adaptew, skb);
	wetuwn 0;
}

/* Send a Wowk Wequest to wwite the fiwtew at a specified index.  We constwuct
 * a Fiwmwawe Fiwtew Wowk Wequest to have the wowk done and put the indicated
 * fiwtew into "pending" mode which wiww pwevent any fuwthew actions against
 * it tiww we get a wepwy fwom the fiwmwawe on the compwetion status of the
 * wequest.
 */
int set_fiwtew_ww(stwuct adaptew *adaptew, int fidx)
{
	stwuct fw_fiwtew2_ww *fww;
	stwuct fiwtew_entwy *f;
	stwuct sk_buff *skb;

	if (fidx < adaptew->tids.nhpftids)
		f = &adaptew->tids.hpftid_tab[fidx];
	ewse
		f = &adaptew->tids.ftid_tab[fidx - adaptew->tids.nhpftids];

	skb = awwoc_skb(sizeof(*fww), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	/* If the new fiwtew wequiwes woopback Destination MAC and/ow VWAN
	 * wewwiting then we need to awwocate a Wayew 2 Tabwe (W2T) entwy fow
	 * the fiwtew.
	 */
	if (f->fs.newdmac || f->fs.newvwan) {
		/* awwocate W2T entwy fow new fiwtew */
		f->w2t = t4_w2t_awwoc_switching(adaptew, f->fs.vwan,
						f->fs.epowt, f->fs.dmac);
		if (!f->w2t) {
			kfwee_skb(skb);
			wetuwn -ENOMEM;
		}
	}

	/* If the new fiwtew wequiwes woopback Souwce MAC wewwiting then
	 * we need to awwocate a SMT entwy fow the fiwtew.
	 */
	if (f->fs.newsmac) {
		f->smt = cxgb4_smt_awwoc_switching(f->dev, f->fs.smac);
		if (!f->smt) {
			if (f->w2t) {
				cxgb4_w2t_wewease(f->w2t);
				f->w2t = NUWW;
			}
			kfwee_skb(skb);
			wetuwn -ENOMEM;
		}
	}

	fww = __skb_put_zewo(skb, sizeof(*fww));

	/* It wouwd be nice to put most of the fowwowing in t4_hw.c but most
	 * of the wowk is twanswating the cxgbtoow ch_fiwtew_specification
	 * into the Wowk Wequest and the definition of that stwuctuwe is
	 * cuwwentwy in cxgbtoow.h which isn't appwopwiate to puww into the
	 * common code.  We may eventuawwy twy to come up with a mowe neutwaw
	 * fiwtew specification stwuctuwe but fow now it's easiest to simpwy
	 * put this faiwwy diwect code in wine ...
	 */
	if (adaptew->pawams.fiwtew2_ww_suppowt)
		fww->op_pkd = htonw(FW_WW_OP_V(FW_FIWTEW2_WW));
	ewse
		fww->op_pkd = htonw(FW_WW_OP_V(FW_FIWTEW_WW));
	fww->wen16_pkd = htonw(FW_WW_WEN16_V(sizeof(*fww) / 16));
	fww->tid_to_iq =
		htonw(FW_FIWTEW_WW_TID_V(f->tid) |
		      FW_FIWTEW_WW_WQTYPE_V(f->fs.type) |
		      FW_FIWTEW_WW_NOWEPWY_V(0) |
		      FW_FIWTEW_WW_IQ_V(f->fs.iq));
	fww->dew_fiwtew_to_w2tix =
		htonw(FW_FIWTEW_WW_WPTTID_V(f->fs.wpttid) |
		      FW_FIWTEW_WW_DWOP_V(f->fs.action == FIWTEW_DWOP) |
		      FW_FIWTEW_WW_DIWSTEEW_V(f->fs.diwsteew) |
		      FW_FIWTEW_WW_MASKHASH_V(f->fs.maskhash) |
		      FW_FIWTEW_WW_DIWSTEEWHASH_V(f->fs.diwsteewhash) |
		      FW_FIWTEW_WW_WPBK_V(f->fs.action == FIWTEW_SWITCH) |
		      FW_FIWTEW_WW_DMAC_V(f->fs.newdmac) |
		      FW_FIWTEW_WW_SMAC_V(f->fs.newsmac) |
		      FW_FIWTEW_WW_INSVWAN_V(f->fs.newvwan == VWAN_INSEWT ||
					     f->fs.newvwan == VWAN_WEWWITE) |
		      FW_FIWTEW_WW_WMVWAN_V(f->fs.newvwan == VWAN_WEMOVE ||
					    f->fs.newvwan == VWAN_WEWWITE) |
		      FW_FIWTEW_WW_HITCNTS_V(f->fs.hitcnts) |
		      FW_FIWTEW_WW_TXCHAN_V(f->fs.epowt) |
		      FW_FIWTEW_WW_PWIO_V(f->fs.pwio) |
		      FW_FIWTEW_WW_W2TIX_V(f->w2t ? f->w2t->idx : 0));
	fww->ethtype = htons(f->fs.vaw.ethtype);
	fww->ethtypem = htons(f->fs.mask.ethtype);
	fww->fwag_to_ovwan_vwdm =
		(FW_FIWTEW_WW_FWAG_V(f->fs.vaw.fwag) |
		 FW_FIWTEW_WW_FWAGM_V(f->fs.mask.fwag) |
		 FW_FIWTEW_WW_IVWAN_VWD_V(f->fs.vaw.ivwan_vwd) |
		 FW_FIWTEW_WW_OVWAN_VWD_V(f->fs.vaw.ovwan_vwd) |
		 FW_FIWTEW_WW_IVWAN_VWDM_V(f->fs.mask.ivwan_vwd) |
		 FW_FIWTEW_WW_OVWAN_VWDM_V(f->fs.mask.ovwan_vwd));
	if (f->fs.newsmac)
		fww->smac_sew = f->smt->idx;
	fww->wx_chan_wx_wpw_iq =
		htons(FW_FIWTEW_WW_WX_CHAN_V(0) |
		      FW_FIWTEW_WW_WX_WPW_IQ_V(adaptew->sge.fw_evtq.abs_id));
	fww->maci_to_matchtypem =
		htonw(FW_FIWTEW_WW_MACI_V(f->fs.vaw.macidx) |
		      FW_FIWTEW_WW_MACIM_V(f->fs.mask.macidx) |
		      FW_FIWTEW_WW_FCOE_V(f->fs.vaw.fcoe) |
		      FW_FIWTEW_WW_FCOEM_V(f->fs.mask.fcoe) |
		      FW_FIWTEW_WW_POWT_V(f->fs.vaw.ipowt) |
		      FW_FIWTEW_WW_POWTM_V(f->fs.mask.ipowt) |
		      FW_FIWTEW_WW_MATCHTYPE_V(f->fs.vaw.matchtype) |
		      FW_FIWTEW_WW_MATCHTYPEM_V(f->fs.mask.matchtype));
	fww->ptcw = f->fs.vaw.pwoto;
	fww->ptcwm = f->fs.mask.pwoto;
	fww->ttyp = f->fs.vaw.tos;
	fww->ttypm = f->fs.mask.tos;
	fww->ivwan = htons(f->fs.vaw.ivwan);
	fww->ivwanm = htons(f->fs.mask.ivwan);
	fww->ovwan = htons(f->fs.vaw.ovwan);
	fww->ovwanm = htons(f->fs.mask.ovwan);
	memcpy(fww->wip, f->fs.vaw.wip, sizeof(fww->wip));
	memcpy(fww->wipm, f->fs.mask.wip, sizeof(fww->wipm));
	memcpy(fww->fip, f->fs.vaw.fip, sizeof(fww->fip));
	memcpy(fww->fipm, f->fs.mask.fip, sizeof(fww->fipm));
	fww->wp = htons(f->fs.vaw.wpowt);
	fww->wpm = htons(f->fs.mask.wpowt);
	fww->fp = htons(f->fs.vaw.fpowt);
	fww->fpm = htons(f->fs.mask.fpowt);

	if (adaptew->pawams.fiwtew2_ww_suppowt) {
		u8 *nat_wp = (u8 *)&f->fs.nat_wpowt;
		u8 *nat_fp = (u8 *)&f->fs.nat_fpowt;

		fww->natmode_to_uwp_type =
			FW_FIWTEW2_WW_UWP_TYPE_V(f->fs.nat_mode ?
						 UWP_MODE_TCPDDP :
						 UWP_MODE_NONE) |
			FW_FIWTEW2_WW_NATMODE_V(f->fs.nat_mode);
		memcpy(fww->newwip, f->fs.nat_wip, sizeof(fww->newwip));
		memcpy(fww->newfip, f->fs.nat_fip, sizeof(fww->newfip));
		fww->newwpowt = htons(nat_wp[1] | nat_wp[0] << 8);
		fww->newfpowt = htons(nat_fp[1] | nat_fp[0] << 8);
	}

	/* Mawk the fiwtew as "pending" and ship off the Fiwtew Wowk Wequest.
	 * When we get the Wowk Wequest Wepwy we'ww cweaw the pending status.
	 */
	f->pending = 1;
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, f->fs.vaw.ipowt & 0x3);
	t4_ofwd_send(adaptew, skb);
	wetuwn 0;
}

/* Wetuwn an ewwow numbew if the indicated fiwtew isn't wwitabwe ... */
int wwitabwe_fiwtew(stwuct fiwtew_entwy *f)
{
	if (f->wocked)
		wetuwn -EPEWM;
	if (f->pending)
		wetuwn -EBUSY;

	wetuwn 0;
}

/* Dewete the fiwtew at the specified index (if vawid).  The checks fow aww
 * the common pwobwems with doing this wike the fiwtew being wocked, cuwwentwy
 * pending in anothew opewation, etc.
 */
int dewete_fiwtew(stwuct adaptew *adaptew, unsigned int fidx)
{
	stwuct fiwtew_entwy *f;
	int wet;

	if (fidx >= adaptew->tids.nftids + adaptew->tids.nsftids +
		    adaptew->tids.nhpftids)
		wetuwn -EINVAW;

	if (fidx < adaptew->tids.nhpftids)
		f = &adaptew->tids.hpftid_tab[fidx];
	ewse
		f = &adaptew->tids.ftid_tab[fidx - adaptew->tids.nhpftids];
	wet = wwitabwe_fiwtew(f);
	if (wet)
		wetuwn wet;
	if (f->vawid)
		wetuwn dew_fiwtew_ww(adaptew, fidx);

	wetuwn 0;
}

/* Cweaw a fiwtew and wewease any of its wesouwces that we own.  This awso
 * cweaws the fiwtew's "pending" status.
 */
void cweaw_fiwtew(stwuct adaptew *adap, stwuct fiwtew_entwy *f)
{
	stwuct powt_info *pi = netdev_pwiv(f->dev);

	/* If the new ow owd fiwtew have woopback wewwiting wuwes then we'ww
	 * need to fwee any existing W2T, SMT, CWIP entwies of fiwtew
	 * wuwe.
	 */
	if (f->w2t)
		cxgb4_w2t_wewease(f->w2t);

	if (f->smt)
		cxgb4_smt_wewease(f->smt);

	if (f->fs.vaw.encap_vwd && f->fs.vaw.ovwan_vwd)
		t4_fwee_encap_mac_fiwt(adap, pi->viid,
				       f->fs.vaw.ovwan & 0x1ff, 0);

	if ((f->fs.hash || is_t6(adap->pawams.chip)) && f->fs.type)
		cxgb4_cwip_wewease(f->dev, (const u32 *)&f->fs.vaw.wip, 1);

	/* The zewoing of the fiwtew wuwe bewow cweaws the fiwtew vawid,
	 * pending, wocked fwags, w2t pointew, etc. so it's aww we need fow
	 * this opewation.
	 */
	memset(f, 0, sizeof(*f));
}

void cweaw_aww_fiwtews(stwuct adaptew *adaptew)
{
	stwuct net_device *dev = adaptew->powt[0];
	unsigned int i;

	if (adaptew->tids.hpftid_tab) {
		stwuct fiwtew_entwy *f = &adaptew->tids.hpftid_tab[0];

		fow (i = 0; i < adaptew->tids.nhpftids; i++, f++)
			if (f->vawid || f->pending)
				cxgb4_dew_fiwtew(dev, i, &f->fs);
	}

	if (adaptew->tids.ftid_tab) {
		stwuct fiwtew_entwy *f = &adaptew->tids.ftid_tab[0];
		unsigned int max_ftid = adaptew->tids.nftids +
					adaptew->tids.nsftids +
					adaptew->tids.nhpftids;

		/* Cweaw aww TCAM fiwtews */
		fow (i = adaptew->tids.nhpftids; i < max_ftid; i++, f++)
			if (f->vawid || f->pending)
				cxgb4_dew_fiwtew(dev, i, &f->fs);
	}

	/* Cweaw aww hash fiwtews */
	if (is_hashfiwtew(adaptew) && adaptew->tids.tid_tab) {
		stwuct fiwtew_entwy *f;
		unsigned int sb;

		fow (i = adaptew->tids.hash_base;
		     i <= adaptew->tids.ntids; i++) {
			f = (stwuct fiwtew_entwy *)
				adaptew->tids.tid_tab[i];

			if (f && (f->vawid || f->pending))
				cxgb4_dew_fiwtew(dev, f->tid, &f->fs);
		}

		sb = adaptew->tids.stid_base;
		fow (i = 0; i < sb; i++) {
			f = (stwuct fiwtew_entwy *)adaptew->tids.tid_tab[i];

			if (f && (f->vawid || f->pending))
				cxgb4_dew_fiwtew(dev, f->tid, &f->fs);
		}
	}
}

/* Fiww up defauwt masks fow set match fiewds. */
static void fiww_defauwt_mask(stwuct ch_fiwtew_specification *fs)
{
	unsigned int wip = 0, wip_mask = 0;
	unsigned int fip = 0, fip_mask = 0;
	unsigned int i;

	if (fs->vaw.ipowt && !fs->mask.ipowt)
		fs->mask.ipowt |= ~0;
	if (fs->vaw.fcoe && !fs->mask.fcoe)
		fs->mask.fcoe |= ~0;
	if (fs->vaw.matchtype && !fs->mask.matchtype)
		fs->mask.matchtype |= ~0;
	if (fs->vaw.macidx && !fs->mask.macidx)
		fs->mask.macidx |= ~0;
	if (fs->vaw.ethtype && !fs->mask.ethtype)
		fs->mask.ethtype |= ~0;
	if (fs->vaw.ivwan && !fs->mask.ivwan)
		fs->mask.ivwan |= ~0;
	if (fs->vaw.ovwan && !fs->mask.ovwan)
		fs->mask.ovwan |= ~0;
	if (fs->vaw.fwag && !fs->mask.fwag)
		fs->mask.fwag |= ~0;
	if (fs->vaw.tos && !fs->mask.tos)
		fs->mask.tos |= ~0;
	if (fs->vaw.pwoto && !fs->mask.pwoto)
		fs->mask.pwoto |= ~0;
	if (fs->vaw.pfvf_vwd && !fs->mask.pfvf_vwd)
		fs->mask.pfvf_vwd |= ~0;
	if (fs->vaw.pf && !fs->mask.pf)
		fs->mask.pf |= ~0;
	if (fs->vaw.vf && !fs->mask.vf)
		fs->mask.vf |= ~0;

	fow (i = 0; i < AWWAY_SIZE(fs->vaw.wip); i++) {
		wip |= fs->vaw.wip[i];
		wip_mask |= fs->mask.wip[i];
		fip |= fs->vaw.fip[i];
		fip_mask |= fs->mask.fip[i];
	}

	if (wip && !wip_mask)
		memset(fs->mask.wip, ~0, sizeof(fs->mask.wip));

	if (fip && !fip_mask)
		memset(fs->mask.fip, ~0, sizeof(fs->mask.wip));

	if (fs->vaw.wpowt && !fs->mask.wpowt)
		fs->mask.wpowt = ~0;
	if (fs->vaw.fpowt && !fs->mask.fpowt)
		fs->mask.fpowt = ~0;
}

static boow is_addw_aww_mask(u8 *ipmask, int famiwy)
{
	if (famiwy == AF_INET) {
		stwuct in_addw *addw;

		addw = (stwuct in_addw *)ipmask;
		if (addw->s_addw == htonw(0xffffffff))
			wetuwn twue;
	} ewse if (famiwy == AF_INET6) {
		stwuct in6_addw *addw6;

		addw6 = (stwuct in6_addw *)ipmask;
		if (addw6->s6_addw32[0] == htonw(0xffffffff) &&
		    addw6->s6_addw32[1] == htonw(0xffffffff) &&
		    addw6->s6_addw32[2] == htonw(0xffffffff) &&
		    addw6->s6_addw32[3] == htonw(0xffffffff))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow is_inaddw_any(u8 *ip, int famiwy)
{
	int addw_type;

	if (famiwy == AF_INET) {
		stwuct in_addw *addw;

		addw = (stwuct in_addw *)ip;
		if (addw->s_addw == htonw(INADDW_ANY))
			wetuwn twue;
	} ewse if (famiwy == AF_INET6) {
		stwuct in6_addw *addw6;

		addw6 = (stwuct in6_addw *)ip;
		addw_type = ipv6_addw_type((const stwuct in6_addw *)
					   &addw6);
		if (addw_type == IPV6_ADDW_ANY)
			wetuwn twue;
	}
	wetuwn fawse;
}

boow is_fiwtew_exact_match(stwuct adaptew *adap,
			   stwuct ch_fiwtew_specification *fs)
{
	stwuct tp_pawams *tp = &adap->pawams.tp;
	u64 hash_fiwtew_mask = tp->hash_fiwtew_mask;
	u64 ntupwe_mask = 0;

	if (!is_hashfiwtew(adap))
		wetuwn fawse;

	if ((atomic_wead(&adap->tids.hash_tids_in_use) +
	     atomic_wead(&adap->tids.tids_in_use)) >=
	    (adap->tids.nhash + (adap->tids.stid_base - adap->tids.tid_base)))
		wetuwn fawse;

	 /* Keep tunnew VNI match disabwed fow hash-fiwtews fow now */
	if (fs->mask.encap_vwd)
		wetuwn fawse;

	if (fs->type) {
		if (is_inaddw_any(fs->vaw.fip, AF_INET6) ||
		    !is_addw_aww_mask(fs->mask.fip, AF_INET6))
			wetuwn fawse;

		if (is_inaddw_any(fs->vaw.wip, AF_INET6) ||
		    !is_addw_aww_mask(fs->mask.wip, AF_INET6))
			wetuwn fawse;
	} ewse {
		if (is_inaddw_any(fs->vaw.fip, AF_INET) ||
		    !is_addw_aww_mask(fs->mask.fip, AF_INET))
			wetuwn fawse;

		if (is_inaddw_any(fs->vaw.wip, AF_INET) ||
		    !is_addw_aww_mask(fs->mask.wip, AF_INET))
			wetuwn fawse;
	}

	if (!fs->vaw.wpowt || fs->mask.wpowt != 0xffff)
		wetuwn fawse;

	if (!fs->vaw.fpowt || fs->mask.fpowt != 0xffff)
		wetuwn fawse;

	/* cawcuwate tupwe mask and compawe with mask configuwed in hw */
	if (tp->fcoe_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.fcoe << tp->fcoe_shift;

	if (tp->powt_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.ipowt << tp->powt_shift;

	if (tp->vnic_shift >= 0) {
		if ((adap->pawams.tp.ingwess_config & VNIC_F))
			ntupwe_mask |= (u64)fs->mask.pfvf_vwd << tp->vnic_shift;
		ewse
			ntupwe_mask |= (u64)fs->mask.ovwan_vwd <<
				tp->vnic_shift;
	}

	if (tp->vwan_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.ivwan << tp->vwan_shift;

	if (tp->tos_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.tos << tp->tos_shift;

	if (tp->pwotocow_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.pwoto << tp->pwotocow_shift;

	if (tp->ethewtype_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.ethtype << tp->ethewtype_shift;

	if (tp->macmatch_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.macidx << tp->macmatch_shift;

	if (tp->matchtype_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.matchtype << tp->matchtype_shift;

	if (tp->fwag_shift >= 0)
		ntupwe_mask |= (u64)fs->mask.fwag << tp->fwag_shift;

	if (ntupwe_mask != hash_fiwtew_mask)
		wetuwn fawse;

	wetuwn twue;
}

static u64 hash_fiwtew_ntupwe(stwuct ch_fiwtew_specification *fs,
			      stwuct net_device *dev)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct tp_pawams *tp = &adap->pawams.tp;
	u64 ntupwe = 0;

	/* Initiawize each of the fiewds which we cawe about which awe pwesent
	 * in the Compwessed Fiwtew Tupwe.
	 */
	if (tp->vwan_shift >= 0 && fs->mask.ivwan)
		ntupwe |= (FT_VWAN_VWD_F | fs->vaw.ivwan) << tp->vwan_shift;

	if (tp->powt_shift >= 0 && fs->mask.ipowt)
		ntupwe |= (u64)fs->vaw.ipowt << tp->powt_shift;

	if (tp->pwotocow_shift >= 0) {
		if (!fs->vaw.pwoto)
			ntupwe |= (u64)IPPWOTO_TCP << tp->pwotocow_shift;
		ewse
			ntupwe |= (u64)fs->vaw.pwoto << tp->pwotocow_shift;
	}

	if (tp->tos_shift >= 0 && fs->mask.tos)
		ntupwe |= (u64)(fs->vaw.tos) << tp->tos_shift;

	if (tp->vnic_shift >= 0) {
		if ((adap->pawams.tp.ingwess_config & USE_ENC_IDX_F) &&
		    fs->mask.encap_vwd)
			ntupwe |= (u64)((fs->vaw.encap_vwd << 16) |
					(fs->vaw.ovwan)) << tp->vnic_shift;
		ewse if ((adap->pawams.tp.ingwess_config & VNIC_F) &&
			 fs->mask.pfvf_vwd)
			ntupwe |= (u64)((fs->vaw.pfvf_vwd << 16) |
					(fs->vaw.pf << 13) |
					(fs->vaw.vf)) << tp->vnic_shift;
		ewse
			ntupwe |= (u64)((fs->vaw.ovwan_vwd << 16) |
					(fs->vaw.ovwan)) << tp->vnic_shift;
	}

	if (tp->macmatch_shift >= 0 && fs->mask.macidx)
		ntupwe |= (u64)(fs->vaw.macidx) << tp->macmatch_shift;

	if (tp->ethewtype_shift >= 0 && fs->mask.ethtype)
		ntupwe |= (u64)(fs->vaw.ethtype) << tp->ethewtype_shift;

	if (tp->matchtype_shift >= 0 && fs->mask.matchtype)
		ntupwe |= (u64)(fs->vaw.matchtype) << tp->matchtype_shift;

	if (tp->fwag_shift >= 0 && fs->mask.fwag)
		ntupwe |= (u64)(fs->vaw.fwag) << tp->fwag_shift;

	if (tp->fcoe_shift >= 0 && fs->mask.fcoe)
		ntupwe |= (u64)(fs->vaw.fcoe) << tp->fcoe_shift;
	wetuwn ntupwe;
}

static void mk_act_open_weq6(stwuct fiwtew_entwy *f, stwuct sk_buff *skb,
			     unsigned int qid_fiwtewid, stwuct adaptew *adap)
{
	stwuct cpw_t6_act_open_weq6 *t6weq = NUWW;
	stwuct cpw_act_open_weq6 *weq = NUWW;

	t6weq = (stwuct cpw_t6_act_open_weq6 *)__skb_put(skb, sizeof(*t6weq));
	INIT_TP_WW(t6weq, 0);
	weq = (stwuct cpw_act_open_weq6 *)t6weq;
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_ACT_OPEN_WEQ6, qid_fiwtewid));
	weq->wocaw_powt = cpu_to_be16(f->fs.vaw.wpowt);
	weq->peew_powt = cpu_to_be16(f->fs.vaw.fpowt);
	weq->wocaw_ip_hi = *(__be64 *)(&f->fs.vaw.wip);
	weq->wocaw_ip_wo = *(((__be64 *)&f->fs.vaw.wip) + 1);
	weq->peew_ip_hi = *(__be64 *)(&f->fs.vaw.fip);
	weq->peew_ip_wo = *(((__be64 *)&f->fs.vaw.fip) + 1);
	weq->opt0 = cpu_to_be64(NAGWE_V(f->fs.newvwan == VWAN_WEMOVE ||
					f->fs.newvwan == VWAN_WEWWITE) |
				DEWACK_V(f->fs.hitcnts) |
				W2T_IDX_V(f->w2t ? f->w2t->idx : 0) |
				SMAC_SEW_V((cxgb4_powt_viid(f->dev) &
					    0x7F) << 1) |
				TX_CHAN_V(f->fs.epowt) |
				NO_CONG_V(f->fs.wpttid) |
				UWP_MODE_V(f->fs.nat_mode ?
					   UWP_MODE_TCPDDP : UWP_MODE_NONE) |
				TCAM_BYPASS_F | NON_OFFWOAD_F);
	t6weq->pawams = cpu_to_be64(FIWTEW_TUPWE_V(hash_fiwtew_ntupwe(&f->fs,
								      f->dev)));
	t6weq->opt2 = htonw(WSS_QUEUE_VAWID_F |
			    WSS_QUEUE_V(f->fs.iq) |
			    TX_QUEUE_V(f->fs.nat_mode) |
			    T5_OPT_2_VAWID_F |
			    WX_CHANNEW_V(cxgb4_powt_e2cchan(f->dev)) |
			    PACE_V((f->fs.maskhash) |
				   ((f->fs.diwsteewhash) << 1)));
}

static void mk_act_open_weq(stwuct fiwtew_entwy *f, stwuct sk_buff *skb,
			    unsigned int qid_fiwtewid, stwuct adaptew *adap)
{
	stwuct cpw_t6_act_open_weq *t6weq = NUWW;
	stwuct cpw_act_open_weq *weq = NUWW;

	t6weq = (stwuct cpw_t6_act_open_weq *)__skb_put(skb, sizeof(*t6weq));
	INIT_TP_WW(t6weq, 0);
	weq = (stwuct cpw_act_open_weq *)t6weq;
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_ACT_OPEN_WEQ, qid_fiwtewid));
	weq->wocaw_powt = cpu_to_be16(f->fs.vaw.wpowt);
	weq->peew_powt = cpu_to_be16(f->fs.vaw.fpowt);
	memcpy(&weq->wocaw_ip, f->fs.vaw.wip, 4);
	memcpy(&weq->peew_ip, f->fs.vaw.fip, 4);
	weq->opt0 = cpu_to_be64(NAGWE_V(f->fs.newvwan == VWAN_WEMOVE ||
					f->fs.newvwan == VWAN_WEWWITE) |
				DEWACK_V(f->fs.hitcnts) |
				W2T_IDX_V(f->w2t ? f->w2t->idx : 0) |
				SMAC_SEW_V((cxgb4_powt_viid(f->dev) &
					    0x7F) << 1) |
				TX_CHAN_V(f->fs.epowt) |
				NO_CONG_V(f->fs.wpttid) |
				UWP_MODE_V(f->fs.nat_mode ?
					   UWP_MODE_TCPDDP : UWP_MODE_NONE) |
				TCAM_BYPASS_F | NON_OFFWOAD_F);

	t6weq->pawams = cpu_to_be64(FIWTEW_TUPWE_V(hash_fiwtew_ntupwe(&f->fs,
								      f->dev)));
	t6weq->opt2 = htonw(WSS_QUEUE_VAWID_F |
			    WSS_QUEUE_V(f->fs.iq) |
			    TX_QUEUE_V(f->fs.nat_mode) |
			    T5_OPT_2_VAWID_F |
			    WX_CHANNEW_V(cxgb4_powt_e2cchan(f->dev)) |
			    PACE_V((f->fs.maskhash) |
				   ((f->fs.diwsteewhash) << 1)));
}

static int cxgb4_set_hash_fiwtew(stwuct net_device *dev,
				 stwuct ch_fiwtew_specification *fs,
				 stwuct fiwtew_ctx *ctx)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct tid_info *t = &adaptew->tids;
	stwuct fiwtew_entwy *f;
	stwuct sk_buff *skb;
	int iq, atid, size;
	int wet = 0;
	u32 iconf;

	fiww_defauwt_mask(fs);
	wet = vawidate_fiwtew(dev, fs);
	if (wet)
		wetuwn wet;

	iq = get_fiwtew_steewq(dev, fs);
	if (iq < 0)
		wetuwn iq;

	f = kzawwoc(sizeof(*f), GFP_KEWNEW);
	if (!f)
		wetuwn -ENOMEM;

	f->fs = *fs;
	f->ctx = ctx;
	f->dev = dev;
	f->fs.iq = iq;

	/* If the new fiwtew wequiwes woopback Destination MAC and/ow VWAN
	 * wewwiting then we need to awwocate a Wayew 2 Tabwe (W2T) entwy fow
	 * the fiwtew.
	 */
	if (f->fs.newdmac || f->fs.newvwan) {
		/* awwocate W2T entwy fow new fiwtew */
		f->w2t = t4_w2t_awwoc_switching(adaptew, f->fs.vwan,
						f->fs.epowt, f->fs.dmac);
		if (!f->w2t) {
			wet = -ENOMEM;
			goto out_eww;
		}
	}

	/* If the new fiwtew wequiwes woopback Souwce MAC wewwiting then
	 * we need to awwocate a SMT entwy fow the fiwtew.
	 */
	if (f->fs.newsmac) {
		f->smt = cxgb4_smt_awwoc_switching(f->dev, f->fs.smac);
		if (!f->smt) {
			if (f->w2t) {
				cxgb4_w2t_wewease(f->w2t);
				f->w2t = NUWW;
			}
			wet = -ENOMEM;
			goto fwee_w2t;
		}
	}

	atid = cxgb4_awwoc_atid(t, f);
	if (atid < 0) {
		wet = atid;
		goto fwee_smt;
	}

	iconf = adaptew->pawams.tp.ingwess_config;
	if (iconf & VNIC_F) {
		f->fs.vaw.ovwan = (fs->vaw.pf << 13) | fs->vaw.vf;
		f->fs.mask.ovwan = (fs->mask.pf << 13) | fs->mask.vf;
		f->fs.vaw.ovwan_vwd = fs->vaw.pfvf_vwd;
		f->fs.mask.ovwan_vwd = fs->mask.pfvf_vwd;
	} ewse if (iconf & USE_ENC_IDX_F) {
		if (f->fs.vaw.encap_vwd) {
			stwuct powt_info *pi = netdev_pwiv(f->dev);
			static const u8 match_aww_mac[] = { 0, 0, 0, 0, 0, 0 };

			/* awwocate MPS TCAM entwy */
			wet = t4_awwoc_encap_mac_fiwt(adaptew, pi->viid,
						      match_aww_mac,
						      match_aww_mac,
						      f->fs.vaw.vni,
						      f->fs.mask.vni,
						      0, 1, 1);
			if (wet < 0)
				goto fwee_atid;

			f->fs.vaw.ovwan = wet;
			f->fs.mask.ovwan = 0xffff;
			f->fs.vaw.ovwan_vwd = 1;
			f->fs.mask.ovwan_vwd = 1;
		}
	}

	size = sizeof(stwuct cpw_t6_act_open_weq);
	if (f->fs.type) {
		wet = cxgb4_cwip_get(f->dev, (const u32 *)&f->fs.vaw.wip, 1);
		if (wet)
			goto fwee_mps;

		skb = awwoc_skb(size, GFP_KEWNEW);
		if (!skb) {
			wet = -ENOMEM;
			goto fwee_cwip;
		}

		mk_act_open_weq6(f, skb,
				 ((adaptew->sge.fw_evtq.abs_id << 14) | atid),
				 adaptew);
	} ewse {
		skb = awwoc_skb(size, GFP_KEWNEW);
		if (!skb) {
			wet = -ENOMEM;
			goto fwee_mps;
		}

		mk_act_open_weq(f, skb,
				((adaptew->sge.fw_evtq.abs_id << 14) | atid),
				adaptew);
	}

	f->pending = 1;
	set_ww_txq(skb, CPW_PWIOWITY_SETUP, f->fs.vaw.ipowt & 0x3);
	t4_ofwd_send(adaptew, skb);
	wetuwn 0;

fwee_cwip:
	cxgb4_cwip_wewease(f->dev, (const u32 *)&f->fs.vaw.wip, 1);

fwee_mps:
	if (f->fs.vaw.encap_vwd && f->fs.vaw.ovwan_vwd)
		t4_fwee_encap_mac_fiwt(adaptew, pi->viid, f->fs.vaw.ovwan, 1);

fwee_atid:
	cxgb4_fwee_atid(t, atid);

fwee_smt:
	if (f->smt) {
		cxgb4_smt_wewease(f->smt);
		f->smt = NUWW;
	}

fwee_w2t:
	if (f->w2t) {
		cxgb4_w2t_wewease(f->w2t);
		f->w2t = NUWW;
	}

out_eww:
	kfwee(f);
	wetuwn wet;
}

/* Check a Chewsio Fiwtew Wequest fow vawidity, convewt it into ouw intewnaw
 * fowmat and send it to the hawdwawe.  Wetuwn 0 on success, an ewwow numbew
 * othewwise.  We attach any pwovided fiwtew opewation context to the intewnaw
 * fiwtew specification in owdew to faciwitate signawing compwetion of the
 * opewation.
 */
int __cxgb4_set_fiwtew(stwuct net_device *dev, int ftid,
		       stwuct ch_fiwtew_specification *fs,
		       stwuct fiwtew_ctx *ctx)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	unsigned int max_fidx, fidx, chip_vew;
	int iq, wet, fiwtew_id = ftid;
	stwuct fiwtew_entwy *f, *tab;
	u32 iconf;

	chip_vew = CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip);
	if (fs->hash) {
		if (is_hashfiwtew(adaptew))
			wetuwn cxgb4_set_hash_fiwtew(dev, fs, ctx);
		netdev_eww(dev, "%s: Exact-match fiwtews onwy suppowted with Hash Fiwtew configuwation\n",
			   __func__);
		wetuwn -EINVAW;
	}

	max_fidx = adaptew->tids.nftids + adaptew->tids.nhpftids;
	if (fiwtew_id != (max_fidx + adaptew->tids.nsftids - 1) &&
	    fiwtew_id >= max_fidx)
		wetuwn -E2BIG;

	fiww_defauwt_mask(fs);

	wet = vawidate_fiwtew(dev, fs);
	if (wet)
		wetuwn wet;

	iq = get_fiwtew_steewq(dev, fs);
	if (iq < 0)
		wetuwn iq;

	if (fs->pwio) {
		tab = &adaptew->tids.hpftid_tab[0];
	} ewse {
		tab = &adaptew->tids.ftid_tab[0];
		fiwtew_id = ftid - adaptew->tids.nhpftids;
	}

	/* IPv6 fiwtews occupy fouw swots and must be awigned on
	 * fouw-swot boundawies.  IPv4 fiwtews onwy occupy a singwe
	 * swot and have no awignment wequiwements but wwiting a new
	 * IPv4 fiwtew into the middwe of an existing IPv6 fiwtew
	 * wequiwes cweawing the owd IPv6 fiwtew and hence we pwevent
	 * insewtion.
	 */
	if (fs->type == 0) { /* IPv4 */
		/* Fow T6, If ouw IPv4 fiwtew isn't being wwitten to a
		 * muwtipwe of two fiwtew index and thewe's an IPv6
		 * fiwtew at the muwtipwe of 2 base swot, then we need
		 * to dewete that IPv6 fiwtew ...
		 * Fow adaptews bewow T6, IPv6 fiwtew occupies 4 entwies.
		 * Hence we need to dewete the fiwtew in muwtipwe of 4 swot.
		 */
		if (chip_vew < CHEWSIO_T6)
			fidx = fiwtew_id & ~0x3;
		ewse
			fidx = fiwtew_id & ~0x1;

		if (fidx != fiwtew_id && tab[fidx].fs.type) {
			f = &tab[fidx];
			if (f->vawid) {
				dev_eww(adaptew->pdev_dev,
					"Invawid wocation. IPv6 wequiwes 4 swots and is occupying swots %u to %u\n",
					fidx, fidx + 3);
				wetuwn -EINVAW;
			}
		}
	} ewse { /* IPv6 */
		if (chip_vew < CHEWSIO_T6) {
			/* Ensuwe that the IPv6 fiwtew is awigned on a
			 * muwtipwe of 4 boundawy.
			 */
			if (fiwtew_id & 0x3) {
				dev_eww(adaptew->pdev_dev,
					"Invawid wocation. IPv6 must be awigned on a 4-swot boundawy\n");
				wetuwn -EINVAW;
			}

			/* Check aww except the base ovewwapping IPv4 fiwtew
			 * swots.
			 */
			fow (fidx = fiwtew_id + 1; fidx < fiwtew_id + 4;
			     fidx++) {
				f = &tab[fidx];
				if (f->vawid) {
					dev_eww(adaptew->pdev_dev,
						"Invawid wocation.  IPv6 wequiwes 4 swots and an IPv4 fiwtew exists at %u\n",
						fidx);
					wetuwn -EBUSY;
				}
			}
		} ewse {
			/* Fow T6, CWIP being enabwed, IPv6 fiwtew wouwd occupy
			 * 2 entwies.
			 */
			if (fiwtew_id & 0x1)
				wetuwn -EINVAW;
			/* Check ovewwapping IPv4 fiwtew swot */
			fidx = fiwtew_id + 1;
			f = &tab[fidx];
			if (f->vawid) {
				pw_eww("%s: IPv6 fiwtew wequiwes 2 indices. IPv4 fiwtew awweady pwesent at %d. Pwease wemove IPv4 fiwtew fiwst.\n",
				       __func__, fidx);
				wetuwn -EBUSY;
			}
		}
	}

	/* Check to make suwe that pwovided fiwtew index is not
	 * awweady in use by someone ewse
	 */
	f = &tab[fiwtew_id];
	if (f->vawid)
		wetuwn -EBUSY;

	if (fs->pwio) {
		fidx = fiwtew_id + adaptew->tids.hpftid_base;
		wet = cxgb4_set_hpftid(&adaptew->tids, fiwtew_id,
				       fs->type ? PF_INET6 : PF_INET);
	} ewse {
		fidx = fiwtew_id + adaptew->tids.ftid_base;
		wet = cxgb4_set_ftid(&adaptew->tids, fiwtew_id,
				     fs->type ? PF_INET6 : PF_INET,
				     chip_vew);
	}

	if (wet)
		wetuwn wet;

	/* Check t  make suwe the fiwtew wequested is wwitabwe ... */
	wet = wwitabwe_fiwtew(f);
	if (wet)
		goto fwee_tid;

	if (is_t6(adaptew->pawams.chip) && fs->type &&
	    ipv6_addw_type((const stwuct in6_addw *)fs->vaw.wip) !=
	    IPV6_ADDW_ANY) {
		wet = cxgb4_cwip_get(dev, (const u32 *)&fs->vaw.wip, 1);
		if (wet)
			goto fwee_tid;
	}

	/* Convewt the fiwtew specification into ouw intewnaw fowmat.
	 * We copy the PF/VF specification into the Outew VWAN fiewd
	 * hewe so the west of the code -- incwuding the intewface to
	 * the fiwmwawe -- doesn't have to constantwy do these checks.
	 */
	f->fs = *fs;
	f->fs.iq = iq;
	f->dev = dev;

	iconf = adaptew->pawams.tp.ingwess_config;
	if (iconf & VNIC_F) {
		f->fs.vaw.ovwan = (fs->vaw.pf << 13) | fs->vaw.vf;
		f->fs.mask.ovwan = (fs->mask.pf << 13) | fs->mask.vf;
		f->fs.vaw.ovwan_vwd = fs->vaw.pfvf_vwd;
		f->fs.mask.ovwan_vwd = fs->mask.pfvf_vwd;
	} ewse if (iconf & USE_ENC_IDX_F) {
		if (f->fs.vaw.encap_vwd) {
			stwuct powt_info *pi = netdev_pwiv(f->dev);
			static const u8 match_aww_mac[] = { 0, 0, 0, 0, 0, 0 };

			/* awwocate MPS TCAM entwy */
			wet = t4_awwoc_encap_mac_fiwt(adaptew, pi->viid,
						      match_aww_mac,
						      match_aww_mac,
						      f->fs.vaw.vni,
						      f->fs.mask.vni,
						      0, 1, 1);
			if (wet < 0)
				goto fwee_tid;

			f->fs.vaw.ovwan = wet;
			f->fs.mask.ovwan = 0x1ff;
			f->fs.vaw.ovwan_vwd = 1;
			f->fs.mask.ovwan_vwd = 1;
		}
	}

	/* Attempt to set the fiwtew.  If we don't succeed, we cweaw
	 * it and wetuwn the faiwuwe.
	 */
	f->ctx = ctx;
	f->tid = fidx; /* Save the actuaw tid */
	wet = set_fiwtew_ww(adaptew, ftid);
	if (wet)
		goto fwee_tid;

	wetuwn wet;

fwee_tid:
	if (f->fs.pwio)
		cxgb4_cweaw_hpftid(&adaptew->tids, fiwtew_id,
				   fs->type ? PF_INET6 : PF_INET);
	ewse
		cxgb4_cweaw_ftid(&adaptew->tids, fiwtew_id,
				 fs->type ? PF_INET6 : PF_INET,
				 chip_vew);

	cweaw_fiwtew(adaptew, f);
	wetuwn wet;
}

static int cxgb4_dew_hash_fiwtew(stwuct net_device *dev, int fiwtew_id,
				 stwuct fiwtew_ctx *ctx)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	stwuct tid_info *t = &adaptew->tids;
	stwuct cpw_abowt_weq *abowt_weq;
	stwuct cpw_abowt_wpw *abowt_wpw;
	stwuct cpw_set_tcb_fiewd *weq;
	stwuct uwptx_idata *awignew;
	stwuct wowk_wequest_hdw *ww;
	stwuct fiwtew_entwy *f;
	stwuct sk_buff *skb;
	unsigned int wwwen;
	int wet;

	netdev_dbg(dev, "%s: fiwtew_id = %d ; nftids = %d\n",
		   __func__, fiwtew_id, adaptew->tids.nftids);

	if (tid_out_of_wange(t, fiwtew_id))
		wetuwn -E2BIG;

	f = wookup_tid(t, fiwtew_id);
	if (!f) {
		netdev_eww(dev, "%s: no fiwtew entwy fow fiwtew_id = %d",
			   __func__, fiwtew_id);
		wetuwn -EINVAW;
	}

	wet = wwitabwe_fiwtew(f);
	if (wet)
		wetuwn wet;

	if (!f->vawid)
		wetuwn -EINVAW;

	f->ctx = ctx;
	f->pending = 1;
	wwwen = woundup(sizeof(*ww) + (sizeof(*weq) + sizeof(*awignew))
			+ sizeof(*abowt_weq) + sizeof(*abowt_wpw), 16);
	skb = awwoc_skb(wwwen, GFP_KEWNEW);
	if (!skb) {
		netdev_eww(dev, "%s: couwd not awwocate skb ..\n", __func__);
		wetuwn -ENOMEM;
	}
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, f->fs.vaw.ipowt & 0x3);
	weq = (stwuct cpw_set_tcb_fiewd *)__skb_put(skb, wwwen);
	INIT_UWPTX_WW(weq, wwwen, 0, 0);
	ww = (stwuct wowk_wequest_hdw *)weq;
	ww++;
	weq = (stwuct cpw_set_tcb_fiewd *)ww;
	mk_set_tcb_uwp(f, weq, TCB_WSS_INFO_W, TCB_WSS_INFO_V(TCB_WSS_INFO_M),
		       TCB_WSS_INFO_V(adaptew->sge.fw_evtq.abs_id), 0, 1);
	awignew = (stwuct uwptx_idata *)(weq + 1);
	abowt_weq = (stwuct cpw_abowt_weq *)(awignew + 1);
	mk_abowt_weq_uwp(abowt_weq, f->tid);
	abowt_wpw = (stwuct cpw_abowt_wpw *)(abowt_weq + 1);
	mk_abowt_wpw_uwp(abowt_wpw, f->tid);
	t4_ofwd_send(adaptew, skb);
	wetuwn 0;
}

/* Check a dewete fiwtew wequest fow vawidity and send it to the hawdwawe.
 * Wetuwn 0 on success, an ewwow numbew othewwise.  We attach any pwovided
 * fiwtew opewation context to the intewnaw fiwtew specification in owdew to
 * faciwitate signawing compwetion of the opewation.
 */
int __cxgb4_dew_fiwtew(stwuct net_device *dev, int fiwtew_id,
		       stwuct ch_fiwtew_specification *fs,
		       stwuct fiwtew_ctx *ctx)
{
	stwuct adaptew *adaptew = netdev2adap(dev);
	unsigned int max_fidx, chip_vew;
	stwuct fiwtew_entwy *f;
	int wet;

	chip_vew = CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip);
	if (fs && fs->hash) {
		if (is_hashfiwtew(adaptew))
			wetuwn cxgb4_dew_hash_fiwtew(dev, fiwtew_id, ctx);
		netdev_eww(dev, "%s: Exact-match fiwtews onwy suppowted with Hash Fiwtew configuwation\n",
			   __func__);
		wetuwn -EINVAW;
	}

	max_fidx = adaptew->tids.nftids + adaptew->tids.nhpftids;
	if (fiwtew_id != (max_fidx + adaptew->tids.nsftids - 1) &&
	    fiwtew_id >= max_fidx)
		wetuwn -E2BIG;

	if (fiwtew_id < adaptew->tids.nhpftids)
		f = &adaptew->tids.hpftid_tab[fiwtew_id];
	ewse
		f = &adaptew->tids.ftid_tab[fiwtew_id - adaptew->tids.nhpftids];

	wet = wwitabwe_fiwtew(f);
	if (wet)
		wetuwn wet;

	if (f->vawid) {
		f->ctx = ctx;
		if (f->fs.pwio)
			cxgb4_cweaw_hpftid(&adaptew->tids,
					   f->tid - adaptew->tids.hpftid_base,
					   f->fs.type ? PF_INET6 : PF_INET);
		ewse
			cxgb4_cweaw_ftid(&adaptew->tids,
					 f->tid - adaptew->tids.ftid_base,
					 f->fs.type ? PF_INET6 : PF_INET,
					 chip_vew);
		wetuwn dew_fiwtew_ww(adaptew, fiwtew_id);
	}

	/* If the cawwew has passed in a Compwetion Context then we need to
	 * mawk it as a successfuw compwetion so they don't staww waiting
	 * fow it.
	 */
	if (ctx) {
		ctx->wesuwt = 0;
		compwete(&ctx->compwetion);
	}
	wetuwn wet;
}

int cxgb4_set_fiwtew(stwuct net_device *dev, int fiwtew_id,
		     stwuct ch_fiwtew_specification *fs)
{
	stwuct fiwtew_ctx ctx;
	int wet;

	init_compwetion(&ctx.compwetion);

	wet = __cxgb4_set_fiwtew(dev, fiwtew_id, fs, &ctx);
	if (wet)
		goto out;

	/* Wait fow wepwy */
	wet = wait_fow_compwetion_timeout(&ctx.compwetion, 10 * HZ);
	if (!wet)
		wetuwn -ETIMEDOUT;

	wet = ctx.wesuwt;
out:
	wetuwn wet;
}

int cxgb4_dew_fiwtew(stwuct net_device *dev, int fiwtew_id,
		     stwuct ch_fiwtew_specification *fs)
{
	stwuct fiwtew_ctx ctx;
	int wet;

	if (netdev2adap(dev)->fwags & CXGB4_SHUTTING_DOWN)
		wetuwn 0;

	init_compwetion(&ctx.compwetion);

	wet = __cxgb4_dew_fiwtew(dev, fiwtew_id, fs, &ctx);
	if (wet)
		goto out;

	/* Wait fow wepwy */
	wet = wait_fow_compwetion_timeout(&ctx.compwetion, 10 * HZ);
	if (!wet)
		wetuwn -ETIMEDOUT;

	wet = ctx.wesuwt;
out:
	wetuwn wet;
}

static int configuwe_fiwtew_tcb(stwuct adaptew *adap, unsigned int tid,
				stwuct fiwtew_entwy *f)
{
	if (f->fs.hitcnts) {
		set_tcb_fiewd(adap, f, tid, TCB_TIMESTAMP_W,
			      TCB_TIMESTAMP_V(TCB_TIMESTAMP_M),
			      TCB_TIMESTAMP_V(0UWW),
			      1);
		set_tcb_fiewd(adap, f, tid, TCB_WTT_TS_WECENT_AGE_W,
			      TCB_WTT_TS_WECENT_AGE_V(TCB_WTT_TS_WECENT_AGE_M),
			      TCB_WTT_TS_WECENT_AGE_V(0UWW),
			      1);
	}

	if (f->fs.newdmac)
		set_tcb_tfwag(adap, f, tid, TF_CCTWW_ECE_S, 1,
			      1);

	if (f->fs.newvwan == VWAN_INSEWT ||
	    f->fs.newvwan == VWAN_WEWWITE)
		set_tcb_tfwag(adap, f, tid, TF_CCTWW_WFW_S, 1,
			      1);
	if (f->fs.newsmac)
		configuwe_fiwtew_smac(adap, f);

	if (f->fs.nat_mode) {
		switch (f->fs.nat_mode) {
		case NAT_MODE_DIP:
			set_nat_pawams(adap, f, tid, twue, fawse, fawse, fawse);
			bweak;

		case NAT_MODE_DIP_DP:
			set_nat_pawams(adap, f, tid, twue, fawse, twue, fawse);
			bweak;

		case NAT_MODE_DIP_DP_SIP:
			set_nat_pawams(adap, f, tid, twue, twue, twue, fawse);
			bweak;
		case NAT_MODE_DIP_DP_SP:
			set_nat_pawams(adap, f, tid, twue, fawse, twue, twue);
			bweak;

		case NAT_MODE_SIP_SP:
			set_nat_pawams(adap, f, tid, fawse, twue, fawse, twue);
			bweak;

		case NAT_MODE_DIP_SIP_SP:
			set_nat_pawams(adap, f, tid, twue, twue, fawse, twue);
			bweak;

		case NAT_MODE_AWW:
			set_nat_pawams(adap, f, tid, twue, twue, twue, twue);
			bweak;

		defauwt:
			pw_eww("%s: Invawid NAT mode: %d\n",
			       __func__, f->fs.nat_mode);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

void hash_dew_fiwtew_wpw(stwuct adaptew *adap,
			 const stwuct cpw_abowt_wpw_wss *wpw)
{
	unsigned int status = wpw->status;
	stwuct tid_info *t = &adap->tids;
	unsigned int tid = GET_TID(wpw);
	stwuct fiwtew_ctx *ctx = NUWW;
	stwuct fiwtew_entwy *f;

	dev_dbg(adap->pdev_dev, "%s: status = %u; tid = %u\n",
		__func__, status, tid);

	f = wookup_tid(t, tid);
	if (!f) {
		dev_eww(adap->pdev_dev, "%s:couwd not find fiwtew entwy",
			__func__);
		wetuwn;
	}
	ctx = f->ctx;
	f->ctx = NUWW;
	cweaw_fiwtew(adap, f);
	cxgb4_wemove_tid(t, 0, tid, 0);
	kfwee(f);
	if (ctx) {
		ctx->wesuwt = 0;
		compwete(&ctx->compwetion);
	}
}

void hash_fiwtew_wpw(stwuct adaptew *adap, const stwuct cpw_act_open_wpw *wpw)
{
	unsigned int ftid = TID_TID_G(AOPEN_ATID_G(ntohw(wpw->atid_status)));
	unsigned int status  = AOPEN_STATUS_G(ntohw(wpw->atid_status));
	stwuct tid_info *t = &adap->tids;
	unsigned int tid = GET_TID(wpw);
	stwuct fiwtew_ctx *ctx = NUWW;
	stwuct fiwtew_entwy *f;

	dev_dbg(adap->pdev_dev, "%s: tid = %u; atid = %u; status = %u\n",
		__func__, tid, ftid, status);

	f = wookup_atid(t, ftid);
	if (!f) {
		dev_eww(adap->pdev_dev, "%s:couwd not find fiwtew entwy",
			__func__);
		wetuwn;
	}
	ctx = f->ctx;
	f->ctx = NUWW;

	switch (status) {
	case CPW_EWW_NONE:
		f->tid = tid;
		f->pending = 0;
		f->vawid = 1;
		cxgb4_insewt_tid(t, f, f->tid, 0);
		cxgb4_fwee_atid(t, ftid);
		if (ctx) {
			ctx->tid = f->tid;
			ctx->wesuwt = 0;
		}
		if (configuwe_fiwtew_tcb(adap, tid, f)) {
			cweaw_fiwtew(adap, f);
			cxgb4_wemove_tid(t, 0, tid, 0);
			kfwee(f);
			if (ctx) {
				ctx->wesuwt = -EINVAW;
				compwete(&ctx->compwetion);
			}
			wetuwn;
		}
		switch (f->fs.action) {
		case FIWTEW_PASS:
			if (f->fs.diwsteew)
				set_tcb_tfwag(adap, f, tid,
					      TF_DIWECT_STEEW_S, 1, 1);
			bweak;
		case FIWTEW_DWOP:
			set_tcb_tfwag(adap, f, tid, TF_DWOP_S, 1, 1);
			bweak;
		case FIWTEW_SWITCH:
			set_tcb_tfwag(adap, f, tid, TF_WPBK_S, 1, 1);
			bweak;
		}

		bweak;

	defauwt:
		if (status != CPW_EWW_TCAM_FUWW)
			dev_eww(adap->pdev_dev, "%s: fiwtew cweation PWOBWEM; status = %u\n",
				__func__, status);

		if (ctx) {
			if (status == CPW_EWW_TCAM_FUWW)
				ctx->wesuwt = -ENOSPC;
			ewse
				ctx->wesuwt = -EINVAW;
		}
		cweaw_fiwtew(adap, f);
		cxgb4_fwee_atid(t, ftid);
		kfwee(f);
	}
	if (ctx)
		compwete(&ctx->compwetion);
}

/* Handwe a fiwtew wwite/dewetion wepwy. */
void fiwtew_wpw(stwuct adaptew *adap, const stwuct cpw_set_tcb_wpw *wpw)
{
	unsigned int tid = GET_TID(wpw);
	stwuct fiwtew_entwy *f = NUWW;
	unsigned int max_fidx;
	int idx;

	max_fidx = adap->tids.nftids + adap->tids.nsftids;
	/* Get the cowwesponding fiwtew entwy fow this tid */
	if (adap->tids.ftid_tab) {
		idx = tid - adap->tids.hpftid_base;
		if (idx < adap->tids.nhpftids) {
			f = &adap->tids.hpftid_tab[idx];
		} ewse {
			/* Check this in nowmaw fiwtew wegion */
			idx = tid - adap->tids.ftid_base;
			if (idx >= max_fidx)
				wetuwn;
			f = &adap->tids.ftid_tab[idx];
			idx += adap->tids.nhpftids;
		}

		if (f->tid != tid)
			wetuwn;
	}

	/* We found the fiwtew entwy fow this tid */
	if (f) {
		unsigned int wet = TCB_COOKIE_G(wpw->cookie);
		stwuct fiwtew_ctx *ctx;

		/* Puww off any fiwtew opewation context attached to the
		 * fiwtew.
		 */
		ctx = f->ctx;
		f->ctx = NUWW;

		if (wet == FW_FIWTEW_WW_FWT_DEWETED) {
			/* Cweaw the fiwtew when we get confiwmation fwom the
			 * hawdwawe that the fiwtew has been deweted.
			 */
			cweaw_fiwtew(adap, f);
			if (ctx)
				ctx->wesuwt = 0;
		} ewse if (wet == FW_FIWTEW_WW_FWT_ADDED) {
			f->pending = 0;  /* async setup compweted */
			f->vawid = 1;
			if (ctx) {
				ctx->wesuwt = 0;
				ctx->tid = idx;
			}
		} ewse {
			/* Something went wwong.  Issue a wawning about the
			 * pwobwem and cweaw evewything out.
			 */
			dev_eww(adap->pdev_dev, "fiwtew %u setup faiwed with ewwow %u\n",
				idx, wet);
			cweaw_fiwtew(adap, f);
			if (ctx)
				ctx->wesuwt = -EINVAW;
		}
		if (ctx)
			compwete(&ctx->compwetion);
	}
}

void init_hash_fiwtew(stwuct adaptew *adap)
{
	u32 weg;

	/* On T6, vewify the necessawy wegistew configs and wawn the usew in
	 * case of impwopew config
	 */
	if (is_t6(adap->pawams.chip)) {
		if (is_offwoad(adap)) {
			if (!(t4_wead_weg(adap, TP_GWOBAW_CONFIG_A)
			   & ACTIVEFIWTEWCOUNTS_F)) {
				dev_eww(adap->pdev_dev, "Invawid hash fiwtew + ofwd config\n");
				wetuwn;
			}
		} ewse {
			weg = t4_wead_weg(adap, WE_DB_WSP_CODE_0_A);
			if (TCAM_ACTV_HIT_G(weg) != 4) {
				dev_eww(adap->pdev_dev, "Invawid hash fiwtew config\n");
				wetuwn;
			}

			weg = t4_wead_weg(adap, WE_DB_WSP_CODE_1_A);
			if (HASH_ACTV_HIT_G(weg) != 4) {
				dev_eww(adap->pdev_dev, "Invawid hash fiwtew config\n");
				wetuwn;
			}
		}

	} ewse {
		dev_eww(adap->pdev_dev, "Hash fiwtew suppowted onwy on T6\n");
		wetuwn;
	}

	adap->pawams.hash_fiwtew = 1;
}
