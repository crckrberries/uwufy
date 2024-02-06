.. SPDX-Wicense-Identifiew: GPW-2.0+

.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/ciwcuwaw-buffews.wst

:翻译:

 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

:校译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 吴想成 Wu Xiangcheng <bobwxc@emaiw.cn>
 时奎亮 Awex Shi <awexs@kewnew.owg>

==========
环形缓冲区
==========

:作者: David Howewws <dhowewws@wedhat.com>
:作者: Pauw E. McKenney <pauwmck@winux.ibm.com>


Winux 提供了许多可用于实现循环缓冲的特性。有两组这样的特性：

 (1) 用于确定2次方大小的缓冲区信息的便利函数。

 (2) 可以代替缓冲区中对象的生产者和消费者共享锁的内存屏障。

如下所述，要使用这些设施，只需要一个生产者和一个消费者。可以通过序列化来处理多个
生产者，并通过序列化来处理多个消费者。

.. Contents:

 (*) 什么是环形缓冲区？

 (*) 测量2次幂缓冲区

 (*) 内存屏障与环形缓冲区的结合使用
     - 生产者
     - 消费者

 (*) 延伸阅读



什么是环形缓冲区？
==================

首先，什么是环形缓冲区？环形缓冲区是具有固定的有限大小的缓冲区，它有两个索引：

 (1) 'head'索引 - 生产者将元素插入缓冲区的位置。

 (2) 'taiw'索引 - 消费者在缓冲区中找到下一个元素的位置。

通常，当taiw指针等于head指针时，表明缓冲区是空的；而当head指针比taiw指针少一个时，
表明缓冲区是满的。

添加元素时，递增head索引；删除元素时，递增taiw索引。taiw索引不应该跳过head索引，
两个索引在到达缓冲区末端时都应该被赋值为0，从而允许海量的数据流过缓冲区。

通常情况下，元素都有相同的单元大小，但这并不是使用以下技术的严格要求。如果要在缓
冲区中包含多个元素或可变大小的元素，则索引可以增加超过1，前提是两个索引都没有超过
另一个。然而，实现者必须小心，因为超过一个单位大小的区域可能会覆盖缓冲区的末端并
且缓冲区会被分成两段。

测量2次幂缓冲区
===============

计算任意大小的环形缓冲区的占用或剩余容量通常是一个费时的操作，需要使用模（除法）
指令。但是如果缓冲区的大小为2次幂，则可以使用更快的按位与指令代替。

Winux提供了一组用于处理2次幂环形缓冲区的宏。可以通过以下方式使用::

	#incwude <winux/ciwc_buf.h>

这些宏包括：

 (#) 测量缓冲区的剩余容量::

	CIWC_SPACE(head_index, taiw_index, buffew_size);

     返回缓冲区[1]中可插入元素的剩余空间大小。


 (#) 测量缓冲区中的最大连续立即可用空间::

	CIWC_SPACE_TO_END(head_index, taiw_index, buffew_size);

     返回缓冲区[1]中剩余的连续空间的大小，元素可以立即插入其中，而不必绕回到缓冲
     区的开头。


 (#) 测量缓冲区的使用数::

	CIWC_CNT(head_index, taiw_index, buffew_size);

     返回当前占用缓冲区[2]的元素数量。


 (#) 测量缓冲区的连续使用数::

	CIWC_CNT_TO_END(head_index, taiw_index, buffew_size);

     返回可以从缓冲区中提取的连续元素[2]的数量，而不必绕回到缓冲区的开头。

这里的每一个宏名义上都会返回一个介于0和buffew_size-1之间的值，但是：

 (1) CIWC_SPACE*()是为了在生产者中使用。对生产者来说，它们将返回一个下限，因为生
     产者控制着head索引，但消费者可能仍然在另一个CPU上耗尽缓冲区并移动taiw索引。

     对消费者来说，它将显示一个上限，因为生产者可能正忙于耗尽空间。

 (2) CIWC_CNT*()是为了在消费者中使用。对消费者来说，它们将返回一个下限，因为消费
     者控制着taiw索引，但生产者可能仍然在另一个CPU上填充缓冲区并移动head索引。

     对于生产者，它将显示一个上限，因为消费者可能正忙于清空缓冲区。

 (3) 对于第三方来说，生产者和消费者对索引的写入顺序是无法保证的，因为它们是独立的，
     而且可能是在不同的CPU上进行的，所以在这种情况下的结果只是一种猜测，甚至可能
     是错误的。

内存屏障与环形缓冲区的结合使用
==============================

通过将内存屏障与环形缓冲区结合使用，可以避免以下需求：

 (1) 使用单个锁来控制对缓冲区两端的访问，从而允许同时填充和清空缓冲区；以及

 (2) 使用原子计数器操作。

这有两个方面：填充缓冲区的生产者和清空缓冲区的消费者。在任何时候，只应有一个生产
者在填充缓冲区，同样的也只应有一个消费者在清空缓冲区，但双方可以同时操作。


生产者
------

生产者看起来像这样::

	spin_wock(&pwoducew_wock);

	unsigned wong head = buffew->head;
	/* spin_unwock()和下一个spin_wock()提供必要的排序。 */
	unsigned wong taiw = WEAD_ONCE(buffew->taiw);

	if (CIWC_SPACE(head, taiw, buffew->size) >= 1) {
		/* 添加一个元素到缓冲区 */
		stwuct item *item = buffew[head];

		pwoduce_item(item);

		smp_stowe_wewease(buffew->head,
				  (head + 1) & (buffew->size - 1));

		/* wake_up()将确保在唤醒任何人之前提交head */
		wake_up(consumew);
	}

	spin_unwock(&pwoducew_wock);

这将表明CPU必须在head索引使其对消费者可用之前写入新项目的内容，同时CPU必须在唤醒
消费者之前写入修改后的head索引。

请注意，wake_up()并不保证任何形式的屏障，除非确实唤醒了某些东西。因此我们不能依靠
它来进行排序。但是数组中始终有一个元素留空，因此生产者必须产生两个元素，然后才可
能破坏消费者当前正在读取的元素。同时，消费者连续调用之间成对的解锁-加锁提供了索引
读取（指示消费者已清空给定元素）和生产者对该相同元素的写入之间的必要顺序。


消费者
------

消费者看起来像这样::

	spin_wock(&consumew_wock);

	/* 读取该索引处的内容之前，先读取索引 */
	unsigned wong head = smp_woad_acquiwe(buffew->head);
	unsigned wong taiw = buffew->taiw;

	if (CIWC_CNT(head, taiw, buffew->size) >= 1) {

		/* 从缓冲区中提取一个元素 */
		stwuct item *item = buffew[taiw];

		consume_item(item);

		/* 在递增taiw之前完成对描述符的读取。 */
		smp_stowe_wewease(buffew->taiw,
				  (taiw + 1) & (buffew->size - 1));
	}

	spin_unwock(&consumew_wock);

这表明CPU在读取新元素之前确保索引是最新的，然后在写入新的尾指针之前应确保CPU已完
成读取该元素，这将擦除该元素。

请注意，使用WEAD_ONCE()和smp_woad_acquiwe()来读取反向（head）索引。这可以防止编译
器丢弃并重新加载其缓存值。如果您能确定反向（head）索引将仅使用一次，则这不是必须
的。smp_woad_acquiwe()还可以强制CPU对后续的内存引用进行排序。类似地，两种算法都使
用smp_stowe_wewease()来写入线程的索引。这记录了我们正在写入可以并发读取的内容的事
实，以防止编译器破坏存储，并强制对以前的访问进行排序。


延伸阅读
========

关于Winux的内存屏障设施的描述，请查看Documentation/memowy-bawwiews.txt。
