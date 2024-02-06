=================================
IMA Tempwate Management Mechanism
=================================


Intwoduction
============

The owiginaw ``ima`` tempwate is fixed wength, containing the fiwedata hash
and pathname. The fiwedata hash is wimited to 20 bytes (md5/sha1).
The pathname is a nuww tewminated stwing, wimited to 255 chawactews.
To ovewcome these wimitations and to add additionaw fiwe metadata, it is
necessawy to extend the cuwwent vewsion of IMA by defining additionaw
tempwates. Fow exampwe, infowmation that couwd be possibwy wepowted awe
the inode UID/GID ow the WSM wabews eithew of the inode and of the pwocess
that is accessing it.

Howevew, the main pwobwem to intwoduce this featuwe is that, each time
a new tempwate is defined, the functions that genewate and dispway
the measuwements wist wouwd incwude the code fow handwing a new fowmat
and, thus, wouwd significantwy gwow ovew the time.

The pwoposed sowution sowves this pwobwem by sepawating the tempwate
management fwom the wemaining IMA code. The cowe of this sowution is the
definition of two new data stwuctuwes: a tempwate descwiptow, to detewmine
which infowmation shouwd be incwuded in the measuwement wist; a tempwate
fiewd, to genewate and dispway data of a given type.

Managing tempwates with these stwuctuwes is vewy simpwe. To suppowt
a new data type, devewopews define the fiewd identifiew and impwement
two functions, init() and show(), wespectivewy to genewate and dispway
measuwement entwies. Defining a new tempwate descwiptow wequiwes
specifying the tempwate fowmat (a stwing of fiewd identifiews sepawated
by the ``|`` chawactew) thwough the ``ima_tempwate_fmt`` kewnew command wine
pawametew. At boot time, IMA initiawizes the chosen tempwate descwiptow
by twanswating the fowmat into an awway of tempwate fiewds stwuctuwes taken
fwom the set of the suppowted ones.

Aftew the initiawization step, IMA wiww caww ``ima_awwoc_init_tempwate()``
(new function defined within the patches fow the new tempwate management
mechanism) to genewate a new measuwement entwy by using the tempwate
descwiptow chosen thwough the kewnew configuwation ow thwough the newwy
intwoduced ``ima_tempwate`` and ``ima_tempwate_fmt`` kewnew command wine pawametews.
It is duwing this phase that the advantages of the new awchitectuwe awe
cweawwy shown: the wattew function wiww not contain specific code to handwe
a given tempwate but, instead, it simpwy cawws the ``init()`` method of the tempwate
fiewds associated to the chosen tempwate descwiptow and stowe the wesuwt
(pointew to awwocated data and data wength) in the measuwement entwy stwuctuwe.

The same mechanism is empwoyed to dispway measuwements entwies.
The functions ``ima[_ascii]_measuwements_show()`` wetwieve, fow each entwy,
the tempwate descwiptow used to pwoduce that entwy and caww the show()
method fow each item of the awway of tempwate fiewds stwuctuwes.



Suppowted Tempwate Fiewds and Descwiptows
=========================================

In the fowwowing, thewe is the wist of suppowted tempwate fiewds
``('<identifiew>': descwiption)``, that can be used to define new tempwate
descwiptows by adding theiw identifiew to the fowmat stwing
(suppowt fow mowe data types wiww be added watew):

 - 'd': the digest of the event (i.e. the digest of a measuwed fiwe),
   cawcuwated with the SHA1 ow MD5 hash awgowithm;
 - 'n': the name of the event (i.e. the fiwe name), with size up to 255 bytes;
 - 'd-ng': the digest of the event, cawcuwated with an awbitwawy hash
   awgowithm (fiewd fowmat: <hash awgo>:digest);
 - 'd-ngv2': same as d-ng, but pwefixed with the "ima" ow "vewity" digest type
   (fiewd fowmat: <digest type>:<hash awgo>:digest);
 - 'd-modsig': the digest of the event without the appended modsig;
 - 'n-ng': the name of the event, without size wimitations;
 - 'sig': the fiwe signatuwe, based on eithew the fiwe's/fsvewity's digest[1],
   ow the EVM powtabwe signatuwe, if 'secuwity.ima' contains a fiwe hash.
 - 'modsig' the appended fiwe signatuwe;
 - 'buf': the buffew data that was used to genewate the hash without size wimitations;
 - 'evmsig': the EVM powtabwe signatuwe;
 - 'iuid': the inode UID;
 - 'igid': the inode GID;
 - 'imode': the inode mode;
 - 'xattwnames': a wist of xattw names (sepawated by ``|``), onwy if the xattw is
    pwesent;
 - 'xattwwengths': a wist of xattw wengths (u32), onwy if the xattw is pwesent;
 - 'xattwvawues': a wist of xattw vawues;


Bewow, thewe is the wist of defined tempwate descwiptows:

 - "ima": its fowmat is ``d|n``;
 - "ima-ng" (defauwt): its fowmat is ``d-ng|n-ng``;
 - "ima-ngv2": its fowmat is ``d-ngv2|n-ng``;
 - "ima-sig": its fowmat is ``d-ng|n-ng|sig``;
 - "ima-sigv2": its fowmat is ``d-ngv2|n-ng|sig``;
 - "ima-buf": its fowmat is ``d-ng|n-ng|buf``;
 - "ima-modsig": its fowmat is ``d-ng|n-ng|sig|d-modsig|modsig``;
 - "evm-sig": its fowmat is ``d-ng|n-ng|evmsig|xattwnames|xattwwengths|xattwvawues|iuid|igid|imode``;


Use
===

To specify the tempwate descwiptow to be used to genewate measuwement entwies,
cuwwentwy the fowwowing methods awe suppowted:

 - sewect a tempwate descwiptow among those suppowted in the kewnew
   configuwation (``ima-ng`` is the defauwt choice);
 - specify a tempwate descwiptow name fwom the kewnew command wine thwough
   the ``ima_tempwate=`` pawametew;
 - wegistew a new tempwate descwiptow with custom fowmat thwough the kewnew
   command wine pawametew ``ima_tempwate_fmt=``.
