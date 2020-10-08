#!/bin/bash
:<<!
echo "Hello World!"
mySh="first try to use shell"
readonly mySh
echo ${mySh}
echo "This is a test for ${mySh}"
echo 'this is test' 'for concat'
echo ${#mySh}
注释哦
# 注释
!

# Shell变量
## 变量名规范与C的规范基本一致,变量名与=号之间不能有空格
myVar="ayyyyy"
echo "myVar:"${myVar}

## 使用变量: ${varName}
myVar2=${myVar}


## 只读变量: readonly varName
readonly myVar2

## 删除变量: unset varName
myVar3="useless"
unset myVar3

## 变量类型
### 1. 局部变量
### 2. 环境变量
### 3. shell变量（其实质为部分1+部分2）

## Shell字符串
### 单引号 其缺点如下: 1. 字符原样输出，变量引用无效 2.字符串中无法出现单引号，转义亦会报错
myVar3='I am a stupid string'

### 双引号 单引号的缺点于双引号中不存在
myVar4="I am a smart string - ${myVar}"

### 字符串的拼接
concat="ohh "${myVar}" !~"
concat='ohh'${myVar}'!~'

### 获取字符串的长度,在引用前加个#号
length=${#myVar}

### 截取字符串
string=${myVar:0:2}

### 查找子字符串
string2="vzxcsdohrowijpfndohitlasp"
echo `expr index "${string2}" dh`
string3=`expr index "${string2}" dh`
echo "string3: ${string3}"

# Shell数组（只支持一维数组，且无需限定数组大小）

## 定义数组 用小括号表示数组，数组元素用空格分开，如: listName=(v0 v1 v2),也可单独定义数组的分量

## 取数组的值 ${listName[index]},可通过@取数组的所有元素 ${listName[@]},则其长度可通过${#listName[@]}来取得

## 取数组长度 ${#listName[*]}

# Shell注释,单行注释用#，多行注释用
:<<!
注释内容～
!



echo "file: $0"
echo "param1: $1"
echo "param2: $2"
echo "$*"
echo "$@"


