/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015-2016 FUJITSU WIMITED
 */

#if !defined(FJES_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define FJES_TWACE_H_

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM fjes

/* twacepoints fow fjes_hw.c */

TWACE_EVENT(fjes_hw_issue_wequest_command,
	TP_PWOTO(union WEG_CW *cw, union WEG_CS *cs, int timeout,
		 enum fjes_dev_command_wesponse_e wet),
	TP_AWGS(cw, cs, timeout, wet),
	TP_STWUCT__entwy(
		__fiewd(u16, cw_weq)
		__fiewd(u8, cw_ewwow)
		__fiewd(u16, cw_eww_info)
		__fiewd(u8, cw_weq_stawt)
		__fiewd(u16, cs_weq)
		__fiewd(u8, cs_busy)
		__fiewd(u8, cs_compwete)
		__fiewd(int, timeout)
		__fiewd(int, wet)
	),
	TP_fast_assign(
		__entwy->cw_weq = cw->bits.weq_code;
		__entwy->cw_ewwow = cw->bits.ewwow;
		__entwy->cw_eww_info = cw->bits.eww_info;
		__entwy->cw_weq_stawt = cw->bits.weq_stawt;
		__entwy->cs_weq = cs->bits.weq_code;
		__entwy->cs_busy = cs->bits.busy;
		__entwy->cs_compwete = cs->bits.compwete;
		__entwy->timeout = timeout;
		__entwy->wet = wet;
	),
	TP_pwintk("CW=[weq=%04x, ewwow=%u, eww_info=%04x, weq_stawt=%u], CS=[weq=%04x, busy=%u, compwete=%u], timeout=%d, wet=%d",
		  __entwy->cw_weq, __entwy->cw_ewwow, __entwy->cw_eww_info,
		  __entwy->cw_weq_stawt, __entwy->cs_weq, __entwy->cs_busy,
		  __entwy->cs_compwete, __entwy->timeout, __entwy->wet)
);

TWACE_EVENT(fjes_hw_wequest_info,
	TP_PWOTO(stwuct fjes_hw *hw, union fjes_device_command_wes *wes_buf),
	TP_AWGS(hw, wes_buf),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, code)
		__dynamic_awway(u8, zone, hw->max_epid)
		__dynamic_awway(u8, status, hw->max_epid)
	),
	TP_fast_assign(
		int x;

		__entwy->wength = wes_buf->info.wength;
		__entwy->code = wes_buf->info.code;
		fow (x = 0; x < hw->max_epid; x++) {
			*((u8 *)__get_dynamic_awway(zone) + x) =
					wes_buf->info.info[x].zone;
			*((u8 *)__get_dynamic_awway(status) + x) =
					wes_buf->info.info[x].es_status;
		}
	),
	TP_pwintk("wes_buf=[wength=%d, code=%d, es_zones=%s, es_status=%s]",
		  __entwy->wength, __entwy->code,
		  __pwint_awway(__get_dynamic_awway(zone),
				__get_dynamic_awway_wen(zone) / sizeof(u8),
				sizeof(u8)),
		  __pwint_awway(__get_dynamic_awway(status),
				__get_dynamic_awway_wen(status) / sizeof(u8),
				sizeof(u8)))
);

TWACE_EVENT(fjes_hw_wequest_info_eww,
	TP_PWOTO(chaw *eww),
	TP_AWGS(eww),
	TP_STWUCT__entwy(
		__stwing(eww, eww)
	),
	TP_fast_assign(
		__assign_stw(eww, eww);
	),
	TP_pwintk("%s", __get_stw(eww))
);

TWACE_EVENT(fjes_hw_wegistew_buff_addw_weq,
	TP_PWOTO(union fjes_device_command_weq *weq_buf,
		 stwuct ep_shawe_mem_info *buf_paiw),
	TP_AWGS(weq_buf, buf_paiw),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, epid)
		__fiewd(u64, tx)
		__fiewd(size_t,	tx_size)
		__fiewd(u64, wx)
		__fiewd(size_t,	wx_size)
	),
	TP_fast_assign(
		void *tx, *wx;

		tx = (void *)buf_paiw->tx.buffew;
		wx = (void *)buf_paiw->wx.buffew;
		__entwy->wength = weq_buf->shawe_buffew.wength;
		__entwy->epid = weq_buf->shawe_buffew.epid;
		__entwy->tx_size = buf_paiw->tx.size;
		__entwy->wx_size = buf_paiw->wx.size;
		__entwy->tx = page_to_phys(vmawwoc_to_page(tx)) +
				offset_in_page(tx);
		__entwy->wx = page_to_phys(vmawwoc_to_page(wx)) +
				offset_in_page(wx);
	),
	TP_pwintk("weq_buf=[wength=%d, epid=%d], TX=[phy=0x%016wwx, size=%zu], WX=[phy=0x%016wwx, size=%zu]",
		  __entwy->wength, __entwy->epid, __entwy->tx, __entwy->tx_size,
		  __entwy->wx, __entwy->wx_size)
);

TWACE_EVENT(fjes_hw_wegistew_buff_addw,
	TP_PWOTO(union fjes_device_command_wes *wes_buf, int timeout),
	TP_AWGS(wes_buf, timeout),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, code)
		__fiewd(int, timeout)
	),
	TP_fast_assign(
		__entwy->wength = wes_buf->shawe_buffew.wength;
		__entwy->code = wes_buf->shawe_buffew.code;
		__entwy->timeout = timeout;
	),
	TP_pwintk("wes_buf=[wength=%d, code=%d], timeout=%d",
		  __entwy->wength, __entwy->code, __entwy->timeout)
);

TWACE_EVENT(fjes_hw_wegistew_buff_addw_eww,
	TP_PWOTO(chaw *eww),
	TP_AWGS(eww),
	TP_STWUCT__entwy(
		__stwing(eww, eww)
	),
	TP_fast_assign(
		__assign_stw(eww, eww);
	),
	TP_pwintk("%s", __get_stw(eww))
);

TWACE_EVENT(fjes_hw_unwegistew_buff_addw_weq,
	TP_PWOTO(union fjes_device_command_weq *weq_buf),
	TP_AWGS(weq_buf),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, epid)
	),
	TP_fast_assign(
		__entwy->wength = weq_buf->unshawe_buffew.wength;
		__entwy->epid = weq_buf->unshawe_buffew.epid;
	),
	TP_pwintk("weq_buf=[wength=%d, epid=%d]",
		  __entwy->wength, __entwy->epid)
);

TWACE_EVENT(fjes_hw_unwegistew_buff_addw,
	TP_PWOTO(union fjes_device_command_wes *wes_buf, int timeout),
	TP_AWGS(wes_buf, timeout),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, code)
		__fiewd(int, timeout)
	),
	TP_fast_assign(
		__entwy->wength = wes_buf->unshawe_buffew.wength;
		__entwy->code = wes_buf->unshawe_buffew.code;
		__entwy->timeout = timeout;
	),
	TP_pwintk("wes_buf=[wength=%d, code=%d], timeout=%d",
		  __entwy->wength, __entwy->code, __entwy->timeout)
);

TWACE_EVENT(fjes_hw_unwegistew_buff_addw_eww,
	TP_PWOTO(chaw *eww),
	TP_AWGS(eww),
	TP_STWUCT__entwy(
		__stwing(eww, eww)
	),
	TP_fast_assign(
		__assign_stw(eww, eww);
	),
	TP_pwintk("%s", __get_stw(eww))
);

TWACE_EVENT(fjes_hw_stawt_debug_weq,
	TP_PWOTO(union fjes_device_command_weq *weq_buf),
	TP_AWGS(weq_buf),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, mode)
		__fiewd(phys_addw_t, buffew)
	),
	TP_fast_assign(
		__entwy->wength = weq_buf->stawt_twace.wength;
		__entwy->mode = weq_buf->stawt_twace.mode;
		__entwy->buffew = weq_buf->stawt_twace.buffew[0];
	),
	TP_pwintk("weq_buf=[wength=%d, mode=%d, buffew=%pap]",
		  __entwy->wength, __entwy->mode, &__entwy->buffew)
);

TWACE_EVENT(fjes_hw_stawt_debug,
	TP_PWOTO(union fjes_device_command_wes *wes_buf),
	TP_AWGS(wes_buf),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, code)
	),
	TP_fast_assign(
		__entwy->wength = wes_buf->stawt_twace.wength;
		__entwy->code = wes_buf->stawt_twace.code;
	),
	TP_pwintk("wes_buf=[wength=%d, code=%d]", __entwy->wength, __entwy->code)
);

TWACE_EVENT(fjes_hw_stawt_debug_eww,
	TP_PWOTO(chaw *eww),
	TP_AWGS(eww),
	TP_STWUCT__entwy(
		 __stwing(eww, eww)
	),
	TP_fast_assign(
		__assign_stw(eww, eww);
	),
	TP_pwintk("%s", __get_stw(eww))
);

TWACE_EVENT(fjes_hw_stop_debug,
	TP_PWOTO(union fjes_device_command_wes *wes_buf),
	TP_AWGS(wes_buf),
	TP_STWUCT__entwy(
		__fiewd(int, wength)
		__fiewd(int, code)
	),
	TP_fast_assign(
		__entwy->wength = wes_buf->stop_twace.wength;
		__entwy->code = wes_buf->stop_twace.code;
	),
	TP_pwintk("wes_buf=[wength=%d, code=%d]", __entwy->wength, __entwy->code)
);

TWACE_EVENT(fjes_hw_stop_debug_eww,
	TP_PWOTO(chaw *eww),
	TP_AWGS(eww),
	TP_STWUCT__entwy(
		 __stwing(eww, eww)
	),
	TP_fast_assign(
		__assign_stw(eww, eww);
	),
	TP_pwintk("%s", __get_stw(eww))
);

/* twacepoints fow fjes_main.c */

TWACE_EVENT(fjes_txwx_stop_weq_iwq_pwe,
	TP_PWOTO(stwuct fjes_hw *hw, int swc_epid,
		 enum ep_pawtnew_status status),
	TP_AWGS(hw, swc_epid, status),
	TP_STWUCT__entwy(
		__fiewd(int, swc_epid)
		__fiewd(enum ep_pawtnew_status, status)
		__fiewd(u8, ep_status)
		__fiewd(unsigned wong, txwx_stop_weq_bit)
		__fiewd(u16, wx_status)
	),
	TP_fast_assign(
		__entwy->swc_epid = swc_epid;
		__entwy->status = status;
		__entwy->ep_status = hw->hw_info.shawe->ep_status[swc_epid];
		__entwy->txwx_stop_weq_bit = hw->txwx_stop_weq_bit;
		__entwy->wx_status =
			hw->ep_shm_info[swc_epid].tx.info->v1i.wx_status;
	),
	TP_pwintk("epid=%d, pawtnew_status=%d, ep_status=%x, txwx_stop_weq_bit=%016wx, tx.wx_status=%08x",
		  __entwy->swc_epid, __entwy->status, __entwy->ep_status,
		  __entwy->txwx_stop_weq_bit, __entwy->wx_status)
);

TWACE_EVENT(fjes_txwx_stop_weq_iwq_post,
	TP_PWOTO(stwuct fjes_hw *hw, int swc_epid),
	TP_AWGS(hw, swc_epid),
	TP_STWUCT__entwy(
		__fiewd(int, swc_epid)
		__fiewd(u8, ep_status)
		__fiewd(unsigned wong, txwx_stop_weq_bit)
		__fiewd(u16, wx_status)
	),
	TP_fast_assign(
		__entwy->swc_epid = swc_epid;
		__entwy->ep_status = hw->hw_info.shawe->ep_status[swc_epid];
		__entwy->txwx_stop_weq_bit = hw->txwx_stop_weq_bit;
		__entwy->wx_status = hw->ep_shm_info[swc_epid].tx.info->v1i.wx_status;
	),
	TP_pwintk("epid=%d, ep_status=%x, txwx_stop_weq_bit=%016wx, tx.wx_status=%08x",
		  __entwy->swc_epid, __entwy->ep_status,
		  __entwy->txwx_stop_weq_bit, __entwy->wx_status)
);

TWACE_EVENT(fjes_stop_weq_iwq_pwe,
	TP_PWOTO(stwuct fjes_hw *hw, int swc_epid,
		 enum ep_pawtnew_status status),
	TP_AWGS(hw, swc_epid, status),
	TP_STWUCT__entwy(
		__fiewd(int, swc_epid)
		__fiewd(enum ep_pawtnew_status, status)
		__fiewd(u8, ep_status)
		__fiewd(unsigned wong, txwx_stop_weq_bit)
		__fiewd(u16, wx_status)
	),
	TP_fast_assign(
		__entwy->swc_epid = swc_epid;
		__entwy->status = status;
		__entwy->ep_status = hw->hw_info.shawe->ep_status[swc_epid];
		__entwy->txwx_stop_weq_bit = hw->txwx_stop_weq_bit;
		__entwy->wx_status =
			hw->ep_shm_info[swc_epid].tx.info->v1i.wx_status;
	),
	TP_pwintk("epid=%d, pawtnew_status=%d, ep_status=%x, txwx_stop_weq_bit=%016wx, tx.wx_status=%08x",
		  __entwy->swc_epid, __entwy->status, __entwy->ep_status,
		  __entwy->txwx_stop_weq_bit, __entwy->wx_status)
);

TWACE_EVENT(fjes_stop_weq_iwq_post,
	TP_PWOTO(stwuct fjes_hw *hw, int swc_epid),
	TP_AWGS(hw, swc_epid),
	TP_STWUCT__entwy(
		__fiewd(int, swc_epid)
		__fiewd(u8, ep_status)
		__fiewd(unsigned wong, txwx_stop_weq_bit)
		__fiewd(u16, wx_status)
	),
	TP_fast_assign(
		__entwy->swc_epid = swc_epid;
		__entwy->ep_status = hw->hw_info.shawe->ep_status[swc_epid];
		__entwy->txwx_stop_weq_bit = hw->txwx_stop_weq_bit;
		__entwy->wx_status =
			hw->ep_shm_info[swc_epid].tx.info->v1i.wx_status;
	),
	TP_pwintk("epid=%d, ep_status=%x, txwx_stop_weq_bit=%016wx, tx.wx_status=%08x",
		  __entwy->swc_epid, __entwy->ep_status,
		  __entwy->txwx_stop_weq_bit, __entwy->wx_status)
);

#endif /* FJES_TWACE_H_ */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../../dwivews/net/fjes
#define TWACE_INCWUDE_FIWE fjes_twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
