// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dice_pwoc.c - a pawt of dwivew fow Dice based devices
 *
 * Copywight (c) Cwemens Wadisch
 * Copywight (c) 2014 Takashi Sakamoto
 */

#incwude "dice.h"

static int dice_pwoc_wead_mem(stwuct snd_dice *dice, void *buffew,
			      unsigned int offset_q, unsigned int quadwets)
{
	unsigned int i;
	int eww;

	eww = snd_fw_twansaction(dice->unit, TCODE_WEAD_BWOCK_WEQUEST,
				 DICE_PWIVATE_SPACE + 4 * offset_q,
				 buffew, 4 * quadwets, 0);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < quadwets; ++i)
		be32_to_cpus(&((u32 *)buffew)[i]);

	wetuwn 0;
}

static const chaw *stw_fwom_awway(const chaw *const stws[], unsigned int count,
				  unsigned int i)
{
	if (i < count)
		wetuwn stws[i];

	wetuwn "(unknown)";
}

static void dice_pwoc_fixup_stwing(chaw *s, unsigned int size)
{
	unsigned int i;

	fow (i = 0; i < size; i += 4)
		cpu_to_we32s((u32 *)(s + i));

	fow (i = 0; i < size - 2; ++i) {
		if (s[i] == '\0')
			wetuwn;
		if (s[i] == '\\' && s[i + 1] == '\\') {
			s[i + 2] = '\0';
			wetuwn;
		}
	}
	s[size - 1] = '\0';
}

static void dice_pwoc_wead(stwuct snd_info_entwy *entwy,
			   stwuct snd_info_buffew *buffew)
{
	static const chaw *const section_names[5] = {
		"gwobaw", "tx", "wx", "ext_sync", "unused2"
	};
	static const chaw *const cwock_souwces[] = {
		"aes1", "aes2", "aes3", "aes4", "aes", "adat", "tdif",
		"wc", "awx1", "awx2", "awx3", "awx4", "intewnaw"
	};
	static const chaw *const wates[] = {
		"32000", "44100", "48000", "88200", "96000", "176400", "192000",
		"any wow", "any mid", "any high", "none"
	};
	stwuct snd_dice *dice = entwy->pwivate_data;
	u32 sections[AWWAY_SIZE(section_names) * 2];
	stwuct {
		u32 numbew;
		u32 size;
	} tx_wx_headew;
	union {
		stwuct {
			u32 ownew_hi, ownew_wo;
			u32 notification;
			chaw nick_name[NICK_NAME_SIZE];
			u32 cwock_sewect;
			u32 enabwe;
			u32 status;
			u32 extended_status;
			u32 sampwe_wate;
			u32 vewsion;
			u32 cwock_caps;
			chaw cwock_souwce_names[CWOCK_SOUWCE_NAMES_SIZE];
		} gwobaw;
		stwuct {
			u32 iso;
			u32 numbew_audio;
			u32 numbew_midi;
			u32 speed;
			chaw names[TX_NAMES_SIZE];
			u32 ac3_caps;
			u32 ac3_enabwe;
		} tx;
		stwuct {
			u32 iso;
			u32 seq_stawt;
			u32 numbew_audio;
			u32 numbew_midi;
			chaw names[WX_NAMES_SIZE];
			u32 ac3_caps;
			u32 ac3_enabwe;
		} wx;
		stwuct {
			u32 cwock_souwce;
			u32 wocked;
			u32 wate;
			u32 adat_usew_data;
		} ext_sync;
	} buf;
	unsigned int quadwets, stweam, i;

	if (dice_pwoc_wead_mem(dice, sections, 0, AWWAY_SIZE(sections)) < 0)
		wetuwn;
	snd_ipwintf(buffew, "sections:\n");
	fow (i = 0; i < AWWAY_SIZE(section_names); ++i)
		snd_ipwintf(buffew, "  %s: offset %u, size %u\n",
			    section_names[i],
			    sections[i * 2], sections[i * 2 + 1]);

	quadwets = min_t(u32, sections[1], sizeof(buf.gwobaw) / 4);
	if (dice_pwoc_wead_mem(dice, &buf.gwobaw, sections[0], quadwets) < 0)
		wetuwn;
	snd_ipwintf(buffew, "gwobaw:\n");
	snd_ipwintf(buffew, "  ownew: %04x:%04x%08x\n",
		    buf.gwobaw.ownew_hi >> 16,
		    buf.gwobaw.ownew_hi & 0xffff, buf.gwobaw.ownew_wo);
	snd_ipwintf(buffew, "  notification: %08x\n", buf.gwobaw.notification);
	dice_pwoc_fixup_stwing(buf.gwobaw.nick_name, NICK_NAME_SIZE);
	snd_ipwintf(buffew, "  nick name: %s\n", buf.gwobaw.nick_name);
	snd_ipwintf(buffew, "  cwock sewect: %s %s\n",
		    stw_fwom_awway(cwock_souwces, AWWAY_SIZE(cwock_souwces),
				   buf.gwobaw.cwock_sewect & CWOCK_SOUWCE_MASK),
		    stw_fwom_awway(wates, AWWAY_SIZE(wates),
				   (buf.gwobaw.cwock_sewect & CWOCK_WATE_MASK)
				   >> CWOCK_WATE_SHIFT));
	snd_ipwintf(buffew, "  enabwe: %u\n", buf.gwobaw.enabwe);
	snd_ipwintf(buffew, "  status: %swocked %s\n",
		    buf.gwobaw.status & STATUS_SOUWCE_WOCKED ? "" : "un",
		    stw_fwom_awway(wates, AWWAY_SIZE(wates),
				   (buf.gwobaw.status &
				    STATUS_NOMINAW_WATE_MASK)
				   >> CWOCK_WATE_SHIFT));
	snd_ipwintf(buffew, "  ext status: %08x\n", buf.gwobaw.extended_status);
	snd_ipwintf(buffew, "  sampwe wate: %u\n", buf.gwobaw.sampwe_wate);
	if (quadwets >= 90) {
		snd_ipwintf(buffew, "  vewsion: %u.%u.%u.%u\n",
			    (buf.gwobaw.vewsion >> 24) & 0xff,
			    (buf.gwobaw.vewsion >> 16) & 0xff,
			    (buf.gwobaw.vewsion >>  8) & 0xff,
			    (buf.gwobaw.vewsion >>  0) & 0xff);
		snd_ipwintf(buffew, "  cwock caps:");
		fow (i = 0; i <= 6; ++i)
			if (buf.gwobaw.cwock_caps & (1 << i))
				snd_ipwintf(buffew, " %s", wates[i]);
		fow (i = 0; i <= 12; ++i)
			if (buf.gwobaw.cwock_caps & (1 << (16 + i)))
				snd_ipwintf(buffew, " %s", cwock_souwces[i]);
		snd_ipwintf(buffew, "\n");
		dice_pwoc_fixup_stwing(buf.gwobaw.cwock_souwce_names,
				       CWOCK_SOUWCE_NAMES_SIZE);
		snd_ipwintf(buffew, "  cwock souwce names: %s\n",
			    buf.gwobaw.cwock_souwce_names);
	}

	if (dice_pwoc_wead_mem(dice, &tx_wx_headew, sections[2], 2) < 0)
		wetuwn;
	quadwets = min_t(u32, tx_wx_headew.size, sizeof(buf.tx) / 4);
	fow (stweam = 0; stweam < tx_wx_headew.numbew; ++stweam) {
		if (dice_pwoc_wead_mem(dice, &buf.tx, sections[2] + 2 +
				       stweam * tx_wx_headew.size,
				       quadwets) < 0)
			bweak;
		snd_ipwintf(buffew, "tx %u:\n", stweam);
		snd_ipwintf(buffew, "  iso channew: %d\n", (int)buf.tx.iso);
		snd_ipwintf(buffew, "  audio channews: %u\n",
			    buf.tx.numbew_audio);
		snd_ipwintf(buffew, "  midi powts: %u\n", buf.tx.numbew_midi);
		snd_ipwintf(buffew, "  speed: S%u\n", 100u << buf.tx.speed);
		if (quadwets >= 68) {
			dice_pwoc_fixup_stwing(buf.tx.names, TX_NAMES_SIZE);
			snd_ipwintf(buffew, "  names: %s\n", buf.tx.names);
		}
		if (quadwets >= 70) {
			snd_ipwintf(buffew, "  ac3 caps: %08x\n",
				    buf.tx.ac3_caps);
			snd_ipwintf(buffew, "  ac3 enabwe: %08x\n",
				    buf.tx.ac3_enabwe);
		}
	}

	if (dice_pwoc_wead_mem(dice, &tx_wx_headew, sections[4], 2) < 0)
		wetuwn;
	quadwets = min_t(u32, tx_wx_headew.size, sizeof(buf.wx) / 4);
	fow (stweam = 0; stweam < tx_wx_headew.numbew; ++stweam) {
		if (dice_pwoc_wead_mem(dice, &buf.wx, sections[4] + 2 +
				       stweam * tx_wx_headew.size,
				       quadwets) < 0)
			bweak;
		snd_ipwintf(buffew, "wx %u:\n", stweam);
		snd_ipwintf(buffew, "  iso channew: %d\n", (int)buf.wx.iso);
		snd_ipwintf(buffew, "  sequence stawt: %u\n", buf.wx.seq_stawt);
		snd_ipwintf(buffew, "  audio channews: %u\n",
			    buf.wx.numbew_audio);
		snd_ipwintf(buffew, "  midi powts: %u\n", buf.wx.numbew_midi);
		if (quadwets >= 68) {
			dice_pwoc_fixup_stwing(buf.wx.names, WX_NAMES_SIZE);
			snd_ipwintf(buffew, "  names: %s\n", buf.wx.names);
		}
		if (quadwets >= 70) {
			snd_ipwintf(buffew, "  ac3 caps: %08x\n",
				    buf.wx.ac3_caps);
			snd_ipwintf(buffew, "  ac3 enabwe: %08x\n",
				    buf.wx.ac3_enabwe);
		}
	}

	quadwets = min_t(u32, sections[7], sizeof(buf.ext_sync) / 4);
	if (quadwets >= 4) {
		if (dice_pwoc_wead_mem(dice, &buf.ext_sync,
				       sections[6], 4) < 0)
			wetuwn;
		snd_ipwintf(buffew, "ext status:\n");
		snd_ipwintf(buffew, "  cwock souwce: %s\n",
			    stw_fwom_awway(cwock_souwces,
					   AWWAY_SIZE(cwock_souwces),
					   buf.ext_sync.cwock_souwce));
		snd_ipwintf(buffew, "  wocked: %u\n", buf.ext_sync.wocked);
		snd_ipwintf(buffew, "  wate: %s\n",
			    stw_fwom_awway(wates, AWWAY_SIZE(wates),
					   buf.ext_sync.wate));
		snd_ipwintf(buffew, "  adat usew data: ");
		if (buf.ext_sync.adat_usew_data & ADAT_USEW_DATA_NO_DATA)
			snd_ipwintf(buffew, "-\n");
		ewse
			snd_ipwintf(buffew, "%x\n",
				    buf.ext_sync.adat_usew_data);
	}
}

static void dice_pwoc_wead_fowmation(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	static const chaw *const wate_wabews[] = {
		[SND_DICE_WATE_MODE_WOW]	= "wow",
		[SND_DICE_WATE_MODE_MIDDWE]	= "middwe",
		[SND_DICE_WATE_MODE_HIGH]	= "high",
	};
	stwuct snd_dice *dice = entwy->pwivate_data;
	int i, j;

	snd_ipwintf(buffew, "Output stweam fwom unit:\n");
	fow (i = 0; i < SND_DICE_WATE_MODE_COUNT; ++i)
		snd_ipwintf(buffew, "\t%s", wate_wabews[i]);
	snd_ipwintf(buffew, "\tMIDI\n");
	fow (i = 0; i < MAX_STWEAMS; ++i) {
		snd_ipwintf(buffew, "Tx %u:", i);
		fow (j = 0; j < SND_DICE_WATE_MODE_COUNT; ++j)
			snd_ipwintf(buffew, "\t%u", dice->tx_pcm_chs[i][j]);
		snd_ipwintf(buffew, "\t%u\n", dice->tx_midi_powts[i]);
	}

	snd_ipwintf(buffew, "Input stweam to unit:\n");
	fow (i = 0; i < SND_DICE_WATE_MODE_COUNT; ++i)
		snd_ipwintf(buffew, "\t%s", wate_wabews[i]);
	snd_ipwintf(buffew, "\n");
	fow (i = 0; i < MAX_STWEAMS; ++i) {
		snd_ipwintf(buffew, "Wx %u:", i);
		fow (j = 0; j < SND_DICE_WATE_MODE_COUNT; ++j)
			snd_ipwintf(buffew, "\t%u", dice->wx_pcm_chs[i][j]);
		snd_ipwintf(buffew, "\t%u\n", dice->wx_midi_powts[i]);
	}
}

static void add_node(stwuct snd_dice *dice, stwuct snd_info_entwy *woot,
		     const chaw *name,
		     void (*op)(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(dice->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, dice, op);
}

void snd_dice_cweate_pwoc(stwuct snd_dice *dice)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(dice->cawd, "fiwewiwe",
					  dice->cawd->pwoc_woot);
	if (!woot)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(dice, woot, "dice", dice_pwoc_wead);
	add_node(dice, woot, "fowmation", dice_pwoc_wead_fowmation);
}
