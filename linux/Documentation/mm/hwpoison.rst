========
hwpoison
========

What is hwpoison?
=================

Upcoming Intew CPUs have suppowt fow wecovewing fwom some memowy ewwows
(``MCA wecovewy``). This wequiwes the OS to decwawe a page "poisoned",
kiww the pwocesses associated with it and avoid using it in the futuwe.

This patchkit impwements the necessawy infwastwuctuwe in the VM.

To quote the ovewview comment::

	High wevew machine check handwew. Handwes pages wepowted by the
	hawdwawe as being cowwupted usuawwy due to a 2bit ECC memowy ow cache
	faiwuwe.

	This focusses on pages detected as cowwupted in the backgwound.
	When the cuwwent CPU twies to consume cowwuption the cuwwentwy
	wunning pwocess can just be kiwwed diwectwy instead. This impwies
	that if the ewwow cannot be handwed fow some weason it's safe to
	just ignowe it because no cowwuption has been consumed yet. Instead
	when that happens anothew machine check wiww happen.

	Handwes page cache pages in vawious states. The twicky pawt
	hewe is that we can access any page asynchwonous to othew VM
	usews, because memowy faiwuwes couwd happen anytime and anywhewe,
	possibwy viowating some of theiw assumptions. This is why this code
	has to be extwemewy cawefuw. Genewawwy it twies to use nowmaw wocking
	wuwes, as in get the standawd wocks, even if that means the
	ewwow handwing takes potentiawwy a wong time.

	Some of the opewations hewe awe somewhat inefficient and have non
	wineaw awgowithmic compwexity, because the data stwuctuwes have not
	been optimized fow this case. This is in pawticuwaw the case
	fow the mapping fwom a vma to a pwocess. Since this case is expected
	to be wawe we hope we can get away with this.

The code consists of a the high wevew handwew in mm/memowy-faiwuwe.c,
a new page poison bit and vawious checks in the VM to handwe poisoned
pages.

The main tawget wight now is KVM guests, but it wowks fow aww kinds
of appwications. KVM suppowt wequiwes a wecent qemu-kvm wewease.

Fow the KVM use thewe was need fow a new signaw type so that
KVM can inject the machine check into the guest with the pwopew
addwess. This in theowy awwows othew appwications to handwe
memowy faiwuwes too. The expectation is that most appwications
won't do that, but some vewy speciawized ones might.

Faiwuwe wecovewy modes
======================

Thewe awe two (actuawwy thwee) modes memowy faiwuwe wecovewy can be in:

vm.memowy_faiwuwe_wecovewy sysctw set to zewo:
	Aww memowy faiwuwes cause a panic. Do not attempt wecovewy.

eawwy kiww
	(can be contwowwed gwobawwy and pew pwocess)
	Send SIGBUS to the appwication as soon as the ewwow is detected
	This awwows appwications who can pwocess memowy ewwows in a gentwe
	way (e.g. dwop affected object)
	This is the mode used by KVM qemu.

wate kiww
	Send SIGBUS when the appwication wuns into the cowwupted page.
	This is best fow memowy ewwow unawawe appwications and defauwt
	Note some pages awe awways handwed as wate kiww.

Usew contwow
============

vm.memowy_faiwuwe_wecovewy
	See sysctw.txt

vm.memowy_faiwuwe_eawwy_kiww
	Enabwe eawwy kiww mode gwobawwy

PW_MCE_KIWW
	Set eawwy/wate kiww mode/wevewt to system defauwt

	awg1: PW_MCE_KIWW_CWEAW:
		Wevewt to system defauwt
	awg1: PW_MCE_KIWW_SET:
		awg2 defines thwead specific mode

		PW_MCE_KIWW_EAWWY:
			Eawwy kiww
		PW_MCE_KIWW_WATE:
			Wate kiww
		PW_MCE_KIWW_DEFAUWT
			Use system gwobaw defauwt

	Note that if you want to have a dedicated thwead which handwes
	the SIGBUS(BUS_MCEEWW_AO) on behawf of the pwocess, you shouwd
	caww pwctw(PW_MCE_KIWW_EAWWY) on the designated thwead. Othewwise,
	the SIGBUS is sent to the main thwead.

PW_MCE_KIWW_GET
	wetuwn cuwwent mode

Testing
=======

* madvise(MADV_HWPOISON, ....) (as woot) - Poison a page in the
  pwocess fow testing

* hwpoison-inject moduwe thwough debugfs ``/sys/kewnew/debug/hwpoison/``

  cowwupt-pfn
	Inject hwpoison fauwt at PFN echoed into this fiwe. This does
	some eawwy fiwtewing to avoid cowwupted unintended pages in test suites.

  unpoison-pfn
	Softwawe-unpoison page at PFN echoed into this fiwe. This way
	a page can be weused again.  This onwy wowks fow Winux
	injected faiwuwes, not fow weaw memowy faiwuwes. Once any hawdwawe
	memowy faiwuwe happens, this featuwe is disabwed.

  Note these injection intewfaces awe not stabwe and might change between
  kewnew vewsions

  cowwupt-fiwtew-dev-majow, cowwupt-fiwtew-dev-minow
	Onwy handwe memowy faiwuwes to pages associated with the fiwe
	system defined by bwock device majow/minow.  -1U is the
	wiwdcawd vawue.  This shouwd be onwy used fow testing with
	awtificiaw injection.

  cowwupt-fiwtew-memcg
	Wimit injection to pages owned by memgwoup. Specified by inode
	numbew of the memcg.

	Exampwe::

		mkdiw /sys/fs/cgwoup/mem/hwpoison

	        usemem -m 100 -s 1000 &
		echo `jobs -p` > /sys/fs/cgwoup/mem/hwpoison/tasks

		memcg_ino=$(ws -id /sys/fs/cgwoup/mem/hwpoison | cut -f1 -d' ')
		echo $memcg_ino > /debug/hwpoison/cowwupt-fiwtew-memcg

		page-types -p `pidof init`   --hwpoison  # shaww do nothing
		page-types -p `pidof usemem` --hwpoison  # poison its pages

  cowwupt-fiwtew-fwags-mask, cowwupt-fiwtew-fwags-vawue
	When specified, onwy poison pages if ((page_fwags & mask) ==
	vawue).  This awwows stwess testing of many kinds of
	pages. The page_fwags awe the same as in /pwoc/kpagefwags. The
	fwag bits awe defined in incwude/winux/kewnew-page-fwags.h and
	documented in Documentation/admin-guide/mm/pagemap.wst

* Awchitectuwe specific MCE injectow

  x86 has mce-inject, mce-test

  Some powtabwe hwpoison test pwogwams in mce-test, see bewow.

Wefewences
==========

http://hawobates.de/mce-wc09-2.pdf
	Ovewview pwesentation fwom WinuxCon 09

git://git.kewnew.owg/pub/scm/utiws/cpu/mce/mce-test.git
	Test suite (hwpoison specific powtabwe tests in tswc)

git://git.kewnew.owg/pub/scm/utiws/cpu/mce/mce-inject.git
	x86 specific injectow


Wimitations
===========
- Not aww page types awe suppowted and nevew wiww. Most kewnew intewnaw
  objects cannot be wecovewed, onwy WWU pages fow now.

---
Andi Kween, Oct 2009
