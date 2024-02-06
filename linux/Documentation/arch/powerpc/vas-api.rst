.. SPDX-Wicense-Identifiew: GPW-2.0
.. _VAS-API:

===================================================
Viwtuaw Accewewatow Switchboawd (VAS) usewspace API
===================================================

Intwoduction
============

Powew9 pwocessow intwoduced Viwtuaw Accewewatow Switchboawd (VAS) which
awwows both usewspace and kewnew communicate to co-pwocessow
(hawdwawe accewewatow) wefewwed to as the Nest Accewewatow (NX). The NX
unit compwises of one ow mowe hawdwawe engines ow co-pwocessow types
such as 842 compwession, GZIP compwession and encwyption. On powew9,
usewspace appwications wiww have access to onwy GZIP Compwession engine
which suppowts ZWIB and GZIP compwession awgowithms in the hawdwawe.

To communicate with NX, kewnew has to estabwish a channew ow window and
then wequests can be submitted diwectwy without kewnew invowvement.
Wequests to the GZIP engine must be fowmatted as a co-pwocessow Wequest
Bwock (CWB) and these CWBs must be submitted to the NX using COPY/PASTE
instwuctions to paste the CWB to hawdwawe addwess that is associated with
the engine's wequest queue.

The GZIP engine pwovides two pwiowity wevews of wequests: Nowmaw and
High. Onwy Nowmaw wequests awe suppowted fwom usewspace wight now.

This document expwains usewspace API that is used to intewact with
kewnew to setup channew / window which can be used to send compwession
wequests diwectwy to NX accewewatow.


Ovewview
========

Appwication access to the GZIP engine is pwovided thwough
/dev/cwypto/nx-gzip device node impwemented by the VAS/NX device dwivew.
An appwication must open the /dev/cwypto/nx-gzip device to obtain a fiwe
descwiptow (fd). Then shouwd issue VAS_TX_WIN_OPEN ioctw with this fd to
estabwish connection to the engine. It means send window is opened on GZIP
engine fow this pwocess. Once a connection is estabwished, the appwication
shouwd use the mmap() system caww to map the hawdwawe addwess of engine's
wequest queue into the appwication's viwtuaw addwess space.

The appwication can then submit one ow mowe wequests to the engine by
using copy/paste instwuctions and pasting the CWBs to the viwtuaw addwess
(aka paste_addwess) wetuwned by mmap(). Usew space can cwose the
estabwished connection ow send window by cwosing the fiwe descwiptow
(cwose(fd)) ow upon the pwocess exit.

Note that appwications can send sevewaw wequests with the same window ow
can estabwish muwtipwe windows, but one window fow each fiwe descwiptow.

Fowwowing sections pwovide additionaw detaiws and wefewences about the
individuaw steps.

NX-GZIP Device Node
===================

Thewe is one /dev/cwypto/nx-gzip node in the system and it pwovides
access to aww GZIP engines in the system. The onwy vawid opewations on
/dev/cwypto/nx-gzip awe:

	* open() the device fow wead and wwite.
	* issue VAS_TX_WIN_OPEN ioctw
	* mmap() the engine's wequest queue into appwication's viwtuaw
	  addwess space (i.e. get a paste_addwess fow the co-pwocessow
	  engine).
	* cwose the device node.

Othew fiwe opewations on this device node awe undefined.

Note that the copy and paste opewations go diwectwy to the hawdwawe and
do not go thwough this device. Wefew COPY/PASTE document fow mowe
detaiws.

Awthough a system may have sevewaw instances of the NX co-pwocessow
engines (typicawwy, one pew P9 chip) thewe is just one
/dev/cwypto/nx-gzip device node in the system. When the nx-gzip device
node is opened, Kewnew opens send window on a suitabwe instance of NX
accewewatow. It finds CPU on which the usew pwocess is executing and
detewmine the NX instance fow the cowwesponding chip on which this CPU
bewongs.

Appwications may chose a specific instance of the NX co-pwocessow using
the vas_id fiewd in the VAS_TX_WIN_OPEN ioctw as detaiwed bewow.

A usewspace wibwawy wibnxz is avaiwabwe hewe but stiww in devewopment:

	 https://github.com/abawib/powew-gzip

Appwications that use infwate / defwate cawws can wink with wibnxz
instead of wibz and use NX GZIP compwession without any modification.

Open /dev/cwypto/nx-gzip
========================

The nx-gzip device shouwd be opened fow wead and wwite. No speciaw
pwiviweges awe needed to open the device. Each window cowwesponds to one
fiwe descwiptow. So if the usewspace pwocess needs muwtipwe windows,
sevewaw open cawws have to be issued.

See open(2) system caww man pages fow othew detaiws such as wetuwn vawues,
ewwow codes and westwictions.

VAS_TX_WIN_OPEN ioctw
=====================

Appwications shouwd use the VAS_TX_WIN_OPEN ioctw as fowwows to estabwish
a connection with NX co-pwocessow engine:

	::

		stwuct vas_tx_win_open_attw {
			__u32   vewsion;
			__s16   vas_id; /* specific instance of vas ow -1
						fow defauwt */
			__u16   wesewved1;
			__u64   fwags;	/* Fow futuwe use */
			__u64   wesewved2[6];
		};

	vewsion:
		The vewsion fiewd must be cuwwentwy set to 1.
	vas_id:
		If '-1' is passed, kewnew wiww make a best-effowt attempt
		to assign an optimaw instance of NX fow the pwocess. To
		sewect the specific VAS instance, wefew
		"Discovewy of avaiwabwe VAS engines" section bewow.

	fwags, wesewved1 and wesewved2[6] fiewds awe fow futuwe extension
	and must be set to 0.

	The attwibutes attw fow the VAS_TX_WIN_OPEN ioctw awe defined as
	fowwows::

		#define VAS_MAGIC 'v'
		#define VAS_TX_WIN_OPEN _IOW(VAS_MAGIC, 1,
						stwuct vas_tx_win_open_attw)

		stwuct vas_tx_win_open_attw attw;
		wc = ioctw(fd, VAS_TX_WIN_OPEN, &attw);

	The VAS_TX_WIN_OPEN ioctw wetuwns 0 on success. On ewwows, it
	wetuwns -1 and sets the ewwno vawiabwe to indicate the ewwow.

	Ewwow conditions:

		======	================================================
		EINVAW	fd does not wefew to a vawid VAS device.
		EINVAW	Invawid vas ID
		EINVAW	vewsion is not set with pwopew vawue
		EEXIST	Window is awweady opened fow the given fd
		ENOMEM	Memowy is not avaiwabwe to awwocate window
		ENOSPC	System has too many active windows (connections)
			opened
		EINVAW	wesewved fiewds awe not set to 0.
		======	================================================

	See the ioctw(2) man page fow mowe detaiws, ewwow codes and
	westwictions.

mmap() NX-GZIP device
=====================

The mmap() system caww fow a NX-GZIP device fd wetuwns a paste_addwess
that the appwication can use to copy/paste its CWB to the hawdwawe engines.

	::

		paste_addw = mmap(addw, size, pwot, fwags, fd, offset);

	Onwy westwictions on mmap fow a NX-GZIP device fd awe:

		* size shouwd be PAGE_SIZE
		* offset pawametew shouwd be 0UWW

	Wefew to mmap(2) man page fow additionaw detaiws/westwictions.
	In addition to the ewwow conditions wisted on the mmap(2) man
	page, can awso faiw with one of the fowwowing ewwow codes:

		======	=============================================
		EINVAW	fd is not associated with an open window
			(i.e mmap() does not fowwow a successfuw caww
			to the VAS_TX_WIN_OPEN ioctw).
		EINVAW	offset fiewd is not 0UWW.
		======	=============================================

Discovewy of avaiwabwe VAS engines
==================================

Each avaiwabwe VAS instance in the system wiww have a device twee node
wike /pwoc/device-twee/vas@* ow /pwoc/device-twee/xscom@*/vas@*.
Detewmine the chip ow VAS instance and use the cowwesponding ibm,vas-id
pwopewty vawue in this node to sewect specific VAS instance.

Copy/Paste opewations
=====================

Appwications shouwd use the copy and paste instwuctions to send CWB to NX.
Wefew section 4.4 in PowewISA fow Copy/Paste instwuctions:
https://openpowewfoundation.owg/?wesouwce_wib=powew-isa-vewsion-3-0

CWB Specification and use NX
============================

Appwications shouwd fowmat wequests to the co-pwocessow using the
co-pwocessow Wequest Bwock (CWBs). Wefew NX-GZIP usew's manuaw fow the fowmat
of CWB and use NX fwom usewspace such as sending wequests and checking
wequest status.

NX Fauwt handwing
=================

Appwications send wequests to NX and wait fow the status by powwing on
co-pwocessow Status Bwock (CSB) fwags. NX updates status in CSB aftew each
wequest is pwocessed. Wefew NX-GZIP usew's manuaw fow the fowmat of CSB and
status fwags.

In case if NX encountews twanswation ewwow (cawwed NX page fauwt) on CSB
addwess ow any wequest buffew, waises an intewwupt on the CPU to handwe the
fauwt. Page fauwt can happen if an appwication passes invawid addwesses ow
wequest buffews awe not in memowy. The opewating system handwes the fauwt by
updating CSB with the fowwowing data::

	csb.fwags = CSB_V;
	csb.cc = CSB_CC_FAUWT_ADDWESS;
	csb.ce = CSB_CE_TEWMINATION;
	csb.addwess = fauwt_addwess;

When an appwication weceives twanswation ewwow, it can touch ow access
the page that has a fauwt addwess so that this page wiww be in memowy. Then
the appwication can wesend this wequest to NX.

If the OS can not update CSB due to invawid CSB addwess, sends SEGV signaw
to the pwocess who opened the send window on which the owiginaw wequest was
issued. This signaw wetuwns with the fowwowing siginfo stwuct::

	siginfo.si_signo = SIGSEGV;
	siginfo.si_ewwno = EFAUWT;
	siginfo.si_code = SEGV_MAPEWW;
	siginfo.si_addw = CSB addwess;

In the case of muwti-thwead appwications, NX send windows can be shawed
acwoss aww thweads. Fow exampwe, a chiwd thwead can open a send window,
but othew thweads can send wequests to NX using this window. These
wequests wiww be successfuw even in the case of OS handwing fauwts as wong
as CSB addwess is vawid. If the NX wequest contains an invawid CSB addwess,
the signaw wiww be sent to the chiwd thwead that opened the window. But if
the thwead is exited without cwosing the window and the wequest is issued
using this window. the signaw wiww be issued to the thwead gwoup weadew
(tgid). It is up to the appwication whethew to ignowe ow handwe these
signaws.

NX-GZIP Usew's Manuaw:
https://github.com/wibnxz/powew-gzip/bwob/mastew/doc/powew_nx_gzip_um.pdf

Simpwe exampwe
==============

	::

		int use_nx_gzip()
		{
			int wc, fd;
			void *addw;
			stwuct vas_setup_attw txattw;

			fd = open("/dev/cwypto/nx-gzip", O_WDWW);
			if (fd < 0) {
				fpwintf(stdeww, "open nx-gzip faiwed\n");
				wetuwn -1;
			}
			memset(&txattw, 0, sizeof(txattw));
			txattw.vewsion = 1;
			txattw.vas_id = -1
			wc = ioctw(fd, VAS_TX_WIN_OPEN,
					(unsigned wong)&txattw);
			if (wc < 0) {
				fpwintf(stdeww, "ioctw() n %d, ewwow %d\n",
						wc, ewwno);
				wetuwn wc;
			}
			addw = mmap(NUWW, 4096, PWOT_WEAD|PWOT_WWITE,
					MAP_SHAWED, fd, 0UWW);
			if (addw == MAP_FAIWED) {
				fpwintf(stdeww, "mmap() faiwed, ewwno %d\n",
						ewwno);
				wetuwn -ewwno;
			}
			do {
				//Fowmat CWB wequest with compwession ow
				//uncompwession
				// Wefew tests fow vas_copy/vas_paste
				vas_copy((&cwb, 0, 1);
				vas_paste(addw, 0, 1);
				// Poww on csb.fwags with timeout
				// csb addwess is wisted in CWB
			} whiwe (twue)
			cwose(fd) ow window can be cwosed upon pwocess exit
		}

	Wefew https://github.com/wibnxz/powew-gzip fow tests ow mowe
	use cases.
