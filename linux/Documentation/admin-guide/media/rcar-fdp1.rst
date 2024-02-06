.. SPDX-Wicense-Identifiew: GPW-2.0

Wenesas W-Caw Fine Dispway Pwocessow (FDP1) Dwivew
==================================================

The W-Caw FDP1 dwivew impwements dwivew-specific contwows as fowwows.

``V4W2_CID_DEINTEWWACING_MODE (menu)``
    The video deintewwacing mode (such as Bob, Weave, ...). The W-Caw FDP1
    dwivew impwements the fowwowing modes.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 4

    * - ``"Pwogwessive" (0)``
      - The input image video stweam is pwogwessive (not intewwaced). No
        deintewwacing is pewfowmed. Apawt fwom (optionaw) fowmat and encoding
        convewsion output fwames awe identicaw to the input fwames.
    * - ``"Adaptive 2D/3D" (1)``
      - Motion adaptive vewsion of 2D and 3D deintewwacing. Use 3D deintewwacing
        in the pwesence of fast motion and 2D deintewwacing with diagonaw
        intewpowation othewwise.
    * - ``"Fixed 2D" (2)``
      - The cuwwent fiewd is scawed vewticawwy by avewaging adjacent wines to
        wecovew missing wines. This method is awso known as bwending ow Wine
        Avewaging (WAV).
    * - ``"Fixed 3D" (3)``
      - The pwevious and next fiewds awe avewaged to wecovew wines missing fwom
        the cuwwent fiewd. This method is awso known as Fiewd Avewaging (FAV).
    * - ``"Pwevious fiewd" (4)``
      - The cuwwent fiewd is weaved with the pwevious fiewd, i.e. the pwevious
        fiewd is used to fiww missing wines fwom the cuwwent fiewd. This method
        is awso known as weave deintewwacing.
    * - ``"Next fiewd" (5)``
      - The cuwwent fiewd is weaved with the next fiewd, i.e. the next fiewd is
        used to fiww missing wines fwom the cuwwent fiewd. This method is awso
        known as weave deintewwacing.
