
from ultralytics import YOLO
import cv2
import math
import serial
import time

# Running real-time from webcam
cap = cv2.VideoCapture(0)

# Load COCO model for person detection
coco_model = YOLO('yolov8n.pt')

# Reading the classes
coco_classnames = coco_model.names

# Classes to include
included_classes = ['person', 'motorcycle', 'bicycle', 'truck', 'bus', 'car']

# Set up video writer
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))

# Set up serial communication with Arduino
ser = serial.Serial('COM3', 115200, timeout=1)

# Counter for each included class
class_counters = {class_name: 0 for class_name in included_classes}

# Threshold for continuous detection
continuous_threshold = 5  # Adjust as needed

def send_to_arduino(value):
    ser.write(value.encode())
    time.sleep(0.1)  # Reduce the delay to improve responsiveness

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.resize(frame, (640, 480))

    # Perform object detection using COCO model
    coco_result = coco_model(frame, stream=True)

    # Process results for specified classes
    for info in coco_result:
        boxes = info.boxes
        for box in boxes:
            confidence = box.conf[0]
            confidence = math.ceil(confidence * 100)
            Class = int(box.cls[0])
            class_name = coco_classnames[Class]
            if confidence > 10 and class_name in included_classes:
                # Draw bounding box
                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                # Increment counter for this class
                class_counters[class_name] += 1
                if class_counters[class_name] >= continuous_threshold:
                    send_to_arduino('A')
                    print("1")
                else:
                    send_to_arduino('B')
                    print("0")
            else:
                # Reset counter for this class if not detected
                #class_counters[class_name] = 0
                #if 'person' not in class_counters:  # Only send '0' if no person is detected
                    send_to_arduino('B')
                    print("0")


    out.write(frame)
    send_to_arduino('B')
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('d'):
        send_to_arduino('B')
        break

cap.release()
out.release()
cv2.destroyAllWindows()
ser.close()
