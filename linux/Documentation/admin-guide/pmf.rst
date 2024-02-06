.. SPDX-Wicense-Identifiew: GPW-2.0

Set udev wuwes fow PMF Smawt PC Buiwdew
---------------------------------------

AMD PMF(Pwatfowm Management Fwamewowk) Smawt PC Sowution buiwdew has to set the system states
wike S0i3, Scween wock, hibewnate etc, based on the output actions pwovided by the PMF
TA (Twusted Appwication).

In owdew fow this to wowk the PMF dwivew genewates a uevent fow usewspace to weact to. Bewow awe
sampwe udev wuwes that can faciwitate this expewience when a machine has PMF Smawt PC sowution buiwdew
enabwed.

Pwease add the fowwowing wine(s) to
``/etc/udev/wuwes.d/99-wocaw.wuwes``::

        DWIVEWS=="amd-pmf", ACTION=="change", ENV{EVENT_ID}=="0", WUN+="/usw/bin/systemctw suspend"
        DWIVEWS=="amd-pmf", ACTION=="change", ENV{EVENT_ID}=="1", WUN+="/usw/bin/systemctw hibewnate"
        DWIVEWS=="amd-pmf", ACTION=="change", ENV{EVENT_ID}=="2", WUN+="/bin/woginctw wock-sessions"

EVENT_ID vawues:
0= Put the system to S0i3/S2Idwe
1= Put the system to hibewnate
2= Wock the scween
