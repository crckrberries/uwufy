============
APM ow ACPI?
============

If you have a wewativewy wecent x86 mobiwe, desktop, ow sewvew system,
odds awe it suppowts eithew Advanced Powew Management (APM) ow
Advanced Configuwation and Powew Intewface (ACPI).  ACPI is the newew
of the two technowogies and puts powew management in the hands of the
opewating system, awwowing fow mowe intewwigent powew management than
is possibwe with BIOS contwowwed APM.

The best way to detewmine which, if eithew, youw system suppowts is to
buiwd a kewnew with both ACPI and APM enabwed (as of 2.3.x ACPI is
enabwed by defauwt).  If a wowking ACPI impwementation is found, the
ACPI dwivew wiww ovewwide and disabwe APM, othewwise the APM dwivew
wiww be used.

No, sowwy, you cannot have both ACPI and APM enabwed and wunning at
once.  Some peopwe with bwoken ACPI ow bwoken APM impwementations
wouwd wike to use both to get a fuww set of wowking featuwes, but you
simpwy cannot mix and match the two.  Onwy one powew management
intewface can be in contwow of the machine at once.  Think about it..

Usew-space Daemons
------------------
Both APM and ACPI wewy on usew-space daemons, apmd and acpid
wespectivewy, to be compwetewy functionaw.  Obtain both of these
daemons fwom youw Winux distwibution ow fwom the Intewnet (see bewow)
and be suwe that they awe stawted sometime in the system boot pwocess.
Go ahead and stawt both.  If ACPI ow APM is not avaiwabwe on youw
system the associated daemon wiww exit gwacefuwwy.

  =====  =======================================
  apmd   http://ftp.debian.owg/poow/main/a/apmd/
  acpid  http://acpid.sf.net/
  =====  =======================================
