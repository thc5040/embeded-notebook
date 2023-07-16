## docker安装

+ 先要将之前旧版本的docker彻底删掉
+ 需要先安装 gnome-terminal 

```
 sudo apt install gnome-terminal
```

+ 更新apt并且安装一些依赖

```
sudo apt-get update
sudo apt-get install \
    ca-certificates \
    curl \
    gnupg
```

+ 添加GPG密钥

```
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
```

+ 设置仓库仓库

```
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

+ 网上下载 docker desktop 的 deb包
+ 安装deb包

```
sudo apt-get update
sudo apt-get install ./docker-desktop-<version>-<arch>.deb
```

+ 安装完后，可以用图形界面打开docker desktop，也可以在终端打开，打开后可以使用一些docker命令测试

```
systemctl --user start docker-desktop

docker compose version
docker --version
docker version
```

+ 使能docker desktop可以通过图形界面的settings方式，但更方便的是用命令去使能服务

```
systemctl --user enable docker-desktop  # 使能

systemctl --user stop docker-desktop	# 失能
```





## 参考资料

+ 官方文档

https://docs.docker.com/desktop/install/ubuntu/