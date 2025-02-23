環境構築
raspberry piを用意
sudo apt install net-tools vim openssh-server git wget curl make build-essential
sudo apt-get update
sudo apt-get install -y libatlas-base-dev

＃openCVインストール
pip3 install -U pip
pip3 --default-timeout=1000 install opencv-python


pip3 install onnxruntime