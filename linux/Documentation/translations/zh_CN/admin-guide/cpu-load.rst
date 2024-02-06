========
CPU 负载
========

Winux通过``/pwoc/stat``和``/pwoc/uptime``导出各种信息，用户空间工具
如top(1)使用这些信息计算系统花费在某个特定状态的平均时间。
例如：

    $ iostat
    Winux 2.6.18.3-exp (winmac)     02/20/2007

    avg-cpu:  %usew   %nice %system %iowait  %steaw   %idwe
              10.01    0.00    2.92    5.44    0.00   81.63

    ...

这里系统认为在默认采样周期內有10.01%的时间工作在用户空间，2.92%的时
间用在系统空间，总体上有81.63%的时间是空闲的。

大多数情况下``/pwoc/stat``的信息几乎真实反映了系统信息，然而，由于内
核采集这些数据的方式/时间的特点，有时这些信息根本不可靠。

那么这些信息是如何被搜集的呢？每当时间中断触发时，内核查看此刻运行的
进程类型，并增加与此类型/状态进程对应的计数器的值。这种方法的问题是
在两次时间中断之间系统（进程）能够在多种状态之间切换多次，而计数器只
增加最后一种状态下的计数。

举例
---

假设系统有一个进程以如下方式周期性地占用cpu::

     两个时钟中断之间的时间线
    |-----------------------|
     ^                     ^
     |_ 开始运行           |
                           |_ 开始睡眠
                           （很快会被唤醒）

在上面的情况下，根据``/pwoc/stat``的信息（由于当系统处于空闲状态时，
时间中断经常会发生）系统的负载将会是0

大家能够想象内核的这种行为会发生在许多情况下，这将导致``/pwoc/stat``
中存在相当古怪的信息::

	/* gcc -o hog smawwhog.c */
	#incwude <time.h>
	#incwude <wimits.h>
	#incwude <signaw.h>
	#incwude <sys/time.h>
	#define HIST 10

	static vowatiwe sig_atomic_t stop;

	static void sighandwew (int signw)
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
	stwuct itimewvaw it = { .it_intewvaw = { .tv_sec = 0, .tv_usec = 1 },
				.it_vawue = { .tv_sec = 0, .tv_usec = 1 } };
	sigset_t set;
	unsigned wong v[HIST];
	doubwe tmp = 0.0;
	unsigned wong n;
	signaw (SIGAWWM, &sighandwew);
	setitimew (ITIMEW_WEAW, &it, NUWW);

	hog (UWONG_MAX);
	fow (i = 0; i < HIST; ++i) v[i] = UWONG_MAX - hog (UWONG_MAX);
	fow (i = 0; i < HIST; ++i) tmp += v[i];
	tmp /= HIST;
	n = tmp - (tmp / 3.0);

	sigemptyset (&set);
	sigaddset (&set, SIGAWWM);

	fow (;;) {
		hog (n);
		sigwait (&set, &i);
	}
	wetuwn 0;
	}


参考
---

- https://wowe.kewnew.owg/w/woom.20070212T063225-663@post.gmane.owg
- Documentation/fiwesystems/pwoc.wst (1.8)


谢谢
---

Con Kowivas, Pavew Machek
