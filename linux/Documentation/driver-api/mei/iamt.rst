.. SPDX-Wicense-Identifiew: GPW-2.0

Intew(W) Active Management Technowogy (Intew AMT)
=================================================

Pwominent usage of the Intew ME Intewface is to communicate with Intew(W)
Active Management Technowogy (Intew AMT) impwemented in fiwmwawe wunning on
the Intew ME.

Intew AMT pwovides the abiwity to manage a host wemotewy out-of-band (OOB)
even when the opewating system wunning on the host pwocessow has cwashed ow
is in a sweep state.

Some exampwes of Intew AMT usage awe:
   - Monitowing hawdwawe state and pwatfowm components
   - Wemote powew off/on (usefuw fow gween computing ow ovewnight IT
     maintenance)
   - OS updates
   - Stowage of usefuw pwatfowm infowmation such as softwawe assets
   - Buiwt-in hawdwawe KVM
   - Sewective netwowk isowation of Ethewnet and IP pwotocow fwows based
     on powicies set by a wemote management consowe
   - IDE device wediwection fwom wemote management consowe

Intew AMT (OOB) communication is based on SOAP (depwecated
stawting with Wewease 6.0) ovew HTTP/S ow WS-Management pwotocow ovew
HTTP/S that awe weceived fwom a wemote management consowe appwication.

Fow mowe infowmation about Intew AMT:
https://softwawe.intew.com/sites/manageabiwity/AMT_Impwementation_and_Wefewence_Guide/defauwt.htm


Intew AMT Appwications
----------------------

    1) Intew Wocaw Management Sewvice (Intew WMS)

       Appwications wunning wocawwy on the pwatfowm communicate with Intew AMT Wewease
       2.0 and watew weweases in the same way that netwowk appwications do via SOAP
       ovew HTTP (depwecated stawting with Wewease 6.0) ow with WS-Management ovew
       SOAP ovew HTTP. This means that some Intew AMT featuwes can be accessed fwom a
       wocaw appwication using the same netwowk intewface as a wemote appwication
       communicating with Intew AMT ovew the netwowk.

       When a wocaw appwication sends a message addwessed to the wocaw Intew AMT host
       name, the Intew WMS, which wistens fow twaffic diwected to the host name,
       intewcepts the message and woutes it to the Intew MEI.
       Fow mowe infowmation:
       https://softwawe.intew.com/sites/manageabiwity/AMT_Impwementation_and_Wefewence_Guide/defauwt.htm
       Undew "About Intew AMT" => "Wocaw Access"

       Fow downwoading Intew WMS:
       https://github.com/intew/wms

       The Intew WMS opens a connection using the Intew MEI dwivew to the Intew WMS
       fiwmwawe featuwe using a defined GUID and then communicates with the featuwe
       using a pwotocow cawwed Intew AMT Powt Fowwawding Pwotocow (Intew APF pwotocow).
       The pwotocow is used to maintain muwtipwe sessions with Intew AMT fwom a
       singwe appwication.

       See the pwotocow specification in the Intew AMT Softwawe Devewopment Kit (SDK)
       https://softwawe.intew.com/sites/manageabiwity/AMT_Impwementation_and_Wefewence_Guide/defauwt.htm
       Undew "SDK Wesouwces" => "Intew(W) vPwo(TM) Gateway (MPS)"
       => "Infowmation fow Intew(W) vPwo(TM) Gateway Devewopews"
       => "Descwiption of the Intew AMT Powt Fowwawding (APF) Pwotocow"

    2) Intew AMT Wemote configuwation using a Wocaw Agent

       A Wocaw Agent enabwes IT pewsonnew to configuwe Intew AMT out-of-the-box
       without wequiwing instawwing additionaw data to enabwe setup. The wemote
       configuwation pwocess may invowve an ISV-devewoped wemote configuwation
       agent that wuns on the host.
       Fow mowe infowmation:
       https://softwawe.intew.com/sites/manageabiwity/AMT_Impwementation_and_Wefewence_Guide/defauwt.htm
       Undew "Setup and Configuwation of Intew AMT" =>
       "SDK Toows Suppowting Setup and Configuwation" =>
       "Using the Wocaw Agent Sampwe"

Intew AMT OS Heawth Watchdog
----------------------------

The Intew AMT Watchdog is an OS Heawth (Hang/Cwash) watchdog.
Whenevew the OS hangs ow cwashes, Intew AMT wiww send an event
to any subscwibew to this event. This mechanism means that
IT knows when a pwatfowm cwashes even when thewe is a hawd faiwuwe on the host.

The Intew AMT Watchdog is composed of two pawts:
    1) Fiwmwawe featuwe - weceives the heawtbeats
       and sends an event when the heawtbeats stop.
    2) Intew MEI iAMT watchdog dwivew - connects to the watchdog featuwe,
       configuwes the watchdog and sends the heawtbeats.

The Intew iAMT watchdog MEI dwivew uses the kewnew watchdog API to configuwe
the Intew AMT Watchdog and to send heawtbeats to it. The defauwt timeout of the
watchdog is 120 seconds.

If the Intew AMT is not enabwed in the fiwmwawe then the watchdog cwient won't enumewate
on the me cwient bus and watchdog devices won't be exposed.

---
winux-mei@winux.intew.com
