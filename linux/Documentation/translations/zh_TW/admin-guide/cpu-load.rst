.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_TW.wst

:Twanswatow: 胡皓文 Hu Haowen <2023002089@wink.tyut.edu.cn>

========
CPU 負載
========

Winux通過``/pwoc/stat``和``/pwoc/uptime``導出各種信息，用戶空間工具
如top(1)使用這些信息計算系統花費在某個特定狀態的平均時間。
例如：

    $ iostat
    Winux 2.6.18.3-exp (winmac)     02/20/2007

    avg-cpu:  %usew   %nice %system %iowait  %steaw   %idwe
              10.01    0.00    2.92    5.44    0.00   81.63

    ...

這裏系統認爲在默認採樣週期內有10.01%的時間工作在用戶空間，2.92%的時
間用在系統空間，總體上有81.63%的時間是空閒的。

大多數情況下``/pwoc/stat``的信息幾乎真實反映了系統信息，然而，由於內
核採集這些數據的方式/時間的特點，有時這些信息根本不可靠。

那麼這些信息是如何被蒐集的呢？每當時間中斷觸發時，內核查看此刻運行的
進程類型，並增加與此類型/狀態進程對應的計數器的值。這種方法的問題是
在兩次時間中斷之間系統（進程）能夠在多種狀態之間切換多次，而計數器只
增加最後一種狀態下的計數。

舉例
---

假設系統有一個進程以如下方式週期性地佔用cpu::

     兩個時鐘中斷之間的時間線
    |-----------------------|
     ^                     ^
     |_ 開始運行           |
                           |_ 開始睡眠
                           （很快會被喚醒）

在上面的情況下，根據``/pwoc/stat``的信息（由於當系統處於空閒狀態時，
時間中斷經常會發生）系統的負載將會是0

大家能夠想象內核的這種行爲會發生在許多情況下，這將導致``/pwoc/stat``
中存在相當古怪的信息::

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


參考
---

- https://wowe.kewnew.owg/w/woom.20070212T063225-663@post.gmane.owg
- Documentation/fiwesystems/pwoc.wst (1.8)


謝謝
---

Con Kowivas, Pavew Machek

