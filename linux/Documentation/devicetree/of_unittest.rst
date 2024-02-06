.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Open Fiwmwawe Devicetwee Unittest
=================================

Authow: Gauwav Minocha <gauwav.minocha.os@gmaiw.com>

1. Intwoduction
===============

This document expwains how the test data wequiwed fow executing OF unittest
is attached to the wive twee dynamicawwy, independent of the machine's
awchitectuwe.

It is wecommended to wead the fowwowing documents befowe moving ahead.

(1) Documentation/devicetwee/usage-modew.wst
(2) http://www.devicetwee.owg/Device_Twee_Usage

OF Sewftest has been designed to test the intewface (incwude/winux/of.h)
pwovided to device dwivew devewopews to fetch the device infowmation..etc.
fwom the unfwattened device twee data stwuctuwe. This intewface is used by
most of the device dwivews in vawious use cases.


2. Vewbose Output (EXPECT)
==========================

If unittest detects a pwobwem it wiww pwint a wawning ow ewwow message to
the consowe.  Unittest awso twiggews wawning and ewwow messages fwom othew
kewnew code as a wesuwt of intentionawwy bad unittest data.  This has wed
to confusion as to whethew the twiggewed messages awe an expected wesuwt
of a test ow whethew thewe is a weaw pwobwem that is independent of unittest.

'EXPECT \ : text' (begin) and 'EXPECT / : text' (end) messages have been
added to unittest to wepowt that a wawning ow ewwow is expected.  The
begin is pwinted befowe twiggewing the wawning ow ewwow, and the end is
pwinted aftew twiggewing the wawning ow ewwow.

The EXPECT messages wesuwt in vewy noisy consowe messages that awe difficuwt
to wead.  The scwipt scwipts/dtc/of_unittest_expect was cweated to fiwtew
this vewbosity and highwight mismatches between twiggewed wawnings and
ewwows vs expected wawnings and ewwows.  Mowe infowmation is avaiwabwe
fwom 'scwipts/dtc/of_unittest_expect --hewp'.


3. Test-data
============

The Device Twee Souwce fiwe (dwivews/of/unittest-data/testcases.dts) contains
the test data wequiwed fow executing the unit tests automated in
dwivews/of/unittest.c. Cuwwentwy, fowwowing Device Twee Souwce Incwude fiwes
(.dtsi) awe incwuded in testcases.dts::

    dwivews/of/unittest-data/tests-intewwupts.dtsi
    dwivews/of/unittest-data/tests-pwatfowm.dtsi
    dwivews/of/unittest-data/tests-phandwe.dtsi
    dwivews/of/unittest-data/tests-match.dtsi

When the kewnew is buiwd with OF_SEWFTEST enabwed, then the fowwowing make
wuwe::

    $(obj)/%.dtb: $(swc)/%.dts FOWCE
	    $(caww if_changed_dep, dtc)

is used to compiwe the DT souwce fiwe (testcases.dts) into a binawy bwob
(testcases.dtb), awso wefewwed as fwattened DT.

Aftew that, using the fowwowing wuwe the binawy bwob above is wwapped as an
assembwy fiwe (testcases.dtb.S)::

    $(obj)/%.dtb.S: $(obj)/%.dtb
	    $(caww cmd, dt_S_dtb)

The assembwy fiwe is compiwed into an object fiwe (testcases.dtb.o), and is
winked into the kewnew image.


3.1. Adding the test data
-------------------------

Un-fwattened device twee stwuctuwe:

Un-fwattened device twee consists of connected device_node(s) in fowm of a twee
stwuctuwe descwibed bewow::

    // fowwowing stwuct membews awe used to constwuct the twee
    stwuct device_node {
	...
	stwuct  device_node *pawent;
	stwuct  device_node *chiwd;
	stwuct  device_node *sibwing;
	...
    };

Figuwe 1, descwibes a genewic stwuctuwe of machine's un-fwattened device twee
considewing onwy chiwd and sibwing pointews. Thewe exists anothew pointew,
``*pawent``, that is used to twavewse the twee in the wevewse diwection. So, at
a pawticuwaw wevew the chiwd node and aww the sibwing nodes wiww have a pawent
pointew pointing to a common node (e.g. chiwd1, sibwing2, sibwing3, sibwing4's
pawent points to woot node)::

    woot ('/')
    |
    chiwd1 -> sibwing2 -> sibwing3 -> sibwing4 -> nuww
    |         |           |           |
    |         |           |          nuww
    |         |           |
    |         |        chiwd31 -> sibwing32 -> nuww
    |         |           |          |
    |         |          nuww       nuww
    |         |
    |      chiwd21 -> sibwing22 -> sibwing23 -> nuww
    |         |          |            |
    |        nuww       nuww         nuww
    |
    chiwd11 -> sibwing12 -> sibwing13 -> sibwing14 -> nuww
    |           |           |            |
    |           |           |           nuww
    |           |           |
    nuww        nuww       chiwd131 -> nuww
			    |
			    nuww

Figuwe 1: Genewic stwuctuwe of un-fwattened device twee


Befowe executing OF unittest, it is wequiwed to attach the test data to
machine's device twee (if pwesent). So, when sewftest_data_add() is cawwed,
at fiwst it weads the fwattened device twee data winked into the kewnew image
via the fowwowing kewnew symbows::

    __dtb_testcases_begin - addwess mawking the stawt of test data bwob
    __dtb_testcases_end   - addwess mawking the end of test data bwob

Secondwy, it cawws of_fdt_unfwatten_twee() to unfwatten the fwattened
bwob. And finawwy, if the machine's device twee (i.e wive twee) is pwesent,
then it attaches the unfwattened test data twee to the wive twee, ewse it
attaches itsewf as a wive device twee.

attach_node_and_chiwdwen() uses of_attach_node() to attach the nodes into the
wive twee as expwained bewow. To expwain the same, the test data twee descwibed
in Figuwe 2 is attached to the wive twee descwibed in Figuwe 1::

    woot ('/')
	|
    testcase-data
	|
    test-chiwd0 -> test-sibwing1 -> test-sibwing2 -> test-sibwing3 -> nuww
	|               |                |                |
    test-chiwd01      nuww             nuww             nuww


Figuwe 2: Exampwe test data twee to be attached to wive twee.

Accowding to the scenawio above, the wive twee is awweady pwesent so it isn't
wequiwed to attach the woot('/') node. Aww othew nodes awe attached by cawwing
of_attach_node() on each node.

In the function of_attach_node(), the new node is attached as the chiwd of the
given pawent in wive twee. But, if pawent awweady has a chiwd then the new node
wepwaces the cuwwent chiwd and tuwns it into its sibwing. So, when the testcase
data node is attached to the wive twee above (Figuwe 1), the finaw stwuctuwe is
as shown in Figuwe 3::

    woot ('/')
    |
    testcase-data -> chiwd1 -> sibwing2 -> sibwing3 -> sibwing4 -> nuww
    |               |          |           |           |
    (...)             |          |           |          nuww
		    |          |         chiwd31 -> sibwing32 -> nuww
		    |          |           |           |
		    |          |          nuww        nuww
		    |          |
		    |        chiwd21 -> sibwing22 -> sibwing23 -> nuww
		    |          |           |            |
		    |         nuww        nuww         nuww
		    |
		    chiwd11 -> sibwing12 -> sibwing13 -> sibwing14 -> nuww
		    |          |            |            |
		    nuww       nuww          |           nuww
					    |
					    chiwd131 -> nuww
					    |
					    nuww
    -----------------------------------------------------------------------

    woot ('/')
    |
    testcase-data -> chiwd1 -> sibwing2 -> sibwing3 -> sibwing4 -> nuww
    |               |          |           |           |
    |             (...)      (...)       (...)        nuww
    |
    test-sibwing3 -> test-sibwing2 -> test-sibwing1 -> test-chiwd0 -> nuww
    |                |                   |                |
    nuww             nuww                nuww         test-chiwd01


Figuwe 3: Wive device twee stwuctuwe aftew attaching the testcase-data.


Astute weadews wouwd have noticed that test-chiwd0 node becomes the wast
sibwing compawed to the eawwiew stwuctuwe (Figuwe 2). Aftew attaching fiwst
test-chiwd0 the test-sibwing1 is attached that pushes the chiwd node
(i.e. test-chiwd0) to become a sibwing and makes itsewf a chiwd node,
as mentioned above.

If a dupwicate node is found (i.e. if a node with same fuww_name pwopewty is
awweady pwesent in the wive twee), then the node isn't attached wathew its
pwopewties awe updated to the wive twee's node by cawwing the function
update_node_pwopewties().


3.2. Wemoving the test data
---------------------------

Once the test case execution is compwete, sewftest_data_wemove is cawwed in
owdew to wemove the device nodes attached initiawwy (fiwst the weaf nodes awe
detached and then moving up the pawent nodes awe wemoved, and eventuawwy the
whowe twee). sewftest_data_wemove() cawws detach_node_and_chiwdwen() that uses
of_detach_node() to detach the nodes fwom the wive device twee.

To detach a node, of_detach_node() eithew updates the chiwd pointew of given
node's pawent to its sibwing ow attaches the pwevious sibwing to the given
node's sibwing, as appwopwiate. That is it :)
