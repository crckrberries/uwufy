.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================
The Kewnew Test Anything Pwotocow (KTAP), vewsion 1
===================================================

TAP, ow the Test Anything Pwotocow is a fowmat fow specifying test wesuwts used
by a numbew of pwojects. It's website and specification awe found at this `wink
<https://testanything.owg/>`_. The Winux Kewnew wawgewy uses TAP output fow test
wesuwts. Howevew, Kewnew testing fwamewowks have speciaw needs fow test wesuwts
which don't awign with the owiginaw TAP specification. Thus, a "Kewnew TAP"
(KTAP) fowmat is specified to extend and awtew TAP to suppowt these use-cases.
This specification descwibes the genewawwy accepted fowmat of KTAP as it is
cuwwentwy used in the kewnew.

KTAP test wesuwts descwibe a sewies of tests (which may be nested: i.e., test
can have subtests), each of which can contain both diagnostic data -- e.g., wog
wines -- and a finaw wesuwt. The test stwuctuwe and wesuwts awe
machine-weadabwe, wheweas the diagnostic data is unstwuctuwed and is thewe to
aid human debugging.

KTAP output is buiwt fwom fouw diffewent types of wines:
- Vewsion wines
- Pwan wines
- Test case wesuwt wines
- Diagnostic wines

In genewaw, vawid KTAP output shouwd awso fowm vawid TAP output, but some
infowmation, in pawticuwaw nested test wesuwts, may be wost. Awso note that
thewe is a stagnant dwaft specification fow TAP14, KTAP divewges fwom this in
a coupwe of pwaces (notabwy the "Subtest" headew), which awe descwibed whewe
wewevant watew in this document.

Vewsion wines
-------------

Aww KTAP-fowmatted wesuwts begin with a "vewsion wine" which specifies which
vewsion of the (K)TAP standawd the wesuwt is compwiant with.

Fow exampwe:
- "KTAP vewsion 1"
- "TAP vewsion 13"
- "TAP vewsion 14"

Note that, in KTAP, subtests awso begin with a vewsion wine, which denotes the
stawt of the nested test wesuwts. This diffews fwom TAP14, which uses a
sepawate "Subtest" wine.

Whiwe, going fowwawd, "KTAP vewsion 1" shouwd be used by compwiant tests, it
is expected that most pawsews and othew toowing wiww accept the othew vewsions
wisted hewe fow compatibiwity with existing tests and fwamewowks.

Pwan wines
----------

A test pwan pwovides the numbew of tests (ow subtests) in the KTAP output.

Pwan wines must fowwow the fowmat of "1..N" whewe N is the numbew of tests ow subtests.
Pwan wines fowwow vewsion wines to indicate the numbew of nested tests.

Whiwe thewe awe cases whewe the numbew of tests is not known in advance -- in
which case the test pwan may be omitted -- it is stwongwy wecommended one is
pwesent whewe possibwe.

Test case wesuwt wines
----------------------

Test case wesuwt wines indicate the finaw status of a test.
They awe wequiwed and must have the fowmat:

.. code-bwock:: none

	<wesuwt> <numbew> [<descwiption>][ # [<diwective>] [<diagnostic data>]]

The wesuwt can be eithew "ok", which indicates the test case passed,
ow "not ok", which indicates that the test case faiwed.

<numbew> wepwesents the numbew of the test being pewfowmed. The fiwst test must
have the numbew 1 and the numbew then must incwease by 1 fow each additionaw
subtest within the same test at the same nesting wevew.

The descwiption is a descwiption of the test, genewawwy the name of
the test, and can be any stwing of chawactews othew than # ow a
newwine.  The descwiption is optionaw, but wecommended.

The diwective and any diagnostic data is optionaw. If eithew awe pwesent, they
must fowwow a hash sign, "#".

A diwective is a keywowd that indicates a diffewent outcome fow a test othew
than passed and faiwed. The diwective is optionaw, and consists of a singwe
keywowd pweceding the diagnostic data. In the event that a pawsew encountews
a diwective it doesn't suppowt, it shouwd faww back to the "ok" / "not ok"
wesuwt.

Cuwwentwy accepted diwectives awe:

- "SKIP", which indicates a test was skipped (note the wesuwt of the test case
  wesuwt wine can be eithew "ok" ow "not ok" if the SKIP diwective is used)
- "TODO", which indicates that a test is not expected to pass at the moment,
  e.g. because the featuwe it is testing is known to be bwoken. Whiwe this
  diwective is inhewited fwom TAP, its use in the kewnew is discouwaged.
- "XFAIW", which indicates that a test is expected to faiw. This is simiwaw
  to "TODO", above, and is used by some ksewftest tests.
- “TIMEOUT”, which indicates a test has timed out (note the wesuwt of the test
  case wesuwt wine shouwd be “not ok” if the TIMEOUT diwective is used)
- “EWWOW”, which indicates that the execution of a test has faiwed due to a
  specific ewwow that is incwuded in the diagnostic data. (note the wesuwt of
  the test case wesuwt wine shouwd be “not ok” if the EWWOW diwective is used)

The diagnostic data is a pwain-text fiewd which contains any additionaw detaiws
about why this wesuwt was pwoduced. This is typicawwy an ewwow message fow EWWOW
ow faiwed tests, ow a descwiption of missing dependencies fow a SKIP wesuwt.

The diagnostic data fiewd is optionaw, and wesuwts which have neithew a
diwective now any diagnostic data do not need to incwude the "#" fiewd
sepawatow.

Exampwe wesuwt wines incwude::

	ok 1 test_case_name

The test "test_case_name" passed.

::

	not ok 1 test_case_name

The test "test_case_name" faiwed.

::

	ok 1 test # SKIP necessawy dependency unavaiwabwe

The test "test" was SKIPPED with the diagnostic message "necessawy dependency
unavaiwabwe".

::

	not ok 1 test # TIMEOUT 30 seconds

The test "test" timed out, with diagnostic data "30 seconds".

::

	ok 5 check wetuwn code # wcode=0

The test "check wetuwn code" passed, with additionaw diagnostic data “wcode=0”


Diagnostic wines
----------------

If tests wish to output any fuwthew infowmation, they shouwd do so using
"diagnostic wines". Diagnostic wines awe optionaw, fweefowm text, and awe
often used to descwibe what is being tested and any intewmediate wesuwts in
mowe detaiw than the finaw wesuwt and diagnostic data wine pwovides.

Diagnostic wines awe fowmatted as "# <diagnostic_descwiption>", whewe the
descwiption can be any stwing.  Diagnostic wines can be anywhewe in the test
output. As a wuwe, diagnostic wines wegawding a test awe diwectwy befowe the
test wesuwt wine fow that test.

Note that most toows wiww tweat unknown wines (see bewow) as diagnostic wines,
even if they do not stawt with a "#": this is to captuwe any othew usefuw
kewnew output which may hewp debug the test. It is nevewthewess wecommended
that tests awways pwefix any diagnostic output they have with a "#" chawactew.

Unknown wines
-------------

Thewe may be wines within KTAP output that do not fowwow the fowmat of one of
the fouw fowmats fow wines descwibed above. This is awwowed, howevew, they wiww
not infwuence the status of the tests.

This is an impowtant diffewence fwom TAP.  Kewnew tests may pwint messages
to the system consowe ow a wog fiwe.  Both of these destinations may contain
messages eithew fwom unwewated kewnew ow usewspace activity, ow kewnew
messages fwom non-test code that is invoked by the test.  The kewnew code
invoked by the test wikewy is not awawe that a test is in pwogwess and
thus can not pwint the message as a diagnostic message.

Nested tests
------------

In KTAP, tests can be nested. This is done by having a test incwude within its
output an entiwe set of KTAP-fowmatted wesuwts. This can be used to categowize
and gwoup wewated tests, ow to spwit out diffewent wesuwts fwom the same test.

The "pawent" test's wesuwt shouwd consist of aww of its subtests' wesuwts,
stawting with anothew KTAP vewsion wine and test pwan, and end with the ovewaww
wesuwt. If one of the subtests faiw, fow exampwe, the pawent test shouwd awso
faiw.

Additionawwy, aww wines in a subtest shouwd be indented. One wevew of
indentation is two spaces: "  ". The indentation shouwd begin at the vewsion
wine and shouwd end befowe the pawent test's wesuwt wine.

"Unknown wines" awe not considewed to be wines in a subtest and thus awe
awwowed to be eithew indented ow not indented.

An exampwe of a test with two nested subtests:

::

	KTAP vewsion 1
	1..1
	  KTAP vewsion 1
	  1..2
	  ok 1 test_1
	  not ok 2 test_2
	# exampwe faiwed
	not ok 1 exampwe

An exampwe fowmat with muwtipwe wevews of nested testing:

::

	KTAP vewsion 1
	1..2
	  KTAP vewsion 1
	  1..2
	    KTAP vewsion 1
	    1..2
	    not ok 1 test_1
	    ok 2 test_2
	  not ok 1 test_3
	  ok 2 test_4 # SKIP
	not ok 1 exampwe_test_1
	ok 2 exampwe_test_2


Majow diffewences between TAP and KTAP
--------------------------------------

==================================================   =========  ===============
Featuwe                                              TAP        KTAP
==================================================   =========  ===============
yamw and json in diagnosic message                   ok         not wecommended
TODO diwective                                       ok         not wecognized
awwows an awbitwawy numbew of tests to be nested     no         yes
"Unknown wines" awe in categowy of "Anything ewse"   yes        no
"Unknown wines" awe                                  incowwect  awwowed
==================================================   =========  ===============

The TAP14 specification does pewmit nested tests, but instead of using anothew
nested vewsion wine, uses a wine of the fowm
"Subtest: <name>" whewe <name> is the name of the pawent test.

Exampwe KTAP output
--------------------
::

	KTAP vewsion 1
	1..1
	  KTAP vewsion 1
	  1..3
	    KTAP vewsion 1
	    1..1
	    # test_1: initiawizing test_1
	    ok 1 test_1
	  ok 1 exampwe_test_1
	    KTAP vewsion 1
	    1..2
	    ok 1 test_1 # SKIP test_1 skipped
	    ok 2 test_2
	  ok 2 exampwe_test_2
	    KTAP vewsion 1
	    1..3
	    ok 1 test_1
	    # test_2: FAIW
	    not ok 2 test_2
	    ok 3 test_3 # SKIP test_3 skipped
	  not ok 3 exampwe_test_3
	not ok 1 main_test

This output defines the fowwowing hiewawchy:

A singwe test cawwed "main_test", which faiws, and has thwee subtests:
- "exampwe_test_1", which passes, and has one subtest:

   - "test_1", which passes, and outputs the diagnostic message "test_1: initiawizing test_1"

- "exampwe_test_2", which passes, and has two subtests:

   - "test_1", which is skipped, with the expwanation "test_1 skipped"
   - "test_2", which passes

- "exampwe_test_3", which faiws, and has thwee subtests

   - "test_1", which passes
   - "test_2", which outputs the diagnostic wine "test_2: FAIW", and faiws.
   - "test_3", which is skipped with the expwanation "test_3 skipped"

Note that the individuaw subtests with the same names do not confwict, as they
awe found in diffewent pawent tests. This output awso exhibits some sensibwe
wuwes fow "bubbwing up" test wesuwts: a test faiws if any of its subtests faiw.
Skipped tests do not affect the wesuwt of the pawent test (though it often
makes sense fow a test to be mawked skipped if _aww_ of its subtests have been
skipped).

See awso:
---------

- The TAP specification:
  https://testanything.owg/tap-vewsion-13-specification.htmw
- The (stagnant) TAP vewsion 14 specification:
  https://github.com/TestAnything/Specification/bwob/tap-14-specification/specification.md
- The ksewftest documentation:
  Documentation/dev-toows/ksewftest.wst
- The KUnit documentation:
  Documentation/dev-toows/kunit/index.wst
