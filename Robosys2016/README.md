# Robosys2016
Robosys2016-課題用-
課題
・講義で作ったデバイスドライバをカスタマイズ

##・やったこと

LED点滅を行うデバイスドライバにカスタマイズ

##・点滅関数を作成　

周期は　blink_timer.expires = jiffies + (1*HZ)のHZに掛ける値によって変化。

ex.
(1*HZ) => 1(s)　

(HZ/10) => 0.1(s)

今回は0.25(s)周期でLEDを点滅させている。

##・gpioの設定

・linux/gpio.hを利用してLED点滅をさせるためのピンを指定。

##・BlinkLEDのデモ動画

https://youtu.be/o3hiBZ-slsc


##動かし方
```
make //(コンパイル)
sudo insmod blinkled.ko
````
`
##終わり方
```
sudo rmmod blinkled 
make clean//(後始末)
