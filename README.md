# MS-DAYOLO
This is offical implementation of [Multiscale Domain Adaptive YOLO (MS-DAYOLO) for Cross-Domain Object Detection](https://ieeexplore.ieee.org/document/9506039) based on Darknet (YOLOv4).

## Installation
Please follow the instruction in [AlexeyAB/darknet](https://github.com/AlexeyAB/darknet) to install the requirments to compile Darkent and use YOLOv4 object detector. 

## Example Usage
Please follow these steps to adpate from KITTI dataset to Cityscapes dataset using MS-DAYOLO:

1. Run `make` to compile Darknet with MS-DAYOLO.
2. Download the pre-trained weights-file: [yolov4.conv.137](https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.conv.137).
3. Download the required data file which has source set with annotation, target set (with dummy annotation), and test target set with annotation.
4. Extract the file in data folder.

5. Train MS-DAYOLO by running this comment:
```
./darknet detector train data/k2c.data cfg/ms-dayolo.cfg yolov4.conv.137 -dont_show -map -da
```




## Citation
```
@INPROCEEDINGS{ms-dayolo,
  author={Hnewa, Mazin and Radha, Hayder},
  booktitle={2021 IEEE International Conference on Image Processing (ICIP)}, 
  title={Multiscale Domain Adaptive Yolo For Cross-Domain Object Detection}, 
  year={2021},
  pages={3323-3327}}
```
