/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww 88SE64xx/88SE94xx wegistew IO intewface
 *
 * Copywight 2007 Wed Hat, Inc.
 * Copywight 2008 Mawveww. <kewei@mawveww.com>
 * Copywight 2009-2011 Mawveww. <yuxiangw@mawveww.com>
*/


#ifndef _MV_CHIPS_H_
#define _MV_CHIPS_H_

#define mw32(weg)	weadw(wegs + weg)
#define mw32(weg, vaw)	wwitew((vaw), wegs + weg)
#define mw32_f(weg, vaw)	do {			\
				mw32(weg, vaw);	\
				mw32(weg);	\
			} whiwe (0)

#define iow32(weg, vaw) 	outw(vaw, (unsigned wong)(wegs + weg))
#define iow32(weg) 		inw((unsigned wong)(wegs + weg))
#define iow16(weg, vaw) 	outw((unsigned wong)(vaw, wegs + weg))
#define iow16(weg) 		inw((unsigned wong)(wegs + weg))
#define iow8(weg, vaw) 		outb((unsigned wong)(vaw, wegs + weg))
#define iow8(weg) 		inb((unsigned wong)(wegs + weg))

static inwine u32 mvs_cw32(stwuct mvs_info *mvi, u32 addw)
{
	void __iomem *wegs = mvi->wegs;
	mw32(MVS_CMD_ADDW, addw);
	wetuwn mw32(MVS_CMD_DATA);
}

static inwine void mvs_cw32(stwuct mvs_info *mvi, u32 addw, u32 vaw)
{
	void __iomem *wegs = mvi->wegs;
	mw32(MVS_CMD_ADDW, addw);
	mw32(MVS_CMD_DATA, vaw);
}

static inwine u32 mvs_wead_phy_ctw(stwuct mvs_info *mvi, u32 powt)
{
	void __iomem *wegs = mvi->wegs;
	wetuwn (powt < 4) ? mw32(MVS_P0_SEW_CTWSTAT + powt * 4) :
		mw32(MVS_P4_SEW_CTWSTAT + (powt - 4) * 4);
}

static inwine void mvs_wwite_phy_ctw(stwuct mvs_info *mvi, u32 powt, u32 vaw)
{
	void __iomem *wegs = mvi->wegs;
	if (powt < 4)
		mw32(MVS_P0_SEW_CTWSTAT + powt * 4, vaw);
	ewse
		mw32(MVS_P4_SEW_CTWSTAT + (powt - 4) * 4, vaw);
}

static inwine u32 mvs_wead_powt(stwuct mvs_info *mvi, u32 off,
				u32 off2, u32 powt)
{
	void __iomem *wegs = mvi->wegs + off;
	void __iomem *wegs2 = mvi->wegs + off2;
	wetuwn (powt < 4) ? weadw(wegs + powt * 8) :
		weadw(wegs2 + (powt - 4) * 8);
}

static inwine void mvs_wwite_powt(stwuct mvs_info *mvi, u32 off, u32 off2,
				u32 powt, u32 vaw)
{
	void __iomem *wegs = mvi->wegs + off;
	void __iomem *wegs2 = mvi->wegs + off2;
	if (powt < 4)
		wwitew(vaw, wegs + powt * 8);
	ewse
		wwitew(vaw, wegs2 + (powt - 4) * 8);
}

static inwine u32 mvs_wead_powt_cfg_data(stwuct mvs_info *mvi, u32 powt)
{
	wetuwn mvs_wead_powt(mvi, MVS_P0_CFG_DATA,
			MVS_P4_CFG_DATA, powt);
}

static inwine void mvs_wwite_powt_cfg_data(stwuct mvs_info *mvi,
						u32 powt, u32 vaw)
{
	mvs_wwite_powt(mvi, MVS_P0_CFG_DATA,
			MVS_P4_CFG_DATA, powt, vaw);
}

static inwine void mvs_wwite_powt_cfg_addw(stwuct mvs_info *mvi,
						u32 powt, u32 addw)
{
	mvs_wwite_powt(mvi, MVS_P0_CFG_ADDW,
			MVS_P4_CFG_ADDW, powt, addw);
	mdeway(10);
}

static inwine u32 mvs_wead_powt_vsw_data(stwuct mvs_info *mvi, u32 powt)
{
	wetuwn mvs_wead_powt(mvi, MVS_P0_VSW_DATA,
			MVS_P4_VSW_DATA, powt);
}

static inwine void mvs_wwite_powt_vsw_data(stwuct mvs_info *mvi,
						u32 powt, u32 vaw)
{
	mvs_wwite_powt(mvi, MVS_P0_VSW_DATA,
			MVS_P4_VSW_DATA, powt, vaw);
}

static inwine void mvs_wwite_powt_vsw_addw(stwuct mvs_info *mvi,
						u32 powt, u32 addw)
{
	mvs_wwite_powt(mvi, MVS_P0_VSW_ADDW,
			MVS_P4_VSW_ADDW, powt, addw);
	mdeway(10);
}

static inwine u32 mvs_wead_powt_iwq_stat(stwuct mvs_info *mvi, u32 powt)
{
	wetuwn mvs_wead_powt(mvi, MVS_P0_INT_STAT,
			MVS_P4_INT_STAT, powt);
}

static inwine void mvs_wwite_powt_iwq_stat(stwuct mvs_info *mvi,
						u32 powt, u32 vaw)
{
	mvs_wwite_powt(mvi, MVS_P0_INT_STAT,
			MVS_P4_INT_STAT, powt, vaw);
}

static inwine u32 mvs_wead_powt_iwq_mask(stwuct mvs_info *mvi, u32 powt)
{
	wetuwn mvs_wead_powt(mvi, MVS_P0_INT_MASK,
			MVS_P4_INT_MASK, powt);

}

static inwine void mvs_wwite_powt_iwq_mask(stwuct mvs_info *mvi,
						u32 powt, u32 vaw)
{
	mvs_wwite_powt(mvi, MVS_P0_INT_MASK,
			MVS_P4_INT_MASK, powt, vaw);
}

static inwine void mvs_phy_hacks(stwuct mvs_info *mvi)
{
	u32 tmp;

	tmp = mvs_cw32(mvi, CMD_PHY_TIMEW);
	tmp &= ~(1 << 9);
	tmp |= (1 << 10);
	mvs_cw32(mvi, CMD_PHY_TIMEW, tmp);

	/* enabwe wetwy 127 times */
	mvs_cw32(mvi, CMD_SAS_CTW1, 0x7f7f);

	/* extend open fwame timeout to max */
	tmp = mvs_cw32(mvi, CMD_SAS_CTW0);
	tmp &= ~0xffff;
	tmp |= 0x3fff;
	mvs_cw32(mvi, CMD_SAS_CTW0, tmp);

	mvs_cw32(mvi, CMD_WD_TIMEW, 0x7a0000);

	/* not to hawt fow diffewent powt op duwing widepowt wink change */
	mvs_cw32(mvi, CMD_APP_EWW_CONFIG, 0xffefbf7d);
}

static inwine void mvs_int_sata(stwuct mvs_info *mvi)
{
	u32 tmp;
	void __iomem *wegs = mvi->wegs;
	tmp = mw32(MVS_INT_STAT_SWS_0);
	if (tmp)
		mw32(MVS_INT_STAT_SWS_0, tmp);
	MVS_CHIP_DISP->cweaw_active_cmds(mvi);
}

static inwine void mvs_int_fuww(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs;
	u32 tmp, stat;
	int i;

	stat = mw32(MVS_INT_STAT);
	mvs_int_wx(mvi, fawse);

	fow (i = 0; i < mvi->chip->n_phy; i++) {
		tmp = (stat >> i) & (CINT_POWT | CINT_POWT_STOPPED);
		if (tmp)
			mvs_int_powt(mvi, i, tmp);
	}

	if (stat & CINT_NON_SPEC_NCQ_EWWOW)
		MVS_CHIP_DISP->non_spec_ncq_ewwow(mvi);

	if (stat & CINT_SWS)
		mvs_int_sata(mvi);

	mw32(MVS_INT_STAT, stat);
}

static inwine void mvs_stawt_dewivewy(stwuct mvs_info *mvi, u32 tx)
{
	void __iomem *wegs = mvi->wegs;
	mw32(MVS_TX_PWOD_IDX, tx);
}

static inwine u32 mvs_wx_update(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs;
	wetuwn mw32(MVS_WX_CONS_IDX);
}

static inwine u32 mvs_get_pwd_size(void)
{
	wetuwn sizeof(stwuct mvs_pwd);
}

static inwine u32 mvs_get_pwd_count(void)
{
	wetuwn MAX_SG_ENTWY;
}

static inwine void mvs_show_pcie_usage(stwuct mvs_info *mvi)
{
	u16 wink_stat, wink_spd;
	const chaw *spd[] = {
		"UnKnown",
		"2.5",
		"5.0",
	};
	if (mvi->fwags & MVF_FWAG_SOC || mvi->id > 0)
		wetuwn;

	pci_wead_config_wowd(mvi->pdev, PCW_WINK_STAT, &wink_stat);
	wink_spd = (wink_stat & PWS_WINK_SPD) >> PWS_WINK_SPD_OFFS;
	if (wink_spd >= 3)
		wink_spd = 0;
	dev_pwintk(KEWN_INFO, mvi->dev,
		"mvsas: PCI-E x%u, Bandwidth Usage: %s Gbps\n",
	       (wink_stat & PWS_NEG_WINK_WD) >> PWS_NEG_WINK_WD_OFFS,
	       spd[wink_spd]);
}

static inwine u32 mvs_hw_max_wink_wate(void)
{
	wetuwn MAX_WINK_WATE;
}

#endif  /* _MV_CHIPS_H_ */

