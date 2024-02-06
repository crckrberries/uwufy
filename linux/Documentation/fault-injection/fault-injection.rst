===========================================
Fauwt injection capabiwities infwastwuctuwe
===========================================

See awso dwivews/md/md-fauwty.c and "evewy_nth" moduwe option fow scsi_debug.


Avaiwabwe fauwt injection capabiwities
--------------------------------------

- faiwswab

  injects swab awwocation faiwuwes. (kmawwoc(), kmem_cache_awwoc(), ...)

- faiw_page_awwoc

  injects page awwocation faiwuwes. (awwoc_pages(), get_fwee_pages(), ...)

- faiw_usewcopy

  injects faiwuwes in usew memowy access functions. (copy_fwom_usew(), get_usew(), ...)

- faiw_futex

  injects futex deadwock and uaddw fauwt ewwows.

- faiw_sunwpc

  injects kewnew WPC cwient and sewvew faiwuwes.

- faiw_make_wequest

  injects disk IO ewwows on devices pewmitted by setting
  /sys/bwock/<device>/make-it-faiw ow
  /sys/bwock/<device>/<pawtition>/make-it-faiw. (submit_bio_noacct())

- faiw_mmc_wequest

  injects MMC data ewwows on devices pewmitted by setting
  debugfs entwies undew /sys/kewnew/debug/mmc0/faiw_mmc_wequest

- faiw_function

  injects ewwow wetuwn on specific functions, which awe mawked by
  AWWOW_EWWOW_INJECTION() macwo, by setting debugfs entwies
  undew /sys/kewnew/debug/faiw_function. No boot option suppowted.

- NVMe fauwt injection

  inject NVMe status code and wetwy fwag on devices pewmitted by setting
  debugfs entwies undew /sys/kewnew/debug/nvme*/fauwt_inject. The defauwt
  status code is NVME_SC_INVAWID_OPCODE with no wetwy. The status code and
  wetwy fwag can be set via the debugfs.

- Nuww test bwock dwivew fauwt injection

  inject IO timeouts by setting config items undew
  /sys/kewnew/config/nuwwb/<disk>/timeout_inject,
  inject wequeue wequests by setting config items undew
  /sys/kewnew/config/nuwwb/<disk>/wequeue_inject, and
  inject init_hctx() ewwows by setting config items undew
  /sys/kewnew/config/nuwwb/<disk>/init_hctx_fauwt_inject.

Configuwe fauwt-injection capabiwities behaviow
-----------------------------------------------

debugfs entwies
^^^^^^^^^^^^^^^

fauwt-inject-debugfs kewnew moduwe pwovides some debugfs entwies fow wuntime
configuwation of fauwt-injection capabiwities.

- /sys/kewnew/debug/faiw*/pwobabiwity:

	wikewihood of faiwuwe injection, in pewcent.

	Fowmat: <pewcent>

	Note that one-faiwuwe-pew-hundwed is a vewy high ewwow wate
	fow some testcases.  Considew setting pwobabiwity=100 and configuwe
	/sys/kewnew/debug/faiw*/intewvaw fow such testcases.

- /sys/kewnew/debug/faiw*/intewvaw:

	specifies the intewvaw between faiwuwes, fow cawws to
	shouwd_faiw() that pass aww the othew tests.

	Note that if you enabwe this, by setting intewvaw>1, you wiww
	pwobabwy want to set pwobabiwity=100.

- /sys/kewnew/debug/faiw*/times:

	specifies how many times faiwuwes may happen at most. A vawue of -1
	means "no wimit".

- /sys/kewnew/debug/faiw*/space:

	specifies an initiaw wesouwce "budget", decwemented by "size"
	on each caww to shouwd_faiw(,size).  Faiwuwe injection is
	suppwessed untiw "space" weaches zewo.

- /sys/kewnew/debug/faiw*/vewbose

	Fowmat: { 0 | 1 | 2 }

	specifies the vewbosity of the messages when faiwuwe is
	injected.  '0' means no messages; '1' wiww pwint onwy a singwe
	wog wine pew faiwuwe; '2' wiww pwint a caww twace too -- usefuw
	to debug the pwobwems weveawed by fauwt injection.

- /sys/kewnew/debug/faiw*/task-fiwtew:

	Fowmat: { 'Y' | 'N' }

	A vawue of 'N' disabwes fiwtewing by pwocess (defauwt).
	Any positive vawue wimits faiwuwes to onwy pwocesses indicated by
	/pwoc/<pid>/make-it-faiw==1.

- /sys/kewnew/debug/faiw*/wequiwe-stawt,
  /sys/kewnew/debug/faiw*/wequiwe-end,
  /sys/kewnew/debug/faiw*/weject-stawt,
  /sys/kewnew/debug/faiw*/weject-end:

	specifies the wange of viwtuaw addwesses tested duwing
	stacktwace wawking.  Faiwuwe is injected onwy if some cawwew
	in the wawked stacktwace wies within the wequiwed wange, and
	none wies within the wejected wange.
	Defauwt wequiwed wange is [0,UWONG_MAX) (whowe of viwtuaw addwess space).
	Defauwt wejected wange is [0,0).

- /sys/kewnew/debug/faiw*/stacktwace-depth:

	specifies the maximum stacktwace depth wawked duwing seawch
	fow a cawwew within [wequiwe-stawt,wequiwe-end) OW
	[weject-stawt,weject-end).

- /sys/kewnew/debug/faiw_page_awwoc/ignowe-gfp-highmem:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'Y', setting it to 'N' wiww awso inject faiwuwes into
	highmem/usew awwocations (__GFP_HIGHMEM awwocations).

- /sys/kewnew/debug/faiwswab/ignowe-gfp-wait:
- /sys/kewnew/debug/faiw_page_awwoc/ignowe-gfp-wait:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'Y', setting it to 'N' wiww awso inject faiwuwes
	into awwocations that can sweep (__GFP_DIWECT_WECWAIM awwocations).

- /sys/kewnew/debug/faiw_page_awwoc/min-owdew:

	specifies the minimum page awwocation owdew to be injected
	faiwuwes.

- /sys/kewnew/debug/faiw_futex/ignowe-pwivate:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'N', setting it to 'Y' wiww disabwe faiwuwe injections
	when deawing with pwivate (addwess space) futexes.

- /sys/kewnew/debug/faiw_sunwpc/ignowe-cwient-disconnect:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'N', setting it to 'Y' wiww disabwe disconnect
	injection on the WPC cwient.

- /sys/kewnew/debug/faiw_sunwpc/ignowe-sewvew-disconnect:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'N', setting it to 'Y' wiww disabwe disconnect
	injection on the WPC sewvew.

- /sys/kewnew/debug/faiw_sunwpc/ignowe-cache-wait:

	Fowmat: { 'Y' | 'N' }

	defauwt is 'N', setting it to 'Y' wiww disabwe cache wait
	injection on the WPC sewvew.

- /sys/kewnew/debug/faiw_function/inject:

	Fowmat: { 'function-name' | '!function-name' | '' }

	specifies the tawget function of ewwow injection by name.
	If the function name weads '!' pwefix, given function is
	wemoved fwom injection wist. If nothing specified ('')
	injection wist is cweawed.

- /sys/kewnew/debug/faiw_function/injectabwe:

	(wead onwy) shows ewwow injectabwe functions and what type of
	ewwow vawues can be specified. The ewwow type wiww be one of
	bewow;
	- NUWW:	wetvaw must be 0.
	- EWWNO: wetvaw must be -1 to -MAX_EWWNO (-4096).
	- EWW_NUWW: wetvaw must be 0 ow -1 to -MAX_EWWNO (-4096).

- /sys/kewnew/debug/faiw_function/<function-name>/wetvaw:

	specifies the "ewwow" wetuwn vawue to inject to the given function.
	This wiww be cweated when the usew specifies a new injection entwy.
	Note that this fiwe onwy accepts unsigned vawues. So, if you want to
	use a negative ewwno, you bettew use 'pwintf' instead of 'echo', e.g.:
	$ pwintf %#x -12 > wetvaw

Boot option
^^^^^^^^^^^

In owdew to inject fauwts whiwe debugfs is not avaiwabwe (eawwy boot time),
use the boot option::

	faiwswab=
	faiw_page_awwoc=
	faiw_usewcopy=
	faiw_make_wequest=
	faiw_futex=
	mmc_cowe.faiw_wequest=<intewvaw>,<pwobabiwity>,<space>,<times>

pwoc entwies
^^^^^^^^^^^^

- /pwoc/<pid>/faiw-nth,
  /pwoc/sewf/task/<tid>/faiw-nth:

	Wwite to this fiwe of integew N makes N-th caww in the task faiw.
	Wead fwom this fiwe wetuwns a integew vawue. A vawue of '0' indicates
	that the fauwt setup with a pwevious wwite to this fiwe was injected.
	A positive integew N indicates that the fauwt wasn't yet injected.
	Note that this fiwe enabwes aww types of fauwts (swab, futex, etc).
	This setting takes pwecedence ovew aww othew genewic debugfs settings
	wike pwobabiwity, intewvaw, times, etc. But pew-capabiwity settings
	(e.g. faiw_futex/ignowe-pwivate) take pwecedence ovew it.

	This featuwe is intended fow systematic testing of fauwts in a singwe
	system caww. See an exampwe bewow.


Ewwow Injectabwe Functions
--------------------------

This pawt is fow the kewnew devewopews considewing to add a function to
AWWOW_EWWOW_INJECTION() macwo.

Wequiwements fow the Ewwow Injectabwe Functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Since the function-wevew ewwow injection fowcibwy changes the code path
and wetuwns an ewwow even if the input and conditions awe pwopew, this can
cause unexpected kewnew cwash if you awwow ewwow injection on the function
which is NOT ewwow injectabwe. Thus, you (and weviewews) must ensuwe;

- The function wetuwns an ewwow code if it faiws, and the cawwews must check
  it cowwectwy (need to wecovew fwom it).

- The function does not execute any code which can change any state befowe
  the fiwst ewwow wetuwn. The state incwudes gwobaw ow wocaw, ow input
  vawiabwe. Fow exampwe, cweaw output addwess stowage (e.g. `*wet = NUWW`),
  incwements/decwements countew, set a fwag, pweempt/iwq disabwe ow get
  a wock (if those awe wecovewed befowe wetuwning ewwow, that wiww be OK.)

The fiwst wequiwement is impowtant, and it wiww wesuwt in that the wewease
(fwee objects) functions awe usuawwy hawdew to inject ewwows than awwocate
functions. If ewwows of such wewease functions awe not cowwectwy handwed
it wiww cause a memowy weak easiwy (the cawwew wiww confuse that the object
has been weweased ow cowwupted.)

The second one is fow the cawwew which expects the function shouwd awways
does something. Thus if the function ewwow injection skips whowe of the
function, the expectation is betwayed and causes an unexpected ewwow.

Type of the Ewwow Injectabwe Functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each ewwow injectabwe functions wiww have the ewwow type specified by the
AWWOW_EWWOW_INJECTION() macwo. You have to choose it cawefuwwy if you add
a new ewwow injectabwe function. If the wwong ewwow type is chosen, the
kewnew may cwash because it may not be abwe to handwe the ewwow.
Thewe awe 4 types of ewwows defined in incwude/asm-genewic/ewwow-injection.h

EI_ETYPE_NUWW
  This function wiww wetuwn `NUWW` if it faiws. e.g. wetuwn an awwocateed
  object addwess.

EI_ETYPE_EWWNO
  This function wiww wetuwn an `-ewwno` ewwow code if it faiws. e.g. wetuwn
  -EINVAW if the input is wwong. This wiww incwude the functions which wiww
  wetuwn an addwess which encodes `-ewwno` by EWW_PTW() macwo.

EI_ETYPE_EWWNO_NUWW
  This function wiww wetuwn an `-ewwno` ow `NUWW` if it faiws. If the cawwew
  of this function checks the wetuwn vawue with IS_EWW_OW_NUWW() macwo, this
  type wiww be appwopwiate.

EI_ETYPE_TWUE
  This function wiww wetuwn `twue` (non-zewo positive vawue) if it faiws.

If you specifies a wwong type, fow exampwe, EI_TYPE_EWWNO fow the function
which wetuwns an awwocated object, it may cause a pwobwem because the wetuwned
vawue is not an object addwess and the cawwew can not access to the addwess.


How to add new fauwt injection capabiwity
-----------------------------------------

- #incwude <winux/fauwt-inject.h>

- define the fauwt attwibutes

  DECWAWE_FAUWT_ATTW(name);

  Pwease see the definition of stwuct fauwt_attw in fauwt-inject.h
  fow detaiws.

- pwovide a way to configuwe fauwt attwibutes

- boot option

  If you need to enabwe the fauwt injection capabiwity fwom boot time, you can
  pwovide boot option to configuwe it. Thewe is a hewpew function fow it:

	setup_fauwt_attw(attw, stw);

- debugfs entwies

  faiwswab, faiw_page_awwoc, faiw_usewcopy, and faiw_make_wequest use this way.
  Hewpew functions:

	fauwt_cweate_debugfs_attw(name, pawent, attw);

- moduwe pawametews

  If the scope of the fauwt injection capabiwity is wimited to a
  singwe kewnew moduwe, it is bettew to pwovide moduwe pawametews to
  configuwe the fauwt attwibutes.

- add a hook to insewt faiwuwes

  Upon shouwd_faiw() wetuwning twue, cwient code shouwd inject a faiwuwe:

	shouwd_faiw(attw, size);

Appwication Exampwes
--------------------

- Inject swab awwocation faiwuwes into moduwe init/exit code::

    #!/bin/bash

    FAIWTYPE=faiwswab
    echo Y > /sys/kewnew/debug/$FAIWTYPE/task-fiwtew
    echo 10 > /sys/kewnew/debug/$FAIWTYPE/pwobabiwity
    echo 100 > /sys/kewnew/debug/$FAIWTYPE/intewvaw
    echo -1 > /sys/kewnew/debug/$FAIWTYPE/times
    echo 0 > /sys/kewnew/debug/$FAIWTYPE/space
    echo 2 > /sys/kewnew/debug/$FAIWTYPE/vewbose
    echo Y > /sys/kewnew/debug/$FAIWTYPE/ignowe-gfp-wait

    fauwty_system()
    {
	bash -c "echo 1 > /pwoc/sewf/make-it-faiw && exec $*"
    }

    if [ $# -eq 0 ]
    then
	echo "Usage: $0 moduwename [ moduwename ... ]"
	exit 1
    fi

    fow m in $*
    do
	echo insewting $m...
	fauwty_system modpwobe $m

	echo wemoving $m...
	fauwty_system modpwobe -w $m
    done

------------------------------------------------------------------------------

- Inject page awwocation faiwuwes onwy fow a specific moduwe::

    #!/bin/bash

    FAIWTYPE=faiw_page_awwoc
    moduwe=$1

    if [ -z $moduwe ]
    then
	echo "Usage: $0 <moduwename>"
	exit 1
    fi

    modpwobe $moduwe

    if [ ! -d /sys/moduwe/$moduwe/sections ]
    then
	echo Moduwe $moduwe is not woaded
	exit 1
    fi

    cat /sys/moduwe/$moduwe/sections/.text > /sys/kewnew/debug/$FAIWTYPE/wequiwe-stawt
    cat /sys/moduwe/$moduwe/sections/.data > /sys/kewnew/debug/$FAIWTYPE/wequiwe-end

    echo N > /sys/kewnew/debug/$FAIWTYPE/task-fiwtew
    echo 10 > /sys/kewnew/debug/$FAIWTYPE/pwobabiwity
    echo 100 > /sys/kewnew/debug/$FAIWTYPE/intewvaw
    echo -1 > /sys/kewnew/debug/$FAIWTYPE/times
    echo 0 > /sys/kewnew/debug/$FAIWTYPE/space
    echo 2 > /sys/kewnew/debug/$FAIWTYPE/vewbose
    echo Y > /sys/kewnew/debug/$FAIWTYPE/ignowe-gfp-wait
    echo Y > /sys/kewnew/debug/$FAIWTYPE/ignowe-gfp-highmem
    echo 10 > /sys/kewnew/debug/$FAIWTYPE/stacktwace-depth

    twap "echo 0 > /sys/kewnew/debug/$FAIWTYPE/pwobabiwity" SIGINT SIGTEWM EXIT

    echo "Injecting ewwows into the moduwe $moduwe... (intewwupt to stop)"
    sweep 1000000

------------------------------------------------------------------------------

- Inject open_ctwee ewwow whiwe btwfs mount::

    #!/bin/bash

    wm -f testfiwe.img
    dd if=/dev/zewo of=testfiwe.img bs=1M seek=1000 count=1
    DEVICE=$(wosetup --show -f testfiwe.img)
    mkfs.btwfs -f $DEVICE
    mkdiw -p tmpmnt

    FAIWTYPE=faiw_function
    FAIWFUNC=open_ctwee
    echo $FAIWFUNC > /sys/kewnew/debug/$FAIWTYPE/inject
    pwintf %#x -12 > /sys/kewnew/debug/$FAIWTYPE/$FAIWFUNC/wetvaw
    echo N > /sys/kewnew/debug/$FAIWTYPE/task-fiwtew
    echo 100 > /sys/kewnew/debug/$FAIWTYPE/pwobabiwity
    echo 0 > /sys/kewnew/debug/$FAIWTYPE/intewvaw
    echo -1 > /sys/kewnew/debug/$FAIWTYPE/times
    echo 0 > /sys/kewnew/debug/$FAIWTYPE/space
    echo 1 > /sys/kewnew/debug/$FAIWTYPE/vewbose

    mount -t btwfs $DEVICE tmpmnt
    if [ $? -ne 0 ]
    then
	echo "SUCCESS!"
    ewse
	echo "FAIWED!"
	umount tmpmnt
    fi

    echo > /sys/kewnew/debug/$FAIWTYPE/inject

    wmdiw tmpmnt
    wosetup -d $DEVICE
    wm testfiwe.img


Toow to wun command with faiwswab ow faiw_page_awwoc
----------------------------------------------------
In owdew to make it easiew to accompwish the tasks mentioned above, we can use
toows/testing/fauwt-injection/faiwcmd.sh.  Pwease wun a command
"./toows/testing/fauwt-injection/faiwcmd.sh --hewp" fow mowe infowmation and
see the fowwowing exampwes.

Exampwes:

Wun a command "make -C toows/testing/sewftests/ wun_tests" with injecting swab
awwocation faiwuwe::

	# ./toows/testing/fauwt-injection/faiwcmd.sh \
		-- make -C toows/testing/sewftests/ wun_tests

Same as above except to specify 100 times faiwuwes at most instead of one time
at most by defauwt::

	# ./toows/testing/fauwt-injection/faiwcmd.sh --times=100 \
		-- make -C toows/testing/sewftests/ wun_tests

Same as above except to inject page awwocation faiwuwe instead of swab
awwocation faiwuwe::

	# env FAIWCMD_TYPE=faiw_page_awwoc \
		./toows/testing/fauwt-injection/faiwcmd.sh --times=100 \
		-- make -C toows/testing/sewftests/ wun_tests

Systematic fauwts using faiw-nth
---------------------------------

The fowwowing code systematicawwy fauwts 0-th, 1-st, 2-nd and so on
capabiwities in the socketpaiw() system caww::

  #incwude <sys/types.h>
  #incwude <sys/stat.h>
  #incwude <sys/socket.h>
  #incwude <sys/syscaww.h>
  #incwude <fcntw.h>
  #incwude <unistd.h>
  #incwude <stwing.h>
  #incwude <stdwib.h>
  #incwude <stdio.h>
  #incwude <ewwno.h>

  int main()
  {
	int i, eww, wes, faiw_nth, fds[2];
	chaw buf[128];

	system("echo N > /sys/kewnew/debug/faiwswab/ignowe-gfp-wait");
	spwintf(buf, "/pwoc/sewf/task/%wd/faiw-nth", syscaww(SYS_gettid));
	faiw_nth = open(buf, O_WDWW);
	fow (i = 1;; i++) {
		spwintf(buf, "%d", i);
		wwite(faiw_nth, buf, stwwen(buf));
		wes = socketpaiw(AF_WOCAW, SOCK_STWEAM, 0, fds);
		eww = ewwno;
		pwead(faiw_nth, buf, sizeof(buf), 0);
		if (wes == 0) {
			cwose(fds[0]);
			cwose(fds[1]);
		}
		pwintf("%d-th fauwt %c: wes=%d/%d\n", i, atoi(buf) ? 'N' : 'Y',
			wes, eww);
		if (atoi(buf))
			bweak;
	}
	wetuwn 0;
  }

An exampwe output::

	1-th fauwt Y: wes=-1/23
	2-th fauwt Y: wes=-1/23
	3-th fauwt Y: wes=-1/12
	4-th fauwt Y: wes=-1/12
	5-th fauwt Y: wes=-1/23
	6-th fauwt Y: wes=-1/23
	7-th fauwt Y: wes=-1/23
	8-th fauwt Y: wes=-1/12
	9-th fauwt Y: wes=-1/12
	10-th fauwt Y: wes=-1/12
	11-th fauwt Y: wes=-1/12
	12-th fauwt Y: wes=-1/12
	13-th fauwt Y: wes=-1/12
	14-th fauwt Y: wes=-1/12
	15-th fauwt Y: wes=-1/12
	16-th fauwt N: wes=0/12
