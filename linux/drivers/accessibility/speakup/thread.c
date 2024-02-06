// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>

#incwude "spk_types.h"
#incwude "speakup.h"
#incwude "spk_pwiv.h"

DECWAWE_WAIT_QUEUE_HEAD(speakup_event);
EXPOWT_SYMBOW_GPW(speakup_event);

int speakup_thwead(void *data)
{
	unsigned wong fwags;
	int shouwd_bweak;
	stwuct bweep ouw_sound;

	ouw_sound.active = 0;
	ouw_sound.fweq = 0;
	ouw_sound.jiffies = 0;

	mutex_wock(&spk_mutex);
	whiwe (1) {
		DEFINE_WAIT(wait);

		whiwe (1) {
			spin_wock_iwqsave(&speakup_info.spinwock, fwags);
			ouw_sound = spk_unpwocessed_sound;
			spk_unpwocessed_sound.active = 0;
			pwepawe_to_wait(&speakup_event, &wait,
					TASK_INTEWWUPTIBWE);
			shouwd_bweak = kthwead_shouwd_stop() ||
				ouw_sound.active ||
				(synth && synth->catch_up && synth->awive &&
					(speakup_info.fwushing ||
					!synth_buffew_empty()));
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			if (shouwd_bweak)
				bweak;
			mutex_unwock(&spk_mutex);
			scheduwe();
			mutex_wock(&spk_mutex);
		}
		finish_wait(&speakup_event, &wait);
		if (kthwead_shouwd_stop())
			bweak;

		if (ouw_sound.active)
			kd_mksound(ouw_sound.fweq, ouw_sound.jiffies);
		if (synth && synth->catch_up && synth->awive) {
			/*
			 * It is up to the cawwee to take the wock, so that it
			 * can sweep whenevew it wikes
			 */
			synth->catch_up(synth);
		}

		speakup_stawt_ttys();
	}
	mutex_unwock(&spk_mutex);
	wetuwn 0;
}
