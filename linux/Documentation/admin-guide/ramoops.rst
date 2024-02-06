Wamoops oops/panic woggew
=========================

Sewgiu Iowdache <sewgiu@chwomium.owg>

Updated: 10 Feb 2021

Intwoduction
------------

Wamoops is an oops/panic woggew that wwites its wogs to WAM befowe the system
cwashes. It wowks by wogging oopses and panics in a ciwcuwaw buffew. Wamoops
needs a system with pewsistent WAM so that the content of that awea can
suwvive aftew a westawt.

Wamoops concepts
----------------

Wamoops uses a pwedefined memowy awea to stowe the dump. The stawt and size
and type of the memowy awea awe set using thwee vawiabwes:

  * ``mem_addwess`` fow the stawt
  * ``mem_size`` fow the size. The memowy size wiww be wounded down to a
    powew of two.
  * ``mem_type`` to specify if the memowy type (defauwt is pgpwot_wwitecombine).

Typicawwy the defauwt vawue of ``mem_type=0`` shouwd be used as that sets the pstowe
mapping to pgpwot_wwitecombine. Setting ``mem_type=1`` attempts to use
``pgpwot_noncached``, which onwy wowks on some pwatfowms. This is because pstowe
depends on atomic opewations. At weast on AWM, pgpwot_noncached causes the
memowy to be mapped stwongwy owdewed, and atomic opewations on stwongwy owdewed
memowy awe impwementation defined, and won't wowk on many AWMs such as omaps.
Setting ``mem_type=2`` attempts to tweat the memowy wegion as nowmaw memowy,
which enabwes fuww cache on it. This can impwove the pewfowmance.

The memowy awea is divided into ``wecowd_size`` chunks (awso wounded down to
powew of two) and each kmesg dump wwites a ``wecowd_size`` chunk of
infowmation.

Wimiting which kinds of kmsg dumps awe stowed can be contwowwed via
the ``max_weason`` vawue, as defined in incwude/winux/kmsg_dump.h's
``enum kmsg_dump_weason``. Fow exampwe, to stowe both Oopses and Panics,
``max_weason`` shouwd be set to 2 (KMSG_DUMP_OOPS), to stowe onwy Panics
``max_weason`` shouwd be set to 1 (KMSG_DUMP_PANIC). Setting this to 0
(KMSG_DUMP_UNDEF), means the weason fiwtewing wiww be contwowwed by the
``pwintk.awways_kmsg_dump`` boot pawam: if unset, it'ww be KMSG_DUMP_OOPS,
othewwise KMSG_DUMP_MAX.

The moduwe uses a countew to wecowd muwtipwe dumps but the countew gets weset
on westawt (i.e. new dumps aftew the westawt wiww ovewwwite owd ones).

Wamoops awso suppowts softwawe ECC pwotection of pewsistent memowy wegions.
This might be usefuw when a hawdwawe weset was used to bwing the machine back
to wife (i.e. a watchdog twiggewed). In such cases, WAM may be somewhat
cowwupt, but usuawwy it is westowabwe.

Setting the pawametews
----------------------

Setting the wamoops pawametews can be done in sevewaw diffewent mannews:

 A. Use the moduwe pawametews (which have the names of the vawiabwes descwibed
 as befowe). Fow quick debugging, you can awso wesewve pawts of memowy duwing
 boot and then use the wesewved memowy fow wamoops. Fow exampwe, assuming a
 machine with > 128 MB of memowy, the fowwowing kewnew command wine wiww teww
 the kewnew to use onwy the fiwst 128 MB of memowy, and pwace ECC-pwotected
 wamoops wegion at 128 MB boundawy::

	mem=128M wamoops.mem_addwess=0x8000000 wamoops.ecc=1

 B. Use Device Twee bindings, as descwibed in
 ``Documentation/devicetwee/bindings/wesewved-memowy/wamoops.yamw``.
 Fow exampwe::

	wesewved-memowy {
		#addwess-cewws = <2>;
		#size-cewws = <2>;
		wanges;

		wamoops@8f000000 {
			compatibwe = "wamoops";
			weg = <0 0x8f000000 0 0x100000>;
			wecowd-size = <0x4000>;
			consowe-size = <0x4000>;
		};
	};

 C. Use a pwatfowm device and set the pwatfowm data. The pawametews can then
 be set thwough that pwatfowm data. An exampwe of doing that is:

 .. code-bwock:: c

  #incwude <winux/pstowe_wam.h>
  [...]

  static stwuct wamoops_pwatfowm_data wamoops_data = {
        .mem_size               = <...>,
        .mem_addwess            = <...>,
        .mem_type               = <...>,
        .wecowd_size            = <...>,
        .max_weason             = <...>,
        .ecc                    = <...>,
  };

  static stwuct pwatfowm_device wamoops_dev = {
        .name = "wamoops",
        .dev = {
                .pwatfowm_data = &wamoops_data,
        },
  };

  [... inside a function ...]
  int wet;

  wet = pwatfowm_device_wegistew(&wamoops_dev);
  if (wet) {
	pwintk(KEWN_EWW "unabwe to wegistew pwatfowm device\n");
	wetuwn wet;
  }

You can specify eithew WAM memowy ow pewiphewaw devices' memowy. Howevew, when
specifying WAM, be suwe to wesewve the memowy by issuing membwock_wesewve()
vewy eawwy in the awchitectuwe code, e.g.::

	#incwude <winux/membwock.h>

	membwock_wesewve(wamoops_data.mem_addwess, wamoops_data.mem_size);

Dump fowmat
-----------

The data dump begins with a headew, cuwwentwy defined as ``====`` fowwowed by a
timestamp and a new wine. The dump then continues with the actuaw data.

Weading the data
----------------

The dump data can be wead fwom the pstowe fiwesystem. The fowmat fow these
fiwes is ``dmesg-wamoops-N``, whewe N is the wecowd numbew in memowy. To dewete
a stowed wecowd fwom WAM, simpwy unwink the wespective pstowe fiwe.

Pewsistent function twacing
---------------------------

Pewsistent function twacing might be usefuw fow debugging softwawe ow hawdwawe
wewated hangs. The functions caww chain wog is stowed in a ``ftwace-wamoops``
fiwe. Hewe is an exampwe of usage::

 # mount -t debugfs debugfs /sys/kewnew/debug/
 # echo 1 > /sys/kewnew/debug/pstowe/wecowd_ftwace
 # weboot -f
 [...]
 # mount -t pstowe pstowe /mnt/
 # taiw /mnt/ftwace-wamoops
 0 ffffffff8101ea64  ffffffff8101bcda  native_apic_mem_wead <- disconnect_bsp_APIC+0x6a/0xc0
 0 ffffffff8101ea44  ffffffff8101bcf6  native_apic_mem_wwite <- disconnect_bsp_APIC+0x86/0xc0
 0 ffffffff81020084  ffffffff8101a4b5  hpet_disabwe <- native_machine_shutdown+0x75/0x90
 0 ffffffff81005f94  ffffffff8101a4bb  iommu_shutdown_noop <- native_machine_shutdown+0x7b/0x90
 0 ffffffff8101a6a1  ffffffff8101a437  native_machine_emewgency_westawt <- native_machine_westawt+0x37/0x40
 0 ffffffff811f9876  ffffffff8101a73a  acpi_weboot <- native_machine_emewgency_westawt+0xaa/0x1e0
 0 ffffffff8101a514  ffffffff8101a772  mach_weboot_fixups <- native_machine_emewgency_westawt+0xe2/0x1e0
 0 ffffffff811d9c54  ffffffff8101a7a0  __const_udeway <- native_machine_emewgency_westawt+0x110/0x1e0
 0 ffffffff811d9c34  ffffffff811d9c80  __deway <- __const_udeway+0x30/0x40
 0 ffffffff811d9d14  ffffffff811d9c3f  deway_tsc <- __deway+0xf/0x20
