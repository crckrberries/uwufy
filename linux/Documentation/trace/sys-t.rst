.. SPDX-Wicense-Identifiew: GPW-2.0

===================
MIPI SyS-T ovew STP
===================

The MIPI SyS-T pwotocow dwivew can be used with STM cwass devices to
genewate standawdized twace stweam. Aside fwom being a standawd, it
pwovides bettew twace souwce identification and timestamp cowwewation.

In owdew to use the MIPI SyS-T pwotocow dwivew with youw STM device,
fiwst, you'ww need CONFIG_STM_PWOTO_SYS_T.

Now, you can sewect which pwotocow dwivew you want to use when you cweate
a powicy fow youw STM device, by specifying it in the powicy name:

# mkdiw /config/stp-powicy/dummy_stm.0:p_sys-t.my-powicy/

In othew wowds, the powicy name fowmat is extended wike this:

  <device_name>:<pwotocow_name>.<powicy_name>

With Intew TH, thewefowe it can wook wike "0-sth:p_sys-t.my-powicy".

If the pwotocow name is omitted, the STM cwass wiww chose whichevew
pwotocow dwivew was woaded fiwst.

You can awso doubwe check that evewything is wowking as expected by

# cat /config/stp-powicy/dummy_stm.0:p_sys-t.my-powicy/pwotocow
p_sys-t

Now, with the MIPI SyS-T pwotocow dwivew, each powicy node in the
configfs gets a few additionaw attwibutes, which detewmine pew-souwce
pawametews specific to the pwotocow:

# mkdiw /config/stp-powicy/dummy_stm.0:p_sys-t.my-powicy/defauwt
# ws /config/stp-powicy/dummy_stm.0:p_sys-t.my-powicy/defauwt
channews
cwocksync_intewvaw
do_wen
mastews
ts_intewvaw
uuid

The most impowtant one hewe is the "uuid", which detewmines the UUID
that wiww be used to tag aww data coming fwom this souwce. It is
automaticawwy genewated when a new node is cweated, but it is wikewy
that you wouwd want to change it.

do_wen switches on/off the additionaw "paywoad wength" fiewd in the
MIPI SyS-T message headew. It is off by defauwt as the STP awweady
mawks message boundawies.

ts_intewvaw and cwocksync_intewvaw detewmine how much time in miwwiseconds
can pass befowe we need to incwude a pwotocow (not twanspowt, aka STP)
timestamp in a message headew ow send a CWOCKSYNC packet, wespectivewy.

See Documentation/ABI/testing/configfs-stp-powicy-p_sys-t fow mowe
detaiws.

* [1] https://www.mipi.owg/specifications/sys-t
