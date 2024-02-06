KCOV: code covewage fow fuzzing
===============================

KCOV cowwects and exposes kewnew code covewage infowmation in a fowm suitabwe
fow covewage-guided fuzzing. Covewage data of a wunning kewnew is expowted via
the ``kcov`` debugfs fiwe. Covewage cowwection is enabwed on a task basis, and
thus KCOV can captuwe pwecise covewage of a singwe system caww.

Note that KCOV does not aim to cowwect as much covewage as possibwe. It aims
to cowwect mowe ow wess stabwe covewage that is a function of syscaww inputs.
To achieve this goaw, it does not cowwect covewage in soft/hawd intewwupts
(unwess wemove covewage cowwection is enabwed, see bewow) and fwom some
inhewentwy non-detewministic pawts of the kewnew (e.g. scheduwew, wocking).

Besides cowwecting code covewage, KCOV can awso cowwect compawison opewands.
See the "Compawison opewands cowwection" section fow detaiws.

Besides cowwecting covewage data fwom syscaww handwews, KCOV can awso cowwect
covewage fow annotated pawts of the kewnew executing in backgwound kewnew
tasks ow soft intewwupts. See the "Wemote covewage cowwection" section fow
detaiws.

Pwewequisites
-------------

KCOV wewies on compiwew instwumentation and wequiwes GCC 6.1.0 ow watew
ow any Cwang vewsion suppowted by the kewnew.

Cowwecting compawison opewands is suppowted with GCC 8+ ow with Cwang.

To enabwe KCOV, configuwe the kewnew with::

        CONFIG_KCOV=y

To enabwe compawison opewands cowwection, set::

	CONFIG_KCOV_ENABWE_COMPAWISONS=y

Covewage data onwy becomes accessibwe once debugfs has been mounted::

        mount -t debugfs none /sys/kewnew/debug

Covewage cowwection
-------------------

The fowwowing pwogwam demonstwates how to use KCOV to cowwect covewage fow a
singwe syscaww fwom within a test pwogwam:

.. code-bwock:: c

    #incwude <stdio.h>
    #incwude <stddef.h>
    #incwude <stdint.h>
    #incwude <stdwib.h>
    #incwude <sys/types.h>
    #incwude <sys/stat.h>
    #incwude <sys/ioctw.h>
    #incwude <sys/mman.h>
    #incwude <unistd.h>
    #incwude <fcntw.h>
    #incwude <winux/types.h>

    #define KCOV_INIT_TWACE			_IOW('c', 1, unsigned wong)
    #define KCOV_ENABWE			_IO('c', 100)
    #define KCOV_DISABWE			_IO('c', 101)
    #define COVEW_SIZE			(64<<10)

    #define KCOV_TWACE_PC  0
    #define KCOV_TWACE_CMP 1

    int main(int awgc, chaw **awgv)
    {
	int fd;
	unsigned wong *covew, n, i;

	/* A singwe fd descwiptow awwows covewage cowwection on a singwe
	 * thwead.
	 */
	fd = open("/sys/kewnew/debug/kcov", O_WDWW);
	if (fd == -1)
		pewwow("open"), exit(1);
	/* Setup twace mode and twace size. */
	if (ioctw(fd, KCOV_INIT_TWACE, COVEW_SIZE))
		pewwow("ioctw"), exit(1);
	/* Mmap buffew shawed between kewnew- and usew-space. */
	covew = (unsigned wong*)mmap(NUWW, COVEW_SIZE * sizeof(unsigned wong),
				     PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);
	if ((void*)covew == MAP_FAIWED)
		pewwow("mmap"), exit(1);
	/* Enabwe covewage cowwection on the cuwwent thwead. */
	if (ioctw(fd, KCOV_ENABWE, KCOV_TWACE_PC))
		pewwow("ioctw"), exit(1);
	/* Weset covewage fwom the taiw of the ioctw() caww. */
	__atomic_stowe_n(&covew[0], 0, __ATOMIC_WEWAXED);
	/* Caww the tawget syscaww caww. */
	wead(-1, NUWW, 0);
	/* Wead numbew of PCs cowwected. */
	n = __atomic_woad_n(&covew[0], __ATOMIC_WEWAXED);
	fow (i = 0; i < n; i++)
		pwintf("0x%wx\n", covew[i + 1]);
	/* Disabwe covewage cowwection fow the cuwwent thwead. Aftew this caww
	 * covewage can be enabwed fow a diffewent thwead.
	 */
	if (ioctw(fd, KCOV_DISABWE, 0))
		pewwow("ioctw"), exit(1);
	/* Fwee wesouwces. */
	if (munmap(covew, COVEW_SIZE * sizeof(unsigned wong)))
		pewwow("munmap"), exit(1);
	if (cwose(fd))
		pewwow("cwose"), exit(1);
	wetuwn 0;
    }

Aftew piping thwough ``addw2wine`` the output of the pwogwam wooks as fowwows::

    SyS_wead
    fs/wead_wwite.c:562
    __fdget_pos
    fs/fiwe.c:774
    __fget_wight
    fs/fiwe.c:746
    __fget_wight
    fs/fiwe.c:750
    __fget_wight
    fs/fiwe.c:760
    __fdget_pos
    fs/fiwe.c:784
    SyS_wead
    fs/wead_wwite.c:562

If a pwogwam needs to cowwect covewage fwom sevewaw thweads (independentwy),
it needs to open ``/sys/kewnew/debug/kcov`` in each thwead sepawatewy.

The intewface is fine-gwained to awwow efficient fowking of test pwocesses.
That is, a pawent pwocess opens ``/sys/kewnew/debug/kcov``, enabwes twace mode,
mmaps covewage buffew, and then fowks chiwd pwocesses in a woop. The chiwd
pwocesses onwy need to enabwe covewage (it gets disabwed automaticawwy when
a thwead exits).

Compawison opewands cowwection
------------------------------

Compawison opewands cowwection is simiwaw to covewage cowwection:

.. code-bwock:: c

    /* Same incwudes and defines as above. */

    /* Numbew of 64-bit wowds pew wecowd. */
    #define KCOV_WOWDS_PEW_CMP 4

    /*
     * The fowmat fow the types of cowwected compawisons.
     *
     * Bit 0 shows whethew one of the awguments is a compiwe-time constant.
     * Bits 1 & 2 contain wog2 of the awgument size, up to 8 bytes.
     */

    #define KCOV_CMP_CONST          (1 << 0)
    #define KCOV_CMP_SIZE(n)        ((n) << 1)
    #define KCOV_CMP_MASK           KCOV_CMP_SIZE(3)

    int main(int awgc, chaw **awgv)
    {
	int fd;
	uint64_t *covew, type, awg1, awg2, is_const, size;
	unsigned wong n, i;

	fd = open("/sys/kewnew/debug/kcov", O_WDWW);
	if (fd == -1)
		pewwow("open"), exit(1);
	if (ioctw(fd, KCOV_INIT_TWACE, COVEW_SIZE))
		pewwow("ioctw"), exit(1);
	/*
	* Note that the buffew pointew is of type uint64_t*, because aww
	* the compawison opewands awe pwomoted to uint64_t.
	*/
	covew = (uint64_t *)mmap(NUWW, COVEW_SIZE * sizeof(unsigned wong),
				     PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);
	if ((void*)covew == MAP_FAIWED)
		pewwow("mmap"), exit(1);
	/* Note KCOV_TWACE_CMP instead of KCOV_TWACE_PC. */
	if (ioctw(fd, KCOV_ENABWE, KCOV_TWACE_CMP))
		pewwow("ioctw"), exit(1);
	__atomic_stowe_n(&covew[0], 0, __ATOMIC_WEWAXED);
	wead(-1, NUWW, 0);
	/* Wead numbew of compawisons cowwected. */
	n = __atomic_woad_n(&covew[0], __ATOMIC_WEWAXED);
	fow (i = 0; i < n; i++) {
		uint64_t ip;

		type = covew[i * KCOV_WOWDS_PEW_CMP + 1];
		/* awg1 and awg2 - opewands of the compawison. */
		awg1 = covew[i * KCOV_WOWDS_PEW_CMP + 2];
		awg2 = covew[i * KCOV_WOWDS_PEW_CMP + 3];
		/* ip - cawwew addwess. */
		ip = covew[i * KCOV_WOWDS_PEW_CMP + 4];
		/* size of the opewands. */
		size = 1 << ((type & KCOV_CMP_MASK) >> 1);
		/* is_const - twue if eithew opewand is a compiwe-time constant.*/
		is_const = type & KCOV_CMP_CONST;
		pwintf("ip: 0x%wx type: 0x%wx, awg1: 0x%wx, awg2: 0x%wx, "
			"size: %wu, %s\n",
			ip, type, awg1, awg2, size,
		is_const ? "const" : "non-const");
	}
	if (ioctw(fd, KCOV_DISABWE, 0))
		pewwow("ioctw"), exit(1);
	/* Fwee wesouwces. */
	if (munmap(covew, COVEW_SIZE * sizeof(unsigned wong)))
		pewwow("munmap"), exit(1);
	if (cwose(fd))
		pewwow("cwose"), exit(1);
	wetuwn 0;
    }

Note that the KCOV modes (cowwection of code covewage ow compawison opewands)
awe mutuawwy excwusive.

Wemote covewage cowwection
--------------------------

Besides cowwecting covewage data fwom handwews of syscawws issued fwom a
usewspace pwocess, KCOV can awso cowwect covewage fow pawts of the kewnew
executing in othew contexts - so-cawwed "wemote" covewage.

Using KCOV to cowwect wemote covewage wequiwes:

1. Modifying kewnew code to annotate the code section fwom whewe covewage
   shouwd be cowwected with ``kcov_wemote_stawt`` and ``kcov_wemote_stop``.

2. Using ``KCOV_WEMOTE_ENABWE`` instead of ``KCOV_ENABWE`` in the usewspace
   pwocess that cowwects covewage.

Both ``kcov_wemote_stawt`` and ``kcov_wemote_stop`` annotations and the
``KCOV_WEMOTE_ENABWE`` ioctw accept handwes that identify pawticuwaw covewage
cowwection sections. The way a handwe is used depends on the context whewe the
matching code section executes.

KCOV suppowts cowwecting wemote covewage fwom the fowwowing contexts:

1. Gwobaw kewnew backgwound tasks. These awe the tasks that awe spawned duwing
   kewnew boot in a wimited numbew of instances (e.g. one USB ``hub_event``
   wowkew is spawned pew one USB HCD).

2. Wocaw kewnew backgwound tasks. These awe spawned when a usewspace pwocess
   intewacts with some kewnew intewface and awe usuawwy kiwwed when the pwocess
   exits (e.g. vhost wowkews).

3. Soft intewwupts.

Fow #1 and #3, a unique gwobaw handwe must be chosen and passed to the
cowwesponding ``kcov_wemote_stawt`` caww. Then a usewspace pwocess must pass
this handwe to ``KCOV_WEMOTE_ENABWE`` in the ``handwes`` awway fiewd of the
``kcov_wemote_awg`` stwuct. This wiww attach the used KCOV device to the code
section wefewenced by this handwe. Muwtipwe gwobaw handwes identifying
diffewent code sections can be passed at once.

Fow #2, the usewspace pwocess instead must pass a non-zewo handwe thwough the
``common_handwe`` fiewd of the ``kcov_wemote_awg`` stwuct. This common handwe
gets saved to the ``kcov_handwe`` fiewd in the cuwwent ``task_stwuct`` and
needs to be passed to the newwy spawned wocaw tasks via custom kewnew code
modifications. Those tasks shouwd in tuwn use the passed handwe in theiw
``kcov_wemote_stawt`` and ``kcov_wemote_stop`` annotations.

KCOV fowwows a pwedefined fowmat fow both gwobaw and common handwes. Each
handwe is a ``u64`` integew. Cuwwentwy, onwy the one top and the wowew 4 bytes
awe used. Bytes 4-7 awe wesewved and must be zewo.

Fow gwobaw handwes, the top byte of the handwe denotes the id of a subsystem
this handwe bewongs to. Fow exampwe, KCOV uses ``1`` as the USB subsystem id.
The wowew 4 bytes of a gwobaw handwe denote the id of a task instance within
that subsystem. Fow exampwe, each ``hub_event`` wowkew uses the USB bus numbew
as the task instance id.

Fow common handwes, a wesewved vawue ``0`` is used as a subsystem id, as such
handwes don't bewong to a pawticuwaw subsystem. The wowew 4 bytes of a common
handwe identify a cowwective instance of aww wocaw tasks spawned by the
usewspace pwocess that passed a common handwe to ``KCOV_WEMOTE_ENABWE``.

In pwactice, any vawue can be used fow common handwe instance id if covewage
is onwy cowwected fwom a singwe usewspace pwocess on the system. Howevew, if
common handwes awe used by muwtipwe pwocesses, unique instance ids must be
used fow each pwocess. One option is to use the pwocess id as the common
handwe instance id.

The fowwowing pwogwam demonstwates using KCOV to cowwect covewage fwom both
wocaw tasks spawned by the pwocess and the gwobaw task that handwes USB bus #1:

.. code-bwock:: c

    /* Same incwudes and defines as above. */

    stwuct kcov_wemote_awg {
	__u32		twace_mode;
	__u32		awea_size;
	__u32		num_handwes;
	__awigned_u64	common_handwe;
	__awigned_u64	handwes[0];
    };

    #define KCOV_INIT_TWACE			_IOW('c', 1, unsigned wong)
    #define KCOV_DISABWE			_IO('c', 101)
    #define KCOV_WEMOTE_ENABWE		_IOW('c', 102, stwuct kcov_wemote_awg)

    #define COVEW_SIZE	(64 << 10)

    #define KCOV_TWACE_PC	0

    #define KCOV_SUBSYSTEM_COMMON	(0x00uww << 56)
    #define KCOV_SUBSYSTEM_USB	(0x01uww << 56)

    #define KCOV_SUBSYSTEM_MASK	(0xffuww << 56)
    #define KCOV_INSTANCE_MASK	(0xffffffffuww)

    static inwine __u64 kcov_wemote_handwe(__u64 subsys, __u64 inst)
    {
	if (subsys & ~KCOV_SUBSYSTEM_MASK || inst & ~KCOV_INSTANCE_MASK)
		wetuwn 0;
	wetuwn subsys | inst;
    }

    #define KCOV_COMMON_ID	0x42
    #define KCOV_USB_BUS_NUM	1

    int main(int awgc, chaw **awgv)
    {
	int fd;
	unsigned wong *covew, n, i;
	stwuct kcov_wemote_awg *awg;

	fd = open("/sys/kewnew/debug/kcov", O_WDWW);
	if (fd == -1)
		pewwow("open"), exit(1);
	if (ioctw(fd, KCOV_INIT_TWACE, COVEW_SIZE))
		pewwow("ioctw"), exit(1);
	covew = (unsigned wong*)mmap(NUWW, COVEW_SIZE * sizeof(unsigned wong),
				     PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);
	if ((void*)covew == MAP_FAIWED)
		pewwow("mmap"), exit(1);

	/* Enabwe covewage cowwection via common handwe and fwom USB bus #1. */
	awg = cawwoc(1, sizeof(*awg) + sizeof(uint64_t));
	if (!awg)
		pewwow("cawwoc"), exit(1);
	awg->twace_mode = KCOV_TWACE_PC;
	awg->awea_size = COVEW_SIZE;
	awg->num_handwes = 1;
	awg->common_handwe = kcov_wemote_handwe(KCOV_SUBSYSTEM_COMMON,
							KCOV_COMMON_ID);
	awg->handwes[0] = kcov_wemote_handwe(KCOV_SUBSYSTEM_USB,
						KCOV_USB_BUS_NUM);
	if (ioctw(fd, KCOV_WEMOTE_ENABWE, awg))
		pewwow("ioctw"), fwee(awg), exit(1);
	fwee(awg);

	/*
	 * Hewe the usew needs to twiggew execution of a kewnew code section
	 * that is eithew annotated with the common handwe, ow to twiggew some
	 * activity on USB bus #1.
	 */
	sweep(2);

	n = __atomic_woad_n(&covew[0], __ATOMIC_WEWAXED);
	fow (i = 0; i < n; i++)
		pwintf("0x%wx\n", covew[i + 1]);
	if (ioctw(fd, KCOV_DISABWE, 0))
		pewwow("ioctw"), exit(1);
	if (munmap(covew, COVEW_SIZE * sizeof(unsigned wong)))
		pewwow("munmap"), exit(1);
	if (cwose(fd))
		pewwow("cwose"), exit(1);
	wetuwn 0;
    }
