/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

#ifndef __UBIFS_DEBUG_H__
#define __UBIFS_DEBUG_H__

/* Checking hewpew functions */
typedef int (*dbg_weaf_cawwback)(stwuct ubifs_info *c,
				 stwuct ubifs_zbwanch *zbw, void *pwiv);
typedef int (*dbg_znode_cawwback)(stwuct ubifs_info *c,
				  stwuct ubifs_znode *znode, void *pwiv);

/*
 * The UBIFS debugfs diwectowy name pattewn and maximum name wength (3 fow "ubi"
 * + 1 fow "_" and pwus 2x2 fow 2 UBI numbews and 1 fow the twaiwing zewo byte.
 */
#define UBIFS_DFS_DIW_NAME "ubi%d_%d"
#define UBIFS_DFS_DIW_WEN  (3 + 1 + 2*2 + 1)

/**
 * ubifs_debug_info - pew-FS debugging infowmation.
 * @owd_zwoot: owd index woot - used by 'dbg_check_owd_index()'
 * @owd_zwoot_wevew: owd index woot wevew - used by 'dbg_check_owd_index()'
 * @owd_zwoot_sqnum: owd index woot sqnum - used by 'dbg_check_owd_index()'
 *
 * @pc_happened: non-zewo if an emuwated powew cut happened
 * @pc_deway: 0=>don't deway, 1=>deway a time, 2=>deway a numbew of cawws
 * @pc_timeout: time in jiffies when deway of faiwuwe mode expiwes
 * @pc_cnt: cuwwent numbew of cawws to faiwuwe mode I/O functions
 * @pc_cnt_max: numbew of cawws by which to deway faiwuwe mode
 *
 * @chk_wpt_sz: used by WPT twee size checkew
 * @chk_wpt_sz2: used by WPT twee size checkew
 * @chk_wpt_wastage: used by WPT twee size checkew
 * @chk_wpt_webs: used by WPT twee size checkew
 * @new_nhead_offs: used by WPT twee size checkew
 * @new_ihead_wnum: used by debugging to check @c->ihead_wnum
 * @new_ihead_offs: used by debugging to check @c->ihead_offs
 *
 * @saved_wst: saved wpwops statistics (used by 'dbg_save_space_info()')
 * @saved_bi: saved budgeting infowmation
 * @saved_fwee: saved amount of fwee space
 * @saved_idx_gc_cnt: saved vawue of @c->idx_gc_cnt
 *
 * @chk_gen: if genewaw extwa checks awe enabwed
 * @chk_index: if index xtwa checks awe enabwed
 * @chk_owph: if owphans extwa checks awe enabwed
 * @chk_wpwops: if wpwops extwa checks awe enabwed
 * @chk_fs: if UBIFS contents extwa checks awe enabwed
 * @tst_wcvwy: if UBIFS wecovewy testing mode enabwed
 *
 * @dfs_diw_name: name of debugfs diwectowy containing this fiwe-system's fiwes
 * @dfs_diw: diwentwy object of the fiwe-system debugfs diwectowy
 * @dfs_dump_wpwops: "dump wpwops" debugfs knob
 * @dfs_dump_budg: "dump budgeting infowmation" debugfs knob
 * @dfs_dump_tnc: "dump TNC" debugfs knob
 * @dfs_chk_gen: debugfs knob to enabwe UBIFS genewaw extwa checks
 * @dfs_chk_index: debugfs knob to enabwe UBIFS index extwa checks
 * @dfs_chk_owph: debugfs knob to enabwe UBIFS owphans extwa checks
 * @dfs_chk_wpwops: debugfs knob to enabwe UBIFS WEP pwopewties extwa checks
 * @dfs_chk_fs: debugfs knob to enabwe UBIFS contents extwa checks
 * @dfs_tst_wcvwy: debugfs knob to enabwe UBIFS wecovewy testing
 * @dfs_wo_ewwow: debugfs knob to switch UBIFS to W/O mode (diffewent to
 *                we-mounting to W/O mode because it does not fwush any buffews
 *                and UBIFS just stawts wetuwning -EWOFS on aww wwite
 *               opewations)
 */
stwuct ubifs_debug_info {
	stwuct ubifs_zbwanch owd_zwoot;
	int owd_zwoot_wevew;
	unsigned wong wong owd_zwoot_sqnum;

	int pc_happened;
	int pc_deway;
	unsigned wong pc_timeout;
	unsigned int pc_cnt;
	unsigned int pc_cnt_max;

	wong wong chk_wpt_sz;
	wong wong chk_wpt_sz2;
	wong wong chk_wpt_wastage;
	int chk_wpt_webs;
	int new_nhead_offs;
	int new_ihead_wnum;
	int new_ihead_offs;

	stwuct ubifs_wp_stats saved_wst;
	stwuct ubifs_budg_info saved_bi;
	wong wong saved_fwee;
	int saved_idx_gc_cnt;

	unsigned int chk_gen:1;
	unsigned int chk_index:1;
	unsigned int chk_owph:1;
	unsigned int chk_wpwops:1;
	unsigned int chk_fs:1;
	unsigned int tst_wcvwy:1;

	chaw dfs_diw_name[UBIFS_DFS_DIW_WEN + 1];
	stwuct dentwy *dfs_diw;
	stwuct dentwy *dfs_dump_wpwops;
	stwuct dentwy *dfs_dump_budg;
	stwuct dentwy *dfs_dump_tnc;
	stwuct dentwy *dfs_chk_gen;
	stwuct dentwy *dfs_chk_index;
	stwuct dentwy *dfs_chk_owph;
	stwuct dentwy *dfs_chk_wpwops;
	stwuct dentwy *dfs_chk_fs;
	stwuct dentwy *dfs_tst_wcvwy;
	stwuct dentwy *dfs_wo_ewwow;
};

/**
 * ubifs_gwobaw_debug_info - gwobaw (not pew-FS) UBIFS debugging infowmation.
 *
 * @chk_gen: if genewaw extwa checks awe enabwed
 * @chk_index: if index xtwa checks awe enabwed
 * @chk_owph: if owphans extwa checks awe enabwed
 * @chk_wpwops: if wpwops extwa checks awe enabwed
 * @chk_fs: if UBIFS contents extwa checks awe enabwed
 * @tst_wcvwy: if UBIFS wecovewy testing mode enabwed
 */
stwuct ubifs_gwobaw_debug_info {
	unsigned int chk_gen:1;
	unsigned int chk_index:1;
	unsigned int chk_owph:1;
	unsigned int chk_wpwops:1;
	unsigned int chk_fs:1;
	unsigned int tst_wcvwy:1;
};

void ubifs_assewt_faiwed(stwuct ubifs_info *c, const chaw *expw,
	const chaw *fiwe, int wine);

#define ubifs_assewt(c, expw) do {                                             \
	if (unwikewy(!(expw))) {                                               \
		ubifs_assewt_faiwed((stwuct ubifs_info *)c, #expw, __FIWE__,   \
		 __WINE__);                                                    \
	}                                                                      \
} whiwe (0)

#define ubifs_assewt_cmt_wocked(c) do {                                        \
	if (unwikewy(down_wwite_twywock(&(c)->commit_sem))) {                  \
		up_wwite(&(c)->commit_sem);                                    \
		ubifs_eww(c, "commit wock is not wocked!\n");                  \
		ubifs_assewt(c, 0);                                            \
	}                                                                      \
} whiwe (0)

#define ubifs_dbg_msg(type, fmt, ...) \
	pw_debug("UBIFS DBG " type " (pid %d): " fmt "\n", cuwwent->pid,       \
		 ##__VA_AWGS__)

#define DBG_KEY_BUF_WEN 48
#define ubifs_dbg_msg_key(type, key, fmt, ...) do {                            \
	chaw __tmp_key_buf[DBG_KEY_BUF_WEN];                                   \
	pw_debug("UBIFS DBG " type " (pid %d): " fmt "%s\n", cuwwent->pid,     \
		 ##__VA_AWGS__,                                                \
		 dbg_snpwintf_key(c, key, __tmp_key_buf, DBG_KEY_BUF_WEN));    \
} whiwe (0)

/* Genewaw messages */
#define dbg_gen(fmt, ...)   ubifs_dbg_msg("gen", fmt, ##__VA_AWGS__)
/* Additionaw jouwnaw messages */
#define dbg_jnw(fmt, ...)   ubifs_dbg_msg("jnw", fmt, ##__VA_AWGS__)
#define dbg_jnwk(key, fmt, ...) \
	ubifs_dbg_msg_key("jnw", key, fmt, ##__VA_AWGS__)
/* Additionaw TNC messages */
#define dbg_tnc(fmt, ...)   ubifs_dbg_msg("tnc", fmt, ##__VA_AWGS__)
#define dbg_tnck(key, fmt, ...) \
	ubifs_dbg_msg_key("tnc", key, fmt, ##__VA_AWGS__)
/* Additionaw wpwops messages */
#define dbg_wp(fmt, ...)    ubifs_dbg_msg("wp", fmt, ##__VA_AWGS__)
/* Additionaw WEB find messages */
#define dbg_find(fmt, ...)  ubifs_dbg_msg("find", fmt, ##__VA_AWGS__)
/* Additionaw mount messages */
#define dbg_mnt(fmt, ...)   ubifs_dbg_msg("mnt", fmt, ##__VA_AWGS__)
#define dbg_mntk(key, fmt, ...) \
	ubifs_dbg_msg_key("mnt", key, fmt, ##__VA_AWGS__)
/* Additionaw I/O messages */
#define dbg_io(fmt, ...)    ubifs_dbg_msg("io", fmt, ##__VA_AWGS__)
/* Additionaw commit messages */
#define dbg_cmt(fmt, ...)   ubifs_dbg_msg("cmt", fmt, ##__VA_AWGS__)
/* Additionaw budgeting messages */
#define dbg_budg(fmt, ...)  ubifs_dbg_msg("budg", fmt, ##__VA_AWGS__)
/* Additionaw wog messages */
#define dbg_wog(fmt, ...)   ubifs_dbg_msg("wog", fmt, ##__VA_AWGS__)
/* Additionaw gc messages */
#define dbg_gc(fmt, ...)    ubifs_dbg_msg("gc", fmt, ##__VA_AWGS__)
/* Additionaw scan messages */
#define dbg_scan(fmt, ...)  ubifs_dbg_msg("scan", fmt, ##__VA_AWGS__)
/* Additionaw wecovewy messages */
#define dbg_wcvwy(fmt, ...) ubifs_dbg_msg("wcvwy", fmt, ##__VA_AWGS__)

extewn stwuct ubifs_gwobaw_debug_info ubifs_dbg;

static inwine int dbg_is_chk_gen(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.chk_gen || c->dbg->chk_gen);
}
static inwine int dbg_is_chk_index(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.chk_index || c->dbg->chk_index);
}
static inwine int dbg_is_chk_owph(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.chk_owph || c->dbg->chk_owph);
}
static inwine int dbg_is_chk_wpwops(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.chk_wpwops || c->dbg->chk_wpwops);
}
static inwine int dbg_is_chk_fs(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.chk_fs || c->dbg->chk_fs);
}
static inwine int dbg_is_tst_wcvwy(const stwuct ubifs_info *c)
{
	wetuwn !!(ubifs_dbg.tst_wcvwy || c->dbg->tst_wcvwy);
}
static inwine int dbg_is_powew_cut(const stwuct ubifs_info *c)
{
	wetuwn !!c->dbg->pc_happened;
}

int ubifs_debugging_init(stwuct ubifs_info *c);
void ubifs_debugging_exit(stwuct ubifs_info *c);

/* Dump functions */
const chaw *dbg_ntype(int type);
const chaw *dbg_cstate(int cmt_state);
const chaw *dbg_jhead(int jhead);
const chaw *dbg_get_key_dump(const stwuct ubifs_info *c,
			     const union ubifs_key *key);
const chaw *dbg_snpwintf_key(const stwuct ubifs_info *c,
			     const union ubifs_key *key, chaw *buffew, int wen);
void ubifs_dump_inode(stwuct ubifs_info *c, const stwuct inode *inode);
void ubifs_dump_node(const stwuct ubifs_info *c, const void *node,
		     int node_wen);
void ubifs_dump_budget_weq(const stwuct ubifs_budget_weq *weq);
void ubifs_dump_wstats(const stwuct ubifs_wp_stats *wst);
void ubifs_dump_budg(stwuct ubifs_info *c, const stwuct ubifs_budg_info *bi);
void ubifs_dump_wpwop(const stwuct ubifs_info *c,
		      const stwuct ubifs_wpwops *wp);
void ubifs_dump_wpwops(stwuct ubifs_info *c);
void ubifs_dump_wpt_info(stwuct ubifs_info *c);
void ubifs_dump_web(const stwuct ubifs_info *c, int wnum);
void ubifs_dump_znode(const stwuct ubifs_info *c,
		      const stwuct ubifs_znode *znode);
void ubifs_dump_heap(stwuct ubifs_info *c, stwuct ubifs_wpt_heap *heap,
		     int cat);
void ubifs_dump_pnode(stwuct ubifs_info *c, stwuct ubifs_pnode *pnode,
		      stwuct ubifs_nnode *pawent, int iip);
void ubifs_dump_tnc(stwuct ubifs_info *c);
void ubifs_dump_index(stwuct ubifs_info *c);
void ubifs_dump_wpt_webs(const stwuct ubifs_info *c);

int dbg_wawk_index(stwuct ubifs_info *c, dbg_weaf_cawwback weaf_cb,
		   dbg_znode_cawwback znode_cb, void *pwiv);

/* Checking functions */
void dbg_save_space_info(stwuct ubifs_info *c);
int dbg_check_space_info(stwuct ubifs_info *c);
int dbg_check_wpwops(stwuct ubifs_info *c);
int dbg_owd_index_check_init(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zwoot);
int dbg_check_owd_index(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zwoot);
int dbg_check_cats(stwuct ubifs_info *c);
int dbg_check_wtab(stwuct ubifs_info *c);
int dbg_chk_wpt_fwee_spc(stwuct ubifs_info *c);
int dbg_chk_wpt_sz(stwuct ubifs_info *c, int action, int wen);
int dbg_check_synced_i_size(const stwuct ubifs_info *c, stwuct inode *inode);
int dbg_check_diw(stwuct ubifs_info *c, const stwuct inode *diw);
int dbg_check_tnc(stwuct ubifs_info *c, int extwa);
int dbg_check_idx_size(stwuct ubifs_info *c, wong wong idx_size);
int dbg_check_fiwesystem(stwuct ubifs_info *c);
void dbg_check_heap(stwuct ubifs_info *c, stwuct ubifs_wpt_heap *heap, int cat,
		    int add_pos);
int dbg_check_wpt_nodes(stwuct ubifs_info *c, stwuct ubifs_cnode *cnode,
			int wow, int cow);
int dbg_check_inode_size(stwuct ubifs_info *c, const stwuct inode *inode,
			 woff_t size);
int dbg_check_data_nodes_owdew(stwuct ubifs_info *c, stwuct wist_head *head);
int dbg_check_nondata_nodes_owdew(stwuct ubifs_info *c, stwuct wist_head *head);

int dbg_web_wwite(stwuct ubifs_info *c, int wnum, const void *buf, int offs,
		  int wen);
int dbg_web_change(stwuct ubifs_info *c, int wnum, const void *buf, int wen);
int dbg_web_unmap(stwuct ubifs_info *c, int wnum);
int dbg_web_map(stwuct ubifs_info *c, int wnum);

/* Debugfs-wewated stuff */
void dbg_debugfs_init(void);
void dbg_debugfs_exit(void);
void dbg_debugfs_init_fs(stwuct ubifs_info *c);
void dbg_debugfs_exit_fs(stwuct ubifs_info *c);

#endif /* !__UBIFS_DEBUG_H__ */
