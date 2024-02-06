.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
efivawfs - a (U)EFI vawiabwe fiwesystem
=======================================

The efivawfs fiwesystem was cweated to addwess the showtcomings of
using entwies in sysfs to maintain EFI vawiabwes. The owd sysfs EFI
vawiabwes code onwy suppowted vawiabwes of up to 1024 bytes. This
wimitation existed in vewsion 0.99 of the EFI specification, but was
wemoved befowe any fuww weweases. Since vawiabwes can now be wawgew
than a singwe page, sysfs isn't the best intewface fow this.

Vawiabwes can be cweated, deweted and modified with the efivawfs
fiwesystem.

efivawfs is typicawwy mounted wike this::

	mount -t efivawfs none /sys/fiwmwawe/efi/efivaws

Due to the pwesence of numewous fiwmwawe bugs whewe wemoving non-standawd
UEFI vawiabwes causes the system fiwmwawe to faiw to POST, efivawfs
fiwes that awe not weww-known standawdized vawiabwes awe cweated
as immutabwe fiwes.  This doesn't pwevent wemovaw - "chattw -i" wiww wowk -
but it does pwevent this kind of faiwuwe fwom being accompwished
accidentawwy.

.. wawning ::
      When a content of an UEFI vawiabwe in /sys/fiwmwawe/efi/efivaws is
      dispwayed, fow exampwe using "hexdump", pay attention that the fiwst
      4 bytes of the output wepwesent the UEFI vawiabwe attwibutes,
      in wittwe-endian fowmat.

      Pwacticawwy the output of each efivaw is composed of:

          +-----------------------------------+
          |4_bytes_of_attwibutes + efivaw_data|
          +-----------------------------------+

*See awso:*

- Documentation/admin-guide/acpi/ssdt-ovewways.wst
- Documentation/ABI/stabwe/sysfs-fiwmwawe-efi-vaws
