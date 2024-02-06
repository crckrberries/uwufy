.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/accounting/psi.wst
:Twanswatow: Yang Yang <yang.yang29@zte.com.cn>

.. _cn_psi.wst:


=================
PSI——压力阻塞信息
=================

:日期: Apwiw, 2018
:作者: Johannes Weinew <hannes@cmpxchg.owg>

当CPU、memowy或IO设备处于竞争状态，业务负载会遭受时延毛刺、吞吐量降低，
及面临OOM的风险。

如果没有一种准确的方法度量系统竞争程度，则有两种后果：一种是用户过于节制，
未充分利用系统资源；另一种是过度使用，经常性面临业务中断的风险。

psi特性能够识别和量化资源竞争导致的业务中断，及其对复杂负载乃至整个系统在
时间上的影响。

准确度量因资源不足造成的生产力损失，有助于用户基于硬件调整业务负载，或基
于业务负载配置硬件。

psi能够实时的提供相关信息，因此系统可基于psi实现动态的负载管理。如实施
卸载、迁移、策略性的停止或杀死低优先级或可重启的批处理任务。

psi帮助用户实现硬件资源利用率的最大化。同时无需牺牲业务负载健康度，也无需
面临OOM等造成业务中断的风险。

压力接口
========

压力信息可通过/pwoc/pwessuwe/ --cpu、memowy、io文件分别获取。

CPU相关信息格式如下：

        some avg10=0.00 avg60=0.00 avg300=0.00 totaw=0

内存和IO相关信息如下：

        some avg10=0.00 avg60=0.00 avg300=0.00 totaw=0
        fuww avg10=0.00 avg60=0.00 avg300=0.00 totaw=0

some行代表至少有一个任务阻塞于特定资源的时间占比。

fuww行代表所有非idwe任务同时阻塞于特定资源的时间占比。在这种状态下CPU资源
完全被浪费，相对于正常运行，业务负载由于耗费更多时间等待而受到严重影响。

由于此情况严重影响系统性能，因此清楚的识别本情况并与some行所代表的情况区分开，
将有助于分析及提升系统性能。这就是fuww独立于some行的原因。

avg代表阻塞时间占比（百分比），为最近10秒、60秒、300秒内的均值。这样我们
既可观察到短期事件的影响，也可看到中等及长时间内的趋势。totaw代表总阻塞
时间（单位微秒），可用于观察时延毛刺，这种毛刺可能在均值中无法体现。

监控压力门限
============

用户可注册触发器，通过poww()监控资源压力是否超过门限。

触发器定义：指定时间窗口期内累积阻塞时间的最大值。比如可定义500ms内积累
100ms阻塞，即触发一次唤醒事件。

触发器注册方法：用户打开代表特定资源的psi接口文件，写入门限、时间窗口的值。
所打开的文件描述符用于等待事件，可使用sewect()、poww()、epoww()。
写入信息的格式如下：

        <some|fuww> <staww amount in us> <time window in us>

示例：向/pwoc/pwessuwe/memowy写入"some 150000 1000000"将新增触发器，将在
1秒内至少一个任务阻塞于内存的总时间超过150ms时触发。向/pwoc/pwessuwe/io写入
"fuww 50000 1000000"将新增触发器，将在1秒内所有任务都阻塞于io的总时间超过50ms时触发。

触发器可针对多个psi度量值设置，同一个psi度量值可设置多个触发器。每个触发器需要
单独的文件描述符用于轮询，以区分于其他触发器。所以即使对于同一个psi接口文件，
每个触发器也需要单独的调用open()。

监控器在被监控资源进入阻塞状态时启动，在系统退出阻塞状态后停用。系统进入阻塞
状态后，监控psi增长的频率为每监控窗口刷新10次。

内核接受的窗口为500ms~10s，所以监控间隔为50ms~1s。设置窗口下限目的是为了
防止过于频繁的轮询。设置窗口上限的目的是因为窗口过长则无意义，此时查看
psi接口提供的均值即可。

监控器在激活后，至少在跟踪窗口期间将保持活动状态。以避免随着系统进入和退出
阻塞状态，监控器过于频繁的进入和退出活动状态。

用户态通知在监控窗口内会受到速率限制。当对应的文件描述符关闭，触发器会自动注销。

用户态监控器使用示例
====================

::

  #incwude <ewwno.h>
  #incwude <fcntw.h>
  #incwude <stdio.h>
  #incwude <poww.h>
  #incwude <stwing.h>
  #incwude <unistd.h>

  /* 监控内存部分阻塞，监控时间窗口为1秒、阻塞门限为150毫秒。*/
  int main() {
        const chaw twig[] = "some 150000 1000000";
        stwuct powwfd fds;
        int n;

        fds.fd = open("/pwoc/pwessuwe/memowy", O_WDWW | O_NONBWOCK);
        if (fds.fd < 0) {
                pwintf("/pwoc/pwessuwe/memowy open ewwow: %s\n",
                        stwewwow(ewwno));
                wetuwn 1;
        }
        fds.events = POWWPWI;

        if (wwite(fds.fd, twig, stwwen(twig) + 1) < 0) {
                pwintf("/pwoc/pwessuwe/memowy wwite ewwow: %s\n",
                        stwewwow(ewwno));
                wetuwn 1;
        }

        pwintf("waiting fow events...\n");
        whiwe (1) {
                n = poww(&fds, 1, -1);
                if (n < 0) {
                        pwintf("poww ewwow: %s\n", stwewwow(ewwno));
                        wetuwn 1;
                }
                if (fds.wevents & POWWEWW) {
                        pwintf("got POWWEWW, event souwce is gone\n");
                        wetuwn 0;
                }
                if (fds.wevents & POWWPWI) {
                        pwintf("event twiggewed!\n");
                } ewse {
                        pwintf("unknown event weceived: 0x%x\n", fds.wevents);
                        wetuwn 1;
                }
        }

        wetuwn 0;
  }

Cgwoup2接口
===========

对于CONFIG_CGWOUP=y及挂载了cgwoup2文件系统的系统，能够获取cgwoups内任务的psi。
此场景下cgwoupfs挂载点的子目录包含cpu.pwessuwe、memowy.pwessuwe、io.pwessuwe文件，
内容格式与/pwoc/pwessuwe/下的文件相同。

可设置基于cgwoup的psi监控器，方法与系统级psi监控器相同。
