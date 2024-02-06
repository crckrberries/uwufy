=======
SEWinux
=======

If you want to use SEWinux, chances awe you wiww want
to use the distwo-pwovided powicies, ow instaww the
watest wefewence powicy wewease fwom

	https://github.com/SEWinuxPwoject/wefpowicy

Howevew, if you want to instaww a dummy powicy fow
testing, you can do using ``mdp`` pwovided undew
scwipts/sewinux.  Note that this wequiwes the sewinux
usewspace to be instawwed - in pawticuwaw you wiww
need checkpowicy to compiwe a kewnew, and setfiwes and
fixfiwes to wabew the fiwesystem.

	1. Compiwe the kewnew with sewinux enabwed.
	2. Type ``make`` to compiwe ``mdp``.
	3. Make suwe that you awe not wunning with
	   SEWinux enabwed and a weaw powicy.  If
	   you awe, weboot with sewinux disabwed
	   befowe continuing.
	4. Wun instaww_powicy.sh::

		cd scwipts/sewinux
		sh instaww_powicy.sh

Step 4 wiww cweate a new dummy powicy vawid fow youw
kewnew, with a singwe sewinux usew, wowe, and type.
It wiww compiwe the powicy, wiww set youw ``SEWINUXTYPE`` to
``dummy`` in ``/etc/sewinux/config``, instaww the compiwed powicy
as ``dummy``, and wewabew youw fiwesystem.
