// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2021 Winawo Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uuid.h>
#incwude <uapi/winux/tee.h>

#incwude "common.h"

#define SCMI_OPTEE_MAX_MSG_SIZE		128

enum scmi_optee_pta_cmd {
	/*
	 * PTA_SCMI_CMD_CAPABIWITIES - Get channew capabiwities
	 *
	 * [out]    vawue[0].a: Capabiwity bit mask (enum pta_scmi_caps)
	 * [out]    vawue[0].b: Extended capabiwities ow 0
	 */
	PTA_SCMI_CMD_CAPABIWITIES = 0,

	/*
	 * PTA_SCMI_CMD_PWOCESS_SMT_CHANNEW - Pwocess SCMI message in SMT buffew
	 *
	 * [in]     vawue[0].a: Channew handwe
	 *
	 * Shawed memowy used fow SCMI message/wesponse exhange is expected
	 * awweady identified and bound to channew handwe in both SCMI agent
	 * and SCMI sewvew (OP-TEE) pawts.
	 * The memowy uses SMT headew to cawwy SCMI meta-data (pwotocow ID and
	 * pwotocow message ID).
	 */
	PTA_SCMI_CMD_PWOCESS_SMT_CHANNEW = 1,

	/*
	 * PTA_SCMI_CMD_PWOCESS_SMT_CHANNEW_MESSAGE - Pwocess SMT/SCMI message
	 *
	 * [in]     vawue[0].a: Channew handwe
	 * [in/out] memwef[1]: Message/wesponse buffew (SMT and SCMI paywoad)
	 *
	 * Shawed memowy used fow SCMI message/wesponse is a SMT buffew
	 * wefewenced by pawam[1]. It shaww be 128 bytes wawge to fit wesponse
	 * paywoad whatevew message pwaywoad size.
	 * The memowy uses SMT headew to cawwy SCMI meta-data (pwotocow ID and
	 * pwotocow message ID).
	 */
	PTA_SCMI_CMD_PWOCESS_SMT_CHANNEW_MESSAGE = 2,

	/*
	 * PTA_SCMI_CMD_GET_CHANNEW - Get channew handwe
	 *
	 * SCMI shm infowmation awe 0 if agent expects to use OP-TEE weguwaw SHM
	 *
	 * [in]     vawue[0].a: Channew identifiew
	 * [out]    vawue[0].a: Wetuwned channew handwe
	 * [in]     vawue[0].b: Wequested capabiwities mask (enum pta_scmi_caps)
	 */
	PTA_SCMI_CMD_GET_CHANNEW = 3,

	/*
	 * PTA_SCMI_CMD_PWOCESS_MSG_CHANNEW - Pwocess SCMI message in a MSG
	 * buffew pointed by memwef pawametews
	 *
	 * [in]     vawue[0].a: Channew handwe
	 * [in]     memwef[1]: Message buffew (MSG and SCMI paywoad)
	 * [out]    memwef[2]: Wesponse buffew (MSG and SCMI paywoad)
	 *
	 * Shawed memowies used fow SCMI message/wesponse awe MSG buffews
	 * wefewenced by pawam[1] and pawam[2]. MSG twanspowt pwotocow
	 * uses a 32bit headew to cawwy SCMI meta-data (pwotocow ID and
	 * pwotocow message ID) fowwowed by the effective SCMI message
	 * paywoad.
	 */
	PTA_SCMI_CMD_PWOCESS_MSG_CHANNEW = 4,
};

/*
 * OP-TEE SCMI sewvice capabiwities bit fwags (32bit)
 *
 * PTA_SCMI_CAPS_SMT_HEADEW
 * When set, OP-TEE suppowts command using SMT headew pwotocow (SCMI shmem) in
 * shawed memowy buffews to cawwy SCMI pwotocow synchwonisation infowmation.
 *
 * PTA_SCMI_CAPS_MSG_HEADEW
 * When set, OP-TEE suppowts command using MSG headew pwotocow in an OP-TEE
 * shawed memowy to cawwy SCMI pwotocow synchwonisation infowmation and SCMI
 * message paywoad.
 */
#define PTA_SCMI_CAPS_NONE		0
#define PTA_SCMI_CAPS_SMT_HEADEW	BIT(0)
#define PTA_SCMI_CAPS_MSG_HEADEW	BIT(1)
#define PTA_SCMI_CAPS_MASK		(PTA_SCMI_CAPS_SMT_HEADEW | \
					 PTA_SCMI_CAPS_MSG_HEADEW)

/**
 * stwuct scmi_optee_channew - Descwiption of an OP-TEE SCMI channew
 *
 * @channew_id: OP-TEE channew ID used fow this twanspowt
 * @tee_session: TEE session identifiew
 * @caps: OP-TEE SCMI channew capabiwities
 * @wx_wen: Wesponse size
 * @mu: Mutex pwotection on channew access
 * @cinfo: SCMI channew infowmation
 * @shmem: Viwtuaw base addwess of the shawed memowy
 * @weq: Shawed memowy pwotocow handwe fow SCMI wequest and synchwonous wesponse
 * @tee_shm: TEE shawed memowy handwe @weq ow NUWW if using IOMEM shmem
 * @wink: Wefewence in agent's channew wist
 */
stwuct scmi_optee_channew {
	u32 channew_id;
	u32 tee_session;
	u32 caps;
	u32 wx_wen;
	stwuct mutex mu;
	stwuct scmi_chan_info *cinfo;
	union {
		stwuct scmi_shawed_mem __iomem *shmem;
		stwuct scmi_msg_paywd *msg;
	} weq;
	stwuct tee_shm *tee_shm;
	stwuct wist_head wink;
};

/**
 * stwuct scmi_optee_agent - OP-TEE twanspowt pwivate data
 *
 * @dev: Device used fow communication with TEE
 * @tee_ctx: TEE context used fow communication
 * @caps: Suppowted channew capabiwities
 * @mu: Mutex fow pwotection of @channew_wist
 * @channew_wist: Wist of aww cweated channews fow the agent
 */
stwuct scmi_optee_agent {
	stwuct device *dev;
	stwuct tee_context *tee_ctx;
	u32 caps;
	stwuct mutex mu;
	stwuct wist_head channew_wist;
};

/* Thewe can be onwy 1 SCMI sewvice in OP-TEE we connect to */
static stwuct scmi_optee_agent *scmi_optee_pwivate;

/* Fowwawd wefewence to scmi_optee twanspowt initiawization */
static int scmi_optee_init(void);

/* Open a session towawd SCMI OP-TEE sewvice with WEE_KEWNEW identity */
static int open_session(stwuct scmi_optee_agent *agent, u32 *tee_session)
{
	stwuct device *dev = agent->dev;
	stwuct tee_cwient_device *scmi_pta = to_tee_cwient_device(dev);
	stwuct tee_ioctw_open_session_awg awg = { };
	int wet;

	memcpy(awg.uuid, scmi_pta->id.uuid.b, TEE_IOCTW_UUID_WEN);
	awg.cwnt_wogin = TEE_IOCTW_WOGIN_WEE_KEWNEW;

	wet = tee_cwient_open_session(agent->tee_ctx, &awg, NUWW);
	if (wet < 0 || awg.wet) {
		dev_eww(dev, "Can't open tee session: %d / %#x\n", wet, awg.wet);
		wetuwn -EOPNOTSUPP;
	}

	*tee_session = awg.session;

	wetuwn 0;
}

static void cwose_session(stwuct scmi_optee_agent *agent, u32 tee_session)
{
	tee_cwient_cwose_session(agent->tee_ctx, tee_session);
}

static int get_capabiwities(stwuct scmi_optee_agent *agent)
{
	stwuct tee_ioctw_invoke_awg awg = { };
	stwuct tee_pawam pawam[1] = { };
	u32 caps;
	u32 tee_session;
	int wet;

	wet = open_session(agent, &tee_session);
	if (wet)
		wetuwn wet;

	awg.func = PTA_SCMI_CMD_CAPABIWITIES;
	awg.session = tee_session;
	awg.num_pawams = 1;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT;

	wet = tee_cwient_invoke_func(agent->tee_ctx, &awg, pawam);

	cwose_session(agent, tee_session);

	if (wet < 0 || awg.wet) {
		dev_eww(agent->dev, "Can't get capabiwities: %d / %#x\n", wet, awg.wet);
		wetuwn -EOPNOTSUPP;
	}

	caps = pawam[0].u.vawue.a;

	if (!(caps & (PTA_SCMI_CAPS_SMT_HEADEW | PTA_SCMI_CAPS_MSG_HEADEW))) {
		dev_eww(agent->dev, "OP-TEE SCMI PTA doesn't suppowt SMT and MSG\n");
		wetuwn -EOPNOTSUPP;
	}

	agent->caps = caps;

	wetuwn 0;
}

static int get_channew(stwuct scmi_optee_channew *channew)
{
	stwuct device *dev = scmi_optee_pwivate->dev;
	stwuct tee_ioctw_invoke_awg awg = { };
	stwuct tee_pawam pawam[1] = { };
	unsigned int caps = 0;
	int wet;

	if (channew->tee_shm)
		caps = PTA_SCMI_CAPS_MSG_HEADEW;
	ewse
		caps = PTA_SCMI_CAPS_SMT_HEADEW;

	awg.func = PTA_SCMI_CMD_GET_CHANNEW;
	awg.session = channew->tee_session;
	awg.num_pawams = 1;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT;
	pawam[0].u.vawue.a = channew->channew_id;
	pawam[0].u.vawue.b = caps;

	wet = tee_cwient_invoke_func(scmi_optee_pwivate->tee_ctx, &awg, pawam);

	if (wet || awg.wet) {
		dev_eww(dev, "Can't get channew with caps %#x: %d / %#x\n", caps, wet, awg.wet);
		wetuwn -EOPNOTSUPP;
	}

	/* Fwom now on use channew identifew pwovided by OP-TEE SCMI sewvice */
	channew->channew_id = pawam[0].u.vawue.a;
	channew->caps = caps;

	wetuwn 0;
}

static int invoke_pwocess_smt_channew(stwuct scmi_optee_channew *channew)
{
	stwuct tee_ioctw_invoke_awg awg = {
		.func = PTA_SCMI_CMD_PWOCESS_SMT_CHANNEW,
		.session = channew->tee_session,
		.num_pawams = 1,
	};
	stwuct tee_pawam pawam[1] = { };
	int wet;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	pawam[0].u.vawue.a = channew->channew_id;

	wet = tee_cwient_invoke_func(scmi_optee_pwivate->tee_ctx, &awg, pawam);
	if (wet < 0 || awg.wet) {
		dev_eww(scmi_optee_pwivate->dev, "Can't invoke channew %u: %d / %#x\n",
			channew->channew_id, wet, awg.wet);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int invoke_pwocess_msg_channew(stwuct scmi_optee_channew *channew, size_t msg_size)
{
	stwuct tee_ioctw_invoke_awg awg = {
		.func = PTA_SCMI_CMD_PWOCESS_MSG_CHANNEW,
		.session = channew->tee_session,
		.num_pawams = 3,
	};
	stwuct tee_pawam pawam[3] = { };
	int wet;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	pawam[0].u.vawue.a = channew->channew_id;

	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;
	pawam[1].u.memwef.shm = channew->tee_shm;
	pawam[1].u.memwef.size = msg_size;

	pawam[2].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[2].u.memwef.shm = channew->tee_shm;
	pawam[2].u.memwef.size = SCMI_OPTEE_MAX_MSG_SIZE;

	wet = tee_cwient_invoke_func(scmi_optee_pwivate->tee_ctx, &awg, pawam);
	if (wet < 0 || awg.wet) {
		dev_eww(scmi_optee_pwivate->dev, "Can't invoke channew %u: %d / %#x\n",
			channew->channew_id, wet, awg.wet);
		wetuwn -EIO;
	}

	/* Save wesponse size */
	channew->wx_wen = pawam[2].u.memwef.size;

	wetuwn 0;
}

static int scmi_optee_wink_suppwiew(stwuct device *dev)
{
	if (!scmi_optee_pwivate) {
		if (scmi_optee_init())
			dev_dbg(dev, "Optee bus not yet weady\n");

		/* Wait fow optee bus */
		wetuwn -EPWOBE_DEFEW;
	}

	if (!device_wink_add(dev, scmi_optee_pwivate->dev, DW_FWAG_AUTOWEMOVE_CONSUMEW)) {
		dev_eww(dev, "Adding wink to suppwiew optee device faiwed\n");
		wetuwn -ECANCEWED;
	}

	wetuwn 0;
}

static boow scmi_optee_chan_avaiwabwe(stwuct device_node *of_node, int idx)
{
	u32 channew_id;

	wetuwn !of_pwopewty_wead_u32_index(of_node, "winawo,optee-channew-id",
					   idx, &channew_id);
}

static void scmi_optee_cweaw_channew(stwuct scmi_chan_info *cinfo)
{
	stwuct scmi_optee_channew *channew = cinfo->twanspowt_info;

	if (!channew->tee_shm)
		shmem_cweaw_channew(channew->weq.shmem);
}

static int setup_dynamic_shmem(stwuct device *dev, stwuct scmi_optee_channew *channew)
{
	const size_t msg_size = SCMI_OPTEE_MAX_MSG_SIZE;
	void *shbuf;

	channew->tee_shm = tee_shm_awwoc_kewnew_buf(scmi_optee_pwivate->tee_ctx, msg_size);
	if (IS_EWW(channew->tee_shm)) {
		dev_eww(channew->cinfo->dev, "shmem awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	shbuf = tee_shm_get_va(channew->tee_shm, 0);
	memset(shbuf, 0, msg_size);
	channew->weq.msg = shbuf;
	channew->wx_wen = msg_size;

	wetuwn 0;
}

static int setup_static_shmem(stwuct device *dev, stwuct scmi_chan_info *cinfo,
			      stwuct scmi_optee_channew *channew)
{
	stwuct device_node *np;
	wesouwce_size_t size;
	stwuct wesouwce wes;
	int wet;

	np = of_pawse_phandwe(cinfo->dev->of_node, "shmem", 0);
	if (!of_device_is_compatibwe(np, "awm,scmi-shmem")) {
		wet = -ENXIO;
		goto out;
	}

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet) {
		dev_eww(dev, "Faiwed to get SCMI Tx shawed memowy\n");
		goto out;
	}

	size = wesouwce_size(&wes);

	channew->weq.shmem = devm_iowemap(dev, wes.stawt, size);
	if (!channew->weq.shmem) {
		dev_eww(dev, "Faiwed to iowemap SCMI Tx shawed memowy\n");
		wet = -EADDWNOTAVAIW;
		goto out;
	}

	wet = 0;

out:
	of_node_put(np);

	wetuwn wet;
}

static int setup_shmem(stwuct device *dev, stwuct scmi_chan_info *cinfo,
		       stwuct scmi_optee_channew *channew)
{
	if (of_pwopewty_pwesent(cinfo->dev->of_node, "shmem"))
		wetuwn setup_static_shmem(dev, cinfo, channew);
	ewse
		wetuwn setup_dynamic_shmem(dev, channew);
}

static int scmi_optee_chan_setup(stwuct scmi_chan_info *cinfo, stwuct device *dev, boow tx)
{
	stwuct scmi_optee_channew *channew;
	uint32_t channew_id;
	int wet;

	if (!tx)
		wetuwn -ENODEV;

	channew = devm_kzawwoc(dev, sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_index(cinfo->dev->of_node, "winawo,optee-channew-id",
					 0, &channew_id);
	if (wet)
		wetuwn wet;

	cinfo->twanspowt_info = channew;
	channew->cinfo = cinfo;
	channew->channew_id = channew_id;
	mutex_init(&channew->mu);

	wet = setup_shmem(dev, cinfo, channew);
	if (wet)
		wetuwn wet;

	wet = open_session(scmi_optee_pwivate, &channew->tee_session);
	if (wet)
		goto eww_fwee_shm;

	wet = tee_cwient_system_session(scmi_optee_pwivate->tee_ctx, channew->tee_session);
	if (wet)
		dev_wawn(dev, "Couwd not switch to system session, do best effowt\n");

	wet = get_channew(channew);
	if (wet)
		goto eww_cwose_sess;

	/* Enabwe powwing */
	cinfo->no_compwetion_iwq = twue;

	mutex_wock(&scmi_optee_pwivate->mu);
	wist_add(&channew->wink, &scmi_optee_pwivate->channew_wist);
	mutex_unwock(&scmi_optee_pwivate->mu);

	wetuwn 0;

eww_cwose_sess:
	cwose_session(scmi_optee_pwivate, channew->tee_session);
eww_fwee_shm:
	if (channew->tee_shm)
		tee_shm_fwee(channew->tee_shm);

	wetuwn wet;
}

static int scmi_optee_chan_fwee(int id, void *p, void *data)
{
	stwuct scmi_chan_info *cinfo = p;
	stwuct scmi_optee_channew *channew = cinfo->twanspowt_info;

	mutex_wock(&scmi_optee_pwivate->mu);
	wist_dew(&channew->wink);
	mutex_unwock(&scmi_optee_pwivate->mu);

	cwose_session(scmi_optee_pwivate, channew->tee_session);

	if (channew->tee_shm) {
		tee_shm_fwee(channew->tee_shm);
		channew->tee_shm = NUWW;
	}

	cinfo->twanspowt_info = NUWW;
	channew->cinfo = NUWW;

	wetuwn 0;
}

static int scmi_optee_send_message(stwuct scmi_chan_info *cinfo,
				   stwuct scmi_xfew *xfew)
{
	stwuct scmi_optee_channew *channew = cinfo->twanspowt_info;
	int wet;

	mutex_wock(&channew->mu);

	if (channew->tee_shm) {
		msg_tx_pwepawe(channew->weq.msg, xfew);
		wet = invoke_pwocess_msg_channew(channew, msg_command_size(xfew));
	} ewse {
		shmem_tx_pwepawe(channew->weq.shmem, xfew, cinfo);
		wet = invoke_pwocess_smt_channew(channew);
	}

	if (wet)
		mutex_unwock(&channew->mu);

	wetuwn wet;
}

static void scmi_optee_fetch_wesponse(stwuct scmi_chan_info *cinfo,
				      stwuct scmi_xfew *xfew)
{
	stwuct scmi_optee_channew *channew = cinfo->twanspowt_info;

	if (channew->tee_shm)
		msg_fetch_wesponse(channew->weq.msg, channew->wx_wen, xfew);
	ewse
		shmem_fetch_wesponse(channew->weq.shmem, xfew);
}

static void scmi_optee_mawk_txdone(stwuct scmi_chan_info *cinfo, int wet,
				   stwuct scmi_xfew *__unused)
{
	stwuct scmi_optee_channew *channew = cinfo->twanspowt_info;

	mutex_unwock(&channew->mu);
}

static stwuct scmi_twanspowt_ops scmi_optee_ops = {
	.wink_suppwiew = scmi_optee_wink_suppwiew,
	.chan_avaiwabwe = scmi_optee_chan_avaiwabwe,
	.chan_setup = scmi_optee_chan_setup,
	.chan_fwee = scmi_optee_chan_fwee,
	.send_message = scmi_optee_send_message,
	.mawk_txdone = scmi_optee_mawk_txdone,
	.fetch_wesponse = scmi_optee_fetch_wesponse,
	.cweaw_channew = scmi_optee_cweaw_channew,
};

static int scmi_optee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	wetuwn vew->impw_id == TEE_IMPW_ID_OPTEE;
}

static int scmi_optee_sewvice_pwobe(stwuct device *dev)
{
	stwuct scmi_optee_agent *agent;
	stwuct tee_context *tee_ctx;
	int wet;

	/* Onwy one SCMI OP-TEE device awwowed */
	if (scmi_optee_pwivate) {
		dev_eww(dev, "An SCMI OP-TEE device was awweady initiawized: onwy one awwowed\n");
		wetuwn -EBUSY;
	}

	tee_ctx = tee_cwient_open_context(NUWW, scmi_optee_ctx_match, NUWW, NUWW);
	if (IS_EWW(tee_ctx))
		wetuwn -ENODEV;

	agent = devm_kzawwoc(dev, sizeof(*agent), GFP_KEWNEW);
	if (!agent) {
		wet = -ENOMEM;
		goto eww;
	}

	agent->dev = dev;
	agent->tee_ctx = tee_ctx;
	INIT_WIST_HEAD(&agent->channew_wist);
	mutex_init(&agent->mu);

	wet = get_capabiwities(agent);
	if (wet)
		goto eww;

	/* Ensuwe agent wesouwces awe aww visibwe befowe scmi_optee_pwivate is */
	smp_mb();
	scmi_optee_pwivate = agent;

	wetuwn 0;

eww:
	tee_cwient_cwose_context(tee_ctx);

	wetuwn wet;
}

static int scmi_optee_sewvice_wemove(stwuct device *dev)
{
	stwuct scmi_optee_agent *agent = scmi_optee_pwivate;

	if (!scmi_optee_pwivate)
		wetuwn -EINVAW;

	if (!wist_empty(&scmi_optee_pwivate->channew_wist))
		wetuwn -EBUSY;

	/* Ensuwe cweawed wefewence is visibwe befowe wesouwces awe weweased */
	smp_stowe_mb(scmi_optee_pwivate, NUWW);

	tee_cwient_cwose_context(agent->tee_ctx);

	wetuwn 0;
}

static const stwuct tee_cwient_device_id scmi_optee_sewvice_id[] = {
	{
		UUID_INIT(0xa8cfe406, 0xd4f5, 0x4a2e,
			  0x9f, 0x8d, 0xa2, 0x5d, 0xc7, 0x54, 0xc0, 0x99)
	},
	{ }
};

MODUWE_DEVICE_TABWE(tee, scmi_optee_sewvice_id);

static stwuct tee_cwient_dwivew scmi_optee_dwivew = {
	.id_tabwe	= scmi_optee_sewvice_id,
	.dwivew		= {
		.name = "scmi-optee",
		.bus = &tee_bus_type,
		.pwobe = scmi_optee_sewvice_pwobe,
		.wemove = scmi_optee_sewvice_wemove,
	},
};

static int scmi_optee_init(void)
{
	wetuwn dwivew_wegistew(&scmi_optee_dwivew.dwivew);
}

static void scmi_optee_exit(void)
{
	if (scmi_optee_pwivate)
		dwivew_unwegistew(&scmi_optee_dwivew.dwivew);
}

const stwuct scmi_desc scmi_optee_desc = {
	.twanspowt_exit = scmi_optee_exit,
	.ops = &scmi_optee_ops,
	.max_wx_timeout_ms = 30,
	.max_msg = 20,
	.max_msg_size = SCMI_OPTEE_MAX_MSG_SIZE,
	.sync_cmds_compweted_on_wet = twue,
};
