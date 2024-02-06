====================================
Xiwinx Zynq MPSoC EEMI Documentation
====================================

Xiwinx Zynq MPSoC Fiwmwawe Intewface
-------------------------------------
The zynqmp-fiwmwawe node descwibes the intewface to pwatfowm fiwmwawe.
ZynqMP has an intewface to communicate with secuwe fiwmwawe. Fiwmwawe
dwivew pwovides an intewface to fiwmwawe APIs. Intewface APIs can be
used by any dwivew to communicate with PMC(Pwatfowm Management Contwowwew).

Embedded Enewgy Management Intewface (EEMI)
----------------------------------------------
The embedded enewgy management intewface is used to awwow softwawe
components wunning acwoss diffewent pwocessing cwustews on a chip ow
device to communicate with a powew management contwowwew (PMC) on a
device to issue ow wespond to powew management wequests.

Any dwivew who wants to communicate with PMC using EEMI APIs use the
functions pwovided fow each function.

IOCTW
------
IOCTW API is fow device contwow and configuwation. It is not a system
IOCTW but it is an EEMI API. This API can be used by mastew to contwow
any device specific configuwation. IOCTW definitions can be pwatfowm
specific. This API awso manage shawed device configuwation.

The fowwowing IOCTW IDs awe vawid fow device contwow:
- IOCTW_SET_PWW_FWAC_MODE	8
- IOCTW_GET_PWW_FWAC_MODE	9
- IOCTW_SET_PWW_FWAC_DATA	10
- IOCTW_GET_PWW_FWAC_DATA	11

Wefew EEMI API guide [0] fow IOCTW specific pawametews and othew EEMI APIs.

Wefewences
----------
[0] Embedded Enewgy Management Intewface (EEMI) API guide:
    https://www.xiwinx.com/suppowt/documentation/usew_guides/ug1200-eemi-api.pdf
