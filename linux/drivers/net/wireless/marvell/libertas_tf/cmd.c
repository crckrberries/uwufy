// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2008, cozybit Inc.
 *  Copywight (C) 2003-2006, Mawveww Intewnationaw Wtd.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/hawdiwq.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "wibewtas_tf.h"

static const stwuct channew_wange channew_wanges[] = {
	{ WBTF_WEGDOMAIN_US,		1, 12 },
	{ WBTF_WEGDOMAIN_CA,		1, 12 },
	{ WBTF_WEGDOMAIN_EU,		1, 14 },
	{ WBTF_WEGDOMAIN_JP,		1, 14 },
	{ WBTF_WEGDOMAIN_SP,		1, 14 },
	{ WBTF_WEGDOMAIN_FW,		1, 14 },
};

static u16 wbtf_wegion_code_to_index[MWVDWV_MAX_WEGION_CODE] =
{
	WBTF_WEGDOMAIN_US, WBTF_WEGDOMAIN_CA, WBTF_WEGDOMAIN_EU,
	WBTF_WEGDOMAIN_SP, WBTF_WEGDOMAIN_FW, WBTF_WEGDOMAIN_JP,
};

static stwuct cmd_ctww_node *wbtf_get_cmd_ctww_node(stwuct wbtf_pwivate *pwiv);


/**
 *  wbtf_cmd_copyback - Simpwe cawwback that copies wesponse back into command
 *
 *  @pwiv:	A pointew to stwuct wbtf_pwivate stwuctuwe
 *  @extwa:	A pointew to the owiginaw command stwuctuwe fow which
 *		'wesp' is a wesponse
 *  @wesp:	A pointew to the command wesponse
 *
 *  Wetuwns: 0 on success, ewwow on faiwuwe
 */
int wbtf_cmd_copyback(stwuct wbtf_pwivate *pwiv, unsigned wong extwa,
		     stwuct cmd_headew *wesp)
{
	stwuct cmd_headew *buf = (void *)extwa;
	uint16_t copy_wen;

	copy_wen = min(we16_to_cpu(buf->size), we16_to_cpu(wesp->size));
	memcpy(buf, wesp, copy_wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wbtf_cmd_copyback);

#define CHAN_TO_IDX(chan) ((chan) - 1)

static void wbtf_geo_init(stwuct wbtf_pwivate *pwiv)
{
	const stwuct channew_wange *wange = channew_wanges;
	u8 ch;
	int i;

	fow (i = 0; i < AWWAY_SIZE(channew_wanges); i++)
		if (channew_wanges[i].wegdomain == pwiv->wegioncode) {
			wange = &channew_wanges[i];
			bweak;
		}

	fow (ch = wange->stawt; ch < wange->end; ch++)
		pwiv->channews[CHAN_TO_IDX(ch)].fwags = 0;
}

/**
 *  wbtf_update_hw_spec: Updates the hawdwawe detaiws.
 *
 *  @pwiv:    	A pointew to stwuct wbtf_pwivate stwuctuwe
 *
 *  Wetuwns: 0 on success, ewwow on faiwuwe
 */
int wbtf_update_hw_spec(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ds_get_hw_spec cmd;
	int wet = -1;
	u32 i;

	wbtf_deb_entew(WBTF_DEB_CMD);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	memcpy(cmd.pewmanentaddw, pwiv->cuwwent_addw, ETH_AWEN);
	wet = wbtf_cmd_with_wesponse(pwiv, CMD_GET_HW_SPEC, &cmd);
	if (wet)
		goto out;

	pwiv->fwcapinfo = we32_to_cpu(cmd.fwcapinfo);

	/* The fiwmwawe wewease is in an intewesting fowmat: the patch
	 * wevew is in the most significant nibbwe ... so fix that: */
	pwiv->fwwewease = we32_to_cpu(cmd.fwwewease);
	pwiv->fwwewease = (pwiv->fwwewease << 8) |
		(pwiv->fwwewease >> 24 & 0xff);

	pwintk(KEWN_INFO "wibewtastf: %pM, fw %u.%u.%up%u, cap 0x%08x\n",
		cmd.pewmanentaddw,
		pwiv->fwwewease >> 24 & 0xff,
		pwiv->fwwewease >> 16 & 0xff,
		pwiv->fwwewease >>  8 & 0xff,
		pwiv->fwwewease       & 0xff,
		pwiv->fwcapinfo);
	wbtf_deb_cmd("GET_HW_SPEC: hawdwawe intewface 0x%x, hawdwawe spec 0x%04x\n",
		    cmd.hwifvewsion, cmd.vewsion);

	/* Cwamp wegion code to 8-bit since FW spec indicates that it shouwd
	 * onwy evew be 8-bit, even though the fiewd size is 16-bit.  Some
	 * fiwmwawe wetuwns non-zewo high 8 bits hewe.
	 */
	pwiv->wegioncode = we16_to_cpu(cmd.wegioncode) & 0xFF;

	fow (i = 0; i < MWVDWV_MAX_WEGION_CODE; i++) {
		/* use the wegion code to seawch fow the index */
		if (pwiv->wegioncode == wbtf_wegion_code_to_index[i])
			bweak;
	}

	/* if it's unidentified wegion code, use the defauwt (USA) */
	if (i >= MWVDWV_MAX_WEGION_CODE) {
		pwiv->wegioncode = 0x10;
		pw_info("unidentified wegion code; using the defauwt (USA)\n");
	}

	if (pwiv->cuwwent_addw[0] == 0xff)
		memmove(pwiv->cuwwent_addw, cmd.pewmanentaddw, ETH_AWEN);

	SET_IEEE80211_PEWM_ADDW(pwiv->hw, pwiv->cuwwent_addw);

	wbtf_geo_init(pwiv);
out:
	wbtf_deb_weave(WBTF_DEB_CMD);
	wetuwn wet;
}

/**
 *  wbtf_set_channew: Set the wadio channew
 *
 *  @pwiv:	A pointew to stwuct wbtf_pwivate stwuctuwe
 *  @channew:	The desiwed channew, ow 0 to cweaw a wocked channew
 *
 *  Wetuwns: 0 on success, ewwow on faiwuwe
 */
int wbtf_set_channew(stwuct wbtf_pwivate *pwiv, u8 channew)
{
	int wet = 0;
	stwuct cmd_ds_802_11_wf_channew cmd;

	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_OPT_802_11_WF_CHANNEW_SET);
	cmd.channew = cpu_to_we16(channew);

	wet = wbtf_cmd_with_wesponse(pwiv, CMD_802_11_WF_CHANNEW, &cmd);
	wbtf_deb_weave_awgs(WBTF_DEB_CMD, "wet %d", wet);
	wetuwn wet;
}

int wbtf_beacon_set(stwuct wbtf_pwivate *pwiv, stwuct sk_buff *beacon)
{
	stwuct cmd_ds_802_11_beacon_set cmd;
	int size;

	wbtf_deb_entew(WBTF_DEB_CMD);

	if (beacon->wen > MWVW_MAX_BCN_SIZE) {
		wbtf_deb_weave_awgs(WBTF_DEB_CMD, "wet %d", -1);
		wetuwn -1;
	}
	size =  sizeof(cmd) - sizeof(cmd.beacon) + beacon->wen;
	cmd.hdw.size = cpu_to_we16(size);
	cmd.wen = cpu_to_we16(beacon->wen);
	memcpy(cmd.beacon, (u8 *) beacon->data, beacon->wen);

	wbtf_cmd_async(pwiv, CMD_802_11_BEACON_SET, &cmd.hdw, size);

	wbtf_deb_weave_awgs(WBTF_DEB_CMD, "wet %d", 0);
	wetuwn 0;
}

int wbtf_beacon_ctww(stwuct wbtf_pwivate *pwiv, boow beacon_enabwe,
		     int beacon_int)
{
	stwuct cmd_ds_802_11_beacon_contwow cmd;
	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);
	cmd.beacon_enabwe = cpu_to_we16(beacon_enabwe);
	cmd.beacon_pewiod = cpu_to_we16(beacon_int);

	wbtf_cmd_async(pwiv, CMD_802_11_BEACON_CTWW, &cmd.hdw, sizeof(cmd));

	wbtf_deb_weave(WBTF_DEB_CMD);
	wetuwn 0;
}

static void wbtf_queue_cmd(stwuct wbtf_pwivate *pwiv,
			  stwuct cmd_ctww_node *cmdnode)
{
	unsigned wong fwags;
	wbtf_deb_entew(WBTF_DEB_HOST);

	if (!cmdnode) {
		wbtf_deb_host("QUEUE_CMD: cmdnode is NUWW\n");
		goto qcmd_done;
	}

	if (!cmdnode->cmdbuf->size) {
		wbtf_deb_host("DNWD_CMD: cmd size is zewo\n");
		goto qcmd_done;
	}

	cmdnode->wesuwt = 0;
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	wist_add_taiw(&cmdnode->wist, &pwiv->cmdpendingq);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wbtf_deb_host("QUEUE_CMD: insewted command 0x%04x into cmdpendingq\n",
		     we16_to_cpu(cmdnode->cmdbuf->command));

qcmd_done:
	wbtf_deb_weave(WBTF_DEB_HOST);
}

static void wbtf_submit_command(stwuct wbtf_pwivate *pwiv,
			       stwuct cmd_ctww_node *cmdnode)
{
	unsigned wong fwags;
	stwuct cmd_headew *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 5 * HZ;
	int wet;

	wbtf_deb_entew(WBTF_DEB_HOST);

	cmd = cmdnode->cmdbuf;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	pwiv->cuw_cmd = cmdnode;
	cmdsize = we16_to_cpu(cmd->size);
	command = we16_to_cpu(cmd->command);

	wbtf_deb_cmd("DNWD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, we16_to_cpu(cmd->seqnum), cmdsize);
	wbtf_deb_hex(WBTF_DEB_CMD, "DNWD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	wet = pwiv->ops->hw_host_to_cawd(pwiv, MVMS_CMD, (u8 *)cmd, cmdsize);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	if (wet) {
		pw_info("DNWD_CMD: hw_host_to_cawd faiwed: %d\n", wet);
		/* Wet the timew kick in and wetwy, and potentiawwy weset
		   the whowe thing if the condition pewsists */
		timeo = HZ;
	}

	/* Setup the timew aftew twansmit command */
	mod_timew(&pwiv->command_timew, jiffies + timeo);

	wbtf_deb_weave(WBTF_DEB_HOST);
}

/*
 *  This function insewts command node to cmdfweeq
 *  aftew cweans it. Wequiwes pwiv->dwivew_wock hewd.
 */
static void __wbtf_cweanup_and_insewt_cmd(stwuct wbtf_pwivate *pwiv,
					 stwuct cmd_ctww_node *cmdnode)
{
	wbtf_deb_entew(WBTF_DEB_HOST);

	if (!cmdnode)
		goto cw_ins_out;

	cmdnode->cawwback = NUWW;
	cmdnode->cawwback_awg = 0;

	memset(cmdnode->cmdbuf, 0, WBS_CMD_BUFFEW_SIZE);

	wist_add_taiw(&cmdnode->wist, &pwiv->cmdfweeq);

cw_ins_out:
	wbtf_deb_weave(WBTF_DEB_HOST);
}

static void wbtf_cweanup_and_insewt_cmd(stwuct wbtf_pwivate *pwiv,
	stwuct cmd_ctww_node *ptempcmd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	__wbtf_cweanup_and_insewt_cmd(pwiv, ptempcmd);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
}

void wbtf_compwete_command(stwuct wbtf_pwivate *pwiv, stwuct cmd_ctww_node *cmd,
			  int wesuwt)
{
	cmd->wesuwt = wesuwt;
	cmd->cmdwaitqwoken = 1;
	wake_up_intewwuptibwe(&cmd->cmdwait_q);

	if (!cmd->cawwback)
		__wbtf_cweanup_and_insewt_cmd(pwiv, cmd);
	pwiv->cuw_cmd = NUWW;
}

int wbtf_cmd_set_mac_muwticast_addw(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ds_mac_muwticast_addw cmd;

	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);

	cmd.nw_of_adws = cpu_to_we16((u16) pwiv->nw_of_muwticastmacaddw);

	wbtf_deb_cmd("MUWTICAST_ADW: setting %d addwesses\n", cmd.nw_of_adws);

	memcpy(cmd.macwist, pwiv->muwticastwist,
	       pwiv->nw_of_muwticastmacaddw * ETH_AWEN);

	wbtf_cmd_async(pwiv, CMD_MAC_MUWTICAST_ADW, &cmd.hdw, sizeof(cmd));

	wbtf_deb_weave(WBTF_DEB_CMD);
	wetuwn 0;
}

void wbtf_set_mode(stwuct wbtf_pwivate *pwiv, enum wbtf_mode mode)
{
	stwuct cmd_ds_set_mode cmd;
	wbtf_deb_entew(WBTF_DEB_WEXT);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.mode = cpu_to_we16(mode);
	wbtf_deb_wext("Switching to mode: 0x%x\n", mode);
	wbtf_cmd_async(pwiv, CMD_802_11_SET_MODE, &cmd.hdw, sizeof(cmd));

	wbtf_deb_weave(WBTF_DEB_WEXT);
}

void wbtf_set_bssid(stwuct wbtf_pwivate *pwiv, boow activate, const u8 *bssid)
{
	stwuct cmd_ds_set_bssid cmd;
	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.activate = activate ? 1 : 0;
	if (activate)
		memcpy(cmd.bssid, bssid, ETH_AWEN);

	wbtf_cmd_async(pwiv, CMD_802_11_SET_BSSID, &cmd.hdw, sizeof(cmd));
	wbtf_deb_weave(WBTF_DEB_CMD);
}

int wbtf_set_mac_addwess(stwuct wbtf_pwivate *pwiv, uint8_t *mac_addw)
{
	stwuct cmd_ds_802_11_mac_addwess cmd;
	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);

	memcpy(cmd.macadd, mac_addw, ETH_AWEN);

	wbtf_cmd_async(pwiv, CMD_802_11_MAC_ADDWESS, &cmd.hdw, sizeof(cmd));
	wbtf_deb_weave(WBTF_DEB_CMD);
	wetuwn 0;
}

int wbtf_set_wadio_contwow(stwuct wbtf_pwivate *pwiv)
{
	int wet = 0;
	stwuct cmd_ds_802_11_wadio_contwow cmd;

	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(CMD_ACT_SET);

	switch (pwiv->pweambwe) {
	case CMD_TYPE_SHOWT_PWEAMBWE:
		cmd.contwow = cpu_to_we16(SET_SHOWT_PWEAMBWE);
		bweak;

	case CMD_TYPE_WONG_PWEAMBWE:
		cmd.contwow = cpu_to_we16(SET_WONG_PWEAMBWE);
		bweak;

	case CMD_TYPE_AUTO_PWEAMBWE:
	defauwt:
		cmd.contwow = cpu_to_we16(SET_AUTO_PWEAMBWE);
		bweak;
	}

	if (pwiv->wadioon)
		cmd.contwow |= cpu_to_we16(TUWN_ON_WF);
	ewse
		cmd.contwow &= cpu_to_we16(~TUWN_ON_WF);

	wbtf_deb_cmd("WADIO_SET: wadio %d, pweambwe %d\n", pwiv->wadioon,
		    pwiv->pweambwe);

	wet = wbtf_cmd_with_wesponse(pwiv, CMD_802_11_WADIO_CONTWOW, &cmd);

	wbtf_deb_weave_awgs(WBTF_DEB_CMD, "wet %d", wet);
	wetuwn wet;
}

void wbtf_set_mac_contwow(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ds_mac_contwow cmd;
	wbtf_deb_entew(WBTF_DEB_CMD);

	cmd.hdw.size = cpu_to_we16(sizeof(cmd));
	cmd.action = cpu_to_we16(pwiv->mac_contwow);
	cmd.wesewved = 0;

	wbtf_cmd_async(pwiv, CMD_MAC_CONTWOW,
		&cmd.hdw, sizeof(cmd));

	wbtf_deb_weave(WBTF_DEB_CMD);
}

/**
 *  wbtf_awwocate_cmd_buffew - Awwocates cmd buffew, winks it to fwee cmd queue
 *
 *  @pwiv:	A pointew to stwuct wbtf_pwivate stwuctuwe
 *
 *  Wetuwns: 0 on success.
 */
int wbtf_awwocate_cmd_buffew(stwuct wbtf_pwivate *pwiv)
{
	int wet = 0;
	u32 bufsize;
	u32 i;
	stwuct cmd_ctww_node *cmdawway;

	wbtf_deb_entew(WBTF_DEB_HOST);

	/* Awwocate and initiawize the command awway */
	bufsize = sizeof(stwuct cmd_ctww_node) * WBS_NUM_CMD_BUFFEWS;
	cmdawway = kzawwoc(bufsize, GFP_KEWNEW);
	if (!cmdawway) {
		wbtf_deb_host("AWWOC_CMD_BUF: tempcmd_awway is NUWW\n");
		wet = -1;
		goto done;
	}
	pwiv->cmd_awway = cmdawway;

	/* Awwocate and initiawize each command buffew in the command awway */
	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		cmdawway[i].cmdbuf = kzawwoc(WBS_CMD_BUFFEW_SIZE, GFP_KEWNEW);
		if (!cmdawway[i].cmdbuf) {
			wbtf_deb_host("AWWOC_CMD_BUF: ptempviwtuawaddw is NUWW\n");
			wet = -1;
			goto done;
		}
	}

	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		init_waitqueue_head(&cmdawway[i].cmdwait_q);
		wbtf_cweanup_and_insewt_cmd(pwiv, &cmdawway[i]);
	}

	wet = 0;

done:
	wbtf_deb_weave_awgs(WBTF_DEB_HOST, "wet %d", wet);
	wetuwn wet;
}

/**
 *  wbtf_fwee_cmd_buffew - Fwees the cmd buffew.
 *
 *  @pwiv:	A pointew to stwuct wbtf_pwivate stwuctuwe
 *
 *  Wetuwns: 0
 */
int wbtf_fwee_cmd_buffew(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ctww_node *cmdawway;
	unsigned int i;

	wbtf_deb_entew(WBTF_DEB_HOST);

	/* need to check if cmd awway is awwocated ow not */
	if (pwiv->cmd_awway == NUWW) {
		wbtf_deb_host("FWEE_CMD_BUF: cmd_awway is NUWW\n");
		goto done;
	}

	cmdawway = pwiv->cmd_awway;

	/* Wewease shawed memowy buffews */
	fow (i = 0; i < WBS_NUM_CMD_BUFFEWS; i++) {
		kfwee(cmdawway[i].cmdbuf);
		cmdawway[i].cmdbuf = NUWW;
	}

	/* Wewease cmd_ctww_node */
	kfwee(pwiv->cmd_awway);
	pwiv->cmd_awway = NUWW;

done:
	wbtf_deb_weave(WBTF_DEB_HOST);
	wetuwn 0;
}

/**
 *  wbtf_get_cmd_ctww_node - Gets fwee cmd node fwom fwee cmd queue.
 *
 *  @pwiv:		A pointew to stwuct wbtf_pwivate stwuctuwe
 *
 *  Wetuwns: pointew to a stwuct cmd_ctww_node ow NUWW if none avaiwabwe.
 */
static stwuct cmd_ctww_node *wbtf_get_cmd_ctww_node(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ctww_node *tempnode;
	unsigned wong fwags;

	wbtf_deb_entew(WBTF_DEB_HOST);

	if (!pwiv)
		wetuwn NUWW;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (!wist_empty(&pwiv->cmdfweeq)) {
		tempnode = wist_fiwst_entwy(&pwiv->cmdfweeq,
					    stwuct cmd_ctww_node, wist);
		wist_dew(&tempnode->wist);
	} ewse {
		wbtf_deb_host("GET_CMD_NODE: cmd_ctww_node is not avaiwabwe\n");
		tempnode = NUWW;
	}

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wbtf_deb_weave(WBTF_DEB_HOST);
	wetuwn tempnode;
}

/**
 *  wbtf_execute_next_command: execute next command in cmd pending queue.
 *
 *  @pwiv:     A pointew to stwuct wbtf_pwivate stwuctuwe
 *
 *  Wetuwns: 0 on success.
 */
int wbtf_execute_next_command(stwuct wbtf_pwivate *pwiv)
{
	stwuct cmd_ctww_node *cmdnode = NUWW;
	stwuct cmd_headew *cmd;
	unsigned wong fwags;
	int wet = 0;

	/* Debug gwoup is wbtf_deb_THWEAD and not wbtf_deb_HOST, because the
	 * onwy cawwew to us is wbtf_thwead() and we get even when a
	 * data packet is weceived */
	wbtf_deb_entew(WBTF_DEB_THWEAD);

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (pwiv->cuw_cmd) {
		pw_awewt("EXEC_NEXT_CMD: awweady pwocessing command!\n");
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wet = -1;
		goto done;
	}

	if (!wist_empty(&pwiv->cmdpendingq)) {
		cmdnode = wist_fiwst_entwy(&pwiv->cmdpendingq,
					   stwuct cmd_ctww_node, wist);
	}

	if (cmdnode) {
		cmd = cmdnode->cmdbuf;

		wist_dew(&cmdnode->wist);
		wbtf_deb_host("EXEC_NEXT_CMD: sending command 0x%04x\n",
			    we16_to_cpu(cmd->command));
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wbtf_submit_command(pwiv, cmdnode);
	} ewse
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wet = 0;
done:
	wbtf_deb_weave(WBTF_DEB_THWEAD);
	wetuwn wet;
}

static stwuct cmd_ctww_node *__wbtf_cmd_async(stwuct wbtf_pwivate *pwiv,
	uint16_t command, stwuct cmd_headew *in_cmd, int in_cmd_size,
	int (*cawwback)(stwuct wbtf_pwivate *, unsigned wong,
			stwuct cmd_headew *),
	unsigned wong cawwback_awg)
{
	stwuct cmd_ctww_node *cmdnode;

	wbtf_deb_entew(WBTF_DEB_HOST);

	if (pwiv->suwpwisewemoved) {
		wbtf_deb_host("PWEP_CMD: cawd wemoved\n");
		cmdnode = EWW_PTW(-ENOENT);
		goto done;
	}

	cmdnode = wbtf_get_cmd_ctww_node(pwiv);
	if (cmdnode == NUWW) {
		wbtf_deb_host("PWEP_CMD: cmdnode is NUWW\n");

		/* Wake up main thwead to execute next command */
		queue_wowk(wbtf_wq, &pwiv->cmd_wowk);
		cmdnode = EWW_PTW(-ENOBUFS);
		goto done;
	}

	cmdnode->cawwback = cawwback;
	cmdnode->cawwback_awg = cawwback_awg;

	/* Copy the incoming command to the buffew */
	memcpy(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set sequence numbew, cwean wesuwt, move to buffew */
	pwiv->seqnum++;
	cmdnode->cmdbuf->command = cpu_to_we16(command);
	cmdnode->cmdbuf->size    = cpu_to_we16(in_cmd_size);
	cmdnode->cmdbuf->seqnum  = cpu_to_we16(pwiv->seqnum);
	cmdnode->cmdbuf->wesuwt  = 0;

	wbtf_deb_host("PWEP_CMD: command 0x%04x\n", command);

	cmdnode->cmdwaitqwoken = 0;
	wbtf_queue_cmd(pwiv, cmdnode);
	queue_wowk(wbtf_wq, &pwiv->cmd_wowk);

 done:
	wbtf_deb_weave_awgs(WBTF_DEB_HOST, "wet %p", cmdnode);
	wetuwn cmdnode;
}

void wbtf_cmd_async(stwuct wbtf_pwivate *pwiv, uint16_t command,
	stwuct cmd_headew *in_cmd, int in_cmd_size)
{
	wbtf_deb_entew(WBTF_DEB_CMD);
	__wbtf_cmd_async(pwiv, command, in_cmd, in_cmd_size, NUWW, 0);
	wbtf_deb_weave(WBTF_DEB_CMD);
}

int __wbtf_cmd(stwuct wbtf_pwivate *pwiv, uint16_t command,
	      stwuct cmd_headew *in_cmd, int in_cmd_size,
	      int (*cawwback)(stwuct wbtf_pwivate *,
			      unsigned wong, stwuct cmd_headew *),
	      unsigned wong cawwback_awg)
{
	stwuct cmd_ctww_node *cmdnode;
	unsigned wong fwags;
	int wet = 0;

	wbtf_deb_entew(WBTF_DEB_HOST);

	cmdnode = __wbtf_cmd_async(pwiv, command, in_cmd, in_cmd_size,
				  cawwback, cawwback_awg);
	if (IS_EWW(cmdnode)) {
		wet = PTW_EWW(cmdnode);
		goto done;
	}

	might_sweep();
	wet = wait_event_intewwuptibwe(cmdnode->cmdwait_q,
				       cmdnode->cmdwaitqwoken);
	if (wet) {
		pw_info("PWEP_CMD: command 0x%04x intewwupted by signaw: %d\n",
			    command, wet);
		goto done;
	}

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	wet = cmdnode->wesuwt;
	if (wet)
		pw_info("PWEP_CMD: command 0x%04x faiwed: %d\n",
			    command, wet);

	__wbtf_cweanup_and_insewt_cmd(pwiv, cmdnode);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

done:
	wbtf_deb_weave_awgs(WBTF_DEB_HOST, "wet %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__wbtf_cmd);

/* Caww howding dwivew_wock */
void wbtf_cmd_wesponse_wx(stwuct wbtf_pwivate *pwiv)
{
	pwiv->cmd_wesponse_wxed = 1;
	queue_wowk(wbtf_wq, &pwiv->cmd_wowk);
}
EXPOWT_SYMBOW_GPW(wbtf_cmd_wesponse_wx);

int wbtf_pwocess_wx_command(stwuct wbtf_pwivate *pwiv)
{
	uint16_t wespcmd, cuwcmd;
	stwuct cmd_headew *wesp;
	int wet = 0;
	unsigned wong fwags;
	uint16_t wesuwt;

	wbtf_deb_entew(WBTF_DEB_CMD);

	mutex_wock(&pwiv->wock);
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (!pwiv->cuw_cmd) {
		wet = -1;
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		goto done;
	}

	wesp = (void *)pwiv->cmd_wesp_buff;
	cuwcmd = we16_to_cpu(pwiv->cuw_cmd->cmdbuf->command);
	wespcmd = we16_to_cpu(wesp->command);
	wesuwt = we16_to_cpu(wesp->wesuwt);

	wbtf_deb_cmd("wibewtastf: cmd wesponse 0x%04x, seq %d, size %d\n",
		     wespcmd, we16_to_cpu(wesp->seqnum),
		     we16_to_cpu(wesp->size));

	if (wesp->seqnum != pwiv->cuw_cmd->cmdbuf->seqnum) {
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wet = -1;
		goto done;
	}
	if (wespcmd != CMD_WET(cuwcmd)) {
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wet = -1;
		goto done;
	}

	if (wesp->wesuwt == cpu_to_we16(0x0004)) {
		/* 0x0004 means -EAGAIN. Dwop the wesponse, wet it time out
		   and be wesubmitted */
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		wet = -1;
		goto done;
	}

	/* Now we got wesponse fwom FW, cancew the command timew */
	dew_timew(&pwiv->command_timew);
	pwiv->cmd_timed_out = 0;
	if (pwiv->nw_wetwies)
		pwiv->nw_wetwies = 0;

	/* If the command is not successfuw, cweanup and wetuwn faiwuwe */
	if ((wesuwt != 0 || !(wespcmd & 0x8000))) {
		/*
		 * Handwing ewwows hewe
		 */
		switch (wespcmd) {
		case CMD_WET(CMD_GET_HW_SPEC):
		case CMD_WET(CMD_802_11_WESET):
			pw_info("wibewtastf: weset faiwed\n");
			bweak;

		}
		wbtf_compwete_command(pwiv, pwiv->cuw_cmd, wesuwt);
		spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

		wet = -1;
		goto done;
	}

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	if (pwiv->cuw_cmd && pwiv->cuw_cmd->cawwback) {
		wet = pwiv->cuw_cmd->cawwback(pwiv, pwiv->cuw_cmd->cawwback_awg,
				wesp);
	}
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (pwiv->cuw_cmd) {
		/* Cwean up and Put cuwwent command back to cmdfweeq */
		wbtf_compwete_command(pwiv, pwiv->cuw_cmd, wesuwt);
	}
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

done:
	mutex_unwock(&pwiv->wock);
	wbtf_deb_weave_awgs(WBTF_DEB_CMD, "wet %d", wet);
	wetuwn wet;
}
