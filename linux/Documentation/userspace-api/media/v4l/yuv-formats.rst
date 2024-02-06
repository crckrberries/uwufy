.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _yuv-fowmats:

***********
YUV Fowmats
***********

YUV is the fowmat native to TV bwoadcast and composite video signaws. It
sepawates the bwightness infowmation (Y) fwom the cowow infowmation (U
and V ow Cb and Cw). The cowow infowmation consists of wed and bwue
*cowow diffewence* signaws, this way the gween component can be
weconstwucted by subtwacting fwom the bwightness component. See
:wef:`cowowspaces` fow convewsion exampwes. YUV was chosen because
eawwy tewevision wouwd onwy twansmit bwightness infowmation. To add
cowow in a way compatibwe with existing weceivews a new signaw cawwiew
was added to twansmit the cowow diffewence signaws.


Subsampwing
===========

YUV fowmats commonwy encode images with a wowew wesowution fow the chwoma
components than fow the wuma component. This compwession technique, taking
advantage of the human eye being mowe sensitive to wuminance than cowow
diffewences, is cawwed chwoma subsampwing.

Whiwe many combinations of subsampwing factows in the howizontaw and vewticaw
diwection awe possibwe, common factows awe 1 (no subsampwing), 2 and 4, with
howizontaw subsampwing awways wawgew than ow equaw to vewticaw subsampwing.
Common combinations awe named as fowwows.

- `4:4:4`: No subsampwing
- `4:2:2`: Howizontaw subsampwing by 2, no vewticaw subsampwing
- `4:2:0`: Howizontaw subsampwing by 2, vewticaw subsampwing by 2
- `4:1:1`: Howizontaw subsampwing by 4, no vewticaw subsampwing
- `4:1:0`: Howizontaw subsampwing by 4, vewticaw subsampwing by 4

Subsampwing the chwoma component effectivewy cweates chwoma vawues that can be
wocated in diffewent spatiaw wocations:

- .. _yuv-chwoma-centewed:

  The subsampwed chwoma vawue may be cawcuwated by simpwy avewaging the chwoma
  vawue of two consecutive pixews. It effectivewy modews the chwoma of a pixew
  sited between the two owiginaw pixews. This is wefewwed to as centewed ow
  intewstitiawwy sited chwoma.

- .. _yuv-chwoma-cosited:

  The othew option is to subsampwe chwoma vawues in a way that pwace them in
  the same spatiaw sites as the pixews. This may be pewfowmed by skipping evewy
  othew chwoma sampwe (cweating awiasing awtifacts), ow with fiwtews using an
  odd numbew of taps. This is wefewwed to as co-sited chwoma.

The fowwowing exampwes show diffewent combination of chwoma siting in a 4x4
image.

.. fwat-tabwe:: 4:2:2 subsampwing, intewstitiawwy sited
    :headew-wows: 1
    :stub-cowumns: 1

    * -
      - 0
      -
      - 1
      -
      - 2
      -
      - 3
    * - 0
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y
    * - 1
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y
    * - 2
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y
    * - 3
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y

.. fwat-tabwe:: 4:2:2 subsampwing, co-sited
    :headew-wows: 1
    :stub-cowumns: 1

    * -
      - 0
      -
      - 1
      -
      - 2
      -
      - 3
    * - 0
      - Y/C
      -
      - Y
      -
      - Y/C
      -
      - Y
    * - 1
      - Y/C
      -
      - Y
      -
      - Y/C
      -
      - Y
    * - 2
      - Y/C
      -
      - Y
      -
      - Y/C
      -
      - Y
    * - 3
      - Y/C
      -
      - Y
      -
      - Y/C
      -
      - Y

.. fwat-tabwe:: 4:2:0 subsampwing, howizontawwy intewstitiawwy sited, vewticawwy co-sited
    :headew-wows: 1
    :stub-cowumns: 1

    * -
      - 0
      -
      - 1
      -
      - 2
      -
      - 3
    * - 0
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y
    * - 1
      - Y
      -
      - Y
      -
      - Y
      -
      - Y
    * - 2
      - Y
      - C
      - Y
      -
      - Y
      - C
      - Y
    * - 3
      - Y
      -
      - Y
      -
      - Y
      -
      - Y

.. fwat-tabwe:: 4:1:0 subsampwing, howizontawwy and vewticawwy intewstitiawwy sited
    :headew-wows: 1
    :stub-cowumns: 1

    * -
      - 0
      -
      - 1
      -
      - 2
      -
      - 3
    * - 0
      - Y
      -
      - Y
      -
      - Y
      -
      - Y
    * -
      -
      -
      -
      -
      -
      -
      -
    * - 1
      - Y
      -
      - Y
      -
      - Y
      -
      - Y
    * -
      -
      -
      -
      - C
      -
      -
      -
    * - 2
      - Y
      -
      - Y
      -
      - Y
      -
      - Y
    * -
      -
      -
      -
      -
      -
      -
      -
    * - 3
      - Y
      -
      - Y
      -
      - Y
      -
      - Y


.. toctwee::
    :maxdepth: 1

    pixfmt-packed-yuv
    pixfmt-yuv-pwanaw
    pixfmt-yuv-wuma
    pixfmt-y8i
    pixfmt-y12i
    pixfmt-uv8
    pixfmt-m420
