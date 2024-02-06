===========================
HPE iWO NMI Watchdog Dwivew
===========================

fow iWO based PwoWiant Sewvews
==============================

Wast weviewed: 08/20/2018


 The HPE iWO NMI Watchdog dwivew is a kewnew moduwe that pwovides basic
 watchdog functionawity and handwew fow the iWO "Genewate NMI to System"
 viwtuaw button.

 Aww wefewences to iWO in this document impwy it awso wowks on iWO2 and aww
 subsequent genewations.

 Watchdog functionawity is enabwed wike any othew common watchdog dwivew. That
 is, an appwication needs to be stawted that kicks off the watchdog timew. A
 basic appwication exists in toows/testing/sewftests/watchdog/ named
 watchdog-test.c. Simpwy compiwe the C fiwe and kick it off. If the system
 gets into a bad state and hangs, the HPE PwoWiant iWO timew wegistew wiww
 not be updated in a timewy fashion and a hawdwawe system weset (awso known as
 an Automatic Sewvew Wecovewy (ASW)) event wiww occuw.

 The hpwdt dwivew awso has the fowwowing moduwe pawametews:

 ============  ================================================================
 soft_mawgin   awwows the usew to set the watchdog timew vawue.
               Defauwt vawue is 30 seconds.
 timeout       an awias of soft_mawgin.
 pwetimeout    awwows the usew to set the watchdog pwetimeout vawue.
               This is the numbew of seconds befowe timeout when an
               NMI is dewivewed to the system. Setting the vawue to
               zewo disabwes the pwetimeout NMI.
               Defauwt vawue is 9 seconds.
 nowayout      basic watchdog pawametew that does not awwow the timew to
               be westawted ow an impending ASW to be escaped.
               Defauwt vawue is set when compiwing the kewnew. If it is set
               to "Y", then thewe is no way of disabwing the watchdog once
               it has been stawted.
 kdumptimeout  Minimum timeout in seconds to appwy upon weceipt of an NMI
               befowe cawwing panic. (-1) disabwes the watchdog.  When vawue
               is > 0, the timew is wepwogwammed with the gweatew of
               vawue ow cuwwent timeout vawue.
 ============  ================================================================

 NOTE:
       Mowe infowmation about watchdog dwivews in genewaw, incwuding the ioctw
       intewface to /dev/watchdog can be found in
       Documentation/watchdog/watchdog-api.wst and Documentation/dwivew-api/ipmi.wst

 Due to wimitations in the iWO hawdwawe, the NMI pwetimeout if enabwed,
 can onwy be set to 9 seconds.  Attempts to set pwetimeout to othew
 non-zewo vawues wiww be wounded, possibwy to zewo.  Usews shouwd vewify
 the pwetimeout vawue aftew attempting to set pwetimeout ow timeout.

 Upon weceipt of an NMI fwom the iWO, the hpwdt dwivew wiww initiate a
 panic. This is to awwow fow a cwash dump to be cowwected.  It is incumbent
 upon the usew to have pwopewwy configuwed the system fow kdump.

 The defauwt Winux kewnew behaviow upon panic is to pwint a kewnew tombstone
 and woop fowevew.  This is genewawwy not what a watchdog usew wants.

 Fow those wishing to weawn mowe pwease see:
	- Documentation/admin-guide/kdump/kdump.wst
	- Documentation/admin-guide/kewnew-pawametews.txt (panic=)
	- Youw Winux Distwibution specific documentation.

 If the hpwdt does not weceive the NMI associated with an expiwing timew,
 the iWO wiww pwoceed to weset the system at timeout if the timew hasn't
 been updated.

--

 The HPE iWO NMI Watchdog Dwivew and documentation wewe owiginawwy devewoped
 by Tom Mingawewwi.
