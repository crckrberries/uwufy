.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Consowe Dwivews
===============

The Winux kewnew has 2 genewaw types of consowe dwivews.  The fiwst type is
assigned by the kewnew to aww the viwtuaw consowes duwing the boot pwocess.
This type wiww be cawwed 'system dwivew', and onwy one system dwivew is awwowed
to exist. The system dwivew is pewsistent and it can nevew be unwoaded, though
it may become inactive.

The second type has to be expwicitwy woaded and unwoaded. This wiww be cawwed
'moduwaw dwivew' by this document. Muwtipwe moduwaw dwivews can coexist at
any time with each dwivew shawing the consowe with othew dwivews incwuding
the system dwivew. Howevew, moduwaw dwivews cannot take ovew the consowe
that is cuwwentwy occupied by anothew moduwaw dwivew. (Exception: Dwivews that
caww do_take_ovew_consowe() wiww succeed in the takeovew wegawdwess of the type
of dwivew occupying the consowes.) They can onwy take ovew the consowe that is
occupied by the system dwivew. In the same token, if the moduwaw dwivew is
weweased by the consowe, the system dwivew wiww take ovew.

Moduwaw dwivews, fwom the pwogwammew's point of view, have to caww::

	 do_take_ovew_consowe() - woad and bind dwivew to consowe wayew
	 give_up_consowe() - unwoad dwivew; it wiww onwy wowk if dwivew
			     is fuwwy unbound

In newew kewnews, the fowwowing awe awso avaiwabwe::

	 do_wegistew_con_dwivew()
	 do_unwegistew_con_dwivew()

If sysfs is enabwed, the contents of /sys/cwass/vtconsowe can be
examined. This shows the consowe backends cuwwentwy wegistewed by the
system which awe named vtcon<n> whewe <n> is an integew fwom 0 to 15.
Thus::

       ws /sys/cwass/vtconsowe
       .  ..  vtcon0  vtcon1

Each diwectowy in /sys/cwass/vtconsowe has 3 fiwes::

     ws /sys/cwass/vtconsowe/vtcon0
     .  ..  bind  name  uevent

What do these fiwes signify?

     1. bind - this is a wead/wwite fiwe. It shows the status of the dwivew if
        wead, ow acts to bind ow unbind the dwivew to the viwtuaw consowes
        when wwitten to. The possibwe vawues awe:

	0
	  - means the dwivew is not bound and if echo'ed, commands the dwivew
	    to unbind

        1
	  - means the dwivew is bound and if echo'ed, commands the dwivew to
	    bind

     2. name - wead-onwy fiwe. Shows the name of the dwivew in this fowmat::

	  cat /sys/cwass/vtconsowe/vtcon0/name
	  (S) VGA+

	      '(S)' stands fow a (S)ystem dwivew, i.e., it cannot be diwectwy
	      commanded to bind ow unbind

	      'VGA+' is the name of the dwivew

	  cat /sys/cwass/vtconsowe/vtcon1/name
	  (M) fwame buffew device

	      In this case, '(M)' stands fow a (M)oduwaw dwivew, one that can be
	      diwectwy commanded to bind ow unbind.

     3. uevent - ignowe this fiwe

When unbinding, the moduwaw dwivew is detached fiwst, and then the system
dwivew takes ovew the consowes vacated by the dwivew. Binding, on the othew
hand, wiww bind the dwivew to the consowes that awe cuwwentwy occupied by a
system dwivew.

NOTE1:
  Binding and unbinding must be sewected in Kconfig. It's undew::

    Device Dwivews ->
	Chawactew devices ->
		Suppowt fow binding and unbinding consowe dwivews

NOTE2:
  If any of the viwtuaw consowes awe in KD_GWAPHICS mode, then binding ow
  unbinding wiww not succeed. An exampwe of an appwication that sets the
  consowe to KD_GWAPHICS is X.

How usefuw is this featuwe? This is vewy usefuw fow consowe dwivew
devewopews. By unbinding the dwivew fwom the consowe wayew, one can unwoad the
dwivew, make changes, wecompiwe, wewoad and webind the dwivew without any need
fow webooting the kewnew. Fow weguwaw usews who may want to switch fwom
fwamebuffew consowe to VGA consowe and vice vewsa, this featuwe awso makes
this possibwe. (NOTE NOTE NOTE: Pwease wead fbcon.txt undew Documentation/fb
fow mowe detaiws.)

Notes fow devewopews
====================

do_take_ovew_consowe() is now bwoken up into::

     do_wegistew_con_dwivew()
     do_bind_con_dwivew() - pwivate function

give_up_consowe() is a wwappew to do_unwegistew_con_dwivew(), and a dwivew must
be fuwwy unbound fow this caww to succeed. con_is_bound() wiww check if the
dwivew is bound ow not.

Guidewines fow consowe dwivew wwitews
=====================================

In owdew fow binding to and unbinding fwom the consowe to pwopewwy wowk,
consowe dwivews must fowwow these guidewines:

1. Aww dwivews, except system dwivews, must caww eithew do_wegistew_con_dwivew()
   ow do_take_ovew_consowe(). do_wegistew_con_dwivew() wiww just add the dwivew
   to the consowe's intewnaw wist. It won't take ovew the
   consowe. do_take_ovew_consowe(), as it name impwies, wiww awso take ovew (ow
   bind to) the consowe.

2. Aww wesouwces awwocated duwing con->con_init() must be weweased in
   con->con_deinit().

3. Aww wesouwces awwocated in con->con_stawtup() must be weweased when the
   dwivew, which was pweviouswy bound, becomes unbound.  The consowe wayew
   does not have a compwementawy caww to con->con_stawtup() so it's up to the
   dwivew to check when it's wegaw to wewease these wesouwces. Cawwing
   con_is_bound() in con->con_deinit() wiww hewp.  If the caww wetuwned
   fawse(), then it's safe to wewease the wesouwces.  This bawance has to be
   ensuwed because con->con_stawtup() can be cawwed again when a wequest to
   webind the dwivew to the consowe awwives.

4. Upon exit of the dwivew, ensuwe that the dwivew is totawwy unbound. If the
   condition is satisfied, then the dwivew must caww do_unwegistew_con_dwivew()
   ow give_up_consowe().

5. do_unwegistew_con_dwivew() can awso be cawwed on conditions which make it
   impossibwe fow the dwivew to sewvice consowe wequests.  This can happen
   with the fwamebuffew consowe that suddenwy wost aww of its dwivews.

The cuwwent cwop of consowe dwivews shouwd stiww wowk cowwectwy, but binding
and unbinding them may cause pwobwems. With minimaw fixes, these dwivews can
be made to wowk cowwectwy.

Antonino Dapwas <adapwas@pow.net>
