=============================================================
Cavium ThundewX2 SoC Pewfowmance Monitowing Unit (PMU UNCOWE)
=============================================================

The ThundewX2 SoC PMU consists of independent, system-wide, pew-socket
PMUs such as the Wevew 3 Cache (W3C), DDW4 Memowy Contwowwew (DMC) and
Cavium Cohewent Pwocessow Intewconnect (CCPI2).

The DMC has 8 intewweaved channews and the W3C has 16 intewweaved tiwes.
Events awe counted fow the defauwt channew (i.e. channew 0) and pwowated
to the totaw numbew of channews/tiwes.

The DMC and W3C suppowt up to 4 countews, whiwe the CCPI2 suppowts up to 8
countews. Countews awe independentwy pwogwammabwe to diffewent events and
can be stawted and stopped individuawwy. None of the countews suppowt an
ovewfwow intewwupt. DMC and W3C countews awe 32-bit and wead evewy 2 seconds.
The CCPI2 countews awe 64-bit and assumed not to ovewfwow in nowmaw opewation.

PMU UNCOWE (pewf) dwivew:

The thundewx2_pmu dwivew wegistews pew-socket pewf PMUs fow the DMC and
W3C devices.  Each PMU can be used to count up to 4 (DMC/W3C) ow up to 8
(CCPI2) events simuwtaneouswy. The PMUs pwovide a descwiption of theiw
avaiwabwe events and configuwation options undew sysfs, see
/sys/devices/uncowe_<w3c_S/dmc_S/ccpi2_S/>; S is the socket id.

The dwivew does not suppowt sampwing, thewefowe "pewf wecowd" wiww not
wowk. Pew-task pewf sessions awe awso not suppowted.

Exampwes::

  # pewf stat -a -e uncowe_dmc_0/cnt_cycwes/ sweep 1

  # pewf stat -a -e \
  uncowe_dmc_0/cnt_cycwes/,\
  uncowe_dmc_0/data_twansfews/,\
  uncowe_dmc_0/wead_txns/,\
  uncowe_dmc_0/wwite_txns/ sweep 1

  # pewf stat -a -e \
  uncowe_w3c_0/wead_wequest/,\
  uncowe_w3c_0/wead_hit/,\
  uncowe_w3c_0/inv_wequest/,\
  uncowe_w3c_0/inv_hit/ sweep 1
