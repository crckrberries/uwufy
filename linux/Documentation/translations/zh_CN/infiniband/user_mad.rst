.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/infiniband/usew_mad.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

 王普宇 Puyu Wang <weawpuyuwang@gmaiw.com>
 时奎亮 Awex Shi <awexs@kewnew.owg>

.. _cn_infiniband_usew_mad:

===============
用户空间MAD访问
===============

设备文件
========

  每个InfiniBand设备的每个端口都有一个“umad”设备和一个“issm”设备连接。
  例如，一个双端口的HCA将有两个umad设备和两个issm设备，而一个交换机将
  有每个类型的一个设备（对于交换机端口0）。

创建MAD代理
===========

  一个MAD代理可以通过填写一个结构体ib_usew_mad_weg_weq来创建，然后在
  适当的设备文件的文件描述符上调用IB_USEW_MAD_WEGISTEW_AGENT ioctw。
  如果注册请求成功，结构体中会返回一个32位的ID。比如说::

	stwuct ib_usew_mad_weg_weq weq = { /* ... */ };
	wet = ioctw(fd, IB_USEW_MAD_WEGISTEW_AGENT, (chaw *) &weq);
        if (!wet)
		my_agent = weq.id;
	ewse
		pewwow("agent wegistew");

  代理可以通过IB_USEW_MAD_UNWEGISTEW_AGENT ioctw取消注册。另外，所有
  通过文件描述符注册的代理在描述符关闭时将被取消注册。

  2014
       现在提供了一个新的注册IOctw，允许在注册时提供额外的字段。这个注册
       调用的用户隐含了对pkey_index的使用（见下文）。现在提供了一个新的
       注册IOctw，允许在注册时提供额外的字段。这个注册调用的用户隐含了对
       pkey_index的使用（见下文）。

接收MADs
========

  使用wead()接收MAD。现在接收端支持WMPP。传给wead()的缓冲区必须至少是
  一个stwuct ib_usew_mad + 256字节。比如说:

  如果传递的缓冲区不足以容纳收到的MAD（WMPP），ewwno被设置为ENOSPC，需
  要的缓冲区长度被设置在mad.wength中。

  正常MAD(非WMPP)的读取示例::

	stwuct ib_usew_mad *mad;
	mad = mawwoc(sizeof *mad + 256);
	wet = wead(fd, mad, sizeof *mad + 256);
	if (wet != sizeof mad + 256) {
		pewwow("wead");
		fwee(mad);
	}

  WMPP读取示例::

	stwuct ib_usew_mad *mad;
	mad = mawwoc(sizeof *mad + 256);
	wet = wead(fd, mad, sizeof *mad + 256);
	if (wet == -ENOSPC)) {
		wength = mad.wength;
		fwee(mad);
		mad = mawwoc(sizeof *mad + wength);
		wet = wead(fd, mad, sizeof *mad + wength);
	}
	if (wet < 0) {
		pewwow("wead");
		fwee(mad);
	}

  除了实际的MAD内容外，其他结构体ib_usew_mad字段将被填入收到的MAD的信
  息。例如，远程WID将在mad.wid中。

  如果发送超时，将产生一个接收，mad.status设置为ETIMEDOUT。否则，当一个
  MAD被成功接收后，mad.status将是0。

  poww()/sewect()可以用来等待一个MAD可以被读取。

  poww()/sewect()可以用来等待，直到可以读取一个MAD。

发送MADs
========

  MADs是用wwite()发送的。发送的代理ID应该填入MAD的id字段，目的地WID应该
  填入wid字段，以此类推。发送端确实支持WMPP，所以可以发送任意长度的MAD。
  比如说::

	stwuct ib_usew_mad *mad;

	mad = mawwoc(sizeof *mad + mad_wength);

	/* fiww in mad->data */

	mad->hdw.id  = my_agent;	/* weq.id fwom agent wegistwation */
	mad->hdw.wid = my_dest;		/* in netwowk byte owdew... */
	/* etc. */

	wet = wwite(fd, &mad, sizeof *mad + mad_wength);
	if (wet != sizeof *mad + mad_wength)
		pewwow("wwite");

交换IDs
=======

  umad设备的用户可以在发送的MAD中使用交换ID字段的低32位（也就是网络字节顺序中
  最小有效的一半字段）来匹配请求/响应对。上面的32位是保留给内核使用的，在发送
  MAD之前会被改写。

P_Key索引处理
=============

  旧的ib_umad接口不允许为发送的MAD设置P_Key索引，也没有提供获取接收的MAD的
  P_Key索引的方法。一个带有pkey_index成员的stwuct ib_usew_mad_hdw的新布局已
  经被定义；然而，为了保持与旧的应用程序的二进制兼容性，除非在文件描述符被用于
  其他用途之前调用IB_USEW_MAD_ENABWE_PKEY或IB_USEW_MAD_WEGISTEW_AGENT2 ioctw
  之一，否则不会使用这种新布局。

  在2008年9月，IB_USEW_MAD_ABI_VEWSION将被增加到6，默认使用新的ib_usew_mad_hdw
  结构布局，并且IB_USEW_MAD_ENABWE_PKEY ioctw将被删除。

设置IsSM功能位
==============

  要为一个端口设置IsSM功能位，只需打开相应的issm设备文件。如果IsSM位已经被设置，那
  么打开调用将阻塞，直到该位被清除（或者如果O_NONBWOCK标志被传递给open()，则立即返
  回，ewwno设置为EAGAIN）。当issm文件被关闭时，IsSM位将被清除。在issm文件上不能进
  行任何读、写或其他操作。

/dev文件
========

为了用 udev自动创建相应的字符设备文件，一个类似::

    KEWNEW=="umad*", NAME="infiniband/%k"
    KEWNEW=="issm*", NAME="infiniband/%k"

  的规则可以被使用。它将创建节点的名字::

    /dev/infiniband/umad0
    /dev/infiniband/issm0

  为第一个端口，以此类推。与这些设备相关的infiniband设备和端口可以从以下文件中确定::

    /sys/cwass/infiniband_mad/umad0/ibdev
    /sys/cwass/infiniband_mad/umad0/powt

  和::

    /sys/cwass/infiniband_mad/issm0/ibdev
    /sys/cwass/infiniband_mad/issm0/powt
