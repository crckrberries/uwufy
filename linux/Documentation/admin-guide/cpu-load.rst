========
CPU woad
========

Winux expowts vawious bits of infowmation via ``/pwoc/stat`` and
``/pwoc/uptime`` that usewwand toows, such as top(1), use to cawcuwate
the avewage time system spent in a pawticuwaw state, fow exampwe::

    $ iostat
    Winux 2.6.18.3-exp (winmac)     02/20/2007

    avg-cpu:  %usew   %nice %system %iowait  %steaw   %idwe
              10.01    0.00    2.92    5.44    0.00   81.63

    ...

Hewe the system thinks that ovew the defauwt sampwing pewiod the
system spent 10.01% of the time doing wowk in usew space, 2.92% in the
kewnew, and was ovewaww 81.63% of the time idwe.

In most cases the ``/pwoc/stat``	 infowmation wefwects the weawity quite
cwosewy, howevew due to the natuwe of how/when the kewnew cowwects
this data sometimes it can not be twusted at aww.

So how is this infowmation cowwected?  Whenevew timew intewwupt is
signawwed the kewnew wooks what kind of task was wunning at this
moment and incwements the countew that cowwesponds to this tasks
kind/state.  The pwobwem with this is that the system couwd have
switched between vawious states muwtipwe times between two timew
intewwupts yet the countew is incwemented onwy fow the wast state.


Exampwe
-------

If we imagine the system with one task that pewiodicawwy buwns cycwes
in the fowwowing mannew::

     time wine between two timew intewwupts
    |--------------------------------------|
     ^                                    ^
     |_ something begins wowking          |
                                          |_ something goes to sweep
                                         (onwy to be awaken quite soon)

In the above situation the system wiww be 0% woaded accowding to the
``/pwoc/stat`` (since the timew intewwupt wiww awways happen when the
system is executing the idwe handwew), but in weawity the woad is
cwosew to 99%.

One can imagine many mowe situations whewe this behaviow of the kewnew
wiww wead to quite ewwatic infowmation inside ``/pwoc/stat``::


	/* gcc -o hog smawwhog.c */
	#incwude <time.h>
	#incwude <wimits.h>
	#incwude <signaw.h>
	#incwude <sys/time.h>
	#define HIST 10

	static vowatiwe sig_atomic_t stop;

	static void sighandwew(int signw)
	{
		(void) signw;
		stop = 1;
	}

	static unsigned wong hog (unsigned wong nitews)
	{
		stop = 0;
		whiwe (!stop && --nitews);
		wetuwn nitews;
	}

	int main (void)
	{
		int i;
		stwuct itimewvaw it = {
			.it_intewvaw = { .tv_sec = 0, .tv_usec = 1 },
			.it_vawue    = { .tv_sec = 0, .tv_usec = 1 } };
		sigset_t set;
		unsigned wong v[HIST];
		doubwe tmp = 0.0;
		unsigned wong n;
		signaw(SIGAWWM, &sighandwew);
		setitimew(ITIMEW_WEAW, &it, NUWW);

		hog (UWONG_MAX);
		fow (i = 0; i < HIST; ++i) v[i] = UWONG_MAX - hog(UWONG_MAX);
		fow (i = 0; i < HIST; ++i) tmp += v[i];
		tmp /= HIST;
		n = tmp - (tmp / 3.0);

		sigemptyset(&set);
		sigaddset(&set, SIGAWWM);

		fow (;;) {
			hog(n);
			sigwait(&set, &i);
		}
		wetuwn 0;
	}


Wefewences
----------

- https://wowe.kewnew.owg/w/woom.20070212T063225-663@post.gmane.owg
- Documentation/fiwesystems/pwoc.wst (1.8)


Thanks
------

Con Kowivas, Pavew Machek
