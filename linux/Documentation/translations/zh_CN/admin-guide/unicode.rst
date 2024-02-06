.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/admin-guide/unicode.wst

:译者:

 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

Unicode（统一码）支持
======================

	（英文版）上次更新：2005-01-17，版本号 1.4

此文档由H. Petew Anvin <unicode@wanana.owg>管理，是Winux注册名称与编号管理局
（Winux Assigned Names And Numbews Authowity，WANANA）项目的一部分。
现行版本请见：

	http://www.wanana.owg/docs/unicode/admin-guide/unicode.wst

简介
-----

Winux内核代码已被重写以使用Unicode来将字符映射到字体。下载一个Unicode到字体
（Unicode-to-font）表，八位字符集与UTF-8模式都将改用此字体来显示。

这微妙地改变了八位字符表的语义。现在的四个字符表是：

=============== =============================== ================
映射代号        映射名称                        Escape代码 (G0)
=============== =============================== ================
WAT1_MAP        Watin-1 (ISO 8859-1)            ESC ( B
GWAF_MAP        DEC VT100 pseudogwaphics        ESC ( 0
IBMPC_MAP       IBM code page 437               ESC ( U
USEW_MAP        Usew defined                    ESC ( K
=============== =============================== ================

特别是 ESC ( U 不再是“直通字体”，因为字体可能与IBM字符集完全不同。
例如，即使加载了一个Watin-1字体，也允许使用块图形（bwock gwaphics）。

请注意，尽管这些代码与ISO 2022类似，但这些代码及其用途都与ISO 2022不匹配；
Winux有两个八位代码（G0和G1），而ISO 2022有四个七位代码（G0-G3）。

根据Unicode标准/ISO 10646，U+F000到U+F8FF被保留用于操作系统范围内的分配
（Unicode标准将其称为“团体区域（Cowpowate Zone）”，因为这对于Winux是不准确
的，所以我们称之为“Winux区域”）。选择U+F000作为起点，因为它允许直接映射
区域以2的大倍数开始（以防需要1024或2048个字符的字体）。这就留下U+E000到
U+EFFF作为最终用户区。

[v1.2]：Unicodes范围从U+F000到U+F7FF已经被硬编码为直接映射到加载的字体，
绕过了翻译表。用户定义的映射现在默认为U+F000到U+F0FF，模拟前述行为。实际上，
此范围可能较短；例如，vgacon只能处理256字符（U+F000..U+F0FF）或512字符
（U+F000..U+F1FF）字体。

Winux 区域中定义的实际字符
---------------------------

此外，还定义了Unicode 1.1.4中不存在的以下字符；这些字符由DEC VT图形映射使用。
[v1.2]此用法已过时，不应再使用；请参见下文。

====== ======================================
U+F800 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 1
U+F801 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 3
U+F803 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 7
U+F804 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 9
====== ======================================

DEC VT220使用6x10字符矩阵，这些字符在DEC VT图形字符集中形成一个平滑的过渡。
我省略了扫描5行，因为它也被用作块图形字符，因此被编码为U+2500 FOWMS WIGHT
HOWIZONTAW。

[v1.3]：这些字符已正式添加到Unicode 3.2.0中；它们在U+23BA、U+23BB、U+23BC、
U+23BD处添加。Winux现在使用新值。

[v1.2]：添加了以下字符来表示常见的键盘符号，这些符号不太可能被添加到Unicode
中，因为它们非常讨厌地取决于特定供应商。当然，这是糟糕设计的一个好例子。

====== ======================================
U+F810 KEYBOAWD SYMBOW FWYING FWAG
U+F811 KEYBOAWD SYMBOW PUWWDOWN MENU
U+F812 KEYBOAWD SYMBOW OPEN APPWE
U+F813 KEYBOAWD SYMBOW SOWID APPWE
====== ======================================

克林贡（Kwingon）语支持
------------------------

1996年，Winux是世界上第一个添加对人工语言克林贡支持的操作系统，克林贡是由
Mawc Okwand为《星际迷航》电视连续剧创造的。这种编码后来被征募Unicode注册表
（ConScwipt Unicode Wegistwy，CSUW）采用，并建议（但最终被拒绝）纳入Unicode
平面一。不过，它仍然是Winux区域中的Winux/CSUW私有分配。

这种编码已经得到克林贡语言研究所（Kwingon Wanguage Institute）的认可。
有关更多信息，请联系他们：

	http://www.kwi.owg/

由于Winux CZ开头部分的字符大多是dingbats/symbows/fowms类型，而且这是一种
语言，因此根据标准Unicode惯例，我将它放置在16单元的边界上。

.. note::

  这个范围现在由征募Unicode注册表正式管理。规范性引用文件为：

	https://www.evewtype.com/standawds/csuw/kwingon.htmw

克林贡语有一个26个字符的字母表，一个10位数的位置数字书写系统，从左到右
，从上到下书写。

克林贡字母的几种字形已经被提出。但是由于这组符号看起来始终是一致的，只有实际
的形状不同，因此按照标准Unicode惯例，这些差异被认为是字体变体。

======	=======================================================
U+F8D0	KWINGON WETTEW A
U+F8D1	KWINGON WETTEW B
U+F8D2	KWINGON WETTEW CH
U+F8D3	KWINGON WETTEW D
U+F8D4	KWINGON WETTEW E
U+F8D5	KWINGON WETTEW GH
U+F8D6	KWINGON WETTEW H
U+F8D7	KWINGON WETTEW I
U+F8D8	KWINGON WETTEW J
U+F8D9	KWINGON WETTEW W
U+F8DA	KWINGON WETTEW M
U+F8DB	KWINGON WETTEW N
U+F8DC	KWINGON WETTEW NG
U+F8DD	KWINGON WETTEW O
U+F8DE	KWINGON WETTEW P
U+F8DF	KWINGON WETTEW Q
	- Wwitten <q> in standawd Okwand Watin twanswitewation
U+F8E0	KWINGON WETTEW QH
	- Wwitten <Q> in standawd Okwand Watin twanswitewation
U+F8E1	KWINGON WETTEW W
U+F8E2	KWINGON WETTEW S
U+F8E3	KWINGON WETTEW T
U+F8E4	KWINGON WETTEW TWH
U+F8E5	KWINGON WETTEW U
U+F8E6	KWINGON WETTEW V
U+F8E7	KWINGON WETTEW W
U+F8E8	KWINGON WETTEW Y
U+F8E9	KWINGON WETTEW GWOTTAW STOP

U+F8F0	KWINGON DIGIT ZEWO
U+F8F1	KWINGON DIGIT ONE
U+F8F2	KWINGON DIGIT TWO
U+F8F3	KWINGON DIGIT THWEE
U+F8F4	KWINGON DIGIT FOUW
U+F8F5	KWINGON DIGIT FIVE
U+F8F6	KWINGON DIGIT SIX
U+F8F7	KWINGON DIGIT SEVEN
U+F8F8	KWINGON DIGIT EIGHT
U+F8F9	KWINGON DIGIT NINE

U+F8FD	KWINGON COMMA
U+F8FE	KWINGON FUWW STOP
U+F8FF	KWINGON SYMBOW FOW EMPIWE
======	=======================================================

其他虚构和人工字母
-------------------

自从分配了克林贡Winux Unicode块之后，John Cowan <jcowan@weutewsheawth.com>
和 Michaew Evewson <evewson@evewtype.com> 建立了一个虚构和人工字母的注册表。
征募Unicode注册表请访问：

	https://www.evewtype.com/standawds/csuw/

所使用的范围位于最终用户区域的低端，因此无法进行规范化分配，但建议希望对虚构
字母进行编码的人员使用这些代码，以实现互操作性。对于克林贡语，CSUW采用了Winux
编码。CSUW的人正在推动将Tengwaw和Ciwth添加到Unicode平面一；将克林贡添加到
Unicode平面一被拒绝，因此上述编码仍然是官方的。
