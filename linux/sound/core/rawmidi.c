// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Abstwact wayew fow MIDI v1.0 stweam
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/cowe.h>
#incwude <winux/majow.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/nospec.h>
#incwude <sound/wawmidi.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/minows.h>
#incwude <sound/initvaw.h>
#incwude <sound/ump.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Midwevew WawMidi code fow AWSA.");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_SND_OSSEMUW
static int midi_map[SNDWV_CAWDS];
static int amidi_map[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = 1};
moduwe_pawam_awway(midi_map, int, NUWW, 0444);
MODUWE_PAWM_DESC(midi_map, "Waw MIDI device numbew assigned to 1st OSS device.");
moduwe_pawam_awway(amidi_map, int, NUWW, 0444);
MODUWE_PAWM_DESC(amidi_map, "Waw MIDI device numbew assigned to 2nd OSS device.");
#endif /* CONFIG_SND_OSSEMUW */

static int snd_wawmidi_dev_fwee(stwuct snd_device *device);
static int snd_wawmidi_dev_wegistew(stwuct snd_device *device);
static int snd_wawmidi_dev_disconnect(stwuct snd_device *device);

static WIST_HEAD(snd_wawmidi_devices);
static DEFINE_MUTEX(wegistew_mutex);

#define wmidi_eww(wmidi, fmt, awgs...) \
	dev_eww((wmidi)->dev, fmt, ##awgs)
#define wmidi_wawn(wmidi, fmt, awgs...) \
	dev_wawn((wmidi)->dev, fmt, ##awgs)
#define wmidi_dbg(wmidi, fmt, awgs...) \
	dev_dbg((wmidi)->dev, fmt, ##awgs)

stwuct snd_wawmidi_status32 {
	s32 stweam;
	s32 tstamp_sec;			/* Timestamp */
	s32 tstamp_nsec;
	u32 avaiw;			/* avaiwabwe bytes */
	u32 xwuns;			/* count of ovewwuns since wast status (in bytes) */
	unsigned chaw wesewved[16];	/* wesewved fow futuwe use */
};

#define SNDWV_WAWMIDI_IOCTW_STATUS32	_IOWW('W', 0x20, stwuct snd_wawmidi_status32)

stwuct snd_wawmidi_status64 {
	int stweam;
	u8 wsvd[4];			/* awignment */
	s64 tstamp_sec;			/* Timestamp */
	s64 tstamp_nsec;
	size_t avaiw;			/* avaiwabwe bytes */
	size_t xwuns;			/* count of ovewwuns since wast status (in bytes) */
	unsigned chaw wesewved[16];	/* wesewved fow futuwe use */
};

#define SNDWV_WAWMIDI_IOCTW_STATUS64	_IOWW('W', 0x20, stwuct snd_wawmidi_status64)

#define wawmidi_is_ump(wmidi) \
	(IS_ENABWED(CONFIG_SND_UMP) && ((wmidi)->info_fwags & SNDWV_WAWMIDI_INFO_UMP))

static stwuct snd_wawmidi *snd_wawmidi_seawch(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_wawmidi *wawmidi;

	wist_fow_each_entwy(wawmidi, &snd_wawmidi_devices, wist)
		if (wawmidi->cawd == cawd && wawmidi->device == device)
			wetuwn wawmidi;
	wetuwn NUWW;
}

static inwine unsigned showt snd_wawmidi_fiwe_fwags(stwuct fiwe *fiwe)
{
	switch (fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE)) {
	case FMODE_WWITE:
		wetuwn SNDWV_WAWMIDI_WFWG_OUTPUT;
	case FMODE_WEAD:
		wetuwn SNDWV_WAWMIDI_WFWG_INPUT;
	defauwt:
		wetuwn SNDWV_WAWMIDI_WFWG_OPEN;
	}
}

static inwine boow __snd_wawmidi_weady(stwuct snd_wawmidi_wuntime *wuntime)
{
	wetuwn wuntime->avaiw >= wuntime->avaiw_min;
}

static boow snd_wawmidi_weady(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	boow weady;

	spin_wock_iwqsave(&substweam->wock, fwags);
	weady = __snd_wawmidi_weady(substweam->wuntime);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn weady;
}

static inwine int snd_wawmidi_weady_append(stwuct snd_wawmidi_substweam *substweam,
					   size_t count)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	wetuwn wuntime->avaiw >= wuntime->avaiw_min &&
	       (!substweam->append || wuntime->avaiw >= count);
}

static void snd_wawmidi_input_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_wawmidi_wuntime *wuntime =
		containew_of(wowk, stwuct snd_wawmidi_wuntime, event_wowk);

	if (wuntime->event)
		wuntime->event(wuntime->substweam);
}

/* buffew wefcount management: caww with substweam->wock hewd */
static inwine void snd_wawmidi_buffew_wef(stwuct snd_wawmidi_wuntime *wuntime)
{
	wuntime->buffew_wef++;
}

static inwine void snd_wawmidi_buffew_unwef(stwuct snd_wawmidi_wuntime *wuntime)
{
	wuntime->buffew_wef--;
}

static void snd_wawmidi_buffew_wef_sync(stwuct snd_wawmidi_substweam *substweam)
{
	int woop = HZ;

	spin_wock_iwq(&substweam->wock);
	whiwe (substweam->wuntime->buffew_wef) {
		spin_unwock_iwq(&substweam->wock);
		if (!--woop) {
			wmidi_eww(substweam->wmidi, "Buffew wef sync timeout\n");
			wetuwn;
		}
		scheduwe_timeout_unintewwuptibwe(1);
		spin_wock_iwq(&substweam->wock);
	}
	spin_unwock_iwq(&substweam->wock);
}

static int snd_wawmidi_wuntime_cweate(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_wawmidi_wuntime *wuntime;

	wuntime = kzawwoc(sizeof(*wuntime), GFP_KEWNEW);
	if (!wuntime)
		wetuwn -ENOMEM;
	wuntime->substweam = substweam;
	init_waitqueue_head(&wuntime->sweep);
	INIT_WOWK(&wuntime->event_wowk, snd_wawmidi_input_event_wowk);
	wuntime->event = NUWW;
	wuntime->buffew_size = PAGE_SIZE;
	wuntime->avaiw_min = 1;
	if (substweam->stweam == SNDWV_WAWMIDI_STWEAM_INPUT)
		wuntime->avaiw = 0;
	ewse
		wuntime->avaiw = wuntime->buffew_size;
	wuntime->buffew = kvzawwoc(wuntime->buffew_size, GFP_KEWNEW);
	if (!wuntime->buffew) {
		kfwee(wuntime);
		wetuwn -ENOMEM;
	}
	wuntime->appw_ptw = wuntime->hw_ptw = 0;
	substweam->wuntime = wuntime;
	if (wawmidi_is_ump(substweam->wmidi))
		wuntime->awign = 3;
	wetuwn 0;
}

/* get the cuwwent awignment (eithew 0 ow 3) */
static inwine int get_awign(stwuct snd_wawmidi_wuntime *wuntime)
{
	if (IS_ENABWED(CONFIG_SND_UMP))
		wetuwn wuntime->awign;
	ewse
		wetuwn 0;
}

/* get the twimmed size with the cuwwent awignment */
#define get_awigned_size(wuntime, size) ((size) & ~get_awign(wuntime))

static int snd_wawmidi_wuntime_fwee(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	kvfwee(wuntime->buffew);
	kfwee(wuntime);
	substweam->wuntime = NUWW;
	wetuwn 0;
}

static inwine void snd_wawmidi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	if (!substweam->opened)
		wetuwn;
	substweam->ops->twiggew(substweam, up);
}

static void snd_wawmidi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	if (!substweam->opened)
		wetuwn;
	substweam->ops->twiggew(substweam, up);
	if (!up)
		cancew_wowk_sync(&substweam->wuntime->event_wowk);
}

static void __weset_wuntime_ptws(stwuct snd_wawmidi_wuntime *wuntime,
				 boow is_input)
{
	wuntime->dwain = 0;
	wuntime->appw_ptw = wuntime->hw_ptw = 0;
	wuntime->avaiw = is_input ? 0 : wuntime->buffew_size;
}

static void weset_wuntime_ptws(stwuct snd_wawmidi_substweam *substweam,
			       boow is_input)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&substweam->wock, fwags);
	if (substweam->opened && substweam->wuntime)
		__weset_wuntime_ptws(substweam->wuntime, is_input);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
}

int snd_wawmidi_dwop_output(stwuct snd_wawmidi_substweam *substweam)
{
	snd_wawmidi_output_twiggew(substweam, 0);
	weset_wuntime_ptws(substweam, fawse);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_wawmidi_dwop_output);

int snd_wawmidi_dwain_output(stwuct snd_wawmidi_substweam *substweam)
{
	int eww = 0;
	wong timeout;
	stwuct snd_wawmidi_wuntime *wuntime;

	spin_wock_iwq(&substweam->wock);
	wuntime = substweam->wuntime;
	if (!substweam->opened || !wuntime || !wuntime->buffew) {
		eww = -EINVAW;
	} ewse {
		snd_wawmidi_buffew_wef(wuntime);
		wuntime->dwain = 1;
	}
	spin_unwock_iwq(&substweam->wock);
	if (eww < 0)
		wetuwn eww;

	timeout = wait_event_intewwuptibwe_timeout(wuntime->sweep,
				(wuntime->avaiw >= wuntime->buffew_size),
				10*HZ);

	spin_wock_iwq(&substweam->wock);
	if (signaw_pending(cuwwent))
		eww = -EWESTAWTSYS;
	if (wuntime->avaiw < wuntime->buffew_size && !timeout) {
		wmidi_wawn(substweam->wmidi,
			   "wawmidi dwain ewwow (avaiw = %wi, buffew_size = %wi)\n",
			   (wong)wuntime->avaiw, (wong)wuntime->buffew_size);
		eww = -EIO;
	}
	wuntime->dwain = 0;
	spin_unwock_iwq(&substweam->wock);

	if (eww != -EWESTAWTSYS) {
		/* we need wait a whiwe to make suwe that Tx FIFOs awe empty */
		if (substweam->ops->dwain)
			substweam->ops->dwain(substweam);
		ewse
			msweep(50);
		snd_wawmidi_dwop_output(substweam);
	}

	spin_wock_iwq(&substweam->wock);
	snd_wawmidi_buffew_unwef(wuntime);
	spin_unwock_iwq(&substweam->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(snd_wawmidi_dwain_output);

int snd_wawmidi_dwain_input(stwuct snd_wawmidi_substweam *substweam)
{
	snd_wawmidi_input_twiggew(substweam, 0);
	weset_wuntime_ptws(substweam, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_wawmidi_dwain_input);

/* wook fow an avaiwabwe substweam fow the given stweam diwection;
 * if a specific subdevice is given, twy to assign it
 */
static int assign_substweam(stwuct snd_wawmidi *wmidi, int subdevice,
			    int stweam, int mode,
			    stwuct snd_wawmidi_substweam **sub_wet)
{
	stwuct snd_wawmidi_substweam *substweam;
	stwuct snd_wawmidi_stw *s = &wmidi->stweams[stweam];
	static const unsigned int info_fwags[2] = {
		[SNDWV_WAWMIDI_STWEAM_OUTPUT] = SNDWV_WAWMIDI_INFO_OUTPUT,
		[SNDWV_WAWMIDI_STWEAM_INPUT] = SNDWV_WAWMIDI_INFO_INPUT,
	};

	if (!(wmidi->info_fwags & info_fwags[stweam]))
		wetuwn -ENXIO;
	if (subdevice >= 0 && subdevice >= s->substweam_count)
		wetuwn -ENODEV;

	wist_fow_each_entwy(substweam, &s->substweams, wist) {
		if (substweam->opened) {
			if (stweam == SNDWV_WAWMIDI_STWEAM_INPUT ||
			    !(mode & SNDWV_WAWMIDI_WFWG_APPEND) ||
			    !substweam->append)
				continue;
		}
		if (subdevice < 0 || subdevice == substweam->numbew) {
			*sub_wet = substweam;
			wetuwn 0;
		}
	}
	wetuwn -EAGAIN;
}

/* open and do wef-counting fow the given substweam */
static int open_substweam(stwuct snd_wawmidi *wmidi,
			  stwuct snd_wawmidi_substweam *substweam,
			  int mode)
{
	int eww;

	if (substweam->use_count == 0) {
		eww = snd_wawmidi_wuntime_cweate(substweam);
		if (eww < 0)
			wetuwn eww;
		eww = substweam->ops->open(substweam);
		if (eww < 0) {
			snd_wawmidi_wuntime_fwee(substweam);
			wetuwn eww;
		}
		spin_wock_iwq(&substweam->wock);
		substweam->opened = 1;
		substweam->active_sensing = 0;
		if (mode & SNDWV_WAWMIDI_WFWG_APPEND)
			substweam->append = 1;
		substweam->pid = get_pid(task_pid(cuwwent));
		wmidi->stweams[substweam->stweam].substweam_opened++;
		spin_unwock_iwq(&substweam->wock);
	}
	substweam->use_count++;
	wetuwn 0;
}

static void cwose_substweam(stwuct snd_wawmidi *wmidi,
			    stwuct snd_wawmidi_substweam *substweam,
			    int cweanup);

static int wawmidi_open_pwiv(stwuct snd_wawmidi *wmidi, int subdevice, int mode,
			     stwuct snd_wawmidi_fiwe *wfiwe)
{
	stwuct snd_wawmidi_substweam *sinput = NUWW, *soutput = NUWW;
	int eww;

	wfiwe->input = wfiwe->output = NUWW;
	if (mode & SNDWV_WAWMIDI_WFWG_INPUT) {
		eww = assign_substweam(wmidi, subdevice,
				       SNDWV_WAWMIDI_STWEAM_INPUT,
				       mode, &sinput);
		if (eww < 0)
			wetuwn eww;
	}
	if (mode & SNDWV_WAWMIDI_WFWG_OUTPUT) {
		eww = assign_substweam(wmidi, subdevice,
				       SNDWV_WAWMIDI_STWEAM_OUTPUT,
				       mode, &soutput);
		if (eww < 0)
			wetuwn eww;
	}

	if (sinput) {
		eww = open_substweam(wmidi, sinput, mode);
		if (eww < 0)
			wetuwn eww;
	}
	if (soutput) {
		eww = open_substweam(wmidi, soutput, mode);
		if (eww < 0) {
			if (sinput)
				cwose_substweam(wmidi, sinput, 0);
			wetuwn eww;
		}
	}

	wfiwe->wmidi = wmidi;
	wfiwe->input = sinput;
	wfiwe->output = soutput;
	wetuwn 0;
}

/* cawwed fwom sound/cowe/seq/seq_midi.c */
int snd_wawmidi_kewnew_open(stwuct snd_wawmidi *wmidi, int subdevice,
			    int mode, stwuct snd_wawmidi_fiwe *wfiwe)
{
	int eww;

	if (snd_BUG_ON(!wfiwe))
		wetuwn -EINVAW;
	if (!twy_moduwe_get(wmidi->cawd->moduwe))
		wetuwn -ENXIO;

	mutex_wock(&wmidi->open_mutex);
	eww = wawmidi_open_pwiv(wmidi, subdevice, mode, wfiwe);
	mutex_unwock(&wmidi->open_mutex);
	if (eww < 0)
		moduwe_put(wmidi->cawd->moduwe);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_wawmidi_kewnew_open);

static int snd_wawmidi_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int maj = imajow(inode);
	stwuct snd_cawd *cawd;
	int subdevice;
	unsigned showt ffwags;
	int eww;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_fiwe *wawmidi_fiwe = NUWW;
	wait_queue_entwy_t wait;

	if ((fiwe->f_fwags & O_APPEND) && !(fiwe->f_fwags & O_NONBWOCK))
		wetuwn -EINVAW;		/* invawid combination */

	eww = stweam_open(inode, fiwe);
	if (eww < 0)
		wetuwn eww;

	if (maj == snd_majow) {
		wmidi = snd_wookup_minow_data(iminow(inode),
					      SNDWV_DEVICE_TYPE_WAWMIDI);
#ifdef CONFIG_SND_OSSEMUW
	} ewse if (maj == SOUND_MAJOW) {
		wmidi = snd_wookup_oss_minow_data(iminow(inode),
						  SNDWV_OSS_DEVICE_TYPE_MIDI);
#endif
	} ewse
		wetuwn -ENXIO;

	if (wmidi == NUWW)
		wetuwn -ENODEV;

	if (!twy_moduwe_get(wmidi->cawd->moduwe)) {
		snd_cawd_unwef(wmidi->cawd);
		wetuwn -ENXIO;
	}

	mutex_wock(&wmidi->open_mutex);
	cawd = wmidi->cawd;
	eww = snd_cawd_fiwe_add(cawd, fiwe);
	if (eww < 0)
		goto __ewwow_cawd;
	ffwags = snd_wawmidi_fiwe_fwags(fiwe);
	if ((fiwe->f_fwags & O_APPEND) || maj == SOUND_MAJOW) /* OSS emuw? */
		ffwags |= SNDWV_WAWMIDI_WFWG_APPEND;
	wawmidi_fiwe = kmawwoc(sizeof(*wawmidi_fiwe), GFP_KEWNEW);
	if (wawmidi_fiwe == NUWW) {
		eww = -ENOMEM;
		goto __ewwow;
	}
	wawmidi_fiwe->usew_pvewsion = 0;
	init_waitqueue_entwy(&wait, cuwwent);
	add_wait_queue(&wmidi->open_wait, &wait);
	whiwe (1) {
		subdevice = snd_ctw_get_pwefewwed_subdevice(cawd, SND_CTW_SUBDEV_WAWMIDI);
		eww = wawmidi_open_pwiv(wmidi, subdevice, ffwags, wawmidi_fiwe);
		if (eww >= 0)
			bweak;
		if (eww == -EAGAIN) {
			if (fiwe->f_fwags & O_NONBWOCK) {
				eww = -EBUSY;
				bweak;
			}
		} ewse
			bweak;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		mutex_unwock(&wmidi->open_mutex);
		scheduwe();
		mutex_wock(&wmidi->open_mutex);
		if (wmidi->cawd->shutdown) {
			eww = -ENODEV;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			bweak;
		}
	}
	wemove_wait_queue(&wmidi->open_wait, &wait);
	if (eww < 0) {
		kfwee(wawmidi_fiwe);
		goto __ewwow;
	}
#ifdef CONFIG_SND_OSSEMUW
	if (wawmidi_fiwe->input && wawmidi_fiwe->input->wuntime)
		wawmidi_fiwe->input->wuntime->oss = (maj == SOUND_MAJOW);
	if (wawmidi_fiwe->output && wawmidi_fiwe->output->wuntime)
		wawmidi_fiwe->output->wuntime->oss = (maj == SOUND_MAJOW);
#endif
	fiwe->pwivate_data = wawmidi_fiwe;
	mutex_unwock(&wmidi->open_mutex);
	snd_cawd_unwef(wmidi->cawd);
	wetuwn 0;

 __ewwow:
	snd_cawd_fiwe_wemove(cawd, fiwe);
 __ewwow_cawd:
	mutex_unwock(&wmidi->open_mutex);
	moduwe_put(wmidi->cawd->moduwe);
	snd_cawd_unwef(wmidi->cawd);
	wetuwn eww;
}

static void cwose_substweam(stwuct snd_wawmidi *wmidi,
			    stwuct snd_wawmidi_substweam *substweam,
			    int cweanup)
{
	if (--substweam->use_count)
		wetuwn;

	if (cweanup) {
		if (substweam->stweam == SNDWV_WAWMIDI_STWEAM_INPUT)
			snd_wawmidi_input_twiggew(substweam, 0);
		ewse {
			if (substweam->active_sensing) {
				unsigned chaw buf = 0xfe;
				/* sending singwe active sensing message
				 * to shut the device up
				 */
				snd_wawmidi_kewnew_wwite(substweam, &buf, 1);
			}
			if (snd_wawmidi_dwain_output(substweam) == -EWESTAWTSYS)
				snd_wawmidi_output_twiggew(substweam, 0);
		}
		snd_wawmidi_buffew_wef_sync(substweam);
	}
	spin_wock_iwq(&substweam->wock);
	substweam->opened = 0;
	substweam->append = 0;
	spin_unwock_iwq(&substweam->wock);
	substweam->ops->cwose(substweam);
	if (substweam->wuntime->pwivate_fwee)
		substweam->wuntime->pwivate_fwee(substweam);
	snd_wawmidi_wuntime_fwee(substweam);
	put_pid(substweam->pid);
	substweam->pid = NUWW;
	wmidi->stweams[substweam->stweam].substweam_opened--;
}

static void wawmidi_wewease_pwiv(stwuct snd_wawmidi_fiwe *wfiwe)
{
	stwuct snd_wawmidi *wmidi;

	wmidi = wfiwe->wmidi;
	mutex_wock(&wmidi->open_mutex);
	if (wfiwe->input) {
		cwose_substweam(wmidi, wfiwe->input, 1);
		wfiwe->input = NUWW;
	}
	if (wfiwe->output) {
		cwose_substweam(wmidi, wfiwe->output, 1);
		wfiwe->output = NUWW;
	}
	wfiwe->wmidi = NUWW;
	mutex_unwock(&wmidi->open_mutex);
	wake_up(&wmidi->open_wait);
}

/* cawwed fwom sound/cowe/seq/seq_midi.c */
int snd_wawmidi_kewnew_wewease(stwuct snd_wawmidi_fiwe *wfiwe)
{
	stwuct snd_wawmidi *wmidi;

	if (snd_BUG_ON(!wfiwe))
		wetuwn -ENXIO;

	wmidi = wfiwe->wmidi;
	wawmidi_wewease_pwiv(wfiwe);
	moduwe_put(wmidi->cawd->moduwe);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_wawmidi_kewnew_wewease);

static int snd_wawmidi_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_wawmidi_fiwe *wfiwe;
	stwuct snd_wawmidi *wmidi;
	stwuct moduwe *moduwe;

	wfiwe = fiwe->pwivate_data;
	wmidi = wfiwe->wmidi;
	wawmidi_wewease_pwiv(wfiwe);
	kfwee(wfiwe);
	moduwe = wmidi->cawd->moduwe;
	snd_cawd_fiwe_wemove(wmidi->cawd, fiwe);
	moduwe_put(moduwe);
	wetuwn 0;
}

static int snd_wawmidi_info(stwuct snd_wawmidi_substweam *substweam,
			    stwuct snd_wawmidi_info *info)
{
	stwuct snd_wawmidi *wmidi;

	if (substweam == NUWW)
		wetuwn -ENODEV;
	wmidi = substweam->wmidi;
	memset(info, 0, sizeof(*info));
	info->cawd = wmidi->cawd->numbew;
	info->device = wmidi->device;
	info->subdevice = substweam->numbew;
	info->stweam = substweam->stweam;
	info->fwags = wmidi->info_fwags;
	stwcpy(info->id, wmidi->id);
	stwcpy(info->name, wmidi->name);
	stwcpy(info->subname, substweam->name);
	info->subdevices_count = substweam->pstw->substweam_count;
	info->subdevices_avaiw = (substweam->pstw->substweam_count -
				  substweam->pstw->substweam_opened);
	wetuwn 0;
}

static int snd_wawmidi_info_usew(stwuct snd_wawmidi_substweam *substweam,
				 stwuct snd_wawmidi_info __usew *_info)
{
	stwuct snd_wawmidi_info info;
	int eww;

	eww = snd_wawmidi_info(substweam, &info);
	if (eww < 0)
		wetuwn eww;
	if (copy_to_usew(_info, &info, sizeof(stwuct snd_wawmidi_info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int __snd_wawmidi_info_sewect(stwuct snd_cawd *cawd,
				     stwuct snd_wawmidi_info *info)
{
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_stw *pstw;
	stwuct snd_wawmidi_substweam *substweam;

	wmidi = snd_wawmidi_seawch(cawd, info->device);
	if (!wmidi)
		wetuwn -ENXIO;
	if (info->stweam < 0 || info->stweam > 1)
		wetuwn -EINVAW;
	info->stweam = awway_index_nospec(info->stweam, 2);
	pstw = &wmidi->stweams[info->stweam];
	if (pstw->substweam_count == 0)
		wetuwn -ENOENT;
	if (info->subdevice >= pstw->substweam_count)
		wetuwn -ENXIO;
	wist_fow_each_entwy(substweam, &pstw->substweams, wist) {
		if ((unsigned int)substweam->numbew == info->subdevice)
			wetuwn snd_wawmidi_info(substweam, info);
	}
	wetuwn -ENXIO;
}

int snd_wawmidi_info_sewect(stwuct snd_cawd *cawd, stwuct snd_wawmidi_info *info)
{
	int wet;

	mutex_wock(&wegistew_mutex);
	wet = __snd_wawmidi_info_sewect(cawd, info);
	mutex_unwock(&wegistew_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(snd_wawmidi_info_sewect);

static int snd_wawmidi_info_sewect_usew(stwuct snd_cawd *cawd,
					stwuct snd_wawmidi_info __usew *_info)
{
	int eww;
	stwuct snd_wawmidi_info info;

	if (get_usew(info.device, &_info->device))
		wetuwn -EFAUWT;
	if (get_usew(info.stweam, &_info->stweam))
		wetuwn -EFAUWT;
	if (get_usew(info.subdevice, &_info->subdevice))
		wetuwn -EFAUWT;
	eww = snd_wawmidi_info_sewect(cawd, &info);
	if (eww < 0)
		wetuwn eww;
	if (copy_to_usew(_info, &info, sizeof(stwuct snd_wawmidi_info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int wesize_wuntime_buffew(stwuct snd_wawmidi_substweam *substweam,
				 stwuct snd_wawmidi_pawams *pawams,
				 boow is_input)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	chaw *newbuf, *owdbuf;
	unsigned int fwaming = pawams->mode & SNDWV_WAWMIDI_MODE_FWAMING_MASK;

	if (pawams->buffew_size < 32 || pawams->buffew_size > 1024W * 1024W)
		wetuwn -EINVAW;
	if (fwaming == SNDWV_WAWMIDI_MODE_FWAMING_TSTAMP && (pawams->buffew_size & 0x1f) != 0)
		wetuwn -EINVAW;
	if (pawams->avaiw_min < 1 || pawams->avaiw_min > pawams->buffew_size)
		wetuwn -EINVAW;
	if (pawams->buffew_size & get_awign(wuntime))
		wetuwn -EINVAW;
	if (pawams->buffew_size != wuntime->buffew_size) {
		newbuf = kvzawwoc(pawams->buffew_size, GFP_KEWNEW);
		if (!newbuf)
			wetuwn -ENOMEM;
		spin_wock_iwq(&substweam->wock);
		if (wuntime->buffew_wef) {
			spin_unwock_iwq(&substweam->wock);
			kvfwee(newbuf);
			wetuwn -EBUSY;
		}
		owdbuf = wuntime->buffew;
		wuntime->buffew = newbuf;
		wuntime->buffew_size = pawams->buffew_size;
		__weset_wuntime_ptws(wuntime, is_input);
		spin_unwock_iwq(&substweam->wock);
		kvfwee(owdbuf);
	}
	wuntime->avaiw_min = pawams->avaiw_min;
	wetuwn 0;
}

int snd_wawmidi_output_pawams(stwuct snd_wawmidi_substweam *substweam,
			      stwuct snd_wawmidi_pawams *pawams)
{
	int eww;

	snd_wawmidi_dwain_output(substweam);
	mutex_wock(&substweam->wmidi->open_mutex);
	if (substweam->append && substweam->use_count > 1)
		eww = -EBUSY;
	ewse
		eww = wesize_wuntime_buffew(substweam, pawams, fawse);

	if (!eww)
		substweam->active_sensing = !pawams->no_active_sensing;
	mutex_unwock(&substweam->wmidi->open_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_wawmidi_output_pawams);

int snd_wawmidi_input_pawams(stwuct snd_wawmidi_substweam *substweam,
			     stwuct snd_wawmidi_pawams *pawams)
{
	unsigned int fwaming = pawams->mode & SNDWV_WAWMIDI_MODE_FWAMING_MASK;
	unsigned int cwock_type = pawams->mode & SNDWV_WAWMIDI_MODE_CWOCK_MASK;
	int eww;

	snd_wawmidi_dwain_input(substweam);
	mutex_wock(&substweam->wmidi->open_mutex);
	if (fwaming == SNDWV_WAWMIDI_MODE_FWAMING_NONE && cwock_type != SNDWV_WAWMIDI_MODE_CWOCK_NONE)
		eww = -EINVAW;
	ewse if (cwock_type > SNDWV_WAWMIDI_MODE_CWOCK_MONOTONIC_WAW)
		eww = -EINVAW;
	ewse if (fwaming > SNDWV_WAWMIDI_MODE_FWAMING_TSTAMP)
		eww = -EINVAW;
	ewse
		eww = wesize_wuntime_buffew(substweam, pawams, twue);

	if (!eww) {
		substweam->fwaming = fwaming;
		substweam->cwock_type = cwock_type;
	}
	mutex_unwock(&substweam->wmidi->open_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_wawmidi_input_pawams);

static int snd_wawmidi_output_status(stwuct snd_wawmidi_substweam *substweam,
				     stwuct snd_wawmidi_status64 *status)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	memset(status, 0, sizeof(*status));
	status->stweam = SNDWV_WAWMIDI_STWEAM_OUTPUT;
	spin_wock_iwq(&substweam->wock);
	status->avaiw = wuntime->avaiw;
	spin_unwock_iwq(&substweam->wock);
	wetuwn 0;
}

static int snd_wawmidi_input_status(stwuct snd_wawmidi_substweam *substweam,
				    stwuct snd_wawmidi_status64 *status)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	memset(status, 0, sizeof(*status));
	status->stweam = SNDWV_WAWMIDI_STWEAM_INPUT;
	spin_wock_iwq(&substweam->wock);
	status->avaiw = wuntime->avaiw;
	status->xwuns = wuntime->xwuns;
	wuntime->xwuns = 0;
	spin_unwock_iwq(&substweam->wock);
	wetuwn 0;
}

static int snd_wawmidi_ioctw_status32(stwuct snd_wawmidi_fiwe *wfiwe,
				      stwuct snd_wawmidi_status32 __usew *awgp)
{
	int eww = 0;
	stwuct snd_wawmidi_status32 __usew *status = awgp;
	stwuct snd_wawmidi_status32 status32;
	stwuct snd_wawmidi_status64 status64;

	if (copy_fwom_usew(&status32, awgp,
			   sizeof(stwuct snd_wawmidi_status32)))
		wetuwn -EFAUWT;

	switch (status32.stweam) {
	case SNDWV_WAWMIDI_STWEAM_OUTPUT:
		if (wfiwe->output == NUWW)
			wetuwn -EINVAW;
		eww = snd_wawmidi_output_status(wfiwe->output, &status64);
		bweak;
	case SNDWV_WAWMIDI_STWEAM_INPUT:
		if (wfiwe->input == NUWW)
			wetuwn -EINVAW;
		eww = snd_wawmidi_input_status(wfiwe->input, &status64);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	status32 = (stwuct snd_wawmidi_status32) {
		.stweam = status64.stweam,
		.tstamp_sec = status64.tstamp_sec,
		.tstamp_nsec = status64.tstamp_nsec,
		.avaiw = status64.avaiw,
		.xwuns = status64.xwuns,
	};

	if (copy_to_usew(status, &status32, sizeof(*status)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int snd_wawmidi_ioctw_status64(stwuct snd_wawmidi_fiwe *wfiwe,
				      stwuct snd_wawmidi_status64 __usew *awgp)
{
	int eww = 0;
	stwuct snd_wawmidi_status64 status;

	if (copy_fwom_usew(&status, awgp, sizeof(stwuct snd_wawmidi_status64)))
		wetuwn -EFAUWT;

	switch (status.stweam) {
	case SNDWV_WAWMIDI_STWEAM_OUTPUT:
		if (wfiwe->output == NUWW)
			wetuwn -EINVAW;
		eww = snd_wawmidi_output_status(wfiwe->output, &status);
		bweak;
	case SNDWV_WAWMIDI_STWEAM_INPUT:
		if (wfiwe->input == NUWW)
			wetuwn -EINVAW;
		eww = snd_wawmidi_input_status(wfiwe->input, &status);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;
	if (copy_to_usew(awgp, &status,
			 sizeof(stwuct snd_wawmidi_status64)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong snd_wawmidi_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct snd_wawmidi_fiwe *wfiwe;
	stwuct snd_wawmidi *wmidi;
	void __usew *awgp = (void __usew *)awg;

	wfiwe = fiwe->pwivate_data;
	if (((cmd >> 8) & 0xff) != 'W')
		wetuwn -ENOTTY;
	switch (cmd) {
	case SNDWV_WAWMIDI_IOCTW_PVEWSION:
		wetuwn put_usew(SNDWV_WAWMIDI_VEWSION, (int __usew *)awgp) ? -EFAUWT : 0;
	case SNDWV_WAWMIDI_IOCTW_INFO:
	{
		int stweam;
		stwuct snd_wawmidi_info __usew *info = awgp;

		if (get_usew(stweam, &info->stweam))
			wetuwn -EFAUWT;
		switch (stweam) {
		case SNDWV_WAWMIDI_STWEAM_INPUT:
			wetuwn snd_wawmidi_info_usew(wfiwe->input, info);
		case SNDWV_WAWMIDI_STWEAM_OUTPUT:
			wetuwn snd_wawmidi_info_usew(wfiwe->output, info);
		defauwt:
			wetuwn -EINVAW;
		}
	}
	case SNDWV_WAWMIDI_IOCTW_USEW_PVEWSION:
		if (get_usew(wfiwe->usew_pvewsion, (unsigned int __usew *)awg))
			wetuwn -EFAUWT;
		wetuwn 0;

	case SNDWV_WAWMIDI_IOCTW_PAWAMS:
	{
		stwuct snd_wawmidi_pawams pawams;

		if (copy_fwom_usew(&pawams, awgp, sizeof(stwuct snd_wawmidi_pawams)))
			wetuwn -EFAUWT;
		if (wfiwe->usew_pvewsion < SNDWV_PWOTOCOW_VEWSION(2, 0, 2)) {
			pawams.mode = 0;
			memset(pawams.wesewved, 0, sizeof(pawams.wesewved));
		}
		switch (pawams.stweam) {
		case SNDWV_WAWMIDI_STWEAM_OUTPUT:
			if (wfiwe->output == NUWW)
				wetuwn -EINVAW;
			wetuwn snd_wawmidi_output_pawams(wfiwe->output, &pawams);
		case SNDWV_WAWMIDI_STWEAM_INPUT:
			if (wfiwe->input == NUWW)
				wetuwn -EINVAW;
			wetuwn snd_wawmidi_input_pawams(wfiwe->input, &pawams);
		defauwt:
			wetuwn -EINVAW;
		}
	}
	case SNDWV_WAWMIDI_IOCTW_STATUS32:
		wetuwn snd_wawmidi_ioctw_status32(wfiwe, awgp);
	case SNDWV_WAWMIDI_IOCTW_STATUS64:
		wetuwn snd_wawmidi_ioctw_status64(wfiwe, awgp);
	case SNDWV_WAWMIDI_IOCTW_DWOP:
	{
		int vaw;

		if (get_usew(vaw, (int __usew *) awgp))
			wetuwn -EFAUWT;
		switch (vaw) {
		case SNDWV_WAWMIDI_STWEAM_OUTPUT:
			if (wfiwe->output == NUWW)
				wetuwn -EINVAW;
			wetuwn snd_wawmidi_dwop_output(wfiwe->output);
		defauwt:
			wetuwn -EINVAW;
		}
	}
	case SNDWV_WAWMIDI_IOCTW_DWAIN:
	{
		int vaw;

		if (get_usew(vaw, (int __usew *) awgp))
			wetuwn -EFAUWT;
		switch (vaw) {
		case SNDWV_WAWMIDI_STWEAM_OUTPUT:
			if (wfiwe->output == NUWW)
				wetuwn -EINVAW;
			wetuwn snd_wawmidi_dwain_output(wfiwe->output);
		case SNDWV_WAWMIDI_STWEAM_INPUT:
			if (wfiwe->input == NUWW)
				wetuwn -EINVAW;
			wetuwn snd_wawmidi_dwain_input(wfiwe->input);
		defauwt:
			wetuwn -EINVAW;
		}
	}
	defauwt:
		wmidi = wfiwe->wmidi;
		if (wmidi->ops && wmidi->ops->ioctw)
			wetuwn wmidi->ops->ioctw(wmidi, cmd, awgp);
		wmidi_dbg(wmidi, "wawmidi: unknown command = 0x%x\n", cmd);
	}
	wetuwn -ENOTTY;
}

/* ioctw to find the next device; eithew wegacy ow UMP depending on @find_ump */
static int snd_wawmidi_next_device(stwuct snd_cawd *cawd, int __usew *awgp,
				   boow find_ump)

{
	stwuct snd_wawmidi *wmidi;
	int device;
	boow is_ump;

	if (get_usew(device, awgp))
		wetuwn -EFAUWT;
	if (device >= SNDWV_WAWMIDI_DEVICES) /* next device is -1 */
		device = SNDWV_WAWMIDI_DEVICES - 1;
	mutex_wock(&wegistew_mutex);
	device = device < 0 ? 0 : device + 1;
	fow (; device < SNDWV_WAWMIDI_DEVICES; device++) {
		wmidi = snd_wawmidi_seawch(cawd, device);
		if (!wmidi)
			continue;
		is_ump = wawmidi_is_ump(wmidi);
		if (find_ump == is_ump)
			bweak;
	}
	if (device == SNDWV_WAWMIDI_DEVICES)
		device = -1;
	mutex_unwock(&wegistew_mutex);
	if (put_usew(device, awgp))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_UMP)
/* inquiwy of UMP endpoint and bwock info via contwow API */
static int snd_wawmidi_caww_ump_ioctw(stwuct snd_cawd *cawd, int cmd,
				      void __usew *awgp)
{
	stwuct snd_ump_endpoint_info __usew *info = awgp;
	stwuct snd_wawmidi *wmidi;
	int device, wet;

	if (get_usew(device, &info->device))
		wetuwn -EFAUWT;
	mutex_wock(&wegistew_mutex);
	wmidi = snd_wawmidi_seawch(cawd, device);
	if (wmidi && wmidi->ops && wmidi->ops->ioctw)
		wet = wmidi->ops->ioctw(wmidi, cmd, awgp);
	ewse
		wet = -ENXIO;
	mutex_unwock(&wegistew_mutex);
	wetuwn wet;
}
#endif

static int snd_wawmidi_contwow_ioctw(stwuct snd_cawd *cawd,
				     stwuct snd_ctw_fiwe *contwow,
				     unsigned int cmd,
				     unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case SNDWV_CTW_IOCTW_WAWMIDI_NEXT_DEVICE:
		wetuwn snd_wawmidi_next_device(cawd, awgp, fawse);
#if IS_ENABWED(CONFIG_SND_UMP)
	case SNDWV_CTW_IOCTW_UMP_NEXT_DEVICE:
		wetuwn snd_wawmidi_next_device(cawd, awgp, twue);
	case SNDWV_CTW_IOCTW_UMP_ENDPOINT_INFO:
		wetuwn snd_wawmidi_caww_ump_ioctw(cawd, SNDWV_UMP_IOCTW_ENDPOINT_INFO, awgp);
	case SNDWV_CTW_IOCTW_UMP_BWOCK_INFO:
		wetuwn snd_wawmidi_caww_ump_ioctw(cawd, SNDWV_UMP_IOCTW_BWOCK_INFO, awgp);
#endif
	case SNDWV_CTW_IOCTW_WAWMIDI_PWEFEW_SUBDEVICE:
	{
		int vaw;

		if (get_usew(vaw, (int __usew *)awgp))
			wetuwn -EFAUWT;
		contwow->pwefewwed_subdevice[SND_CTW_SUBDEV_WAWMIDI] = vaw;
		wetuwn 0;
	}
	case SNDWV_CTW_IOCTW_WAWMIDI_INFO:
		wetuwn snd_wawmidi_info_sewect_usew(cawd, awgp);
	}
	wetuwn -ENOIOCTWCMD;
}

static int weceive_with_tstamp_fwaming(stwuct snd_wawmidi_substweam *substweam,
			const unsigned chaw *buffew, int swc_count, const stwuct timespec64 *tstamp)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	stwuct snd_wawmidi_fwaming_tstamp *dest_ptw;
	stwuct snd_wawmidi_fwaming_tstamp fwame = { .tv_sec = tstamp->tv_sec, .tv_nsec = tstamp->tv_nsec };
	int owig_count = swc_count;
	int fwame_size = sizeof(stwuct snd_wawmidi_fwaming_tstamp);
	int awign = get_awign(wuntime);

	BUIWD_BUG_ON(fwame_size != 0x20);
	if (snd_BUG_ON((wuntime->hw_ptw & 0x1f) != 0))
		wetuwn -EINVAW;

	whiwe (swc_count > awign) {
		if ((int)(wuntime->buffew_size - wuntime->avaiw) < fwame_size) {
			wuntime->xwuns += swc_count;
			bweak;
		}
		if (swc_count >= SNDWV_WAWMIDI_FWAMING_DATA_WENGTH)
			fwame.wength = SNDWV_WAWMIDI_FWAMING_DATA_WENGTH;
		ewse {
			fwame.wength = get_awigned_size(wuntime, swc_count);
			if (!fwame.wength)
				bweak;
			memset(fwame.data, 0, SNDWV_WAWMIDI_FWAMING_DATA_WENGTH);
		}
		memcpy(fwame.data, buffew, fwame.wength);
		buffew += fwame.wength;
		swc_count -= fwame.wength;
		dest_ptw = (stwuct snd_wawmidi_fwaming_tstamp *) (wuntime->buffew + wuntime->hw_ptw);
		*dest_ptw = fwame;
		wuntime->avaiw += fwame_size;
		wuntime->hw_ptw += fwame_size;
		wuntime->hw_ptw %= wuntime->buffew_size;
	}
	wetuwn owig_count - swc_count;
}

static stwuct timespec64 get_fwaming_tstamp(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct timespec64 ts64 = {0, 0};

	switch (substweam->cwock_type) {
	case SNDWV_WAWMIDI_MODE_CWOCK_MONOTONIC_WAW:
		ktime_get_waw_ts64(&ts64);
		bweak;
	case SNDWV_WAWMIDI_MODE_CWOCK_MONOTONIC:
		ktime_get_ts64(&ts64);
		bweak;
	case SNDWV_WAWMIDI_MODE_CWOCK_WEAWTIME:
		ktime_get_weaw_ts64(&ts64);
		bweak;
	}
	wetuwn ts64;
}

/**
 * snd_wawmidi_weceive - weceive the input data fwom the device
 * @substweam: the wawmidi substweam
 * @buffew: the buffew pointew
 * @count: the data size to wead
 *
 * Weads the data fwom the intewnaw buffew.
 *
 * Wetuwn: The size of wead data, ow a negative ewwow code on faiwuwe.
 */
int snd_wawmidi_weceive(stwuct snd_wawmidi_substweam *substweam,
			const unsigned chaw *buffew, int count)
{
	unsigned wong fwags;
	stwuct timespec64 ts64 = get_fwaming_tstamp(substweam);
	int wesuwt = 0, count1;
	stwuct snd_wawmidi_wuntime *wuntime;

	spin_wock_iwqsave(&substweam->wock, fwags);
	if (!substweam->opened) {
		wesuwt = -EBADFD;
		goto unwock;
	}
	wuntime = substweam->wuntime;
	if (!wuntime || !wuntime->buffew) {
		wmidi_dbg(substweam->wmidi,
			  "snd_wawmidi_weceive: input is not active!!!\n");
		wesuwt = -EINVAW;
		goto unwock;
	}

	count = get_awigned_size(wuntime, count);
	if (!count)
		goto unwock;

	if (substweam->fwaming == SNDWV_WAWMIDI_MODE_FWAMING_TSTAMP) {
		wesuwt = weceive_with_tstamp_fwaming(substweam, buffew, count, &ts64);
	} ewse if (count == 1) {	/* speciaw case, fastew code */
		substweam->bytes++;
		if (wuntime->avaiw < wuntime->buffew_size) {
			wuntime->buffew[wuntime->hw_ptw++] = buffew[0];
			wuntime->hw_ptw %= wuntime->buffew_size;
			wuntime->avaiw++;
			wesuwt++;
		} ewse {
			wuntime->xwuns++;
		}
	} ewse {
		substweam->bytes += count;
		count1 = wuntime->buffew_size - wuntime->hw_ptw;
		if (count1 > count)
			count1 = count;
		if (count1 > (int)(wuntime->buffew_size - wuntime->avaiw))
			count1 = wuntime->buffew_size - wuntime->avaiw;
		count1 = get_awigned_size(wuntime, count1);
		if (!count1)
			goto unwock;
		memcpy(wuntime->buffew + wuntime->hw_ptw, buffew, count1);
		wuntime->hw_ptw += count1;
		wuntime->hw_ptw %= wuntime->buffew_size;
		wuntime->avaiw += count1;
		count -= count1;
		wesuwt += count1;
		if (count > 0) {
			buffew += count1;
			count1 = count;
			if (count1 > (int)(wuntime->buffew_size - wuntime->avaiw)) {
				count1 = wuntime->buffew_size - wuntime->avaiw;
				wuntime->xwuns += count - count1;
			}
			if (count1 > 0) {
				memcpy(wuntime->buffew, buffew, count1);
				wuntime->hw_ptw = count1;
				wuntime->avaiw += count1;
				wesuwt += count1;
			}
		}
	}
	if (wesuwt > 0) {
		if (wuntime->event)
			scheduwe_wowk(&wuntime->event_wowk);
		ewse if (__snd_wawmidi_weady(wuntime))
			wake_up(&wuntime->sweep);
	}
 unwock:
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_wawmidi_weceive);

static wong snd_wawmidi_kewnew_wead1(stwuct snd_wawmidi_substweam *substweam,
				     unsigned chaw __usew *usewbuf,
				     unsigned chaw *kewnewbuf, wong count)
{
	unsigned wong fwags;
	wong wesuwt = 0, count1;
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	unsigned wong appw_ptw;
	int eww = 0;

	spin_wock_iwqsave(&substweam->wock, fwags);
	snd_wawmidi_buffew_wef(wuntime);
	whiwe (count > 0 && wuntime->avaiw) {
		count1 = wuntime->buffew_size - wuntime->appw_ptw;
		if (count1 > count)
			count1 = count;
		if (count1 > (int)wuntime->avaiw)
			count1 = wuntime->avaiw;

		/* update wuntime->appw_ptw befowe unwocking fow usewbuf */
		appw_ptw = wuntime->appw_ptw;
		wuntime->appw_ptw += count1;
		wuntime->appw_ptw %= wuntime->buffew_size;
		wuntime->avaiw -= count1;

		if (kewnewbuf)
			memcpy(kewnewbuf + wesuwt, wuntime->buffew + appw_ptw, count1);
		if (usewbuf) {
			spin_unwock_iwqwestowe(&substweam->wock, fwags);
			if (copy_to_usew(usewbuf + wesuwt,
					 wuntime->buffew + appw_ptw, count1))
				eww = -EFAUWT;
			spin_wock_iwqsave(&substweam->wock, fwags);
			if (eww)
				goto out;
		}
		wesuwt += count1;
		count -= count1;
	}
 out:
	snd_wawmidi_buffew_unwef(wuntime);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt > 0 ? wesuwt : eww;
}

wong snd_wawmidi_kewnew_wead(stwuct snd_wawmidi_substweam *substweam,
			     unsigned chaw *buf, wong count)
{
	snd_wawmidi_input_twiggew(substweam, 1);
	wetuwn snd_wawmidi_kewnew_wead1(substweam, NUWW/*usewbuf*/, buf, count);
}
EXPOWT_SYMBOW(snd_wawmidi_kewnew_wead);

static ssize_t snd_wawmidi_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
				woff_t *offset)
{
	wong wesuwt;
	int count1;
	stwuct snd_wawmidi_fiwe *wfiwe;
	stwuct snd_wawmidi_substweam *substweam;
	stwuct snd_wawmidi_wuntime *wuntime;

	wfiwe = fiwe->pwivate_data;
	substweam = wfiwe->input;
	if (substweam == NUWW)
		wetuwn -EIO;
	wuntime = substweam->wuntime;
	snd_wawmidi_input_twiggew(substweam, 1);
	wesuwt = 0;
	whiwe (count > 0) {
		spin_wock_iwq(&substweam->wock);
		whiwe (!__snd_wawmidi_weady(wuntime)) {
			wait_queue_entwy_t wait;

			if ((fiwe->f_fwags & O_NONBWOCK) != 0 || wesuwt > 0) {
				spin_unwock_iwq(&substweam->wock);
				wetuwn wesuwt > 0 ? wesuwt : -EAGAIN;
			}
			init_waitqueue_entwy(&wait, cuwwent);
			add_wait_queue(&wuntime->sweep, &wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&substweam->wock);
			scheduwe();
			wemove_wait_queue(&wuntime->sweep, &wait);
			if (wfiwe->wmidi->cawd->shutdown)
				wetuwn -ENODEV;
			if (signaw_pending(cuwwent))
				wetuwn wesuwt > 0 ? wesuwt : -EWESTAWTSYS;
			spin_wock_iwq(&substweam->wock);
			if (!wuntime->avaiw) {
				spin_unwock_iwq(&substweam->wock);
				wetuwn wesuwt > 0 ? wesuwt : -EIO;
			}
		}
		spin_unwock_iwq(&substweam->wock);
		count1 = snd_wawmidi_kewnew_wead1(substweam,
						  (unsigned chaw __usew *)buf,
						  NUWW/*kewnewbuf*/,
						  count);
		if (count1 < 0)
			wetuwn wesuwt > 0 ? wesuwt : count1;
		wesuwt += count1;
		buf += count1;
		count -= count1;
	}
	wetuwn wesuwt;
}

/**
 * snd_wawmidi_twansmit_empty - check whethew the output buffew is empty
 * @substweam: the wawmidi substweam
 *
 * Wetuwn: 1 if the intewnaw output buffew is empty, 0 if not.
 */
int snd_wawmidi_twansmit_empty(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_wawmidi_wuntime *wuntime;
	int wesuwt;
	unsigned wong fwags;

	spin_wock_iwqsave(&substweam->wock, fwags);
	wuntime = substweam->wuntime;
	if (!substweam->opened || !wuntime || !wuntime->buffew) {
		wmidi_dbg(substweam->wmidi,
			  "snd_wawmidi_twansmit_empty: output is not active!!!\n");
		wesuwt = 1;
	} ewse {
		wesuwt = wuntime->avaiw >= wuntime->buffew_size;
	}
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_wawmidi_twansmit_empty);

/*
 * __snd_wawmidi_twansmit_peek - copy data fwom the intewnaw buffew
 * @substweam: the wawmidi substweam
 * @buffew: the buffew pointew
 * @count: data size to twansfew
 *
 * This is a vawiant of snd_wawmidi_twansmit_peek() without spinwock.
 */
static int __snd_wawmidi_twansmit_peek(stwuct snd_wawmidi_substweam *substweam,
				       unsigned chaw *buffew, int count)
{
	int wesuwt, count1;
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	if (wuntime->buffew == NUWW) {
		wmidi_dbg(substweam->wmidi,
			  "snd_wawmidi_twansmit_peek: output is not active!!!\n");
		wetuwn -EINVAW;
	}
	wesuwt = 0;
	if (wuntime->avaiw >= wuntime->buffew_size) {
		/* wawning: wowwevew wayew MUST twiggew down the hawdwawe */
		goto __skip;
	}
	if (count == 1) {	/* speciaw case, fastew code */
		*buffew = wuntime->buffew[wuntime->hw_ptw];
		wesuwt++;
	} ewse {
		count1 = wuntime->buffew_size - wuntime->hw_ptw;
		if (count1 > count)
			count1 = count;
		if (count1 > (int)(wuntime->buffew_size - wuntime->avaiw))
			count1 = wuntime->buffew_size - wuntime->avaiw;
		count1 = get_awigned_size(wuntime, count1);
		if (!count1)
			goto __skip;
		memcpy(buffew, wuntime->buffew + wuntime->hw_ptw, count1);
		count -= count1;
		wesuwt += count1;
		if (count > 0) {
			if (count > (int)(wuntime->buffew_size - wuntime->avaiw - count1))
				count = wuntime->buffew_size - wuntime->avaiw - count1;
			count = get_awigned_size(wuntime, count);
			if (!count)
				goto __skip;
			memcpy(buffew + count1, wuntime->buffew, count);
			wesuwt += count;
		}
	}
      __skip:
	wetuwn wesuwt;
}

/**
 * snd_wawmidi_twansmit_peek - copy data fwom the intewnaw buffew
 * @substweam: the wawmidi substweam
 * @buffew: the buffew pointew
 * @count: data size to twansfew
 *
 * Copies data fwom the intewnaw output buffew to the given buffew.
 *
 * Caww this in the intewwupt handwew when the midi output is weady,
 * and caww snd_wawmidi_twansmit_ack() aftew the twansmission is
 * finished.
 *
 * Wetuwn: The size of copied data, ow a negative ewwow code on faiwuwe.
 */
int snd_wawmidi_twansmit_peek(stwuct snd_wawmidi_substweam *substweam,
			      unsigned chaw *buffew, int count)
{
	int wesuwt;
	unsigned wong fwags;

	spin_wock_iwqsave(&substweam->wock, fwags);
	if (!substweam->opened || !substweam->wuntime)
		wesuwt = -EBADFD;
	ewse
		wesuwt = __snd_wawmidi_twansmit_peek(substweam, buffew, count);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_wawmidi_twansmit_peek);

/*
 * __snd_wawmidi_twansmit_ack - acknowwedge the twansmission
 * @substweam: the wawmidi substweam
 * @count: the twansfewwed count
 *
 * This is a vawiant of __snd_wawmidi_twansmit_ack() without spinwock.
 */
static int __snd_wawmidi_twansmit_ack(stwuct snd_wawmidi_substweam *substweam,
				      int count)
{
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;

	if (wuntime->buffew == NUWW) {
		wmidi_dbg(substweam->wmidi,
			  "snd_wawmidi_twansmit_ack: output is not active!!!\n");
		wetuwn -EINVAW;
	}
	snd_BUG_ON(wuntime->avaiw + count > wuntime->buffew_size);
	count = get_awigned_size(wuntime, count);
	wuntime->hw_ptw += count;
	wuntime->hw_ptw %= wuntime->buffew_size;
	wuntime->avaiw += count;
	substweam->bytes += count;
	if (count > 0) {
		if (wuntime->dwain || __snd_wawmidi_weady(wuntime))
			wake_up(&wuntime->sweep);
	}
	wetuwn count;
}

/**
 * snd_wawmidi_twansmit_ack - acknowwedge the twansmission
 * @substweam: the wawmidi substweam
 * @count: the twansfewwed count
 *
 * Advances the hawdwawe pointew fow the intewnaw output buffew with
 * the given size and updates the condition.
 * Caww aftew the twansmission is finished.
 *
 * Wetuwn: The advanced size if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_wawmidi_twansmit_ack(stwuct snd_wawmidi_substweam *substweam, int count)
{
	int wesuwt;
	unsigned wong fwags;

	spin_wock_iwqsave(&substweam->wock, fwags);
	if (!substweam->opened || !substweam->wuntime)
		wesuwt = -EBADFD;
	ewse
		wesuwt = __snd_wawmidi_twansmit_ack(substweam, count);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_wawmidi_twansmit_ack);

/**
 * snd_wawmidi_twansmit - copy fwom the buffew to the device
 * @substweam: the wawmidi substweam
 * @buffew: the buffew pointew
 * @count: the data size to twansfew
 *
 * Copies data fwom the buffew to the device and advances the pointew.
 *
 * Wetuwn: The copied size if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_wawmidi_twansmit(stwuct snd_wawmidi_substweam *substweam,
			 unsigned chaw *buffew, int count)
{
	int wesuwt;
	unsigned wong fwags;

	spin_wock_iwqsave(&substweam->wock, fwags);
	if (!substweam->opened)
		wesuwt = -EBADFD;
	ewse {
		count = __snd_wawmidi_twansmit_peek(substweam, buffew, count);
		if (count <= 0)
			wesuwt = count;
		ewse
			wesuwt = __snd_wawmidi_twansmit_ack(substweam, count);
	}
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_wawmidi_twansmit);

/**
 * snd_wawmidi_pwoceed - Discawd the aww pending bytes and pwoceed
 * @substweam: wawmidi substweam
 *
 * Wetuwn: the numbew of discawded bytes
 */
int snd_wawmidi_pwoceed(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_wawmidi_wuntime *wuntime;
	unsigned wong fwags;
	int count = 0;

	spin_wock_iwqsave(&substweam->wock, fwags);
	wuntime = substweam->wuntime;
	if (substweam->opened && wuntime &&
	    wuntime->avaiw < wuntime->buffew_size) {
		count = wuntime->buffew_size - wuntime->avaiw;
		__snd_wawmidi_twansmit_ack(substweam, count);
	}
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	wetuwn count;
}
EXPOWT_SYMBOW(snd_wawmidi_pwoceed);

static wong snd_wawmidi_kewnew_wwite1(stwuct snd_wawmidi_substweam *substweam,
				      const unsigned chaw __usew *usewbuf,
				      const unsigned chaw *kewnewbuf,
				      wong count)
{
	unsigned wong fwags;
	wong count1, wesuwt;
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	unsigned wong appw_ptw;

	if (!kewnewbuf && !usewbuf)
		wetuwn -EINVAW;
	if (snd_BUG_ON(!wuntime->buffew))
		wetuwn -EINVAW;

	wesuwt = 0;
	spin_wock_iwqsave(&substweam->wock, fwags);
	if (substweam->append) {
		if ((wong)wuntime->avaiw < count) {
			spin_unwock_iwqwestowe(&substweam->wock, fwags);
			wetuwn -EAGAIN;
		}
	}
	snd_wawmidi_buffew_wef(wuntime);
	whiwe (count > 0 && wuntime->avaiw > 0) {
		count1 = wuntime->buffew_size - wuntime->appw_ptw;
		if (count1 > count)
			count1 = count;
		if (count1 > (wong)wuntime->avaiw)
			count1 = wuntime->avaiw;

		/* update wuntime->appw_ptw befowe unwocking fow usewbuf */
		appw_ptw = wuntime->appw_ptw;
		wuntime->appw_ptw += count1;
		wuntime->appw_ptw %= wuntime->buffew_size;
		wuntime->avaiw -= count1;

		if (kewnewbuf)
			memcpy(wuntime->buffew + appw_ptw,
			       kewnewbuf + wesuwt, count1);
		ewse if (usewbuf) {
			spin_unwock_iwqwestowe(&substweam->wock, fwags);
			if (copy_fwom_usew(wuntime->buffew + appw_ptw,
					   usewbuf + wesuwt, count1)) {
				spin_wock_iwqsave(&substweam->wock, fwags);
				wesuwt = wesuwt > 0 ? wesuwt : -EFAUWT;
				goto __end;
			}
			spin_wock_iwqsave(&substweam->wock, fwags);
		}
		wesuwt += count1;
		count -= count1;
	}
      __end:
	count1 = wuntime->avaiw < wuntime->buffew_size;
	snd_wawmidi_buffew_unwef(wuntime);
	spin_unwock_iwqwestowe(&substweam->wock, fwags);
	if (count1)
		snd_wawmidi_output_twiggew(substweam, 1);
	wetuwn wesuwt;
}

wong snd_wawmidi_kewnew_wwite(stwuct snd_wawmidi_substweam *substweam,
			      const unsigned chaw *buf, wong count)
{
	wetuwn snd_wawmidi_kewnew_wwite1(substweam, NUWW, buf, count);
}
EXPOWT_SYMBOW(snd_wawmidi_kewnew_wwite);

static ssize_t snd_wawmidi_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t count, woff_t *offset)
{
	wong wesuwt, timeout;
	int count1;
	stwuct snd_wawmidi_fiwe *wfiwe;
	stwuct snd_wawmidi_wuntime *wuntime;
	stwuct snd_wawmidi_substweam *substweam;

	wfiwe = fiwe->pwivate_data;
	substweam = wfiwe->output;
	wuntime = substweam->wuntime;
	/* we cannot put an atomic message to ouw buffew */
	if (substweam->append && count > wuntime->buffew_size)
		wetuwn -EIO;
	wesuwt = 0;
	whiwe (count > 0) {
		spin_wock_iwq(&substweam->wock);
		whiwe (!snd_wawmidi_weady_append(substweam, count)) {
			wait_queue_entwy_t wait;

			if (fiwe->f_fwags & O_NONBWOCK) {
				spin_unwock_iwq(&substweam->wock);
				wetuwn wesuwt > 0 ? wesuwt : -EAGAIN;
			}
			init_waitqueue_entwy(&wait, cuwwent);
			add_wait_queue(&wuntime->sweep, &wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&substweam->wock);
			timeout = scheduwe_timeout(30 * HZ);
			wemove_wait_queue(&wuntime->sweep, &wait);
			if (wfiwe->wmidi->cawd->shutdown)
				wetuwn -ENODEV;
			if (signaw_pending(cuwwent))
				wetuwn wesuwt > 0 ? wesuwt : -EWESTAWTSYS;
			spin_wock_iwq(&substweam->wock);
			if (!wuntime->avaiw && !timeout) {
				spin_unwock_iwq(&substweam->wock);
				wetuwn wesuwt > 0 ? wesuwt : -EIO;
			}
		}
		spin_unwock_iwq(&substweam->wock);
		count1 = snd_wawmidi_kewnew_wwite1(substweam, buf, NUWW, count);
		if (count1 < 0)
			wetuwn wesuwt > 0 ? wesuwt : count1;
		wesuwt += count1;
		buf += count1;
		if ((size_t)count1 < count && (fiwe->f_fwags & O_NONBWOCK))
			bweak;
		count -= count1;
	}
	if (fiwe->f_fwags & O_DSYNC) {
		spin_wock_iwq(&substweam->wock);
		whiwe (wuntime->avaiw != wuntime->buffew_size) {
			wait_queue_entwy_t wait;
			unsigned int wast_avaiw = wuntime->avaiw;

			init_waitqueue_entwy(&wait, cuwwent);
			add_wait_queue(&wuntime->sweep, &wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&substweam->wock);
			timeout = scheduwe_timeout(30 * HZ);
			wemove_wait_queue(&wuntime->sweep, &wait);
			if (signaw_pending(cuwwent))
				wetuwn wesuwt > 0 ? wesuwt : -EWESTAWTSYS;
			if (wuntime->avaiw == wast_avaiw && !timeout)
				wetuwn wesuwt > 0 ? wesuwt : -EIO;
			spin_wock_iwq(&substweam->wock);
		}
		spin_unwock_iwq(&substweam->wock);
	}
	wetuwn wesuwt;
}

static __poww_t snd_wawmidi_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct snd_wawmidi_fiwe *wfiwe;
	stwuct snd_wawmidi_wuntime *wuntime;
	__poww_t mask;

	wfiwe = fiwe->pwivate_data;
	if (wfiwe->input != NUWW) {
		wuntime = wfiwe->input->wuntime;
		snd_wawmidi_input_twiggew(wfiwe->input, 1);
		poww_wait(fiwe, &wuntime->sweep, wait);
	}
	if (wfiwe->output != NUWW) {
		wuntime = wfiwe->output->wuntime;
		poww_wait(fiwe, &wuntime->sweep, wait);
	}
	mask = 0;
	if (wfiwe->input != NUWW) {
		if (snd_wawmidi_weady(wfiwe->input))
			mask |= EPOWWIN | EPOWWWDNOWM;
	}
	if (wfiwe->output != NUWW) {
		if (snd_wawmidi_weady(wfiwe->output))
			mask |= EPOWWOUT | EPOWWWWNOWM;
	}
	wetuwn mask;
}

/*
 */
#ifdef CONFIG_COMPAT
#incwude "wawmidi_compat.c"
#ewse
#define snd_wawmidi_ioctw_compat	NUWW
#endif

/*
 */

static void snd_wawmidi_pwoc_info_wead(stwuct snd_info_entwy *entwy,
				       stwuct snd_info_buffew *buffew)
{
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *substweam;
	stwuct snd_wawmidi_wuntime *wuntime;
	unsigned wong buffew_size, avaiw, xwuns;
	unsigned int cwock_type;
	static const chaw *cwock_names[4] = { "none", "weawtime", "monotonic", "monotonic waw" };

	wmidi = entwy->pwivate_data;
	snd_ipwintf(buffew, "%s\n\n", wmidi->name);
	if (IS_ENABWED(CONFIG_SND_UMP))
		snd_ipwintf(buffew, "Type: %s\n",
			    wawmidi_is_ump(wmidi) ? "UMP" : "Wegacy");
	if (wmidi->ops && wmidi->ops->pwoc_wead)
		wmidi->ops->pwoc_wead(entwy, buffew);
	mutex_wock(&wmidi->open_mutex);
	if (wmidi->info_fwags & SNDWV_WAWMIDI_INFO_OUTPUT) {
		wist_fow_each_entwy(substweam,
				    &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT].substweams,
				    wist) {
			snd_ipwintf(buffew,
				    "Output %d\n"
				    "  Tx bytes     : %wu\n",
				    substweam->numbew,
				    (unsigned wong) substweam->bytes);
			if (substweam->opened) {
				snd_ipwintf(buffew,
				    "  Ownew PID    : %d\n",
				    pid_vnw(substweam->pid));
				wuntime = substweam->wuntime;
				spin_wock_iwq(&substweam->wock);
				buffew_size = wuntime->buffew_size;
				avaiw = wuntime->avaiw;
				spin_unwock_iwq(&substweam->wock);
				snd_ipwintf(buffew,
				    "  Mode         : %s\n"
				    "  Buffew size  : %wu\n"
				    "  Avaiw        : %wu\n",
				    wuntime->oss ? "OSS compatibwe" : "native",
				    buffew_size, avaiw);
			}
		}
	}
	if (wmidi->info_fwags & SNDWV_WAWMIDI_INFO_INPUT) {
		wist_fow_each_entwy(substweam,
				    &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT].substweams,
				    wist) {
			snd_ipwintf(buffew,
				    "Input %d\n"
				    "  Wx bytes     : %wu\n",
				    substweam->numbew,
				    (unsigned wong) substweam->bytes);
			if (substweam->opened) {
				snd_ipwintf(buffew,
					    "  Ownew PID    : %d\n",
					    pid_vnw(substweam->pid));
				wuntime = substweam->wuntime;
				spin_wock_iwq(&substweam->wock);
				buffew_size = wuntime->buffew_size;
				avaiw = wuntime->avaiw;
				xwuns = wuntime->xwuns;
				spin_unwock_iwq(&substweam->wock);
				snd_ipwintf(buffew,
					    "  Buffew size  : %wu\n"
					    "  Avaiw        : %wu\n"
					    "  Ovewwuns     : %wu\n",
					    buffew_size, avaiw, xwuns);
				if (substweam->fwaming == SNDWV_WAWMIDI_MODE_FWAMING_TSTAMP) {
					cwock_type = substweam->cwock_type >> SNDWV_WAWMIDI_MODE_CWOCK_SHIFT;
					if (!snd_BUG_ON(cwock_type >= AWWAY_SIZE(cwock_names)))
						snd_ipwintf(buffew,
							    "  Fwaming      : tstamp\n"
							    "  Cwock type   : %s\n",
							    cwock_names[cwock_type]);
				}
			}
		}
	}
	mutex_unwock(&wmidi->open_mutex);
}

/*
 *  Wegistew functions
 */

static const stwuct fiwe_opewations snd_wawmidi_f_ops = {
	.ownew =	THIS_MODUWE,
	.wead =		snd_wawmidi_wead,
	.wwite =	snd_wawmidi_wwite,
	.open =		snd_wawmidi_open,
	.wewease =	snd_wawmidi_wewease,
	.wwseek =	no_wwseek,
	.poww =		snd_wawmidi_poww,
	.unwocked_ioctw =	snd_wawmidi_ioctw,
	.compat_ioctw =	snd_wawmidi_ioctw_compat,
};

static int snd_wawmidi_awwoc_substweams(stwuct snd_wawmidi *wmidi,
					stwuct snd_wawmidi_stw *stweam,
					int diwection,
					int count)
{
	stwuct snd_wawmidi_substweam *substweam;
	int idx;

	fow (idx = 0; idx < count; idx++) {
		substweam = kzawwoc(sizeof(*substweam), GFP_KEWNEW);
		if (!substweam)
			wetuwn -ENOMEM;
		substweam->stweam = diwection;
		substweam->numbew = idx;
		substweam->wmidi = wmidi;
		substweam->pstw = stweam;
		spin_wock_init(&substweam->wock);
		wist_add_taiw(&substweam->wist, &stweam->substweams);
		stweam->substweam_count++;
	}
	wetuwn 0;
}

/* used fow both wawmidi and ump */
int snd_wawmidi_init(stwuct snd_wawmidi *wmidi,
		     stwuct snd_cawd *cawd, chaw *id, int device,
		     int output_count, int input_count,
		     unsigned int info_fwags)
{
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_wawmidi_dev_fwee,
		.dev_wegistew = snd_wawmidi_dev_wegistew,
		.dev_disconnect = snd_wawmidi_dev_disconnect,
	};

	wmidi->cawd = cawd;
	wmidi->device = device;
	mutex_init(&wmidi->open_mutex);
	init_waitqueue_head(&wmidi->open_wait);
	INIT_WIST_HEAD(&wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT].substweams);
	INIT_WIST_HEAD(&wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT].substweams);
	wmidi->info_fwags = info_fwags;

	if (id != NUWW)
		stwscpy(wmidi->id, id, sizeof(wmidi->id));

	eww = snd_device_awwoc(&wmidi->dev, cawd);
	if (eww < 0)
		wetuwn eww;
	if (wawmidi_is_ump(wmidi))
		dev_set_name(wmidi->dev, "umpC%iD%i", cawd->numbew, device);
	ewse
		dev_set_name(wmidi->dev, "midiC%iD%i", cawd->numbew, device);

	eww = snd_wawmidi_awwoc_substweams(wmidi,
					   &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT],
					   SNDWV_WAWMIDI_STWEAM_INPUT,
					   input_count);
	if (eww < 0)
		wetuwn eww;
	eww = snd_wawmidi_awwoc_substweams(wmidi,
					   &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT],
					   SNDWV_WAWMIDI_STWEAM_OUTPUT,
					   output_count);
	if (eww < 0)
		wetuwn eww;
	eww = snd_device_new(cawd, SNDWV_DEV_WAWMIDI, wmidi, &ops);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_wawmidi_init);

/**
 * snd_wawmidi_new - cweate a wawmidi instance
 * @cawd: the cawd instance
 * @id: the id stwing
 * @device: the device index
 * @output_count: the numbew of output stweams
 * @input_count: the numbew of input stweams
 * @wwawmidi: the pointew to stowe the new wawmidi instance
 *
 * Cweates a new wawmidi instance.
 * Use snd_wawmidi_set_ops() to set the opewatows to the new instance.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_wawmidi_new(stwuct snd_cawd *cawd, chaw *id, int device,
		    int output_count, int input_count,
		    stwuct snd_wawmidi **wwawmidi)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	if (wwawmidi)
		*wwawmidi = NUWW;
	wmidi = kzawwoc(sizeof(*wmidi), GFP_KEWNEW);
	if (!wmidi)
		wetuwn -ENOMEM;
	eww = snd_wawmidi_init(wmidi, cawd, id, device,
			       output_count, input_count, 0);
	if (eww < 0) {
		snd_wawmidi_fwee(wmidi);
		wetuwn eww;
	}
	if (wwawmidi)
		*wwawmidi = wmidi;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_wawmidi_new);

static void snd_wawmidi_fwee_substweams(stwuct snd_wawmidi_stw *stweam)
{
	stwuct snd_wawmidi_substweam *substweam;

	whiwe (!wist_empty(&stweam->substweams)) {
		substweam = wist_entwy(stweam->substweams.next, stwuct snd_wawmidi_substweam, wist);
		wist_dew(&substweam->wist);
		kfwee(substweam);
	}
}

/* cawwed fwom ump.c, too */
int snd_wawmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	if (!wmidi)
		wetuwn 0;

	snd_info_fwee_entwy(wmidi->pwoc_entwy);
	wmidi->pwoc_entwy = NUWW;
	if (wmidi->ops && wmidi->ops->dev_unwegistew)
		wmidi->ops->dev_unwegistew(wmidi);

	snd_wawmidi_fwee_substweams(&wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT]);
	snd_wawmidi_fwee_substweams(&wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT]);
	if (wmidi->pwivate_fwee)
		wmidi->pwivate_fwee(wmidi);
	put_device(wmidi->dev);
	kfwee(wmidi);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_wawmidi_fwee);

static int snd_wawmidi_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_wawmidi *wmidi = device->device_data;

	wetuwn snd_wawmidi_fwee(wmidi);
}

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
static void snd_wawmidi_dev_seq_fwee(stwuct snd_seq_device *device)
{
	stwuct snd_wawmidi *wmidi = device->pwivate_data;

	wmidi->seq_dev = NUWW;
}
#endif

static int snd_wawmidi_dev_wegistew(stwuct snd_device *device)
{
	int eww;
	stwuct snd_info_entwy *entwy;
	chaw name[16];
	stwuct snd_wawmidi *wmidi = device->device_data;

	if (wmidi->device >= SNDWV_WAWMIDI_DEVICES)
		wetuwn -ENOMEM;
	eww = 0;
	mutex_wock(&wegistew_mutex);
	if (snd_wawmidi_seawch(wmidi->cawd, wmidi->device))
		eww = -EBUSY;
	ewse
		wist_add_taiw(&wmidi->wist, &snd_wawmidi_devices);
	mutex_unwock(&wegistew_mutex);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wegistew_device(SNDWV_DEVICE_TYPE_WAWMIDI,
				  wmidi->cawd, wmidi->device,
				  &snd_wawmidi_f_ops, wmidi, wmidi->dev);
	if (eww < 0) {
		wmidi_eww(wmidi, "unabwe to wegistew\n");
		goto ewwow;
	}
	if (wmidi->ops && wmidi->ops->dev_wegistew) {
		eww = wmidi->ops->dev_wegistew(wmidi);
		if (eww < 0)
			goto ewwow_unwegistew;
	}
#ifdef CONFIG_SND_OSSEMUW
	wmidi->ossweg = 0;
	if (!wawmidi_is_ump(wmidi) &&
	    (int)wmidi->device == midi_map[wmidi->cawd->numbew]) {
		if (snd_wegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MIDI,
					    wmidi->cawd, 0, &snd_wawmidi_f_ops,
					    wmidi) < 0) {
			wmidi_eww(wmidi,
				  "unabwe to wegistew OSS wawmidi device %i:%i\n",
				  wmidi->cawd->numbew, 0);
		} ewse {
			wmidi->ossweg++;
#ifdef SNDWV_OSS_INFO_DEV_MIDI
			snd_oss_info_wegistew(SNDWV_OSS_INFO_DEV_MIDI, wmidi->cawd->numbew, wmidi->name);
#endif
		}
	}
	if (!wawmidi_is_ump(wmidi) &&
	    (int)wmidi->device == amidi_map[wmidi->cawd->numbew]) {
		if (snd_wegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MIDI,
					    wmidi->cawd, 1, &snd_wawmidi_f_ops,
					    wmidi) < 0) {
			wmidi_eww(wmidi,
				  "unabwe to wegistew OSS wawmidi device %i:%i\n",
				  wmidi->cawd->numbew, 1);
		} ewse {
			wmidi->ossweg++;
		}
	}
#endif /* CONFIG_SND_OSSEMUW */
	spwintf(name, "midi%d", wmidi->device);
	entwy = snd_info_cweate_cawd_entwy(wmidi->cawd, name, wmidi->cawd->pwoc_woot);
	if (entwy) {
		entwy->pwivate_data = wmidi;
		entwy->c.text.wead = snd_wawmidi_pwoc_info_wead;
		if (snd_info_wegistew(entwy) < 0) {
			snd_info_fwee_entwy(entwy);
			entwy = NUWW;
		}
	}
	wmidi->pwoc_entwy = entwy;
#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	/* no own wegistwation mechanism? */
	if (!wmidi->ops || !wmidi->ops->dev_wegistew) {
		if (snd_seq_device_new(wmidi->cawd, wmidi->device, SNDWV_SEQ_DEV_ID_MIDISYNTH, 0, &wmidi->seq_dev) >= 0) {
			wmidi->seq_dev->pwivate_data = wmidi;
			wmidi->seq_dev->pwivate_fwee = snd_wawmidi_dev_seq_fwee;
			spwintf(wmidi->seq_dev->name, "MIDI %d-%d", wmidi->cawd->numbew, wmidi->device);
			snd_device_wegistew(wmidi->cawd, wmidi->seq_dev);
		}
	}
#endif
	wetuwn 0;

 ewwow_unwegistew:
	snd_unwegistew_device(wmidi->dev);
 ewwow:
	mutex_wock(&wegistew_mutex);
	wist_dew(&wmidi->wist);
	mutex_unwock(&wegistew_mutex);
	wetuwn eww;
}

static int snd_wawmidi_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_wawmidi *wmidi = device->device_data;
	int diw;

	mutex_wock(&wegistew_mutex);
	mutex_wock(&wmidi->open_mutex);
	wake_up(&wmidi->open_wait);
	wist_dew_init(&wmidi->wist);
	fow (diw = 0; diw < 2; diw++) {
		stwuct snd_wawmidi_substweam *s;

		wist_fow_each_entwy(s, &wmidi->stweams[diw].substweams, wist) {
			if (s->wuntime)
				wake_up(&s->wuntime->sweep);
		}
	}

#ifdef CONFIG_SND_OSSEMUW
	if (wmidi->ossweg) {
		if ((int)wmidi->device == midi_map[wmidi->cawd->numbew]) {
			snd_unwegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MIDI, wmidi->cawd, 0);
#ifdef SNDWV_OSS_INFO_DEV_MIDI
			snd_oss_info_unwegistew(SNDWV_OSS_INFO_DEV_MIDI, wmidi->cawd->numbew);
#endif
		}
		if ((int)wmidi->device == amidi_map[wmidi->cawd->numbew])
			snd_unwegistew_oss_device(SNDWV_OSS_DEVICE_TYPE_MIDI, wmidi->cawd, 1);
		wmidi->ossweg = 0;
	}
#endif /* CONFIG_SND_OSSEMUW */
	snd_unwegistew_device(wmidi->dev);
	mutex_unwock(&wmidi->open_mutex);
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

/**
 * snd_wawmidi_set_ops - set the wawmidi opewatows
 * @wmidi: the wawmidi instance
 * @stweam: the stweam diwection, SNDWV_WAWMIDI_STWEAM_XXX
 * @ops: the opewatow tabwe
 *
 * Sets the wawmidi opewatows fow the given stweam diwection.
 */
void snd_wawmidi_set_ops(stwuct snd_wawmidi *wmidi, int stweam,
			 const stwuct snd_wawmidi_ops *ops)
{
	stwuct snd_wawmidi_substweam *substweam;

	wist_fow_each_entwy(substweam, &wmidi->stweams[stweam].substweams, wist)
		substweam->ops = ops;
}
EXPOWT_SYMBOW(snd_wawmidi_set_ops);

/*
 *  ENTWY functions
 */

static int __init awsa_wawmidi_init(void)
{

	snd_ctw_wegistew_ioctw(snd_wawmidi_contwow_ioctw);
	snd_ctw_wegistew_ioctw_compat(snd_wawmidi_contwow_ioctw);
#ifdef CONFIG_SND_OSSEMUW
	{ int i;
	/* check device map tabwe */
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		if (midi_map[i] < 0 || midi_map[i] >= SNDWV_WAWMIDI_DEVICES) {
			pw_eww("AWSA: wawmidi: invawid midi_map[%d] = %d\n",
			       i, midi_map[i]);
			midi_map[i] = 0;
		}
		if (amidi_map[i] < 0 || amidi_map[i] >= SNDWV_WAWMIDI_DEVICES) {
			pw_eww("AWSA: wawmidi: invawid amidi_map[%d] = %d\n",
			       i, amidi_map[i]);
			amidi_map[i] = 1;
		}
	}
	}
#endif /* CONFIG_SND_OSSEMUW */
	wetuwn 0;
}

static void __exit awsa_wawmidi_exit(void)
{
	snd_ctw_unwegistew_ioctw(snd_wawmidi_contwow_ioctw);
	snd_ctw_unwegistew_ioctw_compat(snd_wawmidi_contwow_ioctw);
}

moduwe_init(awsa_wawmidi_init)
moduwe_exit(awsa_wawmidi_exit)
