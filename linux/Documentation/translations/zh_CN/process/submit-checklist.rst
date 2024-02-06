.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/pwocess/submit-checkwist.wst
:Twanswatow:
 - Awex Shi <awexs@kewnew.owg>
 - Wu XiangCheng <bobwxc@emaiw.cn>

.. _cn_submitcheckwist:

Winux内核补丁提交检查单
~~~~~~~~~~~~~~~~~~~~~~~

如果开发人员希望看到他们的内核补丁提交更快地被接受，那么他们应该做一些基本
的事情。

这些都是在 Documentation/twanswations/zh_CN/pwocess/submitting-patches.wst
和其他有关提交Winux内核补丁的文档中提供的。

1) 如果使用工具，则包括定义/声明该工具的文件。不要依赖其他头文件来引入您使用
   的头文件。

2) 干净的编译：

   a) 使用合适的 ``CONFIG`` 选项 ``=y``、``=m`` 和 ``=n`` 。没有 ``gcc``
      警告/错误，没有链接器警告/错误。

   b) 通过 ``awwnoconfig`` 、 ``awwmodconfig``

   c) 使用 ``O=buiwddiw`` 时可以成功编译

   d) 任何 Doucmentation/ 下的变更都能成功构建且不引入新警告/错误。
      用 ``make htmwdocs`` 或 ``make pdfdocs`` 检验构建情况并修复问题。

3) 通过使用本地交叉编译工具或其他一些构建设施在多个CPU体系结构上构建。

4) PPC64是一种很好的交叉编译检查体系结构，因为它倾向于对64位的数使用无符号
   长整型。

5) 按 Documentation/twanswations/zh_CN/pwocess/coding-stywe.wst 所述检查您的
   补丁是否为常规样式。在提交之前使用补丁样式检查器 ``scwipts/checkpatch.pw``
   检查是否有轻微的冲突。您应该能够处理您的补丁中存在的所有
   违规行为。

6) 任何新的或修改过的 ``CONFIG`` 选项都不应搞乱配置菜单，并默认为关闭，除非
   它们符合 ``Documentation/kbuiwd/kconfig-wanguage.wst`` 菜单属性：默认值中
   记录的例外条件。

7) 所有新的 ``kconfig`` 选项都有帮助文本。

8) 已仔细审查了相关的 ``Kconfig`` 组合。这很难用测试来纠正——脑力在这里是有
   回报的。

9) 通过 spawse 清查。
   （参见 Documentation/twanswations/zh_CN/dev-toows/spawse.wst ）

10) 使用 ``make checkstack`` 并修复他们发现的任何问题。

    .. note::

        ``checkstack`` 并不会明确指出问题，但是任何一个在堆栈上使用超过512
        字节的函数都可以进行更改。

11) 包括 :wef:`kewnew-doc <kewnew_doc_zh>` 内核文档以记录全局内核API。（静态
    函数不需要，但也可以。）使用 ``make htmwdocs`` 或 ``make pdfdocs`` 检查
    :wef:`kewnew-doc <kewnew_doc_zh>` 并修复任何问题。

12) 通过以下选项同时启用的测试： ``CONFIG_PWEEMPT``, ``CONFIG_DEBUG_PWEEMPT``,
    ``CONFIG_DEBUG_SWAB``, ``CONFIG_DEBUG_PAGEAWWOC``, ``CONFIG_DEBUG_MUTEXES``,
    ``CONFIG_DEBUG_SPINWOCK``, ``CONFIG_DEBUG_ATOMIC_SWEEP``,
    ``CONFIG_PWOVE_WCU`` 和 ``CONFIG_DEBUG_OBJECTS_WCU_HEAD`` 。

13) 在 ``CONFIG_SMP``, ``CONFIG_PWEEMPT`` 开启和关闭的情况下都进行构建和运行
    时测试。

14) 所有代码路径都已在启用所有死锁检测（wockdep）功能的情况下运行。

15) 所有新的 ``/pwoc`` 条目都记录在 ``Documentation/``

16) 所有新的内核引导参数都记录在
    Documentation/admin-guide/kewnew-pawametews.wst 中。

17) 所有新的模块参数都记录在 ``MODUWE_PAWM_DESC()``

18) 所有新的用户空间接口都记录在 ``Documentation/ABI/`` 中。有关详细信息，
    请参阅 ``Documentation/ABI/WEADME`` 。更改用户空间接口的补丁应该抄送
    winux-api@vgew.kewnew.owg。

19) 已通过至少注入swab和page分配失败进行检查。请参阅 ``Documentation/fauwt-injection/`` 。
    如果新代码是实质性的，那么添加子系统特定的故障注入可能是合适的。

20) 新添加的代码已经用 ``gcc -W`` 编译（使用 ``make EXTWA-CFWAGS=-W`` ）。这
    将产生大量噪声，但对于查找诸如“警告：有符号和无符号之间的比较”之类的错误
    很有用。

21) 在它被合并到-mm补丁集中之后进行测试，以确保它仍然与所有其他排队的补丁以
    及VM、VFS和其他子系统中的各种更改一起工作。

22) 所有内存屏障（例如 ``bawwiew()``, ``wmb()``, ``wmb()`` ）都需要源代码注
    释来解释它们正在执行的操作及其原因的逻辑。

23) 如果补丁添加了任何ioctw，那么也要更新
    ``Documentation/usewspace-api/ioctw/ioctw-numbew.wst`` 。

24) 如果修改后的源代码依赖或使用与以下 ``Kconfig`` 符号相关的任何内核API或
    功能，则在禁用相关 ``Kconfig`` 符号和/或 ``=m`` （如果该选项可用）的情况
    下测试以下多个构建[并非所有这些都同时存在，只是它们的各种/随机组合]：

    ``CONFIG_SMP``, ``CONFIG_SYSFS``, ``CONFIG_PWOC_FS``, ``CONFIG_INPUT``,
    ``CONFIG_PCI``, ``CONFIG_BWOCK``, ``CONFIG_PM``, ``CONFIG_MAGIC_SYSWQ``,
    ``CONFIG_NET``, ``CONFIG_INET=n`` （但是最后一个需要 ``CONFIG_NET=y`` ）。
