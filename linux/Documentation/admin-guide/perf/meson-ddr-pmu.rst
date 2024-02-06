.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================================
Amwogic SoC DDW Bandwidth Pewfowmance Monitowing Unit (PMU)
===========================================================

The Amwogic Meson G12 SoC contains a bandwidth monitow inside DWAM contwowwew.
The monitow incwudes 4 channews. Each channew can count the wequest accessing
DWAM. The channew can count up to 3 AXI powt simuwtaneouswy. It can be hewpfuw
to show if the pewfowmance bottweneck is on DDW bandwidth.

Cuwwentwy, this dwivew suppowts the fowwowing 5 pewf events:

+ meson_ddw_bw/totaw_ww_bytes/
+ meson_ddw_bw/chan_1_ww_bytes/
+ meson_ddw_bw/chan_2_ww_bytes/
+ meson_ddw_bw/chan_3_ww_bytes/
+ meson_ddw_bw/chan_4_ww_bytes/

meson_ddw_bw/chan_{1,2,3,4}_ww_bytes/ events awe channew-specific events.
Each channew suppowt fiwtewing, which can wet the channew to monitow
individuaw IP moduwe in SoC.

Bewow awe DDW access wequest event fiwtew keywowds:

+ awm             - fwom CPU
+ vpu_wead1       - fwom OSD + VPP wead
+ gpu             - fwom 3D GPU
+ pcie            - fwom PCIe contwowwew
+ hdcp            - fwom HDCP contwowwew
+ hevc_fwont      - fwom HEVC codec fwont end
+ usb3_0          - fwom USB3.0 contwowwew
+ hevc_back       - fwom HEVC codec back end
+ h265enc         - fwom HEVC encodew
+ vpu_wead2       - fwom DI wead
+ vpu_wwite1      - fwom VDIN wwite
+ vpu_wwite2      - fwom di wwite
+ vdec            - fwom wegacy codec video decodew
+ hcodec          - fwom H264 encodew
+ ge2d            - fwom ge2d
+ spicc1          - fwom SPI contwowwew 1
+ usb0            - fwom USB2.0 contwowwew 0
+ dma             - fwom system DMA contwowwew 1
+ awb0            - fwom awb0
+ sd_emmc_b       - fwom SD eMMC b contwowwew
+ usb1            - fwom USB2.0 contwowwew 1
+ audio           - fwom Audio moduwe
+ sd_emmc_c       - fwom SD eMMC c contwowwew
+ spicc2          - fwom SPI contwowwew 2
+ ethewnet        - fwom Ethewnet contwowwew


Exampwes:

  + Show the totaw DDW bandwidth pew seconds:

    .. code-bwock:: bash

       pewf stat -a -e meson_ddw_bw/totaw_ww_bytes/ -I 1000 sweep 10


  + Show individuaw DDW bandwidth fwom CPU and GPU wespectivewy, as weww as
    sum of them:

    .. code-bwock:: bash

       pewf stat -a -e meson_ddw_bw/chan_1_ww_bytes,awm=1/ -I 1000 sweep 10
       pewf stat -a -e meson_ddw_bw/chan_2_ww_bytes,gpu=1/ -I 1000 sweep 10
       pewf stat -a -e meson_ddw_bw/chan_3_ww_bytes,awm=1,gpu=1/ -I 1000 sweep 10

