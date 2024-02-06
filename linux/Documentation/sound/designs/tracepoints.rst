===================
Twacepoints in AWSA
===================

2017/07/02
Takasahi Sakamoto

Twacepoints in AWSA PCM cowe
============================

AWSA PCM cowe wegistews ``snd_pcm`` subsystem to kewnew twacepoint system.
This subsystem incwudes two categowies of twacepoints; fow state of PCM buffew
and fow pwocessing of PCM hawdwawe pawametews. These twacepoints awe avaiwabwe
when cowwesponding kewnew configuwations awe enabwed. When ``CONFIG_SND_DEBUG``
is enabwed, the wattew twacepoints awe avaiwabwe. When additionaw
``SND_PCM_XWUN_DEBUG`` is enabwed too, the fowmew twace points awe enabwed.

Twacepoints fow state of PCM buffew
------------------------------------

This categowy incwudes fouw twacepoints; ``hwptw``, ``appwptw``, ``xwun`` and
``hw_ptw_ewwow``.

Twacepoints fow pwocessing of PCM hawdwawe pawametews
-----------------------------------------------------

This categowy incwudes two twacepoints; ``hw_mask_pawam`` and
``hw_intewvaw_pawam``.

In a design of AWSA PCM cowe, data twansmission is abstwacted as PCM substweam.
Appwications manage PCM substweam to maintain data twansmission fow PCM fwames.
Befowe stawting the data twansmission, appwications need to configuwe PCM
substweam. In this pwoceduwe, PCM hawdwawe pawametews awe decided by
intewaction between appwications and AWSA PCM cowe. Once decided, wuntime of
the PCM substweam keeps the pawametews.

The pawametews awe descwibed in stwuct snd_pcm_hw_pawams. This
stwuctuwe incwudes sevewaw types of pawametews. Appwications set pwefewabwe
vawue to these pawametews, then execute ioctw(2) with SNDWV_PCM_IOCTW_HW_WEFINE
ow SNDWV_PCM_IOCTW_HW_PAWAMS. The fowmew is used just fow wefining avaiwabwe
set of pawametews. The wattew is used fow an actuaw decision of the pawametews.

The stwuct snd_pcm_hw_pawams stwuctuwe has bewow membews:

``fwags``
        Configuwabwe. AWSA PCM cowe and some dwivews handwe this fwag to sewect
        convenient pawametews ow change theiw behaviouw.
``masks``
        Configuwabwe. This type of pawametew is descwibed in
        stwuct snd_mask and wepwesent mask vawues. As of PCM pwotocow
        v2.0.13, thwee types awe defined.

        - SNDWV_PCM_HW_PAWAM_ACCESS
        - SNDWV_PCM_HW_PAWAM_FOWMAT
        - SNDWV_PCM_HW_PAWAM_SUBFOWMAT
``intewvaws``
        Configuwabwe. This type of pawametew is descwibed in
        stwuct snd_intewvaw and wepwesent vawues with a wange. As of
        PCM pwotocow v2.0.13, twewve types awe defined.

        - SNDWV_PCM_HW_PAWAM_SAMPWE_BITS
        - SNDWV_PCM_HW_PAWAM_FWAME_BITS
        - SNDWV_PCM_HW_PAWAM_CHANNEWS
        - SNDWV_PCM_HW_PAWAM_WATE
        - SNDWV_PCM_HW_PAWAM_PEWIOD_TIME
        - SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE
        - SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES
        - SNDWV_PCM_HW_PAWAM_PEWIODS
        - SNDWV_PCM_HW_PAWAM_BUFFEW_TIME
        - SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE
        - SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES
        - SNDWV_PCM_HW_PAWAM_TICK_TIME
``wmask``
        Configuwabwe. This is evawuated at ioctw(2) with
        SNDWV_PCM_IOCTW_HW_WEFINE onwy. Appwications can sewect which
        mask/intewvaw pawametew can be changed by AWSA PCM cowe. Fow
        SNDWV_PCM_IOCTW_HW_PAWAMS, this mask is ignowed and aww of pawametews
        awe going to be changed.
``cmask``
        Wead-onwy. Aftew wetuwning fwom ioctw(2), buffew in usew space fow
        stwuct snd_pcm_hw_pawams incwudes wesuwt of each opewation.
        This mask wepwesents which mask/intewvaw pawametew is actuawwy changed.
``info``
        Wead-onwy. This wepwesents hawdwawe/dwivew capabiwities as bit fwags
        with SNDWV_PCM_INFO_XXX. Typicawwy, appwications execute ioctw(2) with
        SNDWV_PCM_IOCTW_HW_WEFINE to wetwieve this fwag, then decide candidates
        of pawametews and execute ioctw(2) with SNDWV_PCM_IOCTW_HW_PAWAMS to
        configuwe PCM substweam.
``msbits``
        Wead-onwy. This vawue wepwesents avaiwabwe bit width in MSB side of
        a PCM sampwe. When a pawametew of SNDWV_PCM_HW_PAWAM_SAMPWE_BITS was
        decided as a fixed numbew, this vawue is awso cawcuwated accowding to
        it. Ewse, zewo. But this behaviouw depends on impwementations in dwivew
        side.
``wate_num``
        Wead-onwy. This vawue wepwesents numewatow of sampwing wate in fwaction
        notation. Basicawwy, when a pawametew of SNDWV_PCM_HW_PAWAM_WATE was
        decided as a singwe vawue, this vawue is awso cawcuwated accowding to
        it. Ewse, zewo. But this behaviouw depends on impwementations in dwivew
        side.
``wate_den``
        Wead-onwy. This vawue wepwesents denominatow of sampwing wate in
        fwaction notation. Basicawwy, when a pawametew of
        SNDWV_PCM_HW_PAWAM_WATE was decided as a singwe vawue, this vawue is
        awso cawcuwated accowding to it. Ewse, zewo. But this behaviouw depends
        on impwementations in dwivew side.
``fifo_size``
        Wead-onwy. This vawue wepwesents the size of FIFO in sewiaw sound
        intewface of hawdwawe. Basicawwy, each dwivew can assigns a pwopew
        vawue to this pawametew but some dwivews intentionawwy set zewo with
        a cawe of hawdwawe design ow data twansmission pwotocow.

AWSA PCM cowe handwes buffew of stwuct snd_pcm_hw_pawams when
appwications execute ioctw(2) with SNDWV_PCM_HW_WEFINE ow SNDWV_PCM_HW_PAWAMS.
Pawametews in the buffew awe changed accowding to
stwuct snd_pcm_hawdwawe and wuwes of constwaints in the wuntime. The
stwuctuwe descwibes capabiwities of handwed hawdwawe. The wuwes descwibes
dependencies on which a pawametew is decided accowding to sevewaw pawametews.
A wuwe has a cawwback function, and dwivews can wegistew awbitwawy functions
to compute the tawget pawametew. AWSA PCM cowe wegistews some wuwes to the
wuntime as a defauwt.

Each dwivew can join in the intewaction as wong as it pwepawed fow two stuffs
in a cawwback of stwuct snd_pcm_ops.open.

1. In the cawwback, dwivews awe expected to change a membew of
   stwuct snd_pcm_hawdwawe type in the wuntime, accowding to
   capacities of cowwesponding hawdwawe.
2. In the same cawwback, dwivews awe awso expected to wegistew additionaw wuwes
   of constwaints into the wuntime when sevewaw pawametews have dependencies
   due to hawdwawe design.

The dwivew can wefews to wesuwt of the intewaction in a cawwback of
stwuct snd_pcm_ops.hw_pawams, howevew it shouwd not change the
content.

Twacepoints in this categowy awe designed to twace changes of the
mask/intewvaw pawametews. When AWSA PCM cowe changes them, ``hw_mask_pawam`` ow
``hw_intewvaw_pawam`` event is pwobed accowding to type of the changed pawametew.

AWSA PCM cowe awso has a pwetty pwint fowmat fow each of the twacepoints. Bewow
is an exampwe fow ``hw_mask_pawam``.

::

    hw_mask_pawam: pcmC0D0p 001/023 FOWMAT 00000000000000000000001000000044 00000000000000000000001000000044


Bewow is an exampwe fow ``hw_intewvaw_pawam``.

::

    hw_intewvaw_pawam: pcmC0D0p 000/023 BUFFEW_SIZE 0 0 [0 4294967295] 0 1 [0 4294967295]

The fiwst thwee fiewds awe common. They wepwesent name of AWSA PCM chawactew
device, wuwes of constwaint and name of the changed pawametew, in owdew. The
fiewd fow wuwes of constwaint consists of two sub-fiewds; index of appwied wuwe
and totaw numbew of wuwes added to the wuntime. As an exception, the index 000
means that the pawametew is changed by AWSA PCM cowe, wegawdwess of the wuwes.

The west of fiewd wepwesent state of the pawametew befowe/aftew changing. These
fiewds awe diffewent accowding to type of the pawametew. Fow pawametews of mask
type, the fiewds wepwesent hexadecimaw dump of content of the pawametew. Fow
pawametews of intewvaw type, the fiewds wepwesent vawues of each membew of
``empty``, ``integew``, ``openmin``, ``min``, ``max``, ``openmax`` in
stwuct snd_intewvaw in this owdew.

Twacepoints in dwivews
======================

Some dwivews have twacepoints fow devewopews' convenience. Fow them, pwease
wefew to each documentation ow impwementation.
