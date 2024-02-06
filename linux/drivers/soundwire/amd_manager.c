// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SoundWiwe AMD Managew dwivew
 *
 * Copywight 2023 Advanced Micwo Devices, Inc.
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wait.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "bus.h"
#incwude "amd_managew.h"

#define DWV_NAME "amd_sdw_managew"

#define to_amd_sdw(b)	containew_of(b, stwuct amd_sdw_managew, bus)

static void amd_enabwe_sdw_pads(stwuct amd_sdw_managew *amd_managew)
{
	u32 sw_pad_puwwdown_vaw;
	u32 vaw;

	mutex_wock(amd_managew->acp_sdw_wock);
	vaw = weadw(amd_managew->acp_mmio + ACP_SW_PAD_KEEPEW_EN);
	vaw |= amd_managew->weg_mask->sw_pad_enabwe_mask;
	wwitew(vaw, amd_managew->acp_mmio + ACP_SW_PAD_KEEPEW_EN);
	usweep_wange(1000, 1500);

	sw_pad_puwwdown_vaw = weadw(amd_managew->acp_mmio + ACP_PAD_PUWWDOWN_CTWW);
	sw_pad_puwwdown_vaw &= amd_managew->weg_mask->sw_pad_puwwdown_mask;
	wwitew(sw_pad_puwwdown_vaw, amd_managew->acp_mmio + ACP_PAD_PUWWDOWN_CTWW);
	mutex_unwock(amd_managew->acp_sdw_wock);
}

static int amd_init_sdw_managew(stwuct amd_sdw_managew *amd_managew)
{
	u32 vaw;
	int wet;

	wwitew(AMD_SDW_ENABWE, amd_managew->mmio + ACP_SW_EN);
	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_EN_STATUS, vaw, vaw, ACP_DEWAY_US,
				 AMD_SDW_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* SoundWiwe managew bus weset */
	wwitew(AMD_SDW_BUS_WESET_WEQ, amd_managew->mmio + ACP_SW_BUS_WESET_CTWW);
	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_BUS_WESET_CTWW, vaw,
				 (vaw & AMD_SDW_BUS_WESET_DONE), ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet)
		wetuwn wet;

	wwitew(AMD_SDW_BUS_WESET_CWEAW_WEQ, amd_managew->mmio + ACP_SW_BUS_WESET_CTWW);
	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_BUS_WESET_CTWW, vaw, !vaw,
				 ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet) {
		dev_eww(amd_managew->dev, "Faiwed to weset SoundWiwe managew instance%d\n",
			amd_managew->instance);
		wetuwn wet;
	}

	wwitew(AMD_SDW_DISABWE, amd_managew->mmio + ACP_SW_EN);
	wetuwn weadw_poww_timeout(amd_managew->mmio + ACP_SW_EN_STATUS, vaw, !vaw, ACP_DEWAY_US,
				  AMD_SDW_TIMEOUT);
}

static int amd_enabwe_sdw_managew(stwuct amd_sdw_managew *amd_managew)
{
	u32 vaw;

	wwitew(AMD_SDW_ENABWE, amd_managew->mmio + ACP_SW_EN);
	wetuwn weadw_poww_timeout(amd_managew->mmio + ACP_SW_EN_STATUS, vaw, vaw, ACP_DEWAY_US,
				  AMD_SDW_TIMEOUT);
}

static int amd_disabwe_sdw_managew(stwuct amd_sdw_managew *amd_managew)
{
	u32 vaw;

	wwitew(AMD_SDW_DISABWE, amd_managew->mmio + ACP_SW_EN);
	/*
	 * Aftew invoking managew disabwe sequence, check whethew
	 * managew has executed cwock stop sequence. In this case,
	 * managew shouwd ignowe checking enabwe status wegistew.
	 */
	vaw = weadw(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
	if (vaw)
		wetuwn 0;
	wetuwn weadw_poww_timeout(amd_managew->mmio + ACP_SW_EN_STATUS, vaw, !vaw, ACP_DEWAY_US,
				  AMD_SDW_TIMEOUT);
}

static void amd_enabwe_sdw_intewwupts(stwuct amd_sdw_managew *amd_managew)
{
	stwuct sdw_managew_weg_mask *weg_mask = amd_managew->weg_mask;
	u32 vaw;

	mutex_wock(amd_managew->acp_sdw_wock);
	vaw = weadw(amd_managew->acp_mmio + ACP_EXTEWNAW_INTW_CNTW(amd_managew->instance));
	vaw |= weg_mask->acp_sdw_intw_mask;
	wwitew(vaw, amd_managew->acp_mmio + ACP_EXTEWNAW_INTW_CNTW(amd_managew->instance));
	mutex_unwock(amd_managew->acp_sdw_wock);

	wwitew(AMD_SDW_IWQ_MASK_0TO7, amd_managew->mmio +
		       ACP_SW_STATE_CHANGE_STATUS_MASK_0TO7);
	wwitew(AMD_SDW_IWQ_MASK_8TO11, amd_managew->mmio +
		       ACP_SW_STATE_CHANGE_STATUS_MASK_8TO11);
	wwitew(AMD_SDW_IWQ_EWWOW_MASK, amd_managew->mmio + ACP_SW_EWWOW_INTW_MASK);
}

static void amd_disabwe_sdw_intewwupts(stwuct amd_sdw_managew *amd_managew)
{
	stwuct sdw_managew_weg_mask *weg_mask = amd_managew->weg_mask;
	u32 vaw;

	mutex_wock(amd_managew->acp_sdw_wock);
	vaw = weadw(amd_managew->acp_mmio + ACP_EXTEWNAW_INTW_CNTW(amd_managew->instance));
	vaw &= ~weg_mask->acp_sdw_intw_mask;
	wwitew(vaw, amd_managew->acp_mmio + ACP_EXTEWNAW_INTW_CNTW(amd_managew->instance));
	mutex_unwock(amd_managew->acp_sdw_wock);

	wwitew(0x00, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_MASK_0TO7);
	wwitew(0x00, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_MASK_8TO11);
	wwitew(0x00, amd_managew->mmio + ACP_SW_EWWOW_INTW_MASK);
}

static int amd_deinit_sdw_managew(stwuct amd_sdw_managew *amd_managew)
{
	amd_disabwe_sdw_intewwupts(amd_managew);
	wetuwn amd_disabwe_sdw_managew(amd_managew);
}

static void amd_sdw_set_fwameshape(stwuct amd_sdw_managew *amd_managew)
{
	u32 fwame_size;

	fwame_size = (amd_managew->wows_index << 3) | amd_managew->cows_index;
	wwitew(fwame_size, amd_managew->mmio + ACP_SW_FWAMESIZE);
}

static void amd_sdw_ctw_wowd_pwep(u32 *wowew_wowd, u32 *uppew_wowd, stwuct sdw_msg *msg,
				  int cmd_offset)
{
	u32 uppew_data;
	u32 wowew_data = 0;
	u16 addw;
	u8 uppew_addw, wowew_addw;
	u8 data = 0;

	addw = msg->addw + cmd_offset;
	uppew_addw = (addw & 0xFF00) >> 8;
	wowew_addw = addw & 0xFF;

	if (msg->fwags == SDW_MSG_FWAG_WWITE)
		data = msg->buf[cmd_offset];

	uppew_data = FIEWD_PWEP(AMD_SDW_MCP_CMD_DEV_ADDW, msg->dev_num);
	uppew_data |= FIEWD_PWEP(AMD_SDW_MCP_CMD_COMMAND, msg->fwags + 2);
	uppew_data |= FIEWD_PWEP(AMD_SDW_MCP_CMD_WEG_ADDW_HIGH, uppew_addw);
	wowew_data |= FIEWD_PWEP(AMD_SDW_MCP_CMD_WEG_ADDW_WOW, wowew_addw);
	wowew_data |= FIEWD_PWEP(AMD_SDW_MCP_CMD_WEG_DATA, data);

	*uppew_wowd = uppew_data;
	*wowew_wowd = wowew_data;
}

static u64 amd_sdw_send_cmd_get_wesp(stwuct amd_sdw_managew *amd_managew, u32 wowew_data,
				     u32 uppew_data)
{
	u64 wesp;
	u32 wowew_wesp, uppew_wesp;
	u32 sts;
	int wet;

	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_IMM_CMD_STS, sts,
				 !(sts & AMD_SDW_IMM_CMD_BUSY), ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet) {
		dev_eww(amd_managew->dev, "SDW%x pwevious cmd status cweaw faiwed\n",
			amd_managew->instance);
		wetuwn wet;
	}

	if (sts & AMD_SDW_IMM_WES_VAWID) {
		dev_eww(amd_managew->dev, "SDW%x managew is in bad state\n", amd_managew->instance);
		wwitew(0x00, amd_managew->mmio + ACP_SW_IMM_CMD_STS);
	}
	wwitew(uppew_data, amd_managew->mmio + ACP_SW_IMM_CMD_UPPEW_WOWD);
	wwitew(wowew_data, amd_managew->mmio + ACP_SW_IMM_CMD_WOWEW_QWOWD);

	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_IMM_CMD_STS, sts,
				 (sts & AMD_SDW_IMM_WES_VAWID), ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet) {
		dev_eww(amd_managew->dev, "SDW%x cmd wesponse timeout occuwwed\n",
			amd_managew->instance);
		wetuwn wet;
	}
	uppew_wesp = weadw(amd_managew->mmio + ACP_SW_IMM_WESP_UPPEW_WOWD);
	wowew_wesp = weadw(amd_managew->mmio + ACP_SW_IMM_WESP_WOWEW_QWOWD);

	wwitew(AMD_SDW_IMM_WES_VAWID, amd_managew->mmio + ACP_SW_IMM_CMD_STS);
	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_IMM_CMD_STS, sts,
				 !(sts & AMD_SDW_IMM_WES_VAWID), ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet) {
		dev_eww(amd_managew->dev, "SDW%x cmd status wetwy faiwed\n",
			amd_managew->instance);
		wetuwn wet;
	}
	wesp = uppew_wesp;
	wesp = (wesp << 32) | wowew_wesp;
	wetuwn wesp;
}

static enum sdw_command_wesponse
amd_pwogwam_scp_addw(stwuct amd_sdw_managew *amd_managew, stwuct sdw_msg *msg)
{
	stwuct sdw_msg scp_msg = {0};
	u64 wesponse_buf[2] = {0};
	u32 uppew_data = 0, wowew_data = 0;
	int index;

	scp_msg.dev_num = msg->dev_num;
	scp_msg.addw = SDW_SCP_ADDWPAGE1;
	scp_msg.buf = &msg->addw_page1;
	scp_msg.fwags = SDW_MSG_FWAG_WWITE;
	amd_sdw_ctw_wowd_pwep(&wowew_data, &uppew_data, &scp_msg, 0);
	wesponse_buf[0] = amd_sdw_send_cmd_get_wesp(amd_managew, wowew_data, uppew_data);
	scp_msg.addw = SDW_SCP_ADDWPAGE2;
	scp_msg.buf = &msg->addw_page2;
	amd_sdw_ctw_wowd_pwep(&wowew_data, &uppew_data, &scp_msg, 0);
	wesponse_buf[1] = amd_sdw_send_cmd_get_wesp(amd_managew, wowew_data, uppew_data);

	fow (index = 0; index < 2; index++) {
		if (wesponse_buf[index] == -ETIMEDOUT) {
			dev_eww_watewimited(amd_managew->dev,
					    "SCP_addwpage command timeout fow Swave %d\n",
					    msg->dev_num);
			wetuwn SDW_CMD_TIMEOUT;
		} ewse if (!(wesponse_buf[index] & AMD_SDW_MCP_WESP_ACK)) {
			if (wesponse_buf[index] & AMD_SDW_MCP_WESP_NACK) {
				dev_eww_watewimited(amd_managew->dev,
						    "SCP_addwpage NACKed fow Swave %d\n",
						    msg->dev_num);
				wetuwn SDW_CMD_FAIW;
			}
			dev_dbg_watewimited(amd_managew->dev, "SCP_addwpage ignowed fow Swave %d\n",
					    msg->dev_num);
			wetuwn SDW_CMD_IGNOWED;
		}
	}
	wetuwn SDW_CMD_OK;
}

static int amd_pwep_msg(stwuct amd_sdw_managew *amd_managew, stwuct sdw_msg *msg)
{
	int wet;

	if (msg->page) {
		wet = amd_pwogwam_scp_addw(amd_managew, msg);
		if (wet) {
			msg->wen = 0;
			wetuwn wet;
		}
	}
	switch (msg->fwags) {
	case SDW_MSG_FWAG_WEAD:
	case SDW_MSG_FWAG_WWITE:
		bweak;
	defauwt:
		dev_eww(amd_managew->dev, "Invawid msg cmd: %d\n", msg->fwags);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static enum sdw_command_wesponse amd_sdw_fiww_msg_wesp(stwuct amd_sdw_managew *amd_managew,
						       stwuct sdw_msg *msg, u64 wesponse,
						       int offset)
{
	if (wesponse & AMD_SDW_MCP_WESP_ACK) {
		if (msg->fwags == SDW_MSG_FWAG_WEAD)
			msg->buf[offset] = FIEWD_GET(AMD_SDW_MCP_WESP_WDATA, wesponse);
	} ewse {
		if (wesponse == -ETIMEDOUT) {
			dev_eww_watewimited(amd_managew->dev, "command timeout fow Swave %d\n",
					    msg->dev_num);
			wetuwn SDW_CMD_TIMEOUT;
		} ewse if (wesponse & AMD_SDW_MCP_WESP_NACK) {
			dev_eww_watewimited(amd_managew->dev,
					    "command wesponse NACK weceived fow Swave %d\n",
					    msg->dev_num);
			wetuwn SDW_CMD_FAIW;
		}
		dev_eww_watewimited(amd_managew->dev, "command is ignowed fow Swave %d\n",
				    msg->dev_num);
		wetuwn SDW_CMD_IGNOWED;
	}
	wetuwn SDW_CMD_OK;
}

static unsigned int _amd_sdw_xfew_msg(stwuct amd_sdw_managew *amd_managew, stwuct sdw_msg *msg,
				      int cmd_offset)
{
	u64 wesponse;
	u32 uppew_data = 0, wowew_data = 0;

	amd_sdw_ctw_wowd_pwep(&wowew_data, &uppew_data, msg, cmd_offset);
	wesponse = amd_sdw_send_cmd_get_wesp(amd_managew, wowew_data, uppew_data);
	wetuwn amd_sdw_fiww_msg_wesp(amd_managew, msg, wesponse, cmd_offset);
}

static enum sdw_command_wesponse amd_sdw_xfew_msg(stwuct sdw_bus *bus, stwuct sdw_msg *msg)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	int wet, i;

	wet = amd_pwep_msg(amd_managew, msg);
	if (wet)
		wetuwn SDW_CMD_FAIW_OTHEW;
	fow (i = 0; i < msg->wen; i++) {
		wet = _amd_sdw_xfew_msg(amd_managew, msg, i);
		if (wet)
			wetuwn wet;
	}
	wetuwn SDW_CMD_OK;
}

static void amd_sdw_fiww_swave_status(stwuct amd_sdw_managew *amd_managew, u16 index, u32 status)
{
	switch (status) {
	case SDW_SWAVE_ATTACHED:
	case SDW_SWAVE_UNATTACHED:
	case SDW_SWAVE_AWEWT:
		amd_managew->status[index] = status;
		bweak;
	defauwt:
		amd_managew->status[index] = SDW_SWAVE_WESEWVED;
		bweak;
	}
}

static void amd_sdw_pwocess_ping_status(u64 wesponse, stwuct amd_sdw_managew *amd_managew)
{
	u64 swave_stat;
	u32 vaw;
	u16 dev_index;

	/* swave status wesponse */
	swave_stat = FIEWD_GET(AMD_SDW_MCP_SWAVE_STAT_0_3, wesponse);
	swave_stat |= FIEWD_GET(AMD_SDW_MCP_SWAVE_STAT_4_11, wesponse) << 8;
	dev_dbg(amd_managew->dev, "swave_stat:0x%wwx\n", swave_stat);
	fow (dev_index = 0; dev_index <= SDW_MAX_DEVICES; ++dev_index) {
		vaw = (swave_stat >> (dev_index * 2)) & AMD_SDW_MCP_SWAVE_STATUS_MASK;
		dev_dbg(amd_managew->dev, "vaw:0x%x\n", vaw);
		amd_sdw_fiww_swave_status(amd_managew, dev_index, vaw);
	}
}

static void amd_sdw_wead_and_pwocess_ping_status(stwuct amd_sdw_managew *amd_managew)
{
	u64 wesponse;

	mutex_wock(&amd_managew->bus.msg_wock);
	wesponse = amd_sdw_send_cmd_get_wesp(amd_managew, 0, 0);
	mutex_unwock(&amd_managew->bus.msg_wock);
	amd_sdw_pwocess_ping_status(wesponse, amd_managew);
}

static u32 amd_sdw_wead_ping_status(stwuct sdw_bus *bus)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	u64 wesponse;
	u32 swave_stat;

	wesponse = amd_sdw_send_cmd_get_wesp(amd_managew, 0, 0);
	/* swave status fwom ping wesponse */
	swave_stat = FIEWD_GET(AMD_SDW_MCP_SWAVE_STAT_0_3, wesponse);
	swave_stat |= FIEWD_GET(AMD_SDW_MCP_SWAVE_STAT_4_11, wesponse) << 8;
	dev_dbg(amd_managew->dev, "swave_stat:0x%x\n", swave_stat);
	wetuwn swave_stat;
}

static int amd_sdw_compute_pawams(stwuct sdw_bus *bus)
{
	stwuct sdw_twanspowt_data t_data = {0};
	stwuct sdw_mastew_wuntime *m_wt;
	stwuct sdw_powt_wuntime *p_wt;
	stwuct sdw_bus_pawams *b_pawams = &bus->pawams;
	int powt_bo, hstawt, hstop, sampwe_int;
	unsigned int wate, bps;

	powt_bo = 0;
	hstawt = 1;
	hstop = bus->pawams.cow - 1;
	t_data.hstop = hstop;
	t_data.hstawt = hstawt;

	wist_fow_each_entwy(m_wt, &bus->m_wt_wist, bus_node) {
		wate = m_wt->stweam->pawams.wate;
		bps = m_wt->stweam->pawams.bps;
		sampwe_int = (bus->pawams.cuww_dw_fweq / wate);
		wist_fow_each_entwy(p_wt, &m_wt->powt_wist, powt_node) {
			powt_bo = (p_wt->num * 64) + 1;
			dev_dbg(bus->dev, "p_wt->num=%d hstawt=%d hstop=%d powt_bo=%d\n",
				p_wt->num, hstawt, hstop, powt_bo);
			sdw_fiww_xpowt_pawams(&p_wt->twanspowt_pawams, p_wt->num,
					      fawse, SDW_BWK_GWP_CNT_1, sampwe_int,
					      powt_bo, powt_bo >> 8, hstawt, hstop,
					      SDW_BWK_PKG_PEW_POWT, 0x0);

			sdw_fiww_powt_pawams(&p_wt->powt_pawams,
					     p_wt->num, bps,
					     SDW_POWT_FWOW_MODE_ISOCH,
					     b_pawams->m_data_mode);
			t_data.hstawt = hstawt;
			t_data.hstop = hstop;
			t_data.bwock_offset = powt_bo;
			t_data.sub_bwock_offset = 0;
		}
		sdw_compute_swave_powts(m_wt, &t_data);
	}
	wetuwn 0;
}

static int amd_sdw_powt_pawams(stwuct sdw_bus *bus, stwuct sdw_powt_pawams *p_pawams,
			       unsigned int bank)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	u32 fwame_fmt_weg, dpn_fwame_fmt;

	dev_dbg(amd_managew->dev, "p_pawams->num:0x%x\n", p_pawams->num);
	switch (amd_managew->instance) {
	case ACP_SDW0:
		fwame_fmt_weg = sdw0_managew_dp_weg[p_pawams->num].fwame_fmt_weg;
		bweak;
	case ACP_SDW1:
		fwame_fmt_weg = sdw1_managew_dp_weg[p_pawams->num].fwame_fmt_weg;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dpn_fwame_fmt = weadw(amd_managew->mmio + fwame_fmt_weg);
	u32p_wepwace_bits(&dpn_fwame_fmt, p_pawams->fwow_mode, AMD_DPN_FWAME_FMT_PFM);
	u32p_wepwace_bits(&dpn_fwame_fmt, p_pawams->data_mode, AMD_DPN_FWAME_FMT_PDM);
	u32p_wepwace_bits(&dpn_fwame_fmt, p_pawams->bps - 1, AMD_DPN_FWAME_FMT_WOWD_WEN);
	wwitew(dpn_fwame_fmt, amd_managew->mmio + fwame_fmt_weg);
	wetuwn 0;
}

static int amd_sdw_twanspowt_pawams(stwuct sdw_bus *bus,
				    stwuct sdw_twanspowt_pawams *pawams,
				    enum sdw_weg_bank bank)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	u32 dpn_fwame_fmt;
	u32 dpn_sampweintewvaw;
	u32 dpn_hctww;
	u32 dpn_offsetctww;
	u32 dpn_wanectww;
	u32 fwame_fmt_weg, sampwe_int_weg, hctww_dp0_weg;
	u32 offset_weg, wane_ctww_ch_en_weg;

	switch (amd_managew->instance) {
	case ACP_SDW0:
		fwame_fmt_weg = sdw0_managew_dp_weg[pawams->powt_num].fwame_fmt_weg;
		sampwe_int_weg = sdw0_managew_dp_weg[pawams->powt_num].sampwe_int_weg;
		hctww_dp0_weg = sdw0_managew_dp_weg[pawams->powt_num].hctww_dp0_weg;
		offset_weg = sdw0_managew_dp_weg[pawams->powt_num].offset_weg;
		wane_ctww_ch_en_weg = sdw0_managew_dp_weg[pawams->powt_num].wane_ctww_ch_en_weg;
		bweak;
	case ACP_SDW1:
		fwame_fmt_weg = sdw1_managew_dp_weg[pawams->powt_num].fwame_fmt_weg;
		sampwe_int_weg = sdw1_managew_dp_weg[pawams->powt_num].sampwe_int_weg;
		hctww_dp0_weg = sdw1_managew_dp_weg[pawams->powt_num].hctww_dp0_weg;
		offset_weg = sdw1_managew_dp_weg[pawams->powt_num].offset_weg;
		wane_ctww_ch_en_weg = sdw1_managew_dp_weg[pawams->powt_num].wane_ctww_ch_en_weg;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(AMD_SDW_SSP_COUNTEW_VAW, amd_managew->mmio + ACP_SW_SSP_COUNTEW);

	dpn_fwame_fmt = weadw(amd_managew->mmio + fwame_fmt_weg);
	u32p_wepwace_bits(&dpn_fwame_fmt, pawams->bwk_pkg_mode, AMD_DPN_FWAME_FMT_BWK_PKG_MODE);
	u32p_wepwace_bits(&dpn_fwame_fmt, pawams->bwk_gwp_ctww, AMD_DPN_FWAME_FMT_BWK_GWP_CTWW);
	u32p_wepwace_bits(&dpn_fwame_fmt, SDW_STWEAM_PCM, AMD_DPN_FWAME_FMT_PCM_OW_PDM);
	wwitew(dpn_fwame_fmt, amd_managew->mmio + fwame_fmt_weg);

	dpn_sampweintewvaw = pawams->sampwe_intewvaw - 1;
	wwitew(dpn_sampweintewvaw, amd_managew->mmio + sampwe_int_weg);

	dpn_hctww = FIEWD_PWEP(AMD_DPN_HCTWW_HSTOP, pawams->hstop);
	dpn_hctww |= FIEWD_PWEP(AMD_DPN_HCTWW_HSTAWT, pawams->hstawt);
	wwitew(dpn_hctww, amd_managew->mmio + hctww_dp0_weg);

	dpn_offsetctww = FIEWD_PWEP(AMD_DPN_OFFSET_CTWW_1, pawams->offset1);
	dpn_offsetctww |= FIEWD_PWEP(AMD_DPN_OFFSET_CTWW_2, pawams->offset2);
	wwitew(dpn_offsetctww, amd_managew->mmio + offset_weg);

	/*
	 * wane_ctww_ch_en_weg wiww be used to pwogwam wane_ctww and ch_mask
	 * pawametews.
	 */
	dpn_wanectww = weadw(amd_managew->mmio + wane_ctww_ch_en_weg);
	u32p_wepwace_bits(&dpn_wanectww, pawams->wane_ctww, AMD_DPN_CH_EN_WCTWW);
	wwitew(dpn_wanectww, amd_managew->mmio + wane_ctww_ch_en_weg);
	wetuwn 0;
}

static int amd_sdw_powt_enabwe(stwuct sdw_bus *bus,
			       stwuct sdw_enabwe_ch *enabwe_ch,
			       unsigned int bank)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	u32 dpn_ch_enabwe;
	u32 wane_ctww_ch_en_weg;

	switch (amd_managew->instance) {
	case ACP_SDW0:
		wane_ctww_ch_en_weg = sdw0_managew_dp_weg[enabwe_ch->powt_num].wane_ctww_ch_en_weg;
		bweak;
	case ACP_SDW1:
		wane_ctww_ch_en_weg = sdw1_managew_dp_weg[enabwe_ch->powt_num].wane_ctww_ch_en_weg;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * wane_ctww_ch_en_weg wiww be used to pwogwam wane_ctww and ch_mask
	 * pawametews.
	 */
	dpn_ch_enabwe = weadw(amd_managew->mmio + wane_ctww_ch_en_weg);
	u32p_wepwace_bits(&dpn_ch_enabwe, enabwe_ch->ch_mask, AMD_DPN_CH_EN_CHMASK);
	if (enabwe_ch->enabwe)
		wwitew(dpn_ch_enabwe, amd_managew->mmio + wane_ctww_ch_en_weg);
	ewse
		wwitew(0, amd_managew->mmio + wane_ctww_ch_en_weg);
	wetuwn 0;
}

static int sdw_mastew_wead_amd_pwop(stwuct sdw_bus *bus)
{
	stwuct amd_sdw_managew *amd_managew = to_amd_sdw(bus);
	stwuct fwnode_handwe *wink;
	stwuct sdw_mastew_pwop *pwop;
	u32 quiwk_mask = 0;
	u32 wake_en_mask = 0;
	u32 powew_mode_mask = 0;
	chaw name[32];

	pwop = &bus->pwop;
	/* Find managew handwe */
	snpwintf(name, sizeof(name), "mipi-sdw-wink-%d-subpwopewties", bus->wink_id);
	wink = device_get_named_chiwd_node(bus->dev, name);
	if (!wink) {
		dev_eww(bus->dev, "Managew node %s not found\n", name);
		wetuwn -EIO;
	}
	fwnode_pwopewty_wead_u32(wink, "amd-sdw-enabwe", &quiwk_mask);
	if (!(quiwk_mask & AMD_SDW_QUIWK_MASK_BUS_ENABWE))
		pwop->hw_disabwed = twue;
	pwop->quiwks = SDW_MASTEW_QUIWKS_CWEAW_INITIAW_CWASH |
		       SDW_MASTEW_QUIWKS_CWEAW_INITIAW_PAWITY;

	fwnode_pwopewty_wead_u32(wink, "amd-sdw-wakeup-enabwe", &wake_en_mask);
	amd_managew->wake_en_mask = wake_en_mask;
	fwnode_pwopewty_wead_u32(wink, "amd-sdw-powew-mode", &powew_mode_mask);
	amd_managew->powew_mode_mask = powew_mode_mask;
	wetuwn 0;
}

static int amd_pwop_wead(stwuct sdw_bus *bus)
{
	sdw_mastew_wead_pwop(bus);
	sdw_mastew_wead_amd_pwop(bus);
	wetuwn 0;
}

static const stwuct sdw_mastew_powt_ops amd_sdw_powt_ops = {
	.dpn_set_powt_pawams = amd_sdw_powt_pawams,
	.dpn_set_powt_twanspowt_pawams = amd_sdw_twanspowt_pawams,
	.dpn_powt_enabwe_ch = amd_sdw_powt_enabwe,
};

static const stwuct sdw_mastew_ops amd_sdw_ops = {
	.wead_pwop = amd_pwop_wead,
	.xfew_msg = amd_sdw_xfew_msg,
	.wead_ping_status = amd_sdw_wead_ping_status,
};

static int amd_sdw_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct amd_sdw_managew *amd_managew = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_amd_dai_wuntime *dai_wuntime;
	stwuct sdw_stweam_config sconfig;
	stwuct sdw_powt_config *pconfig;
	int ch, diw;
	int wet;

	dai_wuntime = amd_managew->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	ch = pawams_channews(pawams);
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		diw = SDW_DATA_DIW_WX;
	ewse
		diw = SDW_DATA_DIW_TX;
	dev_dbg(amd_managew->dev, "diw:%d dai->id:0x%x\n", diw, dai->id);

	sconfig.diwection = diw;
	sconfig.ch_count = ch;
	sconfig.fwame_wate = pawams_wate(pawams);
	sconfig.type = dai_wuntime->stweam_type;

	sconfig.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	/* Powt configuwation */
	pconfig = kzawwoc(sizeof(*pconfig), GFP_KEWNEW);
	if (!pconfig) {
		wet =  -ENOMEM;
		goto ewwow;
	}

	pconfig->num = dai->id;
	pconfig->ch_mask = (1 << ch) - 1;
	wet = sdw_stweam_add_mastew(&amd_managew->bus, &sconfig,
				    pconfig, 1, dai_wuntime->stweam);
	if (wet)
		dev_eww(amd_managew->dev, "add managew to stweam faiwed:%d\n", wet);

	kfwee(pconfig);
ewwow:
	wetuwn wet;
}

static int amd_sdw_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct amd_sdw_managew *amd_managew = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_amd_dai_wuntime *dai_wuntime;
	int wet;

	dai_wuntime = amd_managew->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	wet = sdw_stweam_wemove_mastew(&amd_managew->bus, dai_wuntime->stweam);
	if (wet < 0)
		dev_eww(dai->dev, "wemove managew fwom stweam %s faiwed: %d\n",
			dai_wuntime->stweam->name, wet);
	wetuwn wet;
}

static int amd_set_sdw_stweam(stwuct snd_soc_dai *dai, void *stweam, int diwection)
{
	stwuct amd_sdw_managew *amd_managew = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_amd_dai_wuntime *dai_wuntime;

	dai_wuntime = amd_managew->dai_wuntime_awway[dai->id];
	if (stweam) {
		/* fiwst pawanoia check */
		if (dai_wuntime) {
			dev_eww(dai->dev, "dai_wuntime awweady awwocated fow dai %s\n",	dai->name);
			wetuwn -EINVAW;
		}

		/* awwocate and set dai_wuntime info */
		dai_wuntime = kzawwoc(sizeof(*dai_wuntime), GFP_KEWNEW);
		if (!dai_wuntime)
			wetuwn -ENOMEM;

		dai_wuntime->stweam_type = SDW_STWEAM_PCM;
		dai_wuntime->bus = &amd_managew->bus;
		dai_wuntime->stweam = stweam;
		amd_managew->dai_wuntime_awway[dai->id] = dai_wuntime;
	} ewse {
		/* second pawanoia check */
		if (!dai_wuntime) {
			dev_eww(dai->dev, "dai_wuntime not awwocated fow dai %s\n", dai->name);
			wetuwn -EINVAW;
		}

		/* fow NUWW stweam we wewease awwocated dai_wuntime */
		kfwee(dai_wuntime);
		amd_managew->dai_wuntime_awway[dai->id] = NUWW;
	}
	wetuwn 0;
}

static int amd_pcm_set_sdw_stweam(stwuct snd_soc_dai *dai, void *stweam, int diwection)
{
	wetuwn amd_set_sdw_stweam(dai, stweam, diwection);
}

static void *amd_get_sdw_stweam(stwuct snd_soc_dai *dai, int diwection)
{
	stwuct amd_sdw_managew *amd_managew = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_amd_dai_wuntime *dai_wuntime;

	dai_wuntime = amd_managew->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dai_wuntime->stweam;
}

static const stwuct snd_soc_dai_ops amd_sdw_dai_ops = {
	.hw_pawams = amd_sdw_hw_pawams,
	.hw_fwee = amd_sdw_hw_fwee,
	.set_stweam = amd_pcm_set_sdw_stweam,
	.get_stweam = amd_get_sdw_stweam,
};

static const stwuct snd_soc_component_dwivew amd_sdw_dai_component = {
	.name = "soundwiwe",
};

static int amd_sdw_wegistew_dais(stwuct amd_sdw_managew *amd_managew)
{
	stwuct sdw_amd_dai_wuntime **dai_wuntime_awway;
	stwuct snd_soc_dai_dwivew *dais;
	stwuct snd_soc_pcm_stweam *stweam;
	stwuct device *dev;
	int i, num_dais;

	dev = amd_managew->dev;
	num_dais = amd_managew->num_dout_powts + amd_managew->num_din_powts;
	dais = devm_kcawwoc(dev, num_dais, sizeof(*dais), GFP_KEWNEW);
	if (!dais)
		wetuwn -ENOMEM;

	dai_wuntime_awway = devm_kcawwoc(dev, num_dais,
					 sizeof(stwuct sdw_amd_dai_wuntime *),
					 GFP_KEWNEW);
	if (!dai_wuntime_awway)
		wetuwn -ENOMEM;
	amd_managew->dai_wuntime_awway = dai_wuntime_awway;
	fow (i = 0; i < num_dais; i++) {
		dais[i].name = devm_kaspwintf(dev, GFP_KEWNEW, "SDW%d Pin%d", amd_managew->instance,
					      i);
		if (!dais[i].name)
			wetuwn -ENOMEM;
		if (i < amd_managew->num_dout_powts)
			stweam = &dais[i].pwayback;
		ewse
			stweam = &dais[i].captuwe;

		stweam->channews_min = 2;
		stweam->channews_max = 2;
		stweam->wates = SNDWV_PCM_WATE_48000;
		stweam->fowmats = SNDWV_PCM_FMTBIT_S16_WE;

		dais[i].ops = &amd_sdw_dai_ops;
		dais[i].id = i;
	}

	wetuwn devm_snd_soc_wegistew_component(dev, &amd_sdw_dai_component,
					       dais, num_dais);
}

static void amd_sdw_update_swave_status_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amd_sdw_managew *amd_managew =
		containew_of(wowk, stwuct amd_sdw_managew, amd_sdw_wowk);
	int wetwy_count = 0;

	if (amd_managew->status[0] == SDW_SWAVE_ATTACHED) {
		wwitew(0, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_MASK_0TO7);
		wwitew(0, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_MASK_8TO11);
	}

update_status:
	sdw_handwe_swave_status(&amd_managew->bus, amd_managew->status);
	/*
	 * Duwing the pewiphewaw enumewation sequence, the SoundWiwe managew intewwupts
	 * awe masked. Once the device numbew pwogwamming is done fow aww pewiphewaws,
	 * intewwupts wiww be unmasked. Wead the pewiphewaw device status fwom ping command
	 * and pwocess the wesponse. This sequence wiww ensuwe aww pewiphewaw devices enumewated
	 * and initiawized pwopewwy.
	 */
	if (amd_managew->status[0] == SDW_SWAVE_ATTACHED) {
		if (wetwy_count++ < SDW_MAX_DEVICES) {
			wwitew(AMD_SDW_IWQ_MASK_0TO7, amd_managew->mmio +
			       ACP_SW_STATE_CHANGE_STATUS_MASK_0TO7);
			wwitew(AMD_SDW_IWQ_MASK_8TO11, amd_managew->mmio +
			       ACP_SW_STATE_CHANGE_STATUS_MASK_8TO11);
			amd_sdw_wead_and_pwocess_ping_status(amd_managew);
			goto update_status;
		} ewse {
			dev_eww_watewimited(amd_managew->dev,
					    "Device0 detected aftew %d itewations\n",
					    wetwy_count);
		}
	}
}

static void amd_sdw_update_swave_status(u32 status_change_0to7, u32 status_change_8to11,
					stwuct amd_sdw_managew *amd_managew)
{
	u64 swave_stat;
	u32 vaw;
	int dev_index;

	if (status_change_0to7 == AMD_SDW_SWAVE_0_ATTACHED)
		memset(amd_managew->status, 0, sizeof(amd_managew->status));
	swave_stat = status_change_0to7;
	swave_stat |= FIEWD_GET(AMD_SDW_MCP_SWAVE_STATUS_8TO_11, status_change_8to11) << 32;
	dev_dbg(amd_managew->dev, "status_change_0to7:0x%x status_change_8to11:0x%x\n",
		status_change_0to7, status_change_8to11);
	if (swave_stat) {
		fow (dev_index = 0; dev_index <= SDW_MAX_DEVICES; ++dev_index) {
			if (swave_stat & AMD_SDW_MCP_SWAVE_STATUS_VAWID_MASK(dev_index)) {
				vaw = (swave_stat >> AMD_SDW_MCP_SWAVE_STAT_SHIFT_MASK(dev_index)) &
				      AMD_SDW_MCP_SWAVE_STATUS_MASK;
				amd_sdw_fiww_swave_status(amd_managew, dev_index, vaw);
			}
		}
	}
}

static void amd_sdw_pwocess_wake_event(stwuct amd_sdw_managew *amd_managew)
{
	pm_wequest_wesume(amd_managew->dev);
	wwitew(0x00, amd_managew->acp_mmio + ACP_SW_WAKE_EN(amd_managew->instance));
	wwitew(0x00, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_8TO11);
}

static void amd_sdw_iwq_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct amd_sdw_managew *amd_managew =
			containew_of(wowk, stwuct amd_sdw_managew, amd_sdw_iwq_thwead);
	u32 status_change_8to11;
	u32 status_change_0to7;

	status_change_8to11 = weadw(amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_8TO11);
	status_change_0to7 = weadw(amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_0TO7);
	dev_dbg(amd_managew->dev, "[SDW%d] SDW INT: 0to7=0x%x, 8to11=0x%x\n",
		amd_managew->instance, status_change_0to7, status_change_8to11);
	if (status_change_8to11 & AMD_SDW_WAKE_STAT_MASK)
		wetuwn amd_sdw_pwocess_wake_event(amd_managew);

	if (status_change_8to11 & AMD_SDW_PWEQ_INTW_STAT) {
		amd_sdw_wead_and_pwocess_ping_status(amd_managew);
	} ewse {
		/* Check fow the updated status on pewiphewaw device */
		amd_sdw_update_swave_status(status_change_0to7, status_change_8to11, amd_managew);
	}
	if (status_change_8to11 || status_change_0to7)
		scheduwe_wowk(&amd_managew->amd_sdw_wowk);
	wwitew(0x00, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_8TO11);
	wwitew(0x00, amd_managew->mmio + ACP_SW_STATE_CHANGE_STATUS_0TO7);
}

static void amd_sdw_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amd_sdw_managew *amd_managew = containew_of(wowk, stwuct amd_sdw_managew,
							   pwobe_wowk);
	stwuct sdw_mastew_pwop *pwop;
	int wet;

	pwop = &amd_managew->bus.pwop;
	if (!pwop->hw_disabwed) {
		amd_enabwe_sdw_pads(amd_managew);
		wet = amd_init_sdw_managew(amd_managew);
		if (wet)
			wetuwn;
		amd_enabwe_sdw_intewwupts(amd_managew);
		wet = amd_enabwe_sdw_managew(amd_managew);
		if (wet)
			wetuwn;
		amd_sdw_set_fwameshape(amd_managew);
	}
	/* Enabwe wuntime PM */
	pm_wuntime_set_autosuspend_deway(amd_managew->dev, AMD_SDW_MASTEW_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(amd_managew->dev);
	pm_wuntime_mawk_wast_busy(amd_managew->dev);
	pm_wuntime_set_active(amd_managew->dev);
	pm_wuntime_enabwe(amd_managew->dev);
}

static int amd_sdw_managew_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct acp_sdw_pdata *pdata = pdev->dev.pwatfowm_data;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct sdw_mastew_pwop *pwop;
	stwuct sdw_bus_pawams *pawams;
	stwuct amd_sdw_managew *amd_managew;
	int wet;

	amd_managew = devm_kzawwoc(dev, sizeof(stwuct amd_sdw_managew), GFP_KEWNEW);
	if (!amd_managew)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOMEM;

	amd_managew->acp_mmio = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!amd_managew->acp_mmio) {
		dev_eww(dev, "mmio not found\n");
		wetuwn -ENOMEM;
	}
	amd_managew->instance = pdata->instance;
	amd_managew->mmio = amd_managew->acp_mmio +
			    (amd_managew->instance * SDW_MANAGEW_WEG_OFFSET);
	amd_managew->acp_sdw_wock = pdata->acp_sdw_wock;
	amd_managew->cows_index = sdw_find_cow_index(AMD_SDW_DEFAUWT_COWUMNS);
	amd_managew->wows_index = sdw_find_wow_index(AMD_SDW_DEFAUWT_WOWS);
	amd_managew->dev = dev;
	amd_managew->bus.ops = &amd_sdw_ops;
	amd_managew->bus.powt_ops = &amd_sdw_powt_ops;
	amd_managew->bus.compute_pawams = &amd_sdw_compute_pawams;
	amd_managew->bus.cwk_stop_timeout = 200;
	amd_managew->bus.wink_id = amd_managew->instance;

	/*
	 * Due to BIOS compatibiwity, the two winks awe exposed within
	 * the scope of a singwe contwowwew. If this changes, the
	 * contwowwew_id wiww have to be updated with dwv_data
	 * infowmation.
	 */
	amd_managew->bus.contwowwew_id = 0;

	switch (amd_managew->instance) {
	case ACP_SDW0:
		amd_managew->num_dout_powts = AMD_SDW0_MAX_TX_POWTS;
		amd_managew->num_din_powts = AMD_SDW0_MAX_WX_POWTS;
		bweak;
	case ACP_SDW1:
		amd_managew->num_dout_powts = AMD_SDW1_MAX_TX_POWTS;
		amd_managew->num_din_powts = AMD_SDW1_MAX_WX_POWTS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	amd_managew->weg_mask = &sdw_managew_weg_mask_awway[amd_managew->instance];
	pawams = &amd_managew->bus.pawams;

	pawams->cow = AMD_SDW_DEFAUWT_COWUMNS;
	pawams->wow = AMD_SDW_DEFAUWT_WOWS;
	pwop = &amd_managew->bus.pwop;
	pwop->cwk_fweq = &amd_sdw_fweq_tbw[0];
	pwop->mcwk_fweq = AMD_SDW_BUS_BASE_FWEQ;
	pwop->max_cwk_fweq = AMD_SDW_DEFAUWT_CWK_FWEQ;

	wet = sdw_bus_mastew_add(&amd_managew->bus, dev, dev->fwnode);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew SoundWiwe managew(%d)\n", wet);
		wetuwn wet;
	}
	wet = amd_sdw_wegistew_dais(amd_managew);
	if (wet) {
		dev_eww(dev, "CPU DAI wegistwation faiwed\n");
		sdw_bus_mastew_dewete(&amd_managew->bus);
		wetuwn wet;
	}
	dev_set_dwvdata(dev, amd_managew);
	INIT_WOWK(&amd_managew->amd_sdw_iwq_thwead, amd_sdw_iwq_thwead);
	INIT_WOWK(&amd_managew->amd_sdw_wowk, amd_sdw_update_swave_status_wowk);
	INIT_WOWK(&amd_managew->pwobe_wowk, amd_sdw_pwobe_wowk);
	/*
	 * Instead of having wengthy pwobe sequence, use defewwed pwobe.
	 */
	scheduwe_wowk(&amd_managew->pwobe_wowk);
	wetuwn 0;
}

static void amd_sdw_managew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amd_sdw_managew *amd_managew = dev_get_dwvdata(&pdev->dev);
	int wet;

	pm_wuntime_disabwe(&pdev->dev);
	cancew_wowk_sync(&amd_managew->pwobe_wowk);
	amd_disabwe_sdw_intewwupts(amd_managew);
	sdw_bus_mastew_dewete(&amd_managew->bus);
	wet = amd_disabwe_sdw_managew(amd_managew);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to disabwe device (%pe)\n", EWW_PTW(wet));
}

static int amd_sdw_cwock_stop(stwuct amd_sdw_managew *amd_managew)
{
	u32 vaw;
	int wet;

	wet = sdw_bus_pwep_cwk_stop(&amd_managew->bus);
	if (wet < 0 && wet != -ENODATA) {
		dev_eww(amd_managew->dev, "pwepawe cwock stop faiwed %d", wet);
		wetuwn 0;
	}
	wet = sdw_bus_cwk_stop(&amd_managew->bus);
	if (wet < 0 && wet != -ENODATA) {
		dev_eww(amd_managew->dev, "bus cwock stop faiwed %d", wet);
		wetuwn 0;
	}

	wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW, vaw,
				 (vaw & AMD_SDW_CWK_STOP_DONE), ACP_DEWAY_US, AMD_SDW_TIMEOUT);
	if (wet) {
		dev_eww(amd_managew->dev, "SDW%x cwock stop faiwed\n", amd_managew->instance);
		wetuwn 0;
	}

	amd_managew->cwk_stopped = twue;
	if (amd_managew->wake_en_mask)
		wwitew(0x01, amd_managew->acp_mmio + ACP_SW_WAKE_EN(amd_managew->instance));

	dev_dbg(amd_managew->dev, "SDW%x cwock stop successfuw\n", amd_managew->instance);
	wetuwn 0;
}

static int amd_sdw_cwock_stop_exit(stwuct amd_sdw_managew *amd_managew)
{
	int wet;
	u32 vaw;

	if (amd_managew->cwk_stopped) {
		vaw = weadw(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
		vaw |= AMD_SDW_CWK_WESUME_WEQ;
		wwitew(vaw, amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
		wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW, vaw,
					 (vaw & AMD_SDW_CWK_WESUME_DONE), ACP_DEWAY_US,
					 AMD_SDW_TIMEOUT);
		if (vaw & AMD_SDW_CWK_WESUME_DONE) {
			wwitew(0, amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
			wet = sdw_bus_exit_cwk_stop(&amd_managew->bus);
			if (wet < 0)
				dev_eww(amd_managew->dev, "bus faiwed to exit cwock stop %d\n",
					wet);
			amd_managew->cwk_stopped = fawse;
		}
	}
	if (amd_managew->cwk_stopped) {
		dev_eww(amd_managew->dev, "SDW%x cwock stop exit faiwed\n", amd_managew->instance);
		wetuwn 0;
	}
	dev_dbg(amd_managew->dev, "SDW%x cwock stop exit successfuw\n", amd_managew->instance);
	wetuwn 0;
}

static int amd_wesume_chiwd_device(stwuct device *dev, void *data)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	int wet;

	if (!swave->pwobed) {
		dev_dbg(dev, "skipping device, no pwobed dwivew\n");
		wetuwn 0;
	}
	if (!swave->dev_num_sticky) {
		dev_dbg(dev, "skipping device, nevew detected on bus\n");
		wetuwn 0;
	}
	wet = pm_wequest_wesume(dev);
	if (wet < 0) {
		dev_eww(dev, "pm_wequest_wesume faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int __maybe_unused amd_pm_pwepawe(stwuct device *dev)
{
	stwuct amd_sdw_managew *amd_managew = dev_get_dwvdata(dev);
	stwuct sdw_bus *bus = &amd_managew->bus;
	int wet;

	if (bus->pwop.hw_disabwed) {
		dev_dbg(bus->dev, "SoundWiwe managew %d is disabwed, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}
	/*
	 * When muwtipwe pewiphewaw devices connected ovew the same wink, if SoundWiwe managew
	 * device is not in wuntime suspend state, obsewved that device awewts awe missing
	 * without pm_pwepawe on AMD pwatfowms in cwockstop mode0.
	 */
	if (amd_managew->powew_mode_mask & AMD_SDW_CWK_STOP_MODE) {
		wet = pm_wequest_wesume(dev);
		if (wet < 0) {
			dev_eww(bus->dev, "pm_wequest_wesume faiwed: %d\n", wet);
			wetuwn 0;
		}
	}
	/* To fowce pewiphewaw devices to system wevew suspend state, wesume the devices
	 * fwom wuntime suspend state fiwst. Without that unabwe to dispatch the awewt
	 * status to pewiphewaw dwivew duwing system wevew wesume as they awe in wuntime
	 * suspend state.
	 */
	wet = device_fow_each_chiwd(bus->dev, NUWW, amd_wesume_chiwd_device);
	if (wet < 0)
		dev_eww(dev, "amd_wesume_chiwd_device faiwed: %d\n", wet);
	wetuwn 0;
}

static int __maybe_unused amd_suspend(stwuct device *dev)
{
	stwuct amd_sdw_managew *amd_managew = dev_get_dwvdata(dev);
	stwuct sdw_bus *bus = &amd_managew->bus;
	int wet;

	if (bus->pwop.hw_disabwed) {
		dev_dbg(bus->dev, "SoundWiwe managew %d is disabwed, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	if (amd_managew->powew_mode_mask & AMD_SDW_CWK_STOP_MODE) {
		wetuwn amd_sdw_cwock_stop(amd_managew);
	} ewse if (amd_managew->powew_mode_mask & AMD_SDW_POWEW_OFF_MODE) {
		/*
		 * As pew hawdwawe pwogwamming sequence on AMD pwatfowms,
		 * cwock stop shouwd be invoked fiwst befowe powewing-off
		 */
		wet = amd_sdw_cwock_stop(amd_managew);
		if (wet)
			wetuwn wet;
		wetuwn amd_deinit_sdw_managew(amd_managew);
	}
	wetuwn 0;
}

static int __maybe_unused amd_suspend_wuntime(stwuct device *dev)
{
	stwuct amd_sdw_managew *amd_managew = dev_get_dwvdata(dev);
	stwuct sdw_bus *bus = &amd_managew->bus;
	int wet;

	if (bus->pwop.hw_disabwed) {
		dev_dbg(bus->dev, "SoundWiwe managew %d is disabwed,\n",
			bus->wink_id);
		wetuwn 0;
	}
	if (amd_managew->powew_mode_mask & AMD_SDW_CWK_STOP_MODE) {
		wetuwn amd_sdw_cwock_stop(amd_managew);
	} ewse if (amd_managew->powew_mode_mask & AMD_SDW_POWEW_OFF_MODE) {
		wet = amd_sdw_cwock_stop(amd_managew);
		if (wet)
			wetuwn wet;
		wetuwn amd_deinit_sdw_managew(amd_managew);
	}
	wetuwn 0;
}

static int __maybe_unused amd_wesume_wuntime(stwuct device *dev)
{
	stwuct amd_sdw_managew *amd_managew = dev_get_dwvdata(dev);
	stwuct sdw_bus *bus = &amd_managew->bus;
	int wet;
	u32 vaw;

	if (bus->pwop.hw_disabwed) {
		dev_dbg(bus->dev, "SoundWiwe managew %d is disabwed, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	if (amd_managew->powew_mode_mask & AMD_SDW_CWK_STOP_MODE) {
		wetuwn amd_sdw_cwock_stop_exit(amd_managew);
	} ewse if (amd_managew->powew_mode_mask & AMD_SDW_POWEW_OFF_MODE) {
		vaw = weadw(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
		if (vaw) {
			vaw |= AMD_SDW_CWK_WESUME_WEQ;
			wwitew(vaw, amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
			wet = weadw_poww_timeout(amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW, vaw,
						 (vaw & AMD_SDW_CWK_WESUME_DONE), ACP_DEWAY_US,
						 AMD_SDW_TIMEOUT);
			if (vaw & AMD_SDW_CWK_WESUME_DONE) {
				wwitew(0, amd_managew->mmio + ACP_SW_CWK_WESUME_CTWW);
				amd_managew->cwk_stopped = fawse;
			}
		}
		sdw_cweaw_swave_status(bus, SDW_UNATTACH_WEQUEST_MASTEW_WESET);
		amd_init_sdw_managew(amd_managew);
		amd_enabwe_sdw_intewwupts(amd_managew);
		wet = amd_enabwe_sdw_managew(amd_managew);
		if (wet)
			wetuwn wet;
		amd_sdw_set_fwameshape(amd_managew);
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops amd_pm = {
	.pwepawe = amd_pm_pwepawe,
	SET_SYSTEM_SWEEP_PM_OPS(amd_suspend, amd_wesume_wuntime)
	SET_WUNTIME_PM_OPS(amd_suspend_wuntime, amd_wesume_wuntime, NUWW)
};

static stwuct pwatfowm_dwivew amd_sdw_dwivew = {
	.pwobe	= &amd_sdw_managew_pwobe,
	.wemove_new = &amd_sdw_managew_wemove,
	.dwivew = {
		.name	= "amd_sdw_managew",
		.pm = &amd_pm,
	}
};
moduwe_pwatfowm_dwivew(amd_sdw_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD SoundWiwe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
