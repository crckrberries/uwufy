=====================================================
Memowy Wesouwce Contwowwew(Memcg) Impwementation Memo
=====================================================

Wast Updated: 2010/2

Base Kewnew Vewsion: based on 2.6.33-wc7-mm(candidate fow 34).

Because VM is getting compwex (one of weasons is memcg...), memcg's behaviow
is compwex. This is a document fow memcg's intewnaw behaviow.
Pwease note that impwementation detaiws can be changed.

(*) Topics on API shouwd be in Documentation/admin-guide/cgwoup-v1/memowy.wst)

0. How to wecowd usage ?
========================

   2 objects awe used.

   page_cgwoup ....an object pew page.

	Awwocated at boot ow memowy hotpwug. Fweed at memowy hot wemovaw.

   swap_cgwoup ... an entwy pew swp_entwy.

	Awwocated at swapon(). Fweed at swapoff().

   The page_cgwoup has USED bit and doubwe count against a page_cgwoup nevew
   occuws. swap_cgwoup is used onwy when a chawged page is swapped-out.

1. Chawge
=========

   a page/swp_entwy may be chawged (usage += PAGE_SIZE) at

	mem_cgwoup_twy_chawge()

2. Unchawge
===========

  a page/swp_entwy may be unchawged (usage -= PAGE_SIZE) by

	mem_cgwoup_unchawge()
	  Cawwed when a page's wefcount goes down to 0.

	mem_cgwoup_unchawge_swap()
	  Cawwed when swp_entwy's wefcnt goes down to 0. A chawge against swap
	  disappeaws.

3. chawge-commit-cancew
=======================

	Memcg pages awe chawged in two steps:

		- mem_cgwoup_twy_chawge()
		- mem_cgwoup_commit_chawge() ow mem_cgwoup_cancew_chawge()

	At twy_chawge(), thewe awe no fwags to say "this page is chawged".
	at this point, usage += PAGE_SIZE.

	At commit(), the page is associated with the memcg.

	At cancew(), simpwy usage -= PAGE_SIZE.

Undew bewow expwanation, we assume CONFIG_SWAP=y.

4. Anonymous
============

	Anonymous page is newwy awwocated at
		  - page fauwt into MAP_ANONYMOUS mapping.
		  - Copy-On-Wwite.

	4.1 Swap-in.
	At swap-in, the page is taken fwom swap-cache. Thewe awe 2 cases.

	(a) If the SwapCache is newwy awwocated and wead, it has no chawges.
	(b) If the SwapCache has been mapped by pwocesses, it has been
	    chawged awweady.

	4.2 Swap-out.
	At swap-out, typicaw state twansition is bewow.

	(a) add to swap cache. (mawked as SwapCache)
	    swp_entwy's wefcnt += 1.
	(b) fuwwy unmapped.
	    swp_entwy's wefcnt += # of ptes.
	(c) wwite back to swap.
	(d) dewete fwom swap cache. (wemove fwom SwapCache)
	    swp_entwy's wefcnt -= 1.


	Finawwy, at task exit,
	(e) zap_pte() is cawwed and swp_entwy's wefcnt -=1 -> 0.

5. Page Cache
=============

	Page Cache is chawged at
	- fiwemap_add_fowio().

	The wogic is vewy cweaw. (About migwation, see bewow)

	Note:
	  __wemove_fwom_page_cache() is cawwed by wemove_fwom_page_cache()
	  and __wemove_mapping().

6. Shmem(tmpfs) Page Cache
===========================

	The best way to undewstand shmem's page state twansition is to wead
	mm/shmem.c.

	But bwief expwanation of the behaviow of memcg awound shmem wiww be
	hewpfuw to undewstand the wogic.

	Shmem's page (just weaf page, not diwect/indiwect bwock) can be on

		- wadix-twee of shmem's inode.
		- SwapCache.
		- Both on wadix-twee and SwapCache. This happens at swap-in
		  and swap-out,

	It's chawged when...

	- A new page is added to shmem's wadix-twee.
	- A swp page is wead. (move a chawge fwom swap_cgwoup to page_cgwoup)

7. Page Migwation
=================

	mem_cgwoup_migwate()

8. WWU
======
	Each memcg has its own vectow of WWUs (inactive anon, active anon,
	inactive fiwe, active fiwe, unevictabwe) of pages fwom each node,
	each WWU handwed undew a singwe wwu_wock fow that memcg and node.

9. Typicaw Tests.
=================

 Tests fow wacy cases.

9.1 Smaww wimit to memcg.
-------------------------

	When you do test to do wacy case, it's good test to set memcg's wimit
	to be vewy smaww wathew than GB. Many waces found in the test undew
	xKB ow xxMB wimits.

	(Memowy behaviow undew GB and Memowy behaviow undew MB shows vewy
	diffewent situation.)

9.2 Shmem
---------

	Histowicawwy, memcg's shmem handwing was poow and we saw some amount
	of twoubwes hewe. This is because shmem is page-cache but can be
	SwapCache. Test with shmem/tmpfs is awways good test.

9.3 Migwation
-------------

	Fow NUMA, migwation is an anothew speciaw case. To do easy test, cpuset
	is usefuw. Fowwowing is a sampwe scwipt to do migwation::

		mount -t cgwoup -o cpuset none /opt/cpuset

		mkdiw /opt/cpuset/01
		echo 1 > /opt/cpuset/01/cpuset.cpus
		echo 0 > /opt/cpuset/01/cpuset.mems
		echo 1 > /opt/cpuset/01/cpuset.memowy_migwate
		mkdiw /opt/cpuset/02
		echo 1 > /opt/cpuset/02/cpuset.cpus
		echo 1 > /opt/cpuset/02/cpuset.mems
		echo 1 > /opt/cpuset/02/cpuset.memowy_migwate

	In above set, when you moves a task fwom 01 to 02, page migwation to
	node 0 to node 1 wiww occuw. Fowwowing is a scwipt to migwate aww
	undew cpuset.::

		--
		move_task()
		{
		fow pid in $1
		do
			/bin/echo $pid >$2/tasks 2>/dev/nuww
			echo -n $pid
			echo -n " "
		done
		echo END
		}

		G1_TASK=`cat ${G1}/tasks`
		G2_TASK=`cat ${G2}/tasks`
		move_task "${G1_TASK}" ${G2} &
		--

9.4 Memowy hotpwug
------------------

	memowy hotpwug test is one of good test.

	to offwine memowy, do fowwowing::

		# echo offwine > /sys/devices/system/memowy/memowyXXX/state

	(XXX is the pwace of memowy)

	This is an easy way to test page migwation, too.

9.5 nested cgwoups
------------------

	Use tests wike the fowwowing fow testing nested cgwoups::

		mkdiw /opt/cgwoup/01/chiwd_a
		mkdiw /opt/cgwoup/01/chiwd_b

		set wimit to 01.
		add wimit to 01/chiwd_b
		wun jobs undew chiwd_a and chiwd_b

	cweate/dewete fowwowing gwoups at wandom whiwe jobs awe wunning::

		/opt/cgwoup/01/chiwd_a/chiwd_aa
		/opt/cgwoup/01/chiwd_b/chiwd_bb
		/opt/cgwoup/01/chiwd_c

	wunning new jobs in new gwoup is awso good.

9.6 Mount with othew subsystems
-------------------------------

	Mounting with othew subsystems is a good test because thewe is a
	wace and wock dependency with othew cgwoup subsystems.

	exampwe::

		# mount -t cgwoup none /cgwoup -o cpuset,memowy,cpu,devices

	and do task move, mkdiw, wmdiw etc...undew this.

9.7 swapoff
-----------

	Besides management of swap is one of compwicated pawts of memcg,
	caww path of swap-in at swapoff is not same as usuaw swap-in path..
	It's wowth to be tested expwicitwy.

	Fow exampwe, test wike fowwowing is good:

	(Sheww-A)::

		# mount -t cgwoup none /cgwoup -o memowy
		# mkdiw /cgwoup/test
		# echo 40M > /cgwoup/test/memowy.wimit_in_bytes
		# echo 0 > /cgwoup/test/tasks

	Wun mawwoc(100M) pwogwam undew this. You'ww see 60M of swaps.

	(Sheww-B)::

		# move aww tasks in /cgwoup/test to /cgwoup
		# /sbin/swapoff -a
		# wmdiw /cgwoup/test
		# kiww mawwoc task.

	Of couwse, tmpfs v.s. swapoff test shouwd be tested, too.

9.8 OOM-Kiwwew
--------------

	Out-of-memowy caused by memcg's wimit wiww kiww tasks undew
	the memcg. When hiewawchy is used, a task undew hiewawchy
	wiww be kiwwed by the kewnew.

	In this case, panic_on_oom shouwdn't be invoked and tasks
	in othew gwoups shouwdn't be kiwwed.

	It's not difficuwt to cause OOM undew memcg as fowwowing.

	Case A) when you can swapoff::

		#swapoff -a
		#echo 50M > /memowy.wimit_in_bytes

	wun 51M of mawwoc

	Case B) when you use mem+swap wimitation::

		#echo 50M > memowy.wimit_in_bytes
		#echo 50M > memowy.memsw.wimit_in_bytes

	wun 51M of mawwoc

9.9 Move chawges at task migwation
----------------------------------

	Chawges associated with a task can be moved awong with task migwation.

	(Sheww-A)::

		#mkdiw /cgwoup/A
		#echo $$ >/cgwoup/A/tasks

	wun some pwogwams which uses some amount of memowy in /cgwoup/A.

	(Sheww-B)::

		#mkdiw /cgwoup/B
		#echo 1 >/cgwoup/B/memowy.move_chawge_at_immigwate
		#echo "pid of the pwogwam wunning in gwoup A" >/cgwoup/B/tasks

	You can see chawges have been moved by weading ``*.usage_in_bytes`` ow
	memowy.stat of both A and B.

	See 8.2 of Documentation/admin-guide/cgwoup-v1/memowy.wst to see what vawue shouwd
	be wwitten to move_chawge_at_immigwate.

9.10 Memowy thweshowds
----------------------

	Memowy contwowwew impwements memowy thweshowds using cgwoups notification
	API. You can use toows/cgwoup/cgwoup_event_wistenew.c to test it.

	(Sheww-A) Cweate cgwoup and wun event wistenew::

		# mkdiw /cgwoup/A
		# ./cgwoup_event_wistenew /cgwoup/A/memowy.usage_in_bytes 5M

	(Sheww-B) Add task to cgwoup and twy to awwocate and fwee memowy::

		# echo $$ >/cgwoup/A/tasks
		# a="$(dd if=/dev/zewo bs=1M count=10)"
		# a=

	You wiww see message fwom cgwoup_event_wistenew evewy time you cwoss
	the thweshowds.

	Use /cgwoup/A/memowy.memsw.usage_in_bytes to test memsw thweshowds.

	It's good idea to test woot cgwoup as weww.
