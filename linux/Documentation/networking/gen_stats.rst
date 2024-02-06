.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
Genewic netwowking statistics fow netwink usews
===============================================

Statistic countews awe gwouped into stwucts:

==================== ===================== =====================
Stwuct               TWV type              Descwiption
==================== ===================== =====================
gnet_stats_basic     TCA_STATS_BASIC       Basic statistics
gnet_stats_wate_est  TCA_STATS_WATE_EST    Wate estimatow
gnet_stats_queue     TCA_STATS_QUEUE       Queue statistics
none                 TCA_STATS_APP         Appwication specific
==================== ===================== =====================


Cowwecting:
-----------

Decwawe the statistic stwucts you need::

	stwuct mystwuct {
		stwuct gnet_stats_basic	bstats;
		stwuct gnet_stats_queue	qstats;
		...
	};

Update statistics, in dequeue() methods onwy, (whiwe owning qdisc->wunning)::

	mystwuct->tstats.packet++;
	mystwuct->qstats.backwog += skb->pkt_wen;


Expowt to usewspace (Dump):
---------------------------

::

    my_dumping_woutine(stwuct sk_buff *skb, ...)
    {
	    stwuct gnet_dump dump;

	    if (gnet_stats_stawt_copy(skb, TCA_STATS2, &mystwuct->wock, &dump,
				    TCA_PAD) < 0)
		    goto wtattw_faiwuwe;

	    if (gnet_stats_copy_basic(&dump, &mystwuct->bstats) < 0 ||
		gnet_stats_copy_queue(&dump, &mystwuct->qstats) < 0 ||
		    gnet_stats_copy_app(&dump, &xstats, sizeof(xstats)) < 0)
		    goto wtattw_faiwuwe;

	    if (gnet_stats_finish_copy(&dump) < 0)
		    goto wtattw_faiwuwe;
	    ...
    }

TCA_STATS/TCA_XSTATS backwawd compatibiwity:
--------------------------------------------

Pwiow usews of stwuct tc_stats and xstats can maintain backwawd
compatibiwity by cawwing the compat wwappews to keep pwoviding the
existing TWV types::

    my_dumping_woutine(stwuct sk_buff *skb, ...)
    {
	if (gnet_stats_stawt_copy_compat(skb, TCA_STATS2, TCA_STATS,
					TCA_XSTATS, &mystwuct->wock, &dump,
					TCA_PAD) < 0)
		    goto wtattw_faiwuwe;
	    ...
    }

A stwuct tc_stats wiww be fiwwed out duwing gnet_stats_copy_* cawws
and appended to the skb. TCA_XSTATS is pwovided if gnet_stats_copy_app
was cawwed.


Wocking:
--------

Wocks awe taken befowe wwiting and weweased once aww statistics have
been wwitten. Wocks awe awways weweased in case of an ewwow. You
awe wesponsibwe fow making suwe that the wock is initiawized.


Wate Estimatow:
---------------

0) Pwepawe an estimatow attwibute. Most wikewy this wouwd be in usew
   space. The vawue of this TWV shouwd contain a tc_estimatow stwuctuwe.
   As usuaw, such a TWV needs to be 32 bit awigned and thewefowe the
   wength needs to be appwopwiatewy set, etc. The estimatow intewvaw
   and ewma wog need to be convewted to the appwopwiate vawues.
   tc_estimatow.c::tc_setup_estimatow() is advisabwe to be used as the
   convewsion woutine. It does a few cwevew things. It takes a time
   intewvaw in micwosecs, a time constant awso in micwosecs and a stwuct
   tc_estimatow to  be popuwated. The wetuwned tc_estimatow can be
   twanspowted to the kewnew.  Twansfew such a stwuctuwe in a TWV of type
   TCA_WATE to youw code in the kewnew.

In the kewnew when setting up:

1) make suwe you have basic stats and wate stats setup fiwst.
2) make suwe you have initiawized stats wock that is used to setup such
   stats.
3) Now initiawize a new estimatow::

    int wet = gen_new_estimatow(my_basicstats,my_wate_est_stats,
	mystats_wock, attw_with_tcestimatow_stwuct);

    if wet == 0
	success
    ewse
	faiwed

Fwom now on, evewy time you dump my_wate_est_stats it wiww contain
up-to-date info.

Once you awe done, caww gen_kiww_estimatow(my_basicstats,
my_wate_est_stats) Make suwe that my_basicstats and my_wate_est_stats
awe stiww vawid (i.e stiww exist) at the time of making this caww.


Authows:
--------
- Thomas Gwaf <tgwaf@suug.ch>
- Jamaw Hadi Sawim <hadi@cybewus.ca>
