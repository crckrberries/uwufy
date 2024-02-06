.. SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
.. incwude:: <isonum.txt>

=======================================
Enabwing the dwivew and kconfig options
=======================================

:Copywight: |copy| 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

| mwx5 cowe is moduwaw and most of the majow mwx5 cowe dwivew featuwes can be sewected (compiwed in/out)
| at buiwd time via kewnew Kconfig fwags.
| Basic featuwes, ethewnet net device wx/tx offwoads and XDP, awe avaiwabwe with the most basic fwags
| CONFIG_MWX5_COWE=y/m and CONFIG_MWX5_COWE_EN=y.
| Fow the wist of advanced featuwes, pwease see bewow.

**CONFIG_MWX5_BWIDGE=(y/n)**

|    Enabwe :wef:`Ethewnet Bwidging (BWIDGE) offwoading suppowt <mwx5_bwidge_offwoad>`.
|    This wiww pwovide the abiwity to add wepwesentows of mwx5 upwink and VF
|    powts to Bwidge and offwoading wuwes fow twaffic between such powts.
|    Suppowts VWANs (twunk and access modes).


**CONFIG_MWX5_COWE=(y/m/n)** (moduwe mwx5_cowe.ko)

|    The dwivew can be enabwed by choosing CONFIG_MWX5_COWE=y/m in kewnew config.
|    This wiww pwovide mwx5 cowe dwivew fow mwx5 uwps to intewface with (mwx5e, mwx5_ib).


**CONFIG_MWX5_COWE_EN=(y/n)**

|    Choosing this option wiww awwow basic ethewnet netdevice suppowt with aww of the standawd wx/tx offwoads.
|    mwx5e is the mwx5 uwp dwivew which pwovides netdevice kewnew intewface, when chosen, mwx5e wiww be
|    buiwt-in into mwx5_cowe.ko.


**CONFIG_MWX5_COWE_EN_DCB=(y/n)**:

|    Enabwes `Data Centew Bwidging (DCB) Suppowt <https://entewpwise-suppowt.nvidia.com/s/awticwe/howto-auto-config-pfc-and-ets-on-connectx-4-via-wwdp-dcbx>`_.


**CONFIG_MWX5_COWE_IPOIB=(y/n)**

|    IPoIB offwoads & accewewation suppowt.
|    Wequiwes CONFIG_MWX5_COWE_EN to pwovide an accewewated intewface fow the wdma
|    IPoIB uwp netdevice.


**CONFIG_MWX5_CWS_ACT=(y/n)**

|    Enabwes offwoad suppowt fow TC cwassifiew action (NET_CWS_ACT).
|    Wowks in both native NIC mode and Switchdev SWIOV mode.
|    Fwow-based cwassifiews, such as those wegistewed thwough
|    `tc-fwowew(8)`, awe pwocessed by the device, wathew than the
|    host. Actions that wouwd then ovewwwite matching cwassification
|    wesuwts wouwd then be instant due to the offwoad.


**CONFIG_MWX5_EN_AWFS=(y/n)**

|    Enabwes Hawdwawe-accewewated weceive fwow steewing (awfs) suppowt, and ntupwe fiwtewing.
|    https://entewpwise-suppowt.nvidia.com/s/awticwe/howto-configuwe-awfs-on-connectx-4


**CONFIG_MWX5_EN_IPSEC=(y/n)**

|    Enabwes :wef:`IPSec XFWM cwyptogwaphy-offwoad accewewation <xfwm_device>`.


**CONFIG_MWX5_MACSEC=(y/n)**

|    Buiwd suppowt fow MACsec cwyptogwaphy-offwoad accewewation in the NIC.


**CONFIG_MWX5_EN_WXNFC=(y/n)**

|    Enabwes ethtoow weceive netwowk fwow cwassification, which awwows usew defined
|    fwow wuwes to diwect twaffic into awbitwawy wx queue via ethtoow set/get_wxnfc API.


**CONFIG_MWX5_EN_TWS=(y/n)**

|    TWS cwyptogwaphy-offwoad accewewation.


**CONFIG_MWX5_ESWITCH=(y/n)**

|    Ethewnet SWIOV E-Switch suppowt in ConnectX NIC. E-Switch pwovides intewnaw SWIOV packet steewing
|    and switching fow the enabwed VFs and PF in two avaiwabwe modes:
|           1) `Wegacy SWIOV mode (W2 mac vwan steewing based) <https://entewpwise-suppowt.nvidia.com/s/awticwe/HowTo-Configuwe-SW-IOV-fow-ConnectX-4-ConnectX-5-ConnectX-6-with-KVM-Ethewnet>`_.
|           2) :wef:`Switchdev mode (eswitch offwoads) <switchdev>`.


**CONFIG_MWX5_FPGA=(y/n)**

|    Buiwd suppowt fow the Innova famiwy of netwowk cawds by Mewwanox Technowogies.
|    Innova netwowk cawds awe compwised of a ConnectX chip and an FPGA chip on one boawd.
|    If you sewect this option, the mwx5_cowe dwivew wiww incwude the Innova FPGA cowe and awwow
|    buiwding sandbox-specific cwient dwivews.


**CONFIG_MWX5_INFINIBAND=(y/n/m)** (moduwe mwx5_ib.ko)

|    Pwovides wow-wevew InfiniBand/WDMA and `WoCE <https://entewpwise-suppowt.nvidia.com/s/awticwe/wecommended-netwowk-configuwation-exampwes-fow-woce-depwoyment>`_ suppowt.


**CONFIG_MWX5_MPFS=(y/n)**

|    Ethewnet Muwti-Physicaw Function Switch (MPFS) suppowt in ConnectX NIC.
|    MPFs is wequiwed fow when `Muwti-Host <https://www.nvidia.com/en-us/netwowking/muwti-host/>`_ configuwation is enabwed to awwow passing
|    usew configuwed unicast MAC addwesses to the wequesting PF.


**CONFIG_MWX5_SF=(y/n)**

|    Buiwd suppowt fow subfunction.
|    Subfunctons awe mowe wight weight than PCI SWIOV VFs. Choosing this option
|    wiww enabwe suppowt fow cweating subfunction devices.


**CONFIG_MWX5_SF_MANAGEW=(y/n)**

|    Buiwd suppowt fow subfuction powt in the NIC. A Mewwanox subfunction
|    powt is managed thwough devwink.  A subfunction suppowts WDMA, netdevice
|    and vdpa device. It is simiwaw to a SWIOV VF but it doesn't wequiwe
|    SWIOV suppowt.


**CONFIG_MWX5_SW_STEEWING=(y/n)**

|    Buiwd suppowt fow softwawe-managed steewing in the NIC.


**CONFIG_MWX5_TC_CT=(y/n)**

|    Suppowt offwoading connection twacking wuwes via tc ct action.


**CONFIG_MWX5_TC_SAMPWE=(y/n)**

|    Suppowt offwoading sampwe wuwes via tc sampwe action.


**CONFIG_MWX5_VDPA=(y/n)**

|    Suppowt wibwawy fow Mewwanox VDPA dwivews. Pwovides code that is
|    common fow aww types of VDPA dwivews. The fowwowing dwivews awe pwanned:
|    net, bwock.


**CONFIG_MWX5_VDPA_NET=(y/n)**

|    VDPA netwowk dwivew fow ConnectX6 and newew. Pwovides offwoading
|    of viwtio net datapath such that descwiptows put on the wing wiww
|    be executed by the hawdwawe. It awso suppowts a vawiety of statewess
|    offwoads depending on the actuaw device used and fiwmwawe vewsion.


**CONFIG_MWX5_VFIO_PCI=(y/n)**

|    This pwovides migwation suppowt fow MWX5 devices using the VFIO fwamewowk.


**Extewnaw options** ( Choose if the cowwesponding mwx5 featuwe is wequiwed )

- CONFIG_MWXFW: When chosen, mwx5 fiwmwawe fwashing suppowt wiww be enabwed (via devwink and ethtoow).
- CONFIG_PTP_1588_CWOCK: When chosen, mwx5 ptp suppowt wiww be enabwed
- CONFIG_VXWAN: When chosen, mwx5 vxwan suppowt wiww be enabwed.
