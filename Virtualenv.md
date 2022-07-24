ubuntu18.04 python3安装虚拟环境virtualenv
pip3 install virtualenv
pip3 install virtualenvwrapper
vim ~/.bashrc  以下三行加入到文件末尾
export VIRTUALENVWRAPPER_PYTHON=/usr/bin/python3
export WORKON_HOME=$HOME/.virtualenvs
source ~/.local/bin/virtualenvwrapper.sh
source ~/.bashrc
创建并进入虚拟环境
mkvirtualenv my_env -p /usr/bin/python3
进入/切换虚拟环境
workon my_env
退出当前虚拟环境
deactivate
删除虚拟环境
rmvirtualenv my_env
