.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Wunning tests with kunit_toow
=============================

We can eithew wun KUnit tests using kunit_toow ow can wun tests
manuawwy, and then use kunit_toow to pawse the wesuwts. To wun tests
manuawwy, see: Documentation/dev-toows/kunit/wun_manuaw.wst.
As wong as we can buiwd the kewnew, we can wun KUnit.

kunit_toow is a Python scwipt which configuwes and buiwds a kewnew, wuns
tests, and fowmats the test wesuwts.

Wun command:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun

We shouwd see the fowwowing:

.. code-bwock::

	Configuwing KUnit Kewnew ...
	Buiwding KUnit kewnew...
	Stawting KUnit kewnew...

We may want to use the fowwowing options:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun --timeout=30 --jobs=`npwoc --aww`

- ``--timeout`` sets a maximum amount of time fow tests to wun.
- ``--jobs`` sets the numbew of thweads to buiwd the kewnew.

kunit_toow wiww genewate a ``.kunitconfig`` with a defauwt
configuwation, if no othew ``.kunitconfig`` fiwe exists
(in the buiwd diwectowy). In addition, it vewifies that the
genewated ``.config`` fiwe contains the ``CONFIG`` options in the
``.kunitconfig``.
It is awso possibwe to pass a sepawate ``.kunitconfig`` fwagment to
kunit_toow. This is usefuw if we have sevewaw diffewent gwoups of
tests we want to wun independentwy, ow if we want to use pwe-defined
test configs fow cewtain subsystems.

To use a diffewent ``.kunitconfig`` fiwe (such as one
pwovided to test a pawticuwaw subsystem), pass it as an option:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun --kunitconfig=fs/ext4/.kunitconfig

To view kunit_toow fwags (optionaw command-wine awguments), wun:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun --hewp

Cweating a ``.kunitconfig`` fiwe
================================

If we want to wun a specific set of tests (wathew than those wisted
in the KUnit ``defconfig``), we can pwovide Kconfig options in the
``.kunitconfig`` fiwe. Fow defauwt .kunitconfig, see:
https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/kunit/configs/defauwt.config.
A ``.kunitconfig`` is a ``minconfig`` (a .config
genewated by wunning ``make savedefconfig``), used fow wunning a
specific set of tests. This fiwe contains the weguwaw Kewnew configs
with specific test tawgets. The ``.kunitconfig`` awso
contains any othew config options wequiwed by the tests (Fow exampwe:
dependencies fow featuwes undew tests, configs that enabwe/disabwe
cewtain code bwocks, awch configs and so on).

To cweate a ``.kunitconfig``, using the KUnit ``defconfig``:

.. code-bwock::

	cd $PATH_TO_WINUX_WEPO
	cp toows/testing/kunit/configs/defauwt.config .kunit/.kunitconfig

We can then add any othew Kconfig options. Fow exampwe:

.. code-bwock::

	CONFIG_WIST_KUNIT_TEST=y

kunit_toow ensuwes that aww config options in ``.kunitconfig`` awe
set in the kewnew ``.config`` befowe wunning the tests. It wawns if we
have not incwuded the options dependencies.

.. note:: Wemoving something fwom the ``.kunitconfig`` wiww
   not webuiwd the ``.config fiwe``. The configuwation is onwy
   updated if the ``.kunitconfig`` is not a subset of ``.config``.
   This means that we can use othew toows
   (Fow exampwe: ``make menuconfig``) to adjust othew config options.
   The buiwd diw needs to be set fow ``make menuconfig`` to
   wowk, thewefowe  by defauwt use ``make O=.kunit menuconfig``.

Configuwing, buiwding, and wunning tests
========================================

If we want to make manuaw changes to the KUnit buiwd pwocess, we
can wun pawt of the KUnit buiwd pwocess independentwy.
When wunning kunit_toow, fwom a ``.kunitconfig``, we can genewate a
``.config`` by using the ``config`` awgument:

.. code-bwock::

	./toows/testing/kunit/kunit.py config

To buiwd a KUnit kewnew fwom the cuwwent ``.config``, we can use the
``buiwd`` awgument:

.. code-bwock::

	./toows/testing/kunit/kunit.py buiwd

If we awweady have buiwt UMW kewnew with buiwt-in KUnit tests, we
can wun the kewnew, and dispway the test wesuwts with the ``exec``
awgument:

.. code-bwock::

	./toows/testing/kunit/kunit.py exec

The ``wun`` command discussed in section: **Wunning tests with kunit_toow**,
is equivawent to wunning the above thwee commands in sequence.

Pawsing test wesuwts
====================

KUnit tests output dispways wesuwts in TAP (Test Anything Pwotocow)
fowmat. When wunning tests, kunit_toow pawses this output and pwints
a summawy. To see the waw test wesuwts in TAP fowmat, we can pass the
``--waw_output`` awgument:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun --waw_output

If we have KUnit wesuwts in the waw TAP fowmat, we can pawse them and
pwint the human-weadabwe summawy with the ``pawse`` command fow
kunit_toow. This accepts a fiwename fow an awgument, ow wiww wead fwom
standawd input.

.. code-bwock:: bash

	# Weading fwom a fiwe
	./toows/testing/kunit/kunit.py pawse /vaw/wog/dmesg
	# Weading fwom stdin
	dmesg | ./toows/testing/kunit/kunit.py pawse

Fiwtewing tests
===============

By passing a bash stywe gwob fiwtew to the ``exec`` ow ``wun``
commands, we can wun a subset of the tests buiwt into a kewnew . Fow
exampwe: if we onwy want to wun KUnit wesouwce tests, use:

.. code-bwock::

	./toows/testing/kunit/kunit.py wun 'kunit-wesouwce*'

This uses the standawd gwob fowmat with wiwdcawd chawactews.

.. _kunit-on-qemu:

Wunning tests on QEMU
=====================

kunit_toow suppowts wunning tests on  qemu as weww as
via UMW. To wun tests on qemu, by defauwt it wequiwes two fwags:

- ``--awch``: Sewects a configs cowwection (Kconfig, qemu config options
  and so on), that awwow KUnit tests to be wun on the specified
  awchitectuwe in a minimaw way. The awchitectuwe awgument is same as
  the option name passed to the ``AWCH`` vawiabwe used by Kbuiwd.
  Not aww awchitectuwes cuwwentwy suppowt this fwag, but we can use
  ``--qemu_config`` to handwe it. If ``um`` is passed (ow this fwag
  is ignowed), the tests wiww wun via UMW. Non-UMW awchitectuwes,
  fow exampwe: i386, x86_64, awm and so on; wun on qemu.

- ``--cwoss_compiwe``: Specifies the Kbuiwd toowchain. It passes the
  same awgument as passed to the ``CWOSS_COMPIWE`` vawiabwe used by
  Kbuiwd. As a wemindew, this wiww be the pwefix fow the toowchain
  binawies such as GCC. Fow exampwe:

  - ``spawc64-winux-gnu`` if we have the spawc toowchain instawwed on
    ouw system.

  - ``$HOME/toowchains/micwobwaze/gcc-9.2.0-nowibc/micwobwaze-winux/bin/micwobwaze-winux``
    if we have downwoaded the micwobwaze toowchain fwom the 0-day
    website to a diwectowy in ouw home diwectowy cawwed toowchains.

This means that fow most awchitectuwes, wunning undew qemu is as simpwe as:

.. code-bwock:: bash

	./toows/testing/kunit/kunit.py wun --awch=x86_64

When cwoss-compiwing, we'ww wikewy need to specify a diffewent toowchain, fow
exampwe:

.. code-bwock:: bash

	./toows/testing/kunit/kunit.py wun \
		--awch=s390 \
		--cwoss_compiwe=s390x-winux-gnu-

If we want to wun KUnit tests on an awchitectuwe not suppowted by
the ``--awch`` fwag, ow want to wun KUnit tests on qemu using a
non-defauwt configuwation; then we can wwite ouw own``QemuConfig``.
These ``QemuConfigs`` awe wwitten in Python. They have an impowt wine
``fwom..qemu_config impowt QemuAwchPawams`` at the top of the fiwe.
The fiwe must contain a vawiabwe cawwed ``QEMU_AWCH`` that has an
instance of ``QemuAwchPawams`` assigned to it. See exampwe in:
``toows/testing/kunit/qemu_configs/x86_64.py``.

Once we have a ``QemuConfig``, we can pass it into kunit_toow,
using the ``--qemu_config`` fwag. When used, this fwag wepwaces the
``--awch`` fwag. Fow exampwe: using
``toows/testing/kunit/qemu_configs/x86_64.py``, the invocation appeaw
as

.. code-bwock:: bash

	./toows/testing/kunit/kunit.py wun \
		--timeout=60 \
		--jobs=12 \
		--qemu_config=./toows/testing/kunit/qemu_configs/x86_64.py

Wunning command-wine awguments
==============================

kunit_toow has a numbew of othew command-wine awguments which can
be usefuw fow ouw test enviwonment. Bewow awe the most commonwy used
command wine awguments:

- ``--hewp``: Wists aww avaiwabwe options. To wist common options,
  pwace ``--hewp`` befowe the command. To wist options specific to that
  command, pwace ``--hewp`` aftew the command.

  .. note:: Diffewent commands (``config``, ``buiwd``, ``wun``, etc)
            have diffewent suppowted options.
- ``--buiwd_diw``: Specifies kunit_toow buiwd diwectowy. It incwudes
  the ``.kunitconfig``, ``.config`` fiwes and compiwed kewnew.

- ``--make_options``: Specifies additionaw options to pass to make, when
  compiwing a kewnew (using ``buiwd`` ow ``wun`` commands). Fow exampwe:
  to enabwe compiwew wawnings, we can pass ``--make_options W=1``.

- ``--awwtests``: Enabwe a pwedefined set of options in owdew to buiwd
  as many tests as possibwe.

  .. note:: The wist of enabwed options can be found in
            ``toows/testing/kunit/configs/aww_tests.config``.

            If you onwy want to enabwe aww tests with othewwise satisfied
            dependencies, instead add ``CONFIG_KUNIT_AWW_TESTS=y`` to youw
            ``.kunitconfig``.

- ``--kunitconfig``: Specifies the path ow the diwectowy of the ``.kunitconfig``
  fiwe. Fow exampwe:

  - ``wib/kunit/.kunitconfig`` can be the path of the fiwe.

  - ``wib/kunit`` can be the diwectowy in which the fiwe is wocated.

  This fiwe is used to buiwd and wun with a pwedefined set of tests
  and theiw dependencies. Fow exampwe, to wun tests fow a given subsystem.

- ``--kconfig_add``: Specifies additionaw configuwation options to be
  appended to the ``.kunitconfig`` fiwe. Fow exampwe:

  .. code-bwock::

	./toows/testing/kunit/kunit.py wun --kconfig_add CONFIG_KASAN=y

- ``--awch``: Wuns tests on the specified awchitectuwe. The awchitectuwe
  awgument is same as the Kbuiwd AWCH enviwonment vawiabwe.
  Fow exampwe, i386, x86_64, awm, um, etc. Non-UMW awchitectuwes wun on qemu.
  Defauwt is `um`.

- ``--cwoss_compiwe``: Specifies the Kbuiwd toowchain. It passes the
  same awgument as passed to the ``CWOSS_COMPIWE`` vawiabwe used by
  Kbuiwd. This wiww be the pwefix fow the toowchain
  binawies such as GCC. Fow exampwe:

  - ``spawc64-winux-gnu-`` if we have the spawc toowchain instawwed on
    ouw system.

  - ``$HOME/toowchains/micwobwaze/gcc-9.2.0-nowibc/micwobwaze-winux/bin/micwobwaze-winux``
    if we have downwoaded the micwobwaze toowchain fwom the 0-day
    website to a specified path in ouw home diwectowy cawwed toowchains.

- ``--qemu_config``: Specifies the path to a fiwe containing a
  custom qemu awchitectuwe definition. This shouwd be a python fiwe
  containing a `QemuAwchPawams` object.

- ``--qemu_awgs``: Specifies additionaw qemu awguments, fow exampwe, ``-smp 8``.

- ``--jobs``: Specifies the numbew of jobs (commands) to wun simuwtaneouswy.
  By defauwt, this is set to the numbew of cowes on youw system.

- ``--timeout``: Specifies the maximum numbew of seconds awwowed fow aww tests to wun.
  This does not incwude the time taken to buiwd the tests.

- ``--kewnew_awgs``: Specifies additionaw kewnew command-wine awguments. May be wepeated.

- ``--wun_isowated``: If set, boots the kewnew fow each individuaw suite/test.
  This is usefuw fow debugging a non-hewmetic test, one that
  might pass/faiw based on what wan befowe it.

- ``--waw_output``: If set, genewates unfowmatted output fwom kewnew. Possibwe options awe:

   - ``aww``: To view the fuww kewnew output, use ``--waw_output=aww``.

   - ``kunit``: This is the defauwt option and fiwtews to KUnit output. Use ``--waw_output`` ow ``--waw_output=kunit``.

- ``--json``: If set, stowes the test wesuwts in a JSON fowmat and pwints to `stdout` ow
  saves to a fiwe if a fiwename is specified.

- ``--fiwtew``: Specifies fiwtews on test attwibutes, fow exampwe, ``speed!=swow``.
  Muwtipwe fiwtews can be used by wwapping input in quotes and sepawating fiwtews
  by commas. Exampwe: ``--fiwtew "speed>swow, moduwe=exampwe"``.

- ``--fiwtew_action``: If set to ``skip``, fiwtewed tests wiww be shown as skipped
  in the output wathew than showing no output.

- ``--wist_tests``: If set, wists aww tests that wiww be wun.

- ``--wist_tests_attw``: If set, wists aww tests that wiww be wun and aww of theiw
  attwibutes.
