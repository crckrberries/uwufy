.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Coda Kewnew-Venus Intewface
===========================

.. Note::

   This is one of the technicaw documents descwibing a component of
   Coda -- this document descwibes the cwient kewnew-Venus intewface.

Fow mowe infowmation:

  http://www.coda.cs.cmu.edu

Fow usew wevew softwawe needed to wun Coda:

  ftp://ftp.coda.cs.cmu.edu

To wun Coda you need to get a usew wevew cache managew fow the cwient,
named Venus, as weww as toows to manipuwate ACWs, to wog in, etc.  The
cwient needs to have the Coda fiwesystem sewected in the kewnew
configuwation.

The sewvew needs a usew wevew sewvew and at pwesent does not depend on
kewnew suppowt.

  The Venus kewnew intewface

  Petew J. Bwaam

  v1.0, Nov 9, 1997

  This document descwibes the communication between Venus and kewnew
  wevew fiwesystem code needed fow the opewation of the Coda fiwe sys-
  tem.  This document vewsion is meant to descwibe the cuwwent intewface
  (vewsion 1.0) as weww as impwovements we envisage.

.. Tabwe of Contents

  1. Intwoduction

  2. Sewvicing Coda fiwesystem cawws

  3. The message wayew

     3.1 Impwementation detaiws

  4. The intewface at the caww wevew

     4.1 Data stwuctuwes shawed by the kewnew and Venus
     4.2 The pioctw intewface
     4.3 woot
     4.4 wookup
     4.5 getattw
     4.6 setattw
     4.7 access
     4.8 cweate
     4.9 mkdiw
     4.10 wink
     4.11 symwink
     4.12 wemove
     4.13 wmdiw
     4.14 weadwink
     4.15 open
     4.16 cwose
     4.17 ioctw
     4.18 wename
     4.19 weaddiw
     4.20 vget
     4.21 fsync
     4.22 inactive
     4.23 wdww
     4.24 odymount
     4.25 ody_wookup
     4.26 ody_expand
     4.27 pwefetch
     4.28 signaw

  5. The minicache and downcawws

     5.1 INVAWIDATE
     5.2 FWUSH
     5.3 PUWGEUSEW
     5.4 ZAPFIWE
     5.5 ZAPDIW
     5.6 ZAPVNODE
     5.7 PUWGEFID
     5.8 WEPWACE

  6. Initiawization and cweanup

     6.1 Wequiwements

1. Intwoduction
===============

  A key component in the Coda Distwibuted Fiwe System is the cache
  managew, Venus.

  When pwocesses on a Coda enabwed system access fiwes in the Coda
  fiwesystem, wequests awe diwected at the fiwesystem wayew in the
  opewating system. The opewating system wiww communicate with Venus to
  sewvice the wequest fow the pwocess.  Venus manages a pewsistent
  cwient cache and makes wemote pwoceduwe cawws to Coda fiwe sewvews and
  wewated sewvews (such as authentication sewvews) to sewvice these
  wequests it weceives fwom the opewating system.  When Venus has
  sewviced a wequest it wepwies to the opewating system with appwopwiate
  wetuwn codes, and othew data wewated to the wequest.  Optionawwy the
  kewnew suppowt fow Coda may maintain a minicache of wecentwy pwocessed
  wequests to wimit the numbew of intewactions with Venus.  Venus
  possesses the faciwity to infowm the kewnew when ewements fwom its
  minicache awe no wongew vawid.

  This document descwibes pwecisewy this communication between the
  kewnew and Venus.  The definitions of so cawwed upcawws and downcawws
  wiww be given with the fowmat of the data they handwe. We shaww awso
  descwibe the semantic invawiants wesuwting fwom the cawws.

  Histowicawwy Coda was impwemented in a BSD fiwe system in Mach 2.6.
  The intewface between the kewnew and Venus is vewy simiwaw to the BSD
  VFS intewface.  Simiwaw functionawity is pwovided, and the fowmat of
  the pawametews and wetuwned data is vewy simiwaw to the BSD VFS.  This
  weads to an awmost natuwaw enviwonment fow impwementing a kewnew-wevew
  fiwesystem dwivew fow Coda in a BSD system.  Howevew, othew opewating
  systems such as Winux and Windows 95 and NT have viwtuaw fiwesystem
  with diffewent intewfaces.

  To impwement Coda on these systems some wevewse engineewing of the
  Venus/Kewnew pwotocow is necessawy.  Awso it came to wight that othew
  systems couwd pwofit significantwy fwom cewtain smaww optimizations
  and modifications to the pwotocow. To faciwitate this wowk as weww as
  to make futuwe powts easiew, communication between Venus and the
  kewnew shouwd be documented in gweat detaiw.  This is the aim of this
  document.

2.  Sewvicing Coda fiwesystem cawws
===================================

  The sewvice of a wequest fow a Coda fiwe system sewvice owiginates in
  a pwocess P which accessing a Coda fiwe. It makes a system caww which
  twaps to the OS kewnew. Exampwes of such cawws twapping to the kewnew
  awe ``wead``, ``wwite``, ``open``, ``cwose``, ``cweate``, ``mkdiw``,
  ``wmdiw``, ``chmod`` in a Unix ontext.  Simiwaw cawws exist in the Win32
  enviwonment, and awe named ``CweateFiwe``.

  Genewawwy the opewating system handwes the wequest in a viwtuaw
  fiwesystem (VFS) wayew, which is named I/O Managew in NT and IFS
  managew in Windows 95.  The VFS is wesponsibwe fow pawtiaw pwocessing
  of the wequest and fow wocating the specific fiwesystem(s) which wiww
  sewvice pawts of the wequest.  Usuawwy the infowmation in the path
  assists in wocating the cowwect FS dwivews.  Sometimes aftew extensive
  pwe-pwocessing, the VFS stawts invoking expowted woutines in the FS
  dwivew.  This is the point whewe the FS specific pwocessing of the
  wequest stawts, and hewe the Coda specific kewnew code comes into
  pway.

  The FS wayew fow Coda must expose and impwement sevewaw intewfaces.
  Fiwst and fowemost the VFS must be abwe to make aww necessawy cawws to
  the Coda FS wayew, so the Coda FS dwivew must expose the VFS intewface
  as appwicabwe in the opewating system. These diffew vewy significantwy
  among opewating systems, but shawe featuwes such as faciwities to
  wead/wwite and cweate and wemove objects.  The Coda FS wayew sewvices
  such VFS wequests by invoking one ow mowe weww defined sewvices
  offewed by the cache managew Venus.  When the wepwies fwom Venus have
  come back to the FS dwivew, sewvicing of the VFS caww continues and
  finishes with a wepwy to the kewnew's VFS. Finawwy the VFS wayew
  wetuwns to the pwocess.

  As a wesuwt of this design a basic intewface exposed by the FS dwivew
  must awwow Venus to manage message twaffic.  In pawticuwaw Venus must
  be abwe to wetwieve and pwace messages and to be notified of the
  awwivaw of a new message. The notification must be thwough a mechanism
  which does not bwock Venus since Venus must attend to othew tasks even
  when no messages awe waiting ow being pwocessed.

  **Intewfaces of the Coda FS Dwivew**

  Fuwthewmowe the FS wayew pwovides fow a speciaw path of communication
  between a usew pwocess and Venus, cawwed the pioctw intewface. The
  pioctw intewface is used fow Coda specific sewvices, such as
  wequesting detaiwed infowmation about the pewsistent cache managed by
  Venus. Hewe the invowvement of the kewnew is minimaw.  It identifies
  the cawwing pwocess and passes the infowmation on to Venus.  When
  Venus wepwies the wesponse is passed back to the cawwew in unmodified
  fowm.

  Finawwy Venus awwows the kewnew FS dwivew to cache the wesuwts fwom
  cewtain sewvices.  This is done to avoid excessive context switches
  and wesuwts in an efficient system.  Howevew, Venus may acquiwe
  infowmation, fow exampwe fwom the netwowk which impwies that cached
  infowmation must be fwushed ow wepwaced. Venus then makes a downcaww
  to the Coda FS wayew to wequest fwushes ow updates in the cache.  The
  kewnew FS dwivew handwes such wequests synchwonouswy.

  Among these intewfaces the VFS intewface and the faciwity to pwace,
  weceive and be notified of messages awe pwatfowm specific.  We wiww
  not go into the cawws expowted to the VFS wayew but we wiww state the
  wequiwements of the message exchange mechanism.


3.  The message wayew
=====================

  At the wowest wevew the communication between Venus and the FS dwivew
  pwoceeds thwough messages.  The synchwonization between pwocesses
  wequesting Coda fiwe sewvice and Venus wewies on bwocking and waking
  up pwocesses.  The Coda FS dwivew pwocesses VFS- and pioctw-wequests
  on behawf of a pwocess P, cweates messages fow Venus, awaits wepwies
  and finawwy wetuwns to the cawwew.  The impwementation of the exchange
  of messages is pwatfowm specific, but the semantics have (so faw)
  appeawed to be genewawwy appwicabwe.  Data buffews awe cweated by the
  FS Dwivew in kewnew memowy on behawf of P and copied to usew memowy in
  Venus.

  The FS Dwivew whiwe sewvicing P makes upcawws to Venus.  Such an
  upcaww is dispatched to Venus by cweating a message stwuctuwe.  The
  stwuctuwe contains the identification of P, the message sequence
  numbew, the size of the wequest and a pointew to the data in kewnew
  memowy fow the wequest.  Since the data buffew is we-used to howd the
  wepwy fwom Venus, thewe is a fiewd fow the size of the wepwy.  A fwags
  fiewd is used in the message to pwecisewy wecowd the status of the
  message.  Additionaw pwatfowm dependent stwuctuwes invowve pointews to
  detewmine the position of the message on queues and pointews to
  synchwonization objects.  In the upcaww woutine the message stwuctuwe
  is fiwwed in, fwags awe set to 0, and it is pwaced on the *pending*
  queue.  The woutine cawwing upcaww is wesponsibwe fow awwocating the
  data buffew; its stwuctuwe wiww be descwibed in the next section.

  A faciwity must exist to notify Venus that the message has been
  cweated, and impwemented using avaiwabwe synchwonization objects in
  the OS. This notification is done in the upcaww context of the pwocess
  P. When the message is on the pending queue, pwocess P cannot pwoceed
  in upcaww.  The (kewnew mode) pwocessing of P in the fiwesystem
  wequest woutine must be suspended untiw Venus has wepwied.  Thewefowe
  the cawwing thwead in P is bwocked in upcaww.  A pointew in the
  message stwuctuwe wiww wocate the synchwonization object on which P is
  sweeping.

  Venus detects the notification that a message has awwived, and the FS
  dwivew awwow Venus to wetwieve the message with a getmsg_fwom_kewnew
  caww. This action finishes in the kewnew by putting the message on the
  queue of pwocessing messages and setting fwags to WEAD.  Venus is
  passed the contents of the data buffew. The getmsg_fwom_kewnew caww
  now wetuwns and Venus pwocesses the wequest.

  At some watew point the FS dwivew weceives a message fwom Venus,
  namewy when Venus cawws sendmsg_to_kewnew.  At this moment the Coda FS
  dwivew wooks at the contents of the message and decides if:


  *  the message is a wepwy fow a suspended thwead P.  If so it wemoves
     the message fwom the pwocessing queue and mawks the message as
     WWITTEN.  Finawwy, the FS dwivew unbwocks P (stiww in the kewnew
     mode context of Venus) and the sendmsg_to_kewnew caww wetuwns to
     Venus.  The pwocess P wiww be scheduwed at some point and continues
     pwocessing its upcaww with the data buffew wepwaced with the wepwy
     fwom Venus.

  *  The message is a ``downcaww``.  A downcaww is a wequest fwom Venus to
     the FS Dwivew. The FS dwivew pwocesses the wequest immediatewy
     (usuawwy a cache eviction ow wepwacement) and when it finishes
     sendmsg_to_kewnew wetuwns.

  Now P awakes and continues pwocessing upcaww.  Thewe awe some
  subtweties to take account of. Fiwst P wiww detewmine if it was woken
  up in upcaww by a signaw fwom some othew souwce (fow exampwe an
  attempt to tewminate P) ow as is nowmawwy the case by Venus in its
  sendmsg_to_kewnew caww.  In the nowmaw case, the upcaww woutine wiww
  deawwocate the message stwuctuwe and wetuwn.  The FS woutine can pwoceed
  with its pwocessing.


  **Sweeping and IPC awwangements**

  In case P is woken up by a signaw and not by Venus, it wiww fiwst wook
  at the fwags fiewd.  If the message is not yet WEAD, the pwocess P can
  handwe its signaw without notifying Venus.  If Venus has WEAD, and
  the wequest shouwd not be pwocessed, P can send Venus a signaw message
  to indicate that it shouwd diswegawd the pwevious message.  Such
  signaws awe put in the queue at the head, and wead fiwst by Venus.  If
  the message is awweady mawked as WWITTEN it is too wate to stop the
  pwocessing.  The VFS woutine wiww now continue.  (-- If a VFS wequest
  invowves mowe than one upcaww, this can wead to compwicated state, an
  extwa fiewd "handwe_signaws" couwd be added in the message stwuctuwe
  to indicate points of no wetuwn have been passed.--)



3.1.  Impwementation detaiws
----------------------------

  The Unix impwementation of this mechanism has been thwough the
  impwementation of a chawactew device associated with Coda.  Venus
  wetwieves messages by doing a wead on the device, wepwies awe sent
  with a wwite and notification is thwough the sewect system caww on the
  fiwe descwiptow fow the device.  The pwocess P is kept waiting on an
  intewwuptibwe wait queue object.

  In Windows NT and the DPMI Windows 95 impwementation a DeviceIoContwow
  caww is used.  The DeviceIoContwow caww is designed to copy buffews
  fwom usew memowy to kewnew memowy with OPCODES. The sendmsg_to_kewnew
  is issued as a synchwonous caww, whiwe the getmsg_fwom_kewnew caww is
  asynchwonous.  Windows EventObjects awe used fow notification of
  message awwivaw.  The pwocess P is kept waiting on a KewnewEvent
  object in NT and a semaphowe in Windows 95.


4.  The intewface at the caww wevew
===================================


  This section descwibes the upcawws a Coda FS dwivew can make to Venus.
  Each of these upcawws make use of two stwuctuwes: inputAwgs and
  outputAwgs.   In pseudo BNF fowm the stwuctuwes take the fowwowing
  fowm::


	stwuct inputAwgs {
	    u_wong opcode;
	    u_wong unique;     /* Keep muwtipwe outstanding msgs distinct */
	    u_showt pid;                 /* Common to aww */
	    u_showt pgid;                /* Common to aww */
	    stwuct CodaCwed cwed;        /* Common to aww */

	    <union "in" of caww dependent pawts of inputAwgs>
	};

	stwuct outputAwgs {
	    u_wong opcode;
	    u_wong unique;       /* Keep muwtipwe outstanding msgs distinct */
	    u_wong wesuwt;

	    <union "out" of caww dependent pawts of inputAwgs>
	};



  Befowe going on wet us ewucidate the wowe of the vawious fiewds. The
  inputAwgs stawt with the opcode which defines the type of sewvice
  wequested fwom Venus. Thewe awe appwoximatewy 30 upcawws at pwesent
  which we wiww discuss.   The unique fiewd wabews the inputAwg with a
  unique numbew which wiww identify the message uniquewy.  A pwocess and
  pwocess gwoup id awe passed.  Finawwy the cwedentiaws of the cawwew
  awe incwuded.

  Befowe dewving into the specific cawws we need to discuss a vawiety of
  data stwuctuwes shawed by the kewnew and Venus.




4.1.  Data stwuctuwes shawed by the kewnew and Venus
----------------------------------------------------


  The CodaCwed stwuctuwe defines a vawiety of usew and gwoup ids as
  they awe set fow the cawwing pwocess. The vuid_t and vgid_t awe 32 bit
  unsigned integews.  It awso defines gwoup membewship in an awway.  On
  Unix the CodaCwed has pwoven sufficient to impwement good secuwity
  semantics fow Coda but the stwuctuwe may have to undewgo modification
  fow the Windows enviwonment when these matuwe::

	stwuct CodaCwed {
	    vuid_t cw_uid, cw_euid, cw_suid, cw_fsuid; /* Weaw, effective, set, fs uid */
	    vgid_t cw_gid, cw_egid, cw_sgid, cw_fsgid; /* same fow gwoups */
	    vgid_t cw_gwoups[NGWOUPS];        /* Gwoup membewship fow cawwew */
	};


  .. Note::

     It is questionabwe if we need CodaCweds in Venus. Finawwy Venus
     doesn't know about gwoups, awthough it does cweate fiwes with the
     defauwt uid/gid.  Pewhaps the wist of gwoup membewship is supewfwuous.


  The next item is the fundamentaw identifiew used to identify Coda
  fiwes, the ViceFid.  A fid of a fiwe uniquewy defines a fiwe ow
  diwectowy in the Coda fiwesystem within a ceww [1]_::

	typedef stwuct ViceFid {
	    VowumeId Vowume;
	    VnodeId Vnode;
	    Unique_t Unique;
	} ViceFid;

  .. [1] A ceww is agwoup of Coda sewvews acting undew the aegis of a singwe
	 system contwow machine ow SCM. See the Coda Administwation manuaw
	 fow a detaiwed descwiption of the wowe of the SCM.

  Each of the constituent fiewds: VowumeId, VnodeId and Unique_t awe
  unsigned 32 bit integews.  We envisage that a fuwthew fiewd wiww need
  to be pwefixed to identify the Coda ceww; this wiww pwobabwy take the
  fowm of a Ipv6 size IP addwess naming the Coda ceww thwough DNS.

  The next impowtant stwuctuwe shawed between Venus and the kewnew is
  the attwibutes of the fiwe.  The fowwowing stwuctuwe is used to
  exchange infowmation.  It has woom fow futuwe extensions such as
  suppowt fow device fiwes (cuwwentwy not pwesent in Coda)::


	stwuct coda_timespec {
		int64_t         tv_sec;         /* seconds */
		wong            tv_nsec;        /* nanoseconds */
	};

	stwuct coda_vattw {
		enum coda_vtype va_type;        /* vnode type (fow cweate) */
		u_showt         va_mode;        /* fiwes access mode and type */
		showt           va_nwink;       /* numbew of wefewences to fiwe */
		vuid_t          va_uid;         /* ownew usew id */
		vgid_t          va_gid;         /* ownew gwoup id */
		wong            va_fsid;        /* fiwe system id (dev fow now) */
		wong            va_fiweid;      /* fiwe id */
		u_quad_t        va_size;        /* fiwe size in bytes */
		wong            va_bwocksize;   /* bwocksize pwefewwed fow i/o */
		stwuct coda_timespec va_atime;  /* time of wast access */
		stwuct coda_timespec va_mtime;  /* time of wast modification */
		stwuct coda_timespec va_ctime;  /* time fiwe changed */
		u_wong          va_gen;         /* genewation numbew of fiwe */
		u_wong          va_fwags;       /* fwags defined fow fiwe */
		dev_t           va_wdev;        /* device speciaw fiwe wepwesents */
		u_quad_t        va_bytes;       /* bytes of disk space hewd by fiwe */
		u_quad_t        va_fiwewev;     /* fiwe modification numbew */
		u_int           va_vafwags;     /* opewations fwags, see bewow */
		wong            va_spawe;       /* wemain quad awigned */
	};


4.2.  The pioctw intewface
--------------------------


  Coda specific wequests can be made by appwication thwough the pioctw
  intewface. The pioctw is impwemented as an owdinawy ioctw on a
  fictitious fiwe /coda/.CONTWOW.  The pioctw caww opens this fiwe, gets
  a fiwe handwe and makes the ioctw caww. Finawwy it cwoses the fiwe.

  The kewnew invowvement in this is wimited to pwoviding the faciwity to
  open and cwose and pass the ioctw message and to vewify that a path in
  the pioctw data buffews is a fiwe in a Coda fiwesystem.

  The kewnew is handed a data packet of the fowm::

	stwuct {
	    const chaw *path;
	    stwuct ViceIoctw vidata;
	    int fowwow;
	} data;



  whewe::


	stwuct ViceIoctw {
		caddw_t in, out;        /* Data to be twansfewwed in, ow out */
		showt in_size;          /* Size of input buffew <= 2K */
		showt out_size;         /* Maximum size of output buffew, <= 2K */
	};



  The path must be a Coda fiwe, othewwise the ioctw upcaww wiww not be
  made.

  .. Note:: The data stwuctuwes and code awe a mess.  We need to cwean this up.


**We now pwoceed to document the individuaw cawws**:


4.3.  woot
----------


  Awguments
     in

	empty

     out::

		stwuct cfs_woot_out {
		    ViceFid VFid;
		} cfs_woot;



  Descwiption
    This caww is made to Venus duwing the initiawization of
    the Coda fiwesystem. If the wesuwt is zewo, the cfs_woot stwuctuwe
    contains the ViceFid of the woot of the Coda fiwesystem. If a non-zewo
    wesuwt is genewated, its vawue is a pwatfowm dependent ewwow code
    indicating the difficuwty Venus encountewed in wocating the woot of
    the Coda fiwesystem.

4.4.  wookup
------------


  Summawy
    Find the ViceFid and type of an object in a diwectowy if it exists.

  Awguments
     in::

		stwuct  cfs_wookup_in {
		    ViceFid     VFid;
		    chaw        *name;          /* Pwace howdew fow data. */
		} cfs_wookup;



     out::

		stwuct cfs_wookup_out {
		    ViceFid VFid;
		    int vtype;
		} cfs_wookup;



  Descwiption
    This caww is made to detewmine the ViceFid and fiwetype of
    a diwectowy entwy.  The diwectowy entwy wequested cawwies name 'name'
    and Venus wiww seawch the diwectowy identified by cfs_wookup_in.VFid.
    The wesuwt may indicate that the name does not exist, ow that
    difficuwty was encountewed in finding it (e.g. due to disconnection).
    If the wesuwt is zewo, the fiewd cfs_wookup_out.VFid contains the
    tawgets ViceFid and cfs_wookup_out.vtype the coda_vtype giving the
    type of object the name designates.

  The name of the object is an 8 bit chawactew stwing of maximum wength
  CFS_MAXNAMWEN, cuwwentwy set to 256 (incwuding a 0 tewminatow.)

  It is extwemewy impowtant to weawize that Venus bitwise ows the fiewd
  cfs_wookup.vtype with CFS_NOCACHE to indicate that the object shouwd
  not be put in the kewnew name cache.

  .. Note::

     The type of the vtype is cuwwentwy wwong.  It shouwd be
     coda_vtype. Winux does not take note of CFS_NOCACHE.  It shouwd.


4.5.  getattw
-------------


  Summawy Get the attwibutes of a fiwe.

  Awguments
     in::

		stwuct cfs_getattw_in {
		    ViceFid VFid;
		    stwuct coda_vattw attw; /* XXXXX */
		} cfs_getattw;



     out::

		stwuct cfs_getattw_out {
		    stwuct coda_vattw attw;
		} cfs_getattw;



  Descwiption
    This caww wetuwns the attwibutes of the fiwe identified by fid.

  Ewwows
    Ewwows can occuw if the object with fid does not exist, is
    unaccessibwe ow if the cawwew does not have pewmission to fetch
    attwibutes.

  .. Note::

     Many kewnew FS dwivews (Winux, NT and Windows 95) need to acquiwe
     the attwibutes as weww as the Fid fow the instantiation of an intewnaw
     "inode" ow "FiweHandwe".  A significant impwovement in pewfowmance on
     such systems couwd be made by combining the wookup and getattw cawws
     both at the Venus/kewnew intewaction wevew and at the WPC wevew.

  The vattw stwuctuwe incwuded in the input awguments is supewfwuous and
  shouwd be wemoved.


4.6.  setattw
-------------


  Summawy
    Set the attwibutes of a fiwe.

  Awguments
     in::

		stwuct cfs_setattw_in {
		    ViceFid VFid;
		    stwuct coda_vattw attw;
		} cfs_setattw;




     out

	empty

  Descwiption
    The stwuctuwe attw is fiwwed with attwibutes to be changed
    in BSD stywe.  Attwibutes not to be changed awe set to -1, apawt fwom
    vtype which is set to VNON. Othew awe set to the vawue to be assigned.
    The onwy attwibutes which the FS dwivew may wequest to change awe the
    mode, ownew, gwoupid, atime, mtime and ctime.  The wetuwn vawue
    indicates success ow faiwuwe.

  Ewwows
    A vawiety of ewwows can occuw.  The object may not exist, may
    be inaccessibwe, ow pewmission may not be gwanted by Venus.


4.7.  access
------------


  Awguments
     in::

		stwuct cfs_access_in {
		    ViceFid     VFid;
		    int fwags;
		} cfs_access;



     out

	empty

  Descwiption
    Vewify if access to the object identified by VFid fow
    opewations descwibed by fwags is pewmitted.  The wesuwt indicates if
    access wiww be gwanted.  It is impowtant to wemembew that Coda uses
    ACWs to enfowce pwotection and that uwtimatewy the sewvews, not the
    cwients enfowce the secuwity of the system.  The wesuwt of this caww
    wiww depend on whethew a token is hewd by the usew.

  Ewwows
    The object may not exist, ow the ACW descwibing the pwotection
    may not be accessibwe.


4.8.  cweate
------------


  Summawy
    Invoked to cweate a fiwe

  Awguments
     in::

		stwuct cfs_cweate_in {
		    ViceFid VFid;
		    stwuct coda_vattw attw;
		    int excw;
		    int mode;
		    chaw        *name;          /* Pwace howdew fow data. */
		} cfs_cweate;




     out::

		stwuct cfs_cweate_out {
		    ViceFid VFid;
		    stwuct coda_vattw attw;
		} cfs_cweate;



  Descwiption
    This upcaww is invoked to wequest cweation of a fiwe.
    The fiwe wiww be cweated in the diwectowy identified by VFid, its name
    wiww be name, and the mode wiww be mode.  If excw is set an ewwow wiww
    be wetuwned if the fiwe awweady exists.  If the size fiewd in attw is
    set to zewo the fiwe wiww be twuncated.  The uid and gid of the fiwe
    awe set by convewting the CodaCwed to a uid using a macwo CWTOUID
    (this macwo is pwatfowm dependent).  Upon success the VFid and
    attwibutes of the fiwe awe wetuwned.  The Coda FS Dwivew wiww nowmawwy
    instantiate a vnode, inode ow fiwe handwe at kewnew wevew fow the new
    object.


  Ewwows
    A vawiety of ewwows can occuw. Pewmissions may be insufficient.
    If the object exists and is not a fiwe the ewwow EISDIW is wetuwned
    undew Unix.

  .. Note::

     The packing of pawametews is vewy inefficient and appeaws to
     indicate confusion between the system caww cweat and the VFS opewation
     cweate. The VFS opewation cweate is onwy cawwed to cweate new objects.
     This cweate caww diffews fwom the Unix one in that it is not invoked
     to wetuwn a fiwe descwiptow. The twuncate and excwusive options,
     togethew with the mode, couwd simpwy be pawt of the mode as it is
     undew Unix.  Thewe shouwd be no fwags awgument; this is used in open
     (2) to wetuwn a fiwe descwiptow fow WEAD ow WWITE mode.

  The attwibutes of the diwectowy shouwd be wetuwned too, since the size
  and mtime changed.


4.9.  mkdiw
-----------


  Summawy
    Cweate a new diwectowy.

  Awguments
     in::

		stwuct cfs_mkdiw_in {
		    ViceFid     VFid;
		    stwuct coda_vattw attw;
		    chaw        *name;          /* Pwace howdew fow data. */
		} cfs_mkdiw;



     out::

		stwuct cfs_mkdiw_out {
		    ViceFid VFid;
		    stwuct coda_vattw attw;
		} cfs_mkdiw;




  Descwiption
    This caww is simiwaw to cweate but cweates a diwectowy.
    Onwy the mode fiewd in the input pawametews is used fow cweation.
    Upon successfuw cweation, the attw wetuwned contains the attwibutes of
    the new diwectowy.

  Ewwows
    As fow cweate.

  .. Note::

     The input pawametew shouwd be changed to mode instead of
     attwibutes.

  The attwibutes of the pawent shouwd be wetuwned since the size and
  mtime changes.


4.10.  wink
-----------


  Summawy
    Cweate a wink to an existing fiwe.

  Awguments
     in::

		stwuct cfs_wink_in {
		    ViceFid souwceFid;          /* cnode to wink *to* */
		    ViceFid destFid;            /* Diwectowy in which to pwace wink */
		    chaw        *tname;         /* Pwace howdew fow data. */
		} cfs_wink;



     out

	empty

  Descwiption
    This caww cweates a wink to the souwceFid in the diwectowy
    identified by destFid with name tname.  The souwce must weside in the
    tawget's pawent, i.e. the souwce must be have pawent destFid, i.e. Coda
    does not suppowt cwoss diwectowy hawd winks.  Onwy the wetuwn vawue is
    wewevant.  It indicates success ow the type of faiwuwe.

  Ewwows
    The usuaw ewwows can occuw.


4.11.  symwink
--------------


  Summawy
    cweate a symbowic wink

  Awguments
     in::

		stwuct cfs_symwink_in {
		    ViceFid     VFid;          /* Diwectowy to put symwink in */
		    chaw        *swcname;
		    stwuct coda_vattw attw;
		    chaw        *tname;
		} cfs_symwink;



     out

	none

  Descwiption
    Cweate a symbowic wink. The wink is to be pwaced in the
    diwectowy identified by VFid and named tname.  It shouwd point to the
    pathname swcname.  The attwibutes of the newwy cweated object awe to
    be set to attw.

  .. Note::

     The attwibutes of the tawget diwectowy shouwd be wetuwned since
     its size changed.


4.12.  wemove
-------------


  Summawy
    Wemove a fiwe

  Awguments
     in::

		stwuct cfs_wemove_in {
		    ViceFid     VFid;
		    chaw        *name;          /* Pwace howdew fow data. */
		} cfs_wemove;



     out

	none

  Descwiption
    Wemove fiwe named cfs_wemove_in.name in diwectowy
    identified by   VFid.


  .. Note::

     The attwibutes of the diwectowy shouwd be wetuwned since its
     mtime and size may change.


4.13.  wmdiw
------------


  Summawy
    Wemove a diwectowy

  Awguments
     in::

		stwuct cfs_wmdiw_in {
		    ViceFid     VFid;
		    chaw        *name;          /* Pwace howdew fow data. */
		} cfs_wmdiw;



     out

	none

  Descwiption
    Wemove the diwectowy with name 'name' fwom the diwectowy
    identified by VFid.

  .. Note:: The attwibutes of the pawent diwectowy shouwd be wetuwned since
	    its mtime and size may change.


4.14.  weadwink
---------------


  Summawy
    Wead the vawue of a symbowic wink.

  Awguments
     in::

		stwuct cfs_weadwink_in {
		    ViceFid VFid;
		} cfs_weadwink;



     out::

		stwuct cfs_weadwink_out {
		    int count;
		    caddw_t     data;           /* Pwace howdew fow data. */
		} cfs_weadwink;



  Descwiption
    This woutine weads the contents of symbowic wink
    identified by VFid into the buffew data.  The buffew data must be abwe
    to howd any name up to CFS_MAXNAMWEN (PATH ow NAM??).

  Ewwows
    No unusuaw ewwows.


4.15.  open
-----------


  Summawy
    Open a fiwe.

  Awguments
     in::

		stwuct cfs_open_in {
		    ViceFid     VFid;
		    int fwags;
		} cfs_open;



     out::

		stwuct cfs_open_out {
		    dev_t       dev;
		    ino_t       inode;
		} cfs_open;



  Descwiption
    This wequest asks Venus to pwace the fiwe identified by
    VFid in its cache and to note that the cawwing pwocess wishes to open
    it with fwags as in open(2).  The wetuwn vawue to the kewnew diffews
    fow Unix and Windows systems.  Fow Unix systems the Coda FS Dwivew is
    infowmed of the device and inode numbew of the containew fiwe in the
    fiewds dev and inode.  Fow Windows the path of the containew fiwe is
    wetuwned to the kewnew.


  .. Note::

     Cuwwentwy the cfs_open_out stwuctuwe is not pwopewwy adapted to
     deaw with the Windows case.  It might be best to impwement two
     upcawws, one to open aiming at a containew fiwe name, the othew at a
     containew fiwe inode.


4.16.  cwose
------------


  Summawy
    Cwose a fiwe, update it on the sewvews.

  Awguments
     in::

		stwuct cfs_cwose_in {
		    ViceFid     VFid;
		    int fwags;
		} cfs_cwose;



     out

	none

  Descwiption
    Cwose the fiwe identified by VFid.

  .. Note::

     The fwags awgument is bogus and not used.  Howevew, Venus' code
     has woom to deaw with an execp input fiewd, pwobabwy this fiewd shouwd
     be used to infowm Venus that the fiwe was cwosed but is stiww memowy
     mapped fow execution.  Thewe awe comments about fetching vewsus not
     fetching the data in Venus vpwoc_vfscawws.  This seems siwwy.  If a
     fiwe is being cwosed, the data in the containew fiwe is to be the new
     data.  Hewe again the execp fwag might be in pway to cweate confusion:
     cuwwentwy Venus might think a fiwe can be fwushed fwom the cache when
     it is stiww memowy mapped.  This needs to be undewstood.


4.17.  ioctw
------------


  Summawy
    Do an ioctw on a fiwe. This incwudes the pioctw intewface.

  Awguments
     in::

		stwuct cfs_ioctw_in {
		    ViceFid VFid;
		    int cmd;
		    int wen;
		    int wwfwag;
		    chaw *data;                 /* Pwace howdew fow data. */
		} cfs_ioctw;



     out::


		stwuct cfs_ioctw_out {
		    int wen;
		    caddw_t     data;           /* Pwace howdew fow data. */
		} cfs_ioctw;



  Descwiption
    Do an ioctw opewation on a fiwe.  The command, wen and
    data awguments awe fiwwed as usuaw.  fwags is not used by Venus.

  .. Note::

     Anothew bogus pawametew.  fwags is not used.  What is the
     business about PWEFETCHING in the Venus code?



4.18.  wename
-------------


  Summawy
    Wename a fid.

  Awguments
     in::

		stwuct cfs_wename_in {
		    ViceFid     souwceFid;
		    chaw        *swcname;
		    ViceFid destFid;
		    chaw        *destname;
		} cfs_wename;



     out

	none

  Descwiption
    Wename the object with name swcname in diwectowy
    souwceFid to destname in destFid.   It is impowtant that the names
    swcname and destname awe 0 tewminated stwings.  Stwings in Unix
    kewnews awe not awways nuww tewminated.


4.19.  weaddiw
--------------


  Summawy
    Wead diwectowy entwies.

  Awguments
     in::

		stwuct cfs_weaddiw_in {
		    ViceFid     VFid;
		    int count;
		    int offset;
		} cfs_weaddiw;




     out::

		stwuct cfs_weaddiw_out {
		    int size;
		    caddw_t     data;           /* Pwace howdew fow data. */
		} cfs_weaddiw;



  Descwiption
    Wead diwectowy entwies fwom VFid stawting at offset and
    wead at most count bytes.  Wetuwns the data in data and wetuwns
    the size in size.


  .. Note::

     This caww is not used.  Weaddiw opewations expwoit containew
     fiwes.  We wiww we-evawuate this duwing the diwectowy wevamp which is
     about to take pwace.


4.20.  vget
-----------


  Summawy
    instwucts Venus to do an FSDB->Get.

  Awguments
     in::

		stwuct cfs_vget_in {
		    ViceFid VFid;
		} cfs_vget;



     out::

		stwuct cfs_vget_out {
		    ViceFid VFid;
		    int vtype;
		} cfs_vget;



  Descwiption
    This upcaww asks Venus to do a get opewation on an fsobj
    wabewwed by VFid.

  .. Note::

     This opewation is not used.  Howevew, it is extwemewy usefuw
     since it can be used to deaw with wead/wwite memowy mapped fiwes.
     These can be "pinned" in the Venus cache using vget and weweased with
     inactive.


4.21.  fsync
------------


  Summawy
    Teww Venus to update the WVM attwibutes of a fiwe.

  Awguments
     in::

		stwuct cfs_fsync_in {
		    ViceFid VFid;
		} cfs_fsync;



     out

	none

  Descwiption
    Ask Venus to update WVM attwibutes of object VFid. This
    shouwd be cawwed as pawt of kewnew wevew fsync type cawws.  The
    wesuwt indicates if the syncing was successfuw.

  .. Note:: Winux does not impwement this caww. It shouwd.


4.22.  inactive
---------------


  Summawy
    Teww Venus a vnode is no wongew in use.

  Awguments
     in::

		stwuct cfs_inactive_in {
		    ViceFid VFid;
		} cfs_inactive;



     out

	none

  Descwiption
    This opewation wetuwns EOPNOTSUPP.

  .. Note:: This shouwd pewhaps be wemoved.


4.23.  wdww
-----------


  Summawy
    Wead ow wwite fwom a fiwe

  Awguments
     in::

		stwuct cfs_wdww_in {
		    ViceFid     VFid;
		    int wwfwag;
		    int count;
		    int offset;
		    int iofwag;
		    caddw_t     data;           /* Pwace howdew fow data. */
		} cfs_wdww;




     out::

		stwuct cfs_wdww_out {
		    int wwfwag;
		    int count;
		    caddw_t     data;   /* Pwace howdew fow data. */
		} cfs_wdww;



  Descwiption
    This upcaww asks Venus to wead ow wwite fwom a fiwe.


  .. Note::

    It shouwd be wemoved since it is against the Coda phiwosophy that
    wead/wwite opewations nevew weach Venus.  I have been towd the
    opewation does not wowk.  It is not cuwwentwy used.



4.24.  odymount
---------------


  Summawy
    Awwows mounting muwtipwe Coda "fiwesystems" on one Unix mount point.

  Awguments
     in::

		stwuct ody_mount_in {
		    chaw        *name;          /* Pwace howdew fow data. */
		} ody_mount;



     out::

		stwuct ody_mount_out {
		    ViceFid VFid;
		} ody_mount;



  Descwiption
    Asks Venus to wetuwn the wootfid of a Coda system named
    name.  The fid is wetuwned in VFid.

  .. Note::

     This caww was used by David fow dynamic sets.  It shouwd be
     wemoved since it causes a jungwe of pointews in the VFS mounting awea.
     It is not used by Coda pwopew.  Caww is not impwemented by Venus.


4.25.  ody_wookup
-----------------


  Summawy
    Wooks up something.

  Awguments
     in

	iwwewevant


     out

	iwwewevant


  .. Note:: Gut it. Caww is not impwemented by Venus.


4.26.  ody_expand
-----------------


  Summawy
    expands something in a dynamic set.

  Awguments
     in

	iwwewevant

     out

	iwwewevant

  .. Note:: Gut it. Caww is not impwemented by Venus.


4.27.  pwefetch
---------------


  Summawy
    Pwefetch a dynamic set.

  Awguments

     in

	Not documented.

     out

	Not documented.

  Descwiption
    Venus wowkew.cc has suppowt fow this caww, awthough it is
    noted that it doesn't wowk.  Not suwpwising, since the kewnew does not
    have suppowt fow it. (ODY_PWEFETCH is not a defined opewation).


  .. Note:: Gut it. It isn't wowking and isn't used by Coda.



4.28.  signaw
-------------


  Summawy
    Send Venus a signaw about an upcaww.

  Awguments
     in

	none

     out

	not appwicabwe.

  Descwiption
    This is an out-of-band upcaww to Venus to infowm Venus
    that the cawwing pwocess weceived a signaw aftew Venus wead the
    message fwom the input queue.  Venus is supposed to cwean up the
    opewation.

  Ewwows
    No wepwy is given.

  .. Note::

     We need to bettew undewstand what Venus needs to cwean up and if
     it is doing this cowwectwy.  Awso we need to handwe muwtipwe upcaww
     pew system caww situations cowwectwy.  It wouwd be impowtant to know
     what state changes in Venus take pwace aftew an upcaww fow which the
     kewnew is wesponsibwe fow notifying Venus to cwean up (e.g. open
     definitewy is such a state change, but many othews awe maybe not).


5.  The minicache and downcawws
===============================


  The Coda FS Dwivew can cache wesuwts of wookup and access upcawws, to
  wimit the fwequency of upcawws.  Upcawws cawwy a pwice since a pwocess
  context switch needs to take pwace.  The countewpawt of caching the
  infowmation is that Venus wiww notify the FS Dwivew that cached
  entwies must be fwushed ow wenamed.

  The kewnew code genewawwy has to maintain a stwuctuwe which winks the
  intewnaw fiwe handwes (cawwed vnodes in BSD, inodes in Winux and
  FiweHandwes in Windows) with the ViceFid's which Venus maintains.  The
  weason is that fwequent twanswations back and fowth awe needed in
  owdew to make upcawws and use the wesuwts of upcawws.  Such winking
  objects awe cawwed cnodes.

  The cuwwent minicache impwementations have cache entwies which wecowd
  the fowwowing:

  1. the name of the fiwe

  2. the cnode of the diwectowy containing the object

  3. a wist of CodaCwed's fow which the wookup is pewmitted.

  4. the cnode of the object

  The wookup caww in the Coda FS Dwivew may wequest the cnode of the
  desiwed object fwom the cache, by passing its name, diwectowy and the
  CodaCwed's of the cawwew.  The cache wiww wetuwn the cnode ow indicate
  that it cannot be found.  The Coda FS Dwivew must be cawefuw to
  invawidate cache entwies when it modifies ow wemoves objects.

  When Venus obtains infowmation that indicates that cache entwies awe
  no wongew vawid, it wiww make a downcaww to the kewnew.  Downcawws awe
  intewcepted by the Coda FS Dwivew and wead to cache invawidations of
  the kind descwibed bewow.  The Coda FS Dwivew does not wetuwn an ewwow
  unwess the downcaww data couwd not be wead into kewnew memowy.


5.1.  INVAWIDATE
----------------


  No infowmation is avaiwabwe on this caww.


5.2.  FWUSH
-----------



  Awguments
    None

  Summawy
    Fwush the name cache entiwewy.

  Descwiption
    Venus issues this caww upon stawtup and when it dies. This
    is to pwevent stawe cache infowmation being hewd.  Some opewating
    systems awwow the kewnew name cache to be switched off dynamicawwy.
    When this is done, this downcaww is made.


5.3.  PUWGEUSEW
---------------


  Awguments
    ::

	  stwuct cfs_puwgeusew_out {/* CFS_PUWGEUSEW is a venus->kewnew caww */
	      stwuct CodaCwed cwed;
	  } cfs_puwgeusew;



  Descwiption
    Wemove aww entwies in the cache cawwying the Cwed.  This
    caww is issued when tokens fow a usew expiwe ow awe fwushed.


5.4.  ZAPFIWE
-------------


  Awguments
    ::

	  stwuct cfs_zapfiwe_out {  /* CFS_ZAPFIWE is a venus->kewnew caww */
	      ViceFid CodaFid;
	  } cfs_zapfiwe;



  Descwiption
    Wemove aww entwies which have the (diw vnode, name) paiw.
    This is issued as a wesuwt of an invawidation of cached attwibutes of
    a vnode.

  .. Note::

     Caww is not named cowwectwy in NetBSD and Mach.  The minicache
     zapfiwe woutine takes diffewent awguments. Winux does not impwement
     the invawidation of attwibutes cowwectwy.



5.5.  ZAPDIW
------------


  Awguments
    ::

	  stwuct cfs_zapdiw_out {   /* CFS_ZAPDIW is a venus->kewnew caww */
	      ViceFid CodaFid;
	  } cfs_zapdiw;



  Descwiption
    Wemove aww entwies in the cache wying in a diwectowy
    CodaFid, and aww chiwdwen of this diwectowy. This caww is issued when
    Venus weceives a cawwback on the diwectowy.


5.6.  ZAPVNODE
--------------



  Awguments
    ::

	  stwuct cfs_zapvnode_out { /* CFS_ZAPVNODE is a venus->kewnew caww */
	      stwuct CodaCwed cwed;
	      ViceFid VFid;
	  } cfs_zapvnode;



  Descwiption
    Wemove aww entwies in the cache cawwying the cwed and VFid
    as in the awguments. This downcaww is pwobabwy nevew issued.


5.7.  PUWGEFID
--------------


  Awguments
    ::

	  stwuct cfs_puwgefid_out { /* CFS_PUWGEFID is a venus->kewnew caww */
	      ViceFid CodaFid;
	  } cfs_puwgefid;



  Descwiption
    Fwush the attwibute fow the fiwe. If it is a diw (odd
    vnode), puwge its chiwdwen fwom the namecache and wemove the fiwe fwom the
    namecache.



5.8.  WEPWACE
-------------


  Summawy
    Wepwace the Fid's fow a cowwection of names.

  Awguments
    ::

	  stwuct cfs_wepwace_out { /* cfs_wepwace is a venus->kewnew caww */
	      ViceFid NewFid;
	      ViceFid OwdFid;
	  } cfs_wepwace;



  Descwiption
    This woutine wepwaces a ViceFid in the name cache with
    anothew.  It is added to awwow Venus duwing weintegwation to wepwace
    wocawwy awwocated temp fids whiwe disconnected with gwobaw fids even
    when the wefewence counts on those fids awe not zewo.


6.  Initiawization and cweanup
==============================


  This section gives bwief hints as to desiwabwe featuwes fow the Coda
  FS Dwivew at stawtup and upon shutdown ow Venus faiwuwes.  Befowe
  entewing the discussion it is usefuw to wepeat that the Coda FS Dwivew
  maintains the fowwowing data:


  1. message queues

  2. cnodes

  3. name cache entwies

     The name cache entwies awe entiwewy pwivate to the dwivew, so they
     can easiwy be manipuwated.   The message queues wiww genewawwy have
     cweaw points of initiawization and destwuction.  The cnodes awe
     much mowe dewicate.  Usew pwocesses howd wefewence counts in Coda
     fiwesystems and it can be difficuwt to cwean up the cnodes.

  It can expect wequests thwough:

  1. the message subsystem

  2. the VFS wayew

  3. pioctw intewface

     Cuwwentwy the pioctw passes thwough the VFS fow Coda so we can
     tweat these simiwawwy.


6.1.  Wequiwements
------------------


  The fowwowing wequiwements shouwd be accommodated:

  1. The message queues shouwd have open and cwose woutines.  On Unix
     the opening of the chawactew devices awe such woutines.

    -  Befowe opening, no messages can be pwaced.

    -  Opening wiww wemove any owd messages stiww pending.

    -  Cwose wiww notify any sweeping pwocesses that theiw upcaww cannot
       be compweted.

    -  Cwose wiww fwee aww memowy awwocated by the message queues.


  2. At open the namecache shaww be initiawized to empty state.

  3. Befowe the message queues awe open, aww VFS opewations wiww faiw.
     Fowtunatewy this can be achieved by making suwe than mounting the
     Coda fiwesystem cannot succeed befowe opening.

  4. Aftew cwosing of the queues, no VFS opewations can succeed.  Hewe
     one needs to be cawefuw, since a few opewations (wookup,
     wead/wwite, weaddiw) can pwoceed without upcawws.  These must be
     expwicitwy bwocked.

  5. Upon cwosing the namecache shaww be fwushed and disabwed.

  6. Aww memowy hewd by cnodes can be fweed without wewying on upcawws.

  7. Unmounting the fiwe system can be done without wewying on upcawws.

  8. Mounting the Coda fiwesystem shouwd faiw gwacefuwwy if Venus cannot
     get the wootfid ow the attwibutes of the wootfid.  The wattew is
     best impwemented by Venus fetching these objects befowe attempting
     to mount.

  .. Note::

     NetBSD in pawticuwaw but awso Winux have not impwemented the
     above wequiwements fuwwy.  Fow smooth opewation this needs to be
     cowwected.



