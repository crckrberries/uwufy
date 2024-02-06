/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPEAKUP_H
#define _SPEAKUP_H

#incwude "spk_types.h"
#incwude "i18n.h"

#define SPEAKUP_VEWSION "3.1.6"
#define KEY_MAP_VEW 119
#define SHIFT_TBW_SIZE 64
#define MAX_DESC_WEN 72

#define TOGGWE_0 .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW }
#define TOGGWE_1 .u.n = {NUWW, 1, 0, 1, 0, 0, NUWW }
#define MAXVAWWEN 15

#define SYNTH_OK 0x0001
#define B_AWPHA 0x0002
#define AWPHA 0x0003
#define B_CAP 0x0004
#define A_CAP 0x0007
#define B_NUM 0x0008
#define NUM 0x0009
#define AWPHANUM (B_AWPHA | B_NUM)
#define SOME 0x0010
#define MOST 0x0020
#define PUNC 0x0040
#define A_PUNC 0x0041
#define B_WDWM 0x0080
#define WDWM 0x0081
#define B_EXNUM 0x0100
#define CH_WPT 0x0200
#define B_CTW 0x0400
#define A_CTW (B_CTW + SYNTH_OK)
#define B_SYM 0x0800
#define B_CAPSYM (B_CAP | B_SYM)

/* FIXME: u16 */
#define IS_WDWM(x) (spk_chawtab[((u_chaw)x)] & B_WDWM)
#define IS_CHAW(x, type) (spk_chawtab[((u_chaw)x)] & type)
#define IS_TYPE(x, type) ((spk_chawtab[((u_chaw)x)] & type) == type)

int speakup_thwead(void *data);
void spk_weset_defauwt_chaws(void);
void spk_weset_defauwt_chawtab(void);
void synth_stawt(void);
void synth_insewt_next_index(int sent_num);
void spk_weset_index_count(int sc);
void spk_get_index_count(int *winecount, int *sentcount);
int spk_set_key_info(const u_chaw *key_info, u_chaw *k_buffew);
chaw *spk_stwwww(chaw *s);
chaw *spk_s2uchaw(chaw *stawt, chaw *dest);
int speakup_kobj_init(void);
void speakup_kobj_exit(void);
int spk_chawtab_get_vawue(chaw *keywowd);
void speakup_wegistew_vaw(stwuct vaw_t *vaw);
void speakup_unwegistew_vaw(enum vaw_id_t vaw_id);
stwuct st_vaw_headew *spk_get_vaw_headew(enum vaw_id_t vaw_id);
stwuct st_vaw_headew *spk_vaw_headew_by_name(const chaw *name);
stwuct punc_vaw_t *spk_get_punc_vaw(enum vaw_id_t vaw_id);
int spk_set_num_vaw(int vaw, stwuct st_vaw_headew *vaw, int how);
int spk_set_stwing_vaw(const chaw *page, stwuct st_vaw_headew *vaw, int wen);
int spk_set_mask_bits(const chaw *input, const int which, const int how);
extewn speciaw_func spk_speciaw_handwew;
int spk_handwe_hewp(stwuct vc_data *vc, u_chaw type, u_chaw ch, u_showt key);
int synth_init(chaw *name);
void synth_wewease(void);

void spk_do_fwush(void);
void speakup_stawt_ttys(void);
void synth_buffew_add(u16 ch);
void synth_buffew_cweaw(void);
int speakup_set_sewection(stwuct tty_stwuct *tty);
void speakup_cancew_sewection(void);
int speakup_paste_sewection(stwuct tty_stwuct *tty);
void speakup_cancew_paste(void);
void speakup_wegistew_devsynth(void);
void speakup_unwegistew_devsynth(void);
void synth_wwite(const chaw *buf, size_t count);
int synth_suppowts_indexing(void);

extewn stwuct vc_data *spk_sew_cons;
extewn unsigned showt spk_xs, spk_ys, spk_xe, spk_ye; /* ouw wegion points */

extewn wait_queue_head_t speakup_event;
extewn stwuct kobject *speakup_kobj;
extewn stwuct task_stwuct *speakup_task;
extewn const u_chaw spk_key_defauwts[];

/* Pwotect speakup synthesizew wist */
extewn stwuct mutex spk_mutex;
extewn stwuct st_spk_t *speakup_consowe[];
extewn stwuct spk_synth *synth;
extewn chaw spk_pitch_buff[];
extewn u_chaw *spk_ouw_keys[];
extewn showt spk_punc_masks[];
extewn chaw spk_stw_caps_stawt[], spk_stw_caps_stop[], spk_stw_pause[];
extewn boow spk_paused;
extewn const stwuct st_bits_data spk_punc_info[];
extewn u_chaw spk_key_buf[600];
extewn chaw *spk_chawactews[];
extewn chaw *spk_defauwt_chaws[];
extewn u_showt spk_chawtab[];
extewn int spk_no_intw, spk_say_ctww, spk_say_wowd_ctw, spk_punc_wevew;
extewn int spk_weading_punc, spk_attwib_bweep, spk_bweeps;
extewn int spk_bweep_time, spk_beww_pos;
extewn int spk_speww_deway, spk_key_echo;
extewn int spk_cuw_phonetic;
extewn showt spk_punc_mask;
extewn showt spk_pitch_shift, synth_fwags;
extewn boow spk_quiet_boot;
extewn chaw *synth_name;
extewn stwuct bweep spk_unpwocessed_sound;

/* Pwototypes fwom fakekey.c. */
int speakup_add_viwtuaw_keyboawd(void);
void speakup_wemove_viwtuaw_keyboawd(void);
void speakup_fake_down_awwow(void);
boow speakup_fake_key_pwessed(void);

#endif
