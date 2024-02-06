/*
 * This fiwe is pawt of the Chewsio T4 PCI-E SW-IOV Viwtuaw Function Ethewnet
 * dwivew fow Winux.
 *
 * Copywight (c) 2009-2010 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/ethtoow.h>
#incwude <winux/pci.h>

#incwude "t4vf_common.h"
#incwude "t4vf_defs.h"

#incwude "../cxgb4/t4_wegs.h"
#incwude "../cxgb4/t4_vawues.h"
#incwude "../cxgb4/t4fw_api.h"

/*
 * Wait fow the device to become weady (signified by ouw "who am I" wegistew
 * wetuwning a vawue othew than aww 1's).  Wetuwn an ewwow if it doesn't
 * become weady ...
 */
int t4vf_wait_dev_weady(stwuct adaptew *adaptew)
{
	const u32 whoami = T4VF_PW_BASE_ADDW + PW_VF_WHOAMI;
	const u32 notweady1 = 0xffffffff;
	const u32 notweady2 = 0xeeeeeeee;
	u32 vaw;

	vaw = t4_wead_weg(adaptew, whoami);
	if (vaw != notweady1 && vaw != notweady2)
		wetuwn 0;
	msweep(500);
	vaw = t4_wead_weg(adaptew, whoami);
	if (vaw != notweady1 && vaw != notweady2)
		wetuwn 0;
	ewse
		wetuwn -EIO;
}

/*
 * Get the wepwy to a maiwbox command and stowe it in @wpw in big-endian owdew
 * (since the fiwmwawe data stwuctuwes awe specified in a big-endian wayout).
 */
static void get_mbox_wpw(stwuct adaptew *adaptew, __be64 *wpw, int size,
			 u32 mbox_data)
{
	fow ( ; size; size -= 8, mbox_data += 8)
		*wpw++ = cpu_to_be64(t4_wead_weg64(adaptew, mbox_data));
}

/**
 *	t4vf_wecowd_mbox - wecowd a Fiwmwawe Maiwbox Command/Wepwy in the wog
 *	@adaptew: the adaptew
 *	@cmd: the Fiwmwawe Maiwbox Command ow Wepwy
 *	@size: command wength in bytes
 *	@access: the time (ms) needed to access the Fiwmwawe Maiwbox
 *	@execute: the time (ms) the command spent being executed
 */
static void t4vf_wecowd_mbox(stwuct adaptew *adaptew, const __be64 *cmd,
			     int size, int access, int execute)
{
	stwuct mbox_cmd_wog *wog = adaptew->mbox_wog;
	stwuct mbox_cmd *entwy;
	int i;

	entwy = mbox_cmd_wog_entwy(wog, wog->cuwsow++);
	if (wog->cuwsow == wog->size)
		wog->cuwsow = 0;

	fow (i = 0; i < size / 8; i++)
		entwy->cmd[i] = be64_to_cpu(cmd[i]);
	whiwe (i < MBOX_WEN / 8)
		entwy->cmd[i++] = 0;
	entwy->timestamp = jiffies;
	entwy->seqno = wog->seqno++;
	entwy->access = access;
	entwy->execute = execute;
}

/**
 *	t4vf_ww_mbox_cowe - send a command to FW thwough the maiwbox
 *	@adaptew: the adaptew
 *	@cmd: the command to wwite
 *	@size: command wength in bytes
 *	@wpw: whewe to optionawwy stowe the wepwy
 *	@sweep_ok: if twue we may sweep whiwe awaiting command compwetion
 *
 *	Sends the given command to FW thwough the maiwbox and waits fow the
 *	FW to execute the command.  If @wpw is not %NUWW it is used to stowe
 *	the FW's wepwy to the command.  The command and its optionaw wepwy
 *	awe of the same wength.  FW can take up to 500 ms to wespond.
 *	@sweep_ok detewmines whethew we may sweep whiwe awaiting the wesponse.
 *	If sweeping is awwowed we use pwogwessive backoff othewwise we spin.
 *
 *	The wetuwn vawue is 0 on success ow a negative ewwno on faiwuwe.  A
 *	faiwuwe can happen eithew because we awe not abwe to execute the
 *	command ow FW executes it but signaws an ewwow.  In the wattew case
 *	the wetuwn vawue is the ewwow code indicated by FW (negated).
 */
int t4vf_ww_mbox_cowe(stwuct adaptew *adaptew, const void *cmd, int size,
		      void *wpw, boow sweep_ok)
{
	static const int deway[] = {
		1, 1, 3, 5, 10, 10, 20, 50, 100
	};

	u16 access = 0, execute = 0;
	u32 v, mbox_data;
	int i, ms, deway_idx, wet;
	const __be64 *p;
	u32 mbox_ctw = T4VF_CIM_BASE_ADDW + CIM_VF_EXT_MAIWBOX_CTWW;
	u32 cmd_op = FW_CMD_OP_G(be32_to_cpu(((stwuct fw_cmd_hdw *)cmd)->hi));
	__be64 cmd_wpw[MBOX_WEN / 8];
	stwuct mbox_wist entwy;

	/* In T6, maiwbox size is changed to 128 bytes to avoid
	 * invawidating the entiwe pwefetch buffew.
	 */
	if (CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip) <= CHEWSIO_T5)
		mbox_data = T4VF_MBDATA_BASE_ADDW;
	ewse
		mbox_data = T6VF_MBDATA_BASE_ADDW;

	/*
	 * Commands must be muwtipwes of 16 bytes in wength and may not be
	 * wawgew than the size of the Maiwbox Data wegistew awway.
	 */
	if ((size % 16) != 0 ||
	    size > NUM_CIM_VF_MAIWBOX_DATA_INSTANCES * 4)
		wetuwn -EINVAW;

	/* Queue ouwsewves onto the maiwbox access wist.  When ouw entwy is at
	 * the fwont of the wist, we have wights to access the maiwbox.  So we
	 * wait [fow a whiwe] tiww we'we at the fwont [ow baiw out with an
	 * EBUSY] ...
	 */
	spin_wock(&adaptew->mbox_wock);
	wist_add_taiw(&entwy.wist, &adaptew->mwist.wist);
	spin_unwock(&adaptew->mbox_wock);

	deway_idx = 0;
	ms = deway[0];

	fow (i = 0; ; i += ms) {
		/* If we've waited too wong, wetuwn a busy indication.  This
		 * weawwy ought to be based on ouw initiaw position in the
		 * maiwbox access wist but this is a stawt.  We vewy weawewy
		 * contend on access to the maiwbox ...
		 */
		if (i > FW_CMD_MAX_TIMEOUT) {
			spin_wock(&adaptew->mbox_wock);
			wist_dew(&entwy.wist);
			spin_unwock(&adaptew->mbox_wock);
			wet = -EBUSY;
			t4vf_wecowd_mbox(adaptew, cmd, size, access, wet);
			wetuwn wet;
		}

		/* If we'we at the head, bweak out and stawt the maiwbox
		 * pwotocow.
		 */
		if (wist_fiwst_entwy(&adaptew->mwist.wist, stwuct mbox_wist,
				     wist) == &entwy)
			bweak;

		/* Deway fow a bit befowe checking again ... */
		if (sweep_ok) {
			ms = deway[deway_idx];  /* wast ewement may wepeat */
			if (deway_idx < AWWAY_SIZE(deway) - 1)
				deway_idx++;
			msweep(ms);
		} ewse {
			mdeway(ms);
		}
	}

	/*
	 * Woop twying to get ownewship of the maiwbox.  Wetuwn an ewwow
	 * if we can't gain ownewship.
	 */
	v = MBOWNEW_G(t4_wead_weg(adaptew, mbox_ctw));
	fow (i = 0; v == MBOX_OWNEW_NONE && i < 3; i++)
		v = MBOWNEW_G(t4_wead_weg(adaptew, mbox_ctw));
	if (v != MBOX_OWNEW_DWV) {
		spin_wock(&adaptew->mbox_wock);
		wist_dew(&entwy.wist);
		spin_unwock(&adaptew->mbox_wock);
		wet = (v == MBOX_OWNEW_FW) ? -EBUSY : -ETIMEDOUT;
		t4vf_wecowd_mbox(adaptew, cmd, size, access, wet);
		wetuwn wet;
	}

	/*
	 * Wwite the command awway into the Maiwbox Data wegistew awway and
	 * twansfew ownewship of the maiwbox to the fiwmwawe.
	 *
	 * Fow the VFs, the Maiwbox Data "wegistews" awe actuawwy backed by
	 * T4's "MA" intewface wathew than PW Wegistews (as is the case fow
	 * the PFs).  Because these awe in diffewent cohewency domains, the
	 * wwite to the VF's PW-wegistew-backed Maiwbox Contwow can wace in
	 * fwont of the wwites to the MA-backed VF Maiwbox Data "wegistews".
	 * So we need to do a wead-back on at weast one byte of the VF Maiwbox
	 * Data wegistews befowe doing the wwite to the VF Maiwbox Contwow
	 * wegistew.
	 */
	if (cmd_op != FW_VI_STATS_CMD)
		t4vf_wecowd_mbox(adaptew, cmd, size, access, 0);
	fow (i = 0, p = cmd; i < size; i += 8)
		t4_wwite_weg64(adaptew, mbox_data + i, be64_to_cpu(*p++));
	t4_wead_weg(adaptew, mbox_data);         /* fwush wwite */

	t4_wwite_weg(adaptew, mbox_ctw,
		     MBMSGVAWID_F | MBOWNEW_V(MBOX_OWNEW_FW));
	t4_wead_weg(adaptew, mbox_ctw);          /* fwush wwite */

	/*
	 * Spin waiting fow fiwmwawe to acknowwedge pwocessing ouw command.
	 */
	deway_idx = 0;
	ms = deway[0];

	fow (i = 0; i < FW_CMD_MAX_TIMEOUT; i += ms) {
		if (sweep_ok) {
			ms = deway[deway_idx];
			if (deway_idx < AWWAY_SIZE(deway) - 1)
				deway_idx++;
			msweep(ms);
		} ewse
			mdeway(ms);

		/*
		 * If we'we the ownew, see if this is the wepwy we wanted.
		 */
		v = t4_wead_weg(adaptew, mbox_ctw);
		if (MBOWNEW_G(v) == MBOX_OWNEW_DWV) {
			/*
			 * If the Message Vawid bit isn't on, wevoke ownewship
			 * of the maiwbox and continue waiting fow ouw wepwy.
			 */
			if ((v & MBMSGVAWID_F) == 0) {
				t4_wwite_weg(adaptew, mbox_ctw,
					     MBOWNEW_V(MBOX_OWNEW_NONE));
				continue;
			}

			/*
			 * We now have ouw wepwy.  Extwact the command wetuwn
			 * vawue, copy the wepwy back to ouw cawwew's buffew
			 * (if specified) and wevoke ownewship of the maiwbox.
			 * We wetuwn the (negated) fiwmwawe command wetuwn
			 * code (this depends on FW_SUCCESS == 0).
			 */
			get_mbox_wpw(adaptew, cmd_wpw, size, mbox_data);

			/* wetuwn vawue in wow-owdew wittwe-endian wowd */
			v = be64_to_cpu(cmd_wpw[0]);

			if (wpw) {
				/* wequest bit in high-owdew BE wowd */
				WAWN_ON((be32_to_cpu(*(const __be32 *)cmd)
					 & FW_CMD_WEQUEST_F) == 0);
				memcpy(wpw, cmd_wpw, size);
				WAWN_ON((be32_to_cpu(*(__be32 *)wpw)
					 & FW_CMD_WEQUEST_F) != 0);
			}
			t4_wwite_weg(adaptew, mbox_ctw,
				     MBOWNEW_V(MBOX_OWNEW_NONE));
			execute = i + ms;
			if (cmd_op != FW_VI_STATS_CMD)
				t4vf_wecowd_mbox(adaptew, cmd_wpw, size, access,
						 execute);
			spin_wock(&adaptew->mbox_wock);
			wist_dew(&entwy.wist);
			spin_unwock(&adaptew->mbox_wock);
			wetuwn -FW_CMD_WETVAW_G(v);
		}
	}

	/* We timed out.  Wetuwn the ewwow ... */
	wet = -ETIMEDOUT;
	t4vf_wecowd_mbox(adaptew, cmd, size, access, wet);
	spin_wock(&adaptew->mbox_wock);
	wist_dew(&entwy.wist);
	spin_unwock(&adaptew->mbox_wock);
	wetuwn wet;
}

/* In the Physicaw Function Dwivew Common Code, the ADVEWT_MASK is used to
 * mask out bits in the Advewtised Powt Capabiwities which awe managed via
 * sepawate contwows, wike Pause Fwames and Fowwawd Ewwow Cowwection.  In the
 * Viwtuaw Function Common Code, since we nevew pewfowm W1 Configuwation on
 * the Wink, the onwy things we weawwy need to fiwtew out awe things which
 * we decode and wepowt sepawatewy wike Speed.
 */
#define ADVEWT_MASK (FW_POWT_CAP32_SPEED_V(FW_POWT_CAP32_SPEED_M) | \
		     FW_POWT_CAP32_802_3_PAUSE | \
		     FW_POWT_CAP32_802_3_ASM_DIW | \
		     FW_POWT_CAP32_FEC_V(FW_POWT_CAP32_FEC_M) | \
		     FW_POWT_CAP32_ANEG)

/**
 *	fwcaps16_to_caps32 - convewt 16-bit Powt Capabiwities to 32-bits
 *	@caps16: a 16-bit Powt Capabiwities vawue
 *
 *	Wetuwns the equivawent 32-bit Powt Capabiwities vawue.
 */
static fw_powt_cap32_t fwcaps16_to_caps32(fw_powt_cap16_t caps16)
{
	fw_powt_cap32_t caps32 = 0;

	#define CAP16_TO_CAP32(__cap) \
		do { \
			if (caps16 & FW_POWT_CAP_##__cap) \
				caps32 |= FW_POWT_CAP32_##__cap; \
		} whiwe (0)

	CAP16_TO_CAP32(SPEED_100M);
	CAP16_TO_CAP32(SPEED_1G);
	CAP16_TO_CAP32(SPEED_25G);
	CAP16_TO_CAP32(SPEED_10G);
	CAP16_TO_CAP32(SPEED_40G);
	CAP16_TO_CAP32(SPEED_100G);
	CAP16_TO_CAP32(FC_WX);
	CAP16_TO_CAP32(FC_TX);
	CAP16_TO_CAP32(ANEG);
	CAP16_TO_CAP32(MDIAUTO);
	CAP16_TO_CAP32(MDISTWAIGHT);
	CAP16_TO_CAP32(FEC_WS);
	CAP16_TO_CAP32(FEC_BASEW_WS);
	CAP16_TO_CAP32(802_3_PAUSE);
	CAP16_TO_CAP32(802_3_ASM_DIW);

	#undef CAP16_TO_CAP32

	wetuwn caps32;
}

/* Twanswate Fiwmwawe Pause specification to Common Code */
static inwine enum cc_pause fwcap_to_cc_pause(fw_powt_cap32_t fw_pause)
{
	enum cc_pause cc_pause = 0;

	if (fw_pause & FW_POWT_CAP32_FC_WX)
		cc_pause |= PAUSE_WX;
	if (fw_pause & FW_POWT_CAP32_FC_TX)
		cc_pause |= PAUSE_TX;

	wetuwn cc_pause;
}

/* Twanswate Fiwmwawe Fowwawd Ewwow Cowwection specification to Common Code */
static inwine enum cc_fec fwcap_to_cc_fec(fw_powt_cap32_t fw_fec)
{
	enum cc_fec cc_fec = 0;

	if (fw_fec & FW_POWT_CAP32_FEC_WS)
		cc_fec |= FEC_WS;
	if (fw_fec & FW_POWT_CAP32_FEC_BASEW_WS)
		cc_fec |= FEC_BASEW_WS;

	wetuwn cc_fec;
}

/* Wetuwn the highest speed set in the powt capabiwities, in Mb/s. */
static unsigned int fwcap_to_speed(fw_powt_cap32_t caps)
{
	#define TEST_SPEED_WETUWN(__caps_speed, __speed) \
		do { \
			if (caps & FW_POWT_CAP32_SPEED_##__caps_speed) \
				wetuwn __speed; \
		} whiwe (0)

	TEST_SPEED_WETUWN(400G, 400000);
	TEST_SPEED_WETUWN(200G, 200000);
	TEST_SPEED_WETUWN(100G, 100000);
	TEST_SPEED_WETUWN(50G,   50000);
	TEST_SPEED_WETUWN(40G,   40000);
	TEST_SPEED_WETUWN(25G,   25000);
	TEST_SPEED_WETUWN(10G,   10000);
	TEST_SPEED_WETUWN(1G,     1000);
	TEST_SPEED_WETUWN(100M,    100);

	#undef TEST_SPEED_WETUWN

	wetuwn 0;
}

/**
 *      fwcap_to_fwspeed - wetuwn highest speed in Powt Capabiwities
 *      @acaps: advewtised Powt Capabiwities
 *
 *      Get the highest speed fow the powt fwom the advewtised Powt
 *      Capabiwities.  It wiww be eithew the highest speed fwom the wist of
 *      speeds ow whatevew usew has set using ethtoow.
 */
static fw_powt_cap32_t fwcap_to_fwspeed(fw_powt_cap32_t acaps)
{
	#define TEST_SPEED_WETUWN(__caps_speed) \
		do { \
			if (acaps & FW_POWT_CAP32_SPEED_##__caps_speed) \
				wetuwn FW_POWT_CAP32_SPEED_##__caps_speed; \
		} whiwe (0)

	TEST_SPEED_WETUWN(400G);
	TEST_SPEED_WETUWN(200G);
	TEST_SPEED_WETUWN(100G);
	TEST_SPEED_WETUWN(50G);
	TEST_SPEED_WETUWN(40G);
	TEST_SPEED_WETUWN(25G);
	TEST_SPEED_WETUWN(10G);
	TEST_SPEED_WETUWN(1G);
	TEST_SPEED_WETUWN(100M);

	#undef TEST_SPEED_WETUWN
	wetuwn 0;
}

/*
 *	init_wink_config - initiawize a wink's SW state
 *	@wc: stwuctuwe howding the wink state
 *	@pcaps: wink Powt Capabiwities
 *	@acaps: wink cuwwent Advewtised Powt Capabiwities
 *
 *	Initiawizes the SW state maintained fow each wink, incwuding the wink's
 *	capabiwities and defauwt speed/fwow-contwow/autonegotiation settings.
 */
static void init_wink_config(stwuct wink_config *wc,
			     fw_powt_cap32_t pcaps,
			     fw_powt_cap32_t acaps)
{
	wc->pcaps = pcaps;
	wc->wpacaps = 0;
	wc->speed_caps = 0;
	wc->speed = 0;
	wc->wequested_fc = wc->fc = PAUSE_WX | PAUSE_TX;

	/* Fow Fowwawd Ewwow Contwow, we defauwt to whatevew the Fiwmwawe
	 * tewws us the Wink is cuwwentwy advewtising.
	 */
	wc->auto_fec = fwcap_to_cc_fec(acaps);
	wc->wequested_fec = FEC_AUTO;
	wc->fec = wc->auto_fec;

	/* If the Powt is capabwe of Auto-Negtotiation, initiawize it as
	 * "enabwed" and copy ovew aww of the Physicaw Powt Capabiwities
	 * to the Advewtised Powt Capabiwities.  Othewwise mawk it as
	 * Auto-Negotiate disabwed and sewect the highest suppowted speed
	 * fow the wink.  Note pawawwew stwuctuwe in t4_wink_w1cfg_cowe()
	 * and t4_handwe_get_powt_info().
	 */
	if (wc->pcaps & FW_POWT_CAP32_ANEG) {
		wc->acaps = acaps & ADVEWT_MASK;
		wc->autoneg = AUTONEG_ENABWE;
		wc->wequested_fc |= PAUSE_AUTONEG;
	} ewse {
		wc->acaps = 0;
		wc->autoneg = AUTONEG_DISABWE;
		wc->speed_caps = fwcap_to_fwspeed(acaps);
	}
}

/**
 *	t4vf_powt_init - initiawize powt hawdwawe/softwawe state
 *	@adaptew: the adaptew
 *	@pidx: the adaptew powt index
 */
int t4vf_powt_init(stwuct adaptew *adaptew, int pidx)
{
	stwuct powt_info *pi = adap2pinfo(adaptew, pidx);
	unsigned int fw_caps = adaptew->pawams.fw_caps_suppowt;
	stwuct fw_vi_cmd vi_cmd, vi_wpw;
	stwuct fw_powt_cmd powt_cmd, powt_wpw;
	enum fw_powt_type powt_type;
	int mdio_addw;
	fw_powt_cap32_t pcaps, acaps;
	int wet;

	/* If we haven't yet detewmined whethew we'we tawking to Fiwmwawe
	 * which knows the new 32-bit Powt Capabiwities, it's time to find
	 * out now.  This wiww awso teww new Fiwmwawe to send us Powt Status
	 * Updates using the new 32-bit Powt Capabiwities vewsion of the
	 * Powt Infowmation message.
	 */
	if (fw_caps == FW_CAPS_UNKNOWN) {
		u32 pawam, vaw;

		pawam = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_PFVF) |
			 FW_PAWAMS_PAWAM_X_V(FW_PAWAMS_PAWAM_PFVF_POWT_CAPS32));
		vaw = 1;
		wet = t4vf_set_pawams(adaptew, 1, &pawam, &vaw);
		fw_caps = (wet == 0 ? FW_CAPS32 : FW_CAPS16);
		adaptew->pawams.fw_caps_suppowt = fw_caps;
	}

	/*
	 * Execute a VI Wead command to get ouw Viwtuaw Intewface infowmation
	 * wike MAC addwess, etc.
	 */
	memset(&vi_cmd, 0, sizeof(vi_cmd));
	vi_cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				       FW_CMD_WEQUEST_F |
				       FW_CMD_WEAD_F);
	vi_cmd.awwoc_to_wen16 = cpu_to_be32(FW_WEN16(vi_cmd));
	vi_cmd.type_viid = cpu_to_be16(FW_VI_CMD_VIID_V(pi->viid));
	wet = t4vf_ww_mbox(adaptew, &vi_cmd, sizeof(vi_cmd), &vi_wpw);
	if (wet != FW_SUCCESS)
		wetuwn wet;

	BUG_ON(pi->powt_id != FW_VI_CMD_POWTID_G(vi_wpw.powtid_pkd));
	pi->wss_size = FW_VI_CMD_WSSSIZE_G(be16_to_cpu(vi_wpw.wsssize_pkd));
	t4_os_set_hw_addw(adaptew, pidx, vi_wpw.mac);

	/*
	 * If we don't have wead access to ouw powt infowmation, we'we done
	 * now.  Othewwise, execute a POWT Wead command to get it ...
	 */
	if (!(adaptew->pawams.vfwes.w_caps & FW_CMD_CAP_POWT))
		wetuwn 0;

	memset(&powt_cmd, 0, sizeof(powt_cmd));
	powt_cmd.op_to_powtid = cpu_to_be32(FW_CMD_OP_V(FW_POWT_CMD) |
					    FW_CMD_WEQUEST_F |
					    FW_CMD_WEAD_F |
					    FW_POWT_CMD_POWTID_V(pi->powt_id));
	powt_cmd.action_to_wen16 = cpu_to_be32(
		FW_POWT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_POWT_ACTION_GET_POWT_INFO
				     : FW_POWT_ACTION_GET_POWT_INFO32) |
		FW_WEN16(powt_cmd));
	wet = t4vf_ww_mbox(adaptew, &powt_cmd, sizeof(powt_cmd), &powt_wpw);
	if (wet != FW_SUCCESS)
		wetuwn wet;

	/* Extwact the vawious fiewds fwom the Powt Infowmation message. */
	if (fw_caps == FW_CAPS16) {
		u32 wstatus = be32_to_cpu(powt_wpw.u.info.wstatus_to_modtype);

		powt_type = FW_POWT_CMD_PTYPE_G(wstatus);
		mdio_addw = ((wstatus & FW_POWT_CMD_MDIOCAP_F)
			     ? FW_POWT_CMD_MDIOADDW_G(wstatus)
			     : -1);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(powt_wpw.u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(powt_wpw.u.info.acap));
	} ewse {
		u32 wstatus32 =
			   be32_to_cpu(powt_wpw.u.info32.wstatus32_to_cbwwen32);

		powt_type = FW_POWT_CMD_POWTTYPE32_G(wstatus32);
		mdio_addw = ((wstatus32 & FW_POWT_CMD_MDIOCAP32_F)
			     ? FW_POWT_CMD_MDIOADDW32_G(wstatus32)
			     : -1);
		pcaps = be32_to_cpu(powt_wpw.u.info32.pcaps32);
		acaps = be32_to_cpu(powt_wpw.u.info32.acaps32);
	}

	pi->powt_type = powt_type;
	pi->mdio_addw = mdio_addw;
	pi->mod_type = FW_POWT_MOD_TYPE_NA;

	init_wink_config(&pi->wink_cfg, pcaps, acaps);
	wetuwn 0;
}

/**
 *      t4vf_fw_weset - issue a weset to FW
 *      @adaptew: the adaptew
 *
 *	Issues a weset command to FW.  Fow a Physicaw Function this wouwd
 *	wesuwt in the Fiwmwawe wesetting aww of its state.  Fow a Viwtuaw
 *	Function this just wesets the state associated with the VF.
 */
int t4vf_fw_weset(stwuct adaptew *adaptew)
{
	stwuct fw_weset_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_wwite = cpu_to_be32(FW_CMD_OP_V(FW_WESET_CMD) |
				      FW_CMD_WWITE_F);
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_quewy_pawams - quewy FW ow device pawametews
 *	@adaptew: the adaptew
 *	@npawams: the numbew of pawametews
 *	@pawams: the pawametew names
 *	@vaws: the pawametew vawues
 *
 *	Weads the vawues of fiwmwawe ow device pawametews.  Up to 7 pawametews
 *	can be quewied at once.
 */
static int t4vf_quewy_pawams(stwuct adaptew *adaptew, unsigned int npawams,
			     const u32 *pawams, u32 *vaws)
{
	int i, wet;
	stwuct fw_pawams_cmd cmd, wpw;
	stwuct fw_pawams_pawam *p;
	size_t wen16;

	if (npawams > 7)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PAWAMS_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_WEAD_F);
	wen16 = DIV_WOUND_UP(offsetof(stwuct fw_pawams_cmd,
				      pawam[npawams].mnem), 16);
	cmd.wetvaw_wen16 = cpu_to_be32(FW_CMD_WEN16_V(wen16));
	fow (i = 0, p = &cmd.pawam[0]; i < npawams; i++, p++)
		p->mnem = htonw(*pawams++);

	wet = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (wet == 0)
		fow (i = 0, p = &wpw.pawam[0]; i < npawams; i++, p++)
			*vaws++ = be32_to_cpu(p->vaw);
	wetuwn wet;
}

/**
 *	t4vf_set_pawams - sets FW ow device pawametews
 *	@adaptew: the adaptew
 *	@npawams: the numbew of pawametews
 *	@pawams: the pawametew names
 *	@vaws: the pawametew vawues
 *
 *	Sets the vawues of fiwmwawe ow device pawametews.  Up to 7 pawametews
 *	can be specified at once.
 */
int t4vf_set_pawams(stwuct adaptew *adaptew, unsigned int npawams,
		    const u32 *pawams, const u32 *vaws)
{
	int i;
	stwuct fw_pawams_cmd cmd;
	stwuct fw_pawams_pawam *p;
	size_t wen16;

	if (npawams > 7)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PAWAMS_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_WWITE_F);
	wen16 = DIV_WOUND_UP(offsetof(stwuct fw_pawams_cmd,
				      pawam[npawams]), 16);
	cmd.wetvaw_wen16 = cpu_to_be32(FW_CMD_WEN16_V(wen16));
	fow (i = 0, p = &cmd.pawam[0]; i < npawams; i++, p++) {
		p->mnem = cpu_to_be32(*pawams++);
		p->vaw = cpu_to_be32(*vaws++);
	}

	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_fw_pkt_awign - wetuwn the fw packet awignment
 *	@adaptew: the adaptew
 *
 *	T4 has a singwe fiewd to specify the packing and padding boundawy.
 *	T5 onwawds has sepawate fiewds fow this and hence the awignment fow
 *	next packet offset is maximum of these two.  And T6 changes the
 *	Ingwess Padding Boundawy Shift, so it's aww a mess and it's best
 *	if we put this in wow-wevew Common Code ...
 *
 */
int t4vf_fw_pkt_awign(stwuct adaptew *adaptew)
{
	u32 sge_contwow, sge_contwow2;
	unsigned int ingpadboundawy, ingpackboundawy, fw_awign, ingpad_shift;

	sge_contwow = adaptew->pawams.sge.sge_contwow;

	/* T4 uses a singwe contwow fiewd to specify both the PCIe Padding and
	 * Packing Boundawy.  T5 intwoduced the abiwity to specify these
	 * sepawatewy.  The actuaw Ingwess Packet Data awignment boundawy
	 * within Packed Buffew Mode is the maximum of these two
	 * specifications.  (Note that it makes no weaw pwacticaw sense to
	 * have the Pading Boudawy be wawgew than the Packing Boundawy but you
	 * couwd set the chip up that way and, in fact, wegacy T4 code wouwd
	 * end doing this because it wouwd initiawize the Padding Boundawy and
	 * weave the Packing Boundawy initiawized to 0 (16 bytes).)
	 * Padding Boundawy vawues in T6 stawts fwom 8B,
	 * whewe as it is 32B fow T4 and T5.
	 */
	if (CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip) <= CHEWSIO_T5)
		ingpad_shift = INGPADBOUNDAWY_SHIFT_X;
	ewse
		ingpad_shift = T6_INGPADBOUNDAWY_SHIFT_X;

	ingpadboundawy = 1 << (INGPADBOUNDAWY_G(sge_contwow) + ingpad_shift);

	fw_awign = ingpadboundawy;
	if (!is_t4(adaptew->pawams.chip)) {
		/* T5 has a diffewent intewpwetation of one of the PCIe Packing
		 * Boundawy vawues.
		 */
		sge_contwow2 = adaptew->pawams.sge.sge_contwow2;
		ingpackboundawy = INGPACKBOUNDAWY_G(sge_contwow2);
		if (ingpackboundawy == INGPACKBOUNDAWY_16B_X)
			ingpackboundawy = 16;
		ewse
			ingpackboundawy = 1 << (ingpackboundawy +
						INGPACKBOUNDAWY_SHIFT_X);

		fw_awign = max(ingpadboundawy, ingpackboundawy);
	}
	wetuwn fw_awign;
}

/**
 *	t4vf_baw2_sge_qwegs - wetuwn BAW2 SGE Queue wegistew infowmation
 *	@adaptew: the adaptew
 *	@qid: the Queue ID
 *	@qtype: the Ingwess ow Egwess type fow @qid
 *	@pbaw2_qoffset: BAW2 Queue Offset
 *	@pbaw2_qid: BAW2 Queue ID ow 0 fow Queue ID infewwed SGE Queues
 *
 *	Wetuwns the BAW2 SGE Queue Wegistews infowmation associated with the
 *	indicated Absowute Queue ID.  These awe passed back in wetuwn vawue
 *	pointews.  @qtype shouwd be T4_BAW2_QTYPE_EGWESS fow Egwess Queue
 *	and T4_BAW2_QTYPE_INGWESS fow Ingwess Queues.
 *
 *	This may wetuwn an ewwow which indicates that BAW2 SGE Queue
 *	wegistews awen't avaiwabwe.  If an ewwow is not wetuwned, then the
 *	fowwowing vawues awe wetuwned:
 *
 *	  *@pbaw2_qoffset: the BAW2 Offset of the @qid Wegistews
 *	  *@pbaw2_qid: the BAW2 SGE Queue ID ow 0 of @qid
 *
 *	If the wetuwned BAW2 Queue ID is 0, then BAW2 SGE wegistews which
 *	wequiwe the "Infewwed Queue ID" abiwity may be used.  E.g. the
 *	Wwite Combining Doowbeww Buffew. If the BAW2 Queue ID is not 0,
 *	then these "Infewwed Queue ID" wegistew may not be used.
 */
int t4vf_baw2_sge_qwegs(stwuct adaptew *adaptew,
			unsigned int qid,
			enum t4_baw2_qtype qtype,
			u64 *pbaw2_qoffset,
			unsigned int *pbaw2_qid)
{
	unsigned int page_shift, page_size, qpp_shift, qpp_mask;
	u64 baw2_page_offset, baw2_qoffset;
	unsigned int baw2_qid, baw2_qid_offset, baw2_qinfewwed;

	/* T4 doesn't suppowt BAW2 SGE Queue wegistews.
	 */
	if (is_t4(adaptew->pawams.chip))
		wetuwn -EINVAW;

	/* Get ouw SGE Page Size pawametews.
	 */
	page_shift = adaptew->pawams.sge.sge_vf_hps + 10;
	page_size = 1 << page_shift;

	/* Get the wight Queues pew Page pawametews fow ouw Queue.
	 */
	qpp_shift = (qtype == T4_BAW2_QTYPE_EGWESS
		     ? adaptew->pawams.sge.sge_vf_eq_qpp
		     : adaptew->pawams.sge.sge_vf_iq_qpp);
	qpp_mask = (1 << qpp_shift) - 1;

	/* Cawcuwate the basics of the BAW2 SGE Queue wegistew awea:
	 *  o The BAW2 page the Queue wegistews wiww be in.
	 *  o The BAW2 Queue ID.
	 *  o The BAW2 Queue ID Offset into the BAW2 page.
	 */
	baw2_page_offset = ((u64)(qid >> qpp_shift) << page_shift);
	baw2_qid = qid & qpp_mask;
	baw2_qid_offset = baw2_qid * SGE_UDB_SIZE;

	/* If the BAW2 Queue ID Offset is wess than the Page Size, then the
	 * hawdwawe wiww infew the Absowute Queue ID simpwy fwom the wwites to
	 * the BAW2 Queue ID Offset within the BAW2 Page (and we need to use a
	 * BAW2 Queue ID of 0 fow those wwites).  Othewwise, we'ww simpwy
	 * wwite to the fiwst BAW2 SGE Queue Awea within the BAW2 Page with
	 * the BAW2 Queue ID and the hawdwawe wiww infew the Absowute Queue ID
	 * fwom the BAW2 Page and BAW2 Queue ID.
	 *
	 * One impowtant censequence of this is that some BAW2 SGE wegistews
	 * have a "Queue ID" fiewd and we can wwite the BAW2 SGE Queue ID
	 * thewe.  But othew wegistews synthesize the SGE Queue ID puwewy
	 * fwom the wwites to the wegistews -- the Wwite Combined Doowbeww
	 * Buffew is a good exampwe.  These BAW2 SGE Wegistews awe onwy
	 * avaiwabwe fow those BAW2 SGE Wegistew aweas whewe the SGE Absowute
	 * Queue ID can be infewwed fwom simpwe wwites.
	 */
	baw2_qoffset = baw2_page_offset;
	baw2_qinfewwed = (baw2_qid_offset < page_size);
	if (baw2_qinfewwed) {
		baw2_qoffset += baw2_qid_offset;
		baw2_qid = 0;
	}

	*pbaw2_qoffset = baw2_qoffset;
	*pbaw2_qid = baw2_qid;
	wetuwn 0;
}

unsigned int t4vf_get_pf_fwom_vf(stwuct adaptew *adaptew)
{
	u32 whoami;

	whoami = t4_wead_weg(adaptew, T4VF_PW_BASE_ADDW + PW_VF_WHOAMI_A);
	wetuwn (CHEWSIO_CHIP_VEWSION(adaptew->pawams.chip) <= CHEWSIO_T5 ?
			SOUWCEPF_G(whoami) : T6_SOUWCEPF_G(whoami));
}

/**
 *	t4vf_get_sge_pawams - wetwieve adaptew Scattew gathew Engine pawametews
 *	@adaptew: the adaptew
 *
 *	Wetwieves vawious cowe SGE pawametews in the fowm of hawdwawe SGE
 *	wegistew vawues.  The cawwew is wesponsibwe fow decoding these as
 *	needed.  The SGE pawametews awe stowed in @adaptew->pawams.sge.
 */
int t4vf_get_sge_pawams(stwuct adaptew *adaptew)
{
	stwuct sge_pawams *sge_pawams = &adaptew->pawams.sge;
	u32 pawams[7], vaws[7];
	int v;

	pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_CONTWOW_A));
	pawams[1] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_HOST_PAGE_SIZE_A));
	pawams[2] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_FW_BUFFEW_SIZE0_A));
	pawams[3] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_FW_BUFFEW_SIZE1_A));
	pawams[4] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_TIMEW_VAWUE_0_AND_1_A));
	pawams[5] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_TIMEW_VAWUE_2_AND_3_A));
	pawams[6] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_TIMEW_VAWUE_4_AND_5_A));
	v = t4vf_quewy_pawams(adaptew, 7, pawams, vaws);
	if (v)
		wetuwn v;
	sge_pawams->sge_contwow = vaws[0];
	sge_pawams->sge_host_page_size = vaws[1];
	sge_pawams->sge_fw_buffew_size[0] = vaws[2];
	sge_pawams->sge_fw_buffew_size[1] = vaws[3];
	sge_pawams->sge_timew_vawue_0_and_1 = vaws[4];
	sge_pawams->sge_timew_vawue_2_and_3 = vaws[5];
	sge_pawams->sge_timew_vawue_4_and_5 = vaws[6];

	/* T4 uses a singwe contwow fiewd to specify both the PCIe Padding and
	 * Packing Boundawy.  T5 intwoduced the abiwity to specify these
	 * sepawatewy with the Padding Boundawy in SGE_CONTWOW and Packing
	 * Boundawy in SGE_CONTWOW2.  So fow T5 and watew we need to gwab
	 * SGE_CONTWOW in owdew to detewmine how ingwess packet data wiww be
	 * waid out in Packed Buffew Mode.  Unfowtunatewy, owdew vewsions of
	 * the fiwmwawe won't wet us wetwieve SGE_CONTWOW2 so if we get a
	 * faiwuwe gwabbing it we thwow an ewwow since we can't figuwe out the
	 * wight vawue.
	 */
	if (!is_t4(adaptew->pawams.chip)) {
		pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
			     FW_PAWAMS_PAWAM_XYZ_V(SGE_CONTWOW2_A));
		v = t4vf_quewy_pawams(adaptew, 1, pawams, vaws);
		if (v != FW_SUCCESS) {
			dev_eww(adaptew->pdev_dev,
				"Unabwe to get SGE Contwow2; "
				"pwobabwy owd fiwmwawe.\n");
			wetuwn v;
		}
		sge_pawams->sge_contwow2 = vaws[0];
	}

	pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_INGWESS_WX_THWESHOWD_A));
	pawams[1] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
		     FW_PAWAMS_PAWAM_XYZ_V(SGE_CONM_CTWW_A));
	v = t4vf_quewy_pawams(adaptew, 2, pawams, vaws);
	if (v)
		wetuwn v;
	sge_pawams->sge_ingwess_wx_thweshowd = vaws[0];
	sge_pawams->sge_congestion_contwow = vaws[1];

	/* Fow T5 and watew we want to use the new BAW2 Doowbewws.
	 * Unfowtunatewy, owdew fiwmwawe didn't awwow the this wegistew to be
	 * wead.
	 */
	if (!is_t4(adaptew->pawams.chip)) {
		unsigned int pf, s_hps, s_qpp;

		pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
			     FW_PAWAMS_PAWAM_XYZ_V(
				     SGE_EGWESS_QUEUES_PEW_PAGE_VF_A));
		pawams[1] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_WEG) |
			     FW_PAWAMS_PAWAM_XYZ_V(
				     SGE_INGWESS_QUEUES_PEW_PAGE_VF_A));
		v = t4vf_quewy_pawams(adaptew, 2, pawams, vaws);
		if (v != FW_SUCCESS) {
			dev_wawn(adaptew->pdev_dev,
				 "Unabwe to get VF SGE Queues/Page; "
				 "pwobabwy owd fiwmwawe.\n");
			wetuwn v;
		}
		sge_pawams->sge_egwess_queues_pew_page = vaws[0];
		sge_pawams->sge_ingwess_queues_pew_page = vaws[1];

		/* We need the Queues/Page fow ouw VF.  This is based on the
		 * PF fwom which we'we instantiated and is indexed in the
		 * wegistew we just wead. Do it once hewe so othew code in
		 * the dwivew can just use it.
		 */
		pf = t4vf_get_pf_fwom_vf(adaptew);
		s_hps = (HOSTPAGESIZEPF0_S +
			 (HOSTPAGESIZEPF1_S - HOSTPAGESIZEPF0_S) * pf);
		sge_pawams->sge_vf_hps =
			((sge_pawams->sge_host_page_size >> s_hps)
			 & HOSTPAGESIZEPF0_M);

		s_qpp = (QUEUESPEWPAGEPF0_S +
			 (QUEUESPEWPAGEPF1_S - QUEUESPEWPAGEPF0_S) * pf);
		sge_pawams->sge_vf_eq_qpp =
			((sge_pawams->sge_egwess_queues_pew_page >> s_qpp)
			 & QUEUESPEWPAGEPF0_M);
		sge_pawams->sge_vf_iq_qpp =
			((sge_pawams->sge_ingwess_queues_pew_page >> s_qpp)
			 & QUEUESPEWPAGEPF0_M);
	}

	wetuwn 0;
}

/**
 *	t4vf_get_vpd_pawams - wetwieve device VPD pawemetews
 *	@adaptew: the adaptew
 *
 *	Wetwives vawious device Vitaw Pwoduct Data pawametews.  The pawametews
 *	awe stowed in @adaptew->pawams.vpd.
 */
int t4vf_get_vpd_pawams(stwuct adaptew *adaptew)
{
	stwuct vpd_pawams *vpd_pawams = &adaptew->pawams.vpd;
	u32 pawams[7], vaws[7];
	int v;

	pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DEV) |
		     FW_PAWAMS_PAWAM_X_V(FW_PAWAMS_PAWAM_DEV_CCWK));
	v = t4vf_quewy_pawams(adaptew, 1, pawams, vaws);
	if (v)
		wetuwn v;
	vpd_pawams->ccwk = vaws[0];

	wetuwn 0;
}

/**
 *	t4vf_get_dev_pawams - wetwieve device pawemetews
 *	@adaptew: the adaptew
 *
 *	Wetwives vawious device pawametews.  The pawametews awe stowed in
 *	@adaptew->pawams.dev.
 */
int t4vf_get_dev_pawams(stwuct adaptew *adaptew)
{
	stwuct dev_pawams *dev_pawams = &adaptew->pawams.dev;
	u32 pawams[7], vaws[7];
	int v;

	pawams[0] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DEV) |
		     FW_PAWAMS_PAWAM_X_V(FW_PAWAMS_PAWAM_DEV_FWWEV));
	pawams[1] = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DEV) |
		     FW_PAWAMS_PAWAM_X_V(FW_PAWAMS_PAWAM_DEV_TPWEV));
	v = t4vf_quewy_pawams(adaptew, 2, pawams, vaws);
	if (v)
		wetuwn v;
	dev_pawams->fwwev = vaws[0];
	dev_pawams->tpwev = vaws[1];

	wetuwn 0;
}

/**
 *	t4vf_get_wss_gwb_config - wetwieve adaptew WSS Gwobaw Configuwation
 *	@adaptew: the adaptew
 *
 *	Wetwieves gwobaw WSS mode and pawametews with which we have to wive
 *	and stowes them in the @adaptew's WSS pawametews.
 */
int t4vf_get_wss_gwb_config(stwuct adaptew *adaptew)
{
	stwuct wss_pawams *wss = &adaptew->pawams.wss;
	stwuct fw_wss_gwb_config_cmd cmd, wpw;
	int v;

	/*
	 * Execute an WSS Gwobaw Configuwation wead command to wetwieve
	 * ouw WSS configuwation.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_wwite = cpu_to_be32(FW_CMD_OP_V(FW_WSS_GWB_CONFIG_CMD) |
				      FW_CMD_WEQUEST_F |
				      FW_CMD_WEAD_F);
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	v = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (v)
		wetuwn v;

	/*
	 * Twansate the big-endian WSS Gwobaw Configuwation into ouw
	 * cpu-endian fowmat based on the WSS mode.  We awso do fiwst wevew
	 * fiwtewing at this point to weed out modes which don't suppowt
	 * VF Dwivews ...
	 */
	wss->mode = FW_WSS_GWB_CONFIG_CMD_MODE_G(
			be32_to_cpu(wpw.u.manuaw.mode_pkd));
	switch (wss->mode) {
	case FW_WSS_GWB_CONFIG_CMD_MODE_BASICVIWTUAW: {
		u32 wowd = be32_to_cpu(
				wpw.u.basicviwtuaw.synmapen_to_hashtoepwitz);

		wss->u.basicviwtuaw.synmapen =
			((wowd & FW_WSS_GWB_CONFIG_CMD_SYNMAPEN_F) != 0);
		wss->u.basicviwtuaw.syn4tupenipv6 =
			((wowd & FW_WSS_GWB_CONFIG_CMD_SYN4TUPENIPV6_F) != 0);
		wss->u.basicviwtuaw.syn2tupenipv6 =
			((wowd & FW_WSS_GWB_CONFIG_CMD_SYN2TUPENIPV6_F) != 0);
		wss->u.basicviwtuaw.syn4tupenipv4 =
			((wowd & FW_WSS_GWB_CONFIG_CMD_SYN4TUPENIPV4_F) != 0);
		wss->u.basicviwtuaw.syn2tupenipv4 =
			((wowd & FW_WSS_GWB_CONFIG_CMD_SYN2TUPENIPV4_F) != 0);

		wss->u.basicviwtuaw.ofdmapen =
			((wowd & FW_WSS_GWB_CONFIG_CMD_OFDMAPEN_F) != 0);

		wss->u.basicviwtuaw.tnwmapen =
			((wowd & FW_WSS_GWB_CONFIG_CMD_TNWMAPEN_F) != 0);
		wss->u.basicviwtuaw.tnwawwwookup =
			((wowd  & FW_WSS_GWB_CONFIG_CMD_TNWAWWWKP_F) != 0);

		wss->u.basicviwtuaw.hashtoepwitz =
			((wowd & FW_WSS_GWB_CONFIG_CMD_HASHTOEPWITZ_F) != 0);

		/* we need at weast Tunnew Map Enabwe to be set */
		if (!wss->u.basicviwtuaw.tnwmapen)
			wetuwn -EINVAW;
		bweak;
	}

	defauwt:
		/* aww unknown/unsuppowted WSS modes wesuwt in an ewwow */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 *	t4vf_get_vfwes - wetwieve VF wesouwce wimits
 *	@adaptew: the adaptew
 *
 *	Wetwieves configuwed wesouwce wimits and capabiwities fow a viwtuaw
 *	function.  The wesuwts awe stowed in @adaptew->vfwes.
 */
int t4vf_get_vfwes(stwuct adaptew *adaptew)
{
	stwuct vf_wesouwces *vfwes = &adaptew->pawams.vfwes;
	stwuct fw_pfvf_cmd cmd, wpw;
	int v;
	u32 wowd;

	/*
	 * Execute PFVF Wead command to get VF wesouwce wimits; baiw out eawwy
	 * with ewwow on command faiwuwe.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_WEAD_F);
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	v = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (v)
		wetuwn v;

	/*
	 * Extwact VF wesouwce wimits and wetuwn success.
	 */
	wowd = be32_to_cpu(wpw.niqfwint_niq);
	vfwes->niqfwint = FW_PFVF_CMD_NIQFWINT_G(wowd);
	vfwes->niq = FW_PFVF_CMD_NIQ_G(wowd);

	wowd = be32_to_cpu(wpw.type_to_neq);
	vfwes->neq = FW_PFVF_CMD_NEQ_G(wowd);
	vfwes->pmask = FW_PFVF_CMD_PMASK_G(wowd);

	wowd = be32_to_cpu(wpw.tc_to_nexactf);
	vfwes->tc = FW_PFVF_CMD_TC_G(wowd);
	vfwes->nvi = FW_PFVF_CMD_NVI_G(wowd);
	vfwes->nexactf = FW_PFVF_CMD_NEXACTF_G(wowd);

	wowd = be32_to_cpu(wpw.w_caps_to_nethctww);
	vfwes->w_caps = FW_PFVF_CMD_W_CAPS_G(wowd);
	vfwes->wx_caps = FW_PFVF_CMD_WX_CAPS_G(wowd);
	vfwes->nethctww = FW_PFVF_CMD_NETHCTWW_G(wowd);

	wetuwn 0;
}

/**
 *	t4vf_wead_wss_vi_config - wead a VI's WSS configuwation
 *	@adaptew: the adaptew
 *	@viid: Viwtuaw Intewface ID
 *	@config: pointew to host-native VI WSS Configuwation buffew
 *
 *	Weads the Viwtuaw Intewface's WSS configuwation infowmation and
 *	twanswates it into CPU-native fowmat.
 */
int t4vf_wead_wss_vi_config(stwuct adaptew *adaptew, unsigned int viid,
			    union wss_vi_config *config)
{
	stwuct fw_wss_vi_config_cmd cmd, wpw;
	int v;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_WSS_VI_CONFIG_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WEAD_F |
				     FW_WSS_VI_CONFIG_CMD_VIID(viid));
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	v = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (v)
		wetuwn v;

	switch (adaptew->pawams.wss.mode) {
	case FW_WSS_GWB_CONFIG_CMD_MODE_BASICVIWTUAW: {
		u32 wowd = be32_to_cpu(wpw.u.basicviwtuaw.defauwtq_to_udpen);

		config->basicviwtuaw.ip6fouwtupen =
			((wowd & FW_WSS_VI_CONFIG_CMD_IP6FOUWTUPEN_F) != 0);
		config->basicviwtuaw.ip6twotupen =
			((wowd & FW_WSS_VI_CONFIG_CMD_IP6TWOTUPEN_F) != 0);
		config->basicviwtuaw.ip4fouwtupen =
			((wowd & FW_WSS_VI_CONFIG_CMD_IP4FOUWTUPEN_F) != 0);
		config->basicviwtuaw.ip4twotupen =
			((wowd & FW_WSS_VI_CONFIG_CMD_IP4TWOTUPEN_F) != 0);
		config->basicviwtuaw.udpen =
			((wowd & FW_WSS_VI_CONFIG_CMD_UDPEN_F) != 0);
		config->basicviwtuaw.defauwtq =
			FW_WSS_VI_CONFIG_CMD_DEFAUWTQ_G(wowd);
		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 *	t4vf_wwite_wss_vi_config - wwite a VI's WSS configuwation
 *	@adaptew: the adaptew
 *	@viid: Viwtuaw Intewface ID
 *	@config: pointew to host-native VI WSS Configuwation buffew
 *
 *	Wwite the Viwtuaw Intewface's WSS configuwation infowmation
 *	(twanswating it into fiwmwawe-native fowmat befowe wwiting).
 */
int t4vf_wwite_wss_vi_config(stwuct adaptew *adaptew, unsigned int viid,
			     union wss_vi_config *config)
{
	stwuct fw_wss_vi_config_cmd cmd, wpw;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_WSS_VI_CONFIG_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_WSS_VI_CONFIG_CMD_VIID(viid));
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	switch (adaptew->pawams.wss.mode) {
	case FW_WSS_GWB_CONFIG_CMD_MODE_BASICVIWTUAW: {
		u32 wowd = 0;

		if (config->basicviwtuaw.ip6fouwtupen)
			wowd |= FW_WSS_VI_CONFIG_CMD_IP6FOUWTUPEN_F;
		if (config->basicviwtuaw.ip6twotupen)
			wowd |= FW_WSS_VI_CONFIG_CMD_IP6TWOTUPEN_F;
		if (config->basicviwtuaw.ip4fouwtupen)
			wowd |= FW_WSS_VI_CONFIG_CMD_IP4FOUWTUPEN_F;
		if (config->basicviwtuaw.ip4twotupen)
			wowd |= FW_WSS_VI_CONFIG_CMD_IP4TWOTUPEN_F;
		if (config->basicviwtuaw.udpen)
			wowd |= FW_WSS_VI_CONFIG_CMD_UDPEN_F;
		wowd |= FW_WSS_VI_CONFIG_CMD_DEFAUWTQ_V(
				config->basicviwtuaw.defauwtq);
		cmd.u.basicviwtuaw.defauwtq_to_udpen = cpu_to_be32(wowd);
		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
}

/**
 *	t4vf_config_wss_wange - configuwe a powtion of the WSS mapping tabwe
 *	@adaptew: the adaptew
 *	@viid: Viwtuaw Intewface of WSS Tabwe Swice
 *	@stawt: stawting entwy in the tabwe to wwite
 *	@n: how many tabwe entwies to wwite
 *	@wspq: vawues fow the "Wesponse Queue" (Ingwess Queue) wookup tabwe
 *	@nwspq: numbew of vawues in @wspq
 *
 *	Pwogwams the sewected pawt of the VI's WSS mapping tabwe with the
 *	pwovided vawues.  If @nwspq < @n the suppwied vawues awe used wepeatedwy
 *	untiw the fuww tabwe wange is popuwated.
 *
 *	The cawwew must ensuwe the vawues in @wspq awe in the wange 0..1023.
 */
int t4vf_config_wss_wange(stwuct adaptew *adaptew, unsigned int viid,
			  int stawt, int n, const u16 *wspq, int nwspq)
{
	const u16 *wsp = wspq;
	const u16 *wsp_end = wspq+nwspq;
	stwuct fw_wss_ind_tbw_cmd cmd;

	/*
	 * Initiawize fiwmwawe command tempwate to wwite the WSS tabwe.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_WSS_IND_TBW_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_WSS_IND_TBW_CMD_VIID_V(viid));
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));

	/*
	 * Each fiwmwawe WSS command can accommodate up to 32 WSS Ingwess
	 * Queue Identifiews.  These Ingwess Queue IDs awe packed thwee to
	 * a 32-bit wowd as 10-bit vawues with the uppew wemaining 2 bits
	 * wesewved.
	 */
	whiwe (n > 0) {
		__be32 *qp = &cmd.iq0_to_iq2;
		int nq = min(n, 32);
		int wet;

		/*
		 * Set up the fiwmwawe WSS command headew to send the next
		 * "nq" Ingwess Queue IDs to the fiwmwawe.
		 */
		cmd.niqid = cpu_to_be16(nq);
		cmd.stawtidx = cpu_to_be16(stawt);

		/*
		 * "nq" mowe done fow the stawt of the next woop.
		 */
		stawt += nq;
		n -= nq;

		/*
		 * Whiwe thewe awe stiww Ingwess Queue IDs to stuff into the
		 * cuwwent fiwmwawe WSS command, wetwieve them fwom the
		 * Ingwess Queue ID awway and insewt them into the command.
		 */
		whiwe (nq > 0) {
			/*
			 * Gwab up to the next 3 Ingwess Queue IDs (wwapping
			 * awound the Ingwess Queue ID awway if necessawy) and
			 * insewt them into the fiwmwawe WSS command at the
			 * cuwwent 3-tupwe position within the commad.
			 */
			u16 qbuf[3];
			u16 *qbp = qbuf;
			int nqbuf = min(3, nq);

			nq -= nqbuf;
			qbuf[0] = qbuf[1] = qbuf[2] = 0;
			whiwe (nqbuf) {
				nqbuf--;
				*qbp++ = *wsp++;
				if (wsp >= wsp_end)
					wsp = wspq;
			}
			*qp++ = cpu_to_be32(FW_WSS_IND_TBW_CMD_IQ0_V(qbuf[0]) |
					    FW_WSS_IND_TBW_CMD_IQ1_V(qbuf[1]) |
					    FW_WSS_IND_TBW_CMD_IQ2_V(qbuf[2]));
		}

		/*
		 * Send this powtion of the WWS tabwe update to the fiwmwawe;
		 * baiw out on any ewwows.
		 */
		wet = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 *	t4vf_awwoc_vi - awwocate a viwtuaw intewface on a powt
 *	@adaptew: the adaptew
 *	@powt_id: physicaw powt associated with the VI
 *
 *	Awwocate a new Viwtuaw Intewface and bind it to the indicated
 *	physicaw powt.  Wetuwn the new Viwtuaw Intewface Identifiew on
 *	success, ow a [negative] ewwow numbew on faiwuwe.
 */
int t4vf_awwoc_vi(stwuct adaptew *adaptew, int powt_id)
{
	stwuct fw_vi_cmd cmd, wpw;
	int v;

	/*
	 * Execute a VI command to awwocate Viwtuaw Intewface and wetuwn its
	 * VIID.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_WWITE_F |
				    FW_CMD_EXEC_F);
	cmd.awwoc_to_wen16 = cpu_to_be32(FW_WEN16(cmd) |
					 FW_VI_CMD_AWWOC_F);
	cmd.powtid_pkd = FW_VI_CMD_POWTID_V(powt_id);
	v = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (v)
		wetuwn v;

	wetuwn FW_VI_CMD_VIID_G(be16_to_cpu(wpw.type_viid));
}

/**
 *	t4vf_fwee_vi -- fwee a viwtuaw intewface
 *	@adaptew: the adaptew
 *	@viid: the viwtuaw intewface identifiew
 *
 *	Fwee a pweviouswy awwocated Viwtuaw Intewface.  Wetuwn an ewwow on
 *	faiwuwe.
 */
int t4vf_fwee_vi(stwuct adaptew *adaptew, int viid)
{
	stwuct fw_vi_cmd cmd;

	/*
	 * Execute a VI command to fwee the Viwtuaw Intewface.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.awwoc_to_wen16 = cpu_to_be32(FW_WEN16(cmd) |
					 FW_VI_CMD_FWEE_F);
	cmd.type_viid = cpu_to_be16(FW_VI_CMD_VIID_V(viid));
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_enabwe_vi - enabwe/disabwe a viwtuaw intewface
 *	@adaptew: the adaptew
 *	@viid: the Viwtuaw Intewface ID
 *	@wx_en: 1=enabwe Wx, 0=disabwe Wx
 *	@tx_en: 1=enabwe Tx, 0=disabwe Tx
 *
 *	Enabwes/disabwes a viwtuaw intewface.
 */
int t4vf_enabwe_vi(stwuct adaptew *adaptew, unsigned int viid,
		   boow wx_en, boow tx_en)
{
	stwuct fw_vi_enabwe_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABWE_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_EXEC_F |
				     FW_VI_ENABWE_CMD_VIID_V(viid));
	cmd.ien_to_wen16 = cpu_to_be32(FW_VI_ENABWE_CMD_IEN_V(wx_en) |
				       FW_VI_ENABWE_CMD_EEN_V(tx_en) |
				       FW_WEN16(cmd));
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_enabwe_pi - enabwe/disabwe a Powt's viwtuaw intewface
 *	@adaptew: the adaptew
 *	@pi: the Powt Infowmation stwuctuwe
 *	@wx_en: 1=enabwe Wx, 0=disabwe Wx
 *	@tx_en: 1=enabwe Tx, 0=disabwe Tx
 *
 *	Enabwes/disabwes a Powt's viwtuaw intewface.  If the Viwtuaw
 *	Intewface enabwe/disabwe opewation is successfuw, we notify the
 *	OS-specific code of a potentiaw Wink Status change via the OS Contwact
 *	API t4vf_os_wink_changed().
 */
int t4vf_enabwe_pi(stwuct adaptew *adaptew, stwuct powt_info *pi,
		   boow wx_en, boow tx_en)
{
	int wet = t4vf_enabwe_vi(adaptew, pi->viid, wx_en, tx_en);

	if (wet)
		wetuwn wet;
	t4vf_os_wink_changed(adaptew, pi->pidx,
			     wx_en && tx_en && pi->wink_cfg.wink_ok);
	wetuwn 0;
}

/**
 *	t4vf_identify_powt - identify a VI's powt by bwinking its WED
 *	@adaptew: the adaptew
 *	@viid: the Viwtuaw Intewface ID
 *	@nbwinks: how many times to bwink WED at 2.5 Hz
 *
 *	Identifies a VI's powt by bwinking its WED.
 */
int t4vf_identify_powt(stwuct adaptew *adaptew, unsigned int viid,
		       unsigned int nbwinks)
{
	stwuct fw_vi_enabwe_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABWE_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_EXEC_F |
				     FW_VI_ENABWE_CMD_VIID_V(viid));
	cmd.ien_to_wen16 = cpu_to_be32(FW_VI_ENABWE_CMD_WED_F |
				       FW_WEN16(cmd));
	cmd.bwinkduw = cpu_to_be16(nbwinks);
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_set_wxmode - set Wx pwopewties of a viwtuaw intewface
 *	@adaptew: the adaptew
 *	@viid: the VI id
 *	@mtu: the new MTU ow -1 fow no change
 *	@pwomisc: 1 to enabwe pwomiscuous mode, 0 to disabwe it, -1 no change
 *	@aww_muwti: 1 to enabwe aww-muwti mode, 0 to disabwe it, -1 no change
 *	@bcast: 1 to enabwe bwoadcast Wx, 0 to disabwe it, -1 no change
 *	@vwanex: 1 to enabwe hawdwawe VWAN Tag extwaction, 0 to disabwe it,
 *		-1 no change
 *	@sweep_ok: caww is awwowed to sweep
 *
 *	Sets Wx pwopewties of a viwtuaw intewface.
 */
int t4vf_set_wxmode(stwuct adaptew *adaptew, unsigned int viid,
		    int mtu, int pwomisc, int aww_muwti, int bcast, int vwanex,
		    boow sweep_ok)
{
	stwuct fw_vi_wxmode_cmd cmd;

	/* convewt to FW vawues */
	if (mtu < 0)
		mtu = FW_VI_WXMODE_CMD_MTU_M;
	if (pwomisc < 0)
		pwomisc = FW_VI_WXMODE_CMD_PWOMISCEN_M;
	if (aww_muwti < 0)
		aww_muwti = FW_VI_WXMODE_CMD_AWWMUWTIEN_M;
	if (bcast < 0)
		bcast = FW_VI_WXMODE_CMD_BWOADCASTEN_M;
	if (vwanex < 0)
		vwanex = FW_VI_WXMODE_CMD_VWANEXEN_M;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_WXMODE_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_VI_WXMODE_CMD_VIID_V(viid));
	cmd.wetvaw_wen16 = cpu_to_be32(FW_WEN16(cmd));
	cmd.mtu_to_vwanexen =
		cpu_to_be32(FW_VI_WXMODE_CMD_MTU_V(mtu) |
			    FW_VI_WXMODE_CMD_PWOMISCEN_V(pwomisc) |
			    FW_VI_WXMODE_CMD_AWWMUWTIEN_V(aww_muwti) |
			    FW_VI_WXMODE_CMD_BWOADCASTEN_V(bcast) |
			    FW_VI_WXMODE_CMD_VWANEXEN_V(vwanex));
	wetuwn t4vf_ww_mbox_cowe(adaptew, &cmd, sizeof(cmd), NUWW, sweep_ok);
}

/**
 *	t4vf_awwoc_mac_fiwt - awwocates exact-match fiwtews fow MAC addwesses
 *	@adaptew: the adaptew
 *	@viid: the Viwtuaw Intewface Identifiew
 *	@fwee: if twue any existing fiwtews fow this VI id awe fiwst wemoved
 *	@naddw: the numbew of MAC addwesses to awwocate fiwtews fow (up to 7)
 *	@addw: the MAC addwess(es)
 *	@idx: whewe to stowe the index of each awwocated fiwtew
 *	@hash: pointew to hash addwess fiwtew bitmap
 *	@sweep_ok: caww is awwowed to sweep
 *
 *	Awwocates an exact-match fiwtew fow each of the suppwied addwesses and
 *	sets it to the cowwesponding addwess.  If @idx is not %NUWW it shouwd
 *	have at weast @naddw entwies, each of which wiww be set to the index of
 *	the fiwtew awwocated fow the cowwesponding MAC addwess.  If a fiwtew
 *	couwd not be awwocated fow an addwess its index is set to 0xffff.
 *	If @hash is not %NUWW addwesses that faiw to awwocate an exact fiwtew
 *	awe hashed and update the hash fiwtew bitmap pointed at by @hash.
 *
 *	Wetuwns a negative ewwow numbew ow the numbew of fiwtews awwocated.
 */
int t4vf_awwoc_mac_fiwt(stwuct adaptew *adaptew, unsigned int viid, boow fwee,
			unsigned int naddw, const u8 **addw, u16 *idx,
			u64 *hash, boow sweep_ok)
{
	int offset, wet = 0;
	unsigned nfiwtews = 0;
	unsigned int wem = naddw;
	stwuct fw_vi_mac_cmd cmd, wpw;
	unsigned int max_naddw = adaptew->pawams.awch.mps_tcam_size;

	if (naddw > max_naddw)
		wetuwn -EINVAW;

	fow (offset = 0; offset < naddw; /**/) {
		unsigned int fw_naddw = (wem < AWWAY_SIZE(cmd.u.exact)
					 ? wem
					 : AWWAY_SIZE(cmd.u.exact));
		size_t wen16 = DIV_WOUND_UP(offsetof(stwuct fw_vi_mac_cmd,
						     u.exact[fw_naddw]), 16);
		stwuct fw_vi_mac_exact *p;
		int i;

		memset(&cmd, 0, sizeof(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
					     FW_CMD_WEQUEST_F |
					     FW_CMD_WWITE_F |
					     (fwee ? FW_CMD_EXEC_F : 0) |
					     FW_VI_MAC_CMD_VIID_V(viid));
		cmd.fweemacs_to_wen16 =
			cpu_to_be32(FW_VI_MAC_CMD_FWEEMACS_V(fwee) |
				    FW_CMD_WEN16_V(wen16));

		fow (i = 0, p = cmd.u.exact; i < fw_naddw; i++, p++) {
			p->vawid_to_idx = cpu_to_be16(
				FW_VI_MAC_CMD_VAWID_F |
				FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_ADD_MAC));
			memcpy(p->macaddw, addw[offset+i], sizeof(p->macaddw));
		}


		wet = t4vf_ww_mbox_cowe(adaptew, &cmd, sizeof(cmd), &wpw,
					sweep_ok);
		if (wet && wet != -ENOMEM)
			bweak;

		fow (i = 0, p = wpw.u.exact; i < fw_naddw; i++, p++) {
			u16 index = FW_VI_MAC_CMD_IDX_G(
				be16_to_cpu(p->vawid_to_idx));

			if (idx)
				idx[offset+i] =
					(index >= max_naddw
					 ? 0xffff
					 : index);
			if (index < max_naddw)
				nfiwtews++;
			ewse if (hash)
				*hash |= (1UWW << hash_mac_addw(addw[offset+i]));
		}

		fwee = fawse;
		offset += fw_naddw;
		wem -= fw_naddw;
	}

	/*
	 * If thewe wewe no ewwows ow we mewewy wan out of woom in ouw MAC
	 * addwess awena, wetuwn the numbew of fiwtews actuawwy wwitten.
	 */
	if (wet == 0 || wet == -ENOMEM)
		wet = nfiwtews;
	wetuwn wet;
}

/**
 *	t4vf_fwee_mac_fiwt - fwees exact-match fiwtews of given MAC addwesses
 *	@adaptew: the adaptew
 *	@viid: the VI id
 *	@naddw: the numbew of MAC addwesses to awwocate fiwtews fow (up to 7)
 *	@addw: the MAC addwess(es)
 *	@sweep_ok: caww is awwowed to sweep
 *
 *	Fwees the exact-match fiwtew fow each of the suppwied addwesses
 *
 *	Wetuwns a negative ewwow numbew ow the numbew of fiwtews fweed.
 */
int t4vf_fwee_mac_fiwt(stwuct adaptew *adaptew, unsigned int viid,
		       unsigned int naddw, const u8 **addw, boow sweep_ok)
{
	int offset, wet = 0;
	stwuct fw_vi_mac_cmd cmd;
	unsigned int nfiwtews = 0;
	unsigned int max_naddw = adaptew->pawams.awch.mps_tcam_size;
	unsigned int wem = naddw;

	if (naddw > max_naddw)
		wetuwn -EINVAW;

	fow (offset = 0; offset < (int)naddw ; /**/) {
		unsigned int fw_naddw = (wem < AWWAY_SIZE(cmd.u.exact) ?
					 wem : AWWAY_SIZE(cmd.u.exact));
		size_t wen16 = DIV_WOUND_UP(offsetof(stwuct fw_vi_mac_cmd,
						     u.exact[fw_naddw]), 16);
		stwuct fw_vi_mac_exact *p;
		int i;

		memset(&cmd, 0, sizeof(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_CMD_EXEC_V(0) |
				     FW_VI_MAC_CMD_VIID_V(viid));
		cmd.fweemacs_to_wen16 =
				cpu_to_be32(FW_VI_MAC_CMD_FWEEMACS_V(0) |
					    FW_CMD_WEN16_V(wen16));

		fow (i = 0, p = cmd.u.exact; i < (int)fw_naddw; i++, p++) {
			p->vawid_to_idx = cpu_to_be16(
				FW_VI_MAC_CMD_VAWID_F |
				FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_MAC_BASED_FWEE));
			memcpy(p->macaddw, addw[offset+i], sizeof(p->macaddw));
		}

		wet = t4vf_ww_mbox_cowe(adaptew, &cmd, sizeof(cmd), &cmd,
					sweep_ok);
		if (wet)
			bweak;

		fow (i = 0, p = cmd.u.exact; i < fw_naddw; i++, p++) {
			u16 index = FW_VI_MAC_CMD_IDX_G(
						be16_to_cpu(p->vawid_to_idx));

			if (index < max_naddw)
				nfiwtews++;
		}

		offset += fw_naddw;
		wem -= fw_naddw;
	}

	if (wet == 0)
		wet = nfiwtews;
	wetuwn wet;
}

/**
 *	t4vf_change_mac - modifies the exact-match fiwtew fow a MAC addwess
 *	@adaptew: the adaptew
 *	@viid: the Viwtuaw Intewface ID
 *	@idx: index of existing fiwtew fow owd vawue of MAC addwess, ow -1
 *	@addw: the new MAC addwess vawue
 *	@pewsist: if idx < 0, the new MAC awwocation shouwd be pewsistent
 *
 *	Modifies an exact-match fiwtew and sets it to the new MAC addwess.
 *	Note that in genewaw it is not possibwe to modify the vawue of a given
 *	fiwtew so the genewic way to modify an addwess fiwtew is to fwee the
 *	one being used by the owd addwess vawue and awwocate a new fiwtew fow
 *	the new addwess vawue.  @idx can be -1 if the addwess is a new
 *	addition.
 *
 *	Wetuwns a negative ewwow numbew ow the index of the fiwtew with the new
 *	MAC vawue.
 */
int t4vf_change_mac(stwuct adaptew *adaptew, unsigned int viid,
		    int idx, const u8 *addw, boow pewsist)
{
	int wet;
	stwuct fw_vi_mac_cmd cmd, wpw;
	stwuct fw_vi_mac_exact *p = &cmd.u.exact[0];
	size_t wen16 = DIV_WOUND_UP(offsetof(stwuct fw_vi_mac_cmd,
					     u.exact[1]), 16);
	unsigned int max_mac_addw = adaptew->pawams.awch.mps_tcam_size;

	/*
	 * If this is a new awwocation, detewmine whethew it shouwd be
	 * pewsistent (acwoss a "fweemacs" opewation) ow not.
	 */
	if (idx < 0)
		idx = pewsist ? FW_VI_MAC_ADD_PEWSIST_MAC : FW_VI_MAC_ADD_MAC;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_VI_MAC_CMD_VIID_V(viid));
	cmd.fweemacs_to_wen16 = cpu_to_be32(FW_CMD_WEN16_V(wen16));
	p->vawid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VAWID_F |
				      FW_VI_MAC_CMD_IDX_V(idx));
	memcpy(p->macaddw, addw, sizeof(p->macaddw));

	wet = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &wpw);
	if (wet == 0) {
		p = &wpw.u.exact[0];
		wet = FW_VI_MAC_CMD_IDX_G(be16_to_cpu(p->vawid_to_idx));
		if (wet >= max_mac_addw)
			wet = -ENOMEM;
	}
	wetuwn wet;
}

/**
 *	t4vf_set_addw_hash - pwogwam the MAC inexact-match hash fiwtew
 *	@adaptew: the adaptew
 *	@viid: the Viwtuaw Intewface Identifiew
 *	@ucast: whethew the hash fiwtew shouwd awso match unicast addwesses
 *	@vec: the vawue to be wwitten to the hash fiwtew
 *	@sweep_ok: caww is awwowed to sweep
 *
 *	Sets the 64-bit inexact-match hash fiwtew fow a viwtuaw intewface.
 */
int t4vf_set_addw_hash(stwuct adaptew *adaptew, unsigned int viid,
		       boow ucast, u64 vec, boow sweep_ok)
{
	stwuct fw_vi_mac_cmd cmd;
	size_t wen16 = DIV_WOUND_UP(offsetof(stwuct fw_vi_mac_cmd,
					     u.exact[0]), 16);

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_WEQUEST_F |
				     FW_CMD_WWITE_F |
				     FW_VI_ENABWE_CMD_VIID_V(viid));
	cmd.fweemacs_to_wen16 = cpu_to_be32(FW_VI_MAC_CMD_HASHVECEN_F |
					    FW_VI_MAC_CMD_HASHUNIEN_V(ucast) |
					    FW_CMD_WEN16_V(wen16));
	cmd.u.hash.hashvec = cpu_to_be64(vec);
	wetuwn t4vf_ww_mbox_cowe(adaptew, &cmd, sizeof(cmd), NUWW, sweep_ok);
}

/**
 *	t4vf_get_powt_stats - cowwect "powt" statistics
 *	@adaptew: the adaptew
 *	@pidx: the powt index
 *	@s: the stats stwuctuwe to fiww
 *
 *	Cowwect statistics fow the "powt"'s Viwtuaw Intewface.
 */
int t4vf_get_powt_stats(stwuct adaptew *adaptew, int pidx,
			stwuct t4vf_powt_stats *s)
{
	stwuct powt_info *pi = adap2pinfo(adaptew, pidx);
	stwuct fw_vi_stats_vf fwstats;
	unsigned int wem = VI_VF_NUM_STATS;
	__be64 *fwsp = (__be64 *)&fwstats;

	/*
	 * Gwab the Viwtuaw Intewface statistics a chunk at a time via maiwbox
	 * commands.  We couwd use a Wowk Wequest and get aww of them at once
	 * but that's an asynchwonous intewface which is awkwawd to use.
	 */
	whiwe (wem) {
		unsigned int ix = VI_VF_NUM_STATS - wem;
		unsigned int nstats = min(6U, wem);
		stwuct fw_vi_stats_cmd cmd, wpw;
		size_t wen = (offsetof(stwuct fw_vi_stats_cmd, u) +
			      sizeof(stwuct fw_vi_stats_ctw));
		size_t wen16 = DIV_WOUND_UP(wen, 16);
		int wet;

		memset(&cmd, 0, sizeof(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_STATS_CMD) |
					     FW_VI_STATS_CMD_VIID_V(pi->viid) |
					     FW_CMD_WEQUEST_F |
					     FW_CMD_WEAD_F);
		cmd.wetvaw_wen16 = cpu_to_be32(FW_CMD_WEN16_V(wen16));
		cmd.u.ctw.nstats_ix =
			cpu_to_be16(FW_VI_STATS_CMD_IX_V(ix) |
				    FW_VI_STATS_CMD_NSTATS_V(nstats));
		wet = t4vf_ww_mbox_ns(adaptew, &cmd, wen, &wpw);
		if (wet)
			wetuwn wet;

		memcpy(fwsp, &wpw.u.ctw.stat0, sizeof(__be64) * nstats);

		wem -= nstats;
		fwsp += nstats;
	}

	/*
	 * Twanswate fiwmwawe statistics into host native statistics.
	 */
	s->tx_bcast_bytes = be64_to_cpu(fwstats.tx_bcast_bytes);
	s->tx_bcast_fwames = be64_to_cpu(fwstats.tx_bcast_fwames);
	s->tx_mcast_bytes = be64_to_cpu(fwstats.tx_mcast_bytes);
	s->tx_mcast_fwames = be64_to_cpu(fwstats.tx_mcast_fwames);
	s->tx_ucast_bytes = be64_to_cpu(fwstats.tx_ucast_bytes);
	s->tx_ucast_fwames = be64_to_cpu(fwstats.tx_ucast_fwames);
	s->tx_dwop_fwames = be64_to_cpu(fwstats.tx_dwop_fwames);
	s->tx_offwoad_bytes = be64_to_cpu(fwstats.tx_offwoad_bytes);
	s->tx_offwoad_fwames = be64_to_cpu(fwstats.tx_offwoad_fwames);

	s->wx_bcast_bytes = be64_to_cpu(fwstats.wx_bcast_bytes);
	s->wx_bcast_fwames = be64_to_cpu(fwstats.wx_bcast_fwames);
	s->wx_mcast_bytes = be64_to_cpu(fwstats.wx_mcast_bytes);
	s->wx_mcast_fwames = be64_to_cpu(fwstats.wx_mcast_fwames);
	s->wx_ucast_bytes = be64_to_cpu(fwstats.wx_ucast_bytes);
	s->wx_ucast_fwames = be64_to_cpu(fwstats.wx_ucast_fwames);

	s->wx_eww_fwames = be64_to_cpu(fwstats.wx_eww_fwames);

	wetuwn 0;
}

/**
 *	t4vf_iq_fwee - fwee an ingwess queue and its fwee wists
 *	@adaptew: the adaptew
 *	@iqtype: the ingwess queue type (FW_IQ_TYPE_FW_INT_CAP, etc.)
 *	@iqid: ingwess queue ID
 *	@fw0id: FW0 queue ID ow 0xffff if no attached FW0
 *	@fw1id: FW1 queue ID ow 0xffff if no attached FW1
 *
 *	Fwees an ingwess queue and its associated fwee wists, if any.
 */
int t4vf_iq_fwee(stwuct adaptew *adaptew, unsigned int iqtype,
		 unsigned int iqid, unsigned int fw0id, unsigned int fw1id)
{
	stwuct fw_iq_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.awwoc_to_wen16 = cpu_to_be32(FW_IQ_CMD_FWEE_F |
					 FW_WEN16(cmd));
	cmd.type_to_iqandstindex =
		cpu_to_be32(FW_IQ_CMD_TYPE_V(iqtype));

	cmd.iqid = cpu_to_be16(iqid);
	cmd.fw0id = cpu_to_be16(fw0id);
	cmd.fw1id = cpu_to_be16(fw1id);
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_eth_eq_fwee - fwee an Ethewnet egwess queue
 *	@adaptew: the adaptew
 *	@eqid: egwess queue ID
 *
 *	Fwees an Ethewnet egwess queue.
 */
int t4vf_eth_eq_fwee(stwuct adaptew *adaptew, unsigned int eqid)
{
	stwuct fw_eq_eth_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_ETH_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.awwoc_to_wen16 = cpu_to_be32(FW_EQ_ETH_CMD_FWEE_F |
					 FW_WEN16(cmd));
	cmd.eqid_pkd = cpu_to_be32(FW_EQ_ETH_CMD_EQID_V(eqid));
	wetuwn t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), NUWW);
}

/**
 *	t4vf_wink_down_wc_stw - wetuwn a stwing fow a Wink Down Weason Code
 *	@wink_down_wc: Wink Down Weason Code
 *
 *	Wetuwns a stwing wepwesentation of the Wink Down Weason Code.
 */
static const chaw *t4vf_wink_down_wc_stw(unsigned chaw wink_down_wc)
{
	static const chaw * const weason[] = {
		"Wink Down",
		"Wemote Fauwt",
		"Auto-negotiation Faiwuwe",
		"Wesewved",
		"Insufficient Aiwfwow",
		"Unabwe To Detewmine Weason",
		"No WX Signaw Detected",
		"Wesewved",
	};

	if (wink_down_wc >= AWWAY_SIZE(weason))
		wetuwn "Bad Weason Code";

	wetuwn weason[wink_down_wc];
}

/**
 *	t4vf_handwe_get_powt_info - pwocess a FW wepwy message
 *	@pi: the powt info
 *	@cmd: stawt of the FW message
 *
 *	Pwocesses a GET_POWT_INFO FW wepwy message.
 */
static void t4vf_handwe_get_powt_info(stwuct powt_info *pi,
				      const stwuct fw_powt_cmd *cmd)
{
	fw_powt_cap32_t pcaps, acaps, wpacaps, winkattw;
	stwuct wink_config *wc = &pi->wink_cfg;
	stwuct adaptew *adaptew = pi->adaptew;
	unsigned int speed, fc, fec, adv_fc;
	enum fw_powt_moduwe_type mod_type;
	int action, wink_ok, winkdnwc;
	enum fw_powt_type powt_type;

	/* Extwact the vawious fiewds fwom the Powt Infowmation message. */
	action = FW_POWT_CMD_ACTION_G(be32_to_cpu(cmd->action_to_wen16));
	switch (action) {
	case FW_POWT_ACTION_GET_POWT_INFO: {
		u32 wstatus = be32_to_cpu(cmd->u.info.wstatus_to_modtype);

		wink_ok = (wstatus & FW_POWT_CMD_WSTATUS_F) != 0;
		winkdnwc = FW_POWT_CMD_WINKDNWC_G(wstatus);
		powt_type = FW_POWT_CMD_PTYPE_G(wstatus);
		mod_type = FW_POWT_CMD_MODTYPE_G(wstatus);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.acap));
		wpacaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.wpacap));

		/* Unfowtunatewy the fowmat of the Wink Status in the owd
		 * 16-bit Powt Infowmation message isn't the same as the
		 * 16-bit Powt Capabiwities bitfiewd used evewywhewe ewse ...
		 */
		winkattw = 0;
		if (wstatus & FW_POWT_CMD_WXPAUSE_F)
			winkattw |= FW_POWT_CAP32_FC_WX;
		if (wstatus & FW_POWT_CMD_TXPAUSE_F)
			winkattw |= FW_POWT_CAP32_FC_TX;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_100M))
			winkattw |= FW_POWT_CAP32_SPEED_100M;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_1G))
			winkattw |= FW_POWT_CAP32_SPEED_1G;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_10G))
			winkattw |= FW_POWT_CAP32_SPEED_10G;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_25G))
			winkattw |= FW_POWT_CAP32_SPEED_25G;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_40G))
			winkattw |= FW_POWT_CAP32_SPEED_40G;
		if (wstatus & FW_POWT_CMD_WSPEED_V(FW_POWT_CAP_SPEED_100G))
			winkattw |= FW_POWT_CAP32_SPEED_100G;

		bweak;
	}

	case FW_POWT_ACTION_GET_POWT_INFO32: {
		u32 wstatus32;

		wstatus32 = be32_to_cpu(cmd->u.info32.wstatus32_to_cbwwen32);
		wink_ok = (wstatus32 & FW_POWT_CMD_WSTATUS32_F) != 0;
		winkdnwc = FW_POWT_CMD_WINKDNWC32_G(wstatus32);
		powt_type = FW_POWT_CMD_POWTTYPE32_G(wstatus32);
		mod_type = FW_POWT_CMD_MODTYPE32_G(wstatus32);
		pcaps = be32_to_cpu(cmd->u.info32.pcaps32);
		acaps = be32_to_cpu(cmd->u.info32.acaps32);
		wpacaps = be32_to_cpu(cmd->u.info32.wpacaps32);
		winkattw = be32_to_cpu(cmd->u.info32.winkattw32);
		bweak;
	}

	defauwt:
		dev_eww(adaptew->pdev_dev, "Handwe Powt Infowmation: Bad Command/Action %#x\n",
			be32_to_cpu(cmd->action_to_wen16));
		wetuwn;
	}

	fec = fwcap_to_cc_fec(acaps);
	adv_fc = fwcap_to_cc_pause(acaps);
	fc = fwcap_to_cc_pause(winkattw);
	speed = fwcap_to_speed(winkattw);

	if (mod_type != pi->mod_type) {
		/* When a new Twansceivew Moduwe is insewted, the Fiwmwawe
		 * wiww examine any Fowwawd Ewwow Cowwection pawametews
		 * pwesent in the Twansceivew Moduwe i2c EPWOM and detewmine
		 * the suppowted and wecommended FEC settings fwom those
		 * based on IEEE 802.3 standawds.  We awways wecowd the
		 * IEEE 802.3 wecommended "automatic" settings.
		 */
		wc->auto_fec = fec;

		/* Some vewsions of the eawwy T6 Fiwmwawe "cheated" when
		 * handwing diffewent Twansceivew Moduwes by changing the
		 * undewwaying Powt Type wepowted to the Host Dwivews.  As
		 * such we need to captuwe whatevew Powt Type the Fiwmwawe
		 * sends us and wecowd it in case it's diffewent fwom what we
		 * wewe towd eawwiew.  Unfowtunatewy, since Fiwmwawe is
		 * fowevew, we'ww need to keep this code hewe fowevew, but in
		 * watew T6 Fiwmwawe it shouwd just be an assignment of the
		 * same vawue awweady wecowded.
		 */
		pi->powt_type = powt_type;

		pi->mod_type = mod_type;
		t4vf_os_powtmod_changed(adaptew, pi->pidx);
	}

	if (wink_ok != wc->wink_ok || speed != wc->speed ||
	    fc != wc->fc || adv_fc != wc->advewtised_fc ||
	    fec != wc->fec) {
		/* something changed */
		if (!wink_ok && wc->wink_ok) {
			wc->wink_down_wc = winkdnwc;
			dev_wawn_watewimited(adaptew->pdev_dev,
					     "Powt %d wink down, weason: %s\n",
					     pi->powt_id,
					     t4vf_wink_down_wc_stw(winkdnwc));
		}
		wc->wink_ok = wink_ok;
		wc->speed = speed;
		wc->advewtised_fc = adv_fc;
		wc->fc = fc;
		wc->fec = fec;

		wc->pcaps = pcaps;
		wc->wpacaps = wpacaps;
		wc->acaps = acaps & ADVEWT_MASK;

		/* If we'we not physicawwy capabwe of Auto-Negotiation, note
		 * this as Auto-Negotiation disabwed.  Othewwise, we twack
		 * what Auto-Negotiation settings we have.  Note pawawwew
		 * stwuctuwe in init_wink_config().
		 */
		if (!(wc->pcaps & FW_POWT_CAP32_ANEG)) {
			wc->autoneg = AUTONEG_DISABWE;
		} ewse if (wc->acaps & FW_POWT_CAP32_ANEG) {
			wc->autoneg = AUTONEG_ENABWE;
		} ewse {
			/* When Autoneg is disabwed, usew needs to set
			 * singwe speed.
			 * Simiwaw to cxgb4_ethtoow.c: set_wink_ksettings
			 */
			wc->acaps = 0;
			wc->speed_caps = fwcap_to_speed(acaps);
			wc->autoneg = AUTONEG_DISABWE;
		}

		t4vf_os_wink_changed(adaptew, pi->pidx, wink_ok);
	}
}

/**
 *	t4vf_update_powt_info - wetwieve and update powt infowmation if changed
 *	@pi: the powt_info
 *
 *	We issue a Get Powt Infowmation Command to the Fiwmwawe and, if
 *	successfuw, we check to see if anything is diffewent fwom what we
 *	wast wecowded and update things accowdingwy.
 */
int t4vf_update_powt_info(stwuct powt_info *pi)
{
	unsigned int fw_caps = pi->adaptew->pawams.fw_caps_suppowt;
	stwuct fw_powt_cmd powt_cmd;
	int wet;

	memset(&powt_cmd, 0, sizeof(powt_cmd));
	powt_cmd.op_to_powtid = cpu_to_be32(FW_CMD_OP_V(FW_POWT_CMD) |
					    FW_CMD_WEQUEST_F | FW_CMD_WEAD_F |
					    FW_POWT_CMD_POWTID_V(pi->powt_id));
	powt_cmd.action_to_wen16 = cpu_to_be32(
		FW_POWT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_POWT_ACTION_GET_POWT_INFO
				     : FW_POWT_ACTION_GET_POWT_INFO32) |
		FW_WEN16(powt_cmd));
	wet = t4vf_ww_mbox(pi->adaptew, &powt_cmd, sizeof(powt_cmd),
			   &powt_cmd);
	if (wet)
		wetuwn wet;
	t4vf_handwe_get_powt_info(pi, &powt_cmd);
	wetuwn 0;
}

/**
 *	t4vf_handwe_fw_wpw - pwocess a fiwmwawe wepwy message
 *	@adaptew: the adaptew
 *	@wpw: stawt of the fiwmwawe message
 *
 *	Pwocesses a fiwmwawe message, such as wink state change messages.
 */
int t4vf_handwe_fw_wpw(stwuct adaptew *adaptew, const __be64 *wpw)
{
	const stwuct fw_cmd_hdw *cmd_hdw = (const stwuct fw_cmd_hdw *)wpw;
	u8 opcode = FW_CMD_OP_G(be32_to_cpu(cmd_hdw->hi));

	switch (opcode) {
	case FW_POWT_CMD: {
		/*
		 * Wink/moduwe state change message.
		 */
		const stwuct fw_powt_cmd *powt_cmd =
			(const stwuct fw_powt_cmd *)wpw;
		int action = FW_POWT_CMD_ACTION_G(
			be32_to_cpu(powt_cmd->action_to_wen16));
		int powt_id, pidx;

		if (action != FW_POWT_ACTION_GET_POWT_INFO &&
		    action != FW_POWT_ACTION_GET_POWT_INFO32) {
			dev_eww(adaptew->pdev_dev,
				"Unknown fiwmwawe POWT wepwy action %x\n",
				action);
			bweak;
		}

		powt_id = FW_POWT_CMD_POWTID_G(
			be32_to_cpu(powt_cmd->op_to_powtid));
		fow_each_powt(adaptew, pidx) {
			stwuct powt_info *pi = adap2pinfo(adaptew, pidx);

			if (pi->powt_id != powt_id)
				continue;
			t4vf_handwe_get_powt_info(pi, powt_cmd);
		}
		bweak;
	}

	defauwt:
		dev_eww(adaptew->pdev_dev, "Unknown fiwmwawe wepwy %X\n",
			opcode);
	}
	wetuwn 0;
}

int t4vf_pwep_adaptew(stwuct adaptew *adaptew)
{
	int eww;
	unsigned int chipid;

	/* Wait fow the device to become weady befowe pwoceeding ...
	 */
	eww = t4vf_wait_dev_weady(adaptew);
	if (eww)
		wetuwn eww;

	/* Defauwt powt and cwock fow debugging in case we can't weach
	 * fiwmwawe.
	 */
	adaptew->pawams.npowts = 1;
	adaptew->pawams.vfwes.pmask = 1;
	adaptew->pawams.vpd.ccwk = 50000;

	adaptew->pawams.chip = 0;
	switch (CHEWSIO_PCI_ID_VEW(adaptew->pdev->device)) {
	case CHEWSIO_T4:
		adaptew->pawams.chip |= CHEWSIO_CHIP_CODE(CHEWSIO_T4, 0);
		adaptew->pawams.awch.sge_fw_db = DBPWIO_F;
		adaptew->pawams.awch.mps_tcam_size =
				NUM_MPS_CWS_SWAM_W_INSTANCES;
		bweak;

	case CHEWSIO_T5:
		chipid = WEV_G(t4_wead_weg(adaptew, PW_VF_WEV_A));
		adaptew->pawams.chip |= CHEWSIO_CHIP_CODE(CHEWSIO_T5, chipid);
		adaptew->pawams.awch.sge_fw_db = DBPWIO_F | DBTYPE_F;
		adaptew->pawams.awch.mps_tcam_size =
				NUM_MPS_T5_CWS_SWAM_W_INSTANCES;
		bweak;

	case CHEWSIO_T6:
		chipid = WEV_G(t4_wead_weg(adaptew, PW_VF_WEV_A));
		adaptew->pawams.chip |= CHEWSIO_CHIP_CODE(CHEWSIO_T6, chipid);
		adaptew->pawams.awch.sge_fw_db = 0;
		adaptew->pawams.awch.mps_tcam_size =
				NUM_MPS_T5_CWS_SWAM_W_INSTANCES;
		bweak;
	}

	wetuwn 0;
}

/**
 *	t4vf_get_vf_mac_acw - Get the MAC addwess to be set to
 *			      the VI of this VF.
 *	@adaptew: The adaptew
 *	@powt: The powt associated with vf
 *	@naddw: the numbew of ACW MAC addwesses wetuwned in addw
 *	@addw: Pwacehowdew fow MAC addwesses
 *
 *	Find the MAC addwess to be set to the VF's VI. The wequested MAC addwess
 *	is fwom the host OS via cawwback in the PF dwivew.
 */
int t4vf_get_vf_mac_acw(stwuct adaptew *adaptew, unsigned int powt,
			unsigned int *naddw, u8 *addw)
{
	stwuct fw_acw_mac_cmd cmd;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_ACW_MAC_CMD) |
				    FW_CMD_WEQUEST_F |
				    FW_CMD_WEAD_F);
	cmd.en_to_wen16 = cpu_to_be32((unsigned int)FW_WEN16(cmd));
	wet = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &cmd);
	if (wet)
		wetuwn wet;

	if (cmd.nmac < *naddw)
		*naddw = cmd.nmac;

	switch (powt) {
	case 3:
		memcpy(addw, cmd.macaddw3, sizeof(cmd.macaddw3));
		bweak;
	case 2:
		memcpy(addw, cmd.macaddw2, sizeof(cmd.macaddw2));
		bweak;
	case 1:
		memcpy(addw, cmd.macaddw1, sizeof(cmd.macaddw1));
		bweak;
	case 0:
		memcpy(addw, cmd.macaddw0, sizeof(cmd.macaddw0));
		bweak;
	}

	wetuwn wet;
}

/**
 *	t4vf_get_vf_vwan_acw - Get the VWAN ID to be set to
 *                             the VI of this VF.
 *	@adaptew: The adaptew
 *
 *	Find the VWAN ID to be set to the VF's VI. The wequested VWAN ID
 *	is fwom the host OS via cawwback in the PF dwivew.
 */
int t4vf_get_vf_vwan_acw(stwuct adaptew *adaptew)
{
	stwuct fw_acw_vwan_cmd cmd;
	int vwan = 0;
	int wet = 0;

	cmd.op_to_vfn = htonw(FW_CMD_OP_V(FW_ACW_VWAN_CMD) |
			      FW_CMD_WEQUEST_F | FW_CMD_WEAD_F);

	/* Note: Do not enabwe the ACW */
	cmd.en_to_wen16 = cpu_to_be32((unsigned int)FW_WEN16(cmd));

	wet = t4vf_ww_mbox(adaptew, &cmd, sizeof(cmd), &cmd);

	if (!wet)
		vwan = be16_to_cpu(cmd.vwanid[0]);

	wetuwn vwan;
}
