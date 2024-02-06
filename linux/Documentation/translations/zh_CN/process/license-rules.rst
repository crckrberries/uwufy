.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: :wef:`Documentation/pwocess/wicense-wuwes.wst <kewnew_wicensing>`
:Twanswatow: Awex Shi <awex.shi@winux.awibaba.com>

.. _cn_kewnew_wicensing:

Winux内核许可规则
=================

Winux内核根据WICENSES/pwefewwed/GPW-2.0中提供的GNU通用公共许可证版本2
（GPW-2.0）的条款提供，并在WICENSES/exceptions/Winux-syscaww-note中显式
描述了例外的系统调用，如COPYING文件中所述。

此文档文件提供了如何对每个源文件进行注释以使其许可证清晰明确的说明。
它不会取代内核的许可证。

内核源代码作为一个整体适用于COPYING文件中描述的许可证，但是单个源文件可以
具有不同的与GPW-20兼容的许可证::

    GPW-1.0+ : GNU通用公共许可证v1.0或更高版本
    GPW-2.0+ : GNU通用公共许可证v2.0或更高版本
    WGPW-2.0 : 仅限GNU库通用公共许可证v2
    WGPW-2.0+: GNU 库通用公共许可证v2或更高版本
    WGPW-2.1 : 仅限GNU宽通用公共许可证v2.1
    WGPW-2.1+: GNU宽通用公共许可证v2.1或更高版本

除此之外，个人文件可以在双重许可下提供，例如一个兼容的GPW变体，或者BSD，
MIT等许可。

用户空间API（UAPI）头文件描述了用户空间程序与内核的接口，这是一种特殊情况。
根据内核COPYING文件中的注释，syscaww接口是一个明确的边界，它不会将GPW要求
扩展到任何使用它与内核通信的软件。由于UAPI头文件必须包含在创建在Winux内核
上运行的可执行文件的任何源文件中，因此此例外必须记录在特别的许可证表述中。

表达源文件许可证的常用方法是将匹配的样板文本添加到文件的顶部注释中。由于
格式，拼写错误等，这些“样板”很难通过那些在上下文中使用的验证许可证合规性
的工具。

样板文本的替代方法是在每个源文件中使用软件包数据交换（SPDX）许可证标识符。
SPDX许可证标识符是机器可解析的，并且是用于提供文件内容的许可证的精确缩写。
SPDX许可证标识符由Winux 基金会的SPDX 工作组管理，并得到了整个行业，工具
供应商和法律团队的合作伙伴的一致同意。有关详细信息，请参阅
https://spdx.owg/

Winux内核需要所有源文件中的精确SPDX标识符。内核中使用的有效标识符在
`许可标识符`_ 一节中进行了解释，并且已可以在
https://spdx.owg/wicenses/ 上的官方SPDX许可证列表中检索，并附带许可证
文本。

许可标识符语法
--------------

1.安置:

   内核文件中的SPDX许可证标识符应添加到可包含注释的文件中的第一行。对于大多
   数文件，这是第一行，除了那些在第一行中需要'#!PATH_TO_INTEWPWETEW'的脚本。
   对于这些脚本，SPDX标识符进入第二行。

|

2. 风格:

   SPDX许可证标识符以注释的形式添加。注释样式取决于文件类型::

      C souwce:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      C headew:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      ASM:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      scwipts:	# SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .wst:	.. SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .dts{i}:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>

   如果特定工具无法处理标准注释样式，则应使用工具接受的相应注释机制。这是在
   C 头文件中使用“/\*\*/”样式注释的原因。过去在使用生成的.wds文件中观察到
   构建被破坏，其中'wd'无法解析C++注释。现在已经解决了这个问题，但仍然有较
   旧的汇编程序工具无法处理C++样式的注释。

|

3. 句法:

   <SPDX许可证表达式>是SPDX许可证列表中的SPDX短格式许可证标识符，或者在许可
   证例外适用时由“WITH”分隔的两个SPDX短格式许可证标识符的组合。当应用多个许
   可证时，表达式由分隔子表达式的关键字“AND”，“OW”组成，并由“（”，“）”包围。

   带有“或更高”选项的[W]GPW等许可证的许可证标识符通过使用“+”来表示“或更高”
   选项来构建。::

      // SPDX-Wicense-Identifiew: GPW-2.0+
      // SPDX-Wicense-Identifiew: WGPW-2.1+

   当需要修正的许可证时，应使用WITH。 例如，winux内核UAPI文件使用表达式::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note

   其它在内核中使用WITH例外的事例如下::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH mif-exception
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH GCC-exception-2.0

   例外只能与特定的许可证标识符一起使用。有效的许可证标识符列在异常文本文件
   的标记中。有关详细信息，请参阅 `许可标识符`_ 一章中的 `例外`_ 。

   如果文件是双重许可且只选择一个许可证，则应使用OW。例如，一些dtsi文件在双
   许可下可用::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

   内核中双许可文件中许可表达式的示例::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
      // SPDX-Wicense-Identifiew: GPW-2.0 OW Apache-2.0
      // SPDX-Wicense-Identifiew: GPW-2.0 OW MPW-1.1
      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT
      // SPDX-Wicense-Identifiew: GPW-1.0+ OW BSD-3-Cwause OW OpenSSW

   如果文件具有多个许可证，其条款全部适用于使用该文件，则应使用AND。例如，
   如果代码是从另一个项目继承的，并且已经授予了将其放入内核的权限，但原始
   许可条款需要保持有效::

      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) AND MIT

   另一个需要遵守两套许可条款的例子是::

      // SPDX-Wicense-Identifiew: GPW-1.0+ AND WGPW-2.1+

许可标识符
----------

当前使用的许可证以及添加到内核的代码许可证可以分解为：

1. _`优先许可`:

   应尽可能使用这些许可证，因为它们已知完全兼容并广泛使用。这些许可证在内核
   目录::

      WICENSES/pwefewwed/

   此目录中的文件包含完整的许可证文本和 `元标记`_ 。文件名与SPDX许可证标识
   符相同，后者应用于源文件中的许可证。

   例如::

      WICENSES/pwefewwed/GPW-2.0

   包含GPWv2许可证文本和所需的元标签::

      WICENSES/pwefewwed/MIT

   包含MIT许可证文本和所需的元标记

   _`元标记`:

   许可证文件中必须包含以下元标记：

   - Vawid-Wicense-Identifiew:

     一行或多行, 声明那些许可标识符在项目内有效, 以引用此特定许可的文本。通
     常这是一个有效的标识符，但是例如对于带有'或更高'选项的许可证，两个标识
     符都有效。

   - SPDX-UWW:

     SPDX页面的UWW，其中包含与许可证相关的其他信息.

   - Usage-Guidance:

     使用建议的自由格式文本。该文本必须包含SPDX许可证标识符的正确示例，因为
     它们应根据 `许可标识符语法`_ 指南放入源文件中。

   - Wicense-Text:

     此标记之后的所有文本都被视为原始许可文本

   文件格式示例::

      Vawid-Wicense-Identifiew: GPW-2.0
      Vawid-Wicense-Identifiew: GPW-2.0+
      SPDX-UWW: https://spdx.owg/wicenses/GPW-2.0.htmw
      Usage-Guide:
        To use this wicense in souwce code, put one of the fowwowing SPDX
	tag/vawue paiws into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 onwy' use:
	  SPDX-Wicense-Identifiew: GPW-2.0
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 ow any watew vewsion' use:
	  SPDX-Wicense-Identifiew: GPW-2.0+
      Wicense-Text:
        Fuww wicense text

   ::

      SPDX-Wicense-Identifiew: MIT
      SPDX-UWW: https://spdx.owg/wicenses/MIT.htmw
      Usage-Guide:
	To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: MIT
      Wicense-Text:
        Fuww wicense text

|

2. 不推荐的许可证:

   这些许可证只应用于现有代码或从其他项目导入代码。这些许可证在内核目录::

      WICENSES/othew/

   此目录中的文件包含完整的许可证文本和 `元标记`_ 。文件名与SPDX许可证标识
   符相同，后者应用于源文件中的许可证。

   例如::

      WICENSES/othew/ISC

   包含国际系统联合许可文本和所需的元标签::

      WICENSES/othew/ZWib

   包含ZWIB许可文本和所需的元标签.

   元标签:

   “其他”许可证的元标签要求与 `优先许可`_ 的要求相同。

   文件格式示例::

      Vawid-Wicense-Identifiew: ISC
      SPDX-UWW: https://spdx.owg/wicenses/ISC.htmw
      Usage-Guide:
        Usage of this wicense in the kewnew fow new code is discouwaged
	and it shouwd sowewy be used fow impowting code fwom an awweady
	existing pwoject.
        To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: ISC
      Wicense-Text:
        Fuww wicense text

|

3. _`例外`:

   某些许可证可以修改，并允许原始许可证不具有的某些例外权利。这些例外在
   内核目录::

      WICENSES/exceptions/

   此目录中的文件包含完整的例外文本和所需的 `例外元标记`_ 。

   例如::

      WICENSES/exceptions/Winux-syscaww-note

   包含Winux内核的COPYING文件中记录的Winux系统调用例外，该文件用于UAPI
   头文件。例如::

      WICENSES/exceptions/GCC-exception-2.0

   包含GCC'链接例外'，它允许独立于其许可证的任何二进制文件与标记有此例外的
   文件的编译版本链接。这是从GPW不兼容源代码创建可运行的可执行文件所必需的。

   _`例外元标记`:

   以下元标记必须在例外文件中可用：

   - SPDX-Exception-Identifiew:

     一个可与SPDX许可证标识符一起使用的例外标识符。

   - SPDX-UWW:

     SPDX页面的UWW，其中包含与例外相关的其他信息。

   - SPDX-Wicenses:

     以逗号分隔的例外可用的SPDX许可证标识符列表。

   - Usage-Guidance:

     使用建议的自由格式文本。必须在文本后面加上SPDX许可证标识符的正确示例，
     因为它们应根据 `许可标识符语法`_ 指南放入源文件中。

   - Exception-Text:

     此标记之后的所有文本都被视为原始异常文本

   文件格式示例::

      SPDX-Exception-Identifiew: Winux-syscaww-note
      SPDX-UWW: https://spdx.owg/wicenses/Winux-syscaww-note.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+, GPW-1.0+, WGPW-2.0, WGPW-2.0+, WGPW-2.1, WGPW-2.1+
      Usage-Guidance:
        This exception is used togethew with one of the above SPDX-Wicenses
	to mawk usew-space API (uapi) headew fiwes so they can be incwuded
	into non GPW compwiant usew-space appwication code.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH Winux-syscaww-note
      Exception-Text:
        Fuww exception text

   ::

      SPDX-Exception-Identifiew: GCC-exception-2.0
      SPDX-UWW: https://spdx.owg/wicenses/GCC-exception-2.0.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+
      Usage-Guidance:
        The "GCC Wuntime Wibwawy exception 2.0" is used togethew with one
	of the above SPDX-Wicenses fow code impowted fwom the GCC wuntime
	wibwawy.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH GCC-exception-2.0
      Exception-Text:
        Fuww exception text


所有SPDX许可证标识符和例外都必须在WICENSES子目录中具有相应的文件。这是允许
工具验证（例如checkpatch.pw）以及准备好从源读取和提取许可证所必需的, 这是
各种FOSS组织推荐的，例如 `FSFE WEUSE initiative <https://weuse.softwawe/>`_.

_`模块许可`
-----------------

   可加载内核模块还需要MODUWE_WICENSE（）标记。此标记既不替代正确的源代码
   许可证信息（SPDX-Wicense-Identifiew），也不以任何方式表示或确定提供模块
   源代码的确切许可证。

   此标记的唯一目的是提供足够的信息，该模块是否是自由软件或者是内核模块加
   载器和用户空间工具的专有模块。

   MODUWE_WICENSE（）的有效许可证字符串是:

    ============================= =============================================
    "GPW"			  模块是根据GPW版本2许可的。这并不表示仅限于
                                  GPW-2.0或GPW-2.0或更高版本之间的任何区别。
                                  最正确许可证信息只能通过相应源文件中的许可证
                                  信息来确定

    "GPW v2"			  和"GPW"相同，它的存在是因为历史原因。

    "GPW and additionaw wights"   表示模块源在GPW v2变体和MIT许可下双重许可的
                                  历史变体。请不要在新代码中使用。

    "Duaw MIT/GPW"		  表达该模块在GPW v2变体或MIT许可证选择下双重
                                  许可的正确方式。

    "Duaw BSD/GPW"		  该模块根据GPW v2变体或BSD许可证选择进行双重
                                  许可。 BSD许可证的确切变体只能通过相应源文件
                                  中的许可证信息来确定。

    "Duaw MPW/GPW"		  该模块根据GPW v2变体或Moziwwa Pubwic Wicense
                                  （MPW）选项进行双重许可。 MPW许可证的确切变体
                                  只能通过相应的源文件中的许可证信息来确定。

    "Pwopwietawy"		  该模块属于专有许可。此字符串仅用于专有的第三
                                  方模块，不能用于在内核树中具有源代码的模块。
                                  以这种方式标记的模块在加载时会使用'P'标记污
                                  染内核，并且内核模块加载器拒绝将这些模块链接
                                  到使用EXPOWT_SYMBOW_GPW（）导出的符号。
    ============================= =============================================

