# M5Stackカード型キーボードをUSB化
![cardkb](https://github.com/user-attachments/assets/f7e06f58-538f-4a41-ac54-64a00dbc36e8)

# 機能
* M5StampS3とカードサイズキーボードを組み合わせ、パソコンのUSBキーボードとして機能させる。
* bluetoothキーボードしか持ってなくてもUEFIやBIOSの設定ができる。

# 必要なもの
* [CardKB Mini Keyboard Programmable Unit V1.1](https://shop.m5stack.com/products/cardkb-mini-keyboard-programmable-unit-v1-1-mega8a)

* [ M5Stamp ESP32S3 Module](https://shop.m5stack.com/products/m5stamp-esp32s3-module)
  ※M5シリーズでUSB-OTG機能があるものなら大体動くと思います。

# 使い方
- [fn]キー + 数字キーでファンクションキーを使用
  - [fn] + 1～0キー = F1～F10
  - [fn] + [BACKSPACE]キー (右上のキー) = F11
  - [fn] + [tab]キー = F12
- [fn]キー、[Sym]キー、[↑]キーはダブルクリックで固定
-  通常の[BACKSPACE]キーは biosに入りやすいように[Del]キーに割り当てた
- M5StampS3の本体ボタン：
  - 1回押す = Ctrlキー押下状態（赤色LED点滅）
  - 2回押す = Altキー押下状態（緑色LED点滅）
  - 3回押す = 通常状態

# コンパイル
* Arduino IDEを使ってコンパイルした
