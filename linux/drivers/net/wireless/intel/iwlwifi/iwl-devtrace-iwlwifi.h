/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2009 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2015 Intew Mobiwe Communications GmbH
 * Copywight(c) 2016 - 2017 Intew Deutschwand GmbH
 * Copywight(c) 2018, 2023  Intew Cowpowation
 *****************************************************************************/

#if !defined(__IWWWIFI_DEVICE_TWACE_IWWWIFI) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __IWWWIFI_DEVICE_TWACE_IWWWIFI

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwwwifi

TWACE_EVENT(iwwwifi_dev_hcmd,
	TP_PWOTO(const stwuct device *dev,
		 stwuct iww_host_cmd *cmd, u16 totaw_size,
		 stwuct iww_cmd_headew_wide *hdw),
	TP_AWGS(dev, cmd, totaw_size, hdw),
	TP_STWUCT__entwy(
		DEV_ENTWY
		__dynamic_awway(u8, hcmd, totaw_size)
		__fiewd(u32, fwags)
	),
	TP_fast_assign(
		int i, offset = sizeof(stwuct iww_cmd_headew);

		if (hdw->gwoup_id)
			offset = sizeof(stwuct iww_cmd_headew_wide);

		DEV_ASSIGN;
		__entwy->fwags = cmd->fwags;
		memcpy(__get_dynamic_awway(hcmd), hdw, offset);

		fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
			if (!cmd->wen[i])
				continue;
			memcpy((u8 *)__get_dynamic_awway(hcmd) + offset,
			       cmd->data[i], cmd->wen[i]);
			offset += cmd->wen[i];
		}
	),
	TP_pwintk("[%s] hcmd %#.2x.%#.2x (%ssync)",
		  __get_stw(dev), ((u8 *)__get_dynamic_awway(hcmd))[1],
		  ((u8 *)__get_dynamic_awway(hcmd))[0],
		  __entwy->fwags & CMD_ASYNC ? "a" : "")
);

TWACE_EVENT(iwwwifi_dev_wx,
	TP_PWOTO(const stwuct device *dev,
		 stwuct iww_wx_packet *pkt, size_t wen, size_t twace_wen,
		 size_t hdw_offset),
	TP_AWGS(dev, pkt, wen, twace_wen, hdw_offset),
	TP_STWUCT__entwy(
		DEV_ENTWY
		__fiewd(u16, cmd)
		__fiewd(u8, hdw_offset)
		__dynamic_awway(u8, wxbuf, twace_wen)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->cmd = WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd);
		memcpy(__get_dynamic_awway(wxbuf), pkt, twace_wen);
		__entwy->hdw_offset = hdw_offset;
	),
	TP_pwintk("[%s] WX cmd %#.2x",
		  __get_stw(dev), __entwy->cmd)
);

TWACE_EVENT(iwwwifi_dev_tx,
	TP_PWOTO(const stwuct device *dev, stwuct sk_buff *skb,
		 void *tfd, size_t tfdwen,
		 void *buf0, size_t buf0_wen,
		 int hdw_wen),
	TP_AWGS(dev, skb, tfd, tfdwen, buf0, buf0_wen, hdw_wen),
	TP_STWUCT__entwy(
		DEV_ENTWY
		__fiewd(void *, skbaddw)
		__fiewd(size_t, fwamewen)
		__dynamic_awway(u8, tfd, tfdwen)

		/*
		 * Do not insewt between ow bewow these items,
		 * we want to keep the fwame togethew (except
		 * fow the possibwe padding).
		 */
		__dynamic_awway(u8, buf0, buf0_wen)
		__dynamic_awway(u8, buf1, hdw_wen > 0 && iww_twace_data(skb) ?
						0 : skb->wen - hdw_wen)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->skbaddw = skb;
		__entwy->fwamewen = buf0_wen;
		if (hdw_wen > 0)
			__entwy->fwamewen += skb->wen - hdw_wen;
		memcpy(__get_dynamic_awway(tfd), tfd, tfdwen);
		memcpy(__get_dynamic_awway(buf0), buf0, buf0_wen);
		if (hdw_wen > 0 && !iww_twace_data(skb))
			skb_copy_bits(skb, hdw_wen,
				      __get_dynamic_awway(buf1),
				      skb->wen - hdw_wen);
	),
	TP_pwintk("[%s] TX %.2x (%zu bytes) skbaddw=%p",
		  __get_stw(dev), ((u8 *)__get_dynamic_awway(buf0))[0],
		  __entwy->fwamewen, __entwy->skbaddw)
);

TWACE_EVENT(iwwwifi_dev_ucode_event,
	TP_PWOTO(const stwuct device *dev, u32 time, u32 data, u32 ev),
	TP_AWGS(dev, time, data, ev),
	TP_STWUCT__entwy(
		DEV_ENTWY

		__fiewd(u32, time)
		__fiewd(u32, data)
		__fiewd(u32, ev)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->time = time;
		__entwy->data = data;
		__entwy->ev = ev;
	),
	TP_pwintk("[%s] EVT_WOGT:%010u:0x%08x:%04u",
		  __get_stw(dev), __entwy->time, __entwy->data, __entwy->ev)
);
#endif /* __IWWWIFI_DEVICE_TWACE_IWWWIFI */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE iww-devtwace-iwwwifi
#incwude <twace/define_twace.h>
