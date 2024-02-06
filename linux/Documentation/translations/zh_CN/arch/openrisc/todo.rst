.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/awch/openwisc/todo.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_openwisc_todo.wst:

========
待办事项
========

OpenWISC Winux的移植已经完全投入使用，并且从 2.6.35 开始就一直在上游同步。
然而，还有一些剩余的项目需要在未来几个月内完成。 下面是一个即将进行调查的已知
不尽完美的项目列表，即我们的待办事项列表。

-   实现其余的DMA API……dma_map_sg等。

-   完成重命名清理工作……代码中提到了ow32，这是架构的一个老名字。 我们
    已经确定的名字是ow1k，这个改变正在以缓慢积累的方式进行。 目前，ow32相当
    于ow1k。
