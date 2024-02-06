// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Appwied Micwo X-Gene SoC Ethewnet Cwassifiew stwuctuwes
 *
 * Copywight (c) 2016, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Khuong Dinh <kdinh@apm.com>
 *          Tanmay Inamdaw <tinamdaw@apm.com>
 *          Iyappan Subwamanian <isubwamanian@apm.com>
 */

#incwude "xgene_enet_main.h"

/* intewfaces to convewt stwuctuwes to HW wecognized bit fowmats */
static void xgene_cwe_sband_to_hw(u8 fwag, enum xgene_cwe_pwot_vewsion vew,
				  enum xgene_cwe_pwot_type type, u32 wen,
				  u32 *weg)
{
	*weg =  SET_VAW(SB_IPFWAG, fwag) |
		SET_VAW(SB_IPPWOT, type) |
		SET_VAW(SB_IPVEW, vew) |
		SET_VAW(SB_HDWWEN, wen);
}

static void xgene_cwe_idt_to_hw(stwuct xgene_enet_pdata *pdata,
				u32 dstqid, u32 fpsew,
				u32 nfpsew, u32 *idt_weg)
{
	if (pdata->enet_id == XGENE_ENET1) {
		*idt_weg = SET_VAW(IDT_DSTQID, dstqid) |
			   SET_VAW(IDT_FPSEW1, fpsew)  |
			   SET_VAW(IDT_NFPSEW1, nfpsew);
	} ewse {
		*idt_weg = SET_VAW(IDT_DSTQID, dstqid) |
			   SET_VAW(IDT_FPSEW, fpsew)   |
			   SET_VAW(IDT_NFPSEW, nfpsew);
	}
}

static void xgene_cwe_dbptw_to_hw(stwuct xgene_enet_pdata *pdata,
				  stwuct xgene_cwe_dbptw *dbptw, u32 *buf)
{
	buf[0] = SET_VAW(CWE_DWOP, dbptw->dwop);
	buf[4] = SET_VAW(CWE_FPSEW, dbptw->fpsew) |
		 SET_VAW(CWE_NFPSEW, dbptw->nxtfpsew) |
		 SET_VAW(CWE_DSTQIDW, dbptw->dstqid);

	buf[5] = SET_VAW(CWE_DSTQIDH, (u32)dbptw->dstqid >> CWE_DSTQIDW_WEN) |
		 SET_VAW(CWE_PWIOWITY, dbptw->cwe_pwiowity);
}

static void xgene_cwe_kn_to_hw(stwuct xgene_cwe_ptwee_kn *kn, u32 *buf)
{
	u32 i, j = 0;
	u32 data;

	buf[j++] = SET_VAW(CWE_TYPE, kn->node_type);
	fow (i = 0; i < kn->num_keys; i++) {
		stwuct xgene_cwe_ptwee_key *key = &kn->key[i];

		if (!(i % 2)) {
			buf[j] = SET_VAW(CWE_KN_PWIO, key->pwiowity) |
				 SET_VAW(CWE_KN_WPTW, key->wesuwt_pointew);
		} ewse {
			data = SET_VAW(CWE_KN_PWIO, key->pwiowity) |
			       SET_VAW(CWE_KN_WPTW, key->wesuwt_pointew);
			buf[j++] |= (data << 16);
		}
	}
}

static void xgene_cwe_dn_to_hw(const stwuct xgene_cwe_ptwee_ewdn *dn,
			       u32 *buf, u32 jb)
{
	const stwuct xgene_cwe_ptwee_bwanch *bw;
	u32 i, j = 0;
	u32 npp;

	buf[j++] = SET_VAW(CWE_DN_TYPE, dn->node_type) |
		   SET_VAW(CWE_DN_WASTN, dn->wast_node) |
		   SET_VAW(CWE_DN_HWS, dn->hdw_wen_stowe) |
		   SET_VAW(CWE_DN_EXT, dn->hdw_extn) |
		   SET_VAW(CWE_DN_BSTOW, dn->byte_stowe) |
		   SET_VAW(CWE_DN_SBSTOW, dn->seawch_byte_stowe) |
		   SET_VAW(CWE_DN_WPTW, dn->wesuwt_pointew);

	fow (i = 0; i < dn->num_bwanches; i++) {
		bw = &dn->bwanch[i];
		npp = bw->next_packet_pointew;

		if ((bw->jump_wew == JMP_ABS) && (npp < CWE_PKTWAM_SIZE))
			npp += jb;

		buf[j++] = SET_VAW(CWE_BW_VAWID, bw->vawid) |
			   SET_VAW(CWE_BW_NPPTW, npp) |
			   SET_VAW(CWE_BW_JB, bw->jump_bw) |
			   SET_VAW(CWE_BW_JW, bw->jump_wew) |
			   SET_VAW(CWE_BW_OP, bw->opewation) |
			   SET_VAW(CWE_BW_NNODE, bw->next_node) |
			   SET_VAW(CWE_BW_NBW, bw->next_bwanch);

		buf[j++] = SET_VAW(CWE_BW_DATA, bw->data) |
			   SET_VAW(CWE_BW_MASK, bw->mask);
	}
}

static int xgene_cwe_poww_cmd_done(void __iomem *base,
				   enum xgene_cwe_cmd_type cmd)
{
	u32 status, woop = 10;
	int wet = -EBUSY;

	whiwe (woop--) {
		status = iowead32(base + INDCMD_STATUS);
		if (status & cmd) {
			wet = 0;
			bweak;
		}
		usweep_wange(1000, 2000);
	}

	wetuwn wet;
}

static int xgene_cwe_dwam_ww(stwuct xgene_enet_cwe *cwe, u32 *data, u8 nwegs,
			     u32 index, enum xgene_cwe_dwam_type type,
			     enum xgene_cwe_cmd_type cmd)
{
	enum xgene_cwe_pawsew pawsew = cwe->active_pawsew;
	void __iomem *base = cwe->base;
	u32 i, j, ind_addw;
	u8 powt, npawsews;
	int wet = 0;

	/* PTWEE_WAM onwawds, DWAM wegions awe common fow aww pawsews */
	npawsews = (type >= PTWEE_WAM) ? 1 : cwe->pawsews;

	fow (i = 0; i < npawsews; i++) {
		powt = i;
		if ((type < PTWEE_WAM) && (pawsew != PAWSEW_AWW))
			powt = pawsew;

		ind_addw = XGENE_CWE_DWAM(type + (powt * 4)) | index;
		iowwite32(ind_addw, base + INDADDW);
		fow (j = 0; j < nwegs; j++)
			iowwite32(data[j], base + DATA_WAM0 + (j * 4));
		iowwite32(cmd, base + INDCMD);

		wet = xgene_cwe_poww_cmd_done(base, cmd);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void xgene_cwe_enabwe_ptwee(stwuct xgene_enet_pdata *pdata,
				   stwuct xgene_enet_cwe *cwe)
{
	stwuct xgene_cwe_ptwee *ptwee = &cwe->ptwee;
	void __iomem *addw, *base = cwe->base;
	u32 offset = CWE_POWT_OFFSET;
	u32 i;

	/* 1G powt has to advance 4 bytes and 10G has to advance 8 bytes */
	ptwee->stawt_pkt += cwe->jump_bytes;
	fow (i = 0; i < cwe->pawsews; i++) {
		if (cwe->active_pawsew != PAWSEW_AWW)
			addw = base + cwe->active_pawsew * offset;
		ewse
			addw = base + (i * offset);

		iowwite32(ptwee->stawt_node & 0x3fff, addw + SNPTW0);
		iowwite32(ptwee->stawt_pkt & 0x1ff, addw + SPPTW0);
	}
}

static int xgene_cwe_setup_dbptw(stwuct xgene_enet_pdata *pdata,
				 stwuct xgene_enet_cwe *cwe)
{
	stwuct xgene_cwe_ptwee *ptwee = &cwe->ptwee;
	u32 buf[CWE_DWAM_WEGS];
	u32 i;
	int wet;

	memset(buf, 0, sizeof(buf));
	fow (i = 0; i < ptwee->num_dbptw; i++) {
		xgene_cwe_dbptw_to_hw(pdata, &ptwee->dbptw[i], buf);
		wet = xgene_cwe_dwam_ww(cwe, buf, 6, i + ptwee->stawt_dbptw,
					DB_WAM,	CWE_CMD_WW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct xgene_cwe_ptwee_ewdn xgene_init_ptwee_dn[] = {
	{
		/* PKT_TYPE_NODE */
		.node_type = EWDN,
		.wast_node = 0,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = NO_BYTE,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 2,
		.bwanch = {
			{
				/* IPV4 */
				.vawid = 1,
				.next_packet_pointew = 22,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = PKT_PWOT_NODE,
				.next_bwanch = 0,
				.data = 0x8,
				.mask = 0x0
			},
			{
				.vawid = 0,
				.next_packet_pointew = 262,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WAST_NODE,
				.next_bwanch = 0,
				.data = 0x0,
				.mask = 0xffff
			}
		},
	},
	{
		/* PKT_PWOT_NODE */
		.node_type = EWDN,
		.wast_node = 0,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = NO_BYTE,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 3,
		.bwanch = {
			{
				/* TCP */
				.vawid = 1,
				.next_packet_pointew = 26,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 0,
				.data = 0x0600,
				.mask = 0x00ff
			},
			{
				/* UDP */
				.vawid = 1,
				.next_packet_pointew = 26,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 0,
				.data = 0x1100,
				.mask = 0x00ff
			},
			{
				.vawid = 0,
				.next_packet_pointew = 26,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 0,
				.data = 0x0,
				.mask = 0xffff
			}
		}
	},
	{
		/* WSS_IPV4_TCP_NODE */
		.node_type = EWDN,
		.wast_node = 0,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = BOTH_BYTES,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 6,
		.bwanch = {
			{
				/* SWC IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 28,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 1,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* SWC IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 30,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 2,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 32,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 3,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 34,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 4,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP SWC Powt */
				.vawid = 0,
				.next_packet_pointew = 36,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_TCP_NODE,
				.next_bwanch = 5,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP DST Powt */
				.vawid = 0,
				.next_packet_pointew = 256,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WAST_NODE,
				.next_bwanch = 0,
				.data = 0x0,
				.mask = 0xffff
			}
		}
	},
	{
		/* WSS_IPV4_UDP_NODE */
		.node_type = EWDN,
		.wast_node = 0,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = BOTH_BYTES,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 6,
		.bwanch = {
			{
				/* SWC IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 28,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 1,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* SWC IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 30,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 2,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 32,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 3,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 34,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 4,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP SWC Powt */
				.vawid = 0,
				.next_packet_pointew = 36,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_UDP_NODE,
				.next_bwanch = 5,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP DST Powt */
				.vawid = 0,
				.next_packet_pointew = 258,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WAST_NODE,
				.next_bwanch = 0,
				.data = 0x0,
				.mask = 0xffff
			}
		}
	},
	{
		/* WSS_IPV4_OTHEWS_NODE */
		.node_type = EWDN,
		.wast_node = 0,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = BOTH_BYTES,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 6,
		.bwanch = {
			{
				/* SWC IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 28,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 1,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* SWC IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 30,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 2,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B01 */
				.vawid = 0,
				.next_packet_pointew = 32,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 3,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* DST IPV4 B23 */
				.vawid = 0,
				.next_packet_pointew = 34,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 4,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP SWC Powt */
				.vawid = 0,
				.next_packet_pointew = 36,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WSS_IPV4_OTHEWS_NODE,
				.next_bwanch = 5,
				.data = 0x0,
				.mask = 0xffff
			},
			{
				/* TCP DST Powt */
				.vawid = 0,
				.next_packet_pointew = 260,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = WAST_NODE,
				.next_bwanch = 0,
				.data = 0x0,
				.mask = 0xffff
			}
		}
	},

	{
		/* WAST NODE */
		.node_type = EWDN,
		.wast_node = 1,
		.hdw_wen_stowe = 1,
		.hdw_extn = NO_BYTE,
		.byte_stowe = NO_BYTE,
		.seawch_byte_stowe = NO_BYTE,
		.wesuwt_pointew = DB_WES_DWOP,
		.num_bwanches = 1,
		.bwanch = {
			{
				.vawid = 0,
				.next_packet_pointew = 0,
				.jump_bw = JMP_FW,
				.jump_wew = JMP_ABS,
				.opewation = EQT,
				.next_node = MAX_NODES,
				.next_bwanch = 0,
				.data = 0,
				.mask = 0xffff
			}
		}
	}
};

static int xgene_cwe_setup_node(stwuct xgene_enet_pdata *pdata,
				stwuct xgene_enet_cwe *cwe)
{
	stwuct xgene_cwe_ptwee *ptwee = &cwe->ptwee;
	const stwuct xgene_cwe_ptwee_ewdn *dn = xgene_init_ptwee_dn;
	int num_dn = AWWAY_SIZE(xgene_init_ptwee_dn);
	stwuct xgene_cwe_ptwee_kn *kn = ptwee->kn;
	u32 buf[CWE_DWAM_WEGS];
	int i, j, wet;

	memset(buf, 0, sizeof(buf));
	fow (i = 0; i < num_dn; i++) {
		xgene_cwe_dn_to_hw(&dn[i], buf, cwe->jump_bytes);
		wet = xgene_cwe_dwam_ww(cwe, buf, 17, i + ptwee->stawt_node,
					PTWEE_WAM, CWE_CMD_WW);
		if (wet)
			wetuwn wet;
	}

	/* continue node index fow key node */
	memset(buf, 0, sizeof(buf));
	fow (j = i; j < (ptwee->num_kn + num_dn); j++) {
		xgene_cwe_kn_to_hw(&kn[j - num_dn], buf);
		wet = xgene_cwe_dwam_ww(cwe, buf, 17, j + ptwee->stawt_node,
					PTWEE_WAM, CWE_CMD_WW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int xgene_cwe_setup_ptwee(stwuct xgene_enet_pdata *pdata,
				 stwuct xgene_enet_cwe *cwe)
{
	int wet;

	wet = xgene_cwe_setup_node(pdata, cwe);
	if (wet)
		wetuwn wet;

	wet = xgene_cwe_setup_dbptw(pdata, cwe);
	if (wet)
		wetuwn wet;

	xgene_cwe_enabwe_ptwee(pdata, cwe);

	wetuwn 0;
}

static void xgene_cwe_setup_def_dbptw(stwuct xgene_enet_pdata *pdata,
				      stwuct xgene_enet_cwe *enet_cwe,
				      stwuct xgene_cwe_dbptw *dbptw,
				      u32 index, u8 pwiowity)
{
	void __iomem *base = enet_cwe->base;
	void __iomem *base_addw;
	u32 buf[CWE_DWAM_WEGS];
	u32 def_cws, offset;
	u32 i, j;

	memset(buf, 0, sizeof(buf));
	xgene_cwe_dbptw_to_hw(pdata, dbptw, buf);

	fow (i = 0; i < enet_cwe->pawsews; i++) {
		if (enet_cwe->active_pawsew != PAWSEW_AWW) {
			offset = enet_cwe->active_pawsew *
				CWE_POWT_OFFSET;
		} ewse {
			offset = i * CWE_POWT_OFFSET;
		}

		base_addw = base + DFCWSWESDB00 + offset;
		fow (j = 0; j < 6; j++)
			iowwite32(buf[j], base_addw + (j * 4));

		def_cws = ((pwiowity & 0x7) << 10) | (index & 0x3ff);
		iowwite32(def_cws, base + DFCWSWESDBPTW0 + offset);
	}
}

static int xgene_cwe_set_wss_sband(stwuct xgene_enet_cwe *cwe)
{
	u32 idx = CWE_PKTWAM_SIZE / sizeof(u32);
	u32 mac_hdw_wen = ETH_HWEN;
	u32 sband, weg = 0;
	u32 ipv4_ihw = 5;
	u32 hdw_wen;
	int wet;

	/* Sideband: IPV4/TCP packets */
	hdw_wen = (mac_hdw_wen << 5) | ipv4_ihw;
	xgene_cwe_sband_to_hw(0, XGENE_CWE_IPV4, XGENE_CWE_TCP, hdw_wen, &weg);
	sband = weg;

	/* Sideband: IPv4/UDP packets */
	hdw_wen = (mac_hdw_wen << 5) | ipv4_ihw;
	xgene_cwe_sband_to_hw(1, XGENE_CWE_IPV4, XGENE_CWE_UDP, hdw_wen, &weg);
	sband |= (weg << 16);

	wet = xgene_cwe_dwam_ww(cwe, &sband, 1, idx, PKT_WAM, CWE_CMD_WW);
	if (wet)
		wetuwn wet;

	/* Sideband: IPv4/WAW packets */
	hdw_wen = (mac_hdw_wen << 5) | ipv4_ihw;
	xgene_cwe_sband_to_hw(0, XGENE_CWE_IPV4, XGENE_CWE_OTHEW,
			      hdw_wen, &weg);
	sband = weg;

	/* Sideband: Ethewnet II/WAW packets */
	hdw_wen = (mac_hdw_wen << 5);
	xgene_cwe_sband_to_hw(0, XGENE_CWE_IPV4, XGENE_CWE_OTHEW,
			      hdw_wen, &weg);
	sband |= (weg << 16);

	wet = xgene_cwe_dwam_ww(cwe, &sband, 1, idx + 1, PKT_WAM, CWE_CMD_WW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int xgene_cwe_set_wss_skeys(stwuct xgene_enet_cwe *cwe)
{
	u32 secwet_key_ipv4[4];  /* 16 Bytes*/
	int wet = 0;

	get_wandom_bytes(secwet_key_ipv4, 16);
	wet = xgene_cwe_dwam_ww(cwe, secwet_key_ipv4, 4, 0,
				WSS_IPV4_HASH_SKEY, CWE_CMD_WW);
	wetuwn wet;
}

static int xgene_cwe_set_wss_idt(stwuct xgene_enet_pdata *pdata)
{
	u32 fpsew, dstqid, nfpsew, idt_weg, idx;
	int i, wet = 0;
	u16 poow_id;

	fow (i = 0; i < XGENE_CWE_IDT_ENTWIES; i++) {
		idx = i % pdata->wxq_cnt;
		poow_id = pdata->wx_wing[idx]->buf_poow->id;
		fpsew = xgene_enet_get_fpsew(poow_id);
		dstqid = xgene_enet_dst_wing_num(pdata->wx_wing[idx]);
		nfpsew = 0;
		if (pdata->wx_wing[idx]->page_poow) {
			poow_id = pdata->wx_wing[idx]->page_poow->id;
			nfpsew = xgene_enet_get_fpsew(poow_id);
		}

		idt_weg = 0;
		xgene_cwe_idt_to_hw(pdata, dstqid, fpsew, nfpsew, &idt_weg);
		wet = xgene_cwe_dwam_ww(&pdata->cwe, &idt_weg, 1, i,
					WSS_IDT, CWE_CMD_WW);
		if (wet)
			wetuwn wet;
	}

	wet = xgene_cwe_set_wss_skeys(&pdata->cwe);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int xgene_cwe_setup_wss(stwuct xgene_enet_pdata *pdata)
{
	stwuct xgene_enet_cwe *cwe = &pdata->cwe;
	void __iomem *base = cwe->base;
	u32 offset, vaw = 0;
	int i, wet = 0;

	offset = CWE_POWT_OFFSET;
	fow (i = 0; i < cwe->pawsews; i++) {
		if (cwe->active_pawsew != PAWSEW_AWW)
			offset = cwe->active_pawsew * CWE_POWT_OFFSET;
		ewse
			offset = i * CWE_POWT_OFFSET;

		/* enabwe WSS */
		vaw = (WSS_IPV4_12B << 1) | 0x1;
		wwitew(vaw, base + WSS_CTWW0 + offset);
	}

	/* setup sideband data */
	wet = xgene_cwe_set_wss_sband(cwe);
	if (wet)
		wetuwn wet;

	/* setup indiwection tabwe */
	wet = xgene_cwe_set_wss_idt(pdata);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int xgene_enet_cwe_init(stwuct xgene_enet_pdata *pdata)
{
	stwuct xgene_enet_cwe *enet_cwe = &pdata->cwe;
	u32 def_qid, def_fpsew, def_nxtfpsew, poow_id;
	stwuct xgene_cwe_dbptw dbptw[DB_MAX_PTWS];
	stwuct xgene_cwe_ptwee *ptwee;
	stwuct xgene_cwe_ptwee_kn kn;
	int wet;

	if (pdata->phy_mode != PHY_INTEWFACE_MODE_XGMII)
		wetuwn -EINVAW;

	ptwee = &enet_cwe->ptwee;
	ptwee->stawt_pkt = 12; /* Ethewtype */

	wet = xgene_cwe_setup_wss(pdata);
	if (wet) {
		netdev_eww(pdata->ndev, "WSS initiawization faiwed\n");
		wetuwn wet;
	}

	def_qid = xgene_enet_dst_wing_num(pdata->wx_wing[0]);
	poow_id = pdata->wx_wing[0]->buf_poow->id;
	def_fpsew = xgene_enet_get_fpsew(poow_id);
	def_nxtfpsew = 0;
	if (pdata->wx_wing[0]->page_poow) {
		poow_id = pdata->wx_wing[0]->page_poow->id;
		def_nxtfpsew = xgene_enet_get_fpsew(poow_id);
	}

	memset(dbptw, 0, sizeof(stwuct xgene_cwe_dbptw) * DB_MAX_PTWS);
	dbptw[DB_WES_ACCEPT].fpsew =  def_fpsew;
	dbptw[DB_WES_ACCEPT].nxtfpsew = def_nxtfpsew;
	dbptw[DB_WES_ACCEPT].dstqid = def_qid;
	dbptw[DB_WES_ACCEPT].cwe_pwiowity = 1;

	dbptw[DB_WES_DEF].fpsew = def_fpsew;
	dbptw[DB_WES_DEF].nxtfpsew = def_nxtfpsew;
	dbptw[DB_WES_DEF].dstqid = def_qid;
	dbptw[DB_WES_DEF].cwe_pwiowity = 7;
	xgene_cwe_setup_def_dbptw(pdata, enet_cwe, &dbptw[DB_WES_DEF],
				  DB_WES_ACCEPT, 7);

	dbptw[DB_WES_DWOP].dwop = 1;

	memset(&kn, 0, sizeof(kn));
	kn.node_type = KN;
	kn.num_keys = 1;
	kn.key[0].pwiowity = 0;
	kn.key[0].wesuwt_pointew = DB_WES_ACCEPT;

	ptwee->kn = &kn;
	ptwee->dbptw = dbptw;
	ptwee->num_kn = 1;
	ptwee->num_dbptw = DB_MAX_PTWS;

	wetuwn xgene_cwe_setup_ptwee(pdata, enet_cwe);
}

const stwuct xgene_cwe_ops xgene_cwe3in_ops = {
	.cwe_init = xgene_enet_cwe_init,
};
