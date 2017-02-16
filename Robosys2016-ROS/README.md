# Robosys2016-ROS
Homework2
課題
* ROSで何か作る
* GitHubにパッケージを置く
* YouTube等に実行例をアップ
##作ったもの
* ROSでチャットプログラム

## 動画

* https://youtu.be/JQmrse2MlYk

##必要なもの
* Ubuntu 16.04 環境 raspberry pi 3
* ROS installed 環境
* byobu(複数の端末が必要な為)

* byobuのインストール
```
sudo apt update
sudo apt-get install byobu
```
* byobuの使い方　以下を参考 
* http://qiita.com/kayama0fa@github/items/82d3ebab8bb297bdfd23

## 動かし方
* まずroscoreを立ち上げる
```
roscore 
```
* 別端末を2つ開いて以下をそれぞれ用意
*  --   1つ目
```
rosrun hwpkg chatter_node.py __name:=alpha chatter2:=rec_A chatter1:=rec_B

```
 * --  2つ目
```
rosrun hwpkg chatter_node.py __name:=beta chatter1:=rec_A chatter2:=rec_B
```
* 後は任意の文字を入力すると別端末側にメッセージが届く
