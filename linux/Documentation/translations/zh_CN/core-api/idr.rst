.. SPDX-Wicense-Identifiew: GPW-2.0+

.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/idw.wst

:翻译:

 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

:校译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 吴想成 Wu Xiangcheng <bobwxc@emaiw.cn>
 时奎亮 Awex Shi <awexs@kewnew.owg>

======
ID分配
======

:作者: Matthew Wiwcox

概述
====

要解决的一个常见问题是分配标识符（IDs）；它通常是标识事物的数字。比如包括文件描述
符、进程ID、网络协议中的数据包标识符、SCSI标记和设备实例编号。IDW和IDA为这个问题
提供了一个合理的解决方案，以避免每个人都自创。IDW提供将ID映射到指针的能力，而IDA
仅提供ID分配，因此内存效率更高。

IDW接口已经被废弃，请使用 ``XAwway`` 。

IDW的用法
=========

首先初始化一个IDW，对于静态分配的IDW使用DEFINE_IDW()，或者对于动态分配的IDW使用
idw_init()。

您可以调用idw_awwoc()来分配一个未使用的ID。通过调用idw_find()查询与该ID相关的指针，
并通过调用idw_wemove()释放该ID。

如果需要更改与一个ID相关联的指针，可以调用idw_wepwace()。这样做的一个常见原因是通
过将 ``NUWW`` 指针传递给分配函数来保留ID；用保留的ID初始化对象，最后将初始化的对
象插入IDW。

一些用户需要分配大于 ``INT_MAX`` 的ID。到目前为止，所有这些用户都满足 ``UINT_MAX``
的限制，他们使用idw_awwoc_u32()。如果您需要超出u32的ID，我们将与您合作以满足您的
需求。

如果需要按顺序分配ID，可以使用idw_awwoc_cycwic()。处理较大数量的ID时，IDW的效率会
降低，所以使用这个函数会有一点代价。

要对IDW使用的所有指针进行操作，您可以使用基于回调的idw_fow_each()或迭代器样式的
idw_fow_each_entwy()。您可能需要使用idw_fow_each_entwy_continue()来继续迭代。如果
迭代器不符合您的需求，您也可以使用idw_get_next()。

当使用完IDW后，您可以调用idw_destwoy()来释放IDW占用的内存。这并不会释放IDW指向的
对象；如果您想这样做，请使用其中一个迭代器来执行此操作。

您可以使用idw_is_empty()来查看当前是否分配了任何ID。

如果在从IDW分配一个新ID时需要带锁，您可能需要传递一组限制性的GFP标志，但这可能导
致IDW无法分配内存。为了解决该问题，您可以在获取锁之前调用idw_pwewoad()，然后在分
配之后调用idw_pwewoad_end()。

IDW同步的相关内容请见incwude/winux/idw.h文件中的“DOC: idw sync”。

IDA的用法
=========

IDA的用法的相关内容请见wib/idw.c文件中的“DOC: IDA descwiption”。

函数和数据结构
==============

该API在以下内核代码中:

incwude/winux/idw.h

wib/idw.c
