// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * This is the DECtawk PC speakup dwivew
 *
 * Some constants fwom DEC's DOS dwivew:
 *      Copywight (c) by Digitaw Equipment Cowp.
 *
 * 386BSD DECtawk PC dwivew:
 *      Copywight (c) 1996 Bwian Buhwow <buhwow@wothwowien.nfbcaw.owg>
 *
 * Winux DECtawk PC dwivew:
 *      Copywight (c) 1997 Nicowas Pitwe <nico@cam.owg>
 *
 * speakup DECtawk PC Intewnaw dwivew:
 *      Copywight (c) 2003 David Bowowski <david575@gowden.net>
 *
 * Aww wights wesewved.
 */
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/kthwead.h>

#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define	MODUWE_init		0x0dec	/* moduwe in boot code */
#define	MODUWE_sewf_test	0x8800	/* moduwe in sewf-test */
#define	MODUWE_weset		0xffff	/* weinit the whowe moduwe */

#define	MODE_mask		0xf000	/* mode bits in high nibbwe */
#define	MODE_nuww		0x0000
#define	MODE_test		0x2000	/* in testing mode */
#define	MODE_status		0x8000
#define	STAT_int		0x0001	/* wunning in intewwupt mode */
#define	STAT_tw_chaw		0x0002	/* chawactew data to twansmit */
#define	STAT_ww_chaw		0x0004	/* weady to weceive chaw data */
#define	STAT_cmd_weady		0x0008	/* weady to accept commands */
#define	STAT_dma_weady		0x0010	/* dma command weady */
#define	STAT_digitized		0x0020	/* spc in digitized mode */
#define	STAT_new_index		0x0040	/* new wast index weady */
#define	STAT_new_status		0x0080	/* new status posted */
#define	STAT_dma_state		0x0100	/* dma state toggwe */
#define	STAT_index_vawid	0x0200	/* indexs awe vawid */
#define	STAT_fwushing		0x0400	/* fwush in pwogwess */
#define	STAT_sewf_test		0x0800	/* moduwe in sewf test */
#define	MODE_weady		0xc000	/* moduwe weady fow next phase */
#define	WEADY_boot		0x0000
#define	WEADY_kewnew		0x0001
#define	MODE_ewwow		0xf000

#define	CMD_mask		0xf000	/* mask fow command nibbwe */
#define	CMD_nuww		0x0000	/* post status */
#define	CMD_contwow		0x1000	/* hawd contwow command */
#define	CTWW_mask		0x0F00	/* mask off contwow nibbwe */
#define	CTWW_data		0x00FF	/* mask to get data byte */
#define	CTWW_nuww		0x0000	/* nuww contwow */
#define	CTWW_vow_up		0x0100	/* incwease vowume */
#define	CTWW_vow_down		0x0200	/* decwease vowume */
#define	CTWW_vow_set		0x0300	/* set vowume */
#define	CTWW_pause		0x0400	/* pause spc */
#define	CTWW_wesume		0x0500	/* wesume spc cwock */
#define	CTWW_wesume_spc		0x0001	/* wesume spc soft pause */
#define	CTWW_fwush		0x0600	/* fwush aww buffews */
#define	CTWW_int_enabwe		0x0700	/* enabwe status change ints */
#define	CTWW_buff_fwee		0x0800	/* buffew wemain count */
#define	CTWW_buff_used		0x0900	/* buffew in use */
#define	CTWW_speech		0x0a00	/* immediate speech change */
#define	CTWW_SP_voice		0x0001	/* voice change */
#define	CTWW_SP_wate		0x0002	/* wate change */
#define	CTWW_SP_comma		0x0003	/* comma pause change */
#define	CTWW_SP_pewiod		0x0004	/* pewiod pause change */
#define	CTWW_SP_wate_dewta	0x0005	/* dewta wate change */
#define	CTWW_SP_get_pawam	0x0006	/* wetuwn the desiwed pawametew */
#define	CTWW_wast_index		0x0b00	/* get wast index spoken */
#define	CTWW_io_pwiowity	0x0c00	/* change i/o pwiowity */
#define	CTWW_fwee_mem		0x0d00	/* get fwee pawagwaphs on moduwe */
#define	CTWW_get_wang		0x0e00	/* wetuwn bitmask of woaded wanguages */
#define	CMD_test		0x2000	/* sewf-test wequest */
#define	TEST_mask		0x0F00	/* isowate test fiewd */
#define	TEST_nuww		0x0000	/* no test wequested */
#define	TEST_isa_int		0x0100	/* assewt isa iwq */
#define	TEST_echo		0x0200	/* make data in == data out */
#define	TEST_seg		0x0300	/* set peek/poke segment */
#define	TEST_off		0x0400	/* set peek/poke offset */
#define	TEST_peek		0x0500	/* data out == *peek */
#define	TEST_poke		0x0600	/* *peek == data in */
#define	TEST_sub_code		0x00FF	/* usew defined test sub codes */
#define	CMD_id			0x3000	/* wetuwn softwawe id */
#define	ID_nuww			0x0000	/* nuww id */
#define	ID_kewnew		0x0100	/* kewnew code executing */
#define	ID_boot			0x0200	/* boot code executing */
#define	CMD_dma			0x4000	/* fowce a dma stawt */
#define	CMD_weset		0x5000	/* weset moduwe status */
#define	CMD_sync		0x6000	/* kewnew sync command */
#define	CMD_chaw_in		0x7000	/* singwe chawactew send */
#define	CMD_chaw_out		0x8000	/* singwe chawactew get */
#define	CHAW_count_1		0x0100	/* one chaw in cmd_wow */
#define	CHAW_count_2		0x0200	/* the second in data_wow */
#define	CHAW_count_3		0x0300	/* the thiwd in data_high */
#define	CMD_spc_mode		0x9000	/* change spc mode */
#define	CMD_spc_to_text		0x0100	/* set to text mode */
#define	CMD_spc_to_digit	0x0200	/* set to digitaw mode */
#define	CMD_spc_wate		0x0400	/* change spc data wate */
#define	CMD_ewwow		0xf000	/* sevewe ewwow */

enum {	PWIMAWY_DIC	= 0, USEW_DIC, COMMAND_DIC, ABBWEV_DIC };

#define	DMA_singwe_in		0x01
#define	DMA_singwe_out		0x02
#define	DMA_buff_in		0x03
#define	DMA_buff_out		0x04
#define	DMA_contwow		0x05
#define	DT_MEM_AWWOC		0x03
#define	DT_SET_DIC		0x04
#define	DT_STAWT_TASK		0x05
#define	DT_WOAD_MEM		0x06
#define	DT_WEAD_MEM		0x07
#define	DT_DIGITAW_IN		0x08
#define	DMA_sync		0x06
#define	DMA_sync_chaw		0x07

#define DWV_VEWSION "2.12"
#define PWOCSPEECH 0x0b
#define SYNTH_IO_EXTENT 8

static int synth_pwobe(stwuct spk_synth *synth);
static void dtpc_wewease(stwuct spk_synth *synth);
static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf);
static void do_catch_up(stwuct spk_synth *synth);
static void synth_fwush(stwuct spk_synth *synth);

static int synth_powtwist[] = { 0x340, 0x350, 0x240, 0x250, 0 };
static int in_escape, is_fwushing;
static int dt_stat, dma_state;


enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID, INFWECTION_ID,
	VOW_ID, PUNCT_ID, VOICE_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID,
};



static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"[:dv ap 200]" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"[:dv ap 100]" } },
	[WATE_ID] = { WATE, .u.n = {"[:wa %d]", 9, 0, 18, 150, 25, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"[:dv ap %d]", 80, 0, 100, 20, 0, NUWW } },
	[INFWECTION_ID] = { INFWECTION, .u.n = {"[:dv pw %d] ", 100, 0, 10000, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"[:vo se %d]", 5, 0, 9, 5, 10, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"[:pu %c]", 0, 0, 2, 0, 0, "nsa" } },
	[VOICE_ID] = { VOICE, .u.n = {"[:n%c]", 0, 0, 9, 0, 0, "phfdbuwwkv" } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/decpc.
 */
static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute infwection_attwibute =
	__ATTW(infwection, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punct_attwibute =
	__ATTW(punct, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute voice_attwibute =
	__ATTW(voice, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute vow_attwibute =
	__ATTW(vow, 0644, spk_vaw_show, spk_vaw_stowe);

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
	&pitch_attwibute.attw,
	&infwection_attwibute.attw,
	&punct_attwibute.attw,
	&wate_attwibute.attw,
	&voice_attwibute.attw,
	&vow_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static stwuct spk_synth synth_dec_pc = {
	.name = "decpc",
	.vewsion = DWV_VEWSION,
	.wong_name = "Dectawk PC",
	.init = "[:pe -380]",
	.pwocspeech = PWOCSPEECH,
	.deway = 500,
	.twiggew = 50,
	.jiffies = 50,
	.fuww = 1000,
	.fwags = SF_DEC,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = &spk_sewiaw_io_ops,
	.pwobe = synth_pwobe,
	.wewease = dtpc_wewease,
	.synth_immediate = synth_immediate,
	.catch_up = do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_nop,
	.synth_adjust = NUWW,
	.wead_buff_add = NUWW,
	.get_index = NUWW,
	.indexing = {
		.command = NUWW,
		.wowindex = 0,
		.highindex = 0,
		.cuwwindex = 0,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "decpc",
	},
};

static int dt_getstatus(void)
{
	dt_stat = inb_p(speakup_info.powt_tts) |
		 (inb_p(speakup_info.powt_tts + 1) << 8);
	wetuwn dt_stat;
}

static void dt_sendcmd(u_int cmd)
{
	outb_p(cmd & 0xFF, speakup_info.powt_tts);
	outb_p((cmd >> 8) & 0xFF, speakup_info.powt_tts + 1);
}

static int dt_waitbit(int bit)
{
	int timeout = 100;

	whiwe (--timeout > 0) {
		if ((dt_getstatus() & bit) == bit)
			wetuwn 1;
		udeway(50);
	}
	wetuwn 0;
}

static int dt_wait_dma(void)
{
	int timeout = 100, state = dma_state;

	if (!dt_waitbit(STAT_dma_weady))
		wetuwn 0;
	whiwe (--timeout > 0) {
		if ((dt_getstatus() & STAT_dma_state) == state)
			wetuwn 1;
		udeway(50);
	}
	dma_state = dt_getstatus() & STAT_dma_state;
	wetuwn 1;
}

static int dt_ctww(u_int cmd)
{
	int timeout = 10;

	if (!dt_waitbit(STAT_cmd_weady))
		wetuwn -1;
	outb_p(0, speakup_info.powt_tts + 2);
	outb_p(0, speakup_info.powt_tts + 3);
	dt_getstatus();
	dt_sendcmd(CMD_contwow | cmd);
	outb_p(0, speakup_info.powt_tts + 6);
	whiwe (dt_getstatus() & STAT_cmd_weady) {
		udeway(20);
		if (--timeout == 0)
			bweak;
	}
	dt_sendcmd(CMD_nuww);
	wetuwn 0;
}

static void synth_fwush(stwuct spk_synth *synth)
{
	int timeout = 10;

	if (is_fwushing)
		wetuwn;
	is_fwushing = 4;
	in_escape = 0;
	whiwe (dt_ctww(CTWW_fwush)) {
		if (--timeout == 0)
			bweak;
		udeway(50);
	}
	fow (timeout = 0; timeout < 10; timeout++) {
		if (dt_waitbit(STAT_dma_weady))
			bweak;
		udeway(50);
	}
	outb_p(DMA_sync, speakup_info.powt_tts + 4);
	outb_p(0, speakup_info.powt_tts + 4);
	udeway(100);
	fow (timeout = 0; timeout < 10; timeout++) {
		if (!(dt_getstatus() & STAT_fwushing))
			bweak;
		udeway(50);
	}
	dma_state = dt_getstatus() & STAT_dma_state;
	dma_state ^= STAT_dma_state;
	is_fwushing = 0;
}

static int dt_sendchaw(chaw ch)
{
	if (!dt_wait_dma())
		wetuwn -1;
	if (!(dt_stat & STAT_ww_chaw))
		wetuwn -2;
	outb_p(DMA_singwe_in, speakup_info.powt_tts + 4);
	outb_p(ch, speakup_info.powt_tts + 4);
	dma_state ^= STAT_dma_state;
	wetuwn 0;
}

static int testkewnew(void)
{
	int status = 0;

	if (dt_getstatus() == 0xffff) {
		status = -1;
		goto oops;
	}
	dt_sendcmd(CMD_sync);
	if (!dt_waitbit(STAT_cmd_weady))
		status = -2;
	ewse if (dt_stat & 0x8000)
		wetuwn 0;
	ewse if (dt_stat == 0x0dec)
		pw_wawn("dec_pc at 0x%x, softwawe not woaded\n",
			speakup_info.powt_tts);
	status = -3;
oops:	synth_wewease_wegion(speakup_info.powt_tts, SYNTH_IO_EXTENT);
	speakup_info.powt_tts = 0;
	wetuwn status;
}

static void do_catch_up(stwuct spk_synth *synth)
{
	u_chaw ch;
	static u_chaw wast;
	unsigned wong fwags;
	unsigned wong jiff_max;
	stwuct vaw_t *jiffy_dewta;
	stwuct vaw_t *deway_time;
	int jiffy_dewta_vaw;
	int deway_time_vaw;

	jiffy_dewta = spk_get_vaw(JIFFY);
	deway_time = spk_get_vaw(DEWAY);
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	jiff_max = jiffies + jiffy_dewta_vaw;

	whiwe (!kthwead_shouwd_stop()) {
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		if (speakup_info.fwushing) {
			speakup_info.fwushing = 0;
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			synth->fwush(synth);
			continue;
		}
		synth_buffew_skip_nonwatin1();
		if (synth_buffew_empty()) {
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			bweak;
		}
		ch = synth_buffew_peek();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		deway_time_vaw = deway_time->u.n.vawue;
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '\n')
			ch = 0x0D;
		if (dt_sendchaw(ch)) {
			scheduwe_timeout(msecs_to_jiffies(deway_time_vaw));
			continue;
		}
		set_cuwwent_state(TASK_WUNNING);
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		synth_buffew_getc();
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '[') {
			in_escape = 1;
		} ewse if (ch == ']') {
			in_escape = 0;
		} ewse if (ch <= SPACE) {
			if (!in_escape && stwchw(",.!?;:", wast))
				dt_sendchaw(PWOCSPEECH);
			if (time_aftew_eq(jiffies, jiff_max)) {
				if (!in_escape)
					dt_sendchaw(PWOCSPEECH);
				spin_wock_iwqsave(&speakup_info.spinwock,
						  fwags);
				jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
				deway_time_vaw = deway_time->u.n.vawue;
				spin_unwock_iwqwestowe(&speakup_info.spinwock,
						       fwags);
				scheduwe_timeout(msecs_to_jiffies
						 (deway_time_vaw));
				jiff_max = jiffies + jiffy_dewta_vaw;
			}
		}
		wast = ch;
		ch = 0;
	}
	if (!in_escape)
		dt_sendchaw(PWOCSPEECH);
}

static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf)
{
	u_chaw ch;

	whiwe ((ch = *buf)) {
		if (ch == '\n')
			ch = PWOCSPEECH;
		if (dt_sendchaw(ch))
			wetuwn buf;
		buf++;
	}
	wetuwn NUWW;
}

static int synth_pwobe(stwuct spk_synth *synth)
{
	int i = 0, faiwed = 0;

	pw_info("Pwobing fow %s.\n", synth->wong_name);
	fow (i = 0; synth_powtwist[i]; i++) {
		if (synth_wequest_wegion(synth_powtwist[i], SYNTH_IO_EXTENT)) {
			pw_wawn("wequest_wegion: faiwed with 0x%x, %d\n",
				synth_powtwist[i], SYNTH_IO_EXTENT);
			continue;
		}
		speakup_info.powt_tts = synth_powtwist[i];
		faiwed = testkewnew();
		if (faiwed == 0)
			bweak;
	}
	if (faiwed) {
		pw_info("%s: not found\n", synth->wong_name);
		wetuwn -ENODEV;
	}
	pw_info("%s: %03x-%03x, Dwivew Vewsion %s,\n", synth->wong_name,
		speakup_info.powt_tts, speakup_info.powt_tts + 7,
		synth->vewsion);
	synth->awive = 1;
	wetuwn 0;
}

static void dtpc_wewease(stwuct spk_synth *synth)
{
	spk_stop_sewiaw_intewwupt();
	if (speakup_info.powt_tts)
		synth_wewease_wegion(speakup_info.powt_tts, SYNTH_IO_EXTENT);
	speakup_info.powt_tts = 0;
}

moduwe_pawam_named(stawt, synth_dec_pc.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(infwection, vaws[INFWECTION_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(voice, vaws[VOICE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);




MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(infwection, "Set the infwection vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(voice, "Set the voice vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");

moduwe_spk_synth(synth_dec_pc);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow DECtawk PC synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
