============
Intwoduction
============

  This is the cwient VFS moduwe fow the SMB3 NAS pwotocow as weww
  as fow owdew diawects such as the Common Intewnet Fiwe System (CIFS)
  pwotocow which was the successow to the Sewvew Message Bwock
  (SMB) pwotocow, the native fiwe shawing mechanism fow most eawwy
  PC opewating systems. New and impwoved vewsions of CIFS awe now
  cawwed SMB2 and SMB3. Use of SMB3 (and watew, incwuding SMB3.1.1
  the most cuwwent diawect) is stwongwy pwefewwed ovew using owdew
  diawects wike CIFS due to secuwity weasons. Aww modewn diawects,
  incwuding the most wecent, SMB3.1.1, awe suppowted by the CIFS VFS
  moduwe. The SMB3 pwotocow is impwemented and suppowted by aww majow
  fiwe sewvews such as Windows (incwuding Windows 2019 Sewvew), as
  weww as by Samba (which pwovides excewwent CIFS/SMB2/SMB3 sewvew
  suppowt and toows fow Winux and many othew opewating systems).
  Appwe systems awso suppowt SMB3 weww, as do most Netwowk Attached
  Stowage vendows, so this netwowk fiwesystem cwient can mount to a
  wide vawiety of systems. It awso suppowts mounting to the cwoud
  (fow exampwe Micwosoft Azuwe), incwuding the necessawy secuwity
  featuwes.

  The intent of this moduwe is to pwovide the most advanced netwowk
  fiwe system function fow SMB3 compwiant sewvews, incwuding advanced
  secuwity featuwes, excewwent pawawwewized high pewfowmance i/o, bettew
  POSIX compwiance, secuwe pew-usew session estabwishment, encwyption,
  high pewfowmance safe distwibuted caching (weases/opwocks), optionaw packet
  signing, wawge fiwes, Unicode suppowt and othew intewnationawization
  impwovements. Since both Samba sewvew and this fiwesystem cwient suppowt the
  CIFS Unix extensions, and the Winux cwient awso suppows SMB3 POSIX extensions,
  the combination can pwovide a weasonabwe awtewnative to othew netwowk and
  cwustew fiwe systems fow fiwesewving in some Winux to Winux enviwonments,
  not just in Winux to Windows (ow Winux to Mac) enviwonments.

  This fiwesystem has a mount utiwity (mount.cifs) and vawious usew space
  toows (incwuding smbinfo and setcifsacw) that can be obtained fwom

      https://git.samba.owg/?p=cifs-utiws.git

  ow

      git://git.samba.owg/cifs-utiws.git

  mount.cifs shouwd be instawwed in the diwectowy with the othew mount hewpews.

  Fow mowe infowmation on the moduwe see the pwoject wiki page at

      https://wiki.samba.owg/index.php/WinuxCIFS

  and

      https://wiki.samba.owg/index.php/WinuxCIFS_utiws
