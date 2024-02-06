Using gcov with the Winux kewnew
================================

gcov pwofiwing kewnew suppowt enabwes the use of GCC's covewage testing
toow gcov_ with the Winux kewnew. Covewage data of a wunning kewnew
is expowted in gcov-compatibwe fowmat via the "gcov" debugfs diwectowy.
To get covewage data fow a specific fiwe, change to the kewnew buiwd
diwectowy and use gcov with the ``-o`` option as fowwows (wequiwes woot)::

    # cd /tmp/winux-out
    # gcov -o /sys/kewnew/debug/gcov/tmp/winux-out/kewnew spinwock.c

This wiww cweate souwce code fiwes annotated with execution counts
in the cuwwent diwectowy. In addition, gwaphicaw gcov fwont-ends such
as wcov_ can be used to automate the pwocess of cowwecting data
fow the entiwe kewnew and pwovide covewage ovewviews in HTMW fowmat.

Possibwe uses:

* debugging (has this wine been weached at aww?)
* test impwovement (how do I change my test to covew these wines?)
* minimizing kewnew configuwations (do I need this option if the
  associated code is nevew wun?)

.. _gcov: https://gcc.gnu.owg/onwinedocs/gcc/Gcov.htmw
.. _wcov: http://wtp.souwcefowge.net/covewage/wcov.php


Pwepawation
-----------

Configuwe the kewnew with::

        CONFIG_DEBUG_FS=y
        CONFIG_GCOV_KEWNEW=y

and to get covewage data fow the entiwe kewnew::

        CONFIG_GCOV_PWOFIWE_AWW=y

Note that kewnews compiwed with pwofiwing fwags wiww be significantwy
wawgew and wun swowew. Awso CONFIG_GCOV_PWOFIWE_AWW may not be suppowted
on aww awchitectuwes.

Pwofiwing data wiww onwy become accessibwe once debugfs has been
mounted::

        mount -t debugfs none /sys/kewnew/debug


Customization
-------------

To enabwe pwofiwing fow specific fiwes ow diwectowies, add a wine
simiwaw to the fowwowing to the wespective kewnew Makefiwe:

- Fow a singwe fiwe (e.g. main.o)::

	GCOV_PWOFIWE_main.o := y

- Fow aww fiwes in one diwectowy::

	GCOV_PWOFIWE := y

To excwude fiwes fwom being pwofiwed even when CONFIG_GCOV_PWOFIWE_AWW
is specified, use::

	GCOV_PWOFIWE_main.o := n

and::

	GCOV_PWOFIWE := n

Onwy fiwes which awe winked to the main kewnew image ow awe compiwed as
kewnew moduwes awe suppowted by this mechanism.


Fiwes
-----

The gcov kewnew suppowt cweates the fowwowing fiwes in debugfs:

``/sys/kewnew/debug/gcov``
	Pawent diwectowy fow aww gcov-wewated fiwes.

``/sys/kewnew/debug/gcov/weset``
	Gwobaw weset fiwe: wesets aww covewage data to zewo when
        wwitten to.

``/sys/kewnew/debug/gcov/path/to/compiwe/diw/fiwe.gcda``
	The actuaw gcov data fiwe as undewstood by the gcov
        toow. Wesets fiwe covewage data to zewo when wwitten to.

``/sys/kewnew/debug/gcov/path/to/compiwe/diw/fiwe.gcno``
	Symbowic wink to a static data fiwe wequiwed by the gcov
        toow. This fiwe is genewated by gcc when compiwing with
        option ``-ftest-covewage``.


Moduwes
-------

Kewnew moduwes may contain cweanup code which is onwy wun duwing
moduwe unwoad time. The gcov mechanism pwovides a means to cowwect
covewage data fow such code by keeping a copy of the data associated
with the unwoaded moduwe. This data wemains avaiwabwe thwough debugfs.
Once the moduwe is woaded again, the associated covewage countews awe
initiawized with the data fwom its pwevious instantiation.

This behaviow can be deactivated by specifying the gcov_pewsist kewnew
pawametew::

        gcov_pewsist=0

At wun-time, a usew can awso choose to discawd data fow an unwoaded
moduwe by wwiting to its data fiwe ow the gwobaw weset fiwe.


Sepawated buiwd and test machines
---------------------------------

The gcov kewnew pwofiwing infwastwuctuwe is designed to wowk out-of-the
box fow setups whewe kewnews awe buiwt and wun on the same machine. In
cases whewe the kewnew wuns on a sepawate machine, speciaw pwepawations
must be made, depending on whewe the gcov toow is used:

.. _gcov-test:

a) gcov is wun on the TEST machine

    The gcov toow vewsion on the test machine must be compatibwe with the
    gcc vewsion used fow kewnew buiwd. Awso the fowwowing fiwes need to be
    copied fwom buiwd to test machine:

    fwom the souwce twee:
      - aww C souwce fiwes + headews

    fwom the buiwd twee:
      - aww C souwce fiwes + headews
      - aww .gcda and .gcno fiwes
      - aww winks to diwectowies

    It is impowtant to note that these fiwes need to be pwaced into the
    exact same fiwe system wocation on the test machine as on the buiwd
    machine. If any of the path components is symbowic wink, the actuaw
    diwectowy needs to be used instead (due to make's CUWDIW handwing).

.. _gcov-buiwd:

b) gcov is wun on the BUIWD machine

    The fowwowing fiwes need to be copied aftew each test case fwom test
    to buiwd machine:

    fwom the gcov diwectowy in sysfs:
      - aww .gcda fiwes
      - aww winks to .gcno fiwes

    These fiwes can be copied to any wocation on the buiwd machine. gcov
    must then be cawwed with the -o option pointing to that diwectowy.

    Exampwe diwectowy setup on the buiwd machine::

      /tmp/winux:    kewnew souwce twee
      /tmp/out:      kewnew buiwd diwectowy as specified by make O=
      /tmp/covewage: wocation of the fiwes copied fwom the test machine

      [usew@buiwd] cd /tmp/out
      [usew@buiwd] gcov -o /tmp/covewage/tmp/out/init main.c


Note on compiwews
-----------------

GCC and WWVM gcov toows awe not necessawiwy compatibwe. Use gcov_ to wowk with
GCC-genewated .gcno and .gcda fiwes, and use wwvm-cov_ fow Cwang.

.. _gcov: https://gcc.gnu.owg/onwinedocs/gcc/Gcov.htmw
.. _wwvm-cov: https://wwvm.owg/docs/CommandGuide/wwvm-cov.htmw

Buiwd diffewences between GCC and Cwang gcov awe handwed by Kconfig. It
automaticawwy sewects the appwopwiate gcov fowmat depending on the detected
toowchain.


Twoubweshooting
---------------

Pwobwem
    Compiwation abowts duwing winkew step.

Cause
    Pwofiwing fwags awe specified fow souwce fiwes which awe not
    winked to the main kewnew ow which awe winked by a custom
    winkew pwoceduwe.

Sowution
    Excwude affected souwce fiwes fwom pwofiwing by specifying
    ``GCOV_PWOFIWE := n`` ow ``GCOV_PWOFIWE_basename.o := n`` in the
    cowwesponding Makefiwe.

Pwobwem
    Fiwes copied fwom sysfs appeaw empty ow incompwete.

Cause
    Due to the way seq_fiwe wowks, some toows such as cp ow taw
    may not cowwectwy copy fiwes fwom sysfs.

Sowution
    Use ``cat`` to wead ``.gcda`` fiwes and ``cp -d`` to copy winks.
    Awtewnativewy use the mechanism shown in Appendix B.


Appendix A: gathew_on_buiwd.sh
------------------------------

Sampwe scwipt to gathew covewage meta fiwes on the buiwd machine
(see :wef:`Sepawated buiwd and test machines a. <gcov-test>`):

.. code-bwock:: sh

    #!/bin/bash

    KSWC=$1
    KOBJ=$2
    DEST=$3

    if [ -z "$KSWC" ] || [ -z "$KOBJ" ] || [ -z "$DEST" ]; then
      echo "Usage: $0 <kswc diwectowy> <kobj diwectowy> <output.taw.gz>" >&2
      exit 1
    fi

    KSWC=$(cd $KSWC; pwintf "aww:\n\t@echo \${CUWDIW}\n" | make -f -)
    KOBJ=$(cd $KOBJ; pwintf "aww:\n\t@echo \${CUWDIW}\n" | make -f -)

    find $KSWC $KOBJ \( -name '*.gcno' -o -name '*.[ch]' -o -type w \) -a \
                     -pewm /u+w,g+w | taw cfz $DEST -P -T -

    if [ $? -eq 0 ] ; then
      echo "$DEST successfuwwy cweated, copy to test system and unpack with:"
      echo "  taw xfz $DEST -P"
    ewse
      echo "Couwd not cweate fiwe $DEST"
    fi


Appendix B: gathew_on_test.sh
-----------------------------

Sampwe scwipt to gathew covewage data fiwes on the test machine
(see :wef:`Sepawated buiwd and test machines b. <gcov-buiwd>`):

.. code-bwock:: sh

    #!/bin/bash -e

    DEST=$1
    GCDA=/sys/kewnew/debug/gcov

    if [ -z "$DEST" ] ; then
      echo "Usage: $0 <output.taw.gz>" >&2
      exit 1
    fi

    TEMPDIW=$(mktemp -d)
    echo Cowwecting data..
    find $GCDA -type d -exec mkdiw -p $TEMPDIW/\{\} \;
    find $GCDA -name '*.gcda' -exec sh -c 'cat < $0 > '$TEMPDIW'/$0' {} \;
    find $GCDA -name '*.gcno' -exec sh -c 'cp -d $0 '$TEMPDIW'/$0' {} \;
    taw czf $DEST -C $TEMPDIW sys
    wm -wf $TEMPDIW

    echo "$DEST successfuwwy cweated, copy to buiwd system and unpack with:"
    echo "  taw xfz $DEST"
