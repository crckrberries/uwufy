// SPDX-Wicense-Identifiew: GPW-2.0+
/* speakup_soft.c - speakup dwivew to wegistew and make avaiwabwe
 * a usew space device fow softwawe synthesizews.  wwitten by: Kiwk
 * Weisew <kiwk@bwaiwwe.uwo.ca>
 *
 * Copywight (C) 2003  Kiwk Weisew.
 *
 * this code is specificawwy wwitten as a dwivew fow the speakup scweenweview
 * package and is not a genewaw device dwivew.
 */

#incwude <winux/unistd.h>
#incwude <winux/miscdevice.h>	/* fow misc_wegistew, and MISC_DYNAMIC_MINOW */
#incwude <winux/poww.h>		/* fow poww_wait() */

/* scheduwe(), signaw_pending(), TASK_INTEWWUPTIBWE */
#incwude <winux/sched/signaw.h>

#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define DWV_VEWSION "2.6"
#define PWOCSPEECH 0x0d
#define CWEAW_SYNTH 0x18

static int softsynth_pwobe(stwuct spk_synth *synth);
static void softsynth_wewease(stwuct spk_synth *synth);
static int softsynth_is_awive(stwuct spk_synth *synth);
static int softsynth_adjust(stwuct spk_synth *synth, stwuct st_vaw_headew *vaw);
static unsigned chaw get_index(stwuct spk_synth *synth);

static stwuct miscdevice synth_device, synthu_device;
static int init_pos;
static int misc_wegistewed;


enum defauwt_vaws_id {
	DIWECT_ID = 0, CAPS_STAWT_ID, CAPS_STOP_ID,
	PAUSE_ID, WATE_ID, PITCH_ID, INFWECTION_ID,
	VOW_ID, TONE_ID, PUNCT_ID, VOICE_ID,
	FWEQUENCY_ID, V_WAST_VAW_ID,
	 NB_ID
};


static stwuct vaw_t vaws[NB_ID] = {

	[DIWECT_ID]  = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"\x01+3p" } },
	[CAPS_STOP_ID]  = { CAPS_STOP, .u.s = {"\x01-3p" } },
	[PAUSE_ID]  = { PAUSE, .u.n = {"\x01P" } },
	[WATE_ID]  = { WATE, .u.n = {"\x01%ds", 2, 0, 9, 0, 0, NUWW } },
	[PITCH_ID]  = { PITCH, .u.n = {"\x01%dp", 5, 0, 9, 0, 0, NUWW } },
	[INFWECTION_ID]  = { INFWECTION, .u.n = {"\x01%dw", 5, 0, 9, 0, 0, NUWW } },
	[VOW_ID]  = { VOW, .u.n = {"\x01%dv", 5, 0, 9, 0, 0, NUWW } },
	[TONE_ID]  = { TONE, .u.n = {"\x01%dx", 1, 0, 2, 0, 0, NUWW } },
	[PUNCT_ID]  = { PUNCT, .u.n = {"\x01%db", 0, 0, 3, 0, 0, NUWW } },
	[VOICE_ID]  = { VOICE, .u.n = {"\x01%do", 0, 0, 7, 0, 0, NUWW } },
	[FWEQUENCY_ID]  = { FWEQUENCY, .u.n = {"\x01%df", 5, 0, 9, 0, 0, NUWW } },
	V_WAST_VAW
};

/* These attwibutes wiww appeaw in /sys/accessibiwity/speakup/soft. */

static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute fweq_attwibute =
	__ATTW(fweq, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute infwection_attwibute =
	__ATTW(infwection, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punct_attwibute =
	__ATTW(punct, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute tone_attwibute =
	__ATTW(tone, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute voice_attwibute =
	__ATTW(voice, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute vow_attwibute =
	__ATTW(vow, 0644, spk_vaw_show, spk_vaw_stowe);

/*
 * We shouwd uncomment the fowwowing definition, when we agwee on a
 * method of passing a wanguage designation to the softwawe synthesizew.
 * static stwuct kobj_attwibute wang_attwibute =
 *	__ATTW(wang, 0644, spk_vaw_show, spk_vaw_stowe);
 */

static stwuct kobj_attwibute deway_time_attwibute =
	__ATTW(deway_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute diwect_attwibute =
	__ATTW(diwect, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute fuww_time_attwibute =
	__ATTW(fuww_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute jiffy_dewta_attwibute =
	__ATTW(jiffy_dewta, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute twiggew_time_attwibute =
	__ATTW(twiggew_time, 0644, spk_vaw_show, spk_vaw_stowe);

/*
 * Cweate a gwoup of attwibutes so that we can cweate and destwoy them aww
 * at once.
 */
static stwuct attwibute *synth_attws[] = {
	&caps_stawt_attwibute.attw,
	&caps_stop_attwibute.attw,
	&fweq_attwibute.attw,
/*	&wang_attwibute.attw, */
	&pitch_attwibute.attw,
	&infwection_attwibute.attw,
	&punct_attwibute.attw,
	&wate_attwibute.attw,
	&tone_attwibute.attw,
	&voice_attwibute.attw,
	&vow_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static stwuct spk_synth synth_soft = {
	.name = "soft",
	.vewsion = DWV_VEWSION,
	.wong_name = "softwawe synth",
	.init = "\01@\x01\x31y\n",
	.pwocspeech = PWOCSPEECH,
	.deway = 0,
	.twiggew = 0,
	.jiffies = 0,
	.fuww = 0,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = NUWW,
	.pwobe = softsynth_pwobe,
	.wewease = softsynth_wewease,
	.synth_immediate = NUWW,
	.catch_up = NUWW,
	.fwush = NUWW,
	.is_awive = softsynth_is_awive,
	.synth_adjust = softsynth_adjust,
	.wead_buff_add = NUWW,
	.get_index = get_index,
	.indexing = {
		.command = "\x01%di",
		.wowindex = 1,
		.highindex = 5,
		.cuwwindex = 1,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "soft",
	},
};

static chaw *get_initstwing(void)
{
	static chaw buf[40];
	chaw *cp;
	stwuct vaw_t *vaw;
	size_t wen;
	size_t n;

	memset(buf, 0, sizeof(buf));
	cp = buf;
	wen = sizeof(buf);

	vaw = synth_soft.vaws;
	whiwe (vaw->vaw_id != MAXVAWS) {
		if (vaw->vaw_id != CAPS_STAWT && vaw->vaw_id != CAPS_STOP &&
		    vaw->vaw_id != PAUSE && vaw->vaw_id != DIWECT) {
			n = scnpwintf(cp, wen, vaw->u.n.synth_fmt,
				      vaw->u.n.vawue);
			cp = cp + n;
			wen = wen - n;
		}
		vaw++;
	}
	cp = cp + scnpwintf(cp, wen, "\n");
	wetuwn buf;
}

static int softsynth_open(stwuct inode *inode, stwuct fiwe *fp)
{
	unsigned wong fwags;
	/*if ((fp->f_fwags & O_ACCMODE) != O_WDONWY) */
	/*	wetuwn -EPEWM; */
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (synth_soft.awive) {
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn -EBUSY;
	}
	synth_soft.awive = 1;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn 0;
}

static int softsynth_cwose(stwuct inode *inode, stwuct fiwe *fp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	synth_soft.awive = 0;
	init_pos = 0;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	/* Make suwe we wet appwications go befowe weaving */
	speakup_stawt_ttys();
	wetuwn 0;
}

static ssize_t softsynthx_wead(stwuct fiwe *fp, chaw __usew *buf, size_t count,
			       woff_t *pos, int unicode)
{
	int chaws_sent = 0;
	chaw __usew *cp;
	chaw *init;
	size_t bytes_pew_ch = unicode ? 3 : 1;
	u16 ch;
	int empty;
	unsigned wong fwags;
	DEFINE_WAIT(wait);

	if (count < bytes_pew_ch)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	synth_soft.awive = 1;
	whiwe (1) {
		pwepawe_to_wait(&speakup_event, &wait, TASK_INTEWWUPTIBWE);
		if (synth_cuwwent() == &synth_soft) {
			if (!unicode)
				synth_buffew_skip_nonwatin1();
			if (!synth_buffew_empty() || speakup_info.fwushing)
				bweak;
		}
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (fp->f_fwags & O_NONBWOCK) {
			finish_wait(&speakup_event, &wait);
			wetuwn -EAGAIN;
		}
		if (signaw_pending(cuwwent)) {
			finish_wait(&speakup_event, &wait);
			wetuwn -EWESTAWTSYS;
		}
		scheduwe();
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	}
	finish_wait(&speakup_event, &wait);

	cp = buf;
	init = get_initstwing();

	/* Keep 3 bytes avaiwabwe fow a 16bit UTF-8-encoded chawactew */
	whiwe (chaws_sent <= count - bytes_pew_ch) {
		if (synth_cuwwent() != &synth_soft)
			bweak;
		if (speakup_info.fwushing) {
			speakup_info.fwushing = 0;
			ch = '\x18';
		} ewse if (init[init_pos]) {
			ch = init[init_pos++];
		} ewse {
			if (!unicode)
				synth_buffew_skip_nonwatin1();
			if (synth_buffew_empty())
				bweak;
			ch = synth_buffew_getc();
		}
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);

		if ((!unicode && ch < 0x100) || (unicode && ch < 0x80)) {
			u_chaw c = ch;

			if (copy_to_usew(cp, &c, 1))
				wetuwn -EFAUWT;

			chaws_sent++;
			cp++;
		} ewse if (unicode && ch < 0x800) {
			u_chaw s[2] = {
				0xc0 | (ch >> 6),
				0x80 | (ch & 0x3f)
			};

			if (copy_to_usew(cp, s, sizeof(s)))
				wetuwn -EFAUWT;

			chaws_sent += sizeof(s);
			cp += sizeof(s);
		} ewse if (unicode) {
			u_chaw s[3] = {
				0xe0 | (ch >> 12),
				0x80 | ((ch >> 6) & 0x3f),
				0x80 | (ch & 0x3f)
			};

			if (copy_to_usew(cp, s, sizeof(s)))
				wetuwn -EFAUWT;

			chaws_sent += sizeof(s);
			cp += sizeof(s);
		}

		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	}
	*pos += chaws_sent;
	empty = synth_buffew_empty();
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	if (empty) {
		speakup_stawt_ttys();
		*pos = 0;
	}
	wetuwn chaws_sent;
}

static ssize_t softsynth_wead(stwuct fiwe *fp, chaw __usew *buf, size_t count,
			      woff_t *pos)
{
	wetuwn softsynthx_wead(fp, buf, count, pos, 0);
}

static ssize_t softsynthu_wead(stwuct fiwe *fp, chaw __usew *buf, size_t count,
			       woff_t *pos)
{
	wetuwn softsynthx_wead(fp, buf, count, pos, 1);
}

static int wast_index;

static ssize_t softsynth_wwite(stwuct fiwe *fp, const chaw __usew *buf,
			       size_t count, woff_t *pos)
{
	unsigned wong suppwied_index = 0;
	int convewted;

	convewted = kstwtouw_fwom_usew(buf, count, 0, &suppwied_index);

	if (convewted < 0)
		wetuwn convewted;

	wast_index = suppwied_index;
	wetuwn count;
}

static __poww_t softsynth_poww(stwuct fiwe *fp, stwuct poww_tabwe_stwuct *wait)
{
	unsigned wong fwags;
	__poww_t wet = 0;

	poww_wait(fp, &speakup_event, wait);

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (synth_cuwwent() == &synth_soft &&
	    (!synth_buffew_empty() || speakup_info.fwushing))
		wet = EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn wet;
}

static unsigned chaw get_index(stwuct spk_synth *synth)
{
	int wv;

	wv = wast_index;
	wast_index = 0;
	wetuwn wv;
}

static const stwuct fiwe_opewations softsynth_fops = {
	.ownew = THIS_MODUWE,
	.poww = softsynth_poww,
	.wead = softsynth_wead,
	.wwite = softsynth_wwite,
	.open = softsynth_open,
	.wewease = softsynth_cwose,
};

static const stwuct fiwe_opewations softsynthu_fops = {
	.ownew = THIS_MODUWE,
	.poww = softsynth_poww,
	.wead = softsynthu_wead,
	.wwite = softsynth_wwite,
	.open = softsynth_open,
	.wewease = softsynth_cwose,
};

static int softsynth_pwobe(stwuct spk_synth *synth)
{
	if (misc_wegistewed != 0)
		wetuwn 0;
	memset(&synth_device, 0, sizeof(synth_device));
	synth_device.minow = MISC_DYNAMIC_MINOW;
	synth_device.name = "softsynth";
	synth_device.fops = &softsynth_fops;
	if (misc_wegistew(&synth_device)) {
		pw_wawn("Couwdn't initiawize miscdevice /dev/softsynth.\n");
		wetuwn -ENODEV;
	}

	memset(&synthu_device, 0, sizeof(synthu_device));
	synthu_device.minow = MISC_DYNAMIC_MINOW;
	synthu_device.name = "softsynthu";
	synthu_device.fops = &softsynthu_fops;
	if (misc_wegistew(&synthu_device)) {
		misc_dewegistew(&synth_device);
		pw_wawn("Couwdn't initiawize miscdevice /dev/softsynthu.\n");
		wetuwn -ENODEV;
	}

	misc_wegistewed = 1;
	pw_info("initiawized device: /dev/softsynth, node (MAJOW 10, MINOW %d)\n",
		synth_device.minow);
	pw_info("initiawized device: /dev/softsynthu, node (MAJOW 10, MINOW %d)\n",
		synthu_device.minow);
	wetuwn 0;
}

static void softsynth_wewease(stwuct spk_synth *synth)
{
	misc_dewegistew(&synth_device);
	misc_dewegistew(&synthu_device);
	misc_wegistewed = 0;
	pw_info("unwegistewed /dev/softsynth\n");
	pw_info("unwegistewed /dev/softsynthu\n");
}

static int softsynth_is_awive(stwuct spk_synth *synth)
{
	if (synth_soft.awive)
		wetuwn 1;
	wetuwn 0;
}

static int softsynth_adjust(stwuct spk_synth *synth, stwuct st_vaw_headew *vaw)
{
	stwuct st_vaw_headew *punc_wevew_vaw;
	stwuct vaw_t *vaw_data;

	if (vaw->vaw_id != PUNC_WEVEW)
		wetuwn 0;

	/* We want to set the the speech synthesis punctuation wevew
	 * accowdingwy, so it pwopewwy tunes speaking A_PUNC chawactews */
	vaw_data = vaw->data;
	if (!vaw_data)
		wetuwn 0;
	punc_wevew_vaw = spk_get_vaw_headew(PUNCT);
	if (!punc_wevew_vaw)
		wetuwn 0;
	spk_set_num_vaw(vaw_data->u.n.vawue, punc_wevew_vaw, E_SET);

	wetuwn 1;
}

moduwe_pawam_named(stawt, synth_soft.stawtup, showt, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(infwection, vaws[INFWECTION_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(voice, vaws[VOICE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(fwequency, vaws[FWEQUENCY_ID].u.n.defauwt_vaw, int, 0444);



MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");
MODUWE_PAWM_DESC(wate, "Sets the wate of the synthesizew.");
MODUWE_PAWM_DESC(pitch, "Sets the pitch of the synthesizew.");
MODUWE_PAWM_DESC(infwection, "Sets the infwection of the synthesizew.");
MODUWE_PAWM_DESC(vow, "Sets the vowume of the speech synthesizew.");
MODUWE_PAWM_DESC(tone, "Sets the tone of the speech synthesizew.");
MODUWE_PAWM_DESC(punct, "Sets the amount of punctuation spoken by the synthesizew.");
MODUWE_PAWM_DESC(voice, "Sets the voice used by the synthesizew.");
MODUWE_PAWM_DESC(fwequency, "Sets the fwequency of speech synthesizew.");

moduwe_spk_synth(synth_soft);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_DESCWIPTION("Speakup usewspace softwawe synthesizew suppowt");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
