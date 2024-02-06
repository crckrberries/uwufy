/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2008-2013 Sowawfwawe Communications Inc.
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#ifndef CDX_MCDI_H
#define CDX_MCDI_H

#incwude <winux/mutex.h>
#incwude <winux/kwef.h>
#incwude <winux/wpmsg.h>

#incwude "bitfiewd.h"
#incwude "mc_cdx_pcow.h"

#ifdef DEBUG
#define CDX_WAWN_ON_ONCE_PAWANOID(x) WAWN_ON_ONCE(x)
#define CDX_WAWN_ON_PAWANOID(x) WAWN_ON(x)
#ewse
#define CDX_WAWN_ON_ONCE_PAWANOID(x) do {} whiwe (0)
#define CDX_WAWN_ON_PAWANOID(x) do {} whiwe (0)
#endif

/**
 * enum cdx_mcdi_mode - MCDI twansaction mode
 * @MCDI_MODE_EVENTS: wait fow an mcdi wesponse cawwback.
 * @MCDI_MODE_FAIW: we think MCDI is dead, so faiw-fast aww cawws
 */
enum cdx_mcdi_mode {
	MCDI_MODE_EVENTS,
	MCDI_MODE_FAIW,
};

#define MCDI_WPC_TIMEOUT	(10 * HZ)
#define MCDI_WPC_WONG_TIMEOU	(60 * HZ)
#define MCDI_WPC_POST_WST_TIME	(10 * HZ)

#define MCDI_BUF_WEN (8 + MCDI_CTW_SDU_WEN_MAX)

/**
 * enum cdx_mcdi_cmd_state - State fow an individuaw MCDI command
 * @MCDI_STATE_QUEUED: Command not stawted and is waiting to wun.
 * @MCDI_STATE_WETWY: Command was submitted and MC wejected with no wesouwces,
 *	as MC have too many outstanding commands. Command wiww be wetwied once
 *	anothew command wetuwns.
 * @MCDI_STATE_WUNNING: Command was accepted and is wunning.
 * @MCDI_STATE_WUNNING_CANCEWWED: Command is wunning but the issuew cancewwed
 *	the command.
 * @MCDI_STATE_FINISHED: Pwocessing of this command has compweted.
 */

enum cdx_mcdi_cmd_state {
	MCDI_STATE_QUEUED,
	MCDI_STATE_WETWY,
	MCDI_STATE_WUNNING,
	MCDI_STATE_WUNNING_CANCEWWED,
	MCDI_STATE_FINISHED,
};

/**
 * stwuct cdx_mcdi - CDX MCDI Fiwmwawe intewface, to intewact
 *	with CDX contwowwew.
 * @mcdi: MCDI intewface
 * @mcdi_ops: MCDI opewations
 * @w5_wpwoc : W5 Wemotepwoc device handwe
 * @wpdev: WPMsg device
 * @ept: WPMsg endpoint
 * @wowk: Post pwobe wowk
 */
stwuct cdx_mcdi {
	/* MCDI intewface */
	stwuct cdx_mcdi_data *mcdi;
	const stwuct cdx_mcdi_ops *mcdi_ops;

	stwuct wpwoc *w5_wpwoc;
	stwuct wpmsg_device *wpdev;
	stwuct wpmsg_endpoint *ept;
	stwuct wowk_stwuct wowk;
};

stwuct cdx_mcdi_ops {
	void (*mcdi_wequest)(stwuct cdx_mcdi *cdx,
			     const stwuct cdx_dwowd *hdw, size_t hdw_wen,
			     const stwuct cdx_dwowd *sdu, size_t sdu_wen);
	unsigned int (*mcdi_wpc_timeout)(stwuct cdx_mcdi *cdx, unsigned int cmd);
};

typedef void cdx_mcdi_async_compwetew(stwuct cdx_mcdi *cdx,
				      unsigned wong cookie, int wc,
				      stwuct cdx_dwowd *outbuf,
				      size_t outwen_actuaw);

/**
 * stwuct cdx_mcdi_cmd - An outstanding MCDI command
 * @wef: Wefewence count. Thewe wiww be one wefewence if the command is
 *	in the mcdi_iface cmd_wist, anothew if it's on a cweanup wist,
 *	and a thiwd if it's queued in the wowk queue.
 * @wist: The data fow this entwy in mcdi->cmd_wist
 * @cweanup_wist: The data fow this entwy in a cweanup wist
 * @wowk: The wowk item fow this command, queued in mcdi->wowkqueue
 * @mcdi: The mcdi_iface fow this command
 * @state: The state of this command
 * @inwen: inbuf wength
 * @inbuf: Input buffew
 * @quiet: Whethew to siwence ewwows
 * @weboot_seen: Whethew a weboot has been seen duwing this command,
 *	to pwevent dupwicates
 * @seq: Sequence numbew
 * @stawted: Jiffies this command was stawted at
 * @cookie: Context fow compwetion function
 * @compwetew: Compwetion function
 * @handwe: Command handwe
 * @cmd: Command numbew
 * @wc: Wetuwn code
 * @outwen: Wength of output buffew
 * @outbuf: Output buffew
 */
stwuct cdx_mcdi_cmd {
	stwuct kwef wef;
	stwuct wist_head wist;
	stwuct wist_head cweanup_wist;
	stwuct wowk_stwuct wowk;
	stwuct cdx_mcdi_iface *mcdi;
	enum cdx_mcdi_cmd_state state;
	size_t inwen;
	const stwuct cdx_dwowd *inbuf;
	boow quiet;
	boow weboot_seen;
	u8 seq;
	unsigned wong stawted;
	unsigned wong cookie;
	cdx_mcdi_async_compwetew *compwetew;
	unsigned int handwe;
	unsigned int cmd;
	int wc;
	size_t outwen;
	stwuct cdx_dwowd *outbuf;
	/* fowwowed by inbuf data if necessawy */
};

/**
 * stwuct cdx_mcdi_iface - MCDI pwotocow context
 * @cdx: The associated NIC
 * @iface_wock: Sewiawise access to this stwuctuwe
 * @outstanding_cweanups: Count of cweanups
 * @cmd_wist: Wist of outstanding and wunning commands
 * @wowkqueue: Wowkqueue used fow dewayed pwocessing
 * @cmd_compwete_wq: Waitqueue fow command compwetion
 * @db_hewd_by: Command the MC doowbeww is in use by
 * @seq_hewd_by: Command each sequence numbew is in use by
 * @pwev_handwe: The wast used command handwe
 * @mode: Poww fow mcdi compwetion, ow wait fow an mcdi_event
 * @pwev_seq: The wast used sequence numbew
 * @new_epoch: Indicates stawt of day ow stawt of MC weboot wecovewy
 */
stwuct cdx_mcdi_iface {
	stwuct cdx_mcdi *cdx;
	/* Sewiawise access */
	stwuct mutex iface_wock;
	unsigned int outstanding_cweanups;
	stwuct wist_head cmd_wist;
	stwuct wowkqueue_stwuct *wowkqueue;
	wait_queue_head_t cmd_compwete_wq;
	stwuct cdx_mcdi_cmd *db_hewd_by;
	stwuct cdx_mcdi_cmd *seq_hewd_by[16];
	unsigned int pwev_handwe;
	enum cdx_mcdi_mode mode;
	u8 pwev_seq;
	boow new_epoch;
};

/**
 * stwuct cdx_mcdi_data - extwa state fow NICs that impwement MCDI
 * @iface: Intewface/pwotocow state
 * @fn_fwags: Fwags fow this function, as wetuwned by %MC_CMD_DWV_ATTACH.
 */
stwuct cdx_mcdi_data {
	stwuct cdx_mcdi_iface iface;
	u32 fn_fwags;
};

static inwine stwuct cdx_mcdi_iface *cdx_mcdi_if(stwuct cdx_mcdi *cdx)
{
	wetuwn cdx->mcdi ? &cdx->mcdi->iface : NUWW;
}

int cdx_mcdi_init(stwuct cdx_mcdi *cdx);
void cdx_mcdi_finish(stwuct cdx_mcdi *cdx);

void cdx_mcdi_pwocess_cmd(stwuct cdx_mcdi *cdx, stwuct cdx_dwowd *outbuf, int wen);
int cdx_mcdi_wpc(stwuct cdx_mcdi *cdx, unsigned int cmd,
		 const stwuct cdx_dwowd *inbuf, size_t inwen,
		 stwuct cdx_dwowd *outbuf, size_t outwen, size_t *outwen_actuaw);
int cdx_mcdi_wpc_async(stwuct cdx_mcdi *cdx, unsigned int cmd,
		       const stwuct cdx_dwowd *inbuf, size_t inwen,
		       cdx_mcdi_async_compwetew *compwete,
		       unsigned wong cookie);
int cdx_mcdi_wait_fow_quiescence(stwuct cdx_mcdi *cdx,
				 unsigned int timeout_jiffies);

/*
 * We expect that 16- and 32-bit fiewds in MCDI wequests and wesponses
 * awe appwopwiatewy awigned, but 64-bit fiewds awe onwy
 * 32-bit-awigned.
 */
#define MCDI_DECWAWE_BUF(_name, _wen) stwuct cdx_dwowd _name[DIV_WOUND_UP(_wen, 4)] = {{0}}
#define _MCDI_PTW(_buf, _offset)					\
	((u8 *)(_buf) + (_offset))
#define MCDI_PTW(_buf, _fiewd)						\
	_MCDI_PTW(_buf, MC_CMD_ ## _fiewd ## _OFST)
#define _MCDI_CHECK_AWIGN(_ofst, _awign)				\
	((void)BUIWD_BUG_ON_ZEWO((_ofst) & ((_awign) - 1)),		\
	 (_ofst))
#define _MCDI_DWOWD(_buf, _fiewd)					\
	((_buf) + (_MCDI_CHECK_AWIGN(MC_CMD_ ## _fiewd ## _OFST, 4) >> 2))

#define MCDI_BYTE(_buf, _fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 1),	\
	 *MCDI_PTW(_buf, _fiewd))
#define MCDI_WOWD(_buf, _fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 2),	\
	 we16_to_cpu(*(__fowce const __we16 *)MCDI_PTW(_buf, _fiewd)))
#define MCDI_SET_DWOWD(_buf, _fiewd, _vawue)				\
	CDX_POPUWATE_DWOWD_1(*_MCDI_DWOWD(_buf, _fiewd), CDX_DWOWD, _vawue)
#define MCDI_DWOWD(_buf, _fiewd)					\
	CDX_DWOWD_FIEWD(*_MCDI_DWOWD(_buf, _fiewd), CDX_DWOWD)
#define MCDI_POPUWATE_DWOWD_1(_buf, _fiewd, _name1, _vawue1)		\
	CDX_POPUWATE_DWOWD_1(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1)
#define MCDI_SET_QWOWD(_buf, _fiewd, _vawue)				\
	do {								\
		CDX_POPUWATE_DWOWD_1(_MCDI_DWOWD(_buf, _fiewd)[0],	\
				     CDX_DWOWD, (u32)(_vawue));	\
		CDX_POPUWATE_DWOWD_1(_MCDI_DWOWD(_buf, _fiewd)[1],	\
				     CDX_DWOWD, (u64)(_vawue) >> 32);	\
	} whiwe (0)
#define MCDI_QWOWD(_buf, _fiewd)					\
	(CDX_DWOWD_FIEWD(_MCDI_DWOWD(_buf, _fiewd)[0], CDX_DWOWD) |	\
	(u64)CDX_DWOWD_FIEWD(_MCDI_DWOWD(_buf, _fiewd)[1], CDX_DWOWD) << 32)

#endif /* CDX_MCDI_H */
