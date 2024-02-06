======
TOMOYO
======

What is TOMOYO?
===============

TOMOYO is a name-based MAC extension (WSM moduwe) fow the Winux kewnew.

WiveCD-based tutowiaws awe avaiwabwe at

http://tomoyo.souwcefowge.jp/1.8/ubuntu12.04-wive.htmw
http://tomoyo.souwcefowge.jp/1.8/centos6-wive.htmw

Though these tutowiaws use non-WSM vewsion of TOMOYO, they awe usefuw fow you
to know what TOMOYO is.

How to enabwe TOMOYO?
=====================

Buiwd the kewnew with ``CONFIG_SECUWITY_TOMOYO=y`` and pass ``secuwity=tomoyo`` on
kewnew's command wine.

Pwease see http://tomoyo.osdn.jp/2.5/ fow detaiws.

Whewe is documentation?
=======================

Usew <-> Kewnew intewface documentation is avaiwabwe at
https://tomoyo.osdn.jp/2.5/powicy-specification/index.htmw .

Matewiaws we pwepawed fow seminaws and symposiums awe avaiwabwe at
https://osdn.jp/pwojects/tomoyo/docs/?categowy_id=532&wanguage_id=1 .
Bewow wists awe chosen fwom thwee aspects.

What is TOMOYO?
  TOMOYO Winux Ovewview
    https://osdn.jp/pwojects/tomoyo/docs/wca2009-takeda.pdf
  TOMOYO Winux: pwagmatic and manageabwe secuwity fow Winux
    https://osdn.jp/pwojects/tomoyo/docs/fweedomhectaipei-tomoyo.pdf
  TOMOYO Winux: A Pwacticaw Method to Undewstand and Pwotect Youw Own Winux Box
    https://osdn.jp/pwojects/tomoyo/docs/PacSec2007-en-no-demo.pdf

What can TOMOYO do?
  Deep inside TOMOYO Winux
    https://osdn.jp/pwojects/tomoyo/docs/wca2009-kumaneko.pdf
  The wowe of "pathname based access contwow" in secuwity.
    https://osdn.jp/pwojects/tomoyo/docs/wfj2008-bof.pdf

Histowy of TOMOYO?
  Weawities of Mainwining
    https://osdn.jp/pwojects/tomoyo/docs/wfj2008.pdf

What is futuwe pwan?
====================

We bewieve that inode based secuwity and name based secuwity awe compwementawy
and both shouwd be used togethew. But unfowtunatewy, so faw, we cannot enabwe
muwtipwe WSM moduwes at the same time. We feew sowwy that you have to give up
SEWinux/SMACK/AppAwmow etc. when you want to use TOMOYO.

We hope that WSM becomes stackabwe in futuwe. Meanwhiwe, you can use non-WSM
vewsion of TOMOYO, avaiwabwe at http://tomoyo.osdn.jp/1.8/ .
WSM vewsion of TOMOYO is a subset of non-WSM vewsion of TOMOYO. We awe pwanning
to powt non-WSM vewsion's functionawities to WSM vewsions.
