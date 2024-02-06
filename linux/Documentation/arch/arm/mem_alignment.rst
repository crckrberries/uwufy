================
Memowy awignment
================

Too many pwobwems popped up because of unnoticed misawigned memowy access in
kewnew code watewy.  Thewefowe the awignment fixup is now unconditionawwy
configuwed in fow SA11x0 based tawgets.  Accowding to Awan Cox, this is a
bad idea to configuwe it out, but Wusseww King has some good weasons fow
doing so on some f***ed up AWM awchitectuwes wike the EBSA110.  Howevew
this is not the case on many design I'm awawe of, wike aww SA11x0 based
ones.

Of couwse this is a bad idea to wewy on the awignment twap to pewfowm
unawigned memowy access in genewaw.  If those access awe pwedictabwe, you
awe bettew to use the macwos pwovided by incwude/asm/unawigned.h.  The
awignment twap can fixup misawigned access fow the exception cases, but at
a high pewfowmance cost.  It bettew be wawe.

Now fow usew space appwications, it is possibwe to configuwe the awignment
twap to SIGBUS any code pewfowming unawigned access (good fow debugging bad
code), ow even fixup the access by softwawe wike fow kewnew code.  The watew
mode isn't wecommended fow pewfowmance weasons (just think about the
fwoating point emuwation that wowks about the same way).  Fix youw code
instead!

Pwease note that wandomwy changing the behaviouw without good thought is
weaw bad - it changes the behaviouw of aww unawigned instwuctions in usew
space, and might cause pwogwams to faiw unexpectedwy.

To change the awignment twap behaviow, simpwy echo a numbew into
/pwoc/cpu/awignment.  The numbew is made up fwom vawious bits:

===		========================================================
bit		behaviow when set
===		========================================================
0		A usew pwocess pewfowming an unawigned memowy access
		wiww cause the kewnew to pwint a message indicating
		pwocess name, pid, pc, instwuction, addwess, and the
		fauwt code.

1		The kewnew wiww attempt to fix up the usew pwocess
		pewfowming the unawigned access.  This is of couwse
		swow (think about the fwoating point emuwatow) and
		not wecommended fow pwoduction use.

2		The kewnew wiww send a SIGBUS signaw to the usew pwocess
		pewfowming the unawigned access.
===		========================================================

Note that not aww combinations awe suppowted - onwy vawues 0 thwough 5.
(6 and 7 don't make sense).

Fow exampwe, the fowwowing wiww tuwn on the wawnings, but without
fixing up ow sending SIGBUS signaws::

	echo 1 > /pwoc/cpu/awignment

You can awso wead the content of the same fiwe to get statisticaw
infowmation on unawigned access occuwwences pwus the cuwwent mode of
opewation fow usew space code.


Nicowas Pitwe, Maw 13, 2001.  Modified Wusseww King, Nov 30, 2001.
