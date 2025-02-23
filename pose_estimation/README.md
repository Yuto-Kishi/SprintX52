仮想環境構築
python3 -m venv pose
source pose/bin/activate

pip3 install onnxruntime
(pose) kyuto@rasp:~/pose_estimation $ mkdir model
(pose) kyuto@rasp:~/pose_estimation $ cd model
(pose) kyuto@rasp:~/pose_estimation/model $ ls -lrt
~/pose_estimation/
┗pose.py
┗model
　　┗ model_float32.onnx

execute!
(pose) kyuto@rasp:~/pose_estimation/model $ python3 pose.py
