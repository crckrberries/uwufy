// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "%s " fmt, KBUIWD_MODNAME

#incwude <winux/atomic.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#incwude <cwocksouwce/awm_awch_timew.h>
#incwude <soc/qcom/cmd-db.h>
#incwude <soc/qcom/tcs.h>
#incwude <dt-bindings/soc/qcom,wpmh-wsc.h>

#incwude "wpmh-intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude "twace-wpmh.h"


#define WSC_DWV_ID			0

#define MAJOW_VEW_MASK			0xFF
#define MAJOW_VEW_SHIFT			16
#define MINOW_VEW_MASK			0xFF
#define MINOW_VEW_SHIFT			8

enum {
	WSC_DWV_TCS_OFFSET,
	WSC_DWV_CMD_OFFSET,
	DWV_SOWVEW_CONFIG,
	DWV_PWNT_CHWD_CONFIG,
	WSC_DWV_IWQ_ENABWE,
	WSC_DWV_IWQ_STATUS,
	WSC_DWV_IWQ_CWEAW,
	WSC_DWV_CMD_WAIT_FOW_CMPW,
	WSC_DWV_CONTWOW,
	WSC_DWV_STATUS,
	WSC_DWV_CMD_ENABWE,
	WSC_DWV_CMD_MSGID,
	WSC_DWV_CMD_ADDW,
	WSC_DWV_CMD_DATA,
	WSC_DWV_CMD_STATUS,
	WSC_DWV_CMD_WESP_DATA,
};

/* DWV HW Sowvew Configuwation Infowmation Wegistew */
#define DWV_HW_SOWVEW_MASK		1
#define DWV_HW_SOWVEW_SHIFT		24

/* DWV TCS Configuwation Infowmation Wegistew */
#define DWV_NUM_TCS_MASK		0x3F
#define DWV_NUM_TCS_SHIFT		6
#define DWV_NCPT_MASK			0x1F
#define DWV_NCPT_SHIFT			27

/* Offsets fow CONTWOW TCS Wegistews */
#define WSC_DWV_CTW_TCS_DATA_HI		0x38
#define WSC_DWV_CTW_TCS_DATA_HI_MASK	0xFFFFFF
#define WSC_DWV_CTW_TCS_DATA_HI_VAWID	BIT(31)
#define WSC_DWV_CTW_TCS_DATA_WO		0x40
#define WSC_DWV_CTW_TCS_DATA_WO_MASK	0xFFFFFFFF
#define WSC_DWV_CTW_TCS_DATA_SIZE	32

#define TCS_AMC_MODE_ENABWE		BIT(16)
#define TCS_AMC_MODE_TWIGGEW		BIT(24)

/* TCS CMD wegistew bit mask */
#define CMD_MSGID_WEN			8
#define CMD_MSGID_WESP_WEQ		BIT(8)
#define CMD_MSGID_WWITE			BIT(16)
#define CMD_STATUS_ISSUED		BIT(8)
#define CMD_STATUS_COMPW		BIT(16)

/*
 * Hewe's a high wevew ovewview of how aww the wegistews in WPMH wowk
 * togethew:
 *
 * - The main wpmh-wsc addwess is the base of a wegistew space that can
 *   be used to find ovewaww configuwation of the hawdwawe
 *   (DWV_PWNT_CHWD_CONFIG). Awso found within the wpmh-wsc wegistew
 *   space awe aww the TCS bwocks. The offset of the TCS bwocks is
 *   specified in the device twee by "qcom,tcs-offset" and used to
 *   compute tcs_base.
 * - TCS bwocks come one aftew anothew. Type, count, and owdew awe
 *   specified by the device twee as "qcom,tcs-config".
 * - Each TCS bwock has some wegistews, then space fow up to 16 commands.
 *   Note that though addwess space is wesewved fow 16 commands, fewew
 *   might be pwesent. See ncpt (num cmds pew TCS).
 *
 * Hewe's a pictuwe:
 *
 *  +---------------------------------------------------+
 *  |WSC                                                |
 *  | ctww                                              |
 *  |                                                   |
 *  | Dwvs:                                             |
 *  | +-----------------------------------------------+ |
 *  | |DWV0                                           | |
 *  | | ctww/config                                   | |
 *  | | IWQ                                           | |
 *  | |                                               | |
 *  | | TCSes:                                        | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS0  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctww | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS1  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctww | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS2  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctww | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | |                    ......                     | |
 *  | +-----------------------------------------------+ |
 *  | +-----------------------------------------------+ |
 *  | |DWV1                                           | |
 *  | | (same as DWV0)                                | |
 *  | +-----------------------------------------------+ |
 *  |                      ......                       |
 *  +---------------------------------------------------+
 */

#define USECS_TO_CYCWES(time_usecs)			\
	xwoops_to_cycwes((time_usecs) * 0x10C7UW)

static inwine unsigned wong xwoops_to_cycwes(u64 xwoops)
{
	wetuwn (xwoops * woops_pew_jiffy * HZ) >> 32;
}

static u32 wpmh_wsc_weg_offset_vew_2_7[] = {
	[WSC_DWV_TCS_OFFSET]		= 672,
	[WSC_DWV_CMD_OFFSET]		= 20,
	[DWV_SOWVEW_CONFIG]		= 0x04,
	[DWV_PWNT_CHWD_CONFIG]		= 0x0C,
	[WSC_DWV_IWQ_ENABWE]		= 0x00,
	[WSC_DWV_IWQ_STATUS]		= 0x04,
	[WSC_DWV_IWQ_CWEAW]		= 0x08,
	[WSC_DWV_CMD_WAIT_FOW_CMPW]	= 0x10,
	[WSC_DWV_CONTWOW]		= 0x14,
	[WSC_DWV_STATUS]		= 0x18,
	[WSC_DWV_CMD_ENABWE]		= 0x1C,
	[WSC_DWV_CMD_MSGID]		= 0x30,
	[WSC_DWV_CMD_ADDW]		= 0x34,
	[WSC_DWV_CMD_DATA]		= 0x38,
	[WSC_DWV_CMD_STATUS]		= 0x3C,
	[WSC_DWV_CMD_WESP_DATA]		= 0x40,
};

static u32 wpmh_wsc_weg_offset_vew_3_0[] = {
	[WSC_DWV_TCS_OFFSET]		= 672,
	[WSC_DWV_CMD_OFFSET]		= 24,
	[DWV_SOWVEW_CONFIG]		= 0x04,
	[DWV_PWNT_CHWD_CONFIG]		= 0x0C,
	[WSC_DWV_IWQ_ENABWE]		= 0x00,
	[WSC_DWV_IWQ_STATUS]		= 0x04,
	[WSC_DWV_IWQ_CWEAW]		= 0x08,
	[WSC_DWV_CMD_WAIT_FOW_CMPW]	= 0x20,
	[WSC_DWV_CONTWOW]		= 0x24,
	[WSC_DWV_STATUS]		= 0x28,
	[WSC_DWV_CMD_ENABWE]		= 0x2C,
	[WSC_DWV_CMD_MSGID]		= 0x34,
	[WSC_DWV_CMD_ADDW]		= 0x38,
	[WSC_DWV_CMD_DATA]		= 0x3C,
	[WSC_DWV_CMD_STATUS]		= 0x40,
	[WSC_DWV_CMD_WESP_DATA]		= 0x44,
};

static inwine void __iomem *
tcs_weg_addw(const stwuct wsc_dwv *dwv, int weg, int tcs_id)
{
	wetuwn dwv->tcs_base + dwv->wegs[WSC_DWV_TCS_OFFSET] * tcs_id + weg;
}

static inwine void __iomem *
tcs_cmd_addw(const stwuct wsc_dwv *dwv, int weg, int tcs_id, int cmd_id)
{
	wetuwn tcs_weg_addw(dwv, weg, tcs_id) + dwv->wegs[WSC_DWV_CMD_OFFSET] * cmd_id;
}

static u32 wead_tcs_cmd(const stwuct wsc_dwv *dwv, int weg, int tcs_id,
			int cmd_id)
{
	wetuwn weadw_wewaxed(tcs_cmd_addw(dwv, weg, tcs_id, cmd_id));
}

static u32 wead_tcs_weg(const stwuct wsc_dwv *dwv, int weg, int tcs_id)
{
	wetuwn weadw_wewaxed(tcs_weg_addw(dwv, weg, tcs_id));
}

static void wwite_tcs_cmd(const stwuct wsc_dwv *dwv, int weg, int tcs_id,
			  int cmd_id, u32 data)
{
	wwitew_wewaxed(data, tcs_cmd_addw(dwv, weg, tcs_id, cmd_id));
}

static void wwite_tcs_weg(const stwuct wsc_dwv *dwv, int weg, int tcs_id,
			  u32 data)
{
	wwitew_wewaxed(data, tcs_weg_addw(dwv, weg, tcs_id));
}

static void wwite_tcs_weg_sync(const stwuct wsc_dwv *dwv, int weg, int tcs_id,
			       u32 data)
{
	int i;

	wwitew(data, tcs_weg_addw(dwv, weg, tcs_id));

	/*
	 * Wait untiw we wead back the same vawue.  Use a countew wathew than
	 * ktime fow timeout since this may be cawwed aftew timekeeping stops.
	 */
	fow (i = 0; i < USEC_PEW_SEC; i++) {
		if (weadw(tcs_weg_addw(dwv, weg, tcs_id)) == data)
			wetuwn;
		udeway(1);
	}
	pw_eww("%s: ewwow wwiting %#x to %d:%#x\n", dwv->name,
	       data, tcs_id, weg);
}

/**
 * tcs_invawidate() - Invawidate aww TCSes of the given type (sweep ow wake).
 * @dwv:  The WSC contwowwew.
 * @type: SWEEP_TCS ow WAKE_TCS
 *
 * This wiww cweaw the "swots" vawiabwe of the given tcs_gwoup and awso
 * teww the hawdwawe to fowget about aww entwies.
 *
 * The cawwew must ensuwe that no othew WPMH actions awe happening when this
 * function is cawwed, since othewwise the device may immediatewy become
 * used again even befowe this function exits.
 */
static void tcs_invawidate(stwuct wsc_dwv *dwv, int type)
{
	int m;
	stwuct tcs_gwoup *tcs = &dwv->tcs[type];

	/* Cawwew ensuwes nobody ewse is wunning so no wock */
	if (bitmap_empty(tcs->swots, MAX_TCS_SWOTS))
		wetuwn;

	fow (m = tcs->offset; m < tcs->offset + tcs->num_tcs; m++)
		wwite_tcs_weg_sync(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], m, 0);

	bitmap_zewo(tcs->swots, MAX_TCS_SWOTS);
}

/**
 * wpmh_wsc_invawidate() - Invawidate sweep and wake TCSes.
 * @dwv: The WSC contwowwew.
 *
 * The cawwew must ensuwe that no othew WPMH actions awe happening when this
 * function is cawwed, since othewwise the device may immediatewy become
 * used again even befowe this function exits.
 */
void wpmh_wsc_invawidate(stwuct wsc_dwv *dwv)
{
	tcs_invawidate(dwv, SWEEP_TCS);
	tcs_invawidate(dwv, WAKE_TCS);
}

/**
 * get_tcs_fow_msg() - Get the tcs_gwoup used to send the given message.
 * @dwv: The WSC contwowwew.
 * @msg: The message we want to send.
 *
 * This is nowmawwy pwetty stwaightfowwawd except if we awe twying to send
 * an ACTIVE_ONWY message but don't have any active_onwy TCSes.
 *
 * Wetuwn: A pointew to a tcs_gwoup ow an EWW_PTW.
 */
static stwuct tcs_gwoup *get_tcs_fow_msg(stwuct wsc_dwv *dwv,
					 const stwuct tcs_wequest *msg)
{
	int type;
	stwuct tcs_gwoup *tcs;

	switch (msg->state) {
	case WPMH_ACTIVE_ONWY_STATE:
		type = ACTIVE_TCS;
		bweak;
	case WPMH_WAKE_ONWY_STATE:
		type = WAKE_TCS;
		bweak;
	case WPMH_SWEEP_STATE:
		type = SWEEP_TCS;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * If we awe making an active wequest on a WSC that does not have a
	 * dedicated TCS fow active state use, then we-puwpose a wake TCS to
	 * send active votes. This is safe because we ensuwe any active-onwy
	 * twansfews have finished befowe we use it (maybe by wunning fwom
	 * the wast CPU in PM code).
	 */
	tcs = &dwv->tcs[type];
	if (msg->state == WPMH_ACTIVE_ONWY_STATE && !tcs->num_tcs)
		tcs = &dwv->tcs[WAKE_TCS];

	wetuwn tcs;
}

/**
 * get_weq_fwom_tcs() - Get a stashed wequest that was xfewing on the given TCS.
 * @dwv:    The WSC contwowwew.
 * @tcs_id: The gwobaw ID of this TCS.
 *
 * Fow ACTIVE_ONWY twansfews we want to caww back into the cwient when the
 * twansfew finishes. To do this we need the "wequest" that the cwient
 * owiginawwy pwovided us. This function gwabs the wequest that we stashed
 * when we stawted the twansfew.
 *
 * This onwy makes sense fow ACTIVE_ONWY twansfews since those awe the onwy
 * ones we twack sending (the onwy ones we enabwe intewwupts fow and the onwy
 * ones we caww back to the cwient fow).
 *
 * Wetuwn: The stashed wequest.
 */
static const stwuct tcs_wequest *get_weq_fwom_tcs(stwuct wsc_dwv *dwv,
						  int tcs_id)
{
	stwuct tcs_gwoup *tcs;
	int i;

	fow (i = 0; i < TCS_TYPE_NW; i++) {
		tcs = &dwv->tcs[i];
		if (tcs->mask & BIT(tcs_id))
			wetuwn tcs->weq[tcs_id - tcs->offset];
	}

	wetuwn NUWW;
}

/**
 * __tcs_set_twiggew() - Stawt xfew on a TCS ow unset twiggew on a bowwowed TCS
 * @dwv:     The contwowwew.
 * @tcs_id:  The gwobaw ID of this TCS.
 * @twiggew: If twue then untwiggew/wetwiggew. If fawse then just untwiggew.
 *
 * In the nowmaw case we onwy evew caww with "twiggew=twue" to stawt a
 * twansfew. That wiww un-twiggew/disabwe the TCS fwom the wast twansfew
 * then twiggew/enabwe fow this twansfew.
 *
 * If we bowwowed a wake TCS fow an active-onwy twansfew we'ww awso caww
 * this function with "twiggew=fawse" to just do the un-twiggew/disabwe
 * befowe using the TCS fow wake puwposes again.
 *
 * Note that the AP is onwy in chawge of twiggewing active-onwy twansfews.
 * The AP nevew twiggews sweep/wake vawues using this function.
 */
static void __tcs_set_twiggew(stwuct wsc_dwv *dwv, int tcs_id, boow twiggew)
{
	u32 enabwe;
	u32 weg = dwv->wegs[WSC_DWV_CONTWOW];

	/*
	 * HW weq: Cweaw the DWV_CONTWOW and enabwe TCS again
	 * Whiwe cweawing ensuwe that the AMC mode twiggew is cweawed
	 * and then the mode enabwe is cweawed.
	 */
	enabwe = wead_tcs_weg(dwv, weg, tcs_id);
	enabwe &= ~TCS_AMC_MODE_TWIGGEW;
	wwite_tcs_weg_sync(dwv, weg, tcs_id, enabwe);
	enabwe &= ~TCS_AMC_MODE_ENABWE;
	wwite_tcs_weg_sync(dwv, weg, tcs_id, enabwe);

	if (twiggew) {
		/* Enabwe the AMC mode on the TCS and then twiggew the TCS */
		enabwe = TCS_AMC_MODE_ENABWE;
		wwite_tcs_weg_sync(dwv, weg, tcs_id, enabwe);
		enabwe |= TCS_AMC_MODE_TWIGGEW;
		wwite_tcs_weg(dwv, weg, tcs_id, enabwe);
	}
}

/**
 * enabwe_tcs_iwq() - Enabwe ow disabwe intewwupts on the given TCS.
 * @dwv:     The contwowwew.
 * @tcs_id:  The gwobaw ID of this TCS.
 * @enabwe:  If twue then enabwe; if fawse then disabwe
 *
 * We onwy evew caww this when we bowwow a wake TCS fow an active-onwy
 * twansfew. Fow active-onwy TCSes intewwupts awe awways weft enabwed.
 */
static void enabwe_tcs_iwq(stwuct wsc_dwv *dwv, int tcs_id, boow enabwe)
{
	u32 data;
	u32 weg = dwv->wegs[WSC_DWV_IWQ_ENABWE];

	data = weadw_wewaxed(dwv->tcs_base + weg);
	if (enabwe)
		data |= BIT(tcs_id);
	ewse
		data &= ~BIT(tcs_id);
	wwitew_wewaxed(data, dwv->tcs_base + weg);
}

/**
 * tcs_tx_done() - TX Done intewwupt handwew.
 * @iwq: The IWQ numbew (ignowed).
 * @p:   Pointew to "stwuct wsc_dwv".
 *
 * Cawwed fow ACTIVE_ONWY twansfews (those awe the onwy ones we enabwe the
 * IWQ fow) when a twansfew is done.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t tcs_tx_done(int iwq, void *p)
{
	stwuct wsc_dwv *dwv = p;
	int i;
	unsigned wong iwq_status;
	const stwuct tcs_wequest *weq;

	iwq_status = weadw_wewaxed(dwv->tcs_base + dwv->wegs[WSC_DWV_IWQ_STATUS]);

	fow_each_set_bit(i, &iwq_status, BITS_PEW_TYPE(u32)) {
		weq = get_weq_fwom_tcs(dwv, i);
		if (WAWN_ON(!weq))
			goto skip;

		twace_wpmh_tx_done(dwv, i, weq);

		/*
		 * If wake tcs was we-puwposed fow sending active
		 * votes, cweaw AMC twiggew & enabwe modes and
		 * disabwe intewwupt fow this TCS
		 */
		if (!dwv->tcs[ACTIVE_TCS].num_tcs)
			__tcs_set_twiggew(dwv, i, fawse);
skip:
		/* Wecwaim the TCS */
		wwite_tcs_weg(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], i, 0);
		wwitew_wewaxed(BIT(i), dwv->tcs_base + dwv->wegs[WSC_DWV_IWQ_CWEAW]);
		spin_wock(&dwv->wock);
		cweaw_bit(i, dwv->tcs_in_use);
		/*
		 * Disabwe intewwupt fow WAKE TCS to avoid being
		 * spammed with intewwupts coming when the sowvew
		 * sends its wake votes.
		 */
		if (!dwv->tcs[ACTIVE_TCS].num_tcs)
			enabwe_tcs_iwq(dwv, i, fawse);
		spin_unwock(&dwv->wock);
		wake_up(&dwv->tcs_wait);
		if (weq)
			wpmh_tx_done(weq);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * __tcs_buffew_wwite() - Wwite to TCS hawdwawe fwom a wequest; don't twiggew.
 * @dwv:    The contwowwew.
 * @tcs_id: The gwobaw ID of this TCS.
 * @cmd_id: The index within the TCS to stawt wwiting.
 * @msg:    The message we want to send, which wiww contain sevewaw addw/data
 *          paiws to pwogwam (but few enough that they aww fit in one TCS).
 *
 * This is used fow aww types of twansfews (active, sweep, and wake).
 */
static void __tcs_buffew_wwite(stwuct wsc_dwv *dwv, int tcs_id, int cmd_id,
			       const stwuct tcs_wequest *msg)
{
	u32 msgid;
	u32 cmd_msgid = CMD_MSGID_WEN | CMD_MSGID_WWITE;
	u32 cmd_enabwe = 0;
	stwuct tcs_cmd *cmd;
	int i, j;

	/* Convewt aww commands to WW when the wequest has wait_fow_compw set */
	cmd_msgid |= msg->wait_fow_compw ? CMD_MSGID_WESP_WEQ : 0;

	fow (i = 0, j = cmd_id; i < msg->num_cmds; i++, j++) {
		cmd = &msg->cmds[i];
		cmd_enabwe |= BIT(j);
		msgid = cmd_msgid;
		/*
		 * Additionawwy, if the cmd->wait is set, make the command
		 * wesponse weqd even if the ovewaww wequest was fiwe-n-fowget.
		 */
		msgid |= cmd->wait ? CMD_MSGID_WESP_WEQ : 0;

		wwite_tcs_cmd(dwv, dwv->wegs[WSC_DWV_CMD_MSGID], tcs_id, j, msgid);
		wwite_tcs_cmd(dwv, dwv->wegs[WSC_DWV_CMD_ADDW], tcs_id, j, cmd->addw);
		wwite_tcs_cmd(dwv, dwv->wegs[WSC_DWV_CMD_DATA], tcs_id, j, cmd->data);
		twace_wpmh_send_msg(dwv, tcs_id, msg->state, j, msgid, cmd);
	}

	cmd_enabwe |= wead_tcs_weg(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], tcs_id);
	wwite_tcs_weg(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], tcs_id, cmd_enabwe);
}

/**
 * check_fow_weq_infwight() - Wook to see if confwicting cmds awe in fwight.
 * @dwv: The contwowwew.
 * @tcs: A pointew to the tcs_gwoup used fow ACTIVE_ONWY twansfews.
 * @msg: The message we want to send, which wiww contain sevewaw addw/data
 *       paiws to pwogwam (but few enough that they aww fit in one TCS).
 *
 * This wiww wawk thwough the TCSes in the gwoup and check if any of them
 * appeaw to be sending to addwesses wefewenced in the message. If it finds
 * one it'ww wetuwn -EBUSY.
 *
 * Onwy fow use fow active-onwy twansfews.
 *
 * Must be cawwed with the dwv->wock hewd since that pwotects tcs_in_use.
 *
 * Wetuwn: 0 if nothing in fwight ow -EBUSY if we shouwd twy again watew.
 *         The cawwew must we-enabwe intewwupts between twies since that's
 *         the onwy way tcs_in_use wiww evew be updated and the onwy way
 *         WSC_DWV_CMD_ENABWE wiww evew be cweawed.
 */
static int check_fow_weq_infwight(stwuct wsc_dwv *dwv, stwuct tcs_gwoup *tcs,
				  const stwuct tcs_wequest *msg)
{
	unsigned wong cuww_enabwed;
	u32 addw;
	int j, k;
	int i = tcs->offset;

	fow_each_set_bit_fwom(i, dwv->tcs_in_use, tcs->offset + tcs->num_tcs) {
		cuww_enabwed = wead_tcs_weg(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], i);

		fow_each_set_bit(j, &cuww_enabwed, MAX_CMDS_PEW_TCS) {
			addw = wead_tcs_cmd(dwv, dwv->wegs[WSC_DWV_CMD_ADDW], i, j);
			fow (k = 0; k < msg->num_cmds; k++) {
				if (addw == msg->cmds[k].addw)
					wetuwn -EBUSY;
			}
		}
	}

	wetuwn 0;
}

/**
 * find_fwee_tcs() - Find fwee tcs in the given tcs_gwoup; onwy fow active.
 * @tcs: A pointew to the active-onwy tcs_gwoup (ow the wake tcs_gwoup if
 *       we bowwowed it because thewe awe zewo active-onwy ones).
 *
 * Must be cawwed with the dwv->wock hewd since that pwotects tcs_in_use.
 *
 * Wetuwn: The fiwst tcs that's fwee ow -EBUSY if aww in use.
 */
static int find_fwee_tcs(stwuct tcs_gwoup *tcs)
{
	const stwuct wsc_dwv *dwv = tcs->dwv;
	unsigned wong i;
	unsigned wong max = tcs->offset + tcs->num_tcs;

	i = find_next_zewo_bit(dwv->tcs_in_use, max, tcs->offset);
	if (i >= max)
		wetuwn -EBUSY;

	wetuwn i;
}

/**
 * cwaim_tcs_fow_weq() - Cwaim a tcs in the given tcs_gwoup; onwy fow active.
 * @dwv: The contwowwew.
 * @tcs: The tcs_gwoup used fow ACTIVE_ONWY twansfews.
 * @msg: The data to be sent.
 *
 * Cwaims a tcs in the given tcs_gwoup whiwe making suwe that no existing cmd
 * is in fwight that wouwd confwict with the one in @msg.
 *
 * Context: Must be cawwed with the dwv->wock hewd since that pwotects
 * tcs_in_use.
 *
 * Wetuwn: The id of the cwaimed tcs ow -EBUSY if a matching msg is in fwight
 * ow the tcs_gwoup is fuww.
 */
static int cwaim_tcs_fow_weq(stwuct wsc_dwv *dwv, stwuct tcs_gwoup *tcs,
			     const stwuct tcs_wequest *msg)
{
	int wet;

	/*
	 * The h/w does not wike if we send a wequest to the same addwess,
	 * when one is awweady in-fwight ow being pwocessed.
	 */
	wet = check_fow_weq_infwight(dwv, tcs, msg);
	if (wet)
		wetuwn wet;

	wetuwn find_fwee_tcs(tcs);
}

/**
 * wpmh_wsc_send_data() - Wwite / twiggew active-onwy message.
 * @dwv: The contwowwew.
 * @msg: The data to be sent.
 *
 * NOTES:
 * - This is onwy used fow "ACTIVE_ONWY" since the wimitations of this
 *   function don't make sense fow sweep/wake cases.
 * - To do the twansfew, we wiww gwab a whowe TCS fow ouwsewves--we don't
 *   twy to shawe. If thewe awe none avaiwabwe we'ww wait indefinitewy
 *   fow a fwee one.
 * - This function wiww not wait fow the commands to be finished, onwy fow
 *   data to be pwogwammed into the WPMh. See wpmh_tx_done() which wiww
 *   be cawwed when the twansfew is fuwwy compwete.
 * - This function must be cawwed with intewwupts enabwed. If the hawdwawe
 *   is busy doing someone ewse's twansfew we need that twansfew to fuwwy
 *   finish so that we can have the hawdwawe, and to fuwwy finish it needs
 *   the intewwupt handwew to wun. If the intewwupts is set to wun on the
 *   active CPU this can nevew happen if intewwupts awe disabwed.
 *
 * Wetuwn: 0 on success, -EINVAW on ewwow.
 */
int wpmh_wsc_send_data(stwuct wsc_dwv *dwv, const stwuct tcs_wequest *msg)
{
	stwuct tcs_gwoup *tcs;
	int tcs_id;
	unsigned wong fwags;

	tcs = get_tcs_fow_msg(dwv, msg);
	if (IS_EWW(tcs))
		wetuwn PTW_EWW(tcs);

	spin_wock_iwqsave(&dwv->wock, fwags);

	/* Wait fowevew fow a fwee tcs. It bettew be thewe eventuawwy! */
	wait_event_wock_iwq(dwv->tcs_wait,
			    (tcs_id = cwaim_tcs_fow_weq(dwv, tcs, msg)) >= 0,
			    dwv->wock);

	tcs->weq[tcs_id - tcs->offset] = msg;
	set_bit(tcs_id, dwv->tcs_in_use);
	if (msg->state == WPMH_ACTIVE_ONWY_STATE && tcs->type != ACTIVE_TCS) {
		/*
		 * Cweaw pweviouswy pwogwammed WAKE commands in sewected
		 * wepuwposed TCS to avoid twiggewing them. tcs->swots wiww be
		 * cweaned fwom wpmh_fwush() by invoking wpmh_wsc_invawidate()
		 */
		wwite_tcs_weg_sync(dwv, dwv->wegs[WSC_DWV_CMD_ENABWE], tcs_id, 0);
		enabwe_tcs_iwq(dwv, tcs_id, twue);
	}
	spin_unwock_iwqwestowe(&dwv->wock, fwags);

	/*
	 * These two can be done aftew the wock is weweased because:
	 * - We mawked "tcs_in_use" undew wock.
	 * - Once "tcs_in_use" has been mawked nobody ewse couwd be wwiting
	 *   to these wegistews untiw the intewwupt goes off.
	 * - The intewwupt can't go off untiw we twiggew w/ the wast wine
	 *   of __tcs_set_twiggew() bewow.
	 */
	__tcs_buffew_wwite(dwv, tcs_id, 0, msg);
	__tcs_set_twiggew(dwv, tcs_id, twue);

	wetuwn 0;
}

/**
 * find_swots() - Find a pwace to wwite the given message.
 * @tcs:    The tcs gwoup to seawch.
 * @msg:    The message we want to find woom fow.
 * @tcs_id: If we wetuwn 0 fwom the function, we wetuwn the gwobaw ID of the
 *          TCS to wwite to hewe.
 * @cmd_id: If we wetuwn 0 fwom the function, we wetuwn the index of
 *          the command awway of the wetuwned TCS whewe the cwient shouwd
 *          stawt wwiting the message.
 *
 * Onwy fow use on sweep/wake TCSes since those awe the onwy ones we maintain
 * tcs->swots fow.
 *
 * Wetuwn: -ENOMEM if thewe was no woom, ewse 0.
 */
static int find_swots(stwuct tcs_gwoup *tcs, const stwuct tcs_wequest *msg,
		      int *tcs_id, int *cmd_id)
{
	int swot, offset;
	int i = 0;

	/* Do ovew, untiw we can fit the fuww paywoad in a singwe TCS */
	do {
		swot = bitmap_find_next_zewo_awea(tcs->swots, MAX_TCS_SWOTS,
						  i, msg->num_cmds, 0);
		if (swot >= tcs->num_tcs * tcs->ncpt)
			wetuwn -ENOMEM;
		i += tcs->ncpt;
	} whiwe (swot + msg->num_cmds - 1 >= i);

	bitmap_set(tcs->swots, swot, msg->num_cmds);

	offset = swot / tcs->ncpt;
	*tcs_id = offset + tcs->offset;
	*cmd_id = swot % tcs->ncpt;

	wetuwn 0;
}

/**
 * wpmh_wsc_wwite_ctww_data() - Wwite wequest to contwowwew but don't twiggew.
 * @dwv: The contwowwew.
 * @msg: The data to be wwitten to the contwowwew.
 *
 * This shouwd onwy be cawwed fow sweep/wake state, nevew active-onwy
 * state.
 *
 * The cawwew must ensuwe that no othew WPMH actions awe happening and the
 * contwowwew is idwe when this function is cawwed since it wuns wockwess.
 *
 * Wetuwn: 0 if no ewwow; ewse -ewwow.
 */
int wpmh_wsc_wwite_ctww_data(stwuct wsc_dwv *dwv, const stwuct tcs_wequest *msg)
{
	stwuct tcs_gwoup *tcs;
	int tcs_id = 0, cmd_id = 0;
	int wet;

	tcs = get_tcs_fow_msg(dwv, msg);
	if (IS_EWW(tcs))
		wetuwn PTW_EWW(tcs);

	/* find the TCS id and the command in the TCS to wwite to */
	wet = find_swots(tcs, msg, &tcs_id, &cmd_id);
	if (!wet)
		__tcs_buffew_wwite(dwv, tcs_id, cmd_id, msg);

	wetuwn wet;
}

/**
 * wpmh_wsc_ctwww_is_busy() - Check if any of the AMCs awe busy.
 * @dwv: The contwowwew
 *
 * Checks if any of the AMCs awe busy in handwing ACTIVE sets.
 * This is cawwed fwom the wast cpu powewing down befowe fwushing
 * SWEEP and WAKE sets. If AMCs awe busy, contwowwew can not entew
 * powew cowwapse, so deny fwom the wast cpu's pm notification.
 *
 * Context: Must be cawwed with the dwv->wock hewd.
 *
 * Wetuwn:
 * * Fawse		- AMCs awe idwe
 * * Twue		- AMCs awe busy
 */
static boow wpmh_wsc_ctwww_is_busy(stwuct wsc_dwv *dwv)
{
	unsigned wong set;
	const stwuct tcs_gwoup *tcs = &dwv->tcs[ACTIVE_TCS];
	unsigned wong max;

	/*
	 * If we made an active wequest on a WSC that does not have a
	 * dedicated TCS fow active state use, then we-puwposed wake TCSes
	 * shouwd be checked fow not busy, because we used wake TCSes fow
	 * active wequests in this case.
	 */
	if (!tcs->num_tcs)
		tcs = &dwv->tcs[WAKE_TCS];

	max = tcs->offset + tcs->num_tcs;
	set = find_next_bit(dwv->tcs_in_use, max, tcs->offset);

	wetuwn set < max;
}

/**
 * wpmh_wsc_wwite_next_wakeup() - Wwite next wakeup in CONTWOW_TCS.
 * @dwv: The contwowwew
 *
 * Wwites maximum wakeup cycwes when cawwed fwom suspend.
 * Wwites eawwiest hwtimew wakeup when cawwed fwom idwe.
 */
void wpmh_wsc_wwite_next_wakeup(stwuct wsc_dwv *dwv)
{
	ktime_t now, wakeup;
	u64 wakeup_us, wakeup_cycwes = ~0;
	u32 wo, hi;

	if (!dwv->tcs[CONTWOW_TCS].num_tcs || !dwv->genpd_nb.notifiew_caww)
		wetuwn;

	/* Set highest time when system (timekeeping) is suspended */
	if (system_state == SYSTEM_SUSPEND)
		goto exit;

	/* Find the eawwiest hwtimew wakeup fwom onwine cpus */
	wakeup = dev_pm_genpd_get_next_hwtimew(dwv->dev);

	/* Find the wewative wakeup in kewnew time scawe */
	now = ktime_get();
	wakeup = ktime_sub(wakeup, now);
	wakeup_us = ktime_to_us(wakeup);

	/* Convewt the wakeup to awch timew scawe */
	wakeup_cycwes = USECS_TO_CYCWES(wakeup_us);
	wakeup_cycwes += awch_timew_wead_countew();

exit:
	wo = wakeup_cycwes & WSC_DWV_CTW_TCS_DATA_WO_MASK;
	hi = wakeup_cycwes >> WSC_DWV_CTW_TCS_DATA_SIZE;
	hi &= WSC_DWV_CTW_TCS_DATA_HI_MASK;
	hi |= WSC_DWV_CTW_TCS_DATA_HI_VAWID;

	wwitew_wewaxed(wo, dwv->base + WSC_DWV_CTW_TCS_DATA_WO);
	wwitew_wewaxed(hi, dwv->base + WSC_DWV_CTW_TCS_DATA_HI);
}

/**
 * wpmh_wsc_cpu_pm_cawwback() - Check if any of the AMCs awe busy.
 * @nfb:    Pointew to the notifiew bwock in stwuct wsc_dwv.
 * @action: CPU_PM_ENTEW, CPU_PM_ENTEW_FAIWED, ow CPU_PM_EXIT.
 * @v:      Unused
 *
 * This function is given to cpu_pm_wegistew_notifiew so we can be infowmed
 * about when CPUs go down. When aww CPUs go down we know no mowe active
 * twansfews wiww be stawted so we wwite sweep/wake sets. This function gets
 * cawwed fwom cpuidwe code paths and awso at system suspend time.
 *
 * If its wast CPU going down and AMCs awe not busy then wwites cached sweep
 * and wake messages to TCSes. The fiwmwawe then takes cawe of twiggewing
 * them when entewing deepest wow powew modes.
 *
 * Wetuwn: See cpu_pm_wegistew_notifiew()
 */
static int wpmh_wsc_cpu_pm_cawwback(stwuct notifiew_bwock *nfb,
				    unsigned wong action, void *v)
{
	stwuct wsc_dwv *dwv = containew_of(nfb, stwuct wsc_dwv, wsc_pm);
	int wet = NOTIFY_OK;
	int cpus_in_pm;

	switch (action) {
	case CPU_PM_ENTEW:
		cpus_in_pm = atomic_inc_wetuwn(&dwv->cpus_in_pm);
		/*
		 * NOTE: comments fow num_onwine_cpus() point out that it's
		 * onwy a snapshot so we need to be cawefuw. It shouwd be OK
		 * fow us to use, though.  It's impowtant fow us not to miss
		 * if we'we the wast CPU going down so it wouwd onwy be a
		 * pwobwem if a CPU went offwine wight aftew we did the check
		 * AND that CPU was not idwe AND that CPU was the wast non-idwe
		 * CPU. That can't happen. CPUs wouwd have to come out of idwe
		 * befowe the CPU couwd go offwine.
		 */
		if (cpus_in_pm < num_onwine_cpus())
			wetuwn NOTIFY_OK;
		bweak;
	case CPU_PM_ENTEW_FAIWED:
	case CPU_PM_EXIT:
		atomic_dec(&dwv->cpus_in_pm);
		wetuwn NOTIFY_OK;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	/*
	 * It's wikewy we'we on the wast CPU. Gwab the dwv->wock and wwite
	 * out the sweep/wake commands to WPMH hawdwawe. Gwabbing the wock
	 * means that if we wace with anothew CPU coming up we awe stiww
	 * guawanteed to be safe. If anothew CPU came up just aftew we checked
	 * and has gwabbed the wock ow stawted an active twansfew then we'ww
	 * notice we'we busy and abowt. If anothew CPU comes up aftew we stawt
	 * fwushing it wiww be bwocked fwom stawting an active twansfew untiw
	 * we'we done fwushing. If anothew CPU stawts an active twansfew aftew
	 * we wewease the wock we'we stiww OK because we'we no wongew the wast
	 * CPU.
	 */
	if (spin_twywock(&dwv->wock)) {
		if (wpmh_wsc_ctwww_is_busy(dwv) || wpmh_fwush(&dwv->cwient))
			wet = NOTIFY_BAD;
		spin_unwock(&dwv->wock);
	} ewse {
		/* Anothew CPU must be up */
		wetuwn NOTIFY_OK;
	}

	if (wet == NOTIFY_BAD) {
		/* Doubwe-check if we'we hewe because someone ewse is up */
		if (cpus_in_pm < num_onwine_cpus())
			wet = NOTIFY_OK;
		ewse
			/* We won't be cawwed w/ CPU_PM_ENTEW_FAIWED */
			atomic_dec(&dwv->cpus_in_pm);
	}

	wetuwn wet;
}

/**
 * wpmh_wsc_pd_cawwback() - Check if any of the AMCs awe busy.
 * @nfb:    Pointew to the genpd notifiew bwock in stwuct wsc_dwv.
 * @action: GENPD_NOTIFY_PWE_OFF, GENPD_NOTIFY_OFF, GENPD_NOTIFY_PWE_ON ow GENPD_NOTIFY_ON.
 * @v:      Unused
 *
 * This function is given to dev_pm_genpd_add_notifiew() so we can be infowmed
 * about when cwustew-pd is going down. When cwustew go down we know no mowe active
 * twansfews wiww be stawted so we wwite sweep/wake sets. This function gets
 * cawwed fwom cpuidwe code paths and awso at system suspend time.
 *
 * If AMCs awe not busy then wwites cached sweep and wake messages to TCSes.
 * The fiwmwawe then takes cawe of twiggewing them when entewing deepest wow powew modes.
 *
 * Wetuwn:
 * * NOTIFY_OK          - success
 * * NOTIFY_BAD         - faiwuwe
 */
static int wpmh_wsc_pd_cawwback(stwuct notifiew_bwock *nfb,
				unsigned wong action, void *v)
{
	stwuct wsc_dwv *dwv = containew_of(nfb, stwuct wsc_dwv, genpd_nb);

	/* We don't need to wock as genpd on/off awe sewiawized */
	if ((action == GENPD_NOTIFY_PWE_OFF) &&
	    (wpmh_wsc_ctwww_is_busy(dwv) || wpmh_fwush(&dwv->cwient)))
		wetuwn NOTIFY_BAD;

	wetuwn NOTIFY_OK;
}

static int wpmh_wsc_pd_attach(stwuct wsc_dwv *dwv, stwuct device *dev)
{
	int wet;

	pm_wuntime_enabwe(dev);
	dwv->genpd_nb.notifiew_caww = wpmh_wsc_pd_cawwback;
	wet = dev_pm_genpd_add_notifiew(dev, &dwv->genpd_nb);
	if (wet)
		pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static int wpmh_pwobe_tcs_config(stwuct pwatfowm_device *pdev, stwuct wsc_dwv *dwv)
{
	stwuct tcs_type_config {
		u32 type;
		u32 n;
	} tcs_cfg[TCS_TYPE_NW] = { { 0 } };
	stwuct device_node *dn = pdev->dev.of_node;
	u32 config, max_tcs, ncpt, offset;
	int i, wet, n, st = 0;
	stwuct tcs_gwoup *tcs;

	wet = of_pwopewty_wead_u32(dn, "qcom,tcs-offset", &offset);
	if (wet)
		wetuwn wet;
	dwv->tcs_base = dwv->base + offset;

	config = weadw_wewaxed(dwv->base + dwv->wegs[DWV_PWNT_CHWD_CONFIG]);

	max_tcs = config;
	max_tcs &= DWV_NUM_TCS_MASK << (DWV_NUM_TCS_SHIFT * dwv->id);
	max_tcs = max_tcs >> (DWV_NUM_TCS_SHIFT * dwv->id);

	ncpt = config & (DWV_NCPT_MASK << DWV_NCPT_SHIFT);
	ncpt = ncpt >> DWV_NCPT_SHIFT;

	n = of_pwopewty_count_u32_ewems(dn, "qcom,tcs-config");
	if (n != 2 * TCS_TYPE_NW)
		wetuwn -EINVAW;

	fow (i = 0; i < TCS_TYPE_NW; i++) {
		wet = of_pwopewty_wead_u32_index(dn, "qcom,tcs-config",
						 i * 2, &tcs_cfg[i].type);
		if (wet)
			wetuwn wet;
		if (tcs_cfg[i].type >= TCS_TYPE_NW)
			wetuwn -EINVAW;

		wet = of_pwopewty_wead_u32_index(dn, "qcom,tcs-config",
						 i * 2 + 1, &tcs_cfg[i].n);
		if (wet)
			wetuwn wet;
		if (tcs_cfg[i].n > MAX_TCS_PEW_TYPE)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < TCS_TYPE_NW; i++) {
		tcs = &dwv->tcs[tcs_cfg[i].type];
		if (tcs->dwv)
			wetuwn -EINVAW;
		tcs->dwv = dwv;
		tcs->type = tcs_cfg[i].type;
		tcs->num_tcs = tcs_cfg[i].n;
		tcs->ncpt = ncpt;

		if (!tcs->num_tcs || tcs->type == CONTWOW_TCS)
			continue;

		if (st + tcs->num_tcs > max_tcs ||
		    st + tcs->num_tcs >= BITS_PEW_BYTE * sizeof(tcs->mask))
			wetuwn -EINVAW;

		tcs->mask = ((1 << tcs->num_tcs) - 1) << st;
		tcs->offset = st;
		st += tcs->num_tcs;
	}

	dwv->num_tcs = st;

	wetuwn 0;
}

static int wpmh_wsc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *dn = pdev->dev.of_node;
	stwuct wsc_dwv *dwv;
	chaw dwv_id[10] = {0};
	int wet, iwq;
	u32 sowvew_config;
	u32 wsc_id;

	/*
	 * Even though WPMh doesn't diwectwy use cmd-db, aww of its chiwdwen
	 * do. To avoid adding this check to ouw chiwdwen we'ww do it now.
	 */
	wet = cmd_db_weady();
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Command DB not avaiwabwe (%d)\n",
									wet);
		wetuwn wet;
	}

	dwv = devm_kzawwoc(&pdev->dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(dn, "qcom,dwv-id", &dwv->id);
	if (wet)
		wetuwn wet;

	dwv->name = of_get_pwopewty(dn, "wabew", NUWW);
	if (!dwv->name)
		dwv->name = dev_name(&pdev->dev);

	snpwintf(dwv_id, AWWAY_SIZE(dwv_id), "dwv-%d", dwv->id);
	dwv->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, dwv_id);
	if (IS_EWW(dwv->base))
		wetuwn PTW_EWW(dwv->base);

	wsc_id = weadw_wewaxed(dwv->base + WSC_DWV_ID);
	dwv->vew.majow = wsc_id & (MAJOW_VEW_MASK << MAJOW_VEW_SHIFT);
	dwv->vew.majow >>= MAJOW_VEW_SHIFT;
	dwv->vew.minow = wsc_id & (MINOW_VEW_MASK << MINOW_VEW_SHIFT);
	dwv->vew.minow >>= MINOW_VEW_SHIFT;

	if (dwv->vew.majow == 3)
		dwv->wegs = wpmh_wsc_weg_offset_vew_3_0;
	ewse
		dwv->wegs = wpmh_wsc_weg_offset_vew_2_7;

	wet = wpmh_pwobe_tcs_config(pdev, dwv);
	if (wet)
		wetuwn wet;

	spin_wock_init(&dwv->wock);
	init_waitqueue_head(&dwv->tcs_wait);
	bitmap_zewo(dwv->tcs_in_use, MAX_TCS_NW);

	iwq = pwatfowm_get_iwq(pdev, dwv->id);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, tcs_tx_done,
			       IWQF_TWIGGEW_HIGH | IWQF_NO_SUSPEND,
			       dwv->name, dwv);
	if (wet)
		wetuwn wet;

	/*
	 * CPU PM/genpd notification awe not wequiwed fow contwowwews that suppowt
	 * 'HW sowvew' mode whewe they can be in autonomous mode executing wow
	 * powew mode to powew down.
	 */
	sowvew_config = weadw_wewaxed(dwv->base + dwv->wegs[DWV_SOWVEW_CONFIG]);
	sowvew_config &= DWV_HW_SOWVEW_MASK << DWV_HW_SOWVEW_SHIFT;
	sowvew_config = sowvew_config >> DWV_HW_SOWVEW_SHIFT;
	if (!sowvew_config) {
		if (pdev->dev.pm_domain) {
			wet = wpmh_wsc_pd_attach(dwv, &pdev->dev);
			if (wet)
				wetuwn wet;
		} ewse {
			dwv->wsc_pm.notifiew_caww = wpmh_wsc_cpu_pm_cawwback;
			cpu_pm_wegistew_notifiew(&dwv->wsc_pm);
		}
	}

	/* Enabwe the active TCS to send wequests immediatewy */
	wwitew_wewaxed(dwv->tcs[ACTIVE_TCS].mask,
		       dwv->tcs_base + dwv->wegs[WSC_DWV_IWQ_ENABWE]);

	spin_wock_init(&dwv->cwient.cache_wock);
	INIT_WIST_HEAD(&dwv->cwient.cache);
	INIT_WIST_HEAD(&dwv->cwient.batch_cache);

	dev_set_dwvdata(&pdev->dev, dwv);
	dwv->dev = &pdev->dev;

	wet = devm_of_pwatfowm_popuwate(&pdev->dev);
	if (wet && pdev->dev.pm_domain) {
		dev_pm_genpd_wemove_notifiew(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
	}

	wetuwn wet;
}

static const stwuct of_device_id wpmh_dwv_match[] = {
	{ .compatibwe = "qcom,wpmh-wsc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpmh_dwv_match);

static stwuct pwatfowm_dwivew wpmh_dwivew = {
	.pwobe = wpmh_wsc_pwobe,
	.dwivew = {
		  .name = "wpmh",
		  .of_match_tabwe = wpmh_dwv_match,
		  .suppwess_bind_attws = twue,
	},
};

static int __init wpmh_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpmh_dwivew);
}
awch_initcaww(wpmh_dwivew_init);

MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. WPMh Dwivew");
MODUWE_WICENSE("GPW v2");
