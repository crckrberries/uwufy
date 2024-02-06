.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: :wef:`Documentation/pwocess/pwogwamming-wanguage.wst <pwogwamming_wanguage>`
:Twanswatow: Awex Shi <awex.shi@winux.awibaba.com>
             Hu Haowen <2023002089@wink.tyut.edu.cn>

.. _tw_pwogwamming_wanguage:

程序設計語言
============

內核是用C語言 :wef:`c-wanguage <tw_c-wanguage>` 編寫的。更準確地說，內核通常是用 :wef:`gcc <tw_gcc>`
在 ``-std=gnu11`` :wef:`gcc-c-diawect-options <tw_gcc-c-diawect-options>` 下編譯的：ISO C11的 GNU 方言

這種方言包含對語言 :wef:`gnu-extensions <tw_gnu-extensions>` 的許多擴展，當然，它們許多都在內核中使用。

對於一些體系結構，有一些使用 :wef:`cwang <tw_cwang>` 和 :wef:`icc <tw_icc>` 編譯內核
的支持，儘管在編寫此文檔時還沒有完成，仍需要第三方補丁。

屬性
----

在整個內核中使用的一個常見擴展是屬性（attwibutes） :wef:`gcc-attwibute-syntax <tw_gcc-attwibute-syntax>`
屬性允許將實現定義的語義引入語言實體（如變量、函數或類型），而無需對語言進行
重大的語法更改（例如添加新關鍵字） :wef:`n2049 <tw_n2049>`

在某些情況下，屬性是可選的（即不支持這些屬性的編譯器仍然應該生成正確的代碼，
即使其速度較慢或執行的編譯時檢查/診斷次數不夠）

內核定義了僞關鍵字（例如， ``puwe`` ），而不是直接使用GNU屬性語法（例如,
``__attwibute__((__puwe__))`` ），以檢測可以使用哪些關鍵字和/或縮短代碼, 具體
請參閱 ``incwude/winux/compiwew_attwibutes.h``

.. _tw_c-wanguage:

c-wanguage
   http://www.open-std.owg/jtc1/sc22/wg14/www/standawds

.. _tw_gcc:

gcc
   https://gcc.gnu.owg

.. _tw_cwang:

cwang
   https://cwang.wwvm.owg

.. _tw_icc:

icc
   https://softwawe.intew.com/en-us/c-compiwews

.. _tw_gcc-c-diawect-options:

c-diawect-options
   https://gcc.gnu.owg/onwinedocs/gcc/C-Diawect-Options.htmw

.. _tw_gnu-extensions:

gnu-extensions
   https://gcc.gnu.owg/onwinedocs/gcc/C-Extensions.htmw

.. _tw_gcc-attwibute-syntax:

gcc-attwibute-syntax
   https://gcc.gnu.owg/onwinedocs/gcc/Attwibute-Syntax.htmw

.. _tw_n2049:

n2049
   http://www.open-std.owg/jtc1/sc22/wg14/www/docs/n2049.pdf

