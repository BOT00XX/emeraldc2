  绿宝石反编译汉化

该项目完全开源
允许各位以任何形式使用里面的资源
分支介绍
 master:主分支
    比原版的基础加了Z招式
        汉化了的
    合并了其他的所有分支

pokeemerald:汉化分支
    只比原版的基础多了汉化，没汉化的话就不更新

battle_engine:战斗引擎分支
    有mega进化，等一堆后时代战斗中的系统
    没有z招式
	    要使用Z招式建议使用主分支
	    或者合并 https://github.com/ghoulslash/pokeemerald/tree/zmove 
	       不过没汉化
    没有极巨化
   比原版多了汉化

item_expansion:道具扩充
    后世代的道具
    比原版多了汉化

pokemon_expansion:精灵扩充
    后世代的精灵
    比原版多了汉化

 1.battle_engine
 2.item_expansion
 3.pokemon_expansion
  分支不能单独编译，会报错
  必须合并pokeemerald分支


   编译方法

 以下三个选项根据说明选择
						第一次用电脑编译，第一次编译该项目
下载devkitpro https://github.com/devkitPro/installer/releases
安装特别选择GBA，其他可不选
安装好了
打开 C:\devkitPro\msys2的msys2_shell.bat.这个文件
输入 pacman -S make gcc zlib-devel git
输入y
下载libpng https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download
输入 cd Downloads
输入tar xf libpng-1.6.37.tar.xz
输入cd libpng-1.6.37
输入./configure --prefix=/usr
输入make check
输入make install
输入cd
输入git clone https://github.com/pret/pokeemerald
输入git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh 项目地址
cd 项目地址
make
						第二次在电脑上编译pokeemerald/pokeruby/pokefirered
cd agbcc
./install.sh 项目地址
						要编译的项目在电脑编译过
cd 项目地址
make

						地址（因为地址需要改成这种"/"斜杠“方便储存”）
