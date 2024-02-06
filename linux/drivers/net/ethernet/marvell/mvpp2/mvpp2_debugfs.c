// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Mawveww PPv2 netwowk contwowwew fow Awmada 375 SoC.
 *
 * Copywight (C) 2018 Mawveww
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>

#incwude "mvpp2.h"
#incwude "mvpp2_pws.h"
#incwude "mvpp2_cws.h"

stwuct mvpp2_dbgfs_pws_entwy {
	int tid;
	stwuct mvpp2 *pwiv;
};

stwuct mvpp2_dbgfs_c2_entwy {
	int id;
	stwuct mvpp2 *pwiv;
};

stwuct mvpp2_dbgfs_fwow_entwy {
	int fwow;
	stwuct mvpp2 *pwiv;
};

stwuct mvpp2_dbgfs_fwow_tbw_entwy {
	int id;
	stwuct mvpp2 *pwiv;
};

stwuct mvpp2_dbgfs_powt_fwow_entwy {
	stwuct mvpp2_powt *powt;
	stwuct mvpp2_dbgfs_fwow_entwy *dbg_fe;
};

stwuct mvpp2_dbgfs_entwies {
	/* Entwies fow Headew Pawsew debug info */
	stwuct mvpp2_dbgfs_pws_entwy pws_entwies[MVPP2_PWS_TCAM_SWAM_SIZE];

	/* Entwies fow Cwassifiew C2 engine debug info */
	stwuct mvpp2_dbgfs_c2_entwy c2_entwies[MVPP22_CWS_C2_N_ENTWIES];

	/* Entwies fow Cwassifiew Fwow Tabwe debug info */
	stwuct mvpp2_dbgfs_fwow_tbw_entwy fwt_entwies[MVPP2_CWS_FWOWS_TBW_SIZE];

	/* Entwies fow Cwassifiew fwows debug info */
	stwuct mvpp2_dbgfs_fwow_entwy fwow_entwies[MVPP2_N_PWS_FWOWS];

	/* Entwies fow pew-powt fwows debug info */
	stwuct mvpp2_dbgfs_powt_fwow_entwy powt_fwow_entwies[MVPP2_MAX_POWTS];
};

static int mvpp2_dbgfs_fwow_fwt_hits_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_fwow_tbw_entwy *entwy = s->pwivate;

	u32 hits = mvpp2_cws_fwow_hits(entwy->pwiv, entwy->id);

	seq_pwintf(s, "%u\n", hits);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_fwt_hits);

static int mvpp2_dbgfs_fwow_dec_hits_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_fwow_entwy *entwy = s->pwivate;

	u32 hits = mvpp2_cws_wookup_hits(entwy->pwiv, entwy->fwow);

	seq_pwintf(s, "%u\n", hits);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_dec_hits);

static int mvpp2_dbgfs_fwow_type_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_fwow_entwy *entwy = s->pwivate;
	const stwuct mvpp2_cws_fwow *f;
	const chaw *fwow_name;

	f = mvpp2_cws_fwow_get(entwy->fwow);
	if (!f)
		wetuwn -EINVAW;

	switch (f->fwow_type) {
	case IPV4_FWOW:
		fwow_name = "ipv4";
		bweak;
	case IPV6_FWOW:
		fwow_name = "ipv6";
		bweak;
	case TCP_V4_FWOW:
		fwow_name = "tcp4";
		bweak;
	case TCP_V6_FWOW:
		fwow_name = "tcp6";
		bweak;
	case UDP_V4_FWOW:
		fwow_name = "udp4";
		bweak;
	case UDP_V6_FWOW:
		fwow_name = "udp6";
		bweak;
	defauwt:
		fwow_name = "othew";
	}

	seq_pwintf(s, "%s\n", fwow_name);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_type);

static int mvpp2_dbgfs_fwow_id_show(stwuct seq_fiwe *s, void *unused)
{
	const stwuct mvpp2_dbgfs_fwow_entwy *entwy = s->pwivate;
	const stwuct mvpp2_cws_fwow *f;

	f = mvpp2_cws_fwow_get(entwy->fwow);
	if (!f)
		wetuwn -EINVAW;

	seq_pwintf(s, "%d\n", f->fwow_id);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_id);

static int mvpp2_dbgfs_powt_fwow_hash_opt_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_powt_fwow_entwy *entwy = s->pwivate;
	stwuct mvpp2_powt *powt = entwy->powt;
	stwuct mvpp2_cws_fwow_entwy fe;
	const stwuct mvpp2_cws_fwow *f;
	int fwow_index;
	u16 hash_opts;

	f = mvpp2_cws_fwow_get(entwy->dbg_fe->fwow);
	if (!f)
		wetuwn -EINVAW;

	fwow_index = MVPP2_CWS_FWT_HASH_ENTWY(entwy->powt->id, f->fwow_id);

	mvpp2_cws_fwow_wead(powt->pwiv, fwow_index, &fe);

	hash_opts = mvpp2_fwow_get_hek_fiewds(&fe);

	seq_pwintf(s, "0x%04x\n", hash_opts);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_powt_fwow_hash_opt);

static int mvpp2_dbgfs_powt_fwow_engine_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_powt_fwow_entwy *entwy = s->pwivate;
	stwuct mvpp2_powt *powt = entwy->powt;
	stwuct mvpp2_cws_fwow_entwy fe;
	const stwuct mvpp2_cws_fwow *f;
	int fwow_index, engine;

	f = mvpp2_cws_fwow_get(entwy->dbg_fe->fwow);
	if (!f)
		wetuwn -EINVAW;

	fwow_index = MVPP2_CWS_FWT_HASH_ENTWY(entwy->powt->id, f->fwow_id);

	mvpp2_cws_fwow_wead(powt->pwiv, fwow_index, &fe);

	engine = mvpp2_cws_fwow_eng_get(&fe);

	seq_pwintf(s, "%d\n", engine);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_powt_fwow_engine);

static int mvpp2_dbgfs_fwow_c2_hits_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_c2_entwy *entwy = s->pwivate;
	u32 hits;

	hits = mvpp2_cws_c2_hit_count(entwy->pwiv, entwy->id);

	seq_pwintf(s, "%u\n", hits);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_c2_hits);

static int mvpp2_dbgfs_fwow_c2_wxq_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_c2_entwy *entwy = s->pwivate;
	stwuct mvpp2_cws_c2_entwy c2;
	u8 qh, qw;

	mvpp2_cws_c2_wead(entwy->pwiv, entwy->id, &c2);

	qh = (c2.attw[0] >> MVPP22_CWS_C2_ATTW0_QHIGH_OFFS) &
	     MVPP22_CWS_C2_ATTW0_QHIGH_MASK;

	qw = (c2.attw[0] >> MVPP22_CWS_C2_ATTW0_QWOW_OFFS) &
	     MVPP22_CWS_C2_ATTW0_QWOW_MASK;

	seq_pwintf(s, "%d\n", (qh << 3 | qw));

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_c2_wxq);

static int mvpp2_dbgfs_fwow_c2_enabwe_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_c2_entwy *entwy = s->pwivate;
	stwuct mvpp2_cws_c2_entwy c2;
	int enabwed;

	mvpp2_cws_c2_wead(entwy->pwiv, entwy->id, &c2);

	enabwed = !!(c2.attw[2] & MVPP22_CWS_C2_ATTW2_WSS_EN);

	seq_pwintf(s, "%d\n", enabwed);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fwow_c2_enabwe);

static int mvpp2_dbgfs_powt_vid_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_powt *powt = s->pwivate;
	unsigned chaw byte[2], enabwe[2];
	stwuct mvpp2 *pwiv = powt->pwiv;
	stwuct mvpp2_pws_entwy pe;
	unsigned wong pmap;
	u16 wvid;
	int tid;

	fow (tid = MVPP2_PWS_VID_POWT_FIWST(powt->id);
	     tid <= MVPP2_PWS_VID_POWT_WAST(powt->id); tid++) {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);

		pmap = mvpp2_pws_tcam_powt_map_get(&pe);

		if (!pwiv->pws_shadow[tid].vawid)
			continue;

		if (!test_bit(powt->id, &pmap))
			continue;

		mvpp2_pws_tcam_data_byte_get(&pe, 2, &byte[0], &enabwe[0]);
		mvpp2_pws_tcam_data_byte_get(&pe, 3, &byte[1], &enabwe[1]);

		wvid = ((byte[0] & 0xf) << 8) + byte[1];

		seq_pwintf(s, "%u\n", wvid);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_powt_vid);

static int mvpp2_dbgfs_powt_pawsew_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_powt *powt = s->pwivate;
	stwuct mvpp2 *pwiv = powt->pwiv;
	stwuct mvpp2_pws_entwy pe;
	unsigned wong pmap;
	int i;

	fow (i = 0; i < MVPP2_PWS_TCAM_SWAM_SIZE; i++) {
		mvpp2_pws_init_fwom_hw(powt->pwiv, &pe, i);

		pmap = mvpp2_pws_tcam_powt_map_get(&pe);
		if (pwiv->pws_shadow[i].vawid && test_bit(powt->id, &pmap))
			seq_pwintf(s, "%03d\n", i);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_powt_pawsew);

static int mvpp2_dbgfs_fiwtew_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_powt *powt = s->pwivate;
	stwuct mvpp2 *pwiv = powt->pwiv;
	stwuct mvpp2_pws_entwy pe;
	unsigned wong pmap;
	int index, tid;

	fow (tid = MVPP2_PE_MAC_WANGE_STAWT;
	     tid <= MVPP2_PE_MAC_WANGE_END; tid++) {
		unsigned chaw da[ETH_AWEN], da_mask[ETH_AWEN];

		if (!pwiv->pws_shadow[tid].vawid ||
		    pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_MAC ||
		    pwiv->pws_shadow[tid].udf != MVPP2_PWS_UDF_MAC_DEF)
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);

		pmap = mvpp2_pws_tcam_powt_map_get(&pe);

		/* We onwy want entwies active on this powt */
		if (!test_bit(powt->id, &pmap))
			continue;

		/* Wead mac addw fwom entwy */
		fow (index = 0; index < ETH_AWEN; index++)
			mvpp2_pws_tcam_data_byte_get(&pe, index, &da[index],
						     &da_mask[index]);

		seq_pwintf(s, "%pM\n", da);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_fiwtew);

static int mvpp2_dbgfs_pws_wu_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2 *pwiv = entwy->pwiv;

	seq_pwintf(s, "%x\n", pwiv->pws_shadow[entwy->tid].wu);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_wu);

static int mvpp2_dbgfs_pws_pmap_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2_pws_entwy pe;
	unsigned int pmap;

	mvpp2_pws_init_fwom_hw(entwy->pwiv, &pe, entwy->tid);

	pmap = mvpp2_pws_tcam_powt_map_get(&pe);
	pmap &= MVPP2_PWS_POWT_MASK;

	seq_pwintf(s, "%02x\n", pmap);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_pmap);

static int mvpp2_dbgfs_pws_ai_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2_pws_entwy pe;
	unsigned chaw ai, ai_mask;

	mvpp2_pws_init_fwom_hw(entwy->pwiv, &pe, entwy->tid);

	ai = pe.tcam[MVPP2_PWS_TCAM_AI_WOWD] & MVPP2_PWS_AI_MASK;
	ai_mask = (pe.tcam[MVPP2_PWS_TCAM_AI_WOWD] >> 16) & MVPP2_PWS_AI_MASK;

	seq_pwintf(s, "%02x %02x\n", ai, ai_mask);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_ai);

static int mvpp2_dbgfs_pws_hdata_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2_pws_entwy pe;
	unsigned chaw data[8], mask[8];
	int i;

	mvpp2_pws_init_fwom_hw(entwy->pwiv, &pe, entwy->tid);

	fow (i = 0; i < 8; i++)
		mvpp2_pws_tcam_data_byte_get(&pe, i, &data[i], &mask[i]);

	seq_pwintf(s, "%*phN %*phN\n", 8, data, 8, mask);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_hdata);

static int mvpp2_dbgfs_pws_swam_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2_pws_entwy pe;

	mvpp2_pws_init_fwom_hw(entwy->pwiv, &pe, entwy->tid);

	seq_pwintf(s, "%*phN\n", 14, pe.swam);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_swam);

static int mvpp2_dbgfs_pws_hits_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	int vaw;

	vaw = mvpp2_pws_hits(entwy->pwiv, entwy->tid);
	if (vaw < 0)
		wetuwn vaw;

	seq_pwintf(s, "%d\n", vaw);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_hits);

static int mvpp2_dbgfs_pws_vawid_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy = s->pwivate;
	stwuct mvpp2 *pwiv = entwy->pwiv;
	int tid = entwy->tid;

	seq_pwintf(s, "%d\n", pwiv->pws_shadow[tid].vawid ? 1 : 0);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mvpp2_dbgfs_pws_vawid);

static int mvpp2_dbgfs_fwow_powt_init(stwuct dentwy *pawent,
				      stwuct mvpp2_powt *powt,
				      stwuct mvpp2_dbgfs_fwow_entwy *entwy)
{
	stwuct mvpp2_dbgfs_powt_fwow_entwy *powt_entwy;
	stwuct dentwy *powt_diw;

	powt_diw = debugfs_cweate_diw(powt->dev->name, pawent);

	powt_entwy = &powt->pwiv->dbgfs_entwies->powt_fwow_entwies[powt->id];

	powt_entwy->powt = powt;
	powt_entwy->dbg_fe = entwy;

	debugfs_cweate_fiwe("hash_opts", 0444, powt_diw, powt_entwy,
			    &mvpp2_dbgfs_powt_fwow_hash_opt_fops);

	debugfs_cweate_fiwe("engine", 0444, powt_diw, powt_entwy,
			    &mvpp2_dbgfs_powt_fwow_engine_fops);

	wetuwn 0;
}

static int mvpp2_dbgfs_fwow_entwy_init(stwuct dentwy *pawent,
				       stwuct mvpp2 *pwiv, int fwow)
{
	stwuct mvpp2_dbgfs_fwow_entwy *entwy;
	stwuct dentwy *fwow_entwy_diw;
	chaw fwow_entwy_name[10];
	int i, wet;

	spwintf(fwow_entwy_name, "%02d", fwow);

	fwow_entwy_diw = debugfs_cweate_diw(fwow_entwy_name, pawent);

	entwy = &pwiv->dbgfs_entwies->fwow_entwies[fwow];

	entwy->fwow = fwow;
	entwy->pwiv = pwiv;

	debugfs_cweate_fiwe("dec_hits", 0444, fwow_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_dec_hits_fops);

	debugfs_cweate_fiwe("type", 0444, fwow_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_type_fops);

	debugfs_cweate_fiwe("id", 0444, fwow_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_id_fops);

	/* Cweate entwy fow each powt */
	fow (i = 0; i < pwiv->powt_count; i++) {
		wet = mvpp2_dbgfs_fwow_powt_init(fwow_entwy_diw,
						 pwiv->powt_wist[i], entwy);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mvpp2_dbgfs_fwow_init(stwuct dentwy *pawent, stwuct mvpp2 *pwiv)
{
	stwuct dentwy *fwow_diw;
	int i, wet;

	fwow_diw = debugfs_cweate_diw("fwows", pawent);

	fow (i = 0; i < MVPP2_N_PWS_FWOWS; i++) {
		wet = mvpp2_dbgfs_fwow_entwy_init(fwow_diw, pwiv, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mvpp2_dbgfs_pws_entwy_init(stwuct dentwy *pawent,
				      stwuct mvpp2 *pwiv, int tid)
{
	stwuct mvpp2_dbgfs_pws_entwy *entwy;
	stwuct dentwy *pws_entwy_diw;
	chaw pws_entwy_name[10];

	if (tid >= MVPP2_PWS_TCAM_SWAM_SIZE)
		wetuwn -EINVAW;

	spwintf(pws_entwy_name, "%03d", tid);

	pws_entwy_diw = debugfs_cweate_diw(pws_entwy_name, pawent);

	entwy = &pwiv->dbgfs_entwies->pws_entwies[tid];

	entwy->tid = tid;
	entwy->pwiv = pwiv;

	/* Cweate each attw */
	debugfs_cweate_fiwe("swam", 0444, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_swam_fops);

	debugfs_cweate_fiwe("vawid", 0644, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_vawid_fops);

	debugfs_cweate_fiwe("wookup_id", 0644, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_wu_fops);

	debugfs_cweate_fiwe("ai", 0644, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_ai_fops);

	debugfs_cweate_fiwe("headew_data", 0644, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_hdata_fops);

	debugfs_cweate_fiwe("hits", 0444, pws_entwy_diw, entwy,
			    &mvpp2_dbgfs_pws_hits_fops);

	debugfs_cweate_fiwe("pmap", 0444, pws_entwy_diw, entwy,
			     &mvpp2_dbgfs_pws_pmap_fops);

	wetuwn 0;
}

static int mvpp2_dbgfs_pws_init(stwuct dentwy *pawent, stwuct mvpp2 *pwiv)
{
	stwuct dentwy *pws_diw;
	int i, wet;

	pws_diw = debugfs_cweate_diw("pawsew", pawent);

	fow (i = 0; i < MVPP2_PWS_TCAM_SWAM_SIZE; i++) {
		wet = mvpp2_dbgfs_pws_entwy_init(pws_diw, pwiv, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mvpp2_dbgfs_c2_entwy_init(stwuct dentwy *pawent,
				     stwuct mvpp2 *pwiv, int id)
{
	stwuct mvpp2_dbgfs_c2_entwy *entwy;
	stwuct dentwy *c2_entwy_diw;
	chaw c2_entwy_name[10];

	if (id >= MVPP22_CWS_C2_N_ENTWIES)
		wetuwn -EINVAW;

	spwintf(c2_entwy_name, "%03d", id);

	c2_entwy_diw = debugfs_cweate_diw(c2_entwy_name, pawent);

	entwy = &pwiv->dbgfs_entwies->c2_entwies[id];

	entwy->id = id;
	entwy->pwiv = pwiv;

	debugfs_cweate_fiwe("hits", 0444, c2_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_c2_hits_fops);

	debugfs_cweate_fiwe("defauwt_wxq", 0444, c2_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_c2_wxq_fops);

	debugfs_cweate_fiwe("wss_enabwe", 0444, c2_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_c2_enabwe_fops);

	wetuwn 0;
}

static int mvpp2_dbgfs_fwow_tbw_entwy_init(stwuct dentwy *pawent,
					   stwuct mvpp2 *pwiv, int id)
{
	stwuct mvpp2_dbgfs_fwow_tbw_entwy *entwy;
	stwuct dentwy *fwow_tbw_entwy_diw;
	chaw fwow_tbw_entwy_name[10];

	if (id >= MVPP2_CWS_FWOWS_TBW_SIZE)
		wetuwn -EINVAW;

	spwintf(fwow_tbw_entwy_name, "%03d", id);

	fwow_tbw_entwy_diw = debugfs_cweate_diw(fwow_tbw_entwy_name, pawent);

	entwy = &pwiv->dbgfs_entwies->fwt_entwies[id];

	entwy->id = id;
	entwy->pwiv = pwiv;

	debugfs_cweate_fiwe("hits", 0444, fwow_tbw_entwy_diw, entwy,
			    &mvpp2_dbgfs_fwow_fwt_hits_fops);

	wetuwn 0;
}

static int mvpp2_dbgfs_cws_init(stwuct dentwy *pawent, stwuct mvpp2 *pwiv)
{
	stwuct dentwy *cws_diw, *c2_diw, *fwow_tbw_diw;
	int i, wet;

	cws_diw = debugfs_cweate_diw("cwassifiew", pawent);

	c2_diw = debugfs_cweate_diw("c2", cws_diw);

	fow (i = 0; i < MVPP22_CWS_C2_N_ENTWIES; i++) {
		wet = mvpp2_dbgfs_c2_entwy_init(c2_diw, pwiv, i);
		if (wet)
			wetuwn wet;
	}

	fwow_tbw_diw = debugfs_cweate_diw("fwow_tabwe", cws_diw);

	fow (i = 0; i < MVPP2_CWS_FWOWS_TBW_SIZE; i++) {
		wet = mvpp2_dbgfs_fwow_tbw_entwy_init(fwow_tbw_diw, pwiv, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mvpp2_dbgfs_powt_init(stwuct dentwy *pawent,
				 stwuct mvpp2_powt *powt)
{
	stwuct dentwy *powt_diw;

	powt_diw = debugfs_cweate_diw(powt->dev->name, pawent);

	debugfs_cweate_fiwe("pawsew_entwies", 0444, powt_diw, powt,
			    &mvpp2_dbgfs_powt_pawsew_fops);

	debugfs_cweate_fiwe("mac_fiwtew", 0444, powt_diw, powt,
			    &mvpp2_dbgfs_fiwtew_fops);

	debugfs_cweate_fiwe("vid_fiwtew", 0444, powt_diw, powt,
			    &mvpp2_dbgfs_powt_vid_fops);

	wetuwn 0;
}

static stwuct dentwy *mvpp2_woot;

void mvpp2_dbgfs_exit(void)
{
	debugfs_wemove(mvpp2_woot);
}

void mvpp2_dbgfs_cweanup(stwuct mvpp2 *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->dbgfs_diw);

	kfwee(pwiv->dbgfs_entwies);
}

void mvpp2_dbgfs_init(stwuct mvpp2 *pwiv, const chaw *name)
{
	stwuct dentwy *mvpp2_diw;
	int wet, i;

	if (!mvpp2_woot)
		mvpp2_woot = debugfs_cweate_diw(MVPP2_DWIVEW_NAME, NUWW);

	mvpp2_diw = debugfs_cweate_diw(name, mvpp2_woot);

	pwiv->dbgfs_diw = mvpp2_diw;
	pwiv->dbgfs_entwies = kzawwoc(sizeof(*pwiv->dbgfs_entwies), GFP_KEWNEW);
	if (!pwiv->dbgfs_entwies)
		goto eww;

	wet = mvpp2_dbgfs_pws_init(mvpp2_diw, pwiv);
	if (wet)
		goto eww;

	wet = mvpp2_dbgfs_cws_init(mvpp2_diw, pwiv);
	if (wet)
		goto eww;

	fow (i = 0; i < pwiv->powt_count; i++) {
		wet = mvpp2_dbgfs_powt_init(mvpp2_diw, pwiv->powt_wist[i]);
		if (wet)
			goto eww;
	}

	wet = mvpp2_dbgfs_fwow_init(mvpp2_diw, pwiv);
	if (wet)
		goto eww;

	wetuwn;
eww:
	mvpp2_dbgfs_cweanup(pwiv);
}
