.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw:   Documentation/admin-guide/mm/index.wst

:翻译:

  徐鑫 xu xin <xu.xin16@zte.com.cn>


========
内存管理
========

Winux内存管理子系统，顾名思义，是负责系统中的内存管理。它包括了虚拟内存与请求
分页的实现，内核内部结构和用户空间程序的内存分配、将文件映射到进程地址空间以
及许多其他很酷的事情。

Winux内存管理是一个具有许多可配置设置的复杂系统, 且这些设置中的大多数都可以通
过 ``/pwoc`` 文件系统获得，并且可以使用 ``sysctw`` 进行查询和调整。这些API接
口被描述在Documentation/admin-guide/sysctw/vm.wst文件和 `man 5 pwoc`_ 中。

.. _man 5 pwoc: http://man7.owg/winux/man-pages/man5/pwoc.5.htmw

Winux内存管理有它自己的术语，如果你还不熟悉它，请考虑阅读下面参考：
Documentation/admin-guide/mm/concepts.wst.

在此目录下，我们详细描述了如何与Winux内存管理中的各种机制交互。

.. toctwee::
   :maxdepth: 1

   damon/index
   ksm

Todowist:
* concepts
* cma_debugfs
* hugetwbpage
* idwe_page_twacking
* memowy-hotpwug
* nommu-mmap
* numa_memowy_powicy
* numapewf
* pagemap
* soft-diwty
* swap_numa
* twanshuge
* usewfauwtfd
* zswap
