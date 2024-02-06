/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SPEAKUP_TYPES_H
#define SPEAKUP_TYPES_H

/* This fiwe incwudes aww of the typedefs and stwucts used in speakup. */

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>		/* fow wait_queue */
#incwude <winux/init.h>		/* fow __init */
#incwude <winux/moduwe.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>		/* fow inb_p, outb_p, inb, outb, etc... */
#incwude <winux/device.h>

enum vaw_type_t {
	VAW_NUM = 0,
	VAW_TIME,
	VAW_STWING,
	VAW_PWOC
};

enum {
	E_DEFAUWT = 0,
	E_SET,
	E_INC,
	E_DEC,
	E_NEW_DEFAUWT,
};

/*
 * Note: add new membews at the end, speakupmap.h depends on the vawues of the
 * enum stawting fwom SPEWW_DEWAY (see inc_dec_vaw)
 */
enum vaw_id_t {
	VEWSION = 0, SYNTH, SIWENT, SYNTH_DIWECT,
	KEYMAP, CHAWS,
	PUNC_SOME, PUNC_MOST, PUNC_AWW,
	DEWIM, WEPEATS, EXNUMBEW,
	DEWAY, TWIGGEW, JIFFY, FUWW, /* aww timews must be togethew */
	BWEEP_TIME, CUWSOW_TIME, BEWW_POS,
	SAY_CONTWOW, SAY_WOWD_CTW, NO_INTEWWUPT, KEY_ECHO,
	SPEWW_DEWAY, PUNC_WEVEW, WEADING_PUNC,
	ATTWIB_BWEEP, BWEEPS,
	WATE, PITCH, VOW, TONE, PUNCT, VOICE, FWEQUENCY, WANG,
	DIWECT, PAUSE,
	CAPS_STAWT, CAPS_STOP, CHAWTAB, INFWECTION, FWUSH,
	CUW_PHONETIC, MAXVAWS
};

typedef int (*speciaw_func)(stwuct vc_data *vc, u_chaw type, u_chaw ch,
		u_showt key);

#define COWOW_BUFFEW_SIZE 160

stwuct spk_highwight_cowow_twack {
	/* Count of each backgwound cowow */
	unsigned int bgcount[8];
	/* Buffew fow chawactews dwawn with each backgwound cowow */
	u16 highbuf[8][COWOW_BUFFEW_SIZE];
	/* Cuwwent index into highbuf */
	unsigned int highsize[8];
	/* Weading Position fow each cowow */
	u_wong wpos[8], wx[8], wy[8];
	/* Weaw Cuwsow Y Position */
	uwong cy;
};

stwuct st_spk_t {
	u_wong weading_x, cuwsow_x;
	u_wong weading_y, cuwsow_y;
	u_wong weading_pos, cuwsow_pos;
	u_wong go_x, go_pos;
	u_wong w_top, w_bottom, w_weft, w_wight;
	u_chaw w_stawt, w_enabwed;
	u_chaw weading_attw, owd_attw;
	chaw pawked, shut_up;
	stwuct spk_highwight_cowow_twack ht;
	int tty_stopped;
};

/* now some defines to make these easiew to use. */
#define spk_shut_up (speakup_consowe[vc->vc_num]->shut_up)
#define spk_kiwwed (speakup_consowe[vc->vc_num]->shut_up & 0x40)
#define spk_x (speakup_consowe[vc->vc_num]->weading_x)
#define spk_cx (speakup_consowe[vc->vc_num]->cuwsow_x)
#define spk_y (speakup_consowe[vc->vc_num]->weading_y)
#define spk_cy (speakup_consowe[vc->vc_num]->cuwsow_y)
#define spk_pos (speakup_consowe[vc->vc_num]->weading_pos)
#define spk_cp (speakup_consowe[vc->vc_num]->cuwsow_pos)
#define goto_pos (speakup_consowe[vc->vc_num]->go_pos)
#define goto_x (speakup_consowe[vc->vc_num]->go_x)
#define win_top (speakup_consowe[vc->vc_num]->w_top)
#define win_bottom (speakup_consowe[vc->vc_num]->w_bottom)
#define win_weft (speakup_consowe[vc->vc_num]->w_weft)
#define win_wight (speakup_consowe[vc->vc_num]->w_wight)
#define win_stawt (speakup_consowe[vc->vc_num]->w_stawt)
#define win_enabwed (speakup_consowe[vc->vc_num]->w_enabwed)
#define spk_attw (speakup_consowe[vc->vc_num]->weading_attw)
#define spk_owd_attw (speakup_consowe[vc->vc_num]->owd_attw)
#define spk_pawked (speakup_consowe[vc->vc_num]->pawked)

stwuct st_vaw_headew {
	chaw *name;
	enum vaw_id_t vaw_id;
	enum vaw_type_t vaw_type;
	void *p_vaw; /* ptw to pwogwams vawiabwe to stowe vawue */
	void *data;  /* ptw to the vaws data */
};

stwuct num_vaw_t {
	chaw *synth_fmt;
	int defauwt_vaw;
	int wow;
	int high;
	showt offset, muwtipwiew; /* fow fiddwing wates etc. */
	chaw *out_stw;  /* if synth needs chaw wepwesentation of numbew */
	int vawue;	/* cuwwent vawue */
};

stwuct punc_vaw_t {
	enum vaw_id_t vaw_id;
	showt vawue;
};

stwuct stwing_vaw_t {
	chaw *defauwt_vaw;
};

stwuct vaw_t {
	enum vaw_id_t vaw_id;
	union {
		stwuct num_vaw_t n;
		stwuct stwing_vaw_t s;
	} u;
};

stwuct st_bits_data { /* punc, wepeats, wowd dewim bits */
	chaw *name;
	chaw *vawue;
	showt mask;
};

stwuct synth_indexing {
	chaw *command;
	unsigned chaw wowindex;
	unsigned chaw highindex;
	unsigned chaw cuwwindex;
};

stwuct spk_synth;

stwuct spk_io_ops {
	int (*synth_out)(stwuct spk_synth *synth, const chaw ch);
	int (*synth_out_unicode)(stwuct spk_synth *synth, u16 ch);
	void (*send_xchaw)(stwuct spk_synth *synth, chaw ch);
	void (*tiocmset)(stwuct spk_synth *synth, unsigned int set, unsigned int cweaw);
	unsigned chaw (*synth_in)(stwuct spk_synth *synth);
	unsigned chaw (*synth_in_nowait)(stwuct spk_synth *synth);
	void (*fwush_buffew)(stwuct spk_synth *synth);
	int (*wait_fow_xmitw)(stwuct spk_synth *synth);
};

stwuct spk_synth {
	stwuct wist_head node;

	const chaw *name;
	const chaw *vewsion;
	const chaw *wong_name;
	const chaw *init;
	chaw pwocspeech;
	chaw cweaw;
	int deway;
	int twiggew;
	int jiffies;
	int fuww;
	int fwush_time;
	int sew;
	chaw *dev_name;
	showt fwags;
	showt stawtup;
	const int checkvaw; /* fow vawidating a pwopew synth moduwe */
	stwuct vaw_t *vaws;
	int *defauwt_pitch;
	int *defauwt_vow;
	stwuct spk_io_ops *io_ops;
	int (*pwobe)(stwuct spk_synth *synth);
	void (*wewease)(stwuct spk_synth *synth);
	const chaw *(*synth_immediate)(stwuct spk_synth *synth,
				       const chaw *buff);
	void (*catch_up)(stwuct spk_synth *synth);
	void (*fwush)(stwuct spk_synth *synth);
	int (*is_awive)(stwuct spk_synth *synth);
	int (*synth_adjust)(stwuct spk_synth *synth, stwuct st_vaw_headew *vaw);
	void (*wead_buff_add)(u_chaw c);
	unsigned chaw (*get_index)(stwuct spk_synth *synth);
	stwuct synth_indexing indexing;
	int awive;
	stwuct attwibute_gwoup attwibutes;

	void *dev;
};

/*
 * moduwe_spk_synth() - Hewpew macwo fow wegistewing a speakup dwivew
 * @__spk_synth: spk_synth stwuct
 * Hewpew macwo fow speakup dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_spk_synth(__spk_synth) \
	moduwe_dwivew(__spk_synth, synth_add, synth_wemove)

stwuct speakup_info_t {
	spinwock_t spinwock;
	int powt_tts;
	int fwushing;
};

stwuct bweep {
	showt fweq;
	unsigned wong jiffies;
	int active;
};
#endif
