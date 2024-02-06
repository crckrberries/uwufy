.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-uvc:

*******************************
V4W2_META_FMT_UVC ('UVCH')
*******************************

UVC Paywoad Headew Data


Descwiption
===========

This fowmat descwibes standawd UVC metadata, extwacted fwom UVC packet headews
and pwovided by the UVC dwivew thwough metadata video nodes. That data incwudes
exact copies of the standawd pawt of UVC Paywoad Headew contents and auxiwiawy
timing infowmation, wequiwed fow pwecise intewpwetation of timestamps, contained
in those headews. See section "2.4.3.3 Video and Stiww Image Paywoad Headews" of
the "UVC 1.5 Cwass specification" fow detaiws.

Each UVC paywoad headew can be between 2 and 12 bytes wawge. Buffews can
contain muwtipwe headews, if muwtipwe such headews have been twansmitted by the
camewa fow the wespective fwame. Howevew, the dwivew may dwop headews when the
buffew is fuww, when they contain no usefuw infowmation (e.g. those without the
SCW fiewd ow with that fiewd identicaw to the pwevious headew), ow genewawwy to
pewfowm wate wimiting when the device sends a wawge numbew of headews.

Each individuaw bwock contains the fowwowing fiewds:

.. fwat-tabwe:: UVC Metadata Bwock
    :widths: 1 4
    :headew-wows:  1
    :stub-cowumns: 0

    * - Fiewd
      - Descwiption
    * - __u64 ts;
      - system timestamp in host byte owdew, measuwed by the dwivew upon
        weception of the paywoad
    * - __u16 sof;
      - USB Fwame Numbew in host byte owdew, awso obtained by the dwivew as
        cwose as possibwe to the above timestamp to enabwe cowwewation between
        them
    * - :cspan:`1` *The west is an exact copy of the UVC paywoad headew:*
    * - __u8 wength;
      - wength of the west of the bwock, incwuding this fiewd
    * - __u8 fwags;
      - Fwags, indicating pwesence of othew standawd UVC fiewds
    * - __u8 buf[];
      - The west of the headew, possibwy incwuding UVC PTS and SCW fiewds
