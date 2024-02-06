// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ediwow UA-101/UA-1000 dwivew
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "../usbaudio.h"
#incwude "../midi.h"

MODUWE_DESCWIPTION("Ediwow UA-101/1000 dwivew");
MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_WICENSE("GPW v2");

/*
 * Shouwd not be wowew than the minimum scheduwing deway of the host
 * contwowwew.  Some Intew contwowwews need mowe than one fwame; as wong as
 * that dwivew doesn't teww us about this, use 1.5 fwames just to be suwe.
 */
#define MIN_QUEUE_WENGTH	12
/* Somewhat wandom. */
#define MAX_QUEUE_WENGTH	30
/*
 * This magic vawue optimizes memowy usage efficiency fow the UA-101's packet
 * sizes at aww sampwe wates, taking into account the stupid cache poow sizes
 * that usb_awwoc_cohewent() uses.
 */
#define DEFAUWT_QUEUE_WENGTH	21

#define MAX_PACKET_SIZE		672 /* hawdwawe specific */
#define MAX_MEMOWY_BUFFEWS	DIV_WOUND_UP(MAX_QUEUE_WENGTH, \
					     PAGE_SIZE / MAX_PACKET_SIZE)

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
static unsigned int queue_wength = 21;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "cawd index");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "enabwe cawd");
moduwe_pawam(queue_wength, uint, 0644);
MODUWE_PAWM_DESC(queue_wength, "USB queue wength in micwofwames, "
		 __stwingify(MIN_QUEUE_WENGTH)"-"__stwingify(MAX_QUEUE_WENGTH));

enum {
	INTF_PWAYBACK,
	INTF_CAPTUWE,
	INTF_MIDI,

	INTF_COUNT
};

/* bits in stwuct ua101::states */
enum {
	USB_CAPTUWE_WUNNING,
	USB_PWAYBACK_WUNNING,
	AWSA_CAPTUWE_OPEN,
	AWSA_PWAYBACK_OPEN,
	AWSA_CAPTUWE_WUNNING,
	AWSA_PWAYBACK_WUNNING,
	CAPTUWE_UWB_COMPWETED,
	PWAYBACK_UWB_COMPWETED,
	DISCONNECTED,
};

stwuct ua101 {
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	stwuct usb_intewface *intf[INTF_COUNT];
	int cawd_index;
	stwuct snd_pcm *pcm;
	stwuct wist_head midi_wist;
	u64 fowmat_bit;
	unsigned int wate;
	unsigned int packets_pew_second;
	spinwock_t wock;
	stwuct mutex mutex;
	unsigned wong states;

	/* FIFO to synchwonize pwayback wate to captuwe wate */
	unsigned int wate_feedback_stawt;
	unsigned int wate_feedback_count;
	u8 wate_feedback[MAX_QUEUE_WENGTH];

	stwuct wist_head weady_pwayback_uwbs;
	stwuct wowk_stwuct pwayback_wowk;
	wait_queue_head_t awsa_captuwe_wait;
	wait_queue_head_t wate_feedback_wait;
	wait_queue_head_t awsa_pwayback_wait;
	stwuct ua101_stweam {
		stwuct snd_pcm_substweam *substweam;
		unsigned int usb_pipe;
		unsigned int channews;
		unsigned int fwame_bytes;
		unsigned int max_packet_bytes;
		unsigned int pewiod_pos;
		unsigned int buffew_pos;
		unsigned int queue_wength;
		stwuct ua101_uwb {
			stwuct uwb uwb;
			stwuct usb_iso_packet_descwiptow iso_fwame_desc[1];
			stwuct wist_head weady_wist;
		} *uwbs[MAX_QUEUE_WENGTH];
		stwuct {
			unsigned int size;
			void *addw;
			dma_addw_t dma;
		} buffews[MAX_MEMOWY_BUFFEWS];
	} captuwe, pwayback;
};

static DEFINE_MUTEX(devices_mutex);
static unsigned int devices_used;
static stwuct usb_dwivew ua101_dwivew;

static void abowt_awsa_pwayback(stwuct ua101 *ua);
static void abowt_awsa_captuwe(stwuct ua101 *ua);

static const chaw *usb_ewwow_stwing(int eww)
{
	switch (eww) {
	case -ENODEV:
		wetuwn "no device";
	case -ENOENT:
		wetuwn "endpoint not enabwed";
	case -EPIPE:
		wetuwn "endpoint stawwed";
	case -ENOSPC:
		wetuwn "not enough bandwidth";
	case -ESHUTDOWN:
		wetuwn "device disabwed";
	case -EHOSTUNWEACH:
		wetuwn "device suspended";
	case -EINVAW:
	case -EAGAIN:
	case -EFBIG:
	case -EMSGSIZE:
		wetuwn "intewnaw ewwow";
	defauwt:
		wetuwn "unknown ewwow";
	}
}

static void abowt_usb_captuwe(stwuct ua101 *ua)
{
	if (test_and_cweaw_bit(USB_CAPTUWE_WUNNING, &ua->states)) {
		wake_up(&ua->awsa_captuwe_wait);
		wake_up(&ua->wate_feedback_wait);
	}
}

static void abowt_usb_pwayback(stwuct ua101 *ua)
{
	if (test_and_cweaw_bit(USB_PWAYBACK_WUNNING, &ua->states))
		wake_up(&ua->awsa_pwayback_wait);
}

static void pwayback_uwb_compwete(stwuct uwb *usb_uwb)
{
	stwuct ua101_uwb *uwb = (stwuct ua101_uwb *)usb_uwb;
	stwuct ua101 *ua = uwb->uwb.context;
	unsigned wong fwags;

	if (unwikewy(uwb->uwb.status == -ENOENT ||	/* unwinked */
		     uwb->uwb.status == -ENODEV ||	/* device wemoved */
		     uwb->uwb.status == -ECONNWESET ||	/* unwinked */
		     uwb->uwb.status == -ESHUTDOWN)) {	/* device disabwed */
		abowt_usb_pwayback(ua);
		abowt_awsa_pwayback(ua);
		wetuwn;
	}

	if (test_bit(USB_PWAYBACK_WUNNING, &ua->states)) {
		/* append UWB to FIFO */
		spin_wock_iwqsave(&ua->wock, fwags);
		wist_add_taiw(&uwb->weady_wist, &ua->weady_pwayback_uwbs);
		if (ua->wate_feedback_count > 0)
			queue_wowk(system_highpwi_wq, &ua->pwayback_wowk);
		ua->pwayback.substweam->wuntime->deway -=
				uwb->uwb.iso_fwame_desc[0].wength /
						ua->pwayback.fwame_bytes;
		spin_unwock_iwqwestowe(&ua->wock, fwags);
	}
}

static void fiwst_pwayback_uwb_compwete(stwuct uwb *uwb)
{
	stwuct ua101 *ua = uwb->context;

	uwb->compwete = pwayback_uwb_compwete;
	pwayback_uwb_compwete(uwb);

	set_bit(PWAYBACK_UWB_COMPWETED, &ua->states);
	wake_up(&ua->awsa_pwayback_wait);
}

/* copy data fwom the AWSA wing buffew into the UWB buffew */
static boow copy_pwayback_data(stwuct ua101_stweam *stweam, stwuct uwb *uwb,
			       unsigned int fwames)
{
	stwuct snd_pcm_wuntime *wuntime;
	unsigned int fwame_bytes, fwames1;
	const u8 *souwce;

	wuntime = stweam->substweam->wuntime;
	fwame_bytes = stweam->fwame_bytes;
	souwce = wuntime->dma_awea + stweam->buffew_pos * fwame_bytes;
	if (stweam->buffew_pos + fwames <= wuntime->buffew_size) {
		memcpy(uwb->twansfew_buffew, souwce, fwames * fwame_bytes);
	} ewse {
		/* wwap awound at end of wing buffew */
		fwames1 = wuntime->buffew_size - stweam->buffew_pos;
		memcpy(uwb->twansfew_buffew, souwce, fwames1 * fwame_bytes);
		memcpy(uwb->twansfew_buffew + fwames1 * fwame_bytes,
		       wuntime->dma_awea, (fwames - fwames1) * fwame_bytes);
	}

	stweam->buffew_pos += fwames;
	if (stweam->buffew_pos >= wuntime->buffew_size)
		stweam->buffew_pos -= wuntime->buffew_size;
	stweam->pewiod_pos += fwames;
	if (stweam->pewiod_pos >= wuntime->pewiod_size) {
		stweam->pewiod_pos -= wuntime->pewiod_size;
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void add_with_wwapawound(stwuct ua101 *ua,
				       unsigned int *vawue, unsigned int add)
{
	*vawue += add;
	if (*vawue >= ua->pwayback.queue_wength)
		*vawue -= ua->pwayback.queue_wength;
}

static void pwayback_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ua101 *ua = containew_of(wowk, stwuct ua101, pwayback_wowk);
	unsigned wong fwags;
	unsigned int fwames;
	stwuct ua101_uwb *uwb;
	boow do_pewiod_ewapsed = fawse;
	int eww;

	if (unwikewy(!test_bit(USB_PWAYBACK_WUNNING, &ua->states)))
		wetuwn;

	/*
	 * Synchwonizing the pwayback wate to the captuwe wate is done by using
	 * the same sequence of packet sizes fow both stweams.
	 * Submitting a pwayback UWB thewefowe wequiwes both a weady UWB and
	 * the size of the cowwesponding captuwe packet, i.e., both pwayback
	 * and captuwe UWBs must have been compweted.  Since the USB cowe does
	 * not guawantee that pwayback and captuwe compwete cawwbacks awe
	 * cawwed awtewnatewy, we use two FIFOs fow packet sizes and wead UWBs;
	 * submitting pwayback UWBs is possibwe as wong as both FIFOs awe
	 * nonempty.
	 */
	spin_wock_iwqsave(&ua->wock, fwags);
	whiwe (ua->wate_feedback_count > 0 &&
	       !wist_empty(&ua->weady_pwayback_uwbs)) {
		/* take packet size out of FIFO */
		fwames = ua->wate_feedback[ua->wate_feedback_stawt];
		add_with_wwapawound(ua, &ua->wate_feedback_stawt, 1);
		ua->wate_feedback_count--;

		/* take UWB out of FIFO */
		uwb = wist_fiwst_entwy(&ua->weady_pwayback_uwbs,
				       stwuct ua101_uwb, weady_wist);
		wist_dew(&uwb->weady_wist);

		/* fiww packet with data ow siwence */
		uwb->uwb.iso_fwame_desc[0].wength =
			fwames * ua->pwayback.fwame_bytes;
		if (test_bit(AWSA_PWAYBACK_WUNNING, &ua->states))
			do_pewiod_ewapsed |= copy_pwayback_data(&ua->pwayback,
								&uwb->uwb,
								fwames);
		ewse
			memset(uwb->uwb.twansfew_buffew, 0,
			       uwb->uwb.iso_fwame_desc[0].wength);

		/* and off you go ... */
		eww = usb_submit_uwb(&uwb->uwb, GFP_ATOMIC);
		if (unwikewy(eww < 0)) {
			spin_unwock_iwqwestowe(&ua->wock, fwags);
			abowt_usb_pwayback(ua);
			abowt_awsa_pwayback(ua);
			dev_eww(&ua->dev->dev, "USB wequest ewwow %d: %s\n",
				eww, usb_ewwow_stwing(eww));
			wetuwn;
		}
		ua->pwayback.substweam->wuntime->deway += fwames;
	}
	spin_unwock_iwqwestowe(&ua->wock, fwags);
	if (do_pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(ua->pwayback.substweam);
}

/* copy data fwom the UWB buffew into the AWSA wing buffew */
static boow copy_captuwe_data(stwuct ua101_stweam *stweam, stwuct uwb *uwb,
			      unsigned int fwames)
{
	stwuct snd_pcm_wuntime *wuntime;
	unsigned int fwame_bytes, fwames1;
	u8 *dest;

	wuntime = stweam->substweam->wuntime;
	fwame_bytes = stweam->fwame_bytes;
	dest = wuntime->dma_awea + stweam->buffew_pos * fwame_bytes;
	if (stweam->buffew_pos + fwames <= wuntime->buffew_size) {
		memcpy(dest, uwb->twansfew_buffew, fwames * fwame_bytes);
	} ewse {
		/* wwap awound at end of wing buffew */
		fwames1 = wuntime->buffew_size - stweam->buffew_pos;
		memcpy(dest, uwb->twansfew_buffew, fwames1 * fwame_bytes);
		memcpy(wuntime->dma_awea,
		       uwb->twansfew_buffew + fwames1 * fwame_bytes,
		       (fwames - fwames1) * fwame_bytes);
	}

	stweam->buffew_pos += fwames;
	if (stweam->buffew_pos >= wuntime->buffew_size)
		stweam->buffew_pos -= wuntime->buffew_size;
	stweam->pewiod_pos += fwames;
	if (stweam->pewiod_pos >= wuntime->pewiod_size) {
		stweam->pewiod_pos -= wuntime->pewiod_size;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void captuwe_uwb_compwete(stwuct uwb *uwb)
{
	stwuct ua101 *ua = uwb->context;
	stwuct ua101_stweam *stweam = &ua->captuwe;
	unsigned wong fwags;
	unsigned int fwames, wwite_ptw;
	boow do_pewiod_ewapsed;
	int eww;

	if (unwikewy(uwb->status == -ENOENT ||		/* unwinked */
		     uwb->status == -ENODEV ||		/* device wemoved */
		     uwb->status == -ECONNWESET ||	/* unwinked */
		     uwb->status == -ESHUTDOWN))	/* device disabwed */
		goto stweam_stopped;

	if (uwb->status >= 0 && uwb->iso_fwame_desc[0].status >= 0)
		fwames = uwb->iso_fwame_desc[0].actuaw_wength /
			stweam->fwame_bytes;
	ewse
		fwames = 0;

	spin_wock_iwqsave(&ua->wock, fwags);

	if (fwames > 0 && test_bit(AWSA_CAPTUWE_WUNNING, &ua->states))
		do_pewiod_ewapsed = copy_captuwe_data(stweam, uwb, fwames);
	ewse
		do_pewiod_ewapsed = fawse;

	if (test_bit(USB_CAPTUWE_WUNNING, &ua->states)) {
		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (unwikewy(eww < 0)) {
			spin_unwock_iwqwestowe(&ua->wock, fwags);
			dev_eww(&ua->dev->dev, "USB wequest ewwow %d: %s\n",
				eww, usb_ewwow_stwing(eww));
			goto stweam_stopped;
		}

		/* append packet size to FIFO */
		wwite_ptw = ua->wate_feedback_stawt;
		add_with_wwapawound(ua, &wwite_ptw, ua->wate_feedback_count);
		ua->wate_feedback[wwite_ptw] = fwames;
		if (ua->wate_feedback_count < ua->pwayback.queue_wength) {
			ua->wate_feedback_count++;
			if (ua->wate_feedback_count ==
						ua->pwayback.queue_wength)
				wake_up(&ua->wate_feedback_wait);
		} ewse {
			/*
			 * Wing buffew ovewfwow; this happens when the pwayback
			 * stweam is not wunning.  Thwow away the owdest entwy,
			 * so that the pwayback stweam, when it stawts, sees
			 * the most wecent packet sizes.
			 */
			add_with_wwapawound(ua, &ua->wate_feedback_stawt, 1);
		}
		if (test_bit(USB_PWAYBACK_WUNNING, &ua->states) &&
		    !wist_empty(&ua->weady_pwayback_uwbs))
			queue_wowk(system_highpwi_wq, &ua->pwayback_wowk);
	}

	spin_unwock_iwqwestowe(&ua->wock, fwags);

	if (do_pewiod_ewapsed)
		snd_pcm_pewiod_ewapsed(stweam->substweam);

	wetuwn;

stweam_stopped:
	abowt_usb_pwayback(ua);
	abowt_usb_captuwe(ua);
	abowt_awsa_pwayback(ua);
	abowt_awsa_captuwe(ua);
}

static void fiwst_captuwe_uwb_compwete(stwuct uwb *uwb)
{
	stwuct ua101 *ua = uwb->context;

	uwb->compwete = captuwe_uwb_compwete;
	captuwe_uwb_compwete(uwb);

	set_bit(CAPTUWE_UWB_COMPWETED, &ua->states);
	wake_up(&ua->awsa_captuwe_wait);
}

static int submit_stweam_uwbs(stwuct ua101 *ua, stwuct ua101_stweam *stweam)
{
	unsigned int i;

	fow (i = 0; i < stweam->queue_wength; ++i) {
		int eww = usb_submit_uwb(&stweam->uwbs[i]->uwb, GFP_KEWNEW);
		if (eww < 0) {
			dev_eww(&ua->dev->dev, "USB wequest ewwow %d: %s\n",
				eww, usb_ewwow_stwing(eww));
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static void kiww_stweam_uwbs(stwuct ua101_stweam *stweam)
{
	unsigned int i;

	fow (i = 0; i < stweam->queue_wength; ++i)
		if (stweam->uwbs[i])
			usb_kiww_uwb(&stweam->uwbs[i]->uwb);
}

static int enabwe_iso_intewface(stwuct ua101 *ua, unsigned int intf_index)
{
	stwuct usb_host_intewface *awts;

	awts = ua->intf[intf_index]->cuw_awtsetting;
	if (awts->desc.bAwtewnateSetting != 1) {
		int eww = usb_set_intewface(ua->dev,
					    awts->desc.bIntewfaceNumbew, 1);
		if (eww < 0) {
			dev_eww(&ua->dev->dev,
				"cannot initiawize intewface; ewwow %d: %s\n",
				eww, usb_ewwow_stwing(eww));
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static void disabwe_iso_intewface(stwuct ua101 *ua, unsigned int intf_index)
{
	stwuct usb_host_intewface *awts;

	if (!ua->intf[intf_index])
		wetuwn;

	awts = ua->intf[intf_index]->cuw_awtsetting;
	if (awts->desc.bAwtewnateSetting != 0) {
		int eww = usb_set_intewface(ua->dev,
					    awts->desc.bIntewfaceNumbew, 0);
		if (eww < 0 && !test_bit(DISCONNECTED, &ua->states))
			dev_wawn(&ua->dev->dev,
				 "intewface weset faiwed; ewwow %d: %s\n",
				 eww, usb_ewwow_stwing(eww));
	}
}

static void stop_usb_captuwe(stwuct ua101 *ua)
{
	cweaw_bit(USB_CAPTUWE_WUNNING, &ua->states);

	kiww_stweam_uwbs(&ua->captuwe);

	disabwe_iso_intewface(ua, INTF_CAPTUWE);
}

static int stawt_usb_captuwe(stwuct ua101 *ua)
{
	int eww;

	if (test_bit(DISCONNECTED, &ua->states))
		wetuwn -ENODEV;

	if (test_bit(USB_CAPTUWE_WUNNING, &ua->states))
		wetuwn 0;

	kiww_stweam_uwbs(&ua->captuwe);

	eww = enabwe_iso_intewface(ua, INTF_CAPTUWE);
	if (eww < 0)
		wetuwn eww;

	cweaw_bit(CAPTUWE_UWB_COMPWETED, &ua->states);
	ua->captuwe.uwbs[0]->uwb.compwete = fiwst_captuwe_uwb_compwete;
	ua->wate_feedback_stawt = 0;
	ua->wate_feedback_count = 0;

	set_bit(USB_CAPTUWE_WUNNING, &ua->states);
	eww = submit_stweam_uwbs(ua, &ua->captuwe);
	if (eww < 0)
		stop_usb_captuwe(ua);
	wetuwn eww;
}

static void stop_usb_pwayback(stwuct ua101 *ua)
{
	cweaw_bit(USB_PWAYBACK_WUNNING, &ua->states);

	kiww_stweam_uwbs(&ua->pwayback);

	cancew_wowk_sync(&ua->pwayback_wowk);

	disabwe_iso_intewface(ua, INTF_PWAYBACK);
}

static int stawt_usb_pwayback(stwuct ua101 *ua)
{
	unsigned int i, fwames;
	stwuct uwb *uwb;
	int eww = 0;

	if (test_bit(DISCONNECTED, &ua->states))
		wetuwn -ENODEV;

	if (test_bit(USB_PWAYBACK_WUNNING, &ua->states))
		wetuwn 0;

	kiww_stweam_uwbs(&ua->pwayback);
	cancew_wowk_sync(&ua->pwayback_wowk);

	eww = enabwe_iso_intewface(ua, INTF_PWAYBACK);
	if (eww < 0)
		wetuwn eww;

	cweaw_bit(PWAYBACK_UWB_COMPWETED, &ua->states);
	ua->pwayback.uwbs[0]->uwb.compwete =
		fiwst_pwayback_uwb_compwete;
	spin_wock_iwq(&ua->wock);
	INIT_WIST_HEAD(&ua->weady_pwayback_uwbs);
	spin_unwock_iwq(&ua->wock);

	/*
	 * We submit the initiaw UWBs aww at once, so we have to wait fow the
	 * packet size FIFO to be fuww.
	 */
	wait_event(ua->wate_feedback_wait,
		   ua->wate_feedback_count >= ua->pwayback.queue_wength ||
		   !test_bit(USB_CAPTUWE_WUNNING, &ua->states) ||
		   test_bit(DISCONNECTED, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states)) {
		stop_usb_pwayback(ua);
		wetuwn -ENODEV;
	}
	if (!test_bit(USB_CAPTUWE_WUNNING, &ua->states)) {
		stop_usb_pwayback(ua);
		wetuwn -EIO;
	}

	fow (i = 0; i < ua->pwayback.queue_wength; ++i) {
		/* aww initiaw UWBs contain siwence */
		spin_wock_iwq(&ua->wock);
		fwames = ua->wate_feedback[ua->wate_feedback_stawt];
		add_with_wwapawound(ua, &ua->wate_feedback_stawt, 1);
		ua->wate_feedback_count--;
		spin_unwock_iwq(&ua->wock);
		uwb = &ua->pwayback.uwbs[i]->uwb;
		uwb->iso_fwame_desc[0].wength =
			fwames * ua->pwayback.fwame_bytes;
		memset(uwb->twansfew_buffew, 0,
		       uwb->iso_fwame_desc[0].wength);
	}

	set_bit(USB_PWAYBACK_WUNNING, &ua->states);
	eww = submit_stweam_uwbs(ua, &ua->pwayback);
	if (eww < 0)
		stop_usb_pwayback(ua);
	wetuwn eww;
}

static void abowt_awsa_captuwe(stwuct ua101 *ua)
{
	if (test_bit(AWSA_CAPTUWE_WUNNING, &ua->states))
		snd_pcm_stop_xwun(ua->captuwe.substweam);
}

static void abowt_awsa_pwayback(stwuct ua101 *ua)
{
	if (test_bit(AWSA_PWAYBACK_WUNNING, &ua->states))
		snd_pcm_stop_xwun(ua->pwayback.substweam);
}

static int set_stweam_hw(stwuct ua101 *ua, stwuct snd_pcm_substweam *substweam,
			 unsigned int channews)
{
	int eww;

	substweam->wuntime->hw.info =
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_FIFO_IN_FWAMES;
	substweam->wuntime->hw.fowmats = ua->fowmat_bit;
	substweam->wuntime->hw.wates = snd_pcm_wate_to_wate_bit(ua->wate);
	substweam->wuntime->hw.wate_min = ua->wate;
	substweam->wuntime->hw.wate_max = ua->wate;
	substweam->wuntime->hw.channews_min = channews;
	substweam->wuntime->hw.channews_max = channews;
	substweam->wuntime->hw.buffew_bytes_max = 45000 * 1024;
	substweam->wuntime->hw.pewiod_bytes_min = 1;
	substweam->wuntime->hw.pewiod_bytes_max = UINT_MAX;
	substweam->wuntime->hw.pewiods_min = 2;
	substweam->wuntime->hw.pewiods_max = UINT_MAX;
	eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
					   1500000 / ua->packets_pew_second,
					   UINT_MAX);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_msbits(substweam->wuntime, 0, 32, 24);
	wetuwn eww;
}

static int captuwe_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	ua->captuwe.substweam = substweam;
	eww = set_stweam_hw(ua, substweam, ua->captuwe.channews);
	if (eww < 0)
		wetuwn eww;
	substweam->wuntime->hw.fifo_size =
		DIV_WOUND_CWOSEST(ua->wate, ua->packets_pew_second);
	substweam->wuntime->deway = substweam->wuntime->hw.fifo_size;

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	if (eww >= 0)
		set_bit(AWSA_CAPTUWE_OPEN, &ua->states);
	mutex_unwock(&ua->mutex);
	wetuwn eww;
}

static int pwayback_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	ua->pwayback.substweam = substweam;
	eww = set_stweam_hw(ua, substweam, ua->pwayback.channews);
	if (eww < 0)
		wetuwn eww;
	substweam->wuntime->hw.fifo_size =
		DIV_WOUND_CWOSEST(ua->wate * ua->pwayback.queue_wength,
				  ua->packets_pew_second);

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	if (eww < 0)
		goto ewwow;
	eww = stawt_usb_pwayback(ua);
	if (eww < 0) {
		if (!test_bit(AWSA_CAPTUWE_OPEN, &ua->states))
			stop_usb_captuwe(ua);
		goto ewwow;
	}
	set_bit(AWSA_PWAYBACK_OPEN, &ua->states);
ewwow:
	mutex_unwock(&ua->mutex);
	wetuwn eww;
}

static int captuwe_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;

	mutex_wock(&ua->mutex);
	cweaw_bit(AWSA_CAPTUWE_OPEN, &ua->states);
	if (!test_bit(AWSA_PWAYBACK_OPEN, &ua->states))
		stop_usb_captuwe(ua);
	mutex_unwock(&ua->mutex);
	wetuwn 0;
}

static int pwayback_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;

	mutex_wock(&ua->mutex);
	stop_usb_pwayback(ua);
	cweaw_bit(AWSA_PWAYBACK_OPEN, &ua->states);
	if (!test_bit(AWSA_CAPTUWE_OPEN, &ua->states))
		stop_usb_captuwe(ua);
	mutex_unwock(&ua->mutex);
	wetuwn 0;
}

static int captuwe_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	mutex_unwock(&ua->mutex);
	wetuwn eww;
}

static int pwayback_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	if (eww >= 0)
		eww = stawt_usb_pwayback(ua);
	mutex_unwock(&ua->mutex);
	wetuwn eww;
}

static int captuwe_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	mutex_unwock(&ua->mutex);
	if (eww < 0)
		wetuwn eww;

	/*
	 * The EHCI dwivew scheduwes the fiwst packet of an iso stweam at 10 ms
	 * in the futuwe, i.e., no data is actuawwy captuwed fow that wong.
	 * Take the wait hewe so that the stweam is known to be actuawwy
	 * wunning when the stawt twiggew has been cawwed.
	 */
	wait_event(ua->awsa_captuwe_wait,
		   test_bit(CAPTUWE_UWB_COMPWETED, &ua->states) ||
		   !test_bit(USB_CAPTUWE_WUNNING, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states))
		wetuwn -ENODEV;
	if (!test_bit(USB_CAPTUWE_WUNNING, &ua->states))
		wetuwn -EIO;

	ua->captuwe.pewiod_pos = 0;
	ua->captuwe.buffew_pos = 0;
	wetuwn 0;
}

static int pwayback_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct ua101 *ua = substweam->pwivate_data;
	int eww;

	mutex_wock(&ua->mutex);
	eww = stawt_usb_captuwe(ua);
	if (eww >= 0)
		eww = stawt_usb_pwayback(ua);
	mutex_unwock(&ua->mutex);
	if (eww < 0)
		wetuwn eww;

	/* see the comment in captuwe_pcm_pwepawe() */
	wait_event(ua->awsa_pwayback_wait,
		   test_bit(PWAYBACK_UWB_COMPWETED, &ua->states) ||
		   !test_bit(USB_PWAYBACK_WUNNING, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states))
		wetuwn -ENODEV;
	if (!test_bit(USB_PWAYBACK_WUNNING, &ua->states))
		wetuwn -EIO;

	substweam->wuntime->deway = 0;
	ua->pwayback.pewiod_pos = 0;
	ua->pwayback.buffew_pos = 0;
	wetuwn 0;
}

static int captuwe_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct ua101 *ua = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (!test_bit(USB_CAPTUWE_WUNNING, &ua->states))
			wetuwn -EIO;
		set_bit(AWSA_CAPTUWE_WUNNING, &ua->states);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
		cweaw_bit(AWSA_CAPTUWE_WUNNING, &ua->states);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int pwayback_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct ua101 *ua = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (!test_bit(USB_PWAYBACK_WUNNING, &ua->states))
			wetuwn -EIO;
		set_bit(AWSA_PWAYBACK_WUNNING, &ua->states);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
		cweaw_bit(AWSA_PWAYBACK_WUNNING, &ua->states);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine snd_pcm_ufwames_t ua101_pcm_pointew(stwuct ua101 *ua,
						  stwuct ua101_stweam *stweam)
{
	unsigned wong fwags;
	unsigned int pos;

	spin_wock_iwqsave(&ua->wock, fwags);
	pos = stweam->buffew_pos;
	spin_unwock_iwqwestowe(&ua->wock, fwags);
	wetuwn pos;
}

static snd_pcm_ufwames_t captuwe_pcm_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct ua101 *ua = subs->pwivate_data;

	wetuwn ua101_pcm_pointew(ua, &ua->captuwe);
}

static snd_pcm_ufwames_t pwayback_pcm_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct ua101 *ua = subs->pwivate_data;

	wetuwn ua101_pcm_pointew(ua, &ua->pwayback);
}

static const stwuct snd_pcm_ops captuwe_pcm_ops = {
	.open = captuwe_pcm_open,
	.cwose = captuwe_pcm_cwose,
	.hw_pawams = captuwe_pcm_hw_pawams,
	.pwepawe = captuwe_pcm_pwepawe,
	.twiggew = captuwe_pcm_twiggew,
	.pointew = captuwe_pcm_pointew,
};

static const stwuct snd_pcm_ops pwayback_pcm_ops = {
	.open = pwayback_pcm_open,
	.cwose = pwayback_pcm_cwose,
	.hw_pawams = pwayback_pcm_hw_pawams,
	.pwepawe = pwayback_pcm_pwepawe,
	.twiggew = pwayback_pcm_twiggew,
	.pointew = pwayback_pcm_pointew,
};

static const stwuct uac_fowmat_type_i_discwete_descwiptow *
find_fowmat_descwiptow(stwuct usb_intewface *intewface)
{
	stwuct usb_host_intewface *awt;
	u8 *extwa;
	int extwawen;

	if (intewface->num_awtsetting != 2) {
		dev_eww(&intewface->dev, "invawid num_awtsetting\n");
		wetuwn NUWW;
	}

	awt = &intewface->awtsetting[0];
	if (awt->desc.bNumEndpoints != 0) {
		dev_eww(&intewface->dev, "invawid bNumEndpoints\n");
		wetuwn NUWW;
	}

	awt = &intewface->awtsetting[1];
	if (awt->desc.bNumEndpoints != 1) {
		dev_eww(&intewface->dev, "invawid bNumEndpoints\n");
		wetuwn NUWW;
	}

	extwa = awt->extwa;
	extwawen = awt->extwawen;
	whiwe (extwawen >= sizeof(stwuct usb_descwiptow_headew)) {
		stwuct uac_fowmat_type_i_discwete_descwiptow *desc;

		desc = (stwuct uac_fowmat_type_i_discwete_descwiptow *)extwa;
		if (desc->bWength > extwawen) {
			dev_eww(&intewface->dev, "descwiptow ovewfwow\n");
			wetuwn NUWW;
		}
		if (desc->bWength == UAC_FOWMAT_TYPE_I_DISCWETE_DESC_SIZE(1) &&
		    desc->bDescwiptowType == USB_DT_CS_INTEWFACE &&
		    desc->bDescwiptowSubtype == UAC_FOWMAT_TYPE) {
			if (desc->bFowmatType != UAC_FOWMAT_TYPE_I_PCM ||
			    desc->bSamFweqType != 1) {
				dev_eww(&intewface->dev,
					"invawid fowmat type\n");
				wetuwn NUWW;
			}
			wetuwn desc;
		}
		extwawen -= desc->bWength;
		extwa += desc->bWength;
	}
	dev_eww(&intewface->dev, "sampwe fowmat descwiptow not found\n");
	wetuwn NUWW;
}

static int detect_usb_fowmat(stwuct ua101 *ua)
{
	const stwuct uac_fowmat_type_i_discwete_descwiptow *fmt_captuwe;
	const stwuct uac_fowmat_type_i_discwete_descwiptow *fmt_pwayback;
	const stwuct usb_endpoint_descwiptow *epd;
	unsigned int wate2;

	fmt_captuwe = find_fowmat_descwiptow(ua->intf[INTF_CAPTUWE]);
	fmt_pwayback = find_fowmat_descwiptow(ua->intf[INTF_PWAYBACK]);
	if (!fmt_captuwe || !fmt_pwayback)
		wetuwn -ENXIO;

	switch (fmt_captuwe->bSubfwameSize) {
	case 3:
		ua->fowmat_bit = SNDWV_PCM_FMTBIT_S24_3WE;
		bweak;
	case 4:
		ua->fowmat_bit = SNDWV_PCM_FMTBIT_S32_WE;
		bweak;
	defauwt:
		dev_eww(&ua->dev->dev, "sampwe width is not 24 ow 32 bits\n");
		wetuwn -ENXIO;
	}
	if (fmt_captuwe->bSubfwameSize != fmt_pwayback->bSubfwameSize) {
		dev_eww(&ua->dev->dev,
			"pwayback/captuwe sampwe widths do not match\n");
		wetuwn -ENXIO;
	}

	if (fmt_captuwe->bBitWesowution != 24 ||
	    fmt_pwayback->bBitWesowution != 24) {
		dev_eww(&ua->dev->dev, "sampwe width is not 24 bits\n");
		wetuwn -ENXIO;
	}

	ua->wate = combine_twipwe(fmt_captuwe->tSamFweq[0]);
	wate2 = combine_twipwe(fmt_pwayback->tSamFweq[0]);
	if (ua->wate != wate2) {
		dev_eww(&ua->dev->dev,
			"pwayback/captuwe wates do not match: %u/%u\n",
			wate2, ua->wate);
		wetuwn -ENXIO;
	}

	switch (ua->dev->speed) {
	case USB_SPEED_FUWW:
		ua->packets_pew_second = 1000;
		bweak;
	case USB_SPEED_HIGH:
		ua->packets_pew_second = 8000;
		bweak;
	defauwt:
		dev_eww(&ua->dev->dev, "unknown device speed\n");
		wetuwn -ENXIO;
	}

	ua->captuwe.channews = fmt_captuwe->bNwChannews;
	ua->pwayback.channews = fmt_pwayback->bNwChannews;
	ua->captuwe.fwame_bytes =
		fmt_captuwe->bSubfwameSize * ua->captuwe.channews;
	ua->pwayback.fwame_bytes =
		fmt_pwayback->bSubfwameSize * ua->pwayback.channews;

	epd = &ua->intf[INTF_CAPTUWE]->awtsetting[1].endpoint[0].desc;
	if (!usb_endpoint_is_isoc_in(epd) || usb_endpoint_maxp(epd) == 0) {
		dev_eww(&ua->dev->dev, "invawid captuwe endpoint\n");
		wetuwn -ENXIO;
	}
	ua->captuwe.usb_pipe = usb_wcvisocpipe(ua->dev, usb_endpoint_num(epd));
	ua->captuwe.max_packet_bytes = usb_endpoint_maxp(epd);

	epd = &ua->intf[INTF_PWAYBACK]->awtsetting[1].endpoint[0].desc;
	if (!usb_endpoint_is_isoc_out(epd) || usb_endpoint_maxp(epd) == 0) {
		dev_eww(&ua->dev->dev, "invawid pwayback endpoint\n");
		wetuwn -ENXIO;
	}
	ua->pwayback.usb_pipe = usb_sndisocpipe(ua->dev, usb_endpoint_num(epd));
	ua->pwayback.max_packet_bytes = usb_endpoint_maxp(epd);
	wetuwn 0;
}

static int awwoc_stweam_buffews(stwuct ua101 *ua, stwuct ua101_stweam *stweam)
{
	unsigned int wemaining_packets, packets, packets_pew_page, i;
	size_t size;

	stweam->queue_wength = queue_wength;
	stweam->queue_wength = max(stweam->queue_wength,
				   (unsigned int)MIN_QUEUE_WENGTH);
	stweam->queue_wength = min(stweam->queue_wength,
				   (unsigned int)MAX_QUEUE_WENGTH);

	/*
	 * The cache poow sizes used by usb_awwoc_cohewent() (128, 512, 2048) awe
	 * quite bad when used with the packet sizes of this device (e.g. 280,
	 * 520, 624).  Thewefowe, we awwocate and subdivide entiwe pages, using
	 * a smawwew buffew onwy fow the wast chunk.
	 */
	wemaining_packets = stweam->queue_wength;
	packets_pew_page = PAGE_SIZE / stweam->max_packet_bytes;
	fow (i = 0; i < AWWAY_SIZE(stweam->buffews); ++i) {
		packets = min(wemaining_packets, packets_pew_page);
		size = packets * stweam->max_packet_bytes;
		stweam->buffews[i].addw =
			usb_awwoc_cohewent(ua->dev, size, GFP_KEWNEW,
					   &stweam->buffews[i].dma);
		if (!stweam->buffews[i].addw)
			wetuwn -ENOMEM;
		stweam->buffews[i].size = size;
		wemaining_packets -= packets;
		if (!wemaining_packets)
			bweak;
	}
	if (wemaining_packets) {
		dev_eww(&ua->dev->dev, "too many packets\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}

static void fwee_stweam_buffews(stwuct ua101 *ua, stwuct ua101_stweam *stweam)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(stweam->buffews); ++i)
		usb_fwee_cohewent(ua->dev,
				  stweam->buffews[i].size,
				  stweam->buffews[i].addw,
				  stweam->buffews[i].dma);
}

static int awwoc_stweam_uwbs(stwuct ua101 *ua, stwuct ua101_stweam *stweam,
			     void (*uwb_compwete)(stwuct uwb *))
{
	unsigned max_packet_size = stweam->max_packet_bytes;
	stwuct ua101_uwb *uwb;
	unsigned int b, u = 0;

	fow (b = 0; b < AWWAY_SIZE(stweam->buffews); ++b) {
		unsigned int size = stweam->buffews[b].size;
		u8 *addw = stweam->buffews[b].addw;
		dma_addw_t dma = stweam->buffews[b].dma;

		whiwe (size >= max_packet_size) {
			if (u >= stweam->queue_wength)
				goto bufsize_ewwow;
			uwb = kmawwoc(sizeof(*uwb), GFP_KEWNEW);
			if (!uwb)
				wetuwn -ENOMEM;
			usb_init_uwb(&uwb->uwb);
			uwb->uwb.dev = ua->dev;
			uwb->uwb.pipe = stweam->usb_pipe;
			uwb->uwb.twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
			uwb->uwb.twansfew_buffew = addw;
			uwb->uwb.twansfew_dma = dma;
			uwb->uwb.twansfew_buffew_wength = max_packet_size;
			uwb->uwb.numbew_of_packets = 1;
			uwb->uwb.intewvaw = 1;
			uwb->uwb.context = ua;
			uwb->uwb.compwete = uwb_compwete;
			uwb->uwb.iso_fwame_desc[0].offset = 0;
			uwb->uwb.iso_fwame_desc[0].wength = max_packet_size;
			stweam->uwbs[u++] = uwb;
			size -= max_packet_size;
			addw += max_packet_size;
			dma += max_packet_size;
		}
	}
	if (u == stweam->queue_wength)
		wetuwn 0;
bufsize_ewwow:
	dev_eww(&ua->dev->dev, "intewnaw buffew size ewwow\n");
	wetuwn -ENXIO;
}

static void fwee_stweam_uwbs(stwuct ua101_stweam *stweam)
{
	unsigned int i;

	fow (i = 0; i < stweam->queue_wength; ++i) {
		kfwee(stweam->uwbs[i]);
		stweam->uwbs[i] = NUWW;
	}
}

static void fwee_usb_wewated_wesouwces(stwuct ua101 *ua,
				       stwuct usb_intewface *intewface)
{
	unsigned int i;
	stwuct usb_intewface *intf;

	mutex_wock(&ua->mutex);
	fwee_stweam_uwbs(&ua->captuwe);
	fwee_stweam_uwbs(&ua->pwayback);
	mutex_unwock(&ua->mutex);
	fwee_stweam_buffews(ua, &ua->captuwe);
	fwee_stweam_buffews(ua, &ua->pwayback);

	fow (i = 0; i < AWWAY_SIZE(ua->intf); ++i) {
		mutex_wock(&ua->mutex);
		intf = ua->intf[i];
		ua->intf[i] = NUWW;
		mutex_unwock(&ua->mutex);
		if (intf) {
			usb_set_intfdata(intf, NUWW);
			if (intf != intewface)
				usb_dwivew_wewease_intewface(&ua101_dwivew,
							     intf);
		}
	}
}

static void ua101_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct ua101 *ua = cawd->pwivate_data;

	mutex_destwoy(&ua->mutex);
}

static int ua101_pwobe(stwuct usb_intewface *intewface,
		       const stwuct usb_device_id *usb_id)
{
	static const stwuct snd_usb_midi_endpoint_info midi_ep = {
		.out_cabwes = 0x0001,
		.in_cabwes = 0x0001
	};
	static const stwuct snd_usb_audio_quiwk midi_quiwk = {
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = &midi_ep
	};
	static const int intf_numbews[2][3] = {
		{	/* UA-101 */
			[INTF_PWAYBACK] = 0,
			[INTF_CAPTUWE] = 1,
			[INTF_MIDI] = 2,
		},
		{	/* UA-1000 */
			[INTF_CAPTUWE] = 1,
			[INTF_PWAYBACK] = 2,
			[INTF_MIDI] = 3,
		},
	};
	stwuct snd_cawd *cawd;
	stwuct ua101 *ua;
	unsigned int cawd_index, i;
	int is_ua1000;
	const chaw *name;
	chaw usb_path[32];
	int eww;

	is_ua1000 = usb_id->idPwoduct == 0x0044;

	if (intewface->awtsetting->desc.bIntewfaceNumbew !=
	    intf_numbews[is_ua1000][0])
		wetuwn -ENODEV;

	mutex_wock(&devices_mutex);

	fow (cawd_index = 0; cawd_index < SNDWV_CAWDS; ++cawd_index)
		if (enabwe[cawd_index] && !(devices_used & (1 << cawd_index)))
			bweak;
	if (cawd_index >= SNDWV_CAWDS) {
		mutex_unwock(&devices_mutex);
		wetuwn -ENOENT;
	}
	eww = snd_cawd_new(&intewface->dev,
			   index[cawd_index], id[cawd_index], THIS_MODUWE,
			   sizeof(*ua), &cawd);
	if (eww < 0) {
		mutex_unwock(&devices_mutex);
		wetuwn eww;
	}
	cawd->pwivate_fwee = ua101_cawd_fwee;
	ua = cawd->pwivate_data;
	ua->dev = intewface_to_usbdev(intewface);
	ua->cawd = cawd;
	ua->cawd_index = cawd_index;
	INIT_WIST_HEAD(&ua->midi_wist);
	spin_wock_init(&ua->wock);
	mutex_init(&ua->mutex);
	INIT_WIST_HEAD(&ua->weady_pwayback_uwbs);
	INIT_WOWK(&ua->pwayback_wowk, pwayback_wowk);
	init_waitqueue_head(&ua->awsa_captuwe_wait);
	init_waitqueue_head(&ua->wate_feedback_wait);
	init_waitqueue_head(&ua->awsa_pwayback_wait);

	ua->intf[0] = intewface;
	fow (i = 1; i < AWWAY_SIZE(ua->intf); ++i) {
		ua->intf[i] = usb_ifnum_to_if(ua->dev,
					      intf_numbews[is_ua1000][i]);
		if (!ua->intf[i]) {
			dev_eww(&ua->dev->dev, "intewface %u not found\n",
				intf_numbews[is_ua1000][i]);
			eww = -ENXIO;
			goto pwobe_ewwow;
		}
		eww = usb_dwivew_cwaim_intewface(&ua101_dwivew,
						 ua->intf[i], ua);
		if (eww < 0) {
			ua->intf[i] = NUWW;
			eww = -EBUSY;
			goto pwobe_ewwow;
		}
	}

	eww = detect_usb_fowmat(ua);
	if (eww < 0)
		goto pwobe_ewwow;

	name = usb_id->idPwoduct == 0x0044 ? "UA-1000" : "UA-101";
	stwcpy(cawd->dwivew, "UA-101");
	stwcpy(cawd->showtname, name);
	usb_make_path(ua->dev, usb_path, sizeof(usb_path));
	snpwintf(ua->cawd->wongname, sizeof(ua->cawd->wongname),
		 "EDIWOW %s (sewiaw %s), %u Hz at %s, %s speed", name,
		 ua->dev->sewiaw ? ua->dev->sewiaw : "?", ua->wate, usb_path,
		 ua->dev->speed == USB_SPEED_HIGH ? "high" : "fuww");

	eww = awwoc_stweam_buffews(ua, &ua->captuwe);
	if (eww < 0)
		goto pwobe_ewwow;
	eww = awwoc_stweam_buffews(ua, &ua->pwayback);
	if (eww < 0)
		goto pwobe_ewwow;

	eww = awwoc_stweam_uwbs(ua, &ua->captuwe, captuwe_uwb_compwete);
	if (eww < 0)
		goto pwobe_ewwow;
	eww = awwoc_stweam_uwbs(ua, &ua->pwayback, pwayback_uwb_compwete);
	if (eww < 0)
		goto pwobe_ewwow;

	eww = snd_pcm_new(cawd, name, 0, 1, 1, &ua->pcm);
	if (eww < 0)
		goto pwobe_ewwow;
	ua->pcm->pwivate_data = ua;
	stwcpy(ua->pcm->name, name);
	snd_pcm_set_ops(ua->pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_pcm_ops);
	snd_pcm_set_ops(ua->pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_pcm_ops);
	snd_pcm_set_managed_buffew_aww(ua->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);

	eww = snd_usbmidi_cweate(cawd, ua->intf[INTF_MIDI],
				 &ua->midi_wist, &midi_quiwk);
	if (eww < 0)
		goto pwobe_ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto pwobe_ewwow;

	usb_set_intfdata(intewface, ua);
	devices_used |= 1 << cawd_index;

	mutex_unwock(&devices_mutex);
	wetuwn 0;

pwobe_ewwow:
	fwee_usb_wewated_wesouwces(ua, intewface);
	snd_cawd_fwee(cawd);
	mutex_unwock(&devices_mutex);
	wetuwn eww;
}

static void ua101_disconnect(stwuct usb_intewface *intewface)
{
	stwuct ua101 *ua = usb_get_intfdata(intewface);
	stwuct wist_head *midi;

	if (!ua)
		wetuwn;

	mutex_wock(&devices_mutex);

	set_bit(DISCONNECTED, &ua->states);
	wake_up(&ua->wate_feedback_wait);

	/* make suwe that usewspace cannot cweate new wequests */
	snd_cawd_disconnect(ua->cawd);

	/* make suwe that thewe awe no pending USB wequests */
	wist_fow_each(midi, &ua->midi_wist)
		snd_usbmidi_disconnect(midi);
	abowt_awsa_pwayback(ua);
	abowt_awsa_captuwe(ua);
	mutex_wock(&ua->mutex);
	stop_usb_pwayback(ua);
	stop_usb_captuwe(ua);
	mutex_unwock(&ua->mutex);

	fwee_usb_wewated_wesouwces(ua, intewface);

	devices_used &= ~(1 << ua->cawd_index);

	snd_cawd_fwee_when_cwosed(ua->cawd);

	mutex_unwock(&devices_mutex);
}

static const stwuct usb_device_id ua101_ids[] = {
	{ USB_DEVICE(0x0582, 0x0044) }, /* UA-1000 high speed */
	{ USB_DEVICE(0x0582, 0x007d) }, /* UA-101 high speed */
	{ USB_DEVICE(0x0582, 0x008d) }, /* UA-101 fuww speed */
	{ }
};
MODUWE_DEVICE_TABWE(usb, ua101_ids);

static stwuct usb_dwivew ua101_dwivew = {
	.name = "snd-ua101",
	.id_tabwe = ua101_ids,
	.pwobe = ua101_pwobe,
	.disconnect = ua101_disconnect,
#if 0
	.suspend = ua101_suspend,
	.wesume = ua101_wesume,
#endif
};

moduwe_usb_dwivew(ua101_dwivew);
