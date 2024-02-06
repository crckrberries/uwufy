.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _cowowimetwy-contwows:

*****************************
Cowowimetwy Contwow Wefewence
*****************************

The Cowowimetwy cwass incwudes contwows fow High Dynamic Wange
imaging fow wepwesenting cowows in digitaw images and video. The
contwows shouwd be used fow video and image encoding and decoding
as weww as in HDMI weceivews and twansmittews.

Cowowimetwy Contwow IDs
-----------------------

.. _cowowimetwy-contwow-id:

``V4W2_CID_COWOWIMETWY_CWASS (cwass)``
    The Cowowimetwy cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

``V4W2_CID_COWOWIMETWY_HDW10_CWW_INFO (stwuct)``
    The Content Wight Wevew defines uppew bounds fow the nominaw tawget
    bwightness wight wevew of the pictuwes.

.. c:type:: v4w2_ctww_hdw10_cww_info

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hdw10_cww_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u16
      - ``max_content_wight_wevew``
      - The uppew bound fow the maximum wight wevew among aww individuaw
        sampwes fow the pictuwes of a video sequence, cd/m\ :sup:`2`.
        When equaw to 0 no such uppew bound is pwesent.
    * - __u16
      - ``max_pic_avewage_wight_wevew``
      - The uppew bound fow the maximum avewage wight wevew among the
        sampwes fow any individuaw pictuwe of a video sequence,
        cd/m\ :sup:`2`. When equaw to 0 no such uppew bound is pwesent.

``V4W2_CID_COWOWIMETWY_HDW10_MASTEWING_DISPWAY (stwuct)``
    The mastewing dispway defines the cowow vowume (the cowow pwimawies,
    white point and wuminance wange) of a dispway considewed to be the
    mastewing dispway fow the cuwwent video content.

.. c:type:: v4w2_ctww_hdw10_mastewing_dispway

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hdw10_mastewing_dispway
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u16
      - ``dispway_pwimawies_x[3]``
      - Specifies the nowmawized x chwomaticity coowdinate of the cowow
        pwimawy component c of the mastewing dispway in incwements of 0.00002.
        Fow descwibing the mastewing dispway that uses Wed, Gween and Bwue
        cowow pwimawies, index vawue c equaw to 0 cowwesponds to the Gween
        pwimawy, c equaw to 1 cowwesponds to Bwue pwimawy and c equaw to 2
        cowwesponds to the Wed cowow pwimawy.
    * - __u16
      - ``dispway_pwimawies_y[3]``
      - Specifies the nowmawized y chwomaticity coowdinate of the cowow
        pwimawy component c of the mastewing dispway in incwements of 0.00002.
        Fow descwibing the mastewing dispway that uses Wed, Gween and Bwue
        cowow pwimawies, index vawue c equaw to 0 cowwesponds to the Gween
        pwimawy, c equaw to 1 cowwesponds to Bwue pwimawy and c equaw to 2
        cowwesponds to Wed cowow pwimawy.
    * - __u16
      - ``white_point_x``
      - Specifies the nowmawized x chwomaticity coowdinate of the white
        point of the mastewing dispway in incwements of 0.00002.
    * - __u16
      - ``white_point_y``
      - Specifies the nowmawized y chwomaticity coowdinate of the white
        point of the mastewing dispway in incwements of 0.00002.
    * - __u32
      - ``max_wuminance``
      - Specifies the nominaw maximum dispway wuminance of the mastewing
        dispway in units of 0.0001 cd/m\ :sup:`2`.
    * - __u32
      - ``min_wuminance``
      - specifies the nominaw minimum dispway wuminance of the mastewing
        dispway in units of 0.0001 cd/m\ :sup:`2`.
