# the tools needed
sudo apt-get update
sudo apt-get -y install cmake curl
sudo apt-get -y install libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev
sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get -y install libxvidcore-dev libx264-dev
sudo apt-get -y install qt4-dev-tools 
sudo apt-get -y install libatlas-base-dev
# download the TensorFlow version (2.6.0)
wget -O tensorflow.zip https://github.com/tensorflow/tensorflow/archive/v2.6.0.zip
# unpack and give the folder a convenient name
unzip tensorflow.zip
mv tensorflow-2.6.0 tensorflow
cd tensorflow
# get the dependencies
./tensorflow/lite/tools/make/download_dependencies.sh
# run the C++ installation (± 25 min)
./tensorflow/lite/tools/make/build_rpi_lib.sh

# remove the 'old' flatbuffers
cd tensorflow/lite/tools/make/downloads
rm -rf flatbuffers
# download the latest flatbuffers
git clone --depth=1 --recursive https://github.com/google/flatbuffers.git
cd flatbuffers
mkdir build
cd build
cmake ..
make -j4
sudo make install
sudo ldconfig

mkdir -p ~/working
cd ~/working
git clone https://github.com/EdjeElectronics/TensorFlow-Lite-Object-Detection-on-Android-and-Raspberry-Pi.git TFLite_example
cd TFLite_example
wget https://storage.googleapis.com/download.tensorflow.org/models/tflite/coco_ssd_mobilenet_v1_1.0_quant_2018_06_29.zip
unzip coco_ssd_mobilenet_v1_1.0_quant_2018_06_29.zip

version=$(python3 -c 'import sys; print(".".join(map(str, sys.version_info[:2])))')

if [ $version == "3.9" ]; then
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp39-cp39-linux_armv7l.whl
fi

if [ $version == "3.8" ]; then
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp38-cp38-linux_armv7l.whl
fi

if [ $version == "3.7" ]; then
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp37-cp37m-linux_armv7l.whl
fi

if [ $version == "3.6" ]; then
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp36-cp36m-linux_armv7l.whl
fi

if [ $version == "3.5" ]; then
pip3 install https://github.com/google-coral/pycoral/releases/download/release-frogfish/tflite_runtime-2.5.0-cp35-cp35m-linux_armv7l.whl
fi
