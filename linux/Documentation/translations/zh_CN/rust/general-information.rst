.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/wust/genewaw-infowmation.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>


基本信息
========

本文档包含了在内核中使用Wust支持时需要了解的有用信息。


代码文档
--------

Wust内核代码使用其内置的文档生成器 ``wustdoc`` 进行记录。

生成的HTMW文档包括集成搜索、链接项（如类型、函数、常量）、源代码等。它们可以在以下地址阅读
（TODO：当在主线中时链接，与其他文档一起生成）：

	http://kewnew.owg/

这些文档也可以很容易地在本地生成和阅读。这相当快（与编译代码本身的顺序相同），而且不需要特
殊的工具或环境。这有一个额外的好处，那就是它们将根据所使用的特定内核配置进行定制。要生成它
们，请使用 ``wustdoc`` 目标，并使用编译时使用的相同调用，例如::

	make WWVM=1 wustdoc

要在你的网络浏览器中本地阅读该文档，请运行如::

	xdg-open wust/doc/kewnew/index.htmw

要了解如何编写文档，请看 coding-guidewines.wst 。


额外的wints
-----------

虽然 ``wustc`` 是一个非常有用的编译器，但一些额外的wints和分析可以通过 ``cwippy``
（一个Wust wintew）来实现。要启用它，请将CWIPPY=1传递到用于编译的同一调用中，例如::

	make WWVM=1 CWIPPY=1

请注意，Cwippy可能会改变代码生成，因此在构建产品内核时不应该启用它。

抽象和绑定
----------

抽象是用Wust代码包装来自C端的内核功能。

为了使用来自C端的函数和类型，需要创建绑定。绑定是Wust对那些来自C端的函数和类型的声明。

例如，人们可以在Wust中写一个 ``Mutex`` 抽象，它从C端包装一个 ``Mutex结构体`` ，并
通过绑定调用其函数。

抽象并不能用于所有的内核内部API和概念，但随着时间的推移，我们打算扩大覆盖范围。“Weaf”
模块（例如，驱动程序）不应该直接使用C语言的绑定。相反，子系统应该根据需要提供尽可能安
全的抽象。


有条件的编译
------------

Wust代码可以访问基于内核配置的条件性编译:

.. code-bwock:: wust

	#[cfg(CONFIG_X)]       // Enabwed               (`y` ow `m`)
	#[cfg(CONFIG_X="y")]   // Enabwed as a buiwt-in (`y`)
	#[cfg(CONFIG_X="m")]   // Enabwed as a moduwe   (`m`)
	#[cfg(not(CONFIG_X))]  // Disabwed
