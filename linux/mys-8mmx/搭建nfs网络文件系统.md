+ 在开发主机上安装nfs服务器，并进行配置

```
#以下命令在主机上运行
sudo apt install nfs-kernel-server

# 在/etc/exports文件下末尾添加如下内容  /home/thc/nfsShare是共享文件夹  192.168.0.0/24这个表示ip为192.168.1.xxx的机器都可以挂在这个nfs文件系统上
/home/thc/nfsShare 192.168.1.0/24(rw,no_root_squash,no_subtree_check)

# 重新生效该文件
sudo exportfs -arv

# 查看nfs服务器加载情况
showmount -e
```

+ 在开发板上挂载nfs网络文件系统， 192.168.1.128是虚拟机的ip地址，使用桥接网络

```
# 安装nfs 客户端
sudo apt install nfs-common

# 查看
showmout -e 192.168.1.128

# 挂载
sudo mount -t nfs 192.168.1.128:/home/thc/nfsShare /mnt

# 取消挂载
sudo umount /mnt
```

