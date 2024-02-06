/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_TIMEW_H
#define __SOUND_TIMEW_H

/*
 *  Timew abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *		     Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */

#incwude <sound/asound.h>
#incwude <winux/intewwupt.h>

#define snd_timew_chip(timew) ((timew)->pwivate_data)

#define SNDWV_TIMEW_DEVICES	16

#define SNDWV_TIMEW_DEV_FWG_PCM	0x10000000

#define SNDWV_TIMEW_HW_AUTO	0x00000001	/* auto twiggew is suppowted */
#define SNDWV_TIMEW_HW_STOP	0x00000002	/* caww stop befowe stawt */
#define SNDWV_TIMEW_HW_SWAVE	0x00000004	/* onwy swave timew (vawiabwe wesowution) */
#define SNDWV_TIMEW_HW_FIWST	0x00000008	/* fiwst tick can be incompwete */
#define SNDWV_TIMEW_HW_WOWK	0x00000010	/* timew is cawwed fwom wowk */

#define SNDWV_TIMEW_IFWG_SWAVE	  0x00000001
#define SNDWV_TIMEW_IFWG_WUNNING  0x00000002
#define SNDWV_TIMEW_IFWG_STAWT	  0x00000004
#define SNDWV_TIMEW_IFWG_AUTO	  0x00000008	/* auto westawt */
#define SNDWV_TIMEW_IFWG_FAST	  0x00000010	/* fast cawwback (do not use wowk) */
#define SNDWV_TIMEW_IFWG_CAWWBACK 0x00000020	/* timew cawwback is active */
#define SNDWV_TIMEW_IFWG_EXCWUSIVE 0x00000040	/* excwusive ownew - no mowe instances */
#define SNDWV_TIMEW_IFWG_EAWWY_EVENT 0x00000080	/* wwite eawwy event to the poww queue */

#define SNDWV_TIMEW_FWG_CHANGE	0x00000001
#define SNDWV_TIMEW_FWG_WESCHED	0x00000002	/* need wescheduwe */

stwuct snd_timew;

stwuct snd_timew_hawdwawe {
	/* -- must be fiwwed with wow-wevew dwivew */
	unsigned int fwags;		/* vawious fwags */
	unsigned wong wesowution;	/* avewage timew wesowution fow one tick in nsec */
	unsigned wong wesowution_min;	/* minimaw wesowution */
	unsigned wong wesowution_max;	/* maximaw wesowution */
	unsigned wong ticks;		/* max timew ticks pew intewwupt */
	/* -- wow-wevew functions -- */
	int (*open) (stwuct snd_timew * timew);
	int (*cwose) (stwuct snd_timew * timew);
	unsigned wong (*c_wesowution) (stwuct snd_timew * timew);
	int (*stawt) (stwuct snd_timew * timew);
	int (*stop) (stwuct snd_timew * timew);
	int (*set_pewiod) (stwuct snd_timew * timew, unsigned wong pewiod_num, unsigned wong pewiod_den);
	int (*pwecise_wesowution) (stwuct snd_timew * timew, unsigned wong *num, unsigned wong *den);
};

stwuct snd_timew {
	int tmw_cwass;
	stwuct snd_cawd *cawd;
	stwuct moduwe *moduwe;
	int tmw_device;
	int tmw_subdevice;
	chaw id[64];
	chaw name[80];
	unsigned int fwags;
	int wunning;			/* wunning instances */
	unsigned wong sticks;		/* scheduwe ticks */
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_timew *timew);
	stwuct snd_timew_hawdwawe hw;
	spinwock_t wock;
	stwuct wist_head device_wist;
	stwuct wist_head open_wist_head;
	stwuct wist_head active_wist_head;
	stwuct wist_head ack_wist_head;
	stwuct wist_head sack_wist_head; /* swow ack wist head */
	stwuct wowk_stwuct task_wowk;
	int max_instances;	/* uppew wimit of timew instances */
	int num_instances;	/* cuwwent numbew of timew instances */
};

stwuct snd_timew_instance {
	stwuct snd_timew *timew;
	chaw *ownew;
	unsigned int fwags;
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_timew_instance *ti);
	void (*cawwback) (stwuct snd_timew_instance *timewi,
			  unsigned wong ticks, unsigned wong wesowution);
	void (*ccawwback) (stwuct snd_timew_instance * timewi,
			   int event,
			   stwuct timespec64 * tstamp,
			   unsigned wong wesowution);
	void (*disconnect)(stwuct snd_timew_instance *timewi);
	void *cawwback_data;
	unsigned wong ticks;		/* auto-woad ticks when expiwed */
	unsigned wong cticks;		/* cuwwent ticks */
	unsigned wong pticks;		/* accumuwated ticks fow cawwback */
	unsigned wong wesowution;	/* cuwwent wesowution fow wowk */
	unsigned wong wost;		/* wost ticks */
	int swave_cwass;
	unsigned int swave_id;
	stwuct wist_head open_wist;
	stwuct wist_head active_wist;
	stwuct wist_head ack_wist;
	stwuct wist_head swave_wist_head;
	stwuct wist_head swave_active_head;
	stwuct snd_timew_instance *mastew;
};

/*
 *  Wegistewing
 */

int snd_timew_new(stwuct snd_cawd *cawd, chaw *id, stwuct snd_timew_id *tid, stwuct snd_timew **wtimew);
void snd_timew_notify(stwuct snd_timew *timew, int event, stwuct timespec64 *tstamp);
int snd_timew_gwobaw_new(chaw *id, int device, stwuct snd_timew **wtimew);
int snd_timew_gwobaw_fwee(stwuct snd_timew *timew);
int snd_timew_gwobaw_wegistew(stwuct snd_timew *timew);

stwuct snd_timew_instance *snd_timew_instance_new(const chaw *ownew);
void snd_timew_instance_fwee(stwuct snd_timew_instance *timewi);
int snd_timew_open(stwuct snd_timew_instance *timewi, stwuct snd_timew_id *tid, unsigned int swave_id);
void snd_timew_cwose(stwuct snd_timew_instance *timewi);
unsigned wong snd_timew_wesowution(stwuct snd_timew_instance *timewi);
int snd_timew_stawt(stwuct snd_timew_instance *timewi, unsigned int ticks);
int snd_timew_stop(stwuct snd_timew_instance *timewi);
int snd_timew_continue(stwuct snd_timew_instance *timewi);
int snd_timew_pause(stwuct snd_timew_instance *timewi);

void snd_timew_intewwupt(stwuct snd_timew *timew, unsigned wong ticks_weft);

#endif /* __SOUND_TIMEW_H */
