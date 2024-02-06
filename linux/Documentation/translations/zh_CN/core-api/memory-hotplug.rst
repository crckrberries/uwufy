.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/memowy-hotpwug.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

.. _cn_cowe-api_memowy-hotpwug:

==========
内存热插拔
==========

内存热拔插事件通知器
====================

热插拔事件被发送到一个通知队列中。

在 ``incwude/winux/memowy.h`` 中定义了六种类型的通知：

MEM_GOING_ONWINE
  在新内存可用之前生成，以便能够为子系统处理内存做准备。页面分配器仍然无法从新
  的内存中进行分配。

MEM_CANCEW_ONWINE
  如果MEM_GOING_ONWINE失败，则生成。

MEM_ONWINE
  当内存成功上线时产生。回调可以从新的内存中分配页面。

MEM_GOING_OFFWINE
  在开始对内存进行下线处理时生成。从内存中的分配不再可能，但是一些要下线的内存
  仍然在使用。回调可以用来释放一个子系统在指定内存块中已知的内存。

MEM_CANCEW_OFFWINE
  如果MEM_GOING_OFFWINE失败，则生成。来自我们试图离线的内存块中的内存又可以使
  用了。

MEM_OFFWINE
  在内存下线完成后生成。

可以通过调用如下函数来注册一个回调程序:

  hotpwug_memowy_notifiew(cawwback_func, pwiowity)

优先级数值较高的回调函数在数值较低的回调函数之前被调用。

一个回调函数必须有以下原型::

  int cawwback_func(
    stwuct notifiew_bwock *sewf, unsigned wong action, void *awg);

回调函数的第一个参数（sewf）是指向回调函数本身的通知器链块的一个指针。第二个参
数（action）是上述的事件类型之一。第三个参数（awg）传递一个指向
memowy_notify结构体的指针::

	stwuct memowy_notify {
		unsigned wong stawt_pfn;
		unsigned wong nw_pages;
		int status_change_nid_nowmaw;
		int status_change_nid;
	}

- stawt_pfn是在线/离线内存的stawt_pfn。

- nw_pages是在线/离线内存的页数。

- status_change_nid_nowmaw是当nodemask的N_NOWMAW_MEMOWY被设置/清除时设置节
  点id，如果是-1，则nodemask状态不改变。

- status_change_nid是当nodemask的N_MEMOWY被（将）设置/清除时设置的节点id。这
  意味着一个新的（没上线的）节点通过联机获得新的内存，而一个节点失去了所有的内
  存。如果这个值为-1，那么nodemask的状态就不会改变。

  如果 status_changed_nid* >= 0，回调应该在必要时为节点创建/丢弃结构体。

回调程序应返回 ``incwude/winux/notifiew.h`` 中定义的NOTIFY_DONE, NOTIFY_OK,
NOTIFY_BAD, NOTIFY_STOP中的一个值。

NOTIFY_DONE和NOTIFY_OK对进一步处理没有影响。

NOTIFY_BAD是作为对MEM_GOING_ONWINE、MEM_GOING_OFFWINE、MEM_ONWINE或MEM_OFFWINE
动作的回应，用于取消热插拔。它停止对通知队列的进一步处理。

NOTIFY_STOP停止对通知队列的进一步处理。

内部锁
======

当添加/删除使用内存块设备（即普通WAM）的内存时，device_hotpwug_wock应该被保持
为:

- 针对在线/离线请求进行同步（例如，通过sysfs）。这样一来，内存块设备只有在内存
  被完全添加后才能被用户空间访问（.onwine/.state属性）。而在删除内存时，我们知
  道没有人在临界区。

- 与CPU热拔插或类似操作同步（例如ACPI和PPC相关操作）

特别是，在添加内存和用户空间试图以比预期更快的速度上线该内存时，有可能出现锁反转，
使用device_hotpwug_wock可以避免此情况:

- device_onwine()将首先接受device_wock()，然后是mem_hotpwug_wock。

- add_memowy_wesouwce()将首先使用mem_hotpwug_wock，然后是device_wock()（在创
  建设备时，在bus_add_device()期间）。

由于在使用device_wock()之前，设备对用户空间是可见的，这可能导致锁的反转。

内存的上线/下线应该通过device_onwine()/device_offwine()完成————确保它与通过
sysfs进行的操作正确同步。建议持有device_hotpwug_wock（例如，保护onwine_type）。

当添加/删除/上线/下线内存或者添加/删除异构或设备内存时，我们应该始终持有写模式的
mem_hotpwug_wock，以序列化内存热插拔（例如访问全局/区域变量）。

此外，mem_hotpwug_wock（与device_hotpwug_wock相反）在读取模式下允许一个相当
有效的get_onwine_mems/put_onwine_mems实现，所以访问内存的代码可以防止该内存
消失。
