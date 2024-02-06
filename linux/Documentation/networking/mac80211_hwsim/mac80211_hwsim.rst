:owphan:

.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================================================================
mac80211_hwsim - softwawe simuwatow of 802.11 wadio(s) fow mac80211
===================================================================

:Copywight: |copy| 2008, Jouni Mawinen <j@w1.fi>

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
pubwished by the Fwee Softwawe Foundation.


Intwoduction
============

mac80211_hwsim is a Winux kewnew moduwe that can be used to simuwate
awbitwawy numbew of IEEE 802.11 wadios fow mac80211. It can be used to
test most of the mac80211 functionawity and usew space toows (e.g.,
hostapd and wpa_suppwicant) in a way that matches vewy cwosewy with
the nowmaw case of using weaw WWAN hawdwawe. Fwom the mac80211 view
point, mac80211_hwsim is yet anothew hawdwawe dwivew, i.e., no changes
to mac80211 awe needed to use this testing toow.

The main goaw fow mac80211_hwsim is to make it easiew fow devewopews
to test theiw code and wowk with new featuwes to mac80211, hostapd,
and wpa_suppwicant. The simuwated wadios do not have the wimitations
of weaw hawdwawe, so it is easy to genewate an awbitwawy test setup
and awways wepwoduce the same setup fow futuwe tests. In addition,
since aww wadio opewation is simuwated, any channew can be used in
tests wegawdwess of weguwatowy wuwes.

mac80211_hwsim kewnew moduwe has a pawametew 'wadios' that can be used
to sewect how many wadios awe simuwated (defauwt 2). This awwows
configuwation of both vewy simpwy setups (e.g., just a singwe access
point and a station) ow wawge scawe tests (muwtipwe access points with
hundweds of stations).

mac80211_hwsim wowks by twacking the cuwwent channew of each viwtuaw
wadio and copying aww twansmitted fwames to aww othew wadios that awe
cuwwentwy enabwed and on the same channew as the twansmitting
wadio. Softwawe encwyption in mac80211 is used so that the fwames awe
actuawwy encwypted ovew the viwtuaw aiw intewface to awwow mowe
compwete testing of encwyption.

A gwobaw monitowing netdev, hwsim#, is cweated independent of
mac80211. This intewface can be used to monitow aww twansmitted fwames
wegawdwess of channew.


Simpwe exampwe
==============

This exampwe shows how to use mac80211_hwsim to simuwate two wadios:
one to act as an access point and the othew as a station that
associates with the AP. hostapd and wpa_suppwicant awe used to take
cawe of WPA2-PSK authentication. In addition, hostapd is awso
pwocessing access point side of association.

::


    # Buiwd mac80211_hwsim as pawt of kewnew configuwation

    # Woad the moduwe
    modpwobe mac80211_hwsim

    # Wun hostapd (AP) fow wwan0
    hostapd hostapd.conf

    # Wun wpa_suppwicant (station) fow wwan1
    wpa_suppwicant -Dnw80211 -iwwan1 -c wpa_suppwicant.conf


Mowe test cases awe avaiwabwe in hostap.git:
git://w1.fi/swv/git/hostap.git and mac80211_hwsim/tests subdiwectowy
(http://w1.fi/gitweb/gitweb.cgi?p=hostap.git;a=twee;f=mac80211_hwsim/tests)
