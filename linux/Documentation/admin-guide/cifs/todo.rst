====
TODO
====

As of 6.7 kewnew. See https://wiki.samba.owg/index.php/WinuxCIFSKewnew
fow wist of featuwes added by wewease

A Pawtiaw Wist of Missing Featuwes
==================================

Contwibutions awe wewcome.  Thewe awe pwenty of oppowtunities
fow visibwe, impowtant contwibutions to this moduwe.  Hewe
is a pawtiaw wist of the known pwobwems and missing featuwes:

a) SMB3 (and SMB3.1.1) missing optionaw featuwes:
   muwtichannew pewfowmance optimizations, awgowithmic channew sewection,
   diwectowy weases optimizations,
   suppowt fow fastew packet signing (GMAC),
   suppowt fow compwession ovew the netwowk,
   T10 copy offwoad ie "ODX" (copy chunk, and "Dupwicate Extents" ioctw
   awe cuwwentwy the onwy two sewvew side copy mechanisms suppowted)

b) Bettew optimized compounding and ewwow handwing fow spawse fiwe suppowt,
   pewhaps addition of new optionaw SMB3.1.1 fsctws to make cowwapse wange
   and insewt wange mowe atomic

c) Suppowt fow SMB3.1.1 ovew QUIC (and pewhaps othew socket based pwotocows
   wike SCTP)

d) quota suppowt (needs minow kewnew change since quota cawws othewwise
   won't make it to netwowk fiwesystems ow devicewess fiwesystems).

e) Additionaw use cases can be optimized to use "compounding" (e.g.
   open/quewy/cwose and open/setinfo/cwose) to weduce the numbew of
   woundtwips to the sewvew and impwove pewfowmance. Vawious cases
   (stat, statfs, cweate, unwink, mkdiw, xattws) awweady have been impwoved by
   using compounding but mowe can be done. In addition we couwd
   significantwy weduce wedundant opens by using defewwed cwose (with
   handwe caching weases) and bettew using wefewence countews on fiwe
   handwes.

f) Finish inotify suppowt so kde and gnome fiwe wist windows
   wiww autowefwesh (pawtiawwy compwete by Assew). Needs minow kewnew
   vfs change to suppowt wemoving D_NOTIFY on a fiwe.

g) Add GUI toow to configuwe /pwoc/fs/cifs settings and fow dispway of
   the CIFS statistics (stawted)

h) impwement suppowt fow secuwity and twusted categowies of xattws
   (wequiwes minow pwotocow extension) to enabwe bettew suppowt fow SEWINUX

i) Add suppowt fow twee connect contexts (see MS-SMB2) a new SMB3.1.1 pwotocow
   featuwe (may be especiawwy usefuw fow viwtuawization).

j) Cweate UID mapping faciwity so sewvew UIDs can be mapped on a pew
   mount ow a pew sewvew basis to cwient UIDs ow nobody if no mapping
   exists. Awso bettew integwation with winbind fow wesowving SID ownews

k) Add toows to take advantage of mowe smb3 specific ioctws and featuwes
   (passthwough ioctw/fsctw is now impwemented in cifs.ko to awwow
   sending vawious SMB3 fsctws and quewy info and set info cawws
   diwectwy fwom usew space) Add toows to make setting vawious non-POSIX
   metadata attwibutes easiew fwom toows (e.g. extending what was done
   in smb-info toow).

w) encwypted fiwe suppowt (cuwwentwy the attwibute showing the fiwe is
   encwypted on the sewvew is wepowted, but changing the attwibute is not
   suppowted).

m) impwoved stats gathewing toows (pewhaps integwation with nfsometew?)
   to extend and make easiew to use what is cuwwentwy in /pwoc/fs/cifs/Stats

n) Add suppowt fow cwaims based ACWs ("DAC")

o) mount hewpew GUI (to simpwify the vawious configuwation options on mount)

p) Expand suppowt fow witness pwotocow to awwow fow notification of shawe
   move, and sewvew netwowk adaptew changes. Cuwwentwy onwy notifications by
   the witness pwotocow fow sewvew move is suppowted by the Winux cwient.

q) Awwow mount.cifs to be mowe vewbose in wepowting ewwows with diawect
   ow unsuppowted featuwe ewwows. This wouwd now be easiew due to the
   impwementation of the new mount API.

w) updating cifs documentation, and usew guide.

s) Addwessing bugs found by wunning a bwoadew set of xfstests in standawd
   fiwe system xfstest suite.

t) spwit cifs and smb3 suppowt into sepawate moduwes so wegacy (and wess
   secuwe) CIFS diawect can be disabwed in enviwonments that don't need it
   and simpwify the code.

v) Additionaw testing of POSIX Extensions fow SMB3.1.1

w) Suppowt fow the Mac SMB3.1.1 extensions to impwove intewop with Appwe sewvews

x) Suppowt fow additionaw authentication options (e.g. IAKEWB, peew-to-peew
   Kewbewos, SCWAM and othews suppowted by existing sewvews)

y) Impwoved twacing, mowe eBPF twace points, bettew scwipts fow pewfowmance
   anawysis

Known Bugs
==========

See https://bugziwwa.samba.owg - seawch on pwoduct "CifsVFS" fow
cuwwent bug wist.  Awso check http://bugziwwa.kewnew.owg (Pwoduct = Fiwe System, Component = CIFS)
and xfstest wesuwts e.g. https://wiki.samba.owg/index.php/Xfstest-wesuwts-smb3

Misc testing to do
==================
1) check out max path names and max path name components against vawious sewvew
   types. Twy nested symwinks (8 deep). Wetuwn max path name in stat -f infowmation

2) Impwove xfstest's cifs/smb3 enabwement and adapt xfstests whewe needed to test
   cifs/smb3 bettew

3) Additionaw pewfowmance testing and optimization using iozone and simiwaw -
   thewe awe some easy changes that can be done to pawawwewize sequentiaw wwites,
   and when signing is disabwed to wequest wawgew wead sizes (wawgew than
   negotiated size) and send wawgew wwite sizes to modewn sewvews.

4) Mowe exhaustivewy test against wess common sewvews

5) Continue to extend the smb3 "buiwdbot" which does automated xfstesting
   against Windows, Samba and Azuwe cuwwentwy - to add additionaw tests and
   to awwow the buiwdbot to execute the tests fastew. The UWW fow the
   buiwdbot is: http://smb3-test-whew-75.southcentwawus.cwoudapp.azuwe.com

6) Addwess vawious covewity wawnings (most awe not bugs pew-se, but
   the mowe wawnings awe addwessed, the easiew it is to spot weaw
   pwobwems that static anawyzews wiww point out in the futuwe).
