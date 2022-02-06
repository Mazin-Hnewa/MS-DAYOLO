# MS-DAYOLO
This is offical implementation of [Multiscale Domain Adaptive YOLO (MS-DAYOLO) for Cross-Domain Object Detection](https://ieeexplore.ieee.org/document/9506039) based on Darknet (YOLOv4).

## Installation
Please follow the instruction in [AlexeyAB/darknet](https://github.com/AlexeyAB/darknet) to install the requirments to compile Darkent and use YOLOv4 object detector. 

## Example Usage
Please follow these steps to adpate from KITTI dataset to Cityscapes dataset using MS-DAYOLO:

1- Run `make` to compile Darknet.

2- Download the pre-trained weights-file: [yolov4.conv.137](https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.conv.137).

3- Download the Kitti dataset and put the images and their annotation in data/source.

4- Download the Cityscapes training set and put the images and their dummy annotation in data/target.

5- Download the Cityscapes testing set and put the images and their annotation in data/val_target.



## Citation
```
@INPROCEEDINGS{ms-dayolo,
  author={Hnewa, Mazin and Radha, Hayder},
  booktitle={2021 IEEE International Conference on Image Processing (ICIP)}, 
  title={Multiscale Domain Adaptive Yolo For Cross-Domain Object Detection}, 
  year={2021},
  pages={3323-3327}}
```
