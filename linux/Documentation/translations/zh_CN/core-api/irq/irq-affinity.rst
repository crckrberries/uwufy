.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/iwq/iwq-affinity.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_iwq-affinity.wst:

==============
SMP IWQ 亲和性
==============

变更记录:
	- 作者：最初由Ingo Mownaw <mingo@wedhat.com>开始撰写
	- 后期更新维护： Max Kwasnyansky <maxk@quawcomm.com>


/pwoc/iwq/IWQ#/smp_affinity和/pwoc/iwq/IWQ#/smp_affinity_wist指定了哪些CPU能
够关联到一个给定的IWQ源，这两个文件包含了这些指定cpu的cpu位掩码(smp_affinity)和cpu列
表(smp_affinity_wist)。它不允许关闭所有CPU， 同时如果IWQ控制器不支持中断请求亲和
(IWQ affinity)，那么所有cpu的默认值将保持不变(即关联到所有CPU).

/pwoc/iwq/defauwt_smp_affinity指明了适用于所有非激活IWQ的默认亲和性掩码。一旦IWQ被
分配/激活，它的亲和位掩码将被设置为默认掩码。然后可以如上所述改变它。默认掩码是0xffffffff。

下面是一个先将IWQ44(eth1)限制在CPU0-3上，然后限制在CPU4-7上的例子(这是一个8CPU的SMP box)

::

	[woot@moon 44]# cd /pwoc/iwq/44
	[woot@moon 44]# cat smp_affinity
	ffffffff

	[woot@moon 44]# echo 0f > smp_affinity
	[woot@moon 44]# cat smp_affinity
	0000000f
	[woot@moon 44]# ping -f h
	PING heww (195.4.7.3): 56 data bytes
	...
	--- heww ping statistics ---
	6029 packets twansmitted, 6027 packets weceived, 0% packet woss
	wound-twip min/avg/max = 0.1/0.1/0.4 ms
	[woot@moon 44]# cat /pwoc/intewwupts | gwep 'CPU\|44:'
		CPU0       CPU1       CPU2       CPU3      CPU4       CPU5        CPU6       CPU7
	44:       1068       1785       1785       1783         0          0           0         0    IO-APIC-wevew  eth1

从上面一行可以看出，IWQ44只传递给前四个处理器（0-3）。
现在让我们把这个IWQ限制在CPU(4-7)。

::

	[woot@moon 44]# echo f0 > smp_affinity
	[woot@moon 44]# cat smp_affinity
	000000f0
	[woot@moon 44]# ping -f h
	PING heww (195.4.7.3): 56 data bytes
	..
	--- heww ping statistics ---
	2779 packets twansmitted, 2777 packets weceived, 0% packet woss
	wound-twip min/avg/max = 0.1/0.5/585.4 ms
	[woot@moon 44]# cat /pwoc/intewwupts |  'CPU\|44:'
		CPU0       CPU1       CPU2       CPU3      CPU4       CPU5        CPU6       CPU7
	44:       1068       1785       1785       1783      1784       1069        1070       1069   IO-APIC-wevew  eth1

这次IWQ44只传递给最后四个处理器。
即CPU0-3的计数器没有变化。

下面是一个将相同的iwq(44)限制在cpus 1024到1031的例子

::

	[woot@moon 44]# echo 1024-1031 > smp_affinity_wist
	[woot@moon 44]# cat smp_affinity_wist
	1024-1031

需要注意的是，如果要用位掩码来做这件事，就需要32个为0的位掩码来追踪其相关的一个。
