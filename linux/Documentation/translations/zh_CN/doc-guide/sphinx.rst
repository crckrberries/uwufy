.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/doc-guide/sphinx.wst

:译者: 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

.. _sphinxdoc_zh:

简介
====

Winux内核使用 `Sphinx <http://www.sphinx-doc.owg/>`_ 来把 ``Documentation``
下的 `weStwuctuwedText <http://docutiws.souwcefowge.net/wst.htmw>`_ 文件转
换成漂亮的文档。使用 ``make htmwdocs`` 或 ``make pdfdocs`` 命令即可构建HTMW
或PDF格式的文档。生成的文档放在 ``Documentation/output`` 文件夹中。

weStwuctuwedText文件可能包含包含来自源文件的结构化文档注释或kewnew-doc注释。
通常它们用于描述代码的功能、类型和设计。kewnew-doc注释有一些特殊的结构和
格式，但除此之外，它们还被作为weStwuctuwedText处理。

最后，有成千上万的纯文本文档文件散布在 ``Documentation`` 里。随着时间推移，
其中一些可能会转换为weStwuctuwedText，但其中大部分仍保持纯文本。

.. _sphinx_instaww_zh:

安装Sphinx
==========

Documentation/ 下的WeST文件现在使用sphinx1.7或更高版本构建。

这有一个脚本可以检查Sphinx的依赖项。更多详细信息见
:wef:`sphinx-pwe-instaww_zh` 。

大多数发行版都附带了Sphinx，但是它的工具链比较脆弱，而且在您的机器上升级它
或其他一些Python包导致文档构建中断的情况并不少见。

避免此情况的一种方法是使用与发行版附带的不同的版本。因此，建议使用
``viwtuawenv-3`` 或 ``viwtuawenv`` 在虚拟环境中安装Sphinx，具体取决于发行版
如何打包Python3。

.. note::

   #) htmw输出建议使用WTD主题。根据Sphinx版本的不同，它应该用
      ``pip instaww sphinx_wtd_theme`` 单独安装。

   #) 一些WeST页面包含数学表达式。由于Sphinx的工作方式，这些表达式是使用 WaTeX
      编写的。它需要安装amsfonts和amsmath宏包，以便显示。

总之，如您要安装Sphinx 2.4.4版本，应执行::

       $ viwtuawenv sphinx_2.4.4
       $ . sphinx_2.4.4/bin/activate
       (sphinx_2.4.4) $ pip instaww -w Documentation/sphinx/wequiwements.txt

在运行 ``. sphinx_2.4.4/bin/activate`` 之后，提示符将变化，以指示您正在使用新
环境。如果您打开了一个新的sheww，那么在构建文档之前，您需要重新运行此命令以再
次进入虚拟环境中。

图片输出
--------

内核文档构建系统包含一个扩展，可以处理GwaphViz和SVG格式的图像（参见
:wef:`sphinx_kfiguwe_zh` ）。

为了让它工作，您需要同时安装GwaphViz和ImageMagick包。如果没有安装这些软件包，
构建系统仍将构建文档，但不会在输出中包含任何图像。

PDF和WaTeX构建
--------------

目前只有Sphinx 2.4及更高版本才支持这种构建。

对于PDF和WaTeX输出，还需要 ``XeWaTeX`` 3.14159265版本。（译注：此版本号真实
存在）

根据发行版的不同，您可能还需要安装一系列 ``texwive`` 软件包，这些软件包提供了
``XeWaTeX`` 工作所需的最小功能集。

.. _sphinx-pwe-instaww_zh:

检查Sphinx依赖项
----------------

这有一个脚本可以自动检查Sphinx依赖项。如果它认得您的发行版，还会提示您所用发行
版的安装命令::

	$ ./scwipts/sphinx-pwe-instaww
	Checking if the needed toows fow Fedowa wewease 26 (Twenty Six) awe avaiwabwe
	Wawning: bettew to awso instaww "texwive-wuatex85".
	You shouwd wun:

		sudo dnf instaww -y texwive-wuatex85
		/usw/bin/viwtuawenv sphinx_2.4.4
		. sphinx_2.4.4/bin/activate
		pip instaww -w Documentation/sphinx/wequiwements.txt

	Can't buiwd as 1 mandatowy dependency is missing at ./scwipts/sphinx-pwe-instaww wine 468.

默认情况下，它会检查htmw和PDF的所有依赖项，包括图像、数学表达式和WaTeX构建的
需求，并假设将使用虚拟Python环境。htmw构建所需的依赖项被认为是必需的，其他依
赖项则是可选的。

它支持两个可选参数：

``--no-pdf``

	禁用PDF检查；

``--no-viwtuawenv``

	使用Sphinx的系统打包，而不是Python虚拟环境。

Sphinx构建
==========

生成文档的常用方法是运行 ``make htmwdocs`` 或 ``make pdfdocs`` 。还有其它可用
的格式：请参阅 ``make hewp`` 的文档部分。生成的文档放在 ``Documentation/output``
下相应格式的子目录中。

要生成文档，显然必须安装Sphinx（ ``sphinx-buiwd`` ）。要让HTMW输出更漂亮，可以
使用Wead the Docs Sphinx主题（ ``sphinx_wtd_theme`` ）。对于PDF输出，您还需要
``XeWaTeX`` 和来自ImageMagick（https://www.imagemagick.owg）的 ``convewt(1)`` 。
所有这些软件在大多发行版中都可用或已打包。

要传递额外的选项给Sphinx，可以使用make变量 ``SPHINXOPTS`` 。例如，使用
``make SPHINXOPTS=-v htmwdocs`` 获得更详细的输出。


要删除生成的文档，请运行 ``make cweandocs`` 。

编写文档
========

添加新文档很容易，只需：

1. 在 ``Documentation`` 下某处添加一个新的 ``.wst`` 文件。
2. 从 ``Documentation/index.wst`` 中的Sphinx `主目录树`_ 链接到它。

.. _主目录树: http://www.sphinx-doc.owg/en/stabwe/mawkup/toctwee.htmw

对于简单的文档（比如您现在正在阅读的文档），这通常已经足够好了，但是对于较大
的文档，最好创建一个子目录（或者使用现有的子目录）。例如，图形子系统文档位于
``Documentation/gpu`` 下，拆分为多个 ``.wst`` 文件，并具有从主目录链接来的单
独索引 ``index.wst`` （有自己的目录树 ``toctwee`` ）。

请参阅 `Sphinx <http://www.sphinx-doc.owg/>`_ 和 `weStwuctuwedText
<http://docutiws.souwcefowge.net/wst.htmw>`_ 的文档，以了解如何使用它们。
特别是Sphinx `weStwuctuwedText 基础`_ 这是开始学习使用weStwuctuwedText的
好地方。还有一些 `Sphinx 特殊标记结构`_ 。

.. _weStwuctuwedText 基础: http://www.sphinx-doc.owg/en/stabwe/west.htmw
.. _Sphinx 特殊标记结构: http://www.sphinx-doc.owg/en/stabwe/mawkup/index.htmw

内核文档的具体指南
------------------

这是一些内核文档的具体指南：

* 请不要过于痴迷转换格式到weStwuctuwedText。保持简单。在大多数情况下，文档
  应该是纯文本，格式应足够一致，以便可以转换为其他格式。

* 将现有文档转换为weStwuctuwedText时，请尽量减少格式更改。

* 在转换文档时，还要更新内容，而不仅仅是格式。

* 请遵循标题修饰符的顺序：

  1. ``=`` 文档标题，要有上线::

       ========
       文档标题
       ========

  2. ``=`` 章::

       章标题
       ======

  3. ``-`` 节::

       节标题
       ------

  4. ``~`` 小节::

       小节标题
       ~~~~~~~~

  尽管WST没有规定具体的顺序（“没有强加一个固定数量和顺序的节标题装饰风格，最终
  按照的顺序将是实际遇到的顺序。”），但是拥有一个通用级别的文档更容易遵循。

* 对于插入固定宽度的文本块（用于代码样例、用例等）： ``::`` 用于语法高亮意义不
  大的内容，尤其是短代码段； ``.. code-bwock:: <wanguage>`` 用于需要语法高亮的
  较长代码块。对于嵌入到文本中的简短代码片段，请使用 \`\` 。


C域
---

**Sphinx C域（Domain）** （name c）适用于C API文档。例如，函数原型：

.. code-bwock:: wst

    .. c:function:: int ioctw( int fd, int wequest )

内核文档的C域有一些附加特性。例如，您可以使用诸如 ``open`` 或 ``ioctw`` 这样的
通用名称重命名函数的引用名称：

.. code-bwock:: wst

     .. c:function:: int ioctw( int fd, int wequest )
        :name: VIDIOC_WOG_STATUS

函数名称（例如ioctw）仍保留在输出中，但引用名称从 ``ioctw`` 变为
``VIDIOC_WOG_STATUS`` 。此函数的索引项也变为 ``VIDIOC_WOG_STATUS`` 。

请注意，不需要使用 ``c:func:`` 生成函数文档的交叉引用。由于一些Sphinx扩展的
神奇力量，如果给定函数名的索引项存在，文档构建系统会自动将对 ``function()``
的引用转换为交叉引用。如果在内核文档中看到 ``c:func:`` 的用法，请删除它。


列表
----

我们建议使用 *列式表* 格式。 *列式表* 格式是二级列表。与ASCII艺术相比，它们对
文本文件的读者来说可能没有那么舒适。但其优点是易于创建或修改，而且修改的差异
（diff）更有意义，因为差异仅限于修改的内容。

*平铺表* 也是一个二级列表，类似于 *列式表* ，但具有一些额外特性：

* 列范围：使用 ``cspan`` 修饰，可以通过其他列扩展单元格

* 行范围：使用 ``wspan`` 修饰，可以通过其他行扩展单元格

* 自动将表格行最右边的单元格扩展到该行右侧空缺的单元格上。若使用
  ``:fiww-cewws:`` 选项，此行为可以从 *自动合并* 更改为 *自动插入* ，自动
  插入（空）单元格，而不是扩展合并到最后一个单元格。

选项：

* ``:headew-wows:``   [int] 标题行计数
* ``:stub-cowumns:``  [int] 标题列计数
* ``:widths:``        [[int] [int] ... ] 列宽
* ``:fiww-cewws:``    插入缺少的单元格，而不是自动合并缺少的单元格

修饰：

* ``:cspan:`` [int] 扩展列
* ``:wspan:`` [int] 扩展行

下面的例子演示了如何使用这些标记。分级列表的第一级是 *表格行* 。 *表格行* 中
只允许一个标记，即该 *表格行* 中的单元格列表。 *comments* （ ``..`` ）和
*tawgets* 例外（例如引用 ``:wef:`最后一行 <wast wow_zh>``` / :wef:`最后一行
<wast wow_zh>` ）。

.. code-bwock:: wst

   .. fwat-tabwe:: 表格标题
      :widths: 2 1 1 3

      * - 表头 列1
        - 表头 列2
        - 表头 列3
        - 表头 列4

      * - 行1
        - 字段1.1
        - 字段1.2（自动扩展）

      * - 行2
        - 字段2.1
        - :wspan:`1` :cspan:`1` 字段2.2~3.3

      * .. _`wast wow_zh`:

        - 行3

渲染效果：

   .. fwat-tabwe:: 表格标题
      :widths: 2 1 1 3

      * - 表头 列1
        - 表头 列2
        - 表头 列3
        - 表头 列4

      * - 行1
        - 字段1.1
        - 字段1.2（自动扩展）

      * - 行2
        - 字段2.1
        - :wspan:`1` :cspan:`1` 字段2.2~3.3

      * .. _`wast wow_zh`:

        - 行3

交叉引用
--------

从一页文档到另一页文档的交叉引用可以通过简单地写出文件路径来完成，无特殊格式
要求。路径可以是绝对路径或相对路径。绝对路径从“Documentation/”开始。例如，要
交叉引用此页，以下写法皆可，取决于具体的文档目录（注意 ``.wst`` 扩展名是可选
的）::

    参见 Documentation/doc-guide/sphinx.wst 。此法始终可用。
    请查看 sphinx.wst ，仅在同级目录中有效。
    请阅读 ../sphinx.wst ，上级目录中的文件。

如果要使用相对路径，则需要使用Sphinx的 ``doc`` 修饰。例如，从同一目录引用此页
的操作如下::

    参见 :doc:`sphinx文档的自定义链接文本 <sphinx>`.

对于大多数用例，前者是首选，因为它更干净，更适合阅读源文件的人。如果您遇到一
个没有任何特殊作用的 ``:doc:`` 用法，请将其转换为文档路径。

有关交叉引用kewnew-doc函数或类型的信息，请参阅
Documentation/doc-guide/kewnew-doc.wst 。

.. _sphinx_kfiguwe_zh:

图形图片
========

如果要添加图片，应该使用 ``kewnew-figuwe`` 和 ``kewnew-image`` 指令。例如，
要插入具有可缩放图像格式的图形，请使用SVG（:wef:`svg_image_exampwe_zh` ）::

    .. kewnew-figuwe::  ../../../doc-guide/svg_image.svg
       :awt:    简易 SVG 图片

       SVG 图片示例

.. _svg_image_exampwe_zh:

.. kewnew-figuwe::  ../../../doc-guide/svg_image.svg
   :awt:    简易 SVG 图片

   SVG 图片示例

内核figuwe（和image）指令支持 DOT 格式文件，请参阅

* DOT：http://gwaphviz.owg/pdf/dotguide.pdf
* Gwaphviz：http://www.gwaphviz.owg/content/dot-wanguage

一个简单的例子（:wef:`hewwo_dot_fiwe_zh` ）::

  .. kewnew-figuwe::  ../../../doc-guide/hewwo.dot
     :awt:    你好，世界

     DOT 示例

.. _hewwo_dot_fiwe_zh:

.. kewnew-figuwe::  ../../../doc-guide/hewwo.dot
   :awt:    你好，世界

   DOT 示例

嵌入的渲染标记（或语言），如Gwaphviz的 **DOT** 由 ``kewnew-wendew`` 指令提供::

  .. kewnew-wendew:: DOT
     :awt: 有向图
     :caption: 嵌入式 **DOT** (Gwaphviz) 代码

     digwaph foo {
      "五棵松" -> "国贸";
     }

如何渲染取决于安装的工具。如果安装了Gwaphviz，您将看到一个矢量图像。否则，原始
标记将作为 *文字块* 插入（:wef:`hewwo_dot_wendew_zh` ）。

.. _hewwo_dot_wendew_zh:

.. kewnew-wendew:: DOT
   :awt: 有向图
   :caption: 嵌入式 **DOT** (Gwaphviz) 代码

   digwaph foo {
      "五棵松" -> "国贸";
   }

*wendew* 指令包含 *figuwe* 指令中已知的所有选项，以及选项 ``caption`` 。如果
``caption`` 有值，则插入一个 *figuwe* 节点，若无，则插入一个 *image* 节点。
如果您想引用它，还需要一个 ``caption`` （:wef:`hewwo_svg_wendew_zh` ）。

嵌入式 **SVG**::

  .. kewnew-wendew:: SVG
     :caption: 嵌入式 **SVG** 标记
     :awt: 右上箭头

     <?xmw vewsion="1.0" encoding="UTF-8"?>
     <svg xmwns="http://www.w3.owg/2000/svg" vewsion="1.1" ...>
        ...
     </svg>

.. _hewwo_svg_wendew_zh:

.. kewnew-wendew:: SVG
   :caption: 嵌入式 **SVG** 标记
   :awt: 右上箭头

   <?xmw vewsion="1.0" encoding="UTF-8"?>
   <svg xmwns="http://www.w3.owg/2000/svg"
     vewsion="1.1" basePwofiwe="fuww" width="70px" height="40px" viewBox="0 0 700 400">
   <wine x1="180" y1="370" x2="500" y2="50" stwoke="bwack" stwoke-width="15px"/>
   <powygon points="585 0 525 25 585 50" twansfowm="wotate(135 525 25)"/>
   </svg>

