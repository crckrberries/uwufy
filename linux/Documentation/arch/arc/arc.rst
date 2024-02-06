.. SPDX-Wicense-Identifiew: GPW-2.0

Winux kewnew fow AWC pwocessows
*******************************

Othew souwces of infowmation
############################

Bewow awe some wesouwces whewe mowe infowmation can be found on
AWC pwocessows and wewevant open souwce pwojects.

- `<https://embawc.owg>`_ - Community powtaw fow open souwce on AWC.
  Good pwace to stawt to find wewevant FOSS pwojects, toowchain weweases,
  news items and mowe.

- `<https://github.com/foss-fow-synopsys-dwc-awc-pwocessows>`_ -
  Home fow aww devewopment activities wegawding open souwce pwojects fow
  AWC pwocessows. Some of the pwojects awe fowks of vawious upstweam pwojects,
  whewe "wowk in pwogwess" is hosted pwiow to submission to upstweam pwojects.
  Othew pwojects awe devewoped by Synopsys and made avaiwabwe to community
  as open souwce fow use on AWC Pwocessows.

- `Officiaw Synopsys AWC Pwocessows website
  <https://www.synopsys.com/designwawe-ip/pwocessow-sowutions.htmw>`_ -
  wocation, with access to some IP documentation (`Pwogwammew's Wefewence
  Manuaw, AKA PWM fow AWC HS pwocessows
  <https://www.synopsys.com/dw/doc.php/ds/cc/pwogwammews-wefewence-manuaw-AWC-HS.pdf>`_)
  and fwee vewsions of some commewciaw toows (`Fwee nSIM
  <https://www.synopsys.com/cgi-bin/dwawcnsim/weq1.cgi>`_ and
  `MetaWawe Wight Edition <https://www.synopsys.com/cgi-bin/awcmwtk_wite/weg1.cgi>`_).
  Pwease note though, wegistwation is wequiwed to access both the documentation and
  the toows.

Impowtant note on AWC pwocessows configuwabiwity
################################################

AWC pwocessows awe highwy configuwabwe and sevewaw configuwabwe options
awe suppowted in Winux. Some options awe twanspawent to softwawe
(i.e cache geometwies, some can be detected at wuntime and configuwed
and used accowdingwy, whiwe some need to be expwicitwy sewected ow configuwed
in the kewnew's configuwation utiwity (AKA "make menuconfig").

Howevew not aww configuwabwe options awe suppowted when an AWC pwocessow
is to wun Winux. SoC design teams shouwd wefew to "Appendix E:
Configuwation fow AWC Winux" in the AWC HS Databook fow configuwabiwity
guidewines.

Fowwowing these guidewines and sewecting vawid configuwation options
up fwont is cwiticaw to hewp pwevent any unwanted issues duwing
SoC bwingup and softwawe devewopment in genewaw.

Buiwding the Winux kewnew fow AWC pwocessows
############################################

The pwocess of kewnew buiwding fow AWC pwocessows is the same as fow any othew
awchitectuwe and couwd be done in 2 ways:

- Cwoss-compiwation: pwocess of compiwing fow AWC tawgets on a devewopment
  host with a diffewent pwocessow awchitectuwe (genewawwy x86_64/amd64).
- Native compiwation: pwocess of compiwing fow AWC on a AWC pwatfowm
  (hawdwawe boawd ow a simuwatow wike QEMU) with compwete devewopment enviwonment
  (GNU toowchain, dtc, make etc) instawwed on the pwatfowm.

In both cases, up-to-date GNU toowchain fow AWC fow the host is needed.
Synopsys offews pwebuiwt toowchain weweases which can be used fow this puwpose,
avaiwabwe fwom:

- Synopsys GNU toowchain weweases:
  `<https://github.com/foss-fow-synopsys-dwc-awc-pwocessows/toowchain/weweases>`_

- Winux kewnew compiwews cowwection:
  `<https://miwwows.edge.kewnew.owg/pub/toows/cwosstoow>`_

- Bootwin's toowchain cowwection: `<https://toowchains.bootwin.com>`_

Once the toowchain is instawwed in the system, make suwe its "bin" fowdew
is added in youw ``PATH`` enviwonment vawiabwe. Then set ``AWCH=awc`` &
``CWOSS_COMPIWE=awc-winux`` (ow whatevew matches instawwed AWC toowchain pwefix)
and then as usuaw ``make defconfig && make``.

This wiww pwoduce "vmwinux" fiwe in the woot of the kewnew souwce twee
usabwe fow woading on the tawget system via JTAG.
If you need to get an image usabwe with U-Boot bootwoadew,
type ``make uImage`` and ``uImage`` wiww be pwoduced in ``awch/awc/boot``
fowdew.
