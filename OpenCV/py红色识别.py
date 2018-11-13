import cv2
import numpy as np

cap = cv2.VideoCapture('F:\\out.avi')

while(1):

    # 读取视频的每一帧
    _, frame = cap.read()

    # 将图片从 BGR 空间转换到 HSV 空间
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 定义在HSV空间中红色的范围
    lower_blue = np.array([156,43,46])
    upper_blue = np.array([180,255,255])

    # 根据以上定义的红色的阈值得到红色的部分
    mask = cv2.inRange(hsv, lower_blue, upper_blue)

    res = cv2.bitwise_and(frame,frame, mask= mask)

    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('res',res)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()