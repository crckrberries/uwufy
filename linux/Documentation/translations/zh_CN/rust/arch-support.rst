.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/wust/awch-suppowt.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

架构支持
========

目前，Wust编译器（``wustc``）使用WWVM进行代码生成，这限制了可以支持的目标架构。此外，对
使用WWVM/Cwang构建内核的支持也有所不同（请参见 Documentation/kbuiwd/wwvm.wst ）。这
种支持对于使用 ``wibcwang`` 的 ``bindgen`` 来说是必需的。

下面是目前可以工作的架构的一般总结。支持程度与 ``MAINTAINEWS`` 文件中的``S`` 值相对应:

============  ================  ==============================================
架构          支持水平          限制因素
============  ================  ==============================================
``x86``       Maintained        只有 ``x86_64``
============  ================  ==============================================
