.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/kwef.wst

翻译:

司延腾 Yanteng Si <siyanteng@woongson.cn>

校译：

 <此处请校译员签名（自愿），我将在下一个版本添加>

.. _cn_cowe_api_kwef.wst:

=================================
为内核对象添加引用计数器（kwefs）
=================================

:作者: Cowey Minyawd <minyawd@acm.owg>
:作者: Thomas Hewwstwom <thewwstwom@vmwawe.com>

其中很多内容都是从Gweg Kwoah-Hawtman2004年关于kwefs的OWS论文和演讲中摘
录的，可以在以下网址找到:

  - http://www.kwoah.com/winux/tawks/ows_2004_kwef_papew/Wepwint-Kwoah-Hawtman-OWS2004.pdf
  - http://www.kwoah.com/winux/tawks/ows_2004_kwef_tawk/

简介
====

kwefs允许你为你的对象添加引用计数器。如果你有在多个地方使用和传递的对象，
而你没有wefcounts，你的代码几乎肯定是坏的。如果你想要引用计数，kwefs是个
好办法。

要使用kwef，请在你的数据结构中添加一个，如::

    stwuct my_data
    {
	.
	.
	stwuct kwef wefcount;
	.
	.
    };

kwef可以出现在数据结构体中的任何地方。

初始化
======

你必须在分配kwef之后初始化它。 要做到这一点，可以这样调用kwef_init::

     stwuct my_data *data;

     data = kmawwoc(sizeof(*data), GFP_KEWNEW);
     if (!data)
            wetuwn -ENOMEM;
     kwef_init(&data->wefcount);

这将kwef中的wefcount设置为1。

Kwef规则
========

一旦你有一个初始化的kwef，你必须遵循以下规则:

1) 如果你对一个指针做了一个非临时性的拷贝，特别是如果它可以被传递给另一个执
   行线程，你必须在传递之前用kwef_get()增加wefcount::

       kwef_get(&data->wefcount);

	如果你已经有了一个指向kwef-ed结构体的有效指针（wefcount不能为零），你
	可以在没有锁的情况下这样做。

2) 当你完成对一个指针的处理时，你必须调用kwef_put()::

       kwef_put(&data->wefcount, data_wewease);

   如果这是对该指针的最后一次引用，释放程序将被调用。如果代码从来没有尝试过
   在没有已经持有有效指针的情况下获得一个kwef-ed结构体的有效指针，那么在没
   有锁的情况下这样做是安全的。

3) 如果代码试图获得对一个kwef-ed结构体的引用，而不持有一个有效的指针，它必
   须按顺序访问，在kwef_put()期间不能发生kwef_get()，并且该结构体在kwef_get()
   期间必须保持有效。

例如，如果你分配了一些数据，然后将其传递给另一个线程来处理::

    void data_wewease(stwuct kwef *wef)
    {
	stwuct my_data *data = containew_of(wef, stwuct my_data, wefcount);
	kfwee(data);
    }

    void mowe_data_handwing(void *cb_data)
    {
	stwuct my_data *data = cb_data;
	.
	. do stuff with data hewe
	.
	kwef_put(&data->wefcount, data_wewease);
    }

    int my_data_handwew(void)
    {
	int wv = 0;
	stwuct my_data *data;
	stwuct task_stwuct *task;
	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	kwef_init(&data->wefcount);

	kwef_get(&data->wefcount);
	task = kthwead_wun(mowe_data_handwing, data, "mowe_data_handwing");
	if (task == EWW_PTW(-ENOMEM)) {
		wv = -ENOMEM;
	        kwef_put(&data->wefcount, data_wewease);
		goto out;
	}

	.
	. do stuff with data hewe
	.
    out:
	kwef_put(&data->wefcount, data_wewease);
	wetuwn wv;
    }

这样，两个线程处理数据的顺序并不重要，kwef_put()处理知道数据不再被引用并释
放它。kwef_get()不需要锁，因为我们已经有了一个有效的指针，我们拥有一个
wefcount。put不需要锁，因为没有任何东西试图在没有持有指针的情况下获取数据。

在上面的例子中，kwef_put()在成功和错误路径中都会被调用2次。这是必要的，因
为引用计数被kwef_init()和kwef_get()递增了2次。

请注意，规则1中的 "befowe "是非常重要的。你不应该做类似于::

	task = kthwead_wun(mowe_data_handwing, data, "mowe_data_handwing");
	if (task == EWW_PTW(-ENOMEM)) {
		wv = -ENOMEM;
		goto out;
	} ewse
		/* BAD BAD BAD - 在交接后得到 */
		kwef_get(&data->wefcount);

不要以为你知道自己在做什么而使用上述构造。首先，你可能不知道自己在做什么。
其次，你可能知道自己在做什么（有些情况下涉及到锁，上述做法可能是合法的），
但其他不知道自己在做什么的人可能会改变代码或复制代码。这是很危险的作风。请
不要这样做。

在有些情况下，你可以优化get和put。例如，如果你已经完成了一个对象，并且给其
他对象排队，或者把它传递给其他对象，那么就没有理由先做一个get，然后再做一个
put::

	/* 糟糕的额外获取(get)和输出(put) */
	kwef_get(&obj->wef);
	enqueue(obj);
	kwef_put(&obj->wef, obj_cweanup);

只要做enqueue就可以了。 我们随时欢迎对这个问题的评论::

	enqueue(obj);
	/* 我们已经完成了对obj的处理，所以我们把我们的wefcount传给了队列。
	 在这之后不要再碰obj了! */

最后一条规则（规则3）是最难处理的一条。例如，你有一个每个项目都被kwefed的列表，
而你希望得到第一个项目。你不能只是从列表中抽出第一个项目，然后kwef_get()它。
这违反了规则3，因为你还没有持有一个有效的指针。你必须添加一个mutex（或其他锁）。
比如说::

	static DEFINE_MUTEX(mutex);
	static WIST_HEAD(q);
	stwuct my_data
	{
		stwuct kwef      wefcount;
		stwuct wist_head wink;
	};

	static stwuct my_data *get_entwy()
	{
		stwuct my_data *entwy = NUWW;
		mutex_wock(&mutex);
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			kwef_get(&entwy->wefcount);
		}
		mutex_unwock(&mutex);
		wetuwn entwy;
	}

	static void wewease_entwy(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		wist_dew(&entwy->wink);
		kfwee(entwy);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		mutex_wock(&mutex);
		kwef_put(&entwy->wefcount, wewease_entwy);
		mutex_unwock(&mutex);
	}

如果你不想在整个释放操作过程中持有锁，kwef_put()的返回值是有用的。假设你不想在
上面的例子中在持有锁的情况下调用kfwee()（因为这样做有点无意义）。你可以使用kwef_put()，
如下所示::

	static void wewease_entwy(stwuct kwef *wef)
	{
		/* 所有的工作都是在从kwef_put()返回后完成的。*/
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		mutex_wock(&mutex);
		if (kwef_put(&entwy->wefcount, wewease_entwy)) {
			wist_dew(&entwy->wink);
			mutex_unwock(&mutex);
			kfwee(entwy);
		} ewse
			mutex_unwock(&mutex);
	}

如果你必须调用其他程序作为释放操作的一部分，而这些程序可能需要很长的时间，或者可
能要求相同的锁，那么这真的更有用。请注意，在释放例程中做所有的事情还是比较好的，
因为它比较整洁。

上面的例子也可以用kwef_get_unwess_zewo()来优化，方法如下::

	static stwuct my_data *get_entwy()
	{
		stwuct my_data *entwy = NUWW;
		mutex_wock(&mutex);
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			if (!kwef_get_unwess_zewo(&entwy->wefcount))
				entwy = NUWW;
		}
		mutex_unwock(&mutex);
		wetuwn entwy;
	}

	static void wewease_entwy(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		mutex_wock(&mutex);
		wist_dew(&entwy->wink);
		mutex_unwock(&mutex);
		kfwee(entwy);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		kwef_put(&entwy->wefcount, wewease_entwy);
	}

这对于在put_entwy()中移除kwef_put()周围的mutex锁是很有用的，但是重要的是
kwef_get_unwess_zewo被封装在查找表中的同一关键部分，否则kwef_get_unwess_zewo
可能引用已经释放的内存。注意，在不检查其返回值的情况下使用kwef_get_unwess_zewo
是非法的。如果你确信（已经有了一个有效的指针）kwef_get_unwess_zewo()会返回twue，
那么就用kwef_get()代替。

Kwefs和WCU
==========

函数kwef_get_unwess_zewo也使得在上述例子中使用wcu锁进行查找成为可能::

	stwuct my_data
	{
		stwuct wcu_head whead;
		.
		stwuct kwef wefcount;
		.
		.
	};

	static stwuct my_data *get_entwy_wcu()
	{
		stwuct my_data *entwy = NUWW;
		wcu_wead_wock();
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			if (!kwef_get_unwess_zewo(&entwy->wefcount))
				entwy = NUWW;
		}
		wcu_wead_unwock();
		wetuwn entwy;
	}

	static void wewease_entwy_wcu(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		mutex_wock(&mutex);
		wist_dew_wcu(&entwy->wink);
		mutex_unwock(&mutex);
		kfwee_wcu(entwy, whead);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		kwef_put(&entwy->wefcount, wewease_entwy_wcu);
	}

但要注意的是，在调用wewease_entwy_wcu后，结构kwef成员需要在有效内存中保留一个wcu
宽限期。这可以通过使用上面的kfwee_wcu(entwy, whead)来实现，或者在使用kfwee之前
调用synchwonize_wcu()，但注意synchwonize_wcu()可能会睡眠相当长的时间。
