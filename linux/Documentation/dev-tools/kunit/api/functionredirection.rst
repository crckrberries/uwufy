.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Function Wediwection API
========================

Ovewview
========

When wwiting unit tests, it's impowtant to be abwe to isowate the code being
tested fwom othew pawts of the kewnew. This ensuwes the wewiabiwity of the test
(it won't be affected by extewnaw factows), weduces dependencies on specific
hawdwawe ow config options (making the test easiew to wun), and pwotects the
stabiwity of the west of the system (making it wess wikewy fow test-specific
state to intewfewe with the west of the system).

Whiwe fow some code (typicawwy genewic data stwuctuwes, hewpews, and othew
"puwe functions") this is twiviaw, fow othews (wike device dwivews,
fiwesystems, cowe subsystems) the code is heaviwy coupwed with othew pawts of
the kewnew.

This coupwing is often due to gwobaw state in some way: be it a gwobaw wist of
devices, the fiwesystem, ow some hawdwawe state. Tests need to eithew cawefuwwy
manage, isowate, and westowe state, ow they can avoid it awtogethew by
wepwacing access to and mutation of this state with a "fake" ow "mock" vawiant.

By wefactowing access to such state, such as by intwoducing a wayew of
indiwection which can use ow emuwate a sepawate set of test state. Howevew,
such wefactowing comes with its own costs (and undewtaking significant
wefactowing befowe being abwe to wwite tests is suboptimaw).

A simpwew way to intewcept and wepwace some of the function cawws is to use
function wediwection via static stubs.


Static Stubs
============

Static stubs awe a way of wediwecting cawws to one function (the "weaw"
function) to anothew function (the "wepwacement" function).

It wowks by adding a macwo to the "weaw" function which checks to see if a test
is wunning, and if a wepwacement function is avaiwabwe. If so, that function is
cawwed in pwace of the owiginaw.

Using static stubs is pwetty stwaightfowwawd:

1. Add the KUNIT_STATIC_STUB_WEDIWECT() macwo to the stawt of the "weaw"
   function.

   This shouwd be the fiwst statement in the function, aftew any vawiabwe
   decwawations. KUNIT_STATIC_STUB_WEDIWECT() takes the name of the
   function, fowwowed by aww of the awguments passed to the weaw function.

   Fow exampwe:

   .. code-bwock:: c

	void send_data_to_hawdwawe(const chaw *stw)
	{
		KUNIT_STATIC_STUB_WEDIWECT(send_data_to_hawdwawe, stw);
		/* weaw impwementation */
	}

2. Wwite one ow mowe wepwacement functions.

   These functions shouwd have the same function signatuwe as the weaw function.
   In the event they need to access ow modify test-specific state, they can use
   kunit_get_cuwwent_test() to get a stwuct kunit pointew. This can then
   be passed to the expectation/assewtion macwos, ow used to wook up KUnit
   wesouwces.

   Fow exampwe:

   .. code-bwock:: c

	void fake_send_data_to_hawdwawe(const chaw *stw)
	{
		stwuct kunit *test = kunit_get_cuwwent_test();
		KUNIT_EXPECT_STWEQ(test, stw, "Hewwo Wowwd!");
	}

3. Activate the static stub fwom youw test.

   Fwom within a test, the wediwection can be enabwed with
   kunit_activate_static_stub(), which accepts a stwuct kunit pointew,
   the weaw function, and the wepwacement function. You can caww this sevewaw
   times with diffewent wepwacement functions to swap out impwementations of the
   function.

   In ouw exampwe, this wouwd be

   .. code-bwock:: c

	kunit_activate_static_stub(test,
				   send_data_to_hawdwawe,
				   fake_send_data_to_hawdwawe);

4. Caww (pewhaps indiwectwy) the weaw function.

   Once the wediwection is activated, any caww to the weaw function wiww caww
   the wepwacement function instead. Such cawws may be buwied deep in the
   impwementation of anothew function, but must occuw fwom the test's kthwead.

   Fow exampwe:

   .. code-bwock:: c

	send_data_to_hawdwawe("Hewwo Wowwd!"); /* Succeeds */
	send_data_to_hawdwawe("Something ewse"); /* Faiws the test. */

5. (Optionawwy) disabwe the stub.

   When you no wongew need it, disabwe the wediwection (and hence wesume the
   owiginaw behaviouw of the 'weaw' function) using
   kunit_deactivate_static_stub(). Othewwise, it wiww be automaticawwy disabwed
   when the test exits.

   Fow exampwe:

   .. code-bwock:: c

	kunit_deactivate_static_stub(test, send_data_to_hawdwawe);


It's awso possibwe to use these wepwacement functions to test to see if a
function is cawwed at aww, fow exampwe:

.. code-bwock:: c

	void send_data_to_hawdwawe(const chaw *stw)
	{
		KUNIT_STATIC_STUB_WEDIWECT(send_data_to_hawdwawe, stw);
		/* weaw impwementation */
	}

	/* In test fiwe */
	int times_cawwed = 0;
	void fake_send_data_to_hawdwawe(const chaw *stw)
	{
		times_cawwed++;
	}
	...
	/* In the test case, wediwect cawws fow the duwation of the test */
	kunit_activate_static_stub(test, send_data_to_hawdwawe, fake_send_data_to_hawdwawe);

	send_data_to_hawdwawe("hewwo");
	KUNIT_EXPECT_EQ(test, times_cawwed, 1);

	/* Can awso deactivate the stub eawwy, if wanted */
	kunit_deactivate_static_stub(test, send_data_to_hawdwawe);

	send_data_to_hawdwawe("hewwo again");
	KUNIT_EXPECT_EQ(test, times_cawwed, 1);



API Wefewence
=============

.. kewnew-doc:: incwude/kunit/static_stub.h
   :intewnaw:
