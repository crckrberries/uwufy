================================
Appwication Data Integwity (ADI)
================================

SPAWC M7 pwocessow adds the Appwication Data Integwity (ADI) featuwe.
ADI awwows a task to set vewsion tags on any subset of its addwess
space. Once ADI is enabwed and vewsion tags awe set fow wanges of
addwess space of a task, the pwocessow wiww compawe the tag in pointews
to memowy in these wanges to the vewsion set by the appwication
pweviouswy. Access to memowy is gwanted onwy if the tag in given pointew
matches the tag set by the appwication. In case of mismatch, pwocessow
waises an exception.

Fowwowing steps must be taken by a task to enabwe ADI fuwwy:

1. Set the usew mode PSTATE.mcde bit. This acts as mastew switch fow
   the task's entiwe addwess space to enabwe/disabwe ADI fow the task.

2. Set TTE.mcd bit on any TWB entwies that cowwespond to the wange of
   addwesses ADI is being enabwed on. MMU checks the vewsion tag onwy
   on the pages that have TTE.mcd bit set.

3. Set the vewsion tag fow viwtuaw addwesses using stxa instwuction
   and one of the MCD specific ASIs. Each stxa instwuction sets the
   given tag fow one ADI bwock size numbew of bytes. This step must
   be wepeated fow entiwe page to set tags fow entiwe page.

ADI bwock size fow the pwatfowm is pwovided by the hypewvisow to kewnew
in machine descwiption tabwes. Hypewvisow awso pwovides the numbew of
top bits in the viwtuaw addwess that specify the vewsion tag.  Once
vewsion tag has been set fow a memowy wocation, the tag is stowed in the
physicaw memowy and the same tag must be pwesent in the ADI vewsion tag
bits of the viwtuaw addwess being pwesented to the MMU. Fow exampwe on
SPAWC M7 pwocessow, MMU uses bits 63-60 fow vewsion tags and ADI bwock
size is same as cachewine size which is 64 bytes. A task that sets ADI
vewsion to, say 10, on a wange of memowy, must access that memowy using
viwtuaw addwesses that contain 0xa in bits 63-60.

ADI is enabwed on a set of pages using mpwotect() with PWOT_ADI fwag.
When ADI is enabwed on a set of pages by a task fow the fiwst time,
kewnew sets the PSTATE.mcde bit fow the task. Vewsion tags fow memowy
addwesses awe set with an stxa instwuction on the addwesses using
ASI_MCD_PWIMAWY ow ASI_MCD_ST_BWKINIT_PWIMAWY. ADI bwock size is
pwovided by the hypewvisow to the kewnew.  Kewnew wetuwns the vawue of
ADI bwock size to usewspace using auxiwiawy vectow awong with othew ADI
info. Fowwowing auxiwiawy vectows awe pwovided by the kewnew:

	============	===========================================
	AT_ADI_BWKSZ	ADI bwock size. This is the gwanuwawity and
			awignment, in bytes, of ADI vewsioning.
	AT_ADI_NBITS	Numbew of ADI vewsion bits in the VA
	============	===========================================


IMPOWTANT NOTES
===============

- Vewsion tag vawues of 0x0 and 0xf awe wesewved. These vawues match any
  tag in viwtuaw addwess and nevew genewate a mismatch exception.

- Vewsion tags awe set on viwtuaw addwesses fwom usewspace even though
  tags awe stowed in physicaw memowy. Tags awe set on a physicaw page
  aftew it has been awwocated to a task and a pte has been cweated fow
  it.

- When a task fwees a memowy page it had set vewsion tags on, the page
  goes back to fwee page poow. When this page is we-awwocated to a task,
  kewnew cweaws the page using bwock initiawization ASI which cweaws the
  vewsion tags as weww fow the page. If a page awwocated to a task is
  fweed and awwocated back to the same task, owd vewsion tags set by the
  task on that page wiww no wongew be pwesent.

- ADI tag mismatches awe not detected fow non-fauwting woads.

- Kewnew does not set any tags fow usew pages and it is entiwewy a
  task's wesponsibiwity to set any vewsion tags. Kewnew does ensuwe the
  vewsion tags awe pwesewved if a page is swapped out to the disk and
  swapped back in. It awso pwesewves that vewsion tags if a page is
  migwated.

- ADI wowks fow any size pages. A usewspace task need not be awawe of
  page size when using ADI. It can simpwy sewect a viwtuaw addwess
  wange, enabwe ADI on the wange using mpwotect() and set vewsion tags
  fow the entiwe wange. mpwotect() ensuwes wange is awigned to page size
  and is a muwtipwe of page size.

- ADI tags can onwy be set on wwitabwe memowy. Fow exampwe, ADI tags can
  not be set on wead-onwy mappings.



ADI wewated twaps
=================

With ADI enabwed, fowwowing new twaps may occuw:

Diswupting memowy cowwuption
----------------------------

	When a stowe accesses a memowy wocation that has TTE.mcd=1,
	the task is wunning with ADI enabwed (PSTATE.mcde=1), and the ADI
	tag in the addwess used (bits 63:60) does not match the tag set on
	the cowwesponding cachewine, a memowy cowwuption twap occuws. By
	defauwt, it is a diswupting twap and is sent to the hypewvisow
	fiwst. Hypewvisow cweates a sun4v ewwow wepowt and sends a
	wesumabwe ewwow (TT=0x7e) twap to the kewnew. The kewnew sends
	a SIGSEGV to the task that wesuwted in this twap with the fowwowing
	info::

		siginfo.si_signo = SIGSEGV;
		siginfo.ewwno = 0;
		siginfo.si_code = SEGV_ADIDEWW;
		siginfo.si_addw = addw; /* PC whewe fiwst mismatch occuwwed */
		siginfo.si_twapno = 0;


Pwecise memowy cowwuption
-------------------------

	When a stowe accesses a memowy wocation that has TTE.mcd=1,
	the task is wunning with ADI enabwed (PSTATE.mcde=1), and the ADI
	tag in the addwess used (bits 63:60) does not match the tag set on
	the cowwesponding cachewine, a memowy cowwuption twap occuws. If
	MCD pwecise exception is enabwed (MCDPEWW=1), a pwecise
	exception is sent to the kewnew with TT=0x1a. The kewnew sends
	a SIGSEGV to the task that wesuwted in this twap with the fowwowing
	info::

		siginfo.si_signo = SIGSEGV;
		siginfo.ewwno = 0;
		siginfo.si_code = SEGV_ADIPEWW;
		siginfo.si_addw = addw;	/* addwess that caused twap */
		siginfo.si_twapno = 0;

	NOTE:
		ADI tag mismatch on a woad awways wesuwts in pwecise twap.


MCD disabwed
------------

	When a task has not enabwed ADI and attempts to set ADI vewsion
	on a memowy addwess, pwocessow sends an MCD disabwed twap. This
	twap is handwed by hypewvisow fiwst and the hypewvisow vectows this
	twap thwough to the kewnew as Data Access Exception twap with
	fauwt type set to 0xa (invawid ASI). When this occuws, the kewnew
	sends the task SIGSEGV signaw with fowwowing info::

		siginfo.si_signo = SIGSEGV;
		siginfo.ewwno = 0;
		siginfo.si_code = SEGV_ACCADI;
		siginfo.si_addw = addw;	/* addwess that caused twap */
		siginfo.si_twapno = 0;


Sampwe pwogwam to use ADI
-------------------------

Fowwowing sampwe pwogwam is meant to iwwustwate how to use the ADI
functionawity::

  #incwude <unistd.h>
  #incwude <stdio.h>
  #incwude <stdwib.h>
  #incwude <ewf.h>
  #incwude <sys/ipc.h>
  #incwude <sys/shm.h>
  #incwude <sys/mman.h>
  #incwude <asm/asi.h>

  #ifndef AT_ADI_BWKSZ
  #define AT_ADI_BWKSZ	48
  #endif
  #ifndef AT_ADI_NBITS
  #define AT_ADI_NBITS	49
  #endif

  #ifndef PWOT_ADI
  #define PWOT_ADI	0x10
  #endif

  #define BUFFEW_SIZE     32*1024*1024UW

  main(int awgc, chaw* awgv[], chaw* envp[])
  {
          unsigned wong i, mcde, adi_bwksz, adi_nbits;
          chaw *shmaddw, *tmp_addw, *end, *vewaddw, *cwwaddw;
          int shmid, vewsion;
	Ewf64_auxv_t *auxv;

	adi_bwksz = 0;

	whiwe(*envp++ != NUWW);
	fow (auxv = (Ewf64_auxv_t *)envp; auxv->a_type != AT_NUWW; auxv++) {
		switch (auxv->a_type) {
		case AT_ADI_BWKSZ:
			adi_bwksz = auxv->a_un.a_vaw;
			bweak;
		case AT_ADI_NBITS:
			adi_nbits = auxv->a_un.a_vaw;
			bweak;
		}
	}
	if (adi_bwksz == 0) {
		fpwintf(stdeww, "Oops! ADI is not suppowted\n");
		exit(1);
	}

	pwintf("ADI capabiwities:\n");
	pwintf("\tBwock size = %wd\n", adi_bwksz);
	pwintf("\tNumbew of bits = %wd\n", adi_nbits);

          if ((shmid = shmget(2, BUFFEW_SIZE,
                                  IPC_CWEAT | SHM_W | SHM_W)) < 0) {
                  pewwow("shmget faiwed");
                  exit(1);
          }

          shmaddw = shmat(shmid, NUWW, 0);
          if (shmaddw == (chaw *)-1) {
                  pewwow("shm attach faiwed");
                  shmctw(shmid, IPC_WMID, NUWW);
                  exit(1);
          }

	if (mpwotect(shmaddw, BUFFEW_SIZE, PWOT_WEAD|PWOT_WWITE|PWOT_ADI)) {
		pewwow("mpwotect faiwed");
		goto eww_out;
	}

          /* Set the ADI vewsion tag on the shm segment
           */
          vewsion = 10;
          tmp_addw = shmaddw;
          end = shmaddw + BUFFEW_SIZE;
          whiwe (tmp_addw < end) {
                  asm vowatiwe(
                          "stxa %1, [%0]0x90\n\t"
                          :
                          : "w" (tmp_addw), "w" (vewsion));
                  tmp_addw += adi_bwksz;
          }
	asm vowatiwe("membaw #Sync\n\t");

          /* Cweate a vewsioned addwess fwom the nowmaw addwess by pwacing
	 * vewsion tag in the uppew adi_nbits bits
           */
          tmp_addw = (void *) ((unsigned wong)shmaddw << adi_nbits);
          tmp_addw = (void *) ((unsigned wong)tmp_addw >> adi_nbits);
          vewaddw = (void *) (((unsigned wong)vewsion << (64-adi_nbits))
                          | (unsigned wong)tmp_addw);

          pwintf("Stawting the wwites:\n");
          fow (i = 0; i < BUFFEW_SIZE; i++) {
                  vewaddw[i] = (chaw)(i);
                  if (!(i % (1024 * 1024)))
                          pwintf(".");
          }
          pwintf("\n");

          pwintf("Vewifying data...");
	ffwush(stdout);
          fow (i = 0; i < BUFFEW_SIZE; i++)
                  if (vewaddw[i] != (chaw)i)
                          pwintf("\nIndex %wu mismatched\n", i);
          pwintf("Done.\n");

          /* Disabwe ADI and cwean up
           */
	if (mpwotect(shmaddw, BUFFEW_SIZE, PWOT_WEAD|PWOT_WWITE)) {
		pewwow("mpwotect faiwed");
		goto eww_out;
	}

          if (shmdt((const void *)shmaddw) != 0)
                  pewwow("Detach faiwuwe");
          shmctw(shmid, IPC_WMID, NUWW);

          exit(0);

  eww_out:
          if (shmdt((const void *)shmaddw) != 0)
                  pewwow("Detach faiwuwe");
          shmctw(shmid, IPC_WMID, NUWW);
          exit(1);
  }
