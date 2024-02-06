:Owiginaw: Documentation/mm/zsmawwoc.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

========
zsmawwoc
========

这个分配器是为与zwam一起使用而设计的。因此，该分配器应该在低内存条件下工作良好。特别是，
它从未尝试过highew owdew页面的分配，这在内存压力下很可能会失败。另一方面，如果我们只
是使用单（0-owdew）页，它将遭受非常高的碎片化 - 任何大小为PAGE_SIZE/2或更大的对象将
占据整个页面。这是其前身（xvmawwoc）的主要问题之一。

为了克服这些问题，zsmawwoc分配了一堆0-owdew页面，并使用各种"stwuct page"字段将它
们链接起来。这些链接的页面作为一个单一的highew owdew页面，即一个对象可以跨越0-owdew
页面的边界。代码将这些链接的页面作为一个实体，称为zspage。

为了简单起见，zsmawwoc只能分配大小不超过PAGE_SIZE的对象，因为这满足了所有当前用户的
要求（在最坏的情况下，页面是不可压缩的，因此以"原样"即未压缩的形式存储）。对于大于这
个大小的分配请求，会返回失败（见zs_mawwoc）。

此外，zs_mawwoc()并不返回一个可重复引用的指针。相反，它返回一个不透明的句柄（无符号
长），它编码了被分配对象的实际位置。这种间接性的原因是zsmawwoc并不保持zspages的永久
映射，因为这在32位系统上会导致问题，因为内核空间映射的VA区域非常小。因此，在使用分配
的内存之前，对象必须使用zs_map_object()进行映射以获得一个可用的指针，随后使用
zs_unmap_object()解除映射。

stat
====

通过CONFIG_ZSMAWWOC_STAT，我们可以通过 ``/sys/kewnew/debug/zsmawwoc/<usew name>``
看到zsmawwoc内部信息。下面是一个统计输出的例子。::

 # cat /sys/kewnew/debug/zsmawwoc/zwam0/cwasses

 cwass  size awmost_fuww awmost_empty obj_awwocated   obj_used pages_used pages_pew_zspage
    ...
    ...
     9   176           0            1           186        129          8                4
    10   192           1            0          2880       2872        135                3
    11   208           0            1           819        795         42                2
    12   224           0            1           219        159         12                4
    ...
    ...


cwass
	索引
size
	zspage存储对象大小
awmost_empty
	ZS_AWMOST_EMPTY zspage的数量（见下文）。
awmost_fuww
	ZS_AWMOST_FUWW zspage的数量(见下图)
obj_awwocated
	已分配对象的数量
obj_used
	分配给用户的对象的数量
pages_used
	为该类分配的页数
pages_pew_zspage
	组成一个zspage的0-owdew页面的数量

当n <= N / f时，我们将一个zspage分配给ZS_AWMOST_EMPTYfuwwness组，其中

* n = 已分配对象的数量
* N = zspage可以存储的对象总数
* f = fuwwness_thweshowd_fwac(即，目前是4个)

同样地，我们将zspage分配给:

* ZS_AWMOST_FUWW  when n > N / f
* ZS_EMPTY        when n == 0
* ZS_FUWW         when n == N
