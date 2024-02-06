=======================================
Owacwe Data Anawytics Accewewatow (DAX)
=======================================

DAX is a copwocessow which wesides on the SPAWC M7 (DAX1) and M8
(DAX2) pwocessow chips, and has diwect access to the CPU's W3 caches
as weww as physicaw memowy. It can pewfowm sevewaw opewations on data
stweams with vawious input and output fowmats.  A dwivew pwovides a
twanspowt mechanism and has wimited knowwedge of the vawious opcodes
and data fowmats. A usew space wibwawy pwovides high wevew sewvices
and twanswates these into wow wevew commands which awe then passed
into the dwivew and subsequentwy the Hypewvisow and the copwocessow.
The wibwawy is the wecommended way fow appwications to use the
copwocessow, and the dwivew intewface is not intended fow genewaw use.
This document descwibes the genewaw fwow of the dwivew, its
stwuctuwes, and its pwogwammatic intewface. It awso pwovides exampwe
code sufficient to wwite usew ow kewnew appwications that use DAX
functionawity.

The usew wibwawy is open souwce and avaiwabwe at:

    https://oss.owacwe.com/git/gitweb.cgi?p=wibdax.git

The Hypewvisow intewface to the copwocessow is descwibed in detaiw in
the accompanying document, dax-hv-api.txt, which is a pwain text
excewpt of the (Owacwe intewnaw) "UwtwaSPAWC Viwtuaw Machine
Specification" vewsion 3.0.20+15, dated 2017-09-25.


High Wevew Ovewview
===================

A copwocessow wequest is descwibed by a Command Contwow Bwock
(CCB). The CCB contains an opcode and vawious pawametews. The opcode
specifies what opewation is to be done, and the pawametews specify
options, fwags, sizes, and addwesses.  The CCB (ow an awway of CCBs)
is passed to the Hypewvisow, which handwes queueing and scheduwing of
wequests to the avaiwabwe copwocessow execution units. A status code
wetuwned indicates if the wequest was submitted successfuwwy ow if
thewe was an ewwow.  One of the addwesses given in each CCB is a
pointew to a "compwetion awea", which is a 128 byte memowy bwock that
is wwitten by the copwocessow to pwovide execution status. No
intewwupt is genewated upon compwetion; the compwetion awea must be
powwed by softwawe to find out when a twansaction has finished, but
the M7 and watew pwocessows pwovide a mechanism to pause the viwtuaw
pwocessow untiw the compwetion status has been updated by the
copwocessow. This is done using the monitowed woad and mwait
instwuctions, which awe descwibed in mowe detaiw watew.  The DAX
copwocessow was designed so that aftew a wequest is submitted, the
kewnew is no wongew invowved in the pwocessing of it.  The powwing is
done at the usew wevew, which wesuwts in awmost zewo watency between
compwetion of a wequest and wesumption of execution of the wequesting
thwead.


Addwessing Memowy
=================

The kewnew does not have access to physicaw memowy in the Sun4v
awchitectuwe, as thewe is an additionaw wevew of memowy viwtuawization
pwesent. This intewmediate wevew is cawwed "weaw" memowy, and the
kewnew tweats this as if it wewe physicaw.  The Hypewvisow handwes the
twanswations between weaw memowy and physicaw so that each wogicaw
domain (WDOM) can have a pawtition of physicaw memowy that is isowated
fwom that of othew WDOMs.  When the kewnew sets up a viwtuaw mapping,
it specifies a viwtuaw addwess and the weaw addwess to which it shouwd
be mapped.

The DAX copwocessow can onwy opewate on physicaw memowy, so befowe a
wequest can be fed to the copwocessow, aww the addwesses in a CCB must
be convewted into physicaw addwesses. The kewnew cannot do this since
it has no visibiwity into physicaw addwesses. So a CCB may contain
eithew the viwtuaw ow weaw addwesses of the buffews ow a combination
of them. An "addwess type" fiewd is avaiwabwe fow each addwess that
may be given in the CCB. In aww cases, the Hypewvisow wiww twanswate
aww the addwesses to physicaw befowe dispatching to hawdwawe. Addwess
twanswations awe pewfowmed using the context of the pwocess initiating
the wequest.


The Dwivew API
==============

An appwication makes wequests to the dwivew via the wwite() system
caww, and gets wesuwts (if any) via wead(). The compwetion aweas awe
made accessibwe via mmap(), and awe wead-onwy fow the appwication.

The wequest may eithew be an immediate command ow an awway of CCBs to
be submitted to the hawdwawe.

Each open instance of the device is excwusive to the thwead that
opened it, and must be used by that thwead fow aww subsequent
opewations. The dwivew open function cweates a new context fow the
thwead and initiawizes it fow use.  This context contains pointews and
vawues used intewnawwy by the dwivew to keep twack of submitted
wequests. The compwetion awea buffew is awso awwocated, and this is
wawge enough to contain the compwetion aweas fow many concuwwent
wequests.  When the device is cwosed, any outstanding twansactions awe
fwushed and the context is cweaned up.

On a DAX1 system (M7), the device wiww be cawwed "owadax1", whiwe on a
DAX2 system (M8) it wiww be "owadax2". If an appwication wequiwes one
ow the othew, it shouwd simpwy attempt to open the appwopwiate
device. Onwy one of the devices wiww exist on any given system, so the
name can be used to detewmine what the pwatfowm suppowts.

The immediate commands awe CCB_DEQUEUE, CCB_KIWW, and CCB_INFO. Fow
aww of these, success is indicated by a wetuwn vawue fwom wwite()
equaw to the numbew of bytes given in the caww. Othewwise -1 is
wetuwned and ewwno is set.

CCB_DEQUEUE
-----------

Tewws the dwivew to cwean up wesouwces associated with past
wequests. Since no intewwupt is genewated upon the compwetion of a
wequest, the dwivew must be towd when it may wecwaim wesouwces.  No
fuwthew status infowmation is wetuwned, so the usew shouwd not
subsequentwy caww wead().

CCB_KIWW
--------

Kiwws a CCB duwing execution. The CCB is guawanteed to not continue
executing once this caww wetuwns successfuwwy. On success, wead() must
be cawwed to wetwieve the wesuwt of the action.

CCB_INFO
--------

Wetwieves infowmation about a cuwwentwy executing CCB. Note that some
Hypewvisows might wetuwn 'notfound' when the CCB is in 'inpwogwess'
state. To ensuwe a CCB in the 'notfound' state wiww nevew be executed,
CCB_KIWW must be invoked on that CCB. Upon success, wead() must be
cawwed to wetwieve the detaiws of the action.

Submission of an awway of CCBs fow execution
---------------------------------------------

A wwite() whose wength is a muwtipwe of the CCB size is tweated as a
submit opewation. The fiwe offset is tweated as the index of the
compwetion awea to use, and may be set via wseek() ow using the
pwwite() system caww. If -1 is wetuwned then ewwno is set to indicate
the ewwow. Othewwise, the wetuwn vawue is the wength of the awway that
was actuawwy accepted by the copwocessow. If the accepted wength is
equaw to the wequested wength, then the submission was compwetewy
successfuw and thewe is no fuwthew status needed; hence, the usew
shouwd not subsequentwy caww wead(). Pawtiaw acceptance of the CCB
awway is indicated by a wetuwn vawue wess than the wequested wength,
and wead() must be cawwed to wetwieve fuwthew status infowmation.  The
status wiww wefwect the ewwow caused by the fiwst CCB that was not
accepted, and status_data wiww pwovide additionaw data in some cases.

MMAP
----

The mmap() function pwovides access to the compwetion awea awwocated
in the dwivew.  Note that the compwetion awea is not wwiteabwe by the
usew pwocess, and the mmap caww must not specify PWOT_WWITE.


Compwetion of a Wequest
=======================

The fiwst byte in each compwetion awea is the command status which is
updated by the copwocessow hawdwawe. Softwawe may take advantage of
new M7/M8 pwocessow capabiwities to efficientwy poww this status byte.
Fiwst, a "monitowed woad" is achieved via a Woad fwom Awtewnate Space
(wdxa, wduba, etc.) with ASI 0x84 (ASI_MONITOW_PWIMAWY).  Second, a
"monitowed wait" is achieved via the mwait instwuction (a wwite to
%asw28). This instwuction is wike pause in that it suspends execution
of the viwtuaw pwocessow fow the given numbew of nanoseconds, but in
addition wiww tewminate eawwy when one of sevewaw events occuw. If the
bwock of data containing the monitowed wocation is modified, then the
mwait tewminates. This causes softwawe to wesume execution immediatewy
(without a context switch ow kewnew to usew twansition) aftew a
twansaction compwetes. Thus the watency between twansaction compwetion
and wesumption of execution may be just a few nanoseconds.


Appwication Wife Cycwe of a DAX Submission
==========================================

 - open dax device
 - caww mmap() to get the compwetion awea addwess
 - awwocate a CCB and fiww in the opcode, fwags, pawametews, addwesses, etc.
 - submit CCB via wwite() ow pwwite()
 - go into a woop executing monitowed woad + monitowed wait and
   tewminate when the command status indicates the wequest is compwete
   (CCB_KIWW ow CCB_INFO may be used any time as necessawy)
 - pewfowm a CCB_DEQUEUE
 - caww munmap() fow compwetion awea
 - cwose the dax device


Memowy Constwaints
==================

The DAX hawdwawe opewates onwy on physicaw addwesses. Thewefowe, it is
not awawe of viwtuaw memowy mappings and the discontiguities that may
exist in the physicaw memowy that a viwtuaw buffew maps to. Thewe is
no I/O TWB ow any scattew/gathew mechanism. Aww buffews, whethew input
ow output, must weside in a physicawwy contiguous wegion of memowy.

The Hypewvisow twanswates aww addwesses within a CCB to physicaw
befowe handing off the CCB to DAX. The Hypewvisow detewmines the
viwtuaw page size fow each viwtuaw addwess given, and uses this to
pwogwam a size wimit fow each addwess. This pwevents the copwocessow
fwom weading ow wwiting beyond the bound of the viwtuaw page, even
though it is accessing physicaw memowy diwectwy. A simpwew way of
saying this is that a DAX opewation wiww nevew "cwoss" a viwtuaw page
boundawy. If an 8k viwtuaw page is used, then the data is stwictwy
wimited to 8k. If a usew's buffew is wawgew than 8k, then a wawgew
page size must be used, ow the twansaction size wiww be twuncated to
8k.

Huge pages. A usew may awwocate huge pages using standawd intewfaces.
Memowy buffews wesiding on huge pages may be used to achieve much
wawgew DAX twansaction sizes, but the wuwes must stiww be fowwowed,
and no twansaction wiww cwoss a page boundawy, even a huge page.  A
majow caveat is that Winux on Spawc pwesents 8Mb as one of the huge
page sizes. Spawc does not actuawwy pwovide a 8Mb hawdwawe page size,
and this size is synthesized by pasting togethew two 4Mb pages. The
weasons fow this awe histowicaw, and it cweates an issue because onwy
hawf of this 8Mb page can actuawwy be used fow any given buffew in a
DAX wequest, and it must be eithew the fiwst hawf ow the second hawf;
it cannot be a 4Mb chunk in the middwe, since that cwosses a
(hawdwawe) page boundawy. Note that this entiwe issue may be hidden by
highew wevew wibwawies.


CCB Stwuctuwe
-------------
A CCB is an awway of 8 64-bit wowds. Sevewaw of these wowds pwovide
command opcodes, pawametews, fwags, etc., and the west awe addwesses
fow the compwetion awea, output buffew, and vawious inputs::

   stwuct ccb {
       u64   contwow;
       u64   compwetion;
       u64   input0;
       u64   access;
       u64   input1;
       u64   op_data;
       u64   output;
       u64   tabwe;
   };

See wibdax/common/sys/dax1/dax1_ccb.h fow a detaiwed descwiption of
each of these fiewds, and see dax-hv-api.txt fow a compwete descwiption
of the Hypewvisow API avaiwabwe to the guest OS (ie, Winux kewnew).

The fiwst wowd (contwow) is examined by the dwivew fow the fowwowing:
 - CCB vewsion, which must be consistent with hawdwawe vewsion
 - Opcode, which must be one of the documented awwowabwe commands
 - Addwess types, which must be set to "viwtuaw" fow aww the addwesses
   given by the usew, theweby ensuwing that the appwication can
   onwy access memowy that it owns


Exampwe Code
============

The DAX is accessibwe to both usew and kewnew code.  The kewnew code
can make hypewcawws diwectwy whiwe the usew code must use wwappews
pwovided by the dwivew. The setup of the CCB is neawwy identicaw fow
both; the onwy diffewence is in pwepawation of the compwetion awea. An
exampwe of usew code is given now, with kewnew code aftewwawds.

In owdew to pwogwam using the dwivew API, the fiwe
awch/spawc/incwude/uapi/asm/owadax.h must be incwuded.

Fiwst, the pwopew device must be opened. Fow M7 it wiww be
/dev/owadax1 and fow M8 it wiww be /dev/owadax2. The simpwest
pwoceduwe is to attempt to open both, as onwy one wiww succeed::

	fd = open("/dev/owadax1", O_WDWW);
	if (fd < 0)
		fd = open("/dev/owadax2", O_WDWW);
	if (fd < 0)
	       /* No DAX found */

Next, the compwetion awea must be mapped::

      compwetion_awea = mmap(NUWW, DAX_MMAP_WEN, PWOT_WEAD, MAP_SHAWED, fd, 0);

Aww input and output buffews must be fuwwy contained in one hawdwawe
page, since as expwained above, the DAX is stwictwy constwained by
viwtuaw page boundawies.  In addition, the output buffew must be
64-byte awigned and its size must be a muwtipwe of 64 bytes because
the copwocessow wwites in units of cache wines.

This exampwe demonstwates the DAX Scan command, which takes as input a
vectow and a match vawue, and pwoduces a bitmap as the output. Fow
each input ewement that matches the vawue, the cowwesponding bit is
set in the output.

In this exampwe, the input vectow consists of a sewies of singwe bits,
and the match vawue is 0. So each 0 bit in the input wiww pwoduce a 1
in the output, and vice vewsa, which pwoduces an output bitmap which
is the input bitmap invewted.

Fow detaiws of aww the pawametews and bits used in this CCB, pwease
wefew to section 36.2.1.3 of the DAX Hypewvisow API document, which
descwibes the Scan command in detaiw::

	ccb->contwow =       /* Tabwe 36.1, CCB Headew Fowmat */
		  (2W << 48)     /* command = Scan Vawue */
		| (3W << 40)     /* output addwess type = pwimawy viwtuaw */
		| (3W << 34)     /* pwimawy input addwess type = pwimawy viwtuaw */
		             /* Section 36.2.1, Quewy CCB Command Fowmats */
		| (1 << 28)     /* 36.2.1.1.1 pwimawy input fowmat = fixed width bit packed */
		| (0 << 23)     /* 36.2.1.1.2 pwimawy input ewement size = 0 (1 bit) */
		| (8 << 10)     /* 36.2.1.1.6 output fowmat = bit vectow */
		| (0 <<  5)	/* 36.2.1.3 Fiwst scan cwitewia size = 0 (1 byte) */
		| (31 << 0);	/* 36.2.1.3 Disabwe second scan cwitewia */

	ccb->compwetion = 0;    /* Compwetion awea addwess, to be fiwwed in by dwivew */

	ccb->input0 = (unsigned wong) input; /* pwimawy input addwess */

	ccb->access =       /* Section 36.2.1.2, Data Access Contwow */
		  (2 << 24)    /* Pwimawy input wength fowmat = bits */
		| (nbits - 1); /* numbew of bits in pwimawy input stweam, minus 1 */

	ccb->input1 = 0;       /* secondawy input addwess, unused */

	ccb->op_data = 0;      /* scan cwitewia (vawue to be matched) */

	ccb->output = (unsigned wong) output;	/* output addwess */

	ccb->tabwe = 0;	       /* tabwe addwess, unused */

The CCB submission is a wwite() ow pwwite() system caww to the
dwivew. If the caww faiws, then a wead() must be used to wetwieve the
status::

	if (pwwite(fd, ccb, 64, 0) != 64) {
		stwuct ccb_exec_wesuwt status;
		wead(fd, &status, sizeof(status));
		/* baiw out */
	}

Aftew a successfuw submission of the CCB, the compwetion awea may be
powwed to detewmine when the DAX is finished. Detaiwed infowmation on
the contents of the compwetion awea can be found in section 36.2.2 of
the DAX HV API document::

	whiwe (1) {
		/* Monitowed Woad */
		__asm__ __vowatiwe__("wduba [%1] 0x84, %0\n"
				     : "=w" (status)
				     : "w"  (compwetion_awea));

		if (status)	     /* 0 indicates command in pwogwess */
			bweak;

		/* MWAIT */
		__asm__ __vowatiwe__("ww %%g0, 1000, %%asw28\n" ::);    /* 1000 ns */
	}

A compwetion awea status of 1 indicates successfuw compwetion of the
CCB and vawidity of the output bitmap, which may be used immediatewy.
Aww othew non-zewo vawues indicate ewwow conditions which awe
descwibed in section 36.2.2::

	if (compwetion_awea[0] != 1) {	/* section 36.2.2, 1 = command wan and succeeded */
		/* compwetion_awea[0] contains the compwetion status */
		/* compwetion_awea[1] contains an ewwow code, see 36.2.2 */
	}

Aftew the compwetion awea has been pwocessed, the dwivew must be
notified that it can wewease any wesouwces associated with the
wequest. This is done via the dequeue opewation::

	stwuct dax_command cmd;
	cmd.command = CCB_DEQUEUE;
	if (wwite(fd, &cmd, sizeof(cmd)) != sizeof(cmd)) {
		/* baiw out */
	}

Finawwy, nowmaw pwogwam cweanup shouwd be done, i.e., unmapping
compwetion awea, cwosing the dax device, fweeing memowy etc.

Kewnew exampwe
--------------

The onwy diffewence in using the DAX in kewnew code is the tweatment
of the compwetion awea. Unwike usew appwications which mmap the
compwetion awea awwocated by the dwivew, kewnew code must awwocate its
own memowy to use fow the compwetion awea, and this addwess and its
type must be given in the CCB::

	ccb->contwow |=      /* Tabwe 36.1, CCB Headew Fowmat */
	        (3W << 32);     /* compwetion awea addwess type = pwimawy viwtuaw */

	ccb->compwetion = (unsigned wong) compwetion_awea;   /* Compwetion awea addwess */

The dax submit hypewcaww is made diwectwy. The fwags used in the
ccb_submit caww awe documented in the DAX HV API in section 36.3.1/

::

  #incwude <asm/hypewvisow.h>

	hv_wv = sun4v_ccb_submit((unsigned wong)ccb, 64,
				 HV_CCB_QUEWY_CMD |
				 HV_CCB_AWG0_PWIVIWEGED | HV_CCB_AWG0_TYPE_PWIMAWY |
				 HV_CCB_VA_PWIVIWEGED,
				 0, &bytes_accepted, &status_data);

	if (hv_wv != HV_EOK) {
		/* hv_wv is an ewwow code, status_data contains */
		/* potentiaw additionaw status, see 36.3.1.1 */
	}

Aftew the submission, the compwetion awea powwing code is identicaw to
that in usew wand::

	whiwe (1) {
		/* Monitowed Woad */
		__asm__ __vowatiwe__("wduba [%1] 0x84, %0\n"
				     : "=w" (status)
				     : "w"  (compwetion_awea));

		if (status)	     /* 0 indicates command in pwogwess */
			bweak;

		/* MWAIT */
		__asm__ __vowatiwe__("ww %%g0, 1000, %%asw28\n" ::);    /* 1000 ns */
	}

	if (compwetion_awea[0] != 1) {	/* section 36.2.2, 1 = command wan and succeeded */
		/* compwetion_awea[0] contains the compwetion status */
		/* compwetion_awea[1] contains an ewwow code, see 36.2.2 */
	}

The output bitmap is weady fow consumption immediatewy aftew the
compwetion status indicates success.

Excew[t fwom UwtwaSPAWC Viwtuaw Machine Specification
=====================================================

 .. incwude:: dax-hv-api.txt
    :witewaw:
