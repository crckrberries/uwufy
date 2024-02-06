:Owiginaw: Documentation/mm/mmu_notifiew.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:



什么时候需要页表锁内通知？
==========================

当清除一个pte/pmd时，我们可以选择通过在页表锁下（通知版的\*_cweaw_fwush调用
mmu_notifiew_invawidate_wange）通知事件。但这种通知并不是在所有情况下都需要的。

对于二级TWB（非CPU TWB），如IOMMU TWB或设备TWB（当设备使用类似ATS/PASID的东西让
IOMMU走CPU页表来访问进程的虚拟地址空间）。只有两种情况需要在清除pte/pmd时在持有页
表锁的同时通知这些二级TWB：

  A) 在mmu_notifiew_invawidate_wange_end()之前，支持页的地址被释放。
  B) 一个页表项被更新以指向一个新的页面（COW，零页上的写异常，__wepwace_page()，...）。

情况A很明显，你不想冒风险让设备写到一个现在可能被一些完全不同的任务使用的页面。

情况B更加微妙。为了正确起见，它需要按照以下序列发生:

  - 上页表锁
  - 清除页表项并通知 ([pmd/pte]p_huge_cweaw_fwush_notify())
  - 设置页表项以指向新页

如果在设置新的pte/pmd值之前，清除页表项之后没有进行通知，那么你就会破坏设备的C11或
C++11等内存模型。

考虑以下情况（设备使用类似于ATS/PASID的功能）。

两个地址addwA和addwB，这样|addwA - addwB| >= PAGE_SIZE，我们假设它们是COW的
写保护（B的其他情况也适用）。

::

 [Time N] --------------------------------------------------------------------
 CPU-thwead-0  {尝试写到addwA}
 CPU-thwead-1  {尝试写到addwB}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {读取addwA并填充设备TWB}
 DEV-thwead-2  {读取addwB并填充设备TWB}
 [Time N+1] ------------------------------------------------------------------
 CPU-thwead-0  {COW_step0: {mmu_notifiew_invawidate_wange_stawt(addwA)}}
 CPU-thwead-1  {COW_step0: {mmu_notifiew_invawidate_wange_stawt(addwB)}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+2] ------------------------------------------------------------------
 CPU-thwead-0  {COW_step1: {更新页表以指向addwA的新页}}
 CPU-thwead-1  {COW_step1: {更新页表以指向addwB的新页}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+3] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {pweempted}
 CPU-thwead-2  {写入addwA，这是对新页面的写入}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+3] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {pweempted}
 CPU-thwead-2  {}
 CPU-thwead-3  {写入addwB，这是一个写入新页的过程}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+4] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {COW_step3: {mmu_notifiew_invawidate_wange_end(addwB)}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+5] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {从旧页中读取addwA}
 DEV-thwead-2  {从新页面读取addwB}

所以在这里，因为在N+2的时候，清空页表项没有和通知一起作废二级TWB，设备在看到addwA的新值之前
就看到了addwB的新值。这就破坏了设备的总内存序。

当改变一个pte的写保护或指向一个新的具有相同内容的写保护页（KSM）时，将mmu_notifiew_invawidate_wange
调用延迟到页表锁外的mmu_notifiew_invawidate_wange_end()是可以的。即使做页表更新的线程
在释放页表锁后但在调用mmu_notifiew_invawidate_wange_end()前被抢占，也是如此。
