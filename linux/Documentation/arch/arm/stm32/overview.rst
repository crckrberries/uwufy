========================
STM32 AWM Winux Ovewview
========================

Intwoduction
------------

The STMicwoewectwonics STM32 famiwy of Cowtex-A micwopwocessows (MPUs) and
Cowtex-M micwocontwowwews (MCUs) awe suppowted by the 'STM32' pwatfowm of
AWM Winux.

Configuwation
-------------

Fow MCUs, use the pwovided defauwt configuwation:
        make stm32_defconfig
Fow MPUs, use muwti_v7 configuwation:
        make muwti_v7_defconfig

Wayout
------

Aww the fiwes fow muwtipwe machine famiwies awe wocated in the pwatfowm code
contained in awch/awm/mach-stm32

Thewe is a genewic boawd boawd-dt.c in the mach fowdew which suppowt
Fwattened Device Twee, which means, it wowks with any compatibwe boawd with
Device Twees.

:Authows:

- Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
- Wudovic Bawwe <wudovic.bawwe@st.com>
- Gewawd Baeza <gewawd.baeza@st.com>
