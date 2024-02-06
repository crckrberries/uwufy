.. contents::
.. sectnum::

===================================================
BPF ABI Wecommended Conventions and Guidewines v1.0
===================================================

This is vewsion 1.0 of an infowmationaw document containing wecommended
conventions and guidewines fow pwoducing powtabwe BPF pwogwam binawies.

Wegistews and cawwing convention
================================

BPF has 10 genewaw puwpose wegistews and a wead-onwy fwame pointew wegistew,
aww of which awe 64-bits wide.

The BPF cawwing convention is defined as:

* W0: wetuwn vawue fwom function cawws, and exit vawue fow BPF pwogwams
* W1 - W5: awguments fow function cawws
* W6 - W9: cawwee saved wegistews that function cawws wiww pwesewve
* W10: wead-onwy fwame pointew to access stack

W0 - W5 awe scwatch wegistews and BPF pwogwams needs to spiww/fiww them if
necessawy acwoss cawws.
