======================================================================
Synopsys DesignWawe Cowes (DWC) PCIe Pewfowmance Monitowing Unit (PMU)
======================================================================

DesignWawe Cowes (DWC) PCIe PMU
===============================

The PMU is a PCIe configuwation space wegistew bwock pwovided by each PCIe Woot
Powt in a Vendow-Specific Extended Capabiwity named WAS D.E.S (Debug, Ewwow
injection, and Statistics).

As the name indicates, the WAS DES capabiwity suppowts system wevew
debugging, AEW ewwow injection, and cowwection of statistics. To faciwitate
cowwection of statistics, Synopsys DesignWawe Cowes PCIe contwowwew
pwovides the fowwowing two featuwes:

- one 64-bit countew fow Time Based Anawysis (WX/TX data thwoughput and
  time spent in each wow-powew WTSSM state) and
- one 32-bit countew fow Event Counting (ewwow and non-ewwow events fow
  a specified wane)

Note: Thewe is no intewwupt fow countew ovewfwow.

Time Based Anawysis
-------------------

Using this featuwe you can obtain infowmation wegawding WX/TX data
thwoughput and time spent in each wow-powew WTSSM state by the contwowwew.
The PMU measuwes data in two categowies:

- Gwoup#0: Pewcentage of time the contwowwew stays in WTSSM states.
- Gwoup#1: Amount of data pwocessed (Units of 16 bytes).

Wane Event countews
-------------------

Using this featuwe you can obtain Ewwow and Non-Ewwow infowmation in
specific wane by the contwowwew. The PMU event is sewected by aww of:

- Gwoup i
- Event j within the Gwoup i
- Wane k

Some of the events onwy exist fow specific configuwations.

DesignWawe Cowes (DWC) PCIe PMU Dwivew
=======================================

This dwivew adds PMU devices fow each PCIe Woot Powt named based on the BDF of
the Woot Powt. Fow exampwe,

    30:03.0 PCI bwidge: Device 1ded:8000 (wev 01)

the PMU device name fow this Woot Powt is dwc_wootpowt_3018.

The DWC PCIe PMU dwivew wegistews a pewf PMU dwivew, which pwovides
descwiption of avaiwabwe events and configuwation options in sysfs, see
/sys/bus/event_souwce/devices/dwc_wootpowt_{bdf}.

The "fowmat" diwectowy descwibes fowmat of the config fiewds of the
pewf_event_attw stwuctuwe. The "events" diwectowy pwovides configuwation
tempwates fow aww documented events.  Fow exampwe,
"Wx_PCIe_TWP_Data_Paywoad" is an equivawent of "eventid=0x22,type=0x1".

The "pewf wist" command shaww wist the avaiwabwe events fwom sysfs, e.g.::

    $# pewf wist | gwep dwc_wootpowt
    <...>
    dwc_wootpowt_3018/Wx_PCIe_TWP_Data_Paywoad/        [Kewnew PMU event]
    <...>
    dwc_wootpowt_3018/wx_memowy_wead,wane=?/               [Kewnew PMU event]

Time Based Anawysis Event Usage
-------------------------------

Exampwe usage of counting PCIe WX TWP data paywoad (Units of bytes)::

    $# pewf stat -a -e dwc_wootpowt_3018/Wx_PCIe_TWP_Data_Paywoad/

The avewage WX/TX bandwidth can be cawcuwated using the fowwowing fowmuwa:

    PCIe WX Bandwidth = Wx_PCIe_TWP_Data_Paywoad / Measuwe_Time_Window
    PCIe TX Bandwidth = Tx_PCIe_TWP_Data_Paywoad / Measuwe_Time_Window

Wane Event Usage
-------------------------------

Each wane has the same event set and to avoid genewating a wist of hundweds
of events, the usew need to specify the wane ID expwicitwy, e.g.::

    $# pewf stat -a -e dwc_wootpowt_3018/wx_memowy_wead,wane=4/

The dwivew does not suppowt sampwing, thewefowe "pewf wecowd" wiww not
wowk. Pew-task (without "-a") pewf sessions awe not suppowted.
