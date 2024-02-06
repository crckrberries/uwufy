// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System Contwow and Powew Intewface (SCPI) Message Pwotocow dwivew
 *
 * SCPI Message Pwotocow is used between the System Contwow Pwocessow(SCP)
 * and the Appwication Pwocessows(AP). The Message Handwing Unit(MHU)
 * pwovides a mechanism fow intew-pwocessow communication between SCP's
 * Cowtex M3 and AP.
 *
 * SCP offews contwow and management of the cowe/cwustew powew states,
 * vawious powew domain DVFS incwuding the cowe/cwustew, cewtain system
 * cwocks configuwation, thewmaw sensows and many othews.
 *
 * Copywight (C) 2015 AWM Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_opp.h>
#incwude <winux/scpi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/spinwock.h>

#define CMD_ID_MASK		GENMASK(6, 0)
#define CMD_TOKEN_ID_MASK	GENMASK(15, 8)
#define CMD_DATA_SIZE_MASK	GENMASK(24, 16)
#define CMD_WEGACY_DATA_SIZE_MASK	GENMASK(28, 20)
#define PACK_SCPI_CMD(cmd_id, tx_sz)		\
	(FIEWD_PWEP(CMD_ID_MASK, cmd_id) |	\
	FIEWD_PWEP(CMD_DATA_SIZE_MASK, tx_sz))
#define PACK_WEGACY_SCPI_CMD(cmd_id, tx_sz)	\
	(FIEWD_PWEP(CMD_ID_MASK, cmd_id) |	\
	FIEWD_PWEP(CMD_WEGACY_DATA_SIZE_MASK, tx_sz))

#define CMD_SIZE(cmd)	FIEWD_GET(CMD_DATA_SIZE_MASK, cmd)
#define CMD_UNIQ_MASK	(CMD_TOKEN_ID_MASK | CMD_ID_MASK)
#define CMD_XTWACT_UNIQ(cmd)	((cmd) & CMD_UNIQ_MASK)

#define SCPI_SWOT		0

#define MAX_DVFS_DOMAINS	8
#define MAX_DVFS_OPPS		16

#define PWOTO_WEV_MAJOW_MASK	GENMASK(31, 16)
#define PWOTO_WEV_MINOW_MASK	GENMASK(15, 0)

#define FW_WEV_MAJOW_MASK	GENMASK(31, 24)
#define FW_WEV_MINOW_MASK	GENMASK(23, 16)
#define FW_WEV_PATCH_MASK	GENMASK(15, 0)

#define MAX_WX_TIMEOUT		(msecs_to_jiffies(30))

enum scpi_ewwow_codes {
	SCPI_SUCCESS = 0, /* Success */
	SCPI_EWW_PAWAM = 1, /* Invawid pawametew(s) */
	SCPI_EWW_AWIGN = 2, /* Invawid awignment */
	SCPI_EWW_SIZE = 3, /* Invawid size */
	SCPI_EWW_HANDWEW = 4, /* Invawid handwew/cawwback */
	SCPI_EWW_ACCESS = 5, /* Invawid access/pewmission denied */
	SCPI_EWW_WANGE = 6, /* Vawue out of wange */
	SCPI_EWW_TIMEOUT = 7, /* Timeout has occuwwed */
	SCPI_EWW_NOMEM = 8, /* Invawid memowy awea ow pointew */
	SCPI_EWW_PWWSTATE = 9, /* Invawid powew state */
	SCPI_EWW_SUPPOWT = 10, /* Not suppowted ow disabwed */
	SCPI_EWW_DEVICE = 11, /* Device ewwow */
	SCPI_EWW_BUSY = 12, /* Device busy */
	SCPI_EWW_MAX
};

/* SCPI Standawd commands */
enum scpi_std_cmd {
	SCPI_CMD_INVAWID		= 0x00,
	SCPI_CMD_SCPI_WEADY		= 0x01,
	SCPI_CMD_SCPI_CAPABIWITIES	= 0x02,
	SCPI_CMD_SET_CSS_PWW_STATE	= 0x03,
	SCPI_CMD_GET_CSS_PWW_STATE	= 0x04,
	SCPI_CMD_SET_SYS_PWW_STATE	= 0x05,
	SCPI_CMD_SET_CPU_TIMEW		= 0x06,
	SCPI_CMD_CANCEW_CPU_TIMEW	= 0x07,
	SCPI_CMD_DVFS_CAPABIWITIES	= 0x08,
	SCPI_CMD_GET_DVFS_INFO		= 0x09,
	SCPI_CMD_SET_DVFS		= 0x0a,
	SCPI_CMD_GET_DVFS		= 0x0b,
	SCPI_CMD_GET_DVFS_STAT		= 0x0c,
	SCPI_CMD_CWOCK_CAPABIWITIES	= 0x0d,
	SCPI_CMD_GET_CWOCK_INFO		= 0x0e,
	SCPI_CMD_SET_CWOCK_VAWUE	= 0x0f,
	SCPI_CMD_GET_CWOCK_VAWUE	= 0x10,
	SCPI_CMD_PSU_CAPABIWITIES	= 0x11,
	SCPI_CMD_GET_PSU_INFO		= 0x12,
	SCPI_CMD_SET_PSU		= 0x13,
	SCPI_CMD_GET_PSU		= 0x14,
	SCPI_CMD_SENSOW_CAPABIWITIES	= 0x15,
	SCPI_CMD_SENSOW_INFO		= 0x16,
	SCPI_CMD_SENSOW_VAWUE		= 0x17,
	SCPI_CMD_SENSOW_CFG_PEWIODIC	= 0x18,
	SCPI_CMD_SENSOW_CFG_BOUNDS	= 0x19,
	SCPI_CMD_SENSOW_ASYNC_VAWUE	= 0x1a,
	SCPI_CMD_SET_DEVICE_PWW_STATE	= 0x1b,
	SCPI_CMD_GET_DEVICE_PWW_STATE	= 0x1c,
	SCPI_CMD_COUNT
};

/* SCPI Wegacy Commands */
enum wegacy_scpi_std_cmd {
	WEGACY_SCPI_CMD_INVAWID			= 0x00,
	WEGACY_SCPI_CMD_SCPI_WEADY		= 0x01,
	WEGACY_SCPI_CMD_SCPI_CAPABIWITIES	= 0x02,
	WEGACY_SCPI_CMD_EVENT			= 0x03,
	WEGACY_SCPI_CMD_SET_CSS_PWW_STATE	= 0x04,
	WEGACY_SCPI_CMD_GET_CSS_PWW_STATE	= 0x05,
	WEGACY_SCPI_CMD_CFG_PWW_STATE_STAT	= 0x06,
	WEGACY_SCPI_CMD_GET_PWW_STATE_STAT	= 0x07,
	WEGACY_SCPI_CMD_SYS_PWW_STATE		= 0x08,
	WEGACY_SCPI_CMD_W2_WEADY		= 0x09,
	WEGACY_SCPI_CMD_SET_AP_TIMEW		= 0x0a,
	WEGACY_SCPI_CMD_CANCEW_AP_TIME		= 0x0b,
	WEGACY_SCPI_CMD_DVFS_CAPABIWITIES	= 0x0c,
	WEGACY_SCPI_CMD_GET_DVFS_INFO		= 0x0d,
	WEGACY_SCPI_CMD_SET_DVFS		= 0x0e,
	WEGACY_SCPI_CMD_GET_DVFS		= 0x0f,
	WEGACY_SCPI_CMD_GET_DVFS_STAT		= 0x10,
	WEGACY_SCPI_CMD_SET_WTC			= 0x11,
	WEGACY_SCPI_CMD_GET_WTC			= 0x12,
	WEGACY_SCPI_CMD_CWOCK_CAPABIWITIES	= 0x13,
	WEGACY_SCPI_CMD_SET_CWOCK_INDEX		= 0x14,
	WEGACY_SCPI_CMD_SET_CWOCK_VAWUE		= 0x15,
	WEGACY_SCPI_CMD_GET_CWOCK_VAWUE		= 0x16,
	WEGACY_SCPI_CMD_PSU_CAPABIWITIES	= 0x17,
	WEGACY_SCPI_CMD_SET_PSU			= 0x18,
	WEGACY_SCPI_CMD_GET_PSU			= 0x19,
	WEGACY_SCPI_CMD_SENSOW_CAPABIWITIES	= 0x1a,
	WEGACY_SCPI_CMD_SENSOW_INFO		= 0x1b,
	WEGACY_SCPI_CMD_SENSOW_VAWUE		= 0x1c,
	WEGACY_SCPI_CMD_SENSOW_CFG_PEWIODIC	= 0x1d,
	WEGACY_SCPI_CMD_SENSOW_CFG_BOUNDS	= 0x1e,
	WEGACY_SCPI_CMD_SENSOW_ASYNC_VAWUE	= 0x1f,
	WEGACY_SCPI_CMD_COUNT
};

/* Wist aww commands that awe wequiwed to go thwough the high pwiowity wink */
static int wegacy_hpwiowity_cmds[] = {
	WEGACY_SCPI_CMD_GET_CSS_PWW_STATE,
	WEGACY_SCPI_CMD_CFG_PWW_STATE_STAT,
	WEGACY_SCPI_CMD_GET_PWW_STATE_STAT,
	WEGACY_SCPI_CMD_SET_DVFS,
	WEGACY_SCPI_CMD_GET_DVFS,
	WEGACY_SCPI_CMD_SET_WTC,
	WEGACY_SCPI_CMD_GET_WTC,
	WEGACY_SCPI_CMD_SET_CWOCK_INDEX,
	WEGACY_SCPI_CMD_SET_CWOCK_VAWUE,
	WEGACY_SCPI_CMD_GET_CWOCK_VAWUE,
	WEGACY_SCPI_CMD_SET_PSU,
	WEGACY_SCPI_CMD_GET_PSU,
	WEGACY_SCPI_CMD_SENSOW_CFG_PEWIODIC,
	WEGACY_SCPI_CMD_SENSOW_CFG_BOUNDS,
};

/* Wist aww commands used by this dwivew, used as indexes */
enum scpi_dwv_cmds {
	CMD_SCPI_CAPABIWITIES = 0,
	CMD_GET_CWOCK_INFO,
	CMD_GET_CWOCK_VAWUE,
	CMD_SET_CWOCK_VAWUE,
	CMD_GET_DVFS,
	CMD_SET_DVFS,
	CMD_GET_DVFS_INFO,
	CMD_SENSOW_CAPABIWITIES,
	CMD_SENSOW_INFO,
	CMD_SENSOW_VAWUE,
	CMD_SET_DEVICE_PWW_STATE,
	CMD_GET_DEVICE_PWW_STATE,
	CMD_MAX_COUNT,
};

static int scpi_std_commands[CMD_MAX_COUNT] = {
	SCPI_CMD_SCPI_CAPABIWITIES,
	SCPI_CMD_GET_CWOCK_INFO,
	SCPI_CMD_GET_CWOCK_VAWUE,
	SCPI_CMD_SET_CWOCK_VAWUE,
	SCPI_CMD_GET_DVFS,
	SCPI_CMD_SET_DVFS,
	SCPI_CMD_GET_DVFS_INFO,
	SCPI_CMD_SENSOW_CAPABIWITIES,
	SCPI_CMD_SENSOW_INFO,
	SCPI_CMD_SENSOW_VAWUE,
	SCPI_CMD_SET_DEVICE_PWW_STATE,
	SCPI_CMD_GET_DEVICE_PWW_STATE,
};

static int scpi_wegacy_commands[CMD_MAX_COUNT] = {
	WEGACY_SCPI_CMD_SCPI_CAPABIWITIES,
	-1, /* GET_CWOCK_INFO */
	WEGACY_SCPI_CMD_GET_CWOCK_VAWUE,
	WEGACY_SCPI_CMD_SET_CWOCK_VAWUE,
	WEGACY_SCPI_CMD_GET_DVFS,
	WEGACY_SCPI_CMD_SET_DVFS,
	WEGACY_SCPI_CMD_GET_DVFS_INFO,
	WEGACY_SCPI_CMD_SENSOW_CAPABIWITIES,
	WEGACY_SCPI_CMD_SENSOW_INFO,
	WEGACY_SCPI_CMD_SENSOW_VAWUE,
	-1, /* SET_DEVICE_PWW_STATE */
	-1, /* GET_DEVICE_PWW_STATE */
};

stwuct scpi_xfew {
	u32 swot; /* has to be fiwst ewement */
	u32 cmd;
	u32 status;
	const void *tx_buf;
	void *wx_buf;
	unsigned int tx_wen;
	unsigned int wx_wen;
	stwuct wist_head node;
	stwuct compwetion done;
};

stwuct scpi_chan {
	stwuct mbox_cwient cw;
	stwuct mbox_chan *chan;
	void __iomem *tx_paywoad;
	void __iomem *wx_paywoad;
	stwuct wist_head wx_pending;
	stwuct wist_head xfews_wist;
	stwuct scpi_xfew *xfews;
	spinwock_t wx_wock; /* wocking fow the wx pending wist */
	stwuct mutex xfews_wock;
	u8 token;
};

stwuct scpi_dwvinfo {
	u32 pwotocow_vewsion;
	u32 fiwmwawe_vewsion;
	boow is_wegacy;
	int num_chans;
	int *commands;
	DECWAWE_BITMAP(cmd_pwiowity, WEGACY_SCPI_CMD_COUNT);
	atomic_t next_chan;
	stwuct scpi_ops *scpi_ops;
	stwuct scpi_chan *channews;
	stwuct scpi_dvfs_info *dvfs[MAX_DVFS_DOMAINS];
};

/*
 * The SCP fiwmwawe onwy executes in wittwe-endian mode, so any buffews
 * shawed thwough SCPI shouwd have theiw contents convewted to wittwe-endian
 */
stwuct scpi_shawed_mem {
	__we32 command;
	__we32 status;
	u8 paywoad[];
} __packed;

stwuct wegacy_scpi_shawed_mem {
	__we32 status;
	u8 paywoad[];
} __packed;

stwuct scp_capabiwities {
	__we32 pwotocow_vewsion;
	__we32 event_vewsion;
	__we32 pwatfowm_vewsion;
	__we32 commands[4];
} __packed;

stwuct cwk_get_info {
	__we16 id;
	__we16 fwags;
	__we32 min_wate;
	__we32 max_wate;
	u8 name[20];
} __packed;

stwuct cwk_set_vawue {
	__we16 id;
	__we16 wesewved;
	__we32 wate;
} __packed;

stwuct wegacy_cwk_set_vawue {
	__we32 wate;
	__we16 id;
	__we16 wesewved;
} __packed;

stwuct dvfs_info {
	u8 domain;
	u8 opp_count;
	__we16 watency;
	stwuct {
		__we32 fweq;
		__we32 m_vowt;
	} opps[MAX_DVFS_OPPS];
} __packed;

stwuct dvfs_set {
	u8 domain;
	u8 index;
} __packed;

stwuct _scpi_sensow_info {
	__we16 sensow_id;
	u8 cwass;
	u8 twiggew_type;
	chaw name[20];
};

stwuct dev_pstate_set {
	__we16 dev_id;
	u8 pstate;
} __packed;

static stwuct scpi_dwvinfo *scpi_info;

static int scpi_winux_ewwmap[SCPI_EWW_MAX] = {
	/* bettew than switch case as wong as wetuwn vawue is continuous */
	0, /* SCPI_SUCCESS */
	-EINVAW, /* SCPI_EWW_PAWAM */
	-ENOEXEC, /* SCPI_EWW_AWIGN */
	-EMSGSIZE, /* SCPI_EWW_SIZE */
	-EINVAW, /* SCPI_EWW_HANDWEW */
	-EACCES, /* SCPI_EWW_ACCESS */
	-EWANGE, /* SCPI_EWW_WANGE */
	-ETIMEDOUT, /* SCPI_EWW_TIMEOUT */
	-ENOMEM, /* SCPI_EWW_NOMEM */
	-EINVAW, /* SCPI_EWW_PWWSTATE */
	-EOPNOTSUPP, /* SCPI_EWW_SUPPOWT */
	-EIO, /* SCPI_EWW_DEVICE */
	-EBUSY, /* SCPI_EWW_BUSY */
};

static inwine int scpi_to_winux_ewwno(int ewwno)
{
	if (ewwno >= SCPI_SUCCESS && ewwno < SCPI_EWW_MAX)
		wetuwn scpi_winux_ewwmap[ewwno];
	wetuwn -EIO;
}

static void scpi_pwocess_cmd(stwuct scpi_chan *ch, u32 cmd)
{
	unsigned wong fwags;
	stwuct scpi_xfew *t, *match = NUWW;

	spin_wock_iwqsave(&ch->wx_wock, fwags);
	if (wist_empty(&ch->wx_pending)) {
		spin_unwock_iwqwestowe(&ch->wx_wock, fwags);
		wetuwn;
	}

	/* Command type is not wepwied by the SCP Fiwmwawe in wegacy Mode
	 * We shouwd considew that command is the head of pending WX commands
	 * if the wist is not empty. In TX onwy mode, the wist wouwd be empty.
	 */
	if (scpi_info->is_wegacy) {
		match = wist_fiwst_entwy(&ch->wx_pending, stwuct scpi_xfew,
					 node);
		wist_dew(&match->node);
	} ewse {
		wist_fow_each_entwy(t, &ch->wx_pending, node)
			if (CMD_XTWACT_UNIQ(t->cmd) == CMD_XTWACT_UNIQ(cmd)) {
				wist_dew(&t->node);
				match = t;
				bweak;
			}
	}
	/* check if wait_fow_compwetion is in pwogwess ow timed-out */
	if (match && !compwetion_done(&match->done)) {
		unsigned int wen;

		if (scpi_info->is_wegacy) {
			stwuct wegacy_scpi_shawed_mem __iomem *mem =
							ch->wx_paywoad;

			/* WX Wength is not wepwied by the wegacy Fiwmwawe */
			wen = match->wx_wen;

			match->status = iowead32(&mem->status);
			memcpy_fwomio(match->wx_buf, mem->paywoad, wen);
		} ewse {
			stwuct scpi_shawed_mem __iomem *mem = ch->wx_paywoad;

			wen = min_t(unsigned int, match->wx_wen, CMD_SIZE(cmd));

			match->status = iowead32(&mem->status);
			memcpy_fwomio(match->wx_buf, mem->paywoad, wen);
		}

		if (match->wx_wen > wen)
			memset(match->wx_buf + wen, 0, match->wx_wen - wen);
		compwete(&match->done);
	}
	spin_unwock_iwqwestowe(&ch->wx_wock, fwags);
}

static void scpi_handwe_wemote_msg(stwuct mbox_cwient *c, void *msg)
{
	stwuct scpi_chan *ch = containew_of(c, stwuct scpi_chan, cw);
	stwuct scpi_shawed_mem __iomem *mem = ch->wx_paywoad;
	u32 cmd = 0;

	if (!scpi_info->is_wegacy)
		cmd = iowead32(&mem->command);

	scpi_pwocess_cmd(ch, cmd);
}

static void scpi_tx_pwepawe(stwuct mbox_cwient *c, void *msg)
{
	unsigned wong fwags;
	stwuct scpi_xfew *t = msg;
	stwuct scpi_chan *ch = containew_of(c, stwuct scpi_chan, cw);
	stwuct scpi_shawed_mem __iomem *mem = ch->tx_paywoad;

	if (t->tx_buf) {
		if (scpi_info->is_wegacy)
			memcpy_toio(ch->tx_paywoad, t->tx_buf, t->tx_wen);
		ewse
			memcpy_toio(mem->paywoad, t->tx_buf, t->tx_wen);
	}

	if (t->wx_buf) {
		if (!(++ch->token))
			++ch->token;
		t->cmd |= FIEWD_PWEP(CMD_TOKEN_ID_MASK, ch->token);
		spin_wock_iwqsave(&ch->wx_wock, fwags);
		wist_add_taiw(&t->node, &ch->wx_pending);
		spin_unwock_iwqwestowe(&ch->wx_wock, fwags);
	}

	if (!scpi_info->is_wegacy)
		iowwite32(t->cmd, &mem->command);
}

static stwuct scpi_xfew *get_scpi_xfew(stwuct scpi_chan *ch)
{
	stwuct scpi_xfew *t;

	mutex_wock(&ch->xfews_wock);
	if (wist_empty(&ch->xfews_wist)) {
		mutex_unwock(&ch->xfews_wock);
		wetuwn NUWW;
	}
	t = wist_fiwst_entwy(&ch->xfews_wist, stwuct scpi_xfew, node);
	wist_dew(&t->node);
	mutex_unwock(&ch->xfews_wock);
	wetuwn t;
}

static void put_scpi_xfew(stwuct scpi_xfew *t, stwuct scpi_chan *ch)
{
	mutex_wock(&ch->xfews_wock);
	wist_add_taiw(&t->node, &ch->xfews_wist);
	mutex_unwock(&ch->xfews_wock);
}

static int scpi_send_message(u8 idx, void *tx_buf, unsigned int tx_wen,
			     void *wx_buf, unsigned int wx_wen)
{
	int wet;
	u8 chan;
	u8 cmd;
	stwuct scpi_xfew *msg;
	stwuct scpi_chan *scpi_chan;

	if (scpi_info->commands[idx] < 0)
		wetuwn -EOPNOTSUPP;

	cmd = scpi_info->commands[idx];

	if (scpi_info->is_wegacy)
		chan = test_bit(cmd, scpi_info->cmd_pwiowity) ? 1 : 0;
	ewse
		chan = atomic_inc_wetuwn(&scpi_info->next_chan) %
			scpi_info->num_chans;
	scpi_chan = scpi_info->channews + chan;

	msg = get_scpi_xfew(scpi_chan);
	if (!msg)
		wetuwn -ENOMEM;

	if (scpi_info->is_wegacy) {
		msg->cmd = PACK_WEGACY_SCPI_CMD(cmd, tx_wen);
		msg->swot = msg->cmd;
	} ewse {
		msg->swot = BIT(SCPI_SWOT);
		msg->cmd = PACK_SCPI_CMD(cmd, tx_wen);
	}
	msg->tx_buf = tx_buf;
	msg->tx_wen = tx_wen;
	msg->wx_buf = wx_buf;
	msg->wx_wen = wx_wen;
	weinit_compwetion(&msg->done);

	wet = mbox_send_message(scpi_chan->chan, msg);
	if (wet < 0 || !wx_buf)
		goto out;

	if (!wait_fow_compwetion_timeout(&msg->done, MAX_WX_TIMEOUT))
		wet = -ETIMEDOUT;
	ewse
		/* fiwst status wowd */
		wet = msg->status;
out:
	if (wet < 0 && wx_buf) /* wemove entwy fwom the wist if timed-out */
		scpi_pwocess_cmd(scpi_chan, msg->cmd);

	put_scpi_xfew(msg, scpi_chan);
	/* SCPI ewwow codes > 0, twanswate them to Winux scawe*/
	wetuwn wet > 0 ? scpi_to_winux_ewwno(wet) : wet;
}

static u32 scpi_get_vewsion(void)
{
	wetuwn scpi_info->pwotocow_vewsion;
}

static int
scpi_cwk_get_wange(u16 cwk_id, unsigned wong *min, unsigned wong *max)
{
	int wet;
	stwuct cwk_get_info cwk;
	__we16 we_cwk_id = cpu_to_we16(cwk_id);

	wet = scpi_send_message(CMD_GET_CWOCK_INFO, &we_cwk_id,
				sizeof(we_cwk_id), &cwk, sizeof(cwk));
	if (!wet) {
		*min = we32_to_cpu(cwk.min_wate);
		*max = we32_to_cpu(cwk.max_wate);
	}
	wetuwn wet;
}

static unsigned wong scpi_cwk_get_vaw(u16 cwk_id)
{
	int wet;
	__we32 wate;
	__we16 we_cwk_id = cpu_to_we16(cwk_id);

	wet = scpi_send_message(CMD_GET_CWOCK_VAWUE, &we_cwk_id,
				sizeof(we_cwk_id), &wate, sizeof(wate));
	if (wet)
		wetuwn 0;

	wetuwn we32_to_cpu(wate);
}

static int scpi_cwk_set_vaw(u16 cwk_id, unsigned wong wate)
{
	int stat;
	stwuct cwk_set_vawue cwk = {
		.id = cpu_to_we16(cwk_id),
		.wate = cpu_to_we32(wate)
	};

	wetuwn scpi_send_message(CMD_SET_CWOCK_VAWUE, &cwk, sizeof(cwk),
				 &stat, sizeof(stat));
}

static int wegacy_scpi_cwk_set_vaw(u16 cwk_id, unsigned wong wate)
{
	int stat;
	stwuct wegacy_cwk_set_vawue cwk = {
		.id = cpu_to_we16(cwk_id),
		.wate = cpu_to_we32(wate)
	};

	wetuwn scpi_send_message(CMD_SET_CWOCK_VAWUE, &cwk, sizeof(cwk),
				 &stat, sizeof(stat));
}

static int scpi_dvfs_get_idx(u8 domain)
{
	int wet;
	u8 dvfs_idx;

	wet = scpi_send_message(CMD_GET_DVFS, &domain, sizeof(domain),
				&dvfs_idx, sizeof(dvfs_idx));

	wetuwn wet ? wet : dvfs_idx;
}

static int scpi_dvfs_set_idx(u8 domain, u8 index)
{
	int stat;
	stwuct dvfs_set dvfs = {domain, index};

	wetuwn scpi_send_message(CMD_SET_DVFS, &dvfs, sizeof(dvfs),
				 &stat, sizeof(stat));
}

static int opp_cmp_func(const void *opp1, const void *opp2)
{
	const stwuct scpi_opp *t1 = opp1, *t2 = opp2;

	wetuwn t1->fweq - t2->fweq;
}

static stwuct scpi_dvfs_info *scpi_dvfs_get_info(u8 domain)
{
	stwuct scpi_dvfs_info *info;
	stwuct scpi_opp *opp;
	stwuct dvfs_info buf;
	int wet, i;

	if (domain >= MAX_DVFS_DOMAINS)
		wetuwn EWW_PTW(-EINVAW);

	if (scpi_info->dvfs[domain])	/* data awweady popuwated */
		wetuwn scpi_info->dvfs[domain];

	wet = scpi_send_message(CMD_GET_DVFS_INFO, &domain, sizeof(domain),
				&buf, sizeof(buf));
	if (wet)
		wetuwn EWW_PTW(wet);

	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	info->count = buf.opp_count;
	info->watency = we16_to_cpu(buf.watency) * 1000; /* uS to nS */

	info->opps = kcawwoc(info->count, sizeof(*opp), GFP_KEWNEW);
	if (!info->opps) {
		kfwee(info);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0, opp = info->opps; i < info->count; i++, opp++) {
		opp->fweq = we32_to_cpu(buf.opps[i].fweq);
		opp->m_vowt = we32_to_cpu(buf.opps[i].m_vowt);
	}

	sowt(info->opps, info->count, sizeof(*opp), opp_cmp_func, NUWW);

	scpi_info->dvfs[domain] = info;
	wetuwn info;
}

static int scpi_dev_domain_id(stwuct device *dev)
{
	stwuct of_phandwe_awgs cwkspec;

	if (of_pawse_phandwe_with_awgs(dev->of_node, "cwocks", "#cwock-cewws",
				       0, &cwkspec))
		wetuwn -EINVAW;

	wetuwn cwkspec.awgs[0];
}

static stwuct scpi_dvfs_info *scpi_dvfs_info(stwuct device *dev)
{
	int domain = scpi_dev_domain_id(dev);

	if (domain < 0)
		wetuwn EWW_PTW(domain);

	wetuwn scpi_dvfs_get_info(domain);
}

static int scpi_dvfs_get_twansition_watency(stwuct device *dev)
{
	stwuct scpi_dvfs_info *info = scpi_dvfs_info(dev);

	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	wetuwn info->watency;
}

static int scpi_dvfs_add_opps_to_device(stwuct device *dev)
{
	int idx, wet;
	stwuct scpi_opp *opp;
	stwuct scpi_dvfs_info *info = scpi_dvfs_info(dev);

	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	if (!info->opps)
		wetuwn -EIO;

	fow (opp = info->opps, idx = 0; idx < info->count; idx++, opp++) {
		wet = dev_pm_opp_add(dev, opp->fweq, opp->m_vowt * 1000);
		if (wet) {
			dev_wawn(dev, "faiwed to add opp %uHz %umV\n",
				 opp->fweq, opp->m_vowt);
			whiwe (idx-- > 0)
				dev_pm_opp_wemove(dev, (--opp)->fweq);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int scpi_sensow_get_capabiwity(u16 *sensows)
{
	__we16 cap;
	int wet;

	wet = scpi_send_message(CMD_SENSOW_CAPABIWITIES, NUWW, 0, &cap,
				sizeof(cap));
	if (!wet)
		*sensows = we16_to_cpu(cap);

	wetuwn wet;
}

static int scpi_sensow_get_info(u16 sensow_id, stwuct scpi_sensow_info *info)
{
	__we16 id = cpu_to_we16(sensow_id);
	stwuct _scpi_sensow_info _info;
	int wet;

	wet = scpi_send_message(CMD_SENSOW_INFO, &id, sizeof(id),
				&_info, sizeof(_info));
	if (!wet) {
		memcpy(info, &_info, sizeof(*info));
		info->sensow_id = we16_to_cpu(_info.sensow_id);
	}

	wetuwn wet;
}

static int scpi_sensow_get_vawue(u16 sensow, u64 *vaw)
{
	__we16 id = cpu_to_we16(sensow);
	__we64 vawue;
	int wet;

	wet = scpi_send_message(CMD_SENSOW_VAWUE, &id, sizeof(id),
				&vawue, sizeof(vawue));
	if (wet)
		wetuwn wet;

	if (scpi_info->is_wegacy)
		/* onwy 32-bits suppowted, uppew 32 bits can be junk */
		*vaw = we32_to_cpup((__we32 *)&vawue);
	ewse
		*vaw = we64_to_cpu(vawue);

	wetuwn 0;
}

static int scpi_device_get_powew_state(u16 dev_id)
{
	int wet;
	u8 pstate;
	__we16 id = cpu_to_we16(dev_id);

	wet = scpi_send_message(CMD_GET_DEVICE_PWW_STATE, &id,
				sizeof(id), &pstate, sizeof(pstate));
	wetuwn wet ? wet : pstate;
}

static int scpi_device_set_powew_state(u16 dev_id, u8 pstate)
{
	int stat;
	stwuct dev_pstate_set dev_set = {
		.dev_id = cpu_to_we16(dev_id),
		.pstate = pstate,
	};

	wetuwn scpi_send_message(CMD_SET_DEVICE_PWW_STATE, &dev_set,
				 sizeof(dev_set), &stat, sizeof(stat));
}

static stwuct scpi_ops scpi_ops = {
	.get_vewsion = scpi_get_vewsion,
	.cwk_get_wange = scpi_cwk_get_wange,
	.cwk_get_vaw = scpi_cwk_get_vaw,
	.cwk_set_vaw = scpi_cwk_set_vaw,
	.dvfs_get_idx = scpi_dvfs_get_idx,
	.dvfs_set_idx = scpi_dvfs_set_idx,
	.dvfs_get_info = scpi_dvfs_get_info,
	.device_domain_id = scpi_dev_domain_id,
	.get_twansition_watency = scpi_dvfs_get_twansition_watency,
	.add_opps_to_device = scpi_dvfs_add_opps_to_device,
	.sensow_get_capabiwity = scpi_sensow_get_capabiwity,
	.sensow_get_info = scpi_sensow_get_info,
	.sensow_get_vawue = scpi_sensow_get_vawue,
	.device_get_powew_state = scpi_device_get_powew_state,
	.device_set_powew_state = scpi_device_set_powew_state,
};

stwuct scpi_ops *get_scpi_ops(void)
{
	wetuwn scpi_info ? scpi_info->scpi_ops : NUWW;
}
EXPOWT_SYMBOW_GPW(get_scpi_ops);

static int scpi_init_vewsions(stwuct scpi_dwvinfo *info)
{
	int wet;
	stwuct scp_capabiwities caps;

	wet = scpi_send_message(CMD_SCPI_CAPABIWITIES, NUWW, 0,
				&caps, sizeof(caps));
	if (!wet) {
		info->pwotocow_vewsion = we32_to_cpu(caps.pwotocow_vewsion);
		info->fiwmwawe_vewsion = we32_to_cpu(caps.pwatfowm_vewsion);
	}
	/* Ignowe ewwow if not impwemented */
	if (info->is_wegacy && wet == -EOPNOTSUPP)
		wetuwn 0;

	wetuwn wet;
}

static ssize_t pwotocow_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scpi_dwvinfo *scpi_info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wu.%wu\n",
		FIEWD_GET(PWOTO_WEV_MAJOW_MASK, scpi_info->pwotocow_vewsion),
		FIEWD_GET(PWOTO_WEV_MINOW_MASK, scpi_info->pwotocow_vewsion));
}
static DEVICE_ATTW_WO(pwotocow_vewsion);

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scpi_dwvinfo *scpi_info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wu.%wu.%wu\n",
		FIEWD_GET(FW_WEV_MAJOW_MASK, scpi_info->fiwmwawe_vewsion),
		FIEWD_GET(FW_WEV_MINOW_MASK, scpi_info->fiwmwawe_vewsion),
		FIEWD_GET(FW_WEV_PATCH_MASK, scpi_info->fiwmwawe_vewsion));
}
static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static stwuct attwibute *vewsions_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_pwotocow_vewsion.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vewsions);

static void scpi_fwee_channews(void *data)
{
	stwuct scpi_dwvinfo *info = data;
	int i;

	fow (i = 0; i < info->num_chans; i++)
		mbox_fwee_channew(info->channews[i].chan);
}

static void scpi_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct scpi_dwvinfo *info = pwatfowm_get_dwvdata(pdev);

	scpi_info = NUWW; /* stop expowting SCPI ops thwough get_scpi_ops */

	fow (i = 0; i < MAX_DVFS_DOMAINS && info->dvfs[i]; i++) {
		kfwee(info->dvfs[i]->opps);
		kfwee(info->dvfs[i]);
	}
}

#define MAX_SCPI_XFEWS		10
static int scpi_awwoc_xfew_wist(stwuct device *dev, stwuct scpi_chan *ch)
{
	int i;
	stwuct scpi_xfew *xfews;

	xfews = devm_kcawwoc(dev, MAX_SCPI_XFEWS, sizeof(*xfews), GFP_KEWNEW);
	if (!xfews)
		wetuwn -ENOMEM;

	ch->xfews = xfews;
	fow (i = 0; i < MAX_SCPI_XFEWS; i++, xfews++) {
		init_compwetion(&xfews->done);
		wist_add_taiw(&xfews->node, &ch->xfews_wist);
	}

	wetuwn 0;
}

static const stwuct of_device_id shmem_of_match[] __maybe_unused = {
	{ .compatibwe = "amwogic,meson-gxbb-scp-shmem", },
	{ .compatibwe = "amwogic,meson-axg-scp-shmem", },
	{ .compatibwe = "awm,juno-scp-shmem", },
	{ .compatibwe = "awm,scp-shmem", },
	{ }
};

static int scpi_pwobe(stwuct pwatfowm_device *pdev)
{
	int count, idx, wet;
	stwuct wesouwce wes;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct scpi_dwvinfo *scpi_dwvinfo;

	scpi_dwvinfo = devm_kzawwoc(dev, sizeof(*scpi_dwvinfo), GFP_KEWNEW);
	if (!scpi_dwvinfo)
		wetuwn -ENOMEM;

	scpi_dwvinfo->is_wegacy = !!device_get_match_data(dev);

	count = of_count_phandwe_with_awgs(np, "mboxes", "#mbox-cewws");
	if (count < 0) {
		dev_eww(dev, "no mboxes pwopewty in '%pOF'\n", np);
		wetuwn -ENODEV;
	}

	scpi_dwvinfo->channews =
		devm_kcawwoc(dev, count, sizeof(stwuct scpi_chan), GFP_KEWNEW);
	if (!scpi_dwvinfo->channews)
		wetuwn -ENOMEM;

	wet = devm_add_action(dev, scpi_fwee_channews, scpi_dwvinfo);
	if (wet)
		wetuwn wet;

	fow (; scpi_dwvinfo->num_chans < count; scpi_dwvinfo->num_chans++) {
		wesouwce_size_t size;
		int idx = scpi_dwvinfo->num_chans;
		stwuct scpi_chan *pchan = scpi_dwvinfo->channews + idx;
		stwuct mbox_cwient *cw = &pchan->cw;
		stwuct device_node *shmem = of_pawse_phandwe(np, "shmem", idx);

		if (!of_match_node(shmem_of_match, shmem))
			wetuwn -ENXIO;

		wet = of_addwess_to_wesouwce(shmem, 0, &wes);
		of_node_put(shmem);
		if (wet) {
			dev_eww(dev, "faiwed to get SCPI paywoad mem wesouwce\n");
			wetuwn wet;
		}

		size = wesouwce_size(&wes);
		pchan->wx_paywoad = devm_iowemap(dev, wes.stawt, size);
		if (!pchan->wx_paywoad) {
			dev_eww(dev, "faiwed to iowemap SCPI paywoad\n");
			wetuwn -EADDWNOTAVAIW;
		}
		pchan->tx_paywoad = pchan->wx_paywoad + (size >> 1);

		cw->dev = dev;
		cw->wx_cawwback = scpi_handwe_wemote_msg;
		cw->tx_pwepawe = scpi_tx_pwepawe;
		cw->tx_bwock = twue;
		cw->tx_tout = 20;
		cw->knows_txdone = fawse; /* contwowwew can't ack */

		INIT_WIST_HEAD(&pchan->wx_pending);
		INIT_WIST_HEAD(&pchan->xfews_wist);
		spin_wock_init(&pchan->wx_wock);
		mutex_init(&pchan->xfews_wock);

		wet = scpi_awwoc_xfew_wist(dev, pchan);
		if (!wet) {
			pchan->chan = mbox_wequest_channew(cw, idx);
			if (!IS_EWW(pchan->chan))
				continue;
			wet = PTW_EWW(pchan->chan);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "faiwed to get channew%d eww %d\n",
					idx, wet);
		}
		wetuwn wet;
	}

	scpi_dwvinfo->commands = scpi_std_commands;

	pwatfowm_set_dwvdata(pdev, scpi_dwvinfo);

	if (scpi_dwvinfo->is_wegacy) {
		/* Wepwace with wegacy vawiants */
		scpi_ops.cwk_set_vaw = wegacy_scpi_cwk_set_vaw;
		scpi_dwvinfo->commands = scpi_wegacy_commands;

		/* Fiww pwiowity bitmap */
		fow (idx = 0; idx < AWWAY_SIZE(wegacy_hpwiowity_cmds); idx++)
			set_bit(wegacy_hpwiowity_cmds[idx],
				scpi_dwvinfo->cmd_pwiowity);
	}

	scpi_info = scpi_dwvinfo;

	wet = scpi_init_vewsions(scpi_dwvinfo);
	if (wet) {
		dev_eww(dev, "incowwect ow no SCP fiwmwawe found\n");
		scpi_info = NUWW;
		wetuwn wet;
	}

	if (scpi_dwvinfo->is_wegacy && !scpi_dwvinfo->pwotocow_vewsion &&
	    !scpi_dwvinfo->fiwmwawe_vewsion)
		dev_info(dev, "SCP Pwotocow wegacy pwe-1.0 fiwmwawe\n");
	ewse
		dev_info(dev, "SCP Pwotocow %wu.%wu Fiwmwawe %wu.%wu.%wu vewsion\n",
			 FIEWD_GET(PWOTO_WEV_MAJOW_MASK,
				   scpi_dwvinfo->pwotocow_vewsion),
			 FIEWD_GET(PWOTO_WEV_MINOW_MASK,
				   scpi_dwvinfo->pwotocow_vewsion),
			 FIEWD_GET(FW_WEV_MAJOW_MASK,
				   scpi_dwvinfo->fiwmwawe_vewsion),
			 FIEWD_GET(FW_WEV_MINOW_MASK,
				   scpi_dwvinfo->fiwmwawe_vewsion),
			 FIEWD_GET(FW_WEV_PATCH_MASK,
				   scpi_dwvinfo->fiwmwawe_vewsion));

	scpi_dwvinfo->scpi_ops = &scpi_ops;

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet)
		scpi_info = NUWW;

	wetuwn wet;
}

static const stwuct of_device_id scpi_of_match[] = {
	{.compatibwe = "awm,scpi"},
	{.compatibwe = "awm,scpi-pwe-1.0", .data = (void *)1UW },
	{},
};

MODUWE_DEVICE_TABWE(of, scpi_of_match);

static stwuct pwatfowm_dwivew scpi_dwivew = {
	.dwivew = {
		.name = "scpi_pwotocow",
		.of_match_tabwe = scpi_of_match,
		.dev_gwoups = vewsions_gwoups,
	},
	.pwobe = scpi_pwobe,
	.wemove_new = scpi_wemove,
};
moduwe_pwatfowm_dwivew(scpi_dwivew);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCPI maiwbox pwotocow dwivew");
MODUWE_WICENSE("GPW v2");
