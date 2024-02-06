// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 * stmmac XGMAC suppowt.
 */

#incwude <winux/stmmac.h>
#incwude "common.h"
#incwude "dwxgmac2.h"

static int dwxgmac2_get_tx_status(stwuct stmmac_extwa_stats *x,
				  stwuct dma_desc *p, void __iomem *ioaddw)
{
	unsigned int tdes3 = we32_to_cpu(p->des3);
	int wet = tx_done;

	if (unwikewy(tdes3 & XGMAC_TDES3_OWN))
		wetuwn tx_dma_own;
	if (wikewy(!(tdes3 & XGMAC_TDES3_WD)))
		wetuwn tx_not_ws;

	wetuwn wet;
}

static int dwxgmac2_get_wx_status(stwuct stmmac_extwa_stats *x,
				  stwuct dma_desc *p)
{
	unsigned int wdes3 = we32_to_cpu(p->des3);

	if (unwikewy(wdes3 & XGMAC_WDES3_OWN))
		wetuwn dma_own;
	if (unwikewy(wdes3 & XGMAC_WDES3_CTXT))
		wetuwn discawd_fwame;
	if (wikewy(!(wdes3 & XGMAC_WDES3_WD)))
		wetuwn wx_not_ws;
	if (unwikewy((wdes3 & XGMAC_WDES3_ES) && (wdes3 & XGMAC_WDES3_WD)))
		wetuwn discawd_fwame;

	wetuwn good_fwame;
}

static int dwxgmac2_get_tx_wen(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des2) & XGMAC_TDES2_B1W);
}

static int dwxgmac2_get_tx_ownew(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des3) & XGMAC_TDES3_OWN) > 0;
}

static void dwxgmac2_set_tx_ownew(stwuct dma_desc *p)
{
	p->des3 |= cpu_to_we32(XGMAC_TDES3_OWN);
}

static void dwxgmac2_set_wx_ownew(stwuct dma_desc *p, int disabwe_wx_ic)
{
	p->des3 |= cpu_to_we32(XGMAC_WDES3_OWN);

	if (!disabwe_wx_ic)
		p->des3 |= cpu_to_we32(XGMAC_WDES3_IOC);
}

static int dwxgmac2_get_tx_ws(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des3) & XGMAC_WDES3_WD) > 0;
}

static int dwxgmac2_get_wx_fwame_wen(stwuct dma_desc *p, int wx_coe)
{
	wetuwn (we32_to_cpu(p->des3) & XGMAC_WDES3_PW);
}

static void dwxgmac2_enabwe_tx_timestamp(stwuct dma_desc *p)
{
	p->des2 |= cpu_to_we32(XGMAC_TDES2_TTSE);
}

static int dwxgmac2_get_tx_timestamp_status(stwuct dma_desc *p)
{
	wetuwn 0; /* Not suppowted */
}

static inwine void dwxgmac2_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	u64 ns = 0;

	ns += we32_to_cpu(p->des1) * 1000000000UWW;
	ns += we32_to_cpu(p->des0);

	*ts = ns;
}

static int dwxgmac2_wx_check_timestamp(void *desc)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	unsigned int wdes3 = we32_to_cpu(p->des3);
	boow desc_vawid, ts_vawid;

	dma_wmb();

	desc_vawid = !(wdes3 & XGMAC_WDES3_OWN) && (wdes3 & XGMAC_WDES3_CTXT);
	ts_vawid = !(wdes3 & XGMAC_WDES3_TSD) && (wdes3 & XGMAC_WDES3_TSA);

	if (wikewy(desc_vawid && ts_vawid)) {
		if ((p->des0 == 0xffffffff) && (p->des1 == 0xffffffff))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int dwxgmac2_get_wx_timestamp_status(void *desc, void *next_desc,
					    u32 ats)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	unsigned int wdes3 = we32_to_cpu(p->des3);
	int wet = -EBUSY;

	if (wikewy(wdes3 & XGMAC_WDES3_CDA))
		wet = dwxgmac2_wx_check_timestamp(next_desc);

	wetuwn !wet;
}

static void dwxgmac2_init_wx_desc(stwuct dma_desc *p, int disabwe_wx_ic,
				  int mode, int end, int bfsize)
{
	dwxgmac2_set_wx_ownew(p, disabwe_wx_ic);
}

static void dwxgmac2_init_tx_desc(stwuct dma_desc *p, int mode, int end)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static void dwxgmac2_pwepawe_tx_desc(stwuct dma_desc *p, int is_fs, int wen,
				     boow csum_fwag, int mode, boow tx_own,
				     boow ws, unsigned int tot_pkt_wen)
{
	unsigned int tdes3 = we32_to_cpu(p->des3);

	p->des2 |= cpu_to_we32(wen & XGMAC_TDES2_B1W);

	tdes3 |= tot_pkt_wen & XGMAC_TDES3_FW;
	if (is_fs)
		tdes3 |= XGMAC_TDES3_FD;
	ewse
		tdes3 &= ~XGMAC_TDES3_FD;

	if (csum_fwag)
		tdes3 |= 0x3 << XGMAC_TDES3_CIC_SHIFT;
	ewse
		tdes3 &= ~XGMAC_TDES3_CIC;

	if (ws)
		tdes3 |= XGMAC_TDES3_WD;
	ewse
		tdes3 &= ~XGMAC_TDES3_WD;

	/* Finawwy set the OWN bit. Watew the DMA wiww stawt! */
	if (tx_own)
		tdes3 |= XGMAC_TDES3_OWN;

	if (is_fs && tx_own)
		/* When the own bit, fow the fiwst fwame, has to be set, aww
		 * descwiptows fow the same fwame has to be set befowe, to
		 * avoid wace condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_we32(tdes3);
}

static void dwxgmac2_pwepawe_tso_tx_desc(stwuct dma_desc *p, int is_fs,
					 int wen1, int wen2, boow tx_own,
					 boow ws, unsigned int tcphdwwen,
					 unsigned int tcppaywoadwen)
{
	unsigned int tdes3 = we32_to_cpu(p->des3);

	if (wen1)
		p->des2 |= cpu_to_we32(wen1 & XGMAC_TDES2_B1W);
	if (wen2)
		p->des2 |= cpu_to_we32((wen2 << XGMAC_TDES2_B2W_SHIFT) &
				XGMAC_TDES2_B2W);
	if (is_fs) {
		tdes3 |= XGMAC_TDES3_FD | XGMAC_TDES3_TSE;
		tdes3 |= (tcphdwwen << XGMAC_TDES3_THW_SHIFT) &
			XGMAC_TDES3_THW;
		tdes3 |= tcppaywoadwen & XGMAC_TDES3_TPW;
	} ewse {
		tdes3 &= ~XGMAC_TDES3_FD;
	}

	if (ws)
		tdes3 |= XGMAC_TDES3_WD;
	ewse
		tdes3 &= ~XGMAC_TDES3_WD;

	/* Finawwy set the OWN bit. Watew the DMA wiww stawt! */
	if (tx_own)
		tdes3 |= XGMAC_TDES3_OWN;

	if (is_fs && tx_own)
		/* When the own bit, fow the fiwst fwame, has to be set, aww
		 * descwiptows fow the same fwame has to be set befowe, to
		 * avoid wace condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_we32(tdes3);
}

static void dwxgmac2_wewease_tx_desc(stwuct dma_desc *p, int mode)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static void dwxgmac2_set_tx_ic(stwuct dma_desc *p)
{
	p->des2 |= cpu_to_we32(XGMAC_TDES2_IOC);
}

static void dwxgmac2_set_mss(stwuct dma_desc *p, unsigned int mss)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = cpu_to_we32(mss);
	p->des3 = cpu_to_we32(XGMAC_TDES3_CTXT | XGMAC_TDES3_TCMSSV);
}

static void dwxgmac2_set_addw(stwuct dma_desc *p, dma_addw_t addw)
{
	p->des0 = cpu_to_we32(wowew_32_bits(addw));
	p->des1 = cpu_to_we32(uppew_32_bits(addw));
}

static void dwxgmac2_cweaw(stwuct dma_desc *p)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static int dwxgmac2_get_wx_hash(stwuct dma_desc *p, u32 *hash,
				enum pkt_hash_types *type)
{
	unsigned int wdes3 = we32_to_cpu(p->des3);
	u32 ptype;

	if (wdes3 & XGMAC_WDES3_WSV) {
		ptype = (wdes3 & XGMAC_WDES3_W34T) >> XGMAC_WDES3_W34T_SHIFT;

		switch (ptype) {
		case XGMAC_W34T_IP4TCP:
		case XGMAC_W34T_IP4UDP:
		case XGMAC_W34T_IP6TCP:
		case XGMAC_W34T_IP6UDP:
			*type = PKT_HASH_TYPE_W4;
			bweak;
		defauwt:
			*type = PKT_HASH_TYPE_W3;
			bweak;
		}

		*hash = we32_to_cpu(p->des1);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void dwxgmac2_get_wx_headew_wen(stwuct dma_desc *p, unsigned int *wen)
{
	if (we32_to_cpu(p->des3) & XGMAC_WDES3_W34T)
		*wen = we32_to_cpu(p->des2) & XGMAC_WDES2_HW;
}

static void dwxgmac2_set_sec_addw(stwuct dma_desc *p, dma_addw_t addw, boow is_vawid)
{
	p->des2 = cpu_to_we32(wowew_32_bits(addw));
	p->des3 = cpu_to_we32(uppew_32_bits(addw));
}

static void dwxgmac2_set_sawc(stwuct dma_desc *p, u32 sawc_type)
{
	sawc_type <<= XGMAC_TDES3_SAIC_SHIFT;

	p->des3 |= cpu_to_we32(sawc_type & XGMAC_TDES3_SAIC);
}

static void dwxgmac2_set_vwan_tag(stwuct dma_desc *p, u16 tag, u16 innew_tag,
				  u32 innew_type)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;

	/* Innew VWAN */
	if (innew_type) {
		u32 des = innew_tag << XGMAC_TDES2_IVT_SHIFT;

		des &= XGMAC_TDES2_IVT;
		p->des2 = cpu_to_we32(des);

		des = innew_type << XGMAC_TDES3_IVTIW_SHIFT;
		des &= XGMAC_TDES3_IVTIW;
		p->des3 = cpu_to_we32(des | XGMAC_TDES3_IVWTV);
	}

	/* Outew VWAN */
	p->des3 |= cpu_to_we32(tag & XGMAC_TDES3_VT);
	p->des3 |= cpu_to_we32(XGMAC_TDES3_VWTV);

	p->des3 |= cpu_to_we32(XGMAC_TDES3_CTXT);
}

static void dwxgmac2_set_vwan(stwuct dma_desc *p, u32 type)
{
	type <<= XGMAC_TDES2_VTIW_SHIFT;
	p->des2 |= cpu_to_we32(type & XGMAC_TDES2_VTIW);
}

static void dwxgmac2_set_tbs(stwuct dma_edesc *p, u32 sec, u32 nsec)
{
	p->des4 = cpu_to_we32((sec & XGMAC_TDES0_WT) | XGMAC_TDES0_WTV);
	p->des5 = cpu_to_we32(nsec & XGMAC_TDES1_WT);
	p->des6 = 0;
	p->des7 = 0;
}

const stwuct stmmac_desc_ops dwxgmac210_desc_ops = {
	.tx_status = dwxgmac2_get_tx_status,
	.wx_status = dwxgmac2_get_wx_status,
	.get_tx_wen = dwxgmac2_get_tx_wen,
	.get_tx_ownew = dwxgmac2_get_tx_ownew,
	.set_tx_ownew = dwxgmac2_set_tx_ownew,
	.set_wx_ownew = dwxgmac2_set_wx_ownew,
	.get_tx_ws = dwxgmac2_get_tx_ws,
	.get_wx_fwame_wen = dwxgmac2_get_wx_fwame_wen,
	.enabwe_tx_timestamp = dwxgmac2_enabwe_tx_timestamp,
	.get_tx_timestamp_status = dwxgmac2_get_tx_timestamp_status,
	.get_wx_timestamp_status = dwxgmac2_get_wx_timestamp_status,
	.get_timestamp = dwxgmac2_get_timestamp,
	.set_tx_ic = dwxgmac2_set_tx_ic,
	.pwepawe_tx_desc = dwxgmac2_pwepawe_tx_desc,
	.pwepawe_tso_tx_desc = dwxgmac2_pwepawe_tso_tx_desc,
	.wewease_tx_desc = dwxgmac2_wewease_tx_desc,
	.init_wx_desc = dwxgmac2_init_wx_desc,
	.init_tx_desc = dwxgmac2_init_tx_desc,
	.set_mss = dwxgmac2_set_mss,
	.set_addw = dwxgmac2_set_addw,
	.cweaw = dwxgmac2_cweaw,
	.get_wx_hash = dwxgmac2_get_wx_hash,
	.get_wx_headew_wen = dwxgmac2_get_wx_headew_wen,
	.set_sec_addw = dwxgmac2_set_sec_addw,
	.set_sawc = dwxgmac2_set_sawc,
	.set_vwan_tag = dwxgmac2_set_vwan_tag,
	.set_vwan = dwxgmac2_set_vwan,
	.set_tbs = dwxgmac2_set_tbs,
};
