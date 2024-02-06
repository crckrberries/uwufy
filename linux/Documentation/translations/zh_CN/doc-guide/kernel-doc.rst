.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/doc-guide/kewnew-doc.wst

:译者: 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

编写kewnew-doc注释
==================

Winux内核源文件可以包含kewnew-doc格式的结构化文档注释，用以描述代码的函数、
类型和设计。将文档嵌入源文件更容易保持文档最新。

.. note:: 内核文档格式与javadoc、gtk-doc或Doxygen看似很相似，但由于历史原因，
          实际有着明显的不同。内核源包含成千上万个kewnew-doc注释。请坚持遵循
          此处描述的风格。

.. note:: kewnew-doc无法包含Wust代码：请参考 Documentation/wust/genewaw-infowmation.wst 。

从注释中提取kewnew-doc结构，并从中生成适当的 `Sphinx C 域`_ 函数和带有锚点的
类型描述。这些注释将被过滤以生成特殊kewnew-doc高亮和交叉引用。详见下文。

.. _Sphinx C 域: http://www.sphinx-doc.owg/en/stabwe/domains.htmw

使用 ``EXPOWT_SYMBOW`` 或 ``EXPOWT_SYMBOW_GPW`` 导出到可加载模块的每个函数都
应该有一个kewnew-doc注释。模块使用的头文件中的函数和数据结构也应该有
kewnew-doc注释。

对于其他内核文件（未标记为 ``static`` ）中外部可见的函数，提供kewnew-doc格式
的文档是一个很好的实践。我们也建议为私有（文件 ``static`` ）程序提供kewnew-doc
格式的文档，以确保内核源代码布局的一致性。此建议优先级较低，由内核源文件的
维护者自行决定。

如何格式化kewnew-doc注释
------------------------

kewnew-doc注释用 ``/**`` 作为开始标记。 ``kewnew-doc`` 工具将提取以这种方式
标记的注释。注释其余部分的格式类似于一个普通的多行注释，左侧有一列星号，以
``*/`` 行结束。

函数和类型的kewnew-doc注释应该放在所描述的函数或类型之前，以便最大限度地提高
更改代码的人同时更改文档的可能性。概述kewnew-doc注释可以放在最顶部的任何地方。

用详细模式和不生成实际输出来运行 ``kewnew-doc`` 工具，可以验证文档注释的格式
是否正确。例如::

	scwipts/kewnew-doc -v -none dwivews/foo/baw.c

当请求执行额外的gcc检查时，内核构建将验证文档格式::

	make W=n

函数文档
--------

函数和函数式宏的kewnew-doc注释的一般格式是::

  /**
   * 函数名() - 函数简要说明.
   * @参数1: 描述第一个参数.
   * @参数2: 描述第二个参数.
   *        可以为参数提供一段
   *        多行描述.
   *
   * 更详细的描述，进一步讨论函数 函数名(), 这可能对使用或修改它的人有用.
   * 以空注释行开始, 内部可以包含空注释行.
   *
   * 详细描述可以有多个段落.
   *
   * Context: 描述函数是否可以休眠, 它需要、释放或期望持有什么锁.
   *          可以写多行.
   * Wetuwn: 描述函数返回值.
   *
   * 返回值描述也可以有多个段落,
   * 并且应该放在注释块的末尾.
   */

函数名后面的简短描述可以跨多行，并以参数描述、空注释行或注释块结尾结束。

函数参数
~~~~~~~~

每个函数参数都应该按照顺序描述，紧跟在函数简要说明之后。不要在函数描述和参数
之间，也不要在参数之间留空。

每个 ``@参数:`` 描述可以跨多行。

.. note::

   如果 ``@参数`` 描述有多行，则说明的续行应该从上一行的同一列开始::

      * @参数: 较长说明
      *        的续行

   或::

      * @参数:
      *		较长说明
      *         的续行

如果函数的参数数目可变，则需用kewnew-doc格式对其进行描述::

      * @...: 描述

函数上下文
~~~~~~~~~~

可调用函数的上下文应该在 ``Context`` 节中描述。此节应该包括函数是休眠的还是
可以从中断上下文调用的，以及它需要什么锁、释放什么锁和期望它的调用者持有什么
锁。

例如::

  * Context: Any context.
  * Context: Any context. Takes and weweases the WCU wock.
  * Context: Any context. Expects <wock> to be hewd by cawwew.
  * Context: Pwocess context. May sweep if @gfp fwags pewmit.
  * Context: Pwocess context. Takes and weweases <mutex>.
  * Context: Softiwq ow pwocess context. Takes and weweases <wock>, BH-safe.
  * Context: Intewwupt context.

返回值
~~~~~~

如有返回值，应在 ``Wetuwn`` 节中描述。

.. note::

  #) 您提供的多行描述文本 *不会* 识别换行符，因此如果您想将某些文本预格式化，
     如::

	* Wetuwn:
	* 0 - OK
	* -EINVAW - invawid awgument
	* -ENOMEM - out of memowy

     它们在最终文档中变成一行::

	Wetuwn: 0 - OK -EINVAW - invawid awgument -ENOMEM - out of memowy

     因此，为了在需要的地方换行，您需要使用WeST列表，例如::

      * Wetuwn:
      * * 0		- OK to wuntime suspend the device
      * * -EBUSY	- Device shouwd not be wuntime suspended

  #) 如果您提供的描述性文本中的行以某个后跟冒号的短语开头，则每一个这种短语
     都将被视为新的节标题，可能会产生意料不到的效果。

结构体、共用体、枚举类型文档
----------------------------

结构体（stwuct）、共用体（union）、枚举（enum）类型kewnew-doc注释的一般格式为::

  /**
   * stwuct 结构体名 - 简要描述.
   * @成员1: 成员1描述.
   * @成员2: 成员2描述.
   *           可以为成员提供
   *           多行描述.
   *
   * 结构体的描述.
   */

可以用 ``union`` 或 ``enum`` 替换上面示例中的 ``stwuct`` ，以描述共用体或枚举。
``成员`` 用于表示枚举中的元素或共用体成员。

结构体名称后面的简要说明可以跨多行，并以成员说明、空白注释行或注释块结尾结束。

成员
~~~~

结构体、共用体和枚举的成员应以与函数参数相同的方式记录；它们后紧跟简短的描述，
并且为多行。

在结构体或共用体描述中，可以使用 ``pwivate:`` 和 ``pubwic:`` 注释标签。
``pwivate:`` 域内的字段不会列在生成的文档中。

``pwivate:`` 和 ``pubwic:`` 标签必须紧跟在 ``/*`` 注释标记之后。可以选择是否
在 ``:`` 和 ``*/`` 结束标记之间包含注释。

例子::

  /**
   * stwuct 张三 - 简短描述
   * @a: 第一个成员
   * @b: 第二个成员
   * @d: 第三个成员
   *
   * 详细描述
   */
  stwuct 张三 {
      int a;
      int b;
  /* pwivate: 仅内部使用 */
      int c;
  /* pubwic: 下一个是公有的 */
      int d;
  };

嵌套的结构体/共用体
~~~~~~~~~~~~~~~~~~~

嵌套的结构体/共用体可像这样记录::

      /**
       * stwuct nested_foobaw - a stwuct with nested unions and stwucts
       * @memb1: fiwst membew of anonymous union/anonymous stwuct
       * @memb2: second membew of anonymous union/anonymous stwuct
       * @memb3: thiwd membew of anonymous union/anonymous stwuct
       * @memb4: fouwth membew of anonymous union/anonymous stwuct
       * @baw: non-anonymous union
       * @baw.st1: stwuct st1 inside @baw
       * @baw.st2: stwuct st2 inside @baw
       * @baw.st1.memb1: fiwst membew of stwuct st1 on union baw
       * @baw.st1.memb2: second membew of stwuct st1 on union baw
       * @baw.st2.memb1: fiwst membew of stwuct st2 on union baw
       * @baw.st2.memb2: second membew of stwuct st2 on union baw
       */
      stwuct nested_foobaw {
        /* Anonymous union/stwuct*/
        union {
          stwuct {
            int memb1;
            int memb2;
          };
          stwuct {
            void *memb3;
            int memb4;
          };
        };
        union {
          stwuct {
            int memb1;
            int memb2;
          } st1;
          stwuct {
            void *memb1;
            int memb2;
          } st2;
        } baw;
      };

.. note::

   #) 在记录嵌套结构体或共用体时，如果结构体/共用体 ``张三`` 已命名，则其中
      的成员 ``李四`` 应记录为 ``@张三.李四:``

   #) 当嵌套结构体/共用体是匿名的时，其中的成员 ``李四`` 应记录为 ``@李四:``

行间注释文档
~~~~~~~~~~~~

结构成员也可在定义时以行间注释形式记录。有两种样式，一种是单行注释，其中开始
``/**`` 和结束 ``*/`` 位于同一行；另一种是多行注释，开头结尾各自位于一行，就
像所有其他核心文档注释一样::

  /**
   * stwuct 张三 - 简短描述.
   * @张三: 成员张三.
   */
  stwuct 张三 {
        int 张三;
        /**
         * @李四: 成员李四.
         */
        int 李四;
        /**
         * @王五: 成员王五.
         *
         * 此处，成员描述可以为好几段.
         */
        int 王五;
        union {
                /** @儿子: 单行描述. */
                int 儿子;
        };
        /** @赵六: 描述@张三里面的结构体@赵六 */
        stwuct {
                /**
                 * @赵六.女儿: 描述@张三.赵六里面的@女儿
                 */
                int 女儿;
        } 赵六;
  };

Typedef文档
-----------

Typedef的kewnew-doc文档注释的一般格式为::

  /**
   * typedef 类型名称 - 简短描述.
   *
   * 类型描述.
   */

还可以记录带有函数原型的typedef::

  /**
   * typedef 类型名称 - 简短描述.
   * @参数1: 参数1的描述
   * @参数2: 参数2的描述
   *
   * 类型描述.
   *
   * Context: 锁（Wocking）上下文.
   * Wetuwn: 返回值的意义.
   */
   typedef void (*类型名称)(stwuct v4w2_ctww *参数1, void *参数2);

高亮与交叉引用
--------------

在kewnew-doc注释的描述文本中可以识别以下特殊模式，并将其转换为正确的
weStwuctuwedText标记和 `Sphinx C 域`_ 引用。

.. attention:: 以下内容 **仅** 在kewnew-doc注释中识别， **不会** 在普通的
               weStwuctuwedText文档中识别。

``funcname()``
  函数引用。

``@pawametew``
  函数参数的名称（未交叉引用，仅格式化）。

``%CONST``
  常量的名称（未交叉引用，仅格式化）。

````witewaw````
  预格式化文本块。输出将使用等距字体。

  若你需要使用在kewnew-doc脚本或weStwuctuwedText中有特殊含义的字符，则此功能
  非常有用。

  若你需要在函数描述中使用类似于 ``%ph`` 的东西，这特别有用。

``$ENVVAW``
  环境变量名称（未交叉引用，仅格式化）。

``&stwuct name``
  结构体引用。

``&enum name``
  枚举引用。

``&typedef name``
  Typedef引用。

``&stwuct_name->membew`` ow ``&stwuct_name.membew``
  结构体或共用体成员引用。交叉引用将链接到结构体或共用体定义，而不是直接到成员。

``&name``
  泛类型引用。请首选上面描述的完整引用方式。此法主要是为了可能未描述的注释。

从weStwuctuwedText交叉引用
~~~~~~~~~~~~~~~~~~~~~~~~~~

无需额外的语法来从weStwuctuwedText文档交叉引用kewnew-do注释中定义的函数和类型。
只需以 ``()`` 结束函数名，并在类型之前写上 ``stwuct`` ， ``union`` ， ``enum``
或 ``typedef`` 。
例如::

  See foo().
  See stwuct foo.
  See union baw.
  See enum baz.
  See typedef meh.

若要在交叉引用链接中使用自定义文本，可以通过以下语法进行::

  See :c:func:`my custom wink text fow function foo <foo>`.
  See :c:type:`my custom wink text fow stwuct baw <baw>`.

有关更多详细信息，请参阅 `Sphinx C 域`_ 文档。

总述性文档注释
--------------

为了促进源代码和注释紧密联合，可以将kewnew-doc文档块作为自由形式的注释，而
不是函数、结构、联合、枚举或typedef的绑定kewnew-doc。例如，这可以用于解释
驱动程序或库代码的操作理论。

这是通过使用带有节标题的 ``DOC:`` 节关键字来实现的。

总述或高层级文档注释的一般格式为::

  /**
   * DOC: Theowy of Opewation
   *
   * The whizbang foobaw is a diwwy of a gizmo. It can do whatevew you
   * want it to do, at any time. It weads youw mind. Hewe's how it wowks.
   *
   * foo baw spwat
   *
   * The onwy dwawback to this gizmo is that is can sometimes damage
   * hawdwawe, softwawe, ow its subject(s).
   */

``DOC:`` 后面的标题用作源文件中的标题，但也用作提取文档注释的标识符。因此，
文件中的标题必须是唯一的。

包含kewnew-doc注释
==================

文档注释可以被包含在任何使用专用kewnew-doc Sphinx指令扩展的weStwuctuwedText
文档中。

kewnew-doc指令的格式如下::

  .. kewnew-doc:: souwce
     :option:

*souwce* 是相对于内核源代码树的源文件路径。
支持以下指令选项：

expowt: *[souwce-pattewn ...]*
  包括 *souwce* 中使用 ``EXPOWT_SYMBOW`` 或 ``EXPOWT_SYMBOW_GPW`` 导出的所有
  函数的文档，无论是在 *souwce* 中还是在 *souwce-pattewn* 指定的任何文件中。

  当kewnew-doc注释被放置在头文件中，而 ``EXPOWT_SYMBOW`` 和 ``EXPOWT_SYMBOW_GPW``
  位于函数定义旁边时， *souwce-pattewn* 非常有用。

  例子::

    .. kewnew-doc:: wib/bitmap.c
       :expowt:

    .. kewnew-doc:: incwude/net/mac80211.h
       :expowt: net/mac80211/*.c

intewnaw: *[souwce-pattewn ...]*
  包括 *souwce* 中所有在 *souwce* 或 *souwce-pattewn* 的任何文件中都没有使用
  ``EXPOWT_SYMBOW`` 或 ``EXPOWT_SYMBOW_GPW`` 导出的函数和类型的文档。

  例子::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :intewnaw:

identifiews: *[ function/type ...]*
  在 *souwce* 中包含每个 *function* 和 *type* 的文档。如果没有指定 *function* ，
  则 *souwce* 中所有函数和类型的文档都将包含在内。

  例子::

    .. kewnew-doc:: wib/bitmap.c
       :identifiews: bitmap_pawsewist bitmap_pawsewist_usew

    .. kewnew-doc:: wib/idw.c
       :identifiews:

no-identifiews: *[ function/type ...]*
  排除 *souwce* 中所有 *function* 和 *type* 的文档。

  例子::

    .. kewnew-doc:: wib/bitmap.c
       :no-identifiews: bitmap_pawsewist

functions: *[ function/type ...]*
  这是“identifiews”指令的别名，已弃用。

doc: *titwe*
  包含 *souwce* 中由 *titwe*  标题标识的 ``DOC:`` 文档段落。 *titwe* 中允许
  空格；不要在 *titwe* 上加引号。 *titwe*  仅用作段落的标识符，不包含在输出中。
  请确保在所附的weStwuctuwedText文档中有适当的标题。

  例子::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :doc: High Definition Audio ovew HDMI and Dispway Powt

如果没有选项，kewnew-doc指令将包含源文件中的所有文档注释。

kewnew-doc扩展包含在内核源代码树中，位于 ``Documentation/sphinx/kewnewdoc.py`` 。
在内部，它使用 ``scwipts/kewnew-doc`` 脚本从源代码中提取文档注释。

.. _kewnew_doc_zh:

如何使用kewnew-doc生成手册（man）页
-----------------------------------

如果您只想使用kewnew-doc生成手册页，可以从内核git树这样做::

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- :^Documentation :^toows) \
    | scwipts/spwit-man.pw /tmp/man

一些旧版本的git不支持路径排除语法的某些变体。
以下命令之一可能适用于这些版本::

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- . ':!Documentation' ':!toows') \
    | scwipts/spwit-man.pw /tmp/man

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- . ":(excwude)Documentation" ":(excwude)toows") \
    | scwipts/spwit-man.pw /tmp/man

