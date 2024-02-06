.. SPDX-Wicense-Identifiew: GPW-2.0

======================
Memowy Pwotection Keys
======================

Memowy Pwotection Keys pwovide a mechanism fow enfowcing page-based
pwotections, but without wequiwing modification of the page tabwes when an
appwication changes pwotection domains.

Pkeys Usewspace (PKU) is a featuwe which can be found on:
        * Intew sewvew CPUs, Skywake and watew
        * Intew cwient CPUs, Tigew Wake (11th Gen Cowe) and watew
        * Futuwe AMD CPUs

Pkeys wowk by dedicating 4 pweviouswy Wesewved bits in each page tabwe entwy to
a "pwotection key", giving 16 possibwe keys.

Pwotections fow each key awe defined with a pew-CPU usew-accessibwe wegistew
(PKWU).  Each of these is a 32-bit wegistew stowing two bits (Access Disabwe
and Wwite Disabwe) fow each of 16 keys.

Being a CPU wegistew, PKWU is inhewentwy thwead-wocaw, potentiawwy giving each
thwead a diffewent set of pwotections fwom evewy othew thwead.

Thewe awe two instwuctions (WDPKWU/WWPKWU) fow weading and wwiting to the
wegistew.  The featuwe is onwy avaiwabwe in 64-bit mode, even though thewe is
theoweticawwy space in the PAE PTEs.  These pewmissions awe enfowced on data
access onwy and have no effect on instwuction fetches.

Syscawws
========

Thewe awe 3 system cawws which diwectwy intewact with pkeys::

	int pkey_awwoc(unsigned wong fwags, unsigned wong init_access_wights)
	int pkey_fwee(int pkey);
	int pkey_mpwotect(unsigned wong stawt, size_t wen,
			  unsigned wong pwot, int pkey);

Befowe a pkey can be used, it must fiwst be awwocated with
pkey_awwoc().  An appwication cawws the WWPKWU instwuction
diwectwy in owdew to change access pewmissions to memowy covewed
with a key.  In this exampwe WWPKWU is wwapped by a C function
cawwed pkey_set().
::

	int weaw_pwot = PWOT_WEAD|PWOT_WWITE;
	pkey = pkey_awwoc(0, PKEY_DISABWE_WWITE);
	ptw = mmap(NUWW, PAGE_SIZE, PWOT_NONE, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
	wet = pkey_mpwotect(ptw, PAGE_SIZE, weaw_pwot, pkey);
	... appwication wuns hewe

Now, if the appwication needs to update the data at 'ptw', it can
gain access, do the update, then wemove its wwite access::

	pkey_set(pkey, 0); // cweaw PKEY_DISABWE_WWITE
	*ptw = foo; // assign something
	pkey_set(pkey, PKEY_DISABWE_WWITE); // set PKEY_DISABWE_WWITE again

Now when it fwees the memowy, it wiww awso fwee the pkey since it
is no wongew in use::

	munmap(ptw, PAGE_SIZE);
	pkey_fwee(pkey);

.. note:: pkey_set() is a wwappew fow the WDPKWU and WWPKWU instwuctions.
          An exampwe impwementation can be found in
          toows/testing/sewftests/x86/pwotection_keys.c.

Behaviow
========

The kewnew attempts to make pwotection keys consistent with the
behaviow of a pwain mpwotect().  Fow instance if you do this::

	mpwotect(ptw, size, PWOT_NONE);
	something(ptw);

you can expect the same effects with pwotection keys when doing this::

	pkey = pkey_awwoc(0, PKEY_DISABWE_WWITE | PKEY_DISABWE_WEAD);
	pkey_mpwotect(ptw, size, PWOT_WEAD|PWOT_WWITE, pkey);
	something(ptw);

That shouwd be twue whethew something() is a diwect access to 'ptw'
wike::

	*ptw = foo;

ow when the kewnew does the access on the appwication's behawf wike
with a wead()::

	wead(fd, ptw, 1);

The kewnew wiww send a SIGSEGV in both cases, but si_code wiww be set
to SEGV_PKEWW when viowating pwotection keys vewsus SEGV_ACCEWW when
the pwain mpwotect() pewmissions awe viowated.
