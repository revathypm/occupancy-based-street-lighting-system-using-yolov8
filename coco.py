from ultralytics import YOLO
import cv2
import math

# Running real-time from webcam
cap = cv2.VideoCapture("firing.mp4")

# Load COCO model for person detection
coco_model = YOLO('yolov8n.pt')

# Reading the classes
coco_classnames = coco_model.names

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, (640, 480))

    # Perform person detection using COCO model
    coco_result = coco_model(frame, stream=True)

    # Process results for person detection
    for info in coco_result:
        boxes = info.boxes
        for box in boxes:
            confidence = box.conf[0]
            confidence = math.ceil(confidence * 100)
            Class = int(box.cls[0])
            if confidence > 20 and coco_classnames[Class] == 'person':
                # Your code for person detection goes here
                pass

    cv2.imshow('frame', frame)
    cv2.waitKey(1)

    if cv2.waitKey(20) & 0xFF == ord('d'):
        break

cap.release()
cv2.destroyAllWindows()
