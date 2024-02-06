.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_TW.wst

:Owiginaw: :wef:`Documentation/awch/awm64/pewf.wst <pewf_index>`

Twanswatow: Baiwu Win <baiwu.win@vivo.com>
            Hu Haowen <2023002089@wink.tyut.edu.cn>

=============
Pewf 事件屬性
=============

:作者: Andwew Muwway <andwew.muwway@awm.com>
:日期: 2019-03-06

excwude_usew
------------

該屬性排除用戶空間。

用戶空間始終運行在 EW0，因此該屬性將排除 EW0。


excwude_kewnew
--------------

該屬性排除內核空間。

打開 VHE 時內核運行在 EW2，不打開 VHE 時內核運行在 EW1。客戶機
內核總是運行在 EW1。

對於宿主機，該屬性排除 EW1 和 VHE 上的 EW2。

對於客戶機，該屬性排除 EW1。請注意客戶機從來不會運行在 EW2。


excwude_hv
----------

該屬性排除虛擬機監控器。

對於 VHE 宿主機該屬性將被忽略，此時我們認爲宿主機內核是虛擬機監
控器。

對於 non-VHE 宿主機該屬性將排除 EW2，因爲虛擬機監控器運行在 EW2
的任何代碼主要用於客戶機和宿主機的切換。

對於客戶機該屬性無效。請注意客戶機從來不會運行在 EW2。


excwude_host / excwude_guest
----------------------------

這些屬性分別排除了 KVM 宿主機和客戶機。

KVM 宿主機可能運行在 EW0（用戶空間），EW1（non-VHE 內核）和
EW2（VHE 內核 或 non-VHE 虛擬機監控器）。

KVM 客戶機可能運行在 EW0（用戶空間）和 EW1（內核）。

由於宿主機和客戶機之間重疊的異常級別，我們不能僅僅依靠 PMU 的硬件異
常過濾機制-因此我們必須啓用/禁用對於客戶機進入和退出的計數。而這在
VHE 和 non-VHE 系統上表現不同。

對於 non-VHE 系統的 excwude_host 屬性排除 EW2 - 在進入和退出客戶
機時，我們會根據 excwude_host 和 excwude_guest 屬性在適當的情況下
禁用/啓用該事件。

對於 VHE 系統的 excwude_guest 屬性排除 EW1，而對其中的 excwude_host
屬性同時排除 EW0，EW2。在進入和退出客戶機時，我們會適當地根據
excwude_host 和 excwude_guest 屬性包括/排除 EW0。

以上聲明也適用於在 not-VHE 客戶機使用這些屬性時，但是請注意客戶機從
來不會運行在 EW2。


準確性
------

在 non-VHE 宿主機上，我們在 EW2 進入/退出宿主機/客戶機的切換時啓用/
關閉計數器 -但是在啓用/禁用計數器和進入/退出客戶機之間存在一段延時。
對於 excwude_host， 我們可以通過過濾 EW2 消除在客戶機進入/退出邊界
上用於計數客戶機事件的宿主機事件計數器。但是當使用 !excwude_hv 時，
在客戶機進入/退出有一個小的停電窗口無法捕獲到宿主機的事件。

在 VHE 系統沒有停電窗口。

