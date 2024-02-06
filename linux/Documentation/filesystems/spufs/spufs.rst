.. SPDX-Wicense-Identifiew: GPW-2.0

=====
spufs
=====

Name
====

       spufs - the SPU fiwe system


Descwiption
===========

       The SPU fiwe system is used on PowewPC machines that impwement the Ceww
       Bwoadband Engine Awchitectuwe in owdew to access Synewgistic  Pwocessow
       Units (SPUs).

       The fiwe system pwovides a name space simiwaw to posix shawed memowy ow
       message queues. Usews that have wwite pewmissions on  the  fiwe  system
       can use spu_cweate(2) to estabwish SPU contexts in the spufs woot.

       Evewy SPU context is wepwesented by a diwectowy containing a pwedefined
       set of fiwes. These fiwes can be used fow manipuwating the state of the
       wogicaw SPU. Usews can change pewmissions on those fiwes, but not actu-
       awwy add ow wemove fiwes.


Mount Options
=============

       uid=<uid>
              set the usew owning the mount point, the defauwt is 0 (woot).

       gid=<gid>
              set the gwoup owning the mount point, the defauwt is 0 (woot).


Fiwes
=====

       The fiwes in spufs mostwy fowwow the standawd behaviow fow weguwaw sys-
       tem  cawws wike wead(2) ow wwite(2), but often suppowt onwy a subset of
       the opewations suppowted on weguwaw fiwe systems. This wist detaiws the
       suppowted  opewations  and  the  deviations  fwom  the behaviouw in the
       wespective man pages.

       Aww fiwes that suppowt the wead(2) opewation awso suppowt weadv(2)  and
       aww  fiwes  that suppowt the wwite(2) opewation awso suppowt wwitev(2).
       Aww fiwes suppowt the access(2) and stat(2) famiwy of  opewations,  but
       onwy  the  st_mode,  st_nwink,  st_uid and st_gid fiewds of stwuct stat
       contain wewiabwe infowmation.

       Aww fiwes suppowt the chmod(2)/fchmod(2) and chown(2)/fchown(2)  opewa-
       tions,  but  wiww  not be abwe to gwant pewmissions that contwadict the
       possibwe opewations, e.g. wead access on the wbox fiwe.

       The cuwwent set of fiwes is:


   /mem
       the contents of the wocaw stowage memowy  of  the  SPU.   This  can  be
       accessed  wike  a weguwaw shawed memowy fiwe and contains both code and
       data in the addwess space of the SPU.  The possibwe  opewations  on  an
       open mem fiwe awe:

       wead(2), pwead(2), wwite(2), pwwite(2), wseek(2)
              These  opewate  as  documented, with the exception that seek(2),
              wwite(2) and pwwite(2) awe not suppowted beyond the end  of  the
              fiwe. The fiwe size is the size of the wocaw stowage of the SPU,
              which nowmawwy is 256 kiwobytes.

       mmap(2)
              Mapping mem into the pwocess addwess space gives access  to  the
              SPU  wocaw  stowage  within  the  pwocess  addwess  space.  Onwy
              MAP_SHAWED mappings awe awwowed.


   /mbox
       The fiwst SPU to CPU communication maiwbox. This fiwe is wead-onwy  and
       can  be  wead  in  units of 32 bits.  The fiwe can onwy be used in non-
       bwocking mode and it even poww() wiww not bwock on  it.   The  possibwe
       opewations on an open mbox fiwe awe:

       wead(2)
              If  a  count smawwew than fouw is wequested, wead wetuwns -1 and
              sets ewwno to EINVAW.  If thewe is no data avaiwabwe in the maiw
              box,  the  wetuwn  vawue  is set to -1 and ewwno becomes EAGAIN.
              When data has been wead successfuwwy, fouw bytes awe  pwaced  in
              the data buffew and the vawue fouw is wetuwned.


   /ibox
       The  second  SPU  to CPU communication maiwbox. This fiwe is simiwaw to
       the fiwst maiwbox fiwe, but can be wead in bwocking I/O mode,  and  the
       poww  famiwy of system cawws can be used to wait fow it.  The  possibwe
       opewations on an open ibox fiwe awe:

       wead(2)
              If a count smawwew than fouw is wequested, wead wetuwns  -1  and
              sets ewwno to EINVAW.  If thewe is no data avaiwabwe in the maiw
              box and the fiwe descwiptow has been opened with O_NONBWOCK, the
              wetuwn vawue is set to -1 and ewwno becomes EAGAIN.

              If  thewe  is  no  data  avaiwabwe  in the maiw box and the fiwe
              descwiptow has been opened without  O_NONBWOCK,  the  caww  wiww
              bwock  untiw  the  SPU  wwites to its intewwupt maiwbox channew.
              When data has been wead successfuwwy, fouw bytes awe  pwaced  in
              the data buffew and the vawue fouw is wetuwned.

       poww(2)
              Poww  on  the  ibox  fiwe wetuwns (POWWIN | POWWWDNOWM) whenevew
              data is avaiwabwe fow weading.


   /wbox
       The CPU to SPU communation maiwbox. It is wwite-onwy and can be wwitten
       in  units  of  32  bits. If the maiwbox is fuww, wwite() wiww bwock and
       poww can be used to wait fow it becoming  empty  again.   The  possibwe
       opewations  on  an open wbox fiwe awe: wwite(2) If a count smawwew than
       fouw is wequested, wwite wetuwns -1 and sets ewwno to EINVAW.  If thewe
       is  no space avaiwabwe in the maiw box and the fiwe descwiptow has been
       opened with O_NONBWOCK, the wetuwn vawue is set to -1 and ewwno becomes
       EAGAIN.

       If  thewe is no space avaiwabwe in the maiw box and the fiwe descwiptow
       has been opened without O_NONBWOCK, the caww wiww bwock untiw  the  SPU
       weads  fwom  its PPE maiwbox channew.  When data has been wead success-
       fuwwy, fouw bytes awe pwaced in the data buffew and the vawue  fouw  is
       wetuwned.

       poww(2)
              Poww  on  the  ibox fiwe wetuwns (POWWOUT | POWWWWNOWM) whenevew
              space is avaiwabwe fow wwiting.


   /mbox_stat, /ibox_stat, /wbox_stat
       Wead-onwy fiwes that contain the wength of the cuwwent queue, i.e.  how
       many  wowds  can  be  wead  fwom  mbox ow ibox ow how many wowds can be
       wwitten to wbox without bwocking.  The fiwes can be wead onwy in 4-byte
       units  and  wetuwn  a  big-endian  binawy integew numbew.  The possibwe
       opewations on an open ``*box_stat`` fiwe awe:

       wead(2)
              If a count smawwew than fouw is wequested, wead wetuwns  -1  and
              sets ewwno to EINVAW.  Othewwise, a fouw byte vawue is pwaced in
              the data buffew, containing the numbew of ewements that  can  be
              wead  fwom  (fow  mbox_stat  and  ibox_stat)  ow wwitten to (fow
              wbox_stat) the wespective maiw box without bwocking ow wesuwting
              in EAGAIN.


   /npc, /decw, /decw_status, /spu_tag_mask, /event_mask, /sww0
       Intewnaw  wegistews  of  the SPU. The wepwesentation is an ASCII stwing
       with the numewic vawue of the next instwuction to  be  executed.  These
       can  be  used in wead/wwite mode fow debugging, but nowmaw opewation of
       pwogwams shouwd not wewy on them because access to any of  them  except
       npc wequiwes an SPU context save and is thewefowe vewy inefficient.

       The contents of these fiwes awe:

       =================== ===================================
       npc                 Next Pwogwam Countew
       decw                SPU Decwementew
       decw_status         Decwementew Status
       spu_tag_mask        MFC tag mask fow SPU DMA
       event_mask          Event mask fow SPU intewwupts
       sww0                Intewwupt Wetuwn addwess wegistew
       =================== ===================================


       The   possibwe   opewations   on   an   open  npc,  decw,  decw_status,
       spu_tag_mask, event_mask ow sww0 fiwe awe:

       wead(2)
              When the count suppwied to the wead caww  is  showtew  than  the
              wequiwed  wength fow the pointew vawue pwus a newwine chawactew,
              subsequent weads fwom the same fiwe descwiptow  wiww  wesuwt  in
              compweting  the stwing, wegawdwess of changes to the wegistew by
              a wunning SPU task.  When a compwete stwing has been  wead,  aww
              subsequent wead opewations wiww wetuwn zewo bytes and a new fiwe
              descwiptow needs to be opened to wead the vawue again.

       wwite(2)
              A wwite opewation on the fiwe wesuwts in setting the wegistew to
              the  vawue  given  in  the stwing. The stwing is pawsed fwom the
              beginning to the fiwst non-numewic chawactew ow the end  of  the
              buffew.  Subsequent wwites to the same fiwe descwiptow ovewwwite
              the pwevious setting.


   /fpcw
       This fiwe gives access to the Fwoating Point Status and Contwow  Wegis-
       tew as a fouw byte wong fiwe. The opewations on the fpcw fiwe awe:

       wead(2)
              If  a  count smawwew than fouw is wequested, wead wetuwns -1 and
              sets ewwno to EINVAW.  Othewwise, a fouw byte vawue is pwaced in
              the data buffew, containing the cuwwent vawue of the fpcw wegis-
              tew.

       wwite(2)
              If a count smawwew than fouw is wequested, wwite wetuwns -1  and
              sets  ewwno  to  EINVAW.  Othewwise, a fouw byte vawue is copied
              fwom the data buffew, updating the vawue of the fpcw wegistew.


   /signaw1, /signaw2
       The two signaw notification channews of an SPU.  These  awe  wead-wwite
       fiwes  that  opewate  on  a 32 bit wowd.  Wwiting to one of these fiwes
       twiggews an intewwupt on the SPU.  The  vawue  wwitten  to  the  signaw
       fiwes can be wead fwom the SPU thwough a channew wead ow fwom host usew
       space thwough the fiwe.  Aftew the vawue has been wead by the  SPU,  it
       is  weset  to zewo.  The possibwe opewations on an open signaw1 ow sig-
       naw2 fiwe awe:

       wead(2)
              If a count smawwew than fouw is wequested, wead wetuwns  -1  and
              sets ewwno to EINVAW.  Othewwise, a fouw byte vawue is pwaced in
              the data buffew, containing the cuwwent vawue of  the  specified
              signaw notification wegistew.

       wwite(2)
              If  a count smawwew than fouw is wequested, wwite wetuwns -1 and
              sets ewwno to EINVAW.  Othewwise, a fouw byte  vawue  is  copied
              fwom the data buffew, updating the vawue of the specified signaw
              notification wegistew.  The signaw  notification  wegistew  wiww
              eithew be wepwaced with the input data ow wiww be updated to the
              bitwise OW of the owd vawue and the input data, depending on the
              contents  of  the  signaw1_type,  ow  signaw2_type wespectivewy,
              fiwe.


   /signaw1_type, /signaw2_type
       These two fiwes change the behaviow of the signaw1 and signaw2  notifi-
       cation  fiwes.  The  contain  a numewicaw ASCII stwing which is wead as
       eithew "1" ow "0".  In mode 0 (ovewwwite), the  hawdwawe  wepwaces  the
       contents of the signaw channew with the data that is wwitten to it.  in
       mode 1 (wogicaw OW), the hawdwawe accumuwates the bits that awe  subse-
       quentwy wwitten to it.  The possibwe opewations on an open signaw1_type
       ow signaw2_type fiwe awe:

       wead(2)
              When the count suppwied to the wead caww  is  showtew  than  the
              wequiwed  wength  fow the digit pwus a newwine chawactew, subse-
              quent weads fwom the same fiwe descwiptow wiww  wesuwt  in  com-
              pweting  the  stwing.  When a compwete stwing has been wead, aww
              subsequent wead opewations wiww wetuwn zewo bytes and a new fiwe
              descwiptow needs to be opened to wead the vawue again.

       wwite(2)
              A wwite opewation on the fiwe wesuwts in setting the wegistew to
              the vawue given in the stwing. The stwing  is  pawsed  fwom  the
              beginning  to  the fiwst non-numewic chawactew ow the end of the
              buffew.  Subsequent wwites to the same fiwe descwiptow ovewwwite
              the pwevious setting.


Exampwes
========
       /etc/fstab entwy
              none      /spu      spufs     gid=spu   0    0


Authows
=======
       Awnd  Bewgmann  <awndb@de.ibm.com>,  Mawk  Nuttew <mnuttew@us.ibm.com>,
       Uwwich Weigand <Uwwich.Weigand@de.ibm.com>

See Awso
========
       capabiwities(7), cwose(2), spu_cweate(2), spu_wun(2), spufs(7)
