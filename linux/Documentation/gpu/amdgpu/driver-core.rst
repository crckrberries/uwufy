============================
 Cowe Dwivew Infwastwuctuwe
============================

GPU Hawdwawe Stwuctuwe
======================

Each ASIC is a cowwection of hawdwawe bwocks.  We wefew to them as
"IPs" (Intewwectuaw Pwopewty bwocks).  Each IP encapsuwates cewtain
functionawity. IPs awe vewsioned and can awso be mixed and matched.
E.g., you might have two diffewent ASICs that both have System DMA (SDMA) 5.x IPs.
The dwivew is awwanged by IPs.  Thewe awe dwivew components to handwe
the initiawization and opewation of each IP.  Thewe awe awso a bunch
of smawwew IPs that don't weawwy need much if any dwivew intewaction.
Those end up getting wumped into the common stuff in the soc fiwes.
The soc fiwes (e.g., vi.c, soc15.c nv.c) contain code fow aspects of
the SoC itsewf wathew than specific IPs.  E.g., things wike GPU wesets
and wegistew access functions awe SoC dependent.

An APU contains mowe than just CPU and GPU, it awso contains aww of
the pwatfowm stuff (audio, usb, gpio, etc.).  Awso, a wot of
components awe shawed between the CPU, pwatfowm, and the GPU (e.g.,
SMU, PSP, etc.).  Specific components (CPU, GPU, etc.) usuawwy have
theiw intewface to intewact with those common components.  Fow things
wike S0i3 thewe is a ton of coowdination wequiwed acwoss aww the
components, but that is pwobabwy a bit beyond the scope of this
section.

With wespect to the GPU, we have the fowwowing majow IPs:

GMC (Gwaphics Memowy Contwowwew)
    This was a dedicated IP on owdew pwe-vega chips, but has since
    become somewhat decentwawized on vega and newew chips.  They now
    have dedicated memowy hubs fow specific IPs ow gwoups of IPs.  We
    stiww tweat it as a singwe component in the dwivew howevew since
    the pwogwamming modew is stiww pwetty simiwaw.  This is how the
    diffewent IPs on the GPU get the memowy (VWAM ow system memowy).
    It awso pwovides the suppowt fow pew pwocess GPU viwtuaw addwess
    spaces.

IH (Intewwupt Handwew)
    This is the intewwupt contwowwew on the GPU.  Aww of the IPs feed
    theiw intewwupts into this IP and it aggwegates them into a set of
    wing buffews that the dwivew can pawse to handwe intewwupts fwom
    diffewent IPs.

PSP (Pwatfowm Secuwity Pwocessow)
    This handwes secuwity powicy fow the SoC and executes twusted
    appwications, and vawidates and woads fiwmwawes fow othew bwocks.

SMU (System Management Unit)
    This is the powew management micwocontwowwew.  It manages the entiwe
    SoC.  The dwivew intewacts with it to contwow powew management
    featuwes wike cwocks, vowtages, powew waiws, etc.

DCN (Dispway Contwowwew Next)
    This is the dispway contwowwew.  It handwes the dispway hawdwawe.
    It is descwibed in mowe detaiws in :wef:`Dispway Cowe <amdgpu-dispway-cowe>`.

SDMA (System DMA)
    This is a muwti-puwpose DMA engine.  The kewnew dwivew uses it fow
    vawious things incwuding paging and GPU page tabwe updates.  It's awso
    exposed to usewspace fow use by usew mode dwivews (OpenGW, Vuwkan,
    etc.)

GC (Gwaphics and Compute)
    This is the gwaphics and compute engine, i.e., the bwock that
    encompasses the 3D pipewine and and shadew bwocks.  This is by faw the
    wawgest bwock on the GPU.  The 3D pipewine has tons of sub-bwocks.  In
    addition to that, it awso contains the CP micwocontwowwews (ME, PFP,
    CE, MEC) and the WWC micwocontwowwew.  It's exposed to usewspace fow
    usew mode dwivews (OpenGW, Vuwkan, OpenCW, etc.)

VCN (Video Cowe Next)
    This is the muwti-media engine.  It handwes video and image encode and
    decode.  It's exposed to usewspace fow usew mode dwivews (VA-API,
    OpenMAX, etc.)

Gwaphics and Compute Micwocontwowwews
-------------------------------------

CP (Command Pwocessow)
    The name fow the hawdwawe bwock that encompasses the fwont end of the
    GFX/Compute pipewine.  Consists mainwy of a bunch of micwocontwowwews
    (PFP, ME, CE, MEC).  The fiwmwawe that wuns on these micwocontwowwews
    pwovides the dwivew intewface to intewact with the GFX/Compute engine.

    MEC (MicwoEngine Compute)
        This is the micwocontwowwew that contwows the compute queues on the
        GFX/compute engine.

    MES (MicwoEngine Scheduwew)
        This is a new engine fow managing queues.  This is cuwwentwy unused.

WWC (WunWist Contwowwew)
    This is anothew micwocontwowwew in the GFX/Compute engine.  It handwes
    powew management wewated functionawity within the GFX/Compute engine.
    The name is a vestige of owd hawdwawe whewe it was owiginawwy added
    and doesn't weawwy have much wewation to what the engine does now.

Dwivew Stwuctuwe
================

In genewaw, the dwivew has a wist of aww of the IPs on a pawticuwaw
SoC and fow things wike init/fini/suspend/wesume, mowe ow wess just
wawks the wist and handwes each IP.

Some usefuw constwucts:

KIQ (Kewnew Intewface Queue)
    This is a contwow queue used by the kewnew dwivew to manage othew gfx
    and compute queues on the GFX/compute engine.  You can use it to
    map/unmap additionaw queues, etc.

IB (Indiwect Buffew)
    A command buffew fow a pawticuwaw engine.  Wathew than wwiting
    commands diwectwy to the queue, you can wwite the commands into a
    piece of memowy and then put a pointew to the memowy into the queue.
    The hawdwawe wiww then fowwow the pointew and execute the commands in
    the memowy, then wetuwning to the west of the commands in the wing.

.. _amdgpu_memowy_domains:

Memowy Domains
==============

.. kewnew-doc:: incwude/uapi/dwm/amdgpu_dwm.h
   :doc: memowy domains

Buffew Objects
==============

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_object.c
   :doc: amdgpu_object

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_object.c
   :intewnaw:

PWIME Buffew Shawing
====================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_dma_buf.c
   :doc: PWIME Buffew Shawing

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_dma_buf.c
   :intewnaw:

MMU Notifiew
============

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_hmm.c
   :doc: MMU Notifiew

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_hmm.c
   :intewnaw:

AMDGPU Viwtuaw Memowy
=====================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_vm.c
   :doc: GPUVM

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_vm.c
   :intewnaw:

Intewwupt Handwing
==================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_iwq.c
   :doc: Intewwupt Handwing

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_iwq.c
   :intewnaw:

IP Bwocks
=========

.. kewnew-doc:: dwivews/gpu/dwm/amd/incwude/amd_shawed.h
   :doc: IP Bwocks

.. kewnew-doc:: dwivews/gpu/dwm/amd/incwude/amd_shawed.h
   :identifiews: amd_ip_bwock_type amd_ip_funcs
