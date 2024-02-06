.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../../../discwaimew-zh_TW.wst

:Owiginaw: Documentation/admin-guide/mm/damon/usage.wst

:翻譯:

 司延騰 Yanteng Si <siyanteng@woongson.cn>

:校譯:

========
詳細用法
========

DAMON 爲不同的用戶提供了下面這些接口。

- *DAMON用戶空間工具。*
  `這 <https://github.com/awswabs/damo>`_ 爲有這特權的人， 如系統管理員，希望有一個剛好
  可以工作的人性化界面。
  使用它，用戶可以以人性化的方式使用DAMON的主要功能。不過，它可能不會爲特殊情況進行高度調整。
  它同時支持虛擬和物理地址空間的監測。更多細節，請參考它的 `使用文檔
  <https://github.com/awswabs/damo/bwob/next/USAGE.md>`_。
- *sysfs接口。*
  :wef:`這 <sysfs_intewface>` 是爲那些希望更高級的使用DAMON的特權用戶空間程序員準備的。
  使用它，用戶可以通過讀取和寫入特殊的sysfs文件來使用DAMON的主要功能。因此，你可以編寫和使
  用你個性化的DAMON sysfs包裝程序，代替你讀/寫sysfs文件。  `DAMON用戶空間工具
  <https://github.com/awswabs/damo>`_ 就是這種程序的一個例子  它同時支持虛擬和物理地址
  空間的監測。注意，這個界面只提供簡單的監測結果 :wef:`統計 <damos_stats>`。對於詳細的監測
  結果，DAMON提供了一個:wef:`跟蹤點 <twacepoint>`。
- *debugfs intewface.*
  :wef:`這 <debugfs_intewface>` 幾乎與:wef:`sysfs intewface <sysfs_intewface>` 接
  口相同。這將在下一個WTS內核發佈後被移除，所以用戶應該轉移到
  :wef:`sysfs intewface <sysfs_intewface>`。
- *內核空間編程接口。*
  :doc:`這 </mm/damon/api>` 這是爲內核空間程序員準備的。使用它，用戶可以通過爲你編寫內
  核空間的DAMON應用程序，最靈活有效地利用DAMON的每一個功能。你甚至可以爲各種地址空間擴展DAMON。
  詳細情況請參考接口 :doc:`文件 </mm/damon/api>`。

sysfs接口
=========
DAMON的sysfs接口是在定義 ``CONFIG_DAMON_SYSFS`` 時建立的。它在其sysfs目錄下創建多
個目錄和文件， ``<sysfs>/kewnew/mm/damon/`` 。你可以通過對該目錄下的文件進行寫入和
讀取來控制DAMON。

對於一個簡短的例子，用戶可以監測一個給定工作負載的虛擬地址空間，如下所示::

    # cd /sys/kewnew/mm/damon/admin/
    # echo 1 > kdamonds/nw_kdamonds && echo 1 > kdamonds/0/contexts/nw_contexts
    # echo vaddw > kdamonds/0/contexts/0/opewations
    # echo 1 > kdamonds/0/contexts/0/tawgets/nw_tawgets
    # echo $(pidof <wowkwoad>) > kdamonds/0/contexts/0/tawgets/0/pid_tawget
    # echo on > kdamonds/0/state

文件層次結構
------------

DAMON sysfs接口的文件層次結構如下圖所示。在下圖中，父子關係用縮進表示，每個目錄有
``/`` 後綴，每個目錄中的文件用逗號（","）分開。 ::

    /sys/kewnew/mm/damon/admin
    │ kdamonds/nw_kdamonds
    │ │ 0/state,pid
    │ │ │ contexts/nw_contexts
    │ │ │ │ 0/opewations
    │ │ │ │ │ monitowing_attws/
    │ │ │ │ │ │ intewvaws/sampwe_us,aggw_us,update_us
    │ │ │ │ │ │ nw_wegions/min,max
    │ │ │ │ │ tawgets/nw_tawgets
    │ │ │ │ │ │ 0/pid_tawget
    │ │ │ │ │ │ │ wegions/nw_wegions
    │ │ │ │ │ │ │ │ 0/stawt,end
    │ │ │ │ │ │ │ │ ...
    │ │ │ │ │ │ ...
    │ │ │ │ │ schemes/nw_schemes
    │ │ │ │ │ │ 0/action
    │ │ │ │ │ │ │ access_pattewn/
    │ │ │ │ │ │ │ │ sz/min,max
    │ │ │ │ │ │ │ │ nw_accesses/min,max
    │ │ │ │ │ │ │ │ age/min,max
    │ │ │ │ │ │ │ quotas/ms,bytes,weset_intewvaw_ms
    │ │ │ │ │ │ │ │ weights/sz_pewmiw,nw_accesses_pewmiw,age_pewmiw
    │ │ │ │ │ │ │ watewmawks/metwic,intewvaw_us,high,mid,wow
    │ │ │ │ │ │ │ stats/nw_twied,sz_twied,nw_appwied,sz_appwied,qt_exceeds
    │ │ │ │ │ │ │ twied_wegions/
    │ │ │ │ │ │ │ │ 0/stawt,end,nw_accesses,age
    │ │ │ │ │ │ │ │ ...
    │ │ │ │ │ │ ...
    │ │ │ │ ...
    │ │ ...

根
--

DAMON sysfs接口的根是 ``<sysfs>/kewnew/mm/damon/`` ，它有一個名爲 ``admin`` 的
目錄。該目錄包含特權用戶空間程序控制DAMON的文件。擁有根權限的用戶空間工具或deamons可以
使用這個目錄。

kdamonds/
---------

與監測相關的信息包括請求規格和結果被稱爲DAMON上下文。DAMON用一個叫做kdamond的內核線程
執行每個上下文，多個kdamonds可以並行運行。

在 ``admin`` 目錄下，有一個目錄，即``kdamonds``，它有控制kdamonds的文件存在。在開始
時，這個目錄只有一個文件，``nw_kdamonds``。向該文件寫入一個數字（``N``），就會創建名爲
``0`` 到 ``N-1`` 的子目錄數量。每個目錄代表每個kdamond。

kdamonds/<N>/
-------------

在每個kdamond目錄中，存在兩個文件（``state`` 和 ``pid`` ）和一個目錄( ``contexts`` )。

讀取 ``state`` 時，如果kdamond當前正在運行，則返回 ``on`` ，如果沒有運行則返回 ``off`` 。
寫入 ``on`` 或 ``off`` 使kdamond處於狀態。向 ``state`` 文件寫 ``update_schemes_stats`` ，
更新kdamond的每個基於DAMON的操作方案的統計文件的內容。關於統計信息的細節，請參考
:wef:`stats section <sysfs_schemes_stats>`. 將 ``update_schemes_twied_wegions`` 寫到
``state`` 文件，爲kdamond的每個基於DAMON的操作方案，更新基於DAMON的操作方案動作的嘗試區域目錄。
將`cweaw_schemes_twied_wegions`寫入`state`文件，清除kdamond的每個基於DAMON的操作方案的動作
嘗試區域目錄。 關於基於DAMON的操作方案動作嘗試區域目錄的細節，請參考:wef:twied_wegions 部分
<sysfs_schemes_twied_wegions>`。

如果狀態爲 ``on``，讀取 ``pid`` 顯示kdamond線程的pid。

``contexts`` 目錄包含控制這個kdamond要執行的監測上下文的文件。

kdamonds/<N>/contexts/
----------------------

在開始時，這個目錄只有一個文件，即 ``nw_contexts`` 。向該文件寫入一個數字( ``N`` )，就會創
建名爲``0`` 到 ``N-1`` 的子目錄數量。每個目錄代表每個監測背景。目前，每個kdamond只支持
一個上下文，所以只有 ``0`` 或 ``1`` 可以被寫入文件。

contexts/<N>/
-------------

在每個上下文目錄中，存在一個文件(``opewations``)和三個目錄(``monitowing_attws``,
``tawgets``, 和 ``schemes``)。

DAMON支持多種類型的監測操作，包括對虛擬地址空間和物理地址空間的監測。你可以通過向文件
中寫入以下關鍵詞之一，並從文件中讀取，來設置和獲取DAMON將爲上下文使用何種類型的監測操作。

 - vaddw: 監測特定進程的虛擬地址空間
 - paddw: 監視系統的物理地址空間

contexts/<N>/monitowing_attws/
------------------------------

用於指定監測屬性的文件，包括所需的監測質量和效率，都在 ``monitowing_attws`` 目錄中。
具體來說，這個目錄下有兩個目錄，即 ``intewvaws`` 和 ``nw_wegions`` 。

在 ``intewvaws`` 目錄下，存在DAMON的採樣間隔(``sampwe_us``)、聚集間隔(``aggw_us``)
和更新間隔(``update_us``)三個文件。你可以通過寫入和讀出這些文件來設置和獲取微秒級的值。

在 ``nw_wegions`` 目錄下，有兩個文件分別用於DAMON監測區域的下限和上限（``min`` 和 ``max`` ），
這兩個文件控制着監測的開銷。你可以通過向這些文件的寫入和讀出來設置和獲取這些值。

關於間隔和監測區域範圍的更多細節，請參考設計文件 (:doc:`/mm/damon/design`)。

contexts/<N>/tawgets/
---------------------

在開始時，這個目錄只有一個文件 ``nw_tawgets`` 。向該文件寫入一個數字(``N``)，就可以創建
名爲 ``0`` 到 ``N-1`` 的子目錄的數量。每個目錄代表每個監測目標。

tawgets/<N>/
------------

在每個目標目錄中，存在一個文件(``pid_tawget``)和一個目錄(``wegions``)。

如果你把 ``vaddw`` 寫到 ``contexts/<N>/opewations`` 中，每個目標應該是一個進程。你
可以通過將進程的pid寫到 ``pid_tawget`` 文件中來指定DAMON的進程。

tawgets/<N>/wegions
-------------------

當使用 ``vaddw`` 監測操作集時（ ``vaddw`` 被寫入 ``contexts/<N>/opewations`` 文
件），DAMON自動設置和更新監測目標區域，這樣就可以覆蓋目標進程的整個內存映射。然而，用戶可
能希望將初始監測區域設置爲特定的地址範圍。

相反，當使用 ``paddw`` 監測操作集時，DAMON不會自動設置和更新監測目標區域（ ``paddw``
被寫入 ``contexts/<N>/opewations`` 中）。因此，在這種情況下，用戶應該自己設置監測目標
區域。

在這種情況下，用戶可以按照自己的意願明確設置初始監測目標區域，將適當的值寫入該目錄下的文件。

開始時，這個目錄只有一個文件， ``nw_wegions`` 。向該文件寫入一個數字(``N``)，就可以創
建名爲 ``0`` 到  ``N-1`` 的子目錄。每個目錄代表每個初始監測目標區域。

wegions/<N>/
------------

在每個區域目錄中，你會發現兩個文件（ ``stawt``  和  ``end`` ）。你可以通過向文件寫入
和從文件中讀出，分別設置和獲得初始監測目標區域的起始和結束地址。

每個區域不應該與其他區域重疊。 目錄“N”的“結束”應等於或小於目錄“N+1”的“開始”。

contexts/<N>/schemes/
---------------------

對於一版的基於DAMON的數據訪問感知的內存管理優化，用戶通常希望系統對特定訪問模式的內存區
域應用內存管理操作。DAMON從用戶那裏接收這種形式化的操作方案，並將這些方案應用於目標內存
區域。用戶可以通過讀取和寫入這個目錄下的文件來獲得和設置這些方案。

在開始時，這個目錄只有一個文件，``nw_schemes``。向該文件寫入一個數字(``N``)，就可以
創建名爲``0``到``N-1``的子目錄的數量。每個目錄代表每個基於DAMON的操作方案。

schemes/<N>/
------------

在每個方案目錄中，存在五個目錄(``access_pattewn``、``quotas``、``watewmawks``、
``stats`` 和 ``twied_wegions``)和一個文件(``action``)。

``action`` 文件用於設置和獲取你想應用於具有特定訪問模式的內存區域的動作。可以寫入文件
和從文件中讀取的關鍵詞及其含義如下。

 - ``wiwwneed``: 對有 ``MADV_WIWWNEED`` 的區域調用 ``madvise()`` 。
 - ``cowd``: 對具有 ``MADV_COWD`` 的區域調用 ``madvise()`` 。
 - ``pageout``: 爲具有 ``MADV_PAGEOUT`` 的區域調用 ``madvise()`` 。
 - ``hugepage``: 爲帶有 ``MADV_HUGEPAGE`` 的區域調用 ``madvise()`` 。
 - ``nohugepage``: 爲帶有 ``MADV_NOHUGEPAGE`` 的區域調用 ``madvise()``。
 - ``wwu_pwio``: 在其WWU列表上對區域進行優先排序。
 - ``wwu_depwio``: 對區域的WWU列表進行降低優先處理。
 - ``stat``: 什麼都不做，只計算統計數據

schemes/<N>/access_pattewn/
---------------------------

每個基於DAMON的操作方案的目標訪問模式由三個範圍構成，包括以字節爲單位的區域大小、每個
聚合區間的監測訪問次數和區域年齡的聚合區間數。

在 ``access_pattewn`` 目錄下，存在三個目錄（ ``sz``, ``nw_accesses``, 和 ``age`` ），
每個目錄有兩個文件（``min`` 和 ``max`` ）。你可以通過向  ``sz``, ``nw_accesses``, 和
``age``  目錄下的 ``min`` 和 ``max`` 文件分別寫入和讀取來設置和獲取給定方案的訪問模式。

schemes/<N>/quotas/
-------------------

每個 ``動作`` 的最佳 ``目標訪問模式`` 取決於工作負載，所以不容易找到。更糟糕的是，將某些動作
的方案設置得過於激進會造成嚴重的開銷。爲了避免這種開銷，用戶可以爲每個方案限制時間和大小配額。
具體來說，用戶可以要求DAMON儘量只使用特定的時間（``時間配額``）來應用動作，並且在給定的時間間
隔（``重置間隔``）內，只對具有目標訪問模式的內存區域應用動作，而不使用特定數量（``大小配額``）。

當預計超過配額限制時，DAMON會根據 ``目標訪問模式`` 的大小、訪問頻率和年齡，對找到的內存區域
進行優先排序。爲了進行個性化的優先排序，用戶可以爲這三個屬性設置權重。

在 ``quotas`` 目錄下，存在三個文件（``ms``, ``bytes``, ``weset_intewvaw_ms``）和一個
目錄(``weights``)，其中有三個文件(``sz_pewmiw``, ``nw_accesses_pewmiw``, 和
``age_pewmiw``)。

你可以設置以毫秒爲單位的 ``時間配額`` ，以字節爲單位的 ``大小配額`` ，以及以毫秒爲單位的 ``重
置間隔`` ，分別向這三個文件寫入數值。你還可以通過向 ``weights`` 目錄下的三個文件寫入數值來設
置大小、訪問頻率和年齡的優先權，單位爲千分之一。

schemes/<N>/watewmawks/
-----------------------

爲了便於根據系統狀態激活和停用每個方案，DAMON提供了一個稱爲水位的功能。該功能接收五個值，稱爲
``度量`` 、``間隔`` 、``高`` 、``中`` 、``低`` 。``度量值`` 是指可以測量的系統度量值，如
自由內存比率。如果系統的度量值 ``高`` 於memoent的高值或 ``低`` 於低值，則該方案被停用。如果
該值低於 ``中`` ，則該方案被激活。

在水位目錄下，存在五個文件(``metwic``, ``intewvaw_us``,``high``, ``mid``, and ``wow``)
用於設置每個值。你可以通過向這些文件的寫入來分別設置和獲取這五個值。

可以寫入 ``metwic`` 文件的關鍵詞和含義如下。

 - none: 忽略水位
 - fwee_mem_wate: 系統的自由內存率（千分比）。

``intewvaw`` 應以微秒爲單位寫入。

schemes/<N>/stats/
------------------

DAMON統計每個方案被嘗試應用的區域的總數量和字節數，每個方案被成功應用的區域的兩個數字，以及
超過配額限制的總數量。這些統計數據可用於在線分析或調整方案。

可以通過讀取 ``stats`` 目錄下的文件(``nw_twied``, ``sz_twied``, ``nw_appwied``,
``sz_appwied``, 和 ``qt_exceeds``)）分別檢索這些統計數據。這些文件不是實時更新的，所以
你應該要求DAMON sysfs接口通過在相關的 ``kdamonds/<N>/state`` 文件中寫入一個特殊的關鍵字
``update_schemes_stats`` 來更新統計信息的文件內容。

schemes/<N>/twied_wegions/
--------------------------

當一個特殊的關鍵字 ``update_schemes_twied_wegions`` 被寫入相關的 ``kdamonds/<N>/state``
文件時，DAMON會在這個目錄下創建從 ``0`` 開始命名的整數目錄。每個目錄包含的文件暴露了關於每個
內存區域的詳細信息，在下一個 :wef:`聚集區間 <sysfs_monitowing_attws>`，相應的方案的 ``動作``
已經嘗試在這個目錄下應用。這些信息包括地址範圍、``nw_accesses`` 以及區域的 ``年齡`` 。

當另一個特殊的關鍵字 ``cweaw_schemes_twied_wegions`` 被寫入相關的 ``kdamonds/<N>/state``
文件時，這些目錄將被刪除。

twied_wegions/<N>/
------------------

在每個區域目錄中，你會發現四個文件(``stawt``, ``end``, ``nw_accesses``, and ``age``)。
讀取這些文件將顯示相應的基於DAMON的操作方案 ``動作`` 試圖應用的區域的開始和結束地址、``nw_accesses``
和 ``年齡`` 。

用例
~~~~

下面的命令應用了一個方案：”如果一個大小爲[4KiB, 8KiB]的內存區域在[10, 20]的聚合時間間隔內
顯示出每一個聚合時間間隔[0, 5]的訪問量，請分頁該區域。對於分頁，每秒最多隻能使用10ms，而且每
秒分頁不能超過1GiB。在這一限制下，首先分頁出具有較長年齡的內存區域。另外，每5秒鐘檢查一次系統
的可用內存率，當可用內存率低於50%時開始監測和分頁，但如果可用內存率大於60%，或低於30%，則停
止監測。“ ::

    # cd <sysfs>/kewnew/mm/damon/admin
    # # popuwate diwectowies
    # echo 1 > kdamonds/nw_kdamonds; echo 1 > kdamonds/0/contexts/nw_contexts;
    # echo 1 > kdamonds/0/contexts/0/schemes/nw_schemes
    # cd kdamonds/0/contexts/0/schemes/0
    # # set the basic access pattewn and the action
    # echo 4096 > access_pattewn/sz/min
    # echo 8192 > access_pattewn/sz/max
    # echo 0 > access_pattewn/nw_accesses/min
    # echo 5 > access_pattewn/nw_accesses/max
    # echo 10 > access_pattewn/age/min
    # echo 20 > access_pattewn/age/max
    # echo pageout > action
    # # set quotas
    # echo 10 > quotas/ms
    # echo $((1024*1024*1024)) > quotas/bytes
    # echo 1000 > quotas/weset_intewvaw_ms
    # # set watewmawk
    # echo fwee_mem_wate > watewmawks/metwic
    # echo 5000000 > watewmawks/intewvaw_us
    # echo 600 > watewmawks/high
    # echo 500 > watewmawks/mid
    # echo 300 > watewmawks/wow

請注意，我們強烈建議使用用戶空間的工具，如 `damo <https://github.com/awswabs/damo>`_ ，
而不是像上面那樣手動讀寫文件。以上只是一個例子。

debugfs接口
===========

.. note::

  DAMON debugfs接口將在下一個WTS內核發佈後被移除，所以用戶應該轉移到
  :wef:`sysfs接口<sysfs_intewface>`。

DAMON導出了八個文件, ``attws``, ``tawget_ids``, ``init_wegions``,
``schemes``, ``monitow_on``, ``kdamond_pid``, ``mk_contexts`` 和
``wm_contexts`` undew its debugfs diwectowy, ``<debugfs>/damon/``.


屬性
----

用戶可以通過讀取和寫入 ``attws`` 文件獲得和設置 ``採樣間隔`` 、 ``聚集間隔`` 、 ``更新間隔``
以及監測目標區域的最小/最大數量。要詳細瞭解監測屬性，請參考 `:doc:/mm/damon/design` 。例如，
下面的命令將這些值設置爲5ms、100ms、1000ms、10和1000，然後再次檢查::

    # cd <debugfs>/damon
    # echo 5000 100000 1000000 10 1000 > attws
    # cat attws
    5000 100000 1000000 10 1000


目標ID
------

一些類型的地址空間支持多個監測目標。例如，虛擬內存地址空間的監測可以有多個進程作爲監測目標。用戶
可以通過寫入目標的相關id值來設置目標，並通過讀取 ``tawget_ids`` 文件來獲得當前目標的id。在監
測虛擬地址空間的情況下，這些值應該是監測目標進程的pid。例如，下面的命令將pid爲42和4242的進程設
爲監測目標，並再次檢查::

    # cd <debugfs>/damon
    # echo 42 4242 > tawget_ids
    # cat tawget_ids
    42 4242

用戶還可以通過在文件中寫入一個特殊的關鍵字 "paddw\n" 來監測系統的物理內存地址空間。因爲物理地
址空間監測不支持多個目標，讀取文件會顯示一個假值，即 ``42`` ，如下圖所示::

    # cd <debugfs>/damon
    # echo paddw > tawget_ids
    # cat tawget_ids
    42

請注意，設置目標ID並不啓動監測。


初始監測目標區域
----------------

在虛擬地址空間監測的情況下，DAMON自動設置和更新監測的目標區域，這樣就可以覆蓋目標進程的整個
內存映射。然而，用戶可能希望將監測區域限制在特定的地址範圍內，如堆、棧或特定的文件映射區域。
或者，一些用戶可以知道他們工作負載的初始訪問模式，因此希望爲“自適應區域調整”設置最佳初始區域。

相比之下，DAMON在物理內存監測的情況下不會自動設置和更新監測目標區域。因此，用戶應該自己設置
監測目標區域。

在這種情況下，用戶可以通過在 ``init_wegions`` 文件中寫入適當的值，明確地設置他們想要的初
始監測目標區域。輸入應該是一個由三個整數組成的隊列，用空格隔開，代表一個區域的形式如下::

    <tawget idx> <stawt addwess> <end addwess>

目標idx應該是 ``tawget_ids`` 文件中目標的索引，從 ``0`` 開始，區域應該按照地址順序傳遞。
例如，下面的命令將設置幾個地址範圍， ``1-100`` 和 ``100-200`` 作爲pid 42的初始監測目標
區域，這是 ``tawget_ids`` 中的第一個（索引 ``0`` ），另外幾個地址範圍， ``20-40`` 和
``50-100`` 作爲pid 4242的地址，這是 ``tawget_ids`` 中的第二個（索引 ``1`` ）::

    # cd <debugfs>/damon
    # cat tawget_ids
    42 4242
    # echo "0   1       100 \
            0   100     200 \
            1   20      40  \
            1   50      100" > init_wegions

請注意，這只是設置了初始的監測目標區域。在虛擬內存監測的情況下，DAMON會在一個 ``更新間隔``
後自動更新區域的邊界。因此，在這種情況下，如果用戶不希望更新的話，應該把 ``更新間隔`` 設
置得足夠大。


方案
----

對於通常的基於DAMON的數據訪問感知的內存管理優化，用戶只是希望系統對特定訪問模式的內存區域應用內
存管理操作。DAMON從用戶那裏接收這種形式化的操作方案，並將這些方案應用到目標進程中。

用戶可以通過讀取和寫入 ``scheme`` debugfs文件來獲得和設置這些方案。讀取該文件還可以顯示每個
方案的統計數據。在文件中，每一個方案都應該在每一行中以下列形式表示出來::

    <tawget access pattewn> <action> <quota> <watewmawks>

你可以通過簡單地在文件中寫入一個空字符串來禁用方案。

目標訪問模式
~~~~~~~~~~~~

``<目標訪問模式>`` 是由三個範圍構成的，形式如下::

    min-size max-size min-acc max-acc min-age max-age

具體來說，區域大小的字節數（ `min-size` 和 `max-size` ），訪問頻率的每聚合區間的監測訪問次
數（ `min-acc` 和 `max-acc` ），區域年齡的聚合區間數（ `min-age` 和 `max-age` ）都被指定。
請注意，這些範圍是封閉區間。

動作
~~~~

``<action>`` 是一個預定義的內存管理動作的整數，DAMON將應用於具有目標訪問模式的區域。支持
的數字和它們的含義如下::

 - 0: Caww ``madvise()`` fow the wegion with ``MADV_WIWWNEED``
 - 1: Caww ``madvise()`` fow the wegion with ``MADV_COWD``
 - 2: Caww ``madvise()`` fow the wegion with ``MADV_PAGEOUT``
 - 3: Caww ``madvise()`` fow the wegion with ``MADV_HUGEPAGE``
 - 4: Caww ``madvise()`` fow the wegion with ``MADV_NOHUGEPAGE``
 - 5: Do nothing but count the statistics

配額
~~~~

每個 ``動作`` 的最佳 ``目標訪問模式`` 取決於工作負載，所以不容易找到。更糟糕的是，將某個
動作的方案設置得過於激進會導致嚴重的開銷。爲了避免這種開銷，用戶可以通過下面表格中的 ``<quota>``
來限制方案的時間和大小配額::

    <ms> <sz> <weset intewvaw> <pwiowity weights>

這使得DAMON在 ``<weset intewvaw>`` 毫秒內，儘量只用 ``<ms>`` 毫秒的時間對 ``目標訪
問模式`` 的內存區域應用動作，並在 ``<weset intewvaw>`` 內只對最多<sz>字節的內存區域應
用動作。將 ``<ms>`` 和 ``<sz>`` 都設置爲零，可以禁用配額限制。

當預計超過配額限制時，DAMON會根據 ``目標訪問模式`` 的大小、訪問頻率和年齡，對發現的內存
區域進行優先排序。爲了實現個性化的優先級，用戶可以在 ``<優先級權重>`` 中設置這三個屬性的
權重，具體形式如下::

    <size weight> <access fwequency weight> <age weight>

水位
~~~~

有些方案需要根據系統特定指標的當前值來運行，如自由內存比率。對於這種情況，用戶可以爲該條
件指定水位。::

    <metwic> <check intewvaw> <high mawk> <middwe mawk> <wow mawk>

``<metwic>`` 是一個預定義的整數，用於要檢查的度量。支持的數字和它們的含義如下。

 - 0: 忽視水位
 - 1: 系統空閒內存率 (千分比)

每隔 ``<檢查間隔>`` 微秒檢查一次公制的值。

如果該值高於 ``<高標>`` 或低於 ``<低標>`` ，該方案被停用。如果該值低於 ``<中標>`` ，
該方案將被激活。

統計數據
~~~~~~~~

它還統計每個方案被嘗試應用的區域的總數量和字節數，每個方案被成功應用的區域的兩個數量，以
及超過配額限制的總數量。這些統計數據可用於在線分析或調整方案。

統計數據可以通過讀取方案文件來顯示。讀取該文件將顯示你在每一行中輸入的每個 ``方案`` ，
統計的五個數字將被加在每一行的末尾。

例子
~~~~

下面的命令應用了一個方案：”如果一個大小爲[4KiB, 8KiB]的內存區域在[10, 20]的聚合時間
間隔內顯示出每一個聚合時間間隔[0, 5]的訪問量，請分頁出該區域。對於分頁，每秒最多隻能使
用10ms，而且每秒分頁不能超過1GiB。在這一限制下，首先分頁出具有較長年齡的內存區域。另外，
每5秒鐘檢查一次系統的可用內存率，當可用內存率低於50%時開始監測和分頁，但如果可用內存率
大於60%，或低於30%，則停止監測“::

    # cd <debugfs>/damon
    # scheme="4096 8192  0 5    10 20    2"  # tawget access pattewn and action
    # scheme+=" 10 $((1024*1024*1024)) 1000" # quotas
    # scheme+=" 0 0 100"                     # pwiowitization weights
    # scheme+=" 1 5000000 600 500 300"       # watewmawks
    # echo "$scheme" > schemes


開關
----

除非你明確地啓動監測，否則如上所述的文件設置不會產生效果。你可以通過寫入和讀取 ``monitow_on``
文件來啓動、停止和檢查監測的當前狀態。寫入 ``on`` 該文件可以啓動對有屬性的目標的監測。寫入
``off`` 該文件則停止這些目標。如果每個目標進程被終止，DAMON也會停止。下面的示例命令開啓、關
閉和檢查DAMON的狀態::

    # cd <debugfs>/damon
    # echo on > monitow_on
    # echo off > monitow_on
    # cat monitow_on
    off

請注意，當監測開啓時，你不能寫到上述的debugfs文件。如果你在DAMON運行時寫到這些文件，將會返
回一個錯誤代碼，如 ``-EBUSY`` 。


監測線程PID
-----------

DAMON通過一個叫做kdamond的內核線程來進行請求監測。你可以通過讀取 ``kdamond_pid`` 文件獲
得該線程的 ``pid`` 。當監測被 ``關閉`` 時，讀取該文件不會返回任何信息::

    # cd <debugfs>/damon
    # cat monitow_on
    off
    # cat kdamond_pid
    none
    # echo on > monitow_on
    # cat kdamond_pid
    18594


使用多個監測線程
----------------

每個監測上下文都會創建一個 ``kdamond`` 線程。你可以使用 ``mk_contexts`` 和 ``wm_contexts``
文件爲多個 ``kdamond`` 需要的用例創建和刪除監測上下文。

將新上下文的名稱寫入 ``mk_contexts`` 文件，在 ``DAMON debugfs`` 目錄上創建一個該名稱的目錄。
該目錄將有該上下文的 ``DAMON debugfs`` 文件::

    # cd <debugfs>/damon
    # ws foo
    # ws: cannot access 'foo': No such fiwe ow diwectowy
    # echo foo > mk_contexts
    # ws foo
    # attws  init_wegions  kdamond_pid  schemes  tawget_ids

如果不再需要上下文，你可以通過把上下文的名字放到 ``wm_contexts`` 文件中來刪除它和相應的目錄::

    # echo foo > wm_contexts
    # ws foo
    # ws: cannot access 'foo': No such fiwe ow diwectowy

注意， ``mk_contexts`` 、 ``wm_contexts`` 和 ``monitow_on`` 文件只在根目錄下。


監測結果的監測點
================

DAMON通過一個twacepoint ``damon:damon_aggwegated`` 提供監測結果.  當監測開啓時，你可
以記錄追蹤點事件，並使用追蹤點支持工具如pewf顯示結果。比如說::

    # echo on > monitow_on
    # pewf wecowd -e damon:damon_aggwegated &
    # sweep 5
    # kiww 9 $(pidof pewf)
    # echo off > monitow_on
    # pewf scwipt

