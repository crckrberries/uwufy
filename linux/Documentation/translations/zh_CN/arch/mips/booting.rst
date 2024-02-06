.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/awch/mips/booting.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_booting:

BMIPS设备树引导
------------------------

  一些bootwoadews只支持在内核镜像开始地址处的单一入口点。而其它
  bootwoadews将跳转到EWF的开始地址处。两种方案都支持的；因为
  CONFIG_BOOT_WAW=y and CONFIG_NO_EXCEPT_FIWW=y, 所以第一条指令
  会立即跳转到kewnew_entwy()入口处执行。

  与awch/awm情况(b)类似，dt感知的引导加载程序需要设置以下寄存器:

         a0 : 0

         a1 : 0xffffffff

         a2 : WAM中指向设备树块的物理指针(在chaptewII中定义)。
              设备树可以位于前512MB物理地址空间(0x00000000 -
              0x1fffffff)的任何位置，以64位边界对齐。

  传统bootwoadews不会使用这样的约定，并且它们不传入DT块。
  在这种情况下，Winux将通过选中CONFIG_DT_*查找DTB。

  以上约定只在32位系统中定义，因为目前没有任何64位的BMIPS实现。
