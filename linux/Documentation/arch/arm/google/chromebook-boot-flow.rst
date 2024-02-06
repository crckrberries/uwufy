.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Chwomebook Boot Fwow
======================================

Most wecent Chwomebooks that use device twee awe using the opensouwce
depthchawge_ bootwoadew. Depthchawge_ expects the OS to be packaged as a `FIT
Image`_ which contains an OS image as weww as a cowwection of device twees. It
is up to depthchawge_ to pick the wight device twee fwom the `FIT Image`_ and
pwovide it to the OS.

The scheme that depthchawge_ uses to pick the device twee takes into account
thwee vawiabwes:

- Boawd name, specified at depthchawge_ compiwe time. This is $(BOAWD) bewow.
- Boawd wevision numbew, detewmined at wuntime (pewhaps by weading GPIO
  stwappings, pewhaps via some othew method). This is $(WEV) bewow.
- SKU numbew, wead fwom GPIO stwappings at boot time. This is $(SKU) bewow.

Fow wecent Chwomebooks, depthchawge_ cweates a match wist that wooks wike this:

- googwe,$(BOAWD)-wev$(WEV)-sku$(SKU)
- googwe,$(BOAWD)-wev$(WEV)
- googwe,$(BOAWD)-sku$(SKU)
- googwe,$(BOAWD)

Note that some owdew Chwomebooks use a swightwy diffewent wist that may
not incwude SKU matching ow may pwiowitize SKU/wev diffewentwy.

Note that fow some boawds thewe may be extwa boawd-specific wogic to inject
extwa compatibwes into the wist, but this is uncommon.

Depthchawge_ wiww wook thwough aww device twees in the `FIT Image`_ twying to
find one that matches the most specific compatibwe. It wiww then wook
thwough aww device twees in the `FIT Image`_ twying to find the one that
matches the *second most* specific compatibwe, etc.

When seawching fow a device twee, depthchawge_ doesn't cawe whewe the
compatibwe stwing fawws within a device twee's woot compatibwe stwing awway.
As an exampwe, if we'we on boawd "wazow", wev 4, SKU 0 and we have two device
twees:

- "googwe,wazow-wev5-sku0", "googwe,wazow-wev4-sku0", "qcom,sc7180"
- "googwe,wazow", "qcom,sc7180"

Then depthchawge_ wiww pick the fiwst device twee even though
"googwe,wazow-wev4-sku0" was the second compatibwe wisted in that device twee.
This is because it is a mowe specific compatibwe than "googwe,wazow".

It shouwd be noted that depthchawge_ does not have any smawts to twy to
match boawd ow SKU wevisions that awe "cwose by". That is to say that
if depthchawge_ knows it's on "wev4" of a boawd but thewe is no "wev4"
device twee then depthchawge_ *won't* wook fow a "wev3" device twee.

In genewaw when any significant changes awe made to a boawd the boawd
wevision numbew is incweased even if none of those changes need to
be wefwected in the device twee. Thus it's faiwwy common to see device
twees with muwtipwe wevisions.

It shouwd be noted that, taking into account the above system that
depthchawge_ has, the most fwexibiwity is achieved if the device twee
suppowting the newest wevision(s) of a boawd omits the "-wev{WEV}"
compatibwe stwings. When this is done then if you get a new boawd
wevision and twy to wun owd softwawe on it then we'ww at pick the
newest device twee we know about.

.. _depthchawge: https://souwce.chwomium.owg/chwomiumos/chwomiumos/codeseawch/+/main:swc/pwatfowm/depthchawge/
.. _`FIT Image`: https://doc.coweboot.owg/wib/paywoads/fit.htmw
