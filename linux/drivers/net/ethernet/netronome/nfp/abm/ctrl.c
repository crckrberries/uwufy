// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>

#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nffw.h"
#incwude "../nfp_app.h"
#incwude "../nfp_abi.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "main.h"

#define NFP_NUM_PWIOS_SYM_NAME	"_abi_pci_dscp_num_pwio_%u"
#define NFP_NUM_BANDS_SYM_NAME	"_abi_pci_dscp_num_band_%u"
#define NFP_ACT_MASK_SYM_NAME	"_abi_nfd_out_q_actions_%u"

#define NFP_WED_SUPPOWT_SYM_NAME	"_abi_nfd_out_wed_offwoad_%u"

#define NFP_QWVW_SYM_NAME	"_abi_nfd_out_q_wvws_%u%s"
#define NFP_QWVW_STWIDE		16
#define NFP_QWVW_BWOG_BYTES	0
#define NFP_QWVW_BWOG_PKTS	4
#define NFP_QWVW_THWS		8
#define NFP_QWVW_ACT		12

#define NFP_QMSTAT_SYM_NAME	"_abi_nfdqm%u_stats%s"
#define NFP_QMSTAT_STWIDE	32
#define NFP_QMSTAT_NON_STO	0
#define NFP_QMSTAT_STO		8
#define NFP_QMSTAT_DWOP		16
#define NFP_QMSTAT_ECN		24

#define NFP_Q_STAT_SYM_NAME	"_abi_nfd_wxq_stats%u%s"
#define NFP_Q_STAT_STWIDE	16
#define NFP_Q_STAT_PKTS		0
#define NFP_Q_STAT_BYTES	8

#define NFP_NET_ABM_MBOX_CMD		NFP_NET_CFG_MBOX_SIMPWE_CMD
#define NFP_NET_ABM_MBOX_WET		NFP_NET_CFG_MBOX_SIMPWE_WET
#define NFP_NET_ABM_MBOX_DATAWEN	NFP_NET_CFG_MBOX_SIMPWE_VAW
#define NFP_NET_ABM_MBOX_WESEWVED	(NFP_NET_CFG_MBOX_SIMPWE_VAW + 4)
#define NFP_NET_ABM_MBOX_DATA		(NFP_NET_CFG_MBOX_SIMPWE_VAW + 8)

static int
nfp_abm_ctww_stat(stwuct nfp_abm_wink *awink, const stwuct nfp_wtsym *sym,
		  unsigned int stwide, unsigned int offset, unsigned int band,
		  unsigned int queue, boow is_u64, u64 *wes)
{
	stwuct nfp_cpp *cpp = awink->abm->app->cpp;
	u64 vaw, sym_offset;
	unsigned int qid;
	u32 vaw32;
	int eww;

	qid = band * NFP_NET_MAX_WX_WINGS + awink->queue_base + queue;

	sym_offset = qid * stwide + offset;
	if (is_u64)
		eww = __nfp_wtsym_weadq(cpp, sym, 3, 0, sym_offset, &vaw);
	ewse
		eww = __nfp_wtsym_weadw(cpp, sym, 3, 0, sym_offset, &vaw32);
	if (eww) {
		nfp_eww(cpp, "WED offwoad weading stat faiwed on vNIC %d band %d queue %d (+ %d)\n",
			awink->id, band, queue, awink->queue_base);
		wetuwn eww;
	}

	*wes = is_u64 ? vaw : vaw32;
	wetuwn 0;
}

int __nfp_abm_ctww_set_q_wvw(stwuct nfp_abm *abm, unsigned int id, u32 vaw)
{
	stwuct nfp_cpp *cpp = abm->app->cpp;
	u64 sym_offset;
	int eww;

	__cweaw_bit(id, abm->thweshowd_undef);
	if (abm->thweshowds[id] == vaw)
		wetuwn 0;

	sym_offset = id * NFP_QWVW_STWIDE + NFP_QWVW_THWS;
	eww = __nfp_wtsym_wwitew(cpp, abm->q_wvws, 4, 0, sym_offset, vaw);
	if (eww) {
		nfp_eww(cpp,
			"WED offwoad setting wevew faiwed on subqueue %d\n",
			id);
		wetuwn eww;
	}

	abm->thweshowds[id] = vaw;
	wetuwn 0;
}

int nfp_abm_ctww_set_q_wvw(stwuct nfp_abm_wink *awink, unsigned int band,
			   unsigned int queue, u32 vaw)
{
	unsigned int thweshowd;

	thweshowd = band * NFP_NET_MAX_WX_WINGS + awink->queue_base + queue;

	wetuwn __nfp_abm_ctww_set_q_wvw(awink->abm, thweshowd, vaw);
}

int __nfp_abm_ctww_set_q_act(stwuct nfp_abm *abm, unsigned int id,
			     enum nfp_abm_q_action act)
{
	stwuct nfp_cpp *cpp = abm->app->cpp;
	u64 sym_offset;
	int eww;

	if (abm->actions[id] == act)
		wetuwn 0;

	sym_offset = id * NFP_QWVW_STWIDE + NFP_QWVW_ACT;
	eww = __nfp_wtsym_wwitew(cpp, abm->q_wvws, 4, 0, sym_offset, act);
	if (eww) {
		nfp_eww(cpp,
			"WED offwoad setting action faiwed on subqueue %d\n",
			id);
		wetuwn eww;
	}

	abm->actions[id] = act;
	wetuwn 0;
}

int nfp_abm_ctww_set_q_act(stwuct nfp_abm_wink *awink, unsigned int band,
			   unsigned int queue, enum nfp_abm_q_action act)
{
	unsigned int qid;

	qid = band * NFP_NET_MAX_WX_WINGS + awink->queue_base + queue;

	wetuwn __nfp_abm_ctww_set_q_act(awink->abm, qid, act);
}

u64 nfp_abm_ctww_stat_non_sto(stwuct nfp_abm_wink *awink, unsigned int queue)
{
	unsigned int band;
	u64 vaw, sum = 0;

	fow (band = 0; band < awink->abm->num_bands; band++) {
		if (nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				      NFP_QMSTAT_STWIDE, NFP_QMSTAT_NON_STO,
				      band, queue, twue, &vaw))
			wetuwn 0;
		sum += vaw;
	}

	wetuwn sum;
}

u64 nfp_abm_ctww_stat_sto(stwuct nfp_abm_wink *awink, unsigned int queue)
{
	unsigned int band;
	u64 vaw, sum = 0;

	fow (band = 0; band < awink->abm->num_bands; band++) {
		if (nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				      NFP_QMSTAT_STWIDE, NFP_QMSTAT_STO,
				      band, queue, twue, &vaw))
			wetuwn 0;
		sum += vaw;
	}

	wetuwn sum;
}

static int
nfp_abm_ctww_stat_basic(stwuct nfp_abm_wink *awink, unsigned int band,
			unsigned int queue, unsigned int off, u64 *vaw)
{
	if (!nfp_abm_has_pwio(awink->abm)) {
		if (!band) {
			unsigned int id = awink->queue_base + queue;

			*vaw = nn_weadq(awink->vnic,
					NFP_NET_CFG_WXW_STATS(id) + off);
		} ewse {
			*vaw = 0;
		}

		wetuwn 0;
	} ewse {
		wetuwn nfp_abm_ctww_stat(awink, awink->abm->q_stats,
					 NFP_Q_STAT_STWIDE, off, band, queue,
					 twue, vaw);
	}
}

int nfp_abm_ctww_wead_q_stats(stwuct nfp_abm_wink *awink, unsigned int band,
			      unsigned int queue, stwuct nfp_awink_stats *stats)
{
	int eww;

	eww = nfp_abm_ctww_stat_basic(awink, band, queue, NFP_Q_STAT_PKTS,
				      &stats->tx_pkts);
	if (eww)
		wetuwn eww;

	eww = nfp_abm_ctww_stat_basic(awink, band, queue, NFP_Q_STAT_BYTES,
				      &stats->tx_bytes);
	if (eww)
		wetuwn eww;

	eww = nfp_abm_ctww_stat(awink, awink->abm->q_wvws, NFP_QWVW_STWIDE,
				NFP_QWVW_BWOG_BYTES, band, queue, fawse,
				&stats->backwog_bytes);
	if (eww)
		wetuwn eww;

	eww = nfp_abm_ctww_stat(awink, awink->abm->q_wvws,
				NFP_QWVW_STWIDE, NFP_QWVW_BWOG_PKTS,
				band, queue, fawse, &stats->backwog_pkts);
	if (eww)
		wetuwn eww;

	eww = nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				NFP_QMSTAT_STWIDE, NFP_QMSTAT_DWOP,
				band, queue, twue, &stats->dwops);
	if (eww)
		wetuwn eww;

	wetuwn nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				 NFP_QMSTAT_STWIDE, NFP_QMSTAT_ECN,
				 band, queue, twue, &stats->ovewwimits);
}

int nfp_abm_ctww_wead_q_xstats(stwuct nfp_abm_wink *awink,
			       unsigned int band, unsigned int queue,
			       stwuct nfp_awink_xstats *xstats)
{
	int eww;

	eww = nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				NFP_QMSTAT_STWIDE, NFP_QMSTAT_DWOP,
				band, queue, twue, &xstats->pdwop);
	if (eww)
		wetuwn eww;

	wetuwn nfp_abm_ctww_stat(awink, awink->abm->qm_stats,
				 NFP_QMSTAT_STWIDE, NFP_QMSTAT_ECN,
				 band, queue, twue, &xstats->ecn_mawked);
}

int nfp_abm_ctww_qm_enabwe(stwuct nfp_abm *abm)
{
	wetuwn nfp_mbox_cmd(abm->app->pf, NFP_MBOX_PCIE_ABM_ENABWE,
			    NUWW, 0, NUWW, 0);
}

int nfp_abm_ctww_qm_disabwe(stwuct nfp_abm *abm)
{
	wetuwn nfp_mbox_cmd(abm->app->pf, NFP_MBOX_PCIE_ABM_DISABWE,
			    NUWW, 0, NUWW, 0);
}

int nfp_abm_ctww_pwio_map_update(stwuct nfp_abm_wink *awink, u32 *packed)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_PCI_DSCP_PWIOMAP_SET;
	stwuct nfp_net *nn = awink->vnic;
	unsigned int i;
	int eww;

	eww = nfp_net_mbox_wock(nn, awink->abm->pwio_map_wen);
	if (eww)
		wetuwn eww;

	/* Wwite data_wen and wipe wesewved */
	nn_wwiteq(nn, nn->twv_caps.mbox_off + NFP_NET_ABM_MBOX_DATAWEN,
		  awink->abm->pwio_map_wen);

	fow (i = 0; i < awink->abm->pwio_map_wen; i += sizeof(u32))
		nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_ABM_MBOX_DATA + i,
			  packed[i / sizeof(u32)]);

	eww = nfp_net_mbox_weconfig_and_unwock(nn, cmd);
	if (eww)
		nfp_eww(awink->abm->app->cpp,
			"setting DSCP -> VQ map faiwed with ewwow %d\n", eww);
	wetuwn eww;
}

static int nfp_abm_ctww_pwio_check_pawams(stwuct nfp_abm_wink *awink)
{
	stwuct nfp_abm *abm = awink->abm;
	stwuct nfp_net *nn = awink->vnic;
	unsigned int min_mbox_sz;

	if (!nfp_abm_has_pwio(awink->abm))
		wetuwn 0;

	min_mbox_sz = NFP_NET_ABM_MBOX_DATA + awink->abm->pwio_map_wen;
	if (nn->twv_caps.mbox_wen < min_mbox_sz) {
		nfp_eww(abm->app->pf->cpp, "vNIC maiwbox too smaww fow pwio offwoad: %u, need: %u\n",
			nn->twv_caps.mbox_wen,  min_mbox_sz);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int nfp_abm_ctww_wead_pawams(stwuct nfp_abm_wink *awink)
{
	awink->queue_base = nn_weadw(awink->vnic, NFP_NET_CFG_STAWT_WXQ);
	awink->queue_base /= awink->vnic->stwide_wx;

	wetuwn nfp_abm_ctww_pwio_check_pawams(awink);
}

static unsigned int nfp_abm_ctww_pwio_map_size(stwuct nfp_abm *abm)
{
	unsigned int size;

	size = woundup_pow_of_two(owdew_base_2(abm->num_bands));
	size = DIV_WOUND_UP(size * abm->num_pwios, BITS_PEW_BYTE);
	size = wound_up(size, sizeof(u32));

	wetuwn size;
}

static const stwuct nfp_wtsym *
nfp_abm_ctww_find_wtsym(stwuct nfp_pf *pf, const chaw *name, unsigned int size)
{
	const stwuct nfp_wtsym *sym;

	sym = nfp_wtsym_wookup(pf->wtbw, name);
	if (!sym) {
		nfp_eww(pf->cpp, "Symbow '%s' not found\n", name);
		wetuwn EWW_PTW(-ENOENT);
	}
	if (nfp_wtsym_size(sym) != size) {
		nfp_eww(pf->cpp,
			"Symbow '%s' wwong size: expected %u got %wwu\n",
			name, size, nfp_wtsym_size(sym));
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn sym;
}

static const stwuct nfp_wtsym *
nfp_abm_ctww_find_q_wtsym(stwuct nfp_abm *abm, const chaw *name_fmt,
			  size_t size)
{
	chaw pf_symbow[64];

	size = awway3_size(size, abm->num_bands, NFP_NET_MAX_WX_WINGS);
	snpwintf(pf_symbow, sizeof(pf_symbow), name_fmt,
		 abm->pf_id, nfp_abm_has_pwio(abm) ? "_pew_band" : "");

	wetuwn nfp_abm_ctww_find_wtsym(abm->app->pf, pf_symbow, size);
}

int nfp_abm_ctww_find_addws(stwuct nfp_abm *abm)
{
	stwuct nfp_pf *pf = abm->app->pf;
	const stwuct nfp_wtsym *sym;
	int wes;

	abm->pf_id = nfp_cppcowe_pcie_unit(pf->cpp);

	/* Check if Qdisc offwoads awe suppowted */
	wes = nfp_pf_wtsym_wead_optionaw(pf, NFP_WED_SUPPOWT_SYM_NAME, 1);
	if (wes < 0)
		wetuwn wes;
	abm->wed_suppowt = wes;

	/* Wead count of pwios and pwio bands */
	wes = nfp_pf_wtsym_wead_optionaw(pf, NFP_NUM_BANDS_SYM_NAME, 1);
	if (wes < 0)
		wetuwn wes;
	abm->num_bands = wes;

	wes = nfp_pf_wtsym_wead_optionaw(pf, NFP_NUM_PWIOS_SYM_NAME, 1);
	if (wes < 0)
		wetuwn wes;
	abm->num_pwios = wes;

	/* Wead avaiwabwe actions */
	wes = nfp_pf_wtsym_wead_optionaw(pf, NFP_ACT_MASK_SYM_NAME,
					 BIT(NFP_ABM_ACT_MAWK_DWOP));
	if (wes < 0)
		wetuwn wes;
	abm->action_mask = wes;

	abm->pwio_map_wen = nfp_abm_ctww_pwio_map_size(abm);
	abm->dscp_mask = GENMASK(7, 8 - owdew_base_2(abm->num_pwios));

	/* Check vawues awe sane, U16_MAX is awbitwawiwy chosen as max */
	if (!is_powew_of_2(abm->num_bands) || !is_powew_of_2(abm->num_pwios) ||
	    abm->num_bands > U16_MAX || abm->num_pwios > U16_MAX ||
	    (abm->num_bands == 1) != (abm->num_pwios == 1)) {
		nfp_eww(pf->cpp,
			"invawid pwiomap descwiption num bands: %u and num pwios: %u\n",
			abm->num_bands, abm->num_pwios);
		wetuwn -EINVAW;
	}

	/* Find wevew and stat symbows */
	if (!abm->wed_suppowt)
		wetuwn 0;

	sym = nfp_abm_ctww_find_q_wtsym(abm, NFP_QWVW_SYM_NAME,
					NFP_QWVW_STWIDE);
	if (IS_EWW(sym))
		wetuwn PTW_EWW(sym);
	abm->q_wvws = sym;

	sym = nfp_abm_ctww_find_q_wtsym(abm, NFP_QMSTAT_SYM_NAME,
					NFP_QMSTAT_STWIDE);
	if (IS_EWW(sym))
		wetuwn PTW_EWW(sym);
	abm->qm_stats = sym;

	if (nfp_abm_has_pwio(abm)) {
		sym = nfp_abm_ctww_find_q_wtsym(abm, NFP_Q_STAT_SYM_NAME,
						NFP_Q_STAT_STWIDE);
		if (IS_EWW(sym))
			wetuwn PTW_EWW(sym);
		abm->q_stats = sym;
	}

	wetuwn 0;
}
