;; Auto-generated. Do not edit!


(when (boundp 'teleoperation::Status)
  (if (not (find-package "TELEOPERATION"))
    (make-package "TELEOPERATION"))
  (shadow 'Status (find-package "TELEOPERATION")))
(unless (find-package "TELEOPERATION::STATUS")
  (make-package "TELEOPERATION::STATUS"))

(in-package "ROS")
;;//! \htmlinclude Status.msg.html


(defclass teleoperation::Status
  :super ros::object
  :slots (_battery_level _current _ADC1 _ADC2 _ADC3 _ADC4 _speed_front_left _speed_front_right _odometry_left _odometry_right _version _relay1 ))

(defmethod teleoperation::Status
  (:init
   (&key
    ((:battery_level __battery_level) 0.0)
    ((:current __current) 0.0)
    ((:ADC1 __ADC1) 0)
    ((:ADC2 __ADC2) 0)
    ((:ADC3 __ADC3) 0)
    ((:ADC4 __ADC4) 0)
    ((:speed_front_left __speed_front_left) 0.0)
    ((:speed_front_right __speed_front_right) 0.0)
    ((:odometry_left __odometry_left) 0.0)
    ((:odometry_right __odometry_right) 0.0)
    ((:version __version) 0)
    ((:relay1 __relay1) 0)
    )
   (send-super :init)
   (setq _battery_level (float __battery_level))
   (setq _current (float __current))
   (setq _ADC1 (round __ADC1))
   (setq _ADC2 (round __ADC2))
   (setq _ADC3 (round __ADC3))
   (setq _ADC4 (round __ADC4))
   (setq _speed_front_left (float __speed_front_left))
   (setq _speed_front_right (float __speed_front_right))
   (setq _odometry_left (float __odometry_left))
   (setq _odometry_right (float __odometry_right))
   (setq _version (round __version))
   (setq _relay1 (round __relay1))
   self)
  (:battery_level
   (&optional __battery_level)
   (if __battery_level (setq _battery_level __battery_level)) _battery_level)
  (:current
   (&optional __current)
   (if __current (setq _current __current)) _current)
  (:ADC1
   (&optional __ADC1)
   (if __ADC1 (setq _ADC1 __ADC1)) _ADC1)
  (:ADC2
   (&optional __ADC2)
   (if __ADC2 (setq _ADC2 __ADC2)) _ADC2)
  (:ADC3
   (&optional __ADC3)
   (if __ADC3 (setq _ADC3 __ADC3)) _ADC3)
  (:ADC4
   (&optional __ADC4)
   (if __ADC4 (setq _ADC4 __ADC4)) _ADC4)
  (:speed_front_left
   (&optional __speed_front_left)
   (if __speed_front_left (setq _speed_front_left __speed_front_left)) _speed_front_left)
  (:speed_front_right
   (&optional __speed_front_right)
   (if __speed_front_right (setq _speed_front_right __speed_front_right)) _speed_front_right)
  (:odometry_left
   (&optional __odometry_left)
   (if __odometry_left (setq _odometry_left __odometry_left)) _odometry_left)
  (:odometry_right
   (&optional __odometry_right)
   (if __odometry_right (setq _odometry_right __odometry_right)) _odometry_right)
  (:version
   (&optional __version)
   (if __version (setq _version __version)) _version)
  (:relay1
   (&optional __relay1)
   (if __relay1 (setq _relay1 __relay1)) _relay1)
  (:serialization-length
   ()
   (+
    ;; float64 _battery_level
    8
    ;; float64 _current
    8
    ;; int32 _ADC1
    4
    ;; int32 _ADC2
    4
    ;; int32 _ADC3
    4
    ;; int32 _ADC4
    4
    ;; float64 _speed_front_left
    8
    ;; float64 _speed_front_right
    8
    ;; float64 _odometry_left
    8
    ;; float64 _odometry_right
    8
    ;; int32 _version
    4
    ;; int32 _relay1
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _battery_level
       (sys::poke _battery_level (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _current
       (sys::poke _current (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _ADC1
       (write-long _ADC1 s)
     ;; int32 _ADC2
       (write-long _ADC2 s)
     ;; int32 _ADC3
       (write-long _ADC3 s)
     ;; int32 _ADC4
       (write-long _ADC4 s)
     ;; float64 _speed_front_left
       (sys::poke _speed_front_left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_front_right
       (sys::poke _speed_front_right (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _odometry_left
       (sys::poke _odometry_left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _odometry_right
       (sys::poke _odometry_right (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _version
       (write-long _version s)
     ;; int32 _relay1
       (write-long _relay1 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _battery_level
     (setq _battery_level (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _current
     (setq _current (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _ADC1
     (setq _ADC1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ADC2
     (setq _ADC2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ADC3
     (setq _ADC3 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ADC4
     (setq _ADC4 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _speed_front_left
     (setq _speed_front_left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_front_right
     (setq _speed_front_right (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _odometry_left
     (setq _odometry_left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _odometry_right
     (setq _odometry_right (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _version
     (setq _version (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _relay1
     (setq _relay1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get teleoperation::Status :md5sum-) "37bcaf258748a50f0e114a698e6097e9")
(setf (get teleoperation::Status :datatype-) "teleoperation/Status")
(setf (get teleoperation::Status :definition-)
      "float64 battery_level
float64 current
int32 ADC1
int32 ADC2
int32 ADC3
int32 ADC4
float64 speed_front_left
float64 speed_front_right
float64 odometry_left
float64 odometry_right
int32 version
int32 relay1

")



(provide :teleoperation/Status "37bcaf258748a50f0e114a698e6097e9")


