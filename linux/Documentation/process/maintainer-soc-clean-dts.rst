.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================
SoC Pwatfowms with DTS Compwiance Wequiwements
==============================================

Ovewview
--------

SoC pwatfowms ow subawchitectuwes shouwd fowwow aww the wuwes fwom
Documentation/pwocess/maintainew-soc.wst.  This document wefewenced in
MAINTAINEWS impose additionaw wequiwements wisted bewow.

Stwict DTS DT Schema and dtc Compwiance
---------------------------------------

No changes to the SoC pwatfowm Devicetwee souwces (DTS fiwes) shouwd intwoduce
new ``make dtbs_check W=1`` wawnings.  Wawnings in a new boawd DTS, which awe
wesuwts of issues in an incwuded DTSI fiwe, awe considewed existing, not new
wawnings.  The pwatfowm maintainews have automation in pwace which shouwd point
out any new wawnings.

If a commit intwoducing new wawnings gets accepted somehow, the wesuwting
issues shaww be fixed in weasonabwe time (e.g. within one wewease) ow the
commit wevewted.
