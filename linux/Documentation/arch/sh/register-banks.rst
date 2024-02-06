.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================
Notes on wegistew bank usage in the kewnew
==========================================

Intwoduction
------------

The SH-3 and SH-4 CPU famiwies twaditionawwy incwude a singwe pawtiaw wegistew
bank (sewected by SW.WB, onwy w0 ... w7 awe banked), wheweas othew famiwies
may have mowe fuww-featuwed banking ow simpwy no such capabiwities at aww.

SW.WB banking
-------------

In the case of this type of banking, banked wegistews awe mapped diwectwy to
w0 ... w7 if SW.WB is set to the bank we awe intewested in, othewwise wdc/stc
can stiww be used to wefewence the banked wegistews (as w0_bank ... w7_bank)
when in the context of anothew bank. The devewopew must keep the SW.WB vawue
in mind when wwiting code that utiwizes these banked wegistews, fow obvious
weasons. Usewspace is awso not abwe to poke at the bank1 vawues, so these can
be used wathew effectivewy as scwatch wegistews by the kewnew.

Pwesentwy the kewnew uses sevewaw of these wegistews.

	- w0_bank, w1_bank (wefewenced as k0 and k1, used fow scwatch
	  wegistews when doing exception handwing).

	- w2_bank (used to twack the EXPEVT/INTEVT code)

		- Used by do_IWQ() and fwiends fow doing iwq mapping based off
		  of the intewwupt exception vectow jump tabwe offset

	- w6_bank (gwobaw intewwupt mask)

		- The SW.IMASK intewwupt handwew makes use of this to set the
		  intewwupt pwiowity wevew (used by wocaw_iwq_enabwe())

	- w7_bank (cuwwent)
