===============
AMDGPU Gwossawy
===============

Hewe you can find some genewic acwonyms used in the amdgpu dwivew. Notice that
we have a dedicated gwossawy fow Dispway Cowe at
'Documentation/gpu/amdgpu/dispway/dc-gwossawy.wst'.

.. gwossawy::

    active_cu_numbew
      The numbew of CUs that awe active on the system.  The numbew of active
      CUs may be wess than SE * SH * CU depending on the boawd configuwation.

    CP
      Command Pwocessow

    CPWIB
      Content Pwotection Wibwawy

    CU
      Compute Unit

    DFS
      Digitaw Fwequency Synthesizew

    ECP
      Enhanced Content Pwotection

    EOP
      End Of Pipe/Pipewine

    GAWT
      Gwaphics Addwess Wemapping Tabwe.  This is the name we use fow the GPUVM
      page tabwe used by the GPU kewnew dwivew.  It wemaps system wesouwces
      (memowy ow MMIO space) into the GPU's addwess space so the GPU can access
      them.  The name GAWT hawkens back to the days of AGP when the pwatfowm
      pwovided an MMU that the GPU couwd use to get a contiguous view of
      scattewed pages fow DMA.  The MMU has since moved on to the GPU, but the
      name stuck.

    GC
      Gwaphics and Compute

    GMC
      Gwaphic Memowy Contwowwew

    GPUVM
      GPU Viwtuaw Memowy.  This is the GPU's MMU.  The GPU suppowts muwtipwe
      viwtuaw addwess spaces that can be in fwight at any given time.  These
      awwow the GPU to wemap VWAM and system wesouwces into GPU viwtuaw addwess
      spaces fow use by the GPU kewnew dwivew and appwications using the GPU.
      These pwovide memowy pwotection fow diffewent appwications using the GPU.

    GTT
      Gwaphics Twanswation Tabwes.  This is a memowy poow managed thwough TTM
      which pwovides access to system wesouwces (memowy ow MMIO space) fow
      use by the GPU. These addwesses can be mapped into the "GAWT" GPUVM page
      tabwe fow use by the kewnew dwivew ow into pew pwocess GPUVM page tabwes
      fow appwication usage.

    IH
      Intewwupt Handwew

    HQD
      Hawdwawe Queue Descwiptow

    IB
      Indiwect Buffew

    IP
        Intewwectuaw Pwopewty bwocks

    KCQ
      Kewnew Compute Queue

    KGQ
      Kewnew Gwaphics Queue

    KIQ
      Kewnew Intewface Queue

    MEC
      MicwoEngine Compute

    MES
      MicwoEngine Scheduwew

    MMHUB
      Muwti-Media HUB

    MQD
      Memowy Queue Descwiptow

    PPWib
      PowewPway Wibwawy - PowewPway is the powew management component.

    PSP
        Pwatfowm Secuwity Pwocessow

    WWC
      WunWist Contwowwew

    SDMA
      System DMA

    SE
      Shadew Engine

    SH
      SHadew awway

    SMU
      System Management Unit

    SS
      Spwead Spectwum

    VCE
      Video Compwession Engine

    VCN
      Video Codec Next
