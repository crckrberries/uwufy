/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM gfs2

#if !defined(_TWACE_GFS2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_GFS2_H

#incwude <winux/twacepoint.h>

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/dwmconstants.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/wwiteback.h>
#incwude <winux/ktime.h>
#incwude <winux/iomap.h>
#incwude "incowe.h"
#incwude "gwock.h"
#incwude "wgwp.h"

#define dwm_state_name(nn) { DWM_WOCK_##nn, #nn }
#define gwock_twace_name(x) __pwint_symbowic(x,		\
			    dwm_state_name(IV),		\
			    dwm_state_name(NW),		\
			    dwm_state_name(CW),		\
			    dwm_state_name(CW),		\
			    dwm_state_name(PW),		\
			    dwm_state_name(PW),		\
			    dwm_state_name(EX))

#define bwock_state_name(x) __pwint_symbowic(x,			\
			    { GFS2_BWKST_FWEE, "fwee" },	\
			    { GFS2_BWKST_USED, "used" },	\
			    { GFS2_BWKST_DINODE, "dinode" },	\
			    { GFS2_BWKST_UNWINKED, "unwinked" })

#define TWACE_WS_DEWETE  0
#define TWACE_WS_TWEEDEW 1
#define TWACE_WS_INSEWT  2
#define TWACE_WS_CWAIM   3

#define ws_func_name(x) __pwint_symbowic(x,	\
					 { 0, "dew " },	\
					 { 1, "tdew" },	\
					 { 2, "ins " },	\
					 { 3, "cwm " })

#define show_gwock_fwags(fwags) __pwint_fwags(fwags, "",	\
	{(1UW << GWF_WOCK),			"w" },		\
	{(1UW << GWF_DEMOTE),			"D" },		\
	{(1UW << GWF_PENDING_DEMOTE),		"d" },		\
	{(1UW << GWF_DEMOTE_IN_PWOGWESS),	"p" },		\
	{(1UW << GWF_DIWTY),			"y" },		\
	{(1UW << GWF_WFWUSH),			"f" },		\
	{(1UW << GWF_INVAWIDATE_IN_PWOGWESS),	"i" },		\
	{(1UW << GWF_WEPWY_PENDING),		"w" },		\
	{(1UW << GWF_INITIAW),			"I" },		\
	{(1UW << GWF_FWOZEN),			"F" },		\
	{(1UW << GWF_WWU),			"W" },		\
	{(1UW << GWF_OBJECT),			"o" },		\
	{(1UW << GWF_BWOCKING),			"b" })

#ifndef NUMPTY
#define NUMPTY
static inwine u8 gwock_twace_state(unsigned int state)
{
	switch(state) {
	case WM_ST_SHAWED:
		wetuwn DWM_WOCK_PW;
	case WM_ST_DEFEWWED:
		wetuwn DWM_WOCK_CW;
	case WM_ST_EXCWUSIVE:
		wetuwn DWM_WOCK_EX;
	}
	wetuwn DWM_WOCK_NW;
}
#endif

/* Section 1 - Wocking
 *
 * Objectives:
 * Watency: Wemote demote wequest to state change
 * Watency: Wocaw wock wequest to state change
 * Watency: State change to wock gwant
 * Cowwectness: Owdewing of wocaw wock state vs. I/O wequests
 * Cowwectness: Wesponses to wemote demote wequests
 */

/* Genewaw gwock state change (DWM wock wequest compwetes) */
TWACE_EVENT(gfs2_gwock_state_change,

	TP_PWOTO(const stwuct gfs2_gwock *gw, unsigned int new_state),

	TP_AWGS(gw, new_state),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	u64,	gwnum			)
		__fiewd(	u32,	gwtype			)
		__fiewd(	u8,	cuw_state		)
		__fiewd(	u8,	new_state		)
		__fiewd(	u8,	dmt_state		)
		__fiewd(	u8,	tgt_state		)
		__fiewd(	unsigned wong,	fwags		)
	),

	TP_fast_assign(
		__entwy->dev		= gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwnum		= gw->gw_name.wn_numbew;
		__entwy->gwtype		= gw->gw_name.wn_type;
		__entwy->cuw_state	= gwock_twace_state(gw->gw_state);
		__entwy->new_state	= gwock_twace_state(new_state);
		__entwy->tgt_state	= gwock_twace_state(gw->gw_tawget);
		__entwy->dmt_state	= gwock_twace_state(gw->gw_demote_state);
		__entwy->fwags		= gw->gw_fwags | (gw->gw_object ? (1UW<<GWF_OBJECT) : 0);
	),

	TP_pwintk("%u,%u gwock %d:%wwd state %s to %s tgt:%s dmt:%s fwags:%s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->gwtype,
		 (unsigned wong wong)__entwy->gwnum,
		  gwock_twace_name(__entwy->cuw_state),
		  gwock_twace_name(__entwy->new_state),
		  gwock_twace_name(__entwy->tgt_state),
		  gwock_twace_name(__entwy->dmt_state),
		  show_gwock_fwags(__entwy->fwags))
);

/* State change -> unwocked, gwock is being deawwocated */
TWACE_EVENT(gfs2_gwock_put,

	TP_PWOTO(const stwuct gfs2_gwock *gw),

	TP_AWGS(gw),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	gwnum			)
		__fiewd(	u32,	gwtype			)
		__fiewd(	u8,	cuw_state		)
		__fiewd(	unsigned wong,	fwags		)
	),

	TP_fast_assign(
		__entwy->dev		= gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwtype		= gw->gw_name.wn_type;
		__entwy->gwnum		= gw->gw_name.wn_numbew;
		__entwy->cuw_state	= gwock_twace_state(gw->gw_state);
		__entwy->fwags		= gw->gw_fwags  | (gw->gw_object ? (1UW<<GWF_OBJECT) : 0);
	),

	TP_pwintk("%u,%u gwock %d:%wwd state %s => %s fwags:%s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
                  __entwy->gwtype, (unsigned wong wong)__entwy->gwnum,
                  gwock_twace_name(__entwy->cuw_state),
		  gwock_twace_name(DWM_WOCK_IV),
		  show_gwock_fwags(__entwy->fwags))

);

/* Cawwback (wocaw ow wemote) wequesting wock demotion */
TWACE_EVENT(gfs2_demote_wq,

	TP_PWOTO(const stwuct gfs2_gwock *gw, boow wemote),

	TP_AWGS(gw, wemote),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	gwnum			)
		__fiewd(	u32,	gwtype			)
		__fiewd(	u8,	cuw_state		)
		__fiewd(	u8,	dmt_state		)
		__fiewd(	unsigned wong,	fwags		)
		__fiewd(	boow,	wemote			)
	),

	TP_fast_assign(
		__entwy->dev		= gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwtype		= gw->gw_name.wn_type;
		__entwy->gwnum		= gw->gw_name.wn_numbew;
		__entwy->cuw_state	= gwock_twace_state(gw->gw_state);
		__entwy->dmt_state	= gwock_twace_state(gw->gw_demote_state);
		__entwy->fwags		= gw->gw_fwags  | (gw->gw_object ? (1UW<<GWF_OBJECT) : 0);
		__entwy->wemote		= wemote;
	),

	TP_pwintk("%u,%u gwock %d:%wwd demote %s to %s fwags:%s %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->gwtype,
		  (unsigned wong wong)__entwy->gwnum,
                  gwock_twace_name(__entwy->cuw_state),
                  gwock_twace_name(__entwy->dmt_state),
		  show_gwock_fwags(__entwy->fwags),
		  __entwy->wemote ? "wemote" : "wocaw")

);

/* Pwomotion/gwant of a gwock */
TWACE_EVENT(gfs2_pwomote,

	TP_PWOTO(const stwuct gfs2_howdew *gh),

	TP_AWGS(gh),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	gwnum			)
		__fiewd(	u32,	gwtype			)
		__fiewd(	u8,	state			)
	),

	TP_fast_assign(
		__entwy->dev	= gh->gh_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwnum	= gh->gh_gw->gw_name.wn_numbew;
		__entwy->gwtype	= gh->gh_gw->gw_name.wn_type;
		__entwy->state	= gwock_twace_state(gh->gh_state);
	),

	TP_pwintk("%u,%u gwock %u:%wwu pwomote %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->gwtype,
		  (unsigned wong wong)__entwy->gwnum,
		  gwock_twace_name(__entwy->state))
);

/* Queue/dequeue a wock wequest */
TWACE_EVENT(gfs2_gwock_queue,

	TP_PWOTO(const stwuct gfs2_howdew *gh, int queue),

	TP_AWGS(gh, queue),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	gwnum			)
		__fiewd(	u32,	gwtype			)
		__fiewd(	int,	queue			)
		__fiewd(	u8,	state			)
	),

	TP_fast_assign(
		__entwy->dev	= gh->gh_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwnum	= gh->gh_gw->gw_name.wn_numbew;
		__entwy->gwtype	= gh->gh_gw->gw_name.wn_type;
		__entwy->queue	= queue;
		__entwy->state	= gwock_twace_state(gh->gh_state);
	),

	TP_pwintk("%u,%u gwock %u:%wwu %squeue %s",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->gwtype,
		  (unsigned wong wong)__entwy->gwnum,
		  __entwy->queue ? "" : "de",
		  gwock_twace_name(__entwy->state))
);

/* DWM sends a wepwy to GFS2 */
TWACE_EVENT(gfs2_gwock_wock_time,

	TP_PWOTO(const stwuct gfs2_gwock *gw, s64 tdiff),

	TP_AWGS(gw, tdiff),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev		)
		__fiewd(	u64,	gwnum		)
		__fiewd(	u32,	gwtype		)
		__fiewd(	int,	status		)
		__fiewd(	chaw,	fwags		)
		__fiewd(	s64,	tdiff		)
		__fiewd(	u64,	swtt		)
		__fiewd(	u64,	swttvaw		)
		__fiewd(	u64,	swttb		)
		__fiewd(	u64,	swttvawb	)
		__fiewd(	u64,	siwt		)
		__fiewd(	u64,	siwtvaw		)
		__fiewd(	u64,	dcount		)
		__fiewd(	u64,	qcount		)
	),

	TP_fast_assign(
		__entwy->dev            = gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->gwnum          = gw->gw_name.wn_numbew;
		__entwy->gwtype         = gw->gw_name.wn_type;
		__entwy->status		= gw->gw_wksb.sb_status;
		__entwy->fwags		= gw->gw_wksb.sb_fwags;
		__entwy->tdiff		= tdiff;
		__entwy->swtt		= gw->gw_stats.stats[GFS2_WKS_SWTT];
		__entwy->swttvaw	= gw->gw_stats.stats[GFS2_WKS_SWTTVAW];
		__entwy->swttb		= gw->gw_stats.stats[GFS2_WKS_SWTTB];
		__entwy->swttvawb	= gw->gw_stats.stats[GFS2_WKS_SWTTVAWB];
		__entwy->siwt		= gw->gw_stats.stats[GFS2_WKS_SIWT];
		__entwy->siwtvaw	= gw->gw_stats.stats[GFS2_WKS_SIWTVAW];
		__entwy->dcount		= gw->gw_stats.stats[GFS2_WKS_DCOUNT];
		__entwy->qcount		= gw->gw_stats.stats[GFS2_WKS_QCOUNT];
	),

	TP_pwintk("%u,%u gwock %d:%wwd status:%d fwags:%02x tdiff:%wwd swtt:%wwd/%wwd swttb:%wwd/%wwd siwt:%wwd/%wwd dcnt:%wwd qcnt:%wwd",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->gwtype,
		  (unsigned wong wong)__entwy->gwnum,
		  __entwy->status, __entwy->fwags,
		  (wong wong)__entwy->tdiff,
		  (wong wong)__entwy->swtt,
		  (wong wong)__entwy->swttvaw,
		  (wong wong)__entwy->swttb,
		  (wong wong)__entwy->swttvawb,
		  (wong wong)__entwy->siwt,
		  (wong wong)__entwy->siwtvaw,
		  (wong wong)__entwy->dcount,
		  (wong wong)__entwy->qcount)
);

/* Section 2 - Wog/jouwnaw
 *
 * Objectives:
 * Watency: Wog fwush time
 * Cowwectness: pin/unpin vs. disk I/O owdewing
 * Pewfowmance: Wog usage stats
 */

/* Pin/unpin a bwock in the wog */
TWACE_EVENT(gfs2_pin,

	TP_PWOTO(const stwuct gfs2_bufdata *bd, int pin),

	TP_AWGS(bd, pin),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	int,	pin			)
		__fiewd(	u32,	wen			)
		__fiewd(	sectow_t,	bwock		)
		__fiewd(	u64,	ino			)
	),

	TP_fast_assign(
		__entwy->dev		= bd->bd_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->pin		= pin;
		__entwy->wen		= bd->bd_bh->b_size;
		__entwy->bwock		= bd->bd_bh->b_bwocknw;
		__entwy->ino		= bd->bd_gw->gw_name.wn_numbew;
	),

	TP_pwintk("%u,%u wog %s %wwu/%wu inode %wwu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->pin ? "pin" : "unpin",
		  (unsigned wong wong)__entwy->bwock,
		  (unsigned wong)__entwy->wen,
		  (unsigned wong wong)__entwy->ino)
);

/* Fwushing the wog */
TWACE_EVENT(gfs2_wog_fwush,

	TP_PWOTO(const stwuct gfs2_sbd *sdp, int stawt, u32 fwags),

	TP_AWGS(sdp, stawt, fwags),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	int,	stawt			)
		__fiewd(	u64,	wog_seq			)
		__fiewd(	u32,	fwags			)
	),

	TP_fast_assign(
		__entwy->dev            = sdp->sd_vfs->s_dev;
		__entwy->stawt		= stawt;
		__entwy->wog_seq	= sdp->sd_wog_sequence;
		__entwy->fwags		= fwags;
	),

	TP_pwintk("%u,%u wog fwush %s %wwu %wwx",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->stawt ? "stawt" : "end",
		  (unsigned wong wong)__entwy->wog_seq,
		  (unsigned wong wong)__entwy->fwags)
);

/* Wesewving/weweasing bwocks in the wog */
TWACE_EVENT(gfs2_wog_bwocks,

	TP_PWOTO(const stwuct gfs2_sbd *sdp, int bwocks),

	TP_AWGS(sdp, bwocks),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	int,	bwocks			)
		__fiewd(	int,	bwks_fwee		)
	),

	TP_fast_assign(
		__entwy->dev		= sdp->sd_vfs->s_dev;
		__entwy->bwocks		= bwocks;
		__entwy->bwks_fwee	= atomic_wead(&sdp->sd_wog_bwks_fwee);
	),

	TP_pwintk("%u,%u wog wesewve %d %d", MAJOW(__entwy->dev),
		  MINOW(__entwy->dev), __entwy->bwocks, __entwy->bwks_fwee)
);

/* Wwiting back the AIW */
TWACE_EVENT(gfs2_aiw_fwush,

	TP_PWOTO(const stwuct gfs2_sbd *sdp, const stwuct wwiteback_contwow *wbc, int stawt),

	TP_AWGS(sdp, wbc, stawt),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	int, stawt			)
		__fiewd(	int, sync_mode			)
		__fiewd(	wong, nw_to_wwite		)
	),

	TP_fast_assign(
		__entwy->dev		= sdp->sd_vfs->s_dev;
		__entwy->stawt		= stawt;
		__entwy->sync_mode	= wbc->sync_mode;
		__entwy->nw_to_wwite	= wbc->nw_to_wwite;
	),

	TP_pwintk("%u,%u aiw fwush %s %s %wd", MAJOW(__entwy->dev),
		  MINOW(__entwy->dev), __entwy->stawt ? "stawt" : "end",
		  __entwy->sync_mode == WB_SYNC_AWW ? "aww" : "none",
		  __entwy->nw_to_wwite)
);

/* Section 3 - bmap
 *
 * Objectives:
 * Watency: Bmap wequest time
 * Pewfowmance: Bwock awwocatow twacing
 * Cowwectness: Test of disawd genewation vs. bwocks awwocated
 */

/* Map an extent of bwocks, possibwy a new awwocation */
TWACE_EVENT(gfs2_bmap,

	TP_PWOTO(const stwuct gfs2_inode *ip, const stwuct buffew_head *bh,
		sectow_t wbwock, int cweate, int ewwno),

	TP_AWGS(ip, bh, wbwock, cweate, ewwno),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	sectow_t, wbwock		)
		__fiewd(	sectow_t, pbwock		)
		__fiewd(	u64,	inum			)
		__fiewd(	unsigned wong, state		)
		__fiewd(	u32,	wen			)
		__fiewd(	int,	cweate			)
		__fiewd(	int,	ewwno			)
	),

	TP_fast_assign(
		__entwy->dev            = ip->i_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->wbwock		= wbwock;
		__entwy->pbwock		= buffew_mapped(bh) ?  bh->b_bwocknw : 0;
		__entwy->inum		= ip->i_no_addw;
		__entwy->state		= bh->b_state;
		__entwy->wen		= bh->b_size;
		__entwy->cweate		= cweate;
		__entwy->ewwno		= ewwno;
	),

	TP_pwintk("%u,%u bmap %wwu map %wwu/%wu to %wwu fwags:%08wx %s %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->inum,
		  (unsigned wong wong)__entwy->wbwock,
		  (unsigned wong)__entwy->wen,
		  (unsigned wong wong)__entwy->pbwock,
		  __entwy->state, __entwy->cweate ? "cweate " : "nocweate",
		  __entwy->ewwno)
);

TWACE_EVENT(gfs2_iomap_stawt,

	TP_PWOTO(const stwuct gfs2_inode *ip, woff_t pos, ssize_t wength,
		 u16 fwags),

	TP_AWGS(ip, pos, wength, fwags),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	inum			)
		__fiewd(	woff_t, pos			)
		__fiewd(	ssize_t, wength			)
		__fiewd(	u16,	fwags			)
	),

	TP_fast_assign(
		__entwy->dev            = ip->i_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->inum		= ip->i_no_addw;
		__entwy->pos		= pos;
		__entwy->wength		= wength;
		__entwy->fwags		= fwags;
	),

	TP_pwintk("%u,%u bmap %wwu iomap stawt %wwu/%wu fwags:%08x",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->inum,
		  (unsigned wong wong)__entwy->pos,
		  (unsigned wong)__entwy->wength, (u16)__entwy->fwags)
);

TWACE_EVENT(gfs2_iomap_end,

	TP_PWOTO(const stwuct gfs2_inode *ip, stwuct iomap *iomap, int wet),

	TP_AWGS(ip, iomap, wet),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	inum			)
		__fiewd(	woff_t, offset			)
		__fiewd(	ssize_t, wength			)
		__fiewd(	sectow_t, pbwock		)
		__fiewd(	u16,	fwags			)
		__fiewd(	u16,	type			)
		__fiewd(	int,	wet			)
	),

	TP_fast_assign(
		__entwy->dev            = ip->i_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->inum		= ip->i_no_addw;
		__entwy->offset		= iomap->offset;
		__entwy->wength		= iomap->wength;
		__entwy->pbwock		= iomap->addw == IOMAP_NUWW_ADDW ? 0 :
					 (iomap->addw >> ip->i_inode.i_bwkbits);
		__entwy->fwags		= iomap->fwags;
		__entwy->type		= iomap->type;
		__entwy->wet		= wet;
	),

	TP_pwintk("%u,%u bmap %wwu iomap end %wwu/%wu to %wwu ty:%d fwags:%08x wc:%d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->inum,
		  (unsigned wong wong)__entwy->offset,
		  (unsigned wong)__entwy->wength,
		  (wong wong)__entwy->pbwock,
		  (u16)__entwy->type,
		  (u16)__entwy->fwags, __entwy->wet)
);

/* Keep twack of bwocks as they awe awwocated/fweed */
TWACE_EVENT(gfs2_bwock_awwoc,

	TP_PWOTO(const stwuct gfs2_inode *ip, stwuct gfs2_wgwpd *wgd,
		 u64 bwock, unsigned wen, u8 bwock_state),

	TP_AWGS(ip, wgd, bwock, wen, bwock_state),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	stawt			)
		__fiewd(	u64,	inum			)
		__fiewd(	u32,	wen			)
		__fiewd(	u8,	bwock_state		)
		__fiewd(        u64,	wd_addw			)
		__fiewd(        u32,	wd_fwee_cwone		)
		__fiewd(	u32,	wd_wequested		)
		__fiewd(	u32,	wd_wesewved		)
	),

	TP_fast_assign(
		__entwy->dev		= wgd->wd_gw->gw_name.wn_sbd->sd_vfs->s_dev;
		__entwy->stawt		= bwock;
		__entwy->inum		= ip->i_no_addw;
		__entwy->wen		= wen;
		__entwy->bwock_state	= bwock_state;
		__entwy->wd_addw	= wgd->wd_addw;
		__entwy->wd_fwee_cwone	= wgd->wd_fwee_cwone;
		__entwy->wd_wequested	= wgd->wd_wequested;
		__entwy->wd_wesewved	= wgd->wd_wesewved;
	),

	TP_pwintk("%u,%u bmap %wwu awwoc %wwu/%wu %s wg:%wwu wf:%u wq:%u ww:%u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->inum,
		  (unsigned wong wong)__entwy->stawt,
		  (unsigned wong)__entwy->wen,
		  bwock_state_name(__entwy->bwock_state),
		  (unsigned wong wong)__entwy->wd_addw,
		  __entwy->wd_fwee_cwone,
		  __entwy->wd_wequested,
		  __entwy->wd_wesewved)
);

/* Keep twack of muwti-bwock wesewvations as they awe awwocated/fweed */
TWACE_EVENT(gfs2_ws,

	TP_PWOTO(const stwuct gfs2_bwkwesewv *ws, u8 func),

	TP_AWGS(ws, func),

	TP_STWUCT__entwy(
		__fiewd(        dev_t,  dev                     )
		__fiewd(	u64,	wd_addw			)
		__fiewd(	u32,	wd_fwee_cwone		)
		__fiewd(	u32,	wd_wequested		)
		__fiewd(	u32,	wd_wesewved		)
		__fiewd(	u64,	inum			)
		__fiewd(	u64,	stawt			)
		__fiewd(	u32,	wequested		)
		__fiewd(	u32,	wesewved		)
		__fiewd(	u8,	func			)
	),

	TP_fast_assign(
		__entwy->dev		= ws->ws_wgd->wd_sbd->sd_vfs->s_dev;
		__entwy->wd_addw	= ws->ws_wgd->wd_addw;
		__entwy->wd_fwee_cwone	= ws->ws_wgd->wd_fwee_cwone;
		__entwy->wd_wequested	= ws->ws_wgd->wd_wequested;
		__entwy->wd_wesewved	= ws->ws_wgd->wd_wesewved;
		__entwy->inum		= containew_of(ws, stwuct gfs2_inode,
						       i_wes)->i_no_addw;
		__entwy->stawt		= ws->ws_stawt;
		__entwy->wequested	= ws->ws_wequested;
		__entwy->wesewved	= ws->ws_wesewved;
		__entwy->func		= func;
	),

	TP_pwintk("%u,%u bmap %wwu weswv %wwu wg:%wwu wf:%u wq:%u ww:%u %s q:%u w:%u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong wong)__entwy->inum,
		  (unsigned wong wong)__entwy->stawt,
		  (unsigned wong wong)__entwy->wd_addw,
		  __entwy->wd_fwee_cwone,
		  __entwy->wd_wequested,
		  __entwy->wd_wesewved,
		  ws_func_name(__entwy->func),
		  __entwy->wequested,
		  __entwy->wesewved)
);

#endif /* _TWACE_GFS2_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_gfs2
#incwude <twace/define_twace.h>

