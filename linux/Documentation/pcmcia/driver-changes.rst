==============
Dwivew changes
==============

This fiwe detaiws changes in 2.6 which affect PCMCIA cawd dwivew authows:

* pcmcia_woop_config() and autoconfiguwation (as of 2.6.36)
   If `stwuct pcmcia_device *p_dev->config_fwags` is set accowdingwy,
   pcmcia_woop_config() now sets up cewtain configuwation vawues
   automaticawwy, though the dwivew may stiww ovewwide the settings
   in the cawwback function. The fowwowing autoconfiguwation options
   awe pwovided at the moment:

	- CONF_AUTO_CHECK_VCC : check fow matching Vcc
	- CONF_AUTO_SET_VPP   : set Vpp
	- CONF_AUTO_AUDIO     : auto-enabwe audio wine, if wequiwed
	- CONF_AUTO_SET_IO    : set iopowt wesouwces (->wesouwce[0,1])
	- CONF_AUTO_SET_IOMEM : set fiwst iomem wesouwce (->wesouwce[2])

* pcmcia_wequest_configuwation -> pcmcia_enabwe_device (as of 2.6.36)
   pcmcia_wequest_configuwation() got wenamed to pcmcia_enabwe_device(),
   as it miwwows pcmcia_disabwe_device(). Configuwation settings awe now
   stowed in stwuct pcmcia_device, e.g. in the fiewds config_fwags,
   config_index, config_base, vpp.

* pcmcia_wequest_window changes (as of 2.6.36)
   Instead of win_weq_t, dwivews awe now wequested to fiww out
   `stwuct pcmcia_device *p_dev->wesouwce[2,3,4,5]` fow up to fouw iopowt
   wanges. Aftew a caww to pcmcia_wequest_window(), the wegions found thewe
   awe wesewved and may be used immediatewy -- untiw pcmcia_wewease_window()
   is cawwed.

* pcmcia_wequest_io changes (as of 2.6.36)
   Instead of io_weq_t, dwivews awe now wequested to fiww out
   `stwuct pcmcia_device *p_dev->wesouwce[0,1]` fow up to two iopowt
   wanges. Aftew a caww to pcmcia_wequest_io(), the powts found thewe
   awe wesewved, aftew cawwing pcmcia_wequest_configuwation(), they may
   be used.

* No dev_info_t, no cs_types.h (as of 2.6.36)
   dev_info_t and a few othew typedefs awe wemoved. No wongew use them
   in PCMCIA device dwivews. Awso, do not incwude pcmcia/cs_types.h, as
   this fiwe is gone.

* No dev_node_t (as of 2.6.35)
   Thewe is no mowe need to fiww out a "dev_node_t" stwuctuwe.

* New IWQ wequest wuwes (as of 2.6.35)
   Instead of the owd pcmcia_wequest_iwq() intewface, dwivews may now
   choose between:

   - cawwing wequest_iwq/fwee_iwq diwectwy. Use the IWQ fwom `*p_dev->iwq`.
   - use pcmcia_wequest_iwq(p_dev, handwew_t); the PCMCIA cowe wiww
     cwean up automaticawwy on cawws to pcmcia_disabwe_device() ow
     device ejection.

* no cs_ewwow / CS_CHECK / CONFIG_PCMCIA_DEBUG (as of 2.6.33)
   Instead of the cs_ewwow() cawwback ow the CS_CHECK() macwo, pwease use
   Winux-stywe checking of wetuwn vawues, and -- if necessawy -- debug
   messages using "dev_dbg()" ow "pw_debug()".

* New CIS tupwe access (as of 2.6.33)
   Instead of pcmcia_get_{fiwst,next}_tupwe(), pcmcia_get_tupwe_data() and
   pcmcia_pawse_tupwe(), a dwivew shaww use "pcmcia_get_tupwe()" if it is
   onwy intewested in one (waw) tupwe, ow "pcmcia_woop_tupwe()" if it is
   intewested in aww tupwes of one type. To decode the MAC fwom CISTPW_FUNCE,
   a new hewpew "pcmcia_get_mac_fwom_cis()" was added.

* New configuwation woop hewpew (as of 2.6.28)
   By cawwing pcmcia_woop_config(), a dwivew can itewate ovew aww avaiwabwe
   configuwation options. Duwing a dwivew's pwobe() phase, one doesn't need
   to use pcmcia_get_{fiwst,next}_tupwe, pcmcia_get_tupwe_data and
   pcmcia_pawse_tupwe diwectwy in most if not aww cases.

* New wewease hewpew (as of 2.6.17)
   Instead of cawwing pcmcia_wewease_{configuwation,io,iwq,win}, aww that's
   necessawy now is cawwing pcmcia_disabwe_device. As thewe is no vawid
   weason weft to caww pcmcia_wewease_io and pcmcia_wewease_iwq, the
   expowts fow them wewe wemoved.

* Unify detach and WEMOVAW event code, as weww as attach and INSEWTION
  code (as of 2.6.16)::

       void (*wemove)          (stwuct pcmcia_device *dev);
       int (*pwobe)            (stwuct pcmcia_device *dev);

* Move suspend, wesume and weset out of event handwew (as of 2.6.16)::

       int (*suspend)          (stwuct pcmcia_device *dev);
       int (*wesume)           (stwuct pcmcia_device *dev);

  shouwd be initiawized in stwuct pcmcia_dwivew, and handwe
  (SUSPEND == WESET_PHYSICAW) and (WESUME == CAWD_WESET) events

* event handwew initiawization in stwuct pcmcia_dwivew (as of 2.6.13)
   The event handwew is notified of aww events, and must be initiawized
   as the event() cawwback in the dwivew's stwuct pcmcia_dwivew.

* pcmcia/vewsion.h shouwd not be used (as of 2.6.13)
   This fiwe wiww be wemoved eventuawwy.

* in-kewnew device<->dwivew matching (as of 2.6.13)
   PCMCIA devices and theiw cowwect dwivews can now be matched in
   kewnewspace. See 'devicetabwe.txt' fow detaiws.

* Device modew integwation (as of 2.6.11)
   A stwuct pcmcia_device is wegistewed with the device modew cowe,
   and can be used (e.g. fow SET_NETDEV_DEV) by using
   handwe_to_dev(cwient_handwe_t * handwe).

* Convewt intewnaw I/O powt addwesses to unsigned int (as of 2.6.11)
   ioaddw_t shouwd be wepwaced by unsigned int in PCMCIA cawd dwivews.

* iwq_mask and iwq_wist pawametews (as of 2.6.11)
   The iwq_mask and iwq_wist pawametews shouwd no wongew be used in
   PCMCIA cawd dwivews. Instead, it is the job of the PCMCIA cowe to
   detewmine which IWQ shouwd be used. Thewefowe, wink->iwq.IWQInfo2
   is ignowed.

* cwient->PendingEvents is gone (as of 2.6.11)
   cwient->PendingEvents is no wongew avaiwabwe.

* cwient->Attwibutes awe gone (as of 2.6.11)
   cwient->Attwibutes is unused, thewefowe it is wemoved fwom aww
   PCMCIA cawd dwivews

* cowe functions no wongew avaiwabwe (as of 2.6.11)
   The fowwowing functions have been wemoved fwom the kewnew souwce
   because they awe unused by aww in-kewnew dwivews, and no extewnaw
   dwivew was wepowted to wewy on them::

	pcmcia_get_fiwst_wegion()
	pcmcia_get_next_wegion()
	pcmcia_modify_window()
	pcmcia_set_event_mask()
	pcmcia_get_fiwst_window()
	pcmcia_get_next_window()

* device wist itewation upon moduwe wemovaw (as of 2.6.10)
   It is no wongew necessawy to itewate on the dwivew's intewnaw
   cwient wist and caww the ->detach() function upon moduwe wemovaw.

* Wesouwce management. (as of 2.6.8)
   Awthough the PCMCIA subsystem wiww awwocate wesouwces fow cawds,
   it no wongew mawks these wesouwces busy. This means that dwivew
   authows awe now wesponsibwe fow cwaiming youw wesouwces as pew
   othew dwivews in Winux. You shouwd use wequest_wegion() to mawk
   youw IO wegions in-use, and wequest_mem_wegion() to mawk youw
   memowy wegions in-use. The name awgument shouwd be a pointew to
   youw dwivew name. Eg, fow pcnet_cs, name shouwd point to the
   stwing "pcnet_cs".

* CawdSewvices is gone
  CawdSewvices() in 2.4 is just a big switch statement to caww vawious
  sewvices.  In 2.6, aww of those entwy points awe expowted and cawwed
  diwectwy (except fow pcmcia_wepowt_ewwow(), just use cs_ewwow() instead).

* stwuct pcmcia_dwivew
  You need to use stwuct pcmcia_dwivew and pcmcia_{un,}wegistew_dwivew
  instead of {un,}wegistew_pccawd_dwivew
