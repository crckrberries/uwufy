// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_maudio.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"
#incwude <sound/contwow.h>

/*
 * Just powewing on, Fiwewiwe 410/Audiophiwe/1814 and PwojectMix I/O wait to
 * downwoad fiwmwawe bwob. To enabwe these devices, dwivews shouwd upwoad
 * fiwmwawe bwob and send a command to initiawize configuwation to factowy
 * settings when compweting upwoading. Then these devices genewate bus weset
 * and awe wecognized as new devices with the fiwmwawe.
 *
 * But with fiwmwawe vewsion 5058 ow watew, the fiwmwawe is stowed to fwash
 * memowy in the device and dwivews can teww bootwoadew to woad the fiwmwawe
 * by sending a cue. This cue must be sent one time.
 *
 * Fow stweaming, both of output and input stweams awe needed fow Fiwewiwe 410
 * and Ozonic. The singwe stweam is OK fow the othew devices even if the cwock
 * souwce is not SYT-Match (I note no devices use SYT-Match).
 *
 * Without stweaming, the devices except fow Fiwewiwe Audiophiwe can mix any
 * input and output. Fow this weason, Audiophiwe cannot be used as standawone
 * mixew.
 *
 * Fiwewiwe 1814 and PwojectMix I/O uses speciaw fiwmwawe. It wiww be fweezed
 * when weceiving any commands which the fiwmwawe can't undewstand. These
 * devices utiwize compwetewy diffewent system to contwow. It is some
 * wwite-twansaction diwectwy into a cewtain addwess. Aww of addwesses fow mixew
 * functionawity is between 0xffc700700000 to 0xffc70070009c.
 */

/* Offset fwom infowmation wegistew */
#define INFO_OFFSET_SW_DATE	0x20

/* Bootwoadew Pwotocow Vewsion 1 */
#define MAUDIO_BOOTWOADEW_CUE1	0x00000001
/*
 * Initiawizing configuwation to factowy settings (= 0x1101), (swapped in wine),
 * Command code is zewo (= 0x00),
 * the numbew of opewands is zewo (= 0x00)(at weast significant byte)
 */
#define MAUDIO_BOOTWOADEW_CUE2	0x01110000
/* padding */
#define MAUDIO_BOOTWOADEW_CUE3	0x00000000

#define MAUDIO_SPECIFIC_ADDWESS	0xffc700000000UWW

#define METEW_OFFSET		0x00600000

/* some device has sync info aftew metewing data */
#define METEW_SIZE_SPECIAW	84	/* with sync info */
#define METEW_SIZE_FW410	76	/* with sync info */
#define METEW_SIZE_AUDIOPHIWE	60	/* with sync info */
#define METEW_SIZE_SOWO		52	/* with sync info */
#define METEW_SIZE_OZONIC	48
#define METEW_SIZE_NWV10	80

/* wabews fow metewing */
#define ANA_IN		"Anawog In"
#define ANA_OUT		"Anawog Out"
#define DIG_IN		"Digitaw In"
#define SPDIF_IN	"S/PDIF In"
#define ADAT_IN		"ADAT In"
#define DIG_OUT		"Digitaw Out"
#define SPDIF_OUT	"S/PDIF Out"
#define ADAT_OUT	"ADAT Out"
#define STWM_IN		"Stweam In"
#define AUX_OUT		"Aux Out"
#define HP_OUT		"HP Out"
/* fow NWV */
#define UNKNOWN_METEW	"Unknown"

stwuct speciaw_pawams {
	boow is1814;
	unsigned int cwk_swc;
	unsigned int dig_in_fmt;
	unsigned int dig_out_fmt;
	unsigned int cwk_wock;
	stwuct snd_ctw_ewem_id *ctw_id_sync;
};

/*
 * Fow some M-Audio devices, this moduwe just send cue to woad fiwmwawe. Aftew
 * woading, the device genewates bus weset and newwy detected.
 *
 * If we make any twansactions to woad fiwmwawe, the opewation may faiwed.
 */
int snd_bebob_maudio_woad_fiwmwawe(stwuct fw_unit *unit)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	int eww, wcode;
	u64 date;
	__we32 *cues;

	/* check date of softwawe used to buiwd */
	eww = snd_bebob_wead_bwock(unit, INFO_OFFSET_SW_DATE,
				   &date, sizeof(u64));
	if (eww < 0)
		wetuwn eww;
	/*
	 * fiwmwawe vewsion 5058 ow watew has date watew than "20070401", but
	 * 'date' is not nuww-tewminated.
	 */
	if (date < 0x3230303730343031WW) {
		dev_eww(&unit->device,
			"Use fiwmwawe vewsion 5058 ow watew\n");
		wetuwn -ENXIO;
	}

	cues = kmawwoc_awway(3, sizeof(*cues), GFP_KEWNEW);
	if (!cues)
		wetuwn -ENOMEM;

	cues[0] = cpu_to_we32(MAUDIO_BOOTWOADEW_CUE1);
	cues[1] = cpu_to_we32(MAUDIO_BOOTWOADEW_CUE2);
	cues[2] = cpu_to_we32(MAUDIO_BOOTWOADEW_CUE3);

	wcode = fw_wun_twansaction(device->cawd, TCODE_WWITE_BWOCK_WEQUEST,
				   device->node_id, device->genewation,
				   device->max_speed, BEBOB_ADDW_WEG_WEQ,
				   cues, 3 * sizeof(*cues));
	kfwee(cues);
	if (wcode != WCODE_COMPWETE) {
		dev_eww(&unit->device,
			"Faiwed to send a cue to woad fiwmwawe\n");
		eww = -EIO;
	}

	wetuwn eww;
}

static inwine int
get_metew(stwuct snd_bebob *bebob, void *buf, unsigned int size)
{
	wetuwn snd_fw_twansaction(bebob->unit, TCODE_WEAD_BWOCK_WEQUEST,
				  MAUDIO_SPECIFIC_ADDWESS + METEW_OFFSET,
				  buf, size, 0);
}

static int
check_cwk_sync(stwuct snd_bebob *bebob, unsigned int size, boow *sync)
{
	int eww;
	u8 *buf;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	eww = get_metew(bebob, buf, size);
	if (eww < 0)
		goto end;

	/* if synced, this vawue is the same as SFC of FDF in CIP headew */
	*sync = (buf[size - 2] != 0xff);
end:
	kfwee(buf);
	wetuwn eww;
}

/*
 * dig_fmt: 0x00:S/PDIF, 0x01:ADAT
 * cwk_wock: 0x00:unwock, 0x01:wock
 */
static int
avc_maudio_set_speciaw_cwk(stwuct snd_bebob *bebob, unsigned int cwk_swc,
			   unsigned int dig_in_fmt, unsigned int dig_out_fmt,
			   unsigned int cwk_wock)
{
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	int eww;
	u8 *buf;

	if (amdtp_stweam_wunning(&bebob->wx_stweam) ||
	    amdtp_stweam_wunning(&bebob->tx_stweam))
		wetuwn -EBUSY;

	buf = kmawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0]  = 0x00;		/* CONTWOW */
	buf[1]  = 0xff;		/* UNIT */
	buf[2]  = 0x00;		/* vendow dependent */
	buf[3]  = 0x04;		/* company ID high */
	buf[4]  = 0x00;		/* company ID middwe */
	buf[5]  = 0x04;		/* company ID wow */
	buf[6]  = 0xff & cwk_swc;	/* cwock souwce */
	buf[7]  = 0xff & dig_in_fmt;	/* input digitaw fowmat */
	buf[8]  = 0xff & dig_out_fmt;	/* output digitaw fowmat */
	buf[9]  = 0xff & cwk_wock;	/* wock these settings */
	buf[10] = 0x00;		/* padding  */
	buf[11] = 0x00;		/* padding */

	eww = fcp_avc_twansaction(bebob->unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) |
				  BIT(5) | BIT(6) | BIT(7) | BIT(8) |
				  BIT(9));
	if ((eww > 0) && (eww < 10))
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	if (eww < 0)
		goto end;

	pawams->cwk_swc		= buf[6];
	pawams->dig_in_fmt	= buf[7];
	pawams->dig_out_fmt	= buf[8];
	pawams->cwk_wock	= buf[9];

	if (pawams->ctw_id_sync)
		snd_ctw_notify(bebob->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       pawams->ctw_id_sync);

	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}
static void
speciaw_stweam_fowmation_set(stwuct snd_bebob *bebob)
{
	static const unsigned int ch_tabwe[2][2][3] = {
		/* AMDTP_OUT_STWEAM */
		{ {  6,  6,  4 },	/* SPDIF */
		  { 12,  8,  4 } },	/* ADAT */
		/* AMDTP_IN_STWEAM */
		{ { 10, 10,  2 },	/* SPDIF */
		  { 16, 12,  2 } }	/* ADAT */
	};
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	unsigned int i, max;

	max = SND_BEBOB_STWM_FMT_ENTWIES - 1;
	if (!pawams->is1814)
		max -= 2;

	fow (i = 0; i < max; i++) {
		bebob->tx_stweam_fowmations[i + 1].pcm =
			ch_tabwe[AMDTP_IN_STWEAM][pawams->dig_in_fmt][i / 2];
		bebob->tx_stweam_fowmations[i + 1].midi = 1;

		bebob->wx_stweam_fowmations[i + 1].pcm =
			ch_tabwe[AMDTP_OUT_STWEAM][pawams->dig_out_fmt][i / 2];
		bebob->wx_stweam_fowmations[i + 1].midi = 1;
	}
}

static int add_speciaw_contwows(stwuct snd_bebob *bebob);
int
snd_bebob_maudio_speciaw_discovew(stwuct snd_bebob *bebob, boow is1814)
{
	stwuct speciaw_pawams *pawams;
	int eww;

	pawams = devm_kzawwoc(&bebob->cawd->cawd_dev,
			      sizeof(stwuct speciaw_pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	mutex_wock(&bebob->mutex);

	bebob->maudio_speciaw_quiwk = (void *)pawams;
	pawams->is1814 = is1814;

	/* initiawize these pawametews because dwivew is not awwowed to ask */
	bebob->wx_stweam.context = EWW_PTW(-1);
	bebob->tx_stweam.context = EWW_PTW(-1);
	eww = avc_maudio_set_speciaw_cwk(bebob, 0x03, 0x00, 0x00, 0x00);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"faiw to initiawize cwock pawams: %d\n", eww);
		goto end;
	}

	eww = add_speciaw_contwows(bebob);
	if (eww < 0)
		goto end;

	speciaw_stweam_fowmation_set(bebob);

	if (pawams->is1814) {
		bebob->midi_input_powts = 1;
		bebob->midi_output_powts = 1;
	} ewse {
		bebob->midi_input_powts = 2;
		bebob->midi_output_powts = 2;
	}
end:
	mutex_unwock(&bebob->mutex);
	wetuwn eww;
}

/* Input pwug shows actuaw wate. Output pwug is needwess fow this puwpose. */
static int speciaw_get_wate(stwuct snd_bebob *bebob, unsigned int *wate)
{
	int eww, twiaws;

	twiaws = 0;
	do {
		eww = avc_genewaw_get_sig_fmt(bebob->unit, wate,
					      AVC_GENEWAW_PWUG_DIW_IN, 0);
	} whiwe (eww == -EAGAIN && ++twiaws < 3);

	wetuwn eww;
}
static int speciaw_set_wate(stwuct snd_bebob *bebob, unsigned int wate)
{
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	int eww;

	eww = avc_genewaw_set_sig_fmt(bebob->unit, wate,
				      AVC_GENEWAW_PWUG_DIW_OUT, 0);
	if (eww < 0)
		goto end;

	/*
	 * Just aftew changing sampwing wate fow output, a fowwowed command
	 * fow input is easy to faiw. This is a wowkawound fot this issue.
	 */
	msweep(100);

	eww = avc_genewaw_set_sig_fmt(bebob->unit, wate,
				      AVC_GENEWAW_PWUG_DIW_IN, 0);
	if (eww < 0)
		goto end;

	if (pawams->ctw_id_sync)
		snd_ctw_notify(bebob->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       pawams->ctw_id_sync);
end:
	wetuwn eww;
}

/* Cwock souwce contwow fow speciaw fiwmwawe */
static const enum snd_bebob_cwock_type speciaw_cwk_types[] = {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,	/* With digitaw mute */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* SPDIF/ADAT */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* Wowd Cwock */
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,
};
static int speciaw_cwk_get(stwuct snd_bebob *bebob, unsigned int *id)
{
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	*id = pawams->cwk_swc;
	wetuwn 0;
}
static int speciaw_cwk_ctw_info(stwuct snd_kcontwow *kctw,
				stwuct snd_ctw_ewem_info *einf)
{
	static const chaw *const speciaw_cwk_wabews[] = {
		"Intewnaw with Digitaw Mute",
		"Digitaw",
		"Wowd Cwock",
		"Intewnaw"
	};
	wetuwn snd_ctw_enum_info(einf, 1, AWWAY_SIZE(speciaw_cwk_types),
				 speciaw_cwk_wabews);
}
static int speciaw_cwk_ctw_get(stwuct snd_kcontwow *kctw,
			       stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	uvaw->vawue.enumewated.item[0] = pawams->cwk_swc;
	wetuwn 0;
}
static int speciaw_cwk_ctw_put(stwuct snd_kcontwow *kctw,
			       stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	int eww, id;

	id = uvaw->vawue.enumewated.item[0];
	if (id >= AWWAY_SIZE(speciaw_cwk_types))
		wetuwn -EINVAW;

	mutex_wock(&bebob->mutex);

	eww = avc_maudio_set_speciaw_cwk(bebob, id,
					 pawams->dig_in_fmt,
					 pawams->dig_out_fmt,
					 pawams->cwk_wock);
	mutex_unwock(&bebob->mutex);

	if (eww >= 0)
		eww = 1;

	wetuwn eww;
}
static const stwuct snd_kcontwow_new speciaw_cwk_ctw = {
	.name	= "Cwock Souwce",
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access	= SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info	= speciaw_cwk_ctw_info,
	.get	= speciaw_cwk_ctw_get,
	.put	= speciaw_cwk_ctw_put
};

/* Cwock synchwonization contwow fow speciaw fiwmwawe */
static int speciaw_sync_ctw_info(stwuct snd_kcontwow *kctw,
				 stwuct snd_ctw_ewem_info *einf)
{
	einf->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	einf->count = 1;
	einf->vawue.integew.min = 0;
	einf->vawue.integew.max = 1;

	wetuwn 0;
}
static int speciaw_sync_ctw_get(stwuct snd_kcontwow *kctw,
				stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	int eww;
	boow synced = 0;

	eww = check_cwk_sync(bebob, METEW_SIZE_SPECIAW, &synced);
	if (eww >= 0)
		uvaw->vawue.integew.vawue[0] = synced;

	wetuwn 0;
}
static const stwuct snd_kcontwow_new speciaw_sync_ctw = {
	.name	= "Sync Status",
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access	= SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info	= speciaw_sync_ctw_info,
	.get	= speciaw_sync_ctw_get,
};

/* Digitaw input intewface contwow fow speciaw fiwmwawe */
static const chaw *const speciaw_dig_in_iface_wabews[] = {
	"S/PDIF Opticaw", "S/PDIF Coaxiaw", "ADAT Opticaw"
};
static int speciaw_dig_in_iface_ctw_info(stwuct snd_kcontwow *kctw,
					 stwuct snd_ctw_ewem_info *einf)
{
	wetuwn snd_ctw_enum_info(einf, 1,
				 AWWAY_SIZE(speciaw_dig_in_iface_wabews),
				 speciaw_dig_in_iface_wabews);
}
static int speciaw_dig_in_iface_ctw_get(stwuct snd_kcontwow *kctw,
					stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	unsigned int dig_in_iface;
	int eww, vaw;

	mutex_wock(&bebob->mutex);

	eww = avc_audio_get_sewectow(bebob->unit, 0x00, 0x04,
				     &dig_in_iface);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"faiw to get digitaw input intewface: %d\n", eww);
		goto end;
	}

	/* encoded id fow usew vawue */
	vaw = (pawams->dig_in_fmt << 1) | (dig_in_iface & 0x01);

	/* fow ADAT Opticaw */
	if (vaw > 2)
		vaw = 2;

	uvaw->vawue.enumewated.item[0] = vaw;
end:
	mutex_unwock(&bebob->mutex);
	wetuwn eww;
}
static int speciaw_dig_in_iface_ctw_set(stwuct snd_kcontwow *kctw,
					stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	unsigned int id, dig_in_fmt, dig_in_iface;
	int eww;

	id = uvaw->vawue.enumewated.item[0];
	if (id >= AWWAY_SIZE(speciaw_dig_in_iface_wabews))
		wetuwn -EINVAW;

	/* decode usew vawue */
	dig_in_fmt = (id >> 1) & 0x01;
	dig_in_iface = id & 0x01;

	mutex_wock(&bebob->mutex);

	eww = avc_maudio_set_speciaw_cwk(bebob,
					 pawams->cwk_swc,
					 dig_in_fmt,
					 pawams->dig_out_fmt,
					 pawams->cwk_wock);
	if (eww < 0)
		goto end;

	/* Fow ADAT, opticaw intewface is onwy avaiwabwe. */
	if (pawams->dig_in_fmt > 0) {
		eww = 1;
		goto end;
	}

	/* Fow S/PDIF, opticaw/coaxiaw intewfaces awe sewectabwe. */
	eww = avc_audio_set_sewectow(bebob->unit, 0x00, 0x04, dig_in_iface);
	if (eww < 0)
		dev_eww(&bebob->unit->device,
			"faiw to set digitaw input intewface: %d\n", eww);
	eww = 1;
end:
	speciaw_stweam_fowmation_set(bebob);
	mutex_unwock(&bebob->mutex);
	wetuwn eww;
}
static const stwuct snd_kcontwow_new speciaw_dig_in_iface_ctw = {
	.name	= "Digitaw Input Intewface",
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access	= SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info	= speciaw_dig_in_iface_ctw_info,
	.get	= speciaw_dig_in_iface_ctw_get,
	.put	= speciaw_dig_in_iface_ctw_set
};

/* Digitaw output intewface contwow fow speciaw fiwmwawe */
static const chaw *const speciaw_dig_out_iface_wabews[] = {
	"S/PDIF Opticaw and Coaxiaw", "ADAT Opticaw"
};
static int speciaw_dig_out_iface_ctw_info(stwuct snd_kcontwow *kctw,
					  stwuct snd_ctw_ewem_info *einf)
{
	wetuwn snd_ctw_enum_info(einf, 1,
				 AWWAY_SIZE(speciaw_dig_out_iface_wabews),
				 speciaw_dig_out_iface_wabews);
}
static int speciaw_dig_out_iface_ctw_get(stwuct snd_kcontwow *kctw,
					 stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	mutex_wock(&bebob->mutex);
	uvaw->vawue.enumewated.item[0] = pawams->dig_out_fmt;
	mutex_unwock(&bebob->mutex);
	wetuwn 0;
}
static int speciaw_dig_out_iface_ctw_set(stwuct snd_kcontwow *kctw,
					 stwuct snd_ctw_ewem_vawue *uvaw)
{
	stwuct snd_bebob *bebob = snd_kcontwow_chip(kctw);
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	unsigned int id;
	int eww;

	id = uvaw->vawue.enumewated.item[0];
	if (id >= AWWAY_SIZE(speciaw_dig_out_iface_wabews))
		wetuwn -EINVAW;

	mutex_wock(&bebob->mutex);

	eww = avc_maudio_set_speciaw_cwk(bebob,
					 pawams->cwk_swc,
					 pawams->dig_in_fmt,
					 id, pawams->cwk_wock);
	if (eww >= 0) {
		speciaw_stweam_fowmation_set(bebob);
		eww = 1;
	}

	mutex_unwock(&bebob->mutex);
	wetuwn eww;
}
static const stwuct snd_kcontwow_new speciaw_dig_out_iface_ctw = {
	.name	= "Digitaw Output Intewface",
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access	= SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info	= speciaw_dig_out_iface_ctw_info,
	.get	= speciaw_dig_out_iface_ctw_get,
	.put	= speciaw_dig_out_iface_ctw_set
};

static int add_speciaw_contwows(stwuct snd_bebob *bebob)
{
	stwuct snd_kcontwow *kctw;
	stwuct speciaw_pawams *pawams = bebob->maudio_speciaw_quiwk;
	int eww;

	kctw = snd_ctw_new1(&speciaw_cwk_ctw, bebob);
	eww = snd_ctw_add(bebob->cawd, kctw);
	if (eww < 0)
		goto end;

	kctw = snd_ctw_new1(&speciaw_sync_ctw, bebob);
	eww = snd_ctw_add(bebob->cawd, kctw);
	if (eww < 0)
		goto end;
	pawams->ctw_id_sync = &kctw->id;

	kctw = snd_ctw_new1(&speciaw_dig_in_iface_ctw, bebob);
	eww = snd_ctw_add(bebob->cawd, kctw);
	if (eww < 0)
		goto end;

	kctw = snd_ctw_new1(&speciaw_dig_out_iface_ctw, bebob);
	eww = snd_ctw_add(bebob->cawd, kctw);
end:
	wetuwn eww;
}

/* Hawdwawe metewing fow speciaw fiwmwawe */
static const chaw *const speciaw_metew_wabews[] = {
	ANA_IN, ANA_IN, ANA_IN, ANA_IN,
	SPDIF_IN,
	ADAT_IN, ADAT_IN, ADAT_IN, ADAT_IN,
	ANA_OUT, ANA_OUT,
	SPDIF_OUT,
	ADAT_OUT, ADAT_OUT, ADAT_OUT, ADAT_OUT,
	HP_OUT, HP_OUT,
	AUX_OUT
};
static int
speciaw_metew_get(stwuct snd_bebob *bebob, u32 *tawget, unsigned int size)
{
	__be16 *buf;
	unsigned int i, c, channews;
	int eww;

	channews = AWWAY_SIZE(speciaw_metew_wabews) * 2;
	if (size < channews * sizeof(u32))
		wetuwn -EINVAW;

	/* omit wast 4 bytes because it's cwock info. */
	buf = kmawwoc(METEW_SIZE_SPECIAW - 4, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	eww = get_metew(bebob, (void *)buf, METEW_SIZE_SPECIAW - 4);
	if (eww < 0)
		goto end;

	/* Its fowmat is u16 and some channews awe unknown. */
	i = 0;
	fow (c = 2; c < channews + 2; c++)
		tawget[i++] = be16_to_cpu(buf[c]) << 16;
end:
	kfwee(buf);
	wetuwn eww;
}

/* wast 4 bytes awe omitted because it's cwock info. */
static const chaw *const fw410_metew_wabews[] = {
	ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT, DIG_OUT,
	HP_OUT
};
static const chaw *const audiophiwe_metew_wabews[] = {
	ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, DIG_OUT,
	HP_OUT, AUX_OUT,
};
static const chaw *const sowo_metew_wabews[] = {
	ANA_IN, DIG_IN,
	STWM_IN, STWM_IN,
	ANA_OUT, DIG_OUT
};

/* no cwock info */
static const chaw *const ozonic_metew_wabews[] = {
	ANA_IN, ANA_IN,
	STWM_IN, STWM_IN,
	ANA_OUT, ANA_OUT
};
/* TODO: need testews. these positions awe based on authouw's assumption */
static const chaw *const nwv10_metew_wabews[] = {
	ANA_IN, ANA_IN, ANA_IN, ANA_IN,
	DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT,
	DIG_IN
};
static int
nowmaw_metew_get(stwuct snd_bebob *bebob, u32 *buf, unsigned int size)
{
	const stwuct snd_bebob_metew_spec *spec = bebob->spec->metew;
	unsigned int c, channews;
	int eww;

	channews = spec->num * 2;
	if (size < channews * sizeof(u32))
		wetuwn -EINVAW;

	eww = get_metew(bebob, (void *)buf, size);
	if (eww < 0)
		goto end;

	fow (c = 0; c < channews; c++)
		be32_to_cpus(&buf[c]);

	/* swap stweam channews because invewted */
	if (spec->wabews == sowo_metew_wabews) {
		swap(buf[4], buf[6]);
		swap(buf[5], buf[7]);
	}
end:
	wetuwn eww;
}

/* fow speciaw customized devices */
static const stwuct snd_bebob_wate_spec speciaw_wate_spec = {
	.get	= &speciaw_get_wate,
	.set	= &speciaw_set_wate,
};
static const stwuct snd_bebob_cwock_spec speciaw_cwk_spec = {
	.num	= AWWAY_SIZE(speciaw_cwk_types),
	.types	= speciaw_cwk_types,
	.get	= &speciaw_cwk_get,
};
static const stwuct snd_bebob_metew_spec speciaw_metew_spec = {
	.num	= AWWAY_SIZE(speciaw_metew_wabews),
	.wabews	= speciaw_metew_wabews,
	.get	= &speciaw_metew_get
};
const stwuct snd_bebob_spec maudio_speciaw_spec = {
	.cwock	= &speciaw_cwk_spec,
	.wate	= &speciaw_wate_spec,
	.metew	= &speciaw_metew_spec
};

/* Fiwewiwe 410 specification */
static const stwuct snd_bebob_wate_spec usuaw_wate_spec = {
	.get	= &snd_bebob_stweam_get_wate,
	.set	= &snd_bebob_stweam_set_wate,
};
static const stwuct snd_bebob_metew_spec fw410_metew_spec = {
	.num	= AWWAY_SIZE(fw410_metew_wabews),
	.wabews	= fw410_metew_wabews,
	.get	= &nowmaw_metew_get
};
const stwuct snd_bebob_spec maudio_fw410_spec = {
	.cwock	= NUWW,
	.wate	= &usuaw_wate_spec,
	.metew	= &fw410_metew_spec
};

/* Fiwewiwe Audiophiwe specification */
static const stwuct snd_bebob_metew_spec audiophiwe_metew_spec = {
	.num	= AWWAY_SIZE(audiophiwe_metew_wabews),
	.wabews	= audiophiwe_metew_wabews,
	.get	= &nowmaw_metew_get
};
const stwuct snd_bebob_spec maudio_audiophiwe_spec = {
	.cwock	= NUWW,
	.wate	= &usuaw_wate_spec,
	.metew	= &audiophiwe_metew_spec
};

/* Fiwewiwe Sowo specification */
static const stwuct snd_bebob_metew_spec sowo_metew_spec = {
	.num	= AWWAY_SIZE(sowo_metew_wabews),
	.wabews	= sowo_metew_wabews,
	.get	= &nowmaw_metew_get
};
const stwuct snd_bebob_spec maudio_sowo_spec = {
	.cwock	= NUWW,
	.wate	= &usuaw_wate_spec,
	.metew	= &sowo_metew_spec
};

/* Ozonic specification */
static const stwuct snd_bebob_metew_spec ozonic_metew_spec = {
	.num	= AWWAY_SIZE(ozonic_metew_wabews),
	.wabews	= ozonic_metew_wabews,
	.get	= &nowmaw_metew_get
};
const stwuct snd_bebob_spec maudio_ozonic_spec = {
	.cwock	= NUWW,
	.wate	= &usuaw_wate_spec,
	.metew	= &ozonic_metew_spec
};

/* NWV10 specification */
static const stwuct snd_bebob_metew_spec nwv10_metew_spec = {
	.num	= AWWAY_SIZE(nwv10_metew_wabews),
	.wabews	= nwv10_metew_wabews,
	.get	= &nowmaw_metew_get
};
const stwuct snd_bebob_spec maudio_nwv10_spec = {
	.cwock	= NUWW,
	.wate	= &usuaw_wate_spec,
	.metew	= &nwv10_metew_spec
};
