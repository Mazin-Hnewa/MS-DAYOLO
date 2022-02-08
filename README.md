# MS-DAYOLO
This is the official implementation of [Multiscale Domain Adaptive YOLO (MS-DAYOLO) for Cross-Domain Object Detection](https://ieeexplore.ieee.org/document/9506039) based on Darknet (YOLOv4).

## Installation
Please follow the instruction in [AlexeyAB/darknet](https://github.com/AlexeyAB/darknet) to install the requirements to compile Darkent and use YOLOv4 object detector. 

## Example Usage
Please follow these steps to adapt from Cityscapes to Foggy Cityscapes:

1. Run `make` to compile Darknet with MS-DAYOLO.
2. Download the pre-trained weights-file: [yolov4.conv.137](https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.conv.137).
3. Download the required data file [Cityscaples2Foggy.zip](https://drive.google.com/file/d/1NqXY9iXXQOCPvbYpS9l8Yk66-nGzlMwQ/view?usp=sharing) which has:
- source set with  ground-truth annotation
- target set (with dummy annotation)
- test target set with ground-truth annotation.
5. Extract the file in `data/` folder.
6. Train MS-DAYOLO:
```
./darknet detector train data/c2f.data cfg/ms-dayolo.cfg yolov4.conv.137 -dont_show -map -da
```
During training, the best weight will be saved in `backup/` folder.

6. If the best weight file does not be updated for a long time, stop the training.
7. After training is finished, evaluate the trained MS-DAYOLO:
```
./darknet detector map data/c2f.data cfg/ms-dayolo.cfg backup/ms-dayolo_best.weights
```
8. For comparison with the original YOLOv4, train it:
```
./darknet detector train data/c2f.data cfg/yolov4.cfg yolov4.conv.137 -dont_show -map
```
and evaluate the trained YOLOv4:
```
./darknet detector map data/c2f.data cfg/yolov4.cfg backup/yolov4_best.weights
```

## Results & Pretrained Weights
Adaptation from Cityscapes to Foggy Cityscapes
|Method| mAP|Pretrained Weights|
|---|---|---|
|YOLOv4|35.64|[download](https://drive.google.com/file/d/18__pgkEWbLAmTE1veYpgn6YG6NmU1P7u/view?usp=sharing)|
|MS-DAYOLO|43.04|[download](https://drive.google.com/file/d/1oTnIRw9kZOTcqJyhK0O3rwD0GZfGRPsP/view?usp=sharing)|


## Citation
```
@INPROCEEDINGS{ms-dayolo,
  author={Hnewa, Mazin and Radha, Hayder},
  booktitle={2021 IEEE International Conference on Image Processing (ICIP)}, 
  title={Multiscale Domain Adaptive Yolo For Cross-Domain Object Detection}, 
  year={2021},
  pages={3323-3327}}
```
