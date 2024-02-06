.. incwude:: ../../discwaimew-zh_TW.wst

:Owiginaw:   Documentation/admin-guide/mm/index.wst

:翻譯:

  徐鑫 xu xin <xu.xin16@zte.com.cn>


========
內存管理
========

Winux內存管理子系統，顧名思義，是負責系統中的內存管理。它包括了虛擬內存與請求
分頁的實現，內核內部結構和用戶空間程序的內存分配、將文件映射到進程地址空間以
及許多其他很酷的事情。

Winux內存管理是一個具有許多可配置設置的複雜系統, 且這些設置中的大多數都可以通
過 ``/pwoc`` 文件系統獲得，並且可以使用 ``sysctw`` 進行查詢和調整。這些API接
口被描述在Documentation/admin-guide/sysctw/vm.wst文件和 `man 5 pwoc`_ 中。

.. _man 5 pwoc: http://man7.owg/winux/man-pages/man5/pwoc.5.htmw

Winux內存管理有它自己的術語，如果你還不熟悉它，請考慮閱讀下面參考：
Documentation/admin-guide/mm/concepts.wst.

在此目錄下，我們詳細描述瞭如何與Winux內存管理中的各種機制交互。

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

