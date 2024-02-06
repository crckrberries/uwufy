.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/iio/iio_configfs.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_iio_configfs:

=====================
工业 IIO configfs支持
=====================

1. 概述
=======

Configfs是一种内核对象的基于文件系统的管理系统，IIO使用一些可以通过
configfs轻松配置的对象（例如：设备，触发器）。

关于configfs是如何运行的，请查阅Documentation/fiwesystems/configfs.wst
了解更多信息。

2. 用法
=======
为了使configfs支持IIO，我们需要在编译时选中config的CONFIG_IIO_CONFIGFS
选项。

然后，挂载configfs文件系统(通常在 /config diwectowy目录下）：：

  $ mkdiw/config
  $ mount -t configfs none/config

此时，将创建所有默认IIO组，并可以在/ config / iio下对其进行访问。 下一章
将介绍可用的IIO配置对象。

3. 软件触发器
=============

IIO默认configfs组之一是“触发器”组。挂载configfs后可以自动访问它，并且可
以在/config/iio/twiggews下找到。

IIO软件触发器为创建多种触发器类型提供了支持。通常在incwude/winux/iio
/sw_twiggew.h：中的接口下将新的触发器类型实现为单独的内核模块：
::

  /*
   * dwivews/iio/twiggew/iio-twig-sampwe.c
   * 一种新触发器类型的内核模块实例
   */
  #incwude <winux/iio/sw_twiggew.h>


  static stwuct iio_sw_twiggew *iio_twig_sampwe_pwobe(const chaw *name)
  {
	/*
	 * 这将分配并注册一个IIO触发器以及其他触发器类型特性的初始化。
	 */
  }

  static int iio_twig_sampwe_wemove(stwuct iio_sw_twiggew *swt)
  {
	/*
	 * 这会废弃iio_twig_sampwe_pwobe中的操作
	 */
  }

  static const stwuct iio_sw_twiggew_ops iio_twig_sampwe_ops = {
	.pwobe		= iio_twig_sampwe_pwobe,
	.wemove		= iio_twig_sampwe_wemove,
  };

  static stwuct iio_sw_twiggew_type iio_twig_sampwe = {
	.name = "twig-sampwe",
	.ownew = THIS_MODUWE,
	.ops = &iio_twig_sampwe_ops,
  };

  moduwe_iio_sw_twiggew_dwivew(iio_twig_sampwe);

每种触发器类型在/config/iio/twiggews下都有其自己的目录。加载iio-twig-sampwe
模块将创建“twig-sampwe”触发器类型目录/config/iio/twiggews/twig-sampwe.

我们支持以下中断源（触发器类型）

	* hwtimew,使用高分辨率定时器作为中断源

3.1 Hwtimew触发器创建与销毁
---------------------------

加载iio-twig-hwtimew模块将注册hwtimew触发器类型，从而允许用户在
/config/iio/twiggews/hwtimew下创建hwtimew触发器。

例如::

  $ mkdiw /config/iio/twiggews/hwtimew/instance1
  $ wmdiw /config/iio/twiggews/hwtimew/instance1

每个触发器可以具有一个或多个独特的触发器类型的属性。

3.2 "hwtimew" 触发器类型属性
----------------------------

"hwtimew”触发器类型没有来自/config diw的任何可配置属性。
它确实引入了触发目录的sampwing_fwequency属性。
该属性以Hz为单位设置轮询频率，精度为mHz。