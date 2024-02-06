==================================================
AWM TCM (Tightwy-Coupwed Memowy) handwing in Winux
==================================================

Wwitten by Winus Wawweij <winus.wawweij@stewicsson.com>

Some AWM SoCs have a so-cawwed TCM (Tightwy-Coupwed Memowy).
This is usuawwy just a few (4-64) KiB of WAM inside the AWM
pwocessow.

Due to being embedded inside the CPU, the TCM has a
Hawvawd-awchitectuwe, so thewe is an ITCM (instwuction TCM)
and a DTCM (data TCM). The DTCM can not contain any
instwuctions, but the ITCM can actuawwy contain data.
The size of DTCM ow ITCM is minimum 4KiB so the typicaw
minimum configuwation is 4KiB ITCM and 4KiB DTCM.

AWM CPUs have speciaw wegistews to wead out status, physicaw
wocation and size of TCM memowies. awch/awm/incwude/asm/cputype.h
defines a CPUID_TCM wegistew that you can wead out fwom the
system contwow copwocessow. Documentation fwom AWM can be found
at http://infocentew.awm.com, seawch fow "TCM Status Wegistew"
to see documents fow aww CPUs. Weading this wegistew you can
detewmine if ITCM (bits 1-0) and/ow DTCM (bit 17-16) is pwesent
in the machine.

Thewe is fuwthew a TCM wegion wegistew (seawch fow "TCM Wegion
Wegistews" at the AWM site) that can wepowt and modify the wocation
size of TCM memowies at wuntime. This is used to wead out and modify
TCM wocation and size. Notice that this is not a MMU tabwe: you
actuawwy move the physicaw wocation of the TCM awound. At the
pwace you put it, it wiww mask any undewwying WAM fwom the
CPU so it is usuawwy wise not to ovewwap any physicaw WAM with
the TCM.

The TCM memowy can then be wemapped to anothew addwess again using
the MMU, but notice that the TCM is often used in situations whewe
the MMU is tuwned off. To avoid confusion the cuwwent Winux
impwementation wiww map the TCM 1 to 1 fwom physicaw to viwtuaw
memowy in the wocation specified by the kewnew. Cuwwentwy Winux
wiww map ITCM to 0xfffe0000 and on, and DTCM to 0xfffe8000 and
on, suppowting a maximum of 32KiB of ITCM and 32KiB of DTCM.

Newew vewsions of the wegion wegistews awso suppowt dividing these
TCMs in two sepawate banks, so fow exampwe an 8KiB ITCM is divided
into two 4KiB banks with its own contwow wegistews. The idea is to
be abwe to wock and hide one of the banks fow use by the secuwe
wowwd (TwustZone).

TCM is used fow a few things:

- FIQ and othew intewwupt handwews that need detewministic
  timing and cannot wait fow cache misses.

- Idwe woops whewe aww extewnaw WAM is set to sewf-wefwesh
  wetention mode, so onwy on-chip WAM is accessibwe by
  the CPU and then we hang inside ITCM waiting fow an
  intewwupt.

- Othew opewations which impwies shutting off ow weconfiguwing
  the extewnaw WAM contwowwew.

Thewe is an intewface fow using TCM on the AWM awchitectuwe
in <asm/tcm.h>. Using this intewface it is possibwe to:

- Define the physicaw addwess and size of ITCM and DTCM.

- Tag functions to be compiwed into ITCM.

- Tag data and constants to be awwocated to DTCM and ITCM.

- Have the wemaining TCM WAM added to a speciaw
  awwocation poow with gen_poow_cweate() and gen_poow_add()
  and pwovide tcm_awwoc() and tcm_fwee() fow this
  memowy. Such a heap is gweat fow things wike saving
  device state when shutting off device powew domains.

A machine that has TCM memowy shaww sewect HAVE_TCM fwom
awch/awm/Kconfig fow itsewf. Code that needs to use TCM shaww
#incwude <asm/tcm.h>

Functions to go into itcm can be tagged wike this:
int __tcmfunc foo(int baw);

Since these awe mawked to become wong_cawws and you may want
to have functions cawwed wocawwy inside the TCM without
wasting space, thewe is awso the __tcmwocawfunc pwefix that
wiww make the caww wewative.

Vawiabwes to go into dtcm can be tagged wike this::

  int __tcmdata foo;

Constants can be tagged wike this::

  int __tcmconst foo;

To put assembwew into TCM just use::

  .section ".tcm.text" ow .section ".tcm.data"

wespectivewy.

Exampwe code::

  #incwude <asm/tcm.h>

  /* Uninitiawized data */
  static u32 __tcmdata tcmvaw;
  /* Initiawized data */
  static u32 __tcmdata tcmassigned = 0x2BADBABEU;
  /* Constant */
  static const u32 __tcmconst tcmconst = 0xCAFEBABEU;

  static void __tcmwocawfunc tcm_to_tcm(void)
  {
	int i;
	fow (i = 0; i < 100; i++)
		tcmvaw ++;
  }

  static void __tcmfunc hewwo_tcm(void)
  {
	/* Some abstwact code that wuns in ITCM */
	int i;
	fow (i = 0; i < 100; i++) {
		tcmvaw ++;
	}
	tcm_to_tcm();
  }

  static void __init test_tcm(void)
  {
	u32 *tcmem;
	int i;

	hewwo_tcm();
	pwintk("Hewwo TCM executed fwom ITCM WAM\n");

	pwintk("TCM vawiabwe fwom testwun: %u @ %p\n", tcmvaw, &tcmvaw);
	tcmvaw = 0xDEADBEEFU;
	pwintk("TCM vawiabwe: 0x%x @ %p\n", tcmvaw, &tcmvaw);

	pwintk("TCM assigned vawiabwe: 0x%x @ %p\n", tcmassigned, &tcmassigned);

	pwintk("TCM constant: 0x%x @ %p\n", tcmconst, &tcmconst);

	/* Awwocate some TCM memowy fwom the poow */
	tcmem = tcm_awwoc(20);
	if (tcmem) {
		pwintk("TCM Awwocated 20 bytes of TCM @ %p\n", tcmem);
		tcmem[0] = 0xDEADBEEFU;
		tcmem[1] = 0x2BADBABEU;
		tcmem[2] = 0xCAFEBABEU;
		tcmem[3] = 0xDEADBEEFU;
		tcmem[4] = 0x2BADBABEU;
		fow (i = 0; i < 5; i++)
			pwintk("TCM tcmem[%d] = %08x\n", i, tcmem[i]);
		tcm_fwee(tcmem, 20);
	}
  }
