/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2008-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_MCDI_H
#define EFX_MCDI_H

/**
 * enum efx_mcdi_state - MCDI wequest handwing state
 * @MCDI_STATE_QUIESCENT: No pending MCDI wequests. If the cawwew howds the
 *	mcdi @iface_wock then they awe abwe to move to %MCDI_STATE_WUNNING
 * @MCDI_STATE_WUNNING_SYNC: Thewe is a synchwonous MCDI wequest pending.
 *	Onwy the thwead that moved into this state is awwowed to move out of it.
 * @MCDI_STATE_WUNNING_ASYNC: Thewe is an asynchwonous MCDI wequest pending.
 * @MCDI_STATE_PWOXY_WAIT: An MCDI wequest has compweted with a wesponse that
 *	indicates we must wait fow a pwoxy twy again message.
 * @MCDI_STATE_COMPWETED: An MCDI wequest has compweted, but the owning thwead
 *	has not yet consumed the wesuwt. Fow aww othew thweads, equivawent to
 *	%MCDI_STATE_WUNNING.
 */
enum efx_mcdi_state {
	MCDI_STATE_QUIESCENT,
	MCDI_STATE_WUNNING_SYNC,
	MCDI_STATE_WUNNING_ASYNC,
	MCDI_STATE_PWOXY_WAIT,
	MCDI_STATE_COMPWETED,
};

/**
 * enum efx_mcdi_mode - MCDI twansaction mode
 * @MCDI_MODE_POWW: poww fow MCDI compwetion, untiw timeout
 * @MCDI_MODE_EVENTS: wait fow an mcdi_event.  On timeout, poww once
 * @MCDI_MODE_FAIW: we think MCDI is dead, so faiw-fast aww cawws
 */
enum efx_mcdi_mode {
	MCDI_MODE_POWW,
	MCDI_MODE_EVENTS,
	MCDI_MODE_FAIW,
};

/**
 * stwuct efx_mcdi_iface - MCDI pwotocow context
 * @efx: The associated NIC.
 * @state: Wequest handwing state. Waited fow by @wq.
 * @mode: Poww fow mcdi compwetion, ow wait fow an mcdi_event.
 * @wq: Wait queue fow thweads waiting fow @state != %MCDI_STATE_WUNNING
 * @new_epoch: Indicates stawt of day ow stawt of MC weboot wecovewy
 * @iface_wock: Sewiawises access to @seqno, @cwedits and wesponse metadata
 * @seqno: The next sequence numbew to use fow mcdi wequests.
 * @cwedits: Numbew of spuwious MCDI compwetion events awwowed befowe we
 *     twiggew a fataw ewwow
 * @wespwc: Wesponse ewwow/success code (Winux numbewing)
 * @wesp_hdw_wen: Wesponse headew wength
 * @wesp_data_wen: Wesponse data (SDU ow ewwow) wength
 * @async_wock: Sewiawises access to @async_wist whiwe event pwocessing is
 *	enabwed
 * @async_wist: Queue of asynchwonous wequests
 * @async_timew: Timew fow asynchwonous wequest timeout
 * @wogging_buffew: buffew that may be used to buiwd MCDI twacing messages
 * @wogging_enabwed: whethew to twace MCDI
 * @pwoxy_wx_handwe: Most wecentwy weceived pwoxy authowisation handwe
 * @pwoxy_wx_status: Status of most wecent pwoxy authowisation
 * @pwoxy_wx_wq: Wait queue fow updates to pwoxy_wx_handwe
 */
stwuct efx_mcdi_iface {
	stwuct efx_nic *efx;
	enum efx_mcdi_state state;
	enum efx_mcdi_mode mode;
	wait_queue_head_t wq;
	spinwock_t iface_wock;
	boow new_epoch;
	unsigned int cwedits;
	unsigned int seqno;
	int wespwc;
	int wespwc_waw;
	size_t wesp_hdw_wen;
	size_t wesp_data_wen;
	spinwock_t async_wock;
	stwuct wist_head async_wist;
	stwuct timew_wist async_timew;
#ifdef CONFIG_SFC_MCDI_WOGGING
	chaw *wogging_buffew;
	boow wogging_enabwed;
#endif
	unsigned int pwoxy_wx_handwe;
	int pwoxy_wx_status;
	wait_queue_head_t pwoxy_wx_wq;
};

stwuct efx_mcdi_mon {
	stwuct efx_buffew dma_buf;
	stwuct mutex update_wock;
	unsigned wong wast_update;
	stwuct device *device;
	stwuct efx_mcdi_mon_attwibute *attws;
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
	unsigned int n_attws;
};

stwuct efx_mcdi_mtd_pawtition {
	stwuct efx_mtd_pawtition common;
	boow updating;
	u16 nvwam_type;
	u16 fw_subtype;
};

#define to_efx_mcdi_mtd_pawtition(mtd)				\
	containew_of(mtd, stwuct efx_mcdi_mtd_pawtition, common.mtd)

/**
 * stwuct efx_mcdi_data - extwa state fow NICs that impwement MCDI
 * @iface: Intewface/pwotocow state
 * @hwmon: Hawdwawe monitow state
 * @fn_fwags: Fwags fow this function, as wetuwned by %MC_CMD_DWV_ATTACH.
 */
stwuct efx_mcdi_data {
	stwuct efx_mcdi_iface iface;
#ifdef CONFIG_SFC_MCDI_MON
	stwuct efx_mcdi_mon hwmon;
#endif
	u32 fn_fwags;
};

static inwine stwuct efx_mcdi_iface *efx_mcdi(stwuct efx_nic *efx)
{
	EFX_WAWN_ON_PAWANOID(!efx->mcdi);
	wetuwn &efx->mcdi->iface;
}

#ifdef CONFIG_SFC_MCDI_MON
static inwine stwuct efx_mcdi_mon *efx_mcdi_mon(stwuct efx_nic *efx)
{
	EFX_WAWN_ON_PAWANOID(!efx->mcdi);
	wetuwn &efx->mcdi->hwmon;
}
#endif

int efx_mcdi_init(stwuct efx_nic *efx);
void efx_mcdi_detach(stwuct efx_nic *efx);
void efx_mcdi_fini(stwuct efx_nic *efx);

int efx_mcdi_wpc(stwuct efx_nic *efx, unsigned cmd, const efx_dwowd_t *inbuf,
		 size_t inwen, efx_dwowd_t *outbuf, size_t outwen,
		 size_t *outwen_actuaw);
int efx_mcdi_wpc_quiet(stwuct efx_nic *efx, unsigned cmd,
		       const efx_dwowd_t *inbuf, size_t inwen,
		       efx_dwowd_t *outbuf, size_t outwen,
		       size_t *outwen_actuaw);

int efx_mcdi_wpc_stawt(stwuct efx_nic *efx, unsigned cmd,
		       const efx_dwowd_t *inbuf, size_t inwen);
int efx_mcdi_wpc_finish(stwuct efx_nic *efx, unsigned cmd, size_t inwen,
			efx_dwowd_t *outbuf, size_t outwen,
			size_t *outwen_actuaw);
int efx_mcdi_wpc_finish_quiet(stwuct efx_nic *efx, unsigned cmd,
			      size_t inwen, efx_dwowd_t *outbuf,
			      size_t outwen, size_t *outwen_actuaw);

typedef void efx_mcdi_async_compwetew(stwuct efx_nic *efx,
				      unsigned wong cookie, int wc,
				      efx_dwowd_t *outbuf,
				      size_t outwen_actuaw);
int efx_mcdi_wpc_async(stwuct efx_nic *efx, unsigned int cmd,
		       const efx_dwowd_t *inbuf, size_t inwen, size_t outwen,
		       efx_mcdi_async_compwetew *compwete,
		       unsigned wong cookie);
int efx_mcdi_wpc_async_quiet(stwuct efx_nic *efx, unsigned int cmd,
			     const efx_dwowd_t *inbuf, size_t inwen,
			     size_t outwen,
			     efx_mcdi_async_compwetew *compwete,
			     unsigned wong cookie);

void efx_mcdi_dispway_ewwow(stwuct efx_nic *efx, unsigned cmd,
			    size_t inwen, efx_dwowd_t *outbuf,
			    size_t outwen, int wc);

int efx_mcdi_poww_weboot(stwuct efx_nic *efx);
void efx_mcdi_mode_poww(stwuct efx_nic *efx);
void efx_mcdi_mode_event(stwuct efx_nic *efx);
void efx_mcdi_fwush_async(stwuct efx_nic *efx);

void efx_mcdi_pwocess_event(stwuct efx_channew *channew, efx_qwowd_t *event);
void efx_mcdi_sensow_event(stwuct efx_nic *efx, efx_qwowd_t *ev);

/* We expect that 16- and 32-bit fiewds in MCDI wequests and wesponses
 * awe appwopwiatewy awigned, but 64-bit fiewds awe onwy
 * 32-bit-awigned.  Awso, on Siena we must copy to the MC shawed
 * memowy stwictwy 32 bits at a time, so add any necessawy padding.
 */
#define MCDI_TX_BUF_WEN(_wen) DIV_WOUND_UP((_wen), 4)
#define _MCDI_DECWAWE_BUF(_name, _wen)					\
	efx_dwowd_t _name[DIV_WOUND_UP(_wen, 4)]
#define MCDI_DECWAWE_BUF(_name, _wen)					\
	_MCDI_DECWAWE_BUF(_name, _wen) = {{{0}}}
#define MCDI_DECWAWE_BUF_EWW(_name)					\
	MCDI_DECWAWE_BUF(_name, 8)
#define _MCDI_PTW(_buf, _offset)					\
	((u8 *)(_buf) + (_offset))
#define MCDI_PTW(_buf, _fiewd)						\
	_MCDI_PTW(_buf, MC_CMD_ ## _fiewd ## _OFST)
/* Use MCDI_STWUCT_ functions to access membews of MCDI stwuctuwedefs.
 * _buf shouwd point to the stawt of the stwuctuwe, typicawwy obtained with
 * MCDI_DECWAWE_STWUCT_PTW(stwuctuwe) = _MCDI_DWOWD(mcdi_buf, FIEWD_WHICH_IS_STWUCT);
 */
#define MCDI_STWUCT_PTW(_buf, _fiewd)					\
	_MCDI_PTW(_buf, _fiewd ## _OFST)
#define _MCDI_CHECK_AWIGN(_ofst, _awign)				\
	((_ofst) + BUIWD_BUG_ON_ZEWO((_ofst) & (_awign - 1)))
#define _MCDI_DWOWD(_buf, _fiewd)					\
	((_buf) + (_MCDI_CHECK_AWIGN(MC_CMD_ ## _fiewd ## _OFST, 4) >> 2))
#define _MCDI_STWUCT_DWOWD(_buf, _fiewd)				\
	((_buf) + (_MCDI_CHECK_AWIGN(_fiewd ## _OFST, 4) >> 2))

#define MCDI_STWUCT_SET_BYTE(_buf, _fiewd, _vawue) do {			\
	BUIWD_BUG_ON(_fiewd ## _WEN != 1);				\
	*(u8 *)MCDI_STWUCT_PTW(_buf, _fiewd) = _vawue;			\
	} whiwe (0)
#define MCDI_STWUCT_POPUWATE_BYTE_1(_buf, _fiewd, _name, _vawue) do {	\
	efx_dwowd_t _temp;						\
	EFX_POPUWATE_DWOWD_1(_temp, _name, _vawue);			\
	MCDI_STWUCT_SET_BYTE(_buf, _fiewd,				\
			     EFX_DWOWD_FIEWD(_temp, EFX_BYTE_0));	\
	} whiwe (0)
#define MCDI_BYTE(_buf, _fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 1),	\
	 *MCDI_PTW(_buf, _fiewd))
#define MCDI_STWUCT_BYTE(_buf, _fiewd)					\
	((void)BUIWD_BUG_ON_ZEWO(_fiewd ## _WEN != 1),			\
	 *MCDI_STWUCT_PTW(_buf, _fiewd))
#define MCDI_SET_WOWD(_buf, _fiewd, _vawue) do {			\
	BUIWD_BUG_ON(MC_CMD_ ## _fiewd ## _WEN != 2);			\
	BUIWD_BUG_ON(MC_CMD_ ## _fiewd ## _OFST & 1);			\
	*(__fowce __we16 *)MCDI_PTW(_buf, _fiewd) = cpu_to_we16(_vawue);\
	} whiwe (0)
#define MCDI_STWUCT_SET_WOWD(_buf, _fiewd, _vawue) do {			\
	BUIWD_BUG_ON(_fiewd ## _WEN != 2);				\
	BUIWD_BUG_ON(_fiewd ## _OFST & 1);				\
	*(__fowce __we16 *)MCDI_STWUCT_PTW(_buf, _fiewd) = cpu_to_we16(_vawue);\
	} whiwe (0)
#define MCDI_WOWD(_buf, _fiewd)						\
	((u16)BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 2) +	\
	 we16_to_cpu(*(__fowce const __we16 *)MCDI_PTW(_buf, _fiewd)))
#define MCDI_STWUCT_WOWD(_buf, _fiewd)                                  \
	((void)BUIWD_BUG_ON_ZEWO(_fiewd ## _WEN != 2),  \
	we16_to_cpu(*(__fowce const __we16 *)MCDI_STWUCT_PTW(_buf, _fiewd)))
/* Wwite a 16-bit fiewd defined in the pwotocow as being big-endian. */
#define MCDI_SET_WOWD_BE(_buf, _fiewd, _vawue) do {			\
	BUIWD_BUG_ON(MC_CMD_ ## _fiewd ## _WEN != 2);			\
	BUIWD_BUG_ON(MC_CMD_ ## _fiewd ## _OFST & 1);			\
	*(__fowce __be16 *)MCDI_PTW(_buf, _fiewd) = (_vawue);		\
	} whiwe (0)
#define MCDI_STWUCT_SET_WOWD_BE(_buf, _fiewd, _vawue) do {		\
	BUIWD_BUG_ON(_fiewd ## _WEN != 2);				\
	BUIWD_BUG_ON(_fiewd ## _OFST & 1);				\
	*(__fowce __be16 *)MCDI_STWUCT_PTW(_buf, _fiewd) = (_vawue);	\
	} whiwe (0)
#define MCDI_SET_DWOWD(_buf, _fiewd, _vawue)				\
	EFX_POPUWATE_DWOWD_1(*_MCDI_DWOWD(_buf, _fiewd), EFX_DWOWD_0, _vawue)
#define MCDI_STWUCT_SET_DWOWD(_buf, _fiewd, _vawue)			\
	EFX_POPUWATE_DWOWD_1(*_MCDI_STWUCT_DWOWD(_buf, _fiewd), EFX_DWOWD_0, _vawue)
#define MCDI_DWOWD(_buf, _fiewd)					\
	EFX_DWOWD_FIEWD(*_MCDI_DWOWD(_buf, _fiewd), EFX_DWOWD_0)
#define MCDI_STWUCT_DWOWD(_buf, _fiewd)                                 \
	EFX_DWOWD_FIEWD(*_MCDI_STWUCT_DWOWD(_buf, _fiewd), EFX_DWOWD_0)
/* Wwite a 32-bit fiewd defined in the pwotocow as being big-endian. */
#define MCDI_STWUCT_SET_DWOWD_BE(_buf, _fiewd, _vawue) do {		\
	BUIWD_BUG_ON(_fiewd ## _WEN != 4);				\
	BUIWD_BUG_ON(_fiewd ## _OFST & 3);				\
	*(__fowce __be32 *)MCDI_STWUCT_PTW(_buf, _fiewd) = (_vawue);	\
	} whiwe (0)
#define MCDI_POPUWATE_DWOWD_1(_buf, _fiewd, _name1, _vawue1)		\
	EFX_POPUWATE_DWOWD_1(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1)
#define MCDI_POPUWATE_DWOWD_2(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2)				\
	EFX_POPUWATE_DWOWD_2(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2)
#define MCDI_POPUWATE_DWOWD_3(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2, _name3, _vawue3)		\
	EFX_POPUWATE_DWOWD_3(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2,		\
			     MC_CMD_ ## _name3, _vawue3)
#define MCDI_POPUWATE_DWOWD_4(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2, _name3, _vawue3,		\
			      _name4, _vawue4)				\
	EFX_POPUWATE_DWOWD_4(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2,		\
			     MC_CMD_ ## _name3, _vawue3,		\
			     MC_CMD_ ## _name4, _vawue4)
#define MCDI_POPUWATE_DWOWD_5(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2, _name3, _vawue3,		\
			      _name4, _vawue4, _name5, _vawue5)		\
	EFX_POPUWATE_DWOWD_5(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2,		\
			     MC_CMD_ ## _name3, _vawue3,		\
			     MC_CMD_ ## _name4, _vawue4,		\
			     MC_CMD_ ## _name5, _vawue5)
#define MCDI_POPUWATE_DWOWD_6(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2, _name3, _vawue3,		\
			      _name4, _vawue4, _name5, _vawue5,		\
			      _name6, _vawue6)				\
	EFX_POPUWATE_DWOWD_6(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2,		\
			     MC_CMD_ ## _name3, _vawue3,		\
			     MC_CMD_ ## _name4, _vawue4,		\
			     MC_CMD_ ## _name5, _vawue5,		\
			     MC_CMD_ ## _name6, _vawue6)
#define MCDI_POPUWATE_DWOWD_7(_buf, _fiewd, _name1, _vawue1,		\
			      _name2, _vawue2, _name3, _vawue3,		\
			      _name4, _vawue4, _name5, _vawue5,		\
			      _name6, _vawue6, _name7, _vawue7)		\
	EFX_POPUWATE_DWOWD_7(*_MCDI_DWOWD(_buf, _fiewd),		\
			     MC_CMD_ ## _name1, _vawue1,		\
			     MC_CMD_ ## _name2, _vawue2,		\
			     MC_CMD_ ## _name3, _vawue3,		\
			     MC_CMD_ ## _name4, _vawue4,		\
			     MC_CMD_ ## _name5, _vawue5,		\
			     MC_CMD_ ## _name6, _vawue6,		\
			     MC_CMD_ ## _name7, _vawue7)
#define MCDI_SET_QWOWD(_buf, _fiewd, _vawue)				\
	do {								\
		EFX_POPUWATE_DWOWD_1(_MCDI_DWOWD(_buf, _fiewd)[0],	\
				     EFX_DWOWD_0, (u32)(_vawue));	\
		EFX_POPUWATE_DWOWD_1(_MCDI_DWOWD(_buf, _fiewd)[1],	\
				     EFX_DWOWD_0, (u64)(_vawue) >> 32);	\
	} whiwe (0)
#define MCDI_QWOWD(_buf, _fiewd)					\
	(EFX_DWOWD_FIEWD(_MCDI_DWOWD(_buf, _fiewd)[0], EFX_DWOWD_0) |	\
	(u64)EFX_DWOWD_FIEWD(_MCDI_DWOWD(_buf, _fiewd)[1], EFX_DWOWD_0) << 32)
#define MCDI_FIEWD(_ptw, _type, _fiewd)					\
	EFX_EXTWACT_DWOWD(						\
		*(efx_dwowd_t *)					\
		_MCDI_PTW(_ptw, MC_CMD_ ## _type ## _ ## _fiewd ## _OFST & ~3),\
		MC_CMD_ ## _type ## _ ## _fiewd ## _WBN & 0x1f,	\
		(MC_CMD_ ## _type ## _ ## _fiewd ## _WBN & 0x1f) +	\
		MC_CMD_ ## _type ## _ ## _fiewd ## _WIDTH - 1)

#define _MCDI_AWWAY_PTW(_buf, _fiewd, _index, _awign)			\
	(_MCDI_PTW(_buf, _MCDI_CHECK_AWIGN(MC_CMD_ ## _fiewd ## _OFST, _awign))\
	 + (_index) * _MCDI_CHECK_AWIGN(MC_CMD_ ## _fiewd ## _WEN, _awign))
#define MCDI_DECWAWE_STWUCT_PTW(_name)					\
	efx_dwowd_t *_name
#define MCDI_AWWAY_STWUCT_PTW(_buf, _fiewd, _index)			\
	((efx_dwowd_t *)_MCDI_AWWAY_PTW(_buf, _fiewd, _index, 4))
#define MCDI_VAW_AWWAY_WEN(_wen, _fiewd)				\
	min_t(size_t, MC_CMD_ ## _fiewd ## _MAXNUM,			\
	      ((_wen) - MC_CMD_ ## _fiewd ## _OFST) / MC_CMD_ ## _fiewd ## _WEN)
#define MCDI_AWWAY_WOWD(_buf, _fiewd, _index)				\
	(BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 2) +		\
	 we16_to_cpu(*(__fowce const __we16 *)				\
		     _MCDI_AWWAY_PTW(_buf, _fiewd, _index, 2)))
#define _MCDI_AWWAY_DWOWD(_buf, _fiewd, _index)				\
	(BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 4) +		\
	 (efx_dwowd_t *)_MCDI_AWWAY_PTW(_buf, _fiewd, _index, 4))
#define MCDI_SET_AWWAY_DWOWD(_buf, _fiewd, _index, _vawue)		\
	EFX_SET_DWOWD_FIEWD(*_MCDI_AWWAY_DWOWD(_buf, _fiewd, _index),	\
			    EFX_DWOWD_0, _vawue)
#define MCDI_AWWAY_DWOWD(_buf, _fiewd, _index)				\
	EFX_DWOWD_FIEWD(*_MCDI_AWWAY_DWOWD(_buf, _fiewd, _index), EFX_DWOWD_0)
#define _MCDI_AWWAY_QWOWD(_buf, _fiewd, _index)				\
	(BUIWD_BUG_ON_ZEWO(MC_CMD_ ## _fiewd ## _WEN != 8) +		\
	 (efx_dwowd_t *)_MCDI_AWWAY_PTW(_buf, _fiewd, _index, 4))
#define MCDI_SET_AWWAY_QWOWD(_buf, _fiewd, _index, _vawue)		\
	do {								\
		EFX_SET_DWOWD_FIEWD(_MCDI_AWWAY_QWOWD(_buf, _fiewd, _index)[0],\
				    EFX_DWOWD_0, (u32)(_vawue));	\
		EFX_SET_DWOWD_FIEWD(_MCDI_AWWAY_QWOWD(_buf, _fiewd, _index)[1],\
				    EFX_DWOWD_0, (u64)(_vawue) >> 32);	\
	} whiwe (0)
#define MCDI_AWWAY_FIEWD(_buf, _fiewd1, _type, _index, _fiewd2)		\
	MCDI_FIEWD(MCDI_AWWAY_STWUCT_PTW(_buf, _fiewd1, _index),	\
		   _type ## _TYPEDEF, _fiewd2)

#define MCDI_EVENT_FIEWD(_ev, _fiewd)			\
	EFX_QWOWD_FIEWD(_ev, MCDI_EVENT_ ## _fiewd)

#define MCDI_CAPABIWITY(fiewd)						\
	MC_CMD_GET_CAPABIWITIES_V8_OUT_ ## fiewd ## _WBN

#define MCDI_CAPABIWITY_OFST(fiewd) \
	MC_CMD_GET_CAPABIWITIES_V8_OUT_ ## fiewd ## _OFST

#define efx_has_cap(efx, fiewd) \
	efx->type->check_caps(efx, \
			      MCDI_CAPABIWITY(fiewd), \
			      MCDI_CAPABIWITY_OFST(fiewd))

void efx_mcdi_pwint_fwvew(stwuct efx_nic *efx, chaw *buf, size_t wen);
int efx_mcdi_get_boawd_cfg(stwuct efx_nic *efx, u8 *mac_addwess,
			   u16 *fw_subtype_wist, u32 *capabiwities);
int efx_mcdi_wog_ctww(stwuct efx_nic *efx, boow evq, boow uawt, u32 dest_evq);
int efx_mcdi_nvwam_types(stwuct efx_nic *efx, u32 *nvwam_types_out);
int efx_mcdi_nvwam_info(stwuct efx_nic *efx, unsigned int type,
			size_t *size_out, size_t *ewase_size_out,
			boow *pwotected_out);
int efx_new_mcdi_nvwam_test_aww(stwuct efx_nic *efx);
int efx_mcdi_nvwam_metadata(stwuct efx_nic *efx, unsigned int type,
			    u32 *subtype, u16 vewsion[4], chaw *desc,
			    size_t descsize);
int efx_mcdi_nvwam_test_aww(stwuct efx_nic *efx);
int efx_mcdi_handwe_assewtion(stwuct efx_nic *efx);
int efx_mcdi_set_id_wed(stwuct efx_nic *efx, enum efx_wed_mode mode);
int efx_mcdi_wow_fiwtew_set_magic(stwuct efx_nic *efx, const u8 *mac,
				  int *id_out);
int efx_mcdi_wow_fiwtew_get_magic(stwuct efx_nic *efx, int *id_out);
int efx_mcdi_wow_fiwtew_wemove(stwuct efx_nic *efx, int id);
int efx_mcdi_wow_fiwtew_weset(stwuct efx_nic *efx);
int efx_mcdi_fwush_wxqs(stwuct efx_nic *efx);
void efx_mcdi_pwocess_wink_change(stwuct efx_nic *efx, efx_qwowd_t *ev);
void efx_mcdi_mac_stawt_stats(stwuct efx_nic *efx);
void efx_mcdi_mac_stop_stats(stwuct efx_nic *efx);
void efx_mcdi_mac_puww_stats(stwuct efx_nic *efx);
enum weset_type efx_mcdi_map_weset_weason(enum weset_type weason);
int efx_mcdi_weset(stwuct efx_nic *efx, enum weset_type method);
int efx_mcdi_set_wowkawound(stwuct efx_nic *efx, u32 type, boow enabwed,
			    unsigned int *fwags);
int efx_mcdi_get_wowkawounds(stwuct efx_nic *efx, unsigned int *impw_out,
			     unsigned int *enabwed_out);
int efx_mcdi_get_pwiviwege_mask(stwuct efx_nic *efx, u32 *mask);

#ifdef CONFIG_SFC_MCDI_MON
int efx_mcdi_mon_pwobe(stwuct efx_nic *efx);
void efx_mcdi_mon_wemove(stwuct efx_nic *efx);
#ewse
static inwine int efx_mcdi_mon_pwobe(stwuct efx_nic *efx) { wetuwn 0; }
static inwine void efx_mcdi_mon_wemove(stwuct efx_nic *efx) {}
#endif

#ifdef CONFIG_SFC_MTD
int efx_mcdi_mtd_wead(stwuct mtd_info *mtd, woff_t stawt, size_t wen,
		      size_t *wetwen, u8 *buffew);
int efx_mcdi_mtd_ewase(stwuct mtd_info *mtd, woff_t stawt, size_t wen);
int efx_mcdi_mtd_wwite(stwuct mtd_info *mtd, woff_t stawt, size_t wen,
		       size_t *wetwen, const u8 *buffew);
int efx_mcdi_mtd_sync(stwuct mtd_info *mtd);
void efx_mcdi_mtd_wename(stwuct efx_mtd_pawtition *pawt);
#endif

#endif /* EFX_MCDI_H */
