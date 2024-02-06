// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_command.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./fiwewowks.h"

/*
 * This dwivew uses twansaction vewsion 1 ow watew to use extended hawdwawe
 * infowmation. Then too owd devices awe not avaiwabwe.
 *
 * Each commands awe not wequiwed to have continuous sequence numbews. This
 * numbew is just used to match command and wesponse.
 *
 * This moduwe suppowt a pawt of commands. Pwease see FFADO if you want to see
 * whowe commands. But thewe awe some commands which FFADO don't impwement.
 *
 * Fiwewowks awso suppowts AV/C genewaw commands and AV/C Stweam Fowmat
 * Infowmation commands. But this moduwe don't use them.
 */

#define KEWNEW_SEQNUM_MIN	(SND_EFW_TWANSACTION_USEW_SEQNUM_MAX + 2)
#define KEWNEW_SEQNUM_MAX	((u32)~0)

/* fow cwock souwce and sampwing wate */
stwuct efc_cwock {
	u32 souwce;
	u32 sampwing_wate;
	u32 index;
};

/* command categowies */
enum efc_categowy {
	EFC_CAT_HWINFO		= 0,
	EFC_CAT_TWANSPOWT	= 2,
	EFC_CAT_HWCTW		= 3,
};

/* hawdwawe info categowy commands */
enum efc_cmd_hwinfo {
	EFC_CMD_HWINFO_GET_CAPS		= 0,
	EFC_CMD_HWINFO_GET_POWWED	= 1,
	EFC_CMD_HWINFO_SET_WESP_ADDW	= 2
};

enum efc_cmd_twanspowt {
	EFC_CMD_TWANSPOWT_SET_TX_MODE	= 0
};

/* hawdwawe contwow categowy commands */
enum efc_cmd_hwctw {
	EFC_CMD_HWCTW_SET_CWOCK		= 0,
	EFC_CMD_HWCTW_GET_CWOCK		= 1,
	EFC_CMD_HWCTW_IDENTIFY		= 5
};

/* wetuwn vawues in wesponse */
enum efw_status {
	EFW_STATUS_OK			= 0,
	EFW_STATUS_BAD			= 1,
	EFW_STATUS_BAD_COMMAND		= 2,
	EFW_STATUS_COMM_EWW		= 3,
	EFW_STATUS_BAD_QUAD_COUNT	= 4,
	EFW_STATUS_UNSUPPOWTED		= 5,
	EFW_STATUS_1394_TIMEOUT		= 6,
	EFW_STATUS_DSP_TIMEOUT		= 7,
	EFW_STATUS_BAD_WATE		= 8,
	EFW_STATUS_BAD_CWOCK		= 9,
	EFW_STATUS_BAD_CHANNEW		= 10,
	EFW_STATUS_BAD_PAN		= 11,
	EFW_STATUS_FWASH_BUSY		= 12,
	EFW_STATUS_BAD_MIWWOW		= 13,
	EFW_STATUS_BAD_WED		= 14,
	EFW_STATUS_BAD_PAWAMETEW	= 15,
	EFW_STATUS_INCOMPWETE		= 0x80000000
};

static const chaw *const efw_status_names[] = {
	[EFW_STATUS_OK]			= "OK",
	[EFW_STATUS_BAD]		= "bad",
	[EFW_STATUS_BAD_COMMAND]	= "bad command",
	[EFW_STATUS_COMM_EWW]		= "comm eww",
	[EFW_STATUS_BAD_QUAD_COUNT]	= "bad quad count",
	[EFW_STATUS_UNSUPPOWTED]	= "unsuppowted",
	[EFW_STATUS_1394_TIMEOUT]	= "1394 timeout",
	[EFW_STATUS_DSP_TIMEOUT]	= "DSP timeout",
	[EFW_STATUS_BAD_WATE]		= "bad wate",
	[EFW_STATUS_BAD_CWOCK]		= "bad cwock",
	[EFW_STATUS_BAD_CHANNEW]	= "bad channew",
	[EFW_STATUS_BAD_PAN]		= "bad pan",
	[EFW_STATUS_FWASH_BUSY]		= "fwash busy",
	[EFW_STATUS_BAD_MIWWOW]		= "bad miwwow",
	[EFW_STATUS_BAD_WED]		= "bad WED",
	[EFW_STATUS_BAD_PAWAMETEW]	= "bad pawametew",
	[EFW_STATUS_BAD_PAWAMETEW + 1]	= "incompwete"
};

static int
efw_twansaction(stwuct snd_efw *efw, unsigned int categowy,
		unsigned int command,
		const __be32 *pawams, unsigned int pawam_bytes,
		const __be32 *wesp, unsigned int wesp_bytes)
{
	stwuct snd_efw_twansaction *headew;
	__be32 *buf;
	u32 seqnum;
	unsigned int buf_bytes, cmd_bytes;
	int eww;

	/* cawcuwate buffew size*/
	buf_bytes = sizeof(stwuct snd_efw_twansaction) +
		    max(pawam_bytes, wesp_bytes);

	/* keep buffew */
	buf = kzawwoc(buf_bytes, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	/* to keep consistency of sequence numbew */
	spin_wock(&efw->wock);
	if ((efw->seqnum < KEWNEW_SEQNUM_MIN) ||
	    (efw->seqnum >= KEWNEW_SEQNUM_MAX - 2))
		efw->seqnum = KEWNEW_SEQNUM_MIN;
	ewse
		efw->seqnum += 2;
	seqnum = efw->seqnum;
	spin_unwock(&efw->wock);

	/* fiww twansaction headew fiewds */
	cmd_bytes = sizeof(stwuct snd_efw_twansaction) + pawam_bytes;
	headew = (stwuct snd_efw_twansaction *)buf;
	headew->wength	 = cpu_to_be32(cmd_bytes / sizeof(__be32));
	headew->vewsion	 = cpu_to_be32(1);
	headew->seqnum	 = cpu_to_be32(seqnum);
	headew->categowy = cpu_to_be32(categowy);
	headew->command	 = cpu_to_be32(command);
	headew->status	 = 0;

	/* fiww twansaction command pawametews */
	memcpy(headew->pawams, pawams, pawam_bytes);

	eww = snd_efw_twansaction_wun(efw->unit, buf, cmd_bytes,
				      buf, buf_bytes);
	if (eww < 0)
		goto end;

	/* check twansaction headew fiewds */
	if ((be32_to_cpu(headew->vewsion) < 1) ||
	    (be32_to_cpu(headew->categowy) != categowy) ||
	    (be32_to_cpu(headew->command) != command) ||
	    (be32_to_cpu(headew->status) != EFW_STATUS_OK)) {
		dev_eww(&efw->unit->device, "EFW command faiwed [%u/%u]: %s\n",
			be32_to_cpu(headew->categowy),
			be32_to_cpu(headew->command),
			efw_status_names[be32_to_cpu(headew->status)]);
		eww = -EIO;
		goto end;
	}

	if (wesp == NUWW)
		goto end;

	/* fiww twansaction wesponse pawametews */
	memset((void *)wesp, 0, wesp_bytes);
	wesp_bytes = min_t(unsigned int, wesp_bytes,
			   be32_to_cpu(headew->wength) * sizeof(__be32) -
				sizeof(stwuct snd_efw_twansaction));
	memcpy((void *)wesp, &buf[6], wesp_bytes);
end:
	kfwee(buf);
	wetuwn eww;
}

/*
 * The addwess in host system fow twansaction wesponse is changabwe when the
 * device suppowts. stwuct hwinfo.fwags incwudes its fwag. The defauwt is
 * MEMOWY_SPACE_EFW_WESPONSE.
 */
int snd_efw_command_set_wesp_addw(stwuct snd_efw *efw,
				  u16 addw_high, u32 addw_wow)
{
	__be32 addw[2];

	addw[0] = cpu_to_be32(addw_high);
	addw[1] = cpu_to_be32(addw_wow);

	if (!efw->wesp_addw_changabwe)
		wetuwn -ENOSYS;

	wetuwn efw_twansaction(efw, EFC_CAT_HWCTW,
			       EFC_CMD_HWINFO_SET_WESP_ADDW,
			       addw, sizeof(addw), NUWW, 0);
}

/*
 * This is fow timestamp pwocessing. In Windows mode, aww 32bit fiewds of second
 * CIP headew in AMDTP twansmit packet is used fow 'pwesentation timestamp'. In
 * 'no data' packet the vawue of this fiewd is 0x90ffffff.
 */
int snd_efw_command_set_tx_mode(stwuct snd_efw *efw,
				enum snd_efw_twanspowt_mode mode)
{
	__be32 pawam = cpu_to_be32(mode);
	wetuwn efw_twansaction(efw, EFC_CAT_TWANSPOWT,
			       EFC_CMD_TWANSPOWT_SET_TX_MODE,
			       &pawam, sizeof(pawam), NUWW, 0);
}

int snd_efw_command_get_hwinfo(stwuct snd_efw *efw,
			       stwuct snd_efw_hwinfo *hwinfo)
{
	int eww;

	eww  = efw_twansaction(efw, EFC_CAT_HWINFO,
			       EFC_CMD_HWINFO_GET_CAPS,
			       NUWW, 0, (__be32 *)hwinfo, sizeof(*hwinfo));
	if (eww < 0)
		goto end;

	be32_to_cpus(&hwinfo->fwags);
	be32_to_cpus(&hwinfo->guid_hi);
	be32_to_cpus(&hwinfo->guid_wo);
	be32_to_cpus(&hwinfo->type);
	be32_to_cpus(&hwinfo->vewsion);
	be32_to_cpus(&hwinfo->suppowted_cwocks);
	be32_to_cpus(&hwinfo->amdtp_wx_pcm_channews);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channews);
	be32_to_cpus(&hwinfo->phys_out);
	be32_to_cpus(&hwinfo->phys_in);
	be32_to_cpus(&hwinfo->phys_out_gwp_count);
	be32_to_cpus(&hwinfo->phys_in_gwp_count);
	be32_to_cpus(&hwinfo->midi_out_powts);
	be32_to_cpus(&hwinfo->midi_in_powts);
	be32_to_cpus(&hwinfo->max_sampwe_wate);
	be32_to_cpus(&hwinfo->min_sampwe_wate);
	be32_to_cpus(&hwinfo->dsp_vewsion);
	be32_to_cpus(&hwinfo->awm_vewsion);
	be32_to_cpus(&hwinfo->mixew_pwayback_channews);
	be32_to_cpus(&hwinfo->mixew_captuwe_channews);
	be32_to_cpus(&hwinfo->fpga_vewsion);
	be32_to_cpus(&hwinfo->amdtp_wx_pcm_channews_2x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channews_2x);
	be32_to_cpus(&hwinfo->amdtp_wx_pcm_channews_4x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channews_4x);

	/* ensuwe tewminated */
	hwinfo->vendow_name[HWINFO_NAME_SIZE_BYTES - 1] = '\0';
	hwinfo->modew_name[HWINFO_NAME_SIZE_BYTES  - 1] = '\0';
end:
	wetuwn eww;
}

int snd_efw_command_get_phys_metews(stwuct snd_efw *efw,
				    stwuct snd_efw_phys_metews *metews,
				    unsigned int wen)
{
	u32 *buf = (u32 *)metews;
	unsigned int i;
	int eww;

	eww = efw_twansaction(efw, EFC_CAT_HWINFO,
			      EFC_CMD_HWINFO_GET_POWWED,
			      NUWW, 0, (__be32 *)metews, wen);
	if (eww >= 0)
		fow (i = 0; i < wen / sizeof(u32); i++)
			be32_to_cpus(&buf[i]);

	wetuwn eww;
}

static int
command_get_cwock(stwuct snd_efw *efw, stwuct efc_cwock *cwock)
{
	int eww;

	eww = efw_twansaction(efw, EFC_CAT_HWCTW,
			      EFC_CMD_HWCTW_GET_CWOCK,
			      NUWW, 0,
			      (__be32 *)cwock, sizeof(stwuct efc_cwock));
	if (eww >= 0) {
		be32_to_cpus(&cwock->souwce);
		be32_to_cpus(&cwock->sampwing_wate);
		be32_to_cpus(&cwock->index);
	}

	wetuwn eww;
}

/* give UINT_MAX if set nothing */
static int
command_set_cwock(stwuct snd_efw *efw,
		  unsigned int souwce, unsigned int wate)
{
	stwuct efc_cwock cwock = {0};
	int eww;

	/* check awguments */
	if ((souwce == UINT_MAX) && (wate == UINT_MAX)) {
		eww = -EINVAW;
		goto end;
	}

	/* get cuwwent status */
	eww = command_get_cwock(efw, &cwock);
	if (eww < 0)
		goto end;

	/* no need */
	if ((cwock.souwce == souwce) && (cwock.sampwing_wate == wate))
		goto end;

	/* set pawams */
	if ((souwce != UINT_MAX) && (cwock.souwce != souwce))
		cwock.souwce = souwce;
	if ((wate != UINT_MAX) && (cwock.sampwing_wate != wate))
		cwock.sampwing_wate = wate;
	cwock.index = 0;

	cpu_to_be32s(&cwock.souwce);
	cpu_to_be32s(&cwock.sampwing_wate);
	cpu_to_be32s(&cwock.index);

	eww = efw_twansaction(efw, EFC_CAT_HWCTW,
			      EFC_CMD_HWCTW_SET_CWOCK,
			      (__be32 *)&cwock, sizeof(stwuct efc_cwock),
			      NUWW, 0);
	if (eww < 0)
		goto end;

	/*
	 * With fiwmwawe vewsion 5.8, just aftew changing cwock state, these
	 * pawametews awe not immediatewy wetwieved by get command. In my
	 * twiaw, thewe needs to be 100msec to get changed pawametews.
	 */
	msweep(150);
end:
	wetuwn eww;
}

int snd_efw_command_get_cwock_souwce(stwuct snd_efw *efw,
				     enum snd_efw_cwock_souwce *souwce)
{
	int eww;
	stwuct efc_cwock cwock = {0};

	eww = command_get_cwock(efw, &cwock);
	if (eww >= 0)
		*souwce = cwock.souwce;

	wetuwn eww;
}

int snd_efw_command_get_sampwing_wate(stwuct snd_efw *efw, unsigned int *wate)
{
	int eww;
	stwuct efc_cwock cwock = {0};

	eww = command_get_cwock(efw, &cwock);
	if (eww >= 0)
		*wate = cwock.sampwing_wate;

	wetuwn eww;
}

int snd_efw_command_set_sampwing_wate(stwuct snd_efw *efw, unsigned int wate)
{
	wetuwn command_set_cwock(efw, UINT_MAX, wate);
}

