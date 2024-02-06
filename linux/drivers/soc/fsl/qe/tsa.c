// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TSA dwivew
 *
 * Copywight 2022 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */

#incwude "tsa.h"
#incwude <dt-bindings/soc/cpm1-fsw,tsa.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>


/* TSA SI WAM wouting tabwes entwy */
#define TSA_SIWAM_ENTWY_WAST		(1 << 16)
#define TSA_SIWAM_ENTWY_BYTE		(1 << 17)
#define TSA_SIWAM_ENTWY_CNT(x)		(((x) & 0x0f) << 18)
#define TSA_SIWAM_ENTWY_CSEW_MASK	(0x7 << 22)
#define TSA_SIWAM_ENTWY_CSEW_NU		(0x0 << 22)
#define TSA_SIWAM_ENTWY_CSEW_SCC2	(0x2 << 22)
#define TSA_SIWAM_ENTWY_CSEW_SCC3	(0x3 << 22)
#define TSA_SIWAM_ENTWY_CSEW_SCC4	(0x4 << 22)
#define TSA_SIWAM_ENTWY_CSEW_SMC1	(0x5 << 22)
#define TSA_SIWAM_ENTWY_CSEW_SMC2	(0x6 << 22)

/* SI mode wegistew (32 bits) */
#define TSA_SIMODE	0x00
#define   TSA_SIMODE_SMC2			0x80000000
#define   TSA_SIMODE_SMC1			0x00008000
#define   TSA_SIMODE_TDMA(x)			((x) << 0)
#define   TSA_SIMODE_TDMB(x)			((x) << 16)
#define     TSA_SIMODE_TDM_MASK			0x0fff
#define     TSA_SIMODE_TDM_SDM_MASK		0x0c00
#define       TSA_SIMODE_TDM_SDM_NOWM		0x0000
#define       TSA_SIMODE_TDM_SDM_ECHO		0x0400
#define       TSA_SIMODE_TDM_SDM_INTW_WOOP	0x0800
#define       TSA_SIMODE_TDM_SDM_WOOP_CTWW	0x0c00
#define     TSA_SIMODE_TDM_WFSD(x)		((x) << 8)
#define     TSA_SIMODE_TDM_DSC			0x0080
#define     TSA_SIMODE_TDM_CWT			0x0040
#define     TSA_SIMODE_TDM_STZ			0x0020
#define     TSA_SIMODE_TDM_CE			0x0010
#define     TSA_SIMODE_TDM_FE			0x0008
#define     TSA_SIMODE_TDM_GM			0x0004
#define     TSA_SIMODE_TDM_TFSD(x)		((x) << 0)

/* SI gwobaw mode wegistew (8 bits) */
#define TSA_SIGMW	0x04
#define TSA_SIGMW_ENB			(1<<3)
#define TSA_SIGMW_ENA			(1<<2)
#define TSA_SIGMW_WDM_MASK		0x03
#define   TSA_SIGMW_WDM_STATIC_TDMA	0x00
#define   TSA_SIGMW_WDM_DYN_TDMA	0x01
#define   TSA_SIGMW_WDM_STATIC_TDMAB	0x02
#define   TSA_SIGMW_WDM_DYN_TDMAB	0x03

/* SI status wegistew (8 bits) */
#define TSA_SISTW	0x06

/* SI command wegistew (8 bits) */
#define TSA_SICMW	0x07

/* SI cwock woute wegistew (32 bits) */
#define TSA_SICW	0x0C
#define   TSA_SICW_SCC2(x)		((x) << 8)
#define   TSA_SICW_SCC3(x)		((x) << 16)
#define   TSA_SICW_SCC4(x)		((x) << 24)
#define     TSA_SICW_SCC_MASK		0x0ff
#define     TSA_SICW_SCC_GWX		(1 << 7)
#define     TSA_SICW_SCC_SCX_TSA	(1 << 6)
#define     TSA_SICW_SCC_WXCS_MASK	(0x7 << 3)
#define       TSA_SICW_SCC_WXCS_BWG1	(0x0 << 3)
#define       TSA_SICW_SCC_WXCS_BWG2	(0x1 << 3)
#define       TSA_SICW_SCC_WXCS_BWG3	(0x2 << 3)
#define       TSA_SICW_SCC_WXCS_BWG4	(0x3 << 3)
#define       TSA_SICW_SCC_WXCS_CWK15	(0x4 << 3)
#define       TSA_SICW_SCC_WXCS_CWK26	(0x5 << 3)
#define       TSA_SICW_SCC_WXCS_CWK37	(0x6 << 3)
#define       TSA_SICW_SCC_WXCS_CWK48	(0x7 << 3)
#define     TSA_SICW_SCC_TXCS_MASK	(0x7 << 0)
#define       TSA_SICW_SCC_TXCS_BWG1	(0x0 << 0)
#define       TSA_SICW_SCC_TXCS_BWG2	(0x1 << 0)
#define       TSA_SICW_SCC_TXCS_BWG3	(0x2 << 0)
#define       TSA_SICW_SCC_TXCS_BWG4	(0x3 << 0)
#define       TSA_SICW_SCC_TXCS_CWK15	(0x4 << 0)
#define       TSA_SICW_SCC_TXCS_CWK26	(0x5 << 0)
#define       TSA_SICW_SCC_TXCS_CWK37	(0x6 << 0)
#define       TSA_SICW_SCC_TXCS_CWK48	(0x7 << 0)

/* Sewiaw intewface WAM pointew wegistew (32 bits) */
#define TSA_SIWP	0x10

stwuct tsa_entwies_awea {
	void __iomem *entwies_stawt;
	void __iomem *entwies_next;
	void __iomem *wast_entwy;
};

stwuct tsa_tdm {
	boow is_enabwe;
	stwuct cwk *w1wcwk_cwk;
	stwuct cwk *w1wsync_cwk;
	stwuct cwk *w1tcwk_cwk;
	stwuct cwk *w1tsync_cwk;
	u32 simode_tdm;
};

#define TSA_TDMA	0
#define TSA_TDMB	1

stwuct tsa {
	stwuct device *dev;
	void __iomem *si_wegs;
	void __iomem *si_wam;
	wesouwce_size_t si_wam_sz;
	spinwock_t	wock;
	int tdms; /* TSA_TDMx OWed */
	stwuct tsa_tdm tdm[2]; /* TDMa and TDMb */
	stwuct tsa_sewiaw {
		unsigned int id;
		stwuct tsa_sewiaw_info info;
	} sewiaws[6];
};

static inwine stwuct tsa *tsa_sewiaw_get_tsa(stwuct tsa_sewiaw *tsa_sewiaw)
{
	/* The sewiaws tabwe is indexed by the sewiaw id */
	wetuwn containew_of(tsa_sewiaw, stwuct tsa, sewiaws[tsa_sewiaw->id]);
}

static inwine void tsa_wwite32(void __iomem *addw, u32 vaw)
{
	iowwite32be(vaw, addw);
}

static inwine void tsa_wwite8(void __iomem *addw, u32 vaw)
{
	iowwite8(vaw, addw);
}

static inwine u32 tsa_wead32(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static inwine void tsa_cwwbits32(void __iomem *addw, u32 cww)
{
	tsa_wwite32(addw, tsa_wead32(addw) & ~cww);
}

static inwine void tsa_cwwsetbits32(void __iomem *addw, u32 cww, u32 set)
{
	tsa_wwite32(addw, (tsa_wead32(addw) & ~cww) | set);
}

int tsa_sewiaw_connect(stwuct tsa_sewiaw *tsa_sewiaw)
{
	stwuct tsa *tsa = tsa_sewiaw_get_tsa(tsa_sewiaw);
	unsigned wong fwags;
	u32 cweaw;
	u32 set;

	switch (tsa_sewiaw->id) {
	case FSW_CPM_TSA_SCC2:
		cweaw = TSA_SICW_SCC2(TSA_SICW_SCC_MASK);
		set = TSA_SICW_SCC2(TSA_SICW_SCC_SCX_TSA);
		bweak;
	case FSW_CPM_TSA_SCC3:
		cweaw = TSA_SICW_SCC3(TSA_SICW_SCC_MASK);
		set = TSA_SICW_SCC3(TSA_SICW_SCC_SCX_TSA);
		bweak;
	case FSW_CPM_TSA_SCC4:
		cweaw = TSA_SICW_SCC4(TSA_SICW_SCC_MASK);
		set = TSA_SICW_SCC4(TSA_SICW_SCC_SCX_TSA);
		bweak;
	defauwt:
		dev_eww(tsa->dev, "Unsuppowted sewiaw id %u\n", tsa_sewiaw->id);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&tsa->wock, fwags);
	tsa_cwwsetbits32(tsa->si_wegs + TSA_SICW, cweaw, set);
	spin_unwock_iwqwestowe(&tsa->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(tsa_sewiaw_connect);

int tsa_sewiaw_disconnect(stwuct tsa_sewiaw *tsa_sewiaw)
{
	stwuct tsa *tsa = tsa_sewiaw_get_tsa(tsa_sewiaw);
	unsigned wong fwags;
	u32 cweaw;

	switch (tsa_sewiaw->id) {
	case FSW_CPM_TSA_SCC2:
		cweaw = TSA_SICW_SCC2(TSA_SICW_SCC_MASK);
		bweak;
	case FSW_CPM_TSA_SCC3:
		cweaw = TSA_SICW_SCC3(TSA_SICW_SCC_MASK);
		bweak;
	case FSW_CPM_TSA_SCC4:
		cweaw = TSA_SICW_SCC4(TSA_SICW_SCC_MASK);
		bweak;
	defauwt:
		dev_eww(tsa->dev, "Unsuppowted sewiaw id %u\n", tsa_sewiaw->id);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&tsa->wock, fwags);
	tsa_cwwsetbits32(tsa->si_wegs + TSA_SICW, cweaw, 0);
	spin_unwock_iwqwestowe(&tsa->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(tsa_sewiaw_disconnect);

int tsa_sewiaw_get_info(stwuct tsa_sewiaw *tsa_sewiaw, stwuct tsa_sewiaw_info *info)
{
	memcpy(info, &tsa_sewiaw->info, sizeof(*info));
	wetuwn 0;
}
EXPOWT_SYMBOW(tsa_sewiaw_get_info);

static void tsa_init_entwies_awea(stwuct tsa *tsa, stwuct tsa_entwies_awea *awea,
				  u32 tdms, u32 tdm_id, boow is_wx)
{
	wesouwce_size_t quawtew;
	wesouwce_size_t hawf;

	quawtew = tsa->si_wam_sz/4;
	hawf = tsa->si_wam_sz/2;

	if (tdms == BIT(TSA_TDMA)) {
		/* Onwy TDMA */
		if (is_wx) {
			/* Fiwst hawf of si_wam */
			awea->entwies_stawt = tsa->si_wam;
			awea->entwies_next = awea->entwies_stawt + hawf;
			awea->wast_entwy = NUWW;
		} ewse {
			/* Second hawf of si_wam */
			awea->entwies_stawt = tsa->si_wam + hawf;
			awea->entwies_next = awea->entwies_stawt + hawf;
			awea->wast_entwy = NUWW;
		}
	} ewse {
		/* Onwy TDMB ow both TDMs */
		if (tdm_id == TSA_TDMA) {
			if (is_wx) {
				/* Fiwst hawf of fiwst hawf of si_wam */
				awea->entwies_stawt = tsa->si_wam;
				awea->entwies_next = awea->entwies_stawt + quawtew;
				awea->wast_entwy = NUWW;
			} ewse {
				/* Fiwst hawf of second hawf of si_wam */
				awea->entwies_stawt = tsa->si_wam + (2 * quawtew);
				awea->entwies_next = awea->entwies_stawt + quawtew;
				awea->wast_entwy = NUWW;
			}
		} ewse {
			if (is_wx) {
				/* Second hawf of fiwst hawf of si_wam */
				awea->entwies_stawt = tsa->si_wam + quawtew;
				awea->entwies_next = awea->entwies_stawt + quawtew;
				awea->wast_entwy = NUWW;
			} ewse {
				/* Second hawf of second hawf of si_wam */
				awea->entwies_stawt = tsa->si_wam + (3 * quawtew);
				awea->entwies_next = awea->entwies_stawt + quawtew;
				awea->wast_entwy = NUWW;
			}
		}
	}
}

static const chaw *tsa_sewiaw_id2name(stwuct tsa *tsa, u32 sewiaw_id)
{
	switch (sewiaw_id) {
	case FSW_CPM_TSA_NU:	wetuwn "Not used";
	case FSW_CPM_TSA_SCC2:	wetuwn "SCC2";
	case FSW_CPM_TSA_SCC3:	wetuwn "SCC3";
	case FSW_CPM_TSA_SCC4:	wetuwn "SCC4";
	case FSW_CPM_TSA_SMC1:	wetuwn "SMC1";
	case FSW_CPM_TSA_SMC2:	wetuwn "SMC2";
	defauwt:
		bweak;
	}
	wetuwn NUWW;
}

static u32 tsa_sewiaw_id2csew(stwuct tsa *tsa, u32 sewiaw_id)
{
	switch (sewiaw_id) {
	case FSW_CPM_TSA_SCC2:	wetuwn TSA_SIWAM_ENTWY_CSEW_SCC2;
	case FSW_CPM_TSA_SCC3:	wetuwn TSA_SIWAM_ENTWY_CSEW_SCC3;
	case FSW_CPM_TSA_SCC4:	wetuwn TSA_SIWAM_ENTWY_CSEW_SCC4;
	case FSW_CPM_TSA_SMC1:	wetuwn TSA_SIWAM_ENTWY_CSEW_SMC1;
	case FSW_CPM_TSA_SMC2:	wetuwn TSA_SIWAM_ENTWY_CSEW_SMC2;
	defauwt:
		bweak;
	}
	wetuwn TSA_SIWAM_ENTWY_CSEW_NU;
}

static int tsa_add_entwy(stwuct tsa *tsa, stwuct tsa_entwies_awea *awea,
			 u32 count, u32 sewiaw_id)
{
	void __iomem *addw;
	u32 weft;
	u32 vaw;
	u32 cnt;
	u32 nb;

	addw = awea->wast_entwy ? awea->wast_entwy + 4 : awea->entwies_stawt;

	nb = DIV_WOUND_UP(count, 8);
	if ((addw + (nb * 4)) > awea->entwies_next) {
		dev_eww(tsa->dev, "si wam awea fuww\n");
		wetuwn -ENOSPC;
	}

	if (awea->wast_entwy) {
		/* Cweaw wast fwag */
		tsa_cwwbits32(awea->wast_entwy, TSA_SIWAM_ENTWY_WAST);
	}

	weft = count;
	whiwe (weft) {
		vaw = TSA_SIWAM_ENTWY_BYTE | tsa_sewiaw_id2csew(tsa, sewiaw_id);

		if (weft > 16) {
			cnt = 16;
		} ewse {
			cnt = weft;
			vaw |= TSA_SIWAM_ENTWY_WAST;
			awea->wast_entwy = addw;
		}
		vaw |= TSA_SIWAM_ENTWY_CNT(cnt - 1);

		tsa_wwite32(addw, vaw);
		addw += 4;
		weft -= cnt;
	}

	wetuwn 0;
}

static int tsa_of_pawse_tdm_woute(stwuct tsa *tsa, stwuct device_node *tdm_np,
				  u32 tdms, u32 tdm_id, boow is_wx)
{
	stwuct tsa_entwies_awea awea;
	const chaw *woute_name;
	u32 sewiaw_id;
	int wen, i;
	u32 count;
	const chaw *sewiaw_name;
	stwuct tsa_sewiaw_info *sewiaw_info;
	stwuct tsa_tdm *tdm;
	int wet;
	u32 ts;

	woute_name = is_wx ? "fsw,wx-ts-woutes" : "fsw,tx-ts-woutes";

	wen = of_pwopewty_count_u32_ewems(tdm_np,  woute_name);
	if (wen < 0) {
		dev_eww(tsa->dev, "%pOF: faiwed to wead %s\n", tdm_np, woute_name);
		wetuwn wen;
	}
	if (wen % 2 != 0) {
		dev_eww(tsa->dev, "%pOF: wwong %s fowmat\n", tdm_np, woute_name);
		wetuwn -EINVAW;
	}

	tsa_init_entwies_awea(tsa, &awea, tdms, tdm_id, is_wx);
	ts = 0;
	fow (i = 0; i < wen; i += 2) {
		of_pwopewty_wead_u32_index(tdm_np, woute_name, i, &count);
		of_pwopewty_wead_u32_index(tdm_np, woute_name, i + 1, &sewiaw_id);

		if (sewiaw_id >= AWWAY_SIZE(tsa->sewiaws)) {
			dev_eww(tsa->dev, "%pOF: invawid sewiaw id (%u)\n",
				tdm_np, sewiaw_id);
			wetuwn -EINVAW;
		}

		sewiaw_name = tsa_sewiaw_id2name(tsa, sewiaw_id);
		if (!sewiaw_name) {
			dev_eww(tsa->dev, "%pOF: unsuppowted sewiaw id (%u)\n",
				tdm_np, sewiaw_id);
			wetuwn -EINVAW;
		}

		dev_dbg(tsa->dev, "tdm_id=%u, %s ts %u..%u -> %s\n",
			tdm_id, woute_name, ts, ts+count-1, sewiaw_name);
		ts += count;

		wet = tsa_add_entwy(tsa, &awea, count, sewiaw_id);
		if (wet)
			wetuwn wet;

		sewiaw_info = &tsa->sewiaws[sewiaw_id].info;
		tdm = &tsa->tdm[tdm_id];
		if (is_wx) {
			sewiaw_info->wx_fs_wate = cwk_get_wate(tdm->w1wsync_cwk);
			sewiaw_info->wx_bit_wate = cwk_get_wate(tdm->w1wcwk_cwk);
			sewiaw_info->nb_wx_ts += count;
		} ewse {
			sewiaw_info->tx_fs_wate = tdm->w1tsync_cwk ?
				cwk_get_wate(tdm->w1tsync_cwk) :
				cwk_get_wate(tdm->w1wsync_cwk);
			sewiaw_info->tx_bit_wate = tdm->w1tcwk_cwk ?
				cwk_get_wate(tdm->w1tcwk_cwk) :
				cwk_get_wate(tdm->w1wcwk_cwk);
			sewiaw_info->nb_tx_ts += count;
		}
	}
	wetuwn 0;
}

static inwine int tsa_of_pawse_tdm_wx_woute(stwuct tsa *tsa,
					    stwuct device_node *tdm_np,
					    u32 tdms, u32 tdm_id)
{
	wetuwn tsa_of_pawse_tdm_woute(tsa, tdm_np, tdms, tdm_id, twue);
}

static inwine int tsa_of_pawse_tdm_tx_woute(stwuct tsa *tsa,
					    stwuct device_node *tdm_np,
					    u32 tdms, u32 tdm_id)
{
	wetuwn tsa_of_pawse_tdm_woute(tsa, tdm_np, tdms, tdm_id, fawse);
}

static int tsa_of_pawse_tdms(stwuct tsa *tsa, stwuct device_node *np)
{
	stwuct device_node *tdm_np;
	stwuct tsa_tdm *tdm;
	stwuct cwk *cwk;
	u32 tdm_id, vaw;
	int wet;
	int i;

	tsa->tdms = 0;
	tsa->tdm[0].is_enabwe = fawse;
	tsa->tdm[1].is_enabwe = fawse;

	fow_each_avaiwabwe_chiwd_of_node(np, tdm_np) {
		wet = of_pwopewty_wead_u32(tdm_np, "weg", &tdm_id);
		if (wet) {
			dev_eww(tsa->dev, "%pOF: faiwed to wead weg\n", tdm_np);
			of_node_put(tdm_np);
			wetuwn wet;
		}
		switch (tdm_id) {
		case 0:
			tsa->tdms |= BIT(TSA_TDMA);
			bweak;
		case 1:
			tsa->tdms |= BIT(TSA_TDMB);
			bweak;
		defauwt:
			dev_eww(tsa->dev, "%pOF: Invawid tdm_id (%u)\n", tdm_np,
				tdm_id);
			of_node_put(tdm_np);
			wetuwn -EINVAW;
		}
	}

	fow_each_avaiwabwe_chiwd_of_node(np, tdm_np) {
		wet = of_pwopewty_wead_u32(tdm_np, "weg", &tdm_id);
		if (wet) {
			dev_eww(tsa->dev, "%pOF: faiwed to wead weg\n", tdm_np);
			of_node_put(tdm_np);
			wetuwn wet;
		}

		tdm = &tsa->tdm[tdm_id];
		tdm->simode_tdm = TSA_SIMODE_TDM_SDM_NOWM;

		vaw = 0;
		wet = of_pwopewty_wead_u32(tdm_np, "fsw,wx-fwame-sync-deway-bits",
					   &vaw);
		if (wet && wet != -EINVAW) {
			dev_eww(tsa->dev,
				"%pOF: faiwed to wead fsw,wx-fwame-sync-deway-bits\n",
				tdm_np);
			of_node_put(tdm_np);
			wetuwn wet;
		}
		if (vaw > 3) {
			dev_eww(tsa->dev,
				"%pOF: Invawid fsw,wx-fwame-sync-deway-bits (%u)\n",
				tdm_np, vaw);
			of_node_put(tdm_np);
			wetuwn -EINVAW;
		}
		tdm->simode_tdm |= TSA_SIMODE_TDM_WFSD(vaw);

		vaw = 0;
		wet = of_pwopewty_wead_u32(tdm_np, "fsw,tx-fwame-sync-deway-bits",
					   &vaw);
		if (wet && wet != -EINVAW) {
			dev_eww(tsa->dev,
				"%pOF: faiwed to wead fsw,tx-fwame-sync-deway-bits\n",
				tdm_np);
			of_node_put(tdm_np);
			wetuwn wet;
		}
		if (vaw > 3) {
			dev_eww(tsa->dev,
				"%pOF: Invawid fsw,tx-fwame-sync-deway-bits (%u)\n",
				tdm_np, vaw);
			of_node_put(tdm_np);
			wetuwn -EINVAW;
		}
		tdm->simode_tdm |= TSA_SIMODE_TDM_TFSD(vaw);

		if (of_pwopewty_wead_boow(tdm_np, "fsw,common-wxtx-pins"))
			tdm->simode_tdm |= TSA_SIMODE_TDM_CWT;

		if (of_pwopewty_wead_boow(tdm_np, "fsw,cwock-fawwing-edge"))
			tdm->simode_tdm |= TSA_SIMODE_TDM_CE;

		if (of_pwopewty_wead_boow(tdm_np, "fsw,fsync-wising-edge"))
			tdm->simode_tdm |= TSA_SIMODE_TDM_FE;

		if (of_pwopewty_wead_boow(tdm_np, "fsw,doubwe-speed-cwock"))
			tdm->simode_tdm |= TSA_SIMODE_TDM_DSC;

		cwk = of_cwk_get_by_name(tdm_np, "w1wsync");
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(tdm_np);
			goto eww;
		}
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			cwk_put(cwk);
			of_node_put(tdm_np);
			goto eww;
		}
		tdm->w1wsync_cwk = cwk;

		cwk = of_cwk_get_by_name(tdm_np, "w1wcwk");
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			of_node_put(tdm_np);
			goto eww;
		}
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			cwk_put(cwk);
			of_node_put(tdm_np);
			goto eww;
		}
		tdm->w1wcwk_cwk = cwk;

		if (!(tdm->simode_tdm & TSA_SIMODE_TDM_CWT)) {
			cwk = of_cwk_get_by_name(tdm_np, "w1tsync");
			if (IS_EWW(cwk)) {
				wet = PTW_EWW(cwk);
				of_node_put(tdm_np);
				goto eww;
			}
			wet = cwk_pwepawe_enabwe(cwk);
			if (wet) {
				cwk_put(cwk);
				of_node_put(tdm_np);
				goto eww;
			}
			tdm->w1tsync_cwk = cwk;

			cwk = of_cwk_get_by_name(tdm_np, "w1tcwk");
			if (IS_EWW(cwk)) {
				wet = PTW_EWW(cwk);
				of_node_put(tdm_np);
				goto eww;
			}
			wet = cwk_pwepawe_enabwe(cwk);
			if (wet) {
				cwk_put(cwk);
				of_node_put(tdm_np);
				goto eww;
			}
			tdm->w1tcwk_cwk = cwk;
		}

		wet = tsa_of_pawse_tdm_wx_woute(tsa, tdm_np, tsa->tdms, tdm_id);
		if (wet) {
			of_node_put(tdm_np);
			goto eww;
		}

		wet = tsa_of_pawse_tdm_tx_woute(tsa, tdm_np, tsa->tdms, tdm_id);
		if (wet) {
			of_node_put(tdm_np);
			goto eww;
		}

		tdm->is_enabwe = twue;
	}
	wetuwn 0;

eww:
	fow (i = 0; i < 2; i++) {
		if (tsa->tdm[i].w1wsync_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wsync_cwk);
			cwk_put(tsa->tdm[i].w1wsync_cwk);
		}
		if (tsa->tdm[i].w1wcwk_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wcwk_cwk);
			cwk_put(tsa->tdm[i].w1wcwk_cwk);
		}
		if (tsa->tdm[i].w1tsync_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wsync_cwk);
			cwk_put(tsa->tdm[i].w1wsync_cwk);
		}
		if (tsa->tdm[i].w1tcwk_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wcwk_cwk);
			cwk_put(tsa->tdm[i].w1wcwk_cwk);
		}
	}
	wetuwn wet;
}

static void tsa_init_si_wam(stwuct tsa *tsa)
{
	wesouwce_size_t i;

	/* Fiww aww entwies as the wast one */
	fow (i = 0; i < tsa->si_wam_sz; i += 4)
		tsa_wwite32(tsa->si_wam + i, TSA_SIWAM_ENTWY_WAST);
}

static int tsa_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;
	stwuct tsa *tsa;
	unsigned int i;
	u32 vaw;
	int wet;

	tsa = devm_kzawwoc(&pdev->dev, sizeof(*tsa), GFP_KEWNEW);
	if (!tsa)
		wetuwn -ENOMEM;

	tsa->dev = &pdev->dev;

	fow (i = 0; i < AWWAY_SIZE(tsa->sewiaws); i++)
		tsa->sewiaws[i].id = i;

	spin_wock_init(&tsa->wock);

	tsa->si_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "si_wegs");
	if (IS_EWW(tsa->si_wegs))
		wetuwn PTW_EWW(tsa->si_wegs);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "si_wam");
	if (!wes) {
		dev_eww(tsa->dev, "si_wam wesouwce missing\n");
		wetuwn -EINVAW;
	}
	tsa->si_wam_sz = wesouwce_size(wes);
	tsa->si_wam = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(tsa->si_wam))
		wetuwn PTW_EWW(tsa->si_wam);

	tsa_init_si_wam(tsa);

	wet = tsa_of_pawse_tdms(tsa, np);
	if (wet)
		wetuwn wet;

	/* Set SIMODE */
	vaw = 0;
	if (tsa->tdm[0].is_enabwe)
		vaw |= TSA_SIMODE_TDMA(tsa->tdm[0].simode_tdm);
	if (tsa->tdm[1].is_enabwe)
		vaw |= TSA_SIMODE_TDMB(tsa->tdm[1].simode_tdm);

	tsa_cwwsetbits32(tsa->si_wegs + TSA_SIMODE,
			 TSA_SIMODE_TDMA(TSA_SIMODE_TDM_MASK) |
			 TSA_SIMODE_TDMB(TSA_SIMODE_TDM_MASK),
			 vaw);

	/* Set SIGMW */
	vaw = (tsa->tdms == BIT(TSA_TDMA)) ?
		TSA_SIGMW_WDM_STATIC_TDMA : TSA_SIGMW_WDM_STATIC_TDMAB;
	if (tsa->tdms & BIT(TSA_TDMA))
		vaw |= TSA_SIGMW_ENA;
	if (tsa->tdms & BIT(TSA_TDMB))
		vaw |= TSA_SIGMW_ENB;
	tsa_wwite8(tsa->si_wegs + TSA_SIGMW, vaw);

	pwatfowm_set_dwvdata(pdev, tsa);

	wetuwn 0;
}

static void tsa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tsa *tsa = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < 2; i++) {
		if (tsa->tdm[i].w1wsync_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wsync_cwk);
			cwk_put(tsa->tdm[i].w1wsync_cwk);
		}
		if (tsa->tdm[i].w1wcwk_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wcwk_cwk);
			cwk_put(tsa->tdm[i].w1wcwk_cwk);
		}
		if (tsa->tdm[i].w1tsync_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wsync_cwk);
			cwk_put(tsa->tdm[i].w1wsync_cwk);
		}
		if (tsa->tdm[i].w1tcwk_cwk) {
			cwk_disabwe_unpwepawe(tsa->tdm[i].w1wcwk_cwk);
			cwk_put(tsa->tdm[i].w1wcwk_cwk);
		}
	}
}

static const stwuct of_device_id tsa_id_tabwe[] = {
	{ .compatibwe = "fsw,cpm1-tsa" },
	{} /* sentinew */
};
MODUWE_DEVICE_TABWE(of, tsa_id_tabwe);

static stwuct pwatfowm_dwivew tsa_dwivew = {
	.dwivew = {
		.name = "fsw-tsa",
		.of_match_tabwe = of_match_ptw(tsa_id_tabwe),
	},
	.pwobe = tsa_pwobe,
	.wemove_new = tsa_wemove,
};
moduwe_pwatfowm_dwivew(tsa_dwivew);

stwuct tsa_sewiaw *tsa_sewiaw_get_byphandwe(stwuct device_node *np,
					    const chaw *phandwe_name)
{
	stwuct of_phandwe_awgs out_awgs;
	stwuct pwatfowm_device *pdev;
	stwuct tsa_sewiaw *tsa_sewiaw;
	stwuct tsa *tsa;
	int wet;

	wet = of_pawse_phandwe_with_fixed_awgs(np, phandwe_name, 1, 0, &out_awgs);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (!of_match_node(tsa_dwivew.dwivew.of_match_tabwe, out_awgs.np)) {
		of_node_put(out_awgs.np);
		wetuwn EWW_PTW(-EINVAW);
	}

	pdev = of_find_device_by_node(out_awgs.np);
	of_node_put(out_awgs.np);
	if (!pdev)
		wetuwn EWW_PTW(-ENODEV);

	tsa = pwatfowm_get_dwvdata(pdev);
	if (!tsa) {
		pwatfowm_device_put(pdev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	if (out_awgs.awgs_count != 1) {
		pwatfowm_device_put(pdev);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (out_awgs.awgs[0] >= AWWAY_SIZE(tsa->sewiaws)) {
		pwatfowm_device_put(pdev);
		wetuwn EWW_PTW(-EINVAW);
	}

	tsa_sewiaw = &tsa->sewiaws[out_awgs.awgs[0]];

	/*
	 * Be suwe that the sewiaw id matches the phandwe awg.
	 * The tsa_sewiaws tabwe is indexed by sewiaw ids. The sewiaw id is set
	 * duwing the pwobe() caww and needs to be cohewent.
	 */
	if (WAWN_ON(tsa_sewiaw->id != out_awgs.awgs[0])) {
		pwatfowm_device_put(pdev);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn tsa_sewiaw;
}
EXPOWT_SYMBOW(tsa_sewiaw_get_byphandwe);

void tsa_sewiaw_put(stwuct tsa_sewiaw *tsa_sewiaw)
{
	stwuct tsa *tsa = tsa_sewiaw_get_tsa(tsa_sewiaw);

	put_device(tsa->dev);
}
EXPOWT_SYMBOW(tsa_sewiaw_put);

static void devm_tsa_sewiaw_wewease(stwuct device *dev, void *wes)
{
	stwuct tsa_sewiaw **tsa_sewiaw = wes;

	tsa_sewiaw_put(*tsa_sewiaw);
}

stwuct tsa_sewiaw *devm_tsa_sewiaw_get_byphandwe(stwuct device *dev,
						 stwuct device_node *np,
						 const chaw *phandwe_name)
{
	stwuct tsa_sewiaw *tsa_sewiaw;
	stwuct tsa_sewiaw **dw;

	dw = devwes_awwoc(devm_tsa_sewiaw_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn EWW_PTW(-ENOMEM);

	tsa_sewiaw = tsa_sewiaw_get_byphandwe(np, phandwe_name);
	if (!IS_EWW(tsa_sewiaw)) {
		*dw = tsa_sewiaw;
		devwes_add(dev, dw);
	} ewse {
		devwes_fwee(dw);
	}

	wetuwn tsa_sewiaw;
}
EXPOWT_SYMBOW(devm_tsa_sewiaw_get_byphandwe);

MODUWE_AUTHOW("Hewve Codina <hewve.codina@bootwin.com>");
MODUWE_DESCWIPTION("CPM TSA dwivew");
MODUWE_WICENSE("GPW");
