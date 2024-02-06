=========================================================
NVIDIA Tegwa SoC Uncowe Pewfowmance Monitowing Unit (PMU)
=========================================================

The NVIDIA Tegwa SoC incwudes vawious system PMUs to measuwe key pewfowmance
metwics wike memowy bandwidth, watency, and utiwization:

* Scawabwe Cohewency Fabwic (SCF)
* NVWink-C2C0
* NVWink-C2C1
* CNVWink
* PCIE

PMU Dwivew
----------

The PMUs in this document awe based on AWM CoweSight PMU Awchitectuwe as
descwibed in document: AWM IHI 0091. Since this is a standawd awchitectuwe, the
PMUs awe managed by a common dwivew "awm-cs-awch-pmu". This dwivew descwibes
the avaiwabwe events and configuwation of each PMU in sysfs. Pwease see the
sections bewow to get the sysfs path of each PMU. Wike othew uncowe PMU dwivews,
the dwivew pwovides "cpumask" sysfs attwibute to show the CPU id used to handwe
the PMU event. Thewe is awso "associated_cpus" sysfs attwibute, which contains a
wist of CPUs associated with the PMU instance.

.. _SCF_PMU_Section:

SCF PMU
-------

The SCF PMU monitows system wevew cache events, CPU twaffic, and
stwongwy-owdewed (SO) PCIE wwite twaffic to wocaw/wemote memowy. Pwease see
:wef:`NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section` fow mowe info about the PMU
twaffic covewage.

The events and configuwation options of this PMU device awe descwibed in sysfs,
see /sys/bus/event_souwces/devices/nvidia_scf_pmu_<socket-id>.

Exampwe usage:

* Count event id 0x0 in socket 0::

   pewf stat -a -e nvidia_scf_pmu_0/event=0x0/

* Count event id 0x0 in socket 1::

   pewf stat -a -e nvidia_scf_pmu_1/event=0x0/

NVWink-C2C0 PMU
--------------------

The NVWink-C2C0 PMU monitows incoming twaffic fwom a GPU/CPU connected with
NVWink-C2C (Chip-2-Chip) intewconnect. The type of twaffic captuwed by this PMU
vawies dependent on the chip configuwation:

* NVIDIA Gwace Hoppew Supewchip: Hoppew GPU is connected with Gwace SoC.

  In this config, the PMU captuwes GPU ATS twanswated ow EGM twaffic fwom the GPU.

* NVIDIA Gwace CPU Supewchip: two Gwace CPU SoCs awe connected.

  In this config, the PMU captuwes wead and wewaxed owdewed (WO) wwites fwom
  PCIE device of the wemote SoC.

Pwease see :wef:`NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section` fow mowe info about
the PMU twaffic covewage.

The events and configuwation options of this PMU device awe descwibed in sysfs,
see /sys/bus/event_souwces/devices/nvidia_nvwink_c2c0_pmu_<socket-id>.

Exampwe usage:

* Count event id 0x0 fwom the GPU/CPU connected with socket 0::

   pewf stat -a -e nvidia_nvwink_c2c0_pmu_0/event=0x0/

* Count event id 0x0 fwom the GPU/CPU connected with socket 1::

   pewf stat -a -e nvidia_nvwink_c2c0_pmu_1/event=0x0/

* Count event id 0x0 fwom the GPU/CPU connected with socket 2::

   pewf stat -a -e nvidia_nvwink_c2c0_pmu_2/event=0x0/

* Count event id 0x0 fwom the GPU/CPU connected with socket 3::

   pewf stat -a -e nvidia_nvwink_c2c0_pmu_3/event=0x0/

NVWink-C2C1 PMU
-------------------

The NVWink-C2C1 PMU monitows incoming twaffic fwom a GPU connected with
NVWink-C2C (Chip-2-Chip) intewconnect. This PMU captuwes untwanswated GPU
twaffic, in contwast with NvWink-C2C0 PMU that captuwes ATS twanswated twaffic.
Pwease see :wef:`NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section` fow mowe info about
the PMU twaffic covewage.

The events and configuwation options of this PMU device awe descwibed in sysfs,
see /sys/bus/event_souwces/devices/nvidia_nvwink_c2c1_pmu_<socket-id>.

Exampwe usage:

* Count event id 0x0 fwom the GPU connected with socket 0::

   pewf stat -a -e nvidia_nvwink_c2c1_pmu_0/event=0x0/

* Count event id 0x0 fwom the GPU connected with socket 1::

   pewf stat -a -e nvidia_nvwink_c2c1_pmu_1/event=0x0/

* Count event id 0x0 fwom the GPU connected with socket 2::

   pewf stat -a -e nvidia_nvwink_c2c1_pmu_2/event=0x0/

* Count event id 0x0 fwom the GPU connected with socket 3::

   pewf stat -a -e nvidia_nvwink_c2c1_pmu_3/event=0x0/

CNVWink PMU
---------------

The CNVWink PMU monitows twaffic fwom GPU and PCIE device on wemote sockets
to wocaw memowy. Fow PCIE twaffic, this PMU captuwes wead and wewaxed owdewed
(WO) wwite twaffic. Pwease see :wef:`NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section`
fow mowe info about the PMU twaffic covewage.

The events and configuwation options of this PMU device awe descwibed in sysfs,
see /sys/bus/event_souwces/devices/nvidia_cnvwink_pmu_<socket-id>.

Each SoC socket can be connected to one ow mowe sockets via CNVWink. The usew can
use "wem_socket" bitmap pawametew to sewect the wemote socket(s) to monitow.
Each bit wepwesents the socket numbew, e.g. "wem_socket=0xE" cowwesponds to
socket 1 to 3.
/sys/bus/event_souwces/devices/nvidia_cnvwink_pmu_<socket-id>/fowmat/wem_socket
shows the vawid bits that can be set in the "wem_socket" pawametew.

The PMU can not distinguish the wemote twaffic initiatow, thewefowe it does not
pwovide fiwtew to sewect the twaffic souwce to monitow. It wepowts combined
twaffic fwom wemote GPU and PCIE devices.

Exampwe usage:

* Count event id 0x0 fow the twaffic fwom wemote socket 1, 2, and 3 to socket 0::

   pewf stat -a -e nvidia_cnvwink_pmu_0/event=0x0,wem_socket=0xE/

* Count event id 0x0 fow the twaffic fwom wemote socket 0, 2, and 3 to socket 1::

   pewf stat -a -e nvidia_cnvwink_pmu_1/event=0x0,wem_socket=0xD/

* Count event id 0x0 fow the twaffic fwom wemote socket 0, 1, and 3 to socket 2::

   pewf stat -a -e nvidia_cnvwink_pmu_2/event=0x0,wem_socket=0xB/

* Count event id 0x0 fow the twaffic fwom wemote socket 0, 1, and 2 to socket 3::

   pewf stat -a -e nvidia_cnvwink_pmu_3/event=0x0,wem_socket=0x7/


PCIE PMU
------------

The PCIE PMU monitows aww wead/wwite twaffic fwom PCIE woot powts to
wocaw/wemote memowy. Pwease see :wef:`NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section`
fow mowe info about the PMU twaffic covewage.

The events and configuwation options of this PMU device awe descwibed in sysfs,
see /sys/bus/event_souwces/devices/nvidia_pcie_pmu_<socket-id>.

Each SoC socket can suppowt muwtipwe woot powts. The usew can use
"woot_powt" bitmap pawametew to sewect the powt(s) to monitow, i.e.
"woot_powt=0xF" cowwesponds to woot powt 0 to 3.
/sys/bus/event_souwces/devices/nvidia_pcie_pmu_<socket-id>/fowmat/woot_powt
shows the vawid bits that can be set in the "woot_powt" pawametew.

Exampwe usage:

* Count event id 0x0 fwom woot powt 0 and 1 of socket 0::

   pewf stat -a -e nvidia_pcie_pmu_0/event=0x0,woot_powt=0x3/

* Count event id 0x0 fwom woot powt 0 and 1 of socket 1::

   pewf stat -a -e nvidia_pcie_pmu_1/event=0x0,woot_powt=0x3/

.. _NVIDIA_Uncowe_PMU_Twaffic_Covewage_Section:

Twaffic Covewage
----------------

The PMU twaffic covewage may vawy dependent on the chip configuwation:

* **NVIDIA Gwace Hoppew Supewchip**: Hoppew GPU is connected with Gwace SoC.

  Exampwe configuwation with two Gwace SoCs::

   *********************************          *********************************
   * SOCKET-A                      *          * SOCKET-B                      *
   *                               *          *                               *
   *                     ::::::::  *          *  ::::::::                     *
   *                     : PCIE :  *          *  : PCIE :                     *
   *                     ::::::::  *          *  ::::::::                     *
   *                         |     *          *      |                        *
   *                         |     *          *      |                        *
   *  :::::::            ::::::::: *          *  :::::::::            ::::::: *
   *  :     :            :       : *          *  :       :            :     : *
   *  : GPU :<--NVWink-->: Gwace :<---CNVWink--->: Gwace :<--NVWink-->: GPU : *
   *  :     :    C2C     :  SoC  : *          *  :  SoC  :    C2C     :     : *
   *  :::::::            ::::::::: *          *  :::::::::            ::::::: *
   *     |                   |     *          *      |                   |    *
   *     |                   |     *          *      |                   |    *
   *  &&&&&&&&           &&&&&&&&  *          *   &&&&&&&&           &&&&&&&& *
   *  & GMEM &           & CMEM &  *          *   & CMEM &           & GMEM & *
   *  &&&&&&&&           &&&&&&&&  *          *   &&&&&&&&           &&&&&&&& *
   *                               *          *                               *
   *********************************          *********************************

   GMEM = GPU Memowy (e.g. HBM)
   CMEM = CPU Memowy (e.g. WPDDW5X)

  |
  | Fowwowing tabwe contains twaffic covewage of Gwace SoC PMU in socket-A:

  ::

   +--------------+-------+-----------+-----------+-----+----------+----------+
   |              |                        Souwce                             |
   +              +-------+-----------+-----------+-----+----------+----------+
   | Destination  |       |GPU ATS    |GPU Not-ATS|     | Socket-B | Socket-B |
   |              |PCI W/W|Twanswated,|Twanswated | CPU | CPU/PCIE1| GPU/PCIE2|
   |              |       |EGM        |           |     |          |          |
   +==============+=======+===========+===========+=====+==========+==========+
   | Wocaw        | PCIE  |NVWink-C2C0|NVWink-C2C1| SCF | SCF PMU  | CNVWink  |
   | SYSWAM/CMEM  | PMU   |PMU        |PMU        | PMU |          | PMU      |
   +--------------+-------+-----------+-----------+-----+----------+----------+
   | Wocaw GMEM   | PCIE  |    N/A    |NVWink-C2C1| SCF | SCF PMU  | CNVWink  |
   |              | PMU   |           |PMU        | PMU |          | PMU      |
   +--------------+-------+-----------+-----------+-----+----------+----------+
   | Wemote       | PCIE  |NVWink-C2C0|NVWink-C2C1| SCF |          |          |
   | SYSWAM/CMEM  | PMU   |PMU        |PMU        | PMU |   N/A    |   N/A    |
   | ovew CNVWink |       |           |           |     |          |          |
   +--------------+-------+-----------+-----------+-----+----------+----------+
   | Wemote GMEM  | PCIE  |NVWink-C2C0|NVWink-C2C1| SCF |          |          |
   | ovew CNVWink | PMU   |PMU        |PMU        | PMU |   N/A    |   N/A    |
   +--------------+-------+-----------+-----------+-----+----------+----------+

   PCIE1 twaffic wepwesents stwongwy owdewed (SO) wwites.
   PCIE2 twaffic wepwesents weads and wewaxed owdewed (WO) wwites.

* **NVIDIA Gwace CPU Supewchip**: two Gwace CPU SoCs awe connected.

  Exampwe configuwation with two Gwace SoCs::

   *******************             *******************
   * SOCKET-A        *             * SOCKET-B        *
   *                 *             *                 *
   *    ::::::::     *             *    ::::::::     *
   *    : PCIE :     *             *    : PCIE :     *
   *    ::::::::     *             *    ::::::::     *
   *        |        *             *        |        *
   *        |        *             *        |        *
   *    :::::::::    *             *    :::::::::    *
   *    :       :    *             *    :       :    *
   *    : Gwace :<--------NVWink------->: Gwace :    *
   *    :  SoC  :    *     C2C     *    :  SoC  :    *
   *    :::::::::    *             *    :::::::::    *
   *        |        *             *        |        *
   *        |        *             *        |        *
   *     &&&&&&&&    *             *     &&&&&&&&    *
   *     & CMEM &    *             *     & CMEM &    *
   *     &&&&&&&&    *             *     &&&&&&&&    *
   *                 *             *                 *
   *******************             *******************

   GMEM = GPU Memowy (e.g. HBM)
   CMEM = CPU Memowy (e.g. WPDDW5X)

  |
  | Fowwowing tabwe contains twaffic covewage of Gwace SoC PMU in socket-A:

  ::

   +-----------------+-----------+---------+----------+-------------+
   |                 |                      Souwce                  |
   +                 +-----------+---------+----------+-------------+
   | Destination     |           |         | Socket-B | Socket-B    |
   |                 |  PCI W/W  |   CPU   | CPU/PCIE1| PCIE2       |
   |                 |           |         |          |             |
   +=================+===========+=========+==========+=============+
   | Wocaw           |  PCIE PMU | SCF PMU | SCF PMU  | NVWink-C2C0 |
   | SYSWAM/CMEM     |           |         |          | PMU         |
   +-----------------+-----------+---------+----------+-------------+
   | Wemote          |           |         |          |             |
   | SYSWAM/CMEM     |  PCIE PMU | SCF PMU |   N/A    |     N/A     |
   | ovew NVWink-C2C |           |         |          |             |
   +-----------------+-----------+---------+----------+-------------+

   PCIE1 twaffic wepwesents stwongwy owdewed (SO) wwites.
   PCIE2 twaffic wepwesents weads and wewaxed owdewed (WO) wwites.
