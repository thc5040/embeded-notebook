1. 先到官网下载安装好，在电脑上安装好vs code，默认安装路径 一般是C:\Users\thc\AppData\Local\Programs\Microsoft VS Code
2. 在vscode官网 extension 提前下载 VSIX后缀的插件离线安装包， 如remote-ssh， c/c++等。离线安装到win上
3. 看版本号，看commit id，这是为了下载对应版本的 vscode-server-linux-x64.tar.gz

```
# 到如下网址下载
https://update.code.visualstudio.com/commit:${commit_id}/server-linux-x64/stable

https://update.code.visualstudio.com/commit:74f6148eb9ea00507ec113ec51c489d6ffb4b771/server-linux-x64/stable
```

3. vscode，左边栏 extensions 的... 中离线安装下载好的插件， install from VSIX
4. 在win自己的user目录下查看.ssh，（如果没有密钥可以用 sshkey gen生成），在config文件（没有后缀）添加ip 登录用户名信息，例如：

```
Host ubuntu
  HostName 192.168.1.128
  User thc
```

3. 先利用mobaXterm（或其他ssh登录终端）登录到服务器中，将vscode-server-linux送到服务器中，一键脚本如下：

```
commit_id=74f6148eb9ea00507ec113ec51c489d6ffb4b771
VSCODE_SERVER_PATH=/home/thc/Downloads/vscode-server-linux-x64.tar.gz
 
rm -rf ~/.vscode-server
mkdir -p ~/.vscode-server/bin
 
tar -xzf ${VSCODE_SERVER_PATH} -C ~/.vscode-server/bin
mv ~/.vscode-server/bin/vscode-server-linux-x64/ ~/.vscode-server/bin/${commit_id}/
 
mkdir -p ~/.vscode-server/extensions
cp -r ~/.vscode-server/bin/${commit_id}/extensions/* ~/.vscode-server/extensions

# 最后 ~/.vscode-server/bin目录下会有一个你的commit id 文件夹
```

4. 这时候vscode就可以通过最左下角的 open a remote window连接你的服务器了
5. 免密登录， 复制win用户.ssh文件中的 id_rsa.pub 密钥，在服务器的 ~/.ssh下新建一个 authorized_keys文件，将密钥复制到该文件中，就可以免密登录了。
6. 在vscode服务器内安装插件，也是跟win下安装插件同样的
7. 结束

