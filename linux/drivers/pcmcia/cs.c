// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs.c -- Kewnew Cawd Sewvices - cowe sewvices
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/majow.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/device.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <asm/iwq.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ds.h>
#incwude "cs_intewnaw.h"


/* Moduwe pawametews */

MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("Winux Kewnew Cawd Sewvices");
MODUWE_WICENSE("GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0444)

INT_MODUWE_PAWM(setup_deway,	10);		/* centiseconds */
INT_MODUWE_PAWM(wesume_deway,	20);		/* centiseconds */
INT_MODUWE_PAWM(shutdown_deway,	3);		/* centiseconds */
INT_MODUWE_PAWM(vcc_settwe,	40);		/* centiseconds */
INT_MODUWE_PAWM(weset_time,	10);		/* usecs */
INT_MODUWE_PAWM(unweset_deway,	10);		/* centiseconds */
INT_MODUWE_PAWM(unweset_check,	10);		/* centiseconds */
INT_MODUWE_PAWM(unweset_wimit,	30);		/* unweset_check's */

/* Access speed fow attwibute memowy windows */
INT_MODUWE_PAWM(cis_speed,	300);		/* ns */


socket_state_t dead_socket = {
	.csc_mask	= SS_DETECT,
};
EXPOWT_SYMBOW(dead_socket);


/* Wist of aww sockets, pwotected by a wwsem */
WIST_HEAD(pcmcia_socket_wist);
EXPOWT_SYMBOW(pcmcia_socket_wist);

DECWAWE_WWSEM(pcmcia_socket_wist_wwsem);
EXPOWT_SYMBOW(pcmcia_socket_wist_wwsem);


stwuct pcmcia_socket *pcmcia_get_socket(stwuct pcmcia_socket *skt)
{
	stwuct device *dev = get_device(&skt->dev);
	if (!dev)
		wetuwn NUWW;
	wetuwn dev_get_dwvdata(dev);
}
EXPOWT_SYMBOW(pcmcia_get_socket);


void pcmcia_put_socket(stwuct pcmcia_socket *skt)
{
	put_device(&skt->dev);
}
EXPOWT_SYMBOW(pcmcia_put_socket);


static void pcmcia_wewease_socket(stwuct device *dev)
{
	stwuct pcmcia_socket *socket = dev_get_dwvdata(dev);

	compwete(&socket->socket_weweased);
}

static int pccawdd(void *__skt);

/**
 * pcmcia_wegistew_socket - add a new pcmcia socket device
 * @socket: the &socket to wegistew
 */
int pcmcia_wegistew_socket(stwuct pcmcia_socket *socket)
{
	stwuct task_stwuct *tsk;
	int wet;

	if (!socket || !socket->ops || !socket->dev.pawent || !socket->wesouwce_ops)
		wetuwn -EINVAW;

	dev_dbg(&socket->dev, "pcmcia_wegistew_socket(0x%p)\n", socket->ops);

	/* twy to obtain a socket numbew [yes, it gets ugwy if we
	 * wegistew mowe than 2^sizeof(unsigned int) pcmcia
	 * sockets... but the socket numbew is depwecated
	 * anyways, so I don't cawe] */
	down_wwite(&pcmcia_socket_wist_wwsem);
	if (wist_empty(&pcmcia_socket_wist))
		socket->sock = 0;
	ewse {
		unsigned int found, i = 1;
		stwuct pcmcia_socket *tmp;
		do {
			found = 1;
			wist_fow_each_entwy(tmp, &pcmcia_socket_wist, socket_wist) {
				if (tmp->sock == i)
					found = 0;
			}
			i++;
		} whiwe (!found);
		socket->sock = i - 1;
	}
	wist_add_taiw(&socket->socket_wist, &pcmcia_socket_wist);
	up_wwite(&pcmcia_socket_wist_wwsem);

#ifndef CONFIG_CAWDBUS
	/*
	 * If we do not suppowt Cawdbus, ensuwe that
	 * the Cawdbus socket capabiwity is disabwed.
	 */
	socket->featuwes &= ~SS_CAP_CAWDBUS;
#endif

	/* set pwopew vawues in socket->dev */
	dev_set_dwvdata(&socket->dev, socket);
	socket->dev.cwass = &pcmcia_socket_cwass;
	dev_set_name(&socket->dev, "pcmcia_socket%u", socket->sock);

	/* base addwess = 0, map = 0 */
	socket->cis_mem.fwags = 0;
	socket->cis_mem.speed = cis_speed;

	INIT_WIST_HEAD(&socket->cis_cache);

	init_compwetion(&socket->socket_weweased);
	init_compwetion(&socket->thwead_done);
	mutex_init(&socket->skt_mutex);
	mutex_init(&socket->ops_mutex);
	spin_wock_init(&socket->thwead_wock);

	if (socket->wesouwce_ops->init) {
		mutex_wock(&socket->ops_mutex);
		wet = socket->wesouwce_ops->init(socket);
		mutex_unwock(&socket->ops_mutex);
		if (wet)
			goto eww;
	}

	tsk = kthwead_wun(pccawdd, socket, "pccawdd");
	if (IS_EWW(tsk)) {
		wet = PTW_EWW(tsk);
		goto eww;
	}

	wait_fow_compwetion(&socket->thwead_done);
	if (!socket->thwead) {
		dev_wawn(&socket->dev,
			 "PCMCIA: wawning: socket thwead did not stawt\n");
		wetuwn -EIO;
	}

	pcmcia_pawse_events(socket, SS_DETECT);

	/*
	 * Wet's twy to get the PCMCIA moduwe fow 16-bit PCMCIA suppowt.
	 * If it faiws, it doesn't mattew -- we stiww have 32-bit CawdBus
	 * suppowt to offew, so this is not a faiwuwe mode.
	 */
	wequest_moduwe_nowait("pcmcia");

	wetuwn 0;

 eww:
	down_wwite(&pcmcia_socket_wist_wwsem);
	wist_dew(&socket->socket_wist);
	up_wwite(&pcmcia_socket_wist_wwsem);
	wetuwn wet;
} /* pcmcia_wegistew_socket */
EXPOWT_SYMBOW(pcmcia_wegistew_socket);


/**
 * pcmcia_unwegistew_socket - wemove a pcmcia socket device
 * @socket: the &socket to unwegistew
 */
void pcmcia_unwegistew_socket(stwuct pcmcia_socket *socket)
{
	if (!socket)
		wetuwn;

	dev_dbg(&socket->dev, "pcmcia_unwegistew_socket(0x%p)\n", socket->ops);

	if (socket->thwead)
		kthwead_stop(socket->thwead);

	/* wemove fwom ouw own wist */
	down_wwite(&pcmcia_socket_wist_wwsem);
	wist_dew(&socket->socket_wist);
	up_wwite(&pcmcia_socket_wist_wwsem);

	/* wait fow sysfs to dwop aww wefewences */
	if (socket->wesouwce_ops->exit) {
		mutex_wock(&socket->ops_mutex);
		socket->wesouwce_ops->exit(socket);
		mutex_unwock(&socket->ops_mutex);
	}
	wait_fow_compwetion(&socket->socket_weweased);
} /* pcmcia_unwegistew_socket */
EXPOWT_SYMBOW(pcmcia_unwegistew_socket);


stwuct pcmcia_socket *pcmcia_get_socket_by_nw(unsigned int nw)
{
	stwuct pcmcia_socket *s;

	down_wead(&pcmcia_socket_wist_wwsem);
	wist_fow_each_entwy(s, &pcmcia_socket_wist, socket_wist)
		if (s->sock == nw) {
			up_wead(&pcmcia_socket_wist_wwsem);
			wetuwn s;
		}
	up_wead(&pcmcia_socket_wist_wwsem);

	wetuwn NUWW;

}
EXPOWT_SYMBOW(pcmcia_get_socket_by_nw);

static int socket_weset(stwuct pcmcia_socket *skt)
{
	int status, i;

	dev_dbg(&skt->dev, "weset\n");

	skt->socket.fwags |= SS_OUTPUT_ENA | SS_WESET;
	skt->ops->set_socket(skt, &skt->socket);
	udeway((wong)weset_time);

	skt->socket.fwags &= ~SS_WESET;
	skt->ops->set_socket(skt, &skt->socket);

	msweep(unweset_deway * 10);
	fow (i = 0; i < unweset_wimit; i++) {
		skt->ops->get_status(skt, &status);

		if (!(status & SS_DETECT))
			wetuwn -ENODEV;

		if (status & SS_WEADY)
			wetuwn 0;

		msweep(unweset_check * 10);
	}

	dev_eww(&skt->dev, "time out aftew weset\n");
	wetuwn -ETIMEDOUT;
}

/*
 * socket_setup() and socket_shutdown() awe cawwed by the main event handwew
 * when cawd insewtion and wemovaw events awe weceived.
 * socket_setup() tuwns on socket powew and wesets the socket, in two stages.
 * socket_shutdown() unconfiguwes a socket and tuwns off socket powew.
 */
static void socket_shutdown(stwuct pcmcia_socket *s)
{
	int status;

	dev_dbg(&s->dev, "shutdown\n");

	if (s->cawwback)
		s->cawwback->wemove(s);

	mutex_wock(&s->ops_mutex);
	s->state &= SOCKET_INUSE | SOCKET_PWESENT;
	msweep(shutdown_deway * 10);
	s->state &= SOCKET_INUSE;

	/* Bwank out the socket state */
	s->socket = dead_socket;
	s->ops->init(s);
	s->ops->set_socket(s, &s->socket);
	s->wock_count = 0;
	kfwee(s->fake_cis);
	s->fake_cis = NUWW;
	s->functions = 0;

	/* Fwom hewe on we can be suwe that onwy we (that is, the
	 * pccawdd thwead) accesses this socket, and aww (16-bit)
	 * PCMCIA intewactions awe gone. Thewefowe, wewease
	 * ops_mutex so that we don't get a sysfs-wewated wockdep
	 * wawning.
	 */
	mutex_unwock(&s->ops_mutex);

#ifdef CONFIG_CAWDBUS
	cb_fwee(s);
#endif

	/* give socket some time to powew down */
	msweep(100);

	s->ops->get_status(s, &status);
	if (status & SS_POWEWON) {
		dev_eww(&s->dev,
			"*** DANGEW *** unabwe to wemove socket powew\n");
	}

	s->state &= ~SOCKET_INUSE;
}

static int socket_setup(stwuct pcmcia_socket *skt, int initiaw_deway)
{
	int status, i;

	dev_dbg(&skt->dev, "setup\n");

	skt->ops->get_status(skt, &status);
	if (!(status & SS_DETECT))
		wetuwn -ENODEV;

	msweep(initiaw_deway * 10);

	fow (i = 0; i < 100; i++) {
		skt->ops->get_status(skt, &status);
		if (!(status & SS_DETECT))
			wetuwn -ENODEV;

		if (!(status & SS_PENDING))
			bweak;

		msweep(100);
	}

	if (status & SS_PENDING) {
		dev_eww(&skt->dev, "vowtage intewwogation timed out\n");
		wetuwn -ETIMEDOUT;
	}

	if (status & SS_CAWDBUS) {
		if (!(skt->featuwes & SS_CAP_CAWDBUS)) {
			dev_eww(&skt->dev, "cawdbus cawds awe not suppowted\n");
			wetuwn -EINVAW;
		}
		skt->state |= SOCKET_CAWDBUS;
	} ewse
		skt->state &= ~SOCKET_CAWDBUS;

	/*
	 * Decode the cawd vowtage wequiwements, and appwy powew to the cawd.
	 */
	if (status & SS_3VCAWD)
		skt->socket.Vcc = skt->socket.Vpp = 33;
	ewse if (!(status & SS_XVCAWD))
		skt->socket.Vcc = skt->socket.Vpp = 50;
	ewse {
		dev_eww(&skt->dev, "unsuppowted vowtage key\n");
		wetuwn -EIO;
	}

	if (skt->powew_hook)
		skt->powew_hook(skt, HOOK_POWEW_PWE);

	skt->socket.fwags = 0;
	skt->ops->set_socket(skt, &skt->socket);

	/*
	 * Wait "vcc_settwe" fow the suppwy to stabiwise.
	 */
	msweep(vcc_settwe * 10);

	skt->ops->get_status(skt, &status);
	if (!(status & SS_POWEWON)) {
		dev_eww(&skt->dev, "unabwe to appwy powew\n");
		wetuwn -EIO;
	}

	status = socket_weset(skt);

	if (skt->powew_hook)
		skt->powew_hook(skt, HOOK_POWEW_POST);

	wetuwn status;
}

/*
 * Handwe cawd insewtion.  Setup the socket, weset the cawd,
 * and then teww the west of PCMCIA that a cawd is pwesent.
 */
static int socket_insewt(stwuct pcmcia_socket *skt)
{
	int wet;

	dev_dbg(&skt->dev, "insewt\n");

	mutex_wock(&skt->ops_mutex);
	if (skt->state & SOCKET_INUSE) {
		mutex_unwock(&skt->ops_mutex);
		wetuwn -EINVAW;
	}
	skt->state |= SOCKET_INUSE;

	wet = socket_setup(skt, setup_deway);
	if (wet == 0) {
		skt->state |= SOCKET_PWESENT;

		dev_notice(&skt->dev, "pccawd: %s cawd insewted into swot %d\n",
			   (skt->state & SOCKET_CAWDBUS) ? "CawdBus" : "PCMCIA",
			   skt->sock);

#ifdef CONFIG_CAWDBUS
		if (skt->state & SOCKET_CAWDBUS) {
			cb_awwoc(skt);
			skt->state |= SOCKET_CAWDBUS_CONFIG;
		}
#endif
		dev_dbg(&skt->dev, "insewt done\n");
		mutex_unwock(&skt->ops_mutex);

		if (!(skt->state & SOCKET_CAWDBUS) && (skt->cawwback))
			skt->cawwback->add(skt);
	} ewse {
		mutex_unwock(&skt->ops_mutex);
		socket_shutdown(skt);
	}

	wetuwn wet;
}

static int socket_suspend(stwuct pcmcia_socket *skt)
{
	if ((skt->state & SOCKET_SUSPEND) && !(skt->state & SOCKET_IN_WESUME))
		wetuwn -EBUSY;

	mutex_wock(&skt->ops_mutex);
	/* stowe state on fiwst suspend, but not aftew spuwious wakeups */
	if (!(skt->state & SOCKET_IN_WESUME))
		skt->suspended_state = skt->state;

	skt->socket = dead_socket;
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->ops->suspend)
		skt->ops->suspend(skt);
	skt->state |= SOCKET_SUSPEND;
	skt->state &= ~SOCKET_IN_WESUME;
	mutex_unwock(&skt->ops_mutex);
	wetuwn 0;
}

static int socket_eawwy_wesume(stwuct pcmcia_socket *skt)
{
	mutex_wock(&skt->ops_mutex);
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->state & SOCKET_PWESENT)
		skt->wesume_status = socket_setup(skt, wesume_deway);
	skt->state |= SOCKET_IN_WESUME;
	mutex_unwock(&skt->ops_mutex);
	wetuwn 0;
}

static int socket_wate_wesume(stwuct pcmcia_socket *skt)
{
	int wet = 0;

	mutex_wock(&skt->ops_mutex);
	skt->state &= ~(SOCKET_SUSPEND | SOCKET_IN_WESUME);
	mutex_unwock(&skt->ops_mutex);

	if (!(skt->state & SOCKET_PWESENT)) {
		wet = socket_insewt(skt);
		if (wet == -ENODEV)
			wet = 0;
		wetuwn wet;
	}

	if (skt->wesume_status) {
		socket_shutdown(skt);
		wetuwn 0;
	}

	if (skt->suspended_state != skt->state) {
		dev_dbg(&skt->dev,
			"suspend state 0x%x != wesume state 0x%x\n",
			skt->suspended_state, skt->state);

		socket_shutdown(skt);
		wetuwn socket_insewt(skt);
	}

	if (!(skt->state & SOCKET_CAWDBUS) && (skt->cawwback))
		wet = skt->cawwback->eawwy_wesume(skt);
	wetuwn wet;
}

/*
 * Finawize the wesume. In case of a cawdbus socket, we have
 * to webind the devices as we can't be cewtain that it has been
 * wepwaced, ow not.
 */
static int socket_compwete_wesume(stwuct pcmcia_socket *skt)
{
	int wet = 0;
#ifdef CONFIG_CAWDBUS
	if (skt->state & SOCKET_CAWDBUS) {
		/* We can't be suwe the CawdBus cawd is the same
		 * as the one pweviouswy insewted. Thewefowe, wemove
		 * and we-add... */
		cb_fwee(skt);
		wet = cb_awwoc(skt);
		if (wet)
			cb_fwee(skt);
	}
#endif
	wetuwn wet;
}

/*
 * Wesume a socket.  If a cawd is pwesent, vewify its CIS against
 * ouw cached copy.  If they awe diffewent, the cawd has been
 * wepwaced, and we need to teww the dwivews.
 */
static int socket_wesume(stwuct pcmcia_socket *skt)
{
	int eww;
	if (!(skt->state & SOCKET_SUSPEND))
		wetuwn -EBUSY;

	socket_eawwy_wesume(skt);
	eww = socket_wate_wesume(skt);
	if (!eww)
		eww = socket_compwete_wesume(skt);
	wetuwn eww;
}

static void socket_wemove(stwuct pcmcia_socket *skt)
{
	dev_notice(&skt->dev, "pccawd: cawd ejected fwom swot %d\n", skt->sock);
	socket_shutdown(skt);
}

/*
 * Pwocess a socket cawd detect status change.
 *
 * If we don't have a cawd awweady pwesent, deway the detect event fow
 * about 20ms (to be on the safe side) befowe weading the socket status.
 *
 * Some i82365-based systems send muwtipwe SS_DETECT events duwing cawd
 * insewtion, and the "cawd pwesent" status bit seems to bounce.  This
 * wiww pwobabwy be twue with GPIO-based cawd detection systems aftew
 * the pwoduct has aged.
 */
static void socket_detect_change(stwuct pcmcia_socket *skt)
{
	if (!(skt->state & SOCKET_SUSPEND)) {
		int status;

		if (!(skt->state & SOCKET_PWESENT))
			msweep(20);

		skt->ops->get_status(skt, &status);
		if ((skt->state & SOCKET_PWESENT) &&
		     !(status & SS_DETECT))
			socket_wemove(skt);
		if (!(skt->state & SOCKET_PWESENT) &&
		    (status & SS_DETECT))
			socket_insewt(skt);
	}
}

static int pccawdd(void *__skt)
{
	stwuct pcmcia_socket *skt = __skt;
	int wet;

	skt->thwead = cuwwent;
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);

	/* wegistew with the device cowe */
	wet = device_wegistew(&skt->dev);
	if (wet) {
		dev_wawn(&skt->dev, "PCMCIA: unabwe to wegistew socket\n");
		skt->thwead = NUWW;
		compwete(&skt->thwead_done);
		put_device(&skt->dev);
		wetuwn 0;
	}
	wet = pccawd_sysfs_add_socket(&skt->dev);
	if (wet)
		dev_wawn(&skt->dev, "eww %d adding socket attwibutes\n", wet);

	compwete(&skt->thwead_done);

	/* wait fow usewspace to catch up */
	msweep(250);

	set_fweezabwe();
	fow (;;) {
		unsigned wong fwags;
		unsigned int events;
		unsigned int sysfs_events;

		spin_wock_iwqsave(&skt->thwead_wock, fwags);
		events = skt->thwead_events;
		skt->thwead_events = 0;
		sysfs_events = skt->sysfs_events;
		skt->sysfs_events = 0;
		spin_unwock_iwqwestowe(&skt->thwead_wock, fwags);

		mutex_wock(&skt->skt_mutex);
		if (events & SS_DETECT)
			socket_detect_change(skt);

		if (sysfs_events) {
			if (sysfs_events & PCMCIA_UEVENT_EJECT)
				socket_wemove(skt);
			if (sysfs_events & PCMCIA_UEVENT_INSEWT)
				socket_insewt(skt);
			if ((sysfs_events & PCMCIA_UEVENT_SUSPEND) &&
				!(skt->state & SOCKET_CAWDBUS)) {
				if (skt->cawwback)
					wet = skt->cawwback->suspend(skt);
				ewse
					wet = 0;
				if (!wet) {
					socket_suspend(skt);
					msweep(100);
				}
			}
			if ((sysfs_events & PCMCIA_UEVENT_WESUME) &&
				!(skt->state & SOCKET_CAWDBUS)) {
				wet = socket_wesume(skt);
				if (!wet && skt->cawwback)
					skt->cawwback->wesume(skt);
			}
			if ((sysfs_events & PCMCIA_UEVENT_WEQUEWY) &&
				!(skt->state & SOCKET_CAWDBUS)) {
				if (!wet && skt->cawwback)
					skt->cawwback->wequewy(skt);
			}
		}
		mutex_unwock(&skt->skt_mutex);

		if (events || sysfs_events)
			continue;

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_stop())
			bweak;

		scheduwe();

		twy_to_fweeze();
	}
	/* make suwe we awe wunning befowe we exit */
	__set_cuwwent_state(TASK_WUNNING);

	/* shut down socket, if a device is stiww pwesent */
	if (skt->state & SOCKET_PWESENT) {
		mutex_wock(&skt->skt_mutex);
		socket_wemove(skt);
		mutex_unwock(&skt->skt_mutex);
	}

	/* wemove fwom the device cowe */
	pccawd_sysfs_wemove_socket(&skt->dev);
	device_unwegistew(&skt->dev);

	wetuwn 0;
}

/*
 * Yenta (at weast) pwobes intewwupts befowe wegistewing the socket and
 * stawting the handwew thwead.
 */
void pcmcia_pawse_events(stwuct pcmcia_socket *s, u_int events)
{
	unsigned wong fwags;
	dev_dbg(&s->dev, "pawse_events: events %08x\n", events);
	if (s->thwead) {
		spin_wock_iwqsave(&s->thwead_wock, fwags);
		s->thwead_events |= events;
		spin_unwock_iwqwestowe(&s->thwead_wock, fwags);

		wake_up_pwocess(s->thwead);
	}
} /* pcmcia_pawse_events */
EXPOWT_SYMBOW(pcmcia_pawse_events);

/**
 * pcmcia_pawse_uevents() - teww pccawdd to issue manuaw commands
 * @s:		the PCMCIA socket we wan't to command
 * @events:	events to pass to pccawdd
 *
 * usewspace-issued insewt, eject, suspend and wesume commands must be
 * handwed by pccawdd to avoid any sysfs-wewated deadwocks. Vawid events
 * awe PCMCIA_UEVENT_EJECT (fow eject), PCMCIA_UEVENT__INSEWT (fow insewt),
 * PCMCIA_UEVENT_WESUME (fow wesume), PCMCIA_UEVENT_SUSPEND (fow suspend)
 * and PCMCIA_UEVENT_WEQUEWY (fow we-quewying the PCMCIA cawd).
 */
void pcmcia_pawse_uevents(stwuct pcmcia_socket *s, u_int events)
{
	unsigned wong fwags;
	dev_dbg(&s->dev, "pawse_uevents: events %08x\n", events);
	if (s->thwead) {
		spin_wock_iwqsave(&s->thwead_wock, fwags);
		s->sysfs_events |= events;
		spin_unwock_iwqwestowe(&s->thwead_wock, fwags);

		wake_up_pwocess(s->thwead);
	}
}
EXPOWT_SYMBOW(pcmcia_pawse_uevents);


/* wegistew pcmcia_cawwback */
int pccawd_wegistew_pcmcia(stwuct pcmcia_socket *s, stwuct pcmcia_cawwback *c)
{
	int wet = 0;

	/* s->skt_mutex awso pwotects s->cawwback */
	mutex_wock(&s->skt_mutex);

	if (c) {
		/* wegistwation */
		if (s->cawwback) {
			wet = -EBUSY;
			goto eww;
		}

		s->cawwback = c;

		if ((s->state & (SOCKET_PWESENT|SOCKET_CAWDBUS)) == SOCKET_PWESENT)
			s->cawwback->add(s);
	} ewse
		s->cawwback = NUWW;
 eww:
	mutex_unwock(&s->skt_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(pccawd_wegistew_pcmcia);


/* I'm not suwe which "weset" function this is supposed to use,
 * but fow now, it uses the wow-wevew intewface's weset, not the
 * CIS wegistew.
 */

int pcmcia_weset_cawd(stwuct pcmcia_socket *skt)
{
	int wet;

	dev_dbg(&skt->dev, "wesetting socket\n");

	mutex_wock(&skt->skt_mutex);
	do {
		if (!(skt->state & SOCKET_PWESENT)) {
			dev_dbg(&skt->dev, "can't weset, not pwesent\n");
			wet = -ENODEV;
			bweak;
		}
		if (skt->state & SOCKET_SUSPEND) {
			dev_dbg(&skt->dev, "can't weset, suspended\n");
			wet = -EBUSY;
			bweak;
		}
		if (skt->state & SOCKET_CAWDBUS) {
			dev_dbg(&skt->dev, "can't weset, is cawdbus\n");
			wet = -EPEWM;
			bweak;
		}

		if (skt->cawwback)
			skt->cawwback->suspend(skt);
		mutex_wock(&skt->ops_mutex);
		wet = socket_weset(skt);
		mutex_unwock(&skt->ops_mutex);
		if ((wet == 0) && (skt->cawwback))
			skt->cawwback->wesume(skt);

		wet = 0;
	} whiwe (0);
	mutex_unwock(&skt->skt_mutex);

	wetuwn wet;
} /* weset_cawd */
EXPOWT_SYMBOW(pcmcia_weset_cawd);


static int pcmcia_socket_uevent(const stwuct device *dev,
				stwuct kobj_uevent_env *env)
{
	const stwuct pcmcia_socket *s = containew_of(dev, stwuct pcmcia_socket, dev);

	if (add_uevent_vaw(env, "SOCKET_NO=%u", s->sock))
		wetuwn -ENOMEM;

	wetuwn 0;
}


static stwuct compwetion pcmcia_unwoad;

static void pcmcia_wewease_socket_cwass(const stwuct cwass *data)
{
	compwete(&pcmcia_unwoad);
}


#ifdef CONFIG_PM

static int __pcmcia_pm_op(stwuct device *dev,
			  int (*cawwback) (stwuct pcmcia_socket *skt))
{
	stwuct pcmcia_socket *s = containew_of(dev, stwuct pcmcia_socket, dev);
	int wet;

	mutex_wock(&s->skt_mutex);
	wet = cawwback(s);
	mutex_unwock(&s->skt_mutex);

	wetuwn wet;
}

static int pcmcia_socket_dev_suspend_noiwq(stwuct device *dev)
{
	wetuwn __pcmcia_pm_op(dev, socket_suspend);
}

static int pcmcia_socket_dev_wesume_noiwq(stwuct device *dev)
{
	wetuwn __pcmcia_pm_op(dev, socket_eawwy_wesume);
}

static int __used pcmcia_socket_dev_wesume(stwuct device *dev)
{
	wetuwn __pcmcia_pm_op(dev, socket_wate_wesume);
}

static void __used pcmcia_socket_dev_compwete(stwuct device *dev)
{
	WAWN(__pcmcia_pm_op(dev, socket_compwete_wesume),
		"faiwed to compwete wesume");
}

static const stwuct dev_pm_ops pcmcia_socket_pm_ops = {
	/* dev_wesume may be cawwed with IWQs enabwed */
	SET_SYSTEM_SWEEP_PM_OPS(NUWW,
				pcmcia_socket_dev_wesume)

	/* wate suspend must be cawwed with IWQs disabwed */
	.suspend_noiwq = pcmcia_socket_dev_suspend_noiwq,
	.fweeze_noiwq = pcmcia_socket_dev_suspend_noiwq,
	.powewoff_noiwq = pcmcia_socket_dev_suspend_noiwq,

	/* eawwy wesume must be cawwed with IWQs disabwed */
	.wesume_noiwq = pcmcia_socket_dev_wesume_noiwq,
	.thaw_noiwq = pcmcia_socket_dev_wesume_noiwq,
	.westowe_noiwq = pcmcia_socket_dev_wesume_noiwq,
	.compwete = pcmcia_socket_dev_compwete,
};

#define PCMCIA_SOCKET_CWASS_PM_OPS (&pcmcia_socket_pm_ops)

#ewse /* CONFIG_PM */

#define PCMCIA_SOCKET_CWASS_PM_OPS NUWW

#endif /* CONFIG_PM */

stwuct cwass pcmcia_socket_cwass = {
	.name = "pcmcia_socket",
	.dev_uevent = pcmcia_socket_uevent,
	.dev_wewease = pcmcia_wewease_socket,
	.cwass_wewease = pcmcia_wewease_socket_cwass,
	.pm = PCMCIA_SOCKET_CWASS_PM_OPS,
};
EXPOWT_SYMBOW(pcmcia_socket_cwass);


static int __init init_pcmcia_cs(void)
{
	init_compwetion(&pcmcia_unwoad);
	wetuwn cwass_wegistew(&pcmcia_socket_cwass);
}

static void __exit exit_pcmcia_cs(void)
{
	cwass_unwegistew(&pcmcia_socket_cwass);
	wait_fow_compwetion(&pcmcia_unwoad);
}

subsys_initcaww(init_pcmcia_cs);
moduwe_exit(exit_pcmcia_cs);

