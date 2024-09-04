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
* [fn]キー＋１キーでファンクションキー1
* ...
* [fn]キー＋0キーでファンクションキー10
* [fn]キー＋[x]キー(bsキー）でファンクションキー11
* [fn]キー＋[tab]キーでファンクションキー12
* [x]キーはDeleteキーに割り当てた。
* [fn]キー、[Sym]キー、[↑]キーはダブルクリックで固定される。
  
* M5StampS3の本体のボタンを1回押すと赤色のＬＥＤが点滅してCtrlキーを押した状態になる。
* 2回押すと緑色のＬＥＤが点滅してAltキーを押した状態になる。
* 3回押すとノーマル状態に戻る。

# コンパイル
* Arduino IDEを使ってコンパイルした
