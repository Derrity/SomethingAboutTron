# Easy way to "BOOM" Tron balance


## Define 声明


***本项目仅娱乐作用!任何事情与作者无关!***

***This project is for entertainment purposes only! The author is not responsible for anything!***

## Before

**You Must have Blockchair API Key**

1. Clone this repository

   ```bash
   git clone https://github.com/Derrity/SomethingAboutTron.git
   cd SomethingAboutTron
   git submodule init
   git submodule update
   ```

   Edit the `install.sh`

   change the content of `config.json` of v2ray to your own

   but don't change the `HTTP port`

   run the `install.sh`

   ```bash
   chmod +x install.sh
   sh install.sh
   ```

   and wait one ~~(two three....)~~ minute

2. Build this

   ```bash
   mkdir -p build
   cd build
   cmake ..
   make -j
   ```

3. Move `checktronbalance` to anywhere you want

   but make sure the `generateAddress/wordlist.txt` is at the same path with `checktronbalance`

## Last but not Least


You can contact me by email:

derrity0731@gmail.com

or

Take the [Github issue](https://github.com/Derrity/generateAddress/issues).

or 

Telegram: [@Derrity](https://t.me/Derrity)