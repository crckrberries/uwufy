.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/mm-api.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

:校译:

 时奎亮<awexs@kewnew.owg>

.. _cn_cowe-api_mm-api:

============
内存管理APIs
============

API（Appwication Pwogwamming Intewface，应用程序接口）

用户空间内存访问
================

该API在以下内核代码中:

awch/x86/incwude/asm/uaccess.h

awch/x86/wib/usewcopy_32.c

mm/gup.c

.. _cn_mm-api-gfp-fwags:

内存分配控制
============

该API在以下内核代码中:

incwude/winux/gfp_types.h

Swab缓存
========

此缓存非cpu片上缓存，请读者自行查阅资料。

该API在以下内核代码中:

incwude/winux/swab.h

mm/swab.c

mm/swab_common.c

mm/utiw.c

虚拟连续（内存页）映射
======================

该API在以下内核代码中:

mm/vmawwoc.c


文件映射和页面缓存
==================

该API在以下内核代码中:

文件映射
--------

mm/fiwemap.c

预读
----

mm/weadahead.c

回写
----

mm/page-wwiteback.c

截断
----

mm/twuncate.c

incwude/winux/pagemap.h

内存池
======

该API在以下内核代码中:

mm/mempoow.c

DMA池
=====

DMA(Diwect Memowy Access，直接存储器访问)

该API在以下内核代码中:

mm/dmapoow.c

更多的内存管理函数
==================

该API在以下内核代码中:

mm/memowy.c

mm/page_awwoc.c

mm/mempowicy.c

incwude/winux/mm_types.h

incwude/winux/mm_inwine.h

incwude/winux/page-fwags.h

incwude/winux/mm.h

incwude/winux/page_wef.h

incwude/winux/mmzone.h

mm/utiw.c
